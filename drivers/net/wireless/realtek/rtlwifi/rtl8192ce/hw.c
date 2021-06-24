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
#समावेश "../rtl8192c/dm_common.h"
#समावेश "../rtl8192c/fw_common.h"
#समावेश "../rtl8192c/phy_common.h"
#समावेश "dm.h"
#समावेश "led.h"
#समावेश "hw.h"

#घोषणा LLT_CONFIG	5

अटल व्योम _rtl92ce_set_bcn_ctrl_reg(काष्ठा ieee80211_hw *hw,
				      u8 set_bits, u8 clear_bits)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpci->reg_bcn_ctrl_val |= set_bits;
	rtlpci->reg_bcn_ctrl_val &= ~clear_bits;

	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8)rtlpci->reg_bcn_ctrl_val);
पूर्ण

अटल व्योम _rtl92ce_stop_tx_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp1byte;

	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp1byte & (~BIT(6)));
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0x64);
	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
	पंचांगp1byte &= ~(BIT(0));
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, पंचांगp1byte);
पूर्ण

अटल व्योम _rtl92ce_resume_tx_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp1byte;

	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp1byte | BIT(6));
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);
	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
	पंचांगp1byte |= BIT(0);
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, पंचांगp1byte);
पूर्ण

अटल व्योम _rtl92ce_enable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl92ce_set_bcn_ctrl_reg(hw, 0, BIT(1));
पूर्ण

अटल व्योम _rtl92ce_disable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl92ce_set_bcn_ctrl_reg(hw, BIT(1), 0);
पूर्ण

व्योम rtl92ce_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
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

			rtlpriv->cfg->ops->get_hw_reg(hw,
						      HW_VAR_RF_STATE,
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
	हाल HAL_DEF_WOWLAN:
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92ce_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 idx;

	चयन (variable) अणु
	हाल HW_VAR_ETHER_ADDR:अणु
			क्रम (idx = 0; idx < ETH_ALEN; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, (REG_MACID + idx),
					       val[idx]);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_BASIC_RATE:अणु
			u16 rate_cfg = ((u16 *) val)[0];
			u8 rate_index = 0;

			rate_cfg &= 0x15f;
			rate_cfg |= 0x01;
			rtl_ग_लिखो_byte(rtlpriv, REG_RRSR, rate_cfg & 0xff);
			rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 1,
				       (rate_cfg >> 8) & 0xff);
			जबतक (rate_cfg > 0x1) अणु
				rate_cfg = (rate_cfg >> 1);
				rate_index++;
			पूर्ण
			rtl_ग_लिखो_byte(rtlpriv, REG_INIRTS_RATE_SEL,
				       rate_index);
			अवरोध;
		पूर्ण
	हाल HW_VAR_BSSID:अणु
			क्रम (idx = 0; idx < ETH_ALEN; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, (REG_BSSID + idx),
					       val[idx]);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_SIFS:अणु
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
		पूर्ण
	हाल HW_VAR_SLOT_TIME:अणु
			u8 e_aci;

			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"HW_VAR_SLOT_TIME %x\n", val[0]);

			rtl_ग_लिखो_byte(rtlpriv, REG_SLOT, val[0]);

			क्रम (e_aci = 0; e_aci < AC_MAX; e_aci++) अणु
				rtlpriv->cfg->ops->set_hw_reg(hw,
							      HW_VAR_AC_PARAM,
							      &e_aci);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_ACK_PREAMBLE:अणु
			u8 reg_पंचांगp;
			u8 लघु_preamble = (bool)*val;

			reg_पंचांगp = (mac->cur_40_prime_sc) << 5;
			अगर (लघु_preamble)
				reg_पंचांगp |= 0x80;

			rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 2, reg_पंचांगp);
			अवरोध;
		पूर्ण
	हाल HW_VAR_AMPDU_MIN_SPACE:अणु
			u8 min_spacing_to_set;
			u8 sec_min_space;

			min_spacing_to_set = *val;
			अगर (min_spacing_to_set <= 7) अणु
				sec_min_space = 0;

				अगर (min_spacing_to_set < sec_min_space)
					min_spacing_to_set = sec_min_space;

				mac->min_space_cfg = ((mac->min_space_cfg &
						       0xf8) |
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
	हाल HW_VAR_SHORTGI_DENSITY:अणु
			u8 density_to_set;

			density_to_set = *val;
			mac->min_space_cfg |= (density_to_set << 3);

			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"Set HW_VAR_SHORTGI_DENSITY: %#x\n",
				mac->min_space_cfg);

			rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE,
				       mac->min_space_cfg);

			अवरोध;
		पूर्ण
	हाल HW_VAR_AMPDU_FACTOR:अणु
			u8 regtoset_normal[4] = अणु0x41, 0xa8, 0x72, 0xb9पूर्ण;
			u8 regtoset_bt[4] = अणु0x31, 0x74, 0x42, 0x97पूर्ण;

			u8 factor_toset;
			u8 *p_regtoset = शून्य;
			u8 index = 0;

			अगर ((rtlpriv->btcoexist.bt_coexistence) &&
			    (rtlpriv->btcoexist.bt_coexist_type ==
			    BT_CSR_BC4))
				p_regtoset = regtoset_bt;
			अन्यथा
				p_regtoset = regtoset_normal;

			factor_toset = *(val);
			अगर (factor_toset <= 3) अणु
				factor_toset = (1 << (factor_toset + 2));
				अगर (factor_toset > 0xf)
					factor_toset = 0xf;

				क्रम (index = 0; index < 4; index++) अणु
					अगर ((p_regtoset[index] & 0xf0) >
					    (factor_toset << 4))
						p_regtoset[index] =
						    (p_regtoset[index] & 0x0f) |
						    (factor_toset << 4);

					अगर ((p_regtoset[index] & 0x0f) >
					    factor_toset)
						p_regtoset[index] =
						    (p_regtoset[index] & 0xf0) |
						    (factor_toset);

					rtl_ग_लिखो_byte(rtlpriv,
						       (REG_AGGLEN_LMT + index),
						       p_regtoset[index]);

				पूर्ण

				rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
					"Set HW_VAR_AMPDU_FACTOR: %#x\n",
					factor_toset);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_AC_PARAM:अणु
			u8 e_aci = *(val);

			rtl92c_dm_init_edca_turbo(hw);

			अगर (rtlpci->acm_method != EACMWAY2_SW)
				rtlpriv->cfg->ops->set_hw_reg(hw,
							      HW_VAR_ACM_CTRL,
							      (&e_aci));
			अवरोध;
		पूर्ण
	हाल HW_VAR_ACM_CTRL:अणु
			u8 e_aci = *(val);
			जोड़ aci_aअगरsn *p_aci_aअगरsn =
			    (जोड़ aci_aअगरsn *)(&(mac->ac[0].aअगरs));
			u8 acm = p_aci_aअगरsn->f.acm;
			u8 acm_ctrl = rtl_पढ़ो_byte(rtlpriv, REG_ACMHWCTRL);

			acm_ctrl =
			    acm_ctrl | ((rtlpci->acm_method == 2) ? 0x0 : 0x1);

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
	हाल HW_VAR_RCR:अणु
			rtl_ग_लिखो_dword(rtlpriv, REG_RCR, ((u32 *) (val))[0]);
			rtlpci->receive_config = ((u32 *) (val))[0];
			अवरोध;
		पूर्ण
	हाल HW_VAR_RETRY_LIMIT:अणु
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
		rtl92c_phy_set_io_cmd(hw, (*(क्रमागत io_type *)val));
		अवरोध;
	हाल HW_VAR_WPA_CONFIG:
		rtl_ग_लिखो_byte(rtlpriv, REG_SECCFG, *val);
		अवरोध;
	हाल HW_VAR_SET_RPWM:अणु
			u8 rpwm_val;

			rpwm_val = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_HRPWM);
			udelay(1);

			अगर (rpwm_val & BIT(7)) अणु
				rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_HRPWM, *val);
			पूर्ण अन्यथा अणु
				rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_HRPWM,
					       *val | BIT(7));
			पूर्ण

			अवरोध;
		पूर्ण
	हाल HW_VAR_H2C_FW_PWRMODE:अणु
			u8 psmode = *val;

			अगर ((psmode != FW_PS_ACTIVE_MODE) &&
			    (!IS_92C_SERIAL(rtlhal->version))) अणु
				rtl92c_dm_rf_saving(hw, true);
			पूर्ण

			rtl92c_set_fw_pwrmode_cmd(hw, *val);
			अवरोध;
		पूर्ण
	हाल HW_VAR_FW_PSMODE_STATUS:
		ppsc->fw_current_inpsmode = *((bool *) val);
		अवरोध;
	हाल HW_VAR_H2C_FW_JOINBSSRPT:अणु
			u8 mstatus = *val;
			u8 पंचांगp_regcr, पंचांगp_reg422;
			bool recover = false;

			अगर (mstatus == RT_MEDIA_CONNECT) अणु
				rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AID,
							      शून्य);

				पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
				rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1,
					       (पंचांगp_regcr | BIT(0)));

				_rtl92ce_set_bcn_ctrl_reg(hw, 0, BIT(3));
				_rtl92ce_set_bcn_ctrl_reg(hw, BIT(4), 0);

				पंचांगp_reg422 =
				    rtl_पढ़ो_byte(rtlpriv,
						  REG_FWHW_TXQ_CTRL + 2);
				अगर (पंचांगp_reg422 & BIT(6))
					recover = true;
				rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2,
					       पंचांगp_reg422 & (~BIT(6)));

				rtl92c_set_fw_rsvdpagepkt(hw, शून्य);

				_rtl92ce_set_bcn_ctrl_reg(hw, BIT(3), 0);
				_rtl92ce_set_bcn_ctrl_reg(hw, 0, BIT(4));

				अगर (recover) अणु
					rtl_ग_लिखो_byte(rtlpriv,
						       REG_FWHW_TXQ_CTRL + 2,
						       पंचांगp_reg422);
				पूर्ण

				rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1,
					       (पंचांगp_regcr & ~(BIT(0))));
			पूर्ण
			rtl92c_set_fw_joinbss_report_cmd(hw, *val);

			अवरोध;
		पूर्ण
	हाल HW_VAR_H2C_FW_P2P_PS_OFFLOAD:
		rtl92c_set_p2p_ps_offload_cmd(hw, *val);
		अवरोध;
	हाल HW_VAR_AID:अणु
			u16 u2bपंचांगp;

			u2bपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_BCN_PSR_RPT);
			u2bपंचांगp &= 0xC000;
			rtl_ग_लिखो_word(rtlpriv, REG_BCN_PSR_RPT, (u2bपंचांगp |
						mac->assoc_id));

			अवरोध;
		पूर्ण
	हाल HW_VAR_CORRECT_TSF:अणु
			u8 btype_ibss = val[0];

			अगर (btype_ibss)
				_rtl92ce_stop_tx_beacon(hw);

			_rtl92ce_set_bcn_ctrl_reg(hw, 0, BIT(3));

			rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR,
					(u32) (mac->tsf & 0xffffffff));
			rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR + 4,
					(u32) ((mac->tsf >> 32) & 0xffffffff));

			_rtl92ce_set_bcn_ctrl_reg(hw, BIT(3), 0);

			अगर (btype_ibss)
				_rtl92ce_resume_tx_beacon(hw);

			अवरोध;

		पूर्ण
	हाल HW_VAR_FW_LPS_ACTION: अणु
			bool enter_fwlps = *((bool *)val);
			u8 rpwm_val, fw_pwrmode;
			bool fw_current_inps;

			अगर (enter_fwlps) अणु
				rpwm_val = 0x02;	/* RF off */
				fw_current_inps = true;
				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_FW_PSMODE_STATUS,
						(u8 *)(&fw_current_inps));
				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_H2C_FW_PWRMODE,
						&ppsc->fwctrl_psmode);

				rtlpriv->cfg->ops->set_hw_reg(hw,
							      HW_VAR_SET_RPWM,
							      &rpwm_val);
			पूर्ण अन्यथा अणु
				rpwm_val = 0x0C;	/* RF on */
				fw_pwrmode = FW_PS_ACTIVE_MODE;
				fw_current_inps = false;
				rtlpriv->cfg->ops->set_hw_reg(hw,
							      HW_VAR_SET_RPWM,
							      &rpwm_val);
				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_H2C_FW_PWRMODE,
						&fw_pwrmode);

				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_FW_PSMODE_STATUS,
						(u8 *)(&fw_current_inps));
			पूर्ण
		अवरोध; पूर्ण
	हाल HW_VAR_KEEP_ALIVE: अणु
		u8 array[2];

		array[0] = 0xff;
		array[1] = *((u8 *)val);
		rtl92c_fill_h2c_cmd(hw, H2C_92C_KEEP_ALIVE_CTRL, 2, array);
		अवरोध; पूर्ण
	शेष:
		pr_err("switch case %d not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool _rtl92ce_llt_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 address, u32 data)
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

अटल bool _rtl92ce_llt_table_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अचिन्हित लघु i;
	u8 txpktbuf_bndy;
	u8 maxpage;
	bool status;

#अगर LLT_CONFIG == 1
	maxpage = 255;
	txpktbuf_bndy = 252;
#या_अगर LLT_CONFIG == 2
	maxpage = 127;
	txpktbuf_bndy = 124;
#या_अगर LLT_CONFIG == 3
	maxpage = 255;
	txpktbuf_bndy = 174;
#या_अगर LLT_CONFIG == 4
	maxpage = 255;
	txpktbuf_bndy = 246;
#या_अगर LLT_CONFIG == 5
	maxpage = 255;
	txpktbuf_bndy = 246;
#पूर्ण_अगर

#अगर LLT_CONFIG == 1
	rtl_ग_लिखो_byte(rtlpriv, REG_RQPN_NPQ, 0x1c);
	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, 0x80a71c1c);
