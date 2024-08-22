#!/bin/bash

BUILD_DIR=build-tmp

# Function to prompt the user for yes or no
prompt_user() {
    read -p "The folder ${BUILD_DIR} already exists and WILL BE DELETED. Do you want to continue? (yes/no): " yn
    case $yn in
        [Yy]* )
              echo "Proceeding..."
              return
              ;;
          * )
              echo "Aborting..."
              exit 1
              ;;
    esac
}

if [ -d "${BUILD_DIR}" ]; then
  prompt_user
fi

CMAKE_FLAGS="-DBUILD_TESTING=OFF"

rm -rf ${BUILD_DIR}
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
cmake ${CMAKE_FLAGS} -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --target install

cd ..
rm -rf ${BUILD_DIR}
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
cmake ${CMAKE_FLAGS} -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target install
cd ..
rm -rf ${BUILD_DIR}