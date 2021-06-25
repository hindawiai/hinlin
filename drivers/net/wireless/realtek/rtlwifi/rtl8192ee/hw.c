<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

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
#समावेश "../pwrseqcmd.h"
#समावेश "pwrseq.h"

#घोषणा LLT_CONFIG	5

अटल व्योम _rtl92ee_set_bcn_ctrl_reg(काष्ठा ieee80211_hw *hw,
				      u8 set_bits, u8 clear_bits)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpci->reg_bcn_ctrl_val |= set_bits;
	rtlpci->reg_bcn_ctrl_val &= ~clear_bits;

	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8)rtlpci->reg_bcn_ctrl_val);
पूर्ण

अटल व्योम _rtl92ee_stop_tx_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp;

	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp & (~BIT(6)));
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0x64);
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
	पंचांगp &= ~(BIT(0));
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, पंचांगp);
पूर्ण

अटल व्योम _rtl92ee_resume_tx_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp;

	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp | BIT(6));
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
	पंचांगp |= BIT(0);
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, पंचांगp);
पूर्ण

अटल व्योम _rtl92ee_enable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl92ee_set_bcn_ctrl_reg(hw, 0, BIT(1));
पूर्ण

अटल व्योम _rtl92ee_disable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl92ee_set_bcn_ctrl_reg(hw, BIT(1), 0);
पूर्ण

अटल व्योम _rtl92ee_set_fw_घड़ी_on(काष्ठा ieee80211_hw *hw,
				     u8 rpwm_val, bool b_need_turn_off_ckk)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool b_support_remote_wake_up;
	u32 count = 0, isr_regaddr, content;
	bool b_schedule_समयr = b_need_turn_off_ckk;

	rtlpriv->cfg->ops->get_hw_reg(hw, HAL_DEF_WOWLAN,
				      (u8 *)(&b_support_remote_wake_up));

	अगर (!rtlhal->fw_पढ़ोy)
		वापस;
	अगर (!rtlpriv->psc.fw_current_inpsmode)
		वापस;

	जबतक (1) अणु
		spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
		अगर (rtlhal->fw_clk_change_in_progress) अणु
			जबतक (rtlhal->fw_clk_change_in_progress) अणु
				spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
				count++;
				udelay(100);
				अगर (count > 1000)
					वापस;
				spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
			पूर्ण
			spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
		पूर्ण अन्यथा अणु
			rtlhal->fw_clk_change_in_progress = false;
			spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (IS_IN_LOW_POWER_STATE_92E(rtlhal->fw_ps_state)) अणु
		rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_SET_RPWM,
					      (u8 *)(&rpwm_val));
		अगर (FW_PS_IS_ACK(rpwm_val)) अणु
			isr_regaddr = REG_HISR;
			content = rtl_पढ़ो_dword(rtlpriv, isr_regaddr);
			जबतक (!(content & IMR_CPWM) && (count < 500)) अणु
				udelay(50);
				count++;
				content = rtl_पढ़ो_dword(rtlpriv, isr_regaddr);
			पूर्ण

			अगर (content & IMR_CPWM) अणु
				rtl_ग_लिखो_word(rtlpriv, isr_regaddr, 0x0100);
				rtlhal->fw_ps_state = FW_PS_STATE_RF_ON_92E;
				rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
					"Receive CPWM INT!!! PSState = %X\n",
					rtlhal->fw_ps_state);
			पूर्ण
		पूर्ण

		spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
		rtlhal->fw_clk_change_in_progress = false;
		spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
		अगर (b_schedule_समयr) अणु
			mod_समयr(&rtlpriv->works.fw_घड़ीoff_समयr,
				  jअगरfies + MSECS(10));
		पूर्ण
	पूर्ण अन्यथा  अणु
		spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
		rtlhal->fw_clk_change_in_progress = false;
		spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_set_fw_घड़ी_off(काष्ठा ieee80211_hw *hw, u8 rpwm_val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring;
	क्रमागत rf_pwrstate rtstate;
	bool b_schedule_समयr = false;
	u8 queue;

	अगर (!rtlhal->fw_पढ़ोy)
		वापस;
	अगर (!rtlpriv->psc.fw_current_inpsmode)
		वापस;
	अगर (!rtlhal->allow_sw_to_change_hwclc)
		वापस;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RF_STATE, (u8 *)(&rtstate));
	अगर (rtstate == ERFOFF || rtlpriv->psc.inactive_pwrstate == ERFOFF)
		वापस;

	क्रम (queue = 0; queue < RTL_PCI_MAX_TX_QUEUE_COUNT; queue++) अणु
		ring = &rtlpci->tx_ring[queue];
		अगर (skb_queue_len(&ring->queue)) अणु
			b_schedule_समयr = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (b_schedule_समयr) अणु
		mod_समयr(&rtlpriv->works.fw_घड़ीoff_समयr,
			  jअगरfies + MSECS(10));
		वापस;
	पूर्ण

	अगर (FW_PS_STATE(rtlhal->fw_ps_state) != FW_PS_STATE_RF_OFF_LOW_PWR) अणु
		spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
		अगर (!rtlhal->fw_clk_change_in_progress) अणु
			rtlhal->fw_clk_change_in_progress = true;
			spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
			rtlhal->fw_ps_state = FW_PS_STATE(rpwm_val);
			rtl_ग_लिखो_word(rtlpriv, REG_HISR, 0x0100);
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
						      (u8 *)(&rpwm_val));
			spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
			rtlhal->fw_clk_change_in_progress = false;
			spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
		पूर्ण अन्यथा अणु
			spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
			mod_समयr(&rtlpriv->works.fw_घड़ीoff_समयr,
				  jअगरfies + MSECS(10));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_set_fw_ps_rf_on(काष्ठा ieee80211_hw *hw)
अणु
	u8 rpwm_val = 0;

	rpwm_val |= (FW_PS_STATE_RF_OFF_92E | FW_PS_ACK);
	_rtl92ee_set_fw_घड़ी_on(hw, rpwm_val, true);
पूर्ण

अटल व्योम _rtl92ee_set_fw_ps_rf_off_low_घातer(काष्ठा ieee80211_hw *hw)
अणु
	u8 rpwm_val = 0;

	rpwm_val |= FW_PS_STATE_RF_OFF_LOW_PWR;
	_rtl92ee_set_fw_घड़ी_off(hw, rpwm_val);
पूर्ण

व्योम rtl92ee_fw_clk_off_समयr_callback(अचिन्हित दीर्घ data)
अणु
	काष्ठा ieee80211_hw *hw = (काष्ठा ieee80211_hw *)data;

	_rtl92ee_set_fw_ps_rf_off_low_घातer(hw);
पूर्ण

अटल व्योम _rtl92ee_fwlps_leave(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inps = false;
	u8 rpwm_val = 0, fw_pwrmode = FW_PS_ACTIVE_MODE;

	अगर (ppsc->low_घातer_enable) अणु
		rpwm_val = (FW_PS_STATE_ALL_ON_92E | FW_PS_ACK);/* RF on */
		_rtl92ee_set_fw_घड़ी_on(hw, rpwm_val, false);
		rtlhal->allow_sw_to_change_hwclc = false;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      (u8 *)(&fw_pwrmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
	पूर्ण अन्यथा अणु
		rpwm_val = FW_PS_STATE_ALL_ON_92E;	/* RF on */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
					      (u8 *)(&rpwm_val));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      (u8 *)(&fw_pwrmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_fwlps_enter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inps = true;
	u8 rpwm_val;

	अगर (ppsc->low_घातer_enable) अणु
		rpwm_val = FW_PS_STATE_RF_OFF_LOW_PWR;	/* RF off */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      (u8 *)(&ppsc->fwctrl_psmode));
		rtlhal->allow_sw_to_change_hwclc = true;
		_rtl92ee_set_fw_घड़ी_off(hw, rpwm_val);
	पूर्ण अन्यथा अणु
		rpwm_val = FW_PS_STATE_RF_OFF_92E;	/* RF off */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      (u8 *)(&ppsc->fwctrl_psmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
					      (u8 *)(&rpwm_val));
	पूर्ण
पूर्ण

व्योम rtl92ee_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
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

			rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RF_STATE,
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
		पूर्ण
		अवरोध;
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
		पूर्ण
		अवरोध;
	हाल HAL_DEF_WOWLAN:
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_DMESG,
			"switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_करोwnload_rsvd_page(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp_regcr, पंचांगp_reg422;
	u8 bcnvalid_reg, txbc_reg;
	u8 count = 0, dlbcn_count = 0;
	bool b_recover = false;

	/*Set REG_CR bit 8. DMA beacon by SW.*/
	पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, पंचांगp_regcr | BIT(0));

	/* Disable Hw protection क्रम a समय which revserd क्रम Hw sending beacon.
	 * Fix करोwnload reserved page packet fail
	 * that access collision with the protection समय.
	 * 2010.05.11. Added by tynli.
	 */
	_rtl92ee_set_bcn_ctrl_reg(hw, 0, BIT(3));
	_rtl92ee_set_bcn_ctrl_reg(hw, BIT(4), 0);

	/* Set FWHW_TXQ_CTRL 0x422[6]=0 to
	 * tell Hw the packet is not a real beacon frame.
	 */
	पंचांगp_reg422 = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp_reg422 & (~BIT(6)));

	अगर (पंचांगp_reg422 & BIT(6))
		b_recover = true;

	करो अणु
		/* Clear beacon valid check bit */
		bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv, REG_DWBCN0_CTRL + 2);
		rtl_ग_लिखो_byte(rtlpriv, REG_DWBCN0_CTRL + 2,
			       bcnvalid_reg | BIT(0));

		/* करोwnload rsvd page */
		rtl92ee_set_fw_rsvdpagepkt(hw, false);

		txbc_reg = rtl_पढ़ो_byte(rtlpriv, REG_MGQ_TXBD_NUM + 3);
		count = 0;
		जबतक ((txbc_reg & BIT(4)) && count < 20) अणु
			count++;
			udelay(10);
			txbc_reg = rtl_पढ़ो_byte(rtlpriv, REG_MGQ_TXBD_NUM + 3);
		पूर्ण
		rtl_ग_लिखो_byte(rtlpriv, REG_MGQ_TXBD_NUM + 3,
			       txbc_reg | BIT(4));

		/* check rsvd page करोwnload OK. */
		bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv, REG_DWBCN0_CTRL + 2);
		count = 0;
		जबतक (!(bcnvalid_reg & BIT(0)) && count < 20) अणु
			count++;
			udelay(50);
			bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv,
						     REG_DWBCN0_CTRL + 2);
		पूर्ण

		अगर (bcnvalid_reg & BIT(0))
			rtl_ग_लिखो_byte(rtlpriv, REG_DWBCN0_CTRL + 2, BIT(0));

		dlbcn_count++;
	पूर्ण जबतक (!(bcnvalid_reg & BIT(0)) && dlbcn_count < 5);

	अगर (!(bcnvalid_reg & BIT(0)))
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Download RSVD page failed!\n");

	/* Enable Bcn */
	_rtl92ee_set_bcn_ctrl_reg(hw, BIT(3), 0);
	_rtl92ee_set_bcn_ctrl_reg(hw, 0, BIT(4));

	अगर (b_recover)
		rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp_reg422);

	पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, पंचांगp_regcr & (~BIT(0)));
पूर्ण

व्योम rtl92ee_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *efuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 idx;

	चयन (variable) अणु
	हाल HW_VAR_ETHER_ADDR:
		क्रम (idx = 0; idx < ETH_ALEN; idx++)
			rtl_ग_लिखो_byte(rtlpriv, (REG_MACID + idx), val[idx]);
		अवरोध;
	हाल HW_VAR_BASIC_RATE:अणु
		u16 b_rate_cfg = ((u16 *)val)[0];

		b_rate_cfg = b_rate_cfg & 0x15f;
		b_rate_cfg |= 0x01;
		b_rate_cfg = (b_rate_cfg | 0xd) & (~BIT(1));
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR, b_rate_cfg & 0xff);
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 1, (b_rate_cfg >> 8) & 0xff);
		अवरोध; पूर्ण
	हाल HW_VAR_BSSID:
		क्रम (idx = 0; idx < ETH_ALEN; idx++)
			rtl_ग_लिखो_byte(rtlpriv, (REG_BSSID + idx), val[idx]);
		अवरोध;
	हाल HW_VAR_SIFS:
		rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_CTX + 1, val[0]);
		rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_TRX + 1, val[1]);

		rtl_ग_लिखो_byte(rtlpriv, REG_SPEC_SIFS + 1, val[0]);
		rtl_ग_लिखो_byte(rtlpriv, REG_MAC_SPEC_SIFS + 1, val[0]);

		अगर (!mac->ht_enable)
			rtl_ग_लिखो_word(rtlpriv, REG_RESP_SIFS_OFDM, 0x0e0e);
		अन्यथा
			rtl_ग_लिखो_word(rtlpriv, REG_RESP_SIFS_OFDM,
				       *((u16 *)val));
		अवरोध;
	हाल HW_VAR_SLOT_TIME:अणु
		u8 e_aci;

		rtl_dbg(rtlpriv, COMP_MLME, DBG_TRACE,
			"HW_VAR_SLOT_TIME %x\n", val[0]);

		rtl_ग_लिखो_byte(rtlpriv, REG_SLOT, val[0]);

		क्रम (e_aci = 0; e_aci < AC_MAX; e_aci++) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      (u8 *)(&e_aci));
		पूर्ण
		अवरोध; पूर्ण
	हाल HW_VAR_ACK_PREAMBLE:अणु
		u8 reg_पंचांगp;
		u8 लघु_preamble = (bool)(*(u8 *)val);

		reg_पंचांगp = (rtlpriv->mac80211.cur_40_prime_sc) << 5;
		अगर (लघु_preamble)
			reg_पंचांगp |= 0x80;
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 2, reg_पंचांगp);
		rtlpriv->mac80211.लघु_preamble = लघु_preamble;
		पूर्ण
		अवरोध;
	हाल HW_VAR_WPA_CONFIG:
		rtl_ग_लिखो_byte(rtlpriv, REG_SECCFG, *((u8 *)val));
		अवरोध;
	हाल HW_VAR_AMPDU_FACTOR:अणु
		u8 regtoset_normal[4] = अणु 0x41, 0xa8, 0x72, 0xb9 पूर्ण;
		u8 fac;
		u8 *reg = शून्य;
		u8 i = 0;

		reg = regtoset_normal;

		fac = *((u8 *)val);
		अगर (fac <= 3) अणु
			fac = (1 << (fac + 2));
			अगर (fac > 0xf)
				fac = 0xf;
			क्रम (i = 0; i < 4; i++) अणु
				अगर ((reg[i] & 0xf0) > (fac << 4))
					reg[i] = (reg[i] & 0x0f) |
						(fac << 4);
				अगर ((reg[i] & 0x0f) > fac)
					reg[i] = (reg[i] & 0xf0) | fac;
				rtl_ग_लिखो_byte(rtlpriv,
					       (REG_AGGLEN_LMT + i),
					       reg[i]);
			पूर्ण
			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"Set HW_VAR_AMPDU_FACTOR:%#x\n", fac);
		पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_AC_PARAM:अणु
		u8 e_aci = *((u8 *)val);

		अगर (rtlpci->acm_method != EACMWAY2_SW)
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ACM_CTRL,
						      (u8 *)(&e_aci));
		पूर्ण
		अवरोध;
	हाल HW_VAR_ACM_CTRL:अणु
		u8 e_aci = *((u8 *)val);
		जोड़ aci_aअगरsn *aअगरs = (जोड़ aci_aअगरsn *)(&mac->ac[0].aअगरs);

		u8 acm = aअगरs->f.acm;
		u8 acm_ctrl = rtl_पढ़ो_byte(rtlpriv, REG_ACMHWCTRL);

		acm_ctrl = acm_ctrl | ((rtlpci->acm_method == 2) ? 0x0 : 0x1);

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
				rtl_dbg(rtlpriv, COMP_ERR, DBG_DMESG,
					"switch case %#x not processed\n",
					e_aci);
				अवरोध;
			पूर्ण
		पूर्ण

		rtl_dbg(rtlpriv, COMP_QOS, DBG_TRACE,
			"SetHwReg8190pci(): [HW_VAR_ACM_CTRL] Write 0x%X\n",
			acm_ctrl);
		rtl_ग_लिखो_byte(rtlpriv, REG_ACMHWCTRL, acm_ctrl);
		पूर्ण
		अवरोध;
	हाल HW_VAR_RCR:अणु
		rtl_ग_लिखो_dword(rtlpriv, REG_RCR, ((u32 *)(val))[0]);
		rtlpci->receive_config = ((u32 *)(val))[0];
		पूर्ण
		अवरोध;
	हाल HW_VAR_RETRY_LIMIT:अणु
		u8 retry_limit = ((u8 *)(val))[0];

		rtl_ग_लिखो_word(rtlpriv, REG_RETRY_LIMIT,
			       retry_limit << RETRY_LIMIT_SHORT_SHIFT |
			       retry_limit << RETRY_LIMIT_LONG_SHIFT);
		पूर्ण
		अवरोध;
	हाल HW_VAR_DUAL_TSF_RST:
		rtl_ग_लिखो_byte(rtlpriv, REG_DUAL_TSF_RST, (BIT(0) | BIT(1)));
		अवरोध;
	हाल HW_VAR_EFUSE_BYTES:
		efuse->efuse_usedbytes = *((u16 *)val);
		अवरोध;
	हाल HW_VAR_EFUSE_USAGE:
		efuse->efuse_usedpercentage = *((u8 *)val);
		अवरोध;
	हाल HW_VAR_IO_CMD:
		rtl92ee_phy_set_io_cmd(hw, (*(क्रमागत io_type *)val));
		अवरोध;
	हाल HW_VAR_SET_RPWM:अणु
		u8 rpwm_val;

		rpwm_val = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_HRPWM);
		udelay(1);

		अगर (rpwm_val & BIT(7)) अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_HRPWM, (*(u8 *)val));
		पूर्ण अन्यथा अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_HRPWM,
				       ((*(u8 *)val) | BIT(7)));
		पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_H2C_FW_PWRMODE:
		rtl92ee_set_fw_pwrmode_cmd(hw, (*(u8 *)val));
		अवरोध;
	हाल HW_VAR_FW_PSMODE_STATUS:
		ppsc->fw_current_inpsmode = *((bool *)val);
		अवरोध;
	हाल HW_VAR_RESUME_CLK_ON:
		_rtl92ee_set_fw_ps_rf_on(hw);
		अवरोध;
	हाल HW_VAR_FW_LPS_ACTION:अणु
		bool b_enter_fwlps = *((bool *)val);

		अगर (b_enter_fwlps)
			_rtl92ee_fwlps_enter(hw);
		अन्यथा
			_rtl92ee_fwlps_leave(hw);
		पूर्ण
		अवरोध;
	हाल HW_VAR_H2C_FW_JOINBSSRPT:अणु
		u8 mstatus = (*(u8 *)val);

		अगर (mstatus == RT_MEDIA_CONNECT) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AID, शून्य);
			_rtl92ee_करोwnload_rsvd_page(hw);
		पूर्ण
		rtl92ee_set_fw_media_status_rpt_cmd(hw, mstatus);
		पूर्ण
		अवरोध;
	हाल HW_VAR_H2C_FW_P2P_PS_OFFLOAD:
		rtl92ee_set_p2p_ps_offload_cmd(hw, (*(u8 *)val));
		अवरोध;
	हाल HW_VAR_AID:अणु
		u16 u2bपंचांगp;

		u2bपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_BCN_PSR_RPT);
		u2bपंचांगp &= 0xC000;
		rtl_ग_लिखो_word(rtlpriv, REG_BCN_PSR_RPT,
			       (u2bपंचांगp | mac->assoc_id));
		पूर्ण
		अवरोध;
	हाल HW_VAR_CORRECT_TSF:अणु
		u8 btype_ibss = ((u8 *)(val))[0];

		अगर (btype_ibss)
			_rtl92ee_stop_tx_beacon(hw);

		_rtl92ee_set_bcn_ctrl_reg(hw, 0, BIT(3));

		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR,
				(u32)(mac->tsf & 0xffffffff));
		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR + 4,
				(u32)((mac->tsf >> 32) & 0xffffffff));

		_rtl92ee_set_bcn_ctrl_reg(hw, BIT(3), 0);

		अगर (btype_ibss)
			_rtl92ee_resume_tx_beacon(hw);
		पूर्ण
		अवरोध;
	हाल HW_VAR_KEEP_ALIVE: अणु
		u8 array[2];

		array[0] = 0xff;
		array[1] = *((u8 *)val);
		rtl92ee_fill_h2c_cmd(hw, H2C_92E_KEEP_ALIVE_CTRL, 2, array);
		पूर्ण
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_DMESG,
			"switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool _rtl92ee_llt_table_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 txpktbuf_bndy;
	u8 u8पंचांगp, testcnt = 0;

	txpktbuf_bndy = 0xF7;

	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, 0x80E60808);

	rtl_ग_लिखो_byte(rtlpriv, REG_TRXFF_BNDY, txpktbuf_bndy);
	rtl_ग_लिखो_word(rtlpriv, REG_TRXFF_BNDY + 2, 0x3d00 - 1);

	rtl_ग_लिखो_byte(rtlpriv, REG_DWBCN0_CTRL + 1, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_DWBCN1_CTRL + 1, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, REG_BCNQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_BCNQ1_BDNY, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, REG_MGQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, 0x45D, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, REG_PBP, 0x31);
	rtl_ग_लिखो_byte(rtlpriv, REG_RX_DRVINFO_SZ, 0x4);

	u8पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_AUTO_LLT + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_AUTO_LLT + 2, u8पंचांगp | BIT(0));

	जबतक (u8पंचांगp & BIT(0)) अणु
		u8पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_AUTO_LLT + 2);
		udelay(10);
		testcnt++;
		अगर (testcnt > 10)
			अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम _rtl92ee_gen_refresh_led_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;

	अगर (rtlpriv->rtlhal.up_first_समय)
		वापस;

	अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
		rtl92ee_sw_led_on(hw, pled0);
	अन्यथा अगर (ppsc->rfoff_reason == RF_CHANGE_BY_INIT)
		rtl92ee_sw_led_on(hw, pled0);
	अन्यथा
		rtl92ee_sw_led_off(hw, pled0);
पूर्ण

अटल bool _rtl92ee_init_mac(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	u8 byteपंचांगp;
	u16 wordपंचांगp;
	u32 dwordपंचांगp;

	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0);

	dwordपंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG1);
	अगर (dwordपंचांगp & BIT(24)) अणु
		rtl_ग_लिखो_byte(rtlpriv, 0x7c, 0xc3);
	पूर्ण अन्यथा अणु
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x16);
		rtl_ग_लिखो_byte(rtlpriv, 0x16, byteपंचांगp | BIT(4) | BIT(6));
		rtl_ग_लिखो_byte(rtlpriv, 0x7c, 0x83);
	पूर्ण
	/* 1. 40Mhz crystal source*/
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_AFE_CTRL2);
	byteपंचांगp &= 0xfb;
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_CTRL2, byteपंचांगp);

	dwordपंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_AFE_CTRL4);
	dwordपंचांगp &= 0xfffffc7f;
	rtl_ग_लिखो_dword(rtlpriv, REG_AFE_CTRL4, dwordपंचांगp);

	/* 2. 92E AFE parameter
	 * MP chip then check version
	 */
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_AFE_CTRL2);
	byteपंचांगp &= 0xbf;
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_CTRL2, byteपंचांगp);

	dwordपंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_AFE_CTRL4);
	dwordपंचांगp &= 0xffdfffff;
	rtl_ग_लिखो_dword(rtlpriv, REG_AFE_CTRL4, dwordपंचांगp);

	/* HW Power on sequence */
	अगर (!rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
				      PWR_INTF_PCI_MSK,
				      RTL8192E_NIC_ENABLE_FLOW)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"init MAC Fail as rtl_hal_pwrseqcmdparsing\n");
		वापस false;
	पूर्ण

	/* Release MAC IO रेजिस्टर reset */
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_CR);
	byteपंचांगp = 0xff;
	rtl_ग_लिखो_byte(rtlpriv, REG_CR, byteपंचांगp);
	mdelay(2);
	byteपंचांगp = 0x7f;
	rtl_ग_लिखो_byte(rtlpriv, REG_HWSEQ_CTRL, byteपंचांगp);
	mdelay(2);

	/* Add क्रम wakeup online */
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CLKR);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_CLKR, byteपंचांगp | BIT(3));
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_MUXCFG + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG + 1, byteपंचांगp & (~BIT(4)));
	/* Release MAC IO रेजिस्टर reset */
	rtl_ग_लिखो_word(rtlpriv, REG_CR, 0x2ff);

	अगर (!rtlhal->mac_func_enable) अणु
		अगर (!_rtl92ee_llt_table_init(hw)) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"LLT table init fail\n");
			वापस false;
		पूर्ण
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, REG_HISR, 0xffffffff);
	rtl_ग_लिखो_dword(rtlpriv, REG_HISRE, 0xffffffff);

	wordपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_TRXDMA_CTRL);
	wordपंचांगp &= 0xf;
	wordपंचांगp |= 0xF5B1;
	rtl_ग_लिखो_word(rtlpriv, REG_TRXDMA_CTRL, wordपंचांगp);
	/* Reported Tx status from HW क्रम rate adaptive.*/
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 1, 0x1F);

	/* Set RCR रेजिस्टर */
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);
	rtl_ग_लिखो_word(rtlpriv, REG_RXFLTMAP2, 0xffff);

	/* Set TCR रेजिस्टर */
	rtl_ग_लिखो_dword(rtlpriv, REG_TCR, rtlpci->transmit_config);

	/* Set TX/RX descriptor physical address -- HI part */
	अगर (!rtlpriv->cfg->mod_params->dma64)
		जाओ dma64_end;

	rtl_ग_लिखो_dword(rtlpriv, REG_BCNQ_DESA + 4,
			((u64)rtlpci->tx_ring[BEACON_QUEUE].buffer_desc_dma) >>
				32);
	rtl_ग_लिखो_dword(rtlpriv, REG_MGQ_DESA + 4,
			(u64)rtlpci->tx_ring[MGNT_QUEUE].buffer_desc_dma >> 32);
	rtl_ग_लिखो_dword(rtlpriv, REG_VOQ_DESA + 4,
			(u64)rtlpci->tx_ring[VO_QUEUE].buffer_desc_dma >> 32);
	rtl_ग_लिखो_dword(rtlpriv, REG_VIQ_DESA + 4,
			(u64)rtlpci->tx_ring[VI_QUEUE].buffer_desc_dma >> 32);
	rtl_ग_लिखो_dword(rtlpriv, REG_BEQ_DESA + 4,
			(u64)rtlpci->tx_ring[BE_QUEUE].buffer_desc_dma >> 32);
	rtl_ग_लिखो_dword(rtlpriv, REG_BKQ_DESA + 4,
			(u64)rtlpci->tx_ring[BK_QUEUE].buffer_desc_dma >> 32);
	rtl_ग_लिखो_dword(rtlpriv, REG_HQ0_DESA + 4,
			(u64)rtlpci->tx_ring[HIGH_QUEUE].buffer_desc_dma >> 32);

	rtl_ग_लिखो_dword(rtlpriv, REG_RX_DESA + 4,
			(u64)rtlpci->rx_ring[RX_MPDU_QUEUE].dma >> 32);

dma64_end:

	/* Set TX/RX descriptor physical address(from OS API). */
	rtl_ग_लिखो_dword(rtlpriv, REG_BCNQ_DESA,
			((u64)rtlpci->tx_ring[BEACON_QUEUE].buffer_desc_dma) &
			DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_MGQ_DESA,
			(u64)rtlpci->tx_ring[MGNT_QUEUE].buffer_desc_dma &
			DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_VOQ_DESA,
			(u64)rtlpci->tx_ring[VO_QUEUE].buffer_desc_dma &
			DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_VIQ_DESA,
			(u64)rtlpci->tx_ring[VI_QUEUE].buffer_desc_dma &
			DMA_BIT_MASK(32));

	rtl_ग_लिखो_dword(rtlpriv, REG_BEQ_DESA,
			(u64)rtlpci->tx_ring[BE_QUEUE].buffer_desc_dma &
			DMA_BIT_MASK(32));

	dwordपंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_BEQ_DESA);

	rtl_ग_लिखो_dword(rtlpriv, REG_BKQ_DESA,
			(u64)rtlpci->tx_ring[BK_QUEUE].buffer_desc_dma &
			DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_HQ0_DESA,
			(u64)rtlpci->tx_ring[HIGH_QUEUE].buffer_desc_dma &
			DMA_BIT_MASK(32));

	rtl_ग_लिखो_dword(rtlpriv, REG_RX_DESA,
			(u64)rtlpci->rx_ring[RX_MPDU_QUEUE].dma &
			DMA_BIT_MASK(32));

	/* अगर we want to support 64 bit DMA, we should set it here,
	 * but now we करो not support 64 bit DMA
	 */

	rtl_ग_लिखो_dword(rtlpriv, REG_TSFTIMER_HCI, 0x3fffffff);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_CTRL_REG + 3);
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 3, byteपंचांगp | 0xF7);

	rtl_ग_लिखो_dword(rtlpriv, REG_INT_MIG, 0);

	rtl_ग_लिखो_dword(rtlpriv, REG_MCUTST_1, 0x0);

	rtl_ग_लिखो_word(rtlpriv, REG_MGQ_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_VOQ_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_VIQ_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_BEQ_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_VOQ_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_BKQ_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_HI0Q_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_HI1Q_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_HI2Q_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_HI3Q_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_HI4Q_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_HI5Q_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_HI6Q_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	rtl_ग_लिखो_word(rtlpriv, REG_HI7Q_TXBD_NUM,
		       TX_DESC_NUM_92E | ((RTL8192EE_SEG_NUM << 12) & 0x3000));
	/*Rx*/
	rtl_ग_लिखो_word(rtlpriv, REG_RX_RXBD_NUM,
		       RX_DESC_NUM_92E |
		       ((RTL8192EE_SEG_NUM << 13) & 0x6000) | 0x8000);

	rtl_ग_लिखो_dword(rtlpriv, REG_TSFTIMER_HCI, 0XFFFFFFFF);

	_rtl92ee_gen_refresh_led_state(hw);
	वापस true;
पूर्ण

अटल व्योम _rtl92ee_hw_configure(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 reg_rrsr;

	reg_rrsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
	/* Init value क्रम RRSR. */
	rtl_ग_लिखो_dword(rtlpriv, REG_RRSR, reg_rrsr);

	/* ARFB table 9 क्रम 11ac 5G 2SS */
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR0, 0x00000010);
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR0 + 4, 0x3e0ff000);

	/* ARFB table 10 क्रम 11ac 5G 1SS */
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR1, 0x00000010);
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR1 + 4, 0x000ff000);

	/* Set SLOT समय */
	rtl_ग_लिखो_byte(rtlpriv, REG_SLOT, 0x09);

	/* CF-End setting. */
	rtl_ग_लिखो_word(rtlpriv, REG_FWHW_TXQ_CTRL, 0x1F80);

	/* Set retry limit */
	rtl_ग_लिखो_word(rtlpriv, REG_RETRY_LIMIT, 0x0707);

	/* BAR settings */
	rtl_ग_लिखो_dword(rtlpriv, REG_BAR_MODE_CTRL, 0x0201ffff);

	/* Set Data / Response स्वतः rate fallack retry count */
	rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC, 0x01000000);
	rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4, 0x07060504);
	rtl_ग_लिखो_dword(rtlpriv, REG_RARFRC, 0x01000000);
	rtl_ग_लिखो_dword(rtlpriv, REG_RARFRC + 4, 0x07060504);

	/* Beacon related, क्रम rate adaptive */
	rtl_ग_लिखो_byte(rtlpriv, REG_ATIMWND, 0x2);
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_MAX_ERR, 0xff);

	rtlpci->reg_bcn_ctrl_val = 0x1d;
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, rtlpci->reg_bcn_ctrl_val);

	/* Marked out by Bruce, 2010-09-09.
	 * This रेजिस्टर is configured क्रम the 2nd Beacon (multiple BSSID).
	 * We shall disable this रेजिस्टर अगर we only support 1 BSSID.
	 * vivi guess 92d also need this, also 92d now करोesnot set this reg
	 */
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL_1, 0);

	/* TBTT prohibit hold समय. Suggested by designer TimChen. */
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff); /* 8 ms */

	rtl_ग_लिखो_byte(rtlpriv, REG_PIFS, 0);
	rtl_ग_लिखो_byte(rtlpriv, REG_AGGR_BREAK_TIME, 0x16);

	rtl_ग_लिखो_word(rtlpriv, REG_NAV_PROT_LEN, 0x0040);
	rtl_ग_लिखो_word(rtlpriv, REG_PROT_MODE_CTRL, 0x08ff);

	/* For Rx TP. Suggested by SD1 Riअक्षरd. Added by tynli. 2010.04.12.*/
	rtl_ग_लिखो_dword(rtlpriv, REG_FAST_EDCA_CTRL, 0x03086666);

	/* ACKTO क्रम IOT issue. */
	rtl_ग_लिखो_byte(rtlpriv, REG_ACKTO, 0x40);

	/* Set Spec SIFS (used in NAV) */
	rtl_ग_लिखो_word(rtlpriv, REG_SPEC_SIFS, 0x100a);
	rtl_ग_लिखो_word(rtlpriv, REG_MAC_SPEC_SIFS, 0x100a);

	/* Set SIFS क्रम CCK */
	rtl_ग_लिखो_word(rtlpriv, REG_SIFS_CTX, 0x100a);

	/* Set SIFS क्रम OFDM */
	rtl_ग_लिखो_word(rtlpriv, REG_SIFS_TRX, 0x100a);

	/* Note Data sheet करोn't define */
	rtl_ग_लिखो_byte(rtlpriv, 0x4C7, 0x80);

	rtl_ग_लिखो_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x20);

	rtl_ग_लिखो_word(rtlpriv, REG_MAX_AGGR_NUM, 0x1717);

	/* Set Multicast Address. 2009.01.07. by tynli. */
	rtl_ग_लिखो_dword(rtlpriv, REG_MAR, 0xffffffff);
	rtl_ग_लिखो_dword(rtlpriv, REG_MAR + 4, 0xffffffff);
पूर्ण

अटल व्योम _rtl92ee_enable_aspm_back_करोor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u32 पंचांगp32 = 0, count = 0;
	u8 पंचांगp8 = 0;

	rtl_ग_लिखो_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0x78);
	rtl_ग_लिखो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x2);
	पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	जबतक (पंचांगp8 && count < 20) अणु
		udelay(10);
		पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	पूर्ण

	अगर (0 == पंचांगp8) अणु
		पंचांगp32 = rtl_पढ़ो_dword(rtlpriv, REG_BACKDOOR_DBI_RDATA);
		अगर ((पंचांगp32 & 0xff00) != 0x2000) अणु
			पंचांगp32 &= 0xffff00ff;
			rtl_ग_लिखो_dword(rtlpriv, REG_BACKDOOR_DBI_WDATA,
					पंचांगp32 | BIT(13));
			rtl_ग_लिखो_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0xf078);
			rtl_ग_लिखो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x1);

			पंचांगp8 = rtl_पढ़ो_byte(rtlpriv,
					     REG_BACKDOOR_DBI_DATA + 2);
			count = 0;
			जबतक (पंचांगp8 && count < 20) अणु
				udelay(10);
				पंचांगp8 = rtl_पढ़ो_byte(rtlpriv,
						     REG_BACKDOOR_DBI_DATA + 2);
				count++;
			पूर्ण
		पूर्ण
	पूर्ण

	rtl_ग_लिखो_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0x70c);
	rtl_ग_लिखो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x2);
	पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	जबतक (पंचांगp8 && count < 20) अणु
		udelay(10);
		पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	पूर्ण
	अगर (0 == पंचांगp8) अणु
		पंचांगp32 = rtl_पढ़ो_dword(rtlpriv, REG_BACKDOOR_DBI_RDATA);
		rtl_ग_लिखो_dword(rtlpriv, REG_BACKDOOR_DBI_WDATA,
				पंचांगp32 | BIT(31));
		rtl_ग_लिखो_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0xf70c);
		rtl_ग_लिखो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x1);
	पूर्ण

	पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	जबतक (पंचांगp8 && count < 20) अणु
		udelay(10);
		पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	पूर्ण

	rtl_ग_लिखो_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0x718);
	rtl_ग_लिखो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x2);
	पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	जबतक (पंचांगp8 && count < 20) अणु
		udelay(10);
		पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	पूर्ण
	अगर (ppsc->support_backकरोor || (0 == पंचांगp8)) अणु
		पंचांगp32 = rtl_पढ़ो_dword(rtlpriv, REG_BACKDOOR_DBI_RDATA);
		rtl_ग_लिखो_dword(rtlpriv, REG_BACKDOOR_DBI_WDATA,
				पंचांगp32 | BIT(11) | BIT(12));
		rtl_ग_लिखो_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0xf718);
		rtl_ग_लिखो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x1);
	पूर्ण
	पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	जबतक (पंचांगp8 && count < 20) अणु
		udelay(10);
		पंचांगp8 = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	पूर्ण
पूर्ण

व्योम rtl92ee_enable_hw_security_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 sec_reg_value;
	u8 पंचांगp;

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

	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, पंचांगp | BIT(1));

	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
		"The SECR-value %x\n", sec_reg_value);

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_WPA_CONFIG, &sec_reg_value);
पूर्ण

अटल bool _rtl8192ee_check_pcie_dma_hang(काष्ठा rtl_priv *rtlpriv)
अणु
	u8 पंचांगp;

	/* ग_लिखो reg 0x350 Bit[26]=1. Enable debug port. */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 3);
	अगर (!(पंचांगp & BIT(2))) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 3,
			       पंचांगp | BIT(2));
		mdelay(100); /* Suggested by DD Justin_tsai. */
	पूर्ण

	/* पढ़ो reg 0x350 Bit[25] अगर 1 : RX hang
	 * पढ़ो reg 0x350 Bit[24] अगर 1 : TX hang
	 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 3);
	अगर ((पंचांगp & BIT(0)) || (पंचांगp & BIT(1))) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"CheckPcieDMAHang8192EE(): true!!\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम _rtl8192ee_reset_pcie_पूर्णांकerface_dma(काष्ठा rtl_priv *rtlpriv,
						bool mac_घातer_on)
अणु
	u8 पंचांगp;
	bool release_mac_rx_छोड़ो;
	u8 backup_pcie_dma_छोड़ो;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"ResetPcieInterfaceDMA8192EE()\n");

	/* Revise Note: Follow the करोcument "PCIe RX DMA Hang Reset Flow_v03"
	 * released by SD1 Alan.
	 */

	/* 1. disable रेजिस्टर ग_लिखो lock
	 *	ग_लिखो 0x1C bit[1:0] = 2'h0
	 *	ग_लिखो 0xCC bit[2] = 1'b1
	 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL);
	पंचांगp &= ~(BIT(1) | BIT(0));
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, पंचांगp);
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_PMC_DBG_CTRL2);
	पंचांगp |= BIT(2);
	rtl_ग_लिखो_byte(rtlpriv, REG_PMC_DBG_CTRL2, पंचांगp);

	/* 2. Check and छोड़ो TRX DMA
	 *	ग_लिखो 0x284 bit[18] = 1'b1
	 *	ग_लिखो 0x301 = 0xFF
	 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
	अगर (पंचांगp & BIT(2)) अणु
		/* Alपढ़ोy छोड़ो beक्रमe the function क्रम another reason. */
		release_mac_rx_छोड़ो = false;
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL, (पंचांगp | BIT(2)));
		release_mac_rx_छोड़ो = true;
	पूर्ण

	backup_pcie_dma_छोड़ो = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1);
	अगर (backup_pcie_dma_छोड़ो != 0xFF)
		rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xFF);

	अगर (mac_घातer_on) अणु
		/* 3. reset TRX function
		 *	ग_लिखो 0x100 = 0x00
		 */
		rtl_ग_लिखो_byte(rtlpriv, REG_CR, 0);
	पूर्ण

	/* 4. Reset PCIe DMA
	 *	ग_लिखो 0x003 bit[0] = 0
	 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	पंचांगp &= ~(BIT(0));
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगp);

	/* 5. Enable PCIe DMA
	 *	ग_लिखो 0x003 bit[0] = 1
	 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	पंचांगp |= BIT(0);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगp);

	अगर (mac_घातer_on) अणु
		/* 6. enable TRX function
		 *	ग_लिखो 0x100 = 0xFF
		 */
		rtl_ग_लिखो_byte(rtlpriv, REG_CR, 0xFF);

		/* We should init LLT & RQPN and
		 * prepare Tx/Rx descrptor address later
		 * because MAC function is reset.
		 */
	पूर्ण

	/* 7. Restore PCIe स्वतःload करोwn bit
	 *	ग_लिखो 0xF8 bit[17] = 1'b1
	 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MAC_PHY_CTRL_NORMAL + 2);
	पंचांगp |= BIT(1);
	rtl_ग_लिखो_byte(rtlpriv, REG_MAC_PHY_CTRL_NORMAL + 2, पंचांगp);

	/* In MAC घातer on state, BB and RF maybe in ON state,
	 * अगर we release TRx DMA here
	 * it will cause packets to be started to Tx/Rx,
	 * so we release Tx/Rx DMA later.
	 */
	अगर (!mac_घातer_on) अणु
		/* 8. release TRX DMA
		 *	ग_लिखो 0x284 bit[18] = 1'b0
		 *	ग_लिखो 0x301 = 0x00
		 */
		अगर (release_mac_rx_छोड़ो) अणु
			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
			rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL,
				       (पंचांगp & (~BIT(2))));
		पूर्ण
		rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1,
			       backup_pcie_dma_छोड़ो);
	पूर्ण

	/* 9. lock प्रणाली रेजिस्टर
	 *	ग_लिखो 0xCC bit[2] = 1'b0
	 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_PMC_DBG_CTRL2);
	पंचांगp &= ~(BIT(2));
	rtl_ग_लिखो_byte(rtlpriv, REG_PMC_DBG_CTRL2, पंचांगp);
पूर्ण

पूर्णांक rtl92ee_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool rtstatus = true;
	पूर्णांक err = 0;
	u8 पंचांगp_u1b, u1byte;
	u32 पंचांगp_u4b;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, " Rtl8192EE hw init\n");
	rtlpriv->rtlhal.being_init_adapter = true;
	rtlpriv->पूर्णांकf_ops->disable_aspm(hw);

	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CLKR+1);
	u1byte = rtl_पढ़ो_byte(rtlpriv, REG_CR);
	अगर ((पंचांगp_u1b & BIT(3)) && (u1byte != 0 && u1byte != 0xEA)) अणु
		rtlhal->mac_func_enable = true;
	पूर्ण अन्यथा अणु
		rtlhal->mac_func_enable = false;
		rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON_92E;
	पूर्ण

	अगर (_rtl8192ee_check_pcie_dma_hang(rtlpriv)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "92ee dma hang!\n");
		_rtl8192ee_reset_pcie_पूर्णांकerface_dma(rtlpriv,
						    rtlhal->mac_func_enable);
		rtlhal->mac_func_enable = false;
	पूर्ण

	rtstatus = _rtl92ee_init_mac(hw);

	rtl_ग_लिखो_byte(rtlpriv, 0x577, 0x03);

	/*क्रम Crystal 40 Mhz setting */
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_CTRL4, 0x2A);
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_CTRL4 + 1, 0x00);
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_CTRL2, 0x83);

	/*Forced the antenna b to wअगरi */
	अगर (rtlpriv->btcoexist.btc_info.btcoexist == 1) अणु
		rtl_ग_लिखो_byte(rtlpriv, 0x64, 0);
		rtl_ग_लिखो_byte(rtlpriv, 0x65, 1);
	पूर्ण
	अगर (!rtstatus) अणु
		pr_err("Init MAC failed\n");
		err = 1;
		वापस err;
	पूर्ण
	rtlhal->rx_tag = 0;
	rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG, 0x8000);
	err = rtl92ee_करोwnload_fw(hw, false);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Failed to download FW. Init HW without FW now..\n");
		err = 1;
		rtlhal->fw_पढ़ोy = false;
		वापस err;
	पूर्ण
	rtlhal->fw_पढ़ोy = true;
	/*fw related variable initialize */
	ppsc->fw_current_inpsmode = false;
	rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON_92E;
	rtlhal->fw_clk_change_in_progress = false;
	rtlhal->allow_sw_to_change_hwclc = false;
	rtlhal->last_hmeboxnum = 0;

	rtl92ee_phy_mac_config(hw);

	rtl92ee_phy_bb_config(hw);

	rtl92ee_phy_rf_config(hw);

	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, RF90_PATH_A,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl_get_rfreg(hw, RF90_PATH_B,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->backup_rf_0x1a = (u32)rtl_get_rfreg(hw, RF90_PATH_A, RF_RX_G1,
						    RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[0] = (rtlphy->rfreg_chnlval[0] & 0xfffff3ff) |
				   BIT(10) | BIT(11);

	rtl_set_rfreg(hw, RF90_PATH_A, RF_CHNLBW, RFREG_OFFSET_MASK,
		      rtlphy->rfreg_chnlval[0]);
	rtl_set_rfreg(hw, RF90_PATH_B, RF_CHNLBW, RFREG_OFFSET_MASK,
		      rtlphy->rfreg_chnlval[0]);

	/*---- Set CCK and OFDM Block "ON"----*/
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);

	/* Must set this,
	 * otherwise the rx sensitivity will be very pool. Maddest
	 */
	rtl_set_rfreg(hw, RF90_PATH_A, 0xB1, RFREG_OFFSET_MASK, 0x54418);

	/*Set Hardware(MAC शेष setting.)*/
	_rtl92ee_hw_configure(hw);

	rtlhal->mac_func_enable = true;

	rtl_cam_reset_all_entry(hw);
	rtl92ee_enable_hw_security_config(hw);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	_rtl92ee_enable_aspm_back_करोor(hw);
	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);

	rtl92ee_bt_hw_init(hw);

	rtlpriv->rtlhal.being_init_adapter = false;

	अगर (ppsc->rfpwr_state == ERFON) अणु
		अगर (rtlphy->iqk_initialized) अणु
			rtl92ee_phy_iq_calibrate(hw, true);
		पूर्ण अन्यथा अणु
			rtl92ee_phy_iq_calibrate(hw, false);
			rtlphy->iqk_initialized = true;
		पूर्ण
	पूर्ण

	rtlphy->rfpath_rx_enable[0] = true;
	अगर (rtlphy->rf_type == RF_2T2R)
		rtlphy->rfpath_rx_enable[1] = true;

	efuse_one_byte_पढ़ो(hw, 0x1FA, &पंचांगp_u1b);
	अगर (!(पंचांगp_u1b & BIT(0))) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0F, 0x05);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "PA BIAS path A\n");
	पूर्ण

	अगर ((!(पंचांगp_u1b & BIT(1))) && (rtlphy->rf_type == RF_2T2R)) अणु
		rtl_set_rfreg(hw, RF90_PATH_B, 0x15, 0x0F, 0x05);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "PA BIAS path B\n");
	पूर्ण

	rtl_ग_लिखो_byte(rtlpriv, REG_NAV_UPPER, ((30000 + 127) / 128));

	/*Fixed LDPC rx hang issue. */
	पंचांगp_u4b = rtl_पढ़ो_dword(rtlpriv, REG_SYS_SWR_CTRL1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_SWR_CTRL2, 0x75);
	पंचांगp_u4b =  (पंचांगp_u4b & 0xfff00fff) | (0x7E << 12);
	rtl_ग_लिखो_dword(rtlpriv, REG_SYS_SWR_CTRL1, पंचांगp_u4b);

	rtl92ee_dm_init(hw);

	rtl_ग_लिखो_dword(rtlpriv, 0x4fc, 0);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"end of Rtl8192EE hw init %x\n", err);
	वापस 0;
पूर्ण

अटल क्रमागत version_8192e _rtl92ee_पढ़ो_chip_version(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	क्रमागत version_8192e version = VERSION_UNKNOWN;
	u32 value32;

	rtlphy->rf_type = RF_2T2R;

	value32 = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG1);
	अगर (value32 & TRP_VAUX_EN)
		version = (क्रमागत version_8192e)VERSION_TEST_CHIP_2T2R_8192E;
	अन्यथा
		version = (क्रमागत version_8192e)VERSION_NORMAL_CHIP_2T2R_8192E;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Chip RF Type: %s\n", (rtlphy->rf_type == RF_2T2R) ?
		"RF_2T2R" : "RF_1T1R");

	वापस version;
पूर्ण

अटल पूर्णांक _rtl92ee_set_media_status(काष्ठा ieee80211_hw *hw,
				     क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_msr = rtl_पढ़ो_byte(rtlpriv, MSR) & 0xfc;
	क्रमागत led_ctl_mode ledaction = LED_CTL_NO_LINK;
	u8 mode = MSR_NOLINK;

	चयन (type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		mode = MSR_NOLINK;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to NO LINK!\n");
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_MESH_POINT:
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
	अगर (mode != MSR_AP && rtlpriv->mac80211.link_state < MAC80211_LINKED) अणु
		mode = MSR_NOLINK;
		ledaction = LED_CTL_NO_LINK;
	पूर्ण

	अगर (mode == MSR_NOLINK || mode == MSR_INFRA) अणु
		_rtl92ee_stop_tx_beacon(hw);
		_rtl92ee_enable_bcn_sub_func(hw);
	पूर्ण अन्यथा अगर (mode == MSR_ADHOC || mode == MSR_AP) अणु
		_rtl92ee_resume_tx_beacon(hw);
		_rtl92ee_disable_bcn_sub_func(hw);
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

व्योम rtl92ee_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid)
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
		_rtl92ee_set_bcn_ctrl_reg(hw, 0, BIT(4));
	पूर्ण अन्यथा अणु
		reg_rcr &= (~(RCR_CBSSID_DATA | RCR_CBSSID_BCN));
		_rtl92ee_set_bcn_ctrl_reg(hw, BIT(4), 0);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR,
					      (u8 *)(&reg_rcr));
	पूर्ण
पूर्ण

पूर्णांक rtl92ee_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (_rtl92ee_set_media_status(hw, type))
		वापस -EOPNOTSUPP;

	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		अगर (type != NL80211_IFTYPE_AP &&
		    type != NL80211_IFTYPE_MESH_POINT)
			rtl92ee_set_check_bssid(hw, true);
	पूर्ण अन्यथा अणु
		rtl92ee_set_check_bssid(hw, false);
	पूर्ण

	वापस 0;
पूर्ण

/* करोn't set REG_EDCA_BE_PARAM here because mac80211 will send pkt when scan */
व्योम rtl92ee_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl92ee_dm_init_edca_turbo(hw);
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
		WARN_ONCE(true, "rtl8192ee: invalid aci: %d !\n", aci);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92ee_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, rtlpci->irq_mask[0] & 0xFFFFFFFF);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, rtlpci->irq_mask[1] & 0xFFFFFFFF);
	rtlpci->irq_enabled = true;
पूर्ण

व्योम rtl92ee_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, IMR_DISABLED);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, IMR_DISABLED);
	rtlpci->irq_enabled = false;
	/*synchronize_irq(rtlpci->pdev->irq);*/
पूर्ण

अटल व्योम _rtl92ee_घातeroff_adapter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 u1b_पंचांगp;

	rtlhal->mac_func_enable = false;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "POWER OFF adapter\n");

	/* Run LPS WL RFOFF flow */
	rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
				 PWR_INTF_PCI_MSK, RTL8192E_NIC_LPS_ENTER_FLOW);
	/* turn off RF */
	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, 0x00);

	/* ==== Reset digital sequence   ======  */
	अगर ((rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL) & BIT(7)) && rtlhal->fw_पढ़ोy)
		rtl92ee_firmware_selfreset(hw);

	/* Reset MCU  */
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, (u1b_पंचांगp & (~BIT(2))));

	/* reset MCU पढ़ोy status */
	rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0x00);

	/* HW card disable configuration. */
	rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
				 PWR_INTF_PCI_MSK, RTL8192E_NIC_DISABLE_FLOW);

	/* Reset MCU IO Wrapper */
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_पंचांगp & (~BIT(0))));
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_पंचांगp | BIT(0)));

	/* lock ISO/CLK/Power control रेजिस्टर */
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0E);
पूर्ण

व्योम rtl92ee_card_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	क्रमागत nl80211_अगरtype opmode;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "RTL8192ee card disable\n");

	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;

	_rtl92ee_set_media_status(hw, opmode);

	अगर (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);

	_rtl92ee_घातeroff_adapter(hw);

	/* after घातer off we should करो iqk again */
	अगर (!rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->phy.iqk_initialized = false;
पूर्ण

व्योम rtl92ee_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_पूर्णांक *पूर्णांकvec)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	पूर्णांकvec->पूर्णांकa = rtl_पढ़ो_dword(rtlpriv, ISR) & rtlpci->irq_mask[0];
	rtl_ग_लिखो_dword(rtlpriv, ISR, पूर्णांकvec->पूर्णांकa);

	पूर्णांकvec->पूर्णांकb = rtl_पढ़ो_dword(rtlpriv, REG_HISRE) & rtlpci->irq_mask[1];
	rtl_ग_लिखो_dword(rtlpriv, REG_HISRE, पूर्णांकvec->पूर्णांकb);
पूर्ण

व्योम rtl92ee_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u16 bcn_पूर्णांकerval, atim_winकरोw;

	bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;
	atim_winकरोw = 2;	/*FIX MERGE */
	rtl92ee_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_ATIMWND, atim_winकरोw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl_ग_लिखो_word(rtlpriv, REG_BCNTCFG, 0x660f);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_CCK, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, 0x606, 0x30);
	rtlpci->reg_bcn_ctrl_val |= BIT(3);
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8)rtlpci->reg_bcn_ctrl_val);
पूर्ण

व्योम rtl92ee_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;

	rtl_dbg(rtlpriv, COMP_BEACON, DBG_DMESG,
		"beacon_interval:%d\n", bcn_पूर्णांकerval);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
पूर्ण

व्योम rtl92ee_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
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
	rtl92ee_disable_पूर्णांकerrupt(hw);
	rtl92ee_enable_पूर्णांकerrupt(hw);
पूर्ण

अटल u8 _rtl92ee_get_chnl_group(u8 chnl)
अणु
	u8 group = 0;

	अगर (chnl <= 14) अणु
		अगर (1 <= chnl && chnl <= 2)
			group = 0;
		अन्यथा अगर (3 <= chnl && chnl <= 5)
			group = 1;
		अन्यथा अगर (6 <= chnl && chnl <= 8)
			group = 2;
		अन्यथा अगर (9 <= chnl && chnl <= 11)
			group = 3;
		अन्यथा अगर (12 <= chnl && chnl <= 14)
			group = 4;
	पूर्ण अन्यथा अणु
		अगर (36 <= chnl && chnl <= 42)
			group = 0;
		अन्यथा अगर (44 <= chnl && chnl <= 48)
			group = 1;
		अन्यथा अगर (50 <= chnl && chnl <= 58)
			group = 2;
		अन्यथा अगर (60 <= chnl && chnl <= 64)
			group = 3;
		अन्यथा अगर (100 <= chnl && chnl <= 106)
			group = 4;
		अन्यथा अगर (108 <= chnl && chnl <= 114)
			group = 5;
		अन्यथा अगर (116 <= chnl && chnl <= 122)
			group = 6;
		अन्यथा अगर (124 <= chnl && chnl <= 130)
			group = 7;
		अन्यथा अगर (132 <= chnl && chnl <= 138)
			group = 8;
		अन्यथा अगर (140 <= chnl && chnl <= 144)
			group = 9;
		अन्यथा अगर (149 <= chnl && chnl <= 155)
			group = 10;
		अन्यथा अगर (157 <= chnl && chnl <= 161)
			group = 11;
		अन्यथा अगर (165 <= chnl && chnl <= 171)
			group = 12;
		अन्यथा अगर (173 <= chnl && chnl <= 177)
			group = 13;
	पूर्ण
	वापस group;
पूर्ण

अटल व्योम _rtl8192ee_पढ़ो_घातer_value_fromprom(काष्ठा ieee80211_hw *hw,
						 काष्ठा txघातer_info_2g *pwr2g,
						 काष्ठा txघातer_info_5g *pwr5g,
						 bool स्वतःload_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 rf, addr = EEPROM_TX_PWR_INX, group, i = 0;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"hal_ReadPowerValueFromPROM92E(): PROMContent[0x%x]=0x%x\n",
		(addr + 1), hwinfo[addr + 1]);
	अगर (0xFF == hwinfo[addr+1])  /*YJ,add,120316*/
		स्वतःload_fail = true;

	अगर (स्वतःload_fail) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"auto load fail : Use Default value!\n");
		क्रम (rf = 0 ; rf < MAX_RF_PATH ; rf++) अणु
			/* 2.4G शेष value */
			क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) अणु
				pwr2g->index_cck_base[rf][group] = 0x2D;
				pwr2g->index_bw40_base[rf][group] = 0x2D;
			पूर्ण
			क्रम (i = 0; i < MAX_TX_COUNT; i++) अणु
				अगर (i == 0) अणु
					pwr2g->bw20_dअगरf[rf][0] = 0x02;
					pwr2g->ofdm_dअगरf[rf][0] = 0x04;
				पूर्ण अन्यथा अणु
					pwr2g->bw20_dअगरf[rf][i] = 0xFE;
					pwr2g->bw40_dअगरf[rf][i] = 0xFE;
					pwr2g->cck_dअगरf[rf][i] = 0xFE;
					pwr2g->ofdm_dअगरf[rf][i] = 0xFE;
				पूर्ण
			पूर्ण

			/*5G शेष value*/
			क्रम (group = 0 ; group < MAX_CHNL_GROUP_5G; group++)
				pwr5g->index_bw40_base[rf][group] = 0x2A;

			क्रम (i = 0; i < MAX_TX_COUNT; i++) अणु
				अगर (i == 0) अणु
					pwr5g->ofdm_dअगरf[rf][0] = 0x04;
					pwr5g->bw20_dअगरf[rf][0] = 0x00;
					pwr5g->bw80_dअगरf[rf][0] = 0xFE;
					pwr5g->bw160_dअगरf[rf][0] = 0xFE;
				पूर्ण अन्यथा अणु
					pwr5g->ofdm_dअगरf[rf][0] = 0xFE;
					pwr5g->bw20_dअगरf[rf][0] = 0xFE;
					pwr5g->bw40_dअगरf[rf][0] = 0xFE;
					pwr5g->bw80_dअगरf[rf][0] = 0xFE;
					pwr5g->bw160_dअगरf[rf][0] = 0xFE;
				पूर्ण
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	rtl_priv(hw)->efuse.txpwr_fromeprom = true;

	क्रम (rf = 0 ; rf < MAX_RF_PATH ; rf++) अणु
		/*2.4G शेष value*/
		क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) अणु
			pwr2g->index_cck_base[rf][group] = hwinfo[addr++];
			अगर (pwr2g->index_cck_base[rf][group] == 0xFF)
				pwr2g->index_cck_base[rf][group] = 0x2D;
		पूर्ण
		क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G - 1; group++) अणु
			pwr2g->index_bw40_base[rf][group] = hwinfo[addr++];
			अगर (pwr2g->index_bw40_base[rf][group] == 0xFF)
				pwr2g->index_bw40_base[rf][group] = 0x2D;
		पूर्ण
		क्रम (i = 0; i < MAX_TX_COUNT; i++) अणु
			अगर (i == 0) अणु
				pwr2g->bw40_dअगरf[rf][i] = 0;
				अगर (hwinfo[addr] == 0xFF) अणु
					pwr2g->bw20_dअगरf[rf][i] = 0x02;
				पूर्ण अन्यथा अणु
					pwr2g->bw20_dअगरf[rf][i] = (hwinfo[addr]
								   & 0xf0) >> 4;
					अगर (pwr2g->bw20_dअगरf[rf][i] & BIT(3))
						pwr2g->bw20_dअगरf[rf][i] |= 0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF) अणु
					pwr2g->ofdm_dअगरf[rf][i] = 0x04;
				पूर्ण अन्यथा अणु
					pwr2g->ofdm_dअगरf[rf][i] = (hwinfo[addr]
								   & 0x0f);
					अगर (pwr2g->ofdm_dअगरf[rf][i] & BIT(3))
						pwr2g->ofdm_dअगरf[rf][i] |= 0xF0;
				पूर्ण
				pwr2g->cck_dअगरf[rf][i] = 0;
				addr++;
			पूर्ण अन्यथा अणु
				अगर (hwinfo[addr] == 0xFF) अणु
					pwr2g->bw40_dअगरf[rf][i] = 0xFE;
				पूर्ण अन्यथा अणु
					pwr2g->bw40_dअगरf[rf][i] = (hwinfo[addr]
								   & 0xf0) >> 4;
					अगर (pwr2g->bw40_dअगरf[rf][i] & BIT(3))
						pwr2g->bw40_dअगरf[rf][i] |= 0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF) अणु
					pwr2g->bw20_dअगरf[rf][i] = 0xFE;
				पूर्ण अन्यथा अणु
					pwr2g->bw20_dअगरf[rf][i] = (hwinfo[addr]
								   & 0x0f);
					अगर (pwr2g->bw20_dअगरf[rf][i] & BIT(3))
						pwr2g->bw20_dअगरf[rf][i] |= 0xF0;
				पूर्ण
				addr++;

				अगर (hwinfo[addr] == 0xFF) अणु
					pwr2g->ofdm_dअगरf[rf][i] = 0xFE;
				पूर्ण अन्यथा अणु
					pwr2g->ofdm_dअगरf[rf][i] = (hwinfo[addr]
								   & 0xf0) >> 4;
					अगर (pwr2g->ofdm_dअगरf[rf][i] & BIT(3))
						pwr2g->ofdm_dअगरf[rf][i] |= 0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF) अणु
					pwr2g->cck_dअगरf[rf][i] = 0xFE;
				पूर्ण अन्यथा अणु
					pwr2g->cck_dअगरf[rf][i] = (hwinfo[addr]
								  & 0x0f);
					अगर (pwr2g->cck_dअगरf[rf][i] & BIT(3))
						pwr2g->cck_dअगरf[rf][i] |= 0xF0;
				पूर्ण
				addr++;
			पूर्ण
		पूर्ण

		/*5G शेष value*/
		क्रम (group = 0 ; group < MAX_CHNL_GROUP_5G; group++) अणु
			pwr5g->index_bw40_base[rf][group] = hwinfo[addr++];
			अगर (pwr5g->index_bw40_base[rf][group] == 0xFF)
				pwr5g->index_bw40_base[rf][group] = 0xFE;
		पूर्ण

		क्रम (i = 0; i < MAX_TX_COUNT; i++) अणु
			अगर (i == 0) अणु
				pwr5g->bw40_dअगरf[rf][i] = 0;

				अगर (hwinfo[addr] == 0xFF) अणु
					pwr5g->bw20_dअगरf[rf][i] = 0;
				पूर्ण अन्यथा अणु
					pwr5g->bw20_dअगरf[rf][0] = (hwinfo[addr]
								   & 0xf0) >> 4;
					अगर (pwr5g->bw20_dअगरf[rf][i] & BIT(3))
						pwr5g->bw20_dअगरf[rf][i] |= 0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF) अणु
					pwr5g->ofdm_dअगरf[rf][i] = 0x04;
				पूर्ण अन्यथा अणु
					pwr5g->ofdm_dअगरf[rf][0] = (hwinfo[addr]
								   & 0x0f);
					अगर (pwr5g->ofdm_dअगरf[rf][i] & BIT(3))
						pwr5g->ofdm_dअगरf[rf][i] |= 0xF0;
				पूर्ण
				addr++;
			पूर्ण अन्यथा अणु
				अगर (hwinfo[addr] == 0xFF) अणु
					pwr5g->bw40_dअगरf[rf][i] = 0xFE;
				पूर्ण अन्यथा अणु
					pwr5g->bw40_dअगरf[rf][i] = (hwinfo[addr]
								  & 0xf0) >> 4;
					अगर (pwr5g->bw40_dअगरf[rf][i] & BIT(3))
						pwr5g->bw40_dअगरf[rf][i] |= 0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF) अणु
					pwr5g->bw20_dअगरf[rf][i] = 0xFE;
				पूर्ण अन्यथा अणु
					pwr5g->bw20_dअगरf[rf][i] = (hwinfo[addr]
								   & 0x0f);
					अगर (pwr5g->bw20_dअगरf[rf][i] & BIT(3))
						pwr5g->bw20_dअगरf[rf][i] |= 0xF0;
				पूर्ण
				addr++;
			पूर्ण
		पूर्ण

		अगर (hwinfo[addr] == 0xFF) अणु
			pwr5g->ofdm_dअगरf[rf][1] = 0xFE;
			pwr5g->ofdm_dअगरf[rf][2] = 0xFE;
		पूर्ण अन्यथा अणु
			pwr5g->ofdm_dअगरf[rf][1] = (hwinfo[addr] & 0xf0) >> 4;
			pwr5g->ofdm_dअगरf[rf][2] = (hwinfo[addr] & 0x0f);
		पूर्ण
		addr++;

		अगर (hwinfo[addr] == 0xFF)
			pwr5g->ofdm_dअगरf[rf][3] = 0xFE;
		अन्यथा
			pwr5g->ofdm_dअगरf[rf][3] = (hwinfo[addr] & 0x0f);
		addr++;

		क्रम (i = 1; i < MAX_TX_COUNT; i++) अणु
			अगर (pwr5g->ofdm_dअगरf[rf][i] == 0xFF)
				pwr5g->ofdm_dअगरf[rf][i] = 0xFE;
			अन्यथा अगर (pwr5g->ofdm_dअगरf[rf][i] & BIT(3))
				pwr5g->ofdm_dअगरf[rf][i] |= 0xF0;
		पूर्ण

		क्रम (i = 0; i < MAX_TX_COUNT; i++) अणु
			अगर (hwinfo[addr] == 0xFF) अणु
				pwr5g->bw80_dअगरf[rf][i] = 0xFE;
			पूर्ण अन्यथा अणु
				pwr5g->bw80_dअगरf[rf][i] = (hwinfo[addr] & 0xf0)
							  >> 4;
				अगर (pwr5g->bw80_dअगरf[rf][i] & BIT(3))
					pwr5g->bw80_dअगरf[rf][i] |= 0xF0;
			पूर्ण

			अगर (hwinfo[addr] == 0xFF) अणु
				pwr5g->bw160_dअगरf[rf][i] = 0xFE;
			पूर्ण अन्यथा अणु
				pwr5g->bw160_dअगरf[rf][i] =
				  (hwinfo[addr] & 0x0f);
				अगर (pwr5g->bw160_dअगरf[rf][i] & BIT(3))
					pwr5g->bw160_dअगरf[rf][i] |= 0xF0;
			पूर्ण
			addr++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_पढ़ो_txघातer_info_from_hwpg(काष्ठा ieee80211_hw *hw,
						 bool स्वतःload_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *efu = rtl_efuse(rtl_priv(hw));
	काष्ठा txघातer_info_2g pwr2g;
	काष्ठा txघातer_info_5g pwr5g;
	u8 rf, idx;
	u8 i;

	_rtl8192ee_पढ़ो_घातer_value_fromprom(hw, &pwr2g, &pwr5g,
					     स्वतःload_fail, hwinfo);

	क्रम (rf = 0; rf < MAX_RF_PATH; rf++) अणु
		क्रम (i = 0; i < 14; i++) अणु
			idx = _rtl92ee_get_chnl_group(i + 1);

			अगर (i == CHANNEL_MAX_NUMBER_2G - 1) अणु
				efu->txpwrlevel_cck[rf][i] =
						pwr2g.index_cck_base[rf][5];
				efu->txpwrlevel_ht40_1s[rf][i] =
						pwr2g.index_bw40_base[rf][idx];
			पूर्ण अन्यथा अणु
				efu->txpwrlevel_cck[rf][i] =
						pwr2g.index_cck_base[rf][idx];
				efu->txpwrlevel_ht40_1s[rf][i] =
						pwr2g.index_bw40_base[rf][idx];
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < CHANNEL_MAX_NUMBER_5G; i++) अणु
			idx = _rtl92ee_get_chnl_group(channel5g[i]);
			efu->txpwr_5g_bw40base[rf][i] =
					pwr5g.index_bw40_base[rf][idx];
		पूर्ण
		क्रम (i = 0; i < CHANNEL_MAX_NUMBER_5G_80M; i++) अणु
			u8 upper, lower;

			idx = _rtl92ee_get_chnl_group(channel5g_80m[i]);
			upper = pwr5g.index_bw40_base[rf][idx];
			lower = pwr5g.index_bw40_base[rf][idx + 1];

			efu->txpwr_5g_bw80base[rf][i] = (upper + lower) / 2;
		पूर्ण
		क्रम (i = 0; i < MAX_TX_COUNT; i++) अणु
			efu->txpwr_cckdअगरf[rf][i] = pwr2g.cck_dअगरf[rf][i];
			efu->txpwr_legacyhtdअगरf[rf][i] = pwr2g.ofdm_dअगरf[rf][i];
			efu->txpwr_ht20dअगरf[rf][i] = pwr2g.bw20_dअगरf[rf][i];
			efu->txpwr_ht40dअगरf[rf][i] = pwr2g.bw40_dअगरf[rf][i];

			efu->txpwr_5g_ofdmdअगरf[rf][i] = pwr5g.ofdm_dअगरf[rf][i];
			efu->txpwr_5g_bw20dअगरf[rf][i] = pwr5g.bw20_dअगरf[rf][i];
			efu->txpwr_5g_bw40dअगरf[rf][i] = pwr5g.bw40_dअगरf[rf][i];
			efu->txpwr_5g_bw80dअगरf[rf][i] = pwr5g.bw80_dअगरf[rf][i];
		पूर्ण
	पूर्ण

	अगर (!स्वतःload_fail)
		efu->eeprom_thermalmeter = hwinfo[EEPROM_THERMAL_METER_92E];
	अन्यथा
		efu->eeprom_thermalmeter = EEPROM_DEFAULT_THERMALMETER;

	अगर (efu->eeprom_thermalmeter == 0xff || स्वतःload_fail) अणु
		efu->apk_thermalmeterignore = true;
		efu->eeprom_thermalmeter = EEPROM_DEFAULT_THERMALMETER;
	पूर्ण

	efu->thermalmeter[0] = efu->eeprom_thermalmeter;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"thermalmeter = 0x%x\n", efu->eeprom_thermalmeter);

	अगर (!स्वतःload_fail) अणु
		efu->eeprom_regulatory = hwinfo[EEPROM_RF_BOARD_OPTION_92E]
					 & 0x07;
		अगर (hwinfo[EEPROM_RF_BOARD_OPTION_92E] == 0xFF)
			efu->eeprom_regulatory = 0;
	पूर्ण अन्यथा अणु
		efu->eeprom_regulatory = 0;
	पूर्ण
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"eeprom_regulatory = 0x%x\n", efu->eeprom_regulatory);
पूर्ण

अटल व्योम _rtl92ee_पढ़ो_adapter_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक params[] = अणुRTL8192E_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13पूर्ण;
	u8 *hwinfo;

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	अगर (!hwinfo)
		वापस;

	अगर (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		जाओ निकास;

	अगर (rtlefuse->eeprom_oemid == 0xFF)
		rtlefuse->eeprom_oemid = 0;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM Customer ID: 0x%2x\n", rtlefuse->eeprom_oemid);
	/* set channel plan from efuse */
	rtlefuse->channel_plan = rtlefuse->eeprom_channelplan;
	/*tx घातer*/
	_rtl92ee_पढ़ो_txघातer_info_from_hwpg(hw, rtlefuse->स्वतःload_failflag,
					     hwinfo);

	rtl92ee_पढ़ो_bt_coexist_info_from_hwpg(hw, rtlefuse->स्वतःload_failflag,
					       hwinfo);

	/*board type*/
	rtlefuse->board_type = (((*(u8 *)&hwinfo[EEPROM_RF_BOARD_OPTION_92E])
				& 0xE0) >> 5);
	अगर ((*(u8 *)&hwinfo[EEPROM_RF_BOARD_OPTION_92E]) == 0xFF)
		rtlefuse->board_type = 0;

	अगर (rtlpriv->btcoexist.btc_info.btcoexist == 1)
		rtlefuse->board_type |= BIT(2); /* ODM_BOARD_BT */

	rtlhal->board_type = rtlefuse->board_type;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"board_type = 0x%x\n", rtlefuse->board_type);
	/*parse xtal*/
	rtlefuse->crystalcap = hwinfo[EEPROM_XTAL_92E];
	अगर (hwinfo[EEPROM_XTAL_92E] == 0xFF)
		rtlefuse->crystalcap = 0x20;

	/*antenna भागersity*/
	rtlefuse->antenna_भाग_प्रकारype = NO_ANTDIV;
	rtlefuse->antenna_भाग_cfg = 0;

	अगर (rtlhal->oem_id == RT_CID_DEFAULT) अणु
		चयन (rtlefuse->eeprom_oemid) अणु
		हाल EEPROM_CID_DEFAULT:
			अगर (rtlefuse->eeprom_did == 0x818B) अणु
				अगर ((rtlefuse->eeprom_svid == 0x10EC) &&
				    (rtlefuse->eeprom_smid == 0x001B))
					rtlhal->oem_id = RT_CID_819X_LENOVO;
			पूर्ण अन्यथा अणु
				rtlhal->oem_id = RT_CID_DEFAULT;
			पूर्ण
			अवरोध;
		शेष:
			rtlhal->oem_id = RT_CID_DEFAULT;
			अवरोध;
		पूर्ण
	पूर्ण
निकास:
	kमुक्त(hwinfo);
पूर्ण

अटल व्योम _rtl92ee_hal_customized_behavior(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	rtlpriv->ledctl.led_खोलोdrain = true;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
		"RT Customized ID: 0x%02X\n", rtlhal->oem_id);
पूर्ण

व्योम rtl92ee_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_u1b;

	rtlhal->version = _rtl92ee_पढ़ो_chip_version(hw);
	अगर (get_rf_type(rtlphy) == RF_1T1R) अणु
		rtlpriv->dm.rfpath_rxenable[0] = true;
	पूर्ण अन्यथा अणु
		rtlpriv->dm.rfpath_rxenable[0] = true;
		rtlpriv->dm.rfpath_rxenable[1] = true;
	पूर्ण
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
		_rtl92ee_पढ़ो_adapter_info(hw);
	पूर्ण अन्यथा अणु
		pr_err("Autoload ERR!!\n");
	पूर्ण
	_rtl92ee_hal_customized_behavior(hw);

	rtlphy->rfpath_rx_enable[0] = true;
	अगर (rtlphy->rf_type == RF_2T2R)
		rtlphy->rfpath_rx_enable[1] = true;
पूर्ण

अटल u8 _rtl92ee_mrate_idx_to_arfr_id(काष्ठा ieee80211_hw *hw, u8 rate_index)
अणु
	u8 ret = 0;

	चयन (rate_index) अणु
	हाल RATR_INX_WIRELESS_NGB:
		ret = 0;
		अवरोध;
	हाल RATR_INX_WIRELESS_N:
	हाल RATR_INX_WIRELESS_NG:
		ret = 4;
		अवरोध;
	हाल RATR_INX_WIRELESS_NB:
		ret = 2;
		अवरोध;
	हाल RATR_INX_WIRELESS_GB:
		ret = 6;
		अवरोध;
	हाल RATR_INX_WIRELESS_G:
		ret = 7;
		अवरोध;
	हाल RATR_INX_WIRELESS_B:
		ret = 8;
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम rtl92ee_update_hal_rate_mask(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_sta *sta,
					 u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u32 ratr_biपंचांगap;
	u8 ratr_index;
	u8 curtxbw_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40)
			     ? 1 : 0;
	u8 b_curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
				1 : 0;
	u8 b_curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	क्रमागत wireless_mode wirelessmode = 0;
	bool b_लघुgi = false;
	u8 rate_mask[7] = अणु0पूर्ण;
	u8 macid = 0;
	/*u8 mimo_ps = IEEE80211_SMPS_OFF;*/
	sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
	wirelessmode = sta_entry->wireless_mode;
	अगर (mac->opmode == NL80211_IFTYPE_STATION ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT)
		curtxbw_40mhz = mac->bw_40;
	अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		 mac->opmode == NL80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;

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
	हाल WIRELESS_MODE_N_24G:
		अगर (curtxbw_40mhz)
			ratr_index = RATR_INX_WIRELESS_NGB;
		अन्यथा
			ratr_index = RATR_INX_WIRELESS_NB;

		अगर (rtlphy->rf_type == RF_1T1R) अणु
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
					ratr_biपंचांगap &= 0x0f8f0000;
				अन्यथा अगर (rssi_level == 2)
					ratr_biपंचांगap &= 0x0ffff000;
				अन्यथा
					ratr_biपंचांगap &= 0x0ffff015;
			पूर्ण अन्यथा अणु
				अगर (rssi_level == 1)
					ratr_biपंचांगap &= 0x0f8f0000;
				अन्यथा अगर (rssi_level == 2)
					ratr_biपंचांगap &= 0x0ffff000;
				अन्यथा
					ratr_biपंचांगap &= 0x0ffff005;
			पूर्ण
		पूर्ण

		अगर ((curtxbw_40mhz && b_curलघुgi_40mhz) ||
		    (!curtxbw_40mhz && b_curलघुgi_20mhz)) अणु
			अगर (macid == 0)
				b_लघुgi = true;
			अन्यथा अगर (macid == 1)
				b_लघुgi = false;
		पूर्ण
		अवरोध;
	शेष:
		ratr_index = RATR_INX_WIRELESS_NGB;

		अगर (rtlphy->rf_type == RF_1T1R)
			ratr_biपंचांगap &= 0x000ff0ff;
		अन्यथा
			ratr_biपंचांगap &= 0x0f8ff0ff;
		अवरोध;
	पूर्ण
	ratr_index = _rtl92ee_mrate_idx_to_arfr_id(hw, ratr_index);
	sta_entry->ratr_index = ratr_index;

	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"ratr_bitmap :%x\n", ratr_biपंचांगap);
	*(u32 *)&rate_mask = (ratr_biपंचांगap & 0x0fffffff) |
				       (ratr_index << 28);
	rate_mask[0] = macid;
	rate_mask[1] = ratr_index | (b_लघुgi ? 0x80 : 0x00);
	rate_mask[2] = curtxbw_40mhz | ((!update_bw) << 3);
	rate_mask[3] = (u8)(ratr_biपंचांगap & 0x000000ff);
	rate_mask[4] = (u8)((ratr_biपंचांगap & 0x0000ff00) >> 8);
	rate_mask[5] = (u8)((ratr_biपंचांगap & 0x00ff0000) >> 16);
	rate_mask[6] = (u8)((ratr_biपंचांगap & 0xff000000) >> 24);
	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"Rate_index:%x, ratr_val:%x, %x:%x:%x:%x:%x:%x:%x\n",
		ratr_index, ratr_biपंचांगap, rate_mask[0], rate_mask[1],
		rate_mask[2], rate_mask[3], rate_mask[4],
		rate_mask[5], rate_mask[6]);
	rtl92ee_fill_h2c_cmd(hw, H2C_92E_RA_MASK, 7, rate_mask);
	_rtl92ee_set_bcn_ctrl_reg(hw, BIT(3), 0);
पूर्ण

व्योम rtl92ee_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_sta *sta, u8 rssi_level,
				 bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->dm.useramask)
		rtl92ee_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
पूर्ण

व्योम rtl92ee_update_channel_access_setting(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 sअगरs_समयr;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME,
				      (u8 *)&mac->slot_समय);
	अगर (!mac->ht_enable)
		sअगरs_समयr = 0x0a0a;
	अन्यथा
		sअगरs_समयr = 0x0e0e;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SIFS, (u8 *)&sअगरs_समयr);
पूर्ण

bool rtl92ee_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid)
अणु
	*valid = 1;
	वापस true;
पूर्ण

व्योम rtl92ee_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
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
			rtl_dbg(rtlpriv, COMP_ERR, DBG_DMESG,
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

व्योम rtl92ee_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
					    bool स्वतः_load_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value;

	अगर (!स्वतः_load_fail) अणु
		value = hwinfo[EEPROM_RF_BOARD_OPTION_92E];
		अगर (((value & 0xe0) >> 5) == 0x1)
			rtlpriv->btcoexist.btc_info.btcoexist = 1;
		अन्यथा
			rtlpriv->btcoexist.btc_info.btcoexist = 0;

		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8192E;
		rtlpriv->btcoexist.btc_info.ant_num = ANT_X2;
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.btc_info.btcoexist = 1;
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8192E;
		rtlpriv->btcoexist.btc_info.ant_num = ANT_X1;
	पूर्ण
पूर्ण

व्योम rtl92ee_bt_reg_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* 0:Low, 1:High, 2:From Efuse. */
	rtlpriv->btcoexist.reg_bt_iso = 2;
	/* 0:Idle, 1:None-SCO, 2:SCO, 3:From Counter. */
	rtlpriv->btcoexist.reg_bt_sco = 3;
	/* 0:Disable BT control A-MPDU, 1:Enable BT control A-MPDU. */
	rtlpriv->btcoexist.reg_bt_sco = 0;
पूर्ण

व्योम rtl92ee_bt_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_init_hw_config(rtlpriv);
पूर्ण

व्योम rtl92ee_suspend(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

व्योम rtl92ee_resume(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

/* Turn on AAP (RCR:bit 0) क्रम promicuous mode. */
व्योम rtl92ee_allow_all_destaddr(काष्ठा ieee80211_hw *hw,
				bool allow_all_da, bool ग_लिखो_पूर्णांकo_reg)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	अगर (allow_all_da)	/* Set BIT0 */
		rtlpci->receive_config |= RCR_AAP;
	अन्यथा			/* Clear BIT0 */
		rtlpci->receive_config &= ~RCR_AAP;

	अगर (ग_लिखो_पूर्णांकo_reg)
		rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);

	rtl_dbg(rtlpriv, COMP_TURBO | COMP_INIT, DBG_LOUD,
		"receive_config=0x%08X, write_into_reg=%d\n",
		rtlpci->receive_config, ग_लिखो_पूर्णांकo_reg);
पूर्ण
