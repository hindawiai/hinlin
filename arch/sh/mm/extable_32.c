<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/mm/extable.c
 *  Taken from:
 *   linux/arch/i386/mm/extable.c
 */

#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/ptrace.h>

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(regs->pc);
	अगर (fixup) अणु
		regs->pc = fixup->fixup;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
