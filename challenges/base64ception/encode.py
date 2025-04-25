import base64
import json

def encode_base64_repeatedly(message: str, times: int) -> str:
    encoded = message.encode('utf-8')
    for _ in range(times):
        encoded = base64.b64encode(encoded)
    return encoded.decode('utf-8')

with open("./config.json", "r") as file:
    message = "eviluser:" + json.load(file)["flag"]
    print("message to encode:\t" + message)
times = 21

encoded_message = encode_base64_repeatedly(message, times)
print(f"Encoded {times} times & wrote output to obfuscated.txt")

with open("./obfuscated.txt","w+") as file:
    file.write(encoded_message)