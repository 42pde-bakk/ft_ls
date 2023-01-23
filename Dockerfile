FROM debian:11
WORKDIR /code

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y gcc clang make zsh tcpdump wget git curl man

# terminal colors with xterm
ENV TERM xterm
# set the zsh theme
ENV ZSH_THEME=eastwood

# run the installation script
RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true
