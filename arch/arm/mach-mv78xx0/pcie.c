<शैली गुरु>
/*
 * arch/arm/mach-mv78xx0/pcie.c
 *
 * PCIe functions क्रम Marvell MV78xx0 SoCs
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/mbus.h>
#समावेश <video/vga.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <plat/pcie.h>
#समावेश "mv78xx0.h"
#समावेश "common.h"

#घोषणा MV78XX0_MBUS_PCIE_MEM_TARGET(port, lane) ((port) ? 8 : 4)
#घोषणा MV78XX0_MBUS_PCIE_MEM_ATTR(port, lane)   (0xf8 & ~(0x10 << (lane)))
#घोषणा MV78XX0_MBUS_PCIE_IO_TARGET(port, lane)  ((port) ? 8 : 4)
#घोषणा MV78XX0_MBUS_PCIE_IO_ATTR(port, lane)    (0xf0 & ~(0x10 << (lane)))

काष्ठा pcie_port अणु
	u8			maj;
	u8			min;
	u8			root_bus_nr;
	व्योम __iomem		*base;
	spinlock_t		conf_lock;
	अक्षर			mem_space_name[20];
	काष्ठा resource		res;
पूर्ण;

अटल काष्ठा pcie_port pcie_port[8];
अटल पूर्णांक num_pcie_ports;
अटल काष्ठा resource pcie_io_space;

व्योम __init mv78xx0_pcie_id(u32 *dev, u32 *rev)
अणु
	*dev = orion_pcie_dev_id(PCIE00_VIRT_BASE);
	*rev = orion_pcie_rev(PCIE00_VIRT_BASE);
पूर्ण

u32 pcie_port_size[8] = अणु
	0,
	0x30000000,
	0x10000000,
	0x10000000,
	0x08000000,
	0x08000000,
	0x08000000,
	0x04000000,
पूर्ण;

अटल व्योम __init mv78xx0_pcie_preinit(व्योम)
अणु
	पूर्णांक i;
	u32 size_each;
	u32 start;

	pcie_io_space.name = "PCIe I/O Space";
	pcie_io_space.start = MV78XX0_PCIE_IO_PHYS_BASE(0);
	pcie_io_space.end =
		MV78XX0_PCIE_IO_PHYS_BASE(0) + MV78XX0_PCIE_IO_SIZE * 8 - 1;
	pcie_io_space.flags = IORESOURCE_MEM;
	अगर (request_resource(&iomem_resource, &pcie_io_space))
		panic("can't allocate PCIe I/O space");

	अगर (num_pcie_ports > 7)
		panic("invalid number of PCIe ports");

	size_each = pcie_port_size[num_pcie_ports];

	start = MV78XX0_PCIE_MEM_PHYS_BASE;
	क्रम (i = 0; i < num_pcie_ports; i++) अणु
		काष्ठा pcie_port *pp = pcie_port + i;

		snम_लिखो(pp->mem_space_name, माप(pp->mem_space_name),
			"PCIe %d.%d MEM", pp->maj, pp->min);
		pp->mem_space_name[माप(pp->mem_space_name) - 1] = 0;
		pp->res.name = pp->mem_space_name;
		pp->res.flags = IORESOURCE_MEM;
		pp->res.start = start;
		pp->res.end = start + size_each - 1;
		start += size_each;

		अगर (request_resource(&iomem_resource, &pp->res))
			panic("can't allocate PCIe MEM sub-space");

		mvebu_mbus_add_winकरोw_by_id(MV78XX0_MBUS_PCIE_MEM_TARGET(pp->maj, pp->min),
					    MV78XX0_MBUS_PCIE_MEM_ATTR(pp->maj, pp->min),
					    pp->res.start, resource_size(&pp->res));
		mvebu_mbus_add_winकरोw_remap_by_id(MV78XX0_MBUS_PCIE_IO_TARGET(pp->maj, pp->min),
						  MV78XX0_MBUS_PCIE_IO_ATTR(pp->maj, pp->min),
						  i * SZ_64K, SZ_64K, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक __init mv78xx0_pcie_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys)
अणु
	काष्ठा pcie_port *pp;

	अगर (nr >= num_pcie_ports)
		वापस 0;

	pp = &pcie_port[nr];
	sys->निजी_data = pp;
	pp->root_bus_nr = sys->busnr;

	/*
	 * Generic PCIe unit setup.
	 */
	orion_pcie_set_local_bus_nr(pp->base, sys->busnr);
	orion_pcie_setup(pp->base);

	pci_ioremap_io(nr * SZ_64K, MV78XX0_PCIE_IO_PHYS_BASE(nr));

	pci_add_resource_offset(&sys->resources, &pp->res, sys->mem_offset);

	वापस 1;
पूर्ण

