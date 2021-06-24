<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Intel Corp.
 * Author: Jiang Liu <jiang.liu@linux.पूर्णांकel.com>
 *
 * This file is licensed under GPLv2.
 *
 * This file contains common code to support Message Signaled Interrupts क्रम
 * PCI compatible and non PCI compatible devices.
 */
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/msi.h>
#समावेश <linux/slab.h>

#समावेश "internals.h"

/**
 * alloc_msi_entry - Allocate an initialize msi_entry
 * @dev:	Poपूर्णांकer to the device क्रम which this is allocated
 * @nvec:	The number of vectors used in this entry
 * @affinity:	Optional poपूर्णांकer to an affinity mask array size of @nvec
 *
 * If @affinity is not शून्य then an affinity array[@nvec] is allocated
 * and the affinity masks and flags from @affinity are copied.
 */
काष्ठा msi_desc *alloc_msi_entry(काष्ठा device *dev, पूर्णांक nvec,
				 स्थिर काष्ठा irq_affinity_desc *affinity)
अणु
	काष्ठा msi_desc *desc;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस शून्य;

	INIT_LIST_HEAD(&desc->list);
	desc->dev = dev;
	desc->nvec_used = nvec;
	अगर (affinity) अणु
		desc->affinity = kmemdup(affinity,
			nvec * माप(*desc->affinity), GFP_KERNEL);
		अगर (!desc->affinity) अणु
			kमुक्त(desc);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस desc;
पूर्ण

व्योम मुक्त_msi_entry(काष्ठा msi_desc *entry)
अणु
	kमुक्त(entry->affinity);
	kमुक्त(entry);
पूर्ण

व्योम __get_cached_msi_msg(काष्ठा msi_desc *entry, काष्ठा msi_msg *msg)
अणु
	*msg = entry->msg;
पूर्ण

व्योम get_cached_msi_msg(अचिन्हित पूर्णांक irq, काष्ठा msi_msg *msg)
अणु
	काष्ठा msi_desc *entry = irq_get_msi_desc(irq);

	__get_cached_msi_msg(entry, msg);
पूर्ण
EXPORT_SYMBOL_GPL(get_cached_msi_msg);

#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN
अटल अंतरभूत व्योम irq_chip_ग_लिखो_msi_msg(काष्ठा irq_data *data,
					  काष्ठा msi_msg *msg)
अणु
	data->chip->irq_ग_लिखो_msi_msg(data, msg);
पूर्ण

अटल व्योम msi_check_level(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा msi_msg *msg)
अणु
	काष्ठा msi_करोमुख्य_info *info = करोमुख्य->host_data;

	/*
	 * If the MSI provider has messed with the second message and
	 * not advertized that it is level-capable, संकेत the अवरोधage.
	 */
	WARN_ON(!((info->flags & MSI_FLAG_LEVEL_CAPABLE) &&
		  (info->chip->flags & IRQCHIP_SUPPORTS_LEVEL_MSI)) &&
		(msg[1].address_lo || msg[1].address_hi || msg[1].data));
पूर्ण

/**
 * msi_करोमुख्य_set_affinity - Generic affinity setter function क्रम MSI करोमुख्यs
 * @irq_data:	The irq data associated to the पूर्णांकerrupt
 * @mask:	The affinity mask to set
 * @क्रमce:	Flag to enक्रमce setting (disable online checks)
 *
 * Intended to be used by MSI पूर्णांकerrupt controllers which are
 * implemented with hierarchical करोमुख्यs.
 */
पूर्णांक msi_करोमुख्य_set_affinity(काष्ठा irq_data *irq_data,
			    स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा irq_data *parent = irq_data->parent_data;
	काष्ठा msi_msg msg[2] = अणु [1] = अणु पूर्ण, पूर्ण;
	पूर्णांक ret;

	ret = parent->chip->irq_set_affinity(parent, mask, क्रमce);
	अगर (ret >= 0 && ret != IRQ_SET_MASK_OK_DONE) अणु
		BUG_ON(irq_chip_compose_msi_msg(irq_data, msg));
		msi_check_level(irq_data->करोमुख्य, msg);
		irq_chip_ग_लिखो_msi_msg(irq_data, msg);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक msi_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
			       काष्ठा irq_data *irq_data, bool early)
अणु
	काष्ठा msi_msg msg[2] = अणु [1] = अणु पूर्ण, पूर्ण;

	BUG_ON(irq_chip_compose_msi_msg(irq_data, msg));
	msi_check_level(irq_data->करोमुख्य, msg);
	irq_chip_ग_लिखो_msi_msg(irq_data, msg);
	वापस 0;
पूर्ण

अटल व्योम msi_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
				  काष्ठा irq_data *irq_data)
अणु
	काष्ठा msi_msg msg[2];

	स_रखो(msg, 0, माप(msg));
	irq_chip_ग_लिखो_msi_msg(irq_data, msg);
पूर्ण

अटल पूर्णांक msi_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			    अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा msi_करोमुख्य_info *info = करोमुख्य->host_data;
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;
	irq_hw_number_t hwirq = ops->get_hwirq(info, arg);
	पूर्णांक i, ret;

	अगर (irq_find_mapping(करोमुख्य, hwirq) > 0)
		वापस -EEXIST;

	अगर (करोमुख्य->parent) अणु
		ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, arg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < nr_irqs; i++) अणु
		ret = ops->msi_init(करोमुख्य, info, virq + i, hwirq + i, arg);
		अगर (ret < 0) अणु
			अगर (ops->msi_मुक्त) अणु
				क्रम (i--; i > 0; i--)
					ops->msi_मुक्त(करोमुख्य, info, virq + i);
			पूर्ण
			irq_करोमुख्य_मुक्त_irqs_top(करोमुख्य, virq, nr_irqs);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम msi_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			    अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा msi_करोमुख्य_info *info = करोमुख्य->host_data;
	पूर्णांक i;

	अगर (info->ops->msi_मुक्त) अणु
		क्रम (i = 0; i < nr_irqs; i++)
			info->ops->msi_मुक्त(करोमुख्य, info, virq + i);
	पूर्ण
	irq_करोमुख्य_मुक्त_irqs_top(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops msi_करोमुख्य_ops = अणु
	.alloc		= msi_करोमुख्य_alloc,
	.मुक्त		= msi_करोमुख्य_मुक्त,
	.activate	= msi_करोमुख्य_activate,
	.deactivate	= msi_करोमुख्य_deactivate,
पूर्ण;

अटल irq_hw_number_t msi_करोमुख्य_ops_get_hwirq(काष्ठा msi_करोमुख्य_info *info,
						msi_alloc_info_t *arg)
अणु
	वापस arg->hwirq;
पूर्ण

अटल पूर्णांक msi_करोमुख्य_ops_prepare(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
				  पूर्णांक nvec, msi_alloc_info_t *arg)
अणु
	स_रखो(arg, 0, माप(*arg));
	वापस 0;
पूर्ण

अटल व्योम msi_करोमुख्य_ops_set_desc(msi_alloc_info_t *arg,
				    काष्ठा msi_desc *desc)
अणु
	arg->desc = desc;
पूर्ण

अटल पूर्णांक msi_करोमुख्य_ops_init(काष्ठा irq_करोमुख्य *करोमुख्य,
			       काष्ठा msi_करोमुख्य_info *info,
			       अचिन्हित पूर्णांक virq, irq_hw_number_t hwirq,
			       msi_alloc_info_t *arg)
अणु
	irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq, info->chip,
				      info->chip_data);
	अगर (info->handler && info->handler_name) अणु
		__irq_set_handler(virq, info->handler, 0, info->handler_name);
		अगर (info->handler_data)
			irq_set_handler_data(virq, info->handler_data);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msi_करोमुख्य_ops_check(काष्ठा irq_करोमुख्य *करोमुख्य,
				काष्ठा msi_करोमुख्य_info *info,
				काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops msi_करोमुख्य_ops_शेष = अणु
	.get_hwirq		= msi_करोमुख्य_ops_get_hwirq,
	.msi_init		= msi_करोमुख्य_ops_init,
	.msi_check		= msi_करोमुख्य_ops_check,
	.msi_prepare		= msi_करोमुख्य_ops_prepare,
	.set_desc		= msi_करोमुख्य_ops_set_desc,
	.करोमुख्य_alloc_irqs	= __msi_करोमुख्य_alloc_irqs,
	.करोमुख्य_मुक्त_irqs	= __msi_करोमुख्य_मुक्त_irqs,
पूर्ण;

अटल व्योम msi_करोमुख्य_update_करोm_ops(काष्ठा msi_करोमुख्य_info *info)
अणु
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;

	अगर (ops == शून्य) अणु
		info->ops = &msi_करोमुख्य_ops_शेष;
		वापस;
	पूर्ण

	अगर (ops->करोमुख्य_alloc_irqs == शून्य)
		ops->करोमुख्य_alloc_irqs = msi_करोमुख्य_ops_शेष.करोमुख्य_alloc_irqs;
	अगर (ops->करोमुख्य_मुक्त_irqs == शून्य)
		ops->करोमुख्य_मुक्त_irqs = msi_करोमुख्य_ops_शेष.करोमुख्य_मुक्त_irqs;

	अगर (!(info->flags & MSI_FLAG_USE_DEF_DOM_OPS))
		वापस;

	अगर (ops->get_hwirq == शून्य)
		ops->get_hwirq = msi_करोमुख्य_ops_शेष.get_hwirq;
	अगर (ops->msi_init == शून्य)
		ops->msi_init = msi_करोमुख्य_ops_शेष.msi_init;
	अगर (ops->msi_check == शून्य)
		ops->msi_check = msi_करोमुख्य_ops_शेष.msi_check;
	अगर (ops->msi_prepare == शून्य)
		ops->msi_prepare = msi_करोमुख्य_ops_शेष.msi_prepare;
	अगर (ops->set_desc == शून्य)
		ops->set_desc = msi_करोमुख्य_ops_शेष.set_desc;
पूर्ण

अटल व्योम msi_करोमुख्य_update_chip_ops(काष्ठा msi_करोमुख्य_info *info)
अणु
	काष्ठा irq_chip *chip = info->chip;

	BUG_ON(!chip || !chip->irq_mask || !chip->irq_unmask);
	अगर (!chip->irq_set_affinity)
		chip->irq_set_affinity = msi_करोमुख्य_set_affinity;
पूर्ण

/**
 * msi_create_irq_करोमुख्य - Create a MSI पूर्णांकerrupt करोमुख्य
 * @fwnode:	Optional fwnode of the पूर्णांकerrupt controller
 * @info:	MSI करोमुख्य info
 * @parent:	Parent irq करोमुख्य
 */
काष्ठा irq_करोमुख्य *msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
					 काष्ठा msi_करोमुख्य_info *info,
					 काष्ठा irq_करोमुख्य *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	msi_करोमुख्य_update_करोm_ops(info);
	अगर (info->flags & MSI_FLAG_USE_DEF_CHIP_OPS)
		msi_करोमुख्य_update_chip_ops(info);

	करोमुख्य = irq_करोमुख्य_create_hierarchy(parent, IRQ_DOMAIN_FLAG_MSI, 0,
					     fwnode, &msi_करोमुख्य_ops, info);

	अगर (करोमुख्य && !करोमुख्य->name && info->chip)
		करोमुख्य->name = info->chip->name;

	वापस करोमुख्य;
पूर्ण

पूर्णांक msi_करोमुख्य_prepare_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			    पूर्णांक nvec, msi_alloc_info_t *arg)
अणु
	काष्ठा msi_करोमुख्य_info *info = करोमुख्य->host_data;
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;
	पूर्णांक ret;

	ret = ops->msi_check(करोमुख्य, info, dev);
	अगर (ret == 0)
		ret = ops->msi_prepare(करोमुख्य, dev, nvec, arg);

	वापस ret;
पूर्ण

पूर्णांक msi_करोमुख्य_populate_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			     पूर्णांक virq, पूर्णांक nvec, msi_alloc_info_t *arg)
अणु
	काष्ठा msi_करोमुख्य_info *info = करोमुख्य->host_data;
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;
	काष्ठा msi_desc *desc;
	पूर्णांक ret = 0;

	क्रम_each_msi_entry(desc, dev) अणु
		/* Don't even try the multi-MSI brain damage. */
		अगर (WARN_ON(!desc->irq || desc->nvec_used != 1)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (!(desc->irq >= virq && desc->irq < (virq + nvec)))
			जारी;

		ops->set_desc(arg, desc);
		/* Assumes the करोमुख्य mutex is held! */
		ret = irq_करोमुख्य_alloc_irqs_hierarchy(करोमुख्य, desc->irq, 1,
						      arg);
		अगर (ret)
			अवरोध;

		irq_set_msi_desc_off(desc->irq, 0, desc);
	पूर्ण

	अगर (ret) अणु
		/* Mop up the damage */
		क्रम_each_msi_entry(desc, dev) अणु
			अगर (!(desc->irq >= virq && desc->irq < (virq + nvec)))
				जारी;

			irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, desc->irq, 1);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Carefully check whether the device can use reservation mode. If
 * reservation mode is enabled then the early activation will assign a
 * dummy vector to the device. If the PCI/MSI device करोes not support
 * masking of the entry then this can result in spurious पूर्णांकerrupts when
 * the device driver is not असलolutely careful. But even then a malfunction
 * of the hardware could result in a spurious पूर्णांकerrupt on the dummy vector
 * and render the device unusable. If the entry can be masked then the core
 * logic will prevent the spurious पूर्णांकerrupt and reservation mode can be
 * used. For now reservation mode is restricted to PCI/MSI.
 */
अटल bool msi_check_reservation_mode(काष्ठा irq_करोमुख्य *करोमुख्य,
				       काष्ठा msi_करोमुख्य_info *info,
				       काष्ठा device *dev)
अणु
	काष्ठा msi_desc *desc;

	चयन(करोमुख्य->bus_token) अणु
	हाल DOMAIN_BUS_PCI_MSI:
	हाल DOMAIN_BUS_VMD_MSI:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (!(info->flags & MSI_FLAG_MUST_REACTIVATE))
		वापस false;

	अगर (IS_ENABLED(CONFIG_PCI_MSI) && pci_msi_ignore_mask)
		वापस false;

	/*
	 * Checking the first MSI descriptor is sufficient. MSIX supports
	 * masking and MSI करोes so when the maskbit is set.
	 */
	desc = first_msi_entry(dev);
	वापस desc->msi_attrib.is_msix || desc->msi_attrib.maskbit;
पूर्ण

पूर्णांक __msi_करोमुख्य_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			    पूर्णांक nvec)
अणु
	काष्ठा msi_करोमुख्य_info *info = करोमुख्य->host_data;
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;
	काष्ठा irq_data *irq_data;
	काष्ठा msi_desc *desc;
	msi_alloc_info_t arg = अणु पूर्ण;
	पूर्णांक i, ret, virq;
	bool can_reserve;

	ret = msi_करोमुख्य_prepare_irqs(करोमुख्य, dev, nvec, &arg);
	अगर (ret)
		वापस ret;

	क्रम_each_msi_entry(desc, dev) अणु
		ops->set_desc(&arg, desc);

		virq = __irq_करोमुख्य_alloc_irqs(करोमुख्य, -1, desc->nvec_used,
					       dev_to_node(dev), &arg, false,
					       desc->affinity);
		अगर (virq < 0) अणु
			ret = -ENOSPC;
			अगर (ops->handle_error)
				ret = ops->handle_error(करोमुख्य, desc, ret);
			अगर (ops->msi_finish)
				ops->msi_finish(&arg, ret);
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < desc->nvec_used; i++) अणु
			irq_set_msi_desc_off(virq, i, desc);
			irq_debugfs_copy_devname(virq + i, dev);
		पूर्ण
	पूर्ण

	अगर (ops->msi_finish)
		ops->msi_finish(&arg, 0);

	can_reserve = msi_check_reservation_mode(करोमुख्य, info, dev);

	/*
	 * This flag is set by the PCI layer as we need to activate
	 * the MSI entries beक्रमe the PCI layer enables MSI in the
	 * card. Otherwise the card latches a अक्रमom msi message.
	 */
	अगर (!(info->flags & MSI_FLAG_ACTIVATE_EARLY))
		जाओ skip_activate;

	क्रम_each_msi_vector(desc, i, dev) अणु
		अगर (desc->irq == i) अणु
			virq = desc->irq;
			dev_dbg(dev, "irq [%d-%d] for MSI\n",
				virq, virq + desc->nvec_used - 1);
		पूर्ण

		irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, i);
		अगर (!can_reserve) अणु
			irqd_clr_can_reserve(irq_data);
			अगर (करोमुख्य->flags & IRQ_DOMAIN_MSI_NOMASK_QUIRK)
				irqd_set_msi_nomask_quirk(irq_data);
		पूर्ण
		ret = irq_करोमुख्य_activate_irq(irq_data, can_reserve);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

