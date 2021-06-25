<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Atheros AR724X PCI host controller driver
 *
 *  Copyright (C) 2011 Renथऊ Bollकरोrf <xsecute@googlemail.com>
 *  Copyright (C) 2009-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 */

#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/mach-ath79/ath79.h>
#समावेश <यंत्र/mach-ath79/ar71xx_regs.h>

#घोषणा AR724X_PCI_REG_APP		0x00
#घोषणा AR724X_PCI_REG_RESET		0x18
#घोषणा AR724X_PCI_REG_INT_STATUS	0x4c
#घोषणा AR724X_PCI_REG_INT_MASK		0x50

#घोषणा AR724X_PCI_APP_LTSSM_ENABLE	BIT(0)

#घोषणा AR724X_PCI_RESET_LINK_UP	BIT(0)

#घोषणा AR724X_PCI_INT_DEV0		BIT(14)

#घोषणा AR724X_PCI_IRQ_COUNT		1

#घोषणा AR7240_BAR0_WAR_VALUE	0xffff

#घोषणा AR724X_PCI_CMD_INIT	(PCI_COMMAND_MEMORY |		\
				 PCI_COMMAND_MASTER |		\
				 PCI_COMMAND_INVALIDATE |	\
				 PCI_COMMAND_PARITY |		\
				 PCI_COMMAND_SERR |		\
				 PCI_COMMAND_FAST_BACK)

काष्ठा ar724x_pci_controller अणु
	व्योम __iomem *devcfg_base;
	व्योम __iomem *ctrl_base;
	व्योम __iomem *crp_base;

	पूर्णांक irq;
	पूर्णांक irq_base;

	bool link_up;
	bool bar0_is_cached;
	u32  bar0_value;

	काष्ठा pci_controller pci_controller;
	काष्ठा resource io_res;
	काष्ठा resource mem_res;
पूर्ण;

अटल अंतरभूत bool ar724x_pci_check_link(काष्ठा ar724x_pci_controller *apc)
अणु
	u32 reset;

	reset = __raw_पढ़ोl(apc->ctrl_base + AR724X_PCI_REG_RESET);
	वापस reset & AR724X_PCI_RESET_LINK_UP;
पूर्ण

अटल अंतरभूत काष्ठा ar724x_pci_controller *
pci_bus_to_ar724x_controller(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose;

	hose = (काष्ठा pci_controller *) bus->sysdata;
	वापस container_of(hose, काष्ठा ar724x_pci_controller, pci_controller);
पूर्ण

अटल पूर्णांक ar724x_pci_local_ग_लिखो(काष्ठा ar724x_pci_controller *apc,
				  पूर्णांक where, पूर्णांक size, u32 value)
अणु
	व्योम __iomem *base;
	u32 data;
	पूर्णांक s;

	WARN_ON(where & (size - 1));

	अगर (!apc->link_up)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	base = apc->crp_base;
	data = __raw_पढ़ोl(base + (where & ~3));

	चयन (size) अणु
	हाल 1:
		s = ((where & 3) * 8);
		data &= ~(0xff << s);
		data |= ((value & 0xff) << s);
		अवरोध;
	हाल 2:
		s = ((where & 2) * 8);
		data &= ~(0xffff << s);
		data |= ((value & 0xffff) << s);
		अवरोध;
	हाल 4:
		data = value;
		अवरोध;
	शेष:
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	__raw_ग_लिखोl(data, base + (where & ~3));
	/* flush ग_लिखो */
	__raw_पढ़ोl(base + (where & ~3));

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ar724x_pci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
			    पूर्णांक size, uपूर्णांक32_t *value)
अणु
	काष्ठा ar724x_pci_controller *apc;
	व्योम __iomem *base;
	u32 data;

	apc = pci_bus_to_ar724x_controller(bus);
	अगर (!apc->link_up)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (devfn)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	base = apc->devcfg_base;
	data = __raw_पढ़ोl(base + (where & ~3));

	चयन (size) अणु
	हाल 1:
		अगर (where & 1)
			data >>= 8;
		अगर (where & 2)
			data >>= 16;
		data &= 0xff;
		अवरोध;
	हाल 2:
		अगर (where & 2)
			data >>= 16;
		data &= 0xffff;
		अवरोध;
	हाल 4:
		अवरोध;
	शेष:
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	अगर (where == PCI_BASE_ADDRESS_0 && size == 4 &&
	    apc->bar0_is_cached) अणु
		/* use the cached value */
		*value = apc->bar0_value;
	पूर्ण अन्यथा अणु
		*value = data;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ar724x_pci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
			     पूर्णांक size, uपूर्णांक32_t value)
