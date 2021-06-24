<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/ptrace.c
 *
 * By Ross Biro 1/23/92
 * edited by Linus Torvalds
 * ARM modअगरications Copyright (C) 2000 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/audit.h>
#समावेश <linux/compat.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/nospec.h>
#समावेश <linux/smp.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/security.h>
#समावेश <linux/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/regset.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/elf.h>

#समावेश <यंत्र/compat.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/mte.h>
#समावेश <यंत्र/poपूर्णांकer_auth.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_NAME(r) अणु.name = #r, .offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण
#घोषणा GPR_OFFSET_NAME(r) \
	अणु.name = "x" #r, .offset = दुरत्व(काष्ठा pt_regs, regs[r])पूर्ण

अटल स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
	GPR_OFFSET_NAME(0),
	GPR_OFFSET_NAME(1),
	GPR_OFFSET_NAME(2),
	GPR_OFFSET_NAME(3),
	GPR_OFFSET_NAME(4),
	GPR_OFFSET_NAME(5),
	GPR_OFFSET_NAME(6),
	GPR_OFFSET_NAME(7),
	GPR_OFFSET_NAME(8),
	GPR_OFFSET_NAME(9),
	GPR_OFFSET_NAME(10),
	GPR_OFFSET_NAME(11),
	GPR_OFFSET_NAME(12),
	GPR_OFFSET_NAME(13),
	GPR_OFFSET_NAME(14),
	GPR_OFFSET_NAME(15),
	GPR_OFFSET_NAME(16),
	GPR_OFFSET_NAME(17),
	GPR_OFFSET_NAME(18),
	GPR_OFFSET_NAME(19),
	GPR_OFFSET_NAME(20),
	GPR_OFFSET_NAME(21),
	GPR_OFFSET_NAME(22),
	GPR_OFFSET_NAME(23),
	GPR_OFFSET_NAME(24),
	GPR_OFFSET_NAME(25),
	GPR_OFFSET_NAME(26),
	GPR_OFFSET_NAME(27),
	GPR_OFFSET_NAME(28),
	GPR_OFFSET_NAME(29),
	GPR_OFFSET_NAME(30),
	अणु.name = "lr", .offset = दुरत्व(काष्ठा pt_regs, regs[30])पूर्ण,
	REG_OFFSET_NAME(sp),
	REG_OFFSET_NAME(pc),
	REG_OFFSET_NAME(pstate),
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
	वापस ((addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_poपूर्णांकer(regs) & ~(THREAD_SIZE - 1))) ||
		on_irq_stack(addr, शून्य);
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
 * TODO: करोes not yet catch संकेतs sent when the child dies.
 * in निकास.c or in संकेत.c.
 */

/*
 * Called by kernel/ptrace.c when detaching..
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	/*
	 * This would be better off in core code, but PTRACE_DETACH has
	 * grown its fair share of arch-specअगरic worts and changing it
	 * is likely to cause regressions on obscure architectures.
	 */
	user_disable_single_step(child);
पूर्ण

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
/*
 * Handle hitting a HW-अवरोधpoपूर्णांक.
 */
अटल व्योम ptrace_hbptriggered(काष्ठा perf_event *bp,
				काष्ठा perf_sample_data *data,
				काष्ठा pt_regs *regs)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *bkpt = counter_arch_bp(bp);
	स्थिर अक्षर *desc = "Hardware breakpoint trap (ptrace)";

#अगर_घोषित CONFIG_COMPAT
	अगर (is_compat_task()) अणु
		पूर्णांक si_त्रुटि_सं = 0;
		पूर्णांक i;

		क्रम (i = 0; i < ARM_MAX_BRP; ++i) अणु
			अगर (current->thपढ़ो.debug.hbp_अवरोध[i] == bp) अणु
				si_त्रुटि_सं = (i << 1) + 1;
				अवरोध;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < ARM_MAX_WRP; ++i) अणु
			अगर (current->thपढ़ो.debug.hbp_watch[i] == bp) अणु
				si_त्रुटि_सं = -((i << 1) + 1);
				अवरोध;
			पूर्ण
		पूर्ण
		arm64_क्रमce_sig_ptrace_त्रुटि_सं_trap(si_त्रुटि_सं, bkpt->trigger,
						  desc);
		वापस;
	पूर्ण
#पूर्ण_अगर
	arm64_क्रमce_sig_fault(SIGTRAP, TRAP_HWBKPT, bkpt->trigger, desc);
पूर्ण

/*
 * Unरेजिस्टर अवरोधpoपूर्णांकs from this task and reset the poपूर्णांकers in
 * the thपढ़ो_काष्ठा.
 */
व्योम flush_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक i;
	काष्ठा thपढ़ो_काष्ठा *t = &tsk->thपढ़ो;

	क्रम (i = 0; i < ARM_MAX_BRP; i++) अणु
		अगर (t->debug.hbp_अवरोध[i]) अणु
			unरेजिस्टर_hw_अवरोधpoपूर्णांक(t->debug.hbp_अवरोध[i]);
			t->debug.hbp_अवरोध[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARM_MAX_WRP; i++) अणु
		अगर (t->debug.hbp_watch[i]) अणु
			unरेजिस्टर_hw_अवरोधpoपूर्णांक(t->debug.hbp_watch[i]);
			t->debug.hbp_watch[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ptrace_hw_copy_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	स_रखो(&tsk->thपढ़ो.debug, 0, माप(काष्ठा debug_info));
पूर्ण

अटल काष्ठा perf_event *ptrace_hbp_get_event(अचिन्हित पूर्णांक note_type,
					       काष्ठा task_काष्ठा *tsk,
					       अचिन्हित दीर्घ idx)
अणु
	काष्ठा perf_event *bp = ERR_PTR(-EINVAL);

	चयन (note_type) अणु
	हाल NT_ARM_HW_BREAK:
		अगर (idx >= ARM_MAX_BRP)
			जाओ out;
		idx = array_index_nospec(idx, ARM_MAX_BRP);
		bp = tsk->thपढ़ो.debug.hbp_अवरोध[idx];
		अवरोध;
	हाल NT_ARM_HW_WATCH:
		अगर (idx >= ARM_MAX_WRP)
			जाओ out;
		idx = array_index_nospec(idx, ARM_MAX_WRP);
		bp = tsk->thपढ़ो.debug.hbp_watch[idx];
		अवरोध;
	पूर्ण

out:
	वापस bp;
पूर्ण

अटल पूर्णांक ptrace_hbp_set_event(अचिन्हित पूर्णांक note_type,
				काष्ठा task_काष्ठा *tsk,
				अचिन्हित दीर्घ idx,
				काष्ठा perf_event *bp)
अणु
	पूर्णांक err = -EINVAL;

	चयन (note_type) अणु
	हाल NT_ARM_HW_BREAK:
		अगर (idx >= ARM_MAX_BRP)
			जाओ out;
		idx = array_index_nospec(idx, ARM_MAX_BRP);
		tsk->thपढ़ो.debug.hbp_अवरोध[idx] = bp;
		err = 0;
		अवरोध;
	हाल NT_ARM_HW_WATCH:
		अगर (idx >= ARM_MAX_WRP)
			जाओ out;
		idx = array_index_nospec(idx, ARM_MAX_WRP);
		tsk->thपढ़ो.debug.hbp_watch[idx] = bp;
		err = 0;
		अवरोध;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल काष्ठा perf_event *ptrace_hbp_create(अचिन्हित पूर्णांक note_type,
					    काष्ठा task_काष्ठा *tsk,
					    अचिन्हित दीर्घ idx)
अणु
	काष्ठा perf_event *bp;
	काष्ठा perf_event_attr attr;
	पूर्णांक err, type;

	चयन (note_type) अणु
	हाल NT_ARM_HW_BREAK:
		type = HW_BREAKPOINT_X;
		अवरोध;
	हाल NT_ARM_HW_WATCH:
		type = HW_BREAKPOINT_RW;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ptrace_अवरोधpoपूर्णांक_init(&attr);

	/*
	 * Initialise fields to sane शेषs
	 * (i.e. values that will pass validation).
	 */
	attr.bp_addr	= 0;
	attr.bp_len	= HW_BREAKPOINT_LEN_4;
	attr.bp_type	= type;
	attr.disabled	= 1;

	bp = रेजिस्टर_user_hw_अवरोधpoपूर्णांक(&attr, ptrace_hbptriggered, शून्य, tsk);
	अगर (IS_ERR(bp))
		वापस bp;

	err = ptrace_hbp_set_event(note_type, tsk, idx, bp);
	अगर (err)
		वापस ERR_PTR(err);

	वापस bp;
पूर्ण

अटल पूर्णांक ptrace_hbp_fill_attr_ctrl(अचिन्हित पूर्णांक note_type,
				     काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl,
				     काष्ठा perf_event_attr *attr)
अणु
	पूर्णांक err, len, type, offset, disabled = !ctrl.enabled;

	attr->disabled = disabled;
	अगर (disabled)
		वापस 0;

	err = arch_bp_generic_fields(ctrl, &len, &type, &offset);
	अगर (err)
		वापस err;

	चयन (note_type) अणु
	हाल NT_ARM_HW_BREAK:
		अगर ((type & HW_BREAKPOINT_X) != type)
			वापस -EINVAL;
		अवरोध;
	हाल NT_ARM_HW_WATCH:
		अगर ((type & HW_BREAKPOINT_RW) != type)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	attr->bp_len	= len;
	attr->bp_type	= type;
	attr->bp_addr	+= offset;

	वापस 0;
पूर्ण

अटल पूर्णांक ptrace_hbp_get_resource_info(अचिन्हित पूर्णांक note_type, u32 *info)
अणु
	u8 num;
	u32 reg = 0;

	चयन (note_type) अणु
	हाल NT_ARM_HW_BREAK:
		num = hw_अवरोधpoपूर्णांक_slots(TYPE_INST);
		अवरोध;
	हाल NT_ARM_HW_WATCH:
		num = hw_अवरोधpoपूर्णांक_slots(TYPE_DATA);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg |= debug_monitors_arch();
	reg <<= 8;
	reg |= num;

	*info = reg;
	वापस 0;
पूर्ण

अटल पूर्णांक ptrace_hbp_get_ctrl(अचिन्हित पूर्णांक note_type,
			       काष्ठा task_काष्ठा *tsk,
			       अचिन्हित दीर्घ idx,
			       u32 *ctrl)
अणु
	काष्ठा perf_event *bp = ptrace_hbp_get_event(note_type, tsk, idx);

	अगर (IS_ERR(bp))
		वापस PTR_ERR(bp);

	*ctrl = bp ? encode_ctrl_reg(counter_arch_bp(bp)->ctrl) : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ptrace_hbp_get_addr(अचिन्हित पूर्णांक note_type,
			       काष्ठा task_काष्ठा *tsk,
			       अचिन्हित दीर्घ idx,
			       u64 *addr)
अणु
	काष्ठा perf_event *bp = ptrace_hbp_get_event(note_type, tsk, idx);

	अगर (IS_ERR(bp))
		वापस PTR_ERR(bp);

	*addr = bp ? counter_arch_bp(bp)->address : 0;
	वापस 0;
पूर्ण

अटल काष्ठा perf_event *ptrace_hbp_get_initialised_bp(अचिन्हित पूर्णांक note_type,
							काष्ठा task_काष्ठा *tsk,
							अचिन्हित दीर्घ idx)
अणु
	काष्ठा perf_event *bp = ptrace_hbp_get_event(note_type, tsk, idx);

	अगर (!bp)
		bp = ptrace_hbp_create(note_type, tsk, idx);

	वापस bp;
पूर्ण

अटल पूर्णांक ptrace_hbp_set_ctrl(अचिन्हित पूर्णांक note_type,
			       काष्ठा task_काष्ठा *tsk,
			       अचिन्हित दीर्घ idx,
			       u32 uctrl)
अणु
	पूर्णांक err;
	काष्ठा perf_event *bp;
	काष्ठा perf_event_attr attr;
	काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl;

	bp = ptrace_hbp_get_initialised_bp(note_type, tsk, idx);
	अगर (IS_ERR(bp)) अणु
		err = PTR_ERR(bp);
		वापस err;
	पूर्ण

	attr = bp->attr;
	decode_ctrl_reg(uctrl, &ctrl);
	err = ptrace_hbp_fill_attr_ctrl(note_type, ctrl, &attr);
	अगर (err)
		वापस err;

	वापस modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
पूर्ण

अटल पूर्णांक ptrace_hbp_set_addr(अचिन्हित पूर्णांक note_type,
			       काष्ठा task_काष्ठा *tsk,
			       अचिन्हित दीर्घ idx,
			       u64 addr)
अणु
	पूर्णांक err;
	काष्ठा perf_event *bp;
	काष्ठा perf_event_attr attr;

	bp = ptrace_hbp_get_initialised_bp(note_type, tsk, idx);
	अगर (IS_ERR(bp)) अणु
		err = PTR_ERR(bp);
		वापस err;
	पूर्ण

	attr = bp->attr;
	attr.bp_addr = addr;
	err = modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
	वापस err;
पूर्ण

#घोषणा PTRACE_HBP_ADDR_SZ	माप(u64)
#घोषणा PTRACE_HBP_CTRL_SZ	माप(u32)
#घोषणा PTRACE_HBP_PAD_SZ	माप(u32)

अटल पूर्णांक hw_अवरोध_get(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			काष्ठा membuf to)
अणु
	अचिन्हित पूर्णांक note_type = regset->core_note_type;
	पूर्णांक ret, idx = 0;
	u32 info, ctrl;
	u64 addr;

	/* Resource info */
	ret = ptrace_hbp_get_resource_info(note_type, &info);
	अगर (ret)
		वापस ret;

	membuf_ग_लिखो(&to, &info, माप(info));
	membuf_zero(&to, माप(u32));
	/* (address, ctrl) रेजिस्टरs */
	जबतक (to.left) अणु
		ret = ptrace_hbp_get_addr(note_type, target, idx, &addr);
		अगर (ret)
			वापस ret;
		ret = ptrace_hbp_get_ctrl(note_type, target, idx, &ctrl);
		अगर (ret)
			वापस ret;
		membuf_store(&to, addr);
		membuf_store(&to, ctrl);
		membuf_zero(&to, माप(u32));
		idx++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hw_अवरोध_set(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित पूर्णांक note_type = regset->core_note_type;
	पूर्णांक ret, idx = 0, offset, limit;
	u32 ctrl;
	u64 addr;

	/* Resource info and pad */
	offset = दुरत्व(काष्ठा user_hwdebug_state, dbg_regs);
	ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf, 0, offset);
	अगर (ret)
		वापस ret;

	/* (address, ctrl) रेजिस्टरs */
	limit = regset->n * regset->size;
	जबतक (count && offset < limit) अणु
		अगर (count < PTRACE_HBP_ADDR_SZ)
			वापस -EINVAL;
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &addr,
					 offset, offset + PTRACE_HBP_ADDR_SZ);
		अगर (ret)
			वापस ret;
		ret = ptrace_hbp_set_addr(note_type, target, idx, addr);
		अगर (ret)
			वापस ret;
		offset += PTRACE_HBP_ADDR_SZ;

		अगर (!count)
			अवरोध;
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &ctrl,
					 offset, offset + PTRACE_HBP_CTRL_SZ);
		अगर (ret)
			वापस ret;
		ret = ptrace_hbp_set_ctrl(note_type, target, idx, ctrl);
		अगर (ret)
			वापस ret;
		offset += PTRACE_HBP_CTRL_SZ;

		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						offset,
						offset + PTRACE_HBP_PAD_SZ);
		अगर (ret)
			वापस ret;
		offset += PTRACE_HBP_PAD_SZ;
		idx++;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_HAVE_HW_BREAKPOINT */

