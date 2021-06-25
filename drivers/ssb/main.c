<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Subप्रणाली core
 *
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ssb/ssb.h>
#समावेश <linux/ssb/ssb_regs.h>
#समावेश <linux/ssb/ssb_driver_gige.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/slab.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>


MODULE_DESCRIPTION("Sonics Silicon Backplane driver");
MODULE_LICENSE("GPL");


/* Temporary list of yet-to-be-attached buses */
अटल LIST_HEAD(attach_queue);
/* List अगर running buses */
अटल LIST_HEAD(buses);
/* Software ID counter */
अटल अचिन्हित पूर्णांक next_busnumber;
/* buses_mutes locks the two buslists and the next_busnumber.
 * Don't lock this directly, but use ssb_buses_[un]lock() below. */
अटल DEFINE_MUTEX(buses_mutex);

/* There are dअगरferences in the codeflow, अगर the bus is
 * initialized from early boot, as various needed services
 * are not available early. This is a mechanism to delay
 * these initializations to after early boot has finished.
 * It's also used to avoid mutex locking, as that's not
 * available and needed early. */
अटल bool ssb_is_early_boot = 1;

अटल व्योम ssb_buses_lock(व्योम);
अटल व्योम ssb_buses_unlock(व्योम);


#अगर_घोषित CONFIG_SSB_PCIHOST
काष्ठा ssb_bus *ssb_pci_dev_to_bus(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ssb_bus *bus;

	ssb_buses_lock();
	list_क्रम_each_entry(bus, &buses, list) अणु
		अगर (bus->bustype == SSB_BUSTYPE_PCI &&
		    bus->host_pci == pdev)
			जाओ found;
	पूर्ण
	bus = शून्य;
found:
	ssb_buses_unlock();

	वापस bus;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCIHOST */

#अगर_घोषित CONFIG_SSB_PCMCIAHOST
काष्ठा ssb_bus *ssb_pcmcia_dev_to_bus(काष्ठा pcmcia_device *pdev)
अणु
	काष्ठा ssb_bus *bus;

	ssb_buses_lock();
	list_क्रम_each_entry(bus, &buses, list) अणु
		अगर (bus->bustype == SSB_BUSTYPE_PCMCIA &&
		    bus->host_pcmcia == pdev)
			जाओ found;
	पूर्ण
	bus = शून्य;
found:
	ssb_buses_unlock();

	वापस bus;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCMCIAHOST */

पूर्णांक ssb_क्रम_each_bus_call(अचिन्हित दीर्घ data,
			  पूर्णांक (*func)(काष्ठा ssb_bus *bus, अचिन्हित दीर्घ data))
अणु
	काष्ठा ssb_bus *bus;
	पूर्णांक res;

	ssb_buses_lock();
	list_क्रम_each_entry(bus, &buses, list) अणु
		res = func(bus, data);
		अगर (res >= 0) अणु
			ssb_buses_unlock();
			वापस res;
		पूर्ण
	पूर्ण
	ssb_buses_unlock();

	वापस -ENODEV;
पूर्ण

अटल काष्ठा ssb_device *ssb_device_get(काष्ठा ssb_device *dev)
अणु
	अगर (dev)
		get_device(dev->dev);
	वापस dev;
पूर्ण

अटल व्योम ssb_device_put(काष्ठा ssb_device *dev)
अणु
	अगर (dev)
		put_device(dev->dev);
पूर्ण

अटल पूर्णांक ssb_device_resume(काष्ठा device *dev)
अणु
	काष्ठा ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	काष्ठा ssb_driver *ssb_drv;
	पूर्णांक err = 0;

	अगर (dev->driver) अणु
		ssb_drv = drv_to_ssb_drv(dev->driver);
		अगर (ssb_drv && ssb_drv->resume)
			err = ssb_drv->resume(ssb_dev);
		अगर (err)
			जाओ out;
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक ssb_device_suspend(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	काष्ठा ssb_driver *ssb_drv;
	पूर्णांक err = 0;

	अगर (dev->driver) अणु
		ssb_drv = drv_to_ssb_drv(dev->driver);
		अगर (ssb_drv && ssb_drv->suspend)
			err = ssb_drv->suspend(ssb_dev, state);
		अगर (err)
			जाओ out;
	पूर्ण
out:
	वापस err;
पूर्ण

पूर्णांक ssb_bus_resume(काष्ठा ssb_bus *bus)
अणु
	पूर्णांक err;

	/* Reset HW state inक्रमmation in memory, so that HW is
	 * completely reinitialized. */
	bus->mapped_device = शून्य;
#अगर_घोषित CONFIG_SSB_DRIVER_PCICORE
	bus->pcicore.setup_करोne = 0;
#पूर्ण_अगर

	err = ssb_bus_घातerup(bus, 0);
	अगर (err)
		वापस err;
	err = ssb_pcmcia_hardware_setup(bus);
	अगर (err) अणु
		ssb_bus_may_घातerकरोwn(bus);
		वापस err;
	पूर्ण
	ssb_chipco_resume(&bus->chipco);
	ssb_bus_may_घातerकरोwn(bus);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ssb_bus_resume);

पूर्णांक ssb_bus_suspend(काष्ठा ssb_bus *bus)
अणु
	ssb_chipco_suspend(&bus->chipco);
	ssb_pci_xtal(bus, SSB_GPIO_XTAL | SSB_GPIO_PLL, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ssb_bus_suspend);

#अगर_घोषित CONFIG_SSB_SPROM
/** ssb_devices_मुक्तze - Freeze all devices on the bus.
 *
 * After मुक्तzing no device driver will be handling a device
 * on this bus anymore. ssb_devices_thaw() must be called after
 * a successful मुक्तze to reactivate the devices.
 *
 * @bus: The bus.
 * @ctx: Context काष्ठाure. Pass this to ssb_devices_thaw().
 */
पूर्णांक ssb_devices_मुक्तze(काष्ठा ssb_bus *bus, काष्ठा ssb_मुक्तze_context *ctx)
अणु
	काष्ठा ssb_device *sdev;
	काष्ठा ssb_driver *sdrv;
	अचिन्हित पूर्णांक i;

	स_रखो(ctx, 0, माप(*ctx));
	ctx->bus = bus;
	WARN_ON(bus->nr_devices > ARRAY_SIZE(ctx->device_frozen));

	क्रम (i = 0; i < bus->nr_devices; i++) अणु
		sdev = ssb_device_get(&bus->devices[i]);

		अगर (!sdev->dev || !sdev->dev->driver ||
		    !device_is_रेजिस्टरed(sdev->dev)) अणु
			ssb_device_put(sdev);
			जारी;
		पूर्ण
		sdrv = drv_to_ssb_drv(sdev->dev->driver);
		अगर (WARN_ON(!sdrv->हटाओ))
			जारी;
		sdrv->हटाओ(sdev);
		ctx->device_frozen[i] = 1;
	पूर्ण

	वापस 0;
पूर्ण

/** ssb_devices_thaw - Unमुक्तze all devices on the bus.
 *
 * This will re-attach the device drivers and re-init the devices.
 *
 * @ctx: The context काष्ठाure from ssb_devices_मुक्तze()
 */
पूर्णांक ssb_devices_thaw(काष्ठा ssb_मुक्तze_context *ctx)
अणु
	काष्ठा ssb_bus *bus = ctx->bus;
	काष्ठा ssb_device *sdev;
	काष्ठा ssb_driver *sdrv;
	अचिन्हित पूर्णांक i;
	पूर्णांक err, result = 0;

	क्रम (i = 0; i < bus->nr_devices; i++) अणु
		अगर (!ctx->device_frozen[i])
			जारी;
		sdev = &bus->devices[i];

		अगर (WARN_ON(!sdev->dev || !sdev->dev->driver))
			जारी;
		sdrv = drv_to_ssb_drv(sdev->dev->driver);
		अगर (WARN_ON(!sdrv || !sdrv->probe))
			जारी;

		err = sdrv->probe(sdev, &sdev->id);
		अगर (err) अणु
			dev_err(sdev->dev,
				"Failed to thaw device %s\n",
				dev_name(sdev->dev));
			result = err;
		पूर्ण
		ssb_device_put(sdev);
	पूर्ण

	वापस result;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_SPROM */

अटल व्योम ssb_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	काष्ठा ssb_driver *ssb_drv;

	अगर (!dev->driver)
		वापस;
	ssb_drv = drv_to_ssb_drv(dev->driver);
	अगर (ssb_drv && ssb_drv->shutकरोwn)
		ssb_drv->shutकरोwn(ssb_dev);
पूर्ण

अटल पूर्णांक ssb_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	काष्ठा ssb_driver *ssb_drv = drv_to_ssb_drv(dev->driver);

	अगर (ssb_drv && ssb_drv->हटाओ)
		ssb_drv->हटाओ(ssb_dev);
	ssb_device_put(ssb_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ssb_device_probe(काष्ठा device *dev)
अणु
	काष्ठा ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	काष्ठा ssb_driver *ssb_drv = drv_to_ssb_drv(dev->driver);
	पूर्णांक err = 0;

	ssb_device_get(ssb_dev);
	अगर (ssb_drv && ssb_drv->probe)
		err = ssb_drv->probe(ssb_dev, &ssb_dev->id);
	अगर (err)
		ssb_device_put(ssb_dev);

	वापस err;
पूर्ण

अटल पूर्णांक ssb_match_devid(स्थिर काष्ठा ssb_device_id *tabid,
			   स्थिर काष्ठा ssb_device_id *devid)
अणु
	अगर ((tabid->venकरोr != devid->venकरोr) &&
	    tabid->venकरोr != SSB_ANY_VENDOR)
		वापस 0;
	अगर ((tabid->coreid != devid->coreid) &&
	    tabid->coreid != SSB_ANY_ID)
		वापस 0;
	अगर ((tabid->revision != devid->revision) &&
	    tabid->revision != SSB_ANY_REV)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक ssb_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	काष्ठा ssb_driver *ssb_drv = drv_to_ssb_drv(drv);
	स्थिर काष्ठा ssb_device_id *id;

	क्रम (id = ssb_drv->id_table;
	     id->venकरोr || id->coreid || id->revision;
	     id++) अणु
		अगर (ssb_match_devid(id, &ssb_dev->id))
			वापस 1; /* found */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssb_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा ssb_device *ssb_dev = dev_to_ssb_dev(dev);

	अगर (!dev)
		वापस -ENODEV;

	वापस add_uevent_var(env,
			     "MODALIAS=ssb:v%04Xid%04Xrev%02X",
			     ssb_dev->id.venकरोr, ssb_dev->id.coreid,
			     ssb_dev->id.revision);
पूर्ण

#घोषणा ssb_config_attr(attrib, field, क्रमmat_string) \
अटल sमाप_प्रकार \
attrib##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	वापस प्र_लिखो(buf, क्रमmat_string, dev_to_ssb_dev(dev)->field); \
पूर्ण \
अटल DEVICE_ATTR_RO(attrib);

ssb_config_attr(core_num, core_index, "%u\n")
ssb_config_attr(coreid, id.coreid, "0x%04x\n")
ssb_config_attr(venकरोr, id.venकरोr, "0x%04x\n")
ssb_config_attr(revision, id.revision, "%u\n")
ssb_config_attr(irq, irq, "%u\n")
अटल sमाप_प्रकार
name_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n",
		       ssb_core_name(dev_to_ssb_dev(dev)->id.coreid));
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *ssb_device_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_core_num.attr,
	&dev_attr_coreid.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_revision.attr,
	&dev_attr_irq.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ssb_device);

अटल काष्ठा bus_type ssb_bustype = अणु
	.name		= "ssb",
	.match		= ssb_bus_match,
	.probe		= ssb_device_probe,
	.हटाओ		= ssb_device_हटाओ,
	.shutकरोwn	= ssb_device_shutकरोwn,
	.suspend	= ssb_device_suspend,
	.resume		= ssb_device_resume,
	.uevent		= ssb_device_uevent,
	.dev_groups	= ssb_device_groups,
पूर्ण;

अटल व्योम ssb_buses_lock(व्योम)
अणु
	/* See the comment at the ssb_is_early_boot definition */
	अगर (!ssb_is_early_boot)
		mutex_lock(&buses_mutex);
पूर्ण

अटल व्योम ssb_buses_unlock(व्योम)
अणु
	/* See the comment at the ssb_is_early_boot definition */
	अगर (!ssb_is_early_boot)
		mutex_unlock(&buses_mutex);
पूर्ण

अटल व्योम ssb_devices_unरेजिस्टर(काष्ठा ssb_bus *bus)
अणु
	काष्ठा ssb_device *sdev;
	पूर्णांक i;

	क्रम (i = bus->nr_devices - 1; i >= 0; i--) अणु
		sdev = &(bus->devices[i]);
		अगर (sdev->dev)
			device_unरेजिस्टर(sdev->dev);
	पूर्ण

#अगर_घोषित CONFIG_SSB_EMBEDDED
	अगर (bus->bustype == SSB_BUSTYPE_SSB)
		platक्रमm_device_unरेजिस्टर(bus->watchकरोg);
#पूर्ण_अगर
पूर्ण

व्योम ssb_bus_unरेजिस्टर(काष्ठा ssb_bus *bus)
अणु
	पूर्णांक err;

	err = ssb_gpio_unरेजिस्टर(bus);
	अगर (err == -EBUSY)
		pr_debug("Some GPIOs are still in use\n");
	अन्यथा अगर (err)
		pr_debug("Can not unregister GPIO driver: %i\n", err);

	ssb_buses_lock();
	ssb_devices_unरेजिस्टर(bus);
	list_del(&bus->list);
	ssb_buses_unlock();

	ssb_pcmcia_निकास(bus);
	ssb_pci_निकास(bus);
	ssb_iounmap(bus);
पूर्ण
EXPORT_SYMBOL(ssb_bus_unरेजिस्टर);

अटल व्योम ssb_release_dev(काष्ठा device *dev)
अणु
	काष्ठा __ssb_dev_wrapper *devwrap;

	devwrap = container_of(dev, काष्ठा __ssb_dev_wrapper, dev);
	kमुक्त(devwrap);
पूर्ण

अटल पूर्णांक ssb_devices_रेजिस्टर(काष्ठा ssb_bus *bus)
अणु
	काष्ठा ssb_device *sdev;
	काष्ठा device *dev;
	काष्ठा __ssb_dev_wrapper *devwrap;
	पूर्णांक i, err = 0;
	पूर्णांक dev_idx = 0;

	क्रम (i = 0; i < bus->nr_devices; i++) अणु
		sdev = &(bus->devices[i]);

		/* We करोn't रेजिस्टर SSB-प्रणाली devices to the kernel,
		 * as the drivers क्रम them are built पूर्णांकo SSB. */
		चयन (sdev->id.coreid) अणु
		हाल SSB_DEV_CHIPCOMMON:
		हाल SSB_DEV_PCI:
		हाल SSB_DEV_PCIE:
		हाल SSB_DEV_PCMCIA:
		हाल SSB_DEV_MIPS:
		हाल SSB_DEV_MIPS_3302:
		हाल SSB_DEV_EXTIF:
			जारी;
		पूर्ण

		devwrap = kzalloc(माप(*devwrap), GFP_KERNEL);
		अगर (!devwrap) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
		dev = &devwrap->dev;
		devwrap->sdev = sdev;

		dev->release = ssb_release_dev;
		dev->bus = &ssb_bustype;
		dev_set_name(dev, "ssb%u:%d", bus->busnumber, dev_idx);

		चयन (bus->bustype) अणु
		हाल SSB_BUSTYPE_PCI:
#अगर_घोषित CONFIG_SSB_PCIHOST
			sdev->irq = bus->host_pci->irq;
			dev->parent = &bus->host_pci->dev;
			sdev->dma_dev = dev->parent;
#पूर्ण_अगर
			अवरोध;
		हाल SSB_BUSTYPE_PCMCIA:
#अगर_घोषित CONFIG_SSB_PCMCIAHOST
			sdev->irq = bus->host_pcmcia->irq;
			dev->parent = &bus->host_pcmcia->dev;
#पूर्ण_अगर
			अवरोध;
		हाल SSB_BUSTYPE_SDIO:
#अगर_घोषित CONFIG_SSB_SDIOHOST
			dev->parent = &bus->host_sdio->dev;
#पूर्ण_अगर
			अवरोध;
		हाल SSB_BUSTYPE_SSB:
			dev->dma_mask = &dev->coherent_dma_mask;
			sdev->dma_dev = dev;
			अवरोध;
		पूर्ण

		sdev->dev = dev;
		err = device_रेजिस्टर(dev);
		अगर (err) अणु
			pr_err("Could not register %s\n", dev_name(dev));
			/* Set dev to शून्य to not unरेजिस्टर
			 * dev on error unwinding. */
			sdev->dev = शून्य;
			put_device(dev);
			जाओ error;
		पूर्ण
		dev_idx++;
	पूर्ण

#अगर_घोषित CONFIG_SSB_DRIVER_MIPS
	अगर (bus->mipscore.pflash.present) अणु
		err = platक्रमm_device_रेजिस्टर(&ssb_pflash_dev);
		अगर (err)
			pr_err("Error registering parallel flash\n");
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SSB_SFLASH
	अगर (bus->mipscore.sflash.present) अणु
		err = platक्रमm_device_रेजिस्टर(&ssb_sflash_dev);
		अगर (err)
			pr_err("Error registering serial flash\n");
	पूर्ण
#पूर्ण_अगर

	वापस 0;
error:
	/* Unwind the alपढ़ोy रेजिस्टरed devices. */
	ssb_devices_unरेजिस्टर(bus);
	वापस err;
पूर्ण

/* Needs ssb_buses_lock() */
अटल पूर्णांक ssb_attach_queued_buses(व्योम)
अणु
	काष्ठा ssb_bus *bus, *n;
	पूर्णांक err = 0;
	पूर्णांक drop_them_all = 0;

	list_क्रम_each_entry_safe(bus, n, &attach_queue, list) अणु
		अगर (drop_them_all) अणु
			list_del(&bus->list);
			जारी;
		पूर्ण
		/* Can't init the PCIcore in ssb_bus_रेजिस्टर(), as that
		 * is too early in boot क्रम embedded प्रणालीs
		 * (no udelay() available). So करो it here in attach stage.
		 */
		err = ssb_bus_घातerup(bus, 0);
		अगर (err)
			जाओ error;
		ssb_pcicore_init(&bus->pcicore);
		अगर (bus->bustype == SSB_BUSTYPE_SSB)
			ssb_watchकरोg_रेजिस्टर(bus);

		err = ssb_gpio_init(bus);
		अगर (err == -ENOTSUPP)
			pr_debug("GPIO driver not activated\n");
		अन्यथा अगर (err)
			pr_debug("Error registering GPIO driver: %i\n", err);

		ssb_bus_may_घातerकरोwn(bus);

		err = ssb_devices_रेजिस्टर(bus);
