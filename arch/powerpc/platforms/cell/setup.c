<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/arch/घातerpc/platक्रमms/cell/cell_setup.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 *  Adapted from 'alpha' version by Gary Thomas
 *  Modअगरied by Cort Dougan (cort@cs.nmt.edu)
 *  Modअगरied by PPC64 Team, IBM Corp
 *  Modअगरied by Cell Team, IBM Deutschland Entwicklung GmbH
 */
#अघोषित DEBUG

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/export.h>
#समावेश <linux/unistd.h>
#समावेश <linux/user.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/console.h>
#समावेश <linux/mutex.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/cell-regs.h>
#समावेश <यंत्र/io-workarounds.h>

#समावेश "cell.h"
#समावेश "interrupt.h"
#समावेश "pervasive.h"
#समावेश "ras.h"

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

अटल व्योम cell_show_cpuinfo(काष्ठा seq_file *m)
अणु
	काष्ठा device_node *root;
	स्थिर अक्षर *model = "";

	root = of_find_node_by_path("/");
	अगर (root)
		model = of_get_property(root, "model", शून्य);
	seq_म_लिखो(m, "machine\t\t: CHRP %s\n", model);
	of_node_put(root);
पूर्ण

अटल व्योम cell_progress(अक्षर *s, अचिन्हित लघु hex)
अणु
	prपूर्णांकk("*** %04x : %s\n", hex, s ? s : "");
पूर्ण

अटल व्योम cell_fixup_pcie_rootcomplex(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose;
	स्थिर अक्षर *s;
	पूर्णांक i;

	अगर (!machine_is(cell))
		वापस;

	/* We're searching क्रम a direct child of the PHB */
	अगर (dev->bus->self != शून्य || dev->devfn != 0)
		वापस;

	hose = pci_bus_to_host(dev->bus);
	अगर (hose == शून्य)
		वापस;

	/* Only on PCIE */
	अगर (!of_device_is_compatible(hose->dn, "pciex"))
		वापस;

	/* And only on axon */
	s = of_get_property(hose->dn, "model", शून्य);
	अगर (!s || म_भेद(s, "Axon") != 0)
		वापस;

	क्रम (i = 0; i < PCI_BRIDGE_RESOURCES; i++) अणु
		dev->resource[i].start = dev->resource[i].end = 0;
		dev->resource[i].flags = 0;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "PCI: Hiding resources on Axon PCIE RC %s\n",
	       pci_name(dev));
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, cell_fixup_pcie_rootcomplex);

अटल पूर्णांक cell_setup_phb(काष्ठा pci_controller *phb)
अणु
	स्थिर अक्षर *model;
	काष्ठा device_node *np;

	पूर्णांक rc = rtas_setup_phb(phb);
	अगर (rc)
		वापस rc;

	phb->controller_ops = cell_pci_controller_ops;

	np = phb->dn;
	model = of_get_property(np, "model", शून्य);
	अगर (model == शून्य || !of_node_name_eq(np, "pci"))
		वापस 0;

	/* Setup workarounds क्रम spider */
	अगर (म_भेद(model, "Spider"))
		वापस 0;

	iowa_रेजिस्टर_bus(phb, &spiderpci_ops, &spiderpci_iowa_init,
				  (व्योम *)SPIDER_PCI_REG_BASE);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cell_bus_ids[] __initस्थिर = अणु
	अणु .type = "soc", पूर्ण,
	अणु .compatible = "soc", पूर्ण,
	अणु .type = "spider", पूर्ण,
	अणु .type = "axon", पूर्ण,
	अणु .type = "plb5", पूर्ण,
	अणु .type = "plb4", पूर्ण,
	अणु .type = "opb", पूर्ण,
	अणु .type = "ebc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init cell_publish_devices(व्योम)
