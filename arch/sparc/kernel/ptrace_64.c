<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ptrace.c: Sparc process tracing support.
 *
 * Copyright (C) 1996, 2008 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *
 * Based upon code written by Ross Biro, Linus Torvalds, Bob Manson,
 * and David Mosberger.
 *
 * Added Linux support -miguel (weird, eh?, the original code was meant
 * to emulate SunOS).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/smp.h>
#समावेश <linux/security.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/audit.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/regset.h>
#समावेश <linux/tracehook.h>
#समावेश <trace/syscall.h>
#समावेश <linux/compat.h>
#समावेश <linux/elf.h>
#समावेश <linux/context_tracking.h>

#समावेश <यंत्र/asi.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/psrcompat.h>
#समावेश <यंत्र/visयंत्र.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/cacheflush.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

#समावेश "entry.h"

/* #घोषणा ALLOW_INIT_TRACING */

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_NAME(n, r) \
	अणु.name = n, .offset = (PT_V9_##r)पूर्ण
#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण

अटल स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
	REG_OFFSET_NAME("g0", G0),
	REG_OFFSET_NAME("g1", G1),
	REG_OFFSET_NAME("g2", G2),
	REG_OFFSET_NAME("g3", G3),
	REG_OFFSET_NAME("g4", G4),
	REG_OFFSET_NAME("g5", G5),
	REG_OFFSET_NAME("g6", G6),
	REG_OFFSET_NAME("g7", G7),

	REG_OFFSET_NAME("i0", I0),
	REG_OFFSET_NAME("i1", I1),
	REG_OFFSET_NAME("i2", I2),
	REG_OFFSET_NAME("i3", I3),
	REG_OFFSET_NAME("i4", I4),
	REG_OFFSET_NAME("i5", I5),
	REG_OFFSET_NAME("i6", I6),
	REG_OFFSET_NAME("i7", I7),

	REG_OFFSET_NAME("tstate", TSTATE),
	REG_OFFSET_NAME("pc", TPC),
	REG_OFFSET_NAME("npc", TNPC),
	REG_OFFSET_NAME("y", Y),
	REG_OFFSET_NAME("lr", I7),

	REG_OFFSET_END,
पूर्ण;

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure single step bits etc are not set.
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	/* nothing to करो */
पूर्ण

/* To get the necessary page काष्ठा, access_process_vm() first calls
 * get_user_pages().  This has करोne a flush_dcache_page() on the
 * accessed page.  Then our caller (copy_अणुto,fromपूर्ण_user_page()) did
 * to स_नकल to पढ़ो/ग_लिखो the data from that page.
 *
 * Now, the only thing we have to करो is:
 * 1) flush the D-cache अगर it's possible than an illegal alias
 *    has been created
 * 2) flush the I-cache अगर this is pre-cheetah and we did a ग_लिखो
 */
व्योम flush_ptrace_access(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			 अचिन्हित दीर्घ uaddr, व्योम *kaddr,
			 अचिन्हित दीर्घ len, पूर्णांक ग_लिखो)
अणु
	BUG_ON(len > PAGE_SIZE);

	अगर (tlb_type == hypervisor)
		वापस;

	preempt_disable();

#अगर_घोषित DCACHE_ALIASING_POSSIBLE
	/* If bit 13 of the kernel address we used to access the
	 * user page is the same as the भव address that page
	 * is mapped to in the user's address space, we can skip the
	 * D-cache flush.
	 */
	अगर ((uaddr ^ (अचिन्हित दीर्घ) kaddr) & (1UL << 13)) अणु
		अचिन्हित दीर्घ start = __pa(kaddr);
		अचिन्हित दीर्घ end = start + len;
		अचिन्हित दीर्घ dcache_line_size;

		dcache_line_size = local_cpu_data().dcache_line_size;

		अगर (tlb_type == spitfire) अणु
			क्रम (; start < end; start += dcache_line_size)
				spitfire_put_dcache_tag(start & 0x3fe0, 0x0);
		पूर्ण अन्यथा अणु
			start &= ~(dcache_line_size - 1);
			क्रम (; start < end; start += dcache_line_size)
				__यंत्र__ __अस्थिर__(
					"stxa %%g0, [%0] %1\n\t"
					"membar #Sync"
					: /* no outमाला_दो */
					: "r" (start),
					"i" (ASI_DCACHE_INVALIDATE));
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (ग_लिखो && tlb_type == spitfire) अणु
		अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) kaddr;
		अचिन्हित दीर्घ end = start + len;
		अचिन्हित दीर्घ icache_line_size;

		icache_line_size = local_cpu_data().icache_line_size;

		क्रम (; start < end; start += icache_line_size)
			flushi(start);
	पूर्ण

	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(flush_ptrace_access);

