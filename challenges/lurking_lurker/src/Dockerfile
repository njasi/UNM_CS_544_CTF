FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc \
    build-essential \
    openssh-server \
    sudo \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir /var/run/sshd && \
    useradd -m inspector && echo 'inspector:gadget' | chpasswd && \
    usermod -aG sudo inspector && \
    echo 'PermitRootLogin no' >> /etc/ssh/sshd_config && \
    echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config && \
    echo 'AllowUsers inspector' >> /etc/ssh/sshd_config

COPY normal.c /normal.c
COPY target.c /target.c
COPY shared.c /shared.c
COPY shared.h /shared.h
COPY run.sh /run.sh

RUN gcc -o /normal /shared.c /normal.c && \
    gcc -o /target /shared.c /target.c && \
    rm /normal.c /target.c /shared.c

# make it so we dont need to password for sudo
RUN echo "inspector ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# fix /etc/hosts so we dont have sudo complaining
# idk how to fully fix this tbh
# RUN echo "127.0.0.1 $(hostname)" >> /etc/hosts

RUN chmod +x /run.sh

EXPOSE 22

CMD ["sh", "-c", "service ssh start && /run.sh"]
