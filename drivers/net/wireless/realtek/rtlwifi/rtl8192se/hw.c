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
#समावेश "hw.h"

व्योम rtl92se_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	चयन (variable) अणु
	हाल HW_VAR_RCR: अणु
			*((u32 *) (val)) = rtlpci->receive_config;
			अवरोध;
		पूर्ण
	हाल HW_VAR_RF_STATE: अणु
			*((क्रमागत rf_pwrstate *)(val)) = ppsc->rfpwr_state;
			अवरोध;
		पूर्ण
	हाल HW_VAR_FW_PSMODE_STATUS: अणु
			*((bool *) (val)) = ppsc->fw_current_inpsmode;
			अवरोध;
		पूर्ण
	हाल HW_VAR_CORRECT_TSF: अणु
			u64 tsf;
			u32 *ptsf_low = (u32 *)&tsf;
			u32 *ptsf_high = ((u32 *)&tsf) + 1;

			*ptsf_high = rtl_पढ़ो_dword(rtlpriv, (TSFR + 4));
			*ptsf_low = rtl_पढ़ो_dword(rtlpriv, TSFR);

			*((u64 *) (val)) = tsf;

			अवरोध;
		पूर्ण
	हाल HW_VAR_MRC: अणु
			*((bool *)(val)) = rtlpriv->dm.current_mrc_चयन;
			अवरोध;
		पूर्ण
	हाल HAL_DEF_WOWLAN:
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92se_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	चयन (variable) अणु
	हाल HW_VAR_ETHER_ADDR:अणु
			rtl_ग_लिखो_dword(rtlpriv, IDR0, ((u32 *)(val))[0]);
			rtl_ग_लिखो_word(rtlpriv, IDR4, ((u16 *)(val + 4))[0]);
			अवरोध;
		पूर्ण
	हाल HW_VAR_BASIC_RATE:अणु
			u16 rate_cfg = ((u16 *) val)[0];
			u8 rate_index = 0;

			अगर (rtlhal->version == VERSION_8192S_ACUT)
				rate_cfg = rate_cfg & 0x150;
			अन्यथा
				rate_cfg = rate_cfg & 0x15f;

			rate_cfg |= 0x01;

			rtl_ग_लिखो_byte(rtlpriv, RRSR, rate_cfg & 0xff);
			rtl_ग_लिखो_byte(rtlpriv, RRSR + 1,
				       (rate_cfg >> 8) & 0xff);

			जबतक (rate_cfg > 0x1) अणु
				rate_cfg = (rate_cfg >> 1);
				rate_index++;
			पूर्ण
			rtl_ग_लिखो_byte(rtlpriv, INIRTSMCS_SEL, rate_index);

			अवरोध;
		पूर्ण
	हाल HW_VAR_BSSID:अणु
			rtl_ग_लिखो_dword(rtlpriv, BSSIDR, ((u32 *)(val))[0]);
			rtl_ग_लिखो_word(rtlpriv, BSSIDR + 4,
				       ((u16 *)(val + 4))[0]);
			अवरोध;
		पूर्ण
	हाल HW_VAR_SIFS:अणु
			rtl_ग_लिखो_byte(rtlpriv, SIFS_OFDM, val[0]);
			rtl_ग_लिखो_byte(rtlpriv, SIFS_OFDM + 1, val[1]);
			अवरोध;
		पूर्ण
	हाल HW_VAR_SLOT_TIME:अणु
			u8 e_aci;

			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"HW_VAR_SLOT_TIME %x\n", val[0]);

			rtl_ग_लिखो_byte(rtlpriv, SLOT_TIME, val[0]);

			क्रम (e_aci = 0; e_aci < AC_MAX; e_aci++) अणु
				rtlpriv->cfg->ops->set_hw_reg(hw,
						HW_VAR_AC_PARAM,
						(&e_aci));
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_ACK_PREAMBLE:अणु
			u8 reg_पंचांगp;
			u8 लघु_preamble = (bool) (*val);
			reg_पंचांगp = (mac->cur_40_prime_sc) << 5;
			अगर (लघु_preamble)
				reg_पंचांगp |= 0x80;

			rtl_ग_लिखो_byte(rtlpriv, RRSR + 2, reg_पंचांगp);
			अवरोध;
		पूर्ण
	हाल HW_VAR_AMPDU_MIN_SPACE:अणु
			u8 min_spacing_to_set;
			u8 sec_min_space;

			min_spacing_to_set = *val;
			अगर (min_spacing_to_set <= 7) अणु
				अगर (rtlpriv->sec.pairwise_enc_algorithm ==
				    NO_ENCRYPTION)
					sec_min_space = 0;
				अन्यथा
					sec_min_space = 1;

				अगर (min_spacing_to_set < sec_min_space)
					min_spacing_to_set = sec_min_space;
				अगर (min_spacing_to_set > 5)
					min_spacing_to_set = 5;

				mac->min_space_cfg =
						((mac->min_space_cfg & 0xf8) |
						min_spacing_to_set);

				*val = min_spacing_to_set;

				rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
					"Set HW_VAR_AMPDU_MIN_SPACE: %#x\n",
					mac->min_space_cfg);

				rtl_ग_लिखो_byte(rtlpriv, AMPDU_MIN_SPACE,
					       mac->min_space_cfg);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_SHORTGI_DENSITY:अणु
			u8 density_to_set;

			density_to_set = *val;
			mac->min_space_cfg = rtlpriv->rtlhal.minspace_cfg;
			mac->min_space_cfg |= (density_to_set << 3);

			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"Set HW_VAR_SHORTGI_DENSITY: %#x\n",
				mac->min_space_cfg);

			rtl_ग_लिखो_byte(rtlpriv, AMPDU_MIN_SPACE,
				       mac->min_space_cfg);

			अवरोध;
		पूर्ण
	हाल HW_VAR_AMPDU_FACTOR:अणु
			u8 factor_toset;
			u8 regtoset;
			u8 factorlevel[18] = अणु
				2, 4, 4, 7, 7, 13, 13,
				13, 2, 7, 7, 13, 13,
				15, 15, 15, 15, 0पूर्ण;
			u8 index = 0;

			factor_toset = *val;
			अगर (factor_toset <= 3) अणु
				factor_toset = (1 << (factor_toset + 2));
				अगर (factor_toset > 0xf)
					factor_toset = 0xf;

				क्रम (index = 0; index < 17; index++) अणु
					अगर (factorlevel[index] > factor_toset)
						factorlevel[index] =
								 factor_toset;
				पूर्ण

				क्रम (index = 0; index < 8; index++) अणु
					regtoset = ((factorlevel[index * 2]) |
						    (factorlevel[index *
						    2 + 1] << 4));
					rtl_ग_लिखो_byte(rtlpriv,
						       AGGLEN_LMT_L + index,
						       regtoset);
				पूर्ण

				regtoset = ((factorlevel[16]) |
					    (factorlevel[17] << 4));
				rtl_ग_लिखो_byte(rtlpriv, AGGLEN_LMT_H, regtoset);

				rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
					"Set HW_VAR_AMPDU_FACTOR: %#x\n",
					factor_toset);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_AC_PARAM:अणु
			u8 e_aci = *val;
			rtl92s_dm_init_edca_turbo(hw);

			अगर (rtlpci->acm_method != EACMWAY2_SW)
				rtlpriv->cfg->ops->set_hw_reg(hw,
						 HW_VAR_ACM_CTRL,
						 &e_aci);
			अवरोध;
		पूर्ण
	हाल HW_VAR_ACM_CTRL:अणु
			u8 e_aci = *val;
			जोड़ aci_aअगरsn *p_aci_aअगरsn = (जोड़ aci_aअगरsn *)(&(
							mac->ac[0].aअगरs));
			u8 acm = p_aci_aअगरsn->f.acm;
			u8 acm_ctrl = rtl_पढ़ो_byte(rtlpriv, ACMHWCTRL);

			acm_ctrl = acm_ctrl | ((rtlpci->acm_method == 2) ?
				   0x0 : 0x1);

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
				"HW_VAR_ACM_CTRL Write 0x%X\n", acm_ctrl);
			rtl_ग_लिखो_byte(rtlpriv, ACMHWCTRL, acm_ctrl);
			अवरोध;
		पूर्ण
	हाल HW_VAR_RCR:अणु
			rtl_ग_लिखो_dword(rtlpriv, RCR, ((u32 *) (val))[0]);
			rtlpci->receive_config = ((u32 *) (val))[0];
			अवरोध;
		पूर्ण
	हाल HW_VAR_RETRY_LIMIT:अणु
			u8 retry_limit = val[0];

			rtl_ग_लिखो_word(rtlpriv, RETRY_LIMIT,
				       retry_limit << RETRY_LIMIT_SHORT_SHIFT |
				       retry_limit << RETRY_LIMIT_LONG_SHIFT);
			अवरोध;
		पूर्ण
	हाल HW_VAR_DUAL_TSF_RST: अणु
			अवरोध;
		पूर्ण
	हाल HW_VAR_EFUSE_BYTES: अणु
			rtlefuse->efuse_usedbytes = *((u16 *) val);
			अवरोध;
		पूर्ण
	हाल HW_VAR_EFUSE_USAGE: अणु
			rtlefuse->efuse_usedpercentage = *val;
			अवरोध;
		पूर्ण
	हाल HW_VAR_IO_CMD: अणु
			अवरोध;
		पूर्ण
	हाल HW_VAR_WPA_CONFIG: अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_SECR, *val);
			अवरोध;
		पूर्ण
	हाल HW_VAR_SET_RPWM:अणु
			अवरोध;
		पूर्ण
	हाल HW_VAR_H2C_FW_PWRMODE:अणु
			अवरोध;
		पूर्ण
	हाल HW_VAR_FW_PSMODE_STATUS: अणु
			ppsc->fw_current_inpsmode = *((bool *) val);
			अवरोध;
		पूर्ण
	हाल HW_VAR_H2C_FW_JOINBSSRPT:अणु
			अवरोध;
		पूर्ण
	हाल HW_VAR_AID:अणु
			अवरोध;
		पूर्ण
	हाल HW_VAR_CORRECT_TSF:अणु
			अवरोध;
		पूर्ण
	हाल HW_VAR_MRC: अणु
			bool bmrc_toset = *((bool *)val);
			u8 u1bdata = 0;

			अगर (bmrc_toset) अणु
				rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE,
					      MASKBYTE0, 0x33);
				u1bdata = (u8)rtl_get_bbreg(hw,
						ROFDM1_TRXPATHENABLE,
						MASKBYTE0);
				rtl_set_bbreg(hw, ROFDM1_TRXPATHENABLE,
					      MASKBYTE0,
					      ((u1bdata & 0xf0) | 0x03));
				u1bdata = (u8)rtl_get_bbreg(hw,
						ROFDM0_TRXPATHENABLE,
						MASKBYTE1);
				rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE,
					      MASKBYTE1,
					      (u1bdata | 0x04));

				/* Update current settings. */
				rtlpriv->dm.current_mrc_चयन = bmrc_toset;
			पूर्ण अन्यथा अणु
				rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE,
					      MASKBYTE0, 0x13);
				u1bdata = (u8)rtl_get_bbreg(hw,
						 ROFDM1_TRXPATHENABLE,
						 MASKBYTE0);
				rtl_set_bbreg(hw, ROFDM1_TRXPATHENABLE,
					      MASKBYTE0,
					      ((u1bdata & 0xf0) | 0x01));
				u1bdata = (u8)rtl_get_bbreg(hw,
						ROFDM0_TRXPATHENABLE,
						MASKBYTE1);
				rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE,
					      MASKBYTE1, (u1bdata & 0xfb));

				/* Update current settings. */
				rtlpriv->dm.current_mrc_चयन = bmrc_toset;
			पूर्ण

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

			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
						      &rpwm_val);
		पूर्ण अन्यथा अणु
			rpwm_val = 0x0C;	/* RF on */
			fw_pwrmode = FW_PS_ACTIVE_MODE;
			fw_current_inps = false;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
						      &rpwm_val);
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
						      &fw_pwrmode);

			rtlpriv->cfg->ops->set_hw_reg(hw,
					HW_VAR_FW_PSMODE_STATUS,
					(u8 *)(&fw_current_inps));
		पूर्ण
		अवरोध; पूर्ण
	शेष:
		pr_err("switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण

पूर्ण

व्योम rtl92se_enable_hw_security_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 sec_reg_value = 0x0;

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

	rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD, "The SECR-value %x\n",
		sec_reg_value);

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_WPA_CONFIG, &sec_reg_value);

