FROM fedora:30

LABEL version="2.1"
ADD install_criterion.sh /root/

RUN dnf -y update && dnf -y install gcc gcc-c++ make\
	&& dnf -y install wget gcovr cmake findutils unzip bzip2 tar git openssh

RUN /root/install_criterion.sh

WORKDIR /app

COPY . /app

RUN make
