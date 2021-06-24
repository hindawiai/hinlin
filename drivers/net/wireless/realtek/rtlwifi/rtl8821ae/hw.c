<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2010  Realtek Corporation.*/

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
#समावेश "../btcoexist/rtl_btc.h"

#घोषणा LLT_CONFIG	5

अटल व्योम _rtl8821ae_वापस_beacon_queue_skb(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl8821ae_set_bcn_ctrl_reg(काष्ठा ieee80211_hw *hw,
					u8 set_bits, u8 clear_bits)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpci->reg_bcn_ctrl_val |= set_bits;
	rtlpci->reg_bcn_ctrl_val &= ~clear_bits;

	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8)rtlpci->reg_bcn_ctrl_val);
पूर्ण

व्योम _rtl8821ae_stop_tx_beacon(काष्ठा ieee80211_hw *hw)
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

व्योम _rtl8821ae_resume_tx_beacon(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl8821ae_enable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl8821ae_set_bcn_ctrl_reg(hw, 0, BIT(1));
पूर्ण

अटल व्योम _rtl8821ae_disable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl8821ae_set_bcn_ctrl_reg(hw, BIT(1), 0);
पूर्ण

अटल व्योम _rtl8821ae_set_fw_घड़ी_on(काष्ठा ieee80211_hw *hw,
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
					जाओ change_करोne;
				spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
			पूर्ण
			spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
		पूर्ण अन्यथा अणु
			rtlhal->fw_clk_change_in_progress = false;
			spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
			जाओ change_करोne;
		पूर्ण
	पूर्ण
change_करोne:
	अगर (IS_IN_LOW_POWER_STATE_8821AE(rtlhal->fw_ps_state)) अणु
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
				rtlhal->fw_ps_state = FW_PS_STATE_RF_ON_8821AE;
				rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
					"Receive CPWM INT!!! Set rtlhal->FwPSState = %X\n",
					rtlhal->fw_ps_state);
			पूर्ण
		पूर्ण

		spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
		rtlhal->fw_clk_change_in_progress = false;
		spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
		अगर (b_schedule_समयr)
			mod_समयr(&rtlpriv->works.fw_घड़ीoff_समयr,
				  jअगरfies + MSECS(10));
	पूर्ण अन्यथा  अणु
		spin_lock_bh(&rtlpriv->locks.fw_ps_lock);
		rtlhal->fw_clk_change_in_progress = false;
		spin_unlock_bh(&rtlpriv->locks.fw_ps_lock);
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_set_fw_घड़ी_off(काष्ठा ieee80211_hw *hw,
					u8 rpwm_val)
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

	अगर (FW_PS_STATE(rtlhal->fw_ps_state) !=
		FW_PS_STATE_RF_OFF_LOW_PWR_8821AE) अणु
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

अटल व्योम _rtl8821ae_set_fw_ps_rf_on(काष्ठा ieee80211_hw *hw)
अणु
	u8 rpwm_val = 0;

	rpwm_val |= (FW_PS_STATE_RF_OFF_8821AE | FW_PS_ACK);
	_rtl8821ae_set_fw_घड़ी_on(hw, rpwm_val, true);
पूर्ण

अटल व्योम _rtl8821ae_fwlps_leave(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inps = false;
	u8 rpwm_val = 0, fw_pwrmode = FW_PS_ACTIVE_MODE;

	अगर (ppsc->low_घातer_enable) अणु
		rpwm_val = (FW_PS_STATE_ALL_ON_8821AE|FW_PS_ACK);/* RF on */
		_rtl8821ae_set_fw_घड़ी_on(hw, rpwm_val, false);
		rtlhal->allow_sw_to_change_hwclc = false;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
				(u8 *)(&fw_pwrmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				(u8 *)(&fw_current_inps));
	पूर्ण अन्यथा अणु
		rpwm_val = FW_PS_STATE_ALL_ON_8821AE;	/* RF on */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
				(u8 *)(&rpwm_val));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
				(u8 *)(&fw_pwrmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				(u8 *)(&fw_current_inps));
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_fwlps_enter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inps = true;
	u8 rpwm_val;

	अगर (ppsc->low_घातer_enable) अणु
		rpwm_val = FW_PS_STATE_RF_OFF_LOW_PWR_8821AE;	/* RF off */
		rtlpriv->cfg->ops->set_hw_reg(hw,
				HW_VAR_FW_PSMODE_STATUS,
				(u8 *)(&fw_current_inps));
		rtlpriv->cfg->ops->set_hw_reg(hw,
				HW_VAR_H2C_FW_PWRMODE,
				(u8 *)(&ppsc->fwctrl_psmode));
		rtlhal->allow_sw_to_change_hwclc = true;
		_rtl8821ae_set_fw_घड़ी_off(hw, rpwm_val);
	पूर्ण अन्यथा अणु
		rpwm_val = FW_PS_STATE_RF_OFF_8821AE;	/* RF off */
		rtlpriv->cfg->ops->set_hw_reg(hw,
				HW_VAR_FW_PSMODE_STATUS,
				(u8 *)(&fw_current_inps));
		rtlpriv->cfg->ops->set_hw_reg(hw,
				HW_VAR_H2C_FW_PWRMODE,
				(u8 *)(&ppsc->fwctrl_psmode));
		rtlpriv->cfg->ops->set_hw_reg(hw,
				HW_VAR_SET_RPWM,
				(u8 *)(&rpwm_val));
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_करोwnload_rsvd_page(काष्ठा ieee80211_hw *hw,
					  bool dl_whole_packets)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u8 पंचांगp_regcr, पंचांगp_reg422, bcnvalid_reg;
	u8 count = 0, dlbcn_count = 0;
	bool send_beacon = false;

	पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, (पंचांगp_regcr | BIT(0)));

	_rtl8821ae_set_bcn_ctrl_reg(hw, 0, BIT(3));
	_rtl8821ae_set_bcn_ctrl_reg(hw, BIT(4), 0);

	पंचांगp_reg422 = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2,
		       पंचांगp_reg422 & (~BIT(6)));
	अगर (पंचांगp_reg422 & BIT(6))
		send_beacon = true;

	करो अणु
		bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv, REG_TDECTRL + 2);
		rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 2,
			       (bcnvalid_reg | BIT(0)));
		_rtl8821ae_वापस_beacon_queue_skb(hw);

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_set_fw_rsvdpagepkt(hw, false,
						     dl_whole_packets);
		अन्यथा
			rtl8821ae_set_fw_rsvdpagepkt(hw, false,
						     dl_whole_packets);

		bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv, REG_TDECTRL + 2);
		count = 0;
		जबतक (!(bcnvalid_reg & BIT(0)) && count < 20) अणु
			count++;
			udelay(10);
			bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv, REG_TDECTRL + 2);
		पूर्ण
		dlbcn_count++;
	पूर्ण जबतक (!(bcnvalid_reg & BIT(0)) && dlbcn_count < 5);

	अगर (!(bcnvalid_reg & BIT(0)))
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Download RSVD page failed!\n");
	अगर (bcnvalid_reg & BIT(0) && rtlhal->enter_pnp_sleep) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 2, bcnvalid_reg | BIT(0));
		_rtl8821ae_वापस_beacon_queue_skb(hw);
		अगर (send_beacon) अणु
			dlbcn_count = 0;
			करो अणु
				rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 2,
					       bcnvalid_reg | BIT(0));

				_rtl8821ae_वापस_beacon_queue_skb(hw);

				अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
					rtl8812ae_set_fw_rsvdpagepkt(hw, true,
								     false);
				अन्यथा
					rtl8821ae_set_fw_rsvdpagepkt(hw, true,
								     false);

				/* check rsvd page करोwnload OK. */
				bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv,
							     REG_TDECTRL + 2);
				count = 0;
				जबतक (!(bcnvalid_reg & BIT(0)) && count < 20) अणु
					count++;
					udelay(10);
					bcnvalid_reg =
					  rtl_पढ़ो_byte(rtlpriv,
							REG_TDECTRL + 2);
				पूर्ण
				dlbcn_count++;
			पूर्ण जबतक (!(bcnvalid_reg & BIT(0)) && dlbcn_count < 5);

			अगर (!(bcnvalid_reg & BIT(0)))
				rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
					"2 Download RSVD page failed!\n");
		पूर्ण
	पूर्ण

	अगर (bcnvalid_reg & BIT(0))
		rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 2, BIT(0));

	_rtl8821ae_set_bcn_ctrl_reg(hw, BIT(3), 0);
	_rtl8821ae_set_bcn_ctrl_reg(hw, 0, BIT(4));

	अगर (send_beacon)
		rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp_reg422);

	अगर (!rtlhal->enter_pnp_sleep) अणु
		पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
		rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, (पंचांगp_regcr & ~(BIT(0))));
	पूर्ण
पूर्ण

व्योम rtl8821ae_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	चयन (variable) अणु
	हाल HW_VAR_ETHER_ADDR:
		*((u32 *)(val)) = rtl_पढ़ो_dword(rtlpriv, REG_MACID);
		*((u16 *)(val+4)) = rtl_पढ़ो_word(rtlpriv, REG_MACID + 4);
		अवरोध;
	हाल HW_VAR_BSSID:
		*((u32 *)(val)) = rtl_पढ़ो_dword(rtlpriv, REG_BSSID);
		*((u16 *)(val+4)) = rtl_पढ़ो_word(rtlpriv, REG_BSSID+4);
		अवरोध;
	हाल HW_VAR_MEDIA_STATUS:
		val[0] = rtl_पढ़ो_byte(rtlpriv, MSR) & 0x3;
		अवरोध;
	हाल HW_VAR_SLOT_TIME:
		*((u8 *)(val)) = mac->slot_समय;
		अवरोध;
	हाल HW_VAR_BEACON_INTERVAL:
		*((u16 *)(val)) = rtl_पढ़ो_word(rtlpriv, REG_BCN_INTERVAL);
		अवरोध;
	हाल HW_VAR_ATIM_WINDOW:
		*((u16 *)(val)) =  rtl_पढ़ो_word(rtlpriv, REG_ATIMWND);
		अवरोध;
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
		अगर (ppsc->wo_wlan_mode)
			*((bool *)(val)) = true;
		अन्यथा
			*((bool *)(val)) = false;
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl8821ae_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
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
			b_rate_cfg = b_rate_cfg & 0x15f;
			rtl_ग_लिखो_word(rtlpriv, REG_RRSR, b_rate_cfg);
			अवरोध;
		पूर्ण
	हाल HW_VAR_BSSID:अणु
			क्रम (idx = 0; idx < ETH_ALEN; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, (REG_BSSID + idx),
					       val[idx]);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_SIFS:
		rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_CTX + 1, val[0]);
		rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_TRX + 1, val[0]);

		rtl_ग_लिखो_byte(rtlpriv, REG_SPEC_SIFS + 1, val[0]);
		rtl_ग_लिखो_byte(rtlpriv, REG_MAC_SPEC_SIFS + 1, val[0]);

		rtl_ग_लिखो_byte(rtlpriv, REG_RESP_SIFS_OFDM + 1, val[0]);
		rtl_ग_लिखो_byte(rtlpriv, REG_RESP_SIFS_OFDM, val[0]);
		अवरोध;
	हाल HW_VAR_R2T_SIFS:
		rtl_ग_लिखो_byte(rtlpriv, REG_RESP_SIFS_OFDM + 1, val[0]);
		अवरोध;
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
		अवरोध; पूर्ण
	हाल HW_VAR_ACK_PREAMBLE:अणु
		u8 reg_पंचांगp;
		u8 लघु_preamble = (bool)(*(u8 *)val);

		reg_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_TRXPTCL_CTL+2);
		अगर (लघु_preamble) अणु
			reg_पंचांगp |= BIT(1);
			rtl_ग_लिखो_byte(rtlpriv, REG_TRXPTCL_CTL + 2,
				       reg_पंचांगp);
		पूर्ण अन्यथा अणु
			reg_पंचांगp &= (~BIT(1));
			rtl_ग_लिखो_byte(rtlpriv,
				REG_TRXPTCL_CTL + 2,
				reg_पंचांगp);
		पूर्ण
		अवरोध; पूर्ण
	हाल HW_VAR_WPA_CONFIG:
		rtl_ग_लिखो_byte(rtlpriv, REG_SECCFG, *((u8 *)val));
		अवरोध;
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
		अवरोध; पूर्ण
	हाल HW_VAR_SHORTGI_DENSITY:अणु
		u8 density_to_set;

		density_to_set = *((u8 *)val);
		mac->min_space_cfg |= (density_to_set << 3);

		rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
			"Set HW_VAR_SHORTGI_DENSITY: %#x\n",
			mac->min_space_cfg);

		rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE,
			       mac->min_space_cfg);

		अवरोध; पूर्ण
	हाल HW_VAR_AMPDU_FACTOR:अणु
		u32	ampdu_len =  (*((u8 *)val));

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			अगर (ampdu_len < VHT_AGG_SIZE_128K)
				ampdu_len =
					(0x2000 << (*((u8 *)val))) - 1;
			अन्यथा
				ampdu_len = 0x1ffff;
		पूर्ण अन्यथा अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
			अगर (ampdu_len < HT_AGG_SIZE_64K)
				ampdu_len =
					(0x2000 << (*((u8 *)val))) - 1;
			अन्यथा
				ampdu_len = 0xffff;
		पूर्ण
		ampdu_len |= BIT(31);

		rtl_ग_लिखो_dword(rtlpriv,
			REG_AMPDU_MAX_LENGTH_8812, ampdu_len);
		अवरोध; पूर्ण
	हाल HW_VAR_AC_PARAM:अणु
		u8 e_aci = *((u8 *)val);

		rtl8821ae_dm_init_edca_turbo(hw);
		अगर (rtlpci->acm_method != EACMWAY2_SW)
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_ACM_CTRL,
						      (u8 *)(&e_aci));
		अवरोध; पूर्ण
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
		अवरोध; पूर्ण
	हाल HW_VAR_RCR:
		rtl_ग_लिखो_dword(rtlpriv, REG_RCR, ((u32 *)(val))[0]);
		rtlpci->receive_config = ((u32 *)(val))[0];
		अवरोध;
	हाल HW_VAR_RETRY_LIMIT:अणु
		u8 retry_limit = ((u8 *)(val))[0];

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
		rtlefuse->efuse_usedpercentage = *((u8 *)val);
		अवरोध;
	हाल HW_VAR_IO_CMD:
		rtl8821ae_phy_set_io_cmd(hw, (*(क्रमागत io_type *)val));
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

		अवरोध; पूर्ण
	हाल HW_VAR_H2C_FW_PWRMODE:
		rtl8821ae_set_fw_pwrmode_cmd(hw, (*(u8 *)val));
		अवरोध;
	हाल HW_VAR_FW_PSMODE_STATUS:
		ppsc->fw_current_inpsmode = *((bool *)val);
		अवरोध;
	हाल HW_VAR_INIT_RTS_RATE:
		अवरोध;
	हाल HW_VAR_RESUME_CLK_ON:
		_rtl8821ae_set_fw_ps_rf_on(hw);
		अवरोध;
	हाल HW_VAR_FW_LPS_ACTION:अणु
		bool b_enter_fwlps = *((bool *)val);

		अगर (b_enter_fwlps)
			_rtl8821ae_fwlps_enter(hw);
		 अन्यथा
			_rtl8821ae_fwlps_leave(hw);
		 अवरोध; पूर्ण
	हाल HW_VAR_H2C_FW_JOINBSSRPT:अणु
		u8 mstatus = (*(u8 *)val);

		अगर (mstatus == RT_MEDIA_CONNECT) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AID,
						      शून्य);
			_rtl8821ae_करोwnload_rsvd_page(hw, false);
		पूर्ण
		rtl8821ae_set_fw_media_status_rpt_cmd(hw, mstatus);

		अवरोध; पूर्ण
	हाल HW_VAR_H2C_FW_P2P_PS_OFFLOAD:
		rtl8821ae_set_p2p_ps_offload_cmd(hw, (*(u8 *)val));
		अवरोध;
	हाल HW_VAR_AID:अणु
		u16 u2bपंचांगp;
		u2bपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_BCN_PSR_RPT);
		u2bपंचांगp &= 0xC000;
		rtl_ग_लिखो_word(rtlpriv, REG_BCN_PSR_RPT, (u2bपंचांगp |
			       mac->assoc_id));
		अवरोध; पूर्ण
	हाल HW_VAR_CORRECT_TSF:अणु
		u8 btype_ibss = ((u8 *)(val))[0];

		अगर (btype_ibss)
			_rtl8821ae_stop_tx_beacon(hw);

		_rtl8821ae_set_bcn_ctrl_reg(hw, 0, BIT(3));

		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR,
				(u32)(mac->tsf & 0xffffffff));
		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR + 4,
				(u32)((mac->tsf >> 32) & 0xffffffff));

		_rtl8821ae_set_bcn_ctrl_reg(hw, BIT(3), 0);

		अगर (btype_ibss)
			_rtl8821ae_resume_tx_beacon(hw);
		अवरोध; पूर्ण
	हाल HW_VAR_NAV_UPPER: अणु
		u32	us_nav_upper = *(u32 *)val;

		अगर (us_nav_upper > HAL_92C_NAV_UPPER_UNIT * 0xFF) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_WARNING,
				"The setting value (0x%08X us) of NAV_UPPER is larger than (%d * 0xFF)!!!\n",
				us_nav_upper, HAL_92C_NAV_UPPER_UNIT);
			अवरोध;
		पूर्ण
		rtl_ग_लिखो_byte(rtlpriv, REG_NAV_UPPER,
			       ((u8)((us_nav_upper +
				HAL_92C_NAV_UPPER_UNIT - 1) /
				HAL_92C_NAV_UPPER_UNIT)));
		अवरोध; पूर्ण
	हाल HW_VAR_KEEP_ALIVE: अणु
		u8 array[2];
		array[0] = 0xff;
		array[1] = *((u8 *)val);
		rtl8821ae_fill_h2c_cmd(hw, H2C_8821AE_KEEP_ALIVE_CTRL, 2,
				       array);
		अवरोध; पूर्ण
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool _rtl8821ae_llt_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 address, u32 data)
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

