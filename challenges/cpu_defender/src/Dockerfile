FROM python:3.9-slim

RUN apt-get update && apt-get install -y \
    hping3 \
    openssh-server \
    curl \
    && pip install Flask \
    && apt-get clean

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
