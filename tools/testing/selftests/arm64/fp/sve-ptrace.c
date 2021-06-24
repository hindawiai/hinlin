<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015-2020 ARM Limited.
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */
#समावेश <त्रुटिसं.स>
#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/auxv.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/types.h>
#समावेश <sys/uपन.स>
#समावेश <sys/रुको.h>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/ptrace.h>

#समावेश "../../kselftest.h"

/* <linux/elf.h> and <sys/auxv.h> करोn't like each other, so: */
#अगर_अघोषित NT_ARM_SVE
#घोषणा NT_ARM_SVE 0x405
#पूर्ण_अगर

/* Number of रेजिस्टरs filled in by sve_store_patterns */
#घोषणा NR_VREGS 5

व्योम sve_store_patterns(__uपूर्णांक128_t v[NR_VREGS]);

अटल व्योम dump(स्थिर व्योम *buf, माप_प्रकार size)
अणु
	माप_प्रकार i;
	स्थिर अचिन्हित अक्षर *p = buf;

	क्रम (i = 0; i < size; ++i)
		म_लिखो(" %.2x", *p++);
पूर्ण

अटल पूर्णांक check_vregs(स्थिर __uपूर्णांक128_t vregs[NR_VREGS])
अणु
	पूर्णांक i;
	पूर्णांक ok = 1;

	क्रम (i = 0; i < NR_VREGS; ++i) अणु
		म_लिखो("# v[%d]:", i);
		dump(&vregs[i], माप vregs[i]);
		अक्षर_दो('\n');

		अगर (vregs[i] != vregs[0])
			ok = 0;
	पूर्ण

	वापस ok;
पूर्ण

अटल पूर्णांक करो_child(व्योम)
अणु
	अगर (ptrace(PTRACE_TRACEME, -1, शून्य, शून्य))
		ksft_निकास_fail_msg("PTRACE_TRACEME", म_त्रुटि(त्रुटि_सं));

	अगर (उठाओ(SIGSTOP))
		ksft_निकास_fail_msg("raise(SIGSTOP)", म_त्रुटि(त्रुटि_सं));

	वापस निकास_सफल;
पूर्ण

अटल काष्ठा user_sve_header *get_sve(pid_t pid, व्योम **buf, माप_प्रकार *size)
अणु
	काष्ठा user_sve_header *sve;
	व्योम *p;
	माप_प्रकार sz = माप *sve;
	काष्ठा iovec iov;

	जबतक (1) अणु
		अगर (*size < sz) अणु
			p = पुनः_स्मृति(*buf, sz);
			अगर (!p) अणु
				त्रुटि_सं = ENOMEM;
				जाओ error;
			पूर्ण

			*buf = p;
			*size = sz;
		पूर्ण

		iov.iov_base = *buf;
		iov.iov_len = sz;
		अगर (ptrace(PTRACE_GETREGSET, pid, NT_ARM_SVE, &iov))
			जाओ error;

		sve = *buf;
		अगर (sve->size <= sz)
			अवरोध;

		sz = sve->size;
	पूर्ण

	वापस sve;

error:
	वापस शून्य;
पूर्ण

अटल पूर्णांक set_sve(pid_t pid, स्थिर काष्ठा user_sve_header *sve)
अणु
	काष्ठा iovec iov;

	iov.iov_base = (व्योम *)sve;
	iov.iov_len = sve->size;
	वापस ptrace(PTRACE_SETREGSET, pid, NT_ARM_SVE, &iov);
पूर्ण

अटल व्योम dump_sve_regs(स्थिर काष्ठा user_sve_header *sve, अचिन्हित पूर्णांक num,
			  अचिन्हित पूर्णांक vlmax)
