FROM fedora:30

LABEL version="2.1"
ADD install_criterion.sh /root/

RUN dnf -y update && dnf -y install gcc gcc-c++ make\
	&& dnf -y install wget gcovr cmake findutils unzip bzip2 tar git openssh

RUN /root/install_criterion.sh

WORKDIR /tmp

RUN wget https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz && tar xzvf boost_1_70_0.tar.gz && cp -r /tmp/boost_1_70_0/boost /usr/include/

WORKDIR /app

COPY . /app

RUN g++ async_tcp_echo_server.cpp -lpthread && make && make tests

CMD [ "game_server", "8080" ]

EXPOSE 8080
