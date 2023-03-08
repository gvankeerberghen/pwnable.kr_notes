FROM kalilinux/kali-rolling
RUN apt update
RUN apt-get -y install kali-linux-headless
RUN apt-get -y install curl python3 gdb binutils file procps python3-pwntools
RUN bash -c "$(curl -fsSL https://gef.blah.cat/sh)"