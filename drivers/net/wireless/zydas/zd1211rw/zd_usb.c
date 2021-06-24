<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 * Copyright (C) 2006-2007 Michael Wu <flamingice@sourmilk.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/firmware.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/module.h>
#समावेश <net/mac80211.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "zd_def.h"
#समावेश "zd_mac.h"
#समावेश "zd_usb.h"

अटल स्थिर काष्ठा usb_device_id usb_ids[] = अणु
	/* ZD1211 */
	अणु USB_DEVICE(0x0105, 0x145f), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0586, 0x3401), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0586, 0x3402), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0586, 0x3407), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0586, 0x3409), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x079b, 0x004a), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x07b8, 0x6001), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0ace, 0x1211), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0ace, 0xa211), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x170c), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0b3b, 0x1630), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0b3b, 0x5630), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x9071), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x9075), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x126f, 0xa006), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x129b, 0x1666), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x13b1, 0x001e), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x1435, 0x0711), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x14ea, 0xab10), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x14ea, 0xab13), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x157e, 0x300a), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x157e, 0x300b), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x157e, 0x3204), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x157e, 0x3207), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x1740, 0x2000), .driver_info = DEVICE_ZD1211 पूर्ण,
	अणु USB_DEVICE(0x6891, 0xa727), .driver_info = DEVICE_ZD1211 पूर्ण,
	/* ZD1211B */
	अणु USB_DEVICE(0x0053, 0x5301), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0409, 0x0248), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0411, 0x00da), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0471, 0x1236), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0471, 0x1237), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x050d, 0x705c), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x054c, 0x0257), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0586, 0x340a), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0586, 0x340f), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0586, 0x3410), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0586, 0x3412), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0586, 0x3413), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x079b, 0x0062), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x07b8, 0x6001), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x07fa, 0x1196), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x083a, 0x4505), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x083a, 0xe501), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x083a, 0xe503), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x083a, 0xe506), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0ace, 0x1215), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0ace, 0xb215), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x171b), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0baf, 0x0121), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0cde, 0x001a), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0036), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x129b, 0x1667), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x13b1, 0x0024), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x157e, 0x300d), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x1582, 0x6003), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x2019, 0x5303), .driver_info = DEVICE_ZD1211B पूर्ण,
	अणु USB_DEVICE(0x2019, 0xed01), .driver_info = DEVICE_ZD1211B पूर्ण,
	/* "Driverless" devices that need ejecting */
	अणु USB_DEVICE(0x0ace, 0x2011), .driver_info = DEVICE_INSTALLER पूर्ण,
	अणु USB_DEVICE(0x0ace, 0x20ff), .driver_info = DEVICE_INSTALLER पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("USB driver for devices with the ZD1211 chip.");
MODULE_AUTHOR("Ulrich Kunitz");
MODULE_AUTHOR("Daniel Drake");
MODULE_VERSION("1.0");
MODULE_DEVICE_TABLE(usb, usb_ids);

#घोषणा FW_ZD1211_PREFIX	"zd1211/zd1211_"
#घोषणा FW_ZD1211B_PREFIX	"zd1211/zd1211b_"

अटल bool check_पढ़ो_regs(काष्ठा zd_usb *usb, काष्ठा usb_req_पढ़ो_regs *req,
			    अचिन्हित पूर्णांक count);

/* USB device initialization */
अटल व्योम पूर्णांक_urb_complete(काष्ठा urb *urb);

अटल पूर्णांक request_fw_file(
	स्थिर काष्ठा firmware **fw, स्थिर अक्षर *name, काष्ठा device *device)
अणु
	पूर्णांक r;

	dev_dbg_f(device, "fw name %s\n", name);

	r = request_firmware(fw, name, device);
	अगर (r)
		dev_err(device,
		       "Could not load firmware file %s. Error number %d\n",
		       name, r);
	वापस r;
पूर्ण

अटल अंतरभूत u16 get_bcdDevice(स्थिर काष्ठा usb_device *udev)
अणु
	वापस le16_to_cpu(udev->descriptor.bcdDevice);
पूर्ण

क्रमागत upload_code_flags अणु
	REBOOT = 1,
पूर्ण;

/* Ensures that MAX_TRANSFER_SIZE is even. */
#घोषणा MAX_TRANSFER_SIZE (USB_MAX_TRANSFER_SIZE & ~1)

अटल पूर्णांक upload_code(काष्ठा usb_device *udev,
	स्थिर u8 *data, माप_प्रकार size, u16 code_offset, पूर्णांक flags)
अणु
	u8 *p;
	पूर्णांक r;

	/* USB request blocks need "kmalloced" buffers.
	 */
	p = kदो_स्मृति(MAX_TRANSFER_SIZE, GFP_KERNEL);
	अगर (!p) अणु
		r = -ENOMEM;
		जाओ error;
	पूर्ण

	size &= ~1;
	जबतक (size > 0) अणु
		माप_प्रकार transfer_size = size <= MAX_TRANSFER_SIZE ?
			size : MAX_TRANSFER_SIZE;

		dev_dbg_f(&udev->dev, "transfer size %zu\n", transfer_size);

		स_नकल(p, data, transfer_size);
		r = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			USB_REQ_FIRMWARE_DOWNLOAD,
			USB_सूची_OUT | USB_TYPE_VENDOR,
			code_offset, 0, p, transfer_size, 1000 /* ms */);
		अगर (r < 0) अणु
			dev_err(&udev->dev,
			       "USB control request for firmware upload"
			       " failed. Error number %d\n", r);
			जाओ error;
		पूर्ण
		transfer_size = r & ~1;

		size -= transfer_size;
		data += transfer_size;
		code_offset += transfer_size/माप(u16);
	पूर्ण

	अगर (flags & REBOOT) अणु
		u8 ret;

		/* Use "DMA-aware" buffer. */
		r = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			USB_REQ_FIRMWARE_CONFIRM,
			USB_सूची_IN | USB_TYPE_VENDOR,
			0, 0, p, माप(ret), 5000 /* ms */);
		अगर (r != माप(ret)) अणु
			dev_err(&udev->dev,
				"control request firmware confirmation failed."
				" Return value %d\n", r);
			अगर (r >= 0)
				r = -ENODEV;
			जाओ error;
		पूर्ण
		ret = p[0];
		अगर (ret & 0x80) अणु
			dev_err(&udev->dev,
				"Internal error while downloading."
				" Firmware confirm return value %#04x\n",
				(अचिन्हित पूर्णांक)ret);
			r = -ENODEV;
			जाओ error;
		पूर्ण
		dev_dbg_f(&udev->dev, "firmware confirm return value %#04x\n",
			(अचिन्हित पूर्णांक)ret);
	पूर्ण

	r = 0;
error:
	kमुक्त(p);
	वापस r;
पूर्ण

अटल u16 get_word(स्थिर व्योम *data, u16 offset)
अणु
	स्थिर __le16 *p = data;
	वापस le16_to_cpu(p[offset]);
पूर्ण

अटल अक्षर *get_fw_name(काष्ठा zd_usb *usb, अक्षर *buffer, माप_प्रकार size,
	               स्थिर अक्षर* postfix)
अणु
	scnम_लिखो(buffer, size, "%s%s",
		usb->is_zd1211b ?
			FW_ZD1211B_PREFIX : FW_ZD1211_PREFIX,
		postfix);
	वापस buffer;
पूर्ण

अटल पूर्णांक handle_version_mismatch(काष्ठा zd_usb *usb,
	स्थिर काष्ठा firmware *ub_fw)
अणु
	काष्ठा usb_device *udev = zd_usb_to_usbdev(usb);
	स्थिर काष्ठा firmware *ur_fw = शून्य;
	पूर्णांक offset;
	पूर्णांक r = 0;
	अक्षर fw_name[128];

	r = request_fw_file(&ur_fw,
		get_fw_name(usb, fw_name, माप(fw_name), "ur"),
		&udev->dev);
	अगर (r)
		जाओ error;

	r = upload_code(udev, ur_fw->data, ur_fw->size, FW_START, REBOOT);
	अगर (r)
		जाओ error;

	offset = (E2P_BOOT_CODE_OFFSET * माप(u16));
	r = upload_code(udev, ub_fw->data + offset, ub_fw->size - offset,
		E2P_START + E2P_BOOT_CODE_OFFSET, REBOOT);

	/* At this poपूर्णांक, the venकरोr driver करोwnloads the whole firmware
	 * image, hacks around with version IDs, and uploads it again,
	 * completely overwriting the boot code. We करो not करो this here as
	 * it is not required on any tested devices, and it is suspected to
	 * cause problems. */
error:
	release_firmware(ur_fw);
	वापस r;
पूर्ण

