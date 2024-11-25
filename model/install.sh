#!/bin/bash

curDir=$(dirname $(realpath -- $0))

pythonShell=${curDir}/model/main.py

cd $curDir

export POETRY_CACHE_DIR=${curDir}/build-cache

poetry install --no-dev

