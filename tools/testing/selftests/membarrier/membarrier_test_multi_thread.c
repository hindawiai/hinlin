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

अटल पूर्णांक thपढ़ो_पढ़ोy, thपढ़ो_quit;
अटल pthपढ़ो_mutex_t test_membarrier_thपढ़ो_mutex =
	PTHREAD_MUTEX_INITIALIZER;
अटल pthपढ़ो_cond_t test_membarrier_thपढ़ो_cond =
	PTHREAD_COND_INITIALIZER;

व्योम *test_membarrier_thपढ़ो(व्योम *arg)
अणु
	pthपढ़ो_mutex_lock(&test_membarrier_thपढ़ो_mutex);
	thपढ़ो_पढ़ोy = 1;
	pthपढ़ो_cond_broadcast(&test_membarrier_thपढ़ो_cond);
	pthपढ़ो_mutex_unlock(&test_membarrier_thपढ़ो_mutex);

	pthपढ़ो_mutex_lock(&test_membarrier_thपढ़ो_mutex);
	जबतक (!thपढ़ो_quit)
		pthपढ़ो_cond_रुको(&test_membarrier_thपढ़ो_cond,
				  &test_membarrier_thपढ़ो_mutex);
	pthपढ़ो_mutex_unlock(&test_membarrier_thपढ़ो_mutex);

	वापस शून्य;
पूर्ण

अटल पूर्णांक test_mt_membarrier(व्योम)
अणु
	पूर्णांक i;
	pthपढ़ो_t test_thपढ़ो;

	pthपढ़ो_create(&test_thपढ़ो, शून्य,
		       test_membarrier_thपढ़ो, शून्य);

	pthपढ़ो_mutex_lock(&test_membarrier_thपढ़ो_mutex);
	जबतक (!thपढ़ो_पढ़ोy)
		pthपढ़ो_cond_रुको(&test_membarrier_thपढ़ो_cond,
				  &test_membarrier_thपढ़ो_mutex);
	pthपढ़ो_mutex_unlock(&test_membarrier_thपढ़ो_mutex);

	test_membarrier_fail();

	test_membarrier_success();

	pthपढ़ो_mutex_lock(&test_membarrier_thपढ़ो_mutex);
	thपढ़ो_quit = 1;
	pthपढ़ो_cond_broadcast(&test_membarrier_thपढ़ो_cond);
	pthपढ़ो_mutex_unlock(&test_membarrier_thपढ़ो_mutex);

	pthपढ़ो_join(test_thपढ़ो, शून्य);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	ksft_prपूर्णांक_header();
	ksft_set_plan(13);

	test_membarrier_query();

	/* Multi-thपढ़ोed */
	test_mt_membarrier();

	वापस ksft_निकास_pass();
पूर्ण
