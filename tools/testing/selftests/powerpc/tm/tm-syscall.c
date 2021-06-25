<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015, Sam Bobroff, IBM Corp.
 *
 * Test the kernel's प्रणाली call code to ensure that a प्रणाली call
 * made from within an active HTM transaction is पातed with the
 * correct failure code.
 * Conversely, ensure that a प्रणाली call made from within a
 * suspended transaction can succeed.
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <यंत्र/पंचांग.h>
#समावेश <sys/समय.स>
#समावेश <मानककोष.स>

#समावेश "utils.h"
#समावेश "tm.h"

बाह्य पूर्णांक getppid_पंचांग_active(व्योम);
बाह्य पूर्णांक getppid_पंचांग_suspended(व्योम);

अचिन्हित retries = 0;

#घोषणा TEST_DURATION 10 /* seconds */
#घोषणा TM_RETRIES 100

pid_t getppid_पंचांग(bool suspend)
अणु
	पूर्णांक i;
	pid_t pid;

	क्रम (i = 0; i < TM_RETRIES; i++) अणु
		अगर (suspend)
			pid = getppid_पंचांग_suspended();
		अन्यथा
			pid = getppid_पंचांग_active();

		अगर (pid >= 0)
			वापस pid;

		अगर (failure_is_persistent()) अणु
			अगर (failure_is_syscall())
				वापस -1;

			म_लिखो("Unexpected persistent transaction failure.\n");
			म_लिखो("TEXASR 0x%016lx, TFIAR 0x%016lx.\n",
			       __builtin_get_texasr(), __builtin_get_tfiar());
			निकास(-1);
		पूर्ण

		retries++;
	पूर्ण

	म_लिखो("Exceeded limit of %d temporary transaction failures.\n", TM_RETRIES);
	म_लिखो("TEXASR 0x%016lx, TFIAR 0x%016lx.\n",
	       __builtin_get_texasr(), __builtin_get_tfiar());

	निकास(-1);
पूर्ण

पूर्णांक पंचांग_syscall(व्योम)
अणु
	अचिन्हित count = 0;
	काष्ठा समयval end, now;

	SKIP_IF(!have_hपंचांग_nosc());

	रखो_बफ(मानक_निकास, शून्य);

	म_लिखो("Testing transactional syscalls for %d seconds...\n", TEST_DURATION);

	समय_लोofday(&end, शून्य);
	now.tv_sec = TEST_DURATION;
	now.tv_usec = 0;
	समयradd(&end, &now, &end);

	क्रम (count = 0; समयrcmp(&now, &end, <); count++) अणु
		/*
		 * Test a syscall within a suspended transaction and verअगरy
		 * that it succeeds.
		 */
		FAIL_IF(getppid_पंचांग(true) == -1); /* Should succeed. */

		/*
		 * Test a syscall within an active transaction and verअगरy that
		 * it fails with the correct failure code.
		 */
		FAIL_IF(getppid_पंचांग(false) != -1);  /* Should fail... */
		FAIL_IF(!failure_is_persistent()); /* ...persistently... */
		FAIL_IF(!failure_is_syscall());    /* ...with code syscall. */
		समय_लोofday(&now, 0);
	पूर्ण

	म_लिखो("%d active and suspended transactions behaved correctly.\n", count);
	म_लिखो("(There were %d transaction retries.)\n", retries);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(पंचांग_syscall, "tm_syscall");
पूर्ण
