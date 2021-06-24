<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../ps.h"
#समावेश "../core.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "fw.h"
#समावेश "hw.h"
#समावेश "table.h"

अटल u32 _rtl92s_phy_calculate_bit_shअगरt(u32 biपंचांगask)
अणु
	u32 i = ffs(biपंचांगask);

	वापस i ? i - 1 : 32;
पूर्ण

u32 rtl92s_phy_query_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 वापसvalue = 0, originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE, "regaddr(%#x), bitmask(%#x)\n",
		regaddr, biपंचांगask);

	originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
	bitshअगरt = _rtl92s_phy_calculate_bit_shअगरt(biपंचांगask);
	वापसvalue = (originalvalue & biपंचांगask) >> bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE, "BBR MASK=0x%x Addr[0x%x]=0x%x\n",
		biपंचांगask, regaddr, originalvalue);

	वापस वापसvalue;

पूर्ण

व्योम rtl92s_phy_set_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask,
			   u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);

	अगर (biपंचांगask != MASKDWORD) अणु
		originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
		bitshअगरt = _rtl92s_phy_calculate_bit_shअगरt(biपंचांगask);
		data = ((originalvalue & (~biपंचांगask)) | (data << bitshअगरt));
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, regaddr, data);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);

पूर्ण

अटल u32 _rtl92s_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
				      क्रमागत radio_path rfpath, u32 offset)
अणु

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];
	u32 newoffset;
	u32 पंचांगpदीर्घ, पंचांगpदीर्घ2;
	u8 rfpi_enable = 0;
	u32 retvalue = 0;

	offset &= 0x3f;
	newoffset = offset;

	पंचांगpदीर्घ = rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, MASKDWORD);

	अगर (rfpath == RF90_PATH_A)
		पंचांगpदीर्घ2 = पंचांगpदीर्घ;
	अन्यथा
		पंचांगpदीर्घ2 = rtl_get_bbreg(hw, pphyreg->rfhssi_para2, MASKDWORD);

	पंचांगpदीर्घ2 = (पंचांगpदीर्घ2 & (~BLSSI_READADDRESS)) | (newoffset << 23) |
			BLSSI_READEDGE;

	rtl_set_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, MASKDWORD,
		      पंचांगpदीर्घ & (~BLSSI_READEDGE));

	mdelay(1);

	rtl_set_bbreg(hw, pphyreg->rfhssi_para2, MASKDWORD, पंचांगpदीर्घ2);
	mdelay(1);

	rtl_set_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, MASKDWORD, पंचांगpदीर्घ |
		      BLSSI_READEDGE);
	mdelay(1);

	अगर (rfpath == RF90_PATH_A)
		rfpi_enable = (u8)rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER1,
						BIT(8));
	अन्यथा अगर (rfpath == RF90_PATH_B)
		rfpi_enable = (u8)rtl_get_bbreg(hw, RFPGA0_XB_HSSIPARAMETER1,
						BIT(8));

	अगर (rfpi_enable)
		retvalue = rtl_get_bbreg(hw, pphyreg->rf_rbpi,
					 BLSSI_READBACK_DATA);
	अन्यथा
		retvalue = rtl_get_bbreg(hw, pphyreg->rf_rb,
					 BLSSI_READBACK_DATA);

	retvalue = rtl_get_bbreg(hw, pphyreg->rf_rb,
				 BLSSI_READBACK_DATA);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE, "RFR-%d Addr[0x%x]=0x%x\n",
		rfpath, pphyreg->rf_rb, retvalue);

	वापस retvalue;

पूर्ण

अटल व्योम _rtl92s_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
					क्रमागत radio_path rfpath, u32 offset,
					u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];
	u32 data_and_addr = 0;
	u32 newoffset;

	offset &= 0x3f;
	newoffset = offset;

	data_and_addr = ((newoffset << 20) | (data & 0x000fffff)) & 0x0fffffff;
	rtl_set_bbreg(hw, pphyreg->rf3wire_offset, MASKDWORD, data_and_addr);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE, "RFW-%d Addr[0x%x]=0x%x\n",
		rfpath, pphyreg->rf3wire_offset, data_and_addr);
पूर्ण


u32 rtl92s_phy_query_rf_reg(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
			    u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, पढ़ोback_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x)\n",
		 regaddr, rfpath, biपंचांगask);

	spin_lock(&rtlpriv->locks.rf_lock);

	original_value = _rtl92s_phy_rf_serial_पढ़ो(hw, rfpath, regaddr);

	bitshअगरt = _rtl92s_phy_calculate_bit_shअगरt(biपंचांगask);
	पढ़ोback_value = (original_value & biपंचांगask) >> bitshअगरt;

	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x), original_value(%#x)\n",
		regaddr, rfpath, biपंचांगask, original_value);

	वापस पढ़ोback_value;
पूर्ण

व्योम rtl92s_phy_set_rf_reg(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
			   u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 original_value, bitshअगरt;

	अगर (!((rtlphy->rf_pathmap >> rfpath) & 0x1))
		वापस;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, rfpath);

	spin_lock(&rtlpriv->locks.rf_lock);

	अगर (biपंचांगask != RFREG_OFFSET_MASK) अणु
		original_value = _rtl92s_phy_rf_serial_पढ़ो(hw, rfpath,
							    regaddr);
		bitshअगरt = _rtl92s_phy_calculate_bit_shअगरt(biपंचांगask);
		data = ((original_value & (~biपंचांगask)) | (data << bitshअगरt));
	पूर्ण

	_rtl92s_phy_rf_serial_ग_लिखो(hw, rfpath, regaddr, data);

	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, rfpath);

पूर्ण

व्योम rtl92s_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw,
				      u8 operation)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (!is_hal_stop(rtlhal)) अणु
		चयन (operation) अणु
		हाल SCAN_OPT_BACKUP:
			rtl92s_phy_set_fw_cmd(hw, FW_CMD_PAUSE_DM_BY_SCAN);
			अवरोध;
		हाल SCAN_OPT_RESTORE:
			rtl92s_phy_set_fw_cmd(hw, FW_CMD_RESUME_DM_BY_SCAN);
			अवरोध;
		शेष:
			pr_err("Unknown operation\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92s_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
			    क्रमागत nl80211_channel_type ch_type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 reg_bw_opmode;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "Switch to %s bandwidth\n",
		rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20 ?
		"20MHz" : "40MHz");

	अगर (rtlphy->set_bwmode_inprogress)
		वापस;
	अगर (is_hal_stop(rtlhal))
		वापस;

	rtlphy->set_bwmode_inprogress = true;

	reg_bw_opmode = rtl_पढ़ो_byte(rtlpriv, BW_OPMODE);
	/* dummy पढ़ो */
	rtl_पढ़ो_byte(rtlpriv, RRSR + 2);

	चयन (rtlphy->current_chan_bw) अणु
	हाल HT_CHANNEL_WIDTH_20:
		reg_bw_opmode |= BW_OPMODE_20MHZ;
		rtl_ग_लिखो_byte(rtlpriv, BW_OPMODE, reg_bw_opmode);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		reg_bw_opmode &= ~BW_OPMODE_20MHZ;
		rtl_ग_लिखो_byte(rtlpriv, BW_OPMODE, reg_bw_opmode);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		अवरोध;
	पूर्ण

	चयन (rtlphy->current_chan_bw) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x0);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x0);

		अगर (rtlhal->version >= VERSION_8192S_BCUT)
			rtl_ग_लिखो_byte(rtlpriv, RFPGA0_ANALOGPARAMETER2, 0x58);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x1);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x1);

		rtl_set_bbreg(hw, RCCK0_SYSTEM, BCCK_SIDEBAND,
				(mac->cur_40_prime_sc >> 1));
		rtl_set_bbreg(hw, ROFDM1_LSTF, 0xC00, mac->cur_40_prime_sc);

		अगर (rtlhal->version >= VERSION_8192S_BCUT)
			rtl_ग_लिखो_byte(rtlpriv, RFPGA0_ANALOGPARAMETER2, 0x18);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		अवरोध;
	पूर्ण

	rtl92s_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "<==\n");
