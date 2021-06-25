<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/audit.h>
#समावेश <linux/elf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/regset.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/smp.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/user.h>

#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/यंत्र-offsets.h>

#समावेश <abi/regdef.h>
#समावेश <abi/ckmmu.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

/* sets the trace bits. */
#घोषणा TRACE_MODE_SI      (1 << 14)
#घोषणा TRACE_MODE_RUN     0
#घोषणा TRACE_MODE_MASK    ~(0x3 << 14)

/*
 * Make sure the single step bit is not set.
 */
अटल व्योम singlestep_disable(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा pt_regs *regs;

	regs = task_pt_regs(tsk);
	regs->sr = (regs->sr & TRACE_MODE_MASK) | TRACE_MODE_RUN;

	/* Enable irq */
	regs->sr |= BIT(6);
पूर्ण

अटल व्योम singlestep_enable(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा pt_regs *regs;

	regs = task_pt_regs(tsk);
	regs->sr = (regs->sr & TRACE_MODE_MASK) | TRACE_MODE_SI;

	/* Disable irq */
	regs->sr &= ~BIT(6);
पूर्ण

/*
 * Make sure the single step bit is set.
 */
व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	singlestep_enable(child);
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	singlestep_disable(child);
पूर्ण

क्रमागत csky_regset अणु
	REGSET_GPR,
	REGSET_FPR,
पूर्ण;

अटल पूर्णांक gpr_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);

	/* Abiv1 regs->tls is fake and we need sync here. */
	regs->tls = task_thपढ़ो_info(target)->tp_value;

	वापस membuf_ग_लिखो(&to, regs, माप(*regs));
पूर्ण

अटल पूर्णांक gpr_set(काष्ठा task_काष्ठा *target,
		    स्थिर काष्ठा user_regset *regset,
		    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		    स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा pt_regs regs;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &regs, 0, -1);
	अगर (ret)
		वापस ret;

	regs.sr = task_pt_regs(target)->sr;
#अगर_घोषित CONFIG_CPU_HAS_HILO
	regs.dcsr = task_pt_regs(target)->dcsr;
#पूर्ण_अगर
	task_thपढ़ो_info(target)->tp_value = regs.tls;

	*task_pt_regs(target) = regs;

	वापस 0;
पूर्ण

अटल पूर्णांक fpr_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	काष्ठा user_fp *regs = (काष्ठा user_fp *)&target->thपढ़ो.user_fp;

#अगर defined(CONFIG_CPU_HAS_FPUV2) && !defined(CONFIG_CPU_HAS_VDSP)
	पूर्णांक i;
	काष्ठा user_fp पंचांगp = *regs;

	क्रम (i = 0; i < 16; i++) अणु
		पंचांगp.vr[i*4] = regs->vr[i*2];
		पंचांगp.vr[i*4 + 1] = regs->vr[i*2 + 1];
	पूर्ण

	क्रम (i = 0; i < 32; i++)
		पंचांगp.vr[64 + i] = regs->vr[32 + i];

	वापस membuf_ग_लिखो(&to, &पंचांगp, माप(पंचांगp));
#अन्यथा
	वापस membuf_ग_लिखो(&to, regs, माप(*regs));
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक fpr_set(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा user_fp *regs = (काष्ठा user_fp *)&target->thपढ़ो.user_fp;

#अगर defined(CONFIG_CPU_HAS_FPUV2) && !defined(CONFIG_CPU_HAS_VDSP)
	पूर्णांक i;
	काष्ठा user_fp पंचांगp;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &पंचांगp, 0, -1);

	*regs = पंचांगp;

	क्रम (i = 0; i < 16; i++) अणु
		regs->vr[i*2] = पंचांगp.vr[i*4];
		regs->vr[i*2 + 1] = पंचांगp.vr[i*4 + 1];
	पूर्ण

	क्रम (i = 0; i < 32; i++)
		regs->vr[32 + i] = पंचांगp.vr[64 + i];
#अन्यथा
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, regs, 0, -1);
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा user_regset csky_regsets[] = अणु
	[REGSET_GPR] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = माप(काष्ठा pt_regs) / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = gpr_get,
		.set = gpr_set,
	पूर्ण,
	[REGSET_FPR] = अणु
		.core_note_type = NT_PRFPREG,
		.n = माप(काष्ठा user_fp) / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = fpr_get,
		.set = fpr_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_csky_view = अणु
	.name = "csky",
	.e_machine = ELF_ARCH,
	.regsets = csky_regsets,
	.n = ARRAY_SIZE(csky_regsets),
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &user_csky_view;
पूर्ण

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_NAME(r) अणु.name = #r, .offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण

अटल स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
	REG_OFFSET_NAME(tls),
	REG_OFFSET_NAME(lr),
	REG_OFFSET_NAME(pc),
	REG_OFFSET_NAME(sr),
	REG_OFFSET_NAME(usp),
	REG_OFFSET_NAME(orig_a0),
	REG_OFFSET_NAME(a0),
	REG_OFFSET_NAME(a1),
	REG_OFFSET_NAME(a2),
	REG_OFFSET_NAME(a3),
	REG_OFFSET_NAME(regs[0]),
	REG_OFFSET_NAME(regs[1]),
	REG_OFFSET_NAME(regs[2]),
	REG_OFFSET_NAME(regs[3]),
	REG_OFFSET_NAME(regs[4]),
	REG_OFFSET_NAME(regs[5]),
	REG_OFFSET_NAME(regs[6]),
	REG_OFFSET_NAME(regs[7]),
	REG_OFFSET_NAME(regs[8]),
	REG_OFFSET_NAME(regs[9]),
#अगर defined(__CSKYABIV2__)
	REG_OFFSET_NAME(exregs[0]),
	REG_OFFSET_NAME(exregs[1]),
	REG_OFFSET_NAME(exregs[2]),
	REG_OFFSET_NAME(exregs[3]),
	REG_OFFSET_NAME(exregs[4]),
	REG_OFFSET_NAME(exregs[5]),
	REG_OFFSET_NAME(exregs[6]),
	REG_OFFSET_NAME(exregs[7]),
	REG_OFFSET_NAME(exregs[8]),
	REG_OFFSET_NAME(exregs[9]),
	REG_OFFSET_NAME(exregs[10]),
	REG_OFFSET_NAME(exregs[11]),
	REG_OFFSET_NAME(exregs[12]),
	REG_OFFSET_NAME(exregs[13]),
	REG_OFFSET_NAME(exregs[14]),
	REG_OFFSET_NAME(rhi),
	REG_OFFSET_NAME(rlo),
	REG_OFFSET_NAME(dcsr),
#पूर्ण_अगर
	REG_OFFSET_END,
पूर्ण;

/**
 * regs_query_रेजिस्टर_offset() - query रेजिस्टर offset from its name
 * @name:	the name of a रेजिस्टर
 *
 * regs_query_रेजिस्टर_offset() वापसs the offset of a रेजिस्टर in काष्ठा
 * pt_regs from its name. If the name is invalid, this वापसs -EINVAL;
 */
पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;

	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (!म_भेद(roff->name, name))
			वापस roff->offset;
	वापस -EINVAL;
पूर्ण

/**
 * regs_within_kernel_stack() - check the address in the stack
 * @regs:      pt_regs which contains kernel stack poपूर्णांकer.
 * @addr:      address which is checked.
 *
 * regs_within_kernel_stack() checks @addr is within the kernel stack page(s).
 * If @addr is within the kernel stack, it वापसs true. If not, वापसs false.
 */
अटल bool regs_within_kernel_stack(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	वापस (addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_poपूर्णांकer(regs) & ~(THREAD_SIZE - 1));
पूर्ण

/**
 * regs_get_kernel_stack_nth() - get Nth entry of the stack
 * @regs:	pt_regs which contains kernel stack poपूर्णांकer.
 * @n:		stack entry number.
 *
 * regs_get_kernel_stack_nth() वापसs @n th entry of the kernel stack which
 * is specअगरied by @regs. If the @n th entry is NOT in the kernel stack,
 * this वापसs 0.
 */
अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *)kernel_stack_poपूर्णांकer(regs);

	addr += n;
	अगर (regs_within_kernel_stack(regs, (अचिन्हित दीर्घ)addr))
		वापस *addr;
	अन्यथा
		वापस 0;
पूर्ण

व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	singlestep_disable(child);
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	दीर्घ ret = -EIO;

	चयन (request) अणु
	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

यंत्रlinkage पूर्णांक syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		अगर (tracehook_report_syscall_entry(regs))
			वापस -1;

	अगर (secure_computing() == -1)
		वापस -1;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_enter(regs, syscall_get_nr(current, regs));

	audit_syscall_entry(regs_syscallid(regs), regs->a0, regs->a1, regs->a2, regs->a3);
	वापस 0;
पूर्ण

यंत्रlinkage व्योम syscall_trace_निकास(काष्ठा pt_regs *regs)
अणु
	audit_syscall_निकास(regs);

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, 0);

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_निकास(regs, syscall_get_वापस_value(current, regs));
पूर्ण

#अगर_घोषित CONFIG_CPU_CK860
अटल व्योम show_iutlb(व्योम)
अणु
	पूर्णांक entry, i;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ oldpid;
	अचिन्हित दीर्घ entryhi[16], entrylo0[16], entrylo1[16];

	oldpid = पढ़ो_mmu_entryhi();

	entry = 0x8000;

	local_irq_save(flags);

	क्रम (i = 0; i < 16; i++) अणु
		ग_लिखो_mmu_index(entry);
		tlb_पढ़ो();
		entryhi[i]  = पढ़ो_mmu_entryhi();
		entrylo0[i] = पढ़ो_mmu_entrylo0();
		entrylo1[i] = पढ़ो_mmu_entrylo1();

		entry++;
	पूर्ण

	local_irq_restore(flags);

	ग_लिखो_mmu_entryhi(oldpid);

	prपूर्णांकk("\n\n\n");
	क्रम (i = 0; i < 16; i++)
		prपूर्णांकk("iutlb[%d]:	entryhi - 0x%lx;	entrylo0 - 0x%lx;"
		       "	entrylo1 - 0x%lx\n",
			 i, entryhi[i], entrylo0[i], entrylo1[i]);
	prपूर्णांकk("\n\n\n");
पूर्ण

अटल व्योम show_dutlb(व्योम)
अणु
	पूर्णांक entry, i;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ oldpid;
	अचिन्हित दीर्घ entryhi[16], entrylo0[16], entrylo1[16];

	oldpid = पढ़ो_mmu_entryhi();

	entry = 0x4000;

	local_irq_save(flags);

	क्रम (i = 0; i < 16; i++) अणु
		ग_लिखो_mmu_index(entry);
		tlb_पढ़ो();
		entryhi[i]  = पढ़ो_mmu_entryhi();
		entrylo0[i] = पढ़ो_mmu_entrylo0();
		entrylo1[i] = पढ़ो_mmu_entrylo1();

		entry++;
	पूर्ण

	local_irq_restore(flags);

	ग_लिखो_mmu_entryhi(oldpid);

	prपूर्णांकk("\n\n\n");
	क्रम (i = 0; i < 16; i++)
		prपूर्णांकk("dutlb[%d]:	entryhi - 0x%lx;	entrylo0 - 0x%lx;"
		       "	entrylo1 - 0x%lx\n",
			 i, entryhi[i], entrylo0[i], entrylo1[i]);
	prपूर्णांकk("\n\n\n");
पूर्ण

अटल अचिन्हित दीर्घ entryhi[1024], entrylo0[1024], entrylo1[1024];
अटल व्योम show_jtlb(व्योम)
अणु
	पूर्णांक entry;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ oldpid;

	oldpid = पढ़ो_mmu_entryhi();

	entry = 0;

	local_irq_save(flags);
	जबतक (entry < 1024) अणु
		ग_लिखो_mmu_index(entry);
		tlb_पढ़ो();
		entryhi[entry]  = पढ़ो_mmu_entryhi();
		entrylo0[entry] = पढ़ो_mmu_entrylo0();
		entrylo1[entry] = पढ़ो_mmu_entrylo1();

		entry++;
	पूर्ण
	local_irq_restore(flags);

	ग_लिखो_mmu_entryhi(oldpid);

	prपूर्णांकk("\n\n\n");

	क्रम (entry = 0; entry < 1024; entry++)
		prपूर्णांकk("jtlb[%x]:	entryhi - 0x%lx;	entrylo0 - 0x%lx;"
		       "	entrylo1 - 0x%lx\n",
			 entry, entryhi[entry], entrylo0[entry], entrylo1[entry]);
	prपूर्णांकk("\n\n\n");
पूर्ण

अटल व्योम show_tlb(व्योम)
अणु
	show_iutlb();
	show_dutlb();
	show_jtlb();
पूर्ण
#अन्यथा
अटल व्योम show_tlb(व्योम)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

व्योम show_regs(काष्ठा pt_regs *fp)
अणु
	pr_info("\nCURRENT PROCESS:\n\n");
	pr_info("COMM=%s PID=%d\n", current->comm, current->pid);

	अगर (current->mm) अणु
		pr_info("TEXT=%08x-%08x DATA=%08x-%08x BSS=%08x-%08x\n",
		       (पूर्णांक) current->mm->start_code,
		       (पूर्णांक) current->mm->end_code,
		       (पूर्णांक) current->mm->start_data,
		       (पूर्णांक) current->mm->end_data,
		       (पूर्णांक) current->mm->end_data,
		       (पूर्णांक) current->mm->brk);
		pr_info("USER-STACK=%08x  KERNEL-STACK=%08x\n\n",
		       (पूर्णांक) current->mm->start_stack,
		       (पूर्णांक) (((अचिन्हित दीर्घ) current) + 2 * PAGE_SIZE));
	पूर्ण

	pr_info("PC: 0x%08lx (%pS)\n", (दीर्घ)fp->pc, (व्योम *)fp->pc);
	pr_info("LR: 0x%08lx (%pS)\n", (दीर्घ)fp->lr, (व्योम *)fp->lr);
	pr_info("SP: 0x%08lx\n", (दीर्घ)fp->usp);
	pr_info("PSR: 0x%08lx\n", (दीर्घ)fp->sr);
	pr_info("orig_a0: 0x%08lx\n", fp->orig_a0);
	pr_info("PT_REGS: 0x%08lx\n", (दीर्घ)fp);

	pr_info(" a0: 0x%08lx   a1: 0x%08lx   a2: 0x%08lx   a3: 0x%08lx\n",
		fp->a0, fp->a1, fp->a2, fp->a3);
#अगर defined(__CSKYABIV2__)
	pr_info(" r4: 0x%08lx   r5: 0x%08lx   r6: 0x%08lx   r7: 0x%08lx\n",
		fp->regs[0], fp->regs[1], fp->regs[2], fp->regs[3]);
	pr_info(" r8: 0x%08lx   r9: 0x%08lx  r10: 0x%08lx  r11: 0x%08lx\n",
		fp->regs[4], fp->regs[5], fp->regs[6], fp->regs[7]);
	pr_info("r12: 0x%08lx  r13: 0x%08lx  r15: 0x%08lx\n",
		fp->regs[8], fp->regs[9], fp->lr);
	pr_info("r16: 0x%08lx  r17: 0x%08lx  r18: 0x%08lx  r19: 0x%08lx\n",
		fp->exregs[0], fp->exregs[1], fp->exregs[2], fp->exregs[3]);
	pr_info("r20: 0x%08lx  r21: 0x%08lx  r22: 0x%08lx  r23: 0x%08lx\n",
		fp->exregs[4], fp->exregs[5], fp->exregs[6], fp->exregs[7]);
	pr_info("r24: 0x%08lx  r25: 0x%08lx  r26: 0x%08lx  r27: 0x%08lx\n",
		fp->exregs[8], fp->exregs[9], fp->exregs[10], fp->exregs[11]);
	pr_info("r28: 0x%08lx  r29: 0x%08lx  r30: 0x%08lx  tls: 0x%08lx\n",
		fp->exregs[12], fp->exregs[13], fp->exregs[14], fp->tls);
	pr_info(" hi: 0x%08lx   lo: 0x%08lx\n",
		fp->rhi, fp->rlo);
#अन्यथा
	pr_info(" r6: 0x%08lx   r7: 0x%08lx   r8: 0x%08lx   r9: 0x%08lx\n",
		fp->regs[0], fp->regs[1], fp->regs[2], fp->regs[3]);
	pr_info("r10: 0x%08lx  r11: 0x%08lx  r12: 0x%08lx  r13: 0x%08lx\n",
		fp->regs[4], fp->regs[5], fp->regs[6], fp->regs[7]);
	pr_info("r14: 0x%08lx   r1: 0x%08lx\n",
		fp->regs[8], fp->regs[9]);
#पूर्ण_अगर

	show_tlb();

	वापस;
पूर्ण
