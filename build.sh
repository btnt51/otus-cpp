mkdir ./build
cd ./build
cmake -DPATCH_VERSION=$1 -DWITH_TESTS=$2 -DBoost_INCLUDE_DIR=$4 -DBoost_LIBRARY_DIRS=$5 -DBoost_ROOT=$6 ../
cmake --build .
cmake --build . --target $3