पूर्ण

अटल bool _rtl92s_phy_set_sw_chnl_cmdarray(काष्ठा swchnlcmd *cmdtable,
		u32 cmdtableidx, u32 cmdtablesz, क्रमागत swchnlcmd_id cmdid,
		u32 para1, u32 para2, u32 msdelay)
अणु
	काष्ठा swchnlcmd *pcmd;

	अगर (cmdtable == शून्य) अणु
		WARN_ONCE(true, "rtl8192se: cmdtable cannot be NULL\n");
		वापस false;
	पूर्ण

	अगर (cmdtableidx >= cmdtablesz)
		वापस false;

	pcmd = cmdtable + cmdtableidx;
	pcmd->cmdid = cmdid;
	pcmd->para1 = para1;
	pcmd->para2 = para2;
	pcmd->msdelay = msdelay;

	वापस true;
पूर्ण

अटल bool _rtl92s_phy_sw_chnl_step_by_step(काष्ठा ieee80211_hw *hw,
	     u8 channel, u8 *stage, u8 *step, u32 *delay)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा swchnlcmd precommoncmd[MAX_PRECMD_CNT];
	u32 precommoncmdcnt;
	काष्ठा swchnlcmd postcommoncmd[MAX_POSTCMD_CNT];
	u32 postcommoncmdcnt;
	काष्ठा swchnlcmd rfdependcmd[MAX_RFDEPENDCMD_CNT];
	u32 rfdependcmdcnt;
	काष्ठा swchnlcmd *currentcmd = शून्य;
	u8 rfpath;
	u8 num_total_rfpath = rtlphy->num_total_rfpath;

	precommoncmdcnt = 0;
	_rtl92s_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
			MAX_PRECMD_CNT, CMDID_SET_TXPOWEROWER_LEVEL, 0, 0, 0);
	_rtl92s_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
			MAX_PRECMD_CNT, CMDID_END, 0, 0, 0);

	postcommoncmdcnt = 0;

	_rtl92s_phy_set_sw_chnl_cmdarray(postcommoncmd, postcommoncmdcnt++,
			MAX_POSTCMD_CNT, CMDID_END, 0, 0, 0);

	rfdependcmdcnt = 0;

	WARN_ONCE((channel < 1 || channel > 14),
		  "rtl8192se: invalid channel for Zebra: %d\n", channel);

	_rtl92s_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					 MAX_RFDEPENDCMD_CNT, CMDID_RF_WRITEREG,
					 RF_CHNLBW, channel, 10);

	_rtl92s_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
			MAX_RFDEPENDCMD_CNT, CMDID_END, 0, 0, 0);

	करो अणु
		चयन (*stage) अणु
		हाल 0:
			currentcmd = &precommoncmd[*step];
			अवरोध;
		हाल 1:
			currentcmd = &rfdependcmd[*step];
			अवरोध;
		हाल 2:
			currentcmd = &postcommoncmd[*step];
			अवरोध;
		शेष:
			वापस true;
		पूर्ण

		अगर (currentcmd->cmdid == CMDID_END) अणु
			अगर ((*stage) == 2) अणु
				वापस true;
			पूर्ण अन्यथा अणु
				(*stage)++;
				(*step) = 0;
				जारी;
			पूर्ण
		पूर्ण

		चयन (currentcmd->cmdid) अणु
		हाल CMDID_SET_TXPOWEROWER_LEVEL:
			rtl92s_phy_set_txघातer(hw, channel);
			अवरोध;
		हाल CMDID_WRITEPORT_ULONG:
			rtl_ग_लिखो_dword(rtlpriv, currentcmd->para1,
					currentcmd->para2);
			अवरोध;
		हाल CMDID_WRITEPORT_USHORT:
			rtl_ग_लिखो_word(rtlpriv, currentcmd->para1,
				       (u16)currentcmd->para2);
			अवरोध;
		हाल CMDID_WRITEPORT_UCHAR:
			rtl_ग_लिखो_byte(rtlpriv, currentcmd->para1,
				       (u8)currentcmd->para2);
			अवरोध;
		हाल CMDID_RF_WRITEREG:
			क्रम (rfpath = 0; rfpath < num_total_rfpath; rfpath++) अणु
				rtlphy->rfreg_chnlval[rfpath] =
					 ((rtlphy->rfreg_chnlval[rfpath] &
					 0xfffffc00) | currentcmd->para2);
				rtl_set_rfreg(hw, (क्रमागत radio_path)rfpath,
					      currentcmd->para1,
					      RFREG_OFFSET_MASK,
					      rtlphy->rfreg_chnlval[rfpath]);
			पूर्ण
			अवरोध;
		शेष:
			pr_err("switch case %#x not processed\n",
			       currentcmd->cmdid);
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण जबतक (true);

	(*delay) = currentcmd->msdelay;
	(*step)++;
	वापस false;
पूर्ण

u8 rtl92s_phy_sw_chnl(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 delay;
	bool ret;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "switch to channel%d\n",
		rtlphy->current_channel);

	अगर (rtlphy->sw_chnl_inprogress)
		वापस 0;

	अगर (rtlphy->set_bwmode_inprogress)
		वापस 0;

	अगर (is_hal_stop(rtlhal))
		वापस 0;

	rtlphy->sw_chnl_inprogress = true;
	rtlphy->sw_chnl_stage = 0;
	rtlphy->sw_chnl_step = 0;

	करो अणु
		अगर (!rtlphy->sw_chnl_inprogress)
			अवरोध;

		ret = _rtl92s_phy_sw_chnl_step_by_step(hw,
				 rtlphy->current_channel,
				 &rtlphy->sw_chnl_stage,
				 &rtlphy->sw_chnl_step, &delay);
		अगर (!ret) अणु
			अगर (delay > 0)
				mdelay(delay);
			अन्यथा
				जारी;
		पूर्ण अन्यथा अणु
			rtlphy->sw_chnl_inprogress = false;
		पूर्ण
		अवरोध;
	पूर्ण जबतक (true);

	rtlphy->sw_chnl_inprogress = false;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "<==\n");

	वापस 1;
पूर्ण

अटल व्योम _rtl92se_phy_set_rf_sleep(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1bपंचांगp;

	u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, LDOV12D_CTRL);
	u1bपंचांगp |= BIT(0);

	rtl_ग_लिखो_byte(rtlpriv, LDOV12D_CTRL, u1bपंचांगp);
	rtl_ग_लिखो_byte(rtlpriv, SPS1_CTRL, 0x0);
	rtl_ग_लिखो_byte(rtlpriv, TXPAUSE, 0xFF);
	rtl_ग_लिखो_word(rtlpriv, CMDR, 0x57FC);
	udelay(100);

	rtl_ग_लिखो_word(rtlpriv, CMDR, 0x77FC);
	rtl_ग_लिखो_byte(rtlpriv, PHY_CCA, 0x0);
	udelay(10);

	rtl_ग_लिखो_word(rtlpriv, CMDR, 0x37FC);
	udelay(10);

	rtl_ग_लिखो_word(rtlpriv, CMDR, 0x77FC);
	udelay(10);

	rtl_ग_लिखो_word(rtlpriv, CMDR, 0x57FC);

	/* we should chnge GPIO to input mode
	 * this will drop away current about 25mA*/
	rtl8192se_gpiobit3_cfg_inpuपंचांगode(hw);
