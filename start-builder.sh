#! /bin/bash

docker run -it --rm -v "$(pwd)"/lib:/src/micropython/examples/natmod/myfeature ghcr.io/coopstools/c-to-mpy-for-esp32:v0 bash
