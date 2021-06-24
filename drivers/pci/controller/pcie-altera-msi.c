<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Altera PCIe MSI support
 *
 * Author: Ley Foon Tan <lftan@altera.com>
 *
 * Copyright Altera Corporation (C) 2013-2015. All rights reserved
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा MSI_STATUS		0x0
#घोषणा MSI_ERROR		0x4
#घोषणा MSI_INTMASK		0x8

#घोषणा MAX_MSI_VECTORS		32

काष्ठा altera_msi अणु
	DECLARE_BITMAP(used, MAX_MSI_VECTORS);
	काष्ठा mutex		lock;	/* protect "used" biपंचांगap */
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा irq_करोमुख्य	*msi_करोमुख्य;
	काष्ठा irq_करोमुख्य	*inner_करोमुख्य;
	व्योम __iomem		*csr_base;
	व्योम __iomem		*vector_base;
	phys_addr_t		vector_phy;
	u32			num_of_vectors;
	पूर्णांक			irq;
पूर्ण;

अटल अंतरभूत व्योम msi_ग_लिखोl(काष्ठा altera_msi *msi, स्थिर u32 value,
			      स्थिर u32 reg)
अणु
	ग_लिखोl_relaxed(value, msi->csr_base + reg);
पूर्ण

अटल अंतरभूत u32 msi_पढ़ोl(काष्ठा altera_msi *msi, स्थिर u32 reg)
अणु
	वापस पढ़ोl_relaxed(msi->csr_base + reg);
पूर्ण

अटल व्योम altera_msi_isr(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा altera_msi *msi;
	अचिन्हित दीर्घ status;
	u32 bit;
	u32 virq;

	chained_irq_enter(chip, desc);
	msi = irq_desc_get_handler_data(desc);

	जबतक ((status = msi_पढ़ोl(msi, MSI_STATUS)) != 0) अणु
		क्रम_each_set_bit(bit, &status, msi->num_of_vectors) अणु
			/* Dummy पढ़ो from vector to clear the पूर्णांकerrupt */
			पढ़ोl_relaxed(msi->vector_base + (bit * माप(u32)));

			virq = irq_find_mapping(msi->inner_करोमुख्य, bit);
			अगर (virq)
				generic_handle_irq(virq);
			अन्यथा
				dev_err(&msi->pdev->dev, "unexpected MSI\n");
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल काष्ठा irq_chip altera_msi_irq_chip = अणु
	.name = "Altera PCIe MSI",
	.irq_mask = pci_msi_mask_irq,
	.irq_unmask = pci_msi_unmask_irq,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info altera_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		     MSI_FLAG_PCI_MSIX),
	.chip	= &altera_msi_irq_chip,
पूर्ण;

अटल व्योम altera_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा altera_msi *msi = irq_data_get_irq_chip_data(data);
	phys_addr_t addr = msi->vector_phy + (data->hwirq * माप(u32));

	msg->address_lo = lower_32_bits(addr);
	msg->address_hi = upper_32_bits(addr);
	msg->data = data->hwirq;

	dev_dbg(&msi->pdev->dev, "msi#%d address_hi %#x address_lo %#x\n",
		(पूर्णांक)data->hwirq, msg->address_hi, msg->address_lo);
पूर्ण

अटल पूर्णांक altera_msi_set_affinity(काष्ठा irq_data *irq_data,
				   स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	 वापस -EINVAL;
पूर्ण

अटल काष्ठा irq_chip altera_msi_bottom_irq_chip = अणु
	.name			= "Altera MSI",
	.irq_compose_msi_msg	= altera_compose_msi_msg,
	.irq_set_affinity	= altera_msi_set_affinity,
पूर्ण;

अटल पूर्णांक altera_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा altera_msi *msi = करोमुख्य->host_data;
	अचिन्हित दीर्घ bit;
	u32 mask;

	WARN_ON(nr_irqs != 1);
	mutex_lock(&msi->lock);

	bit = find_first_zero_bit(msi->used, msi->num_of_vectors);
	अगर (bit >= msi->num_of_vectors) अणु
		mutex_unlock(&msi->lock);
		वापस -ENOSPC;
	पूर्ण

	set_bit(bit, msi->used);

	mutex_unlock(&msi->lock);

	irq_करोमुख्य_set_info(करोमुख्य, virq, bit, &altera_msi_bottom_irq_chip,
			    करोमुख्य->host_data, handle_simple_irq,
			    शून्य, शून्य);

	mask = msi_पढ़ोl(msi, MSI_INTMASK);
	mask |= 1 << bit;
	msi_ग_लिखोl(msi, mask, MSI_INTMASK);

	वापस 0;
पूर्ण

अटल व्योम altera_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				   अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा altera_msi *msi = irq_data_get_irq_chip_data(d);
	u32 mask;

	mutex_lock(&msi->lock);

	अगर (!test_bit(d->hwirq, msi->used)) अणु
		dev_err(&msi->pdev->dev, "trying to free unused MSI#%lu\n",
			d->hwirq);
	पूर्ण अन्यथा अणु
		__clear_bit(d->hwirq, msi->used);
		mask = msi_पढ़ोl(msi, MSI_INTMASK);
		mask &= ~(1 << d->hwirq);
		msi_ग_लिखोl(msi, mask, MSI_INTMASK);
	पूर्ण

	mutex_unlock(&msi->lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops msi_करोमुख्य_ops = अणु
	.alloc	= altera_irq_करोमुख्य_alloc,
	.मुक्त	= altera_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल पूर्णांक altera_allocate_करोमुख्यs(काष्ठा altera_msi *msi)
अणु
	काष्ठा fwnode_handle *fwnode = of_node_to_fwnode(msi->pdev->dev.of_node);

	msi->inner_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, msi->num_of_vectors,
					     &msi_करोमुख्य_ops, msi);
	अगर (!msi->inner_करोमुख्य) अणु
		dev_err(&msi->pdev->dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	msi->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode,
				&altera_msi_करोमुख्य_info, msi->inner_करोमुख्य);
	अगर (!msi->msi_करोमुख्य) अणु
		dev_err(&msi->pdev->dev, "failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(msi->inner_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम altera_मुक्त_करोमुख्यs(काष्ठा altera_msi *msi)
अणु
	irq_करोमुख्य_हटाओ(msi->msi_करोमुख्य);
	irq_करोमुख्य_हटाओ(msi->inner_करोमुख्य);
पूर्ण

अटल पूर्णांक altera_msi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altera_msi *msi = platक्रमm_get_drvdata(pdev);

	msi_ग_लिखोl(msi, 0, MSI_INTMASK);
	irq_set_chained_handler_and_data(msi->irq, शून्य, शून्य);

	altera_मुक्त_करोमुख्यs(msi);

	platक्रमm_set_drvdata(pdev, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक altera_msi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altera_msi *msi;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;
	पूर्णांक ret;

	msi = devm_kzalloc(&pdev->dev, माप(काष्ठा altera_msi),
			   GFP_KERNEL);
	अगर (!msi)
		वापस -ENOMEM;

	mutex_init(&msi->lock);
	msi->pdev = pdev;

	msi->csr_base = devm_platक्रमm_ioremap_resource_byname(pdev, "csr");
	अगर (IS_ERR(msi->csr_base)) अणु
		dev_err(&pdev->dev, "failed to map csr memory\n");
		वापस PTR_ERR(msi->csr_base);
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "vector_slave");
	msi->vector_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(msi->vector_base))
		वापस PTR_ERR(msi->vector_base);

	msi->vector_phy = res->start;

	अगर (of_property_पढ़ो_u32(np, "num-vectors", &msi->num_of_vectors)) अणु
		dev_err(&pdev->dev, "failed to parse the number of vectors\n");
		वापस -EINVAL;
	पूर्ण

	ret = altera_allocate_करोमुख्यs(msi);
	अगर (ret)
		वापस ret;

	msi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (msi->irq < 0) अणु
		ret = msi->irq;
		जाओ err;
	पूर्ण

	irq_set_chained_handler_and_data(msi->irq, altera_msi_isr, msi);
	platक्रमm_set_drvdata(pdev, msi);

	वापस 0;

err:
	altera_msi_हटाओ(pdev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id altera_msi_of_match[] = अणु
	अणु .compatible = "altr,msi-1.0", शून्य पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver altera_msi_driver = अणु
	.driver = अणु
		.name = "altera-msi",
		.of_match_table = altera_msi_of_match,
	पूर्ण,
	.probe = altera_msi_probe,
	.हटाओ = altera_msi_हटाओ,
पूर्ण;

अटल पूर्णांक __init altera_msi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&altera_msi_driver);
पूर्ण

अटल व्योम __निकास altera_msi_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&altera_msi_driver);
पूर्ण

subsys_initcall(altera_msi_init);
MODULE_DEVICE_TABLE(of, altera_msi_of_match);
module_निकास(altera_msi_निकास);
MODULE_LICENSE("GPL v2");
