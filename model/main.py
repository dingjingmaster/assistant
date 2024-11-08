import torch
from transformers import AutoTokenizer, AutoModelForSeq2SeqLM

# 模型文件路径
modelPath = './model'

# 加载分词器和模型
tokenizer = AutoTokenizer.from_pretrained(modelPath)
model = AutoModelForSeq2SeqLM.from_pretrained(modelPath)

# 准备输入数据
inputs = tokenizer('Hello, my dog is cute', return_tensors='pt')

# 在模型上推理
outputs = model.generate(**inputs)

# 获取预测结果
print(tokenizer.decode(outputs[0], skip_special_tokens=True))