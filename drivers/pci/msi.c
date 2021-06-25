<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Message Signaled Interrupt (MSI)
 *
 * Copyright (C) 2003-2004 Intel
 * Copyright (C) Tom Long Nguyen (tom.l.nguyen@पूर्णांकel.com)
 * Copyright (C) 2016 Christoph Hellwig.
 */

#समावेश <linux/err.h>
#समावेश <linux/mm.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/msi.h>
#समावेश <linux/smp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/acpi_iort.h>
#समावेश <linux/slab.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_irq.h>

#समावेश "pci.h"

#अगर_घोषित CONFIG_PCI_MSI

अटल पूर्णांक pci_msi_enable = 1;
पूर्णांक pci_msi_ignore_mask;

#घोषणा msix_table_size(flags)	((flags & PCI_MSIX_FLAGS_QSIZE) + 1)

#अगर_घोषित CONFIG_PCI_MSI_IRQ_DOMAIN
अटल पूर्णांक pci_msi_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	करोमुख्य = dev_get_msi_करोमुख्य(&dev->dev);
	अगर (करोमुख्य && irq_करोमुख्य_is_hierarchy(करोमुख्य))
		वापस msi_करोमुख्य_alloc_irqs(करोमुख्य, &dev->dev, nvec);

	वापस arch_setup_msi_irqs(dev, nvec, type);
पूर्ण

अटल व्योम pci_msi_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	करोमुख्य = dev_get_msi_करोमुख्य(&dev->dev);
	अगर (करोमुख्य && irq_करोमुख्य_is_hierarchy(करोमुख्य))
		msi_करोमुख्य_मुक्त_irqs(करोमुख्य, &dev->dev);
	अन्यथा
		arch_tearकरोwn_msi_irqs(dev);
पूर्ण
#अन्यथा
#घोषणा pci_msi_setup_msi_irqs		arch_setup_msi_irqs
#घोषणा pci_msi_tearकरोwn_msi_irqs	arch_tearकरोwn_msi_irqs
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_MSI_ARCH_FALLBACKS
/* Arch hooks */
पूर्णांक __weak arch_setup_msi_irq(काष्ठा pci_dev *dev, काष्ठा msi_desc *desc)
अणु
	वापस -EINVAL;
पूर्ण

व्योम __weak arch_tearकरोwn_msi_irq(अचिन्हित पूर्णांक irq)
अणु
पूर्ण

पूर्णांक __weak arch_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	काष्ठा msi_desc *entry;
	पूर्णांक ret;

	/*
	 * If an architecture wants to support multiple MSI, it needs to
	 * override arch_setup_msi_irqs()
	 */
	अगर (type == PCI_CAP_ID_MSI && nvec > 1)
		वापस 1;

	क्रम_each_pci_msi_entry(entry, dev) अणु
		ret = arch_setup_msi_irq(dev, entry);
		अगर (ret < 0)
			वापस ret;
		अगर (ret > 0)
			वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __weak arch_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;
	काष्ठा msi_desc *entry;

	क्रम_each_pci_msi_entry(entry, dev)
		अगर (entry->irq)
			क्रम (i = 0; i < entry->nvec_used; i++)
				arch_tearकरोwn_msi_irq(entry->irq + i);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI_ARCH_FALLBACKS */

अटल व्योम शेष_restore_msi_irq(काष्ठा pci_dev *dev, पूर्णांक irq)
अणु
	काष्ठा msi_desc *entry;

	entry = शून्य;
	अगर (dev->msix_enabled) अणु
		क्रम_each_pci_msi_entry(entry, dev) अणु
			अगर (irq == entry->irq)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (dev->msi_enabled)  अणु
		entry = irq_get_msi_desc(irq);
	पूर्ण

	अगर (entry)
		__pci_ग_लिखो_msi_msg(entry, &entry->msg);
पूर्ण

व्योम __weak arch_restore_msi_irqs(काष्ठा pci_dev *dev)
अणु
	वापस शेष_restore_msi_irqs(dev);
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ u32 msi_mask(अचिन्हित x)
अणु
	/* Don't shअगरt by >= width of type */
	अगर (x >= 5)
		वापस 0xffffffff;
	वापस (1 << (1 << x)) - 1;
पूर्ण

/*
 * PCI 2.3 करोes not specअगरy mask bits क्रम each MSI पूर्णांकerrupt.  Attempting to
 * mask all MSI पूर्णांकerrupts by clearing the MSI enable bit करोes not work
 * reliably as devices without an INTx disable bit will then generate a
 * level IRQ which will never be cleared.
 */
u32 __pci_msi_desc_mask_irq(काष्ठा msi_desc *desc, u32 mask, u32 flag)
अणु
	u32 mask_bits = desc->masked;

	अगर (pci_msi_ignore_mask || !desc->msi_attrib.maskbit)
		वापस 0;

	mask_bits &= ~mask;
	mask_bits |= flag;
	pci_ग_लिखो_config_dword(msi_desc_to_pci_dev(desc), desc->mask_pos,
			       mask_bits);

	वापस mask_bits;
पूर्ण

अटल व्योम msi_mask_irq(काष्ठा msi_desc *desc, u32 mask, u32 flag)
अणु
	desc->masked = __pci_msi_desc_mask_irq(desc, mask, flag);
पूर्ण

अटल व्योम __iomem *pci_msix_desc_addr(काष्ठा msi_desc *desc)
अणु
	अगर (desc->msi_attrib.is_भव)
		वापस शून्य;

	वापस desc->mask_base +
		desc->msi_attrib.entry_nr * PCI_MSIX_ENTRY_SIZE;
पूर्ण

/*
 * This पूर्णांकernal function करोes not flush PCI ग_लिखोs to the device.
 * All users must ensure that they पढ़ो from the device beक्रमe either
 * assuming that the device state is up to date, or वापसing out of this
 * file.  This saves a few milliseconds when initialising devices with lots
 * of MSI-X पूर्णांकerrupts.
 */
u32 __pci_msix_desc_mask_irq(काष्ठा msi_desc *desc, u32 flag)
अणु
	u32 mask_bits = desc->masked;
	व्योम __iomem *desc_addr;

	अगर (pci_msi_ignore_mask)
		वापस 0;

	desc_addr = pci_msix_desc_addr(desc);
	अगर (!desc_addr)
		वापस 0;

	mask_bits &= ~PCI_MSIX_ENTRY_CTRL_MASKBIT;
	अगर (flag & PCI_MSIX_ENTRY_CTRL_MASKBIT)
		mask_bits |= PCI_MSIX_ENTRY_CTRL_MASKBIT;

	ग_लिखोl(mask_bits, desc_addr + PCI_MSIX_ENTRY_VECTOR_CTRL);

	वापस mask_bits;
पूर्ण

अटल व्योम msix_mask_irq(काष्ठा msi_desc *desc, u32 flag)
अणु
	desc->masked = __pci_msix_desc_mask_irq(desc, flag);
पूर्ण

अटल व्योम msi_set_mask_bit(काष्ठा irq_data *data, u32 flag)
अणु
	काष्ठा msi_desc *desc = irq_data_get_msi_desc(data);

	अगर (desc->msi_attrib.is_msix) अणु
		msix_mask_irq(desc, flag);
		पढ़ोl(desc->mask_base);		/* Flush ग_लिखो to device */
	पूर्ण अन्यथा अणु
		अचिन्हित offset = data->irq - desc->irq;
		msi_mask_irq(desc, 1 << offset, flag << offset);
	पूर्ण
पूर्ण

/**
 * pci_msi_mask_irq - Generic IRQ chip callback to mask PCI/MSI पूर्णांकerrupts
 * @data:	poपूर्णांकer to irqdata associated to that पूर्णांकerrupt
 */
व्योम pci_msi_mask_irq(काष्ठा irq_data *data)
अणु
	msi_set_mask_bit(data, 1);
पूर्ण
EXPORT_SYMBOL_GPL(pci_msi_mask_irq);

/**
 * pci_msi_unmask_irq - Generic IRQ chip callback to unmask PCI/MSI पूर्णांकerrupts
 * @data:	poपूर्णांकer to irqdata associated to that पूर्णांकerrupt
 */
व्योम pci_msi_unmask_irq(काष्ठा irq_data *data)
अणु
	msi_set_mask_bit(data, 0);
पूर्ण
EXPORT_SYMBOL_GPL(pci_msi_unmask_irq);

व्योम शेष_restore_msi_irqs(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *entry;

	क्रम_each_pci_msi_entry(entry, dev)
		शेष_restore_msi_irq(dev, entry->irq);
पूर्ण

व्योम __pci_पढ़ो_msi_msg(काष्ठा msi_desc *entry, काष्ठा msi_msg *msg)
अणु
	काष्ठा pci_dev *dev = msi_desc_to_pci_dev(entry);

	BUG_ON(dev->current_state != PCI_D0);

	अगर (entry->msi_attrib.is_msix) अणु
		व्योम __iomem *base = pci_msix_desc_addr(entry);

		अगर (!base) अणु
			WARN_ON(1);
			वापस;
		पूर्ण

		msg->address_lo = पढ़ोl(base + PCI_MSIX_ENTRY_LOWER_ADDR);
		msg->address_hi = पढ़ोl(base + PCI_MSIX_ENTRY_UPPER_ADDR);
		msg->data = पढ़ोl(base + PCI_MSIX_ENTRY_DATA);
	पूर्ण अन्यथा अणु
		पूर्णांक pos = dev->msi_cap;
		u16 data;

		pci_पढ़ो_config_dword(dev, pos + PCI_MSI_ADDRESS_LO,
				      &msg->address_lo);
		अगर (entry->msi_attrib.is_64) अणु
			pci_पढ़ो_config_dword(dev, pos + PCI_MSI_ADDRESS_HI,
					      &msg->address_hi);
			pci_पढ़ो_config_word(dev, pos + PCI_MSI_DATA_64, &data);
		पूर्ण अन्यथा अणु
			msg->address_hi = 0;
			pci_पढ़ो_config_word(dev, pos + PCI_MSI_DATA_32, &data);
		पूर्ण
		msg->data = data;
	पूर्ण
पूर्ण

व्योम __pci_ग_लिखो_msi_msg(काष्ठा msi_desc *entry, काष्ठा msi_msg *msg)
अणु
	काष्ठा pci_dev *dev = msi_desc_to_pci_dev(entry);

	अगर (dev->current_state != PCI_D0 || pci_dev_is_disconnected(dev)) अणु
		/* Don't touch the hardware now */
	पूर्ण अन्यथा अगर (entry->msi_attrib.is_msix) अणु
		व्योम __iomem *base = pci_msix_desc_addr(entry);

		अगर (!base)
			जाओ skip;

		ग_लिखोl(msg->address_lo, base + PCI_MSIX_ENTRY_LOWER_ADDR);
		ग_लिखोl(msg->address_hi, base + PCI_MSIX_ENTRY_UPPER_ADDR);
		ग_लिखोl(msg->data, base + PCI_MSIX_ENTRY_DATA);
	पूर्ण अन्यथा अणु
		पूर्णांक pos = dev->msi_cap;
		u16 msgctl;

		pci_पढ़ो_config_word(dev, pos + PCI_MSI_FLAGS, &msgctl);
		msgctl &= ~PCI_MSI_FLAGS_QSIZE;
		msgctl |= entry->msi_attrib.multiple << 4;
		pci_ग_लिखो_config_word(dev, pos + PCI_MSI_FLAGS, msgctl);

		pci_ग_लिखो_config_dword(dev, pos + PCI_MSI_ADDRESS_LO,
				       msg->address_lo);
		अगर (entry->msi_attrib.is_64) अणु
			pci_ग_लिखो_config_dword(dev, pos + PCI_MSI_ADDRESS_HI,
					       msg->address_hi);
			pci_ग_लिखो_config_word(dev, pos + PCI_MSI_DATA_64,
					      msg->data);
		पूर्ण अन्यथा अणु
			pci_ग_लिखो_config_word(dev, pos + PCI_MSI_DATA_32,
					      msg->data);
		पूर्ण
	पूर्ण

skip:
	entry->msg = *msg;

	अगर (entry->ग_लिखो_msi_msg)
		entry->ग_लिखो_msi_msg(entry, entry->ग_लिखो_msi_msg_data);

पूर्ण

व्योम pci_ग_लिखो_msi_msg(अचिन्हित पूर्णांक irq, काष्ठा msi_msg *msg)
अणु
	काष्ठा msi_desc *entry = irq_get_msi_desc(irq);

	__pci_ग_लिखो_msi_msg(entry, msg);
पूर्ण
EXPORT_SYMBOL_GPL(pci_ग_लिखो_msi_msg);

अटल व्योम मुक्त_msi_irqs(काष्ठा pci_dev *dev)
अणु
	काष्ठा list_head *msi_list = dev_to_msi_list(&dev->dev);
	काष्ठा msi_desc *entry, *पंचांगp;
	काष्ठा attribute **msi_attrs;
	काष्ठा device_attribute *dev_attr;
	पूर्णांक i, count = 0;

	क्रम_each_pci_msi_entry(entry, dev)
		अगर (entry->irq)
			क्रम (i = 0; i < entry->nvec_used; i++)
				BUG_ON(irq_has_action(entry->irq + i));

	pci_msi_tearकरोwn_msi_irqs(dev);

	list_क्रम_each_entry_safe(entry, पंचांगp, msi_list, list) अणु
		अगर (entry->msi_attrib.is_msix) अणु
			अगर (list_is_last(&entry->list, msi_list))
				iounmap(entry->mask_base);
		पूर्ण

		list_del(&entry->list);
		मुक्त_msi_entry(entry);
	पूर्ण

	अगर (dev->msi_irq_groups) अणु
		sysfs_हटाओ_groups(&dev->dev.kobj, dev->msi_irq_groups);
		msi_attrs = dev->msi_irq_groups[0]->attrs;
		जबतक (msi_attrs[count]) अणु
			dev_attr = container_of(msi_attrs[count],
						काष्ठा device_attribute, attr);
			kमुक्त(dev_attr->attr.name);
			kमुक्त(dev_attr);
			++count;
		पूर्ण
		kमुक्त(msi_attrs);
		kमुक्त(dev->msi_irq_groups[0]);
		kमुक्त(dev->msi_irq_groups);
		dev->msi_irq_groups = शून्य;
	पूर्ण
पूर्ण

अटल व्योम pci_पूर्णांकx_क्रम_msi(काष्ठा pci_dev *dev, पूर्णांक enable)
अणु
	अगर (!(dev->dev_flags & PCI_DEV_FLAGS_MSI_INTX_DISABLE_BUG))
		pci_पूर्णांकx(dev, enable);
पूर्ण

अटल व्योम pci_msi_set_enable(काष्ठा pci_dev *dev, पूर्णांक enable)
अणु
	u16 control;

	pci_पढ़ो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, &control);
	control &= ~PCI_MSI_FLAGS_ENABLE;
	अगर (enable)
		control |= PCI_MSI_FLAGS_ENABLE;
	pci_ग_लिखो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, control);
पूर्ण

अटल व्योम __pci_restore_msi_state(काष्ठा pci_dev *dev)
अणु
	u16 control;
	काष्ठा msi_desc *entry;

	अगर (!dev->msi_enabled)
		वापस;

	entry = irq_get_msi_desc(dev->irq);

	pci_पूर्णांकx_क्रम_msi(dev, 0);
	pci_msi_set_enable(dev, 0);
	arch_restore_msi_irqs(dev);

	pci_पढ़ो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, &control);
	msi_mask_irq(entry, msi_mask(entry->msi_attrib.multi_cap),
		     entry->masked);
	control &= ~PCI_MSI_FLAGS_QSIZE;
	control |= (entry->msi_attrib.multiple << 4) | PCI_MSI_FLAGS_ENABLE;
	pci_ग_लिखो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, control);
पूर्ण

अटल व्योम pci_msix_clear_and_set_ctrl(काष्ठा pci_dev *dev, u16 clear, u16 set)
अणु
	u16 ctrl;

	pci_पढ़ो_config_word(dev, dev->msix_cap + PCI_MSIX_FLAGS, &ctrl);
	ctrl &= ~clear;
	ctrl |= set;
	pci_ग_लिखो_config_word(dev, dev->msix_cap + PCI_MSIX_FLAGS, ctrl);
पूर्ण

अटल व्योम __pci_restore_msix_state(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *entry;

	अगर (!dev->msix_enabled)
		वापस;
	BUG_ON(list_empty(dev_to_msi_list(&dev->dev)));

	/* route the table */
	pci_पूर्णांकx_क्रम_msi(dev, 0);
	pci_msix_clear_and_set_ctrl(dev, 0,
				PCI_MSIX_FLAGS_ENABLE | PCI_MSIX_FLAGS_MASKALL);

	arch_restore_msi_irqs(dev);
	क्रम_each_pci_msi_entry(entry, dev)
		msix_mask_irq(entry, entry->masked);

	pci_msix_clear_and_set_ctrl(dev, PCI_MSIX_FLAGS_MASKALL, 0);
पूर्ण

व्योम pci_restore_msi_state(काष्ठा pci_dev *dev)
अणु
	__pci_restore_msi_state(dev);
	__pci_restore_msix_state(dev);
पूर्ण
EXPORT_SYMBOL_GPL(pci_restore_msi_state);

अटल sमाप_प्रकार msi_mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा msi_desc *entry;
	अचिन्हित दीर्घ irq;
	पूर्णांक retval;

	retval = kम_से_अदीर्घ(attr->attr.name, 10, &irq);
	अगर (retval)
		वापस retval;

	entry = irq_get_msi_desc(irq);
	अगर (entry)
		वापस प्र_लिखो(buf, "%s\n",
				entry->msi_attrib.is_msix ? "msix" : "msi");

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक populate_msi_sysfs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा attribute **msi_attrs;
	काष्ठा attribute *msi_attr;
	काष्ठा device_attribute *msi_dev_attr;
	काष्ठा attribute_group *msi_irq_group;
	स्थिर काष्ठा attribute_group **msi_irq_groups;
	काष्ठा msi_desc *entry;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक num_msi = 0;
	पूर्णांक count = 0;
	पूर्णांक i;

	/* Determine how many msi entries we have */
	क्रम_each_pci_msi_entry(entry, pdev)
		num_msi += entry->nvec_used;
	अगर (!num_msi)
		वापस 0;

	/* Dynamically create the MSI attributes क्रम the PCI device */
	msi_attrs = kसुस्मृति(num_msi + 1, माप(व्योम *), GFP_KERNEL);
	अगर (!msi_attrs)
		वापस -ENOMEM;
	क्रम_each_pci_msi_entry(entry, pdev) अणु
		क्रम (i = 0; i < entry->nvec_used; i++) अणु
			msi_dev_attr = kzalloc(माप(*msi_dev_attr), GFP_KERNEL);
			अगर (!msi_dev_attr)
				जाओ error_attrs;
			msi_attrs[count] = &msi_dev_attr->attr;

			sysfs_attr_init(&msi_dev_attr->attr);
			msi_dev_attr->attr.name = kaप्र_लिखो(GFP_KERNEL, "%d",
							    entry->irq + i);
			अगर (!msi_dev_attr->attr.name)
				जाओ error_attrs;
			msi_dev_attr->attr.mode = S_IRUGO;
			msi_dev_attr->show = msi_mode_show;
			++count;
		पूर्ण
	पूर्ण

	msi_irq_group = kzalloc(माप(*msi_irq_group), GFP_KERNEL);
	अगर (!msi_irq_group)
		जाओ error_attrs;
	msi_irq_group->name = "msi_irqs";
	msi_irq_group->attrs = msi_attrs;

	msi_irq_groups = kसुस्मृति(2, माप(व्योम *), GFP_KERNEL);
	अगर (!msi_irq_groups)
		जाओ error_irq_group;
	msi_irq_groups[0] = msi_irq_group;

	ret = sysfs_create_groups(&pdev->dev.kobj, msi_irq_groups);
	अगर (ret)
		जाओ error_irq_groups;
	pdev->msi_irq_groups = msi_irq_groups;

	वापस 0;

error_irq_groups:
	kमुक्त(msi_irq_groups);
error_irq_group:
	kमुक्त(msi_irq_group);
error_attrs:
	count = 0;
	msi_attr = msi_attrs[count];
	जबतक (msi_attr) अणु
		msi_dev_attr = container_of(msi_attr, काष्ठा device_attribute, attr);
		kमुक्त(msi_attr->name);
		kमुक्त(msi_dev_attr);
		++count;
		msi_attr = msi_attrs[count];
	पूर्ण
	kमुक्त(msi_attrs);
	वापस ret;
पूर्ण

अटल काष्ठा msi_desc *
msi_setup_entry(काष्ठा pci_dev *dev, पूर्णांक nvec, काष्ठा irq_affinity *affd)
अणु
	काष्ठा irq_affinity_desc *masks = शून्य;
	काष्ठा msi_desc *entry;
	u16 control;

	अगर (affd)
		masks = irq_create_affinity_masks(nvec, affd);

	/* MSI Entry Initialization */
	entry = alloc_msi_entry(&dev->dev, nvec, masks);
	अगर (!entry)
		जाओ out;

	pci_पढ़ो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, &control);

	entry->msi_attrib.is_msix	= 0;
	entry->msi_attrib.is_64		= !!(control & PCI_MSI_FLAGS_64BIT);
	entry->msi_attrib.is_भव    = 0;
	entry->msi_attrib.entry_nr	= 0;
	entry->msi_attrib.maskbit	= !!(control & PCI_MSI_FLAGS_MASKBIT);
	entry->msi_attrib.शेष_irq	= dev->irq;	/* Save IOAPIC IRQ */
	entry->msi_attrib.multi_cap	= (control & PCI_MSI_FLAGS_QMASK) >> 1;
	entry->msi_attrib.multiple	= ilog2(__roundup_घात_of_two(nvec));

	अगर (control & PCI_MSI_FLAGS_64BIT)
		entry->mask_pos = dev->msi_cap + PCI_MSI_MASK_64;
	अन्यथा
		entry->mask_pos = dev->msi_cap + PCI_MSI_MASK_32;

	/* Save the initial mask status */
	अगर (entry->msi_attrib.maskbit)
		pci_पढ़ो_config_dword(dev, entry->mask_pos, &entry->masked);

out:
	kमुक्त(masks);
	वापस entry;
पूर्ण

अटल पूर्णांक msi_verअगरy_entries(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *entry;

	क्रम_each_pci_msi_entry(entry, dev) अणु
		अगर (entry->msg.address_hi && dev->no_64bit_msi) अणु
			pci_err(dev, "arch assigned 64-bit MSI address %#x%08x but device only supports 32 bits\n",
				entry->msg.address_hi, entry->msg.address_lo);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * msi_capability_init - configure device's MSI capability काष्ठाure
 * @dev: poपूर्णांकer to the pci_dev data काष्ठाure of MSI device function
 * @nvec: number of पूर्णांकerrupts to allocate
 * @affd: description of स्वतःmatic IRQ affinity assignments (may be %शून्य)
 *
 * Setup the MSI capability काष्ठाure of the device with the requested
 * number of पूर्णांकerrupts.  A वापस value of zero indicates the successful
 * setup of an entry with the new MSI IRQ.  A negative वापस value indicates
 * an error, and a positive वापस value indicates the number of पूर्णांकerrupts
 * which could have been allocated.
 */
अटल पूर्णांक msi_capability_init(काष्ठा pci_dev *dev, पूर्णांक nvec,
			       काष्ठा irq_affinity *affd)
अणु
	काष्ठा msi_desc *entry;
	पूर्णांक ret;
	अचिन्हित mask;

	pci_msi_set_enable(dev, 0);	/* Disable MSI during set up */

	entry = msi_setup_entry(dev, nvec, affd);
	अगर (!entry)
		वापस -ENOMEM;

	/* All MSIs are unmasked by शेष; mask them all */
	mask = msi_mask(entry->msi_attrib.multi_cap);
	msi_mask_irq(entry, mask, mask);

	list_add_tail(&entry->list, dev_to_msi_list(&dev->dev));

	/* Configure MSI capability काष्ठाure */
	ret = pci_msi_setup_msi_irqs(dev, nvec, PCI_CAP_ID_MSI);
	अगर (ret) अणु
		msi_mask_irq(entry, mask, ~mask);
		मुक्त_msi_irqs(dev);
		वापस ret;
	पूर्ण

	ret = msi_verअगरy_entries(dev);
	अगर (ret) अणु
		msi_mask_irq(entry, mask, ~mask);
		मुक्त_msi_irqs(dev);
		वापस ret;
	पूर्ण

	ret = populate_msi_sysfs(dev);
	अगर (ret) अणु
		msi_mask_irq(entry, mask, ~mask);
		मुक्त_msi_irqs(dev);
		वापस ret;
	पूर्ण

	/* Set MSI enabled bits	*/
	pci_पूर्णांकx_क्रम_msi(dev, 0);
	pci_msi_set_enable(dev, 1);
	dev->msi_enabled = 1;

	pcibios_मुक्त_irq(dev);
	dev->irq = entry->irq;
	वापस 0;
पूर्ण

अटल व्योम __iomem *msix_map_region(काष्ठा pci_dev *dev, अचिन्हित nr_entries)
अणु
	resource_माप_प्रकार phys_addr;
	u32 table_offset;
	अचिन्हित दीर्घ flags;
	u8 bir;

	pci_पढ़ो_config_dword(dev, dev->msix_cap + PCI_MSIX_TABLE,
			      &table_offset);
	bir = (u8)(table_offset & PCI_MSIX_TABLE_BIR);
	flags = pci_resource_flags(dev, bir);
	अगर (!flags || (flags & IORESOURCE_UNSET))
		वापस शून्य;

	table_offset &= PCI_MSIX_TABLE_OFFSET;
	phys_addr = pci_resource_start(dev, bir) + table_offset;

	वापस ioremap(phys_addr, nr_entries * PCI_MSIX_ENTRY_SIZE);
पूर्ण

अटल पूर्णांक msix_setup_entries(काष्ठा pci_dev *dev, व्योम __iomem *base,
			      काष्ठा msix_entry *entries, पूर्णांक nvec,
			      काष्ठा irq_affinity *affd)
अणु
	काष्ठा irq_affinity_desc *curmsk, *masks = शून्य;
	काष्ठा msi_desc *entry;
	पूर्णांक ret, i;
	पूर्णांक vec_count = pci_msix_vec_count(dev);

	अगर (affd)
		masks = irq_create_affinity_masks(nvec, affd);

	क्रम (i = 0, curmsk = masks; i < nvec; i++) अणु
		entry = alloc_msi_entry(&dev->dev, 1, curmsk);
		अगर (!entry) अणु
			अगर (!i)
				iounmap(base);
			अन्यथा
				मुक्त_msi_irqs(dev);
			/* No enough memory. Don't try again */
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		entry->msi_attrib.is_msix	= 1;
		entry->msi_attrib.is_64		= 1;
		अगर (entries)
			entry->msi_attrib.entry_nr = entries[i].entry;
		अन्यथा
			entry->msi_attrib.entry_nr = i;

		entry->msi_attrib.is_भव =
			entry->msi_attrib.entry_nr >= vec_count;

		entry->msi_attrib.शेष_irq	= dev->irq;
		entry->mask_base		= base;

		list_add_tail(&entry->list, dev_to_msi_list(&dev->dev));
		अगर (masks)
			curmsk++;
	पूर्ण
	ret = 0;
out:
	kमुक्त(masks);
	वापस ret;
पूर्ण

अटल व्योम msix_program_entries(काष्ठा pci_dev *dev,
				 काष्ठा msix_entry *entries)
अणु
	काष्ठा msi_desc *entry;
	पूर्णांक i = 0;
	व्योम __iomem *desc_addr;

	क्रम_each_pci_msi_entry(entry, dev) अणु
		अगर (entries)
			entries[i++].vector = entry->irq;

		desc_addr = pci_msix_desc_addr(entry);
		अगर (desc_addr)
			entry->masked = पढ़ोl(desc_addr +
					      PCI_MSIX_ENTRY_VECTOR_CTRL);
		अन्यथा
			entry->masked = 0;

		msix_mask_irq(entry, 1);
	पूर्ण
पूर्ण

/**
 * msix_capability_init - configure device's MSI-X capability
 * @dev: poपूर्णांकer to the pci_dev data काष्ठाure of MSI-X device function
 * @entries: poपूर्णांकer to an array of काष्ठा msix_entry entries
 * @nvec: number of @entries
 * @affd: Optional poपूर्णांकer to enable स्वतःmatic affinity assignment
 *
 * Setup the MSI-X capability काष्ठाure of device function with a
 * single MSI-X IRQ. A वापस of zero indicates the successful setup of
 * requested MSI-X entries with allocated IRQs or non-zero क्रम otherwise.
 **/
अटल पूर्णांक msix_capability_init(काष्ठा pci_dev *dev, काष्ठा msix_entry *entries,
				पूर्णांक nvec, काष्ठा irq_affinity *affd)
अणु
	पूर्णांक ret;
	u16 control;
	व्योम __iomem *base;

	/* Ensure MSI-X is disabled जबतक it is set up */
	pci_msix_clear_and_set_ctrl(dev, PCI_MSIX_FLAGS_ENABLE, 0);

	pci_पढ़ो_config_word(dev, dev->msix_cap + PCI_MSIX_FLAGS, &control);
	/* Request & Map MSI-X table region */
	base = msix_map_region(dev, msix_table_size(control));
	अगर (!base)
		वापस -ENOMEM;

	ret = msix_setup_entries(dev, base, entries, nvec, affd);
	अगर (ret)
		वापस ret;

	ret = pci_msi_setup_msi_irqs(dev, nvec, PCI_CAP_ID_MSIX);
	अगर (ret)
		जाओ out_avail;

	/* Check अगर all MSI entries honor device restrictions */
	ret = msi_verअगरy_entries(dev);
	अगर (ret)
		जाओ out_मुक्त;

	/*
	 * Some devices require MSI-X to be enabled beक्रमe we can touch the
	 * MSI-X रेजिस्टरs.  We need to mask all the vectors to prevent
	 * पूर्णांकerrupts coming in beक्रमe they're fully set up.
	 */
	pci_msix_clear_and_set_ctrl(dev, 0,
				PCI_MSIX_FLAGS_MASKALL | PCI_MSIX_FLAGS_ENABLE);

	msix_program_entries(dev, entries);

	ret = populate_msi_sysfs(dev);
	अगर (ret)
		जाओ out_मुक्त;

	/* Set MSI-X enabled bits and unmask the function */
	pci_पूर्णांकx_क्रम_msi(dev, 0);
	dev->msix_enabled = 1;
	pci_msix_clear_and_set_ctrl(dev, PCI_MSIX_FLAGS_MASKALL, 0);

	pcibios_मुक्त_irq(dev);
	वापस 0;

out_avail:
	अगर (ret < 0) अणु
		/*
		 * If we had some success, report the number of IRQs
		 * we succeeded in setting up.
		 */
		काष्ठा msi_desc *entry;
		पूर्णांक avail = 0;

		क्रम_each_pci_msi_entry(entry, dev) अणु
			अगर (entry->irq != 0)
				avail++;
		पूर्ण
		अगर (avail != 0)
			ret = avail;
	पूर्ण

out_मुक्त:
	मुक्त_msi_irqs(dev);

	वापस ret;
पूर्ण

/**
 * pci_msi_supported - check whether MSI may be enabled on a device
 * @dev: poपूर्णांकer to the pci_dev data काष्ठाure of MSI device function
 * @nvec: how many MSIs have been requested?
 *
 * Look at global flags, the device itself, and its parent buses
 * to determine अगर MSI/-X are supported क्रम the device. If MSI/-X is
 * supported वापस 1, अन्यथा वापस 0.
 **/
अटल पूर्णांक pci_msi_supported(काष्ठा pci_dev *dev, पूर्णांक nvec)
अणु
	काष्ठा pci_bus *bus;

	/* MSI must be globally enabled and supported by the device */
	अगर (!pci_msi_enable)
		वापस 0;

	अगर (!dev || dev->no_msi)
		वापस 0;

	/*
	 * You can't ask to have 0 or less MSIs configured.
	 *  a) it's stupid ..
	 *  b) the list manipulation code assumes nvec >= 1.
	 */
	अगर (nvec < 1)
		वापस 0;

	/*
	 * Any bridge which करोes NOT route MSI transactions from its
	 * secondary bus to its primary bus must set NO_MSI flag on
	 * the secondary pci_bus.
	 *
	 * The NO_MSI flag can either be set directly by:
	 * - arch-specअगरic PCI host bus controller drivers (deprecated)
	 * - quirks क्रम specअगरic PCI bridges
	 *
	 * or indirectly by platक्रमm-specअगरic PCI host bridge drivers by
	 * advertising the 'msi_domain' property, which results in
	 * the NO_MSI flag when no MSI करोमुख्य is found क्रम this bridge
	 * at probe समय.
	 */
	क्रम (bus = dev->bus; bus; bus = bus->parent)
		अगर (bus->bus_flags & PCI_BUS_FLAGS_NO_MSI)
			वापस 0;

	वापस 1;
पूर्ण

/**
 * pci_msi_vec_count - Return the number of MSI vectors a device can send
 * @dev: device to report about
 *
 * This function वापसs the number of MSI vectors a device requested via
 * Multiple Message Capable रेजिस्टर. It वापसs a negative त्रुटि_सं अगर the
 * device is not capable sending MSI पूर्णांकerrupts. Otherwise, the call succeeds
 * and वापसs a घातer of two, up to a maximum of 2^5 (32), according to the
 * MSI specअगरication.
 **/
पूर्णांक pci_msi_vec_count(काष्ठा pci_dev *dev)
अणु
	पूर्णांक ret;
	u16 msgctl;

	अगर (!dev->msi_cap)
		वापस -EINVAL;

	pci_पढ़ो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, &msgctl);
	ret = 1 << ((msgctl & PCI_MSI_FLAGS_QMASK) >> 1);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(pci_msi_vec_count);

अटल व्योम pci_msi_shutकरोwn(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *desc;
	u32 mask;

	अगर (!pci_msi_enable || !dev || !dev->msi_enabled)
		वापस;

	BUG_ON(list_empty(dev_to_msi_list(&dev->dev)));
	desc = first_pci_msi_entry(dev);

	pci_msi_set_enable(dev, 0);
	pci_पूर्णांकx_क्रम_msi(dev, 1);
	dev->msi_enabled = 0;

	/* Return the device with MSI unmasked as initial states */
	mask = msi_mask(desc->msi_attrib.multi_cap);
	/* Keep cached state to be restored */
	__pci_msi_desc_mask_irq(desc, mask, ~mask);

	/* Restore dev->irq to its शेष pin-निश्चितion IRQ */
	dev->irq = desc->msi_attrib.शेष_irq;
	pcibios_alloc_irq(dev);
पूर्ण

व्योम pci_disable_msi(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_msi_enable || !dev || !dev->msi_enabled)
		वापस;

	pci_msi_shutकरोwn(dev);
	मुक्त_msi_irqs(dev);
पूर्ण
EXPORT_SYMBOL(pci_disable_msi);

/**
 * pci_msix_vec_count - वापस the number of device's MSI-X table entries
 * @dev: poपूर्णांकer to the pci_dev data काष्ठाure of MSI-X device function
 * This function वापसs the number of device's MSI-X table entries and
 * thereक्रमe the number of MSI-X vectors device is capable of sending.
 * It वापसs a negative त्रुटि_सं अगर the device is not capable of sending MSI-X
 * पूर्णांकerrupts.
 **/
पूर्णांक pci_msix_vec_count(काष्ठा pci_dev *dev)
अणु
	u16 control;

	अगर (!dev->msix_cap)
		वापस -EINVAL;

	pci_पढ़ो_config_word(dev, dev->msix_cap + PCI_MSIX_FLAGS, &control);
	वापस msix_table_size(control);
पूर्ण
EXPORT_SYMBOL(pci_msix_vec_count);

अटल पूर्णांक __pci_enable_msix(काष्ठा pci_dev *dev, काष्ठा msix_entry *entries,
			     पूर्णांक nvec, काष्ठा irq_affinity *affd, पूर्णांक flags)
अणु
	पूर्णांक nr_entries;
	पूर्णांक i, j;

	अगर (!pci_msi_supported(dev, nvec) || dev->current_state != PCI_D0)
		वापस -EINVAL;

	nr_entries = pci_msix_vec_count(dev);
	अगर (nr_entries < 0)
		वापस nr_entries;
	अगर (nvec > nr_entries && !(flags & PCI_IRQ_VIRTUAL))
		वापस nr_entries;

	अगर (entries) अणु
		/* Check क्रम any invalid entries */
		क्रम (i = 0; i < nvec; i++) अणु
			अगर (entries[i].entry >= nr_entries)
				वापस -EINVAL;		/* invalid entry */
			क्रम (j = i + 1; j < nvec; j++) अणु
				अगर (entries[i].entry == entries[j].entry)
					वापस -EINVAL;	/* duplicate entry */
			पूर्ण
		पूर्ण
	पूर्ण

	/* Check whether driver alपढ़ोy requested क्रम MSI IRQ */
	अगर (dev->msi_enabled) अणु
		pci_info(dev, "can't enable MSI-X (MSI IRQ already assigned)\n");
		वापस -EINVAL;
	पूर्ण
	वापस msix_capability_init(dev, entries, nvec, affd);
पूर्ण

अटल व्योम pci_msix_shutकरोwn(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *entry;

	अगर (!pci_msi_enable || !dev || !dev->msix_enabled)
		वापस;

	अगर (pci_dev_is_disconnected(dev)) अणु
		dev->msix_enabled = 0;
		वापस;
	पूर्ण

	/* Return the device with MSI-X masked as initial states */
	क्रम_each_pci_msi_entry(entry, dev) अणु
		/* Keep cached states to be restored */
		__pci_msix_desc_mask_irq(entry, 1);
	पूर्ण

	pci_msix_clear_and_set_ctrl(dev, PCI_MSIX_FLAGS_ENABLE, 0);
	pci_पूर्णांकx_क्रम_msi(dev, 1);
	dev->msix_enabled = 0;
	pcibios_alloc_irq(dev);
पूर्ण

व्योम pci_disable_msix(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_msi_enable || !dev || !dev->msix_enabled)
		वापस;

	pci_msix_shutकरोwn(dev);
	मुक्त_msi_irqs(dev);
पूर्ण
EXPORT_SYMBOL(pci_disable_msix);

व्योम pci_no_msi(व्योम)
अणु
	pci_msi_enable = 0;
पूर्ण

/**
 * pci_msi_enabled - is MSI enabled?
 *
 * Returns true अगर MSI has not been disabled by the command-line option
 * pci=nomsi.
 **/
पूर्णांक pci_msi_enabled(व्योम)
अणु
	वापस pci_msi_enable;
पूर्ण
EXPORT_SYMBOL(pci_msi_enabled);

अटल पूर्णांक __pci_enable_msi_range(काष्ठा pci_dev *dev, पूर्णांक minvec, पूर्णांक maxvec,
				  काष्ठा irq_affinity *affd)
अणु
	पूर्णांक nvec;
	पूर्णांक rc;

	अगर (!pci_msi_supported(dev, minvec) || dev->current_state != PCI_D0)
		वापस -EINVAL;

	/* Check whether driver alपढ़ोy requested MSI-X IRQs */
	अगर (dev->msix_enabled) अणु
		pci_info(dev, "can't enable MSI (MSI-X already enabled)\n");
		वापस -EINVAL;
	पूर्ण

	अगर (maxvec < minvec)
		वापस -दुस्फल;

	अगर (WARN_ON_ONCE(dev->msi_enabled))
		वापस -EINVAL;

	nvec = pci_msi_vec_count(dev);
	अगर (nvec < 0)
		वापस nvec;
	अगर (nvec < minvec)
		वापस -ENOSPC;

	अगर (nvec > maxvec)
		nvec = maxvec;

	क्रम (;;) अणु
		अगर (affd) अणु
			nvec = irq_calc_affinity_vectors(minvec, nvec, affd);
			अगर (nvec < minvec)
				वापस -ENOSPC;
		पूर्ण

		rc = msi_capability_init(dev, nvec, affd);
		अगर (rc == 0)
			वापस nvec;

		अगर (rc < 0)
			वापस rc;
		अगर (rc < minvec)
			वापस -ENOSPC;

		nvec = rc;
	पूर्ण
पूर्ण

/* deprecated, करोn't use */
पूर्णांक pci_enable_msi(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc = __pci_enable_msi_range(dev, 1, 1, शून्य);
	अगर (rc < 0)
		वापस rc;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pci_enable_msi);

अटल पूर्णांक __pci_enable_msix_range(काष्ठा pci_dev *dev,
				   काष्ठा msix_entry *entries, पूर्णांक minvec,
				   पूर्णांक maxvec, काष्ठा irq_affinity *affd,
				   पूर्णांक flags)
अणु
	पूर्णांक rc, nvec = maxvec;

	अगर (maxvec < minvec)
		वापस -दुस्फल;

	अगर (WARN_ON_ONCE(dev->msix_enabled))
		वापस -EINVAL;

	क्रम (;;) अणु
		अगर (affd) अणु
			nvec = irq_calc_affinity_vectors(minvec, nvec, affd);
			अगर (nvec < minvec)
				वापस -ENOSPC;
		पूर्ण

		rc = __pci_enable_msix(dev, entries, nvec, affd, flags);
		अगर (rc == 0)
			वापस nvec;

		अगर (rc < 0)
			वापस rc;
		अगर (rc < minvec)
			वापस -ENOSPC;

		nvec = rc;
	पूर्ण
पूर्ण

/**
 * pci_enable_msix_range - configure device's MSI-X capability काष्ठाure
 * @dev: poपूर्णांकer to the pci_dev data काष्ठाure of MSI-X device function
 * @entries: poपूर्णांकer to an array of MSI-X entries
 * @minvec: minimum number of MSI-X IRQs requested
 * @maxvec: maximum number of MSI-X IRQs requested
 *
 * Setup the MSI-X capability काष्ठाure of device function with a maximum
 * possible number of पूर्णांकerrupts in the range between @minvec and @maxvec
 * upon its software driver call to request क्रम MSI-X mode enabled on its
 * hardware device function. It वापसs a negative त्रुटि_सं अगर an error occurs.
 * If it succeeds, it वापसs the actual number of पूर्णांकerrupts allocated and
 * indicates the successful configuration of MSI-X capability काष्ठाure
 * with new allocated MSI-X पूर्णांकerrupts.
 **/
पूर्णांक pci_enable_msix_range(काष्ठा pci_dev *dev, काष्ठा msix_entry *entries,
		पूर्णांक minvec, पूर्णांक maxvec)
अणु
	वापस __pci_enable_msix_range(dev, entries, minvec, maxvec, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(pci_enable_msix_range);

/**
 * pci_alloc_irq_vectors_affinity - allocate multiple IRQs क्रम a device
 * @dev:		PCI device to operate on
 * @min_vecs:		minimum number of vectors required (must be >= 1)
 * @max_vecs:		maximum (desired) number of vectors
 * @flags:		flags or quirks क्रम the allocation
 * @affd:		optional description of the affinity requirements
 *
 * Allocate up to @max_vecs पूर्णांकerrupt vectors क्रम @dev, using MSI-X or MSI
 * vectors अगर available, and fall back to a single legacy vector
 * अगर neither is available.  Return the number of vectors allocated,
 * (which might be smaller than @max_vecs) अगर successful, or a negative
 * error code on error. If less than @min_vecs पूर्णांकerrupt vectors are
 * available क्रम @dev the function will fail with -ENOSPC.
 *
 * To get the Linux IRQ number used क्रम a vector that can be passed to
 * request_irq() use the pci_irq_vector() helper.
 */
पूर्णांक pci_alloc_irq_vectors_affinity(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक min_vecs,
				   अचिन्हित पूर्णांक max_vecs, अचिन्हित पूर्णांक flags,
				   काष्ठा irq_affinity *affd)
अणु
	काष्ठा irq_affinity msi_शेष_affd = अणु0पूर्ण;
	पूर्णांक nvecs = -ENOSPC;

	अगर (flags & PCI_IRQ_AFFINITY) अणु
		अगर (!affd)
			affd = &msi_शेष_affd;
	पूर्ण अन्यथा अणु
		अगर (WARN_ON(affd))
			affd = शून्य;
	पूर्ण

	अगर (flags & PCI_IRQ_MSIX) अणु
		nvecs = __pci_enable_msix_range(dev, शून्य, min_vecs, max_vecs,
						affd, flags);
		अगर (nvecs > 0)
			वापस nvecs;
	पूर्ण

	अगर (flags & PCI_IRQ_MSI) अणु
		nvecs = __pci_enable_msi_range(dev, min_vecs, max_vecs, affd);
		अगर (nvecs > 0)
			वापस nvecs;
	पूर्ण

	/* use legacy IRQ अगर allowed */
	अगर (flags & PCI_IRQ_LEGACY) अणु
		अगर (min_vecs == 1 && dev->irq) अणु
			/*
			 * Invoke the affinity spपढ़ोing logic to ensure that
			 * the device driver can adjust queue configuration
			 * क्रम the single पूर्णांकerrupt हाल.
			 */
			अगर (affd)
				irq_create_affinity_masks(1, affd);
			pci_पूर्णांकx(dev, 1);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस nvecs;
पूर्ण
EXPORT_SYMBOL(pci_alloc_irq_vectors_affinity);

/**
 * pci_मुक्त_irq_vectors - मुक्त previously allocated IRQs क्रम a device
 * @dev:		PCI device to operate on
 *
 * Unकरोes the allocations and enabling in pci_alloc_irq_vectors().
 */
व्योम pci_मुक्त_irq_vectors(काष्ठा pci_dev *dev)
अणु
	pci_disable_msix(dev);
	pci_disable_msi(dev);
पूर्ण
EXPORT_SYMBOL(pci_मुक्त_irq_vectors);

/**
 * pci_irq_vector - वापस Linux IRQ number of a device vector
 * @dev: PCI device to operate on
 * @nr: device-relative पूर्णांकerrupt vector index (0-based).
 */
पूर्णांक pci_irq_vector(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक nr)
अणु
	अगर (dev->msix_enabled) अणु
		काष्ठा msi_desc *entry;
		पूर्णांक i = 0;

		क्रम_each_pci_msi_entry(entry, dev) अणु
			अगर (i == nr)
				वापस entry->irq;
			i++;
		पूर्ण
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	अगर (dev->msi_enabled) अणु
		काष्ठा msi_desc *entry = first_pci_msi_entry(dev);

		अगर (WARN_ON_ONCE(nr >= entry->nvec_used))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (WARN_ON_ONCE(nr > 0))
			वापस -EINVAL;
	पूर्ण

	वापस dev->irq + nr;
पूर्ण
EXPORT_SYMBOL(pci_irq_vector);

/**
 * pci_irq_get_affinity - वापस the affinity of a particular MSI vector
 * @dev:	PCI device to operate on
 * @nr:		device-relative पूर्णांकerrupt vector index (0-based).
 */
स्थिर काष्ठा cpumask *pci_irq_get_affinity(काष्ठा pci_dev *dev, पूर्णांक nr)
अणु
	अगर (dev->msix_enabled) अणु
		काष्ठा msi_desc *entry;
		पूर्णांक i = 0;

		क्रम_each_pci_msi_entry(entry, dev) अणु
			अगर (i == nr)
				वापस &entry->affinity->mask;
			i++;
		पूर्ण
		WARN_ON_ONCE(1);
		वापस शून्य;
	पूर्ण अन्यथा अगर (dev->msi_enabled) अणु
		काष्ठा msi_desc *entry = first_pci_msi_entry(dev);

		अगर (WARN_ON_ONCE(!entry || !entry->affinity ||
				 nr >= entry->nvec_used))
			वापस शून्य;

		वापस &entry->affinity[nr].mask;
	पूर्ण अन्यथा अणु
		वापस cpu_possible_mask;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pci_irq_get_affinity);

काष्ठा pci_dev *msi_desc_to_pci_dev(काष्ठा msi_desc *desc)
अणु
	वापस to_pci_dev(desc->dev);
पूर्ण
EXPORT_SYMBOL(msi_desc_to_pci_dev);

व्योम *msi_desc_to_pci_sysdata(काष्ठा msi_desc *desc)
अणु
	काष्ठा pci_dev *dev = msi_desc_to_pci_dev(desc);

	वापस dev->bus->sysdata;
पूर्ण
EXPORT_SYMBOL_GPL(msi_desc_to_pci_sysdata);

#अगर_घोषित CONFIG_PCI_MSI_IRQ_DOMAIN
/**
 * pci_msi_करोमुख्य_ग_लिखो_msg - Helper to ग_लिखो MSI message to PCI config space
 * @irq_data:	Poपूर्णांकer to पूर्णांकerrupt data of the MSI पूर्णांकerrupt
 * @msg:	Poपूर्णांकer to the message
 */
व्योम pci_msi_करोमुख्य_ग_लिखो_msg(काष्ठा irq_data *irq_data, काष्ठा msi_msg *msg)
अणु
	काष्ठा msi_desc *desc = irq_data_get_msi_desc(irq_data);

	/*
	 * For MSI-X desc->irq is always equal to irq_data->irq. For
	 * MSI only the first पूर्णांकerrupt of MULTI MSI passes the test.
	 */
	अगर (desc->irq == irq_data->irq)
		__pci_ग_लिखो_msi_msg(desc, msg);
पूर्ण

/**
 * pci_msi_करोमुख्य_calc_hwirq - Generate a unique ID क्रम an MSI source
 * @desc:	Poपूर्णांकer to the MSI descriptor
 *
 * The ID number is only used within the irqकरोमुख्य.
 */
अटल irq_hw_number_t pci_msi_करोमुख्य_calc_hwirq(काष्ठा msi_desc *desc)
अणु
	काष्ठा pci_dev *dev = msi_desc_to_pci_dev(desc);

	वापस (irq_hw_number_t)desc->msi_attrib.entry_nr |
		pci_dev_id(dev) << 11 |
		(pci_करोमुख्य_nr(dev->bus) & 0xFFFFFFFF) << 27;
पूर्ण

अटल अंतरभूत bool pci_msi_desc_is_multi_msi(काष्ठा msi_desc *desc)
अणु
	वापस !desc->msi_attrib.is_msix && desc->nvec_used > 1;
पूर्ण

/**
 * pci_msi_करोमुख्य_check_cap - Verअगरy that @करोमुख्य supports the capabilities
 * 			      क्रम @dev
 * @करोमुख्य:	The पूर्णांकerrupt करोमुख्य to check
 * @info:	The करोमुख्य info क्रम verअगरication
 * @dev:	The device to check
 *
 * Returns:
 *  0 अगर the functionality is supported
 *  1 अगर Multi MSI is requested, but the करोमुख्य करोes not support it
 *  -ENOTSUPP otherwise
 */
पूर्णांक pci_msi_करोमुख्य_check_cap(काष्ठा irq_करोमुख्य *करोमुख्य,
			     काष्ठा msi_करोमुख्य_info *info, काष्ठा device *dev)
अणु
	काष्ठा msi_desc *desc = first_pci_msi_entry(to_pci_dev(dev));

	/* Special handling to support __pci_enable_msi_range() */
	अगर (pci_msi_desc_is_multi_msi(desc) &&
	    !(info->flags & MSI_FLAG_MULTI_PCI_MSI))
		वापस 1;
	अन्यथा अगर (desc->msi_attrib.is_msix && !(info->flags & MSI_FLAG_PCI_MSIX))
		वापस -ENOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक pci_msi_करोमुख्य_handle_error(काष्ठा irq_करोमुख्य *करोमुख्य,
				       काष्ठा msi_desc *desc, पूर्णांक error)
अणु
	/* Special handling to support __pci_enable_msi_range() */
	अगर (pci_msi_desc_is_multi_msi(desc) && error == -ENOSPC)
		वापस 1;

	वापस error;
पूर्ण

अटल व्योम pci_msi_करोमुख्य_set_desc(msi_alloc_info_t *arg,
				    काष्ठा msi_desc *desc)
अणु
	arg->desc = desc;
	arg->hwirq = pci_msi_करोमुख्य_calc_hwirq(desc);
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops pci_msi_करोमुख्य_ops_शेष = अणु
	.set_desc	= pci_msi_करोमुख्य_set_desc,
	.msi_check	= pci_msi_करोमुख्य_check_cap,
	.handle_error	= pci_msi_करोमुख्य_handle_error,
पूर्ण;

अटल व्योम pci_msi_करोमुख्य_update_करोm_ops(काष्ठा msi_करोमुख्य_info *info)
अणु
	काष्ठा msi_करोमुख्य_ops *ops = info->ops;

	अगर (ops == शून्य) अणु
		info->ops = &pci_msi_करोमुख्य_ops_शेष;
	पूर्ण अन्यथा अणु
		अगर (ops->set_desc == शून्य)
			ops->set_desc = pci_msi_करोमुख्य_set_desc;
		अगर (ops->msi_check == शून्य)
			ops->msi_check = pci_msi_करोमुख्य_check_cap;
		अगर (ops->handle_error == शून्य)
			ops->handle_error = pci_msi_करोमुख्य_handle_error;
	पूर्ण
पूर्ण

अटल व्योम pci_msi_करोमुख्य_update_chip_ops(काष्ठा msi_करोमुख्य_info *info)
अणु
	काष्ठा irq_chip *chip = info->chip;

	BUG_ON(!chip);
	अगर (!chip->irq_ग_लिखो_msi_msg)
		chip->irq_ग_लिखो_msi_msg = pci_msi_करोमुख्य_ग_लिखो_msg;
	अगर (!chip->irq_mask)
		chip->irq_mask = pci_msi_mask_irq;
	अगर (!chip->irq_unmask)
		chip->irq_unmask = pci_msi_unmask_irq;
पूर्ण

/**
 * pci_msi_create_irq_करोमुख्य - Create a MSI पूर्णांकerrupt करोमुख्य
 * @fwnode:	Optional fwnode of the पूर्णांकerrupt controller
 * @info:	MSI करोमुख्य info
 * @parent:	Parent irq करोमुख्य
 *
 * Updates the करोमुख्य and chip ops and creates a MSI पूर्णांकerrupt करोमुख्य.
 *
 * Returns:
 * A करोमुख्य poपूर्णांकer or शून्य in हाल of failure.
 */
काष्ठा irq_करोमुख्य *pci_msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
					     काष्ठा msi_करोमुख्य_info *info,
					     काष्ठा irq_करोमुख्य *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (WARN_ON(info->flags & MSI_FLAG_LEVEL_CAPABLE))
		info->flags &= ~MSI_FLAG_LEVEL_CAPABLE;

	अगर (info->flags & MSI_FLAG_USE_DEF_DOM_OPS)
		pci_msi_करोमुख्य_update_करोm_ops(info);
	अगर (info->flags & MSI_FLAG_USE_DEF_CHIP_OPS)
		pci_msi_करोमुख्य_update_chip_ops(info);

	info->flags |= MSI_FLAG_ACTIVATE_EARLY;
	अगर (IS_ENABLED(CONFIG_GENERIC_IRQ_RESERVATION_MODE))
		info->flags |= MSI_FLAG_MUST_REACTIVATE;

	/* PCI-MSI is oneshot-safe */
	info->chip->flags |= IRQCHIP_ONESHOT_SAFE;

	करोमुख्य = msi_create_irq_करोमुख्य(fwnode, info, parent);
	अगर (!करोमुख्य)
		वापस शून्य;

	irq_करोमुख्य_update_bus_token(करोमुख्य, DOMAIN_BUS_PCI_MSI);
	वापस करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(pci_msi_create_irq_करोमुख्य);

/*
 * Users of the generic MSI infraकाष्ठाure expect a device to have a single ID,
 * so with DMA aliases we have to pick the least-worst compromise. Devices with
 * DMA phantom functions tend to still emit MSIs from the real function number,
 * so we ignore those and only consider topological aliases where either the
 * alias device or RID appears on a dअगरferent bus number. We also make the
 * reasonable assumption that bridges are walked in an upstream direction (so
 * the last one seen wins), and the much braver assumption that the most likely
 * हाल is that of PCI->PCIe so we should always use the alias RID. This echoes
 * the logic from पूर्णांकel_irq_remapping's set_msi_sid(), which presumably works
 * well enough in practice; in the face of the horrible PCIe<->PCI-X conditions
 * क्रम taking ownership all we can really करो is बंद our eyes and hope...
 */
अटल पूर्णांक get_msi_id_cb(काष्ठा pci_dev *pdev, u16 alias, व्योम *data)
अणु
	u32 *pa = data;
	u8 bus = PCI_BUS_NUM(*pa);

	अगर (pdev->bus->number != bus || PCI_BUS_NUM(alias) != bus)
		*pa = alias;

	वापस 0;
पूर्ण

/**
 * pci_msi_करोमुख्य_get_msi_rid - Get the MSI requester id (RID)
 * @करोमुख्य:	The पूर्णांकerrupt करोमुख्य
 * @pdev:	The PCI device.
 *
 * The RID क्रम a device is क्रमmed from the alias, with a firmware
 * supplied mapping applied
 *
 * Returns: The RID.
 */
u32 pci_msi_करोमुख्य_get_msi_rid(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा pci_dev *pdev)
अणु
	काष्ठा device_node *of_node;
	u32 rid = pci_dev_id(pdev);

	pci_क्रम_each_dma_alias(pdev, get_msi_id_cb, &rid);

	of_node = irq_करोमुख्य_get_of_node(करोमुख्य);
	rid = of_node ? of_msi_map_id(&pdev->dev, of_node, rid) :
			iort_msi_map_id(&pdev->dev, rid);

	वापस rid;
पूर्ण

/**
 * pci_msi_get_device_करोमुख्य - Get the MSI करोमुख्य क्रम a given PCI device
 * @pdev:	The PCI device
 *
 * Use the firmware data to find a device-specअगरic MSI करोमुख्य
 * (i.e. not one that is set as a शेष).
 *
 * Returns: The corresponding MSI करोमुख्य or शून्य अगर none has been found.
 */
काष्ठा irq_करोमुख्य *pci_msi_get_device_करोमुख्य(काष्ठा pci_dev *pdev)
अणु
	काष्ठा irq_करोमुख्य *करोm;
	u32 rid = pci_dev_id(pdev);

	pci_क्रम_each_dma_alias(pdev, get_msi_id_cb, &rid);
	करोm = of_msi_map_get_device_करोमुख्य(&pdev->dev, rid, DOMAIN_BUS_PCI_MSI);
	अगर (!करोm)
		करोm = iort_get_device_करोमुख्य(&pdev->dev, rid,
					     DOMAIN_BUS_PCI_MSI);
	वापस करोm;
पूर्ण

/**
 * pci_dev_has_special_msi_करोमुख्य - Check whether the device is handled by
 *				    a non-standard PCI-MSI करोमुख्य
 * @pdev:	The PCI device to check.
 *
 * Returns: True अगर the device irqकरोमुख्य or the bus irqकरोमुख्य is
 * non-standard PCI/MSI.
 */
bool pci_dev_has_special_msi_करोमुख्य(काष्ठा pci_dev *pdev)
अणु
	काष्ठा irq_करोमुख्य *करोm = dev_get_msi_करोमुख्य(&pdev->dev);

	अगर (!करोm)
		करोm = dev_get_msi_करोमुख्य(&pdev->bus->dev);

	अगर (!करोm)
		वापस true;

	वापस करोm->bus_token != DOMAIN_BUS_PCI_MSI;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI_MSI_IRQ_DOMAIN */
#पूर्ण_अगर /* CONFIG_PCI_MSI */

व्योम pci_msi_init(काष्ठा pci_dev *dev)
अणु
	u16 ctrl;

	/*
	 * Disable the MSI hardware to aव्योम screaming पूर्णांकerrupts
	 * during boot.  This is the घातer on reset शेष so
	 * usually this should be a noop.
	 */
	dev->msi_cap = pci_find_capability(dev, PCI_CAP_ID_MSI);
	अगर (!dev->msi_cap)
		वापस;

	pci_पढ़ो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, &ctrl);
	अगर (ctrl & PCI_MSI_FLAGS_ENABLE)
		pci_ग_लिखो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS,
				      ctrl & ~PCI_MSI_FLAGS_ENABLE);

	अगर (!(ctrl & PCI_MSI_FLAGS_64BIT))
		dev->no_64bit_msi = 1;
पूर्ण

व्योम pci_msix_init(काष्ठा pci_dev *dev)
अणु
	u16 ctrl;

	dev->msix_cap = pci_find_capability(dev, PCI_CAP_ID_MSIX);
	अगर (!dev->msix_cap)
		वापस;

	pci_पढ़ो_config_word(dev, dev->msix_cap + PCI_MSIX_FLAGS, &ctrl);
	अगर (ctrl & PCI_MSIX_FLAGS_ENABLE)
		pci_ग_लिखो_config_word(dev, dev->msix_cap + PCI_MSIX_FLAGS,
				      ctrl & ~PCI_MSIX_FLAGS_ENABLE);
पूर्ण
