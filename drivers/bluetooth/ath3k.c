<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2008-2009 Atheros Communications Inc.
 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/usb.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/bluetooth/bluetooth.h>

#घोषणा VERSION "1.0"
#घोषणा ATH3K_FIRMWARE	"ath3k-1.fw"

#घोषणा ATH3K_DNLOAD				0x01
#घोषणा ATH3K_GETSTATE				0x05
#घोषणा ATH3K_SET_NORMAL_MODE			0x07
#घोषणा ATH3K_GETVERSION			0x09
#घोषणा USB_REG_SWITCH_VID_PID			0x0a

#घोषणा ATH3K_MODE_MASK				0x3F
#घोषणा ATH3K_NORMAL_MODE			0x0E

#घोषणा ATH3K_PATCH_UPDATE			0x80
#घोषणा ATH3K_SYSCFG_UPDATE			0x40

#घोषणा ATH3K_XTAL_FREQ_26M			0x00
#घोषणा ATH3K_XTAL_FREQ_40M			0x01
#घोषणा ATH3K_XTAL_FREQ_19P2			0x02
#घोषणा ATH3K_NAME_LEN				0xFF

काष्ठा ath3k_version अणु
	__le32	rom_version;
	__le32	build_version;
	__le32	ram_version;
	__u8	ref_घड़ी;
	__u8	reserved[7];
पूर्ण __packed;

अटल स्थिर काष्ठा usb_device_id ath3k_table[] = अणु
	/* Atheros AR3011 */
	अणु USB_DEVICE(0x0CF3, 0x3000) पूर्ण,

	/* Atheros AR3011 with sflash firmware*/
	अणु USB_DEVICE(0x0489, 0xE027) पूर्ण,
	अणु USB_DEVICE(0x0489, 0xE03D) पूर्ण,
	अणु USB_DEVICE(0x04F2, 0xAFF1) पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0215) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x3002) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0xE019) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3304) पूर्ण,

	/* Atheros AR9285 Malbec with sflash firmware */
	अणु USB_DEVICE(0x03F0, 0x311D) पूर्ण,

	/* Atheros AR3012 with sflash firmware*/
	अणु USB_DEVICE(0x0489, 0xe04d) पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe04e) पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe057) पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe056) पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe05f) पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe076) पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe078) पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe095) पूर्ण,
	अणु USB_DEVICE(0x04c5, 0x1330) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x3004) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x3005) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x3006) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x3007) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x3008) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x300b) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x300d) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x300f) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x3010) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x3014) पूर्ण,
	अणु USB_DEVICE(0x04CA, 0x3018) पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0219) पूर्ण,
	अणु USB_DEVICE(0x0930, 0x021c) पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0220) पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0227) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x17d0) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x0036) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x3004) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x3008) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x311D) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x311E) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x311F) पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x3121) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x817a) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x817b) पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe003) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0xE004) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0xE005) पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0xE006) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3362) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3375) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3393) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3395) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3402) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3408) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3423) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3432) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3472) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3474) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3487) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3490) पूर्ण,

	/* Atheros AR5BBU12 with sflash firmware */
	अणु USB_DEVICE(0x0489, 0xE02C) पूर्ण,

	/* Atheros AR5BBU22 with sflash firmware */
	अणु USB_DEVICE(0x0489, 0xE036) पूर्ण,
	अणु USB_DEVICE(0x0489, 0xE03C) पूर्ण,

	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, ath3k_table);

#घोषणा BTUSB_ATH3012		0x80
/* This table is to load patch and sysconfig files
 * क्रम AR3012
 */
अटल स्थिर काष्ठा usb_device_id ath3k_blist_tbl[] = अणु

	/* Atheros AR3012 with sflash firmware*/
	अणु USB_DEVICE(0x0489, 0xe04e), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe04d), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe056), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe057), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe05f), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe076), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe078), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe095), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04c5, 0x1330), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3004), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3005), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3006), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3007), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3008), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x300b), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x300d), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x300f), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3010), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3014), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3018), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0219), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0930, 0x021c), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0220), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0227), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x17d0), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x0036), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x3004), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x3008), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x311D), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x311E), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x311F), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x3121), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x817a), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0CF3, 0x817b), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe004), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe005), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe006), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe003), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3362), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3375), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3393), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3395), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3402), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3408), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3423), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3432), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3472), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3474), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3487), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3490), .driver_info = BTUSB_ATH3012 पूर्ण,

	/* Atheros AR5BBU22 with sflash firmware */
	अणु USB_DEVICE(0x0489, 0xE036), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xE03C), .driver_info = BTUSB_ATH3012 पूर्ण,

	अणु पूर्ण	/* Terminating entry */
पूर्ण;

अटल अंतरभूत व्योम ath3k_log_failed_loading(पूर्णांक err, पूर्णांक len, पूर्णांक size,
					    पूर्णांक count)
अणु
	BT_ERR("Firmware loading err = %d, len = %d, size = %d, count = %d",
	       err, len, size, count);
पूर्ण

#घोषणा USB_REQ_DFU_DNLOAD	1
#घोषणा BULK_SIZE		4096
#घोषणा FW_HDR_SIZE		20
#घोषणा TIMEGAP_USEC_MIN	50
#घोषणा TIMEGAP_USEC_MAX	100

अटल पूर्णांक ath3k_load_firmware(काष्ठा usb_device *udev,
				स्थिर काष्ठा firmware *firmware)
अणु
	u8 *send_buf;
	पूर्णांक len = 0;
	पूर्णांक err, pipe, size, sent = 0;
	पूर्णांक count = firmware->size;

	BT_DBG("udev %p", udev);

	send_buf = kदो_स्मृति(BULK_SIZE, GFP_KERNEL);
	अगर (!send_buf) अणु
		BT_ERR("Can't allocate memory chunk for firmware");
		वापस -ENOMEM;
	पूर्ण

	err = usb_control_msg_send(udev, 0, USB_REQ_DFU_DNLOAD, USB_TYPE_VENDOR,
				   0, 0, firmware->data, FW_HDR_SIZE,
				   USB_CTRL_SET_TIMEOUT, GFP_KERNEL);
	अगर (err) अणु
		BT_ERR("Can't change to loading configuration err");
		जाओ error;
	पूर्ण
	sent += FW_HDR_SIZE;
	count -= FW_HDR_SIZE;

	pipe = usb_sndbulkpipe(udev, 0x02);

	जबतक (count) अणु
		/* workaround the compatibility issue with xHCI controller*/
		usleep_range(TIMEGAP_USEC_MIN, TIMEGAP_USEC_MAX);

		size = min_t(uपूर्णांक, count, BULK_SIZE);
		स_नकल(send_buf, firmware->data + sent, size);

		err = usb_bulk_msg(udev, pipe, send_buf, size,
					&len, 3000);

		अगर (err || (len != size)) अणु
			ath3k_log_failed_loading(err, len, size, count);
			जाओ error;
		पूर्ण

		sent  += size;
		count -= size;
	पूर्ण

error:
	kमुक्त(send_buf);
	वापस err;
पूर्ण

अटल पूर्णांक ath3k_get_state(काष्ठा usb_device *udev, अचिन्हित अक्षर *state)
अणु
	वापस usb_control_msg_recv(udev, 0, ATH3K_GETSTATE,
				    USB_TYPE_VENDOR | USB_सूची_IN, 0, 0,
				    state, 1, USB_CTRL_SET_TIMEOUT,
				    GFP_KERNEL);
पूर्ण

अटल पूर्णांक ath3k_get_version(काष्ठा usb_device *udev,
			काष्ठा ath3k_version *version)
अणु
	वापस usb_control_msg_recv(udev, 0, ATH3K_GETVERSION,
				    USB_TYPE_VENDOR | USB_सूची_IN, 0, 0,
				    version, माप(*version), USB_CTRL_SET_TIMEOUT,
				    GFP_KERNEL);
पूर्ण

अटल पूर्णांक ath3k_load_fwfile(काष्ठा usb_device *udev,
		स्थिर काष्ठा firmware *firmware)
अणु
	u8 *send_buf;
	पूर्णांक len = 0;
	पूर्णांक err, pipe, size, count, sent = 0;
	पूर्णांक ret;

	count = firmware->size;

	send_buf = kदो_स्मृति(BULK_SIZE, GFP_KERNEL);
	अगर (!send_buf) अणु
		BT_ERR("Can't allocate memory chunk for firmware");
		वापस -ENOMEM;
	पूर्ण

	size = min_t(uपूर्णांक, count, FW_HDR_SIZE);

	ret = usb_control_msg_send(udev, 0, ATH3K_DNLOAD, USB_TYPE_VENDOR, 0, 0,
				   firmware->data, size, USB_CTRL_SET_TIMEOUT,
				   GFP_KERNEL);
	अगर (ret) अणु
		BT_ERR("Can't change to loading configuration err");
		kमुक्त(send_buf);
		वापस ret;
	पूर्ण

	sent += size;
	count -= size;

	pipe = usb_sndbulkpipe(udev, 0x02);

	जबतक (count) अणु
		/* workaround the compatibility issue with xHCI controller*/
		usleep_range(TIMEGAP_USEC_MIN, TIMEGAP_USEC_MAX);

		size = min_t(uपूर्णांक, count, BULK_SIZE);
		स_नकल(send_buf, firmware->data + sent, size);

		err = usb_bulk_msg(udev, pipe, send_buf, size,
					&len, 3000);
		अगर (err || (len != size)) अणु
			ath3k_log_failed_loading(err, len, size, count);
			kमुक्त(send_buf);
			वापस err;
		पूर्ण
		sent  += size;
		count -= size;
	पूर्ण

	kमुक्त(send_buf);
	वापस 0;
पूर्ण

अटल व्योम ath3k_चयन_pid(काष्ठा usb_device *udev)
अणु
	usb_control_msg_send(udev, 0, USB_REG_SWITCH_VID_PID, USB_TYPE_VENDOR,
			     0, 0, शून्य, 0, USB_CTRL_SET_TIMEOUT, GFP_KERNEL);
पूर्ण

अटल पूर्णांक ath3k_set_normal_mode(काष्ठा usb_device *udev)
अणु
	अचिन्हित अक्षर fw_state;
	पूर्णांक ret;

	ret = ath3k_get_state(udev, &fw_state);
	अगर (ret) अणु
		BT_ERR("Can't get state to change to normal mode err");
		वापस ret;
	पूर्ण

	अगर ((fw_state & ATH3K_MODE_MASK) == ATH3K_NORMAL_MODE) अणु
		BT_DBG("firmware was already in normal mode");
		वापस 0;
	पूर्ण

	वापस usb_control_msg_send(udev, 0, ATH3K_SET_NORMAL_MODE,
				    USB_TYPE_VENDOR, 0, 0, शून्य, 0,
				    USB_CTRL_SET_TIMEOUT, GFP_KERNEL);
पूर्ण

अटल पूर्णांक ath3k_load_patch(काष्ठा usb_device *udev)
अणु
	अचिन्हित अक्षर fw_state;
	अक्षर filename[ATH3K_NAME_LEN];
	स्थिर काष्ठा firmware *firmware;
	काष्ठा ath3k_version fw_version;
	__u32 pt_rom_version, pt_build_version;
	पूर्णांक ret;

	ret = ath3k_get_state(udev, &fw_state);
	अगर (ret) अणु
		BT_ERR("Can't get state to change to load ram patch err");
		वापस ret;
	पूर्ण

	अगर (fw_state & ATH3K_PATCH_UPDATE) अणु
		BT_DBG("Patch was already downloaded");
		वापस 0;
	पूर्ण

	ret = ath3k_get_version(udev, &fw_version);
	अगर (ret) अणु
		BT_ERR("Can't get version to change to load ram patch err");
		वापस ret;
	पूर्ण

	snम_लिखो(filename, ATH3K_NAME_LEN, "ar3k/AthrBT_0x%08x.dfu",
		 le32_to_cpu(fw_version.rom_version));

	ret = request_firmware(&firmware, filename, &udev->dev);
	अगर (ret < 0) अणु
		BT_ERR("Patch file not found %s", filename);
		वापस ret;
	पूर्ण

	pt_rom_version = get_unaligned_le32(firmware->data +
					    firmware->size - 8);
	pt_build_version = get_unaligned_le32(firmware->data +
					      firmware->size - 4);

	अगर (pt_rom_version != le32_to_cpu(fw_version.rom_version) ||
	    pt_build_version <= le32_to_cpu(fw_version.build_version)) अणु
		BT_ERR("Patch file version did not match with firmware");
		release_firmware(firmware);
		वापस -EINVAL;
	पूर्ण

	ret = ath3k_load_fwfile(udev, firmware);
	release_firmware(firmware);

	वापस ret;
पूर्ण

अटल पूर्णांक ath3k_load_syscfg(काष्ठा usb_device *udev)
अणु
	अचिन्हित अक्षर fw_state;
	अक्षर filename[ATH3K_NAME_LEN];
	स्थिर काष्ठा firmware *firmware;
	काष्ठा ath3k_version fw_version;
	पूर्णांक clk_value, ret;

	ret = ath3k_get_state(udev, &fw_state);
	अगर (ret) अणु
		BT_ERR("Can't get state to change to load configuration err");
		वापस -EBUSY;
	पूर्ण

	ret = ath3k_get_version(udev, &fw_version);
	अगर (ret) अणु
		BT_ERR("Can't get version to change to load ram patch err");
		वापस ret;
	पूर्ण

	चयन (fw_version.ref_घड़ी) अणु

	हाल ATH3K_XTAL_FREQ_26M:
		clk_value = 26;
		अवरोध;
	हाल ATH3K_XTAL_FREQ_40M:
		clk_value = 40;
		अवरोध;
	हाल ATH3K_XTAL_FREQ_19P2:
		clk_value = 19;
		अवरोध;
	शेष:
		clk_value = 0;
		अवरोध;
	पूर्ण

	snम_लिखो(filename, ATH3K_NAME_LEN, "ar3k/ramps_0x%08x_%d%s",
		le32_to_cpu(fw_version.rom_version), clk_value, ".dfu");

	ret = request_firmware(&firmware, filename, &udev->dev);
	अगर (ret < 0) अणु
		BT_ERR("Configuration file not found %s", filename);
		वापस ret;
	पूर्ण

	ret = ath3k_load_fwfile(udev, firmware);
	release_firmware(firmware);

	वापस ret;
पूर्ण

अटल पूर्णांक ath3k_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	स्थिर काष्ठा firmware *firmware;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक ret;

	BT_DBG("intf %p id %p", पूर्णांकf, id);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 0)
		वापस -ENODEV;

	/* match device ID in ath3k blacklist table */
	अगर (!id->driver_info) अणु
		स्थिर काष्ठा usb_device_id *match;

		match = usb_match_id(पूर्णांकf, ath3k_blist_tbl);
		अगर (match)
			id = match;
	पूर्ण

	/* load patch and sysconfig files क्रम AR3012 */
	अगर (id->driver_info & BTUSB_ATH3012) अणु
		/* New firmware with patch and sysconfig files alपढ़ोy loaded */
		अगर (le16_to_cpu(udev->descriptor.bcdDevice) > 0x0001)
			वापस -ENODEV;

		ret = ath3k_load_patch(udev);
		अगर (ret < 0) अणु
			BT_ERR("Loading patch file failed");
			वापस ret;
		पूर्ण
		ret = ath3k_load_syscfg(udev);
		अगर (ret < 0) अणु
			BT_ERR("Loading sysconfig file failed");
			वापस ret;
		पूर्ण
		ret = ath3k_set_normal_mode(udev);
		अगर (ret) अणु
			BT_ERR("Set normal mode failed");
			वापस ret;
		पूर्ण
		ath3k_चयन_pid(udev);
		वापस 0;
	पूर्ण

	ret = request_firmware(&firmware, ATH3K_FIRMWARE, &udev->dev);
	अगर (ret < 0) अणु
		अगर (ret == -ENOENT)
			BT_ERR("Firmware file \"%s\" not found",
							ATH3K_FIRMWARE);
		अन्यथा
			BT_ERR("Firmware file \"%s\" request failed (err=%d)",
							ATH3K_FIRMWARE, ret);
		वापस ret;
	पूर्ण

	ret = ath3k_load_firmware(udev, firmware);
	release_firmware(firmware);

	वापस ret;
पूर्ण

अटल व्योम ath3k_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	BT_DBG("%s intf %p", __func__, पूर्णांकf);
पूर्ण

अटल काष्ठा usb_driver ath3k_driver = अणु
	.name		= "ath3k",
	.probe		= ath3k_probe,
	.disconnect	= ath3k_disconnect,
	.id_table	= ath3k_table,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(ath3k_driver);

MODULE_AUTHOR("Atheros Communications");
MODULE_DESCRIPTION("Atheros AR30xx firmware driver");
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(ATH3K_FIRMWARE);
