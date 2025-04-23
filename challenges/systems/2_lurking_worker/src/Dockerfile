FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

COPY main.c /main.c
COPY run.sh /run.sh

RUN chmod +x /run.sh

CMD ["/run.sh"]