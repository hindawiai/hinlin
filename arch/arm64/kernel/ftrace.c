<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm64/kernel/ftrace.c
 *
 * Copyright (C) 2013 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 */

#समावेश <linux/ftrace.h>
#समावेश <linux/module.h>
#समावेश <linux/swab.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/insn.h>

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
/*
 * Replace a single inकाष्ठाion, which may be a branch or NOP.
 * If @validate == true, a replaced inकाष्ठाion is checked against 'old'.
 */
अटल पूर्णांक ftrace_modअगरy_code(अचिन्हित दीर्घ pc, u32 old, u32 new,
			      bool validate)
अणु
	u32 replaced;

	/*
	 * Note:
	 * We are paranoid about modअगरying text, as अगर a bug were to happen, it
	 * could cause us to पढ़ो or ग_लिखो to someplace that could cause harm.
	 * Carefully पढ़ो and modअगरy the code with aarch64_insn_*() which uses
	 * probe_kernel_*(), and make sure what we पढ़ो is what we expected it
	 * to be beक्रमe modअगरying it.
	 */
	अगर (validate) अणु
		अगर (aarch64_insn_पढ़ो((व्योम *)pc, &replaced))
			वापस -EFAULT;

		अगर (replaced != old)
			वापस -EINVAL;
	पूर्ण
	अगर (aarch64_insn_patch_text_nosync((व्योम *)pc, new))
		वापस -EPERM;

	वापस 0;
पूर्ण

/*
 * Replace tracer function in ftrace_caller()
 */
पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित दीर्घ pc;
	u32 new;

	pc = (अचिन्हित दीर्घ)function_nocfi(ftrace_call);
	new = aarch64_insn_gen_branch_imm(pc, (अचिन्हित दीर्घ)func,
					  AARCH64_INSN_BRANCH_LINK);

	वापस ftrace_modअगरy_code(pc, 0, new, false);
पूर्ण

अटल काष्ठा plt_entry *get_ftrace_plt(काष्ठा module *mod, अचिन्हित दीर्घ addr)
अणु
#अगर_घोषित CONFIG_ARM64_MODULE_PLTS
	काष्ठा plt_entry *plt = mod->arch.ftrace_trampolines;

	अगर (addr == FTRACE_ADDR)
		वापस &plt[FTRACE_PLT_IDX];
	अगर (addr == FTRACE_REGS_ADDR &&
	    IS_ENABLED(CONFIG_DYNAMIC_FTRACE_WITH_REGS))
		वापस &plt[FTRACE_REGS_PLT_IDX];
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

/*
 * Turn on the call to ftrace_caller() in instrumented function
 */
पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pc = rec->ip;
	u32 old, new;
	दीर्घ offset = (दीर्घ)pc - (दीर्घ)addr;

	अगर (offset < -SZ_128M || offset >= SZ_128M) अणु
		काष्ठा module *mod;
		काष्ठा plt_entry *plt;

		अगर (!IS_ENABLED(CONFIG_ARM64_MODULE_PLTS))
			वापस -EINVAL;

		/*
		 * On kernels that support module PLTs, the offset between the
		 * branch inकाष्ठाion and its target may legally exceed the
		 * range of an ordinary relative 'bl' opcode. In this हाल, we
		 * need to branch via a trampoline in the module.
		 *
		 * NOTE: __module_text_address() must be called with preemption
		 * disabled, but we can rely on ftrace_lock to ensure that 'mod'
		 * retains its validity throughout the reमुख्यder of this code.
		 */
		preempt_disable();
		mod = __module_text_address(pc);
		preempt_enable();

		अगर (WARN_ON(!mod))
			वापस -EINVAL;

		plt = get_ftrace_plt(mod, addr);
		अगर (!plt) अणु
			pr_err("ftrace: no module PLT for %ps\n", (व्योम *)addr);
			वापस -EINVAL;
		पूर्ण

		addr = (अचिन्हित दीर्घ)plt;
	पूर्ण

	old = aarch64_insn_gen_nop();
	new = aarch64_insn_gen_branch_imm(pc, addr, AARCH64_INSN_BRANCH_LINK);

	वापस ftrace_modअगरy_code(pc, old, new, true);
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
			अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pc = rec->ip;
	u32 old, new;

	old = aarch64_insn_gen_branch_imm(pc, old_addr,
					  AARCH64_INSN_BRANCH_LINK);
	new = aarch64_insn_gen_branch_imm(pc, addr, AARCH64_INSN_BRANCH_LINK);

	वापस ftrace_modअगरy_code(pc, old, new, true);
पूर्ण

/*
 * The compiler has inserted two NOPs beक्रमe the regular function prologue.
 * All instrumented functions follow the AAPCS, so x0-x8 and x19-x30 are live,
 * and x9-x18 are मुक्त क्रम our use.
 *
 * At runसमय we want to be able to swing a single NOP <-> BL to enable or
 * disable the ftrace call. The BL requires us to save the original LR value,
 * so here we insert a <MOV X9, LR> over the first NOP so the inकाष्ठाions
 * beक्रमe the regular prologue are:
 *
 * | Compiled | Disabled   | Enabled    |
 * +----------+------------+------------+
 * | NOP      | MOV X9, LR | MOV X9, LR |
 * | NOP      | NOP        | BL <entry> |
 *
 * The LR value will be recovered by ftrace_regs_entry, and restored पूर्णांकo LR
 * beक्रमe वापसing to the regular function prologue. When a function is not
 * being traced, the MOV is not harmful given x9 is not live per the AAPCS.
 *
 * Note: ftrace_process_locs() has pre-adjusted rec->ip to be the address of
 * the BL.
 */
पूर्णांक ftrace_init_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec)
अणु
	अचिन्हित दीर्घ pc = rec->ip - AARCH64_INSN_SIZE;
	u32 old, new;

	old = aarch64_insn_gen_nop();
	new = aarch64_insn_gen_move_reg(AARCH64_INSN_REG_9,
					AARCH64_INSN_REG_LR,
					AARCH64_INSN_VARIANT_64BIT);
	वापस ftrace_modअगरy_code(pc, old, new, true);
पूर्ण
#पूर्ण_अगर

/*
 * Turn off the call to ftrace_caller() in instrumented function
 */
पूर्णांक ftrace_make_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec,
		    अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pc = rec->ip;
	bool validate = true;
	u32 old = 0, new;
	दीर्घ offset = (दीर्घ)pc - (दीर्घ)addr;

	अगर (offset < -SZ_128M || offset >= SZ_128M) अणु
		u32 replaced;

		अगर (!IS_ENABLED(CONFIG_ARM64_MODULE_PLTS))
			वापस -EINVAL;

		/*
		 * 'mod' is only set at module load समय, but अगर we end up
		 * dealing with an out-of-range condition, we can assume it
		 * is due to a module being loaded far away from the kernel.
		 */
		अगर (!mod) अणु
			preempt_disable();
			mod = __module_text_address(pc);
			preempt_enable();

			अगर (WARN_ON(!mod))
				वापस -EINVAL;
		पूर्ण

		/*
		 * The inकाष्ठाion we are about to patch may be a branch and
		 * link inकाष्ठाion that was redirected via a PLT entry. In
		 * this हाल, the normal validation will fail, but we can at
		 * least check that we are dealing with a branch and link
		 * inकाष्ठाion that poपूर्णांकs पूर्णांकo the right module.
		 */
		अगर (aarch64_insn_पढ़ो((व्योम *)pc, &replaced))
			वापस -EFAULT;

		अगर (!aarch64_insn_is_bl(replaced) ||
		    !within_module(pc + aarch64_get_branch_offset(replaced),
				   mod))
			वापस -EINVAL;

		validate = false;
	पूर्ण अन्यथा अणु
		old = aarch64_insn_gen_branch_imm(pc, addr,
						  AARCH64_INSN_BRANCH_LINK);
	पूर्ण

	new = aarch64_insn_gen_nop();

	वापस ftrace_modअगरy_code(pc, old, new, validate);
पूर्ण

व्योम arch_ftrace_update_code(पूर्णांक command)
अणु
	command |= FTRACE_MAY_SLEEP;
	ftrace_modअगरy_all_code(command);
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
/*
 * function_graph tracer expects ftrace_वापस_to_handler() to be called
 * on the way back to parent. For this purpose, this function is called
 * in _mcount() or ftrace_caller() to replace वापस address (*parent) on
 * the call stack to वापस_to_handler.
 *
 * Note that @frame_poपूर्णांकer is used only क्रम sanity check later.
 */
व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ self_addr, अचिन्हित दीर्घ *parent,
			   अचिन्हित दीर्घ frame_poपूर्णांकer)
अणु
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ)&वापस_to_handler;
	अचिन्हित दीर्घ old;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	/*
	 * Note:
	 * No protection against faulting at *parent, which may be seen
	 * on other archs. It's unlikely on AArch64.
	 */
	old = *parent;

	अगर (!function_graph_enter(old, self_addr, frame_poपूर्णांकer, शून्य))
		*parent = वापस_hooker;
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
/*
 * Turn on/off the call to ftrace_graph_caller() in ftrace_caller()
 * depending on @enable.
 */
अटल पूर्णांक ftrace_modअगरy_graph_caller(bool enable)
अणु
	अचिन्हित दीर्घ pc = (अचिन्हित दीर्घ)&ftrace_graph_call;
	u32 branch, nop;

	branch = aarch64_insn_gen_branch_imm(pc,
					     (अचिन्हित दीर्घ)ftrace_graph_caller,
					     AARCH64_INSN_BRANCH_NOLINK);
	nop = aarch64_insn_gen_nop();

	अगर (enable)
		वापस ftrace_modअगरy_code(pc, nop, branch, true);
	अन्यथा
		वापस ftrace_modअगरy_code(pc, branch, nop, true);
पूर्ण

पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	वापस ftrace_modअगरy_graph_caller(true);
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	वापस ftrace_modअगरy_graph_caller(false);
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */
