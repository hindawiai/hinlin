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
#समावेश "../rtl8723com/phy_common.h"
#समावेश "dm.h"
#समावेश "../rtl8723com/dm_common.h"
#समावेश "fw.h"
#समावेश "../rtl8723com/fw_common.h"
#समावेश "led.h"
#समावेश "hw.h"
#समावेश "../pwrseqcmd.h"
#समावेश "pwrseq.h"
#समावेश "btc.h"

#घोषणा LLT_CONFIG	5

अटल व्योम _rtl8723e_set_bcn_ctrl_reg(काष्ठा ieee80211_hw *hw,
				       u8 set_bits, u8 clear_bits)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpci->reg_bcn_ctrl_val |= set_bits;
	rtlpci->reg_bcn_ctrl_val &= ~clear_bits;

	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8) rtlpci->reg_bcn_ctrl_val);
पूर्ण

अटल व्योम _rtl8723e_stop_tx_beacon(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl8723e_resume_tx_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp1byte;

	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp1byte | BIT(6));
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);
	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
	पंचांगp1byte |= BIT(1);
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, पंचांगp1byte);
पूर्ण

अटल व्योम _rtl8723e_enable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl8723e_set_bcn_ctrl_reg(hw, 0, BIT(1));
पूर्ण

अटल व्योम _rtl8723e_disable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl8723e_set_bcn_ctrl_reg(hw, BIT(1), 0);
पूर्ण

व्योम rtl8723e_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	चयन (variable) अणु
	हाल HW_VAR_RCR:
		*((u32 *)(val)) = rtlpci->receive_config;
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
				*((bool *)(val)) = true;
			पूर्ण अन्यथा अणु
				val_rcr = rtl_पढ़ो_dword(rtlpriv, REG_RCR);
				val_rcr &= 0x00070000;
				अगर (val_rcr)
					*((bool *)(val)) = false;
				अन्यथा
					*((bool *)(val)) = true;
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_FW_PSMODE_STATUS:
		*((bool *)(val)) = ppsc->fw_current_inpsmode;
		अवरोध;
	हाल HW_VAR_CORRECT_TSF:अणु
			u64 tsf;
			u32 *ptsf_low = (u32 *)&tsf;
			u32 *ptsf_high = ((u32 *)&tsf) + 1;

			*ptsf_high = rtl_पढ़ो_dword(rtlpriv, (REG_TSFTR + 4));
			*ptsf_low = rtl_पढ़ो_dword(rtlpriv, REG_TSFTR);

			*((u64 *)(val)) = tsf;

			अवरोध;
		पूर्ण
	हाल HAL_DEF_WOWLAN:
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl8723e_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
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
			u16 b_rate_cfg = ((u16 *)val)[0];
			u8 rate_index = 0;

			b_rate_cfg = b_rate_cfg & 0x15f;
			b_rate_cfg |= 0x01;
			rtl_ग_लिखो_byte(rtlpriv, REG_RRSR, b_rate_cfg & 0xff);
			rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 1,
				       (b_rate_cfg >> 8) & 0xff);
			जबतक (b_rate_cfg > 0x1) अणु
				b_rate_cfg = (b_rate_cfg >> 1);
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
					       *((u16 *)val));
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
							      (u8 *)(&e_aci));
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_ACK_PREAMBLE:अणु
			u8 reg_पंचांगp;
			u8 लघु_preamble = (bool)(*(u8 *)val);

			reg_पंचांगp = (mac->cur_40_prime_sc) << 5;
			अगर (लघु_preamble)
				reg_पंचांगp |= 0x80;

			rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 2, reg_पंचांगp);
			अवरोध;
		पूर्ण
	हाल HW_VAR_AMPDU_MIN_SPACE:अणु
			u8 min_spacing_to_set;
			u8 sec_min_space;

			min_spacing_to_set = *((u8 *)val);
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

			density_to_set = *((u8 *)val);
			mac->min_space_cfg |= (density_to_set << 3);

			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"Set HW_VAR_SHORTGI_DENSITY: %#x\n",
				mac->min_space_cfg);

			rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE,
				       mac->min_space_cfg);

			अवरोध;
		पूर्ण
	हाल HW_VAR_AMPDU_FACTOR:अणु
			u8 regtoset_normal[4] = अणु 0x41, 0xa8, 0x72, 0xb9 पूर्ण;
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

			factor_toset = *((u8 *)val);
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
			u8 e_aci = *((u8 *)val);

			rtl8723_dm_init_edca_turbo(hw);

			अगर (rtlpci->acm_method != EACMWAY2_SW)
				rtlpriv->cfg->ops->set_hw_reg(hw,
							      HW_VAR_ACM_CTRL,
							      (u8 *)(&e_aci));
			अवरोध;
		पूर्ण
	हाल HW_VAR_ACM_CTRL:अणु
			u8 e_aci = *((u8 *)val);
			जोड़ aci_aअगरsn *p_aci_aअगरsn =
			    (जोड़ aci_aअगरsn *)(&mac->ac[0].aअगरs);
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
					rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
						"switch case %#x not processed\n",
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
			rtl_ग_लिखो_dword(rtlpriv, REG_RCR, ((u32 *)(val))[0]);
			rtlpci->receive_config = ((u32 *)(val))[0];
			अवरोध;
		पूर्ण
	हाल HW_VAR_RETRY_LIMIT:अणु
			u8 retry_limit = ((u8 *)(val))[0];

			rtl_ग_लिखो_word(rtlpriv, REG_RL,
				       retry_limit << RETRY_LIMIT_SHORT_SHIFT |
				       retry_limit << RETRY_LIMIT_LONG_SHIFT);
			अवरोध;
		पूर्ण
	हाल HW_VAR_DUAL_TSF_RST:
		rtl_ग_लिखो_byte(rtlpriv, REG_DUAL_TSF_RST, (BIT(0) | BIT(1)));
		अवरोध;
	हाल HW_VAR_EFUSE_BYTES:
		rtlefuse->efuse_usedbytes = *((u16 *)val);
		अवरोध;
	हाल HW_VAR_EFUSE_USAGE:
		rtlefuse->efuse_usedpercentage = *((u8 *)val);
		अवरोध;
	हाल HW_VAR_IO_CMD:
		rtl8723e_phy_set_io_cmd(hw, (*(क्रमागत io_type *)val));
		अवरोध;
	हाल HW_VAR_WPA_CONFIG:
		rtl_ग_लिखो_byte(rtlpriv, REG_SECCFG, *((u8 *)val));
		अवरोध;
	हाल HW_VAR_SET_RPWM:अणु
			u8 rpwm_val;

			rpwm_val = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_HRPWM);
			udelay(1);

			अगर (rpwm_val & BIT(7)) अणु
				rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_HRPWM,
					       (*(u8 *)val));
			पूर्ण अन्यथा अणु
				rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_HRPWM,
					       ((*(u8 *)val) | BIT(7)));
			पूर्ण

			अवरोध;
		पूर्ण
	हाल HW_VAR_H2C_FW_PWRMODE:अणु
			u8 psmode = (*(u8 *)val);

			अगर (psmode != FW_PS_ACTIVE_MODE)
				rtl8723e_dm_rf_saving(hw, true);

			rtl8723e_set_fw_pwrmode_cmd(hw, (*(u8 *)val));
			अवरोध;
		पूर्ण
	हाल HW_VAR_FW_PSMODE_STATUS:
		ppsc->fw_current_inpsmode = *((bool *)val);
		अवरोध;
	हाल HW_VAR_H2C_FW_JOINBSSRPT:अणु
			u8 mstatus = (*(u8 *)val);
			u8 पंचांगp_regcr, पंचांगp_reg422;
			bool b_recover = false;

			अगर (mstatus == RT_MEDIA_CONNECT) अणु
				rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AID,
							      शून्य);

				पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
				rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1,
					       (पंचांगp_regcr | BIT(0)));

				_rtl8723e_set_bcn_ctrl_reg(hw, 0, BIT(3));
				_rtl8723e_set_bcn_ctrl_reg(hw, BIT(4), 0);

				पंचांगp_reg422 =
				    rtl_पढ़ो_byte(rtlpriv,
						  REG_FWHW_TXQ_CTRL + 2);
				अगर (पंचांगp_reg422 & BIT(6))
					b_recover = true;
				rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2,
					       पंचांगp_reg422 & (~BIT(6)));

				rtl8723e_set_fw_rsvdpagepkt(hw, 0);

				_rtl8723e_set_bcn_ctrl_reg(hw, BIT(3), 0);
				_rtl8723e_set_bcn_ctrl_reg(hw, 0, BIT(4));

				अगर (b_recover) अणु
					rtl_ग_लिखो_byte(rtlpriv,
						       REG_FWHW_TXQ_CTRL + 2,
						       पंचांगp_reg422);
				पूर्ण

				rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1,
					       (पंचांगp_regcr & ~(BIT(0))));
			पूर्ण
			rtl8723e_set_fw_joinbss_report_cmd(hw, (*(u8 *)val));

			अवरोध;
		पूर्ण
	हाल HW_VAR_H2C_FW_P2P_PS_OFFLOAD:अणु
		rtl8723e_set_p2p_ps_offload_cmd(hw, (*(u8 *)val));
		अवरोध;
	पूर्ण
	हाल HW_VAR_AID:अणु
			u16 u2bपंचांगp;

			u2bपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_BCN_PSR_RPT);
			u2bपंचांगp &= 0xC000;
			rtl_ग_लिखो_word(rtlpriv, REG_BCN_PSR_RPT,
				       (u2bपंचांगp | mac->assoc_id));

			अवरोध;
		पूर्ण
	हाल HW_VAR_CORRECT_TSF:अणु
			u8 btype_ibss = ((u8 *)(val))[0];

			अगर (btype_ibss)
				_rtl8723e_stop_tx_beacon(hw);

			_rtl8723e_set_bcn_ctrl_reg(hw, 0, BIT(3));

			rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR,
					(u32)(mac->tsf & 0xffffffff));
			rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR + 4,
					(u32)((mac->tsf >> 32) & 0xffffffff));

			_rtl8723e_set_bcn_ctrl_reg(hw, BIT(3), 0);

			अगर (btype_ibss)
				_rtl8723e_resume_tx_beacon(hw);

			अवरोध;
		पूर्ण
	हाल HW_VAR_FW_LPS_ACTION:अणु
			bool b_enter_fwlps = *((bool *)val);
			u8 rpwm_val, fw_pwrmode;
			bool fw_current_inps;

			अगर (b_enter_fwlps) अणु
				rpwm_val = 0x02;	/* RF off */
				fw_current_inps = true;
				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_FW_PSMODE_STATUS,
						(u8 *)(&fw_current_inps));
				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_H2C_FW_PWRMODE,
						(u8 *)(&ppsc->fwctrl_psmode));

				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_SET_RPWM,
						(u8 *)(&rpwm_val));
			पूर्ण अन्यथा अणु
				rpwm_val = 0x0C;	/* RF on */
				fw_pwrmode = FW_PS_ACTIVE_MODE;
				fw_current_inps = false;
				rtlpriv->cfg->ops->set_hw_reg(hw,
							      HW_VAR_SET_RPWM,
							      (u8 *)(&rpwm_val));
				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_H2C_FW_PWRMODE,
						(u8 *)(&fw_pwrmode));

				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_FW_PSMODE_STATUS,
						(u8 *)(&fw_current_inps));
			पूर्ण
			 अवरोध;
		पूर्ण
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool _rtl8723e_llt_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 address, u32 data)
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

