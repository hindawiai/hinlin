<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Ralink MT7620A SoC PCI support
 *
 *  Copyright (C) 2007-2013 Bruce Chang (Mediatek)
 *  Copyright (C) 2013-2016 John Crispin <john@phrozen.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/reset.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-ralink/ralink_regs.h>
#समावेश <यंत्र/mach-ralink/mt7620.h>

#घोषणा RALINK_PCI_IO_MAP_BASE		0x10160000
#घोषणा RALINK_PCI_MEMORY_BASE		0x0

#घोषणा RALINK_INT_PCIE0		4

#घोषणा RALINK_CLKCFG1			0x30
#घोषणा RALINK_GPIOMODE			0x60

#घोषणा PPLL_CFG1			0x9c
#घोषणा PPLL_LD				BIT(23)

#घोषणा PPLL_DRV			0xa0
#घोषणा PDRV_SW_SET			BIT(31)
#घोषणा LC_CKDRVPD			BIT(19)
#घोषणा LC_CKDRVOHZ			BIT(18)
#घोषणा LC_CKDRVHZ			BIT(17)
#घोषणा LC_CKTEST			BIT(16)

/* PCI Bridge रेजिस्टरs */
#घोषणा RALINK_PCI_PCICFG_ADDR		0x00
#घोषणा PCIRST				BIT(1)

#घोषणा RALINK_PCI_PCIENA		0x0C
#घोषणा PCIINT2				BIT(20)

#घोषणा RALINK_PCI_CONFIG_ADDR		0x20
#घोषणा RALINK_PCI_CONFIG_DATA_VIRT_REG	0x24
#घोषणा RALINK_PCI_MEMBASE		0x28
#घोषणा RALINK_PCI_IOBASE		0x2C

/* PCI RC रेजिस्टरs */
#घोषणा RALINK_PCI0_BAR0SETUP_ADDR	0x10
#घोषणा RALINK_PCI0_IMBASEBAR0_ADDR	0x18
#घोषणा RALINK_PCI0_ID			0x30
#घोषणा RALINK_PCI0_CLASS		0x34
#घोषणा RALINK_PCI0_SUBID		0x38
#घोषणा RALINK_PCI0_STATUS		0x50
#घोषणा PCIE_LINK_UP_ST			BIT(0)

#घोषणा PCIEPHY0_CFG			0x90

#घोषणा RALINK_PCIEPHY_P0_CTL_OFFSET	0x7498
#घोषणा RALINK_PCIE0_CLK_EN		BIT(26)

#घोषणा BUSY				0x80000000
#घोषणा WAITRETRY_MAX			10
#घोषणा WRITE_MODE			(1UL << 23)
#घोषणा DATA_SHIFT			0
#घोषणा ADDR_SHIFT			8


अटल व्योम __iomem *bridge_base;
अटल व्योम __iomem *pcie_base;

अटल काष्ठा reset_control *rstpcie0;

अटल अंतरभूत व्योम bridge_w32(u32 val, अचिन्हित reg)
अणु
	ioग_लिखो32(val, bridge_base + reg);
पूर्ण

अटल अंतरभूत u32 bridge_r32(अचिन्हित reg)
अणु
	वापस ioपढ़ो32(bridge_base + reg);
पूर्ण

अटल अंतरभूत व्योम pcie_w32(u32 val, अचिन्हित reg)
अणु
	ioग_लिखो32(val, pcie_base + reg);
पूर्ण

अटल अंतरभूत u32 pcie_r32(अचिन्हित reg)
अणु
	वापस ioपढ़ो32(pcie_base + reg);
पूर्ण

अटल अंतरभूत व्योम pcie_m32(u32 clr, u32 set, अचिन्हित reg)
अणु
	u32 val = pcie_r32(reg);

	val &= ~clr;
	val |= set;
	pcie_w32(val, reg);
पूर्ण

अटल पूर्णांक रुको_pciephy_busy(व्योम)
अणु
	अचिन्हित दीर्घ reg_value = 0x0, retry = 0;

	जबतक (1) अणु
		reg_value = pcie_r32(PCIEPHY0_CFG);

		अगर (reg_value & BUSY)
			mdelay(100);
		अन्यथा
			अवरोध;
		अगर (retry++ > WAITRETRY_MAX) अणु
			pr_warn("PCIE-PHY retry failed.\n");
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pcie_phy(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ val)
अणु
	रुको_pciephy_busy();
	pcie_w32(WRITE_MODE | (val << DATA_SHIFT) | (addr << ADDR_SHIFT),
		 PCIEPHY0_CFG);
	mdelay(1);
	रुको_pciephy_busy();
पूर्ण

अटल पूर्णांक pci_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
			   पूर्णांक size, u32 *val)
अणु
	अचिन्हित पूर्णांक slot = PCI_SLOT(devfn);
	u8 func = PCI_FUNC(devfn);
	u32 address;
	u32 data;
	u32 num = 0;

	अगर (bus)
		num = bus->number;

	address = (((where & 0xF00) >> 8) << 24) | (num << 16) | (slot << 11) |
		  (func << 8) | (where & 0xfc) | 0x80000000;
	bridge_w32(address, RALINK_PCI_CONFIG_ADDR);
	data = bridge_r32(RALINK_PCI_CONFIG_DATA_VIRT_REG);

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

अटल पूर्णांक pci_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
			    पूर्णांक size, u32 val)
अणु
	अचिन्हित पूर्णांक slot = PCI_SLOT(devfn);
	u8 func = PCI_FUNC(devfn);
	u32 address;
	u32 data;
	u32 num = 0;

	अगर (bus)
		num = bus->number;

	address = (((where & 0xF00) >> 8) << 24) | (num << 16) | (slot << 11) |
		  (func << 8) | (where & 0xfc) | 0x80000000;
	bridge_w32(address, RALINK_PCI_CONFIG_ADDR);
	data = bridge_r32(RALINK_PCI_CONFIG_DATA_VIRT_REG);

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

	bridge_w32(data, RALINK_PCI_CONFIG_DATA_VIRT_REG);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops mt7620_pci_ops = अणु
	.पढ़ो	= pci_config_पढ़ो,
	.ग_लिखो	= pci_config_ग_लिखो,
पूर्ण;

अटल काष्ठा resource mt7620_res_pci_mem1;
अटल काष्ठा resource mt7620_res_pci_io1;
काष्ठा pci_controller mt7620_controller = अणु
	.pci_ops	= &mt7620_pci_ops,
	.mem_resource	= &mt7620_res_pci_mem1,
	.mem_offset	= 0x00000000UL,
	.io_resource	= &mt7620_res_pci_io1,
	.io_offset	= 0x00000000UL,
	.io_map_base	= 0xa0000000,
पूर्ण;

अटल पूर्णांक mt7620_pci_hw_init(काष्ठा platक्रमm_device *pdev)
अणु
	/* bypass PCIe DLL */
	pcie_phy(0x0, 0x80);
	pcie_phy(0x1, 0x04);

	/* Elastic buffer control */
	pcie_phy(0x68, 0xB4);

	/* put core पूर्णांकo reset */
	pcie_m32(0, PCIRST, RALINK_PCI_PCICFG_ADDR);
	reset_control_निश्चित(rstpcie0);

	/* disable घातer and all घड़ीs */
	rt_sysc_m32(RALINK_PCIE0_CLK_EN, 0, RALINK_CLKCFG1);
	rt_sysc_m32(LC_CKDRVPD, PDRV_SW_SET, PPLL_DRV);

	/* bring core out of reset */
	reset_control_deनिश्चित(rstpcie0);
	rt_sysc_m32(0, RALINK_PCIE0_CLK_EN, RALINK_CLKCFG1);
	mdelay(100);

	अगर (!(rt_sysc_r32(PPLL_CFG1) & PPLL_LD)) अणु
		dev_err(&pdev->dev, "pcie PLL not locked, aborting init\n");
		reset_control_निश्चित(rstpcie0);
		rt_sysc_m32(RALINK_PCIE0_CLK_EN, 0, RALINK_CLKCFG1);
		वापस -1;
	पूर्ण

	/* घातer up the bus */
	rt_sysc_m32(LC_CKDRVHZ | LC_CKDRVOHZ, LC_CKDRVPD | PDRV_SW_SET,
		    PPLL_DRV);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7628_pci_hw_init(काष्ठा platक्रमm_device *pdev)
