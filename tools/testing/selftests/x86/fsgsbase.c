<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fsgsbase.c, an fsgsbase test
 * Copyright (c) 2014-2016 Andy Lutomirski
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>
#समावेश <err.h>
#समावेश <sys/user.h>
#समावेश <यंत्र/prctl.h>
#समावेश <sys/prctl.h>
#समावेश <संकेत.स>
#समावेश <सीमा.स>
#समावेश <sys/ucontext.h>
#समावेश <sched.h>
#समावेश <linux/futex.h>
#समावेश <pthपढ़ो.h>
#समावेश <यंत्र/ldt.h>
#समावेश <sys/mman.h>
#समावेश <मानकघोष.स>
#समावेश <sys/ptrace.h>
#समावेश <sys/रुको.h>
#समावेश <समलाँघ.स>

#अगर_अघोषित __x86_64__
# error This test is 64-bit only
#पूर्ण_अगर

अटल अस्थिर संक_पूर्ण_प्रकार want_segv;
अटल अस्थिर अचिन्हित दीर्घ segv_addr;

अटल अचिन्हित लघु *shared_scratch;

अटल पूर्णांक nerrs;

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

अटल व्योम sigsegv(पूर्णांक sig, siginfo_t *si, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;

	अगर (!want_segv) अणु
		clearhandler(संक_अंश);
		वापस;  /* Crash cleanly. */
	पूर्ण

	want_segv = false;
	segv_addr = (अचिन्हित दीर्घ)si->si_addr;

	ctx->uc_mcontext.gregs[REG_RIP] += 4;	/* Skip the faulting mov */

पूर्ण

अटल लाँघ_बफ jmpbuf;

अटल व्योम sigill(पूर्णांक sig, siginfo_t *si, व्योम *ctx_व्योम)
अणु
	sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

अटल bool have_fsgsbase;

अटल अंतरभूत अचिन्हित दीर्घ rdgsbase(व्योम)
अणु
	अचिन्हित दीर्घ gsbase;

	यंत्र अस्थिर("rdgsbase %0" : "=r" (gsbase) :: "memory");

	वापस gsbase;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ rdfsbase(व्योम)
अणु
	अचिन्हित दीर्घ fsbase;

	यंत्र अस्थिर("rdfsbase %0" : "=r" (fsbase) :: "memory");

	वापस fsbase;
पूर्ण

अटल अंतरभूत व्योम wrgsbase(अचिन्हित दीर्घ gsbase)
अणु
	यंत्र अस्थिर("wrgsbase %0" :: "r" (gsbase) : "memory");
पूर्ण

अटल अंतरभूत व्योम wrfsbase(अचिन्हित दीर्घ fsbase)
अणु
	यंत्र अस्थिर("wrfsbase %0" :: "r" (fsbase) : "memory");
पूर्ण

क्रमागत which_base अणु FS, GS पूर्ण;

अटल अचिन्हित दीर्घ पढ़ो_base(क्रमागत which_base which)
अणु
	अचिन्हित दीर्घ offset;
	/*
	 * Unless we have FSGSBASE, there's no direct way to करो this from
	 * user mode.  We can get at it indirectly using संकेतs, though.
	 */

	want_segv = true;

	offset = 0;
	अगर (which == FS) अणु
		/* Use a स्थिरant-length inकाष्ठाion here. */
		यंत्र अस्थिर ("mov %%fs:(%%rcx), %%rax" : : "c" (offset) : "rax");
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर ("mov %%gs:(%%rcx), %%rax" : : "c" (offset) : "rax");
	पूर्ण
	अगर (!want_segv)
		वापस segv_addr + offset;

	/*
	 * If that didn't segfault, try the other end of the address space.
	 * Unless we get really unlucky and run पूर्णांकo the vsyscall page, this
	 * is guaranteed to segfault.
	 */

	offset = (अच_दीर्घ_उच्च >> 1) + 1;
	अगर (which == FS) अणु
		यंत्र अस्थिर ("mov %%fs:(%%rcx), %%rax"
			      : : "c" (offset) : "rax");
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर ("mov %%gs:(%%rcx), %%rax"
			      : : "c" (offset) : "rax");
	पूर्ण
	अगर (!want_segv)
		वापस segv_addr + offset;

	पात();
पूर्ण

अटल व्योम check_gs_value(अचिन्हित दीर्घ value)
अणु
	अचिन्हित दीर्घ base;
	अचिन्हित लघु sel;

	म_लिखो("[RUN]\tARCH_SET_GS to 0x%lx\n", value);
	अगर (syscall(SYS_arch_prctl, ARCH_SET_GS, value) != 0)
		err(1, "ARCH_SET_GS");

	यंत्र अस्थिर ("mov %%gs, %0" : "=rm" (sel));
	base = पढ़ो_base(GS);
	अगर (base == value) अणु
		म_लिखो("[OK]\tGSBASE was set as expected (selector 0x%hx)\n",
		       sel);
	पूर्ण अन्यथा अणु
		nerrs++;
		म_लिखो("[FAIL]\tGSBASE was not as expected: got 0x%lx (selector 0x%hx)\n",
		       base, sel);
	पूर्ण

	अगर (syscall(SYS_arch_prctl, ARCH_GET_GS, &base) != 0)
		err(1, "ARCH_GET_GS");
	अगर (base == value) अणु
		म_लिखो("[OK]\tARCH_GET_GS worked as expected (selector 0x%hx)\n",
		       sel);
	पूर्ण अन्यथा अणु
		nerrs++;
		म_लिखो("[FAIL]\tARCH_GET_GS was not as expected: got 0x%lx (selector 0x%hx)\n",
		       base, sel);
	पूर्ण
पूर्ण

अटल व्योम mov_0_gs(अचिन्हित दीर्घ initial_base, bool schedule)
अणु
	अचिन्हित दीर्घ base, arch_base;

	म_लिखो("[RUN]\tARCH_SET_GS to 0x%lx then mov 0 to %%gs%s\n", initial_base, schedule ? " and schedule " : "");
	अगर (syscall(SYS_arch_prctl, ARCH_SET_GS, initial_base) != 0)
		err(1, "ARCH_SET_GS");

	अगर (schedule)
		usleep(10);

	यंत्र अस्थिर ("mov %0, %%gs" : : "rm" (0));
	base = पढ़ो_base(GS);
	अगर (syscall(SYS_arch_prctl, ARCH_GET_GS, &arch_base) != 0)
		err(1, "ARCH_GET_GS");
	अगर (base == arch_base) अणु
		म_लिखो("[OK]\tGSBASE is 0x%lx\n", base);
	पूर्ण अन्यथा अणु
		nerrs++;
		म_लिखो("[FAIL]\tGSBASE changed to 0x%lx but kernel reports 0x%lx\n", base, arch_base);
	पूर्ण
पूर्ण

अटल अस्थिर अचिन्हित दीर्घ remote_base;
अटल अस्थिर bool remote_hard_zero;
अटल अस्थिर अचिन्हित पूर्णांक ftx;

/*
 * ARCH_SET_FS/GS(0) may or may not program a selector of zero.  HARD_ZERO
 * means to क्रमce the selector to zero to improve test coverage.
 */
#घोषणा HARD_ZERO 0xa1fa5f343cb85fa4

अटल व्योम करो_remote_base()
अणु
	अचिन्हित दीर्घ to_set = remote_base;
	bool hard_zero = false;
	अगर (to_set == HARD_ZERO) अणु
		to_set = 0;
		hard_zero = true;
	पूर्ण

	अगर (syscall(SYS_arch_prctl, ARCH_SET_GS, to_set) != 0)
		err(1, "ARCH_SET_GS");

	अगर (hard_zero)
		यंत्र अस्थिर ("mov %0, %%gs" : : "rm" ((अचिन्हित लघु)0));

	अचिन्हित लघु sel;
	यंत्र अस्थिर ("mov %%gs, %0" : "=rm" (sel));
	म_लिखो("\tother thread: ARCH_SET_GS(0x%lx)%s -- sel is 0x%hx\n",
	       to_set, hard_zero ? " and clear gs" : "", sel);
पूर्ण

अटल __thपढ़ो पूर्णांक set_thपढ़ो_area_entry_number = -1;

अटल अचिन्हित लघु load_gs(व्योम)
अणु
	/*
	 * Sets GS != 0 and GSBASE != 0 but arranges क्रम the kernel to think
	 * that GSBASE == 0 (i.e. thपढ़ो.gsbase == 0).
	 */

	/* Step 1: tell the kernel that we have GSBASE == 0. */
	अगर (syscall(SYS_arch_prctl, ARCH_SET_GS, 0) != 0)
		err(1, "ARCH_SET_GS");

	/* Step 2: change GSBASE without telling the kernel. */
	काष्ठा user_desc desc = अणु
		.entry_number    = 0,
		.base_addr       = 0xBAADF00D,
		.limit           = 0xfffff,
		.seg_32bit       = 1,
		.contents        = 0, /* Data, grow-up */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 1,
		.seg_not_present = 0,
		.useable         = 0
	पूर्ण;
	अगर (syscall(SYS_modअगरy_ldt, 1, &desc, माप(desc)) == 0) अणु
		म_लिखो("\tusing LDT slot 0\n");
		यंत्र अस्थिर ("mov %0, %%gs" : : "rm" ((अचिन्हित लघु)0x7));
		वापस 0x7;
	पूर्ण अन्यथा अणु
		/* No modअगरy_ldt क्रम us (configured out, perhaps) */

		काष्ठा user_desc *low_desc = mmap(
			शून्य, माप(desc),
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
		स_नकल(low_desc, &desc, माप(desc));

		low_desc->entry_number = set_thपढ़ो_area_entry_number;

		/* 32-bit set_thपढ़ो_area */
		दीर्घ ret;
		यंत्र अस्थिर ("int $0x80"
			      : "=a" (ret), "+m" (*low_desc)
			      : "a" (243), "b" (low_desc)
			      : "r8", "r9", "r10", "r11");
		स_नकल(&desc, low_desc, माप(desc));
		munmap(low_desc, माप(desc));

		अगर (ret != 0) अणु
			म_लिखो("[NOTE]\tcould not create a segment -- test won't do anything\n");
			वापस 0;
		पूर्ण
		म_लिखो("\tusing GDT slot %d\n", desc.entry_number);
		set_thपढ़ो_area_entry_number = desc.entry_number;

		अचिन्हित लघु gs = (अचिन्हित लघु)((desc.entry_number << 3) | 0x3);
		यंत्र अस्थिर ("mov %0, %%gs" : : "rm" (gs));
		वापस gs;
	पूर्ण
पूर्ण

व्योम test_wrbase(अचिन्हित लघु index, अचिन्हित दीर्घ base)
अणु
	अचिन्हित लघु newindex;
	अचिन्हित दीर्घ newbase;

	म_लिखो("[RUN]\tGS = 0x%hx, GSBASE = 0x%lx\n", index, base);

	यंत्र अस्थिर ("mov %0, %%gs" : : "rm" (index));
	wrgsbase(base);

	remote_base = 0;
	ftx = 1;
	syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, शून्य, शून्य, 0);
	जबतक (ftx != 0)
		syscall(SYS_futex, &ftx, FUTEX_WAIT, 1, शून्य, शून्य, 0);

	यंत्र अस्थिर ("mov %%gs, %0" : "=rm" (newindex));
	newbase = rdgsbase();

	अगर (newindex == index && newbase == base) अणु
		म_लिखो("[OK]\tIndex and base were preserved\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[FAIL]\tAfter switch, GS = 0x%hx and GSBASE = 0x%lx\n",
		       newindex, newbase);
		nerrs++;
	पूर्ण
पूर्ण

अटल व्योम *thपढ़ोproc(व्योम *ctx)
अणु
	जबतक (1) अणु
		जबतक (ftx == 0)
			syscall(SYS_futex, &ftx, FUTEX_WAIT, 0, शून्य, शून्य, 0);
		अगर (ftx == 3)
			वापस शून्य;

		अगर (ftx == 1) अणु
			करो_remote_base();
		पूर्ण अन्यथा अगर (ftx == 2) अणु
			/*
			 * On AMD chips, this causes GSBASE != 0, GS == 0, and
			 * thपढ़ो.gsbase == 0.
			 */

			load_gs();
			यंत्र अस्थिर ("mov %0, %%gs" : : "rm" ((अचिन्हित लघु)0));
		पूर्ण अन्यथा अणु
			errx(1, "helper thread got bad command");
		पूर्ण

		ftx = 0;
		syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, शून्य, शून्य, 0);
	पूर्ण
