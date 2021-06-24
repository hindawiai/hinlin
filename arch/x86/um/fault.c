<शैली गुरु>
/* 
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#समावेश <sysdep/ptrace.h>

/* These two are from यंत्र-um/uaccess.h and linux/module.h, check them. */
काष्ठा exception_table_entry
अणु
	अचिन्हित दीर्घ insn;
	अचिन्हित दीर्घ fixup;
पूर्ण;

स्थिर काष्ठा exception_table_entry *search_exception_tables(अचिन्हित दीर्घ add);

/* Compare this to arch/i386/mm/extable.c:fixup_exception() */
पूर्णांक arch_fixup(अचिन्हित दीर्घ address, काष्ठा uml_pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(address);
	अगर (fixup) अणु
		UPT_IP(regs) = fixup->fixup;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
