<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(inकाष्ठाion_poपूर्णांकer(regs));
	अगर (fixup)
		regs->ipc = fixup->fixup;

	वापस fixup != शून्य;
पूर्ण
