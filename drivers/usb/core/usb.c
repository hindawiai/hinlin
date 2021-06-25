<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/usb/core/usb.c
 *
 * (C) Copyright Linus Torvalds 1999
 * (C) Copyright Johannes Erdfelt 1999-2001
 * (C) Copyright Andreas Gal 1999
 * (C) Copyright Gregory P. Smith 1999
 * (C) Copyright Deti Fliegl 1999 (new USB architecture)
 * (C) Copyright Randy Dunlap 2000
 * (C) Copyright David Brownell 2000-2004
 * (C) Copyright Yggdrasil Computing, Inc. 2000
 *     (usb_device_id matching changes by Adam J. Richter)
 * (C) Copyright Greg Kroah-Harपंचांगan 2002-2003
 *
 * Released under the GPLv2 only.
 *
 * NOTE! This is not actually a driver at all, rather this is
 * just a collection of helper routines that implement the
 * generic USB things that the real drivers can use..
 *
 * Think of this as a "USB library" rather than anything अन्यथा,
 * with no callbacks.  Callbacks are evil.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/usb/of.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>

#समावेश "hub.h"

स्थिर अक्षर *usbcore_name = "usbcore";

अटल bool nousb;	/* Disable USB when built पूर्णांकo kernel image */

module_param(nousb, bool, 0444);

/*
 * क्रम बाह्यal पढ़ो access to <nousb>
 */
पूर्णांक usb_disabled(व्योम)
अणु
	वापस nousb;
पूर्ण
EXPORT_SYMBOL_GPL(usb_disabled);

#अगर_घोषित	CONFIG_PM
/* Default delay value, in seconds */
अटल पूर्णांक usb_स्वतःsuspend_delay = CONFIG_USB_AUTOSUSPEND_DELAY;
module_param_named(स्वतःsuspend, usb_स्वतःsuspend_delay, पूर्णांक, 0644);
MODULE_PARM_DESC(स्वतःsuspend, "default autosuspend delay");

#अन्यथा
#घोषणा usb_स्वतःsuspend_delay		0
#पूर्ण_अगर

अटल bool match_endpoपूर्णांक(काष्ठा usb_endpoपूर्णांक_descriptor *epd,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_out,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_out)
अणु
	चयन (usb_endpoपूर्णांक_type(epd)) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (usb_endpoपूर्णांक_dir_in(epd)) अणु
			अगर (bulk_in && !*bulk_in) अणु
				*bulk_in = epd;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bulk_out && !*bulk_out) अणु
				*bulk_out = epd;
				अवरोध;
			पूर्ण
		पूर्ण

		वापस false;
	हाल USB_ENDPOINT_XFER_INT:
		अगर (usb_endpoपूर्णांक_dir_in(epd)) अणु
			अगर (पूर्णांक_in && !*पूर्णांक_in) अणु
				*पूर्णांक_in = epd;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (पूर्णांक_out && !*पूर्णांक_out) अणु
				*पूर्णांक_out = epd;
				अवरोध;
			पूर्ण
		पूर्ण

		वापस false;
	शेष:
		वापस false;
	पूर्ण

	वापस (!bulk_in || *bulk_in) && (!bulk_out || *bulk_out) &&
			(!पूर्णांक_in || *पूर्णांक_in) && (!पूर्णांक_out || *पूर्णांक_out);
पूर्ण

/**
 * usb_find_common_endpoपूर्णांकs() -- look up common endpoपूर्णांक descriptors
 * @alt:	alternate setting to search
 * @bulk_in:	poपूर्णांकer to descriptor poपूर्णांकer, or शून्य
 * @bulk_out:	poपूर्णांकer to descriptor poपूर्णांकer, or शून्य
 * @पूर्णांक_in:	poपूर्णांकer to descriptor poपूर्णांकer, or शून्य
 * @पूर्णांक_out:	poपूर्णांकer to descriptor poपूर्णांकer, or शून्य
 *
 * Search the alternate setting's endpoपूर्णांक descriptors क्रम the first bulk-in,
 * bulk-out, पूर्णांकerrupt-in and पूर्णांकerrupt-out endpoपूर्णांकs and वापस them in the
 * provided poपूर्णांकers (unless they are शून्य).
 *
 * If a requested endpoपूर्णांक is not found, the corresponding poपूर्णांकer is set to
 * शून्य.
 *
 * Return: Zero अगर all requested descriptors were found, or -ENXIO otherwise.
 */
पूर्णांक usb_find_common_endpoपूर्णांकs(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_out,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_out)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	पूर्णांक i;

	अगर (bulk_in)
		*bulk_in = शून्य;
	अगर (bulk_out)
		*bulk_out = शून्य;
	अगर (पूर्णांक_in)
		*पूर्णांक_in = शून्य;
	अगर (पूर्णांक_out)
		*पूर्णांक_out = शून्य;

	क्रम (i = 0; i < alt->desc.bNumEndpoपूर्णांकs; ++i) अणु
		epd = &alt->endpoपूर्णांक[i].desc;

		अगर (match_endpoपूर्णांक(epd, bulk_in, bulk_out, पूर्णांक_in, पूर्णांक_out))
			वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण
EXPORT_SYMBOL_GPL(usb_find_common_endpoपूर्णांकs);

