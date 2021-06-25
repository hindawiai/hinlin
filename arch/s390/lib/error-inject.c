<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/error-injection.h>
#समावेश <linux/kprobes.h>

व्योम override_function_with_वापस(काष्ठा pt_regs *regs)
अणु
	/*
	 * Emulate 'br 14'. 'regs' is captured by kprobes on entry to some
	 * kernel function.
	 */
	regs->psw.addr = regs->gprs[14];
पूर्ण
NOKPROBE_SYMBOL(override_function_with_वापस);