error:
		अगर (err) अणु
			drop_them_all = 1;
			list_del(&bus->list);
			जारी;
		पूर्ण
		list_move_tail(&bus->list, &buses);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ssb_fetch_invariants(काष्ठा ssb_bus *bus,
				ssb_invariants_func_t get_invariants)
अणु
	काष्ठा ssb_init_invariants iv;
	पूर्णांक err;

	स_रखो(&iv, 0, माप(iv));
	err = get_invariants(bus, &iv);
	अगर (err)
		जाओ out;
	स_नकल(&bus->boardinfo, &iv.boardinfo, माप(iv.boardinfo));
	स_नकल(&bus->sprom, &iv.sprom, माप(iv.sprom));
	bus->has_cardbus_slot = iv.has_cardbus_slot;
out:
	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused
ssb_bus_रेजिस्टर(काष्ठा ssb_bus *bus,
		 ssb_invariants_func_t get_invariants,
		 अचिन्हित दीर्घ baseaddr)
अणु
	पूर्णांक err;

	spin_lock_init(&bus->bar_lock);
	INIT_LIST_HEAD(&bus->list);
#अगर_घोषित CONFIG_SSB_EMBEDDED
	spin_lock_init(&bus->gpio_lock);
#पूर्ण_अगर

	/* Powerup the bus */
	err = ssb_pci_xtal(bus, SSB_GPIO_XTAL | SSB_GPIO_PLL, 1);
	अगर (err)
		जाओ out;

	/* Init SDIO-host device (अगर any), beक्रमe the scan */
	err = ssb_sdio_init(bus);
	अगर (err)
		जाओ err_disable_xtal;

	ssb_buses_lock();
	bus->busnumber = next_busnumber;
	/* Scan क्रम devices (cores) */
	err = ssb_bus_scan(bus, baseaddr);
	अगर (err)
		जाओ err_sdio_निकास;

	/* Init PCI-host device (अगर any) */
	err = ssb_pci_init(bus);
	अगर (err)
		जाओ err_unmap;
	/* Init PCMCIA-host device (अगर any) */
	err = ssb_pcmcia_init(bus);
	अगर (err)
		जाओ err_pci_निकास;

	/* Initialize basic प्रणाली devices (अगर available) */
	err = ssb_bus_घातerup(bus, 0);
	अगर (err)
		जाओ err_pcmcia_निकास;
	ssb_chipcommon_init(&bus->chipco);
	ssb_extअगर_init(&bus->extअगर);
	ssb_mipscore_init(&bus->mipscore);
	err = ssb_fetch_invariants(bus, get_invariants);
	अगर (err) अणु
		ssb_bus_may_घातerकरोwn(bus);
		जाओ err_pcmcia_निकास;
	पूर्ण
	ssb_bus_may_घातerकरोwn(bus);

	/* Queue it क्रम attach.
	 * See the comment at the ssb_is_early_boot definition. */
	list_add_tail(&bus->list, &attach_queue);
	अगर (!ssb_is_early_boot) अणु
		/* This is not early boot, so we must attach the bus now */
		err = ssb_attach_queued_buses();
		अगर (err)
			जाओ err_dequeue;
	पूर्ण
	next_busnumber++;
	ssb_buses_unlock();

out:
	वापस err;

err_dequeue:
	list_del(&bus->list);
err_pcmcia_निकास:
	ssb_pcmcia_निकास(bus);
err_pci_निकास:
	ssb_pci_निकास(bus);
err_unmap:
	ssb_iounmap(bus);
err_sdio_निकास:
	ssb_sdio_निकास(bus);
err_disable_xtal:
	ssb_buses_unlock();
	ssb_pci_xtal(bus, SSB_GPIO_XTAL | SSB_GPIO_PLL, 0);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_SSB_PCIHOST
पूर्णांक ssb_bus_pcibus_रेजिस्टर(काष्ठा ssb_bus *bus, काष्ठा pci_dev *host_pci)
अणु
	पूर्णांक err;

	bus->bustype = SSB_BUSTYPE_PCI;
	bus->host_pci = host_pci;
	bus->ops = &ssb_pci_ops;

	err = ssb_bus_रेजिस्टर(bus, ssb_pci_get_invariants, 0);
	अगर (!err) अणु
		dev_info(&host_pci->dev,
			 "Sonics Silicon Backplane found on PCI device %s\n",
			 dev_name(&host_pci->dev));
	पूर्ण अन्यथा अणु
		dev_err(&host_pci->dev,
			"Failed to register PCI version of SSB with error %d\n",
			err);
	पूर्ण

	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCIHOST */

#अगर_घोषित CONFIG_SSB_PCMCIAHOST
पूर्णांक ssb_bus_pcmciabus_रेजिस्टर(काष्ठा ssb_bus *bus,
			       काष्ठा pcmcia_device *pcmcia_dev,
			       अचिन्हित दीर्घ baseaddr)
अणु
	पूर्णांक err;

	bus->bustype = SSB_BUSTYPE_PCMCIA;
	bus->host_pcmcia = pcmcia_dev;
	bus->ops = &ssb_pcmcia_ops;

	err = ssb_bus_रेजिस्टर(bus, ssb_pcmcia_get_invariants, baseaddr);
	अगर (!err) अणु
		dev_info(&pcmcia_dev->dev,
			 "Sonics Silicon Backplane found on PCMCIA device %s\n",
			 pcmcia_dev->devname);
	पूर्ण

	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCMCIAHOST */

#अगर_घोषित CONFIG_SSB_SDIOHOST
पूर्णांक ssb_bus_sdiobus_रेजिस्टर(काष्ठा ssb_bus *bus, काष्ठा sdio_func *func,
			     अचिन्हित पूर्णांक quirks)
