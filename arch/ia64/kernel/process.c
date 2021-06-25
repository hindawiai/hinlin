<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Architecture-specअगरic setup.
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * 04/11/17 Ashok Raj	<ashok.raj@पूर्णांकel.com> Added CPU Hotplug Support
 *
 * 2005-10-07 Keith Owens <kaos@sgi.com>
 *	      Add notअगरy_die() hooks.
 */
#समावेश <linux/cpu.h>
#समावेश <linux/pm.h>
#समावेश <linux/elf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/personality.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/unistd.h>
#समावेश <linux/efi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/utsname.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/rcupdate.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/user.h>
#समावेश <यंत्र/xtp.h>

#समावेश "entry.h"

#समावेश "sigframe.h"

व्योम (*ia64_mark_idle)(पूर्णांक);

अचिन्हित दीर्घ boot_option_idle_override = IDLE_NO_OVERRIDE;
EXPORT_SYMBOL(boot_option_idle_override);
व्योम (*pm_घातer_off) (व्योम);
EXPORT_SYMBOL(pm_घातer_off);

अटल व्योम
ia64_करो_show_stack (काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	अचिन्हित दीर्घ ip, sp, bsp;
	स्थिर अक्षर *loglvl = arg;

	prपूर्णांकk("%s\nCall Trace:\n", loglvl);
	करो अणु
		unw_get_ip(info, &ip);
		अगर (ip == 0)
			अवरोध;

		unw_get_sp(info, &sp);
		unw_get_bsp(info, &bsp);
		prपूर्णांकk("%s [<%016lx>] %pS\n"
			 "                                sp=%016lx bsp=%016lx\n",
			 loglvl, ip, (व्योम *)ip, sp, bsp);
	पूर्ण जबतक (unw_unwind(info) >= 0);
पूर्ण

व्योम
show_stack (काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	अगर (!task)
		unw_init_running(ia64_करो_show_stack, (व्योम *)loglvl);
	अन्यथा अणु
		काष्ठा unw_frame_info info;

		unw_init_from_blocked_task(&info, task);
		ia64_करो_show_stack(&info, (व्योम *)loglvl);
	पूर्ण
पूर्ण

व्योम
show_regs (काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ip = regs->cr_iip + ia64_psr(regs)->ri;

	prपूर्णांक_modules();
	prपूर्णांकk("\n");
	show_regs_prपूर्णांक_info(KERN_DEFAULT);
	prपूर्णांकk("psr : %016lx ifs : %016lx ip  : [<%016lx>]    %s (%s)\n",
	       regs->cr_ipsr, regs->cr_अगरs, ip, prपूर्णांक_taपूर्णांकed(),
	       init_utsname()->release);
	prपूर्णांकk("ip is at %pS\n", (व्योम *)ip);
	prपूर्णांकk("unat: %016lx pfs : %016lx rsc : %016lx\n",
	       regs->ar_unat, regs->ar_pfs, regs->ar_rsc);
	prपूर्णांकk("rnat: %016lx bsps: %016lx pr  : %016lx\n",
	       regs->ar_rnat, regs->ar_bspstore, regs->pr);
	prपूर्णांकk("ldrs: %016lx ccv : %016lx fpsr: %016lx\n",
	       regs->loadrs, regs->ar_ccv, regs->ar_fpsr);
	prपूर्णांकk("csd : %016lx ssd : %016lx\n", regs->ar_csd, regs->ar_ssd);
	prपूर्णांकk("b0  : %016lx b6  : %016lx b7  : %016lx\n", regs->b0, regs->b6, regs->b7);
	prपूर्णांकk("f6  : %05lx%016lx f7  : %05lx%016lx\n",
	       regs->f6.u.bits[1], regs->f6.u.bits[0],
	       regs->f7.u.bits[1], regs->f7.u.bits[0]);
	prपूर्णांकk("f8  : %05lx%016lx f9  : %05lx%016lx\n",
	       regs->f8.u.bits[1], regs->f8.u.bits[0],
	       regs->f9.u.bits[1], regs->f9.u.bits[0]);
	prपूर्णांकk("f10 : %05lx%016lx f11 : %05lx%016lx\n",
	       regs->f10.u.bits[1], regs->f10.u.bits[0],
	       regs->f11.u.bits[1], regs->f11.u.bits[0]);

	prपूर्णांकk("r1  : %016lx r2  : %016lx r3  : %016lx\n", regs->r1, regs->r2, regs->r3);
	prपूर्णांकk("r8  : %016lx r9  : %016lx r10 : %016lx\n", regs->r8, regs->r9, regs->r10);
	prपूर्णांकk("r11 : %016lx r12 : %016lx r13 : %016lx\n", regs->r11, regs->r12, regs->r13);
	prपूर्णांकk("r14 : %016lx r15 : %016lx r16 : %016lx\n", regs->r14, regs->r15, regs->r16);
	prपूर्णांकk("r17 : %016lx r18 : %016lx r19 : %016lx\n", regs->r17, regs->r18, regs->r19);
	prपूर्णांकk("r20 : %016lx r21 : %016lx r22 : %016lx\n", regs->r20, regs->r21, regs->r22);
	prपूर्णांकk("r23 : %016lx r24 : %016lx r25 : %016lx\n", regs->r23, regs->r24, regs->r25);
	prपूर्णांकk("r26 : %016lx r27 : %016lx r28 : %016lx\n", regs->r26, regs->r27, regs->r28);
	prपूर्णांकk("r29 : %016lx r30 : %016lx r31 : %016lx\n", regs->r29, regs->r30, regs->r31);

	अगर (user_mode(regs)) अणु
		/* prपूर्णांक the stacked रेजिस्टरs */
		अचिन्हित दीर्घ val, *bsp, ndirty;
		पूर्णांक i, sof, is_nat = 0;

		sof = regs->cr_अगरs & 0x7f;	/* size of frame */
		ndirty = (regs->loadrs >> 19);
		bsp = ia64_rse_skip_regs((अचिन्हित दीर्घ *) regs->ar_bspstore, ndirty);
		क्रम (i = 0; i < sof; ++i) अणु
			get_user(val, (अचिन्हित दीर्घ __user *) ia64_rse_skip_regs(bsp, i));
			prपूर्णांकk("r%-3u:%c%016lx%s", 32 + i, is_nat ? '*' : ' ', val,
			       ((i == sof - 1) || (i % 3) == 2) ? "\n" : " ");
		पूर्ण
	पूर्ण अन्यथा
		show_stack(शून्य, शून्य, KERN_DEFAULT);
पूर्ण

/* local support क्रम deprecated console_prपूर्णांक */
व्योम
console_prपूर्णांक(स्थिर अक्षर *s)
अणु
	prपूर्णांकk(KERN_EMERG "%s", s);
पूर्ण

व्योम
करो_notअगरy_resume_user(sigset_t *unused, काष्ठा sigscratch *scr, दीर्घ in_syscall)
अणु
	अगर (fsys_mode(current, &scr->pt)) अणु
		/*
		 * defer संकेत-handling etc. until we वापस to
		 * privilege-level 0.
		 */
		अगर (!ia64_psr(&scr->pt)->lp)
			ia64_psr(&scr->pt)->lp = 1;
		वापस;
	पूर्ण

	/* deal with pending संकेत delivery */
	अगर (test_thपढ़ो_flag(TIF_SIGPENDING) ||
	    test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL)) अणु
		local_irq_enable();	/* क्रमce पूर्णांकerrupt enable */
		ia64_करो_संकेत(scr, in_syscall);
	पूर्ण

	अगर (test_thपढ़ो_flag(TIF_NOTIFY_RESUME)) अणु
		local_irq_enable();	/* क्रमce पूर्णांकerrupt enable */
		tracehook_notअगरy_resume(&scr->pt);
	पूर्ण

	/* copy user rbs to kernel rbs */
	अगर (unlikely(test_thपढ़ो_flag(TIF_RESTORE_RSE))) अणु
		local_irq_enable();	/* क्रमce पूर्णांकerrupt enable */
		ia64_sync_krbs();
	पूर्ण

	local_irq_disable();	/* क्रमce पूर्णांकerrupt disable */
पूर्ण

अटल पूर्णांक __init nohalt_setup(अक्षर * str)
अणु
	cpu_idle_poll_ctrl(true);
	वापस 1;
पूर्ण
__setup("nohalt", nohalt_setup);

#अगर_घोषित CONFIG_HOTPLUG_CPU
/* We करोn't actually take CPU करोwn, just spin without पूर्णांकerrupts. */
अटल अंतरभूत व्योम play_dead(व्योम)
अणु
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();

	/* Ack it */
	__this_cpu_ग_लिखो(cpu_state, CPU_DEAD);

	max_xtp();
	local_irq_disable();
	idle_task_निकास();
	ia64_jump_to_sal(&sal_boot_rendez_state[this_cpu]);
	/*
	 * The above is a poपूर्णांक of no-वापस, the processor is
	 * expected to be in SAL loop now.
	 */
	BUG();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम play_dead(व्योम)
अणु
	BUG();
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

व्योम arch_cpu_idle_dead(व्योम)
अणु
	play_dead();
पूर्ण

व्योम arch_cpu_idle(व्योम)
अणु
	व्योम (*mark_idle)(पूर्णांक) = ia64_mark_idle;

#अगर_घोषित CONFIG_SMP
	min_xtp();
#पूर्ण_अगर
	rmb();
	अगर (mark_idle)
		(*mark_idle)(1);

	raw_safe_halt();

	अगर (mark_idle)
		(*mark_idle)(0);
#अगर_घोषित CONFIG_SMP
	normal_xtp();
#पूर्ण_अगर
पूर्ण

व्योम
ia64_save_extra (काष्ठा task_काष्ठा *task)
अणु
	अगर ((task->thपढ़ो.flags & IA64_THREAD_DBG_VALID) != 0)
		ia64_save_debug_regs(&task->thपढ़ो.dbr[0]);
पूर्ण

व्योम
ia64_load_extra (काष्ठा task_काष्ठा *task)
अणु
	अगर ((task->thपढ़ो.flags & IA64_THREAD_DBG_VALID) != 0)
		ia64_load_debug_regs(&task->thपढ़ो.dbr[0]);
पूर्ण

/*
 * Copy the state of an ia-64 thपढ़ो.
 *
 * We get here through the following  call chain:
 *
 *	from user-level:	from kernel:
 *
 *	<clone syscall>	        <some kernel call frames>
 *	sys_clone		   :
 *	kernel_clone		kernel_clone
 *	copy_thपढ़ो		copy_thपढ़ो
 *
 * This means that the stack layout is as follows:
 *
 *	+---------------------+ (highest addr)
 *	|   काष्ठा pt_regs    |
 *	+---------------------+
 *	| काष्ठा चयन_stack |
 *	+---------------------+
 *	|                     |
 *	|    memory stack     |
 *	|                     | <-- sp (lowest addr)
 *	+---------------------+
 *
 * Observe that we copy the unat values that are in pt_regs and चयन_stack.  Spilling an
 * पूर्णांकeger to address X causes bit N in ar.unat to be set to the NaT bit of the रेजिस्टर,
 * with N=(X & 0x1ff)/8.  Thus, copying the unat value preserves the NaT bits ONLY अगर the
 * pt_regs काष्ठाure in the parent is congruent to that of the child, modulo 512.  Since
 * the stack is page aligned and the page size is at least 4KB, this is always the हाल,
 * so there is nothing to worry about.
 */
पूर्णांक
copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ user_stack_base,
	    अचिन्हित दीर्घ user_stack_size, काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	बाह्य अक्षर ia64_ret_from_clone;
	काष्ठा चयन_stack *child_stack, *stack;
	अचिन्हित दीर्घ rbs, child_rbs, rbs_size;
	काष्ठा pt_regs *child_ptregs;
	काष्ठा pt_regs *regs = current_pt_regs();
	पूर्णांक retval = 0;

	child_ptregs = (काष्ठा pt_regs *) ((अचिन्हित दीर्घ) p + IA64_STK_OFFSET) - 1;
	child_stack = (काष्ठा चयन_stack *) child_ptregs - 1;

	rbs = (अचिन्हित दीर्घ) current + IA64_RBS_OFFSET;
	child_rbs = (अचिन्हित दीर्घ) p + IA64_RBS_OFFSET;

	/* copy parts of thपढ़ो_काष्ठा: */
	p->thपढ़ो.ksp = (अचिन्हित दीर्घ) child_stack - 16;

	/*
	 * NOTE: The calling convention considers all भग्नing poपूर्णांक
	 * रेजिस्टरs in the high partition (fph) to be scratch.  Since
	 * the only way to get to this poपूर्णांक is through a प्रणाली call,
	 * we know that the values in fph are all dead.  Hence, there
	 * is no need to inherit the fph state from the parent to the
	 * child and all we have to करो is to make sure that
	 * IA64_THREAD_FPH_VALID is cleared in the child.
	 *
	 * XXX We could push this optimization a bit further by
	 * clearing IA64_THREAD_FPH_VALID on ANY प्रणाली call.
	 * However, it's not clear this is worth करोing.  Also, it
	 * would be a slight deviation from the normal Linux प्रणाली
	 * call behavior where scratch रेजिस्टरs are preserved across
	 * प्रणाली calls (unless used by the प्रणाली call itself).
	 */
#	define THREAD_FLAGS_TO_CLEAR	(IA64_THREAD_FPH_VALID | IA64_THREAD_DBG_VALID \
					 | IA64_THREAD_PM_VALID)
#	define THREAD_FLAGS_TO_SET	0
	p->thपढ़ो.flags = ((current->thपढ़ो.flags & ~THREAD_FLAGS_TO_CLEAR)
			   | THREAD_FLAGS_TO_SET);

	ia64_drop_fpu(p);	/* करोn't pick up stale state from a CPU's fph */

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		अगर (unlikely(!user_stack_base)) अणु
			/* विभाजन_idle() called us */
			वापस 0;
		पूर्ण
		स_रखो(child_stack, 0, माप(*child_ptregs) + माप(*child_stack));
		child_stack->r4 = user_stack_base;	/* payload */
		child_stack->r5 = user_stack_size;	/* argument */
		/*
		 * Preserve PSR bits, except क्रम bits 32-34 and 37-45,
		 * which we can't पढ़ो.
		 */
		child_ptregs->cr_ipsr = ia64_getreg(_IA64_REG_PSR) | IA64_PSR_BN;
		/* mark as valid, empty frame */
		child_ptregs->cr_अगरs = 1UL << 63;
		child_stack->ar_fpsr = child_ptregs->ar_fpsr
			= ia64_getreg(_IA64_REG_AR_FPSR);
		child_stack->pr = (1 << PRED_KERNEL_STACK);
		child_stack->ar_bspstore = child_rbs;
		child_stack->b0 = (अचिन्हित दीर्घ) &ia64_ret_from_clone;

		/* stop some PSR bits from being inherited.
		 * the psr.up/psr.pp bits must be cleared on विभाजन but inherited on execve()
		 * thereक्रमe we must specअगरy them explicitly here and not include them in
		 * IA64_PSR_BITS_TO_CLEAR.
		 */
		child_ptregs->cr_ipsr = ((child_ptregs->cr_ipsr | IA64_PSR_BITS_TO_SET)
				 & ~(IA64_PSR_BITS_TO_CLEAR | IA64_PSR_PP | IA64_PSR_UP));

		वापस 0;
	पूर्ण
	stack = ((काष्ठा चयन_stack *) regs) - 1;
	/* copy parent's चयन_stack & pt_regs to child: */
	स_नकल(child_stack, stack, माप(*child_ptregs) + माप(*child_stack));

	/* copy the parent's रेजिस्टर backing store to the child: */
	rbs_size = stack->ar_bspstore - rbs;
	स_नकल((व्योम *) child_rbs, (व्योम *) rbs, rbs_size);
	अगर (clone_flags & CLONE_SETTLS)
		child_ptregs->r13 = tls;
	अगर (user_stack_base) अणु
		child_ptregs->r12 = user_stack_base + user_stack_size - 16;
		child_ptregs->ar_bspstore = user_stack_base;
		child_ptregs->ar_rnat = 0;
		child_ptregs->loadrs = 0;
	पूर्ण
	child_stack->ar_bspstore = child_rbs + rbs_size;
	child_stack->b0 = (अचिन्हित दीर्घ) &ia64_ret_from_clone;

	/* stop some PSR bits from being inherited.
	 * the psr.up/psr.pp bits must be cleared on विभाजन but inherited on execve()
	 * thereक्रमe we must specअगरy them explicitly here and not include them in
	 * IA64_PSR_BITS_TO_CLEAR.
	 */
	child_ptregs->cr_ipsr = ((child_ptregs->cr_ipsr | IA64_PSR_BITS_TO_SET)
				 & ~(IA64_PSR_BITS_TO_CLEAR | IA64_PSR_PP | IA64_PSR_UP));
	वापस retval;
पूर्ण

यंत्रlinkage दीर्घ ia64_clone(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ stack_start,
			   अचिन्हित दीर्घ stack_size, अचिन्हित दीर्घ parent_tidptr,
			   अचिन्हित दीर्घ child_tidptr, अचिन्हित दीर्घ tls)
अणु
	काष्ठा kernel_clone_args args = अणु
		.flags		= (lower_32_bits(clone_flags) & ~CSIGNAL),
		.pidfd		= (पूर्णांक __user *)parent_tidptr,
		.child_tid	= (पूर्णांक __user *)child_tidptr,
		.parent_tid	= (पूर्णांक __user *)parent_tidptr,
		.निकास_संकेत	= (lower_32_bits(clone_flags) & CSIGNAL),
		.stack		= stack_start,
		.stack_size	= stack_size,
		.tls		= tls,
	पूर्ण;

	वापस kernel_clone(&args);
पूर्ण

अटल व्योम
करो_copy_task_regs (काष्ठा task_काष्ठा *task, काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	अचिन्हित दीर्घ mask, sp, nat_bits = 0, ar_rnat, urbs_end, cfm;
	अचिन्हित दीर्घ ip;
	elf_greg_t *dst = arg;
	काष्ठा pt_regs *pt;
	अक्षर nat;
	पूर्णांक i;

	स_रखो(dst, 0, माप(elf_gregset_t));	/* करोn't leak any kernel bits to user-level */

	अगर (unw_unwind_to_user(info) < 0)
		वापस;

	unw_get_sp(info, &sp);
	pt = (काष्ठा pt_regs *) (sp + 16);

	urbs_end = ia64_get_user_rbs_end(task, pt, &cfm);

	अगर (ia64_sync_user_rbs(task, info->sw, pt->ar_bspstore, urbs_end) < 0)
		वापस;

	ia64_peek(task, info->sw, urbs_end, (दीर्घ) ia64_rse_rnat_addr((दीर्घ *) urbs_end),
		  &ar_rnat);

	/*
	 * coredump क्रमmat:
	 *	r0-r31
	 *	NaT bits (क्रम r0-r31; bit N == 1 अगरf rN is a NaT)
	 *	predicate रेजिस्टरs (p0-p63)
	 *	b0-b7
	 *	ip cfm user-mask
	 *	ar.rsc ar.bsp ar.bspstore ar.rnat
	 *	ar.ccv ar.unat ar.fpsr ar.pfs ar.lc ar.ec
	 */

	/* r0 is zero */
	क्रम (i = 1, mask = (1UL << i); i < 32; ++i) अणु
		unw_get_gr(info, i, &dst[i], &nat);
		अगर (nat)
			nat_bits |= mask;
		mask <<= 1;
	पूर्ण
	dst[32] = nat_bits;
	unw_get_pr(info, &dst[33]);

	क्रम (i = 0; i < 8; ++i)
		unw_get_br(info, i, &dst[34 + i]);

	unw_get_rp(info, &ip);
	dst[42] = ip + ia64_psr(pt)->ri;
	dst[43] = cfm;
	dst[44] = pt->cr_ipsr & IA64_PSR_UM;

	unw_get_ar(info, UNW_AR_RSC, &dst[45]);
	/*
	 * For bsp and bspstore, unw_get_ar() would वापस the kernel
	 * addresses, but we need the user-level addresses instead:
	 */
	dst[46] = urbs_end;	/* note: by convention PT_AR_BSP poपूर्णांकs to the end of the urbs! */
	dst[47] = pt->ar_bspstore;
	dst[48] = ar_rnat;
	unw_get_ar(info, UNW_AR_CCV, &dst[49]);
	unw_get_ar(info, UNW_AR_UNAT, &dst[50]);
	unw_get_ar(info, UNW_AR_FPSR, &dst[51]);
	dst[52] = pt->ar_pfs;	/* UNW_AR_PFS is == to pt->cr_अगरs क्रम पूर्णांकerrupt frames */
	unw_get_ar(info, UNW_AR_LC, &dst[53]);
	unw_get_ar(info, UNW_AR_EC, &dst[54]);
	unw_get_ar(info, UNW_AR_CSD, &dst[55]);
	unw_get_ar(info, UNW_AR_SSD, &dst[56]);
पूर्ण

अटल व्योम
करो_copy_regs (काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	करो_copy_task_regs(current, info, arg);
पूर्ण

व्योम
ia64_elf_core_copy_regs (काष्ठा pt_regs *pt, elf_gregset_t dst)
अणु
	unw_init_running(करो_copy_regs, dst);
पूर्ण

/*
 * Flush thपढ़ो state.  This is called when a thपढ़ो करोes an execve().
 */
व्योम
flush_thपढ़ो (व्योम)
अणु
	/* drop भग्नing-poपूर्णांक and debug-रेजिस्टर state अगर it exists: */
	current->thपढ़ो.flags &= ~(IA64_THREAD_FPH_VALID | IA64_THREAD_DBG_VALID);
	ia64_drop_fpu(current);
पूर्ण

/*
 * Clean up state associated with a thपढ़ो.  This is called when
 * the thपढ़ो calls निकास().
 */
व्योम
निकास_thपढ़ो (काष्ठा task_काष्ठा *tsk)
अणु

	ia64_drop_fpu(tsk);
पूर्ण

अचिन्हित दीर्घ
get_wchan (काष्ठा task_काष्ठा *p)
अणु
	काष्ठा unw_frame_info info;
	अचिन्हित दीर्घ ip;
	पूर्णांक count = 0;

	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	/*
	 * Note: p may not be a blocked task (it could be current or
	 * another process running on some other CPU.  Rather than
	 * trying to determine अगर p is really blocked, we just assume
	 * it's blocked and rely on the unwind routines to fail
	 * gracefully अगर the process wasn't really blocked after all.
	 * --davidm 99/12/15
	 */
	unw_init_from_blocked_task(&info, p);
	करो अणु
		अगर (p->state == TASK_RUNNING)
			वापस 0;
		अगर (unw_unwind(&info) < 0)
			वापस 0;
		unw_get_ip(&info, &ip);
		अगर (!in_sched_functions(ip))
			वापस ip;
	पूर्ण जबतक (count++ < 16);
	वापस 0;
पूर्ण

व्योम
cpu_halt (व्योम)
अणु
	pal_घातer_mgmt_info_u_t घातer_info[8];
	अचिन्हित दीर्घ min_घातer;
	पूर्णांक i, min_घातer_state;

	अगर (ia64_pal_halt_info(घातer_info) != 0)
		वापस;

	min_घातer_state = 0;
	min_घातer = घातer_info[0].pal_घातer_mgmt_info_s.घातer_consumption;
	क्रम (i = 1; i < 8; ++i)
		अगर (घातer_info[i].pal_घातer_mgmt_info_s.im
		    && घातer_info[i].pal_घातer_mgmt_info_s.घातer_consumption < min_घातer) अणु
			min_घातer = घातer_info[i].pal_घातer_mgmt_info_s.घातer_consumption;
			min_घातer_state = i;
		पूर्ण

	जबतक (1)
		ia64_pal_halt(min_घातer_state);
पूर्ण

व्योम machine_shutकरोwn(व्योम)
अणु
	smp_shutकरोwn_nonboot_cpus(reboot_cpu);

#अगर_घोषित CONFIG_KEXEC
	kexec_disable_iosapic();
#पूर्ण_अगर
पूर्ण

व्योम
machine_restart (अक्षर *restart_cmd)
अणु
	(व्योम) notअगरy_die(DIE_MACHINE_RESTART, restart_cmd, शून्य, 0, 0, 0);
	efi_reboot(REBOOT_WARM, शून्य);
पूर्ण

व्योम
machine_halt (व्योम)
अणु
	(व्योम) notअगरy_die(DIE_MACHINE_HALT, "", शून्य, 0, 0, 0);
	cpu_halt();
पूर्ण

व्योम
machine_घातer_off (व्योम)
अणु
	अगर (pm_घातer_off)
		pm_घातer_off();
	machine_halt();
पूर्ण

EXPORT_SYMBOL(ia64_delay_loop);
