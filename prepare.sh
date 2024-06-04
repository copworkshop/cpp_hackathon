#!/bin/bash

set -e
set -x

conan config install ./conan
if ! [ -f ~/.conan/profiles/default ]; then
    conan profile new default --detect
fi
conan profile update settings.compiler.libcxx=libstdc++11 default
pip install gcovr

THIS_DIR=$(pwd)
BUILD_DIR=${THIS_DIR}/build/linux
INSTALL_DIR=${THIS_DIR}/build/linux-install
CMAKE_GENERATOR="Unix Makefiles"

rm -rf ${BUILD_DIR}
rm -rf ${INSTALL_DIR}
mkdir -p ${BUILD_DIR}
mkdir -p ${INSTALL_DIR}

pushd ${BUILD_DIR}

conan install \
    --generator cmake_find_package \
    --settings build_type=Debug \
    --build missing \
    ${THIS_DIR}

cmake \
    -G "${CMAKE_GENERATOR}" \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} \
    -DCMAKE_BUILD_TYPE=Debug \
    ${THIS_DIR}

popd
