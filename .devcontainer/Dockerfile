FROM --platform=linux/amd64 rust:1.70-bullseye

RUN apt-get update && apt-get install -y \
	build-essential \
	curl \
	gcc \
	gdb \
	lldb \
	git \
	pkg-config \
	nasm \
	mtools \
	xorriso \
	grub-pc-bin \
	grub-efi-amd64-bin \
	qemu \
	qemu-system-x86 \
	&& rm -rf /var/lib/apt/lists/*

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" -y

COPY .zshrc /root/.zshrc