अणु
	काष्ठा device_node *root = of_find_node_by_path("/");
	काष्ठा device_node *np;
	पूर्णांक node;

	/* Publish OF platक्रमm devices क्रम southbridge IOs */
	of_platक्रमm_bus_probe(शून्य, cell_bus_ids, शून्य);

	/* On spider based blades, we need to manually create the OF
	 * platक्रमm devices क्रम the PCI host bridges
	 */
	क्रम_each_child_of_node(root, np) अणु
		अगर (!of_node_is_type(np, "pci") && !of_node_is_type(np, "pciex"))
			जारी;
		of_platक्रमm_device_create(np, शून्य, शून्य);
	पूर्ण

	/* There is no device क्रम the MIC memory controller, thus we create
	 * a platक्रमm device क्रम it to attach the EDAC driver to.
	 */
	क्रम_each_online_node(node) अणु
		अगर (cbe_get_cpu_mic_पंचांग_regs(cbe_node_to_cpu(node)) == शून्य)
			जारी;
		platक्रमm_device_रेजिस्टर_simple("cbe-mic", node, शून्य, 0);
	पूर्ण

	वापस 0;
पूर्ण
machine_subsys_initcall(cell, cell_publish_devices);

अटल व्योम __init mpic_init_IRQ(व्योम)
अणु
	काष्ठा device_node *dn;
	काष्ठा mpic *mpic;

	क्रम_each_node_by_name(dn, "interrupt-controller") अणु
		अगर (!of_device_is_compatible(dn, "CBEA,platform-open-pic"))
			जारी;

		/* The MPIC driver will get everything it needs from the
		 * device-tree, just pass 0 to all arguments
		 */
		mpic = mpic_alloc(dn, 0, MPIC_SECONDARY | MPIC_NO_RESET,
				0, 0, " MPIC     ");
		अगर (mpic == शून्य)
			जारी;
		mpic_init(mpic);
	पूर्ण
पूर्ण


अटल व्योम __init cell_init_irq(व्योम)
अणु
	iic_init_IRQ();
	spider_init_IRQ();
	mpic_init_IRQ();
पूर्ण

अटल व्योम __init cell_set_dabrx(व्योम)
अणु
	mtspr(SPRN_DABRX, DABRX_KERNEL | DABRX_USER);
पूर्ण

अटल व्योम __init cell_setup_arch(व्योम)
अणु
#अगर_घोषित CONFIG_SPU_BASE
	spu_priv1_ops = &spu_priv1_mmio_ops;
	spu_management_ops = &spu_management_of_ops;
#पूर्ण_अगर

	cbe_regs_init();

	cell_set_dabrx();

#अगर_घोषित CONFIG_CBE_RAS
	cbe_ras_init();
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	smp_init_cell();
#पूर्ण_अगर
	/* init to some ~sane value until calibrate_delay() runs */
	loops_per_jअगरfy = 50000000;

	/* Find and initialize PCI host bridges */
	init_pci_config_tokens();

	cbe_pervasive_init();

	mmio_nvram_init();
पूर्ण

अटल पूर्णांक __init cell_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("IBM,CBEA") &&
	    !of_machine_is_compatible("IBM,CPBW-1.0"))
		वापस 0;

	pm_घातer_off = rtas_घातer_off;

	वापस 1;
पूर्ण

define_machine(cell) अणु
	.name			= "Cell",
	.probe			= cell_probe,
	.setup_arch		= cell_setup_arch,
	.show_cpuinfo		= cell_show_cpuinfo,
	.restart		= rtas_restart,
	.halt			= rtas_halt,
	.get_boot_समय		= rtas_get_boot_समय,
	.get_rtc_समय		= rtas_get_rtc_समय,
	.set_rtc_समय		= rtas_set_rtc_समय,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= cell_progress,
	.init_IRQ       	= cell_init_irq,
	.pci_setup_phb		= cell_setup_phb,
पूर्ण;

काष्ठा pci_controller_ops cell_pci_controller_ops;
