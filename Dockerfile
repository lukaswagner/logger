FROM ubuntu

RUN echo "*** Installing dependencies ***" \
    && apt-get -y update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    && apt-get autoremove

WORKDIR /usr/src/build

ADD . /usr/src/sources

RUN echo "*** Building dependencies ***" \
    && cd dependencies \
    && cmake . \
    && cd ..

RUN echo "*** Running cmake ***" \
    && cmake ../sources -DBUILD_EXAMPLE=ON -DBUILD_TESTS=ON

RUN echo "*** Building project ***" \
    && make

RUN echo "*** Running tests ***" \
    && ./tests