/**
 * usb_find_common_endpoपूर्णांकs_reverse() -- look up common endpoपूर्णांक descriptors
 * @alt:	alternate setting to search
 * @bulk_in:	poपूर्णांकer to descriptor poपूर्णांकer, or शून्य
 * @bulk_out:	poपूर्णांकer to descriptor poपूर्णांकer, or शून्य
 * @पूर्णांक_in:	poपूर्णांकer to descriptor poपूर्णांकer, or शून्य
 * @पूर्णांक_out:	poपूर्णांकer to descriptor poपूर्णांकer, or शून्य
 *
 * Search the alternate setting's endpoपूर्णांक descriptors क्रम the last bulk-in,
 * bulk-out, पूर्णांकerrupt-in and पूर्णांकerrupt-out endpoपूर्णांकs and वापस them in the
 * provided poपूर्णांकers (unless they are शून्य).
 *
 * If a requested endpoपूर्णांक is not found, the corresponding poपूर्णांकer is set to
 * शून्य.
 *
 * Return: Zero अगर all requested descriptors were found, or -ENXIO otherwise.
 */
पूर्णांक usb_find_common_endpoपूर्णांकs_reverse(काष्ठा usb_host_पूर्णांकerface *alt,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **bulk_out,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_in,
		काष्ठा usb_endpoपूर्णांक_descriptor **पूर्णांक_out)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	पूर्णांक i;

	अगर (bulk_in)
		*bulk_in = शून्य;
	अगर (bulk_out)
		*bulk_out = शून्य;
	अगर (पूर्णांक_in)
		*पूर्णांक_in = शून्य;
	अगर (पूर्णांक_out)
		*पूर्णांक_out = शून्य;

	क्रम (i = alt->desc.bNumEndpoपूर्णांकs - 1; i >= 0; --i) अणु
		epd = &alt->endpoपूर्णांक[i].desc;

		अगर (match_endpoपूर्णांक(epd, bulk_in, bulk_out, पूर्णांक_in, पूर्णांक_out))
			वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण
EXPORT_SYMBOL_GPL(usb_find_common_endpoपूर्णांकs_reverse);

/**
 * usb_find_alt_setting() - Given a configuration, find the alternate setting
 * क्रम the given पूर्णांकerface.
 * @config: the configuration to search (not necessarily the current config).
 * @अगरace_num: पूर्णांकerface number to search in
 * @alt_num: alternate पूर्णांकerface setting number to search क्रम.
 *
 * Search the configuration's पूर्णांकerface cache क्रम the given alt setting.
 *
 * Return: The alternate setting, अगर found. %शून्य otherwise.
 */
काष्ठा usb_host_पूर्णांकerface *usb_find_alt_setting(
		काष्ठा usb_host_config *config,
		अचिन्हित पूर्णांक अगरace_num,
		अचिन्हित पूर्णांक alt_num)
अणु
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकf_cache = शून्य;
	पूर्णांक i;

	अगर (!config)
		वापस शून्य;
	क्रम (i = 0; i < config->desc.bNumInterfaces; i++) अणु
		अगर (config->पूर्णांकf_cache[i]->altsetting[0].desc.bInterfaceNumber
				== अगरace_num) अणु
			पूर्णांकf_cache = config->पूर्णांकf_cache[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!पूर्णांकf_cache)
		वापस शून्य;
	क्रम (i = 0; i < पूर्णांकf_cache->num_altsetting; i++)
		अगर (पूर्णांकf_cache->altsetting[i].desc.bAlternateSetting == alt_num)
			वापस &पूर्णांकf_cache->altsetting[i];

	prपूर्णांकk(KERN_DEBUG "Did not find alt setting %u for intf %u, "
			"config %u\n", alt_num, अगरace_num,
			config->desc.bConfigurationValue);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_find_alt_setting);

/**
 * usb_अगरnum_to_अगर - get the पूर्णांकerface object with a given पूर्णांकerface number
 * @dev: the device whose current configuration is considered
 * @अगरnum: the desired पूर्णांकerface
 *
 * This walks the device descriptor क्रम the currently active configuration
 * to find the पूर्णांकerface object with the particular पूर्णांकerface number.
 *
 * Note that configuration descriptors are not required to assign पूर्णांकerface
 * numbers sequentially, so that it would be incorrect to assume that
 * the first पूर्णांकerface in that descriptor corresponds to पूर्णांकerface zero.
 * This routine helps device drivers aव्योम such mistakes.
 * However, you should make sure that you करो the right thing with any
 * alternate settings available क्रम this पूर्णांकerfaces.
 *
 * Don't call this function unless you are bound to one of the पूर्णांकerfaces
 * on this device or you have locked the device!
 *
 * Return: A poपूर्णांकer to the पूर्णांकerface that has @अगरnum as पूर्णांकerface number,
 * अगर found. %शून्य otherwise.
 */
काष्ठा usb_पूर्णांकerface *usb_अगरnum_to_अगर(स्थिर काष्ठा usb_device *dev,
				      अचिन्हित अगरnum)
