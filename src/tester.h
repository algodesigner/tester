/*
 * Tester v0.1
 * A miniature unit testing framework for C. Interface definition.
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

#ifndef TESTER_H_
#define TESTER_H_

#include <stdbool.h>

typedef struct tester_s tester;

/**
 * Creates a new instance of this tester class. The newly created object can
 * only be used for a single test run and cannot be reset or recycled.
 *
 * @param fp file pointer to be used to output of the testing progress (test
 *        logs)and the test report; can be NULL if output is not required.
 * @param only_failures true to only report failures as the testing progresses;
 *        false will cause all test cases to be logged.
 * @return a new instance of tester or NULL in case of an error.
 */
tester *tester_create(FILE *fp, bool only_failures);

/**
 * Registers a new group of tests with this tester. The testing groups are
 * separated out in the test logs. All the subsequent tests will be reported
 * under the new group until the next one is created.
 *
 * @param obj a tester object.
 * @param name the new group name; can be NULL (in which case the group header
 *        may or may not be printed in the test logs).
 *
 */
void tester_new_group(tester *obj, const char *name);

/**
 * Tests the specified expression.
 *
 * @param obj a tester object.
 * @param exp an assertion to be tested.
 * @param name the name of this test assertion; can be NULL.
 */
#define tester_assert(obj, exp, name) \
        tester_test(obj, exp, name, #exp, __FILE__, __LINE__);

/**
 * Tests the specified expression. This method is expected to be used in test
 * frameworks. For regular test cases, please use tester_assert macro.
 *
 * @param obj a tester object.
 * @param exp an assertion to be tested.
 * @param name the name of this test assertion; can be NULL.
 * @param exp_str the string value of the assertion expression.
 * @param file the name of the source file from which this method is called.
 * @param line the line number of this assertion call in the source file.
 */
void tester_test(tester *obj, bool exp, const char *name, const char *exp_str,
        const char *file, int line);

/**
 * Returns the current testing result. This method is typically called once,
 * at the end of the test run. However, if needed, it can be called multiple
 * times as testing progresses.
 *
 * @return true if and only all the tests passed so far and false if at least
 *         one of them has failed.
 */
bool tester_result(tester *obj);

/**
 * Causes the test report to be finalised and the output buffer flushed if the
 * file pointer provided in the constructor is not NULL and finally destroys
 * the specified tester object.
 *
 * @param obj an object to be destructed; NULL will cause no action to be taken.
 */
void tester_destroy(tester *obj);

#endif
