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
#समावेश "../rtl8723com/phy_common.h"
#समावेश "dm.h"
#समावेश "../rtl8723com/dm_common.h"
#समावेश "fw.h"
#समावेश "../rtl8723com/fw_common.h"
#समावेश "led.h"
#समावेश "hw.h"
#समावेश "../pwrseqcmd.h"
#समावेश "pwrseq.h"
#समावेश "../btcoexist/rtl_btc.h"
#समावेश <linux/kernel.h>

#घोषणा LLT_CONFIG	5

अटल व्योम _rtl8723be_वापस_beacon_queue_skb(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl8723be_set_bcn_ctrl_reg(काष्ठा ieee80211_hw *hw,
					u8 set_bits, u8 clear_bits)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpci->reg_bcn_ctrl_val |= set_bits;
	rtlpci->reg_bcn_ctrl_val &= ~clear_bits;

	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8)rtlpci->reg_bcn_ctrl_val);
पूर्ण

अटल व्योम _rtl8723be_stop_tx_beacon(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl8723be_resume_tx_beacon(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl8723be_enable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl8723be_set_bcn_ctrl_reg(hw, 0, BIT(1));
पूर्ण

अटल व्योम _rtl8723be_disable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	_rtl8723be_set_bcn_ctrl_reg(hw, BIT(1), 0);
पूर्ण

अटल व्योम _rtl8723be_set_fw_घड़ी_on(काष्ठा ieee80211_hw *hw, u8 rpwm_val,
				       bool b_need_turn_off_ckk)
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

	अगर (IS_IN_LOW_POWER_STATE(rtlhal->fw_ps_state)) अणु
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
				rtlhal->fw_ps_state = FW_PS_STATE_RF_ON;
				rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
					"Receive CPWM INT!!! Set pHalData->FwPSState = %X\n",
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

अटल व्योम _rtl8723be_set_fw_घड़ी_off(काष्ठा ieee80211_hw *hw, u8 rpwm_val)
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

अटल व्योम _rtl8723be_set_fw_ps_rf_on(काष्ठा ieee80211_hw *hw)
अणु
	u8 rpwm_val = 0;
	rpwm_val |= (FW_PS_STATE_RF_OFF | FW_PS_ACK);
	_rtl8723be_set_fw_घड़ी_on(hw, rpwm_val, true);
पूर्ण

अटल व्योम _rtl8723be_fwlps_leave(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inps = false;
	u8 rpwm_val = 0, fw_pwrmode = FW_PS_ACTIVE_MODE;

	अगर (ppsc->low_घातer_enable) अणु
		rpwm_val = (FW_PS_STATE_ALL_ON | FW_PS_ACK);/* RF on */
		_rtl8723be_set_fw_घड़ी_on(hw, rpwm_val, false);
		rtlhal->allow_sw_to_change_hwclc = false;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      (u8 *)(&fw_pwrmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
	पूर्ण अन्यथा अणु
		rpwm_val = FW_PS_STATE_ALL_ON;	/* RF on */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
					      (u8 *)(&rpwm_val));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      (u8 *)(&fw_pwrmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
	पूर्ण

पूर्ण

अटल व्योम _rtl8723be_fwlps_enter(काष्ठा ieee80211_hw *hw)
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
		_rtl8723be_set_fw_घड़ी_off(hw, rpwm_val);
	पूर्ण अन्यथा अणु
		rpwm_val = FW_PS_STATE_RF_OFF;	/* RF off */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inps));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
					      (u8 *)(&ppsc->fwctrl_psmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
					      (u8 *)(&rpwm_val));
	पूर्ण

पूर्ण

व्योम rtl8723be_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
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
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl8723be_करोwnload_rsvd_page(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp_regcr, पंचांगp_reg422, bcnvalid_reg;
	u8 count = 0, dlbcn_count = 0;
	bool b_recover = false;

	पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1,
		       (पंचांगp_regcr | BIT(0)));

	_rtl8723be_set_bcn_ctrl_reg(hw, 0, BIT(3));
	_rtl8723be_set_bcn_ctrl_reg(hw, BIT(4), 0);

	पंचांगp_reg422 = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp_reg422 & (~BIT(6)));
	अगर (पंचांगp_reg422 & BIT(6))
		b_recover = true;

	करो अणु
		bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv, REG_TDECTRL + 2);
		rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 2,
			       (bcnvalid_reg | BIT(0)));
		_rtl8723be_वापस_beacon_queue_skb(hw);

		rtl8723be_set_fw_rsvdpagepkt(hw, 0);
		bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv, REG_TDECTRL + 2);
		count = 0;
		जबतक (!(bcnvalid_reg & BIT(0)) && count < 20) अणु
			count++;
			udelay(10);
			bcnvalid_reg = rtl_पढ़ो_byte(rtlpriv,
						     REG_TDECTRL + 2);
		पूर्ण
		dlbcn_count++;
	पूर्ण जबतक (!(bcnvalid_reg & BIT(0)) && dlbcn_count < 5);

	अगर (bcnvalid_reg & BIT(0))
		rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 2, BIT(0));

	_rtl8723be_set_bcn_ctrl_reg(hw, BIT(3), 0);
	_rtl8723be_set_bcn_ctrl_reg(hw, 0, BIT(4));

	अगर (b_recover)
		rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, पंचांगp_reg422);

	पंचांगp_regcr = rtl_पढ़ो_byte(rtlpriv, REG_CR + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, (पंचांगp_regcr & ~(BIT(0))));
पूर्ण

