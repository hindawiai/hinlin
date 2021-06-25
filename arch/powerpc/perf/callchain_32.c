<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter callchain support - घातerpc architecture code
 *
 * Copyright तऊ 2009 Paul Mackerras, IBM Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/percpu.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/pte-walk.h>

#समावेश "callchain.h"

#अगर_घोषित CONFIG_PPC64
#समावेश "../kernel/ppc32.h"
#अन्यथा  /* CONFIG_PPC64 */

#घोषणा __SIGNAL_FRAMESIZE32	__SIGNAL_FRAMESIZE
#घोषणा sigcontext32		sigcontext
#घोषणा mcontext32		mcontext
#घोषणा ucontext32		ucontext
#घोषणा compat_siginfo_t	काष्ठा siginfo

#पूर्ण_अगर /* CONFIG_PPC64 */

अटल पूर्णांक पढ़ो_user_stack_32(स्थिर अचिन्हित पूर्णांक __user *ptr, अचिन्हित पूर्णांक *ret)
अणु
	वापस __पढ़ो_user_stack(ptr, ret, माप(*ret));
पूर्ण

/*
 * Layout क्रम non-RT संकेत frames
 */
काष्ठा संकेत_frame_32 अणु
	अक्षर			dummy[__SIGNAL_FRAMESIZE32];
	काष्ठा sigcontext32	sctx;
	काष्ठा mcontext32	mctx;
	पूर्णांक			abigap[56];
पूर्ण;

/*
 * Layout क्रम RT संकेत frames
 */
काष्ठा rt_संकेत_frame_32 अणु
	अक्षर			dummy[__SIGNAL_FRAMESIZE32 + 16];
	compat_siginfo_t	info;
	काष्ठा ucontext32	uc;
	पूर्णांक			abigap[56];
पूर्ण;

अटल पूर्णांक is_sigवापस_32_address(अचिन्हित पूर्णांक nip, अचिन्हित पूर्णांक fp)
अणु
	अगर (nip == fp + दुरत्व(काष्ठा संकेत_frame_32, mctx.mc_pad))
		वापस 1;
	अगर (current->mm->context.vdso &&
	    nip == VDSO32_SYMBOL(current->mm->context.vdso, sigtramp32))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक is_rt_sigवापस_32_address(अचिन्हित पूर्णांक nip, अचिन्हित पूर्णांक fp)
अणु
	अगर (nip == fp + दुरत्व(काष्ठा rt_संकेत_frame_32,
				 uc.uc_mcontext.mc_pad))
		वापस 1;
	अगर (current->mm->context.vdso &&
	    nip == VDSO32_SYMBOL(current->mm->context.vdso, sigtramp_rt32))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक sane_संकेत_32_frame(अचिन्हित पूर्णांक sp)
अणु
	काष्ठा संकेत_frame_32 __user *sf;
	अचिन्हित पूर्णांक regs;

	sf = (काष्ठा संकेत_frame_32 __user *) (अचिन्हित दीर्घ) sp;
	अगर (पढ़ो_user_stack_32((अचिन्हित पूर्णांक __user *) &sf->sctx.regs, &regs))
		वापस 0;
	वापस regs == (अचिन्हित दीर्घ) &sf->mctx;
पूर्ण

अटल पूर्णांक sane_rt_संकेत_32_frame(अचिन्हित पूर्णांक sp)
अणु
	काष्ठा rt_संकेत_frame_32 __user *sf;
	अचिन्हित पूर्णांक regs;

	sf = (काष्ठा rt_संकेत_frame_32 __user *) (अचिन्हित दीर्घ) sp;
	अगर (पढ़ो_user_stack_32((अचिन्हित पूर्णांक __user *) &sf->uc.uc_regs, &regs))
		वापस 0;
	वापस regs == (अचिन्हित दीर्घ) &sf->uc.uc_mcontext;
पूर्ण

अटल अचिन्हित पूर्णांक __user *संकेत_frame_32_regs(अचिन्हित पूर्णांक sp,
				अचिन्हित पूर्णांक next_sp, अचिन्हित पूर्णांक next_ip)
अणु
	काष्ठा mcontext32 __user *mctx = शून्य;
	काष्ठा संकेत_frame_32 __user *sf;
	काष्ठा rt_संकेत_frame_32 __user *rt_sf;

	/*
	 * Note: the next_sp - sp >= संकेत frame size check
	 * is true when next_sp < sp, क्रम example, when
	 * transitioning from an alternate संकेत stack to the
	 * normal stack.
	 */
	अगर (next_sp - sp >= माप(काष्ठा संकेत_frame_32) &&
	    is_sigवापस_32_address(next_ip, sp) &&
	    sane_संकेत_32_frame(sp)) अणु
		sf = (काष्ठा संकेत_frame_32 __user *) (अचिन्हित दीर्घ) sp;
		mctx = &sf->mctx;
	पूर्ण

	अगर (!mctx && next_sp - sp >= माप(काष्ठा rt_संकेत_frame_32) &&
	    is_rt_sigवापस_32_address(next_ip, sp) &&
	    sane_rt_संकेत_32_frame(sp)) अणु
		rt_sf = (काष्ठा rt_संकेत_frame_32 __user *) (अचिन्हित दीर्घ) sp;
		mctx = &rt_sf->uc.uc_mcontext;
	पूर्ण

	अगर (!mctx)
		वापस शून्य;
	वापस mctx->mc_gregs;
पूर्ण

व्योम perf_callchain_user_32(काष्ठा perf_callchain_entry_ctx *entry,
			    काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक sp, next_sp;
	अचिन्हित पूर्णांक next_ip;
	अचिन्हित पूर्णांक lr;
	दीर्घ level = 0;
	अचिन्हित पूर्णांक __user *fp, *uregs;

	next_ip = perf_inकाष्ठाion_poपूर्णांकer(regs);
	lr = regs->link;
	sp = regs->gpr[1];
	perf_callchain_store(entry, next_ip);

	जबतक (entry->nr < entry->max_stack) अणु
		fp = (अचिन्हित पूर्णांक __user *) (अचिन्हित दीर्घ) sp;
		अगर (invalid_user_sp(sp) || पढ़ो_user_stack_32(fp, &next_sp))
			वापस;
		अगर (level > 0 && पढ़ो_user_stack_32(&fp[1], &next_ip))
			वापस;

		uregs = संकेत_frame_32_regs(sp, next_sp, next_ip);
		अगर (!uregs && level <= 1)
			uregs = संकेत_frame_32_regs(sp, next_sp, lr);
		अगर (uregs) अणु
			/*
			 * This looks like an संकेत frame, so restart
			 * the stack trace with the values in it.
			 */
			अगर (पढ़ो_user_stack_32(&uregs[PT_NIP], &next_ip) ||
			    पढ़ो_user_stack_32(&uregs[PT_LNK], &lr) ||
			    पढ़ो_user_stack_32(&uregs[PT_R1], &sp))
				वापस;
			level = 0;
			perf_callchain_store_context(entry, PERF_CONTEXT_USER);
			perf_callchain_store(entry, next_ip);
			जारी;
		पूर्ण

		अगर (level == 0)
			next_ip = lr;
		perf_callchain_store(entry, next_ip);
		++level;
		sp = next_sp;
	पूर्ण
पूर्ण
