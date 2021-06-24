<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/ptrace.c
 *
 *  By Ross Biro 1/23/92
 * edited by Linus Torvalds
 * ARM modअगरications Copyright (C) 2000 Russell King
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/elf.h>
#समावेश <linux/smp.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/security.h>
#समावेश <linux/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/regset.h>
#समावेश <linux/audit.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/unistd.h>

#समावेश <यंत्र/traps.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

#घोषणा REG_PC	15
#घोषणा REG_PSR	16
/*
 * करोes not yet catch संकेतs sent when the child dies.
 * in निकास.c or in संकेत.c.
 */

#अगर 0
/*
 * Breakpoपूर्णांक SWI inकाष्ठाion: SWI &9F0001
 */
#घोषणा BREAKINST_ARM	0xef9f0001
#घोषणा BREAKINST_THUMB	0xdf00		/* fill this in later */
#अन्यथा
/*
 * New अवरोधpoपूर्णांकs - use an undefined inकाष्ठाion.  The ARM architecture
 * reference manual guarantees that the following inकाष्ठाion space
 * will produce an undefined inकाष्ठाion exception on all CPUs:
 *
 *  ARM:   xxxx 0111 1111 xxxx xxxx xxxx 1111 xxxx
 *  Thumb: 1101 1110 xxxx xxxx
 */
#घोषणा BREAKINST_ARM	0xe7f001f0
#घोषणा BREAKINST_THUMB	0xde01
#पूर्ण_अगर

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_NAME(r) \
	अणु.name = #r, .offset = दुरत्व(काष्ठा pt_regs, ARM_##r)पूर्ण
#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण

अटल स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
	REG_OFFSET_NAME(r0),
	REG_OFFSET_NAME(r1),
	REG_OFFSET_NAME(r2),
	REG_OFFSET_NAME(r3),
	REG_OFFSET_NAME(r4),
	REG_OFFSET_NAME(r5),
	REG_OFFSET_NAME(r6),
	REG_OFFSET_NAME(r7),
	REG_OFFSET_NAME(r8),
	REG_OFFSET_NAME(r9),
	REG_OFFSET_NAME(r10),
	REG_OFFSET_NAME(fp),
	REG_OFFSET_NAME(ip),
	REG_OFFSET_NAME(sp),
	REG_OFFSET_NAME(lr),
	REG_OFFSET_NAME(pc),
	REG_OFFSET_NAME(cpsr),
	REG_OFFSET_NAME(ORIG_r0),
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
 * regs_query_रेजिस्टर_name() - query रेजिस्टर name from its offset
 * @offset:	the offset of a रेजिस्टर in काष्ठा pt_regs.
 *
 * regs_query_रेजिस्टर_name() वापसs the name of a रेजिस्टर from its
 * offset in काष्ठा pt_regs. If the @offset is invalid, this वापसs शून्य;
 */
स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;
	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (roff->offset == offset)
			वापस roff->name;
	वापस शून्य;
पूर्ण

/**
 * regs_within_kernel_stack() - check the address in the stack
 * @regs:      pt_regs which contains kernel stack poपूर्णांकer.
 * @addr:      address which is checked.
 *
 * regs_within_kernel_stack() checks @addr is within the kernel stack page(s).
 * If @addr is within the kernel stack, it वापसs true. If not, वापसs false.
 */
