# CS 544 final project

## Setup:

setup is all contained within setup.sh:

```sh
./setup.sh
```

this will clone the ctfd repo, make a secret key & (copy over our custom challenge files?)

## Start:

The service can be started with the start bash script:

```sh
./start.sh
```

## Making a CTF:

Ctfs have to be created on the ctfd admin interface or via the api. for simplicity we will represent our challenges as json. Below is an example json.

```json
{
  "title": "Hello World",
  "score": 5,
  "message": "Hello this is a basic challenge to get you started, the flag for this challenge is \"cs544{hello_world}\"",
  "flag": "cs544{hello_world}",
  "download": "./download.zip"
}
```


# Config
## CTFd Docker Plugin
This project uses the [CTFd docker challenges](https://github.com/offsecginger/CTFd-Docker-Challenges) plugin, it will be installed via the setup.sh script but we also need to configure our docker deamon:

open or create `/etc/docker/daemon.json`
```json
{
  "hosts": ["tcp://0.0.0.0:2376"],
  "tls": true,
  "tlsverify": true,
  "tlscacert": "/etc/docker/ssl/ca.pem",
  "tlscert": "/etc/docker/ssl/server-cert.pem",
  "tlskey": "/etc/docker/ssl/server-key.pem"
}
```