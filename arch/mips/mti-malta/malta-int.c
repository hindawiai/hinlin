<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000, 2001, 2004 MIPS Technologies, Inc.
 * Copyright (C) 2001 Ralf Baechle
 * Copyright (C) 2013 Imagination Technologies Ltd.
 *
 * Routines क्रम generic manipulation of the पूर्णांकerrupts found on the MIPS
 * Malta board. The पूर्णांकerrupt controller is located in the South Bridge
 * a PIIX4 device with two पूर्णांकernal 82C95 पूर्णांकerrupt controllers.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>

#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/mips-boards/malta.h>
#समावेश <यंत्र/mips-boards/maltaपूर्णांक.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/gt64120.h>
#समावेश <यंत्र/mips-boards/generic.h>
#समावेश <यंत्र/mips-boards/msc01_pci.h>
#समावेश <यंत्र/msc01_ic.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/rtlx.h>

अटल अंतरभूत पूर्णांक mips_pcibios_iack(व्योम)
अणु
	पूर्णांक irq;

	/*
	 * Determine highest priority pending पूर्णांकerrupt by perक्रमming
	 * a PCI Interrupt Acknowledge cycle.
	 */
	चयन (mips_revision_sconid) अणु
	हाल MIPS_REVISION_SCON_SOCIT:
	हाल MIPS_REVISION_SCON_ROCIT:
	हाल MIPS_REVISION_SCON_SOCITSC:
	हाल MIPS_REVISION_SCON_SOCITSCP:
		MSC_READ(MSC01_PCI_IACK, irq);
		irq &= 0xff;
		अवरोध;
	हाल MIPS_REVISION_SCON_GT64120:
		irq = GT_READ(GT_PCI0_IACK_OFS);
		irq &= 0xff;
		अवरोध;
	हाल MIPS_REVISION_SCON_BONITO:
		/* The following will generate a PCI IACK cycle on the
		 * Bonito controller. It's a little bit kludgy, but it
		 * was the easiest way to implement it in hardware at
		 * the given समय.
		 */
		BONITO_PCIMAP_CFG = 0x20000;

		/* Flush Bonito रेजिस्टर block */
		(व्योम) BONITO_PCIMAP_CFG;
		iob();	  /* sync */

		irq = __raw_पढ़ोl((u32 *)_pcictrl_bonito_pcicfg);
		iob();	  /* sync */
		irq &= 0xff;
		BONITO_PCIMAP_CFG = 0;
		अवरोध;
	शेष:
		pr_emerg("Unknown system controller.\n");
		वापस -1;
	पूर्ण
	वापस irq;
पूर्ण

अटल व्योम corehi_irqdispatch(व्योम)
अणु
	अचिन्हित पूर्णांक पूर्णांकedge, पूर्णांकsteer, pcicmd, pcibadaddr;
	अचिन्हित पूर्णांक pcimstat, पूर्णांकisr, पूर्णांकen, पूर्णांकpol;
	अचिन्हित पूर्णांक पूर्णांकrcause, datalo, datahi;
	काष्ठा pt_regs *regs = get_irq_regs();

	pr_emerg("CoreHI interrupt, shouldn't happen, we die here!\n");
	pr_emerg("epc	 : %08lx\nStatus: %08lx\n"
		 "Cause : %08lx\nbadVaddr : %08lx\n",
		 regs->cp0_epc, regs->cp0_status,
		 regs->cp0_cause, regs->cp0_badvaddr);

	/* Read all the रेजिस्टरs and then prपूर्णांक them as there is a
	   problem with पूर्णांकerspersed prपूर्णांकk's upsetting the Bonito controller.
	   Do it क्रम the others too.
	*/

	चयन (mips_revision_sconid) अणु
	हाल MIPS_REVISION_SCON_SOCIT:
	हाल MIPS_REVISION_SCON_ROCIT:
	हाल MIPS_REVISION_SCON_SOCITSC:
	हाल MIPS_REVISION_SCON_SOCITSCP:
		ll_msc_irq();
		अवरोध;
	हाल MIPS_REVISION_SCON_GT64120:
		पूर्णांकrcause = GT_READ(GT_INTRCAUSE_OFS);
		datalo = GT_READ(GT_CPUERR_ADDRLO_OFS);
		datahi = GT_READ(GT_CPUERR_ADDRHI_OFS);
		pr_emerg("GT_INTRCAUSE = %08x\n", पूर्णांकrcause);
		pr_emerg("GT_CPUERR_ADDR = %02x%08x\n",
				datahi, datalo);
		अवरोध;
	हाल MIPS_REVISION_SCON_BONITO:
		pcibadaddr = BONITO_PCIBADADDR;
		pcimstat = BONITO_PCIMSTAT;
		पूर्णांकisr = BONITO_INTISR;
		पूर्णांकen = BONITO_INTEN;
		पूर्णांकpol = BONITO_INTPOL;
		पूर्णांकedge = BONITO_INTEDGE;
		पूर्णांकsteer = BONITO_INTSTEER;
		pcicmd = BONITO_PCICMD;
		pr_emerg("BONITO_INTISR = %08x\n", पूर्णांकisr);
		pr_emerg("BONITO_INTEN = %08x\n", पूर्णांकen);
		pr_emerg("BONITO_INTPOL = %08x\n", पूर्णांकpol);
		pr_emerg("BONITO_INTEDGE = %08x\n", पूर्णांकedge);
		pr_emerg("BONITO_INTSTEER = %08x\n", पूर्णांकsteer);
		pr_emerg("BONITO_PCICMD = %08x\n", pcicmd);
		pr_emerg("BONITO_PCIBADADDR = %08x\n", pcibadaddr);
		pr_emerg("BONITO_PCIMSTAT = %08x\n", pcimstat);
		अवरोध;
	पूर्ण

	die("CoreHi interrupt", regs);
पूर्ण

अटल irqवापस_t corehi_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	corehi_irqdispatch();
	वापस IRQ_HANDLED;
पूर्ण

अटल msc_irqmap_t msc_irqmap[] __initdata = अणु
	अणुMSC01C_INT_TMR,		MSC01_IRQ_EDGE, 0पूर्ण,
	अणुMSC01C_INT_PCI,		MSC01_IRQ_LEVEL, 0पूर्ण,
पूर्ण;
अटल पूर्णांक msc_nr_irqs __initdata = ARRAY_SIZE(msc_irqmap);

अटल msc_irqmap_t msc_eicirqmap[] __initdata = अणु
	अणुMSC01E_INT_SW0,		MSC01_IRQ_LEVEL, 0पूर्ण,
	अणुMSC01E_INT_SW1,		MSC01_IRQ_LEVEL, 0पूर्ण,
	अणुMSC01E_INT_I8259A,		MSC01_IRQ_LEVEL, 0पूर्ण,
	अणुMSC01E_INT_SMI,		MSC01_IRQ_LEVEL, 0पूर्ण,
	अणुMSC01E_INT_COREHI,		MSC01_IRQ_LEVEL, 0पूर्ण,
	अणुMSC01E_INT_CORELO,		MSC01_IRQ_LEVEL, 0पूर्ण,
	अणुMSC01E_INT_TMR,		MSC01_IRQ_EDGE, 0पूर्ण,
	अणुMSC01E_INT_PCI,		MSC01_IRQ_LEVEL, 0पूर्ण,
	अणुMSC01E_INT_PERFCTR,		MSC01_IRQ_LEVEL, 0पूर्ण,
	अणुMSC01E_INT_CPUCTR,		MSC01_IRQ_LEVEL, 0पूर्ण
पूर्ण;

अटल पूर्णांक msc_nr_eicirqs __initdata = ARRAY_SIZE(msc_eicirqmap);

व्योम __init arch_init_irq(व्योम)
अणु
	पूर्णांक corehi_irq;

	/*
	 * Pपुनः_स्मृतिate the i8259's expected virq's here. Since irqchip_init()
	 * will probe the irqchips in hierarchial order, i8259 is probed last.
	 * If anything allocates a virq beक्रमe the i8259 is probed, it will
	 * be given one of the i8259's expected range and consequently setup
	 * of the i8259 will fail.
	 */
	WARN(irq_alloc_descs(I8259A_IRQ_BASE, I8259A_IRQ_BASE,
			    16, numa_node_id()) < 0,
		"Cannot reserve i8259 virqs at IRQ%d\n", I8259A_IRQ_BASE);

	i8259_set_poll(mips_pcibios_iack);
	irqchip_init();

	चयन (mips_revision_sconid) अणु
	हाल MIPS_REVISION_SCON_SOCIT:
	हाल MIPS_REVISION_SCON_ROCIT:
		अगर (cpu_has_veic)
			init_msc_irqs(MIPS_MSC01_IC_REG_BASE,
					MSC01E_INT_BASE, msc_eicirqmap,
					msc_nr_eicirqs);
		अन्यथा
			init_msc_irqs(MIPS_MSC01_IC_REG_BASE,
					MSC01C_INT_BASE, msc_irqmap,
					msc_nr_irqs);
		अवरोध;

	हाल MIPS_REVISION_SCON_SOCITSC:
	हाल MIPS_REVISION_SCON_SOCITSCP:
		अगर (cpu_has_veic)
			init_msc_irqs(MIPS_SOCITSC_IC_REG_BASE,
					MSC01E_INT_BASE, msc_eicirqmap,
					msc_nr_eicirqs);
		अन्यथा
			init_msc_irqs(MIPS_SOCITSC_IC_REG_BASE,
					MSC01C_INT_BASE, msc_irqmap,
					msc_nr_irqs);
	पूर्ण

	अगर (mips_gic_present()) अणु
		corehi_irq = MIPS_CPU_IRQ_BASE + MIPSCPU_INT_COREHI;
	पूर्ण अन्यथा अगर (cpu_has_veic) अणु
		set_vi_handler(MSC01E_INT_COREHI, corehi_irqdispatch);
		corehi_irq = MSC01E_INT_BASE + MSC01E_INT_COREHI;
	पूर्ण अन्यथा अणु
		corehi_irq = MIPS_CPU_IRQ_BASE + MIPSCPU_INT_COREHI;
	पूर्ण

	अगर (request_irq(corehi_irq, corehi_handler, IRQF_NO_THREAD, "CoreHi",
			शून्य))
		pr_err("Failed to request irq %d (CoreHi)\n", corehi_irq);
पूर्ण