अटल पूर्णांक upload_firmware(काष्ठा zd_usb *usb)
अणु
	पूर्णांक r;
	u16 fw_bcdDevice;
	u16 bcdDevice;
	काष्ठा usb_device *udev = zd_usb_to_usbdev(usb);
	स्थिर काष्ठा firmware *ub_fw = शून्य;
	स्थिर काष्ठा firmware *uph_fw = शून्य;
	अक्षर fw_name[128];

	bcdDevice = get_bcdDevice(udev);

	r = request_fw_file(&ub_fw,
		get_fw_name(usb, fw_name, माप(fw_name), "ub"),
		&udev->dev);
	अगर (r)
		जाओ error;

	fw_bcdDevice = get_word(ub_fw->data, E2P_DATA_OFFSET);

	अगर (fw_bcdDevice != bcdDevice) अणु
		dev_info(&udev->dev,
			"firmware version %#06x and device bootcode version "
			"%#06x differ\n", fw_bcdDevice, bcdDevice);
		अगर (bcdDevice <= 0x4313)
			dev_warn(&udev->dev, "device has old bootcode, please "
				"report success or failure\n");

		r = handle_version_mismatch(usb, ub_fw);
		अगर (r)
			जाओ error;
	पूर्ण अन्यथा अणु
		dev_dbg_f(&udev->dev,
			"firmware device id %#06x is equal to the "
			"actual device id\n", fw_bcdDevice);
	पूर्ण


	r = request_fw_file(&uph_fw,
		get_fw_name(usb, fw_name, माप(fw_name), "uphr"),
		&udev->dev);
	अगर (r)
		जाओ error;

	r = upload_code(udev, uph_fw->data, uph_fw->size, FW_START, REBOOT);
	अगर (r) अणु
		dev_err(&udev->dev,
			"Could not upload firmware code uph. Error number %d\n",
			r);
	पूर्ण

	/* FALL-THROUGH */
error:
	release_firmware(ub_fw);
	release_firmware(uph_fw);
	वापस r;
पूर्ण

MODULE_FIRMWARE(FW_ZD1211B_PREFIX "ur");
MODULE_FIRMWARE(FW_ZD1211_PREFIX "ur");
MODULE_FIRMWARE(FW_ZD1211B_PREFIX "ub");
MODULE_FIRMWARE(FW_ZD1211_PREFIX "ub");
MODULE_FIRMWARE(FW_ZD1211B_PREFIX "uphr");
MODULE_FIRMWARE(FW_ZD1211_PREFIX "uphr");

/* Read data from device address space using "firmware interface" which करोes
 * not require firmware to be loaded. */
पूर्णांक zd_usb_पढ़ो_fw(काष्ठा zd_usb *usb, zd_addr_t addr, u8 *data, u16 len)
अणु
	पूर्णांक r;
	काष्ठा usb_device *udev = zd_usb_to_usbdev(usb);
	u8 *buf;

	/* Use "DMA-aware" buffer. */
	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	r = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
		USB_REQ_FIRMWARE_READ_DATA, USB_सूची_IN | 0x40, addr, 0,
		buf, len, 5000);
	अगर (r < 0) अणु
		dev_err(&udev->dev,
			"read over firmware interface failed: %d\n", r);
		जाओ निकास;
	पूर्ण अन्यथा अगर (r != len) अणु
		dev_err(&udev->dev,
			"incomplete read over firmware interface: %d/%d\n",
			r, len);
		r = -EIO;
		जाओ निकास;
	पूर्ण
	r = 0;
	स_नकल(data, buf, len);
निकास:
	kमुक्त(buf);
	वापस r;
पूर्ण

#घोषणा urb_dev(urb) (&(urb)->dev->dev)

अटल अंतरभूत व्योम handle_regs_पूर्णांक_override(काष्ठा urb *urb)
अणु
	काष्ठा zd_usb *usb = urb->context;
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पूर्णांकr->lock, flags);
	अगर (atomic_पढ़ो(&पूर्णांकr->पढ़ो_regs_enabled)) अणु
		atomic_set(&पूर्णांकr->पढ़ो_regs_enabled, 0);
		पूर्णांकr->पढ़ो_regs_पूर्णांक_overridden = 1;
		complete(&पूर्णांकr->पढ़ो_regs.completion);
	पूर्ण
	spin_unlock_irqrestore(&पूर्णांकr->lock, flags);
पूर्ण

अटल अंतरभूत व्योम handle_regs_पूर्णांक(काष्ठा urb *urb)
अणु
	काष्ठा zd_usb *usb = urb->context;
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;
	अचिन्हित दीर्घ flags;
	पूर्णांक len;
	u16 पूर्णांक_num;

	spin_lock_irqsave(&पूर्णांकr->lock, flags);

	पूर्णांक_num = le16_to_cpu(*(__le16 *)(urb->transfer_buffer+2));
	अगर (पूर्णांक_num == CR_INTERRUPT) अणु
		काष्ठा zd_mac *mac = zd_hw_mac(zd_usb_to_hw(urb->context));
		spin_lock(&mac->lock);
		स_नकल(&mac->पूर्णांकr_buffer, urb->transfer_buffer,
				USB_MAX_EP_INT_BUFFER);
		spin_unlock(&mac->lock);
		schedule_work(&mac->process_पूर्णांकr);
	पूर्ण अन्यथा अगर (atomic_पढ़ो(&पूर्णांकr->पढ़ो_regs_enabled)) अणु
		len = urb->actual_length;
		पूर्णांकr->पढ़ो_regs.length = urb->actual_length;
		अगर (len > माप(पूर्णांकr->पढ़ो_regs.buffer))
			len = माप(पूर्णांकr->पढ़ो_regs.buffer);

		स_नकल(पूर्णांकr->पढ़ो_regs.buffer, urb->transfer_buffer, len);

		/* Someबार USB_INT_ID_REGS is not overridden, but comes after
		 * USB_INT_ID_RETRY_FAILED. Read-reg retry then माला_लो this
		 * delayed USB_INT_ID_REGS, but leaves USB_INT_ID_REGS of
		 * retry unhandled. Next पढ़ो-reg command then might catch
		 * this wrong USB_INT_ID_REGS. Fix by ignoring wrong पढ़ोs.
		 */
		अगर (!check_पढ़ो_regs(usb, पूर्णांकr->पढ़ो_regs.req,
						पूर्णांकr->पढ़ो_regs.req_count))
			जाओ out;

		atomic_set(&पूर्णांकr->पढ़ो_regs_enabled, 0);
		पूर्णांकr->पढ़ो_regs_पूर्णांक_overridden = 0;
		complete(&पूर्णांकr->पढ़ो_regs.completion);

		जाओ out;
	पूर्ण

out:
	spin_unlock_irqrestore(&पूर्णांकr->lock, flags);

	/* CR_INTERRUPT might override पढ़ो_reg too. */
	अगर (पूर्णांक_num == CR_INTERRUPT && atomic_पढ़ो(&पूर्णांकr->पढ़ो_regs_enabled))
		handle_regs_पूर्णांक_override(urb);
पूर्ण

अटल व्योम पूर्णांक_urb_complete(काष्ठा urb *urb)
अणु
	पूर्णांक r;
	काष्ठा usb_पूर्णांक_header *hdr;
	काष्ठा zd_usb *usb;
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ESHUTDOWN:
	हाल -EINVAL:
	हाल -ENODEV:
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -EPIPE:
		dev_dbg_f(urb_dev(urb), "urb %p error %d\n", urb, urb->status);
		वापस;
	शेष:
		dev_dbg_f(urb_dev(urb), "urb %p error %d\n", urb, urb->status);
		जाओ resubmit;
	पूर्ण

	अगर (urb->actual_length < माप(hdr)) अणु
		dev_dbg_f(urb_dev(urb), "error: urb %p to small\n", urb);
		जाओ resubmit;
	पूर्ण

	hdr = urb->transfer_buffer;
	अगर (hdr->type != USB_INT_TYPE) अणु
		dev_dbg_f(urb_dev(urb), "error: urb %p wrong type\n", urb);
		जाओ resubmit;
	पूर्ण

	/* USB_INT_ID_RETRY_FAILED triggered by tx-urb submit can override
	 * pending USB_INT_ID_REGS causing पढ़ो command समयout.
	 */
	usb = urb->context;
	पूर्णांकr = &usb->पूर्णांकr;
	अगर (hdr->id != USB_INT_ID_REGS && atomic_पढ़ो(&पूर्णांकr->पढ़ो_regs_enabled))
		handle_regs_पूर्णांक_override(urb);

	चयन (hdr->id) अणु
	हाल USB_INT_ID_REGS:
		handle_regs_पूर्णांक(urb);
		अवरोध;
	हाल USB_INT_ID_RETRY_FAILED:
		zd_mac_tx_failed(urb);
		अवरोध;
	शेष:
		dev_dbg_f(urb_dev(urb), "error: urb %p unknown id %x\n", urb,
			(अचिन्हित पूर्णांक)hdr->id);
		जाओ resubmit;
	पूर्ण

