<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Exceptions क्रम specअगरic devices. Usually work-arounds क्रम fatal design flaws.
 */

#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pci.h>
#समावेश <linux/vgaarb.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/pci_x86.h>

अटल व्योम pci_fixup_i450nx(काष्ठा pci_dev *d)
अणु
	/*
	 * i450NX -- Find and scan all secondary buses on all PXB's.
	 */
	पूर्णांक pxb, reg;
	u8 busno, suba, subb;

	dev_warn(&d->dev, "Searching for i450NX host bridges\n");
	reg = 0xd0;
	क्रम(pxb = 0; pxb < 2; pxb++) अणु
		pci_पढ़ो_config_byte(d, reg++, &busno);
		pci_पढ़ो_config_byte(d, reg++, &suba);
		pci_पढ़ो_config_byte(d, reg++, &subb);
		dev_dbg(&d->dev, "i450NX PXB %d: %02x/%02x/%02x\n", pxb, busno,
			suba, subb);
		अगर (busno)
			pcibios_scan_root(busno);	/* Bus A */
		अगर (suba < subb)
			pcibios_scan_root(suba+1);	/* Bus B */
	पूर्ण
	pcibios_last_bus = -1;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82451NX, pci_fixup_i450nx);

अटल व्योम pci_fixup_i450gx(काष्ठा pci_dev *d)
अणु
	/*
	 * i450GX and i450KX -- Find and scan all secondary buses.
	 * (called separately क्रम each PCI bridge found)
	 */
	u8 busno;
	pci_पढ़ो_config_byte(d, 0x4a, &busno);
	dev_info(&d->dev, "i440KX/GX host bridge; secondary bus %02x\n", busno);
	pcibios_scan_root(busno);
	pcibios_last_bus = -1;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82454GX, pci_fixup_i450gx);

अटल व्योम pci_fixup_umc_ide(काष्ठा pci_dev *d)
अणु
	/*
	 * UM8886BF IDE controller sets region type bits incorrectly,
	 * thereक्रमe they look like memory despite of them being I/O.
	 */
	पूर्णांक i;

	dev_warn(&d->dev, "Fixing base address flags\n");
	क्रम(i = 0; i < 4; i++)
		d->resource[i].flags |= PCI_BASE_ADDRESS_SPACE_IO;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_UMC, PCI_DEVICE_ID_UMC_UM8886BF, pci_fixup_umc_ide);

अटल व्योम pci_fixup_latency(काष्ठा pci_dev *d)
अणु
	/*
	 *  SiS 5597 and 5598 chipsets require latency समयr set to
	 *  at most 32 to aव्योम lockups.
	 */
	dev_dbg(&d->dev, "Setting max latency to 32\n");
	pcibios_max_latency = 32;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_5597, pci_fixup_latency);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_5598, pci_fixup_latency);

अटल व्योम pci_fixup_piix4_acpi(काष्ठा pci_dev *d)
अणु
	/*
	 * PIIX4 ACPI device: hardwired IRQ9
	 */
	d->irq = 9;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371AB_3, pci_fixup_piix4_acpi);

/*
 * Addresses issues with problems in the memory ग_लिखो queue समयr in
 * certain VIA Northbridges.  This bugfix is per VIA's specअगरications,
 * except क्रम the KL133/KM133: clearing bit 5 on those Northbridges seems
 * to trigger a bug in its पूर्णांकegrated ProSavage video card, which
 * causes screen corruption.  We only clear bits 6 and 7 क्रम that chipset,
 * until VIA can provide us with definitive inक्रमmation on why screen
 * corruption occurs, and what exactly those bits करो.
 *
 * VIA 8363,8622,8361 Northbridges:
 *  - bits  5, 6, 7 at offset 0x55 need to be turned off
 * VIA 8367 (KT266x) Northbridges:
 *  - bits  5, 6, 7 at offset 0x95 need to be turned off
 * VIA 8363 rev 0x81/0x84 (KL133/KM133) Northbridges:
 *  - bits     6, 7 at offset 0x55 need to be turned off
 */

#घोषणा VIA_8363_KL133_REVISION_ID 0x81
#घोषणा VIA_8363_KM133_REVISION_ID 0x84

