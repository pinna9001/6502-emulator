#ifndef TESTING_TEST_H
#define TESTING_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    int tests;
    int failedTests;
    char** failedTestNames;
    int capacity;
} TestingTestSuite;

void testingAddFailedTestcase(char* name) {
    char* nameCopy = malloc(strlen(name) + 1);
    strcpy(nameCopy, name);
    if (TestingTestSuite.failedTests + 1 > TestingTestSuite.capacity) {
        int newCapacity = TestingTestSuite.capacity * 2;
        char** newData = realloc(TestingTestSuite.failedTestNames, newCapacity);
        if (!newData) {
            fprintf(stderr, "Couldn't realloc");
            exit(1);
        }
        TestingTestSuite.capacity = newCapacity;
        TestingTestSuite.failedTestNames = newData;
    }
    TestingTestSuite.failedTestNames[TestingTestSuite.failedTests++] = nameCopy;
}

#define LOG_ERROR()                         \
    testingAddFailedTestcase(testCaseName); \
    printf("Failed testcase %d \"%s\" at assert number %d.\n\n", TestingTestSuite.tests, testCaseName, asserts)
#define LOG_ERROR_MSG(errorMsg)             \
    testingAddFailedTestcase(testCaseName); \
    printf("Failed testcase %d \"%s\" at assert number %d with message: \"%s\"\n\n", TestingTestSuite.tests, testCaseName, asserts, errorMsg)
#define LOG_PASSED_ASSERT() printf("Passed assert %d.\n", asserts)
#define LOG_PASSED_TESTCASE() printf("Passed testcase %d \"%s\".\n\n", TestingTestSuite.tests, testCaseName)

#define INIT_TESTS()                  \
    TestingTestSuite.tests = 0;       \
    TestingTestSuite.failedTests = 0; \
    TestingTestSuite.capacity = 8;    \
    TestingTestSuite.failedTestNames = malloc(TestingTestSuite.capacity * sizeof(char*))

#define START_TESTCASE(name)                                                       \
    do {                                                                           \
        printf("Starting testcase %d \"%s\"\n", TestingTestSuite.tests + 1, name); \
        TestingTestSuite.tests++;                                                  \
        int asserts = 1;                                                           \
    char* testCaseName = name

#define ASSERT(value)        \
    if (!(value)) {          \
        LOG_ERROR();         \
        break;               \
    } else {                 \
        LOG_PASSED_ASSERT(); \
    }                        \
    asserts++

#define ASSERT_MSG(value, errorMsg) \
    if (!(value)) {                 \
        LOG_ERROR_MSG(errorMsg);    \
        break;                      \
    } else {                        \
        LOG_PASSED_ASSERT();        \
    }                               \
    asserts++

#define ASSERT_OP(value1, value2, op) \
    if (!((value1)op(value2))) {      \
        LOG_ERROR();                  \
        break;                        \
    } else {                          \
        LOG_PASSED_ASSERT();          \
    }                                 \
    asserts++

#define ASSERT_OP_MSG(value1, value2, op, errorMsg) \
    if (!((value1)op(value2))) {                    \
        LOG_ERROR_MSG(errorMsg);                    \
        break;                                      \
    } else {                                        \
        LOG_PASSED_ASSERT();                        \
    }                                               \
    asserts++

#define END_TESTCASE()     \
    LOG_PASSED_TESTCASE(); \
    }                      \
    while (0)

#define END_TESTS()                                                                                                             \
    printf("----------\nTests passed: %d/%d\n", TestingTestSuite.tests - TestingTestSuite.failedTests, TestingTestSuite.tests); \
    if (TestingTestSuite.failedTests != 0) {                                                                                    \
        printf("Failed Tests:\n");                                                                                              \
    }                                                                                                                           \
    for (int i = 0; i < TestingTestSuite.failedTests; i++) {                                                                    \
        printf("- %s\n", TestingTestSuite.failedTestNames[i]);                                                                  \
        free(TestingTestSuite.failedTestNames[i]);                                                                              \
    }                                                                                                                           \
    free(TestingTestSuite.failedTestNames);                                                                                     \
    return (TestingTestSuite.tests - TestingTestSuite.failedTests) != TestingTestSuite.tests

#endif  // TEST_H