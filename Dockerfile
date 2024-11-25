# 第一阶段
FROM ubuntu:24.04
# AS builder

WORKDIR /app
VOLUME ["/tmp"]

# 安装 poetry
RUN     apt-get update \
    &&  apt-get install python3-poetry -y \
    && apt-get autoremove -y \
    && rm -rf /usr/share/doc /usr/share/man \
    && rm -rf /var/lib/apt/lists/*

COPY model/model            /app/model
COPY model/run.sh           /app/run.sh
#COPY model/install.sh       /app/install.sh
COPY model/poetry.lock      /app/poetry.lock
COPY model/build-cache      /app/
COPY model/pyproject.toml   /app/pyproject.toml

#RUN /app/install.sh

# 第二阶段
#FROM ubuntu:24.04

#WORKDIR /app

# 复制第一阶段构建环境
#COPY --from=builder /usr/lib/python* /usr/lib/
#COPY --from=builder /usr/bin/python* /usr/bin/
#COPY --from=builder /usr/local/lib/python* /usr/local/lib/
#COPY --from=builder /usr/local/bin/python* /usr/local/bin/
#COPY --from=builder /app /app

ENTRYPOINT [ "/usr/bin/bash", "/app/run.sh" ]