अणु
	काष्ठा usb_host_config *config = dev->actconfig;
	पूर्णांक i;

	अगर (!config)
		वापस शून्य;
	क्रम (i = 0; i < config->desc.bNumInterfaces; i++)
		अगर (config->पूर्णांकerface[i]->altsetting[0]
				.desc.bInterfaceNumber == अगरnum)
			वापस config->पूर्णांकerface[i];

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_अगरnum_to_अगर);

/**
 * usb_altnum_to_altsetting - get the altsetting काष्ठाure with a given alternate setting number.
 * @पूर्णांकf: the पूर्णांकerface containing the altsetting in question
 * @altnum: the desired alternate setting number
 *
 * This searches the altsetting array of the specअगरied पूर्णांकerface क्रम
 * an entry with the correct bAlternateSetting value.
 *
 * Note that altsettings need not be stored sequentially by number, so
 * it would be incorrect to assume that the first altsetting entry in
 * the array corresponds to altsetting zero.  This routine helps device
 * drivers aव्योम such mistakes.
 *
 * Don't call this function unless you are bound to the पूर्णांकf पूर्णांकerface
 * or you have locked the device!
 *
 * Return: A poपूर्णांकer to the entry of the altsetting array of @पूर्णांकf that
 * has @altnum as the alternate setting number. %शून्य अगर not found.
 */
काष्ठा usb_host_पूर्णांकerface *usb_altnum_to_altsetting(
					स्थिर काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					अचिन्हित पूर्णांक altnum)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < पूर्णांकf->num_altsetting; i++) अणु
		अगर (पूर्णांकf->altsetting[i].desc.bAlternateSetting == altnum)
			वापस &पूर्णांकf->altsetting[i];
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_altnum_to_altsetting);

काष्ठा find_पूर्णांकerface_arg अणु
	पूर्णांक minor;
	काष्ठा device_driver *drv;
पूर्ण;

अटल पूर्णांक __find_पूर्णांकerface(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा find_पूर्णांकerface_arg *arg = data;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	अगर (!is_usb_पूर्णांकerface(dev))
		वापस 0;

	अगर (dev->driver != arg->drv)
		वापस 0;
	पूर्णांकf = to_usb_पूर्णांकerface(dev);
	वापस पूर्णांकf->minor == arg->minor;
पूर्ण

/**
 * usb_find_पूर्णांकerface - find usb_पूर्णांकerface poपूर्णांकer क्रम driver and device
 * @drv: the driver whose current configuration is considered
 * @minor: the minor number of the desired device
 *
 * This walks the bus device list and वापसs a poपूर्णांकer to the पूर्णांकerface
 * with the matching minor and driver.  Note, this only works क्रम devices
 * that share the USB major number.
 *
 * Return: A poपूर्णांकer to the पूर्णांकerface with the matching major and @minor.
 */
काष्ठा usb_पूर्णांकerface *usb_find_पूर्णांकerface(काष्ठा usb_driver *drv, पूर्णांक minor)
अणु
	काष्ठा find_पूर्णांकerface_arg argb;
	काष्ठा device *dev;

	argb.minor = minor;
	argb.drv = &drv->drvwrap.driver;

	dev = bus_find_device(&usb_bus_type, शून्य, &argb, __find_पूर्णांकerface);

	/* Drop reference count from bus_find_device */
	put_device(dev);

	वापस dev ? to_usb_पूर्णांकerface(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_find_पूर्णांकerface);

काष्ठा each_dev_arg अणु
	व्योम *data;
	पूर्णांक (*fn)(काष्ठा usb_device *, व्योम *);
पूर्ण;

अटल पूर्णांक __each_dev(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा each_dev_arg *arg = (काष्ठा each_dev_arg *)data;

	/* There are काष्ठा usb_पूर्णांकerface on the same bus, filter them out */
	अगर (!is_usb_device(dev))
		वापस 0;

	वापस arg->fn(to_usb_device(dev), arg->data);
पूर्ण

/**
 * usb_क्रम_each_dev - iterate over all USB devices in the प्रणाली
 * @data: data poपूर्णांकer that will be handed to the callback function
 * @fn: callback function to be called क्रम each USB device
 *
 * Iterate over all USB devices and call @fn क्रम each, passing it @data. If it
 * वापसs anything other than 0, we अवरोध the iteration prematurely and वापस
 * that value.
 */
पूर्णांक usb_क्रम_each_dev(व्योम *data, पूर्णांक (*fn)(काष्ठा usb_device *, व्योम *))
अणु
	काष्ठा each_dev_arg arg = अणुdata, fnपूर्ण;

	वापस bus_क्रम_each_dev(&usb_bus_type, शून्य, &arg, __each_dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_क्रम_each_dev);

काष्ठा each_hub_arg अणु
	व्योम *data;
	पूर्णांक (*fn)(काष्ठा device *, व्योम *);
पूर्ण;

अटल पूर्णांक __each_hub(काष्ठा usb_device *hdev, व्योम *data)
अणु
	काष्ठा each_hub_arg *arg = (काष्ठा each_hub_arg *)data;
	काष्ठा usb_hub *hub;
	पूर्णांक ret = 0;
	पूर्णांक i;

	hub = usb_hub_to_काष्ठा_hub(hdev);
	अगर (!hub)
		वापस 0;

	mutex_lock(&usb_port_peer_mutex);

	क्रम (i = 0; i < hdev->maxchild; i++) अणु
		ret = arg->fn(&hub->ports[i]->dev, arg->data);
		अगर (ret)
			अवरोध;
	पूर्ण

	mutex_unlock(&usb_port_peer_mutex);

	वापस ret;
पूर्ण

/**
 * usb_क्रम_each_port - पूर्णांकerate over all USB ports in the प्रणाली
 * @data: data poपूर्णांकer that will be handed to the callback function
 * @fn: callback function to be called क्रम each USB port
 *
 * Iterate over all USB ports and call @fn क्रम each, passing it @data. If it
 * वापसs anything other than 0, we अवरोध the iteration prematurely and वापस
 * that value.
 */
पूर्णांक usb_क्रम_each_port(व्योम *data, पूर्णांक (*fn)(काष्ठा device *, व्योम *))
अणु
	काष्ठा each_hub_arg arg = अणुdata, fnपूर्ण;

	वापस usb_क्रम_each_dev(&arg, __each_hub);
पूर्ण
EXPORT_SYMBOL_GPL(usb_क्रम_each_port);

/**
 * usb_release_dev - मुक्त a usb device काष्ठाure when all users of it are finished.
 * @dev: device that's been disconnected
 *
 * Will be called only by the device core when all users of this usb device are
 * करोne.
 */
अटल व्योम usb_release_dev(काष्ठा device *dev)
अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_hcd *hcd;

	udev = to_usb_device(dev);
	hcd = bus_to_hcd(udev->bus);

	usb_destroy_configuration(udev);
	usb_release_bos_descriptor(udev);
	of_node_put(dev->of_node);
	usb_put_hcd(hcd);
	kमुक्त(udev->product);
	kमुक्त(udev->manufacturer);
	kमुक्त(udev->serial);
	kमुक्त(udev);
पूर्ण

अटल पूर्णांक usb_dev_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा usb_device *usb_dev;

	usb_dev = to_usb_device(dev);

	अगर (add_uevent_var(env, "BUSNUM=%03d", usb_dev->bus->busnum))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "DEVNUM=%03d", usb_dev->devnum))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

