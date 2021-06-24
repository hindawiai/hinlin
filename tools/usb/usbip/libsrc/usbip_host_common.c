<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 *
 * Refactored from usbip_host_driver.c, which is:
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>

#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>

#समावेश <libudev.h>

#समावेश "usbip_common.h"
#समावेश "usbip_host_common.h"
#समावेश "list.h"
#समावेश "sysfs_utils.h"

बाह्य काष्ठा udev *udev_context;

अटल पूर्णांक32_t पढ़ो_attr_usbip_status(काष्ठा usbip_usb_device *udev)
अणु
	अक्षर status_attr_path[SYSFS_PATH_MAX];
	पूर्णांक size;
	पूर्णांक fd;
	पूर्णांक length;
	अक्षर status[2] = अणु 0 पूर्ण;
	पूर्णांक value = 0;

	size = snम_लिखो(status_attr_path, माप(status_attr_path),
			"%s/usbip_status", udev->path);
	अगर (size < 0 || (अचिन्हित पूर्णांक)size >= माप(status_attr_path)) अणु
		err("usbip_status path length %i >= %lu or < 0", size,
		    (दीर्घ अचिन्हित)माप(status_attr_path));
		वापस -1;
	पूर्ण


	fd = खोलो(status_attr_path, O_RDONLY);
	अगर (fd < 0) अणु
		err("error opening attribute %s", status_attr_path);
		वापस -1;
	पूर्ण

	length = पढ़ो(fd, status, 1);
	अगर (length < 0) अणु
		err("error reading attribute %s", status_attr_path);
		बंद(fd);
		वापस -1;
	पूर्ण

	value = म_से_प(status);
	बंद(fd);
	वापस value;
पूर्ण

अटल
काष्ठा usbip_exported_device *usbip_exported_device_new(
		काष्ठा usbip_host_driver *hdriver, स्थिर अक्षर *sdevpath)
अणु
	काष्ठा usbip_exported_device *edev = शून्य;
	काष्ठा usbip_exported_device *edev_old;
	माप_प्रकार size;
	पूर्णांक i;

	edev = सुस्मृति(1, माप(काष्ठा usbip_exported_device));

	edev->sudev =
		udev_device_new_from_syspath(udev_context, sdevpath);
	अगर (!edev->sudev) अणु
		err("udev_device_new_from_syspath: %s", sdevpath);
		जाओ err;
	पूर्ण

	अगर (hdriver->ops.पढ़ो_device(edev->sudev, &edev->udev) < 0)
		जाओ err;

	edev->status = पढ़ो_attr_usbip_status(&edev->udev);
	अगर (edev->status < 0)
		जाओ err;

	/* पुनः_स्मृतिate buffer to include usb पूर्णांकerface data */
	size = माप(काष्ठा usbip_exported_device) +
		edev->udev.bNumInterfaces * माप(काष्ठा usbip_usb_पूर्णांकerface);

	edev_old = edev;
	edev = पुनः_स्मृति(edev, size);
	अगर (!edev) अणु
		edev = edev_old;
		dbg("realloc failed");
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < edev->udev.bNumInterfaces; i++) अणु
		/* vudc करोes not support पढ़ोing पूर्णांकerfaces */
		अगर (!hdriver->ops.पढ़ो_पूर्णांकerface)
			अवरोध;
		hdriver->ops.पढ़ो_पूर्णांकerface(&edev->udev, i, &edev->uinf[i]);
	पूर्ण

	वापस edev;
err:
	अगर (edev->sudev)
		udev_device_unref(edev->sudev);
	अगर (edev)
		मुक्त(edev);

	वापस शून्य;
पूर्ण

अटल पूर्णांक refresh_exported_devices(काष्ठा usbip_host_driver *hdriver)
अणु
	काष्ठा usbip_exported_device *edev;
	काष्ठा udev_क्रमागतerate *क्रमागतerate;
	काष्ठा udev_list_entry *devices, *dev_list_entry;
	काष्ठा udev_device *dev;
	स्थिर अक्षर *path;

	क्रमागतerate = udev_क्रमागतerate_new(udev_context);
	udev_क्रमागतerate_add_match_subप्रणाली(क्रमागतerate, hdriver->udev_subप्रणाली);
	udev_क्रमागतerate_scan_devices(क्रमागतerate);

	devices = udev_क्रमागतerate_get_list_entry(क्रमागतerate);

	udev_list_entry_क्रमeach(dev_list_entry, devices) अणु
		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev_context,
						   path);
		अगर (dev == शून्य)
			जारी;

		/* Check whether device uses usbip driver. */
		अगर (hdriver->ops.is_my_device(dev)) अणु
			edev = usbip_exported_device_new(hdriver, path);
			अगर (!edev) अणु
				dbg("usbip_exported_device_new failed");
				जारी;
			पूर्ण

			list_add(&edev->node, &hdriver->edev_list);
			hdriver->ndevs++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम usbip_exported_device_destroy(काष्ठा list_head *devs)
अणु
	काष्ठा list_head *i, *पंचांगp;
	काष्ठा usbip_exported_device *edev;

	list_क्रम_each_safe(i, पंचांगp, devs) अणु
		edev = list_entry(i, काष्ठा usbip_exported_device, node);
		list_del(i);
		मुक्त(edev);
	पूर्ण
पूर्ण

पूर्णांक usbip_generic_driver_खोलो(काष्ठा usbip_host_driver *hdriver)
अणु
	पूर्णांक rc;

	udev_context = udev_new();
	अगर (!udev_context) अणु
		err("udev_new failed");
		वापस -1;
	पूर्ण

	rc = refresh_exported_devices(hdriver);
	अगर (rc < 0)
		जाओ err;
	वापस 0;
err:
	udev_unref(udev_context);
	वापस -1;
पूर्ण

व्योम usbip_generic_driver_बंद(काष्ठा usbip_host_driver *hdriver)
अणु
	अगर (!hdriver)
		वापस;

	usbip_exported_device_destroy(&hdriver->edev_list);

	udev_unref(udev_context);
पूर्ण

पूर्णांक usbip_generic_refresh_device_list(काष्ठा usbip_host_driver *hdriver)
अणु
	पूर्णांक rc;

	usbip_exported_device_destroy(&hdriver->edev_list);

	hdriver->ndevs = 0;
	INIT_LIST_HEAD(&hdriver->edev_list);

	rc = refresh_exported_devices(hdriver);
	अगर (rc < 0)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक usbip_export_device(काष्ठा usbip_exported_device *edev, पूर्णांक sockfd)
अणु
	अक्षर attr_name[] = "usbip_sockfd";
	अक्षर sockfd_attr_path[SYSFS_PATH_MAX];
	पूर्णांक size;
	अक्षर sockfd_buff[30];
	पूर्णांक ret;

	अगर (edev->status != SDEV_ST_AVAILABLE) अणु
		dbg("device not available: %s", edev->udev.busid);
		चयन (edev->status) अणु
		हाल SDEV_ST_ERROR:
			dbg("status SDEV_ST_ERROR");
			ret = ST_DEV_ERR;
			अवरोध;
		हाल SDEV_ST_USED:
			dbg("status SDEV_ST_USED");
			ret = ST_DEV_BUSY;
			अवरोध;
		शेष:
			dbg("status unknown: 0x%x", edev->status);
			ret = -1;
		पूर्ण
		वापस ret;
	पूर्ण

	/* only the first पूर्णांकerface is true */
	size = snम_लिखो(sockfd_attr_path, माप(sockfd_attr_path), "%s/%s",
			edev->udev.path, attr_name);
	अगर (size < 0 || (अचिन्हित पूर्णांक)size >= माप(sockfd_attr_path)) अणु
		err("exported device path length %i >= %lu or < 0", size,
		    (दीर्घ अचिन्हित)माप(sockfd_attr_path));
		वापस -1;
	पूर्ण

	size = snम_लिखो(sockfd_buff, माप(sockfd_buff), "%d\n", sockfd);
	अगर (size < 0 || (अचिन्हित पूर्णांक)size >= माप(sockfd_buff)) अणु
		err("socket length %i >= %lu or < 0", size,
		    (दीर्घ अचिन्हित)माप(sockfd_buff));
		वापस -1;
	पूर्ण

	ret = ग_लिखो_sysfs_attribute(sockfd_attr_path, sockfd_buff,
				    म_माप(sockfd_buff));
	अगर (ret < 0) अणु
		err("write_sysfs_attribute failed: sockfd %s to %s",
		    sockfd_buff, sockfd_attr_path);
		वापस ret;
	पूर्ण

	info("connect: %s", edev->udev.busid);

	वापस ret;
पूर्ण

काष्ठा usbip_exported_device *usbip_generic_get_device(
		काष्ठा usbip_host_driver *hdriver, पूर्णांक num)
अणु
	काष्ठा list_head *i;
	काष्ठा usbip_exported_device *edev;
	पूर्णांक cnt = 0;

	list_क्रम_each(i, &hdriver->edev_list) अणु
		edev = list_entry(i, काष्ठा usbip_exported_device, node);
		अगर (num == cnt)
			वापस edev;
		cnt++;
	पूर्ण

	वापस शून्य;
पूर्ण
