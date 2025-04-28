import os
import time
import logging
import threading
from collections import deque
from flask import Flask, request, abort
from logging.handlers import RotatingFileHandler


with open("/flag.txt", "r") as file:
    FLAG = file.readline()
# remove the flag right after starting up <3
os.remove("/flag.txt")

app = Flask(__name__)
recent_requests = deque([time.time()] * 30, maxlen=50)
lock = threading.Lock()

#################
# SETUP LOGGING #
#################

# 200 kb limit
log_handler = RotatingFileHandler(
    '/home/ctf/app/access.log', maxBytes=200 * 1024, backupCount=1
)
log_handler.setLevel(logging.DEBUG)

formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
log_handler.setFormatter(formatter)

logger = logging.getLogger(__name__)
logger.addHandler(log_handler)
logger.setLevel(logging.DEBUG)

logger.info("Starting up")

@app.before_request
def log_request():
    logger.info(
        f"Request received: {request.method} {request.path} from {request.remote_addr}"
    )


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
    return FLAG + "\n"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80)
