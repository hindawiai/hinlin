<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/h8300/mm/fault.c
 *
 *  Copyright (C) 1998  D. Jeff Dionne <jeff@lineo.ca>,
 *  Copyright (C) 2000  Lineo, Inc.  (www.lineo.com)
 *
 *  Based on:
 *
 *  linux/arch/m68knommu/mm/fault.c
 *  linux/arch/m68k/mm/fault.c
 *
 *  Copyright (C) 1995  Hamish Macकरोnald
 */

#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>


व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *fp, अचिन्हित दीर्घ err);

/*
 * This routine handles page faults.  It determines the problem, and
 * then passes it off to one of the appropriate routines.
 *
 * error_code:
 *	bit 0 == 0 means no page found, 1 means protection fault
 *	bit 1 == 0 means पढ़ो, 1 means ग_लिखो
 *
 * If this routine detects a bad access, it वापसs 1, otherwise it
 * वापसs 0.
 */
यंत्रlinkage पूर्णांक करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
			      अचिन्हित दीर्घ error_code)
अणु
#अगर_घोषित DEBUG
	pr_debug("regs->sr=%#x, regs->pc=%#lx, address=%#lx, %ld\n",
		 regs->sr, regs->pc, address, error_code);
#पूर्ण_अगर

/*
 * Oops. The kernel tried to access some bad page. We'll have to
 * terminate things with extreme prejudice.
 */
	अगर ((अचिन्हित दीर्घ) address < PAGE_SIZE)
		pr_alert("Unable to handle kernel NULL pointer dereference");
	अन्यथा
		pr_alert("Unable to handle kernel access");
	prपूर्णांकk(" at virtual address %08lx\n", address);
	अगर (!user_mode(regs))
		die("Oops", regs, error_code);
	करो_निकास(SIGKILL);

	वापस 1;
पूर्ण
