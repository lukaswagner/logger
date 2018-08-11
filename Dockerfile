FROM ubuntu

RUN echo "*** Installing dependencies ***" \
    && apt-get -y update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    ca-certificates \
    doxygen \
    && apt-get autoremove

WORKDIR /usr/src/build

ADD . /usr/src/sources

RUN echo "*** Building dependencies ***" \
    && cd ../sources/dependencies \
    && cmake .

RUN echo "*** Running cmake ***" \
    && cmake ../sources -DBUILD_EXAMPLE=ON -DBUILD_TESTS=ON -DBUILD_DOCS=ON

RUN echo "*** Building project ***" \
    && make \
    && make docs

RUN echo "*** Running tests ***" \
    && ./tests
