FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    bash \
    sudo \
    cron \
    openssh-server \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m ctf && echo 'ctf:ctf' | chpasswd && \
    echo "ctf ALL=(ALL) NOPASSWD: /bin/false" >> /etc/sudoers

RUN mkdir /var/run/sshd
RUN echo 'PermitRootLogin yes' >> /etc/ssh/sshd_config && \
    echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config

# rotate script run as root
COPY rotate-logs.sh /opt/rotate-logs.sh
COPY logcron /etc/cron.d/logcron
RUN chmod +x /opt/rotate-logs.sh && chmod 644 /etc/cron.d/logcron && \
    touch /var/log/syslog && crontab /etc/cron.d/logcron

USER ctf
WORKDIR /home/ctf
RUN mkdir -p bin && echo 'export PATH=/home/ctf/bin:$PATH' >> ~/.bashrc

COPY flag.txt /root/flag.txt
RUN chmod 600 /root/flag.txt

EXPOSE 22
CMD service cron start && /usr/sbin/sshd -D
