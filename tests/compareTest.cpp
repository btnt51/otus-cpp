#include <exception>
#include <gtest/gtest.h>

#include "File.hpp"


TEST(File, TrueFileCompare) {
    File a("tests/data/file.txt");
    File b("tests/data/filec.txt");
    ASSERT_TRUE(File::compareFiles(a, b, "SHA1"));
}

TEST(File, FalseFileCompare) {
    try {
        File a("tests/data/file.txt");
        File b("tests/data/file3.txt");
        ASSERT_FALSE(File::compareFiles(a, b, "SHA1"));
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

TEST(File, TrueFile2Comapares) {
    File a("tests/data/file.txt");
    File b("tests/data/file2.txt");
    File c("tests/data/filec.txt");
    ASSERT_FALSE(File::compareFiles(a, b, "SHA1"));
    ASSERT_TRUE(File::compareFiles(a, c, "SHA1"));
}