bool regs_within_kernel_stack(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	वापस ((addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_poपूर्णांकer(regs) & ~(THREAD_SIZE - 1)));
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

/*
 * this routine will get a word off of the processes privileged stack.
 * the offset is how far from the base addr as stored in the THREAD.
 * this routine assumes that all the privileged stacks are in our
 * data space.
 */
अटल अंतरभूत दीर्घ get_user_reg(काष्ठा task_काष्ठा *task, पूर्णांक offset)
अणु
	वापस task_pt_regs(task)->uregs[offset];
पूर्ण

/*
 * this routine will put a word on the processes privileged stack.
 * the offset is how far from the base addr as stored in the THREAD.
 * this routine assumes that all the privileged stacks are in our
 * data space.
 */
अटल अंतरभूत पूर्णांक
put_user_reg(काष्ठा task_काष्ठा *task, पूर्णांक offset, दीर्घ data)
अणु
	काष्ठा pt_regs newregs, *regs = task_pt_regs(task);
	पूर्णांक ret = -EINVAL;

	newregs = *regs;
	newregs.uregs[offset] = data;

	अगर (valid_user_regs(&newregs)) अणु
		regs->uregs[offset] = data;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Called by kernel/ptrace.c when detaching..
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	/* Nothing to करो. */
पूर्ण

/*
 * Handle hitting a अवरोधpoपूर्णांक.
 */
व्योम ptrace_अवरोध(काष्ठा pt_regs *regs)
अणु
	क्रमce_sig_fault(SIGTRAP, TRAP_BRKPT,
			(व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs));
पूर्ण

अटल पूर्णांक अवरोध_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	ptrace_अवरोध(regs);
	वापस 0;
पूर्ण

अटल काष्ठा undef_hook arm_अवरोध_hook = अणु
	.instr_mask	= 0x0fffffff,
	.instr_val	= 0x07f001f0,
	.cpsr_mask	= PSR_T_BIT,
	.cpsr_val	= 0,
	.fn		= अवरोध_trap,
पूर्ण;

अटल काष्ठा undef_hook thumb_अवरोध_hook = अणु
	.instr_mask	= 0xffffffff,
	.instr_val	= 0x0000de01,
	.cpsr_mask	= PSR_T_BIT,
	.cpsr_val	= PSR_T_BIT,
	.fn		= अवरोध_trap,
पूर्ण;

अटल काष्ठा undef_hook thumb2_अवरोध_hook = अणु
	.instr_mask	= 0xffffffff,
	.instr_val	= 0xf7f0a000,
	.cpsr_mask	= PSR_T_BIT,
	.cpsr_val	= PSR_T_BIT,
	.fn		= अवरोध_trap,
पूर्ण;

अटल पूर्णांक __init ptrace_अवरोध_init(व्योम)
अणु
	रेजिस्टर_undef_hook(&arm_अवरोध_hook);
	रेजिस्टर_undef_hook(&thumb_अवरोध_hook);
	रेजिस्टर_undef_hook(&thumb2_अवरोध_hook);
	वापस 0;
पूर्ण

core_initcall(ptrace_अवरोध_init);

/*
 * Read the word at offset "off" पूर्णांकo the "struct user".  We
 * actually access the pt_regs stored on the kernel stack.
 */
अटल पूर्णांक ptrace_पढ़ो_user(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ off,
			    अचिन्हित दीर्घ __user *ret)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर (off & 3)
		वापस -EIO;

	पंचांगp = 0;
	अगर (off == PT_TEXT_ADDR)
		पंचांगp = tsk->mm->start_code;
	अन्यथा अगर (off == PT_DATA_ADDR)
		पंचांगp = tsk->mm->start_data;
	अन्यथा अगर (off == PT_TEXT_END_ADDR)
		पंचांगp = tsk->mm->end_code;
	अन्यथा अगर (off < माप(काष्ठा pt_regs))
		पंचांगp = get_user_reg(tsk, off >> 2);
	अन्यथा अगर (off >= माप(काष्ठा user))
		वापस -EIO;

	वापस put_user(पंचांगp, ret);
पूर्ण

/*
 * Write the word at offset "off" पूर्णांकo "struct user".  We
 * actually access the pt_regs stored on the kernel stack.
 */
अटल पूर्णांक ptrace_ग_लिखो_user(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ off,
			     अचिन्हित दीर्घ val)
अणु
	अगर (off & 3 || off >= माप(काष्ठा user))
		वापस -EIO;

	अगर (off >= माप(काष्ठा pt_regs))
		वापस 0;

	वापस put_user_reg(tsk, off >> 2, val);
पूर्ण

#अगर_घोषित CONFIG_IWMMXT

/*
 * Get the child iWMMXt state.
 */
अटल पूर्णांक ptrace_getwmmxregs(काष्ठा task_काष्ठा *tsk, व्योम __user *ufp)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = task_thपढ़ो_info(tsk);

	अगर (!test_ti_thपढ़ो_flag(thपढ़ो, TIF_USING_IWMMXT))
		वापस -ENODATA;
	iwmmxt_task_disable(thपढ़ो);  /* क्रमce it to ram */
	वापस copy_to_user(ufp, &thपढ़ो->fpstate.iwmmxt, IWMMXT_SIZE)
		? -EFAULT : 0;
पूर्ण

/*
 * Set the child iWMMXt state.
 */
अटल पूर्णांक ptrace_setwmmxregs(काष्ठा task_काष्ठा *tsk, व्योम __user *ufp)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = task_thपढ़ो_info(tsk);

	अगर (!test_ti_thपढ़ो_flag(thपढ़ो, TIF_USING_IWMMXT))
		वापस -EACCES;
	iwmmxt_task_release(thपढ़ो);  /* क्रमce a reload */
	वापस copy_from_user(&thपढ़ो->fpstate.iwmmxt, ufp, IWMMXT_SIZE)
		? -EFAULT : 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_CRUNCH
/*
 * Get the child Crunch state.
 */
अटल पूर्णांक ptrace_अ_लोrunchregs(काष्ठा task_काष्ठा *tsk, व्योम __user *ufp)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = task_thपढ़ो_info(tsk);

	crunch_task_disable(thपढ़ो);  /* क्रमce it to ram */
	वापस copy_to_user(ufp, &thपढ़ो->crunchstate, CRUNCH_SIZE)
		? -EFAULT : 0;
पूर्ण

/*
 * Set the child Crunch state.
 */
अटल पूर्णांक ptrace_setcrunchregs(काष्ठा task_काष्ठा *tsk, व्योम __user *ufp)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = task_thपढ़ो_info(tsk);

	crunch_task_release(thपढ़ो);  /* क्रमce a reload */
	वापस copy_from_user(&thपढ़ो->crunchstate, ufp, CRUNCH_SIZE)
		? -EFAULT : 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
/*
 * Convert a भव रेजिस्टर number पूर्णांकo an index क्रम a thपढ़ो_info
 * अवरोधpoपूर्णांक array. Breakpoपूर्णांकs are identअगरied using positive numbers
 * whilst watchpoपूर्णांकs are negative. The रेजिस्टरs are laid out as pairs
 * of (address, control), each pair mapping to a unique hw_अवरोधpoपूर्णांक काष्ठा.
 * Register 0 is reserved क्रम describing resource inक्रमmation.
 */
अटल पूर्णांक ptrace_hbp_num_to_idx(दीर्घ num)
अणु
	अगर (num < 0)
		num = (ARM_MAX_BRP << 1) - num;
	वापस (num - 1) >> 1;
पूर्ण

/*
 * Returns the भव रेजिस्टर number क्रम the address of the
 * अवरोधpoपूर्णांक at index idx.
 */
अटल दीर्घ ptrace_hbp_idx_to_num(पूर्णांक idx)
अणु
	दीर्घ mid = ARM_MAX_BRP << 1;
	दीर्घ num = (idx << 1) + 1;
	वापस num > mid ? mid - num : num;
पूर्ण

/*
 * Handle hitting a HW-अवरोधpoपूर्णांक.
 */
अटल व्योम ptrace_hbptriggered(काष्ठा perf_event *bp,
				     काष्ठा perf_sample_data *data,
				     काष्ठा pt_regs *regs)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *bkpt = counter_arch_bp(bp);
	दीर्घ num;
	पूर्णांक i;

	क्रम (i = 0; i < ARM_MAX_HBP_SLOTS; ++i)
		अगर (current->thपढ़ो.debug.hbp[i] == bp)
			अवरोध;

	num = (i == ARM_MAX_HBP_SLOTS) ? 0 : ptrace_hbp_idx_to_num(i);

	क्रमce_sig_ptrace_त्रुटि_सं_trap((पूर्णांक)num, (व्योम __user *)(bkpt->trigger));
पूर्ण

/*
 * Set ptrace अवरोधpoपूर्णांक poपूर्णांकers to zero क्रम this task.
 * This is required in order to prevent child processes from unरेजिस्टरing
 * अवरोधpoपूर्णांकs held by their parent.
 */
व्योम clear_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk)
अणु
	स_रखो(tsk->thपढ़ो.debug.hbp, 0, माप(tsk->thपढ़ो.debug.hbp));
