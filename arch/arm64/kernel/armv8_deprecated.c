<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2014 ARM Limited
 */

#समावेश <linux/cpu.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/kprobes.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace-events-emulation.h"

/*
 * The runसमय support क्रम deprecated inकाष्ठाion support can be in one of
 * following three states -
 *
 * 0 = undef
 * 1 = emulate (software emulation)
 * 2 = hw (supported in hardware)
 */
क्रमागत insn_emulation_mode अणु
	INSN_UNDEF,
	INSN_EMULATE,
	INSN_HW,
पूर्ण;

क्रमागत legacy_insn_status अणु
	INSN_DEPRECATED,
	INSN_OBSOLETE,
पूर्ण;

काष्ठा insn_emulation_ops अणु
	स्थिर अक्षर		*name;
	क्रमागत legacy_insn_status	status;
	काष्ठा undef_hook	*hooks;
	पूर्णांक			(*set_hw_mode)(bool enable);
पूर्ण;

काष्ठा insn_emulation अणु
	काष्ठा list_head node;
	काष्ठा insn_emulation_ops *ops;
	पूर्णांक current_mode;
	पूर्णांक min;
	पूर्णांक max;
पूर्ण;

अटल LIST_HEAD(insn_emulation);
अटल पूर्णांक nr_insn_emulated __initdata;
अटल DEFINE_RAW_SPINLOCK(insn_emulation_lock);

अटल व्योम रेजिस्टर_emulation_hooks(काष्ठा insn_emulation_ops *ops)
अणु
	काष्ठा undef_hook *hook;

	BUG_ON(!ops->hooks);

	क्रम (hook = ops->hooks; hook->instr_mask; hook++)
		रेजिस्टर_undef_hook(hook);

	pr_notice("Registered %s emulation handler\n", ops->name);
पूर्ण

अटल व्योम हटाओ_emulation_hooks(काष्ठा insn_emulation_ops *ops)
अणु
	काष्ठा undef_hook *hook;

	BUG_ON(!ops->hooks);

	क्रम (hook = ops->hooks; hook->instr_mask; hook++)
		unरेजिस्टर_undef_hook(hook);

	pr_notice("Removed %s emulation handler\n", ops->name);
पूर्ण

अटल व्योम enable_insn_hw_mode(व्योम *data)
अणु
	काष्ठा insn_emulation *insn = (काष्ठा insn_emulation *)data;
	अगर (insn->ops->set_hw_mode)
		insn->ops->set_hw_mode(true);
पूर्ण

अटल व्योम disable_insn_hw_mode(व्योम *data)
अणु
	काष्ठा insn_emulation *insn = (काष्ठा insn_emulation *)data;
	अगर (insn->ops->set_hw_mode)
		insn->ops->set_hw_mode(false);
पूर्ण

/* Run set_hw_mode(mode) on all active CPUs */
अटल पूर्णांक run_all_cpu_set_hw_mode(काष्ठा insn_emulation *insn, bool enable)
अणु
	अगर (!insn->ops->set_hw_mode)
		वापस -EINVAL;
	अगर (enable)
		on_each_cpu(enable_insn_hw_mode, (व्योम *)insn, true);
	अन्यथा
		on_each_cpu(disable_insn_hw_mode, (व्योम *)insn, true);
	वापस 0;
पूर्ण

/*
 * Run set_hw_mode क्रम all insns on a starting CPU.
 * Returns:
 *  0 		- If all the hooks ran successfully.
 * -EINVAL	- At least one hook is not supported by the CPU.
 */
अटल पूर्णांक run_all_insn_set_hw_mode(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा insn_emulation *insn;

	raw_spin_lock_irqsave(&insn_emulation_lock, flags);
	list_क्रम_each_entry(insn, &insn_emulation, node) अणु
		bool enable = (insn->current_mode == INSN_HW);
		अगर (insn->ops->set_hw_mode && insn->ops->set_hw_mode(enable)) अणु
			pr_warn("CPU[%u] cannot support the emulation of %s",
				cpu, insn->ops->name);
			rc = -EINVAL;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&insn_emulation_lock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक update_insn_emulation_mode(काष्ठा insn_emulation *insn,
				       क्रमागत insn_emulation_mode prev)
अणु
	पूर्णांक ret = 0;

	चयन (prev) अणु
	हाल INSN_UNDEF: /* Nothing to be करोne */
		अवरोध;
	हाल INSN_EMULATE:
		हटाओ_emulation_hooks(insn->ops);
		अवरोध;
	हाल INSN_HW:
		अगर (!run_all_cpu_set_hw_mode(insn, false))
			pr_notice("Disabled %s support\n", insn->ops->name);
		अवरोध;
	पूर्ण

	चयन (insn->current_mode) अणु
	हाल INSN_UNDEF:
		अवरोध;
	हाल INSN_EMULATE:
		रेजिस्टर_emulation_hooks(insn->ops);
		अवरोध;
	हाल INSN_HW:
		ret = run_all_cpu_set_hw_mode(insn, true);
		अगर (!ret)
			pr_notice("Enabled %s support\n", insn->ops->name);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __init रेजिस्टर_insn_emulation(काष्ठा insn_emulation_ops *ops)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा insn_emulation *insn;

	insn = kzalloc(माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस;

	insn->ops = ops;
	insn->min = INSN_UNDEF;

	चयन (ops->status) अणु
	हाल INSN_DEPRECATED:
		insn->current_mode = INSN_EMULATE;
		/* Disable the HW mode अगर it was turned on at early boot समय */
		run_all_cpu_set_hw_mode(insn, false);
		insn->max = INSN_HW;
		अवरोध;
	हाल INSN_OBSOLETE:
		insn->current_mode = INSN_UNDEF;
		insn->max = INSN_EMULATE;
		अवरोध;
	पूर्ण

	raw_spin_lock_irqsave(&insn_emulation_lock, flags);
	list_add(&insn->node, &insn_emulation);
	nr_insn_emulated++;
	raw_spin_unlock_irqrestore(&insn_emulation_lock, flags);

	/* Register any handlers अगर required */
	update_insn_emulation_mode(insn, INSN_UNDEF);
पूर्ण

अटल पूर्णांक emulation_proc_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				  व्योम *buffer, माप_प्रकार *lenp,
				  loff_t *ppos)
अणु
	पूर्णांक ret = 0;
	काष्ठा insn_emulation *insn = (काष्ठा insn_emulation *) table->data;
	क्रमागत insn_emulation_mode prev_mode = insn->current_mode;

	table->data = &insn->current_mode;
	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	अगर (ret || !ग_लिखो || prev_mode == insn->current_mode)
		जाओ ret;

	ret = update_insn_emulation_mode(insn, prev_mode);
	अगर (ret) अणु
		/* Mode change failed, revert to previous mode. */
		insn->current_mode = prev_mode;
		update_insn_emulation_mode(insn, INSN_UNDEF);
	पूर्ण
ret:
	table->data = insn;
	वापस ret;
पूर्ण

अटल व्योम __init रेजिस्टर_insn_emulation_sysctl(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i = 0;
	काष्ठा insn_emulation *insn;
	काष्ठा ctl_table *insns_sysctl, *sysctl;

	insns_sysctl = kसुस्मृति(nr_insn_emulated + 1, माप(*sysctl),
			       GFP_KERNEL);
	अगर (!insns_sysctl)
		वापस;

	raw_spin_lock_irqsave(&insn_emulation_lock, flags);
	list_क्रम_each_entry(insn, &insn_emulation, node) अणु
		sysctl = &insns_sysctl[i];

		sysctl->mode = 0644;
		sysctl->maxlen = माप(पूर्णांक);

		sysctl->procname = insn->ops->name;
		sysctl->data = insn;
		sysctl->extra1 = &insn->min;
		sysctl->extra2 = &insn->max;
		sysctl->proc_handler = emulation_proc_handler;
		i++;
	पूर्ण
	raw_spin_unlock_irqrestore(&insn_emulation_lock, flags);

	रेजिस्टर_sysctl("abi", insns_sysctl);
पूर्ण

/*
 *  Implement emulation of the SWP/SWPB inकाष्ठाions using load-exclusive and
 *  store-exclusive.
 *
 *  Syntax of SWPअणुBपूर्ण inकाष्ठाion: SWPअणुBपूर्ण<c> <Rt>, <Rt2>, [<Rn>]
 *  Where: Rt  = destination
 *	   Rt2 = source
 *	   Rn  = address
 */

/*
 * Error-checking SWP macros implemented using ldxrअणुbपूर्ण/stxrअणुbपूर्ण
 */

/* Arbitrary स्थिरant to ensure क्रमward-progress of the LL/SC loop */
#घोषणा __SWP_LL_SC_LOOPS	4

#घोषणा __user_swpX_यंत्र(data, addr, res, temp, temp2, B)	\
करो अणु								\
	uaccess_enable_privileged();				\
	__यंत्र__ __अस्थिर__(					\
	"	mov		%w3, %w7\n"			\
	"0:	ldxr"B"		%w2, [%4]\n"			\
	"1:	stxr"B"		%w0, %w1, [%4]\n"		\
	"	cbz		%w0, 2f\n"			\
	"	sub		%w3, %w3, #1\n"			\
	"	cbnz		%w3, 0b\n"			\
	"	mov		%w0, %w5\n"			\
	"	b		3f\n"				\
	"2:\n"							\
	"	mov		%w1, %w2\n"			\
	"3:\n"							\
	"	.pushsection	 .fixup,\"ax\"\n"		\
	"	.align		2\n"				\
	"4:	mov		%w0, %w6\n"			\
	"	b		3b\n"				\
	"	.popsection"					\
	_ASM_EXTABLE(0b, 4b)					\
	_ASM_EXTABLE(1b, 4b)					\
	: "=&r" (res), "+r" (data), "=&r" (temp), "=&r" (temp2)	\
	: "r" ((अचिन्हित दीर्घ)addr), "i" (-EAGAIN),		\
	  "i" (-EFAULT),					\
	  "i" (__SWP_LL_SC_LOOPS)				\
	: "memory");						\
	uaccess_disable_privileged();				\
पूर्ण जबतक (0)

#घोषणा __user_swp_यंत्र(data, addr, res, temp, temp2) \
	__user_swpX_यंत्र(data, addr, res, temp, temp2, "")
#घोषणा __user_swpb_यंत्र(data, addr, res, temp, temp2) \
	__user_swpX_यंत्र(data, addr, res, temp, temp2, "b")

/*
 * Bit 22 of the inकाष्ठाion encoding distinguishes between
 * the SWP and SWPB variants (bit set means SWPB).
 */
#घोषणा TYPE_SWPB (1 << 22)

अटल पूर्णांक emulate_swpX(अचिन्हित पूर्णांक address, अचिन्हित पूर्णांक *data,
			अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक res = 0;

	अगर ((type != TYPE_SWPB) && (address & 0x3)) अणु
		/* SWP to unaligned address not permitted */
		pr_debug("SWP instruction on unaligned pointer!\n");
		वापस -EFAULT;
	पूर्ण

	जबतक (1) अणु
		अचिन्हित दीर्घ temp, temp2;

		अगर (type == TYPE_SWPB)
			__user_swpb_यंत्र(*data, address, res, temp, temp2);
		अन्यथा
			__user_swp_यंत्र(*data, address, res, temp, temp2);

		अगर (likely(res != -EAGAIN) || संकेत_pending(current))
			अवरोध;

		cond_resched();
	पूर्ण

	वापस res;
पूर्ण

#घोषणा ARM_OPCODE_CONDTEST_FAIL   0
#घोषणा ARM_OPCODE_CONDTEST_PASS   1
#घोषणा ARM_OPCODE_CONDTEST_UNCOND 2

#घोषणा	ARM_OPCODE_CONDITION_UNCOND	0xf

अटल अचिन्हित पूर्णांक __kprobes aarch32_check_condition(u32 opcode, u32 psr)
अणु
	u32 cc_bits  = opcode >> 28;

	अगर (cc_bits != ARM_OPCODE_CONDITION_UNCOND) अणु
		अगर ((*aarch32_opcode_cond_checks[cc_bits])(psr))
			वापस ARM_OPCODE_CONDTEST_PASS;
		अन्यथा
			वापस ARM_OPCODE_CONDTEST_FAIL;
	पूर्ण
	वापस ARM_OPCODE_CONDTEST_UNCOND;
पूर्ण

/*
 * swp_handler logs the id of calling process, dissects the inकाष्ठाion, sanity
 * checks the memory location, calls emulate_swpX क्रम the actual operation and
 * deals with fixup/error handling beक्रमe वापसing
 */
अटल पूर्णांक swp_handler(काष्ठा pt_regs *regs, u32 instr)
अणु
	u32 destreg, data, type, address = 0;
	स्थिर व्योम __user *user_ptr;
	पूर्णांक rn, rt2, res = 0;

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, regs->pc);

	type = instr & TYPE_SWPB;

	चयन (aarch32_check_condition(instr, regs->pstate)) अणु
	हाल ARM_OPCODE_CONDTEST_PASS:
		अवरोध;
	हाल ARM_OPCODE_CONDTEST_FAIL:
		/* Condition failed - वापस to next inकाष्ठाion */
		जाओ ret;
	हाल ARM_OPCODE_CONDTEST_UNCOND:
		/* If unconditional encoding - not a SWP, undef */
		वापस -EFAULT;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rn = aarch32_insn_extract_reg_num(instr, A32_RN_OFFSET);
	rt2 = aarch32_insn_extract_reg_num(instr, A32_RT2_OFFSET);

	address = (u32)regs->user_regs.regs[rn];
	data	= (u32)regs->user_regs.regs[rt2];
	destreg = aarch32_insn_extract_reg_num(instr, A32_RT_OFFSET);

	pr_debug("addr in r%d->0x%08x, dest is r%d, source in r%d->0x%08x)\n",
		rn, address, destreg,
		aarch32_insn_extract_reg_num(instr, A32_RT2_OFFSET), data);

	/* Check access in reasonable access range क्रम both SWP and SWPB */
	user_ptr = (स्थिर व्योम __user *)(अचिन्हित दीर्घ)(address & ~3);
	अगर (!access_ok(user_ptr, 4)) अणु
		pr_debug("SWP{B} emulation: access to 0x%08x not allowed!\n",
			address);
		जाओ fault;
	पूर्ण

	res = emulate_swpX(address, &data, type);
	अगर (res == -EFAULT)
		जाओ fault;
	अन्यथा अगर (res == 0)
		regs->user_regs.regs[destreg] = data;

ret:
	अगर (type == TYPE_SWPB)
		trace_inकाष्ठाion_emulation("swpb", regs->pc);
	अन्यथा
		trace_inकाष्ठाion_emulation("swp", regs->pc);

	pr_warn_ratelimited("\"%s\" (%ld) uses obsolete SWP{B} instruction at 0x%llx\n",
			current->comm, (अचिन्हित दीर्घ)current->pid, regs->pc);

	arm64_skip_faulting_inकाष्ठाion(regs, 4);
	वापस 0;

fault:
	pr_debug("SWP{B} emulation: access caused memory abort!\n");
	arm64_notअगरy_segfault(address);

	वापस 0;
पूर्ण

/*
 * Only emulate SWP/SWPB executed in ARM state/User mode.
 * The kernel must be SWP मुक्त and SWPअणुBपूर्ण करोes not exist in Thumb.
 */
अटल काष्ठा undef_hook swp_hooks[] = अणु
	अणु
		.instr_mask	= 0x0fb00ff0,
		.instr_val	= 0x01000090,
		.pstate_mask	= PSR_AA32_MODE_MASK,
		.pstate_val	= PSR_AA32_MODE_USR,
		.fn		= swp_handler
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा insn_emulation_ops swp_ops = अणु
	.name = "swp",
	.status = INSN_OBSOLETE,
	.hooks = swp_hooks,
	.set_hw_mode = शून्य,
पूर्ण;

अटल पूर्णांक cp15barrier_handler(काष्ठा pt_regs *regs, u32 instr)
अणु
	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, regs->pc);

	चयन (aarch32_check_condition(instr, regs->pstate)) अणु
	हाल ARM_OPCODE_CONDTEST_PASS:
		अवरोध;
	हाल ARM_OPCODE_CONDTEST_FAIL:
		/* Condition failed - वापस to next inकाष्ठाion */
		जाओ ret;
	हाल ARM_OPCODE_CONDTEST_UNCOND:
		/* If unconditional encoding - not a barrier inकाष्ठाion */
		वापस -EFAULT;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (aarch32_insn_mcr_extract_crm(instr)) अणु
	हाल 10:
		/*
		 * dmb - mcr p15, 0, Rt, c7, c10, 5
		 * dsb - mcr p15, 0, Rt, c7, c10, 4
		 */
		अगर (aarch32_insn_mcr_extract_opc2(instr) == 5) अणु
			dmb(sy);
			trace_inकाष्ठाion_emulation(
				"mcr p15, 0, Rt, c7, c10, 5 ; dmb", regs->pc);
		पूर्ण अन्यथा अणु
			dsb(sy);
			trace_inकाष्ठाion_emulation(
				"mcr p15, 0, Rt, c7, c10, 4 ; dsb", regs->pc);
		पूर्ण
		अवरोध;
	हाल 5:
		/*
		 * isb - mcr p15, 0, Rt, c7, c5, 4
		 *
		 * Taking an exception or वापसing from one acts as an
		 * inकाष्ठाion barrier. So no explicit barrier needed here.
		 */
		trace_inकाष्ठाion_emulation(
			"mcr p15, 0, Rt, c7, c5, 4 ; isb", regs->pc);
		अवरोध;
	पूर्ण

ret:
	pr_warn_ratelimited("\"%s\" (%ld) uses deprecated CP15 Barrier instruction at 0x%llx\n",
			current->comm, (अचिन्हित दीर्घ)current->pid, regs->pc);

	arm64_skip_faulting_inकाष्ठाion(regs, 4);
	वापस 0;
पूर्ण

अटल पूर्णांक cp15_barrier_set_hw_mode(bool enable)
अणु
	अगर (enable)
		sysreg_clear_set(sctlr_el1, 0, SCTLR_EL1_CP15BEN);
	अन्यथा
		sysreg_clear_set(sctlr_el1, SCTLR_EL1_CP15BEN, 0);
	वापस 0;
पूर्ण

अटल काष्ठा undef_hook cp15_barrier_hooks[] = अणु
	अणु
		.instr_mask	= 0x0fff0fdf,
		.instr_val	= 0x0e070f9a,
		.pstate_mask	= PSR_AA32_MODE_MASK,
		.pstate_val	= PSR_AA32_MODE_USR,
		.fn		= cp15barrier_handler,
	पूर्ण,
	अणु
		.instr_mask	= 0x0fff0fff,
		.instr_val	= 0x0e070f95,
		.pstate_mask	= PSR_AA32_MODE_MASK,
		.pstate_val	= PSR_AA32_MODE_USR,
		.fn		= cp15barrier_handler,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा insn_emulation_ops cp15_barrier_ops = अणु
	.name = "cp15_barrier",
	.status = INSN_DEPRECATED,
	.hooks = cp15_barrier_hooks,
	.set_hw_mode = cp15_barrier_set_hw_mode,
पूर्ण;

अटल पूर्णांक setend_set_hw_mode(bool enable)
अणु
	अगर (!cpu_supports_mixed_endian_el0())
		वापस -EINVAL;

	अगर (enable)
		sysreg_clear_set(sctlr_el1, SCTLR_EL1_SED, 0);
	अन्यथा
		sysreg_clear_set(sctlr_el1, 0, SCTLR_EL1_SED);
	वापस 0;
पूर्ण

अटल पूर्णांक compat_setend_handler(काष्ठा pt_regs *regs, u32 big_endian)
अणु
	अक्षर *insn;

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, regs->pc);

	अगर (big_endian) अणु
		insn = "setend be";
		regs->pstate |= PSR_AA32_E_BIT;
	पूर्ण अन्यथा अणु
		insn = "setend le";
		regs->pstate &= ~PSR_AA32_E_BIT;
	पूर्ण

	trace_inकाष्ठाion_emulation(insn, regs->pc);
	pr_warn_ratelimited("\"%s\" (%ld) uses deprecated setend instruction at 0x%llx\n",
			current->comm, (अचिन्हित दीर्घ)current->pid, regs->pc);

	वापस 0;
