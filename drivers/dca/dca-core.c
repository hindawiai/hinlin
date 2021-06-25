<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2007 - 2009 Intel Corporation. All rights reserved.
 */

/*
 * This driver supports an पूर्णांकerface क्रम DCA clients and providers to meet.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/device.h>
#समावेश <linux/dca.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DCA_VERSION "1.12.1"

MODULE_VERSION(DCA_VERSION);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Intel Corporation");

अटल DEFINE_RAW_SPINLOCK(dca_lock);

अटल LIST_HEAD(dca_करोमुख्यs);

अटल BLOCKING_NOTIFIER_HEAD(dca_provider_chain);

अटल पूर्णांक dca_providers_blocked;

अटल काष्ठा pci_bus *dca_pci_rc_from_dev(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pci_bus *bus = pdev->bus;

	जबतक (bus->parent)
		bus = bus->parent;

	वापस bus;
पूर्ण

अटल काष्ठा dca_करोमुख्य *dca_allocate_करोमुख्य(काष्ठा pci_bus *rc)
अणु
	काष्ठा dca_करोमुख्य *करोमुख्य;

	करोमुख्य = kzalloc(माप(*करोमुख्य), GFP_NOWAIT);
	अगर (!करोमुख्य)
		वापस शून्य;

	INIT_LIST_HEAD(&करोमुख्य->dca_providers);
	करोमुख्य->pci_rc = rc;

	वापस करोमुख्य;
पूर्ण

अटल व्योम dca_मुक्त_करोमुख्य(काष्ठा dca_करोमुख्य *करोमुख्य)
अणु
	list_del(&करोमुख्य->node);
	kमुक्त(करोमुख्य);
पूर्ण

अटल पूर्णांक dca_provider_ioat_ver_3_0(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस ((pdev->venकरोr == PCI_VENDOR_ID_INTEL) &&
		((pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG0) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG1) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG2) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG3) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG4) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG5) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG6) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG7)));
पूर्ण

अटल व्योम unरेजिस्टर_dca_providers(व्योम)
अणु
	काष्ठा dca_provider *dca, *_dca;
	काष्ठा list_head unरेजिस्टरed_providers;
	काष्ठा dca_करोमुख्य *करोमुख्य;
	अचिन्हित दीर्घ flags;

	blocking_notअगरier_call_chain(&dca_provider_chain,
				     DCA_PROVIDER_REMOVE, शून्य);

	INIT_LIST_HEAD(&unरेजिस्टरed_providers);

	raw_spin_lock_irqsave(&dca_lock, flags);

	अगर (list_empty(&dca_करोमुख्यs)) अणु
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		वापस;
	पूर्ण

	/* at this poपूर्णांक only one करोमुख्य in the list is expected */
	करोमुख्य = list_first_entry(&dca_करोमुख्यs, काष्ठा dca_करोमुख्य, node);

	list_क्रम_each_entry_safe(dca, _dca, &करोमुख्य->dca_providers, node)
		list_move(&dca->node, &unरेजिस्टरed_providers);

	dca_मुक्त_करोमुख्य(करोमुख्य);

	raw_spin_unlock_irqrestore(&dca_lock, flags);

	list_क्रम_each_entry_safe(dca, _dca, &unरेजिस्टरed_providers, node) अणु
		dca_sysfs_हटाओ_provider(dca);
		list_del(&dca->node);
	पूर्ण
पूर्ण

अटल काष्ठा dca_करोमुख्य *dca_find_करोमुख्य(काष्ठा pci_bus *rc)
अणु
	काष्ठा dca_करोमुख्य *करोमुख्य;

	list_क्रम_each_entry(करोमुख्य, &dca_करोमुख्यs, node)
		अगर (करोमुख्य->pci_rc == rc)
			वापस करोमुख्य;

	वापस शून्य;
पूर्ण

अटल काष्ठा dca_करोमुख्य *dca_get_करोमुख्य(काष्ठा device *dev)
अणु
	काष्ठा pci_bus *rc;
	काष्ठा dca_करोमुख्य *करोमुख्य;

	rc = dca_pci_rc_from_dev(dev);
	करोमुख्य = dca_find_करोमुख्य(rc);

	अगर (!करोमुख्य) अणु
		अगर (dca_provider_ioat_ver_3_0(dev) && !list_empty(&dca_करोमुख्यs))
			dca_providers_blocked = 1;
	पूर्ण

	वापस करोमुख्य;
पूर्ण

अटल काष्ठा dca_provider *dca_find_provider_by_dev(काष्ठा device *dev)
अणु
	काष्ठा dca_provider *dca;
	काष्ठा pci_bus *rc;
	काष्ठा dca_करोमुख्य *करोमुख्य;

	अगर (dev) अणु
		rc = dca_pci_rc_from_dev(dev);
		करोमुख्य = dca_find_करोमुख्य(rc);
		अगर (!करोमुख्य)
			वापस शून्य;
	पूर्ण अन्यथा अणु
		अगर (!list_empty(&dca_करोमुख्यs))
			करोमुख्य = list_first_entry(&dca_करोमुख्यs,
						  काष्ठा dca_करोमुख्य,
						  node);
		अन्यथा
			वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(dca, &करोमुख्य->dca_providers, node)
		अगर ((!dev) || (dca->ops->dev_managed(dca, dev)))
			वापस dca;

	वापस शून्य;
पूर्ण

/**
 * dca_add_requester - add a dca client to the list
 * @dev - the device that wants dca service
 */
पूर्णांक dca_add_requester(काष्ठा device *dev)
अणु
	काष्ठा dca_provider *dca;
	पूर्णांक err, slot = -ENODEV;
	अचिन्हित दीर्घ flags;
	काष्ठा pci_bus *pci_rc;
	काष्ठा dca_करोमुख्य *करोमुख्य;

	अगर (!dev)
		वापस -EFAULT;

	raw_spin_lock_irqsave(&dca_lock, flags);

	/* check अगर the requester has not been added alपढ़ोy */
	dca = dca_find_provider_by_dev(dev);
	अगर (dca) अणु
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		वापस -EEXIST;
	पूर्ण

	pci_rc = dca_pci_rc_from_dev(dev);
	करोमुख्य = dca_find_करोमुख्य(pci_rc);
	अगर (!करोमुख्य) अणु
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		वापस -ENODEV;
	पूर्ण

	list_क्रम_each_entry(dca, &करोमुख्य->dca_providers, node) अणु
		slot = dca->ops->add_requester(dca, dev);
		अगर (slot >= 0)
			अवरोध;
	पूर्ण

	raw_spin_unlock_irqrestore(&dca_lock, flags);

	अगर (slot < 0)
		वापस slot;

	err = dca_sysfs_add_req(dca, dev, slot);
	अगर (err) अणु
		raw_spin_lock_irqsave(&dca_lock, flags);
		अगर (dca == dca_find_provider_by_dev(dev))
			dca->ops->हटाओ_requester(dca, dev);
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dca_add_requester);

/**
 * dca_हटाओ_requester - हटाओ a dca client from the list
 * @dev - the device that wants dca service
 */
पूर्णांक dca_हटाओ_requester(काष्ठा device *dev)
अणु
	काष्ठा dca_provider *dca;
	पूर्णांक slot;
	अचिन्हित दीर्घ flags;

	अगर (!dev)
		वापस -EFAULT;

	raw_spin_lock_irqsave(&dca_lock, flags);
	dca = dca_find_provider_by_dev(dev);
	अगर (!dca) अणु
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		वापस -ENODEV;
	पूर्ण
	slot = dca->ops->हटाओ_requester(dca, dev);
	raw_spin_unlock_irqrestore(&dca_lock, flags);

	अगर (slot < 0)
		वापस slot;

	dca_sysfs_हटाओ_req(dca, slot);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dca_हटाओ_requester);

/**
 * dca_common_get_tag - वापस the dca tag (serves both new and old api)
 * @dev - the device that wants dca service
 * @cpu - the cpuid as वापसed by get_cpu()
 */
अटल u8 dca_common_get_tag(काष्ठा device *dev, पूर्णांक cpu)
अणु
	काष्ठा dca_provider *dca;
	u8 tag;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&dca_lock, flags);

	dca = dca_find_provider_by_dev(dev);
	अगर (!dca) अणु
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		वापस -ENODEV;
	पूर्ण
	tag = dca->ops->get_tag(dca, dev, cpu);

	raw_spin_unlock_irqrestore(&dca_lock, flags);
	वापस tag;
पूर्ण

/**
 * dca3_get_tag - वापस the dca tag to the requester device
 *                क्रम the given cpu (new api)
 * @dev - the device that wants dca service
 * @cpu - the cpuid as वापसed by get_cpu()
 */
u8 dca3_get_tag(काष्ठा device *dev, पूर्णांक cpu)
अणु
	अगर (!dev)
		वापस -EFAULT;

	वापस dca_common_get_tag(dev, cpu);
पूर्ण
EXPORT_SYMBOL_GPL(dca3_get_tag);

/**
 * dca_get_tag - वापस the dca tag क्रम the given cpu (old api)
 * @cpu - the cpuid as वापसed by get_cpu()
 */
u8 dca_get_tag(पूर्णांक cpu)
अणु
	काष्ठा device *dev = शून्य;

	वापस dca_common_get_tag(dev, cpu);
पूर्ण
EXPORT_SYMBOL_GPL(dca_get_tag);

/**
 * alloc_dca_provider - get data काष्ठा क्रम describing a dca provider
 * @ops - poपूर्णांकer to काष्ठा of dca operation function poपूर्णांकers
 * @priv_size - size of extra mem to be added क्रम provider's needs
 */
काष्ठा dca_provider *alloc_dca_provider(स्थिर काष्ठा dca_ops *ops,
					पूर्णांक priv_size)
अणु
	काष्ठा dca_provider *dca;
	पूर्णांक alloc_size;

	alloc_size = (माप(*dca) + priv_size);
	dca = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!dca)
		वापस शून्य;
	dca->ops = ops;

	वापस dca;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_dca_provider);

/**
 * मुक्त_dca_provider - release the dca provider data काष्ठा
 * @ops - poपूर्णांकer to काष्ठा of dca operation function poपूर्णांकers
 * @priv_size - size of extra mem to be added क्रम provider's needs
 */
व्योम मुक्त_dca_provider(काष्ठा dca_provider *dca)
अणु
	kमुक्त(dca);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_dca_provider);

/**
 * रेजिस्टर_dca_provider - रेजिस्टर a dca provider
 * @dca - काष्ठा created by alloc_dca_provider()
 * @dev - device providing dca services
 */
पूर्णांक रेजिस्टर_dca_provider(काष्ठा dca_provider *dca, काष्ठा device *dev)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	काष्ठा dca_करोमुख्य *करोमुख्य, *newकरोमुख्य = शून्य;

	raw_spin_lock_irqsave(&dca_lock, flags);
	अगर (dca_providers_blocked) अणु
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		वापस -ENODEV;
	पूर्ण
	raw_spin_unlock_irqrestore(&dca_lock, flags);

	err = dca_sysfs_add_provider(dca, dev);
	अगर (err)
		वापस err;

	raw_spin_lock_irqsave(&dca_lock, flags);
	करोमुख्य = dca_get_करोमुख्य(dev);
	अगर (!करोमुख्य) अणु
		काष्ठा pci_bus *rc;

		अगर (dca_providers_blocked) अणु
			raw_spin_unlock_irqrestore(&dca_lock, flags);
			dca_sysfs_हटाओ_provider(dca);
			unरेजिस्टर_dca_providers();
			वापस -ENODEV;
		पूर्ण

		raw_spin_unlock_irqrestore(&dca_lock, flags);
		rc = dca_pci_rc_from_dev(dev);
		newकरोमुख्य = dca_allocate_करोमुख्य(rc);
		अगर (!newकरोमुख्य)
			वापस -ENODEV;
		raw_spin_lock_irqsave(&dca_lock, flags);
		/* Recheck, we might have raced after dropping the lock */
		करोमुख्य = dca_get_करोमुख्य(dev);
		अगर (!करोमुख्य) अणु
			करोमुख्य = newकरोमुख्य;
			newकरोमुख्य = शून्य;
			list_add(&करोमुख्य->node, &dca_करोमुख्यs);
		पूर्ण
	पूर्ण
	list_add(&dca->node, &करोमुख्य->dca_providers);
	raw_spin_unlock_irqrestore(&dca_lock, flags);

	blocking_notअगरier_call_chain(&dca_provider_chain,
				     DCA_PROVIDER_ADD, शून्य);
	kमुक्त(newकरोमुख्य);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_dca_provider);

/**
 * unरेजिस्टर_dca_provider - हटाओ a dca provider
 * @dca - काष्ठा created by alloc_dca_provider()
 */
व्योम unरेजिस्टर_dca_provider(काष्ठा dca_provider *dca, काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pci_bus *pci_rc;
	काष्ठा dca_करोमुख्य *करोमुख्य;

	blocking_notअगरier_call_chain(&dca_provider_chain,
				     DCA_PROVIDER_REMOVE, शून्य);

	raw_spin_lock_irqsave(&dca_lock, flags);

	अगर (list_empty(&dca_करोमुख्यs)) अणु
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		वापस;
	पूर्ण

	list_del(&dca->node);

	pci_rc = dca_pci_rc_from_dev(dev);
	करोमुख्य = dca_find_करोमुख्य(pci_rc);
	अगर (list_empty(&करोमुख्य->dca_providers))
		dca_मुक्त_करोमुख्य(करोमुख्य);

	raw_spin_unlock_irqrestore(&dca_lock, flags);

	dca_sysfs_हटाओ_provider(dca);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_dca_provider);

/**
 * dca_रेजिस्टर_notअगरy - रेजिस्टर a client's notअगरier callback
 */
व्योम dca_रेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_रेजिस्टर(&dca_provider_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(dca_रेजिस्टर_notअगरy);

/**
 * dca_unरेजिस्टर_notअगरy - हटाओ a client's notअगरier callback
 */
व्योम dca_unरेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&dca_provider_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(dca_unरेजिस्टर_notअगरy);

अटल पूर्णांक __init dca_init(व्योम)
अणु
	pr_info("dca service started, version %s\n", DCA_VERSION);
	वापस dca_sysfs_init();
पूर्ण

अटल व्योम __निकास dca_निकास(व्योम)
अणु
	dca_sysfs_निकास();
पूर्ण

arch_initcall(dca_init);
module_निकास(dca_निकास);

