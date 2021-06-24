<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * entry_from_vm86.c - tests kernel entries from vm86 mode
 * Copyright (c) 2014-2015 Andrew Lutomirski
 *
 * This exercises a few paths that need to special-हाल vm86 mode.
 */

#घोषणा _GNU_SOURCE

#समावेश <निश्चित.स>
#समावेश <मानककोष.स>
#समावेश <sys/syscall.h>
#समावेश <sys/संकेत.स>
#समावेश <sys/ucontext.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/mman.h>
#समावेश <err.h>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/vm86.h>

अटल अचिन्हित दीर्घ load_addr = 0x10000;
अटल पूर्णांक nerrs = 0;

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

अटल संक_पूर्ण_प्रकार got_संकेत;

अटल व्योम sighandler(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;

	अगर (ctx->uc_mcontext.gregs[REG_EFL] & X86_EFLAGS_VM ||
	    (ctx->uc_mcontext.gregs[REG_CS] & 3) != 3) अणु
		म_लिखो("[FAIL]\tSignal frame should not reflect vm86 mode\n");
		nerrs++;
	पूर्ण

	स्थिर अक्षर *signame;
	अगर (sig == संक_अंश)
		signame = "SIGSEGV";
	अन्यथा अगर (sig == संक_अवैध)
		signame = "SIGILL";
	अन्यथा
		signame = "unexpected signal";

	म_लिखो("[INFO]\t%s: FLAGS = 0x%lx, CS = 0x%hx\n", signame,
	       (अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_EFL],
	       (अचिन्हित लघु)ctx->uc_mcontext.gregs[REG_CS]);

	got_संकेत = 1;
पूर्ण

यंत्र (
	".pushsection .rodata\n\t"
	".type vmcode_bound, @object\n\t"
	"vmcode:\n\t"
	"vmcode_bound:\n\t"
	".code16\n\t"
	"bound %ax, (2048)\n\t"
	"int3\n\t"
	"vmcode_sysenter:\n\t"
	"sysenter\n\t"
	"vmcode_syscall:\n\t"
	"syscall\n\t"
	"vmcode_sti:\n\t"
	"sti\n\t"
	"vmcode_int3:\n\t"
	"int3\n\t"
	"vmcode_int80:\n\t"
	"int $0x80\n\t"
	"vmcode_popf_hlt:\n\t"
	"push %ax\n\t"
	"popf\n\t"
	"hlt\n\t"
	"vmcode_umip:\n\t"
	/* addressing via displacements */
	"smsw (2052)\n\t"
	"sidt (2054)\n\t"
	"sgdt (2060)\n\t"
	/* addressing via रेजिस्टरs */
	"mov $2066, %bx\n\t"
	"smsw (%bx)\n\t"
	"mov $2068, %bx\n\t"
	"sidt (%bx)\n\t"
	"mov $2074, %bx\n\t"
	"sgdt (%bx)\n\t"
	/* रेजिस्टर opeअक्रमs, only क्रम smsw */
	"smsw %ax\n\t"
	"mov %ax, (2080)\n\t"
	"int3\n\t"
	"vmcode_umip_str:\n\t"
	"str %eax\n\t"
	"vmcode_umip_sldt:\n\t"
	"sldt %eax\n\t"
	"int3\n\t"
	".size vmcode, . - vmcode\n\t"
	"end_vmcode:\n\t"
	".code32\n\t"
	".popsection"
	);

बाह्य अचिन्हित अक्षर vmcode[], end_vmcode[];
बाह्य अचिन्हित अक्षर vmcode_bound[], vmcode_sysenter[], vmcode_syscall[],
	vmcode_sti[], vmcode_पूर्णांक3[], vmcode_पूर्णांक80[], vmcode_popf_hlt[],
	vmcode_umip[], vmcode_umip_str[], vmcode_umip_sldt[];

/* Returns false अगर the test was skipped. */
अटल bool करो_test(काष्ठा vm86plus_काष्ठा *v86, अचिन्हित दीर्घ eip,
		    अचिन्हित पूर्णांक rettype, अचिन्हित पूर्णांक retarg,
		    स्थिर अक्षर *text)
अणु
	दीर्घ ret;

	म_लिखो("[RUN]\t%s from vm86 mode\n", text);
	v86->regs.eip = eip;
	ret = vm86(VM86_ENTER, v86);

	अगर (ret == -1 && (त्रुटि_सं == ENOSYS || त्रुटि_सं == EPERM)) अणु
		म_लिखो("[SKIP]\tvm86 %s\n",
		       त्रुटि_सं == ENOSYS ? "not supported" : "not allowed");
		वापस false;
	पूर्ण

	अगर (VM86_TYPE(ret) == VM86_INTx) अणु
		अक्षर trapname[32];
		पूर्णांक trapno = VM86_ARG(ret);
		अगर (trapno == 13)
			म_नकल(trapname, "GP");
		अन्यथा अगर (trapno == 5)
			म_नकल(trapname, "BR");
		अन्यथा अगर (trapno == 14)
			म_नकल(trapname, "PF");
		अन्यथा
			प्र_लिखो(trapname, "%d", trapno);

		म_लिखो("[INFO]\tExited vm86 mode due to #%s\n", trapname);
	पूर्ण अन्यथा अगर (VM86_TYPE(ret) == VM86_UNKNOWN) अणु
		म_लिखो("[INFO]\tExited vm86 mode due to unhandled GP fault\n");
	पूर्ण अन्यथा अगर (VM86_TYPE(ret) == VM86_TRAP) अणु
		म_लिखो("[INFO]\tExited vm86 mode due to a trap (arg=%ld)\n",
		       VM86_ARG(ret));
	पूर्ण अन्यथा अगर (VM86_TYPE(ret) == VM86_SIGNAL) अणु
		म_लिखो("[INFO]\tExited vm86 mode due to a signal\n");
	पूर्ण अन्यथा अगर (VM86_TYPE(ret) == VM86_STI) अणु
		म_लिखो("[INFO]\tExited vm86 mode due to STI\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[INFO]\tExited vm86 mode due to type %ld, arg %ld\n",
		       VM86_TYPE(ret), VM86_ARG(ret));
	पूर्ण

	अगर (rettype == -1 ||
	    (VM86_TYPE(ret) == rettype && VM86_ARG(ret) == retarg)) अणु
		म_लिखो("[OK]\tReturned correctly\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[FAIL]\tIncorrect return reason (started at eip = 0x%lx, ended at eip = 0x%lx)\n", eip, v86->regs.eip);
		nerrs++;
	पूर्ण

	वापस true;
पूर्ण

व्योम करो_umip_tests(काष्ठा vm86plus_काष्ठा *vm86, अचिन्हित अक्षर *test_mem)
अणु
	काष्ठा table_desc अणु
		अचिन्हित लघु limit;
		अचिन्हित दीर्घ base;
	पूर्ण __attribute__((packed));

	/* Initialize variables with arbitrary values */
	काष्ठा table_desc gdt1 = अणु .base = 0x3c3c3c3c, .limit = 0x9999 पूर्ण;
	काष्ठा table_desc gdt2 = अणु .base = 0x1a1a1a1a, .limit = 0xaeae पूर्ण;
	काष्ठा table_desc idt1 = अणु .base = 0x7b7b7b7b, .limit = 0xf1f1 पूर्ण;
	काष्ठा table_desc idt2 = अणु .base = 0x89898989, .limit = 0x1313 पूर्ण;
	अचिन्हित लघु msw1 = 0x1414, msw2 = 0x2525, msw3 = 3737;

	/* UMIP -- निकास with INT3 unless kernel emulation did not trap #GP */
	करो_test(vm86, vmcode_umip - vmcode, VM86_TRAP, 3, "UMIP tests");

	/* Results from displacement-only addressing */
	msw1 = *(अचिन्हित लघु *)(test_mem + 2052);
	स_नकल(&idt1, test_mem + 2054, माप(idt1));
	स_नकल(&gdt1, test_mem + 2060, माप(gdt1));

	/* Results from रेजिस्टर-indirect addressing */
	msw2 = *(अचिन्हित लघु *)(test_mem + 2066);
	स_नकल(&idt2, test_mem + 2068, माप(idt2));
	स_नकल(&gdt2, test_mem + 2074, माप(gdt2));

	/* Results when using रेजिस्टर opeअक्रमs */
	msw3 = *(अचिन्हित लघु *)(test_mem + 2080);

	म_लिखो("[INFO]\tResult from SMSW:[0x%04x]\n", msw1);
	म_लिखो("[INFO]\tResult from SIDT: limit[0x%04x]base[0x%08lx]\n",
	       idt1.limit, idt1.base);
	म_लिखो("[INFO]\tResult from SGDT: limit[0x%04x]base[0x%08lx]\n",
	       gdt1.limit, gdt1.base);

	अगर (msw1 != msw2 || msw1 != msw3)
		म_लिखो("[FAIL]\tAll the results of SMSW should be the same.\n");
	अन्यथा
		म_लिखो("[PASS]\tAll the results from SMSW are identical.\n");

	अगर (स_भेद(&gdt1, &gdt2, माप(gdt1)))
		म_लिखो("[FAIL]\tAll the results of SGDT should be the same.\n");
	अन्यथा
		म_लिखो("[PASS]\tAll the results from SGDT are identical.\n");

	अगर (स_भेद(&idt1, &idt2, माप(idt1)))
		म_लिखो("[FAIL]\tAll the results of SIDT should be the same.\n");
	अन्यथा
		म_लिखो("[PASS]\tAll the results from SIDT are identical.\n");

	sethandler(संक_अवैध, sighandler, 0);
	करो_test(vm86, vmcode_umip_str - vmcode, VM86_SIGNAL, 0,
		"STR instruction");
	clearhandler(संक_अवैध);

	sethandler(संक_अवैध, sighandler, 0);
	करो_test(vm86, vmcode_umip_sldt - vmcode, VM86_SIGNAL, 0,
		"SLDT instruction");
	clearhandler(संक_अवैध);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा vm86plus_काष्ठा v86;
	अचिन्हित अक्षर *addr = mmap((व्योम *)load_addr, 4096,
				   PROT_READ | PROT_WRITE | PROT_EXEC,
				   MAP_ANONYMOUS | MAP_PRIVATE, -1,0);
	अगर (addr != (अचिन्हित अक्षर *)load_addr)
		err(1, "mmap");

	स_नकल(addr, vmcode, end_vmcode - vmcode);
	addr[2048] = 2;
	addr[2050] = 3;

	स_रखो(&v86, 0, माप(v86));

	v86.regs.cs = load_addr / 16;
	v86.regs.ss = load_addr / 16;
	v86.regs.ds = load_addr / 16;
	v86.regs.es = load_addr / 16;

	/* Use the end of the page as our stack. */
	v86.regs.esp = 4096;

	निश्चित((v86.regs.cs & 3) == 0);	/* Looks like RPL = 0 */

	/* #BR -- should deliver SIG??? */
	करो_test(&v86, vmcode_bound - vmcode, VM86_INTx, 5, "#BR");

	/*
	 * SYSENTER -- should cause #GP or #UD depending on CPU.
	 * Expected वापस type -1 means that we shouldn't validate
	 * the vm86 वापस value.  This will aव्योम problems on non-SEP
	 * CPUs.
	 */
	sethandler(संक_अवैध, sighandler, 0);
	करो_test(&v86, vmcode_sysenter - vmcode, -1, 0, "SYSENTER");
	clearhandler(संक_अवैध);

	/*
	 * SYSCALL would be a disaster in VM86 mode.  Fortunately,
	 * there is no kernel that both enables SYSCALL and sets
	 * EFER.SCE, so it's #UD on all प्रणालीs.  But vm86 is
	 * buggy (or has a "feature"), so the संक_अवैध will actually
	 * be delivered.
	 */
	sethandler(संक_अवैध, sighandler, 0);
	करो_test(&v86, vmcode_syscall - vmcode, VM86_SIGNAL, 0, "SYSCALL");
	clearhandler(संक_अवैध);

	/* STI with VIP set */
	v86.regs.eflags |= X86_EFLAGS_VIP;
	v86.regs.eflags &= ~X86_EFLAGS_IF;
	करो_test(&v86, vmcode_sti - vmcode, VM86_STI, 0, "STI with VIP set");

	/* POPF with VIP set but IF clear: should not trap */
	v86.regs.eflags = X86_EFLAGS_VIP;
	v86.regs.eax = 0;
	करो_test(&v86, vmcode_popf_hlt - vmcode, VM86_UNKNOWN, 0, "POPF with VIP set and IF clear");

	/* POPF with VIP set and IF set: should trap */
	v86.regs.eflags = X86_EFLAGS_VIP;
	v86.regs.eax = X86_EFLAGS_IF;
	करो_test(&v86, vmcode_popf_hlt - vmcode, VM86_STI, 0, "POPF with VIP and IF set");

	/* POPF with VIP clear and IF set: should not trap */
	v86.regs.eflags = 0;
	v86.regs.eax = X86_EFLAGS_IF;
	करो_test(&v86, vmcode_popf_hlt - vmcode, VM86_UNKNOWN, 0, "POPF with VIP clear and IF set");

	v86.regs.eflags = 0;

	/* INT3 -- should cause #BP */
	करो_test(&v86, vmcode_पूर्णांक3 - vmcode, VM86_TRAP, 3, "INT3");

	/* INT80 -- should निकास with "INTx 0x80" */
	v86.regs.eax = (अचिन्हित पूर्णांक)-1;
	करो_test(&v86, vmcode_पूर्णांक80 - vmcode, VM86_INTx, 0x80, "int80");

	/* UMIP -- should निकास with INTx 0x80 unless UMIP was not disabled */
	करो_umip_tests(&v86, addr);

	/* Execute a null poपूर्णांकer */
	v86.regs.cs = 0;
	v86.regs.ss = 0;
	sethandler(संक_अंश, sighandler, 0);
	got_संकेत = 0;
	अगर (करो_test(&v86, 0, VM86_SIGNAL, 0, "Execute null pointer") &&
	    !got_संकेत) अणु
		म_लिखो("[FAIL]\tDid not receive SIGSEGV\n");
		nerrs++;
	पूर्ण
	clearhandler(संक_अंश);

	/* Make sure nothing explodes अगर we विभाजन. */
	अगर (विभाजन() == 0)
		वापस 0;

	वापस (nerrs == 0 ? 0 : 1);
पूर्ण
