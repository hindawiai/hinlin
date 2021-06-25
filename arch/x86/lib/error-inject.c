<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/error-injection.h>
#समावेश <linux/kprobes.h>

यंत्रlinkage व्योम just_वापस_func(व्योम);

यंत्र(
	".text\n"
	".type just_return_func, @function\n"
	".globl just_return_func\n"
	"just_return_func:\n"
	"	ret\n"
	".size just_return_func, .-just_return_func\n"
);

व्योम override_function_with_वापस(काष्ठा pt_regs *regs)
अणु
	regs->ip = (अचिन्हित दीर्घ)&just_वापस_func;
पूर्ण
NOKPROBE_SYMBOL(override_function_with_वापस);
