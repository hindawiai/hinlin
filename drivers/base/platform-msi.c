<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MSI framework क्रम platक्रमm devices
 *
 * Copyright (C) 2015 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/msi.h>
#समावेश <linux/slab.h>

#घोषणा DEV_ID_SHIFT	21
#घोषणा MAX_DEV_MSIS	(1 << (32 - DEV_ID_SHIFT))

/*
 * Internal data काष्ठाure containing a (made up, but unique) devid
 * and the callback to ग_लिखो the MSI message.
 */
काष्ठा platक्रमm_msi_priv_data अणु
	काष्ठा device		*dev;
	व्योम 			*host_data;
	msi_alloc_info_t	arg;
	irq_ग_लिखो_msi_msg_t	ग_लिखो_msg;
	पूर्णांक			devid;
पूर्ण;

/* The devid allocator */
अटल DEFINE_IDA(platक्रमm_msi_devid_ida);

#अगर_घोषित GENERIC_MSI_DOMAIN_OPS
/*
 * Convert an msi_desc to a globaly unique identअगरier (per-device
 * devid + msi_desc position in the msi_list).
 */
अटल irq_hw_number_t platक्रमm_msi_calc_hwirq(काष्ठा msi_desc *desc)
अणु
	u32 devid;

	devid = desc->platक्रमm.msi_priv_data->devid;

	वापस (devid << (32 - DEV_ID_SHIFT)) | desc->platक्रमm.msi_index;
पूर्ण

अटल व्योम platक्रमm_msi_set_desc(msi_alloc_info_t *arg, काष्ठा msi_desc *desc)
अणु
	arg->desc = desc;
	arg->hwirq = platक्रमm_msi_calc_hwirq(desc);
पूर्ण

अटल पूर्णांक platक्रमm_msi_init(काष्ठा irq_करोमुख्य *करोमुख्य,
			     काष्ठा msi_करोमुख्य_info *info,
			     अचिन्हित पूर्णांक virq, irq_hw_number_t hwirq,
			     msi_alloc_info_t *arg)
अणु
	वापस irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
					     info->chip, info->chip_data);
पूर्ण

अटल व्योम platक्रमm_msi_set_proxy_dev(msi_alloc_info_t *arg)
अणु
	arg->flags |= MSI_ALLOC_FLAGS_PROXY_DEVICE;
पूर्ण
#अन्यथा
#घोषणा platक्रमm_msi_set_desc		शून्य
#घोषणा platक्रमm_msi_init		शून्य
#घोषणा platक्रमm_msi_set_proxy_dev(x)	करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर

अटल व्योम platक्रमm_msi_update_करोm_ops(काष्ठा msi_करोमुख्य_info *info)
अणु
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;

	BUG_ON(!ops);

	अगर (ops->msi_init == शून्य)
		ops->msi_init = platक्रमm_msi_init;
	अगर (ops->set_desc == शून्य)
		ops->set_desc = platक्रमm_msi_set_desc;
पूर्ण

अटल व्योम platक्रमm_msi_ग_लिखो_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा msi_desc *desc = irq_data_get_msi_desc(data);
	काष्ठा platक्रमm_msi_priv_data *priv_data;

	priv_data = desc->platक्रमm.msi_priv_data;

	priv_data->ग_लिखो_msg(desc, msg);
पूर्ण

अटल व्योम platक्रमm_msi_update_chip_ops(काष्ठा msi_करोमुख्य_info *info)
अणु
	काष्ठा irq_chip *chip = info->chip;

	BUG_ON(!chip);
	अगर (!chip->irq_mask)
		chip->irq_mask = irq_chip_mask_parent;
	अगर (!chip->irq_unmask)
		chip->irq_unmask = irq_chip_unmask_parent;
	अगर (!chip->irq_eoi)
		chip->irq_eoi = irq_chip_eoi_parent;
	अगर (!chip->irq_set_affinity)
		chip->irq_set_affinity = msi_करोमुख्य_set_affinity;
	अगर (!chip->irq_ग_लिखो_msi_msg)
		chip->irq_ग_लिखो_msi_msg = platक्रमm_msi_ग_लिखो_msg;
	अगर (WARN_ON((info->flags & MSI_FLAG_LEVEL_CAPABLE) &&
		    !(chip->flags & IRQCHIP_SUPPORTS_LEVEL_MSI)))
		info->flags &= ~MSI_FLAG_LEVEL_CAPABLE;
पूर्ण

अटल व्योम platक्रमm_msi_मुक्त_descs(काष्ठा device *dev, पूर्णांक base, पूर्णांक nvec)
अणु
	काष्ठा msi_desc *desc, *पंचांगp;

	list_क्रम_each_entry_safe(desc, पंचांगp, dev_to_msi_list(dev), list) अणु
		अगर (desc->platक्रमm.msi_index >= base &&
		    desc->platक्रमm.msi_index < (base + nvec)) अणु
			list_del(&desc->list);
			मुक्त_msi_entry(desc);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक platक्रमm_msi_alloc_descs_with_irq(काष्ठा device *dev, पूर्णांक virq,
					     पूर्णांक nvec,
					     काष्ठा platक्रमm_msi_priv_data *data)

अणु
	काष्ठा msi_desc *desc;
	पूर्णांक i, base = 0;

	अगर (!list_empty(dev_to_msi_list(dev))) अणु
		desc = list_last_entry(dev_to_msi_list(dev),
				       काष्ठा msi_desc, list);
		base = desc->platक्रमm.msi_index + 1;
	पूर्ण

	क्रम (i = 0; i < nvec; i++) अणु
		desc = alloc_msi_entry(dev, 1, शून्य);
		अगर (!desc)
			अवरोध;

		desc->platक्रमm.msi_priv_data = data;
		desc->platक्रमm.msi_index = base + i;
		desc->irq = virq ? virq + i : 0;

		list_add_tail(&desc->list, dev_to_msi_list(dev));
	पूर्ण

	अगर (i != nvec) अणु
		/* Clean up the mess */
		platक्रमm_msi_मुक्त_descs(dev, base, nvec);

		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_msi_alloc_descs(काष्ठा device *dev, पूर्णांक nvec,
				    काष्ठा platक्रमm_msi_priv_data *data)

अणु
	वापस platक्रमm_msi_alloc_descs_with_irq(dev, 0, nvec, data);
पूर्ण

/**
 * platक्रमm_msi_create_irq_करोमुख्य - Create a platक्रमm MSI पूर्णांकerrupt करोमुख्य
 * @fwnode:		Optional fwnode of the पूर्णांकerrupt controller
 * @info:	MSI करोमुख्य info
 * @parent:	Parent irq करोमुख्य
 *
 * Updates the करोमुख्य and chip ops and creates a platक्रमm MSI
 * पूर्णांकerrupt करोमुख्य.
 *
 * Returns:
 * A करोमुख्य poपूर्णांकer or शून्य in हाल of failure.
 */
काष्ठा irq_करोमुख्य *platक्रमm_msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
						  काष्ठा msi_करोमुख्य_info *info,
						  काष्ठा irq_करोमुख्य *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (info->flags & MSI_FLAG_USE_DEF_DOM_OPS)
		platक्रमm_msi_update_करोm_ops(info);
	अगर (info->flags & MSI_FLAG_USE_DEF_CHIP_OPS)
		platक्रमm_msi_update_chip_ops(info);

	करोमुख्य = msi_create_irq_करोमुख्य(fwnode, info, parent);
	अगर (करोमुख्य)
		irq_करोमुख्य_update_bus_token(करोमुख्य, DOMAIN_BUS_PLATFORM_MSI);

	वापस करोमुख्य;
पूर्ण

अटल काष्ठा platक्रमm_msi_priv_data *
platक्रमm_msi_alloc_priv_data(काष्ठा device *dev, अचिन्हित पूर्णांक nvec,
			     irq_ग_लिखो_msi_msg_t ग_लिखो_msi_msg)
अणु
	काष्ठा platक्रमm_msi_priv_data *datap;
	/*
	 * Limit the number of पूर्णांकerrupts to 2048 per device. Should we
	 * need to bump this up, DEV_ID_SHIFT should be adjusted
	 * accordingly (which would impact the max number of MSI
	 * capable devices).
	 */
	अगर (!dev->msi_करोमुख्य || !ग_लिखो_msi_msg || !nvec || nvec > MAX_DEV_MSIS)
		वापस ERR_PTR(-EINVAL);

	अगर (dev->msi_करोमुख्य->bus_token != DOMAIN_BUS_PLATFORM_MSI) अणु
		dev_err(dev, "Incompatible msi_domain, giving up\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Alपढ़ोy had a helping of MSI? Greed... */
	अगर (!list_empty(dev_to_msi_list(dev)))
		वापस ERR_PTR(-EBUSY);

	datap = kzalloc(माप(*datap), GFP_KERNEL);
	अगर (!datap)
		वापस ERR_PTR(-ENOMEM);

	datap->devid = ida_simple_get(&platक्रमm_msi_devid_ida,
				      0, 1 << DEV_ID_SHIFT, GFP_KERNEL);
	अगर (datap->devid < 0) अणु
		पूर्णांक err = datap->devid;
		kमुक्त(datap);
		वापस ERR_PTR(err);
	पूर्ण

	datap->ग_लिखो_msg = ग_लिखो_msi_msg;
	datap->dev = dev;

	वापस datap;
पूर्ण

अटल व्योम platक्रमm_msi_मुक्त_priv_data(काष्ठा platक्रमm_msi_priv_data *data)
अणु
	ida_simple_हटाओ(&platक्रमm_msi_devid_ida, data->devid);
	kमुक्त(data);
पूर्ण

/**
 * platक्रमm_msi_करोमुख्य_alloc_irqs - Allocate MSI पूर्णांकerrupts क्रम @dev
 * @dev:		The device क्रम which to allocate पूर्णांकerrupts
 * @nvec:		The number of पूर्णांकerrupts to allocate
 * @ग_लिखो_msi_msg:	Callback to ग_लिखो an पूर्णांकerrupt message क्रम @dev
 *
 * Returns:
 * Zero क्रम success, or an error code in हाल of failure
 */
पूर्णांक platक्रमm_msi_करोमुख्य_alloc_irqs(काष्ठा device *dev, अचिन्हित पूर्णांक nvec,
				   irq_ग_लिखो_msi_msg_t ग_लिखो_msi_msg)
अणु
	काष्ठा platक्रमm_msi_priv_data *priv_data;
	पूर्णांक err;

	priv_data = platक्रमm_msi_alloc_priv_data(dev, nvec, ग_लिखो_msi_msg);
	अगर (IS_ERR(priv_data))
		वापस PTR_ERR(priv_data);

	err = platक्रमm_msi_alloc_descs(dev, nvec, priv_data);
	अगर (err)
		जाओ out_मुक्त_priv_data;

	err = msi_करोमुख्य_alloc_irqs(dev->msi_करोमुख्य, dev, nvec);
	अगर (err)
		जाओ out_मुक्त_desc;

	वापस 0;

out_मुक्त_desc:
	platक्रमm_msi_मुक्त_descs(dev, 0, nvec);
out_मुक्त_priv_data:
	platक्रमm_msi_मुक्त_priv_data(priv_data);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_msi_करोमुख्य_alloc_irqs);

/**
 * platक्रमm_msi_करोमुख्य_मुक्त_irqs - Free MSI पूर्णांकerrupts क्रम @dev
 * @dev:	The device क्रम which to मुक्त पूर्णांकerrupts
 */
व्योम platक्रमm_msi_करोमुख्य_मुक्त_irqs(काष्ठा device *dev)
अणु
	अगर (!list_empty(dev_to_msi_list(dev))) अणु
		काष्ठा msi_desc *desc;

		desc = first_msi_entry(dev);
		platक्रमm_msi_मुक्त_priv_data(desc->platक्रमm.msi_priv_data);
	पूर्ण

	msi_करोमुख्य_मुक्त_irqs(dev->msi_करोमुख्य, dev);
	platक्रमm_msi_मुक्त_descs(dev, 0, MAX_DEV_MSIS);
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_msi_करोमुख्य_मुक्त_irqs);

/**
 * platक्रमm_msi_get_host_data - Query the निजी data associated with
 *                              a platक्रमm-msi करोमुख्य
 * @करोमुख्य:	The platक्रमm-msi करोमुख्य
 *
 * Returns the निजी data provided when calling
 * platक्रमm_msi_create_device_करोमुख्य.
 */
व्योम *platक्रमm_msi_get_host_data(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा platक्रमm_msi_priv_data *data = करोमुख्य->host_data;
	वापस data->host_data;
पूर्ण

/**
 * __platक्रमm_msi_create_device_करोमुख्य - Create a platक्रमm-msi करोमुख्य
 *
 * @dev:		The device generating the MSIs
 * @nvec:		The number of MSIs that need to be allocated
 * @is_tree:		flag to indicate tree hierarchy
 * @ग_लिखो_msi_msg:	Callback to ग_लिखो an पूर्णांकerrupt message क्रम @dev
 * @ops:		The hierarchy करोमुख्य operations to use
 * @host_data:		Private data associated to this करोमुख्य
 *
 * Returns an irqकरोमुख्य क्रम @nvec पूर्णांकerrupts
 */
काष्ठा irq_करोमुख्य *
__platक्रमm_msi_create_device_करोमुख्य(काष्ठा device *dev,
				    अचिन्हित पूर्णांक nvec,
				    bool is_tree,
				    irq_ग_लिखो_msi_msg_t ग_लिखो_msi_msg,
				    स्थिर काष्ठा irq_करोमुख्य_ops *ops,
				    व्योम *host_data)
अणु
	काष्ठा platक्रमm_msi_priv_data *data;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक err;

	data = platक्रमm_msi_alloc_priv_data(dev, nvec, ग_लिखो_msi_msg);
	अगर (IS_ERR(data))
		वापस शून्य;

	data->host_data = host_data;
	करोमुख्य = irq_करोमुख्य_create_hierarchy(dev->msi_करोमुख्य, 0,
					     is_tree ? 0 : nvec,
					     dev->fwnode, ops, data);
	अगर (!करोमुख्य)
		जाओ मुक्त_priv;

	platक्रमm_msi_set_proxy_dev(&data->arg);
	err = msi_करोमुख्य_prepare_irqs(करोमुख्य->parent, dev, nvec, &data->arg);
	अगर (err)
		जाओ मुक्त_करोमुख्य;

	वापस करोमुख्य;

मुक्त_करोमुख्य:
	irq_करोमुख्य_हटाओ(करोमुख्य);
मुक्त_priv:
	platक्रमm_msi_मुक्त_priv_data(data);
	वापस शून्य;
पूर्ण

/**
 * platक्रमm_msi_करोमुख्य_मुक्त - Free पूर्णांकerrupts associated with a platक्रमm-msi
 *                            करोमुख्य
 *
 * @करोमुख्य:	The platक्रमm-msi करोमुख्य
 * @virq:	The base irq from which to perक्रमm the मुक्त operation
 * @nvec:	How many पूर्णांकerrupts to मुक्त from @virq
 */
व्योम platक्रमm_msi_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nvec)
अणु
	काष्ठा platक्रमm_msi_priv_data *data = करोमुख्य->host_data;
	काष्ठा msi_desc *desc, *पंचांगp;
	क्रम_each_msi_entry_safe(desc, पंचांगp, data->dev) अणु
		अगर (WARN_ON(!desc->irq || desc->nvec_used != 1))
			वापस;
		अगर (!(desc->irq >= virq && desc->irq < (virq + nvec)))
			जारी;

		irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, desc->irq, 1);
		list_del(&desc->list);
		मुक्त_msi_entry(desc);
	पूर्ण
पूर्ण

/**
 * platक्रमm_msi_करोमुख्य_alloc - Allocate पूर्णांकerrupts associated with
 *			       a platक्रमm-msi करोमुख्य
 *
 * @करोमुख्य:	The platक्रमm-msi करोमुख्य
 * @virq:	The base irq from which to perक्रमm the allocate operation
 * @nr_irqs:	How many पूर्णांकerrupts to मुक्त from @virq
 *
 * Return 0 on success, or an error code on failure. Must be called
 * with irq_करोमुख्य_mutex held (which can only be करोne as part of a
 * top-level पूर्णांकerrupt allocation).
 */
पूर्णांक platक्रमm_msi_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा platक्रमm_msi_priv_data *data = करोमुख्य->host_data;
	पूर्णांक err;

	err = platक्रमm_msi_alloc_descs_with_irq(data->dev, virq, nr_irqs, data);
	अगर (err)
		वापस err;

	err = msi_करोमुख्य_populate_irqs(करोमुख्य->parent, data->dev,
				       virq, nr_irqs, &data->arg);
	अगर (err)
		platक्रमm_msi_करोमुख्य_मुक्त(करोमुख्य, virq, nr_irqs);

	वापस err;
पूर्ण
