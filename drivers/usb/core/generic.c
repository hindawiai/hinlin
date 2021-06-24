<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/usb/generic.c - generic driver क्रम USB devices (not पूर्णांकerfaces)
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
 */

#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <uapi/linux/usb/audपन.स>
#समावेश "usb.h"

अटल अंतरभूत स्थिर अक्षर *plural(पूर्णांक n)
अणु
	वापस (n == 1 ? "" : "s");
पूर्ण

अटल पूर्णांक is_rndis(काष्ठा usb_पूर्णांकerface_descriptor *desc)
अणु
	वापस desc->bInterfaceClass == USB_CLASS_COMM
		&& desc->bInterfaceSubClass == 2
		&& desc->bInterfaceProtocol == 0xff;
पूर्ण

अटल पूर्णांक is_activesync(काष्ठा usb_पूर्णांकerface_descriptor *desc)
अणु
	वापस desc->bInterfaceClass == USB_CLASS_MISC
		&& desc->bInterfaceSubClass == 1
		&& desc->bInterfaceProtocol == 1;
पूर्ण

अटल bool is_audio(काष्ठा usb_पूर्णांकerface_descriptor *desc)
अणु
	वापस desc->bInterfaceClass == USB_CLASS_AUDIO;
पूर्ण

अटल bool is_uac3_config(काष्ठा usb_पूर्णांकerface_descriptor *desc)
अणु
	वापस desc->bInterfaceProtocol == UAC_VERSION_3;
पूर्ण

पूर्णांक usb_choose_configuration(काष्ठा usb_device *udev)
अणु
	पूर्णांक i;
	पूर्णांक num_configs;
	पूर्णांक insufficient_घातer = 0;
	काष्ठा usb_host_config *c, *best;

	अगर (usb_device_is_owned(udev))
		वापस 0;

	best = शून्य;
	c = udev->config;
	num_configs = udev->descriptor.bNumConfigurations;
	क्रम (i = 0; i < num_configs; (i++, c++)) अणु
		काष्ठा usb_पूर्णांकerface_descriptor	*desc = शून्य;

		/* It's possible that a config has no पूर्णांकerfaces! */
		अगर (c->desc.bNumInterfaces > 0)
			desc = &c->पूर्णांकf_cache[0]->altsetting->desc;

		/*
		 * HP's USB bus-घातered keyboard has only one configuration
		 * and it claims to be self-घातered; other devices may have
		 * similar errors in their descriptors.  If the next test
		 * were allowed to execute, such configurations would always
		 * be rejected and the devices would not work as expected.
		 * In the meanसमय, we run the risk of selecting a config
		 * that requires बाह्यal घातer at a समय when that घातer
		 * isn't available.  It seems to be the lesser of two evils.
		 *
		 * Bugzilla #6448 reports a device that appears to crash
		 * when it receives a GET_DEVICE_STATUS request!  We करोn't
		 * have any other way to tell whether a device is self-घातered,
		 * but since we करोn't use that inक्रमmation anywhere but here,
		 * the call has been हटाओd.
		 *
		 * Maybe the GET_DEVICE_STATUS call and the test below can
		 * be reinstated when device firmwares become more reliable.
		 * Don't hold your breath.
		 */
#अगर 0
		/* Rule out self-घातered configs क्रम a bus-घातered device */
		अगर (bus_घातered && (c->desc.bmAttributes &
					USB_CONFIG_ATT_SELFPOWER))
			जारी;
#पूर्ण_अगर

		/*
		 * The next test may not be as effective as it should be.
		 * Some hubs have errors in their descriptor, claiming
		 * to be self-घातered when they are really bus-घातered.
		 * We will overestimate the amount of current such hubs
		 * make available क्रम each port.
		 *
		 * This is a fairly benign sort of failure.  It won't
		 * cause us to reject configurations that we should have
		 * accepted.
		 */

		/* Rule out configs that draw too much bus current */
		अगर (usb_get_max_घातer(udev, c) > udev->bus_mA) अणु
			insufficient_घातer++;
			जारी;
		पूर्ण

		/*
		 * Select first configuration as शेष क्रम audio so that
		 * devices that करोn't comply with UAC3 protocol are supported.
		 * But, still iterate through other configurations and
		 * select UAC3 compliant config अगर present.
		 */
		अगर (desc && is_audio(desc)) अणु
			/* Always prefer the first found UAC3 config */
			अगर (is_uac3_config(desc)) अणु
				best = c;
				अवरोध;
			पूर्ण

			/* If there is no UAC3 config, prefer the first config */
			अन्यथा अगर (i == 0)
				best = c;

			/* Unconditional जारी, because the rest of the code
			 * in the loop is irrelevant क्रम audio devices, and
			 * because it can reassign best, which क्रम audio devices
			 * we करोn't want.
			 */
			जारी;
		पूर्ण

		/* When the first config's first interface is one of Microsoft's
		 * pet nonstandard Ethernet-over-USB protocols, ignore it unless
		 * this kernel has enabled the necessary host side driver.
		 * But: Don't ignore it if it's the only config.
		 */
		अगर (i == 0 && num_configs > 1 && desc &&
				(is_rndis(desc) || is_activesync(desc))) अणु
#अगर !defined(CONFIG_USB_NET_RNDIS_HOST) && !defined(CONFIG_USB_NET_RNDIS_HOST_MODULE)
			जारी;
#अन्यथा
			best = c;