पूर्ण

bool rtl92s_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				   क्रमागत rf_pwrstate rfpwr_state)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool bresult = true;
	u8 i, queue_id;
	काष्ठा rtl8192_tx_ring *ring = शून्य;

	अगर (rfpwr_state == ppsc->rfpwr_state)
		वापस false;

	चयन (rfpwr_state) अणु
	हाल ERFON:अणु
			अगर ((ppsc->rfpwr_state == ERFOFF) &&
			    RT_IN_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC)) अणु

				bool rtstatus;
				u32 initializecount = 0;
				करो अणु
					initializecount++;
					rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
						"IPS Set eRf nic enable\n");
					rtstatus = rtl_ps_enable_nic(hw);
				पूर्ण जबतक (!rtstatus && (initializecount < 10));

				RT_CLEAR_PS_LEVEL(ppsc,
						  RT_RF_OFF_LEVL_HALT_NIC);
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
					"awake, slept:%d ms state_inap:%x\n",
					jअगरfies_to_msecs(jअगरfies -
					ppsc->last_sleep_jअगरfies),
					rtlpriv->psc.state_inap);
				ppsc->last_awake_jअगरfies = jअगरfies;
				rtl_ग_लिखो_word(rtlpriv, CMDR, 0x37FC);
				rtl_ग_लिखो_byte(rtlpriv, TXPAUSE, 0x00);
				rtl_ग_लिखो_byte(rtlpriv, PHY_CCA, 0x3);
			पूर्ण

			अगर (mac->link_state == MAC80211_LINKED)
				rtlpriv->cfg->ops->led_control(hw,
							 LED_CTL_LINK);
			अन्यथा
				rtlpriv->cfg->ops->led_control(hw,
							 LED_CTL_NO_LINK);
			अवरोध;
		पूर्ण
	हाल ERFOFF:अणु
			अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC) अणु
				rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
					"IPS Set eRf nic disable\n");
				rtl_ps_disable_nic(hw);
				RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
			पूर्ण अन्यथा अणु
				अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
					rtlpriv->cfg->ops->led_control(hw,
							 LED_CTL_NO_LINK);
				अन्यथा
					rtlpriv->cfg->ops->led_control(hw,
							 LED_CTL_POWER_OFF);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल ERFSLEEP:
			अगर (ppsc->rfpwr_state == ERFOFF)
				वापस false;

			क्रम (queue_id = 0, i = 0;
			     queue_id < RTL_PCI_MAX_TX_QUEUE_COUNT;) अणु
				ring = &pcipriv->dev.tx_ring[queue_id];
				अगर (skb_queue_len(&ring->queue) == 0 ||
					queue_id == BEACON_QUEUE) अणु
					queue_id++;
					जारी;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
						"eRf Off/Sleep: %d times TcbBusyQueue[%d] = %d before doze!\n",
						i + 1, queue_id,
						skb_queue_len(&ring->queue));

					udelay(10);
					i++;
				पूर्ण

				अगर (i >= MAX_DOZE_WAITING_TIMES_9x) अणु
					rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
						"ERFOFF: %d times TcbBusyQueue[%d] = %d !\n",
						MAX_DOZE_WAITING_TIMES_9x,
						queue_id,
						skb_queue_len(&ring->queue));
					अवरोध;
				पूर्ण
			पूर्ण

			rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
				"Set ERFSLEEP awaked:%d ms\n",
				jअगरfies_to_msecs(jअगरfies -
						 ppsc->last_awake_jअगरfies));

			rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
				"sleep awaked:%d ms state_inap:%x\n",
				jअगरfies_to_msecs(jअगरfies -
						 ppsc->last_awake_jअगरfies),
				 rtlpriv->psc.state_inap);
			ppsc->last_sleep_jअगरfies = jअगरfies;
			_rtl92se_phy_set_rf_sleep(hw);
			अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n",
		       rfpwr_state);
		bresult = false;
		अवरोध;
	पूर्ण

	अगर (bresult)
		ppsc->rfpwr_state = rfpwr_state;

	वापस bresult;
पूर्ण

अटल bool _rtl92s_phy_config_rfpa_bias_current(काष्ठा ieee80211_hw *hw,
						 क्रमागत radio_path rfpath)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool rtstatus = true;
	u32 पंचांगpval = 0;

	/* If inferiority IC, we have to increase the PA bias current */
	अगर (rtlhal->ic_class != IC_INFERIORITY_A) अणु
		पंचांगpval = rtl92s_phy_query_rf_reg(hw, rfpath, RF_IPA, 0xf);
		rtl92s_phy_set_rf_reg(hw, rfpath, RF_IPA, 0xf, पंचांगpval + 1);
	पूर्ण

	वापस rtstatus;
पूर्ण

