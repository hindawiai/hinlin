<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Faraday Technology FTPC100 PCI Controller
 *
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 *
 * Based on the out-of-tree OpenWRT patch क्रम Cortina Gemini:
 * Copyright (C) 2009 Janos Laube <janos.dev@gmail.com>
 * Copyright (C) 2009 Paulius Zaleckas <paulius.zaleckas@teltonika.lt>
 * Based on SL2312 PCI controller code
 * Storlink (C) 2003
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>

#समावेश "../pci.h"

/*
 * Special configuration रेजिस्टरs directly in the first few words
 * in I/O space.
 */
#घोषणा PCI_IOSIZE	0x00
#घोषणा PCI_PROT	0x04 /* AHB protection */
#घोषणा PCI_CTRL	0x08 /* PCI control संकेत */
#घोषणा PCI_SOFTRST	0x10 /* Soft reset counter and response error enable */
#घोषणा PCI_CONFIG	0x28 /* PCI configuration command रेजिस्टर */
#घोषणा PCI_DATA	0x2C

#घोषणा FARADAY_PCI_STATUS_CMD		0x04 /* Status and command */
#घोषणा FARADAY_PCI_PMC			0x40 /* Power management control */
#घोषणा FARADAY_PCI_PMCSR		0x44 /* Power management status */
#घोषणा FARADAY_PCI_CTRL1		0x48 /* Control रेजिस्टर 1 */
#घोषणा FARADAY_PCI_CTRL2		0x4C /* Control रेजिस्टर 2 */
#घोषणा FARADAY_PCI_MEM1_BASE_SIZE	0x50 /* Memory base and size #1 */
#घोषणा FARADAY_PCI_MEM2_BASE_SIZE	0x54 /* Memory base and size #2 */
#घोषणा FARADAY_PCI_MEM3_BASE_SIZE	0x58 /* Memory base and size #3 */

#घोषणा PCI_STATUS_66MHZ_CAPABLE	BIT(21)

/* Bits 31..28 gives INTD..INTA status */
#घोषणा PCI_CTRL2_INTSTS_SHIFT		28
#घोषणा PCI_CTRL2_INTMASK_CMDERR	BIT(27)
#घोषणा PCI_CTRL2_INTMASK_PARERR	BIT(26)
/* Bits 25..22 masks INTD..INTA */
#घोषणा PCI_CTRL2_INTMASK_SHIFT		22
#घोषणा PCI_CTRL2_INTMASK_MABRT_RX	BIT(21)
#घोषणा PCI_CTRL2_INTMASK_TABRT_RX	BIT(20)
#घोषणा PCI_CTRL2_INTMASK_TABRT_TX	BIT(19)
#घोषणा PCI_CTRL2_INTMASK_RETRY4	BIT(18)
#घोषणा PCI_CTRL2_INTMASK_SERR_RX	BIT(17)
#घोषणा PCI_CTRL2_INTMASK_PERR_RX	BIT(16)
/* Bit 15 reserved */
#घोषणा PCI_CTRL2_MSTPRI_REQ6		BIT(14)
#घोषणा PCI_CTRL2_MSTPRI_REQ5		BIT(13)
#घोषणा PCI_CTRL2_MSTPRI_REQ4		BIT(12)
#घोषणा PCI_CTRL2_MSTPRI_REQ3		BIT(11)
#घोषणा PCI_CTRL2_MSTPRI_REQ2		BIT(10)
#घोषणा PCI_CTRL2_MSTPRI_REQ1		BIT(9)
#घोषणा PCI_CTRL2_MSTPRI_REQ0		BIT(8)
/* Bits 7..4 reserved */
/* Bits 3..0 TRDYW */

/*
 * Memory configs:
 * Bit 31..20 defines the PCI side memory base
 * Bit 19..16 (4 bits) defines the size per below
 */
#घोषणा FARADAY_PCI_MEMBASE_MASK	0xfff00000
#घोषणा FARADAY_PCI_MEMSIZE_1MB		0x0
#घोषणा FARADAY_PCI_MEMSIZE_2MB		0x1
#घोषणा FARADAY_PCI_MEMSIZE_4MB		0x2
#घोषणा FARADAY_PCI_MEMSIZE_8MB		0x3
#घोषणा FARADAY_PCI_MEMSIZE_16MB	0x4
#घोषणा FARADAY_PCI_MEMSIZE_32MB	0x5
#घोषणा FARADAY_PCI_MEMSIZE_64MB	0x6
#घोषणा FARADAY_PCI_MEMSIZE_128MB	0x7
#घोषणा FARADAY_PCI_MEMSIZE_256MB	0x8
#घोषणा FARADAY_PCI_MEMSIZE_512MB	0x9
#घोषणा FARADAY_PCI_MEMSIZE_1GB		0xa
#घोषणा FARADAY_PCI_MEMSIZE_2GB		0xb
#घोषणा FARADAY_PCI_MEMSIZE_SHIFT	16