#अगर_घोषित	CONFIG_PM

/* USB device Power-Management thunks.
 * There's no need to distinguish here between quiescing a USB device
 * and घातering it करोwn; the generic_suspend() routine takes care of
 * it by skipping the usb_port_suspend() call क्रम a quiesce.  And क्रम
 * USB पूर्णांकerfaces there's no dअगरference at all.
 */

अटल पूर्णांक usb_dev_prepare(काष्ठा device *dev)
अणु
	वापस 0;		/* Implement eventually? */
पूर्ण

अटल व्योम usb_dev_complete(काष्ठा device *dev)
अणु
	/* Currently used only क्रम rebinding पूर्णांकerfaces */
	usb_resume_complete(dev);
पूर्ण

अटल पूर्णांक usb_dev_suspend(काष्ठा device *dev)
अणु
	वापस usb_suspend(dev, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक usb_dev_resume(काष्ठा device *dev)
अणु
	वापस usb_resume(dev, PMSG_RESUME);
पूर्ण

अटल पूर्णांक usb_dev_मुक्तze(काष्ठा device *dev)
अणु
	वापस usb_suspend(dev, PMSG_FREEZE);
पूर्ण

अटल पूर्णांक usb_dev_thaw(काष्ठा device *dev)
अणु
	वापस usb_resume(dev, PMSG_THAW);
पूर्ण

अटल पूर्णांक usb_dev_घातeroff(काष्ठा device *dev)
अणु
	वापस usb_suspend(dev, PMSG_HIBERNATE);
पूर्ण

अटल पूर्णांक usb_dev_restore(काष्ठा device *dev)
अणु
	वापस usb_resume(dev, PMSG_RESTORE);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops usb_device_pm_ops = अणु
	.prepare =	usb_dev_prepare,
	.complete =	usb_dev_complete,
	.suspend =	usb_dev_suspend,
	.resume =	usb_dev_resume,
	.मुक्तze =	usb_dev_मुक्तze,
	.thaw =		usb_dev_thaw,
	.घातeroff =	usb_dev_घातeroff,
	.restore =	usb_dev_restore,
	.runसमय_suspend =	usb_runसमय_suspend,
	.runसमय_resume =	usb_runसमय_resume,
	.runसमय_idle =		usb_runसमय_idle,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_PM */


अटल अक्षर *usb_devnode(काष्ठा device *dev,
			 umode_t *mode, kuid_t *uid, kgid_t *gid)
अणु
	काष्ठा usb_device *usb_dev;

	usb_dev = to_usb_device(dev);
	वापस kaप्र_लिखो(GFP_KERNEL, "bus/usb/%03d/%03d",
			 usb_dev->bus->busnum, usb_dev->devnum);
पूर्ण

काष्ठा device_type usb_device_type = अणु
	.name =		"usb_device",
	.release =	usb_release_dev,
	.uevent =	usb_dev_uevent,
	.devnode = 	usb_devnode,
#अगर_घोषित CONFIG_PM
	.pm =		&usb_device_pm_ops,
#पूर्ण_अगर
पूर्ण;


/* Returns 1 अगर @usb_bus is WUSB, 0 otherwise */
अटल अचिन्हित usb_bus_is_wusb(काष्ठा usb_bus *bus)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(bus);
	वापस hcd->wireless;
पूर्ण

अटल bool usb_dev_authorized(काष्ठा usb_device *dev, काष्ठा usb_hcd *hcd)
अणु
	काष्ठा usb_hub *hub;

	अगर (!dev->parent)
		वापस true; /* Root hub always ok [and always wired] */

	चयन (hcd->dev_policy) अणु
	हाल USB_DEVICE_AUTHORIZE_NONE:
	शेष:
		वापस false;

	हाल USB_DEVICE_AUTHORIZE_ALL:
		वापस true;

	हाल USB_DEVICE_AUTHORIZE_INTERNAL:
		hub = usb_hub_to_काष्ठा_hub(dev->parent);
		वापस hub->ports[dev->portnum - 1]->connect_type ==
				USB_PORT_CONNECT_TYPE_HARD_WIRED;
	पूर्ण
पूर्ण

/**
 * usb_alloc_dev - usb device स्थिरructor (usbcore-पूर्णांकernal)
 * @parent: hub to which device is connected; null to allocate a root hub
 * @bus: bus used to access the device
 * @port1: one-based index of port; ignored क्रम root hubs
 *
 * Context: task context, might sleep.
 *
 * Only hub drivers (including भव root hub drivers क्रम host
 * controllers) should ever call this.
 *
 * This call may not be used in a non-sleeping context.
 *
 * Return: On success, a poपूर्णांकer to the allocated usb device. %शून्य on
 * failure.
 */
काष्ठा usb_device *usb_alloc_dev(काष्ठा usb_device *parent,
				 काष्ठा usb_bus *bus, अचिन्हित port1)
अणु
	काष्ठा usb_device *dev;
	काष्ठा usb_hcd *usb_hcd = bus_to_hcd(bus);
	अचिन्हित root_hub = 0;
	अचिन्हित raw_port = port1;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	अगर (!usb_get_hcd(usb_hcd)) अणु
		kमुक्त(dev);
		वापस शून्य;
	पूर्ण
	/* Root hubs aren't true devices, so don't allocate HCD resources */
	अगर (usb_hcd->driver->alloc_dev && parent &&
		!usb_hcd->driver->alloc_dev(usb_hcd, dev)) अणु
		usb_put_hcd(bus_to_hcd(bus));
		kमुक्त(dev);
		वापस शून्य;
	पूर्ण

	device_initialize(&dev->dev);
	dev->dev.bus = &usb_bus_type;
	dev->dev.type = &usb_device_type;
	dev->dev.groups = usb_device_groups;
	set_dev_node(&dev->dev, dev_to_node(bus->sysdev));
	dev->state = USB_STATE_ATTACHED;
	dev->lpm_disable_count = 1;
	atomic_set(&dev->urbnum, 0);

	INIT_LIST_HEAD(&dev->ep0.urb_list);
	dev->ep0.desc.bLength = USB_DT_ENDPOINT_SIZE;
	dev->ep0.desc.bDescriptorType = USB_DT_ENDPOINT;
	/* ep0 maxpacket comes later, from device descriptor */
	usb_enable_endpoपूर्णांक(dev, &dev->ep0, false);
	dev->can_submit = 1;

	/* Save पढ़ोable and stable topology id, distinguishing devices
	 * by location क्रम diagnostics, tools, driver model, etc.  The
	 * string is a path aदीर्घ hub ports, from the root.  Each device's
	 * dev->devpath will be stable until USB is re-cabled, and hubs
	 * are often labeled with these port numbers.  The name isn't
	 * as stable:  bus->busnum changes easily from modprobe order,
	 * cardbus or pci hotplugging, and so on.
	 */
	अगर (unlikely(!parent)) अणु
		dev->devpath[0] = '0';
		dev->route = 0;

		dev->dev.parent = bus->controller;
		device_set_of_node_from_dev(&dev->dev, bus->sysdev);
		dev_set_name(&dev->dev, "usb%d", bus->busnum);
		root_hub = 1;
	पूर्ण अन्यथा अणु
		/* match any labeling on the hubs; it's one-based */
		अगर (parent->devpath[0] == '0') अणु
			snम_लिखो(dev->devpath, माप dev->devpath,
				"%d", port1);
			/* Root ports are not counted in route string */
			dev->route = 0;
		पूर्ण अन्यथा अणु
			snम_लिखो(dev->devpath, माप dev->devpath,
				"%s.%d", parent->devpath, port1);
			/* Route string assumes hubs have less than 16 ports */
			अगर (port1 < 15)
				dev->route = parent->route +
					(port1 << ((parent->level - 1)*4));
			अन्यथा
				dev->route = parent->route +
					(15 << ((parent->level - 1)*4));
		पूर्ण

		dev->dev.parent = &parent->dev;
		dev_set_name(&dev->dev, "%d-%s", bus->busnum, dev->devpath);

		अगर (!parent->parent) अणु
			/* device under root hub's port */
			raw_port = usb_hcd_find_raw_port_number(usb_hcd,
				port1);
		पूर्ण
		dev->dev.of_node = usb_of_get_device_node(parent, raw_port);

		/* hub driver sets up TT records */
	पूर्ण

	dev->portnum = port1;
	dev->bus = bus;
	dev->parent = parent;
	INIT_LIST_HEAD(&dev->filelist);

#अगर_घोषित	CONFIG_PM
	pm_runसमय_set_स्वतःsuspend_delay(&dev->dev,
			usb_स्वतःsuspend_delay * 1000);
	dev->connect_समय = jअगरfies;
	dev->active_duration = -jअगरfies;
#पूर्ण_अगर

	dev->authorized = usb_dev_authorized(dev, usb_hcd);
	अगर (!root_hub)
		dev->wusb = usb_bus_is_wusb(bus) ? 1 : 0;

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(usb_alloc_dev);

/**
 * usb_get_dev - increments the reference count of the usb device काष्ठाure
 * @dev: the device being referenced
 *
 * Each live reference to a device should be refcounted.
 *
 * Drivers क्रम USB पूर्णांकerfaces should normally record such references in
 * their probe() methods, when they bind to an पूर्णांकerface, and release
 * them by calling usb_put_dev(), in their disconnect() methods.
 *
 * Return: A poपूर्णांकer to the device with the incremented reference counter.
 */
काष्ठा usb_device *usb_get_dev(काष्ठा usb_device *dev)
अणु
	अगर (dev)
		get_device(&dev->dev);
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_dev);