#पूर्ण_अगर
		पूर्ण

		/* From the reमुख्यing configs, choose the first one whose
		 * first पूर्णांकerface is क्रम a non-venकरोr-specअगरic class.
		 * Reason: Linux is more likely to have a class driver
		 * than a venकरोr-specअगरic driver. */
		अन्यथा अगर (udev->descriptor.bDeviceClass !=
						USB_CLASS_VENDOR_SPEC &&
				(desc && desc->bInterfaceClass !=
						USB_CLASS_VENDOR_SPEC)) अणु
			best = c;
			अवरोध;
		पूर्ण

		/* If all the reमुख्यing configs are venकरोr-specअगरic,
		 * choose the first one. */
		अन्यथा अगर (!best)
			best = c;
	पूर्ण

	अगर (insufficient_घातer > 0)
		dev_info(&udev->dev, "rejected %d configuration%s "
			"due to insufficient available bus power\n",
			insufficient_घातer, plural(insufficient_घातer));

	अगर (best) अणु
		i = best->desc.bConfigurationValue;
		dev_dbg(&udev->dev,
			"configuration #%d chosen from %d choice%s\n",
			i, num_configs, plural(num_configs));
	पूर्ण अन्यथा अणु
		i = -1;
		dev_warn(&udev->dev,
			"no configuration chosen from %d choice%s\n",
			num_configs, plural(num_configs));
	पूर्ण
	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(usb_choose_configuration);

अटल पूर्णांक __check_क्रम_non_generic_match(काष्ठा device_driver *drv, व्योम *data)
अणु
	काष्ठा usb_device *udev = data;
	काष्ठा usb_device_driver *udrv;

	अगर (!is_usb_device_driver(drv))
		वापस 0;
	udrv = to_usb_device_driver(drv);
	अगर (udrv == &usb_generic_driver)
		वापस 0;
	वापस usb_driver_applicable(udev, udrv);
पूर्ण

अटल bool usb_generic_driver_match(काष्ठा usb_device *udev)
अणु
	अगर (udev->use_generic_driver)
		वापस true;

	/*
	 * If any other driver wants the device, leave the device to this other
	 * driver.
	 */
	अगर (bus_क्रम_each_drv(&usb_bus_type, शून्य, udev, __check_क्रम_non_generic_match))
		वापस false;

	वापस true;
पूर्ण

पूर्णांक usb_generic_driver_probe(काष्ठा usb_device *udev)
अणु
	पूर्णांक err, c;

	/* Choose and set the configuration.  This रेजिस्टरs the पूर्णांकerfaces
	 * with the driver core and lets पूर्णांकerface drivers bind to them.
	 */
	अगर (udev->authorized == 0)
		dev_err(&udev->dev, "Device is not authorized for usage\n");
	अन्यथा अणु
		c = usb_choose_configuration(udev);
		अगर (c >= 0) अणु
			err = usb_set_configuration(udev, c);
			अगर (err && err != -ENODEV) अणु
				dev_err(&udev->dev, "can't set config #%d, error %d\n",
					c, err);
				/* This need not be fatal.  The user can try to
				 * set other configurations. */
			पूर्ण
		पूर्ण
	पूर्ण
	/* USB device state == configured ... usable */
	usb_notअगरy_add_device(udev);

	वापस 0;
पूर्ण

व्योम usb_generic_driver_disconnect(काष्ठा usb_device *udev)
अणु
	usb_notअगरy_हटाओ_device(udev);

	/* अगर this is only an unbind, not a physical disconnect, then
	 * unconfigure the device */
	अगर (udev->actconfig)
		usb_set_configuration(udev, -1);
पूर्ण

#अगर_घोषित	CONFIG_PM

पूर्णांक usb_generic_driver_suspend(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	पूर्णांक rc;

	/* Normal USB devices suspend through their upstream port.
	 * Root hubs करोn't have upstream ports to suspend,
	 * so we have to shut करोwn their करोwnstream HC-to-USB
	 * पूर्णांकerfaces manually by करोing a bus (or "global") suspend.
	 */
	अगर (!udev->parent)
		rc = hcd_bus_suspend(udev, msg);

	/*
	 * Non-root USB2 devices करोn't need to करो anything क्रम FREEZE
	 * or PRETHAW. USB3 devices करोn't support global suspend and
	 * needs to be selectively suspended.
	 */
	अन्यथा अगर ((msg.event == PM_EVENT_FREEZE || msg.event == PM_EVENT_PRETHAW)
		 && (udev->speed < USB_SPEED_SUPER))
		rc = 0;
	अन्यथा
		rc = usb_port_suspend(udev, msg);

	अगर (rc == 0)
		usbfs_notअगरy_suspend(udev);
	वापस rc;
पूर्ण

पूर्णांक usb_generic_driver_resume(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	पूर्णांक rc;

	/* Normal USB devices resume/reset through their upstream port.
	 * Root hubs करोn't have upstream ports to resume or reset,
	 * so we have to start up their करोwnstream HC-to-USB
	 * पूर्णांकerfaces manually by करोing a bus (or "global") resume.
	 */
	अगर (!udev->parent)
		rc = hcd_bus_resume(udev, msg);
	अन्यथा
		rc = usb_port_resume(udev, msg);

	अगर (rc == 0)
		usbfs_notअगरy_resume(udev);
	वापस rc;
पूर्ण

#पूर्ण_अगर	/* CONFIG_PM */

काष्ठा usb_device_driver usb_generic_driver = अणु
	.name =	"usb",
	.match = usb_generic_driver_match,
	.probe = usb_generic_driver_probe,
	.disconnect = usb_generic_driver_disconnect,
#अगर_घोषित	CONFIG_PM
	.suspend = usb_generic_driver_suspend,
	.resume = usb_generic_driver_resume,
#पूर्ण_अगर
	.supports_स्वतःsuspend = 1,
पूर्ण;