/*
 * The DMA base is set to 0x0 क्रम all memory segments, it reflects the
 * fact that the memory of the host प्रणाली starts at 0x0.
 */
#घोषणा FARADAY_PCI_DMA_MEM1_BASE	0x00000000
#घोषणा FARADAY_PCI_DMA_MEM2_BASE	0x00000000
#घोषणा FARADAY_PCI_DMA_MEM3_BASE	0x00000000

/* Defines क्रम PCI configuration command रेजिस्टर */
#घोषणा PCI_CONF_ENABLE		BIT(31)
#घोषणा PCI_CONF_WHERE(r)	((r) & 0xFC)
#घोषणा PCI_CONF_BUS(b)		(((b) & 0xFF) << 16)
#घोषणा PCI_CONF_DEVICE(d)	(((d) & 0x1F) << 11)
#घोषणा PCI_CONF_FUNCTION(f)	(((f) & 0x07) << 8)

/**
 * काष्ठा faraday_pci_variant - encodes IP block dअगरferences
 * @cascaded_irq: this host has cascaded IRQs from an पूर्णांकerrupt controller
 *	embedded in the host bridge.
 */
काष्ठा faraday_pci_variant अणु
	bool cascaded_irq;
पूर्ण;

काष्ठा faraday_pci अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	काष्ठा pci_bus *bus;
	काष्ठा clk *bus_clk;
पूर्ण;

अटल पूर्णांक faraday_res_to_memcfg(resource_माप_प्रकार mem_base,
				 resource_माप_प्रकार mem_size, u32 *val)
अणु
	u32 outval;

	चयन (mem_size) अणु
	हाल SZ_1M:
		outval = FARADAY_PCI_MEMSIZE_1MB;
		अवरोध;
	हाल SZ_2M:
		outval = FARADAY_PCI_MEMSIZE_2MB;
		अवरोध;
	हाल SZ_4M:
		outval = FARADAY_PCI_MEMSIZE_4MB;
		अवरोध;
	हाल SZ_8M:
		outval = FARADAY_PCI_MEMSIZE_8MB;
		अवरोध;
	हाल SZ_16M:
		outval = FARADAY_PCI_MEMSIZE_16MB;
		अवरोध;
	हाल SZ_32M:
		outval = FARADAY_PCI_MEMSIZE_32MB;
		अवरोध;
	हाल SZ_64M:
		outval = FARADAY_PCI_MEMSIZE_64MB;
		अवरोध;
	हाल SZ_128M:
		outval = FARADAY_PCI_MEMSIZE_128MB;
		अवरोध;
	हाल SZ_256M:
		outval = FARADAY_PCI_MEMSIZE_256MB;
		अवरोध;
	हाल SZ_512M:
		outval = FARADAY_PCI_MEMSIZE_512MB;
		अवरोध;
	हाल SZ_1G:
		outval = FARADAY_PCI_MEMSIZE_1GB;
		अवरोध;
	हाल SZ_2G:
		outval = FARADAY_PCI_MEMSIZE_2GB;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	outval <<= FARADAY_PCI_MEMSIZE_SHIFT;

	/* This is probably not good */
	अगर (mem_base & ~(FARADAY_PCI_MEMBASE_MASK))
		pr_warn("truncated PCI memory base\n");
	/* Translate to bridge side address space */
	outval |= (mem_base & FARADAY_PCI_MEMBASE_MASK);
	pr_debug("Translated pci base @%pap, size %pap to config %08x\n",
		 &mem_base, &mem_size, outval);

	*val = outval;
	वापस 0;
पूर्ण

अटल पूर्णांक faraday_raw_pci_पढ़ो_config(काष्ठा faraday_pci *p, पूर्णांक bus_number,
				       अचिन्हित पूर्णांक fn, पूर्णांक config, पूर्णांक size,
				       u32 *value)
