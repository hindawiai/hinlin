<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * core.c - contains all core device and protocol registration functions
 *
 * Copyright 2002 Adam Belay <ambx1@neo.rr.com>
 */

#समावेश <linux/pnp.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/dma-mapping.h>

#समावेश "base.h"

अटल LIST_HEAD(pnp_protocols);
LIST_HEAD(pnp_global);
DEFINE_MUTEX(pnp_lock);

/*
 * ACPI or PNPBIOS should tell us about all platक्रमm devices, so we can
 * skip some blind probes.  ISAPNP typically क्रमागतerates only plug-in ISA
 * devices, not built-in things like COM ports.
 */
पूर्णांक pnp_platक्रमm_devices;
EXPORT_SYMBOL(pnp_platक्रमm_devices);

व्योम *pnp_alloc(दीर्घ size)
अणु
	व्योम *result;

	result = kzalloc(size, GFP_KERNEL);
	अगर (!result) अणु
		prपूर्णांकk(KERN_ERR "pnp: Out of Memory\n");
		वापस शून्य;
	पूर्ण
	वापस result;
पूर्ण

अटल व्योम pnp_हटाओ_protocol(काष्ठा pnp_protocol *protocol)
अणु
	mutex_lock(&pnp_lock);
	list_del(&protocol->protocol_list);
	mutex_unlock(&pnp_lock);
पूर्ण

/**
 * pnp_रेजिस्टर_protocol - adds a pnp protocol to the pnp layer
 * @protocol: poपूर्णांकer to the corresponding pnp_protocol काष्ठाure
 *
 *  Ex protocols: ISAPNP, PNPBIOS, etc
 */
पूर्णांक pnp_रेजिस्टर_protocol(काष्ठा pnp_protocol *protocol)
अणु
	काष्ठा list_head *pos;
	पूर्णांक nodक्रमागत, ret;

	INIT_LIST_HEAD(&protocol->devices);
	INIT_LIST_HEAD(&protocol->cards);
	nodक्रमागत = 0;

	mutex_lock(&pnp_lock);

	/* assign the lowest unused number */
	list_क्रम_each(pos, &pnp_protocols) अणु
		काष्ठा pnp_protocol *cur = to_pnp_protocol(pos);
		अगर (cur->number == nodक्रमागत) अणु
			pos = &pnp_protocols;
			nodक्रमागत++;
		पूर्ण
	पूर्ण

	protocol->number = nodक्रमागत;
	dev_set_name(&protocol->dev, "pnp%d", nodक्रमागत);

	list_add_tail(&protocol->protocol_list, &pnp_protocols);

	mutex_unlock(&pnp_lock);

	ret = device_रेजिस्टर(&protocol->dev);
	अगर (ret)
		pnp_हटाओ_protocol(protocol);

	वापस ret;
पूर्ण

/**
 * pnp_unरेजिस्टर_protocol - हटाओs a pnp protocol from the pnp layer
 * @protocol: poपूर्णांकer to the corresponding pnp_protocol काष्ठाure
 */
व्योम pnp_unरेजिस्टर_protocol(काष्ठा pnp_protocol *protocol)
अणु
	pnp_हटाओ_protocol(protocol);
	device_unरेजिस्टर(&protocol->dev);
पूर्ण

अटल व्योम pnp_मुक्त_ids(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_id *id;
	काष्ठा pnp_id *next;

	id = dev->id;
	जबतक (id) अणु
		next = id->next;
		kमुक्त(id);
		id = next;
	पूर्ण
पूर्ण

व्योम pnp_मुक्त_resource(काष्ठा pnp_resource *pnp_res)
अणु
	list_del(&pnp_res->list);
	kमुक्त(pnp_res);
पूर्ण

व्योम pnp_मुक्त_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_resource *pnp_res, *पंचांगp;

	list_क्रम_each_entry_safe(pnp_res, पंचांगp, &dev->resources, list) अणु
		pnp_मुक्त_resource(pnp_res);
	पूर्ण
पूर्ण

अटल व्योम pnp_release_device(काष्ठा device *dmdev)
अणु
	काष्ठा pnp_dev *dev = to_pnp_dev(dmdev);

	pnp_मुक्त_ids(dev);
	pnp_मुक्त_resources(dev);
	pnp_मुक्त_options(dev);
	kमुक्त(dev);
पूर्ण

काष्ठा pnp_dev *pnp_alloc_dev(काष्ठा pnp_protocol *protocol, पूर्णांक id,
			      स्थिर अक्षर *pnpid)
अणु
	काष्ठा pnp_dev *dev;
	काष्ठा pnp_id *dev_id;

	dev = kzalloc(माप(काष्ठा pnp_dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	INIT_LIST_HEAD(&dev->resources);
	INIT_LIST_HEAD(&dev->options);
	dev->protocol = protocol;
	dev->number = id;
	dev->dma_mask = DMA_BIT_MASK(24);

	dev->dev.parent = &dev->protocol->dev;
	dev->dev.bus = &pnp_bus_type;
	dev->dev.dma_mask = &dev->dma_mask;
	dev->dev.coherent_dma_mask = dev->dma_mask;
	dev->dev.release = &pnp_release_device;

	dev_set_name(&dev->dev, "%02x:%02x", dev->protocol->number, dev->number);

	dev_id = pnp_add_id(dev, pnpid);
	अगर (!dev_id) अणु
		kमुक्त(dev);
		वापस शून्य;
	पूर्ण

	वापस dev;
पूर्ण

अटल व्योम pnp_delist_device(काष्ठा pnp_dev *dev)
अणु
	mutex_lock(&pnp_lock);
	list_del(&dev->global_list);
	list_del(&dev->protocol_list);
	mutex_unlock(&pnp_lock);
पूर्ण

पूर्णांक __pnp_add_device(काष्ठा pnp_dev *dev)
अणु
	पूर्णांक ret;

	pnp_fixup_device(dev);
	dev->status = PNP_READY;

	mutex_lock(&pnp_lock);

	list_add_tail(&dev->global_list, &pnp_global);
	list_add_tail(&dev->protocol_list, &dev->protocol->devices);

	mutex_unlock(&pnp_lock);

	ret = device_रेजिस्टर(&dev->dev);
	अगर (ret)
		pnp_delist_device(dev);
	अन्यथा अगर (dev->protocol->can_wakeup)
		device_set_wakeup_capable(&dev->dev,
				dev->protocol->can_wakeup(dev));

	वापस ret;
पूर्ण

/*
 * pnp_add_device - adds a pnp device to the pnp layer
 * @dev: poपूर्णांकer to dev to add
 *
 *  adds to driver model, name database, fixups, पूर्णांकerface, etc.
 */
पूर्णांक pnp_add_device(काष्ठा pnp_dev *dev)
अणु
	पूर्णांक ret;
	अक्षर buf[128];
	पूर्णांक len = 0;
	काष्ठा pnp_id *id;

	अगर (dev->card)
		वापस -EINVAL;

	ret = __pnp_add_device(dev);
	अगर (ret)
		वापस ret;

	buf[0] = '\0';
	क्रम (id = dev->id; id; id = id->next)
		len += scnम_लिखो(buf + len, माप(buf) - len, " %s", id->id);

	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "%s device, IDs%s (%s)\n",
		   dev->protocol->name, buf,
		   dev->active ? "active" : "disabled");
	वापस 0;
पूर्ण

व्योम __pnp_हटाओ_device(काष्ठा pnp_dev *dev)
अणु
	pnp_delist_device(dev);
	device_unरेजिस्टर(&dev->dev);
पूर्ण

अटल पूर्णांक __init pnp_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&pnp_bus_type);
पूर्ण

subsys_initcall(pnp_init);

पूर्णांक pnp_debug;

#अगर defined(CONFIG_PNP_DEBUG_MESSAGES)
module_param_named(debug, pnp_debug, पूर्णांक, 0644);
#पूर्ण_अगर
