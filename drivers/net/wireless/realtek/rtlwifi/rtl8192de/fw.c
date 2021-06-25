<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "../efuse.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "fw.h"
#समावेश "sw.h"

अटल bool _rtl92d_is_fw_करोwnloaded(काष्ठा rtl_priv *rtlpriv)
अणु
	वापस (rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL) & MCUFWDL_RDY) ?
		true : false;
पूर्ण

अटल व्योम _rtl92d_enable_fw_करोwnload(काष्ठा ieee80211_hw *hw, bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp;

	अगर (enable) अणु
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगp | 0x04);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, पंचांगp | 0x01);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL + 2);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL + 2, पंचांगp & 0xf7);
	पूर्ण अन्यथा अणु
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, पंचांगp & 0xfe);
		/* Reserved क्रम fw extension.
		 * 0x81[7] is used क्रम mac0 status ,
		 * so करोn't ग_लिखो this reg here
		 * rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL + 1, 0x00);*/
	पूर्ण
पूर्ण

अटल व्योम _rtl92d_ग_लिखो_fw(काष्ठा ieee80211_hw *hw,
			     क्रमागत version_8192d version, u8 *buffer, u32 size)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 *bufferptr = buffer;
	u32 pagक्रमागतs, reमुख्यsize;
	u32 page, offset;

	rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE, "FW size is %d bytes,\n", size);
	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192DE)
		rtl_fill_dummy(bufferptr, &size);
	pagक्रमागतs = size / FW_8192D_PAGE_SIZE;
	reमुख्यsize = size % FW_8192D_PAGE_SIZE;
	अगर (pagक्रमागतs > 8)
		pr_err("Page numbers should not greater then 8\n");
	क्रम (page = 0; page < pagक्रमागतs; page++) अणु
		offset = page * FW_8192D_PAGE_SIZE;
		rtl_fw_page_ग_लिखो(hw, page, (bufferptr + offset),
				  FW_8192D_PAGE_SIZE);
	पूर्ण
	अगर (reमुख्यsize) अणु
		offset = pagक्रमागतs * FW_8192D_PAGE_SIZE;
		page = pagक्रमागतs;
		rtl_fw_page_ग_लिखो(hw, page, (bufferptr + offset), reमुख्यsize);
	पूर्ण
पूर्ण

अटल पूर्णांक _rtl92d_fw_मुक्त_to_go(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 counter = 0;
	u32 value32;

	करो अणु
		value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);
	पूर्ण जबतक ((counter++ < FW_8192D_POLLING_TIMEOUT_COUNT) &&
		 (!(value32 & FWDL_CHKSUM_RPT)));
	अगर (counter >= FW_8192D_POLLING_TIMEOUT_COUNT) अणु
		pr_err("chksum report fail! REG_MCUFWDL:0x%08x\n",
		       value32);
		वापस -EIO;
	पूर्ण
	value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);
	value32 |= MCUFWDL_RDY;
	rtl_ग_लिखो_dword(rtlpriv, REG_MCUFWDL, value32);
	वापस 0;
पूर्ण

व्योम rtl92d_firmware_selfreset(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1b_पंचांगp;
	u8 delay = 100;

	/* Set (REG_HMETFR + 3) to  0x20 is reset 8051 */
	rtl_ग_लिखो_byte(rtlpriv, REG_HMETFR + 3, 0x20);
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	जबतक (u1b_पंचांगp & BIT(2)) अणु
		delay--;
		अगर (delay == 0)
			अवरोध;
		udelay(50);
		u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	पूर्ण
	WARN_ONCE((delay <= 0), "rtl8192de: 8051 reset failed!\n");
	rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
		"=====> 8051 reset success (%d)\n", delay);
पूर्ण