अटल व्योम pci_fixup_via_northbridge_bug(काष्ठा pci_dev *d)
अणु
	u8 v;
	पूर्णांक where = 0x55;
	पूर्णांक mask = 0x1f; /* clear bits 5, 6, 7 by शेष */

	अगर (d->device == PCI_DEVICE_ID_VIA_8367_0) अणु
		/* fix pci bus latency issues resulted by NB bios error
		   it appears on bug मुक्त^Wreduced kt266x's bios क्रमces
		   NB latency to zero */
		pci_ग_लिखो_config_byte(d, PCI_LATENCY_TIMER, 0);

		where = 0x95; /* the memory ग_लिखो queue समयr रेजिस्टर is
				dअगरferent क्रम the KT266x's: 0x95 not 0x55 */
	पूर्ण अन्यथा अगर (d->device == PCI_DEVICE_ID_VIA_8363_0 &&
			(d->revision == VIA_8363_KL133_REVISION_ID ||
			d->revision == VIA_8363_KM133_REVISION_ID)) अणु
			mask = 0x3f; /* clear only bits 6 and 7; clearing bit 5
					causes screen corruption on the KL133/KM133 */
	पूर्ण

	pci_पढ़ो_config_byte(d, where, &v);
	अगर (v & ~mask) अणु
		dev_warn(&d->dev, "Disabling VIA memory write queue (PCI ID %04x, rev %02x): [%02x] %02x & %02x -> %02x\n", \
			d->device, d->revision, where, v, mask, v & mask);
		v &= mask;
		pci_ग_लिखो_config_byte(d, where, v);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8363_0, pci_fixup_via_northbridge_bug);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8622, pci_fixup_via_northbridge_bug);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8361, pci_fixup_via_northbridge_bug);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8367_0, pci_fixup_via_northbridge_bug);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8363_0, pci_fixup_via_northbridge_bug);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8622, pci_fixup_via_northbridge_bug);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8361, pci_fixup_via_northbridge_bug);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8367_0, pci_fixup_via_northbridge_bug);

/*
 * For some reasons Intel decided that certain parts of their
 * 815, 845 and some other chipsets must look like PCI-to-PCI bridges
 * जबतक they are obviously not. The 82801 family (AA, AB, BAM/CAM,
 * BA/CA/DB and E) PCI bridges are actually HUB-to-PCI ones, according
 * to Intel terminology. These devices करो क्रमward all addresses from
 * प्रणाली to PCI bus no matter what are their winकरोw settings, so they are
 * "transparent" (or subtractive decoding) from programmers poपूर्णांक of view.
 */
अटल व्योम pci_fixup_transparent_bridge(काष्ठा pci_dev *dev)
अणु
	अगर ((dev->device & 0xff00) == 0x2400)
		dev->transparent = 1;
पूर्ण
DECLARE_PCI_FIXUP_CLASS_HEADER(PCI_VENDOR_ID_INTEL, PCI_ANY_ID,
			 PCI_CLASS_BRIDGE_PCI, 8, pci_fixup_transparent_bridge);

/*
 * Fixup क्रम C1 Halt Disconnect problem on nForce2 प्रणालीs.
 *
 * From inक्रमmation provided by "Allen Martin" <AMartin@nvidia.com>:
 *
 * A hang is caused when the CPU generates a very fast CONNECT/HALT cycle
 * sequence.  Workaround is to set the SYSTEM_IDLE_TIMEOUT to 80 ns.
 * This allows the state-machine and समयr to वापस to a proper state within
 * 80 ns of the CONNECT and probe appearing together.  Since the CPU will not
 * issue another HALT within 80 ns of the initial HALT, the failure condition
 * is aव्योमed.
 */
अटल व्योम pci_fixup_nक्रमce2(काष्ठा pci_dev *dev)
अणु
	u32 val;

	/*
	 * Chip  Old value   New value
	 * C17   0x1F0FFF01  0x1F01FF01
	 * C18D  0x9F0FFF01  0x9F01FF01
	 *
	 * Northbridge chip version may be determined by
	 * पढ़ोing the PCI revision ID (0xC1 or greater is C18D).
	 */
	pci_पढ़ो_config_dword(dev, 0x6c, &val);

	/*
	 * Apply fixup अगर needed, but करोn't touch disconnect state
	 */
	अगर ((val & 0x00FF0000) != 0x00010000) अणु
		dev_warn(&dev->dev, "nForce2 C1 Halt Disconnect fixup\n");
		pci_ग_लिखो_config_dword(dev, 0x6c, (val & 0xFF00FFFF) | 0x00010000);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE2, pci_fixup_nक्रमce2);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE2, pci_fixup_nक्रमce2);

/* Max PCI Express root ports */
#घोषणा MAX_PCIEROOT	6
अटल पूर्णांक quirk_aspm_offset[MAX_PCIEROOT << 3];

#घोषणा GET_INDEX(a, b) ((((a) - PCI_DEVICE_ID_INTEL_MCH_PA) << 3) + ((b) & 7))

अटल पूर्णांक quirk_pcie_aspm_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	वापस raw_pci_पढ़ो(pci_करोमुख्य_nr(bus), bus->number,
						devfn, where, size, value);
पूर्ण

/*
 * Replace the original pci bus ops क्रम ग_लिखो with a new one that will filter
 * the request to insure ASPM cannot be enabled.
 */
अटल पूर्णांक quirk_pcie_aspm_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 value)
अणु
	u8 offset;

	offset = quirk_aspm_offset[GET_INDEX(bus->self->device, devfn)];

	अगर ((offset) && (where == offset))
		value = value & ~PCI_EXP_LNKCTL_ASPMC;

	वापस raw_pci_ग_लिखो(pci_करोमुख्य_nr(bus), bus->number,
						devfn, where, size, value);
पूर्ण

अटल काष्ठा pci_ops quirk_pcie_aspm_ops = अणु
	.पढ़ो = quirk_pcie_aspm_पढ़ो,
	.ग_लिखो = quirk_pcie_aspm_ग_लिखो,
पूर्ण;

/*
 * Prevents PCI Express ASPM (Active State Power Management) being enabled.
 *
 * Save the रेजिस्टर offset, where the ASPM control bits are located,
 * क्रम each PCI Express device that is in the device list of
 * the root port in an array क्रम fast indexing. Replace the bus ops
 * with the modअगरied one.
 */
अटल व्योम pcie_rootport_aspm_quirk(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा pci_bus  *pbus;
	काष्ठा pci_dev *dev;

	अगर ((pbus = pdev->subordinate) == शून्य)
		वापस;

	/*
	 * Check अगर the DID of pdev matches one of the six root ports. This
	 * check is needed in the हाल this function is called directly by the
	 * hot-plug driver.
	 */
	अगर ((pdev->device < PCI_DEVICE_ID_INTEL_MCH_PA) ||
	    (pdev->device > PCI_DEVICE_ID_INTEL_MCH_PC1))
		वापस;

	अगर (list_empty(&pbus->devices)) अणु
		/*
		 * If no device is attached to the root port at घातer-up or
		 * after hot-हटाओ, the pbus->devices is empty and this code
		 * will set the offsets to zero and the bus ops to parent's bus
		 * ops, which is unmodअगरied.
		 */
		क्रम (i = GET_INDEX(pdev->device, 0); i <= GET_INDEX(pdev->device, 7); ++i)
			quirk_aspm_offset[i] = 0;

		pci_bus_set_ops(pbus, pbus->parent->ops);
	पूर्ण अन्यथा अणु
		/*
		 * If devices are attached to the root port at घातer-up or
		 * after hot-add, the code loops through the device list of
		 * each root port to save the रेजिस्टर offsets and replace the
		 * bus ops.
		 */
		list_क्रम_each_entry(dev, &pbus->devices, bus_list)
			/* There are 0 to 8 devices attached to this bus */
			quirk_aspm_offset[GET_INDEX(pdev->device, dev->devfn)] =
				dev->pcie_cap + PCI_EXP_LNKCTL;

		pci_bus_set_ops(pbus, &quirk_pcie_aspm_ops);
		dev_info(&pbus->dev, "writes to ASPM control bits will be ignored\n");
	पूर्ण

पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_MCH_PA,	pcie_rootport_aspm_quirk);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_MCH_PA1,	pcie_rootport_aspm_quirk);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_MCH_PB,	pcie_rootport_aspm_quirk);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_MCH_PB1,	pcie_rootport_aspm_quirk);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_MCH_PC,	pcie_rootport_aspm_quirk);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_MCH_PC1,	pcie_rootport_aspm_quirk);

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


अटल स्थिर काष्ठा dmi_प्रणाली_id msi_k8t_dmi_table[] = अणु
	अणु
		.ident = "MSI-K8T-Neo2Fir",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MSI"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MS-6702E"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * The AMD-Athlon64 board MSI "K8T Neo2-FIR" disables the onboard sound
 * card अगर a PCI-soundcard is added.
 *
 * The BIOS only gives options "DISABLED" and "AUTO". This code sets
 * the corresponding रेजिस्टर-value to enable the soundcard.
 *
 * The soundcard is only enabled, अगर the मुख्यboard is identअगरied
 * via DMI-tables and the soundcard is detected to be off.
 */
अटल व्योम pci_fixup_msi_k8t_onboard_sound(काष्ठा pci_dev *dev)
अणु
	अचिन्हित अक्षर val;
	अगर (!dmi_check_प्रणाली(msi_k8t_dmi_table))
		वापस; /* only applies to MSI K8T Neo2-FIR */

	pci_पढ़ो_config_byte(dev, 0x50, &val);
	अगर (val & 0x40) अणु
		pci_ग_लिखो_config_byte(dev, 0x50, val & (~0x40));

		/* verअगरy the change क्रम status output */
		pci_पढ़ो_config_byte(dev, 0x50, &val);
		अगर (val & 0x40)
			dev_info(&dev->dev, "Detected MSI K8T Neo2-FIR; "
					"can't enable onboard soundcard!\n");
		अन्यथा
			dev_info(&dev->dev, "Detected MSI K8T Neo2-FIR; "
					"enabled onboard soundcard\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8237,
		pci_fixup_msi_k8t_onboard_sound);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8237,
		pci_fixup_msi_k8t_onboard_sound);

/*
 * Some Toshiba laptops need extra code to enable their TI TSB43AB22/A.
 *
 * We pretend to bring them out of full D3 state, and restore the proper
 * IRQ, PCI cache line size, and BARs, otherwise the device won't function
 * properly.  In some हालs, the device will generate an पूर्णांकerrupt on
 * the wrong IRQ line, causing any devices sharing the line it's
 * *supposed* to use to be disabled by the kernel's IRQ debug code.
 */
अटल u16 toshiba_line_size;

अटल स्थिर काष्ठा dmi_प्रणाली_id toshiba_ohci1394_dmi_table[] = अणु
	अणु
		.ident = "Toshiba PS5 based laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "PS5"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Toshiba PSM4 based laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "PSM4"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Toshiba A40 based laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "PSA40U"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम pci_pre_fixup_toshiba_ohci1394(काष्ठा pci_dev *dev)
अणु
	अगर (!dmi_check_प्रणाली(toshiba_ohci1394_dmi_table))
		वापस; /* only applies to certain Toshibas (so far) */

	dev->current_state = PCI_D3cold;
	pci_पढ़ो_config_word(dev, PCI_CACHE_LINE_SIZE, &toshiba_line_size);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_TI, 0x8032,
			 pci_pre_fixup_toshiba_ohci1394);

अटल व्योम pci_post_fixup_toshiba_ohci1394(काष्ठा pci_dev *dev)
अणु
	अगर (!dmi_check_प्रणाली(toshiba_ohci1394_dmi_table))
		वापस; /* only applies to certain Toshibas (so far) */

	/* Restore config space on Toshiba laptops */
	pci_ग_लिखो_config_word(dev, PCI_CACHE_LINE_SIZE, toshiba_line_size);
	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, (u8 *)&dev->irq);
	pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_0,
			       pci_resource_start(dev, 0));
	pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_1,
			       pci_resource_start(dev, 1));
पूर्ण
DECLARE_PCI_FIXUP_ENABLE(PCI_VENDOR_ID_TI, 0x8032,
			 pci_post_fixup_toshiba_ohci1394);


/*
 * Prevent the BIOS trapping accesses to the Cyrix CS5530A video device
 * configuration space.
 */
अटल व्योम pci_early_fixup_cyrix_5530(काष्ठा pci_dev *dev)
अणु
	u8 r;
	/* clear 'F4 Video Configuration Trap' bit */
	pci_पढ़ो_config_byte(dev, 0x42, &r);
	r &= 0xfd;
	pci_ग_लिखो_config_byte(dev, 0x42, r);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_CYRIX, PCI_DEVICE_ID_CYRIX_5530_LEGACY,
			pci_early_fixup_cyrix_5530);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_CYRIX, PCI_DEVICE_ID_CYRIX_5530_LEGACY,
			pci_early_fixup_cyrix_5530);

/*
 * Siemens Nixकरोrf AG FSC Multiprocessor Interrupt Controller:
 * prevent update of the BAR0, which करोesn't look like a normal BAR.
 */
अटल व्योम pci_siemens_पूर्णांकerrupt_controller(काष्ठा pci_dev *dev)
अणु
	dev->resource[0].flags |= IORESOURCE_PCI_FIXED;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SIEMENS, 0x0015,
			  pci_siemens_पूर्णांकerrupt_controller);

/*
 * SB600: Disable BAR1 on device 14.0 to aव्योम HPET resources from
 * confusing the PCI engine:
 */
अटल व्योम sb600_disable_hpet_bar(काष्ठा pci_dev *dev)
अणु
	u8 val;

	/*
	 * The SB600 and SB700 both share the same device
	 * ID, but the PM रेजिस्टर 0x55 करोes something dअगरferent
	 * क्रम the SB700, so make sure we are dealing with the
	 * SB600 beक्रमe touching the bit:
	 */

	pci_पढ़ो_config_byte(dev, 0x08, &val);

	अगर (val < 0x2F) अणु
		outb(0x55, 0xCD6);
		val = inb(0xCD7);

		/* Set bit 7 in PM रेजिस्टर 0x55 */
		outb(0x55, 0xCD6);
		outb(val | 0x80, 0xCD7);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_ATI, 0x4385, sb600_disable_hpet_bar);

#अगर_घोषित CONFIG_HPET_TIMER
अटल व्योम sb600_hpet_quirk(काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *r = &dev->resource[1];

	अगर (r->flags & IORESOURCE_MEM && r->start == hpet_address) अणु
		r->flags |= IORESOURCE_PCI_FIXED;
		dev_info(&dev->dev, "reg 0x14 contains HPET; making it immovable\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATI, 0x4385, sb600_hpet_quirk);
#पूर्ण_अगर

/*
 * Twinhead H12Y needs us to block out a region otherwise we map devices
 * there and any access समाप्तs the box.
 *
 *   See: https://bugzilla.kernel.org/show_bug.cgi?id=10231
 *
 * Match off the LPC and svid/sdid (older kernels lose the bridge subvenकरोr)
 */
अटल व्योम twinhead_reserve_समाप्तing_zone(काष्ठा pci_dev *dev)
अणु
        अगर (dev->subप्रणाली_venकरोr == 0x14FF && dev->subप्रणाली_device == 0xA003) अणु
                pr_info("Reserving memory on Twinhead H12Y\n");
                request_mem_region(0xFFB00000, 0x100000, "twinhead");
        पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x27B9, twinhead_reserve_समाप्तing_zone);

/*
 * Device [8086:2fc0]
 * Erratum HSE43
 * CONFIG_TDP_NOMINAL CSR Implemented at Incorrect Offset
 * https://www.पूर्णांकel.com/content/www/us/en/processors/xeon/xeon-e5-v3-spec-update.hपंचांगl
 *
 * Devices [8086:6f60,6fa0,6fc0]
 * Erratum BDF2
 * PCI BARs in the Home Agent Will Return Non-Zero Values During Enumeration
 * https://www.पूर्णांकel.com/content/www/us/en/processors/xeon/xeon-e5-v4-spec-update.hपंचांगl
 */
अटल व्योम pci_invalid_bar(काष्ठा pci_dev *dev)
अणु
	dev->non_compliant_bars = 1;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x2fc0, pci_invalid_bar);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x6f60, pci_invalid_bar);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x6fa0, pci_invalid_bar);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x6fc0, pci_invalid_bar);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0xa1ec, pci_invalid_bar);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0xa1ed, pci_invalid_bar);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0xa26c, pci_invalid_bar);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0xa26d, pci_invalid_bar);

/*
 * Device [1022:7808]
 * 23. USB Wake on Connect/Disconnect with Low Speed Devices
 * https://support.amd.com/TechDocs/46837.pdf
 * Appendix A2
 * https://support.amd.com/TechDocs/42413.pdf
 */
अटल व्योम pci_fixup_amd_ehci_pme(काष्ठा pci_dev *dev)
अणु
	dev_info(&dev->dev, "PME# does not work under D3, disabling it\n");
	dev->pme_support &= ~((PCI_PM_CAP_PME_D3hot | PCI_PM_CAP_PME_D3cold)
		>> PCI_PM_CAP_PME_SHIFT);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x7808, pci_fixup_amd_ehci_pme);

/*
 * Device [1022:7914]
 * When in D0, PME# करोesn't get निश्चितed when plugging USB 2.0 device.
 */
अटल व्योम pci_fixup_amd_fch_xhci_pme(काष्ठा pci_dev *dev)
अणु
	dev_info(&dev->dev, "PME# does not work under D0, disabling it\n");
	dev->pme_support &= ~(PCI_PM_CAP_PME_D0 >> PCI_PM_CAP_PME_SHIFT);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x7914, pci_fixup_amd_fch_xhci_pme);

/*
 * Apple MacBook Pro: Aव्योम [mem 0x7fa00000-0x7fbfffff]
 *
 * Using the [mem 0x7fa00000-0x7fbfffff] region, e.g., by assigning it to
 * the 00:1c.0 Root Port, causes a conflict with [io 0x1804], which is used
 * क्रम soft घातeroff and suspend-to-RAM.
 *
 * As far as we know, this is related to the address space, not to the Root
 * Port itself.  Attaching the quirk to the Root Port is a convenience, but
 * it could probably also be a standalone DMI quirk.
 *
 * https://bugzilla.kernel.org/show_bug.cgi?id=103211
 */
अटल व्योम quirk_apple_mbp_घातeroff(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;

	अगर ((!dmi_match(DMI_PRODUCT_NAME, "MacBookPro11,4") &&
	     !dmi_match(DMI_PRODUCT_NAME, "MacBookPro11,5")) ||
	    pdev->bus->number != 0 || pdev->devfn != PCI_DEVFN(0x1c, 0))
		वापस;

	res = request_mem_region(0x7fa00000, 0x200000,
				 "MacBook Pro poweroff workaround");
	अगर (res)
		dev_info(dev, "claimed %s %pR\n", res->name, res);
	अन्यथा
		dev_info(dev, "can't work around MacBook Pro poweroff issue\n");
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x8c10, quirk_apple_mbp_घातeroff);

/*
 * VMD-enabled root ports will change the source ID क्रम all messages
 * to the VMD device. Rather than करोing device matching with the source
 * ID, the AER driver should traverse the child device tree, पढ़ोing
 * AER रेजिस्टरs to find the faulting device.
 */
अटल व्योम quirk_no_aersid(काष्ठा pci_dev *pdev)
अणु
	/* VMD Doमुख्य */
	अगर (is_vmd(pdev->bus) && pci_is_root_bus(pdev->bus))
		pdev->bus->bus_flags |= PCI_BUS_FLAGS_NO_AERSID;
पूर्ण
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, PCI_ANY_ID,
			      PCI_CLASS_BRIDGE_PCI, 8, quirk_no_aersid);

अटल व्योम quirk_पूर्णांकel_th_dnv(काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *r = &dev->resource[4];

	/*
	 * Denverton reports 2k of RTIT_BAR (पूर्णांकel_th resource 4), which
	 * appears to be 4 MB in reality.
	 */
	अगर (r->end == r->start + 0x7ff) अणु
		r->start = 0;
		r->end   = 0x3fffff;
		r->flags |= IORESOURCE_UNSET;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x19e1, quirk_पूर्णांकel_th_dnv);

#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT

#घोषणा AMD_141b_MMIO_BASE(x)	(0x80 + (x) * 0x8)
#घोषणा AMD_141b_MMIO_BASE_RE_MASK		BIT(0)
#घोषणा AMD_141b_MMIO_BASE_WE_MASK		BIT(1)
#घोषणा AMD_141b_MMIO_BASE_MMIOBASE_MASK	GENMASK(31,8)

#घोषणा AMD_141b_MMIO_LIMIT(x)	(0x84 + (x) * 0x8)
#घोषणा AMD_141b_MMIO_LIMIT_MMIOLIMIT_MASK	GENMASK(31,8)

#घोषणा AMD_141b_MMIO_HIGH(x)	(0x180 + (x) * 0x4)
#घोषणा AMD_141b_MMIO_HIGH_MMIOBASE_MASK	GENMASK(7,0)
#घोषणा AMD_141b_MMIO_HIGH_MMIOLIMIT_SHIFT	16
#घोषणा AMD_141b_MMIO_HIGH_MMIOLIMIT_MASK	GENMASK(23,16)

/*
 * The PCI Firmware Spec, rev 3.2, notes that ACPI should optionally allow
 * configuring host bridge winकरोws using the _PRS and _SRS methods.
 *
 * But this is rarely implemented, so we manually enable a large 64bit BAR क्रम
 * PCIe device on AMD Family 15h (Models 00h-1fh, 30h-3fh, 60h-7fh) Processors
 * here.
 */
अटल व्योम pci_amd_enable_64bit_bar(काष्ठा pci_dev *dev)
अणु
	अटल स्थिर अक्षर *name = "PCI Bus 0000:00";
	काष्ठा resource *res, *conflict;
	u32 base, limit, high;
	काष्ठा pci_dev *other;
	अचिन्हित i;

	अगर (!(pci_probe & PCI_BIG_ROOT_WINDOW))
		वापस;

	/* Check that we are the only device of that type */
	other = pci_get_device(dev->venकरोr, dev->device, शून्य);
	अगर (other != dev ||
	    (other = pci_get_device(dev->venकरोr, dev->device, other))) अणु
		/* This is a multi-socket प्रणाली, करोn't touch it क्रम now */
		pci_dev_put(other);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		pci_पढ़ो_config_dword(dev, AMD_141b_MMIO_BASE(i), &base);
		pci_पढ़ो_config_dword(dev, AMD_141b_MMIO_HIGH(i), &high);

		/* Is this slot मुक्त? */
		अगर (!(base & (AMD_141b_MMIO_BASE_RE_MASK |
			      AMD_141b_MMIO_BASE_WE_MASK)))
			अवरोध;

		base >>= 8;
		base |= high << 24;

		/* Abort अगर a slot alपढ़ोy configures a 64bit BAR. */
		अगर (base > 0x10000)
			वापस;
	पूर्ण
	अगर (i == 8)
		वापस;

	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस;

	/*
	 * Allocate a 256GB winकरोw directly below the 0xfd00000000 hardware
	 * limit (see AMD Family 15h Models 30h-3Fh BKDG, sec 2.4.6).
	 */
	res->name = name;
	res->flags = IORESOURCE_PREFETCH | IORESOURCE_MEM |
		IORESOURCE_MEM_64 | IORESOURCE_WINDOW;
	res->start = 0xbd00000000ull;
	res->end = 0xfd00000000ull - 1;

	conflict = request_resource_conflict(&iomem_resource, res);
	अगर (conflict) अणु
		kमुक्त(res);
		अगर (conflict->name != name)
			वापस;

		/* We are resuming from suspend; just reenable the winकरोw */
		res = conflict;
	पूर्ण अन्यथा अणु
		dev_info(&dev->dev, "adding root bus resource %pR (tainting kernel)\n",
			 res);
		add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);
		pci_bus_add_resource(dev->bus, res, 0);
	पूर्ण

	base = ((res->start >> 8) & AMD_141b_MMIO_BASE_MMIOBASE_MASK) |
		AMD_141b_MMIO_BASE_RE_MASK | AMD_141b_MMIO_BASE_WE_MASK;
	limit = ((res->end + 1) >> 8) & AMD_141b_MMIO_LIMIT_MMIOLIMIT_MASK;
	high = ((res->start >> 40) & AMD_141b_MMIO_HIGH_MMIOBASE_MASK) |
		((((res->end + 1) >> 40) << AMD_141b_MMIO_HIGH_MMIOLIMIT_SHIFT)
		 & AMD_141b_MMIO_HIGH_MMIOLIMIT_MASK);

	pci_ग_लिखो_config_dword(dev, AMD_141b_MMIO_HIGH(i), high);
	pci_ग_लिखो_config_dword(dev, AMD_141b_MMIO_LIMIT(i), limit);
	pci_ग_लिखो_config_dword(dev, AMD_141b_MMIO_BASE(i), base);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x1401, pci_amd_enable_64bit_bar);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x141b, pci_amd_enable_64bit_bar);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x1571, pci_amd_enable_64bit_bar);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x15b1, pci_amd_enable_64bit_bar);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x1601, pci_amd_enable_64bit_bar);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_AMD, 0x1401, pci_amd_enable_64bit_bar);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_AMD, 0x141b, pci_amd_enable_64bit_bar);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_AMD, 0x1571, pci_amd_enable_64bit_bar);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_AMD, 0x15b1, pci_amd_enable_64bit_bar);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_AMD, 0x1601, pci_amd_enable_64bit_bar);

#घोषणा RS690_LOWER_TOP_OF_DRAM2	0x30
#घोषणा RS690_LOWER_TOP_OF_DRAM2_VALID	0x1
#घोषणा RS690_UPPER_TOP_OF_DRAM2	0x31
#घोषणा RS690_HTIU_NB_INDEX		0xA8
#घोषणा RS690_HTIU_NB_INDEX_WR_ENABLE	0x100
#घोषणा RS690_HTIU_NB_DATA		0xAC

/*
 * Some BIOS implementations support RAM above 4GB, but करो not configure the
 * PCI host to respond to bus master accesses क्रम these addresses. These
 * implementations set the TOP_OF_DRAM_SLOT1 रेजिस्टर correctly, so PCI DMA
 * works as expected क्रम addresses below 4GB.
 *
 * Reference: "AMD RS690 ASIC Family Register Reference Guide" (pg. 2-57)
 * https://www.amd.com/प्रणाली/files/TechDocs/43372_rs690_rrg_3.00o.pdf
 */
अटल व्योम rs690_fix_64bit_dma(काष्ठा pci_dev *pdev)
अणु
	u32 val = 0;
	phys_addr_t top_of_dram = __pa(high_memory - 1) + 1;

	अगर (top_of_dram <= (1ULL << 32))
		वापस;

	pci_ग_लिखो_config_dword(pdev, RS690_HTIU_NB_INDEX,
				RS690_LOWER_TOP_OF_DRAM2);
	pci_पढ़ो_config_dword(pdev, RS690_HTIU_NB_DATA, &val);

	अगर (val)
		वापस;

	pci_info(pdev, "Adjusting top of DRAM to %pa for 64-bit DMA support\n", &top_of_dram);

	pci_ग_लिखो_config_dword(pdev, RS690_HTIU_NB_INDEX,
		RS690_UPPER_TOP_OF_DRAM2 | RS690_HTIU_NB_INDEX_WR_ENABLE);
	pci_ग_लिखो_config_dword(pdev, RS690_HTIU_NB_DATA, top_of_dram >> 32);

	pci_ग_लिखो_config_dword(pdev, RS690_HTIU_NB_INDEX,
		RS690_LOWER_TOP_OF_DRAM2 | RS690_HTIU_NB_INDEX_WR_ENABLE);
	pci_ग_लिखो_config_dword(pdev, RS690_HTIU_NB_DATA,
		top_of_dram | RS690_LOWER_TOP_OF_DRAM2_VALID);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x7910, rs690_fix_64bit_dma);

#पूर्ण_अगर
