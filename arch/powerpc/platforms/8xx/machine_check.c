<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ptrace.h>

#समावेश <यंत्र/reg.h>

पूर्णांक machine_check_8xx(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ reason = regs->msr;

	pr_err("Machine check in kernel mode.\n");
	pr_err("Caused by (from SRR1=%lx): ", reason);
	अगर (reason & 0x40000000)
		pr_cont("Fetch error at address %lx\n", regs->nip);
	अन्यथा
		pr_cont("Data access error at address %lx\n", regs->dar);

#अगर_घोषित CONFIG_PCI
	/* the qspan pci पढ़ो routines can cause machine checks -- Cort
	 *
	 * yuck !!! that totally needs to go away ! There are better ways
	 * to deal with that than having a wart in the mcheck handler.
	 * -- BenH
	 */
	bad_page_fault(regs, SIGBUS);
	वापस 1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण
