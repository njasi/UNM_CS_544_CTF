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

COPY real.c /real.c
COPY fake.c /fake.c
COPY manager.c /manager.c
COPY run.sh /run.sh

RUN gcc -o /real /real.c && \
    gcc -o /fake /fake.c && \
    gcc -o /manager /manager.c && \
    rm /real.c /fake.c /manager.c

# make it so we dont need to password for sudo
RUN echo "inspector ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN chmod +x /run.sh

EXPOSE 22

CMD service ssh start && /run.sh
