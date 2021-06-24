<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/pci.h>
#समावेश <loongson.h>

अटल व्योम pci_fixup_radeon(काष्ठा pci_dev *pdev)
अणु
	काष्ठा resource *res = &pdev->resource[PCI_ROM_RESOURCE];

	अगर (res->start)
		वापस;

	अगर (!loongson_sysconf.vgabios_addr)
		वापस;

	pci_disable_rom(pdev);
	अगर (res->parent)
		release_resource(res);

	res->start = virt_to_phys((व्योम *) loongson_sysconf.vgabios_addr);
	res->end   = res->start + 256*1024 - 1;
	res->flags = IORESOURCE_MEM | IORESOURCE_ROM_SHADOW |
		     IORESOURCE_PCI_FIXED;

	dev_info(&pdev->dev, "BAR %d: assigned %pR for Radeon ROM\n",
		 PCI_ROM_RESOURCE, res);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_ATI, 0x9615,
				PCI_CLASS_DISPLAY_VGA, 8, pci_fixup_radeon);
