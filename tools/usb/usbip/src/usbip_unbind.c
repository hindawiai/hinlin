<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#समावेश <libudev.h>

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>

#समावेश <getopt.h>

#समावेश "usbip_common.h"
#समावेश "utils.h"
#समावेश "usbip.h"
#समावेश "sysfs_utils.h"

अटल स्थिर अक्षर usbip_unbind_usage_string[] =
	"usbip unbind <args>\n"
	"    -b, --busid=<busid>    Unbind " USBIP_HOST_DRV_NAME ".ko from "
	"device on <busid>\n";

व्योम usbip_unbind_usage(व्योम)
अणु
	म_लिखो("usage: %s", usbip_unbind_usage_string);
पूर्ण

अटल पूर्णांक unbind_device(अक्षर *busid)
अणु
	अक्षर bus_type[] = "usb";
	पूर्णांक rc, ret = -1;

	अक्षर unbind_attr_name[] = "unbind";
	अक्षर unbind_attr_path[SYSFS_PATH_MAX];
	अक्षर rebind_attr_name[] = "rebind";
	अक्षर rebind_attr_path[SYSFS_PATH_MAX];

	काष्ठा udev *udev;
	काष्ठा udev_device *dev;
	स्थिर अक्षर *driver;

	/* Create libudev context. */
	udev = udev_new();

	/* Check whether the device with this bus ID exists. */
	dev = udev_device_new_from_subप्रणाली_sysname(udev, "usb", busid);
	अगर (!dev) अणु
		err("device with the specified bus ID does not exist");
		जाओ err_बंद_udev;
	पूर्ण

	/* Check whether the device is using usbip-host driver. */
	driver = udev_device_get_driver(dev);
	अगर (!driver || म_भेद(driver, "usbip-host")) अणु
		err("device is not bound to usbip-host driver");
		जाओ err_बंद_udev;
	पूर्ण

	/* Unbind device from driver. */
	snम_लिखो(unbind_attr_path, माप(unbind_attr_path), "%s/%s/%s/%s/%s/%s",
		 SYSFS_MNT_PATH, SYSFS_BUS_NAME, bus_type, SYSFS_DRIVERS_NAME,
		 USBIP_HOST_DRV_NAME, unbind_attr_name);

	rc = ग_लिखो_sysfs_attribute(unbind_attr_path, busid, म_माप(busid));
	अगर (rc < 0) अणु
		err("error unbinding device %s from driver", busid);
		जाओ err_बंद_udev;
	पूर्ण

	/* Notअगरy driver of unbind. */
	rc = modअगरy_match_busid(busid, 0);
	अगर (rc < 0) अणु
		err("unable to unbind device on %s", busid);
		जाओ err_बंद_udev;
	पूर्ण

	/* Trigger new probing. */
	snम_लिखो(rebind_attr_path, माप(unbind_attr_path), "%s/%s/%s/%s/%s/%s",
			SYSFS_MNT_PATH, SYSFS_BUS_NAME, bus_type, SYSFS_DRIVERS_NAME,
			USBIP_HOST_DRV_NAME, rebind_attr_name);

	rc = ग_लिखो_sysfs_attribute(rebind_attr_path, busid, म_माप(busid));
	अगर (rc < 0) अणु
		err("error rebinding");
		जाओ err_बंद_udev;
	पूर्ण

	ret = 0;
	info("unbind device on busid %s: complete", busid);

err_बंद_udev:
	udev_device_unref(dev);
	udev_unref(udev);

	वापस ret;
पूर्ण

पूर्णांक usbip_unbind(पूर्णांक argc, अक्षर *argv[])
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
			ret = unbind_device(optarg);
			जाओ out;
		शेष:
			जाओ err_out;
		पूर्ण
	पूर्ण

err_out:
	usbip_unbind_usage();
out:
	वापस ret;
पूर्ण
