<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Based on arch/arm/mm/extable.c
 */

#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(inकाष्ठाion_poपूर्णांकer(regs));
	अगर (!fixup)
		वापस 0;

	अगर (in_bpf_jit(regs))
		वापस arm64_bpf_fixup_exception(fixup, regs);

	regs->pc = (अचिन्हित दीर्घ)&fixup->fixup + fixup->fixup;
	वापस 1;
पूर्ण
