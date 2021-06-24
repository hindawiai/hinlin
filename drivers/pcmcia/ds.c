<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ds.c -- 16-bit PCMCIA core support
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999		David A. Hinds
 * (C) 2003 - 2010	Dominik Broकरोwski
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/crc32.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kref.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/ss.h>

#समावेश "cs_internal.h"

/*====================================================================*/

/* Module parameters */

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("PCMCIA Driver Services");
MODULE_LICENSE("GPL");


/*====================================================================*/

अटल व्योम pcmcia_check_driver(काष्ठा pcmcia_driver *p_drv)
अणु
	स्थिर काष्ठा pcmcia_device_id *did = p_drv->id_table;
	अचिन्हित पूर्णांक i;
	u32 hash;

	अगर (!p_drv->probe || !p_drv->हटाओ)
		prपूर्णांकk(KERN_DEBUG "pcmcia: %s lacks a requisite callback "
		       "function\n", p_drv->name);

	जबतक (did && did->match_flags) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर (!did->prod_id[i])
				जारी;

			hash = crc32(0, did->prod_id[i], म_माप(did->prod_id[i]));
			अगर (hash == did->prod_id_hash[i])
				जारी;

			prपूर्णांकk(KERN_DEBUG "pcmcia: %s: invalid hash for "
			       "product string \"%s\": is 0x%x, should "
			       "be 0x%x\n", p_drv->name, did->prod_id[i],
			       did->prod_id_hash[i], hash);
			prपूर्णांकk(KERN_DEBUG "pcmcia: see "
				"Documentation/pcmcia/devicetable.rst for "
				"details\n");
		पूर्ण
		did++;
	पूर्ण

	वापस;
पूर्ण


/*======================================================================*/


काष्ठा pcmcia_dynid अणु
	काष्ठा list_head		node;
	काष्ठा pcmcia_device_id		id;
पूर्ण;

/**
 * new_id_store() - add a new PCMCIA device ID to this driver and re-probe devices
 * @driver: target device driver
 * @buf: buffer क्रम scanning device ID data
 * @count: input size
 *
 * Adds a new dynamic PCMCIA device ID to this driver,
 * and causes the driver to probe क्रम all devices again.
 */
अटल sमाप_प्रकार
new_id_store(काष्ठा device_driver *driver, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_dynid *dynid;
	काष्ठा pcmcia_driver *pdrv = to_pcmcia_drv(driver);
	__u16 match_flags, manf_id, card_id;
	__u8 func_id, function, device_no;
	__u32 prod_id_hash[4] = अणु0, 0, 0, 0पूर्ण;
	पूर्णांक fields = 0;
	पूर्णांक retval = 0;

	fields = माला_पूछो(buf, "%hx %hx %hx %hhx %hhx %hhx %x %x %x %x",
			&match_flags, &manf_id, &card_id, &func_id, &function, &device_no,
			&prod_id_hash[0], &prod_id_hash[1], &prod_id_hash[2], &prod_id_hash[3]);
	अगर (fields < 6)
		वापस -EINVAL;

	dynid = kzalloc(माप(काष्ठा pcmcia_dynid), GFP_KERNEL);
	अगर (!dynid)
		वापस -ENOMEM;

	dynid->id.match_flags = match_flags;
	dynid->id.manf_id = manf_id;
	dynid->id.card_id = card_id;
	dynid->id.func_id = func_id;
	dynid->id.function = function;
	dynid->id.device_no = device_no;
	स_नकल(dynid->id.prod_id_hash, prod_id_hash, माप(__u32) * 4);

	mutex_lock(&pdrv->dynids.lock);
	list_add_tail(&dynid->node, &pdrv->dynids.list);
	mutex_unlock(&pdrv->dynids.lock);

	retval = driver_attach(&pdrv->drv);

	अगर (retval)
		वापस retval;
	वापस count;
पूर्ण
अटल DRIVER_ATTR_WO(new_id);

अटल व्योम
pcmcia_मुक्त_dynids(काष्ठा pcmcia_driver *drv)
अणु
	काष्ठा pcmcia_dynid *dynid, *n;

	mutex_lock(&drv->dynids.lock);
	list_क्रम_each_entry_safe(dynid, n, &drv->dynids.list, node) अणु
		list_del(&dynid->node);
		kमुक्त(dynid);
	पूर्ण
	mutex_unlock(&drv->dynids.lock);
पूर्ण

अटल पूर्णांक
pcmcia_create_newid_file(काष्ठा pcmcia_driver *drv)
अणु
	पूर्णांक error = 0;
	अगर (drv->probe != शून्य)
		error = driver_create_file(&drv->drv, &driver_attr_new_id);
	वापस error;
पूर्ण

अटल व्योम
pcmcia_हटाओ_newid_file(काष्ठा pcmcia_driver *drv)
अणु
	driver_हटाओ_file(&drv->drv, &driver_attr_new_id);
पूर्ण

/**
 * pcmcia_रेजिस्टर_driver - रेजिस्टर a PCMCIA driver with the bus core
 * @driver: the &driver being रेजिस्टरed
 *
 * Registers a PCMCIA driver with the PCMCIA bus core.
 */
पूर्णांक pcmcia_रेजिस्टर_driver(काष्ठा pcmcia_driver *driver)
अणु
	पूर्णांक error;

	अगर (!driver)
		वापस -EINVAL;

	pcmcia_check_driver(driver);

	/* initialize common fields */
	driver->drv.bus = &pcmcia_bus_type;
	driver->drv.owner = driver->owner;
	driver->drv.name = driver->name;
	mutex_init(&driver->dynids.lock);
	INIT_LIST_HEAD(&driver->dynids.list);

	pr_debug("registering driver %s\n", driver->name);

	error = driver_रेजिस्टर(&driver->drv);
	अगर (error < 0)
		वापस error;

	error = pcmcia_create_newid_file(driver);
	अगर (error)
		driver_unरेजिस्टर(&driver->drv);

	वापस error;
पूर्ण
EXPORT_SYMBOL(pcmcia_रेजिस्टर_driver);

/**
 * pcmcia_unरेजिस्टर_driver - unरेजिस्टर a PCMCIA driver with the bus core
 * @driver: the &driver being unरेजिस्टरed
 */
व्योम pcmcia_unरेजिस्टर_driver(काष्ठा pcmcia_driver *driver)
अणु
	pr_debug("unregistering driver %s\n", driver->name);
	pcmcia_हटाओ_newid_file(driver);
	driver_unरेजिस्टर(&driver->drv);
	pcmcia_मुक्त_dynids(driver);
पूर्ण
EXPORT_SYMBOL(pcmcia_unरेजिस्टर_driver);


/* pcmcia_device handling */

अटल काष्ठा pcmcia_device *pcmcia_get_dev(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा device *पंचांगp_dev;
	पंचांगp_dev = get_device(&p_dev->dev);
	अगर (!पंचांगp_dev)
		वापस शून्य;
	वापस to_pcmcia_dev(पंचांगp_dev);
पूर्ण

अटल व्योम pcmcia_put_dev(काष्ठा pcmcia_device *p_dev)
अणु
	अगर (p_dev)
		put_device(&p_dev->dev);
पूर्ण

अटल व्योम pcmcia_release_function(काष्ठा kref *ref)
अणु
	काष्ठा config_t *c = container_of(ref, काष्ठा config_t, ref);
	pr_debug("releasing config_t\n");
	kमुक्त(c);
पूर्ण

अटल व्योम pcmcia_release_dev(काष्ठा device *dev)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);
	पूर्णांक i;
	dev_dbg(dev, "releasing device\n");
	pcmcia_put_socket(p_dev->socket);
	क्रम (i = 0; i < 4; i++)
		kमुक्त(p_dev->prod_id[i]);
	kमुक्त(p_dev->devname);
	kref_put(&p_dev->function_config->ref, pcmcia_release_function);
	kमुक्त(p_dev);
पूर्ण


अटल पूर्णांक pcmcia_device_probe(काष्ठा device *dev)
अणु
	काष्ठा pcmcia_device *p_dev;
	काष्ठा pcmcia_driver *p_drv;
	काष्ठा pcmcia_socket *s;
	cistpl_config_t cis_config;
	पूर्णांक ret = 0;

	dev = get_device(dev);
	अगर (!dev)
		वापस -ENODEV;

	p_dev = to_pcmcia_dev(dev);
	p_drv = to_pcmcia_drv(dev->driver);
	s = p_dev->socket;

	dev_dbg(dev, "trying to bind to %s\n", p_drv->name);

	अगर ((!p_drv->probe) || (!p_dev->function_config) ||
	    (!try_module_get(p_drv->owner))) अणु
		ret = -EINVAL;
		जाओ put_dev;
	पूर्ण

	/* set up some more device inक्रमmation */
	ret = pccard_पढ़ो_tuple(p_dev->socket, p_dev->func, CISTPL_CONFIG,
				&cis_config);
	अगर (!ret) अणु
		p_dev->config_base = cis_config.base;
		p_dev->config_regs = cis_config.rmask[0];
		dev_dbg(dev, "base %x, regs %x", p_dev->config_base,
			p_dev->config_regs);
	पूर्ण अन्यथा अणु
		dev_info(dev,
			 "pcmcia: could not parse base and rmask0 of CIS\n");
		p_dev->config_base = 0;
		p_dev->config_regs = 0;
	पूर्ण

	ret = p_drv->probe(p_dev);
	अगर (ret) अणु
		dev_dbg(dev, "binding to %s failed with %d\n",
			   p_drv->name, ret);
		जाओ put_module;
	पूर्ण
	dev_dbg(dev, "%s bound: Vpp %d.%d, idx %x, IRQ %d", p_drv->name,
		p_dev->vpp/10, p_dev->vpp%10, p_dev->config_index, p_dev->irq);
	dev_dbg(dev, "resources: ioport %pR %pR iomem %pR %pR %pR",
		p_dev->resource[0], p_dev->resource[1], p_dev->resource[2],
		p_dev->resource[3], p_dev->resource[4]);

	mutex_lock(&s->ops_mutex);
	अगर ((s->pcmcia_pfc) &&
	    (p_dev->socket->device_count == 1) && (p_dev->device_no == 0))
		pcmcia_parse_uevents(s, PCMCIA_UEVENT_REQUERY);
	mutex_unlock(&s->ops_mutex);

put_module:
	अगर (ret)
		module_put(p_drv->owner);
put_dev:
	अगर (ret)
		put_device(dev);
	वापस ret;
पूर्ण


/*
 * Removes a PCMCIA card from the device tree and socket list.
 */
अटल व्योम pcmcia_card_हटाओ(काष्ठा pcmcia_socket *s, काष्ठा pcmcia_device *leftover)
अणु
	काष्ठा pcmcia_device	*p_dev;
	काष्ठा pcmcia_device	*पंचांगp;

	dev_dbg(leftover ? &leftover->dev : &s->dev,
		   "pcmcia_card_remove(%d) %s\n", s->sock,
		   leftover ? leftover->devname : "");

	mutex_lock(&s->ops_mutex);
	अगर (!leftover)
		s->device_count = 0;
	अन्यथा
		s->device_count = 1;
	mutex_unlock(&s->ops_mutex);

	/* unरेजिस्टर all pcmcia_devices रेजिस्टरed with this socket, except leftover */
	list_क्रम_each_entry_safe(p_dev, पंचांगp, &s->devices_list, socket_device_list) अणु
		अगर (p_dev == leftover)
			जारी;

		mutex_lock(&s->ops_mutex);
		list_del(&p_dev->socket_device_list);
		mutex_unlock(&s->ops_mutex);

		dev_dbg(&p_dev->dev, "unregistering device\n");
		device_unरेजिस्टर(&p_dev->dev);
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक pcmcia_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा pcmcia_device *p_dev;
	काष्ठा pcmcia_driver *p_drv;
	पूर्णांक i;

	p_dev = to_pcmcia_dev(dev);
	p_drv = to_pcmcia_drv(dev->driver);

	dev_dbg(dev, "removing device\n");

	/* If we're removing the primary module driving a
	 * pseuकरो multi-function card, we need to unbind
	 * all devices
	 */
	अगर ((p_dev->socket->pcmcia_pfc) &&
	    (p_dev->socket->device_count > 0) &&
	    (p_dev->device_no == 0))
		pcmcia_card_हटाओ(p_dev->socket, p_dev);

	/* detach the "instance" */
	अगर (p_drv->हटाओ)
		p_drv->हटाओ(p_dev);

	/* check क्रम proper unloading */
	अगर (p_dev->_irq || p_dev->_io || p_dev->_locked)
		dev_info(dev,
			 "pcmcia: driver %s did not release config properly\n",
			 p_drv->name);

	क्रम (i = 0; i < MAX_WIN; i++)
		अगर (p_dev->_win & CLIENT_WIN_REQ(i))
			dev_info(dev,
				 "pcmcia: driver %s did not release window properly\n",
				 p_drv->name);

	/* references from pcmcia_device_probe */
	pcmcia_put_dev(p_dev);
	module_put(p_drv->owner);

	वापस 0;
पूर्ण


/*
 * pcmcia_device_query -- determine inक्रमmation about a pcmcia device
 */
अटल पूर्णांक pcmcia_device_query(काष्ठा pcmcia_device *p_dev)
अणु
	cistpl_manfid_t manf_id;
	cistpl_funcid_t func_id;
	cistpl_vers_1_t	*vers1;
	अचिन्हित पूर्णांक i;

	vers1 = kदो_स्मृति(माप(*vers1), GFP_KERNEL);
	अगर (!vers1)
		वापस -ENOMEM;

	अगर (!pccard_पढ़ो_tuple(p_dev->socket, BIND_FN_ALL,
			       CISTPL_MANFID, &manf_id)) अणु
		mutex_lock(&p_dev->socket->ops_mutex);
		p_dev->manf_id = manf_id.manf;
		p_dev->card_id = manf_id.card;
		p_dev->has_manf_id = 1;
		p_dev->has_card_id = 1;
		mutex_unlock(&p_dev->socket->ops_mutex);
	पूर्ण

	अगर (!pccard_पढ़ो_tuple(p_dev->socket, p_dev->func,
			       CISTPL_FUNCID, &func_id)) अणु
		mutex_lock(&p_dev->socket->ops_mutex);
		p_dev->func_id = func_id.func;
		p_dev->has_func_id = 1;
		mutex_unlock(&p_dev->socket->ops_mutex);
	पूर्ण अन्यथा अणु
		/* rule of thumb: cards with no FUNCID, but with
		 * common memory device geometry inक्रमmation, are
		 * probably memory cards (from pcmcia-cs) */
		cistpl_device_geo_t *devgeo;

		devgeo = kदो_स्मृति(माप(*devgeo), GFP_KERNEL);
		अगर (!devgeo) अणु
			kमुक्त(vers1);
			वापस -ENOMEM;
		पूर्ण
		अगर (!pccard_पढ़ो_tuple(p_dev->socket, p_dev->func,
				      CISTPL_DEVICE_GEO, devgeo)) अणु
			dev_dbg(&p_dev->dev,
				   "mem device geometry probably means "
				   "FUNCID_MEMORY\n");
			mutex_lock(&p_dev->socket->ops_mutex);
			p_dev->func_id = CISTPL_FUNCID_MEMORY;
			p_dev->has_func_id = 1;
			mutex_unlock(&p_dev->socket->ops_mutex);
		पूर्ण
		kमुक्त(devgeo);
	पूर्ण

	अगर (!pccard_पढ़ो_tuple(p_dev->socket, BIND_FN_ALL, CISTPL_VERS_1,
			       vers1)) अणु
		mutex_lock(&p_dev->socket->ops_mutex);
		क्रम (i = 0; i < min_t(अचिन्हित पूर्णांक, 4, vers1->ns); i++) अणु
			अक्षर *पंचांगp;
			अचिन्हित पूर्णांक length;
			अक्षर *new;

			पंचांगp = vers1->str + vers1->ofs[i];

			length = म_माप(पंचांगp) + 1;
			अगर ((length < 2) || (length > 255))
				जारी;

			new = kstrdup(पंचांगp, GFP_KERNEL);
			अगर (!new)
				जारी;

			पंचांगp = p_dev->prod_id[i];
			p_dev->prod_id[i] = new;
			kमुक्त(पंचांगp);
		पूर्ण
		mutex_unlock(&p_dev->socket->ops_mutex);
	पूर्ण

	kमुक्त(vers1);
	वापस 0;
पूर्ण


अटल काष्ठा pcmcia_device *pcmcia_device_add(काष्ठा pcmcia_socket *s,
					       अचिन्हित पूर्णांक function)
अणु
	काष्ठा pcmcia_device *p_dev, *पंचांगp_dev;
	पूर्णांक i;

	s = pcmcia_get_socket(s);
	अगर (!s)
		वापस शून्य;

	pr_debug("adding device to %d, function %d\n", s->sock, function);

	p_dev = kzalloc(माप(काष्ठा pcmcia_device), GFP_KERNEL);
	अगर (!p_dev)
		जाओ err_put;

	mutex_lock(&s->ops_mutex);
	p_dev->device_no = (s->device_count++);
	mutex_unlock(&s->ops_mutex);

	/* max of 2 PFC devices */
	अगर ((p_dev->device_no >= 2) && (function == 0))
		जाओ err_मुक्त;

	/* max of 4 devices overall */
	अगर (p_dev->device_no >= 4)
		जाओ err_मुक्त;

	p_dev->socket = s;
	p_dev->func   = function;

	p_dev->dev.bus = &pcmcia_bus_type;
	p_dev->dev.parent = s->dev.parent;
	p_dev->dev.release = pcmcia_release_dev;
	/* by शेष करोn't allow DMA */
	p_dev->dma_mask = 0;
	p_dev->dev.dma_mask = &p_dev->dma_mask;
	dev_set_name(&p_dev->dev, "%d.%d", p_dev->socket->sock, p_dev->device_no);
	अगर (!dev_name(&p_dev->dev))
		जाओ err_मुक्त;
	p_dev->devname = kaप्र_लिखो(GFP_KERNEL, "pcmcia%s", dev_name(&p_dev->dev));
	अगर (!p_dev->devname)
		जाओ err_मुक्त;
	dev_dbg(&p_dev->dev, "devname is %s\n", p_dev->devname);

	mutex_lock(&s->ops_mutex);

	/*
	 * p_dev->function_config must be the same क्रम all card functions.
	 * Note that this is serialized by ops_mutex, so that only one
	 * such काष्ठा will be created.
	 */
	list_क्रम_each_entry(पंचांगp_dev, &s->devices_list, socket_device_list)
		अगर (p_dev->func == पंचांगp_dev->func) अणु
			p_dev->function_config = पंचांगp_dev->function_config;
			p_dev->irq = पंचांगp_dev->irq;
			kref_get(&p_dev->function_config->ref);
		पूर्ण

	/* Add to the list in pcmcia_bus_socket */
	list_add(&p_dev->socket_device_list, &s->devices_list);

	अगर (pcmcia_setup_irq(p_dev))
		dev_warn(&p_dev->dev,
			"IRQ setup failed -- device might not work\n");

	अगर (!p_dev->function_config) अणु
		config_t *c;
		dev_dbg(&p_dev->dev, "creating config_t\n");
		c = kzalloc(माप(काष्ठा config_t), GFP_KERNEL);
		अगर (!c) अणु
			mutex_unlock(&s->ops_mutex);
			जाओ err_unreg;
		पूर्ण
		p_dev->function_config = c;
		kref_init(&c->ref);
		क्रम (i = 0; i < MAX_IO_WIN; i++) अणु
			c->io[i].name = p_dev->devname;
			c->io[i].flags = IORESOURCE_IO;
		पूर्ण
		क्रम (i = 0; i < MAX_WIN; i++) अणु
			c->mem[i].name = p_dev->devname;
			c->mem[i].flags = IORESOURCE_MEM;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < MAX_IO_WIN; i++)
		p_dev->resource[i] = &p_dev->function_config->io[i];
	क्रम (; i < (MAX_IO_WIN + MAX_WIN); i++)
		p_dev->resource[i] = &p_dev->function_config->mem[i-MAX_IO_WIN];

	mutex_unlock(&s->ops_mutex);

	dev_notice(&p_dev->dev, "pcmcia: registering new device %s (IRQ: %d)\n",
		   p_dev->devname, p_dev->irq);

	pcmcia_device_query(p_dev);

	अगर (device_रेजिस्टर(&p_dev->dev))
		जाओ err_unreg;

	वापस p_dev;

 err_unreg:
	mutex_lock(&s->ops_mutex);
	list_del(&p_dev->socket_device_list);
	mutex_unlock(&s->ops_mutex);

 err_मुक्त:
	mutex_lock(&s->ops_mutex);
	s->device_count--;
	mutex_unlock(&s->ops_mutex);

	क्रम (i = 0; i < 4; i++)
		kमुक्त(p_dev->prod_id[i]);
	kमुक्त(p_dev->devname);
	kमुक्त(p_dev);
 err_put:
	pcmcia_put_socket(s);

	वापस शून्य;
पूर्ण


अटल पूर्णांक pcmcia_card_add(काष्ठा pcmcia_socket *s)
अणु
	cistpl_दीर्घlink_mfc_t mfc;
	अचिन्हित पूर्णांक no_funcs, i, no_chains;
	पूर्णांक ret = -EAGAIN;

	mutex_lock(&s->ops_mutex);
	अगर (!(s->resource_setup_करोne)) अणु
		dev_dbg(&s->dev,
			   "no resources available, delaying card_add\n");
		mutex_unlock(&s->ops_mutex);
		वापस -EAGAIN; /* try again, but later... */
	पूर्ण

	अगर (pcmcia_validate_mem(s)) अणु
		dev_dbg(&s->dev, "validating mem resources failed, "
		       "delaying card_add\n");
		mutex_unlock(&s->ops_mutex);
		वापस -EAGAIN; /* try again, but later... */
	पूर्ण
	mutex_unlock(&s->ops_mutex);

	ret = pccard_validate_cis(s, &no_chains);
	अगर (ret || !no_chains) अणु
#अगर defined(CONFIG_MTD_PCMCIA_ANONYMOUS)
		/* Set up as an anonymous card. If we करोn't have anonymous
		   memory support then just error the card as there is no
		   poपूर्णांक trying to second guess.

		   Note: some cards have just a device entry, it may be
		   worth extending support to cover these in future */
		अगर (ret == -EIO) अणु
			dev_info(&s->dev, "no CIS, assuming an anonymous memory card.\n");
			pcmcia_replace_cis(s, "\xFF", 1);
			no_chains = 1;
			ret = 0;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			dev_dbg(&s->dev, "invalid CIS or invalid resources\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (!pccard_पढ़ो_tuple(s, BIND_FN_ALL, CISTPL_LONGLINK_MFC, &mfc))
		no_funcs = mfc.nfn;
	अन्यथा
		no_funcs = 1;
	s->functions = no_funcs;

	क्रम (i = 0; i < no_funcs; i++)
		pcmcia_device_add(s, i);

	वापस ret;
पूर्ण


अटल पूर्णांक pcmcia_requery_callback(काष्ठा device *dev, व्योम *_data)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);
	अगर (!p_dev->dev.driver) अणु
		dev_dbg(dev, "update device information\n");
		pcmcia_device_query(p_dev);
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम pcmcia_requery(काष्ठा pcmcia_socket *s)
अणु
	पूर्णांक has_pfc;

	अगर (!(s->state & SOCKET_PRESENT))
		वापस;

	अगर (s->functions == 0) अणु
		pcmcia_card_add(s);
		वापस;
	पूर्ण

	/* some device inक्रमmation might have changed because of a CIS
	 * update or because we can finally पढ़ो it correctly... so
	 * determine it again, overwriting old values अगर necessary. */
	bus_क्रम_each_dev(&pcmcia_bus_type, शून्य, शून्य, pcmcia_requery_callback);

	/* अगर the CIS changed, we need to check whether the number of
	 * functions changed. */
	अगर (s->fake_cis) अणु
		पूर्णांक old_funcs, new_funcs;
		cistpl_दीर्घlink_mfc_t mfc;

		/* करोes this cis override add or हटाओ functions? */
		old_funcs = s->functions;

		अगर (!pccard_पढ़ो_tuple(s, BIND_FN_ALL, CISTPL_LONGLINK_MFC,
					&mfc))
			new_funcs = mfc.nfn;
		अन्यथा
			new_funcs = 1;
		अगर (old_funcs != new_funcs) अणु
			/* we need to re-start */
			pcmcia_card_हटाओ(s, शून्य);
			s->functions = 0;
			pcmcia_card_add(s);
		पूर्ण
	पूर्ण

	/* If the PCMCIA device consists of two pseuकरो devices,
	 * call pcmcia_device_add() -- which will fail अगर both
	 * devices are alपढ़ोy रेजिस्टरed. */
	mutex_lock(&s->ops_mutex);
	has_pfc = s->pcmcia_pfc;
	mutex_unlock(&s->ops_mutex);
	अगर (has_pfc)
		pcmcia_device_add(s, 0);

	/* we re-scan all devices, not just the ones connected to this
	 * socket. This करोes not matter, though. */
	अगर (bus_rescan_devices(&pcmcia_bus_type))
		dev_warn(&s->dev, "rescanning the bus failed\n");