पूर्ण

/*
 * Unरेजिस्टर अवरोधpoपूर्णांकs from this task and reset the poपूर्णांकers in
 * the thपढ़ो_काष्ठा.
 */
व्योम flush_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक i;
	काष्ठा thपढ़ो_काष्ठा *t = &tsk->thपढ़ो;

	क्रम (i = 0; i < ARM_MAX_HBP_SLOTS; i++) अणु
		अगर (t->debug.hbp[i]) अणु
			unरेजिस्टर_hw_अवरोधpoपूर्णांक(t->debug.hbp[i]);
			t->debug.hbp[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल u32 ptrace_get_hbp_resource_info(व्योम)
अणु
	u8 num_brps, num_wrps, debug_arch, wp_len;
	u32 reg = 0;

	num_brps	= hw_अवरोधpoपूर्णांक_slots(TYPE_INST);
	num_wrps	= hw_अवरोधpoपूर्णांक_slots(TYPE_DATA);
	debug_arch	= arch_get_debug_arch();
	wp_len		= arch_get_max_wp_len();

	reg		|= debug_arch;
	reg		<<= 8;
	reg		|= wp_len;
	reg		<<= 8;
	reg		|= num_wrps;
	reg		<<= 8;
	reg		|= num_brps;

	वापस reg;
पूर्ण

अटल काष्ठा perf_event *ptrace_hbp_create(काष्ठा task_काष्ठा *tsk, पूर्णांक type)
अणु
	काष्ठा perf_event_attr attr;

	ptrace_अवरोधpoपूर्णांक_init(&attr);

	/* Initialise fields to sane शेषs. */
	attr.bp_addr	= 0;
	attr.bp_len	= HW_BREAKPOINT_LEN_4;
	attr.bp_type	= type;
	attr.disabled	= 1;

	वापस रेजिस्टर_user_hw_अवरोधpoपूर्णांक(&attr, ptrace_hbptriggered, शून्य,
					   tsk);
पूर्ण

अटल पूर्णांक ptrace_gethbpregs(काष्ठा task_काष्ठा *tsk, दीर्घ num,
			     अचिन्हित दीर्घ  __user *data)
अणु
	u32 reg;
	पूर्णांक idx, ret = 0;
	काष्ठा perf_event *bp;
	काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl arch_ctrl;

	अगर (num == 0) अणु
		reg = ptrace_get_hbp_resource_info();
	पूर्ण अन्यथा अणु
		idx = ptrace_hbp_num_to_idx(num);
		अगर (idx < 0 || idx >= ARM_MAX_HBP_SLOTS) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		bp = tsk->thपढ़ो.debug.hbp[idx];
		अगर (!bp) अणु
			reg = 0;
			जाओ put;
		पूर्ण

		arch_ctrl = counter_arch_bp(bp)->ctrl;

		/*
		 * Fix up the len because we may have adjusted it
		 * to compensate क्रम an unaligned address.
		 */
		जबतक (!(arch_ctrl.len & 0x1))
			arch_ctrl.len >>= 1;

		अगर (num & 0x1)
			reg = bp->attr.bp_addr;
		अन्यथा
			reg = encode_ctrl_reg(arch_ctrl);
	पूर्ण

put:
	अगर (put_user(reg, data))
		ret = -EFAULT;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ptrace_sethbpregs(काष्ठा task_काष्ठा *tsk, दीर्घ num,
			     अचिन्हित दीर्घ __user *data)
अणु
	पूर्णांक idx, gen_len, gen_type, implied_type, ret = 0;
	u32 user_val;
	काष्ठा perf_event *bp;
	काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl;
	काष्ठा perf_event_attr attr;

	अगर (num == 0)
		जाओ out;
	अन्यथा अगर (num < 0)
		implied_type = HW_BREAKPOINT_RW;
	अन्यथा
		implied_type = HW_BREAKPOINT_X;

	idx = ptrace_hbp_num_to_idx(num);
	अगर (idx < 0 || idx >= ARM_MAX_HBP_SLOTS) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (get_user(user_val, data)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	bp = tsk->thपढ़ो.debug.hbp[idx];
	अगर (!bp) अणु
		bp = ptrace_hbp_create(tsk, implied_type);
		अगर (IS_ERR(bp)) अणु
			ret = PTR_ERR(bp);
			जाओ out;
		पूर्ण
		tsk->thपढ़ो.debug.hbp[idx] = bp;
	पूर्ण

	attr = bp->attr;

	अगर (num & 0x1) अणु
		/* Address */
		attr.bp_addr	= user_val;
	पूर्ण अन्यथा अणु
		/* Control */
		decode_ctrl_reg(user_val, &ctrl);
		ret = arch_bp_generic_fields(ctrl, &gen_len, &gen_type);
		अगर (ret)
			जाओ out;

		अगर ((gen_type & implied_type) != gen_type) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		attr.bp_len	= gen_len;
		attr.bp_type	= gen_type;
		attr.disabled	= !ctrl.enabled;
	पूर्ण

	ret = modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
out:
	वापस ret;
पूर्ण
#पूर्ण_अगर

/* regset get/set implementations */

अटल पूर्णांक gpr_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	वापस membuf_ग_लिखो(&to, task_pt_regs(target), माप(काष्ठा pt_regs));
पूर्ण

अटल पूर्णांक gpr_set(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा pt_regs newregs = *task_pt_regs(target);

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &newregs,
				 0, माप(newregs));
	अगर (ret)
		वापस ret;

	अगर (!valid_user_regs(&newregs))
		वापस -EINVAL;

	*task_pt_regs(target) = newregs;
	वापस 0;
पूर्ण

अटल पूर्णांक fpa_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	वापस membuf_ग_लिखो(&to, &task_thपढ़ो_info(target)->fpstate,
				 माप(काष्ठा user_fp));
पूर्ण

अटल पूर्णांक fpa_set(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = task_thपढ़ो_info(target);

	thपढ़ो->used_cp[1] = thपढ़ो->used_cp[2] = 1;

	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
		&thपढ़ो->fpstate,
		0, माप(काष्ठा user_fp));
पूर्ण

#अगर_घोषित CONFIG_VFP
/*
 * VFP रेजिस्टर get/set implementations.
 *
 * With respect to the kernel, काष्ठा user_fp is भागided पूर्णांकo three chunks:
 * 16 or 32 real VFP रेजिस्टरs (d0-d15 or d0-31)
 *	These are transferred to/from the real रेजिस्टरs in the task's
 *	vfp_hard_काष्ठा.  The number of रेजिस्टरs depends on the kernel
 *	configuration.
 *
 * 16 or 0 fake VFP रेजिस्टरs (d16-d31 or empty)
 *	i.e., the user_vfp काष्ठाure has space क्रम 32 रेजिस्टरs even अगर
 *	the kernel करोesn't have them all.
 *
 *	vfp_get() पढ़ोs this chunk as zero where applicable
 *	vfp_set() ignores this chunk
 *
 * 1 word क्रम the FPSCR
 */
अटल पूर्णांक vfp_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = task_thपढ़ो_info(target);
	काष्ठा vfp_hard_काष्ठा स्थिर *vfp = &thपढ़ो->vfpstate.hard;
	स्थिर माप_प्रकार user_fpscr_offset = दुरत्व(काष्ठा user_vfp, fpscr);

	vfp_sync_hwstate(thपढ़ो);

	membuf_ग_लिखो(&to, vfp->fpregs, माप(vfp->fpregs));
	membuf_zero(&to, user_fpscr_offset - माप(vfp->fpregs));
	वापस membuf_store(&to, vfp->fpscr);
पूर्ण

/*
 * For vfp_set() a पढ़ो-modअगरy-ग_लिखो is करोne on the VFP रेजिस्टरs,
 * in order to aव्योम writing back a half-modअगरied set of रेजिस्टरs on
 * failure.
 */
अटल पूर्णांक vfp_set(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			  स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा thपढ़ो_info *thपढ़ो = task_thपढ़ो_info(target);
	काष्ठा vfp_hard_काष्ठा new_vfp;
	स्थिर माप_प्रकार user_fpregs_offset = दुरत्व(काष्ठा user_vfp, fpregs);
	स्थिर माप_प्रकार user_fpscr_offset = दुरत्व(काष्ठा user_vfp, fpscr);

	vfp_sync_hwstate(thपढ़ो);
	new_vfp = thपढ़ो->vfpstate.hard;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &new_vfp.fpregs,
				  user_fpregs_offset,
				  user_fpregs_offset + माप(new_vfp.fpregs));
	अगर (ret)
		वापस ret;

	ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
				user_fpregs_offset + माप(new_vfp.fpregs),
				user_fpscr_offset);
	अगर (ret)
		वापस ret;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &new_vfp.fpscr,
				 user_fpscr_offset,
				 user_fpscr_offset + माप(new_vfp.fpscr));
	अगर (ret)
		वापस ret;

	thपढ़ो->vfpstate.hard = new_vfp;
	vfp_flush_hwstate(thपढ़ो);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_VFP */

क्रमागत arm_regset अणु
	REGSET_GPR,
	REGSET_FPR,
#अगर_घोषित CONFIG_VFP
	REGSET_VFP,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset arm_regsets[] = अणु
	[REGSET_GPR] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = ELF_NGREG,
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = gpr_get,
		.set = gpr_set
	पूर्ण,
	[REGSET_FPR] = अणु
		/*
		 * For the FPA regs in fpstate, the real fields are a mixture
		 * of sizes, so pretend that the रेजिस्टरs are word-sized:
		 */
		.core_note_type = NT_PRFPREG,
		.n = माप(काष्ठा user_fp) / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = fpa_get,
		.set = fpa_set
	पूर्ण,
#अगर_घोषित CONFIG_VFP
	[REGSET_VFP] = अणु
		/*
		 * Pretend that the VFP regs are word-sized, since the FPSCR is
		 * a single word dangling at the end of काष्ठा user_vfp:
		 */
		.core_note_type = NT_ARM_VFP,
		.n = ARM_VFPREGS_SIZE / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = vfp_get,
		.set = vfp_set
	पूर्ण,
#पूर्ण_अगर /* CONFIG_VFP */
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_arm_view = अणु
	.name = "arm", .e_machine = ELF_ARCH, .ei_osabi = ELF_OSABI,
	.regsets = arm_regsets, .n = ARRAY_SIZE(arm_regsets)
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &user_arm_view;
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ __user *datap = (अचिन्हित दीर्घ __user *) data;

	चयन (request) अणु
		हाल PTRACE_PEEKUSR:
			ret = ptrace_पढ़ो_user(child, addr, datap);
			अवरोध;

		हाल PTRACE_POKEUSR:
			ret = ptrace_ग_लिखो_user(child, addr, data);
			अवरोध;

		हाल PTRACE_GETREGS:
			ret = copy_regset_to_user(child,
						  &user_arm_view, REGSET_GPR,
						  0, माप(काष्ठा pt_regs),
						  datap);
			अवरोध;

		हाल PTRACE_SETREGS:
			ret = copy_regset_from_user(child,
						    &user_arm_view, REGSET_GPR,
						    0, माप(काष्ठा pt_regs),
						    datap);
			अवरोध;

		हाल PTRACE_GETFPREGS:
			ret = copy_regset_to_user(child,
						  &user_arm_view, REGSET_FPR,
						  0, माप(जोड़ fp_state),
						  datap);
			अवरोध;

		हाल PTRACE_SETFPREGS:
			ret = copy_regset_from_user(child,
						    &user_arm_view, REGSET_FPR,
						    0, माप(जोड़ fp_state),
						    datap);
			अवरोध;