अणु
	अचिन्हित पूर्णांक vq;
	अचिन्हित पूर्णांक i;

	अगर ((sve->flags & SVE_PT_REGS_MASK) != SVE_PT_REGS_SVE)
		ksft_निकास_fail_msg("Dumping non-SVE register\n");

	अगर (vlmax > sve->vl)
		vlmax = sve->vl;

	vq = sve_vq_from_vl(sve->vl);
	क्रम (i = 0; i < num; ++i) अणु
		म_लिखो("# z%u:", i);
		dump((स्थिर अक्षर *)sve + SVE_PT_SVE_ZREG_OFFSET(vq, i),
		     vlmax);
		म_लिखो("%s\n", vlmax == sve->vl ? "" : " ...");
	पूर्ण
पूर्ण

अटल पूर्णांक करो_parent(pid_t child)
अणु
	पूर्णांक ret = निकास_त्रुटि;
	pid_t pid;
	पूर्णांक status;
	siginfo_t si;
	व्योम *svebuf = शून्य, *newsvebuf;
	माप_प्रकार svebufsz = 0, newsvebufsz;
	काष्ठा user_sve_header *sve, *new_sve;
	काष्ठा user_fpsimd_state *fpsimd;
	अचिन्हित पूर्णांक i, j;
	अचिन्हित अक्षर *p;
	अचिन्हित पूर्णांक vq;

	/* Attach to the child */
	जबतक (1) अणु
		पूर्णांक sig;

		pid = रुको(&status);
		अगर (pid == -1) अणु
			लिखो_त्रुटि("wait");
			जाओ error;
		पूर्ण

		/*
		 * This should never happen but it's hard to flag in
		 * the framework.
		 */
		अगर (pid != child)
			जारी;

		अगर (WIFEXITED(status) || WIFSIGNALED(status))
			ksft_निकास_fail_msg("Child died unexpectedly\n");

		ksft_test_result(WIFSTOPPED(status), "WIFSTOPPED(%d)\n",
				 status);
		अगर (!WIFSTOPPED(status))
			जाओ error;

		sig = WSTOPSIG(status);

		अगर (ptrace(PTRACE_GETSIGINFO, pid, शून्य, &si)) अणु
			अगर (त्रुटि_सं == ESRCH)
				जाओ disappeared;

			अगर (त्रुटि_सं == EINVAL) अणु
				sig = 0; /* bust group-stop */
				जाओ cont;
			पूर्ण

			ksft_test_result_fail("PTRACE_GETSIGINFO: %s\n",
					      म_त्रुटि(त्रुटि_सं));
			जाओ error;
		पूर्ण

		अगर (sig == SIGSTOP && si.si_code == SI_TKILL &&
		    si.si_pid == pid)
			अवरोध;

	cont:
		अगर (ptrace(PTRACE_CONT, pid, शून्य, sig)) अणु
			अगर (त्रुटि_सं == ESRCH)
				जाओ disappeared;

			ksft_test_result_fail("PTRACE_CONT: %s\n",
					      म_त्रुटि(त्रुटि_सं));
			जाओ error;
		पूर्ण
	पूर्ण

	sve = get_sve(pid, &svebuf, &svebufsz);
	अगर (!sve) अणु
		पूर्णांक e = त्रुटि_सं;

		ksft_test_result_fail("get_sve: %s\n", म_त्रुटि(त्रुटि_सं));
		अगर (e == ESRCH)
			जाओ disappeared;

		जाओ error;
	पूर्ण अन्यथा अणु
		ksft_test_result_pass("get_sve\n");
	पूर्ण

	ksft_test_result((sve->flags & SVE_PT_REGS_MASK) == SVE_PT_REGS_FPSIMD,
			 "FPSIMD registers\n");
	अगर ((sve->flags & SVE_PT_REGS_MASK) != SVE_PT_REGS_FPSIMD)
		जाओ error;

	fpsimd = (काष्ठा user_fpsimd_state *)((अक्षर *)sve +
					      SVE_PT_FPSIMD_OFFSET);
	क्रम (i = 0; i < 32; ++i) अणु
		p = (अचिन्हित अक्षर *)&fpsimd->vregs[i];

		क्रम (j = 0; j < माप fpsimd->vregs[i]; ++j)
			p[j] = j;
	पूर्ण

	अगर (set_sve(pid, sve)) अणु
		पूर्णांक e = त्रुटि_सं;

		ksft_test_result_fail("set_sve(FPSIMD): %s\n",
				      म_त्रुटि(त्रुटि_सं));
		अगर (e == ESRCH)
			जाओ disappeared;

		जाओ error;
	पूर्ण

	vq = sve_vq_from_vl(sve->vl);

	newsvebufsz = SVE_PT_SVE_ZREG_OFFSET(vq, 1);
	new_sve = newsvebuf = दो_स्मृति(newsvebufsz);
	अगर (!new_sve) अणु
		त्रुटि_सं = ENOMEM;
		लिखो_त्रुटि(शून्य);
		जाओ error;
	पूर्ण

	*new_sve = *sve;
	new_sve->flags &= ~SVE_PT_REGS_MASK;
	new_sve->flags |= SVE_PT_REGS_SVE;
	स_रखो((अक्षर *)new_sve + SVE_PT_SVE_ZREG_OFFSET(vq, 0),
	       0, SVE_PT_SVE_ZREG_SIZE(vq));
	new_sve->size = SVE_PT_SVE_ZREG_OFFSET(vq, 1);
	अगर (set_sve(pid, new_sve)) अणु
		पूर्णांक e = त्रुटि_सं;

		ksft_test_result_fail("set_sve(ZREG): %s\n", म_त्रुटि(त्रुटि_सं));
		अगर (e == ESRCH)
			जाओ disappeared;

		जाओ error;
	पूर्ण

	new_sve = get_sve(pid, &newsvebuf, &newsvebufsz);
	अगर (!new_sve) अणु
		पूर्णांक e = त्रुटि_सं;

		ksft_test_result_fail("get_sve(ZREG): %s\n", म_त्रुटि(त्रुटि_सं));
		अगर (e == ESRCH)
			जाओ disappeared;

		जाओ error;
	पूर्ण

	ksft_test_result((new_sve->flags & SVE_PT_REGS_MASK) == SVE_PT_REGS_SVE,
			 "SVE registers\n");
	अगर ((new_sve->flags & SVE_PT_REGS_MASK) != SVE_PT_REGS_SVE)
		जाओ error;

	dump_sve_regs(new_sve, 3, माप fpsimd->vregs[0]);

	p = (अचिन्हित अक्षर *)new_sve + SVE_PT_SVE_ZREG_OFFSET(vq, 1);
	क्रम (i = 0; i < माप fpsimd->vregs[0]; ++i) अणु
		अचिन्हित अक्षर expected = i;

		अगर (__BYTE_ORDER == __BIG_ENDIAN)
			expected = माप fpsimd->vregs[0] - 1 - expected;

		ksft_test_result(p[i] == expected, "p[%d] == expected\n", i);
		अगर (p[i] != expected)
			जाओ error;
	पूर्ण

	ret = निकास_सफल;

error:
	समाप्त(child, SIGKILL);

disappeared:
	वापस ret;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक ret = निकास_सफल;
	__uपूर्णांक128_t v[NR_VREGS];
	pid_t child;

	ksft_prपूर्णांक_header();
	ksft_set_plan(20);

	अगर (!(getauxval(AT_HWCAP) & HWCAP_SVE))
		ksft_निकास_skip("SVE not available\n");

	sve_store_patterns(v);

	अगर (!check_vregs(v))
		ksft_निकास_fail_msg("Initial check_vregs() failed\n");

	child = विभाजन();
	अगर (!child)
		वापस करो_child();

	अगर (करो_parent(child))
		ret = निकास_त्रुटि;

	ksft_prपूर्णांक_cnts();

	वापस ret;
पूर्ण
