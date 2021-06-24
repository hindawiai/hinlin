<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Device tables which are exported to userspace via
 * scripts/mod/file2alias.c.  You must keep that file in sync with this
 * header.
 */

#अगर_अघोषित LINUX_MOD_DEVICETABLE_H
#घोषणा LINUX_MOD_DEVICETABLE_H

#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#समावेश <linux/uuid.h>
प्रकार अचिन्हित दीर्घ kernel_uदीर्घ_t;
#पूर्ण_अगर

#घोषणा PCI_ANY_ID (~0)

/**
 * काष्ठा pci_device_id - PCI device ID काष्ठाure
 * @venकरोr:		Venकरोr ID to match (or PCI_ANY_ID)
 * @device:		Device ID to match (or PCI_ANY_ID)
 * @subvenकरोr:		Subप्रणाली venकरोr ID to match (or PCI_ANY_ID)
 * @subdevice:		Subप्रणाली device ID to match (or PCI_ANY_ID)
 * @class:		Device class, subclass, and "interface" to match.
 *			See Appendix D of the PCI Local Bus Spec or
 *			include/linux/pci_ids.h क्रम a full list of classes.
 *			Most drivers करो not need to specअगरy class/class_mask
 *			as venकरोr/device is normally sufficient.
 * @class_mask:		Limit which sub-fields of the class field are compared.
 *			See drivers/scsi/sym53c8xx_2/ क्रम example of usage.
 * @driver_data:	Data निजी to the driver.
 *			Most drivers करोn't need to use driver_data field.
 *			Best practice is to use driver_data as an index
 *			पूर्णांकo a अटल list of equivalent device types,
 *			instead of using it as a poपूर्णांकer.
 */
काष्ठा pci_device_id अणु
	__u32 venकरोr, device;		/* Venकरोr and device ID or PCI_ANY_ID*/
	__u32 subvenकरोr, subdevice;	/* Subप्रणाली ID's or PCI_ANY_ID */
	__u32 class, class_mask;	/* (class,subclass,prog-अगर) triplet */
	kernel_uदीर्घ_t driver_data;	/* Data निजी to the driver */
पूर्ण;


#घोषणा IEEE1394_MATCH_VENDOR_ID	0x0001
#घोषणा IEEE1394_MATCH_MODEL_ID		0x0002
#घोषणा IEEE1394_MATCH_SPECIFIER_ID	0x0004
#घोषणा IEEE1394_MATCH_VERSION		0x0008

काष्ठा ieee1394_device_id अणु
	__u32 match_flags;
	__u32 venकरोr_id;
	__u32 model_id;
	__u32 specअगरier_id;
	__u32 version;
	kernel_uदीर्घ_t driver_data;
पूर्ण;


/*
 * Device table entry क्रम "new style" table-driven USB drivers.
 * User mode code can पढ़ो these tables to choose which modules to load.
 * Declare the table as a MODULE_DEVICE_TABLE.
 *
 * A probe() parameter will poपूर्णांक to a matching entry from this table.
 * Use the driver_info field क्रम each match to hold inक्रमmation tied
 * to that match:  device quirks, etc.
 *
 * Terminate the driver's table with an all-zeroes entry.
 * Use the flag values to control which fields are compared.
 */

/**
 * काष्ठा usb_device_id - identअगरies USB devices क्रम probing and hotplugging
 * @match_flags: Bit mask controlling which of the other fields are used to
 *	match against new devices. Any field except क्रम driver_info may be
 *	used, although some only make sense in conjunction with other fields.
 *	This is usually set by a USB_DEVICE_*() macro, which sets all
 *	other fields in this काष्ठाure except क्रम driver_info.
 * @idVenकरोr: USB venकरोr ID क्रम a device; numbers are asचिन्हित
 *	by the USB क्रमum to its members.
 * @idProduct: Venकरोr-asचिन्हित product ID.
 * @bcdDevice_lo: Low end of range of venकरोr-asचिन्हित product version numbers.
 *	This is also used to identअगरy inभागidual product versions, क्रम
 *	a range consisting of a single device.
 * @bcdDevice_hi: High end of version number range.  The range of product
 *	versions is inclusive.
 * @bDeviceClass: Class of device; numbers are asचिन्हित
 *	by the USB क्रमum.  Products may choose to implement classes,
 *	or be venकरोr-specअगरic.  Device classes specअगरy behavior of all
 *	the पूर्णांकerfaces on a device.
 * @bDeviceSubClass: Subclass of device; associated with bDeviceClass.
 * @bDeviceProtocol: Protocol of device; associated with bDeviceClass.
 * @bInterfaceClass: Class of पूर्णांकerface; numbers are asचिन्हित
 *	by the USB क्रमum.  Products may choose to implement classes,
 *	or be venकरोr-specअगरic.  Interface classes specअगरy behavior only
 *	of a given पूर्णांकerface; other पूर्णांकerfaces may support other classes.
 * @bInterfaceSubClass: Subclass of पूर्णांकerface; associated with bInterfaceClass.
 * @bInterfaceProtocol: Protocol of पूर्णांकerface; associated with bInterfaceClass.
 * @bInterfaceNumber: Number of पूर्णांकerface; composite devices may use
 *	fixed पूर्णांकerface numbers to dअगरferentiate between venकरोr-specअगरic
 *	पूर्णांकerfaces.
 * @driver_info: Holds inक्रमmation used by the driver.  Usually it holds
 *	a poपूर्णांकer to a descriptor understood by the driver, or perhaps
 *	device flags.
 *
 * In most हालs, drivers will create a table of device IDs by using
 * USB_DEVICE(), or similar macros deचिन्हित क्रम that purpose.
 * They will then export it to userspace using MODULE_DEVICE_TABLE(),
 * and provide it to the USB core through their usb_driver काष्ठाure.
 *
 * See the usb_match_id() function क्रम inक्रमmation about how matches are
 * perक्रमmed.  Briefly, you will normally use one of several macros to help
 * स्थिरruct these entries.  Each entry you provide will either identअगरy
 * one or more specअगरic products, or will identअगरy a class of products
 * which have agreed to behave the same.  You should put the more specअगरic
 * matches towards the beginning of your table, so that driver_info can
 * record quirks of specअगरic products.
 */
काष्ठा usb_device_id अणु
	/* which fields to match against? */
	__u16		match_flags;

	/* Used क्रम product specअगरic matches; range is inclusive */
	__u16		idVenकरोr;
	__u16		idProduct;
	__u16		bcdDevice_lo;
	__u16		bcdDevice_hi;

	/* Used क्रम device class matches */
	__u8		bDeviceClass;
	__u8		bDeviceSubClass;
	__u8		bDeviceProtocol;

	/* Used क्रम पूर्णांकerface class matches */
	__u8		bInterfaceClass;
	__u8		bInterfaceSubClass;
	__u8		bInterfaceProtocol;

	/* Used क्रम venकरोr-specअगरic पूर्णांकerface matches */
	__u8		bInterfaceNumber;

	/* not matched against */
	kernel_uदीर्घ_t	driver_info
		__attribute__((aligned(माप(kernel_uदीर्घ_t))));
पूर्ण;

/* Some useful macros to use to create काष्ठा usb_device_id */
#घोषणा USB_DEVICE_ID_MATCH_VENDOR		0x0001
#घोषणा USB_DEVICE_ID_MATCH_PRODUCT		0x0002
#घोषणा USB_DEVICE_ID_MATCH_DEV_LO		0x0004
#घोषणा USB_DEVICE_ID_MATCH_DEV_HI		0x0008
#घोषणा USB_DEVICE_ID_MATCH_DEV_CLASS		0x0010
#घोषणा USB_DEVICE_ID_MATCH_DEV_SUBCLASS	0x0020
#घोषणा USB_DEVICE_ID_MATCH_DEV_PROTOCOL	0x0040
#घोषणा USB_DEVICE_ID_MATCH_INT_CLASS		0x0080
#घोषणा USB_DEVICE_ID_MATCH_INT_SUBCLASS	0x0100
#घोषणा USB_DEVICE_ID_MATCH_INT_PROTOCOL	0x0200
#घोषणा USB_DEVICE_ID_MATCH_INT_NUMBER		0x0400

#घोषणा HID_ANY_ID				(~0)
#घोषणा HID_BUS_ANY				0xffff
#घोषणा HID_GROUP_ANY				0x0000

काष्ठा hid_device_id अणु
	__u16 bus;
	__u16 group;
	__u32 venकरोr;
	__u32 product;
	kernel_uदीर्घ_t driver_data;
पूर्ण;

/* s390 CCW devices */
काष्ठा ccw_device_id अणु
	__u16	match_flags;	/* which fields to match against */

	__u16	cu_type;	/* control unit type     */
	__u16	dev_type;	/* device type           */
	__u8	cu_model;	/* control unit model    */
	__u8	dev_model;	/* device model          */

	kernel_uदीर्घ_t driver_info;
पूर्ण;

#घोषणा CCW_DEVICE_ID_MATCH_CU_TYPE		0x01
#घोषणा CCW_DEVICE_ID_MATCH_CU_MODEL		0x02
#घोषणा CCW_DEVICE_ID_MATCH_DEVICE_TYPE		0x04
#घोषणा CCW_DEVICE_ID_MATCH_DEVICE_MODEL	0x08