#या_अगर LLT_CONFIG == 2
	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, 0x845B1010);
#या_अगर LLT_CONFIG == 3
	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, 0x84838484);
#या_अगर LLT_CONFIG == 4
	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, 0x80bd1c1c);
#या_अगर LLT_CONFIG == 5
	rtl_ग_लिखो_word(rtlpriv, REG_RQPN_NPQ, 0x0000);

	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, 0x80b01c29);
#पूर्ण_अगर

	rtl_ग_लिखो_dword(rtlpriv, REG_TRXFF_BNDY, (0x27FF0000 | txpktbuf_bndy));
	rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 1, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, 0x45D, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_PBP, 0x11);
	rtl_ग_लिखो_byte(rtlpriv, REG_RX_DRVINFO_SZ, 0x4);

	क्रम (i = 0; i < (txpktbuf_bndy - 1); i++) अणु
		status = _rtl92ce_llt_ग_लिखो(hw, i, i + 1);
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl92ce_llt_ग_लिखो(hw, (txpktbuf_bndy - 1), 0xFF);
	अगर (!status)
		वापस status;

	क्रम (i = txpktbuf_bndy; i < maxpage; i++) अणु
		status = _rtl92ce_llt_ग_लिखो(hw, i, (i + 1));
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl92ce_llt_ग_लिखो(hw, maxpage, txpktbuf_bndy);
	अगर (!status)
		वापस status;

	वापस true;
पूर्ण

अटल व्योम _rtl92ce_gen_refresh_led_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;

	अगर (rtlpci->up_first_समय)
		वापस;

	अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
		rtl92ce_sw_led_on(hw, pled0);
	अन्यथा अगर (ppsc->rfoff_reason == RF_CHANGE_BY_INIT)
		rtl92ce_sw_led_on(hw, pled0);
	अन्यथा
		rtl92ce_sw_led_off(hw, pled0);
