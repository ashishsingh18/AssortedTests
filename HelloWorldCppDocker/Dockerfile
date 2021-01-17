FROM gcc:4.9

RUN apt-get update && apt-get install -y cmake

WORKDIR /home/HelloWorld

COPY CMakeLists.txt HelloWorld.cpp /home/HelloWorld

RUN cmake . && make

CMD ["./HelloWorld"]

#ENTRYPOINT ["bash"]