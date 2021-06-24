<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCI-E support क्रम CNS3xxx
 *
 * Copyright 2008 Cavium Networks
 *		  Riअक्षरd Liu <riअक्षरd.liu@caviumnetworks.com>
 * Copyright 2010 MontaVista Software, LLC.
 *		  Anton Vorontsov <avorontsov@mvista.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <यंत्र/mach/map.h>
#समावेश "cns3xxx.h"
#समावेश "core.h"

काष्ठा cns3xxx_pcie अणु
	व्योम __iomem *host_regs; /* PCI config रेजिस्टरs क्रम host bridge */
	व्योम __iomem *cfg0_regs; /* PCI Type 0 config रेजिस्टरs */
	व्योम __iomem *cfg1_regs; /* PCI Type 1 config रेजिस्टरs */
	अचिन्हित पूर्णांक irqs[2];
	काष्ठा resource res_io;
	काष्ठा resource res_mem;
	पूर्णांक port;
	bool linked;
पूर्ण;

अटल काष्ठा cns3xxx_pcie *sysdata_to_cnspci(व्योम *sysdata)
अणु
	काष्ठा pci_sys_data *root = sysdata;

	वापस root->निजी_data;
पूर्ण

अटल काष्ठा cns3xxx_pcie *pdev_to_cnspci(स्थिर काष्ठा pci_dev *dev)
अणु
	वापस sysdata_to_cnspci(dev->sysdata);
पूर्ण

अटल काष्ठा cns3xxx_pcie *pbus_to_cnspci(काष्ठा pci_bus *bus)
अणु
	वापस sysdata_to_cnspci(bus->sysdata);
पूर्ण

अटल व्योम __iomem *cns3xxx_pci_map_bus(काष्ठा pci_bus *bus,
					 अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा cns3xxx_pcie *cnspci = pbus_to_cnspci(bus);
	पूर्णांक busno = bus->number;
	पूर्णांक slot = PCI_SLOT(devfn);
	व्योम __iomem *base;

	/* If there is no link, just show the CNS PCI bridge. */
	अगर (!cnspci->linked && busno > 0)
		वापस शून्य;

	/*
	 * The CNS PCI bridge करोesn't fit पूर्णांकo the PCI hierarchy, though
	 * we still want to access it.
	 * We place the host bridge on bus 0, and the directly connected
	 * device on bus 1, slot 0.
	 */
	अगर (busno == 0) अणु /* पूर्णांकernal PCIe bus, host bridge device */
		अगर (devfn == 0) /* device# and function# are ignored by hw */
			base = cnspci->host_regs;
		अन्यथा
			वापस शून्य; /* no such device */

	पूर्ण अन्यथा अगर (busno == 1) अणु /* directly connected PCIe device */
		अगर (slot == 0) /* device# is ignored by hw */
			base = cnspci->cfg0_regs;
		अन्यथा
			वापस शून्य; /* no such device */
	पूर्ण अन्यथा /* remote PCI bus */
		base = cnspci->cfg1_regs + ((busno & 0xf) << 20);

	वापस base + where + (devfn << 12);
पूर्ण

अटल पूर्णांक cns3xxx_pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	पूर्णांक ret;
	u32 mask = (0x1ull << (size * 8)) - 1;
	पूर्णांक shअगरt = (where % 4) * 8;

	ret = pci_generic_config_पढ़ो(bus, devfn, where, size, val);

	अगर (ret == PCIBIOS_SUCCESSFUL && !bus->number && !devfn &&
	    (where & 0xffc) == PCI_CLASS_REVISION)
		/*
		 * RC's class is 0xb, but Linux PCI driver needs 0x604
		 * क्रम a PCIe bridge. So we must fixup the class code
		 * to 0x604 here.
		 */
		*val = ((((*val << shअगरt) & 0xff) | (0x604 << 16)) >> shअगरt) & mask;

	वापस ret;
पूर्ण

अटल पूर्णांक cns3xxx_pci_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys)
अणु
	काष्ठा cns3xxx_pcie *cnspci = sysdata_to_cnspci(sys);
	काष्ठा resource *res_io = &cnspci->res_io;
	काष्ठा resource *res_mem = &cnspci->res_mem;

	BUG_ON(request_resource(&iomem_resource, res_io) ||
	       request_resource(&iomem_resource, res_mem));

	pci_add_resource_offset(&sys->resources, res_io, sys->io_offset);
	pci_add_resource_offset(&sys->resources, res_mem, sys->mem_offset);

	वापस 1;
