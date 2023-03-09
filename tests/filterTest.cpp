#include "Filter.hpp"
#include <filesystem>
#include <gtest/gtest.h>
#include <vector>


TEST(FileFilters, TrueDefaultSet) {
    FileFilter filter;
    ASSERT_TRUE(filter.isValid("tests/data/file.txt"));
}

TEST(FileFilter, TrueWithNormalRegular) {
    FileFilter filter("file");
    ASSERT_TRUE(filter.isValid("tests/data/file.txt"));
}

TEST(FileFilter, TrueWithNormalRegularAndFileSize) {
    FileFilter filter("[a-z]*.txt", fs::file_size("tests/data/file.txt"));
    ASSERT_FALSE(filter.isValid("tests/data/file.txt"));
}

TEST(FileFilter, FalseWithNormalRegularAndFileSize) {
    FileFilter filter("[a-z]*.txt", fs::file_size("tests/data/file.txt")+15);
    ASSERT_FALSE(filter.isValid("tests/data/file.txt"));
}

TEST(DirFilter, TrueDefaultTrueSet) {
    DirFilter filter;
    ScanPath path = std::make_pair("tests", 0);
    ASSERT_TRUE(filter.isValid(path));
}

TEST(DirFilter, TrueWithExcludeDirs) {
    std::vector<Path> exc = {""};
    DirFilter filter(exc);
    ScanPath path = std::make_pair("tests", 0);
    ASSERT_TRUE(filter.isValid(path));
}

TEST(DirFilter, TrueWithExcludeDirsAndDepth) {
    ScanPath path = std::make_pair("tests/data", 1);
    std::vector<Path> exc = {"tests"};
    DirFilter filter(exc, 1);
    ASSERT_TRUE(filter.isValid(path));
}

TEST(DirFilter, FalseWithExcludeDirs) {
    std::vector<Path> exc = {"tests"};
    DirFilter filter(exc);
    ScanPath path = std::make_pair("tests", 0);
    ASSERT_FALSE(filter.isValid(path));
}

TEST(DirFilter, FalseWithExcludeDirsAndDepth) {
    ScanPath path = std::make_pair("tests/data", 1);
    std::vector<Path> exc = {"tests"};
    DirFilter filter(exc, 0);
    ASSERT_FALSE(filter.isValid(path));
}