अटल पूर्णांक _rtl92d_fw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 counter;

	rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG, "FW already have download\n");
	/* polling क्रम FW पढ़ोy */
	counter = 0;
	करो अणु
		अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
			अगर (rtl_पढ़ो_byte(rtlpriv, FW_MAC0_READY) &
			    MAC0_READY) अणु
				rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
					"Polling FW ready success!! REG_MCUFWDL: 0x%x\n",
					rtl_पढ़ो_byte(rtlpriv,
						      FW_MAC0_READY));
				वापस 0;
			पूर्ण
			udelay(5);
		पूर्ण अन्यथा अणु
			अगर (rtl_पढ़ो_byte(rtlpriv, FW_MAC1_READY) &
			    MAC1_READY) अणु
				rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
					"Polling FW ready success!! REG_MCUFWDL: 0x%x\n",
					rtl_पढ़ो_byte(rtlpriv,
						      FW_MAC1_READY));
				वापस 0;
			पूर्ण
			udelay(5);
		पूर्ण
	पूर्ण जबतक (counter++ < POLLING_READY_TIMEOUT_COUNT);

	अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
		rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
			"Polling FW ready fail!! MAC0 FW init not ready: 0x%x\n",
			rtl_पढ़ो_byte(rtlpriv, FW_MAC0_READY));
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
			"Polling FW ready fail!! MAC1 FW init not ready: 0x%x\n",
			rtl_पढ़ो_byte(rtlpriv, FW_MAC1_READY));
	पूर्ण
	rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
		"Polling FW ready fail!! REG_MCUFWDL:0x%08x\n",
		rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL));
	वापस -1;
पूर्ण

पूर्णांक rtl92d_करोwnload_fw(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 *pfwheader;
	u8 *pfwdata;
	u32 fwsize;
	पूर्णांक err;
	क्रमागत version_8192d version = rtlhal->version;
	u8 value;
	u32 count;
	bool fw_करोwnloaded = false, fwdl_in_process = false;
	अचिन्हित दीर्घ flags;

	अगर (rtlpriv->max_fw_size == 0 || !rtlhal->pfirmware)
		वापस 1;
	fwsize = rtlhal->fwsize;
	pfwheader = rtlhal->pfirmware;
	pfwdata = rtlhal->pfirmware;
	rtlhal->fw_version = (u16) GET_FIRMWARE_HDR_VERSION(pfwheader);
	rtlhal->fw_subversion = (u16) GET_FIRMWARE_HDR_SUB_VER(pfwheader);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"FirmwareVersion(%d), FirmwareSubVersion(%d), Signature(%#x)\n",
		rtlhal->fw_version, rtlhal->fw_subversion,
		GET_FIRMWARE_HDR_SIGNATURE(pfwheader));
	अगर (IS_FW_HEADER_EXIST(pfwheader)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Shift 32 bytes for FW header!!\n");
		pfwdata = pfwdata + 32;
		fwsize = fwsize - 32;
	पूर्ण

	spin_lock_irqsave(&globalmutex_क्रम_fwकरोwnload, flags);
	fw_करोwnloaded = _rtl92d_is_fw_करोwnloaded(rtlpriv);
	अगर ((rtl_पढ़ो_byte(rtlpriv, 0x1f) & BIT(5)) == BIT(5))
		fwdl_in_process = true;
	अन्यथा
		fwdl_in_process = false;
	अगर (fw_करोwnloaded) अणु
		spin_unlock_irqrestore(&globalmutex_क्रम_fwकरोwnload, flags);
		जाओ निकास;
	पूर्ण अन्यथा अगर (fwdl_in_process) अणु
		spin_unlock_irqrestore(&globalmutex_क्रम_fwकरोwnload, flags);
		क्रम (count = 0; count < 5000; count++) अणु
			udelay(500);
			spin_lock_irqsave(&globalmutex_क्रम_fwकरोwnload, flags);
			fw_करोwnloaded = _rtl92d_is_fw_करोwnloaded(rtlpriv);
			अगर ((rtl_पढ़ो_byte(rtlpriv, 0x1f) & BIT(5)) == BIT(5))
				fwdl_in_process = true;
			अन्यथा
				fwdl_in_process = false;
			spin_unlock_irqrestore(&globalmutex_क्रम_fwकरोwnload,
					       flags);
			अगर (fw_करोwnloaded)
				जाओ निकास;
			अन्यथा अगर (!fwdl_in_process)
				अवरोध;
			अन्यथा
				rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
					"Wait for another mac download fw\n");
		पूर्ण
		spin_lock_irqsave(&globalmutex_क्रम_fwकरोwnload, flags);
		value = rtl_पढ़ो_byte(rtlpriv, 0x1f);
		value |= BIT(5);
		rtl_ग_लिखो_byte(rtlpriv, 0x1f, value);
		spin_unlock_irqrestore(&globalmutex_क्रम_fwकरोwnload, flags);
	पूर्ण अन्यथा अणु
		value = rtl_पढ़ो_byte(rtlpriv, 0x1f);
		value |= BIT(5);
		rtl_ग_लिखो_byte(rtlpriv, 0x1f, value);
		spin_unlock_irqrestore(&globalmutex_क्रम_fwकरोwnload, flags);
	पूर्ण

	/* If 8051 is running in RAM code, driver should
	 * inक्रमm Fw to reset by itself, or it will cause
	 * करोwnload Fw fail.*/
	/* 8051 RAM code */
	अगर (rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL) & BIT(7)) अणु
		rtl92d_firmware_selfreset(hw);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0x00);
	पूर्ण
	_rtl92d_enable_fw_करोwnload(hw, true);
	_rtl92d_ग_लिखो_fw(hw, version, pfwdata, fwsize);
	_rtl92d_enable_fw_करोwnload(hw, false);
	spin_lock_irqsave(&globalmutex_क्रम_fwकरोwnload, flags);
	err = _rtl92d_fw_मुक्त_to_go(hw);
	/* करोwnload fw over,clear 0x1f[5] */
	value = rtl_पढ़ो_byte(rtlpriv, 0x1f);
	value &= (~BIT(5));
	rtl_ग_लिखो_byte(rtlpriv, 0x1f, value);
	spin_unlock_irqrestore(&globalmutex_क्रम_fwकरोwnload, flags);
	अगर (err)
		pr_err("fw is not ready to run!\n");
निकास:
	err = _rtl92d_fw_init(hw);
	वापस err;
पूर्ण

अटल bool _rtl92d_check_fw_पढ़ो_last_h2c(काष्ठा ieee80211_hw *hw, u8 boxnum)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 val_hmetfr;
	bool result = false;

	val_hmetfr = rtl_पढ़ो_byte(rtlpriv, REG_HMETFR);
	अगर (((val_hmetfr >> boxnum) & BIT(0)) == 0)
		result = true;
	वापस result;
पूर्ण

अटल व्योम _rtl92d_fill_h2c_command(काष्ठा ieee80211_hw *hw,
			      u8 element_id, u32 cmd_len, u8 *cmdbuffer)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 boxnum;
	u16 box_reg = 0, box_extreg = 0;
	u8 u1b_पंचांगp;
	bool isfw_पढ़ो = false;
	u8 buf_index = 0;
	bool bग_लिखो_success = false;
	u8 रुको_h2c_limmit = 100;
	u8 रुको_ग_लिखोh2c_limmit = 100;
	u8 boxcontent[4], boxextcontent[2];
	u32 h2c_रुकोcounter = 0;
	अचिन्हित दीर्घ flag;
	u8 idx;

	अगर (ppsc->rfpwr_state == ERFOFF || ppsc->inactive_pwrstate == ERFOFF) अणु
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
			"Return as RF is off!!!\n");
		वापस;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "come in\n");
	जबतक (true) अणु
		spin_lock_irqsave(&rtlpriv->locks.h2c_lock, flag);
		अगर (rtlhal->h2c_setinprogress) अणु
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"H2C set in progress! Wait to set..element_id(%d)\n",
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
	जबतक (!bग_लिखो_success) अणु
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
			pr_err("switch case %#x not processed\n",
			       boxnum);
			अवरोध;
		पूर्ण
		isfw_पढ़ो = _rtl92d_check_fw_पढ़ो_last_h2c(hw, boxnum);
		जबतक (!isfw_पढ़ो) अणु
			रुको_h2c_limmit--;
			अगर (रुको_h2c_limmit == 0) अणु
				rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
					"Waiting too long for FW read clear HMEBox(%d)!\n",
					boxnum);
				अवरोध;
			पूर्ण
			udelay(10);
			isfw_पढ़ो = _rtl92d_check_fw_पढ़ो_last_h2c(hw, boxnum);
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
			स_नकल(boxcontent + 1, cmdbuffer + buf_index, 1);
			क्रम (idx = 0; idx < 4; idx++)
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			अवरोध;
		हाल 2:
			boxcontent[0] &= ~(BIT(7));
			स_नकल(boxcontent + 1, cmdbuffer + buf_index, 2);
			क्रम (idx = 0; idx < 4; idx++)
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			अवरोध;
		हाल 3:
			boxcontent[0] &= ~(BIT(7));
			स_नकल(boxcontent + 1, cmdbuffer + buf_index, 3);
			क्रम (idx = 0; idx < 4; idx++)
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			अवरोध;
		हाल 4:
			boxcontent[0] |= (BIT(7));
			स_नकल(boxextcontent, cmdbuffer + buf_index, 2);
			स_नकल(boxcontent + 1, cmdbuffer + buf_index + 2, 2);
			क्रम (idx = 0; idx < 2; idx++)
				rtl_ग_लिखो_byte(rtlpriv, box_extreg + idx,
					       boxextcontent[idx]);
			क्रम (idx = 0; idx < 4; idx++)
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			अवरोध;
		हाल 5:
			boxcontent[0] |= (BIT(7));
			स_नकल(boxextcontent, cmdbuffer + buf_index, 2);
			स_नकल(boxcontent + 1, cmdbuffer + buf_index + 2, 3);
			क्रम (idx = 0; idx < 2; idx++)
				rtl_ग_लिखो_byte(rtlpriv, box_extreg + idx,
					       boxextcontent[idx]);
			क्रम (idx = 0; idx < 4; idx++)
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			अवरोध;
		शेष:
			pr_err("switch case %#x not processed\n",
			       cmd_len);
			अवरोध;
		पूर्ण
		bग_लिखो_success = true;
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

