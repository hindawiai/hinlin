<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/ptrace.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/regset.h>
#समावेश <linux/unistd.h>
#समावेश <linux/elf.h>

अटल काष्ठा callee_regs *task_callee_regs(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा callee_regs *पंचांगp = (काष्ठा callee_regs *)tsk->thपढ़ो.callee_reg;
	वापस पंचांगp;
पूर्ण

अटल पूर्णांक genregs_get(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *ptregs = task_pt_regs(target);
	स्थिर काष्ठा callee_regs *cregs = task_callee_regs(target);
	अचिन्हित पूर्णांक stop_pc_val;

	membuf_zero(&to, 4);	// pad
	membuf_store(&to, ptregs->bta);
	membuf_store(&to, ptregs->lp_start);
	membuf_store(&to, ptregs->lp_end);
	membuf_store(&to, ptregs->lp_count);
	membuf_store(&to, ptregs->status32);
	membuf_store(&to, ptregs->ret);
	membuf_store(&to, ptregs->blink);
	membuf_store(&to, ptregs->fp);
	membuf_store(&to, ptregs->r26);	// gp
	membuf_store(&to, ptregs->r12);
	membuf_store(&to, ptregs->r11);
	membuf_store(&to, ptregs->r10);
	membuf_store(&to, ptregs->r9);
	membuf_store(&to, ptregs->r8);
	membuf_store(&to, ptregs->r7);
	membuf_store(&to, ptregs->r6);
	membuf_store(&to, ptregs->r5);
	membuf_store(&to, ptregs->r4);
	membuf_store(&to, ptregs->r3);
	membuf_store(&to, ptregs->r2);
	membuf_store(&to, ptregs->r1);
	membuf_store(&to, ptregs->r0);
	membuf_store(&to, ptregs->sp);
	membuf_zero(&to, 4);	// pad2
	membuf_store(&to, cregs->r25);
	membuf_store(&to, cregs->r24);
	membuf_store(&to, cregs->r23);
	membuf_store(&to, cregs->r22);
	membuf_store(&to, cregs->r21);
	membuf_store(&to, cregs->r20);
	membuf_store(&to, cregs->r19);
	membuf_store(&to, cregs->r18);
	membuf_store(&to, cregs->r17);
	membuf_store(&to, cregs->r16);
	membuf_store(&to, cregs->r15);
	membuf_store(&to, cregs->r14);
	membuf_store(&to, cregs->r13);
	membuf_store(&to, target->thपढ़ो.fault_address); // efa

	अगर (in_brkpt_trap(ptregs)) अणु
		stop_pc_val = target->thपढ़ो.fault_address;
		pr_debug("\t\tstop_pc (brk-pt)\n");
	पूर्ण अन्यथा अणु
		stop_pc_val = ptregs->ret;
		pr_debug("\t\tstop_pc (others)\n");
	पूर्ण

	वापस membuf_store(&to, stop_pc_val); // stop_pc
पूर्ण

अटल पूर्णांक genregs_set(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	स्थिर काष्ठा pt_regs *ptregs = task_pt_regs(target);
	स्थिर काष्ठा callee_regs *cregs = task_callee_regs(target);
	पूर्णांक ret = 0;

#घोषणा REG_IN_CHUNK(FIRST, NEXT, PTR)	\
	अगर (!ret)			\
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, \
			(व्योम *)(PTR), \
			दुरत्व(काष्ठा user_regs_काष्ठा, FIRST), \
			दुरत्व(काष्ठा user_regs_काष्ठा, NEXT));

#घोषणा REG_IN_ONE(LOC, PTR)		\
	अगर (!ret)			\
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, \
			(व्योम *)(PTR), \
			दुरत्व(काष्ठा user_regs_काष्ठा, LOC), \
			दुरत्व(काष्ठा user_regs_काष्ठा, LOC) + 4);

#घोषणा REG_IGNORE_ONE(LOC)		\
	अगर (!ret)			\
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf, \
			दुरत्व(काष्ठा user_regs_काष्ठा, LOC), \
			दुरत्व(काष्ठा user_regs_काष्ठा, LOC) + 4);

	REG_IGNORE_ONE(pad);

	REG_IN_ONE(scratch.bta, &ptregs->bta);
	REG_IN_ONE(scratch.lp_start, &ptregs->lp_start);
	REG_IN_ONE(scratch.lp_end, &ptregs->lp_end);
	REG_IN_ONE(scratch.lp_count, &ptregs->lp_count);

	REG_IGNORE_ONE(scratch.status32);

	REG_IN_ONE(scratch.ret, &ptregs->ret);
	REG_IN_ONE(scratch.blink, &ptregs->blink);
	REG_IN_ONE(scratch.fp, &ptregs->fp);
	REG_IN_ONE(scratch.gp, &ptregs->r26);
	REG_IN_ONE(scratch.r12, &ptregs->r12);
	REG_IN_ONE(scratch.r11, &ptregs->r11);
	REG_IN_ONE(scratch.r10, &ptregs->r10);
	REG_IN_ONE(scratch.r9, &ptregs->r9);
	REG_IN_ONE(scratch.r8, &ptregs->r8);
	REG_IN_ONE(scratch.r7, &ptregs->r7);
	REG_IN_ONE(scratch.r6, &ptregs->r6);
	REG_IN_ONE(scratch.r5, &ptregs->r5);
	REG_IN_ONE(scratch.r4, &ptregs->r4);
	REG_IN_ONE(scratch.r3, &ptregs->r3);
	REG_IN_ONE(scratch.r2, &ptregs->r2);
	REG_IN_ONE(scratch.r1, &ptregs->r1);
	REG_IN_ONE(scratch.r0, &ptregs->r0);
	REG_IN_ONE(scratch.sp, &ptregs->sp);

	REG_IGNORE_ONE(pad2);

	REG_IN_ONE(callee.r25, &cregs->r25);
	REG_IN_ONE(callee.r24, &cregs->r24);
	REG_IN_ONE(callee.r23, &cregs->r23);
	REG_IN_ONE(callee.r22, &cregs->r22);
	REG_IN_ONE(callee.r21, &cregs->r21);
	REG_IN_ONE(callee.r20, &cregs->r20);
	REG_IN_ONE(callee.r19, &cregs->r19);
	REG_IN_ONE(callee.r18, &cregs->r18);
	REG_IN_ONE(callee.r17, &cregs->r17);
	REG_IN_ONE(callee.r16, &cregs->r16);
	REG_IN_ONE(callee.r15, &cregs->r15);
	REG_IN_ONE(callee.r14, &cregs->r14);
	REG_IN_ONE(callee.r13, &cregs->r13);

	REG_IGNORE_ONE(efa);			/* efa update invalid */
	REG_IGNORE_ONE(stop_pc);		/* PC updated via @ret */

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ISA_ARCV2
अटल पूर्णांक arcv2regs_get(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = task_pt_regs(target);

	अगर (IS_ENABLED(CONFIG_ARC_HAS_ACCL_REGS))
		/*
		 * itemized copy not needed like above as layout of regs (r30,r58,r59)
		 * is exactly same in kernel (pt_regs) and userspace (user_regs_arcv2)
		 */
		वापस membuf_ग_लिखो(&to, &regs->r30, माप(काष्ठा user_regs_arcv2));


	membuf_ग_लिखो(&to, &regs->r30, 4); /* r30 only */
	वापस membuf_zero(&to, माप(काष्ठा user_regs_arcv2) - 4);
पूर्ण

अटल पूर्णांक arcv2regs_set(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	स्थिर काष्ठा pt_regs *regs = task_pt_regs(target);
	पूर्णांक ret, copy_sz;

	अगर (IS_ENABLED(CONFIG_ARC_HAS_ACCL_REGS))
		copy_sz = माप(काष्ठा user_regs_arcv2);
	अन्यथा
		copy_sz = 4;	/* r30 only */

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, (व्योम *)&regs->r30,
				  0, copy_sz);

	वापस ret;
पूर्ण

#पूर्ण_अगर

क्रमागत arc_माला_लोet अणु
	REGSET_CMN,
	REGSET_ARCV2,
पूर्ण;

अटल स्थिर काष्ठा user_regset arc_regsets[] = अणु
	[REGSET_CMN] = अणु
	       .core_note_type = NT_PRSTATUS,
	       .n = ELF_NGREG,
	       .size = माप(अचिन्हित दीर्घ),
	       .align = माप(अचिन्हित दीर्घ),
	       .regset_get = genregs_get,
	       .set = genregs_set,
	पूर्ण,
#अगर_घोषित CONFIG_ISA_ARCV2
	[REGSET_ARCV2] = अणु
	       .core_note_type = NT_ARC_V2,
	       .n = ELF_ARCV2REG,
	       .size = माप(अचिन्हित दीर्घ),
	       .align = माप(अचिन्हित दीर्घ),
	       .regset_get = arcv2regs_get,
	       .set = arcv2regs_set,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_arc_view = अणु
	.name		= "arc",
	.e_machine	= EM_ARC_INUSE,
	.regsets	= arc_regsets,
	.n		= ARRAY_SIZE(arc_regsets)
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &user_arc_view;
पूर्ण

व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret = -EIO;

	pr_debug("REQ=%ld: ADDR =0x%lx, DATA=0x%lx)\n", request, addr, data);

	चयन (request) अणु
	हाल PTRACE_GET_THREAD_AREA:
		ret = put_user(task_thपढ़ो_info(child)->thr_ptr,
			       (अचिन्हित दीर्घ __user *)data);
		अवरोध;
	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

यंत्रlinkage पूर्णांक syscall_trace_entry(काष्ठा pt_regs *regs)
अणु
	अगर (tracehook_report_syscall_entry(regs))
		वापस अच_दीर्घ_उच्च;

	वापस regs->r8;
पूर्ण

यंत्रlinkage व्योम syscall_trace_निकास(काष्ठा pt_regs *regs)
अणु
	tracehook_report_syscall_निकास(regs, 0);
पूर्ण
