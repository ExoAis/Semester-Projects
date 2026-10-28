#!/usr/bin/env python
# coding: utf-8

# In[1]:


import collections
import os
import pathlib
import re
import string
import sys
import tempfile
import time
import numpy as np
import matplotlib.pyplot as plt
import tensorflow_datasets as tfds
import tensorflow_text as text
import tensorflow as tf


# # Utility Functions

# In[3]:


def add_start_end_tokens(enc, reserved_tokens):
    start = tf.argmax(tf.constant(reserved_tokens) == "[START]")
    end = tf.argmax(tf.constant(reserved_tokens) == "[END]")
    count = enc.bounding_shape()[0]
    starts = tf.fill([count, 1], start)
    ends = tf.fill([count, 1], end)
    enc = tf.concat([starts, enc, ends], axis = 1)
    return enc


# In[10]:


def clean_text(reserved_tokens, token_text):
    bad_tokens = [re.escape(token) for token in reserved_tokens if token != "[UNK]"]
    bad_tokens_re = "|".join(bad_tokens)
    bad_cells = tf.strings.regex_full_match(token_text, bad_tokens_re)
    result = tf.ragged.boolean_mask(token_text, ~bad_cells)
    result = tf.strings.reduce_join(result, separator = " ", axis = -1)
    return result


# # SubWord Tokenizer

# In[12]:


class CustomTokenizer(tf.Module):
    def __init__(self, reserved_tokens, vocab_path):
        self.reserved_tokens = reserved_tokens
        self.vocab_path = tf.saved_model.Asset(vocab_path)
        self.tokenizer = text.BertTokenizer(vocab_path, lower_case = True)
        vocab = pathlib.Path(vocab_path).read_text(encoding='utf-8').splitlines()
        self.vocab = tf.Variable(vocab)
        self.tokenize.get_concrete_function(tf.TensorSpec(shape = [None], dtype = tf.string))
        self.detokenize.get_concrete_function(tf.TensorSpec(shape = [None, None], dtype = tf.int64))
        self.detokenize.get_concrete_function(tf.RaggedTensorSpec(shape = [None, None], dtype = tf.int64))
        self.lookup.get_concrete_function(tf.TensorSpec(shape = [None, None], dtype = tf.int64))
        self.lookup.get_concrete_function(tf.RaggedTensorSpec(shape = [None, None], dtype = tf.int64))
        self.get_vocab_size.get_concrete_function()
        self.get_vocab_path.get_concrete_function()
        self.get_reserved_tokens.get_concrete_function()
    @tf.function()
    def tokenize(self, text):
        enc = self.tokenizer.tokenize(text)
        enc = enc.merge_dims(-2, -1)
        enc = add_start_end_tokens(enc, self.reserved_tokens)
        return enc
    @tf.function()
    def detokenize(self, text):
        dec = self.tokenizer.detokenize(text)
        dec = clean_text(self.reserved_tokens, dec)
        return dec
    @tf.function()
    def lookup(self, token_ids):
        lookups = tf.gather(self.vocab, token_ids)
        return lookups
    @tf.function()
    def get_vocab_size(self):
        return tf.shape(self.vocab)[0]
    @tf.function()
    def get_vocab_path(self):
        return self.vocab_path
    @tf.function()
    def get_reserved_tokens(self):
        return tf.constant(self.reserved_tokens)

