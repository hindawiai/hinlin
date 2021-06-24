<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/arm/kernel/bios32.c
 *
 *  PCI bios-type initialisation क्रम PCI machines
 *
 *  Bits taken from various places.
 */
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/pci.h>

अटल पूर्णांक debug_pci;

/*
 * We can't use pci_get_device() here since we are
 * called from पूर्णांकerrupt context.
 */
अटल व्योम pcibios_bus_report_status(काष्ठा pci_bus *bus, u_पूर्णांक status_mask, पूर्णांक warn)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		u16 status;

		/*
		 * ignore host bridge - we handle
		 * that separately
		 */
		अगर (dev->bus->number == 0 && dev->devfn == 0)
			जारी;

		pci_पढ़ो_config_word(dev, PCI_STATUS, &status);
		अगर (status == 0xffff)
			जारी;

		अगर ((status & status_mask) == 0)
			जारी;

		/* clear the status errors */
		pci_ग_लिखो_config_word(dev, PCI_STATUS, status & status_mask);

		अगर (warn)
			prपूर्णांकk("(%s: %04X) ", pci_name(dev), status);
	पूर्ण

	list_क्रम_each_entry(dev, &bus->devices, bus_list)
		अगर (dev->subordinate)
			pcibios_bus_report_status(dev->subordinate, status_mask, warn);
पूर्ण

व्योम pcibios_report_status(u_पूर्णांक status_mask, पूर्णांक warn)
अणु
	काष्ठा pci_bus *bus;

	list_क्रम_each_entry(bus, &pci_root_buses, node)
		pcibios_bus_report_status(bus, status_mask, warn);
पूर्ण

/*
 * We करोn't use this to fix the device, but initialisation of it.
 * It's not the correct use क्रम this, but it works.
 * Note that the arbiter/ISA bridge appears to be buggy, specअगरically in
 * the following area:
 * 1. park on CPU
 * 2. ISA bridge ping-pong
 * 3. ISA bridge master handling of target RETRY
 *
 * Bug 3 is responsible क्रम the sound DMA grinding to a halt.  We now
 * live with bug 2.
 */
अटल व्योम pci_fixup_83c553(काष्ठा pci_dev *dev)
अणु
	/*
	 * Set memory region to start at address 0, and enable IO
	 */
	pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_0, PCI_BASE_ADDRESS_SPACE_MEMORY);
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, PCI_COMMAND_IO);

	dev->resource[0].end -= dev->resource[0].start;
	dev->resource[0].start = 0;

	/*
	 * All memory requests from ISA to be channelled to PCI
	 */
	pci_ग_लिखो_config_byte(dev, 0x48, 0xff);

	/*
	 * Enable ping-pong on bus master to ISA bridge transactions.
	 * This improves the sound DMA substantially.  The fixed
	 * priority arbiter also helps (see below).
	 */
	pci_ग_लिखो_config_byte(dev, 0x42, 0x01);

	/*
	 * Enable PCI retry
	 */
	pci_ग_लिखो_config_byte(dev, 0x40, 0x22);

	/*
	 * We used to set the arbiter to "park on last master" (bit
	 * 1 set), but unक्रमtunately the CyberPro करोes not park the
	 * bus.  We must thereक्रमe park on CPU.  Unक्रमtunately, this
	 * may trigger yet another bug in the 553.
	 */
	pci_ग_लिखो_config_byte(dev, 0x83, 0x02);

	/*
	 * Make the ISA DMA request lowest priority, and disable
	 * rotating priorities completely.
	 */
	pci_ग_लिखो_config_byte(dev, 0x80, 0x11);
	pci_ग_लिखो_config_byte(dev, 0x81, 0x00);

	/*
	 * Route INTA input to IRQ 11, and set IRQ11 to be level
	 * sensitive.
	 */
	pci_ग_लिखो_config_word(dev, 0x44, 0xb000);
	outb(0x08, 0x4d1);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_WINBOND, PCI_DEVICE_ID_WINBOND_83C553, pci_fixup_83c553);

अटल व्योम pci_fixup_unassign(काष्ठा pci_dev *dev)
अणु
	dev->resource[0].end -= dev->resource[0].start;
	dev->resource[0].start = 0;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_WINBOND2, PCI_DEVICE_ID_WINBOND2_89C940F, pci_fixup_unassign);

/*
 * Prevent the PCI layer from seeing the resources allocated to this device
 * अगर it is the host bridge by marking it as such.  These resources are of
 * no consequence to the PCI layer (they are handled अन्यथाwhere).
 */
अटल व्योम pci_fixup_dec21285(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	अगर (dev->devfn == 0) अणु
		dev->class &= 0xff;
		dev->class |= PCI_CLASS_BRIDGE_HOST << 8;
		क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
			dev->resource[i].start = 0;
			dev->resource[i].end   = 0;
			dev->resource[i].flags = 0;
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_21285, pci_fixup_dec21285);

/*
 * PCI IDE controllers use non-standard I/O port decoding, respect it.
 */
अटल व्योम pci_fixup_ide_bases(काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *r;
	पूर्णांक i;

	अगर ((dev->class >> 8) != PCI_CLASS_STORAGE_IDE)
		वापस;

	क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
		r = dev->resource + i;
		अगर ((r->start & ~0x80) == 0x374) अणु
			r->start |= 2;
			r->end = r->start;
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, pci_fixup_ide_bases);

/*
 * Put the DEC21142 to sleep
 */
अटल व्योम pci_fixup_dec21142(काष्ठा pci_dev *dev)
अणु
	pci_ग_लिखो_config_dword(dev, 0x40, 0x80000000);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_21142, pci_fixup_dec21142);

/*
 * The CY82C693 needs some rather major fixups to ensure that it करोes
 * the right thing.  Idea from the Alpha people, with a few additions.
 *
 * We ensure that the IDE base रेजिस्टरs are set to 1f0/3f4 क्रम the
 * primary bus, and 170/374 क्रम the secondary bus.  Also, hide them
 * from the PCI subप्रणाली view as well so we won't try to perक्रमm
 * our own स्वतः-configuration on them.
 *
 * In addition, we ensure that the PCI IDE पूर्णांकerrupts are routed to
 * IRQ 14 and IRQ 15 respectively.
 *
 * The above माला_लो us to a poपूर्णांक where the IDE on this device is
 * functional.  However, The CY82C693U _करोes not work_ in bus
 * master mode without locking the PCI bus solid.
 */
अटल व्योम pci_fixup_cy82c693(काष्ठा pci_dev *dev)
अणु
	अगर ((dev->class >> 8) == PCI_CLASS_STORAGE_IDE) अणु
		u32 base0, base1;

		अगर (dev->class & 0x80) अणु	/* primary */
			base0 = 0x1f0;
			base1 = 0x3f4;
		पूर्ण अन्यथा अणु			/* secondary */
			base0 = 0x170;
			base1 = 0x374;
		पूर्ण

		pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_0,
				       base0 | PCI_BASE_ADDRESS_SPACE_IO);
		pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_1,
				       base1 | PCI_BASE_ADDRESS_SPACE_IO);

		dev->resource[0].start = 0;
		dev->resource[0].end   = 0;
		dev->resource[0].flags = 0;

		dev->resource[1].start = 0;
		dev->resource[1].end   = 0;
		dev->resource[1].flags = 0;
	पूर्ण अन्यथा अगर (PCI_FUNC(dev->devfn) == 0) अणु
		/*
		 * Setup IDE IRQ routing.
		 */
		pci_ग_लिखो_config_byte(dev, 0x4b, 14);
		pci_ग_लिखो_config_byte(dev, 0x4c, 15);

		/*
		 * Disable FREQACK handshake, enable USB.
		 */
		pci_ग_लिखो_config_byte(dev, 0x4d, 0x41);

		/*
		 * Enable PCI retry, and PCI post-ग_लिखो buffer.
		 */
		pci_ग_लिखो_config_byte(dev, 0x44, 0x17);

		/*
		 * Enable ISA master and DMA post ग_लिखो buffering.
		 */
		pci_ग_लिखो_config_byte(dev, 0x45, 0x03);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_CONTAQ, PCI_DEVICE_ID_CONTAQ_82C693, pci_fixup_cy82c693);

/*
 * If the bus contains any of these devices, then we must not turn on
 * parity checking of any kind.  Currently this is CyberPro 20x0 only.
 */
अटल अंतरभूत पूर्णांक pdev_bad_क्रम_parity(काष्ठा pci_dev *dev)
अणु
	वापस ((dev->venकरोr == PCI_VENDOR_ID_INTERG &&
		 (dev->device == PCI_DEVICE_ID_INTERG_2000 ||
		  dev->device == PCI_DEVICE_ID_INTERG_2010)) ||
		(dev->venकरोr == PCI_VENDOR_ID_ITE &&
		 dev->device == PCI_DEVICE_ID_ITE_8152));

पूर्ण

/*
 * pcibios_fixup_bus - Called after each bus is probed,
 * but beक्रमe its children are examined.
 */
व्योम pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;
	u16 features = PCI_COMMAND_SERR | PCI_COMMAND_PARITY | PCI_COMMAND_FAST_BACK;

	/*
	 * Walk the devices on this bus, working out what we can
	 * and can't support.
	 */
	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		u16 status;

		pci_पढ़ो_config_word(dev, PCI_STATUS, &status);

		/*
		 * If any device on this bus करोes not support fast back
		 * to back transfers, then the bus as a whole is not able
		 * to support them.  Having fast back to back transfers
		 * on saves us one PCI cycle per transaction.
		 */
		अगर (!(status & PCI_STATUS_FAST_BACK))
			features &= ~PCI_COMMAND_FAST_BACK;

		अगर (pdev_bad_क्रम_parity(dev))
			features &= ~(PCI_COMMAND_SERR | PCI_COMMAND_PARITY);

		चयन (dev->class >> 8) अणु
		हाल PCI_CLASS_BRIDGE_PCI:
			pci_पढ़ो_config_word(dev, PCI_BRIDGE_CONTROL, &status);
			status |= PCI_BRIDGE_CTL_PARITY|PCI_BRIDGE_CTL_MASTER_ABORT;
			status &= ~(PCI_BRIDGE_CTL_BUS_RESET|PCI_BRIDGE_CTL_FAST_BACK);
			pci_ग_लिखो_config_word(dev, PCI_BRIDGE_CONTROL, status);
			अवरोध;

		हाल PCI_CLASS_BRIDGE_CARDBUS:
			pci_पढ़ो_config_word(dev, PCI_CB_BRIDGE_CONTROL, &status);
			status |= PCI_CB_BRIDGE_CTL_PARITY|PCI_CB_BRIDGE_CTL_MASTER_ABORT;
			pci_ग_लिखो_config_word(dev, PCI_CB_BRIDGE_CONTROL, status);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Now walk the devices again, this समय setting them up.
	 */
	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		u16 cmd;

		pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
		cmd |= features;
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);

		pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE,
				      L1_CACHE_BYTES >> 2);
	पूर्ण

	/*
	 * Propagate the flags to the PCI bridge.
	 */
	अगर (bus->self && bus->self->hdr_type == PCI_HEADER_TYPE_BRIDGE) अणु
		अगर (features & PCI_COMMAND_FAST_BACK)
			bus->bridge_ctl |= PCI_BRIDGE_CTL_FAST_BACK;
		अगर (features & PCI_COMMAND_PARITY)
			bus->bridge_ctl |= PCI_BRIDGE_CTL_PARITY;
	पूर्ण

	/*
	 * Report what we did क्रम this bus
	 */
	pr_info("PCI: bus%d: Fast back to back transfers %sabled\n",
		bus->number, (features & PCI_COMMAND_FAST_BACK) ? "en" : "dis");
पूर्ण
EXPORT_SYMBOL(pcibios_fixup_bus);

/*
 * Swizzle the device pin each समय we cross a bridge.  If a platक्रमm करोes
 * not provide a swizzle function, we perक्रमm the standard PCI swizzling.
 *
 * The शेष swizzling walks up the bus tree one level at a समय, applying
 * the standard swizzle function at each step, stopping when it finds the PCI
 * root bus.  This will वापस the slot number of the bridge device on the
 * root bus and the पूर्णांकerrupt pin on that device which should correspond
 * with the करोwnstream device पूर्णांकerrupt.
 *
 * Platक्रमms may override this, in which हाल the slot and pin वापसed
 * depend entirely on the platक्रमm code.  However, please note that the
 * PCI standard swizzle is implemented on plug-in cards and Cardbus based
 * PCI extenders, so it can not be ignored.
 */
अटल u8 pcibios_swizzle(काष्ठा pci_dev *dev, u8 *pin)
अणु
	काष्ठा pci_sys_data *sys = dev->sysdata;
	पूर्णांक slot, oldpin = *pin;

	अगर (sys->swizzle)
		slot = sys->swizzle(dev, pin);
	अन्यथा
		slot = pci_common_swizzle(dev, pin);

	अगर (debug_pci)
		prपूर्णांकk("PCI: %s swizzling pin %d => pin %d slot %d\n",
			pci_name(dev), oldpin, *pin, slot);

	वापस slot;
पूर्ण

/*
 * Map a slot/pin to an IRQ.
 */
अटल पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा pci_sys_data *sys = dev->sysdata;
	पूर्णांक irq = -1;

	अगर (sys->map_irq)
		irq = sys->map_irq(dev, slot, pin);

	अगर (debug_pci)
		prपूर्णांकk("PCI: %s mapping slot %d pin %d => irq %d\n",
			pci_name(dev), slot, pin, irq);

	वापस irq;
पूर्ण

अटल पूर्णांक pcibios_init_resource(पूर्णांक busnr, काष्ठा pci_sys_data *sys)
अणु
	पूर्णांक ret;
	काष्ठा resource_entry *winकरोw;

	अगर (list_empty(&sys->resources)) अणु
		pci_add_resource_offset(&sys->resources,
			 &iomem_resource, sys->mem_offset);
	पूर्ण

	resource_list_क्रम_each_entry(winकरोw, &sys->resources)
		अगर (resource_type(winकरोw->res) == IORESOURCE_IO)
			वापस 0;

	sys->io_res.start = (busnr * SZ_64K) ?  : pcibios_min_io;
	sys->io_res.end = (busnr + 1) * SZ_64K - 1;
	sys->io_res.flags = IORESOURCE_IO;
	sys->io_res.name = sys->io_res_name;
	प्र_लिखो(sys->io_res_name, "PCI%d I/O", busnr);

	ret = request_resource(&ioport_resource, &sys->io_res);
	अगर (ret) अणु
		pr_err("PCI: unable to allocate I/O port region (%d)\n", ret);
		वापस ret;
	पूर्ण
	pci_add_resource_offset(&sys->resources, &sys->io_res,
				sys->io_offset);

	वापस 0;
पूर्ण

अटल व्योम pcibios_init_hw(काष्ठा device *parent, काष्ठा hw_pci *hw,
			    काष्ठा list_head *head)
अणु
	काष्ठा pci_sys_data *sys = शून्य;
	पूर्णांक ret;
	पूर्णांक nr, busnr;

	क्रम (nr = busnr = 0; nr < hw->nr_controllers; nr++) अणु
		काष्ठा pci_host_bridge *bridge;

		bridge = pci_alloc_host_bridge(माप(काष्ठा pci_sys_data));
		अगर (WARN(!bridge, "PCI: unable to allocate bridge!"))
			अवरोध;

		sys = pci_host_bridge_priv(bridge);

		sys->busnr   = busnr;
		sys->swizzle = hw->swizzle;
		sys->map_irq = hw->map_irq;
		INIT_LIST_HEAD(&sys->resources);

		अगर (hw->निजी_data)
			sys->निजी_data = hw->निजी_data[nr];

		ret = hw->setup(nr, sys);

		अगर (ret > 0) अणु

			ret = pcibios_init_resource(nr, sys);
			अगर (ret)  अणु
				pci_मुक्त_host_bridge(bridge);
				अवरोध;
			पूर्ण

			bridge->map_irq = pcibios_map_irq;
			bridge->swizzle_irq = pcibios_swizzle;

			अगर (hw->scan)
				ret = hw->scan(nr, bridge);
			अन्यथा अणु
				list_splice_init(&sys->resources,
						 &bridge->winकरोws);
				bridge->dev.parent = parent;
				bridge->sysdata = sys;
				bridge->busnr = sys->busnr;
				bridge->ops = hw->ops;

				ret = pci_scan_root_bus_bridge(bridge);
			पूर्ण

			अगर (WARN(ret < 0, "PCI: unable to scan bus!")) अणु
				pci_मुक्त_host_bridge(bridge);
				अवरोध;
			पूर्ण

			sys->bus = bridge->bus;

			busnr = sys->bus->busn_res.end + 1;

			list_add(&sys->node, head);
		पूर्ण अन्यथा अणु
			pci_मुक्त_host_bridge(bridge);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम pci_common_init_dev(काष्ठा device *parent, काष्ठा hw_pci *hw)
