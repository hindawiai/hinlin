<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Ralink RT288x SoC PCI रेजिस्टर definitions
 *
 *  Copyright (C) 2009 John Crispin <john@phrozen.org>
 *  Copyright (C) 2009 Gabor Juhos <juhosg@खोलोwrt.org>
 *
 *  Parts of this file are based on Ralink's 2.6.21 BSP
 */

#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>

#समावेश <यंत्र/mach-ralink/rt288x.h>

#घोषणा RT2880_PCI_BASE		0x00440000
#घोषणा RT288X_CPU_IRQ_PCI	4

#घोषणा RT2880_PCI_MEM_BASE	0x20000000
#घोषणा RT2880_PCI_MEM_SIZE	0x10000000
#घोषणा RT2880_PCI_IO_BASE	0x00460000
#घोषणा RT2880_PCI_IO_SIZE	0x00010000

#घोषणा RT2880_PCI_REG_PCICFG_ADDR	0x00
#घोषणा RT2880_PCI_REG_PCIMSK_ADDR	0x0c
#घोषणा RT2880_PCI_REG_BAR0SETUP_ADDR	0x10
#घोषणा RT2880_PCI_REG_IMBASEBAR0_ADDR	0x18
#घोषणा RT2880_PCI_REG_CONFIG_ADDR	0x20
#घोषणा RT2880_PCI_REG_CONFIG_DATA	0x24
#घोषणा RT2880_PCI_REG_MEMBASE		0x28
#घोषणा RT2880_PCI_REG_IOBASE		0x2c
#घोषणा RT2880_PCI_REG_ID		0x30
#घोषणा RT2880_PCI_REG_CLASS		0x34
#घोषणा RT2880_PCI_REG_SUBID		0x38
#घोषणा RT2880_PCI_REG_ARBCTL		0x80

अटल व्योम __iomem *rt2880_pci_base;

अटल u32 rt2880_pci_reg_पढ़ो(u32 reg)
अणु
	वापस पढ़ोl(rt2880_pci_base + reg);
पूर्ण

अटल व्योम rt2880_pci_reg_ग_लिखो(u32 val, u32 reg)
अणु
	ग_लिखोl(val, rt2880_pci_base + reg);
पूर्ण

अटल अंतरभूत u32 rt2880_pci_get_cfgaddr(अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक slot,
					 अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक where)
अणु
	वापस ((bus << 16) | (slot << 11) | (func << 8) | (where & 0xfc) |
		0x80000000);
पूर्ण

अटल पूर्णांक rt2880_pci_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	u32 address;
	u32 data;

	address = rt2880_pci_get_cfgaddr(bus->number, PCI_SLOT(devfn),
					 PCI_FUNC(devfn), where);

	rt2880_pci_reg_ग_लिखो(address, RT2880_PCI_REG_CONFIG_ADDR);
	data = rt2880_pci_reg_पढ़ो(RT2880_PCI_REG_CONFIG_DATA);

	चयन (size) अणु
	हाल 1:
		*val = (data >> ((where & 3) << 3)) & 0xff;
		अवरोध;
	हाल 2:
		*val = (data >> ((where & 3) << 3)) & 0xffff;
		अवरोध;
	हाल 4:
		*val = data;
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rt2880_pci_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 address;
	u32 data;

	address = rt2880_pci_get_cfgaddr(bus->number, PCI_SLOT(devfn),
					 PCI_FUNC(devfn), where);

	rt2880_pci_reg_ग_लिखो(address, RT2880_PCI_REG_CONFIG_ADDR);
	data = rt2880_pci_reg_पढ़ो(RT2880_PCI_REG_CONFIG_DATA);

	चयन (size) अणु
	हाल 1:
		data = (data & ~(0xff << ((where & 3) << 3))) |
		       (val << ((where & 3) << 3));
		अवरोध;
	हाल 2:
		data = (data & ~(0xffff << ((where & 3) << 3))) |
		       (val << ((where & 3) << 3));
		अवरोध;
	हाल 4:
		data = val;
		अवरोध;
	पूर्ण

	rt2880_pci_reg_ग_लिखो(data, RT2880_PCI_REG_CONFIG_DATA);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops rt2880_pci_ops = अणु
	.पढ़ो	= rt2880_pci_config_पढ़ो,
	.ग_लिखो	= rt2880_pci_config_ग_लिखो,
पूर्ण;

अटल काष्ठा resource rt2880_pci_mem_resource = अणु
	.name	= "PCI MEM space",
	.start	= RT2880_PCI_MEM_BASE,
	.end	= RT2880_PCI_MEM_BASE + RT2880_PCI_MEM_SIZE - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource rt2880_pci_io_resource = अणु
	.name	= "PCI IO space",
	.start	= RT2880_PCI_IO_BASE,
	.end	= RT2880_PCI_IO_BASE + RT2880_PCI_IO_SIZE - 1,
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल काष्ठा pci_controller rt2880_pci_controller = अणु
	.pci_ops	= &rt2880_pci_ops,
	.mem_resource	= &rt2880_pci_mem_resource,
	.io_resource	= &rt2880_pci_io_resource,
पूर्ण;