अटल bool _rtl8821ae_llt_table_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अचिन्हित लघु i;
	u8 txpktbuf_bndy;
	u32 rqpn;
	u8 maxpage;
	bool status;

	maxpage = 255;
	txpktbuf_bndy = 0xF7;
	rqpn = 0x80e60808;

	rtl_ग_लिखो_byte(rtlpriv, REG_TRXFF_BNDY, txpktbuf_bndy);
	rtl_ग_लिखो_word(rtlpriv, REG_TRXFF_BNDY + 2, MAX_RX_DMA_BUFFER_SIZE - 1);

	rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 1, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, REG_PBP, 0x31);
	rtl_ग_लिखो_byte(rtlpriv, REG_RX_DRVINFO_SZ, 0x4);

	क्रम (i = 0; i < (txpktbuf_bndy - 1); i++) अणु
		status = _rtl8821ae_llt_ग_लिखो(hw, i, i + 1);
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl8821ae_llt_ग_लिखो(hw, (txpktbuf_bndy - 1), 0xFF);
	अगर (!status)
		वापस status;

	क्रम (i = txpktbuf_bndy; i < maxpage; i++) अणु
		status = _rtl8821ae_llt_ग_लिखो(hw, i, (i + 1));
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl8821ae_llt_ग_लिखो(hw, maxpage, txpktbuf_bndy);
	अगर (!status)
		वापस status;

	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, rqpn);

	rtl_ग_लिखो_byte(rtlpriv, REG_RQPN_NPQ, 0x00);

	वापस true;
पूर्ण

अटल व्योम _rtl8821ae_gen_refresh_led_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (rtlpriv->rtlhal.up_first_समय)
		वापस;

	अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_sw_led_on(hw, pled0);
		अन्यथा
			rtl8821ae_sw_led_on(hw, pled0);
	अन्यथा अगर (ppsc->rfoff_reason == RF_CHANGE_BY_INIT)
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_sw_led_on(hw, pled0);
		अन्यथा
			rtl8821ae_sw_led_on(hw, pled0);
	अन्यथा
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_sw_led_off(hw, pled0);
		अन्यथा
			rtl8821ae_sw_led_off(hw, pled0);
पूर्ण

अटल bool _rtl8821ae_init_mac(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	u8 byteपंचांगp = 0;
	u16 wordपंचांगp = 0;
	bool mac_func_enable = rtlhal->mac_func_enable;

	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x00);

	/*Auto Power Down to CHIP-off State*/
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO + 1) & (~BIT(7));
	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO + 1, byteपंचांगp);

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
		/* HW Power on sequence*/
		अगर (!rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK,
					      PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,
					      RTL8812_NIC_ENABLE_FLOW)) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"init 8812 MAC Fail as power on failure\n");
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* HW Power on sequence */
		अगर (!rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_A_MSK,
					      PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,
					      RTL8821A_NIC_ENABLE_FLOW))अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"init 8821 MAC Fail as power on failure\n");
			वापस false;
		पूर्ण
	पूर्ण

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO) | BIT(4);
	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO, byteपंचांगp);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_CR);
	byteपंचांगp = 0xff;
	rtl_ग_लिखो_byte(rtlpriv, REG_CR, byteपंचांगp);
	mdelay(2);

	byteपंचांगp = 0xff;
	rtl_ग_लिखो_byte(rtlpriv, REG_HWSEQ_CTRL, byteपंचांगp);
	mdelay(2);

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CFG + 3);
		अगर (byteपंचांगp & BIT(0)) अणु
			byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x7c);
			byteपंचांगp |= BIT(6);
			rtl_ग_लिखो_byte(rtlpriv, 0x7c, byteपंचांगp);
		पूर्ण
	पूर्ण

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_MUXCFG + 1);
	byteपंचांगp &= ~BIT(4);
	rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG + 1, byteपंचांगp);

	rtl_ग_लिखो_word(rtlpriv, REG_CR, 0x2ff);

	अगर (!mac_func_enable) अणु
		अगर (!_rtl8821ae_llt_table_init(hw))
			वापस false;
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, REG_HISR, 0xffffffff);
	rtl_ग_लिखो_dword(rtlpriv, REG_HISRE, 0xffffffff);

	/* Enable FW Beamक्रमmer Interrupt */
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_FWIMR + 3);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWIMR + 3, byteपंचांगp | BIT(6));

	wordपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_TRXDMA_CTRL);
	wordपंचांगp &= 0xf;
	wordपंचांगp |= 0xF5B1;
	rtl_ग_लिखो_word(rtlpriv, REG_TRXDMA_CTRL, wordपंचांगp);

	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 1, 0x1F);
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);
	rtl_ग_लिखो_word(rtlpriv, REG_RXFLTMAP2, 0xFFFF);
	/*low address*/
	rtl_ग_लिखो_dword(rtlpriv, REG_BCNQ_DESA,
			rtlpci->tx_ring[BEACON_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_MGQ_DESA,
			rtlpci->tx_ring[MGNT_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_VOQ_DESA,
			rtlpci->tx_ring[VO_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_VIQ_DESA,
			rtlpci->tx_ring[VI_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_BEQ_DESA,
			rtlpci->tx_ring[BE_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_BKQ_DESA,
			rtlpci->tx_ring[BK_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_HQ_DESA,
			rtlpci->tx_ring[HIGH_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_RX_DESA,
			rtlpci->rx_ring[RX_MPDU_QUEUE].dma & DMA_BIT_MASK(32));

	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 3, 0x77);

	rtl_ग_लिखो_dword(rtlpriv, REG_INT_MIG, 0);

	rtl_ग_लिखो_dword(rtlpriv, REG_MCUTST_1, 0);

	rtl_ग_लिखो_byte(rtlpriv, REG_SECONDARY_CCA_CTRL, 0x3);
	_rtl8821ae_gen_refresh_led_state(hw);

	वापस true;
पूर्ण

अटल व्योम _rtl8821ae_hw_configure(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 reg_rrsr;

	reg_rrsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;

	rtl_ग_लिखो_dword(rtlpriv, REG_RRSR, reg_rrsr);
	/* ARFB table 9 क्रम 11ac 5G 2SS */
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR0 + 4, 0xfffff000);
	/* ARFB table 10 क्रम 11ac 5G 1SS */
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR1 + 4, 0x003ff000);
	/* ARFB table 11 क्रम 11ac 24G 1SS */
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR2, 0x00000015);
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR2 + 4, 0x003ff000);
	/* ARFB table 12 क्रम 11ac 24G 1SS */
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR3, 0x00000015);
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR3 + 4, 0xffcff000);
	/* 0x420[7] = 0 , enable retry AMPDU in new AMPD not singal MPDU. */
	rtl_ग_लिखो_word(rtlpriv, REG_FWHW_TXQ_CTRL, 0x1F00);
	rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MAX_TIME, 0x70);

	/*Set retry limit*/
	rtl_ग_लिखो_word(rtlpriv, REG_RL, 0x0707);

	/* Set Data / Response स्वतः rate fallack retry count*/
	rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC, 0x01000000);
	rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4, 0x07060504);
	rtl_ग_लिखो_dword(rtlpriv, REG_RARFRC, 0x01000000);
	rtl_ग_लिखो_dword(rtlpriv, REG_RARFRC + 4, 0x07060504);

	rtlpci->reg_bcn_ctrl_val = 0x1d;
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, rtlpci->reg_bcn_ctrl_val);

	/* TBTT prohibit hold समय. Suggested by designer TimChen. */
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);

	/* AGGR_BK_TIME Reg51A 0x16 */
	rtl_ग_लिखो_word(rtlpriv, REG_NAV_PROT_LEN, 0x0040);

	/*For Rx TP. Suggested by SD1 Riअक्षरd. Added by tynli. 2010.04.12.*/
	rtl_ग_लिखो_dword(rtlpriv, REG_FAST_EDCA_CTRL, 0x03086666);

	rtl_ग_लिखो_byte(rtlpriv, REG_HT_SINGLE_AMPDU, 0x80);
	rtl_ग_लिखो_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x20);
	rtl_ग_लिखो_word(rtlpriv, REG_MAX_AGGR_NUM, 0x1F1F);
पूर्ण

अटल u16 _rtl8821ae_mdio_पढ़ो(काष्ठा rtl_priv *rtlpriv, u8 addr)
अणु
	u16 ret = 0;
	u8 पंचांगp = 0, count = 0;

	rtl_ग_लिखो_byte(rtlpriv, REG_MDIO_CTL, addr | BIT(6));
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MDIO_CTL) & BIT(6);
	count = 0;
	जबतक (पंचांगp && count < 20) अणु
		udelay(10);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MDIO_CTL) & BIT(6);
		count++;
	पूर्ण
	अगर (0 == पंचांगp)
		ret = rtl_पढ़ो_word(rtlpriv, REG_MDIO_RDATA);

	वापस ret;
पूर्ण

अटल व्योम _rtl8821ae_mdio_ग_लिखो(काष्ठा rtl_priv *rtlpriv, u8 addr, u16 data)
अणु
	u8 पंचांगp = 0, count = 0;

	rtl_ग_लिखो_word(rtlpriv, REG_MDIO_WDATA, data);
	rtl_ग_लिखो_byte(rtlpriv, REG_MDIO_CTL, addr | BIT(5));
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MDIO_CTL) & BIT(5);
	count = 0;
	जबतक (पंचांगp && count < 20) अणु
		udelay(10);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MDIO_CTL) & BIT(5);
		count++;
	पूर्ण
पूर्ण

अटल u8 _rtl8821ae_dbi_पढ़ो(काष्ठा rtl_priv *rtlpriv, u16 addr)
अणु
	u16 पढ़ो_addr = addr & 0xfffc;
	u8 पंचांगp = 0, count = 0, ret = 0;

	rtl_ग_लिखो_word(rtlpriv, REG_DBI_ADDR, पढ़ो_addr);
	rtl_ग_लिखो_byte(rtlpriv, REG_DBI_FLAG, 0x2);
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_FLAG);
	count = 0;
	जबतक (पंचांगp && count < 20) अणु
		udelay(10);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_FLAG);
		count++;
	पूर्ण
	अगर (0 == पंचांगp) अणु
		पढ़ो_addr = REG_DBI_RDATA + addr % 4;
		ret = rtl_पढ़ो_byte(rtlpriv, पढ़ो_addr);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम _rtl8821ae_dbi_ग_लिखो(काष्ठा rtl_priv *rtlpriv, u16 addr, u8 data)
अणु
	u8 पंचांगp = 0, count = 0;
	u16 ग_लिखो_addr, reमुख्यder = addr % 4;

	ग_लिखो_addr = REG_DBI_WDATA + reमुख्यder;
	rtl_ग_लिखो_byte(rtlpriv, ग_लिखो_addr, data);

	ग_लिखो_addr = (addr & 0xfffc) | (BIT(0) << (reमुख्यder + 12));
	rtl_ग_लिखो_word(rtlpriv, REG_DBI_ADDR, ग_लिखो_addr);

	rtl_ग_लिखो_byte(rtlpriv, REG_DBI_FLAG, 0x1);

	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_FLAG);
	count = 0;
	जबतक (पंचांगp && count < 20) अणु
		udelay(10);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_FLAG);
		count++;
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_enable_aspm_back_करोor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp;

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		अगर (_rtl8821ae_mdio_पढ़ो(rtlpriv, 0x04) != 0x8544)
			_rtl8821ae_mdio_ग_लिखो(rtlpriv, 0x04, 0x8544);

		अगर (_rtl8821ae_mdio_पढ़ो(rtlpriv, 0x0b) != 0x0070)
			_rtl8821ae_mdio_ग_लिखो(rtlpriv, 0x0b, 0x0070);
	पूर्ण

	पंचांगp = _rtl8821ae_dbi_पढ़ो(rtlpriv, 0x70f);
	_rtl8821ae_dbi_ग_लिखो(rtlpriv, 0x70f, पंचांगp | BIT(7) |
			     ASPM_L1_LATENCY << 3);

	पंचांगp = _rtl8821ae_dbi_पढ़ो(rtlpriv, 0x719);
	_rtl8821ae_dbi_ग_लिखो(rtlpriv, 0x719, पंचांगp | BIT(3) | BIT(4));

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
		पंचांगp  = _rtl8821ae_dbi_पढ़ो(rtlpriv, 0x718);
		_rtl8821ae_dbi_ग_लिखो(rtlpriv, 0x718, पंचांगp|BIT(4));
	पूर्ण
पूर्ण

व्योम rtl8821ae_enable_hw_security_config(काष्ठा ieee80211_hw *hw)
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

/* Static MacID Mapping (cf. Used in MacIdDoStaticMapping) ---------- */
#घोषणा MAC_ID_STATIC_FOR_DEFAULT_PORT				0
#घोषणा MAC_ID_STATIC_FOR_BROADCAST_MULTICAST		1
#घोषणा MAC_ID_STATIC_FOR_BT_CLIENT_START				2
#घोषणा MAC_ID_STATIC_FOR_BT_CLIENT_END				3
/* ----------------------------------------------------------- */

अटल व्योम rtl8821ae_macid_initialize_mediastatus(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8	media_rpt[4] = अणुRT_MEDIA_CONNECT, 1,
		MAC_ID_STATIC_FOR_BROADCAST_MULTICAST,
		MAC_ID_STATIC_FOR_BT_CLIENT_ENDपूर्ण;

	rtlpriv->cfg->ops->set_hw_reg(hw,
		HW_VAR_H2C_FW_MEDIASTATUSRPT, media_rpt);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Initialize MacId media status: from %d to %d\n",
		MAC_ID_STATIC_FOR_BROADCAST_MULTICAST,
		MAC_ID_STATIC_FOR_BT_CLIENT_END);
पूर्ण

अटल bool _rtl8821ae_check_pcie_dma_hang(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp;

	/* ग_लिखो reg 0x350 Bit[26]=1. Enable debug port. */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_CTRL + 3);
	अगर (!(पंचांगp & BIT(2))) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_DBI_CTRL + 3, (पंचांगp | BIT(2)));
		mdelay(100);
	पूर्ण

	/* पढ़ो reg 0x350 Bit[25] अगर 1 : RX hang */
	/* पढ़ो reg 0x350 Bit[24] अगर 1 : TX hang */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_CTRL + 3);
	अगर ((पंचांगp & BIT(0)) || (पंचांगp & BIT(1))) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"CheckPcieDMAHang8821AE(): true! Reset PCIE DMA!\n");
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

