<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2002- 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <sched.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/रुको.h>
#समावेश <यंत्र/unistd.h>
#समावेश <as-layout.h>
#समावेश <init.h>
#समावेश <kern_util.h>
#समावेश <स्मृति.स>
#समावेश <os.h>
#समावेश <ptrace_user.h>
#समावेश <रेजिस्टरs.h>
#समावेश <skas.h>
#समावेश <sysdep/stub.h>
#समावेश <linux/thपढ़ोs.h>

पूर्णांक is_skas_winch(पूर्णांक pid, पूर्णांक fd, व्योम *data)
अणु
	वापस pid == getpgrp();
पूर्ण

अटल स्थिर अक्षर *ptrace_reg_name(पूर्णांक idx)
अणु
#घोषणा R(n) हाल HOST_##n: वापस #n

	चयन (idx) अणु
#अगर_घोषित __x86_64__
	R(BX);
	R(CX);
	R(DI);
	R(SI);
	R(DX);
	R(BP);
	R(AX);
	R(R8);
	R(R9);
	R(R10);
	R(R11);
	R(R12);
	R(R13);
	R(R14);
	R(R15);
	R(ORIG_AX);
	R(CS);
	R(SS);
	R(EFLAGS);
#या_अगर defined(__i386__)
	R(IP);
	R(SP);
	R(EFLAGS);
	R(AX);
	R(BX);
	R(CX);
	R(DX);
	R(SI);
	R(DI);
	R(BP);
	R(CS);
	R(SS);
	R(DS);
	R(FS);
	R(ES);
	R(GS);
	R(ORIG_AX);
#पूर्ण_अगर
	पूर्ण
	वापस "";
पूर्ण

अटल पूर्णांक ptrace_dump_regs(पूर्णांक pid)
अणु
	अचिन्हित दीर्घ regs[MAX_REG_NR];
	पूर्णांक i;

	अगर (ptrace(PTRACE_GETREGS, pid, 0, regs) < 0)
		वापस -त्रुटि_सं;

	prपूर्णांकk(UM_KERN_ERR "Stub registers -\n");
	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		स्थिर अक्षर *regname = ptrace_reg_name(i);

		prपूर्णांकk(UM_KERN_ERR "\t%s\t(%2d): %lx\n", regname, i, regs[i]);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Signals that are OK to receive in the stub - we'll just जारी it.
 * SIGWINCH will happen when UML is inside a detached screen.
 */
#घोषणा STUB_SIG_MASK ((1 << SIGALRM) | (1 << SIGWINCH))

/* Signals that the stub will finish with - anything अन्यथा is an error */
#घोषणा STUB_DONE_MASK (1 << SIGTRAP)

व्योम रुको_stub_करोne(पूर्णांक pid)
अणु
	पूर्णांक n, status, err;

	जबतक (1) अणु
		CATCH_EINTR(n = रुकोpid(pid, &status, WUNTRACED | __WALL));
		अगर ((n < 0) || !WIFSTOPPED(status))
			जाओ bad_रुको;

		अगर (((1 << WSTOPSIG(status)) & STUB_SIG_MASK) == 0)
			अवरोध;

		err = ptrace(PTRACE_CONT, pid, 0, 0);
		अगर (err) अणु
			prपूर्णांकk(UM_KERN_ERR "wait_stub_done : continue failed, "
			       "errno = %d\n", त्रुटि_सं);
			fatal_sigsegv();
		पूर्ण
	पूर्ण

	अगर (((1 << WSTOPSIG(status)) & STUB_DONE_MASK) != 0)
		वापस;

bad_रुको:
	err = ptrace_dump_regs(pid);
	अगर (err)
		prपूर्णांकk(UM_KERN_ERR "Failed to get registers from stub, "
		       "errno = %d\n", -err);
	prपूर्णांकk(UM_KERN_ERR "wait_stub_done : failed to wait for SIGTRAP, "
	       "pid = %d, n = %d, errno = %d, status = 0x%x\n", pid, n, त्रुटि_सं,
	       status);
	fatal_sigsegv();