पूर्ण

अटल u8 _rtl92se_halset_sysclk(काष्ठा ieee80211_hw *hw, u8 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 रुकोcount = 100;
	bool bresult = false;
	u8 पंचांगpvalue;

	rtl_ग_लिखो_byte(rtlpriv, SYS_CLKR + 1, data);

	/* Wait the MAC synchronized. */
	udelay(400);

	/* Check अगर it is set पढ़ोy. */
	पंचांगpvalue = rtl_पढ़ो_byte(rtlpriv, SYS_CLKR + 1);
	bresult = ((पंचांगpvalue & BIT(7)) == (data & BIT(7)));

	अगर (!(data & (BIT(6) | BIT(7)))) अणु
		रुकोcount = 100;
		पंचांगpvalue = 0;

		जबतक (1) अणु
			रुकोcount--;

			पंचांगpvalue = rtl_पढ़ो_byte(rtlpriv, SYS_CLKR + 1);
			अगर ((पंचांगpvalue & BIT(6)))
				अवरोध;

			pr_err("wait for BIT(6) return value %x\n", पंचांगpvalue);
			अगर (रुकोcount == 0)
				अवरोध;

			udelay(10);
		पूर्ण

		अगर (रुकोcount == 0)
			bresult = false;
		अन्यथा
			bresult = true;
	पूर्ण

	वापस bresult;
पूर्ण

व्योम rtl8192se_gpiobit3_cfg_inpuपंचांगode(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1पंचांगp;

	/* The following config GPIO function */
	rtl_ग_लिखो_byte(rtlpriv, MAC_PINMUX_CFG, (GPIOMUX_EN | GPIOSEL_GPIO));
	u1पंचांगp = rtl_पढ़ो_byte(rtlpriv, GPIO_IO_SEL);

	/* config GPIO3 to input */
	u1पंचांगp &= HAL_8192S_HW_GPIO_OFF_MASK;
	rtl_ग_लिखो_byte(rtlpriv, GPIO_IO_SEL, u1पंचांगp);

पूर्ण

अटल u8 _rtl92se_rf_onoff_detect(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1पंचांगp;
	u8 retval = ERFON;

	/* The following config GPIO function */
	rtl_ग_लिखो_byte(rtlpriv, MAC_PINMUX_CFG, (GPIOMUX_EN | GPIOSEL_GPIO));
	u1पंचांगp = rtl_पढ़ो_byte(rtlpriv, GPIO_IO_SEL);

	/* config GPIO3 to input */
	u1पंचांगp &= HAL_8192S_HW_GPIO_OFF_MASK;
	rtl_ग_लिखो_byte(rtlpriv, GPIO_IO_SEL, u1पंचांगp);

	/* On some of the platक्रमm, driver cannot पढ़ो correct
	 * value without delay between Write_GPIO_SEL and Read_GPIO_IN */
	mdelay(10);

	/* check GPIO3 */
	u1पंचांगp = rtl_पढ़ो_byte(rtlpriv, GPIO_IN_SE);
	retval = (u1पंचांगp & HAL_8192S_HW_GPIO_OFF_BIT) ? ERFON : ERFOFF;

	वापस retval;
पूर्ण

अटल व्योम _rtl92se_macconfig_beक्रमe_fwकरोwnload(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	u8 i;
	u8 पंचांगpu1b;
	u16 पंचांगpu2b;
	u8 pollingcnt = 20;

	अगर (rtlpci->first_init) अणु
		/* Reset PCIE Digital */
		पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
		पंचांगpu1b &= 0xFE;
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगpu1b);
		udelay(1);
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगpu1b | BIT(0));
	पूर्ण

	/* Switch to SW IO control */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, (SYS_CLKR + 1));
	अगर (पंचांगpu1b & BIT(7)) अणु
		पंचांगpu1b &= ~(BIT(6) | BIT(7));

		/* Set failed, वापस to prevent hang. */
		अगर (!_rtl92se_halset_sysclk(hw, पंचांगpu1b))
			वापस;
	पूर्ण

	rtl_ग_लिखो_byte(rtlpriv, AFE_PLL_CTRL, 0x0);
	udelay(50);
	rtl_ग_लिखो_byte(rtlpriv, LDOA15_CTRL, 0x34);
	udelay(50);

	/* Clear FW RPWM क्रम FW control LPS.*/
	rtl_ग_लिखो_byte(rtlpriv, RPWM, 0x0);

	/* Reset MAC-IO and CPU and Core Digital BIT(10)/11/15 */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	पंचांगpu1b &= 0x73;
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगpu1b);
	/* रुको क्रम BIT 10/11/15 to pull high स्वतःmatically!! */
	mdelay(1);

	rtl_ग_लिखो_byte(rtlpriv, CMDR, 0);
	rtl_ग_लिखो_byte(rtlpriv, TCR, 0);

	/* Data sheet not define 0x562!!! Copy from WMAC!!!!! */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, 0x562);
	पंचांगpu1b |= 0x08;
	rtl_ग_लिखो_byte(rtlpriv, 0x562, पंचांगpu1b);
	पंचांगpu1b &= ~(BIT(3));
	rtl_ग_लिखो_byte(rtlpriv, 0x562, पंचांगpu1b);

	/* Enable AFE घड़ी source */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_XTAL_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, AFE_XTAL_CTRL, (पंचांगpu1b | 0x01));
	/* Delay 1.5ms */
	mdelay(2);
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_XTAL_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, AFE_XTAL_CTRL + 1, (पंचांगpu1b & 0xfb));

	/* Enable AFE Macro Block's Bandgap */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_MISC);
	rtl_ग_लिखो_byte(rtlpriv, AFE_MISC, (पंचांगpu1b | BIT(0)));
	mdelay(1);

	/* Enable AFE Mbias */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_MISC);
	rtl_ग_लिखो_byte(rtlpriv, AFE_MISC, (पंचांगpu1b | 0x02));
	mdelay(1);

	/* Enable LDOA15 block	*/
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, LDOA15_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, LDOA15_CTRL, (पंचांगpu1b | BIT(0)));

	/* Set Digital Vdd to Retention isolation Path. */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, REG_SYS_ISO_CTRL);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_ISO_CTRL, (पंचांगpu2b | BIT(11)));

	/* For warm reboot NIC disappera bug. */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (पंचांगpu2b | BIT(13)));

	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL + 1, 0x68);

	/* Enable AFE PLL Macro Block */
	/* We need to delay 100u beक्रमe enabling PLL. */
	udelay(200);
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_PLL_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, AFE_PLL_CTRL, (पंचांगpu1b | BIT(0) | BIT(4)));

	/* क्रम भागider reset  */
	udelay(100);
	rtl_ग_लिखो_byte(rtlpriv, AFE_PLL_CTRL, (पंचांगpu1b | BIT(0) |
		       BIT(4) | BIT(6)));
	udelay(10);
	rtl_ग_लिखो_byte(rtlpriv, AFE_PLL_CTRL, (पंचांगpu1b | BIT(0) | BIT(4)));
	udelay(10);

	/* Enable MAC 80MHZ घड़ी  */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_PLL_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, AFE_PLL_CTRL + 1, (पंचांगpu1b | BIT(0)));
	mdelay(1);

	/* Release isolation AFE PLL & MD */
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL, 0xA6);

	/* Enable MAC घड़ी */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, SYS_CLKR);
	rtl_ग_लिखो_word(rtlpriv, SYS_CLKR, (पंचांगpu2b | BIT(12) | BIT(11)));

	/* Enable Core digital and enable IOREG R/W */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (पंचांगpu2b | BIT(11)));

	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगpu1b & ~(BIT(7)));

	/* enable REG_EN */
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (पंचांगpu2b | BIT(11) | BIT(15)));

	/* Switch the control path. */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, SYS_CLKR);
	rtl_ग_लिखो_word(rtlpriv, SYS_CLKR, (पंचांगpu2b & (~BIT(2))));

	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, (SYS_CLKR + 1));
	पंचांगpu1b = ((पंचांगpu1b | BIT(7)) & (~BIT(6)));
	अगर (!_rtl92se_halset_sysclk(hw, पंचांगpu1b))
		वापस; /* Set failed, वापस to prevent hang. */

	rtl_ग_लिखो_word(rtlpriv, CMDR, 0x07FC);

	/* MH We must enable the section of code to prevent load IMEM fail. */
	/* Load MAC रेजिस्टर from WMAc temporarily We simulate macreg. */
	/* txt HW will provide MAC txt later  */
	rtl_ग_लिखो_byte(rtlpriv, 0x6, 0x30);
	rtl_ग_लिखो_byte(rtlpriv, 0x49, 0xf0);

	rtl_ग_लिखो_byte(rtlpriv, 0x4b, 0x81);

	rtl_ग_लिखो_byte(rtlpriv, 0xb5, 0x21);

	rtl_ग_लिखो_byte(rtlpriv, 0xdc, 0xff);
	rtl_ग_लिखो_byte(rtlpriv, 0xdd, 0xff);
	rtl_ग_लिखो_byte(rtlpriv, 0xde, 0xff);
	rtl_ग_लिखो_byte(rtlpriv, 0xdf, 0xff);

	rtl_ग_लिखो_byte(rtlpriv, 0x11a, 0x00);
	rtl_ग_लिखो_byte(rtlpriv, 0x11b, 0x00);

	क्रम (i = 0; i < 32; i++)
		rtl_ग_लिखो_byte(rtlpriv, INIMCS_SEL + i, 0x1b);

	rtl_ग_लिखो_byte(rtlpriv, 0x236, 0xff);

	rtl_ग_लिखो_byte(rtlpriv, 0x503, 0x22);

	अगर (ppsc->support_aspm && !ppsc->support_backकरोor)
		rtl_ग_लिखो_byte(rtlpriv, 0x560, 0x40);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, 0x560, 0x00);

	rtl_ग_लिखो_byte(rtlpriv, DBG_PORT, 0x91);

	/* Set RX Desc Address */
	rtl_ग_लिखो_dword(rtlpriv, RDQDA, rtlpci->rx_ring[RX_MPDU_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, RCDA, rtlpci->rx_ring[RX_CMD_QUEUE].dma);

	/* Set TX Desc Address */
	rtl_ग_लिखो_dword(rtlpriv, TBKDA, rtlpci->tx_ring[BK_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, TBEDA, rtlpci->tx_ring[BE_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, TVIDA, rtlpci->tx_ring[VI_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, TVODA, rtlpci->tx_ring[VO_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, TBDA, rtlpci->tx_ring[BEACON_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, TCDA, rtlpci->tx_ring[TXCMD_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, TMDA, rtlpci->tx_ring[MGNT_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, THPDA, rtlpci->tx_ring[HIGH_QUEUE].dma);
	rtl_ग_लिखो_dword(rtlpriv, HDA, rtlpci->tx_ring[HCCA_QUEUE].dma);

	rtl_ग_लिखो_word(rtlpriv, CMDR, 0x37FC);

	/* To make sure that TxDMA can पढ़ोy to करोwnload FW. */
	/* We should reset TxDMA अगर IMEM RPT was not पढ़ोy. */
	करो अणु
		पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, TCR);
		अगर ((पंचांगpu1b & TXDMA_INIT_VALUE) == TXDMA_INIT_VALUE)
			अवरोध;

		udelay(5);
	पूर्ण जबतक (pollingcnt--);

	अगर (pollingcnt <= 0) अणु
		pr_err("Polling TXDMA_INIT_VALUE timeout!! Current TCR(%#x)\n",
		       पंचांगpu1b);
		पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, CMDR);
		rtl_ग_लिखो_byte(rtlpriv, CMDR, पंचांगpu1b & (~TXDMA_EN));
		udelay(2);
		/* Reset TxDMA */
		rtl_ग_लिखो_byte(rtlpriv, CMDR, पंचांगpu1b | TXDMA_EN);
	पूर्ण

	/* After MACIO reset,we must refresh LED state. */
	अगर ((ppsc->rfoff_reason == RF_CHANGE_BY_IPS) ||
	   (ppsc->rfoff_reason == 0)) अणु
		काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;
		क्रमागत rf_pwrstate rfpwr_state_toset;
		rfpwr_state_toset = _rtl92se_rf_onoff_detect(hw);

		अगर (rfpwr_state_toset == ERFON)
			rtl92se_sw_led_on(hw, pled0);
	पूर्ण
पूर्ण

अटल व्योम _rtl92se_macconfig_after_fwकरोwnload(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 i;
	u16 पंचांगpu2b;

	/* 1. System Configure Register (Offset: 0x0000 - 0x003F) */

	/* 2. Command Control Register (Offset: 0x0040 - 0x004F) */
	/* Turn on 0x40 Command रेजिस्टर */
	rtl_ग_लिखो_word(rtlpriv, CMDR, (BBRSTN | BB_GLB_RSTN |
			SCHEDULE_EN | MACRXEN | MACTXEN | DDMA_EN | FW2HW_EN |
			RXDMA_EN | TXDMA_EN | HCI_RXDMA_EN | HCI_TXDMA_EN));

	/* Set TCR TX DMA pre 2 FULL enable bit	*/
	rtl_ग_लिखो_dword(rtlpriv, TCR, rtl_पढ़ो_dword(rtlpriv, TCR) |
			TXDMAPRE2FULL);

	/* Set RCR	*/
	rtl_ग_लिखो_dword(rtlpriv, RCR, rtlpci->receive_config);

	/* 3. MACID Setting Register (Offset: 0x0050 - 0x007F) */

	/* 4. Timing Control Register  (Offset: 0x0080 - 0x009F) */
	/* Set CCK/OFDM SIFS */
	/* CCK SIFS shall always be 10us. */
	rtl_ग_लिखो_word(rtlpriv, SIFS_CCK, 0x0a0a);
	rtl_ग_लिखो_word(rtlpriv, SIFS_OFDM, 0x1010);

	/* Set AckTimeout */
	rtl_ग_लिखो_byte(rtlpriv, ACK_TIMEOUT, 0x40);

	/* Beacon related */
	rtl_ग_लिखो_word(rtlpriv, BCN_INTERVAL, 100);
	rtl_ग_लिखो_word(rtlpriv, ATIMWND, 2);

	/* 5. FIFO Control Register (Offset: 0x00A0 - 0x015F) */
	/* 5.1 Initialize Number of Reserved Pages in Firmware Queue */
	/* Firmware allocate now, associate with FW पूर्णांकernal setting.!!! */

	/* 5.2 Setting TX/RX page size 0/1/2/3/4=64/128/256/512/1024 */
	/* 5.3 Set driver info, we only accept PHY status now. */
	/* 5.4 Set RXDMA arbitration to control RXDMA/MAC/FW R/W क्रम RXFIFO  */
	rtl_ग_लिखो_byte(rtlpriv, RXDMA, rtl_पढ़ो_byte(rtlpriv, RXDMA) | BIT(6));

	/* 6. Adaptive Control Register  (Offset: 0x0160 - 0x01CF) */
	/* Set RRSR to all legacy rate and HT rate
	 * CCK rate is supported by शेष.
	 * CCK rate will be filtered out only when associated
	 * AP करोes not support it.
	 * Only enable ACK rate to OFDM 24M
	 * Disable RRSR क्रम CCK rate in A-Cut	*/

	अगर (rtlhal->version == VERSION_8192S_ACUT)
		rtl_ग_लिखो_byte(rtlpriv, RRSR, 0xf0);
	अन्यथा अगर (rtlhal->version == VERSION_8192S_BCUT)
		rtl_ग_लिखो_byte(rtlpriv, RRSR, 0xff);
	rtl_ग_लिखो_byte(rtlpriv, RRSR + 1, 0x01);
	rtl_ग_लिखो_byte(rtlpriv, RRSR + 2, 0x00);

	/* A-Cut IC करो not support CCK rate. We क्रमbid ARFR to */
	/* fallback to CCK rate */
	क्रम (i = 0; i < 8; i++) अणु
		/*Disable RRSR क्रम CCK rate in A-Cut */
		अगर (rtlhal->version == VERSION_8192S_ACUT)
			rtl_ग_लिखो_dword(rtlpriv, ARFR0 + i * 4, 0x1f0ff0f0);
	पूर्ण

	/* Dअगरferent rate use dअगरferent AMPDU size */
	/* MCS32/ MCS15_SG use max AMPDU size 15*2=30K */
	rtl_ग_लिखो_byte(rtlpriv, AGGLEN_LMT_H, 0x0f);
	/* MCS0/1/2/3 use max AMPDU size 4*2=8K */
	rtl_ग_लिखो_word(rtlpriv, AGGLEN_LMT_L, 0x7442);
	/* MCS4/5 use max AMPDU size 8*2=16K 6/7 use 10*2=20K */
	rtl_ग_लिखो_word(rtlpriv, AGGLEN_LMT_L + 2, 0xddd7);
	/* MCS8/9 use max AMPDU size 8*2=16K 10/11 use 10*2=20K */
	rtl_ग_लिखो_word(rtlpriv, AGGLEN_LMT_L + 4, 0xd772);
	/* MCS12/13/14/15 use max AMPDU size 15*2=30K */
	rtl_ग_लिखो_word(rtlpriv, AGGLEN_LMT_L + 6, 0xfffd);

	/* Set Data / Response स्वतः rate fallack retry count */
	rtl_ग_लिखो_dword(rtlpriv, DARFRC, 0x04010000);
	rtl_ग_लिखो_dword(rtlpriv, DARFRC + 4, 0x09070605);
	rtl_ग_लिखो_dword(rtlpriv, RARFRC, 0x04010000);
	rtl_ग_लिखो_dword(rtlpriv, RARFRC + 4, 0x09070605);

	/* 7. EDCA Setting Register (Offset: 0x01D0 - 0x01FF) */
	/* Set all rate to support SG */
	rtl_ग_लिखो_word(rtlpriv, SG_RATE, 0xFFFF);

	/* 8. WMAC, BA, and CCX related Register (Offset: 0x0200 - 0x023F) */
	/* Set NAV protection length */
	rtl_ग_लिखो_word(rtlpriv, NAV_PROT_LEN, 0x0080);
	/* CF-END Threshold */
	rtl_ग_लिखो_byte(rtlpriv, CFEND_TH, 0xFF);
	/* Set AMPDU minimum space */
	rtl_ग_लिखो_byte(rtlpriv, AMPDU_MIN_SPACE, 0x07);
	/* Set TXOP stall control क्रम several queue/HI/BCN/MGT/ */
	rtl_ग_लिखो_byte(rtlpriv, TXOP_STALL_CTRL, 0x00);

	/* 9. Security Control Register (Offset: 0x0240 - 0x025F) */
	/* 10. Power Save Control Register (Offset: 0x0260 - 0x02DF) */
	/* 11. General Purpose Register (Offset: 0x02E0 - 0x02FF) */
	/* 12. Host Interrupt Status Register (Offset: 0x0300 - 0x030F) */
	/* 13. Test mode and Debug Control Register (Offset: 0x0310 - 0x034F) */

	/* 14. Set driver info, we only accept PHY status now. */
	rtl_ग_लिखो_byte(rtlpriv, RXDRVINFO_SZ, 4);

	/* 15. For EEPROM R/W Workaround */
	/* 16. For EFUSE to share REG_SYS_FUNC_EN with EEPROM!!! */
	पंचांगpu2b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, पंचांगpu2b | BIT(13));
	पंचांगpu2b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_ISO_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL, पंचांगpu2b & (~BIT(8)));

	/* 17. For EFUSE */
	/* We may R/W EFUSE in EEPROM mode */
	अगर (rtlefuse->epromtype == EEPROM_BOOT_EFUSE) अणु
		u8	tempval;

		tempval = rtl_पढ़ो_byte(rtlpriv, REG_SYS_ISO_CTRL + 1);
		tempval &= 0xFE;
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL + 1, tempval);

		/* Change Program timing */
		rtl_ग_लिखो_byte(rtlpriv, REG_EFUSE_CTRL + 3, 0x72);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "EFUSE CONFIG OK\n");
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "OK\n");

पूर्ण

अटल व्योम _rtl92se_hw_configure(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	u8 reg_bw_opmode = 0;
	u32 reg_rrsr = 0;
	u8 regपंचांगp = 0;

	reg_bw_opmode = BW_OPMODE_20MHZ;
	reg_rrsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;

	regपंचांगp = rtl_पढ़ो_byte(rtlpriv, INIRTSMCS_SEL);
	reg_rrsr = ((reg_rrsr & 0x000fffff) << 8) | regपंचांगp;
	rtl_ग_लिखो_dword(rtlpriv, INIRTSMCS_SEL, reg_rrsr);
	rtl_ग_लिखो_byte(rtlpriv, BW_OPMODE, reg_bw_opmode);

	/* Set Retry Limit here */
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RETRY_LIMIT,
			(u8 *)(&rtlpci->लघुretry_limit));

	rtl_ग_लिखो_byte(rtlpriv, MLT, 0x8f);

	/* For Min Spacing configuration. */
	चयन (rtlphy->rf_type) अणु
	हाल RF_1T2R:
	हाल RF_1T1R:
		rtlhal->minspace_cfg = (MAX_MSS_DENSITY_1T << 3);
		अवरोध;
	हाल RF_2T2R:
	हाल RF_2T2R_GREEN:
		rtlhal->minspace_cfg = (MAX_MSS_DENSITY_2T << 3);
		अवरोध;
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, AMPDU_MIN_SPACE, rtlhal->minspace_cfg);
पूर्ण

पूर्णांक rtl92se_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 पंचांगp_byte = 0;
	अचिन्हित दीर्घ flags;
	bool rtstatus = true;
	u8 पंचांगp_u1b;
	पूर्णांक err = false;
	u8 i;
	पूर्णांक wdcapra_add[] = अणु
		EDCAPARA_BE, EDCAPARA_BK,
		EDCAPARA_VI, EDCAPARA_VOपूर्ण;
	u8 secr_value = 0x0;

	rtlpci->being_init_adapter = true;

	/* As this function can take a very दीर्घ समय (up to 350 ms)
	 * and can be called with irqs disabled, reenable the irqs
	 * to let the other devices जारी being serviced.
	 *
	 * It is safe करोing so since our own पूर्णांकerrupts will only be enabled
	 * in a subsequent step.
	 */
	local_save_flags(flags);
	local_irq_enable();

	rtlpriv->पूर्णांकf_ops->disable_aspm(hw);

	/* 1. MAC Initialize */
	/* Beक्रमe FW करोwnload, we have to set some MAC रेजिस्टर */
	_rtl92se_macconfig_beक्रमe_fwकरोwnload(hw);

	rtlhal->version = (क्रमागत version_8192s)((rtl_पढ़ो_dword(rtlpriv,
			PMC_FSM) >> 16) & 0xF);

	rtl8192se_gpiobit3_cfg_inpuपंचांगode(hw);

	/* 2. करोwnload firmware */
	rtstatus = rtl92s_करोwnload_fw(hw);
	अगर (!rtstatus) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Failed to download FW. Init HW without FW now... Please copy FW into /lib/firmware/rtlwifi\n");
		err = 1;
		जाओ निकास;
	पूर्ण

	/* After FW करोwnload, we have to reset MAC रेजिस्टर */
	_rtl92se_macconfig_after_fwकरोwnload(hw);

	/*Retrieve शेष FW Cmd IO map. */
	rtlhal->fwcmd_iomap =	rtl_पढ़ो_word(rtlpriv, LBUS_MON_ADDR);
	rtlhal->fwcmd_ioparam = rtl_पढ़ो_dword(rtlpriv, LBUS_ADDR_MASK);

	/* 3. Initialize MAC/PHY Config by MACPHY_reg.txt */
	अगर (!rtl92s_phy_mac_config(hw)) अणु
		pr_err("MAC Config failed\n");
		err = rtstatus;
		जाओ निकास;
	पूर्ण

	/* because last function modअगरy RCR, so we update
	 * rcr var here, or TP will unstable क्रम receive_config
	 * is wrong, RX RCR_ACRC32 will cause TP unstabel & Rx
	 * RCR_APP_ICV will cause mac80211 unassoc क्रम cisco 1252
	 */
	rtlpci->receive_config = rtl_पढ़ो_dword(rtlpriv, RCR);
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);
	rtl_ग_लिखो_dword(rtlpriv, RCR, rtlpci->receive_config);

	/* Make sure BB/RF ग_लिखो OK. We should prevent enter IPS. radio off. */
	/* We must set flag aव्योम BB/RF config period later!! */
	rtl_ग_लिखो_dword(rtlpriv, CMDR, 0x37FC);

	/* 4. Initialize BB After MAC Config PHY_reg.txt, AGC_Tab.txt */
	अगर (!rtl92s_phy_bb_config(hw)) अणु
		pr_err("BB Config failed\n");
		err = rtstatus;
		जाओ निकास;
	पूर्ण

	/* 5. Initiailze RF RAIO_A.txt RF RAIO_B.txt */
	/* Beक्रमe initalizing RF. We can not use FW to करो RF-R/W. */

	rtlphy->rf_mode = RF_OP_BY_SW_3WIRE;

	/* Beक्रमe RF-R/W we must execute the IO from Scott's suggestion. */
	rtl_ग_लिखो_byte(rtlpriv, AFE_XTAL_CTRL + 1, 0xDB);
	अगर (rtlhal->version == VERSION_8192S_ACUT)
		rtl_ग_लिखो_byte(rtlpriv, SPS1_CTRL + 3, 0x07);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, RF_CTRL, 0x07);

	अगर (!rtl92s_phy_rf_config(hw)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "RF Config failed\n");
		err = rtstatus;
		जाओ निकास;
	पूर्ण

	/* After पढ़ो predefined TXT, we must set BB/MAC/RF
	 * रेजिस्टर as our requirement */

	rtlphy->rfreg_chnlval[0] = rtl92s_phy_query_rf_reg(hw,
							   (क्रमागत radio_path)0,
							   RF_CHNLBW,
							   RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl92s_phy_query_rf_reg(hw,
							   (क्रमागत radio_path)1,
							   RF_CHNLBW,
							   RFREG_OFFSET_MASK);

	/*---- Set CCK and OFDM Block "ON"----*/
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);

	/*3 Set Hardware(Do nothing now) */
	_rtl92se_hw_configure(hw);

	/* Read EEPROM TX घातer index and PHY_REG_PG.txt to capture correct */
	/* TX घातer index क्रम dअगरferent rate set. */
	/* Get original hw reg values */
	rtl92s_phy_get_hw_reg_originalvalue(hw);
	/* Write correct tx घातer index */
	rtl92s_phy_set_txघातer(hw, rtlphy->current_channel);

	/* We must set MAC address after firmware करोwnload. */
	क्रम (i = 0; i < 6; i++)
		rtl_ग_लिखो_byte(rtlpriv, MACIDR0 + i, rtlefuse->dev_addr[i]);

	/* EEPROM R/W workaround */
	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, MAC_PINMUX_CFG);
	rtl_ग_लिखो_byte(rtlpriv, MAC_PINMUX_CFG, पंचांगp_u1b & (~BIT(3)));

	rtl_ग_लिखो_byte(rtlpriv, 0x4d, 0x0);

	अगर (hal_get_firmwareversion(rtlpriv) >= 0x49) अणु
		पंचांगp_byte = rtl_पढ़ो_byte(rtlpriv, FW_RSVD_PG_CRTL) & (~BIT(4));
		पंचांगp_byte = पंचांगp_byte | BIT(5);
		rtl_ग_लिखो_byte(rtlpriv, FW_RSVD_PG_CRTL, पंचांगp_byte);
		rtl_ग_लिखो_dword(rtlpriv, TXDESC_MSK, 0xFFFFCFFF);
	पूर्ण

	/* We enable high घातer and RA related mechanism after NIC
	 * initialized. */
	अगर (hal_get_firmwareversion(rtlpriv) >= 0x35) अणु
		/* Fw v.53 and later. */
		rtl92s_phy_set_fw_cmd(hw, FW_CMD_RA_INIT);
	पूर्ण अन्यथा अगर (hal_get_firmwareversion(rtlpriv) == 0x34) अणु
		/* Fw v.52. */
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_RA_INIT);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
	पूर्ण अन्यथा अणु
		/* Compatible earlier FW version. */
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_RA_RESET);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_RA_ACTIVE);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_RA_REFRESH);
		rtl92s_phy_chk_fwcmd_ioकरोne(hw);
	पूर्ण

	/* Add to prevent ASPM bug. */
	/* Always enable hst and NIC घड़ी request. */
	rtl92s_phy_चयन_ephy_parameter(hw);

	/* Security related
	 * 1. Clear all H/W keys.
	 * 2. Enable H/W encryption/decryption. */
	rtl_cam_reset_all_entry(hw);
	secr_value |= SCR_TXENCENABLE;
	secr_value |= SCR_RXENCENABLE;
	secr_value |= SCR_NOSKMC;
	rtl_ग_लिखो_byte(rtlpriv, REG_SECR, secr_value);

	क्रम (i = 0; i < 4; i++)
		rtl_ग_लिखो_dword(rtlpriv, wdcapra_add[i], 0x5e4322);

	अगर (rtlphy->rf_type == RF_1T2R) अणु
		bool mrc2set = true;
		/* Turn on B-Path */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_MRC, (u8 *)&mrc2set);
	पूर्ण

	rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_ON);
	rtl92s_dm_init(hw);
