<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Exceptions क्रम specअगरic devices. Usually work-arounds क्रम fatal design flaws.
 * Derived from fixup.c of i386 tree.
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/vgaarb.h>
#समावेश <linux/screen_info.h>
#समावेश <यंत्र/uv/uv.h>

/*
 * Fixup to mark boot BIOS video selected by BIOS beक्रमe it changes
 *
 * From inक्रमmation provided by "Jon Smirl" <jonsmirl@gmail.com>
 *
 * The standard boot ROM sequence क्रम an x86 machine uses the BIOS
 * to select an initial video card क्रम boot display. This boot video
 * card will have its BIOS copied to 0xC0000 in प्रणाली RAM.
 * IORESOURCE_ROM_SHADOW is used to associate the boot video
 * card with this copy. On laptops this copy has to be used since
 * the मुख्य ROM may be compressed or combined with another image.
 * See pci_map_rom() क्रम use of this flag. Beक्रमe marking the device
 * with IORESOURCE_ROM_SHADOW check अगर a vga_शेष_device is alपढ़ोy set
 * by either arch code or vga-arbitration; अगर so only apply the fixup to this
 * alपढ़ोy-determined primary video card.
 */

अटल व्योम pci_fixup_video(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *bridge;
	काष्ठा pci_bus *bus;
	u16 config;
	काष्ठा resource *res;

	अगर (is_uv_प्रणाली())
		वापस;
	/* Maybe, this machine supports legacy memory map. */

	/* Is VGA routed to us? */
	bus = pdev->bus;
	जबतक (bus) अणु
		bridge = bus->self;

		/*
		 * From inक्रमmation provided by
		 * "David Miller" <davem@davemloft.net>
		 * The bridge control रेजिस्टर is valid क्रम PCI header
		 * type BRIDGE, or CARDBUS. Host to PCI controllers use
		 * PCI header type NORMAL.
		 */
		अगर (bridge && (pci_is_bridge(bridge))) अणु
			pci_पढ़ो_config_word(bridge, PCI_BRIDGE_CONTROL,
						&config);
			अगर (!(config & PCI_BRIDGE_CTL_VGA))
				वापस;
		पूर्ण
		bus = bus->parent;
	पूर्ण
	अगर (!vga_शेष_device() || pdev == vga_शेष_device()) अणु
		pci_पढ़ो_config_word(pdev, PCI_COMMAND, &config);
		अगर (config & (PCI_COMMAND_IO | PCI_COMMAND_MEMORY)) अणु
			res = &pdev->resource[PCI_ROM_RESOURCE];

			pci_disable_rom(pdev);
			अगर (res->parent)
				release_resource(res);

			res->start = 0xC0000;
			res->end = res->start + 0x20000 - 1;
			res->flags = IORESOURCE_MEM | IORESOURCE_ROM_SHADOW |
				     IORESOURCE_PCI_FIXED;
			dev_info(&pdev->dev, "Video device with shadowed ROM at %pR\n",
				 res);
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_ANY_ID, PCI_ANY_ID,
				PCI_CLASS_DISPLAY_VGA, 8, pci_fixup_video);
