<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ptrace test TM SPR रेजिस्टरs
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#समावेश "ptrace.h"
#समावेश "tm.h"

/* Tracee and tracer shared data */
काष्ठा shared अणु
	पूर्णांक flag;
	काष्ठा पंचांग_spr_regs regs;
पूर्ण;
अचिन्हित दीर्घ tfhar;

पूर्णांक shm_id;
काष्ठा shared *cptr, *pptr;

पूर्णांक shm_id1;
पूर्णांक *cptr1, *pptr1;

#घोषणा TM_KVM_SCHED   0xe0000001ac000001
पूर्णांक validate_पंचांग_spr(काष्ठा पंचांग_spr_regs *regs)
अणु
	FAIL_IF(regs->पंचांग_tfhar != tfhar);
	FAIL_IF((regs->पंचांग_texasr == TM_KVM_SCHED) && (regs->पंचांग_tfiar != 0));

	वापस TEST_PASS;
पूर्ण

व्योम पंचांग_spr(व्योम)
अणु
	अचिन्हित दीर्घ result, texasr;
	पूर्णांक ret;

	cptr = (काष्ठा shared *)shmat(shm_id, शून्य, 0);
	cptr1 = (पूर्णांक *)shmat(shm_id1, शून्य, 0);

trans:
	cptr1[0] = 0;
	यंत्र __अस्थिर__(
		"1: ;"
		/* TM failover handler should follow "tbegin.;" */
		"mflr 31;"
		"bl 4f;"	/* $ = TFHAR - 12 */
		"4: ;"
		"mflr %[tfhar];"
		"mtlr 31;"

		"tbegin.;"
		"beq 2f;"

		"tsuspend.;"
		"li 8, 1;"
		"sth 8, 0(%[cptr1]);"
		"tresume.;"
		"b .;"

		"tend.;"
		"li 0, 0;"
		"ori %[res], 0, 0;"
		"b 3f;"

		"2: ;"

		"li 0, 1;"
		"ori %[res], 0, 0;"
		"mfspr %[texasr], %[sprn_texasr];"

		"3: ;"
		: [tfhar] "=r" (tfhar), [res] "=r" (result),
		[texasr] "=r" (texasr), [cptr1] "=b" (cptr1)
		: [sprn_texasr] "i"  (SPRN_TEXASR)
		: "memory", "r0", "r8", "r31"
		);

	/* There are 2 32bit inकाष्ठाions beक्रमe tbegin. */
	tfhar += 12;

	अगर (result) अणु
		अगर (!cptr->flag)
			जाओ trans;

		ret = validate_पंचांग_spr((काष्ठा पंचांग_spr_regs *)&cptr->regs);
		shmdt((व्योम *)cptr);
		shmdt((व्योम *)cptr1);
		अगर (ret)
			निकास(1);
		निकास(0);
	पूर्ण
	shmdt((व्योम *)cptr);
	shmdt((व्योम *)cptr1);
	निकास(1);
पूर्ण

पूर्णांक trace_पंचांग_spr(pid_t child)
अणु
	FAIL_IF(start_trace(child));
	FAIL_IF(show_पंचांग_spr(child, (काष्ठा पंचांग_spr_regs *)&pptr->regs));

	म_लिखो("TFHAR: %lx TEXASR: %lx TFIAR: %lx\n", pptr->regs.पंचांग_tfhar,
				pptr->regs.पंचांग_texasr, pptr->regs.पंचांग_tfiar);

	pptr->flag = 1;
	FAIL_IF(stop_trace(child));

	वापस TEST_PASS;
पूर्ण

पूर्णांक ptrace_पंचांग_spr(व्योम)
अणु
	pid_t pid;
	पूर्णांक ret, status;

	SKIP_IF(!have_hपंचांग());
	shm_id = shmget(IPC_PRIVATE, माप(काष्ठा shared), 0777|IPC_CREAT);
	shm_id1 = shmget(IPC_PRIVATE, माप(पूर्णांक), 0777|IPC_CREAT);
	pid = विभाजन();
	अगर (pid < 0) अणु
		लिखो_त्रुटि("fork() failed");
		वापस TEST_FAIL;
	पूर्ण

	अगर (pid == 0)
		पंचांग_spr();

	अगर (pid) अणु
		pptr = (काष्ठा shared *)shmat(shm_id, शून्य, 0);
		pptr1 = (पूर्णांक *)shmat(shm_id1, शून्य, 0);

		जबतक (!pptr1[0])
			यंत्र अस्थिर("" : : : "memory");
		ret = trace_पंचांग_spr(pid);
		अगर (ret) अणु
			समाप्त(pid, SIGKILL);
			shmdt((व्योम *)pptr);
			shmdt((व्योम *)pptr1);
			shmctl(shm_id, IPC_RMID, शून्य);
			shmctl(shm_id1, IPC_RMID, शून्य);
			वापस TEST_FAIL;
		पूर्ण

		shmdt((व्योम *)pptr);
		shmdt((व्योम *)pptr1);
		ret = रुको(&status);
		shmctl(shm_id, IPC_RMID, शून्य);
		shmctl(shm_id1, IPC_RMID, शून्य);
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
	वापस test_harness(ptrace_पंचांग_spr, "ptrace_tm_spr");
पूर्ण