#अगर_घोषित CONFIG_IWMMXT
		हाल PTRACE_GETWMMXREGS:
			ret = ptrace_getwmmxregs(child, datap);
			अवरोध;

		हाल PTRACE_SETWMMXREGS:
			ret = ptrace_setwmmxregs(child, datap);
			अवरोध;
#पूर्ण_अगर

		हाल PTRACE_GET_THREAD_AREA:
			ret = put_user(task_thपढ़ो_info(child)->tp_value[0],
				       datap);
			अवरोध;

		हाल PTRACE_SET_SYSCALL:
			task_thपढ़ो_info(child)->syscall = data;
			ret = 0;
			अवरोध;

#अगर_घोषित CONFIG_CRUNCH
		हाल PTRACE_GETCRUNCHREGS:
			ret = ptrace_अ_लोrunchregs(child, datap);
			अवरोध;

		हाल PTRACE_SETCRUNCHREGS:
			ret = ptrace_setcrunchregs(child, datap);
			अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_VFP
		हाल PTRACE_GETVFPREGS:
			ret = copy_regset_to_user(child,
						  &user_arm_view, REGSET_VFP,
						  0, ARM_VFPREGS_SIZE,
						  datap);
			अवरोध;

		हाल PTRACE_SETVFPREGS:
			ret = copy_regset_from_user(child,
						    &user_arm_view, REGSET_VFP,
						    0, ARM_VFPREGS_SIZE,
						    datap);
			अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
		हाल PTRACE_GETHBPREGS:
			ret = ptrace_gethbpregs(child, addr,
						(अचिन्हित दीर्घ __user *)data);
			अवरोध;
		हाल PTRACE_SETHBPREGS:
			ret = ptrace_sethbpregs(child, addr,
						(अचिन्हित दीर्घ __user *)data);
			अवरोध;
