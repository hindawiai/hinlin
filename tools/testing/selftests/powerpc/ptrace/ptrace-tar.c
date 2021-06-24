<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ptrace test क्रम TAR, PPR, DSCR रेजिस्टरs
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#समावेश "ptrace.h"
#समावेश "ptrace-tar.h"

/* Tracer and Tracee Shared Data */
पूर्णांक shm_id;
पूर्णांक *cptr;
पूर्णांक *pptr;

व्योम tar(व्योम)
अणु
	अचिन्हित दीर्घ reg[3];
	पूर्णांक ret;

	cptr = (पूर्णांक *)shmat(shm_id, शून्य, 0);
	म_लिखो("%-30s TAR: %u PPR: %lx DSCR: %u\n",
			user_ग_लिखो, TAR_1, PPR_1, DSCR_1);

	mtspr(SPRN_TAR, TAR_1);
	mtspr(SPRN_PPR, PPR_1);
	mtspr(SPRN_DSCR, DSCR_1);

	cptr[2] = 1;

	/* Wait on parent */
	जबतक (!cptr[0])
		यंत्र अस्थिर("" : : : "memory");

	reg[0] = mfspr(SPRN_TAR);
	reg[1] = mfspr(SPRN_PPR);
	reg[2] = mfspr(SPRN_DSCR);

	म_लिखो("%-30s TAR: %lu PPR: %lx DSCR: %lu\n",
			user_पढ़ो, reg[0], reg[1], reg[2]);

	/* Unblock the parent now */
	cptr[1] = 1;
	shmdt((पूर्णांक *)cptr);

	ret = validate_tar_रेजिस्टरs(reg, TAR_2, PPR_2, DSCR_2);
	अगर (ret)
		निकास(1);
	निकास(0);
पूर्ण

पूर्णांक trace_tar(pid_t child)
अणु
	अचिन्हित दीर्घ reg[3];

	FAIL_IF(start_trace(child));
	FAIL_IF(show_tar_रेजिस्टरs(child, reg));
	म_लिखो("%-30s TAR: %lu PPR: %lx DSCR: %lu\n",
			ptrace_पढ़ो_running, reg[0], reg[1], reg[2]);

	FAIL_IF(validate_tar_रेजिस्टरs(reg, TAR_1, PPR_1, DSCR_1));
	FAIL_IF(stop_trace(child));
	वापस TEST_PASS;
पूर्ण

पूर्णांक trace_tar_ग_लिखो(pid_t child)
अणु
	FAIL_IF(start_trace(child));
	FAIL_IF(ग_लिखो_tar_रेजिस्टरs(child, TAR_2, PPR_2, DSCR_2));
	म_लिखो("%-30s TAR: %u PPR: %lx DSCR: %u\n",
			ptrace_ग_लिखो_running, TAR_2, PPR_2, DSCR_2);

	FAIL_IF(stop_trace(child));
	वापस TEST_PASS;
पूर्ण

पूर्णांक ptrace_tar(व्योम)
अणु
	pid_t pid;
	पूर्णांक ret, status;

	// TAR was added in v2.07
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));

	shm_id = shmget(IPC_PRIVATE, माप(पूर्णांक) * 3, 0777|IPC_CREAT);
	pid = विभाजन();
	अगर (pid < 0) अणु
		लिखो_त्रुटि("fork() failed");
		वापस TEST_FAIL;
	पूर्ण

	अगर (pid == 0)
		tar();

	अगर (pid) अणु
		pptr = (पूर्णांक *)shmat(shm_id, शून्य, 0);
		pptr[0] = 0;
		pptr[1] = 0;

		जबतक (!pptr[2])
			यंत्र अस्थिर("" : : : "memory");
		ret = trace_tar(pid);
		अगर (ret)
			वापस ret;

		ret = trace_tar_ग_लिखो(pid);
		अगर (ret)
			वापस ret;

		/* Unblock the child now */
		pptr[0] = 1;

		/* Wait on child */
		जबतक (!pptr[1])
			यंत्र अस्थिर("" : : : "memory");

		shmdt((पूर्णांक *)pptr);

		ret = रुको(&status);
		shmctl(shm_id, IPC_RMID, शून्य);
		अगर (ret != pid) अणु
			म_लिखो("Child's exit status not captured\n");
			वापस TEST_PASS;
		पूर्ण

		वापस (WIFEXITED(status) && WEXITSTATUS(status)) ? TEST_FAIL :
			TEST_PASS;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(ptrace_tar, "ptrace_tar");
पूर्ण