skip_activate:
	/*
	 * If these पूर्णांकerrupts use reservation mode, clear the activated bit
	 * so request_irq() will assign the final vector.
	 */
	अगर (can_reserve) अणु
		क्रम_each_msi_vector(desc, i, dev) अणु
			irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, i);
			irqd_clr_activated(irq_data);
		पूर्ण
	पूर्ण
	वापस 0;

cleanup:
	क्रम_each_msi_vector(desc, i, dev) अणु
		irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, i);
		अगर (irqd_is_activated(irq_data))
			irq_करोमुख्य_deactivate_irq(irq_data);
	पूर्ण
	msi_करोमुख्य_मुक्त_irqs(करोमुख्य, dev);
	वापस ret;
पूर्ण

/**
 * msi_करोमुख्य_alloc_irqs - Allocate पूर्णांकerrupts from a MSI पूर्णांकerrupt करोमुख्य
 * @करोमुख्य:	The करोमुख्य to allocate from
 * @dev:	Poपूर्णांकer to device काष्ठा of the device क्रम which the पूर्णांकerrupts
 *		are allocated
 * @nvec:	The number of पूर्णांकerrupts to allocate
 *
 * Returns 0 on success or an error code.
 */
पूर्णांक msi_करोमुख्य_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			  पूर्णांक nvec)
अणु
	काष्ठा msi_करोमुख्य_info *info = करोमुख्य->host_data;
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;

	वापस ops->करोमुख्य_alloc_irqs(करोमुख्य, dev, nvec);
पूर्ण

व्योम __msi_करोमुख्य_मुक्त_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा msi_desc *desc;

	क्रम_each_msi_entry(desc, dev) अणु
		/*
		 * We might have failed to allocate an MSI early
		 * enough that there is no IRQ associated to this
		 * entry. If that's the case, don't करो anything.
		 */
		अगर (desc->irq) अणु
			irq_करोमुख्य_मुक्त_irqs(desc->irq, desc->nvec_used);
			desc->irq = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * __msi_करोमुख्य_मुक्त_irqs - Free पूर्णांकerrupts from a MSI पूर्णांकerrupt @करोमुख्य associated tp @dev
 * @करोमुख्य:	The करोमुख्य to managing the पूर्णांकerrupts
 * @dev:	Poपूर्णांकer to device काष्ठा of the device क्रम which the पूर्णांकerrupts
 *		are मुक्त
 */
व्योम msi_करोमुख्य_मुक्त_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा msi_करोमुख्य_info *info = करोमुख्य->host_data;
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;

	वापस ops->करोमुख्य_मुक्त_irqs(करोमुख्य, dev);
पूर्ण

/**
 * msi_get_करोमुख्य_info - Get the MSI पूर्णांकerrupt करोमुख्य info क्रम @करोमुख्य
 * @करोमुख्य:	The पूर्णांकerrupt करोमुख्य to retrieve data from
 *
 * Returns the poपूर्णांकer to the msi_करोमुख्य_info stored in
 * @करोमुख्य->host_data.
 */
काष्ठा msi_करोमुख्य_info *msi_get_करोमुख्य_info(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस (काष्ठा msi_करोमुख्य_info *)करोमुख्य->host_data;
पूर्ण

#पूर्ण_अगर /* CONFIG_GENERIC_MSI_IRQ_DOMAIN */
