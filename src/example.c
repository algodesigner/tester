/*
 * Tester v0.1
 * A sample application using the framework.
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2013-2019, Vlad Shurupov
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tester.h"

static void test_lifecycle(tester *tst)
{
    tester_new_group(tst, "Life Cycle Tests");
    tester *t, *t2;

    t = tester_create(NULL, true);
    tester_assert(tst, t, "tester instantiation");
    t2 = tester_create(NULL, true);
    tester_assert(tst, t != t2, "unique identity check");

    tester_destroy(t);
    tester_destroy(t2);
}

static void test_assertions(tester *tst)
{
    tester_new_group(tst, "Assertion Tests");
    tester *t;
    t = tester_create(NULL, true);

    tester_assert(tst, tst, "tester validity");
    tester_assert(tst, 1, "1 is true");
    tester_assert(tst, true, NULL);

    tester_assert(tst, !!true, "!!true == true");
    tester_assert(tst, !0 == 1, "!0 == 1");
    tester_assert(tst, 0 ^ 1, "0 ^ 1 == 1");

    /* Test a negative assertion and evaluate t result */
    tester_assert(t, NAN == NAN, "NAN == NAN with t");
    tester_assert(tst, !tester_result(t), "t returns false");

    tester_destroy(t);
}

static void test_results(tester *tst)
{
    tester_new_group(tst, "Final Result Tests");
    tester_assert(tst, tester_result(tst), "positive result");
}

int main(void)
{
    tester *tst;
    tst = tester_create(stdout, false);

    test_lifecycle(tst);
    test_assertions(tst);
    test_results(tst);

    tester_destroy(tst);
    return EXIT_SUCCESS;
}
