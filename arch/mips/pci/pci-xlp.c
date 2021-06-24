<शैली गुरु>
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the Broadcom
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY BROADCOM ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BROADCOM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/msi.h>
#समावेश <linux/mm.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/console.h>

#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/netlogic/पूर्णांकerrupt.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/mips-extns.h>

#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/pic.h>
#समावेश <यंत्र/netlogic/xlp-hal/pcibus.h>
#समावेश <यंत्र/netlogic/xlp-hal/bridge.h>

अटल व्योम *pci_config_base;

#घोषणा pci_cfg_addr(bus, devfn, off) (((bus) << 20) | ((devfn) << 12) | (off))

/* PCI ops */
अटल अंतरभूत u32 pci_cfg_पढ़ो_32bit(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where)
अणु
	u32 data;
	u32 *cfgaddr;

	where &= ~3;
	अगर (cpu_is_xlp9xx()) अणु
		/* be very careful on SoC buses */
		अगर (bus->number == 0) अणु
			/* Scan only existing nodes - uboot bug? */
			अगर (PCI_SLOT(devfn) != 0 ||
					   !nlm_node_present(PCI_FUNC(devfn)))
				वापस 0xffffffff;
		पूर्ण अन्यथा अगर (bus->parent->number == 0) अणु	/* SoC bus */
			अगर (PCI_SLOT(devfn) == 0)	/* b.0.0 hangs */
				वापस 0xffffffff;
			अगर (devfn == 44)		/* b.5.4 hangs */
				वापस 0xffffffff;
		पूर्ण
	पूर्ण अन्यथा अगर (bus->number == 0 && PCI_SLOT(devfn) == 1 && where == 0x954) अणु
		वापस 0xffffffff;
	पूर्ण
	cfgaddr = (u32 *)(pci_config_base +
			pci_cfg_addr(bus->number, devfn, where));
	data = *cfgaddr;
	वापस data;
पूर्ण

अटल अंतरभूत व्योम pci_cfg_ग_लिखो_32bit(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, u32 data)
अणु
	u32 *cfgaddr;

	cfgaddr = (u32 *)(pci_config_base +
			pci_cfg_addr(bus->number, devfn, where & ~3));
	*cfgaddr = data;
पूर्ण

अटल पूर्णांक nlm_pcibios_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	u32 data;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	data = pci_cfg_पढ़ो_32bit(bus, devfn, where);

	अगर (size == 1)
		*val = (data >> ((where & 3) << 3)) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (data >> ((where & 3) << 3)) & 0xffff;
	अन्यथा
		*val = data;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण


अटल पूर्णांक nlm_pcibios_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
		पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 data;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	data = pci_cfg_पढ़ो_32bit(bus, devfn, where);

	अगर (size == 1)
		data = (data & ~(0xff << ((where & 3) << 3))) |
			(val << ((where & 3) << 3));
	अन्यथा अगर (size == 2)
		data = (data & ~(0xffff << ((where & 3) << 3))) |
			(val << ((where & 3) << 3));
	अन्यथा
		data = val;

	pci_cfg_ग_लिखो_32bit(bus, devfn, where, data);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops nlm_pci_ops = अणु
	.पढ़ो  = nlm_pcibios_पढ़ो,
	.ग_लिखो = nlm_pcibios_ग_लिखो
पूर्ण;

अटल काष्ठा resource nlm_pci_mem_resource = अणु
	.name		= "XLP PCI MEM",
	.start		= 0xd0000000UL, /* 256MB PCI mem @ 0xd000_0000 */
	.end		= 0xdfffffffUL,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource nlm_pci_io_resource = अणु
	.name		= "XLP IO MEM",
	.start		= 0x14000000UL, /* 64MB PCI IO @ 0x1000_0000 */
	.end		= 0x17ffffffUL,
	.flags		= IORESOURCE_IO,
पूर्ण;

काष्ठा pci_controller nlm_pci_controller = अणु
	.index		= 0,
	.pci_ops	= &nlm_pci_ops,
	.mem_resource	= &nlm_pci_mem_resource,
	.mem_offset	= 0x00000000UL,
	.io_resource	= &nlm_pci_io_resource,
	.io_offset	= 0x00000000UL,
पूर्ण;

