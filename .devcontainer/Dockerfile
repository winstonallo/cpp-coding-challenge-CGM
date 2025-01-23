FROM gcc:14.2.0-bookworm

RUN apt update -y && apt upgrade -y && \
    apt install -y zsh && \
    rm -rf /var/lib/apt/lists/*

    
RUN git config --global --add safe.directory /workspaces/cpp-coding-challenge-CGM

RUN useradd -ms /usr/bin/zsh winstonallo && \
usermod -aG sudo winstonallo

USER winstonallo

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" -y

RUN git config --global --add safe.directory /workspaces/cpp-coding-challenge-CGM