<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ptrace test क्रम TAR, PPR, DSCR रेजिस्टरs in the TM Suspend context
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#समावेश "ptrace.h"
#समावेश "tm.h"
#समावेश "ptrace-tar.h"

पूर्णांक shm_id;
पूर्णांक *cptr, *pptr;

__attribute__((used)) व्योम रुको_parent(व्योम)
अणु
	cptr[2] = 1;
	जबतक (!cptr[1])
		यंत्र अस्थिर("" : : : "memory");
पूर्ण

व्योम पंचांग_spd_tar(व्योम)
अणु
	अचिन्हित दीर्घ result, texasr;
	अचिन्हित दीर्घ regs[3];
	पूर्णांक ret;

	cptr = (पूर्णांक *)shmat(shm_id, शून्य, 0);

trans:
	cptr[2] = 0;
	यंत्र __अस्थिर__(
		"li	4, %[tar_1];"
		"mtspr %[sprn_tar],  4;"	/* TAR_1 */
		"li	4, %[dscr_1];"
		"mtspr %[sprn_dscr], 4;"	/* DSCR_1 */
		"or     31,31,31;"		/* PPR_1*/

		"1: ;"
		"tbegin.;"
		"beq 2f;"

		"li	4, %[tar_2];"
		"mtspr %[sprn_tar],  4;"	/* TAR_2 */
		"li	4, %[dscr_2];"
		"mtspr %[sprn_dscr], 4;"	/* DSCR_2 */
		"or     1,1,1;"			/* PPR_2 */

		"tsuspend.;"
		"li	4, %[tar_3];"
		"mtspr %[sprn_tar],  4;"	/* TAR_3 */
		"li	4, %[dscr_3];"
		"mtspr %[sprn_dscr], 4;"	/* DSCR_3 */
		"or     6,6,6;"			/* PPR_3 */
		"bl wait_parent;"
		"tresume.;"

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
		: [sprn_dscr]"i"(SPRN_DSCR),
		[sprn_tar]"i"(SPRN_TAR), [sprn_ppr]"i"(SPRN_PPR),
		[sprn_texasr]"i"(SPRN_TEXASR), [tar_1]"i"(TAR_1),
		[dscr_1]"i"(DSCR_1), [tar_2]"i"(TAR_2), [dscr_2]"i"(DSCR_2),
		[tar_3]"i"(TAR_3), [dscr_3]"i"(DSCR_3)
		: "memory", "r0", "r3", "r4", "r5", "r6", "lr"
		);

	/* TM failed, analyse */
	अगर (result) अणु
		अगर (!cptr[0])
			जाओ trans;

		regs[0] = mfspr(SPRN_TAR);
		regs[1] = mfspr(SPRN_PPR);
		regs[2] = mfspr(SPRN_DSCR);

		shmdt(&cptr);
		म_लिखो("%-30s TAR: %lu PPR: %lx DSCR: %lu\n",
				user_पढ़ो, regs[0], regs[1], regs[2]);

		ret = validate_tar_रेजिस्टरs(regs, TAR_4, PPR_4, DSCR_4);
		अगर (ret)
			निकास(1);
		निकास(0);
	पूर्ण
	shmdt(&cptr);
	निकास(1);
पूर्ण

पूर्णांक trace_पंचांग_spd_tar(pid_t child)
अणु
	अचिन्हित दीर्घ regs[3];

	FAIL_IF(start_trace(child));
	FAIL_IF(show_tar_रेजिस्टरs(child, regs));
	म_लिखो("%-30s TAR: %lu PPR: %lx DSCR: %lu\n",
			ptrace_पढ़ो_running, regs[0], regs[1], regs[2]);

	FAIL_IF(validate_tar_रेजिस्टरs(regs, TAR_3, PPR_3, DSCR_3));
	FAIL_IF(show_पंचांग_checkpoपूर्णांकed_state(child, regs));
	म_लिखो("%-30s TAR: %lu PPR: %lx DSCR: %lu\n",
			ptrace_पढ़ो_ckpt, regs[0], regs[1], regs[2]);

	FAIL_IF(validate_tar_रेजिस्टरs(regs, TAR_1, PPR_1, DSCR_1));
	FAIL_IF(ग_लिखो_ckpt_tar_रेजिस्टरs(child, TAR_4, PPR_4, DSCR_4));
	म_लिखो("%-30s TAR: %u PPR: %lx DSCR: %u\n",
			ptrace_ग_लिखो_ckpt, TAR_4, PPR_4, DSCR_4);

	pptr[0] = 1;
	pptr[1] = 1;
	FAIL_IF(stop_trace(child));
	वापस TEST_PASS;
पूर्ण

पूर्णांक ptrace_पंचांग_spd_tar(व्योम)
अणु
	pid_t pid;
	पूर्णांक ret, status;

	SKIP_IF(!have_hपंचांग());
	shm_id = shmget(IPC_PRIVATE, माप(पूर्णांक) * 3, 0777|IPC_CREAT);
	pid = विभाजन();
	अगर (pid == 0)
		पंचांग_spd_tar();

	pptr = (पूर्णांक *)shmat(shm_id, शून्य, 0);
	pptr[0] = 0;
	pptr[1] = 0;

	अगर (pid) अणु
		जबतक (!pptr[2])
			यंत्र अस्थिर("" : : : "memory");
		ret = trace_पंचांग_spd_tar(pid);
		अगर (ret) अणु
			समाप्त(pid, संक_इति);
			shmdt(&pptr);
			shmctl(shm_id, IPC_RMID, शून्य);
			वापस TEST_FAIL;
		पूर्ण

		shmdt(&pptr);

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
	वापस test_harness(ptrace_पंचांग_spd_tar, "ptrace_tm_spd_tar");
पूर्ण
