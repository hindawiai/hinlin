<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Sunplus Core Technology Co., Ltd.
 *  Lennox Wu <lennox.wu@sunplusct.com>
 *  Chen Liqin <liqin.chen@sunplusct.com>
 * Copyright (C) 2013 Regents of the University of Calअगरornia
 */


#समावेश <linux/extable.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(regs->epc);
	अगर (fixup) अणु
		regs->epc = fixup->fixup;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
