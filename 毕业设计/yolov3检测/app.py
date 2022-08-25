#!/usr/bin/env python
# coding:utf-8
"""
Author  : Xiwen Lu
Time    : 2021/5/25 21:46
Desc    : 服务器端程序
"""
from flask import Flask, request, render_template,jsonify
from PIL import Image
from yolo import YOLO
from flask_cors import CORS
import base64
import io
import matplotlib.pyplot as plt

yolo = YOLO()
app = Flask(__name__)
CORS(app, supports_credentials=True)

@app.route('/')
def hello_world():
    a = 1+1
    return render_template('index.html')

@app.route('/predict',methods=["POST"])
def predict():
    filename = "test.jpg"
    for upload in request.files.getlist("file"):
        print(upload)
        image = Image.open(upload)
        # destination = "./img/test.jpg"
        r_image = yolo.detect_image(image)
        # r_image.show()
        r_image.save("static/test.jpg")
        # upload.save(destination)

    return render_template("results.html",image_name=filename)

@app.route('/test',methods=["POST"])
def test():
    response = request.get_json()
    data_str = response['picture']
    # print(data_str)
    point = data_str.find(',')
    base64_str = data_str[point:]  # remove unused part like this: "data:image/jpeg;base64,"

    image = base64.b64decode(base64_str)
    img = Image.open(io.BytesIO(image))

    if(img.mode!='RGB'):
        img = img.convert("RGB")

    r_image = yolo.detect_image(img)
    print(r_image)
    plt.imshow(r_image)
    plt.show()

    img_byte = io.BytesIO()
    r_image.save(img_byte, format='JPEG')
    binary_str2 = img_byte.getvalue()
    data = base64.b64encode(binary_str2)
    data_str = "data:image/jpeg;base64,"+str(data,encoding = "utf-8")
    # print(data_str)
    results = {"img": data_str}
    return jsonify(results)

if __name__ == '__main__':
    app.run()