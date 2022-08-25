#!/usr/bin/env python
# coding:utf-8
"""
Author  : Xiwen Lu
Time    : 2021/6/6 10:37
Desc    : 用于读取G、D并对其进行测试
"""
import torch
import numpy as np
from DCGAN_Net import *
import matplotlib.pyplot as plt
import torchvision.transforms as transforms


ngpu = 1
pathG = "net/G_Epoch2001.pth"
device = torch.device("cuda:0")

netG = Generator(ngpu).to(device)
netG.load_state_dict(torch.load(pathG))

netG.eval()
noise = torch.randn(1, nz, 1, 1, device=device)
# Generate fake image batch with G
fake = netG(noise).detach().cpu()
# fake.to
print(fake[0].size())

t = fake[0].clone()  # avoid modifying tensor in-place


def norm_ip(img, low, high):
    img.clamp_(min=low, max=high)
    img.sub_(low).div_(max(high - low, 1e-5))
    return img


nimg = norm_ip(t, float(t.min()), float(t.max()))
# plt.figure()
# img = np.transpose(nimg,(1,2,0))
# plt.savefig(pic_filename)
img = transforms.ToPILImage()(nimg).convert('RGB')


# plt.imshow(np.transpose(fake[0], (1, 2, 0)))
plt.imshow(img)
plt.show()
