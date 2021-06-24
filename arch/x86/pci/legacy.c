<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * legacy.c - traditional, old school PCI bus probing
 */
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/jailhouse_para.h>
#समावेश <यंत्र/pci_x86.h>

/*
 * Discover reमुख्यing PCI buses in हाल there are peer host bridges.
 * We use the number of last PCI bus provided by the PCI BIOS.
 */
अटल व्योम pcibios_fixup_peer_bridges(व्योम)
अणु
	पूर्णांक n;

	अगर (pcibios_last_bus <= 0 || pcibios_last_bus > 0xff)
		वापस;
	DBG("PCI: Peer bridge fixup\n");

	क्रम (n=0; n <= pcibios_last_bus; n++)
		pcibios_scan_specअगरic_bus(n);
पूर्ण

पूर्णांक __init pci_legacy_init(व्योम)
अणु
	अगर (!raw_pci_ops)
		वापस 1;

	pr_info("PCI: Probing PCI hardware\n");
	pcibios_scan_root(0);
	वापस 0;
पूर्ण

व्योम pcibios_scan_specअगरic_bus(पूर्णांक busn)
अणु
	पूर्णांक stride = jailhouse_paravirt() ? 1 : 8;
	पूर्णांक devfn;
	u32 l;

	अगर (pci_find_bus(0, busn))
		वापस;

	क्रम (devfn = 0; devfn < 256; devfn += stride) अणु
		अगर (!raw_pci_पढ़ो(0, busn, devfn, PCI_VENDOR_ID, 2, &l) &&
		    l != 0x0000 && l != 0xffff) अणु
			DBG("Found device at %02x:%02x [%04x]\n", busn, devfn, l);
			pr_info("PCI: Discovered peer bus %02x\n", busn);
			pcibios_scan_root(busn);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_scan_specअगरic_bus);

अटल पूर्णांक __init pci_subsys_init(व्योम)
अणु
	/*
	 * The init function वापसs an non zero value when
	 * pci_legacy_init should be invoked.
	 */
	अगर (x86_init.pci.init()) अणु
		अगर (pci_legacy_init()) अणु
			pr_info("PCI: System does not support PCI\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	pcibios_fixup_peer_bridges();
	x86_init.pci.init_irq();
	pcibios_init();

	वापस 0;
पूर्ण
subsys_initcall(pci_subsys_init);
