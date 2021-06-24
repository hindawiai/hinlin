<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <pthपढ़ो.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <sys/auxv.h>
#समावेश <sys/mman.h>
#समावेश <sys/prctl.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>

#समावेश "kselftest.h"
#समावेश "mte_common_util.h"

#घोषणा PR_SET_TAGGED_ADDR_CTRL 55
#घोषणा PR_GET_TAGGED_ADDR_CTRL 56
# define PR_TAGGED_ADDR_ENABLE  (1UL << 0)
# define PR_MTE_TCF_SHIFT	1
# define PR_MTE_TCF_NONE	(0UL << PR_MTE_TCF_SHIFT)
# define PR_MTE_TCF_SYNC	(1UL << PR_MTE_TCF_SHIFT)
# define PR_MTE_TCF_ASYNC	(2UL << PR_MTE_TCF_SHIFT)
# define PR_MTE_TCF_MASK	(3UL << PR_MTE_TCF_SHIFT)
# define PR_MTE_TAG_SHIFT	3
# define PR_MTE_TAG_MASK	(0xffffUL << PR_MTE_TAG_SHIFT)

#समावेश "mte_def.h"

#घोषणा NUM_ITERATIONS		1024
#घोषणा MAX_THREADS		5
#घोषणा THREAD_ITERATIONS	1000

व्योम *execute_thपढ़ो(व्योम *x)
अणु
	pid_t pid = *((pid_t *)x);
	pid_t tid = gettid();
	uपूर्णांक64_t prctl_tag_mask;
	uपूर्णांक64_t prctl_set;
	uपूर्णांक64_t prctl_get;
	uपूर्णांक64_t prctl_tcf;

	बेक्रम(समय(शून्य) ^ (pid << 16) ^ (tid << 16));

	prctl_tag_mask = अक्रम() & 0xffff;

	अगर (prctl_tag_mask % 2)
		prctl_tcf = PR_MTE_TCF_SYNC;
	अन्यथा
		prctl_tcf = PR_MTE_TCF_ASYNC;

	prctl_set = PR_TAGGED_ADDR_ENABLE | prctl_tcf | (prctl_tag_mask << PR_MTE_TAG_SHIFT);

	क्रम (पूर्णांक j = 0; j < THREAD_ITERATIONS; j++) अणु
		अगर (prctl(PR_SET_TAGGED_ADDR_CTRL, prctl_set, 0, 0, 0)) अणु
			लिखो_त्रुटि("prctl() failed");
			जाओ fail;
		पूर्ण

		prctl_get = prctl(PR_GET_TAGGED_ADDR_CTRL, 0, 0, 0, 0);

		अगर (prctl_set != prctl_get) अणु
			ksft_prपूर्णांक_msg("Error: prctl_set: 0x%lx != prctl_get: 0x%lx\n",
						prctl_set, prctl_get);
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस (व्योम *)KSFT_PASS;

fail:
	वापस (व्योम *)KSFT_FAIL;
पूर्ण

पूर्णांक execute_test(pid_t pid)
अणु
	pthपढ़ो_t thपढ़ो_id[MAX_THREADS];
	पूर्णांक thपढ़ो_data[MAX_THREADS];

	क्रम (पूर्णांक i = 0; i < MAX_THREADS; i++)
		pthपढ़ो_create(&thपढ़ो_id[i], शून्य,
			       execute_thपढ़ो, (व्योम *)&pid);

	क्रम (पूर्णांक i = 0; i < MAX_THREADS; i++)
		pthपढ़ो_join(thपढ़ो_id[i], (व्योम *)&thपढ़ो_data[i]);

	क्रम (पूर्णांक i = 0; i < MAX_THREADS; i++)
		अगर (thपढ़ो_data[i] == KSFT_FAIL)
			वापस KSFT_FAIL;

	वापस KSFT_PASS;
पूर्ण

पूर्णांक mte_gcr_विभाजन_test(व्योम)
अणु
	pid_t pid;
	पूर्णांक results[NUM_ITERATIONS];
	pid_t cpid;
	पूर्णांक res;

	क्रम (पूर्णांक i = 0; i < NUM_ITERATIONS; i++) अणु
		pid = विभाजन();

		अगर (pid < 0)
			वापस KSFT_FAIL;

		अगर (pid == 0) अणु
			cpid = getpid();

			res = execute_test(cpid);

			निकास(res);
		पूर्ण
	पूर्ण

	क्रम (पूर्णांक i = 0; i < NUM_ITERATIONS; i++) अणु
		रुको(&res);

		अगर (WIFEXITED(res))
			results[i] = WEXITSTATUS(res);
		अन्यथा
			--i;
	पूर्ण

	क्रम (पूर्णांक i = 0; i < NUM_ITERATIONS; i++)
		अगर (results[i] == KSFT_FAIL)
			वापस KSFT_FAIL;

	वापस KSFT_PASS;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक err;

	err = mte_शेष_setup();
	अगर (err)
		वापस err;

	ksft_set_plan(1);

	evaluate_test(mte_gcr_विभाजन_test(),
		"Verify that GCR_EL1 is set correctly on context switch\n");

	mte_restore_setup();
	ksft_prपूर्णांक_cnts();

	वापस ksft_get_fail_cnt() == 0 ? KSFT_PASS : KSFT_FAIL;
पूर्ण
