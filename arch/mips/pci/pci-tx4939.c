<शैली गुरु>
/*
 * Based on linux/arch/mips/txx9/rbtx4939/setup.c,
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
#समावेश <यंत्र/txx9/tx4939.h>

पूर्णांक __init tx4939_report_pciclk(व्योम)
अणु
	पूर्णांक pciclk = 0;

	pr_info("PCIC --%s PCICLK:",
		(__raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_PCI66) ?
		" PCI66" : "");
	अगर (__raw_पढ़ोq(&tx4939_ccfgptr->pcfg) & TX4939_PCFG_PCICLKEN_ALL) अणु
		pciclk = txx9_master_घड़ी * 20 / 6;
		अगर (!(__raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_PCI66))
			pciclk /= 2;
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

व्योम __init tx4939_report_pci1clk(व्योम)
अणु
	अचिन्हित पूर्णांक pciclk = txx9_master_घड़ी * 20 / 6;

	pr_info("PCIC1 -- PCICLK:%u.%uMHz\n",
		(pciclk + 50000) / 1000000,
		((pciclk + 50000) / 100000) % 10);
पूर्ण

पूर्णांक tx4939_pcic1_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot)
अणु
	अगर (get_tx4927_pcicptr(dev->bus->sysdata) == tx4939_pcic1ptr) अणु
		चयन (slot) अणु
		हाल TX4927_PCIC_IDSEL_AD_TO_SLOT(31):
			अगर (__raw_पढ़ोq(&tx4939_ccfgptr->pcfg) &
			    TX4939_PCFG_ET0MODE)
				वापस TXX9_IRQ_BASE + TX4939_IR_ETH(0);
			अवरोध;
		हाल TX4927_PCIC_IDSEL_AD_TO_SLOT(30):
			अगर (__raw_पढ़ोq(&tx4939_ccfgptr->pcfg) &
			    TX4939_PCFG_ET1MODE)
				वापस TXX9_IRQ_BASE + TX4939_IR_ETH(1);
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

पूर्णांक tx4939_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq = tx4939_pcic1_map_irq(dev, slot);

	अगर (irq >= 0)
		वापस irq;
	irq = pin;
	/* IRQ rotation */
	irq--;	/* 0-3 */
	irq = (irq + 33 - slot) % 4;
	irq++;	/* 1-4 */

	चयन (irq) अणु
	हाल 1:
		irq = TXX9_IRQ_BASE + TX4939_IR_INTA;
		अवरोध;
	हाल 2:
		irq = TXX9_IRQ_BASE + TX4939_IR_INTB;
		अवरोध;
	हाल 3:
		irq = TXX9_IRQ_BASE + TX4939_IR_INTC;
		अवरोध;
	हाल 4:
		irq = TXX9_IRQ_BASE + TX4939_IR_INTD;
		अवरोध;
	पूर्ण
	वापस irq;
पूर्ण

व्योम __init tx4939_setup_pcierr_irq(व्योम)
अणु
	अगर (request_irq(TXX9_IRQ_BASE + TX4939_IR_PCIERR,
			tx4927_pcierr_पूर्णांकerrupt,
			0, "PCI error",
			(व्योम *)TX4939_PCIC_REG))
		pr_warn("Failed to request irq for PCIERR\n");
पूर्ण
