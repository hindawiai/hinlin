<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../efuse.h"
#समावेश "../base.h"
#समावेश "../regd.h"
#समावेश "../cam.h"
#समावेश "../ps.h"
#समावेश "../pci.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "dm.h"
#समावेश "fw.h"
#समावेश "led.h"
#समावेश "sw.h"
#समावेश "hw.h"

u32 rtl92de_पढ़ो_dword_dbi(काष्ठा ieee80211_hw *hw, u16 offset, u8 direct)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 value;

	rtl_ग_लिखो_word(rtlpriv, REG_DBI_CTRL, (offset & 0xFFC));
	rtl_ग_लिखो_byte(rtlpriv, REG_DBI_FLAG, BIT(1) | direct);
	udelay(10);
	value = rtl_पढ़ो_dword(rtlpriv, REG_DBI_RDATA);
	वापस value;
पूर्ण

व्योम rtl92de_ग_लिखो_dword_dbi(काष्ठा ieee80211_hw *hw,
			     u16 offset, u32 value, u8 direct)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_word(rtlpriv, REG_DBI_CTRL, ((offset & 0xFFC) | 0xF000));
	rtl_ग_लिखो_dword(rtlpriv, REG_DBI_WDATA, value);
	rtl_ग_लिखो_byte(rtlpriv, REG_DBI_FLAG, BIT(0) | direct);
पूर्ण

अटल व्योम _rtl92de_set_bcn_ctrl_reg(काष्ठा ieee80211_hw *hw,
				      u8 set_bits, u8 clear_bits)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpci->reg_bcn_ctrl_val |= set_bits;
	rtlpci->reg_bcn_ctrl_val &= ~clear_bits;
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8) rtlpci->reg_bcn_ctrl_val);
पूर्ण

अटल व्योम _rtl92de_stop_tx_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp1byte;

	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp1byte & (~BIT(6)));
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_MAX_ERR, 0xff);
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0x64);
	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
	पंचांगp1byte &= ~(BIT(0));
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, पंचांगp1byte);
पूर्ण

अटल व्योम _rtl92de_resume_tx_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp1byte;

	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp1byte | BIT(6));
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_MAX_ERR, 0x0a);
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);
	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
	पंचांगp1byte |= BIT(0);
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, पंचांगp1byte);
पूर्ण

अटल व्योम _rtl92de_enable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl92de_set_bcn_ctrl_reg(hw, 0, BIT(1));
पूर्ण

अटल व्योम _rtl92de_disable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl92de_set_bcn_ctrl_reg(hw, BIT(1), 0);
पूर्ण

व्योम rtl92de_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	चयन (variable) अणु
	हाल HW_VAR_RCR:
		*((u32 *) (val)) = rtlpci->receive_config;
		अवरोध;
	हाल HW_VAR_RF_STATE:
		*((क्रमागत rf_pwrstate *)(val)) = ppsc->rfpwr_state;
		अवरोध;
	हाल HW_VAR_FWLPS_RF_ON:अणु
		क्रमागत rf_pwrstate rख_स्थितिe;
		u32 val_rcr;

		rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RF_STATE,
					      (u8 *)(&rख_स्थितिe));
		अगर (rख_स्थितिe == ERFOFF) अणु
			*((bool *) (val)) = true;
		पूर्ण अन्यथा अणु
			val_rcr = rtl_पढ़ो_dword(rtlpriv, REG_RCR);
			val_rcr &= 0x00070000;
			अगर (val_rcr)
				*((bool *) (val)) = false;
			अन्यथा
				*((bool *) (val)) = true;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल HW_VAR_FW_PSMODE_STATUS:
		*((bool *) (val)) = ppsc->fw_current_inpsmode;
		अवरोध;
	हाल HW_VAR_CORRECT_TSF:अणु
		u64 tsf;
		u32 *ptsf_low = (u32 *)&tsf;
		u32 *ptsf_high = ((u32 *)&tsf) + 1;

		*ptsf_high = rtl_पढ़ो_dword(rtlpriv, (REG_TSFTR + 4));
		*ptsf_low = rtl_पढ़ो_dword(rtlpriv, REG_TSFTR);
		*((u64 *) (val)) = tsf;
		अवरोध;
	पूर्ण
	हाल HW_VAR_INT_MIGRATION:
		*((bool *)(val)) = rtlpriv->dm.पूर्णांकerrupt_migration;
		अवरोध;
	हाल HW_VAR_INT_AC:
		*((bool *)(val)) = rtlpriv->dm.disable_tx_पूर्णांक;
		अवरोध;
	हाल HAL_DEF_WOWLAN:
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92de_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 idx;

	चयन (variable) अणु
	हाल HW_VAR_ETHER_ADDR:
		क्रम (idx = 0; idx < ETH_ALEN; idx++) अणु
			rtl_ग_लिखो_byte(rtlpriv, (REG_MACID + idx),
				       val[idx]);
		पूर्ण
		अवरोध;
	हाल HW_VAR_BASIC_RATE: अणु
		u16 rate_cfg = ((u16 *) val)[0];
		u8 rate_index = 0;

		rate_cfg = rate_cfg & 0x15f;
		अगर (mac->venकरोr == PEER_CISCO &&
		    ((rate_cfg & 0x150) == 0))
			rate_cfg |= 0x01;
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR, rate_cfg & 0xff);
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 1,
			       (rate_cfg >> 8) & 0xff);
		जबतक (rate_cfg > 0x1) अणु
			rate_cfg = (rate_cfg >> 1);
			rate_index++;
		पूर्ण
		अगर (rtlhal->fw_version > 0xe)
			rtl_ग_लिखो_byte(rtlpriv, REG_INIRTS_RATE_SEL,
				       rate_index);
		अवरोध;
	पूर्ण
	हाल HW_VAR_BSSID:
		क्रम (idx = 0; idx < ETH_ALEN; idx++) अणु
			rtl_ग_लिखो_byte(rtlpriv, (REG_BSSID + idx),
				       val[idx]);
		पूर्ण
		अवरोध;
	हाल HW_VAR_SIFS:
		rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_CTX + 1, val[0]);
		rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_TRX + 1, val[1]);
		rtl_ग_लिखो_byte(rtlpriv, REG_SPEC_SIFS + 1, val[0]);
		rtl_ग_लिखो_byte(rtlpriv, REG_MAC_SPEC_SIFS + 1, val[0]);
		अगर (!mac->ht_enable)
			rtl_ग_लिखो_word(rtlpriv, REG_RESP_SIFS_OFDM,
				       0x0e0e);
		अन्यथा
			rtl_ग_लिखो_word(rtlpriv, REG_RESP_SIFS_OFDM,
				       *((u16 *) val));
		अवरोध;
	हाल HW_VAR_SLOT_TIME: अणु
		u8 e_aci;

		rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
			"HW_VAR_SLOT_TIME %x\n", val[0]);
		rtl_ग_लिखो_byte(rtlpriv, REG_SLOT, val[0]);
		क्रम (e_aci = 0; e_aci < AC_MAX; e_aci++)
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_AC_PARAM,
						      (&e_aci));
		अवरोध;
	पूर्ण
	हाल HW_VAR_ACK_PREAMBLE: अणु
		u8 reg_पंचांगp;
		u8 लघु_preamble = (bool) (*val);

		reg_पंचांगp = (mac->cur_40_prime_sc) << 5;
		अगर (लघु_preamble)
			reg_पंचांगp |= 0x80;
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 2, reg_पंचांगp);
		अवरोध;
	पूर्ण
	हाल HW_VAR_AMPDU_MIN_SPACE: अणु
		u8 min_spacing_to_set;
		u8 sec_min_space;

		min_spacing_to_set = *val;
		अगर (min_spacing_to_set <= 7) अणु
			sec_min_space = 0;
			अगर (min_spacing_to_set < sec_min_space)
				min_spacing_to_set = sec_min_space;
			mac->min_space_cfg = ((mac->min_space_cfg & 0xf8) |
					      min_spacing_to_set);
			*val = min_spacing_to_set;
			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"Set HW_VAR_AMPDU_MIN_SPACE: %#x\n",
				mac->min_space_cfg);
			rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE,
				       mac->min_space_cfg);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल HW_VAR_SHORTGI_DENSITY: अणु
		u8 density_to_set;

		density_to_set = *val;
		mac->min_space_cfg = rtlpriv->rtlhal.minspace_cfg;
		mac->min_space_cfg |= (density_to_set << 3);
		rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
			"Set HW_VAR_SHORTGI_DENSITY: %#x\n",
			mac->min_space_cfg);
		rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE,
			       mac->min_space_cfg);
		अवरोध;
	पूर्ण
	हाल HW_VAR_AMPDU_FACTOR: अणु
		u8 factor_toset;
		u32 regtoset;
		u8 *pपंचांगp_byte = शून्य;
		u8 index;

		अगर (rtlhal->macphymode == DUALMAC_DUALPHY)
			regtoset = 0xb9726641;
		अन्यथा अगर (rtlhal->macphymode == DUALMAC_SINGLEPHY)
			regtoset = 0x66626641;
		अन्यथा
			regtoset = 0xb972a841;
		factor_toset = *val;
		अगर (factor_toset <= 3) अणु
			factor_toset = (1 << (factor_toset + 2));
			अगर (factor_toset > 0xf)
				factor_toset = 0xf;
			क्रम (index = 0; index < 4; index++) अणु
				pपंचांगp_byte = (u8 *)(&regtoset) + index;
				अगर ((*pपंचांगp_byte & 0xf0) >
				    (factor_toset << 4))
					*pपंचांगp_byte = (*pपंचांगp_byte & 0x0f)
						 | (factor_toset << 4);
				अगर ((*pपंचांगp_byte & 0x0f) > factor_toset)
					*pपंचांगp_byte = (*pपंचांगp_byte & 0xf0)
						     | (factor_toset);
			पूर्ण
			rtl_ग_लिखो_dword(rtlpriv, REG_AGGLEN_LMT, regtoset);
			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"Set HW_VAR_AMPDU_FACTOR: %#x\n",
				factor_toset);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल HW_VAR_AC_PARAM: अणु
		u8 e_aci = *val;
		rtl92d_dm_init_edca_turbo(hw);
		अगर (rtlpci->acm_method != EACMWAY2_SW)
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ACM_CTRL,
						      &e_aci);
		अवरोध;
	पूर्ण
	हाल HW_VAR_ACM_CTRL: अणु
		u8 e_aci = *val;
		जोड़ aci_aअगरsn *p_aci_aअगरsn =
		    (जोड़ aci_aअगरsn *)(&(mac->ac[0].aअगरs));
		u8 acm = p_aci_aअगरsn->f.acm;
		u8 acm_ctrl = rtl_पढ़ो_byte(rtlpriv, REG_ACMHWCTRL);

		acm_ctrl = acm_ctrl | ((rtlpci->acm_method == 2) ?  0x0 : 0x1);
		अगर (acm) अणु
			चयन (e_aci) अणु
			हाल AC0_BE:
				acm_ctrl |= ACMHW_BEQEN;
				अवरोध;
			हाल AC2_VI:
				acm_ctrl |= ACMHW_VIQEN;
				अवरोध;
			हाल AC3_VO:
				acm_ctrl |= ACMHW_VOQEN;
				अवरोध;
			शेष:
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"HW_VAR_ACM_CTRL acm set failed: eACI is %d\n",
					acm);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (e_aci) अणु
			हाल AC0_BE:
				acm_ctrl &= (~ACMHW_BEQEN);
				अवरोध;
			हाल AC2_VI:
				acm_ctrl &= (~ACMHW_VIQEN);
				अवरोध;
			हाल AC3_VO:
				acm_ctrl &= (~ACMHW_VOQEN);
				अवरोध;
			शेष:
				pr_err("switch case %#x not processed\n",
				       e_aci);
				अवरोध;
			पूर्ण
		पूर्ण
		rtl_dbg(rtlpriv, COMP_QOS, DBG_TRACE,
			"SetHwReg8190pci(): [HW_VAR_ACM_CTRL] Write 0x%X\n",
			acm_ctrl);
		rtl_ग_लिखो_byte(rtlpriv, REG_ACMHWCTRL, acm_ctrl);
		अवरोध;
	पूर्ण
	हाल HW_VAR_RCR:
		rtl_ग_लिखो_dword(rtlpriv, REG_RCR, ((u32 *) (val))[0]);
		rtlpci->receive_config = ((u32 *) (val))[0];
		अवरोध;
	हाल HW_VAR_RETRY_LIMIT: अणु
		u8 retry_limit = val[0];

		rtl_ग_लिखो_word(rtlpriv, REG_RL,
			       retry_limit << RETRY_LIMIT_SHORT_SHIFT |
			       retry_limit << RETRY_LIMIT_LONG_SHIFT);
		अवरोध;
	पूर्ण
	हाल HW_VAR_DUAL_TSF_RST:
		rtl_ग_लिखो_byte(rtlpriv, REG_DUAL_TSF_RST, (BIT(0) | BIT(1)));
		अवरोध;
	हाल HW_VAR_EFUSE_BYTES:
		rtlefuse->efuse_usedbytes = *((u16 *) val);
		अवरोध;
	हाल HW_VAR_EFUSE_USAGE:
		rtlefuse->efuse_usedpercentage = *val;
		अवरोध;
	हाल HW_VAR_IO_CMD:
		rtl92d_phy_set_io_cmd(hw, (*(क्रमागत io_type *)val));
		अवरोध;
	हाल HW_VAR_WPA_CONFIG:
		rtl_ग_लिखो_byte(rtlpriv, REG_SECCFG, *val);
		अवरोध;
	हाल HW_VAR_SET_RPWM:
		rtl92d_fill_h2c_cmd(hw, H2C_PWRM, 1, (val));
		अवरोध;
	हाल HW_VAR_H2C_FW_PWRMODE:
		अवरोध;
	हाल HW_VAR_FW_PSMODE_STATUS:
		ppsc->fw_current_inpsmode = *((bool *) val);
		अवरोध;
	हाल HW_VAR_H2C_FW_JOINBSSRPT: अणु
		u8 mstatus = (*val);
		u8 पंचांगp_regcr, पंचांगp_reg422;
		bool recover = false;

		अगर (mstatus == RT_MEDIA_CONNECT) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_AID, शून्य);
			पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
			rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1,
				       (पंचांगp_regcr | BIT(0)));
			_rtl92de_set_bcn_ctrl_reg(hw, 0, BIT(3));
			_rtl92de_set_bcn_ctrl_reg(hw, BIT(4), 0);
			पंचांगp_reg422 = rtl_पढ़ो_byte(rtlpriv,
						 REG_FWHW_TXQ_CTRL + 2);
			अगर (पंचांगp_reg422 & BIT(6))
				recover = true;
			rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2,
				       पंचांगp_reg422 & (~BIT(6)));
			rtl92d_set_fw_rsvdpagepkt(hw, 0);
			_rtl92de_set_bcn_ctrl_reg(hw, BIT(3), 0);
			_rtl92de_set_bcn_ctrl_reg(hw, 0, BIT(4));
			अगर (recover)
				rtl_ग_लिखो_byte(rtlpriv,
					       REG_FWHW_TXQ_CTRL + 2,
					       पंचांगp_reg422);
			rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1,
				       (पंचांगp_regcr & ~(BIT(0))));
		पूर्ण
		rtl92d_set_fw_joinbss_report_cmd(hw, (*val));
		अवरोध;
	पूर्ण
	हाल HW_VAR_AID: अणु
		u16 u2bपंचांगp;
		u2bपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_BCN_PSR_RPT);
		u2bपंचांगp &= 0xC000;
		rtl_ग_लिखो_word(rtlpriv, REG_BCN_PSR_RPT, (u2bपंचांगp |
			       mac->assoc_id));
		अवरोध;
	पूर्ण
	हाल HW_VAR_CORRECT_TSF: अणु
		u8 btype_ibss = val[0];

		अगर (btype_ibss)
			_rtl92de_stop_tx_beacon(hw);
		_rtl92de_set_bcn_ctrl_reg(hw, 0, BIT(3));
		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR,
				(u32) (mac->tsf & 0xffffffff));
		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR + 4,
				(u32) ((mac->tsf >> 32) & 0xffffffff));
		_rtl92de_set_bcn_ctrl_reg(hw, BIT(3), 0);
		अगर (btype_ibss)
			_rtl92de_resume_tx_beacon(hw);

		अवरोध;
	पूर्ण
	हाल HW_VAR_INT_MIGRATION: अणु
		bool पूर्णांक_migration = *(bool *) (val);

		अगर (पूर्णांक_migration) अणु
			/* Set पूर्णांकerrupt migration समयr and
			 * corresponding Tx/Rx counter.
			 * समयr 25ns*0xfa0=100us क्रम 0xf packets.
			 * 0x306:Rx, 0x307:Tx */
			rtl_ग_लिखो_dword(rtlpriv, REG_INT_MIG, 0xfe000fa0);
			rtlpriv->dm.पूर्णांकerrupt_migration = पूर्णांक_migration;
		पूर्ण अन्यथा अणु
			/* Reset all पूर्णांकerrupt migration settings. */
			rtl_ग_लिखो_dword(rtlpriv, REG_INT_MIG, 0);
			rtlpriv->dm.पूर्णांकerrupt_migration = पूर्णांक_migration;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल HW_VAR_INT_AC: अणु
		bool disable_ac_पूर्णांक = *((bool *) val);

		/* Disable four ACs पूर्णांकerrupts. */
		अगर (disable_ac_पूर्णांक) अणु
			/* Disable VO, VI, BE and BK four AC पूर्णांकerrupts
			 * to gain more efficient CPU utilization.
			 * When extremely highly Rx OK occurs,
			 * we will disable Tx पूर्णांकerrupts.
			 */
			rtlpriv->cfg->ops->update_पूर्णांकerrupt_mask(hw, 0,
						 RT_AC_INT_MASKS);
			rtlpriv->dm.disable_tx_पूर्णांक = disable_ac_पूर्णांक;
		/* Enable four ACs पूर्णांकerrupts. */
		पूर्ण अन्यथा अणु
			rtlpriv->cfg->ops->update_पूर्णांकerrupt_mask(hw,
						 RT_AC_INT_MASKS, 0);
			rtlpriv->dm.disable_tx_पूर्णांक = disable_ac_पूर्णांक;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		pr_err("switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool _rtl92de_llt_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 address, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool status = true;
	दीर्घ count = 0;
	u32 value = _LLT_INIT_ADDR(address) |
	    _LLT_INIT_DATA(data) | _LLT_OP(_LLT_WRITE_ACCESS);

	rtl_ग_लिखो_dword(rtlpriv, REG_LLT_INIT, value);
	करो अणु
		value = rtl_पढ़ो_dword(rtlpriv, REG_LLT_INIT);
		अगर (_LLT_NO_ACTIVE == _LLT_OP_VALUE(value))
			अवरोध;
		अगर (count > POLLING_LLT_THRESHOLD) अणु
			pr_err("Failed to polling write LLT done at address %d!\n",
			       address);
			status = false;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (++count);
	वापस status;
पूर्ण

अटल bool _rtl92de_llt_table_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अचिन्हित लघु i;
	u8 txpktbuf_bndy;
	u8 maxpage;
	bool status;
	u32 value32; /* High+low page number */
	u8 value8;	 /* normal page number */

	अगर (rtlpriv->rtlhal.macphymode == SINGLEMAC_SINGLEPHY) अणु
		maxpage = 255;
		txpktbuf_bndy = 246;
		value8 = 0;
		value32 = 0x80bf0d29;
	पूर्ण अन्यथा अणु
		maxpage = 127;
		txpktbuf_bndy = 123;
		value8 = 0;
		value32 = 0x80750005;
	पूर्ण

	/* Set reserved page क्रम each queue */
	/* 11.  RQPN 0x200[31:0] = 0x80BD1C1C */
	/* load RQPN */
	rtl_ग_लिखो_byte(rtlpriv, REG_RQPN_NPQ, value8);
	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, value32);

	/* 12.  TXRKTBUG_PG_BNDY 0x114[31:0] = 0x27FF00F6 */
	/* TXRKTBUG_PG_BNDY */
	rtl_ग_लिखो_dword(rtlpriv, REG_TRXFF_BNDY,
			(rtl_पढ़ो_word(rtlpriv, REG_TRXFF_BNDY + 2) << 16 |
			txpktbuf_bndy));

	/* 13.  TDECTRL[15:8] 0x209[7:0] = 0xF6 */
	/* Beacon Head क्रम TXDMA */
	rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 1, txpktbuf_bndy);

	/* 14.  BCNQ_PGBNDY 0x424[7:0] =  0xF6 */
	/* BCNQ_PGBNDY */
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);

	/* 15.  WMAC_LBK_BF_HD 0x45D[7:0] =  0xF6 */
	/* WMAC_LBK_BF_HD */
	rtl_ग_लिखो_byte(rtlpriv, 0x45D, txpktbuf_bndy);

	/* Set Tx/Rx page size (Tx must be 128 Bytes, */
	/* Rx can be 64,128,256,512,1024 bytes) */
	/* 16.  PBP [7:0] = 0x11 */
	/* TRX page size */
	rtl_ग_लिखो_byte(rtlpriv, REG_PBP, 0x11);

	/* 17.  DRV_INFO_SZ = 0x04 */
	rtl_ग_लिखो_byte(rtlpriv, REG_RX_DRVINFO_SZ, 0x4);

	/* 18.  LLT_table_init(Adapter);  */
	क्रम (i = 0; i < (txpktbuf_bndy - 1); i++) अणु
		status = _rtl92de_llt_ग_लिखो(hw, i, i + 1);
		अगर (!status)
			वापस status;
	पूर्ण

	/* end of list */
	status = _rtl92de_llt_ग_लिखो(hw, (txpktbuf_bndy - 1), 0xFF);
	अगर (!status)
		वापस status;

	/* Make the other pages as ring buffer */
	/* This ring buffer is used as beacon buffer अगर we */
	/* config this MAC as two MAC transfer. */
	/* Otherwise used as local loopback buffer.  */
	क्रम (i = txpktbuf_bndy; i < maxpage; i++) अणु
		status = _rtl92de_llt_ग_लिखो(hw, i, (i + 1));
		अगर (!status)
			वापस status;
	पूर्ण

	/* Let last entry poपूर्णांक to the start entry of ring buffer */
	status = _rtl92de_llt_ग_लिखो(hw, maxpage, txpktbuf_bndy);
	अगर (!status)
		वापस status;

	वापस true;
