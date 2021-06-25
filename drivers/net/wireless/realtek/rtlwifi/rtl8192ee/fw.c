<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "../core.h"
#समावेश "../efuse.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "fw.h"
#समावेश "dm.h"

अटल व्योम _rtl92ee_enable_fw_करोwnload(काष्ठा ieee80211_hw *hw, bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp;

	अगर (enable) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0x05);

		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL + 2);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL + 2, पंचांगp & 0xf7);
	पूर्ण अन्यथा अणु
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, पंचांगp & 0xfe);
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_ग_लिखो_fw(काष्ठा ieee80211_hw *hw,
			      क्रमागत version_8192e version,
			      u8 *buffer, u32 size)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 *bufferptr = (u8 *)buffer;
	u32 pagक्रमागतs, reमुख्यsize;
	u32 page, offset;

	rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "FW size is %d bytes,\n", size);

	rtl_fill_dummy(bufferptr, &size);

	pagक्रमागतs = size / FW_8192C_PAGE_SIZE;
	reमुख्यsize = size % FW_8192C_PAGE_SIZE;

	अगर (pagक्रमागतs > 8)
		pr_err("Page numbers should not greater then 8\n");

	क्रम (page = 0; page < pagक्रमागतs; page++) अणु
		offset = page * FW_8192C_PAGE_SIZE;
		rtl_fw_page_ग_लिखो(hw, page, (bufferptr + offset),
				  FW_8192C_PAGE_SIZE);
		udelay(2);
	पूर्ण

	अगर (reमुख्यsize) अणु
		offset = pagक्रमागतs * FW_8192C_PAGE_SIZE;
		page = pagक्रमागतs;
		rtl_fw_page_ग_लिखो(hw, page, (bufferptr + offset), reमुख्यsize);
	पूर्ण
पूर्ण

अटल पूर्णांक _rtl92ee_fw_मुक्त_to_go(काष्ठा ieee80211_hw *hw)
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
		pr_err("chksum report fail! REG_MCUFWDL:0x%08x\n",
		       value32);
		जाओ निकास;
	पूर्ण
	value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);
	value32 |= MCUFWDL_RDY;
	value32 &= ~WINTINI_RDY;
	rtl_ग_लिखो_dword(rtlpriv, REG_MCUFWDL, value32);

	rtl92ee_firmware_selfreset(hw);
	counter = 0;

	करो अणु
		value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);
		अगर (value32 & WINTINI_RDY)
			वापस 0;

		udelay(FW_8192C_POLLING_DELAY*10);

	पूर्ण जबतक (counter++ < FW_8192C_POLLING_TIMEOUT_COUNT);

	pr_err("Polling FW ready fail!! REG_MCUFWDL:0x%08x. count = %d\n",
	       value32, counter);

निकास:
	वापस err;
पूर्ण

पूर्णांक rtl92ee_करोwnload_fw(काष्ठा ieee80211_hw *hw, bool buse_wake_on_wlan_fw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtlwअगरi_firmware_header *pfwheader;
	u8 *pfwdata;
	u32 fwsize;
	क्रमागत version_8192e version = rtlhal->version;

	अगर (!rtlhal->pfirmware)
		वापस 1;

	pfwheader = (काष्ठा rtlwअगरi_firmware_header *)rtlhal->pfirmware;
	rtlhal->fw_version = le16_to_cpu(pfwheader->version);
	rtlhal->fw_subversion = pfwheader->subversion;
	pfwdata = (u8 *)rtlhal->pfirmware;
	fwsize = rtlhal->fwsize;
	rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
		"normal Firmware SIZE %d\n", fwsize);

	अगर (IS_FW_HEADER_EXIST(pfwheader)) अणु
		rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
			"Firmware Version(%d), Signature(%#x),Size(%d)\n",
			pfwheader->version, pfwheader->signature,
			(पूर्णांक)माप(काष्ठा rtlwअगरi_firmware_header));

		pfwdata = pfwdata + माप(काष्ठा rtlwअगरi_firmware_header);
		fwsize = fwsize - माप(काष्ठा rtlwअगरi_firmware_header);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
			"Firmware no Header, Signature(%#x)\n",
			pfwheader->signature);
	पूर्ण

	अगर (rtlhal->mac_func_enable) अणु
		अगर (rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL) & BIT(7)) अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0);
			rtl92ee_firmware_selfreset(hw);
		पूर्ण
	पूर्ण
	_rtl92ee_enable_fw_करोwnload(hw, true);
	_rtl92ee_ग_लिखो_fw(hw, version, pfwdata, fwsize);
	_rtl92ee_enable_fw_करोwnload(hw, false);

	वापस _rtl92ee_fw_मुक्त_to_go(hw);
पूर्ण

अटल bool _rtl92ee_check_fw_पढ़ो_last_h2c(काष्ठा ieee80211_hw *hw, u8 boxnum)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 val_hmetfr;
	bool result = false;

	val_hmetfr = rtl_पढ़ो_byte(rtlpriv, REG_HMETFR);
	अगर (((val_hmetfr >> boxnum) & BIT(0)) == 0)
		result = true;
	वापस result;
पूर्ण

अटल व्योम _rtl92ee_fill_h2c_command(काष्ठा ieee80211_hw *hw, u8 element_id,
				      u32 cmd_len, u8 *cmdbuffer)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 boxnum;
	u16 box_reg = 0, box_extreg = 0;
	u8 u1b_पंचांगp;
	bool isfw_पढ़ो = false;
	u8 buf_index = 0;
	bool bग_लिखो_sucess = false;
	u8 रुको_h2c_limmit = 100;
	u8 boxcontent[4], boxextcontent[4];
	u32 h2c_रुकोcounter = 0;
	अचिन्हित दीर्घ flag;
	u8 idx;

	अगर (ppsc->करोt11_psmode != EACTIVE ||
	    ppsc->inactive_pwrstate == ERFOFF) अणु
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
			"FillH2CCommand8192E(): Return because RF is off!!!\n");
		वापस;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "come in\n");

	/* 1. Prevent race condition in setting H2C cmd.
	 * (copy from MgntActSet_RF_State().)
	 */
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
		/* 2. Find the last BOX number which has been ग_लिखोn. */
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

		/* 3. Check अगर the box content is empty. */
		isfw_पढ़ो = false;
		u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_CR);

		अगर (u1b_पंचांगp != 0xea) अणु
			isfw_पढ़ो = true;
		पूर्ण अन्यथा अणु
			अगर (rtl_पढ़ो_byte(rtlpriv, REG_TXDMA_STATUS) == 0xea ||
			    rtl_पढ़ो_byte(rtlpriv, REG_TXPKT_EMPTY) == 0xea)
				rtl_ग_लिखो_byte(rtlpriv, REG_SYS_CFG1 + 3, 0xff);
		पूर्ण

		अगर (isfw_पढ़ो) अणु
			रुको_h2c_limmit = 100;
			isfw_पढ़ो = _rtl92ee_check_fw_पढ़ो_last_h2c(hw, boxnum);
			जबतक (!isfw_पढ़ो) अणु
				रुको_h2c_limmit--;
				अगर (रुको_h2c_limmit == 0) अणु
					rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
						"Waiting too long for FW read clear HMEBox(%d)!!!\n",
						boxnum);
					अवरोध;
				पूर्ण
				udelay(10);
				isfw_पढ़ो =
				  _rtl92ee_check_fw_पढ़ो_last_h2c(hw, boxnum);
				u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x130);
				rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
					"Waiting for FW read clear HMEBox(%d)!!! 0x130 = %2x\n",
					boxnum, u1b_पंचांगp);
			पूर्ण
		पूर्ण

		/* If Fw has not पढ़ो the last
		 * H2C cmd, अवरोध and give up this H2C.
		 */
		अगर (!isfw_पढ़ो) अणु
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"Write H2C reg BOX[%d] fail,Fw don't read.\n",
				boxnum);
			अवरोध;
		पूर्ण
		/* 4. Fill the H2C cmd पूर्णांकo box */
		स_रखो(boxcontent, 0, माप(boxcontent));
		स_रखो(boxextcontent, 0, माप(boxextcontent));
		boxcontent[0] = element_id;
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
			"Write element_id box_reg(%4x) = %2x\n",
			box_reg, element_id);

		चयन (cmd_len) अणु
		हाल 1:
		हाल 2:
		हाल 3:
			/*boxcontent[0] &= ~(BIT(7));*/
			स_नकल((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, cmd_len);

			क्रम (idx = 0; idx < 4; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			पूर्ण
			अवरोध;
		हाल 4:
		हाल 5:
		हाल 6:
		हाल 7:
			/*boxcontent[0] |= (BIT(7));*/
			स_नकल((u8 *)(boxextcontent),
			       cmdbuffer + buf_index+3, cmd_len-3);
			स_नकल((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 3);

			क्रम (idx = 0; idx < 4; idx++) अणु
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

व्योम rtl92ee_fill_h2c_cmd(काष्ठा ieee80211_hw *hw,
			  u8 element_id, u32 cmd_len, u8 *cmdbuffer)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 पंचांगp_cmdbuf[2];

	अगर (!rtlhal->fw_पढ़ोy) अणु
		WARN_ONCE(true,
			  "rtl8192ee: error H2C cmd because of Fw download fail!!!\n");
		वापस;
	पूर्ण

	स_रखो(पंचांगp_cmdbuf, 0, 8);
	स_नकल(पंचांगp_cmdbuf, cmdbuffer, cmd_len);
	_rtl92ee_fill_h2c_command(hw, element_id, cmd_len, (u8 *)&पंचांगp_cmdbuf);
पूर्ण

व्योम rtl92ee_firmware_selfreset(काष्ठा ieee80211_hw *hw)
अणु
	u8 u1b_पंचांगp;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_पंचांगp & (~BIT(0))));

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, (u1b_पंचांगp & (~BIT(2))));

	udelay(50);

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_पंचांगp | BIT(0)));

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, (u1b_पंचांगp | BIT(2)));

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"  _8051Reset92E(): 8051 reset success .\n");
पूर्ण

