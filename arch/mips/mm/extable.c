<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1997, 99, 2001 - 2004 Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/extable.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/branch.h>
#समावेश <linux/uaccess.h>

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(exception_epc(regs));
	अगर (fixup) अणु
		regs->cp0_epc = fixup->nextinsn;

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
