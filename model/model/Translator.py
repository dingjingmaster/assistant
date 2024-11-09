import torch
import threading
from transformers import AutoTokenizer, AutoModelForSeq2SeqLM

class Translator:
    _instance = None
    _lock = threading.Lock()

    _modelBaseDir : str = None

    @staticmethod
    def setModelBaseDir(modelBaseDir):
        Translator._modelBaseDir = modelBaseDir

    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            with cls._lock:
                if not cls._instance:
                    cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self):
        # 加载分词器和模型
        self._tokenizer = AutoTokenizer.from_pretrained(Translator._modelBaseDir)
        self._EnglishToChineseModel = AutoModelForSeq2SeqLM.from_pretrained(Translator._modelBaseDir)

    '''
    @brief 中英文翻译
    '''
    def englishToChinese(self, englishStr: str) ->str :
        output = ''
        try:
            inputs = self._tokenizer(englishStr, return_tensors='pt')
            outputs = self._EnglishToChineseModel.generate(**inputs)
            output = self._tokenizer.decode(outputs[0], skip_special_tokens=True)
        except Exception as e:
            print(e)
            pass
        return output

def translatorInstance()->Translator:
    return Translator()
