import torch
from transformers import AutoTokenizer, AutoModelForSeq2SeqLM

# 模型文件路径
modelPath = './data'

# 加载模型
model = AutoModelForSeq2SeqLM.from_pretrained(modelPath)
model.eval()

# 将模型转为 ScriptModule
scriptModel = torch.jit.script(model)

# 保存为 torchScript 格式
scriptModel.save('./model/pytorch_model.pt')