पूर्ण

अटल व्योम _rtl92de_gen_refresh_led_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;

	अगर (rtlpci->up_first_समय)
		वापस;
	अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
		rtl92de_sw_led_on(hw, pled0);
	अन्यथा अगर (ppsc->rfoff_reason == RF_CHANGE_BY_INIT)
		rtl92de_sw_led_on(hw, pled0);
	अन्यथा
		rtl92de_sw_led_off(hw, pled0);
पूर्ण

अटल bool _rtl92de_init_mac(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	अचिन्हित अक्षर byteपंचांगp;
	अचिन्हित लघु wordपंचांगp;
	u16 retry;

	rtl92d_phy_set_घातeron(hw);
	/* Add क्रम resume sequence of घातer करोमुख्य according
	 * to घातer करोcument V11. Chapter V.11....  */
	/* 0.   RSV_CTRL 0x1C[7:0] = 0x00  */
	/* unlock ISO/CLK/Power control रेजिस्टर */
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x00);
	rtl_ग_लिखो_byte(rtlpriv, REG_LDOA15_CTRL, 0x05);

	/* 1.   AFE_XTAL_CTRL [7:0] = 0x0F  enable XTAL */
	/* 2.   SPS0_CTRL 0x11[7:0] = 0x2b  enable SPS पूर्णांकo PWM mode  */
	/* 3.   delay (1ms) this is not necessary when initially घातer on */

	/* C.   Resume Sequence */
	/* a.   SPS0_CTRL 0x11[7:0] = 0x2b */
	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x2b);

	/* b.   AFE_XTAL_CTRL [7:0] = 0x0F */
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_XTAL_CTRL, 0x0F);

	/* c.   DRV runs घातer on init flow */

	/* स्वतः enable WLAN */
	/* 4.   APS_FSMCO 0x04[8] = 1; रुको till 0x04[8] = 0   */
	/* Power On Reset क्रम MAC Block */
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO + 1) | BIT(0);
	udelay(2);
	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO + 1, byteपंचांगp);
	udelay(2);

	/* 5.   Wait जबतक 0x04[8] == 0 जाओ 2, otherwise जाओ 1 */
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO + 1);
	udelay(50);
	retry = 0;
	जबतक ((byteपंचांगp & BIT(0)) && retry < 1000) अणु
		retry++;
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO + 1);
		udelay(50);
	पूर्ण

	/* Enable Radio off, GPIO, and LED function */
	/* 6.   APS_FSMCO 0x04[15:0] = 0x0012  when enable HWPDN */
	rtl_ग_लिखो_word(rtlpriv, REG_APS_FSMCO, 0x1012);

	/* release RF digital isolation  */
	/* 7.  SYS_ISO_CTRL 0x01[1]    = 0x0;  */
	/*Set REG_SYS_ISO_CTRL 0x1=0x82 to prevent wake# problem. */
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL + 1, 0x82);
	udelay(2);

	/* make sure that BB reset OK. */
	/* rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3); */

	/* Disable REG_CR beक्रमe enable it to assure reset */
	rtl_ग_लिखो_word(rtlpriv, REG_CR, 0x0);

	/* Release MAC IO रेजिस्टर reset */
	rtl_ग_लिखो_word(rtlpriv, REG_CR, 0x2ff);

	/* clear stopping tx/rx dma   */
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0x0);

	/* rtl_ग_लिखो_word(rtlpriv,REG_CR+2, 0x2); */

	/* System init */
	/* 18.  LLT_table_init(Adapter);  */
	अगर (!_rtl92de_llt_table_init(hw))
		वापस false;

	/* Clear पूर्णांकerrupt and enable पूर्णांकerrupt */
	/* 19.  HISR 0x124[31:0] = 0xffffffff;  */
	/*      HISRE 0x12C[7:0] = 0xFF */
	rtl_ग_लिखो_dword(rtlpriv, REG_HISR, 0xffffffff);
	rtl_ग_लिखो_byte(rtlpriv, REG_HISRE, 0xff);

	/* 20.  HIMR 0x120[31:0] |= [enable INT mask bit map];  */
	/* 21.  HIMRE 0x128[7:0] = [enable INT mask bit map] */
	/* The IMR should be enabled later after all init sequence
	 * is finished. */

	/* 22.  PCIE configuration space configuration */
	/* 23.  Ensure PCIe Device 0x80[15:0] = 0x0143 (ASPM+CLKREQ),  */
	/*      and PCIe gated घड़ी function is enabled.    */
	/* PCIE configuration space will be written after
	 * all init sequence.(Or by BIOS) */

	rtl92d_phy_config_maccoexist_rfpage(hw);

	/* THe below section is not related to घातer करोcument Vxx . */
	/* This is only useful क्रम driver and OS setting. */
	/* -------------------Software Relative Setting---------------------- */
	wordपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_TRXDMA_CTRL);
	wordपंचांगp &= 0xf;
	wordपंचांगp |= 0xF771;
	rtl_ग_लिखो_word(rtlpriv, REG_TRXDMA_CTRL, wordपंचांगp);

	/* Reported Tx status from HW क्रम rate adaptive. */
	/* This should be realtive to घातer on step 14. But in करोcument V11  */
	/* still not contain the description.!!! */
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 1, 0x1F);

	/* Set Tx/Rx page size (Tx must be 128 Bytes,
	 * Rx can be 64,128,256,512,1024 bytes) */
	/* rtl_ग_लिखो_byte(rtlpriv,REG_PBP, 0x11); */

	/* Set RCR रेजिस्टर */
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);
	/* rtl_ग_लिखो_byte(rtlpriv,REG_RX_DRVINFO_SZ, 4); */

	/*  Set TCR रेजिस्टर */
	rtl_ग_लिखो_dword(rtlpriv, REG_TCR, rtlpci->transmit_config);

	/* disable earlymode */
	rtl_ग_लिखो_byte(rtlpriv, 0x4d0, 0x0);

	/* Set TX/RX descriptor physical address(from OS API). */
	rtl_ग_लिखो_dword(rtlpriv, REG_BCNQ_DESA,
			rtlpci->tx_ring[BEACON_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, REG_MGQ_DESA, rtlpci->tx_ring[MGNT_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, REG_VOQ_DESA, rtlpci->tx_ring[VO_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, REG_VIQ_DESA, rtlpci->tx_ring[VI_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, REG_BEQ_DESA, rtlpci->tx_ring[BE_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, REG_BKQ_DESA, rtlpci->tx_ring[BK_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, REG_HQ_DESA, rtlpci->tx_ring[HIGH_QUEUE].dma);
	/* Set RX Desc Address */
	rtl_ग_लिखो_dword(rtlpriv, REG_RX_DESA,
			rtlpci->rx_ring[RX_MPDU_QUEUE].dma);

	/* अगर we want to support 64 bit DMA, we should set it here,
	 * but now we करो not support 64 bit DMA*/

	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 3, 0x33);

	/* Reset पूर्णांकerrupt migration setting when initialization */
	rtl_ग_लिखो_dword(rtlpriv, REG_INT_MIG, 0);

	/* Reconsider when to करो this operation after asking HWSD. */
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APSD_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, byteपंचांगp & ~BIT(6));
	करो अणु
		retry++;
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APSD_CTRL);
	पूर्ण जबतक ((retry < 200) && !(byteपंचांगp & BIT(7)));

	/* After MACIO reset,we must refresh LED state. */
	_rtl92de_gen_refresh_led_state(hw);

	/* Reset H2C protection रेजिस्टर */
	rtl_ग_लिखो_dword(rtlpriv, REG_MCUTST_1, 0x0);

	वापस true;
पूर्ण

अटल व्योम _rtl92de_hw_configure(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 reg_bw_opmode = BW_OPMODE_20MHZ;
	u32 reg_rrsr;

	reg_rrsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
	rtl_ग_लिखो_byte(rtlpriv, REG_INIRTS_RATE_SEL, 0x8);
	rtl_ग_लिखो_byte(rtlpriv, REG_BWOPMODE, reg_bw_opmode);
	rtl_ग_लिखो_dword(rtlpriv, REG_RRSR, reg_rrsr);
	rtl_ग_लिखो_byte(rtlpriv, REG_SLOT, 0x09);
	rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE, 0x0);
	rtl_ग_लिखो_word(rtlpriv, REG_FWHW_TXQ_CTRL, 0x1F80);
	rtl_ग_लिखो_word(rtlpriv, REG_RL, 0x0707);
	rtl_ग_लिखो_dword(rtlpriv, REG_BAR_MODE_CTRL, 0x02012802);
	rtl_ग_लिखो_byte(rtlpriv, REG_HWSEQ_CTRL, 0xFF);
	rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC, 0x01000000);
	rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4, 0x07060504);
	rtl_ग_लिखो_dword(rtlpriv, REG_RARFRC, 0x01000000);
	rtl_ग_लिखो_dword(rtlpriv, REG_RARFRC + 4, 0x07060504);
	/* Aggregation threshold */
	अगर (rtlhal->macphymode == DUALMAC_DUALPHY)
		rtl_ग_लिखो_dword(rtlpriv, REG_AGGLEN_LMT, 0xb9726641);
	अन्यथा अगर (rtlhal->macphymode == DUALMAC_SINGLEPHY)
		rtl_ग_लिखो_dword(rtlpriv, REG_AGGLEN_LMT, 0x66626641);
	अन्यथा
		rtl_ग_लिखो_dword(rtlpriv, REG_AGGLEN_LMT, 0xb972a841);
	rtl_ग_लिखो_byte(rtlpriv, REG_ATIMWND, 0x2);
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_MAX_ERR, 0x0a);
	rtlpci->reg_bcn_ctrl_val = 0x1f;
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, rtlpci->reg_bcn_ctrl_val);
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);
	rtl_ग_लिखो_byte(rtlpriv, REG_PIFS, 0x1C);
	rtl_ग_लिखो_byte(rtlpriv, REG_AGGR_BREAK_TIME, 0x16);
	rtl_ग_लिखो_word(rtlpriv, REG_NAV_PROT_LEN, 0x0020);
	/* For throughput */
	rtl_ग_लिखो_word(rtlpriv, REG_FAST_EDCA_CTRL, 0x6666);
	/* ACKTO क्रम IOT issue. */
	rtl_ग_लिखो_byte(rtlpriv, REG_ACKTO, 0x40);
	/* Set Spec SIFS (used in NAV) */
	rtl_ग_लिखो_word(rtlpriv, REG_SPEC_SIFS, 0x1010);
	rtl_ग_लिखो_word(rtlpriv, REG_MAC_SPEC_SIFS, 0x1010);
	/* Set SIFS क्रम CCK */
	rtl_ग_लिखो_word(rtlpriv, REG_SIFS_CTX, 0x1010);
	/* Set SIFS क्रम OFDM */
	rtl_ग_लिखो_word(rtlpriv, REG_SIFS_TRX, 0x1010);
	/* Set Multicast Address. */
	rtl_ग_लिखो_dword(rtlpriv, REG_MAR, 0xffffffff);
	rtl_ग_लिखो_dword(rtlpriv, REG_MAR + 4, 0xffffffff);
	चयन (rtlpriv->phy.rf_type) अणु
	हाल RF_1T2R:
	हाल RF_1T1R:
		rtlhal->minspace_cfg = (MAX_MSS_DENSITY_1T << 3);
		अवरोध;
	हाल RF_2T2R:
	हाल RF_2T2R_GREEN:
		rtlhal->minspace_cfg = (MAX_MSS_DENSITY_2T << 3);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl92de_enable_aspm_back_करोor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	rtl_ग_लिखो_byte(rtlpriv, 0x34b, 0x93);
	rtl_ग_लिखो_word(rtlpriv, 0x350, 0x870c);
	rtl_ग_लिखो_byte(rtlpriv, 0x352, 0x1);
	अगर (ppsc->support_backकरोor)
		rtl_ग_लिखो_byte(rtlpriv, 0x349, 0x1b);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, 0x349, 0x03);
	rtl_ग_लिखो_word(rtlpriv, 0x350, 0x2718);
	rtl_ग_लिखो_byte(rtlpriv, 0x352, 0x1);