अटल पूर्णांक get_from_target(काष्ठा task_काष्ठा *target, अचिन्हित दीर्घ uaddr,
			   व्योम *kbuf, पूर्णांक len)
अणु
	अगर (target == current) अणु
		अगर (copy_from_user(kbuf, (व्योम __user *) uaddr, len))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		पूर्णांक len2 = access_process_vm(target, uaddr, kbuf, len,
				FOLL_FORCE);
		अगर (len2 != len)
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_to_target(काष्ठा task_काष्ठा *target, अचिन्हित दीर्घ uaddr,
			 व्योम *kbuf, पूर्णांक len)
अणु
	अगर (target == current) अणु
		अगर (copy_to_user((व्योम __user *) uaddr, kbuf, len))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		पूर्णांक len2 = access_process_vm(target, uaddr, kbuf, len,
				FOLL_FORCE | FOLL_WRITE);
		अगर (len2 != len)
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक regwinकरोw64_get(काष्ठा task_काष्ठा *target,
			   स्थिर काष्ठा pt_regs *regs,
			   काष्ठा reg_winकरोw *wbuf)
अणु
	अचिन्हित दीर्घ rw_addr = regs->u_regs[UREG_I6];

	अगर (!test_thपढ़ो_64bit_stack(rw_addr)) अणु
		काष्ठा reg_winकरोw32 win32;
		पूर्णांक i;

		अगर (get_from_target(target, rw_addr, &win32, माप(win32)))
			वापस -EFAULT;
		क्रम (i = 0; i < 8; i++)
			wbuf->locals[i] = win32.locals[i];
		क्रम (i = 0; i < 8; i++)
			wbuf->ins[i] = win32.ins[i];
	पूर्ण अन्यथा अणु
		rw_addr += STACK_BIAS;
		अगर (get_from_target(target, rw_addr, wbuf, माप(*wbuf)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक regwinकरोw64_set(काष्ठा task_काष्ठा *target,
			   स्थिर काष्ठा pt_regs *regs,
			   काष्ठा reg_winकरोw *wbuf)
अणु
	अचिन्हित दीर्घ rw_addr = regs->u_regs[UREG_I6];

	अगर (!test_thपढ़ो_64bit_stack(rw_addr)) अणु
		काष्ठा reg_winकरोw32 win32;
		पूर्णांक i;

		क्रम (i = 0; i < 8; i++)
			win32.locals[i] = wbuf->locals[i];
		क्रम (i = 0; i < 8; i++)
			win32.ins[i] = wbuf->ins[i];

		अगर (set_to_target(target, rw_addr, &win32, माप(win32)))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		rw_addr += STACK_BIAS;
		अगर (set_to_target(target, rw_addr, wbuf, माप(*wbuf)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत sparc_regset अणु
	REGSET_GENERAL,
	REGSET_FP,
पूर्ण;

अटल पूर्णांक genregs64_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = task_pt_regs(target);
	काष्ठा reg_winकरोw winकरोw;

	अगर (target == current)
		flushw_user();

	membuf_ग_लिखो(&to, regs->u_regs, 16 * माप(u64));
	अगर (!to.left)
		वापस 0;
	अगर (regwinकरोw64_get(target, regs, &winकरोw))
		वापस -EFAULT;
	membuf_ग_लिखो(&to, &winकरोw, 16 * माप(u64));
	/* TSTATE, TPC, TNPC */
	membuf_ग_लिखो(&to, &regs->tstate, 3 * माप(u64));
	वापस membuf_store(&to, (u64)regs->y);
पूर्ण

अटल पूर्णांक genregs64_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	पूर्णांक ret;

	अगर (target == current)
		flushw_user();

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 regs->u_regs,
				 0, 16 * माप(u64));
	अगर (!ret && count && pos < (32 * माप(u64))) अणु
		काष्ठा reg_winकरोw winकरोw;

		अगर (regwinकरोw64_get(target, regs, &winकरोw))
			वापस -EFAULT;

		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &winकरोw,
					 16 * माप(u64),
					 32 * माप(u64));

		अगर (!ret &&
		    regwinकरोw64_set(target, regs, &winकरोw))
			वापस -EFAULT;
	पूर्ण

	अगर (!ret && count > 0) अणु
		अचिन्हित दीर्घ tstate;

		/* TSTATE */
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tstate,
					 32 * माप(u64),
					 33 * माप(u64));
		अगर (!ret) अणु
			/* Only the condition codes and the "in syscall"
			 * state can be modअगरied in the %tstate रेजिस्टर.
			 */
			tstate &= (TSTATE_ICC | TSTATE_XCC | TSTATE_SYSCALL);
			regs->tstate &= ~(TSTATE_ICC | TSTATE_XCC | TSTATE_SYSCALL);
			regs->tstate |= tstate;
		पूर्ण
	पूर्ण

	अगर (!ret) अणु
		/* TPC, TNPC */
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &regs->tpc,
					 33 * माप(u64),
					 35 * माप(u64));
	पूर्ण

	अगर (!ret) अणु
		अचिन्हित दीर्घ y = regs->y;

		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &y,
					 35 * माप(u64),
					 36 * माप(u64));
		अगर (!ret)
			regs->y = y;
	पूर्ण

	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						36 * माप(u64), -1);

	वापस ret;
