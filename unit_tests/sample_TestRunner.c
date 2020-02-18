/* Copyright (c) 2010 James Grenning and Contributed to Unity Project
 * ==========================================
 *  Unity Project - A Test Framework for C
 *  Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
 *  [Released under MIT License. Please refer to license.txt for details]
 * ========================================== */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(mygroup)
{
    RUN_TEST_CASE(mygroup, test1);
    RUN_TEST_CASE(mygroup, test2);
    RUN_TEST_CASE(mygroup, test3);
}


