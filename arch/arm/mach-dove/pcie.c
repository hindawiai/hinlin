<शैली गुरु>
/*
 * arch/arm/mach-करोve/pcie.c
 *
 * PCIe functions क्रम Marvell Dove 88AP510 SoC
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/clk.h>
#समावेश <video/vga.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/delay.h>
#समावेश <plat/pcie.h>
#समावेश <plat/addr-map.h>
#समावेश "irqs.h"
#समावेश "bridge-regs.h"
#समावेश "common.h"

काष्ठा pcie_port अणु
	u8			index;
	u8			root_bus_nr;
	व्योम __iomem		*base;
	spinlock_t		conf_lock;
	अक्षर			mem_space_name[16];
	काष्ठा resource		res;
पूर्ण;

अटल काष्ठा pcie_port pcie_port[2];
अटल पूर्णांक num_pcie_ports;


अटल पूर्णांक __init करोve_pcie_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys)
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

	अगर (pp->index == 0)
		pci_ioremap_io(sys->busnr * SZ_64K, DOVE_PCIE0_IO_PHYS_BASE);
	अन्यथा
		pci_ioremap_io(sys->busnr * SZ_64K, DOVE_PCIE1_IO_PHYS_BASE);

	/*
	 * IORESOURCE_MEM
	 */
	snम_लिखो(pp->mem_space_name, माप(pp->mem_space_name),
		 "PCIe %d MEM", pp->index);
	pp->mem_space_name[माप(pp->mem_space_name) - 1] = 0;
	pp->res.name = pp->mem_space_name;
	अगर (pp->index == 0) अणु
		pp->res.start = DOVE_PCIE0_MEM_PHYS_BASE;
		pp->res.end = pp->res.start + DOVE_PCIE0_MEM_SIZE - 1;
	पूर्ण अन्यथा अणु
		pp->res.start = DOVE_PCIE1_MEM_PHYS_BASE;
		pp->res.end = pp->res.start + DOVE_PCIE1_MEM_SIZE - 1;
	पूर्ण
	pp->res.flags = IORESOURCE_MEM;
	अगर (request_resource(&iomem_resource, &pp->res))
		panic("Request PCIe Memory resource failed\n");
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

अटल पूर्णांक __init
करोve_pcie_scan_bus(पूर्णांक nr, काष्ठा pci_host_bridge *bridge)
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

अटल पूर्णांक __init करोve_pcie_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा pci_sys_data *sys = dev->sysdata;
	काष्ठा pcie_port *pp = sys->निजी_data;

	वापस pp->index ? IRQ_DOVE_PCIE1 : IRQ_DOVE_PCIE0;
पूर्ण

अटल काष्ठा hw_pci करोve_pci __initdata = अणु
	.nr_controllers	= 2,
	.setup		= करोve_pcie_setup,
	.scan		= करोve_pcie_scan_bus,
	.map_irq	= करोve_pcie_map_irq,
पूर्ण;

अटल व्योम __init add_pcie_port(पूर्णांक index, व्योम __iomem *base)
अणु
	prपूर्णांकk(KERN_INFO "Dove PCIe port %d: ", index);

	अगर (orion_pcie_link_up(base)) अणु
		काष्ठा pcie_port *pp = &pcie_port[num_pcie_ports++];
		काष्ठा clk *clk = clk_get_sys("pcie", (index ? "1" : "0"));

		अगर (!IS_ERR(clk))
			clk_prepare_enable(clk);

		prपूर्णांकk(KERN_INFO "link up\n");

		pp->index = index;
		pp->root_bus_nr = -1;
		pp->base = base;
		spin_lock_init(&pp->conf_lock);
		स_रखो(&pp->res, 0, माप(pp->res));
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "link down, ignoring\n");
	पूर्ण
पूर्ण

व्योम __init करोve_pcie_init(पूर्णांक init_port0, पूर्णांक init_port1)
अणु
	vga_base = DOVE_PCIE0_MEM_PHYS_BASE;

	अगर (init_port0)
		add_pcie_port(0, DOVE_PCIE0_VIRT_BASE);

	अगर (init_port1)
		add_pcie_port(1, DOVE_PCIE1_VIRT_BASE);

	pci_common_init(&करोve_pci);
पूर्ण
