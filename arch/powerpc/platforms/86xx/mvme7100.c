<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Board setup routines क्रम the Emerson/Artesyn MVME7100
 *
 * Copyright 2016 Elettra-Sincrotrone Trieste S.C.p.A.
 *
 * Author: Alessio Igor Bogani <alessio.bogani@elettra.eu>
 *
 * Based on earlier code by:
 *
 *	Ajit Prem <ajit.prem@emerson.com>
 *	Copyright 2008 Emerson
 *
 * USB host fixup is borrowed by:
 *
 *	Martyn Welch <martyn.welch@ge.com>
 *	Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 */

#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc86xx.h"

#घोषणा MVME7100_INTERRUPT_REG_2_OFFSET	0x05
#घोषणा MVME7100_DS1375_MASK		0x40
#घोषणा MVME7100_MAX6649_MASK		0x20
#घोषणा MVME7100_ABORT_MASK		0x10

/*
 * Setup the architecture
 */
अटल व्योम __init mvme7100_setup_arch(व्योम)
अणु
	काष्ठा device_node *bcsr_node;
	व्योम __iomem *mvme7100_regs = शून्य;
	u8 reg;

	अगर (ppc_md.progress)
		ppc_md.progress("mvme7100_setup_arch()", 0);

#अगर_घोषित CONFIG_SMP
	mpc86xx_smp_init();
#पूर्ण_अगर

	fsl_pci_assign_primary();

	/* Remap BCSR रेजिस्टरs */
	bcsr_node = of_find_compatible_node(शून्य, शून्य,
			"artesyn,mvme7100-bcsr");
	अगर (bcsr_node) अणु
		mvme7100_regs = of_iomap(bcsr_node, 0);
		of_node_put(bcsr_node);
	पूर्ण

	अगर (mvme7100_regs) अणु
		/* Disable ds1375, max6649, and पात पूर्णांकerrupts */
		reg = पढ़ोb(mvme7100_regs + MVME7100_INTERRUPT_REG_2_OFFSET);
		reg |= MVME7100_DS1375_MASK | MVME7100_MAX6649_MASK
			| MVME7100_ABORT_MASK;
		ग_लिखोb(reg, mvme7100_regs + MVME7100_INTERRUPT_REG_2_OFFSET);
	पूर्ण अन्यथा
		pr_warn("Unable to map board registers\n");

	pr_info("MVME7100 board from Artesyn\n");
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mvme7100_probe(व्योम)
अणु
	अचिन्हित दीर्घ root = of_get_flat_dt_root();

	वापस of_flat_dt_is_compatible(root, "artesyn,MVME7100");
पूर्ण

अटल व्योम mvme7100_usb_host_fixup(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक val;

	अगर (!machine_is(mvme7100))
		वापस;

	/* Ensure only ports 1 & 2 are enabled */
	pci_पढ़ो_config_dword(pdev, 0xe0, &val);
	pci_ग_लिखो_config_dword(pdev, 0xe0, (val & ~7) | 0x2);

	/* System घड़ी is 48-MHz Oscillator and EHCI Enabled. */
	pci_ग_लिखो_config_dword(pdev, 0xe4, 1 << 5);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NEC, PCI_DEVICE_ID_NEC_USB,
	mvme7100_usb_host_fixup);

machine_arch_initcall(mvme7100, mpc86xx_common_publish_devices);

define_machine(mvme7100) अणु
	.name			= "MVME7100",
	.probe			= mvme7100_probe,
	.setup_arch		= mvme7100_setup_arch,
	.init_IRQ		= mpc86xx_init_irq,
	.get_irq		= mpic_get_irq,
	.समय_init		= mpc86xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
#पूर्ण_अगर
पूर्ण;