अटल अंतरभूत u32 rt2880_pci_पढ़ो_u32(अचिन्हित दीर्घ reg)
अणु
	u32 address;
	u32 ret;

	address = rt2880_pci_get_cfgaddr(0, 0, 0, reg);

	rt2880_pci_reg_ग_लिखो(address, RT2880_PCI_REG_CONFIG_ADDR);
	ret = rt2880_pci_reg_पढ़ो(RT2880_PCI_REG_CONFIG_DATA);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rt2880_pci_ग_लिखो_u32(अचिन्हित दीर्घ reg, u32 val)
अणु
	u32 address;

	address = rt2880_pci_get_cfgaddr(0, 0, 0, reg);

	rt2880_pci_reg_ग_लिखो(address, RT2880_PCI_REG_CONFIG_ADDR);
	rt2880_pci_reg_ग_लिखो(val, RT2880_PCI_REG_CONFIG_DATA);
पूर्ण

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq = -1;

	अगर (dev->bus->number != 0)
		वापस irq;

	चयन (PCI_SLOT(dev->devfn)) अणु
	हाल 0x00:
		अवरोध;
	हाल 0x11:
		irq = RT288X_CPU_IRQ_PCI;
		अवरोध;
	शेष:
		pr_err("%s:%s[%d] trying to alloc unknown pci irq\n",
		       __खाता__, __func__, __LINE__);
		BUG();
		अवरोध;
	पूर्ण

	वापस irq;
पूर्ण

अटल पूर्णांक rt288x_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *io_map_base;

	rt2880_pci_base = ioremap(RT2880_PCI_BASE, PAGE_SIZE);

	io_map_base = ioremap(RT2880_PCI_IO_BASE, RT2880_PCI_IO_SIZE);
	rt2880_pci_controller.io_map_base = (अचिन्हित दीर्घ) io_map_base;
	set_io_port_base((अचिन्हित दीर्घ) io_map_base);

	ioport_resource.start = RT2880_PCI_IO_BASE;
	ioport_resource.end = RT2880_PCI_IO_BASE + RT2880_PCI_IO_SIZE - 1;

	rt2880_pci_reg_ग_लिखो(0, RT2880_PCI_REG_PCICFG_ADDR);
	udelay(1);

	rt2880_pci_reg_ग_लिखो(0x79, RT2880_PCI_REG_ARBCTL);
	rt2880_pci_reg_ग_लिखो(0x07FF0001, RT2880_PCI_REG_BAR0SETUP_ADDR);
	rt2880_pci_reg_ग_लिखो(RT2880_PCI_MEM_BASE, RT2880_PCI_REG_MEMBASE);
	rt2880_pci_reg_ग_लिखो(RT2880_PCI_IO_BASE, RT2880_PCI_REG_IOBASE);
	rt2880_pci_reg_ग_लिखो(0x08000000, RT2880_PCI_REG_IMBASEBAR0_ADDR);
	rt2880_pci_reg_ग_लिखो(0x08021814, RT2880_PCI_REG_ID);
	rt2880_pci_reg_ग_लिखो(0x00800001, RT2880_PCI_REG_CLASS);
	rt2880_pci_reg_ग_लिखो(0x28801814, RT2880_PCI_REG_SUBID);
	rt2880_pci_reg_ग_लिखो(0x000c0000, RT2880_PCI_REG_PCIMSK_ADDR);

	rt2880_pci_ग_लिखो_u32(PCI_BASE_ADDRESS_0, 0x08000000);
	(व्योम) rt2880_pci_पढ़ो_u32(PCI_BASE_ADDRESS_0);

	rt2880_pci_controller.of_node = pdev->dev.of_node;

	रेजिस्टर_pci_controller(&rt2880_pci_controller);
	वापस 0;
पूर्ण

पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	अटल bool slot0_init;

	/*
	 * Nobody seems to initialize slot 0, but this platक्रमm requires it, so
	 * करो it once when some other slot is being enabled. The PCI subप्रणाली
	 * should configure other slots properly, so no need to करो anything
	 * special क्रम those.
	 */
	अगर (!slot0_init && dev->bus->number == 0) अणु
		u16 cmd;
		u32 bar0;

		slot0_init = true;

		pci_bus_ग_लिखो_config_dword(dev->bus, 0, PCI_BASE_ADDRESS_0,
					   0x08000000);
		pci_bus_पढ़ो_config_dword(dev->bus, 0, PCI_BASE_ADDRESS_0,
					  &bar0);

		pci_bus_पढ़ो_config_word(dev->bus, 0, PCI_COMMAND, &cmd);
		cmd |= PCI_COMMAND_MASTER | PCI_COMMAND_IO | PCI_COMMAND_MEMORY;
		pci_bus_ग_लिखो_config_word(dev->bus, 0, PCI_COMMAND, cmd);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rt288x_pci_match[] = अणु
	अणु .compatible = "ralink,rt288x-pci" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rt288x_pci_driver = अणु
	.probe = rt288x_pci_probe,
	.driver = अणु
		.name = "rt288x-pci",
		.of_match_table = rt288x_pci_match,
	पूर्ण,
पूर्ण;

पूर्णांक __init pcibios_init(व्योम)
अणु
	पूर्णांक ret = platक्रमm_driver_रेजिस्टर(&rt288x_pci_driver);

	अगर (ret)
		pr_info("rt288x-pci: Error registering platform driver!");

	वापस ret;
पूर्ण

arch_initcall(pcibios_init);