पूर्ण


#अगर_घोषित CONFIG_PCMCIA_LOAD_CIS

/**
 * pcmcia_load_firmware - load CIS from userspace अगर device-provided is broken
 * @dev: the pcmcia device which needs a CIS override
 * @filename: requested filename in /lib/firmware/
 *
 * This uses the in-kernel firmware loading mechanism to use a "fake CIS" अगर
 * the one provided by the card is broken. The firmware files reside in
 * /lib/firmware/ in userspace.
 */
अटल पूर्णांक pcmcia_load_firmware(काष्ठा pcmcia_device *dev, अक्षर *filename)
अणु
	काष्ठा pcmcia_socket *s = dev->socket;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret = -ENOMEM;
	cistpl_दीर्घlink_mfc_t mfc;
	पूर्णांक old_funcs, new_funcs = 1;

	अगर (!filename)
		वापस -EINVAL;

	dev_dbg(&dev->dev, "trying to load CIS file %s\n", filename);

	अगर (request_firmware(&fw, filename, &dev->dev) == 0) अणु
		अगर (fw->size >= CISTPL_MAX_CIS_SIZE) अणु
			ret = -EINVAL;
			dev_err(&dev->dev, "pcmcia: CIS override is too big\n");
			जाओ release;
		पूर्ण

		अगर (!pcmcia_replace_cis(s, fw->data, fw->size))
			ret = 0;
		अन्यथा अणु
			dev_err(&dev->dev, "pcmcia: CIS override failed\n");
			जाओ release;
		पूर्ण

		/* we need to re-start अगर the number of functions changed */
		old_funcs = s->functions;
		अगर (!pccard_पढ़ो_tuple(s, BIND_FN_ALL, CISTPL_LONGLINK_MFC,
					&mfc))
			new_funcs = mfc.nfn;

		अगर (old_funcs != new_funcs)
			ret = -EBUSY;

		/* update inक्रमmation */
		pcmcia_device_query(dev);

		/* requery (as number of functions might have changed) */
		pcmcia_parse_uevents(s, PCMCIA_UEVENT_REQUERY);
	पूर्ण
 release:
	release_firmware(fw);

	वापस ret;
पूर्ण

#अन्यथा /* !CONFIG_PCMCIA_LOAD_CIS */

अटल अंतरभूत पूर्णांक pcmcia_load_firmware(काष्ठा pcmcia_device *dev,
				       अक्षर *filename)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर


अटल अंतरभूत पूर्णांक pcmcia_devmatch(काष्ठा pcmcia_device *dev,
				  स्थिर काष्ठा pcmcia_device_id *did)
अणु
	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_MANF_ID) अणु
		अगर ((!dev->has_manf_id) || (dev->manf_id != did->manf_id))
			वापस 0;
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_CARD_ID) अणु
		अगर ((!dev->has_card_id) || (dev->card_id != did->card_id))
			वापस 0;
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_FUNCTION) अणु
		अगर (dev->func != did->function)
			वापस 0;
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID1) अणु
		अगर (!dev->prod_id[0])
			वापस 0;
		अगर (म_भेद(did->prod_id[0], dev->prod_id[0]))
			वापस 0;
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID2) अणु
		अगर (!dev->prod_id[1])
			वापस 0;
		अगर (म_भेद(did->prod_id[1], dev->prod_id[1]))
			वापस 0;
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID3) अणु
		अगर (!dev->prod_id[2])
			वापस 0;
		अगर (म_भेद(did->prod_id[2], dev->prod_id[2]))
			वापस 0;
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID4) अणु
		अगर (!dev->prod_id[3])
			वापस 0;
		अगर (म_भेद(did->prod_id[3], dev->prod_id[3]))
			वापस 0;
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_DEVICE_NO) अणु
		dev_dbg(&dev->dev, "this is a pseudo-multi-function device\n");
		mutex_lock(&dev->socket->ops_mutex);
		dev->socket->pcmcia_pfc = 1;
		mutex_unlock(&dev->socket->ops_mutex);
		अगर (dev->device_no != did->device_no)
			वापस 0;
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_FUNC_ID) अणु
		पूर्णांक ret;

		अगर ((!dev->has_func_id) || (dev->func_id != did->func_id))
			वापस 0;

		/* अगर this is a pseuकरो-multi-function device,
		 * we need explicit matches */
		अगर (dev->socket->pcmcia_pfc)
			वापस 0;
		अगर (dev->device_no)
			वापस 0;

		/* also, FUNC_ID matching needs to be activated by userspace
		 * after it has re-checked that there is no possible module
		 * with a prod_id/manf_id/card_id match.
		 */
		mutex_lock(&dev->socket->ops_mutex);
		ret = dev->allow_func_id_match;
		mutex_unlock(&dev->socket->ops_mutex);

		अगर (!ret) अणु
			dev_dbg(&dev->dev,
				"skipping FUNC_ID match until userspace ACK\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_FAKE_CIS) अणु
		dev_dbg(&dev->dev, "device needs a fake CIS\n");
		अगर (!dev->socket->fake_cis)
			अगर (pcmcia_load_firmware(dev, did->cisfile))
				वापस 0;
	पूर्ण

	अगर (did->match_flags & PCMCIA_DEV_ID_MATCH_ANONYMOUS) अणु
		पूर्णांक i;
		क्रम (i = 0; i < 4; i++)
			अगर (dev->prod_id[i])
				वापस 0;
		अगर (dev->has_manf_id || dev->has_card_id || dev->has_func_id)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण


अटल पूर्णांक pcmcia_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);
	काष्ठा pcmcia_driver *p_drv = to_pcmcia_drv(drv);
	स्थिर काष्ठा pcmcia_device_id *did = p_drv->id_table;
	काष्ठा pcmcia_dynid *dynid;

	/* match dynamic devices first */
	mutex_lock(&p_drv->dynids.lock);
	list_क्रम_each_entry(dynid, &p_drv->dynids.list, node) अणु
		dev_dbg(dev, "trying to match to %s\n", drv->name);
		अगर (pcmcia_devmatch(p_dev, &dynid->id)) अणु
			dev_dbg(dev, "matched to %s\n", drv->name);
			mutex_unlock(&p_drv->dynids.lock);
			वापस 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&p_drv->dynids.lock);

	जबतक (did && did->match_flags) अणु
		dev_dbg(dev, "trying to match to %s\n", drv->name);
		अगर (pcmcia_devmatch(p_dev, did)) अणु
			dev_dbg(dev, "matched to %s\n", drv->name);
			वापस 1;
		पूर्ण
		did++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcmcia_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा pcmcia_device *p_dev;
	पूर्णांक i;
	u32 hash[4] = अणु 0, 0, 0, 0पूर्ण;

	अगर (!dev)
		वापस -ENODEV;

	p_dev = to_pcmcia_dev(dev);

	/* calculate hashes */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!p_dev->prod_id[i])
			जारी;
		hash[i] = crc32(0, p_dev->prod_id[i], म_माप(p_dev->prod_id[i]));
	पूर्ण

	अगर (add_uevent_var(env, "SOCKET_NO=%u", p_dev->socket->sock))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "DEVICE_NO=%02X", p_dev->device_no))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "MODALIAS=pcmcia:m%04Xc%04Xf%02Xfn%02Xpfn%02X"
			   "pa%08Xpb%08Xpc%08Xpd%08X",
			   p_dev->has_manf_id ? p_dev->manf_id : 0,
			   p_dev->has_card_id ? p_dev->card_id : 0,
			   p_dev->has_func_id ? p_dev->func_id : 0,
			   p_dev->func,
			   p_dev->device_no,
			   hash[0],
			   hash[1],
			   hash[2],
			   hash[3]))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/************************ runसमय PM support ***************************/

अटल पूर्णांक pcmcia_dev_suspend(काष्ठा device *dev);
अटल पूर्णांक pcmcia_dev_resume(काष्ठा device *dev);

अटल पूर्णांक runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक rc;

	device_lock(dev);
	rc = pcmcia_dev_suspend(dev);
	device_unlock(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक rc;

	device_lock(dev);
	rc = pcmcia_dev_resume(dev);
	device_unlock(dev);
	वापस rc;
पूर्ण

/************************ per-device sysfs output ***************************/

#घोषणा pcmcia_device_attr(field, test, क्रमmat)				\
अटल sमाप_प्रकार field##_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);		\
	वापस p_dev->test ? प्र_लिखो(buf, क्रमmat, p_dev->field) : -ENODEV; \
पूर्ण									\
अटल DEVICE_ATTR_RO(field);

#घोषणा pcmcia_device_stringattr(name, field)					\
अटल sमाप_प्रकार name##_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);		\
	वापस p_dev->field ? प्र_लिखो(buf, "%s\n", p_dev->field) : -ENODEV; \
पूर्ण									\
अटल DEVICE_ATTR_RO(name);

pcmcia_device_attr(func_id, has_func_id, "0x%02x\n");
pcmcia_device_attr(manf_id, has_manf_id, "0x%04x\n");
pcmcia_device_attr(card_id, has_card_id, "0x%04x\n");
pcmcia_device_stringattr(prod_id1, prod_id[0]);
pcmcia_device_stringattr(prod_id2, prod_id[1]);
pcmcia_device_stringattr(prod_id3, prod_id[2]);
pcmcia_device_stringattr(prod_id4, prod_id[3]);

अटल sमाप_प्रकार function_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);
	वापस p_dev->socket ? प्र_लिखो(buf, "0x%02x\n", p_dev->func) : -ENODEV;
पूर्ण
अटल DEVICE_ATTR_RO(function);

अटल sमाप_प्रकार resources_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);
	अक्षर *str = buf;
	पूर्णांक i;

	क्रम (i = 0; i < PCMCIA_NUM_RESOURCES; i++)
		str += प्र_लिखो(str, "%pr\n", p_dev->resource[i]);

	वापस str - buf;
पूर्ण
अटल DEVICE_ATTR_RO(resources);

अटल sमाप_प्रकार pm_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);

	अगर (p_dev->suspended)
		वापस प्र_लिखो(buf, "off\n");
	अन्यथा
		वापस प्र_लिखो(buf, "on\n");
पूर्ण