अटल bool _rtl8821ae_reset_pcie_पूर्णांकerface_dma(काष्ठा ieee80211_hw *hw,
					 bool mac_घातer_on,
					 bool in_watchकरोg)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp;
	bool release_mac_rx_छोड़ो;
	u8 backup_pcie_dma_छोड़ो;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "\n");

	/* 1. Disable रेजिस्टर ग_लिखो lock. 0x1c[1] = 0 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL);
	पंचांगp &= ~(BIT(1));
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, पंचांगp);
	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		/* ग_लिखो 0xCC bit[2] = 1'b1 */
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_PMC_DBG_CTRL2);
		पंचांगp |= BIT(2);
		rtl_ग_लिखो_byte(rtlpriv, REG_PMC_DBG_CTRL2, पंचांगp);
	पूर्ण

	/* 2. Check and छोड़ो TRX DMA */
	/* ग_लिखो 0x284 bit[18] = 1'b1 */
	/* ग_लिखो 0x301 = 0xFF */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
	अगर (पंचांगp & BIT(2)) अणु
		/* Alपढ़ोy छोड़ो beक्रमe the function क्रम another purpose. */
		release_mac_rx_छोड़ो = false;
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL, (पंचांगp | BIT(2)));
		release_mac_rx_छोड़ो = true;
	पूर्ण
	backup_pcie_dma_छोड़ो = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1);
	अगर (backup_pcie_dma_छोड़ो != 0xFF)
		rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xFF);

	अगर (mac_घातer_on) अणु
		/* 3. reset TRX function */
		/* ग_लिखो 0x100 = 0x00 */
		rtl_ग_लिखो_byte(rtlpriv, REG_CR, 0);
	पूर्ण

	/* 4. Reset PCIe DMA. 0x3[0] = 0 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	पंचांगp &= ~(BIT(0));
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगp);

	/* 5. Enable PCIe DMA. 0x3[0] = 1 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	पंचांगp |= BIT(0);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, पंचांगp);

	अगर (mac_घातer_on) अणु
		/* 6. enable TRX function */
		/* ग_लिखो 0x100 = 0xFF */
		rtl_ग_लिखो_byte(rtlpriv, REG_CR, 0xFF);

		/* We should init LLT & RQPN and
		 * prepare Tx/Rx descrptor address later
		 * because MAC function is reset.*/
	पूर्ण

	/* 7. Restore PCIe स्वतःload करोwn bit */
	/* 8812AE करोes not has the defination. */
	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		/* ग_लिखो 0xF8 bit[17] = 1'b1 */
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MAC_PHY_CTRL_NORMAL + 2);
		पंचांगp |= BIT(1);
		rtl_ग_लिखो_byte(rtlpriv, REG_MAC_PHY_CTRL_NORMAL + 2, पंचांगp);
	पूर्ण

	/* In MAC घातer on state, BB and RF maybe in ON state,
	 * अगर we release TRx DMA here.
	 * it will cause packets to be started to Tx/Rx,
	 * so we release Tx/Rx DMA later.*/
	अगर (!mac_घातer_on/* || in_watchकरोg*/) अणु
		/* 8. release TRX DMA */
		/* ग_लिखो 0x284 bit[18] = 1'b0 */
		/* ग_लिखो 0x301 = 0x00 */
		अगर (release_mac_rx_छोड़ो) अणु
			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
			rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL,
				       पंचांगp & (~BIT(2)));
		पूर्ण
		rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1,
			       backup_pcie_dma_छोड़ो);
	पूर्ण

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		/* 9. lock प्रणाली रेजिस्टर */
		/* ग_लिखो 0xCC bit[2] = 1'b0 */
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_PMC_DBG_CTRL2);
		पंचांगp &= ~(BIT(2));
		rtl_ग_लिखो_byte(rtlpriv, REG_PMC_DBG_CTRL2, पंचांगp);
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम _rtl8821ae_get_wakeup_reason(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	u8 fw_reason = 0;

	fw_reason = rtl_पढ़ो_byte(rtlpriv, REG_MCUTST_WOWLAN);

	rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "WOL Read 0x1c7 = %02X\n",
		fw_reason);

	ppsc->wakeup_reason = 0;

	rtlhal->last_suspend_sec = kसमय_get_real_seconds();

	चयन (fw_reason) अणु
	हाल FW_WOW_V2_PTK_UPDATE_EVENT:
		ppsc->wakeup_reason = WOL_REASON_PTK_UPDATE;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's a WOL PTK Key update event!\n");
		अवरोध;
	हाल FW_WOW_V2_GTK_UPDATE_EVENT:
		ppsc->wakeup_reason = WOL_REASON_GTK_UPDATE;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's a WOL GTK Key update event!\n");
		अवरोध;
	हाल FW_WOW_V2_DISASSOC_EVENT:
		ppsc->wakeup_reason = WOL_REASON_DISASSOC;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's a disassociation event!\n");
		अवरोध;
	हाल FW_WOW_V2_DEAUTH_EVENT:
		ppsc->wakeup_reason = WOL_REASON_DEAUTH;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's a deauth event!\n");
		अवरोध;
	हाल FW_WOW_V2_FW_DISCONNECT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_AP_LOST;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's a Fw disconnect decision (AP lost) event!\n");
	अवरोध;
	हाल FW_WOW_V2_MAGIC_PKT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_MAGIC_PKT;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's a magic packet event!\n");
		अवरोध;
	हाल FW_WOW_V2_UNICAST_PKT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_UNICAST_PKT;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's an unicast packet event!\n");
		अवरोध;
	हाल FW_WOW_V2_PATTERN_PKT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_PATTERN_PKT;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's a pattern match event!\n");
		अवरोध;
	हाल FW_WOW_V2_RTD3_SSID_MATCH_EVENT:
		ppsc->wakeup_reason = WOL_REASON_RTD3_SSID_MATCH;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's an RTD3 Ssid match event!\n");
		अवरोध;
	हाल FW_WOW_V2_REALWOW_V2_WAKEUPPKT:
		ppsc->wakeup_reason = WOL_REASON_REALWOW_V2_WAKEUPPKT;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's an RealWoW wake packet event!\n");
		अवरोध;
	हाल FW_WOW_V2_REALWOW_V2_ACKLOST:
		ppsc->wakeup_reason = WOL_REASON_REALWOW_V2_ACKLOST;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"It's an RealWoW ack lost event!\n");
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"WOL Read 0x1c7 = %02X, Unknown reason!\n",
			fw_reason);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_init_trx_desc_hw_address(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	/*low address*/
	rtl_ग_लिखो_dword(rtlpriv, REG_BCNQ_DESA,
			rtlpci->tx_ring[BEACON_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_MGQ_DESA,
			rtlpci->tx_ring[MGNT_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_VOQ_DESA,
			rtlpci->tx_ring[VO_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_VIQ_DESA,
			rtlpci->tx_ring[VI_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_BEQ_DESA,
			rtlpci->tx_ring[BE_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_BKQ_DESA,
			rtlpci->tx_ring[BK_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_HQ_DESA,
			rtlpci->tx_ring[HIGH_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_ग_लिखो_dword(rtlpriv, REG_RX_DESA,
			rtlpci->rx_ring[RX_MPDU_QUEUE].dma & DMA_BIT_MASK(32));
पूर्ण

अटल bool _rtl8821ae_init_llt_table(काष्ठा ieee80211_hw *hw, u32 boundary)
अणु
	bool status = true;
	u32 i;
	u32 txpktbuf_bndy = boundary;
	u32 last_entry_of_txpktbuf = LAST_ENTRY_OF_TX_PKT_BUFFER;

	क्रम (i = 0 ; i < (txpktbuf_bndy - 1) ; i++) अणु
		status = _rtl8821ae_llt_ग_लिखो(hw, i , i + 1);
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl8821ae_llt_ग_लिखो(hw, (txpktbuf_bndy - 1), 0xFF);
	अगर (!status)
		वापस status;

	क्रम (i = txpktbuf_bndy ; i < last_entry_of_txpktbuf ; i++) अणु
		status = _rtl8821ae_llt_ग_लिखो(hw, i, (i + 1));
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl8821ae_llt_ग_लिखो(hw, last_entry_of_txpktbuf,
				      txpktbuf_bndy);
	अगर (!status)
		वापस status;

	वापस status;
पूर्ण

अटल bool _rtl8821ae_dynamic_rqpn(काष्ठा ieee80211_hw *hw, u32 boundary,
			     u16 npq_rqpn_value, u32 rqpn_val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp;
	bool ret = true;
	u16 count = 0, पंचांगp16;
	bool support_remote_wakeup;

	rtlpriv->cfg->ops->get_hw_reg(hw, HAL_DEF_WOWLAN,
				      (u8 *)(&support_remote_wakeup));

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"boundary=%#X, NPQ_RQPNValue=%#X, RQPNValue=%#X\n",
		boundary, npq_rqpn_value, rqpn_val);

	/* stop PCIe DMA
	 * 1. 0x301[7:0] = 0xFE */
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xFE);

	/* रुको TXFF empty
	 * 2. polling till 0x41A[15:0]=0x07FF */
	पंचांगp16 = rtl_पढ़ो_word(rtlpriv, REG_TXPKT_EMPTY);
	जबतक ((पंचांगp16 & 0x07FF) != 0x07FF) अणु
		udelay(100);
		पंचांगp16 = rtl_पढ़ो_word(rtlpriv, REG_TXPKT_EMPTY);
		count++;
		अगर ((count % 200) == 0) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Tx queue is not empty for 20ms!\n");
		पूर्ण
		अगर (count >= 1000) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Wait for Tx FIFO empty timeout!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* TX छोड़ो
	 * 3. reg 0x522=0xFF */
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);

	/* Wait TX State Machine OK
	 * 4. polling till reg 0x5FB~0x5F8 = 0x00000000 क्रम 50ms */
	count = 0;
	जबतक (rtl_पढ़ो_byte(rtlpriv, REG_SCH_TXCMD) != 0) अणु
		udelay(100);
		count++;
		अगर (count >= 500) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Wait for TX State Machine ready timeout !!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* stop RX DMA path
	 * 5.	0x284[18] = 1
	 * 6.	रुको till 0x284[17] == 1
	 * रुको RX DMA idle */
	count = 0;
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL, (पंचांगp | BIT(2)));
	करो अणु
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
		udelay(10);
		count++;
	पूर्ण जबतक (!(पंचांगp & BIT(1)) && count < 100);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Wait until Rx DMA Idle. count=%d REG[0x286]=0x%x\n",
		count, पंचांगp);

	/* reset BB
	 * 7.	0x02 [0] = 0 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN);
	पंचांगp &= ~(BIT(0));
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, पंचांगp);

	/* Reset TRX MAC
	 * 8.	 0x100 = 0x00
	 * Delay (1ms) */
	rtl_ग_लिखो_byte(rtlpriv, REG_CR, 0x00);
	udelay(1000);

	/* Disable MAC Security Engine
	 * 9.	0x100 bit[9]=0 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
	पंचांगp &= ~(BIT(1));
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, पंचांगp);

	/* To aव्योम DD-Tim Circuit hang
	 * 10.	0x553 bit[5]=1 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DUAL_TSF_RST);
	rtl_ग_लिखो_byte(rtlpriv, REG_DUAL_TSF_RST, (पंचांगp | BIT(5)));

	/* Enable MAC Security Engine
	 * 11.	0x100 bit[9]=1 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, (पंचांगp | BIT(1)));

	/* Enable TRX MAC
	 * 12.	 0x100 = 0xFF
	 *	Delay (1ms) */
	rtl_ग_लिखो_byte(rtlpriv, REG_CR, 0xFF);
	udelay(1000);

	/* Enable BB
	 * 13.	0x02 [0] = 1 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, (पंचांगp | BIT(0)));

	/* beacon setting
	 * 14,15. set beacon head page (reg 0x209 and 0x424) */
	rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 1, (u8)boundary);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, (u8)boundary);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, (u8)boundary);

	/* 16.	WMAC_LBK_BF_HD 0x45D[7:0]
	 * WMAC_LBK_BF_HD */
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_WMAC_LBK_BF_HD,
		       (u8)boundary);

	rtl_ग_लिखो_word(rtlpriv, REG_TRXFF_BNDY, boundary);

	/* init LLT
	 * 17. init LLT */
	अगर (!_rtl8821ae_init_llt_table(hw, boundary)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_WARNING,
			"Failed to init LLT table!\n");
		वापस false;
	पूर्ण

	/* पुनः_स्मृतिate RQPN
	 * 18. पुनः_स्मृतिate RQPN and init LLT */
	rtl_ग_लिखो_word(rtlpriv, REG_RQPN_NPQ, npq_rqpn_value);
	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, rqpn_val);

	/* release Tx छोड़ो
	 * 19. 0x522=0x00 */
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);

	/* enable PCIE DMA
	 * 20. 0x301[7:0] = 0x00
	 * 21. 0x284[18] = 0 */
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0x00);
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL, (पंचांगp&~BIT(2)));

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "End.\n");
	वापस ret;
पूर्ण

अटल व्योम _rtl8821ae_simple_initialize_adapter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);

#अगर (USE_SPECIFIC_FW_TO_SUPPORT_WOWLAN == 1)
	/* Re-करोwnload normal Fw. */
	rtl8821ae_set_fw_related_क्रम_wowlan(hw, false);
#पूर्ण_अगर

	/* Re-Initialize LLT table. */
	अगर (rtlhal->re_init_llt_table) अणु
		u32 rqpn = 0x80e70808;
		u8 rqpn_npq = 0, boundary = 0xF8;
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			rqpn = 0x80e90808;
			boundary = 0xFA;
		पूर्ण
		अगर (_rtl8821ae_dynamic_rqpn(hw, boundary, rqpn_npq, rqpn))
			rtlhal->re_init_llt_table = false;
	पूर्ण

	ppsc->rfpwr_state = ERFON;
पूर्ण

अटल व्योम _rtl8821ae_enable_l1off(काष्ठा ieee80211_hw *hw)
अणु
	u8 पंचांगp  = 0;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "--->\n");

	पंचांगp = _rtl8821ae_dbi_पढ़ो(rtlpriv, 0x160);
	अगर (!(पंचांगp & (BIT(2) | BIT(3)))) अणु
		rtl_dbg(rtlpriv, COMP_POWER | COMP_INIT, DBG_LOUD,
			"0x160(%#x)return!!\n", पंचांगp);
		वापस;
	पूर्ण

	पंचांगp = _rtl8821ae_mdio_पढ़ो(rtlpriv, 0x1b);
	_rtl8821ae_mdio_ग_लिखो(rtlpriv, 0x1b, (पंचांगp | BIT(4)));

	पंचांगp = _rtl8821ae_dbi_पढ़ो(rtlpriv, 0x718);
	_rtl8821ae_dbi_ग_लिखो(rtlpriv, 0x718, पंचांगp | BIT(5));

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "<---\n");
पूर्ण

अटल व्योम _rtl8821ae_enable_ltr(काष्ठा ieee80211_hw *hw)
अणु
	u8 पंचांगp  = 0;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "--->\n");

	/* Check 0x98[10] */
	पंचांगp = _rtl8821ae_dbi_पढ़ो(rtlpriv, 0x99);
	अगर (!(पंचांगp & BIT(2))) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"<---0x99(%#x) return!!\n", पंचांगp);
		वापस;
	पूर्ण

	/* LTR idle latency, 0x90 क्रम 144us */
	rtl_ग_लिखो_dword(rtlpriv, 0x798, 0x88908890);

	/* LTR active latency, 0x3c क्रम 60us */
	rtl_ग_लिखो_dword(rtlpriv, 0x79c, 0x883c883c);

	पंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x7a4);
	rtl_ग_लिखो_byte(rtlpriv, 0x7a4, (पंचांगp | BIT(4)));

	पंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x7a4);
	rtl_ग_लिखो_byte(rtlpriv, 0x7a4, (पंचांगp & (~BIT(0))));
	rtl_ग_लिखो_byte(rtlpriv, 0x7a4, (पंचांगp | BIT(0)));

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "<---\n");
पूर्ण

