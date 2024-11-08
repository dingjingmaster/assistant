#!/bin/bash

curDir=$(dirname $(realpath -- $0))

pythonShell=${curDir}/model/main.py

poetry run python ${pythonShell} "${curDir}/model"
