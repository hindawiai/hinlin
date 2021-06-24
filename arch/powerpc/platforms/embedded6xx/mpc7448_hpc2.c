<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mpc7448_hpc2.c
 *
 * Board setup routines क्रम the Freescale mpc7448hpc2(taiga) platक्रमm
 *
 * Author: Jacob Pan
 *	 jacob.pan@मुक्तscale.com
 * Author: Xianghua Xiao
 *       x.xiao@मुक्तscale.com
 * Maपूर्णांकainer: Roy Zang <tie-fei.zang@मुक्तscale.com>
 * 	Add Flat Device Tree support fot mpc7448hpc2 board
 *
 * Copyright 2004-2006 Freescale Semiconductor, Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/console.h>
#समावेश <linux/extable.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_core.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/tsi108.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/reg.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/tsi108_pci.h>
#समावेश <यंत्र/tsi108_irq.h>
#समावेश <यंत्र/mpic.h>

#अघोषित DEBUG
#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) करो अणु prपूर्णांकk(fmt); पूर्ण जबतक(0)
#अन्यथा
#घोषणा DBG(fmt...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#घोषणा MPC7448HPC2_PCI_CFG_PHYS 0xfb000000

पूर्णांक mpc7448_hpc2_exclude_device(काष्ठा pci_controller *hose,
				u_अक्षर bus, u_अक्षर devfn)
अणु
	अगर (bus == 0 && PCI_SLOT(devfn) == 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अन्यथा
		वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल व्योम __init mpc7448_hpc2_setup_pci(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा device_node *np;
	अगर (ppc_md.progress)
		ppc_md.progress("mpc7448_hpc2_setup_pci():set_bridge", 0);

	/* setup PCI host bridge */
	क्रम_each_compatible_node(np, "pci", "tsi108-pci")
		tsi108_setup_pci(np, MPC7448HPC2_PCI_CFG_PHYS, 0);

	ppc_md.pci_exclude_device = mpc7448_hpc2_exclude_device;
	अगर (ppc_md.progress)
		ppc_md.progress("tsi108: resources set", 0x100);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init mpc7448_hpc2_setup_arch(व्योम)
अणु
	tsi108_csr_vir_base = get_vir_csrbase();

	prपूर्णांकk(KERN_INFO "MPC7448HPC2 (TAIGA) Platform\n");
	prपूर्णांकk(KERN_INFO
	       "Jointly ported by Freescale and Tundra Semiconductor\n");
	prपूर्णांकk(KERN_INFO
	       "Enabling L2 cache then enabling the HID0 prefetch engine.\n");
पूर्ण

/*
 * Interrupt setup and service.  Interrupts on the mpc7448_hpc2 come
 * from the four बाह्यal INT pins, PCI पूर्णांकerrupts are routed via
 * PCI पूर्णांकerrupt control रेजिस्टरs, it generates पूर्णांकernal IRQ23
 *
 * Interrupt routing on the Taiga Board:
 * TSI108:PB_INT[0] -> CPU0:INT#
 * TSI108:PB_INT[1] -> CPU0:MCP#
 * TSI108:PB_INT[2] -> N/C
 * TSI108:PB_INT[3] -> N/C
 */
अटल व्योम __init mpc7448_hpc2_init_IRQ(व्योम)
अणु
	काष्ठा mpic *mpic;
#अगर_घोषित CONFIG_PCI
	अचिन्हित पूर्णांक cascade_pci_irq;
	काष्ठा device_node *tsi_pci;
	काष्ठा device_node *cascade_node = शून्य;
#पूर्ण_अगर

	mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
			MPIC_SPV_EOI | MPIC_NO_PTHROU_DIS | MPIC_REGSET_TSI108,
			24, 0,
			"Tsi108_PIC");

	BUG_ON(mpic == शून्य);

	mpic_assign_isu(mpic, 0, mpic->paddr + 0x100);

	mpic_init(mpic);

#अगर_घोषित CONFIG_PCI
	tsi_pci = of_find_node_by_type(शून्य, "pci");
	अगर (tsi_pci == शून्य) अणु
		prपूर्णांकk("%s: No tsi108 pci node found !\n", __func__);
		वापस;
	पूर्ण
	cascade_node = of_find_node_by_type(शून्य, "pic-router");
	अगर (cascade_node == शून्य) अणु
		prपूर्णांकk("%s: No tsi108 pci cascade node found !\n", __func__);
		वापस;
	पूर्ण

	cascade_pci_irq = irq_of_parse_and_map(tsi_pci, 0);
	DBG("%s: tsi108 cascade_pci_irq = 0x%x\n", __func__,
	    (u32) cascade_pci_irq);
	tsi108_pci_पूर्णांक_init(cascade_node);
	irq_set_handler_data(cascade_pci_irq, mpic);
	irq_set_chained_handler(cascade_pci_irq, tsi108_irq_cascade);
#पूर्ण_अगर
	/* Configure MPIC outमाला_दो to CPU0 */
	tsi108_ग_लिखो_reg(TSI108_MPIC_OFFSET + 0x30c, 0);
पूर्ण

व्योम mpc7448_hpc2_show_cpuinfo(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "vendor\t\t: Freescale Semiconductor\n");
पूर्ण

अटल व्योम __noवापस mpc7448_hpc2_restart(अक्षर *cmd)
अणु
	local_irq_disable();

	/* Set exception prefix high - to the firmware */
	mपंचांगsr(mfmsr() | MSR_IP);
	isync();

	क्रम (;;) ;		/* Spin until reset happens */
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc7448_hpc2_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("mpc74xx"))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक mpc7448_machine_check_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *entry;

	/* Are we prepared to handle this fault */
	अगर ((entry = search_exception_tables(regs->nip)) != शून्य) अणु
		tsi108_clear_pci_cfg_error();
		regs->msr |= MSR_RI;
		regs->nip = extable_fixup(entry);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

define_machine(mpc7448_hpc2)अणु
	.name 			= "MPC7448 HPC2",
	.probe 			= mpc7448_hpc2_probe,
	.setup_arch 		= mpc7448_hpc2_setup_arch,
	.discover_phbs		= mpc7448_hpc2_setup_pci,
	.init_IRQ 		= mpc7448_hpc2_init_IRQ,
	.show_cpuinfo 		= mpc7448_hpc2_show_cpuinfo,
	.get_irq 		= mpic_get_irq,
	.restart 		= mpc7448_hpc2_restart,
	.calibrate_decr 	= generic_calibrate_decr,
	.machine_check_exception= mpc7448_machine_check_exception,
	.progress 		= udbg_progress,
पूर्ण;