काष्ठा pci_dev *xlp_get_pcie_link(स्थिर काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus, *p;

	bus = dev->bus;

	अगर (cpu_is_xlp9xx()) अणु
		/* find bus with gअक्रम parent number == 0 */
		क्रम (p = bus->parent; p && p->parent && p->parent->number != 0;
				p = p->parent)
			bus = p;
		वापस (p && p->parent) ? bus->self : शून्य;
	पूर्ण अन्यथा अणु
		/* Find the bridge on bus 0 */
		क्रम (p = bus->parent; p && p->number != 0; p = p->parent)
			bus = p;

		वापस p ? bus->self : शून्य;
	पूर्ण
पूर्ण

पूर्णांक xlp_socdev_to_node(स्थिर काष्ठा pci_dev *lnkdev)
अणु
	अगर (cpu_is_xlp9xx())
		वापस PCI_FUNC(lnkdev->bus->self->devfn);
	अन्यथा
		वापस PCI_SLOT(lnkdev->devfn) / 8;
पूर्ण

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा pci_dev *lnkdev;
	पूर्णांक lnkfunc, node;

	/*
	 * For XLP PCIe, there is an IRQ per Link, find out which
	 * link the device is on to assign पूर्णांकerrupts
	*/
	lnkdev = xlp_get_pcie_link(dev);
	अगर (lnkdev == शून्य)
		वापस 0;

	lnkfunc = PCI_FUNC(lnkdev->devfn);
	node = xlp_socdev_to_node(lnkdev);

	वापस nlm_irq_to_xirq(node, PIC_PCIE_LINK_LEGACY_IRQ(lnkfunc));
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

/*
 * If big-endian, enable hardware byteswap on the PCIe bridges.
 * This will make both the SoC and PCIe devices behave consistently with
 * पढ़ोl/ग_लिखोl.
 */
#अगर_घोषित __BIG_ENDIAN
अटल व्योम xlp_config_pci_bswap(पूर्णांक node, पूर्णांक link)
अणु
	uपूर्णांक64_t nbubase, lnkbase;
	u32 reg;

	nbubase = nlm_get_bridge_regbase(node);
	lnkbase = nlm_get_pcie_base(node, link);

	/*
	 *  Enable byte swap in hardware. Program each link's PCIe SWAP regions
	 * from the link's address ranges.
	 */
	अगर (cpu_is_xlp9xx()) अणु
		reg = nlm_पढ़ो_bridge_reg(nbubase,
				BRIDGE_9XX_PCIEMEM_BASE0 + link);
		nlm_ग_लिखो_pci_reg(lnkbase, PCIE_9XX_BYTE_SWAP_MEM_BASE, reg);

		reg = nlm_पढ़ो_bridge_reg(nbubase,
				BRIDGE_9XX_PCIEMEM_LIMIT0 + link);
		nlm_ग_लिखो_pci_reg(lnkbase,
				PCIE_9XX_BYTE_SWAP_MEM_LIM, reg | 0xfff);

		reg = nlm_पढ़ो_bridge_reg(nbubase,
				BRIDGE_9XX_PCIEIO_BASE0 + link);
		nlm_ग_लिखो_pci_reg(lnkbase, PCIE_9XX_BYTE_SWAP_IO_BASE, reg);

		reg = nlm_पढ़ो_bridge_reg(nbubase,
				BRIDGE_9XX_PCIEIO_LIMIT0 + link);
		nlm_ग_लिखो_pci_reg(lnkbase,
				PCIE_9XX_BYTE_SWAP_IO_LIM, reg | 0xfff);
	पूर्ण अन्यथा अणु
		reg = nlm_पढ़ो_bridge_reg(nbubase, BRIDGE_PCIEMEM_BASE0 + link);
		nlm_ग_लिखो_pci_reg(lnkbase, PCIE_BYTE_SWAP_MEM_BASE, reg);

		reg = nlm_पढ़ो_bridge_reg(nbubase,
					BRIDGE_PCIEMEM_LIMIT0 + link);
		nlm_ग_लिखो_pci_reg(lnkbase, PCIE_BYTE_SWAP_MEM_LIM, reg | 0xfff);

		reg = nlm_पढ़ो_bridge_reg(nbubase, BRIDGE_PCIEIO_BASE0 + link);
		nlm_ग_लिखो_pci_reg(lnkbase, PCIE_BYTE_SWAP_IO_BASE, reg);

		reg = nlm_पढ़ो_bridge_reg(nbubase, BRIDGE_PCIEIO_LIMIT0 + link);
		nlm_ग_लिखो_pci_reg(lnkbase, PCIE_BYTE_SWAP_IO_LIM, reg | 0xfff);
	पूर्ण
पूर्ण
#अन्यथा
/* Swap configuration not needed in little-endian mode */
अटल अंतरभूत व्योम xlp_config_pci_bswap(पूर्णांक node, पूर्णांक link) अणुपूर्ण
#पूर्ण_अगर /* __BIG_ENDIAN */

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	uपूर्णांक64_t pciebase;
	पूर्णांक link, n;
	u32 reg;

	/* Firmware assigns PCI resources */
	pci_set_flags(PCI_PROBE_ONLY);
	pci_config_base = ioremap(XLP_DEFAULT_PCI_ECFG_BASE, 64 << 20);

	/* Extend IO port क्रम memory mapped io */
	ioport_resource.start =	 0;
	ioport_resource.end   = ~0;

	क्रम (n = 0; n < NLM_NR_NODES; n++) अणु
		अगर (!nlm_node_present(n))
			जारी;

		क्रम (link = 0; link < PCIE_NLINKS; link++) अणु
			pciebase = nlm_get_pcie_base(n, link);
			अगर (nlm_पढ़ो_pci_reg(pciebase, 0) == 0xffffffff)
				जारी;
			xlp_config_pci_bswap(n, link);
			xlp_init_node_msi_irqs(n, link);

			/* put in पूर्णांकpin and irq - u-boot करोes not */
			reg = nlm_पढ़ो_pci_reg(pciebase, 0xf);
			reg &= ~0x1ffu;
			reg |= (1 << 8) | PIC_PCIE_LINK_LEGACY_IRQ(link);
			nlm_ग_लिखो_pci_reg(pciebase, 0xf, reg);
			pr_info("XLP PCIe: Link %d-%d initialized.\n", n, link);
		पूर्ण
	पूर्ण

	set_io_port_base(CKSEG1);
	nlm_pci_controller.io_map_base = CKSEG1;

	रेजिस्टर_pci_controller(&nlm_pci_controller);
	pr_info("XLP PCIe Controller %pR%pR.\n", &nlm_pci_io_resource,
		&nlm_pci_mem_resource);

	वापस 0;
पूर्ण
arch_initcall(pcibios_init);