निकास:
	local_irq_restore(flags);
	rtlpci->being_init_adapter = false;
	वापस err;
पूर्ण

व्योम rtl92se_set_mac_addr(काष्ठा rtl_io *io, स्थिर u8 *addr)
अणु
	/* This is a stub. */
पूर्ण

व्योम rtl92se_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 reg_rcr;

	अगर (rtlpriv->psc.rfpwr_state != ERFON)
		वापस;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RCR, (u8 *)(&reg_rcr));

	अगर (check_bssid) अणु
		reg_rcr |= (RCR_CBSSID);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR, (u8 *)(&reg_rcr));
	पूर्ण अन्यथा अगर (!check_bssid) अणु
		reg_rcr &= (~RCR_CBSSID);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR, (u8 *)(&reg_rcr));
	पूर्ण

पूर्ण

अटल पूर्णांक _rtl92se_set_media_status(काष्ठा ieee80211_hw *hw,
				     क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_msr = rtl_पढ़ो_byte(rtlpriv, MSR);
	u32 temp;
	bt_msr &= ~MSR_LINK_MASK;

	चयन (type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		bt_msr |= (MSR_LINK_NONE << MSR_LINK_SHIFT);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to NO LINK!\n");
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		bt_msr |= (MSR_LINK_ADHOC << MSR_LINK_SHIFT);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to Ad Hoc!\n");
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		bt_msr |= (MSR_LINK_MANAGED << MSR_LINK_SHIFT);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to STA!\n");
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		bt_msr |= (MSR_LINK_MASTER << MSR_LINK_SHIFT);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to AP!\n");
		अवरोध;
	शेष:
		pr_err("Network type %d not supported!\n", type);
		वापस 1;

	पूर्ण

	अगर (type != NL80211_IFTYPE_AP &&
	    rtlpriv->mac80211.link_state < MAC80211_LINKED)
		bt_msr = rtl_पढ़ो_byte(rtlpriv, MSR) & ~MSR_LINK_MASK;
	rtl_ग_लिखो_byte(rtlpriv, MSR, bt_msr);

	temp = rtl_पढ़ो_dword(rtlpriv, TCR);
	rtl_ग_लिखो_dword(rtlpriv, TCR, temp & (~BIT(8)));
	rtl_ग_लिखो_dword(rtlpriv, TCR, temp | BIT(8));


	वापस 0;
पूर्ण

/* HW_VAR_MEDIA_STATUS & HW_VAR_CECHK_BSSID */
पूर्णांक rtl92se_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (_rtl92se_set_media_status(hw, type))
		वापस -EOPNOTSUPP;

	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		अगर (type != NL80211_IFTYPE_AP)
			rtl92se_set_check_bssid(hw, true);
	पूर्ण अन्यथा अणु
		rtl92se_set_check_bssid(hw, false);
	पूर्ण

	वापस 0;
पूर्ण

/* करोn't set REG_EDCA_BE_PARAM here because mac80211 will send pkt when scan */
व्योम rtl92se_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	rtl92s_dm_init_edca_turbo(hw);

	चयन (aci) अणु
	हाल AC1_BK:
		rtl_ग_लिखो_dword(rtlpriv, EDCAPARA_BK, 0xa44f);
		अवरोध;
	हाल AC0_BE:
		/* rtl_ग_लिखो_dword(rtlpriv, EDCAPARA_BE, u4b_ac_param); */
		अवरोध;
	हाल AC2_VI:
		rtl_ग_लिखो_dword(rtlpriv, EDCAPARA_VI, 0x5e4322);
		अवरोध;
	हाल AC3_VO:
		rtl_ग_लिखो_dword(rtlpriv, EDCAPARA_VO, 0x2f3222);
		अवरोध;
	शेष:
		WARN_ONCE(true, "rtl8192se: invalid aci: %d !\n", aci);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92se_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, INTA_MASK, rtlpci->irq_mask[0]);
	/* Support Bit 32-37(Assign as Bit 0-5) पूर्णांकerrupt setting now */
	rtl_ग_लिखो_dword(rtlpriv, INTA_MASK + 4, rtlpci->irq_mask[1] & 0x3F);
	rtlpci->irq_enabled = true;
पूर्ण

व्योम rtl92se_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv;
	काष्ठा rtl_pci *rtlpci;

	rtlpriv = rtl_priv(hw);
	/* अगर firmware not available, no पूर्णांकerrupts */
	अगर (!rtlpriv || !rtlpriv->max_fw_size)
		वापस;
	rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	rtl_ग_लिखो_dword(rtlpriv, INTA_MASK, 0);
	rtl_ग_लिखो_dword(rtlpriv, INTA_MASK + 4, 0);
	rtlpci->irq_enabled = false;
पूर्ण

अटल u8 _rtl92s_set_sysclk(काष्ठा ieee80211_hw *hw, u8 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 रुकोcnt = 100;
	bool result = false;
	u8 पंचांगp;

	rtl_ग_लिखो_byte(rtlpriv, SYS_CLKR + 1, data);

	/* Wait the MAC synchronized. */
	udelay(400);

	/* Check अगर it is set पढ़ोy. */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, SYS_CLKR + 1);
	result = ((पंचांगp & BIT(7)) == (data & BIT(7)));

	अगर (!(data & (BIT(6) | BIT(7)))) अणु
		रुकोcnt = 100;
		पंचांगp = 0;

		जबतक (1) अणु
			रुकोcnt--;
			पंचांगp = rtl_पढ़ो_byte(rtlpriv, SYS_CLKR + 1);

			अगर ((पंचांगp & BIT(6)))
				अवरोध;

			pr_err("wait for BIT(6) return value %x\n", पंचांगp);

			अगर (रुकोcnt == 0)
				अवरोध;
			udelay(10);
		पूर्ण

		अगर (रुकोcnt == 0)
			result = false;
		अन्यथा
			result = true;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम _rtl92s_phy_set_rfhalt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 u1bपंचांगp;

	अगर (rtlhal->driver_going2unload)
		rtl_ग_लिखो_byte(rtlpriv, 0x560, 0x0);

	/* Power save क्रम BB/RF */
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
	rtl_ग_लिखो_word(rtlpriv, CMDR, 0x0000);

	अगर (rtlhal->driver_going2unload) अणु
		u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, (REG_SYS_FUNC_EN + 1));
		u1bपंचांगp &= ~(BIT(0));
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, u1bपंचांगp);
	पूर्ण

	u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, (SYS_CLKR + 1));

	/* Add description. After चयन control path. रेजिस्टर
	 * after page1 will be invisible. We can not करो any IO
	 * क्रम रेजिस्टर>0x40. After resume&MACIO reset, we need
	 * to remember previous reg content. */
	अगर (u1bपंचांगp & BIT(7)) अणु
		u1bपंचांगp &= ~(BIT(6) | BIT(7));
		अगर (!_rtl92s_set_sysclk(hw, u1bपंचांगp)) अणु
			pr_err("Switch ctrl path fail\n");
			वापस;
		पूर्ण
	पूर्ण

	/* Power save क्रम MAC */
	अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS  &&
		!rtlhal->driver_going2unload) अणु
		/* enable LED function */
		rtl_ग_लिखो_byte(rtlpriv, 0x03, 0xF9);
	/* SW/HW radio off or halt adapter!! For example S3/S4 */
	पूर्ण अन्यथा अणु
		/* LED function disable. Power range is about 8mA now. */
		/* अगर ग_लिखो 0xF1 disconnect_pci घातer
		 *	 अगरconfig wlan0 करोwn घातer are both high 35:70 */
		/* अगर ग_लिखो oxF9 disconnect_pci घातer
		 * अगरconfig wlan0 करोwn घातer are both low  12:45*/
		rtl_ग_लिखो_byte(rtlpriv, 0x03, 0xF9);
	पूर्ण

	rtl_ग_लिखो_byte(rtlpriv, SYS_CLKR + 1, 0x70);
	rtl_ग_लिखो_byte(rtlpriv, AFE_PLL_CTRL + 1, 0x68);
	rtl_ग_लिखो_byte(rtlpriv,  AFE_PLL_CTRL, 0x00);
	rtl_ग_लिखो_byte(rtlpriv, LDOA15_CTRL, 0x34);
	rtl_ग_लिखो_byte(rtlpriv, AFE_XTAL_CTRL, 0x0E);
	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);

