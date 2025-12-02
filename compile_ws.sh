#!/bin/sh

gcc -Wall -Wextra -pedantic ws_example.c lib/wsServer/src/ws.c lib/wsServer/src/utf8.c lib/wsServer/src/handshake.c lib/wsServer/src/sha1.c lib/wsServer/src/base64.c -Ilib/wsServer/src -Ilib/wsServer/include -o ws_example
