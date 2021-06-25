<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sigवापस.c - tests that x86 aव्योमs Intel SYSRET pitfalls
 * Copyright (c) 2014-2016 Andrew Lutomirski
 */

#घोषणा _GNU_SOURCE

#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/संकेत.स>
#समावेश <sys/ucontext.h>
#समावेश <sys/syscall.h>
#समावेश <err.h>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <समलाँघ.स>
#समावेश <sys/user.h>
#समावेश <sys/mman.h>
#समावेश <निश्चित.स>


यंत्र (
	".pushsection \".text\", \"ax\"\n\t"
	".balign 4096\n\t"
	"test_page: .globl test_page\n\t"
	".fill 4094,1,0xcc\n\t"
	"test_syscall_insn:\n\t"
	"syscall\n\t"
	".ifne . - test_page - 4096\n\t"
	".error \"test page is not one page long\"\n\t"
	".endif\n\t"
	".popsection"
    );

बाह्य स्थिर अक्षर test_page[];
अटल व्योम स्थिर *current_test_page_addr = test_page;

अटल व्योम sethandler(पूर्णांक sig, व्योम (*handler)(पूर्णांक, siginfo_t *, व्योम *),
		       पूर्णांक flags)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO | flags;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(sig, &sa, 0))
		err(1, "sigaction");
पूर्ण

अटल व्योम clearhandler(पूर्णांक sig)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_handler = संक_पूर्व;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(sig, &sa, 0))
		err(1, "sigaction");
पूर्ण

/* State used by our संकेत handlers. */
अटल gregset_t initial_regs;

अटल अस्थिर अचिन्हित दीर्घ rip;

अटल व्योम sigsegv_क्रम_sigवापस_test(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;

	अगर (rip != ctx->uc_mcontext.gregs[REG_RIP]) अणु
		म_लिखो("[FAIL]\tRequested RIP=0x%lx but got RIP=0x%lx\n",
		       rip, (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_RIP]);
		ख_साफ(मानक_निकास);
		_निकास(1);
	पूर्ण

	स_नकल(&ctx->uc_mcontext.gregs, &initial_regs, माप(gregset_t));

	म_लिखो("[OK]\tGot SIGSEGV at RIP=0x%lx\n", rip);
पूर्ण

अटल व्योम sigusr1(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;

	स_नकल(&initial_regs, &ctx->uc_mcontext.gregs, माप(gregset_t));

	/* Set IP and CX to match so that SYSRET can happen. */
	ctx->uc_mcontext.gregs[REG_RIP] = rip;
	ctx->uc_mcontext.gregs[REG_RCX] = rip;

	/* R11 and EFLAGS should alपढ़ोy match. */
	निश्चित(ctx->uc_mcontext.gregs[REG_EFL] ==
	       ctx->uc_mcontext.gregs[REG_R11]);

	sethandler(संक_अंश, sigsegv_क्रम_sigवापस_test, SA_RESETHAND);

	वापस;
पूर्ण

अटल व्योम test_sigवापस_to(अचिन्हित दीर्घ ip)
अणु
	rip = ip;
	म_लिखो("[RUN]\tsigreturn to 0x%lx\n", ip);
	उठाओ(SIGUSR1);
पूर्ण

अटल लाँघ_बफ jmpbuf;

अटल व्योम sigsegv_क्रम_fallthrough(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;

	अगर (rip != ctx->uc_mcontext.gregs[REG_RIP]) अणु
		म_लिखो("[FAIL]\tExpected SIGSEGV at 0x%lx but got RIP=0x%lx\n",
		       rip, (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_RIP]);
		ख_साफ(मानक_निकास);
		_निकास(1);
	पूर्ण

	sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

अटल व्योम test_syscall_fallthrough_to(अचिन्हित दीर्घ ip)
अणु
	व्योम *new_address = (व्योम *)(ip - 4096);
	व्योम *ret;

	म_लिखो("[RUN]\tTrying a SYSCALL that falls through to 0x%lx\n", ip);

	ret = mremap((व्योम *)current_test_page_addr, 4096, 4096,
		     MREMAP_MAYMOVE | MREMAP_FIXED, new_address);
	अगर (ret == MAP_FAILED) अणु
		अगर (ip <= (1UL << 47) - PAGE_SIZE) अणु
			err(1, "mremap to %p", new_address);
		पूर्ण अन्यथा अणु
			म_लिखो("[OK]\tmremap to %p failed\n", new_address);
			वापस;
		पूर्ण
	पूर्ण

	अगर (ret != new_address)
		errx(1, "mremap malfunctioned: asked for %p but got %p\n",
		     new_address, ret);

	current_test_page_addr = new_address;
	rip = ip;

	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		यंत्र अस्थिर ("call *%[syscall_insn]" :: "a" (SYS_getpid),
			      [syscall_insn] "rm" (ip - 2));
		errx(1, "[FAIL]\tSyscall trampoline returned");
	पूर्ण

	म_लिखो("[OK]\tWe survived\n");
पूर्ण

पूर्णांक मुख्य()
अणु
	/*
	 * When the kernel वापसs from a slow-path syscall, it will
	 * detect whether SYSRET is appropriate.  If it incorrectly
	 * thinks that SYSRET is appropriate when RIP is noncanonical,
	 * it'll crash on Intel CPUs.
	 */
	sethandler(SIGUSR1, sigusr1, 0);
	क्रम (पूर्णांक i = 47; i < 64; i++)
		test_sigवापस_to(1UL<<i);

	clearhandler(SIGUSR1);

	sethandler(संक_अंश, sigsegv_क्रम_fallthrough, 0);

	/* One extra test to check that we didn't screw up the mremap logic. */
	test_syscall_fallthrough_to((1UL << 47) - 2*PAGE_SIZE);

	/* These are the पूर्णांकeresting हालs. */
	क्रम (पूर्णांक i = 47; i < 64; i++) अणु
		test_syscall_fallthrough_to((1UL<<i) - PAGE_SIZE);
		test_syscall_fallthrough_to(1UL<<i);
	पूर्ण

	वापस 0;
पूर्ण
