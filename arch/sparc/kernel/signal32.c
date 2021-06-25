<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  arch/sparc64/kernel/संकेत32.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)
 *  Copyright (C) 1997 Eddie C. Dost   (ecd@skynet.be)
 *  Copyright (C) 1997,1998 Jakub Jelinek   (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/compat.h>
#समावेश <linux/bitops.h>
#समावेश <linux/tracehook.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/psrcompat.h>
#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/visयंत्र.h>
#समावेश <यंत्र/compat_संकेत.स>
#समावेश <यंत्र/चयन_to.h>

#समावेश "sigutil.h"
#समावेश "kernel.h"

/* This magic should be in g_upper[0] क्रम all upper parts
 * to be valid.
 */
#घोषणा SIGINFO_EXTRA_V8PLUS_MAGIC	0x130e269
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक g_upper[8];
	अचिन्हित पूर्णांक o_upper[8];
	अचिन्हित पूर्णांक asi;
पूर्ण siginfo_extra_v8plus_t;

काष्ठा संकेत_frame32 अणु
	काष्ठा sparc_stackf32	ss;
	__siginfo32_t		info;
	/* __siginfo_fpu_t * */ u32 fpu_save;
	अचिन्हित पूर्णांक		insns[2];
	अचिन्हित पूर्णांक		extramask[_COMPAT_NSIG_WORDS - 1];
	अचिन्हित पूर्णांक		extra_size; /* Should be माप(siginfo_extra_v8plus_t) */
	/* Only valid अगर (info.si_regs.psr & (PSR_VERS|PSR_IMPL)) == PSR_V8PLUS */
	siginfo_extra_v8plus_t	v8plus;
	/* __siginfo_rwin_t * */u32 rwin_save;
पूर्ण __attribute__((aligned(8)));

काष्ठा rt_संकेत_frame32 अणु
	काष्ठा sparc_stackf32	ss;
	compat_siginfo_t	info;
	काष्ठा pt_regs32	regs;
	compat_sigset_t		mask;
	/* __siginfo_fpu_t * */ u32 fpu_save;
	अचिन्हित पूर्णांक		insns[2];
	compat_stack_t		stack;
	अचिन्हित पूर्णांक		extra_size; /* Should be माप(siginfo_extra_v8plus_t) */
	/* Only valid अगर (regs.psr & (PSR_VERS|PSR_IMPL)) == PSR_V8PLUS */
	siginfo_extra_v8plus_t	v8plus;
	/* __siginfo_rwin_t * */u32 rwin_save;
पूर्ण __attribute__((aligned(8)));

/* Checks अगर the fp is valid.  We always build संकेत frames which are
 * 16-byte aligned, thereक्रमe we can always enक्रमce that the restore
 * frame has that property as well.
 */
अटल bool invalid_frame_poपूर्णांकer(व्योम __user *fp, पूर्णांक fplen)
अणु
	अगर ((((अचिन्हित दीर्घ) fp) & 15) ||
	    ((अचिन्हित दीर्घ)fp) > 0x100000000ULL - fplen)
		वापस true;
	वापस false;
पूर्ण

व्योम करो_sigवापस32(काष्ठा pt_regs *regs)
अणु
	काष्ठा संकेत_frame32 __user *sf;
	compat_uptr_t fpu_save;
	compat_uptr_t rwin_save;
	अचिन्हित पूर्णांक psr, ufp;
	अचिन्हित पूर्णांक pc, npc;
	sigset_t set;
	compat_sigset_t seta;
	पूर्णांक err, i;
	
	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	synchronize_user_stack();

	regs->u_regs[UREG_FP] &= 0x00000000ffffffffUL;
	sf = (काष्ठा संकेत_frame32 __user *) regs->u_regs[UREG_FP];

	/* 1. Make sure we are not getting garbage from the user */
	अगर (invalid_frame_poपूर्णांकer(sf, माप(*sf)))
		जाओ segv;

	अगर (get_user(ufp, &sf->info.si_regs.u_regs[UREG_FP]))
		जाओ segv;

	अगर (ufp & 0x7)
		जाओ segv;

	अगर (__get_user(pc, &sf->info.si_regs.pc) ||
	    __get_user(npc, &sf->info.si_regs.npc))
		जाओ segv;

	अगर ((pc | npc) & 3)
		जाओ segv;

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		pc &= 0xffffffff;
		npc &= 0xffffffff;
	पूर्ण
	regs->tpc = pc;
	regs->tnpc = npc;

	/* 2. Restore the state */
	err = __get_user(regs->y, &sf->info.si_regs.y);
	err |= __get_user(psr, &sf->info.si_regs.psr);

	क्रम (i = UREG_G1; i <= UREG_I7; i++)
		err |= __get_user(regs->u_regs[i], &sf->info.si_regs.u_regs[i]);
	अगर ((psr & (PSR_VERS|PSR_IMPL)) == PSR_V8PLUS) अणु
		err |= __get_user(i, &sf->v8plus.g_upper[0]);
		अगर (i == SIGINFO_EXTRA_V8PLUS_MAGIC) अणु
			अचिन्हित दीर्घ asi;

			क्रम (i = UREG_G1; i <= UREG_I7; i++)
				err |= __get_user(((u32 *)regs->u_regs)[2*i], &sf->v8plus.g_upper[i]);
			err |= __get_user(asi, &sf->v8plus.asi);
			regs->tstate &= ~TSTATE_ASI;
			regs->tstate |= ((asi & 0xffUL) << 24UL);
		पूर्ण
	पूर्ण

	/* User can only change condition codes in %tstate. */
	regs->tstate &= ~(TSTATE_ICC|TSTATE_XCC);
	regs->tstate |= psr_to_tstate_icc(psr);

	/* Prevent syscall restart.  */
	pt_regs_clear_syscall(regs);

	err |= __get_user(fpu_save, &sf->fpu_save);
	अगर (!err && fpu_save)
		err |= restore_fpu_state(regs, compat_ptr(fpu_save));
	err |= __get_user(rwin_save, &sf->rwin_save);
	अगर (!err && rwin_save) अणु
		अगर (restore_rwin_state(compat_ptr(rwin_save)))
			जाओ segv;
	पूर्ण
	err |= __get_user(seta.sig[0], &sf->info.si_mask);
	err |= copy_from_user(&seta.sig[1], &sf->extramask,
			      (_COMPAT_NSIG_WORDS - 1) * माप(अचिन्हित पूर्णांक));
	अगर (err)
	    	जाओ segv;

	set.sig[0] = seta.sig[0] + (((दीर्घ)seta.sig[1]) << 32);
	set_current_blocked(&set);
	वापस;

segv:
	क्रमce_sig(संक_अंश);
पूर्ण

यंत्रlinkage व्योम करो_rt_sigवापस32(काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_संकेत_frame32 __user *sf;
	अचिन्हित पूर्णांक psr, pc, npc, ufp;
	compat_uptr_t fpu_save;
	compat_uptr_t rwin_save;
	sigset_t set;
	पूर्णांक err, i;
	
	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	synchronize_user_stack();
	regs->u_regs[UREG_FP] &= 0x00000000ffffffffUL;
	sf = (काष्ठा rt_संकेत_frame32 __user *) regs->u_regs[UREG_FP];

	/* 1. Make sure we are not getting garbage from the user */
	अगर (invalid_frame_poपूर्णांकer(sf, माप(*sf)))
		जाओ segv;

	अगर (get_user(ufp, &sf->regs.u_regs[UREG_FP]))
		जाओ segv;

	अगर (ufp & 0x7)
		जाओ segv;

	अगर (__get_user(pc, &sf->regs.pc) || 
	    __get_user(npc, &sf->regs.npc))
		जाओ segv;

	अगर ((pc | npc) & 3)
		जाओ segv;

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		pc &= 0xffffffff;
		npc &= 0xffffffff;
	पूर्ण
	regs->tpc = pc;
	regs->tnpc = npc;

	/* 2. Restore the state */
	err = __get_user(regs->y, &sf->regs.y);
	err |= __get_user(psr, &sf->regs.psr);
	
	क्रम (i = UREG_G1; i <= UREG_I7; i++)
		err |= __get_user(regs->u_regs[i], &sf->regs.u_regs[i]);
	अगर ((psr & (PSR_VERS|PSR_IMPL)) == PSR_V8PLUS) अणु
		err |= __get_user(i, &sf->v8plus.g_upper[0]);
		अगर (i == SIGINFO_EXTRA_V8PLUS_MAGIC) अणु
			अचिन्हित दीर्घ asi;

			क्रम (i = UREG_G1; i <= UREG_I7; i++)
				err |= __get_user(((u32 *)regs->u_regs)[2*i], &sf->v8plus.g_upper[i]);
			err |= __get_user(asi, &sf->v8plus.asi);
			regs->tstate &= ~TSTATE_ASI;
			regs->tstate |= ((asi & 0xffUL) << 24UL);
		पूर्ण
	पूर्ण

	/* User can only change condition codes in %tstate. */
	regs->tstate &= ~(TSTATE_ICC|TSTATE_XCC);
	regs->tstate |= psr_to_tstate_icc(psr);

	/* Prevent syscall restart.  */
	pt_regs_clear_syscall(regs);

	err |= __get_user(fpu_save, &sf->fpu_save);
	अगर (!err && fpu_save)
		err |= restore_fpu_state(regs, compat_ptr(fpu_save));
	err |= get_compat_sigset(&set, &sf->mask);
	err |= compat_restore_altstack(&sf->stack);
	अगर (err)
		जाओ segv;
		
	err |= __get_user(rwin_save, &sf->rwin_save);
	अगर (!err && rwin_save) अणु
		अगर (restore_rwin_state(compat_ptr(rwin_save)))
			जाओ segv;
	पूर्ण

	set_current_blocked(&set);
	वापस;
segv:
	क्रमce_sig(संक_अंश);
पूर्ण

अटल व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs, अचिन्हित दीर्घ framesize)
अणु
	अचिन्हित दीर्घ sp;
	
	regs->u_regs[UREG_FP] &= 0x00000000ffffffffUL;
	sp = regs->u_regs[UREG_FP];
	
	/*
	 * If we are on the alternate संकेत stack and would overflow it, करोn't.
	 * Return an always-bogus address instead so we will die with संक_अंश.
	 */
	अगर (on_sig_stack(sp) && !likely(on_sig_stack(sp - framesize)))
		वापस (व्योम __user *) -1L;

	/* This is the X/Open sanctioned संकेत stack चयनing.  */
	sp = sigsp(sp, ksig) - framesize;

	/* Always align the stack frame.  This handles two हालs.  First,
	 * sigaltstack need not be mindful of platक्रमm specअगरic stack
	 * alignment.  Second, अगर we took this संकेत because the stack
	 * is not aligned properly, we'd like to take the संकेत cleanly
	 * and report that.
	 */
	sp &= ~15UL;

	वापस (व्योम __user *) sp;
पूर्ण

/* The I-cache flush inकाष्ठाion only works in the primary ASI, which
 * right now is the nucleus, aka. kernel space.
 *
 * Thereक्रमe we have to kick the inकाष्ठाions out using the kernel
 * side linear mapping of the physical address backing the user
 * inकाष्ठाions.
 */
अटल व्योम flush_संकेत_insns(अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ pstate, paddr;
	pte_t *ptep, pte;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;

	/* Commit all stores of the inकाष्ठाions we are about to flush.  */
	wmb();

	/* Disable cross-call reception.  In this way even a very wide
	 * munmap() on another cpu can't tear करोwn the page table
	 * hierarchy from underneath us, since that can't complete
	 * until the IPI tlb flush वापसs.
	 */

	__यंत्र__ __अस्थिर__("rdpr %%pstate, %0" : "=r" (pstate));
	__यंत्र__ __अस्थिर__("wrpr %0, %1, %%pstate"
				: : "r" (pstate), "i" (PSTATE_IE));

	pgdp = pgd_offset(current->mm, address);
	अगर (pgd_none(*pgdp))
		जाओ out_irqs_on;
	p4dp = p4d_offset(pgdp, address);
	अगर (p4d_none(*p4dp))
		जाओ out_irqs_on;
	pudp = pud_offset(p4dp, address);
	अगर (pud_none(*pudp))
		जाओ out_irqs_on;
	pmdp = pmd_offset(pudp, address);
	अगर (pmd_none(*pmdp))
		जाओ out_irqs_on;

	ptep = pte_offset_map(pmdp, address);
	pte = *ptep;
	अगर (!pte_present(pte))
		जाओ out_unmap;

	paddr = (अचिन्हित दीर्घ) page_address(pte_page(pte));

	__यंत्र__ __अस्थिर__("flush	%0 + %1"
			     : /* no outमाला_दो */
			     : "r" (paddr),
			       "r" (address & (PAGE_SIZE - 1))
			     : "memory");

out_unmap:
	pte_unmap(ptep);
out_irqs_on:
	__यंत्र__ __अस्थिर__("wrpr %0, 0x0, %%pstate" : : "r" (pstate));

पूर्ण

अटल पूर्णांक setup_frame32(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs,
			 sigset_t *oldset)
अणु
	काष्ठा संकेत_frame32 __user *sf;
	पूर्णांक i, err, wsaved;
	व्योम __user *tail;
	पूर्णांक sigframe_size;
	u32 psr;
	compat_sigset_t seta;

	/* 1. Make sure everything is clean */
	synchronize_user_stack();
	save_and_clear_fpu();
	
	wsaved = get_thपढ़ो_wsaved();

	sigframe_size = माप(*sf);
	अगर (current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF)
		sigframe_size += माप(__siginfo_fpu_t);
	अगर (wsaved)
		sigframe_size += माप(__siginfo_rwin_t);

	sf = (काष्ठा संकेत_frame32 __user *)
		get_sigframe(ksig, regs, sigframe_size);
	
	अगर (invalid_frame_poपूर्णांकer(sf, sigframe_size)) अणु
		अगर (show_unhandled_संकेतs)
			pr_info("%s[%d] bad frame in setup_frame32: %08lx TPC %08lx O7 %08lx\n",
				current->comm, current->pid, (अचिन्हित दीर्घ)sf,
				regs->tpc, regs->u_regs[UREG_I7]);
		क्रमce_sigsegv(ksig->sig);
		वापस -EINVAL;
	पूर्ण

	tail = (sf + 1);

	/* 2. Save the current process state */
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	err  = put_user(regs->tpc, &sf->info.si_regs.pc);
	err |= __put_user(regs->tnpc, &sf->info.si_regs.npc);
	err |= __put_user(regs->y, &sf->info.si_regs.y);
	psr = tstate_to_psr(regs->tstate);
	अगर (current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF)
		psr |= PSR_EF;
	err |= __put_user(psr, &sf->info.si_regs.psr);
	क्रम (i = 0; i < 16; i++)
		err |= __put_user(regs->u_regs[i], &sf->info.si_regs.u_regs[i]);
	err |= __put_user(माप(siginfo_extra_v8plus_t), &sf->extra_size);
	err |= __put_user(SIGINFO_EXTRA_V8PLUS_MAGIC, &sf->v8plus.g_upper[0]);
	क्रम (i = 1; i < 16; i++)
		err |= __put_user(((u32 *)regs->u_regs)[2*i],
				  &sf->v8plus.g_upper[i]);
	err |= __put_user((regs->tstate & TSTATE_ASI) >> 24UL,
			  &sf->v8plus.asi);

	अगर (psr & PSR_EF) अणु
		__siginfo_fpu_t __user *fp = tail;
		tail += माप(*fp);
		err |= save_fpu_state(regs, fp);
		err |= __put_user((u64)fp, &sf->fpu_save);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->fpu_save);
	पूर्ण
	अगर (wsaved) अणु
		__siginfo_rwin_t __user *rwp = tail;
		tail += माप(*rwp);
		err |= save_rwin_state(wsaved, rwp);
		err |= __put_user((u64)rwp, &sf->rwin_save);
		set_thपढ़ो_wsaved(0);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->rwin_save);
	पूर्ण

	/* If these change we need to know - assignments to seta relies on these sizes */
	BUILD_BUG_ON(_NSIG_WORDS != 1);
	BUILD_BUG_ON(_COMPAT_NSIG_WORDS != 2);
	seta.sig[1] = (oldset->sig[0] >> 32);
	seta.sig[0] = oldset->sig[0];

	err |= __put_user(seta.sig[0], &sf->info.si_mask);
	err |= __copy_to_user(sf->extramask, &seta.sig[1],
			      (_COMPAT_NSIG_WORDS - 1) * माप(अचिन्हित पूर्णांक));

	अगर (!wsaved) अणु
		err |= copy_in_user((u32 __user *)sf,
				    (u32 __user *)(regs->u_regs[UREG_FP]),
				    माप(काष्ठा reg_winकरोw32));
	पूर्ण अन्यथा अणु
		काष्ठा reg_winकरोw *rp;

		rp = &current_thपढ़ो_info()->reg_winकरोw[wsaved - 1];
		क्रम (i = 0; i < 8; i++)
			err |= __put_user(rp->locals[i], &sf->ss.locals[i]);
		क्रम (i = 0; i < 6; i++)
			err |= __put_user(rp->ins[i], &sf->ss.ins[i]);
		err |= __put_user(rp->ins[6], &sf->ss.fp);
		err |= __put_user(rp->ins[7], &sf->ss.callers_pc);
	पूर्ण	
	अगर (err)
		वापस err;

	/* 3. संकेत handler back-trampoline and parameters */
	regs->u_regs[UREG_FP] = (अचिन्हित दीर्घ) sf;
	regs->u_regs[UREG_I0] = ksig->sig;
	regs->u_regs[UREG_I1] = (अचिन्हित दीर्घ) &sf->info;
	regs->u_regs[UREG_I2] = (अचिन्हित दीर्घ) &sf->info;

	/* 4. संकेत handler */
	regs->tpc = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	regs->tnpc = (regs->tpc + 4);
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण

	/* 5. वापस to kernel inकाष्ठाions */
	अगर (ksig->ka.ka_restorer) अणु
		regs->u_regs[UREG_I7] = (अचिन्हित दीर्घ)ksig->ka.ka_restorer;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ address = ((अचिन्हित दीर्घ)&(sf->insns[0]));

		regs->u_regs[UREG_I7] = (अचिन्हित दीर्घ) (&(sf->insns[0]) - 2);
	
		err  = __put_user(0x821020d8, &sf->insns[0]); /*mov __NR_sigवापस, %g1*/
		err |= __put_user(0x91d02010, &sf->insns[1]); /*t 0x10*/
		अगर (err)
			वापस err;
		flush_संकेत_insns(address);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक setup_rt_frame32(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs,
			    sigset_t *oldset)