व्योम rtl8723be_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 idx;

	चयन (variable) अणु
	हाल HW_VAR_ETHER_ADDR:
		क्रम (idx = 0; idx < ETH_ALEN; idx++)
			rtl_ग_लिखो_byte(rtlpriv, (REG_MACID + idx), val[idx]);
		अवरोध;
	हाल HW_VAR_BASIC_RATE:अणु
		u16 b_rate_cfg = ((u16 *)val)[0];
		u8 rate_index = 0;
		b_rate_cfg = b_rate_cfg & 0x15f;
		b_rate_cfg |= 0x01;
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR, b_rate_cfg & 0xff);
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 1, (b_rate_cfg >> 8) & 0xff);
		जबतक (b_rate_cfg > 0x1) अणु
			b_rate_cfg = (b_rate_cfg >> 1);
			rate_index++;
		पूर्ण
		rtl_ग_लिखो_byte(rtlpriv, REG_INIRTS_RATE_SEL, rate_index);
		पूर्ण
		अवरोध;
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

		rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
			"HW_VAR_SLOT_TIME %x\n", val[0]);

		rtl_ग_लिखो_byte(rtlpriv, REG_SLOT, val[0]);

		क्रम (e_aci = 0; e_aci < AC_MAX; e_aci++) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      (u8 *)(&e_aci));
		पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_ACK_PREAMBLE:अणु
		u8 reg_पंचांगp;
		u8 लघु_preamble = (bool)(*(u8 *)val);
		reg_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_TRXPTCL_CTL + 2);
		अगर (लघु_preamble) अणु
			reg_पंचांगp |= 0x02;
			rtl_ग_लिखो_byte(rtlpriv, REG_TRXPTCL_CTL + 2, reg_पंचांगp);
		पूर्ण अन्यथा अणु
			reg_पंचांगp &= 0xFD;
			rtl_ग_लिखो_byte(rtlpriv, REG_TRXPTCL_CTL + 2, reg_पंचांगp);
		पूर्ण
		पूर्ण
		अवरोध;
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

			mac->min_space_cfg = ((mac->min_space_cfg & 0xf8) |
					      min_spacing_to_set);

			*val = min_spacing_to_set;

			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"Set HW_VAR_AMPDU_MIN_SPACE: %#x\n",
				mac->min_space_cfg);

			rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE,
				       mac->min_space_cfg);
		पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_SHORTGI_DENSITY:अणु
		u8 density_to_set;

		density_to_set = *((u8 *)val);
		mac->min_space_cfg |= (density_to_set << 3);

		rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
			"Set HW_VAR_SHORTGI_DENSITY: %#x\n",
			mac->min_space_cfg);

		rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE,
			       mac->min_space_cfg);
		पूर्ण
		अवरोध;
	हाल HW_VAR_AMPDU_FACTOR:अणु
		u8 regtoset_normal[4] = अणु0x41, 0xa8, 0x72, 0xb9पूर्ण;
		u8 factor_toset;
		u8 *p_regtoset = शून्य;
		u8 index = 0;

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

				अगर ((p_regtoset[index] & 0x0f) > factor_toset)
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
		पूर्ण
		अवरोध;
	हाल HW_VAR_AC_PARAM:अणु
		u8 e_aci = *((u8 *)val);
		rtl8723_dm_init_edca_turbo(hw);

		अगर (rtlpci->acm_method != EACMWAY2_SW)
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ACM_CTRL,
						      (u8 *)(&e_aci));
		पूर्ण
		अवरोध;
	हाल HW_VAR_ACM_CTRL:अणु
		u8 e_aci = *((u8 *)val);
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
		पूर्ण
		अवरोध;
	हाल HW_VAR_RCR:
		rtl_ग_लिखो_dword(rtlpriv, REG_RCR, ((u32 *)(val))[0]);
		rtlpci->receive_config = ((u32 *)(val))[0];
		अवरोध;
	हाल HW_VAR_RETRY_LIMIT:अणु
		u8 retry_limit = ((u8 *)(val))[0];

		rtl_ग_लिखो_word(rtlpriv, REG_RL,
			       retry_limit << RETRY_LIMIT_SHORT_SHIFT |
			       retry_limit << RETRY_LIMIT_LONG_SHIFT);
		पूर्ण
		अवरोध;
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
		rtl8723be_phy_set_io_cmd(hw, (*(क्रमागत io_type *)val));
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
		rtl8723be_set_fw_pwrmode_cmd(hw, (*(u8 *)val));
		अवरोध;
	हाल HW_VAR_FW_PSMODE_STATUS:
		ppsc->fw_current_inpsmode = *((bool *)val);
		अवरोध;
	हाल HW_VAR_RESUME_CLK_ON:
		_rtl8723be_set_fw_ps_rf_on(hw);
		अवरोध;
	हाल HW_VAR_FW_LPS_ACTION:अणु
		bool b_enter_fwlps = *((bool *)val);

		अगर (b_enter_fwlps)
			_rtl8723be_fwlps_enter(hw);
		अन्यथा
			_rtl8723be_fwlps_leave(hw);
		पूर्ण
		अवरोध;
	हाल HW_VAR_H2C_FW_JOINBSSRPT:अणु
		u8 mstatus = (*(u8 *)val);

		अगर (mstatus == RT_MEDIA_CONNECT) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AID, शून्य);
			_rtl8723be_करोwnload_rsvd_page(hw);
		पूर्ण
		rtl8723be_set_fw_media_status_rpt_cmd(hw, mstatus);
		पूर्ण
		अवरोध;
	हाल HW_VAR_H2C_FW_P2P_PS_OFFLOAD:
		rtl8723be_set_p2p_ps_offload_cmd(hw, (*(u8 *)val));
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
			_rtl8723be_stop_tx_beacon(hw);

		_rtl8723be_set_bcn_ctrl_reg(hw, 0, BIT(3));

		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR,
				(u32) (mac->tsf & 0xffffffff));
		rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR + 4,
				(u32) ((mac->tsf >> 32) & 0xffffffff));

		_rtl8723be_set_bcn_ctrl_reg(hw, BIT(3), 0);

		अगर (btype_ibss)
			_rtl8723be_resume_tx_beacon(hw);
		पूर्ण
		अवरोध;
	हाल HW_VAR_KEEP_ALIVE:अणु
		u8 array[2];
		array[0] = 0xff;
		array[1] = *((u8 *)val);
		rtl8723be_fill_h2c_cmd(hw, H2C_8723B_KEEP_ALIVE_CTRL, 2, array);
		पूर्ण
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool _rtl8723be_llt_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 address, u32 data)
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

अटल bool _rtl8723be_llt_table_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अचिन्हित लघु i;
	u8 txpktbuf_bndy;
	u8 maxpage;
	bool status;

	maxpage = 255;
	txpktbuf_bndy = 245;

	rtl_ग_लिखो_dword(rtlpriv, REG_TRXFF_BNDY,
			(0x27FF0000 | txpktbuf_bndy));
	rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL + 1, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);

	rtl_ग_लिखो_byte(rtlpriv, 0x45D, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_PBP, 0x31);
	rtl_ग_लिखो_byte(rtlpriv, REG_RX_DRVINFO_SZ, 0x4);

	क्रम (i = 0; i < (txpktbuf_bndy - 1); i++) अणु
		status = _rtl8723be_llt_ग_लिखो(hw, i, i + 1);
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl8723be_llt_ग_लिखो(hw, (txpktbuf_bndy - 1), 0xFF);

	अगर (!status)
		वापस status;

	क्रम (i = txpktbuf_bndy; i < maxpage; i++) अणु
		status = _rtl8723be_llt_ग_लिखो(hw, i, (i + 1));
		अगर (!status)
			वापस status;
	पूर्ण

	status = _rtl8723be_llt_ग_लिखो(hw, maxpage, txpktbuf_bndy);
	अगर (!status)
		वापस status;

	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, 0x80e40808);
	rtl_ग_लिखो_byte(rtlpriv, REG_RQPN_NPQ, 0x00);

	वापस true;
पूर्ण

अटल व्योम _rtl8723be_gen_refresh_led_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;

	अगर (rtlpriv->rtlhal.up_first_समय)
		वापस;

	अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
		rtl8723be_sw_led_on(hw, pled0);
	अन्यथा अगर (ppsc->rfoff_reason == RF_CHANGE_BY_INIT)
		rtl8723be_sw_led_on(hw, pled0);
	अन्यथा
		rtl8723be_sw_led_off(hw, pled0);
पूर्ण

