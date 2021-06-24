<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2013  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../efuse.h"
#समावेश "../base.h"
#समावेश "../regd.h"
#समावेश "../cam.h"
#समावेश "../ps.h"
#समावेश "../pci.h"
#समावेश "../pwrseqcmd.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "dm.h"
#समावेश "fw.h"
#समावेश "led.h"
#समावेश "hw.h"
#समावेश "pwrseq.h"

#घोषणा LLT_CONFIG		5

अटल व्योम _rtl88ee_set_bcn_ctrl_reg(काष्ठा ieee80211_hw *hw,
				      u8 set_bits, u8 clear_bits)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpci->reg_bcn_ctrl_val |= set_bits;
	rtlpci->reg_bcn_ctrl_val &= ~clear_bits;

	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8) rtlpci->reg_bcn_ctrl_val);
पूर्ण

अटल व्योम _rtl88ee_stop_tx_beacon(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl88ee_resume_tx_beacon(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl88ee_enable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl88ee_set_bcn_ctrl_reg(hw, 0, BIT(1));
पूर्ण

अटल व्योम _rtl88ee_वापस_beacon_queue_skb(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[BEACON_QUEUE];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);
	जबतक (skb_queue_len(&ring->queue)) अणु
		काष्ठा rtl_tx_desc *entry = &ring->desc[ring->idx];
		काष्ठा sk_buff *skb = __skb_dequeue(&ring->queue);

		dma_unmap_single(&rtlpci->pdev->dev,
				 rtlpriv->cfg->ops->get_desc(hw, (u8 *)entry,
						true, HW_DESC_TXBUFF_ADDR),
				 skb->len, DMA_TO_DEVICE);
		kमुक्त_skb(skb);
		ring->idx = (ring->idx + 1) % ring->entries;
	पूर्ण
	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);
पूर्ण

अटल व्योम _rtl88ee_disable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl88ee_set_bcn_ctrl_reg(hw, BIT(1), 0);
पूर्ण

अटल व्योम _rtl88ee_set_fw_घड़ी_on(काष्ठा ieee80211_hw *hw,
				     u8 rpwm_val, bool b_need_turn_off_ckk)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool b_support_remote_wake_up;
	u32 count = 0, isr_regaddr, content;
	bool schedule_समयr = b_need_turn_off_ckk;
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

	अगर (IS_IN_LOW_POWER_STATE_88E(rtlhal->fw_ps_state)) अणु
		rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_SET_RPWM, &rpwm_val);
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
				rtlhal->fw_ps_state = FW_PS_STATE_RF_ON_88E;
				rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
					"Receive CPWM INT!!! Set pHalData->FwPSState = %X\n",
					rtlhal->fw_ps_state);
			पूर्ण
		पूर्ण

		spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
		rtlhal->fw_clk_change_in_progress = false;
		spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
		अगर (schedule_समयr) अणु
			mod_समयr(&rtlpriv->works.fw_घड़ीoff_समयr,
				  jअगरfies + MSECS(10));
		पूर्ण

	पूर्ण अन्यथा  अणु
		spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
		rtlhal->fw_clk_change_in_progress = false;
		spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
	पूर्ण
पूर्ण

अटल व्योम _rtl88ee_set_fw_घड़ी_off(काष्ठा ieee80211_hw *hw,
				      u8 rpwm_val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring;
	क्रमागत rf_pwrstate rtstate;
	bool schedule_समयr = false;
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
			schedule_समयr = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (schedule_समयr) अणु
		mod_समयr(&rtlpriv->works.fw_घड़ीoff_समयr,
			  jअगरfies + MSECS(10));
		वापस;
	पूर्ण

	अगर (FW_PS_STATE(rtlhal->fw_ps_state) !=
	    FW_PS_STATE_RF_OFF_LOW_PWR_88E) अणु
		spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
		अगर (!rtlhal->fw_clk_change_in_progress) अणु
			rtlhal->fw_clk_change_in_progress = true;
			spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
			rtlhal->fw_ps_state = FW_PS_STATE(rpwm_val);
			rtl_ग_लिखो_word(rtlpriv, REG_HISR, 0x0100);
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
						      &rpwm_val);
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

अटल व्योम _rtl88ee_set_fw_ps_rf_on(काष्ठा ieee80211_hw *hw)
अणु
	u8 rpwm_val = 0;

	rpwm_val |= (FW_PS_STATE_RF_OFF_88E | FW_PS_ACK);
	_rtl88ee_set_fw_घड़ी_on(hw, rpwm_val, true);
पूर्ण

अटल व्योम _rtl88ee_set_fw_ps_rf_off_low_घातer(काष्ठा ieee80211_hw *hw)
अणु
	u8 rpwm_val = 0;
	rpwm_val |= FW_PS_STATE_RF_OFF_LOW_PWR_88E;
	_rtl88ee_set_fw_घड़ी_off(hw, rpwm_val);
पूर्ण

व्योम rtl88ee_fw_clk_off_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा rtl_priv *rtlpriv = from_समयr(rtlpriv, t,
					      works.fw_घड़ीoff_समयr);
	काष्ठा ieee80211_hw *hw = rtlpriv->hw;

	_rtl88ee_set_fw_ps_rf_off_low_घातer(hw);
पूर्ण

अटल व्योम _rtl88ee_fwlps_leave(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inps = false;
	u8 rpwm_val = 0, fw_pwrmode = FW_PS_ACTIVE_MODE;

	अगर (ppsc->low_घातer_enable) अणु
		rpwm_val = (FW_PS_STATE_ALL_ON_88E|FW_PS_ACK);/* RF on */
		_rtl88ee_set_fw_घड़ी_on(hw, rpwm_val, false);
		rtlhal->allow_sw_to_change_hwclc = false;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      &fw_pwrmode);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
	पूर्ण अन्यथा अणु
		rpwm_val = FW_PS_STATE_ALL_ON_88E;	/* RF on */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM, &rpwm_val);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      &fw_pwrmode);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
	पूर्ण
पूर्ण

अटल व्योम _rtl88ee_fwlps_enter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inps = true;
	u8 rpwm_val;

	अगर (ppsc->low_घातer_enable) अणु
		rpwm_val = FW_PS_STATE_RF_OFF_LOW_PWR_88E;	/* RF off */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      &ppsc->fwctrl_psmode);
		rtlhal->allow_sw_to_change_hwclc = true;
		_rtl88ee_set_fw_घड़ी_off(hw, rpwm_val);
	पूर्ण अन्यथा अणु
		rpwm_val = FW_PS_STATE_RF_OFF_88E;	/* RF off */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      &ppsc->fwctrl_psmode);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM, &rpwm_val);
	पूर्ण
पूर्ण

