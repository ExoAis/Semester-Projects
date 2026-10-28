import dash
from dash import dcc, html
from dash.dependencies import Input, Output, State
from XRay_Classification.XRay_Classification import predict
from Neural_Machine_Translation.Transformer import translatePtToEn, translateEnToRu
from Weapon_Detection.Detection.YOLOv7 import detect
from Weapon_Detection.Classification.Weapon_Classifier import classify
import cv2
import numpy as np
import base64

app = dash.Dash(__name__)

app.layout = html.Div([
    dcc.Dropdown(
        id='model-dropdown',
        options=[
            {'label': 'Xray Classifier', 'value': 'XC'},
            {'label': 'Weapon Detection', 'value': 'WD'},
            {'label': 'Language Translation', 'value': 'LT'}
        ],
        value=None,  # No default selection
    ),
    html.Div(id='model-content')
])

def encode_image(image_path):
    # Read the image
    image = cv2.imread(image_path)
    # Convert image to RGB format (OpenCV uses BGR by default)
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # Encode the image as base64
    _, buffer = cv2.imencode('.png', image_rgb)
    encoded_image = base64.b64encode(buffer).decode('utf-8')

    return f'data:image/png;base64,{encoded_image}'

def parse_contents(contents):
    content_type, content_string = contents.split(',')

    # Decode the base64-encoded image
    decoded = base64.b64decode(content_string)
    
    # Convert to NumPy array
    np_image = np.frombuffer(decoded, dtype=np.uint8)
    
    # Decode the image using OpenCV
    img = cv2.imdecode(np_image, cv2.IMREAD_COLOR)

    # Example: Save the image
    cv2.imwrite('Weapon_Detection/Detection/Image.png', img)

def parse_contents_Xray(contents):
    content_type, content_string = contents.split(',')

    # Decode the base64-encoded image
    decoded = base64.b64decode(content_string)
    
    # Convert to NumPy array
    np_image = np.frombuffer(decoded, dtype=np.uint8)
    
    # Decode the image using OpenCV
    img = cv2.imdecode(np_image, cv2.IMREAD_COLOR)

    # Example: Save the image
    return img

# Callback to update the content based on the selected model
@app.callback(
    Output('model-content', 'children'),
    Input('model-dropdown', 'value')
)
def update_model_content(selected_model):
    if selected_model is None:
        return []  # No model selected, return an empty list

    # Create HTML components dynamically based on the selected model
    if selected_model == 'WD':
        return [
            html.H4('Weapon Detection', style={'textAlign': 'center'}),
            dcc.Upload(
                id='upload-image-1',
                children=html.Div([
                    'Drag and Drop or ',
                    html.A('Select Files')
                ]),
                multiple=False,
                style={
                    'width': '100%',
                    'height': '60px',
                    'lineHeight': '60px',
                    'borderWidth': '1px',
                    'borderStyle': 'dashed',
                    'borderRadius': '5px',
                    'textAlign': 'center',
                    'margin': '10px'
                },
            ),
            html.Button('Process', id='process-button-1', style={'margin-left': '730px'}),
            html.Div(id='WD-output-1')
        ]
    elif selected_model == 'LT':
        return [
            html.H4('Language Translation', style={'textAlign': 'center'}),
            html.Div([
                dcc.Textarea(id='input-text', placeholder='Enter text here...', style={'width': '100%', 'height': '100px'}),
            ], style={'width': '33%', 'display': 'inline-block'}),
            html.Div([
                dcc.Dropdown(
                    id='translation-direction',
                    options=[
                        {'label': 'Portuguese to English', 'value': 'pt_to_en'},
                        {'label': 'English to Russian', 'value': 'en_to_ru'}
                    ],
                    value='pt_to_en',  # Default selection
                ),
                html.Button('Translate', id='translate-button', style={'margin-left': '200px'}),
            ], style={'width': '33%', 'display': 'inline-block', 'vertical-align': 'top'}),
            html.Div([
                dcc.Textarea(id='output-text', placeholder='Translation will appear here...', style={'width': '100%', 'height': '100px'}),
            ], style={'width': '33%', 'display': 'inline-block'}),
        ]
    elif selected_model == 'XC':
        return [
            html.H4('Xray Classification', style={'textAlign': 'center'}),
            dcc.Upload(
                id='upload-image-2',
                children=html.Div([
                    'Drag and Drop or ',
                    html.A('Select Files')
                ]),
                multiple=False,
                style={
                    'width': '100%',
                    'height': '60px',
                    'lineHeight': '60px',
                    'borderWidth': '1px',
                    'borderStyle': 'dashed',
                    'borderRadius': '5px',
                    'textAlign': 'center',
                    'margin': '10px'
                },
            ),
            html.Button('Process', id='process-button-2', style={'margin-left': '730px'}),
            html.Div(id='WD-output-2')
        ]

# Callback to handle image upload and process button click for Weapon Detection
@app.callback(
    Output('WD-output-1', 'children'),
    Input('process-button-1', 'n_clicks'),
    State('upload-image-1', 'contents')
)
def process_WD_image(n_clicks, image_contents):
    if n_clicks is None:
        return dash.no_update

    image_path = 'Image.png'
    parse_contents(image_contents)
    processed_image = detect(image_path, conf = 0.5, iou = 0.5)
    label = classify(processed_image)

    # Display the processed image or any other information
    return [
        html.P(label, style={'textAlign': 'center', 'fontSize': '24px', 'fontWeight': 'bold'}),
        html.Img(src = encode_image('Weapon_Detection/Detection/result.jpg'), style={'width': '50%'})
    ]


@app.callback(
    Output('output-text', 'value'),
    [Input('translate-button', 'n_clicks')],
    [State('input-text', 'value'), State('translation-direction', 'value')]
)
def process_LT_image(n_clicks, inText, trDir):
    if n_clicks is None:
        return dash.no_update
    
    if trDir == 'pt_to_en':
        text = translatePtToEn(inText, len(inText) - 3)
    else:
        text = translateEnToRu(inText, len(inText) - 3)

    return text
    
@app.callback(
    Output('WD-output-2', 'children'),
    Input('process-button-2', 'n_clicks'),
    State('upload-image-2', 'contents')
)
def process_XC_image(n_clicks, image_contents):
    if n_clicks is None:
        return dash.no_update

    img = parse_contents_Xray(image_contents)
    label = predict(img)

    # Display the processed image or any other information
    return [
        html.P(label, style={'textAlign': 'center', 'fontSize': '24px', 'fontWeight': 'bold'})
        # Customize this based on your requirements
    ]

if __name__ == '__main__':
    app.run_server(debug=True)