अटल पूर्णांक gpr_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	काष्ठा user_pt_regs *uregs = &task_pt_regs(target)->user_regs;
	वापस membuf_ग_लिखो(&to, uregs, माप(*uregs));
पूर्ण

अटल पूर्णांक gpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा user_pt_regs newregs = task_pt_regs(target)->user_regs;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &newregs, 0, -1);
	अगर (ret)
		वापस ret;

	अगर (!valid_user_regs(&newregs, target))
		वापस -EINVAL;

	task_pt_regs(target)->user_regs = newregs;
	वापस 0;
पूर्ण

अटल पूर्णांक fpr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!प्रणाली_supports_fpsimd())
		वापस -ENODEV;
	वापस regset->n;
पूर्ण

/*
 * TODO: update fp accessors क्रम lazy context चयनing (sync/flush hwstate)
 */
अटल पूर्णांक __fpr_get(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to)
अणु
	काष्ठा user_fpsimd_state *uregs;

	sve_sync_to_fpsimd(target);

	uregs = &target->thपढ़ो.uw.fpsimd_state;

	वापस membuf_ग_लिखो(&to, uregs, माप(*uregs));
पूर्ण

अटल पूर्णांक fpr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	अगर (!प्रणाली_supports_fpsimd())
		वापस -EINVAL;

	अगर (target == current)
		fpsimd_preserve_current_state();

	वापस __fpr_get(target, regset, to);
पूर्ण

अटल पूर्णांक __fpr_set(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf,
		     अचिन्हित पूर्णांक start_pos)
अणु
	पूर्णांक ret;
	काष्ठा user_fpsimd_state newstate;

	/*
	 * Ensure target->thपढ़ो.uw.fpsimd_state is up to date, so that a
	 * लघु copyin can't resurrect stale data.
	 */
	sve_sync_to_fpsimd(target);

	newstate = target->thपढ़ो.uw.fpsimd_state;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &newstate,
				 start_pos, start_pos + माप(newstate));
	अगर (ret)
		वापस ret;

	target->thपढ़ो.uw.fpsimd_state = newstate;

	वापस ret;
पूर्ण

अटल पूर्णांक fpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;

	अगर (!प्रणाली_supports_fpsimd())
		वापस -EINVAL;

	ret = __fpr_set(target, regset, pos, count, kbuf, ubuf, 0);
	अगर (ret)
		वापस ret;

	sve_sync_from_fpsimd_zeropad(target);
	fpsimd_flush_task_state(target);

	वापस ret;
पूर्ण

अटल पूर्णांक tls_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	अगर (target == current)
		tls_preserve_current_state();

	वापस membuf_store(&to, target->thपढ़ो.uw.tp_value);
पूर्ण

अटल पूर्णांक tls_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ tls = target->thपढ़ो.uw.tp_value;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &tls, 0, -1);
	अगर (ret)
		वापस ret;

	target->thपढ़ो.uw.tp_value = tls;
	वापस ret;
पूर्ण

अटल पूर्णांक प्रणाली_call_get(काष्ठा task_काष्ठा *target,
			   स्थिर काष्ठा user_regset *regset,
			   काष्ठा membuf to)
अणु
	वापस membuf_store(&to, task_pt_regs(target)->syscallno);
पूर्ण

अटल पूर्णांक प्रणाली_call_set(काष्ठा task_काष्ठा *target,
			   स्थिर काष्ठा user_regset *regset,
			   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक syscallno = task_pt_regs(target)->syscallno;
	पूर्णांक ret;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &syscallno, 0, -1);
	अगर (ret)
		वापस ret;

	task_pt_regs(target)->syscallno = syscallno;
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ARM64_SVE

अटल व्योम sve_init_header_from_task(काष्ठा user_sve_header *header,
				      काष्ठा task_काष्ठा *target)
अणु
	अचिन्हित पूर्णांक vq;

	स_रखो(header, 0, माप(*header));

	header->flags = test_tsk_thपढ़ो_flag(target, TIF_SVE) ?
		SVE_PT_REGS_SVE : SVE_PT_REGS_FPSIMD;
	अगर (test_tsk_thपढ़ो_flag(target, TIF_SVE_VL_INHERIT))
		header->flags |= SVE_PT_VL_INHERIT;

	header->vl = target->thपढ़ो.sve_vl;
	vq = sve_vq_from_vl(header->vl);

	header->max_vl = sve_max_vl;
	header->size = SVE_PT_SIZE(vq, header->flags);
	header->max_size = SVE_PT_SIZE(sve_vq_from_vl(header->max_vl),
				      SVE_PT_REGS_SVE);
पूर्ण

अटल अचिन्हित पूर्णांक sve_size_from_header(काष्ठा user_sve_header स्थिर *header)
अणु
	वापस ALIGN(header->size, SVE_VQ_BYTES);
पूर्ण

अटल पूर्णांक sve_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	काष्ठा user_sve_header header;
	अचिन्हित पूर्णांक vq;
	अचिन्हित दीर्घ start, end;

	अगर (!प्रणाली_supports_sve())
		वापस -EINVAL;

	/* Header */
	sve_init_header_from_task(&header, target);
	vq = sve_vq_from_vl(header.vl);

	membuf_ग_लिखो(&to, &header, माप(header));

	अगर (target == current)
		fpsimd_preserve_current_state();

	/* Registers: FPSIMD-only हाल */

	BUILD_BUG_ON(SVE_PT_FPSIMD_OFFSET != माप(header));
	अगर ((header.flags & SVE_PT_REGS_MASK) == SVE_PT_REGS_FPSIMD)
		वापस __fpr_get(target, regset, to);

	/* Otherwise: full SVE हाल */

	BUILD_BUG_ON(SVE_PT_SVE_OFFSET != माप(header));
	start = SVE_PT_SVE_OFFSET;
	end = SVE_PT_SVE_FFR_OFFSET(vq) + SVE_PT_SVE_FFR_SIZE(vq);
	membuf_ग_लिखो(&to, target->thपढ़ो.sve_state, end - start);

	start = end;
	end = SVE_PT_SVE_FPSR_OFFSET(vq);
	membuf_zero(&to, end - start);

	/*
	 * Copy fpsr, and fpcr which must follow contiguously in
	 * काष्ठा fpsimd_state:
	 */
	start = end;
	end = SVE_PT_SVE_FPCR_OFFSET(vq) + SVE_PT_SVE_FPCR_SIZE;
	membuf_ग_लिखो(&to, &target->thपढ़ो.uw.fpsimd_state.fpsr, end - start);

	start = end;
	end = sve_size_from_header(&header);
	वापस membuf_zero(&to, end - start);
पूर्ण

