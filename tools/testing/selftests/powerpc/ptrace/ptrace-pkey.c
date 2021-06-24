<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Ptrace test क्रम Memory Protection Key रेजिस्टरs
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 * Copyright (C) 2018 IBM Corporation.
 */
#समावेश "ptrace.h"
#समावेश "child.h"

#अगर_अघोषित __NR_pkey_alloc
#घोषणा __NR_pkey_alloc		384
#पूर्ण_अगर

#अगर_अघोषित __NR_pkey_मुक्त
#घोषणा __NR_pkey_मुक्त		385
#पूर्ण_अगर

#अगर_अघोषित NT_PPC_PKEY
#घोषणा NT_PPC_PKEY		0x110
#पूर्ण_अगर

#अगर_अघोषित PKEY_DISABLE_EXECUTE
#घोषणा PKEY_DISABLE_EXECUTE	0x4
#पूर्ण_अगर

#घोषणा AMR_BITS_PER_PKEY 2
#घोषणा PKEY_REG_BITS (माप(u64) * 8)
#घोषणा pkeyshअगरt(pkey) (PKEY_REG_BITS - ((pkey + 1) * AMR_BITS_PER_PKEY))

अटल स्थिर अक्षर user_पढ़ो[] = "[User Read (Running)]";
अटल स्थिर अक्षर user_ग_लिखो[] = "[User Write (Running)]";
अटल स्थिर अक्षर ptrace_पढ़ो_running[] = "[Ptrace Read (Running)]";
अटल स्थिर अक्षर ptrace_ग_लिखो_running[] = "[Ptrace Write (Running)]";

/* Inक्रमmation shared between the parent and the child. */
काष्ठा shared_info अणु
	काष्ठा child_sync child_sync;

	/* AMR value the parent expects to पढ़ो from the child. */
	अचिन्हित दीर्घ amr1;

	/* AMR value the parent is expected to ग_लिखो to the child. */
	अचिन्हित दीर्घ amr2;

	/* AMR value that ptrace should refuse to ग_लिखो to the child. */
	अचिन्हित दीर्घ invalid_amr;

	/* IAMR value the parent expects to पढ़ो from the child. */
	अचिन्हित दीर्घ expected_iamr;

	/* UAMOR value the parent expects to पढ़ो from the child. */
	अचिन्हित दीर्घ expected_uamor;

	/*
	 * IAMR and UAMOR values that ptrace should refuse to ग_लिखो to the child
	 * (even though they're valid ones) because userspace doesn't have
	 * access to those रेजिस्टरs.
	 */
	अचिन्हित दीर्घ invalid_iamr;
	अचिन्हित दीर्घ invalid_uamor;
पूर्ण;

अटल पूर्णांक sys_pkey_alloc(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ init_access_rights)
अणु
	वापस syscall(__NR_pkey_alloc, flags, init_access_rights);
पूर्ण

