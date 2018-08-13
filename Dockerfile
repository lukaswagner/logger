FROM ubuntu

RUN apt-get -y update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    ca-certificates \
    && apt-get autoremove

WORKDIR /usr/src/build

ADD . /usr/src/sources

RUN cd ../sources/dependencies && cmake .

RUN cmake ../sources -DBUILD_EXAMPLE=ON -DBUILD_TESTS=ON

RUN make

RUN ./tests