पूर्ण

अटल पूर्णांक fpregs64_get(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			काष्ठा membuf to)
अणु
	काष्ठा thपढ़ो_info *t = task_thपढ़ो_info(target);
	अचिन्हित दीर्घ fprs;

	अगर (target == current)
		save_and_clear_fpu();

	fprs = t->fpsaved[0];

	अगर (fprs & FPRS_DL)
		membuf_ग_लिखो(&to, t->fpregs, 16 * माप(u64));
	अन्यथा
		membuf_zero(&to, 16 * माप(u64));

	अगर (fprs & FPRS_DU)
		membuf_ग_लिखो(&to, t->fpregs + 16, 16 * माप(u64));
	अन्यथा
		membuf_zero(&to, 16 * माप(u64));
	अगर (fprs & FPRS_FEF) अणु
		membuf_store(&to, t->xfsr[0]);
		membuf_store(&to, t->gsr[0]);
	पूर्ण अन्यथा अणु
		membuf_zero(&to, 2 * माप(u64));
	पूर्ण
	वापस membuf_store(&to, fprs);
पूर्ण

अटल पूर्णांक fpregs64_set(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित दीर्घ *fpregs = task_thपढ़ो_info(target)->fpregs;
	अचिन्हित दीर्घ fprs;
	पूर्णांक ret;

	अगर (target == current)
		save_and_clear_fpu();

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 fpregs,
				 0, 32 * माप(u64));
	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 task_thपढ़ो_info(target)->xfsr,
					 32 * माप(u64),
					 33 * माप(u64));
	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 task_thपढ़ो_info(target)->gsr,
					 33 * माप(u64),
					 34 * माप(u64));

	fprs = task_thपढ़ो_info(target)->fpsaved[0];
	अगर (!ret && count > 0) अणु
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &fprs,
					 34 * माप(u64),
					 35 * माप(u64));
	पूर्ण

	fprs |= (FPRS_FEF | FPRS_DL | FPRS_DU);
	task_thपढ़ो_info(target)->fpsaved[0] = fprs;

	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						35 * माप(u64), -1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा user_regset sparc64_regsets[] = अणु
	/* Format is:
	 * 	G0 --> G7
	 *	O0 --> O7
	 *	L0 --> L7
	 *	I0 --> I7
	 *	TSTATE, TPC, TNPC, Y
	 */
	[REGSET_GENERAL] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = 36,
		.size = माप(u64), .align = माप(u64),
		.regset_get = genregs64_get, .set = genregs64_set
	पूर्ण,
	/* Format is:
	 *	F0 --> F63
	 *	FSR
	 *	GSR
	 *	FPRS
	 */
	[REGSET_FP] = अणु
		.core_note_type = NT_PRFPREG,
		.n = 35,
		.size = माप(u64), .align = माप(u64),
		.regset_get = fpregs64_get, .set = fpregs64_set
	पूर्ण,