अटल bool _rtl8723be_init_mac(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	अचिन्हित अक्षर byteपंचांगp;
	अचिन्हित लघु wordपंचांगp;

	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x00);

	/*Auto Power Down to CHIP-off State*/
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO + 1) & (~BIT(7));
	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO + 1, byteपंचांगp);

	/* HW Power on sequence */
	अगर (!rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK,
				      PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,
				      RTL8723_NIC_ENABLE_FLOW)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"init MAC Fail as power on failure\n");
		वापस false;
	पूर्ण

	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_घातer_on_setting(rtlpriv);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MULTI_FUNC_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, REG_MULTI_FUNC_CTRL, byteपंचांगp | BIT(3));

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO) | BIT(4);
	rtl_ग_लिखो_byte(rtlpriv, REG_APS_FSMCO, byteपंचांगp);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_CR);
	byteपंचांगp = 0xff;
	rtl_ग_लिखो_byte(rtlpriv, REG_CR, byteपंचांगp);
	mdelay(2);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_HWSEQ_CTRL);
	byteपंचांगp |= 0x7f;
	rtl_ग_लिखो_byte(rtlpriv, REG_HWSEQ_CTRL, byteपंचांगp);
	mdelay(2);

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CFG + 3);
	अगर (byteपंचांगp & BIT(0)) अणु
		byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x7c);
		rtl_ग_लिखो_byte(rtlpriv, 0x7c, byteपंचांगp | BIT(6));
	पूर्ण

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CLKR);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_CLKR, byteपंचांगp | BIT(3));
	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_MUXCFG + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG + 1, byteपंचांगp & (~BIT(4)));

	rtl_ग_लिखो_word(rtlpriv, REG_CR, 0x2ff);

	अगर (!rtlhal->mac_func_enable) अणु
		अगर (!_rtl8723be_llt_table_init(hw))
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

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_PCIE_CTRL_REG + 3);
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 3, byteपंचांगp | 0x77);

	rtl_ग_लिखो_dword(rtlpriv, REG_INT_MIG, 0);

	rtl_ग_लिखो_dword(rtlpriv, REG_MCUTST_1, 0x0);

	rtl_ग_लिखो_byte(rtlpriv, REG_SECONDARY_CCA_CTRL, 0x3);

	/* <20130114, Kordan> The following setting is
	 * only क्रम DPDT and Fixed board type.
	 * TODO:  A better solution is configure it
	 * according EFUSE during the run-समय.
	 */
	rtl_set_bbreg(hw, 0x64, BIT(20), 0x0);/* 0x66[4]=0 */
	rtl_set_bbreg(hw, 0x64, BIT(24), 0x0);/* 0x66[8]=0 */
	rtl_set_bbreg(hw, 0x40, BIT(4), 0x0)/* 0x40[4]=0 */;
	rtl_set_bbreg(hw, 0x40, BIT(3), 0x1)/* 0x40[3]=1 */;
	rtl_set_bbreg(hw, 0x4C, BIT(24) | BIT(23), 0x2)/* 0x4C[24:23]=10 */;
	rtl_set_bbreg(hw, 0x944, BIT(1) | BIT(0), 0x3)/* 0x944[1:0]=11 */;
	rtl_set_bbreg(hw, 0x930, MASKBYTE0, 0x77)/* 0x930[7:0]=77 */;
	rtl_set_bbreg(hw, 0x38, BIT(11), 0x1)/* 0x38[11]=1 */;

	byteपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL, byteपंचांगp & (~BIT(2)));

	_rtl8723be_gen_refresh_led_state(hw);
	वापस true;
पूर्ण

अटल व्योम _rtl8723be_hw_configure(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 reg_rrsr;

	reg_rrsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
	/* Init value क्रम RRSR. */
	rtl_ग_लिखो_dword(rtlpriv, REG_RRSR, reg_rrsr);

	/* ARFB table 9 क्रम 11ac 5G 2SS */
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR0 + 4, 0xfffff000);

	/* ARFB table 10 क्रम 11ac 5G 1SS */
	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR1 + 4, 0x003ff000);

	/* CF-End setting. */
	rtl_ग_लिखो_word(rtlpriv, REG_FWHW_TXQ_CTRL, 0x1F00);

	/* 0x456 = 0x70, sugguested by Zhilin */
	rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MAX_TIME, 0x70);

	/* Set retry limit */
	rtl_ग_लिखो_word(rtlpriv, REG_RL, 0x0707);

	/* Set Data / Response स्वतः rate fallack retry count */
	rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC, 0x01000000);
	rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4, 0x07060504);
	rtl_ग_लिखो_dword(rtlpriv, REG_RARFRC, 0x01000000);
	rtl_ग_लिखो_dword(rtlpriv, REG_RARFRC + 4, 0x07060504);

	rtlpci->reg_bcn_ctrl_val = 0x1d;
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, rtlpci->reg_bcn_ctrl_val);

	/* TBTT prohibit hold समय. Suggested by designer TimChen. */
	rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff); /* 8 ms */

	rtl_ग_लिखो_word(rtlpriv, REG_NAV_PROT_LEN, 0x0040);

	/*For Rx TP. Suggested by SD1 Riअक्षरd. Added by tynli. 2010.04.12.*/
	rtl_ग_लिखो_dword(rtlpriv, REG_FAST_EDCA_CTRL, 0x03086666);

	rtl_ग_लिखो_byte(rtlpriv, REG_HT_SINGLE_AMPDU, 0x80);

	rtl_ग_लिखो_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x20);

	rtl_ग_लिखो_byte(rtlpriv, REG_MAX_AGGR_NUM, 0x1F);
पूर्ण

अटल u8 _rtl8723be_dbi_पढ़ो(काष्ठा rtl_priv *rtlpriv, u16 addr)
अणु
	u16 पढ़ो_addr = addr & 0xfffc;
	u8 ret = 0, पंचांगp = 0, count = 0;

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

अटल व्योम _rtl8723be_dbi_ग_लिखो(काष्ठा rtl_priv *rtlpriv, u16 addr, u8 data)
अणु
	u8 पंचांगp = 0, count = 0;
	u16 ग_लिखो_addr = 0, reमुख्यder = addr % 4;

	/* Write DBI 1Byte Data */
	ग_लिखो_addr = REG_DBI_WDATA + reमुख्यder;
	rtl_ग_लिखो_byte(rtlpriv, ग_लिखो_addr, data);

	/* Write DBI 2Byte Address & Write Enable */
	ग_लिखो_addr = (addr & 0xfffc) | (BIT(0) << (reमुख्यder + 12));
	rtl_ग_लिखो_word(rtlpriv, REG_DBI_ADDR, ग_लिखो_addr);

	/* Write DBI Write Flag */
	rtl_ग_लिखो_byte(rtlpriv, REG_DBI_FLAG, 0x1);

	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_FLAG);
	count = 0;
	जबतक (पंचांगp && count < 20) अणु
		udelay(10);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_FLAG);
		count++;
	पूर्ण
पूर्ण

अटल u16 _rtl8723be_mdio_पढ़ो(काष्ठा rtl_priv *rtlpriv, u8 addr)
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

अटल व्योम _rtl8723be_mdio_ग_लिखो(काष्ठा rtl_priv *rtlpriv, u8 addr, u16 data)
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

अटल व्योम _rtl8723be_enable_aspm_back_करोor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp8 = 0;
	u16 पंचांगp16 = 0;

	/* <Roger_Notes> Overग_लिखो following ePHY parameter क्रम
	 * some platक्रमm compatibility issue,
	 * especially when CLKReq is enabled, 2012.11.09.
	 */
	पंचांगp16 = _rtl8723be_mdio_पढ़ो(rtlpriv, 0x01);
	अगर (पंचांगp16 != 0x0663)
		_rtl8723be_mdio_ग_लिखो(rtlpriv, 0x01, 0x0663);

	पंचांगp16 = _rtl8723be_mdio_पढ़ो(rtlpriv, 0x04);
	अगर (पंचांगp16 != 0x7544)
		_rtl8723be_mdio_ग_लिखो(rtlpriv, 0x04, 0x7544);

	पंचांगp16 = _rtl8723be_mdio_पढ़ो(rtlpriv, 0x06);
	अगर (पंचांगp16 != 0xB880)
		_rtl8723be_mdio_ग_लिखो(rtlpriv, 0x06, 0xB880);

	पंचांगp16 = _rtl8723be_mdio_पढ़ो(rtlpriv, 0x07);
	अगर (पंचांगp16 != 0x4000)
		_rtl8723be_mdio_ग_लिखो(rtlpriv, 0x07, 0x4000);

	पंचांगp16 = _rtl8723be_mdio_पढ़ो(rtlpriv, 0x08);
	अगर (पंचांगp16 != 0x9003)
		_rtl8723be_mdio_ग_लिखो(rtlpriv, 0x08, 0x9003);

	पंचांगp16 = _rtl8723be_mdio_पढ़ो(rtlpriv, 0x09);
	अगर (पंचांगp16 != 0x0D03)
		_rtl8723be_mdio_ग_लिखो(rtlpriv, 0x09, 0x0D03);

	पंचांगp16 = _rtl8723be_mdio_पढ़ो(rtlpriv, 0x0A);
	अगर (पंचांगp16 != 0x4037)
		_rtl8723be_mdio_ग_लिखो(rtlpriv, 0x0A, 0x4037);

	पंचांगp16 = _rtl8723be_mdio_पढ़ो(rtlpriv, 0x0B);
	अगर (पंचांगp16 != 0x0070)
		_rtl8723be_mdio_ग_लिखो(rtlpriv, 0x0B, 0x0070);

	/* Configuration Space offset 0x70f BIT7 is used to control L0S */
	पंचांगp8 = _rtl8723be_dbi_पढ़ो(rtlpriv, 0x70f);
	_rtl8723be_dbi_ग_लिखो(rtlpriv, 0x70f, पंचांगp8 | BIT(7) |
			     ASPM_L1_LATENCY << 3);

	/* Configuration Space offset 0x719 Bit3 is क्रम L1
	 * BIT4 is क्रम घड़ी request
	 */
	पंचांगp8 = _rtl8723be_dbi_पढ़ो(rtlpriv, 0x719);
	_rtl8723be_dbi_ग_लिखो(rtlpriv, 0x719, पंचांगp8 | BIT(3) | BIT(4));
