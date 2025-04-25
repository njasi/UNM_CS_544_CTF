FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

COPY real.c /real.c
COPY fake.c /fake.c
COPY manager.c /manager.c
COPY run.sh /run.sh

RUN chmod +x /run.sh

CMD ["/run.sh"]