व्योम rtl92d_fill_h2c_cmd(काष्ठा ieee80211_hw *hw,
			 u8 element_id, u32 cmd_len, u8 *cmdbuffer)
अणु
	u32 पंचांगp_cmdbuf[2];

	स_रखो(पंचांगp_cmdbuf, 0, 8);
	स_नकल(पंचांगp_cmdbuf, cmdbuffer, cmd_len);
	_rtl92d_fill_h2c_command(hw, element_id, cmd_len, (u8 *)&पंचांगp_cmdbuf);
	वापस;
पूर्ण

अटल bool _rtl92d_cmd_send_packet(काष्ठा ieee80211_hw *hw,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring;
	काष्ठा rtl_tx_desc *pdesc;
	u8 idx = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *pskb;

	ring = &rtlpci->tx_ring[BEACON_QUEUE];
	pskb = __skb_dequeue(&ring->queue);
	kमुक्त_skb(pskb);
	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);
	pdesc = &ring->desc[idx];
	/* discard output from call below */
	rtlpriv->cfg->ops->get_desc(hw, (u8 *)pdesc, true, HW_DESC_OWN);
	rtlpriv->cfg->ops->fill_tx_cmddesc(hw, (u8 *) pdesc, 1, 1, skb);
	__skb_queue_tail(&ring->queue, skb);
	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);
	rtlpriv->cfg->ops->tx_polling(hw, BEACON_QUEUE);
	वापस true;
पूर्ण

#घोषणा BEACON_PG		0	/*->1 */
#घोषणा PSPOLL_PG		2
#घोषणा शून्य_PG			3
#घोषणा PROBERSP_PG		4	/*->5 */
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

व्योम rtl92d_set_fw_rsvdpagepkt(काष्ठा ieee80211_hw *hw, bool dl_finished)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा sk_buff *skb = शून्य;
	u32 totalpacketlen;
	bool rtstatus;
	u8 u1rsvdpageloc[3] = अणु 0 पूर्ण;
	bool dlok = false;
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
		      "rtl92d_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL",
		      &reserved_page_packet[0], totalpacketlen);
	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
		      "rtl92d_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL",
		      u1rsvdpageloc, 3);
	skb = dev_alloc_skb(totalpacketlen);
	अगर (!skb) अणु
		dlok = false;
	पूर्ण अन्यथा अणु
		skb_put_data(skb, &reserved_page_packet, totalpacketlen);
		rtstatus = _rtl92d_cmd_send_packet(hw, skb);

		अगर (rtstatus)
			dlok = true;
	पूर्ण
	अगर (dlok) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Set RSVD page location to Fw\n");
		RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
			      "H2C_RSVDPAGE", u1rsvdpageloc, 3);
		rtl92d_fill_h2c_cmd(hw, H2C_RSVDPAGE,
			माप(u1rsvdpageloc), u1rsvdpageloc);
	पूर्ण अन्यथा
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Set RSVD page location to Fw FAIL!!!!!!\n");
पूर्ण

व्योम rtl92d_set_fw_joinbss_report_cmd(काष्ठा ieee80211_hw *hw, u8 mstatus)
अणु
	u8 u1_joinbssrpt_parm[1] = अणु0पूर्ण;

	SET_H2CCMD_JOINBSSRPT_PARM_OPMODE(u1_joinbssrpt_parm, mstatus);
	rtl92d_fill_h2c_cmd(hw, H2C_JOINBSSRPT, 1, u1_joinbssrpt_parm);
पूर्ण