अटल bool _rtl8723e_llt_table_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अचिन्हित लघु i;
	u8 txpktbuf_bndy;
	u8 maxpage;
	bool status;
	u8 ubyte;

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

	rtl_ग_लिखो_byte(rtlpriv, REG_CR, 0x8B);

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

	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, 0x80ac1c29);
	rtl_ग_लिखो_byte(rtlpriv, REG_RQPN_NPQ, 0x03);
#पूर्ण_अगर

	rtl_ग_लिखो_dword(rtlpriv, REG_TRXFF_BNDY, (0x27FF0000 | txpktbuf_bndy));
	rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 1, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, 0x45D, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_PBP, 0x11);
	rtl_ग_लिखो_byte(rtlpriv, REG_RX_DRVINFO_SZ, 0x4);

	क्रम (i = 0; i < (txpktbuf_bndy - 1); i++) अणु
		status = _rtl8723e_llt_ग_लिखो(hw, i, i + 1);
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl8723e_llt_ग_लिखो(hw, (txpktbuf_bndy - 1), 0xFF);
	अगर (!status)
		वापस status;

	क्रम (i = txpktbuf_bndy; i < maxpage; i++) अणु
		status = _rtl8723e_llt_ग_लिखो(hw, i, (i + 1));
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl8723e_llt_ग_लिखो(hw, maxpage, txpktbuf_bndy);
	अगर (!status)
		वापस status;

	rtl_ग_लिखो_byte(rtlpriv, REG_CR, 0xff);
	ubyte = rtl_पढ़ो_byte(rtlpriv, REG_RQPN + 3);
	rtl_ग_लिखो_byte(rtlpriv, REG_RQPN + 3, ubyte | BIT(7));

	वापस true;
