FROM debian:bullseye

ARG CLANG_VERSION=14

# Install packages
RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    rm -f /etc/apt/apt.conf.d/docker-clean && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
        lsb-release wget software-properties-common gnupg  \
        python3 python3-pip \
        gcc-multilib g++-multilib && \
    wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && \
    ./llvm.sh ${CLANG_VERSION} && \
    rm llvm.sh

# Install meson + ninja
RUN python3 -m pip install meson[ninja]

# Set default compiler
ENV CC=clang-${CLANG_VERSION} CXX=clang++-${CLANG_VERSION}

# Check compiler
RUN $CXX -v