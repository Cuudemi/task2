#include "test_load.h"
#include "test_move.h"
#include "test_mwbb.h"
#include "test_rc.h"
#include "test_save.h"
#include "test_sne.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
