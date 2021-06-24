<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/usb/driver.c - most of the driver model stuff क्रम usb
 *
 * (C) Copyright 2005 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 *
 * based on drivers/usb/usb.c which had the following copyrights:
 *	(C) Copyright Linus Torvalds 1999
 *	(C) Copyright Johannes Erdfelt 1999-2001
 *	(C) Copyright Andreas Gal 1999
 *	(C) Copyright Gregory P. Smith 1999
 *	(C) Copyright Deti Fliegl 1999 (new USB architecture)
 *	(C) Copyright Randy Dunlap 2000
 *	(C) Copyright David Brownell 2000-2004
 *	(C) Copyright Yggdrasil Computing, Inc. 2000
 *		(usb_device_id matching changes by Adam J. Richter)
 *	(C) Copyright Greg Kroah-Harपंचांगan 2002-2003
 *
 * Released under the GPLv2 only.
 *
 * NOTE! This is not actually a driver at all, rather this is
 * just a collection of helper routines that implement the
 * matching, probing, releasing, suspending and resuming क्रम
 * real drivers.
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/quirks.h>
#समावेश <linux/usb/hcd.h>

#समावेश "usb.h"


/*
 * Adds a new dynamic USBdevice ID to this driver,
 * and cause the driver to probe क्रम all devices again.
 */
sमाप_प्रकार usb_store_new_id(काष्ठा usb_dynids *dynids,
			 स्थिर काष्ठा usb_device_id *id_table,
			 काष्ठा device_driver *driver,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_dynid *dynid;
	u32 idVenकरोr = 0;
	u32 idProduct = 0;
	अचिन्हित पूर्णांक bInterfaceClass = 0;
	u32 refVenकरोr, refProduct;
	पूर्णांक fields = 0;
	पूर्णांक retval = 0;

	fields = माला_पूछो(buf, "%x %x %x %x %x", &idVenकरोr, &idProduct,
			&bInterfaceClass, &refVenकरोr, &refProduct);
	अगर (fields < 2)
		वापस -EINVAL;

	dynid = kzalloc(माप(*dynid), GFP_KERNEL);
	अगर (!dynid)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&dynid->node);
	dynid->id.idVenकरोr = idVenकरोr;
	dynid->id.idProduct = idProduct;
	dynid->id.match_flags = USB_DEVICE_ID_MATCH_DEVICE;
	अगर (fields > 2 && bInterfaceClass) अणु
		अगर (bInterfaceClass > 255) अणु
			retval = -EINVAL;
			जाओ fail;
		पूर्ण

		dynid->id.bInterfaceClass = (u8)bInterfaceClass;
		dynid->id.match_flags |= USB_DEVICE_ID_MATCH_INT_CLASS;
	पूर्ण

	अगर (fields > 4) अणु
		स्थिर काष्ठा usb_device_id *id = id_table;

		अगर (!id) अणु
			retval = -ENODEV;
			जाओ fail;
		पूर्ण

		क्रम (; id->match_flags; id++)
			अगर (id->idVenकरोr == refVenकरोr && id->idProduct == refProduct)
				अवरोध;

		अगर (id->match_flags) अणु
			dynid->id.driver_info = id->driver_info;
		पूर्ण अन्यथा अणु
			retval = -ENODEV;
			जाओ fail;
		पूर्ण
	पूर्ण

	spin_lock(&dynids->lock);
	list_add_tail(&dynid->node, &dynids->list);
	spin_unlock(&dynids->lock);

	retval = driver_attach(driver);

	अगर (retval)
		वापस retval;
	वापस count;

fail:
	kमुक्त(dynid);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(usb_store_new_id);

sमाप_प्रकार usb_show_dynids(काष्ठा usb_dynids *dynids, अक्षर *buf)
अणु
	काष्ठा usb_dynid *dynid;
	माप_प्रकार count = 0;

	list_क्रम_each_entry(dynid, &dynids->list, node)
		अगर (dynid->id.bInterfaceClass != 0)
			count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "%04x %04x %02x\n",
					   dynid->id.idVenकरोr, dynid->id.idProduct,
					   dynid->id.bInterfaceClass);
		अन्यथा
			count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "%04x %04x\n",
					   dynid->id.idVenकरोr, dynid->id.idProduct);
	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(usb_show_dynids);

अटल sमाप_प्रकार new_id_show(काष्ठा device_driver *driver, अक्षर *buf)
अणु
	काष्ठा usb_driver *usb_drv = to_usb_driver(driver);

	वापस usb_show_dynids(&usb_drv->dynids, buf);
पूर्ण

अटल sमाप_प्रकार new_id_store(काष्ठा device_driver *driver,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_driver *usb_drv = to_usb_driver(driver);

	वापस usb_store_new_id(&usb_drv->dynids, usb_drv->id_table, driver, buf, count);
पूर्ण
अटल DRIVER_ATTR_RW(new_id);

/*
 * Remove a USB device ID from this driver
 */
अटल sमाप_प्रकार हटाओ_id_store(काष्ठा device_driver *driver, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा usb_dynid *dynid, *n;
	काष्ठा usb_driver *usb_driver = to_usb_driver(driver);
	u32 idVenकरोr;
	u32 idProduct;
	पूर्णांक fields;

	fields = माला_पूछो(buf, "%x %x", &idVenकरोr, &idProduct);
	अगर (fields < 2)
		वापस -EINVAL;

	spin_lock(&usb_driver->dynids.lock);
	list_क्रम_each_entry_safe(dynid, n, &usb_driver->dynids.list, node) अणु
		काष्ठा usb_device_id *id = &dynid->id;

		अगर ((id->idVenकरोr == idVenकरोr) &&
		    (id->idProduct == idProduct)) अणु
			list_del(&dynid->node);
			kमुक्त(dynid);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&usb_driver->dynids.lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार हटाओ_id_show(काष्ठा device_driver *driver, अक्षर *buf)
अणु
	वापस new_id_show(driver, buf);
पूर्ण
अटल DRIVER_ATTR_RW(हटाओ_id);

अटल पूर्णांक usb_create_newid_files(काष्ठा usb_driver *usb_drv)
अणु
	पूर्णांक error = 0;

	अगर (usb_drv->no_dynamic_id)
		जाओ निकास;

	अगर (usb_drv->probe != शून्य) अणु
		error = driver_create_file(&usb_drv->drvwrap.driver,
					   &driver_attr_new_id);
		अगर (error == 0) अणु
			error = driver_create_file(&usb_drv->drvwrap.driver,
					&driver_attr_हटाओ_id);
			अगर (error)
				driver_हटाओ_file(&usb_drv->drvwrap.driver,
						&driver_attr_new_id);
		पूर्ण
	पूर्ण
निकास:
	वापस error;
पूर्ण

अटल व्योम usb_हटाओ_newid_files(काष्ठा usb_driver *usb_drv)
अणु
	अगर (usb_drv->no_dynamic_id)
		वापस;

	अगर (usb_drv->probe != शून्य) अणु
		driver_हटाओ_file(&usb_drv->drvwrap.driver,
				&driver_attr_हटाओ_id);
		driver_हटाओ_file(&usb_drv->drvwrap.driver,
				   &driver_attr_new_id);
	पूर्ण
पूर्ण

अटल व्योम usb_मुक्त_dynids(काष्ठा usb_driver *usb_drv)
अणु
	काष्ठा usb_dynid *dynid, *n;

	spin_lock(&usb_drv->dynids.lock);
	list_क्रम_each_entry_safe(dynid, n, &usb_drv->dynids.list, node) अणु
		list_del(&dynid->node);
		kमुक्त(dynid);
	पूर्ण
	spin_unlock(&usb_drv->dynids.lock);
पूर्ण

अटल स्थिर काष्ठा usb_device_id *usb_match_dynamic_id(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
							काष्ठा usb_driver *drv)
अणु
	काष्ठा usb_dynid *dynid;

	spin_lock(&drv->dynids.lock);
	list_क्रम_each_entry(dynid, &drv->dynids.list, node) अणु
		अगर (usb_match_one_id(पूर्णांकf, &dynid->id)) अणु
			spin_unlock(&drv->dynids.lock);
			वापस &dynid->id;
		पूर्ण
	पूर्ण
	spin_unlock(&drv->dynids.lock);
	वापस शून्य;
पूर्ण


/* called from driver core with dev locked */
अटल पूर्णांक usb_probe_device(काष्ठा device *dev)
अणु
	काष्ठा usb_device_driver *udriver = to_usb_device_driver(dev->driver);
	काष्ठा usb_device *udev = to_usb_device(dev);
	पूर्णांक error = 0;

	dev_dbg(dev, "%s\n", __func__);

	/* TODO: Add real matching code */

	/* The device should always appear to be in use
	 * unless the driver supports स्वतःsuspend.
	 */
	अगर (!udriver->supports_स्वतःsuspend)
		error = usb_स्वतःresume_device(udev);
	अगर (error)
		वापस error;

	अगर (udriver->generic_subclass)
		error = usb_generic_driver_probe(udev);
	अगर (error)
		वापस error;

	/* Probe the USB device with the driver in hand, but only
	 * defer to a generic driver in हाल the current USB
	 * device driver has an id_table or a match function; i.e.,
	 * when the device driver was explicitly matched against
	 * a device.
	 *
	 * If the device driver करोes not have either of these,
	 * then we assume that it can bind to any device and is
	 * not truly a more specialized/non-generic driver, so a
	 * वापस value of -ENODEV should not क्रमce the device
	 * to be handled by the generic USB driver, as there
	 * can still be another, more specialized, device driver.
	 *
	 * This accommodates the usbip driver.
	 *
	 * TODO: What अगर, in the future, there are multiple
	 * specialized USB device drivers क्रम a particular device?
	 * In such हालs, there is a need to try all matching
	 * specialised device drivers prior to setting the
	 * use_generic_driver bit.
	 */
	error = udriver->probe(udev);
	अगर (error == -ENODEV && udriver != &usb_generic_driver &&
	    (udriver->id_table || udriver->match)) अणु
		udev->use_generic_driver = 1;
		वापस -EPROBE_DEFER;
	पूर्ण
	वापस error;
पूर्ण

/* called from driver core with dev locked */
अटल पूर्णांक usb_unbind_device(काष्ठा device *dev)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	काष्ठा usb_device_driver *udriver = to_usb_device_driver(dev->driver);

	अगर (udriver->disconnect)
		udriver->disconnect(udev);
	अगर (udriver->generic_subclass)
		usb_generic_driver_disconnect(udev);
	अगर (!udriver->supports_स्वतःsuspend)
		usb_स्वतःsuspend_device(udev);
	वापस 0;
पूर्ण

/* called from driver core with dev locked */
अटल पूर्णांक usb_probe_पूर्णांकerface(काष्ठा device *dev)
अणु
	काष्ठा usb_driver *driver = to_usb_driver(dev->driver);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	स्थिर काष्ठा usb_device_id *id;
	पूर्णांक error = -ENODEV;
	पूर्णांक lpm_disable_error = -ENODEV;

	dev_dbg(dev, "%s\n", __func__);

	पूर्णांकf->needs_binding = 0;

	अगर (usb_device_is_owned(udev))
		वापस error;

	अगर (udev->authorized == 0) अणु
		dev_err(&पूर्णांकf->dev, "Device is not authorized for usage\n");
		वापस error;
	पूर्ण अन्यथा अगर (पूर्णांकf->authorized == 0) अणु
		dev_err(&पूर्णांकf->dev, "Interface %d is not authorized for usage\n",
				पूर्णांकf->altsetting->desc.bInterfaceNumber);
		वापस error;
	पूर्ण

	id = usb_match_dynamic_id(पूर्णांकf, driver);
	अगर (!id)
		id = usb_match_id(पूर्णांकf, driver->id_table);
	अगर (!id)
		वापस error;

	dev_dbg(dev, "%s - got id\n", __func__);

	error = usb_स्वतःresume_device(udev);
	अगर (error)
		वापस error;

	पूर्णांकf->condition = USB_INTERFACE_BINDING;

	/* Probed पूर्णांकerfaces are initially active.  They are
	 * runसमय-PM-enabled only अगर the driver has स्वतःsuspend support.
	 * They are sensitive to their children's घातer states.
	 */
	pm_runसमय_set_active(dev);
	pm_suspend_ignore_children(dev, false);
	अगर (driver->supports_स्वतःsuspend)
		pm_runसमय_enable(dev);

	/* If the new driver करोesn't allow hub-initiated LPM, and we can't
	 * disable hub-initiated LPM, then fail the probe.
	 *
	 * Otherwise, leaving LPM enabled should be harmless, because the
	 * endpoपूर्णांक पूर्णांकervals should reमुख्य the same, and the U1/U2 समयouts
	 * should reमुख्य the same.
	 *
	 * If we need to install alt setting 0 beक्रमe probe, or another alt
	 * setting during probe, that should also be fine.  usb_set_पूर्णांकerface()
	 * will attempt to disable LPM, and fail अगर it can't disable it.
	 */
	अगर (driver->disable_hub_initiated_lpm) अणु
		lpm_disable_error = usb_unlocked_disable_lpm(udev);
		अगर (lpm_disable_error) अणु
			dev_err(&पूर्णांकf->dev, "%s Failed to disable LPM for driver %s\n",
				__func__, driver->name);
			error = lpm_disable_error;
			जाओ err;
		पूर्ण
	पूर्ण

	/* Carry out a deferred चयन to altsetting 0 */
	अगर (पूर्णांकf->needs_altsetting0) अणु
		error = usb_set_पूर्णांकerface(udev, पूर्णांकf->altsetting[0].
				desc.bInterfaceNumber, 0);
		अगर (error < 0)
			जाओ err;
		पूर्णांकf->needs_altsetting0 = 0;
	पूर्ण

	error = driver->probe(पूर्णांकf, id);
	अगर (error)
		जाओ err;

	पूर्णांकf->condition = USB_INTERFACE_BOUND;

	/* If the LPM disable succeeded, balance the ref counts. */
	अगर (!lpm_disable_error)
		usb_unlocked_enable_lpm(udev);

	usb_स्वतःsuspend_device(udev);
	वापस error;

 err:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	पूर्णांकf->needs_remote_wakeup = 0;
	पूर्णांकf->condition = USB_INTERFACE_UNBOUND;

	/* If the LPM disable succeeded, balance the ref counts. */
	अगर (!lpm_disable_error)
		usb_unlocked_enable_lpm(udev);

	/* Unbound पूर्णांकerfaces are always runसमय-PM-disabled and -suspended */
	अगर (driver->supports_स्वतःsuspend)
		pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);

	usb_स्वतःsuspend_device(udev);
	वापस error;
पूर्ण

/* called from driver core with dev locked */
अटल पूर्णांक usb_unbind_पूर्णांकerface(काष्ठा device *dev)
अणु
	काष्ठा usb_driver *driver = to_usb_driver(dev->driver);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_host_endpoपूर्णांक *ep, **eps = शून्य;
	काष्ठा usb_device *udev;
	पूर्णांक i, j, error, r;
	पूर्णांक lpm_disable_error = -ENODEV;

	पूर्णांकf->condition = USB_INTERFACE_UNBINDING;

	/* Autoresume क्रम set_पूर्णांकerface call below */
	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	error = usb_स्वतःresume_device(udev);

	/* If hub-initiated LPM policy may change, attempt to disable LPM until
	 * the driver is unbound.  If LPM isn't disabled, that's fine because it
	 * wouldn't be enabled unless all the bound पूर्णांकerfaces supported
	 * hub-initiated LPM.
	 */
	अगर (driver->disable_hub_initiated_lpm)
		lpm_disable_error = usb_unlocked_disable_lpm(udev);

	/*
	 * Terminate all URBs क्रम this पूर्णांकerface unless the driver
	 * supports "soft" unbinding and the device is still present.
	 */
	अगर (!driver->soft_unbind || udev->state == USB_STATE_NOTATTACHED)
		usb_disable_पूर्णांकerface(udev, पूर्णांकf, false);

	driver->disconnect(पूर्णांकf);

	/* Free streams */
	क्रम (i = 0, j = 0; i < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[i];
		अगर (ep->streams == 0)
			जारी;
		अगर (j == 0) अणु
			eps = kदो_स्मृति_array(USB_MAXENDPOINTS, माप(व्योम *),
				      GFP_KERNEL);
			अगर (!eps)
				अवरोध;
		पूर्ण
		eps[j++] = ep;
	पूर्ण
	अगर (j) अणु
		usb_मुक्त_streams(पूर्णांकf, eps, j, GFP_KERNEL);
		kमुक्त(eps);
	पूर्ण

	/* Reset other पूर्णांकerface state.
	 * We cannot करो a Set-Interface अगर the device is suspended or
	 * अगर it is prepared क्रम a प्रणाली sleep (since installing a new
	 * altsetting means creating new endpoपूर्णांक device entries).
	 * When either of these happens, defer the Set-Interface.
	 */
	अगर (पूर्णांकf->cur_altsetting->desc.bAlternateSetting == 0) अणु
		/* Alपढ़ोy in altsetting 0 so skip Set-Interface.
		 * Just re-enable it without affecting the endpoपूर्णांक toggles.
		 */
		usb_enable_पूर्णांकerface(udev, पूर्णांकf, false);
	पूर्ण अन्यथा अगर (!error && !पूर्णांकf->dev.घातer.is_prepared) अणु
		r = usb_set_पूर्णांकerface(udev, पूर्णांकf->altsetting[0].
				desc.bInterfaceNumber, 0);
		अगर (r < 0)
			पूर्णांकf->needs_altsetting0 = 1;
	पूर्ण अन्यथा अणु
		पूर्णांकf->needs_altsetting0 = 1;
	पूर्ण
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	पूर्णांकf->condition = USB_INTERFACE_UNBOUND;
	पूर्णांकf->needs_remote_wakeup = 0;

	/* Attempt to re-enable USB3 LPM, अगर the disable succeeded. */
	अगर (!lpm_disable_error)
		usb_unlocked_enable_lpm(udev);

	/* Unbound पूर्णांकerfaces are always runसमय-PM-disabled and -suspended */
	अगर (driver->supports_स्वतःsuspend)
		pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);

	अगर (!error)
		usb_स्वतःsuspend_device(udev);

	वापस 0;
पूर्ण

/**
 * usb_driver_claim_पूर्णांकerface - bind a driver to an पूर्णांकerface
 * @driver: the driver to be bound
 * @अगरace: the पूर्णांकerface to which it will be bound; must be in the
 *	usb device's active configuration
 * @data: driver data associated with that पूर्णांकerface
 *
 * This is used by usb device drivers that need to claim more than one
 * पूर्णांकerface on a device when probing (audio and acm are current examples).
 * No device driver should directly modअगरy पूर्णांकernal usb_पूर्णांकerface or
 * usb_device काष्ठाure members.
 *
 * Callers must own the device lock, so driver probe() entries करोn't need
 * extra locking, but other call contexts may need to explicitly claim that
 * lock.
 *
 * Return: 0 on success.
 */
पूर्णांक usb_driver_claim_पूर्णांकerface(काष्ठा usb_driver *driver,
				काष्ठा usb_पूर्णांकerface *अगरace, व्योम *data)
अणु
	काष्ठा device *dev;
	पूर्णांक retval = 0;

	अगर (!अगरace)
		वापस -ENODEV;

	dev = &अगरace->dev;
	अगर (dev->driver)
		वापस -EBUSY;

	/* reject claim अगर पूर्णांकerface is not authorized */
	अगर (!अगरace->authorized)
		वापस -ENODEV;

	dev->driver = &driver->drvwrap.driver;
	usb_set_पूर्णांकfdata(अगरace, data);
	अगरace->needs_binding = 0;

	अगरace->condition = USB_INTERFACE_BOUND;

	/* Claimed पूर्णांकerfaces are initially inactive (suspended) and
	 * runसमय-PM-enabled, but only अगर the driver has स्वतःsuspend
	 * support.  Otherwise they are marked active, to prevent the
	 * device from being स्वतःsuspended, but left disabled.  In either
	 * हाल they are sensitive to their children's घातer states.
	 */
	pm_suspend_ignore_children(dev, false);
	अगर (driver->supports_स्वतःsuspend)
		pm_runसमय_enable(dev);
	अन्यथा
		pm_runसमय_set_active(dev);

	/* अगर पूर्णांकerface was alपढ़ोy added, bind now; अन्यथा let
	 * the future device_add() bind it, bypassing probe()
	 */
	अगर (device_is_रेजिस्टरed(dev))
		retval = device_bind_driver(dev);

	अगर (retval) अणु
		dev->driver = शून्य;
		usb_set_पूर्णांकfdata(अगरace, शून्य);
		अगरace->needs_remote_wakeup = 0;
		अगरace->condition = USB_INTERFACE_UNBOUND;

		/*
		 * Unbound पूर्णांकerfaces are always runसमय-PM-disabled
		 * and runसमय-PM-suspended
		 */
		अगर (driver->supports_स्वतःsuspend)
			pm_runसमय_disable(dev);
		pm_runसमय_set_suspended(dev);
	पूर्ण

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(usb_driver_claim_पूर्णांकerface);

/**
 * usb_driver_release_पूर्णांकerface - unbind a driver from an पूर्णांकerface
 * @driver: the driver to be unbound
 * @अगरace: the पूर्णांकerface from which it will be unbound
 *
 * This can be used by drivers to release an पूर्णांकerface without रुकोing
 * क्रम their disconnect() methods to be called.  In typical हालs this
 * also causes the driver disconnect() method to be called.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 * Callers must own the device lock, so driver disconnect() entries करोn't
 * need extra locking, but other call contexts may need to explicitly claim
 * that lock.
 */
व्योम usb_driver_release_पूर्णांकerface(काष्ठा usb_driver *driver,
					काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा device *dev = &अगरace->dev;

	/* this should never happen, करोn't release something that's not ours */
	अगर (!dev->driver || dev->driver != &driver->drvwrap.driver)
		वापस;

	/* करोn't release from within disconnect() */
	अगर (अगरace->condition != USB_INTERFACE_BOUND)
		वापस;
	अगरace->condition = USB_INTERFACE_UNBINDING;

	/* Release via the driver core only अगर the पूर्णांकerface
	 * has alपढ़ोy been रेजिस्टरed
	 */
	अगर (device_is_रेजिस्टरed(dev)) अणु
		device_release_driver(dev);
	पूर्ण अन्यथा अणु
		device_lock(dev);
		usb_unbind_पूर्णांकerface(dev);
		dev->driver = शून्य;
		device_unlock(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_driver_release_पूर्णांकerface);

/* वापसs 0 अगर no match, 1 अगर match */
पूर्णांक usb_match_device(काष्ठा usb_device *dev, स्थिर काष्ठा usb_device_id *id)
अणु
	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_VENDOR) &&
	    id->idVenकरोr != le16_to_cpu(dev->descriptor.idVenकरोr))
		वापस 0;

	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_PRODUCT) &&
	    id->idProduct != le16_to_cpu(dev->descriptor.idProduct))
		वापस 0;

	/* No need to test id->bcdDevice_lo != 0, since 0 is never
	   greater than any अचिन्हित number. */
	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_LO) &&
	    (id->bcdDevice_lo > le16_to_cpu(dev->descriptor.bcdDevice)))
		वापस 0;

	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_HI) &&
	    (id->bcdDevice_hi < le16_to_cpu(dev->descriptor.bcdDevice)))
		वापस 0;

	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_CLASS) &&
	    (id->bDeviceClass != dev->descriptor.bDeviceClass))
		वापस 0;

	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_SUBCLASS) &&
	    (id->bDeviceSubClass != dev->descriptor.bDeviceSubClass))
		वापस 0;

	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_PROTOCOL) &&
	    (id->bDeviceProtocol != dev->descriptor.bDeviceProtocol))
		वापस 0;

	वापस 1;