व्योम rtl92ee_set_fw_pwrmode_cmd(काष्ठा ieee80211_hw *hw, u8 mode)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1_h2c_set_pwrmode[H2C_92E_PWEMODE_LENGTH] = अणु 0 पूर्ण;
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 rlbm, घातer_state = 0, byte5 = 0;
	u8 awake_पूर्णांकvl;	/* DTIM = (awake_पूर्णांकvl - 1) */
	काष्ठा rtl_btc_ops *btc_ops = rtlpriv->btcoexist.btc_ops;
	bool bt_ctrl_lps = (rtlpriv->cfg->ops->get_btc_status() ?
			    btc_ops->btc_is_bt_ctrl_lps(rtlpriv) : false);
	bool bt_lps_on = (rtlpriv->cfg->ops->get_btc_status() ?
			  btc_ops->btc_is_bt_lps_on(rtlpriv) : false);

	अगर (bt_ctrl_lps)
		mode = (bt_lps_on ? FW_PS_MIN_MODE : FW_PS_ACTIVE_MODE);

	rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG, "FW LPS mode = %d (coex:%d)\n",
		mode, bt_ctrl_lps);

	चयन (mode) अणु
	हाल FW_PS_MIN_MODE:
		rlbm = 0;
		awake_पूर्णांकvl = 2;
		अवरोध;
	हाल FW_PS_MAX_MODE:
		rlbm = 1;
		awake_पूर्णांकvl = 2;
		अवरोध;
	हाल FW_PS_DTIM_MODE:
		rlbm = 2;
		awake_पूर्णांकvl = ppsc->reg_max_lps_awakeपूर्णांकvl;
		/* hw->conf.ps_dtim_period or mac->vअगर->bss_conf.dtim_period
		 * is only used in swlps.
		 */
		अवरोध;
	शेष:
		rlbm = 2;
		awake_पूर्णांकvl = 4;
		अवरोध;
	पूर्ण

	अगर (rtlpriv->mac80211.p2p) अणु
		awake_पूर्णांकvl = 2;
		rlbm = 1;
	पूर्ण

	अगर (mode == FW_PS_ACTIVE_MODE) अणु
		byte5 = 0x40;
		घातer_state = FW_PWR_STATE_ACTIVE;
	पूर्ण अन्यथा अणु
		अगर (bt_ctrl_lps) अणु
			byte5 = btc_ops->btc_get_lps_val(rtlpriv);
			घातer_state = btc_ops->btc_get_rpwm_val(rtlpriv);

			अगर ((rlbm == 2) && (byte5 & BIT(4))) अणु
				/* Keep awake पूर्णांकerval to 1 to prevent from
				 * decreasing coex perक्रमmance
				 */
				awake_पूर्णांकvl = 2;
				rlbm = 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			byte5 = 0x40;
			घातer_state = FW_PWR_STATE_RF_OFF;
		पूर्ण
	पूर्ण

	SET_H2CCMD_PWRMODE_PARM_MODE(u1_h2c_set_pwrmode, ((mode) ? 1 : 0));
	SET_H2CCMD_PWRMODE_PARM_RLBM(u1_h2c_set_pwrmode, rlbm);
	SET_H2CCMD_PWRMODE_PARM_SMART_PS(u1_h2c_set_pwrmode,
					 bt_ctrl_lps ? 0 :
					 ((rtlpriv->mac80211.p2p) ?
					  ppsc->smart_ps : 1));
	SET_H2CCMD_PWRMODE_PARM_AWAKE_INTERVAL(u1_h2c_set_pwrmode,
					       awake_पूर्णांकvl);
	SET_H2CCMD_PWRMODE_PARM_ALL_QUEUE_UAPSD(u1_h2c_set_pwrmode, 0);
	SET_H2CCMD_PWRMODE_PARM_PWR_STATE(u1_h2c_set_pwrmode, घातer_state);
	SET_H2CCMD_PWRMODE_PARM_BYTE5(u1_h2c_set_pwrmode, byte5);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
		      "rtl92c_set_fw_pwrmode(): u1_h2c_set_pwrmode\n",
		      u1_h2c_set_pwrmode, H2C_92E_PWEMODE_LENGTH);
	अगर (rtlpriv->cfg->ops->get_btc_status())
		btc_ops->btc_record_pwr_mode(rtlpriv, u1_h2c_set_pwrmode,
					     H2C_92E_PWEMODE_LENGTH);
	rtl92ee_fill_h2c_cmd(hw, H2C_92E_SETPWRMODE, H2C_92E_PWEMODE_LENGTH,
			     u1_h2c_set_pwrmode);
पूर्ण

व्योम rtl92ee_set_fw_media_status_rpt_cmd(काष्ठा ieee80211_hw *hw, u8 mstatus)
अणु
	u8 parm[3] = अणु 0 , 0 , 0 पूर्ण;
	/* parm[0]: bit0=0-->Disconnect, bit0=1-->Connect
	 *          bit1=0-->update Media Status to MACID
	 *          bit1=1-->update Media Status from MACID to MACID_End
	 * parm[1]: MACID, अगर this is INFRA_STA, MacID = 0
	 * parm[2]: MACID_End
	 */

	SET_H2CCMD_MSRRPT_PARM_OPMODE(parm, mstatus);
	SET_H2CCMD_MSRRPT_PARM_MACID_IND(parm, 0);

	rtl92ee_fill_h2c_cmd(hw, H2C_92E_MSRRPT, 3, parm);
पूर्ण

#घोषणा BEACON_PG		0 /* ->1 */
#घोषणा PSPOLL_PG		2
#घोषणा शून्य_PG			3
#घोषणा PROBERSP_PG		4 /* ->5 */
#घोषणा QOS_शून्य_PG		6
#घोषणा BT_QOS_शून्य_PG	7

#घोषणा TOTAL_RESERVED_PKT_LEN	1024

अटल u8 reserved_page_packet[TOTAL_RESERVED_PKT_LEN] = अणु
	/* page 0 beacon */
	0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xE0, 0x4C, 0x02, 0xB1, 0x78,
	0xEC, 0x1A, 0x59, 0x0B, 0xAD, 0xD4, 0x20, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x64, 0x00, 0x10, 0x04, 0x00, 0x05, 0x54, 0x65,
	0x73, 0x74, 0x32, 0x01, 0x08, 0x82, 0x84, 0x0B,
	0x16, 0x24, 0x30, 0x48, 0x6C, 0x03, 0x01, 0x06,
	0x06, 0x02, 0x00, 0x00, 0x2A, 0x01, 0x02, 0x32,
	0x04, 0x0C, 0x12, 0x18, 0x60, 0x2D, 0x1A, 0x6C,
	0x09, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3D, 0x00, 0xDD, 0x07, 0x00, 0xE0, 0x4C,
	0x02, 0x02, 0x00, 0x00, 0xDD, 0x18, 0x00, 0x50,
	0xF2, 0x01, 0x01, 0x00, 0x00, 0x50, 0xF2, 0x04,
	0x01, 0x00, 0x00, 0x50, 0xF2, 0x04, 0x01, 0x00,

	/* page 1 beacon */
	0x00, 0x50, 0xF2, 0x02, 0x00, 0x00, 0x00, 0x00,
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
	0x10, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 2  ps-poll */
	0xA4, 0x10, 0x01, 0xC0, 0xEC, 0x1A, 0x59, 0x0B,
	0xAD, 0xD4, 0x00, 0xE0, 0x4C, 0x02, 0xB1, 0x78,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x18, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 3  null */
	0x48, 0x01, 0x00, 0x00, 0xEC, 0x1A, 0x59, 0x0B,
	0xAD, 0xD4, 0x00, 0xE0, 0x4C, 0x02, 0xB1, 0x78,
	0xEC, 0x1A, 0x59, 0x0B, 0xAD, 0xD4, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x72, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

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
	0x1A, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 6 qos null data */
	0xC8, 0x01, 0x00, 0x00, 0x84, 0xC9, 0xB2, 0xA7,
	0xB3, 0x6E, 0x00, 0xE0, 0x4C, 0x02, 0x51, 0x02,
	0x84, 0xC9, 0xB2, 0xA7, 0xB3, 0x6E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1A, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 7 BT-qos null data */
	0xC8, 0x01, 0x00, 0x00, 0x84, 0xC9, 0xB2, 0xA7,
	0xB3, 0x6E, 0x00, 0xE0, 0x4C, 0x02, 0x51, 0x02,
	0x84, 0xC9, 0xB2, 0xA7, 0xB3, 0x6E, 0x00, 0x00,
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
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
पूर्ण;

