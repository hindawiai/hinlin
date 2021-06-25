<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 32-bit syscall ABI conक्रमmance test.
 *
 * Copyright (c) 2015 Denys Vlasenko
 */
/*
 * Can be built अटलally:
 * gcc -Os -Wall -अटल -m32 test_syscall_vdso.c thunks_32.S
 */
#अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE 1
#अघोषित __USE_GNU
#घोषणा __USE_GNU 1
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <sys/types.h>
#समावेश <sys/select.h>
#समावेश <sys/समय.स>
#समावेश <elf.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/रुको.h>

#अगर !defined(__i386__)
पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv, अक्षर **envp)
अणु
	म_लिखो("[SKIP]\tNot a 32-bit x86 userspace\n");
	वापस 0;
पूर्ण
#अन्यथा

दीर्घ syscall_addr;
दीर्घ get_syscall(अक्षर **envp)
अणु
	Elf32_auxv_t *auxv;
	जबतक (*envp++ != शून्य)
		जारी;
	क्रम (auxv = (व्योम *)envp; auxv->a_type != AT_शून्य; auxv++)
		अगर (auxv->a_type == AT_SYSINFO)
			वापस auxv->a_un.a_val;
	म_लिखो("[WARN]\tAT_SYSINFO not supplied\n");
	वापस 0;
पूर्ण

यंत्र (
	"	.pushsection .text\n"
	"	.global	int80\n"
	"int80:\n"
	"	int	$0x80\n"
	"	ret\n"
	"	.popsection\n"
);
बाह्य अक्षर पूर्णांक80;

काष्ठा regs64 अणु
	uपूर्णांक64_t rax, rbx, rcx, rdx;
	uपूर्णांक64_t rsi, rdi, rbp, rsp;
	uपूर्णांक64_t r8,  r9,  r10, r11;
	uपूर्णांक64_t r12, r13, r14, r15;
पूर्ण;
काष्ठा regs64 regs64;
पूर्णांक kernel_is_64bit;

यंत्र (
	"	.pushsection .text\n"
	"	.code64\n"
	"get_regs64:\n"
	"	push	%rax\n"
	"	mov	$regs64, %eax\n"
	"	pop	0*8(%rax)\n"
	"	movq	%rbx, 1*8(%rax)\n"
	"	movq	%rcx, 2*8(%rax)\n"
	"	movq	%rdx, 3*8(%rax)\n"
	"	movq	%rsi, 4*8(%rax)\n"
	"	movq	%rdi, 5*8(%rax)\n"
	"	movq	%rbp, 6*8(%rax)\n"
	"	movq	%rsp, 7*8(%rax)\n"
	"	movq	%r8,  8*8(%rax)\n"
	"	movq	%r9,  9*8(%rax)\n"
	"	movq	%r10, 10*8(%rax)\n"
	"	movq	%r11, 11*8(%rax)\n"
	"	movq	%r12, 12*8(%rax)\n"
	"	movq	%r13, 13*8(%rax)\n"
	"	movq	%r14, 14*8(%rax)\n"
	"	movq	%r15, 15*8(%rax)\n"
	"	ret\n"
	"poison_regs64:\n"
	"	movq	$0x7f7f7f7f, %r8\n"
	"	shl	$32, %r8\n"
	"	orq	$0x7f7f7f7f, %r8\n"
	"	movq	%r8, %r9\n"
	"	incq	%r9\n"
	"	movq	%r9, %r10\n"
	"	incq	%r10\n"
	"	movq	%r10, %r11\n"
	"	incq	%r11\n"
	"	movq	%r11, %r12\n"
	"	incq	%r12\n"
	"	movq	%r12, %r13\n"
	"	incq	%r13\n"
	"	movq	%r13, %r14\n"
	"	incq	%r14\n"
	"	movq	%r14, %r15\n"
	"	incq	%r15\n"
	"	ret\n"
	"	.code32\n"
	"	.popsection\n"
);
बाह्य व्योम get_regs64(व्योम);
बाह्य व्योम poison_regs64(व्योम);
बाह्य अचिन्हित दीर्घ call64_from_32(व्योम (*function)(व्योम));
व्योम prपूर्णांक_regs64(व्योम)
अणु
	अगर (!kernel_is_64bit)
		वापस;
	म_लिखो("ax:%016llx bx:%016llx cx:%016llx dx:%016llx\n", regs64.rax,  regs64.rbx,  regs64.rcx,  regs64.rdx);
	म_लिखो("si:%016llx di:%016llx bp:%016llx sp:%016llx\n", regs64.rsi,  regs64.rdi,  regs64.rbp,  regs64.rsp);
	म_लिखो(" 8:%016llx  9:%016llx 10:%016llx 11:%016llx\n", regs64.r8 ,  regs64.r9 ,  regs64.r10,  regs64.r11);
	म_लिखो("12:%016llx 13:%016llx 14:%016llx 15:%016llx\n", regs64.r12,  regs64.r13,  regs64.r14,  regs64.r15);
पूर्ण

पूर्णांक check_regs64(व्योम)
अणु
	पूर्णांक err = 0;
	पूर्णांक num = 8;
	uपूर्णांक64_t *r64 = &regs64.r8;
	uपूर्णांक64_t expected = 0x7f7f7f7f7f7f7f7fULL;

	अगर (!kernel_is_64bit)
		वापस 0;

	करो अणु
		अगर (*r64 == expected++)
			जारी; /* रेजिस्टर did not change */
		अगर (syscall_addr != (दीर्घ)&पूर्णांक80) अणु
			/*
			 * Non-INT80 syscall entrypoपूर्णांकs are allowed to clobber R8+ regs:
			 * either clear them to 0, or क्रम R11, load EFLAGS.
			 */
			अगर (*r64 == 0)
				जारी;
			अगर (num == 11) अणु
				म_लिखो("[NOTE]\tR11 has changed:%016llx - assuming clobbered by SYSRET insn\n", *r64);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * INT80 syscall entrypoपूर्णांक can be used by
			 * 64-bit programs too, unlike SYSCALL/SYSENTER.
			 * Thereक्रमe it must preserve R12+
			 * (they are callee-saved रेजिस्टरs in 64-bit C ABI).
			 *
			 * Starting in Linux 4.17 (and any kernel that
			 * backports the change), R8..11 are preserved.
			 * Historically (and probably unपूर्णांकentionally), they
			 * were clobbered or zeroed.
			 */
		पूर्ण
		म_लिखो("[FAIL]\tR%d has changed:%016llx\n", num, *r64);
		err++;
	पूर्ण जबतक (r64++, ++num < 16);

	अगर (!err)
		म_लिखो("[OK]\tR8..R15 did not leak kernel data\n");
	वापस err;
पूर्ण

पूर्णांक nfds;
fd_set rfds;
fd_set wfds;
fd_set efds;
काष्ठा बारpec समयout;
sigset_t sigmask;
काष्ठा अणु
	sigset_t *sp;
	पूर्णांक sz;
पूर्ण sigmask_desc;

व्योम prep_args()
अणु
	nfds = 42;
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_ZERO(&efds);
	FD_SET(0, &rfds);
	FD_SET(1, &wfds);
	FD_SET(2, &efds);
	समयout.tv_sec = 0;
	समयout.tv_nsec = 123;
	sigemptyset(&sigmask);
	sigaddset(&sigmask, संक_विघ्न);
	sigaddset(&sigmask, SIGUSR2);
	sigaddset(&sigmask, SIGRTMAX);
	sigmask_desc.sp = &sigmask;
	sigmask_desc.sz = 8; /* bytes */
पूर्ण

