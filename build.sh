#!/bin/bash

set -e
set -x

THIS_DIR=$(pwd)

BUILD_DIR=${THIS_DIR}/build/linux
INSTALL_DIR=${THIS_DIR}/build/linux-install

pushd ${BUILD_DIR}

cmake \
    -DCMAKE_BUILD_TYPE=Debug \
    ${THIS_DIR}

cmake \
    --build .

cmake \
    --build . \
    --target unit_tests

cmake \
    --install .

popd

pushd ${INSTALL_DIR}

echo ### Test run ###
./PWServerExe /infile ./inventory.json /outfile ./inventory.json
./PWServerExe /db ./db.json /outfile ./db_out.json

echo ### Test run finished ###

popd

echo ### SUCCESS ###