पूर्ण

अटल व्योम _rtl92se_gen_refreshledstate(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;

	अगर (rtlpci->up_first_समय)
		वापस;

	अगर (rtlpriv->psc.rfoff_reason == RF_CHANGE_BY_IPS)
		rtl92se_sw_led_on(hw, pled0);
	अन्यथा
		rtl92se_sw_led_off(hw, pled0);
पूर्ण


अटल व्योम _rtl92se_घातer_करोमुख्य_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 पंचांगpu2b;
	u8 पंचांगpu1b;

	rtlpriv->psc.pwrकरोमुख्य_protect = true;

	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, (SYS_CLKR + 1));
	अगर (पंचांगpu1b & BIT(7)) अणु
		पंचांगpu1b &= ~(BIT(6) | BIT(7));
		अगर (!_rtl92s_set_sysclk(hw, पंचांगpu1b)) अणु
			rtlpriv->psc.pwrकरोमुख्य_protect = false;
			वापस;
		पूर्ण
	पूर्ण

	rtl_ग_लिखो_byte(rtlpriv, AFE_PLL_CTRL, 0x0);
	rtl_ग_लिखो_byte(rtlpriv, LDOA15_CTRL, 0x34);

	/* Reset MAC-IO and CPU and Core Digital BIT10/11/15 */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);

	/* If IPS we need to turn LED on. So we not
	 * not disable BIT 3/7 of reg3. */
	अगर (rtlpriv->psc.rfoff_reason & (RF_CHANGE_BY_IPS | RF_CHANGE_BY_HW))
		पंचांगpu1b &= 0xFB;
	अन्यथा
		पंचांगpu1b &= 0x73;

	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगpu1b);
	/* रुको क्रम BIT 10/11/15 to pull high स्वतःmatically!! */
	mdelay(1);

	rtl_ग_लिखो_byte(rtlpriv, CMDR, 0);
	rtl_ग_लिखो_byte(rtlpriv, TCR, 0);

	/* Data sheet not define 0x562!!! Copy from WMAC!!!!! */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, 0x562);
	पंचांगpu1b |= 0x08;
	rtl_ग_लिखो_byte(rtlpriv, 0x562, पंचांगpu1b);
	पंचांगpu1b &= ~(BIT(3));
	rtl_ग_लिखो_byte(rtlpriv, 0x562, पंचांगpu1b);

	/* Enable AFE घड़ी source */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_XTAL_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, AFE_XTAL_CTRL, (पंचांगpu1b | 0x01));
	/* Delay 1.5ms */
	udelay(1500);
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_XTAL_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, AFE_XTAL_CTRL + 1, (पंचांगpu1b & 0xfb));

	/* Enable AFE Macro Block's Bandgap */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_MISC);
	rtl_ग_लिखो_byte(rtlpriv, AFE_MISC, (पंचांगpu1b | BIT(0)));
	mdelay(1);

	/* Enable AFE Mbias */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_MISC);
	rtl_ग_लिखो_byte(rtlpriv, AFE_MISC, (पंचांगpu1b | 0x02));
	mdelay(1);

	/* Enable LDOA15 block */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, LDOA15_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, LDOA15_CTRL, (पंचांगpu1b | BIT(0)));

	/* Set Digital Vdd to Retention isolation Path. */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, REG_SYS_ISO_CTRL);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_ISO_CTRL, (पंचांगpu2b | BIT(11)));


	/* For warm reboot NIC disappera bug. */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (पंचांगpu2b | BIT(13)));

	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL + 1, 0x68);

	/* Enable AFE PLL Macro Block */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_PLL_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, AFE_PLL_CTRL, (पंचांगpu1b | BIT(0) | BIT(4)));
	/* Enable MAC 80MHZ घड़ी */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, AFE_PLL_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, AFE_PLL_CTRL + 1, (पंचांगpu1b | BIT(0)));
	mdelay(1);

	/* Release isolation AFE PLL & MD */
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL, 0xA6);

	/* Enable MAC घड़ी */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, SYS_CLKR);
	rtl_ग_लिखो_word(rtlpriv, SYS_CLKR, (पंचांगpu2b | BIT(12) | BIT(11)));

	/* Enable Core digital and enable IOREG R/W */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (पंचांगpu2b | BIT(11)));
	/* enable REG_EN */
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (पंचांगpu2b | BIT(11) | BIT(15)));

	/* Switch the control path. */
	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, SYS_CLKR);
	rtl_ग_लिखो_word(rtlpriv, SYS_CLKR, (पंचांगpu2b & (~BIT(2))));

	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, (SYS_CLKR + 1));
	पंचांगpu1b = ((पंचांगpu1b | BIT(7)) & (~BIT(6)));
	अगर (!_rtl92s_set_sysclk(hw, पंचांगpu1b)) अणु
		rtlpriv->psc.pwrकरोमुख्य_protect = false;
		वापस;
	पूर्ण

	rtl_ग_लिखो_word(rtlpriv, CMDR, 0x37FC);

	/* After MACIO reset,we must refresh LED state. */
	_rtl92se_gen_refreshledstate(hw);

	rtlpriv->psc.pwrकरोमुख्य_protect = false;
