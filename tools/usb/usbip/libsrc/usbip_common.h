<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2005-2007 Takahiro Hirofuchi
 */

#अगर_अघोषित __USBIP_COMMON_H
#घोषणा __USBIP_COMMON_H

#समावेश <libudev.h>

#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <syslog.h>
#समावेश <unistd.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usbip.h>

#अगर_अघोषित USBIDS_खाता
#घोषणा USBIDS_खाता "/usr/share/hwdata/usb.ids"
#पूर्ण_अगर

#अगर_अघोषित VHCI_STATE_PATH
#घोषणा VHCI_STATE_PATH "/var/run/vhci_hcd"
#पूर्ण_अगर

#घोषणा VUDC_DEVICE_DESCR_खाता "dev_desc"

/* kernel module names */
#घोषणा USBIP_CORE_MOD_NAME	"usbip-core"
#घोषणा USBIP_HOST_DRV_NAME	"usbip-host"
#घोषणा USBIP_DEVICE_DRV_NAME	"usbip-vudc"
#घोषणा USBIP_VHCI_DRV_NAME	"vhci_hcd"

/* sysfs स्थिरants */
#घोषणा SYSFS_MNT_PATH         "/sys"
#घोषणा SYSFS_BUS_NAME         "bus"
#घोषणा SYSFS_BUS_TYPE         "usb"
#घोषणा SYSFS_DRIVERS_NAME     "drivers"

#घोषणा SYSFS_PATH_MAX		256
#घोषणा SYSFS_BUS_ID_SIZE	32

/* Defines क्रम op_code status in server/client op_common PDUs */
#घोषणा ST_OK	0x00
#घोषणा ST_NA	0x01
	/* Device requested क्रम import is not available */
#घोषणा ST_DEV_BUSY	0x02
	/* Device requested क्रम import is in error state */
#घोषणा ST_DEV_ERR	0x03
#घोषणा ST_NODEV	0x04
#घोषणा ST_ERROR	0x05

बाह्य पूर्णांक usbip_use_syslog;
बाह्य पूर्णांक usbip_use_मानक_त्रुटि;
बाह्य पूर्णांक usbip_use_debug ;

#घोषणा PROGNAME "usbip"

#घोषणा pr_fmt(fmt)	"%s: %s: " fmt "\n", PROGNAME
#घोषणा dbg_fmt(fmt)	pr_fmt("%s:%d:[%s] " fmt), "debug",	\
		        __खाता__, __LINE__, __func__

#घोषणा err(fmt, args...)						\
	करो अणु								\
		अगर (usbip_use_syslog) अणु					\
			syslog(LOG_ERR, pr_fmt(fmt), "error", ##args);	\
		पूर्ण							\
		अगर (usbip_use_मानक_त्रुटि) अणु					\
			ख_लिखो(मानक_त्रुटि, pr_fmt(fmt), "error", ##args);	\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा info(fmt, args...)						\
	करो अणु								\
		अगर (usbip_use_syslog) अणु					\
			syslog(LOG_INFO, pr_fmt(fmt), "info", ##args);	\
		पूर्ण							\
		अगर (usbip_use_मानक_त्रुटि) अणु					\
			ख_लिखो(मानक_त्रुटि, pr_fmt(fmt), "info", ##args);	\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा dbg(fmt, args...)						\
	करो अणु								\
	अगर (usbip_use_debug) अणु						\
		अगर (usbip_use_syslog) अणु					\
			syslog(LOG_DEBUG, dbg_fmt(fmt), ##args);	\
		पूर्ण							\
		अगर (usbip_use_मानक_त्रुटि) अणु					\
			ख_लिखो(मानक_त्रुटि, dbg_fmt(fmt), ##args);		\
		पूर्ण							\
	पूर्ण								\
	पूर्ण जबतक (0)

#घोषणा BUG()						\
	करो अणु						\
		err("sorry, it's a bug!");		\
		पात();				\
	पूर्ण जबतक (0)

काष्ठा usbip_usb_पूर्णांकerface अणु
	uपूर्णांक8_t bInterfaceClass;
	uपूर्णांक8_t bInterfaceSubClass;
	uपूर्णांक8_t bInterfaceProtocol;
	uपूर्णांक8_t padding;	/* alignment */
पूर्ण __attribute__((packed));

काष्ठा usbip_usb_device अणु
	अक्षर path[SYSFS_PATH_MAX];
	अक्षर busid[SYSFS_BUS_ID_SIZE];

	uपूर्णांक32_t busnum;
	uपूर्णांक32_t devnum;
	uपूर्णांक32_t speed;

	uपूर्णांक16_t idVenकरोr;
	uपूर्णांक16_t idProduct;
	uपूर्णांक16_t bcdDevice;

	uपूर्णांक8_t bDeviceClass;
	uपूर्णांक8_t bDeviceSubClass;
	uपूर्णांक8_t bDeviceProtocol;
	uपूर्णांक8_t bConfigurationValue;
	uपूर्णांक8_t bNumConfigurations;
	uपूर्णांक8_t bNumInterfaces;
पूर्ण __attribute__((packed));

#घोषणा to_string(s)	#s

व्योम dump_usb_पूर्णांकerface(काष्ठा usbip_usb_पूर्णांकerface *);
व्योम dump_usb_device(काष्ठा usbip_usb_device *);
पूर्णांक पढ़ो_usb_device(काष्ठा udev_device *sdev, काष्ठा usbip_usb_device *udev);
पूर्णांक पढ़ो_attr_value(काष्ठा udev_device *dev, स्थिर अक्षर *name,
		    स्थिर अक्षर *क्रमmat);
पूर्णांक पढ़ो_usb_पूर्णांकerface(काष्ठा usbip_usb_device *udev, पूर्णांक i,
		       काष्ठा usbip_usb_पूर्णांकerface *uinf);

स्थिर अक्षर *usbip_speed_string(पूर्णांक num);
स्थिर अक्षर *usbip_status_string(पूर्णांक32_t status);
स्थिर अक्षर *usbip_op_common_status_string(पूर्णांक status);

पूर्णांक usbip_names_init(अक्षर *);
व्योम usbip_names_मुक्त(व्योम);
व्योम usbip_names_get_product(अक्षर *buff, माप_प्रकार size, uपूर्णांक16_t venकरोr,
			     uपूर्णांक16_t product);
व्योम usbip_names_get_class(अक्षर *buff, माप_प्रकार size, uपूर्णांक8_t class,
			   uपूर्णांक8_t subclass, uपूर्णांक8_t protocol);

#पूर्ण_अगर /* __USBIP_COMMON_H */