पूर्ण

अटल पूर्णांक a32_setend_handler(काष्ठा pt_regs *regs, u32 instr)
अणु
	पूर्णांक rc = compat_setend_handler(regs, (instr >> 9) & 1);
	arm64_skip_faulting_inकाष्ठाion(regs, 4);
	वापस rc;
पूर्ण

अटल पूर्णांक t16_setend_handler(काष्ठा pt_regs *regs, u32 instr)
अणु
	पूर्णांक rc = compat_setend_handler(regs, (instr >> 3) & 1);
	arm64_skip_faulting_inकाष्ठाion(regs, 2);
	वापस rc;
पूर्ण

अटल काष्ठा undef_hook setend_hooks[] = अणु
	अणु
		.instr_mask	= 0xfffffdff,
		.instr_val	= 0xf1010000,
		.pstate_mask	= PSR_AA32_MODE_MASK,
		.pstate_val	= PSR_AA32_MODE_USR,
		.fn		= a32_setend_handler,
	पूर्ण,
	अणु
		/* Thumb mode */
		.instr_mask	= 0xfffffff7,
		.instr_val	= 0x0000b650,
		.pstate_mask	= (PSR_AA32_T_BIT | PSR_AA32_MODE_MASK),
		.pstate_val	= (PSR_AA32_T_BIT | PSR_AA32_MODE_USR),
		.fn		= t16_setend_handler,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा insn_emulation_ops setend_ops = अणु
	.name = "setend",
	.status = INSN_DEPRECATED,
	.hooks = setend_hooks,
	.set_hw_mode = setend_set_hw_mode,
पूर्ण;

/*
 * Invoked as core_initcall, which guarantees that the inकाष्ठाion
 * emulation is पढ़ोy क्रम userspace.
 */
अटल पूर्णांक __init armv8_deprecated_init(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_SWP_EMULATION))
		रेजिस्टर_insn_emulation(&swp_ops);

	अगर (IS_ENABLED(CONFIG_CP15_BARRIER_EMULATION))
		रेजिस्टर_insn_emulation(&cp15_barrier_ops);

	अगर (IS_ENABLED(CONFIG_SETEND_EMULATION)) अणु
		अगर (प्रणाली_supports_mixed_endian_el0())
			रेजिस्टर_insn_emulation(&setend_ops);
		अन्यथा
			pr_info("setend instruction emulation is not supported on this system\n");
	पूर्ण

	cpuhp_setup_state_nocalls(CPUHP_AP_ARM64_ISNDEP_STARTING,
				  "arm64/isndep:starting",
				  run_all_insn_set_hw_mode, शून्य);
	रेजिस्टर_insn_emulation_sysctl();

	वापस 0;
पूर्ण

core_initcall(armv8_deprecated_init);