पूर्ण

अटल व्योम _rtl8723e_gen_refresh_led_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;

	अगर (rtlpriv->rtlhal.up_first_समय)
		वापस;

	अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
		rtl8723e_sw_led_on(hw, pled0);
	अन्यथा अगर (ppsc->rfoff_reason == RF_CHANGE_BY_INIT)
		rtl8723e_sw_led_on(hw, pled0);
	अन्यथा
		rtl8723e_sw_led_off(hw, pled0);
पूर्ण

अटल bool _rtl8712e_init_mac(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	अचिन्हित अक्षर byteपंचांगp;
	अचिन्हित लघु wordपंचांगp;
	u16 retry = 0;
	u16 पंचांगpu2b;
	bool mac_func_enable;

	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x00);
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_CR);
	अगर (byteपंचांगp == 0xFF)
		mac_func_enable = true;
	अन्यथा
		mac_func_enable = false;

	/* HW Power on sequence */
	अगर (!rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
		PWR_INTF_PCI_MSK, RTL8723_NIC_ENABLE_FLOW))
		वापस false;

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_CTRL_REG+2);
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG+2, byteपंचांगp | BIT(4));

	/* eMAC समय out function enable, 0x369[7]=1 */
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x369);
	rtl_ग_लिखो_byte(rtlpriv, 0x369, byteपंचांगp | BIT(7));

	/* ePHY reg 0x1e bit[4]=1 using MDIO पूर्णांकerface,
	 * we should करो this beक्रमe Enabling ASPM backकरोor.
	 */
	करो अणु
		rtl_ग_लिखो_word(rtlpriv, 0x358, 0x5e);
		udelay(100);
		rtl_ग_लिखो_word(rtlpriv, 0x356, 0xc280);
		rtl_ग_लिखो_word(rtlpriv, 0x354, 0xc290);
		rtl_ग_लिखो_word(rtlpriv, 0x358, 0x3e);
		udelay(100);
		rtl_ग_लिखो_word(rtlpriv, 0x358, 0x5e);
		udelay(100);
		पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, 0x356);
		retry++;
	पूर्ण जबतक (पंचांगpu2b != 0xc290 && retry < 100);

	अगर (retry >= 100) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"InitMAC(): ePHY configure fail!!!\n");
		वापस false;
	पूर्ण

	rtl_ग_लिखो_word(rtlpriv, REG_CR, 0x2ff);
	rtl_ग_लिखो_word(rtlpriv, REG_CR + 1, 0x06);

	अगर (!mac_func_enable) अणु
		अगर (!_rtl8723e_llt_table_init(hw))
			वापस false;
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, REG_HISR, 0xffffffff);
	rtl_ग_लिखो_byte(rtlpriv, REG_HISRE, 0xff);

	rtl_ग_लिखो_word(rtlpriv, REG_TRXFF_BNDY + 2, 0x27ff);

	wordपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_TRXDMA_CTRL);
	wordपंचांगp &= 0xf;
	wordपंचांगp |= 0xF771;
	rtl_ग_लिखो_word(rtlpriv, REG_TRXDMA_CTRL, wordपंचांगp);

	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 1, 0x1F);
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);
	rtl_ग_लिखो_word(rtlpriv, REG_RXFLTMAP2, 0xFFFF);
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

	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 3, 0x74);

	rtl_ग_लिखो_dword(rtlpriv, REG_INT_MIG, 0);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APSD_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, byteपंचांगp & ~BIT(6));
	करो अणु
		retry++;
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APSD_CTRL);
	पूर्ण जबतक ((retry < 200) && (byteपंचांगp & BIT(7)));

	_rtl8723e_gen_refresh_led_state(hw);

	rtl_ग_लिखो_dword(rtlpriv, REG_MCUTST_1, 0x0);

	वापस true;
पूर्ण

अटल व्योम _rtl8723e_hw_configure(काष्ठा ieee80211_hw *hw)
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

	rtl_ग_लिखो_dword(rtlpriv, 0x394, 0x1);
पूर्ण

अटल व्योम _rtl8723e_enable_aspm_back_करोor(काष्ठा ieee80211_hw *hw)
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

व्योम rtl8723e_enable_hw_security_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 sec_reg_value;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
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

	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
		"The SECR-value %x\n", sec_reg_value);

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_WPA_CONFIG, &sec_reg_value);

पूर्ण

पूर्णांक rtl8723e_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	bool rtstatus = true;
	पूर्णांक err;
	u8 पंचांगp_u1b;
	अचिन्हित दीर्घ flags;

	rtlpriv->rtlhal.being_init_adapter = true;
	/* As this function can take a very दीर्घ समय (up to 350 ms)
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
	rtstatus = _rtl8712e_init_mac(hw);
	अगर (!rtstatus) अणु
		pr_err("Init MAC failed\n");
		err = 1;
		जाओ निकास;
	पूर्ण

	err = rtl8723_करोwnload_fw(hw, false, FW_8723A_POLLING_TIMEOUT_COUNT);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Failed to download FW. Init HW without FW now..\n");
		err = 1;
		जाओ निकास;
	पूर्ण
	rtlhal->fw_पढ़ोy = true;

	rtlhal->last_hmeboxnum = 0;
	rtl8723e_phy_mac_config(hw);
	/* because last function modअगरy RCR, so we update
	 * rcr var here, or TP will unstable क्रम receive_config
	 * is wrong, RX RCR_ACRC32 will cause TP unstable & Rx
	 * RCR_APP_ICV will cause mac80211 unassoc क्रम cisco 1252
	 */
	rtlpci->receive_config = rtl_पढ़ो_dword(rtlpriv, REG_RCR);
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);

	rtl8723e_phy_bb_config(hw);
	rtlphy->rf_mode = RF_OP_BY_SW_3WIRE;
	rtl8723e_phy_rf_config(hw);
	अगर (IS_VENDOR_UMC_A_CUT(rtlhal->version)) अणु
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
	_rtl8723e_hw_configure(hw);
	rtl_cam_reset_all_entry(hw);
	rtl8723e_enable_hw_security_config(hw);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	_rtl8723e_enable_aspm_back_करोor(hw);
	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);

	rtl8723e_bt_hw_init(hw);

	अगर (ppsc->rfpwr_state == ERFON) अणु
		rtl8723e_phy_set_rfpath_चयन(hw, 1);
		अगर (rtlphy->iqk_initialized) अणु
			rtl8723e_phy_iq_calibrate(hw, true);
		पूर्ण अन्यथा अणु
			rtl8723e_phy_iq_calibrate(hw, false);
			rtlphy->iqk_initialized = true;
		पूर्ण

		rtl8723e_dm_check_txघातer_tracking(hw);
		rtl8723e_phy_lc_calibrate(hw);
	पूर्ण

	पंचांगp_u1b = efuse_पढ़ो_1byte(hw, 0x1FA);
	अगर (!(पंचांगp_u1b & BIT(0))) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0F, 0x05);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "PA BIAS path A\n");
	पूर्ण

	अगर (!(पंचांगp_u1b & BIT(4))) अणु
		पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, 0x16);
		पंचांगp_u1b &= 0x0F;
		rtl_ग_लिखो_byte(rtlpriv, 0x16, पंचांगp_u1b | 0x80);
		udelay(10);
		rtl_ग_लिखो_byte(rtlpriv, 0x16, पंचांगp_u1b | 0x90);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "under 1.5V\n");
	पूर्ण
	rtl8723e_dm_init(hw);
निकास:
	local_irq_restore(flags);
	rtlpriv->rtlhal.being_init_adapter = false;
	वापस err;
पूर्ण

अटल क्रमागत version_8723e _rtl8723e_पढ़ो_chip_version(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	क्रमागत version_8723e version = 0x0000;
	u32 value32;

	value32 = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG);
	अगर (value32 & TRP_VAUX_EN) अणु
		version = (क्रमागत version_8723e)(version |
			((value32 & VENDOR_ID) ? CHIP_VENDOR_UMC : 0));
		/* RTL8723 with BT function. */
		version = (क्रमागत version_8723e)(version |
			((value32 & BT_FUNC) ? CHIP_8723 : 0));

	पूर्ण अन्यथा अणु
		/* Normal mass production chip. */
		version = (क्रमागत version_8723e) NORMAL_CHIP;
		version = (क्रमागत version_8723e)(version |
			((value32 & VENDOR_ID) ? CHIP_VENDOR_UMC : 0));
		/* RTL8723 with BT function. */
		version = (क्रमागत version_8723e)(version |
			((value32 & BT_FUNC) ? CHIP_8723 : 0));
		अगर (IS_CHIP_VENDOR_UMC(version))
			version = (क्रमागत version_8723e)(version |
			((value32 & CHIP_VER_RTL_MASK)));/* IC version (CUT) */
		अगर (IS_8723_SERIES(version)) अणु
			value32 = rtl_पढ़ो_dword(rtlpriv, REG_GPIO_OUTSTS);
			/* ROM code version. */
			version = (क्रमागत version_8723e)(version |
				((value32 & RF_RL_ID)>>20));
		पूर्ण
	पूर्ण

	अगर (IS_8723_SERIES(version)) अणु
		value32 = rtl_पढ़ो_dword(rtlpriv, REG_MULTI_FUNC_CTRL);
		rtlphy->polarity_ctl = ((value32 & WL_HWPDN_SL) ?
					RT_POLARITY_HIGH_ACT :
					RT_POLARITY_LOW_ACT);
	पूर्ण
	चयन (version) अणु
	हाल VERSION_TEST_UMC_CHIP_8723:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Chip Version ID: VERSION_TEST_UMC_CHIP_8723.\n");
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_8723_1T1R_A_CUT:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Chip Version ID: VERSION_NORMAL_UMC_CHIP_8723_1T1R_A_CUT.\n");
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_8723_1T1R_B_CUT:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Chip Version ID: VERSION_NORMAL_UMC_CHIP_8723_1T1R_B_CUT.\n");
		अवरोध;
	शेष:
		pr_err("Chip Version ID: Unknown. Bug?\n");
		अवरोध;
	पूर्ण

	अगर (IS_8723_SERIES(version))
		rtlphy->rf_type = RF_1T1R;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Chip RF Type: %s\n",
		(rtlphy->rf_type == RF_2T2R) ? "RF_2T2R" : "RF_1T1R");

	वापस version;
पूर्ण

अटल पूर्णांक _rtl8723e_set_media_status(काष्ठा ieee80211_hw *hw,
				      क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_msr = rtl_पढ़ो_byte(rtlpriv, MSR) & 0xfc;
	क्रमागत led_ctl_mode ledaction = LED_CTL_NO_LINK;
	u8 mode = MSR_NOLINK;

	rtl_ग_लिखो_dword(rtlpriv, REG_BCN_CTRL, 0);
	rtl_dbg(rtlpriv, COMP_BEACON, DBG_LOUD,
		"clear 0x550 when set HW_VAR_MEDIA_STATUS\n");

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
	शेष:
		pr_err("Network type %d not support!\n", type);
		वापस 1;
	पूर्ण

	/* MSR_INFRA == Link in infraकाष्ठाure network;
	 * MSR_ADHOC == Link in ad hoc network;
	 * Thereक्रमe, check link state is necessary.
	 *
	 * MSR_AP == AP mode; link state is not cared here.
	 */
	अगर (mode != MSR_AP &&
	    rtlpriv->mac80211.link_state < MAC80211_LINKED) अणु
		mode = MSR_NOLINK;
		ledaction = LED_CTL_NO_LINK;
	पूर्ण
	अगर (mode == MSR_NOLINK || mode == MSR_INFRA) अणु
		_rtl8723e_stop_tx_beacon(hw);
		_rtl8723e_enable_bcn_sub_func(hw);
	पूर्ण अन्यथा अगर (mode == MSR_ADHOC || mode == MSR_AP) अणु
		_rtl8723e_resume_tx_beacon(hw);
		_rtl8723e_disable_bcn_sub_func(hw);
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

व्योम rtl8723e_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 reg_rcr = rtlpci->receive_config;

	अगर (rtlpriv->psc.rfpwr_state != ERFON)
		वापस;

	अगर (check_bssid) अणु
		reg_rcr |= (RCR_CBSSID_DATA | RCR_CBSSID_BCN);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR,
					      (u8 *)(&reg_rcr));
		_rtl8723e_set_bcn_ctrl_reg(hw, 0, BIT(4));
	पूर्ण अन्यथा अगर (!check_bssid) अणु
		reg_rcr &= (~(RCR_CBSSID_DATA | RCR_CBSSID_BCN));
		_rtl8723e_set_bcn_ctrl_reg(hw, BIT(4), 0);
		rtlpriv->cfg->ops->set_hw_reg(hw,
			HW_VAR_RCR, (u8 *)(&reg_rcr));
	पूर्ण
पूर्ण