अटल bool _rtl8821ae_wowlan_initialize_adapter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	bool init_finished = true;
	u8 पंचांगp = 0;

	/* Get Fw wake up reason. */
	_rtl8821ae_get_wakeup_reason(hw);

	/* Patch Pcie Rx DMA hang after S3/S4 several बार.
	 * The root cause has not be found. */
	अगर (_rtl8821ae_check_pcie_dma_hang(hw))
		_rtl8821ae_reset_pcie_पूर्णांकerface_dma(hw, true, false);

	/* Prepare Tx/Rx Desc Hw address. */
	_rtl8821ae_init_trx_desc_hw_address(hw);

	/* Release Pcie Interface Rx DMA to allow wake packet DMA. */
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xFE);
	rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "Enable PCIE Rx DMA.\n");

	/* Check wake up event.
	 * We should check wake packet bit beक्रमe disable wowlan by H2C or
	 * Fw will clear the bit. */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_FTISR + 3);
	rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
		"Read REG_FTISR 0x13f = %#X\n", पंचांगp);

	/* Set the WoWLAN related function control disable. */
	rtl8821ae_set_fw_wowlan_mode(hw, false);
	rtl8821ae_set_fw_remote_wake_ctrl_cmd(hw, 0);

	अगर (rtlhal->hw_rof_enable) अणु
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_HSISR + 3);
		अगर (पंचांगp & BIT(1)) अणु
			/* Clear GPIO9 ISR */
			rtl_ग_लिखो_byte(rtlpriv, REG_HSISR + 3, पंचांगp | BIT(1));
			init_finished = false;
		पूर्ण अन्यथा अणु
			init_finished = true;
		पूर्ण
	पूर्ण

	अगर (init_finished) अणु
		_rtl8821ae_simple_initialize_adapter(hw);

		/* Release Pcie Interface Tx DMA. */
		rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0x00);
		/* Release Pcie RX DMA */
		rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL, 0x02);

		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
		rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, (पंचांगp & (~BIT(0))));

		_rtl8821ae_enable_l1off(hw);
		_rtl8821ae_enable_ltr(hw);
	पूर्ण

	वापस init_finished;
पूर्ण

अटल व्योम _rtl8812ae_bb8812_config_1t(काष्ठा ieee80211_hw *hw)
अणु
	/* BB OFDM RX Path_A */
	rtl_set_bbreg(hw, 0x808, 0xff, 0x11);
	/* BB OFDM TX Path_A */
	rtl_set_bbreg(hw, 0x80c, MASKLWORD, 0x1111);
	/* BB CCK R/Rx Path_A */
	rtl_set_bbreg(hw, 0xa04, 0x0c000000, 0x0);
	/* MCS support */
	rtl_set_bbreg(hw, 0x8bc, 0xc0000060, 0x4);
	/* RF Path_B HSSI OFF */
	rtl_set_bbreg(hw, 0xe00, 0xf, 0x4);
	/* RF Path_B Power Down */
	rtl_set_bbreg(hw, 0xe90, MASKDWORD, 0);
	/* ADDA Path_B OFF */
	rtl_set_bbreg(hw, 0xe60, MASKDWORD, 0);
	rtl_set_bbreg(hw, 0xe64, MASKDWORD, 0);
पूर्ण

अटल व्योम _rtl8821ae_घातeroff_adapter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 u1b_पंचांगp;

	rtlhal->mac_func_enable = false;

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		/* Combo (PCIe + USB) Card and PCIe-MF Card */
		/* 1. Run LPS WL RFOFF flow */
		/* rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"=====>CardDisableRTL8812E,RTL8821A_NIC_LPS_ENTER_FLOW\n");
		*/
		rtl_hal_pwrseqcmdparsing(rtlpriv,
			PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
			PWR_INTF_PCI_MSK, RTL8821A_NIC_LPS_ENTER_FLOW);
	पूर्ण
	/* 2. 0x1F[7:0] = 0 */
	/* turn off RF */
	/* rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, 0x00); */
	अगर ((rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL) & BIT(7)) &&
		rtlhal->fw_पढ़ोy) अणु
		rtl8821ae_firmware_selfreset(hw);
	पूर्ण

	/* Reset MCU. Suggested by Filen. */
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN+1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN+1, (u1b_पंचांगp & (~BIT(2))));

	/* g.	MCUFWDL 0x80[1:0]=0	 */
	/* reset MCU पढ़ोy status */
	rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0x00);

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		/* HW card disable configuration. */
		rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
			PWR_INTF_PCI_MSK, RTL8821A_NIC_DISABLE_FLOW);
	पूर्ण अन्यथा अणु
		/* HW card disable configuration. */
		rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
			PWR_INTF_PCI_MSK, RTL8812_NIC_DISABLE_FLOW);
	पूर्ण

	/* Reset MCU IO Wrapper */
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_पंचांगp & (~BIT(0))));
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, u1b_पंचांगp | BIT(0));

	/* 7. RSV_CTRL 0x1C[7:0] = 0x0E */
	/* lock ISO/CLK/Power control रेजिस्टर */
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0e);
पूर्ण

पूर्णांक rtl8821ae_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool rtstatus = true;
	पूर्णांक err;
	u8 पंचांगp_u1b;
	bool support_remote_wakeup;
	u32 nav_upper = WIFI_NAV_UPPER_US;

	rtlhal->being_init_adapter = true;
	rtlpriv->cfg->ops->get_hw_reg(hw, HAL_DEF_WOWLAN,
				      (u8 *)(&support_remote_wakeup));
	rtlpriv->पूर्णांकf_ops->disable_aspm(hw);

	/*YP wowlan not considered*/

	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_CR);
	अगर (पंचांगp_u1b != 0 && पंचांगp_u1b != 0xEA) अणु
		rtlhal->mac_func_enable = true;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"MAC has already power on.\n");
	पूर्ण अन्यथा अणु
		rtlhal->mac_func_enable = false;
		rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON_8821AE;
	पूर्ण

	अगर (support_remote_wakeup &&
		rtlhal->wake_from_pnp_sleep &&
		rtlhal->mac_func_enable) अणु
		अगर (_rtl8821ae_wowlan_initialize_adapter(hw)) अणु
			rtlhal->being_init_adapter = false;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (_rtl8821ae_check_pcie_dma_hang(hw)) अणु
		_rtl8821ae_reset_pcie_पूर्णांकerface_dma(hw,
						    rtlhal->mac_func_enable,
						    false);
		rtlhal->mac_func_enable = false;
	पूर्ण

	/* Reset MAC/BB/RF status अगर it is not घातered off
	 * beक्रमe calling initialize Hw flow to prevent
	 * from पूर्णांकerface and MAC status mismatch.
	 * 2013.06.21, by tynli. Suggested by SD1 JackieLau. */
	अगर (rtlhal->mac_func_enable) अणु
		_rtl8821ae_घातeroff_adapter(hw);
		rtlhal->mac_func_enable = false;
	पूर्ण

	rtstatus = _rtl8821ae_init_mac(hw);
	अगर (!rtstatus) अणु
		pr_err("Init MAC failed\n");
		err = 1;
		वापस err;
	पूर्ण

	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CFG);
	पंचांगp_u1b &= 0x7F;
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_CFG, पंचांगp_u1b);

	err = rtl8821ae_करोwnload_fw(hw, false);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Failed to download FW. Init HW without FW now\n");
		err = 1;
		rtlhal->fw_पढ़ोy = false;
		वापस err;
	पूर्ण अन्यथा अणु
		rtlhal->fw_पढ़ोy = true;
	पूर्ण
	ppsc->fw_current_inpsmode = false;
	rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON_8821AE;
	rtlhal->fw_clk_change_in_progress = false;
	rtlhal->allow_sw_to_change_hwclc = false;
	rtlhal->last_hmeboxnum = 0;

	/*SIC_Init(Adapter);
	अगर(rtlhal->AMPDUBurstMode)
		rtl_ग_लिखो_byte(rtlpriv,REG_AMPDU_BURST_MODE_8812,  0x7F);*/

	rtl8821ae_phy_mac_config(hw);
	/* because last function modअगरy RCR, so we update
	 * rcr var here, or TP will unstable क्रम receive_config
	 * is wrong, RX RCR_ACRC32 will cause TP unstabel & Rx
	 * RCR_APP_ICV will cause mac80211 unassoc क्रम cisco 1252
	rtlpci->receive_config = rtl_पढ़ो_dword(rtlpriv, REG_RCR);
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);*/
	rtl8821ae_phy_bb_config(hw);

	rtl8821ae_phy_rf_config(hw);

	अगर (rtlpriv->phy.rf_type == RF_1T1R &&
		rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
		_rtl8812ae_bb8812_config_1t(hw);

	_rtl8821ae_hw_configure(hw);

	rtl8821ae_phy_चयन_wirelessband(hw, BAND_ON_2_4G);

	/*set wireless mode*/

	rtlhal->mac_func_enable = true;

	rtl_cam_reset_all_entry(hw);

	rtl8821ae_enable_hw_security_config(hw);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	_rtl8821ae_enable_aspm_back_करोor(hw);
	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE &&
	    (rtlhal->rfe_type == 1 || rtlhal->rfe_type == 5))
		rtl_set_bbreg(hw, 0x900, 0x00000303, 0x0302);

	rtl8821ae_bt_hw_init(hw);
	rtlpriv->rtlhal.being_init_adapter = false;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_NAV_UPPER, (u8 *)&nav_upper);

	/* rtl8821ae_dm_check_txघातer_tracking(hw); */
	/* rtl8821ae_phy_lc_calibrate(hw); */
	अगर (support_remote_wakeup)
		rtl_ग_लिखो_byte(rtlpriv, REG_WOW_CTRL, 0);

	/* Release Rx DMA*/
	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
	अगर (पंचांगp_u1b & BIT(2)) अणु
		/* Release Rx DMA अगर needed*/
		पंचांगp_u1b &= ~BIT(2);
		rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL, पंचांगp_u1b);
	पूर्ण

	/* Release Tx/Rx PCIE DMA अगर*/
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0);

	rtl8821ae_dm_init(hw);
	rtl8821ae_macid_initialize_mediastatus(hw);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "%s() <====\n", __func__);
	वापस err;
पूर्ण

अटल क्रमागत version_8821ae _rtl8821ae_पढ़ो_chip_version(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	क्रमागत version_8821ae version = VERSION_UNKNOWN;
	u32 value32;

	value32 = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"ReadChipVersion8812A 0xF0 = 0x%x\n", value32);

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
		rtlphy->rf_type = RF_2T2R;
	अन्यथा अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE)
		rtlphy->rf_type = RF_1T1R;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"RF_Type is %x!!\n", rtlphy->rf_type);

	अगर (value32 & TRP_VAUX_EN) अणु
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			अगर (rtlphy->rf_type == RF_2T2R)
				version = VERSION_TEST_CHIP_2T2R_8812;
			अन्यथा
				version = VERSION_TEST_CHIP_1T1R_8812;
		पूर्ण अन्यथा
			version = VERSION_TEST_CHIP_8821;
	पूर्ण अन्यथा अणु
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			u32 rtl_id = ((value32 & CHIP_VER_RTL_MASK) >> 12) + 1;

			अगर (rtlphy->rf_type == RF_2T2R)
				version =
					(क्रमागत version_8821ae)(CHIP_8812
					| NORMAL_CHIP |
					RF_TYPE_2T2R);
			अन्यथा
				version = (क्रमागत version_8821ae)(CHIP_8812
					| NORMAL_CHIP);

			version = (क्रमागत version_8821ae)(version | (rtl_id << 12));
		पूर्ण अन्यथा अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
			u32 rtl_id = value32 & CHIP_VER_RTL_MASK;

			version = (क्रमागत version_8821ae)(CHIP_8821
				| NORMAL_CHIP | rtl_id);
		पूर्ण
	पूर्ण

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		/*WL_HWROF_EN.*/
		value32 = rtl_पढ़ो_dword(rtlpriv, REG_MULTI_FUNC_CTRL);
		rtlhal->hw_rof_enable = ((value32 & WL_HWROF_EN) ? 1 : 0);
	पूर्ण

	चयन (version) अणु
	हाल VERSION_TEST_CHIP_1T1R_8812:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID: VERSION_TEST_CHIP_1T1R_8812\n");
		अवरोध;
	हाल VERSION_TEST_CHIP_2T2R_8812:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID: VERSION_TEST_CHIP_2T2R_8812\n");
		अवरोध;
	हाल VERSION_NORMAL_TSMC_CHIP_1T1R_8812:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID:VERSION_NORMAL_TSMC_CHIP_1T1R_8812\n");
		अवरोध;
	हाल VERSION_NORMAL_TSMC_CHIP_2T2R_8812:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID: VERSION_NORMAL_TSMC_CHIP_2T2R_8812\n");
		अवरोध;
	हाल VERSION_NORMAL_TSMC_CHIP_1T1R_8812_C_CUT:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID: VERSION_NORMAL_TSMC_CHIP_1T1R_8812 C CUT\n");
		अवरोध;
	हाल VERSION_NORMAL_TSMC_CHIP_2T2R_8812_C_CUT:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID: VERSION_NORMAL_TSMC_CHIP_2T2R_8812 C CUT\n");
		अवरोध;
	हाल VERSION_TEST_CHIP_8821:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID: VERSION_TEST_CHIP_8821\n");
		अवरोध;
	हाल VERSION_NORMAL_TSMC_CHIP_8821:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID: VERSION_NORMAL_TSMC_CHIP_8821 A CUT\n");
		अवरोध;
	हाल VERSION_NORMAL_TSMC_CHIP_8821_B_CUT:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID: VERSION_NORMAL_TSMC_CHIP_8821 B CUT\n");
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Chip Version ID: Unknown (0x%X)\n", version);
		अवरोध;
	पूर्ण

	वापस version;
पूर्ण

अटल पूर्णांक _rtl8821ae_set_media_status(काष्ठा ieee80211_hw *hw,
				     क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_msr = rtl_पढ़ो_byte(rtlpriv, MSR);
	क्रमागत led_ctl_mode ledaction = LED_CTL_NO_LINK;
	bt_msr &= 0xfc;

	rtl_ग_लिखो_dword(rtlpriv, REG_BCN_CTRL, 0);
	rtl_dbg(rtlpriv, COMP_BEACON, DBG_LOUD,
		"clear 0x550 when set HW_VAR_MEDIA_STATUS\n");

	अगर (type == NL80211_IFTYPE_UNSPECIFIED ||
	    type == NL80211_IFTYPE_STATION) अणु
		_rtl8821ae_stop_tx_beacon(hw);
		_rtl8821ae_enable_bcn_sub_func(hw);
	पूर्ण अन्यथा अगर (type == NL80211_IFTYPE_ADHOC ||
		type == NL80211_IFTYPE_AP) अणु
		_rtl8821ae_resume_tx_beacon(hw);
		_rtl8821ae_disable_bcn_sub_func(hw);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Set HW_VAR_MEDIA_STATUS: No such media status(%x).\n",
			type);
	पूर्ण

	चयन (type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		bt_msr |= MSR_NOLINK;
		ledaction = LED_CTL_LINK;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to NO LINK!\n");
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		bt_msr |= MSR_ADHOC;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to Ad Hoc!\n");
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		bt_msr |= MSR_INFRA;
		ledaction = LED_CTL_LINK;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to STA!\n");
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		bt_msr |= MSR_AP;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to AP!\n");
		अवरोध;
	शेष:
		pr_err("Network type %d not support!\n", type);
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

व्योम rtl8821ae_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid)
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
		_rtl8821ae_set_bcn_ctrl_reg(hw, 0, BIT(4));
	पूर्ण अन्यथा अगर (!check_bssid) अणु
		reg_rcr &= (~(RCR_CBSSID_DATA | RCR_CBSSID_BCN));
		_rtl8821ae_set_bcn_ctrl_reg(hw, BIT(4), 0);
		rtlpriv->cfg->ops->set_hw_reg(hw,
			HW_VAR_RCR, (u8 *)(&reg_rcr));
	पूर्ण
पूर्ण

