<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/error-injection.h>
#समावेश <linux/kprobes.h>

व्योम override_function_with_वापस(काष्ठा pt_regs *regs)
अणु
	/*
	 * 'regs' represents the state on entry of a predefined function in
	 * the kernel/module and which is captured on a kprobe.
	 *
	 * When kprobe वापसs back from exception it will override the end
	 * of probed function and directly वापस to the predefined
	 * function's caller.
	 */
	inकाष्ठाion_poपूर्णांकer_set(regs, procedure_link_poपूर्णांकer(regs));
पूर्ण
NOKPROBE_SYMBOL(override_function_with_वापस);
