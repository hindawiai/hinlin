<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * PCI Hostdevice wrapper
 *
 * Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>
 * Copyright (c) 2005 Stefano Brivio <st3@riseup.net>
 * Copyright (c) 2005 Danny van Dyk <kugelfang@gentoo.org>
 * Copyright (c) 2005 Andreas Jaggi <andreas.jaggi@waterwave.ch>
 * Copyright (c) 2005-2007 Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश <linux/pm.h>
#समावेश <linux/pci.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/ssb/ssb.h>


#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ssb_pcihost_suspend(काष्ठा device *d)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(d);
	काष्ठा ssb_bus *ssb = pci_get_drvdata(dev);
	पूर्णांक err;

	err = ssb_bus_suspend(ssb);
	अगर (err)
		वापस err;
	pci_save_state(dev);
	pci_disable_device(dev);

	/* अगर there is a wakeup enabled child device on ssb bus,
	   enable pci wakeup posibility. */
	device_set_wakeup_enable(d, d->घातer.wakeup_path);

	pci_prepare_to_sleep(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ssb_pcihost_resume(काष्ठा device *d)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(d);
	काष्ठा ssb_bus *ssb = pci_get_drvdata(dev);
	पूर्णांक err;

	pci_back_from_sleep(dev);
	err = pci_enable_device(dev);
	अगर (err)
		वापस err;
	pci_restore_state(dev);
	err = ssb_bus_resume(ssb);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ssb_pcihost_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ssb_pcihost_suspend, ssb_pcihost_resume)
पूर्ण;

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक ssb_pcihost_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ssb_bus *ssb;
	पूर्णांक err = -ENOMEM;
	स्थिर अक्षर *name;
	u32 val;

	ssb = kzalloc(माप(*ssb), GFP_KERNEL);
	अगर (!ssb)
		जाओ out;
	err = pci_enable_device(dev);
	अगर (err)
		जाओ err_kमुक्त_ssb;
	name = dev_name(&dev->dev);
	अगर (dev->driver && dev->driver->name)
		name = dev->driver->name;
	err = pci_request_regions(dev, name);
	अगर (err)
		जाओ err_pci_disable;
	pci_set_master(dev);

	/* Disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state */
	pci_पढ़ो_config_dword(dev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(dev, 0x40, val & 0xffff00ff);

	err = ssb_bus_pcibus_रेजिस्टर(ssb, dev);
	अगर (err)
		जाओ err_pci_release_regions;

	pci_set_drvdata(dev, ssb);

out:
	वापस err;

err_pci_release_regions:
	pci_release_regions(dev);
err_pci_disable:
	pci_disable_device(dev);
err_kमुक्त_ssb:
	kमुक्त(ssb);
	वापस err;
पूर्ण

अटल व्योम ssb_pcihost_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ssb_bus *ssb = pci_get_drvdata(dev);

	ssb_bus_unरेजिस्टर(ssb);
	pci_release_regions(dev);
	pci_disable_device(dev);
	kमुक्त(ssb);
	pci_set_drvdata(dev, शून्य);
पूर्ण

पूर्णांक ssb_pcihost_रेजिस्टर(काष्ठा pci_driver *driver)
अणु
	driver->probe = ssb_pcihost_probe;
	driver->हटाओ = ssb_pcihost_हटाओ;
#अगर_घोषित CONFIG_PM_SLEEP
	driver->driver.pm = &ssb_pcihost_pm_ops;
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(driver);
पूर्ण
EXPORT_SYMBOL(ssb_pcihost_रेजिस्टर);