अटल sमाप_प्रकार pm_state_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);
	पूर्णांक ret = 0;

	अगर (!count)
		वापस -EINVAL;

	अगर ((!p_dev->suspended) && !म_भेदन(buf, "off", 3))
		ret = runसमय_suspend(dev);
	अन्यथा अगर (p_dev->suspended && !म_भेदन(buf, "on", 2))
		ret = runसमय_resume(dev);

	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(pm_state);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);
	पूर्णांक i;
	u32 hash[4] = अणु 0, 0, 0, 0पूर्ण;

	/* calculate hashes */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!p_dev->prod_id[i])
			जारी;
		hash[i] = crc32(0, p_dev->prod_id[i],
				म_माप(p_dev->prod_id[i]));
	पूर्ण
	वापस प्र_लिखो(buf, "pcmcia:m%04Xc%04Xf%02Xfn%02Xpfn%02X"
				"pa%08Xpb%08Xpc%08Xpd%08X\n",
				p_dev->has_manf_id ? p_dev->manf_id : 0,
				p_dev->has_card_id ? p_dev->card_id : 0,
				p_dev->has_func_id ? p_dev->func_id : 0,
				p_dev->func, p_dev->device_no,
				hash[0], hash[1], hash[2], hash[3]);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार allow_func_id_match_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);

	अगर (!count)
		वापस -EINVAL;

	mutex_lock(&p_dev->socket->ops_mutex);
	p_dev->allow_func_id_match = 1;
	mutex_unlock(&p_dev->socket->ops_mutex);
	pcmcia_parse_uevents(p_dev->socket, PCMCIA_UEVENT_REQUERY);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(allow_func_id_match);

अटल काष्ठा attribute *pcmcia_dev_attrs[] = अणु
	&dev_attr_resources.attr,
	&dev_attr_pm_state.attr,
	&dev_attr_function.attr,
	&dev_attr_func_id.attr,
	&dev_attr_manf_id.attr,
	&dev_attr_card_id.attr,
	&dev_attr_prod_id1.attr,
	&dev_attr_prod_id2.attr,
	&dev_attr_prod_id3.attr,
	&dev_attr_prod_id4.attr,
	&dev_attr_modalias.attr,
	&dev_attr_allow_func_id_match.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(pcmcia_dev);

/* PM support, also needed क्रम reset */

अटल पूर्णांक pcmcia_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);
	काष्ठा pcmcia_driver *p_drv = शून्य;
	पूर्णांक ret = 0;

	mutex_lock(&p_dev->socket->ops_mutex);
	अगर (p_dev->suspended) अणु
		mutex_unlock(&p_dev->socket->ops_mutex);
		वापस 0;
	पूर्ण
	p_dev->suspended = 1;
	mutex_unlock(&p_dev->socket->ops_mutex);

	dev_dbg(dev, "suspending\n");

	अगर (dev->driver)
		p_drv = to_pcmcia_drv(dev->driver);

	अगर (!p_drv)
		जाओ out;

	अगर (p_drv->suspend) अणु
		ret = p_drv->suspend(p_dev);
		अगर (ret) अणु
			dev_err(dev,
				"pcmcia: device %s (driver %s) did not want to go to sleep (%d)\n",
				p_dev->devname, p_drv->name, ret);
			mutex_lock(&p_dev->socket->ops_mutex);
			p_dev->suspended = 0;
			mutex_unlock(&p_dev->socket->ops_mutex);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (p_dev->device_no == p_dev->func) अणु
		dev_dbg(dev, "releasing configuration\n");
		pcmcia_release_configuration(p_dev);
	पूर्ण

 out:
	वापस ret;
पूर्ण


अटल पूर्णांक pcmcia_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);
	काष्ठा pcmcia_driver *p_drv = शून्य;
	पूर्णांक ret = 0;

	mutex_lock(&p_dev->socket->ops_mutex);
	अगर (!p_dev->suspended) अणु
		mutex_unlock(&p_dev->socket->ops_mutex);
		वापस 0;
	पूर्ण
	p_dev->suspended = 0;
	mutex_unlock(&p_dev->socket->ops_mutex);

	dev_dbg(dev, "resuming\n");

	अगर (dev->driver)
		p_drv = to_pcmcia_drv(dev->driver);

	अगर (!p_drv)
		जाओ out;

	अगर (p_dev->device_no == p_dev->func) अणु
		dev_dbg(dev, "requesting configuration\n");
		ret = pcmcia_enable_device(p_dev);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (p_drv->resume)
		ret = p_drv->resume(p_dev);

 out:
	वापस ret;
पूर्ण


अटल पूर्णांक pcmcia_bus_suspend_callback(काष्ठा device *dev, व्योम *_data)
अणु
	काष्ठा pcmcia_socket *skt = _data;
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);

	अगर (p_dev->socket != skt || p_dev->suspended)
		वापस 0;

	वापस runसमय_suspend(dev);
पूर्ण

अटल पूर्णांक pcmcia_bus_resume_callback(काष्ठा device *dev, व्योम *_data)
अणु
	काष्ठा pcmcia_socket *skt = _data;
	काष्ठा pcmcia_device *p_dev = to_pcmcia_dev(dev);

	अगर (p_dev->socket != skt || !p_dev->suspended)
		वापस 0;

	runसमय_resume(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pcmcia_bus_resume(काष्ठा pcmcia_socket *skt)
अणु
	dev_dbg(&skt->dev, "resuming socket %d\n", skt->sock);
	bus_क्रम_each_dev(&pcmcia_bus_type, शून्य, skt, pcmcia_bus_resume_callback);
	वापस 0;
पूर्ण

अटल पूर्णांक pcmcia_bus_suspend(काष्ठा pcmcia_socket *skt)
अणु
	dev_dbg(&skt->dev, "suspending socket %d\n", skt->sock);
	अगर (bus_क्रम_each_dev(&pcmcia_bus_type, शून्य, skt,
			     pcmcia_bus_suspend_callback)) अणु
		pcmcia_bus_resume(skt);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcmcia_bus_हटाओ(काष्ठा pcmcia_socket *skt)
अणु
	atomic_set(&skt->present, 0);
	pcmcia_card_हटाओ(skt, शून्य);

	mutex_lock(&skt->ops_mutex);
	destroy_cis_cache(skt);
	pcmcia_cleanup_irq(skt);
	mutex_unlock(&skt->ops_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pcmcia_bus_add(काष्ठा pcmcia_socket *skt)
अणु
	atomic_set(&skt->present, 1);

	mutex_lock(&skt->ops_mutex);
	skt->pcmcia_pfc = 0;
	destroy_cis_cache(skt); /* to be on the safe side... */
	mutex_unlock(&skt->ops_mutex);

	pcmcia_card_add(skt);

	वापस 0;
पूर्ण

अटल पूर्णांक pcmcia_bus_early_resume(काष्ठा pcmcia_socket *skt)
अणु
	अगर (!verअगरy_cis_cache(skt))
		वापस 0;

	dev_dbg(&skt->dev, "cis mismatch - different card\n");

	/* first, हटाओ the card */
	pcmcia_bus_हटाओ(skt);

	mutex_lock(&skt->ops_mutex);
	destroy_cis_cache(skt);
	kमुक्त(skt->fake_cis);
	skt->fake_cis = शून्य;
	skt->functions = 0;
	mutex_unlock(&skt->ops_mutex);

	/* now, add the new card */
	pcmcia_bus_add(skt);
	वापस 0;
पूर्ण


/*
 * NOTE: This is racy. There's no guarantee the card will still be
 * physically present, even अगर the call to this function वापसs
 * non-शून्य. Furthermore, the device driver most likely is unbound
 * almost immediately, so the समयframe where pcmcia_dev_present
 * वापसs शून्य is probably really really small.
 */
काष्ठा pcmcia_device *pcmcia_dev_present(काष्ठा pcmcia_device *_p_dev)
अणु
	काष्ठा pcmcia_device *p_dev;
	काष्ठा pcmcia_device *ret = शून्य;

	p_dev = pcmcia_get_dev(_p_dev);
	अगर (!p_dev)
		वापस शून्य;

	अगर (atomic_पढ़ो(&p_dev->socket->present) != 0)
		ret = p_dev;

	pcmcia_put_dev(p_dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pcmcia_dev_present);


अटल काष्ठा pcmcia_callback pcmcia_bus_callback = अणु
	.owner = THIS_MODULE,
	.add = pcmcia_bus_add,
	.हटाओ = pcmcia_bus_हटाओ,
	.requery = pcmcia_requery,
	.validate = pccard_validate_cis,
	.suspend = pcmcia_bus_suspend,
	.early_resume = pcmcia_bus_early_resume,
	.resume = pcmcia_bus_resume,
पूर्ण;

अटल पूर्णांक pcmcia_bus_add_socket(काष्ठा device *dev,
					   काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा pcmcia_socket *socket = dev_get_drvdata(dev);
	पूर्णांक ret;

	socket = pcmcia_get_socket(socket);
	अगर (!socket) अणु
		dev_err(dev, "PCMCIA obtaining reference to socket failed\n");
		वापस -ENODEV;
	पूर्ण

	ret = sysfs_create_bin_file(&dev->kobj, &pccard_cis_attr);
	अगर (ret) अणु
		dev_err(dev, "PCMCIA registration failed\n");
		pcmcia_put_socket(socket);
		वापस ret;
	पूर्ण

	INIT_LIST_HEAD(&socket->devices_list);
	socket->pcmcia_pfc = 0;
	socket->device_count = 0;
	atomic_set(&socket->present, 0);

	ret = pccard_रेजिस्टर_pcmcia(socket, &pcmcia_bus_callback);
	अगर (ret) अणु
		dev_err(dev, "PCMCIA registration failed\n");
		pcmcia_put_socket(socket);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pcmcia_bus_हटाओ_socket(काष्ठा device *dev,
				     काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा pcmcia_socket *socket = dev_get_drvdata(dev);

	अगर (!socket)
		वापस;

	pccard_रेजिस्टर_pcmcia(socket, शून्य);

	/* unरेजिस्टर any unbound devices */
	mutex_lock(&socket->skt_mutex);
	pcmcia_card_हटाओ(socket, शून्य);
	release_cis_mem(socket);
	mutex_unlock(&socket->skt_mutex);

	sysfs_हटाओ_bin_file(&dev->kobj, &pccard_cis_attr);

	pcmcia_put_socket(socket);

	वापस;
पूर्ण


/* the pcmcia_bus_पूर्णांकerface is used to handle pcmcia socket devices */
अटल काष्ठा class_पूर्णांकerface pcmcia_bus_पूर्णांकerface __refdata = अणु
	.class = &pcmcia_socket_class,
	.add_dev = &pcmcia_bus_add_socket,
	.हटाओ_dev = &pcmcia_bus_हटाओ_socket,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops pcmcia_bus_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pcmcia_dev_suspend, pcmcia_dev_resume)
पूर्ण;

काष्ठा bus_type pcmcia_bus_type = अणु
	.name = "pcmcia",
	.uevent = pcmcia_bus_uevent,
	.match = pcmcia_bus_match,
	.dev_groups = pcmcia_dev_groups,
	.probe = pcmcia_device_probe,
	.हटाओ = pcmcia_device_हटाओ,
	.pm = &pcmcia_bus_pm_ops,
पूर्ण;


अटल पूर्णांक __init init_pcmcia_bus(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&pcmcia_bus_type);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING "pcmcia: bus_register error: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = class_पूर्णांकerface_रेजिस्टर(&pcmcia_bus_पूर्णांकerface);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING
			"pcmcia: class_interface_register error: %d\n", ret);
		bus_unरेजिस्टर(&pcmcia_bus_type);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
fs_initcall(init_pcmcia_bus); /* one level after subsys_initcall so that
			       * pcmcia_socket_class is alपढ़ोy रेजिस्टरed */


अटल व्योम __निकास निकास_pcmcia_bus(व्योम)
अणु
	class_पूर्णांकerface_unरेजिस्टर(&pcmcia_bus_पूर्णांकerface);

	bus_unरेजिस्टर(&pcmcia_bus_type);
पूर्ण
module_निकास(निकास_pcmcia_bus);


MODULE_ALIAS("ds");