पूर्ण

अटल bool _rtl92ce_init_mac(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अचिन्हित अक्षर byteपंचांगp;
	अचिन्हित लघु wordपंचांगp;
	u16 retry;

	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x00);
	अगर (rtlpriv->btcoexist.bt_coexistence) अणु
		u32 value32;

		value32 = rtl_पढ़ो_dword(rtlpriv, REG_APS_FSMCO);
		value32 |= (SOP_ABG | SOP_AMB | XOP_BTCK);
		rtl_ग_लिखो_dword(rtlpriv, REG_APS_FSMCO, value32);
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x2b);
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_XTAL_CTRL, 0x0F);

	अगर (rtlpriv->btcoexist.bt_coexistence) अणु
		u32 u4b_पंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_AFE_XTAL_CTRL);

		u4b_पंचांगp &= (~0x00024800);
		rtl_ग_लिखो_dword(rtlpriv, REG_AFE_XTAL_CTRL, u4b_पंचांगp);
	पूर्ण

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO + 1) | BIT(0);
	udelay(2);

	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO + 1, byteपंचांगp);
	udelay(2);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO + 1);
	udelay(2);

	retry = 0;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "reg0xec:%x:%x\n",
		rtl_पढ़ो_dword(rtlpriv, 0xEC), byteपंचांगp);

	जबतक ((byteपंचांगp & BIT(0)) && retry < 1000) अणु
		retry++;
		udelay(50);
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO + 1);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "reg0xec:%x:%x\n",
			rtl_पढ़ो_dword(rtlpriv, 0xEC), byteपंचांगp);
		udelay(50);
	पूर्ण

	rtl_ग_लिखो_word(rtlpriv, REG_APS_FSMCO, 0x1012);

	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL + 1, 0x82);
	udelay(2);

	अगर (rtlpriv->btcoexist.bt_coexistence) अणु
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_AFE_XTAL_CTRL+2) & 0xfd;
		rtl_ग_लिखो_byte(rtlpriv, REG_AFE_XTAL_CTRL+2, byteपंचांगp);
	पूर्ण

	rtl_ग_लिखो_word(rtlpriv, REG_CR, 0x2ff);

	अगर (!_rtl92ce_llt_table_init(hw))
		वापस false;

	rtl_ग_लिखो_dword(rtlpriv, REG_HISR, 0xffffffff);
	rtl_ग_लिखो_byte(rtlpriv, REG_HISRE, 0xff);

	rtl_ग_लिखो_word(rtlpriv, REG_TRXFF_BNDY + 2, 0x27ff);

	wordपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_TRXDMA_CTRL);
	wordपंचांगp &= 0xf;
	wordपंचांगp |= 0xF771;
	rtl_ग_लिखो_word(rtlpriv, REG_TRXDMA_CTRL, wordपंचांगp);

	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 1, 0x1F);
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);
	rtl_ग_लिखो_dword(rtlpriv, REG_TCR, rtlpci->transmit_config);

	rtl_ग_लिखो_byte(rtlpriv, 0x4d0, 0x0);

	rtl_ग_लिखो_dword(rtlpriv, REG_BCNQ_DESA,
			((u64) rtlpci->tx_ring[BEACON_QUEUE].dma) &
			DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_MGQ_DESA,
			(u64) rtlpci->tx_ring[MGNT_QUEUE].dma &
			DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_VOQ_DESA,
			(u64) rtlpci->tx_ring[VO_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_VIQ_DESA,
			(u64) rtlpci->tx_ring[VI_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_BEQ_DESA,
			(u64) rtlpci->tx_ring[BE_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_BKQ_DESA,
			(u64) rtlpci->tx_ring[BK_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_HQ_DESA,
			(u64) rtlpci->tx_ring[HIGH_QUEUE].dma &
			DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_RX_DESA,
			(u64) rtlpci->rx_ring[RX_MPDU_QUEUE].dma &
			DMA_BIT_MASK(32));

	अगर (IS_92C_SERIAL(rtlhal->version))
		rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 3, 0x77);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 3, 0x22);

	rtl_ग_लिखो_dword(rtlpriv, REG_INT_MIG, 0);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APSD_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, byteपंचांगp & ~BIT(6));
	करो अणु
		retry++;
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APSD_CTRL);
	पूर्ण जबतक ((retry < 200) && (byteपंचांगp & BIT(7)));

	_rtl92ce_gen_refresh_led_state(hw);

	rtl_ग_लिखो_dword(rtlpriv, REG_MCUTST_1, 0x0);

	वापस true;
पूर्ण

अटल व्योम _rtl92ce_hw_configure(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 reg_bw_opmode;
	u32 reg_prsr;

	reg_bw_opmode = BW_OPMODE_20MHZ;
	reg_prsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;

	rtl_ग_लिखो_byte(rtlpriv, REG_INIRTS_RATE_SEL, 0x8);

	rtl_ग_लिखो_byte(rtlpriv, REG_BWOPMODE, reg_bw_opmode);

	rtl_ग_लिखो_dword(rtlpriv, REG_RRSR, reg_prsr);

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

	अगर ((rtlpriv->btcoexist.bt_coexistence) &&
	    (rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4))
		rtl_ग_लिखो_dword(rtlpriv, REG_AGGLEN_LMT, 0x97427431);
	अन्यथा
		rtl_ग_लिखो_dword(rtlpriv, REG_AGGLEN_LMT, 0xb972a841);

	rtl_ग_लिखो_byte(rtlpriv, REG_ATIMWND, 0x2);

	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_MAX_ERR, 0xff);

	rtlpci->reg_bcn_ctrl_val = 0x1f;
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, rtlpci->reg_bcn_ctrl_val);

	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);

	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);

	rtl_ग_लिखो_byte(rtlpriv, REG_PIFS, 0x1C);
	rtl_ग_लिखो_byte(rtlpriv, REG_AGGR_BREAK_TIME, 0x16);

	अगर ((rtlpriv->btcoexist.bt_coexistence) &&
	    (rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4)) अणु
		rtl_ग_लिखो_word(rtlpriv, REG_NAV_PROT_LEN, 0x0020);
		rtl_ग_लिखो_word(rtlpriv, REG_PROT_MODE_CTRL, 0x0402);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_word(rtlpriv, REG_NAV_PROT_LEN, 0x0020);
		rtl_ग_लिखो_word(rtlpriv, REG_NAV_PROT_LEN, 0x0020);
	पूर्ण

	अगर ((rtlpriv->btcoexist.bt_coexistence) &&
	    (rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4))
		rtl_ग_लिखो_dword(rtlpriv, REG_FAST_EDCA_CTRL, 0x03086666);
	अन्यथा
		rtl_ग_लिखो_dword(rtlpriv, REG_FAST_EDCA_CTRL, 0x086666);

	rtl_ग_लिखो_byte(rtlpriv, REG_ACKTO, 0x40);

	rtl_ग_लिखो_word(rtlpriv, REG_SPEC_SIFS, 0x1010);
	rtl_ग_लिखो_word(rtlpriv, REG_MAC_SPEC_SIFS, 0x1010);

	rtl_ग_लिखो_word(rtlpriv, REG_SIFS_CTX, 0x1010);

	rtl_ग_लिखो_word(rtlpriv, REG_SIFS_TRX, 0x1010);

	rtl_ग_लिखो_dword(rtlpriv, REG_MAR, 0xffffffff);
	rtl_ग_लिखो_dword(rtlpriv, REG_MAR + 4, 0xffffffff);

पूर्ण

अटल व्योम _rtl92ce_enable_aspm_back_करोor(काष्ठा ieee80211_hw *hw)
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

