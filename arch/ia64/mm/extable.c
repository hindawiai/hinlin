<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Kernel exception handling table support.  Derived from arch/alpha/mm/extable.c.
 *
 * Copyright (C) 1998, 1999, 2001-2002, 2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/processor.h>

व्योम
ia64_handle_exception (काष्ठा pt_regs *regs, स्थिर काष्ठा exception_table_entry *e)
अणु
	दीर्घ fix = (u64) &e->fixup + e->fixup;

	regs->r8 = -EFAULT;
	अगर (fix & 4)
		regs->r9 = 0;
	regs->cr_iip = fix & ~0xf;
	ia64_psr(regs)->ri = fix & 0x3;		/* set continuation slot number */
पूर्ण
