<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/चयन_to.h>

#समावेश "sigutil.h"

पूर्णांक save_fpu_state(काष्ठा pt_regs *regs, __siginfo_fpu_t __user *fpu)
अणु
	अचिन्हित दीर्घ *fpregs = current_thपढ़ो_info()->fpregs;
	अचिन्हित दीर्घ fprs;
	पूर्णांक err = 0;
	
	fprs = current_thपढ़ो_info()->fpsaved[0];
	अगर (fprs & FPRS_DL)
		err |= copy_to_user(&fpu->si_भग्न_regs[0], fpregs,
				    (माप(अचिन्हित पूर्णांक) * 32));
	अगर (fprs & FPRS_DU)
		err |= copy_to_user(&fpu->si_भग्न_regs[32], fpregs+16,
				    (माप(अचिन्हित पूर्णांक) * 32));
	err |= __put_user(current_thपढ़ो_info()->xfsr[0], &fpu->si_fsr);
	err |= __put_user(current_thपढ़ो_info()->gsr[0], &fpu->si_gsr);
	err |= __put_user(fprs, &fpu->si_fprs);

	वापस err;
पूर्ण

पूर्णांक restore_fpu_state(काष्ठा pt_regs *regs, __siginfo_fpu_t __user *fpu)
अणु
	अचिन्हित दीर्घ *fpregs = current_thपढ़ो_info()->fpregs;
	अचिन्हित दीर्घ fprs;
	पूर्णांक err;

	अगर (((अचिन्हित दीर्घ) fpu) & 7)
		वापस -EFAULT;

	err = get_user(fprs, &fpu->si_fprs);
	fprs_ग_लिखो(0);
	regs->tstate &= ~TSTATE_PEF;
	अगर (fprs & FPRS_DL)
		err |= copy_from_user(fpregs, &fpu->si_भग्न_regs[0],
		       	       (माप(अचिन्हित पूर्णांक) * 32));
	अगर (fprs & FPRS_DU)
		err |= copy_from_user(fpregs+16, &fpu->si_भग्न_regs[32],
		       	       (माप(अचिन्हित पूर्णांक) * 32));
	err |= __get_user(current_thपढ़ो_info()->xfsr[0], &fpu->si_fsr);
	err |= __get_user(current_thपढ़ो_info()->gsr[0], &fpu->si_gsr);
	current_thपढ़ो_info()->fpsaved[0] |= fprs;
	वापस err;
पूर्ण

पूर्णांक save_rwin_state(पूर्णांक wsaved, __siginfo_rwin_t __user *rwin)
अणु
	पूर्णांक i, err = __put_user(wsaved, &rwin->wsaved);

	क्रम (i = 0; i < wsaved; i++) अणु
		काष्ठा reg_winकरोw *rp = &current_thपढ़ो_info()->reg_winकरोw[i];
		अचिन्हित दीर्घ fp = current_thपढ़ो_info()->rwbuf_stkptrs[i];

		err |= copy_to_user(&rwin->reg_winकरोw[i], rp,
				    माप(काष्ठा reg_winकरोw));
		err |= __put_user(fp, &rwin->rwbuf_stkptrs[i]);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक restore_rwin_state(__siginfo_rwin_t __user *rp)
अणु
	काष्ठा thपढ़ो_info *t = current_thपढ़ो_info();
	पूर्णांक i, wsaved, err;

	अगर (((अचिन्हित दीर्घ) rp) & 7)
		वापस -EFAULT;

	get_user(wsaved, &rp->wsaved);
	अगर (wsaved > NSWINS)
		वापस -EFAULT;

	err = 0;
	क्रम (i = 0; i < wsaved; i++) अणु
		err |= copy_from_user(&t->reg_winकरोw[i],
				      &rp->reg_winकरोw[i],
				      माप(काष्ठा reg_winकरोw));
		err |= __get_user(t->rwbuf_stkptrs[i],
				  &rp->rwbuf_stkptrs[i]);
	पूर्ण
	अगर (err)
		वापस err;

	set_thपढ़ो_wsaved(wsaved);
	synchronize_user_stack();
	अगर (get_thपढ़ो_wsaved())
		वापस -EFAULT;
	वापस 0;
पूर्ण
