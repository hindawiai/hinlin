<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Freescale Management Complex (MC) bus driver MSI support
 *
 * Copyright (C) 2015-2016 Freescale Semiconductor, Inc.
 * Author: German Rivera <German.Rivera@मुक्तscale.com>
 *
 */

#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/msi.h>
#समावेश <linux/acpi_iort.h>

#समावेश "fsl-mc-private.h"

#अगर_घोषित GENERIC_MSI_DOMAIN_OPS
/*
 * Generate a unique ID identअगरying the पूर्णांकerrupt (only used within the MSI
 * irqकरोमुख्य.  Combine the icid with the पूर्णांकerrupt index.
 */
अटल irq_hw_number_t fsl_mc_करोमुख्य_calc_hwirq(काष्ठा fsl_mc_device *dev,
						काष्ठा msi_desc *desc)
अणु
	/*
	 * Make the base hwirq value क्रम ICID*10000 so it is पढ़ोable
	 * as a decimal value in /proc/पूर्णांकerrupts.
	 */
	वापस (irq_hw_number_t)(desc->fsl_mc.msi_index + (dev->icid * 10000));
पूर्ण

अटल व्योम fsl_mc_msi_set_desc(msi_alloc_info_t *arg,
				काष्ठा msi_desc *desc)
अणु
	arg->desc = desc;
	arg->hwirq = fsl_mc_करोमुख्य_calc_hwirq(to_fsl_mc_device(desc->dev),
					      desc);
पूर्ण
#अन्यथा
#घोषणा fsl_mc_msi_set_desc शून्य
#पूर्ण_अगर

अटल व्योम fsl_mc_msi_update_करोm_ops(काष्ठा msi_करोमुख्य_info *info)
अणु
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;

	अगर (!ops)
		वापस;

	/*
	 * set_desc should not be set by the caller
	 */
	अगर (!ops->set_desc)
		ops->set_desc = fsl_mc_msi_set_desc;
पूर्ण

अटल व्योम __fsl_mc_msi_ग_लिखो_msg(काष्ठा fsl_mc_device *mc_bus_dev,
				   काष्ठा fsl_mc_device_irq *mc_dev_irq)
अणु
	पूर्णांक error;
	काष्ठा fsl_mc_device *owner_mc_dev = mc_dev_irq->mc_dev;
	काष्ठा msi_desc *msi_desc = mc_dev_irq->msi_desc;
	काष्ठा dprc_irq_cfg irq_cfg;

	/*
	 * msi_desc->msg.address is 0x0 when this function is invoked in
	 * the मुक्त_irq() code path. In this हाल, क्रम the MC, we करोn't
	 * really need to "unprogram" the MSI, so we just वापस.
	 */
	अगर (msi_desc->msg.address_lo == 0x0 && msi_desc->msg.address_hi == 0x0)
		वापस;

	अगर (!owner_mc_dev)
		वापस;

	irq_cfg.paddr = ((u64)msi_desc->msg.address_hi << 32) |
			msi_desc->msg.address_lo;
	irq_cfg.val = msi_desc->msg.data;
	irq_cfg.irq_num = msi_desc->irq;

	अगर (owner_mc_dev == mc_bus_dev) अणु
		/*
		 * IRQ is क्रम the mc_bus_dev's DPRC itself
		 */
		error = dprc_set_irq(mc_bus_dev->mc_io,
				     MC_CMD_FLAG_INTR_DIS | MC_CMD_FLAG_PRI,
				     mc_bus_dev->mc_handle,
				     mc_dev_irq->dev_irq_index,
				     &irq_cfg);
		अगर (error < 0) अणु
			dev_err(&owner_mc_dev->dev,
				"dprc_set_irq() failed: %d\n", error);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * IRQ is क्रम क्रम a child device of mc_bus_dev
		 */
		error = dprc_set_obj_irq(mc_bus_dev->mc_io,
					 MC_CMD_FLAG_INTR_DIS | MC_CMD_FLAG_PRI,
					 mc_bus_dev->mc_handle,
					 owner_mc_dev->obj_desc.type,
					 owner_mc_dev->obj_desc.id,
					 mc_dev_irq->dev_irq_index,
					 &irq_cfg);
		अगर (error < 0) अणु
			dev_err(&owner_mc_dev->dev,
				"dprc_obj_set_irq() failed: %d\n", error);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * NOTE: This function is invoked with पूर्णांकerrupts disabled
 */
अटल व्योम fsl_mc_msi_ग_लिखो_msg(काष्ठा irq_data *irq_data,
				 काष्ठा msi_msg *msg)
अणु
	काष्ठा msi_desc *msi_desc = irq_data_get_msi_desc(irq_data);
	काष्ठा fsl_mc_device *mc_bus_dev = to_fsl_mc_device(msi_desc->dev);
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_bus_dev);
	काष्ठा fsl_mc_device_irq *mc_dev_irq =
		&mc_bus->irq_resources[msi_desc->fsl_mc.msi_index];

	msi_desc->msg = *msg;

	/*
	 * Program the MSI (paddr, value) pair in the device:
	 */
	__fsl_mc_msi_ग_लिखो_msg(mc_bus_dev, mc_dev_irq);
पूर्ण

अटल व्योम fsl_mc_msi_update_chip_ops(काष्ठा msi_करोमुख्य_info *info)
अणु
	काष्ठा irq_chip *chip = info->chip;

	अगर (!chip)
		वापस;

	/*
	 * irq_ग_लिखो_msi_msg should not be set by the caller
	 */
	अगर (!chip->irq_ग_लिखो_msi_msg)
		chip->irq_ग_लिखो_msi_msg = fsl_mc_msi_ग_लिखो_msg;
पूर्ण

/**
 * fsl_mc_msi_create_irq_करोमुख्य - Create a fsl-mc MSI पूर्णांकerrupt करोमुख्य
 * @np:		Optional device-tree node of the पूर्णांकerrupt controller
 * @info:	MSI करोमुख्य info
 * @parent:	Parent irq करोमुख्य
 *
 * Updates the करोमुख्य and chip ops and creates a fsl-mc MSI
 * पूर्णांकerrupt करोमुख्य.
 *
 * Returns:
 * A करोमुख्य poपूर्णांकer or शून्य in हाल of failure.
 */
काष्ठा irq_करोमुख्य *fsl_mc_msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
						काष्ठा msi_करोमुख्य_info *info,
						काष्ठा irq_करोमुख्य *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (WARN_ON((info->flags & MSI_FLAG_LEVEL_CAPABLE)))
		info->flags &= ~MSI_FLAG_LEVEL_CAPABLE;
	अगर (info->flags & MSI_FLAG_USE_DEF_DOM_OPS)
		fsl_mc_msi_update_करोm_ops(info);
	अगर (info->flags & MSI_FLAG_USE_DEF_CHIP_OPS)
		fsl_mc_msi_update_chip_ops(info);

	करोमुख्य = msi_create_irq_करोमुख्य(fwnode, info, parent);
	अगर (करोमुख्य)
		irq_करोमुख्य_update_bus_token(करोमुख्य, DOMAIN_BUS_FSL_MC_MSI);

	वापस करोमुख्य;
पूर्ण

काष्ठा irq_करोमुख्य *fsl_mc_find_msi_करोमुख्य(काष्ठा device *dev)
अणु
	काष्ठा device *root_dprc_dev;
	काष्ठा device *bus_dev;
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	fsl_mc_get_root_dprc(dev, &root_dprc_dev);
	bus_dev = root_dprc_dev->parent;

	अगर (bus_dev->of_node) अणु
		msi_करोमुख्य = of_msi_map_get_device_करोमुख्य(dev,
						  mc_dev->icid,
						  DOMAIN_BUS_FSL_MC_MSI);

		/*
		 * अगर the msi-map property is missing assume that all the
		 * child containers inherit the करोमुख्य from the parent
		 */
		अगर (!msi_करोमुख्य)

			msi_करोमुख्य = of_msi_get_करोमुख्य(bus_dev,
						bus_dev->of_node,
						DOMAIN_BUS_FSL_MC_MSI);
	पूर्ण अन्यथा अणु
		msi_करोमुख्य = iort_get_device_करोमुख्य(dev, mc_dev->icid,
						    DOMAIN_BUS_FSL_MC_MSI);
	पूर्ण

	वापस msi_करोमुख्य;
पूर्ण

अटल व्योम fsl_mc_msi_मुक्त_descs(काष्ठा device *dev)
अणु
	काष्ठा msi_desc *desc, *पंचांगp;

	list_क्रम_each_entry_safe(desc, पंचांगp, dev_to_msi_list(dev), list) अणु
		list_del(&desc->list);
		मुक्त_msi_entry(desc);
	पूर्ण
पूर्ण

अटल पूर्णांक fsl_mc_msi_alloc_descs(काष्ठा device *dev, अचिन्हित पूर्णांक irq_count)

अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक error;
	काष्ठा msi_desc *msi_desc;

	क्रम (i = 0; i < irq_count; i++) अणु
		msi_desc = alloc_msi_entry(dev, 1, शून्य);
		अगर (!msi_desc) अणु
			dev_err(dev, "Failed to allocate msi entry\n");
			error = -ENOMEM;
			जाओ cleanup_msi_descs;
		पूर्ण

		msi_desc->fsl_mc.msi_index = i;
		INIT_LIST_HEAD(&msi_desc->list);
		list_add_tail(&msi_desc->list, dev_to_msi_list(dev));
	पूर्ण

	वापस 0;

cleanup_msi_descs:
	fsl_mc_msi_मुक्त_descs(dev);
	वापस error;
पूर्ण

पूर्णांक fsl_mc_msi_करोमुख्य_alloc_irqs(काष्ठा device *dev,
				 अचिन्हित पूर्णांक irq_count)
अणु
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	पूर्णांक error;

	अगर (!list_empty(dev_to_msi_list(dev)))
		वापस -EINVAL;

	error = fsl_mc_msi_alloc_descs(dev, irq_count);
	अगर (error < 0)
		वापस error;

	msi_करोमुख्य = dev_get_msi_करोमुख्य(dev);
	अगर (!msi_करोमुख्य) अणु
		error = -EINVAL;
		जाओ cleanup_msi_descs;
	पूर्ण

	/*
	 * NOTE: Calling this function will trigger the invocation of the
	 * its_fsl_mc_msi_prepare() callback
	 */
	error = msi_करोमुख्य_alloc_irqs(msi_करोमुख्य, dev, irq_count);

	अगर (error) अणु
		dev_err(dev, "Failed to allocate IRQs\n");
		जाओ cleanup_msi_descs;
	पूर्ण

	वापस 0;

cleanup_msi_descs:
	fsl_mc_msi_मुक्त_descs(dev);
	वापस error;
पूर्ण

व्योम fsl_mc_msi_करोमुख्य_मुक्त_irqs(काष्ठा device *dev)
अणु
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;

	msi_करोमुख्य = dev_get_msi_करोमुख्य(dev);
	अगर (!msi_करोमुख्य)
		वापस;

	msi_करोमुख्य_मुक्त_irqs(msi_करोमुख्य, dev);

	अगर (list_empty(dev_to_msi_list(dev)))
		वापस;

	fsl_mc_msi_मुक्त_descs(dev);
पूर्ण