अणु
	काष्ठा rt_संकेत_frame32 __user *sf;
	पूर्णांक i, err, wsaved;
	व्योम __user *tail;
	पूर्णांक sigframe_size;
	u32 psr;

	/* 1. Make sure everything is clean */
	synchronize_user_stack();
	save_and_clear_fpu();
	
	wsaved = get_thपढ़ो_wsaved();

	sigframe_size = माप(*sf);
	अगर (current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF)
		sigframe_size += माप(__siginfo_fpu_t);
	अगर (wsaved)
		sigframe_size += माप(__siginfo_rwin_t);

	sf = (काष्ठा rt_संकेत_frame32 __user *)
		get_sigframe(ksig, regs, sigframe_size);
	
	अगर (invalid_frame_poपूर्णांकer(sf, sigframe_size)) अणु
		अगर (show_unhandled_संकेतs)
			pr_info("%s[%d] bad frame in setup_rt_frame32: %08lx TPC %08lx O7 %08lx\n",
				current->comm, current->pid, (अचिन्हित दीर्घ)sf,
				regs->tpc, regs->u_regs[UREG_I7]);
		क्रमce_sigsegv(ksig->sig);
		वापस -EINVAL;
	पूर्ण

	tail = (sf + 1);

	/* 2. Save the current process state */
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	err  = put_user(regs->tpc, &sf->regs.pc);
	err |= __put_user(regs->tnpc, &sf->regs.npc);
	err |= __put_user(regs->y, &sf->regs.y);
	psr = tstate_to_psr(regs->tstate);
	अगर (current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF)
		psr |= PSR_EF;
	err |= __put_user(psr, &sf->regs.psr);
	क्रम (i = 0; i < 16; i++)
		err |= __put_user(regs->u_regs[i], &sf->regs.u_regs[i]);
	err |= __put_user(माप(siginfo_extra_v8plus_t), &sf->extra_size);
	err |= __put_user(SIGINFO_EXTRA_V8PLUS_MAGIC, &sf->v8plus.g_upper[0]);
	क्रम (i = 1; i < 16; i++)
		err |= __put_user(((u32 *)regs->u_regs)[2*i],
				  &sf->v8plus.g_upper[i]);
	err |= __put_user((regs->tstate & TSTATE_ASI) >> 24UL,
			  &sf->v8plus.asi);

	अगर (psr & PSR_EF) अणु
		__siginfo_fpu_t __user *fp = tail;
		tail += माप(*fp);
		err |= save_fpu_state(regs, fp);
		err |= __put_user((u64)fp, &sf->fpu_save);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->fpu_save);
	पूर्ण
	अगर (wsaved) अणु
		__siginfo_rwin_t __user *rwp = tail;
		tail += माप(*rwp);
		err |= save_rwin_state(wsaved, rwp);
		err |= __put_user((u64)rwp, &sf->rwin_save);
		set_thपढ़ो_wsaved(0);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->rwin_save);
	पूर्ण

	/* Update the siginfo काष्ठाure.  */
	err |= copy_siginfo_to_user32(&sf->info, &ksig->info);
	
	/* Setup sigaltstack */
	err |= __compat_save_altstack(&sf->stack, regs->u_regs[UREG_FP]);

	err |= put_compat_sigset(&sf->mask, oldset, माप(compat_sigset_t));

	अगर (!wsaved) अणु
		err |= copy_in_user((u32 __user *)sf,
				    (u32 __user *)(regs->u_regs[UREG_FP]),
				    माप(काष्ठा reg_winकरोw32));
	पूर्ण अन्यथा अणु
		काष्ठा reg_winकरोw *rp;

		rp = &current_thपढ़ो_info()->reg_winकरोw[wsaved - 1];
		क्रम (i = 0; i < 8; i++)
			err |= __put_user(rp->locals[i], &sf->ss.locals[i]);
		क्रम (i = 0; i < 6; i++)
			err |= __put_user(rp->ins[i], &sf->ss.ins[i]);
		err |= __put_user(rp->ins[6], &sf->ss.fp);
		err |= __put_user(rp->ins[7], &sf->ss.callers_pc);
	पूर्ण
	अगर (err)
		वापस err;
	
	/* 3. संकेत handler back-trampoline and parameters */
	regs->u_regs[UREG_FP] = (अचिन्हित दीर्घ) sf;
	regs->u_regs[UREG_I0] = ksig->sig;
	regs->u_regs[UREG_I1] = (अचिन्हित दीर्घ) &sf->info;
	regs->u_regs[UREG_I2] = (अचिन्हित दीर्घ) &sf->regs;

	/* 4. संकेत handler */
	regs->tpc = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	regs->tnpc = (regs->tpc + 4);
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण

	/* 5. वापस to kernel inकाष्ठाions */
	अगर (ksig->ka.ka_restorer)
		regs->u_regs[UREG_I7] = (अचिन्हित दीर्घ)ksig->ka.ka_restorer;
	अन्यथा अणु
		अचिन्हित दीर्घ address = ((अचिन्हित दीर्घ)&(sf->insns[0]));

		regs->u_regs[UREG_I7] = (अचिन्हित दीर्घ) (&(sf->insns[0]) - 2);
	
		/* mov __NR_rt_sigवापस, %g1 */
		err |= __put_user(0x82102065, &sf->insns[0]);

		/* t 0x10 */
		err |= __put_user(0x91d02010, &sf->insns[1]);
		अगर (err)
			वापस err;

		flush_संकेत_insns(address);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम handle_संकेत32(काष्ठा kसंकेत *ksig, 
				  काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक err;

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		err = setup_rt_frame32(ksig, regs, oldset);
	अन्यथा
		err = setup_frame32(ksig, regs, oldset);

	संकेत_setup_करोne(err, ksig, 0);
पूर्ण

अटल अंतरभूत व्योम syscall_restart32(अचिन्हित दीर्घ orig_i0, काष्ठा pt_regs *regs,
				     काष्ठा sigaction *sa)
अणु
	चयन (regs->u_regs[UREG_I0]) अणु
	हाल ERESTART_RESTARTBLOCK:
	हाल ERESTARTNOHAND:
	no_प्रणाली_call_restart:
		regs->u_regs[UREG_I0] = EINTR;
		regs->tstate |= TSTATE_ICARRY;
		अवरोध;
	हाल ERESTARTSYS:
		अगर (!(sa->sa_flags & SA_RESTART))
			जाओ no_प्रणाली_call_restart;
		fallthrough;
	हाल ERESTARTNOINTR:
		regs->u_regs[UREG_I0] = orig_i0;
		regs->tpc -= 4;
		regs->tnpc -= 4;
	पूर्ण
पूर्ण

/* Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 */
व्योम करो_संकेत32(काष्ठा pt_regs * regs)
अणु
	काष्ठा kसंकेत ksig;
	अचिन्हित दीर्घ orig_i0 = 0;
	पूर्णांक restart_syscall = 0;
	bool has_handler = get_संकेत(&ksig);

	अगर (pt_regs_is_syscall(regs) &&
	    (regs->tstate & (TSTATE_XCARRY | TSTATE_ICARRY))) अणु
		restart_syscall = 1;
		orig_i0 = regs->u_regs[UREG_G6];
	पूर्ण

	अगर (has_handler) अणु
		अगर (restart_syscall)
			syscall_restart32(orig_i0, regs, &ksig.ka.sa);
		handle_संकेत32(&ksig, regs);
	पूर्ण अन्यथा अणु
		अगर (restart_syscall) अणु
			चयन (regs->u_regs[UREG_I0]) अणु
			हाल ERESTARTNOHAND:
	     		हाल ERESTARTSYS:
			हाल ERESTARTNOINTR:
				/* replay the प्रणाली call when we are करोne */
				regs->u_regs[UREG_I0] = orig_i0;
				regs->tpc -= 4;
				regs->tnpc -= 4;
				pt_regs_clear_syscall(regs);
				fallthrough;
			हाल ERESTART_RESTARTBLOCK:
				regs->u_regs[UREG_G1] = __NR_restart_syscall;
				regs->tpc -= 4;
				regs->tnpc -= 4;
				pt_regs_clear_syscall(regs);
			पूर्ण
		पूर्ण
		restore_saved_sigmask();
	पूर्ण
पूर्ण

काष्ठा sigstack32 अणु
	u32 the_stack;
	पूर्णांक cur_status;
पूर्ण;

यंत्रlinkage पूर्णांक करो_sys32_sigstack(u32 u_ssptr, u32 u_ossptr, अचिन्हित दीर्घ sp)
अणु
	काष्ठा sigstack32 __user *ssptr =
		(काष्ठा sigstack32 __user *)((अचिन्हित दीर्घ)(u_ssptr));
	काष्ठा sigstack32 __user *ossptr =
		(काष्ठा sigstack32 __user *)((अचिन्हित दीर्घ)(u_ossptr));
	पूर्णांक ret = -EFAULT;

	/* First see अगर old state is wanted. */
	अगर (ossptr) अणु
		अगर (put_user(current->sas_ss_sp + current->sas_ss_size,
			     &ossptr->the_stack) ||
		    __put_user(on_sig_stack(sp), &ossptr->cur_status))
			जाओ out;
	पूर्ण
	
	/* Now see अगर we want to update the new state. */
	अगर (ssptr) अणु
		u32 ss_sp;

		अगर (get_user(ss_sp, &ssptr->the_stack))
			जाओ out;

		/* If the current stack was set with sigaltstack, करोn't
		 * swap stacks जबतक we are on it.
		 */
		ret = -EPERM;
		अगर (current->sas_ss_sp && on_sig_stack(sp))
			जाओ out;
			
		/* Since we करोn't know the extent of the stack, and we don't
		 * track onstack-ness, but rather calculate it, we must
		 * presume a size.  Ho hum this पूर्णांकerface is lossy.
		 */
		current->sas_ss_sp = (अचिन्हित दीर्घ)ss_sp - SIGSTKSZ;
		current->sas_ss_size = SIGSTKSZ;
	पूर्ण
	
	ret = 0;
out:
	वापस ret;
पूर्ण
