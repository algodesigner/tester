/*
 * Tester v0.1
 * A miniature unit testing framework for C. Single file implementation.
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
#include "tester.h"

static const char *passed = "PASSED";
static const char *failed = "FAILED";

struct tester_s {
    FILE *fp;
    int groups;
    int tests;
    int failures;
    bool only_failures;
    bool reported_results;
};

static void fprint_results(tester *);
static void fprint_hline(FILE *, int);

tester *tester_create(FILE *fp, bool only_failures)
{
    tester *obj;
    obj = calloc(1, sizeof(tester));
    if (!obj)
        return NULL;
    obj->fp = fp;
    obj->only_failures = only_failures;
    return obj;
}

void tester_new_group(tester *obj, const char *name)
{
    obj->groups++;
    FILE *fp = obj->fp;
    if (fp) {
        fputc('.', fp);
        fprint_hline(fp, 79);
        fprintf(fp, "| %s\n", name);
        fputc('`', fp);
        fprint_hline(fp, 79);
    }
}

void tester_test(tester *obj, bool exp, const char *name, const char *exp_str,
        const char *file, int line)
{
    const char *result;
    obj->tests++;
    if (exp) {
        result = passed;
    } else {
        result = failed;
        obj->failures++;
    }
    if (obj->fp) {
        if (result == failed || !obj->only_failures)
            fprintf(obj->fp, "Test '%s' %s\n", name, result);
        if (result == failed)
            fprintf(obj->fp, "\tExpression: '%s', file %s, line %d\n", exp_str,
                    file, line);
    }
}

bool tester_result(tester *obj)
{
    return !obj->failures;
}

void tester_destroy(tester *obj)
{
    fprint_results(obj);
    if (obj->fp)
        free(obj);
}

/* Prints test results only once */
static void fprint_results(tester *obj) {
    FILE *fp = obj->fp;
    if (fp && !obj->reported_results) {
        fprint_hline(fp, 80);
        fprintf(fp, ""
                "Test Results\n"
                "Groups:   %d\n"
                "Tests:    %d\n"
                "Failures: %d\n", obj->groups, obj->tests, obj->failures);
        fflush(fp);
        obj->reported_results = true;
    }
}

static void fprint_hline(FILE *fp, int n)
{
    if (!fp)
        return;
    int i;
    for (i = 0; i < n; i++)
        fputc('-', fp);
    fputc('\n', fp);
}