resubmit:
	r = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (r) अणु
		dev_dbg_f(urb_dev(urb), "error: resubmit urb %p err code %d\n",
			  urb, r);
		/* TODO: add worker to reset पूर्णांकr->urb */
	पूर्ण
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांक_urb_पूर्णांकerval(काष्ठा usb_device *udev)
अणु
	चयन (udev->speed) अणु
	हाल USB_SPEED_HIGH:
		वापस 4;
	हाल USB_SPEED_LOW:
		वापस 10;
	हाल USB_SPEED_FULL:
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक usb_पूर्णांक_enabled(काष्ठा zd_usb *usb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;
	काष्ठा urb *urb;

	spin_lock_irqsave(&पूर्णांकr->lock, flags);
	urb = पूर्णांकr->urb;
	spin_unlock_irqrestore(&पूर्णांकr->lock, flags);
	वापस urb != शून्य;
पूर्ण

पूर्णांक zd_usb_enable_पूर्णांक(काष्ठा zd_usb *usb)
अणु
	पूर्णांक r;
	काष्ठा usb_device *udev = zd_usb_to_usbdev(usb);
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;
	काष्ठा urb *urb;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb) अणु
		r = -ENOMEM;
		जाओ out;
	पूर्ण

	ZD_ASSERT(!irqs_disabled());
	spin_lock_irq(&पूर्णांकr->lock);
	अगर (पूर्णांकr->urb) अणु
		spin_unlock_irq(&पूर्णांकr->lock);
		r = 0;
		जाओ error_मुक्त_urb;
	पूर्ण
	पूर्णांकr->urb = urb;
	spin_unlock_irq(&पूर्णांकr->lock);

	r = -ENOMEM;
	पूर्णांकr->buffer = usb_alloc_coherent(udev, USB_MAX_EP_INT_BUFFER,
					  GFP_KERNEL, &पूर्णांकr->buffer_dma);
	अगर (!पूर्णांकr->buffer) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"couldn't allocate transfer_buffer\n");
		जाओ error_set_urb_null;
	पूर्ण

	usb_fill_पूर्णांक_urb(urb, udev, usb_rcvपूर्णांकpipe(udev, EP_INT_IN),
			 पूर्णांकr->buffer, USB_MAX_EP_INT_BUFFER,
			 पूर्णांक_urb_complete, usb,
			 पूर्णांकr->पूर्णांकerval);
	urb->transfer_dma = पूर्णांकr->buffer_dma;
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	dev_dbg_f(zd_usb_dev(usb), "submit urb %p\n", पूर्णांकr->urb);
	r = usb_submit_urb(urb, GFP_KERNEL);
	अगर (r) अणु
		dev_dbg_f(zd_usb_dev(usb),
			 "Couldn't submit urb. Error number %d\n", r);
		जाओ error;
	पूर्ण

	वापस 0;
error:
	usb_मुक्त_coherent(udev, USB_MAX_EP_INT_BUFFER,
			  पूर्णांकr->buffer, पूर्णांकr->buffer_dma);
error_set_urb_null:
	spin_lock_irq(&पूर्णांकr->lock);
	पूर्णांकr->urb = शून्य;
	spin_unlock_irq(&पूर्णांकr->lock);
error_मुक्त_urb:
	usb_मुक्त_urb(urb);
out:
	वापस r;
पूर्ण

व्योम zd_usb_disable_पूर्णांक(काष्ठा zd_usb *usb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_device *udev = zd_usb_to_usbdev(usb);
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;
	काष्ठा urb *urb;
	व्योम *buffer;
	dma_addr_t buffer_dma;

	spin_lock_irqsave(&पूर्णांकr->lock, flags);
	urb = पूर्णांकr->urb;
	अगर (!urb) अणु
		spin_unlock_irqrestore(&पूर्णांकr->lock, flags);
		वापस;
	पूर्ण
	पूर्णांकr->urb = शून्य;
	buffer = पूर्णांकr->buffer;
	buffer_dma = पूर्णांकr->buffer_dma;
	पूर्णांकr->buffer = शून्य;
	spin_unlock_irqrestore(&पूर्णांकr->lock, flags);

	usb_समाप्त_urb(urb);
	dev_dbg_f(zd_usb_dev(usb), "urb %p killed\n", urb);
	usb_मुक्त_urb(urb);

	usb_मुक्त_coherent(udev, USB_MAX_EP_INT_BUFFER, buffer, buffer_dma);
पूर्ण

अटल व्योम handle_rx_packet(काष्ठा zd_usb *usb, स्थिर u8 *buffer,
			     अचिन्हित पूर्णांक length)
अणु
	पूर्णांक i;
	स्थिर काष्ठा rx_length_info *length_info;

	अगर (length < माप(काष्ठा rx_length_info)) अणु
		/* It's not a complete packet anyhow. */
		dev_dbg_f(zd_usb_dev(usb), "invalid, small RX packet : %d\n",
					   length);
		वापस;
	पूर्ण
	length_info = (काष्ठा rx_length_info *)
		(buffer + length - माप(काष्ठा rx_length_info));

	/* It might be that three frames are merged पूर्णांकo a single URB
	 * transaction. We have to check क्रम the length info tag.
	 *
	 * While testing we discovered that length_info might be unaligned,
	 * because अगर USB transactions are merged, the last packet will not
	 * be padded. Unaligned access might also happen अगर the length_info
	 * काष्ठाure is not present.
	 */
	अगर (get_unaligned_le16(&length_info->tag) == RX_LENGTH_INFO_TAG)
	अणु
		अचिन्हित पूर्णांक l, k, n;
		क्रम (i = 0, l = 0;; i++) अणु
			k = get_unaligned_le16(&length_info->length[i]);
			अगर (k == 0)
				वापस;
			n = l+k;
			अगर (n > length)
				वापस;
			zd_mac_rx(zd_usb_to_hw(usb), buffer+l, k);
			अगर (i >= 2)
				वापस;
			l = (n+3) & ~3;
		पूर्ण
	पूर्ण अन्यथा अणु
		zd_mac_rx(zd_usb_to_hw(usb), buffer, length);
	पूर्ण
पूर्ण

अटल व्योम rx_urb_complete(काष्ठा urb *urb)
अणु
	पूर्णांक r;
	काष्ठा zd_usb *usb;
	काष्ठा zd_usb_rx *rx;
	स्थिर u8 *buffer;
	अचिन्हित पूर्णांक length;
	अचिन्हित दीर्घ flags;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ESHUTDOWN:
	हाल -EINVAL:
	हाल -ENODEV:
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -EPIPE:
		dev_dbg_f(urb_dev(urb), "urb %p error %d\n", urb, urb->status);
		वापस;
	शेष:
		dev_dbg_f(urb_dev(urb), "urb %p error %d\n", urb, urb->status);
		जाओ resubmit;
	पूर्ण

	buffer = urb->transfer_buffer;
	length = urb->actual_length;
	usb = urb->context;
	rx = &usb->rx;

	tasklet_schedule(&rx->reset_समयr_tasklet);

	अगर (length%rx->usb_packet_size > rx->usb_packet_size-4) अणु
		/* If there is an old first fragment, we करोn't care. */
		dev_dbg_f(urb_dev(urb), "*** first fragment ***\n");
		ZD_ASSERT(length <= ARRAY_SIZE(rx->fragment));
		spin_lock_irqsave(&rx->lock, flags);
		स_नकल(rx->fragment, buffer, length);
		rx->fragment_length = length;
		spin_unlock_irqrestore(&rx->lock, flags);
		जाओ resubmit;
	पूर्ण

	spin_lock_irqsave(&rx->lock, flags);
	अगर (rx->fragment_length > 0) अणु
		/* We are on a second fragment, we believe */
		ZD_ASSERT(length + rx->fragment_length <=
			  ARRAY_SIZE(rx->fragment));
		dev_dbg_f(urb_dev(urb), "*** second fragment ***\n");
		स_नकल(rx->fragment+rx->fragment_length, buffer, length);
		handle_rx_packet(usb, rx->fragment,
			         rx->fragment_length + length);
		rx->fragment_length = 0;
		spin_unlock_irqrestore(&rx->lock, flags);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&rx->lock, flags);
		handle_rx_packet(usb, buffer, length);
	पूर्ण

resubmit:
	r = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (r)
		dev_dbg_f(urb_dev(urb), "urb %p resubmit error %d\n", urb, r);
पूर्ण

अटल काष्ठा urb *alloc_rx_urb(काष्ठा zd_usb *usb)
अणु
	काष्ठा usb_device *udev = zd_usb_to_usbdev(usb);
	काष्ठा urb *urb;
	व्योम *buffer;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस शून्य;
	buffer = usb_alloc_coherent(udev, USB_MAX_RX_SIZE, GFP_KERNEL,
				    &urb->transfer_dma);
	अगर (!buffer) अणु
		usb_मुक्त_urb(urb);
		वापस शून्य;
	पूर्ण

	usb_fill_bulk_urb(urb, udev, usb_rcvbulkpipe(udev, EP_DATA_IN),
			  buffer, USB_MAX_RX_SIZE,
			  rx_urb_complete, usb);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	वापस urb;
पूर्ण

अटल व्योम मुक्त_rx_urb(काष्ठा urb *urb)
अणु
	अगर (!urb)
		वापस;
	usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	usb_मुक्त_urb(urb);
पूर्ण

अटल पूर्णांक __zd_usb_enable_rx(काष्ठा zd_usb *usb)
अणु
	पूर्णांक i, r;
	काष्ठा zd_usb_rx *rx = &usb->rx;
	काष्ठा urb **urbs;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	r = -ENOMEM;
	urbs = kसुस्मृति(RX_URBS_COUNT, माप(काष्ठा urb *), GFP_KERNEL);
	अगर (!urbs)
		जाओ error;
	क्रम (i = 0; i < RX_URBS_COUNT; i++) अणु
		urbs[i] = alloc_rx_urb(usb);
		अगर (!urbs[i])
			जाओ error;
	पूर्ण

	ZD_ASSERT(!irqs_disabled());
	spin_lock_irq(&rx->lock);
	अगर (rx->urbs) अणु
		spin_unlock_irq(&rx->lock);
		r = 0;
		जाओ error;
	पूर्ण
	rx->urbs = urbs;
	rx->urbs_count = RX_URBS_COUNT;
	spin_unlock_irq(&rx->lock);

	क्रम (i = 0; i < RX_URBS_COUNT; i++) अणु
		r = usb_submit_urb(urbs[i], GFP_KERNEL);
		अगर (r)
			जाओ error_submit;
	पूर्ण

	वापस 0;
error_submit:
	क्रम (i = 0; i < RX_URBS_COUNT; i++) अणु
		usb_समाप्त_urb(urbs[i]);
	पूर्ण
	spin_lock_irq(&rx->lock);
	rx->urbs = शून्य;
	rx->urbs_count = 0;
	spin_unlock_irq(&rx->lock);
error:
	अगर (urbs) अणु
		क्रम (i = 0; i < RX_URBS_COUNT; i++)
			मुक्त_rx_urb(urbs[i]);
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक zd_usb_enable_rx(काष्ठा zd_usb *usb)
अणु
	पूर्णांक r;
	काष्ठा zd_usb_rx *rx = &usb->rx;

	mutex_lock(&rx->setup_mutex);
	r = __zd_usb_enable_rx(usb);
	mutex_unlock(&rx->setup_mutex);

	zd_usb_reset_rx_idle_समयr(usb);

	वापस r;
पूर्ण

अटल व्योम __zd_usb_disable_rx(काष्ठा zd_usb *usb)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा urb **urbs;
	अचिन्हित पूर्णांक count;
	काष्ठा zd_usb_rx *rx = &usb->rx;

	spin_lock_irqsave(&rx->lock, flags);
	urbs = rx->urbs;
	count = rx->urbs_count;
	spin_unlock_irqrestore(&rx->lock, flags);
	अगर (!urbs)
		वापस;

	क्रम (i = 0; i < count; i++) अणु
		usb_समाप्त_urb(urbs[i]);
		मुक्त_rx_urb(urbs[i]);
	पूर्ण
	kमुक्त(urbs);

	spin_lock_irqsave(&rx->lock, flags);
	rx->urbs = शून्य;
	rx->urbs_count = 0;
	spin_unlock_irqrestore(&rx->lock, flags);
पूर्ण

व्योम zd_usb_disable_rx(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_rx *rx = &usb->rx;

	mutex_lock(&rx->setup_mutex);
	__zd_usb_disable_rx(usb);
	mutex_unlock(&rx->setup_mutex);

	tasklet_समाप्त(&rx->reset_समयr_tasklet);
	cancel_delayed_work_sync(&rx->idle_work);
पूर्ण

अटल व्योम zd_usb_reset_rx(काष्ठा zd_usb *usb)
अणु
	bool करो_reset;
	काष्ठा zd_usb_rx *rx = &usb->rx;
	अचिन्हित दीर्घ flags;

	mutex_lock(&rx->setup_mutex);

	spin_lock_irqsave(&rx->lock, flags);
	करो_reset = rx->urbs != शून्य;
	spin_unlock_irqrestore(&rx->lock, flags);

	अगर (करो_reset) अणु
		__zd_usb_disable_rx(usb);
		__zd_usb_enable_rx(usb);
	पूर्ण

	mutex_unlock(&rx->setup_mutex);

	अगर (करो_reset)
		zd_usb_reset_rx_idle_समयr(usb);
पूर्ण

/**
 * zd_usb_disable_tx - disable transmission
 * @usb: the zd1211rw-निजी USB काष्ठाure
 *
 * Frees all URBs in the मुक्त list and marks the transmission as disabled.
 */
व्योम zd_usb_disable_tx(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_tx *tx = &usb->tx;
	अचिन्हित दीर्घ flags;

	atomic_set(&tx->enabled, 0);

	/* समाप्त all submitted tx-urbs */
	usb_समाप्त_anchored_urbs(&tx->submitted);

	spin_lock_irqsave(&tx->lock, flags);
	WARN_ON(!skb_queue_empty(&tx->submitted_skbs));
	WARN_ON(tx->submitted_urbs != 0);
	tx->submitted_urbs = 0;
	spin_unlock_irqrestore(&tx->lock, flags);

	/* The stopped state is ignored, relying on ieee80211_wake_queues()
	 * in a potentionally following zd_usb_enable_tx().
	 */
पूर्ण

/**
 * zd_usb_enable_tx - enables transmission
 * @usb: a &काष्ठा zd_usb poपूर्णांकer
 *
 * This function enables transmission and prepares the &zd_usb_tx data
 * काष्ठाure.
 */
व्योम zd_usb_enable_tx(काष्ठा zd_usb *usb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zd_usb_tx *tx = &usb->tx;

	spin_lock_irqsave(&tx->lock, flags);
	atomic_set(&tx->enabled, 1);
	tx->submitted_urbs = 0;
	ieee80211_wake_queues(zd_usb_to_hw(usb));
	tx->stopped = 0;
	spin_unlock_irqrestore(&tx->lock, flags);
पूर्ण

अटल व्योम tx_dec_submitted_urbs(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_tx *tx = &usb->tx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tx->lock, flags);
	--tx->submitted_urbs;
	अगर (tx->stopped && tx->submitted_urbs <= ZD_USB_TX_LOW) अणु
		ieee80211_wake_queues(zd_usb_to_hw(usb));
		tx->stopped = 0;
	पूर्ण
	spin_unlock_irqrestore(&tx->lock, flags);
पूर्ण

अटल व्योम tx_inc_submitted_urbs(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_tx *tx = &usb->tx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tx->lock, flags);
	++tx->submitted_urbs;
	अगर (!tx->stopped && tx->submitted_urbs > ZD_USB_TX_HIGH) अणु
		ieee80211_stop_queues(zd_usb_to_hw(usb));
		tx->stopped = 1;
	पूर्ण
	spin_unlock_irqrestore(&tx->lock, flags);
पूर्ण

/**
 * tx_urb_complete - completes the execution of an URB
 * @urb: a URB
 *
 * This function is called अगर the URB has been transferred to a device or an
 * error has happened.
 */
अटल व्योम tx_urb_complete(काष्ठा urb *urb)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा zd_usb *usb;
	काष्ठा zd_usb_tx *tx;

	skb = (काष्ठा sk_buff *)urb->context;
	info = IEEE80211_SKB_CB(skb);
	/*
	 * grab 'usb' poपूर्णांकer beक्रमe handing off the skb (since
	 * it might be मुक्तd by zd_mac_tx_to_dev or mac80211)
	 */
	usb = &zd_hw_mac(info->rate_driver_data[0])->chip.usb;
	tx = &usb->tx;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ESHUTDOWN:
	हाल -EINVAL:
	हाल -ENODEV:
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -EPIPE:
		dev_dbg_f(urb_dev(urb), "urb %p error %d\n", urb, urb->status);
		अवरोध;
	शेष:
		dev_dbg_f(urb_dev(urb), "urb %p error %d\n", urb, urb->status);
		जाओ resubmit;
	पूर्ण
मुक्त_urb:
	skb_unlink(skb, &usb->tx.submitted_skbs);
	zd_mac_tx_to_dev(skb, urb->status);
	usb_मुक्त_urb(urb);
	tx_dec_submitted_urbs(usb);
	वापस;
resubmit:
	usb_anchor_urb(urb, &tx->submitted);
	r = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (r) अणु
		usb_unanchor_urb(urb);
		dev_dbg_f(urb_dev(urb), "error resubmit urb %p %d\n", urb, r);
		जाओ मुक्त_urb;
	पूर्ण
पूर्ण

/**
 * zd_usb_tx: initiates transfer of a frame of the device
 *
 * @usb: the zd1211rw-निजी USB काष्ठाure
 * @skb: a &काष्ठा sk_buff poपूर्णांकer
 *
 * This function tranmits a frame to the device. It करोesn't रुको क्रम
 * completion. The frame must contain the control set and have all the
 * control set inक्रमmation available.
 *
 * The function वापसs 0 अगर the transfer has been successfully initiated.
 */
पूर्णांक zd_usb_tx(काष्ठा zd_usb *usb, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा usb_device *udev = zd_usb_to_usbdev(usb);
	काष्ठा urb *urb;
	काष्ठा zd_usb_tx *tx = &usb->tx;

	अगर (!atomic_पढ़ो(&tx->enabled)) अणु
		r = -ENOENT;
		जाओ out;
	पूर्ण

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		r = -ENOMEM;
		जाओ out;
	पूर्ण

	usb_fill_bulk_urb(urb, udev, usb_sndbulkpipe(udev, EP_DATA_OUT),
		          skb->data, skb->len, tx_urb_complete, skb);

	info->rate_driver_data[1] = (व्योम *)jअगरfies;
	skb_queue_tail(&tx->submitted_skbs, skb);
	usb_anchor_urb(urb, &tx->submitted);

	r = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (r) अणु
		dev_dbg_f(zd_usb_dev(usb), "error submit urb %p %d\n", urb, r);
		usb_unanchor_urb(urb);
		skb_unlink(skb, &tx->submitted_skbs);
		जाओ error;
	पूर्ण
	tx_inc_submitted_urbs(usb);
	वापस 0;
error:
	usb_मुक्त_urb(urb);
out:
	वापस r;
पूर्ण

अटल bool zd_tx_समयout(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_tx *tx = &usb->tx;
	काष्ठा sk_buff_head *q = &tx->submitted_skbs;
	काष्ठा sk_buff *skb, *skbnext;
	काष्ठा ieee80211_tx_info *info;
	अचिन्हित दीर्घ flags, trans_start;
	bool have_समयकरोut = false;

	spin_lock_irqsave(&q->lock, flags);
	skb_queue_walk_safe(q, skb, skbnext) अणु
		info = IEEE80211_SKB_CB(skb);
		trans_start = (अचिन्हित दीर्घ)info->rate_driver_data[1];

		अगर (समय_is_beक्रमe_jअगरfies(trans_start + ZD_TX_TIMEOUT)) अणु
			have_समयकरोut = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&q->lock, flags);

	वापस have_समयकरोut;
पूर्ण

अटल व्योम zd_tx_watchकरोg_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zd_usb *usb =
		container_of(work, काष्ठा zd_usb, tx.watchकरोg_work.work);
	काष्ठा zd_usb_tx *tx = &usb->tx;

	अगर (!atomic_पढ़ो(&tx->enabled) || !tx->watchकरोg_enabled)
		जाओ out;
	अगर (!zd_tx_समयout(usb))
		जाओ out;

	/* TX halted, try reset */
	dev_warn(zd_usb_dev(usb), "TX-stall detected, resetting device...");

	usb_queue_reset_device(usb->पूर्णांकf);

	/* reset will stop this worker, करोn't rearm */
	वापस;
out:
	queue_delayed_work(zd_workqueue, &tx->watchकरोg_work,
			   ZD_TX_WATCHDOG_INTERVAL);
पूर्ण

व्योम zd_tx_watchकरोg_enable(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_tx *tx = &usb->tx;

	अगर (!tx->watchकरोg_enabled) अणु
		dev_dbg_f(zd_usb_dev(usb), "\n");
		queue_delayed_work(zd_workqueue, &tx->watchकरोg_work,
				   ZD_TX_WATCHDOG_INTERVAL);
		tx->watchकरोg_enabled = 1;
	पूर्ण
पूर्ण

व्योम zd_tx_watchकरोg_disable(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_tx *tx = &usb->tx;

	अगर (tx->watchकरोg_enabled) अणु
		dev_dbg_f(zd_usb_dev(usb), "\n");
		tx->watchकरोg_enabled = 0;
		cancel_delayed_work_sync(&tx->watchकरोg_work);
	पूर्ण
पूर्ण

अटल व्योम zd_rx_idle_समयr_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zd_usb *usb =
		container_of(work, काष्ठा zd_usb, rx.idle_work.work);
	काष्ठा zd_mac *mac = zd_usb_to_mac(usb);

	अगर (!test_bit(ZD_DEVICE_RUNNING, &mac->flags))
		वापस;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	/* 30 seconds since last rx, reset rx */
	zd_usb_reset_rx(usb);
पूर्ण

अटल व्योम zd_usb_reset_rx_idle_समयr_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा zd_usb *usb = from_tasklet(usb, t, rx.reset_समयr_tasklet);

	zd_usb_reset_rx_idle_समयr(usb);
पूर्ण

व्योम zd_usb_reset_rx_idle_समयr(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_rx *rx = &usb->rx;

	mod_delayed_work(zd_workqueue, &rx->idle_work, ZD_RX_IDLE_INTERVAL);
पूर्ण

अटल अंतरभूत व्योम init_usb_पूर्णांकerrupt(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;

	spin_lock_init(&पूर्णांकr->lock);
	पूर्णांकr->पूर्णांकerval = पूर्णांक_urb_पूर्णांकerval(zd_usb_to_usbdev(usb));
	init_completion(&पूर्णांकr->पढ़ो_regs.completion);
	atomic_set(&पूर्णांकr->पढ़ो_regs_enabled, 0);
	पूर्णांकr->पढ़ो_regs.cr_पूर्णांक_addr = cpu_to_le16((u16)CR_INTERRUPT);
पूर्ण

अटल अंतरभूत व्योम init_usb_rx(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_rx *rx = &usb->rx;

	spin_lock_init(&rx->lock);
	mutex_init(&rx->setup_mutex);
	अगर (पूर्णांकerface_to_usbdev(usb->पूर्णांकf)->speed == USB_SPEED_HIGH) अणु
		rx->usb_packet_size = 512;
	पूर्ण अन्यथा अणु
		rx->usb_packet_size = 64;
	पूर्ण
	ZD_ASSERT(rx->fragment_length == 0);
	INIT_DELAYED_WORK(&rx->idle_work, zd_rx_idle_समयr_handler);
	rx->reset_समयr_tasklet.func = (व्योम (*))
					zd_usb_reset_rx_idle_समयr_tasklet;
	rx->reset_समयr_tasklet.data = (अचिन्हित दीर्घ)&rx->reset_समयr_tasklet;
पूर्ण

अटल अंतरभूत व्योम init_usb_tx(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_tx *tx = &usb->tx;

	spin_lock_init(&tx->lock);
	atomic_set(&tx->enabled, 0);
	tx->stopped = 0;
	skb_queue_head_init(&tx->submitted_skbs);
	init_usb_anchor(&tx->submitted);
	tx->submitted_urbs = 0;
	tx->watchकरोg_enabled = 0;
	INIT_DELAYED_WORK(&tx->watchकरोg_work, zd_tx_watchकरोg_handler);
पूर्ण

व्योम zd_usb_init(काष्ठा zd_usb *usb, काष्ठा ieee80211_hw *hw,
	         काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	स_रखो(usb, 0, माप(*usb));
	usb->पूर्णांकf = usb_get_पूर्णांकf(पूर्णांकf);
	usb_set_पूर्णांकfdata(usb->पूर्णांकf, hw);
	init_usb_anchor(&usb->submitted_cmds);
	init_usb_पूर्णांकerrupt(usb);
	init_usb_tx(usb);
	init_usb_rx(usb);
पूर्ण

व्योम zd_usb_clear(काष्ठा zd_usb *usb)
अणु
	usb_set_पूर्णांकfdata(usb->पूर्णांकf, शून्य);
	usb_put_पूर्णांकf(usb->पूर्णांकf);
	ZD_MEMCLEAR(usb, माप(*usb));
	/* FIXME: usb_पूर्णांकerrupt, usb_tx, usb_rx? */
पूर्ण

अटल स्थिर अक्षर *speed(क्रमागत usb_device_speed speed)
अणु
	चयन (speed) अणु
	हाल USB_SPEED_LOW:
		वापस "low";
	हाल USB_SPEED_FULL:
		वापस "full";
	हाल USB_SPEED_HIGH:
		वापस "high";
	शेष:
		वापस "unknown speed";
	पूर्ण
पूर्ण

अटल पूर्णांक scnprपूर्णांक_id(काष्ठा usb_device *udev, अक्षर *buffer, माप_प्रकार size)
अणु
	वापस scnम_लिखो(buffer, size, "%04hx:%04hx v%04hx %s",
		le16_to_cpu(udev->descriptor.idVenकरोr),
		le16_to_cpu(udev->descriptor.idProduct),
		get_bcdDevice(udev),
		speed(udev->speed));
पूर्ण

पूर्णांक zd_usb_scnprपूर्णांक_id(काष्ठा zd_usb *usb, अक्षर *buffer, माप_प्रकार size)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(usb->पूर्णांकf);
	वापस scnprपूर्णांक_id(udev, buffer, size);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम prपूर्णांक_id(काष्ठा usb_device *udev)
अणु
	अक्षर buffer[40];

	scnprपूर्णांक_id(udev, buffer, माप(buffer));
	buffer[माप(buffer)-1] = 0;
	dev_dbg_f(&udev->dev, "%s\n", buffer);
पूर्ण
#अन्यथा
#घोषणा prपूर्णांक_id(udev) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक eject_installer(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc = पूर्णांकf->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	अचिन्हित अक्षर *cmd;
	u8 bulk_out_ep;
	पूर्णांक r;

	अगर (अगरace_desc->desc.bNumEndpoपूर्णांकs < 2)
		वापस -ENODEV;

	/* Find bulk out endpoपूर्णांक */
	क्रम (r = 1; r >= 0; r--) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[r].desc;
		अगर (usb_endpoपूर्णांक_dir_out(endpoपूर्णांक) &&
		    usb_endpoपूर्णांक_xfer_bulk(endpoपूर्णांक)) अणु
			bulk_out_ep = endpoपूर्णांक->bEndpoपूर्णांकAddress;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (r == -1) अणु
		dev_err(&udev->dev,
			"zd1211rw: Could not find bulk out endpoint\n");
		वापस -ENODEV;
	पूर्ण

	cmd = kzalloc(31, GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENODEV;

	/* USB bulk command block */
	cmd[0] = 0x55;	/* bulk command signature */
	cmd[1] = 0x53;	/* bulk command signature */
	cmd[2] = 0x42;	/* bulk command signature */
	cmd[3] = 0x43;	/* bulk command signature */
	cmd[14] = 6;	/* command length */

	cmd[15] = 0x1b;	/* SCSI command: START STOP UNIT */
	cmd[19] = 0x2;	/* eject disc */

	dev_info(&udev->dev, "Ejecting virtual installer media...\n");
	r = usb_bulk_msg(udev, usb_sndbulkpipe(udev, bulk_out_ep),
		cmd, 31, शून्य, 2000);
	kमुक्त(cmd);
	अगर (r)
		वापस r;

	/* At this poपूर्णांक, the device disconnects and reconnects with the real
	 * ID numbers. */

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	वापस 0;
पूर्ण

पूर्णांक zd_usb_init_hw(काष्ठा zd_usb *usb)
अणु
	पूर्णांक r;
	काष्ठा zd_mac *mac = zd_usb_to_mac(usb);

	dev_dbg_f(zd_usb_dev(usb), "\n");

	r = upload_firmware(usb);
	अगर (r) अणु
		dev_err(zd_usb_dev(usb),
		       "couldn't load firmware. Error number %d\n", r);
		वापस r;
	पूर्ण

	r = usb_reset_configuration(zd_usb_to_usbdev(usb));
	अगर (r) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"couldn't reset configuration. Error number %d\n", r);
		वापस r;
	पूर्ण

	r = zd_mac_init_hw(mac->hw);
	अगर (r) अणु
		dev_dbg_f(zd_usb_dev(usb),
		         "couldn't initialize mac. Error number %d\n", r);
		वापस r;
	पूर्ण

	usb->initialized = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक r;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा zd_usb *usb;
	काष्ठा ieee80211_hw *hw = शून्य;

	prपूर्णांक_id(udev);

	अगर (id->driver_info & DEVICE_INSTALLER)
		वापस eject_installer(पूर्णांकf);

	चयन (udev->speed) अणु
	हाल USB_SPEED_LOW:
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_HIGH:
		अवरोध;
	शेष:
		dev_dbg_f(&पूर्णांकf->dev, "Unknown USB speed\n");
		r = -ENODEV;
		जाओ error;
	पूर्ण

	r = usb_reset_device(udev);
	अगर (r) अणु
		dev_err(&पूर्णांकf->dev,
			"couldn't reset usb device. Error number %d\n", r);
		जाओ error;
	पूर्ण

	hw = zd_mac_alloc_hw(पूर्णांकf);
	अगर (hw == शून्य) अणु
		r = -ENOMEM;
		जाओ error;
	पूर्ण

	usb = &zd_hw_mac(hw)->chip.usb;
	usb->is_zd1211b = (id->driver_info == DEVICE_ZD1211B) != 0;

	r = zd_mac_preinit_hw(hw);
	अगर (r) अणु
		dev_dbg_f(&पूर्णांकf->dev,
		         "couldn't initialize mac. Error number %d\n", r);
		जाओ error;
	पूर्ण

	r = ieee80211_रेजिस्टर_hw(hw);
	अगर (r) अणु
		dev_dbg_f(&पूर्णांकf->dev,
			 "couldn't register device. Error number %d\n", r);
		जाओ error;
	पूर्ण

	dev_dbg_f(&पूर्णांकf->dev, "successful\n");
	dev_info(&पूर्णांकf->dev, "%s\n", wiphy_name(hw->wiphy));
	वापस 0;
error:
	usb_reset_device(पूर्णांकerface_to_usbdev(पूर्णांकf));
	अगर (hw) अणु
		zd_mac_clear(zd_hw_mac(hw));
		ieee80211_मुक्त_hw(hw);
	पूर्ण
	वापस r;
पूर्ण

अटल व्योम disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *hw = zd_पूर्णांकf_to_hw(पूर्णांकf);
	काष्ठा zd_mac *mac;
	काष्ठा zd_usb *usb;

	/* Either something really bad happened, or we're just dealing with
	 * a DEVICE_INSTALLER. */
	अगर (hw == शून्य)
		वापस;

	mac = zd_hw_mac(hw);
	usb = &mac->chip.usb;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	ieee80211_unरेजिस्टर_hw(hw);

	/* Just in हाल something has gone wrong! */
	zd_usb_disable_tx(usb);
	zd_usb_disable_rx(usb);
	zd_usb_disable_पूर्णांक(usb);

	/* If the disconnect has been caused by a removal of the
	 * driver module, the reset allows reloading of the driver. If the
	 * reset will not be executed here, the upload of the firmware in the
	 * probe function caused by the reloading of the driver will fail.
	 */
	usb_reset_device(पूर्णांकerface_to_usbdev(पूर्णांकf));

	zd_mac_clear(mac);
	ieee80211_मुक्त_hw(hw);
	dev_dbg(&पूर्णांकf->dev, "disconnected\n");
पूर्ण

अटल व्योम zd_usb_resume(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_mac *mac = zd_usb_to_mac(usb);
	पूर्णांक r;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	r = zd_op_start(zd_usb_to_hw(usb));
	अगर (r < 0) अणु
		dev_warn(zd_usb_dev(usb), "Device resume failed "
			 "with error code %d. Retrying...\n", r);
		अगर (usb->was_running)
			set_bit(ZD_DEVICE_RUNNING, &mac->flags);
		usb_queue_reset_device(usb->पूर्णांकf);
		वापस;
	पूर्ण

	अगर (mac->type != NL80211_IFTYPE_UNSPECIFIED) अणु
		r = zd_restore_settings(mac);
		अगर (r < 0) अणु
			dev_dbg(zd_usb_dev(usb),
				"failed to restore settings, %d\n", r);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम zd_usb_stop(काष्ठा zd_usb *usb)
अणु
	dev_dbg_f(zd_usb_dev(usb), "\n");

	zd_op_stop(zd_usb_to_hw(usb));

	zd_usb_disable_tx(usb);
	zd_usb_disable_rx(usb);
	zd_usb_disable_पूर्णांक(usb);

	usb->initialized = 0;
पूर्ण

अटल पूर्णांक pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *hw = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा zd_mac *mac;
	काष्ठा zd_usb *usb;

	अगर (!hw || पूर्णांकf->condition != USB_INTERFACE_BOUND)
		वापस 0;

	mac = zd_hw_mac(hw);
	usb = &mac->chip.usb;

	usb->was_running = test_bit(ZD_DEVICE_RUNNING, &mac->flags);

	zd_usb_stop(usb);

	mutex_lock(&mac->chip.mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *hw = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा zd_mac *mac;
	काष्ठा zd_usb *usb;

	अगर (!hw || पूर्णांकf->condition != USB_INTERFACE_BOUND)
		वापस 0;

	mac = zd_hw_mac(hw);
	usb = &mac->chip.usb;

	mutex_unlock(&mac->chip.mutex);

	अगर (usb->was_running)
		zd_usb_resume(usb);
	वापस 0;
पूर्ण

अटल काष्ठा usb_driver driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= usb_ids,
	.probe		= probe,
	.disconnect	= disconnect,
	.pre_reset	= pre_reset,
	.post_reset	= post_reset,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

काष्ठा workqueue_काष्ठा *zd_workqueue;

अटल पूर्णांक __init usb_init(व्योम)
अणु
	पूर्णांक r;

	pr_debug("%s usb_init()\n", driver.name);

	zd_workqueue = create_singlethपढ़ो_workqueue(driver.name);
	अगर (zd_workqueue == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s couldn't create workqueue\n", driver.name);
		वापस -ENOMEM;
	पूर्ण

	r = usb_रेजिस्टर(&driver);
	अगर (r) अणु
		destroy_workqueue(zd_workqueue);
		prपूर्णांकk(KERN_ERR "%s usb_register() failed. Error number %d\n",
		       driver.name, r);
		वापस r;
	पूर्ण

	pr_debug("%s initialized\n", driver.name);
	वापस 0;
पूर्ण

अटल व्योम __निकास usb_निकास(व्योम)
अणु
	pr_debug("%s usb_exit()\n", driver.name);
	usb_deरेजिस्टर(&driver);
	destroy_workqueue(zd_workqueue);
पूर्ण

module_init(usb_init);
module_निकास(usb_निकास);

अटल पूर्णांक zd_ep_regs_out_msg(काष्ठा usb_device *udev, व्योम *data, पूर्णांक len,
			      पूर्णांक *actual_length, पूर्णांक समयout)
अणु
	/* In USB 2.0 mode EP_REGS_OUT endpoपूर्णांक is पूर्णांकerrupt type. However in
	 * USB 1.1 mode endpoपूर्णांक is bulk. Select correct type URB by endpoपूर्णांक
	 * descriptor.
	 */
	काष्ठा usb_host_endpoपूर्णांक *ep;
	अचिन्हित पूर्णांक pipe;

	pipe = usb_sndपूर्णांकpipe(udev, EP_REGS_OUT);
	ep = usb_pipe_endpoपूर्णांक(udev, pipe);
	अगर (!ep)
		वापस -EINVAL;

	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc)) अणु
		वापस usb_पूर्णांकerrupt_msg(udev, pipe, data, len,
					 actual_length, समयout);
	पूर्ण अन्यथा अणु
		pipe = usb_sndbulkpipe(udev, EP_REGS_OUT);
		वापस usb_bulk_msg(udev, pipe, data, len, actual_length,
				    समयout);
	पूर्ण
पूर्ण

अटल व्योम prepare_पढ़ो_regs_पूर्णांक(काष्ठा zd_usb *usb,
				  काष्ठा usb_req_पढ़ो_regs *req,
				  अचिन्हित पूर्णांक count)
अणु
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;

	spin_lock_irq(&पूर्णांकr->lock);
	atomic_set(&पूर्णांकr->पढ़ो_regs_enabled, 1);
	पूर्णांकr->पढ़ो_regs.req = req;
	पूर्णांकr->पढ़ो_regs.req_count = count;
	reinit_completion(&पूर्णांकr->पढ़ो_regs.completion);
	spin_unlock_irq(&पूर्णांकr->lock);
पूर्ण

अटल व्योम disable_पढ़ो_regs_पूर्णांक(काष्ठा zd_usb *usb)
अणु
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;

	spin_lock_irq(&पूर्णांकr->lock);
	atomic_set(&पूर्णांकr->पढ़ो_regs_enabled, 0);
	spin_unlock_irq(&पूर्णांकr->lock);
पूर्ण

अटल bool check_पढ़ो_regs(काष्ठा zd_usb *usb, काष्ठा usb_req_पढ़ो_regs *req,
			    अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i;
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;
	काष्ठा पढ़ो_regs_पूर्णांक *rr = &पूर्णांकr->पढ़ो_regs;
	काष्ठा usb_पूर्णांक_regs *regs = (काष्ठा usb_पूर्णांक_regs *)rr->buffer;

	/* The created block size seems to be larger than expected.
	 * However results appear to be correct.
	 */
	अगर (rr->length < काष्ठा_size(regs, regs, count)) अणु
		dev_dbg_f(zd_usb_dev(usb),
			 "error: actual length %d less than expected %zu\n",
			 rr->length, काष्ठा_size(regs, regs, count));
		वापस false;
	पूर्ण

	अगर (rr->length > माप(rr->buffer)) अणु
		dev_dbg_f(zd_usb_dev(usb),
			 "error: actual length %d exceeds buffer size %zu\n",
			 rr->length, माप(rr->buffer));
		वापस false;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा reg_data *rd = &regs->regs[i];
		अगर (rd->addr != req->addr[i]) अणु
			dev_dbg_f(zd_usb_dev(usb),
				 "rd[%d] addr %#06hx expected %#06hx\n", i,
				 le16_to_cpu(rd->addr),
				 le16_to_cpu(req->addr[i]));
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक get_results(काष्ठा zd_usb *usb, u16 *values,
		       काष्ठा usb_req_पढ़ो_regs *req, अचिन्हित पूर्णांक count,
		       bool *retry)
अणु
	पूर्णांक r;
	पूर्णांक i;
	काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr = &usb->पूर्णांकr;
	काष्ठा पढ़ो_regs_पूर्णांक *rr = &पूर्णांकr->पढ़ो_regs;
	काष्ठा usb_पूर्णांक_regs *regs = (काष्ठा usb_पूर्णांक_regs *)rr->buffer;

	spin_lock_irq(&पूर्णांकr->lock);

	r = -EIO;

	/* Read failed because firmware bug? */
	*retry = !!पूर्णांकr->पढ़ो_regs_पूर्णांक_overridden;
	अगर (*retry)
		जाओ error_unlock;

	अगर (!check_पढ़ो_regs(usb, req, count)) अणु
		dev_dbg_f(zd_usb_dev(usb), "error: invalid read regs\n");
		जाओ error_unlock;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा reg_data *rd = &regs->regs[i];
		values[i] = le16_to_cpu(rd->value);
	पूर्ण

	r = 0;
error_unlock:
	spin_unlock_irq(&पूर्णांकr->lock);
	वापस r;
पूर्ण

पूर्णांक zd_usb_ioपढ़ो16v(काष्ठा zd_usb *usb, u16 *values,
	             स्थिर zd_addr_t *addresses, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r, i, req_len, actual_req_len, try_count = 0;
	काष्ठा usb_device *udev;
	काष्ठा usb_req_पढ़ो_regs *req = शून्य;
	अचिन्हित दीर्घ समयout;
	bool retry = false;

	अगर (count < 1) अणु
		dev_dbg_f(zd_usb_dev(usb), "error: count is zero\n");
		वापस -EINVAL;
	पूर्ण
	अगर (count > USB_MAX_IOREAD16_COUNT) अणु
		dev_dbg_f(zd_usb_dev(usb),
			 "error: count %u exceeds possible max %u\n",
			 count, USB_MAX_IOREAD16_COUNT);
		वापस -EINVAL;
	पूर्ण
	अगर (!usb_पूर्णांक_enabled(usb)) अणु
		dev_dbg_f(zd_usb_dev(usb),
			  "error: usb interrupt not enabled\n");
		वापस -EWOULDBLOCK;
	पूर्ण

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));
	BUILD_BUG_ON(माप(काष्ठा usb_req_पढ़ो_regs) + USB_MAX_IOREAD16_COUNT *
		     माप(__le16) > माप(usb->req_buf));
	BUG_ON(माप(काष्ठा usb_req_पढ़ो_regs) + count * माप(__le16) >
	       माप(usb->req_buf));

	req_len = माप(काष्ठा usb_req_पढ़ो_regs) + count * माप(__le16);
	req = (व्योम *)usb->req_buf;

	req->id = cpu_to_le16(USB_REQ_READ_REGS);
	क्रम (i = 0; i < count; i++)
		req->addr[i] = cpu_to_le16((u16)addresses[i]);

retry_पढ़ो:
	try_count++;
	udev = zd_usb_to_usbdev(usb);
	prepare_पढ़ो_regs_पूर्णांक(usb, req, count);
	r = zd_ep_regs_out_msg(udev, req, req_len, &actual_req_len, 50 /*ms*/);
	अगर (r) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"error in zd_ep_regs_out_msg(). Error number %d\n", r);
		जाओ error;
	पूर्ण
	अगर (req_len != actual_req_len) अणु
		dev_dbg_f(zd_usb_dev(usb), "error in zd_ep_regs_out_msg()\n"
			" req_len %d != actual_req_len %d\n",
			req_len, actual_req_len);
		r = -EIO;
		जाओ error;
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&usb->पूर्णांकr.पढ़ो_regs.completion,
					      msecs_to_jअगरfies(50));
	अगर (!समयout) अणु
		disable_पढ़ो_regs_पूर्णांक(usb);
		dev_dbg_f(zd_usb_dev(usb), "read timed out\n");
		r = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	r = get_results(usb, values, req, count, &retry);
	अगर (retry && try_count < 20) अणु
		dev_dbg_f(zd_usb_dev(usb), "read retry, tries so far: %d\n",
				try_count);
		जाओ retry_पढ़ो;
	पूर्ण
error:
	वापस r;
पूर्ण

अटल व्योम ioग_लिखो16v_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा zd_usb *usb = urb->context;

	अगर (urb->status && !usb->cmd_error)
		usb->cmd_error = urb->status;

	अगर (!usb->cmd_error &&
			urb->actual_length != urb->transfer_buffer_length)
		usb->cmd_error = -EIO;
पूर्ण

अटल पूर्णांक zd_submit_रुकोing_urb(काष्ठा zd_usb *usb, bool last)
अणु
	पूर्णांक r = 0;
	काष्ठा urb *urb = usb->urb_async_रुकोing;

	अगर (!urb)
		वापस 0;

	usb->urb_async_रुकोing = शून्य;

	अगर (!last)
		urb->transfer_flags |= URB_NO_INTERRUPT;

	usb_anchor_urb(urb, &usb->submitted_cmds);
	r = usb_submit_urb(urb, GFP_KERNEL);
	अगर (r) अणु
		usb_unanchor_urb(urb);
		dev_dbg_f(zd_usb_dev(usb),
			"error in usb_submit_urb(). Error number %d\n", r);
		जाओ error;
	पूर्ण

	/* fall-through with r == 0 */
error:
	usb_मुक्त_urb(urb);
	वापस r;
पूर्ण

व्योम zd_usb_ioग_लिखो16v_async_start(काष्ठा zd_usb *usb)
अणु
	ZD_ASSERT(usb_anchor_empty(&usb->submitted_cmds));
	ZD_ASSERT(usb->urb_async_रुकोing == शून्य);
	ZD_ASSERT(!usb->in_async);

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));

	usb->in_async = 1;
	usb->cmd_error = 0;
	usb->urb_async_रुकोing = शून्य;
पूर्ण

पूर्णांक zd_usb_ioग_लिखो16v_async_end(काष्ठा zd_usb *usb, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक r;

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));
	ZD_ASSERT(usb->in_async);

	/* Submit last ioग_लिखो16v URB */
	r = zd_submit_रुकोing_urb(usb, true);
	अगर (r) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"error in zd_submit_waiting_usb(). "
			"Error number %d\n", r);

		usb_समाप्त_anchored_urbs(&usb->submitted_cmds);
		जाओ error;
	पूर्ण

	अगर (समयout)
		समयout = usb_रुको_anchor_empty_समयout(&usb->submitted_cmds,
							समयout);
	अगर (!समयout) अणु
		usb_समाप्त_anchored_urbs(&usb->submitted_cmds);
		अगर (usb->cmd_error == -ENOENT) अणु
			dev_dbg_f(zd_usb_dev(usb), "timed out");
			r = -ETIMEDOUT;
			जाओ error;
		पूर्ण
	पूर्ण

	r = usb->cmd_error;
error:
	usb->in_async = 0;
	वापस r;
पूर्ण

पूर्णांक zd_usb_ioग_लिखो16v_async(काष्ठा zd_usb *usb, स्थिर काष्ठा zd_ioreq16 *ioreqs,
			    अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r;
	काष्ठा usb_device *udev;
	काष्ठा usb_req_ग_लिखो_regs *req = शून्य;
	पूर्णांक i, req_len;
	काष्ठा urb *urb;
	काष्ठा usb_host_endpoपूर्णांक *ep;

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));
	ZD_ASSERT(usb->in_async);

	अगर (count == 0)
		वापस 0;
	अगर (count > USB_MAX_IOWRITE16_COUNT) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"error: count %u exceeds possible max %u\n",
			count, USB_MAX_IOWRITE16_COUNT);
		वापस -EINVAL;
	पूर्ण

	udev = zd_usb_to_usbdev(usb);

	ep = usb_pipe_endpoपूर्णांक(udev, usb_sndपूर्णांकpipe(udev, EP_REGS_OUT));
	अगर (!ep)
		वापस -ENOENT;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;

	req_len = काष्ठा_size(req, reg_ग_लिखोs, count);
	req = kदो_स्मृति(req_len, GFP_KERNEL);
	अगर (!req) अणु
		r = -ENOMEM;
		जाओ error;
	पूर्ण

	req->id = cpu_to_le16(USB_REQ_WRITE_REGS);
	क्रम (i = 0; i < count; i++) अणु
		काष्ठा reg_data *rw  = &req->reg_ग_लिखोs[i];
		rw->addr = cpu_to_le16((u16)ioreqs[i].addr);
		rw->value = cpu_to_le16(ioreqs[i].value);
	पूर्ण

	/* In USB 2.0 mode endpoपूर्णांक is पूर्णांकerrupt type. However in USB 1.1 mode
	 * endpoपूर्णांक is bulk. Select correct type URB by endpoपूर्णांक descriptor.
	 */
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc))
		usb_fill_पूर्णांक_urb(urb, udev, usb_sndपूर्णांकpipe(udev, EP_REGS_OUT),
				 req, req_len, ioग_लिखो16v_urb_complete, usb,
				 ep->desc.bInterval);
	अन्यथा
		usb_fill_bulk_urb(urb, udev, usb_sndbulkpipe(udev, EP_REGS_OUT),
				  req, req_len, ioग_लिखो16v_urb_complete, usb);

	urb->transfer_flags |= URB_FREE_BUFFER;

	/* Submit previous URB */
	r = zd_submit_रुकोing_urb(usb, false);
	अगर (r) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"error in zd_submit_waiting_usb(). "
			"Error number %d\n", r);
		जाओ error;
	पूर्ण

	/* Delay submit so that URB_NO_INTERRUPT flag can be set क्रम all URBs
	 * of currect batch except क्रम very last.
	 */
	usb->urb_async_रुकोing = urb;
	वापस 0;
error:
	usb_मुक्त_urb(urb);
	वापस r;
पूर्ण

पूर्णांक zd_usb_ioग_लिखो16v(काष्ठा zd_usb *usb, स्थिर काष्ठा zd_ioreq16 *ioreqs,
			अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r;

	zd_usb_ioग_लिखो16v_async_start(usb);
	r = zd_usb_ioग_लिखो16v_async(usb, ioreqs, count);
	अगर (r) अणु
		zd_usb_ioग_लिखो16v_async_end(usb, 0);
		वापस r;
	पूर्ण
	वापस zd_usb_ioग_लिखो16v_async_end(usb, 50 /* ms */);
पूर्ण

पूर्णांक zd_usb_rख_डालो(काष्ठा zd_usb *usb, u32 value, u8 bits)
अणु
	पूर्णांक r;
	काष्ठा usb_device *udev;
	काष्ठा usb_req_rख_डालो *req = शून्य;
	पूर्णांक i, req_len, actual_req_len;
	u16 bit_value_ढाँचा;

	अगर (bits < USB_MIN_RFWRITE_BIT_COUNT) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"error: bits %d are smaller than"
			" USB_MIN_RFWRITE_BIT_COUNT %d\n",
			bits, USB_MIN_RFWRITE_BIT_COUNT);
		वापस -EINVAL;
	पूर्ण
	अगर (bits > USB_MAX_RFWRITE_BIT_COUNT) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"error: bits %d exceed USB_MAX_RFWRITE_BIT_COUNT %d\n",
			bits, USB_MAX_RFWRITE_BIT_COUNT);
		वापस -EINVAL;
	पूर्ण
#अगर_घोषित DEBUG
	अगर (value & (~0UL << bits)) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"error: value %#09x has bits >= %d set\n",
			value, bits);
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर /* DEBUG */

	dev_dbg_f(zd_usb_dev(usb), "value %#09x bits %d\n", value, bits);

	r = zd_usb_ioपढ़ो16(usb, &bit_value_ढाँचा, ZD_CR203);
	अगर (r) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"error %d: Couldn't read ZD_CR203\n", r);
		वापस r;
	पूर्ण
	bit_value_ढाँचा &= ~(RF_IF_LE|RF_CLK|RF_DATA);

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));
	BUILD_BUG_ON(माप(काष्ठा usb_req_rख_डालो) +
		     USB_MAX_RFWRITE_BIT_COUNT * माप(__le16) >
		     माप(usb->req_buf));
	BUG_ON(माप(काष्ठा usb_req_rख_डालो) + bits * माप(__le16) >
	       माप(usb->req_buf));

	req_len = माप(काष्ठा usb_req_rख_डालो) + bits * माप(__le16);
	req = (व्योम *)usb->req_buf;

	req->id = cpu_to_le16(USB_REQ_WRITE_RF);
	/* 1: 3683a, but not used in ZYDAS driver */
	req->value = cpu_to_le16(2);
	req->bits = cpu_to_le16(bits);

	क्रम (i = 0; i < bits; i++) अणु
		u16 bv = bit_value_ढाँचा;
		अगर (value & (1 << (bits-1-i)))
			bv |= RF_DATA;
		req->bit_values[i] = cpu_to_le16(bv);
	पूर्ण

	udev = zd_usb_to_usbdev(usb);
	r = zd_ep_regs_out_msg(udev, req, req_len, &actual_req_len, 50 /*ms*/);
	अगर (r) अणु
		dev_dbg_f(zd_usb_dev(usb),
			"error in zd_ep_regs_out_msg(). Error number %d\n", r);
		जाओ out;
	पूर्ण
	अगर (req_len != actual_req_len) अणु
		dev_dbg_f(zd_usb_dev(usb), "error in zd_ep_regs_out_msg()"
			" req_len %d != actual_req_len %d\n",
			req_len, actual_req_len);
		r = -EIO;
		जाओ out;
	पूर्ण

	/* FALL-THROUGH with r == 0 */
out:
	वापस r;
पूर्ण
