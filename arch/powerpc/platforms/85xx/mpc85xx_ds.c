<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC85xx DS Board Setup
 *
 * Author Xianghua Xiao (x.xiao@मुक्तscale.com)
 * Roy Zang <tie-fei.zang@मुक्तscale.com>
 * 	- Add PCI/PCI Exprees support
 * Copyright 2007 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/swiotlb.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश "smp.h"

#समावेश "mpc85xx.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt, args...) prपूर्णांकk(KERN_ERR "%s: " fmt, __func__, ## args)
#अन्यथा
#घोषणा DBG(fmt, args...)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_I8259
अटल व्योम mpc85xx_8259_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq = i8259_irq();

	अगर (cascade_irq) अणु
		generic_handle_irq(cascade_irq);
	पूर्ण
	chip->irq_eoi(&desc->irq_data);
पूर्ण
#पूर्ण_अगर	/* CONFIG_PPC_I8259 */

व्योम __init mpc85xx_ds_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic;
#अगर_घोषित CONFIG_PPC_I8259
	काष्ठा device_node *np;
	काष्ठा device_node *cascade_node = शून्य;
	पूर्णांक cascade_irq;
#पूर्ण_अगर
	अगर (of_machine_is_compatible("fsl,MPC8572DS-CAMP")) अणु
		mpic = mpic_alloc(शून्य, 0,
			MPIC_NO_RESET |
			MPIC_BIG_ENDIAN |
			MPIC_SINGLE_DEST_CPU,
			0, 256, " OpenPIC  ");
	पूर्ण अन्यथा अणु
		mpic = mpic_alloc(शून्य, 0,
			  MPIC_BIG_ENDIAN |
			  MPIC_SINGLE_DEST_CPU,
			0, 256, " OpenPIC  ");
	पूर्ण

	BUG_ON(mpic == शून्य);
	mpic_init(mpic);

#अगर_घोषित CONFIG_PPC_I8259
	/* Initialize the i8259 controller */
	क्रम_each_node_by_type(np, "interrupt-controller")
	    अगर (of_device_is_compatible(np, "chrp,iic")) अणु
		cascade_node = np;
		अवरोध;
	पूर्ण

	अगर (cascade_node == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "Could not find i8259 PIC\n");
		वापस;
	पूर्ण

	cascade_irq = irq_of_parse_and_map(cascade_node, 0);
	अगर (!cascade_irq) अणु
		prपूर्णांकk(KERN_ERR "Failed to map cascade interrupt\n");
		वापस;
	पूर्ण

	DBG("mpc85xxds: cascade mapped to irq %d\n", cascade_irq);

	i8259_init(cascade_node, 0);
	of_node_put(cascade_node);

	irq_set_chained_handler(cascade_irq, mpc85xx_8259_cascade);
#पूर्ण_अगर	/* CONFIG_PPC_I8259 */
पूर्ण

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक uli_exclude_device(काष्ठा pci_controller *hose,
				u_अक्षर bus, u_अक्षर devfn);

अटल काष्ठा device_node *pci_with_uli;

अटल पूर्णांक mpc85xx_exclude_device(काष्ठा pci_controller *hose,
				   u_अक्षर bus, u_अक्षर devfn)
अणु
	अगर (hose->dn == pci_with_uli)
		वापस uli_exclude_device(hose, bus, devfn);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PCI */

अटल व्योम __init mpc85xx_ds_uli_init(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा device_node *node;

	/* See अगर we have a ULI under the primary */

	node = of_find_node_by_name(शून्य, "uli1575");
	जबतक ((pci_with_uli = of_get_parent(node))) अणु
		of_node_put(node);
		node = pci_with_uli;

		अगर (pci_with_uli == fsl_pci_primary) अणु
			ppc_md.pci_exclude_device = mpc85xx_exclude_device;
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init mpc85xx_ds_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("mpc85xx_ds_setup_arch()", 0);

	swiotlb_detect_4g();
	fsl_pci_assign_primary();
	mpc85xx_ds_uli_init();
	mpc85xx_smp_init();

	prपूर्णांकk("MPC85xx DS board from Freescale Semiconductor\n");
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc8544_ds_probe(व्योम)
अणु
	वापस !!of_machine_is_compatible("MPC8544DS");
पूर्ण

machine_arch_initcall(mpc8544_ds, mpc85xx_common_publish_devices);
machine_arch_initcall(mpc8572_ds, mpc85xx_common_publish_devices);
machine_arch_initcall(p2020_ds, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc8572_ds_probe(व्योम)
अणु
	वापस !!of_machine_is_compatible("fsl,MPC8572DS");
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init p2020_ds_probe(व्योम)
अणु
	वापस !!of_machine_is_compatible("fsl,P2020DS");
पूर्ण

define_machine(mpc8544_ds) अणु
	.name			= "MPC8544 DS",
	.probe			= mpc8544_ds_probe,
	.setup_arch		= mpc85xx_ds_setup_arch,
	.init_IRQ		= mpc85xx_ds_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(mpc8572_ds) अणु
	.name			= "MPC8572 DS",
	.probe			= mpc8572_ds_probe,
	.setup_arch		= mpc85xx_ds_setup_arch,
	.init_IRQ		= mpc85xx_ds_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p2020_ds) अणु
	.name			= "P2020 DS",
	.probe			= p2020_ds_probe,
	.setup_arch		= mpc85xx_ds_setup_arch,
	.init_IRQ		= mpc85xx_ds_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