पूर्ण;

अटल पूर्णांक getregs64_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = task_pt_regs(target);

	अगर (target == current)
		flushw_user();

	membuf_ग_लिखो(&to, regs->u_regs + 1, 15 * माप(u64));
	membuf_store(&to, (u64)0);
	membuf_ग_लिखो(&to, &regs->tstate, 3 * माप(u64));
	वापस membuf_store(&to, (u64)regs->y);
पूर्ण

अटल पूर्णांक setregs64_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	अचिन्हित दीर्घ y = regs->y;
	अचिन्हित दीर्घ tstate;
	पूर्णांक ret;

	अगर (target == current)
		flushw_user();

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 regs->u_regs + 1,
				 0 * माप(u64),
				 15 * माप(u64));
	अगर (ret)
		वापस ret;
	ret =user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
				 15 * माप(u64), 16 * माप(u64));
	अगर (ret)
		वापस ret;
	/* TSTATE */
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &tstate,
				 16 * माप(u64),
				 17 * माप(u64));
	अगर (ret)
		वापस ret;
	/* Only the condition codes and the "in syscall"
	 * state can be modअगरied in the %tstate रेजिस्टर.
	 */
	tstate &= (TSTATE_ICC | TSTATE_XCC | TSTATE_SYSCALL);
	regs->tstate &= ~(TSTATE_ICC | TSTATE_XCC | TSTATE_SYSCALL);
	regs->tstate |= tstate;

	/* TPC, TNPC */
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &regs->tpc,
				 17 * माप(u64),
				 19 * माप(u64));
	अगर (ret)
		वापस ret;
	/* Y */
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &y,
				 19 * माप(u64),
				 20 * माप(u64));
	अगर (!ret)
		regs->y = y;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा user_regset ptrace64_regsets[] = अणु
	/* Format is:
	 *      G1 --> G7
	 *      O0 --> O7
	 *	0
	 *      TSTATE, TPC, TNPC, Y
	 */
	[REGSET_GENERAL] = अणु
		.n = 20, .size = माप(u64),
		.regset_get = getregs64_get, .set = setregs64_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view ptrace64_view = अणु
	.regsets = ptrace64_regsets, .n = ARRAY_SIZE(ptrace64_regsets)
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_sparc64_view = अणु
	.name = "sparc64", .e_machine = EM_SPARCV9,
	.regsets = sparc64_regsets, .n = ARRAY_SIZE(sparc64_regsets)
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक genregs32_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = task_pt_regs(target);
	u32 uregs[16];
	पूर्णांक i;

	अगर (target == current)
		flushw_user();

	क्रम (i = 0; i < 16; i++)
		membuf_store(&to, (u32)regs->u_regs[i]);
	अगर (!to.left)
		वापस 0;
	अगर (get_from_target(target, regs->u_regs[UREG_I6],
			    uregs, माप(uregs)))
		वापस -EFAULT;
	membuf_ग_लिखो(&to, uregs, 16 * माप(u32));
	membuf_store(&to, (u32)tstate_to_psr(regs->tstate));
	membuf_store(&to, (u32)(regs->tpc));
	membuf_store(&to, (u32)(regs->tnpc));
	membuf_store(&to, (u32)(regs->y));
	वापस membuf_zero(&to, 2 * माप(u32));
पूर्ण

