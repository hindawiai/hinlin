<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "../core.h"
#समावेश "../efuse.h"
#समावेश "../rtl8192ce/reg.h"
#समावेश "../rtl8192ce/def.h"
#समावेश "fw_common.h"
#समावेश <linux/export.h>

अटल व्योम _rtl92c_enable_fw_करोwnload(काष्ठा ieee80211_hw *hw, bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192CU) अणु
		u32 value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);

		अगर (enable)
			value32 |= MCUFWDL_EN;
		अन्यथा
			value32 &= ~MCUFWDL_EN;
		rtl_ग_लिखो_dword(rtlpriv, REG_MCUFWDL, value32);
	पूर्ण अन्यथा अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192CE) अणु
		u8 पंचांगp;

		अगर (enable) अणु
			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
			rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1,
				       पंचांगp | 0x04);

			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL);
			rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, पंचांगp | 0x01);

			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL + 2);
			rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL + 2, पंचांगp & 0xf7);
		पूर्ण अन्यथा अणु
			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL);
			rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, पंचांगp & 0xfe);

			rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL + 1, 0x00);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92c_ग_लिखो_fw(काष्ठा ieee80211_hw *hw,
			     क्रमागत version_8192c version, u8 *buffer, u32 size)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool is_version_b;
	u8 *bufferptr = (u8 *)buffer;

	rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE, "FW size is %d bytes,\n", size);
	is_version_b = IS_NORMAL_CHIP(version);
	अगर (is_version_b) अणु
		u32 pagक्रमागतs, reमुख्यsize;
		u32 page, offset;

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192CE)
			rtl_fill_dummy(bufferptr, &size);

		pagक्रमागतs = size / FW_8192C_PAGE_SIZE;
		reमुख्यsize = size % FW_8192C_PAGE_SIZE;

		अगर (pagक्रमागतs > 4)
			pr_err("Page numbers should not greater then 4\n");

		क्रम (page = 0; page < pagक्रमागतs; page++) अणु
			offset = page * FW_8192C_PAGE_SIZE;
			rtl_fw_page_ग_लिखो(hw, page, (bufferptr + offset),
					  FW_8192C_PAGE_SIZE);
		पूर्ण

		अगर (reमुख्यsize) अणु
			offset = pagक्रमागतs * FW_8192C_PAGE_SIZE;
			page = pagक्रमागतs;
			rtl_fw_page_ग_लिखो(hw, page, (bufferptr + offset),
					  reमुख्यsize);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_fw_block_ग_लिखो(hw, buffer, size);
	पूर्ण
पूर्ण

अटल पूर्णांक _rtl92c_fw_मुक्त_to_go(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक err = -EIO;
	u32 counter = 0;
	u32 value32;

	करो अणु
		value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);
	पूर्ण जबतक ((counter++ < FW_8192C_POLLING_TIMEOUT_COUNT) &&
		 (!(value32 & FWDL_CHKSUM_RPT)));

	अगर (counter >= FW_8192C_POLLING_TIMEOUT_COUNT) अणु
		pr_err("chksum report fail! REG_MCUFWDL:0x%08x .\n",
		       value32);
		जाओ निकास;
	पूर्ण
	value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);
	value32 |= MCUFWDL_RDY;
	value32 &= ~WINTINI_RDY;
	rtl_ग_लिखो_dword(rtlpriv, REG_MCUFWDL, value32);

	counter = 0;

	करो अणु
		value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);
		अगर (value32 & WINTINI_RDY)
			वापस 0;

		mdelay(FW_8192C_POLLING_DELAY);

	पूर्ण जबतक (counter++ < FW_8192C_POLLING_TIMEOUT_COUNT);

	pr_err("Polling FW ready fail! REG_MCUFWDL:0x%08x.\n",
	       value32);

निकास:
	वापस err;
पूर्ण

पूर्णांक rtl92c_करोwnload_fw(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtlwअगरi_firmware_header *pfwheader;
	u8 *pfwdata;
	u32 fwsize;
	पूर्णांक err;
	क्रमागत version_8192c version = rtlhal->version;

	अगर (!rtlhal->pfirmware)
		वापस 1;

	pfwheader = (काष्ठा rtlwअगरi_firmware_header *)rtlhal->pfirmware;
	pfwdata = (u8 *)rtlhal->pfirmware;
	fwsize = rtlhal->fwsize;
	अगर (IS_FW_HEADER_EXIST(pfwheader)) अणु
		rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
			"Firmware Version(%d), Signature(%#x),Size(%d)\n",
			pfwheader->version, pfwheader->signature,
			(पूर्णांक)माप(काष्ठा rtlwअगरi_firmware_header));

		rtlhal->fw_version = le16_to_cpu(pfwheader->version);
		rtlhal->fw_subversion = pfwheader->subversion;
		pfwdata = pfwdata + माप(काष्ठा rtlwअगरi_firmware_header);
		fwsize = fwsize - माप(काष्ठा rtlwअगरi_firmware_header);
	पूर्ण

	_rtl92c_enable_fw_करोwnload(hw, true);
	_rtl92c_ग_लिखो_fw(hw, version, pfwdata, fwsize);
	_rtl92c_enable_fw_करोwnload(hw, false);

	err = _rtl92c_fw_मुक्त_to_go(hw);
	अगर (err)
		pr_err("Firmware is not ready to run!\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtl92c_करोwnload_fw);

अटल bool _rtl92c_check_fw_पढ़ो_last_h2c(काष्ठा ieee80211_hw *hw, u8 boxnum)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 val_hmetfr, val_mcutst_1;
	bool result = false;

	val_hmetfr = rtl_पढ़ो_byte(rtlpriv, REG_HMETFR);
	val_mcutst_1 = rtl_पढ़ो_byte(rtlpriv, (REG_MCUTST_1 + boxnum));

	अगर (((val_hmetfr >> boxnum) & BIT(0)) == 0 && val_mcutst_1 == 0)
		result = true;
	वापस result;
पूर्ण

अटल व्योम _rtl92c_fill_h2c_command(काष्ठा ieee80211_hw *hw,
			      u8 element_id, u32 cmd_len, u8 *cmdbuffer)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 boxnum;
	u16 box_reg = 0, box_extreg = 0;
	u8 u1b_पंचांगp;
	bool isfw_पढ़ो = false;
	u8 buf_index = 0;
	bool bग_लिखो_sucess = false;
	u8 रुको_h2c_limmit = 100;
	u8 रुको_ग_लिखोh2c_limmit = 100;
	u8 boxcontent[4], boxextcontent[2];
	u32 h2c_रुकोcounter = 0;
	अचिन्हित दीर्घ flag;
	u8 idx;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "come in\n");

	जबतक (true) अणु
		spin_lock_irqsave(&rtlpriv->locks.h2c_lock, flag);
		अगर (rtlhal->h2c_setinprogress) अणु
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"H2C set in progress! Wait to set..element_id(%d).\n",
				element_id);
			जबतक (rtlhal->h2c_setinprogress) अणु
				spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock,
						       flag);
				h2c_रुकोcounter++;
				rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
					"Wait 100 us (%d times)...\n",
					 h2c_रुकोcounter);
				udelay(100);

				अगर (h2c_रुकोcounter > 1000)
					वापस;
				spin_lock_irqsave(&rtlpriv->locks.h2c_lock,
						  flag);
			पूर्ण
			spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock, flag);
		पूर्ण अन्यथा अणु
			rtlhal->h2c_setinprogress = true;
			spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock, flag);
			अवरोध;
		पूर्ण
	पूर्ण

	जबतक (!bग_लिखो_sucess) अणु
		रुको_ग_लिखोh2c_limmit--;
		अगर (रुको_ग_लिखोh2c_limmit == 0) अणु
			pr_err("Write H2C fail because no trigger for FW INT!\n");
			अवरोध;
		पूर्ण

		boxnum = rtlhal->last_hmeboxnum;
		चयन (boxnum) अणु
		हाल 0:
			box_reg = REG_HMEBOX_0;
			box_extreg = REG_HMEBOX_EXT_0;
			अवरोध;
		हाल 1:
			box_reg = REG_HMEBOX_1;
			box_extreg = REG_HMEBOX_EXT_1;
			अवरोध;
		हाल 2:
			box_reg = REG_HMEBOX_2;
			box_extreg = REG_HMEBOX_EXT_2;
			अवरोध;
		हाल 3:
			box_reg = REG_HMEBOX_3;
			box_extreg = REG_HMEBOX_EXT_3;
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
				"switch case %#x not processed\n", boxnum);
			अवरोध;
		पूर्ण

		isfw_पढ़ो = _rtl92c_check_fw_पढ़ो_last_h2c(hw, boxnum);
		जबतक (!isfw_पढ़ो) अणु
			रुको_h2c_limmit--;
			अगर (रुको_h2c_limmit == 0) अणु
				rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
					"Waiting too long for FW read clear HMEBox(%d)!\n",
					boxnum);
				अवरोध;
			पूर्ण

			udelay(10);

			isfw_पढ़ो = _rtl92c_check_fw_पढ़ो_last_h2c(hw, boxnum);
			u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x1BF);
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"Waiting for FW read clear HMEBox(%d)!!! 0x1BF = %2x\n",
				boxnum, u1b_पंचांगp);
		पूर्ण

		अगर (!isfw_पढ़ो) अणु
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"Write H2C register BOX[%d] fail!!!!! Fw do not read.\n",
				boxnum);
			अवरोध;
		पूर्ण

		स_रखो(boxcontent, 0, माप(boxcontent));
		स_रखो(boxextcontent, 0, माप(boxextcontent));
		boxcontent[0] = element_id;
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
			"Write element_id box_reg(%4x) = %2x\n",
			box_reg, element_id);

		चयन (cmd_len) अणु
		हाल 1:
			boxcontent[0] &= ~(BIT(7));
			स_नकल((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 1);

			क्रम (idx = 0; idx < 4; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			पूर्ण
			अवरोध;
		हाल 2:
			boxcontent[0] &= ~(BIT(7));
			स_नकल((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 2);

			क्रम (idx = 0; idx < 4; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			पूर्ण
			अवरोध;
		हाल 3:
			boxcontent[0] &= ~(BIT(7));
			स_नकल((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 3);

			क्रम (idx = 0; idx < 4; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			पूर्ण
			अवरोध;
		हाल 4:
			boxcontent[0] |= (BIT(7));
			स_नकल((u8 *)(boxextcontent),
			       cmdbuffer + buf_index, 2);
			स_नकल((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index + 2, 2);

			क्रम (idx = 0; idx < 2; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, box_extreg + idx,
					       boxextcontent[idx]);
			पूर्ण

			क्रम (idx = 0; idx < 4; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			पूर्ण
			अवरोध;
		हाल 5:
			boxcontent[0] |= (BIT(7));
			स_नकल((u8 *)(boxextcontent),
			       cmdbuffer + buf_index, 2);
			स_नकल((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index + 2, 3);

			क्रम (idx = 0; idx < 2; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, box_extreg + idx,
					       boxextcontent[idx]);
			पूर्ण

			क्रम (idx = 0; idx < 4; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			पूर्ण
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
				"switch case %#x not processed\n", cmd_len);
			अवरोध;
		पूर्ण

		bग_लिखो_sucess = true;

		rtlhal->last_hmeboxnum = boxnum + 1;
		अगर (rtlhal->last_hmeboxnum == 4)
			rtlhal->last_hmeboxnum = 0;

		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
			"pHalData->last_hmeboxnum  = %d\n",
			rtlhal->last_hmeboxnum);
	पूर्ण

	spin_lock_irqsave(&rtlpriv->locks.h2c_lock, flag);
	rtlhal->h2c_setinprogress = false;
	spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock, flag);

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "go out\n");
पूर्ण

व्योम rtl92c_fill_h2c_cmd(काष्ठा ieee80211_hw *hw,
			 u8 element_id, u32 cmd_len, u8 *cmdbuffer)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 पंचांगp_cmdbuf[2];

	अगर (!rtlhal->fw_पढ़ोy) अणु
		WARN_ONCE(true,
			  "rtl8192c-common: return H2C cmd because of Fw download fail!!!\n");
		वापस;
	पूर्ण

	स_रखो(पंचांगp_cmdbuf, 0, 8);
	स_नकल(पंचांगp_cmdbuf, cmdbuffer, cmd_len);
	_rtl92c_fill_h2c_command(hw, element_id, cmd_len, (u8 *)&पंचांगp_cmdbuf);

	वापस;
पूर्ण
EXPORT_SYMBOL(rtl92c_fill_h2c_cmd);

व्योम rtl92c_firmware_selfreset(काष्ठा ieee80211_hw *hw)
अणु
	u8 u1b_पंचांगp;
	u8 delay = 100;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_HMETFR + 3, 0x20);
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);

	जबतक (u1b_पंचांगp & BIT(2)) अणु
		delay--;
		अगर (delay == 0) अणु
			WARN_ONCE(true, "rtl8192c-common: 8051 reset fail.\n");
			अवरोध;
		पूर्ण
		udelay(50);
		u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtl92c_firmware_selfreset);

व्योम rtl92c_set_fw_pwrmode_cmd(काष्ठा ieee80211_hw *hw, u8 mode)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1_h2c_set_pwrmode[3] = अणु 0 पूर्ण;
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "FW LPS mode = %d\n", mode);

	SET_H2CCMD_PWRMODE_PARM_MODE(u1_h2c_set_pwrmode, mode);
	SET_H2CCMD_PWRMODE_PARM_SMART_PS(u1_h2c_set_pwrmode,
		(rtlpriv->mac80211.p2p) ? ppsc->smart_ps : 1);
	SET_H2CCMD_PWRMODE_PARM_BCN_PASS_TIME(u1_h2c_set_pwrmode,
					      ppsc->reg_max_lps_awakeपूर्णांकvl);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
		      "rtl92c_set_fw_rsvdpagepkt(): u1_h2c_set_pwrmode\n",
		      u1_h2c_set_pwrmode, 3);
	rtl92c_fill_h2c_cmd(hw, H2C_SETPWRMODE, 3, u1_h2c_set_pwrmode);
पूर्ण
EXPORT_SYMBOL(rtl92c_set_fw_pwrmode_cmd);

#घोषणा BEACON_PG		0 /*->1*/
#घोषणा PSPOLL_PG		2
#घोषणा शून्य_PG			3
#घोषणा PROBERSP_PG		4 /*->5*/

#घोषणा TOTAL_RESERVED_PKT_LEN	768

अटल u8 reserved_page_packet[TOTAL_RESERVED_PKT_LEN] = अणु
	/* page 0 beacon */
	0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x40, 0x10, 0x10, 0x00, 0x03, 0x50, 0x08,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x64, 0x00, 0x00, 0x04, 0x00, 0x0C, 0x6C, 0x69,
	0x6E, 0x6B, 0x73, 0x79, 0x73, 0x5F, 0x77, 0x6C,
	0x61, 0x6E, 0x01, 0x04, 0x82, 0x84, 0x8B, 0x96,
	0x03, 0x01, 0x01, 0x06, 0x02, 0x00, 0x00, 0x2A,
	0x01, 0x00, 0x32, 0x08, 0x24, 0x30, 0x48, 0x6C,
	0x0C, 0x12, 0x18, 0x60, 0x2D, 0x1A, 0x6C, 0x18,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3D, 0x00, 0xDD, 0x06, 0x00, 0xE0, 0x4C, 0x02,
	0x01, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 1 beacon */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x00, 0x20, 0x8C, 0x00, 0x12, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 2  ps-poll */
	0xA4, 0x10, 0x01, 0xC0, 0x00, 0x40, 0x10, 0x10,
	0x00, 0x03, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x18, 0x00, 0x20, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 3  null */
	0x48, 0x01, 0x00, 0x00, 0x00, 0x40, 0x10, 0x10,
	0x00, 0x03, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x40, 0x10, 0x10, 0x00, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x72, 0x00, 0x20, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 4  probe_resp */
	0x50, 0x00, 0x00, 0x00, 0x00, 0x40, 0x10, 0x10,
	0x00, 0x03, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x40, 0x10, 0x10, 0x00, 0x03, 0x00, 0x00,
	0x9E, 0x46, 0x15, 0x32, 0x27, 0xF2, 0x2D, 0x00,
	0x64, 0x00, 0x00, 0x04, 0x00, 0x0C, 0x6C, 0x69,
	0x6E, 0x6B, 0x73, 0x79, 0x73, 0x5F, 0x77, 0x6C,
	0x61, 0x6E, 0x01, 0x04, 0x82, 0x84, 0x8B, 0x96,
	0x03, 0x01, 0x01, 0x06, 0x02, 0x00, 0x00, 0x2A,
	0x01, 0x00, 0x32, 0x08, 0x24, 0x30, 0x48, 0x6C,
	0x0C, 0x12, 0x18, 0x60, 0x2D, 0x1A, 0x6C, 0x18,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3D, 0x00, 0xDD, 0x06, 0x00, 0xE0, 0x4C, 0x02,
	0x01, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 5  probe_resp */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
पूर्ण;

व्योम rtl92c_set_fw_rsvdpagepkt(काष्ठा ieee80211_hw *hw,
	 bool (*cmd_send_packet)(काष्ठा ieee80211_hw *, काष्ठा sk_buff *))
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा sk_buff *skb = शून्य;

	u32 totalpacketlen;
	bool rtstatus;
	u8 u1rsvdpageloc[3] = अणु 0 पूर्ण;
	bool b_dlok = false;

	u8 *beacon;
	u8 *p_pspoll;
	u8 *nullfunc;
	u8 *p_probersp;
	/*---------------------------------------------------------
				(1) beacon
	---------------------------------------------------------*/
	beacon = &reserved_page_packet[BEACON_PG * 128];
	SET_80211_HDR_ADDRESS2(beacon, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(beacon, mac->bssid);

	/*-------------------------------------------------------
				(2) ps-poll
	--------------------------------------------------------*/
	p_pspoll = &reserved_page_packet[PSPOLL_PG * 128];
	SET_80211_PS_POLL_AID(p_pspoll, (mac->assoc_id | 0xc000));
	SET_80211_PS_POLL_BSSID(p_pspoll, mac->bssid);
	SET_80211_PS_POLL_TA(p_pspoll, mac->mac_addr);

	SET_H2CCMD_RSVDPAGE_LOC_PSPOLL(u1rsvdpageloc, PSPOLL_PG);

	/*--------------------------------------------------------
				(3) null data
	---------------------------------------------------------*/
	nullfunc = &reserved_page_packet[शून्य_PG * 128];
	SET_80211_HDR_ADDRESS1(nullfunc, mac->bssid);
	SET_80211_HDR_ADDRESS2(nullfunc, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(nullfunc, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_शून्य_DATA(u1rsvdpageloc, शून्य_PG);

	/*---------------------------------------------------------
				(4) probe response
	----------------------------------------------------------*/
	p_probersp = &reserved_page_packet[PROBERSP_PG * 128];
	SET_80211_HDR_ADDRESS1(p_probersp, mac->bssid);
	SET_80211_HDR_ADDRESS2(p_probersp, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(p_probersp, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(u1rsvdpageloc, PROBERSP_PG);

	totalpacketlen = TOTAL_RESERVED_PKT_LEN;

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "rtl92c_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL\n",
		      &reserved_page_packet[0], totalpacketlen);
	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
		      "rtl92c_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL\n",
		      u1rsvdpageloc, 3);

	skb = dev_alloc_skb(totalpacketlen);
	अगर (!skb)
		वापस;
	skb_put_data(skb, &reserved_page_packet, totalpacketlen);

	अगर (cmd_send_packet)
		rtstatus = cmd_send_packet(hw, skb);
	अन्यथा
		rtstatus = rtl_cmd_send_packet(hw, skb);

	अगर (rtstatus)
		b_dlok = true;

	अगर (b_dlok) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Set RSVD page location to Fw.\n");
		RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
				"H2C_RSVDPAGE:\n",
				u1rsvdpageloc, 3);
		rtl92c_fill_h2c_cmd(hw, H2C_RSVDPAGE,
				    माप(u1rsvdpageloc), u1rsvdpageloc);
	पूर्ण अन्यथा
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Set RSVD page location to Fw FAIL!!!!!!.\n");
पूर्ण
EXPORT_SYMBOL(rtl92c_set_fw_rsvdpagepkt);

व्योम rtl92c_set_fw_joinbss_report_cmd(काष्ठा ieee80211_hw *hw, u8 mstatus)
अणु
	u8 u1_joinbssrpt_parm[1] = अणु 0 पूर्ण;

	SET_H2CCMD_JOINBSSRPT_PARM_OPMODE(u1_joinbssrpt_parm, mstatus);

	rtl92c_fill_h2c_cmd(hw, H2C_JOINBSSRPT, 1, u1_joinbssrpt_parm);
पूर्ण
EXPORT_SYMBOL(rtl92c_set_fw_joinbss_report_cmd);

अटल व्योम rtl92c_set_p2p_ctw_period_cmd(काष्ठा ieee80211_hw *hw, u8 ctwinकरोw)
अणु
	u8 u1_ctwinकरोw_period[1] = अणु ctwinकरोwपूर्ण;

	rtl92c_fill_h2c_cmd(hw, H2C_P2P_PS_CTW_CMD, 1, u1_ctwinकरोw_period);
पूर्ण

/* refactored routine */
अटल व्योम set_noa_data(काष्ठा rtl_priv *rtlpriv,
			 काष्ठा rtl_p2p_ps_info *p2pinfo,
			 काष्ठा p2p_ps_offload_t *p2p_ps_offload)
अणु
	पूर्णांक i;
	u32	start_समय, tsf_low;

	/* hw only support 2 set of NoA */
	क्रम (i = 0 ; i < p2pinfo->noa_num ; i++) अणु
		/* To control the reg setting क्रम which NOA*/
		rtl_ग_लिखो_byte(rtlpriv, 0x5cf, (i << 4));
		अगर (i == 0)
			p2p_ps_offload->noa0_en = 1;
		अन्यथा
			p2p_ps_offload->noa1_en = 1;

		/* config P2P NoA Descriptor Register */
		rtl_ग_लिखो_dword(rtlpriv, 0x5E0,
				p2pinfo->noa_duration[i]);
		rtl_ग_लिखो_dword(rtlpriv, 0x5E4,
				p2pinfo->noa_पूर्णांकerval[i]);

		/*Get Current TSF value */
		tsf_low = rtl_पढ़ो_dword(rtlpriv, REG_TSFTR);

		start_समय = p2pinfo->noa_start_समय[i];
		अगर (p2pinfo->noa_count_type[i] != 1) अणु
			जबतक (start_समय <= (tsf_low+(50*1024))) अणु
				start_समय += p2pinfo->noa_पूर्णांकerval[i];
				अगर (p2pinfo->noa_count_type[i] != 255)
					p2pinfo->noa_count_type[i]--;
			पूर्ण
		पूर्ण
		rtl_ग_लिखो_dword(rtlpriv, 0x5E8, start_समय);
		rtl_ग_लिखो_dword(rtlpriv, 0x5EC,
				p2pinfo->noa_count_type[i]);
	पूर्ण
पूर्ण

व्योम rtl92c_set_p2p_ps_offload_cmd(काष्ठा ieee80211_hw *hw, u8 p2p_ps_state)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *rtlps = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_p2p_ps_info *p2pinfo = &(rtlps->p2p_ps_info);
	काष्ठा p2p_ps_offload_t *p2p_ps_offload = &rtlhal->p2p_ps_offload;
	u16	ctwinकरोw;

	चयन (p2p_ps_state) अणु
	हाल P2P_PS_DISABLE:
			rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD,
				"P2P_PS_DISABLE\n");
			स_रखो(p2p_ps_offload, 0, माप(*p2p_ps_offload));
			अवरोध;
	हाल P2P_PS_ENABLE:
			rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD,
				"P2P_PS_ENABLE\n");
			/* update CTWinकरोw value. */
			अगर (p2pinfo->ctwinकरोw > 0) अणु
				p2p_ps_offload->ctwinकरोw_en = 1;
				ctwinकरोw = p2pinfo->ctwinकरोw;
				rtl92c_set_p2p_ctw_period_cmd(hw, ctwinकरोw);
			पूर्ण
			/* call refactored routine */
			set_noa_data(rtlpriv, p2pinfo, p2p_ps_offload);

			अगर ((p2pinfo->opp_ps == 1) || (p2pinfo->noa_num > 0)) अणु
				/* rst p2p circuit */
				rtl_ग_लिखो_byte(rtlpriv, REG_DUAL_TSF_RST,
					       BIT(4));

				p2p_ps_offload->offload_en = 1;

				अगर (P2P_ROLE_GO == rtlpriv->mac80211.p2p) अणु
					p2p_ps_offload->role = 1;
					p2p_ps_offload->allstasleep = 0;
				पूर्ण अन्यथा अणु
					p2p_ps_offload->role = 0;
				पूर्ण

				p2p_ps_offload->discovery = 0;
			पूर्ण
			अवरोध;
	हाल P2P_PS_SCAN:
			rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_SCAN\n");
			p2p_ps_offload->discovery = 1;
			अवरोध;
	हाल P2P_PS_SCAN_DONE:
			rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD,
				"P2P_PS_SCAN_DONE\n");
			p2p_ps_offload->discovery = 0;
			p2pinfo->p2p_ps_state = P2P_PS_ENABLE;
			अवरोध;
	शेष:
			अवरोध;
	पूर्ण

	rtl92c_fill_h2c_cmd(hw, H2C_P2P_PS_OFFLOAD, 1, (u8 *)p2p_ps_offload);

पूर्ण
EXPORT_SYMBOL_GPL(rtl92c_set_p2p_ps_offload_cmd);