अणु
	काष्ठा ar724x_pci_controller *apc;
	व्योम __iomem *base;
	u32 data;
	पूर्णांक s;

	apc = pci_bus_to_ar724x_controller(bus);
	अगर (!apc->link_up)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (devfn)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (soc_is_ar7240() && where == PCI_BASE_ADDRESS_0 && size == 4) अणु
		अगर (value != 0xffffffff) अणु
			/*
			 * WAR क्रम a hw issue. If the BAR0 रेजिस्टर of the
			 * device is set to the proper base address, the
			 * memory space of the device is not accessible.
			 *
			 * Cache the पूर्णांकended value so it can be पढ़ो back,
			 * and ग_लिखो a SoC specअगरic स्थिरant value to the
			 * BAR0 रेजिस्टर in order to make the device memory
			 * accessible.
			 */
			apc->bar0_is_cached = true;
			apc->bar0_value = value;

			value = AR7240_BAR0_WAR_VALUE;
		पूर्ण अन्यथा अणु
			apc->bar0_is_cached = false;
		पूर्ण
	पूर्ण

	base = apc->devcfg_base;
	data = __raw_पढ़ोl(base + (where & ~3));

	चयन (size) अणु
	हाल 1:
		s = ((where & 3) * 8);
		data &= ~(0xff << s);
		data |= ((value & 0xff) << s);
		अवरोध;
	हाल 2:
		s = ((where & 2) * 8);
		data &= ~(0xffff << s);
		data |= ((value & 0xffff) << s);
		अवरोध;
	हाल 4:
		data = value;
		अवरोध;
	शेष:
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	__raw_ग_लिखोl(data, base + (where & ~3));
	/* flush ग_लिखो */
	__raw_पढ़ोl(base + (where & ~3));

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops ar724x_pci_ops = अणु
	.पढ़ो	= ar724x_pci_पढ़ो,
	.ग_लिखो	= ar724x_pci_ग_लिखो,
पूर्ण;

अटल व्योम ar724x_pci_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा ar724x_pci_controller *apc;
	व्योम __iomem *base;
	u32 pending;

	apc = irq_desc_get_handler_data(desc);
	base = apc->ctrl_base;

	pending = __raw_पढ़ोl(base + AR724X_PCI_REG_INT_STATUS) &
		  __raw_पढ़ोl(base + AR724X_PCI_REG_INT_MASK);

	अगर (pending & AR724X_PCI_INT_DEV0)
		generic_handle_irq(apc->irq_base + 0);

	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

अटल व्योम ar724x_pci_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ar724x_pci_controller *apc;
	व्योम __iomem *base;
	पूर्णांक offset;
	u32 t;

	apc = irq_data_get_irq_chip_data(d);
	base = apc->ctrl_base;
	offset = apc->irq_base - d->irq;

	चयन (offset) अणु
	हाल 0:
		t = __raw_पढ़ोl(base + AR724X_PCI_REG_INT_MASK);
		__raw_ग_लिखोl(t | AR724X_PCI_INT_DEV0,
			     base + AR724X_PCI_REG_INT_MASK);
		/* flush ग_लिखो */
		__raw_पढ़ोl(base + AR724X_PCI_REG_INT_MASK);
	पूर्ण
पूर्ण

अटल व्योम ar724x_pci_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ar724x_pci_controller *apc;
	व्योम __iomem *base;
	पूर्णांक offset;
	u32 t;

	apc = irq_data_get_irq_chip_data(d);
	base = apc->ctrl_base;
	offset = apc->irq_base - d->irq;

	चयन (offset) अणु
	हाल 0:
		t = __raw_पढ़ोl(base + AR724X_PCI_REG_INT_MASK);
		__raw_ग_लिखोl(t & ~AR724X_PCI_INT_DEV0,
			     base + AR724X_PCI_REG_INT_MASK);

		/* flush ग_लिखो */
		__raw_पढ़ोl(base + AR724X_PCI_REG_INT_MASK);

		t = __raw_पढ़ोl(base + AR724X_PCI_REG_INT_STATUS);
		__raw_ग_लिखोl(t | AR724X_PCI_INT_DEV0,
			     base + AR724X_PCI_REG_INT_STATUS);

		/* flush ग_लिखो */
		__raw_पढ़ोl(base + AR724X_PCI_REG_INT_STATUS);
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip ar724x_pci_irq_chip = अणु
	.name		= "AR724X PCI ",
	.irq_mask	= ar724x_pci_irq_mask,
	.irq_unmask	= ar724x_pci_irq_unmask,
	.irq_mask_ack	= ar724x_pci_irq_mask,
पूर्ण;

अटल व्योम ar724x_pci_irq_init(काष्ठा ar724x_pci_controller *apc,
				पूर्णांक id)
अणु
	व्योम __iomem *base;
	पूर्णांक i;

	base = apc->ctrl_base;

	__raw_ग_लिखोl(0, base + AR724X_PCI_REG_INT_MASK);
	__raw_ग_लिखोl(0, base + AR724X_PCI_REG_INT_STATUS);

	apc->irq_base = ATH79_PCI_IRQ_BASE + (id * AR724X_PCI_IRQ_COUNT);

	क्रम (i = apc->irq_base;
	     i < apc->irq_base + AR724X_PCI_IRQ_COUNT; i++) अणु
		irq_set_chip_and_handler(i, &ar724x_pci_irq_chip,
					 handle_level_irq);
		irq_set_chip_data(i, apc);
	पूर्ण

	irq_set_chained_handler_and_data(apc->irq, ar724x_pci_irq_handler,
					 apc);