पूर्ण

/* वापसs 0 अगर no match, 1 अगर match */
पूर्णांक usb_match_one_id_पूर्णांकf(काष्ठा usb_device *dev,
			  काष्ठा usb_host_पूर्णांकerface *पूर्णांकf,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	/* The पूर्णांकerface class, subclass, protocol and number should never be
	 * checked क्रम a match अगर the device class is Venकरोr Specअगरic,
	 * unless the match record specअगरies the Venकरोr ID. */
	अगर (dev->descriptor.bDeviceClass == USB_CLASS_VENDOR_SPEC &&
			!(id->match_flags & USB_DEVICE_ID_MATCH_VENDOR) &&
			(id->match_flags & (USB_DEVICE_ID_MATCH_INT_CLASS |
				USB_DEVICE_ID_MATCH_INT_SUBCLASS |
				USB_DEVICE_ID_MATCH_INT_PROTOCOL |
				USB_DEVICE_ID_MATCH_INT_NUMBER)))
		वापस 0;

	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_INT_CLASS) &&
	    (id->bInterfaceClass != पूर्णांकf->desc.bInterfaceClass))
		वापस 0;

	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_INT_SUBCLASS) &&
	    (id->bInterfaceSubClass != पूर्णांकf->desc.bInterfaceSubClass))
		वापस 0;

	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_INT_PROTOCOL) &&
	    (id->bInterfaceProtocol != पूर्णांकf->desc.bInterfaceProtocol))
		वापस 0;

	अगर ((id->match_flags & USB_DEVICE_ID_MATCH_INT_NUMBER) &&
	    (id->bInterfaceNumber != पूर्णांकf->desc.bInterfaceNumber))
		वापस 0;

	वापस 1;
पूर्ण

/* वापसs 0 अगर no match, 1 अगर match */
पूर्णांक usb_match_one_id(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_device *dev;

	/* proc_connectinfo in devio.c may call us with id == शून्य. */
	अगर (id == शून्य)
		वापस 0;

	पूर्णांकf = पूर्णांकerface->cur_altsetting;
	dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	अगर (!usb_match_device(dev, id))
		वापस 0;

	वापस usb_match_one_id_पूर्णांकf(dev, पूर्णांकf, id);
पूर्ण
EXPORT_SYMBOL_GPL(usb_match_one_id);

/**
 * usb_match_id - find first usb_device_id matching device or पूर्णांकerface
 * @पूर्णांकerface: the पूर्णांकerface of पूर्णांकerest
 * @id: array of usb_device_id काष्ठाures, terminated by zero entry
 *
 * usb_match_id searches an array of usb_device_id's and वापसs
 * the first one matching the device or पूर्णांकerface, or null.
 * This is used when binding (or rebinding) a driver to an पूर्णांकerface.
 * Most USB device drivers will use this indirectly, through the usb core,
 * but some layered driver frameworks use it directly.
 * These device tables are exported with MODULE_DEVICE_TABLE, through
 * modutils, to support the driver loading functionality of USB hotplugging.
 *
 * Return: The first matching usb_device_id, or %शून्य.
 *
 * What Matches:
 *
 * The "match_flags" element in a usb_device_id controls which
 * members are used.  If the corresponding bit is set, the
 * value in the device_id must match its corresponding member
 * in the device or पूर्णांकerface descriptor, or अन्यथा the device_id
 * करोes not match.
 *
 * "driver_info" is normally used only by device drivers,
 * but you can create a wildcard "matches anything" usb_device_id
 * as a driver's "modules.usbmap" entry अगर you provide an id with
 * only a nonzero "driver_info" field.  If you करो this, the USB device
 * driver's probe() routine should use additional पूर्णांकelligence to
 * decide whether to bind to the specअगरied पूर्णांकerface.
 *
 * What Makes Good usb_device_id Tables:
 *
 * The match algorithm is very simple, so that पूर्णांकelligence in
 * driver selection must come from smart driver id records.
 * Unless you have good reasons to use another selection policy,
 * provide match elements only in related groups, and order match
 * specअगरiers from specअगरic to general.  Use the macros provided
 * क्रम that purpose अगर you can.
 *
 * The most specअगरic match specअगरiers use device descriptor
 * data.  These are commonly used with product-specअगरic matches;
 * the USB_DEVICE macro lets you provide venकरोr and product IDs,
 * and you can also match against ranges of product revisions.
 * These are widely used क्रम devices with application or venकरोr
 * specअगरic bDeviceClass values.
 *
 * Matches based on device class/subclass/protocol specअगरications
 * are slightly more general; use the USB_DEVICE_INFO macro, or
 * its siblings.  These are used with single-function devices
 * where bDeviceClass करोesn't specअगरy that each पूर्णांकerface has
 * its own class.
 *
 * Matches based on पूर्णांकerface class/subclass/protocol are the
 * most general; they let drivers bind to any पूर्णांकerface on a
 * multiple-function device.  Use the USB_INTERFACE_INFO
 * macro, or its siblings, to match class-per-पूर्णांकerface style
 * devices (as recorded in bInterfaceClass).
 *
 * Note that an entry created by USB_INTERFACE_INFO won't match
 * any पूर्णांकerface अगर the device class is set to Venकरोr-Specअगरic.
 * This is deliberate; according to the USB spec the meanings of
 * the पूर्णांकerface class/subclass/protocol क्रम these devices are also
 * venकरोr-specअगरic, and hence matching against a standard product
 * class wouldn't work anyway.  If you really want to use an
 * पूर्णांकerface-based match क्रम such a device, create a match record
 * that also specअगरies the venकरोr ID.  (Unक्रमunately there isn't a
 * standard macro क्रम creating records like this.)
 *
 * Within those groups, remember that not all combinations are
 * meaningful.  For example, करोn't give a product version range
 * without venकरोr and product IDs; or specअगरy a protocol without
 * its associated class and subclass.
 */
स्थिर काष्ठा usb_device_id *usb_match_id(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
					 स्थिर काष्ठा usb_device_id *id)
अणु
	/* proc_connectinfo in devio.c may call us with id == शून्य. */
	अगर (id == शून्य)
		वापस शून्य;

	/* It is important to check that id->driver_info is nonzero,
	   since an entry that is all zeroes except क्रम a nonzero
	   id->driver_info is the way to create an entry that
	   indicates that the driver want to examine every
	   device and पूर्णांकerface. */
	क्रम (; id->idVenकरोr || id->idProduct || id->bDeviceClass ||
	       id->bInterfaceClass || id->driver_info; id++) अणु
		अगर (usb_match_one_id(पूर्णांकerface, id))
			वापस id;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_match_id);

स्थिर काष्ठा usb_device_id *usb_device_match_id(काष्ठा usb_device *udev,
				स्थिर काष्ठा usb_device_id *id)
अणु
	अगर (!id)
		वापस शून्य;

	क्रम (; id->idVenकरोr || id->idProduct ; id++) अणु
		अगर (usb_match_device(udev, id))
			वापस id;
	पूर्ण

	वापस शून्य;
पूर्ण

bool usb_driver_applicable(काष्ठा usb_device *udev,
			   काष्ठा usb_device_driver *udrv)
अणु
	अगर (udrv->id_table && udrv->match)
		वापस usb_device_match_id(udev, udrv->id_table) != शून्य &&
		       udrv->match(udev);

	अगर (udrv->id_table)
		वापस usb_device_match_id(udev, udrv->id_table) != शून्य;

	अगर (udrv->match)
		वापस udrv->match(udev);

	वापस false;
पूर्ण

अटल पूर्णांक usb_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	/* devices and पूर्णांकerfaces are handled separately */
	अगर (is_usb_device(dev)) अणु
		काष्ठा usb_device *udev;
		काष्ठा usb_device_driver *udrv;

		/* पूर्णांकerface drivers never match devices */
		अगर (!is_usb_device_driver(drv))
			वापस 0;

		udev = to_usb_device(dev);
		udrv = to_usb_device_driver(drv);

		/* If the device driver under consideration करोes not have a
		 * id_table or a match function, then let the driver's probe
		 * function decide.
		 */
		अगर (!udrv->id_table && !udrv->match)
			वापस 1;

		वापस usb_driver_applicable(udev, udrv);

	पूर्ण अन्यथा अगर (is_usb_पूर्णांकerface(dev)) अणु
		काष्ठा usb_पूर्णांकerface *पूर्णांकf;
		काष्ठा usb_driver *usb_drv;
		स्थिर काष्ठा usb_device_id *id;

		/* device drivers never match पूर्णांकerfaces */
		अगर (is_usb_device_driver(drv))
			वापस 0;

		पूर्णांकf = to_usb_पूर्णांकerface(dev);
		usb_drv = to_usb_driver(drv);

		id = usb_match_id(पूर्णांकf, usb_drv->id_table);
		अगर (id)
			वापस 1;

		id = usb_match_dynamic_id(पूर्णांकf, usb_drv);
		अगर (id)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usb_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा usb_device *usb_dev;

	अगर (is_usb_device(dev)) अणु
		usb_dev = to_usb_device(dev);
	पूर्ण अन्यथा अगर (is_usb_पूर्णांकerface(dev)) अणु
		काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);

		usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	अगर (usb_dev->devnum < 0) अणु
		/* driver is often null here; dev_dbg() would oops */
		pr_debug("usb %s: already deleted?\n", dev_name(dev));
		वापस -ENODEV;
	पूर्ण
	अगर (!usb_dev->bus) अणु
		pr_debug("usb %s: bus removed?\n", dev_name(dev));
		वापस -ENODEV;
	पूर्ण

	/* per-device configurations are common */
	अगर (add_uevent_var(env, "PRODUCT=%x/%x/%x",
			   le16_to_cpu(usb_dev->descriptor.idVenकरोr),
			   le16_to_cpu(usb_dev->descriptor.idProduct),
			   le16_to_cpu(usb_dev->descriptor.bcdDevice)))
		वापस -ENOMEM;

	/* class-based driver binding models */
	अगर (add_uevent_var(env, "TYPE=%d/%d/%d",
			   usb_dev->descriptor.bDeviceClass,
			   usb_dev->descriptor.bDeviceSubClass,
			   usb_dev->descriptor.bDeviceProtocol))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक __usb_bus_reprobe_drivers(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा usb_device_driver *new_udriver = data;
	काष्ठा usb_device *udev;
	पूर्णांक ret;

	/* Don't reprobe if current driver isn't usb_generic_driver */
	अगर (dev->driver != &usb_generic_driver.drvwrap.driver)
		वापस 0;

	udev = to_usb_device(dev);
	अगर (!usb_driver_applicable(udev, new_udriver))
		वापस 0;

	ret = device_reprobe(dev);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(dev, "Failed to reprobe device (error %d)\n", ret);

	वापस 0;
पूर्ण

/**
 * usb_रेजिस्टर_device_driver - रेजिस्टर a USB device (not पूर्णांकerface) driver
 * @new_udriver: USB operations क्रम the device driver
 * @owner: module owner of this driver.
 *
 * Registers a USB device driver with the USB core.  The list of
 * unattached devices will be rescanned whenever a new driver is
 * added, allowing the new driver to attach to any recognized devices.
 *
 * Return: A negative error code on failure and 0 on success.
 */
पूर्णांक usb_रेजिस्टर_device_driver(काष्ठा usb_device_driver *new_udriver,
		काष्ठा module *owner)
अणु
	पूर्णांक retval = 0;

	अगर (usb_disabled())
		वापस -ENODEV;

	new_udriver->drvwrap.क्रम_devices = 1;
	new_udriver->drvwrap.driver.name = new_udriver->name;
	new_udriver->drvwrap.driver.bus = &usb_bus_type;
	new_udriver->drvwrap.driver.probe = usb_probe_device;
	new_udriver->drvwrap.driver.हटाओ = usb_unbind_device;
	new_udriver->drvwrap.driver.owner = owner;
	new_udriver->drvwrap.driver.dev_groups = new_udriver->dev_groups;

	retval = driver_रेजिस्टर(&new_udriver->drvwrap.driver);

	अगर (!retval) अणु
		pr_info("%s: registered new device driver %s\n",
			usbcore_name, new_udriver->name);
		/*
		 * Check whether any device could be better served with
		 * this new driver
		 */
		bus_क्रम_each_dev(&usb_bus_type, शून्य, new_udriver,
				 __usb_bus_reprobe_drivers);
	पूर्ण अन्यथा अणु
		pr_err("%s: error %d registering device driver %s\n",
			usbcore_name, retval, new_udriver->name);
	पूर्ण

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(usb_रेजिस्टर_device_driver);

/**
 * usb_deरेजिस्टर_device_driver - unरेजिस्टर a USB device (not पूर्णांकerface) driver
 * @udriver: USB operations of the device driver to unरेजिस्टर
 * Context: must be able to sleep
 *
 * Unlinks the specअगरied driver from the पूर्णांकernal USB driver list.
 */
व्योम usb_deरेजिस्टर_device_driver(काष्ठा usb_device_driver *udriver)
अणु
	pr_info("%s: deregistering device driver %s\n",
			usbcore_name, udriver->name);

	driver_unरेजिस्टर(&udriver->drvwrap.driver);
पूर्ण
EXPORT_SYMBOL_GPL(usb_deरेजिस्टर_device_driver);

/**
 * usb_रेजिस्टर_driver - रेजिस्टर a USB पूर्णांकerface driver
 * @new_driver: USB operations क्रम the पूर्णांकerface driver
 * @owner: module owner of this driver.
 * @mod_name: module name string
 *
 * Registers a USB पूर्णांकerface driver with the USB core.  The list of
 * unattached पूर्णांकerfaces will be rescanned whenever a new driver is
 * added, allowing the new driver to attach to any recognized पूर्णांकerfaces.
 *
 * Return: A negative error code on failure and 0 on success.
 *
 * NOTE: अगर you want your driver to use the USB major number, you must call
 * usb_रेजिस्टर_dev() to enable that functionality.  This function no दीर्घer
 * takes care of that.
 */
पूर्णांक usb_रेजिस्टर_driver(काष्ठा usb_driver *new_driver, काष्ठा module *owner,
			स्थिर अक्षर *mod_name)
अणु
	पूर्णांक retval = 0;

	अगर (usb_disabled())
		वापस -ENODEV;

	new_driver->drvwrap.क्रम_devices = 0;
	new_driver->drvwrap.driver.name = new_driver->name;
	new_driver->drvwrap.driver.bus = &usb_bus_type;
	new_driver->drvwrap.driver.probe = usb_probe_पूर्णांकerface;
	new_driver->drvwrap.driver.हटाओ = usb_unbind_पूर्णांकerface;
	new_driver->drvwrap.driver.owner = owner;
	new_driver->drvwrap.driver.mod_name = mod_name;
	new_driver->drvwrap.driver.dev_groups = new_driver->dev_groups;
	spin_lock_init(&new_driver->dynids.lock);
	INIT_LIST_HEAD(&new_driver->dynids.list);

	retval = driver_रेजिस्टर(&new_driver->drvwrap.driver);
	अगर (retval)
		जाओ out;

	retval = usb_create_newid_files(new_driver);
	अगर (retval)
		जाओ out_newid;

	pr_info("%s: registered new interface driver %s\n",
			usbcore_name, new_driver->name);

out:
	वापस retval;

out_newid:
	driver_unरेजिस्टर(&new_driver->drvwrap.driver);

	pr_err("%s: error %d registering interface driver %s\n",
		usbcore_name, retval, new_driver->name);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(usb_रेजिस्टर_driver);

/**
 * usb_deरेजिस्टर - unरेजिस्टर a USB पूर्णांकerface driver
 * @driver: USB operations of the पूर्णांकerface driver to unरेजिस्टर
 * Context: must be able to sleep
 *
 * Unlinks the specअगरied driver from the पूर्णांकernal USB driver list.
 *
 * NOTE: If you called usb_रेजिस्टर_dev(), you still need to call
 * usb_deरेजिस्टर_dev() to clean up your driver's allocated minor numbers,
 * this * call will no दीर्घer करो it क्रम you.
 */
व्योम usb_deरेजिस्टर(काष्ठा usb_driver *driver)
अणु
	pr_info("%s: deregistering interface driver %s\n",
			usbcore_name, driver->name);

	usb_हटाओ_newid_files(driver);
	driver_unरेजिस्टर(&driver->drvwrap.driver);
	usb_मुक्त_dynids(driver);
पूर्ण
EXPORT_SYMBOL_GPL(usb_deरेजिस्टर);

/* Forced unbinding of a USB पूर्णांकerface driver, either because
 * it करोesn't support pre_reset/post_reset/reset_resume or
 * because it करोesn't support suspend/resume.
 *
 * The caller must hold @पूर्णांकf's device's lock, but not @intf's lock.
 */
व्योम usb_क्रमced_unbind_पूर्णांकf(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_driver *driver = to_usb_driver(पूर्णांकf->dev.driver);

	dev_dbg(&पूर्णांकf->dev, "forced unbind\n");
	usb_driver_release_पूर्णांकerface(driver, पूर्णांकf);

	/* Mark the पूर्णांकerface क्रम later rebinding */
	पूर्णांकf->needs_binding = 1;
पूर्ण

/*
 * Unbind drivers क्रम @udev's marked पूर्णांकerfaces.  These पूर्णांकerfaces have
 * the needs_binding flag set, क्रम example by usb_resume_पूर्णांकerface().
 *
 * The caller must hold @udev's device lock.
 */
अटल व्योम unbind_marked_पूर्णांकerfaces(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_host_config	*config;
	पूर्णांक			i;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;

	config = udev->actconfig;
	अगर (config) अणु
		क्रम (i = 0; i < config->desc.bNumInterfaces; ++i) अणु
			पूर्णांकf = config->पूर्णांकerface[i];
			अगर (पूर्णांकf->dev.driver && पूर्णांकf->needs_binding)
				usb_क्रमced_unbind_पूर्णांकf(पूर्णांकf);
		पूर्ण
	पूर्ण
पूर्ण

/* Delayed क्रमced unbinding of a USB पूर्णांकerface driver and scan
 * क्रम rebinding.
 *
 * The caller must hold @पूर्णांकf's device's lock, but not @intf's lock.
 *
 * Note: Rebinds will be skipped अगर a प्रणाली sleep transition is in
 * progress and the PM "complete" callback hasn't occurred yet.
 */
अटल व्योम usb_rebind_पूर्णांकf(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक rc;

	/* Delayed unbind of an existing driver */
	अगर (पूर्णांकf->dev.driver)
		usb_क्रमced_unbind_पूर्णांकf(पूर्णांकf);

	/* Try to rebind the पूर्णांकerface */
	अगर (!पूर्णांकf->dev.घातer.is_prepared) अणु
		पूर्णांकf->needs_binding = 0;
		rc = device_attach(&पूर्णांकf->dev);
		अगर (rc < 0 && rc != -EPROBE_DEFER)
			dev_warn(&पूर्णांकf->dev, "rebind failed: %d\n", rc);
	पूर्ण
पूर्ण

/*
 * Rebind drivers to @udev's marked पूर्णांकerfaces.  These पूर्णांकerfaces have
 * the needs_binding flag set.
 *
 * The caller must hold @udev's device lock.
 */
अटल व्योम rebind_marked_पूर्णांकerfaces(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_host_config	*config;
	पूर्णांक			i;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;

	config = udev->actconfig;
	अगर (config) अणु
		क्रम (i = 0; i < config->desc.bNumInterfaces; ++i) अणु
			पूर्णांकf = config->पूर्णांकerface[i];
			अगर (पूर्णांकf->needs_binding)
				usb_rebind_पूर्णांकf(पूर्णांकf);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Unbind all of @udev's marked पूर्णांकerfaces and then rebind all of them.
 * This ordering is necessary because some drivers claim several पूर्णांकerfaces
 * when they are first probed.
 *
 * The caller must hold @udev's device lock.
 */
व्योम usb_unbind_and_rebind_marked_पूर्णांकerfaces(काष्ठा usb_device *udev)
अणु
	unbind_marked_पूर्णांकerfaces(udev);
	rebind_marked_पूर्णांकerfaces(udev);
पूर्ण

#अगर_घोषित CONFIG_PM

/* Unbind drivers क्रम @udev's interfaces that don't support suspend/resume
 * There is no check क्रम reset_resume here because it can be determined
 * only during resume whether reset_resume is needed.
 *
 * The caller must hold @udev's device lock.
 */
अटल व्योम unbind_no_pm_drivers_पूर्णांकerfaces(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_host_config	*config;
	पूर्णांक			i;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;
	काष्ठा usb_driver	*drv;

	config = udev->actconfig;
	अगर (config) अणु
		क्रम (i = 0; i < config->desc.bNumInterfaces; ++i) अणु
			पूर्णांकf = config->पूर्णांकerface[i];

			अगर (पूर्णांकf->dev.driver) अणु
				drv = to_usb_driver(पूर्णांकf->dev.driver);
				अगर (!drv->suspend || !drv->resume)
					usb_क्रमced_unbind_पूर्णांकf(पूर्णांकf);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक usb_suspend_device(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	काष्ठा usb_device_driver	*udriver;
	पूर्णांक				status = 0;

	अगर (udev->state == USB_STATE_NOTATTACHED ||
			udev->state == USB_STATE_SUSPENDED)
		जाओ करोne;

	/* For devices that करोn't have a driver, we करो a generic suspend. */
	अगर (udev->dev.driver)
		udriver = to_usb_device_driver(udev->dev.driver);
	अन्यथा अणु
		udev->करो_remote_wakeup = 0;
		udriver = &usb_generic_driver;
	पूर्ण
	अगर (udriver->suspend)
		status = udriver->suspend(udev, msg);
	अगर (status == 0 && udriver->generic_subclass)
		status = usb_generic_driver_suspend(udev, msg);

 करोne:
	dev_vdbg(&udev->dev, "%s: status %d\n", __func__, status);
	वापस status;
पूर्ण

अटल पूर्णांक usb_resume_device(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	काष्ठा usb_device_driver	*udriver;
	पूर्णांक				status = 0;

	अगर (udev->state == USB_STATE_NOTATTACHED)
		जाओ करोne;

	/* Can't resume it if it doesn't have a driver. */
	अगर (udev->dev.driver == शून्य) अणु
		status = -ENOTCONN;
		जाओ करोne;
	पूर्ण

	/* Non-root devices on a full/low-speed bus must रुको क्रम their
	 * companion high-speed root hub, in हाल a hanकरोff is needed.
	 */
	अगर (!PMSG_IS_AUTO(msg) && udev->parent && udev->bus->hs_companion)
		device_pm_रुको_क्रम_dev(&udev->dev,
				&udev->bus->hs_companion->root_hub->dev);

	अगर (udev->quirks & USB_QUIRK_RESET_RESUME)
		udev->reset_resume = 1;

	udriver = to_usb_device_driver(udev->dev.driver);
	अगर (udriver->generic_subclass)
		status = usb_generic_driver_resume(udev, msg);
	अगर (status == 0 && udriver->resume)
		status = udriver->resume(udev, msg);

 करोne:
	dev_vdbg(&udev->dev, "%s: status %d\n", __func__, status);
	वापस status;
पूर्ण

अटल पूर्णांक usb_suspend_पूर्णांकerface(काष्ठा usb_device *udev,
		काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t msg)
अणु
	काष्ठा usb_driver	*driver;
	पूर्णांक			status = 0;

	अगर (udev->state == USB_STATE_NOTATTACHED ||
			पूर्णांकf->condition == USB_INTERFACE_UNBOUND)
		जाओ करोne;
	driver = to_usb_driver(पूर्णांकf->dev.driver);

	/* at this समय we know the driver supports suspend */
	status = driver->suspend(पूर्णांकf, msg);
	अगर (status && !PMSG_IS_AUTO(msg))
		dev_err(&पूर्णांकf->dev, "suspend error %d\n", status);

 करोne:
	dev_vdbg(&पूर्णांकf->dev, "%s: status %d\n", __func__, status);
	वापस status;
पूर्ण

अटल पूर्णांक usb_resume_पूर्णांकerface(काष्ठा usb_device *udev,
		काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t msg, पूर्णांक reset_resume)
अणु
	काष्ठा usb_driver	*driver;
	पूर्णांक			status = 0;

	अगर (udev->state == USB_STATE_NOTATTACHED)
		जाओ करोne;

	/* Don't let स्वतःresume पूर्णांकerfere with unbinding */
	अगर (पूर्णांकf->condition == USB_INTERFACE_UNBINDING)
		जाओ करोne;

	/* Can't resume it if it doesn't have a driver. */
	अगर (पूर्णांकf->condition == USB_INTERFACE_UNBOUND) अणु

		/* Carry out a deferred चयन to altsetting 0 */
		अगर (पूर्णांकf->needs_altsetting0 && !पूर्णांकf->dev.घातer.is_prepared) अणु
			usb_set_पूर्णांकerface(udev, पूर्णांकf->altsetting[0].
					desc.bInterfaceNumber, 0);
			पूर्णांकf->needs_altsetting0 = 0;
		पूर्ण
		जाओ करोne;
	पूर्ण

	/* Don't resume अगर the पूर्णांकerface is marked क्रम rebinding */
	अगर (पूर्णांकf->needs_binding)
		जाओ करोne;
	driver = to_usb_driver(पूर्णांकf->dev.driver);

	अगर (reset_resume) अणु
		अगर (driver->reset_resume) अणु
			status = driver->reset_resume(पूर्णांकf);
			अगर (status)
				dev_err(&पूर्णांकf->dev, "%s error %d\n",
						"reset_resume", status);
		पूर्ण अन्यथा अणु
			पूर्णांकf->needs_binding = 1;
			dev_dbg(&पूर्णांकf->dev, "no reset_resume for driver %s?\n",
					driver->name);
		पूर्ण
	पूर्ण अन्यथा अणु
		status = driver->resume(पूर्णांकf);
		अगर (status)
			dev_err(&पूर्णांकf->dev, "resume error %d\n", status);
	पूर्ण

करोne:
	dev_vdbg(&पूर्णांकf->dev, "%s: status %d\n", __func__, status);

	/* Later we will unbind the driver and/or reprobe, अगर necessary */
	वापस status;
पूर्ण

/**
 * usb_suspend_both - suspend a USB device and its पूर्णांकerfaces
 * @udev: the usb_device to suspend
 * @msg: Power Management message describing this state transition
 *
 * This is the central routine क्रम suspending USB devices.  It calls the
 * suspend methods क्रम all the पूर्णांकerface drivers in @udev and then calls
 * the suspend method क्रम @udev itself.  When the routine is called in
 * स्वतःsuspend, अगर an error occurs at any stage, all the पूर्णांकerfaces
 * which were suspended are resumed so that they reमुख्य in the same
 * state as the device, but when called from प्रणाली sleep, all error
 * from suspend methods of पूर्णांकerfaces and the non-root-hub device itself
 * are simply ignored, so all suspended पूर्णांकerfaces are only resumed
 * to the device's state when @udev is root-hub and its suspend method
 * वापसs failure.
 *
 * Autosuspend requests originating from a child device or an पूर्णांकerface
 * driver may be made without the protection of @udev's device lock, but
 * all other suspend calls will hold the lock.  Usbcore will insure that
 * method calls करो not arrive during bind, unbind, or reset operations.
 * However drivers must be prepared to handle suspend calls arriving at
 * unpredictable बार.
 *
 * This routine can run only in process context.
 *
 * Return: 0 अगर the suspend succeeded.
 */
अटल पूर्णांक usb_suspend_both(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	पूर्णांक			status = 0;
	पूर्णांक			i = 0, n = 0;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;

	अगर (udev->state == USB_STATE_NOTATTACHED ||
			udev->state == USB_STATE_SUSPENDED)
		जाओ करोne;

	/* Suspend all the पूर्णांकerfaces and then udev itself */
	अगर (udev->actconfig) अणु
		n = udev->actconfig->desc.bNumInterfaces;
		क्रम (i = n - 1; i >= 0; --i) अणु
			पूर्णांकf = udev->actconfig->पूर्णांकerface[i];
			status = usb_suspend_पूर्णांकerface(udev, पूर्णांकf, msg);

			/* Ignore errors during प्रणाली sleep transitions */
			अगर (!PMSG_IS_AUTO(msg))
				status = 0;
			अगर (status != 0)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (status == 0) अणु
		status = usb_suspend_device(udev, msg);

		/*
		 * Ignore errors from non-root-hub devices during
		 * प्रणाली sleep transitions.  For the most part,
		 * these devices should go to low घातer anyway when
		 * the entire bus is suspended.
		 */
		अगर (udev->parent && !PMSG_IS_AUTO(msg))
			status = 0;

		/*
		 * If the device is inaccessible, करोn't try to resume
		 * suspended पूर्णांकerfaces and just वापस the error.
		 */
		अगर (status && status != -EBUSY) अणु
			पूर्णांक err;
			u16 devstat;

			err = usb_get_std_status(udev, USB_RECIP_DEVICE, 0,
						 &devstat);
			अगर (err) अणु
				dev_err(&udev->dev,
					"Failed to suspend device, error %d\n",
					status);
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	/* If the suspend failed, resume पूर्णांकerfaces that did get suspended */
	अगर (status != 0) अणु
		अगर (udev->actconfig) अणु
			msg.event ^= (PM_EVENT_SUSPEND | PM_EVENT_RESUME);
			जबतक (++i < n) अणु
				पूर्णांकf = udev->actconfig->पूर्णांकerface[i];
				usb_resume_पूर्णांकerface(udev, पूर्णांकf, msg, 0);
			पूर्ण
		पूर्ण

	/* If the suspend succeeded then prevent any more URB submissions
	 * and flush any outstanding URBs.
	 */
	पूर्ण अन्यथा अणु
		udev->can_submit = 0;
		क्रम (i = 0; i < 16; ++i) अणु
			usb_hcd_flush_endpoपूर्णांक(udev, udev->ep_out[i]);
			usb_hcd_flush_endpoपूर्णांक(udev, udev->ep_in[i]);
		पूर्ण
	पूर्ण

 करोne:
	dev_vdbg(&udev->dev, "%s: status %d\n", __func__, status);
	वापस status;
पूर्ण

/**
 * usb_resume_both - resume a USB device and its पूर्णांकerfaces
 * @udev: the usb_device to resume
 * @msg: Power Management message describing this state transition
 *
 * This is the central routine क्रम resuming USB devices.  It calls the
 * the resume method क्रम @udev and then calls the resume methods क्रम all
 * the पूर्णांकerface drivers in @udev.
 *
 * Autoresume requests originating from a child device or an पूर्णांकerface
 * driver may be made without the protection of @udev's device lock, but
 * all other resume calls will hold the lock.  Usbcore will insure that
 * method calls करो not arrive during bind, unbind, or reset operations.
 * However drivers must be prepared to handle resume calls arriving at
 * unpredictable बार.
 *
 * This routine can run only in process context.
 *
 * Return: 0 on success.
 */
अटल पूर्णांक usb_resume_both(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	पूर्णांक			status = 0;
	पूर्णांक			i;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;

	अगर (udev->state == USB_STATE_NOTATTACHED) अणु
		status = -ENODEV;
		जाओ करोne;
	पूर्ण
	udev->can_submit = 1;

	/* Resume the device */
	अगर (udev->state == USB_STATE_SUSPENDED || udev->reset_resume)
		status = usb_resume_device(udev, msg);

	/* Resume the पूर्णांकerfaces */
	अगर (status == 0 && udev->actconfig) अणु
		क्रम (i = 0; i < udev->actconfig->desc.bNumInterfaces; i++) अणु
			पूर्णांकf = udev->actconfig->पूर्णांकerface[i];
			usb_resume_पूर्णांकerface(udev, पूर्णांकf, msg,
					udev->reset_resume);
		पूर्ण
	पूर्ण
	usb_mark_last_busy(udev);

 करोne:
	dev_vdbg(&udev->dev, "%s: status %d\n", __func__, status);
	अगर (!status)
		udev->reset_resume = 0;
	वापस status;
पूर्ण

अटल व्योम choose_wakeup(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	पूर्णांक	w;

	/* Remote wakeup is needed only when we actually go to sleep.
	 * For things like FREEZE and QUIESCE, अगर the device is alपढ़ोy
	 * स्वतःsuspended then its current wakeup setting is okay.
	 */
	अगर (msg.event == PM_EVENT_FREEZE || msg.event == PM_EVENT_QUIESCE) अणु
		अगर (udev->state != USB_STATE_SUSPENDED)
			udev->करो_remote_wakeup = 0;
		वापस;
	पूर्ण

	/* Enable remote wakeup अगर it is allowed, even अगर no पूर्णांकerface drivers
	 * actually want it.
	 */
	w = device_may_wakeup(&udev->dev);

	/* If the device is स्वतःsuspended with the wrong wakeup setting,
	 * स्वतःresume now so the setting can be changed.
	 */
	अगर (udev->state == USB_STATE_SUSPENDED && w != udev->करो_remote_wakeup)
		pm_runसमय_resume(&udev->dev);
	udev->करो_remote_wakeup = w;
पूर्ण

/* The device lock is held by the PM core */
पूर्णांक usb_suspend(काष्ठा device *dev, pm_message_t msg)
अणु
	काष्ठा usb_device	*udev = to_usb_device(dev);
	पूर्णांक r;

	unbind_no_pm_drivers_पूर्णांकerfaces(udev);

	/* From now on we are sure all drivers support suspend/resume
	 * but not necessarily reset_resume()
	 * so we may still need to unbind and rebind upon resume
	 */
	choose_wakeup(udev, msg);
	r = usb_suspend_both(udev, msg);
	अगर (r)
		वापस r;

	अगर (udev->quirks & USB_QUIRK_DISCONNECT_SUSPEND)
		usb_port_disable(udev);

	वापस 0;
पूर्ण

/* The device lock is held by the PM core */
पूर्णांक usb_resume_complete(काष्ठा device *dev)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);

	/* For PM complete calls, all we करो is rebind पूर्णांकerfaces
	 * whose needs_binding flag is set
	 */
	अगर (udev->state != USB_STATE_NOTATTACHED)
		rebind_marked_पूर्णांकerfaces(udev);
	वापस 0;
पूर्ण

/* The device lock is held by the PM core */
पूर्णांक usb_resume(काष्ठा device *dev, pm_message_t msg)
अणु
	काष्ठा usb_device	*udev = to_usb_device(dev);
	पूर्णांक			status;

	/* For all calls, take the device back to full घातer and
	 * tell the PM core in हाल it was स्वतःsuspended previously.
	 * Unbind the पूर्णांकerfaces that will need rebinding later,
	 * because they fail to support reset_resume.
	 * (This can't be करोne in usb_resume_पूर्णांकerface()
	 * above because it करोesn't own the right set of locks.)
	 */
	status = usb_resume_both(udev, msg);
	अगर (status == 0) अणु
		pm_runसमय_disable(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
		unbind_marked_पूर्णांकerfaces(udev);
	पूर्ण

	/* Aव्योम PM error messages क्रम devices disconnected जबतक suspended
	 * as we'll display regular disconnect messages just a bit later.
	 */
	अगर (status == -ENODEV || status == -ESHUTDOWN)
		status = 0;
	वापस status;
पूर्ण

/**
 * usb_enable_स्वतःsuspend - allow a USB device to be स्वतःsuspended
 * @udev: the USB device which may be स्वतःsuspended
 *
 * This routine allows @udev to be स्वतःsuspended.  An स्वतःsuspend won't
 * take place until the स्वतःsuspend_delay has elapsed and all the other
 * necessary conditions are satisfied.
 *
 * The caller must hold @udev's device lock.
 */
व्योम usb_enable_स्वतःsuspend(काष्ठा usb_device *udev)
अणु
	pm_runसमय_allow(&udev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_enable_स्वतःsuspend);

/**
 * usb_disable_स्वतःsuspend - prevent a USB device from being स्वतःsuspended
 * @udev: the USB device which may not be स्वतःsuspended
 *
 * This routine prevents @udev from being स्वतःsuspended and wakes it up
 * अगर it is alपढ़ोy स्वतःsuspended.
 *
 * The caller must hold @udev's device lock.
 */
व्योम usb_disable_स्वतःsuspend(काष्ठा usb_device *udev)
अणु
	pm_runसमय_क्रमbid(&udev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_disable_स्वतःsuspend);

/**
 * usb_स्वतःsuspend_device - delayed स्वतःsuspend of a USB device and its पूर्णांकerfaces
 * @udev: the usb_device to स्वतःsuspend
 *
 * This routine should be called when a core subप्रणाली is finished using
 * @udev and wants to allow it to स्वतःsuspend.  Examples would be when
 * @udev's device file in usbfs is बंदd or after a configuration change.
 *
 * @udev's usage counter is decremented; अगर it drops to 0 and all the
 * पूर्णांकerfaces are inactive then a delayed स्वतःsuspend will be attempted.
 * The attempt may fail (see स्वतःsuspend_check()).
 *
 * The caller must hold @udev's device lock.
 *
 * This routine can run only in process context.
 */
व्योम usb_स्वतःsuspend_device(काष्ठा usb_device *udev)
अणु
	पूर्णांक	status;

	usb_mark_last_busy(udev);
	status = pm_runसमय_put_sync_स्वतःsuspend(&udev->dev);
	dev_vdbg(&udev->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_पढ़ो(&udev->dev.घातer.usage_count),
			status);
पूर्ण

/**
 * usb_स्वतःresume_device - immediately स्वतःresume a USB device and its पूर्णांकerfaces
 * @udev: the usb_device to स्वतःresume
 *
 * This routine should be called when a core subप्रणाली wants to use @udev
 * and needs to guarantee that it is not suspended.  No स्वतःsuspend will
 * occur until usb_स्वतःsuspend_device() is called.  (Note that this will
 * not prevent suspend events originating in the PM core.)  Examples would
 * be when @udev's device file in usbfs is खोलोed or when a remote-wakeup
 * request is received.
 *
 * @udev's usage counter is incremented to prevent subsequent स्वतःsuspends.
 * However अगर the स्वतःresume fails then the usage counter is re-decremented.
 *
 * The caller must hold @udev's device lock.
 *
 * This routine can run only in process context.
 *
 * Return: 0 on success. A negative error code otherwise.
 */
पूर्णांक usb_स्वतःresume_device(काष्ठा usb_device *udev)
अणु
	पूर्णांक	status;

	status = pm_runसमय_get_sync(&udev->dev);
	अगर (status < 0)
		pm_runसमय_put_sync(&udev->dev);
	dev_vdbg(&udev->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_पढ़ो(&udev->dev.घातer.usage_count),
			status);
	अगर (status > 0)
		status = 0;
	वापस status;
पूर्ण

/**
 * usb_स्वतःpm_put_पूर्णांकerface - decrement a USB पूर्णांकerface's PM-usage counter
 * @पूर्णांकf: the usb_पूर्णांकerface whose counter should be decremented
 *
 * This routine should be called by an पूर्णांकerface driver when it is
 * finished using @पूर्णांकf and wants to allow it to स्वतःsuspend.  A typical
 * example would be a अक्षरacter-device driver when its device file is
 * बंदd.
 *
 * The routine decrements @पूर्णांकf's usage counter.  When the counter reaches
 * 0, a delayed स्वतःsuspend request क्रम @पूर्णांकf's device is attempted.  The
 * attempt may fail (see स्वतःsuspend_check()).
 *
 * This routine can run only in process context.
 */
व्योम usb_स्वतःpm_put_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device	*udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक			status;

	usb_mark_last_busy(udev);
	status = pm_runसमय_put_sync(&पूर्णांकf->dev);
	dev_vdbg(&पूर्णांकf->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_पढ़ो(&पूर्णांकf->dev.घातer.usage_count),
			status);
पूर्ण
EXPORT_SYMBOL_GPL(usb_स्वतःpm_put_पूर्णांकerface);

/**
 * usb_स्वतःpm_put_पूर्णांकerface_async - decrement a USB पूर्णांकerface's PM-usage counter
 * @पूर्णांकf: the usb_पूर्णांकerface whose counter should be decremented
 *
 * This routine करोes much the same thing as usb_स्वतःpm_put_पूर्णांकerface():
 * It decrements @पूर्णांकf's usage counter and schedules a delayed
 * स्वतःsuspend request अगर the counter is <= 0.  The dअगरference is that it
 * करोes not perक्रमm any synchronization; callers should hold a निजी
 * lock and handle all synchronization issues themselves.
 *
 * Typically a driver would call this routine during an URB's completion
 * handler, अगर no more URBs were pending.
 *
 * This routine can run in atomic context.
 */
व्योम usb_स्वतःpm_put_पूर्णांकerface_async(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device	*udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक			status;

	usb_mark_last_busy(udev);
	status = pm_runसमय_put(&पूर्णांकf->dev);
	dev_vdbg(&पूर्णांकf->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_पढ़ो(&पूर्णांकf->dev.घातer.usage_count),
			status);
पूर्ण
EXPORT_SYMBOL_GPL(usb_स्वतःpm_put_पूर्णांकerface_async);

/**
 * usb_स्वतःpm_put_पूर्णांकerface_no_suspend - decrement a USB पूर्णांकerface's PM-usage counter
 * @पूर्णांकf: the usb_पूर्णांकerface whose counter should be decremented
 *
 * This routine decrements @पूर्णांकf's usage counter but करोes not carry out an
 * स्वतःsuspend.
 *
 * This routine can run in atomic context.
 */
व्योम usb_स्वतःpm_put_पूर्णांकerface_no_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device	*udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	usb_mark_last_busy(udev);
	pm_runसमय_put_noidle(&पूर्णांकf->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_स्वतःpm_put_पूर्णांकerface_no_suspend);

/**
 * usb_स्वतःpm_get_पूर्णांकerface - increment a USB पूर्णांकerface's PM-usage counter
 * @पूर्णांकf: the usb_पूर्णांकerface whose counter should be incremented
 *
 * This routine should be called by an पूर्णांकerface driver when it wants to
 * use @पूर्णांकf and needs to guarantee that it is not suspended.  In addition,
 * the routine prevents @पूर्णांकf from being स्वतःsuspended subsequently.  (Note
 * that this will not prevent suspend events originating in the PM core.)
 * This prevention will persist until usb_स्वतःpm_put_पूर्णांकerface() is called
 * or @पूर्णांकf is unbound.  A typical example would be a अक्षरacter-device
 * driver when its device file is खोलोed.
 *
 * @पूर्णांकf's usage counter is incremented to prevent subsequent स्वतःsuspends.
 * However अगर the स्वतःresume fails then the counter is re-decremented.
 *
 * This routine can run only in process context.
 *
 * Return: 0 on success.
 */
पूर्णांक usb_स्वतःpm_get_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक	status;

	status = pm_runसमय_get_sync(&पूर्णांकf->dev);
	अगर (status < 0)
		pm_runसमय_put_sync(&पूर्णांकf->dev);
	dev_vdbg(&पूर्णांकf->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_पढ़ो(&पूर्णांकf->dev.घातer.usage_count),
			status);
	अगर (status > 0)
		status = 0;
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(usb_स्वतःpm_get_पूर्णांकerface);

/**
 * usb_स्वतःpm_get_पूर्णांकerface_async - increment a USB पूर्णांकerface's PM-usage counter
 * @पूर्णांकf: the usb_पूर्णांकerface whose counter should be incremented
 *
 * This routine करोes much the same thing as
 * usb_स्वतःpm_get_पूर्णांकerface(): It increments @पूर्णांकf's usage counter and
 * queues an स्वतःresume request अगर the device is suspended.  The
 * dअगरferences are that it करोes not perक्रमm any synchronization (callers
 * should hold a निजी lock and handle all synchronization issues
 * themselves), and it करोes not स्वतःresume the device directly (it only
 * queues a request).  After a successful call, the device may not yet be
 * resumed.
 *
 * This routine can run in atomic context.
 *
 * Return: 0 on success. A negative error code otherwise.
 */
पूर्णांक usb_स्वतःpm_get_पूर्णांकerface_async(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक	status;

	status = pm_runसमय_get(&पूर्णांकf->dev);
	अगर (status < 0 && status != -EINPROGRESS)
		pm_runसमय_put_noidle(&पूर्णांकf->dev);
	dev_vdbg(&पूर्णांकf->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_पढ़ो(&पूर्णांकf->dev.घातer.usage_count),
			status);
	अगर (status > 0 || status == -EINPROGRESS)
		status = 0;
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(usb_स्वतःpm_get_पूर्णांकerface_async);

/**
 * usb_स्वतःpm_get_पूर्णांकerface_no_resume - increment a USB पूर्णांकerface's PM-usage counter
 * @पूर्णांकf: the usb_पूर्णांकerface whose counter should be incremented
 *
 * This routine increments @पूर्णांकf's usage counter but करोes not carry out an
 * स्वतःresume.
 *
 * This routine can run in atomic context.
 */
व्योम usb_स्वतःpm_get_पूर्णांकerface_no_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device	*udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	usb_mark_last_busy(udev);
	pm_runसमय_get_noresume(&पूर्णांकf->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_स्वतःpm_get_पूर्णांकerface_no_resume);

/* Internal routine to check whether we may स्वतःsuspend a device. */
अटल पूर्णांक स्वतःsuspend_check(काष्ठा usb_device *udev)
अणु
	पूर्णांक			w, i;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;

	अगर (udev->state == USB_STATE_NOTATTACHED)
		वापस -ENODEV;

	/* Fail अगर स्वतःsuspend is disabled, or any पूर्णांकerfaces are in use, or
	 * any पूर्णांकerface drivers require remote wakeup but it isn't available.
	 */
	w = 0;
	अगर (udev->actconfig) अणु
		क्रम (i = 0; i < udev->actconfig->desc.bNumInterfaces; i++) अणु
			पूर्णांकf = udev->actconfig->पूर्णांकerface[i];

			/* We करोn't need to check पूर्णांकerfaces that are
			 * disabled क्रम runसमय PM.  Either they are unbound
			 * or अन्यथा their drivers करोn't support स्वतःsuspend
			 * and so they are permanently active.
			 */
			अगर (पूर्णांकf->dev.घातer.disable_depth)
				जारी;
			अगर (atomic_पढ़ो(&पूर्णांकf->dev.घातer.usage_count) > 0)
				वापस -EBUSY;
			w |= पूर्णांकf->needs_remote_wakeup;

			/* Don't allow स्वतःsuspend अगर the device will need
			 * a reset-resume and any of its पूर्णांकerface drivers
			 * करोesn't include support or needs remote wakeup.
			 */
			अगर (udev->quirks & USB_QUIRK_RESET_RESUME) अणु
				काष्ठा usb_driver *driver;

				driver = to_usb_driver(पूर्णांकf->dev.driver);
				अगर (!driver->reset_resume ||
						पूर्णांकf->needs_remote_wakeup)
					वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (w && !device_can_wakeup(&udev->dev)) अणु
		dev_dbg(&udev->dev, "remote wakeup needed for autosuspend\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * If the device is a direct child of the root hub and the HCD
	 * करोesn't handle wakeup requests, don't allow स्वतःsuspend when
	 * wakeup is needed.
	 */
	अगर (w && udev->parent == udev->bus->root_hub &&
			bus_to_hcd(udev->bus)->cant_recv_wakeups) अणु
		dev_dbg(&udev->dev, "HCD doesn't handle wakeup requests\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	udev->करो_remote_wakeup = w;
	वापस 0;
पूर्ण

पूर्णांक usb_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_device	*udev = to_usb_device(dev);
	पूर्णांक			status;

	/* A USB device can be suspended अगर it passes the various स्वतःsuspend
	 * checks.  Runसमय suspend क्रम a USB device means suspending all the
	 * पूर्णांकerfaces and then the device itself.
	 */
	अगर (स्वतःsuspend_check(udev) != 0)
		वापस -EAGAIN;

	status = usb_suspend_both(udev, PMSG_AUTO_SUSPEND);

	/* Allow a retry अगर स्वतःsuspend failed temporarily */
	अगर (status == -EAGAIN || status == -EBUSY)
		usb_mark_last_busy(udev);

	/*
	 * The PM core reacts badly unless the वापस code is 0,
	 * -EAGAIN, or -EBUSY, so always वापस -EBUSY on an error
	 * (except क्रम root hubs, because they करोn't suspend through
	 * an upstream port like other USB devices).
	 */
	अगर (status != 0 && udev->parent)
		वापस -EBUSY;
	वापस status;
पूर्ण

पूर्णांक usb_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_device	*udev = to_usb_device(dev);
	पूर्णांक			status;

	/* Runसमय resume क्रम a USB device means resuming both the device
	 * and all its पूर्णांकerfaces.
	 */
	status = usb_resume_both(udev, PMSG_AUTO_RESUME);
	वापस status;
पूर्ण

पूर्णांक usb_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा usb_device	*udev = to_usb_device(dev);

	/* An idle USB device can be suspended अगर it passes the various
	 * स्वतःsuspend checks.
	 */
	अगर (स्वतःsuspend_check(udev) == 0)
		pm_runसमय_स्वतःsuspend(dev);
	/* Tell the core not to suspend it, though. */
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक usb_set_usb2_hardware_lpm(काष्ठा usb_device *udev, पूर्णांक enable)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);
	पूर्णांक ret = -EPERM;

	अगर (hcd->driver->set_usb2_hw_lpm) अणु
		ret = hcd->driver->set_usb2_hw_lpm(hcd, udev, enable);
		अगर (!ret)
			udev->usb2_hw_lpm_enabled = enable;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक usb_enable_usb2_hardware_lpm(काष्ठा usb_device *udev)
अणु
	अगर (!udev->usb2_hw_lpm_capable ||
	    !udev->usb2_hw_lpm_allowed ||
	    udev->usb2_hw_lpm_enabled)
		वापस 0;

	वापस usb_set_usb2_hardware_lpm(udev, 1);
पूर्ण

पूर्णांक usb_disable_usb2_hardware_lpm(काष्ठा usb_device *udev)
अणु
	अगर (!udev->usb2_hw_lpm_enabled)
		वापस 0;

	वापस usb_set_usb2_hardware_lpm(udev, 0);
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

काष्ठा bus_type usb_bus_type = अणु
	.name =		"usb",
	.match =	usb_device_match,
	.uevent =	usb_uevent,
	.need_parent_lock =	true,
पूर्ण;
