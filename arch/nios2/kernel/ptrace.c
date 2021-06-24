<शैली गुरु>
/*
 * Copyright (C) 2014 Altera Corporation
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#समावेश <linux/elf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/regset.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/user.h>

अटल पूर्णांक genregs_get(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = task_pt_regs(target);
	स्थिर काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *)regs - 1;

	membuf_zero(&to, 4); // R0
	membuf_ग_लिखो(&to, &regs->r1, 7 * 4); // R1..R7
	membuf_ग_लिखो(&to, &regs->r8, 8 * 4); // R8..R15
	membuf_ग_लिखो(&to, sw, 8 * 4); // R16..R23
	membuf_zero(&to, 2 * 4); /* et and bt */
	membuf_store(&to, regs->gp);
	membuf_store(&to, regs->sp);
	membuf_store(&to, regs->fp);
	membuf_store(&to, regs->ea);
	membuf_zero(&to, 4); // PTR_BA
	membuf_store(&to, regs->ra);
	membuf_store(&to, regs->ea); /* use ea क्रम PC */
	वापस membuf_zero(&to, (NUM_PTRACE_REG - PTR_PC) * 4);
पूर्ण

/*
 * Set the thपढ़ो state from a regset passed in via ptrace
 */
अटल पूर्णांक genregs_set(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	स्थिर काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *)regs - 1;
	पूर्णांक ret = 0;

#घोषणा REG_IGNORE_RANGE(START, END)		\
	अगर (!ret)					\
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf, \
			START * 4, (END * 4) + 4);

#घोषणा REG_IN_ONE(PTR, LOC)	\
	अगर (!ret)			\
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, \
			(व्योम *)(PTR), LOC * 4, (LOC * 4) + 4);

#घोषणा REG_IN_RANGE(PTR, START, END)	\
	अगर (!ret)				\
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, \
			(व्योम *)(PTR), START * 4, (END * 4) + 4);

	REG_IGNORE_RANGE(PTR_R0, PTR_R0);
	REG_IN_RANGE(&regs->r1, PTR_R1, PTR_R7);
	REG_IN_RANGE(&regs->r8, PTR_R8, PTR_R15);
	REG_IN_RANGE(sw, PTR_R16, PTR_R23);
	REG_IGNORE_RANGE(PTR_R24, PTR_R25); /* et and bt */
	REG_IN_ONE(&regs->gp, PTR_GP);
	REG_IN_ONE(&regs->sp, PTR_SP);
	REG_IN_ONE(&regs->fp, PTR_FP);
	REG_IN_ONE(&regs->ea, PTR_EA);
	REG_IGNORE_RANGE(PTR_BA, PTR_BA);
	REG_IN_ONE(&regs->ra, PTR_RA);
	REG_IN_ONE(&regs->ea, PTR_PC); /* use ea क्रम PC */
	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					 PTR_STATUS * 4, -1);

	वापस ret;
पूर्ण

/*
 * Define the रेजिस्टर sets available on Nios2 under Linux
 */
क्रमागत nios2_regset अणु
	REGSET_GENERAL,
पूर्ण;

अटल स्थिर काष्ठा user_regset nios2_regsets[] = अणु
	[REGSET_GENERAL] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = NUM_PTRACE_REG,
		.size = माप(अचिन्हित दीर्घ),
		.align = माप(अचिन्हित दीर्घ),
		.regset_get = genregs_get,
		.set = genregs_set,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा user_regset_view nios2_user_view = अणु
	.name = "nios2",
	.e_machine = ELF_ARCH,
	.ei_osabi = ELF_OSABI,
	.regsets = nios2_regsets,
	.n = ARRAY_SIZE(nios2_regsets)
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &nios2_user_view;
पूर्ण

व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु

पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request, अचिन्हित दीर्घ addr,
		 अचिन्हित दीर्घ data)
अणु
	वापस ptrace_request(child, request, addr, data);
पूर्ण

यंत्रlinkage पूर्णांक करो_syscall_trace_enter(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		ret = tracehook_report_syscall_entry(task_pt_regs(current));

	वापस ret;
पूर्ण

यंत्रlinkage व्योम करो_syscall_trace_निकास(व्योम)
अणु
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(task_pt_regs(current), 0);
पूर्ण
