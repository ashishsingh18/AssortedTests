# Get the GCC preinstalled image from Docker Hub
FROM gcc:4.9

 Update apps on the base image and install cmake
RUN apt-get update && apt-get install -y cmake


# Specify the working directory
WORKDIR /home/HelloWorld

# Copy C++ source code from current dir to the Docker image under /home/HelloWorld
COPY CMakeLists.txt HelloWorld.cpp /home/HelloWorld


# run cmake and make
RUN cmake . && make

# set ./HelloWorld command as the default command to execute when container starts
CMD ["./HelloWorld"]

#define entrypoint - can be same as HelloWorld or can be "bash" if you want to see the contents of the image
#ENTRYPOINT ["bash"]