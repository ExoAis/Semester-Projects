import random
import numpy as np
from tqdm import tqdm
import gymnasium as gym
from matplotlib import pyplot as plt


# Variables

Alpha = 0.2
Gamma = 0.85
Epsilon = 0.2
Num_Eps = 2500
C = 256
Batch_Size = 32
Buffer_Size = 100000
Save_Interval = 100
Num_Features_State = 8
Num_Actions = 4


# Functions

def max_argmax(state, func_aproximator, num_actions = Num_Actions):
    max_Q = -float('inf')
    best_actions = []
    
    for a in range(num_actions):
        cur_Q = func_aproximator(state, a)
        if cur_Q > max_Q:
            max_Q = cur_Q
            best_actions = [a]
        elif cur_Q == max_Q:
            best_actions.append(a) 

    # Choose a random action among the best actions
    best_action = np.random.choice(best_actions)
    return max_Q, best_action

def epsilon_greedy(state, func_aproximator, epsilon = Epsilon, num_actions = Num_Actions):
    if np.random.random() < epsilon:
        return np.random.choice(num_actions)
    else:
        _, best_action = max_argmax(state, func_aproximator, num_actions)
        return best_action

def run_episode(env, action):
    next_state, reward, terminated, truncated, info = env.step(action)
    return next_state, reward, terminated or truncated

def build_q_vector(state, action):
    action_vector = np.zeros(shape=(Num_Actions,))
    action_vector[action] = 1
    q_feature_vector = np.hstack((state, action_vector))
    return q_feature_vector

def func_aproximator(state, action, weights):
    q_feature_vector = build_q_vector(state, action)
    return np.dot(q_feature_vector, weights)

def DQN(
        env, 
        discount = Gamma, 
        learning_rate = Alpha, 
        num_episodes = Num_Eps, 
        steps_for_target_update = C,
        batch_size = Batch_Size, 
        replay_buffer_size = Buffer_Size,
        save_interval = Save_Interval
):
    replay_buffer = []    
    weights = np.random.normal(loc=0, scale=0.1, size=(Num_Features_State + Num_Actions,))
    target_weights = weights.copy()
    steps_finished = 0

    mses = []
    returns = []
    mean_scores = []

    for episode_no in tqdm(range(num_episodes), desc="Running Episodes"):
        state, info = env.reset()
        done = False

        cur_return = 0
        cum_reward = 0
        time = 0
        while not done:
            cur_func_aproximator = lambda s, a: func_aproximator(
                state=s, action=a, weights=weights
            )
            action = epsilon_greedy(state, cur_func_aproximator)
            next_state, reward, done = run_episode(env, action)

            replay_buffer.append((state, action, next_state, reward, done))
            
            cur_return += reward * discount ** time
            cum_reward += reward
            time += 1
            state = next_state

            if len(replay_buffer) > replay_buffer_size:
                replay_buffer.pop(0)

            if len(replay_buffer) > batch_size:
                batch = random.sample(replay_buffer, batch_size)

                for s, a, sp, r, d in batch:                    
                    target = r
                    if d:
                        target_func_aproximator = lambda s, a: func_aproximator(
                            state=s, action=a, weights=target_weights
                        )
                        max_next_q, _ = max_argmax(sp, target_func_aproximator)
                        target += discount * max_next_q

                    q_feature_vector = build_q_vector(state=s, action=a)
                    weights += learning_rate * (target - cur_func_aproximator(s, a)) * q_feature_vector
                    cur_error = target - cur_func_aproximator(s, a)
                    steps_finished += 1

            if steps_finished > steps_for_target_update:
                steps_finished = 0
                target_weights = weights.copy()

        if episode_no % save_interval == 0:
            mses.append(np.mean(np.square(cur_error)))
            returns.append(cur_return)
            mean_scores.append(cum_reward / time)

    learned_func_aproximator = lambda s, a: func_aproximator(
        state=s, action=a, weights=weights
    )
    stats = {
        "mean_squared_error": mses,
        "returns_per_episiode": returns,
        "mean_scores_per_episode": mean_scores
    }
    return learned_func_aproximator, stats


if __name__ == "__main__":    
    env = gym.make("LunarLander-v3")

    learned_func_aproximator, stats = DQN(env)

    # Plotting
    for stat_name, stat in stats.items():
        plt.scatter(list(range(len(stat))), stat)
        plt.title(f"DQN: {stat_name}")
        plt.show()
        plt.clf()