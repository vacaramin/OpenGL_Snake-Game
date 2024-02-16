FROM ubuntu:16.04

WORKDIR /game

RUN apt-get update && \
    apt-get install -y build-essential make && \
    apt-get install -y freeglut3-dev glew-utils libglewmx1.13 libfreeimage-dev

COPY . .

RUN  make && \
    chmod -R 775 game-release
CMD [ "make" ]