#पूर्ण_अगर

		शेष:
			ret = ptrace_request(child, request, addr, data);
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

क्रमागत ptrace_syscall_dir अणु
	PTRACE_SYSCALL_ENTER = 0,
	PTRACE_SYSCALL_EXIT,
पूर्ण;

अटल व्योम tracehook_report_syscall(काष्ठा pt_regs *regs,
				    क्रमागत ptrace_syscall_dir dir)
अणु
	अचिन्हित दीर्घ ip;

	/*
	 * IP is used to denote syscall entry/निकास:
	 * IP = 0 -> entry, =1 -> निकास
	 */
	ip = regs->ARM_ip;
	regs->ARM_ip = dir;

	अगर (dir == PTRACE_SYSCALL_EXIT)
		tracehook_report_syscall_निकास(regs, 0);
	अन्यथा अगर (tracehook_report_syscall_entry(regs))
		current_thपढ़ो_info()->syscall = -1;

	regs->ARM_ip = ip;
पूर्ण

यंत्रlinkage पूर्णांक syscall_trace_enter(काष्ठा pt_regs *regs, पूर्णांक scno)
अणु
	current_thपढ़ो_info()->syscall = scno;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall(regs, PTRACE_SYSCALL_ENTER);

	/* Do seccomp after ptrace; syscall may have changed. */
