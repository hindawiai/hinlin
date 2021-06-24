<शैली गुरु>
/*
 * Copyright (C) 2010, Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009, Wind River Systems Inc
 *   Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(regs->ea);
	अगर (fixup) अणु
		regs->ea = fixup->fixup;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