पूर्णांक rtl8821ae_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "%s!\n", __func__);

	अगर (_rtl8821ae_set_media_status(hw, type))
		वापस -EOPNOTSUPP;

	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		अगर (type != NL80211_IFTYPE_AP)
			rtl8821ae_set_check_bssid(hw, true);
	पूर्ण अन्यथा अणु
		rtl8821ae_set_check_bssid(hw, false);
	पूर्ण

	वापस 0;
पूर्ण

/* करोn't set REG_EDCA_BE_PARAM here because mac80211 will send pkt when scan */
व्योम rtl8821ae_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	rtl8821ae_dm_init_edca_turbo(hw);
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
		WARN_ONCE(true, "rtl8821ae: invalid aci: %d !\n", aci);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtl8821ae_clear_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 पंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_HISR);

	rtl_ग_लिखो_dword(rtlpriv, REG_HISR, पंचांगp);

	पंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_HISRE);
	rtl_ग_लिखो_dword(rtlpriv, REG_HISRE, पंचांगp);

	पंचांगp = rtl_पढ़ो_dword(rtlpriv, REG_HSISR);
	rtl_ग_लिखो_dword(rtlpriv, REG_HSISR, पंचांगp);
पूर्ण

व्योम rtl8821ae_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	अगर (rtlpci->पूर्णांक_clear)
		rtl8821ae_clear_पूर्णांकerrupt(hw);/*clear it here first*/

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, rtlpci->irq_mask[0] & 0xFFFFFFFF);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, rtlpci->irq_mask[1] & 0xFFFFFFFF);
	rtlpci->irq_enabled = true;
	/* there are some C2H CMDs have been sent beक्रमe
	प्रणाली पूर्णांकerrupt is enabled, e.g., C2H, CPWM.
	*So we need to clear all C2H events that FW has
	notअगरied, otherwise FW won't schedule any commands anymore.
	*/
	/* rtl_ग_लिखो_byte(rtlpriv, REG_C2HEVT_CLEAR, 0); */
	/*enable प्रणाली पूर्णांकerrupt*/
	rtl_ग_लिखो_dword(rtlpriv, REG_HSIMR, rtlpci->sys_irq_mask & 0xFFFFFFFF);
पूर्ण

व्योम rtl8821ae_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, IMR_DISABLED);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, IMR_DISABLED);
	rtlpci->irq_enabled = false;
	/*synchronize_irq(rtlpci->pdev->irq);*/
पूर्ण

अटल व्योम _rtl8821ae_clear_pci_pme_status(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u16 cap_hdr;
	u8 cap_poपूर्णांकer;
	u8 cap_id = 0xff;
	u8 pmcs_reg;
	u8 cnt = 0;

	/* Get the Capability poपूर्णांकer first,
	 * the Capability Poपूर्णांकer is located at
	 * offset 0x34 from the Function Header */

	pci_पढ़ो_config_byte(rtlpci->pdev, 0x34, &cap_poपूर्णांकer);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"PCI configuration 0x34 = 0x%2x\n", cap_poपूर्णांकer);

	करो अणु
		pci_पढ़ो_config_word(rtlpci->pdev, cap_poपूर्णांकer, &cap_hdr);
		cap_id = cap_hdr & 0xFF;

		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"in pci configuration, cap_pointer%x = %x\n",
			cap_poपूर्णांकer, cap_id);

		अगर (cap_id == 0x01) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			/* poपूर्णांक to next Capability */
			cap_poपूर्णांकer = (cap_hdr >> 8) & 0xFF;
			/* 0: end of pci capability, 0xff: invalid value */
			अगर (cap_poपूर्णांकer == 0x00 || cap_poपूर्णांकer == 0xff) अणु
				cap_id = 0xff;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (cnt++ < 200);

	अगर (cap_id == 0x01) अणु
		/* Get the PM CSR (Control/Status Register),
		 * The PME_Status is located at PM Capatibility offset 5, bit 7
		 */
		pci_पढ़ो_config_byte(rtlpci->pdev, cap_poपूर्णांकer + 5, &pmcs_reg);

		अगर (pmcs_reg & BIT(7)) अणु
			/* PME event occured, clear the PM_Status by ग_लिखो 1 */
			pmcs_reg = pmcs_reg | BIT(7);

			pci_ग_लिखो_config_byte(rtlpci->pdev, cap_poपूर्णांकer + 5,
					      pmcs_reg);
			/* Read it back to check */
			pci_पढ़ो_config_byte(rtlpci->pdev, cap_poपूर्णांकer + 5,
					     &pmcs_reg);
			rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
				"Clear PME status 0x%2x to 0x%2x\n",
				cap_poपूर्णांकer + 5, pmcs_reg);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
				"PME status(0x%2x) = 0x%2x\n",
				cap_poपूर्णांकer + 5, pmcs_reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_WARNING,
			"Cannot find PME Capability\n");
	पूर्ण
पूर्ण

व्योम rtl8821ae_card_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	क्रमागत nl80211_अगरtype opmode;
	bool support_remote_wakeup;
	u8 पंचांगp;
	u32 count = 0;

	rtlpriv->cfg->ops->get_hw_reg(hw, HAL_DEF_WOWLAN,
				      (u8 *)(&support_remote_wakeup));

	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);

	अगर (!(support_remote_wakeup && mac->opmode == NL80211_IFTYPE_STATION)
	    || !rtlhal->enter_pnp_sleep) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "Normal Power off\n");
		mac->link_state = MAC80211_NOLINK;
		opmode = NL80211_IFTYPE_UNSPECIFIED;
		_rtl8821ae_set_media_status(hw, opmode);
		_rtl8821ae_घातeroff_adapter(hw);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "Wowlan Supported.\n");
		/* 3 <1> Prepare क्रम configuring wowlan related infomations */
		/* Clear Fw WoWLAN event. */
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUTST_WOWLAN, 0x0);

#अगर (USE_SPECIFIC_FW_TO_SUPPORT_WOWLAN == 1)
		rtl8821ae_set_fw_related_क्रम_wowlan(hw, true);
#पूर्ण_अगर
		/* Dynamically adjust Tx packet boundary
		 * क्रम करोwnload reserved page packet.
		 * reserve 30 pages क्रम rsvd page */
		अगर (_rtl8821ae_dynamic_rqpn(hw, 0xE0, 0x3, 0x80c20d0d))
			rtlhal->re_init_llt_table = true;

		/* 3 <2> Set Fw releted H2C cmd. */

		/* Set WoWLAN related security inक्रमmation. */
		rtl8821ae_set_fw_global_info_cmd(hw);

		_rtl8821ae_करोwnload_rsvd_page(hw, true);

		/* Just enable AOAC related functions when we connect to AP. */
		prपूर्णांकk("mac->link_state = %d\n", mac->link_state);
		अगर (mac->link_state >= MAC80211_LINKED &&
		    mac->opmode == NL80211_IFTYPE_STATION) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AID, शून्य);
			rtl8821ae_set_fw_media_status_rpt_cmd(hw,
							      RT_MEDIA_CONNECT);

			rtl8821ae_set_fw_wowlan_mode(hw, true);
			/* Enable Fw Keep alive mechanism. */
			rtl8821ae_set_fw_keep_alive_cmd(hw, true);

			/* Enable disconnect decision control. */
			rtl8821ae_set_fw_disconnect_decision_ctrl_cmd(hw, true);
		पूर्ण

		/* 3 <3> Hw Configutations */

		/* Wait untill Rx DMA Finished beक्रमe host sleep.
		 * FW Pause Rx DMA may happens when received packet करोing dma.
		 */
		rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL, BIT(2));

		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
		count = 0;
		जबतक (!(पंचांगp & BIT(1)) && (count++ < 100)) अणु
			udelay(10);
			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
		पूर्ण
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Wait Rx DMA Finished before host sleep. count=%d\n",
			count);

		/* reset trx ring */
		rtlpriv->पूर्णांकf_ops->reset_trx_ring(hw);

		rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO + 1, 0x0);

		_rtl8821ae_clear_pci_pme_status(hw);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CLKR);
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_CLKR, पंचांगp | BIT(3));
		/* prevent 8051 to be reset by PERST */
		rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x20);
		rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x60);
	पूर्ण

	अगर (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);
	/* For wowlan+LPS+32k. */
	अगर (support_remote_wakeup && rtlhal->enter_pnp_sleep) अणु
		/* Set the WoWLAN related function control enable.
		 * It should be the last H2C cmd in the WoWLAN flow. */
		rtl8821ae_set_fw_remote_wake_ctrl_cmd(hw, 1);

		/* Stop Pcie Interface Tx DMA. */
		rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xff);
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "Stop PCIE Tx DMA.\n");

		/* Wait क्रम TxDMA idle. */
		count = 0;
		करो अणु
			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_CTRL_REG);
			udelay(10);
			count++;
		पूर्ण जबतक ((पंचांगp != 0) && (count < 100));
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Wait Tx DMA Finished before host sleep. count=%d\n",
			count);

		अगर (rtlhal->hw_rof_enable) अणु
			prपूर्णांकk("hw_rof_enable\n");
			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_HSISR + 3);
			rtl_ग_लिखो_byte(rtlpriv, REG_HSISR + 3, पंचांगp | BIT(1));
		पूर्ण
	पूर्ण
	/* after घातer off we should करो iqk again */
	rtlpriv->phy.iqk_initialized = false;
पूर्ण

व्योम rtl8821ae_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				    काष्ठा rtl_पूर्णांक *पूर्णांकvec)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	पूर्णांकvec->पूर्णांकa = rtl_पढ़ो_dword(rtlpriv, ISR) & rtlpci->irq_mask[0];
	rtl_ग_लिखो_dword(rtlpriv, ISR, पूर्णांकvec->पूर्णांकa);

	पूर्णांकvec->पूर्णांकb = rtl_पढ़ो_dword(rtlpriv, REG_HISRE) & rtlpci->irq_mask[1];
	rtl_ग_लिखो_dword(rtlpriv, REG_HISRE, पूर्णांकvec->पूर्णांकb);
पूर्ण

व्योम rtl8821ae_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u16 bcn_पूर्णांकerval, atim_winकरोw;

	bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;
	atim_winकरोw = 2;	/*FIX MERGE */
	rtl8821ae_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_ATIMWND, atim_winकरोw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl_ग_लिखो_word(rtlpriv, REG_BCNTCFG, 0x660f);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_CCK, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, 0x606, 0x30);
	rtlpci->reg_bcn_ctrl_val |= BIT(3);
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8)rtlpci->reg_bcn_ctrl_val);
	rtl8821ae_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl8821ae_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;

	rtl_dbg(rtlpriv, COMP_BEACON, DBG_DMESG,
		"beacon_interval:%d\n", bcn_पूर्णांकerval);
	rtl8821ae_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl8821ae_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl8821ae_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
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
	rtl8821ae_disable_पूर्णांकerrupt(hw);
	rtl8821ae_enable_पूर्णांकerrupt(hw);
पूर्ण

अटल u8 _rtl8821ae_get_chnl_group(u8 chnl)
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
	अन्यथा /*अगर (12 <= chnl && chnl <= 14)*/
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
	अन्यथा
		WARN_ONCE(true,
			  "rtl8821ae: 5G, Channel %d in Group not found\n",
			  chnl);
	पूर्ण
	वापस group;
पूर्ण

अटल व्योम _rtl8821ae_पढ़ो_घातer_value_fromprom(काष्ठा ieee80211_hw *hw,
	काष्ठा txघातer_info_2g *pwrinfo24g,
	काष्ठा txघातer_info_5g *pwrinfo5g,
	bool स्वतःload_fail,
	u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 rfpath, eeaddr = EEPROM_TX_PWR_INX, group, txcount = 0;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"hal_ReadPowerValueFromPROM8821ae(): hwinfo[0x%x]=0x%x\n",
		(eeaddr + 1), hwinfo[eeaddr + 1]);
	अगर (hwinfo[eeaddr + 1] == 0xFF)  /*YJ,add,120316*/
		स्वतःload_fail = true;

	अगर (स्वतःload_fail) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"auto load fail : Use Default value!\n");
		क्रम (rfpath = 0 ; rfpath < MAX_RF_PATH ; rfpath++) अणु
			/*2.4G शेष value*/
			क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) अणु
				pwrinfo24g->index_cck_base[rfpath][group] = 0x2D;
				pwrinfo24g->index_bw40_base[rfpath][group] = 0x2D;
			पूर्ण
			क्रम (txcount = 0; txcount < MAX_TX_COUNT; txcount++) अणु
				अगर (txcount == 0) अणु
					pwrinfo24g->bw20_dअगरf[rfpath][0] = 0x02;
					pwrinfo24g->ofdm_dअगरf[rfpath][0] = 0x04;
				पूर्ण अन्यथा अणु
					pwrinfo24g->bw20_dअगरf[rfpath][txcount] = 0xFE;
					pwrinfo24g->bw40_dअगरf[rfpath][txcount] = 0xFE;
					pwrinfo24g->cck_dअगरf[rfpath][txcount] =	0xFE;
					pwrinfo24g->ofdm_dअगरf[rfpath][txcount] = 0xFE;
				पूर्ण
			पूर्ण
			/*5G शेष value*/
			क्रम (group = 0 ; group < MAX_CHNL_GROUP_5G; group++)
				pwrinfo5g->index_bw40_base[rfpath][group] = 0x2A;

			क्रम (txcount = 0; txcount < MAX_TX_COUNT; txcount++) अणु
				अगर (txcount == 0) अणु
					pwrinfo5g->ofdm_dअगरf[rfpath][0] = 0x04;
					pwrinfo5g->bw20_dअगरf[rfpath][0] = 0x00;
					pwrinfo5g->bw80_dअगरf[rfpath][0] = 0xFE;
					pwrinfo5g->bw160_dअगरf[rfpath][0] = 0xFE;
				पूर्ण अन्यथा अणु
					pwrinfo5g->ofdm_dअगरf[rfpath][0] = 0xFE;
					pwrinfo5g->bw20_dअगरf[rfpath][0] = 0xFE;
					pwrinfo5g->bw40_dअगरf[rfpath][0] = 0xFE;
					pwrinfo5g->bw80_dअगरf[rfpath][0] = 0xFE;
					pwrinfo5g->bw160_dअगरf[rfpath][0] = 0xFE;
				पूर्ण
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	rtl_priv(hw)->efuse.txpwr_fromeprom = true;

	क्रम (rfpath = 0 ; rfpath < MAX_RF_PATH ; rfpath++) अणु
		/*2.4G शेष value*/
		क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) अणु
			pwrinfo24g->index_cck_base[rfpath][group] = hwinfo[eeaddr++];
			अगर (pwrinfo24g->index_cck_base[rfpath][group] == 0xFF)
				pwrinfo24g->index_cck_base[rfpath][group] = 0x2D;
		पूर्ण
		क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G - 1; group++) अणु
			pwrinfo24g->index_bw40_base[rfpath][group] = hwinfo[eeaddr++];
			अगर (pwrinfo24g->index_bw40_base[rfpath][group] == 0xFF)
				pwrinfo24g->index_bw40_base[rfpath][group] = 0x2D;
		पूर्ण
		क्रम (txcount = 0; txcount < MAX_TX_COUNT; txcount++) अणु
			अगर (txcount == 0) अणु
				pwrinfo24g->bw40_dअगरf[rfpath][txcount] = 0;
				/*bit sign number to 8 bit sign number*/
				pwrinfo24g->bw20_dअगरf[rfpath][txcount] = (hwinfo[eeaddr] & 0xf0) >> 4;
				अगर (pwrinfo24g->bw20_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo24g->bw20_dअगरf[rfpath][txcount] |= 0xF0;
				/*bit sign number to 8 bit sign number*/
				pwrinfo24g->ofdm_dअगरf[rfpath][txcount] = (hwinfo[eeaddr] & 0x0f);
				अगर (pwrinfo24g->ofdm_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo24g->ofdm_dअगरf[rfpath][txcount] |= 0xF0;

				pwrinfo24g->cck_dअगरf[rfpath][txcount] = 0;
				eeaddr++;
			पूर्ण अन्यथा अणु
				pwrinfo24g->bw40_dअगरf[rfpath][txcount] = (hwinfo[eeaddr] & 0xf0) >> 4;
				अगर (pwrinfo24g->bw40_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo24g->bw40_dअगरf[rfpath][txcount] |= 0xF0;

				pwrinfo24g->bw20_dअगरf[rfpath][txcount] = (hwinfo[eeaddr] & 0x0f);
				अगर (pwrinfo24g->bw20_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo24g->bw20_dअगरf[rfpath][txcount] |= 0xF0;

				eeaddr++;

				pwrinfo24g->ofdm_dअगरf[rfpath][txcount] = (hwinfo[eeaddr] & 0xf0) >> 4;
				अगर (pwrinfo24g->ofdm_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo24g->ofdm_dअगरf[rfpath][txcount] |= 0xF0;

				pwrinfo24g->cck_dअगरf[rfpath][txcount] =	(hwinfo[eeaddr] & 0x0f);
				अगर (pwrinfo24g->cck_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo24g->cck_dअगरf[rfpath][txcount] |= 0xF0;

				eeaddr++;
			पूर्ण
		पूर्ण

		/*5G शेष value*/
		क्रम (group = 0 ; group < MAX_CHNL_GROUP_5G; group++) अणु
			pwrinfo5g->index_bw40_base[rfpath][group] = hwinfo[eeaddr++];
			अगर (pwrinfo5g->index_bw40_base[rfpath][group] == 0xFF)
				pwrinfo5g->index_bw40_base[rfpath][group] = 0xFE;
		पूर्ण

		क्रम (txcount = 0; txcount < MAX_TX_COUNT; txcount++) अणु
			अगर (txcount == 0) अणु
				pwrinfo5g->bw40_dअगरf[rfpath][txcount] = 0;

				pwrinfo5g->bw20_dअगरf[rfpath][0] = (hwinfo[eeaddr] & 0xf0) >> 4;
				अगर (pwrinfo5g->bw20_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo5g->bw20_dअगरf[rfpath][txcount] |= 0xF0;

				pwrinfo5g->ofdm_dअगरf[rfpath][0] = (hwinfo[eeaddr] & 0x0f);
				अगर (pwrinfo5g->ofdm_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo5g->ofdm_dअगरf[rfpath][txcount] |= 0xF0;

				eeaddr++;
			पूर्ण अन्यथा अणु
				pwrinfo5g->bw40_dअगरf[rfpath][txcount] = (hwinfo[eeaddr] & 0xf0) >> 4;
				अगर (pwrinfo5g->bw40_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo5g->bw40_dअगरf[rfpath][txcount] |= 0xF0;

				pwrinfo5g->bw20_dअगरf[rfpath][txcount] = (hwinfo[eeaddr] & 0x0f);
				अगर (pwrinfo5g->bw20_dअगरf[rfpath][txcount] & BIT(3))
					pwrinfo5g->bw20_dअगरf[rfpath][txcount] |= 0xF0;

				eeaddr++;
			पूर्ण
		पूर्ण

		pwrinfo5g->ofdm_dअगरf[rfpath][1] =	(hwinfo[eeaddr] & 0xf0) >> 4;
		pwrinfo5g->ofdm_dअगरf[rfpath][2] =	(hwinfo[eeaddr] & 0x0f);

		eeaddr++;

		pwrinfo5g->ofdm_dअगरf[rfpath][3] = (hwinfo[eeaddr] & 0x0f);

		eeaddr++;

		क्रम (txcount = 1; txcount < MAX_TX_COUNT; txcount++) अणु
			अगर (pwrinfo5g->ofdm_dअगरf[rfpath][txcount] & BIT(3))
				pwrinfo5g->ofdm_dअगरf[rfpath][txcount] |= 0xF0;
		पूर्ण
		क्रम (txcount = 0; txcount < MAX_TX_COUNT; txcount++) अणु
			pwrinfo5g->bw80_dअगरf[rfpath][txcount] =	(hwinfo[eeaddr] & 0xf0) >> 4;
			/* 4bit sign number to 8 bit sign number */
			अगर (pwrinfo5g->bw80_dअगरf[rfpath][txcount] & BIT(3))
				pwrinfo5g->bw80_dअगरf[rfpath][txcount] |= 0xF0;
			/* 4bit sign number to 8 bit sign number */
			pwrinfo5g->bw160_dअगरf[rfpath][txcount] = (hwinfo[eeaddr] & 0x0f);
			अगर (pwrinfo5g->bw160_dअगरf[rfpath][txcount] & BIT(3))
				pwrinfo5g->bw160_dअगरf[rfpath][txcount] |= 0xF0;

			eeaddr++;
		पूर्ण
	पूर्ण
पूर्ण
#अगर 0
अटल व्योम _rtl8812ae_पढ़ो_txघातer_info_from_hwpg(काष्ठा ieee80211_hw *hw,
						 bool स्वतःload_fail,
						 u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा txघातer_info_2g pwrinfo24g;
	काष्ठा txघातer_info_5g pwrinfo5g;
	u8 rf_path, index;
	u8 i;

	_rtl8821ae_पढ़ो_घातer_value_fromprom(hw, &pwrinfo24g,
					&pwrinfo5g, स्वतःload_fail, hwinfo);

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < CHANNEL_MAX_NUMBER_2G; i++) अणु
			index = _rtl8821ae_get_chnl_group(i + 1);

			अगर (i == CHANNEL_MAX_NUMBER_2G - 1) अणु
				rtlefuse->txpwrlevel_cck[rf_path][i] =
					pwrinfo24g.index_cck_base[rf_path][5];
				rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
					pwrinfo24g.index_bw40_base[rf_path][index];
			पूर्ण अन्यथा अणु
				rtlefuse->txpwrlevel_cck[rf_path][i] =
					pwrinfo24g.index_cck_base[rf_path][index];
				rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
					pwrinfo24g.index_bw40_base[rf_path][index];
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < CHANNEL_MAX_NUMBER_5G; i++) अणु
			index = _rtl8821ae_get_chnl_group(channel5g[i]);
			rtlefuse->txpwr_5g_bw40base[rf_path][i] =
					pwrinfo5g.index_bw40_base[rf_path][index];
		पूर्ण
		क्रम (i = 0; i < CHANNEL_MAX_NUMBER_5G_80M; i++) अणु
			u8 upper, lower;
			index = _rtl8821ae_get_chnl_group(channel5g_80m[i]);
			upper = pwrinfo5g.index_bw40_base[rf_path][index];
			lower = pwrinfo5g.index_bw40_base[rf_path][index + 1];

			rtlefuse->txpwr_5g_bw80base[rf_path][i] = (upper + lower) / 2;
		पूर्ण
		क्रम (i = 0; i < MAX_TX_COUNT; i++) अणु
			rtlefuse->txpwr_cckdअगरf[rf_path][i] =
				pwrinfo24g.cck_dअगरf[rf_path][i];
			rtlefuse->txpwr_legacyhtdअगरf[rf_path][i] =
				pwrinfo24g.ofdm_dअगरf[rf_path][i];
			rtlefuse->txpwr_ht20dअगरf[rf_path][i] =
				pwrinfo24g.bw20_dअगरf[rf_path][i];
			rtlefuse->txpwr_ht40dअगरf[rf_path][i] =
				pwrinfo24g.bw40_dअगरf[rf_path][i];

			rtlefuse->txpwr_5g_ofdmdअगरf[rf_path][i] =
				pwrinfo5g.ofdm_dअगरf[rf_path][i];
			rtlefuse->txpwr_5g_bw20dअगरf[rf_path][i] =
				pwrinfo5g.bw20_dअगरf[rf_path][i];
			rtlefuse->txpwr_5g_bw40dअगरf[rf_path][i] =
				pwrinfo5g.bw40_dअगरf[rf_path][i];
			rtlefuse->txpwr_5g_bw80dअगरf[rf_path][i] =
				pwrinfo5g.bw80_dअगरf[rf_path][i];
		पूर्ण
	पूर्ण

	अगर (!स्वतःload_fail) अणु
		rtlefuse->eeprom_regulatory =
			hwinfo[EEPROM_RF_BOARD_OPTION] & 0x07;/*bit0~2*/
		अगर (hwinfo[EEPROM_RF_BOARD_OPTION] == 0xFF)
			rtlefuse->eeprom_regulatory = 0;
	पूर्ण अन्यथा अणु
		rtlefuse->eeprom_regulatory = 0;
	पूर्ण

	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
	"eeprom_regulatory = 0x%x\n", rtlefuse->eeprom_regulatory);
पूर्ण
#पूर्ण_अगर
अटल व्योम _rtl8821ae_पढ़ो_txघातer_info_from_hwpg(काष्ठा ieee80211_hw *hw,
						 bool स्वतःload_fail,
						 u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा txघातer_info_2g pwrinfo24g;
	काष्ठा txघातer_info_5g pwrinfo5g;
	u8 rf_path, index;
	u8 i;

	_rtl8821ae_पढ़ो_घातer_value_fromprom(hw, &pwrinfo24g,
		&pwrinfo5g, स्वतःload_fail, hwinfo);

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < CHANNEL_MAX_NUMBER_2G; i++) अणु
			index = _rtl8821ae_get_chnl_group(i + 1);

			अगर (i == CHANNEL_MAX_NUMBER_2G - 1) अणु
				rtlefuse->txpwrlevel_cck[rf_path][i] =
					pwrinfo24g.index_cck_base[rf_path][5];
				rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
					pwrinfo24g.index_bw40_base[rf_path][index];
			पूर्ण अन्यथा अणु
				rtlefuse->txpwrlevel_cck[rf_path][i] =
					pwrinfo24g.index_cck_base[rf_path][index];
				rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
					pwrinfo24g.index_bw40_base[rf_path][index];
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < CHANNEL_MAX_NUMBER_5G; i++) अणु
			index = _rtl8821ae_get_chnl_group(channel5g[i]);
			rtlefuse->txpwr_5g_bw40base[rf_path][i] =
				pwrinfo5g.index_bw40_base[rf_path][index];
		पूर्ण
		क्रम (i = 0; i < CHANNEL_MAX_NUMBER_5G_80M; i++) अणु
			u8 upper, lower;
			index = _rtl8821ae_get_chnl_group(channel5g_80m[i]);
			upper = pwrinfo5g.index_bw40_base[rf_path][index];
			lower = pwrinfo5g.index_bw40_base[rf_path][index + 1];

			rtlefuse->txpwr_5g_bw80base[rf_path][i] = (upper + lower) / 2;
		पूर्ण
		क्रम (i = 0; i < MAX_TX_COUNT; i++) अणु
			rtlefuse->txpwr_cckdअगरf[rf_path][i] =
				pwrinfo24g.cck_dअगरf[rf_path][i];
			rtlefuse->txpwr_legacyhtdअगरf[rf_path][i] =
				pwrinfo24g.ofdm_dअगरf[rf_path][i];
			rtlefuse->txpwr_ht20dअगरf[rf_path][i] =
				pwrinfo24g.bw20_dअगरf[rf_path][i];
			rtlefuse->txpwr_ht40dअगरf[rf_path][i] =
				pwrinfo24g.bw40_dअगरf[rf_path][i];

			rtlefuse->txpwr_5g_ofdmdअगरf[rf_path][i] =
				pwrinfo5g.ofdm_dअगरf[rf_path][i];
			rtlefuse->txpwr_5g_bw20dअगरf[rf_path][i] =
				pwrinfo5g.bw20_dअगरf[rf_path][i];
			rtlefuse->txpwr_5g_bw40dअगरf[rf_path][i] =
				pwrinfo5g.bw40_dअगरf[rf_path][i];
			rtlefuse->txpwr_5g_bw80dअगरf[rf_path][i] =
				pwrinfo5g.bw80_dअगरf[rf_path][i];
		पूर्ण
	पूर्ण
	/*bit0~2*/
	अगर (!स्वतःload_fail) अणु
		rtlefuse->eeprom_regulatory = hwinfo[EEPROM_RF_BOARD_OPTION] & 0x07;
		अगर (hwinfo[EEPROM_RF_BOARD_OPTION] == 0xFF)
			rtlefuse->eeprom_regulatory = 0;
	पूर्ण अन्यथा अणु
		rtlefuse->eeprom_regulatory = 0;
	पूर्ण

	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
	"eeprom_regulatory = 0x%x\n", rtlefuse->eeprom_regulatory);
पूर्ण

अटल व्योम _rtl8812ae_पढ़ो_pa_type(काष्ठा ieee80211_hw *hw, u8 *hwinfo,
				    bool स्वतःload_fail)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	अगर (!स्वतःload_fail) अणु
		rtlhal->pa_type_2g = hwinfo[0XBC];
		rtlhal->lna_type_2g = hwinfo[0XBD];
		अगर (rtlhal->pa_type_2g == 0xFF && rtlhal->lna_type_2g == 0xFF) अणु
			rtlhal->pa_type_2g = 0;
			rtlhal->lna_type_2g = 0;
		पूर्ण
		rtlhal->बाह्यal_pa_2g = ((rtlhal->pa_type_2g & BIT(5)) &&
					  (rtlhal->pa_type_2g & BIT(4))) ?
					 1 : 0;
		rtlhal->बाह्यal_lna_2g = ((rtlhal->lna_type_2g & BIT(7)) &&
					   (rtlhal->lna_type_2g & BIT(3))) ?
					  1 : 0;

		rtlhal->pa_type_5g = hwinfo[0XBC];
		rtlhal->lna_type_5g = hwinfo[0XBF];
		अगर (rtlhal->pa_type_5g == 0xFF && rtlhal->lna_type_5g == 0xFF) अणु
			rtlhal->pa_type_5g = 0;
			rtlhal->lna_type_5g = 0;
		पूर्ण
		rtlhal->बाह्यal_pa_5g = ((rtlhal->pa_type_5g & BIT(1)) &&
					  (rtlhal->pa_type_5g & BIT(0))) ?
					 1 : 0;
		rtlhal->बाह्यal_lna_5g = ((rtlhal->lna_type_5g & BIT(7)) &&
					   (rtlhal->lna_type_5g & BIT(3))) ?
					  1 : 0;
	पूर्ण अन्यथा अणु
		rtlhal->बाह्यal_pa_2g  = 0;
		rtlhal->बाह्यal_lna_2g = 0;
		rtlhal->बाह्यal_pa_5g  = 0;
		rtlhal->बाह्यal_lna_5g = 0;
	पूर्ण
पूर्ण

अटल व्योम _rtl8812ae_पढ़ो_amplअगरier_type(काष्ठा ieee80211_hw *hw, u8 *hwinfo,
					   bool स्वतःload_fail)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	u8 ext_type_pa_2g_a  = (hwinfo[0XBD] & BIT(2))      >> 2; /* 0XBD[2] */
	u8 ext_type_pa_2g_b  = (hwinfo[0XBD] & BIT(6))      >> 6; /* 0XBD[6] */
	u8 ext_type_pa_5g_a  = (hwinfo[0XBF] & BIT(2))      >> 2; /* 0XBF[2] */
	u8 ext_type_pa_5g_b  = (hwinfo[0XBF] & BIT(6))      >> 6; /* 0XBF[6] */
	/* 0XBD[1:0] */
	u8 ext_type_lna_2g_a = (hwinfo[0XBD] & (BIT(1) | BIT(0))) >> 0;
	/* 0XBD[5:4] */
	u8 ext_type_lna_2g_b = (hwinfo[0XBD] & (BIT(5) | BIT(4))) >> 4;
	/* 0XBF[1:0] */
	u8 ext_type_lna_5g_a = (hwinfo[0XBF] & (BIT(1) | BIT(0))) >> 0;
	/* 0XBF[5:4] */
	u8 ext_type_lna_5g_b = (hwinfo[0XBF] & (BIT(5) | BIT(4))) >> 4;

	_rtl8812ae_पढ़ो_pa_type(hw, hwinfo, स्वतःload_fail);

	/* [2.4G] Path A and B are both extPA */
	अगर ((rtlhal->pa_type_2g & (BIT(5) | BIT(4))) == (BIT(5) | BIT(4)))
		rtlhal->type_gpa  = ext_type_pa_2g_b  << 2 | ext_type_pa_2g_a;

	/* [5G] Path A and B are both extPA */
	अगर ((rtlhal->pa_type_5g & (BIT(1) | BIT(0))) == (BIT(1) | BIT(0)))
		rtlhal->type_apa  = ext_type_pa_5g_b  << 2 | ext_type_pa_5g_a;

	/* [2.4G] Path A and B are both extLNA */
	अगर ((rtlhal->lna_type_2g & (BIT(7) | BIT(3))) == (BIT(7) | BIT(3)))
		rtlhal->type_glna = ext_type_lna_2g_b << 2 | ext_type_lna_2g_a;

	/* [5G] Path A and B are both extLNA */
	अगर ((rtlhal->lna_type_5g & (BIT(7) | BIT(3))) == (BIT(7) | BIT(3)))
		rtlhal->type_alna = ext_type_lna_5g_b << 2 | ext_type_lna_5g_a;
पूर्ण

अटल व्योम _rtl8821ae_पढ़ो_pa_type(काष्ठा ieee80211_hw *hw, u8 *hwinfo,
				    bool स्वतःload_fail)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	अगर (!स्वतःload_fail) अणु
		rtlhal->pa_type_2g = hwinfo[0XBC];
		rtlhal->lna_type_2g = hwinfo[0XBD];
		अगर (rtlhal->pa_type_2g == 0xFF && rtlhal->lna_type_2g == 0xFF) अणु
			rtlhal->pa_type_2g = 0;
			rtlhal->lna_type_2g = 0;
		पूर्ण
		rtlhal->बाह्यal_pa_2g = (rtlhal->pa_type_2g & BIT(5)) ? 1 : 0;
		rtlhal->बाह्यal_lna_2g = (rtlhal->lna_type_2g & BIT(7)) ? 1 : 0;

		rtlhal->pa_type_5g = hwinfo[0XBC];
		rtlhal->lna_type_5g = hwinfo[0XBF];
		अगर (rtlhal->pa_type_5g == 0xFF && rtlhal->lna_type_5g == 0xFF) अणु
			rtlhal->pa_type_5g = 0;
			rtlhal->lna_type_5g = 0;
		पूर्ण
		rtlhal->बाह्यal_pa_5g = (rtlhal->pa_type_5g & BIT(1)) ? 1 : 0;
		rtlhal->बाह्यal_lna_5g = (rtlhal->lna_type_5g & BIT(7)) ? 1 : 0;
	पूर्ण अन्यथा अणु
		rtlhal->बाह्यal_pa_2g  = 0;
		rtlhal->बाह्यal_lna_2g = 0;
		rtlhal->बाह्यal_pa_5g  = 0;
		rtlhal->बाह्यal_lna_5g = 0;
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_पढ़ो_rfe_type(काष्ठा ieee80211_hw *hw, u8 *hwinfo,
			      bool स्वतःload_fail)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	अगर (!स्वतःload_fail) अणु
		अगर (hwinfo[EEPROM_RFE_OPTION] & BIT(7)) अणु
			अगर (rtlhal->बाह्यal_lna_5g) अणु
				अगर (rtlhal->बाह्यal_pa_5g) अणु
					अगर (rtlhal->बाह्यal_lna_2g &&
					    rtlhal->बाह्यal_pa_2g)
						rtlhal->rfe_type = 3;
					अन्यथा
						rtlhal->rfe_type = 0;
				पूर्ण अन्यथा अणु
					rtlhal->rfe_type = 2;
				पूर्ण
			पूर्ण अन्यथा अणु
				rtlhal->rfe_type = 4;
			पूर्ण
		पूर्ण अन्यथा अणु
			rtlhal->rfe_type = hwinfo[EEPROM_RFE_OPTION] & 0x3F;

			अगर (rtlhal->rfe_type == 4 &&
			    (rtlhal->बाह्यal_pa_5g ||
			     rtlhal->बाह्यal_pa_2g ||
			     rtlhal->बाह्यal_lna_5g ||
			     rtlhal->बाह्यal_lna_2g)) अणु
				अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
					rtlhal->rfe_type = 2;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rtlhal->rfe_type = 0x04;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"RFE Type: 0x%2x\n", rtlhal->rfe_type);
पूर्ण

अटल व्योम _rtl8812ae_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
					      bool स्वतः_load_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value;

	अगर (!स्वतः_load_fail) अणु
		value = *(u8 *)&hwinfo[EEPROM_RF_BOARD_OPTION];
		अगर (((value & 0xe0) >> 5) == 0x1)
			rtlpriv->btcoexist.btc_info.btcoexist = 1;
		अन्यथा
			rtlpriv->btcoexist.btc_info.btcoexist = 0;
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8812A;

		value = hwinfo[EEPROM_RF_BT_SETTING];
		rtlpriv->btcoexist.btc_info.ant_num = (value & 0x1);
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.btc_info.btcoexist = 0;
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8812A;
		rtlpriv->btcoexist.btc_info.ant_num = ANT_X2;
	पूर्ण
	/*move BT_InitHalVars() to init_sw_vars*/
पूर्ण

अटल व्योम _rtl8821ae_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
					      bool स्वतः_load_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value;
	u32 पंचांगpu_32;

	अगर (!स्वतः_load_fail) अणु
		पंचांगpu_32 = rtl_पढ़ो_dword(rtlpriv, REG_MULTI_FUNC_CTRL);
		अगर (पंचांगpu_32 & BIT(18))
			rtlpriv->btcoexist.btc_info.btcoexist = 1;
		अन्यथा
			rtlpriv->btcoexist.btc_info.btcoexist = 0;
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8821A;

		value = hwinfo[EEPROM_RF_BT_SETTING];
		rtlpriv->btcoexist.btc_info.ant_num = (value & 0x1);
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.btc_info.btcoexist = 0;
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8821A;
		rtlpriv->btcoexist.btc_info.ant_num = ANT_X2;
	पूर्ण
	/*move BT_InitHalVars() to init_sw_vars*/
पूर्ण

अटल व्योम _rtl8821ae_पढ़ो_adapter_info(काष्ठा ieee80211_hw *hw, bool b_pseuकरो_test)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक params[] = अणुRTL_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13पूर्ण;
	u8 *hwinfo;

	अगर (b_pseuकरो_test) अणु
		;/* need add */
	पूर्ण

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	अगर (!hwinfo)
		वापस;

	अगर (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		जाओ निकास;

	_rtl8821ae_पढ़ो_txघातer_info_from_hwpg(hw, rtlefuse->स्वतःload_failflag,
					       hwinfo);

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
		_rtl8812ae_पढ़ो_amplअगरier_type(hw, hwinfo,
					       rtlefuse->स्वतःload_failflag);
		_rtl8812ae_पढ़ो_bt_coexist_info_from_hwpg(hw,
				rtlefuse->स्वतःload_failflag, hwinfo);
	पूर्ण अन्यथा अणु
		_rtl8821ae_पढ़ो_pa_type(hw, hwinfo, rtlefuse->स्वतःload_failflag);
		_rtl8821ae_पढ़ो_bt_coexist_info_from_hwpg(hw,
				rtlefuse->स्वतःload_failflag, hwinfo);
	पूर्ण

	_rtl8821ae_पढ़ो_rfe_type(hw, hwinfo, rtlefuse->स्वतःload_failflag);
	/*board type*/
	rtlefuse->board_type = ODM_BOARD_DEFAULT;
	अगर (rtlhal->बाह्यal_lna_2g != 0)
		rtlefuse->board_type |= ODM_BOARD_EXT_LNA;
	अगर (rtlhal->बाह्यal_lna_5g != 0)
		rtlefuse->board_type |= ODM_BOARD_EXT_LNA_5G;
	अगर (rtlhal->बाह्यal_pa_2g != 0)
		rtlefuse->board_type |= ODM_BOARD_EXT_PA;
	अगर (rtlhal->बाह्यal_pa_5g != 0)
		rtlefuse->board_type |= ODM_BOARD_EXT_PA_5G;

	अगर (rtlpriv->btcoexist.btc_info.btcoexist == 1)
		rtlefuse->board_type |= ODM_BOARD_BT;

	rtlhal->board_type = rtlefuse->board_type;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"board_type = 0x%x\n", rtlefuse->board_type);

	rtlefuse->eeprom_channelplan = *(u8 *)&hwinfo[EEPROM_CHANNELPLAN];
	अगर (rtlefuse->eeprom_channelplan == 0xff)
		rtlefuse->eeprom_channelplan = 0x7F;

	/* set channel plan from efuse */
	rtlefuse->channel_plan = rtlefuse->eeprom_channelplan;

	/*parse xtal*/
	rtlefuse->crystalcap = hwinfo[EEPROM_XTAL_8821AE];
	अगर (rtlefuse->crystalcap == 0xFF)
		rtlefuse->crystalcap = 0x20;

	rtlefuse->eeprom_thermalmeter = *(u8 *)&hwinfo[EEPROM_THERMAL_METER];
	अगर ((rtlefuse->eeprom_thermalmeter == 0xff) ||
	    rtlefuse->स्वतःload_failflag) अणु
		rtlefuse->apk_thermalmeterignore = true;
		rtlefuse->eeprom_thermalmeter = 0xff;
	पूर्ण

	rtlefuse->thermalmeter[0] = rtlefuse->eeprom_thermalmeter;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"thermalmeter = 0x%x\n", rtlefuse->eeprom_thermalmeter);

	अगर (!rtlefuse->स्वतःload_failflag) अणु
		rtlefuse->antenna_भाग_cfg =
		  (hwinfo[EEPROM_RF_BOARD_OPTION] & 0x18) >> 3;
		अगर (hwinfo[EEPROM_RF_BOARD_OPTION] == 0xff)
			rtlefuse->antenna_भाग_cfg = 0;

		अगर (rtlpriv->btcoexist.btc_info.btcoexist == 1 &&
		    rtlpriv->btcoexist.btc_info.ant_num == ANT_X1)
			rtlefuse->antenna_भाग_cfg = 0;

		rtlefuse->antenna_भाग_प्रकारype = hwinfo[EEPROM_RF_ANTENNA_OPT_88E];
		अगर (rtlefuse->antenna_भाग_प्रकारype == 0xff)
			rtlefuse->antenna_भाग_प्रकारype = FIXED_HW_ANTDIV;
	पूर्ण अन्यथा अणु
		rtlefuse->antenna_भाग_cfg = 0;
		rtlefuse->antenna_भाग_प्रकारype = 0;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"SWAS: bHwAntDiv = %x, TRxAntDivType = %x\n",
		rtlefuse->antenna_भाग_cfg, rtlefuse->antenna_भाग_प्रकारype);

	rtlpriv->ledctl.led_खोलोdrain = true;

	अगर (rtlhal->oem_id == RT_CID_DEFAULT) अणु
		चयन (rtlefuse->eeprom_oemid) अणु
		हाल RT_CID_DEFAULT:
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
			अवरोध;
		पूर्ण
	पूर्ण
निकास:
	kमुक्त(hwinfo);
पूर्ण

/*अटल व्योम _rtl8821ae_hal_customized_behavior(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
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
पूर्ण*/

व्योम rtl8821ae_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_u1b;

	rtlhal->version = _rtl8821ae_पढ़ो_chip_version(hw);
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
		_rtl8821ae_पढ़ो_adapter_info(hw, false);
	पूर्ण अन्यथा अणु
		pr_err("Autoload ERR!!\n");
	पूर्ण
	/*hal_ReadRFType_8812A()*/
	/* _rtl8821ae_hal_customized_behavior(hw); */
पूर्ण

अटल व्योम rtl8821ae_update_hal_rate_table(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 ratr_value;
	u8 ratr_index = 0;
	u8 b_nmode = mac->ht_enable;
	u8 mimo_ps = IEEE80211_SMPS_OFF;
	u16 लघुgi_rate;
	u32 पंचांगp_ratr_value;
	u8 curtxbw_40mhz = mac->bw_40;
	u8 b_curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
				1 : 0;
	u8 b_curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
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
		अगर (mimo_ps == IEEE80211_SMPS_STATIC) अणु
			ratr_value &= 0x0007F005;
		पूर्ण अन्यथा अणु
			u32 ratr_mask;

			अगर (get_rf_type(rtlphy) == RF_1T2R ||
			    get_rf_type(rtlphy) == RF_1T1R)
				ratr_mask = 0x000ff005;
			अन्यथा
				ratr_mask = 0x0f0ff005;

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

	अगर ((rtlpriv->btcoexist.bt_coexistence) &&
	     (rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4) &&
	     (rtlpriv->btcoexist.bt_cur_state) &&
	     (rtlpriv->btcoexist.bt_ant_isolation) &&
	     ((rtlpriv->btcoexist.bt_service == BT_SCO) ||
	     (rtlpriv->btcoexist.bt_service == BT_BUSY)))
		ratr_value &= 0x0fffcfc0;
	अन्यथा
		ratr_value &= 0x0FFFFFFF;

	अगर (b_nmode && ((curtxbw_40mhz &&
			 b_curलघुgi_40mhz) || (!curtxbw_40mhz &&
						 b_curलघुgi_20mhz))) अणु
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

अटल u32 _rtl8821ae_rate_to_biपंचांगap_2ssvht(__le16 vht_rate)
अणु
	u8 i, j, पंचांगp_rate;
	u32 rate_biपंचांगap = 0;

	क्रम (i = j = 0; i < 4; i += 2, j += 10) अणु
		पंचांगp_rate = (le16_to_cpu(vht_rate) >> i) & 3;

		चयन (पंचांगp_rate) अणु
		हाल 2:
			rate_biपंचांगap = rate_biपंचांगap | (0x03ff << j);
			अवरोध;
		हाल 1:
			rate_biपंचांगap = rate_biपंचांगap | (0x01ff << j);
			अवरोध;
		हाल 0:
			rate_biपंचांगap = rate_biपंचांगap | (0x00ff << j);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rate_biपंचांगap;
पूर्ण

अटल u32 _rtl8821ae_set_ra_vht_ratr_biपंचांगap(काष्ठा ieee80211_hw *hw,
					     क्रमागत wireless_mode wirelessmode,
					     u32 ratr_biपंचांगap)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 ret_biपंचांगap = ratr_biपंचांगap;

	अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40
		|| rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80)
		ret_biपंचांगap = ratr_biपंचांगap;
	अन्यथा अगर (wirelessmode == WIRELESS_MODE_AC_5G
		|| wirelessmode == WIRELESS_MODE_AC_24G) अणु
		अगर (rtlphy->rf_type == RF_1T1R)
			ret_biपंचांगap = ratr_biपंचांगap & (~BIT21);
		अन्यथा
			ret_biपंचांगap = ratr_biपंचांगap & (~(BIT31|BIT21));
	पूर्ण

	वापस ret_biपंचांगap;
पूर्ण

अटल u8 _rtl8821ae_get_vht_eni(क्रमागत wireless_mode wirelessmode,
			u32 ratr_biपंचांगap)
अणु
	u8 ret = 0;
	अगर (wirelessmode < WIRELESS_MODE_N_24G)
		ret =  0;
	अन्यथा अगर (wirelessmode == WIRELESS_MODE_AC_24G) अणु
		अगर (ratr_biपंचांगap & 0xfff00000)	/* Mix , 2SS */
			ret = 3;
		अन्यथा					/* Mix, 1SS */
			ret = 2;
	पूर्ण अन्यथा अगर (wirelessmode == WIRELESS_MODE_AC_5G) अणु
			ret = 1;
	पूर्ण /* VHT */

	वापस ret << 4;
पूर्ण

अटल u8 _rtl8821ae_get_ra_ldpc(काष्ठा ieee80211_hw *hw,
			     u8 mac_id, काष्ठा rtl_sta_info *sta_entry,
			     क्रमागत wireless_mode wirelessmode)
अणु
	u8 b_ldpc = 0;
	/*not support ldpc, करो not खोलो*/
	वापस b_ldpc << 2;
पूर्ण

अटल u8 _rtl8821ae_get_ra_rftype(काष्ठा ieee80211_hw *hw,
			  क्रमागत wireless_mode wirelessmode,
			  u32 ratr_biपंचांगap)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 rf_type = RF_1T1R;

	अगर (rtlphy->rf_type == RF_1T1R)
		rf_type = RF_1T1R;
	अन्यथा अगर (wirelessmode == WIRELESS_MODE_AC_5G
		|| wirelessmode == WIRELESS_MODE_AC_24G
		|| wirelessmode == WIRELESS_MODE_AC_ONLY) अणु
		अगर (ratr_biपंचांगap & 0xffc00000)
			rf_type = RF_2T2R;
	पूर्ण अन्यथा अगर (wirelessmode == WIRELESS_MODE_N_5G
		|| wirelessmode == WIRELESS_MODE_N_24G) अणु
		अगर (ratr_biपंचांगap & 0xfff00000)
			rf_type = RF_2T2R;
	पूर्ण

	वापस rf_type;
पूर्ण

अटल bool _rtl8821ae_get_ra_लघुgi(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
			      u8 mac_id)
अणु
	bool b_लघु_gi = false;
	u8 b_curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
				1 : 0;
	u8 b_curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	u8 b_curलघुgi_80mhz = 0;
	b_curलघुgi_80mhz = (sta->vht_cap.cap &
			      IEEE80211_VHT_CAP_SHORT_GI_80) ? 1 : 0;

	अगर (mac_id == MAC_ID_STATIC_FOR_BROADCAST_MULTICAST)
			b_लघु_gi = false;

	अगर (b_curलघुgi_40mhz || b_curलघुgi_80mhz
		|| b_curलघुgi_20mhz)
		b_लघु_gi = true;

	वापस b_लघु_gi;
पूर्ण

अटल व्योम rtl8821ae_update_hal_rate_mask(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u32 ratr_biपंचांगap;
	u8 ratr_index;
	क्रमागत wireless_mode wirelessmode = 0;
	u8 curtxbw_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40)
				? 1 : 0;
	bool b_लघुgi = false;
	u8 rate_mask[7];
	u8 macid = 0;
	u8 mimo_ps = IEEE80211_SMPS_OFF;
	u8 rf_type;

	sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
	wirelessmode = sta_entry->wireless_mode;

	rtl_dbg(rtlpriv, COMP_RATR, DBG_LOUD,
		"wireless mode = 0x%x\n", wirelessmode);
	अगर (mac->opmode == NL80211_IFTYPE_STATION ||
		mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		curtxbw_40mhz = mac->bw_40;
	पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;
	अगर (wirelessmode == WIRELESS_MODE_N_5G ||
	    wirelessmode == WIRELESS_MODE_AC_5G ||
	    wirelessmode == WIRELESS_MODE_A)
		ratr_biपंचांगap = sta->supp_rates[NL80211_BAND_5GHZ] << 4;
	अन्यथा
		ratr_biपंचांगap = sta->supp_rates[NL80211_BAND_2GHZ];

	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_biपंचांगap = 0xfff;

	अगर (wirelessmode == WIRELESS_MODE_N_24G
		|| wirelessmode == WIRELESS_MODE_N_5G)
		ratr_biपंचांगap |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
				sta->ht_cap.mcs.rx_mask[0] << 12);
	अन्यथा अगर (wirelessmode == WIRELESS_MODE_AC_24G
		|| wirelessmode == WIRELESS_MODE_AC_5G
		|| wirelessmode == WIRELESS_MODE_AC_ONLY)
		ratr_biपंचांगap |= _rtl8821ae_rate_to_biपंचांगap_2ssvht(
				sta->vht_cap.vht_mcs.rx_mcs_map) << 12;

	b_लघुgi = _rtl8821ae_get_ra_लघुgi(hw, sta, macid);
	rf_type = _rtl8821ae_get_ra_rftype(hw, wirelessmode, ratr_biपंचांगap);

/*mac id owner*/
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

		अगर (mimo_ps == IEEE80211_SMPS_STATIC
			|| mimo_ps == IEEE80211_SMPS_DYNAMIC) अणु
			अगर (rssi_level == 1)
				ratr_biपंचांगap &= 0x000f0000;
			अन्यथा अगर (rssi_level == 2)
				ratr_biपंचांगap &= 0x000ff000;
			अन्यथा
				ratr_biपंचांगap &= 0x000ff005;
		पूर्ण अन्यथा अणु
			अगर (rf_type == RF_1T1R) अणु
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
						ratr_biपंचांगap &= 0x0fff0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x0ffff000;
					अन्यथा
						ratr_biपंचांगap &= 0x0ffff015;
				पूर्ण अन्यथा अणु
					अगर (rssi_level == 1)
						ratr_biपंचांगap &= 0x0fff0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x0ffff000;
					अन्यथा
						ratr_biपंचांगap &= 0x0ffff005;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;

	हाल WIRELESS_MODE_AC_24G:
		ratr_index = RATR_INX_WIRELESS_AC_24N;
		अगर (rssi_level == 1)
			ratr_biपंचांगap &= 0xfc3f0000;
		अन्यथा अगर (rssi_level == 2)
			ratr_biपंचांगap &= 0xfffff000;
		अन्यथा
			ratr_biपंचांगap &= 0xffffffff;
		अवरोध;

	हाल WIRELESS_MODE_AC_5G:
		ratr_index = RATR_INX_WIRELESS_AC_5N;

		अगर (rf_type == RF_1T1R) अणु
			अगर (rssi_level == 1)	/*add by Gary क्रम ac-series*/
				ratr_biपंचांगap &= 0x003f8000;
			अन्यथा अगर (rssi_level == 2)
				ratr_biपंचांगap &= 0x003ff000;
			अन्यथा
				ratr_biपंचांगap &= 0x003ff010;
		पूर्ण अन्यथा अणु
			अगर (rssi_level == 1)
				ratr_biपंचांगap &= 0xfe3f8000;
			अन्यथा अगर (rssi_level == 2)
				ratr_biपंचांगap &= 0xfffff000;
			अन्यथा
				ratr_biपंचांगap &= 0xfffff010;
		पूर्ण
		अवरोध;

	शेष:
		ratr_index = RATR_INX_WIRELESS_NGB;

		अगर (rf_type == RF_1T2R)
			ratr_biपंचांगap &= 0x000ff0ff;
		अन्यथा
			ratr_biपंचांगap &= 0x0f8ff0ff;
		अवरोध;
	पूर्ण

	ratr_index = rtl_mrate_idx_to_arfr_id(hw, ratr_index, wirelessmode);
	sta_entry->ratr_index = ratr_index;
	ratr_biपंचांगap = _rtl8821ae_set_ra_vht_ratr_biपंचांगap(hw, wirelessmode,
							ratr_biपंचांगap);

	rtl_dbg(rtlpriv, COMP_RATR, DBG_LOUD,
		"ratr_bitmap :%x\n", ratr_biपंचांगap);

	/* *(u32 *)& rate_mask = EF4BYTE((ratr_biपंचांगap & 0x0fffffff) |
				       (ratr_index << 28)); */

	rate_mask[0] = macid;
	rate_mask[1] = ratr_index | (b_लघुgi ? 0x80 : 0x00);
	rate_mask[2] = rtlphy->current_chan_bw | ((!update_bw) << 3)
			   | _rtl8821ae_get_vht_eni(wirelessmode, ratr_biपंचांगap)
			   | _rtl8821ae_get_ra_ldpc(hw, macid, sta_entry, wirelessmode);

	rate_mask[3] = (u8)(ratr_biपंचांगap & 0x000000ff);
	rate_mask[4] = (u8)((ratr_biपंचांगap & 0x0000ff00) >> 8);
	rate_mask[5] = (u8)((ratr_biपंचांगap & 0x00ff0000) >> 16);
	rate_mask[6] = (u8)((ratr_biपंचांगap & 0xff000000) >> 24);

	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"Rate_index:%x, ratr_val:%x, %x:%x:%x:%x:%x:%x:%x\n",
		ratr_index, ratr_biपंचांगap,
		rate_mask[0], rate_mask[1],
		 rate_mask[2], rate_mask[3],
		 rate_mask[4], rate_mask[5],
		 rate_mask[6]);
	rtl8821ae_fill_h2c_cmd(hw, H2C_8821AE_RA_MASK, 7, rate_mask);
	_rtl8821ae_set_bcn_ctrl_reg(hw, BIT(3), 0);
पूर्ण

व्योम rtl8821ae_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अगर (rtlpriv->dm.useramask)
		rtl8821ae_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
	अन्यथा
		/*rtl_dbg(rtlpriv, COMP_RATR,DBG_LOUD,
			   "rtl8821ae_update_hal_rate_tbl() Error! 8821ae FW RA Only\n");*/
		rtl8821ae_update_hal_rate_table(hw, sta);
पूर्ण

व्योम rtl8821ae_update_channel_access_setting(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 wireless_mode = mac->mode;
	u8 sअगरs_समयr, r2t_sअगरs;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME,
				      (u8 *)&mac->slot_समय);
	अगर (wireless_mode == WIRELESS_MODE_G)
		sअगरs_समयr = 0x0a;
	अन्यथा
		sअगरs_समयr = 0x0e;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SIFS, (u8 *)&sअगरs_समयr);

	r2t_sअगरs = 0xa;

	अगर (wireless_mode == WIRELESS_MODE_AC_5G &&
	    (mac->vht_ldpc_cap & LDPC_VHT_ENABLE_RX) &&
	    (mac->vht_stbc_cap & STBC_VHT_ENABLE_RX)) अणु
		अगर (mac->venकरोr == PEER_ATH)
			r2t_sअगरs = 0x8;
		अन्यथा
			r2t_sअगरs = 0xa;
	पूर्ण अन्यथा अगर (wireless_mode == WIRELESS_MODE_AC_5G) अणु
		r2t_sअगरs = 0xa;
	पूर्ण

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_R2T_SIFS, (u8 *)&r2t_sअगरs);
पूर्ण