अटल पूर्णांक genregs32_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	compat_uदीर्घ_t __user *reg_winकरोw;
	स्थिर compat_uदीर्घ_t *k = kbuf;
	स्थिर compat_uदीर्घ_t __user *u = ubuf;
	compat_uदीर्घ_t reg;

	अगर (target == current)
		flushw_user();

	pos /= माप(reg);
	count /= माप(reg);

	अगर (kbuf) अणु
		क्रम (; count > 0 && pos < 16; count--)
			regs->u_regs[pos++] = *k++;

		reg_winकरोw = (compat_uदीर्घ_t __user *) regs->u_regs[UREG_I6];
		reg_winकरोw -= 16;
		अगर (target == current) अणु
			क्रम (; count > 0 && pos < 32; count--) अणु
				अगर (put_user(*k++, &reg_winकरोw[pos++]))
					वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (; count > 0 && pos < 32; count--) अणु
				अगर (access_process_vm(target,
						      (अचिन्हित दीर्घ)
						      &reg_winकरोw[pos],
						      (व्योम *) k,
						      माप(*k),
						      FOLL_FORCE | FOLL_WRITE)
				    != माप(*k))
					वापस -EFAULT;
				k++;
				pos++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (; count > 0 && pos < 16; count--) अणु
			अगर (get_user(reg, u++))
				वापस -EFAULT;
			regs->u_regs[pos++] = reg;
		पूर्ण

		reg_winकरोw = (compat_uदीर्घ_t __user *) regs->u_regs[UREG_I6];
		reg_winकरोw -= 16;
		अगर (target == current) अणु
			क्रम (; count > 0 && pos < 32; count--) अणु
				अगर (get_user(reg, u++) ||
				    put_user(reg, &reg_winकरोw[pos++]))
					वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (; count > 0 && pos < 32; count--) अणु
				अगर (get_user(reg, u++))
					वापस -EFAULT;
				अगर (access_process_vm(target,
						      (अचिन्हित दीर्घ)
						      &reg_winकरोw[pos],
						      &reg, माप(reg),
						      FOLL_FORCE | FOLL_WRITE)
				    != माप(reg))
					वापस -EFAULT;
				pos++;
				u++;
			पूर्ण
		पूर्ण
	पूर्ण
	जबतक (count > 0) अणु
		अचिन्हित दीर्घ tstate;

		अगर (kbuf)
			reg = *k++;
		अन्यथा अगर (get_user(reg, u++))
			वापस -EFAULT;

		चयन (pos) अणु
		हाल 32: /* PSR */
			tstate = regs->tstate;
			tstate &= ~(TSTATE_ICC | TSTATE_XCC | TSTATE_SYSCALL);
			tstate |= psr_to_tstate_icc(reg);
			अगर (reg & PSR_SYSCALL)
				tstate |= TSTATE_SYSCALL;
			regs->tstate = tstate;
			अवरोध;
		हाल 33: /* PC */
			regs->tpc = reg;
			अवरोध;
		हाल 34: /* NPC */
			regs->tnpc = reg;
			अवरोध;
		हाल 35: /* Y */
			regs->y = reg;
			अवरोध;
		हाल 36: /* WIM */
		हाल 37: /* TBR */
			अवरोध;
		शेष:
			जाओ finish;
		पूर्ण

		pos++;
		count--;
	पूर्ण
finish:
	pos *= माप(reg);
	count *= माप(reg);

	वापस user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					 38 * माप(reg), -1);
पूर्ण

अटल पूर्णांक fpregs32_get(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			काष्ठा membuf to)
अणु
	काष्ठा thपढ़ो_info *t = task_thपढ़ो_info(target);
	bool enabled;

	अगर (target == current)
		save_and_clear_fpu();

	enabled = t->fpsaved[0] & FPRS_FEF;

	membuf_ग_लिखो(&to, t->fpregs, 32 * माप(u32));
	membuf_zero(&to, माप(u32));
	अगर (enabled)
		membuf_store(&to, (u32)t->xfsr[0]);
	अन्यथा
		membuf_zero(&to, माप(u32));
	membuf_store(&to, (u32)((enabled << 8) | (8 << 16)));
	वापस membuf_zero(&to, 64 * माप(u32));
पूर्ण

अटल पूर्णांक fpregs32_set(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित दीर्घ *fpregs = task_thपढ़ो_info(target)->fpregs;
	अचिन्हित दीर्घ fprs;
	पूर्णांक ret;

	अगर (target == current)
		save_and_clear_fpu();

	fprs = task_thपढ़ो_info(target)->fpsaved[0];

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 fpregs,
				 0, 32 * माप(u32));
	अगर (!ret)
		user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					  32 * माप(u32),
					  33 * माप(u32));
	अगर (!ret && count > 0) अणु
		compat_uदीर्घ_t fsr;
		अचिन्हित दीर्घ val;

		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &fsr,
					 33 * माप(u32),
					 34 * माप(u32));
		अगर (!ret) अणु
			val = task_thपढ़ो_info(target)->xfsr[0];
			val &= 0xffffffff00000000UL;
			val |= fsr;
			task_thपढ़ो_info(target)->xfsr[0] = val;
		पूर्ण
	पूर्ण

	fprs |= (FPRS_FEF | FPRS_DL);
	task_thपढ़ो_info(target)->fpsaved[0] = fprs;

	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						34 * माप(u32), -1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा user_regset sparc32_regsets[] = अणु
	/* Format is:
	 * 	G0 --> G7
	 *	O0 --> O7
	 *	L0 --> L7
	 *	I0 --> I7
	 *	PSR, PC, nPC, Y, WIM, TBR
	 */
	[REGSET_GENERAL] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = 38,
		.size = माप(u32), .align = माप(u32),
		.regset_get = genregs32_get, .set = genregs32_set
	पूर्ण,
	/* Format is:
	 *	F0 --> F31
	 *	empty 32-bit word
	 *	FSR (32--bit word)
	 *	FPU QUEUE COUNT (8-bit अक्षर)
	 *	FPU QUEUE ENTRYSIZE (8-bit अक्षर)
	 *	FPU ENABLED (8-bit अक्षर)
	 *	empty 8-bit अक्षर
	 *	FPU QUEUE (64 32-bit पूर्णांकs)
	 */
	[REGSET_FP] = अणु
		.core_note_type = NT_PRFPREG,
		.n = 99,
		.size = माप(u32), .align = माप(u32),
		.regset_get = fpregs32_get, .set = fpregs32_set
	पूर्ण,
पूर्ण;

अटल पूर्णांक getregs_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = task_pt_regs(target);
	पूर्णांक i;

	अगर (target == current)
		flushw_user();

	membuf_store(&to, (u32)tstate_to_psr(regs->tstate));
	membuf_store(&to, (u32)(regs->tpc));
	membuf_store(&to, (u32)(regs->tnpc));
	membuf_store(&to, (u32)(regs->y));
	क्रम (i = 1; i < 16; i++)
		membuf_store(&to, (u32)regs->u_regs[i]);
	वापस to.left;
पूर्ण

अटल पूर्णांक setregs_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	अचिन्हित दीर्घ tstate;
	u32 uregs[19];
	पूर्णांक i, ret;

	अगर (target == current)
		flushw_user();

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 uregs,
				 0, 19 * माप(u32));
	अगर (ret)
		वापस ret;

	tstate = regs->tstate;
	tstate &= ~(TSTATE_ICC | TSTATE_XCC | TSTATE_SYSCALL);
	tstate |= psr_to_tstate_icc(uregs[0]);
	अगर (uregs[0] & PSR_SYSCALL)
		tstate |= TSTATE_SYSCALL;
	regs->tstate = tstate;
	regs->tpc = uregs[1];
	regs->tnpc = uregs[2];
	regs->y = uregs[3];

	क्रम (i = 1; i < 15; i++)
		regs->u_regs[i] = uregs[3 + i];
	वापस 0;
पूर्ण

अटल पूर्णांक getfpregs_get(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			काष्ठा membuf to)
अणु
	काष्ठा thपढ़ो_info *t = task_thपढ़ो_info(target);

	अगर (target == current)
		save_and_clear_fpu();

	membuf_ग_लिखो(&to, t->fpregs, 32 * माप(u32));
	अगर (t->fpsaved[0] & FPRS_FEF)
		membuf_store(&to, (u32)t->xfsr[0]);
	अन्यथा
		membuf_zero(&to, माप(u32));
	वापस membuf_zero(&to, 35 * माप(u32));
पूर्ण