पूर्ण

व्योम rtl92de_enable_hw_security_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 sec_reg_value;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"PairwiseEncAlgorithm = %d GroupEncAlgorithm = %d\n",
		rtlpriv->sec.pairwise_enc_algorithm,
		rtlpriv->sec.group_enc_algorithm);
	अगर (rtlpriv->cfg->mod_params->sw_crypto || rtlpriv->sec.use_sw_sec) अणु
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
			"not open hw encryption\n");
		वापस;
	पूर्ण
	sec_reg_value = SCR_TXENCENABLE | SCR_RXENCENABLE;
	अगर (rtlpriv->sec.use_शेषkey) अणु
		sec_reg_value |= SCR_TXUSEDK;
		sec_reg_value |= SCR_RXUSEDK;
	पूर्ण
	sec_reg_value |= (SCR_RXBCUSEDK | SCR_TXBCUSEDK);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, 0x02);
	rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
		"The SECR-value %x\n", sec_reg_value);
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_WPA_CONFIG, &sec_reg_value);
पूर्ण

पूर्णांक rtl92de_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool rtstatus = true;
	u8 पंचांगp_u1b;
	पूर्णांक i;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	rtlpci->being_init_adapter = true;
	rtlpci->init_पढ़ोy = false;
	spin_lock_irqsave(&globalmutex_क्रम_घातer_and_efuse, flags);
	/* we should करो iqk after disable/enable */
	rtl92d_phy_reset_iqk_result(hw);
	/* rtlpriv->पूर्णांकf_ops->disable_aspm(hw); */
	rtstatus = _rtl92de_init_mac(hw);
	अगर (!rtstatus) अणु
		pr_err("Init MAC failed\n");
		err = 1;
		spin_unlock_irqrestore(&globalmutex_क्रम_घातer_and_efuse, flags);
		वापस err;
	पूर्ण
	err = rtl92d_करोwnload_fw(hw);
	spin_unlock_irqrestore(&globalmutex_क्रम_घातer_and_efuse, flags);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Failed to download FW. Init HW without FW..\n");
		वापस 1;
	पूर्ण
	rtlhal->last_hmeboxnum = 0;
	rtlpriv->psc.fw_current_inpsmode = false;

	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, 0x605);
	पंचांगp_u1b = पंचांगp_u1b | 0x30;
	rtl_ग_लिखो_byte(rtlpriv, 0x605, पंचांगp_u1b);

	अगर (rtlhal->earlymode_enable) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"EarlyMode Enabled!!!\n");

		पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, 0x4d0);
		पंचांगp_u1b = पंचांगp_u1b | 0x1f;
		rtl_ग_लिखो_byte(rtlpriv, 0x4d0, पंचांगp_u1b);

		rtl_ग_लिखो_byte(rtlpriv, 0x4d3, 0x80);

		पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, 0x605);
		पंचांगp_u1b = पंचांगp_u1b | 0x40;
		rtl_ग_लिखो_byte(rtlpriv, 0x605, पंचांगp_u1b);
	पूर्ण

	अगर (mac->rdg_en) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_RD_CTRL, 0xff);
		rtl_ग_लिखो_word(rtlpriv, REG_RD_NAV_NXT, 0x200);
		rtl_ग_लिखो_byte(rtlpriv, REG_RD_RESP_PKT_TH, 0x05);
	पूर्ण

	rtl92d_phy_mac_config(hw);
	/* because last function modअगरy RCR, so we update
	 * rcr var here, or TP will unstable क्रम receive_config
	 * is wrong, RX RCR_ACRC32 will cause TP unstabel & Rx
	 * RCR_APP_ICV will cause mac80211 unassoc क्रम cisco 1252*/
	rtlpci->receive_config = rtl_पढ़ो_dword(rtlpriv, REG_RCR);
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);

	rtl92d_phy_bb_config(hw);

	rtlphy->rf_mode = RF_OP_BY_SW_3WIRE;
	/* set beक्रमe initialize RF */
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0x00f00000, 0xf);

	/* config RF */
	rtl92d_phy_rf_config(hw);

	/* After पढ़ो predefined TXT, we must set BB/MAC/RF
	 * रेजिस्टर as our requirement */
	/* After load BB,RF params,we need करो more क्रम 92D. */
	rtl92d_update_bbrf_configuration(hw);
	/* set शेष value after initialize RF,  */
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0x00f00000, 0);
	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, (क्रमागत radio_path)0,
			RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl_get_rfreg(hw, (क्रमागत radio_path)1,
			RF_CHNLBW, RFREG_OFFSET_MASK);

	/*---- Set CCK and OFDM Block "ON"----*/
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G)
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);
	अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
		/* RFPGA0_ANALOGPARAMETER2: cck घड़ी select,
		 *  set to 20MHz by शेष */
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10) |
			      BIT(11), 3);
	पूर्ण अन्यथा अणु
		/* Mac1 */
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(11) |
			      BIT(10), 3);
	पूर्ण

	_rtl92de_hw_configure(hw);

	/* reset hw sec */
	rtl_cam_reset_all_entry(hw);
	rtl92de_enable_hw_security_config(hw);

	/* Read EEPROM TX घातer index and PHY_REG_PG.txt to capture correct */
	/* TX घातer index क्रम dअगरferent rate set. */
	rtl92d_phy_get_hw_reg_originalvalue(hw);
	rtl92d_phy_set_txघातer_level(hw, rtlphy->current_channel);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);

	_rtl92de_enable_aspm_back_करोor(hw);
	/* rtlpriv->पूर्णांकf_ops->enable_aspm(hw); */

	rtl92d_dm_init(hw);
	rtlpci->being_init_adapter = false;

	अगर (ppsc->rfpwr_state == ERFON) अणु
		rtl92d_phy_lc_calibrate(hw);
		/* 5G and 2.4G must रुको someसमय to let RF LO पढ़ोy */
		अगर (rtlhal->macphymode == DUALMAC_DUALPHY) अणु
			u32 पंचांगp_rega;
			क्रम (i = 0; i < 10000; i++) अणु
				udelay(MAX_STALL_TIME);

				पंचांगp_rega = rtl_get_rfreg(hw,
						  (क्रमागत radio_path)RF90_PATH_A,
						  0x2a, MASKDWORD);

				अगर (((पंचांगp_rega & BIT(11)) == BIT(11)))
					अवरोध;
			पूर्ण
			/* check that loop was successful. If not, निकास now */
			अगर (i == 10000) अणु
				rtlpci->init_पढ़ोy = false;
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	rtlpci->init_पढ़ोy = true;
	वापस err;
पूर्ण

अटल क्रमागत version_8192d _rtl92de_पढ़ो_chip_version(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	क्रमागत version_8192d version = VERSION_NORMAL_CHIP_92D_SINGLEPHY;
	u32 value32;

	value32 = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG);
	अगर (!(value32 & 0x000f0000)) अणु
		version = VERSION_TEST_CHIP_92D_SINGLEPHY;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "TEST CHIP!!!\n");
	पूर्ण अन्यथा अणु
		version = VERSION_NORMAL_CHIP_92D_SINGLEPHY;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Normal CHIP!!!\n");
	पूर्ण
	वापस version;
पूर्ण

अटल पूर्णांक _rtl92de_set_media_status(काष्ठा ieee80211_hw *hw,
				     क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_msr = rtl_पढ़ो_byte(rtlpriv, MSR);
	क्रमागत led_ctl_mode ledaction = LED_CTL_NO_LINK;
	u8 bcnfunc_enable;

	bt_msr &= 0xfc;

	अगर (type == NL80211_IFTYPE_UNSPECIFIED ||
	    type == NL80211_IFTYPE_STATION) अणु
		_rtl92de_stop_tx_beacon(hw);
		_rtl92de_enable_bcn_sub_func(hw);
	पूर्ण अन्यथा अगर (type == NL80211_IFTYPE_ADHOC ||
		type == NL80211_IFTYPE_AP) अणु
		_rtl92de_resume_tx_beacon(hw);
		_rtl92de_disable_bcn_sub_func(hw);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Set HW_VAR_MEDIA_STATUS: No such media status(%x)\n",
			type);
	पूर्ण
	bcnfunc_enable = rtl_पढ़ो_byte(rtlpriv, REG_BCN_CTRL);
	चयन (type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		bt_msr |= MSR_NOLINK;
		ledaction = LED_CTL_LINK;
		bcnfunc_enable &= 0xF7;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to NO LINK!\n");
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		bt_msr |= MSR_ADHOC;
		bcnfunc_enable |= 0x08;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to Ad Hoc!\n");
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		bt_msr |= MSR_INFRA;
		ledaction = LED_CTL_LINK;
		bcnfunc_enable &= 0xF7;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to STA!\n");
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		bt_msr |= MSR_AP;
		bcnfunc_enable |= 0x08;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to AP!\n");
		अवरोध;
	शेष:
		pr_err("Network type %d not supported!\n", type);
		वापस 1;
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, MSR, bt_msr);
	rtlpriv->cfg->ops->led_control(hw, ledaction);
	अगर ((bt_msr & MSR_MASK) == MSR_AP)
		rtl_ग_लिखो_byte(rtlpriv, REG_BCNTCFG + 1, 0x00);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, REG_BCNTCFG + 1, 0x66);
	वापस 0;
पूर्ण

व्योम rtl92de_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 reg_rcr;

	अगर (rtlpriv->psc.rfpwr_state != ERFON)
		वापस;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RCR, (u8 *)(&reg_rcr));

	अगर (check_bssid) अणु
		reg_rcr |= (RCR_CBSSID_DATA | RCR_CBSSID_BCN);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR, (u8 *)(&reg_rcr));
		_rtl92de_set_bcn_ctrl_reg(hw, 0, BIT(4));
	पूर्ण अन्यथा अगर (!check_bssid) अणु
		reg_rcr &= (~(RCR_CBSSID_DATA | RCR_CBSSID_BCN));
		_rtl92de_set_bcn_ctrl_reg(hw, BIT(4), 0);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR, (u8 *)(&reg_rcr));
	पूर्ण
पूर्ण

पूर्णांक rtl92de_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (_rtl92de_set_media_status(hw, type))
		वापस -EOPNOTSUPP;

	/* check bssid */
	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		अगर (type != NL80211_IFTYPE_AP)
			rtl92de_set_check_bssid(hw, true);
	पूर्ण अन्यथा अणु
		rtl92de_set_check_bssid(hw, false);
	पूर्ण
	वापस 0;
पूर्ण

/* करो iqk or reload iqk */
/* winकरोws just rtl92d_phy_reload_iqk_setting in set channel,
 * but it's very strict क्रम समय sequence so we add
 * rtl92d_phy_reload_iqk_setting here */
व्योम rtl92d_linked_set_reg(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 indexक्रमchannel;
	u8 channel = rtlphy->current_channel;

	indexक्रमchannel = rtl92d_get_rightchnlplace_क्रम_iqk(channel);
	अगर (!rtlphy->iqk_matrix[indexक्रमchannel].iqk_करोne) अणु
		rtl_dbg(rtlpriv, COMP_SCAN | COMP_INIT, DBG_DMESG,
			"Do IQK for channel:%d\n", channel);
		rtl92d_phy_iq_calibrate(hw);
	पूर्ण
पूर्ण

/* करोn't set REG_EDCA_BE_PARAM here because
 * mac80211 will send pkt when scan */
व्योम rtl92de_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci)
अणु
	rtl92d_dm_init_edca_turbo(hw);
पूर्ण

व्योम rtl92de_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, rtlpci->irq_mask[0] & 0xFFFFFFFF);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, rtlpci->irq_mask[1] & 0xFFFFFFFF);
	rtlpci->irq_enabled = true;
पूर्ण

व्योम rtl92de_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, IMR8190_DISABLED);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, IMR8190_DISABLED);
	rtlpci->irq_enabled = false;
पूर्ण

अटल व्योम _rtl92de_घातeroff_adapter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1b_पंचांगp;
	अचिन्हित दीर्घ flags;

	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);
	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, 0x00);
	rtl_set_bbreg(hw, RFPGA0_XCD_RFPARAMETER, BIT(3), 0);
	rtl_set_bbreg(hw, RFPGA0_XCD_RFPARAMETER, BIT(15), 0);

	/* 0x20:value 05-->04 */
	rtl_ग_लिखो_byte(rtlpriv, REG_LDOA15_CTRL, 0x04);

	/*  ==== Reset digital sequence   ====== */
	rtl92d_firmware_selfreset(hw);

	/* f.   SYS_FUNC_EN 0x03[7:0]=0x51 reset MCU, MAC रेजिस्टर, DCORE */
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, 0x51);

	/* g.   MCUFWDL 0x80[1:0]=0 reset MCU पढ़ोy status */
	rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0x00);

	/*  ==== Pull GPIO PIN to balance level and LED control ====== */

	/* h.     GPIO_PIN_CTRL 0x44[31:0]=0x000  */
	rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL, 0x00000000);

	/* i.    Value = GPIO_PIN_CTRL[7:0] */
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_PIN_CTRL);

	/* j.    GPIO_PIN_CTRL 0x44[31:0] = 0x00FF0000 | (value <<8); */
	/* ग_लिखो बाह्यal PIN level  */
	rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL,
			0x00FF0000 | (u1b_पंचांगp << 8));

	/* k.   GPIO_MUXCFG 0x42 [15:0] = 0x0780 */
	rtl_ग_लिखो_word(rtlpriv, REG_GPIO_IO_SEL, 0x0790);

	/* l.   LEDCFG 0x4C[15:0] = 0x8080 */
	rtl_ग_लिखो_word(rtlpriv, REG_LEDCFG0, 0x8080);

	/*  ==== Disable analog sequence === */

	/* m.   AFE_PLL_CTRL[7:0] = 0x80  disable PLL */
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_PLL_CTRL, 0x80);

	/* n.   SPS0_CTRL 0x11[7:0] = 0x22  enter PFM mode */
	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x23);

	/* o.   AFE_XTAL_CTRL 0x24[7:0] = 0x0E  disable XTAL, अगर No BT COEX */
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_XTAL_CTRL, 0x0e);

	/* p.   RSV_CTRL 0x1C[7:0] = 0x0E lock ISO/CLK/Power control रेजिस्टर */
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0e);

	/*  ==== पूर्णांकerface पूर्णांकo suspend === */

	/* q.   APS_FSMCO[15:8] = 0x58 PCIe suspend mode */
	/* According to घातer करोcument V11, we need to set this */
	/* value as 0x18. Otherwise, we may not L0s someबार. */
	/* This indluences घातer consumption. Bases on SD1's test, */
	/* set as 0x00 करो not affect घातer current. And अगर it */
	/* is set as 0x18, they had ever met स्वतः load fail problem. */
	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO + 1, 0x10);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"In PowerOff,reg0x%x=%X\n",
		REG_SPS0_CTRL, rtl_पढ़ो_byte(rtlpriv, REG_SPS0_CTRL));
	/* r.   Note: क्रम PCIe पूर्णांकerface, PON will not turn */
	/* off m-bias and BandGap in PCIe suspend mode.  */

	/* 0x17[7] 1b': power off in process  0b' : घातer off over */
	अगर (rtlpriv->rtlhal.macphymode != SINGLEMAC_SINGLEPHY) अणु
		spin_lock_irqsave(&globalmutex_घातer, flags);
		u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_POWER_OFF_IN_PROCESS);
		u1b_पंचांगp &= (~BIT(7));
		rtl_ग_लिखो_byte(rtlpriv, REG_POWER_OFF_IN_PROCESS, u1b_पंचांगp);
		spin_unlock_irqrestore(&globalmutex_घातer, flags);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "<=======\n");
पूर्ण

व्योम rtl92de_card_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	क्रमागत nl80211_अगरtype opmode;

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;
	_rtl92de_set_media_status(hw, opmode);

	अगर (rtlpci->driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);
	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
	/* Power sequence क्रम each MAC. */
	/* a. stop tx DMA  */
	/* b. बंद RF */
	/* c. clear rx buf */
	/* d. stop rx DMA */
	/* e.  reset MAC */

	/* a. stop tx DMA */
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xFE);
	udelay(50);

	/* b. TXPAUSE 0x522[7:0] = 0xFF Pause MAC TX queue */

	/* c. ========RF OFF sequence==========  */
	/* 0x88c[23:20] = 0xf. */
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0x00f00000, 0xf);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);

	/* APSD_CTRL 0x600[7:0] = 0x40 */
	rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, 0x40);

	/* Close antenna 0,0xc04,0xd04 */
	rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE, MASKBYTE0, 0);
	rtl_set_bbreg(hw, ROFDM1_TRXPATHENABLE, BDWORD, 0);

	/*  SYS_FUNC_EN 0x02[7:0] = 0xE2   reset BB state machine */
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);

	/* Mac0 can not करो Global reset. Mac1 can करो. */
	/* SYS_FUNC_EN 0x02[7:0] = 0xE0  reset BB state machine  */
	अगर (rtlpriv->rtlhal.पूर्णांकerfaceindex == 1)
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE0);
	udelay(50);

	/* d.  stop tx/rx dma beक्रमe disable REG_CR (0x100) to fix */
	/* dma hang issue when disable/enable device.  */
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xff);
	udelay(50);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR, 0x0);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "==> Do power off.......\n");
	अगर (rtl92d_phy_check_घातeroff(hw))
		_rtl92de_घातeroff_adapter(hw);
	वापस;
पूर्ण

व्योम rtl92de_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_पूर्णांक *पूर्णांकvec)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	पूर्णांकvec->पूर्णांकa = rtl_पढ़ो_dword(rtlpriv, ISR) & rtlpci->irq_mask[0];
	rtl_ग_लिखो_dword(rtlpriv, ISR, पूर्णांकvec->पूर्णांकa);
पूर्ण

व्योम rtl92de_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval, atim_winकरोw;

	bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;
	atim_winकरोw = 2;
	rtl92de_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_ATIMWND, atim_winकरोw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl_ग_लिखो_word(rtlpriv, REG_BCNTCFG, 0x660f);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_CCK, 0x20);
	अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_5G)
		rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x30);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x20);
	rtl_ग_लिखो_byte(rtlpriv, 0x606, 0x30);
पूर्ण

व्योम rtl92de_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;

	rtl_dbg(rtlpriv, COMP_BEACON, DBG_DMESG,
		"beacon_interval:%d\n", bcn_पूर्णांकerval);
	rtl92de_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl92de_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl92de_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
				   u32 add_msr, u32 rm_msr)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_dbg(rtlpriv, COMP_INTR, DBG_LOUD, "add_msr:%x, rm_msr:%x\n",
		add_msr, rm_msr);
	अगर (add_msr)
		rtlpci->irq_mask[0] |= add_msr;
	अगर (rm_msr)
		rtlpci->irq_mask[0] &= (~rm_msr);
	rtl92de_disable_पूर्णांकerrupt(hw);
	rtl92de_enable_पूर्णांकerrupt(hw);
पूर्ण

अटल व्योम _rtl92de_पढ़ोघातervalue_fromprom(काष्ठा txघातer_info *pwrinfo,
				 u8 *rom_content, bool स्वतःloadfail)
अणु
	u32 rfpath, eeaddr, group, offset1, offset2;
	u8 i;

	स_रखो(pwrinfo, 0, माप(काष्ठा txघातer_info));
	अगर (स्वतःloadfail) अणु
		क्रम (group = 0; group < CHANNEL_GROUP_MAX; group++) अणु
			क्रम (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) अणु
				अगर (group < CHANNEL_GROUP_MAX_2G) अणु
					pwrinfo->cck_index[rfpath][group] =
					    EEPROM_DEFAULT_TXPOWERLEVEL_2G;
					pwrinfo->ht40_1sindex[rfpath][group] =
					    EEPROM_DEFAULT_TXPOWERLEVEL_2G;
				पूर्ण अन्यथा अणु
					pwrinfo->ht40_1sindex[rfpath][group] =
					    EEPROM_DEFAULT_TXPOWERLEVEL_5G;
				पूर्ण
				pwrinfo->ht40_2sindexdअगरf[rfpath][group] =
				    EEPROM_DEFAULT_HT40_2SDIFF;
				pwrinfo->ht20indexdअगरf[rfpath][group] =
				    EEPROM_DEFAULT_HT20_DIFF;
				pwrinfo->ofdmindexdअगरf[rfpath][group] =
				    EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF;
				pwrinfo->ht40maxoffset[rfpath][group] =
				    EEPROM_DEFAULT_HT40_PWRMAXOFFSET;
				pwrinfo->ht20maxoffset[rfpath][group] =
				    EEPROM_DEFAULT_HT20_PWRMAXOFFSET;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < 3; i++) अणु
			pwrinfo->tssi_a[i] = EEPROM_DEFAULT_TSSI;
			pwrinfo->tssi_b[i] = EEPROM_DEFAULT_TSSI;
		पूर्ण
		वापस;
	पूर्ण

	/* Maybe स्वतःload OK,buf the tx घातer index value is not filled.
	 * If we find it, we set it to शेष value. */
	क्रम (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) अणु
		क्रम (group = 0; group < CHANNEL_GROUP_MAX_2G; group++) अणु
			eeaddr = EEPROM_CCK_TX_PWR_INX_2G + (rfpath * 3)
				 + group;
			pwrinfo->cck_index[rfpath][group] =
					(rom_content[eeaddr] == 0xFF) ?
					     (eeaddr > 0x7B ?
					     EEPROM_DEFAULT_TXPOWERLEVEL_5G :
					     EEPROM_DEFAULT_TXPOWERLEVEL_2G) :
					     rom_content[eeaddr];
		पूर्ण
	पूर्ण
	क्रम (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) अणु
		क्रम (group = 0; group < CHANNEL_GROUP_MAX; group++) अणु
			offset1 = group / 3;
			offset2 = group % 3;
			eeaddr = EEPROM_HT40_1S_TX_PWR_INX_2G + (rfpath * 3) +
			    offset2 + offset1 * 21;
			pwrinfo->ht40_1sindex[rfpath][group] =
			    (rom_content[eeaddr] == 0xFF) ? (eeaddr > 0x7B ?
					     EEPROM_DEFAULT_TXPOWERLEVEL_5G :
					     EEPROM_DEFAULT_TXPOWERLEVEL_2G) :
						 rom_content[eeaddr];
		पूर्ण
	पूर्ण
	/* These just क्रम 92D efuse offset. */
	क्रम (group = 0; group < CHANNEL_GROUP_MAX; group++) अणु
		क्रम (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) अणु
			पूर्णांक base1 = EEPROM_HT40_2S_TX_PWR_INX_DIFF_2G;

			offset1 = group / 3;
			offset2 = group % 3;

			अगर (rom_content[base1 + offset2 + offset1 * 21] != 0xFF)
				pwrinfo->ht40_2sindexdअगरf[rfpath][group] =
				    (rom_content[base1 +
				     offset2 + offset1 * 21] >> (rfpath * 4))
				     & 0xF;
			अन्यथा
				pwrinfo->ht40_2sindexdअगरf[rfpath][group] =
				    EEPROM_DEFAULT_HT40_2SDIFF;
			अगर (rom_content[EEPROM_HT20_TX_PWR_INX_DIFF_2G + offset2
			    + offset1 * 21] != 0xFF)
				pwrinfo->ht20indexdअगरf[rfpath][group] =
				    (rom_content[EEPROM_HT20_TX_PWR_INX_DIFF_2G
				    + offset2 + offset1 * 21] >> (rfpath * 4))
				    & 0xF;
			अन्यथा
				pwrinfo->ht20indexdअगरf[rfpath][group] =
				    EEPROM_DEFAULT_HT20_DIFF;
			अगर (rom_content[EEPROM_OFDM_TX_PWR_INX_DIFF_2G + offset2
			    + offset1 * 21] != 0xFF)
				pwrinfo->ofdmindexdअगरf[rfpath][group] =
				    (rom_content[EEPROM_OFDM_TX_PWR_INX_DIFF_2G
				     + offset2 + offset1 * 21] >> (rfpath * 4))
				     & 0xF;
			अन्यथा
				pwrinfo->ofdmindexdअगरf[rfpath][group] =
				    EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF;
			अगर (rom_content[EEPROM_HT40_MAX_PWR_OFFSET_2G + offset2
			    + offset1 * 21] != 0xFF)
				pwrinfo->ht40maxoffset[rfpath][group] =
				    (rom_content[EEPROM_HT40_MAX_PWR_OFFSET_2G
				    + offset2 + offset1 * 21] >> (rfpath * 4))
				    & 0xF;
			अन्यथा
				pwrinfo->ht40maxoffset[rfpath][group] =
				    EEPROM_DEFAULT_HT40_PWRMAXOFFSET;
			अगर (rom_content[EEPROM_HT20_MAX_PWR_OFFSET_2G + offset2
			    + offset1 * 21] != 0xFF)
				pwrinfo->ht20maxoffset[rfpath][group] =
				    (rom_content[EEPROM_HT20_MAX_PWR_OFFSET_2G +
				     offset2 + offset1 * 21] >> (rfpath * 4)) &
				     0xF;
			अन्यथा
				pwrinfo->ht20maxoffset[rfpath][group] =
				    EEPROM_DEFAULT_HT20_PWRMAXOFFSET;
		पूर्ण
	पूर्ण
	अगर (rom_content[EEPROM_TSSI_A_5G] != 0xFF) अणु
		/* 5GL */
		pwrinfo->tssi_a[0] = rom_content[EEPROM_TSSI_A_5G] & 0x3F;
		pwrinfo->tssi_b[0] = rom_content[EEPROM_TSSI_B_5G] & 0x3F;
		/* 5GM */
		pwrinfo->tssi_a[1] = rom_content[EEPROM_TSSI_AB_5G] & 0x3F;
		pwrinfo->tssi_b[1] =
		    (rom_content[EEPROM_TSSI_AB_5G] & 0xC0) >> 6 |
		    (rom_content[EEPROM_TSSI_AB_5G + 1] & 0x0F) << 2;
		/* 5GH */
		pwrinfo->tssi_a[2] = (rom_content[EEPROM_TSSI_AB_5G + 1] &
				      0xF0) >> 4 |
		    (rom_content[EEPROM_TSSI_AB_5G + 2] & 0x03) << 4;
		pwrinfo->tssi_b[2] = (rom_content[EEPROM_TSSI_AB_5G + 2] &
				      0xFC) >> 2;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 3; i++) अणु
			pwrinfo->tssi_a[i] = EEPROM_DEFAULT_TSSI;
			pwrinfo->tssi_b[i] = EEPROM_DEFAULT_TSSI;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92de_पढ़ो_txघातer_info(काष्ठा ieee80211_hw *hw,
				       bool स्वतःload_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा txघातer_info pwrinfo;
	u8 tempval[2], i, pwr, dअगरf;
	u32 ch, rfpath, group;

	_rtl92de_पढ़ोघातervalue_fromprom(&pwrinfo, hwinfo, स्वतःload_fail);
	अगर (!स्वतःload_fail) अणु
		/* bit0~2 */
		rtlefuse->eeprom_regulatory = (hwinfo[EEPROM_RF_OPT1] & 0x7);
		rtlefuse->eeprom_thermalmeter =
			 hwinfo[EEPROM_THERMAL_METER] & 0x1f;
		rtlefuse->crystalcap = hwinfo[EEPROM_XTAL_K];
		tempval[0] = hwinfo[EEPROM_IQK_DELTA] & 0x03;
		tempval[1] = (hwinfo[EEPROM_LCK_DELTA] & 0x0C) >> 2;
		rtlefuse->txpwr_fromeprom = true;
		अगर (IS_92D_D_CUT(rtlpriv->rtlhal.version) ||
		    IS_92D_E_CUT(rtlpriv->rtlhal.version)) अणु
			rtlefuse->पूर्णांकernal_pa_5g[0] =
				!((hwinfo[EEPROM_TSSI_A_5G] & BIT(6)) >> 6);
			rtlefuse->पूर्णांकernal_pa_5g[1] =
				!((hwinfo[EEPROM_TSSI_B_5G] & BIT(6)) >> 6);
			rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
				"Is D cut,Internal PA0 %d Internal PA1 %d\n",
				rtlefuse->पूर्णांकernal_pa_5g[0],
				rtlefuse->पूर्णांकernal_pa_5g[1]);
		पूर्ण
		rtlefuse->eeprom_c9 = hwinfo[EEPROM_RF_OPT6];
		rtlefuse->eeprom_cc = hwinfo[EEPROM_RF_OPT7];
	पूर्ण अन्यथा अणु
		rtlefuse->eeprom_regulatory = 0;
		rtlefuse->eeprom_thermalmeter = EEPROM_DEFAULT_THERMALMETER;
		rtlefuse->crystalcap = EEPROM_DEFAULT_CRYSTALCAP;
		tempval[0] = tempval[1] = 3;
	पूर्ण

	/* Use शेष value to fill parameters अगर
	 * efuse is not filled on some place. */

	/* ThermalMeter from EEPROM */
	अगर (rtlefuse->eeprom_thermalmeter < 0x06 ||
	    rtlefuse->eeprom_thermalmeter > 0x1c)
		rtlefuse->eeprom_thermalmeter = 0x12;
	rtlefuse->thermalmeter[0] = rtlefuse->eeprom_thermalmeter;

	/* check XTAL_K */
	अगर (rtlefuse->crystalcap == 0xFF)
		rtlefuse->crystalcap = 0;
	अगर (rtlefuse->eeprom_regulatory > 3)
		rtlefuse->eeprom_regulatory = 0;

	क्रम (i = 0; i < 2; i++) अणु
		चयन (tempval[i]) अणु
		हाल 0:
			tempval[i] = 5;
			अवरोध;
		हाल 1:
			tempval[i] = 4;
			अवरोध;
		हाल 2:
			tempval[i] = 3;
			अवरोध;
		हाल 3:
		शेष:
			tempval[i] = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	rtlefuse->delta_iqk = tempval[0];
	अगर (tempval[1] > 0)
		rtlefuse->delta_lck = tempval[1] - 1;
	अगर (rtlefuse->eeprom_c9 == 0xFF)
		rtlefuse->eeprom_c9 = 0x00;
	rtl_dbg(rtlpriv, COMP_INTR, DBG_LOUD,
		"EEPROMRegulatory = 0x%x\n", rtlefuse->eeprom_regulatory);
	rtl_dbg(rtlpriv, COMP_INTR, DBG_LOUD,
		"ThermalMeter = 0x%x\n", rtlefuse->eeprom_thermalmeter);
	rtl_dbg(rtlpriv, COMP_INTR, DBG_LOUD,
		"CrystalCap = 0x%x\n", rtlefuse->crystalcap);
	rtl_dbg(rtlpriv, COMP_INTR, DBG_LOUD,
		"Delta_IQK = 0x%x Delta_LCK = 0x%x\n",
		rtlefuse->delta_iqk, rtlefuse->delta_lck);

	क्रम (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) अणु
		क्रम (ch = 0; ch < CHANNEL_MAX_NUMBER; ch++) अणु
			group = rtl92d_get_chnlgroup_fromarray((u8) ch);
			अगर (ch < CHANNEL_MAX_NUMBER_2G)
				rtlefuse->txpwrlevel_cck[rfpath][ch] =
				    pwrinfo.cck_index[rfpath][group];
			rtlefuse->txpwrlevel_ht40_1s[rfpath][ch] =
				    pwrinfo.ht40_1sindex[rfpath][group];
			rtlefuse->txpwr_ht20dअगरf[rfpath][ch] =
				    pwrinfo.ht20indexdअगरf[rfpath][group];
			rtlefuse->txpwr_legacyhtdअगरf[rfpath][ch] =
				    pwrinfo.ofdmindexdअगरf[rfpath][group];
			rtlefuse->pwrgroup_ht20[rfpath][ch] =
				    pwrinfo.ht20maxoffset[rfpath][group];
			rtlefuse->pwrgroup_ht40[rfpath][ch] =
				    pwrinfo.ht40maxoffset[rfpath][group];
			pwr = pwrinfo.ht40_1sindex[rfpath][group];
			dअगरf = pwrinfo.ht40_2sindexdअगरf[rfpath][group];
			rtlefuse->txpwrlevel_ht40_2s[rfpath][ch] =
				    (pwr > dअगरf) ? (pwr - dअगरf) : 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92de_पढ़ो_macphymode_from_prom(काष्ठा ieee80211_hw *hw,
					       u8 *content)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 macphy_crvalue = content[EEPROM_MAC_FUNCTION];

	अगर (macphy_crvalue & BIT(3)) अणु
		rtlhal->macphymode = SINGLEMAC_SINGLEPHY;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"MacPhyMode SINGLEMAC_SINGLEPHY\n");
	पूर्ण अन्यथा अणु
		rtlhal->macphymode = DUALMAC_DUALPHY;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"MacPhyMode DUALMAC_DUALPHY\n");
	पूर्ण