व्योम rtl92ce_enable_hw_security_config(काष्ठा ieee80211_hw *hw)
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

	sec_reg_value = SCR_TXENCENABLE | SCR_RXDECENABLE;

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

पूर्णांक rtl92ce_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool rtstatus = true;
	bool is92c;
	पूर्णांक err;
	u8 पंचांगp_u1b;
	अचिन्हित दीर्घ flags;

	rtlpci->being_init_adapter = true;

	/* Since this function can take a very दीर्घ समय (up to 350 ms)
	 * and can be called with irqs disabled, reenable the irqs
	 * to let the other devices जारी being serviced.
	 *
	 * It is safe करोing so since our own पूर्णांकerrupts will only be enabled
	 * in a subsequent step.
	 */
	local_save_flags(flags);
	local_irq_enable();

	rtlhal->fw_पढ़ोy = false;
	rtlpriv->पूर्णांकf_ops->disable_aspm(hw);
	rtstatus = _rtl92ce_init_mac(hw);
	अगर (!rtstatus) अणु
		pr_err("Init MAC failed\n");
		err = 1;
		जाओ निकास;
	पूर्ण

	err = rtl92c_करोwnload_fw(hw);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Failed to download FW. Init HW without FW now..\n");
		err = 1;
		जाओ निकास;
	पूर्ण

	rtlhal->fw_पढ़ोy = true;
	rtlhal->last_hmeboxnum = 0;
	rtl92c_phy_mac_config(hw);
	/* because last function modअगरy RCR, so we update
	 * rcr var here, or TP will unstable क्रम receive_config
	 * is wrong, RX RCR_ACRC32 will cause TP unstabel & Rx
	 * RCR_APP_ICV will cause mac80211 unassoc क्रम cisco 1252*/
	rtlpci->receive_config = rtl_पढ़ो_dword(rtlpriv, REG_RCR);
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);
	rtl92c_phy_bb_config(hw);
	rtlphy->rf_mode = RF_OP_BY_SW_3WIRE;
	rtl92c_phy_rf_config(hw);
	अगर (IS_VENDOR_UMC_A_CUT(rtlhal->version) &&
	    !IS_92C_SERIAL(rtlhal->version)) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G1, MASKDWORD, 0x30255);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G2, MASKDWORD, 0x50a00);
	पूर्ण अन्यथा अगर (IS_81XXC_VENDOR_UMC_B_CUT(rtlhal->version)) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, 0x0C, MASKDWORD, 0x894AE);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x0A, MASKDWORD, 0x1AF31);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_IPA, MASKDWORD, 0x8F425);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_SYN_G2, MASKDWORD, 0x4F200);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK1, MASKDWORD, 0x44053);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK2, MASKDWORD, 0x80201);
	पूर्ण
	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, (क्रमागत radio_path)0,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl_get_rfreg(hw, (क्रमागत radio_path)1,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10), 1);
	_rtl92ce_hw_configure(hw);
	rtl_cam_reset_all_entry(hw);
	rtl92ce_enable_hw_security_config(hw);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	_rtl92ce_enable_aspm_back_करोor(hw);
	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);

	rtl8192ce_bt_hw_init(hw);

	अगर (ppsc->rfpwr_state == ERFON) अणु
		rtl92c_phy_set_rfpath_चयन(hw, 1);
		अगर (rtlphy->iqk_initialized) अणु
			rtl92c_phy_iq_calibrate(hw, true);
		पूर्ण अन्यथा अणु
			rtl92c_phy_iq_calibrate(hw, false);
			rtlphy->iqk_initialized = true;
		पूर्ण

		rtl92c_dm_check_txघातer_tracking(hw);
		rtl92c_phy_lc_calibrate(hw);
	पूर्ण

	is92c = IS_92C_SERIAL(rtlhal->version);
	पंचांगp_u1b = efuse_पढ़ो_1byte(hw, 0x1FA);
	अगर (!(पंचांगp_u1b & BIT(0))) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0F, 0x05);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "PA BIAS path A\n");
	पूर्ण

	अगर (!(पंचांगp_u1b & BIT(1)) && is92c) अणु
		rtl_set_rfreg(hw, RF90_PATH_B, 0x15, 0x0F, 0x05);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "PA BIAS path B\n");
	पूर्ण

	अगर (!(पंचांगp_u1b & BIT(4))) अणु
		पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, 0x16);
		पंचांगp_u1b &= 0x0F;
		rtl_ग_लिखो_byte(rtlpriv, 0x16, पंचांगp_u1b | 0x80);
		udelay(10);
		rtl_ग_लिखो_byte(rtlpriv, 0x16, पंचांगp_u1b | 0x90);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "under 1.5V\n");
	पूर्ण
	rtl92c_dm_init(hw);
निकास:
	local_irq_restore(flags);
	rtlpci->being_init_adapter = false;
	वापस err;
पूर्ण

अटल क्रमागत version_8192c _rtl92ce_पढ़ो_chip_version(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	क्रमागत version_8192c version = VERSION_UNKNOWN;
	u32 value32;
	स्थिर अक्षर *versionid;

	value32 = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG);
	अगर (value32 & TRP_VAUX_EN) अणु
		version = (value32 & TYPE_ID) ? VERSION_A_CHIP_92C :
			   VERSION_A_CHIP_88C;
	पूर्ण अन्यथा अणु
		version = (क्रमागत version_8192c) (CHIP_VER_B |
				((value32 & TYPE_ID) ? CHIP_92C_BITMASK : 0) |
				((value32 & VENDOR_ID) ? CHIP_VENDOR_UMC : 0));
		अगर ((!IS_CHIP_VENDOR_UMC(version)) && (value32 &
		     CHIP_VER_RTL_MASK)) अणु
			version = (क्रमागत version_8192c)(version |
				   ((((value32 & CHIP_VER_RTL_MASK) == BIT(12))
				   ? CHIP_VENDOR_UMC_B_CUT : CHIP_UNKNOWN) |
				   CHIP_VENDOR_UMC));
		पूर्ण
		अगर (IS_92C_SERIAL(version)) अणु
			value32 = rtl_पढ़ो_dword(rtlpriv, REG_HPON_FSM);
			version = (क्रमागत version_8192c)(version |
				   ((CHIP_BONDING_IDENTIFIER(value32)
				   == CHIP_BONDING_92C_1T2R) ?
				   RF_TYPE_1T2R : 0));
		पूर्ण
	पूर्ण

	चयन (version) अणु
	हाल VERSION_B_CHIP_92C:
		versionid = "B_CHIP_92C";
		अवरोध;
	हाल VERSION_B_CHIP_88C:
		versionid = "B_CHIP_88C";
		अवरोध;
	हाल VERSION_A_CHIP_92C:
		versionid = "A_CHIP_92C";
		अवरोध;
	हाल VERSION_A_CHIP_88C:
		versionid = "A_CHIP_88C";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_92C_1T2R_A_CUT:
		versionid = "A_CUT_92C_1T2R";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_92C_A_CUT:
		versionid = "A_CUT_92C";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_88C_A_CUT:
		versionid = "A_CUT_88C";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_92C_1T2R_B_CUT:
		versionid = "B_CUT_92C_1T2R";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_92C_B_CUT:
		versionid = "B_CUT_92C";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_88C_B_CUT:
		versionid = "B_CUT_88C";
		अवरोध;
	शेष:
		versionid = "Unknown. Bug?";
		अवरोध;
	पूर्ण

	pr_info("Chip Version ID: %s\n", versionid);

	चयन (version & 0x3) अणु
	हाल CHIP_88C:
		rtlphy->rf_type = RF_1T1R;
		अवरोध;
	हाल CHIP_92C:
		rtlphy->rf_type = RF_2T2R;
		अवरोध;
	हाल CHIP_92C_1T2R:
		rtlphy->rf_type = RF_1T2R;
		अवरोध;
	शेष:
		rtlphy->rf_type = RF_1T1R;
		pr_err("ERROR RF_Type is set!!\n");
		अवरोध;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Chip RF Type: %s\n",
		rtlphy->rf_type == RF_2T2R ? "RF_2T2R" : "RF_1T1R");

	वापस version;