अटल व्योम _rtl92s_store_pwrindex_dअगरfrate_offset(काष्ठा ieee80211_hw *hw,
		u32 reg_addr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	पूर्णांक index;

	अगर (reg_addr == RTXAGC_RATE18_06)
		index = 0;
	अन्यथा अगर (reg_addr == RTXAGC_RATE54_24)
		index = 1;
	अन्यथा अगर (reg_addr == RTXAGC_CCK_MCS32)
		index = 6;
	अन्यथा अगर (reg_addr == RTXAGC_MCS03_MCS00)
		index = 2;
	अन्यथा अगर (reg_addr == RTXAGC_MCS07_MCS04)
		index = 3;
	अन्यथा अगर (reg_addr == RTXAGC_MCS11_MCS08)
		index = 4;
	अन्यथा अगर (reg_addr == RTXAGC_MCS15_MCS12)
		index = 5;
	अन्यथा
		वापस;

	rtlphy->mcs_offset[rtlphy->pwrgroup_cnt][index] = data;
	अगर (index == 5)
		rtlphy->pwrgroup_cnt++;
पूर्ण

अटल व्योम _rtl92s_phy_init_रेजिस्टर_definition(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	/*RF Interface Sowrtware Control */
	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;
	rtlphy->phyreg_def[RF90_PATH_C].rfपूर्णांकfs = RFPGA0_XCD_RFINTERFACESW;
	rtlphy->phyreg_def[RF90_PATH_D].rfपूर्णांकfs = RFPGA0_XCD_RFINTERFACESW;

	/* RF Interface Readback Value */
	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfi = RFPGA0_XAB_RFINTERFACERB;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfi = RFPGA0_XAB_RFINTERFACERB;
	rtlphy->phyreg_def[RF90_PATH_C].rfपूर्णांकfi = RFPGA0_XCD_RFINTERFACERB;
	rtlphy->phyreg_def[RF90_PATH_D].rfपूर्णांकfi = RFPGA0_XCD_RFINTERFACERB;

	/* RF Interface Output (and Enable) */
	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfo = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfo = RFPGA0_XB_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_C].rfपूर्णांकfo = RFPGA0_XC_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_D].rfपूर्णांकfo = RFPGA0_XD_RFINTERFACEOE;

	/* RF Interface (Output and)  Enable */
	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfe = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfe = RFPGA0_XB_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_C].rfपूर्णांकfe = RFPGA0_XC_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_D].rfपूर्णांकfe = RFPGA0_XD_RFINTERFACEOE;

	/* Addr of LSSI. Wirte RF रेजिस्टर by driver */
	rtlphy->phyreg_def[RF90_PATH_A].rf3wire_offset =
						 RFPGA0_XA_LSSIPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_B].rf3wire_offset =
						 RFPGA0_XB_LSSIPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_C].rf3wire_offset =
						 RFPGA0_XC_LSSIPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_D].rf3wire_offset =
						 RFPGA0_XD_LSSIPARAMETER;

	/* RF parameter */
	rtlphy->phyreg_def[RF90_PATH_A].rflssi_select = RFPGA0_XAB_RFPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_B].rflssi_select = RFPGA0_XAB_RFPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_C].rflssi_select = RFPGA0_XCD_RFPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_D].rflssi_select = RFPGA0_XCD_RFPARAMETER;

	/* Tx AGC Gain Stage (same क्रम all path. Should we हटाओ this?) */
	rtlphy->phyreg_def[RF90_PATH_A].rftxgain_stage = RFPGA0_TXGAINSTAGE;
	rtlphy->phyreg_def[RF90_PATH_B].rftxgain_stage = RFPGA0_TXGAINSTAGE;
	rtlphy->phyreg_def[RF90_PATH_C].rftxgain_stage = RFPGA0_TXGAINSTAGE;
	rtlphy->phyreg_def[RF90_PATH_D].rftxgain_stage = RFPGA0_TXGAINSTAGE;

	/* Tranceiver A~D HSSI Parameter-1 */
	rtlphy->phyreg_def[RF90_PATH_A].rfhssi_para1 = RFPGA0_XA_HSSIPARAMETER1;
	rtlphy->phyreg_def[RF90_PATH_B].rfhssi_para1 = RFPGA0_XB_HSSIPARAMETER1;
	rtlphy->phyreg_def[RF90_PATH_C].rfhssi_para1 = RFPGA0_XC_HSSIPARAMETER1;
	rtlphy->phyreg_def[RF90_PATH_D].rfhssi_para1 = RFPGA0_XD_HSSIPARAMETER1;

	/* Tranceiver A~D HSSI Parameter-2 */
	rtlphy->phyreg_def[RF90_PATH_A].rfhssi_para2 = RFPGA0_XA_HSSIPARAMETER2;
	rtlphy->phyreg_def[RF90_PATH_B].rfhssi_para2 = RFPGA0_XB_HSSIPARAMETER2;
	rtlphy->phyreg_def[RF90_PATH_C].rfhssi_para2 = RFPGA0_XC_HSSIPARAMETER2;
	rtlphy->phyreg_def[RF90_PATH_D].rfhssi_para2 = RFPGA0_XD_HSSIPARAMETER2;

	/* RF चयन Control */
	rtlphy->phyreg_def[RF90_PATH_A].rfsw_ctrl = RFPGA0_XAB_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_B].rfsw_ctrl = RFPGA0_XAB_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_C].rfsw_ctrl = RFPGA0_XCD_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_D].rfsw_ctrl = RFPGA0_XCD_SWITCHCONTROL;

	/* AGC control 1  */
	rtlphy->phyreg_def[RF90_PATH_A].rfagc_control1 = ROFDM0_XAAGCCORE1;
	rtlphy->phyreg_def[RF90_PATH_B].rfagc_control1 = ROFDM0_XBAGCCORE1;
	rtlphy->phyreg_def[RF90_PATH_C].rfagc_control1 = ROFDM0_XCAGCCORE1;
	rtlphy->phyreg_def[RF90_PATH_D].rfagc_control1 = ROFDM0_XDAGCCORE1;

	/* AGC control 2  */
	rtlphy->phyreg_def[RF90_PATH_A].rfagc_control2 = ROFDM0_XAAGCCORE2;
	rtlphy->phyreg_def[RF90_PATH_B].rfagc_control2 = ROFDM0_XBAGCCORE2;
	rtlphy->phyreg_def[RF90_PATH_C].rfagc_control2 = ROFDM0_XCAGCCORE2;
	rtlphy->phyreg_def[RF90_PATH_D].rfagc_control2 = ROFDM0_XDAGCCORE2;

	/* RX AFE control 1  */
	rtlphy->phyreg_def[RF90_PATH_A].rfrxiq_imbal = ROFDM0_XARXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_B].rfrxiq_imbal = ROFDM0_XBRXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_C].rfrxiq_imbal = ROFDM0_XCRXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_D].rfrxiq_imbal = ROFDM0_XDRXIQIMBALANCE;

	/* RX AFE control 1   */
	rtlphy->phyreg_def[RF90_PATH_A].rfrx_afe = ROFDM0_XARXAFE;
	rtlphy->phyreg_def[RF90_PATH_B].rfrx_afe = ROFDM0_XBRXAFE;
	rtlphy->phyreg_def[RF90_PATH_C].rfrx_afe = ROFDM0_XCRXAFE;
	rtlphy->phyreg_def[RF90_PATH_D].rfrx_afe = ROFDM0_XDRXAFE;

	/* Tx AFE control 1  */
	rtlphy->phyreg_def[RF90_PATH_A].rftxiq_imbal = ROFDM0_XATXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_B].rftxiq_imbal = ROFDM0_XBTXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_C].rftxiq_imbal = ROFDM0_XCTXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_D].rftxiq_imbal = ROFDM0_XDTXIQIMBALANCE;

	/* Tx AFE control 2  */
	rtlphy->phyreg_def[RF90_PATH_A].rftx_afe = ROFDM0_XATXAFE;
	rtlphy->phyreg_def[RF90_PATH_B].rftx_afe = ROFDM0_XBTXAFE;
	rtlphy->phyreg_def[RF90_PATH_C].rftx_afe = ROFDM0_XCTXAFE;
	rtlphy->phyreg_def[RF90_PATH_D].rftx_afe = ROFDM0_XDTXAFE;

	/* Tranceiver LSSI Readback */
	rtlphy->phyreg_def[RF90_PATH_A].rf_rb = RFPGA0_XA_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rb = RFPGA0_XB_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_C].rf_rb = RFPGA0_XC_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_D].rf_rb = RFPGA0_XD_LSSIREADBACK;

	/* Tranceiver LSSI Readback PI mode  */
	rtlphy->phyreg_def[RF90_PATH_A].rf_rbpi = TRANSCEIVERA_HSPI_READBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rbpi = TRANSCEIVERB_HSPI_READBACK;
पूर्ण


