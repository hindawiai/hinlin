<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ptrace test क्रम GPR/FPR रेजिस्टरs in TM context
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#समावेश "ptrace.h"
#समावेश "ptrace-gpr.h"
#समावेश "tm.h"

/* Tracer and Tracee Shared Data */
पूर्णांक shm_id;
अचिन्हित दीर्घ *cptr, *pptr;

भग्न a = FPR_1;
भग्न b = FPR_2;
भग्न c = FPR_3;

व्योम पंचांग_gpr(व्योम)
अणु
	अचिन्हित दीर्घ gpr_buf[18];
	अचिन्हित दीर्घ result, texasr;
	भग्न fpr_buf[32];

	म_लिखो("Starting the child\n");
	cptr = (अचिन्हित दीर्घ *)shmat(shm_id, शून्य, 0);

trans:
	cptr[1] = 0;
	यंत्र __अस्थिर__(
		ASM_LOAD_GPR_IMMED(gpr_1)
		ASM_LOAD_FPR_SINGLE_PRECISION(flt_1)
		"1: ;"
		"tbegin.;"
		"beq 2f;"
		ASM_LOAD_GPR_IMMED(gpr_2)
		ASM_LOAD_FPR_SINGLE_PRECISION(flt_2)
		"tsuspend.;"
		"li 7, 1;"
		"stw 7, 0(%[cptr1]);"
		"tresume.;"
		"b .;"

		"tend.;"
		"li 0, 0;"
		"ori %[res], 0, 0;"
		"b 3f;"

		/* Transaction पात handler */
		"2: ;"
		"li 0, 1;"
		"ori %[res], 0, 0;"
		"mfspr %[texasr], %[sprn_texasr];"

		"3: ;"
		: [res] "=r" (result), [texasr] "=r" (texasr)
		: [gpr_1]"i"(GPR_1), [gpr_2]"i"(GPR_2),
		[sprn_texasr] "i" (SPRN_TEXASR), [flt_1] "b" (&a),
		[flt_2] "b" (&b), [cptr1] "b" (&cptr[1])
		: "memory", "r7", "r8", "r9", "r10",
		"r11", "r12", "r13", "r14", "r15", "r16",
		"r17", "r18", "r19", "r20", "r21", "r22",
		"r23", "r24", "r25", "r26", "r27", "r28",
		"r29", "r30", "r31"
		);

	अगर (result) अणु
		अगर (!cptr[0])
			जाओ trans;

		shmdt((व्योम *)cptr);
		store_gpr(gpr_buf);
		store_fpr_single_precision(fpr_buf);

		अगर (validate_gpr(gpr_buf, GPR_3))
			निकास(1);

		अगर (validate_fpr_भग्न(fpr_buf, c))
			निकास(1);

		निकास(0);
	पूर्ण
	shmdt((व्योम *)cptr);
	निकास(1);
पूर्ण

पूर्णांक trace_पंचांग_gpr(pid_t child)
अणु
	अचिन्हित दीर्घ gpr[18];
	अचिन्हित दीर्घ fpr[32];

	FAIL_IF(start_trace(child));
	FAIL_IF(show_gpr(child, gpr));
	FAIL_IF(validate_gpr(gpr, GPR_2));
	FAIL_IF(show_fpr(child, fpr));
	FAIL_IF(validate_fpr(fpr, FPR_2_REP));
	FAIL_IF(show_ckpt_fpr(child, fpr));
	FAIL_IF(validate_fpr(fpr, FPR_1_REP));
	FAIL_IF(show_ckpt_gpr(child, gpr));
	FAIL_IF(validate_gpr(gpr, GPR_1));
	FAIL_IF(ग_लिखो_ckpt_gpr(child, GPR_3));
	FAIL_IF(ग_लिखो_ckpt_fpr(child, FPR_3_REP));

	pptr[0] = 1;
	FAIL_IF(stop_trace(child));

	वापस TEST_PASS;
पूर्ण

पूर्णांक ptrace_पंचांग_gpr(व्योम)
अणु
	pid_t pid;
	पूर्णांक ret, status;

	SKIP_IF(!have_hपंचांग());
	shm_id = shmget(IPC_PRIVATE, माप(पूर्णांक) * 2, 0777|IPC_CREAT);
	pid = विभाजन();
	अगर (pid < 0) अणु
		लिखो_त्रुटि("fork() failed");
		वापस TEST_FAIL;
	पूर्ण
	अगर (pid == 0)
		पंचांग_gpr();

	अगर (pid) अणु
		pptr = (अचिन्हित दीर्घ *)shmat(shm_id, शून्य, 0);

		जबतक (!pptr[1])
			यंत्र अस्थिर("" : : : "memory");
		ret = trace_पंचांग_gpr(pid);
		अगर (ret) अणु
			समाप्त(pid, संक_इति);
			वापस TEST_FAIL;
		पूर्ण

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
	वापस test_harness(ptrace_पंचांग_gpr, "ptrace_tm_gpr");
पूर्ण