पूर्ण

अटल व्योम set_gs_and_चयन_to(अचिन्हित दीर्घ local,
				 अचिन्हित लघु क्रमce_sel,
				 अचिन्हित दीर्घ remote)
अणु
	अचिन्हित दीर्घ base;
	अचिन्हित लघु sel_pre_sched, sel_post_sched;

	bool hard_zero = false;
	अगर (local == HARD_ZERO) अणु
		hard_zero = true;
		local = 0;
	पूर्ण

	म_लिखो("[RUN]\tARCH_SET_GS(0x%lx)%s, then schedule to 0x%lx\n",
	       local, hard_zero ? " and clear gs" : "", remote);
	अगर (क्रमce_sel)
		म_लिखो("\tBefore schedule, set selector to 0x%hx\n", क्रमce_sel);
	अगर (syscall(SYS_arch_prctl, ARCH_SET_GS, local) != 0)
		err(1, "ARCH_SET_GS");
	अगर (hard_zero)
		यंत्र अस्थिर ("mov %0, %%gs" : : "rm" ((अचिन्हित लघु)0));

	अगर (पढ़ो_base(GS) != local) अणु
		nerrs++;
		म_लिखो("[FAIL]\tGSBASE wasn't set as expected\n");
	पूर्ण

	अगर (क्रमce_sel) अणु
		यंत्र अस्थिर ("mov %0, %%gs" : : "rm" (क्रमce_sel));
		sel_pre_sched = क्रमce_sel;
		local = पढ़ो_base(GS);

		/*
		 * Signal delivery is quite likely to change a selector
		 * of 1, 2, or 3 back to 0 due to IRET being defective.
		 */
		यंत्र अस्थिर ("mov %0, %%gs" : : "rm" (क्रमce_sel));
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर ("mov %%gs, %0" : "=rm" (sel_pre_sched));
	पूर्ण

	remote_base = remote;
	ftx = 1;
	syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, शून्य, शून्य, 0);
	जबतक (ftx != 0)
		syscall(SYS_futex, &ftx, FUTEX_WAIT, 1, शून्य, शून्य, 0);

	यंत्र अस्थिर ("mov %%gs, %0" : "=rm" (sel_post_sched));
	base = पढ़ो_base(GS);
	अगर (base == local && sel_pre_sched == sel_post_sched) अणु
		म_लिखो("[OK]\tGS/BASE remained 0x%hx/0x%lx\n",
		       sel_pre_sched, local);
	पूर्ण अन्यथा अगर (base == local && sel_pre_sched >= 1 && sel_pre_sched <= 3 &&
		   sel_post_sched == 0) अणु
		/*
		 * IRET is misdeचिन्हित and will squash selectors 1, 2, or 3
		 * to zero.  Don't fail the test just because this happened.
		 */
		म_लिखो("[OK]\tGS/BASE changed from 0x%hx/0x%lx to 0x%hx/0x%lx because IRET is defective\n",
		       sel_pre_sched, local, sel_post_sched, base);
	पूर्ण अन्यथा अणु
		nerrs++;
		म_लिखो("[FAIL]\tGS/BASE changed from 0x%hx/0x%lx to 0x%hx/0x%lx\n",
		       sel_pre_sched, local, sel_post_sched, base);
	पूर्ण
पूर्ण

अटल व्योम test_unexpected_base(व्योम)
अणु
	अचिन्हित दीर्घ base;

	म_लिखो("[RUN]\tARCH_SET_GS(0), clear gs, then manipulate GSBASE in a different thread\n");
	अगर (syscall(SYS_arch_prctl, ARCH_SET_GS, 0) != 0)
		err(1, "ARCH_SET_GS");
	यंत्र अस्थिर ("mov %0, %%gs" : : "rm" ((अचिन्हित लघु)0));

	ftx = 2;
	syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, शून्य, शून्य, 0);
	जबतक (ftx != 0)
		syscall(SYS_futex, &ftx, FUTEX_WAIT, 1, शून्य, शून्य, 0);

	base = पढ़ो_base(GS);
	अगर (base == 0) अणु
		म_लिखो("[OK]\tGSBASE remained 0\n");
	पूर्ण अन्यथा अणु
		nerrs++;
		म_लिखो("[FAIL]\tGSBASE changed to 0x%lx\n", base);
	पूर्ण
पूर्ण

#घोषणा USER_REGS_OFFSET(r) दुरत्व(काष्ठा user_regs_काष्ठा, r)

अटल व्योम test_ptrace_ग_लिखो_gs_पढ़ो_base(व्योम)
अणु
	पूर्णांक status;
	pid_t child = विभाजन();

	अगर (child < 0)
		err(1, "fork");

	अगर (child == 0) अणु
		म_लिखो("[RUN]\tPTRACE_POKE GS, read GSBASE back\n");

		म_लिखो("[RUN]\tARCH_SET_GS to 1\n");
		अगर (syscall(SYS_arch_prctl, ARCH_SET_GS, 1) != 0)
			err(1, "ARCH_SET_GS");

		अगर (ptrace(PTRACE_TRACEME, 0, शून्य, शून्य) != 0)
			err(1, "PTRACE_TRACEME");

		उठाओ(SIGTRAP);
		_निकास(0);
	पूर्ण

	रुको(&status);

	अगर (WSTOPSIG(status) == SIGTRAP) अणु
		अचिन्हित दीर्घ base;
		अचिन्हित दीर्घ gs_offset = USER_REGS_OFFSET(gs);
		अचिन्हित दीर्घ base_offset = USER_REGS_OFFSET(gs_base);

		/* Read the initial base.  It should be 1. */
		base = ptrace(PTRACE_PEEKUSER, child, base_offset, शून्य);
		अगर (base == 1) अणु
			म_लिखो("[OK]\tGSBASE started at 1\n");
		पूर्ण अन्यथा अणु
			nerrs++;
			म_लिखो("[FAIL]\tGSBASE started at 0x%lx\n", base);
		पूर्ण

		म_लिखो("[RUN]\tSet GS = 0x7, read GSBASE\n");

		/* Poke an LDT selector पूर्णांकo GS. */
		अगर (ptrace(PTRACE_POKEUSER, child, gs_offset, 0x7) != 0)
			err(1, "PTRACE_POKEUSER");

		/* And पढ़ो the base. */
		base = ptrace(PTRACE_PEEKUSER, child, base_offset, शून्य);

		अगर (base == 0 || base == 1) अणु
			म_लिखो("[OK]\tGSBASE reads as 0x%lx with invalid GS\n", base);
		पूर्ण अन्यथा अणु
			nerrs++;
			म_लिखो("[FAIL]\tGSBASE=0x%lx (should be 0 or 1)\n", base);
		पूर्ण
	पूर्ण

	ptrace(PTRACE_CONT, child, शून्य, शून्य);

	रुको(&status);
	अगर (!WIFEXITED(status))
		म_लिखो("[WARN]\tChild didn't exit cleanly.\n");
पूर्ण

अटल व्योम test_ptrace_ग_लिखो_gsbase(व्योम)
अणु
	पूर्णांक status;
	pid_t child = विभाजन();

	अगर (child < 0)
		err(1, "fork");

	अगर (child == 0) अणु
		म_लिखो("[RUN]\tPTRACE_POKE(), write GSBASE from ptracer\n");

		*shared_scratch = load_gs();

		अगर (ptrace(PTRACE_TRACEME, 0, शून्य, शून्य) != 0)
			err(1, "PTRACE_TRACEME");

		उठाओ(SIGTRAP);
		_निकास(0);
	पूर्ण

	रुको(&status);

	अगर (WSTOPSIG(status) == SIGTRAP) अणु
		अचिन्हित दीर्घ gs, base;
		अचिन्हित दीर्घ gs_offset = USER_REGS_OFFSET(gs);
		अचिन्हित दीर्घ base_offset = USER_REGS_OFFSET(gs_base);

		gs = ptrace(PTRACE_PEEKUSER, child, gs_offset, शून्य);

		अगर (gs != *shared_scratch) अणु
			nerrs++;
			म_लिखो("[FAIL]\tGS is not prepared with nonzero\n");
			जाओ END;
		पूर्ण

		अगर (ptrace(PTRACE_POKEUSER, child, base_offset, 0xFF) != 0)
			err(1, "PTRACE_POKEUSER");

		gs = ptrace(PTRACE_PEEKUSER, child, gs_offset, शून्य);
		base = ptrace(PTRACE_PEEKUSER, child, base_offset, शून्य);

		/*
		 * In a non-FSGSBASE प्रणाली, the nonzero selector will load
		 * GSBASE (again). But what is tested here is whether the
		 * selector value is changed or not by the GSBASE ग_लिखो in
		 * a ptracer.
		 */
		अगर (gs != *shared_scratch) अणु
			nerrs++;
			म_लिखो("[FAIL]\tGS changed to %lx\n", gs);

			/*
			 * On older kernels, poking a nonzero value पूर्णांकo the
			 * base would zero the selector.  On newer kernels,
			 * this behavior has changed -- poking the base
			 * changes only the base and, अगर FSGSBASE is not
			 * available, this may have no effect once the tracee
			 * is resumed.
			 */
			अगर (gs == 0)
				म_लिखो("\tNote: this is expected behavior on older kernels.\n");
		पूर्ण अन्यथा अगर (have_fsgsbase && (base != 0xFF)) अणु
			nerrs++;
			म_लिखो("[FAIL]\tGSBASE changed to %lx\n", base);
		पूर्ण अन्यथा अणु
			म_लिखो("[OK]\tGS remained 0x%hx", *shared_scratch);
			अगर (have_fsgsbase)
				म_लिखो(" and GSBASE changed to 0xFF");
			म_लिखो("\n");
		पूर्ण
	पूर्ण

END:
	ptrace(PTRACE_CONT, child, शून्य, शून्य);
	रुको(&status);
	अगर (!WIFEXITED(status))
		म_लिखो("[WARN]\tChild didn't exit cleanly.\n");
पूर्ण

पूर्णांक मुख्य()
अणु
	pthपढ़ो_t thपढ़ो;

	shared_scratch = mmap(शून्य, 4096, PROT_READ | PROT_WRITE,
			      MAP_ANONYMOUS | MAP_SHARED, -1, 0);

	/* Do these tests beक्रमe we have an LDT. */
	test_ptrace_ग_लिखो_gs_पढ़ो_base();

	/* Probe FSGSBASE */
	sethandler(संक_अवैध, sigill, 0);
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		rdfsbase();
		have_fsgsbase = true;
		म_लिखो("\tFSGSBASE instructions are enabled\n");
	पूर्ण अन्यथा अणु
		म_लिखो("\tFSGSBASE instructions are disabled\n");
	पूर्ण
	clearhandler(संक_अवैध);

	sethandler(संक_अंश, sigsegv, 0);

	check_gs_value(0);
	check_gs_value(1);
	check_gs_value(0x200000000);
	check_gs_value(0);
	check_gs_value(0x200000000);
	check_gs_value(1);

	क्रम (पूर्णांक sched = 0; sched < 2; sched++) अणु
		mov_0_gs(0, !!sched);
		mov_0_gs(1, !!sched);
		mov_0_gs(0x200000000, !!sched);
	पूर्ण

	/* Set up क्रम multithपढ़ोing. */

	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	अगर (sched_setaffinity(0, माप(cpuset), &cpuset) != 0)
		err(1, "sched_setaffinity to CPU 0");	/* should never fail */

	अगर (pthपढ़ो_create(&thपढ़ो, 0, thपढ़ोproc, 0) != 0)
		err(1, "pthread_create");

	अटल अचिन्हित दीर्घ bases_with_hard_zero[] = अणु
		0, HARD_ZERO, 1, 0x200000000,
	पूर्ण;

	क्रम (पूर्णांक local = 0; local < 4; local++) अणु
		क्रम (पूर्णांक remote = 0; remote < 4; remote++) अणु
			क्रम (अचिन्हित लघु s = 0; s < 5; s++) अणु
				अचिन्हित लघु sel = s;
				अगर (s == 4)
					यंत्र ("mov %%ss, %0" : "=rm" (sel));
				set_gs_and_चयन_to(
					bases_with_hard_zero[local],
					sel,
					bases_with_hard_zero[remote]);
			पूर्ण
		पूर्ण
	पूर्ण

	test_unexpected_base();

	अगर (have_fsgsbase) अणु
		अचिन्हित लघु ss;

		यंत्र अस्थिर ("mov %%ss, %0" : "=rm" (ss));

		test_wrbase(0, 0);
		test_wrbase(0, 1);
		test_wrbase(0, 0x200000000);
		test_wrbase(0, 0xffffffffffffffff);
		test_wrbase(ss, 0);
		test_wrbase(ss, 1);
		test_wrbase(ss, 0x200000000);
		test_wrbase(ss, 0xffffffffffffffff);
	पूर्ण

	ftx = 3;  /* Kill the thपढ़ो. */
	syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, शून्य, शून्य, 0);

	अगर (pthपढ़ो_join(thपढ़ो, शून्य) != 0)
		err(1, "pthread_join");

	test_ptrace_ग_लिखो_gsbase();

	वापस nerrs == 0 ? 0 : 1;
पूर्ण
