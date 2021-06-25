<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/irqकरोमुख्य.h>

/* arch_initcall has too अक्रमom ordering, so call the initializers
   in the right sequence from here. */
अटल __init पूर्णांक pci_arch_init(व्योम)
अणु
	पूर्णांक type, pcbios = 1;

	type = pci_direct_probe();

	अगर (!(pci_probe & PCI_PROBE_NOEARLY))
		pci_mmcfg_early_init();

	अगर (x86_init.pci.arch_init)
		pcbios = x86_init.pci.arch_init();

	/*
	 * Must happen after x86_init.pci.arch_init(). Xen sets up the
	 * x86_init.irqs.create_pci_msi_करोमुख्य there.
	 */
	x86_create_pci_msi_करोमुख्य();

	अगर (!pcbios)
		वापस 0;

	pci_pcbios_init();

	/*
	 * करोn't check क्रम raw_pci_ops here because we want pcbios as last
	 * fallback, yet it's needed to run first to set pcibios_last_bus
	 * in हाल legacy PCI probing is used. otherwise detecting peer busses
	 * fails.
	 */
	pci_direct_init(type);

	अगर (!raw_pci_ops && !raw_pci_ext_ops)
		prपूर्णांकk(KERN_ERR
		"PCI: Fatal: No config space access function found\n");

	dmi_check_pciprobe();

	dmi_check_skip_isa_align();

	वापस 0;
पूर्ण
arch_initcall(pci_arch_init);
