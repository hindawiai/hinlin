<शैली गुरु>
/*
 * pci.c -- PCI bus support क्रम ColdFire processors
 *
 * (C) Copyright 2012, Greg Ungerer <gerg@uclinux.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/m54xxpci.h>

/*
 * Memory and IO mappings. We use a 1:1 mapping क्रम local host memory to
 * PCI bus memory (no reason not to really). IO space is mapped in its own
 * separate address region. The device configuration space is mapped over
 * the IO map space when we enable it in the PCICAR रेजिस्टर.
 */
अटल काष्ठा pci_bus *rootbus;
अटल अचिन्हित दीर्घ iospace;

/*
 * We need to be carefull probing on bus 0 (directly connected to host
 * bridge). We should only access the well defined possible devices in
 * use, ignore aliases and the like.
 */
अटल अचिन्हित अक्षर mcf_host_slot2sid[32] = अणु
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 0, 3, 4, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
पूर्ण;

अटल अचिन्हित अक्षर mcf_host_irq[] = अणु
	0, 69, 69, 71, 71,
पूर्ण;

/*
 * Configuration space access functions. Configuration space access is
 * through the IO mapping winकरोw, enabling it via the PCICAR रेजिस्टर.
 */
अटल अचिन्हित दीर्घ mcf_mk_pcicar(पूर्णांक bus, अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	वापस (bus << PCICAR_BUSN) | (devfn << PCICAR_DEVFNN) | (where & 0xfc);
पूर्ण

अटल पूर्णांक mcf_pci_पढ़ोconfig(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	अचिन्हित दीर्घ addr;

	*value = 0xffffffff;

	अगर (bus->number == 0) अणु
		अगर (mcf_host_slot2sid[PCI_SLOT(devfn)] == 0)
			वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	addr = mcf_mk_pcicar(bus->number, devfn, where);
	__raw_ग_लिखोl(PCICAR_E | addr, PCICAR);
	__raw_पढ़ोl(PCICAR);
	addr = iospace + (where & 0x3);

	चयन (size) अणु
	हाल 1:
		*value = __raw_पढ़ोb(addr);
		अवरोध;
	हाल 2:
		*value = le16_to_cpu(__raw_पढ़ोw(addr));
		अवरोध;
	शेष:
		*value = le32_to_cpu(__raw_पढ़ोl(addr));
		अवरोध;
	पूर्ण

	__raw_ग_लिखोl(0, PCICAR);
	__raw_पढ़ोl(PCICAR);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक mcf_pci_ग_लिखोconfig(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, पूर्णांक size, u32 value)
अणु
	अचिन्हित दीर्घ addr;

	अगर (bus->number == 0) अणु
		अगर (mcf_host_slot2sid[PCI_SLOT(devfn)] == 0)
			वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	addr = mcf_mk_pcicar(bus->number, devfn, where);
	__raw_ग_लिखोl(PCICAR_E | addr, PCICAR);
	__raw_पढ़ोl(PCICAR);
	addr = iospace + (where & 0x3);

	चयन (size) अणु
	हाल 1:
		 __raw_ग_लिखोb(value, addr);
		अवरोध;
	हाल 2:
		__raw_ग_लिखोw(cpu_to_le16(value), addr);
		अवरोध;
	शेष:
		__raw_ग_लिखोl(cpu_to_le32(value), addr);
		अवरोध;
	पूर्ण

	__raw_ग_लिखोl(0, PCICAR);
	__raw_पढ़ोl(PCICAR);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops mcf_pci_ops = अणु
	.पढ़ो	= mcf_pci_पढ़ोconfig,
	.ग_लिखो	= mcf_pci_ग_लिखोconfig,
पूर्ण;

/*
 * Initialize the PCI bus रेजिस्टरs, and scan the bus.
 */
अटल काष्ठा resource mcf_pci_mem = अणु
	.name	= "PCI Memory space",
	.start	= PCI_MEM_PA,
	.end	= PCI_MEM_PA + PCI_MEM_SIZE - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource mcf_pci_io = अणु
	.name	= "PCI IO space",
	.start	= 0x400,
	.end	= 0x10000 - 1,
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल काष्ठा resource busn_resource = अणु
	.name	= "PCI busn",
	.start	= 0,
	.end	= 255,
	.flags	= IORESOURCE_BUS,
पूर्ण;

/*
 * Interrupt mapping and setting.
 */
अटल पूर्णांक mcf_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक sid;

	sid = mcf_host_slot2sid[slot];
	अगर (sid)
		वापस mcf_host_irq[sid];
	वापस 0;
पूर्ण

अटल पूर्णांक __init mcf_pci_init(व्योम)
अणु
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक ret;

	bridge = pci_alloc_host_bridge(0);
	अगर (!bridge)
		वापस -ENOMEM;

	pr_info("ColdFire: PCI bus initialization...\n");

	/* Reset the बाह्यal PCI bus */
	__raw_ग_लिखोl(PCIGSCR_RESET, PCIGSCR);
	__raw_ग_लिखोl(0, PCITCR);

	request_resource(&iomem_resource, &mcf_pci_mem);
	request_resource(&iomem_resource, &mcf_pci_io);

	/* Configure PCI arbiter */
	__raw_ग_लिखोl(PACR_INTMPRI | PACR_INTMINTE | PACR_EXTMPRI(0x1f) |
		PACR_EXTMINTE(0x1f), PACR);

	/* Set required multi-function pins क्रम PCI bus use */
	__raw_ग_लिखोw(0x3ff, MCFGPIO_PAR_PCIBG);
	__raw_ग_लिखोw(0x3ff, MCFGPIO_PAR_PCIBR);

	/* Set up config space क्रम local host bus controller */
	__raw_ग_लिखोl(PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER |
		PCI_COMMAND_INVALIDATE, PCISCR);
	__raw_ग_लिखोl(PCICR1_LT(32) | PCICR1_CL(8), PCICR1);
	__raw_ग_लिखोl(0, PCICR2);

	/*
	 * Set up the initiator winकरोws क्रम memory and IO mapping.
	 * These give the CPU bus access onto the PCI bus. One क्रम each of
	 * PCI memory and IO address spaces.
	 */
	__raw_ग_लिखोl(WXBTAR(PCI_MEM_PA, PCI_MEM_BA, PCI_MEM_SIZE),
		PCIIW0BTAR);
	__raw_ग_लिखोl(WXBTAR(PCI_IO_PA, PCI_IO_BA, PCI_IO_SIZE),
		PCIIW1BTAR);
	__raw_ग_लिखोl(PCIIWCR_W0_MEM /*| PCIIWCR_W0_MRDL*/ | PCIIWCR_W0_E |
		PCIIWCR_W1_IO | PCIIWCR_W1_E, PCIIWCR);

	/*
	 * Set up the target winकरोws क्रम access from the PCI bus back to the
	 * CPU bus. All we need is access to प्रणाली RAM (क्रम mastering).
	 */
	__raw_ग_लिखोl(CONFIG_RAMBASE, PCIBAR1);
	__raw_ग_लिखोl(CONFIG_RAMBASE | PCITBATR1_E, PCITBATR1);

	/* Keep a भव mapping to IO/config space active */
	iospace = (अचिन्हित दीर्घ) ioremap(PCI_IO_PA, PCI_IO_SIZE);
	अगर (iospace == 0) अणु
		pci_मुक्त_host_bridge(bridge);
		वापस -ENODEV;
	पूर्ण
	pr_info("Coldfire: PCI IO/config window mapped to 0x%x\n",
		(u32) iospace);

	/* Turn of PCI reset, and रुको क्रम devices to settle */
	__raw_ग_लिखोl(0, PCIGSCR);
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_समयout(msecs_to_jअगरfies(200));


	pci_add_resource(&bridge->winकरोws, &ioport_resource);
	pci_add_resource(&bridge->winकरोws, &iomem_resource);
	pci_add_resource(&bridge->winकरोws, &busn_resource);
	bridge->dev.parent = शून्य;
	bridge->sysdata = शून्य;
	bridge->busnr = 0;
	bridge->ops = &mcf_pci_ops;
	bridge->swizzle_irq = pci_common_swizzle;
	bridge->map_irq = mcf_pci_map_irq;

	ret = pci_scan_root_bus_bridge(bridge);
	अगर (ret) अणु
		pci_मुक्त_host_bridge(bridge);
		वापस ret;
	पूर्ण

	rootbus = bridge->bus;

	rootbus->resource[0] = &mcf_pci_io;
	rootbus->resource[1] = &mcf_pci_mem;

	pci_bus_size_bridges(rootbus);
	pci_bus_assign_resources(rootbus);
	pci_bus_add_devices(rootbus);
	वापस 0;
पूर्ण

subsys_initcall(mcf_pci_init);
