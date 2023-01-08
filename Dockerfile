FROM ubuntu:23.04

RUN apt-get update
RUN apt-get -y install git wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util
RUN apt-get -y install python-is-python3 python3 python3-pip

RUN pip3 install pyelftools>=0.29

WORKDIR /src
RUN git clone -b v4.4.3 --recursive https://github.com/espressif/esp-idf.git
RUN git clone -b v1.19.1 https://github.com/micropython/micropython.git

WORKDIR /src/esp-idf
RUN ./install.sh
RUN echo "#! /bin/bash\n. /src/esp-idf/export.sh" > esp32_idf
RUN chown 777 esp32_idf
RUN chmod +x esp32_idf
ENV PATH="${PATH}:/src/esp-idf/"

WORKDIR /src/micropython/mpy-cross
RUN make
ENV PATH="${PATH}:/src/micropython/mpy-cross/build/"

WORKDIR /src/bin
RUN wget https://github.com/espressif/crosstool-NG/releases/download/esp-2021r2-patch5/xtensa-esp32-elf-gcc8_4_0-esp-2021r2-patch5-linux-amd64.tar.gz
RUN tar -xvf xtensa-esp32-elf-gcc8_4_0-esp-2021r2-patch5-linux-amd64.tar.gz
ENV PATH="${PATH}:/src/bin/xtensa-esp32-elf/bin"

WORKDIR /src/micropython/examples/natmod/myfeature