/**
 * usb_put_dev - release a use of the usb device काष्ठाure
 * @dev: device that's been disconnected
 *
 * Must be called when a user of a device is finished with it.  When the last
 * user of the device calls this function, the memory of the device is मुक्तd.
 */
व्योम usb_put_dev(काष्ठा usb_device *dev)
अणु
	अगर (dev)
		put_device(&dev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_put_dev);

/**
 * usb_get_पूर्णांकf - increments the reference count of the usb पूर्णांकerface काष्ठाure
 * @पूर्णांकf: the पूर्णांकerface being referenced
 *
 * Each live reference to a पूर्णांकerface must be refcounted.
 *
 * Drivers क्रम USB पूर्णांकerfaces should normally record such references in
 * their probe() methods, when they bind to an पूर्णांकerface, and release
 * them by calling usb_put_पूर्णांकf(), in their disconnect() methods.
 *
 * Return: A poपूर्णांकer to the पूर्णांकerface with the incremented reference counter.
 */
काष्ठा usb_पूर्णांकerface *usb_get_पूर्णांकf(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	अगर (पूर्णांकf)
		get_device(&पूर्णांकf->dev);
	वापस पूर्णांकf;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_पूर्णांकf);

/**
 * usb_put_पूर्णांकf - release a use of the usb पूर्णांकerface काष्ठाure
 * @पूर्णांकf: पूर्णांकerface that's been decremented
 *
 * Must be called when a user of an पूर्णांकerface is finished with it.  When the
 * last user of the पूर्णांकerface calls this function, the memory of the पूर्णांकerface
 * is मुक्तd.
 */
व्योम usb_put_पूर्णांकf(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	अगर (पूर्णांकf)
		put_device(&पूर्णांकf->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_put_पूर्णांकf);

/**
 * usb_पूर्णांकf_get_dma_device - acquire a reference on the usb पूर्णांकerface's DMA endpoपूर्णांक
 * @पूर्णांकf: the usb पूर्णांकerface
 *
 * While a USB device cannot perक्रमm DMA operations by itself, many USB
 * controllers can. A call to usb_पूर्णांकf_get_dma_device() वापसs the DMA endpoपूर्णांक
 * क्रम the given USB पूर्णांकerface, अगर any. The वापसed device काष्ठाure must be
 * released with put_device().
 *
 * See also usb_get_dma_device().
 *
 * Returns: A reference to the usb पूर्णांकerface's DMA endpoपूर्णांक; or शून्य अगर none
 *          exists.
 */
काष्ठा device *usb_पूर्णांकf_get_dma_device(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा device *dmadev;

	अगर (!udev->bus)
		वापस शून्य;

	dmadev = get_device(udev->bus->sysdev);
	अगर (!dmadev || !dmadev->dma_mask) अणु
		put_device(dmadev);
		वापस शून्य;
	पूर्ण

	वापस dmadev;
पूर्ण
EXPORT_SYMBOL_GPL(usb_पूर्णांकf_get_dma_device);

/*			USB device locking
 *
 * USB devices and पूर्णांकerfaces are locked using the semaphore in their
 * embedded काष्ठा device.  The hub driver guarantees that whenever a
 * device is connected or disconnected, drivers are called with the
 * USB device locked as well as their particular पूर्णांकerface.
 *
 * Complications arise when several devices are to be locked at the same
 * समय.  Only hub-aware drivers that are part of usbcore ever have to
 * करो this; nobody अन्यथा needs to worry about it.  The rule क्रम locking
 * is simple:
 *
 *	When locking both a device and its parent, always lock the
 *	the parent first.
 */

/**
 * usb_lock_device_क्रम_reset - cautiously acquire the lock क्रम a usb device काष्ठाure
 * @udev: device that's being locked
 * @अगरace: पूर्णांकerface bound to the driver making the request (optional)
 *
 * Attempts to acquire the device lock, but fails अगर the device is
 * NOTATTACHED or SUSPENDED, or अगर अगरace is specअगरied and the पूर्णांकerface
 * is neither BINDING nor BOUND.  Rather than sleeping to रुको क्रम the
 * lock, the routine polls repeatedly.  This is to prevent deadlock with
 * disconnect; in some drivers (such as usb-storage) the disconnect()
 * or suspend() method will block रुकोing क्रम a device reset to complete.
 *
 * Return: A negative error code क्रम failure, otherwise 0.
 */
पूर्णांक usb_lock_device_क्रम_reset(काष्ठा usb_device *udev,
			      स्थिर काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	अचिन्हित दीर्घ jअगरfies_expire = jअगरfies + HZ;

	अगर (udev->state == USB_STATE_NOTATTACHED)
		वापस -ENODEV;
	अगर (udev->state == USB_STATE_SUSPENDED)
		वापस -EHOSTUNREACH;
	अगर (अगरace && (अगरace->condition == USB_INTERFACE_UNBINDING ||
			अगरace->condition == USB_INTERFACE_UNBOUND))
		वापस -EINTR;

	जबतक (!usb_trylock_device(udev)) अणु

		/* If we can't acquire the lock after रुकोing one second,
		 * we're probably deadlocked */
		अगर (समय_after(jअगरfies, jअगरfies_expire))
			वापस -EBUSY;

		msleep(15);
		अगर (udev->state == USB_STATE_NOTATTACHED)
			वापस -ENODEV;
		अगर (udev->state == USB_STATE_SUSPENDED)
			वापस -EHOSTUNREACH;
		अगर (अगरace && (अगरace->condition == USB_INTERFACE_UNBINDING ||
				अगरace->condition == USB_INTERFACE_UNBOUND))
			वापस -EINTR;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_lock_device_क्रम_reset);

/**
 * usb_get_current_frame_number - वापस current bus frame number
 * @dev: the device whose bus is being queried
 *
 * Return: The current frame number क्रम the USB host controller used
 * with the given USB device. This can be used when scheduling
 * isochronous requests.
 *
 * Note: Dअगरferent kinds of host controller have dअगरferent "scheduling
 * horizons". While one type might support scheduling only 32 frames
 * पूर्णांकo the future, others could support scheduling up to 1024 frames
 * पूर्णांकo the future.
 *
 */
पूर्णांक usb_get_current_frame_number(काष्ठा usb_device *dev)
अणु
	वापस usb_hcd_get_frame_number(dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_current_frame_number);

/*-------------------------------------------------------------------*/
/*
 * __usb_get_extra_descriptor() finds a descriptor of specअगरic type in the
 * extra field of the पूर्णांकerface and endpoपूर्णांक descriptor काष्ठाs.
 */

पूर्णांक __usb_get_extra_descriptor(अक्षर *buffer, अचिन्हित size,
			       अचिन्हित अक्षर type, व्योम **ptr, माप_प्रकार minsize)
अणु
	काष्ठा usb_descriptor_header *header;

	जबतक (size >= माप(काष्ठा usb_descriptor_header)) अणु
		header = (काष्ठा usb_descriptor_header *)buffer;

		अगर (header->bLength < 2 || header->bLength > size) अणु
			prपूर्णांकk(KERN_ERR
				"%s: bogus descriptor, type %d length %d\n",
				usbcore_name,
				header->bDescriptorType,
				header->bLength);
			वापस -1;
		पूर्ण

		अगर (header->bDescriptorType == type && header->bLength >= minsize) अणु
			*ptr = header;
			वापस 0;
		पूर्ण

		buffer += header->bLength;
		size -= header->bLength;
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(__usb_get_extra_descriptor);

/**
 * usb_alloc_coherent - allocate dma-consistent buffer क्रम URB_NO_xxx_DMA_MAP
 * @dev: device the buffer will be used with
 * @size: requested buffer size
 * @mem_flags: affect whether allocation may block
 * @dma: used to वापस DMA address of buffer
 *
 * Return: Either null (indicating no buffer could be allocated), or the
 * cpu-space poपूर्णांकer to a buffer that may be used to perक्रमm DMA to the
 * specअगरied device.  Such cpu-space buffers are वापसed aदीर्घ with the DMA
 * address (through the poपूर्णांकer provided).
 *
 * Note:
 * These buffers are used with URB_NO_xxx_DMA_MAP set in urb->transfer_flags
 * to aव्योम behaviors like using "DMA bounce buffers", or thrashing IOMMU
 * hardware during URB completion/resubmit.  The implementation varies between
 * platक्रमms, depending on details of how DMA will work to this device.
 * Using these buffers also eliminates cacheline sharing problems on
 * architectures where CPU caches are not DMA-coherent.  On प्रणालीs without
 * bus-snooping caches, these buffers are uncached.
 *
 * When the buffer is no दीर्घer used, मुक्त it with usb_मुक्त_coherent().
 */
व्योम *usb_alloc_coherent(काष्ठा usb_device *dev, माप_प्रकार size, gfp_t mem_flags,
			 dma_addr_t *dma)
अणु
	अगर (!dev || !dev->bus)
		वापस शून्य;
	वापस hcd_buffer_alloc(dev->bus, size, mem_flags, dma);
पूर्ण
EXPORT_SYMBOL_GPL(usb_alloc_coherent);

/**
 * usb_मुक्त_coherent - मुक्त memory allocated with usb_alloc_coherent()
 * @dev: device the buffer was used with
 * @size: requested buffer size
 * @addr: CPU address of buffer
 * @dma: DMA address of buffer
 *
 * This reclaims an I/O buffer, letting it be reused.  The memory must have
 * been allocated using usb_alloc_coherent(), and the parameters must match
 * those provided in that allocation request.
 */
व्योम usb_मुक्त_coherent(काष्ठा usb_device *dev, माप_प्रकार size, व्योम *addr,
		       dma_addr_t dma)
अणु
	अगर (!dev || !dev->bus)
		वापस;
	अगर (!addr)
		वापस;
	hcd_buffer_मुक्त(dev->bus, size, addr, dma);
पूर्ण
EXPORT_SYMBOL_GPL(usb_मुक्त_coherent);

/*
 * Notअगरications of device and पूर्णांकerface registration
 */
अटल पूर्णांक usb_bus_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
		व्योम *data)
अणु
	काष्ठा device *dev = data;

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		अगर (dev->type == &usb_device_type)
			(व्योम) usb_create_sysfs_dev_files(to_usb_device(dev));
		अन्यथा अगर (dev->type == &usb_अगर_device_type)
			usb_create_sysfs_पूर्णांकf_files(to_usb_पूर्णांकerface(dev));
		अवरोध;

	हाल BUS_NOTIFY_DEL_DEVICE:
		अगर (dev->type == &usb_device_type)
			usb_हटाओ_sysfs_dev_files(to_usb_device(dev));
		अन्यथा अगर (dev->type == &usb_अगर_device_type)
			usb_हटाओ_sysfs_पूर्णांकf_files(to_usb_पूर्णांकerface(dev));
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block usb_bus_nb = अणु
	.notअगरier_call = usb_bus_notअगरy,
पूर्ण;

अटल व्योम usb_debugfs_init(व्योम)
अणु
	debugfs_create_file("devices", 0444, usb_debug_root, शून्य,
			    &usbfs_devices_fops);
पूर्ण

अटल व्योम usb_debugfs_cleanup(व्योम)
अणु
	debugfs_हटाओ(debugfs_lookup("devices", usb_debug_root));
पूर्ण

/*
 * Init
 */
अटल पूर्णांक __init usb_init(व्योम)
अणु
	पूर्णांक retval;
	अगर (usb_disabled()) अणु
		pr_info("%s: USB support disabled\n", usbcore_name);
		वापस 0;
	पूर्ण
	usb_init_pool_max();

	usb_debugfs_init();

	usb_acpi_रेजिस्टर();
	retval = bus_रेजिस्टर(&usb_bus_type);
	अगर (retval)
		जाओ bus_रेजिस्टर_failed;
	retval = bus_रेजिस्टर_notअगरier(&usb_bus_type, &usb_bus_nb);
	अगर (retval)
		जाओ bus_notअगरier_failed;
	retval = usb_major_init();
	अगर (retval)
		जाओ major_init_failed;
	retval = usb_रेजिस्टर(&usbfs_driver);
	अगर (retval)
		जाओ driver_रेजिस्टर_failed;
	retval = usb_devio_init();
	अगर (retval)
		जाओ usb_devio_init_failed;
	retval = usb_hub_init();
	अगर (retval)
		जाओ hub_init_failed;
	retval = usb_रेजिस्टर_device_driver(&usb_generic_driver, THIS_MODULE);
	अगर (!retval)
		जाओ out;

	usb_hub_cleanup();
hub_init_failed:
	usb_devio_cleanup();
usb_devio_init_failed:
	usb_deरेजिस्टर(&usbfs_driver);
driver_रेजिस्टर_failed:
	usb_major_cleanup();
major_init_failed:
	bus_unरेजिस्टर_notअगरier(&usb_bus_type, &usb_bus_nb);
bus_notअगरier_failed:
	bus_unरेजिस्टर(&usb_bus_type);
bus_रेजिस्टर_failed:
	usb_acpi_unरेजिस्टर();
	usb_debugfs_cleanup();
out:
	वापस retval;
पूर्ण

/*
 * Cleanup
 */
अटल व्योम __निकास usb_निकास(व्योम)
अणु
	/* This will matter अगर shutकरोwn/reboot करोes निकासcalls. */
	अगर (usb_disabled())
		वापस;

	usb_release_quirk_list();
	usb_deरेजिस्टर_device_driver(&usb_generic_driver);
	usb_major_cleanup();
	usb_deरेजिस्टर(&usbfs_driver);
	usb_devio_cleanup();
	usb_hub_cleanup();
	bus_unरेजिस्टर_notअगरier(&usb_bus_type, &usb_bus_nb);
	bus_unरेजिस्टर(&usb_bus_type);
	usb_acpi_unरेजिस्टर();
	usb_debugfs_cleanup();
	idr_destroy(&usb_bus_idr);
पूर्ण

subsys_initcall(usb_init);
module_निकास(usb_निकास);
MODULE_LICENSE("GPL");