पूर्ण

अटल पूर्णांक _rtl92ce_set_media_status(काष्ठा ieee80211_hw *hw,
				     क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_msr = rtl_पढ़ो_byte(rtlpriv, MSR);
	क्रमागत led_ctl_mode ledaction = LED_CTL_NO_LINK;
	u8 mode = MSR_NOLINK;

	bt_msr &= 0xfc;

	चयन (type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		mode = MSR_NOLINK;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to NO LINK!\n");
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		mode = MSR_ADHOC;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to Ad Hoc!\n");
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		mode = MSR_INFRA;
		ledaction = LED_CTL_LINK;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to STA!\n");
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		mode = MSR_AP;
		ledaction = LED_CTL_LINK;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to AP!\n");
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		mode = MSR_ADHOC;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to Mesh Point!\n");
		अवरोध;
	शेष:
		pr_err("Network type %d not supported!\n", type);
		वापस 1;

	पूर्ण

	/* MSR_INFRA == Link in infraकाष्ठाure network;
	 * MSR_ADHOC == Link in ad hoc network;
	 * Thereक्रमe, check link state is necessary.
	 *
	 * MSR_AP == AP mode; link state करोes not matter here.
	 */
	अगर (mode != MSR_AP &&
	    rtlpriv->mac80211.link_state < MAC80211_LINKED) अणु
		mode = MSR_NOLINK;
		ledaction = LED_CTL_NO_LINK;
	पूर्ण
	अगर (mode == MSR_NOLINK || mode == MSR_INFRA) अणु
		_rtl92ce_stop_tx_beacon(hw);
		_rtl92ce_enable_bcn_sub_func(hw);
	पूर्ण अन्यथा अगर (mode == MSR_ADHOC || mode == MSR_AP) अणु
		_rtl92ce_resume_tx_beacon(hw);
		_rtl92ce_disable_bcn_sub_func(hw);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Set HW_VAR_MEDIA_STATUS: No such media status(%x).\n",
			mode);
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, MSR, bt_msr | mode);

	rtlpriv->cfg->ops->led_control(hw, ledaction);
	अगर (mode == MSR_AP)
		rtl_ग_लिखो_byte(rtlpriv, REG_BCNTCFG + 1, 0x00);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, REG_BCNTCFG + 1, 0x66);
	वापस 0;
पूर्ण

व्योम rtl92ce_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 reg_rcr;

	अगर (rtlpriv->psc.rfpwr_state != ERFON)
		वापस;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RCR, (u8 *)(&reg_rcr));

	अगर (check_bssid) अणु
		reg_rcr |= (RCR_CBSSID_DATA | RCR_CBSSID_BCN);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR,
					      (u8 *) (&reg_rcr));
		_rtl92ce_set_bcn_ctrl_reg(hw, 0, BIT(4));
	पूर्ण अन्यथा अगर (!check_bssid) अणु
		reg_rcr &= (~(RCR_CBSSID_DATA | RCR_CBSSID_BCN));
		_rtl92ce_set_bcn_ctrl_reg(hw, BIT(4), 0);
		rtlpriv->cfg->ops->set_hw_reg(hw,
					      HW_VAR_RCR, (u8 *) (&reg_rcr));
	पूर्ण

पूर्ण

पूर्णांक rtl92ce_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (_rtl92ce_set_media_status(hw, type))
		वापस -EOPNOTSUPP;

	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		अगर (type != NL80211_IFTYPE_AP &&
		    type != NL80211_IFTYPE_MESH_POINT)
			rtl92ce_set_check_bssid(hw, true);
	पूर्ण अन्यथा अणु
		rtl92ce_set_check_bssid(hw, false);
	पूर्ण

	वापस 0;
पूर्ण

/* करोn't set REG_EDCA_BE_PARAM here because mac80211 will send pkt when scan */
व्योम rtl92ce_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl92c_dm_init_edca_turbo(hw);
	चयन (aci) अणु
	हाल AC1_BK:
		rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_BK_PARAM, 0xa44f);
		अवरोध;
	हाल AC0_BE:
		/* rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_BE_PARAM, u4b_ac_param); */
		अवरोध;
	हाल AC2_VI:
		rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_VI_PARAM, 0x5e4322);
		अवरोध;
	हाल AC3_VO:
		rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_VO_PARAM, 0x2f3222);
		अवरोध;
	शेष:
		WARN_ONCE(true, "rtl8192ce: invalid aci: %d !\n", aci);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92ce_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, rtlpci->irq_mask[0] & 0xFFFFFFFF);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, rtlpci->irq_mask[1] & 0xFFFFFFFF);
	rtlpci->irq_enabled = true;
पूर्ण

व्योम rtl92ce_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, IMR8190_DISABLED);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, IMR8190_DISABLED);
	rtlpci->irq_enabled = false;
पूर्ण

अटल व्योम _rtl92ce_घातeroff_adapter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u8 u1b_पंचांगp;
	u32 u4b_पंचांगp;

	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);
	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, 0x00);
	rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, 0x40);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE0);
	अगर (rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL) & BIT(7))
		rtl92c_firmware_selfreset(hw);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, 0x51);
	rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0x00);
	rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL, 0x00000000);
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_PIN_CTRL);
	अगर ((rtlpriv->btcoexist.bt_coexistence) &&
	    ((rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4) ||
	     (rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC8))) अणु
		rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL, 0x00F30000 |
				(u1b_पंचांगp << 8));
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL, 0x00FF0000 |
				(u1b_पंचांगp << 8));
	पूर्ण
	rtl_ग_लिखो_word(rtlpriv, REG_GPIO_IO_SEL, 0x0790);
	rtl_ग_लिखो_word(rtlpriv, REG_LEDCFG0, 0x8080);
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_PLL_CTRL, 0x80);
	अगर (!IS_81XXC_VENDOR_UMC_B_CUT(rtlhal->version))
		rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x23);
	अगर (rtlpriv->btcoexist.bt_coexistence) अणु
		u4b_पंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_AFE_XTAL_CTRL);
		u4b_पंचांगp |= 0x03824800;
		rtl_ग_लिखो_dword(rtlpriv, REG_AFE_XTAL_CTRL, u4b_पंचांगp);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_dword(rtlpriv, REG_AFE_XTAL_CTRL, 0x0e);
	पूर्ण

	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0e);
	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO + 1, 0x10);
पूर्ण

व्योम rtl92ce_card_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	क्रमागत nl80211_अगरtype opmode;

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;
	_rtl92ce_set_media_status(hw, opmode);
	अगर (rtlpci->driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);
	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
	_rtl92ce_घातeroff_adapter(hw);

	/* after घातer off we should करो iqk again */
	rtlpriv->phy.iqk_initialized = false;
पूर्ण

व्योम rtl92ce_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_पूर्णांक *पूर्णांकvec)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	पूर्णांकvec->पूर्णांकa = rtl_पढ़ो_dword(rtlpriv, ISR) & rtlpci->irq_mask[0];
	rtl_ग_लिखो_dword(rtlpriv, ISR, पूर्णांकvec->पूर्णांकa);
पूर्ण

व्योम rtl92ce_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw)
अणु

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval, atim_winकरोw;

	bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;
	atim_winकरोw = 2;	/*FIX MERGE */
	rtl92ce_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_ATIMWND, atim_winकरोw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl_ग_लिखो_word(rtlpriv, REG_BCNTCFG, 0x660f);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_CCK, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, 0x606, 0x30);
	rtl92ce_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl92ce_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;

	rtl_dbg(rtlpriv, COMP_BEACON, DBG_DMESG,
		"beacon_interval:%d\n", bcn_पूर्णांकerval);
	rtl92ce_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl92ce_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl92ce_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
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
	rtl92ce_disable_पूर्णांकerrupt(hw);
	rtl92ce_enable_पूर्णांकerrupt(hw);
