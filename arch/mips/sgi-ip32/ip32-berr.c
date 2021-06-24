<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 1995, 1996, 1999, 2000 by Ralf Baechle
 * Copyright (C) 1999, 2000 by Silicon Graphics
 * Copyright (C) 2002  Maciej W. Rozycki
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/tlbdebug.h>

अटल पूर्णांक ip32_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	पूर्णांक data = regs->cp0_cause & 4;

	अगर (is_fixup)
		वापस MIPS_BE_FIXUP;

	prपूर्णांकk("Got %cbe at 0x%lx\n", data ? 'd' : 'i', regs->cp0_epc);
	show_regs(regs);
	dump_tlb_all();
	जबतक(1);
	क्रमce_sig(SIGBUS);
पूर्ण

व्योम __init ip32_be_init(व्योम)
अणु
	board_be_handler = ip32_be_handler;
पूर्ण
