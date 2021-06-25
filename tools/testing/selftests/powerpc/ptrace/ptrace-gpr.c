<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ptrace test क्रम GPR/FPR रेजिस्टरs
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#समावेश "ptrace.h"
#समावेश "ptrace-gpr.h"
#समावेश "reg.h"

/* Tracer and Tracee Shared Data */
पूर्णांक shm_id;
पूर्णांक *cptr, *pptr;

भग्न a = FPR_1;
भग्न b = FPR_2;
भग्न c = FPR_3;

व्योम gpr(व्योम)
अणु
	अचिन्हित दीर्घ gpr_buf[18];
	भग्न fpr_buf[32];

	cptr = (पूर्णांक *)shmat(shm_id, शून्य, 0);

	यंत्र __अस्थिर__(
		ASM_LOAD_GPR_IMMED(gpr_1)
		ASM_LOAD_FPR_SINGLE_PRECISION(flt_1)
		:
		: [gpr_1]"i"(GPR_1), [flt_1] "b" (&a)
		: "memory", "r6", "r7", "r8", "r9", "r10",
		"r11", "r12", "r13", "r14", "r15", "r16", "r17",
		"r18", "r19", "r20", "r21", "r22", "r23", "r24",
		"r25", "r26", "r27", "r28", "r29", "r30", "r31"
		);

	cptr[1] = 1;

	जबतक (!cptr[0])
		यंत्र अस्थिर("" : : : "memory");

	shmdt((व्योम *)cptr);
	store_gpr(gpr_buf);
	store_fpr_single_precision(fpr_buf);

	अगर (validate_gpr(gpr_buf, GPR_3))
		निकास(1);

	अगर (validate_fpr_भग्न(fpr_buf, c))
		निकास(1);

	निकास(0);
पूर्ण

पूर्णांक trace_gpr(pid_t child)
अणु
	अचिन्हित दीर्घ gpr[18];
	अचिन्हित दीर्घ fpr[32];

	FAIL_IF(start_trace(child));
	FAIL_IF(show_gpr(child, gpr));
	FAIL_IF(validate_gpr(gpr, GPR_1));
	FAIL_IF(show_fpr(child, fpr));
	FAIL_IF(validate_fpr(fpr, FPR_1_REP));
	FAIL_IF(ग_लिखो_gpr(child, GPR_3));
	FAIL_IF(ग_लिखो_fpr(child, FPR_3_REP));
	FAIL_IF(stop_trace(child));

	वापस TEST_PASS;
पूर्ण

पूर्णांक ptrace_gpr(व्योम)
अणु
	pid_t pid;
	पूर्णांक ret, status;

	shm_id = shmget(IPC_PRIVATE, माप(पूर्णांक) * 2, 0777|IPC_CREAT);
	pid = विभाजन();
	अगर (pid < 0) अणु
		लिखो_त्रुटि("fork() failed");
		वापस TEST_FAIL;
	पूर्ण
	अगर (pid == 0)
		gpr();

	अगर (pid) अणु
		pptr = (पूर्णांक *)shmat(shm_id, शून्य, 0);
		जबतक (!pptr[1])
			यंत्र अस्थिर("" : : : "memory");

		ret = trace_gpr(pid);
		अगर (ret) अणु
			समाप्त(pid, संक_इति);
			shmdt((व्योम *)pptr);
			shmctl(shm_id, IPC_RMID, शून्य);
			वापस TEST_FAIL;
		पूर्ण

		pptr[0] = 1;
		shmdt((व्योम *)pptr);

		ret = रुको(&status);
		shmctl(shm_id, IPC_RMID, शून्य);
		अगर (ret != pid) अणु
			म_लिखो("Child's exit status not captured\n");
			वापस TEST_FAIL;
		पूर्ण

		वापस (WIFEXITED(status) && WEXITSTATUS(status)) ? TEST_FAIL :
			TEST_PASS;
	पूर्ण

	वापस TEST_PASS;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(ptrace_gpr, "ptrace_gpr");
पूर्ण