अटल पूर्णांक setfpregs_set(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित दीर्घ *fpregs = task_thपढ़ो_info(target)->fpregs;
	अचिन्हित दीर्घ fprs;
	पूर्णांक ret;

	अगर (target == current)
		save_and_clear_fpu();

	fprs = task_thपढ़ो_info(target)->fpsaved[0];

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 fpregs,
				 0, 32 * माप(u32));
	अगर (!ret) अणु
		compat_uदीर्घ_t fsr;
		अचिन्हित दीर्घ val;

		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &fsr,
					 32 * माप(u32),
					 33 * माप(u32));
		अगर (!ret) अणु
			val = task_thपढ़ो_info(target)->xfsr[0];
			val &= 0xffffffff00000000UL;
			val |= fsr;
			task_thपढ़ो_info(target)->xfsr[0] = val;
		पूर्ण
	पूर्ण

	fprs |= (FPRS_FEF | FPRS_DL);
	task_thपढ़ो_info(target)->fpsaved[0] = fprs;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा user_regset ptrace32_regsets[] = अणु
	[REGSET_GENERAL] = अणु
		.n = 19, .size = माप(u32),
		.regset_get = getregs_get, .set = setregs_set,
	पूर्ण,
	[REGSET_FP] = अणु
		.n = 68, .size = माप(u32),
		.regset_get = getfpregs_get, .set = setfpregs_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view ptrace32_view = अणु
	.regsets = ptrace32_regsets, .n = ARRAY_SIZE(ptrace32_regsets)
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_sparc32_view = अणु
	.name = "sparc", .e_machine = EM_SPARC,
	.regsets = sparc32_regsets, .n = ARRAY_SIZE(sparc32_regsets)
पूर्ण;
#पूर्ण_अगर /* CONFIG_COMPAT */

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (test_tsk_thपढ़ो_flag(task, TIF_32BIT))
		वापस &user_sparc32_view;
#पूर्ण_अगर
	वापस &user_sparc64_view;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_fps अणु
	अचिन्हित पूर्णांक regs[32];
	अचिन्हित पूर्णांक fsr;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक extra;
	अचिन्हित पूर्णांक fpqd;
	काष्ठा compat_fq अणु
		अचिन्हित पूर्णांक insnaddr;
		अचिन्हित पूर्णांक insn;
	पूर्ण fpq[16];
पूर्ण;

दीर्घ compat_arch_ptrace(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			compat_uदीर्घ_t caddr, compat_uदीर्घ_t cdata)
अणु
	compat_uदीर्घ_t caddr2 = task_pt_regs(current)->u_regs[UREG_I4];
	काष्ठा pt_regs32 __user *pregs;
	काष्ठा compat_fps __user *fps;
	अचिन्हित दीर्घ addr2 = caddr2;
	अचिन्हित दीर्घ addr = caddr;
	अचिन्हित दीर्घ data = cdata;
	पूर्णांक ret;

	pregs = (काष्ठा pt_regs32 __user *) addr;
	fps = (काष्ठा compat_fps __user *) addr;

	चयन (request) अणु
	हाल PTRACE_PEEKUSR:
		ret = (addr != 0) ? -EIO : 0;
		अवरोध;

	हाल PTRACE_GETREGS:
		ret = copy_regset_to_user(child, &ptrace32_view,
					  REGSET_GENERAL, 0,
					  19 * माप(u32),
					  pregs);
		अवरोध;

	हाल PTRACE_SETREGS:
		ret = copy_regset_from_user(child, &ptrace32_view,
					  REGSET_GENERAL, 0,
					  19 * माप(u32),
					  pregs);
		अवरोध;

	हाल PTRACE_GETFPREGS:
		ret = copy_regset_to_user(child, &ptrace32_view,
					  REGSET_FP, 0,
					  68 * माप(u32),
					  fps);
		अवरोध;

	हाल PTRACE_SETFPREGS:
		ret = copy_regset_from_user(child, &ptrace32_view,
					  REGSET_FP, 0,
					  33 * माप(u32),
					  fps);
		अवरोध;

	हाल PTRACE_READTEXT:
	हाल PTRACE_READDATA:
		ret = ptrace_पढ़ोdata(child, addr,
				      (अक्षर __user *)addr2, data);
		अगर (ret == data)
			ret = 0;
		अन्यथा अगर (ret >= 0)
			ret = -EIO;
		अवरोध;

	हाल PTRACE_WRITETEXT:
	हाल PTRACE_WRITEDATA:
		ret = ptrace_ग_लिखोdata(child, (अक्षर __user *) addr2,
				       addr, data);
		अगर (ret == data)
			ret = 0;
		अन्यथा अगर (ret >= 0)
			ret = -EIO;
		अवरोध;

	शेष:
		अगर (request == PTRACE_SPARC_DETACH)
			request = PTRACE_DETACH;
		ret = compat_ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

काष्ठा fps अणु
	अचिन्हित पूर्णांक regs[64];
	अचिन्हित दीर्घ fsr;