पूर्ण

अटल काष्ठा pci_ops cns3xxx_pcie_ops = अणु
	.map_bus = cns3xxx_pci_map_bus,
	.पढ़ो = cns3xxx_pci_पढ़ो_config,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

अटल पूर्णांक cns3xxx_pcie_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा cns3xxx_pcie *cnspci = pdev_to_cnspci(dev);
	पूर्णांक irq = cnspci->irqs[!!dev->bus->number];

	pr_info("PCIe map irq: %04d:%02x:%02x.%02x slot %d, pin %d, irq: %d\n",
		pci_करोमुख्य_nr(dev->bus), dev->bus->number, PCI_SLOT(dev->devfn),
		PCI_FUNC(dev->devfn), slot, pin, irq);

	वापस irq;
पूर्ण

अटल काष्ठा cns3xxx_pcie cns3xxx_pcie[] = अणु
	[0] = अणु
		.host_regs = (व्योम __iomem *)CNS3XXX_PCIE0_HOST_BASE_VIRT,
		.cfg0_regs = (व्योम __iomem *)CNS3XXX_PCIE0_CFG0_BASE_VIRT,
		.cfg1_regs = (व्योम __iomem *)CNS3XXX_PCIE0_CFG1_BASE_VIRT,
		.res_io = अणु
			.name = "PCIe0 I/O space",
			.start = CNS3XXX_PCIE0_IO_BASE,
			.end = CNS3XXX_PCIE0_CFG0_BASE - 1, /* 16 MiB */
			.flags = IORESOURCE_IO,
		पूर्ण,
		.res_mem = अणु
			.name = "PCIe0 non-prefetchable",
			.start = CNS3XXX_PCIE0_MEM_BASE,
			.end = CNS3XXX_PCIE0_HOST_BASE - 1, /* 176 MiB */
			.flags = IORESOURCE_MEM,
		पूर्ण,
		.irqs = अणु IRQ_CNS3XXX_PCIE0_RC, IRQ_CNS3XXX_PCIE0_DEVICE, पूर्ण,
		.port = 0,
	पूर्ण,
	[1] = अणु
		.host_regs = (व्योम __iomem *)CNS3XXX_PCIE1_HOST_BASE_VIRT,
		.cfg0_regs = (व्योम __iomem *)CNS3XXX_PCIE1_CFG0_BASE_VIRT,
		.cfg1_regs = (व्योम __iomem *)CNS3XXX_PCIE1_CFG1_BASE_VIRT,
		.res_io = अणु
			.name = "PCIe1 I/O space",
			.start = CNS3XXX_PCIE1_IO_BASE,
			.end = CNS3XXX_PCIE1_CFG0_BASE - 1, /* 16 MiB */
			.flags = IORESOURCE_IO,
		पूर्ण,
		.res_mem = अणु
			.name = "PCIe1 non-prefetchable",
			.start = CNS3XXX_PCIE1_MEM_BASE,
			.end = CNS3XXX_PCIE1_HOST_BASE - 1, /* 176 MiB */
			.flags = IORESOURCE_MEM,
		पूर्ण,
		.irqs = अणु IRQ_CNS3XXX_PCIE1_RC, IRQ_CNS3XXX_PCIE1_DEVICE, पूर्ण,
		.port = 1,
	पूर्ण,
पूर्ण;

अटल व्योम __init cns3xxx_pcie_check_link(काष्ठा cns3xxx_pcie *cnspci)
अणु
	पूर्णांक port = cnspci->port;
	u32 reg;
	अचिन्हित दीर्घ समय;

	reg = __raw_पढ़ोl(MISC_PCIE_CTRL(port));
	/*
	 * Enable Application Request to 1, it will निकास L1 स्वतःmatically,
	 * but when chip back, it will use another घड़ी, still can use 0x1.
	 */
	reg |= 0x3;
	__raw_ग_लिखोl(reg, MISC_PCIE_CTRL(port));

	pr_info("PCIe: Port[%d] Enable PCIe LTSSM\n", port);
	pr_info("PCIe: Port[%d] Check data link layer...", port);

	समय = jअगरfies;
	जबतक (1) अणु
		reg = __raw_पढ़ोl(MISC_PCIE_PM_DEBUG(port));
		अगर (reg & 0x1) अणु
			pr_info("Link up.\n");
			cnspci->linked = 1;
			अवरोध;
		पूर्ण अन्यथा अगर (समय_after(jअगरfies, समय + 50)) अणु
			pr_info("Device not found.\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cns3xxx_ग_लिखो_config(काष्ठा cns3xxx_pcie *cnspci,
					 पूर्णांक where, पूर्णांक size, u32 val)
