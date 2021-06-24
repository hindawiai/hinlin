<शैली गुरु>
/*
 *  linux/arch/m68k/kernel/ptrace.c
 *
 *  Copyright (C) 1994 by Hamish Macकरोnald
 *  Taken from linux/kernel/ptrace.c and modअगरied क्रम M680x0.
 *  linux/kernel/ptrace.c is by Ross Biro 1/23/92, edited by Linus Torvalds
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of
 * this archive क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/tracehook.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>

/*
 * करोes not yet catch संकेतs sent when the child dies.
 * in निकास.c or in संकेत.c.
 */

/* determines which bits in the SR the user has access to. */
/* 1 = access 0 = no access */
#घोषणा SR_MASK 0x001f

/* sets the trace bits. */
#घोषणा TRACE_BITS 0xC000
#घोषणा T1_BIT 0x8000
#घोषणा T0_BIT 0x4000

/* Find the stack offset क्रम a रेजिस्टर, relative to thपढ़ो.esp0. */
#घोषणा PT_REG(reg)	((दीर्घ)&((काष्ठा pt_regs *)0)->reg)
#घोषणा SW_REG(reg)	((दीर्घ)&((काष्ठा चयन_stack *)0)->reg \
			 - माप(काष्ठा चयन_stack))
/* Mapping from PT_xxx to the stack offset at which the रेजिस्टर is
   saved.  Notice that usp has no stack-slot and needs to be treated
   specially (see get_reg/put_reg below). */
अटल स्थिर पूर्णांक regoff[] = अणु
	[0]	= PT_REG(d1),
	[1]	= PT_REG(d2),
	[2]	= PT_REG(d3),
	[3]	= PT_REG(d4),
	[4]	= PT_REG(d5),
	[5]	= SW_REG(d6),
	[6]	= SW_REG(d7),
	[7]	= PT_REG(a0),
	[8]	= PT_REG(a1),
	[9]	= PT_REG(a2),
	[10]	= SW_REG(a3),
	[11]	= SW_REG(a4),
	[12]	= SW_REG(a5),
	[13]	= SW_REG(a6),
	[14]	= PT_REG(d0),
	[15]	= -1,
	[16]	= PT_REG(orig_d0),
	[17]	= PT_REG(sr),
	[18]	= PT_REG(pc),
पूर्ण;

/*
 * Get contents of रेजिस्टर REGNO in task TASK.
 */
अटल अंतरभूत दीर्घ get_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno)
अणु
	अचिन्हित दीर्घ *addr;

	अगर (regno == PT_USP)
		addr = &task->thपढ़ो.usp;
	अन्यथा अगर (regno < ARRAY_SIZE(regoff))
		addr = (अचिन्हित दीर्घ *)(task->thपढ़ो.esp0 + regoff[regno]);
	अन्यथा
		वापस 0;
	/* Need to take stkadj पूर्णांकo account. */
	अगर (regno == PT_SR || regno == PT_PC) अणु
		दीर्घ stkadj = *(दीर्घ *)(task->thपढ़ो.esp0 + PT_REG(stkadj));
		addr = (अचिन्हित दीर्घ *) ((अचिन्हित दीर्घ)addr + stkadj);
		/* The sr is actually a 16 bit रेजिस्टर.  */
		अगर (regno == PT_SR)
			वापस *(अचिन्हित लघु *)addr;
	पूर्ण
	वापस *addr;
पूर्ण

/*
 * Write contents of रेजिस्टर REGNO in task TASK.
 */
अटल अंतरभूत पूर्णांक put_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno,
			  अचिन्हित दीर्घ data)
अणु
	अचिन्हित दीर्घ *addr;

	अगर (regno == PT_USP)
		addr = &task->thपढ़ो.usp;
	अन्यथा अगर (regno < ARRAY_SIZE(regoff))
		addr = (अचिन्हित दीर्घ *)(task->thपढ़ो.esp0 + regoff[regno]);
	अन्यथा
		वापस -1;
	/* Need to take stkadj पूर्णांकo account. */
	अगर (regno == PT_SR || regno == PT_PC) अणु
		दीर्घ stkadj = *(दीर्घ *)(task->thपढ़ो.esp0 + PT_REG(stkadj));
		addr = (अचिन्हित दीर्घ *) ((अचिन्हित दीर्घ)addr + stkadj);
		/* The sr is actually a 16 bit रेजिस्टर.  */
		अगर (regno == PT_SR) अणु
			*(अचिन्हित लघु *)addr = data;
			वापस 0;
		पूर्ण
	पूर्ण
	*addr = data;
	वापस 0;
पूर्ण

/*
 * Make sure the single step bit is not set.
 */
अटल अंतरभूत व्योम singlestep_disable(काष्ठा task_काष्ठा *child)
अणु
	अचिन्हित दीर्घ पंचांगp = get_reg(child, PT_SR) & ~TRACE_BITS;
	put_reg(child, PT_SR, पंचांगp);
	clear_tsk_thपढ़ो_flag(child, TIF_DELAYED_TRACE);
पूर्ण

/*
 * Called by kernel/ptrace.c when detaching..
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	singlestep_disable(child);
पूर्ण

व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	अचिन्हित दीर्घ पंचांगp = get_reg(child, PT_SR) & ~TRACE_BITS;
	put_reg(child, PT_SR, पंचांगp | T1_BIT);
	set_tsk_thपढ़ो_flag(child, TIF_DELAYED_TRACE);
पूर्ण

#अगर_घोषित CONFIG_MMU
व्योम user_enable_block_step(काष्ठा task_काष्ठा *child)
अणु
	अचिन्हित दीर्घ पंचांगp = get_reg(child, PT_SR) & ~TRACE_BITS;
	put_reg(child, PT_SR, पंचांगp | T0_BIT);
पूर्ण
#पूर्ण_अगर

व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	singlestep_disable(child);
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक i, ret = 0;
	पूर्णांक regno = addr >> 2; /* temporary hack. */
	अचिन्हित दीर्घ __user *datap = (अचिन्हित दीर्घ __user *) data;

	चयन (request) अणु
	/* पढ़ो the word at location addr in the USER area. */
	हाल PTRACE_PEEKUSR:
		अगर (addr & 3)
			जाओ out_eio;

		अगर (regno >= 0 && regno < 19) अणु
			पंचांगp = get_reg(child, regno);
		पूर्ण अन्यथा अगर (regno >= 21 && regno < 49) अणु
			पंचांगp = child->thपढ़ो.fp[regno - 21];
			/* Convert पूर्णांकernal fpu reg representation
			 * पूर्णांकo दीर्घ द्विगुन क्रमmat
			 */
			अगर (FPU_IS_EMU && (regno < 45) && !(regno % 3))
				पंचांगp = ((पंचांगp & 0xffff0000) << 15) |
				      ((पंचांगp & 0x0000ffff) << 16);
#अगर_अघोषित CONFIG_MMU
		पूर्ण अन्यथा अगर (regno == 49) अणु
			पंचांगp = child->mm->start_code;
		पूर्ण अन्यथा अगर (regno == 50) अणु
			पंचांगp = child->mm->start_data;
		पूर्ण अन्यथा अगर (regno == 51) अणु
			पंचांगp = child->mm->end_code;
#पूर्ण_अगर
		पूर्ण अन्यथा
			जाओ out_eio;
		ret = put_user(पंचांगp, datap);
		अवरोध;

	हाल PTRACE_POKEUSR:
	/* ग_लिखो the word at location addr in the USER area */
		अगर (addr & 3)
			जाओ out_eio;

		अगर (regno == PT_SR) अणु
			data &= SR_MASK;
			data |= get_reg(child, PT_SR) & ~SR_MASK;
		पूर्ण
		अगर (regno >= 0 && regno < 19) अणु
			अगर (put_reg(child, regno, data))
				जाओ out_eio;
		पूर्ण अन्यथा अगर (regno >= 21 && regno < 48) अणु
			/* Convert दीर्घ द्विगुन क्रमmat
			 * पूर्णांकo पूर्णांकernal fpu reg representation
			 */
			अगर (FPU_IS_EMU && (regno < 45) && !(regno % 3)) अणु
				data <<= 15;
				data = (data & 0xffff0000) |
				       ((data & 0x0000ffff) >> 1);
			पूर्ण
			child->thपढ़ो.fp[regno - 21] = data;
		पूर्ण अन्यथा
			जाओ out_eio;
		अवरोध;

	हाल PTRACE_GETREGS:	/* Get all gp regs from the child. */
		क्रम (i = 0; i < 19; i++) अणु
			पंचांगp = get_reg(child, i);
			ret = put_user(पंचांगp, datap);
			अगर (ret)
				अवरोध;
			datap++;
		पूर्ण
		अवरोध;

	हाल PTRACE_SETREGS:	/* Set all gp regs in the child. */
		क्रम (i = 0; i < 19; i++) अणु
			ret = get_user(पंचांगp, datap);
			अगर (ret)
				अवरोध;
			अगर (i == PT_SR) अणु
				पंचांगp &= SR_MASK;
				पंचांगp |= get_reg(child, PT_SR) & ~SR_MASK;
			पूर्ण
			put_reg(child, i, पंचांगp);
			datap++;
		पूर्ण
		अवरोध;

	हाल PTRACE_GETFPREGS:	/* Get the child FPU state. */
		अगर (copy_to_user(datap, &child->thपढ़ो.fp,
				 माप(काष्ठा user_m68kfp_काष्ठा)))
			ret = -EFAULT;
		अवरोध;

	हाल PTRACE_SETFPREGS:	/* Set the child FPU state. */
		अगर (copy_from_user(&child->thपढ़ो.fp, datap,
				   माप(काष्ठा user_m68kfp_काष्ठा)))
			ret = -EFAULT;
		अवरोध;

	हाल PTRACE_GET_THREAD_AREA:
		ret = put_user(task_thपढ़ो_info(child)->tp_value, datap);
		अवरोध;

	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
out_eio:
	वापस -EIO;
पूर्ण

यंत्रlinkage व्योम syscall_trace(व्योम)
अणु
	ptrace_notअगरy(SIGTRAP | ((current->ptrace & PT_TRACESYSGOOD)
				 ? 0x80 : 0));
	/*
	 * this isn't the same as continuing with a संकेत, but it will करो
	 * क्रम normal use.  strace only जारीs with a संकेत अगर the
	 * stopping संकेत is not SIGTRAP.  -brl
	 */
	अगर (current->निकास_code) अणु
		send_sig(current->निकास_code, current, 1);
		current->निकास_code = 0;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_COLDFIRE) || !defined(CONFIG_MMU)
यंत्रlinkage पूर्णांक syscall_trace_enter(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		ret = tracehook_report_syscall_entry(task_pt_regs(current));
	वापस ret;
पूर्ण

यंत्रlinkage व्योम syscall_trace_leave(व्योम)
अणु
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(task_pt_regs(current), 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_COLDFIRE */