पूर्ण

व्योम rtl92se_card_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	क्रमागत nl80211_अगरtype opmode;
	u8 रुको = 30;

	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);

	अगर (rtlpci->driver_is_goingto_unload ||
		ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);

	/* we should chnge GPIO to input mode
	 * this will drop away current about 25mA*/
	rtl8192se_gpiobit3_cfg_inpuपंचांगode(hw);

	/* this is very important क्रम ips घातer save */
	जबतक (रुको-- >= 10 && rtlpriv->psc.pwrकरोमुख्य_protect) अणु
		अगर (rtlpriv->psc.pwrकरोमुख्य_protect)
			mdelay(20);
		अन्यथा
			अवरोध;
	पूर्ण

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;
	_rtl92se_set_media_status(hw, opmode);

	_rtl92s_phy_set_rfhalt(hw);
	udelay(100);
पूर्ण

व्योम rtl92se_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_पूर्णांक *पूर्णांकvec)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	पूर्णांकvec->पूर्णांकa = rtl_पढ़ो_dword(rtlpriv, ISR) & rtlpci->irq_mask[0];
	rtl_ग_लिखो_dword(rtlpriv, ISR, पूर्णांकvec->पूर्णांकa);

	पूर्णांकvec->पूर्णांकb = rtl_पढ़ो_dword(rtlpriv, ISR + 4) & rtlpci->irq_mask[1];
	rtl_ग_लिखो_dword(rtlpriv, ISR + 4, पूर्णांकvec->पूर्णांकb);
पूर्ण

व्योम rtl92se_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcnसमय_cfg = 0;
	u16 bcn_cw = 6, bcn_अगरs = 0xf;
	u16 atim_winकरोw = 2;

	/* ATIM Winकरोw (in unit of TU). */
	rtl_ग_लिखो_word(rtlpriv, ATIMWND, atim_winकरोw);

	/* Beacon पूर्णांकerval (in unit of TU). */
	rtl_ग_लिखो_word(rtlpriv, BCN_INTERVAL, mac->beacon_पूर्णांकerval);

	/* DrvErlyInt (in unit of TU). (Time to send
	 * पूर्णांकerrupt to notअगरy driver to change
	 * beacon content) */
	rtl_ग_लिखो_word(rtlpriv, BCN_DRV_EARLY_INT, 10 << 4);

	/* BcnDMATIM(in unit of us). Indicates the
	 * समय beक्रमe TBTT to perक्रमm beacon queue DMA  */
	rtl_ग_लिखो_word(rtlpriv, BCN_DMATIME, 256);

	/* Force beacon frame transmission even
	 * after receiving beacon frame from
	 * other ad hoc STA */
	rtl_ग_लिखो_byte(rtlpriv, BCN_ERR_THRESH, 100);

	/* Beacon Time Configuration */
	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		bcnसमय_cfg |= (bcn_cw << BCN_TCFG_CW_SHIFT);

	/* TODO: bcn_अगरs may required to be changed on ASIC */
	bcnसमय_cfg |= bcn_अगरs << BCN_TCFG_IFS;

	/*क्रम beacon changed */
	rtl92s_phy_set_beacon_hwreg(hw, mac->beacon_पूर्णांकerval);
पूर्ण

व्योम rtl92se_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;

	/* Beacon पूर्णांकerval (in unit of TU). */
	rtl_ग_लिखो_word(rtlpriv, BCN_INTERVAL, bcn_पूर्णांकerval);
	/* 2008.10.24 added by tynli क्रम beacon changed. */
	rtl92s_phy_set_beacon_hwreg(hw, bcn_पूर्णांकerval);
पूर्ण

व्योम rtl92se_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
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

	rtl92se_disable_पूर्णांकerrupt(hw);
	rtl92se_enable_पूर्णांकerrupt(hw);
पूर्ण

