<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Borrowed heavily from MIPS
 */

#समावेश <linux/export.h>
#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(inकाष्ठाion_poपूर्णांकer(regs));
	अगर (fixup) अणु
		regs->ret = fixup->fixup;

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CC_OPTIMIZE_FOR_SIZE

अचिन्हित दीर्घ arc_clear_user_noअंतरभूत(व्योम __user *to,
		अचिन्हित दीर्घ n)
अणु
	वापस __arc_clear_user(to, n);
पूर्ण
EXPORT_SYMBOL(arc_clear_user_noअंतरभूत);

दीर्घ arc_म_नकलन_from_user_noअंतरभूत(अक्षर *dst, स्थिर अक्षर __user *src,
		दीर्घ count)
अणु
	वापस __arc_म_नकलन_from_user(dst, src, count);
पूर्ण
EXPORT_SYMBOL(arc_म_नकलन_from_user_noअंतरभूत);

दीर्घ arc_strnlen_user_noअंतरभूत(स्थिर अक्षर __user *src, दीर्घ n)
अणु
	वापस __arc_strnlen_user(src, n);
पूर्ण
EXPORT_SYMBOL(arc_strnlen_user_noअंतरभूत);
#पूर्ण_अगर
