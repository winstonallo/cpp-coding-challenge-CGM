FROM gcc:14.2.0-bookworm

RUN apt update -y && apt upgrade -y && \
    apt install -y \
    zsh \
    python3 \
    python3-pip \
    cmake \
    valgrind \
    unzip \
    && \
    rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/clangd/clangd/releases/download/19.1.2/clangd-linux-19.1.2.zip

RUN unzip clangd-linux-19.1.2.zip -d /usr/local && \
    ln -s /usr/local/clangd_19.1.2/bin/clangd /usr/local/bin/clangd && \
    rm clangd-linux-19.1.2.zip

RUN pip install conan --break-system-packages

RUN git config --global --add safe.directory /workspaces/cpp-coding-challenge-CGM

RUN useradd -ms /usr/bin/zsh winstonallo && \
usermod -aG sudo winstonallo

USER winstonallo

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" -y

RUN git config --global --add safe.directory /workspaces/cpp-coding-challenge-CGM

RUN conan profile detect