पूर्ण

बाह्य अचिन्हित दीर्घ current_stub_stack(व्योम);

अटल व्योम get_skas_faultinfo(पूर्णांक pid, काष्ठा faultinfo *fi, अचिन्हित दीर्घ *aux_fp_regs)
अणु
	पूर्णांक err;

	err = get_fp_रेजिस्टरs(pid, aux_fp_regs);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "save_fp_registers returned %d\n",
		       err);
		fatal_sigsegv();
	पूर्ण
	err = ptrace(PTRACE_CONT, pid, 0, संक_अंश);
	अगर (err) अणु
		prपूर्णांकk(UM_KERN_ERR "Failed to continue stub, pid = %d, "
		       "errno = %d\n", pid, त्रुटि_सं);
		fatal_sigsegv();
	पूर्ण
	रुको_stub_करोne(pid);

	/*
	 * faultinfo is prepared by the stub_segv_handler at start of
	 * the stub stack page. We just have to copy it.
	 */
	स_नकल(fi, (व्योम *)current_stub_stack(), माप(*fi));

	err = put_fp_रेजिस्टरs(pid, aux_fp_regs);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "put_fp_registers returned %d\n",
		       err);
		fatal_sigsegv();
	पूर्ण
पूर्ण

अटल व्योम handle_segv(पूर्णांक pid, काष्ठा uml_pt_regs *regs, अचिन्हित दीर्घ *aux_fp_regs)
अणु
	get_skas_faultinfo(pid, &regs->faultinfo, aux_fp_regs);
	segv(regs->faultinfo, 0, 1, शून्य);
पूर्ण

/*
 * To use the same value of using_sysemu as the caller, ask it that value
 * (in local_using_sysemu
 */
अटल व्योम handle_trap(पूर्णांक pid, काष्ठा uml_pt_regs *regs,
			पूर्णांक local_using_sysemu)
अणु
	पूर्णांक err, status;

	अगर ((UPT_IP(regs) >= STUB_START) && (UPT_IP(regs) < STUB_END))
		fatal_sigsegv();

	अगर (!local_using_sysemu)
	अणु
		err = ptrace(PTRACE_POKEUSER, pid, PT_SYSCALL_NR_OFFSET,
			     __NR_getpid);
		अगर (err < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "handle_trap - nullifying syscall "
			       "failed, errno = %d\n", त्रुटि_सं);
			fatal_sigsegv();
		पूर्ण

		err = ptrace(PTRACE_SYSCALL, pid, 0, 0);
		अगर (err < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "handle_trap - continuing to end of "
			       "syscall failed, errno = %d\n", त्रुटि_सं);
			fatal_sigsegv();
		पूर्ण

		CATCH_EINTR(err = रुकोpid(pid, &status, WUNTRACED | __WALL));
		अगर ((err < 0) || !WIFSTOPPED(status) ||
		    (WSTOPSIG(status) != SIGTRAP + 0x80)) अणु
			err = ptrace_dump_regs(pid);
			अगर (err)
				prपूर्णांकk(UM_KERN_ERR "Failed to get registers "
				       "from process, errno = %d\n", -err);
			prपूर्णांकk(UM_KERN_ERR "handle_trap - failed to wait at "
			       "end of syscall, errno = %d, status = %d\n",
			       त्रुटि_सं, status);
			fatal_sigsegv();
		पूर्ण
	पूर्ण

	handle_syscall(regs);
पूर्ण

बाह्य अक्षर __syscall_stub_start[];