पूर्ण

अटल व्योम _rtl92de_पढ़ो_macphymode_and_bandtype(काष्ठा ieee80211_hw *hw,
						  u8 *content)
अणु
	_rtl92de_पढ़ो_macphymode_from_prom(hw, content);
	rtl92d_phy_config_macphymode(hw);
	rtl92d_phy_config_macphymode_info(hw);
पूर्ण

अटल व्योम _rtl92de_efuse_update_chip_version(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	क्रमागत version_8192d chipver = rtlpriv->rtlhal.version;
	u8 cutvalue[2];
	u16 chipvalue;

	rtlpriv->पूर्णांकf_ops->पढ़ो_efuse_byte(hw, EEPROME_CHIP_VERSION_H,
					   &cutvalue[1]);
	rtlpriv->पूर्णांकf_ops->पढ़ो_efuse_byte(hw, EEPROME_CHIP_VERSION_L,
					   &cutvalue[0]);
	chipvalue = (cutvalue[1] << 8) | cutvalue[0];
	चयन (chipvalue) अणु
	हाल 0xAA55:
		chipver |= CHIP_92D_C_CUT;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "C-CUT!!!\n");
		अवरोध;
	हाल 0x9966:
		chipver |= CHIP_92D_D_CUT;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "D-CUT!!!\n");
		अवरोध;
	हाल 0xCC33:
		chipver |= CHIP_92D_E_CUT;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "E-CUT!!!\n");
		अवरोध;
	शेष:
		chipver |= CHIP_92D_D_CUT;
		pr_err("Unknown CUT!\n");
		अवरोध;
	पूर्ण
	rtlpriv->rtlhal.version = chipver;
पूर्ण

अटल व्योम _rtl92de_पढ़ो_adapter_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक params[] = अणुRTL8190_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR_MAC0_92D,
			EEPROM_CHANNEL_PLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13पूर्ण;
	पूर्णांक i;
	u16 usvalue;
	u8 *hwinfo;

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	अगर (!hwinfo)
		वापस;

	अगर (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		जाओ निकास;

	_rtl92de_efuse_update_chip_version(hw);
	_rtl92de_पढ़ो_macphymode_and_bandtype(hw, hwinfo);

	/* Read Permanent MAC address क्रम 2nd पूर्णांकerface */
	अगर (rtlhal->पूर्णांकerfaceindex != 0) अणु
		क्रम (i = 0; i < 6; i += 2) अणु
			usvalue = *(u16 *)&hwinfo[EEPROM_MAC_ADDR_MAC1_92D + i];
			*((u16 *) (&rtlefuse->dev_addr[i])) = usvalue;
		पूर्ण
	पूर्ण
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR,
				      rtlefuse->dev_addr);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "%pM\n", rtlefuse->dev_addr);
	_rtl92de_पढ़ो_txघातer_info(hw, rtlefuse->स्वतःload_failflag, hwinfo);

	/* Read Channel Plan */
	चयन (rtlhal->bandset) अणु
	हाल BAND_ON_2_4G:
		rtlefuse->channel_plan = COUNTRY_CODE_TELEC;
		अवरोध;
	हाल BAND_ON_5G:
		rtlefuse->channel_plan = COUNTRY_CODE_FCC;
		अवरोध;
	हाल BAND_ON_BOTH:
		rtlefuse->channel_plan = COUNTRY_CODE_FCC;
		अवरोध;
	शेष:
		rtlefuse->channel_plan = COUNTRY_CODE_FCC;
		अवरोध;
	पूर्ण
	rtlefuse->txpwr_fromeprom = true;
निकास:
	kमुक्त(hwinfo);
पूर्ण

व्योम rtl92de_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_u1b;

	rtlhal->version = _rtl92de_पढ़ो_chip_version(hw);
	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_9346CR);
	rtlefuse->स्वतःload_status = पंचांगp_u1b;
	अगर (पंचांगp_u1b & BIT(4)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from EEPROM\n");
		rtlefuse->epromtype = EEPROM_93C46;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from EFUSE\n");
		rtlefuse->epromtype = EEPROM_BOOT_EFUSE;
	पूर्ण
	अगर (पंचांगp_u1b & BIT(5)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Autoload OK\n");

		rtlefuse->स्वतःload_failflag = false;
		_rtl92de_पढ़ो_adapter_info(hw);
	पूर्ण अन्यथा अणु
		pr_err("Autoload ERR!!\n");
	पूर्ण
	वापस;
पूर्ण

अटल व्योम rtl92de_update_hal_rate_table(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 ratr_value;
	u8 ratr_index = 0;
	u8 nmode = mac->ht_enable;
	u8 mimo_ps = IEEE80211_SMPS_OFF;
	u16 लघुgi_rate;
	u32 पंचांगp_ratr_value;
	u8 curtxbw_40mhz = mac->bw_40;
	u8 curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
							1 : 0;
	u8 curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
							1 : 0;
	क्रमागत wireless_mode wirelessmode = mac->mode;

	अगर (rtlhal->current_bandtype == BAND_ON_5G)
		ratr_value = sta->supp_rates[1] << 4;
	अन्यथा
		ratr_value = sta->supp_rates[0];
	ratr_value |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
		       sta->ht_cap.mcs.rx_mask[0] << 12);
	चयन (wirelessmode) अणु
	हाल WIRELESS_MODE_A:
		ratr_value &= 0x00000FF0;
		अवरोध;
	हाल WIRELESS_MODE_B:
		अगर (ratr_value & 0x0000000c)
			ratr_value &= 0x0000000d;
		अन्यथा
			ratr_value &= 0x0000000f;
		अवरोध;
	हाल WIRELESS_MODE_G:
		ratr_value &= 0x00000FF5;
		अवरोध;
	हाल WIRELESS_MODE_N_24G:
	हाल WIRELESS_MODE_N_5G:
		nmode = 1;
		अगर (mimo_ps == IEEE80211_SMPS_STATIC) अणु
			ratr_value &= 0x0007F005;
		पूर्ण अन्यथा अणु
			u32 ratr_mask;

			अगर (get_rf_type(rtlphy) == RF_1T2R ||
			    get_rf_type(rtlphy) == RF_1T1R) अणु
				ratr_mask = 0x000ff005;
			पूर्ण अन्यथा अणु
				ratr_mask = 0x0f0ff005;
			पूर्ण

			ratr_value &= ratr_mask;
		पूर्ण
		अवरोध;
	शेष:
		अगर (rtlphy->rf_type == RF_1T2R)
			ratr_value &= 0x000ff0ff;
		अन्यथा
			ratr_value &= 0x0f0ff0ff;

		अवरोध;
	पूर्ण
	ratr_value &= 0x0FFFFFFF;
	अगर (nmode && ((curtxbw_40mhz && curलघुgi_40mhz) ||
	    (!curtxbw_40mhz && curलघुgi_20mhz))) अणु
		ratr_value |= 0x10000000;
		पंचांगp_ratr_value = (ratr_value >> 12);
		क्रम (लघुgi_rate = 15; लघुgi_rate > 0; लघुgi_rate--) अणु
			अगर ((1 << लघुgi_rate) & पंचांगp_ratr_value)
				अवरोध;
		पूर्ण
		लघुgi_rate = (लघुgi_rate << 12) | (लघुgi_rate << 8) |
		    (लघुgi_rate << 4) | (लघुgi_rate);
	पूर्ण
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR0 + ratr_index * 4, ratr_value);
	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG, "%x\n",
		rtl_पढ़ो_dword(rtlpriv, REG_ARFR0));
पूर्ण

अटल व्योम rtl92de_update_hal_rate_mask(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u32 ratr_biपंचांगap;
	u8 ratr_index;
	u8 curtxbw_40mhz = (sta->bandwidth >= IEEE80211_STA_RX_BW_40) ? 1 : 0;
	u8 curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
							1 : 0;
	u8 curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
							1 : 0;
	क्रमागत wireless_mode wirelessmode = 0;
	bool लघुgi = false;
	u32 value[2];
	u8 macid = 0;
	u8 mimo_ps = IEEE80211_SMPS_OFF;

	sta_entry = (काष्ठा rtl_sta_info *) sta->drv_priv;
	mimo_ps = sta_entry->mimo_ps;
	wirelessmode = sta_entry->wireless_mode;
	अगर (mac->opmode == NL80211_IFTYPE_STATION)
		curtxbw_40mhz = mac->bw_40;
	अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;

	अगर (rtlhal->current_bandtype == BAND_ON_5G)
		ratr_biपंचांगap = sta->supp_rates[1] << 4;
	अन्यथा
		ratr_biपंचांगap = sta->supp_rates[0];
	ratr_biपंचांगap |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
			sta->ht_cap.mcs.rx_mask[0] << 12);
	चयन (wirelessmode) अणु
	हाल WIRELESS_MODE_B:
		ratr_index = RATR_INX_WIRELESS_B;
		अगर (ratr_biपंचांगap & 0x0000000c)
			ratr_biपंचांगap &= 0x0000000d;
		अन्यथा
			ratr_biपंचांगap &= 0x0000000f;
		अवरोध;
	हाल WIRELESS_MODE_G:
		ratr_index = RATR_INX_WIRELESS_GB;

		अगर (rssi_level == 1)
			ratr_biपंचांगap &= 0x00000f00;
		अन्यथा अगर (rssi_level == 2)
			ratr_biपंचांगap &= 0x00000ff0;
		अन्यथा
			ratr_biपंचांगap &= 0x00000ff5;
		अवरोध;
	हाल WIRELESS_MODE_A:
		ratr_index = RATR_INX_WIRELESS_G;
		ratr_biपंचांगap &= 0x00000ff0;
		अवरोध;
	हाल WIRELESS_MODE_N_24G:
	हाल WIRELESS_MODE_N_5G:
		अगर (wirelessmode == WIRELESS_MODE_N_24G)
			ratr_index = RATR_INX_WIRELESS_NGB;
		अन्यथा
			ratr_index = RATR_INX_WIRELESS_NG;
		अगर (mimo_ps == IEEE80211_SMPS_STATIC) अणु
			अगर (rssi_level == 1)
				ratr_biपंचांगap &= 0x00070000;
			अन्यथा अगर (rssi_level == 2)
				ratr_biपंचांगap &= 0x0007f000;
			अन्यथा
				ratr_biपंचांगap &= 0x0007f005;
		पूर्ण अन्यथा अणु
			अगर (rtlphy->rf_type == RF_1T2R ||
			    rtlphy->rf_type == RF_1T1R) अणु
				अगर (curtxbw_40mhz) अणु
					अगर (rssi_level == 1)
						ratr_biपंचांगap &= 0x000f0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x000ff000;
					अन्यथा
						ratr_biपंचांगap &= 0x000ff015;
				पूर्ण अन्यथा अणु
					अगर (rssi_level == 1)
						ratr_biपंचांगap &= 0x000f0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x000ff000;
					अन्यथा
						ratr_biपंचांगap &= 0x000ff005;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (curtxbw_40mhz) अणु
					अगर (rssi_level == 1)
						ratr_biपंचांगap &= 0x0f0f0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x0f0ff000;
					अन्यथा
						ratr_biपंचांगap &= 0x0f0ff015;
				पूर्ण अन्यथा अणु
					अगर (rssi_level == 1)
						ratr_biपंचांगap &= 0x0f0f0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x0f0ff000;
					अन्यथा
						ratr_biपंचांगap &= 0x0f0ff005;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर ((curtxbw_40mhz && curलघुgi_40mhz) ||
		    (!curtxbw_40mhz && curलघुgi_20mhz)) अणु

			अगर (macid == 0)
				लघुgi = true;
			अन्यथा अगर (macid == 1)
				लघुgi = false;
		पूर्ण
		अवरोध;
	शेष:
		ratr_index = RATR_INX_WIRELESS_NGB;

		अगर (rtlphy->rf_type == RF_1T2R)
			ratr_biपंचांगap &= 0x000ff0ff;
		अन्यथा
			ratr_biपंचांगap &= 0x0f0ff0ff;
		अवरोध;
	पूर्ण

	value[0] = (ratr_biपंचांगap & 0x0fffffff) | (ratr_index << 28);
	value[1] = macid | (लघुgi ? 0x20 : 0x00) | 0x80;
	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"ratr_bitmap :%x value0:%x value1:%x\n",
		ratr_biपंचांगap, value[0], value[1]);
	rtl92d_fill_h2c_cmd(hw, H2C_RA_MASK, 5, (u8 *) value);
	अगर (macid != 0)
		sta_entry->ratr_index = ratr_index;
पूर्ण

व्योम rtl92de_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->dm.useramask)
		rtl92de_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
	अन्यथा
		rtl92de_update_hal_rate_table(hw, sta);
पूर्ण

व्योम rtl92de_update_channel_access_setting(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 sअगरs_समयr;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME,
				      &mac->slot_समय);
	अगर (!mac->ht_enable)
		sअगरs_समयr = 0x0a0a;
	अन्यथा
		sअगरs_समयr = 0x1010;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SIFS, (u8 *)&sअगरs_समयr);
पूर्ण

bool rtl92de_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	क्रमागत rf_pwrstate e_rfघातerstate_toset;
	u8 u1पंचांगp;
	bool actuallyset = false;
	अचिन्हित दीर्घ flag;

	अगर (rtlpci->being_init_adapter)
		वापस false;
	अगर (ppsc->swrf_processing)
		वापस false;
	spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
	अगर (ppsc->rfchange_inprogress) अणु
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
		वापस false;
	पूर्ण अन्यथा अणु
		ppsc->rfchange_inprogress = true;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, REG_MAC_PINMUX_CFG, rtl_पढ़ो_byte(rtlpriv,
			  REG_MAC_PINMUX_CFG) & ~(BIT(3)));
	u1पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_IO_SEL);
	e_rfघातerstate_toset = (u1पंचांगp & BIT(3)) ? ERFON : ERFOFF;
	अगर (ppsc->hwradiooff && (e_rfघातerstate_toset == ERFON)) अणु
		rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
			"GPIOChangeRF  - HW Radio ON, RF ON\n");
		e_rfघातerstate_toset = ERFON;
		ppsc->hwradiooff = false;
		actuallyset = true;
	पूर्ण अन्यथा अगर (!ppsc->hwradiooff && (e_rfघातerstate_toset == ERFOFF)) अणु
		rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
			"GPIOChangeRF  - HW Radio OFF, RF OFF\n");
		e_rfघातerstate_toset = ERFOFF;
		ppsc->hwradiooff = true;
		actuallyset = true;
	पूर्ण
	अगर (actuallyset) अणु
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	पूर्ण अन्यथा अणु
		अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC)
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	पूर्ण
	*valid = 1;
	वापस !ppsc->hwradiooff;
पूर्ण

व्योम rtl92de_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddr, bool is_group, u8 enc_algo,
		     bool is_wepkey, bool clear_all)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 *macaddr = p_macaddr;
	u32 entry_id;
	bool is_pairwise = false;
	अटल u8 cam_स्थिर_addr[4][6] = अणु
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x01पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x02पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x03पूर्ण
	पूर्ण;
	अटल u8 cam_स्थिर_broad[] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	पूर्ण;

	अगर (clear_all) अणु
		u8 idx;
		u8 cam_offset = 0;
		u8 clear_number = 5;
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG, "clear_all\n");
		क्रम (idx = 0; idx < clear_number; idx++) अणु
			rtl_cam_mark_invalid(hw, cam_offset + idx);
			rtl_cam_empty_entry(hw, cam_offset + idx);

			अगर (idx < 5) अणु
				स_रखो(rtlpriv->sec.key_buf[idx], 0,
				       MAX_KEY_LEN);
				rtlpriv->sec.key_len[idx] = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (enc_algo) अणु
		हाल WEP40_ENCRYPTION:
			enc_algo = CAM_WEP40;
			अवरोध;
		हाल WEP104_ENCRYPTION:
			enc_algo = CAM_WEP104;
			अवरोध;
		हाल TKIP_ENCRYPTION:
			enc_algo = CAM_TKIP;
			अवरोध;
		हाल AESCCMP_ENCRYPTION:
			enc_algo = CAM_AES;
			अवरोध;
		शेष:
			pr_err("switch case %#x not processed\n",
			       enc_algo);
			enc_algo = CAM_TKIP;
			अवरोध;
		पूर्ण
		अगर (is_wepkey || rtlpriv->sec.use_शेषkey) अणु
			macaddr = cam_स्थिर_addr[key_index];
			entry_id = key_index;
		पूर्ण अन्यथा अणु
			अगर (is_group) अणु
				macaddr = cam_स्थिर_broad;
				entry_id = key_index;
			पूर्ण अन्यथा अणु
				अगर (mac->opmode == NL80211_IFTYPE_AP) अणु
					entry_id = rtl_cam_get_मुक्त_entry(hw,
								 p_macaddr);
					अगर (entry_id >=  TOTAL_CAM_ENTRY) अणु
						pr_err("Can not find free hw security cam entry\n");
						वापस;
					पूर्ण
				पूर्ण अन्यथा अणु
					entry_id = CAM_PAIRWISE_KEY_POSITION;
				पूर्ण
				key_index = PAIRWISE_KEYIDX;
				is_pairwise = true;
			पूर्ण
		पूर्ण
		अगर (rtlpriv->sec.key_len[key_index] == 0) अणु
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"delete one entry, entry_id is %d\n",
				entry_id);
			अगर (mac->opmode == NL80211_IFTYPE_AP)
				rtl_cam_del_entry(hw, p_macaddr);
			rtl_cam_delete_one_entry(hw, p_macaddr, entry_id);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"The insert KEY length is %d\n",
				rtlpriv->sec.key_len[PAIRWISE_KEYIDX]);
			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"The insert KEY is %x %x\n",
				rtlpriv->sec.key_buf[0][0],
				rtlpriv->sec.key_buf[0][1]);
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"add one entry\n");
			अगर (is_pairwise) अणु
				RT_PRINT_DATA(rtlpriv, COMP_SEC, DBG_LOUD,
					      "Pairwise Key content",
					      rtlpriv->sec.pairwise_key,
					      rtlpriv->
					      sec.key_len[PAIRWISE_KEYIDX]);
				rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
					"set Pairwise key\n");
				rtl_cam_add_one_entry(hw, macaddr, key_index,
						      entry_id, enc_algo,
						      CAM_CONFIG_NO_USEDK,
						      rtlpriv->
						      sec.key_buf[key_index]);
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
					"set group key\n");
				अगर (mac->opmode == NL80211_IFTYPE_ADHOC) अणु
					rtl_cam_add_one_entry(hw,
						rtlefuse->dev_addr,
						PAIRWISE_KEYIDX,
						CAM_PAIRWISE_KEY_POSITION,
						enc_algo, CAM_CONFIG_NO_USEDK,
						rtlpriv->sec.key_buf[entry_id]);
				पूर्ण
				rtl_cam_add_one_entry(hw, macaddr, key_index,
						entry_id, enc_algo,
						CAM_CONFIG_NO_USEDK,
						rtlpriv->sec.key_buf
						[entry_id]);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92de_suspend(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->rtlhal.macphyctl_reg = rtl_पढ़ो_byte(rtlpriv,
		REG_MAC_PHY_CTRL_NORMAL);
पूर्ण

व्योम rtl92de_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_MAC_PHY_CTRL_NORMAL,
		       rtlpriv->rtlhal.macphyctl_reg);
पूर्ण
