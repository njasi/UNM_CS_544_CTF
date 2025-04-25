FROM ubuntu:22.04

# Install dependencies including OpenSSH
RUN apt-get update && apt-get install -y \
    gcc \
    build-essential \
    openssh-server \
    && rm -rf /var/lib/apt/lists/*

# Create SSH directory and a user
RUN mkdir /var/run/sshd && \
    useradd -m ctf && echo 'inspector:gadget' | chpasswd && \
    echo 'PermitRootLogin no' >> /etc/ssh/sshd_config && \
    echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config && \
    echo 'AllowUsers inspector' >> /etc/ssh/sshd_config

# Copy challenge files
COPY real.c /real.c
COPY fake.c /fake.c
COPY manager.c /manager.c
COPY run.sh /run.sh

# Compile binaries and clean up sources
RUN gcc -o /real /real.c && \
    gcc -o /fake /fake.c && \
    gcc -o /manager /manager.c && \
    rm /real.c /fake.c /manager.c

# Set permissions
RUN chmod +x /run.sh

# Expose SSH port
EXPOSE 22

# Launch SSH and the challenge script
CMD service ssh start && /run.sh