पूर्ण

व्योम rtl8723be_enable_hw_security_config(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl8723be_घातeroff_adapter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 u1b_पंचांगp;

	rtlhal->mac_func_enable = false;
	/* Combo (PCIe + USB) Card and PCIe-MF Card */
	/* 1. Run LPS WL RFOFF flow */
	rtl_hal_pwrseqcmdparsing(rtlpriv, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,
				 PWR_INTF_PCI_MSK, RTL8723_NIC_LPS_ENTER_FLOW);

	/* 2. 0x1F[7:0] = 0 */
	/* turn off RF */
	/* rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, 0x00); */
	अगर ((rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL) & BIT(7)) &&
	    rtlhal->fw_पढ़ोy) अणु
		rtl8723be_firmware_selfreset(hw);
	पूर्ण

	/* Reset MCU. Suggested by Filen. */
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, (u1b_पंचांगp & (~BIT(2))));

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

अटल bool _rtl8723be_check_pcie_dma_hang(काष्ठा rtl_priv *rtlpriv)
अणु
	u8 पंचांगp;

	/* ग_लिखो reg 0x350 Bit[26]=1. Enable debug port. */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_CTRL + 3);
	अगर (!(पंचांगp & BIT(2))) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_DBI_CTRL + 3, (पंचांगp | BIT(2)));
		mdelay(100); /* Suggested by DD Justin_tsai. */
	पूर्ण

	/* पढ़ो reg 0x350 Bit[25] अगर 1 : RX hang
	 * पढ़ो reg 0x350 Bit[24] अगर 1 : TX hang
	 */
	पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_DBI_CTRL + 3);
	अगर ((पंचांगp & BIT(0)) || (पंचांगp & BIT(1))) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"CheckPcieDMAHang8723BE(): true!!\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम _rtl8723be_reset_pcie_पूर्णांकerface_dma(काष्ठा rtl_priv *rtlpriv,
						bool mac_घातer_on)
अणु
	u8 पंचांगp;
	bool release_mac_rx_छोड़ो;
	u8 backup_pcie_dma_छोड़ो;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"ResetPcieInterfaceDMA8723BE()\n");

	/* Revise Note: Follow the करोcument "PCIe RX DMA Hang Reset Flow_v03"
	 * released by SD1 Alan.
	 * 2013.05.07, by tynli.
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

पूर्णांक rtl8723be_hw_init(काष्ठा ieee80211_hw *hw)
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

	/* reenable पूर्णांकerrupts to not पूर्णांकerfere with other devices */
	local_save_flags(flags);
	local_irq_enable();

	rtlhal->fw_पढ़ोy = false;
	rtlpriv->rtlhal.being_init_adapter = true;
	rtlpriv->पूर्णांकf_ops->disable_aspm(hw);

	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_CR);
	अगर (पंचांगp_u1b != 0 && पंचांगp_u1b != 0xea) अणु
		rtlhal->mac_func_enable = true;
	पूर्ण अन्यथा अणु
		rtlhal->mac_func_enable = false;
		rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON;
	पूर्ण

	अगर (_rtl8723be_check_pcie_dma_hang(rtlpriv)) अणु
		_rtl8723be_reset_pcie_पूर्णांकerface_dma(rtlpriv,
						    rtlhal->mac_func_enable);
		rtlhal->mac_func_enable = false;
	पूर्ण
	अगर (rtlhal->mac_func_enable) अणु
		_rtl8723be_घातeroff_adapter(hw);
		rtlhal->mac_func_enable = false;
	पूर्ण
	rtstatus = _rtl8723be_init_mac(hw);
	अगर (!rtstatus) अणु
		pr_err("Init MAC failed\n");
		err = 1;
		जाओ निकास;
	पूर्ण

	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_SYS_CFG);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_CFG, पंचांगp_u1b & 0x7F);

	err = rtl8723_करोwnload_fw(hw, true, FW_8723B_POLLING_TIMEOUT_COUNT);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Failed to download FW. Init HW without FW now..\n");
		err = 1;
		जाओ निकास;
	पूर्ण
	rtlhal->fw_पढ़ोy = true;

	rtlhal->last_hmeboxnum = 0;
	rtl8723be_phy_mac_config(hw);
	/* because last function modअगरy RCR, so we update
	 * rcr var here, or TP will unstable क्रम receive_config
	 * is wrong, RX RCR_ACRC32 will cause TP unstable & Rx
	 * RCR_APP_ICV will cause mac80211 unassoc क्रम cisco 1252
	 */
	rtlpci->receive_config = rtl_पढ़ो_dword(rtlpriv, REG_RCR);
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);
	rtl_ग_लिखो_dword(rtlpriv, REG_RCR, rtlpci->receive_config);

	rtl8723be_phy_bb_config(hw);
	rtl8723be_phy_rf_config(hw);

	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, (क्रमागत radio_path)0,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl_get_rfreg(hw, (क्रमागत radio_path)1,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[0] &= 0xFFF03FF;
	rtlphy->rfreg_chnlval[0] |= (BIT(10) | BIT(11));

	_rtl8723be_hw_configure(hw);
	rtlhal->mac_func_enable = true;
	rtl_cam_reset_all_entry(hw);
	rtl8723be_enable_hw_security_config(hw);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	_rtl8723be_enable_aspm_back_करोor(hw);
	rtlpriv->पूर्णांकf_ops->enable_aspm(hw);

	rtl8723be_bt_hw_init(hw);

	अगर (ppsc->rfpwr_state == ERFON) अणु
		rtl8723be_phy_set_rfpath_चयन(hw, 1);
		/* when use 1ant NIC, iqk will disturb BT music
		 * root cause is not clear now, is something
		 * related with 'mdelay' and Reg[0x948]
		 */
		अगर (rtlpriv->btcoexist.btc_info.ant_num == ANT_X2 ||
		    !rtlpriv->cfg->ops->get_btc_status()) अणु
			rtl8723be_phy_iq_calibrate(hw,
						   (rtlphy->iqk_initialized ?
						    true : false));
			rtlphy->iqk_initialized = true;
		पूर्ण
		rtl8723be_dm_check_txघातer_tracking(hw);
		rtl8723be_phy_lc_calibrate(hw);
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, REG_NAV_UPPER, ((30000 + 127) / 128));

	/* Release Rx DMA. */
	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_RXDMA_CONTROL);
	अगर (पंचांगp_u1b & BIT(2)) अणु
		/* Release Rx DMA अगर needed */
		पंचांगp_u1b &= (~BIT(2));
		rtl_ग_लिखो_byte(rtlpriv, REG_RXDMA_CONTROL, पंचांगp_u1b);
	पूर्ण
	/* Release Tx/Rx PCIE DMA. */
	rtl_ग_लिखो_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0);

	rtl8723be_dm_init(hw);