bool rtl8821ae_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	क्रमागत rf_pwrstate e_rfघातerstate_toset;
	u8 u1पंचांगp = 0;
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
			rtl_पढ़ो_byte(rtlpriv,
					REG_GPIO_IO_SEL_2) & ~(BIT(1)));

	u1पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_PIN_CTRL_2);

	अगर (rtlphy->polarity_ctl)
		e_rfघातerstate_toset = (u1पंचांगp & BIT(1)) ? ERFOFF : ERFON;
	अन्यथा
		e_rfघातerstate_toset = (u1पंचांगp & BIT(1)) ? ERFON : ERFOFF;

	अगर ((ppsc->hwradiooff) && (e_rfघातerstate_toset == ERFON)) अणु
		rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
			"GPIOChangeRF  - HW Radio ON, RF ON\n");

		e_rfघातerstate_toset = ERFON;
		ppsc->hwradiooff = false;
		b_actuallyset = true;
	पूर्ण अन्यथा अगर ((!ppsc->hwradiooff)
		   && (e_rfघातerstate_toset == ERFOFF)) अणु
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

व्योम rtl8821ae_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
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
					entry_id = rtl_cam_get_मुक्त_entry(hw, p_macaddr);
					अगर (entry_id >=  TOTAL_CAM_ENTRY) अणु
						pr_err("an not find free hwsecurity cam entry\n");
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

