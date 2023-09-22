#include "6502/memory.h"
#include "test.h"

int main() {
    INIT_TESTS();
    memory_t memory;

    START_TESTCASE("Memory write.");

    write_memory(&memory, 0, 1);
    ASSERT_MSG(memory.data[0] == 1, "Write failed.");
    write_memory(&memory, 10, 1);
    ASSERT_MSG(memory.data[10] == 1, "Write failed.");
    write_memory(&memory, 11, 1);
    ASSERT_MSG(memory.data[11] == 1, "Write failed.");
    write_memory(&memory, 15, 1);
    ASSERT_MSG(memory.data[15] == 1, "Write failed.");
    write_memory(&memory, 455, 1);
    ASSERT_MSG(memory.data[455] == 1, "Write failed.");

    END_TESTCASE();

    START_TESTCASE("Memory read.");

    ASSERT_MSG(read_memory(&memory, 0) == 1, "Read failed.");
    ASSERT_MSG(read_memory(&memory, 10) == 1, "Read failed.");
    ASSERT_MSG(read_memory(&memory, 11) == 1, "Read failed.");
    ASSERT_MSG(read_memory(&memory, 15) == 1, "Read failed.");
    ASSERT_MSG(read_memory(&memory, 455) == 1, "Read failed.");

    END_TESTCASE();

    init_memory(&memory);

    START_TESTCASE("Memory init.");

    ASSERT_MSG(read_memory(&memory, 0) == 0, "Read failed.");
    ASSERT_MSG(read_memory(&memory, 10) == 0, "Read failed.");
    ASSERT_MSG(read_memory(&memory, 11) == 0, "Read failed.");
    ASSERT_MSG(read_memory(&memory, 15) == 0, "Read failed.");
    ASSERT_MSG(read_memory(&memory, 455) == 0, "Read failed.");

    END_TESTCASE();

    END_TESTS();
}