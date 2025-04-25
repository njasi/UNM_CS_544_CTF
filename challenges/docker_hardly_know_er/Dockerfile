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
RUN echo 'echo "\033[1;33mDocker? I hardly know '\''er!\033[0m"' >> /etc/profile
RUN echo 'echo "You\'ve successfully connected to a docker container!"' >> /etc/profile

# Expose SSH
EXPOSE 22

# Run sshd
CMD ["/usr/sbin/sshd", "-D"]