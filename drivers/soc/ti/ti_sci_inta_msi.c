<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments' K3 Interrupt Aggregator MSI bus
 *
 * Copyright (C) 2018-2019 Texas Instruments Incorporated - http://www.ti.com/
 *	Lokesh Vutla <lokeshvutla@ti.com>
 */

#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/soc/ti/ti_sci_पूर्णांकa_msi.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>

अटल व्योम ti_sci_पूर्णांकa_msi_ग_लिखो_msg(काष्ठा irq_data *data,
				      काष्ठा msi_msg *msg)
अणु
	/* Nothing to करो */
पूर्ण

अटल व्योम ti_sci_पूर्णांकa_msi_compose_msi_msg(काष्ठा irq_data *data,
					    काष्ठा msi_msg *msg)
अणु
	/* Nothing to करो */
पूर्ण

अटल व्योम ti_sci_पूर्णांकa_msi_update_chip_ops(काष्ठा msi_करोमुख्य_info *info)
अणु
	काष्ठा irq_chip *chip = info->chip;

	अगर (WARN_ON(!chip))
		वापस;

	chip->irq_request_resources = irq_chip_request_resources_parent;
	chip->irq_release_resources = irq_chip_release_resources_parent;
	chip->irq_compose_msi_msg = ti_sci_पूर्णांकa_msi_compose_msi_msg;
	chip->irq_ग_लिखो_msi_msg = ti_sci_पूर्णांकa_msi_ग_लिखो_msg;
	chip->irq_set_type = irq_chip_set_type_parent;
	chip->irq_unmask = irq_chip_unmask_parent;
	chip->irq_mask = irq_chip_mask_parent;
	chip->irq_ack = irq_chip_ack_parent;
पूर्ण

काष्ठा irq_करोमुख्य *ti_sci_पूर्णांकa_msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
						     काष्ठा msi_करोमुख्य_info *info,
						     काष्ठा irq_करोमुख्य *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	ti_sci_पूर्णांकa_msi_update_chip_ops(info);

	करोमुख्य = msi_create_irq_करोमुख्य(fwnode, info, parent);
	अगर (करोमुख्य)
		irq_करोमुख्य_update_bus_token(करोमुख्य, DOMAIN_BUS_TI_SCI_INTA_MSI);

	वापस करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_पूर्णांकa_msi_create_irq_करोमुख्य);

अटल व्योम ti_sci_पूर्णांकa_msi_मुक्त_descs(काष्ठा device *dev)
अणु
	काष्ठा msi_desc *desc, *पंचांगp;

	list_क्रम_each_entry_safe(desc, पंचांगp, dev_to_msi_list(dev), list) अणु
		list_del(&desc->list);
		मुक्त_msi_entry(desc);
	पूर्ण
पूर्ण

अटल पूर्णांक ti_sci_पूर्णांकa_msi_alloc_descs(काष्ठा device *dev,
				       काष्ठा ti_sci_resource *res)
अणु
	काष्ठा msi_desc *msi_desc;
	पूर्णांक set, i, count = 0;

	क्रम (set = 0; set < res->sets; set++) अणु
		क्रम (i = 0; i < res->desc[set].num; i++) अणु
			msi_desc = alloc_msi_entry(dev, 1, शून्य);
			अगर (!msi_desc) अणु
				ti_sci_पूर्णांकa_msi_मुक्त_descs(dev);
				वापस -ENOMEM;
			पूर्ण

			msi_desc->पूर्णांकa.dev_index = res->desc[set].start + i;
			INIT_LIST_HEAD(&msi_desc->list);
			list_add_tail(&msi_desc->list, dev_to_msi_list(dev));
			count++;
		पूर्ण
		क्रम (i = 0; i < res->desc[set].num_sec; i++) अणु
			msi_desc = alloc_msi_entry(dev, 1, शून्य);
			अगर (!msi_desc) अणु
				ti_sci_पूर्णांकa_msi_मुक्त_descs(dev);
				वापस -ENOMEM;
			पूर्ण

			msi_desc->पूर्णांकa.dev_index = res->desc[set].start_sec + i;
			INIT_LIST_HEAD(&msi_desc->list);
			list_add_tail(&msi_desc->list, dev_to_msi_list(dev));
			count++;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

पूर्णांक ti_sci_पूर्णांकa_msi_करोमुख्य_alloc_irqs(काष्ठा device *dev,
				      काष्ठा ti_sci_resource *res)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	पूर्णांक ret, nvec;

	msi_करोमुख्य = dev_get_msi_करोमुख्य(dev);
	अगर (!msi_करोमुख्य)
		वापस -EINVAL;

	अगर (pdev->id < 0)
		वापस -ENODEV;

	nvec = ti_sci_पूर्णांकa_msi_alloc_descs(dev, res);
	अगर (nvec <= 0)
		वापस nvec;

	ret = msi_करोमुख्य_alloc_irqs(msi_करोमुख्य, dev, nvec);
	अगर (ret) अणु
		dev_err(dev, "Failed to allocate IRQs %d\n", ret);
		जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	ti_sci_पूर्णांकa_msi_मुक्त_descs(&pdev->dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_पूर्णांकa_msi_करोमुख्य_alloc_irqs);

व्योम ti_sci_पूर्णांकa_msi_करोमुख्य_मुक्त_irqs(काष्ठा device *dev)
अणु
	msi_करोमुख्य_मुक्त_irqs(dev->msi_करोमुख्य, dev);
	ti_sci_पूर्णांकa_msi_मुक्त_descs(dev);
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_पूर्णांकa_msi_करोमुख्य_मुक्त_irqs);

अचिन्हित पूर्णांक ti_sci_पूर्णांकa_msi_get_virq(काष्ठा device *dev, u32 dev_index)
अणु
	काष्ठा msi_desc *desc;

	क्रम_each_msi_entry(desc, dev)
		अगर (desc->पूर्णांकa.dev_index == dev_index)
			वापस desc->irq;

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_पूर्णांकa_msi_get_virq);
