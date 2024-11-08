import torch
from transformers import AutoTokenizer, AutoModelForSeq2SeqLM


class Translator:
    def __init__(self, modelPath):
        self._modelPath = modelPath

        # 加载分词器和模型
        self._tokenizer = AutoTokenizer.from_pretrained(modelPath)
        self._EnglishToChineseModel = AutoModelForSeq2SeqLM.from_pretrained(modelPath)

    '''
    @brief 中英文翻译
    '''
    def englishToChinese(self, englishStr) ->str :
        inputs = self._tokenizer(englishStr, return_tensors='pt')
        outputs = self._EnglishToChineseModel.generate(**inputs)
        return self._tokenizer.decode(outputs[0], skip_special_tokens=True)