पूर्ण

अटल व्योम ar724x_pci_hw_init(काष्ठा ar724x_pci_controller *apc)
अणु
	u32 ppl, app;
	पूर्णांक रुको = 0;

	/* deनिश्चित PCIe host controller and PCIe PHY reset */
	ath79_device_reset_clear(AR724X_RESET_PCIE);
	ath79_device_reset_clear(AR724X_RESET_PCIE_PHY);

	/* हटाओ the reset of the PCIE PLL */
	ppl = ath79_pll_rr(AR724X_PLL_REG_PCIE_CONFIG);
	ppl &= ~AR724X_PLL_REG_PCIE_CONFIG_PPL_RESET;
	ath79_pll_wr(AR724X_PLL_REG_PCIE_CONFIG, ppl);

	/* deनिश्चित bypass क्रम the PCIE PLL */
	ppl = ath79_pll_rr(AR724X_PLL_REG_PCIE_CONFIG);
	ppl &= ~AR724X_PLL_REG_PCIE_CONFIG_PPL_BYPASS;
	ath79_pll_wr(AR724X_PLL_REG_PCIE_CONFIG, ppl);

	/* set PCIE Application Control to पढ़ोy */
	app = __raw_पढ़ोl(apc->ctrl_base + AR724X_PCI_REG_APP);
	app |= AR724X_PCI_APP_LTSSM_ENABLE;
	__raw_ग_लिखोl(app, apc->ctrl_base + AR724X_PCI_REG_APP);

	/* रुको up to 100ms क्रम PHY link up */
	करो अणु
		mdelay(10);
		रुको++;
	पूर्ण जबतक (रुको < 10 && !ar724x_pci_check_link(apc));
पूर्ण

अटल पूर्णांक ar724x_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ar724x_pci_controller *apc;
	काष्ठा resource *res;
	पूर्णांक id;

	id = pdev->id;
	अगर (id == -1)
		id = 0;

	apc = devm_kzalloc(&pdev->dev, माप(काष्ठा ar724x_pci_controller),
			    GFP_KERNEL);
	अगर (!apc)
		वापस -ENOMEM;

	apc->ctrl_base = devm_platक्रमm_ioremap_resource_byname(pdev, "ctrl_base");
	अगर (IS_ERR(apc->ctrl_base))
		वापस PTR_ERR(apc->ctrl_base);

	apc->devcfg_base = devm_platक्रमm_ioremap_resource_byname(pdev, "cfg_base");
	अगर (IS_ERR(apc->devcfg_base))
		वापस PTR_ERR(apc->devcfg_base);

	apc->crp_base = devm_platक्रमm_ioremap_resource_byname(pdev, "crp_base");
	अगर (IS_ERR(apc->crp_base))
		वापस PTR_ERR(apc->crp_base);

	apc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (apc->irq < 0)
		वापस -EINVAL;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IO, "io_base");
	अगर (!res)
		वापस -EINVAL;

	apc->io_res.parent = res;
	apc->io_res.name = "PCI IO space";
	apc->io_res.start = res->start;
	apc->io_res.end = res->end;
	apc->io_res.flags = IORESOURCE_IO;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mem_base");
	अगर (!res)
		वापस -EINVAL;

	apc->mem_res.parent = res;
	apc->mem_res.name = "PCI memory space";
	apc->mem_res.start = res->start;
	apc->mem_res.end = res->end;
	apc->mem_res.flags = IORESOURCE_MEM;

	apc->pci_controller.pci_ops = &ar724x_pci_ops;
	apc->pci_controller.io_resource = &apc->io_res;
	apc->pci_controller.mem_resource = &apc->mem_res;

	/*
	 * Do the full PCIE Root Complex Initialization Sequence अगर the PCIe
	 * host controller is in reset.
	 */
	अगर (ath79_reset_rr(AR724X_RESET_REG_RESET_MODULE) & AR724X_RESET_PCIE)
		ar724x_pci_hw_init(apc);

	apc->link_up = ar724x_pci_check_link(apc);
	अगर (!apc->link_up)
		dev_warn(&pdev->dev, "PCIe link is down\n");

	ar724x_pci_irq_init(apc, id);

	ar724x_pci_local_ग_लिखो(apc, PCI_COMMAND, 4, AR724X_PCI_CMD_INIT);

	रेजिस्टर_pci_controller(&apc->pci_controller);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ar724x_pci_driver = अणु
	.probe = ar724x_pci_probe,
	.driver = अणु
		.name = "ar724x-pci",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ar724x_pci_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ar724x_pci_driver);
पूर्ण

postcore_initcall(ar724x_pci_init);
