<शैली गुरु>
/*
 * Dynamic function tracing support.
 *
 * Copyright (C) 2008 Abhishek Sagar <sagar.abhishek@gmail.com>
 * Copyright (C) 2010 Rabin Vincent <rabin@rab.in>
 *
 * For licencing details, see COPYING.
 *
 * Defines low-level handling of mcount calls when the kernel
 * is compiled with the -pg flag. When using dynamic ftrace, the
 * mcount call-sites get patched with NOP till they are enabled.
 * All code mutation routines here are called under stop_machine().
 */

#समावेश <linux/ftrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/stop_machine.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/opcodes.h>
#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/patch.h>

#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा	NOP		0xf85deb04	/* pop.w अणुlrपूर्ण */
#अन्यथा
#घोषणा	NOP		0xe8bd4000	/* pop अणुlrपूर्ण */
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

अटल पूर्णांक __ftrace_modअगरy_code(व्योम *data)
अणु
	पूर्णांक *command = data;

	ftrace_modअगरy_all_code(*command);

	वापस 0;
पूर्ण

व्योम arch_ftrace_update_code(पूर्णांक command)
अणु
	stop_machine(__ftrace_modअगरy_code, &command, शून्य);
पूर्ण

अटल अचिन्हित दीर्घ ftrace_nop_replace(काष्ठा dyn_ftrace *rec)
अणु
	वापस NOP;
पूर्ण

अटल अचिन्हित दीर्घ adjust_address(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण

पूर्णांक ftrace_arch_code_modअगरy_prepare(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक ftrace_arch_code_modअगरy_post_process(व्योम)
अणु
	/* Make sure any TLB misses during machine stop are cleared. */
	flush_tlb_all();
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ftrace_call_replace(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr)
अणु
	वापस arm_gen_branch_link(pc, addr);
पूर्ण

अटल पूर्णांक ftrace_modअगरy_code(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ old,
			      अचिन्हित दीर्घ new, bool validate)
अणु
	अचिन्हित दीर्घ replaced;

	अगर (IS_ENABLED(CONFIG_THUMB2_KERNEL))
		old = __opcode_to_mem_thumb32(old);
	अन्यथा
		old = __opcode_to_mem_arm(old);

	अगर (validate) अणु
		अगर (copy_from_kernel_nofault(&replaced, (व्योम *)pc,
				MCOUNT_INSN_SIZE))
			वापस -EFAULT;

		अगर (replaced != old)
			वापस -EINVAL;
	पूर्ण

	__patch_text((व्योम *)pc, new);

	वापस 0;
पूर्ण

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ new;
	पूर्णांक ret;

	pc = (अचिन्हित दीर्घ)&ftrace_call;
	new = ftrace_call_replace(pc, (अचिन्हित दीर्घ)func);

	ret = ftrace_modअगरy_code(pc, 0, new, false);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	अगर (!ret) अणु
		pc = (अचिन्हित दीर्घ)&ftrace_regs_call;
		new = ftrace_call_replace(pc, (अचिन्हित दीर्घ)func);

		ret = ftrace_modअगरy_code(pc, 0, new, false);
	पूर्ण
#पूर्ण_अगर

	वापस ret;
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ new, old;
	अचिन्हित दीर्घ ip = rec->ip;

	old = ftrace_nop_replace(rec);

	new = ftrace_call_replace(ip, adjust_address(rec, addr));

	वापस ftrace_modअगरy_code(rec->ip, old, new, true);
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS

पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
				अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ new, old;
	अचिन्हित दीर्घ ip = rec->ip;

	old = ftrace_call_replace(ip, adjust_address(rec, old_addr));

	new = ftrace_call_replace(ip, adjust_address(rec, addr));

	वापस ftrace_modअगरy_code(rec->ip, old, new, true);
पूर्ण

#पूर्ण_अगर

पूर्णांक ftrace_make_nop(काष्ठा module *mod,
		    काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	अचिन्हित दीर्घ old;
	अचिन्हित दीर्घ new;
	पूर्णांक ret;

	old = ftrace_call_replace(ip, adjust_address(rec, addr));
	new = ftrace_nop_replace(rec);
	ret = ftrace_modअगरy_code(ip, old, new, true);

	वापस ret;
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ *parent, अचिन्हित दीर्घ self_addr,
			   अचिन्हित दीर्घ frame_poपूर्णांकer)
अणु
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ) &वापस_to_handler;
	अचिन्हित दीर्घ old;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	old = *parent;
	*parent = वापस_hooker;

	अगर (function_graph_enter(old, self_addr, frame_poपूर्णांकer, शून्य))
		*parent = old;
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य अचिन्हित दीर्घ ftrace_graph_call;
बाह्य अचिन्हित दीर्घ ftrace_graph_call_old;
बाह्य व्योम ftrace_graph_caller_old(व्योम);
बाह्य अचिन्हित दीर्घ ftrace_graph_regs_call;
बाह्य व्योम ftrace_graph_regs_caller(व्योम);

अटल पूर्णांक __ftrace_modअगरy_caller(अचिन्हित दीर्घ *callsite,
				  व्योम (*func) (व्योम), bool enable)
अणु
	अचिन्हित दीर्घ caller_fn = (अचिन्हित दीर्घ) func;
	अचिन्हित दीर्घ pc = (अचिन्हित दीर्घ) callsite;
	अचिन्हित दीर्घ branch = arm_gen_branch(pc, caller_fn);
	अचिन्हित दीर्घ nop = 0xe1a00000;	/* mov r0, r0 */
	अचिन्हित दीर्घ old = enable ? nop : branch;
	अचिन्हित दीर्घ new = enable ? branch : nop;

	वापस ftrace_modअगरy_code(pc, old, new, true);
पूर्ण

अटल पूर्णांक ftrace_modअगरy_graph_caller(bool enable)
अणु
	पूर्णांक ret;

	ret = __ftrace_modअगरy_caller(&ftrace_graph_call,
				     ftrace_graph_caller,
				     enable);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	अगर (!ret)
		ret = __ftrace_modअगरy_caller(&ftrace_graph_regs_call,
				     ftrace_graph_regs_caller,
				     enable);
#पूर्ण_अगर


	वापस ret;
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