अटल पूर्णांक sve_set(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा user_sve_header header;
	अचिन्हित पूर्णांक vq;
	अचिन्हित दीर्घ start, end;

	अगर (!प्रणाली_supports_sve())
		वापस -EINVAL;

	/* Header */
	अगर (count < माप(header))
		वापस -EINVAL;
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &header,
				 0, माप(header));
	अगर (ret)
		जाओ out;

	/*
	 * Apart from SVE_PT_REGS_MASK, all SVE_PT_* flags are consumed by
	 * sve_set_vector_length(), which will also validate them क्रम us:
	 */
	ret = sve_set_vector_length(target, header.vl,
		((अचिन्हित दीर्घ)header.flags & ~SVE_PT_REGS_MASK) << 16);
	अगर (ret)
		जाओ out;

	/* Actual VL set may be less than the user asked क्रम: */
	vq = sve_vq_from_vl(target->thपढ़ो.sve_vl);

	/* Registers: FPSIMD-only हाल */

	BUILD_BUG_ON(SVE_PT_FPSIMD_OFFSET != माप(header));
	अगर ((header.flags & SVE_PT_REGS_MASK) == SVE_PT_REGS_FPSIMD) अणु
		ret = __fpr_set(target, regset, pos, count, kbuf, ubuf,
				SVE_PT_FPSIMD_OFFSET);
		clear_tsk_thपढ़ो_flag(target, TIF_SVE);
		जाओ out;
	पूर्ण

	/* Otherwise: full SVE हाल */

	/*
	 * If setting a dअगरferent VL from the requested VL and there is
	 * रेजिस्टर data, the data layout will be wrong: करोn't even
	 * try to set the रेजिस्टरs in this हाल.
	 */
	अगर (count && vq != sve_vq_from_vl(header.vl)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	sve_alloc(target);

	/*
	 * Ensure target->thपढ़ो.sve_state is up to date with target's
	 * FPSIMD regs, so that a लघु copyin leaves trailing रेजिस्टरs
	 * unmodअगरied.
	 */
	fpsimd_sync_to_sve(target);
	set_tsk_thपढ़ो_flag(target, TIF_SVE);

	BUILD_BUG_ON(SVE_PT_SVE_OFFSET != माप(header));
	start = SVE_PT_SVE_OFFSET;
	end = SVE_PT_SVE_FFR_OFFSET(vq) + SVE_PT_SVE_FFR_SIZE(vq);
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 target->thपढ़ो.sve_state,
				 start, end);
	अगर (ret)
		जाओ out;

	start = end;
	end = SVE_PT_SVE_FPSR_OFFSET(vq);
	ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					start, end);
	अगर (ret)
		जाओ out;

	/*
	 * Copy fpsr, and fpcr which must follow contiguously in
	 * काष्ठा fpsimd_state:
	 */
	start = end;
	end = SVE_PT_SVE_FPCR_OFFSET(vq) + SVE_PT_SVE_FPCR_SIZE;
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &target->thपढ़ो.uw.fpsimd_state.fpsr,
				 start, end);

out:
	fpsimd_flush_task_state(target);
	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_ARM64_SVE */

#अगर_घोषित CONFIG_ARM64_PTR_AUTH
अटल पूर्णांक pac_mask_get(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			काष्ठा membuf to)
अणु
	/*
	 * The PAC bits can dअगरfer across data and inकाष्ठाion poपूर्णांकers
	 * depending on TCR_EL1.TBID*, which we may make use of in future, so
	 * we expose separate masks.
	 */
	अचिन्हित दीर्घ mask = ptrauth_user_pac_mask();
	काष्ठा user_pac_mask uregs = अणु
		.data_mask = mask,
		.insn_mask = mask,
	पूर्ण;

	अगर (!प्रणाली_supports_address_auth())
		वापस -EINVAL;

	वापस membuf_ग_लिखो(&to, &uregs, माप(uregs));
पूर्ण

अटल पूर्णांक pac_enabled_keys_get(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				काष्ठा membuf to)
अणु
	दीर्घ enabled_keys = ptrauth_get_enabled_keys(target);

	अगर (IS_ERR_VALUE(enabled_keys))
		वापस enabled_keys;

	वापस membuf_ग_लिखो(&to, &enabled_keys, माप(enabled_keys));
पूर्ण

अटल पूर्णांक pac_enabled_keys_set(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
				स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	दीर्घ enabled_keys = ptrauth_get_enabled_keys(target);

	अगर (IS_ERR_VALUE(enabled_keys))
		वापस enabled_keys;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &enabled_keys, 0,
				 माप(दीर्घ));
	अगर (ret)
		वापस ret;

	वापस ptrauth_set_enabled_keys(target, PR_PAC_ENABLED_KEYS_MASK,
					enabled_keys);
पूर्ण

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
अटल __uपूर्णांक128_t pac_key_to_user(स्थिर काष्ठा ptrauth_key *key)
अणु
	वापस (__uपूर्णांक128_t)key->hi << 64 | key->lo;
पूर्ण

अटल काष्ठा ptrauth_key pac_key_from_user(__uपूर्णांक128_t ukey)
अणु
	काष्ठा ptrauth_key key = अणु
		.lo = (अचिन्हित दीर्घ)ukey,
		.hi = (अचिन्हित दीर्घ)(ukey >> 64),
	पूर्ण;

	वापस key;
पूर्ण

अटल व्योम pac_address_keys_to_user(काष्ठा user_pac_address_keys *ukeys,
				     स्थिर काष्ठा ptrauth_keys_user *keys)
अणु
	ukeys->apiakey = pac_key_to_user(&keys->apia);
	ukeys->apibkey = pac_key_to_user(&keys->apib);
	ukeys->apdakey = pac_key_to_user(&keys->apda);
	ukeys->apdbkey = pac_key_to_user(&keys->apdb);
पूर्ण

अटल व्योम pac_address_keys_from_user(काष्ठा ptrauth_keys_user *keys,
				       स्थिर काष्ठा user_pac_address_keys *ukeys)
अणु
	keys->apia = pac_key_from_user(ukeys->apiakey);
	keys->apib = pac_key_from_user(ukeys->apibkey);
	keys->apda = pac_key_from_user(ukeys->apdakey);
	keys->apdb = pac_key_from_user(ukeys->apdbkey);
पूर्ण

अटल पूर्णांक pac_address_keys_get(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				काष्ठा membuf to)
अणु
	काष्ठा ptrauth_keys_user *keys = &target->thपढ़ो.keys_user;
	काष्ठा user_pac_address_keys user_keys;

	अगर (!प्रणाली_supports_address_auth())
		वापस -EINVAL;

	pac_address_keys_to_user(&user_keys, keys);

	वापस membuf_ग_लिखो(&to, &user_keys, माप(user_keys));
पूर्ण

अटल पूर्णांक pac_address_keys_set(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
				स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा ptrauth_keys_user *keys = &target->thपढ़ो.keys_user;
	काष्ठा user_pac_address_keys user_keys;
	पूर्णांक ret;

	अगर (!प्रणाली_supports_address_auth())
		वापस -EINVAL;

	pac_address_keys_to_user(&user_keys, keys);
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &user_keys, 0, -1);
	अगर (ret)
		वापस ret;
	pac_address_keys_from_user(keys, &user_keys);

	वापस 0;
पूर्ण

अटल व्योम pac_generic_keys_to_user(काष्ठा user_pac_generic_keys *ukeys,
				     स्थिर काष्ठा ptrauth_keys_user *keys)
अणु
	ukeys->apgakey = pac_key_to_user(&keys->apga);
पूर्ण

अटल व्योम pac_generic_keys_from_user(काष्ठा ptrauth_keys_user *keys,
				       स्थिर काष्ठा user_pac_generic_keys *ukeys)
अणु
	keys->apga = pac_key_from_user(ukeys->apgakey);
पूर्ण

अटल पूर्णांक pac_generic_keys_get(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				काष्ठा membuf to)
अणु
	काष्ठा ptrauth_keys_user *keys = &target->thपढ़ो.keys_user;
	काष्ठा user_pac_generic_keys user_keys;

	अगर (!प्रणाली_supports_generic_auth())
		वापस -EINVAL;

	pac_generic_keys_to_user(&user_keys, keys);

	वापस membuf_ग_लिखो(&to, &user_keys, माप(user_keys));
पूर्ण

अटल पूर्णांक pac_generic_keys_set(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
				स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा ptrauth_keys_user *keys = &target->thपढ़ो.keys_user;
	काष्ठा user_pac_generic_keys user_keys;
	पूर्णांक ret;

	अगर (!प्रणाली_supports_generic_auth())
		वापस -EINVAL;

	pac_generic_keys_to_user(&user_keys, keys);
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &user_keys, 0, -1);
	अगर (ret)
		वापस ret;
	pac_generic_keys_from_user(keys, &user_keys);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CHECKPOINT_RESTORE */
#पूर्ण_अगर /* CONFIG_ARM64_PTR_AUTH */

#अगर_घोषित CONFIG_ARM64_TAGGED_ADDR_ABI
अटल पूर्णांक tagged_addr_ctrl_get(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				काष्ठा membuf to)
अणु
	दीर्घ ctrl = get_tagged_addr_ctrl(target);

	अगर (IS_ERR_VALUE(ctrl))
		वापस ctrl;

	वापस membuf_ग_लिखो(&to, &ctrl, माप(ctrl));
पूर्ण

अटल पूर्णांक tagged_addr_ctrl_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा
				user_regset *regset, अचिन्हित पूर्णांक pos,
				अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf, स्थिर
				व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	दीर्घ ctrl;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &ctrl, 0, -1);
	अगर (ret)
		वापस ret;

	वापस set_tagged_addr_ctrl(target, ctrl);
पूर्ण
#पूर्ण_अगर

क्रमागत aarch64_regset अणु
	REGSET_GPR,
	REGSET_FPR,
	REGSET_TLS,
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	REGSET_HW_BREAK,
	REGSET_HW_WATCH,
#पूर्ण_अगर
	REGSET_SYSTEM_CALL,
#अगर_घोषित CONFIG_ARM64_SVE
	REGSET_SVE,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_PTR_AUTH
	REGSET_PAC_MASK,
	REGSET_PAC_ENABLED_KEYS,
#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	REGSET_PACA_KEYS,
	REGSET_PACG_KEYS,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_TAGGED_ADDR_ABI
	REGSET_TAGGED_ADDR_CTRL,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset aarch64_regsets[] = अणु
	[REGSET_GPR] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = माप(काष्ठा user_pt_regs) / माप(u64),
		.size = माप(u64),
		.align = माप(u64),
		.regset_get = gpr_get,
		.set = gpr_set
	पूर्ण,
	[REGSET_FPR] = अणु
		.core_note_type = NT_PRFPREG,
		.n = माप(काष्ठा user_fpsimd_state) / माप(u32),
		/*
		 * We pretend we have 32-bit रेजिस्टरs because the fpsr and
		 * fpcr are 32-bits wide.
		 */
		.size = माप(u32),
		.align = माप(u32),
		.active = fpr_active,
		.regset_get = fpr_get,
		.set = fpr_set
	पूर्ण,
	[REGSET_TLS] = अणु
		.core_note_type = NT_ARM_TLS,
		.n = 1,
		.size = माप(व्योम *),
		.align = माप(व्योम *),
		.regset_get = tls_get,
		.set = tls_set,
	पूर्ण,
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	[REGSET_HW_BREAK] = अणु
		.core_note_type = NT_ARM_HW_BREAK,
		.n = माप(काष्ठा user_hwdebug_state) / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = hw_अवरोध_get,
		.set = hw_अवरोध_set,
	पूर्ण,
	[REGSET_HW_WATCH] = अणु
		.core_note_type = NT_ARM_HW_WATCH,
		.n = माप(काष्ठा user_hwdebug_state) / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = hw_अवरोध_get,
		.set = hw_अवरोध_set,
	पूर्ण,
#पूर्ण_अगर
	[REGSET_SYSTEM_CALL] = अणु
		.core_note_type = NT_ARM_SYSTEM_CALL,
		.n = 1,
		.size = माप(पूर्णांक),
		.align = माप(पूर्णांक),
		.regset_get = प्रणाली_call_get,
		.set = प्रणाली_call_set,
	पूर्ण,
#अगर_घोषित CONFIG_ARM64_SVE
	[REGSET_SVE] = अणु /* Scalable Vector Extension */
		.core_note_type = NT_ARM_SVE,
		.n = DIV_ROUND_UP(SVE_PT_SIZE(SVE_VQ_MAX, SVE_PT_REGS_SVE),
				  SVE_VQ_BYTES),
		.size = SVE_VQ_BYTES,
		.align = SVE_VQ_BYTES,
		.regset_get = sve_get,
		.set = sve_set,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_PTR_AUTH
	[REGSET_PAC_MASK] = अणु
		.core_note_type = NT_ARM_PAC_MASK,
		.n = माप(काष्ठा user_pac_mask) / माप(u64),
		.size = माप(u64),
		.align = माप(u64),
		.regset_get = pac_mask_get,
		/* this cannot be set dynamically */
	पूर्ण,
	[REGSET_PAC_ENABLED_KEYS] = अणु
		.core_note_type = NT_ARM_PAC_ENABLED_KEYS,
		.n = 1,
		.size = माप(दीर्घ),
		.align = माप(दीर्घ),
		.regset_get = pac_enabled_keys_get,
		.set = pac_enabled_keys_set,
	पूर्ण,
#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	[REGSET_PACA_KEYS] = अणु
		.core_note_type = NT_ARM_PACA_KEYS,
		.n = माप(काष्ठा user_pac_address_keys) / माप(__uपूर्णांक128_t),
		.size = माप(__uपूर्णांक128_t),
		.align = माप(__uपूर्णांक128_t),
		.regset_get = pac_address_keys_get,
		.set = pac_address_keys_set,
	पूर्ण,
	[REGSET_PACG_KEYS] = अणु
		.core_note_type = NT_ARM_PACG_KEYS,
		.n = माप(काष्ठा user_pac_generic_keys) / माप(__uपूर्णांक128_t),
		.size = माप(__uपूर्णांक128_t),
		.align = माप(__uपूर्णांक128_t),
		.regset_get = pac_generic_keys_get,
		.set = pac_generic_keys_set,
	पूर्ण,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_TAGGED_ADDR_ABI
	[REGSET_TAGGED_ADDR_CTRL] = अणु
		.core_note_type = NT_ARM_TAGGED_ADDR_CTRL,
		.n = 1,
		.size = माप(दीर्घ),
		.align = माप(दीर्घ),
		.regset_get = tagged_addr_ctrl_get,
		.set = tagged_addr_ctrl_set,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_aarch64_view = अणु
	.name = "aarch64", .e_machine = EM_AARCH64,
	.regsets = aarch64_regsets, .n = ARRAY_SIZE(aarch64_regsets)
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
क्रमागत compat_regset अणु
	REGSET_COMPAT_GPR,
	REGSET_COMPAT_VFP,
पूर्ण;

अटल अंतरभूत compat_uदीर्घ_t compat_get_user_reg(काष्ठा task_काष्ठा *task, पूर्णांक idx)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(task);

	चयन (idx) अणु
	हाल 15:
		वापस regs->pc;
	हाल 16:
		वापस pstate_to_compat_psr(regs->pstate);
	हाल 17:
		वापस regs->orig_x0;
	शेष:
		वापस regs->regs[idx];
	पूर्ण
पूर्ण

अटल पूर्णांक compat_gpr_get(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  काष्ठा membuf to)
अणु
	पूर्णांक i = 0;

	जबतक (to.left)
		membuf_store(&to, compat_get_user_reg(target, i++));
	वापस 0;
पूर्ण

अटल पूर्णांक compat_gpr_set(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			  स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs newregs;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i, start, num_regs;

	/* Calculate the number of AArch32 रेजिस्टरs contained in count */
	num_regs = count / regset->size;

	/* Convert pos पूर्णांकo an रेजिस्टर number */
	start = pos / regset->size;

	अगर (start + num_regs > regset->n)
		वापस -EIO;

	newregs = *task_pt_regs(target);

	क्रम (i = 0; i < num_regs; ++i) अणु
		अचिन्हित पूर्णांक idx = start + i;
		compat_uदीर्घ_t reg;

		अगर (kbuf) अणु
			स_नकल(&reg, kbuf, माप(reg));
			kbuf += माप(reg);
		पूर्ण अन्यथा अणु
			ret = copy_from_user(&reg, ubuf, माप(reg));
			अगर (ret) अणु
				ret = -EFAULT;
				अवरोध;
			पूर्ण

			ubuf += माप(reg);
		पूर्ण

		चयन (idx) अणु
		हाल 15:
			newregs.pc = reg;
			अवरोध;
		हाल 16:
			reg = compat_psr_to_pstate(reg);
			newregs.pstate = reg;
			अवरोध;
		हाल 17:
			newregs.orig_x0 = reg;
			अवरोध;
		शेष:
			newregs.regs[idx] = reg;
		पूर्ण

	पूर्ण

	अगर (valid_user_regs(&newregs.user_regs, target))
		*task_pt_regs(target) = newregs;
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक compat_vfp_get(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  काष्ठा membuf to)
अणु
	काष्ठा user_fpsimd_state *uregs;
	compat_uदीर्घ_t fpscr;

	अगर (!प्रणाली_supports_fpsimd())
		वापस -EINVAL;

	uregs = &target->thपढ़ो.uw.fpsimd_state;

	अगर (target == current)
		fpsimd_preserve_current_state();

	/*
	 * The VFP रेजिस्टरs are packed पूर्णांकo the fpsimd_state, so they all sit
	 * nicely together क्रम us. We just need to create the fpscr separately.
	 */
	membuf_ग_लिखो(&to, uregs, VFP_STATE_SIZE - माप(compat_uदीर्घ_t));
	fpscr = (uregs->fpsr & VFP_FPSCR_STAT_MASK) |
		(uregs->fpcr & VFP_FPSCR_CTRL_MASK);
	वापस membuf_store(&to, fpscr);
पूर्ण

अटल पूर्णांक compat_vfp_set(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			  स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा user_fpsimd_state *uregs;
	compat_uदीर्घ_t fpscr;
	पूर्णांक ret, vregs_end_pos;

	अगर (!प्रणाली_supports_fpsimd())
		वापस -EINVAL;

	uregs = &target->thपढ़ो.uw.fpsimd_state;

	vregs_end_pos = VFP_STATE_SIZE - माप(compat_uदीर्घ_t);
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, uregs, 0,
				 vregs_end_pos);

	अगर (count && !ret) अणु
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &fpscr,
					 vregs_end_pos, VFP_STATE_SIZE);
		अगर (!ret) अणु
			uregs->fpsr = fpscr & VFP_FPSCR_STAT_MASK;
			uregs->fpcr = fpscr & VFP_FPSCR_CTRL_MASK;
		पूर्ण
	पूर्ण

	fpsimd_flush_task_state(target);
	वापस ret;
पूर्ण

अटल पूर्णांक compat_tls_get(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  काष्ठा membuf to)
अणु
	वापस membuf_store(&to, (compat_uदीर्घ_t)target->thपढ़ो.uw.tp_value);
पूर्ण

अटल पूर्णांक compat_tls_set(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset, अचिन्हित पूर्णांक pos,
			  अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf,
			  स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	compat_uदीर्घ_t tls = target->thपढ़ो.uw.tp_value;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &tls, 0, -1);
	अगर (ret)
		वापस ret;

	target->thपढ़ो.uw.tp_value = tls;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा user_regset aarch32_regsets[] = अणु
	[REGSET_COMPAT_GPR] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = COMPAT_ELF_NGREG,
		.size = माप(compat_elf_greg_t),
		.align = माप(compat_elf_greg_t),
		.regset_get = compat_gpr_get,
		.set = compat_gpr_set
	पूर्ण,
	[REGSET_COMPAT_VFP] = अणु
		.core_note_type = NT_ARM_VFP,
		.n = VFP_STATE_SIZE / माप(compat_uदीर्घ_t),
		.size = माप(compat_uदीर्घ_t),
		.align = माप(compat_uदीर्घ_t),
		.active = fpr_active,
		.regset_get = compat_vfp_get,
		.set = compat_vfp_set
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_aarch32_view = अणु
	.name = "aarch32", .e_machine = EM_ARM,
	.regsets = aarch32_regsets, .n = ARRAY_SIZE(aarch32_regsets)
पूर्ण;

अटल स्थिर काष्ठा user_regset aarch32_ptrace_regsets[] = अणु
	[REGSET_GPR] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = COMPAT_ELF_NGREG,
		.size = माप(compat_elf_greg_t),
		.align = माप(compat_elf_greg_t),
		.regset_get = compat_gpr_get,
		.set = compat_gpr_set
	पूर्ण,
	[REGSET_FPR] = अणु
		.core_note_type = NT_ARM_VFP,
		.n = VFP_STATE_SIZE / माप(compat_uदीर्घ_t),
		.size = माप(compat_uदीर्घ_t),
		.align = माप(compat_uदीर्घ_t),
		.regset_get = compat_vfp_get,
		.set = compat_vfp_set
	पूर्ण,
	[REGSET_TLS] = अणु
		.core_note_type = NT_ARM_TLS,
		.n = 1,
		.size = माप(compat_uदीर्घ_t),
		.align = माप(compat_uदीर्घ_t),
		.regset_get = compat_tls_get,
		.set = compat_tls_set,
	पूर्ण,
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	[REGSET_HW_BREAK] = अणु
		.core_note_type = NT_ARM_HW_BREAK,
		.n = माप(काष्ठा user_hwdebug_state) / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = hw_अवरोध_get,
		.set = hw_अवरोध_set,
	पूर्ण,
	[REGSET_HW_WATCH] = अणु
		.core_note_type = NT_ARM_HW_WATCH,
		.n = माप(काष्ठा user_hwdebug_state) / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = hw_अवरोध_get,
		.set = hw_अवरोध_set,
	पूर्ण,
#पूर्ण_अगर
	[REGSET_SYSTEM_CALL] = अणु
		.core_note_type = NT_ARM_SYSTEM_CALL,
		.n = 1,
		.size = माप(पूर्णांक),
		.align = माप(पूर्णांक),
		.regset_get = प्रणाली_call_get,
		.set = प्रणाली_call_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_aarch32_ptrace_view = अणु
	.name = "aarch32", .e_machine = EM_ARM,
	.regsets = aarch32_ptrace_regsets, .n = ARRAY_SIZE(aarch32_ptrace_regsets)
पूर्ण;

अटल पूर्णांक compat_ptrace_पढ़ो_user(काष्ठा task_काष्ठा *tsk, compat_uदीर्घ_t off,
				   compat_uदीर्घ_t __user *ret)
अणु
	compat_uदीर्घ_t पंचांगp;

	अगर (off & 3)
		वापस -EIO;

	अगर (off == COMPAT_PT_TEXT_ADDR)
		पंचांगp = tsk->mm->start_code;
	अन्यथा अगर (off == COMPAT_PT_DATA_ADDR)
		पंचांगp = tsk->mm->start_data;
	अन्यथा अगर (off == COMPAT_PT_TEXT_END_ADDR)
		पंचांगp = tsk->mm->end_code;
	अन्यथा अगर (off < माप(compat_elf_gregset_t))
		पंचांगp = compat_get_user_reg(tsk, off >> 2);
	अन्यथा अगर (off >= COMPAT_USER_SZ)
		वापस -EIO;
	अन्यथा
		पंचांगp = 0;

	वापस put_user(पंचांगp, ret);
पूर्ण

अटल पूर्णांक compat_ptrace_ग_लिखो_user(काष्ठा task_काष्ठा *tsk, compat_uदीर्घ_t off,
				    compat_uदीर्घ_t val)
