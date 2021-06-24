<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * Authors: Kip Walker, PA Semi
 *	    Olof Johansson, PA Semi
 *
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 *
 * Based on arch/घातerpc/platक्रमms/maple/setup.c
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/console.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/debug.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#समावेश "pasemi.h"

/* SDC reset रेजिस्टर, must be pre-mapped at reset समय */
अटल व्योम __iomem *reset_reg;

/* Various error status रेजिस्टरs, must be pre-mapped at MCE समय */

#घोषणा MAX_MCE_REGS	32
काष्ठा mce_regs अणु
	अक्षर *name;
	व्योम __iomem *addr;
पूर्ण;

अटल काष्ठा mce_regs mce_regs[MAX_MCE_REGS];
अटल पूर्णांक num_mce_regs;
अटल पूर्णांक nmi_virq = 0;


अटल व्योम __noवापस pas_restart(अक्षर *cmd)
अणु
	/* Need to put others cpu in hold loop so they're not sleeping */
	smp_send_stop();
	udelay(10000);
	prपूर्णांकk("Restarting...\n");
	जबतक (1)
		out_le32(reset_reg, 0x6000000);
पूर्ण

#अगर_घोषित CONFIG_PPC_PASEMI_NEMO
व्योम pas_shutकरोwn(व्योम)
अणु
	/* Set the PLD bit that makes the SB600 think the घातer button is being pressed */
	व्योम __iomem *pld_map = ioremap(0xf5000000,4096);
	जबतक (1)
		out_8(pld_map+7,0x01);
पूर्ण

/* RTC platक्रमm device काष्ठाure as is not in device tree */
अटल काष्ठा resource rtc_resource[] = अणुअणु
	.name = "rtc",
	.start = 0x70,
	.end = 0x71,
	.flags = IORESOURCE_IO,
पूर्ण, अणु
	.name = "rtc",
	.start = 8,
	.end = 8,
	.flags = IORESOURCE_IRQ,
पूर्णपूर्ण;

अटल अंतरभूत व्योम nemo_init_rtc(व्योम)
अणु
	platक्रमm_device_रेजिस्टर_simple("rtc_cmos", -1, rtc_resource, 2);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम nemo_init_rtc(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल arch_spinlock_t समयbase_lock;
अटल अचिन्हित दीर्घ समयbase;

अटल व्योम pas_give_समयbase(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	hard_irq_disable();
	arch_spin_lock(&समयbase_lock);
	mtspr(SPRN_TBCTL, TBCTL_FREEZE);
	isync();
	समयbase = get_tb();
	arch_spin_unlock(&समयbase_lock);

	जबतक (समयbase)
		barrier();
	mtspr(SPRN_TBCTL, TBCTL_RESTART);
	local_irq_restore(flags);
पूर्ण

अटल व्योम pas_take_समयbase(व्योम)
अणु
	जबतक (!समयbase)
		smp_rmb();

	arch_spin_lock(&समयbase_lock);
	set_tb(समयbase >> 32, समयbase & 0xffffffff);
	समयbase = 0;
	arch_spin_unlock(&समयbase_lock);
पूर्ण

अटल काष्ठा smp_ops_t pas_smp_ops = अणु
	.probe		= smp_mpic_probe,
	.message_pass	= smp_mpic_message_pass,
	.kick_cpu	= smp_generic_kick_cpu,
	.setup_cpu	= smp_mpic_setup_cpu,
	.give_समयbase	= pas_give_समयbase,
	.take_समयbase	= pas_take_समयbase,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम __init pas_setup_arch(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	/* Setup SMP callback */
	smp_ops = &pas_smp_ops;
#पूर्ण_अगर

	/* Remap SDC रेजिस्टर क्रम करोing reset */
	/* XXXOJN This should maybe come out of the device tree */
	reset_reg = ioremap(0xfc101100, 4);
पूर्ण

अटल पूर्णांक __init pas_setup_mce_regs(व्योम)
अणु
	काष्ठा pci_dev *dev;
	पूर्णांक reg;

	/* Remap various SoC status रेजिस्टरs क्रम use by the MCE handler */

	reg = 0;

	dev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa00a, शून्य);
	जबतक (dev && reg < MAX_MCE_REGS) अणु
		mce_regs[reg].name = kaप्र_लिखो(GFP_KERNEL,
						"mc%d_mcdebug_errsta", reg);
		mce_regs[reg].addr = pasemi_pci_अ_लोfgaddr(dev, 0x730);
		dev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa00a, dev);
		reg++;
	पूर्ण

	dev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa001, शून्य);
	अगर (dev && reg+4 < MAX_MCE_REGS) अणु
		mce_regs[reg].name = "iobdbg_IntStatus1";
		mce_regs[reg].addr = pasemi_pci_अ_लोfgaddr(dev, 0x438);
		reg++;
		mce_regs[reg].name = "iobdbg_IOCTbusIntDbgReg";
		mce_regs[reg].addr = pasemi_pci_अ_लोfgaddr(dev, 0x454);
		reg++;
		mce_regs[reg].name = "iobiom_IntStatus";
		mce_regs[reg].addr = pasemi_pci_अ_लोfgaddr(dev, 0xc10);
		reg++;
		mce_regs[reg].name = "iobiom_IntDbgReg";
		mce_regs[reg].addr = pasemi_pci_अ_लोfgaddr(dev, 0xc1c);
		reg++;
	पूर्ण

	dev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa009, शून्य);
	अगर (dev && reg+2 < MAX_MCE_REGS) अणु
		mce_regs[reg].name = "l2csts_IntStatus";
		mce_regs[reg].addr = pasemi_pci_अ_लोfgaddr(dev, 0x200);
		reg++;
		mce_regs[reg].name = "l2csts_Cnt";
		mce_regs[reg].addr = pasemi_pci_अ_लोfgaddr(dev, 0x214);
		reg++;
	पूर्ण

	num_mce_regs = reg;

	वापस 0;