पूर्णांक rtl8723e_set_network_type(काष्ठा ieee80211_hw *hw,
			      क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (_rtl8723e_set_media_status(hw, type))
		वापस -EOPNOTSUPP;

	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		अगर (type != NL80211_IFTYPE_AP)
			rtl8723e_set_check_bssid(hw, true);
	पूर्ण अन्यथा अणु
		rtl8723e_set_check_bssid(hw, false);
	पूर्ण

	वापस 0;
पूर्ण

/* करोn't set REG_EDCA_BE_PARAM here
 * because mac80211 will send pkt when scan
 */
व्योम rtl8723e_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl8723_dm_init_edca_turbo(hw);
	चयन (aci) अणु
	हाल AC1_BK:
		rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_BK_PARAM, 0xa44f);
		अवरोध;
	हाल AC0_BE:
		अवरोध;
	हाल AC2_VI:
		rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_VI_PARAM, 0x5e4322);
		अवरोध;
	हाल AC3_VO:
		rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_VO_PARAM, 0x2f3222);
		अवरोध;
	शेष:
		WARN_ONCE(true, "rtl8723ae: invalid aci: %d !\n", aci);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl8723e_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, 0x3a8, rtlpci->irq_mask[0] & 0xFFFFFFFF);
	rtl_ग_लिखो_dword(rtlpriv, 0x3ac, rtlpci->irq_mask[1] & 0xFFFFFFFF);
	rtlpci->irq_enabled = true;
पूर्ण

व्योम rtl8723e_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	rtl_ग_लिखो_dword(rtlpriv, 0x3a8, IMR8190_DISABLED);
	rtl_ग_लिखो_dword(rtlpriv, 0x3ac, IMR8190_DISABLED);
	rtlpci->irq_enabled = false;
	/*synchronize_irq(rtlpci->pdev->irq);*/
पूर्ण

अटल व्योम _rtl8723e_घातeroff_adapter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 u1b_पंचांगp;

	/* Combo (PCIe + USB) Card and PCIe-MF Card */
	/* 1. Run LPS WL RFOFF flow */
	rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
				 PWR_INTF_PCI_MSK, RTL8723_NIC_LPS_ENTER_FLOW);

	/* 2. 0x1F[7:0] = 0 */
	/* turn off RF */
	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, 0x00);
	अगर ((rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL) & BIT(7)) &&
	    rtlhal->fw_पढ़ोy) अणु
		rtl8723ae_firmware_selfreset(hw);
	पूर्ण

	/* Reset MCU. Suggested by Filen. */
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN+1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN+1, (u1b_पंचांगp & (~BIT(2))));

	/* g.	MCUFWDL 0x80[1:0]=0	 */
	/* reset MCU पढ़ोy status */
	rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0x00);

	/* HW card disable configuration. */
	rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
		PWR_INTF_PCI_MSK, RTL8723_NIC_DISABLE_FLOW);

	/* Reset MCU IO Wrapper */
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_पंचांगp & (~BIT(0))));
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, u1b_पंचांगp | BIT(0));

	/* 7. RSV_CTRL 0x1C[7:0] = 0x0E */
	/* lock ISO/CLK/Power control रेजिस्टर */
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0e);
पूर्ण

व्योम rtl8723e_card_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	क्रमागत nl80211_अगरtype opmode;

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;
	_rtl8723e_set_media_status(hw, opmode);
	अगर (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);
	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
	_rtl8723e_घातeroff_adapter(hw);

	/* after घातer off we should करो iqk again */
	rtlpriv->phy.iqk_initialized = false;
पूर्ण

व्योम rtl8723e_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				   काष्ठा rtl_पूर्णांक *पूर्णांकvec)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	पूर्णांकvec->पूर्णांकa = rtl_पढ़ो_dword(rtlpriv, 0x3a0) & rtlpci->irq_mask[0];
	rtl_ग_लिखो_dword(rtlpriv, 0x3a0, पूर्णांकvec->पूर्णांकa);
पूर्ण

व्योम rtl8723e_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw)
अणु

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval, atim_winकरोw;

	bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;
	atim_winकरोw = 2;	/*FIX MERGE */
	rtl8723e_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_ATIMWND, atim_winकरोw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl_ग_लिखो_word(rtlpriv, REG_BCNTCFG, 0x660f);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_CCK, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, 0x606, 0x30);
	rtl8723e_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl8723e_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;

	rtl_dbg(rtlpriv, COMP_BEACON, DBG_DMESG,
		"beacon_interval:%d\n", bcn_पूर्णांकerval);
	rtl8723e_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl8723e_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl8723e_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
				    u32 add_msr, u32 rm_msr)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_dbg(rtlpriv, COMP_INTR, DBG_LOUD,
		"add_msr:%x, rm_msr:%x\n", add_msr, rm_msr);

	अगर (add_msr)
		rtlpci->irq_mask[0] |= add_msr;
	अगर (rm_msr)
		rtlpci->irq_mask[0] &= (~rm_msr);
	rtl8723e_disable_पूर्णांकerrupt(hw);
	rtl8723e_enable_पूर्णांकerrupt(hw);
पूर्ण

अटल u8 _rtl8723e_get_chnl_group(u8 chnl)
अणु
	u8 group;

	अगर (chnl < 3)
		group = 0;
	अन्यथा अगर (chnl < 9)
		group = 1;
	अन्यथा
		group = 2;
	वापस group;
पूर्ण

अटल व्योम _rtl8723e_पढ़ो_txघातer_info_from_hwpg(काष्ठा ieee80211_hw *hw,
						  bool स्वतःload_fail,
						  u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 rf_path, index, tempval;
	u16 i;

	क्रम (rf_path = 0; rf_path < 1; rf_path++) अणु
		क्रम (i = 0; i < 3; i++) अणु
			अगर (!स्वतःload_fail) अणु
				rtlefuse->eeprom_chnlarea_txpwr_cck[rf_path][i] =
				    hwinfo[EEPROM_TXPOWERCCK + rf_path * 3 + i];
				rtlefuse->eeprom_chnlarea_txpwr_ht40_1s[rf_path][i] =
				    hwinfo[EEPROM_TXPOWERHT40_1S + rf_path * 3 + i];
			पूर्ण अन्यथा अणु
				rtlefuse->eeprom_chnlarea_txpwr_cck[rf_path][i] =
				    EEPROM_DEFAULT_TXPOWERLEVEL;
				rtlefuse->eeprom_chnlarea_txpwr_ht40_1s[rf_path][i] =
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
				"RF(%d) EEPROM CCK Area(%d) = 0x%x\n", rf_path,
				 i, rtlefuse->eeprom_chnlarea_txpwr_cck
					[rf_path][i]);
	क्रम (rf_path = 0; rf_path < 2; rf_path++)
		क्रम (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM HT40 1S Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->eeprom_chnlarea_txpwr_ht40_1s
					[rf_path][i]);
	क्रम (rf_path = 0; rf_path < 2; rf_path++)
		क्रम (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM HT40 2S Diff Area(%d) = 0x%x\n",
				 rf_path, i,
				 rtlefuse->eprom_chnl_txpwr_ht40_2sdf
					[rf_path][i]);

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 14; i++) अणु
			index = _rtl8723e_get_chnl_group((u8)i);

			rtlefuse->txpwrlevel_cck[rf_path][i] =
				rtlefuse->eeprom_chnlarea_txpwr_cck
					[rf_path][index];
			rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
				rtlefuse->eeprom_chnlarea_txpwr_ht40_1s
					[rf_path][index];

			अगर ((rtlefuse->eeprom_chnlarea_txpwr_ht40_1s
					[rf_path][index] -
			     rtlefuse->eprom_chnl_txpwr_ht40_2sdf
					[rf_path][index]) > 0) अणु
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i] =
				  rtlefuse->eeprom_chnlarea_txpwr_ht40_1s
				  [rf_path][index] -
				  rtlefuse->eprom_chnl_txpwr_ht40_2sdf
				  [rf_path][index];
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
			index = _rtl8723e_get_chnl_group((u8)i);

			अगर (rf_path == RF90_PATH_A) अणु
				rtlefuse->pwrgroup_ht20[rf_path][i] =
				  (rtlefuse->eeprom_pwrlimit_ht20[index] & 0xf);
				rtlefuse->pwrgroup_ht40[rf_path][i] =
				  (rtlefuse->eeprom_pwrlimit_ht40[index] & 0xf);
			पूर्ण अन्यथा अगर (rf_path == RF90_PATH_B) अणु
				rtlefuse->pwrgroup_ht20[rf_path][i] =
				  ((rtlefuse->eeprom_pwrlimit_ht20[index] &
				   0xf0) >> 4);
				rtlefuse->pwrgroup_ht40[rf_path][i] =
				  ((rtlefuse->eeprom_pwrlimit_ht40[index] &
				   0xf0) >> 4);
			पूर्ण

			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF-%d pwrgroup_ht20[%d] = 0x%x\n", rf_path, i,
				rtlefuse->pwrgroup_ht20[rf_path][i]);
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF-%d pwrgroup_ht40[%d] = 0x%x\n", rf_path, i,
				rtlefuse->pwrgroup_ht40[rf_path][i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 14; i++) अणु
		index = _rtl8723e_get_chnl_group((u8)i);

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

		index = _rtl8723e_get_chnl_group((u8)i);

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
			"RF-A Ht20 to HT40 Diff[%d] = 0x%x\n", i,
			 rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i]);
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-A Legacy to Ht40 Diff[%d] = 0x%x\n", i,
			 rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][i]);
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-B Ht20 to HT40 Diff[%d] = 0x%x\n", i,
			 rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i]);
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-B Legacy to HT40 Diff[%d] = 0x%x\n", i,
			 rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_B][i]);

	अगर (!स्वतःload_fail)
		rtlefuse->eeprom_regulatory = (hwinfo[RF_OPTION1] & 0x7);
	अन्यथा
		rtlefuse->eeprom_regulatory = 0;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"eeprom_regulatory = 0x%x\n", rtlefuse->eeprom_regulatory);

	अगर (!स्वतःload_fail)
		rtlefuse->eeprom_tssi[RF90_PATH_A] = hwinfo[EEPROM_TSSI_A];
	अन्यथा
		rtlefuse->eeprom_tssi[RF90_PATH_A] = EEPROM_DEFAULT_TSSI;

	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"TSSI_A = 0x%x, TSSI_B = 0x%x\n",
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

अटल व्योम _rtl8723e_पढ़ो_adapter_info(काष्ठा ieee80211_hw *hw,
					bool b_pseuकरो_test)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक params[] = अणुRTL8190_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13पूर्ण;
	u8 *hwinfo;

	अगर (b_pseuकरो_test) अणु
		/* need add */
		वापस;
	पूर्ण
	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	अगर (!hwinfo)
		वापस;

	अगर (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		जाओ निकास;

	_rtl8723e_पढ़ो_txघातer_info_from_hwpg(hw, rtlefuse->स्वतःload_failflag,
					      hwinfo);

	rtl8723e_पढ़ो_bt_coexist_info_from_hwpg(hw,
			rtlefuse->स्वतःload_failflag, hwinfo);

	अगर (rtlhal->oem_id != RT_CID_DEFAULT)
		जाओ निकास;

	चयन (rtlefuse->eeprom_oemid) अणु
	हाल EEPROM_CID_DEFAULT:
		चयन (rtlefuse->eeprom_did) अणु
		हाल 0x8176:
			चयन (rtlefuse->eeprom_svid) अणु
			हाल 0x10EC:
				चयन (rtlefuse->eeprom_smid) अणु
				हाल 0x6151 ... 0x6152:
				हाल 0x6154 ... 0x6155:
				हाल 0x6177 ... 0x6180:
				हाल 0x7151 ... 0x7152:
				हाल 0x7154 ... 0x7155:
				हाल 0x7177 ... 0x7180:
				हाल 0x8151 ... 0x8152:
				हाल 0x8154 ... 0x8155:
				हाल 0x8181 ... 0x8182:
				हाल 0x8184 ... 0x8185:
				हाल 0x9151 ... 0x9152:
				हाल 0x9154 ... 0x9155:
				हाल 0x9181 ... 0x9182:
				हाल 0x9184 ... 0x9185:
					rtlhal->oem_id = RT_CID_TOSHIBA;
					अवरोध;
				हाल 0x6191 ... 0x6193:
				हाल 0x7191 ... 0x7193:
				हाल 0x8191 ... 0x8193:
				हाल 0x9191 ... 0x9193:
					rtlhal->oem_id = RT_CID_819X_SAMSUNG;
					अवरोध;
				हाल 0x8197:
				हाल 0x9196:
					rtlhal->oem_id = RT_CID_819X_CLEVO;
					अवरोध;
				हाल 0x8203:
					rtlhal->oem_id = RT_CID_819X_PRONETS;
					अवरोध;
				हाल 0x8195:
				हाल 0x9195:
				हाल 0x7194:
				हाल 0x8200 ... 0x8202:
				हाल 0x9200:
					rtlhal->oem_id = RT_CID_819X_LENOVO;
					अवरोध;
				पूर्ण
				अवरोध;
			हाल 0x1025:
				rtlhal->oem_id = RT_CID_819X_ACER;
				अवरोध;
			हाल 0x1028:
				चयन (rtlefuse->eeprom_smid) अणु
				हाल 0x8194:
				हाल 0x8198:
				हाल 0x9197 ... 0x9198:
					rtlhal->oem_id = RT_CID_819X_DELL;
					अवरोध;
				पूर्ण
				अवरोध;
			हाल 0x103C:
				चयन (rtlefuse->eeprom_smid) अणु
				हाल 0x1629:
					rtlhal->oem_id = RT_CID_819X_HP;
				पूर्ण
				अवरोध;
			हाल 0x1A32:
				चयन (rtlefuse->eeprom_smid) अणु
				हाल 0x2315:
					rtlhal->oem_id = RT_CID_819X_QMI;
					अवरोध;
				पूर्ण
				अवरोध;
			हाल 0x1043:
				चयन (rtlefuse->eeprom_smid) अणु
				हाल 0x84B5:
					rtlhal->oem_id =
						RT_CID_819X_EDIMAX_ASUS;
				पूर्ण
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x8178:
			चयन (rtlefuse->eeprom_svid) अणु
			हाल 0x10ec:
				चयन (rtlefuse->eeprom_smid) अणु
				हाल 0x6181 ... 0x6182:
				हाल 0x6184 ... 0x6185:
				हाल 0x7181 ... 0x7182:
				हाल 0x7184 ... 0x7185:
				हाल 0x8181 ... 0x8182:
				हाल 0x8184 ... 0x8185:
				हाल 0x9181 ... 0x9182:
				हाल 0x9184 ... 0x9185:
					rtlhal->oem_id = RT_CID_TOSHIBA;
					अवरोध;
				हाल 0x8186:
					rtlhal->oem_id =
						RT_CID_819X_PRONETS;
					अवरोध;
				पूर्ण
				अवरोध;
			हाल 0x1025:
				rtlhal->oem_id = RT_CID_819X_ACER;
				अवरोध;
			हाल 0x1043:
				चयन (rtlefuse->eeprom_smid) अणु
				हाल 0x8486:
					rtlhal->oem_id =
					     RT_CID_819X_EDIMAX_ASUS;
				पूर्ण
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	हाल EEPROM_CID_TOSHIBA:
		rtlhal->oem_id = RT_CID_TOSHIBA;
		अवरोध;
	हाल EEPROM_CID_CCX:
		rtlhal->oem_id = RT_CID_CCX;
		अवरोध;
	हाल EEPROM_CID_QMI:
		rtlhal->oem_id = RT_CID_819X_QMI;
		अवरोध;
	हाल EEPROM_CID_WHQL:
		अवरोध;
	शेष:
		rtlhal->oem_id = RT_CID_DEFAULT;
		अवरोध;
	पूर्ण
निकास:
	kमुक्त(hwinfo);
पूर्ण

अटल व्योम _rtl8723e_hal_customized_behavior(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	rtlpriv->ledctl.led_खोलोdrain = true;
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

व्योम rtl8723e_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_u1b;
	u32 value32;

	value32 = rtl_पढ़ो_dword(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST]);
	value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_WIFI_SEL_0);
	rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST], value32);

	rtlhal->version = _rtl8723e_पढ़ो_chip_version(hw);

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
		_rtl8723e_पढ़ो_adapter_info(hw, false);
	पूर्ण अन्यथा अणु
		rtlefuse->स्वतःload_failflag = true;
		_rtl8723e_पढ़ो_adapter_info(hw, false);
		pr_err("Autoload ERR!!\n");
	पूर्ण
	_rtl8723e_hal_customized_behavior(hw);
पूर्ण

अटल व्योम rtl8723e_update_hal_rate_table(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 ratr_value;
	u8 ratr_index = 0;
	u8 b_nmode = mac->ht_enable;
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
		b_nmode = 1;
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

	अगर (b_nmode &&
	    ((curtxbw_40mhz && curलघुgi_40mhz) ||
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

	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"%x\n", rtl_पढ़ो_dword(rtlpriv, REG_ARFR0));
पूर्ण

अटल व्योम rtl8723e_update_hal_rate_mask(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_sta *sta,
					  u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u32 ratr_biपंचांगap;
	u8 ratr_index;
	u8 curtxbw_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40)
				? 1 : 0;
	u8 curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
				1 : 0;
	u8 curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	क्रमागत wireless_mode wirelessmode = 0;
	bool लघुgi = false;
	u8 rate_mask[5];
	u8 macid = 0;
	/*u8 mimo_ps = IEEE80211_SMPS_OFF;*/

	sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
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
		ratr_index = RATR_INX_WIRELESS_G;
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
		"Rate_index:%x, ratr_val:%x, %x:%x:%x:%x:%x\n",
		ratr_index, ratr_biपंचांगap,
		rate_mask[0], rate_mask[1],
		rate_mask[2], rate_mask[3],
		rate_mask[4]);
	rtl8723e_fill_h2c_cmd(hw, H2C_RA_MASK, 5, rate_mask);
पूर्ण

व्योम rtl8723e_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_sta *sta, u8 rssi_level,
				  bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->dm.useramask)
		rtl8723e_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
	अन्यथा
		rtl8723e_update_hal_rate_table(hw, sta);
पूर्ण

व्योम rtl8723e_update_channel_access_setting(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 sअगरs_समयr;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME, &mac->slot_समय);
	अगर (!mac->ht_enable)
		sअगरs_समयr = 0x0a0a;
	अन्यथा
		sअगरs_समयr = 0x1010;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SIFS, (u8 *)&sअगरs_समयr);
पूर्ण

bool rtl8723e_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	क्रमागत rf_pwrstate e_rfघातerstate_toset;
	u8 u1पंचांगp;
	bool b_actuallyset = false;

	अगर (rtlpriv->rtlhal.being_init_adapter)
		वापस false;

	अगर (ppsc->swrf_processing)
		वापस false;

	spin_lock(&rtlpriv->locks.rf_ps_lock);
	अगर (ppsc->rfchange_inprogress) अणु
		spin_unlock(&rtlpriv->locks.rf_ps_lock);
		वापस false;
	पूर्ण अन्यथा अणु
		ppsc->rfchange_inprogress = true;
		spin_unlock(&rtlpriv->locks.rf_ps_lock);
	पूर्ण

	rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_IO_SEL_2,
		       rtl_पढ़ो_byte(rtlpriv, REG_GPIO_IO_SEL_2)&~(BIT(1)));

	u1पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_PIN_CTRL_2);

	अगर (rtlphy->polarity_ctl)
		e_rfघातerstate_toset = (u1पंचांगp & BIT(1)) ? ERFOFF : ERFON;
	अन्यथा
		e_rfघातerstate_toset = (u1पंचांगp & BIT(1)) ? ERFON : ERFOFF;

	अगर (ppsc->hwradiooff && (e_rfघातerstate_toset == ERFON)) अणु
		rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
			"GPIOChangeRF  - HW Radio ON, RF ON\n");

		e_rfघातerstate_toset = ERFON;
		ppsc->hwradiooff = false;
		b_actuallyset = true;
	पूर्ण अन्यथा अगर (!ppsc->hwradiooff && (e_rfघातerstate_toset == ERFOFF)) अणु
		rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
			"GPIOChangeRF  - HW Radio OFF, RF OFF\n");

		e_rfघातerstate_toset = ERFOFF;
		ppsc->hwradiooff = true;
		b_actuallyset = true;
	पूर्ण

	अगर (b_actuallyset) अणु
		spin_lock(&rtlpriv->locks.rf_ps_lock);
		ppsc->rfchange_inprogress = false;
		spin_unlock(&rtlpriv->locks.rf_ps_lock);
	पूर्ण अन्यथा अणु
		अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC)
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);

		spin_lock(&rtlpriv->locks.rf_ps_lock);
		ppsc->rfchange_inprogress = false;
		spin_unlock(&rtlpriv->locks.rf_ps_lock);
	पूर्ण

	*valid = 1;
	वापस !ppsc->hwradiooff;

पूर्ण

व्योम rtl8723e_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
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
			rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
				"switch case %#x not processed\n", enc_algo);
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
					entry_id =
					  rtl_cam_get_मुक्त_entry(hw, p_macaddr);
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
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"add one entry\n");
			अगर (is_pairwise) अणु
				rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
					"set Pairwise key\n");

				rtl_cam_add_one_entry(hw, macaddr, key_index,
						      entry_id, enc_algo,
						      CAM_CONFIG_NO_USEDK,
						      rtlpriv->sec.key_buf[key_index]);
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

अटल व्योम rtl8723e_bt_var_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->btcoexist.bt_coexistence =
		rtlpriv->btcoexist.eeprom_bt_coexist;
	rtlpriv->btcoexist.bt_ant_num =
		rtlpriv->btcoexist.eeprom_bt_ant_num;
	rtlpriv->btcoexist.bt_coexist_type =
		rtlpriv->btcoexist.eeprom_bt_type;

	rtlpriv->btcoexist.bt_ant_isolation =
		rtlpriv->btcoexist.eeprom_bt_ant_isol;

	rtlpriv->btcoexist.bt_radio_shared_type =
		rtlpriv->btcoexist.eeprom_bt_radio_shared;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"BT Coexistence = 0x%x\n",
		rtlpriv->btcoexist.bt_coexistence);

	अगर (rtlpriv->btcoexist.bt_coexistence) अणु
		rtlpriv->btcoexist.bt_busy_traffic = false;
		rtlpriv->btcoexist.bt_traffic_mode_set = false;
		rtlpriv->btcoexist.bt_non_traffic_mode_set = false;

		rtlpriv->btcoexist.cstate = 0;
		rtlpriv->btcoexist.previous_state = 0;

		अगर (rtlpriv->btcoexist.bt_ant_num == ANT_X2) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"BlueTooth BT_Ant_Num = Antx2\n");
		पूर्ण अन्यथा अगर (rtlpriv->btcoexist.bt_ant_num == ANT_X1) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"BlueTooth BT_Ant_Num = Antx1\n");
		पूर्ण
		चयन (rtlpriv->btcoexist.bt_coexist_type) अणु
		हाल BT_2WIRE:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"BlueTooth BT_CoexistType = BT_2Wire\n");
			अवरोध;
		हाल BT_ISSC_3WIRE:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"BlueTooth BT_CoexistType = BT_ISSC_3Wire\n");
			अवरोध;
		हाल BT_ACCEL:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"BlueTooth BT_CoexistType = BT_ACCEL\n");
			अवरोध;
		हाल BT_CSR_BC4:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"BlueTooth BT_CoexistType = BT_CSR_BC4\n");
			अवरोध;
		हाल BT_CSR_BC8:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"BlueTooth BT_CoexistType = BT_CSR_BC8\n");
			अवरोध;
		हाल BT_RTL8756:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"BlueTooth BT_CoexistType = BT_RTL8756\n");
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"BlueTooth BT_CoexistType = Unknown\n");
			अवरोध;
		पूर्ण
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"BlueTooth BT_Ant_isolation = %d\n",
			 rtlpriv->btcoexist.bt_ant_isolation);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"BT_RadioSharedType = 0x%x\n",
			 rtlpriv->btcoexist.bt_radio_shared_type);
		rtlpriv->btcoexist.bt_active_zero_cnt = 0;
		rtlpriv->btcoexist.cur_bt_disabled = false;
		rtlpriv->btcoexist.pre_bt_disabled = false;
	पूर्ण
पूर्ण

व्योम rtl8723e_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
					     bool स्वतः_load_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value;
	u32 पंचांगpu_32;

	अगर (!स्वतः_load_fail) अणु
		पंचांगpu_32 = rtl_पढ़ो_dword(rtlpriv, REG_MULTI_FUNC_CTRL);
		अगर (पंचांगpu_32 & BIT(18))
			rtlpriv->btcoexist.eeprom_bt_coexist = 1;
		अन्यथा
			rtlpriv->btcoexist.eeprom_bt_coexist = 0;
		value = hwinfo[RF_OPTION4];
		rtlpriv->btcoexist.eeprom_bt_type = BT_RTL8723A;
		rtlpriv->btcoexist.eeprom_bt_ant_num = (value & 0x1);
		rtlpriv->btcoexist.eeprom_bt_ant_isol = ((value & 0x10) >> 4);
		rtlpriv->btcoexist.eeprom_bt_radio_shared =
		  ((value & 0x20) >> 5);
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.eeprom_bt_coexist = 0;
		rtlpriv->btcoexist.eeprom_bt_type = BT_RTL8723A;
		rtlpriv->btcoexist.eeprom_bt_ant_num = ANT_X2;
		rtlpriv->btcoexist.eeprom_bt_ant_isol = 0;
		rtlpriv->btcoexist.eeprom_bt_radio_shared = BT_RADIO_SHARED;
	पूर्ण

	rtl8723e_bt_var_init(hw);
पूर्ण

व्योम rtl8723e_bt_reg_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* 0:Low, 1:High, 2:From Efuse. */
	rtlpriv->btcoexist.reg_bt_iso = 2;
	/* 0:Idle, 1:None-SCO, 2:SCO, 3:From Counter. */
	rtlpriv->btcoexist.reg_bt_sco = 3;
	/* 0:Disable BT control A-MPDU, 1:Enable BT control A-MPDU. */
	rtlpriv->btcoexist.reg_bt_sco = 0;
पूर्ण

व्योम rtl8723e_bt_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_init_hw_config(rtlpriv);
पूर्ण

व्योम rtl8723e_suspend(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

व्योम rtl8723e_resume(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण
