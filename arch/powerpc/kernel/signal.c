<शैली गुरु>
/*
 * Common संकेत handling code क्रम both 32 and 64 bits
 *
 *    Copyright (c) 2007 Benjamin Herrenschmidt, IBM Corporation
 *    Extracted from संकेत_32.c and संकेत_64.c
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file README.legal in the मुख्य directory of
 * this archive क्रम more details.
 */

#समावेश <linux/tracehook.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/uprobes.h>
#समावेश <linux/key.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/livepatch.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/पंचांग.h>

#समावेश "signal.h"

#अगर_घोषित CONFIG_VSX
अचिन्हित दीर्घ copy_fpr_to_user(व्योम __user *to,
			       काष्ठा task_काष्ठा *task)
अणु
	u64 buf[ELF_NFPREG];
	पूर्णांक i;

	/* save FPR copy to local buffer then ग_लिखो to the thपढ़ो_काष्ठा */
	क्रम (i = 0; i < (ELF_NFPREG - 1) ; i++)
		buf[i] = task->thपढ़ो.TS_FPR(i);
	buf[i] = task->thपढ़ो.fp_state.fpscr;
	वापस __copy_to_user(to, buf, ELF_NFPREG * माप(द्विगुन));
पूर्ण

अचिन्हित दीर्घ copy_fpr_from_user(काष्ठा task_काष्ठा *task,
				 व्योम __user *from)
अणु
	u64 buf[ELF_NFPREG];
	पूर्णांक i;

	अगर (__copy_from_user(buf, from, ELF_NFPREG * माप(द्विगुन)))
		वापस 1;
	क्रम (i = 0; i < (ELF_NFPREG - 1) ; i++)
		task->thपढ़ो.TS_FPR(i) = buf[i];
	task->thपढ़ो.fp_state.fpscr = buf[i];

	वापस 0;
पूर्ण

अचिन्हित दीर्घ copy_vsx_to_user(व्योम __user *to,
			       काष्ठा task_काष्ठा *task)
अणु
	u64 buf[ELF_NVSRHALFREG];
	पूर्णांक i;

	/* save FPR copy to local buffer then ग_लिखो to the thपढ़ो_काष्ठा */
	क्रम (i = 0; i < ELF_NVSRHALFREG; i++)
		buf[i] = task->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET];
	वापस __copy_to_user(to, buf, ELF_NVSRHALFREG * माप(द्विगुन));
पूर्ण

अचिन्हित दीर्घ copy_vsx_from_user(काष्ठा task_काष्ठा *task,
				 व्योम __user *from)
अणु
	u64 buf[ELF_NVSRHALFREG];
	पूर्णांक i;

	अगर (__copy_from_user(buf, from, ELF_NVSRHALFREG * माप(द्विगुन)))
		वापस 1;
	क्रम (i = 0; i < ELF_NVSRHALFREG ; i++)
		task->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET] = buf[i];
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
अचिन्हित दीर्घ copy_ckfpr_to_user(व्योम __user *to,
				  काष्ठा task_काष्ठा *task)
अणु
	u64 buf[ELF_NFPREG];
	पूर्णांक i;

	/* save FPR copy to local buffer then ग_लिखो to the thपढ़ो_काष्ठा */
	क्रम (i = 0; i < (ELF_NFPREG - 1) ; i++)
		buf[i] = task->thपढ़ो.TS_CKFPR(i);
	buf[i] = task->thपढ़ो.ckfp_state.fpscr;
	वापस __copy_to_user(to, buf, ELF_NFPREG * माप(द्विगुन));
पूर्ण

अचिन्हित दीर्घ copy_ckfpr_from_user(काष्ठा task_काष्ठा *task,
					  व्योम __user *from)
अणु
	u64 buf[ELF_NFPREG];
	पूर्णांक i;

	अगर (__copy_from_user(buf, from, ELF_NFPREG * माप(द्विगुन)))
		वापस 1;
	क्रम (i = 0; i < (ELF_NFPREG - 1) ; i++)
		task->thपढ़ो.TS_CKFPR(i) = buf[i];
	task->thपढ़ो.ckfp_state.fpscr = buf[i];

	वापस 0;
पूर्ण

अचिन्हित दीर्घ copy_ckvsx_to_user(व्योम __user *to,
				  काष्ठा task_काष्ठा *task)
अणु
	u64 buf[ELF_NVSRHALFREG];
	पूर्णांक i;

	/* save FPR copy to local buffer then ग_लिखो to the thपढ़ो_काष्ठा */
	क्रम (i = 0; i < ELF_NVSRHALFREG; i++)
		buf[i] = task->thपढ़ो.ckfp_state.fpr[i][TS_VSRLOWOFFSET];
	वापस __copy_to_user(to, buf, ELF_NVSRHALFREG * माप(द्विगुन));
पूर्ण

