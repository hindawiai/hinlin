<शैली गुरु>
/*
 * Based on linux/arch/mips/txx9/rbtx4938/setup.c,
 *	    and RBTX49xx patch from CELF patch archive.
 *
 * Copyright 2001, 2003-2005 MontaVista Software Inc.
 * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)
 * (C) Copyright TOSHIBA CORPORATION 2000-2001, 2004-2007
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/tx4927.h>

पूर्णांक __init tx4927_report_pciclk(व्योम)
अणु
	पूर्णांक pciclk = 0;

	pr_info("PCIC --%s PCICLK:",
		(__raw_पढ़ोq(&tx4927_ccfgptr->ccfg) & TX4927_CCFG_PCI66) ?
		" PCI66" : "");
	अगर (__raw_पढ़ोq(&tx4927_ccfgptr->pcfg) & TX4927_PCFG_PCICLKEN_ALL) अणु
		u64 ccfg = __raw_पढ़ोq(&tx4927_ccfgptr->ccfg);
		चयन ((अचिन्हित दीर्घ)ccfg &
			TX4927_CCFG_PCIDIVMODE_MASK) अणु
		हाल TX4927_CCFG_PCIDIVMODE_2_5:
			pciclk = txx9_cpu_घड़ी * 2 / 5; अवरोध;
		हाल TX4927_CCFG_PCIDIVMODE_3:
			pciclk = txx9_cpu_घड़ी / 3; अवरोध;
		हाल TX4927_CCFG_PCIDIVMODE_5:
			pciclk = txx9_cpu_घड़ी / 5; अवरोध;
		हाल TX4927_CCFG_PCIDIVMODE_6:
			pciclk = txx9_cpu_घड़ी / 6; अवरोध;
		पूर्ण
		pr_cont("Internal(%u.%uMHz)",
			(pciclk + 50000) / 1000000,
			((pciclk + 50000) / 100000) % 10);
	पूर्ण अन्यथा अणु
		pr_cont("External");
		pciclk = -1;
	पूर्ण
	pr_cont("\n");
	वापस pciclk;
पूर्ण

पूर्णांक __init tx4927_pciclk66_setup(व्योम)
अणु
	पूर्णांक pciclk;

	/* Assert M66EN */
	tx4927_ccfg_set(TX4927_CCFG_PCI66);
	/* Double PCICLK (अगर possible) */
	अगर (__raw_पढ़ोq(&tx4927_ccfgptr->pcfg) & TX4927_PCFG_PCICLKEN_ALL) अणु
		अचिन्हित पूर्णांक pciभागmode = 0;
		u64 ccfg = __raw_पढ़ोq(&tx4927_ccfgptr->ccfg);
		pciभागmode = (अचिन्हित दीर्घ)ccfg &
			TX4927_CCFG_PCIDIVMODE_MASK;
		चयन (pciभागmode) अणु
		हाल TX4927_CCFG_PCIDIVMODE_5:
		हाल TX4927_CCFG_PCIDIVMODE_2_5:
			pciभागmode = TX4927_CCFG_PCIDIVMODE_2_5;
			pciclk = txx9_cpu_घड़ी * 2 / 5;
			अवरोध;
		हाल TX4927_CCFG_PCIDIVMODE_6:
		हाल TX4927_CCFG_PCIDIVMODE_3:
		शेष:
			pciभागmode = TX4927_CCFG_PCIDIVMODE_3;
			pciclk = txx9_cpu_घड़ी / 3;
		पूर्ण
		tx4927_ccfg_change(TX4927_CCFG_PCIDIVMODE_MASK,
				   pciभागmode);
		pr_debug("PCICLK: ccfg:%08lx\n",
			 (अचिन्हित दीर्घ)__raw_पढ़ोq(&tx4927_ccfgptr->ccfg));
	पूर्ण अन्यथा
		pciclk = -1;
	वापस pciclk;
पूर्ण

व्योम __init tx4927_setup_pcierr_irq(व्योम)
अणु
	अगर (request_irq(TXX9_IRQ_BASE + TX4927_IR_PCIERR,
			tx4927_pcierr_पूर्णांकerrupt,
			0, "PCI error",
			(व्योम *)TX4927_PCIC_REG))
		pr_warn("Failed to request irq for PCIERR\n");
पूर्ण
