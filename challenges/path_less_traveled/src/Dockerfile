FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    bash \
    sudo \
    cron \
    openssh-server \
    logrotate \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m ctf && echo 'ctf:ctf' | chpasswd && \
    echo "ctf ALL=(ALL) NOPASSWD: /bin/false" >> /etc/sudoers

RUN mkdir /var/run/sshd
RUN echo 'PermitRootLogin yes' >> /etc/ssh/sshd_config && \
    echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config

COPY rotate-logs.sh /opt/rotate-logs.sh
COPY logcron /etc/cron.d/logcron
RUN chmod +x /opt/rotate-logs.sh && \
    chmod u+s /opt/rotate-logs.sh && \
    chmod 644 /etc/cron.d/logcron && \
    touch /var/log/syslog && \
    crontab /etc/cron.d/logcron

# crond.pid stuff
# RUN mkdir -p /var/run && chmod 755 /var/run

COPY flag.txt /home/ctf/flag.txt
RUN chmod 600 /home/ctf/flag.txt

# USER ctf
# WORKDIR /home/ctf
# RUN mkdir -p bin && echo 'export PATH=/home/ctf/bin:$PATH' >> ~/.bashrc

EXPOSE 22
CMD service cron start && /usr/sbin/sshd -D