निकास:
	local_irq_restore(flags);
	rtlpriv->rtlhal.being_init_adapter = false;
	वापस err;
पूर्ण

अटल क्रमागत version_8723e _rtl8723be_पढ़ो_chip_version(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	क्रमागत version_8723e version = VERSION_UNKNOWN;
	u32 value32;

	value32 = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG1);
	अगर ((value32 & (CHIP_8723B)) != CHIP_8723B)
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "unknown chip version\n");
	अन्यथा
		version = (क्रमागत version_8723e)CHIP_8723B;

	rtlphy->rf_type = RF_1T1R;

	/* treat rtl8723be chip as  MP version in शेष */
	version = (क्रमागत version_8723e)(version | NORMAL_CHIP);

	value32 = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG);
	/* cut version */
	version |= (क्रमागत version_8723e)(value32 & CHIP_VER_RTL_MASK);
	/* Manufacture */
	अगर (((value32 & EXT_VENDOR_ID) >> 18) == 0x01)
		version = (क्रमागत version_8723e)(version | CHIP_VENDOR_SMIC);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Chip RF Type: %s\n", (rtlphy->rf_type == RF_2T2R) ?
		"RF_2T2R" : "RF_1T1R");

	वापस version;
पूर्ण

अटल पूर्णांक _rtl8723be_set_media_status(काष्ठा ieee80211_hw *hw,
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
		_rtl8723be_stop_tx_beacon(hw);
		_rtl8723be_enable_bcn_sub_func(hw);
	पूर्ण अन्यथा अगर (mode == MSR_ADHOC || mode == MSR_AP) अणु
		_rtl8723be_resume_tx_beacon(hw);
		_rtl8723be_disable_bcn_sub_func(hw);
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

व्योम rtl8723be_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid)
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
		_rtl8723be_set_bcn_ctrl_reg(hw, 0, BIT(4));
	पूर्ण अन्यथा अगर (!check_bssid) अणु
		reg_rcr &= (~(RCR_CBSSID_DATA | RCR_CBSSID_BCN));
		_rtl8723be_set_bcn_ctrl_reg(hw, BIT(4), 0);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR,
					      (u8 *)(&reg_rcr));
	पूर्ण

पूर्ण

पूर्णांक rtl8723be_set_network_type(काष्ठा ieee80211_hw *hw,
			       क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (_rtl8723be_set_media_status(hw, type))
		वापस -EOPNOTSUPP;

	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		अगर (type != NL80211_IFTYPE_AP)
			rtl8723be_set_check_bssid(hw, true);
	पूर्ण अन्यथा अणु
		rtl8723be_set_check_bssid(hw, false);
	पूर्ण

	वापस 0;
पूर्ण

/* करोn't set REG_EDCA_BE_PARAM here
 * because mac80211 will send pkt when scan
 */
व्योम rtl8723be_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci)
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
		WARN_ONCE(true, "rtl8723be: invalid aci: %d !\n", aci);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl8723be_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, rtlpci->irq_mask[0] & 0xFFFFFFFF);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, rtlpci->irq_mask[1] & 0xFFFFFFFF);
	rtlpci->irq_enabled = true;

	/*enable प्रणाली पूर्णांकerrupt*/
	rtl_ग_लिखो_dword(rtlpriv, REG_HSIMR, rtlpci->sys_irq_mask & 0xFFFFFFFF);
पूर्ण

व्योम rtl8723be_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, IMR_DISABLED);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, IMR_DISABLED);
	rtlpci->irq_enabled = false;
	/*synchronize_irq(rtlpci->pdev->irq);*/
पूर्ण

व्योम rtl8723be_card_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	क्रमागत nl80211_अगरtype opmode;

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;
	_rtl8723be_set_media_status(hw, opmode);
	अगर (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);
	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
	_rtl8723be_घातeroff_adapter(hw);

	/* after घातer off we should करो iqk again */
	अगर (!rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->phy.iqk_initialized = false;
पूर्ण

व्योम rtl8723be_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				    काष्ठा rtl_पूर्णांक *पूर्णांकvec)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	पूर्णांकvec->पूर्णांकa = rtl_पढ़ो_dword(rtlpriv, ISR) & rtlpci->irq_mask[0];
	rtl_ग_लिखो_dword(rtlpriv, ISR, पूर्णांकvec->पूर्णांकa);

	पूर्णांकvec->पूर्णांकb = rtl_पढ़ो_dword(rtlpriv, REG_HISRE) &
				      rtlpci->irq_mask[1];
	rtl_ग_लिखो_dword(rtlpriv, REG_HISRE, पूर्णांकvec->पूर्णांकb);
पूर्ण

