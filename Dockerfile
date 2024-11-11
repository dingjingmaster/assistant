FROM ubuntu:24.04
LABEL author="dingjing" email="dingjing@live.cn"

VOLUME ["/tmp"]

RUN     apt-get update \
    &&  apt-get install python3-poetry -y

COPY model /usr/local/assistant/model

ENTRYPOINT [ "/usr/bin/bash", "/usr/local/assistant/model/run.sh" ]


