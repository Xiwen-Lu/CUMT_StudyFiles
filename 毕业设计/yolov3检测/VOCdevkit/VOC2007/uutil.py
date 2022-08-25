#!/usr/bin/env python
# coding:utf-8
"""
Author  : Xiwen Lu
Time    : 2021/5/29 14:21
Desc    : 测试部分图片操作
"""

import matplotlib.pyplot as plt
from PIL import Image
from torch.utils.data import DataLoader

im = Image.open("JPEGImages/17.jpg")
plt.imshow(im)
plt.show()


