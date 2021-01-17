HelloWorldCppDocker

How to create docker image:

Step 1: Install docker for windows on your windows machine ( equivalent on other OS)

Step 2: Clone this repo

Step 3: Build - On command line run the following command
docker build --no-cache -t hello .

This should succeed. If not check and fix errors

Step 4: Run - On the command line run the following command
docker run -it hello:latest

This should produce the output "Hello, World!"