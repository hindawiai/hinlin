<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
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
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
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
#समावेश <linux/pci_regs.h>

#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/netlogic/पूर्णांकerrupt.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>

#समावेश <यंत्र/netlogic/xlr/msidef.h>
#समावेश <यंत्र/netlogic/xlr/iomap.h>
#समावेश <यंत्र/netlogic/xlr/pic.h>
#समावेश <यंत्र/netlogic/xlr/xlr.h>

अटल व्योम *pci_config_base;

#घोषणा pci_cfg_addr(bus, devfn, off) (((bus) << 16) | ((devfn) << 8) | (off))

/* PCI ops */
अटल अंतरभूत u32 pci_cfg_पढ़ो_32bit(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where)
अणु
	u32 data;
	u32 *cfgaddr;

	cfgaddr = (u32 *)(pci_config_base +
			pci_cfg_addr(bus->number, devfn, where & ~3));
	data = *cfgaddr;
	वापस cpu_to_le32(data);
पूर्ण

अटल अंतरभूत व्योम pci_cfg_ग_लिखो_32bit(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, u32 data)
अणु
	u32 *cfgaddr;

	cfgaddr = (u32 *)(pci_config_base +
			pci_cfg_addr(bus->number, devfn, where & ~3));
	*cfgaddr = cpu_to_le32(data);
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
	.name		= "XLR PCI MEM",
	.start		= 0xd0000000UL, /* 256MB PCI mem @ 0xd000_0000 */
	.end		= 0xdfffffffUL,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource nlm_pci_io_resource = अणु
	.name		= "XLR IO MEM",
	.start		= 0x10000000UL, /* 16MB PCI IO @ 0x1000_0000 */
	.end		= 0x100fffffUL,
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

/*
 * The top level PCIe links on the XLS PCIe controller appear as
 * bridges. Given a device, this function finds which link it is
 * on.
 */