अणु
	व्योम __iomem *base = cnspci->host_regs + (where & 0xffc);
	u32 v;
	u32 mask = (0x1ull << (size * 8)) - 1;
	पूर्णांक shअगरt = (where % 4) * 8;

	v = पढ़ोl_relaxed(base);

	v &= ~(mask << shअगरt);
	v |= (val & mask) << shअगरt;

	ग_लिखोl_relaxed(v, base);
	पढ़ोl_relaxed(base);
पूर्ण

अटल व्योम __init cns3xxx_pcie_hw_init(काष्ठा cns3xxx_pcie *cnspci)
अणु
	u16 mem_base  = cnspci->res_mem.start >> 16;
	u16 mem_limit = cnspci->res_mem.end   >> 16;
	u16 io_base   = cnspci->res_io.start  >> 16;
	u16 io_limit  = cnspci->res_io.end    >> 16;

	cns3xxx_ग_लिखो_config(cnspci, PCI_PRIMARY_BUS, 1, 0);
	cns3xxx_ग_लिखो_config(cnspci, PCI_SECONDARY_BUS, 1, 1);
	cns3xxx_ग_लिखो_config(cnspci, PCI_SUBORDINATE_BUS, 1, 1);
	cns3xxx_ग_लिखो_config(cnspci, PCI_MEMORY_BASE, 2, mem_base);
	cns3xxx_ग_लिखो_config(cnspci, PCI_MEMORY_LIMIT, 2, mem_limit);
	cns3xxx_ग_लिखो_config(cnspci, PCI_IO_BASE_UPPER16, 2, io_base);
	cns3xxx_ग_लिखो_config(cnspci, PCI_IO_LIMIT_UPPER16, 2, io_limit);

	अगर (!cnspci->linked)
		वापस;

	/* Set Device Max_Read_Request_Size to 128 byte */
	pcie_bus_config = PCIE_BUS_PEER2PEER;

	/* Disable PCIe0 Interrupt Mask INTA to INTD */
	__raw_ग_लिखोl(~0x3FFF, MISC_PCIE_INT_MASK(cnspci->port));
पूर्ण

अटल पूर्णांक cns3xxx_pcie_पात_handler(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
				      काष्ठा pt_regs *regs)
अणु
	अगर (fsr & (1 << 10))
		regs->ARM_pc += 4;
	वापस 0;
पूर्ण

व्योम __init cns3xxx_pcie_init_late(व्योम)
अणु
	पूर्णांक i;
	व्योम *निजी_data;
	काष्ठा hw_pci hw_pci = अणु
	       .nr_controllers = 1,
	       .ops = &cns3xxx_pcie_ops,
	       .setup = cns3xxx_pci_setup,
	       .map_irq = cns3xxx_pcie_map_irq,
	       .निजी_data = &निजी_data,
	पूर्ण;

	pcibios_min_io = 0;
	pcibios_min_mem = 0;

	hook_fault_code(16 + 6, cns3xxx_pcie_पात_handler, SIGBUS, 0,
			"imprecise external abort");

	क्रम (i = 0; i < ARRAY_SIZE(cns3xxx_pcie); i++) अणु
		cns3xxx_pwr_clk_en(0x1 << PM_CLK_GATE_REG_OFFSET_PCIE(i));
		cns3xxx_pwr_soft_rst(0x1 << PM_SOFT_RST_REG_OFFST_PCIE(i));
		cns3xxx_pcie_check_link(&cns3xxx_pcie[i]);
		cns3xxx_pcie_hw_init(&cns3xxx_pcie[i]);
		निजी_data = &cns3xxx_pcie[i];
		pci_common_init(&hw_pci);
	पूर्ण

	pci_assign_unasचिन्हित_resources();
पूर्ण