अचिन्हित दीर्घ copy_ckvsx_from_user(काष्ठा task_काष्ठा *task,
					  व्योम __user *from)
अणु
	u64 buf[ELF_NVSRHALFREG];
	पूर्णांक i;

	अगर (__copy_from_user(buf, from, ELF_NVSRHALFREG * माप(द्विगुन)))
		वापस 1;
	क्रम (i = 0; i < ELF_NVSRHALFREG ; i++)
		task->thपढ़ो.ckfp_state.fpr[i][TS_VSRLOWOFFSET] = buf[i];
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */
#पूर्ण_अगर

/* Log an error when sending an unhandled संकेत to a process. Controlled
 * through debug.exception-trace sysctl.
 */

पूर्णांक show_unhandled_संकेतs = 1;

/*
 * Allocate space क्रम the संकेत frame
 */
अटल अचिन्हित दीर्घ get_पंचांग_stackpoपूर्णांकer(काष्ठा task_काष्ठा *tsk);

व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा task_काष्ठा *tsk,
			  माप_प्रकार frame_size, पूर्णांक is_32)
अणु
        अचिन्हित दीर्घ oldsp, newsp;
	अचिन्हित दीर्घ sp = get_पंचांग_stackpoपूर्णांकer(tsk);

        /* Default to using normal stack */
	अगर (is_32)
		oldsp = sp & 0x0ffffffffUL;
	अन्यथा
		oldsp = sp;
	oldsp = sigsp(oldsp, ksig);
	newsp = (oldsp - frame_size) & ~0xFUL;

        वापस (व्योम __user *)newsp;
पूर्ण

अटल व्योम check_syscall_restart(काष्ठा pt_regs *regs, काष्ठा k_sigaction *ka,
				  पूर्णांक has_handler)
अणु
	अचिन्हित दीर्घ ret = regs->gpr[3];
	पूर्णांक restart = 1;

	/* syscall ? */
	अगर (!trap_is_syscall(regs))
		वापस;

	अगर (trap_norestart(regs))
		वापस;

	/* error संकेतled ? */
	अगर (trap_is_scv(regs)) अणु
		/* 32-bit compat mode sign extend? */
		अगर (!IS_ERR_VALUE(ret))
			वापस;
		ret = -ret;
	पूर्ण अन्यथा अगर (!(regs->ccr & 0x10000000)) अणु
		वापस;
	पूर्ण

	चयन (ret) अणु
	हाल ERESTART_RESTARTBLOCK:
	हाल ERESTARTNOHAND:
		/* ERESTARTNOHAND means that the syscall should only be
		 * restarted अगर there was no handler क्रम the संकेत, and since
		 * we only get here अगर there is a handler, we करोnt restart.
		 */
		restart = !has_handler;
		अवरोध;
	हाल ERESTARTSYS:
		/* ERESTARTSYS means to restart the syscall अगर there is no
		 * handler or the handler was रेजिस्टरed with SA_RESTART
		 */
		restart = !has_handler || (ka->sa.sa_flags & SA_RESTART) != 0;
		अवरोध;
	हाल ERESTARTNOINTR:
		/* ERESTARTNOINTR means that the syscall should be
		 * called again after the संकेत handler वापसs.
		 */
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	अगर (restart) अणु
		अगर (ret == ERESTART_RESTARTBLOCK)
			regs->gpr[0] = __NR_restart_syscall;
		अन्यथा
			regs->gpr[3] = regs->orig_gpr3;
		regs->nip -= 4;
		regs->result = 0;
	पूर्ण अन्यथा अणु
		अगर (trap_is_scv(regs)) अणु
			regs->result = -EINTR;
			regs->gpr[3] = -EINTR;
		पूर्ण अन्यथा अणु
			regs->result = -EINTR;
			regs->gpr[3] = EINTR;
			regs->ccr |= 0x10000000;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम करो_संकेत(काष्ठा task_काष्ठा *tsk)
अणु
	sigset_t *oldset = sigmask_to_save();
	काष्ठा kसंकेत ksig = अणु .sig = 0 पूर्ण;
	पूर्णांक ret;

	BUG_ON(tsk != current);

	get_संकेत(&ksig);

	/* Is there any syscall restart business here ? */
	check_syscall_restart(tsk->thपढ़ो.regs, &ksig.ka, ksig.sig > 0);

	अगर (ksig.sig <= 0) अणु
		/* No संकेत to deliver -- put the saved sigmask back */
		restore_saved_sigmask();
		set_trap_norestart(tsk->thपढ़ो.regs);
		वापस;               /* no संकेतs delivered */
	पूर्ण

        /*
	 * Reenable the DABR beक्रमe delivering the संकेत to
	 * user space. The DABR will have been cleared अगर it
	 * triggered inside the kernel.
	 */
	अगर (!IS_ENABLED(CONFIG_PPC_ADV_DEBUG_REGS)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nr_wp_slots(); i++) अणु
			अगर (tsk->thपढ़ो.hw_brk[i].address && tsk->thपढ़ो.hw_brk[i].type)
				__set_अवरोधpoपूर्णांक(i, &tsk->thपढ़ो.hw_brk[i]);
		पूर्ण
	पूर्ण

	/* Re-enable the अवरोधpoपूर्णांकs क्रम the संकेत stack */
	thपढ़ो_change_pc(tsk, tsk->thपढ़ो.regs);

	rseq_संकेत_deliver(&ksig, tsk->thपढ़ो.regs);

	अगर (is_32bit_task()) अणु
        	अगर (ksig.ka.sa.sa_flags & SA_SIGINFO)
			ret = handle_rt_संकेत32(&ksig, oldset, tsk);
		अन्यथा
			ret = handle_संकेत32(&ksig, oldset, tsk);
	पूर्ण अन्यथा अणु
		ret = handle_rt_संकेत64(&ksig, oldset, tsk);
	पूर्ण

	set_trap_norestart(tsk->thपढ़ो.regs);
	संकेत_setup_करोne(ret, &ksig, test_thपढ़ो_flag(TIF_SINGLESTEP));
पूर्ण

व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, अचिन्हित दीर्घ thपढ़ो_info_flags)
अणु
	अगर (thपढ़ो_info_flags & _TIF_UPROBE)
		uprobe_notअगरy_resume(regs);

	अगर (thपढ़ो_info_flags & _TIF_PATCH_PENDING)
		klp_update_patch_state(current);

	अगर (thपढ़ो_info_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL)) अणु
		BUG_ON(regs != current->thपढ़ो.regs);
		करो_संकेत(current);
	पूर्ण

	अगर (thपढ़ो_info_flags & _TIF_NOTIFY_RESUME) अणु
		tracehook_notअगरy_resume(regs);
		rseq_handle_notअगरy_resume(शून्य, regs);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ get_पंचांग_stackpoपूर्णांकer(काष्ठा task_काष्ठा *tsk)
अणु
	/* When in an active transaction that takes a संकेत, we need to be
	 * careful with the stack.  It's possible that the stack has moved back
	 * up after the tbegin.  The obvious हाल here is when the tbegin is
	 * called inside a function that वापसs beक्रमe a tend.  In this हाल,
	 * the stack is part of the checkpoपूर्णांकed transactional memory state.
	 * If we ग_लिखो over this non transactionally or in suspend, we are in
	 * trouble because अगर we get a पंचांग पात, the program counter and stack
	 * poपूर्णांकer will be back at the tbegin but our in memory stack won't be
	 * valid anymore.
	 *
	 * To aव्योम this, when taking a संकेत in an active transaction, we
	 * need to use the stack poपूर्णांकer from the checkpoपूर्णांकed state, rather
	 * than the speculated state.  This ensures that the संकेत context
	 * (written पंचांग suspended) will be written below the stack required क्रम
	 * the rollback.  The transaction is पातed because of the treclaim,
	 * so any memory written between the tbegin and the संकेत will be
	 * rolled back anyway.
	 *
	 * For संकेतs taken in non-TM or suspended mode, we use the
	 * normal/non-checkpoपूर्णांकed stack poपूर्णांकer.
	 */

	अचिन्हित दीर्घ ret = tsk->thपढ़ो.regs->gpr[1];

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	BUG_ON(tsk != current);

	अगर (MSR_TM_ACTIVE(tsk->thपढ़ो.regs->msr)) अणु
		preempt_disable();
		पंचांग_reclaim_current(TM_CAUSE_SIGNAL);
		अगर (MSR_TM_TRANSACTIONAL(tsk->thपढ़ो.regs->msr))
			ret = tsk->thपढ़ो.ckpt_regs.gpr[1];

		/*
		 * If we treclaim, we must clear the current thपढ़ो's TM bits
		 * beक्रमe re-enabling preemption. Otherwise we might be
		 * preempted and have the live MSR[TS] changed behind our back
		 * (पंचांग_recheckpoपूर्णांक_new_task() would recheckpoपूर्णांक). Besides, we
		 * enter the संकेत handler in non-transactional state.
		 */
		tsk->thपढ़ो.regs->msr &= ~MSR_TS_MASK;
		preempt_enable();
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल स्थिर अक्षर fm32[] = KERN_INFO "%s[%d]: bad frame in %s: %p nip %08lx lr %08lx\n";
अटल स्थिर अक्षर fm64[] = KERN_INFO "%s[%d]: bad frame in %s: %p nip %016lx lr %016lx\n";

व्योम संकेत_fault(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs,
		  स्थिर अक्षर *where, व्योम __user *ptr)
अणु
	अगर (show_unhandled_संकेतs)
		prपूर्णांकk_ratelimited(regs->msr & MSR_64BIT ? fm64 : fm32, tsk->comm,
				   task_pid_nr(tsk), where, ptr, regs->nip, regs->link);
पूर्ण