पूर्ण
machine_device_initcall(pasemi, pas_setup_mce_regs);

#अगर_घोषित CONFIG_PPC_PASEMI_NEMO
अटल व्योम sb600_8259_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq = i8259_irq();

	अगर (cascade_irq)
		generic_handle_irq(cascade_irq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल व्योम nemo_init_IRQ(काष्ठा mpic *mpic)
अणु
	काष्ठा device_node *np;
	पूर्णांक gpio_virq;
	/* Connect the SB600's legacy i8259 controller */
	np = of_find_node_by_path("/pxp@0,e0000000");
	i8259_init(np, 0);
	of_node_put(np);

	gpio_virq = irq_create_mapping(शून्य, 3);
	irq_set_irq_type(gpio_virq, IRQ_TYPE_LEVEL_HIGH);
	irq_set_chained_handler(gpio_virq, sb600_8259_cascade);
	mpic_unmask_irq(irq_get_irq_data(gpio_virq));

	irq_set_शेष_host(mpic->irqhost);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम nemo_init_IRQ(काष्ठा mpic *mpic)
अणु
पूर्ण
#पूर्ण_अगर

अटल __init व्योम pas_init_IRQ(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा device_node *root, *mpic_node;
	अचिन्हित दीर्घ खोलोpic_addr;
	स्थिर अचिन्हित पूर्णांक *opprop;
	पूर्णांक naddr, opplen;
	पूर्णांक mpic_flags;
	स्थिर अचिन्हित पूर्णांक *nmiprop;
	काष्ठा mpic *mpic;

	mpic_node = शून्य;

	क्रम_each_node_by_type(np, "interrupt-controller")
		अगर (of_device_is_compatible(np, "open-pic")) अणु
			mpic_node = np;
			अवरोध;
		पूर्ण
	अगर (!mpic_node)
		क्रम_each_node_by_type(np, "open-pic") अणु
			mpic_node = np;
			अवरोध;
		पूर्ण
	अगर (!mpic_node) अणु
		pr_err("Failed to locate the MPIC interrupt controller\n");
		वापस;
	पूर्ण

	/* Find address list in /platक्रमm-खोलो-pic */
	root = of_find_node_by_path("/");
	naddr = of_n_addr_cells(root);
	opprop = of_get_property(root, "platform-open-pic", &opplen);
	अगर (!opprop) अणु
		pr_err("No platform-open-pic property.\n");
		of_node_put(root);
		वापस;
	पूर्ण
	खोलोpic_addr = of_पढ़ो_number(opprop, naddr);
	pr_debug("OpenPIC addr: %lx\n", खोलोpic_addr);

	mpic_flags = MPIC_LARGE_VECTORS | MPIC_NO_BIAS | MPIC_NO_RESET;

	nmiprop = of_get_property(mpic_node, "nmi-source", शून्य);
	अगर (nmiprop)
		mpic_flags |= MPIC_ENABLE_MCK;

	mpic = mpic_alloc(mpic_node, खोलोpic_addr,
			  mpic_flags, 0, 0, "PASEMI-OPIC");
	BUG_ON(!mpic);

	mpic_assign_isu(mpic, 0, mpic->paddr + 0x10000);
	mpic_init(mpic);
	/* The NMI/MCK source needs to be prio 15 */
	अगर (nmiprop) अणु
		nmi_virq = irq_create_mapping(शून्य, *nmiprop);
		mpic_irq_set_priority(nmi_virq, 15);
		irq_set_irq_type(nmi_virq, IRQ_TYPE_EDGE_RISING);
		mpic_unmask_irq(irq_get_irq_data(nmi_virq));
	पूर्ण

	nemo_init_IRQ(mpic);

	of_node_put(mpic_node);
	of_node_put(root);
पूर्ण

अटल व्योम __init pas_progress(अक्षर *s, अचिन्हित लघु hex)
अणु
	prपूर्णांकk("[%04x] : %s\n", hex, s ? s : "");
पूर्ण


अटल पूर्णांक pas_machine_check_handler(काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ srr0, srr1, dsisr;
	पूर्णांक dump_slb = 0;
	पूर्णांक i;

	srr0 = regs->nip;
	srr1 = regs->msr;

	अगर (nmi_virq && mpic_get_mcirq() == nmi_virq) अणु
		pr_err("NMI delivered\n");
		debugger(regs);
		mpic_end_irq(irq_get_irq_data(nmi_virq));
		जाओ out;
	पूर्ण

	dsisr = mfspr(SPRN_DSISR);
	pr_err("Machine Check on CPU %d\n", cpu);
	pr_err("SRR0  0x%016lx SRR1 0x%016lx\n", srr0, srr1);
	pr_err("DSISR 0x%016lx DAR  0x%016lx\n", dsisr, regs->dar);
	pr_err("BER   0x%016lx MER  0x%016lx\n", mfspr(SPRN_PA6T_BER),
		mfspr(SPRN_PA6T_MER));
	pr_err("IER   0x%016lx DER  0x%016lx\n", mfspr(SPRN_PA6T_IER),
		mfspr(SPRN_PA6T_DER));
	pr_err("Cause:\n");

	अगर (srr1 & 0x200000)
		pr_err("Signalled by SDC\n");

	अगर (srr1 & 0x100000) अणु
		pr_err("Load/Store detected error:\n");
		अगर (dsisr & 0x8000)
			pr_err("D-cache ECC double-bit error or bus error\n");
		अगर (dsisr & 0x4000)
			pr_err("LSU snoop response error\n");
		अगर (dsisr & 0x2000) अणु
			pr_err("MMU SLB multi-hit or invalid B field\n");
			dump_slb = 1;
		पूर्ण
		अगर (dsisr & 0x1000)
			pr_err("Recoverable Duptags\n");
		अगर (dsisr & 0x800)
			pr_err("Recoverable D-cache parity error count overflow\n");
		अगर (dsisr & 0x400)
			pr_err("TLB parity error count overflow\n");
	पूर्ण

	अगर (srr1 & 0x80000)
		pr_err("Bus Error\n");

	अगर (srr1 & 0x40000) अणु
		pr_err("I-side SLB multiple hit\n");
		dump_slb = 1;
	पूर्ण

	अगर (srr1 & 0x20000)
		pr_err("I-cache parity error hit\n");

	अगर (num_mce_regs == 0)
		pr_err("No MCE registers mapped yet, can't dump\n");
	अन्यथा
		pr_err("SoC debug registers:\n");

	क्रम (i = 0; i < num_mce_regs; i++)
		pr_err("%s: 0x%08x\n", mce_regs[i].name,
			in_le32(mce_regs[i].addr));

	अगर (dump_slb) अणु
		अचिन्हित दीर्घ e, v;
		पूर्णांक i;

		pr_err("slb contents:\n");
		क्रम (i = 0; i < mmu_slb_size; i++) अणु
			यंत्र अस्थिर("slbmfee  %0,%1" : "=r" (e) : "r" (i));
			यंत्र अस्थिर("slbmfev  %0,%1" : "=r" (v) : "r" (i));
			pr_err("%02d %016lx %016lx\n", i, e, v);
		पूर्ण
	पूर्ण

out:
	/* SRR1[62] is from MSR[62] अगर recoverable, so pass that back */
	वापस !!(srr1 & 0x2);
पूर्ण

अटल स्थिर काष्ठा of_device_id pasemi_bus_ids[] = अणु
	/* Unक्रमtunately needed क्रम legacy firmwares */
	अणु .type = "localbus", पूर्ण,
	अणु .type = "sdc", पूर्ण,
	/* These are the proper entries, which newer firmware uses */
	अणु .compatible = "pasemi,localbus", पूर्ण,
	अणु .compatible = "pasemi,sdc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init pasemi_publish_devices(व्योम)
अणु
	/* Publish OF platक्रमm devices क्रम SDC and other non-PCI devices */
	of_platक्रमm_bus_probe(शून्य, pasemi_bus_ids, शून्य);

	nemo_init_rtc();

	वापस 0;
पूर्ण
machine_device_initcall(pasemi, pasemi_publish_devices);


/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init pas_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("PA6T-1682M") &&
	    !of_machine_is_compatible("pasemi,pwrficient"))
		वापस 0;

#अगर_घोषित CONFIG_PPC_PASEMI_NEMO
	/*
	 * Check क्रम the Nemo motherboard here, अगर we are running on one
	 * change the machine definition to fit
	 */
	अगर (of_machine_is_compatible("pasemi,nemo")) अणु
		pm_घातer_off		= pas_shutकरोwn;
		ppc_md.name		= "A-EON Amigaone X1000";
	पूर्ण
#पूर्ण_अगर

	iommu_init_early_pasemi();

	वापस 1;
पूर्ण

define_machine(pasemi) अणु
	.name			= "PA Semi PWRficient",
	.probe			= pas_probe,
	.setup_arch		= pas_setup_arch,
	.discover_phbs		= pas_pci_init,
	.init_IRQ		= pas_init_IRQ,
	.get_irq		= mpic_get_irq,
	.restart		= pas_restart,
	.get_boot_समय		= pas_get_boot_समय,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= pas_progress,
	.machine_check_exception = pas_machine_check_handler,
पूर्ण;
