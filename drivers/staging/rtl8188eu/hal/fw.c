<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2009-2013  Realtek Corporation.
 *
 * Contact Inक्रमmation:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/

#समावेश "fw.h"
#समावेश "drv_types.h"
#समावेश "usb_ops_linux.h"
#समावेश "rtl8188e_spec.h"
#समावेश "rtl8188e_hal.h"

#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>

अटल व्योम _rtl88e_enable_fw_करोwnload(काष्ठा adapter *adapt, bool enable)
अणु
	u8 पंचांगp;

	अगर (enable) अणु
		पंचांगp = usb_पढ़ो8(adapt, REG_MCUFWDL);
		usb_ग_लिखो8(adapt, REG_MCUFWDL, पंचांगp | 0x01);

		पंचांगp = usb_पढ़ो8(adapt, REG_MCUFWDL + 2);
		usb_ग_लिखो8(adapt, REG_MCUFWDL + 2, पंचांगp & 0xf7);
	पूर्ण अन्यथा अणु
		पंचांगp = usb_पढ़ो8(adapt, REG_MCUFWDL);
		usb_ग_लिखो8(adapt, REG_MCUFWDL, पंचांगp & 0xfe);

		usb_ग_लिखो8(adapt, REG_MCUFWDL + 1, 0x00);
	पूर्ण
पूर्ण

अटल व्योम _rtl88e_fw_block_ग_लिखो(काष्ठा adapter *adapt,
				   स्थिर u8 *buffer, u32 size)
अणु
	u32 blk_sz = माप(u32);
	स्थिर u8 *byte_buffer;
	स्थिर u32 *dword_buffer = (u32 *)buffer;
	u32 i, ग_लिखो_address, blk_cnt, reमुख्य;

	blk_cnt = size / blk_sz;
	reमुख्य = size % blk_sz;

	ग_लिखो_address = FW_8192C_START_ADDRESS;

	क्रम (i = 0; i < blk_cnt; i++, ग_लिखो_address += blk_sz)
		usb_ग_लिखो32(adapt, ग_लिखो_address, dword_buffer[i]);

	byte_buffer = buffer + blk_cnt * blk_sz;
	क्रम (i = 0; i < reमुख्य; i++, ग_लिखो_address++)
		usb_ग_लिखो8(adapt, ग_लिखो_address, byte_buffer[i]);
पूर्ण

अटल व्योम _rtl88e_fw_page_ग_लिखो(काष्ठा adapter *adapt,
				  u32 page, स्थिर u8 *buffer, u32 size)
अणु
	u8 value8;
	u8 u8page = (u8)(page & 0x07);

	value8 = (usb_पढ़ो8(adapt, REG_MCUFWDL + 2) & 0xF8) | u8page;

	usb_ग_लिखो8(adapt, (REG_MCUFWDL + 2), value8);
	_rtl88e_fw_block_ग_लिखो(adapt, buffer, size);
पूर्ण

अटल व्योम _rtl88e_ग_लिखो_fw(काष्ठा adapter *adapt, u8 *buffer, u32 size)
अणु
	u8 *buf_ptr = buffer;
	u32 page_no, reमुख्य;
	u32 page, offset;

	page_no = size / FW_8192C_PAGE_SIZE;
	reमुख्य = size % FW_8192C_PAGE_SIZE;

	क्रम (page = 0; page < page_no; page++) अणु
		offset = page * FW_8192C_PAGE_SIZE;
		_rtl88e_fw_page_ग_लिखो(adapt, page, (buf_ptr + offset),
				      FW_8192C_PAGE_SIZE);
	पूर्ण

	अगर (reमुख्य) अणु
		offset = page_no * FW_8192C_PAGE_SIZE;
		page = page_no;
		_rtl88e_fw_page_ग_लिखो(adapt, page, (buf_ptr + offset), reमुख्य);
	पूर्ण
पूर्ण

अटल व्योम rtl88e_firmware_selfreset(काष्ठा adapter *adapt)
अणु
	u8 u1b_पंचांगp;

	u1b_पंचांगp = usb_पढ़ो8(adapt, REG_SYS_FUNC_EN + 1);
	usb_ग_लिखो8(adapt, REG_SYS_FUNC_EN + 1, (u1b_पंचांगp & (~BIT(2))));
	usb_ग_लिखो8(adapt, REG_SYS_FUNC_EN + 1, (u1b_पंचांगp | BIT(2)));
पूर्ण

अटल पूर्णांक _rtl88e_fw_मुक्त_to_go(काष्ठा adapter *adapt)
अणु
	पूर्णांक err = -EIO;
	u32 counter = 0;
	u32 value32;

	करो अणु
		value32 = usb_पढ़ो32(adapt, REG_MCUFWDL);
		अगर (value32 & FWDL_CHKSUM_RPT)
			अवरोध;
	पूर्ण जबतक (counter++ < POLLING_READY_TIMEOUT_COUNT);

	अगर (counter >= POLLING_READY_TIMEOUT_COUNT)
		जाओ निकास;

	value32 = usb_पढ़ो32(adapt, REG_MCUFWDL);
	value32 |= MCUFWDL_RDY;
	value32 &= ~WINTINI_RDY;
	usb_ग_लिखो32(adapt, REG_MCUFWDL, value32);

	rtl88e_firmware_selfreset(adapt);
	counter = 0;

	करो अणु
		value32 = usb_पढ़ो32(adapt, REG_MCUFWDL);
		अगर (value32 & WINTINI_RDY) अणु
			err = 0;
			जाओ निकास;
		पूर्ण

		udelay(FW_8192C_POLLING_DELAY);

	पूर्ण जबतक (counter++ < POLLING_READY_TIMEOUT_COUNT);

निकास:
	वापस err;
पूर्ण

पूर्णांक rtl88eu_करोwnload_fw(काष्ठा adapter *adapt)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapt);
	काष्ठा device *device = dvobj_to_dev(dvobj);
	स्थिर काष्ठा firmware *fw;
	अटल स्थिर अक्षर fw_name[] = "rtlwifi/rtl8188eufw.bin";
	काष्ठा rtl92c_firmware_header *pfwheader = शून्य;
	u8 *करोwnload_data, *fw_data;
	माप_प्रकार करोwnload_size;
	अचिन्हित पूर्णांक trailing_zeros_length;

	अगर (request_firmware(&fw, fw_name, device)) अणु
		dev_err(device, "Firmware %s not available\n", fw_name);
		वापस -ENOENT;
	पूर्ण

	अगर (fw->size > FW_8188E_SIZE) अणु
		dev_err(device, "Firmware size exceed 0x%X. Check it.\n",
			FW_8188E_SIZE);
		release_firmware(fw);
		वापस -1;
	पूर्ण

	trailing_zeros_length = (4 - fw->size % 4) % 4;

	fw_data = kदो_स्मृति(fw->size + trailing_zeros_length, GFP_KERNEL);
	अगर (!fw_data) अणु
		release_firmware(fw);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(fw_data, fw->data, fw->size);
	स_रखो(fw_data + fw->size, 0, trailing_zeros_length);

	pfwheader = (काष्ठा rtl92c_firmware_header *)fw_data;

	अगर (IS_FW_HEADER_EXIST(pfwheader)) अणु
		करोwnload_data = fw_data + 32;
		करोwnload_size = fw->size + trailing_zeros_length - 32;
	पूर्ण अन्यथा अणु
		करोwnload_data = fw_data;
		करोwnload_size = fw->size + trailing_zeros_length;
	पूर्ण

	release_firmware(fw);

	अगर (usb_पढ़ो8(adapt, REG_MCUFWDL) & RAM_DL_SEL) अणु
		usb_ग_लिखो8(adapt, REG_MCUFWDL, 0);
		rtl88e_firmware_selfreset(adapt);
	पूर्ण
	_rtl88e_enable_fw_करोwnload(adapt, true);
	usb_ग_लिखो8(adapt, REG_MCUFWDL,
		   usb_पढ़ो8(adapt, REG_MCUFWDL) | FWDL_CHKSUM_RPT);
	_rtl88e_ग_लिखो_fw(adapt, करोwnload_data, करोwnload_size);
	_rtl88e_enable_fw_करोwnload(adapt, false);

	kमुक्त(fw_data);
	वापस _rtl88e_fw_मुक्त_to_go(adapt);
पूर्ण
