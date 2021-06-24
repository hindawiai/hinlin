<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#समावेश <libudev.h>

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <getopt.h>

#समावेश "usbip_common.h"
#समावेश "utils.h"
#समावेश "usbip.h"
#समावेश "sysfs_utils.h"

क्रमागत unbind_status अणु
	UNBIND_ST_OK,
	UNBIND_ST_USBIP_HOST,
	UNBIND_ST_FAILED
पूर्ण;

अटल स्थिर अक्षर usbip_bind_usage_string[] =
	"usbip bind <args>\n"
	"    -b, --busid=<busid>    Bind " USBIP_HOST_DRV_NAME ".ko to device "
	"on <busid>\n";

व्योम usbip_bind_usage(व्योम)
अणु
	म_लिखो("usage: %s", usbip_bind_usage_string);
पूर्ण

/* call at unbound state */
अटल पूर्णांक bind_usbip(अक्षर *busid)
अणु
	अक्षर attr_name[] = "bind";
	अक्षर bind_attr_path[SYSFS_PATH_MAX];
	पूर्णांक rc = -1;

	snम_लिखो(bind_attr_path, माप(bind_attr_path), "%s/%s/%s/%s/%s/%s",
		 SYSFS_MNT_PATH, SYSFS_BUS_NAME, SYSFS_BUS_TYPE,
		 SYSFS_DRIVERS_NAME, USBIP_HOST_DRV_NAME, attr_name);

	rc = ग_लिखो_sysfs_attribute(bind_attr_path, busid, म_माप(busid));
	अगर (rc < 0) अणु
		err("error binding device %s to driver: %s", busid,
		    म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* buggy driver may cause dead lock */
अटल पूर्णांक unbind_other(अक्षर *busid)
अणु
	क्रमागत unbind_status status = UNBIND_ST_OK;

	अक्षर attr_name[] = "unbind";
	अक्षर unbind_attr_path[SYSFS_PATH_MAX];
	पूर्णांक rc = -1;

	काष्ठा udev *udev;
	काष्ठा udev_device *dev;
	स्थिर अक्षर *driver;
	स्थिर अक्षर *bDevClass;

	/* Create libudev context. */
	udev = udev_new();

	/* Get the device. */
	dev = udev_device_new_from_subप्रणाली_sysname(udev, "usb", busid);
	अगर (!dev) अणु
		dbg("unable to find device with bus ID %s", busid);
		जाओ err_बंद_busid_dev;
	पूर्ण

	/* Check what kind of device it is. */
	bDevClass  = udev_device_get_sysattr_value(dev, "bDeviceClass");
	अगर (!bDevClass) अणु
		dbg("unable to get bDevClass device attribute");
		जाओ err_बंद_busid_dev;
	पूर्ण

	अगर (!म_भेदन(bDevClass, "09", म_माप(bDevClass))) अणु
		dbg("skip unbinding of hub");
		जाओ err_बंद_busid_dev;
	पूर्ण

	/* Get the device driver. */
	driver = udev_device_get_driver(dev);
	अगर (!driver) अणु
		/* No driver bound to this device. */
		जाओ out;
	पूर्ण

	अगर (!म_भेदन(USBIP_HOST_DRV_NAME, driver,
				म_माप(USBIP_HOST_DRV_NAME))) अणु
		/* Alपढ़ोy bound to usbip-host. */
		status = UNBIND_ST_USBIP_HOST;
		जाओ out;
	पूर्ण

	/* Unbind device from driver. */
	snम_लिखो(unbind_attr_path, माप(unbind_attr_path), "%s/%s/%s/%s/%s/%s",
		 SYSFS_MNT_PATH, SYSFS_BUS_NAME, SYSFS_BUS_TYPE,
		 SYSFS_DRIVERS_NAME, driver, attr_name);

	rc = ग_लिखो_sysfs_attribute(unbind_attr_path, busid, म_माप(busid));
	अगर (rc < 0) अणु
		err("error unbinding device %s from driver", busid);
		जाओ err_बंद_busid_dev;
	पूर्ण

	जाओ out;

err_बंद_busid_dev:
	status = UNBIND_ST_FAILED;
out:
	udev_device_unref(dev);
	udev_unref(udev);

	वापस status;
पूर्ण

अटल पूर्णांक bind_device(अक्षर *busid)
अणु
	पूर्णांक rc;
	काष्ठा udev *udev;
	काष्ठा udev_device *dev;
	स्थिर अक्षर *devpath;

	/* Check whether the device with this bus ID exists. */
	udev = udev_new();
	dev = udev_device_new_from_subप्रणाली_sysname(udev, "usb", busid);
	अगर (!dev) अणु
		err("device with the specified bus ID does not exist");
		वापस -1;
	पूर्ण
	devpath = udev_device_get_devpath(dev);
	udev_unref(udev);

	/* If the device is alपढ़ोy attached to vhci_hcd - bail out */
	अगर (म_माला(devpath, USBIP_VHCI_DRV_NAME)) अणु
		err("bind loop detected: device: %s is attached to %s\n",
		    devpath, USBIP_VHCI_DRV_NAME);
		वापस -1;
	पूर्ण

	rc = unbind_other(busid);
	अगर (rc == UNBIND_ST_FAILED) अणु
		err("could not unbind driver from device on busid %s", busid);
		वापस -1;
	पूर्ण अन्यथा अगर (rc == UNBIND_ST_USBIP_HOST) अणु
		err("device on busid %s is already bound to %s", busid,
		    USBIP_HOST_DRV_NAME);
		वापस -1;
	पूर्ण

	rc = modअगरy_match_busid(busid, 1);
	अगर (rc < 0) अणु
		err("unable to bind device on %s", busid);
		वापस -1;
	पूर्ण

	rc = bind_usbip(busid);
	अगर (rc < 0) अणु
		err("could not bind device to %s", USBIP_HOST_DRV_NAME);
		modअगरy_match_busid(busid, 0);
		वापस -1;
	पूर्ण

	info("bind device on busid %s: complete", busid);

	वापस 0;
पूर्ण

पूर्णांक usbip_bind(पूर्णांक argc, अक्षर *argv[])
अणु
	अटल स्थिर काष्ठा option opts[] = अणु
		अणु "busid", required_argument, शून्य, 'b' पूर्ण,
		अणु शून्य,    0,                 शून्य,  0  पूर्ण
	पूर्ण;

	पूर्णांक opt;
	पूर्णांक ret = -1;

	क्रम (;;) अणु
		opt = getopt_दीर्घ(argc, argv, "b:", opts, शून्य);

		अगर (opt == -1)
			अवरोध;

		चयन (opt) अणु
		हाल 'b':
			ret = bind_device(optarg);
			जाओ out;
		शेष:
			जाओ err_out;
		पूर्ण
	पूर्ण

err_out:
	usbip_bind_usage();
out:
	वापस ret;
पूर्ण
