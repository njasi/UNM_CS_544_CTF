FROM python:3.9-slim

RUN apt-get update && apt-get install -y \
    hping3 \
    openssh-server \
    curl \
    build-essential \
    libcurl4-openssl-dev \
    libssl-dev \
    make \
    wget \
    tar \
    && rm -rf /var/lib/apt/lists/*
    && pip install Flask \
    && apt-get clean

# get curl-loader
RUN wget https://github.com/aschepis/curl-loader/releases/download/v0.1/curl-loader-0.1.tar.gz -O /tmp/curl-loader.tar.gz && \
    tar -zxvf /tmp/curl-loader.tar.gz -C /tmp && \
    cd /tmp/curl-loader-0.1 && \
    make optimize=1 debug=0 && \
    make install

# clean up
RUN rm -rf /tmp/curl-loader-0.1 /tmp/curl-loader.tar.gz

RUN useradd -m ctf && echo "ctf:ctf" | chpasswd && \
    mkdir /home/ctf/.ssh && \
    usermod -aG sudo ctf

RUN echo "PermitRootLogin no" >> /etc/ssh/sshd_config && \
    echo "PasswordAuthentication yes" >> /etc/ssh/sshd_config && \
    echo "UsePAM yes" >> /etc/ssh/sshd_config && \
    echo 'AllowUsers ctf' >> /etc/ssh/sshd_config

# make it so we dont need to password for sudo
RUN echo "ctf ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN mkdir /home/ctf/app

COPY host.py /home/ctf/app/host.py
COPY flag.txt /flag.txt
COPY attackers.sh /attackers.sh

RUN chmod +x /attackers.sh

EXPOSE 22

# flag is deleted in the python script
CMD ["sh", "-c", "service ssh start && python /home/ctf/app/host.py & nohup /attackers.sh"]
