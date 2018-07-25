FROM ubuntu

RUN echo "*** Installing dependencies ***" \
    && apt-get -y update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    && apt-get autoremove

WORKDIR /usr/src/build

ADD . /usr/src/sources

RUN echo "*** Running cmake ***" \
    && cmake ../sources -DBUILD_EXAMPLE=ON

RUN echo "*** Building project ***" \
    && make