अणु
	काष्ठा pt_regs newregs = *task_pt_regs(tsk);
	अचिन्हित पूर्णांक idx = off / 4;

	अगर (off & 3 || off >= COMPAT_USER_SZ)
		वापस -EIO;

	अगर (off >= माप(compat_elf_gregset_t))
		वापस 0;

	चयन (idx) अणु
	हाल 15:
		newregs.pc = val;
		अवरोध;
	हाल 16:
		newregs.pstate = compat_psr_to_pstate(val);
		अवरोध;
	हाल 17:
		newregs.orig_x0 = val;
		अवरोध;
	शेष:
		newregs.regs[idx] = val;
	पूर्ण

	अगर (!valid_user_regs(&newregs.user_regs, tsk))
		वापस -EINVAL;

	*task_pt_regs(tsk) = newregs;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT

/*
 * Convert a भव रेजिस्टर number पूर्णांकo an index क्रम a thपढ़ो_info
 * अवरोधpoपूर्णांक array. Breakpoपूर्णांकs are identअगरied using positive numbers
 * whilst watchpoपूर्णांकs are negative. The रेजिस्टरs are laid out as pairs
 * of (address, control), each pair mapping to a unique hw_अवरोधpoपूर्णांक काष्ठा.
 * Register 0 is reserved क्रम describing resource inक्रमmation.
 */
अटल पूर्णांक compat_ptrace_hbp_num_to_idx(compat_दीर्घ_t num)
अणु
	वापस (असल(num) - 1) >> 1;
पूर्ण

अटल पूर्णांक compat_ptrace_hbp_get_resource_info(u32 *kdata)
अणु
	u8 num_brps, num_wrps, debug_arch, wp_len;
	u32 reg = 0;

	num_brps	= hw_अवरोधpoपूर्णांक_slots(TYPE_INST);
	num_wrps	= hw_अवरोधpoपूर्णांक_slots(TYPE_DATA);

	debug_arch	= debug_monitors_arch();
	wp_len		= 8;
	reg		|= debug_arch;
	reg		<<= 8;
	reg		|= wp_len;
	reg		<<= 8;
	reg		|= num_wrps;
	reg		<<= 8;
	reg		|= num_brps;

	*kdata = reg;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_ptrace_hbp_get(अचिन्हित पूर्णांक note_type,
				 काष्ठा task_काष्ठा *tsk,
				 compat_दीर्घ_t num,
				 u32 *kdata)
अणु
	u64 addr = 0;
	u32 ctrl = 0;

	पूर्णांक err, idx = compat_ptrace_hbp_num_to_idx(num);

	अगर (num & 1) अणु
		err = ptrace_hbp_get_addr(note_type, tsk, idx, &addr);
		*kdata = (u32)addr;
	पूर्ण अन्यथा अणु
		err = ptrace_hbp_get_ctrl(note_type, tsk, idx, &ctrl);
		*kdata = ctrl;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक compat_ptrace_hbp_set(अचिन्हित पूर्णांक note_type,
				 काष्ठा task_काष्ठा *tsk,
				 compat_दीर्घ_t num,
				 u32 *kdata)
अणु
	u64 addr;
	u32 ctrl;

	पूर्णांक err, idx = compat_ptrace_hbp_num_to_idx(num);

	अगर (num & 1) अणु
		addr = *kdata;
		err = ptrace_hbp_set_addr(note_type, tsk, idx, addr);
	पूर्ण अन्यथा अणु
		ctrl = *kdata;
		err = ptrace_hbp_set_ctrl(note_type, tsk, idx, ctrl);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक compat_ptrace_gethbpregs(काष्ठा task_काष्ठा *tsk, compat_दीर्घ_t num,
				    compat_uदीर्घ_t __user *data)
अणु
	पूर्णांक ret;
	u32 kdata;

	/* Watchpoपूर्णांक */
	अगर (num < 0) अणु
		ret = compat_ptrace_hbp_get(NT_ARM_HW_WATCH, tsk, num, &kdata);
	/* Resource info */
	पूर्ण अन्यथा अगर (num == 0) अणु
		ret = compat_ptrace_hbp_get_resource_info(&kdata);
	/* Breakpoपूर्णांक */
	पूर्ण अन्यथा अणु
		ret = compat_ptrace_hbp_get(NT_ARM_HW_BREAK, tsk, num, &kdata);
	पूर्ण

	अगर (!ret)
		ret = put_user(kdata, data);

	वापस ret;
पूर्ण

अटल पूर्णांक compat_ptrace_sethbpregs(काष्ठा task_काष्ठा *tsk, compat_दीर्घ_t num,
				    compat_uदीर्घ_t __user *data)
अणु
	पूर्णांक ret;
	u32 kdata = 0;

	अगर (num == 0)
		वापस 0;

	ret = get_user(kdata, data);
	अगर (ret)
		वापस ret;

	अगर (num < 0)
		ret = compat_ptrace_hbp_set(NT_ARM_HW_WATCH, tsk, num, &kdata);
	अन्यथा
		ret = compat_ptrace_hbp_set(NT_ARM_HW_BREAK, tsk, num, &kdata);

	वापस ret;
पूर्ण
#पूर्ण_अगर	/* CONFIG_HAVE_HW_BREAKPOINT */

दीर्घ compat_arch_ptrace(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			compat_uदीर्घ_t caddr, compat_uदीर्घ_t cdata)
अणु
	अचिन्हित दीर्घ addr = caddr;
	अचिन्हित दीर्घ data = cdata;
	व्योम __user *datap = compat_ptr(data);
	पूर्णांक ret;

	चयन (request) अणु
		हाल PTRACE_PEEKUSR:
			ret = compat_ptrace_पढ़ो_user(child, addr, datap);
			अवरोध;

		हाल PTRACE_POKEUSR:
			ret = compat_ptrace_ग_लिखो_user(child, addr, data);
			अवरोध;

		हाल COMPAT_PTRACE_GETREGS:
			ret = copy_regset_to_user(child,
						  &user_aarch32_view,
						  REGSET_COMPAT_GPR,
						  0, माप(compat_elf_gregset_t),
						  datap);
			अवरोध;

		हाल COMPAT_PTRACE_SETREGS:
			ret = copy_regset_from_user(child,
						    &user_aarch32_view,
						    REGSET_COMPAT_GPR,
						    0, माप(compat_elf_gregset_t),
						    datap);
			अवरोध;

		हाल COMPAT_PTRACE_GET_THREAD_AREA:
			ret = put_user((compat_uदीर्घ_t)child->thपढ़ो.uw.tp_value,
				       (compat_uदीर्घ_t __user *)datap);
			अवरोध;

		हाल COMPAT_PTRACE_SET_SYSCALL:
			task_pt_regs(child)->syscallno = data;
			ret = 0;
			अवरोध;

		हाल COMPAT_PTRACE_GETVFPREGS:
			ret = copy_regset_to_user(child,
						  &user_aarch32_view,
						  REGSET_COMPAT_VFP,
						  0, VFP_STATE_SIZE,
						  datap);
			अवरोध;

		हाल COMPAT_PTRACE_SETVFPREGS:
			ret = copy_regset_from_user(child,
						    &user_aarch32_view,
						    REGSET_COMPAT_VFP,
						    0, VFP_STATE_SIZE,
						    datap);
			अवरोध;

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
		हाल COMPAT_PTRACE_GETHBPREGS:
			ret = compat_ptrace_gethbpregs(child, addr, datap);
			अवरोध;

		हाल COMPAT_PTRACE_SETHBPREGS:
			ret = compat_ptrace_sethbpregs(child, addr, datap);
			अवरोध;
#पूर्ण_अगर

		शेष:
			ret = compat_ptrace_request(child, request, addr,
						    data);
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_COMPAT
	/*
	 * Core dumping of 32-bit tasks or compat ptrace requests must use the
	 * user_aarch32_view compatible with arm32. Native ptrace requests on
	 * 32-bit children use an extended user_aarch32_ptrace_view to allow
	 * access to the TLS रेजिस्टर.
	 */
	अगर (is_compat_task())
		वापस &user_aarch32_view;
	अन्यथा अगर (is_compat_thपढ़ो(task_thपढ़ो_info(task)))
		वापस &user_aarch32_ptrace_view;