व्योम rtl88ee_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
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
		अवरोध; पूर्ण
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
		अवरोध; पूर्ण
	हाल HAL_DEF_WOWLAN:
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl88ee_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
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
				       *((u16 *)val));
		अवरोध;
	हाल HW_VAR_SLOT_TIME:अणु
		u8 e_aci;

		rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
			"HW_VAR_SLOT_TIME %x\n", val[0]);

		rtl_ग_लिखो_byte(rtlpriv, REG_SLOT, val[0]);

		क्रम (e_aci = 0; e_aci < AC_MAX; e_aci++) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      &e_aci);
		पूर्ण
		अवरोध;
		पूर्ण
	हाल HW_VAR_ACK_PREAMBLE:अणु
		u8 reg_पंचांगp;
		u8 लघु_preamble = (bool)*val;
		reg_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_TRXPTCL_CTL+2);
		अगर (लघु_preamble) अणु
			reg_पंचांगp |= 0x02;
			rtl_ग_लिखो_byte(rtlpriv, REG_TRXPTCL_CTL +
				       2, reg_पंचांगp);
		पूर्ण अन्यथा अणु
			reg_पंचांगp |= 0xFD;
			rtl_ग_लिखो_byte(rtlpriv, REG_TRXPTCL_CTL +
				       2, reg_पंचांगp);
		पूर्ण
		अवरोध; पूर्ण
	हाल HW_VAR_WPA_CONFIG:
		rtl_ग_लिखो_byte(rtlpriv, REG_SECCFG, *val);
		अवरोध;
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
		अवरोध; पूर्ण
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
		u8 regtoset_normal[4] = अणु 0x41, 0xa8, 0x72, 0xb9 पूर्ण;
		u8 factor_toset;
		u8 *p_regtoset = शून्य;
		u8 index = 0;

		p_regtoset = regtoset_normal;

		factor_toset = *val;
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
		अवरोध; पूर्ण
	हाल HW_VAR_AC_PARAM:अणु
		u8 e_aci = *val;
		rtl88e_dm_init_edca_turbo(hw);

		अगर (rtlpci->acm_method != EACMWAY2_SW)
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_ACM_CTRL,
						      &e_aci);
		अवरोध; पूर्ण
	हाल HW_VAR_ACM_CTRL:अणु
		u8 e_aci = *val;
		जोड़ aci_aअगरsn *p_aci_aअगरsn =
		    (जोड़ aci_aअगरsn *)(&(mac->ac[0].aअगरs));
		u8 acm = p_aci_aअगरsn->f.acm;
		u8 acm_ctrl = rtl_पढ़ो_byte(rtlpriv, REG_ACMHWCTRL);

		acm_ctrl = acm_ctrl |
			   ((rtlpci->acm_method == 2) ? 0x0 : 0x1);

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
		अवरोध; पूर्ण
	हाल HW_VAR_RCR:
		rtl_ग_लिखो_dword(rtlpriv, REG_RCR, ((u32 *)(val))[0]);
		rtlpci->receive_config = ((u32 *)(val))[0];
		अवरोध;
	हाल HW_VAR_RETRY_LIMIT:अणु
		u8 retry_limit = *val;

		rtl_ग_लिखो_word(rtlpriv, REG_RL,
			       retry_limit << RETRY_LIMIT_SHORT_SHIFT |
			       retry_limit << RETRY_LIMIT_LONG_SHIFT);
		अवरोध; पूर्ण
	हाल HW_VAR_DUAL_TSF_RST:
		rtl_ग_लिखो_byte(rtlpriv, REG_DUAL_TSF_RST, (BIT(0) | BIT(1)));
		अवरोध;
	हाल HW_VAR_EFUSE_BYTES:
		rtlefuse->efuse_usedbytes = *((u16 *)val);
		अवरोध;
	हाल HW_VAR_EFUSE_USAGE:
		rtlefuse->efuse_usedpercentage = *val;
		अवरोध;
	हाल HW_VAR_IO_CMD:
		rtl88e_phy_set_io_cmd(hw, (*(क्रमागत io_type *)val));
		अवरोध;
	हाल HW_VAR_SET_RPWM:अणु
		u8 rpwm_val;

		rpwm_val = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_HRPWM);
		udelay(1);

		अगर (rpwm_val & BIT(7)) अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_HRPWM, *val);
		पूर्ण अन्यथा अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_HRPWM, *val | BIT(7));
		पूर्ण
		अवरोध; पूर्ण
	हाल HW_VAR_H2C_FW_PWRMODE:
		rtl88e_set_fw_pwrmode_cmd(hw, *val);
		अवरोध;
	हाल HW_VAR_FW_PSMODE_STATUS:
		ppsc->fw_current_inpsmode = *((bool *)val);
		अवरोध;
	हाल HW_VAR_RESUME_CLK_ON:
		_rtl88ee_set_fw_ps_rf_on(hw);
		अवरोध;
	हाल HW_VAR_FW_LPS_ACTION:अणु
		bool enter_fwlps = *((bool *)val);

		अगर (enter_fwlps)
			_rtl88ee_fwlps_enter(hw);
		 अन्यथा
			_rtl88ee_fwlps_leave(hw);

		 अवरोध; पूर्ण
	हाल HW_VAR_H2C_FW_JOINBSSRPT:अणु
		u8 mstatus = *val;
		u8 पंचांगp_regcr, पंचांगp_reg422, bcnvalid_reg;
		u8 count = 0, dlbcn_count = 0;
		bool b_recover = false;

		अगर (mstatus == RT_MEDIA_CONNECT) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AID,
						      शून्य);

			पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
			rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1,
				       (पंचांगp_regcr | BIT(0)));

			_rtl88ee_set_bcn_ctrl_reg(hw, 0, BIT(3));
			_rtl88ee_set_bcn_ctrl_reg(hw, BIT(4), 0);

			पंचांगp_reg422 =
			    rtl_पढ़ो_byte(rtlpriv,
					  REG_FWHW_TXQ_CTRL + 2);
			rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2,
				       पंचांगp_reg422 & (~BIT(6)));
			अगर (पंचांगp_reg422 & BIT(6))
				b_recover = true;

			करो अणु
				bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv,
							     REG_TDECTRL+2);
				rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL+2,
					       (bcnvalid_reg | BIT(0)));
				_rtl88ee_वापस_beacon_queue_skb(hw);

				rtl88e_set_fw_rsvdpagepkt(hw, 0);
				bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv,
							     REG_TDECTRL+2);
				count = 0;
				जबतक (!(bcnvalid_reg & BIT(0)) && count < 20) अणु
					count++;
					udelay(10);
					bcnvalid_reg =
					  rtl_पढ़ो_byte(rtlpriv, REG_TDECTRL+2);
				पूर्ण
				dlbcn_count++;
			पूर्ण जबतक (!(bcnvalid_reg & BIT(0)) && dlbcn_count < 5);

			अगर (bcnvalid_reg & BIT(0))
				rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL+2, BIT(0));

			_rtl88ee_set_bcn_ctrl_reg(hw, BIT(3), 0);
			_rtl88ee_set_bcn_ctrl_reg(hw, 0, BIT(4));

			अगर (b_recover) अणु
				rtl_ग_लिखो_byte(rtlpriv,
					       REG_FWHW_TXQ_CTRL + 2,
					       पंचांगp_reg422);
			पूर्ण

			rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1,
				       (पंचांगp_regcr & ~(BIT(0))));
		पूर्ण
		rtl88e_set_fw_joinbss_report_cmd(hw, (*(u8 *)val));
		अवरोध; पूर्ण
	हाल HW_VAR_H2C_FW_P2P_PS_OFFLOAD:
		rtl88e_set_p2p_ps_offload_cmd(hw, *val);
		अवरोध;
	हाल HW_VAR_AID:अणु
		u16 u2bपंचांगp;

		u2bपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_BCN_PSR_RPT);
		u2bपंचांगp &= 0xC000;
		rtl_ग_लिखो_word(rtlpriv, REG_BCN_PSR_RPT, (u2bपंचांगp |
			       mac->assoc_id));
		अवरोध; पूर्ण
	हाल HW_VAR_CORRECT_TSF:अणु
		u8 btype_ibss = *val;

		अगर (btype_ibss)
			_rtl88ee_stop_tx_beacon(hw);

		_rtl88ee_set_bcn_ctrl_reg(hw, 0, BIT(3));

		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR,
				(u32)(mac->tsf & 0xffffffff));
		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR + 4,
				(u32)((mac->tsf >> 32) & 0xffffffff));

		_rtl88ee_set_bcn_ctrl_reg(hw, BIT(3), 0);

		अगर (btype_ibss)
			_rtl88ee_resume_tx_beacon(hw);
		अवरोध; पूर्ण
	हाल HW_VAR_KEEP_ALIVE: अणु
		u8 array[2];

		array[0] = 0xff;
		array[1] = *((u8 *)val);
		rtl88e_fill_h2c_cmd(hw, H2C_88E_KEEP_ALIVE_CTRL,
				    2, array);
		अवरोध; पूर्ण
	शेष:
		pr_err("switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool _rtl88ee_llt_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 address, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool status = true;
	दीर्घ count = 0;
	u32 value = _LLT_INIT_ADDR(address) | _LLT_INIT_DATA(data) |
		    _LLT_OP(_LLT_WRITE_ACCESS);

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

अटल bool _rtl88ee_llt_table_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अचिन्हित लघु i;
	u8 txpktbuf_bndy;
	u8 maxpage;
	bool status;

	maxpage = 0xAF;
	txpktbuf_bndy = 0xAB;

	rtl_ग_लिखो_byte(rtlpriv, REG_RQPN_NPQ, 0x01);
	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, 0x80730d29);

	/*0x2600   MaxRxBuff=10k-max(TxReportSize(64*8), WOLPattern(16*24)) */
	rtl_ग_लिखो_dword(rtlpriv, REG_TRXFF_BNDY, (0x25FF0000 | txpktbuf_bndy));
	rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 1, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, 0x45D, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_PBP, 0x11);
	rtl_ग_लिखो_byte(rtlpriv, REG_RX_DRVINFO_SZ, 0x4);

	क्रम (i = 0; i < (txpktbuf_bndy - 1); i++) अणु
		status = _rtl88ee_llt_ग_लिखो(hw, i, i + 1);
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl88ee_llt_ग_लिखो(hw, (txpktbuf_bndy - 1), 0xFF);
	अगर (!status)
		वापस status;

	क्रम (i = txpktbuf_bndy; i < maxpage; i++) अणु
		status = _rtl88ee_llt_ग_लिखो(hw, i, (i + 1));
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl88ee_llt_ग_लिखो(hw, maxpage, txpktbuf_bndy);
	अगर (!status)
		वापस status;

	वापस true;
पूर्ण

अटल व्योम _rtl88ee_gen_refresh_led_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;

	अगर (rtlpriv->rtlhal.up_first_समय)
		वापस;

	अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
		rtl88ee_sw_led_on(hw, pled0);
	अन्यथा अगर (ppsc->rfoff_reason == RF_CHANGE_BY_INIT)
		rtl88ee_sw_led_on(hw, pled0);
	अन्यथा
		rtl88ee_sw_led_off(hw, pled0);
पूर्ण

अटल bool _rtl88ee_init_mac(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	u8 byteपंचांगp;
	u16 wordपंचांगp;

	/*Disable XTAL OUTPUT क्रम घातer saving. YJ,add,111206. */
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_XCK_OUT_CTRL) & (~BIT(0));
	rtl_ग_लिखो_byte(rtlpriv, REG_XCK_OUT_CTRL, byteपंचांगp);
	/*Auto Power Down to CHIP-off State*/
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO + 1) & (~BIT(7));
	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO + 1, byteपंचांगp);

	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x00);
	/* HW Power on sequence */
	अगर (!rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK,
				      PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,
				      RTL8188EE_NIC_ENABLE_FLOW)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"init MAC Fail as rtl_hal_pwrseqcmdparsing\n");
		वापस false;
	पूर्ण

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO) | BIT(4);
	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO, byteपंचांगp);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_CTRL_REG+2);
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG+2, byteपंचांगp|BIT(2));

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_WATCH_DOG+1);
	rtl_ग_लिखो_byte(rtlpriv, REG_WATCH_DOG+1, byteपंचांगp|BIT(7));

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_AFE_XTAL_CTRL_EXT+1);
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_XTAL_CTRL_EXT+1, byteपंचांगp|BIT(1));

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_TX_RPT_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, REG_TX_RPT_CTRL, byteपंचांगp|BIT(1)|BIT(0));
	rtl_ग_लिखो_byte(rtlpriv, REG_TX_RPT_CTRL+1, 2);
	rtl_ग_लिखो_word(rtlpriv, REG_TX_RPT_TIME, 0xcdf0);

	/*Add क्रम wake up online*/
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CLKR);

	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_CLKR, byteपंचांगp|BIT(3));
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_MUXCFG+1);
	rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG+1, (byteपंचांगp & (~BIT(4))));
	rtl_ग_लिखो_byte(rtlpriv, 0x367, 0x80);

	rtl_ग_लिखो_word(rtlpriv, REG_CR, 0x2ff);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR+1, 0x06);
	rtl_ग_लिखो_byte(rtlpriv, MSR, 0x00);

	अगर (!rtlhal->mac_func_enable) अणु
		अगर (!_rtl88ee_llt_table_init(hw)) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"LLT table init fail\n");
			वापस false;
		पूर्ण
	पूर्ण
	rtl_ग_लिखो_dword(rtlpriv, REG_HISR, 0xffffffff);
	rtl_ग_लिखो_dword(rtlpriv, REG_HISRE, 0xffffffff);

	wordपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_TRXDMA_CTRL);
	wordपंचांगp &= 0xf;
	wordपंचांगp |= 0xE771;
	rtl_ग_लिखो_word(rtlpriv, REG_TRXDMA_CTRL, wordपंचांगp);

	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);
	rtl_ग_लिखो_word(rtlpriv, REG_RXFLTMAP2, 0xffff);
	rtl_ग_लिखो_dword(rtlpriv, REG_TCR, rtlpci->transmit_config);

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

	/* अगर we want to support 64 bit DMA, we should set it here,
	 * but now we करो not support 64 bit DMA
	 */
	rtl_ग_लिखो_dword(rtlpriv, REG_INT_MIG, 0);

	rtl_ग_लिखो_dword(rtlpriv, REG_MCUTST_1, 0x0);
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG+1, 0);/*Enable RX DMA */

	अगर (rtlhal->earlymode_enable) अणु/*Early mode enable*/
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_EARLY_MODE_CONTROL);
		byteपंचांगp |= 0x1f;
		rtl_ग_लिखो_byte(rtlpriv, REG_EARLY_MODE_CONTROL, byteपंचांगp);
		rtl_ग_लिखो_byte(rtlpriv, REG_EARLY_MODE_CONTROL+3, 0x81);
	पूर्ण
	_rtl88ee_gen_refresh_led_state(hw);
	वापस true;
पूर्ण

अटल व्योम _rtl88ee_hw_configure(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 reg_prsr;

	reg_prsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;

	rtl_ग_लिखो_dword(rtlpriv, REG_RRSR, reg_prsr);
	rtl_ग_लिखो_byte(rtlpriv, REG_HWSEQ_CTRL, 0xFF);
पूर्ण

अटल व्योम _rtl88ee_enable_aspm_back_करोor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 पंचांगp1byte = 0;
	u32 पंचांगp4byte = 0, count = 0;

	rtl_ग_लिखो_word(rtlpriv, 0x354, 0x8104);
	rtl_ग_लिखो_word(rtlpriv, 0x358, 0x24);

	rtl_ग_लिखो_word(rtlpriv, 0x350, 0x70c);
	rtl_ग_लिखो_byte(rtlpriv, 0x352, 0x2);
	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, 0x352);
	count = 0;
	जबतक (पंचांगp1byte && count < 20) अणु
		udelay(10);
		पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, 0x352);
		count++;
	पूर्ण
	अगर (0 == पंचांगp1byte) अणु
		पंचांगp4byte = rtl_पढ़ो_dword(rtlpriv, 0x34c);
		rtl_ग_लिखो_dword(rtlpriv, 0x348, पंचांगp4byte|BIT(31));
		rtl_ग_लिखो_word(rtlpriv, 0x350, 0xf70c);
		rtl_ग_लिखो_byte(rtlpriv, 0x352, 0x1);
	पूर्ण

	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, 0x352);
	count = 0;
	जबतक (पंचांगp1byte && count < 20) अणु
		udelay(10);
		पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, 0x352);
		count++;
	पूर्ण

	rtl_ग_लिखो_word(rtlpriv, 0x350, 0x718);
	rtl_ग_लिखो_byte(rtlpriv, 0x352, 0x2);
	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, 0x352);
	count = 0;
	जबतक (पंचांगp1byte && count < 20) अणु
		udelay(10);
		पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, 0x352);
		count++;
	पूर्ण

	अगर (ppsc->support_backकरोor || (0 == पंचांगp1byte)) अणु
		पंचांगp4byte = rtl_पढ़ो_dword(rtlpriv, 0x34c);
		rtl_ग_लिखो_dword(rtlpriv, 0x348, पंचांगp4byte|BIT(11)|BIT(12));
		rtl_ग_लिखो_word(rtlpriv, 0x350, 0xf718);
		rtl_ग_लिखो_byte(rtlpriv, 0x352, 0x1);
	पूर्ण

	पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, 0x352);
	count = 0;
	जबतक (पंचांगp1byte && count < 20) अणु
		udelay(10);
		पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, 0x352);
		count++;
	पूर्ण
पूर्ण

व्योम rtl88ee_enable_hw_security_config(काष्ठा ieee80211_hw *hw)
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

पूर्णांक rtl88ee_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	bool rtstatus;
	पूर्णांक err = 0;
	u8 पंचांगp_u1b, u1byte;
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

	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CLKR+1);
	u1byte = rtl_पढ़ो_byte(rtlpriv, REG_CR);
	अगर ((पंचांगp_u1b & BIT(3)) && (u1byte != 0 && u1byte != 0xEA)) अणु
		rtlhal->mac_func_enable = true;
	पूर्ण अन्यथा अणु
		rtlhal->mac_func_enable = false;
		rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON_88E;
	पूर्ण

	rtstatus = _rtl88ee_init_mac(hw);
	अगर (!rtstatus) अणु
		pr_info("Init MAC failed\n");
		err = 1;
		जाओ निकास;
	पूर्ण

	err = rtl88e_करोwnload_fw(hw, false);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Failed to download FW. Init HW without FW now..\n");
		err = 1;
		जाओ निकास;
	पूर्ण
	rtlhal->fw_पढ़ोy = true;
	/*fw related variable initialize */
	rtlhal->last_hmeboxnum = 0;
	rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON_88E;
	rtlhal->fw_clk_change_in_progress = false;
	rtlhal->allow_sw_to_change_hwclc = false;
	ppsc->fw_current_inpsmode = false;

	rtl88e_phy_mac_config(hw);
	/* because last function modअगरy RCR, so we update
	 * rcr var here, or TP will unstable क्रम receive_config
	 * is wrong, RX RCR_ACRC32 will cause TP unstabel & Rx
	 * RCR_APP_ICV will cause mac80211 unassoc क्रम cisco 1252
	 */
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);

	rtl88e_phy_bb_config(hw);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);

	rtlphy->rf_mode = RF_OP_BY_SW_3WIRE;
	rtl88e_phy_rf_config(hw);

	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, (क्रमागत radio_path)0,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[0] = rtlphy->rfreg_chnlval[0] & 0xfff00fff;

	_rtl88ee_hw_configure(hw);
	rtl_cam_reset_all_entry(hw);
	rtl88ee_enable_hw_security_config(hw);

	rtlhal->mac_func_enable = true;
	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	_rtl88ee_enable_aspm_back_करोor(hw);
	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);

	अगर (ppsc->rfpwr_state == ERFON) अणु
		अगर ((rtlefuse->antenna_भाग_प्रकारype == CGCS_RX_HW_ANTDIV) ||
		    ((rtlefuse->antenna_भाग_प्रकारype == CG_TRX_HW_ANTDIV) &&
		     (rtlhal->oem_id == RT_CID_819X_HP))) अणु
			rtl88e_phy_set_rfpath_चयन(hw, true);
			rtlpriv->dm.fat_table.rx_idle_ant = MAIN_ANT;
		पूर्ण अन्यथा अणु
			rtl88e_phy_set_rfpath_चयन(hw, false);
			rtlpriv->dm.fat_table.rx_idle_ant = AUX_ANT;
		पूर्ण
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "rx idle ant %s\n",
			(rtlpriv->dm.fat_table.rx_idle_ant == MAIN_ANT) ?
			("MAIN_ANT") : ("AUX_ANT"));

		अगर (rtlphy->iqk_initialized) अणु
			rtl88e_phy_iq_calibrate(hw, true);
		पूर्ण अन्यथा अणु
			rtl88e_phy_iq_calibrate(hw, false);
			rtlphy->iqk_initialized = true;
		पूर्ण

		rtl88e_dm_check_txघातer_tracking(hw);
		rtl88e_phy_lc_calibrate(hw);
	पूर्ण

	पंचांगp_u1b = efuse_पढ़ो_1byte(hw, 0x1FA);
	अगर (!(पंचांगp_u1b & BIT(0))) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0F, 0x05);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "PA BIAS path A\n");
	पूर्ण

	अगर (!(पंचांगp_u1b & BIT(4))) अणु
		पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, 0x16);
		पंचांगp_u1b &= 0x0F;
		rtl_ग_लिखो_byte(rtlpriv, 0x16, पंचांगp_u1b | 0x80);
		udelay(10);
		rtl_ग_लिखो_byte(rtlpriv, 0x16, पंचांगp_u1b | 0x90);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "under 1.5V\n");
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, REG_NAV_CTRL+2,  ((30000+127)/128));
	rtl88e_dm_init(hw);
निकास:
	local_irq_restore(flags);
	rtlpriv->rtlhal.being_init_adapter = false;
	वापस err;
पूर्ण

अटल क्रमागत version_8188e _rtl88ee_पढ़ो_chip_version(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	क्रमागत version_8188e version = VERSION_UNKNOWN;
	u32 value32;

	value32 = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG);
	अगर (value32 & TRP_VAUX_EN) अणु
		version = (क्रमागत version_8188e) VERSION_TEST_CHIP_88E;
	पूर्ण अन्यथा अणु
		version = NORMAL_CHIP;
		version = version | ((value32 & TYPE_ID) ? RF_TYPE_2T2R : 0);
		version = version | ((value32 & VENDOR_ID) ?
			  CHIP_VENDOR_UMC : 0);
	पूर्ण

	rtlphy->rf_type = RF_1T1R;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Chip RF Type: %s\n", (rtlphy->rf_type == RF_2T2R) ?
		"RF_2T2R" : "RF_1T1R");

	वापस version;
पूर्ण

अटल पूर्णांक _rtl88ee_set_media_status(काष्ठा ieee80211_hw *hw,
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
		_rtl88ee_stop_tx_beacon(hw);
		_rtl88ee_enable_bcn_sub_func(hw);
	पूर्ण अन्यथा अगर (mode == MSR_ADHOC || mode == MSR_AP) अणु
		_rtl88ee_resume_tx_beacon(hw);
		_rtl88ee_disable_bcn_sub_func(hw);
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

व्योम rtl88ee_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid)
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
		_rtl88ee_set_bcn_ctrl_reg(hw, 0, BIT(4));
	पूर्ण अन्यथा अगर (!check_bssid) अणु
		reg_rcr &= (~(RCR_CBSSID_DATA | RCR_CBSSID_BCN));
		_rtl88ee_set_bcn_ctrl_reg(hw, BIT(4), 0);
		rtlpriv->cfg->ops->set_hw_reg(hw,
			HW_VAR_RCR, (u8 *)(&reg_rcr));
	पूर्ण

पूर्ण

पूर्णांक rtl88ee_set_network_type(काष्ठा ieee80211_hw *hw,
			     क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (_rtl88ee_set_media_status(hw, type))
		वापस -EOPNOTSUPP;

	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		अगर (type != NL80211_IFTYPE_AP &&
		    type != NL80211_IFTYPE_MESH_POINT)
			rtl88ee_set_check_bssid(hw, true);
	पूर्ण अन्यथा अणु
		rtl88ee_set_check_bssid(hw, false);
	पूर्ण

	वापस 0;
पूर्ण

/* करोn't set REG_EDCA_BE_PARAM here
 * because mac80211 will send pkt when scan
 */
व्योम rtl88ee_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	rtl88e_dm_init_edca_turbo(hw);
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
		WARN_ONCE(true, "rtl8188ee: invalid aci: %d !\n", aci);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl88ee_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR,
			rtlpci->irq_mask[0] & 0xFFFFFFFF);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE,
			rtlpci->irq_mask[1] & 0xFFFFFFFF);
	rtlpci->irq_enabled = true;
	/* there are some C2H CMDs have been sent
	 * beक्रमe प्रणाली पूर्णांकerrupt is enabled, e.g., C2H, CPWM.
	 * So we need to clear all C2H events that FW has notअगरied,
	 * otherwise FW won't schedule any commands anymore.
	 */
	rtl_ग_लिखो_byte(rtlpriv, REG_C2HEVT_CLEAR, 0);
	/*enable प्रणाली पूर्णांकerrupt*/
	rtl_ग_लिखो_dword(rtlpriv, REG_HSIMR,
			rtlpci->sys_irq_mask & 0xFFFFFFFF);
पूर्ण

व्योम rtl88ee_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, IMR_DISABLED);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, IMR_DISABLED);
	rtlpci->irq_enabled = false;
	/*synchronize_irq(rtlpci->pdev->irq);*/
पूर्ण

अटल व्योम _rtl88ee_घातeroff_adapter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 u1b_पंचांगp;
	u32 count = 0;
	rtlhal->mac_func_enable = false;
	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "POWER OFF adapter\n");
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_TX_RPT_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, REG_TX_RPT_CTRL, u1b_पंचांगp & (~BIT(1)));

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
	जबतक (!(u1b_पंचांगp & BIT(1)) && (count++ < 100)) अणु
		udelay(10);
		u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
		count++;
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG+1, 0xFF);

	rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
				 PWR_INTF_PCI_MSK,
				 RTL8188EE_NIC_LPS_ENTER_FLOW);

	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, 0x00);

	अगर ((rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL) & BIT(7)) && rtlhal->fw_पढ़ोy)
		rtl88e_firmware_selfreset(hw);

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN+1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, (u1b_पंचांगp & (~BIT(2))));
	rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0x00);

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_32K_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, REG_32K_CTRL, (u1b_पंचांगp & (~BIT(0))));

	rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
				 PWR_INTF_PCI_MSK, RTL8188EE_NIC_DISABLE_FLOW);

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL+1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL+1, (u1b_पंचांगp & (~BIT(3))));
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL+1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL+1, (u1b_पंचांगp | BIT(3)));

	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0E);

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, GPIO_IN);
	rtl_ग_लिखो_byte(rtlpriv, GPIO_OUT, u1b_पंचांगp);
	rtl_ग_लिखो_byte(rtlpriv, GPIO_IO_SEL, 0x7F);

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_IO_SEL);
	rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_IO_SEL, (u1b_पंचांगp << 4) | u1b_पंचांगp);
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_IO_SEL+1);
	rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_IO_SEL+1, u1b_पंचांगp | 0x0F);

	rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_IO_SEL_2+2, 0x00080808);
पूर्ण

व्योम rtl88ee_card_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	क्रमागत nl80211_अगरtype opmode;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "RTL8188ee card disable\n");

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;

	_rtl88ee_set_media_status(hw, opmode);

	अगर (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);

	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
	_rtl88ee_घातeroff_adapter(hw);

	/* after घातer off we should करो iqk again */
	rtlpriv->phy.iqk_initialized = false;
पूर्ण

व्योम rtl88ee_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_पूर्णांक *पूर्णांकvec)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	पूर्णांकvec->पूर्णांकa = rtl_पढ़ो_dword(rtlpriv, ISR) & rtlpci->irq_mask[0];
	rtl_ग_लिखो_dword(rtlpriv, ISR, पूर्णांकvec->पूर्णांकa);

	पूर्णांकvec->पूर्णांकb = rtl_पढ़ो_dword(rtlpriv, REG_HISRE) & rtlpci->irq_mask[1];
	rtl_ग_लिखो_dword(rtlpriv, REG_HISRE, पूर्णांकvec->पूर्णांकb);

पूर्ण

व्योम rtl88ee_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u16 bcn_पूर्णांकerval, atim_winकरोw;

	bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;
	atim_winकरोw = 2;	/*FIX MERGE */
	rtl88ee_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_ATIMWND, atim_winकरोw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl_ग_लिखो_word(rtlpriv, REG_BCNTCFG, 0x660f);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_CCK, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, 0x606, 0x30);
	rtlpci->reg_bcn_ctrl_val |= BIT(3);
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8) rtlpci->reg_bcn_ctrl_val);
	/*rtl88ee_enable_पूर्णांकerrupt(hw);*/
पूर्ण

व्योम rtl88ee_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;

	rtl_dbg(rtlpriv, COMP_BEACON, DBG_DMESG,
		"beacon_interval:%d\n", bcn_पूर्णांकerval);
	/*rtl88ee_disable_पूर्णांकerrupt(hw);*/
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	/*rtl88ee_enable_पूर्णांकerrupt(hw);*/
पूर्ण

व्योम rtl88ee_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
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
	rtl88ee_disable_पूर्णांकerrupt(hw);
	rtl88ee_enable_पूर्णांकerrupt(hw);
पूर्ण

अटल u8 _rtl88e_get_chnl_group(u8 chnl)
अणु
	u8 group = 0;

	अगर (chnl < 3)
		group = 0;
	अन्यथा अगर (chnl < 6)
		group = 1;
	अन्यथा अगर (chnl < 9)
		group = 2;
	अन्यथा अगर (chnl < 12)
		group = 3;
	अन्यथा अगर (chnl < 14)
		group = 4;
	अन्यथा अगर (chnl == 14)
		group = 5;

	वापस group;
पूर्ण

अटल व्योम set_24g_base(काष्ठा txघातer_info_2g *pwrinfo24g, u32 rfpath)
अणु
	पूर्णांक group, txcnt;

	क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) अणु
		pwrinfo24g->index_cck_base[rfpath][group] = 0x2D;
		pwrinfo24g->index_bw40_base[rfpath][group] = 0x2D;
	पूर्ण
	क्रम (txcnt = 0; txcnt < MAX_TX_COUNT; txcnt++) अणु
		अगर (txcnt == 0) अणु
			pwrinfo24g->bw20_dअगरf[rfpath][0] = 0x02;
			pwrinfo24g->ofdm_dअगरf[rfpath][0] = 0x04;
		पूर्ण अन्यथा अणु
			pwrinfo24g->bw20_dअगरf[rfpath][txcnt] = 0xFE;
			pwrinfo24g->bw40_dअगरf[rfpath][txcnt] = 0xFE;
			pwrinfo24g->cck_dअगरf[rfpath][txcnt] =	0xFE;
			pwrinfo24g->ofdm_dअगरf[rfpath][txcnt] = 0xFE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_घातer_value_fromprom(काष्ठा ieee80211_hw *hw,
				      काष्ठा txघातer_info_2g *pwrinfo24g,
				      काष्ठा txघातer_info_5g *pwrinfo5g,
				      bool स्वतःload_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 rfpath, eeaddr = EEPROM_TX_PWR_INX, group, txcnt = 0;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"hal_ReadPowerValueFromPROM88E():PROMContent[0x%x]=0x%x\n",
		(eeaddr + 1), hwinfo[eeaddr + 1]);
	अगर (0xFF == hwinfo[eeaddr+1])  /*YJ,add,120316*/
		स्वतःload_fail = true;

	अगर (स्वतःload_fail) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"auto load fail : Use Default value!\n");
		क्रम (rfpath = 0 ; rfpath < MAX_RF_PATH ; rfpath++) अणु
			/* 2.4G शेष value */
			set_24g_base(pwrinfo24g, rfpath);
		पूर्ण
		वापस;
	पूर्ण

	क्रम (rfpath = 0 ; rfpath < MAX_RF_PATH ; rfpath++) अणु
		/*2.4G शेष value*/
		क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) अणु
			pwrinfo24g->index_cck_base[rfpath][group] =
			  hwinfo[eeaddr++];
			अगर (pwrinfo24g->index_cck_base[rfpath][group] == 0xFF)
				pwrinfo24g->index_cck_base[rfpath][group] =
				  0x2D;
		पूर्ण
		क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G-1; group++) अणु
			pwrinfo24g->index_bw40_base[rfpath][group] =
				hwinfo[eeaddr++];
			अगर (pwrinfo24g->index_bw40_base[rfpath][group] == 0xFF)
				pwrinfo24g->index_bw40_base[rfpath][group] =
					0x2D;
		पूर्ण
		pwrinfo24g->bw40_dअगरf[rfpath][0] = 0;
		अगर (hwinfo[eeaddr] == 0xFF) अणु
			pwrinfo24g->bw20_dअगरf[rfpath][0] = 0x02;
		पूर्ण अन्यथा अणु
			pwrinfo24g->bw20_dअगरf[rfpath][0] =
				(hwinfo[eeaddr]&0xf0)>>4;
			/*bit sign number to 8 bit sign number*/
			अगर (pwrinfo24g->bw20_dअगरf[rfpath][0] & BIT(3))
				pwrinfo24g->bw20_dअगरf[rfpath][0] |= 0xF0;
		पूर्ण

		अगर (hwinfo[eeaddr] == 0xFF) अणु
			pwrinfo24g->ofdm_dअगरf[rfpath][0] = 0x04;
		पूर्ण अन्यथा अणु
			pwrinfo24g->ofdm_dअगरf[rfpath][0] =
				(hwinfo[eeaddr]&0x0f);
				/*bit sign number to 8 bit sign number*/
			अगर (pwrinfo24g->ofdm_dअगरf[rfpath][0] & BIT(3))
				pwrinfo24g->ofdm_dअगरf[rfpath][0] |= 0xF0;
		पूर्ण
		pwrinfo24g->cck_dअगरf[rfpath][0] = 0;
		eeaddr++;
		क्रम (txcnt = 1; txcnt < MAX_TX_COUNT; txcnt++) अणु
			अगर (hwinfo[eeaddr] == 0xFF) अणु
				pwrinfo24g->bw40_dअगरf[rfpath][txcnt] = 0xFE;
			पूर्ण अन्यथा अणु
				pwrinfo24g->bw40_dअगरf[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0xf0)>>4;
				अगर (pwrinfo24g->bw40_dअगरf[rfpath][txcnt] &
				    BIT(3))
					pwrinfo24g->bw40_dअगरf[rfpath][txcnt] |=
					  0xF0;
			पूर्ण

			अगर (hwinfo[eeaddr] == 0xFF) अणु
				pwrinfo24g->bw20_dअगरf[rfpath][txcnt] =
					0xFE;
			पूर्ण अन्यथा अणु
				pwrinfo24g->bw20_dअगरf[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0x0f);
				अगर (pwrinfo24g->bw20_dअगरf[rfpath][txcnt] &
				    BIT(3))
					pwrinfo24g->bw20_dअगरf[rfpath][txcnt] |=
					  0xF0;
			पूर्ण
			eeaddr++;

			अगर (hwinfo[eeaddr] == 0xFF) अणु
				pwrinfo24g->ofdm_dअगरf[rfpath][txcnt] = 0xFE;
			पूर्ण अन्यथा अणु
				pwrinfo24g->ofdm_dअगरf[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0xf0)>>4;
				अगर (pwrinfo24g->ofdm_dअगरf[rfpath][txcnt] &
				    BIT(3))
					pwrinfo24g->ofdm_dअगरf[rfpath][txcnt] |=
					  0xF0;
			पूर्ण

			अगर (hwinfo[eeaddr] == 0xFF) अणु
				pwrinfo24g->cck_dअगरf[rfpath][txcnt] =	0xFE;
			पूर्ण अन्यथा अणु
				pwrinfo24g->cck_dअगरf[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0x0f);
				अगर (pwrinfo24g->cck_dअगरf[rfpath][txcnt] &
				    BIT(3))
					pwrinfo24g->cck_dअगरf[rfpath][txcnt] |=
					  0xF0;
			पूर्ण
			eeaddr++;
		पूर्ण

		/*5G शेष value*/
		क्रम (group = 0 ; group < MAX_CHNL_GROUP_5G; group++) अणु
			pwrinfo5g->index_bw40_base[rfpath][group] =
				hwinfo[eeaddr++];
			अगर (pwrinfo5g->index_bw40_base[rfpath][group] == 0xFF)
				pwrinfo5g->index_bw40_base[rfpath][group] =
				  0xFE;
		पूर्ण

		pwrinfo5g->bw40_dअगरf[rfpath][0] = 0;

		अगर (hwinfo[eeaddr] == 0xFF) अणु
			pwrinfo5g->bw20_dअगरf[rfpath][0] = 0;
		पूर्ण अन्यथा अणु
			pwrinfo5g->bw20_dअगरf[rfpath][0] =
			  (hwinfo[eeaddr]&0xf0)>>4;
			अगर (pwrinfo5g->bw20_dअगरf[rfpath][0] & BIT(3))
				pwrinfo5g->bw20_dअगरf[rfpath][0] |= 0xF0;
		पूर्ण

		अगर (hwinfo[eeaddr] == 0xFF) अणु
			pwrinfo5g->ofdm_dअगरf[rfpath][0] = 0x04;
		पूर्ण अन्यथा अणु
			pwrinfo5g->ofdm_dअगरf[rfpath][0] = (hwinfo[eeaddr]&0x0f);
			अगर (pwrinfo5g->ofdm_dअगरf[rfpath][0] & BIT(3))
				pwrinfo5g->ofdm_dअगरf[rfpath][0] |= 0xF0;
		पूर्ण
		eeaddr++;
		क्रम (txcnt = 1; txcnt < MAX_TX_COUNT; txcnt++) अणु
			अगर (hwinfo[eeaddr] == 0xFF) अणु
				pwrinfo5g->bw40_dअगरf[rfpath][txcnt] =	0xFE;
			पूर्ण अन्यथा अणु
				pwrinfo5g->bw40_dअगरf[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0xf0)>>4;
				अगर (pwrinfo5g->bw40_dअगरf[rfpath][txcnt] &
				    BIT(3))
					pwrinfo5g->bw40_dअगरf[rfpath][txcnt] |=
					  0xF0;
			पूर्ण

			अगर (hwinfo[eeaddr] == 0xFF) अणु
				pwrinfo5g->bw20_dअगरf[rfpath][txcnt] =	0xFE;
			पूर्ण अन्यथा अणु
				pwrinfo5g->bw20_dअगरf[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0x0f);
				अगर (pwrinfo5g->bw20_dअगरf[rfpath][txcnt] &
				    BIT(3))
					pwrinfo5g->bw20_dअगरf[rfpath][txcnt] |=
					  0xF0;
			पूर्ण
			eeaddr++;
		पूर्ण

		अगर (hwinfo[eeaddr] == 0xFF) अणु
			pwrinfo5g->ofdm_dअगरf[rfpath][1] = 0xFE;
			pwrinfo5g->ofdm_dअगरf[rfpath][2] = 0xFE;
		पूर्ण अन्यथा अणु
			pwrinfo5g->ofdm_dअगरf[rfpath][1] =
					(hwinfo[eeaddr]&0xf0)>>4;
			pwrinfo5g->ofdm_dअगरf[rfpath][2] =
					(hwinfo[eeaddr]&0x0f);
		पूर्ण
		eeaddr++;

		अगर (hwinfo[eeaddr] == 0xFF)
			pwrinfo5g->ofdm_dअगरf[rfpath][3] = 0xFE;
		अन्यथा
			pwrinfo5g->ofdm_dअगरf[rfpath][3] = (hwinfo[eeaddr]&0x0f);
		eeaddr++;

		क्रम (txcnt = 1; txcnt < MAX_TX_COUNT; txcnt++) अणु
			अगर (pwrinfo5g->ofdm_dअगरf[rfpath][txcnt] == 0xFF)
				pwrinfo5g->ofdm_dअगरf[rfpath][txcnt] =	0xFE;
			अन्यथा अगर (pwrinfo5g->ofdm_dअगरf[rfpath][txcnt] & BIT(3))
				pwrinfo5g->ofdm_dअगरf[rfpath][txcnt] |= 0xF0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl88ee_पढ़ो_txघातer_info_from_hwpg(काष्ठा ieee80211_hw *hw,
						 bool स्वतःload_fail,
						 u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा txघातer_info_2g pwrinfo24g;
	काष्ठा txघातer_info_5g pwrinfo5g;
	u8 rf_path, index;
	u8 i;

	पढ़ो_घातer_value_fromprom(hw, &pwrinfo24g,
				  &pwrinfo5g, स्वतःload_fail, hwinfo);

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 14; i++) अणु
			index = _rtl88e_get_chnl_group(i+1);

			rtlefuse->txpwrlevel_cck[rf_path][i] =
				pwrinfo24g.index_cck_base[rf_path][index];
			rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
				pwrinfo24g.index_bw40_base[rf_path][index];
			rtlefuse->txpwr_ht20dअगरf[rf_path][i] =
				pwrinfo24g.bw20_dअगरf[rf_path][0];
			rtlefuse->txpwr_legacyhtdअगरf[rf_path][i] =
				pwrinfo24g.ofdm_dअगरf[rf_path][0];
		पूर्ण

		क्रम (i = 0; i < 14; i++) अणु
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF(%d)-Ch(%d) [CCK / HT40_1S ] = [0x%x / 0x%x ]\n",
				rf_path, i,
				rtlefuse->txpwrlevel_cck[rf_path][i],
				rtlefuse->txpwrlevel_ht40_1s[rf_path][i]);
		पूर्ण
	पूर्ण

	अगर (!स्वतःload_fail)
		rtlefuse->eeprom_thermalmeter =
			hwinfo[EEPROM_THERMAL_METER_88E];
	अन्यथा
		rtlefuse->eeprom_thermalmeter = EEPROM_DEFAULT_THERMALMETER;

	अगर (rtlefuse->eeprom_thermalmeter == 0xff || स्वतःload_fail) अणु
		rtlefuse->apk_thermalmeterignore = true;
		rtlefuse->eeprom_thermalmeter = EEPROM_DEFAULT_THERMALMETER;
	पूर्ण

	rtlefuse->thermalmeter[0] = rtlefuse->eeprom_thermalmeter;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"thermalmeter = 0x%x\n", rtlefuse->eeprom_thermalmeter);

	अगर (!स्वतःload_fail) अणु
		rtlefuse->eeprom_regulatory =
			hwinfo[EEPROM_RF_BOARD_OPTION_88E] & 0x07;/*bit0~2*/
		अगर (hwinfo[EEPROM_RF_BOARD_OPTION_88E] == 0xFF)
			rtlefuse->eeprom_regulatory = 0;
	पूर्ण अन्यथा अणु
		rtlefuse->eeprom_regulatory = 0;
	पूर्ण
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"eeprom_regulatory = 0x%x\n", rtlefuse->eeprom_regulatory);
पूर्ण

अटल व्योम _rtl88ee_पढ़ो_adapter_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक params[] = अणुRTL8188E_EEPROM_ID, EEPROM_VID, EEPROM_DID,
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
	_rtl88ee_पढ़ो_txघातer_info_from_hwpg(hw,
					     rtlefuse->स्वतःload_failflag,
					     hwinfo);
	rtlefuse->txpwr_fromeprom = true;

	rtl8188ee_पढ़ो_bt_coexist_info_from_hwpg(hw,
						 rtlefuse->स्वतःload_failflag,
						 hwinfo);

	/*board type*/
	rtlefuse->board_type =
		((hwinfo[EEPROM_RF_BOARD_OPTION_88E] & 0xE0) >> 5);
	rtlhal->board_type = rtlefuse->board_type;
	/*Wake on wlan*/
	rtlefuse->wowlan_enable =
		((hwinfo[EEPROM_RF_FEATURE_OPTION_88E] & 0x40) >> 6);
	/*parse xtal*/
	rtlefuse->crystalcap = hwinfo[EEPROM_XTAL_88E];
	अगर (hwinfo[EEPROM_XTAL_88E])
		rtlefuse->crystalcap = 0x20;
	/*antenna भागersity*/
	rtlefuse->antenna_भाग_cfg =
		(hwinfo[EEPROM_RF_BOARD_OPTION_88E] & 0x18) >> 3;
	अगर (hwinfo[EEPROM_RF_BOARD_OPTION_88E] == 0xFF)
		rtlefuse->antenna_भाग_cfg = 0;
	अगर (rtlpriv->btcoexist.eeprom_bt_coexist != 0 &&
	    rtlpriv->btcoexist.eeprom_bt_ant_num == ANT_X1)
		rtlefuse->antenna_भाग_cfg = 0;

	rtlefuse->antenna_भाग_प्रकारype = hwinfo[EEPROM_RF_ANTENNA_OPT_88E];
	अगर (rtlefuse->antenna_भाग_प्रकारype == 0xFF)
		rtlefuse->antenna_भाग_प्रकारype = 0x01;
	अगर (rtlefuse->antenna_भाग_प्रकारype == CG_TRX_HW_ANTDIV ||
		rtlefuse->antenna_भाग_प्रकारype == CGCS_RX_HW_ANTDIV)
		rtlefuse->antenna_भाग_cfg = 1;

	अगर (rtlhal->oem_id == RT_CID_DEFAULT) अणु
		चयन (rtlefuse->eeprom_oemid) अणु
		हाल EEPROM_CID_DEFAULT:
			अगर (rtlefuse->eeprom_did == 0x8179) अणु
				अगर (rtlefuse->eeprom_svid == 0x1025) अणु
					rtlhal->oem_id = RT_CID_819X_ACER;
				पूर्ण अन्यथा अगर ((rtlefuse->eeprom_svid == 0x10EC &&
				     rtlefuse->eeprom_smid == 0x0179) ||
				     (rtlefuse->eeprom_svid == 0x17AA &&
				     rtlefuse->eeprom_smid == 0x0179)) अणु
					rtlhal->oem_id = RT_CID_819X_LENOVO;
				पूर्ण अन्यथा अगर (rtlefuse->eeprom_svid == 0x103c &&
					   rtlefuse->eeprom_smid == 0x197d) अणु
					rtlhal->oem_id = RT_CID_819X_HP;
				पूर्ण अन्यथा अणु
					rtlhal->oem_id = RT_CID_DEFAULT;
				पूर्ण
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

अटल व्योम _rtl88ee_hal_customized_behavior(काष्ठा ieee80211_hw *hw)
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

व्योम rtl88ee_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_u1b;

	rtlhal->version = _rtl88ee_पढ़ो_chip_version(hw);
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
		_rtl88ee_पढ़ो_adapter_info(hw);
	पूर्ण अन्यथा अणु
		pr_err("Autoload ERR!!\n");
	पूर्ण
	_rtl88ee_hal_customized_behavior(hw);
पूर्ण

अटल व्योम rtl88ee_update_hal_rate_table(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 ratr_value;
	u8 ratr_index = 0;
	u8 b_nmode = mac->ht_enable;
	/*u8 mimo_ps = IEEE80211_SMPS_OFF;*/
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

अटल व्योम rtl88ee_update_hal_rate_mask(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw)
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
	bool b_लघुgi = false;
	u8 rate_mask[5];
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
					ratr_biपंचांगap &= 0x0f8f0000;
				अन्यथा अगर (rssi_level == 2)
					ratr_biपंचांगap &= 0x0f8ff000;
				अन्यथा
					ratr_biपंचांगap &= 0x0f8ff015;
			पूर्ण अन्यथा अणु
				अगर (rssi_level == 1)
					ratr_biपंचांगap &= 0x0f8f0000;
				अन्यथा अगर (rssi_level == 2)
					ratr_biपंचांगap &= 0x0f8ff000;
				अन्यथा
					ratr_biपंचांगap &= 0x0f8ff005;
			पूर्ण
		पूर्ण
		/*पूर्ण*/

		अगर ((curtxbw_40mhz && curलघुgi_40mhz) ||
		    (!curtxbw_40mhz && curलघुgi_20mhz)) अणु

			अगर (macid == 0)
				b_लघुgi = true;
			अन्यथा अगर (macid == 1)
				b_लघुgi = false;
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
	rate_mask[4] = macid | (b_लघुgi ? 0x20 : 0x00) | 0x80;
	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"Rate_index:%x, ratr_val:%x, %x:%x:%x:%x:%x\n",
		ratr_index, ratr_biपंचांगap,
		rate_mask[0], rate_mask[1],
		rate_mask[2], rate_mask[3],
		rate_mask[4]);
	rtl88e_fill_h2c_cmd(hw, H2C_88E_RA_MASK, 5, rate_mask);
	_rtl88ee_set_bcn_ctrl_reg(hw, BIT(3), 0);
पूर्ण

व्योम rtl88ee_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->dm.useramask)
		rtl88ee_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
	अन्यथा
		rtl88ee_update_hal_rate_table(hw, sta);
पूर्ण

व्योम rtl88ee_update_channel_access_setting(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 sअगरs_समयr;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME, &mac->slot_समय);
	अगर (!mac->ht_enable)
		sअगरs_समयr = 0x0a0a;
	अन्यथा
		sअगरs_समयr = 0x0e0e;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SIFS, (u8 *)&sअगरs_समयr);
पूर्ण

bool rtl88ee_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	क्रमागत rf_pwrstate e_rfघातerstate_toset;
	u32 u4पंचांगp;
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

	u4पंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_GPIO_OUTPUT);
	e_rfघातerstate_toset = (u4पंचांगp & BIT(31)) ? ERFON : ERFOFF;

	अगर (ppsc->hwradiooff && (e_rfघातerstate_toset == ERFON)) अणु
		rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
			"GPIOChangeRF  - HW Radio ON, RF ON\n");

		e_rfघातerstate_toset = ERFON;
		ppsc->hwradiooff = false;
		b_actuallyset = true;
	पूर्ण अन्यथा अगर ((!ppsc->hwradiooff) &&
		   (e_rfघातerstate_toset == ERFOFF)) अणु
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

व्योम rtl88ee_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
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

अटल व्योम rtl8188ee_bt_var_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->btcoexist.bt_coexistence =
		rtlpriv->btcoexist.eeprom_bt_coexist;
	rtlpriv->btcoexist.bt_ant_num = rtlpriv->btcoexist.eeprom_bt_ant_num;
	rtlpriv->btcoexist.bt_coexist_type = rtlpriv->btcoexist.eeprom_bt_type;

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

व्योम rtl8188ee_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
					      bool स्वतः_load_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value;

	अगर (!स्वतः_load_fail) अणु
		rtlpriv->btcoexist.eeprom_bt_coexist =
			((hwinfo[EEPROM_RF_FEATURE_OPTION_88E] & 0xe0) >> 5);
		अगर (hwinfo[EEPROM_RF_FEATURE_OPTION_88E] == 0xFF)
			rtlpriv->btcoexist.eeprom_bt_coexist  = 0;
		value = hwinfo[EEPROM_RF_BT_SETTING_88E];
		rtlpriv->btcoexist.eeprom_bt_type = ((value & 0xe) >> 1);
		rtlpriv->btcoexist.eeprom_bt_ant_num = (value & 0x1);
		rtlpriv->btcoexist.eeprom_bt_ant_isol = ((value & 0x10) >> 4);
		rtlpriv->btcoexist.eeprom_bt_radio_shared =
				 ((value & 0x20) >> 5);
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.eeprom_bt_coexist = 0;
		rtlpriv->btcoexist.eeprom_bt_type = BT_2WIRE;
		rtlpriv->btcoexist.eeprom_bt_ant_num = ANT_X2;
		rtlpriv->btcoexist.eeprom_bt_ant_isol = 0;
		rtlpriv->btcoexist.eeprom_bt_radio_shared = BT_RADIO_SHARED;
	पूर्ण

	rtl8188ee_bt_var_init(hw);
पूर्ण

व्योम rtl8188ee_bt_reg_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* 0:Low, 1:High, 2:From Efuse. */
	rtlpriv->btcoexist.reg_bt_iso = 2;
	/* 0:Disable BT control A-MPDU, 1:Enable BT control A-MPDU. */
	rtlpriv->btcoexist.reg_bt_sco = 0;
पूर्ण

व्योम rtl8188ee_bt_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 u1_पंचांगp;

	अगर (rtlpriv->btcoexist.bt_coexistence &&
	    ((rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4) ||
	      rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC8)) अणु
		अगर (rtlpriv->btcoexist.bt_ant_isolation)
			rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG, 0xa0);

		u1_पंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x4fd) & BIT(0);
		u1_पंचांगp = u1_पंचांगp |
			 ((rtlpriv->btcoexist.bt_ant_isolation == 1) ?
			 0 : BIT((1)) |
			 ((rtlpriv->btcoexist.bt_service == BT_SCO) ?
			 0 : BIT(2)));
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

व्योम rtl88ee_suspend(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

व्योम rtl88ee_resume(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण
