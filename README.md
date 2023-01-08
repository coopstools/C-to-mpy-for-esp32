# C-2-MPY Builder for ESP32

This repo contains a module for easily compiling and cross-piling C code to .MPY files for use in Micropython projects used on teh ESP32 board. This repo is NOT meant to be used for other architectures or languages.

## Building C Modules For Micropython ESP32

### Pulling Image

In lieu of building the docker image locally, the image can be pulled from the GitHub Container registry using `docker pull ghcr.io/coopstools/c-to-mpy-for-esp32:v0`. This is big image, and may take some time to download.

### Building Image

If you would like to build the image locally, rather than pulling, run the command `. ./build-image.sh`. This process does take a while to run, so please be patient.

### Building Your Library

Start the image using the `. ./start-builder.sh` command. This will start up and attach to the container. It will start you in a folder linked to the `lib` folder in this directory. If you run `ls ../`, you'll see a list of other example libraries for building C modules for micropython.

WARNING: this container is ephermal and will be deleted if you exit out. Any work not saved in the starting folder, `/src/micropython/examples/natmod/myfeature`, will be lost.

To build a mod, you need at least a C file, ie *.c or *.h, and a makefile. The best appraoch is to just copy on of the example, `cp ../features0/* ./`, and update the files to be what you need.

In the make file, make sure to update the target architecture to use extensawin:
```text
ARCH = xtensawin
```

Also include any additional files that are needed for compiling, and feel free to change the module name to whatever you desire.

Then, just run the make command, `make`. Running this command will generate a `.mpy. file that you can now copy to your Micropython project.

## Using MPY files

`.mpy` files, as can be found in the [micropython documentation](https://docs.micropython.org/en/latest/develop/natmod.html), can be used just like `.py`. Simply place them in you source directory and import. As this is well documented elsewhere, I will not expound further.

## Example

The module found here is an example of creating a parallel driver for the ws2812b. It takes an array of ints, and uses the first 4 LSBs to write to GPIO ports 21, 13, 14, and 15 on the ESP32. This is functioning but does not have full documentation. If you wish to use this library, please leave a ticket and I will add the necessary documentation.

Warning, although I made a mask, it is buggy. Using this library will overwrite all other GPIO values.