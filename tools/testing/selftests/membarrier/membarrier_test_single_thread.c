<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <linux/membarrier.h>
#समावेश <syscall.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>

#समावेश "membarrier_test_impl.h"

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	ksft_prपूर्णांक_header();
	ksft_set_plan(13);

	test_membarrier_query();

	test_membarrier_fail();

	test_membarrier_success();

	वापस ksft_निकास_pass();
पूर्ण