अटल पूर्णांक pcie_valid_config(काष्ठा pcie_port *pp, पूर्णांक bus, पूर्णांक dev)
अणु
	/*
	 * Don't go out when trying to access nonexisting devices
	 * on the local bus.
	 */
	अगर (bus == pp->root_bus_nr && dev > 1)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक pcie_rd_conf(काष्ठा pci_bus *bus, u32 devfn, पूर्णांक where,
			पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_sys_data *sys = bus->sysdata;
	काष्ठा pcie_port *pp = sys->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (pcie_valid_config(pp, bus->number, PCI_SLOT(devfn)) == 0) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	spin_lock_irqsave(&pp->conf_lock, flags);
	ret = orion_pcie_rd_conf(pp->base, bus, devfn, where, size, val);
	spin_unlock_irqrestore(&pp->conf_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक pcie_wr_conf(काष्ठा pci_bus *bus, u32 devfn,
			पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pci_sys_data *sys = bus->sysdata;
	काष्ठा pcie_port *pp = sys->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (pcie_valid_config(pp, bus->number, PCI_SLOT(devfn)) == 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	spin_lock_irqsave(&pp->conf_lock, flags);
	ret = orion_pcie_wr_conf(pp->base, bus, devfn, where, size, val);
	spin_unlock_irqrestore(&pp->conf_lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा pci_ops pcie_ops = अणु
	.पढ़ो = pcie_rd_conf,
	.ग_लिखो = pcie_wr_conf,
पूर्ण;

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

अटल पूर्णांक __init mv78xx0_pcie_scan_bus(पूर्णांक nr, काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा pci_sys_data *sys = pci_host_bridge_priv(bridge);

	अगर (nr >= num_pcie_ports) अणु
		BUG();
		वापस -EINVAL;
	पूर्ण

	list_splice_init(&sys->resources, &bridge->winकरोws);
	bridge->dev.parent = शून्य;
	bridge->sysdata = sys;
	bridge->busnr = sys->busnr;
	bridge->ops = &pcie_ops;

	वापस pci_scan_root_bus_bridge(bridge);
पूर्ण

अटल पूर्णांक __init mv78xx0_pcie_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
	u8 pin)
अणु
	काष्ठा pci_sys_data *sys = dev->bus->sysdata;
	काष्ठा pcie_port *pp = sys->निजी_data;

	वापस IRQ_MV78XX0_PCIE_00 + (pp->maj << 2) + pp->min;
पूर्ण

अटल काष्ठा hw_pci mv78xx0_pci __initdata = अणु
	.nr_controllers	= 8,
	.preinit	= mv78xx0_pcie_preinit,
	.setup		= mv78xx0_pcie_setup,
	.scan		= mv78xx0_pcie_scan_bus,
	.map_irq	= mv78xx0_pcie_map_irq,
पूर्ण;

अटल व्योम __init add_pcie_port(पूर्णांक maj, पूर्णांक min, व्योम __iomem *base)
अणु
	prपूर्णांकk(KERN_INFO "MV78xx0 PCIe port %d.%d: ", maj, min);

	अगर (orion_pcie_link_up(base)) अणु
		काष्ठा pcie_port *pp = &pcie_port[num_pcie_ports++];

		prपूर्णांकk("link up\n");

		pp->maj = maj;
		pp->min = min;
		pp->root_bus_nr = -1;
		pp->base = base;
		spin_lock_init(&pp->conf_lock);
		स_रखो(&pp->res, 0, माप(pp->res));
	पूर्ण अन्यथा अणु
		prपूर्णांकk("link down, ignoring\n");
	पूर्ण
पूर्ण

व्योम __init mv78xx0_pcie_init(पूर्णांक init_port0, पूर्णांक init_port1)
अणु
	vga_base = MV78XX0_PCIE_MEM_PHYS_BASE;

	अगर (init_port0) अणु
		add_pcie_port(0, 0, PCIE00_VIRT_BASE);
		अगर (!orion_pcie_x4_mode(PCIE00_VIRT_BASE)) अणु
			add_pcie_port(0, 1, PCIE01_VIRT_BASE);
			add_pcie_port(0, 2, PCIE02_VIRT_BASE);
			add_pcie_port(0, 3, PCIE03_VIRT_BASE);
		पूर्ण
	पूर्ण

	अगर (init_port1) अणु
		add_pcie_port(1, 0, PCIE10_VIRT_BASE);
		अगर (!orion_pcie_x4_mode((व्योम __iomem *)PCIE10_VIRT_BASE)) अणु
			add_pcie_port(1, 1, PCIE11_VIRT_BASE);
			add_pcie_port(1, 2, PCIE12_VIRT_BASE);
			add_pcie_port(1, 3, PCIE13_VIRT_BASE);
		पूर्ण
	पूर्ण

	pci_common_init(&mv78xx0_pci);
पूर्ण
