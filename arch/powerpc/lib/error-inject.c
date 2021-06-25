<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/error-injection.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/uaccess.h>

व्योम override_function_with_वापस(काष्ठा pt_regs *regs)
अणु
	/*
	 * Emulate 'blr'. 'regs' represents the state on entry of a predefined
	 * function in the kernel/module, captured on a kprobe. We करोn't need
	 * to worry about 32-bit userspace on a 64-bit kernel.
	 */
	regs->nip = regs->link;
पूर्ण
NOKPROBE_SYMBOL(override_function_with_वापस);