अणु
	ग_लिखोl(PCI_CONF_BUS(bus_number) |
			PCI_CONF_DEVICE(PCI_SLOT(fn)) |
			PCI_CONF_FUNCTION(PCI_FUNC(fn)) |
			PCI_CONF_WHERE(config) |
			PCI_CONF_ENABLE,
			p->base + PCI_CONFIG);

	*value = पढ़ोl(p->base + PCI_DATA);

	अगर (size == 1)
		*value = (*value >> (8 * (config & 3))) & 0xFF;
	अन्यथा अगर (size == 2)
		*value = (*value >> (8 * (config & 3))) & 0xFFFF;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक faraday_pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक fn,
				   पूर्णांक config, पूर्णांक size, u32 *value)
अणु
	काष्ठा faraday_pci *p = bus->sysdata;

	dev_dbg(&bus->dev,
		"[read]  slt: %.2d, fnc: %d, cnf: 0x%.2X, val (%d bytes): 0x%.8X\n",
		PCI_SLOT(fn), PCI_FUNC(fn), config, size, *value);

	वापस faraday_raw_pci_पढ़ो_config(p, bus->number, fn, config, size, value);
पूर्ण

अटल पूर्णांक faraday_raw_pci_ग_लिखो_config(काष्ठा faraday_pci *p, पूर्णांक bus_number,
					 अचिन्हित पूर्णांक fn, पूर्णांक config, पूर्णांक size,
					 u32 value)
अणु
	पूर्णांक ret = PCIBIOS_SUCCESSFUL;

	ग_लिखोl(PCI_CONF_BUS(bus_number) |
			PCI_CONF_DEVICE(PCI_SLOT(fn)) |
			PCI_CONF_FUNCTION(PCI_FUNC(fn)) |
			PCI_CONF_WHERE(config) |
			PCI_CONF_ENABLE,
			p->base + PCI_CONFIG);

	चयन (size) अणु
	हाल 4:
		ग_लिखोl(value, p->base + PCI_DATA);
		अवरोध;
	हाल 2:
		ग_लिखोw(value, p->base + PCI_DATA + (config & 3));
		अवरोध;
	हाल 1:
		ग_लिखोb(value, p->base + PCI_DATA + (config & 3));
		अवरोध;
	शेष:
		ret = PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक faraday_pci_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक fn,
				    पूर्णांक config, पूर्णांक size, u32 value)
अणु
	काष्ठा faraday_pci *p = bus->sysdata;

	dev_dbg(&bus->dev,
		"[write] slt: %.2d, fnc: %d, cnf: 0x%.2X, val (%d bytes): 0x%.8X\n",
		PCI_SLOT(fn), PCI_FUNC(fn), config, size, value);

	वापस faraday_raw_pci_ग_लिखो_config(p, bus->number, fn, config, size,
					    value);
पूर्ण

अटल काष्ठा pci_ops faraday_pci_ops = अणु
	.पढ़ो	= faraday_pci_पढ़ो_config,
	.ग_लिखो	= faraday_pci_ग_लिखो_config,
पूर्ण;

अटल व्योम faraday_pci_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा faraday_pci *p = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक reg;

	faraday_raw_pci_पढ़ो_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, &reg);
	reg &= ~(0xF << PCI_CTRL2_INTSTS_SHIFT);
	reg |= BIT(irqd_to_hwirq(d) + PCI_CTRL2_INTSTS_SHIFT);
	faraday_raw_pci_ग_लिखो_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, reg);
पूर्ण

अटल व्योम faraday_pci_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा faraday_pci *p = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक reg;

	faraday_raw_pci_पढ़ो_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, &reg);
	reg &= ~((0xF << PCI_CTRL2_INTSTS_SHIFT)
		 | BIT(irqd_to_hwirq(d) + PCI_CTRL2_INTMASK_SHIFT));
	faraday_raw_pci_ग_लिखो_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, reg);
पूर्ण

अटल व्योम faraday_pci_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा faraday_pci *p = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक reg;

	faraday_raw_pci_पढ़ो_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, &reg);
	reg &= ~(0xF << PCI_CTRL2_INTSTS_SHIFT);
	reg |= BIT(irqd_to_hwirq(d) + PCI_CTRL2_INTMASK_SHIFT);
	faraday_raw_pci_ग_लिखो_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, reg);
पूर्ण

अटल व्योम faraday_pci_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा faraday_pci *p = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक irq_stat, reg, i;

	faraday_raw_pci_पढ़ो_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, &reg);
	irq_stat = reg >> PCI_CTRL2_INTSTS_SHIFT;

	chained_irq_enter(irqchip, desc);

	क्रम (i = 0; i < 4; i++) अणु
		अगर ((irq_stat & BIT(i)) == 0)
			जारी;
		generic_handle_irq(irq_find_mapping(p->irqकरोमुख्य, i));
	पूर्ण

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल काष्ठा irq_chip faraday_pci_irq_chip = अणु
	.name = "PCI",
	.irq_ack = faraday_pci_ack_irq,
	.irq_mask = faraday_pci_mask_irq,
	.irq_unmask = faraday_pci_unmask_irq,
पूर्ण;

अटल पूर्णांक faraday_pci_irq_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
			       irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &faraday_pci_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops faraday_pci_irqकरोमुख्य_ops = अणु
	.map = faraday_pci_irq_map,
पूर्ण;

अटल पूर्णांक faraday_pci_setup_cascaded_irq(काष्ठा faraday_pci *p)
अणु
	काष्ठा device_node *पूर्णांकc = of_get_next_child(p->dev->of_node, शून्य);
	पूर्णांक irq;
	पूर्णांक i;

	अगर (!पूर्णांकc) अणु
		dev_err(p->dev, "missing child interrupt-controller node\n");
		वापस -EINVAL;
	पूर्ण

	/* All PCI IRQs cascade off this one */
	irq = of_irq_get(पूर्णांकc, 0);
	अगर (irq <= 0) अणु
		dev_err(p->dev, "failed to get parent IRQ\n");
		of_node_put(पूर्णांकc);
		वापस irq ?: -EINVAL;
	पूर्ण

	p->irqकरोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc, PCI_NUM_INTX,
					     &faraday_pci_irqकरोमुख्य_ops, p);
	of_node_put(पूर्णांकc);
	अगर (!p->irqकरोमुख्य) अणु
		dev_err(p->dev, "failed to create Gemini PCI IRQ domain\n");
		वापस -EINVAL;
	पूर्ण

	irq_set_chained_handler_and_data(irq, faraday_pci_irq_handler, p);

	क्रम (i = 0; i < 4; i++)
		irq_create_mapping(p->irqकरोमुख्य, i);

	वापस 0;
पूर्ण

