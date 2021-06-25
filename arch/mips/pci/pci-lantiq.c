<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>

#समावेश <यंत्र/addrspace.h>

#समावेश <lantiq_soc.h>
#समावेश <lantiq_irq.h>

#समावेश "pci-lantiq.h"

#घोषणा PCI_CR_FCI_ADDR_MAP0		0x00C0
#घोषणा PCI_CR_FCI_ADDR_MAP1		0x00C4
#घोषणा PCI_CR_FCI_ADDR_MAP2		0x00C8
#घोषणा PCI_CR_FCI_ADDR_MAP3		0x00CC
#घोषणा PCI_CR_FCI_ADDR_MAP4		0x00D0
#घोषणा PCI_CR_FCI_ADDR_MAP5		0x00D4
#घोषणा PCI_CR_FCI_ADDR_MAP6		0x00D8
#घोषणा PCI_CR_FCI_ADDR_MAP7		0x00DC
#घोषणा PCI_CR_CLK_CTRL			0x0000
#घोषणा PCI_CR_PCI_MOD			0x0030
#घोषणा PCI_CR_PC_ARB			0x0080
#घोषणा PCI_CR_FCI_ADDR_MAP11hg		0x00E4
#घोषणा PCI_CR_BAR11MASK		0x0044
#घोषणा PCI_CR_BAR12MASK		0x0048
#घोषणा PCI_CR_BAR13MASK		0x004C
#घोषणा PCI_CS_BASE_ADDR1		0x0010
#घोषणा PCI_CR_PCI_ADDR_MAP11		0x0064
#घोषणा PCI_CR_FCI_BURST_LENGTH		0x00E8
#घोषणा PCI_CR_PCI_EOI			0x002C
#घोषणा PCI_CS_STS_CMD			0x0004

#घोषणा PCI_MASTER0_REQ_MASK_2BITS	8
#घोषणा PCI_MASTER1_REQ_MASK_2BITS	10
#घोषणा PCI_MASTER2_REQ_MASK_2BITS	12
#घोषणा INTERNAL_ARB_ENABLE_BIT		0

#घोषणा LTQ_CGU_IFCCR		0x0018
#घोषणा LTQ_CGU_PCICR		0x0034

#घोषणा ltq_pci_w32(x, y)	ltq_w32((x), ltq_pci_membase + (y))
#घोषणा ltq_pci_r32(x)		ltq_r32(ltq_pci_membase + (x))

#घोषणा ltq_pci_cfg_w32(x, y)	ltq_w32((x), ltq_pci_mapped_cfg + (y))
#घोषणा ltq_pci_cfg_r32(x)	ltq_r32(ltq_pci_mapped_cfg + (x))

__iomem व्योम *ltq_pci_mapped_cfg;
अटल __iomem व्योम *ltq_pci_membase;

अटल पूर्णांक reset_gpio;
अटल काष्ठा clk *clk_pci, *clk_बाह्यal;
अटल काष्ठा resource pci_io_resource;
अटल काष्ठा resource pci_mem_resource;
अटल काष्ठा pci_ops pci_ops = अणु
	.पढ़ो	= ltq_pci_पढ़ो_config_dword,
	.ग_लिखो	= ltq_pci_ग_लिखो_config_dword
पूर्ण;

अटल काष्ठा pci_controller pci_controller = अणु
	.pci_ops	= &pci_ops,
	.mem_resource	= &pci_mem_resource,
	.mem_offset	= 0x00000000UL,
	.io_resource	= &pci_io_resource,
	.io_offset	= 0x00000000UL,
पूर्ण;

अटल अंतरभूत u32 ltq_calc_bar11mask(व्योम)
अणु
	u32 mem, bar11mask;

	/* BAR11MASK value depends on available memory on प्रणाली. */
	mem = get_num_physpages() * PAGE_SIZE;
	bar11mask = (0x0ffffff0 & ~((1 << (fls(mem) - 1)) - 1)) | 8;

	वापस bar11mask;
पूर्ण

अटल पूर्णांक ltq_pci_startup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर __be32 *req_mask, *bus_clk;
	u32 temp_buffer;

	/* get our घड़ीs */
	clk_pci = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk_pci)) अणु
		dev_err(&pdev->dev, "failed to get pci clock\n");
		वापस PTR_ERR(clk_pci);
	पूर्ण

	clk_बाह्यal = clk_get(&pdev->dev, "external");
	अगर (IS_ERR(clk_बाह्यal)) अणु
		clk_put(clk_pci);
		dev_err(&pdev->dev, "failed to get external pci clock\n");
		वापस PTR_ERR(clk_बाह्यal);
	पूर्ण

	/* पढ़ो the bus speed that we want */
	bus_clk = of_get_property(node, "lantiq,bus-clock", शून्य);
	अगर (bus_clk)
		clk_set_rate(clk_pci, *bus_clk);

	/* and enable the घड़ीs */
	clk_enable(clk_pci);
	अगर (of_find_property(node, "lantiq,external-clock", शून्य))
		clk_enable(clk_बाह्यal);
	अन्यथा
		clk_disable(clk_बाह्यal);

	/* setup reset gpio used by pci */
	reset_gpio = of_get_named_gpio(node, "gpio-reset", 0);
	अगर (gpio_is_valid(reset_gpio)) अणु
		पूर्णांक ret = devm_gpio_request(&pdev->dev,
						reset_gpio, "pci-reset");
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"failed to request gpio %d\n", reset_gpio);
			वापस ret;
		पूर्ण
		gpio_direction_output(reset_gpio, 1);
	पूर्ण

	/* enable स्वतः-चयनing between PCI and EBU */
	ltq_pci_w32(0xa, PCI_CR_CLK_CTRL);

	/* busy, i.e. configuration is not करोne, PCI access has to be retried */
	ltq_pci_w32(ltq_pci_r32(PCI_CR_PCI_MOD) & ~(1 << 24), PCI_CR_PCI_MOD);
	wmb();
	/* BUS Master/IO/MEM access */
	ltq_pci_cfg_w32(ltq_pci_cfg_r32(PCI_CS_STS_CMD) | 7, PCI_CS_STS_CMD);

	/* enable बाह्यal 2 PCI masters */
	temp_buffer = ltq_pci_r32(PCI_CR_PC_ARB);
	/* setup the request mask */
	req_mask = of_get_property(node, "req-mask", शून्य);
	अगर (req_mask)
		temp_buffer &= ~((*req_mask & 0xf) << 16);
	अन्यथा
		temp_buffer &= ~0xf0000;
	/* enable पूर्णांकernal arbiter */
	temp_buffer |= (1 << INTERNAL_ARB_ENABLE_BIT);
	/* enable पूर्णांकernal PCI master reqest */
	temp_buffer &= (~(3 << PCI_MASTER0_REQ_MASK_2BITS));

	/* enable EBU request */
	temp_buffer &= (~(3 << PCI_MASTER1_REQ_MASK_2BITS));

	/* enable all बाह्यal masters request */
	temp_buffer &= (~(3 << PCI_MASTER2_REQ_MASK_2BITS));
	ltq_pci_w32(temp_buffer, PCI_CR_PC_ARB);
	wmb();

	/* setup BAR memory regions */
	ltq_pci_w32(0x18000000, PCI_CR_FCI_ADDR_MAP0);
	ltq_pci_w32(0x18400000, PCI_CR_FCI_ADDR_MAP1);
	ltq_pci_w32(0x18800000, PCI_CR_FCI_ADDR_MAP2);
	ltq_pci_w32(0x18c00000, PCI_CR_FCI_ADDR_MAP3);
	ltq_pci_w32(0x19000000, PCI_CR_FCI_ADDR_MAP4);
	ltq_pci_w32(0x19400000, PCI_CR_FCI_ADDR_MAP5);
	ltq_pci_w32(0x19800000, PCI_CR_FCI_ADDR_MAP6);
	ltq_pci_w32(0x19c00000, PCI_CR_FCI_ADDR_MAP7);
	ltq_pci_w32(0x1ae00000, PCI_CR_FCI_ADDR_MAP11hg);
	ltq_pci_w32(ltq_calc_bar11mask(), PCI_CR_BAR11MASK);
	ltq_pci_w32(0, PCI_CR_PCI_ADDR_MAP11);
	ltq_pci_w32(0, PCI_CS_BASE_ADDR1);
	/* both TX and RX endian swap are enabled */
	ltq_pci_w32(ltq_pci_r32(PCI_CR_PCI_EOI) | 3, PCI_CR_PCI_EOI);
	wmb();
	ltq_pci_w32(ltq_pci_r32(PCI_CR_BAR12MASK) | 0x80000000,
		PCI_CR_BAR12MASK);
	ltq_pci_w32(ltq_pci_r32(PCI_CR_BAR13MASK) | 0x80000000,
		PCI_CR_BAR13MASK);
	/*use 8 dw burst length */
	ltq_pci_w32(0x303, PCI_CR_FCI_BURST_LENGTH);
	ltq_pci_w32(ltq_pci_r32(PCI_CR_PCI_MOD) | (1 << 24), PCI_CR_PCI_MOD);
	wmb();

	/* setup irq line */
	ltq_ebu_w32(ltq_ebu_r32(LTQ_EBU_PCC_CON) | 0xc, LTQ_EBU_PCC_CON);
	ltq_ebu_w32(ltq_ebu_r32(LTQ_EBU_PCC_IEN) | 0x10, LTQ_EBU_PCC_IEN);

	/* toggle reset pin */
	अगर (gpio_is_valid(reset_gpio)) अणु
		__gpio_set_value(reset_gpio, 0);
		wmb();
		mdelay(1);
		__gpio_set_value(reset_gpio, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ltq_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res_cfg, *res_bridge;

	pci_clear_flags(PCI_PROBE_ONLY);

	res_bridge = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	ltq_pci_membase = devm_ioremap_resource(&pdev->dev, res_bridge);
	अगर (IS_ERR(ltq_pci_membase))
		वापस PTR_ERR(ltq_pci_membase);

	res_cfg = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ltq_pci_mapped_cfg = devm_ioremap_resource(&pdev->dev, res_cfg);
	अगर (IS_ERR(ltq_pci_mapped_cfg))
		वापस PTR_ERR(ltq_pci_mapped_cfg);

	ltq_pci_startup(pdev);

	pci_load_of_ranges(&pci_controller, pdev->dev.of_node);
	रेजिस्टर_pci_controller(&pci_controller);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ltq_pci_match[] = अणु
	अणु .compatible = "lantiq,pci-xway" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ltq_pci_driver = अणु
	.probe = ltq_pci_probe,
	.driver = अणु
		.name = "pci-xway",
		.of_match_table = ltq_pci_match,
	पूर्ण,
पूर्ण;

पूर्णांक __init pcibios_init(व्योम)
अणु
	पूर्णांक ret = platक्रमm_driver_रेजिस्टर(&ltq_pci_driver);
	अगर (ret)
		pr_info("pci-xway: Error registering platform driver!");
	वापस ret;
पूर्ण

arch_initcall(pcibios_init);