अटल व्योम prपूर्णांक_flags(स्थिर अक्षर *name, अचिन्हित दीर्घ r)
अणु
	अटल स्थिर अक्षर *bitarray[] = अणु
	"\n" ,"c\n" ,/* Carry Flag */
	"0 " ,"1 "  ,/* Bit 1 - always on */
	""   ,"p "  ,/* Parity Flag */
	"0 " ,"3? " ,
	""   ,"a "  ,/* Auxiliary carry Flag */
	"0 " ,"5? " ,
	""   ,"z "  ,/* Zero Flag */
	""   ,"s "  ,/* Sign Flag */
	""   ,"t "  ,/* Trap Flag */
	""   ,"i "  ,/* Interrupt Flag */
	""   ,"d "  ,/* Direction Flag */
	""   ,"o "  ,/* Overflow Flag */
	"0 " ,"1 "  ,/* I/O Privilege Level (2 bits) */
	"0"  ,"1"   ,/* I/O Privilege Level (2 bits) */
	""   ,"n "  ,/* Nested Task */
	"0 " ,"15? ",
	""   ,"r "  ,/* Resume Flag */
	""   ,"v "  ,/* Virtual Mode */
	""   ,"ac " ,/* Alignment Check/Access Control */
	""   ,"vif ",/* Virtual Interrupt Flag */
	""   ,"vip ",/* Virtual Interrupt Pending */
	""   ,"id " ,/* CPUID detection */
	शून्य
	पूर्ण;
	स्थिर अक्षर **bitstr;
	पूर्णांक bit;

	म_लिखो("%s=%016lx ", name, r);
	bitstr = bitarray + 42;
	bit = 21;
	अगर ((r >> 22) != 0)
		म_लिखो("(extra bits are set) ");
	करो अणु
		अगर (bitstr[(r >> bit) & 1][0])
			ख_माला_दो(bitstr[(r >> bit) & 1], मानक_निकास);
		bitstr -= 2;
		bit--;
	पूर्ण जबतक (bit >= 0);
पूर्ण

पूर्णांक run_syscall(व्योम)
अणु
	दीर्घ flags, bad_arg;

	prep_args();

	अगर (kernel_is_64bit)
		call64_from_32(poison_regs64);
	/*prपूर्णांक_regs64();*/

	यंत्र("\n"
	/* Try 6-arg syscall: pselect. It should वापस quickly */
	"	push	%%ebp\n"
	"	mov	$308, %%eax\n"     /* PSELECT */
	"	mov	nfds, %%ebx\n"     /* ebx  arg1 */
	"	mov	$rfds, %%ecx\n"    /* ecx  arg2 */
	"	mov	$wfds, %%edx\n"    /* edx  arg3 */
	"	mov	$efds, %%esi\n"    /* esi  arg4 */
	"	mov	$timeout, %%edi\n" /* edi  arg5 */
	"	mov	$sigmask_desc, %%ebp\n" /* %ebp arg6 */
	"	push	$0x200ed7\n"      /* set almost all flags */
	"	popf\n"		/* except TF, IOPL, NT, RF, VM, AC, VIF, VIP */
	"	call	*syscall_addr\n"
	/* Check that रेजिस्टरs are not clobbered */
	"	pushf\n"
	"	pop	%%eax\n"
	"	cld\n"
	"	cmp	nfds, %%ebx\n"     /* ebx  arg1 */
	"	mov	$1, %%ebx\n"
	"	jne	1f\n"
	"	cmp	$rfds, %%ecx\n"    /* ecx  arg2 */
	"	mov	$2, %%ebx\n"
	"	jne	1f\n"
	"	cmp	$wfds, %%edx\n"    /* edx  arg3 */
	"	mov	$3, %%ebx\n"
	"	jne	1f\n"
	"	cmp	$efds, %%esi\n"    /* esi  arg4 */
	"	mov	$4, %%ebx\n"
	"	jne	1f\n"
	"	cmp	$timeout, %%edi\n" /* edi  arg5 */
	"	mov	$5, %%ebx\n"
	"	jne	1f\n"
	"	cmpl	$sigmask_desc, %%ebp\n" /* %ebp arg6 */
	"	mov	$6, %%ebx\n"
	"	jne	1f\n"
	"	mov	$0, %%ebx\n"
	"1:\n"
	"	pop	%%ebp\n"
	: "=a" (flags), "=b" (bad_arg)
	:
	: "cx", "dx", "si", "di"
	);

	अगर (kernel_is_64bit) अणु
		स_रखो(&regs64, 0x77, माप(regs64));
		call64_from_32(get_regs64);
		/*prपूर्णांक_regs64();*/
	पूर्ण

	/*
	 * On paravirt kernels, flags are not preserved across syscalls.
	 * Thus, we करो not consider it a bug अगर some are changed.
	 * We just show ones which करो.
	 */
	अगर ((0x200ed7 ^ flags) != 0) अणु
		prपूर्णांक_flags("[WARN]\tFlags before", 0x200ed7);
		prपूर्णांक_flags("[WARN]\tFlags  after", flags);
		prपूर्णांक_flags("[WARN]\tFlags change", (0x200ed7 ^ flags));
	पूर्ण

	अगर (bad_arg) अणु
		म_लिखो("[FAIL]\targ#%ld clobbered\n", bad_arg);
		वापस 1;
	पूर्ण
	म_लिखो("[OK]\tArguments are preserved across syscall\n");

	वापस check_regs64();
