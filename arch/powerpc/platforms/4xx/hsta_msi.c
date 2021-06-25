<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MSI support क्रम PPC4xx SoCs using High Speed Transfer Assist (HSTA) क्रम
 * generation of the पूर्णांकerrupt.
 *
 * Copyright तऊ 2013 Alistair Popple <alistair@popple.id.au> IBM Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/semaphore.h>
#समावेश <यंत्र/msi_biपंचांगap.h>
#समावेश <यंत्र/ppc-pci.h>

काष्ठा ppc4xx_hsta_msi अणु
	काष्ठा device *dev;

	/* The ioremapped HSTA MSI IO space */
	u32 __iomem *data;

	/* Physical address of HSTA MSI IO space */
	u64 address;
	काष्ठा msi_biपंचांगap bmp;

	/* An array mapping offsets to hardware IRQs */
	पूर्णांक *irq_map;

	/* Number of hwirqs supported */
	पूर्णांक irq_count;
पूर्ण;
अटल काष्ठा ppc4xx_hsta_msi ppc4xx_hsta_msi;

अटल पूर्णांक hsta_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	काष्ठा msi_msg msg;
	काष्ठा msi_desc *entry;
	पूर्णांक irq, hwirq;
	u64 addr;

	/* We करोn't support MSI-X */
	अगर (type == PCI_CAP_ID_MSIX) अणु
		pr_debug("%s: MSI-X not supported.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_pci_msi_entry(entry, dev) अणु
		irq = msi_biपंचांगap_alloc_hwirqs(&ppc4xx_hsta_msi.bmp, 1);
		अगर (irq < 0) अणु
			pr_debug("%s: Failed to allocate msi interrupt\n",
				 __func__);
			वापस irq;
		पूर्ण

		hwirq = ppc4xx_hsta_msi.irq_map[irq];
		अगर (!hwirq) अणु
			pr_err("%s: Failed mapping irq %d\n", __func__, irq);
			वापस -EINVAL;
		पूर्ण

		/*
		 * HSTA generates पूर्णांकerrupts on ग_लिखोs to 128-bit aligned
		 * addresses.
		 */
		addr = ppc4xx_hsta_msi.address + irq*0x10;
		msg.address_hi = upper_32_bits(addr);
		msg.address_lo = lower_32_bits(addr);

		/* Data is not used by the HSTA. */
		msg.data = 0;

		pr_debug("%s: Setup irq %d (0x%0llx)\n", __func__, hwirq,
			 (((u64) msg.address_hi) << 32) | msg.address_lo);

		अगर (irq_set_msi_desc(hwirq, entry)) अणु
			pr_err(
			"%s: Invalid hwirq %d specified in device tree\n",
			__func__, hwirq);
			msi_biपंचांगap_मुक्त_hwirqs(&ppc4xx_hsta_msi.bmp, irq, 1);
			वापस -EINVAL;
		पूर्ण
		pci_ग_लिखो_msi_msg(hwirq, &msg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hsta_find_hwirq_offset(पूर्णांक hwirq)
अणु
	पूर्णांक irq;

	/* Find the offset given the hwirq */
	क्रम (irq = 0; irq < ppc4xx_hsta_msi.irq_count; irq++)
		अगर (ppc4xx_hsta_msi.irq_map[irq] == hwirq)
			वापस irq;

	वापस -EINVAL;
पूर्ण

अटल व्योम hsta_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *entry;
	पूर्णांक irq;

	क्रम_each_pci_msi_entry(entry, dev) अणु
		अगर (!entry->irq)
			जारी;

		irq = hsta_find_hwirq_offset(entry->irq);

		/* entry->irq should always be in irq_map */
		BUG_ON(irq < 0);
		irq_set_msi_desc(entry->irq, शून्य);
		msi_biपंचांगap_मुक्त_hwirqs(&ppc4xx_hsta_msi.bmp, irq, 1);
		pr_debug("%s: Teardown IRQ %u (index %u)\n", __func__,
			 entry->irq, irq);
	पूर्ण
पूर्ण

अटल पूर्णांक hsta_msi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *mem;
	पूर्णांक irq, ret, irq_count;
	काष्ठा pci_controller *phb;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem) अणु
		dev_err(dev, "Unable to get mmio space\n");
		वापस -EINVAL;
	पूर्ण

	irq_count = of_irq_count(dev->of_node);
	अगर (!irq_count) अणु
		dev_err(dev, "Unable to find IRQ range\n");
		वापस -EINVAL;
	पूर्ण

	ppc4xx_hsta_msi.dev = dev;
	ppc4xx_hsta_msi.address = mem->start;
	ppc4xx_hsta_msi.data = ioremap(mem->start, resource_size(mem));
	ppc4xx_hsta_msi.irq_count = irq_count;
	अगर (!ppc4xx_hsta_msi.data) अणु
		dev_err(dev, "Unable to map memory\n");
		वापस -ENOMEM;
	पूर्ण

	ret = msi_biपंचांगap_alloc(&ppc4xx_hsta_msi.bmp, irq_count, dev->of_node);
	अगर (ret)
		जाओ out;

	ppc4xx_hsta_msi.irq_map = kदो_स्मृति_array(irq_count, माप(पूर्णांक),
						GFP_KERNEL);
	अगर (!ppc4xx_hsta_msi.irq_map) अणु
		ret = -ENOMEM;
		जाओ out1;
	पूर्ण

	/* Setup a mapping from irq offsets to hardware irq numbers */
	क्रम (irq = 0; irq < irq_count; irq++) अणु
		ppc4xx_hsta_msi.irq_map[irq] =
			irq_of_parse_and_map(dev->of_node, irq);
		अगर (!ppc4xx_hsta_msi.irq_map[irq]) अणु
			dev_err(dev, "Unable to map IRQ\n");
			ret = -EINVAL;
			जाओ out2;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(phb, &hose_list, list_node) अणु
		phb->controller_ops.setup_msi_irqs = hsta_setup_msi_irqs;
		phb->controller_ops.tearकरोwn_msi_irqs = hsta_tearकरोwn_msi_irqs;
	पूर्ण
	वापस 0;

out2:
	kमुक्त(ppc4xx_hsta_msi.irq_map);

out1:
	msi_biपंचांगap_मुक्त(&ppc4xx_hsta_msi.bmp);

out:
	iounmap(ppc4xx_hsta_msi.data);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id hsta_msi_ids[] = अणु
	अणु
		.compatible = "ibm,hsta-msi",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver hsta_msi_driver = अणु
	.probe = hsta_msi_probe,
	.driver = अणु
		.name = "hsta-msi",
		.of_match_table = hsta_msi_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक hsta_msi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hsta_msi_driver);
पूर्ण
subsys_initcall(hsta_msi_init);
