<शैली गुरु>
/*
 * arch/arm/mach-orion5x/pci.c
 *
 * PCI and PCIe functions क्रम Marvell Orion System On Chip
 *
 * Maपूर्णांकainer: Tzachi Perelstein <tzachi@marvell.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/mbus.h>
#समावेश <video/vga.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <plat/pcie.h>
#समावेश <plat/addr-map.h>
#समावेश "common.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * Orion has one PCIe controller and one PCI controller.
 *
 * Note1: The local PCIe bus number is '0'. The local PCI bus number
 * follows the scanned PCIe bridged busses, अगर any.
 *
 * Note2: It is possible क्रम PCI/PCIe agents to access many subप्रणाली's
 * space, by configuring BARs and Address Decode Winकरोws, e.g. flashes on
 * device bus, Orion रेजिस्टरs, etc. However this code only enable the
 * access to DDR banks.
 ****************************************************************************/


/*****************************************************************************
 * PCIe controller
 ****************************************************************************/
#घोषणा PCIE_BASE	(ORION5X_PCIE_VIRT_BASE)

व्योम __init orion5x_pcie_id(u32 *dev, u32 *rev)
अणु
	*dev = orion_pcie_dev_id(PCIE_BASE);
	*rev = orion_pcie_rev(PCIE_BASE);
पूर्ण

अटल पूर्णांक pcie_valid_config(पूर्णांक bus, पूर्णांक dev)
अणु
	/*
	 * Don't go out when trying to access --
	 * 1. nonexisting device on local bus
	 * 2. where there's no device connected (no link)
	 */
	अगर (bus == 0 && dev == 0)
		वापस 1;

	अगर (!orion_pcie_link_up(PCIE_BASE))
		वापस 0;

	अगर (bus == 0 && dev != 1)
		वापस 0;

	वापस 1;
पूर्ण


/*
 * PCIe config cycles are करोne by programming the PCIE_CONF_ADDR रेजिस्टर
 * and then पढ़ोing the PCIE_CONF_DATA रेजिस्टर. Need to make sure these
 * transactions are atomic.
 */
अटल DEFINE_SPINLOCK(orion5x_pcie_lock);

अटल पूर्णांक pcie_rd_conf(काष्ठा pci_bus *bus, u32 devfn, पूर्णांक where,
			पूर्णांक size, u32 *val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (pcie_valid_config(bus->number, PCI_SLOT(devfn)) == 0) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	spin_lock_irqsave(&orion5x_pcie_lock, flags);
	ret = orion_pcie_rd_conf(PCIE_BASE, bus, devfn, where, size, val);
	spin_unlock_irqrestore(&orion5x_pcie_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक pcie_rd_conf_wa(काष्ठा pci_bus *bus, u32 devfn,
			   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	पूर्णांक ret;

	अगर (pcie_valid_config(bus->number, PCI_SLOT(devfn)) == 0) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	/*
	 * We only support access to the non-extended configuration
	 * space when using the WA access method (or we would have to
	 * sacrअगरice 256M of CPU भव address space.)
	 */
	अगर (where >= 0x100) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	ret = orion_pcie_rd_conf_wa(ORION5X_PCIE_WA_VIRT_BASE,
				    bus, devfn, where, size, val);

	वापस ret;
पूर्ण

अटल पूर्णांक pcie_wr_conf(काष्ठा pci_bus *bus, u32 devfn,
			पूर्णांक where, पूर्णांक size, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (pcie_valid_config(bus->number, PCI_SLOT(devfn)) == 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	spin_lock_irqsave(&orion5x_pcie_lock, flags);
	ret = orion_pcie_wr_conf(PCIE_BASE, bus, devfn, where, size, val);
	spin_unlock_irqrestore(&orion5x_pcie_lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा pci_ops pcie_ops = अणु
	.पढ़ो = pcie_rd_conf,
	.ग_लिखो = pcie_wr_conf,
पूर्ण;


अटल पूर्णांक __init pcie_setup(काष्ठा pci_sys_data *sys)
अणु
	काष्ठा resource *res;
	पूर्णांक dev;

	/*
	 * Generic PCIe unit setup.
	 */
	orion_pcie_setup(PCIE_BASE);

	/*
	 * Check whether to apply Orion-1/Orion-NAS PCIe config
	 * पढ़ो transaction workaround.
	 */
	dev = orion_pcie_dev_id(PCIE_BASE);
	अगर (dev == MV88F5181_DEV_ID || dev == MV88F5182_DEV_ID) अणु
		prपूर्णांकk(KERN_NOTICE "Applying Orion-1/Orion-NAS PCIe config "
				   "read transaction workaround\n");
		mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_PCIE_WA_TARGET,
					    ORION_MBUS_PCIE_WA_ATTR,
					    ORION5X_PCIE_WA_PHYS_BASE,
					    ORION5X_PCIE_WA_SIZE);
		pcie_ops.पढ़ो = pcie_rd_conf_wa;
	पूर्ण

	pci_ioremap_io(sys->busnr * SZ_64K, ORION5X_PCIE_IO_PHYS_BASE);

	/*
	 * Request resources.
	 */
	res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
	अगर (!res)
		panic("pcie_setup unable to alloc resources");

	/*
	 * IORESOURCE_MEM
	 */
	res->name = "PCIe Memory Space";
	res->flags = IORESOURCE_MEM;
	res->start = ORION5X_PCIE_MEM_PHYS_BASE;
	res->end = res->start + ORION5X_PCIE_MEM_SIZE - 1;
	अगर (request_resource(&iomem_resource, res))
		panic("Request PCIe Memory resource failed\n");
	pci_add_resource_offset(&sys->resources, res, sys->mem_offset);

	वापस 1;
पूर्ण

/*****************************************************************************
 * PCI controller
 ****************************************************************************/
#घोषणा ORION5X_PCI_REG(x)	(ORION5X_PCI_VIRT_BASE + (x))
#घोषणा PCI_MODE		ORION5X_PCI_REG(0xd00)
#घोषणा PCI_CMD			ORION5X_PCI_REG(0xc00)
#घोषणा PCI_P2P_CONF		ORION5X_PCI_REG(0x1d14)
#घोषणा PCI_CONF_ADDR		ORION5X_PCI_REG(0xc78)
#घोषणा PCI_CONF_DATA		ORION5X_PCI_REG(0xc7c)

/*
 * PCI_MODE bits
 */
#घोषणा PCI_MODE_64BIT			(1 << 2)
#घोषणा PCI_MODE_PCIX			((1 << 4) | (1 << 5))

/*
 * PCI_CMD bits
 */
#घोषणा PCI_CMD_HOST_REORDER		(1 << 29)

/*
 * PCI_P2P_CONF bits
 */
#घोषणा PCI_P2P_BUS_OFFS		16
#घोषणा PCI_P2P_BUS_MASK		(0xff << PCI_P2P_BUS_OFFS)
#घोषणा PCI_P2P_DEV_OFFS		24
#घोषणा PCI_P2P_DEV_MASK		(0x1f << PCI_P2P_DEV_OFFS)

/*
 * PCI_CONF_ADDR bits
 */
#घोषणा PCI_CONF_REG(reg)		((reg) & 0xfc)
#घोषणा PCI_CONF_FUNC(func)		(((func) & 0x3) << 8)
#घोषणा PCI_CONF_DEV(dev)		(((dev) & 0x1f) << 11)
#घोषणा PCI_CONF_BUS(bus)		(((bus) & 0xff) << 16)
#घोषणा PCI_CONF_ADDR_EN		(1 << 31)

/*
 * Internal configuration space
 */
#घोषणा PCI_CONF_FUNC_STAT_CMD		0
#घोषणा PCI_CONF_REG_STAT_CMD		4
#घोषणा PCIX_STAT			0x64
#घोषणा PCIX_STAT_BUS_OFFS		8
#घोषणा PCIX_STAT_BUS_MASK		(0xff << PCIX_STAT_BUS_OFFS)

/*
 * PCI Address Decode Winकरोws रेजिस्टरs
 */
#घोषणा PCI_BAR_SIZE_DDR_CS(n)	(((n) == 0) ? ORION5X_PCI_REG(0xc08) : \
				 ((n) == 1) ? ORION5X_PCI_REG(0xd08) : \
				 ((n) == 2) ? ORION5X_PCI_REG(0xc0c) : \
				 ((n) == 3) ? ORION5X_PCI_REG(0xd0c) : शून्य)
#घोषणा PCI_BAR_REMAP_DDR_CS(n)	(((n) == 0) ? ORION5X_PCI_REG(0xc48) : \
				 ((n) == 1) ? ORION5X_PCI_REG(0xd48) : \
				 ((n) == 2) ? ORION5X_PCI_REG(0xc4c) : \
				 ((n) == 3) ? ORION5X_PCI_REG(0xd4c) : शून्य)
#घोषणा PCI_BAR_ENABLE		ORION5X_PCI_REG(0xc3c)
#घोषणा PCI_ADDR_DECODE_CTRL	ORION5X_PCI_REG(0xd3c)

/*
 * PCI configuration helpers क्रम BAR settings
 */
#घोषणा PCI_CONF_FUNC_BAR_CS(n)		((n) >> 1)
#घोषणा PCI_CONF_REG_BAR_LO_CS(n)	(((n) & 1) ? 0x18 : 0x10)
#घोषणा PCI_CONF_REG_BAR_HI_CS(n)	(((n) & 1) ? 0x1c : 0x14)

/*
 * PCI config cycles are करोne by programming the PCI_CONF_ADDR रेजिस्टर
 * and then पढ़ोing the PCI_CONF_DATA रेजिस्टर. Need to make sure these
 * transactions are atomic.
 */
अटल DEFINE_SPINLOCK(orion5x_pci_lock);

अटल पूर्णांक orion5x_pci_cardbus_mode;

अटल पूर्णांक orion5x_pci_local_bus_nr(व्योम)
अणु
	u32 conf = पढ़ोl(PCI_P2P_CONF);
	वापस((conf & PCI_P2P_BUS_MASK) >> PCI_P2P_BUS_OFFS);
पूर्ण

अटल पूर्णांक orion5x_pci_hw_rd_conf(पूर्णांक bus, पूर्णांक dev, u32 func,
					u32 where, u32 size, u32 *val)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&orion5x_pci_lock, flags);

	ग_लिखोl(PCI_CONF_BUS(bus) |
		PCI_CONF_DEV(dev) | PCI_CONF_REG(where) |
		PCI_CONF_FUNC(func) | PCI_CONF_ADDR_EN, PCI_CONF_ADDR);

	*val = पढ़ोl(PCI_CONF_DATA);

	अगर (size == 1)
		*val = (*val >> (8*(where & 0x3))) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (*val >> (8*(where & 0x3))) & 0xffff;

	spin_unlock_irqrestore(&orion5x_pci_lock, flags);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक orion5x_pci_hw_wr_conf(पूर्णांक bus, पूर्णांक dev, u32 func,
					u32 where, u32 size, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = PCIBIOS_SUCCESSFUL;

	spin_lock_irqsave(&orion5x_pci_lock, flags);

	ग_लिखोl(PCI_CONF_BUS(bus) |
		PCI_CONF_DEV(dev) | PCI_CONF_REG(where) |
		PCI_CONF_FUNC(func) | PCI_CONF_ADDR_EN, PCI_CONF_ADDR);

	अगर (size == 4) अणु
		__raw_ग_लिखोl(val, PCI_CONF_DATA);
	पूर्ण अन्यथा अगर (size == 2) अणु
		__raw_ग_लिखोw(val, PCI_CONF_DATA + (where & 0x3));
	पूर्ण अन्यथा अगर (size == 1) अणु
		__raw_ग_लिखोb(val, PCI_CONF_DATA + (where & 0x3));
	पूर्ण अन्यथा अणु
		ret = PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	spin_unlock_irqrestore(&orion5x_pci_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक orion5x_pci_valid_config(पूर्णांक bus, u32 devfn)
अणु
	अगर (bus == orion5x_pci_local_bus_nr()) अणु
		/*
		 * Don't go out क्रम local device
		 */
		अगर (PCI_SLOT(devfn) == 0 && PCI_FUNC(devfn) != 0)
			वापस 0;

		/*
		 * When the PCI संकेतs are directly connected to a
		 * Cardbus slot, ignore all but device IDs 0 and 1.
		 */
		अगर (orion5x_pci_cardbus_mode && PCI_SLOT(devfn) > 1)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक orion5x_pci_rd_conf(काष्ठा pci_bus *bus, u32 devfn,
				पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	अगर (!orion5x_pci_valid_config(bus->number, devfn)) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	वापस orion5x_pci_hw_rd_conf(bus->number, PCI_SLOT(devfn),
					PCI_FUNC(devfn), where, size, val);
पूर्ण

अटल पूर्णांक orion5x_pci_wr_conf(काष्ठा pci_bus *bus, u32 devfn,
				पूर्णांक where, पूर्णांक size, u32 val)
अणु
	अगर (!orion5x_pci_valid_config(bus->number, devfn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस orion5x_pci_hw_wr_conf(bus->number, PCI_SLOT(devfn),
					PCI_FUNC(devfn), where, size, val);
पूर्ण

अटल काष्ठा pci_ops pci_ops = अणु
	.पढ़ो = orion5x_pci_rd_conf,
	.ग_लिखो = orion5x_pci_wr_conf,
पूर्ण;

अटल व्योम __init orion5x_pci_set_bus_nr(पूर्णांक nr)
अणु
	u32 p2p = पढ़ोl(PCI_P2P_CONF);

	अगर (पढ़ोl(PCI_MODE) & PCI_MODE_PCIX) अणु
		/*
		 * PCI-X mode
		 */
		u32 pcix_status, bus, dev;
		bus = (p2p & PCI_P2P_BUS_MASK) >> PCI_P2P_BUS_OFFS;
		dev = (p2p & PCI_P2P_DEV_MASK) >> PCI_P2P_DEV_OFFS;
		orion5x_pci_hw_rd_conf(bus, dev, 0, PCIX_STAT, 4, &pcix_status);
		pcix_status &= ~PCIX_STAT_BUS_MASK;
		pcix_status |= (nr << PCIX_STAT_BUS_OFFS);
		orion5x_pci_hw_wr_conf(bus, dev, 0, PCIX_STAT, 4, pcix_status);
	पूर्ण अन्यथा अणु
		/*
		 * PCI Conventional mode
		 */
		p2p &= ~PCI_P2P_BUS_MASK;
		p2p |= (nr << PCI_P2P_BUS_OFFS);
		ग_लिखोl(p2p, PCI_P2P_CONF);
	पूर्ण
पूर्ण

अटल व्योम __init orion5x_pci_master_slave_enable(व्योम)
अणु
	पूर्णांक bus_nr, func, reg;
	u32 val;

	bus_nr = orion5x_pci_local_bus_nr();
	func = PCI_CONF_FUNC_STAT_CMD;
	reg = PCI_CONF_REG_STAT_CMD;
	orion5x_pci_hw_rd_conf(bus_nr, 0, func, reg, 4, &val);
	val |= (PCI_COMMAND_IO | PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	orion5x_pci_hw_wr_conf(bus_nr, 0, func, reg, 4, val | 0x7);
पूर्ण

अटल व्योम __init orion5x_setup_pci_wins(व्योम)
अणु
	स्थिर काष्ठा mbus_dram_target_info *dram = mv_mbus_dram_info();
	u32 win_enable;
	पूर्णांक bus;
	पूर्णांक i;

	/*
	 * First, disable winकरोws.
	 */
	win_enable = 0xffffffff;
	ग_लिखोl(win_enable, PCI_BAR_ENABLE);

	/*
	 * Setup winकरोws क्रम DDR banks.
	 */
	bus = orion5x_pci_local_bus_nr();

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;
		u32 func = PCI_CONF_FUNC_BAR_CS(cs->cs_index);
		u32 reg;
		u32 val;

		/*
		 * Write DRAM bank base address रेजिस्टर.
		 */
		reg = PCI_CONF_REG_BAR_LO_CS(cs->cs_index);
		orion5x_pci_hw_rd_conf(bus, 0, func, reg, 4, &val);
		val = (cs->base & 0xfffff000) | (val & 0xfff);
		orion5x_pci_hw_wr_conf(bus, 0, func, reg, 4, val);

		/*
		 * Write DRAM bank size रेजिस्टर.
		 */
		reg = PCI_CONF_REG_BAR_HI_CS(cs->cs_index);
		orion5x_pci_hw_wr_conf(bus, 0, func, reg, 4, 0);
		ग_लिखोl((cs->size - 1) & 0xfffff000,
			PCI_BAR_SIZE_DDR_CS(cs->cs_index));
		ग_लिखोl(cs->base & 0xfffff000,
			PCI_BAR_REMAP_DDR_CS(cs->cs_index));

		/*
		 * Enable decode winकरोw क्रम this chip select.
		 */
		win_enable &= ~(1 << cs->cs_index);
	पूर्ण

	/*
	 * Re-enable decode winकरोws.
	 */
	ग_लिखोl(win_enable, PCI_BAR_ENABLE);

	/*
	 * Disable स्वतःmatic update of address remapping when writing to BARs.
	 */
	orion5x_setbits(PCI_ADDR_DECODE_CTRL, 1);
पूर्ण

अटल पूर्णांक __init pci_setup(काष्ठा pci_sys_data *sys)
अणु
	काष्ठा resource *res;

	/*
	 * Poपूर्णांक PCI unit MBUS decode winकरोws to DRAM space.
	 */
	orion5x_setup_pci_wins();

	/*
	 * Master + Slave enable
	 */
	orion5x_pci_master_slave_enable();

	/*
	 * Force ordering
	 */
	orion5x_setbits(PCI_CMD, PCI_CMD_HOST_REORDER);

	pci_ioremap_io(sys->busnr * SZ_64K, ORION5X_PCI_IO_PHYS_BASE);

	/*
	 * Request resources
	 */
	res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
	अगर (!res)
		panic("pci_setup unable to alloc resources");

	/*
	 * IORESOURCE_MEM
	 */
	res->name = "PCI Memory Space";
	res->flags = IORESOURCE_MEM;
	res->start = ORION5X_PCI_MEM_PHYS_BASE;
	res->end = res->start + ORION5X_PCI_MEM_SIZE - 1;
	अगर (request_resource(&iomem_resource, res))
		panic("Request PCI Memory resource failed\n");
	pci_add_resource_offset(&sys->resources, res, sys->mem_offset);

	वापस 1;
पूर्ण


/*****************************************************************************
 * General PCIe + PCI
 ****************************************************************************/
अटल व्योम rc_pci_fixup(काष्ठा pci_dev *dev)
अणु
	/*
	 * Prevent क्रमागतeration of root complex.
	 */
	अगर (dev->bus->parent == शून्य && dev->devfn == 0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
			dev->resource[i].start = 0;
			dev->resource[i].end   = 0;
			dev->resource[i].flags = 0;
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL, PCI_ANY_ID, rc_pci_fixup);

अटल पूर्णांक orion5x_pci_disabled __initdata;

व्योम __init orion5x_pci_disable(व्योम)
अणु
	orion5x_pci_disabled = 1;
पूर्ण

व्योम __init orion5x_pci_set_cardbus_mode(व्योम)
अणु
	orion5x_pci_cardbus_mode = 1;
पूर्ण

पूर्णांक __init orion5x_pci_sys_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys)
अणु
	vga_base = ORION5X_PCIE_MEM_PHYS_BASE;

	अगर (nr == 0) अणु
		orion_pcie_set_local_bus_nr(PCIE_BASE, sys->busnr);
		वापस pcie_setup(sys);
	पूर्ण

	अगर (nr == 1 && !orion5x_pci_disabled) अणु
		orion5x_pci_set_bus_nr(sys->busnr);
		वापस pci_setup(sys);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init orion5x_pci_sys_scan_bus(पूर्णांक nr, काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा pci_sys_data *sys = pci_host_bridge_priv(bridge);

	list_splice_init(&sys->resources, &bridge->winकरोws);
	bridge->dev.parent = शून्य;
	bridge->sysdata = sys;
	bridge->busnr = sys->busnr;

	अगर (nr == 0) अणु
		bridge->ops = &pcie_ops;
		वापस pci_scan_root_bus_bridge(bridge);
	पूर्ण

	अगर (nr == 1 && !orion5x_pci_disabled) अणु
		bridge->ops = &pci_ops;
		वापस pci_scan_root_bus_bridge(bridge);
	पूर्ण

	BUG();
	वापस -ENODEV;
पूर्ण

पूर्णांक __init orion5x_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक bus = dev->bus->number;

	/*
	 * PCIe endpoपूर्णांक?
	 */
	अगर (orion5x_pci_disabled || bus < orion5x_pci_local_bus_nr())
		वापस IRQ_ORION5X_PCIE0_INT;

	वापस -1;
पूर्ण
