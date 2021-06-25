<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ptrace test क्रम VMX/VSX रेजिस्टरs
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#समावेश "ptrace.h"
#समावेश "ptrace-vsx.h"

/* Tracer and Tracee Shared Data */
पूर्णांक shm_id;
पूर्णांक *cptr, *pptr;

अचिन्हित दीर्घ fp_load[VEC_MAX];
अचिन्हित दीर्घ fp_load_new[VEC_MAX];
अचिन्हित दीर्घ fp_store[VEC_MAX];

व्योम vsx(व्योम)
अणु
	पूर्णांक ret;

	cptr = (पूर्णांक *)shmat(shm_id, शून्य, 0);
	loadvsx(fp_load, 0);
	cptr[1] = 1;

	जबतक (!cptr[0])
		यंत्र अस्थिर("" : : : "memory");
	shmdt((व्योम *) cptr);

	storevsx(fp_store, 0);
	ret = compare_vsx_vmx(fp_store, fp_load_new);
	अगर (ret)
		निकास(1);
	निकास(0);
पूर्ण

पूर्णांक trace_vsx(pid_t child)
अणु
	अचिन्हित दीर्घ vsx[VSX_MAX];
	अचिन्हित दीर्घ vmx[VMX_MAX + 2][2];

	FAIL_IF(start_trace(child));
	FAIL_IF(show_vsx(child, vsx));
	FAIL_IF(validate_vsx(vsx, fp_load));
	FAIL_IF(show_vmx(child, vmx));
	FAIL_IF(validate_vmx(vmx, fp_load));

	स_रखो(vsx, 0, माप(vsx));
	स_रखो(vmx, 0, माप(vmx));
	load_vsx_vmx(fp_load_new, vsx, vmx);

	FAIL_IF(ग_लिखो_vsx(child, vsx));
	FAIL_IF(ग_लिखो_vmx(child, vmx));
	FAIL_IF(stop_trace(child));

	वापस TEST_PASS;
पूर्ण

पूर्णांक ptrace_vsx(व्योम)
अणु
	pid_t pid;
	पूर्णांक ret, status, i;

	SKIP_IF(!have_hwcap(PPC_FEATURE_HAS_VSX));

	shm_id = shmget(IPC_PRIVATE, माप(पूर्णांक) * 2, 0777|IPC_CREAT);

	क्रम (i = 0; i < VEC_MAX; i++)
		fp_load[i] = i + अक्रम();

	क्रम (i = 0; i < VEC_MAX; i++)
		fp_load_new[i] = i + 2 * अक्रम();

	pid = विभाजन();
	अगर (pid < 0) अणु
		लिखो_त्रुटि("fork() failed");
		वापस TEST_FAIL;
	पूर्ण

	अगर (pid == 0)
		vsx();

	अगर (pid) अणु
		pptr = (पूर्णांक *)shmat(shm_id, शून्य, 0);
		जबतक (!pptr[1])
			यंत्र अस्थिर("" : : : "memory");

		ret = trace_vsx(pid);
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
	वापस test_harness(ptrace_vsx, "ptrace_vsx");
पूर्ण