अटल bool _rtl92s_phy_config_bb(काष्ठा ieee80211_hw *hw, u8 configtype)
अणु
	पूर्णांक i;
	u32 *phy_reg_table;
	u32 *agc_table;
	u16 phy_reg_len, agc_len;

	agc_len = AGCTAB_ARRAYLENGTH;
	agc_table = rtl8192seagctab_array;
	/* Default RF_type: 2T2R */
	phy_reg_len = PHY_REG_2T2RARRAYLENGTH;
	phy_reg_table = rtl8192sephy_reg_2t2rarray;

	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_reg_len; i = i + 2) अणु
			rtl_addr_delay(phy_reg_table[i]);

			/* Add delay क्रम ECS T20 & LG malow platक्रमm, */
			udelay(1);

			rtl92s_phy_set_bb_reg(hw, phy_reg_table[i], MASKDWORD,
					phy_reg_table[i + 1]);
		पूर्ण
	पूर्ण अन्यथा अगर (configtype == BASEBAND_CONFIG_AGC_TAB) अणु
		क्रम (i = 0; i < agc_len; i = i + 2) अणु
			rtl92s_phy_set_bb_reg(hw, agc_table[i], MASKDWORD,
					agc_table[i + 1]);

			/* Add delay क्रम ECS T20 & LG malow platक्रमm */
			udelay(1);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool _rtl92s_phy_set_bb_to_dअगरf_rf(काष्ठा ieee80211_hw *hw,
					  u8 configtype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 *phy_regarray2xtxr_table;
	u16 phy_regarray2xtxr_len;
	पूर्णांक i;

	अगर (rtlphy->rf_type == RF_1T1R) अणु
		phy_regarray2xtxr_table = rtl8192sephy_changeto_1t1rarray;
		phy_regarray2xtxr_len = PHY_CHANGETO_1T1RARRAYLENGTH;
	पूर्ण अन्यथा अगर (rtlphy->rf_type == RF_1T2R) अणु
		phy_regarray2xtxr_table = rtl8192sephy_changeto_1t2rarray;
		phy_regarray2xtxr_len = PHY_CHANGETO_1T2RARRAYLENGTH;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_regarray2xtxr_len; i = i + 3) अणु
			rtl_addr_delay(phy_regarray2xtxr_table[i]);

			rtl92s_phy_set_bb_reg(hw, phy_regarray2xtxr_table[i],
				phy_regarray2xtxr_table[i + 1],
				phy_regarray2xtxr_table[i + 2]);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool _rtl92s_phy_config_bb_with_pg(काष्ठा ieee80211_hw *hw,
					  u8 configtype)
अणु
	पूर्णांक i;
	u32 *phy_table_pg;
	u16 phy_pg_len;

	phy_pg_len = PHY_REG_ARRAY_PGLENGTH;
	phy_table_pg = rtl8192sephy_reg_array_pg;

	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_pg_len; i = i + 3) अणु
			rtl_addr_delay(phy_table_pg[i]);

			_rtl92s_store_pwrindex_dअगरfrate_offset(hw,
					phy_table_pg[i],
					phy_table_pg[i + 1],
					phy_table_pg[i + 2]);
			rtl92s_phy_set_bb_reg(hw, phy_table_pg[i],
					phy_table_pg[i + 1],
					phy_table_pg[i + 2]);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool _rtl92s_phy_bb_config_parafile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	bool rtstatus = true;

	/* 1. Read PHY_REG.TXT BB INIT!! */
	/* We will separate as 1T1R/1T2R/1T2R_GREEN/2T2R */
	अगर (rtlphy->rf_type == RF_1T2R || rtlphy->rf_type == RF_2T2R ||
	    rtlphy->rf_type == RF_1T1R || rtlphy->rf_type == RF_2T2R_GREEN) अणु
		rtstatus = _rtl92s_phy_config_bb(hw, BASEBAND_CONFIG_PHY_REG);

		अगर (rtlphy->rf_type != RF_2T2R &&
		    rtlphy->rf_type != RF_2T2R_GREEN)
			/* so we should reconfig BB reg with the right
			 * PHY parameters. */
			rtstatus = _rtl92s_phy_set_bb_to_dअगरf_rf(hw,
						BASEBAND_CONFIG_PHY_REG);
	पूर्ण अन्यथा अणु
		rtstatus = false;
	पूर्ण

	अगर (!rtstatus) अणु
		pr_err("Write BB Reg Fail!!\n");
		जाओ phy_bb8190_config_parafile_fail;
	पूर्ण

	/* 2. If EEPROM or EFUSE स्वतःload OK, We must config by
	 *    PHY_REG_PG.txt */
	अगर (rtlefuse->स्वतःload_failflag == false) अणु
		rtlphy->pwrgroup_cnt = 0;

		rtstatus = _rtl92s_phy_config_bb_with_pg(hw,
						 BASEBAND_CONFIG_PHY_REG);
	पूर्ण
	अगर (!rtstatus) अणु
		pr_err("_rtl92s_phy_bb_config_parafile(): BB_PG Reg Fail!!\n");
		जाओ phy_bb8190_config_parafile_fail;
	पूर्ण

	/* 3. BB AGC table Initialization */
	rtstatus = _rtl92s_phy_config_bb(hw, BASEBAND_CONFIG_AGC_TAB);

	अगर (!rtstatus) अणु
		pr_err("%s(): AGC Table Fail\n", __func__);
		जाओ phy_bb8190_config_parafile_fail;
	पूर्ण

	/* Check अगर the CCK HighPower is turned ON. */
	/* This is used to calculate PWDB. */
	rtlphy->cck_high_घातer = (bool)(rtl92s_phy_query_bb_reg(hw,
			RFPGA0_XA_HSSIPARAMETER2, 0x200));

phy_bb8190_config_parafile_fail:
	वापस rtstatus;
पूर्ण

u8 rtl92s_phy_config_rf(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	पूर्णांक i;
	bool rtstatus = true;
	u32 *radio_a_table;
	u32 *radio_b_table;
	u16 radio_a_tblen, radio_b_tblen;

	radio_a_tblen = RADIOA_1T_ARRAYLENGTH;
	radio_a_table = rtl8192seradioa_1t_array;

	/* Using Green mode array table क्रम RF_2T2R_GREEN */
	अगर (rtlphy->rf_type == RF_2T2R_GREEN) अणु
		radio_b_table = rtl8192seradiob_gm_array;
		radio_b_tblen = RADIOB_GM_ARRAYLENGTH;
	पूर्ण अन्यथा अणु
		radio_b_table = rtl8192seradiob_array;
		radio_b_tblen = RADIOB_ARRAYLENGTH;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
	rtstatus = true;

	चयन (rfpath) अणु
	हाल RF90_PATH_A:
		क्रम (i = 0; i < radio_a_tblen; i = i + 2) अणु
			rtl_rfreg_delay(hw, rfpath, radio_a_table[i],
					MASK20BITS, radio_a_table[i + 1]);

		पूर्ण

		/* PA Bias current क्रम inferiority IC */
		_rtl92s_phy_config_rfpa_bias_current(hw, rfpath);
		अवरोध;
	हाल RF90_PATH_B:
		क्रम (i = 0; i < radio_b_tblen; i = i + 2) अणु
			rtl_rfreg_delay(hw, rfpath, radio_b_table[i],
					MASK20BITS, radio_b_table[i + 1]);
		पूर्ण
		अवरोध;
	हाल RF90_PATH_C:
		;
		अवरोध;
	हाल RF90_PATH_D:
		;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rtstatus;
पूर्ण


bool rtl92s_phy_mac_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;
	u32 arraylength;
	u32 *ptrarray;

	arraylength = MAC_2T_ARRAYLENGTH;
	ptrarray = rtl8192semac_2t_array;

	क्रम (i = 0; i < arraylength; i = i + 2)
		rtl_ग_लिखो_byte(rtlpriv, ptrarray[i], (u8)ptrarray[i + 1]);

	वापस true;
पूर्ण


bool rtl92s_phy_bb_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	bool rtstatus;
	u8 pathmap, index, rf_num = 0;
	u8 path1, path2;

	_rtl92s_phy_init_रेजिस्टर_definition(hw);

	/* Config BB and AGC */
	rtstatus = _rtl92s_phy_bb_config_parafile(hw);


	/* Check BB/RF confiuration setting. */
	/* We only need to configure RF which is turned on. */
	path1 = (u8)(rtl92s_phy_query_bb_reg(hw, RFPGA0_TXINFO, 0xf));
	mdelay(10);
	path2 = (u8)(rtl92s_phy_query_bb_reg(hw, ROFDM0_TRXPATHENABLE, 0xf));
	pathmap = path1 | path2;

	rtlphy->rf_pathmap = pathmap;
	क्रम (index = 0; index < 4; index++) अणु
		अगर ((pathmap >> index) & 0x1)
			rf_num++;
	पूर्ण

	अगर ((rtlphy->rf_type == RF_1T1R && rf_num != 1) ||
	    (rtlphy->rf_type == RF_1T2R && rf_num != 2) ||
	    (rtlphy->rf_type == RF_2T2R && rf_num != 2) ||
	    (rtlphy->rf_type == RF_2T2R_GREEN && rf_num != 2)) अणु
		pr_err("RF_Type(%x) does not match RF_Num(%x)!!\n",
		       rtlphy->rf_type, rf_num);
		pr_err("path1 0x%x, path2 0x%x, pathmap 0x%x\n",
		       path1, path2, pathmap);
	पूर्ण

	वापस rtstatus;
पूर्ण

bool rtl92s_phy_rf_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	/* Initialize general global value */
	अगर (rtlphy->rf_type == RF_1T1R)
		rtlphy->num_total_rfpath = 1;
	अन्यथा
		rtlphy->num_total_rfpath = 2;

	/* Config BB and RF */
	वापस rtl92s_phy_rf6052_config(hw);
पूर्ण

व्योम rtl92s_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	/* पढ़ो rx initial gain */
	rtlphy->शेष_initialgain[0] = rtl_get_bbreg(hw,
			ROFDM0_XAAGCCORE1, MASKBYTE0);
	rtlphy->शेष_initialgain[1] = rtl_get_bbreg(hw,
			ROFDM0_XBAGCCORE1, MASKBYTE0);
	rtlphy->शेष_initialgain[2] = rtl_get_bbreg(hw,
			ROFDM0_XCAGCCORE1, MASKBYTE0);
	rtlphy->शेष_initialgain[3] = rtl_get_bbreg(hw,
			ROFDM0_XDAGCCORE1, MASKBYTE0);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Default initial gain (c50=0x%x, c58=0x%x, c60=0x%x, c68=0x%x)\n",
		rtlphy->शेष_initialgain[0],
		rtlphy->शेष_initialgain[1],
		rtlphy->शेष_initialgain[2],
		rtlphy->शेष_initialgain[3]);

	/* पढ़ो framesync */
	rtlphy->framesync = rtl_get_bbreg(hw, ROFDM0_RXDETECTOR3, MASKBYTE0);
	rtlphy->framesync_c34 = rtl_get_bbreg(hw, ROFDM0_RXDETECTOR2,
					      MASKDWORD);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Default framesync (0x%x) = 0x%x\n",
		ROFDM0_RXDETECTOR3, rtlphy->framesync);