अटल व्योम _rtl8192se_get_ic_inferiority(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 efuse_id;

	rtlhal->ic_class = IC_INFERIORITY_A;

	/* Only retrieving जबतक using EFUSE. */
	अगर ((rtlefuse->epromtype == EEPROM_BOOT_EFUSE) &&
		!rtlefuse->स्वतःload_failflag) अणु
		efuse_id = efuse_पढ़ो_1byte(hw, EFUSE_IC_ID_OFFSET);

		अगर (efuse_id == 0xfe)
			rtlhal->ic_class = IC_INFERIORITY_B;
	पूर्ण
पूर्ण

अटल व्योम _rtl92se_पढ़ो_adapter_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा device *dev = &rtl_pcipriv(hw)->dev.pdev->dev;
	u16 i, usvalue;
	u16	eeprom_id;
	u8 tempval;
	u8 hwinfo[HWSET_MAX_SIZE_92S];
	u8 rf_path, index;

	चयन (rtlefuse->epromtype) अणु
	हाल EEPROM_BOOT_EFUSE:
		rtl_efuse_shaकरोw_map_update(hw);
		अवरोध;

	हाल EEPROM_93C46:
		pr_err("RTL819X Not boot from eeprom, check it !!\n");
		वापस;

	शेष:
		dev_warn(dev, "no efuse data\n");
		वापस;
	पूर्ण

	स_नकल(hwinfo, &rtlefuse->efuse_map[EFUSE_INIT_MAP][0],
	       HWSET_MAX_SIZE_92S);

	RT_PRINT_DATA(rtlpriv, COMP_INIT, DBG_DMESG, "MAP",
		      hwinfo, HWSET_MAX_SIZE_92S);

	eeprom_id = *((u16 *)&hwinfo[0]);
	अगर (eeprom_id != RTL8190_EEPROM_ID) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"EEPROM ID(%#x) is invalid!!\n", eeprom_id);
		rtlefuse->स्वतःload_failflag = true;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Autoload OK\n");
		rtlefuse->स्वतःload_failflag = false;
	पूर्ण

	अगर (rtlefuse->स्वतःload_failflag)
		वापस;

	_rtl8192se_get_ic_inferiority(hw);

	/* Read IC Version && Channel Plan */
	/* VID, DID	 SE	0xA-D */
	rtlefuse->eeprom_vid = *(u16 *)&hwinfo[EEPROM_VID];
	rtlefuse->eeprom_did = *(u16 *)&hwinfo[EEPROM_DID];
	rtlefuse->eeprom_svid = *(u16 *)&hwinfo[EEPROM_SVID];
	rtlefuse->eeprom_smid = *(u16 *)&hwinfo[EEPROM_SMID];
	rtlefuse->eeprom_version = *(u16 *)&hwinfo[EEPROM_VERSION];

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROMId = 0x%4x\n", eeprom_id);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM VID = 0x%4x\n", rtlefuse->eeprom_vid);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM DID = 0x%4x\n", rtlefuse->eeprom_did);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM SVID = 0x%4x\n", rtlefuse->eeprom_svid);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM SMID = 0x%4x\n", rtlefuse->eeprom_smid);

	क्रम (i = 0; i < 6; i += 2) अणु
		usvalue = *(u16 *)&hwinfo[EEPROM_MAC_ADDR + i];
		*((u16 *) (&rtlefuse->dev_addr[i])) = usvalue;
	पूर्ण

	क्रम (i = 0; i < 6; i++)
		rtl_ग_लिखो_byte(rtlpriv, MACIDR0 + i, rtlefuse->dev_addr[i]);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "%pM\n", rtlefuse->dev_addr);

	/* Get Tx Power Level by Channel */
	/* Read Tx घातer of Channel 1 ~ 14 from EEPROM. */
	/* 92S suupport RF A & B */
	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 3; i++) अणु
			/* Read CCK RF A & B Tx घातer  */
			rtlefuse->eeprom_chnlarea_txpwr_cck[rf_path][i] =
			hwinfo[EEPROM_TXPOWERBASE + rf_path * 3 + i];

			/* Read OFDM RF A & B Tx घातer क्रम 1T */
			rtlefuse->eeprom_chnlarea_txpwr_ht40_1s[rf_path][i] =
			hwinfo[EEPROM_TXPOWERBASE + 6 + rf_path * 3 + i];

			/* Read OFDM RF A & B Tx घातer क्रम 2T */
			rtlefuse->eprom_chnl_txpwr_ht40_2sdf[rf_path][i]
				 = hwinfo[EEPROM_TXPOWERBASE + 12 +
				   rf_path * 3 + i];
		पूर्ण
	पूर्ण

	क्रम (rf_path = 0; rf_path < 2; rf_path++)
		क्रम (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM CCK Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->eeprom_chnlarea_txpwr_cck
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

		/* Assign dedicated channel tx घातer */
		क्रम (i = 0; i < 14; i++)	अणु
			/* channel 1~3 use the same Tx Power Level. */
			अगर (i < 3)
				index = 0;
			/* Channel 4-8 */
			अन्यथा अगर (i < 8)
				index = 1;
			/* Channel 9-14 */
			अन्यथा
				index = 2;

			/* Record A & B CCK /OFDM - 1T/2T Channel area
			 * tx घातer */
			rtlefuse->txpwrlevel_cck[rf_path][i]  =
				rtlefuse->eeprom_chnlarea_txpwr_cck
							[rf_path][index];
			rtlefuse->txpwrlevel_ht40_1s[rf_path][i]  =
				rtlefuse->eeprom_chnlarea_txpwr_ht40_1s
							[rf_path][index];
			rtlefuse->txpwrlevel_ht40_2s[rf_path][i]  =
				rtlefuse->eprom_chnl_txpwr_ht40_2sdf
							[rf_path][index];
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

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 3; i++) अणु
			/* Read Power dअगरf limit. */
			rtlefuse->eeprom_pwrgroup[rf_path][i] =
				hwinfo[EEPROM_TXPWRGROUP + rf_path * 3 + i];
		पूर्ण
	पूर्ण

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		/* Fill Pwr group */
		क्रम (i = 0; i < 14; i++) अणु
			/* Chanel 1-3 */
			अगर (i < 3)
				index = 0;
			/* Channel 4-8 */
			अन्यथा अगर (i < 8)
				index = 1;
			/* Channel 9-13 */
			अन्यथा
				index = 2;

			rtlefuse->pwrgroup_ht20[rf_path][i] =
				(rtlefuse->eeprom_pwrgroup[rf_path][index] &
				0xf);
			rtlefuse->pwrgroup_ht40[rf_path][i] =
				((rtlefuse->eeprom_pwrgroup[rf_path][index] &
				0xf0) >> 4);

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
		/* Read tx घातer dअगरference between HT OFDM 20/40 MHZ */
		/* channel 1-3 */
		अगर (i < 3)
			index = 0;
		/* Channel 4-8 */
		अन्यथा अगर (i < 8)
			index = 1;
		/* Channel 9-14 */
		अन्यथा
			index = 2;

		tempval = hwinfo[EEPROM_TX_PWR_HT20_DIFF + index] & 0xff;
		rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i] = (tempval & 0xF);
		rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i] =
						 ((tempval >> 4) & 0xF);

		/* Read OFDM<->HT tx घातer dअगरf */
		/* Channel 1-3 */
		अगर (i < 3)
			index = 0;
		/* Channel 4-8 */
		अन्यथा अगर (i < 8)
			index = 0x11;
		/* Channel 9-14 */
		अन्यथा
			index = 1;

		tempval = hwinfo[EEPROM_TX_PWR_OFDM_DIFF + index] & 0xff;
		rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][i] =
				 (tempval & 0xF);
		rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_B][i] =
				 ((tempval >> 4) & 0xF);

		tempval = hwinfo[TX_PWR_SAFETY_CHK];
		rtlefuse->txpwr_safetyflag = (tempval & 0x01);
	पूर्ण

	rtlefuse->eeprom_regulatory = 0;
	अगर (rtlefuse->eeprom_version >= 2) अणु
		/* BIT(0)~2 */
		अगर (rtlefuse->eeprom_version >= 4)
			rtlefuse->eeprom_regulatory =
				 (hwinfo[EEPROM_REGULATORY] & 0x7);
		अन्यथा /* BIT(0) */
			rtlefuse->eeprom_regulatory =
				 (hwinfo[EEPROM_REGULATORY] & 0x1);
	पूर्ण
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"eeprom_regulatory = 0x%x\n", rtlefuse->eeprom_regulatory);

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

	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"TxPwrSafetyFlag = %d\n", rtlefuse->txpwr_safetyflag);

	/* Read RF-indication and Tx Power gain
	 * index dअगरf of legacy to HT OFDM rate. */
	tempval = hwinfo[EEPROM_RFIND_POWERDIFF] & 0xff;
	rtlefuse->eeprom_txघातerdअगरf = tempval;
	rtlefuse->legacy_ht_txघातerdअगरf =
		rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][0];

	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"TxPowerDiff = %#x\n", rtlefuse->eeprom_txघातerdअगरf);

	/* Get TSSI value क्रम each path. */
	usvalue = *(u16 *)&hwinfo[EEPROM_TSSI_A];
	rtlefuse->eeprom_tssi[RF90_PATH_A] = (u8)((usvalue & 0xff00) >> 8);
	usvalue = hwinfo[EEPROM_TSSI_B];
	rtlefuse->eeprom_tssi[RF90_PATH_B] = (u8)(usvalue & 0xff);

	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER, "TSSI_A = 0x%x, TSSI_B = 0x%x\n",
		rtlefuse->eeprom_tssi[RF90_PATH_A],
		rtlefuse->eeprom_tssi[RF90_PATH_B]);

	/* Read antenna tx घातer offset of B/C/D to A  from EEPROM */
	/* and पढ़ो ThermalMeter from EEPROM */
	tempval = hwinfo[EEPROM_THERMALMETER];
	rtlefuse->eeprom_thermalmeter = tempval;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"thermalmeter = 0x%x\n", rtlefuse->eeprom_thermalmeter);

	/* ThermalMeter, BIT(0)~3 क्रम RFIC1, BIT(4)~7 क्रम RFIC2 */
	rtlefuse->thermalmeter[0] = (rtlefuse->eeprom_thermalmeter & 0x1f);
	rtlefuse->tssi_13dbm = rtlefuse->eeprom_thermalmeter * 100;

	/* Read CrystalCap from EEPROM */
	tempval = hwinfo[EEPROM_CRYSTALCAP] >> 4;
	rtlefuse->eeprom_crystalcap = tempval;
	/* CrystalCap, BIT(12)~15 */
	rtlefuse->crystalcap = rtlefuse->eeprom_crystalcap;

	/* Read IC Version && Channel Plan */
	/* Version ID, Channel plan */
	rtlefuse->eeprom_channelplan = hwinfo[EEPROM_CHANNELPLAN];
	rtlefuse->txpwr_fromeprom = true;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"EEPROM ChannelPlan = 0x%4x\n", rtlefuse->eeprom_channelplan);

	/* Read Customer ID or Board Type!!! */
	tempval = hwinfo[EEPROM_BOARDTYPE];
	/* Change RF type definition */
	अगर (tempval == 0)
		rtlphy->rf_type = RF_2T2R;
	अन्यथा अगर (tempval == 1)
		rtlphy->rf_type = RF_1T2R;
	अन्यथा अगर (tempval == 2)
		rtlphy->rf_type = RF_1T2R;
	अन्यथा अगर (tempval == 3)
		rtlphy->rf_type = RF_1T1R;

	/* 1T2R but 1SS (1x1 receive combining) */
	rtlefuse->b1x1_recvcombine = false;
	अगर (rtlphy->rf_type == RF_1T2R) अणु
		tempval = rtl_पढ़ो_byte(rtlpriv, 0x07);
		अगर (!(tempval & BIT(0))) अणु
			rtlefuse->b1x1_recvcombine = true;
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"RF_TYPE=1T2R but only 1SS\n");
		पूर्ण
	पूर्ण
	rtlefuse->b1ss_support = rtlefuse->b1x1_recvcombine;
	rtlefuse->eeprom_oemid = *&hwinfo[EEPROM_CUSTOMID];

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "EEPROM Customer ID: 0x%2x\n",
		rtlefuse->eeprom_oemid);

	/* set channel paln to world wide 13 */
	rtlefuse->channel_plan = COUNTRY_CODE_WORLD_WIDE_13;
पूर्ण

व्योम rtl92se_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 पंचांगp_u1b = 0;

	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, EPROM_CMD);

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
		_rtl92se_पढ़ो_adapter_info(hw);
	पूर्ण अन्यथा अणु
		pr_err("Autoload ERR!!\n");
		rtlefuse->स्वतःload_failflag = true;
	पूर्ण
पूर्ण

अटल व्योम rtl92se_update_hal_rate_table(काष्ठा ieee80211_hw *hw,
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
	u16 लघुgi_rate = 0;
	u32 पंचांगp_ratr_value = 0;
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
	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_value = 0xfff;
	ratr_value |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
			sta->ht_cap.mcs.rx_mask[0] << 12);
	चयन (wirelessmode) अणु
	हाल WIRELESS_MODE_B:
		ratr_value &= 0x0000000D;
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
				अगर (curtxbw_40mhz)
					ratr_mask = 0x000ff015;
				अन्यथा
					ratr_mask = 0x000ff005;
			पूर्ण अन्यथा अणु
				अगर (curtxbw_40mhz)
					ratr_mask = 0x0f0ff015;
				अन्यथा
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

	अगर (rtlpriv->rtlhal.version >= VERSION_8192S_BCUT)
		ratr_value &= 0x0FFFFFFF;
	अन्यथा अगर (rtlpriv->rtlhal.version == VERSION_8192S_ACUT)
		ratr_value &= 0x0FFFFFF0;

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

		rtl_ग_लिखो_byte(rtlpriv, SG_RATE, लघुgi_rate);
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, ARFR0 + ratr_index * 4, ratr_value);
	अगर (ratr_value & 0xfffff000)
		rtl92s_phy_set_fw_cmd(hw, FW_CMD_RA_REFRESH_N);
	अन्यथा
		rtl92s_phy_set_fw_cmd(hw, FW_CMD_RA_REFRESH_BG);

	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG, "%x\n",
		rtl_पढ़ो_dword(rtlpriv, ARFR0));
पूर्ण

अटल व्योम rtl92se_update_hal_rate_mask(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_sta *sta,
					 u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u32 ratr_biपंचांगap;
	u8 ratr_index = 0;
	u8 curtxbw_40mhz = (sta->bandwidth >= IEEE80211_STA_RX_BW_40) ? 1 : 0;
	u8 curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
				1 : 0;
	u8 curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	क्रमागत wireless_mode wirelessmode = 0;
	bool लघुgi = false;
	u32 ratr_value = 0;
	u8 लघुgi_rate = 0;
	u32 mask = 0;
	u32 band = 0;
	bool bmulticast = false;
	u8 macid = 0;
	u8 mimo_ps = IEEE80211_SMPS_OFF;

	sta_entry = (काष्ठा rtl_sta_info *) sta->drv_priv;
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
		band |= WIRELESS_11B;
		ratr_index = RATR_INX_WIRELESS_B;
		अगर (ratr_biपंचांगap & 0x0000000c)
			ratr_biपंचांगap &= 0x0000000d;
		अन्यथा
			ratr_biपंचांगap &= 0x0000000f;
		अवरोध;
	हाल WIRELESS_MODE_G:
		band |= (WIRELESS_11G | WIRELESS_11B);
		ratr_index = RATR_INX_WIRELESS_GB;

		अगर (rssi_level == 1)
			ratr_biपंचांगap &= 0x00000f00;
		अन्यथा अगर (rssi_level == 2)
			ratr_biपंचांगap &= 0x00000ff0;
		अन्यथा
			ratr_biपंचांगap &= 0x00000ff5;
		अवरोध;
	हाल WIRELESS_MODE_A:
		band |= WIRELESS_11A;
		ratr_index = RATR_INX_WIRELESS_A;
		ratr_biपंचांगap &= 0x00000ff0;
		अवरोध;
	हाल WIRELESS_MODE_N_24G:
	हाल WIRELESS_MODE_N_5G:
		band |= (WIRELESS_11N | WIRELESS_11G | WIRELESS_11B);
		ratr_index = RATR_INX_WIRELESS_NGB;

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
				अगर (rssi_level == 1) अणु
						ratr_biपंचांगap &= 0x000f0000;
				पूर्ण अन्यथा अगर (rssi_level == 3) अणु
					ratr_biपंचांगap &= 0x000fc000;
				पूर्ण अन्यथा अगर (rssi_level == 5) अणु
						ratr_biपंचांगap &= 0x000ff000;
				पूर्ण अन्यथा अणु
					अगर (curtxbw_40mhz)
						ratr_biपंचांगap &= 0x000ff015;
					अन्यथा
						ratr_biपंचांगap &= 0x000ff005;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (rssi_level == 1) अणु
					ratr_biपंचांगap &= 0x0f8f0000;
				पूर्ण अन्यथा अगर (rssi_level == 3) अणु
					ratr_biपंचांगap &= 0x0f8fc000;
				पूर्ण अन्यथा अगर (rssi_level == 5) अणु
					ratr_biपंचांगap &= 0x0f8ff000;
				पूर्ण अन्यथा अणु
					अगर (curtxbw_40mhz)
						ratr_biपंचांगap &= 0x0f8ff015;
					अन्यथा
						ratr_biपंचांगap &= 0x0f8ff005;
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
		band |= (WIRELESS_11N | WIRELESS_11G | WIRELESS_11B);
		ratr_index = RATR_INX_WIRELESS_NGB;

		अगर (rtlphy->rf_type == RF_1T2R)
			ratr_biपंचांगap &= 0x000ff0ff;
		अन्यथा
			ratr_biपंचांगap &= 0x0f8ff0ff;
		अवरोध;
	पूर्ण
	sta_entry->ratr_index = ratr_index;

	अगर (rtlpriv->rtlhal.version >= VERSION_8192S_BCUT)
		ratr_biपंचांगap &= 0x0FFFFFFF;
	अन्यथा अगर (rtlpriv->rtlhal.version == VERSION_8192S_ACUT)
		ratr_biपंचांगap &= 0x0FFFFFF0;

	अगर (लघुgi) अणु
		ratr_biपंचांगap |= 0x10000000;
		/* Get MAX MCS available. */
		ratr_value = (ratr_biपंचांगap >> 12);
		क्रम (लघुgi_rate = 15; लघुgi_rate > 0; लघुgi_rate--) अणु
			अगर ((1 << लघुgi_rate) & ratr_value)
				अवरोध;
		पूर्ण

		लघुgi_rate = (लघुgi_rate << 12) | (लघुgi_rate << 8) |
			(लघुgi_rate << 4) | (लघुgi_rate);
		rtl_ग_लिखो_byte(rtlpriv, SG_RATE, लघुgi_rate);
	पूर्ण

	mask |= (bmulticast ? 1 : 0) << 9 | (macid & 0x1f) << 4 | (band & 0xf);

	rtl_dbg(rtlpriv, COMP_RATR, DBG_TRACE, "mask = %x, bitmap = %x\n",
		mask, ratr_biपंचांगap);
	rtl_ग_लिखो_dword(rtlpriv, 0x2c4, ratr_biपंचांगap);
	rtl_ग_लिखो_dword(rtlpriv, WFM5, (FW_RA_UPDATE_MASK | (mask << 8)));

	अगर (macid != 0)
		sta_entry->ratr_index = ratr_index;
पूर्ण

व्योम rtl92se_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->dm.useramask)
		rtl92se_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
	अन्यथा
		rtl92se_update_hal_rate_table(hw, sta);
पूर्ण

व्योम rtl92se_update_channel_access_setting(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 sअगरs_समयr;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME,
				      &mac->slot_समय);
	sअगरs_समयr = 0x0e0e;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SIFS, (u8 *)&sअगरs_समयr);

पूर्ण

/* this अगरunction is क्रम RFKILL, it's dअगरferent with winकरोws,
 * because UI will disable wireless when GPIO Radio Off.
 * And here we not check or Disable/Enable ASPM like winकरोws*/
bool rtl92se_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	क्रमागत rf_pwrstate rfpwr_toset /*, cur_rख_स्थितिe */;
	अचिन्हित दीर्घ flag = 0;
	bool actuallyset = false;
	bool turnonbyघातerकरोमुख्य = false;

	/* just 8191se can check gpio beक्रमe firstup, 92c/92d have fixed it */
	अगर (rtlpci->up_first_समय || rtlpci->being_init_adapter)
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

	/* cur_rख_स्थितिe = ppsc->rfpwr_state;*/

	/* because after _rtl92s_phy_set_rfhalt, all घातer
	 * बंदd, so we must खोलो some घातer क्रम GPIO check,
	 * or we will always check GPIO RFOFF here,
	 * And we should बंद घातer after GPIO check */
	अगर (RT_IN_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC)) अणु
		_rtl92se_घातer_करोमुख्य_init(hw);
		turnonbyघातerकरोमुख्य = true;
	पूर्ण

	rfpwr_toset = _rtl92se_rf_onoff_detect(hw);

	अगर ((ppsc->hwradiooff) && (rfpwr_toset == ERFON)) अणु
		rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
			"RFKILL-HW Radio ON, RF ON\n");

		rfpwr_toset = ERFON;
		ppsc->hwradiooff = false;
		actuallyset = true;
	पूर्ण अन्यथा अगर ((!ppsc->hwradiooff) && (rfpwr_toset == ERFOFF)) अणु
		rtl_dbg(rtlpriv, COMP_RF,
			DBG_DMESG, "RFKILL-HW Radio OFF, RF OFF\n");

		rfpwr_toset = ERFOFF;
		ppsc->hwradiooff = true;
		actuallyset = true;
	पूर्ण

	अगर (actuallyset) अणु
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);

	/* this not include अगरconfig wlan0 करोwn हाल */
	/* पूर्ण अन्यथा अगर (rfpwr_toset == ERFOFF || cur_rख_स्थितिe == ERFOFF) अणु */
	पूर्ण अन्यथा अणु
		/* because घातer_करोमुख्य_init may be happen when
		 * _rtl92s_phy_set_rfhalt, this will खोलो some घातers
		 * and cause current increasing about 40 mA क्रम ips,
		 * rfoff and अगरconfig करोwn, so we set
		 * _rtl92s_phy_set_rfhalt again here */
		अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC &&
			turnonbyघातerकरोमुख्य) अणु
			_rtl92s_phy_set_rfhalt(hw);
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
		पूर्ण

		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	पूर्ण

	*valid = 1;
	वापस !ppsc->hwradiooff;

पूर्ण

/* Is_wepkey just used क्रम WEP used as group & pairwise key
 * अगर pairwise is AES ang group is WEP Is_wepkey == false.*/
व्योम rtl92se_set_key(काष्ठा ieee80211_hw *hw, u32 key_index, u8 *p_macaddr,
	bool is_group, u8 enc_algo, bool is_wepkey, bool clear_all)
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
						enc_algo, CAM_CONFIG_NO_USEDK,
						rtlpriv->sec.key_buf[entry_id]);
				पूर्ण

				rtl_cam_add_one_entry(hw, macaddr, key_index,
					      entry_id, enc_algo,
					      CAM_CONFIG_NO_USEDK,
					      rtlpriv->sec.key_buf[entry_id]);
			पूर्ण

		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92se_suspend(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtlpci->up_first_समय = true;
पूर्ण

व्योम rtl92se_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 val;

	pci_पढ़ो_config_dword(rtlpci->pdev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(rtlpci->pdev, 0x40,
			val & 0xffff00ff);
पूर्ण
