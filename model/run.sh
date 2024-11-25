#!/bin/bash

curDir=$(dirname $(realpath -- $0))

pythonShell=${curDir}/model/main.py

cd $curDir

export POETRY_CACHE_DIR=${curDir}/build-cache

poetry install
#poetry run python ./main.py "./model/data"
poetry run python ${pythonShell} "${curDir}/model/data"