व्योम rtl8723be_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval, atim_winकरोw;

	bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;
	atim_winकरोw = 2;	/*FIX MERGE */
	rtl8723be_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_ATIMWND, atim_winकरोw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl_ग_लिखो_word(rtlpriv, REG_BCNTCFG, 0x660f);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_CCK, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x18);
	rtl_ग_लिखो_byte(rtlpriv, 0x606, 0x30);
	rtl8723be_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl8723be_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;

	rtl_dbg(rtlpriv, COMP_BEACON, DBG_DMESG,
		"beacon_interval:%d\n", bcn_पूर्णांकerval);
	rtl8723be_disable_पूर्णांकerrupt(hw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	rtl8723be_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl8723be_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
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
	rtl8723be_disable_पूर्णांकerrupt(hw);
	rtl8723be_enable_पूर्णांकerrupt(hw);
पूर्ण

अटल u8 _rtl8723be_get_chnl_group(u8 chnl)
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

अटल व्योम _rtl8723be_पढ़ो_घातer_value_fromprom(काष्ठा ieee80211_hw *hw,
					काष्ठा txघातer_info_2g *pw2g,
					काष्ठा txघातer_info_5g *pw5g,
					bool स्वतःload_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 path, addr = EEPROM_TX_PWR_INX, group, cnt = 0;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"hal_ReadPowerValueFromPROM8723BE(): PROMContent[0x%x]=0x%x\n",
		(addr + 1), hwinfo[addr + 1]);
	अगर (0xFF == hwinfo[addr + 1])  /*YJ,add,120316*/
		स्वतःload_fail = true;

	अगर (स्वतःload_fail) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"auto load fail : Use Default value!\n");
		क्रम (path = 0; path < MAX_RF_PATH; path++) अणु
			/* 2.4G शेष value */
			क्रम (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) अणु
				pw2g->index_cck_base[path][group] = 0x2D;
				pw2g->index_bw40_base[path][group] = 0x2D;
			पूर्ण
			क्रम (cnt = 0; cnt < MAX_TX_COUNT; cnt++) अणु
				अगर (cnt == 0) अणु
					pw2g->bw20_dअगरf[path][0] = 0x02;
					pw2g->ofdm_dअगरf[path][0] = 0x04;
				पूर्ण अन्यथा अणु
					pw2g->bw20_dअगरf[path][cnt] = 0xFE;
					pw2g->bw40_dअगरf[path][cnt] = 0xFE;
					pw2g->cck_dअगरf[path][cnt] = 0xFE;
					pw2g->ofdm_dअगरf[path][cnt] = 0xFE;
				पूर्ण
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	क्रम (path = 0; path < MAX_RF_PATH; path++) अणु
		/*2.4G शेष value*/
		क्रम (group = 0; group < MAX_CHNL_GROUP_24G; group++) अणु
			pw2g->index_cck_base[path][group] = hwinfo[addr++];
			अगर (pw2g->index_cck_base[path][group] == 0xFF)
				pw2g->index_cck_base[path][group] = 0x2D;

		पूर्ण
		क्रम (group = 0; group < MAX_CHNL_GROUP_24G - 1; group++) अणु
			pw2g->index_bw40_base[path][group] = hwinfo[addr++];
			अगर (pw2g->index_bw40_base[path][group] == 0xFF)
				pw2g->index_bw40_base[path][group] = 0x2D;
		पूर्ण
		क्रम (cnt = 0; cnt < MAX_TX_COUNT; cnt++) अणु
			अगर (cnt == 0) अणु
				pw2g->bw40_dअगरf[path][cnt] = 0;
				अगर (hwinfo[addr] == 0xFF) अणु
					pw2g->bw20_dअगरf[path][cnt] = 0x02;
				पूर्ण अन्यथा अणु
					pw2g->bw20_dअगरf[path][cnt] =
						(hwinfo[addr] & 0xf0) >> 4;
					/*bit sign number to 8 bit sign number*/
					अगर (pw2g->bw20_dअगरf[path][cnt] & BIT(3))
						pw2g->bw20_dअगरf[path][cnt] |=
									  0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF) अणु
					pw2g->ofdm_dअगरf[path][cnt] = 0x04;
				पूर्ण अन्यथा अणु
					pw2g->ofdm_dअगरf[path][cnt] =
							(hwinfo[addr] & 0x0f);
					/*bit sign number to 8 bit sign number*/
					अगर (pw2g->ofdm_dअगरf[path][cnt] & BIT(3))
						pw2g->ofdm_dअगरf[path][cnt] |=
									  0xF0;
				पूर्ण
				pw2g->cck_dअगरf[path][cnt] = 0;
				addr++;
			पूर्ण अन्यथा अणु
				अगर (hwinfo[addr] == 0xFF) अणु
					pw2g->bw40_dअगरf[path][cnt] = 0xFE;
				पूर्ण अन्यथा अणु
					pw2g->bw40_dअगरf[path][cnt] =
						(hwinfo[addr] & 0xf0) >> 4;
					अगर (pw2g->bw40_dअगरf[path][cnt] & BIT(3))
						pw2g->bw40_dअगरf[path][cnt] |=
									  0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF) अणु
					pw2g->bw20_dअगरf[path][cnt] = 0xFE;
				पूर्ण अन्यथा अणु
					pw2g->bw20_dअगरf[path][cnt] =
							(hwinfo[addr] & 0x0f);
					अगर (pw2g->bw20_dअगरf[path][cnt] & BIT(3))
						pw2g->bw20_dअगरf[path][cnt] |=
									  0xF0;
				पूर्ण
				addr++;

				अगर (hwinfo[addr] == 0xFF) अणु
					pw2g->ofdm_dअगरf[path][cnt] = 0xFE;
				पूर्ण अन्यथा अणु
					pw2g->ofdm_dअगरf[path][cnt] =
						(hwinfo[addr] & 0xf0) >> 4;
					अगर (pw2g->ofdm_dअगरf[path][cnt] & BIT(3))
						pw2g->ofdm_dअगरf[path][cnt] |=
									  0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF)
					pw2g->cck_dअगरf[path][cnt] = 0xFE;
				अन्यथा अणु
					pw2g->cck_dअगरf[path][cnt] =
							(hwinfo[addr] & 0x0f);
					अगर (pw2g->cck_dअगरf[path][cnt] & BIT(3))
						pw2g->cck_dअगरf[path][cnt] |=
									 0xF0;
				पूर्ण
				addr++;
			पूर्ण
		पूर्ण

		/*5G शेष value*/
		क्रम (group = 0; group < MAX_CHNL_GROUP_5G; group++) अणु
			pw5g->index_bw40_base[path][group] = hwinfo[addr++];
			अगर (pw5g->index_bw40_base[path][group] == 0xFF)
				pw5g->index_bw40_base[path][group] = 0xFE;
		पूर्ण

		क्रम (cnt = 0; cnt < MAX_TX_COUNT; cnt++) अणु
			अगर (cnt == 0) अणु
				pw5g->bw40_dअगरf[path][cnt] = 0;

				अगर (hwinfo[addr] == 0xFF) अणु
					pw5g->bw20_dअगरf[path][cnt] = 0;
				पूर्ण अन्यथा अणु
					pw5g->bw20_dअगरf[path][0] =
						(hwinfo[addr] & 0xf0) >> 4;
					अगर (pw5g->bw20_dअगरf[path][cnt] & BIT(3))
						pw5g->bw20_dअगरf[path][cnt] |=
									  0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF)
					pw5g->ofdm_dअगरf[path][cnt] = 0x04;
				अन्यथा अणु
					pw5g->ofdm_dअगरf[path][0] =
							(hwinfo[addr] & 0x0f);
					अगर (pw5g->ofdm_dअगरf[path][cnt] & BIT(3))
						pw5g->ofdm_dअगरf[path][cnt] |=
									  0xF0;
				पूर्ण
				addr++;
			पूर्ण अन्यथा अणु
				अगर (hwinfo[addr] == 0xFF) अणु
					pw5g->bw40_dअगरf[path][cnt] = 0xFE;
				पूर्ण अन्यथा अणु
					pw5g->bw40_dअगरf[path][cnt] =
						(hwinfo[addr] & 0xf0) >> 4;
					अगर (pw5g->bw40_dअगरf[path][cnt] & BIT(3))
						pw5g->bw40_dअगरf[path][cnt] |= 0xF0;
				पूर्ण

				अगर (hwinfo[addr] == 0xFF) अणु
					pw5g->bw20_dअगरf[path][cnt] = 0xFE;
				पूर्ण अन्यथा अणु
					pw5g->bw20_dअगरf[path][cnt] =
							(hwinfo[addr] & 0x0f);
					अगर (pw5g->bw20_dअगरf[path][cnt] & BIT(3))
						pw5g->bw20_dअगरf[path][cnt] |= 0xF0;
				पूर्ण
				addr++;
			पूर्ण
		पूर्ण

		अगर (hwinfo[addr] == 0xFF) अणु
			pw5g->ofdm_dअगरf[path][1] = 0xFE;
			pw5g->ofdm_dअगरf[path][2] = 0xFE;
		पूर्ण अन्यथा अणु
			pw5g->ofdm_dअगरf[path][1] = (hwinfo[addr] & 0xf0) >> 4;
			pw5g->ofdm_dअगरf[path][2] = (hwinfo[addr] & 0x0f);
		पूर्ण
		addr++;

		अगर (hwinfo[addr] == 0xFF)
			pw5g->ofdm_dअगरf[path][3] = 0xFE;
		अन्यथा
			pw5g->ofdm_dअगरf[path][3] = (hwinfo[addr] & 0x0f);
		addr++;

		क्रम (cnt = 1; cnt < MAX_TX_COUNT; cnt++) अणु
			अगर (pw5g->ofdm_dअगरf[path][cnt] == 0xFF)
				pw5g->ofdm_dअगरf[path][cnt] = 0xFE;
			अन्यथा अगर (pw5g->ofdm_dअगरf[path][cnt] & BIT(3))
				pw5g->ofdm_dअगरf[path][cnt] |= 0xF0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl8723be_पढ़ो_txघातer_info_from_hwpg(काष्ठा ieee80211_hw *hw,
						   bool स्वतःload_fail,
						   u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा txघातer_info_2g pw2g;
	काष्ठा txघातer_info_5g pw5g;
	u8 rf_path, index;
	u8 i;

	_rtl8723be_पढ़ो_घातer_value_fromprom(hw, &pw2g, &pw5g, स्वतःload_fail,
					     hwinfo);

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 14; i++) अणु
			index = _rtl8723be_get_chnl_group(i+1);

			rtlefuse->txpwrlevel_cck[rf_path][i] =
					pw2g.index_cck_base[rf_path][index];
			rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
					pw2g.index_bw40_base[rf_path][index];
		पूर्ण
		क्रम (i = 0; i < MAX_TX_COUNT; i++) अणु
			rtlefuse->txpwr_ht20dअगरf[rf_path][i] =
						pw2g.bw20_dअगरf[rf_path][i];
			rtlefuse->txpwr_ht40dअगरf[rf_path][i] =
						pw2g.bw40_dअगरf[rf_path][i];
			rtlefuse->txpwr_legacyhtdअगरf[rf_path][i] =
						pw2g.ofdm_dअगरf[rf_path][i];
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

अटल u8 _rtl8723be_पढ़ो_package_type(काष्ठा ieee80211_hw *hw)
अणु
	u8 package_type;
	u8 value;

	efuse_घातer_चयन(hw, false, true);
	अगर (!efuse_one_byte_पढ़ो(hw, 0x1FB, &value))
		value = 0;
	efuse_घातer_चयन(hw, false, false);

	चयन (value & 0x7) अणु
	हाल 0x4:
		package_type = PACKAGE_TFBGA79;
		अवरोध;
	हाल 0x5:
		package_type = PACKAGE_TFBGA90;
		अवरोध;
	हाल 0x6:
		package_type = PACKAGE_QFN68;
		अवरोध;
	हाल 0x7:
		package_type = PACKAGE_TFBGA80;
		अवरोध;
	शेष:
		package_type = PACKAGE_DEFAULT;
		अवरोध;
	पूर्ण

	वापस package_type;
पूर्ण

अटल व्योम _rtl8723be_पढ़ो_adapter_info(काष्ठा ieee80211_hw *hw,
					 bool pseuकरो_test)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक params[] = अणुRTL8723BE_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13पूर्ण;
	u8 *hwinfo;
	पूर्णांक i;
	bool is_toshiba_smid1 = false;
	bool is_toshiba_smid2 = false;
	bool is_samsung_smid = false;
	bool is_lenovo_smid = false;
	u16 toshiba_smid1[] = अणु
		0x6151, 0x6152, 0x6154, 0x6155, 0x6177, 0x6178, 0x6179, 0x6180,
		0x7151, 0x7152, 0x7154, 0x7155, 0x7177, 0x7178, 0x7179, 0x7180,
		0x8151, 0x8152, 0x8154, 0x8155, 0x8181, 0x8182, 0x8184, 0x8185,
		0x9151, 0x9152, 0x9154, 0x9155, 0x9181, 0x9182, 0x9184, 0x9185
	पूर्ण;
	u16 toshiba_smid2[] = अणु
		0x6181, 0x6184, 0x6185, 0x7181, 0x7182, 0x7184, 0x7185, 0x8181,
		0x8182, 0x8184, 0x8185, 0x9181, 0x9182, 0x9184, 0x9185
	पूर्ण;
	u16 samsung_smid[] = अणु
		0x6191, 0x6192, 0x6193, 0x7191, 0x7192, 0x7193, 0x8191, 0x8192,
		0x8193, 0x9191, 0x9192, 0x9193
	पूर्ण;
	u16 lenovo_smid[] = अणु
		0x8195, 0x9195, 0x7194, 0x8200, 0x8201, 0x8202, 0x9199, 0x9200
	पूर्ण;

	अगर (pseuकरो_test) अणु
		/* needs to be added */
		वापस;
	पूर्ण

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	अगर (!hwinfo)
		वापस;

	अगर (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		जाओ निकास;

	/*parse xtal*/
	rtlefuse->crystalcap = hwinfo[EEPROM_XTAL_8723BE];
	अगर (rtlefuse->crystalcap == 0xFF)
		rtlefuse->crystalcap = 0x20;

	_rtl8723be_पढ़ो_txघातer_info_from_hwpg(hw, rtlefuse->स्वतःload_failflag,
					       hwinfo);

	rtl8723be_पढ़ो_bt_coexist_info_from_hwpg(hw,
						 rtlefuse->स्वतःload_failflag,
						 hwinfo);

	अगर (rtlpriv->btcoexist.btc_info.btcoexist == 1)
		rtlefuse->board_type |= BIT(2); /* ODM_BOARD_BT */

	rtlhal->board_type = rtlefuse->board_type;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"board_type = 0x%x\n", rtlefuse->board_type);

	rtlhal->package_type = _rtl8723be_पढ़ो_package_type(hw);

	/* set channel plan from efuse */
	rtlefuse->channel_plan = rtlefuse->eeprom_channelplan;

	अगर (rtlhal->oem_id == RT_CID_DEFAULT) अणु
		/* Does this one have a Toshiba SMID from group 1? */
		क्रम (i = 0; i < ARRAY_SIZE(toshiba_smid1); i++) अणु
			अगर (rtlefuse->eeprom_smid == toshiba_smid1[i]) अणु
				is_toshiba_smid1 = true;
				अवरोध;
			पूर्ण
		पूर्ण
		/* Does this one have a Toshiba SMID from group 2? */
		क्रम (i = 0; i < ARRAY_SIZE(toshiba_smid2); i++) अणु
			अगर (rtlefuse->eeprom_smid == toshiba_smid2[i]) अणु
				is_toshiba_smid2 = true;
				अवरोध;
			पूर्ण
		पूर्ण
		/* Does this one have a Samsung SMID? */
		क्रम (i = 0; i < ARRAY_SIZE(samsung_smid); i++) अणु
			अगर (rtlefuse->eeprom_smid == samsung_smid[i]) अणु
				is_samsung_smid = true;
				अवरोध;
			पूर्ण
		पूर्ण
		/* Does this one have a Lenovo SMID? */
		क्रम (i = 0; i < ARRAY_SIZE(lenovo_smid); i++) अणु
			अगर (rtlefuse->eeprom_smid == lenovo_smid[i]) अणु
				is_lenovo_smid = true;
				अवरोध;
			पूर्ण
		पूर्ण
		चयन (rtlefuse->eeprom_oemid) अणु
		हाल EEPROM_CID_DEFAULT:
			अगर (rtlefuse->eeprom_did == 0x8176) अणु
				अगर (rtlefuse->eeprom_svid == 0x10EC &&
				    is_toshiba_smid1) अणु
					rtlhal->oem_id = RT_CID_TOSHIBA;
				पूर्ण अन्यथा अगर (rtlefuse->eeprom_svid == 0x1025) अणु
					rtlhal->oem_id = RT_CID_819X_ACER;
				पूर्ण अन्यथा अगर (rtlefuse->eeprom_svid == 0x10EC &&
					   is_samsung_smid) अणु
					rtlhal->oem_id = RT_CID_819X_SAMSUNG;
				पूर्ण अन्यथा अगर (rtlefuse->eeprom_svid == 0x10EC &&
					   is_lenovo_smid) अणु
					rtlhal->oem_id = RT_CID_819X_LENOVO;
				पूर्ण अन्यथा अगर ((rtlefuse->eeprom_svid == 0x10EC &&
					    rtlefuse->eeprom_smid == 0x8197) ||
					   (rtlefuse->eeprom_svid == 0x10EC &&
					    rtlefuse->eeprom_smid == 0x9196)) अणु
					rtlhal->oem_id = RT_CID_819X_CLEVO;
				पूर्ण अन्यथा अगर ((rtlefuse->eeprom_svid == 0x1028 &&
					    rtlefuse->eeprom_smid == 0x8194) ||
					   (rtlefuse->eeprom_svid == 0x1028 &&
					    rtlefuse->eeprom_smid == 0x8198) ||
					   (rtlefuse->eeprom_svid == 0x1028 &&
					    rtlefuse->eeprom_smid == 0x9197) ||
					   (rtlefuse->eeprom_svid == 0x1028 &&
					    rtlefuse->eeprom_smid == 0x9198)) अणु
					rtlhal->oem_id = RT_CID_819X_DELL;
				पूर्ण अन्यथा अगर ((rtlefuse->eeprom_svid == 0x103C &&
					    rtlefuse->eeprom_smid == 0x1629)) अणु
					rtlhal->oem_id = RT_CID_819X_HP;
				पूर्ण अन्यथा अगर ((rtlefuse->eeprom_svid == 0x1A32 &&
					   rtlefuse->eeprom_smid == 0x2315)) अणु
					rtlhal->oem_id = RT_CID_819X_QMI;
				पूर्ण अन्यथा अगर ((rtlefuse->eeprom_svid == 0x10EC &&
					   rtlefuse->eeprom_smid == 0x8203)) अणु
					rtlhal->oem_id = RT_CID_819X_PRONETS;
				पूर्ण अन्यथा अगर ((rtlefuse->eeprom_svid == 0x1043 &&
					   rtlefuse->eeprom_smid == 0x84B5)) अणु
					rtlhal->oem_id = RT_CID_819X_EDIMAX_ASUS;
				पूर्ण अन्यथा अणु
					rtlhal->oem_id = RT_CID_DEFAULT;
				पूर्ण
			पूर्ण अन्यथा अगर (rtlefuse->eeprom_did == 0x8178) अणु
				अगर (rtlefuse->eeprom_svid == 0x10EC &&
				    is_toshiba_smid2)
					rtlhal->oem_id = RT_CID_TOSHIBA;
				अन्यथा अगर (rtlefuse->eeprom_svid == 0x1025)
					rtlhal->oem_id = RT_CID_819X_ACER;
				अन्यथा अगर ((rtlefuse->eeprom_svid == 0x10EC &&
					  rtlefuse->eeprom_smid == 0x8186))
					rtlhal->oem_id = RT_CID_819X_PRONETS;
				अन्यथा अगर ((rtlefuse->eeprom_svid == 0x1043 &&
					  rtlefuse->eeprom_smid == 0x84B6))
					rtlhal->oem_id =
							RT_CID_819X_EDIMAX_ASUS;
				अन्यथा
					rtlhal->oem_id = RT_CID_DEFAULT;
			पूर्ण अन्यथा अणु
					rtlhal->oem_id = RT_CID_DEFAULT;
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
	पूर्ण
निकास:
	kमुक्त(hwinfo);
पूर्ण

अटल व्योम _rtl8723be_hal_customized_behavior(काष्ठा ieee80211_hw *hw)
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

व्योम rtl8723be_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_u1b;

	rtlhal->version = _rtl8723be_पढ़ो_chip_version(hw);
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
		_rtl8723be_पढ़ो_adapter_info(hw, false);
	पूर्ण अन्यथा अणु
		pr_err("Autoload ERR!!\n");
	पूर्ण
	_rtl8723be_hal_customized_behavior(hw);
पूर्ण

अटल u8 _rtl8723be_mrate_idx_to_arfr_id(काष्ठा ieee80211_hw *hw,
					  u8 rate_index)
अणु
	u8 ret = 0;
	चयन (rate_index) अणु
	हाल RATR_INX_WIRELESS_NGB:
		ret = 1;
		अवरोध;
	हाल RATR_INX_WIRELESS_N:
	हाल RATR_INX_WIRELESS_NG:
		ret = 5;
		अवरोध;
	हाल RATR_INX_WIRELESS_NB:
		ret = 3;
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

अटल व्योम rtl8723be_update_hal_rate_mask(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_sta *sta,
					   u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u32 ratr_biपंचांगap;
	u8 ratr_index;
	u8 curtxbw_40mhz = (sta->ht_cap.cap &
			      IEEE80211_HT_CAP_SUP_WIDTH_20_40) ? 1 : 0;
	u8 curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
				1 : 0;
	u8 curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	क्रमागत wireless_mode wirelessmode = 0;
	bool लघुgi = false;
	u8 rate_mask[7];
	u8 macid = 0;

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
	हाल WIRELESS_MODE_N_5G:
		ratr_index = RATR_INX_WIRELESS_NGB;
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
	rate_mask[0] = macid;
	rate_mask[1] = _rtl8723be_mrate_idx_to_arfr_id(hw, ratr_index) |
						      (लघुgi ? 0x80 : 0x00);
	rate_mask[2] = curtxbw_40mhz | ((!update_bw) << 3);

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
	rtl8723be_fill_h2c_cmd(hw, H2C_8723B_RA_MASK, 7, rate_mask);
	_rtl8723be_set_bcn_ctrl_reg(hw, BIT(3), 0);
पूर्ण

व्योम rtl8723be_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_sta *sta,
				   u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अगर (rtlpriv->dm.useramask)
		rtl8723be_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
पूर्ण

व्योम rtl8723be_update_channel_access_setting(काष्ठा ieee80211_hw *hw)
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

bool rtl8723be_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid)
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
		       rtl_पढ़ो_byte(rtlpriv, REG_GPIO_IO_SEL_2) & ~(BIT(1)));

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

व्योम rtl8723be_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
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

व्योम rtl8723be_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
					      bool स्वतः_load_fail, u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mod_params *mod_params = rtlpriv->cfg->mod_params;
	u8 value;
	u32 पंचांगpu_32;

	अगर (!स्वतः_load_fail) अणु
		पंचांगpu_32 = rtl_पढ़ो_dword(rtlpriv, REG_MULTI_FUNC_CTRL);
		अगर (पंचांगpu_32 & BIT(18))
			rtlpriv->btcoexist.btc_info.btcoexist = 1;
		अन्यथा
			rtlpriv->btcoexist.btc_info.btcoexist = 0;
		value = hwinfo[EEPROM_RF_BT_SETTING_8723B];
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8723B;
		rtlpriv->btcoexist.btc_info.ant_num = (value & 0x1);
		rtlpriv->btcoexist.btc_info.single_ant_path =
			 (value & 0x40 ? ANT_AUX : ANT_MAIN);	/*0xc3[6]*/
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.btc_info.btcoexist = 0;
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8723B;
		rtlpriv->btcoexist.btc_info.ant_num = ANT_X2;
		rtlpriv->btcoexist.btc_info.single_ant_path = ANT_MAIN;
	पूर्ण

	/* override ant_num / ant_path */
	अगर (mod_params->ant_sel) अणु
		rtlpriv->btcoexist.btc_info.ant_num =
			(mod_params->ant_sel == 1 ? ANT_X1 : ANT_X2);

		rtlpriv->btcoexist.btc_info.single_ant_path =
			(mod_params->ant_sel == 1 ? ANT_AUX : ANT_MAIN);
	पूर्ण
पूर्ण

व्योम rtl8723be_bt_reg_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* 0:Low, 1:High, 2:From Efuse. */
	rtlpriv->btcoexist.reg_bt_iso = 2;
	/* 0:Idle, 1:None-SCO, 2:SCO, 3:From Counter. */
	rtlpriv->btcoexist.reg_bt_sco = 3;
	/* 0:Disable BT control A-MPDU, 1:Enable BT control A-MPDU. */
	rtlpriv->btcoexist.reg_bt_sco = 0;
पूर्ण

व्योम rtl8723be_bt_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_init_hw_config(rtlpriv);

पूर्ण

व्योम rtl8723be_suspend(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

व्योम rtl8723be_resume(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण
