from ubuntu:16.04

WORKDIR /game


RUN apt-get update
RUN apt install make
RUN apt-get install freeglut3-dev glew-utils libglewmx1.13 libfreeimage-dev -y
COPY . .

RUN make
RUN chmod -R 775 game-release

CMD ["./game-release"]
