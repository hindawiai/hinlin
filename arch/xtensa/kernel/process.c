<शैली गुरु>
/*
 * arch/xtensa/kernel/process.c
 *
 * Xtensa Processor version.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 *
 * Joe Taylor <joe@tensilica.com, joetylr@yahoo.com>
 * Chris Zankel <chris@zankel.net>
 * Marc Gauthier <marc@tensilica.com, marc@alumni.uwaterloo.ca>
 * Kevin Chea
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/elf.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/init.h>
#समावेश <linux/prctl.h>
#समावेश <linux/init_task.h>
#समावेश <linux/module.h>
#समावेश <linux/mqueue.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/rcupdate.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/platक्रमm.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/regs.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>

बाह्य व्योम ret_from_विभाजन(व्योम);
बाह्य व्योम ret_from_kernel_thपढ़ो(व्योम);

व्योम (*pm_घातer_off)(व्योम) = शून्य;
EXPORT_SYMBOL(pm_घातer_off);


#अगर_घोषित CONFIG_STACKPROTECTOR
#समावेश <linux/stackprotector.h>
अचिन्हित दीर्घ __stack_chk_guard __पढ़ो_mostly;
EXPORT_SYMBOL(__stack_chk_guard);
#पूर्ण_अगर

#अगर XTENSA_HAVE_COPROCESSORS

व्योम coprocessor_release_all(काष्ठा thपढ़ो_info *ti)
अणु
	अचिन्हित दीर्घ cpenable;
	पूर्णांक i;

	/* Make sure we करोn't चयन tasks during this operation. */

	preempt_disable();

	/* Walk through all cp owners and release it क्रम the requested one. */

	cpenable = ti->cpenable;

	क्रम (i = 0; i < XCHAL_CP_MAX; i++) अणु
		अगर (coprocessor_owner[i] == ti) अणु
			coprocessor_owner[i] = 0;
			cpenable &= ~(1 << i);
		पूर्ण
	पूर्ण

	ti->cpenable = cpenable;
	अगर (ti == current_thपढ़ो_info())
		xtensa_set_sr(0, cpenable);

	preempt_enable();
पूर्ण

व्योम coprocessor_flush_all(काष्ठा thपढ़ो_info *ti)
अणु
	अचिन्हित दीर्घ cpenable, old_cpenable;
	पूर्णांक i;

	preempt_disable();

	old_cpenable = xtensa_get_sr(cpenable);
	cpenable = ti->cpenable;
	xtensa_set_sr(cpenable, cpenable);

	क्रम (i = 0; i < XCHAL_CP_MAX; i++) अणु
		अगर ((cpenable & 1) != 0 && coprocessor_owner[i] == ti)
			coprocessor_flush(ti, i);
		cpenable >>= 1;
	पूर्ण
	xtensa_set_sr(old_cpenable, cpenable);

	preempt_enable();
पूर्ण

#पूर्ण_अगर


/*
 * Powermanagement idle function, अगर any is provided by the platक्रमm.
 */
व्योम arch_cpu_idle(व्योम)
अणु
	platक्रमm_idle();
पूर्ण

/*
 * This is called when the thपढ़ो calls निकास().
 */
व्योम निकास_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
#अगर XTENSA_HAVE_COPROCESSORS
	coprocessor_release_all(task_thपढ़ो_info(tsk));
#पूर्ण_अगर
पूर्ण

/*
 * Flush thपढ़ो state. This is called when a thपढ़ो करोes an execve()
 * Note that we flush coprocessor रेजिस्टरs क्रम the हाल execve fails.
 */
व्योम flush_thपढ़ो(व्योम)
अणु
#अगर XTENSA_HAVE_COPROCESSORS
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	coprocessor_flush_all(ti);
	coprocessor_release_all(ti);
#पूर्ण_अगर
	flush_ptrace_hw_अवरोधpoपूर्णांक(current);
पूर्ण

/*
 * this माला_लो called so that we can store coprocessor state पूर्णांकo memory and
 * copy the current task पूर्णांकo the new thपढ़ो.
 */
पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
#अगर XTENSA_HAVE_COPROCESSORS
	coprocessor_flush_all(task_thपढ़ो_info(src));
#पूर्ण_अगर
	*dst = *src;
	वापस 0;
पूर्ण

/*
 * Copy thपढ़ो.
 *
 * There are two modes in which this function is called:
 * 1) Userspace thपढ़ो creation,
 *    regs != शून्य, usp_thपढ़ो_fn is userspace stack poपूर्णांकer.
 *    It is expected to copy parent regs (in हाल CLONE_VM is not set
 *    in the clone_flags) and set up passed usp in the childregs.
 * 2) Kernel thपढ़ो creation,
 *    regs == शून्य, usp_thपढ़ो_fn is the function to run in the new thपढ़ो
 *    and thपढ़ो_fn_arg is its parameter.
 *    childregs are not used क्रम the kernel thपढ़ोs.
 *
 * The stack layout क्रम the new thपढ़ो looks like this:
 *
 *	+------------------------+
 *	|       childregs        |
 *	+------------------------+ <- thपढ़ो.sp = sp in dummy-frame
 *	|      dummy-frame       |    (saved in dummy-frame spill-area)
 *	+------------------------+
 *
 * We create a dummy frame to वापस to either ret_from_विभाजन or
 *   ret_from_kernel_thपढ़ो:
 *   a0 poपूर्णांकs to ret_from_विभाजन/ret_from_kernel_thपढ़ो (simulating a call4)
 *   sp poपूर्णांकs to itself (thपढ़ो.sp)
 *   a2, a3 are unused क्रम userspace thपढ़ोs,
 *   a2 poपूर्णांकs to thपढ़ो_fn, a3 holds thपढ़ो_fn arg क्रम kernel thपढ़ोs.
 *
 * Note: This is a pristine frame, so we करोn't need any spill region on top of
 *       childregs.
 *
 * The fun part:  अगर we're keeping the same VM (i.e. cloning a thपढ़ो,
 * not an entire process), we're normally given a new usp, and we CANNOT share
 * any live address रेजिस्टर winकरोws.  If we just copy those live frames over,
 * the two thपढ़ोs (parent and child) will overflow the same frames onto the
 * parent stack at dअगरferent बार, likely corrupting the parent stack (esp.
 * अगर the parent वापसs from functions that called clone() and calls new
 * ones, beक्रमe the child overflows its now old copies of its parent winकरोws).
 * One solution is to spill winकरोws to the parent stack, but that's fairly
 * involved.  Much simpler to just not copy those live frames across.
 */

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp_thपढ़ो_fn,
		अचिन्हित दीर्घ thपढ़ो_fn_arg, काष्ठा task_काष्ठा *p,
		अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *childregs = task_pt_regs(p);

#अगर (XTENSA_HAVE_COPROCESSORS || XTENSA_HAVE_IO_PORTS)
	काष्ठा thपढ़ो_info *ti;