#अगर_घोषित CONFIG_HAVE_ARCH_SECCOMP_FILTER
	अगर (secure_computing() == -1)
		वापस -1;
#अन्यथा
	/* XXX: हटाओ this once OABI माला_लो fixed */
	secure_computing_strict(current_thपढ़ो_info()->syscall);
#पूर्ण_अगर

	/* Tracer or seccomp may have changed syscall. */
	scno = current_thपढ़ो_info()->syscall;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_enter(regs, scno);

	audit_syscall_entry(scno, regs->ARM_r0, regs->ARM_r1, regs->ARM_r2,
			    regs->ARM_r3);

	वापस scno;
पूर्ण

यंत्रlinkage व्योम syscall_trace_निकास(काष्ठा pt_regs *regs)
अणु
	/*
	 * Audit the syscall beक्रमe anything अन्यथा, as a debugger may
	 * come in and change the current रेजिस्टरs.
	 */
	audit_syscall_निकास(regs);

	/*
	 * Note that we haven't updated the ->syscall field क्रम the
	 * current thपढ़ो. This isn't a problem because it will have
	 * been set on syscall entry and there hasn't been an opportunity
	 * क्रम a PTRACE_SET_SYSCALL since then.
	 */
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_निकास(regs, regs_वापस_value(regs));

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall(regs, PTRACE_SYSCALL_EXIT);
पूर्ण