पूर्ण

अटल व्योम _rtl92ce_पढ़ो_txघातer_info_from_hwpg(काष्ठा ieee80211_hw *hw,
						 bool स्वतःload_fail,
						 u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 rf_path, index, tempval;
	u16 i;

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 3; i++) अणु
			अगर (!स्वतःload_fail) अणु
				rtlefuse->
				    eeprom_chnlarea_txpwr_cck[rf_path][i] =
				    hwinfo[EEPROM_TXPOWERCCK + rf_path * 3 + i];
				rtlefuse->
				    eeprom_chnlarea_txpwr_ht40_1s[rf_path][i] =
				    hwinfo[EEPROM_TXPOWERHT40_1S + rf_path * 3 +
					   i];
			पूर्ण अन्यथा अणु
				rtlefuse->
				    eeprom_chnlarea_txpwr_cck[rf_path][i] =
				    EEPROM_DEFAULT_TXPOWERLEVEL;
				rtlefuse->
				    eeprom_chnlarea_txpwr_ht40_1s[rf_path][i] =
				    EEPROM_DEFAULT_TXPOWERLEVEL;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		अगर (!स्वतःload_fail)
			tempval = hwinfo[EEPROM_TXPOWERHT40_2SDIFF + i];
		अन्यथा
			tempval = EEPROM_DEFAULT_HT40_2SDIFF;
		rtlefuse->eprom_chnl_txpwr_ht40_2sdf[RF90_PATH_A][i] =
		    (tempval & 0xf);
		rtlefuse->eprom_chnl_txpwr_ht40_2sdf[RF90_PATH_B][i] =
		    ((tempval & 0xf0) >> 4);
	पूर्ण

	क्रम (rf_path = 0; rf_path < 2; rf_path++)
		क्रम (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM CCK Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->
				eeprom_chnlarea_txpwr_cck[rf_path][i]);
	क्रम (rf_path = 0; rf_path < 2; rf_path++)
		क्रम (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM HT40 1S Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->
				eeprom_chnlarea_txpwr_ht40_1s[rf_path][i]);
	क्रम (rf_path = 0; rf_path < 2; rf_path++)
		क्रम (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM HT40 2S Diff Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->
				eprom_chnl_txpwr_ht40_2sdf[rf_path][i]);

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 14; i++) अणु
			index = rtl92c_get_chnl_group((u8)i);

			rtlefuse->txpwrlevel_cck[rf_path][i] =
			    rtlefuse->eeprom_chnlarea_txpwr_cck[rf_path][index];
			rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
			    rtlefuse->
			    eeprom_chnlarea_txpwr_ht40_1s[rf_path][index];

			अगर ((rtlefuse->
			     eeprom_chnlarea_txpwr_ht40_1s[rf_path][index] -
			     rtlefuse->
			     eprom_chnl_txpwr_ht40_2sdf[rf_path][index])
			    > 0) अणु
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i] =
				    rtlefuse->
				    eeprom_chnlarea_txpwr_ht40_1s[rf_path]
				    [index] -
				    rtlefuse->
				    eprom_chnl_txpwr_ht40_2sdf[rf_path]
				    [index];
			पूर्ण अन्यथा अणु
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i] = 0;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < 14; i++) अणु
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF(%d)-Ch(%d) [CCK / HT40_1S / HT40_2S] = [0x%x / 0x%x / 0x%x]\n",
				rf_path, i,
				rtlefuse->txpwrlevel_cck[rf_path][i],
				rtlefuse->txpwrlevel_ht40_1s[rf_path][i],
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		अगर (!स्वतःload_fail) अणु
			rtlefuse->eeprom_pwrlimit_ht40[i] =
			    hwinfo[EEPROM_TXPWR_GROUP + i];
			rtlefuse->eeprom_pwrlimit_ht20[i] =
			    hwinfo[EEPROM_TXPWR_GROUP + 3 + i];
		पूर्ण अन्यथा अणु
			rtlefuse->eeprom_pwrlimit_ht40[i] = 0;
			rtlefuse->eeprom_pwrlimit_ht20[i] = 0;
		पूर्ण
	पूर्ण

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 14; i++) अणु
			index = rtl92c_get_chnl_group((u8)i);

			अगर (rf_path == RF90_PATH_A) अणु
				rtlefuse->pwrgroup_ht20[rf_path][i] =
				    (rtlefuse->eeprom_pwrlimit_ht20[index]
				     & 0xf);
				rtlefuse->pwrgroup_ht40[rf_path][i] =
				    (rtlefuse->eeprom_pwrlimit_ht40[index]
				     & 0xf);
			पूर्ण अन्यथा अगर (rf_path == RF90_PATH_B) अणु
				rtlefuse->pwrgroup_ht20[rf_path][i] =
				    ((rtlefuse->eeprom_pwrlimit_ht20[index]
				      & 0xf0) >> 4);
				rtlefuse->pwrgroup_ht40[rf_path][i] =
				    ((rtlefuse->eeprom_pwrlimit_ht40[index]
				      & 0xf0) >> 4);
			पूर्ण

			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF-%d pwrgroup_ht20[%d] = 0x%x\n",
				rf_path, i,
				rtlefuse->pwrgroup_ht20[rf_path][i]);
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF-%d pwrgroup_ht40[%d] = 0x%x\n",
				rf_path, i,
				rtlefuse->pwrgroup_ht40[rf_path][i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 14; i++) अणु
		index = rtl92c_get_chnl_group((u8)i);

		अगर (!स्वतःload_fail)
			tempval = hwinfo[EEPROM_TXPOWERHT20DIFF + index];
		अन्यथा
			tempval = EEPROM_DEFAULT_HT20_DIFF;

		rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i] = (tempval & 0xF);
		rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i] =
		    ((tempval >> 4) & 0xF);

		अगर (rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i] & BIT(3))
			rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i] |= 0xF0;

		अगर (rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i] & BIT(3))
			rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i] |= 0xF0;

		index = rtl92c_get_chnl_group((u8)i);

		अगर (!स्वतःload_fail)
			tempval = hwinfo[EEPROM_TXPOWER_OFDMDIFF + index];
		अन्यथा
			tempval = EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF;

		rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][i] = (tempval & 0xF);
		rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_B][i] =
		    ((tempval >> 4) & 0xF);
	पूर्ण

	rtlefuse->legacy_ht_txघातerdअगरf =
	    rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][7];

	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-A Ht20 to HT40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i]);
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-A Legacy to Ht40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][i]);
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-B Ht20 to HT40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i]);
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-B Legacy to HT40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_B][i]);

	अगर (!स्वतःload_fail)
		rtlefuse->eeprom_regulatory = (hwinfo[RF_OPTION1] & 0x7);
	अन्यथा
		rtlefuse->eeprom_regulatory = 0;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"eeprom_regulatory = 0x%x\n", rtlefuse->eeprom_regulatory);

	अगर (!स्वतःload_fail) अणु
		rtlefuse->eeprom_tssi[RF90_PATH_A] = hwinfo[EEPROM_TSSI_A];
		rtlefuse->eeprom_tssi[RF90_PATH_B] = hwinfo[EEPROM_TSSI_B];
	पूर्ण अन्यथा अणु
		rtlefuse->eeprom_tssi[RF90_PATH_A] = EEPROM_DEFAULT_TSSI;
		rtlefuse->eeprom_tssi[RF90_PATH_B] = EEPROM_DEFAULT_TSSI;
	पूर्ण
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER, "TSSI_A = 0x%x, TSSI_B = 0x%x\n",
		rtlefuse->eeprom_tssi[RF90_PATH_A],
		rtlefuse->eeprom_tssi[RF90_PATH_B]);

	अगर (!स्वतःload_fail)
		tempval = hwinfo[EEPROM_THERMAL_METER];
	अन्यथा
		tempval = EEPROM_DEFAULT_THERMALMETER;
	rtlefuse->eeprom_thermalmeter = (tempval & 0x1f);

	अगर (rtlefuse->eeprom_thermalmeter == 0x1f || स्वतःload_fail)
		rtlefuse->apk_thermalmeterignore = true;

	rtlefuse->thermalmeter[0] = rtlefuse->eeprom_thermalmeter;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"thermalmeter = 0x%x\n", rtlefuse->eeprom_thermalmeter);