पूर्ण

अटल व्योम _rtl92s_phy_get_txघातer_index(काष्ठा ieee80211_hw *hw, u8 channel,
					  u8 *cckघातerlevel, u8 *ofdmघातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 index = (channel - 1);

	/* 1. CCK */
	/* RF-A */
	cckघातerlevel[0] = rtlefuse->txpwrlevel_cck[0][index];
	/* RF-B */
	cckघातerlevel[1] = rtlefuse->txpwrlevel_cck[1][index];

	/* 2. OFDM क्रम 1T or 2T */
	अगर (rtlphy->rf_type == RF_1T2R || rtlphy->rf_type == RF_1T1R) अणु
		/* Read HT 40 OFDM TX घातer */
		ofdmघातerlevel[0] = rtlefuse->txpwrlevel_ht40_1s[0][index];
		ofdmघातerlevel[1] = rtlefuse->txpwrlevel_ht40_1s[1][index];
	पूर्ण अन्यथा अगर (rtlphy->rf_type == RF_2T2R) अणु
		/* Read HT 40 OFDM TX घातer */
		ofdmघातerlevel[0] = rtlefuse->txpwrlevel_ht40_2s[0][index];
		ofdmघातerlevel[1] = rtlefuse->txpwrlevel_ht40_2s[1][index];
	पूर्ण अन्यथा अणु
		ofdmघातerlevel[0] = 0;
		ofdmघातerlevel[1] = 0;
	पूर्ण
पूर्ण

अटल व्योम _rtl92s_phy_ccxघातer_indexcheck(काष्ठा ieee80211_hw *hw,
		u8 channel, u8 *cckघातerlevel, u8 *ofdmघातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	rtlphy->cur_cck_txpwridx = cckघातerlevel[0];
	rtlphy->cur_ofdm24g_txpwridx = ofdmघातerlevel[0];
पूर्ण

व्योम rtl92s_phy_set_txघातer(काष्ठा ieee80211_hw *hw, u8	channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	/* [0]:RF-A, [1]:RF-B */
	u8 cckघातerlevel[2], ofdmघातerlevel[2];

	अगर (!rtlefuse->txpwr_fromeprom)
		वापस;

	/* Mainly we use RF-A Tx Power to ग_लिखो the Tx Power रेजिस्टरs,
	 * but the RF-B Tx Power must be calculated by the antenna dअगरf.
	 * So we have to reग_लिखो Antenna gain offset रेजिस्टर here.
	 * Please refer to BB रेजिस्टर 0x80c
	 * 1. For CCK.
	 * 2. For OFDM 1T or 2T */
	_rtl92s_phy_get_txघातer_index(hw, channel, &cckघातerlevel[0],
			&ofdmघातerlevel[0]);

	rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
		"Channel-%d, cckPowerLevel (A / B) = 0x%x / 0x%x, ofdmPowerLevel (A / B) = 0x%x / 0x%x\n",
		channel, cckघातerlevel[0], cckघातerlevel[1],
		ofdmघातerlevel[0], ofdmघातerlevel[1]);

	_rtl92s_phy_ccxघातer_indexcheck(hw, channel, &cckघातerlevel[0],
			&ofdmघातerlevel[0]);

	rtl92s_phy_rf6052_set_ccktxघातer(hw, cckघातerlevel[0]);
	rtl92s_phy_rf6052_set_ofdmtxघातer(hw, &ofdmघातerlevel[0], channel);

पूर्ण

व्योम rtl92s_phy_chk_fwcmd_ioकरोne(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 pollingcnt = 10000;
	u32 पंचांगpvalue;

	/* Make sure that CMD IO has be accepted by FW. */
	करो अणु
		udelay(10);

		पंचांगpvalue = rtl_पढ़ो_dword(rtlpriv, WFM5);
		अगर (पंचांगpvalue == 0)
			अवरोध;
	पूर्ण जबतक (--pollingcnt);

	अगर (pollingcnt == 0)
		pr_err("Set FW Cmd fail!!\n");
पूर्ण


अटल व्योम _rtl92s_phy_set_fwcmd_io(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 input, current_aid = 0;

	अगर (is_hal_stop(rtlhal))
		वापस;

	अगर (hal_get_firmwareversion(rtlpriv) < 0x34)
		जाओ skip;
	/* We re-map RA related CMD IO to combinational ones */
	/* अगर FW version is v.52 or later. */
	चयन (rtlhal->current_fwcmd_io) अणु
	हाल FW_CMD_RA_REFRESH_N:
		rtlhal->current_fwcmd_io = FW_CMD_RA_REFRESH_N_COMB;
		अवरोध;
	हाल FW_CMD_RA_REFRESH_BG:
		rtlhal->current_fwcmd_io = FW_CMD_RA_REFRESH_BG_COMB;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

skip:
	चयन (rtlhal->current_fwcmd_io) अणु
	हाल FW_CMD_RA_RESET:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_RA_RESET\n");
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_RA_RESET);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;
	हाल FW_CMD_RA_ACTIVE:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_RA_ACTIVE\n");
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_RA_ACTIVE);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;
	हाल FW_CMD_RA_REFRESH_N:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_RA_REFRESH_N\n");
		input = FW_RA_REFRESH;
		rtl_ग_लिखो_dword(rtlpriv, WFM5, input);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_RA_ENABLE_RSSI_MASK);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;
	हाल FW_CMD_RA_REFRESH_BG:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG,
			"FW_CMD_RA_REFRESH_BG\n");
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_RA_REFRESH);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_RA_DISABLE_RSSI_MASK);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;
	हाल FW_CMD_RA_REFRESH_N_COMB:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG,
			"FW_CMD_RA_REFRESH_N_COMB\n");
		input = FW_RA_IOT_N_COMB;
		rtl_ग_लिखो_dword(rtlpriv, WFM5, input);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;
	हाल FW_CMD_RA_REFRESH_BG_COMB:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG,
			"FW_CMD_RA_REFRESH_BG_COMB\n");
		input = FW_RA_IOT_BG_COMB;
		rtl_ग_लिखो_dword(rtlpriv, WFM5, input);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;
	हाल FW_CMD_IQK_ENABLE:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_IQK_ENABLE\n");
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_IQK_ENABLE);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;
	हाल FW_CMD_PAUSE_DM_BY_SCAN:
		/* Lower initial gain */
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, MASKBYTE0, 0x17);
		rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, MASKBYTE0, 0x17);
		/* CCA threshold */
		rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0x40);
		अवरोध;
	हाल FW_CMD_RESUME_DM_BY_SCAN:
		/* CCA threshold */
		rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);
		rtl92s_phy_set_txघातer(hw, rtlphy->current_channel);
		अवरोध;
	हाल FW_CMD_HIGH_PWR_DISABLE:
		अगर (rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE)
			अवरोध;

		/* Lower initial gain */
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, MASKBYTE0, 0x17);
		rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, MASKBYTE0, 0x17);
		/* CCA threshold */
		rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0x40);
		अवरोध;
	हाल FW_CMD_HIGH_PWR_ENABLE:
		अगर ((rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) ||
			rtlpriv->dm.dynamic_txघातer_enable)
			अवरोध;

		/* CCA threshold */
		rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);
		अवरोध;
	हाल FW_CMD_LPS_ENTER:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_LPS_ENTER\n");
		current_aid = rtlpriv->mac80211.assoc_id;
		rtl_ग_लिखो_dword(rtlpriv, WFM5, (FW_LPS_ENTER |
				((current_aid | 0xc000) << 8)));
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		/* FW set TXOP disable here, so disable EDCA
		 * turbo mode until driver leave LPS */
		अवरोध;
	हाल FW_CMD_LPS_LEAVE:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_LPS_LEAVE\n");
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_LPS_LEAVE);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;
	हाल FW_CMD_ADD_A2_ENTRY:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_ADD_A2_ENTRY\n");
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_ADD_A2_ENTRY);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;
	हाल FW_CMD_CTRL_DM_BY_DRIVER:
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
			"FW_CMD_CTRL_DM_BY_DRIVER\n");
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_CTRL_DM_BY_DRIVER);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	rtl92s_phy_chk_fwcmd_ioकरोne(hw);

	/* Clear FW CMD operation flag. */
	rtlhal->set_fwcmd_inprogress = false;