/**
 * userspace_tramp() - userspace trampoline
 * @stack:	poपूर्णांकer to the new userspace stack page, can be शून्य, अगर? FIXME:
 *
 * The userspace trampoline is used to setup a new userspace process in start_userspace() after it was clone()'ed.
 * This function will run on a temporary stack page.
 * It ptrace()'es itself, then
 * Two pages are mapped पूर्णांकo the userspace address space:
 * - STUB_CODE (with EXEC), which contains the skas stub code
 * - STUB_DATA (with R/W), which contains a data page that is used to transfer certain data between the UML userspace process and the UML kernel.
 * Also क्रम the userspace process a संक_अंश handler is installed to catch pagefaults in the userspace process.
 * And last the process stops itself to give control to the UML kernel क्रम this userspace process.
 *
 * Return: Always zero, otherwise the current userspace process is ended with non null निकास() call
 */
अटल पूर्णांक userspace_tramp(व्योम *stack)
अणु
	व्योम *addr;
	पूर्णांक fd;
	अचिन्हित दीर्घ दीर्घ offset;

	ptrace(PTRACE_TRACEME, 0, 0, 0);

	संकेत(संक_इति, संक_पूर्व);
	संकेत(SIGWINCH, संक_छोड़ो);

	fd = phys_mapping(to_phys(__syscall_stub_start), &offset);
	addr = mmap64((व्योम *) STUB_CODE, UM_KERN_PAGE_SIZE,
		      PROT_EXEC, MAP_FIXED | MAP_PRIVATE, fd, offset);
	अगर (addr == MAP_FAILED) अणु
		prपूर्णांकk(UM_KERN_ERR "mapping mmap stub at 0x%lx failed, "
		       "errno = %d\n", STUB_CODE, त्रुटि_सं);
		निकास(1);
	पूर्ण

	अगर (stack != शून्य) अणु
		fd = phys_mapping(to_phys(stack), &offset);
		addr = mmap((व्योम *) STUB_DATA,
			    UM_KERN_PAGE_SIZE, PROT_READ | PROT_WRITE,
			    MAP_FIXED | MAP_SHARED, fd, offset);
		अगर (addr == MAP_FAILED) अणु
			prपूर्णांकk(UM_KERN_ERR "mapping segfault stack "
			       "at 0x%lx failed, errno = %d\n",
			       STUB_DATA, त्रुटि_सं);
			निकास(1);
		पूर्ण
	पूर्ण
	अगर (stack != शून्य) अणु
		काष्ठा sigaction sa;

		अचिन्हित दीर्घ v = STUB_CODE +
				  (अचिन्हित दीर्घ) stub_segv_handler -
				  (अचिन्हित दीर्घ) __syscall_stub_start;

		set_sigstack((व्योम *) STUB_DATA, UM_KERN_PAGE_SIZE);
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_ONSTACK | SA_NODEFER | SA_SIGINFO;
		sa.sa_sigaction = (व्योम *) v;
		sa.sa_restorer = शून्य;
		अगर (sigaction(संक_अंश, &sa, शून्य) < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "userspace_tramp - setting SIGSEGV "
			       "handler failed - errno = %d\n", त्रुटि_सं);
			निकास(1);
		पूर्ण
	पूर्ण

	समाप्त(os_getpid(), SIGSTOP);
	वापस 0;
पूर्ण

पूर्णांक userspace_pid[NR_CPUS];
पूर्णांक समाप्त_userspace_mm[NR_CPUS];

/**
 * start_userspace() - prepare a new userspace process
 * @stub_stack:	poपूर्णांकer to the stub stack. Can be शून्य, अगर? FIXME:
 *
 * Setups a new temporary stack page that is used जबतक userspace_tramp() runs
 * Clones the kernel process पूर्णांकo a new userspace process, with FDs only.
 *
 * Return: When positive: the process id of the new userspace process,
 *         when negative: an error number.
 * FIXME: can PIDs become negative?!
 */
पूर्णांक start_userspace(अचिन्हित दीर्घ stub_stack)
अणु
	व्योम *stack;
	अचिन्हित दीर्घ sp;
	पूर्णांक pid, status, n, flags, err;

	/* setup a temporary stack page */
	stack = mmap(शून्य, UM_KERN_PAGE_SIZE,
		     PROT_READ | PROT_WRITE | PROT_EXEC,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	अगर (stack == MAP_FAILED) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "start_userspace : mmap failed, "
		       "errno = %d\n", त्रुटि_सं);
		वापस err;
	पूर्ण

	/* set stack poपूर्णांकer to the end of the stack page, so it can grow करोwnwards */
	sp = (अचिन्हित दीर्घ) stack + UM_KERN_PAGE_SIZE - माप(व्योम *);

	flags = CLONE_खाताS | SIGCHLD;

	/* clone पूर्णांकo new userspace process */
	pid = clone(userspace_tramp, (व्योम *) sp, flags, (व्योम *) stub_stack);
	अगर (pid < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "start_userspace : clone failed, "
		       "errno = %d\n", त्रुटि_सं);
		वापस err;
	पूर्ण

	करो अणु
		CATCH_EINTR(n = रुकोpid(pid, &status, WUNTRACED | __WALL));
		अगर (n < 0) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "start_userspace : wait failed, "
			       "errno = %d\n", त्रुटि_सं);
			जाओ out_समाप्त;
		पूर्ण
	पूर्ण जबतक (WIFSTOPPED(status) && (WSTOPSIG(status) == SIGALRM));

	अगर (!WIFSTOPPED(status) || (WSTOPSIG(status) != SIGSTOP)) अणु
		err = -EINVAL;
		prपूर्णांकk(UM_KERN_ERR "start_userspace : expected SIGSTOP, got "
		       "status = %d\n", status);
		जाओ out_समाप्त;
	पूर्ण

	अगर (ptrace(PTRACE_OLDSETOPTIONS, pid, शून्य,
		   (व्योम *) PTRACE_O_TRACESYSGOOD) < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "start_userspace : PTRACE_OLDSETOPTIONS "
		       "failed, errno = %d\n", त्रुटि_सं);
		जाओ out_समाप्त;
	पूर्ण

	अगर (munmap(stack, UM_KERN_PAGE_SIZE) < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "start_userspace : munmap failed, "
		       "errno = %d\n", त्रुटि_सं);
		जाओ out_समाप्त;
	पूर्ण

	वापस pid;

 out_समाप्त:
	os_समाप्त_ptraced_process(pid, 1);
	वापस err;
पूर्ण