अणु
	पूर्णांक err;

	bus->bustype = SSB_BUSTYPE_SDIO;
	bus->host_sdio = func;
	bus->ops = &ssb_sdio_ops;
	bus->quirks = quirks;

	err = ssb_bus_रेजिस्टर(bus, ssb_sdio_get_invariants, ~0);
	अगर (!err) अणु
		dev_info(&func->dev,
			 "Sonics Silicon Backplane found on SDIO device %s\n",
			 sdio_func_id(func));
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(ssb_bus_sdiobus_रेजिस्टर);
#पूर्ण_अगर /* CONFIG_SSB_PCMCIAHOST */

#अगर_घोषित CONFIG_SSB_HOST_SOC
पूर्णांक ssb_bus_host_soc_रेजिस्टर(काष्ठा ssb_bus *bus, अचिन्हित दीर्घ baseaddr)
अणु
	पूर्णांक err;

	bus->bustype = SSB_BUSTYPE_SSB;
	bus->ops = &ssb_host_soc_ops;

	err = ssb_bus_रेजिस्टर(bus, ssb_host_soc_get_invariants, baseaddr);
	अगर (!err) अणु
		pr_info("Sonics Silicon Backplane found at address 0x%08lX\n",
			baseaddr);
	पूर्ण

	वापस err;
पूर्ण
#पूर्ण_अगर

पूर्णांक __ssb_driver_रेजिस्टर(काष्ठा ssb_driver *drv, काष्ठा module *owner)
अणु
	drv->drv.name = drv->name;
	drv->drv.bus = &ssb_bustype;
	drv->drv.owner = owner;

	वापस driver_रेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL(__ssb_driver_रेजिस्टर);

व्योम ssb_driver_unरेजिस्टर(काष्ठा ssb_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL(ssb_driver_unरेजिस्टर);

व्योम ssb_set_devtypedata(काष्ठा ssb_device *dev, व्योम *data)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	काष्ठा ssb_device *ent;
	पूर्णांक i;

	क्रम (i = 0; i < bus->nr_devices; i++) अणु
		ent = &(bus->devices[i]);
		अगर (ent->id.venकरोr != dev->id.venकरोr)
			जारी;
		अगर (ent->id.coreid != dev->id.coreid)
			जारी;

		ent->devtypedata = data;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ssb_set_devtypedata);

अटल u32 clkfactor_f6_resolve(u32 v)
अणु
	/* map the magic values */
	चयन (v) अणु
	हाल SSB_CHIPCO_CLK_F6_2:
		वापस 2;
	हाल SSB_CHIPCO_CLK_F6_3:
		वापस 3;
	हाल SSB_CHIPCO_CLK_F6_4:
		वापस 4;
	हाल SSB_CHIPCO_CLK_F6_5:
		वापस 5;
	हाल SSB_CHIPCO_CLK_F6_6:
		वापस 6;
	हाल SSB_CHIPCO_CLK_F6_7:
		वापस 7;
	पूर्ण
	वापस 0;
पूर्ण

/* Calculate the speed the backplane would run at a given set of घड़ीcontrol values */
u32 ssb_calc_घड़ी_rate(u32 plltype, u32 n, u32 m)
अणु
	u32 n1, n2, घड़ी, m1, m2, m3, mc;

	n1 = (n & SSB_CHIPCO_CLK_N1);
	n2 = ((n & SSB_CHIPCO_CLK_N2) >> SSB_CHIPCO_CLK_N2_SHIFT);

	चयन (plltype) अणु
	हाल SSB_PLLTYPE_6: /* 100/200 or 120/240 only */
		अगर (m & SSB_CHIPCO_CLK_T6_MMASK)
			वापस SSB_CHIPCO_CLK_T6_M1;
		वापस SSB_CHIPCO_CLK_T6_M0;
	हाल SSB_PLLTYPE_1: /* 48Mhz base, 3 भागiders */
	हाल SSB_PLLTYPE_3: /* 25Mhz, 2 भागiders */
	हाल SSB_PLLTYPE_4: /* 48Mhz, 4 भागiders */
	हाल SSB_PLLTYPE_7: /* 25Mhz, 4 भागiders */
		n1 = clkfactor_f6_resolve(n1);
		n2 += SSB_CHIPCO_CLK_F5_BIAS;
		अवरोध;
	हाल SSB_PLLTYPE_2: /* 48Mhz, 4 भागiders */
		n1 += SSB_CHIPCO_CLK_T2_BIAS;
		n2 += SSB_CHIPCO_CLK_T2_BIAS;
		WARN_ON(!((n1 >= 2) && (n1 <= 7)));
		WARN_ON(!((n2 >= 5) && (n2 <= 23)));
		अवरोध;
	हाल SSB_PLLTYPE_5: /* 25Mhz, 4 भागiders */
		वापस 100000000;
	शेष:
		WARN_ON(1);
	पूर्ण

	चयन (plltype) अणु
	हाल SSB_PLLTYPE_3: /* 25Mhz, 2 भागiders */
	हाल SSB_PLLTYPE_7: /* 25Mhz, 4 भागiders */
		घड़ी = SSB_CHIPCO_CLK_BASE2 * n1 * n2;
		अवरोध;
	शेष:
		घड़ी = SSB_CHIPCO_CLK_BASE1 * n1 * n2;
	पूर्ण
	अगर (!घड़ी)
		वापस 0;

	m1 = (m & SSB_CHIPCO_CLK_M1);
	m2 = ((m & SSB_CHIPCO_CLK_M2) >> SSB_CHIPCO_CLK_M2_SHIFT);
	m3 = ((m & SSB_CHIPCO_CLK_M3) >> SSB_CHIPCO_CLK_M3_SHIFT);
	mc = ((m & SSB_CHIPCO_CLK_MC) >> SSB_CHIPCO_CLK_MC_SHIFT);

	चयन (plltype) अणु
	हाल SSB_PLLTYPE_1: /* 48Mhz base, 3 भागiders */
	हाल SSB_PLLTYPE_3: /* 25Mhz, 2 भागiders */
	हाल SSB_PLLTYPE_4: /* 48Mhz, 4 भागiders */
	हाल SSB_PLLTYPE_7: /* 25Mhz, 4 भागiders */
		m1 = clkfactor_f6_resolve(m1);
		अगर ((plltype == SSB_PLLTYPE_1) ||
		    (plltype == SSB_PLLTYPE_3))
			m2 += SSB_CHIPCO_CLK_F5_BIAS;
		अन्यथा
			m2 = clkfactor_f6_resolve(m2);
		m3 = clkfactor_f6_resolve(m3);

		चयन (mc) अणु
		हाल SSB_CHIPCO_CLK_MC_BYPASS:
			वापस घड़ी;
		हाल SSB_CHIPCO_CLK_MC_M1:
			वापस (घड़ी / m1);
		हाल SSB_CHIPCO_CLK_MC_M1M2:
			वापस (घड़ी / (m1 * m2));
		हाल SSB_CHIPCO_CLK_MC_M1M2M3:
			वापस (घड़ी / (m1 * m2 * m3));
		हाल SSB_CHIPCO_CLK_MC_M1M3:
			वापस (घड़ी / (m1 * m3));
		पूर्ण
		वापस 0;
	हाल SSB_PLLTYPE_2:
		m1 += SSB_CHIPCO_CLK_T2_BIAS;
		m2 += SSB_CHIPCO_CLK_T2M2_BIAS;
		m3 += SSB_CHIPCO_CLK_T2_BIAS;
		WARN_ON(!((m1 >= 2) && (m1 <= 7)));
		WARN_ON(!((m2 >= 3) && (m2 <= 10)));
		WARN_ON(!((m3 >= 2) && (m3 <= 7)));

		अगर (!(mc & SSB_CHIPCO_CLK_T2MC_M1BYP))
			घड़ी /= m1;
		अगर (!(mc & SSB_CHIPCO_CLK_T2MC_M2BYP))
			घड़ी /= m2;
		अगर (!(mc & SSB_CHIPCO_CLK_T2MC_M3BYP))
			घड़ी /= m3;
		वापस घड़ी;
	शेष:
		WARN_ON(1);
	पूर्ण
	वापस 0;
पूर्ण

/* Get the current speed the backplane is running at */
u32 ssb_घड़ीspeed(काष्ठा ssb_bus *bus)
अणु
	u32 rate;
	u32 plltype;
	u32 clkctl_n, clkctl_m;

	अगर (bus->chipco.capabilities & SSB_CHIPCO_CAP_PMU)
		वापस ssb_pmu_get_controlघड़ी(&bus->chipco);

	अगर (ssb_extअगर_available(&bus->extअगर))
		ssb_extअगर_get_घड़ीcontrol(&bus->extअगर, &plltype,
					   &clkctl_n, &clkctl_m);
	अन्यथा अगर (bus->chipco.dev)
		ssb_chipco_get_घड़ीcontrol(&bus->chipco, &plltype,
					    &clkctl_n, &clkctl_m);
	अन्यथा
		वापस 0;

	अगर (bus->chip_id == 0x5365) अणु
		rate = 100000000;
	पूर्ण अन्यथा अणु
		rate = ssb_calc_घड़ी_rate(plltype, clkctl_n, clkctl_m);
		अगर (plltype == SSB_PLLTYPE_3) /* 25Mhz, 2 भागiders */
			rate /= 2;
	पूर्ण

	वापस rate;
पूर्ण
EXPORT_SYMBOL(ssb_घड़ीspeed);

अटल u32 ssb_पंचांगslow_reject_biपंचांगask(काष्ठा ssb_device *dev)
अणु
	u32 rev = ssb_पढ़ो32(dev, SSB_IDLOW) & SSB_IDLOW_SSBREV;

	/* The REJECT bit seems to be dअगरferent क्रम Backplane rev 2.3 */
	चयन (rev) अणु
	हाल SSB_IDLOW_SSBREV_22:
	हाल SSB_IDLOW_SSBREV_24:
	हाल SSB_IDLOW_SSBREV_26:
		वापस SSB_TMSLOW_REJECT;
	हाल SSB_IDLOW_SSBREV_23:
		वापस SSB_TMSLOW_REJECT_23;
	हाल SSB_IDLOW_SSBREV_25:     /* TODO - find the proper REJECT bit */
	हाल SSB_IDLOW_SSBREV_27:     /* same here */
		वापस SSB_TMSLOW_REJECT;	/* this is a guess */
	हाल SSB_IDLOW_SSBREV:
		अवरोध;
	शेष:
		WARN(1, KERN_INFO "ssb: Backplane Revision 0x%.8X\n", rev);
	पूर्ण
	वापस (SSB_TMSLOW_REJECT | SSB_TMSLOW_REJECT_23);
पूर्ण

पूर्णांक ssb_device_is_enabled(काष्ठा ssb_device *dev)
अणु
	u32 val;
	u32 reject;

	reject = ssb_पंचांगslow_reject_biपंचांगask(dev);
	val = ssb_पढ़ो32(dev, SSB_TMSLOW);
	val &= SSB_TMSLOW_CLOCK | SSB_TMSLOW_RESET | reject;

	वापस (val == SSB_TMSLOW_CLOCK);
पूर्ण
EXPORT_SYMBOL(ssb_device_is_enabled);

अटल व्योम ssb_flush_पंचांगslow(काष्ठा ssb_device *dev)
अणु
	/* Make _really_ sure the device has finished the TMSLOW
	 * रेजिस्टर ग_लिखो transaction, as we risk running पूर्णांकo
	 * a machine check exception otherwise.
	 * Do this by पढ़ोing the रेजिस्टर back to commit the
	 * PCI ग_लिखो and delay an additional usec क्रम the device
	 * to react to the change. */
	ssb_पढ़ो32(dev, SSB_TMSLOW);
	udelay(1);
पूर्ण

व्योम ssb_device_enable(काष्ठा ssb_device *dev, u32 core_specअगरic_flags)
अणु
	u32 val;

	ssb_device_disable(dev, core_specअगरic_flags);
	ssb_ग_लिखो32(dev, SSB_TMSLOW,
		    SSB_TMSLOW_RESET | SSB_TMSLOW_CLOCK |
		    SSB_TMSLOW_FGC | core_specअगरic_flags);
	ssb_flush_पंचांगslow(dev);

	/* Clear SERR अगर set. This is a hw bug workaround. */
	अगर (ssb_पढ़ो32(dev, SSB_TMSHIGH) & SSB_TMSHIGH_SERR)
		ssb_ग_लिखो32(dev, SSB_TMSHIGH, 0);

	val = ssb_पढ़ो32(dev, SSB_IMSTATE);
	अगर (val & (SSB_IMSTATE_IBE | SSB_IMSTATE_TO)) अणु
		val &= ~(SSB_IMSTATE_IBE | SSB_IMSTATE_TO);
		ssb_ग_लिखो32(dev, SSB_IMSTATE, val);
	पूर्ण

	ssb_ग_लिखो32(dev, SSB_TMSLOW,
		    SSB_TMSLOW_CLOCK | SSB_TMSLOW_FGC |
		    core_specअगरic_flags);
	ssb_flush_पंचांगslow(dev);

	ssb_ग_लिखो32(dev, SSB_TMSLOW, SSB_TMSLOW_CLOCK |
		    core_specअगरic_flags);
	ssb_flush_पंचांगslow(dev);
पूर्ण
EXPORT_SYMBOL(ssb_device_enable);

/* Wait क्रम biपंचांगask in a रेजिस्टर to get set or cleared.
 * समयout is in units of ten-microseconds */
अटल पूर्णांक ssb_रुको_bits(काष्ठा ssb_device *dev, u16 reg, u32 biपंचांगask,
			 पूर्णांक समयout, पूर्णांक set)
अणु
	पूर्णांक i;
	u32 val;

	क्रम (i = 0; i < समयout; i++) अणु
		val = ssb_पढ़ो32(dev, reg);
		अगर (set) अणु
			अगर ((val & biपंचांगask) == biपंचांगask)
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (!(val & biपंचांगask))
				वापस 0;
		पूर्ण
		udelay(10);
	पूर्ण
	dev_err(dev->dev,
		"Timeout waiting for bitmask %08X on register %04X to %s\n",
		biपंचांगask, reg, set ? "set" : "clear");

	वापस -ETIMEDOUT;
पूर्ण

व्योम ssb_device_disable(काष्ठा ssb_device *dev, u32 core_specअगरic_flags)
अणु
	u32 reject, val;

	अगर (ssb_पढ़ो32(dev, SSB_TMSLOW) & SSB_TMSLOW_RESET)
		वापस;

	reject = ssb_पंचांगslow_reject_biपंचांगask(dev);

	अगर (ssb_पढ़ो32(dev, SSB_TMSLOW) & SSB_TMSLOW_CLOCK) अणु
		ssb_ग_लिखो32(dev, SSB_TMSLOW, reject | SSB_TMSLOW_CLOCK);
		ssb_रुको_bits(dev, SSB_TMSLOW, reject, 1000, 1);
		ssb_रुको_bits(dev, SSB_TMSHIGH, SSB_TMSHIGH_BUSY, 1000, 0);

		अगर (ssb_पढ़ो32(dev, SSB_IDLOW) & SSB_IDLOW_INITIATOR) अणु
			val = ssb_पढ़ो32(dev, SSB_IMSTATE);
			val |= SSB_IMSTATE_REJECT;
			ssb_ग_लिखो32(dev, SSB_IMSTATE, val);
			ssb_रुको_bits(dev, SSB_IMSTATE, SSB_IMSTATE_BUSY, 1000,
				      0);
		पूर्ण

		ssb_ग_लिखो32(dev, SSB_TMSLOW,
			SSB_TMSLOW_FGC | SSB_TMSLOW_CLOCK |
			reject | SSB_TMSLOW_RESET |
			core_specअगरic_flags);
		ssb_flush_पंचांगslow(dev);

		अगर (ssb_पढ़ो32(dev, SSB_IDLOW) & SSB_IDLOW_INITIATOR) अणु
			val = ssb_पढ़ो32(dev, SSB_IMSTATE);
			val &= ~SSB_IMSTATE_REJECT;
			ssb_ग_लिखो32(dev, SSB_IMSTATE, val);
		पूर्ण
	पूर्ण

	ssb_ग_लिखो32(dev, SSB_TMSLOW,
		    reject | SSB_TMSLOW_RESET |
		    core_specअगरic_flags);
	ssb_flush_पंचांगslow(dev);
पूर्ण
EXPORT_SYMBOL(ssb_device_disable);

/* Some chipsets need routing known क्रम PCIe and 64-bit DMA */
अटल bool ssb_dma_translation_special_bit(काष्ठा ssb_device *dev)
अणु
	u16 chip_id = dev->bus->chip_id;

	अगर (dev->id.coreid == SSB_DEV_80211) अणु
		वापस (chip_id == 0x4322 || chip_id == 43221 ||
			chip_id == 43231 || chip_id == 43222);
	पूर्ण

	वापस false;
पूर्ण

u32 ssb_dma_translation(काष्ठा ssb_device *dev)
अणु
	चयन (dev->bus->bustype) अणु
	हाल SSB_BUSTYPE_SSB:
		वापस 0;
	हाल SSB_BUSTYPE_PCI:
		अगर (pci_is_pcie(dev->bus->host_pci) &&
		    ssb_पढ़ो32(dev, SSB_TMSHIGH) & SSB_TMSHIGH_DMA64) अणु
			वापस SSB_PCIE_DMA_H32;
		पूर्ण अन्यथा अणु
			अगर (ssb_dma_translation_special_bit(dev))
				वापस SSB_PCIE_DMA_H32;
			अन्यथा
				वापस SSB_PCI_DMA;
		पूर्ण
	शेष:
		__ssb_dma_not_implemented(dev);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ssb_dma_translation);

पूर्णांक ssb_bus_may_घातerकरोwn(काष्ठा ssb_bus *bus)
अणु
	काष्ठा ssb_chipcommon *cc;
	पूर्णांक err = 0;

	/* On buses where more than one core may be working
	 * at a समय, we must not घातerकरोwn stuff अगर there are
	 * still cores that may want to run. */
	अगर (bus->bustype == SSB_BUSTYPE_SSB)
		जाओ out;

	cc = &bus->chipco;

	अगर (!cc->dev)
		जाओ out;
	अगर (cc->dev->id.revision < 5)
		जाओ out;

	ssb_chipco_set_घड़ीmode(cc, SSB_CLKMODE_SLOW);
	err = ssb_pci_xtal(bus, SSB_GPIO_XTAL | SSB_GPIO_PLL, 0);
	अगर (err)
		जाओ error;
out:
	bus->घातered_up = 0;
	वापस err;
error:
	pr_err("Bus powerdown failed\n");
	जाओ out;
पूर्ण
EXPORT_SYMBOL(ssb_bus_may_घातerकरोwn);

पूर्णांक ssb_bus_घातerup(काष्ठा ssb_bus *bus, bool dynamic_pctl)
अणु
	पूर्णांक err;
	क्रमागत ssb_clkmode mode;

	err = ssb_pci_xtal(bus, SSB_GPIO_XTAL | SSB_GPIO_PLL, 1);
	अगर (err)
		जाओ error;

	bus->घातered_up = 1;

	mode = dynamic_pctl ? SSB_CLKMODE_DYNAMIC : SSB_CLKMODE_FAST;
	ssb_chipco_set_घड़ीmode(&bus->chipco, mode);

	वापस 0;
error:
	pr_err("Bus powerup failed\n");
	वापस err;
पूर्ण
EXPORT_SYMBOL(ssb_bus_घातerup);

अटल व्योम ssb_broadcast_value(काष्ठा ssb_device *dev,
				u32 address, u32 data)
अणु
#अगर_घोषित CONFIG_SSB_DRIVER_PCICORE
	/* This is used क्रम both, PCI and ChipCommon core, so be careful. */
	BUILD_BUG_ON(SSB_PCICORE_BCAST_ADDR != SSB_CHIPCO_BCAST_ADDR);
	BUILD_BUG_ON(SSB_PCICORE_BCAST_DATA != SSB_CHIPCO_BCAST_DATA);
#पूर्ण_अगर

	ssb_ग_लिखो32(dev, SSB_CHIPCO_BCAST_ADDR, address);
	ssb_पढ़ो32(dev, SSB_CHIPCO_BCAST_ADDR); /* flush */
	ssb_ग_लिखो32(dev, SSB_CHIPCO_BCAST_DATA, data);
	ssb_पढ़ो32(dev, SSB_CHIPCO_BCAST_DATA); /* flush */
पूर्ण

व्योम ssb_commit_settings(काष्ठा ssb_bus *bus)
अणु
	काष्ठा ssb_device *dev;

#अगर_घोषित CONFIG_SSB_DRIVER_PCICORE
	dev = bus->chipco.dev ? bus->chipco.dev : bus->pcicore.dev;
#अन्यथा
	dev = bus->chipco.dev;
#पूर्ण_अगर
	अगर (WARN_ON(!dev))
		वापस;
	/* This क्रमces an update of the cached रेजिस्टरs. */
	ssb_broadcast_value(dev, 0xFD8, 0);
पूर्ण
EXPORT_SYMBOL(ssb_commit_settings);

u32 ssb_admatch_base(u32 adm)
अणु
	u32 base = 0;

	चयन (adm & SSB_ADM_TYPE) अणु
	हाल SSB_ADM_TYPE0:
		base = (adm & SSB_ADM_BASE0);
		अवरोध;
	हाल SSB_ADM_TYPE1:
		WARN_ON(adm & SSB_ADM_NEG); /* unsupported */
		base = (adm & SSB_ADM_BASE1);
		अवरोध;
	हाल SSB_ADM_TYPE2:
		WARN_ON(adm & SSB_ADM_NEG); /* unsupported */
		base = (adm & SSB_ADM_BASE2);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस base;
पूर्ण
EXPORT_SYMBOL(ssb_admatch_base);

u32 ssb_admatch_size(u32 adm)
अणु
	u32 size = 0;

	चयन (adm & SSB_ADM_TYPE) अणु
	हाल SSB_ADM_TYPE0:
		size = ((adm & SSB_ADM_SZ0) >> SSB_ADM_SZ0_SHIFT);
		अवरोध;
	हाल SSB_ADM_TYPE1:
		WARN_ON(adm & SSB_ADM_NEG); /* unsupported */
		size = ((adm & SSB_ADM_SZ1) >> SSB_ADM_SZ1_SHIFT);
		अवरोध;
	हाल SSB_ADM_TYPE2:
		WARN_ON(adm & SSB_ADM_NEG); /* unsupported */
		size = ((adm & SSB_ADM_SZ2) >> SSB_ADM_SZ2_SHIFT);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
	size = (1 << (size + 1));

	वापस size;
पूर्ण
EXPORT_SYMBOL(ssb_admatch_size);

अटल पूर्णांक __init ssb_modinit(व्योम)
अणु
	पूर्णांक err;

	/* See the comment at the ssb_is_early_boot definition */
	ssb_is_early_boot = 0;
	err = bus_रेजिस्टर(&ssb_bustype);
	अगर (err)
		वापस err;

	/* Maybe we alपढ़ोy रेजिस्टरed some buses at early boot.
	 * Check क्रम this and attach them
	 */
	ssb_buses_lock();
	err = ssb_attach_queued_buses();
	ssb_buses_unlock();
	अगर (err) अणु
		bus_unरेजिस्टर(&ssb_bustype);
		जाओ out;
	पूर्ण

	err = b43_pci_ssb_bridge_init();
	अगर (err) अणु
		pr_err("Broadcom 43xx PCI-SSB-bridge initialization failed\n");
		/* करोn't fail SSB init because of this */
		err = 0;
	पूर्ण
	err = ssb_host_pcmcia_init();
	अगर (err) अणु
		pr_err("PCMCIA host initialization failed\n");
		/* करोn't fail SSB init because of this */
		err = 0;
	पूर्ण
	err = ssb_gige_init();
	अगर (err) अणु
		pr_err("SSB Broadcom Gigabit Ethernet driver initialization failed\n");
		/* करोn't fail SSB init because of this */
		err = 0;
	पूर्ण
out:
	वापस err;
पूर्ण
/* ssb must be initialized after PCI but beक्रमe the ssb drivers.
 * That means we must use some initcall between subsys_initcall
 * and device_initcall. */
fs_initcall(ssb_modinit);

अटल व्योम __निकास ssb_modनिकास(व्योम)
अणु
	ssb_gige_निकास();
	ssb_host_pcmcia_निकास();
	b43_pci_ssb_bridge_निकास();
	bus_unरेजिस्टर(&ssb_bustype);
पूर्ण
module_निकास(ssb_modनिकास)
