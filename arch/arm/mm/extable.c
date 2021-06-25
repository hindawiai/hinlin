<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/arm/mm/extable.c
 */
#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(inकाष्ठाion_poपूर्णांकer(regs));
	अगर (fixup) अणु
		regs->ARM_pc = fixup->fixup;
#अगर_घोषित CONFIG_THUMB2_KERNEL
		/* Clear the IT state to aव्योम nasty surprises in the fixup */
		regs->ARM_cpsr &= ~PSR_IT_MASK;
#पूर्ण_अगर
	पूर्ण

	वापस fixup != शून्य;
पूर्ण
