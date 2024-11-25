#!/bin/env python
#-*- coding=utf8 -*-

from transformers import T5ForConditionalGeneration, T5Tokenizer

device = 'cpu' #or 'cpu' for translate on cpu

model_name = 'model/data/'
model = T5ForConditionalGeneration.from_pretrained(model_name)
model.eval()
model.to(device)
tokenizer = T5Tokenizer.from_pretrained(model_name)

prefix = 'translate to zh: '
src_text = prefix + "An individual dentry usually has a pointer to an inode. Inodes are filesystem objects such as regular files, directories, FIFOs and other beasts. They live either on the disc (for block device filesystems) or in the memory (for pseudo filesystems). Inodes that live on the disc are copied into the memory when required and changes to the inode are written back to disc. A single inode can be pointed to by multiple dentries (hard links, for example, do this)."

# translate Russian to Chinese
input_ids = tokenizer(src_text, return_tensors="pt")

generated_tokens = model.generate(**input_ids.to(device))

result = tokenizer.batch_decode(generated_tokens, skip_special_tokens=True)
print(result)
# 再吃这些法国的甜蜜的面包。