अणु
	काष्ठा pci_sys_data *sys;
	LIST_HEAD(head);

	pci_add_flags(PCI_REASSIGN_ALL_BUS);
	अगर (hw->preinit)
		hw->preinit();
	pcibios_init_hw(parent, hw, &head);
	अगर (hw->postinit)
		hw->postinit();

	list_क्रम_each_entry(sys, &head, node) अणु
		काष्ठा pci_bus *bus = sys->bus;

		/*
		 * We insert PCI resources पूर्णांकo the iomem_resource and
		 * ioport_resource trees in either pci_bus_claim_resources()
		 * or pci_bus_assign_resources().
		 */
		अगर (pci_has_flag(PCI_PROBE_ONLY)) अणु
			pci_bus_claim_resources(bus);
		पूर्ण अन्यथा अणु
			काष्ठा pci_bus *child;

			pci_bus_size_bridges(bus);
			pci_bus_assign_resources(bus);

			list_क्रम_each_entry(child, &bus->children, node)
				pcie_bus_configure_settings(child);
		पूर्ण

		pci_bus_add_devices(bus);
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_PCI_HOST_ITE8152
व्योम pcibios_set_master(काष्ठा pci_dev *dev)
अणु
	/* No special bus mastering setup handling */
पूर्ण
#पूर्ण_अगर

अक्षर * __init pcibios_setup(अक्षर *str)
अणु
	अगर (!म_भेद(str, "debug")) अणु
		debug_pci = 1;
		वापस शून्य;
	पूर्ण
	वापस str;
पूर्ण

/*
 * From arch/i386/kernel/pci-i386.c:
 *
 * We need to aव्योम collisions with `mirrored' VGA ports
 * and other strange ISA hardware, so we always want the
 * addresses to be allocated in the 0x000-0x0ff region
 * modulo 0x400.
 *
 * Why? Because some silly बाह्यal IO cards only decode
 * the low 10 bits of the IO address. The 0x00-0xff region
 * is reserved क्रम motherboard devices that decode all 16
 * bits, so it's ok to allocate at, say, 0x2800-0x28ff,
 * but we want to try to aव्योम allocating at 0x2900-0x2bff
 * which might be mirrored at 0x0100-0x03ff..
 */
resource_माप_प्रकार pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
				resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा pci_dev *dev = data;
	resource_माप_प्रकार start = res->start;
	काष्ठा pci_host_bridge *host_bridge;

	अगर (res->flags & IORESOURCE_IO && start & 0x300)
		start = (start + 0x3ff) & ~0x3ff;

	start = (start + align - 1) & ~(align - 1);

	host_bridge = pci_find_host_bridge(dev->bus);

	अगर (host_bridge->align_resource)
		वापस host_bridge->align_resource(dev, res,
				start, size, align);

	वापस start;
पूर्ण

व्योम __init pci_map_io_early(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा map_desc pci_io_desc = अणु
		.भव	= PCI_IO_VIRT_BASE,
		.type		= MT_DEVICE,
		.length		= SZ_64K,
	पूर्ण;

	pci_io_desc.pfn = pfn;
	iotable_init(&pci_io_desc, 1);
पूर्ण
