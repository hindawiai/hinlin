<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ptrace support क्रम Hexagon
 *
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/regset.h>
#समावेश <linux/user.h>
#समावेश <linux/elf.h>

#समावेश <यंत्र/user.h>

#अगर arch_has_single_step()
/*  Both called from ptrace_resume  */
व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	pt_set_singlestep(task_pt_regs(child));
	set_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	pt_clr_singlestep(task_pt_regs(child));
	clear_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक genregs_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);

	/* The general idea here is that the copyout must happen in
	 * exactly the same order in which the userspace expects these
	 * regs. Now, the sequence in userspace करोes not match the
	 * sequence in the kernel, so everything past the 32 gprs
	 * happens one at a समय.
	 */
	membuf_ग_लिखो(&to, &regs->r00, 32*माप(अचिन्हित दीर्घ));
	/* Must be exactly same sequence as काष्ठा user_regs_काष्ठा */
	membuf_store(&to, regs->sa0);
	membuf_store(&to, regs->lc0);
	membuf_store(&to, regs->sa1);
	membuf_store(&to, regs->lc1);
	membuf_store(&to, regs->m0);
	membuf_store(&to, regs->m1);
	membuf_store(&to, regs->usr);
	membuf_store(&to, regs->preds);
	membuf_store(&to, regs->gp);
	membuf_store(&to, regs->ugp);
	membuf_store(&to, pt_elr(regs)); // pc
	membuf_store(&to, (अचिन्हित दीर्घ)pt_cause(regs)); // cause
	membuf_store(&to, pt_badva(regs)); // badva
#अगर CONFIG_HEXAGON_ARCH_VERSION >=4
	membuf_store(&to, regs->cs0);
	membuf_store(&to, regs->cs1);
	वापस membuf_zero(&to, माप(अचिन्हित दीर्घ));
#अन्यथा
	वापस membuf_zero(&to, 3 * माप(अचिन्हित दीर्घ));
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक genregs_set(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ bucket;
	काष्ठा pt_regs *regs = task_pt_regs(target);

	अगर (!regs)
		वापस -EIO;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &regs->r00, 0, 32*माप(अचिन्हित दीर्घ));

#घोषणा INEXT(KPT_REG, USR_REG) \
	अगर (!ret) \
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, \
			KPT_REG, दुरत्व(काष्ठा user_regs_काष्ठा, USR_REG), \
			दुरत्व(काष्ठा user_regs_काष्ठा, USR_REG) + \
				माप(अचिन्हित दीर्घ));

	/* Must be exactly same sequence as काष्ठा user_regs_काष्ठा */
	INEXT(&regs->sa0, sa0);
	INEXT(&regs->lc0, lc0);
	INEXT(&regs->sa1, sa1);
	INEXT(&regs->lc1, lc1);
	INEXT(&regs->m0, m0);
	INEXT(&regs->m1, m1);
	INEXT(&regs->usr, usr);
	INEXT(&regs->preds, p3_0);
	INEXT(&regs->gp, gp);
	INEXT(&regs->ugp, ugp);
	INEXT(&pt_elr(regs), pc);

	/* CAUSE and BADVA aren't ग_लिखोable. */
	INEXT(&bucket, cause);
	INEXT(&bucket, badva);

#अगर CONFIG_HEXAGON_ARCH_VERSION >=4
	INEXT(&regs->cs0, cs0);
	INEXT(&regs->cs1, cs1);
#पूर्ण_अगर

	/* Ignore the rest, अगर needed */
	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					दुरत्व(काष्ठा user_regs_काष्ठा, pad1), -1);

	अगर (ret)
		वापस ret;

	/*
	 * This is special; SP is actually restored by the VM via the
	 * special event record which is set by the special trap.
	 */
	regs->hvmer.vmpsp = regs->r29;
	वापस 0;
पूर्ण

क्रमागत hexagon_regset अणु
	REGSET_GENERAL,
पूर्ण;

अटल स्थिर काष्ठा user_regset hexagon_regsets[] = अणु
	[REGSET_GENERAL] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = ELF_NGREG,
		.size = माप(अचिन्हित दीर्घ),
		.align = माप(अचिन्हित दीर्घ),
		.regset_get = genregs_get,
		.set = genregs_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view hexagon_user_view = अणु
	.name = "hexagon",
	.e_machine = ELF_ARCH,
	.ei_osabi = ELF_OSABI,
	.regsets = hexagon_regsets,
	.e_flags = ELF_CORE_EFLAGS,
	.n = ARRAY_SIZE(hexagon_regsets)
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &hexagon_user_view;
पूर्ण

व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	/* Boilerplate - resolves to null अंतरभूत अगर no HW single-step */
	user_disable_single_step(child);
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	वापस ptrace_request(child, request, addr, data);
पूर्ण
