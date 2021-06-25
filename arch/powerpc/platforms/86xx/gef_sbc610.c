<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GE SBC610 board support
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 *
 * Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on: mpc86xx_hpcn.c (MPC86xx HPCN board specअगरic routines)
 * Copyright 2006 Freescale Semiconductor Inc.
 *
 * NEC fixup adapted from arch/mips/pci/fixup-lm2e.c
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/prom.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/udbg.h>

#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/nvram.h>

#समावेश <sysdev/fsl_pci.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/ge/ge_pic.h>

#समावेश "mpc86xx.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG (fmt...) करो अणु prपूर्णांकk(KERN_ERR "SBC610: " fmt); पूर्ण जबतक (0)
#अन्यथा
#घोषणा DBG (fmt...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

व्योम __iomem *sbc610_regs;

अटल व्योम __init gef_sbc610_init_irq(व्योम)
अणु
	काष्ठा device_node *cascade_node = शून्य;

	mpc86xx_init_irq();

	/*
	 * There is a simple पूर्णांकerrupt handler in the मुख्य FPGA, this needs
	 * to be cascaded पूर्णांकo the MPIC
	 */
	cascade_node = of_find_compatible_node(शून्य, शून्य, "gef,fpga-pic");
	अगर (!cascade_node) अणु
		prपूर्णांकk(KERN_WARNING "SBC610: No FPGA PIC\n");
		वापस;
	पूर्ण

	gef_pic_init(cascade_node);
	of_node_put(cascade_node);
पूर्ण

अटल व्योम __init gef_sbc610_setup_arch(व्योम)
अणु
	काष्ठा device_node *regs;

	prपूर्णांकk(KERN_INFO "GE Intelligent Platforms SBC610 6U VPX SBC\n");

#अगर_घोषित CONFIG_SMP
	mpc86xx_smp_init();
#पूर्ण_अगर

	fsl_pci_assign_primary();

	/* Remap basic board रेजिस्टरs */
	regs = of_find_compatible_node(शून्य, शून्य, "gef,fpga-regs");
	अगर (regs) अणु
		sbc610_regs = of_iomap(regs, 0);
		अगर (sbc610_regs == शून्य)
			prपूर्णांकk(KERN_WARNING "Unable to map board registers\n");
		of_node_put(regs);
	पूर्ण

#अगर defined(CONFIG_MMIO_NVRAM)
	mmio_nvram_init();
#पूर्ण_अगर
पूर्ण

/* Return the PCB revision */
अटल अचिन्हित पूर्णांक gef_sbc610_get_pcb_rev(व्योम)
अणु
	अचिन्हित पूर्णांक reg;

	reg = ioपढ़ो32(sbc610_regs);
	वापस (reg >> 8) & 0xff;
पूर्ण

/* Return the board (software) revision */
अटल अचिन्हित पूर्णांक gef_sbc610_get_board_rev(व्योम)
अणु
	अचिन्हित पूर्णांक reg;

	reg = ioपढ़ो32(sbc610_regs);
	वापस (reg >> 16) & 0xff;
पूर्ण

/* Return the FPGA revision */
अटल अचिन्हित पूर्णांक gef_sbc610_get_fpga_rev(व्योम)
अणु
	अचिन्हित पूर्णांक reg;

	reg = ioपढ़ो32(sbc610_regs);
	वापस (reg >> 24) & 0xf;
पूर्ण

अटल व्योम gef_sbc610_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: GE Intelligent Platforms\n");

	seq_म_लिखो(m, "Revision\t: %u%c\n", gef_sbc610_get_pcb_rev(),
		('A' + gef_sbc610_get_board_rev() - 1));
	seq_म_लिखो(m, "FPGA Revision\t: %u\n", gef_sbc610_get_fpga_rev());

	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);
पूर्ण

अटल व्योम gef_sbc610_nec_fixup(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक val;

	/* Do not करो the fixup on other platक्रमms! */
	अगर (!machine_is(gef_sbc610))
		वापस;

	prपूर्णांकk(KERN_INFO "Running NEC uPD720101 Fixup\n");

	/* Ensure ports 1, 2, 3, 4 & 5 are enabled */
	pci_पढ़ो_config_dword(pdev, 0xe0, &val);
	pci_ग_लिखो_config_dword(pdev, 0xe0, (val & ~7) | 0x5);

	/* System घड़ी is 48-MHz Oscillator and EHCI Enabled. */
	pci_ग_लिखो_config_dword(pdev, 0xe4, 1 << 5);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NEC, PCI_DEVICE_ID_NEC_USB,
	gef_sbc610_nec_fixup);

/*
 * Called very early, device-tree isn't unflattened
 *
 * This function is called to determine whether the BSP is compatible with the
 * supplied device-tree, which is assumed to be the correct one क्रम the actual
 * board. It is expected thati, in the future, a kernel may support multiple
 * boards.
 */
अटल पूर्णांक __init gef_sbc610_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("gef,sbc610"))
		वापस 1;

	वापस 0;
पूर्ण

machine_arch_initcall(gef_sbc610, mpc86xx_common_publish_devices);

define_machine(gef_sbc610) अणु
	.name			= "GE SBC610",
	.probe			= gef_sbc610_probe,
	.setup_arch		= gef_sbc610_setup_arch,
	.init_IRQ		= gef_sbc610_init_irq,
	.show_cpuinfo		= gef_sbc610_show_cpuinfo,
	.get_irq		= mpic_get_irq,
	.समय_init		= mpc86xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
#पूर्ण_अगर
पूर्ण;