अणु
	u32 val = 0;

	/* bring the core out of reset */
	rt_sysc_m32(BIT(16), 0, RALINK_GPIOMODE);
	reset_control_deनिश्चित(rstpcie0);

	/* enable the pci clk */
	rt_sysc_m32(0, RALINK_PCIE0_CLK_EN, RALINK_CLKCFG1);
	mdelay(100);

	/* vooकरोo from the SDK driver */
	pcie_m32(~0xff, 0x5, RALINK_PCIEPHY_P0_CTL_OFFSET);

	pci_config_पढ़ो(शून्य, 0, 0x70c, 4, &val);
	val &= ~(0xff) << 8;
	val |= 0x50 << 8;
	pci_config_ग_लिखो(शून्य, 0, 0x70c, 4, val);

	pci_config_पढ़ो(शून्य, 0, 0x70c, 4, &val);
	dev_err(&pdev->dev, "Port 0 N_FTS = %x\n", (अचिन्हित पूर्णांक) val);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7620_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *bridge_res = platक्रमm_get_resource(pdev,
							    IORESOURCE_MEM, 0);
	काष्ठा resource *pcie_res = platक्रमm_get_resource(pdev,
							  IORESOURCE_MEM, 1);
	u32 val = 0;

	rstpcie0 = devm_reset_control_get_exclusive(&pdev->dev, "pcie0");
	अगर (IS_ERR(rstpcie0))
		वापस PTR_ERR(rstpcie0);

	bridge_base = devm_ioremap_resource(&pdev->dev, bridge_res);
	अगर (IS_ERR(bridge_base))
		वापस PTR_ERR(bridge_base);

	pcie_base = devm_ioremap_resource(&pdev->dev, pcie_res);
	अगर (IS_ERR(pcie_base))
		वापस PTR_ERR(pcie_base);

	iomem_resource.start = 0;
	iomem_resource.end = ~0;
	ioport_resource.start = 0;
	ioport_resource.end = ~0;

	/* bring up the pci core */
	चयन (ralink_soc) अणु
	हाल MT762X_SOC_MT7620A:
		अगर (mt7620_pci_hw_init(pdev))
			वापस -1;
		अवरोध;

	हाल MT762X_SOC_MT7628AN:
	हाल MT762X_SOC_MT7688:
		अगर (mt7628_pci_hw_init(pdev))
			वापस -1;
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "pcie is not supported on this hardware\n");
		वापस -1;
	पूर्ण
	mdelay(50);

	/* enable ग_लिखो access */
	pcie_m32(PCIRST, 0, RALINK_PCI_PCICFG_ADDR);
	mdelay(100);

	/* check अगर there is a card present */
	अगर ((pcie_r32(RALINK_PCI0_STATUS) & PCIE_LINK_UP_ST) == 0) अणु
		reset_control_निश्चित(rstpcie0);
		rt_sysc_m32(RALINK_PCIE0_CLK_EN, 0, RALINK_CLKCFG1);
		अगर (ralink_soc == MT762X_SOC_MT7620A)
			rt_sysc_m32(LC_CKDRVPD, PDRV_SW_SET, PPLL_DRV);
		dev_err(&pdev->dev, "PCIE0 no card, disable it(RST&CLK)\n");
		वापस -1;
	पूर्ण

	/* setup ranges */
	bridge_w32(0xffffffff, RALINK_PCI_MEMBASE);
	bridge_w32(RALINK_PCI_IO_MAP_BASE, RALINK_PCI_IOBASE);

	pcie_w32(0x7FFF0001, RALINK_PCI0_BAR0SETUP_ADDR);
	pcie_w32(RALINK_PCI_MEMORY_BASE, RALINK_PCI0_IMBASEBAR0_ADDR);
	pcie_w32(0x06040001, RALINK_PCI0_CLASS);

	/* enable पूर्णांकerrupts */
	pcie_m32(0, PCIINT2, RALINK_PCI_PCIENA);

	/* vooकरोo from the SDK driver */
	pci_config_पढ़ो(शून्य, 0, 4, 4, &val);
	pci_config_ग_लिखो(शून्य, 0, 4, 4, val | 0x7);

	pci_load_of_ranges(&mt7620_controller, pdev->dev.of_node);
	रेजिस्टर_pci_controller(&mt7620_controller);

	वापस 0;
पूर्ण

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	u16 cmd;
	u32 val;
	पूर्णांक irq = 0;

	अगर ((dev->bus->number == 0) && (slot == 0)) अणु
		pcie_w32(0x7FFF0001, RALINK_PCI0_BAR0SETUP_ADDR);
		pci_config_ग_लिखो(dev->bus, 0, PCI_BASE_ADDRESS_0, 4,
				 RALINK_PCI_MEMORY_BASE);
		pci_config_पढ़ो(dev->bus, 0, PCI_BASE_ADDRESS_0, 4, &val);
	पूर्ण अन्यथा अगर ((dev->bus->number == 1) && (slot == 0x0)) अणु
		irq = RALINK_INT_PCIE0;
	पूर्ण अन्यथा अणु
		dev_err(&dev->dev, "no irq found - bus=0x%x, slot = 0x%x\n",
			dev->bus->number, slot);
		वापस 0;
	पूर्ण
	dev_err(&dev->dev, "card - bus=0x%x, slot = 0x%x irq=%d\n",
		dev->bus->number, slot, irq);

	/* configure the cache line size to 0x14 */
	pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, 0x14);

	/* configure latency समयr to 0xff */
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0xff);
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);

	/* setup the slot */
	cmd = cmd | PCI_COMMAND_MASTER | PCI_COMMAND_IO | PCI_COMMAND_MEMORY;
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);

	वापस irq;
पूर्ण

पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt7620_pci_ids[] = अणु
	अणु .compatible = "mediatek,mt7620-pci" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mt7620_pci_driver = अणु
	.probe = mt7620_pci_probe,
	.driver = अणु
		.name = "mt7620-pci",
		.of_match_table = of_match_ptr(mt7620_pci_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mt7620_pci_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mt7620_pci_driver);
पूर्ण

arch_initcall(mt7620_pci_init);
