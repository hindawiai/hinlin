<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ptrace test क्रम VMX/VSX रेजिस्टरs in the TM context
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#समावेश "ptrace.h"
#समावेश "tm.h"
#समावेश "ptrace-vsx.h"

पूर्णांक shm_id;
अचिन्हित दीर्घ *cptr, *pptr;

अचिन्हित दीर्घ fp_load[VEC_MAX];
अचिन्हित दीर्घ fp_store[VEC_MAX];
अचिन्हित दीर्घ fp_load_ckpt[VEC_MAX];
अचिन्हित दीर्घ fp_load_ckpt_new[VEC_MAX];

__attribute__((used)) व्योम load_vsx(व्योम)
अणु
	loadvsx(fp_load, 0);
पूर्ण

__attribute__((used)) व्योम load_vsx_ckpt(व्योम)
अणु
	loadvsx(fp_load_ckpt, 0);
पूर्ण

व्योम पंचांग_vsx(व्योम)
अणु
	अचिन्हित दीर्घ result, texasr;
	पूर्णांक ret;

	cptr = (अचिन्हित दीर्घ *)shmat(shm_id, शून्य, 0);

trans:
	cptr[1] = 0;
	यंत्र __अस्थिर__(
		"bl load_vsx_ckpt;"

		"1: ;"
		"tbegin.;"
		"beq 2f;"

		"bl load_vsx;"
		"tsuspend.;"
		"li 7, 1;"
		"stw 7, 0(%[cptr1]);"
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
		: [res] "=r" (result), [texasr] "=r" (texasr)
		: [sprn_texasr] "i"  (SPRN_TEXASR), [cptr1] "b" (&cptr[1])
		: "memory", "r0", "r3", "r4",
		  "r7", "r8", "r9", "r10", "r11", "lr"
		);

	अगर (result) अणु
		अगर (!cptr[0])
			जाओ trans;

		shmdt((व्योम *)cptr);
		storevsx(fp_store, 0);
		ret = compare_vsx_vmx(fp_store, fp_load_ckpt_new);
		अगर (ret)
			निकास(1);
		निकास(0);
	पूर्ण
	shmdt((व्योम *)cptr);
	निकास(1);
पूर्ण

पूर्णांक trace_पंचांग_vsx(pid_t child)
अणु
	अचिन्हित दीर्घ vsx[VSX_MAX];
	अचिन्हित दीर्घ vmx[VMX_MAX + 2][2];

	FAIL_IF(start_trace(child));
	FAIL_IF(show_vsx(child, vsx));
	FAIL_IF(validate_vsx(vsx, fp_load));
	FAIL_IF(show_vmx(child, vmx));
	FAIL_IF(validate_vmx(vmx, fp_load));
	FAIL_IF(show_vsx_ckpt(child, vsx));
	FAIL_IF(validate_vsx(vsx, fp_load_ckpt));
	FAIL_IF(show_vmx_ckpt(child, vmx));
	FAIL_IF(validate_vmx(vmx, fp_load_ckpt));
	स_रखो(vsx, 0, माप(vsx));
	स_रखो(vmx, 0, माप(vmx));

	load_vsx_vmx(fp_load_ckpt_new, vsx, vmx);

	FAIL_IF(ग_लिखो_vsx_ckpt(child, vsx));
	FAIL_IF(ग_लिखो_vmx_ckpt(child, vmx));
	pptr[0] = 1;
	FAIL_IF(stop_trace(child));
	वापस TEST_PASS;
पूर्ण

पूर्णांक ptrace_पंचांग_vsx(व्योम)
अणु
	pid_t pid;
	पूर्णांक ret, status, i;

	SKIP_IF(!have_hपंचांग());
	shm_id = shmget(IPC_PRIVATE, माप(पूर्णांक) * 2, 0777|IPC_CREAT);

	क्रम (i = 0; i < 128; i++) अणु
		fp_load[i] = 1 + अक्रम();
		fp_load_ckpt[i] = 1 + 2 * अक्रम();
		fp_load_ckpt_new[i] = 1 + 3 * अक्रम();
	पूर्ण

	pid = विभाजन();
	अगर (pid < 0) अणु
		लिखो_त्रुटि("fork() failed");
		वापस TEST_FAIL;
	पूर्ण

	अगर (pid == 0)
		पंचांग_vsx();

	अगर (pid) अणु
		pptr = (अचिन्हित दीर्घ *)shmat(shm_id, शून्य, 0);
		जबतक (!pptr[1])
			यंत्र अस्थिर("" : : : "memory");

		ret = trace_पंचांग_vsx(pid);
		अगर (ret) अणु
			समाप्त(pid, SIGKILL);
			shmdt((व्योम *)pptr);
			shmctl(shm_id, IPC_RMID, शून्य);
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
	वापस test_harness(ptrace_पंचांग_vsx, "ptrace_tm_vsx");
पूर्ण