/* s390 AP bus devices */
काष्ठा ap_device_id अणु
	__u16 match_flags;	/* which fields to match against */
	__u8 dev_type;		/* device type */
	kernel_uदीर्घ_t driver_info;
पूर्ण;

#घोषणा AP_DEVICE_ID_MATCH_CARD_TYPE		0x01
#घोषणा AP_DEVICE_ID_MATCH_QUEUE_TYPE		0x02

/* s390 css bus devices (subchannels) */
काष्ठा css_device_id अणु
	__u8 match_flags;
	__u8 type; /* subchannel type */
	kernel_uदीर्घ_t driver_data;
पूर्ण;

#घोषणा ACPI_ID_LEN	9

काष्ठा acpi_device_id अणु
	__u8 id[ACPI_ID_LEN];
	kernel_uदीर्घ_t driver_data;
	__u32 cls;
	__u32 cls_msk;
पूर्ण;

#घोषणा PNP_ID_LEN	8
#घोषणा PNP_MAX_DEVICES	8

काष्ठा pnp_device_id अणु
	__u8 id[PNP_ID_LEN];
	kernel_uदीर्घ_t driver_data;
पूर्ण;

काष्ठा pnp_card_device_id अणु
	__u8 id[PNP_ID_LEN];
	kernel_uदीर्घ_t driver_data;
	काष्ठा अणु
		__u8 id[PNP_ID_LEN];
	पूर्ण devs[PNP_MAX_DEVICES];
पूर्ण;


#घोषणा SERIO_ANY	0xff

काष्ठा serio_device_id अणु
	__u8 type;
	__u8 extra;
	__u8 id;
	__u8 proto;
पूर्ण;

काष्ठा hda_device_id अणु
	__u32 venकरोr_id;
	__u32 rev_id;
	__u8 api_version;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ driver_data;
पूर्ण;

काष्ठा sdw_device_id अणु
	__u16 mfg_id;
	__u16 part_id;
	__u8  sdw_version;
	__u8  class_id;
	kernel_uदीर्घ_t driver_data;
पूर्ण;

/*
 * Struct used क्रम matching a device
 */
काष्ठा of_device_id अणु
	अक्षर	name[32];
	अक्षर	type[32];
	अक्षर	compatible[128];
	स्थिर व्योम *data;
पूर्ण;

/* VIO */
काष्ठा vio_device_id अणु
	अक्षर type[32];
	अक्षर compat[32];
पूर्ण;

/* PCMCIA */

काष्ठा pcmcia_device_id अणु
	__u16		match_flags;

	__u16		manf_id;
	__u16		card_id;

	__u8		func_id;

	/* क्रम real multi-function devices */
	__u8		function;

	/* क्रम pseuकरो multi-function devices */
	__u8		device_no;

	__u32		prod_id_hash[4];

	/* not matched against in kernelspace */
	स्थिर अक्षर *	prod_id[4];

	/* not matched against */
	kernel_uदीर्घ_t	driver_info;
	अक्षर *		cisfile;
पूर्ण;

#घोषणा PCMCIA_DEV_ID_MATCH_MANF_ID	0x0001
#घोषणा PCMCIA_DEV_ID_MATCH_CARD_ID	0x0002
#घोषणा PCMCIA_DEV_ID_MATCH_FUNC_ID	0x0004
#घोषणा PCMCIA_DEV_ID_MATCH_FUNCTION	0x0008
#घोषणा PCMCIA_DEV_ID_MATCH_PROD_ID1	0x0010
#घोषणा PCMCIA_DEV_ID_MATCH_PROD_ID2	0x0020
#घोषणा PCMCIA_DEV_ID_MATCH_PROD_ID3	0x0040
#घोषणा PCMCIA_DEV_ID_MATCH_PROD_ID4	0x0080
#घोषणा PCMCIA_DEV_ID_MATCH_DEVICE_NO	0x0100
#घोषणा PCMCIA_DEV_ID_MATCH_FAKE_CIS	0x0200
#घोषणा PCMCIA_DEV_ID_MATCH_ANONYMOUS	0x0400

/* Input */
#घोषणा INPUT_DEVICE_ID_EV_MAX		0x1f
#घोषणा INPUT_DEVICE_ID_KEY_MIN_INTERESTING	0x71
#घोषणा INPUT_DEVICE_ID_KEY_MAX		0x2ff
#घोषणा INPUT_DEVICE_ID_REL_MAX		0x0f
#घोषणा INPUT_DEVICE_ID_ABS_MAX		0x3f
#घोषणा INPUT_DEVICE_ID_MSC_MAX		0x07
#घोषणा INPUT_DEVICE_ID_LED_MAX		0x0f
#घोषणा INPUT_DEVICE_ID_SND_MAX		0x07
#घोषणा INPUT_DEVICE_ID_FF_MAX		0x7f
#घोषणा INPUT_DEVICE_ID_SW_MAX		0x10
#घोषणा INPUT_DEVICE_ID_PROP_MAX	0x1f

#घोषणा INPUT_DEVICE_ID_MATCH_BUS	1
#घोषणा INPUT_DEVICE_ID_MATCH_VENDOR	2
#घोषणा INPUT_DEVICE_ID_MATCH_PRODUCT	4
#घोषणा INPUT_DEVICE_ID_MATCH_VERSION	8

#घोषणा INPUT_DEVICE_ID_MATCH_EVBIT	0x0010
#घोषणा INPUT_DEVICE_ID_MATCH_KEYBIT	0x0020
#घोषणा INPUT_DEVICE_ID_MATCH_RELBIT	0x0040
#घोषणा INPUT_DEVICE_ID_MATCH_ABSBIT	0x0080
#घोषणा INPUT_DEVICE_ID_MATCH_MSCIT	0x0100
#घोषणा INPUT_DEVICE_ID_MATCH_LEDBIT	0x0200
#घोषणा INPUT_DEVICE_ID_MATCH_SNDBIT	0x0400
#घोषणा INPUT_DEVICE_ID_MATCH_FFBIT	0x0800
#घोषणा INPUT_DEVICE_ID_MATCH_SWBIT	0x1000
#घोषणा INPUT_DEVICE_ID_MATCH_PROPBIT	0x2000

काष्ठा input_device_id अणु

	kernel_uदीर्घ_t flags;

	__u16 bustype;
	__u16 venकरोr;
	__u16 product;
	__u16 version;

	kernel_uदीर्घ_t evbit[INPUT_DEVICE_ID_EV_MAX / BITS_PER_LONG + 1];
	kernel_uदीर्घ_t keybit[INPUT_DEVICE_ID_KEY_MAX / BITS_PER_LONG + 1];
	kernel_uदीर्घ_t relbit[INPUT_DEVICE_ID_REL_MAX / BITS_PER_LONG + 1];
	kernel_uदीर्घ_t असलbit[INPUT_DEVICE_ID_ABS_MAX / BITS_PER_LONG + 1];
	kernel_uदीर्घ_t mscbit[INPUT_DEVICE_ID_MSC_MAX / BITS_PER_LONG + 1];
	kernel_uदीर्घ_t ledbit[INPUT_DEVICE_ID_LED_MAX / BITS_PER_LONG + 1];
	kernel_uदीर्घ_t sndbit[INPUT_DEVICE_ID_SND_MAX / BITS_PER_LONG + 1];
	kernel_uदीर्घ_t ffbit[INPUT_DEVICE_ID_FF_MAX / BITS_PER_LONG + 1];
	kernel_uदीर्घ_t swbit[INPUT_DEVICE_ID_SW_MAX / BITS_PER_LONG + 1];
	kernel_uदीर्घ_t propbit[INPUT_DEVICE_ID_PROP_MAX / BITS_PER_LONG + 1];

	kernel_uदीर्घ_t driver_info;
पूर्ण;

/* EISA */

#घोषणा EISA_SIG_LEN   8

/* The EISA signature, in ASCII क्रमm, null terminated */
काष्ठा eisa_device_id अणु
	अक्षर          sig[EISA_SIG_LEN];
	kernel_uदीर्घ_t driver_data;
पूर्ण;

#घोषणा EISA_DEVICE_MODALIAS_FMT "eisa:s%s"

काष्ठा parisc_device_id अणु
	__u8	hw_type;	/* 5 bits used */
	__u8	hversion_rev;	/* 4 bits */
	__u16	hversion;	/* 12 bits */
	__u32	sversion;	/* 20 bits */
पूर्ण;

#घोषणा PA_HWTYPE_ANY_ID	0xff
#घोषणा PA_HVERSION_REV_ANY_ID	0xff
#घोषणा PA_HVERSION_ANY_ID	0xffff
#घोषणा PA_SVERSION_ANY_ID	0xffffffff

/* SDIO */

#घोषणा SDIO_ANY_ID (~0)

काष्ठा sdio_device_id अणु
	__u8	class;			/* Standard पूर्णांकerface or SDIO_ANY_ID */
	__u16	venकरोr;			/* Venकरोr or SDIO_ANY_ID */
	__u16	device;			/* Device ID or SDIO_ANY_ID */
	kernel_uदीर्घ_t driver_data;	/* Data निजी to the driver */
पूर्ण;

/* SSB core, see drivers/ssb/ */
काष्ठा ssb_device_id अणु
	__u16	venकरोr;
	__u16	coreid;
	__u8	revision;
	__u8	__pad;
पूर्ण __attribute__((packed, aligned(2)));
#घोषणा SSB_DEVICE(_venकरोr, _coreid, _revision)  \
	अणु .venकरोr = _venकरोr, .coreid = _coreid, .revision = _revision, पूर्ण

