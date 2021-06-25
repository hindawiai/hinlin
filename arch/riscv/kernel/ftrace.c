<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 * Copyright (C) 2017 Andes Technology Corporation
 */

#समावेश <linux/ftrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/memory.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/patch.h>

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
पूर्णांक ftrace_arch_code_modअगरy_prepare(व्योम) __acquires(&text_mutex)
अणु
	mutex_lock(&text_mutex);
	वापस 0;
पूर्ण

पूर्णांक ftrace_arch_code_modअगरy_post_process(व्योम) __releases(&text_mutex)
अणु
	mutex_unlock(&text_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_check_current_call(अचिन्हित दीर्घ hook_pos,
				     अचिन्हित पूर्णांक *expected)
अणु
	अचिन्हित पूर्णांक replaced[2];
	अचिन्हित पूर्णांक nops[2] = अणुNOP4, NOP4पूर्ण;

	/* we expect nops at the hook position */
	अगर (!expected)
		expected = nops;

	/*
	 * Read the text we want to modअगरy;
	 * वापस must be -EFAULT on पढ़ो error
	 */
	अगर (copy_from_kernel_nofault(replaced, (व्योम *)hook_pos,
			MCOUNT_INSN_SIZE))
		वापस -EFAULT;

	/*
	 * Make sure it is what we expect it to be;
	 * वापस must be -EINVAL on failed comparison
	 */
	अगर (स_भेद(expected, replaced, माप(replaced))) अणु
		pr_err("%p: expected (%08x %08x) but got (%08x %08x)\n",
		       (व्योम *)hook_pos, expected[0], expected[1], replaced[0],
		       replaced[1]);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __ftrace_modअगरy_call(अचिन्हित दीर्घ hook_pos, अचिन्हित दीर्घ target,
				bool enable)
अणु
	अचिन्हित पूर्णांक call[2];
	अचिन्हित पूर्णांक nops[2] = अणुNOP4, NOP4पूर्ण;

	make_call(hook_pos, target, call);

	/* Replace the auipc-jalr pair at once. Return -EPERM on ग_लिखो error. */
	अगर (patch_text_nosync
	    ((व्योम *)hook_pos, enable ? call : nops, MCOUNT_INSN_SIZE))
		वापस -EPERM;

	वापस 0;
पूर्ण

/*
 * Put 5 inकाष्ठाions with 16 bytes at the front of function within
 * patchable function entry nops' area.
 *
 * 0: REG_S  ra, -SZREG(sp)
 * 1: auipc  ra, 0x?
 * 2: jalr   -?(ra)
 * 3: REG_L  ra, -SZREG(sp)
 *
 * So the opcodes is:
 * 0: 0xfe113c23 (sd)/0xfe112e23 (sw)
 * 1: 0x???????? -> auipc
 * 2: 0x???????? -> jalr
 * 3: 0xff813083 (ld)/0xffc12083 (lw)
 */
#अगर __riscv_xlen == 64
#घोषणा INSN0	0xfe113c23
#घोषणा INSN3	0xff813083
#या_अगर __riscv_xlen == 32
#घोषणा INSN0	0xfe112e23
#घोषणा INSN3	0xffc12083
#पूर्ण_अगर

#घोषणा FUNC_ENTRY_SIZE	16
#घोषणा FUNC_ENTRY_JMP	4

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक call[4] = अणुINSN0, 0, 0, INSN3पूर्ण;
	अचिन्हित दीर्घ target = addr;
	अचिन्हित दीर्घ caller = rec->ip + FUNC_ENTRY_JMP;

	call[1] = to_auipc_insn((अचिन्हित पूर्णांक)(target - caller));
	call[2] = to_jalr_insn((अचिन्हित पूर्णांक)(target - caller));

	अगर (patch_text_nosync((व्योम *)rec->ip, call, FUNC_ENTRY_SIZE))
		वापस -EPERM;

	वापस 0;
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec,
		    अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक nops[4] = अणुNOP4, NOP4, NOP4, NOP4पूर्ण;

	अगर (patch_text_nosync((व्योम *)rec->ip, nops, FUNC_ENTRY_SIZE))
		वापस -EPERM;

	वापस 0;
पूर्ण


/*
 * This is called early on, and isn't wrapped by
 * ftrace_arch_code_modअगरy_अणुprepare,post_processपूर्ण() and thereक्रम करोesn't hold
 * text_mutex, which triggers a lockdep failure.  SMP isn't running so we could
 * just directly poke the text, but it's simpler to just take the lock
 * ourselves.
 */
पूर्णांक ftrace_init_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec)
अणु
	पूर्णांक out;

	ftrace_arch_code_modअगरy_prepare();
	out = ftrace_make_nop(mod, rec, MCOUNT_ADDR);
	ftrace_arch_code_modअगरy_post_process();

	वापस out;
पूर्ण

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	पूर्णांक ret = __ftrace_modअगरy_call((अचिन्हित दीर्घ)&ftrace_call,
				       (अचिन्हित दीर्घ)func, true);
	अगर (!ret) अणु
		ret = __ftrace_modअगरy_call((अचिन्हित दीर्घ)&ftrace_regs_call,
					   (अचिन्हित दीर्घ)func, true);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
		       अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक call[2];
	अचिन्हित दीर्घ caller = rec->ip + FUNC_ENTRY_JMP;
	पूर्णांक ret;

	make_call(caller, old_addr, call);
	ret = ftrace_check_current_call(caller, call);

	अगर (ret)
		वापस ret;

	वापस __ftrace_modअगरy_call(caller, addr, true);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
/*
 * Most of this function is copied from arm64.
 */
व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ *parent, अचिन्हित दीर्घ self_addr,
			   अचिन्हित दीर्घ frame_poपूर्णांकer)
अणु
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ)&वापस_to_handler;
	अचिन्हित दीर्घ old;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	/*
	 * We करोn't suffer access faults, so no extra fault-recovery assembly
	 * is needed here.
	 */
	old = *parent;

	अगर (!function_graph_enter(old, self_addr, frame_poपूर्णांकer, parent))
		*parent = वापस_hooker;
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य व्योम ftrace_graph_call(व्योम);
बाह्य व्योम ftrace_graph_regs_call(व्योम);
पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	पूर्णांक ret;

	ret = __ftrace_modअगरy_call((अचिन्हित दीर्घ)&ftrace_graph_call,
				    (अचिन्हित दीर्घ)&prepare_ftrace_वापस, true);
	अगर (ret)
		वापस ret;

	वापस __ftrace_modअगरy_call((अचिन्हित दीर्घ)&ftrace_graph_regs_call,
				    (अचिन्हित दीर्घ)&prepare_ftrace_वापस, true);
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	पूर्णांक ret;

	ret = __ftrace_modअगरy_call((अचिन्हित दीर्घ)&ftrace_graph_call,
				    (अचिन्हित दीर्घ)&prepare_ftrace_वापस, false);
	अगर (ret)
		वापस ret;

	वापस __ftrace_modअगरy_call((अचिन्हित दीर्घ)&ftrace_graph_regs_call,
				    (अचिन्हित दीर्घ)&prepare_ftrace_वापस, false);
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */
