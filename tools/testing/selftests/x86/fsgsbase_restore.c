<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fsgsbase_restore.c, test ptrace vs fsgsbase
 * Copyright (c) 2020 Andy Lutomirski
 *
 * This test हाल simulates a tracer redirecting tracee execution to
 * a function and then restoring tracee state using PTRACE_GETREGS and
 * PTRACE_SETREGS.  This is similar to what gdb करोes when करोing
 * 'p func()'.  The catch is that this test has the called function
 * modअगरy a segment रेजिस्टर.  This makes sure that ptrace correctly
 * restores segment state when using PTRACE_SETREGS.
 *
 * This is not part of fsgsbase.c, because that test is 64-bit only.
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
#समावेश <यंत्र/ldt.h>
#समावेश <sys/mman.h>
#समावेश <मानकघोष.स>
#समावेश <sys/ptrace.h>
#समावेश <sys/रुको.h>
#समावेश <मानक_निवेशt.h>

#घोषणा EXPECTED_VALUE 0x1337f00d

#अगर_घोषित __x86_64__
# define SEG "%gs"
#अन्यथा
# define SEG "%fs"
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक dereference_seg_base(व्योम)
अणु
	पूर्णांक ret;
	यंत्र अस्थिर ("mov %" SEG ":(0), %0" : "=rm" (ret));
	वापस ret;
पूर्ण

अटल व्योम init_seg(व्योम)
अणु
	अचिन्हित पूर्णांक *target = mmap(
		शून्य, माप(अचिन्हित पूर्णांक),
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
	अगर (target == MAP_FAILED)
		err(1, "mmap");

	*target = EXPECTED_VALUE;

	म_लिखो("\tsegment base address = 0x%lx\n", (अचिन्हित दीर्घ)target);

	काष्ठा user_desc desc = अणु
		.entry_number    = 0,
		.base_addr       = (अचिन्हित पूर्णांक)(uपूर्णांकptr_t)target,
		.limit           = माप(अचिन्हित पूर्णांक) - 1,
		.seg_32bit       = 1,
		.contents        = 0, /* Data, grow-up */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 0,
		.useable         = 0
	पूर्ण;
	अगर (syscall(SYS_modअगरy_ldt, 1, &desc, माप(desc)) == 0) अणु
		म_लिखो("\tusing LDT slot 0\n");
		यंत्र अस्थिर ("mov %0, %" SEG :: "rm" ((अचिन्हित लघु)0x7));
	पूर्ण अन्यथा अणु
		/* No modअगरy_ldt क्रम us (configured out, perhaps) */

		काष्ठा user_desc *low_desc = mmap(
			शून्य, माप(desc),
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
		स_नकल(low_desc, &desc, माप(desc));

		low_desc->entry_number = -1;

		/* 32-bit set_thपढ़ो_area */
		दीर्घ ret;
		यंत्र अस्थिर ("int $0x80"
			      : "=a" (ret), "+m" (*low_desc)
			      : "a" (243), "b" (low_desc)
#अगर_घोषित __x86_64__
			      : "r8", "r9", "r10", "r11"
#पूर्ण_अगर
			);
		स_नकल(&desc, low_desc, माप(desc));
		munmap(low_desc, माप(desc));

		अगर (ret != 0) अणु
			म_लिखो("[NOTE]\tcould not create a segment -- can't test anything\n");
			निकास(0);
		पूर्ण
		म_लिखो("\tusing GDT slot %d\n", desc.entry_number);

		अचिन्हित लघु sel = (अचिन्हित लघु)((desc.entry_number << 3) | 0x3);
		यंत्र अस्थिर ("mov %0, %" SEG :: "rm" (sel));
	पूर्ण
पूर्ण

अटल व्योम tracee_zap_segment(व्योम)
अणु
	/*
	 * The tracer will redirect execution here.  This is meant to
	 * work like gdb's 'p func()' feature.  The tricky bit is that
	 * we modअगरy a segment रेजिस्टर in order to make sure that ptrace
	 * can correctly restore segment रेजिस्टरs.
	 */
	म_लिखो("\tTracee: in tracee_zap_segment()\n");

	/*
	 * Write a nonzero selector with base zero to the segment रेजिस्टर.
	 * Using a null selector would defeat the test on AMD pre-Zen2
	 * CPUs, as such CPUs करोn't clear the base when loading a null
	 * selector.
	 */
	अचिन्हित लघु sel;
	यंत्र अस्थिर ("mov %%ss, %0\n\t"
		      "mov %0, %" SEG
		      : "=rm" (sel));

	pid_t pid = getpid(), tid = syscall(SYS_gettid);

	म_लिखो("\tTracee is going back to sleep\n");
	syscall(SYS_tgसमाप्त, pid, tid, SIGSTOP);

	/* Should not get here. */
	जबतक (true) अणु
		म_लिखो("[FAIL]\tTracee hit unreachable code\n");
		छोड़ो();
	पूर्ण
पूर्ण

पूर्णांक मुख्य()
अणु
	म_लिखो("\tSetting up a segment\n");
	init_seg();

	अचिन्हित पूर्णांक val = dereference_seg_base();
	अगर (val != EXPECTED_VALUE) अणु
		म_लिखो("[FAIL]\tseg[0] == %x; should be %x\n", val, EXPECTED_VALUE);
		वापस 1;
	पूर्ण
	म_लिखो("[OK]\tThe segment points to the right place.\n");

	pid_t chld = विभाजन();
	अगर (chld < 0)
		err(1, "fork");

	अगर (chld == 0) अणु
		prctl(PR_SET_PDEATHSIG, SIGKILL, 0, 0, 0, 0);

		अगर (ptrace(PTRACE_TRACEME, 0, 0, 0) != 0)
			err(1, "PTRACE_TRACEME");

		pid_t pid = getpid(), tid = syscall(SYS_gettid);

		म_लिखो("\tTracee will take a nap until signaled\n");
		syscall(SYS_tgसमाप्त, pid, tid, SIGSTOP);

		म_लिखो("\tTracee was resumed.  Will re-check segment.\n");

		val = dereference_seg_base();
		अगर (val != EXPECTED_VALUE) अणु
			म_लिखो("[FAIL]\tseg[0] == %x; should be %x\n", val, EXPECTED_VALUE);
			निकास(1);
		पूर्ण

		म_लिखो("[OK]\tThe segment points to the right place.\n");
		निकास(0);
	पूर्ण

	पूर्णांक status;

	/* Wait क्रम SIGSTOP. */
	अगर (रुकोpid(chld, &status, 0) != chld || !WIFSTOPPED(status))
		err(1, "waitpid");

	काष्ठा user_regs_काष्ठा regs;

	अगर (ptrace(PTRACE_GETREGS, chld, शून्य, &regs) != 0)
		err(1, "PTRACE_GETREGS");

#अगर_घोषित __x86_64__
	म_लिखो("\tChild GS=0x%lx, GSBASE=0x%lx\n", (अचिन्हित दीर्घ)regs.gs, (अचिन्हित दीर्घ)regs.gs_base);
#अन्यथा
	म_लिखो("\tChild FS=0x%lx\n", (अचिन्हित दीर्घ)regs.xfs);
#पूर्ण_अगर

	काष्ठा user_regs_काष्ठा regs2 = regs;
#अगर_घोषित __x86_64__
	regs2.rip = (अचिन्हित दीर्घ)tracee_zap_segment;
	regs2.rsp -= 128;	/* Don't clobber the redzone. */
#अन्यथा
	regs2.eip = (अचिन्हित दीर्घ)tracee_zap_segment;
#पूर्ण_अगर

	म_लिखो("\tTracer: redirecting tracee to tracee_zap_segment()\n");
	अगर (ptrace(PTRACE_SETREGS, chld, शून्य, &regs2) != 0)
		err(1, "PTRACE_GETREGS");
	अगर (ptrace(PTRACE_CONT, chld, शून्य, शून्य) != 0)
		err(1, "PTRACE_GETREGS");

	/* Wait क्रम SIGSTOP. */
	अगर (रुकोpid(chld, &status, 0) != chld || !WIFSTOPPED(status))
		err(1, "waitpid");

	म_लिखो("\tTracer: restoring tracee state\n");
	अगर (ptrace(PTRACE_SETREGS, chld, शून्य, &regs) != 0)
		err(1, "PTRACE_GETREGS");
	अगर (ptrace(PTRACE_DETACH, chld, शून्य, शून्य) != 0)
		err(1, "PTRACE_GETREGS");

	/* Wait क्रम SIGSTOP. */
	अगर (रुकोpid(chld, &status, 0) != chld)
		err(1, "waitpid");

	अगर (WIFSIGNALED(status)) अणु
		म_लिखो("[FAIL]\tTracee crashed\n");
		वापस 1;
	पूर्ण

	अगर (!WIFEXITED(status)) अणु
		म_लिखो("[FAIL]\tTracee stopped for an unexpected reason: %d\n", status);
		वापस 1;
	पूर्ण

	पूर्णांक निकासcode = WEXITSTATUS(status);
	अगर (निकासcode != 0) अणु
		म_लिखो("[FAIL]\tTracee reported failure\n");
		वापस 1;
	पूर्ण

	म_लिखो("[OK]\tAll is well.\n");
	वापस 0;
पूर्ण
