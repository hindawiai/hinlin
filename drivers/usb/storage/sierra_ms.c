<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "protocol.h"
#समावेश "scsiglue.h"
#समावेश "sierra_ms.h"
#समावेश "debug.h"

#घोषणा SWIMS_USB_REQUEST_SetSwocMode	0x0B
#घोषणा SWIMS_USB_REQUEST_GetSwocInfo	0x0A
#घोषणा SWIMS_USB_INDEX_SetMode		0x0000
#घोषणा SWIMS_SET_MODE_Modem		0x0001

#घोषणा TRU_NORMAL 			0x01
#घोषणा TRU_FORCE_MS 			0x02
#घोषणा TRU_FORCE_MODEM 		0x03

अटल अचिन्हित पूर्णांक swi_tru_install = 1;
module_param(swi_tru_install, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(swi_tru_install, "TRU-Install mode (1=Full Logic (def),"
		 " 2=Force CD-Rom, 3=Force Modem)");

काष्ठा swoc_info अणु
	__u8 rev;
	__u8 reserved[8];
	__u16 LinuxSKU;
	__u16 LinuxVer;
	__u8 reserved2[47];
पूर्ण __attribute__((__packed__));

अटल bool containsFullLinuxPackage(काष्ठा swoc_info *swocInfo)
अणु
	अगर ((swocInfo->LinuxSKU >= 0x2100 && swocInfo->LinuxSKU <= 0x2FFF) ||
	   (swocInfo->LinuxSKU >= 0x7100 && swocInfo->LinuxSKU <= 0x7FFF))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक sierra_set_ms_mode(काष्ठा usb_device *udev, __u16 eSWocMode)
अणु
	पूर्णांक result;
	dev_dbg(&udev->dev, "SWIMS: %s", "DEVICE MODE SWITCH\n");
	result = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			SWIMS_USB_REQUEST_SetSwocMode,	/* __u8 request      */
			USB_TYPE_VENDOR | USB_सूची_OUT,	/* __u8 request type */
			eSWocMode,			/* __u16 value       */
			0x0000,				/* __u16 index       */
			शून्य,				/* व्योम *data        */
			0,				/* __u16 size 	     */
			USB_CTRL_SET_TIMEOUT);		/* पूर्णांक समयout       */
	वापस result;
पूर्ण


अटल पूर्णांक sierra_get_swoc_info(काष्ठा usb_device *udev,
				काष्ठा swoc_info *swocInfo)
अणु
	पूर्णांक result;

	dev_dbg(&udev->dev, "SWIMS: Attempting to get TRU-Install info\n");

	result = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			SWIMS_USB_REQUEST_GetSwocInfo,	/* __u8 request      */
			USB_TYPE_VENDOR | USB_सूची_IN,	/* __u8 request type */
			0,				/* __u16 value       */
			0,				/* __u16 index       */
			(व्योम *) swocInfo,		/* व्योम *data        */
			माप(काष्ठा swoc_info),	/* __u16 size 	     */
			USB_CTRL_SET_TIMEOUT);		/* पूर्णांक समयout 	     */

	swocInfo->LinuxSKU = le16_to_cpu(swocInfo->LinuxSKU);
	swocInfo->LinuxVer = le16_to_cpu(swocInfo->LinuxVer);
	वापस result;
पूर्ण

अटल व्योम debug_swoc(स्थिर काष्ठा device *dev, काष्ठा swoc_info *swocInfo)
अणु
	dev_dbg(dev, "SWIMS: SWoC Rev: %02d\n", swocInfo->rev);
	dev_dbg(dev, "SWIMS: Linux SKU: %04X\n", swocInfo->LinuxSKU);
	dev_dbg(dev, "SWIMS: Linux Version: %04X\n", swocInfo->LinuxVer);
पूर्ण


अटल sमाप_प्रकार truinst_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा swoc_info *swocInfo;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक result;
	अगर (swi_tru_install == TRU_FORCE_MS) अणु
		result = snम_लिखो(buf, PAGE_SIZE, "Forced Mass Storage\n");
	पूर्ण अन्यथा अणु
		swocInfo = kदो_स्मृति(माप(काष्ठा swoc_info), GFP_KERNEL);
		अगर (!swocInfo) अणु
			snम_लिखो(buf, PAGE_SIZE, "Error\n");
			वापस -ENOMEM;
		पूर्ण
		result = sierra_get_swoc_info(udev, swocInfo);
		अगर (result < 0) अणु
			dev_dbg(dev, "SWIMS: failed SWoC query\n");
			kमुक्त(swocInfo);
			snम_लिखो(buf, PAGE_SIZE, "Error\n");
			वापस -EIO;
		पूर्ण
		debug_swoc(dev, swocInfo);
		result = snम_लिखो(buf, PAGE_SIZE,
			"REV=%02d SKU=%04X VER=%04X\n",
			swocInfo->rev,
			swocInfo->LinuxSKU,
			swocInfo->LinuxVer);
		kमुक्त(swocInfo);
	पूर्ण
	वापस result;
पूर्ण
अटल DEVICE_ATTR_RO(truinst);

पूर्णांक sierra_ms_init(काष्ठा us_data *us)
अणु
	पूर्णांक result, retries;
	काष्ठा swoc_info *swocInfo;
	काष्ठा usb_device *udev;

	retries = 3;
	result = 0;
	udev = us->pusb_dev;

	/* Force Modem mode */
	अगर (swi_tru_install == TRU_FORCE_MODEM) अणु
		usb_stor_dbg(us, "SWIMS: Forcing Modem Mode\n");
		result = sierra_set_ms_mode(udev, SWIMS_SET_MODE_Modem);
		अगर (result < 0)
			usb_stor_dbg(us, "SWIMS: Failed to switch to modem mode\n");
		वापस -EIO;
	पूर्ण
	/* Force Mass Storage mode (keep CD-Rom) */
	अन्यथा अगर (swi_tru_install == TRU_FORCE_MS) अणु
		usb_stor_dbg(us, "SWIMS: Forcing Mass Storage Mode\n");
		जाओ complete;
	पूर्ण
	/* Normal TRU-Install Logic */
	अन्यथा अणु
		usb_stor_dbg(us, "SWIMS: Normal SWoC Logic\n");

		swocInfo = kदो_स्मृति(माप(काष्ठा swoc_info),
				GFP_KERNEL);
		अगर (!swocInfo)
			वापस -ENOMEM;

		retries = 3;
		करो अणु
			retries--;
			result = sierra_get_swoc_info(udev, swocInfo);
			अगर (result < 0) अणु
				usb_stor_dbg(us, "SWIMS: Failed SWoC query\n");
				schedule_समयout_unपूर्णांकerruptible(2*HZ);
			पूर्ण
		पूर्ण जबतक (retries && result < 0);

		अगर (result < 0) अणु
			usb_stor_dbg(us, "SWIMS: Completely failed SWoC query\n");
			kमुक्त(swocInfo);
			वापस -EIO;
		पूर्ण

		debug_swoc(&us->pusb_dev->dev, swocInfo);

		/*
		 * If there is not Linux software on the TRU-Install device
		 * then चयन to modem mode
		 */
		अगर (!containsFullLinuxPackage(swocInfo)) अणु
			usb_stor_dbg(us, "SWIMS: Switching to Modem Mode\n");
			result = sierra_set_ms_mode(udev,
				SWIMS_SET_MODE_Modem);
			अगर (result < 0)
				usb_stor_dbg(us, "SWIMS: Failed to switch modem\n");
			kमुक्त(swocInfo);
			वापस -EIO;
		पूर्ण
		kमुक्त(swocInfo);
	पूर्ण
complete:
	वापस device_create_file(&us->pusb_पूर्णांकf->dev, &dev_attr_truinst);
पूर्ण

