<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Board setup routines क्रम the IBM 750GX/CL platक्रमm w/ TSI10x bridge
 *
 * Copyright 2007 IBM Corporation
 *
 * Stephen Winiecki <stevewin@us.ibm.com>
 * Josh Boyer <jwboyer@linux.vnet.ibm.com>
 *
 * Based on code from mpc7448_hpc2.c
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/extable.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/tsi108.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/reg.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/tsi108_irq.h>
#समावेश <यंत्र/tsi108_pci.h>
#समावेश <यंत्र/mpic.h>

#अघोषित DEBUG

#घोषणा HOLLY_PCI_CFG_PHYS 0x7c000000

अटल पूर्णांक holly_exclude_device(काष्ठा pci_controller *hose, u_अक्षर bus,
				u_अक्षर devfn)
अणु
	अगर (bus == 0 && PCI_SLOT(devfn) == 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अन्यथा
		वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल व्योम holly_remap_bridge(व्योम)
अणु
	u32 lut_val, lut_addr;
	पूर्णांक i;

	prपूर्णांकk(KERN_INFO "Remapping PCI bridge\n");

	/* Re-init the PCI bridge and LUT रेजिस्टरs to have mappings that करोn't
	 * rely on PIBS
	 */
	lut_addr = 0x900;
	क्रम (i = 0; i < 31; i++) अणु
		tsi108_ग_लिखो_reg(TSI108_PB_OFFSET + lut_addr, 0x00000201);
		lut_addr += 4;
		tsi108_ग_लिखो_reg(TSI108_PB_OFFSET + lut_addr, 0x0);
		lut_addr += 4;
	पूर्ण

	/* Reserve the last LUT entry क्रम PCI I/O space */
	tsi108_ग_लिखो_reg(TSI108_PB_OFFSET + lut_addr, 0x00000241);
	lut_addr += 4;
	tsi108_ग_लिखो_reg(TSI108_PB_OFFSET + lut_addr, 0x0);

	/* Map PCI I/O space */
	tsi108_ग_लिखो_reg(TSI108_PCI_PFAB_IO_UPPER, 0x0);
	tsi108_ग_लिखो_reg(TSI108_PCI_PFAB_IO, 0x1);

	/* Map PCI CFG space */
	tsi108_ग_लिखो_reg(TSI108_PCI_PFAB_BAR0_UPPER, 0x0);
	tsi108_ग_लिखो_reg(TSI108_PCI_PFAB_BAR0, 0x7c000000 | 0x01);

	/* We करोn't need MEM32 and PRM remapping so disable them */
	tsi108_ग_लिखो_reg(TSI108_PCI_PFAB_MEM32, 0x0);
	tsi108_ग_लिखो_reg(TSI108_PCI_PFAB_PFM3, 0x0);
	tsi108_ग_लिखो_reg(TSI108_PCI_PFAB_PFM4, 0x0);

	/* Set P2O_BAR0 */
	tsi108_ग_लिखो_reg(TSI108_PCI_P2O_BAR0_UPPER, 0x0);
	tsi108_ग_लिखो_reg(TSI108_PCI_P2O_BAR0, 0xc0000000);

	/* Init the PCI LUTs to करो no remapping */
	lut_addr = 0x500;
	lut_val = 0x00000002;

	क्रम (i = 0; i < 32; i++) अणु
		tsi108_ग_लिखो_reg(TSI108_PCI_OFFSET + lut_addr, lut_val);
		lut_addr += 4;
		tsi108_ग_लिखो_reg(TSI108_PCI_OFFSET + lut_addr, 0x40000000);
		lut_addr += 4;
		lut_val += 0x02000000;
	पूर्ण
	tsi108_ग_लिखो_reg(TSI108_PCI_P2O_PAGE_SIZES, 0x00007900);

	/* Set 64-bit PCI bus address क्रम प्रणाली memory */
	tsi108_ग_लिखो_reg(TSI108_PCI_P2O_BAR2_UPPER, 0x0);
	tsi108_ग_लिखो_reg(TSI108_PCI_P2O_BAR2, 0x0);
पूर्ण

अटल व्योम __init holly_init_pci(व्योम)
अणु
	काष्ठा device_node *np;

	अगर (ppc_md.progress)
		ppc_md.progress("holly_setup_arch():set_bridge", 0);

	/* setup PCI host bridge */
	holly_remap_bridge();

	np = of_find_node_by_type(शून्य, "pci");
	अगर (np)
		tsi108_setup_pci(np, HOLLY_PCI_CFG_PHYS, 1);

	ppc_md.pci_exclude_device = holly_exclude_device;
	अगर (ppc_md.progress)
		ppc_md.progress("tsi108: resources set", 0x100);
पूर्ण

अटल व्योम __init holly_setup_arch(व्योम)
अणु
	tsi108_csr_vir_base = get_vir_csrbase();

	prपूर्णांकk(KERN_INFO "PPC750GX/CL Platform\n");
पूर्ण

/*
 * Interrupt setup and service.  Interrupts on the holly come
 * from the four बाह्यal INT pins, PCI पूर्णांकerrupts are routed via
 * PCI पूर्णांकerrupt control रेजिस्टरs, it generates पूर्णांकernal IRQ23
 *
 * Interrupt routing on the Holly Board:
 * TSI108:PB_INT[0] -> CPU0:INT#
 * TSI108:PB_INT[1] -> CPU0:MCP#
 * TSI108:PB_INT[2] -> N/C
 * TSI108:PB_INT[3] -> N/C
 */
अटल व्योम __init holly_init_IRQ(व्योम)
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
		prपूर्णांकk(KERN_ERR "%s: No tsi108 pci node found !\n", __func__);
		वापस;
	पूर्ण

	cascade_node = of_find_node_by_type(शून्य, "pic-router");
	अगर (cascade_node == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: No tsi108 pci cascade node found !\n", __func__);
		वापस;
	पूर्ण

	cascade_pci_irq = irq_of_parse_and_map(tsi_pci, 0);
	pr_debug("%s: tsi108 cascade_pci_irq = 0x%x\n", __func__, (u32) cascade_pci_irq);
	tsi108_pci_पूर्णांक_init(cascade_node);
	irq_set_handler_data(cascade_pci_irq, mpic);
	irq_set_chained_handler(cascade_pci_irq, tsi108_irq_cascade);
#पूर्ण_अगर
	/* Configure MPIC outमाला_दो to CPU0 */
	tsi108_ग_लिखो_reg(TSI108_MPIC_OFFSET + 0x30c, 0);
पूर्ण

अटल व्योम holly_show_cpuinfo(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "vendor\t\t: IBM\n");
	seq_म_लिखो(m, "machine\t\t: PPC750 GX/CL\n");
पूर्ण

अटल व्योम __noवापस holly_restart(अक्षर *cmd)
अणु
	__be32 __iomem *ocn_bar1 = शून्य;
	अचिन्हित दीर्घ bar;
	काष्ठा device_node *bridge = शून्य;
	स्थिर व्योम *prop;
	पूर्णांक size;
	phys_addr_t addr = 0xc0000000;

	local_irq_disable();

	bridge = of_find_node_by_type(शून्य, "tsi-bridge");
	अगर (bridge) अणु
		prop = of_get_property(bridge, "reg", &size);
		addr = of_translate_address(bridge, prop);
	पूर्ण
	addr += (TSI108_PB_OFFSET + 0x414);

	ocn_bar1 = ioremap(addr, 0x4);

	/* Turn on the BOOT bit so the addresses are correctly
	 * routed to the HLP पूर्णांकerface */
	bar = ioपढ़ो32be(ocn_bar1);
	bar |= 2;
	ioग_लिखो32be(bar, ocn_bar1);
	iosync();

	/* Set SRR0 to the reset vector and turn on MSR_IP */
	mtspr(SPRN_SRR0, 0xfff00100);
	mtspr(SPRN_SRR1, MSR_IP);

	/* Do an rfi to jump back to firmware.  Somewhat evil,
	 * but it works
	 */
	__यंत्र__ __अस्थिर__("rfi" : : : "memory");

	/* Spin until reset happens.  Shouldn't really get here */
	क्रम (;;) ;
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init holly_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("ibm,holly"))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक ppc750_machine_check_exception(काष्ठा pt_regs *regs)
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

define_machine(holly)अणु
	.name                   	= "PPC750 GX/CL TSI",
	.probe                  	= holly_probe,
	.setup_arch             	= holly_setup_arch,
	.discover_phbs			= holly_init_pci,
	.init_IRQ               	= holly_init_IRQ,
	.show_cpuinfo           	= holly_show_cpuinfo,
	.get_irq                	= mpic_get_irq,
	.restart                	= holly_restart,
	.calibrate_decr         	= generic_calibrate_decr,
	.machine_check_exception	= ppc750_machine_check_exception,
	.progress               	= udbg_progress,
पूर्ण;
