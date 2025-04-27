import os
import time
import logging
import threading
from collections import deque
from flask import Flask, request, abort
from logging.handlers import RotatingFileHandler


with open("/flag.txt","r") as file:
    FLAG = file.readline()
# remove the flag right after starting up <3
os.remove("/flag.txt")

app = Flask(__name__)
recent_requests = deque([time.time()] * 30, maxlen=50)
lock = threading.Lock()

#################
# SETUP LOGGING #
#################

log_handler = RotatingFileHandler(
    '/home/ctf/app/access.log',
    maxBytes=10 * 1024 * 1024,
    backupCount=1
)

log_handler.setLevel(logging.INFO)
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
log_handler.setFormatter(formatter)
app.logger.addHandler(log_handler)

####################
# SETUP APP ROUTES #
####################

@app.route("/")
def home():
    """
    index route to test if the server is running
    """
    return "Victim is up and server running."

@app.route("/flag")
def flag():
    """
    Flag route which the player needs to defend to get access to the flag

    - if (there have been 20 requests in the last 10 seconds):
        no flag, send 503
    - else:
        send flag
    """

    now = time.time()
    with lock:
        recent_requests.append(now)
        # Count requests in last 10 seconds
        recent = [t for t in recent_requests if now - t < 10]

        if len(recent) > 20:
            abort(503)
    return "CTF{ddos_defended_successfully}"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80)