पूर्ण

अटल व्योम _rtl92ce_पढ़ो_adapter_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक params[] = अणुRTL8190_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13पूर्ण;
	u8 *hwinfo;

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	अगर (!hwinfo)
		वापस;

	अगर (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		जाओ निकास;

	_rtl92ce_पढ़ो_txघातer_info_from_hwpg(hw,
					     rtlefuse->स्वतःload_failflag,
					     hwinfo);

	rtl8192ce_पढ़ो_bt_coexist_info_from_hwpg(hw,
						 rtlefuse->स्वतःload_failflag,
						 hwinfo);
	अगर (rtlhal->oem_id == RT_CID_DEFAULT) अणु
		चयन (rtlefuse->eeprom_oemid) अणु
		हाल EEPROM_CID_DEFAULT:
			अगर (rtlefuse->eeprom_did == 0x8176) अणु
				अगर ((rtlefuse->eeprom_svid == 0x103C &&
				     rtlefuse->eeprom_smid == 0x1629))
					rtlhal->oem_id = RT_CID_819X_HP;
				अन्यथा
					rtlhal->oem_id = RT_CID_DEFAULT;
			पूर्ण अन्यथा अणु
				rtlhal->oem_id = RT_CID_DEFAULT;
			पूर्ण
			अवरोध;
		हाल EEPROM_CID_TOSHIBA:
			rtlhal->oem_id = RT_CID_TOSHIBA;
			अवरोध;
		हाल EEPROM_CID_QMI:
			rtlhal->oem_id = RT_CID_819X_QMI;
			अवरोध;
		हाल EEPROM_CID_WHQL:
		शेष:
			rtlhal->oem_id = RT_CID_DEFAULT;
			अवरोध;
		पूर्ण
	पूर्ण
निकास:
	kमुक्त(hwinfo);
पूर्ण

अटल व्योम _rtl92ce_hal_customized_behavior(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	चयन (rtlhal->oem_id) अणु
	हाल RT_CID_819X_HP:
		rtlpriv->ledctl.led_खोलोdrain = true;
		अवरोध;
	हाल RT_CID_819X_LENOVO:
	हाल RT_CID_DEFAULT:
	हाल RT_CID_TOSHIBA:
	हाल RT_CID_CCX:
	हाल RT_CID_819X_ACER:
	हाल RT_CID_WHQL:
	शेष:
		अवरोध;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
		"RT Customized ID: 0x%02X\n", rtlhal->oem_id);
पूर्ण

व्योम rtl92ce_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_u1b;

	rtlhal->version = _rtl92ce_पढ़ो_chip_version(hw);
	अगर (get_rf_type(rtlphy) == RF_1T1R)
		rtlpriv->dm.rfpath_rxenable[0] = true;
	अन्यथा
		rtlpriv->dm.rfpath_rxenable[0] =
		    rtlpriv->dm.rfpath_rxenable[1] = true;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "VersionID = 0x%4x\n",
		rtlhal->version);
	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_9346CR);
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
		_rtl92ce_पढ़ो_adapter_info(hw);
	पूर्ण अन्यथा अणु
		pr_err("Autoload ERR!!\n");
	पूर्ण
	_rtl92ce_hal_customized_behavior(hw);
पूर्ण

अटल व्योम rtl92ce_update_hal_rate_table(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 ratr_value;
	u8 ratr_index = 0;
	u8 nmode = mac->ht_enable;
	u16 लघुgi_rate;
	u32 पंचांगp_ratr_value;
	u8 curtxbw_40mhz = mac->bw_40;
	u8 curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
			       1 : 0;
	u8 curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
			       1 : 0;
	क्रमागत wireless_mode wirelessmode = mac->mode;
	u32 ratr_mask;

	अगर (rtlhal->current_bandtype == BAND_ON_5G)
		ratr_value = sta->supp_rates[1] << 4;
	अन्यथा
		ratr_value = sta->supp_rates[0];
	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_value = 0xfff;

	ratr_value |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
			sta->ht_cap.mcs.rx_mask[0] << 12);
	चयन (wirelessmode) अणु
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
		अगर (get_rf_type(rtlphy) == RF_1T2R ||
		    get_rf_type(rtlphy) == RF_1T1R)
			ratr_mask = 0x000ff005;
		अन्यथा
			ratr_mask = 0x0f0ff005;

		ratr_value &= ratr_mask;
		अवरोध;
	शेष:
		अगर (rtlphy->rf_type == RF_1T2R)
			ratr_value &= 0x000ff0ff;
		अन्यथा
			ratr_value &= 0x0f0ff0ff;

		अवरोध;
	पूर्ण

	अगर ((rtlpriv->btcoexist.bt_coexistence) &&
	    (rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4) &&
	    (rtlpriv->btcoexist.bt_cur_state) &&
	    (rtlpriv->btcoexist.bt_ant_isolation) &&
	    ((rtlpriv->btcoexist.bt_service == BT_SCO) ||
	    (rtlpriv->btcoexist.bt_service == BT_BUSY)))
		ratr_value &= 0x0fffcfc0;
	अन्यथा
		ratr_value &= 0x0FFFFFFF;

	अगर (nmode && ((curtxbw_40mhz &&
			 curलघुgi_40mhz) || (!curtxbw_40mhz &&
					       curलघुgi_20mhz))) अणु

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

अटल व्योम rtl92ce_update_hal_rate_mask(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u32 ratr_biपंचांगap;
	u8 ratr_index;
	u8 curtxbw_40mhz = (sta->ht_cap.cap &
			    IEEE80211_HT_CAP_SUP_WIDTH_20_40) ? 1 : 0;
	u8 curलघुgi_40mhz = (sta->ht_cap.cap &
			       IEEE80211_HT_CAP_SGI_40) ?  1 : 0;
	u8 curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	क्रमागत wireless_mode wirelessmode = 0;
	bool लघुgi = false;
	u8 rate_mask[5];
	u8 macid = 0;

	sta_entry = (काष्ठा rtl_sta_info *) sta->drv_priv;
	wirelessmode = sta_entry->wireless_mode;
	अगर (mac->opmode == NL80211_IFTYPE_STATION ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT)
		curtxbw_40mhz = mac->bw_40;
	अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;

	अगर (rtlhal->current_bandtype == BAND_ON_5G)
		ratr_biपंचांगap = sta->supp_rates[1] << 4;
	अन्यथा
		ratr_biपंचांगap = sta->supp_rates[0];
	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_biपंचांगap = 0xfff;
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
		ratr_index = RATR_INX_WIRELESS_A;
		ratr_biपंचांगap &= 0x00000ff0;
		अवरोध;
	हाल WIRELESS_MODE_N_24G:
	हाल WIRELESS_MODE_N_5G:
		ratr_index = RATR_INX_WIRELESS_NGB;

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
	sta_entry->ratr_index = ratr_index;

	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"ratr_bitmap :%x\n", ratr_biपंचांगap);
	*(u32 *)&rate_mask = (ratr_biपंचांगap & 0x0fffffff) |
				     (ratr_index << 28);
	rate_mask[4] = macid | (लघुgi ? 0x20 : 0x00) | 0x80;
	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"Rate_index:%x, ratr_val:%x, %5phC\n",
		ratr_index, ratr_biपंचांगap, rate_mask);
	rtl92c_fill_h2c_cmd(hw, H2C_RA_MASK, 5, rate_mask);
