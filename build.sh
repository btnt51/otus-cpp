mkdir ./build
cd ./build
cmake -DPATCH_VERSION=$1 -DBUILDING_TESTS=$2 ../
cmake --build .
cmake --build . --target $3