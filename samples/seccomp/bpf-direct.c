<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Seccomp filter example क्रम x86 (32-bit and 64-bit) with BPF macros
 *
 * Copyright (c) 2012 The Chromium OS Authors <chromium-os-dev@chromium.org>
 * Author: Will Drewry <wad@chromium.org>
 *
 * The code may be used by anyone क्रम any purpose,
 * and can serve as a starting poपूर्णांक क्रम developing
 * applications using prctl(PR_SET_SECCOMP, 2, ...).
 */
#अगर defined(__i386__) || defined(__x86_64__)
#घोषणा SUPPORTED_ARCH 1
#पूर्ण_अगर

#अगर defined(SUPPORTED_ARCH)
#घोषणा __USE_GNU 1
#घोषणा _GNU_SOURCE 1

#समावेश <linux/types.h>
#समावेश <linux/filter.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/unistd.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <sys/prctl.h>
#समावेश <unistd.h>

#घोषणा syscall_arg(_n) (दुरत्व(काष्ठा seccomp_data, args[_n]))
#घोषणा syscall_nr (दुरत्व(काष्ठा seccomp_data, nr))

#अगर defined(__i386__)
#घोषणा REG_RESULT	REG_EAX
#घोषणा REG_SYSCALL	REG_EAX
#घोषणा REG_ARG0	REG_EBX
#घोषणा REG_ARG1	REG_ECX
#घोषणा REG_ARG2	REG_EDX
#घोषणा REG_ARG3	REG_ESI
#घोषणा REG_ARG4	REG_EDI
#घोषणा REG_ARG5	REG_EBP
#या_अगर defined(__x86_64__)
#घोषणा REG_RESULT	REG_RAX
#घोषणा REG_SYSCALL	REG_RAX
#घोषणा REG_ARG0	REG_RDI
#घोषणा REG_ARG1	REG_RSI
#घोषणा REG_ARG2	REG_RDX
#घोषणा REG_ARG3	REG_R10
#घोषणा REG_ARG4	REG_R8
#घोषणा REG_ARG5	REG_R9
#पूर्ण_अगर

#अगर_अघोषित PR_SET_NO_NEW_PRIVS
#घोषणा PR_SET_NO_NEW_PRIVS 38
#पूर्ण_अगर

#अगर_अघोषित SYS_SECCOMP
#घोषणा SYS_SECCOMP 1
#पूर्ण_अगर

अटल व्योम emulator(पूर्णांक nr, siginfo_t *info, व्योम *व्योम_context)
अणु
	ucontext_t *ctx = (ucontext_t *)(व्योम_context);
	पूर्णांक syscall;
	अक्षर *buf;
	sमाप_प्रकार bytes;
	माप_प्रकार len;
	अगर (info->si_code != SYS_SECCOMP)
		वापस;
	अगर (!ctx)
		वापस;
	syscall = ctx->uc_mcontext.gregs[REG_SYSCALL];
	buf = (अक्षर *) ctx->uc_mcontext.gregs[REG_ARG1];
	len = (माप_प्रकार) ctx->uc_mcontext.gregs[REG_ARG2];

	अगर (syscall != __NR_ग_लिखो)
		वापस;
	अगर (ctx->uc_mcontext.gregs[REG_ARG0] != STDERR_खाताNO)
		वापस;
	/* Redirect मानक_त्रुटि messages to मानक_निकास. Doesn't handle EINTR, etc */
	ctx->uc_mcontext.gregs[REG_RESULT] = -1;
	अगर (ग_लिखो(STDOUT_खाताNO, "[ERR] ", 6) > 0) अणु
		bytes = ग_लिखो(STDOUT_खाताNO, buf, len);
		ctx->uc_mcontext.gregs[REG_RESULT] = bytes;
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक install_emulator(व्योम)
अणु
	काष्ठा sigaction act;
	sigset_t mask;
	स_रखो(&act, 0, माप(act));
	sigemptyset(&mask);
	sigaddset(&mask, SIGSYS);

	act.sa_sigaction = &emulator;
	act.sa_flags = SA_SIGINFO;
	अगर (sigaction(SIGSYS, &act, शून्य) < 0) अणु
		लिखो_त्रुटि("sigaction");
		वापस -1;
	पूर्ण
	अगर (sigprocmask(SIG_UNBLOCK, &mask, शून्य)) अणु
		लिखो_त्रुटि("sigprocmask");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक install_filter(व्योम)
अणु
	काष्ठा sock_filter filter[] = अणु
		/* Grab the प्रणाली call number */
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS, syscall_nr),
		/* Jump table क्रम the allowed syscalls */
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_rt_sigवापस, 0, 1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
#अगर_घोषित __NR_sigवापस
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_sigवापस, 0, 1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
#पूर्ण_अगर
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_निकास_group, 0, 1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_निकास, 0, 1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_पढ़ो, 1, 0),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_ग_लिखो, 3, 2),

		/* Check that पढ़ो is only using मानक_निवेश. */
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS, syscall_arg(0)),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, STDIN_खाताNO, 4, 0),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL),

		/* Check that ग_लिखो is only using मानक_निकास */
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS, syscall_arg(0)),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, STDOUT_खाताNO, 1, 0),
		/* Trap attempts to ग_लिखो to मानक_त्रुटि */
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, STDERR_खाताNO, 1, 2),

		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_TRAP),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)(माप(filter)/माप(filter[0])),
		.filter = filter,
	पूर्ण;

	अगर (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		लिखो_त्रुटि("prctl(NO_NEW_PRIVS)");
		वापस 1;
	पूर्ण


	अगर (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog)) अणु
		लिखो_त्रुटि("prctl");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा payload(_c) (_c), माप((_c))
पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर buf[4096];
	sमाप_प्रकार bytes = 0;
	अगर (install_emulator())
		वापस 1;
	अगर (install_filter())
		वापस 1;
	syscall(__NR_ग_लिखो, STDOUT_खाताNO,
		payload("OHAI! WHAT IS YOUR NAME? "));
	bytes = syscall(__NR_पढ़ो, STDIN_खाताNO, buf, माप(buf));
	syscall(__NR_ग_लिखो, STDOUT_खाताNO, payload("HELLO, "));
	syscall(__NR_ग_लिखो, STDOUT_खाताNO, buf, bytes);
	syscall(__NR_ग_लिखो, STDERR_खाताNO,
		payload("Error message going to STDERR\n"));
	वापस 0;
पूर्ण
#अन्यथा	/* SUPPORTED_ARCH */
/*
 * This sample is x86-only.  Since kernel samples are compiled with the
 * host toolchain, a non-x86 host will result in using only the मुख्य()
 * below.
 */
पूर्णांक मुख्य(व्योम)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर	/* SUPPORTED_ARCH */