#पूर्ण_अगर
	वापस &user_aarch64_view;
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	चयन (request) अणु
	हाल PTRACE_PEEKMTETAGS:
	हाल PTRACE_POKEMTETAGS:
		वापस mte_ptrace_copy_tags(child, request, addr, data);
	पूर्ण

	वापस ptrace_request(child, request, addr, data);
पूर्ण

क्रमागत ptrace_syscall_dir अणु
	PTRACE_SYSCALL_ENTER = 0,
	PTRACE_SYSCALL_EXIT,
पूर्ण;

अटल व्योम tracehook_report_syscall(काष्ठा pt_regs *regs,
				     क्रमागत ptrace_syscall_dir dir)
अणु
	पूर्णांक regno;
	अचिन्हित दीर्घ saved_reg;

	/*
	 * We have some ABI weirdness here in the way that we handle syscall
	 * निकास stops because we indicate whether or not the stop has been
	 * संकेतled from syscall entry or syscall निकास by clobbering a general
	 * purpose रेजिस्टर (ip/r12 क्रम AArch32, x7 क्रम AArch64) in the tracee
	 * and restoring its old value after the stop. This means that:
	 *
	 * - Any ग_लिखोs by the tracer to this रेजिस्टर during the stop are
	 *   ignored/discarded.
	 *
	 * - The actual value of the रेजिस्टर is not available during the stop,
	 *   so the tracer cannot save it and restore it later.
	 *
	 * - Syscall stops behave dअगरferently to seccomp and pseuकरो-step traps
	 *   (the latter करो not nobble any रेजिस्टरs).
	 */
	regno = (is_compat_task() ? 12 : 7);
	saved_reg = regs->regs[regno];
	regs->regs[regno] = dir;

	अगर (dir == PTRACE_SYSCALL_ENTER) अणु
		अगर (tracehook_report_syscall_entry(regs))
			क्रमget_syscall(regs);
		regs->regs[regno] = saved_reg;
	पूर्ण अन्यथा अगर (!test_thपढ़ो_flag(TIF_SINGLESTEP)) अणु
		tracehook_report_syscall_निकास(regs, 0);
		regs->regs[regno] = saved_reg;
	पूर्ण अन्यथा अणु
		regs->regs[regno] = saved_reg;

		/*
		 * Signal a pseuकरो-step exception since we are stepping but
		 * tracer modअगरications to the रेजिस्टरs may have rewound the
		 * state machine.
		 */
		tracehook_report_syscall_निकास(regs, 1);
	पूर्ण
पूर्ण

पूर्णांक syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags = READ_ONCE(current_thपढ़ो_info()->flags);

	अगर (flags & (_TIF_SYSCALL_EMU | _TIF_SYSCALL_TRACE)) अणु
		tracehook_report_syscall(regs, PTRACE_SYSCALL_ENTER);
		अगर (flags & _TIF_SYSCALL_EMU)
			वापस NO_SYSCALL;
	पूर्ण

	/* Do the secure computing after ptrace; failures should be fast. */
	अगर (secure_computing() == -1)
		वापस NO_SYSCALL;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_enter(regs, regs->syscallno);

	audit_syscall_entry(regs->syscallno, regs->orig_x0, regs->regs[1],
			    regs->regs[2], regs->regs[3]);

	वापस regs->syscallno;
पूर्ण

व्योम syscall_trace_निकास(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags = READ_ONCE(current_thपढ़ो_info()->flags);

	audit_syscall_निकास(regs);

	अगर (flags & _TIF_SYSCALL_TRACEPOINT)
		trace_sys_निकास(regs, regs_वापस_value(regs));

	अगर (flags & (_TIF_SYSCALL_TRACE | _TIF_SINGLESTEP))
		tracehook_report_syscall(regs, PTRACE_SYSCALL_EXIT);

	rseq_syscall(regs);
पूर्ण

/*
 * SPSR_ELx bits which are always architecturally RES0 per ARM DDI 0487D.a.
 * We permit userspace to set SSBS (AArch64 bit 12, AArch32 bit 23) which is
 * not described in ARM DDI 0487D.a.
 * We treat PAN and UAO as RES0 bits, as they are meaningless at EL0, and may
 * be allocated an EL0 meaning in future.
 * Userspace cannot use these until they have an architectural meaning.
 * Note that this follows the SPSR_ELx क्रमmat, not the AArch32 PSR क्रमmat.
 * We also reserve IL क्रम the kernel; SS is handled dynamically.
 */
#घोषणा SPSR_EL1_AARCH64_RES0_BITS \
	(GENMASK_ULL(63, 32) | GENMASK_ULL(27, 26) | GENMASK_ULL(23, 22) | \
	 GENMASK_ULL(20, 13) | GENMASK_ULL(5, 5))
#घोषणा SPSR_EL1_AARCH32_RES0_BITS \
	(GENMASK_ULL(63, 32) | GENMASK_ULL(22, 22) | GENMASK_ULL(20, 20))

अटल पूर्णांक valid_compat_regs(काष्ठा user_pt_regs *regs)
अणु
	regs->pstate &= ~SPSR_EL1_AARCH32_RES0_BITS;

	अगर (!प्रणाली_supports_mixed_endian_el0()) अणु
		अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
			regs->pstate |= PSR_AA32_E_BIT;
		अन्यथा
			regs->pstate &= ~PSR_AA32_E_BIT;
	पूर्ण

	अगर (user_mode(regs) && (regs->pstate & PSR_MODE32_BIT) &&
	    (regs->pstate & PSR_AA32_A_BIT) == 0 &&
	    (regs->pstate & PSR_AA32_I_BIT) == 0 &&
	    (regs->pstate & PSR_AA32_F_BIT) == 0) अणु
		वापस 1;
	पूर्ण

	/*
	 * Force PSR to a valid 32-bit EL0t, preserving the same bits as
	 * arch/arm.
	 */
	regs->pstate &= PSR_AA32_N_BIT | PSR_AA32_Z_BIT |
			PSR_AA32_C_BIT | PSR_AA32_V_BIT |
			PSR_AA32_Q_BIT | PSR_AA32_IT_MASK |
			PSR_AA32_GE_MASK | PSR_AA32_E_BIT |
			PSR_AA32_T_BIT;
	regs->pstate |= PSR_MODE32_BIT;

	वापस 0;
पूर्ण

अटल पूर्णांक valid_native_regs(काष्ठा user_pt_regs *regs)
अणु
	regs->pstate &= ~SPSR_EL1_AARCH64_RES0_BITS;

	अगर (user_mode(regs) && !(regs->pstate & PSR_MODE32_BIT) &&
	    (regs->pstate & PSR_D_BIT) == 0 &&
	    (regs->pstate & PSR_A_BIT) == 0 &&
	    (regs->pstate & PSR_I_BIT) == 0 &&
	    (regs->pstate & PSR_F_BIT) == 0) अणु
		वापस 1;
	पूर्ण

	/* Force PSR to a valid 64-bit EL0t */
	regs->pstate &= PSR_N_BIT | PSR_Z_BIT | PSR_C_BIT | PSR_V_BIT;

	वापस 0;
पूर्ण

/*
 * Are the current रेजिस्टरs suitable क्रम user mode? (used to मुख्यtain
 * security in संकेत handlers)
 */
पूर्णांक valid_user_regs(काष्ठा user_pt_regs *regs, काष्ठा task_काष्ठा *task)
अणु
	/* https://lore.kernel.org/lkml/20191118131525.GA4180@willie-the-truck */
	user_regs_reset_single_step(regs, task);

	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(task)))
		वापस valid_compat_regs(regs);
	अन्यथा
		वापस valid_native_regs(regs);
पूर्ण