अटल पूर्णांक child(काष्ठा shared_info *info)
अणु
	अचिन्हित दीर्घ reg;
	bool disable_execute = true;
	पूर्णांक pkey1, pkey2, pkey3;
	पूर्णांक ret;

	/* Wait until parent fills out the initial रेजिस्टर values. */
	ret = रुको_parent(&info->child_sync);
	अगर (ret)
		वापस ret;

	/* Get some pkeys so that we can change their bits in the AMR. */
	pkey1 = sys_pkey_alloc(0, PKEY_DISABLE_EXECUTE);
	अगर (pkey1 < 0) अणु
		pkey1 = sys_pkey_alloc(0, 0);
		CHILD_FAIL_IF(pkey1 < 0, &info->child_sync);

		disable_execute = false;
	पूर्ण

	pkey2 = sys_pkey_alloc(0, 0);
	CHILD_FAIL_IF(pkey2 < 0, &info->child_sync);

	pkey3 = sys_pkey_alloc(0, 0);
	CHILD_FAIL_IF(pkey3 < 0, &info->child_sync);

	info->amr1 |= 3ul << pkeyshअगरt(pkey1);
	info->amr2 |= 3ul << pkeyshअगरt(pkey2);
	/*
	 * invalid amr value where we try to क्रमce ग_लिखो
	 * things which are deined by a uamor setting.
	 */
	info->invalid_amr = info->amr2 | (~0x0UL & ~info->expected_uamor);

	/*
	 * अगर PKEY_DISABLE_EXECUTE succeeded we should update the expected_iamr
	 */
	अगर (disable_execute)
		info->expected_iamr |= 1ul << pkeyshअगरt(pkey1);
	अन्यथा
		info->expected_iamr &= ~(1ul << pkeyshअगरt(pkey1));

	/*
	 * We allocated pkey2 and pkey 3 above. Clear the IAMR bits.
	 */
	info->expected_iamr &= ~(1ul << pkeyshअगरt(pkey2));
	info->expected_iamr &= ~(1ul << pkeyshअगरt(pkey3));

	/*
	 * Create an IAMR value dअगरferent from expected value.
	 * Kernel will reject an IAMR and UAMOR change.
	 */
	info->invalid_iamr = info->expected_iamr | (1ul << pkeyshअगरt(pkey1) | 1ul << pkeyshअगरt(pkey2));
	info->invalid_uamor = info->expected_uamor & ~(0x3ul << pkeyshअगरt(pkey1));

	म_लिखो("%-30s AMR: %016lx pkey1: %d pkey2: %d pkey3: %d\n",
	       user_ग_लिखो, info->amr1, pkey1, pkey2, pkey3);

	set_amr(info->amr1);

	/* Wait क्रम parent to पढ़ो our AMR value and ग_लिखो a new one. */
	ret = prod_parent(&info->child_sync);
	CHILD_FAIL_IF(ret, &info->child_sync);

	ret = रुको_parent(&info->child_sync);
	अगर (ret)
		वापस ret;

	reg = mfspr(SPRN_AMR);

	म_लिखो("%-30s AMR: %016lx\n", user_पढ़ो, reg);

	CHILD_FAIL_IF(reg != info->amr2, &info->child_sync);

	/*
	 * Wait क्रम parent to try to ग_लिखो an invalid AMR value.
	 */
	ret = prod_parent(&info->child_sync);
	CHILD_FAIL_IF(ret, &info->child_sync);

	ret = रुको_parent(&info->child_sync);
	अगर (ret)
		वापस ret;

	reg = mfspr(SPRN_AMR);

	म_लिखो("%-30s AMR: %016lx\n", user_पढ़ो, reg);

	CHILD_FAIL_IF(reg != info->amr2, &info->child_sync);

	/*
	 * Wait क्रम parent to try to ग_लिखो an IAMR and a UAMOR value. We can't
	 * verअगरy them, but we can verअगरy that the AMR didn't change.
	 */
	ret = prod_parent(&info->child_sync);
	CHILD_FAIL_IF(ret, &info->child_sync);

	ret = रुको_parent(&info->child_sync);
	अगर (ret)
		वापस ret;

	reg = mfspr(SPRN_AMR);

	म_लिखो("%-30s AMR: %016lx\n", user_पढ़ो, reg);

	CHILD_FAIL_IF(reg != info->amr2, &info->child_sync);

	/* Now let parent now that we are finished. */

	ret = prod_parent(&info->child_sync);
	CHILD_FAIL_IF(ret, &info->child_sync);

	वापस TEST_PASS;
पूर्ण

