<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश "usb.h"

अटल पूर्णांक uas_is_पूर्णांकerface(काष्ठा usb_host_पूर्णांकerface *पूर्णांकf)
अणु
	वापस (पूर्णांकf->desc.bInterfaceClass == USB_CLASS_MASS_STORAGE &&
		पूर्णांकf->desc.bInterfaceSubClass == USB_SC_SCSI &&
		पूर्णांकf->desc.bInterfaceProtocol == USB_PR_UAS);
पूर्ण

अटल काष्ठा usb_host_पूर्णांकerface *uas_find_uas_alt_setting(
		काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < पूर्णांकf->num_altsetting; i++) अणु
		काष्ठा usb_host_पूर्णांकerface *alt = &पूर्णांकf->altsetting[i];

		अगर (uas_is_पूर्णांकerface(alt))
			वापस alt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक uas_find_endpoपूर्णांकs(काष्ठा usb_host_पूर्णांकerface *alt,
			      काष्ठा usb_host_endpoपूर्णांक *eps[])
अणु
	काष्ठा usb_host_endpoपूर्णांक *endpoपूर्णांक = alt->endpoपूर्णांक;
	अचिन्हित i, n_endpoपूर्णांकs = alt->desc.bNumEndpoपूर्णांकs;

	क्रम (i = 0; i < n_endpoपूर्णांकs; i++) अणु
		अचिन्हित अक्षर *extra = endpoपूर्णांक[i].extra;
		पूर्णांक len = endpoपूर्णांक[i].extralen;
		जबतक (len >= 3) अणु
			अगर (extra[1] == USB_DT_PIPE_USAGE) अणु
				अचिन्हित pipe_id = extra[2];
				अगर (pipe_id > 0 && pipe_id < 5)
					eps[pipe_id - 1] = &endpoपूर्णांक[i];
				अवरोध;
			पूर्ण
			len -= extra[0];
			extra += extra[0];
		पूर्ण
	पूर्ण

	अगर (!eps[0] || !eps[1] || !eps[2] || !eps[3])
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक uas_use_uas_driver(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			      स्थिर काष्ठा usb_device_id *id,
			      अचिन्हित दीर्घ *flags_ret)
अणु
	काष्ठा usb_host_endpoपूर्णांक *eps[4] = अणु पूर्ण;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);
	अचिन्हित दीर्घ flags = id->driver_info;
	काष्ठा usb_host_पूर्णांकerface *alt;
	पूर्णांक r;

	alt = uas_find_uas_alt_setting(पूर्णांकf);
	अगर (!alt)
		वापस 0;

	r = uas_find_endpoपूर्णांकs(alt, eps);
	अगर (r < 0)
		वापस 0;

	/*
	 * ASMedia has a number of usb3 to sata bridge chips, at the समय of
	 * this writing the following versions exist:
	 * ASM1051 - no uas support version
	 * ASM1051 - with broken (*) uas support
	 * ASM1053 - with working uas support, but problems with large xfers
	 * ASM1153 - with working uas support
	 *
	 * Devices with these chips re-use a number of device-ids over the
	 * entire line, so the device-id is useless to determine अगर we're
	 * dealing with an ASM1051 (which we want to aव्योम).
	 *
	 * The ASM1153 can be identअगरied by config.MaxPower == 0,
	 * where as the ASM105x models have config.MaxPower == 36.
	 *
	 * Dअगरferentiating between the ASM1053 and ASM1051 is trickier, when
	 * connected over USB-3 we can look at the number of streams supported,
	 * ASM1051 supports 32 streams, where as early ASM1053 versions support
	 * 16 streams, newer ASM1053-s also support 32 streams, but have a
	 * dअगरferent prod-id.
	 *
	 * (*) ASM1051 chips करो work with UAS with some disks (with the
	 *     US_FL_NO_REPORT_OPCODES quirk), but are broken with other disks
	 */
	अगर (le16_to_cpu(udev->descriptor.idVenकरोr) == 0x174c &&
			(le16_to_cpu(udev->descriptor.idProduct) == 0x5106 ||
			 le16_to_cpu(udev->descriptor.idProduct) == 0x55aa)) अणु
		अगर (udev->actconfig->desc.bMaxPower == 0) अणु
			/* ASM1153, करो nothing */
		पूर्ण अन्यथा अगर (udev->speed < USB_SPEED_SUPER) अणु
			/* No streams info, assume ASM1051 */
			flags |= US_FL_IGNORE_UAS;
		पूर्ण अन्यथा अगर (usb_ss_max_streams(&eps[1]->ss_ep_comp) == 32) अणु
			/* Possibly an ASM1051, disable uas */
			flags |= US_FL_IGNORE_UAS;
		पूर्ण अन्यथा अणु
			/* ASM1053, these have issues with large transfers */
			flags |= US_FL_MAX_SECTORS_240;
		पूर्ण
	पूर्ण

	/* All Seagate disk enclosures have broken ATA pass-through support */
	अगर (le16_to_cpu(udev->descriptor.idVenकरोr) == 0x0bc2)
		flags |= US_FL_NO_ATA_1X;

	usb_stor_adjust_quirks(udev, &flags);

	अगर (flags & US_FL_IGNORE_UAS) अणु
		dev_warn(&udev->dev,
			"UAS is ignored for this device, using usb-storage instead\n");
		वापस 0;
	पूर्ण

	अगर (udev->bus->sg_tablesize == 0) अणु
		dev_warn(&udev->dev,
			"The driver for the USB controller %s does not support scatter-gather which is\n",
			hcd->driver->description);
		dev_warn(&udev->dev,
			"required by the UAS driver. Please try an other USB controller if you wish to use UAS.\n");
		वापस 0;
	पूर्ण

	अगर (udev->speed >= USB_SPEED_SUPER && !hcd->can_करो_streams) अणु
		dev_warn(&udev->dev,
			"USB controller %s does not support streams, which are required by the UAS driver.\n",
			hcd_to_bus(hcd)->bus_name);
		dev_warn(&udev->dev,
			"Please try an other USB controller if you wish to use UAS.\n");
		वापस 0;
	पूर्ण

	अगर (flags_ret)
		*flags_ret = flags;

	वापस 1;
पूर्ण