#घोषणा SSB_ANY_VENDOR		0xFFFF
#घोषणा SSB_ANY_ID		0xFFFF
#घोषणा SSB_ANY_REV		0xFF

/* Broadcom's specअगरic AMBA core, see drivers/bcma/ */
काष्ठा bcma_device_id अणु
	__u16	manuf;
	__u16	id;
	__u8	rev;
	__u8	class;
पूर्ण __attribute__((packed,aligned(2)));
#घोषणा BCMA_CORE(_manuf, _id, _rev, _class)  \
	अणु .manuf = _manuf, .id = _id, .rev = _rev, .class = _class, पूर्ण

#घोषणा BCMA_ANY_MANUF		0xFFFF
#घोषणा BCMA_ANY_ID		0xFFFF
#घोषणा BCMA_ANY_REV		0xFF
#घोषणा BCMA_ANY_CLASS		0xFF

काष्ठा virtio_device_id अणु
	__u32 device;
	__u32 venकरोr;
पूर्ण;
#घोषणा VIRTIO_DEV_ANY_ID	0xffffffff

/*
 * For Hyper-V devices we use the device guid as the id.
 */
काष्ठा hv_vmbus_device_id अणु
	guid_t guid;
	kernel_uदीर्घ_t driver_data;	/* Data निजी to the driver */
पूर्ण;

/* rpmsg */

#घोषणा RPMSG_NAME_SIZE			32
#घोषणा RPMSG_DEVICE_MODALIAS_FMT	"rpmsg:%s"

काष्ठा rpmsg_device_id अणु
	अक्षर name[RPMSG_NAME_SIZE];
पूर्ण;

/* i2c */

#घोषणा I2C_NAME_SIZE	20
#घोषणा I2C_MODULE_PREFIX "i2c:"

काष्ठा i2c_device_id अणु
	अक्षर name[I2C_NAME_SIZE];
	kernel_uदीर्घ_t driver_data;	/* Data निजी to the driver */
पूर्ण;

/* pci_epf */

#घोषणा PCI_EPF_NAME_SIZE	20
#घोषणा PCI_EPF_MODULE_PREFIX	"pci_epf:"

काष्ठा pci_epf_device_id अणु
	अक्षर name[PCI_EPF_NAME_SIZE];
	kernel_uदीर्घ_t driver_data;
पूर्ण;

/* i3c */

#घोषणा I3C_MATCH_DCR			0x1
#घोषणा I3C_MATCH_MANUF			0x2
#घोषणा I3C_MATCH_PART			0x4
#घोषणा I3C_MATCH_EXTRA_INFO		0x8

काष्ठा i3c_device_id अणु
	__u8 match_flags;
	__u8 dcr;
	__u16 manuf_id;
	__u16 part_id;
	__u16 extra_info;

	स्थिर व्योम *data;
पूर्ण;

/* spi */

#घोषणा SPI_NAME_SIZE	32
#घोषणा SPI_MODULE_PREFIX "spi:"

काष्ठा spi_device_id अणु
	अक्षर name[SPI_NAME_SIZE];
	kernel_uदीर्घ_t driver_data;	/* Data निजी to the driver */
पूर्ण;

/* SLIMbus */

#घोषणा SLIMBUS_NAME_SIZE	32
#घोषणा SLIMBUS_MODULE_PREFIX	"slim:"

काष्ठा slim_device_id अणु
	__u16 manf_id, prod_code;
	__u16 dev_index, instance;

	/* Data निजी to the driver */
	kernel_uदीर्घ_t driver_data;
पूर्ण;

#घोषणा APR_NAME_SIZE	32
#घोषणा APR_MODULE_PREFIX "apr:"

काष्ठा apr_device_id अणु
	अक्षर name[APR_NAME_SIZE];
	__u32 करोमुख्य_id;
	__u32 svc_id;
	__u32 svc_version;
	kernel_uदीर्घ_t driver_data;	/* Data निजी to the driver */
पूर्ण;

#घोषणा SPMI_NAME_SIZE	32
#घोषणा SPMI_MODULE_PREFIX "spmi:"

काष्ठा spmi_device_id अणु
	अक्षर name[SPMI_NAME_SIZE];
	kernel_uदीर्घ_t driver_data;	/* Data निजी to the driver */
पूर्ण;

/* dmi */
क्रमागत dmi_field अणु
	DMI_NONE,
	DMI_BIOS_VENDOR,
	DMI_BIOS_VERSION,
	DMI_BIOS_DATE,
	DMI_BIOS_RELEASE,
	DMI_EC_FIRMWARE_RELEASE,
	DMI_SYS_VENDOR,
	DMI_PRODUCT_NAME,
	DMI_PRODUCT_VERSION,
	DMI_PRODUCT_SERIAL,
	DMI_PRODUCT_UUID,
	DMI_PRODUCT_SKU,
	DMI_PRODUCT_FAMILY,
	DMI_BOARD_VENDOR,
	DMI_BOARD_NAME,
	DMI_BOARD_VERSION,
	DMI_BOARD_SERIAL,
	DMI_BOARD_ASSET_TAG,
	DMI_CHASSIS_VENDOR,
	DMI_CHASSIS_TYPE,
	DMI_CHASSIS_VERSION,
	DMI_CHASSIS_SERIAL,
	DMI_CHASSIS_ASSET_TAG,
	DMI_STRING_MAX,
	DMI_OEM_STRING,	/* special हाल - will not be in dmi_ident */
पूर्ण;

काष्ठा dmi_strmatch अणु
	अचिन्हित अक्षर slot:7;
	अचिन्हित अक्षर exact_match:1;
	अक्षर substr[79];
पूर्ण;

काष्ठा dmi_प्रणाली_id अणु
	पूर्णांक (*callback)(स्थिर काष्ठा dmi_प्रणाली_id *);
	स्थिर अक्षर *ident;
	काष्ठा dmi_strmatch matches[4];
	व्योम *driver_data;
पूर्ण;
/*
 * काष्ठा dmi_device_id appears during expansion of
 * "MODULE_DEVICE_TABLE(dmi, x)". Compiler करोesn't look inside it
 * but this is enough क्रम gcc 3.4.6 to error out:
 *	error: storage size of '__mod_dmi_device_table' isn't known
 */
#घोषणा dmi_device_id dmi_प्रणाली_id

#घोषणा DMI_MATCH(a, b)	अणु .slot = a, .substr = b पूर्ण
#घोषणा DMI_EXACT_MATCH(a, b)	अणु .slot = a, .substr = b, .exact_match = 1 पूर्ण

#घोषणा PLATFORM_NAME_SIZE	20
#घोषणा PLATFORM_MODULE_PREFIX	"platform:"

काष्ठा platक्रमm_device_id अणु
	अक्षर name[PLATFORM_NAME_SIZE];
	kernel_uदीर्घ_t driver_data;
पूर्ण;

#घोषणा MDIO_NAME_SIZE		32
#घोषणा MDIO_MODULE_PREFIX	"mdio:"

#घोषणा MDIO_ID_FMT "%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u"
#घोषणा MDIO_ID_ARGS(_id) \
	((_id)>>31) & 1, ((_id)>>30) & 1, ((_id)>>29) & 1, ((_id)>>28) & 1, \
	((_id)>>27) & 1, ((_id)>>26) & 1, ((_id)>>25) & 1, ((_id)>>24) & 1, \
	((_id)>>23) & 1, ((_id)>>22) & 1, ((_id)>>21) & 1, ((_id)>>20) & 1, \
	((_id)>>19) & 1, ((_id)>>18) & 1, ((_id)>>17) & 1, ((_id)>>16) & 1, \
	((_id)>>15) & 1, ((_id)>>14) & 1, ((_id)>>13) & 1, ((_id)>>12) & 1, \
	((_id)>>11) & 1, ((_id)>>10) & 1, ((_id)>>9) & 1, ((_id)>>8) & 1, \
	((_id)>>7) & 1, ((_id)>>6) & 1, ((_id)>>5) & 1, ((_id)>>4) & 1, \
	((_id)>>3) & 1, ((_id)>>2) & 1, ((_id)>>1) & 1, (_id) & 1

/**
 * काष्ठा mdio_device_id - identअगरies PHY devices on an MDIO/MII bus
 * @phy_id: The result of
 *     (mdio_पढ़ो(&MII_PHYSID1) << 16 | mdio_पढ़ो(&MII_PHYSID2)) & @phy_id_mask
 *     क्रम this PHY type
 * @phy_id_mask: Defines the signअगरicant bits of @phy_id.  A value of 0
 *     is used to terminate an array of काष्ठा mdio_device_id.
 */
काष्ठा mdio_device_id अणु
	__u32 phy_id;
	__u32 phy_id_mask;
पूर्ण;

काष्ठा zorro_device_id अणु
	__u32 id;			/* Device ID or ZORRO_WILDCARD */
	kernel_uदीर्घ_t driver_data;	/* Data निजी to the driver */
पूर्ण;

#घोषणा ZORRO_WILDCARD			(0xffffffff)	/* not official */

#घोषणा ZORRO_DEVICE_MODALIAS_FMT	"zorro:i%08X"

#घोषणा ISAPNP_ANY_ID		0xffff
काष्ठा isapnp_device_id अणु
	अचिन्हित लघु card_venकरोr, card_device;
	अचिन्हित लघु venकरोr, function;
	kernel_uदीर्घ_t driver_data;	/* data निजी to the driver */
पूर्ण;

/**
 * काष्ठा amba_id - identअगरies a device on an AMBA bus
 * @id: The signअगरicant bits अगर the hardware device ID
 * @mask: Biपंचांगask specअगरying which bits of the id field are signअगरicant when
 *	matching.  A driver binds to a device when ((hardware device ID) & mask)
 *	== id.
 * @data: Private data used by the driver.
 */
काष्ठा amba_id अणु
	अचिन्हित पूर्णांक		id;
	अचिन्हित पूर्णांक		mask;
	व्योम			*data;
पूर्ण;

/**
 * काष्ठा mips_cdmm_device_id - identअगरies devices in MIPS CDMM bus
 * @type:	Device type identअगरier.
 */
काष्ठा mips_cdmm_device_id अणु
	__u8	type;
पूर्ण;

/*
 * Match x86 CPUs क्रम CPU specअगरic drivers.
 * See करोcumentation of "x86_match_cpu" क्रम details.
 */

/*
 * MODULE_DEVICE_TABLE expects this काष्ठा to be called x86cpu_device_id.
 * Although gcc seems to ignore this error, clang fails without this define.
 */
#घोषणा x86cpu_device_id x86_cpu_id
काष्ठा x86_cpu_id अणु
	__u16 venकरोr;
	__u16 family;
	__u16 model;
	__u16 steppings;
	__u16 feature;	/* bit index */
	kernel_uदीर्घ_t driver_data;
पूर्ण;

/* Wild cards क्रम x86_cpu_id::venकरोr, family, model and feature */
#घोषणा X86_VENDOR_ANY 0xffff
#घोषणा X86_FAMILY_ANY 0
#घोषणा X86_MODEL_ANY  0
#घोषणा X86_STEPPING_ANY 0
#घोषणा X86_FEATURE_ANY 0	/* Same as FPU, you can't test क्रम that */

/*
 * Generic table type क्रम matching CPU features.
 * @feature:	the bit number of the feature (0 - 65535)
 */

काष्ठा cpu_feature अणु
	__u16	feature;
पूर्ण;

#घोषणा IPACK_ANY_FORMAT 0xff
#घोषणा IPACK_ANY_ID (~0)
काष्ठा ipack_device_id अणु
	__u8  क्रमmat;			/* Format version or IPACK_ANY_ID */
	__u32 venकरोr;			/* Venकरोr ID or IPACK_ANY_ID */
	__u32 device;			/* Device ID or IPACK_ANY_ID */
पूर्ण;

#घोषणा MEI_CL_MODULE_PREFIX "mei:"
#घोषणा MEI_CL_NAME_SIZE 32
#घोषणा MEI_CL_VERSION_ANY 0xff

/**
 * काष्ठा mei_cl_device_id - MEI client device identअगरier
 * @name: helper name
 * @uuid: client uuid
 * @version: client protocol version
 * @driver_info: inक्रमmation used by the driver.
 *
 * identअगरies mei client device by uuid and name
 */
काष्ठा mei_cl_device_id अणु
	अक्षर name[MEI_CL_NAME_SIZE];
	uuid_le uuid;
	__u8    version;
	kernel_uदीर्घ_t driver_info;
पूर्ण;

/* RapidIO */

#घोषणा RIO_ANY_ID	0xffff

/**
 * काष्ठा rio_device_id - RIO device identअगरier
 * @did: RapidIO device ID
 * @vid: RapidIO venकरोr ID
 * @यंत्र_did: RapidIO assembly device ID
 * @यंत्र_vid: RapidIO assembly venकरोr ID
 *
 * Identअगरies a RapidIO device based on both the device/venकरोr IDs and
 * the assembly device/venकरोr IDs.
 */
काष्ठा rio_device_id अणु
	__u16 did, vid;
	__u16 यंत्र_did, यंत्र_vid;
पूर्ण;

काष्ठा mcb_device_id अणु
	__u16 device;
	kernel_uदीर्घ_t driver_data;
पूर्ण;

काष्ठा ulpi_device_id अणु
	__u16 venकरोr;
	__u16 product;
	kernel_uदीर्घ_t driver_data;
पूर्ण;

/**
 * काष्ठा fsl_mc_device_id - MC object device identअगरier
 * @venकरोr: venकरोr ID
 * @obj_type: MC object type
 *
 * Type of entries in the "device Id" table क्रम MC object devices supported by
 * a MC object device driver. The last entry of the table has venकरोr set to 0x0
 */
काष्ठा fsl_mc_device_id अणु
	__u16 venकरोr;
	स्थिर अक्षर obj_type[16];
पूर्ण;

/**
 * काष्ठा tb_service_id - Thunderbolt service identअगरiers
 * @match_flags: Flags used to match the काष्ठाure
 * @protocol_key: Protocol key the service supports
 * @protocol_id: Protocol id the service supports
 * @protocol_version: Version of the protocol
 * @protocol_revision: Revision of the protocol software
 * @driver_data: Driver specअगरic data
 *
 * Thunderbolt XDoमुख्य services are exposed as devices where each device
 * carries the protocol inक्रमmation the service supports. Thunderbolt
 * XDoमुख्य service drivers match against that inक्रमmation.
 */
काष्ठा tb_service_id अणु
	__u32 match_flags;
	अक्षर protocol_key[8 + 1];
	__u32 protocol_id;
	__u32 protocol_version;
	__u32 protocol_revision;
	kernel_uदीर्घ_t driver_data;
पूर्ण;

#घोषणा TBSVC_MATCH_PROTOCOL_KEY	0x0001
#घोषणा TBSVC_MATCH_PROTOCOL_ID		0x0002
#घोषणा TBSVC_MATCH_PROTOCOL_VERSION	0x0004
#घोषणा TBSVC_MATCH_PROTOCOL_REVISION	0x0008

/* USB Type-C Alternate Modes */

#घोषणा TYPEC_ANY_MODE	0x7

/**
 * काष्ठा typec_device_id - USB Type-C alternate mode identअगरiers
 * @svid: Standard or Venकरोr ID
 * @mode: Mode index
 * @driver_data: Driver specअगरic data
 */
काष्ठा typec_device_id अणु
	__u16 svid;
	__u8 mode;
	kernel_uदीर्घ_t driver_data;
पूर्ण;

/**
 * काष्ठा tee_client_device_id - tee based device identअगरier
 * @uuid: For TEE based client devices we use the device uuid as
 *        the identअगरier.
 */
काष्ठा tee_client_device_id अणु
	uuid_t uuid;
पूर्ण;

/* WMI */

#घोषणा WMI_MODULE_PREFIX	"wmi:"

/**
 * काष्ठा wmi_device_id - WMI device identअगरier
 * @guid_string: 36 अक्षर string of the क्रमm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @context: poपूर्णांकer to driver specअगरic data
 */
काष्ठा wmi_device_id अणु
	स्थिर अक्षर guid_string[UUID_STRING_LEN+1];
	स्थिर व्योम *context;
पूर्ण;

#घोषणा MHI_DEVICE_MODALIAS_FMT "mhi:%s"
#घोषणा MHI_NAME_SIZE 32

/**
 * काष्ठा mhi_device_id - MHI device identअगरication
 * @chan: MHI channel name
 * @driver_data: driver data;
 */
काष्ठा mhi_device_id अणु
	स्थिर अक्षर chan[MHI_NAME_SIZE];
	kernel_uदीर्घ_t driver_data;
पूर्ण;

#घोषणा AUXILIARY_NAME_SIZE 32
#घोषणा AUXILIARY_MODULE_PREFIX "auxiliary:"

काष्ठा auxiliary_device_id अणु
	अक्षर name[AUXILIARY_NAME_SIZE];
	kernel_uदीर्घ_t driver_data;
पूर्ण;

/* Surface System Aggregator Module */

#घोषणा SSAM_MATCH_TARGET	0x1
#घोषणा SSAM_MATCH_INSTANCE	0x2
#घोषणा SSAM_MATCH_FUNCTION	0x4

काष्ठा ssam_device_id अणु
	__u8 match_flags;

	__u8 करोमुख्य;
	__u8 category;
	__u8 target;
	__u8 instance;
	__u8 function;

	kernel_uदीर्घ_t driver_data;
पूर्ण;

/*
 * DFL (Device Feature List)
 *
 * DFL defines a linked list of feature headers within the device MMIO space to
 * provide an extensible way of adding features. Software can walk through these
 * predefined data काष्ठाures to क्रमागतerate features. It is now used in the FPGA.
 * See Documentation/fpga/dfl.rst क्रम more inक्रमmation.
 *
 * The dfl bus type is पूर्णांकroduced to match the inभागidual feature devices (dfl
 * devices) क्रम specअगरic dfl drivers.
 */

/**
 * काष्ठा dfl_device_id -  dfl device identअगरier
 * @type: DFL FIU type of the device. See क्रमागत dfl_id_type.
 * @feature_id: feature identअगरier local to its DFL FIU type.
 * @driver_data: driver specअगरic data.
 */
काष्ठा dfl_device_id अणु
	__u16 type;
	__u16 feature_id;
	kernel_uदीर्घ_t driver_data;
पूर्ण;

#पूर्ण_अगर /* LINUX_MOD_DEVICETABLE_H */