पूर्ण

पूर्णांक run_syscall_twice()
अणु
	पूर्णांक निकासcode = 0;
	दीर्घ sv;

	अगर (syscall_addr) अणु
		म_लिखो("[RUN]\tExecuting 6-argument 32-bit syscall via VDSO\n");
		निकासcode = run_syscall();
	पूर्ण
	sv = syscall_addr;
	syscall_addr = (दीर्घ)&पूर्णांक80;
	म_लिखो("[RUN]\tExecuting 6-argument 32-bit syscall via INT 80\n");
	निकासcode += run_syscall();
	syscall_addr = sv;
	वापस निकासcode;
पूर्ण

व्योम ptrace_me()
अणु
	pid_t pid;

	ख_साफ(शून्य);
	pid = विभाजन();
	अगर (pid < 0)
		निकास(1);
	अगर (pid == 0) अणु
		/* child */
		अगर (ptrace(PTRACE_TRACEME, 0L, 0L, 0L) != 0)
			निकास(0);
		उठाओ(SIGSTOP);
		वापस;
	पूर्ण
	/* parent */
	म_लिखो("[RUN]\tRunning tests under ptrace\n");
	जबतक (1) अणु
		पूर्णांक status;
		pid = रुकोpid(-1, &status, __WALL);
		अगर (WIFEXITED(status))
			निकास(WEXITSTATUS(status));
		अगर (WIFSIGNALED(status))
			निकास(WTERMSIG(status));
		अगर (pid <= 0 || !WIFSTOPPED(status)) /* paranoia */
			निकास(255);
		/*
		 * Note: we करो not inject sig = WSTOPSIG(status).
		 * We probably should, but careful: करो not inject SIGTRAP
		 * generated by syscall entry/निकास stops.
		 * That समाप्तs the child.
		 */
		ptrace(PTRACE_SYSCALL, pid, 0L, 0L /*sig*/);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv, अक्षर **envp)
अणु
	पूर्णांक निकासcode = 0;
	पूर्णांक cs;

	यंत्र("\n"
	"	movl	%%cs, %%eax\n"
	: "=a" (cs)
	);
	kernel_is_64bit = (cs == 0x23);
	अगर (!kernel_is_64bit)
		म_लिखो("[NOTE]\tNot a 64-bit kernel, won't test R8..R15 leaks\n");

	/* This only works क्रम non-अटल builds:
	 * syscall_addr = dlsym(dlखोलो("linux-gate.so.1", RTLD_NOW), "__kernel_vsyscall");
	 */
	syscall_addr = get_syscall(envp);

	निकासcode += run_syscall_twice();
	ptrace_me();
	निकासcode += run_syscall_twice();

	वापस निकासcode;
पूर्ण
#पूर्ण_अगर