पूर्ण;

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	स्थिर काष्ठा user_regset_view *view = task_user_regset_view(current);
	अचिन्हित दीर्घ addr2 = task_pt_regs(current)->u_regs[UREG_I4];
	काष्ठा pt_regs __user *pregs;
	काष्ठा fps __user *fps;
	व्योम __user *addr2p;
	पूर्णांक ret;

	pregs = (काष्ठा pt_regs __user *) addr;
	fps = (काष्ठा fps __user *) addr;
	addr2p = (व्योम __user *) addr2;

	चयन (request) अणु
	हाल PTRACE_PEEKUSR:
		ret = (addr != 0) ? -EIO : 0;
		अवरोध;

	हाल PTRACE_GETREGS64:
		ret = copy_regset_to_user(child, &ptrace64_view,
					  REGSET_GENERAL, 0,
					  19 * माप(u64),
					  pregs);
		अवरोध;

	हाल PTRACE_SETREGS64:
		ret = copy_regset_from_user(child, &ptrace64_view,
					  REGSET_GENERAL, 0,
					  19 * माप(u64),
					  pregs);
		अवरोध;

	हाल PTRACE_GETFPREGS64:
		ret = copy_regset_to_user(child, view, REGSET_FP,
					  0 * माप(u64),
					  33 * माप(u64),
					  fps);
		अवरोध;

	हाल PTRACE_SETFPREGS64:
		ret = copy_regset_from_user(child, view, REGSET_FP,
					  0 * माप(u64),
					  33 * माप(u64),
					  fps);
		अवरोध;

	हाल PTRACE_READTEXT:
	हाल PTRACE_READDATA:
		ret = ptrace_पढ़ोdata(child, addr, addr2p, data);
		अगर (ret == data)
			ret = 0;
		अन्यथा अगर (ret >= 0)
			ret = -EIO;
		अवरोध;

	हाल PTRACE_WRITETEXT:
	हाल PTRACE_WRITEDATA:
		ret = ptrace_ग_लिखोdata(child, addr2p, addr, data);
		अगर (ret == data)
			ret = 0;
		अन्यथा अगर (ret >= 0)
			ret = -EIO;
		अवरोध;

	शेष:
		अगर (request == PTRACE_SPARC_DETACH)
			request = PTRACE_DETACH;
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

यंत्रlinkage पूर्णांक syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret = 0;

	/* करो the secure computing check first */
	secure_computing_strict(regs->u_regs[UREG_G1]);

	अगर (test_thपढ़ो_flag(TIF_NOHZ))
		user_निकास();

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		ret = tracehook_report_syscall_entry(regs);

	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->u_regs[UREG_G1]);

	audit_syscall_entry(regs->u_regs[UREG_G1], regs->u_regs[UREG_I0],
			    regs->u_regs[UREG_I1], regs->u_regs[UREG_I2],
			    regs->u_regs[UREG_I3]);

	वापस ret;
पूर्ण

यंत्रlinkage व्योम syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
	अगर (test_thपढ़ो_flag(TIF_NOHZ))
		user_निकास();

	audit_syscall_निकास(regs);

	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_निकास(regs, regs->u_regs[UREG_I0]);

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, 0);

	अगर (test_thपढ़ो_flag(TIF_NOHZ))
		user_enter();
पूर्ण

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
 * @regs:	pt_regs which contains kernel stack poपूर्णांकer.
 * @addr:	address which is checked.
 *
 * regs_within_kernel_stack() checks @addr is within the kernel stack page(s).
 * If @addr is within the kernel stack, it वापसs true. If not, वापसs false.
 */
अटल अंतरभूत पूर्णांक regs_within_kernel_stack(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ksp = kernel_stack_poपूर्णांकer(regs) + STACK_BIAS;
	वापस ((addr & ~(THREAD_SIZE - 1))  ==
		(ksp & ~(THREAD_SIZE - 1)));
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
	अचिन्हित दीर्घ ksp = kernel_stack_poपूर्णांकer(regs) + STACK_BIAS;
	अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *)ksp;
	addr += n;
	अगर (regs_within_kernel_stack(regs, (अचिन्हित दीर्घ)addr))
		वापस *addr;
	अन्यथा
		वापस 0;
पूर्ण