अटल पूर्णांक parent(काष्ठा shared_info *info, pid_t pid)
अणु
	अचिन्हित दीर्घ regs[3];
	पूर्णांक ret, status;

	/*
	 * Get the initial values क्रम AMR, IAMR and UAMOR and communicate them
	 * to the child.
	 */
	ret = ptrace_पढ़ो_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_SKIP_IF_UNSUPPORTED(ret, &info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	info->amr1 = info->amr2 = regs[0];
	info->expected_iamr = regs[1];
	info->expected_uamor = regs[2];

	/* Wake up child so that it can set itself up. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = रुको_child(&info->child_sync);
	अगर (ret)
		वापस ret;

	/* Verअगरy that we can पढ़ो the pkey रेजिस्टरs from the child. */
	ret = ptrace_पढ़ो_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_FAIL_IF(ret, &info->child_sync);

	म_लिखो("%-30s AMR: %016lx IAMR: %016lx UAMOR: %016lx\n",
	       ptrace_पढ़ो_running, regs[0], regs[1], regs[2]);

	PARENT_FAIL_IF(regs[0] != info->amr1, &info->child_sync);
	PARENT_FAIL_IF(regs[1] != info->expected_iamr, &info->child_sync);
	PARENT_FAIL_IF(regs[2] != info->expected_uamor, &info->child_sync);

	/* Write valid AMR value in child. */
	ret = ptrace_ग_लिखो_regs(pid, NT_PPC_PKEY, &info->amr2, 1);
	PARENT_FAIL_IF(ret, &info->child_sync);

	म_लिखो("%-30s AMR: %016lx\n", ptrace_ग_लिखो_running, info->amr2);

	/* Wake up child so that it can verअगरy it changed. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = रुको_child(&info->child_sync);
	अगर (ret)
		वापस ret;

	/* Write invalid AMR value in child. */
	ret = ptrace_ग_लिखो_regs(pid, NT_PPC_PKEY, &info->invalid_amr, 1);
	PARENT_FAIL_IF(ret, &info->child_sync);

	म_लिखो("%-30s AMR: %016lx\n", ptrace_ग_लिखो_running, info->invalid_amr);

	/* Wake up child so that it can verअगरy it didn't change. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = रुको_child(&info->child_sync);
	अगर (ret)
		वापस ret;

	/* Try to ग_लिखो to IAMR. */
	regs[0] = info->amr1;
	regs[1] = info->invalid_iamr;
	ret = ptrace_ग_लिखो_regs(pid, NT_PPC_PKEY, regs, 2);
	PARENT_FAIL_IF(!ret, &info->child_sync);

	म_लिखो("%-30s AMR: %016lx IAMR: %016lx\n",
	       ptrace_ग_लिखो_running, regs[0], regs[1]);

	/* Try to ग_लिखो to IAMR and UAMOR. */
	regs[2] = info->invalid_uamor;
	ret = ptrace_ग_लिखो_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_FAIL_IF(!ret, &info->child_sync);

	म_लिखो("%-30s AMR: %016lx IAMR: %016lx UAMOR: %016lx\n",
	       ptrace_ग_लिखो_running, regs[0], regs[1], regs[2]);

	/* Verअगरy that all रेजिस्टरs still have their expected values. */
	ret = ptrace_पढ़ो_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_FAIL_IF(ret, &info->child_sync);

	म_लिखो("%-30s AMR: %016lx IAMR: %016lx UAMOR: %016lx\n",
	       ptrace_पढ़ो_running, regs[0], regs[1], regs[2]);

	PARENT_FAIL_IF(regs[0] != info->amr2, &info->child_sync);
	PARENT_FAIL_IF(regs[1] != info->expected_iamr, &info->child_sync);
	PARENT_FAIL_IF(regs[2] != info->expected_uamor, &info->child_sync);

	/* Wake up child so that it can verअगरy AMR didn't change and wrap up. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = रुको(&status);
	अगर (ret != pid) अणु
		म_लिखो("Child's exit status not captured\n");
		ret = TEST_PASS;
	पूर्ण अन्यथा अगर (!WIFEXITED(status)) अणु
		म_लिखो("Child exited abnormally\n");
		ret = TEST_FAIL;
	पूर्ण अन्यथा
		ret = WEXITSTATUS(status) ? TEST_FAIL : TEST_PASS;

	वापस ret;
पूर्ण

अटल पूर्णांक ptrace_pkey(व्योम)
अणु
	काष्ठा shared_info *info;
	पूर्णांक shm_id;
	पूर्णांक ret;
	pid_t pid;

	shm_id = shmget(IPC_PRIVATE, माप(*info), 0777 | IPC_CREAT);
	info = shmat(shm_id, शून्य, 0);

	ret = init_child_sync(&info->child_sync);
	अगर (ret)
		वापस ret;

	pid = विभाजन();
	अगर (pid < 0) अणु
		लिखो_त्रुटि("fork() failed");
		ret = TEST_FAIL;
	पूर्ण अन्यथा अगर (pid == 0)
		ret = child(info);
	अन्यथा
		ret = parent(info, pid);

	shmdt(info);

	अगर (pid) अणु
		destroy_child_sync(&info->child_sync);
		shmctl(shm_id, IPC_RMID, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(ptrace_pkey, "ptrace_pkey");
पूर्ण