व्योम rtl92ee_set_fw_rsvdpagepkt(काष्ठा ieee80211_hw *hw, bool b_dl_finished)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा sk_buff *skb = शून्य;
	bool rtstatus;
	u32 totalpacketlen;
	u8 u1rsvdpageloc[5] = अणु 0 पूर्ण;
	bool b_dlok = false;

	u8 *beacon;
	u8 *p_pspoll;
	u8 *nullfunc;
	u8 *p_probersp;
	u8 *qosnull;
	u8 *btqosnull;
	/*---------------------------------------------------------
	 *			(1) beacon
	 *---------------------------------------------------------
	 */
	beacon = &reserved_page_packet[BEACON_PG * 128];
	SET_80211_HDR_ADDRESS2(beacon, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(beacon, mac->bssid);

	/*-------------------------------------------------------
	 *			(2) ps-poll
	 *--------------------------------------------------------
	 */
	p_pspoll = &reserved_page_packet[PSPOLL_PG * 128];
	SET_80211_PS_POLL_AID(p_pspoll, (mac->assoc_id | 0xc000));
	SET_80211_PS_POLL_BSSID(p_pspoll, mac->bssid);
	SET_80211_PS_POLL_TA(p_pspoll, mac->mac_addr);

	SET_H2CCMD_RSVDPAGE_LOC_PSPOLL(u1rsvdpageloc, PSPOLL_PG);

	/*--------------------------------------------------------
	 *			(3) null data
	 *---------------------------------------------------------
	 */
	nullfunc = &reserved_page_packet[शून्य_PG * 128];
	SET_80211_HDR_ADDRESS1(nullfunc, mac->bssid);
	SET_80211_HDR_ADDRESS2(nullfunc, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(nullfunc, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_शून्य_DATA(u1rsvdpageloc, शून्य_PG);

	/*---------------------------------------------------------
	 *			(4) probe response
	 *----------------------------------------------------------
	 */
	p_probersp = &reserved_page_packet[PROBERSP_PG * 128];
	SET_80211_HDR_ADDRESS1(p_probersp, mac->bssid);
	SET_80211_HDR_ADDRESS2(p_probersp, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(p_probersp, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(u1rsvdpageloc, PROBERSP_PG);

	/*---------------------------------------------------------
	 *			(5) QoS null data
	 *----------------------------------------------------------
	 */
	qosnull = &reserved_page_packet[QOS_शून्य_PG * 128];
	SET_80211_HDR_ADDRESS1(qosnull, mac->bssid);
	SET_80211_HDR_ADDRESS2(qosnull, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(qosnull, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_QOS_शून्य_DATA(u1rsvdpageloc, QOS_शून्य_PG);

	/*---------------------------------------------------------
	 *			(6) BT QoS null data
	 *----------------------------------------------------------
	 */
	btqosnull = &reserved_page_packet[BT_QOS_शून्य_PG * 128];
	SET_80211_HDR_ADDRESS1(btqosnull, mac->bssid);
	SET_80211_HDR_ADDRESS2(btqosnull, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(btqosnull, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_BT_QOS_शून्य_DATA(u1rsvdpageloc, BT_QOS_शून्य_PG);

	totalpacketlen = TOTAL_RESERVED_PKT_LEN;

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD ,
		      "rtl92ee_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL\n",
		      &reserved_page_packet[0], totalpacketlen);
	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD ,
		      "rtl92ee_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL\n",
		      u1rsvdpageloc, 3);

	skb = dev_alloc_skb(totalpacketlen);
	अगर (!skb)
		वापस;
	skb_put_data(skb, &reserved_page_packet, totalpacketlen);

	rtstatus = rtl_cmd_send_packet(hw, skb);
	अगर (rtstatus)
		b_dlok = true;

	अगर (b_dlok) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Set RSVD page location to Fw.\n");
		RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD ,
			      "H2C_RSVDPAGE:\n", u1rsvdpageloc, 3);
		rtl92ee_fill_h2c_cmd(hw, H2C_92E_RSVDPAGE,
				     माप(u1rsvdpageloc), u1rsvdpageloc);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Set RSVD page location to Fw FAIL!!!!!!.\n");
	पूर्ण
पूर्ण

/*Shoud check FW support p2p or not.*/
अटल व्योम rtl92ee_set_p2p_ctw_period_cmd(काष्ठा ieee80211_hw *hw, u8 ctwinकरोw)
अणु
	u8 u1_ctwinकरोw_period[1] = अणुctwinकरोwपूर्ण;

	rtl92ee_fill_h2c_cmd(hw, H2C_92E_P2P_PS_CTW_CMD, 1, u1_ctwinकरोw_period);
पूर्ण

व्योम rtl92ee_set_p2p_ps_offload_cmd(काष्ठा ieee80211_hw *hw, u8 p2p_ps_state)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *rtlps = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_p2p_ps_info *p2pinfo = &rtlps->p2p_ps_info;
	काष्ठा p2p_ps_offload_t *p2p_ps_offload = &rtlhal->p2p_ps_offload;
	u8 i;
	u16 ctwinकरोw;
	u32 start_समय, tsf_low;

	चयन (p2p_ps_state) अणु
	हाल P2P_PS_DISABLE:
		rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_DISABLE\n");
		स_रखो(p2p_ps_offload, 0, माप(*p2p_ps_offload));
		अवरोध;
	हाल P2P_PS_ENABLE:
		rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_ENABLE\n");
		/* update CTWinकरोw value. */
		अगर (p2pinfo->ctwinकरोw > 0) अणु
			p2p_ps_offload->ctwinकरोw_en = 1;
			ctwinकरोw = p2pinfo->ctwinकरोw;
			rtl92ee_set_p2p_ctw_period_cmd(hw, ctwinकरोw);
		पूर्ण
		/* hw only support 2 set of NoA */
		क्रम (i = 0 ; i < p2pinfo->noa_num ; i++) अणु
			/* To control the रेजिस्टर setting क्रम which NOA*/
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
				जबतक (start_समय <= (tsf_low + (50 * 1024))) अणु
					start_समय += p2pinfo->noa_पूर्णांकerval[i];
					अगर (p2pinfo->noa_count_type[i] != 255)
						p2pinfo->noa_count_type[i]--;
				पूर्ण
			पूर्ण
			rtl_ग_लिखो_dword(rtlpriv, 0x5E8, start_समय);
			rtl_ग_लिखो_dword(rtlpriv, 0x5EC,
					p2pinfo->noa_count_type[i]);
		पूर्ण
		अगर ((p2pinfo->opp_ps == 1) || (p2pinfo->noa_num > 0)) अणु
			/* rst p2p circuit */
			rtl_ग_लिखो_byte(rtlpriv, REG_DUAL_TSF_RST, BIT(4));
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
		rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_SCAN_DONE\n");
		p2p_ps_offload->discovery = 0;
		p2pinfo->p2p_ps_state = P2P_PS_ENABLE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rtl92ee_fill_h2c_cmd(hw, H2C_92E_P2P_PS_OFFLOAD, 1,
			     (u8 *)p2p_ps_offload);
पूर्ण

व्योम rtl92ee_c2h_ra_report_handler(काष्ठा ieee80211_hw *hw,
				   u8 *cmd_buf, u8 cmd_len)
अणु
	u8 rate = cmd_buf[0] & 0x3F;
	bool collision_state = cmd_buf[3] & BIT(0);

	rtl92ee_dm_dynamic_arfb_select(hw, rate, collision_state);
पूर्ण