पूर्ण

bool rtl92s_phy_set_fw_cmd(काष्ठा ieee80211_hw *hw, क्रमागत fwcmd_iotype fw_cmdio)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32	fw_param = FW_CMD_IO_PARA_QUERY(rtlpriv);
	u16	fw_cmdmap = FW_CMD_IO_QUERY(rtlpriv);
	bool postprocessing = false;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
		"Set FW Cmd(%#x), set_fwcmd_inprogress(%d)\n",
		fw_cmdio, rtlhal->set_fwcmd_inprogress);

	करो अणु
		/* We re-map to combined FW CMD ones अगर firmware version */
		/* is v.53 or later. */
		अगर (hal_get_firmwareversion(rtlpriv) >= 0x35) अणु
			चयन (fw_cmdio) अणु
			हाल FW_CMD_RA_REFRESH_N:
				fw_cmdio = FW_CMD_RA_REFRESH_N_COMB;
				अवरोध;
			हाल FW_CMD_RA_REFRESH_BG:
				fw_cmdio = FW_CMD_RA_REFRESH_BG_COMB;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((fw_cmdio == FW_CMD_IQK_ENABLE) ||
			    (fw_cmdio == FW_CMD_RA_REFRESH_N) ||
			    (fw_cmdio == FW_CMD_RA_REFRESH_BG)) अणु
				postprocessing = true;
				अवरोध;
			पूर्ण
		पूर्ण

		/* If firmware version is v.62 or later,
		 * use FW_CMD_IO_SET क्रम FW_CMD_CTRL_DM_BY_DRIVER */
		अगर (hal_get_firmwareversion(rtlpriv) >= 0x3E) अणु
			अगर (fw_cmdio == FW_CMD_CTRL_DM_BY_DRIVER)
				fw_cmdio = FW_CMD_CTRL_DM_BY_DRIVER_NEW;
		पूर्ण


		/* We shall revise all FW Cmd IO पूर्णांकo Reg0x364
		 * DM map table in the future. */
		चयन (fw_cmdio) अणु
		हाल FW_CMD_RA_INIT:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "RA init!!\n");
			fw_cmdmap |= FW_RA_INIT_CTL;
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			/* Clear control flag to sync with FW. */
			FW_CMD_IO_CLR(rtlpriv, FW_RA_INIT_CTL);
			अवरोध;
		हाल FW_CMD_DIG_DISABLE:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"Set DIG disable!!\n");
			fw_cmdmap &= ~FW_DIG_ENABLE_CTL;
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			अवरोध;
		हाल FW_CMD_DIG_ENABLE:
		हाल FW_CMD_DIG_RESUME:
			अगर (!(rtlpriv->dm.dm_flag & HAL_DM_DIG_DISABLE)) अणु
				rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
					"Set DIG enable or resume!!\n");
				fw_cmdmap |= (FW_DIG_ENABLE_CTL | FW_SS_CTL);
				FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			पूर्ण
			अवरोध;
		हाल FW_CMD_DIG_HALT:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"Set DIG halt!!\n");
			fw_cmdmap &= ~(FW_DIG_ENABLE_CTL | FW_SS_CTL);
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			अवरोध;
		हाल FW_CMD_TXPWR_TRACK_THERMAL: अणु
			u8	thermalval = 0;
			fw_cmdmap |= FW_PWR_TRK_CTL;

			/* Clear FW parameter in terms of thermal parts. */
			fw_param &= FW_PWR_TRK_PARAM_CLR;

			thermalval = rtlpriv->dm.thermalvalue;
			fw_param |= ((thermalval << 24) |
				     (rtlefuse->thermalmeter[0] << 16));

			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"Set TxPwr tracking!! FwCmdMap(%#x), FwParam(%#x)\n",
				fw_cmdmap, fw_param);

			FW_CMD_PARA_SET(rtlpriv, fw_param);
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);

			/* Clear control flag to sync with FW. */
			FW_CMD_IO_CLR(rtlpriv, FW_PWR_TRK_CTL);
			पूर्ण
			अवरोध;
		/* The following FW CMDs are only compatible to
		 * v.53 or later. */
		हाल FW_CMD_RA_REFRESH_N_COMB:
			fw_cmdmap |= FW_RA_N_CTL;

			/* Clear RA BG mode control. */
			fw_cmdmap &= ~(FW_RA_BG_CTL | FW_RA_INIT_CTL);

			/* Clear FW parameter in terms of RA parts. */
			fw_param &= FW_RA_PARAM_CLR;

			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"[FW CMD] [New Version] Set RA/IOT Comb in n mode!! FwCmdMap(%#x), FwParam(%#x)\n",
				fw_cmdmap, fw_param);

			FW_CMD_PARA_SET(rtlpriv, fw_param);
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);

			/* Clear control flag to sync with FW. */
			FW_CMD_IO_CLR(rtlpriv, FW_RA_N_CTL);
			अवरोध;
		हाल FW_CMD_RA_REFRESH_BG_COMB:
			fw_cmdmap |= FW_RA_BG_CTL;

			/* Clear RA n-mode control. */
			fw_cmdmap &= ~(FW_RA_N_CTL | FW_RA_INIT_CTL);
			/* Clear FW parameter in terms of RA parts. */
			fw_param &= FW_RA_PARAM_CLR;

			FW_CMD_PARA_SET(rtlpriv, fw_param);
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);

			/* Clear control flag to sync with FW. */
			FW_CMD_IO_CLR(rtlpriv, FW_RA_BG_CTL);
			अवरोध;
		हाल FW_CMD_IQK_ENABLE:
			fw_cmdmap |= FW_IQK_CTL;
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			/* Clear control flag to sync with FW. */
			FW_CMD_IO_CLR(rtlpriv, FW_IQK_CTL);
			अवरोध;
		/* The following FW CMD is compatible to v.62 or later.  */
		हाल FW_CMD_CTRL_DM_BY_DRIVER_NEW:
			fw_cmdmap |= FW_DRIVER_CTRL_DM_CTL;
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			अवरोध;
		/*  The followed FW Cmds needs post-processing later. */
		हाल FW_CMD_RESUME_DM_BY_SCAN:
			fw_cmdmap |= (FW_DIG_ENABLE_CTL |
				      FW_HIGH_PWR_ENABLE_CTL |
				      FW_SS_CTL);

			अगर (rtlpriv->dm.dm_flag & HAL_DM_DIG_DISABLE ||
				!digtable->dig_enable_flag)
				fw_cmdmap &= ~FW_DIG_ENABLE_CTL;

			अगर ((rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) ||
			    rtlpriv->dm.dynamic_txघातer_enable)
				fw_cmdmap &= ~FW_HIGH_PWR_ENABLE_CTL;

			अगर ((digtable->dig_ext_port_stage ==
			    DIG_EXT_PORT_STAGE_0) ||
			    (digtable->dig_ext_port_stage ==
			    DIG_EXT_PORT_STAGE_1))
				fw_cmdmap &= ~FW_DIG_ENABLE_CTL;

			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			postprocessing = true;
			अवरोध;
		हाल FW_CMD_PAUSE_DM_BY_SCAN:
			fw_cmdmap &= ~(FW_DIG_ENABLE_CTL |
				       FW_HIGH_PWR_ENABLE_CTL |
				       FW_SS_CTL);
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			postprocessing = true;
			अवरोध;
		हाल FW_CMD_HIGH_PWR_DISABLE:
			fw_cmdmap &= ~FW_HIGH_PWR_ENABLE_CTL;
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			postprocessing = true;
			अवरोध;
		हाल FW_CMD_HIGH_PWR_ENABLE:
			अगर (!(rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) &&
			    !rtlpriv->dm.dynamic_txघातer_enable) अणु
				fw_cmdmap |= (FW_HIGH_PWR_ENABLE_CTL |
					      FW_SS_CTL);
				FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
				postprocessing = true;
			पूर्ण
			अवरोध;
		हाल FW_CMD_DIG_MODE_FA:
			fw_cmdmap |= FW_FA_CTL;
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			अवरोध;
		हाल FW_CMD_DIG_MODE_SS:
			fw_cmdmap &= ~FW_FA_CTL;
			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			अवरोध;
		हाल FW_CMD_PAPE_CONTROL:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"[FW CMD] Set PAPE Control\n");
			fw_cmdmap &= ~FW_PAPE_CTL_BY_SW_HW;

			FW_CMD_IO_SET(rtlpriv, fw_cmdmap);
			अवरोध;
		शेष:
			/* Pass to original FW CMD processing callback
			 * routine. */
			postprocessing = true;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (false);

	/* We shall post processing these FW CMD अगर
	 * variable postprocessing is set.
	 */
	अगर (postprocessing && !rtlhal->set_fwcmd_inprogress) अणु
		rtlhal->set_fwcmd_inprogress = true;
		/* Update current FW Cmd क्रम callback use. */
		rtlhal->current_fwcmd_io = fw_cmdio;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	_rtl92s_phy_set_fwcmd_io(hw);
	वापस true;
पूर्ण

अटल	व्योम _rtl92s_phy_check_ephy_चयनपढ़ोy(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32	delay = 100;
	u8	regu1;

	regu1 = rtl_पढ़ो_byte(rtlpriv, 0x554);
	जबतक ((regu1 & BIT(5)) && (delay > 0)) अणु
		regu1 = rtl_पढ़ो_byte(rtlpriv, 0x554);
		delay--;
		/* We delay only 50us to prevent
		 * being scheduled out. */
		udelay(50);
	पूर्ण
पूर्ण

व्योम rtl92s_phy_चयन_ephy_parameter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	/* The way to be capable to चयन घड़ी request
	 * when the PG setting करोes not support घड़ी request.
	 * This is the backकरोor solution to चयन घड़ी
	 * request beक्रमe ASPM or D3. */
	rtl_ग_लिखो_dword(rtlpriv, 0x540, 0x73c11);
	rtl_ग_लिखो_dword(rtlpriv, 0x548, 0x2407c);

	/* Switch EPHY parameter!!!! */
	rtl_ग_लिखो_word(rtlpriv, 0x550, 0x1000);
	rtl_ग_लिखो_byte(rtlpriv, 0x554, 0x20);
	_rtl92s_phy_check_ephy_चयनपढ़ोy(hw);

	rtl_ग_लिखो_word(rtlpriv, 0x550, 0xa0eb);
	rtl_ग_लिखो_byte(rtlpriv, 0x554, 0x3e);
	_rtl92s_phy_check_ephy_चयनपढ़ोy(hw);

	rtl_ग_लिखो_word(rtlpriv, 0x550, 0xff80);
	rtl_ग_लिखो_byte(rtlpriv, 0x554, 0x39);
	_rtl92s_phy_check_ephy_चयनपढ़ोy(hw);

	/* Delay L1 enter समय */
	अगर (ppsc->support_aspm && !ppsc->support_backकरोor)
		rtl_ग_लिखो_byte(rtlpriv, 0x560, 0x40);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, 0x560, 0x00);

पूर्ण

व्योम rtl92s_phy_set_beacon_hwreg(काष्ठा ieee80211_hw *hw, u16 beaconपूर्णांकerval)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 new_bcn_num = 0;

	अगर (hal_get_firmwareversion(rtlpriv) >= 0x33) अणु
		/* Fw v.51 and later. */
		rtl_ग_लिखो_dword(rtlpriv, WFM5, 0xF1000000 |
				(beaconपूर्णांकerval << 8));
	पूर्ण अन्यथा अणु
		new_bcn_num = beaconपूर्णांकerval * 32 - 64;
		rtl_ग_लिखो_dword(rtlpriv, WFM3 + 4, new_bcn_num);
		rtl_ग_लिखो_dword(rtlpriv, WFM3, 0xB026007C);
	पूर्ण
पूर्ण