अटल काष्ठा pci_dev *xls_get_pcie_link(स्थिर काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus, *p;

	/* Find the bridge on bus 0 */
	bus = dev->bus;
	क्रम (p = bus->parent; p && p->number != 0; p = p->parent)
		bus = p;

	वापस p ? bus->self : शून्य;
पूर्ण

अटल पूर्णांक nlm_pci_link_to_irq(पूर्णांक link)
अणु
	चयन	(link) अणु
	हाल 0:
		वापस PIC_PCIE_LINK0_IRQ;
	हाल 1:
		वापस PIC_PCIE_LINK1_IRQ;
	हाल 2:
		अगर (nlm_chip_is_xls_b())
			वापस PIC_PCIE_XLSB0_LINK2_IRQ;
		अन्यथा
			वापस PIC_PCIE_LINK2_IRQ;
	हाल 3:
		अगर (nlm_chip_is_xls_b())
			वापस PIC_PCIE_XLSB0_LINK3_IRQ;
		अन्यथा
			वापस PIC_PCIE_LINK3_IRQ;
	पूर्ण
	WARN(1, "Unexpected link %d\n", link);
	वापस 0;
पूर्ण

अटल पूर्णांक get_irq_vector(स्थिर काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *lnk;
	पूर्णांक link;

	अगर (!nlm_chip_is_xls())
		वापस	PIC_PCIX_IRQ;	/* क्रम XLR just one IRQ */

	lnk = xls_get_pcie_link(dev);
	अगर (lnk == शून्य)
		वापस 0;

	link = PCI_SLOT(lnk->devfn);
	वापस nlm_pci_link_to_irq(link);
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
व्योम arch_tearकरोwn_msi_irq(अचिन्हित पूर्णांक irq)
अणु
पूर्ण

पूर्णांक arch_setup_msi_irq(काष्ठा pci_dev *dev, काष्ठा msi_desc *desc)
अणु
	काष्ठा msi_msg msg;
	काष्ठा pci_dev *lnk;
	पूर्णांक irq, ret;
	u16 val;

	/* MSI not supported on XLR */
	अगर (!nlm_chip_is_xls())
		वापस 1;

	/*
	 * Enable MSI on the XLS PCIe controller bridge which was disabled
	 * at क्रमागतeration, the bridge MSI capability is at 0x50
	 */
	lnk = xls_get_pcie_link(dev);
	अगर (lnk == शून्य)
		वापस 1;

	pci_पढ़ो_config_word(lnk, 0x50 + PCI_MSI_FLAGS, &val);
	अगर ((val & PCI_MSI_FLAGS_ENABLE) == 0) अणु
		val |= PCI_MSI_FLAGS_ENABLE;
		pci_ग_लिखो_config_word(lnk, 0x50 + PCI_MSI_FLAGS, val);
	पूर्ण

	irq = get_irq_vector(dev);
	अगर (irq <= 0)
		वापस 1;

	msg.address_hi = MSI_ADDR_BASE_HI;
	msg.address_lo = MSI_ADDR_BASE_LO   |
		MSI_ADDR_DEST_MODE_PHYSICAL |
		MSI_ADDR_REसूचीECTION_CPU;

	msg.data = MSI_DATA_TRIGGER_EDGE |
		MSI_DATA_LEVEL_ASSERT	 |
		MSI_DATA_DELIVERY_FIXED;

	ret = irq_set_msi_desc(irq, desc);
	अगर (ret < 0)
		वापस ret;

	pci_ग_लिखो_msi_msg(irq, &msg);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Extra ACK needed क्रम XLR on chip PCI controller */
अटल व्योम xlr_pci_ack(काष्ठा irq_data *d)
अणु
	uपूर्णांक64_t pcibase = nlm_mmio_base(NETLOGIC_IO_PCIX_OFFSET);

	nlm_पढ़ो_reg(pcibase, (0x140 >> 2));
पूर्ण

/* Extra ACK needed क्रम XLS on chip PCIe controller */
अटल व्योम xls_pcie_ack(काष्ठा irq_data *d)
अणु
	uपूर्णांक64_t pciebase_le = nlm_mmio_base(NETLOGIC_IO_PCIE_1_OFFSET);

	चयन (d->irq) अणु
	हाल PIC_PCIE_LINK0_IRQ:
		nlm_ग_लिखो_reg(pciebase_le, (0x90 >> 2), 0xffffffff);
		अवरोध;
	हाल PIC_PCIE_LINK1_IRQ:
		nlm_ग_लिखो_reg(pciebase_le, (0x94 >> 2), 0xffffffff);
		अवरोध;
	हाल PIC_PCIE_LINK2_IRQ:
		nlm_ग_लिखो_reg(pciebase_le, (0x190 >> 2), 0xffffffff);
		अवरोध;
	हाल PIC_PCIE_LINK3_IRQ:
		nlm_ग_लिखो_reg(pciebase_le, (0x194 >> 2), 0xffffffff);
		अवरोध;
	पूर्ण
पूर्ण

/* For XLS B silicon, the 3,4 PCI पूर्णांकerrupts are dअगरferent */
अटल व्योम xls_pcie_ack_b(काष्ठा irq_data *d)
अणु
	uपूर्णांक64_t pciebase_le = nlm_mmio_base(NETLOGIC_IO_PCIE_1_OFFSET);

	चयन (d->irq) अणु
	हाल PIC_PCIE_LINK0_IRQ:
		nlm_ग_लिखो_reg(pciebase_le, (0x90 >> 2), 0xffffffff);
		अवरोध;
	हाल PIC_PCIE_LINK1_IRQ:
		nlm_ग_लिखो_reg(pciebase_le, (0x94 >> 2), 0xffffffff);
		अवरोध;
	हाल PIC_PCIE_XLSB0_LINK2_IRQ:
		nlm_ग_लिखो_reg(pciebase_le, (0x190 >> 2), 0xffffffff);
		अवरोध;
	हाल PIC_PCIE_XLSB0_LINK3_IRQ:
		nlm_ग_लिखो_reg(pciebase_le, (0x194 >> 2), 0xffffffff);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	वापस get_irq_vector(dev);
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	व्योम (*extra_ack)(काष्ठा irq_data *);
	पूर्णांक link, irq;

	/* PSB assigns PCI resources */
	pci_set_flags(PCI_PROBE_ONLY);
	pci_config_base = ioremap(DEFAULT_PCI_CONFIG_BASE, 16 << 20);

	/* Extend IO port क्रम memory mapped io */
	ioport_resource.start =	 0;
	ioport_resource.end   = ~0;

	set_io_port_base(CKSEG1);
	nlm_pci_controller.io_map_base = CKSEG1;

	pr_info("Registering XLR/XLS PCIX/PCIE Controller.\n");
	रेजिस्टर_pci_controller(&nlm_pci_controller);

	/*
	 * For PCI पूर्णांकerrupts, we need to ack the PCI controller too, overload
	 * irq handler data to करो this
	 */
	अगर (!nlm_chip_is_xls()) अणु
		/* XLR PCI controller ACK */
		nlm_set_pic_extra_ack(0, PIC_PCIX_IRQ, xlr_pci_ack);
	पूर्ण अन्यथा अणु
		अगर  (nlm_chip_is_xls_b())
			extra_ack = xls_pcie_ack_b;
		अन्यथा
			extra_ack = xls_pcie_ack;
		क्रम (link = 0; link < 4; link++) अणु
			irq = nlm_pci_link_to_irq(link);
			nlm_set_pic_extra_ack(0, irq, extra_ack);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

arch_initcall(pcibios_init);