व्योम rtl8821ae_bt_reg_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* 0:Low, 1:High, 2:From Efuse. */
	rtlpriv->btcoexist.reg_bt_iso = 2;
	/* 0:Idle, 1:None-SCO, 2:SCO, 3:From Counter. */
	rtlpriv->btcoexist.reg_bt_sco = 3;
	/* 0:Disable BT control A-MPDU, 1:Enable BT control A-MPDU. */
	rtlpriv->btcoexist.reg_bt_sco = 0;
पूर्ण

व्योम rtl8821ae_bt_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_init_hw_config(rtlpriv);
पूर्ण

व्योम rtl8821ae_suspend(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

व्योम rtl8821ae_resume(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

/* Turn on AAP (RCR:bit 0) क्रम promicuous mode. */
व्योम rtl8821ae_allow_all_destaddr(काष्ठा ieee80211_hw *hw,
	bool allow_all_da, bool ग_लिखो_पूर्णांकo_reg)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	अगर (allow_all_da) /* Set BIT0 */
		rtlpci->receive_config |= RCR_AAP;
	अन्यथा /* Clear BIT0 */
		rtlpci->receive_config &= ~RCR_AAP;

	अगर (ग_लिखो_पूर्णांकo_reg)
		rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);

	rtl_dbg(rtlpriv, COMP_TURBO | COMP_INIT, DBG_LOUD,
		"receive_config=0x%08X, write_into_reg=%d\n",
		rtlpci->receive_config, ग_लिखो_पूर्णांकo_reg);
पूर्ण

/* WKFMCAMAddAllEntry8812 */
व्योम rtl8821ae_add_wowlan_pattern(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_wow_pattern *rtl_pattern,
				  u8 index)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 cam = 0;
	u8 addr = 0;
	u16 rxbuf_addr;
	u8 पंचांगp, count = 0;
	u16 cam_start;
	u16 offset;

	/* Count the WFCAM entry start offset. */

	/* RX page size = 128 byte */
	offset = MAX_RX_DMA_BUFFER_SIZE_8812 / 128;
	/* We should start from the boundry */
	cam_start = offset * 128;

	/* Enable Rx packet buffer access. */
	rtl_ग_लिखो_byte(rtlpriv, REG_PKT_BUFF_ACCESS_CTRL, RXPKT_BUF_SELECT);
	क्रम (addr = 0; addr < WKFMCAM_ADDR_NUM; addr++) अणु
		/* Set Rx packet buffer offset.
		 * RXBufer poपूर्णांकer increases 1,
		 * we can access 8 bytes in Rx packet buffer.
		 * CAM start offset (unit: 1 byte) =  index*WKFMCAM_SIZE
		 * RXBufer addr = (CAM start offset +
		 *                 per entry offset of a WKFM CAM)/8
		 *	* index: The index of the wake up frame mask
		 *	* WKFMCAM_SIZE: the total size of one WKFM CAM
		 *	* per entry offset of a WKFM CAM: Addr*4 bytes
		 */
		rxbuf_addr = (cam_start + index * WKFMCAM_SIZE + addr * 4) >> 3;
		/* Set R/W start offset */
		rtl_ग_लिखो_word(rtlpriv, REG_PKTBUF_DBG_CTRL, rxbuf_addr);

		अगर (addr == 0) अणु
			cam = BIT(31) | rtl_pattern->crc;

			अगर (rtl_pattern->type == UNICAST_PATTERN)
				cam |= BIT(24);
			अन्यथा अगर (rtl_pattern->type == MULTICAST_PATTERN)
				cam |= BIT(25);
			अन्यथा अगर (rtl_pattern->type == BROADCAST_PATTERN)
				cam |= BIT(26);

			rtl_ग_लिखो_dword(rtlpriv, REG_PKTBUF_DBG_DATA_L, cam);
			rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
				"WRITE entry[%d] 0x%x: %x\n", addr,
				REG_PKTBUF_DBG_DATA_L, cam);

			/* Write to Rx packet buffer. */
			rtl_ग_लिखो_word(rtlpriv, REG_RXPKTBUF_CTRL, 0x0f01);
		पूर्ण अन्यथा अगर (addr == 2 || addr == 4) अणु/* WKFM[127:0] */
			cam = rtl_pattern->mask[addr - 2];

			rtl_ग_लिखो_dword(rtlpriv, REG_PKTBUF_DBG_DATA_L, cam);
			rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
				"WRITE entry[%d] 0x%x: %x\n", addr,
				REG_PKTBUF_DBG_DATA_L, cam);

			rtl_ग_लिखो_word(rtlpriv, REG_RXPKTBUF_CTRL, 0x0f01);
		पूर्ण अन्यथा अगर (addr == 3 || addr == 5) अणु/* WKFM[127:0] */
			cam = rtl_pattern->mask[addr - 2];

			rtl_ग_लिखो_dword(rtlpriv, REG_PKTBUF_DBG_DATA_H, cam);
			rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
				"WRITE entry[%d] 0x%x: %x\n", addr,
				REG_PKTBUF_DBG_DATA_H, cam);

			rtl_ग_लिखो_word(rtlpriv, REG_RXPKTBUF_CTRL, 0xf001);
		पूर्ण

		count = 0;
		करो अणु
			पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXPKTBUF_CTRL);
			udelay(2);
			count++;
		पूर्ण जबतक (पंचांगp && count < 100);

		WARN_ONCE((count >= 100),
			  "rtl8821ae: Write wake up frame mask FAIL %d value!\n",
			  पंचांगp);
	पूर्ण
	/* Disable Rx packet buffer access. */
	rtl_ग_लिखो_byte(rtlpriv, REG_PKT_BUFF_ACCESS_CTRL,
		       DISABLE_TRXPKT_BUF_ACCESS);
पूर्ण
