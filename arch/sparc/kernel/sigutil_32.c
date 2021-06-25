<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/चयन_to.h>

#समावेश "sigutil.h"

पूर्णांक save_fpu_state(काष्ठा pt_regs *regs, __siginfo_fpu_t __user *fpu)
अणु
	पूर्णांक err = 0;
#अगर_घोषित CONFIG_SMP
	अगर (test_tsk_thपढ़ो_flag(current, TIF_USEDFPU)) अणु
		put_psr(get_psr() | PSR_EF);
		fpsave(&current->thपढ़ो.भग्न_regs[0], &current->thपढ़ो.fsr,
		       &current->thपढ़ो.fpqueue[0], &current->thपढ़ो.fpqdepth);
		regs->psr &= ~(PSR_EF);
		clear_tsk_thपढ़ो_flag(current, TIF_USEDFPU);
	पूर्ण
#अन्यथा
	अगर (current == last_task_used_math) अणु
		put_psr(get_psr() | PSR_EF);
		fpsave(&current->thपढ़ो.भग्न_regs[0], &current->thपढ़ो.fsr,
		       &current->thपढ़ो.fpqueue[0], &current->thपढ़ो.fpqdepth);
		last_task_used_math = शून्य;
		regs->psr &= ~(PSR_EF);
	पूर्ण
#पूर्ण_अगर
	err |= __copy_to_user(&fpu->si_भग्न_regs[0],
			      &current->thपढ़ो.भग्न_regs[0],
			      (माप(अचिन्हित दीर्घ) * 32));
	err |= __put_user(current->thपढ़ो.fsr, &fpu->si_fsr);
	err |= __put_user(current->thपढ़ो.fpqdepth, &fpu->si_fpqdepth);
	अगर (current->thपढ़ो.fpqdepth != 0)
		err |= __copy_to_user(&fpu->si_fpqueue[0],
				      &current->thपढ़ो.fpqueue[0],
				      ((माप(अचिन्हित दीर्घ) +
				      (माप(अचिन्हित दीर्घ *)))*16));
	clear_used_math();
	वापस err;
पूर्ण

पूर्णांक restore_fpu_state(काष्ठा pt_regs *regs, __siginfo_fpu_t __user *fpu)
अणु
	पूर्णांक err;

	अगर (((अचिन्हित दीर्घ) fpu) & 3)
		वापस -EFAULT;

#अगर_घोषित CONFIG_SMP
	अगर (test_tsk_thपढ़ो_flag(current, TIF_USEDFPU))
		regs->psr &= ~PSR_EF;
#अन्यथा
	अगर (current == last_task_used_math) अणु
		last_task_used_math = शून्य;
		regs->psr &= ~PSR_EF;
	पूर्ण
#पूर्ण_अगर
	set_used_math();
	clear_tsk_thपढ़ो_flag(current, TIF_USEDFPU);

	अगर (!access_ok(fpu, माप(*fpu)))
		वापस -EFAULT;

	err = __copy_from_user(&current->thपढ़ो.भग्न_regs[0], &fpu->si_भग्न_regs[0],
			       (माप(अचिन्हित दीर्घ) * 32));
	err |= __get_user(current->thपढ़ो.fsr, &fpu->si_fsr);
	err |= __get_user(current->thपढ़ो.fpqdepth, &fpu->si_fpqdepth);
	अगर (current->thपढ़ो.fpqdepth != 0)
		err |= __copy_from_user(&current->thपढ़ो.fpqueue[0],
					&fpu->si_fpqueue[0],
					((माप(अचिन्हित दीर्घ) +
					(माप(अचिन्हित दीर्घ *)))*16));
	वापस err;
पूर्ण

पूर्णांक save_rwin_state(पूर्णांक wsaved, __siginfo_rwin_t __user *rwin)
अणु
	पूर्णांक i, err = __put_user(wsaved, &rwin->wsaved);

	क्रम (i = 0; i < wsaved; i++) अणु
		काष्ठा reg_winकरोw32 *rp;
		अचिन्हित दीर्घ fp;

		rp = &current_thपढ़ो_info()->reg_winकरोw[i];
		fp = current_thपढ़ो_info()->rwbuf_stkptrs[i];
		err |= copy_to_user(&rwin->reg_winकरोw[i], rp,
				    माप(काष्ठा reg_winकरोw32));
		err |= __put_user(fp, &rwin->rwbuf_stkptrs[i]);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक restore_rwin_state(__siginfo_rwin_t __user *rp)
अणु
	काष्ठा thपढ़ो_info *t = current_thपढ़ो_info();
	पूर्णांक i, wsaved, err;

	अगर (((अचिन्हित दीर्घ) rp) & 3)
		वापस -EFAULT;

	get_user(wsaved, &rp->wsaved);
	अगर (wsaved > NSWINS)
		वापस -EFAULT;

	err = 0;
	क्रम (i = 0; i < wsaved; i++) अणु
		err |= copy_from_user(&t->reg_winकरोw[i],
				      &rp->reg_winकरोw[i],
				      माप(काष्ठा reg_winकरोw32));
		err |= __get_user(t->rwbuf_stkptrs[i],
				  &rp->rwbuf_stkptrs[i]);
	पूर्ण
	अगर (err)
		वापस err;

	t->w_saved = wsaved;
	synchronize_user_stack();
	अगर (t->w_saved)
		वापस -EFAULT;
	वापस 0;

पूर्ण