व्योम userspace(काष्ठा uml_pt_regs *regs, अचिन्हित दीर्घ *aux_fp_regs)
अणु
	पूर्णांक err, status, op, pid = userspace_pid[0];
	/* To prevent races अगर using_sysemu changes under us.*/
	पूर्णांक local_using_sysemu;
	siginfo_t si;

	/* Handle any immediate reschedules or संकेतs */
	पूर्णांकerrupt_end();

	जबतक (1) अणु
		अगर (समाप्त_userspace_mm[0])
			fatal_sigsegv();

		/*
		 * This can legitimately fail अगर the process loads a
		 * bogus value पूर्णांकo a segment रेजिस्टर.  It will
		 * segfault and PTRACE_GETREGS will पढ़ो that value
		 * out of the process.  However, PTRACE_SETREGS will
		 * fail.  In this हाल, there is nothing to करो but
		 * just समाप्त the process.
		 */
		अगर (ptrace(PTRACE_SETREGS, pid, 0, regs->gp)) अणु
			prपूर्णांकk(UM_KERN_ERR "userspace - ptrace set regs "
			       "failed, errno = %d\n", त्रुटि_सं);
			fatal_sigsegv();
		पूर्ण

		अगर (put_fp_रेजिस्टरs(pid, regs->fp)) अणु
			prपूर्णांकk(UM_KERN_ERR "userspace - ptrace set fp regs "
			       "failed, errno = %d\n", त्रुटि_सं);
			fatal_sigsegv();
		पूर्ण

		/* Now we set local_using_sysemu to be used क्रम one loop */
		local_using_sysemu = get_using_sysemu();

		op = SELECT_PTRACE_OPERATION(local_using_sysemu,
					     singlestepping(शून्य));

		अगर (ptrace(op, pid, 0, 0)) अणु
			prपूर्णांकk(UM_KERN_ERR "userspace - ptrace continue "
			       "failed, op = %d, errno = %d\n", op, त्रुटि_सं);
			fatal_sigsegv();
		पूर्ण

		CATCH_EINTR(err = रुकोpid(pid, &status, WUNTRACED | __WALL));
		अगर (err < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "userspace - wait failed, "
			       "errno = %d\n", त्रुटि_सं);
			fatal_sigsegv();
		पूर्ण

		regs->is_user = 1;
		अगर (ptrace(PTRACE_GETREGS, pid, 0, regs->gp)) अणु
			prपूर्णांकk(UM_KERN_ERR "userspace - PTRACE_GETREGS failed, "
			       "errno = %d\n", त्रुटि_सं);
			fatal_sigsegv();
		पूर्ण

		अगर (get_fp_रेजिस्टरs(pid, regs->fp)) अणु
			prपूर्णांकk(UM_KERN_ERR "userspace -  get_fp_registers failed, "
			       "errno = %d\n", त्रुटि_सं);
			fatal_sigsegv();
		पूर्ण

		UPT_SYSCALL_NR(regs) = -1; /* Assume: It's not a syscall */

		अगर (WIFSTOPPED(status)) अणु
			पूर्णांक sig = WSTOPSIG(status);

			/* These संकेत handlers need the si argument.
			 * The SIGIO and SIGALARM handlers which स्थिरitute the
			 * majority of invocations, करो not use it.
			 */
			चयन (sig) अणु
			हाल संक_अंश:
			हाल SIGTRAP:
			हाल संक_अवैध:
			हाल SIGBUS:
			हाल संक_भ_त्रुटि:
			हाल SIGWINCH:
				ptrace(PTRACE_GETSIGINFO, pid, 0, (काष्ठा siginfo *)&si);
				अवरोध;
			पूर्ण

			चयन (sig) अणु
			हाल संक_अंश:
				अगर (PTRACE_FULL_FAULTINFO) अणु
					get_skas_faultinfo(pid,
							   &regs->faultinfo, aux_fp_regs);
					(*sig_info[संक_अंश])(संक_अंश, (काष्ठा siginfo *)&si,
							     regs);
				पूर्ण
				अन्यथा handle_segv(pid, regs, aux_fp_regs);
				अवरोध;
			हाल SIGTRAP + 0x80:
			        handle_trap(pid, regs, local_using_sysemu);
				अवरोध;
			हाल SIGTRAP:
				relay_संकेत(SIGTRAP, (काष्ठा siginfo *)&si, regs);
				अवरोध;
			हाल SIGALRM:
				अवरोध;
			हाल SIGIO:
			हाल संक_अवैध:
			हाल SIGBUS:
			हाल संक_भ_त्रुटि:
			हाल SIGWINCH:
				block_संकेतs_trace();
				(*sig_info[sig])(sig, (काष्ठा siginfo *)&si, regs);
				unblock_संकेतs_trace();
				अवरोध;
			शेष:
				prपूर्णांकk(UM_KERN_ERR "userspace - child stopped "
				       "with signal %d\n", sig);
				fatal_sigsegv();
			पूर्ण
			pid = userspace_pid[0];
			पूर्णांकerrupt_end();

			/* Aव्योम -ERESTARTSYS handling in host */
			अगर (PT_SYSCALL_NR_OFFSET != PT_SYSCALL_RET_OFFSET)
				PT_SYSCALL_NR(regs->gp) = -1;
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ thपढ़ो_regs[MAX_REG_NR];
अटल अचिन्हित दीर्घ thपढ़ो_fp_regs[FP_SIZE];

अटल पूर्णांक __init init_thपढ़ो_regs(व्योम)
अणु
	get_safe_रेजिस्टरs(thपढ़ो_regs, thपढ़ो_fp_regs);
	/* Set parent's inकाष्ठाion poपूर्णांकer to start of clone-stub */
	thपढ़ो_regs[REGS_IP_INDEX] = STUB_CODE +
				(अचिन्हित दीर्घ) stub_clone_handler -
				(अचिन्हित दीर्घ) __syscall_stub_start;
	thपढ़ो_regs[REGS_SP_INDEX] = STUB_DATA + UM_KERN_PAGE_SIZE -
		माप(व्योम *);
#अगर_घोषित __SIGNAL_FRAMESIZE
	thपढ़ो_regs[REGS_SP_INDEX] -= __SIGNAL_FRAMESIZE;
#पूर्ण_अगर
	वापस 0;
पूर्ण

__initcall(init_thपढ़ो_regs);

पूर्णांक copy_context_skas0(अचिन्हित दीर्घ new_stack, पूर्णांक pid)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ current_stack = current_stub_stack();
	काष्ठा stub_data *data = (काष्ठा stub_data *) current_stack;
	काष्ठा stub_data *child_data = (काष्ठा stub_data *) new_stack;
	अचिन्हित दीर्घ दीर्घ new_offset;
	पूर्णांक new_fd = phys_mapping(to_phys((व्योम *)new_stack), &new_offset);

	/*
	 * prepare offset and fd of child's stack as argument for parent's
	 * and child's mmap2 calls
	 */
	*data = ((काष्ठा stub_data) अणु
		.offset	= MMAP_OFFSET(new_offset),
		.fd     = new_fd,
		.parent_err = -ESRCH,
		.child_err = 0,
	पूर्ण);

	*child_data = ((काष्ठा stub_data) अणु
		.child_err = -ESRCH,
	पूर्ण);

	err = ptrace_setregs(pid, thपढ़ो_regs);
	अगर (err < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "copy_context_skas0 : PTRACE_SETREGS "
		       "failed, pid = %d, errno = %d\n", pid, -err);
		वापस err;
	पूर्ण

	err = put_fp_रेजिस्टरs(pid, thपढ़ो_fp_regs);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "copy_context_skas0 : put_fp_registers "
		       "failed, pid = %d, err = %d\n", pid, err);
		वापस err;
	पूर्ण

	/*
	 * Wait, until parent has finished its work: पढ़ो child's pid from
	 * parent's stack, and check, अगर bad result.
	 */
	err = ptrace(PTRACE_CONT, pid, 0, 0);
	अगर (err) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "Failed to continue new process, pid = %d, "
		       "errno = %d\n", pid, त्रुटि_सं);
		वापस err;
	पूर्ण

	रुको_stub_करोne(pid);

	pid = data->parent_err;
	अगर (pid < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "copy_context_skas0 - stub-parent reports "
		       "error %d\n", -pid);
		वापस pid;
	पूर्ण

	/*
	 * Wait, until child has finished too: पढ़ो child's result from
	 * child's stack and check it.
	 */
	रुको_stub_करोne(pid);
	अगर (child_data->child_err != STUB_DATA) अणु
		prपूर्णांकk(UM_KERN_ERR "copy_context_skas0 - stub-child %d reports "
		       "error %ld\n", pid, data->child_err);
		err = data->child_err;
		जाओ out_समाप्त;
	पूर्ण

	अगर (ptrace(PTRACE_OLDSETOPTIONS, pid, शून्य,
		   (व्योम *)PTRACE_O_TRACESYSGOOD) < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "copy_context_skas0 : PTRACE_OLDSETOPTIONS "
		       "failed, errno = %d\n", त्रुटि_सं);
		जाओ out_समाप्त;
	पूर्ण

	वापस pid;

 out_समाप्त:
	os_समाप्त_ptraced_process(pid, 1);
	वापस err;
पूर्ण

व्योम new_thपढ़ो(व्योम *stack, लाँघ_बफ *buf, व्योम (*handler)(व्योम))
अणु
	(*buf)[0].JB_IP = (अचिन्हित दीर्घ) handler;
	(*buf)[0].JB_SP = (अचिन्हित दीर्घ) stack + UM_THREAD_SIZE -
		माप(व्योम *);
पूर्ण

#घोषणा INIT_JMP_NEW_THREAD 0
#घोषणा INIT_JMP_CALLBACK 1
#घोषणा INIT_JMP_HALT 2
#घोषणा INIT_JMP_REBOOT 3

व्योम चयन_thपढ़ोs(लाँघ_बफ *me, लाँघ_बफ *you)
अणु
	अगर (UML_SETJMP(me) == 0)
		UML_LONGJMP(you, 1);
पूर्ण

अटल लाँघ_बफ initial_jmpbuf;

/* XXX Make these percpu */
अटल व्योम (*cb_proc)(व्योम *arg);
अटल व्योम *cb_arg;
अटल लाँघ_बफ *cb_back;

पूर्णांक start_idle_thपढ़ो(व्योम *stack, लाँघ_बफ *चयन_buf)
अणु
	पूर्णांक n;

	set_handler(SIGWINCH);

	/*
	 * Can't use UML_SETJMP or UML_LONGJMP here because they save
	 * and restore संकेतs, with the possible side-effect of
	 * trying to handle any संकेतs which came when they were
	 * blocked, which can't be करोne on this stack.
	 * Signals must be blocked when jumping back here and restored
	 * after वापसing to the jumper.
	 */
	n = बनाओ_लाँघ(initial_jmpbuf);
	चयन (n) अणु
	हाल INIT_JMP_NEW_THREAD:
		(*चयन_buf)[0].JB_IP = (अचिन्हित दीर्घ) uml_finishsetup;
		(*चयन_buf)[0].JB_SP = (अचिन्हित दीर्घ) stack +
			UM_THREAD_SIZE - माप(व्योम *);
		अवरोध;
	हाल INIT_JMP_CALLBACK:
		(*cb_proc)(cb_arg);
		दीर्घ_लाँघ(*cb_back, 1);
		अवरोध;
	हाल INIT_JMP_HALT:
		kदो_स्मृति_ok = 0;
		वापस 0;
	हाल INIT_JMP_REBOOT:
		kदो_स्मृति_ok = 0;
		वापस 1;
	शेष:
		prपूर्णांकk(UM_KERN_ERR "Bad sigsetjmp return in "
		       "start_idle_thread - %d\n", n);
		fatal_sigsegv();
	पूर्ण
	दीर्घ_लाँघ(*चयन_buf, 1);

	/* unreachable */
	prपूर्णांकk(UM_KERN_ERR "impossible long jump!");
	fatal_sigsegv();
	वापस 0;
पूर्ण

व्योम initial_thपढ़ो_cb_skas(व्योम (*proc)(व्योम *), व्योम *arg)
अणु
	लाँघ_बफ here;

	cb_proc = proc;
	cb_arg = arg;
	cb_back = &here;

	block_संकेतs_trace();
	अगर (UML_SETJMP(&here) == 0)
		UML_LONGJMP(&initial_jmpbuf, INIT_JMP_CALLBACK);
	unblock_संकेतs_trace();

	cb_proc = शून्य;
	cb_arg = शून्य;
	cb_back = शून्य;
पूर्ण

व्योम halt_skas(व्योम)
अणु
	block_संकेतs_trace();
	UML_LONGJMP(&initial_jmpbuf, INIT_JMP_HALT);
पूर्ण

व्योम reboot_skas(व्योम)
अणु
	block_संकेतs_trace();
	UML_LONGJMP(&initial_jmpbuf, INIT_JMP_REBOOT);
पूर्ण

व्योम __चयन_mm(काष्ठा mm_id *mm_idp)
अणु
	userspace_pid[0] = mm_idp->u.pid;
	समाप्त_userspace_mm[0] = mm_idp->समाप्त;
पूर्ण