अटल पूर्णांक faraday_pci_parse_map_dma_ranges(काष्ठा faraday_pci *p)
अणु
	काष्ठा device *dev = p->dev;
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(p);
	काष्ठा resource_entry *entry;
	u32 confreg[3] = अणु
		FARADAY_PCI_MEM1_BASE_SIZE,
		FARADAY_PCI_MEM2_BASE_SIZE,
		FARADAY_PCI_MEM3_BASE_SIZE,
	पूर्ण;
	पूर्णांक i = 0;
	u32 val;

	resource_list_क्रम_each_entry(entry, &bridge->dma_ranges) अणु
		u64 pci_addr = entry->res->start - entry->offset;
		u64 end = entry->res->end - entry->offset;
		पूर्णांक ret;

		ret = faraday_res_to_memcfg(pci_addr,
					    resource_size(entry->res), &val);
		अगर (ret) अणु
			dev_err(dev,
				"DMA range %d: illegal MEM resource size\n", i);
			वापस -EINVAL;
		पूर्ण

		dev_info(dev, "DMA MEM%d BASE: 0x%016llx -> 0x%016llx config %08x\n",
			 i + 1, pci_addr, end, val);
		अगर (i <= 2) अणु
			faraday_raw_pci_ग_लिखो_config(p, 0, 0, confreg[i],
						     4, val);
		पूर्ण अन्यथा अणु
			dev_err(dev, "ignore extraneous dma-range %d\n", i);
			अवरोध;
		पूर्ण

		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक faraday_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा faraday_pci_variant *variant =
		of_device_get_match_data(dev);
	काष्ठा resource_entry *win;
	काष्ठा faraday_pci *p;
	काष्ठा resource *io;
	काष्ठा pci_host_bridge *host;
	काष्ठा clk *clk;
	अचिन्हित अक्षर max_bus_speed = PCI_SPEED_33MHz;
	अचिन्हित अक्षर cur_bus_speed = PCI_SPEED_33MHz;
	पूर्णांक ret;
	u32 val;

	host = devm_pci_alloc_host_bridge(dev, माप(*p));
	अगर (!host)
		वापस -ENOMEM;

	host->ops = &faraday_pci_ops;
	p = pci_host_bridge_priv(host);
	host->sysdata = p;
	p->dev = dev;

	/* Retrieve and enable optional घड़ीs */
	clk = devm_clk_get(dev, "PCLK");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);
	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "could not prepare PCLK\n");
		वापस ret;
	पूर्ण
	p->bus_clk = devm_clk_get(dev, "PCICLK");
	अगर (IS_ERR(p->bus_clk))
		वापस PTR_ERR(p->bus_clk);
	ret = clk_prepare_enable(p->bus_clk);
	अगर (ret) अणु
		dev_err(dev, "could not prepare PCICLK\n");
		वापस ret;
	पूर्ण

	p->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(p->base))
		वापस PTR_ERR(p->base);

	win = resource_list_first_type(&host->winकरोws, IORESOURCE_IO);
	अगर (win) अणु
		io = win->res;
		अगर (!faraday_res_to_memcfg(io->start - win->offset,
					   resource_size(io), &val)) अणु
			/* setup I/O space size */
			ग_लिखोl(val, p->base + PCI_IOSIZE);
		पूर्ण अन्यथा अणु
			dev_err(dev, "illegal IO mem size\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Setup hostbridge */
	val = पढ़ोl(p->base + PCI_CTRL);
	val |= PCI_COMMAND_IO;
	val |= PCI_COMMAND_MEMORY;
	val |= PCI_COMMAND_MASTER;
	ग_लिखोl(val, p->base + PCI_CTRL);
	/* Mask and clear all पूर्णांकerrupts */
	faraday_raw_pci_ग_लिखो_config(p, 0, 0, FARADAY_PCI_CTRL2 + 2, 2, 0xF000);
	अगर (variant->cascaded_irq) अणु
		ret = faraday_pci_setup_cascaded_irq(p);
		अगर (ret) अणु
			dev_err(dev, "failed to setup cascaded IRQ\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Check bus घड़ी अगर we can gear up to 66 MHz */
	अगर (!IS_ERR(p->bus_clk)) अणु
		अचिन्हित दीर्घ rate;
		u32 val;

		faraday_raw_pci_पढ़ो_config(p, 0, 0,
					    FARADAY_PCI_STATUS_CMD, 4, &val);
		rate = clk_get_rate(p->bus_clk);

		अगर ((rate == 33000000) && (val & PCI_STATUS_66MHZ_CAPABLE)) अणु
			dev_info(dev, "33MHz bus is 66MHz capable\n");
			max_bus_speed = PCI_SPEED_66MHz;
			ret = clk_set_rate(p->bus_clk, 66000000);
			अगर (ret)
				dev_err(dev, "failed to set bus clock\n");
		पूर्ण अन्यथा अणु
			dev_info(dev, "33MHz only bus\n");
			max_bus_speed = PCI_SPEED_33MHz;
		पूर्ण

		/* Bumping the घड़ी may fail so पढ़ो back the rate */
		rate = clk_get_rate(p->bus_clk);
		अगर (rate == 33000000)
			cur_bus_speed = PCI_SPEED_33MHz;
		अगर (rate == 66000000)
			cur_bus_speed = PCI_SPEED_66MHz;
	पूर्ण

	ret = faraday_pci_parse_map_dma_ranges(p);
	अगर (ret)
		वापस ret;

	ret = pci_scan_root_bus_bridge(host);
	अगर (ret) अणु
		dev_err(dev, "failed to scan host: %d\n", ret);
		वापस ret;
	पूर्ण
	p->bus = host->bus;
	p->bus->max_bus_speed = max_bus_speed;
	p->bus->cur_bus_speed = cur_bus_speed;

	pci_bus_assign_resources(p->bus);
	pci_bus_add_devices(p->bus);

	वापस 0;
पूर्ण

/*
 * We encode bridge variants here, we have at least two so it करोesn't
 * hurt to have infraकाष्ठाure to encompass future variants as well.
 */
अटल स्थिर काष्ठा faraday_pci_variant faraday_regular = अणु
	.cascaded_irq = true,
पूर्ण;

अटल स्थिर काष्ठा faraday_pci_variant faraday_dual = अणु
	.cascaded_irq = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id faraday_pci_of_match[] = अणु
	अणु
		.compatible = "faraday,ftpci100",
		.data = &faraday_regular,
	पूर्ण,
	अणु
		.compatible = "faraday,ftpci100-dual",
		.data = &faraday_dual,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver faraday_pci_driver = अणु
	.driver = अणु
		.name = "ftpci100",
		.of_match_table = of_match_ptr(faraday_pci_of_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe  = faraday_pci_probe,
पूर्ण;
builtin_platक्रमm_driver(faraday_pci_driver);