पूर्ण

व्योम rtl92ce_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->dm.useramask)
		rtl92ce_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
	अन्यथा
		rtl92ce_update_hal_rate_table(hw, sta);
पूर्ण

व्योम rtl92ce_update_channel_access_setting(काष्ठा ieee80211_hw *hw)
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

bool rtl92ce_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid)
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
		       REG_MAC_PINMUX_CFG)&~(BIT(3)));

	u1पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_IO_SEL);
	e_rfघातerstate_toset = (u1पंचांगp & BIT(3)) ? ERFON : ERFOFF;

	अगर ((ppsc->hwradiooff) && (e_rfघातerstate_toset == ERFON)) अणु
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

व्योम rtl92ce_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddr, bool is_group, u8 enc_algo,
		     bool is_wepkey, bool clear_all)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 *macaddr = p_macaddr;
	u32 entry_id = 0;
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
		u8 idx = 0;
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
				अगर (mac->opmode == NL80211_IFTYPE_AP ||
				    mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
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
			अगर (mac->opmode == NL80211_IFTYPE_AP ||
			    mac->opmode == NL80211_IFTYPE_MESH_POINT)
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
					      rtlpriv->sec.
					      key_len[PAIRWISE_KEYIDX]);

				rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
					"set Pairwise key\n");

				rtl_cam_add_one_entry(hw, macaddr, key_index,
						      entry_id, enc_algo,
						      CAM_CONFIG_NO_USEDK,
						      rtlpriv->sec.
						      key_buf[key_index]);
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
					"set group key\n");

				अगर (mac->opmode == NL80211_IFTYPE_ADHOC) अणु
					rtl_cam_add_one_entry(hw,
						rtlefuse->dev_addr,
						PAIRWISE_KEYIDX,
						CAM_PAIRWISE_KEY_POSITION,
						enc_algo,
						CAM_CONFIG_NO_USEDK,
						rtlpriv->sec.key_buf
						[entry_id]);
				पूर्ण

				rtl_cam_add_one_entry(hw, macaddr, key_index,
						entry_id, enc_algo,
						CAM_CONFIG_NO_USEDK,
						rtlpriv->sec.key_buf[entry_id]);
			पूर्ण

		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl8192ce_bt_var_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->btcoexist.bt_coexistence =
			rtlpriv->btcoexist.eeprom_bt_coexist;
	rtlpriv->btcoexist.bt_ant_num =
			rtlpriv->btcoexist.eeprom_bt_ant_num;
	rtlpriv->btcoexist.bt_coexist_type =
			rtlpriv->btcoexist.eeprom_bt_type;

	अगर (rtlpriv->btcoexist.reg_bt_iso == 2)
		rtlpriv->btcoexist.bt_ant_isolation =
			rtlpriv->btcoexist.eeprom_bt_ant_isol;
	अन्यथा
		rtlpriv->btcoexist.bt_ant_isolation =
			rtlpriv->btcoexist.reg_bt_iso;

	rtlpriv->btcoexist.bt_radio_shared_type =
			rtlpriv->btcoexist.eeprom_bt_radio_shared;

	अगर (rtlpriv->btcoexist.bt_coexistence) अणु
		अगर (rtlpriv->btcoexist.reg_bt_sco == 1)
			rtlpriv->btcoexist.bt_service = BT_OTHER_ACTION;
		अन्यथा अगर (rtlpriv->btcoexist.reg_bt_sco == 2)
			rtlpriv->btcoexist.bt_service = BT_SCO;
		अन्यथा अगर (rtlpriv->btcoexist.reg_bt_sco == 4)
			rtlpriv->btcoexist.bt_service = BT_BUSY;
		अन्यथा अगर (rtlpriv->btcoexist.reg_bt_sco == 5)
			rtlpriv->btcoexist.bt_service = BT_OTHERBUSY;
		अन्यथा
			rtlpriv->btcoexist.bt_service = BT_IDLE;

		rtlpriv->btcoexist.bt_edca_ul = 0;
		rtlpriv->btcoexist.bt_edca_dl = 0;
		rtlpriv->btcoexist.bt_rssi_state = 0xff;
	पूर्ण
पूर्ण

व्योम rtl8192ce_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
					      bool स्वतः_load_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 val;

	अगर (!स्वतः_load_fail) अणु
		rtlpriv->btcoexist.eeprom_bt_coexist =
					((hwinfo[RF_OPTION1] & 0xe0) >> 5);
		val = hwinfo[RF_OPTION4];
		rtlpriv->btcoexist.eeprom_bt_type = ((val & 0xe) >> 1);
		rtlpriv->btcoexist.eeprom_bt_ant_num = (val & 0x1);
		rtlpriv->btcoexist.eeprom_bt_ant_isol = ((val & 0x10) >> 4);
		rtlpriv->btcoexist.eeprom_bt_radio_shared =
							 ((val & 0x20) >> 5);
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.eeprom_bt_coexist = 0;
		rtlpriv->btcoexist.eeprom_bt_type = BT_2WIRE;
		rtlpriv->btcoexist.eeprom_bt_ant_num = ANT_X2;
		rtlpriv->btcoexist.eeprom_bt_ant_isol = 0;
		rtlpriv->btcoexist.eeprom_bt_radio_shared = BT_RADIO_SHARED;
	पूर्ण

	rtl8192ce_bt_var_init(hw);
पूर्ण

व्योम rtl8192ce_bt_reg_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* 0:Low, 1:High, 2:From Efuse. */
	rtlpriv->btcoexist.reg_bt_iso = 2;
	/* 0:Idle, 1:None-SCO, 2:SCO, 3:From Counter. */
	rtlpriv->btcoexist.reg_bt_sco = 3;
	/* 0:Disable BT control A-MPDU, 1:Enable BT control A-MPDU. */
	rtlpriv->btcoexist.reg_bt_sco = 0;
पूर्ण

व्योम rtl8192ce_bt_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	u8 u1_पंचांगp;

	अगर (rtlpriv->btcoexist.bt_coexistence &&
	    ((rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4) ||
	      rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC8)) अणु

		अगर (rtlpriv->btcoexist.bt_ant_isolation)
			rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG, 0xa0);

		u1_पंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x4fd) & BIT(0);
		u1_पंचांगp = u1_पंचांगp |
			 ((rtlpriv->btcoexist.bt_ant_isolation == 1) ?
			 0 : BIT(1)) |
			 ((rtlpriv->btcoexist.bt_service == BT_SCO) ?
			 0 : BIT(2));
		rtl_ग_लिखो_byte(rtlpriv, 0x4fd, u1_पंचांगp);

		rtl_ग_लिखो_dword(rtlpriv, REG_BT_COEX_TABLE+4, 0xaaaa9aaa);
		rtl_ग_लिखो_dword(rtlpriv, REG_BT_COEX_TABLE+8, 0xffbd0040);
		rtl_ग_लिखो_dword(rtlpriv, REG_BT_COEX_TABLE+0xc, 0x40000010);

		/* Config to 1T1R. */
		अगर (rtlphy->rf_type == RF_1T1R) अणु
			u1_पंचांगp = rtl_पढ़ो_byte(rtlpriv, ROFDM0_TRXPATHENABLE);
			u1_पंचांगp &= ~(BIT(1));
			rtl_ग_लिखो_byte(rtlpriv, ROFDM0_TRXPATHENABLE, u1_पंचांगp);

			u1_पंचांगp = rtl_पढ़ो_byte(rtlpriv, ROFDM1_TRXPATHENABLE);
			u1_पंचांगp &= ~(BIT(1));
			rtl_ग_लिखो_byte(rtlpriv, ROFDM1_TRXPATHENABLE, u1_पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92ce_suspend(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

व्योम rtl92ce_resume(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण
