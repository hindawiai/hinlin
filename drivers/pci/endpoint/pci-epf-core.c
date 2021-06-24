<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Endpoपूर्णांक *Function* (EPF) library
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <linux/pci-epc.h>
#समावेश <linux/pci-epf.h>
#समावेश <linux/pci-ep-cfs.h>

अटल DEFINE_MUTEX(pci_epf_mutex);

अटल काष्ठा bus_type pci_epf_bus_type;
अटल स्थिर काष्ठा device_type pci_epf_type;

/**
 * pci_epf_type_add_cfs() - Help function drivers to expose function specअगरic
 *                          attributes in configfs
 * @epf: the EPF device that has to be configured using configfs
 * @group: the parent configfs group (corresponding to entries in
 *         pci_epf_device_id)
 *
 * Invoke to expose function specअगरic attributes in configfs. If the function
 * driver करोes not have anything to expose (attributes configured by user),
 * वापस शून्य.
 */
काष्ठा config_group *pci_epf_type_add_cfs(काष्ठा pci_epf *epf,
					  काष्ठा config_group *group)
अणु
	काष्ठा config_group *epf_type_group;

	अगर (!epf->driver) अणु
		dev_err(&epf->dev, "epf device not bound to driver\n");
		वापस शून्य;
	पूर्ण

	अगर (!epf->driver->ops->add_cfs)
		वापस शून्य;

	mutex_lock(&epf->lock);
	epf_type_group = epf->driver->ops->add_cfs(epf, group);
	mutex_unlock(&epf->lock);

	वापस epf_type_group;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epf_type_add_cfs);

/**
 * pci_epf_unbind() - Notअगरy the function driver that the binding between the
 *		      EPF device and EPC device has been lost
 * @epf: the EPF device which has lost the binding with the EPC device
 *
 * Invoke to notअगरy the function driver that the binding between the EPF device
 * and EPC device has been lost.
 */
व्योम pci_epf_unbind(काष्ठा pci_epf *epf)
अणु
	अगर (!epf->driver) अणु
		dev_WARN(&epf->dev, "epf device not bound to driver\n");
		वापस;
	पूर्ण

	mutex_lock(&epf->lock);
	epf->driver->ops->unbind(epf);
	mutex_unlock(&epf->lock);
	module_put(epf->driver->owner);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epf_unbind);

/**
 * pci_epf_bind() - Notअगरy the function driver that the EPF device has been
 *		    bound to a EPC device
 * @epf: the EPF device which has been bound to the EPC device
 *
 * Invoke to notअगरy the function driver that it has been bound to a EPC device
 */
पूर्णांक pci_epf_bind(काष्ठा pci_epf *epf)
अणु
	पूर्णांक ret;

	अगर (!epf->driver) अणु
		dev_WARN(&epf->dev, "epf device not bound to driver\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!try_module_get(epf->driver->owner))
		वापस -EAGAIN;

	mutex_lock(&epf->lock);
	ret = epf->driver->ops->bind(epf);
	mutex_unlock(&epf->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epf_bind);

/**
 * pci_epf_मुक्त_space() - मुक्त the allocated PCI EPF रेजिस्टर space
 * @epf: the EPF device from whom to मुक्त the memory
 * @addr: the भव address of the PCI EPF रेजिस्टर space
 * @bar: the BAR number corresponding to the रेजिस्टर space
 * @type: Identअगरies अगर the allocated space is क्रम primary EPC or secondary EPC
 *
 * Invoke to मुक्त the allocated PCI EPF रेजिस्टर space.
 */
व्योम pci_epf_मुक्त_space(काष्ठा pci_epf *epf, व्योम *addr, क्रमागत pci_barno bar,
			क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा device *dev;
	काष्ठा pci_epf_bar *epf_bar;
	काष्ठा pci_epc *epc;

	अगर (!addr)
		वापस;

	अगर (type == PRIMARY_INTERFACE) अणु
		epc = epf->epc;
		epf_bar = epf->bar;
	पूर्ण अन्यथा अणु
		epc = epf->sec_epc;
		epf_bar = epf->sec_epc_bar;
	पूर्ण

	dev = epc->dev.parent;
	dma_मुक्त_coherent(dev, epf_bar[bar].size, addr,
			  epf_bar[bar].phys_addr);

	epf_bar[bar].phys_addr = 0;
	epf_bar[bar].addr = शून्य;
	epf_bar[bar].size = 0;
	epf_bar[bar].barno = 0;
	epf_bar[bar].flags = 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epf_मुक्त_space);

/**
 * pci_epf_alloc_space() - allocate memory क्रम the PCI EPF रेजिस्टर space
 * @epf: the EPF device to whom allocate the memory
 * @size: the size of the memory that has to be allocated
 * @bar: the BAR number corresponding to the allocated रेजिस्टर space
 * @align: alignment size क्रम the allocation region
 * @type: Identअगरies अगर the allocation is क्रम primary EPC or secondary EPC
 *
 * Invoke to allocate memory क्रम the PCI EPF रेजिस्टर space.
 */
व्योम *pci_epf_alloc_space(काष्ठा pci_epf *epf, माप_प्रकार size, क्रमागत pci_barno bar,
			  माप_प्रकार align, क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा pci_epf_bar *epf_bar;
	dma_addr_t phys_addr;
	काष्ठा pci_epc *epc;
	काष्ठा device *dev;
	व्योम *space;

	अगर (size < 128)
		size = 128;

	अगर (align)
		size = ALIGN(size, align);
	अन्यथा
		size = roundup_घात_of_two(size);

	अगर (type == PRIMARY_INTERFACE) अणु
		epc = epf->epc;
		epf_bar = epf->bar;
	पूर्ण अन्यथा अणु
		epc = epf->sec_epc;
		epf_bar = epf->sec_epc_bar;
	पूर्ण

	dev = epc->dev.parent;
	space = dma_alloc_coherent(dev, size, &phys_addr, GFP_KERNEL);
	अगर (!space) अणु
		dev_err(dev, "failed to allocate mem space\n");
		वापस शून्य;
	पूर्ण

	epf_bar[bar].phys_addr = phys_addr;
	epf_bar[bar].addr = space;
	epf_bar[bar].size = size;
	epf_bar[bar].barno = bar;
	epf_bar[bar].flags |= upper_32_bits(size) ?
				PCI_BASE_ADDRESS_MEM_TYPE_64 :
				PCI_BASE_ADDRESS_MEM_TYPE_32;

	वापस space;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epf_alloc_space);

अटल व्योम pci_epf_हटाओ_cfs(काष्ठा pci_epf_driver *driver)
अणु
	काष्ठा config_group *group, *पंचांगp;

	अगर (!IS_ENABLED(CONFIG_PCI_ENDPOINT_CONFIGFS))
		वापस;

	mutex_lock(&pci_epf_mutex);
	list_क्रम_each_entry_safe(group, पंचांगp, &driver->epf_group, group_entry)
		pci_ep_cfs_हटाओ_epf_group(group);
	list_del(&driver->epf_group);
	mutex_unlock(&pci_epf_mutex);
पूर्ण

/**
 * pci_epf_unरेजिस्टर_driver() - unरेजिस्टर the PCI EPF driver
 * @driver: the PCI EPF driver that has to be unरेजिस्टरed
 *
 * Invoke to unरेजिस्टर the PCI EPF driver.
 */
व्योम pci_epf_unरेजिस्टर_driver(काष्ठा pci_epf_driver *driver)
अणु
	pci_epf_हटाओ_cfs(driver);
	driver_unरेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epf_unरेजिस्टर_driver);

अटल पूर्णांक pci_epf_add_cfs(काष्ठा pci_epf_driver *driver)
अणु
	काष्ठा config_group *group;
	स्थिर काष्ठा pci_epf_device_id *id;

	अगर (!IS_ENABLED(CONFIG_PCI_ENDPOINT_CONFIGFS))
		वापस 0;

	INIT_LIST_HEAD(&driver->epf_group);

	id = driver->id_table;
	जबतक (id->name[0]) अणु
		group = pci_ep_cfs_add_epf_group(id->name);
		अगर (IS_ERR(group)) अणु
			pci_epf_हटाओ_cfs(driver);
			वापस PTR_ERR(group);
		पूर्ण

		mutex_lock(&pci_epf_mutex);
		list_add_tail(&group->group_entry, &driver->epf_group);
		mutex_unlock(&pci_epf_mutex);
		id++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __pci_epf_रेजिस्टर_driver() - रेजिस्टर a new PCI EPF driver
 * @driver: काष्ठाure representing PCI EPF driver
 * @owner: the owner of the module that रेजिस्टरs the PCI EPF driver
 *
 * Invoke to रेजिस्टर a new PCI EPF driver.
 */
पूर्णांक __pci_epf_रेजिस्टर_driver(काष्ठा pci_epf_driver *driver,
			      काष्ठा module *owner)
अणु
	पूर्णांक ret;

	अगर (!driver->ops)
		वापस -EINVAL;

	अगर (!driver->ops->bind || !driver->ops->unbind)
		वापस -EINVAL;

	driver->driver.bus = &pci_epf_bus_type;
	driver->driver.owner = owner;

	ret = driver_रेजिस्टर(&driver->driver);
	अगर (ret)
		वापस ret;

	pci_epf_add_cfs(driver);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__pci_epf_रेजिस्टर_driver);

/**
 * pci_epf_destroy() - destroy the created PCI EPF device
 * @epf: the PCI EPF device that has to be destroyed.
 *
 * Invoke to destroy the PCI EPF device created by invoking pci_epf_create().
 */
व्योम pci_epf_destroy(काष्ठा pci_epf *epf)
अणु
	device_unरेजिस्टर(&epf->dev);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epf_destroy);

/**
 * pci_epf_create() - create a new PCI EPF device
 * @name: the name of the PCI EPF device. This name will be used to bind the
 *	  the EPF device to a EPF driver
 *
 * Invoke to create a new PCI EPF device by providing the name of the function
 * device.
 */
काष्ठा pci_epf *pci_epf_create(स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	काष्ठा pci_epf *epf;
	काष्ठा device *dev;
	पूर्णांक len;

	epf = kzalloc(माप(*epf), GFP_KERNEL);
	अगर (!epf)
		वापस ERR_PTR(-ENOMEM);

	len = म_अक्षरnul(name, '.') - name;
	epf->name = kstrndup(name, len, GFP_KERNEL);
	अगर (!epf->name) अणु
		kमुक्त(epf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dev = &epf->dev;
	device_initialize(dev);
	dev->bus = &pci_epf_bus_type;
	dev->type = &pci_epf_type;
	mutex_init(&epf->lock);

	ret = dev_set_name(dev, "%s", name);
	अगर (ret) अणु
		put_device(dev);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = device_add(dev);
	अगर (ret) अणु
		put_device(dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस epf;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epf_create);

अटल व्योम pci_epf_dev_release(काष्ठा device *dev)
अणु
	काष्ठा pci_epf *epf = to_pci_epf(dev);

	kमुक्त(epf->name);
	kमुक्त(epf);
पूर्ण

अटल स्थिर काष्ठा device_type pci_epf_type = अणु
	.release	= pci_epf_dev_release,
पूर्ण;

अटल पूर्णांक
pci_epf_match_id(स्थिर काष्ठा pci_epf_device_id *id, स्थिर काष्ठा pci_epf *epf)
अणु
	जबतक (id->name[0]) अणु
		अगर (म_भेद(epf->name, id->name) == 0)
			वापस true;
		id++;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक pci_epf_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा pci_epf *epf = to_pci_epf(dev);
	काष्ठा pci_epf_driver *driver = to_pci_epf_driver(drv);

	अगर (driver->id_table)
		वापस pci_epf_match_id(driver->id_table, epf);

	वापस !म_भेद(epf->name, drv->name);
पूर्ण

अटल पूर्णांक pci_epf_device_probe(काष्ठा device *dev)
अणु
	काष्ठा pci_epf *epf = to_pci_epf(dev);
	काष्ठा pci_epf_driver *driver = to_pci_epf_driver(dev->driver);

	अगर (!driver->probe)
		वापस -ENODEV;

	epf->driver = driver;

	वापस driver->probe(epf);
पूर्ण

अटल पूर्णांक pci_epf_device_हटाओ(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा pci_epf *epf = to_pci_epf(dev);
	काष्ठा pci_epf_driver *driver = to_pci_epf_driver(dev->driver);

	अगर (driver->हटाओ)
		ret = driver->हटाओ(epf);
	epf->driver = शून्य;

	वापस ret;
पूर्ण

अटल काष्ठा bus_type pci_epf_bus_type = अणु
	.name		= "pci-epf",
	.match		= pci_epf_device_match,
	.probe		= pci_epf_device_probe,
	.हटाओ		= pci_epf_device_हटाओ,
पूर्ण;

अटल पूर्णांक __init pci_epf_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&pci_epf_bus_type);
	अगर (ret) अणु
		pr_err("failed to register pci epf bus --> %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(pci_epf_init);

अटल व्योम __निकास pci_epf_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&pci_epf_bus_type);
पूर्ण
module_निकास(pci_epf_निकास);

MODULE_DESCRIPTION("PCI EPF Library");
MODULE_AUTHOR("Kishon Vijay Abraham I <kishon@ti.com>");
MODULE_LICENSE("GPL v2");
