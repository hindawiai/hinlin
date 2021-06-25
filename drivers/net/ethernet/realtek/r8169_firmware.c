<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* r8169_firmware.c: RealTek 8169/8168/8101 ethernet driver.
 *
 * Copyright (c) 2002 ShuChen <shuchen@realtek.com.tw>
 * Copyright (c) 2003 - 2007 Francois Romieu <romieu@fr.zoreil.com>
 * Copyright (c) a lot of people too. Please respect their work.
 *
 * See MAINTAINERS file क्रम support contact inक्रमmation.
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>

#समावेश "r8169_firmware.h"

क्रमागत rtl_fw_opcode अणु
	PHY_READ		= 0x0,
	PHY_DATA_OR		= 0x1,
	PHY_DATA_AND		= 0x2,
	PHY_BJMPN		= 0x3,
	PHY_MDIO_CHG		= 0x4,
	PHY_CLEAR_READCOUNT	= 0x7,
	PHY_WRITE		= 0x8,
	PHY_READCOUNT_EQ_SKIP	= 0x9,
	PHY_COMP_EQ_SKIPN	= 0xa,
	PHY_COMP_NEQ_SKIPN	= 0xb,
	PHY_WRITE_PREVIOUS	= 0xc,
	PHY_SKIPN		= 0xd,
	PHY_DELAY_MS		= 0xe,
पूर्ण;

काष्ठा fw_info अणु
	u32	magic;
	अक्षर	version[RTL_VER_SIZE];
	__le32	fw_start;
	__le32	fw_len;
	u8	chksum;
पूर्ण __packed;

#घोषणा FW_OPCODE_SIZE माप_field(काष्ठा rtl_fw_phy_action, code[0])

अटल bool rtl_fw_क्रमmat_ok(काष्ठा rtl_fw *rtl_fw)
अणु
	स्थिर काष्ठा firmware *fw = rtl_fw->fw;
	काष्ठा fw_info *fw_info = (काष्ठा fw_info *)fw->data;
	काष्ठा rtl_fw_phy_action *pa = &rtl_fw->phy_action;

	अगर (fw->size < FW_OPCODE_SIZE)
		वापस false;

	अगर (!fw_info->magic) अणु
		माप_प्रकार i, size, start;
		u8 checksum = 0;

		अगर (fw->size < माप(*fw_info))
			वापस false;

		क्रम (i = 0; i < fw->size; i++)
			checksum += fw->data[i];
		अगर (checksum != 0)
			वापस false;

		start = le32_to_cpu(fw_info->fw_start);
		अगर (start > fw->size)
			वापस false;

		size = le32_to_cpu(fw_info->fw_len);
		अगर (size > (fw->size - start) / FW_OPCODE_SIZE)
			वापस false;

		strscpy(rtl_fw->version, fw_info->version, RTL_VER_SIZE);

		pa->code = (__le32 *)(fw->data + start);
		pa->size = size;
	पूर्ण अन्यथा अणु
		अगर (fw->size % FW_OPCODE_SIZE)
			वापस false;

		strscpy(rtl_fw->version, rtl_fw->fw_name, RTL_VER_SIZE);

		pa->code = (__le32 *)fw->data;
		pa->size = fw->size / FW_OPCODE_SIZE;
	पूर्ण

	वापस true;
पूर्ण

अटल bool rtl_fw_data_ok(काष्ठा rtl_fw *rtl_fw)
अणु
	काष्ठा rtl_fw_phy_action *pa = &rtl_fw->phy_action;
	माप_प्रकार index;

	क्रम (index = 0; index < pa->size; index++) अणु
		u32 action = le32_to_cpu(pa->code[index]);
		u32 val = action & 0x0000ffff;
		u32 regno = (action & 0x0fff0000) >> 16;

		चयन (action >> 28) अणु
		हाल PHY_READ:
		हाल PHY_DATA_OR:
		हाल PHY_DATA_AND:
		हाल PHY_CLEAR_READCOUNT:
		हाल PHY_WRITE:
		हाल PHY_WRITE_PREVIOUS:
		हाल PHY_DELAY_MS:
			अवरोध;

		हाल PHY_MDIO_CHG:
			अगर (val > 1)
				जाओ out;
			अवरोध;

		हाल PHY_BJMPN:
			अगर (regno > index)
				जाओ out;
			अवरोध;
		हाल PHY_READCOUNT_EQ_SKIP:
			अगर (index + 2 >= pa->size)
				जाओ out;
			अवरोध;
		हाल PHY_COMP_EQ_SKIPN:
		हाल PHY_COMP_NEQ_SKIPN:
		हाल PHY_SKIPN:
			अगर (index + 1 + regno >= pa->size)
				जाओ out;
			अवरोध;

		शेष:
			dev_err(rtl_fw->dev, "Invalid action 0x%08x\n", action);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
out:
	dev_err(rtl_fw->dev, "Out of range of firmware\n");
	वापस false;
पूर्ण

व्योम rtl_fw_ग_लिखो_firmware(काष्ठा rtl8169_निजी *tp, काष्ठा rtl_fw *rtl_fw)
अणु
	काष्ठा rtl_fw_phy_action *pa = &rtl_fw->phy_action;
	rtl_fw_ग_लिखो_t fw_ग_लिखो = rtl_fw->phy_ग_लिखो;
	rtl_fw_पढ़ो_t fw_पढ़ो = rtl_fw->phy_पढ़ो;
	पूर्णांक predata = 0, count = 0;
	माप_प्रकार index;

	क्रम (index = 0; index < pa->size; index++) अणु
		u32 action = le32_to_cpu(pa->code[index]);
		u32 data = action & 0x0000ffff;
		u32 regno = (action & 0x0fff0000) >> 16;
		क्रमागत rtl_fw_opcode opcode = action >> 28;

		अगर (!action)
			अवरोध;

		चयन (opcode) अणु
		हाल PHY_READ:
			predata = fw_पढ़ो(tp, regno);
			count++;
			अवरोध;
		हाल PHY_DATA_OR:
			predata |= data;
			अवरोध;
		हाल PHY_DATA_AND:
			predata &= data;
			अवरोध;
		हाल PHY_BJMPN:
			index -= (regno + 1);
			अवरोध;
		हाल PHY_MDIO_CHG:
			अगर (data) अणु
				fw_ग_लिखो = rtl_fw->mac_mcu_ग_लिखो;
				fw_पढ़ो = rtl_fw->mac_mcu_पढ़ो;
			पूर्ण अन्यथा अणु
				fw_ग_लिखो = rtl_fw->phy_ग_लिखो;
				fw_पढ़ो = rtl_fw->phy_पढ़ो;
			पूर्ण

			अवरोध;
		हाल PHY_CLEAR_READCOUNT:
			count = 0;
			अवरोध;
		हाल PHY_WRITE:
			fw_ग_लिखो(tp, regno, data);
			अवरोध;
		हाल PHY_READCOUNT_EQ_SKIP:
			अगर (count == data)
				index++;
			अवरोध;
		हाल PHY_COMP_EQ_SKIPN:
			अगर (predata == data)
				index += regno;
			अवरोध;
		हाल PHY_COMP_NEQ_SKIPN:
			अगर (predata != data)
				index += regno;
			अवरोध;
		हाल PHY_WRITE_PREVIOUS:
			fw_ग_लिखो(tp, regno, predata);
			अवरोध;
		हाल PHY_SKIPN:
			index += regno;
			अवरोध;
		हाल PHY_DELAY_MS:
			msleep(data);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl_fw_release_firmware(काष्ठा rtl_fw *rtl_fw)
अणु
	release_firmware(rtl_fw->fw);
पूर्ण

पूर्णांक rtl_fw_request_firmware(काष्ठा rtl_fw *rtl_fw)
अणु
	पूर्णांक rc;

	rc = request_firmware(&rtl_fw->fw, rtl_fw->fw_name, rtl_fw->dev);
	अगर (rc < 0)
		जाओ out;

	अगर (!rtl_fw_क्रमmat_ok(rtl_fw) || !rtl_fw_data_ok(rtl_fw)) अणु
		release_firmware(rtl_fw->fw);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	वापस 0;
out:
	dev_err(rtl_fw->dev, "Unable to load firmware %s (%d)\n",
		rtl_fw->fw_name, rc);
	वापस rc;
पूर्ण
