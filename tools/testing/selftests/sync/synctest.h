<शैली गुरु>
/*
 *  sync tests
 *  Copyright 2015-2016 Collabora Ltd.
 *
 *  Based on the implementation from the Android Open Source Project,
 *
 *  Copyright 2012 Google, Inc
 *
 *  Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 *  copy of this software and associated करोcumentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to करो so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित SELFTESTS_SYNCTEST_H
#घोषणा SELFTESTS_SYNCTEST_H

#समावेश <मानकपन.स>
#समावेश "../kselftest.h"

#घोषणा ASSERT(cond, msg) करो अणु \
	अगर (!(cond)) अणु \
		ksft_prपूर्णांक_msg("[ERROR]\t%s", (msg)); \
		वापस 1; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा RUN_TEST(x) run_test((x), #x)

/* Allocation tests */
पूर्णांक test_alloc_समयline(व्योम);
पूर्णांक test_alloc_fence(व्योम);
पूर्णांक test_alloc_fence_negative(व्योम);

/* Fence tests with one समयline */
पूर्णांक test_fence_one_समयline_रुको(व्योम);
पूर्णांक test_fence_one_समयline_merge(व्योम);

/* Fence merge tests */
पूर्णांक test_fence_merge_same_fence(व्योम);

/* Fence रुको tests */
पूर्णांक test_fence_multi_समयline_रुको(व्योम);

/* Stress test - parallelism */
पूर्णांक test_stress_two_thपढ़ोs_shared_समयline(व्योम);

/* Stress test - consumer */
पूर्णांक test_consumer_stress_multi_producer_single_consumer(व्योम);

/* Stress test - merging */
पूर्णांक test_merge_stress_अक्रमom_merge(व्योम);

#पूर्ण_अगर
