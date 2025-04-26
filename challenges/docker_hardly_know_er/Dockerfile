FROM alpine:latest

RUN apk update && \
    apk add --no-cache openssh bash && \
    adduser -D dockeruser && \
    echo "dockeruser:dockerpass" | chpasswd

RUN mkdir /var/run/sshd && \
    ssh-keygen -A && \
    echo 'PermitRootLogin no' >> /etc/ssh/sshd_config && \
    echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config

# echo flag
RUN echo "cs544{docked_in_the_harbor}" > /home/dockeruser/flag.txt && \
    chown dockeruser:dockeruser /home/dockeruser/flag.txt && \
    chmod 600 /home/dockeruser/flag.txt

# motd instead?
RUN echo 'echo "Docker? I hardly know '\''er!"' >> /etc/profile
RUN echo 'echo "You'\''ve successfully connected to a docker container!"' >> /etc/profile

EXPOSE 22

CMD ["/usr/sbin/sshd", "-D"]