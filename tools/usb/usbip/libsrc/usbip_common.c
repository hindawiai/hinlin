<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005-2007 Takahiro Hirofuchi
 */

#समावेश <libudev.h>
#समावेश "usbip_common.h"
#समावेश "names.h"

#अघोषित  PROGNAME
#घोषणा PROGNAME "libusbip"

पूर्णांक usbip_use_syslog;
पूर्णांक usbip_use_मानक_त्रुटि;
पूर्णांक usbip_use_debug;

बाह्य काष्ठा udev *udev_context;

काष्ठा speed_string अणु
	पूर्णांक num;
	अक्षर *speed;
	अक्षर *desc;
पूर्ण;

अटल स्थिर काष्ठा speed_string speed_strings[] = अणु
	अणु USB_SPEED_UNKNOWN, "unknown", "Unknown Speed"पूर्ण,
	अणु USB_SPEED_LOW,  "1.5", "Low Speed(1.5Mbps)"  पूर्ण,
	अणु USB_SPEED_FULL, "12",  "Full Speed(12Mbps)" पूर्ण,
	अणु USB_SPEED_HIGH, "480", "High Speed(480Mbps)" पूर्ण,
	अणु USB_SPEED_WIRELESS, "53.3-480", "Wireless"पूर्ण,
	अणु USB_SPEED_SUPER, "5000", "Super Speed(5000Mbps)" पूर्ण,
	अणु 0, शून्य, शून्य पूर्ण
पूर्ण;

काष्ठा portst_string अणु
	पूर्णांक num;
	अक्षर *desc;
पूर्ण;

अटल काष्ठा portst_string portst_strings[] = अणु
	अणु SDEV_ST_AVAILABLE,	"Device Available" पूर्ण,
	अणु SDEV_ST_USED,		"Device in Use" पूर्ण,
	अणु SDEV_ST_ERROR,	"Device Error"पूर्ण,
	अणु VDEV_ST_शून्य,		"Port Available"पूर्ण,
	अणु VDEV_ST_NOTASSIGNED,	"Port Initializing"पूर्ण,
	अणु VDEV_ST_USED,		"Port in Use"पूर्ण,
	अणु VDEV_ST_ERROR,	"Port Error"पूर्ण,
	अणु 0, शून्यपूर्ण
पूर्ण;

स्थिर अक्षर *usbip_status_string(पूर्णांक32_t status)
अणु
	क्रम (पूर्णांक i = 0; portst_strings[i].desc != शून्य; i++)
		अगर (portst_strings[i].num == status)
			वापस portst_strings[i].desc;

	वापस "Unknown Status";
पूर्ण

स्थिर अक्षर *usbip_speed_string(पूर्णांक num)
अणु
	क्रम (पूर्णांक i = 0; speed_strings[i].speed != शून्य; i++)
		अगर (speed_strings[i].num == num)
			वापस speed_strings[i].desc;

	वापस "Unknown Speed";
पूर्ण

काष्ठा op_common_status_string अणु
	पूर्णांक num;
	अक्षर *desc;
पूर्ण;

अटल काष्ठा op_common_status_string op_common_status_strings[] = अणु
	अणु ST_OK,	"Request Completed Successfully" पूर्ण,
	अणु ST_NA,	"Request Failed" पूर्ण,
	अणु ST_DEV_BUSY,	"Device busy (exported)" पूर्ण,
	अणु ST_DEV_ERR,	"Device in error state" पूर्ण,
	अणु ST_NODEV,	"Device not found" पूर्ण,
	अणु ST_ERROR,	"Unexpected response" पूर्ण,
	अणु 0, शून्यपूर्ण
पूर्ण;

स्थिर अक्षर *usbip_op_common_status_string(पूर्णांक status)
अणु
	क्रम (पूर्णांक i = 0; op_common_status_strings[i].desc != शून्य; i++)
		अगर (op_common_status_strings[i].num == status)
			वापस op_common_status_strings[i].desc;

	वापस "Unknown Op Common Status";
पूर्ण

#घोषणा DBG_UDEV_INTEGER(name)\
	dbg("%-20s = %x", to_string(name), (पूर्णांक) udev->name)

#घोषणा DBG_UINF_INTEGER(name)\
	dbg("%-20s = %x", to_string(name), (पूर्णांक) uinf->name)

व्योम dump_usb_पूर्णांकerface(काष्ठा usbip_usb_पूर्णांकerface *uinf)
अणु
	अक्षर buff[100];

	usbip_names_get_class(buff, माप(buff),
			uinf->bInterfaceClass,
			uinf->bInterfaceSubClass,
			uinf->bInterfaceProtocol);
	dbg("%-20s = %s", "Interface(C/SC/P)", buff);
पूर्ण

व्योम dump_usb_device(काष्ठा usbip_usb_device *udev)
अणु
	अक्षर buff[100];

	dbg("%-20s = %s", "path",  udev->path);
	dbg("%-20s = %s", "busid", udev->busid);

	usbip_names_get_class(buff, माप(buff),
			udev->bDeviceClass,
			udev->bDeviceSubClass,
			udev->bDeviceProtocol);
	dbg("%-20s = %s", "Device(C/SC/P)", buff);

	DBG_UDEV_INTEGER(bcdDevice);

	usbip_names_get_product(buff, माप(buff),
			udev->idVenकरोr,
			udev->idProduct);
	dbg("%-20s = %s", "Vendor/Product", buff);

	DBG_UDEV_INTEGER(bNumConfigurations);
	DBG_UDEV_INTEGER(bNumInterfaces);

	dbg("%-20s = %s", "speed",
			usbip_speed_string(udev->speed));

	DBG_UDEV_INTEGER(busnum);
	DBG_UDEV_INTEGER(devnum);
पूर्ण


पूर्णांक पढ़ो_attr_value(काष्ठा udev_device *dev, स्थिर अक्षर *name,
		    स्थिर अक्षर *क्रमmat)
अणु
	स्थिर अक्षर *attr;
	पूर्णांक num = 0;
	पूर्णांक ret;

	attr = udev_device_get_sysattr_value(dev, name);
	अगर (!attr) अणु
		err("udev_device_get_sysattr_value failed");
		जाओ err;
	पूर्ण

	/* The client chooses the device configuration
	 * when attaching it so right after being bound
	 * to usbip-host on the server the device will
	 * have no configuration.
	 * Thereक्रमe, attributes such as bConfigurationValue
	 * and bNumInterfaces will not exist and माला_पूछो will
	 * fail. Check क्रम these हालs and करोn't treat them
	 * as errors.
	 */

	ret = माला_पूछो(attr, क्रमmat, &num);
	अगर (ret < 1) अणु
		अगर (म_भेद(name, "bConfigurationValue") &&
				म_भेद(name, "bNumInterfaces")) अणु
			err("sscanf failed for attribute %s", name);
			जाओ err;
		पूर्ण
	पूर्ण

err:

	वापस num;
पूर्ण


पूर्णांक पढ़ो_attr_speed(काष्ठा udev_device *dev)
अणु
	स्थिर अक्षर *speed;

	speed = udev_device_get_sysattr_value(dev, "speed");
	अगर (!speed) अणु
		err("udev_device_get_sysattr_value failed");
		जाओ err;
	पूर्ण

	क्रम (पूर्णांक i = 0; speed_strings[i].speed != शून्य; i++) अणु
		अगर (!म_भेद(speed, speed_strings[i].speed))
			वापस speed_strings[i].num;
	पूर्ण

err:

	वापस USB_SPEED_UNKNOWN;
पूर्ण

#घोषणा READ_ATTR(object, type, dev, name, क्रमmat)			      \
	करो अणु								      \
		(object)->name = (type) पढ़ो_attr_value(dev, to_string(name), \
							क्रमmat);	      \
	पूर्ण जबतक (0)


पूर्णांक पढ़ो_usb_device(काष्ठा udev_device *sdev, काष्ठा usbip_usb_device *udev)
अणु
	uपूर्णांक32_t busnum, devnum;
	स्थिर अक्षर *path, *name;

	READ_ATTR(udev, uपूर्णांक8_t,  sdev, bDeviceClass,		"%02x\n");
	READ_ATTR(udev, uपूर्णांक8_t,  sdev, bDeviceSubClass,	"%02x\n");
	READ_ATTR(udev, uपूर्णांक8_t,  sdev, bDeviceProtocol,	"%02x\n");

	READ_ATTR(udev, uपूर्णांक16_t, sdev, idVenकरोr,		"%04x\n");
	READ_ATTR(udev, uपूर्णांक16_t, sdev, idProduct,		"%04x\n");
	READ_ATTR(udev, uपूर्णांक16_t, sdev, bcdDevice,		"%04x\n");

	READ_ATTR(udev, uपूर्णांक8_t,  sdev, bConfigurationValue,	"%02x\n");
	READ_ATTR(udev, uपूर्णांक8_t,  sdev, bNumConfigurations,	"%02x\n");
	READ_ATTR(udev, uपूर्णांक8_t,  sdev, bNumInterfaces,		"%02x\n");

	READ_ATTR(udev, uपूर्णांक8_t,  sdev, devnum,			"%d\n");
	udev->speed = पढ़ो_attr_speed(sdev);

	path = udev_device_get_syspath(sdev);
	name = udev_device_get_sysname(sdev);

	म_नकलन(udev->path,  path,  SYSFS_PATH_MAX - 1);
	udev->path[SYSFS_PATH_MAX - 1] = '\0';
	म_नकलन(udev->busid, name, SYSFS_BUS_ID_SIZE - 1);
	udev->busid[SYSFS_BUS_ID_SIZE - 1] = '\0';

	माला_पूछो(name, "%u-%u", &busnum, &devnum);
	udev->busnum = busnum;

	वापस 0;
पूर्ण

पूर्णांक पढ़ो_usb_पूर्णांकerface(काष्ठा usbip_usb_device *udev, पूर्णांक i,
		       काष्ठा usbip_usb_पूर्णांकerface *uinf)
अणु
	अक्षर busid[SYSFS_BUS_ID_SIZE];
	पूर्णांक size;
	काष्ठा udev_device *sअगर;

	size = snम_लिखो(busid, माप(busid), "%s:%d.%d",
			udev->busid, udev->bConfigurationValue, i);
	अगर (size < 0 || (अचिन्हित पूर्णांक)size >= माप(busid)) अणु
		err("busid length %i >= %lu or < 0", size,
		    (दीर्घ अचिन्हित)माप(busid));
		वापस -1;
	पूर्ण

	sअगर = udev_device_new_from_subप्रणाली_sysname(udev_context, "usb", busid);
	अगर (!sअगर) अणु
		err("udev_device_new_from_subsystem_sysname %s failed", busid);
		वापस -1;
	पूर्ण

	READ_ATTR(uinf, uपूर्णांक8_t,  sअगर, bInterfaceClass,		"%02x\n");
	READ_ATTR(uinf, uपूर्णांक8_t,  sअगर, bInterfaceSubClass,	"%02x\n");
	READ_ATTR(uinf, uपूर्णांक8_t,  sअगर, bInterfaceProtocol,	"%02x\n");

	वापस 0;
पूर्ण

पूर्णांक usbip_names_init(अक्षर *f)
अणु
	वापस names_init(f);
पूर्ण

व्योम usbip_names_मुक्त(व्योम)
अणु
	names_मुक्त();
पूर्ण

व्योम usbip_names_get_product(अक्षर *buff, माप_प्रकार size, uपूर्णांक16_t venकरोr,
			     uपूर्णांक16_t product)
अणु
	स्थिर अक्षर *prod, *vend;

	prod = names_product(venकरोr, product);
	अगर (!prod)
		prod = "unknown product";


	vend = names_venकरोr(venकरोr);
	अगर (!vend)
		vend = "unknown vendor";

	snम_लिखो(buff, size, "%s : %s (%04x:%04x)", vend, prod, venकरोr, product);
पूर्ण

व्योम usbip_names_get_class(अक्षर *buff, माप_प्रकार size, uपूर्णांक8_t class,
			   uपूर्णांक8_t subclass, uपूर्णांक8_t protocol)
अणु
	स्थिर अक्षर *c, *s, *p;

	अगर (class == 0 && subclass == 0 && protocol == 0) अणु
		snम_लिखो(buff, size, "(Defined at Interface level) (%02x/%02x/%02x)", class, subclass, protocol);
		वापस;
	पूर्ण

	p = names_protocol(class, subclass, protocol);
	अगर (!p)
		p = "unknown protocol";

	s = names_subclass(class, subclass);
	अगर (!s)
		s = "unknown subclass";

	c = names_class(class);
	अगर (!c)
		c = "unknown class";

	snम_लिखो(buff, size, "%s / %s / %s (%02x/%02x/%02x)", c, s, p, class, subclass, protocol);
पूर्ण
