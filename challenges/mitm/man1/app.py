import requests
import time

URL = "172.18.0.22"
DATA = "banana48902"
HEADERS = {"Content-Type": "text/plain"}  # Assuming plain text body

def send_put():
    while True:
        try:
            response = requests.put(URL, data=DATA, headers=HEADERS)
            print(f"PUT {URL} - Status: {response.status_code}")
        except Exception as e:
            print(f"Request failed: {e}")
        time.sleep(30)

if __name__ == "__main__":
    send_put()