#पूर्ण_अगर

	/* Create a call4 dummy-frame: a0 = 0, a1 = childregs. */
	SPILL_SLOT(childregs, 1) = (अचिन्हित दीर्घ)childregs;
	SPILL_SLOT(childregs, 0) = 0;

	p->thपढ़ो.sp = (अचिन्हित दीर्घ)childregs;

	अगर (!(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		काष्ठा pt_regs *regs = current_pt_regs();
		अचिन्हित दीर्घ usp = usp_thपढ़ो_fn ?
			usp_thपढ़ो_fn : regs->areg[1];

		p->thपढ़ो.ra = MAKE_RA_FOR_CALL(
				(अचिन्हित दीर्घ)ret_from_विभाजन, 0x1);

		/* This करोes not copy all the regs.
		 * In a bout of brilliance or madness,
		 * ARs beyond a0-a15 exist past the end of the काष्ठा.
		 */
		*childregs = *regs;
		childregs->areg[1] = usp;
		childregs->areg[2] = 0;

		/* When sharing memory with the parent thपढ़ो, the child
		   usually starts on a pristine stack, so we have to reset
		   winकरोwbase, winकरोwstart and wmask.
		   (Note that such a new thपढ़ो is required to always create
		   an initial call4 frame)
		   The exception is vविभाजन, where the new thपढ़ो जारीs to
		   run on the parent's stack until it calls execve. This could
		   be a call8 or call12, which requires a legal stack frame
		   of the previous caller क्रम the overflow handlers to work.
		   (Note that it's always legal to overflow live रेजिस्टरs).
		   In this हाल, ensure to spill at least the stack poपूर्णांकer
		   of that frame. */

		अगर (clone_flags & CLONE_VM) अणु
			/* check that caller winकरोw is live and same stack */
			पूर्णांक len = childregs->wmask & ~0xf;
			अगर (regs->areg[1] == usp && len != 0) अणु
				पूर्णांक callinc = (regs->areg[0] >> 30) & 3;
				पूर्णांक caller_ars = XCHAL_NUM_AREGS - callinc * 4;
				put_user(regs->areg[caller_ars+1],
					 (अचिन्हित __user*)(usp - 12));
			पूर्ण
			childregs->wmask = 1;
			childregs->winकरोwstart = 1;
			childregs->winकरोwbase = 0;
		पूर्ण अन्यथा अणु
			पूर्णांक len = childregs->wmask & ~0xf;
			स_नकल(&childregs->areg[XCHAL_NUM_AREGS - len/4],
			       &regs->areg[XCHAL_NUM_AREGS - len/4], len);
		पूर्ण

		childregs->syscall = regs->syscall;

		अगर (clone_flags & CLONE_SETTLS)
			childregs->thपढ़ोptr = tls;
	पूर्ण अन्यथा अणु
		p->thपढ़ो.ra = MAKE_RA_FOR_CALL(
				(अचिन्हित दीर्घ)ret_from_kernel_thपढ़ो, 1);

		/* pass parameters to ret_from_kernel_thपढ़ो:
		 * a2 = thपढ़ो_fn, a3 = thपढ़ो_fn arg
		 */
		SPILL_SLOT(childregs, 3) = thपढ़ो_fn_arg;
		SPILL_SLOT(childregs, 2) = usp_thपढ़ो_fn;

		/* Childregs are only used when we're going to userspace
		 * in which हाल start_thपढ़ो will set them up.
		 */
	पूर्ण

#अगर (XTENSA_HAVE_COPROCESSORS || XTENSA_HAVE_IO_PORTS)
	ti = task_thपढ़ो_info(p);
	ti->cpenable = 0;
#पूर्ण_अगर

	clear_ptrace_hw_अवरोधpoपूर्णांक(p);

	वापस 0;
पूर्ण


/*
 * These bracket the sleeping functions..
 */

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ sp, pc;
	अचिन्हित दीर्घ stack_page = (अचिन्हित दीर्घ) task_stack_page(p);
	पूर्णांक count = 0;

	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	sp = p->thपढ़ो.sp;
	pc = MAKE_PC_FROM_RA(p->thपढ़ो.ra, p->thपढ़ो.sp);

	करो अणु
		अगर (sp < stack_page + माप(काष्ठा task_काष्ठा) ||
		    sp >= (stack_page + THREAD_SIZE) ||
		    pc == 0)
			वापस 0;
		अगर (!in_sched_functions(pc))
			वापस pc;

		/* Stack layout: sp-4: ra, sp-3: sp' */

		pc = MAKE_PC_FROM_RA(SPILL_SLOT(sp, 0), sp);
		sp = SPILL_SLOT(sp, 1);
	पूर्ण जबतक (count++ < 16);
	वापस 0;
पूर्ण
