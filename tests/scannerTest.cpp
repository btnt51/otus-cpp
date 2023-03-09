#include <gtest/gtest.h>
#include <utility>


#include "Scanner.hpp"

TEST(FileScanner, TrueDefault) {
    std::set<Path> rightResults;
    rightResults.insert("tests/file.txt");
    rightResults.insert("tests/file2.txt");


    FileScanner fileScanner;
    std::vector<Path> searchDirs = {"tests"};
    ASSERT_EQ(fileScanner.validatePathes(searchDirs), rightResults);
}

TEST(FileScanner, FalseDefault) {
    std::set<Path> rightResults;
    rightResults.insert("tests/data/file.txt");
    rightResults.insert("tests/data/file2.txt");
    rightResults.insert("tests/data/file3.txt");

    FileScanner fileScanner;
    std::vector<Path> searchDirs = {"tests/data"};
    ASSERT_NE(fileScanner.validatePathes(searchDirs), rightResults);
}

TEST(FileScanner, TrueWithExcludeDirs) {
    std::set<Path> rightResults;
    rightResults.insert("tests/file.txt");
    rightResults.insert("tests/file2.txt");

    FileScanner fileScanner(std::vector<Path>{"tests/data"});
    std::vector<Path> searchDirs = {"tests"};
    ASSERT_EQ(fileScanner.validatePathes(searchDirs), rightResults);
}

TEST(FileScanner, TrueWithExcludeDirsAndRegex) {
    std::set<Path> rightResults;
    rightResults.insert("tests/file.txt");

    FileScanner fileScanner(std::vector<Path>{"tests/data"}, "file");
    std::vector<Path> searchDirs = {"tests"};
    ASSERT_EQ(fileScanner.validatePathes(searchDirs), rightResults);
}

TEST(FileScanner, TrueWithExcludeDirsRegexAndDepth) {
    std::set<Path> rightResults;
    rightResults.insert("tests/file.txt");
    rightResults.insert("tests/another folder/file.txt");

    FileScanner fileScanner(std::vector<Path>{"tests/data"}, 
    "file", 1);
    std::vector<Path> searchDirs = {"tests"};
    ASSERT_EQ(fileScanner.validatePathes(searchDirs), rightResults);
}

TEST(FileScanner, TrueWithExcludeDirsRegexDepthAndSizeOfFile) {
    std::set<Path> rightResults;
    rightResults.insert("tests/file.txt");
    rightResults.insert("tests/another folder/file.txt");

    FileScanner fileScanner(std::vector<Path>{"tests/data"}, 
    "file", 1, 11);
    std::vector<Path> searchDirs = {"tests"};
    ASSERT_EQ(fileScanner.validatePathes(searchDirs), rightResults);
}

TEST(FileScanner, TrueWithExcludeDirsRegexSecondDepthAndSizeOfFile) {
    std::set<Path> rightResults;
    rightResults.insert("tests/file.txt");
    rightResults.insert("tests/another folder/file.txt");
    rightResults.insert("tests/another folder/423321/file.txt");

    FileScanner fileScanner(std::vector<Path>{"tests/data"}, 
    "file", 2, 11);
    std::vector<Path> searchDirs = {"tests"};
    ASSERT_EQ(fileScanner.validatePathes(searchDirs), rightResults);
}

TEST(DuplicateScanner, TrueDefault) {
    std::vector<std::pair<Path, std::set<Path> > > rightResults;
    std::set<Path> tempPath;
    tempPath.insert("tests/data/filec.txt");
    rightResults.push_back(std::make_pair("tests/data/file.txt", tempPath));


    FileScanner fileScanner;
    std::vector<Path> searchDirs = {"tests/data"};
    auto files = fileScanner.validatePathes(searchDirs);
    DuplicateScanner dup(files, "SHA1");
    ASSERT_EQ(dup.checkFiles(), rightResults);
}
