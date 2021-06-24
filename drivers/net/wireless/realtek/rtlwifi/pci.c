<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "core.h"
#समावेश "pci.h"
#समावेश "base.h"
#समावेश "ps.h"
#समावेश "efuse.h"
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>

MODULE_AUTHOR("lizhaoming	<chaoming_li@realsil.com.cn>");
MODULE_AUTHOR("Realtek WlanFAE	<wlanfae@realtek.com>");
MODULE_AUTHOR("Larry Finger	<Larry.FInger@lwfinger.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PCI basic driver for rtlwifi");

अटल स्थिर u16 pcibridge_venकरोrs[PCI_BRIDGE_VENDOR_MAX] = अणु
	INTEL_VENDOR_ID,
	ATI_VENDOR_ID,
	AMD_VENDOR_ID,
	SIS_VENDOR_ID
पूर्ण;

अटल स्थिर u8 ac_to_hwq[] = अणु
	VO_QUEUE,
	VI_QUEUE,
	BE_QUEUE,
	BK_QUEUE
पूर्ण;

अटल u8 _rtl_mac_to_hwqueue(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	__le16 fc = rtl_get_fc(skb);
	u8 queue_index = skb_get_queue_mapping(skb);
	काष्ठा ieee80211_hdr *hdr;

	अगर (unlikely(ieee80211_is_beacon(fc)))
		वापस BEACON_QUEUE;
	अगर (ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc))
		वापस MGNT_QUEUE;
	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192SE)
		अगर (ieee80211_is_nullfunc(fc))
			वापस HIGH_QUEUE;
	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8822BE) अणु
		hdr = rtl_get_hdr(skb);

		अगर (is_multicast_ether_addr(hdr->addr1) ||
		    is_broadcast_ether_addr(hdr->addr1))
			वापस HIGH_QUEUE;
	पूर्ण

	वापस ac_to_hwq[queue_index];
पूर्ण

/* Update PCI dependent शेष settings*/
अटल व्योम _rtl_pci_update_शेष_setting(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 pcibridge_venकरोr = pcipriv->ndis_adapter.pcibridge_venकरोr;
	u8 init_aspm;

	ppsc->reg_rfps_level = 0;
	ppsc->support_aspm = false;

	/*Update PCI ASPM setting */
	ppsc->स्थिर_amdpci_aspm = rtlpci->स्थिर_amdpci_aspm;
	चयन (rtlpci->स्थिर_pci_aspm) अणु
	हाल 0:
		/*No ASPM */
		अवरोध;

	हाल 1:
		/*ASPM dynamically enabled/disable. */
		ppsc->reg_rfps_level |= RT_RF_LPS_LEVEL_ASPM;
		अवरोध;

	हाल 2:
		/*ASPM with Clock Req dynamically enabled/disable. */
		ppsc->reg_rfps_level |= (RT_RF_LPS_LEVEL_ASPM |
					 RT_RF_OFF_LEVL_CLK_REQ);
		अवरोध;

	हाल 3:
		/* Always enable ASPM and Clock Req
		 * from initialization to halt.
		 */
		ppsc->reg_rfps_level &= ~(RT_RF_LPS_LEVEL_ASPM);
		ppsc->reg_rfps_level |= (RT_RF_PS_LEVEL_ALWAYS_ASPM |
					 RT_RF_OFF_LEVL_CLK_REQ);
		अवरोध;

	हाल 4:
		/* Always enable ASPM without Clock Req
		 * from initialization to halt.
		 */
		ppsc->reg_rfps_level &= ~(RT_RF_LPS_LEVEL_ASPM |
					  RT_RF_OFF_LEVL_CLK_REQ);
		ppsc->reg_rfps_level |= RT_RF_PS_LEVEL_ALWAYS_ASPM;
		अवरोध;
	पूर्ण

	ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_HALT_NIC;

	/*Update Radio OFF setting */
	चयन (rtlpci->स्थिर_hwsw_rfoff_d3) अणु
	हाल 1:
		अगर (ppsc->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM)
			ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_ASPM;
		अवरोध;

	हाल 2:
		अगर (ppsc->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM)
			ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_ASPM;
		ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_HALT_NIC;
		अवरोध;

	हाल 3:
		ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_PCI_D3;
		अवरोध;
	पूर्ण

	/*Set HW definition to determine अगर it supports ASPM. */
	चयन (rtlpci->स्थिर_support_pciaspm) अणु
	हाल 0:
		/*Not support ASPM. */
		ppsc->support_aspm = false;
		अवरोध;
	हाल 1:
		/*Support ASPM. */
		ppsc->support_aspm = true;
		ppsc->support_backकरोor = true;
		अवरोध;
	हाल 2:
		/*ASPM value set by chipset. */
		अगर (pcibridge_venकरोr == PCI_BRIDGE_VENDOR_INTEL)
			ppsc->support_aspm = true;
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n",
		       rtlpci->स्थिर_support_pciaspm);
		अवरोध;
	पूर्ण

	/* toshiba aspm issue, toshiba will set aspm selfly
	 * so we should not set aspm in driver
	 */
	pci_पढ़ो_config_byte(rtlpci->pdev, 0x80, &init_aspm);
	अगर (rtlpriv->rtlhal.hw_type == HARDWARE_TYPE_RTL8192SE &&
	    init_aspm == 0x43)
		ppsc->support_aspm = false;
पूर्ण

अटल bool _rtl_pci_platक्रमm_चयन_device_pci_aspm(
			काष्ठा ieee80211_hw *hw,
			u8 value)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (rtlhal->hw_type != HARDWARE_TYPE_RTL8192SE)
		value |= 0x40;

	pci_ग_लिखो_config_byte(rtlpci->pdev, 0x80, value);

	वापस false;
पूर्ण

/*When we set 0x01 to enable clk request. Set 0x0 to disable clk req.*/
अटल व्योम _rtl_pci_चयन_clk_req(काष्ठा ieee80211_hw *hw, u8 value)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	pci_ग_लिखो_config_byte(rtlpci->pdev, 0x81, value);

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192SE)
		udelay(100);
पूर्ण

/*Disable RTL8192SE ASPM & Disable Pci Bridge ASPM*/
अटल व्योम rtl_pci_disable_aspm(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 pcibridge_venकरोr = pcipriv->ndis_adapter.pcibridge_venकरोr;
	u8 num4bytes = pcipriv->ndis_adapter.num4bytes;
	/*Retrieve original configuration settings. */
	u8 linkctrl_reg = pcipriv->ndis_adapter.linkctrl_reg;
	u16 pcibridge_linkctrlreg = pcipriv->ndis_adapter.
				pcibridge_linkctrlreg;
	u16 aspmlevel = 0;
	u8 पंचांगp_u1b = 0;

	अगर (!ppsc->support_aspm)
		वापस;

	अगर (pcibridge_venकरोr == PCI_BRIDGE_VENDOR_UNKNOWN) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
			"PCI(Bridge) UNKNOWN\n");

		वापस;
	पूर्ण

	अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_CLK_REQ) अणु
		RT_CLEAR_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_CLK_REQ);
		_rtl_pci_चयन_clk_req(hw, 0x0);
	पूर्ण

	/*क्रम promising device will in L0 state after an I/O. */
	pci_पढ़ो_config_byte(rtlpci->pdev, 0x80, &पंचांगp_u1b);

	/*Set corresponding value. */
	aspmlevel |= BIT(0) | BIT(1);
	linkctrl_reg &= ~aspmlevel;
	pcibridge_linkctrlreg &= ~(BIT(0) | BIT(1));

	_rtl_pci_platक्रमm_चयन_device_pci_aspm(hw, linkctrl_reg);
	udelay(50);

	/*4 Disable Pci Bridge ASPM */
	pci_ग_लिखो_config_byte(rtlpci->pdev, (num4bytes << 2),
			      pcibridge_linkctrlreg);

	udelay(50);
पूर्ण

/*Enable RTL8192SE ASPM & Enable Pci Bridge ASPM क्रम
 *घातer saving We should follow the sequence to enable
 *RTL8192SE first then enable Pci Bridge ASPM
 *or the प्रणाली will show bluescreen.
 */
अटल व्योम rtl_pci_enable_aspm(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 pcibridge_venकरोr = pcipriv->ndis_adapter.pcibridge_venकरोr;
	u8 num4bytes = pcipriv->ndis_adapter.num4bytes;
	u16 aspmlevel;
	u8 u_pcibridge_aspmsetting;
	u8 u_device_aspmsetting;

	अगर (!ppsc->support_aspm)
		वापस;

	अगर (pcibridge_venकरोr == PCI_BRIDGE_VENDOR_UNKNOWN) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
			"PCI(Bridge) UNKNOWN\n");
		वापस;
	पूर्ण

	/*4 Enable Pci Bridge ASPM */

	u_pcibridge_aspmsetting =
	    pcipriv->ndis_adapter.pcibridge_linkctrlreg |
	    rtlpci->स्थिर_hostpci_aspm_setting;

	अगर (pcibridge_venकरोr == PCI_BRIDGE_VENDOR_INTEL)
		u_pcibridge_aspmsetting &= ~BIT(0);

	pci_ग_लिखो_config_byte(rtlpci->pdev, (num4bytes << 2),
			      u_pcibridge_aspmsetting);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"PlatformEnableASPM(): Write reg[%x] = %x\n",
		(pcipriv->ndis_adapter.pcibridge_pciehdr_offset + 0x10),
		u_pcibridge_aspmsetting);

	udelay(50);

	/*Get ASPM level (with/without Clock Req) */
	aspmlevel = rtlpci->स्थिर_devicepci_aspm_setting;
	u_device_aspmsetting = pcipriv->ndis_adapter.linkctrl_reg;

	/*_rtl_pci_platक्रमm_चयन_device_pci_aspm(dev,*/
	/*(priv->ndis_adapter.linkctrl_reg | ASPMLevel)); */

	u_device_aspmsetting |= aspmlevel;

	_rtl_pci_platक्रमm_चयन_device_pci_aspm(hw, u_device_aspmsetting);

	अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_CLK_REQ) अणु
		_rtl_pci_चयन_clk_req(hw, (ppsc->reg_rfps_level &
					     RT_RF_OFF_LEVL_CLK_REQ) ? 1 : 0);
		RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_CLK_REQ);
	पूर्ण
	udelay(100);
पूर्ण

अटल bool rtl_pci_get_amd_l1_patch(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	bool status = false;
	u8 offset_e0;
	अचिन्हित पूर्णांक offset_e4;

	pci_ग_लिखो_config_byte(rtlpci->pdev, 0xe0, 0xa0);

	pci_पढ़ो_config_byte(rtlpci->pdev, 0xe0, &offset_e0);

	अगर (offset_e0 == 0xA0) अणु
		pci_पढ़ो_config_dword(rtlpci->pdev, 0xe4, &offset_e4);
		अगर (offset_e4 & BIT(23))
			status = true;
	पूर्ण

	वापस status;
पूर्ण

अटल bool rtl_pci_check_buddy_priv(काष्ठा ieee80211_hw *hw,
				     काष्ठा rtl_priv **buddy_priv)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	bool find_buddy_priv = false;
	काष्ठा rtl_priv *tpriv;
	काष्ठा rtl_pci_priv *tpcipriv = शून्य;

	अगर (!list_empty(&rtlpriv->glb_var->glb_priv_list)) अणु
		list_क्रम_each_entry(tpriv, &rtlpriv->glb_var->glb_priv_list,
				    list) अणु
			tpcipriv = (काष्ठा rtl_pci_priv *)tpriv->priv;
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"pcipriv->ndis_adapter.funcnumber %x\n",
				pcipriv->ndis_adapter.funcnumber);
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"tpcipriv->ndis_adapter.funcnumber %x\n",
				tpcipriv->ndis_adapter.funcnumber);

			अगर (pcipriv->ndis_adapter.busnumber ==
			    tpcipriv->ndis_adapter.busnumber &&
			    pcipriv->ndis_adapter.devnumber ==
			    tpcipriv->ndis_adapter.devnumber &&
			    pcipriv->ndis_adapter.funcnumber !=
			    tpcipriv->ndis_adapter.funcnumber) अणु
				find_buddy_priv = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"find_buddy_priv %d\n", find_buddy_priv);

	अगर (find_buddy_priv)
		*buddy_priv = tpriv;

	वापस find_buddy_priv;
पूर्ण

अटल व्योम rtl_pci_get_linkcontrol_field(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(pcipriv);
	u8 capabilityoffset = pcipriv->ndis_adapter.pcibridge_pciehdr_offset;
	u8 linkctrl_reg;
	u8 num4bbytes;

	num4bbytes = (capabilityoffset + 0x10) / 4;

	/*Read  Link Control Register */
	pci_पढ़ो_config_byte(rtlpci->pdev, (num4bbytes << 2), &linkctrl_reg);

	pcipriv->ndis_adapter.pcibridge_linkctrlreg = linkctrl_reg;
पूर्ण

अटल व्योम rtl_pci_parse_configuration(काष्ठा pci_dev *pdev,
					काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);

	u8 पंचांगp;
	u16 linkctrl_reg;

	/*Link Control Register */
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKCTL, &linkctrl_reg);
	pcipriv->ndis_adapter.linkctrl_reg = (u8)linkctrl_reg;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Link Control Register =%x\n",
		pcipriv->ndis_adapter.linkctrl_reg);

	pci_पढ़ो_config_byte(pdev, 0x98, &पंचांगp);
	पंचांगp |= BIT(4);
	pci_ग_लिखो_config_byte(pdev, 0x98, पंचांगp);

	पंचांगp = 0x17;
	pci_ग_लिखो_config_byte(pdev, 0x70f, पंचांगp);
पूर्ण

अटल व्योम rtl_pci_init_aspm(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	_rtl_pci_update_शेष_setting(hw);

	अगर (ppsc->reg_rfps_level & RT_RF_PS_LEVEL_ALWAYS_ASPM) अणु
		/*Always enable ASPM & Clock Req. */
		rtl_pci_enable_aspm(hw);
		RT_SET_PS_LEVEL(ppsc, RT_RF_PS_LEVEL_ALWAYS_ASPM);
	पूर्ण
पूर्ण

अटल व्योम _rtl_pci_io_handler_init(काष्ठा device *dev,
				     काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->io.dev = dev;

	rtlpriv->io.ग_लिखो8_async = pci_ग_लिखो8_async;
	rtlpriv->io.ग_लिखो16_async = pci_ग_लिखो16_async;
	rtlpriv->io.ग_लिखो32_async = pci_ग_लिखो32_async;

	rtlpriv->io.पढ़ो8_sync = pci_पढ़ो8_sync;
	rtlpriv->io.पढ़ो16_sync = pci_पढ़ो16_sync;
	rtlpriv->io.पढ़ो32_sync = pci_पढ़ो32_sync;
पूर्ण

अटल bool _rtl_update_earlymode_info(काष्ठा ieee80211_hw *hw,
				       काष्ठा sk_buff *skb,
				       काष्ठा rtl_tcb_desc *tcb_desc, u8 tid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा sk_buff *next_skb;
	u8 additionlen = FCS_LEN;

	/* here खोलो is 4, wep/tkip is 8, aes is 12*/
	अगर (info->control.hw_key)
		additionlen += info->control.hw_key->icv_len;

	/* The most skb num is 6 */
	tcb_desc->empkt_num = 0;
	spin_lock_bh(&rtlpriv->locks.रुकोq_lock);
	skb_queue_walk(&rtlpriv->mac80211.skb_रुकोq[tid], next_skb) अणु
		काष्ठा ieee80211_tx_info *next_info;

		next_info = IEEE80211_SKB_CB(next_skb);
		अगर (next_info->flags & IEEE80211_TX_CTL_AMPDU) अणु
			tcb_desc->empkt_len[tcb_desc->empkt_num] =
				next_skb->len + additionlen;
			tcb_desc->empkt_num++;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण

		अगर (skb_queue_is_last(&rtlpriv->mac80211.skb_रुकोq[tid],
				      next_skb))
			अवरोध;

		अगर (tcb_desc->empkt_num >= rtlhal->max_earlymode_num)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&rtlpriv->locks.रुकोq_lock);

	वापस true;
पूर्ण

/* just क्रम early mode now */
अटल व्योम _rtl_pci_tx_chk_रुकोq(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा ieee80211_tx_info *info = शून्य;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक tid;

	अगर (!rtlpriv->rtlhal.earlymode_enable)
		वापस;

	अगर (rtlpriv->dm.supp_phymode_चयन &&
	    (rtlpriv->easy_concurrent_ctl.चयन_in_process ||
	    (rtlpriv->buddy_priv &&
	    rtlpriv->buddy_priv->easy_concurrent_ctl.चयन_in_process)))
		वापस;
	/* we just use em क्रम BE/BK/VI/VO */
	क्रम (tid = 7; tid >= 0; tid--) अणु
		u8 hw_queue = ac_to_hwq[rtl_tid_to_ac(tid)];
		काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];

		जबतक (!mac->act_scanning &&
		       rtlpriv->psc.rfpwr_state == ERFON) अणु
			काष्ठा rtl_tcb_desc tcb_desc;

			स_रखो(&tcb_desc, 0, माप(काष्ठा rtl_tcb_desc));

			spin_lock(&rtlpriv->locks.रुकोq_lock);
			अगर (!skb_queue_empty(&mac->skb_रुकोq[tid]) &&
			    (ring->entries - skb_queue_len(&ring->queue) >
			     rtlhal->max_earlymode_num)) अणु
				skb = skb_dequeue(&mac->skb_रुकोq[tid]);
			पूर्ण अन्यथा अणु
				spin_unlock(&rtlpriv->locks.रुकोq_lock);
				अवरोध;
			पूर्ण
			spin_unlock(&rtlpriv->locks.रुकोq_lock);

			/* Some macaddr can't करो early mode. like
			 * multicast/broadcast/no_qos data
			 */
			info = IEEE80211_SKB_CB(skb);
			अगर (info->flags & IEEE80211_TX_CTL_AMPDU)
				_rtl_update_earlymode_info(hw, skb,
							   &tcb_desc, tid);

			rtlpriv->पूर्णांकf_ops->adapter_tx(hw, शून्य, skb, &tcb_desc);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl_pci_tx_isr(काष्ठा ieee80211_hw *hw, पूर्णांक prio)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[prio];

	जबतक (skb_queue_len(&ring->queue)) अणु
		काष्ठा sk_buff *skb;
		काष्ठा ieee80211_tx_info *info;
		__le16 fc;
		u8 tid;
		u8 *entry;

		अगर (rtlpriv->use_new_trx_flow)
			entry = (u8 *)(&ring->buffer_desc[ring->idx]);
		अन्यथा
			entry = (u8 *)(&ring->desc[ring->idx]);

		अगर (!rtlpriv->cfg->ops->is_tx_desc_बंदd(hw, prio, ring->idx))
			वापस;
		ring->idx = (ring->idx + 1) % ring->entries;

		skb = __skb_dequeue(&ring->queue);
		dma_unmap_single(&rtlpci->pdev->dev,
				 rtlpriv->cfg->ops->get_desc(hw, (u8 *)entry,
						true, HW_DESC_TXBUFF_ADDR),
				 skb->len, DMA_TO_DEVICE);

		/* हटाओ early mode header */
		अगर (rtlpriv->rtlhal.earlymode_enable)
			skb_pull(skb, EM_HDR_LEN);

		rtl_dbg(rtlpriv, (COMP_INTR | COMP_SEND), DBG_TRACE,
			"new ring->idx:%d, free: skb_queue_len:%d, free: seq:%x\n",
			ring->idx,
			skb_queue_len(&ring->queue),
			*(u16 *)(skb->data + 22));

		अगर (prio == TXCMD_QUEUE) अणु
			dev_kमुक्त_skb(skb);
			जाओ tx_status_ok;
		पूर्ण

		/* क्रम sw LPS, just after शून्य skb send out, we can
		 * sure AP knows we are sleeping, we should not let
		 * rf sleep
		 */
		fc = rtl_get_fc(skb);
		अगर (ieee80211_is_nullfunc(fc)) अणु
			अगर (ieee80211_has_pm(fc)) अणु
				rtlpriv->mac80211.offchan_delay = true;
				rtlpriv->psc.state_inap = true;
			पूर्ण अन्यथा अणु
				rtlpriv->psc.state_inap = false;
			पूर्ण
		पूर्ण
		अगर (ieee80211_is_action(fc)) अणु
			काष्ठा ieee80211_mgmt *action_frame =
				(काष्ठा ieee80211_mgmt *)skb->data;
			अगर (action_frame->u.action.u.ht_smps.action ==
			    WLAN_HT_ACTION_SMPS) अणु
				dev_kमुक्त_skb(skb);
				जाओ tx_status_ok;
			पूर्ण
		पूर्ण

		/* update tid tx pkt num */
		tid = rtl_get_tid(skb);
		अगर (tid <= 7)
			rtlpriv->link_info.tidtx_inperiod[tid]++;

		info = IEEE80211_SKB_CB(skb);

		अगर (likely(!ieee80211_is_nullfunc(fc))) अणु
			ieee80211_tx_info_clear_status(info);
			info->flags |= IEEE80211_TX_STAT_ACK;
			/*info->status.rates[0].count = 1; */
			ieee80211_tx_status_irqsafe(hw, skb);
		पूर्ण अन्यथा अणु
			rtl_tx_ackqueue(hw, skb);
		पूर्ण

		अगर ((ring->entries - skb_queue_len(&ring->queue)) <= 4) अणु
			rtl_dbg(rtlpriv, COMP_ERR, DBG_DMESG,
				"more desc left, wake skb_queue@%d, ring->idx = %d, skb_queue_len = 0x%x\n",
				prio, ring->idx,
				skb_queue_len(&ring->queue));

			ieee80211_wake_queue(hw, skb_get_queue_mapping(skb));
		पूर्ण
tx_status_ok:
		skb = शून्य;
	पूर्ण

	अगर (((rtlpriv->link_info.num_rx_inperiod +
	      rtlpriv->link_info.num_tx_inperiod) > 8) ||
	      rtlpriv->link_info.num_rx_inperiod > 2)
		rtl_lps_leave(hw, false);
पूर्ण

अटल पूर्णांक _rtl_pci_init_one_rxdesc(काष्ठा ieee80211_hw *hw,
				    काष्ठा sk_buff *new_skb, u8 *entry,
				    पूर्णांक rxring_idx, पूर्णांक desc_idx)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 bufferaddress;
	u8 पंचांगp_one = 1;
	काष्ठा sk_buff *skb;

	अगर (likely(new_skb)) अणु
		skb = new_skb;
		जाओ remap;
	पूर्ण
	skb = dev_alloc_skb(rtlpci->rxbuffersize);
	अगर (!skb)
		वापस 0;

remap:
	/* just set skb->cb to mapping addr क्रम pci_unmap_single use */
	*((dma_addr_t *)skb->cb) =
		dma_map_single(&rtlpci->pdev->dev, skb_tail_poपूर्णांकer(skb),
			       rtlpci->rxbuffersize, DMA_FROM_DEVICE);
	bufferaddress = *((dma_addr_t *)skb->cb);
	अगर (dma_mapping_error(&rtlpci->pdev->dev, bufferaddress))
		वापस 0;
	rtlpci->rx_ring[rxring_idx].rx_buf[desc_idx] = skb;
	अगर (rtlpriv->use_new_trx_flow) अणु
		/* skb->cb may be 64 bit address */
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RX_PREPARE,
					    (u8 *)(dma_addr_t *)skb->cb);
	पूर्ण अन्यथा अणु
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RXBUFF_ADDR,
					    (u8 *)&bufferaddress);
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RXPKT_LEN,
					    (u8 *)&rtlpci->rxbuffersize);
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RXOWN,
					    (u8 *)&पंचांगp_one);
	पूर्ण
	वापस 1;
पूर्ण

/* inorder to receive 8K AMSDU we have set skb to
 * 9100bytes in init rx ring, but अगर this packet is
 * not a AMSDU, this large packet will be sent to
 * TCP/IP directly, this cause big packet ping fail
 * like: "ping -s 65507", so here we will पुनः_स्मृति skb
 * based on the true size of packet, Mac80211
 * Probably will करो it better, but करोes not yet.
 *
 * Some platक्रमm will fail when alloc skb someबार.
 * in this condition, we will send the old skb to
 * mac80211 directly, this will not cause any other
 * issues, but only this packet will be lost by TCP/IP
 */
अटल व्योम _rtl_pci_rx_to_mac80211(काष्ठा ieee80211_hw *hw,
				    काष्ठा sk_buff *skb,
				    काष्ठा ieee80211_rx_status rx_status)
अणु
	अगर (unlikely(!rtl_action_proc(hw, skb, false))) अणु
		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *uskb = शून्य;

		uskb = dev_alloc_skb(skb->len + 128);
		अगर (likely(uskb)) अणु
			स_नकल(IEEE80211_SKB_RXCB(uskb), &rx_status,
			       माप(rx_status));
			skb_put_data(uskb, skb->data, skb->len);
			dev_kमुक्त_skb_any(skb);
			ieee80211_rx_irqsafe(hw, uskb);
		पूर्ण अन्यथा अणु
			ieee80211_rx_irqsafe(hw, skb);
		पूर्ण
	पूर्ण
पूर्ण

/*hsisr पूर्णांकerrupt handler*/
अटल व्योम _rtl_pci_hs_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[MAC_HSISR],
		       rtl_पढ़ो_byte(rtlpriv, rtlpriv->cfg->maps[MAC_HSISR]) |
		       rtlpci->sys_irq_mask);
पूर्ण

अटल व्योम _rtl_pci_rx_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	पूर्णांक rxring_idx = RTL_PCI_RX_MPDU_QUEUE;
	काष्ठा ieee80211_rx_status rx_status = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक count = rtlpci->rxringcount;
	u8 own;
	u8 पंचांगp_one;
	bool unicast = false;
	u8 hw_queue = 0;
	अचिन्हित पूर्णांक rx_reमुख्यed_cnt = 0;
	काष्ठा rtl_stats stats = अणु
		.संकेत = 0,
		.rate = 0,
	पूर्ण;

	/*RX NORMAL PKT */
	जबतक (count--) अणु
		काष्ठा ieee80211_hdr *hdr;
		__le16 fc;
		u16 len;
		/*rx buffer descriptor */
		काष्ठा rtl_rx_buffer_desc *buffer_desc = शून्य;
		/*अगर use new trx flow, it means wअगरi info */
		काष्ठा rtl_rx_desc *pdesc = शून्य;
		/*rx pkt */
		काष्ठा sk_buff *skb = rtlpci->rx_ring[rxring_idx].rx_buf[
				      rtlpci->rx_ring[rxring_idx].idx];
		काष्ठा sk_buff *new_skb;

		अगर (rtlpriv->use_new_trx_flow) अणु
			अगर (rx_reमुख्यed_cnt == 0)
				rx_reमुख्यed_cnt =
				rtlpriv->cfg->ops->rx_desc_buff_reमुख्यed_cnt(hw,
								      hw_queue);
			अगर (rx_reमुख्यed_cnt == 0)
				वापस;
			buffer_desc = &rtlpci->rx_ring[rxring_idx].buffer_desc[
				rtlpci->rx_ring[rxring_idx].idx];
			pdesc = (काष्ठा rtl_rx_desc *)skb->data;
		पूर्ण अन्यथा अणु	/* rx descriptor */
			pdesc = &rtlpci->rx_ring[rxring_idx].desc[
				rtlpci->rx_ring[rxring_idx].idx];

			own = (u8)rtlpriv->cfg->ops->get_desc(hw, (u8 *)pdesc,
							      false,
							      HW_DESC_OWN);
			अगर (own) /* रुको data to be filled by hardware */
				वापस;
		पूर्ण

		/* Reaching this poपूर्णांक means: data is filled alपढ़ोy
		 * AAAAAAttention !!!
		 * We can NOT access 'skb' before 'pci_unmap_single'
		 */
		dma_unmap_single(&rtlpci->pdev->dev, *((dma_addr_t *)skb->cb),
				 rtlpci->rxbuffersize, DMA_FROM_DEVICE);

		/* get a new skb - अगर fail, old one will be reused */
		new_skb = dev_alloc_skb(rtlpci->rxbuffersize);
		अगर (unlikely(!new_skb))
			जाओ no_new;
		स_रखो(&rx_status, 0, माप(rx_status));
		rtlpriv->cfg->ops->query_rx_desc(hw, &stats,
						 &rx_status, (u8 *)pdesc, skb);

		अगर (rtlpriv->use_new_trx_flow)
			rtlpriv->cfg->ops->rx_check_dma_ok(hw,
							   (u8 *)buffer_desc,
							   hw_queue);

		len = rtlpriv->cfg->ops->get_desc(hw, (u8 *)pdesc, false,
						  HW_DESC_RXPKT_LEN);

		अगर (skb->end - skb->tail > len) अणु
			skb_put(skb, len);
			अगर (rtlpriv->use_new_trx_flow)
				skb_reserve(skb, stats.rx_drvinfo_size +
					    stats.rx_bufshअगरt + 24);
			अन्यथा
				skb_reserve(skb, stats.rx_drvinfo_size +
					    stats.rx_bufshअगरt);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
				"skb->end - skb->tail = %d, len is %d\n",
				skb->end - skb->tail, len);
			dev_kमुक्त_skb_any(skb);
			जाओ new_trx_end;
		पूर्ण
		/* handle command packet here */
		अगर (stats.packet_report_type == C2H_PACKET) अणु
			rtl_c2hcmd_enqueue(hw, skb);
			जाओ new_trx_end;
		पूर्ण

		/* NOTICE This can not be use क्रम mac80211,
		 * this is करोne in mac80211 code,
		 * अगर करोne here sec DHCP will fail
		 * skb_trim(skb, skb->len - 4);
		 */

		hdr = rtl_get_hdr(skb);
		fc = rtl_get_fc(skb);

		अगर (!stats.crc && !stats.hwerror && (skb->len > FCS_LEN)) अणु
			स_नकल(IEEE80211_SKB_RXCB(skb), &rx_status,
			       माप(rx_status));

			अगर (is_broadcast_ether_addr(hdr->addr1)) अणु
				;/*TODO*/
			पूर्ण अन्यथा अगर (is_multicast_ether_addr(hdr->addr1)) अणु
				;/*TODO*/
			पूर्ण अन्यथा अणु
				unicast = true;
				rtlpriv->stats.rxbytesunicast += skb->len;
			पूर्ण
			rtl_is_special_data(hw, skb, false, true);

			अगर (ieee80211_is_data(fc)) अणु
				rtlpriv->cfg->ops->led_control(hw, LED_CTL_RX);
				अगर (unicast)
					rtlpriv->link_info.num_rx_inperiod++;
			पूर्ण

			rtl_collect_scan_list(hw, skb);

			/* अटल bcn क्रम roaming */
			rtl_beacon_statistic(hw, skb);
			rtl_p2p_info(hw, (व्योम *)skb->data, skb->len);
			/* क्रम sw lps */
			rtl_swlps_beacon(hw, (व्योम *)skb->data, skb->len);
			rtl_recognize_peer(hw, (व्योम *)skb->data, skb->len);
			अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_AP &&
			    rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G &&
			    (ieee80211_is_beacon(fc) ||
			     ieee80211_is_probe_resp(fc))) अणु
				dev_kमुक्त_skb_any(skb);
			पूर्ण अन्यथा अणु
				_rtl_pci_rx_to_mac80211(hw, skb, rx_status);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* drop packets with errors or those too लघु */
			dev_kमुक्त_skb_any(skb);
		पूर्ण
new_trx_end:
		अगर (rtlpriv->use_new_trx_flow) अणु
			rtlpci->rx_ring[hw_queue].next_rx_rp += 1;
			rtlpci->rx_ring[hw_queue].next_rx_rp %=
					RTL_PCI_MAX_RX_COUNT;

			rx_reमुख्यed_cnt--;
			rtl_ग_लिखो_word(rtlpriv, 0x3B4,
				       rtlpci->rx_ring[hw_queue].next_rx_rp);
		पूर्ण
		अगर (((rtlpriv->link_info.num_rx_inperiod +
		      rtlpriv->link_info.num_tx_inperiod) > 8) ||
		      rtlpriv->link_info.num_rx_inperiod > 2)
			rtl_lps_leave(hw, false);
		skb = new_skb;
no_new:
		अगर (rtlpriv->use_new_trx_flow) अणु
			_rtl_pci_init_one_rxdesc(hw, skb, (u8 *)buffer_desc,
						 rxring_idx,
						 rtlpci->rx_ring[rxring_idx].idx);
		पूर्ण अन्यथा अणु
			_rtl_pci_init_one_rxdesc(hw, skb, (u8 *)pdesc,
						 rxring_idx,
						 rtlpci->rx_ring[rxring_idx].idx);
			अगर (rtlpci->rx_ring[rxring_idx].idx ==
			    rtlpci->rxringcount - 1)
				rtlpriv->cfg->ops->set_desc(hw, (u8 *)pdesc,
							    false,
							    HW_DESC_RXERO,
							    (u8 *)&पंचांगp_one);
		पूर्ण
		rtlpci->rx_ring[rxring_idx].idx =
				(rtlpci->rx_ring[rxring_idx].idx + 1) %
				rtlpci->rxringcount;
	पूर्ण
पूर्ण

अटल irqवापस_t _rtl_pci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ieee80211_hw *hw = dev_id;
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	अचिन्हित दीर्घ flags;
	काष्ठा rtl_पूर्णांक पूर्णांकvec = अणु0पूर्ण;

	irqवापस_t ret = IRQ_HANDLED;

	अगर (rtlpci->irq_enabled == 0)
		वापस ret;

	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);
	rtlpriv->cfg->ops->disable_पूर्णांकerrupt(hw);

	/*पढ़ो ISR: 4/8bytes */
	rtlpriv->cfg->ops->पूर्णांकerrupt_recognized(hw, &पूर्णांकvec);

	/*Shared IRQ or HW disappeared */
	अगर (!पूर्णांकvec.पूर्णांकa || पूर्णांकvec.पूर्णांकa == 0xffff)
		जाओ करोne;

	/*<1> beacon related */
	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_TBDOK])
		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
			"beacon ok interrupt!\n");

	अगर (unlikely(पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_TBDER]))
		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
			"beacon err interrupt!\n");

	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_BDOK])
		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE, "beacon interrupt!\n");

	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_BCNINT]) अणु
		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
			"prepare beacon for interrupt!\n");
		tasklet_schedule(&rtlpriv->works.irq_prepare_bcn_tasklet);
	पूर्ण

	/*<2> Tx related */
	अगर (unlikely(पूर्णांकvec.पूर्णांकb & rtlpriv->cfg->maps[RTL_IMR_TXFOVW]))
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING, "IMR_TXFOVW!\n");

	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_MGNTDOK]) अणु
		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
			"Manage ok interrupt!\n");
		_rtl_pci_tx_isr(hw, MGNT_QUEUE);
	पूर्ण

	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_HIGHDOK]) अणु
		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
			"HIGH_QUEUE ok interrupt!\n");
		_rtl_pci_tx_isr(hw, HIGH_QUEUE);
	पूर्ण

	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_BKDOK]) अणु
		rtlpriv->link_info.num_tx_inperiod++;

		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
			"BK Tx OK interrupt!\n");
		_rtl_pci_tx_isr(hw, BK_QUEUE);
	पूर्ण

	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_BEDOK]) अणु
		rtlpriv->link_info.num_tx_inperiod++;

		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
			"BE TX OK interrupt!\n");
		_rtl_pci_tx_isr(hw, BE_QUEUE);
	पूर्ण

	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_VIDOK]) अणु
		rtlpriv->link_info.num_tx_inperiod++;

		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
			"VI TX OK interrupt!\n");
		_rtl_pci_tx_isr(hw, VI_QUEUE);
	पूर्ण

	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_VODOK]) अणु
		rtlpriv->link_info.num_tx_inperiod++;

		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
			"Vo TX OK interrupt!\n");
		_rtl_pci_tx_isr(hw, VO_QUEUE);
	पूर्ण

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8822BE) अणु
		अगर (पूर्णांकvec.पूर्णांकd & rtlpriv->cfg->maps[RTL_IMR_H2CDOK]) अणु
			rtlpriv->link_info.num_tx_inperiod++;

			rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
				"H2C TX OK interrupt!\n");
			_rtl_pci_tx_isr(hw, H2C_QUEUE);
		पूर्ण
	पूर्ण

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192SE) अणु
		अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_COMDOK]) अणु
			rtlpriv->link_info.num_tx_inperiod++;

			rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
				"CMD TX OK interrupt!\n");
			_rtl_pci_tx_isr(hw, TXCMD_QUEUE);
		पूर्ण
	पूर्ण

	/*<3> Rx related */
	अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_ROK]) अणु
		rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE, "Rx ok interrupt!\n");
		_rtl_pci_rx_पूर्णांकerrupt(hw);
	पूर्ण

	अगर (unlikely(पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_RDU])) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"rx descriptor unavailable!\n");
		_rtl_pci_rx_पूर्णांकerrupt(hw);
	पूर्ण

	अगर (unlikely(पूर्णांकvec.पूर्णांकb & rtlpriv->cfg->maps[RTL_IMR_RXFOVW])) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING, "rx overflow !\n");
		_rtl_pci_rx_पूर्णांकerrupt(hw);
	पूर्ण

	/*<4> fw related*/
	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8723AE) अणु
		अगर (पूर्णांकvec.पूर्णांकa & rtlpriv->cfg->maps[RTL_IMR_C2HCMD]) अणु
			rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
				"firmware interrupt!\n");
			queue_delayed_work(rtlpriv->works.rtl_wq,
					   &rtlpriv->works.fwevt_wq, 0);
		पूर्ण
	पूर्ण

	/*<5> hsisr related*/
	/* Only 8188EE & 8723BE Supported.
	 * If Other ICs Come in, System will corrupt,
	 * because maps[RTL_IMR_HSISR_IND] & maps[MAC_HSISR]
	 * are not initialized
	 */
	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8188EE ||
	    rtlhal->hw_type == HARDWARE_TYPE_RTL8723BE) अणु
		अगर (unlikely(पूर्णांकvec.पूर्णांकa &
		    rtlpriv->cfg->maps[RTL_IMR_HSISR_IND])) अणु
			rtl_dbg(rtlpriv, COMP_INTR, DBG_TRACE,
				"hsisr interrupt!\n");
			_rtl_pci_hs_पूर्णांकerrupt(hw);
		पूर्ण
	पूर्ण

	अगर (rtlpriv->rtlhal.earlymode_enable)
		tasklet_schedule(&rtlpriv->works.irq_tasklet);

करोne:
	rtlpriv->cfg->ops->enable_पूर्णांकerrupt(hw);
	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम _rtl_pci_irq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rtl_priv *rtlpriv = from_tasklet(rtlpriv, t, works.irq_tasklet);
	काष्ठा ieee80211_hw *hw = rtlpriv->hw;
	_rtl_pci_tx_chk_रुकोq(hw);
पूर्ण

अटल व्योम _rtl_pci_prepare_bcn_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rtl_priv *rtlpriv = from_tasklet(rtlpriv, t,
						works.irq_prepare_bcn_tasklet);
	काष्ठा ieee80211_hw *hw = rtlpriv->hw;
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl8192_tx_ring *ring = शून्य;
	काष्ठा ieee80211_hdr *hdr = शून्य;
	काष्ठा ieee80211_tx_info *info = शून्य;
	काष्ठा sk_buff *pskb = शून्य;
	काष्ठा rtl_tx_desc *pdesc = शून्य;
	काष्ठा rtl_tcb_desc tcb_desc;
	/*This is क्रम new trx flow*/
	काष्ठा rtl_tx_buffer_desc *pbuffer_desc = शून्य;
	u8 temp_one = 1;
	u8 *entry;

	स_रखो(&tcb_desc, 0, माप(काष्ठा rtl_tcb_desc));
	ring = &rtlpci->tx_ring[BEACON_QUEUE];
	pskb = __skb_dequeue(&ring->queue);
	अगर (rtlpriv->use_new_trx_flow)
		entry = (u8 *)(&ring->buffer_desc[ring->idx]);
	अन्यथा
		entry = (u8 *)(&ring->desc[ring->idx]);
	अगर (pskb) अणु
		dma_unmap_single(&rtlpci->pdev->dev,
				 rtlpriv->cfg->ops->get_desc(hw, (u8 *)entry,
						true, HW_DESC_TXBUFF_ADDR),
				 pskb->len, DMA_TO_DEVICE);
		kमुक्त_skb(pskb);
	पूर्ण

	/*NB: the beacon data buffer must be 32-bit aligned. */
	pskb = ieee80211_beacon_get(hw, mac->vअगर);
	अगर (!pskb)
		वापस;
	hdr = rtl_get_hdr(pskb);
	info = IEEE80211_SKB_CB(pskb);
	pdesc = &ring->desc[0];
	अगर (rtlpriv->use_new_trx_flow)
		pbuffer_desc = &ring->buffer_desc[0];

	rtlpriv->cfg->ops->fill_tx_desc(hw, hdr, (u8 *)pdesc,
					(u8 *)pbuffer_desc, info, शून्य, pskb,
					BEACON_QUEUE, &tcb_desc);

	__skb_queue_tail(&ring->queue, pskb);

	अगर (rtlpriv->use_new_trx_flow) अणु
		temp_one = 4;
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)pbuffer_desc, true,
					    HW_DESC_OWN, (u8 *)&temp_one);
	पूर्ण अन्यथा अणु
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)pdesc, true, HW_DESC_OWN,
					    &temp_one);
	पूर्ण
पूर्ण

अटल व्योम _rtl_pci_init_trx_var(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u8 i;
	u16 desc_num;

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192EE)
		desc_num = TX_DESC_NUM_92E;
	अन्यथा अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8822BE)
		desc_num = TX_DESC_NUM_8822B;
	अन्यथा
		desc_num = RT_TXDESC_NUM;

	क्रम (i = 0; i < RTL_PCI_MAX_TX_QUEUE_COUNT; i++)
		rtlpci->txringcount[i] = desc_num;

	/*we just alloc 2 desc क्रम beacon queue,
	 *because we just need first desc in hw beacon.
	 */
	rtlpci->txringcount[BEACON_QUEUE] = 2;

	/*BE queue need more descriptor क्रम perक्रमmance
	 *consideration or, No more tx desc will happen,
	 *and may cause mac80211 mem leakage.
	 */
	अगर (!rtl_priv(hw)->use_new_trx_flow)
		rtlpci->txringcount[BE_QUEUE] = RT_TXDESC_NUM_BE_QUEUE;

	rtlpci->rxbuffersize = 9100;	/*2048/1024; */
	rtlpci->rxringcount = RTL_PCI_MAX_RX_COUNT;	/*64; */
पूर्ण

अटल व्योम _rtl_pci_init_काष्ठा(काष्ठा ieee80211_hw *hw,
				 काष्ठा pci_dev *pdev)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	rtlpci->up_first_समय = true;
	rtlpci->being_init_adapter = false;

	rtlhal->hw = hw;
	rtlpci->pdev = pdev;

	/*Tx/Rx related var */
	_rtl_pci_init_trx_var(hw);

	/*IBSS*/
	mac->beacon_पूर्णांकerval = 100;

	/*AMPDU*/
	mac->min_space_cfg = 0;
	mac->max_mss_density = 0;
	/*set sane AMPDU शेषs */
	mac->current_ampdu_density = 7;
	mac->current_ampdu_factor = 3;

	/*Retry Limit*/
	mac->retry_लघु = 7;
	mac->retry_दीर्घ = 7;

	/*QOS*/
	rtlpci->acm_method = EACMWAY2_SW;

	/*task */
	tasklet_setup(&rtlpriv->works.irq_tasklet, _rtl_pci_irq_tasklet);
	tasklet_setup(&rtlpriv->works.irq_prepare_bcn_tasklet,
		     _rtl_pci_prepare_bcn_tasklet);
	INIT_WORK(&rtlpriv->works.lps_change_work,
		  rtl_lps_change_work_callback);
पूर्ण

अटल पूर्णांक _rtl_pci_init_tx_ring(काष्ठा ieee80211_hw *hw,
				 अचिन्हित पूर्णांक prio, अचिन्हित पूर्णांक entries)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_tx_buffer_desc *buffer_desc;
	काष्ठा rtl_tx_desc *desc;
	dma_addr_t buffer_desc_dma, desc_dma;
	u32 nextdescaddress;
	पूर्णांक i;

	/* alloc tx buffer desc क्रम new trx flow*/
	अगर (rtlpriv->use_new_trx_flow) अणु
		buffer_desc =
		   dma_alloc_coherent(&rtlpci->pdev->dev,
				      माप(*buffer_desc) * entries,
				      &buffer_desc_dma, GFP_KERNEL);

		अगर (!buffer_desc || (अचिन्हित दीर्घ)buffer_desc & 0xFF) अणु
			pr_err("Cannot allocate TX ring (prio = %d)\n",
			       prio);
			वापस -ENOMEM;
		पूर्ण

		rtlpci->tx_ring[prio].buffer_desc = buffer_desc;
		rtlpci->tx_ring[prio].buffer_desc_dma = buffer_desc_dma;

		rtlpci->tx_ring[prio].cur_tx_rp = 0;
		rtlpci->tx_ring[prio].cur_tx_wp = 0;
	पूर्ण

	/* alloc dma क्रम this ring */
	desc = dma_alloc_coherent(&rtlpci->pdev->dev, माप(*desc) * entries,
				  &desc_dma, GFP_KERNEL);

	अगर (!desc || (अचिन्हित दीर्घ)desc & 0xFF) अणु
		pr_err("Cannot allocate TX ring (prio = %d)\n", prio);
		वापस -ENOMEM;
	पूर्ण

	rtlpci->tx_ring[prio].desc = desc;
	rtlpci->tx_ring[prio].dma = desc_dma;

	rtlpci->tx_ring[prio].idx = 0;
	rtlpci->tx_ring[prio].entries = entries;
	skb_queue_head_init(&rtlpci->tx_ring[prio].queue);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "queue:%d, ring_addr:%p\n",
		prio, desc);

	/* init every desc in this ring */
	अगर (!rtlpriv->use_new_trx_flow) अणु
		क्रम (i = 0; i < entries; i++) अणु
			nextdescaddress = (u32)desc_dma +
					  ((i +	1) % entries) *
					  माप(*desc);

			rtlpriv->cfg->ops->set_desc(hw, (u8 *)&desc[i],
						    true,
						    HW_DESC_TX_NEXTDESC_ADDR,
						    (u8 *)&nextdescaddress);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl_pci_init_rx_ring(काष्ठा ieee80211_hw *hw, पूर्णांक rxring_idx)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक i;

	अगर (rtlpriv->use_new_trx_flow) अणु
		काष्ठा rtl_rx_buffer_desc *entry = शून्य;
		/* alloc dma क्रम this ring */
		rtlpci->rx_ring[rxring_idx].buffer_desc =
		    dma_alloc_coherent(&rtlpci->pdev->dev,
				       माप(*rtlpci->rx_ring[rxring_idx].buffer_desc) *
				       rtlpci->rxringcount,
				       &rtlpci->rx_ring[rxring_idx].dma, GFP_KERNEL);
		अगर (!rtlpci->rx_ring[rxring_idx].buffer_desc ||
		    (uदीर्घ)rtlpci->rx_ring[rxring_idx].buffer_desc & 0xFF) अणु
			pr_err("Cannot allocate RX ring\n");
			वापस -ENOMEM;
		पूर्ण

		/* init every desc in this ring */
		rtlpci->rx_ring[rxring_idx].idx = 0;
		क्रम (i = 0; i < rtlpci->rxringcount; i++) अणु
			entry = &rtlpci->rx_ring[rxring_idx].buffer_desc[i];
			अगर (!_rtl_pci_init_one_rxdesc(hw, शून्य, (u8 *)entry,
						      rxring_idx, i))
				वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा rtl_rx_desc *entry = शून्य;
		u8 पंचांगp_one = 1;
		/* alloc dma क्रम this ring */
		rtlpci->rx_ring[rxring_idx].desc =
		    dma_alloc_coherent(&rtlpci->pdev->dev,
				       माप(*rtlpci->rx_ring[rxring_idx].desc) *
				       rtlpci->rxringcount,
				       &rtlpci->rx_ring[rxring_idx].dma, GFP_KERNEL);
		अगर (!rtlpci->rx_ring[rxring_idx].desc ||
		    (अचिन्हित दीर्घ)rtlpci->rx_ring[rxring_idx].desc & 0xFF) अणु
			pr_err("Cannot allocate RX ring\n");
			वापस -ENOMEM;
		पूर्ण

		/* init every desc in this ring */
		rtlpci->rx_ring[rxring_idx].idx = 0;

		क्रम (i = 0; i < rtlpci->rxringcount; i++) अणु
			entry = &rtlpci->rx_ring[rxring_idx].desc[i];
			अगर (!_rtl_pci_init_one_rxdesc(hw, शून्य, (u8 *)entry,
						      rxring_idx, i))
				वापस -ENOMEM;
		पूर्ण

		rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RXERO, &पंचांगp_one);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम _rtl_pci_मुक्त_tx_ring(काष्ठा ieee80211_hw *hw,
				  अचिन्हित पूर्णांक prio)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[prio];

	/* मुक्त every desc in this ring */
	जबतक (skb_queue_len(&ring->queue)) अणु
		u8 *entry;
		काष्ठा sk_buff *skb = __skb_dequeue(&ring->queue);

		अगर (rtlpriv->use_new_trx_flow)
			entry = (u8 *)(&ring->buffer_desc[ring->idx]);
		अन्यथा
			entry = (u8 *)(&ring->desc[ring->idx]);

		dma_unmap_single(&rtlpci->pdev->dev,
				 rtlpriv->cfg->ops->get_desc(hw, (u8 *)entry,
						true, HW_DESC_TXBUFF_ADDR),
				 skb->len, DMA_TO_DEVICE);
		kमुक्त_skb(skb);
		ring->idx = (ring->idx + 1) % ring->entries;
	पूर्ण

	/* मुक्त dma of this ring */
	dma_मुक्त_coherent(&rtlpci->pdev->dev,
			  माप(*ring->desc) * ring->entries, ring->desc,
			  ring->dma);
	ring->desc = शून्य;
	अगर (rtlpriv->use_new_trx_flow) अणु
		dma_मुक्त_coherent(&rtlpci->pdev->dev,
				  माप(*ring->buffer_desc) * ring->entries,
				  ring->buffer_desc, ring->buffer_desc_dma);
		ring->buffer_desc = शून्य;
	पूर्ण
पूर्ण

अटल व्योम _rtl_pci_मुक्त_rx_ring(काष्ठा ieee80211_hw *hw, पूर्णांक rxring_idx)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	पूर्णांक i;

	/* मुक्त every desc in this ring */
	क्रम (i = 0; i < rtlpci->rxringcount; i++) अणु
		काष्ठा sk_buff *skb = rtlpci->rx_ring[rxring_idx].rx_buf[i];

		अगर (!skb)
			जारी;
		dma_unmap_single(&rtlpci->pdev->dev, *((dma_addr_t *)skb->cb),
				 rtlpci->rxbuffersize, DMA_FROM_DEVICE);
		kमुक्त_skb(skb);
	पूर्ण

	/* मुक्त dma of this ring */
	अगर (rtlpriv->use_new_trx_flow) अणु
		dma_मुक्त_coherent(&rtlpci->pdev->dev,
				  माप(*rtlpci->rx_ring[rxring_idx].buffer_desc) *
				  rtlpci->rxringcount,
				  rtlpci->rx_ring[rxring_idx].buffer_desc,
				  rtlpci->rx_ring[rxring_idx].dma);
		rtlpci->rx_ring[rxring_idx].buffer_desc = शून्य;
	पूर्ण अन्यथा अणु
		dma_मुक्त_coherent(&rtlpci->pdev->dev,
				  माप(*rtlpci->rx_ring[rxring_idx].desc) *
				  rtlpci->rxringcount,
				  rtlpci->rx_ring[rxring_idx].desc,
				  rtlpci->rx_ring[rxring_idx].dma);
		rtlpci->rx_ring[rxring_idx].desc = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक _rtl_pci_init_trx_ring(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	पूर्णांक ret;
	पूर्णांक i, rxring_idx;

	/* rxring_idx 0:RX_MPDU_QUEUE
	 * rxring_idx 1:RX_CMD_QUEUE
	 */
	क्रम (rxring_idx = 0; rxring_idx < RTL_PCI_MAX_RX_QUEUE; rxring_idx++) अणु
		ret = _rtl_pci_init_rx_ring(hw, rxring_idx);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < RTL_PCI_MAX_TX_QUEUE_COUNT; i++) अणु
		ret = _rtl_pci_init_tx_ring(hw, i, rtlpci->txringcount[i]);
		अगर (ret)
			जाओ err_मुक्त_rings;
	पूर्ण

	वापस 0;

err_मुक्त_rings:
	क्रम (rxring_idx = 0; rxring_idx < RTL_PCI_MAX_RX_QUEUE; rxring_idx++)
		_rtl_pci_मुक्त_rx_ring(hw, rxring_idx);

	क्रम (i = 0; i < RTL_PCI_MAX_TX_QUEUE_COUNT; i++)
		अगर (rtlpci->tx_ring[i].desc ||
		    rtlpci->tx_ring[i].buffer_desc)
			_rtl_pci_मुक्त_tx_ring(hw, i);

	वापस 1;
पूर्ण

अटल पूर्णांक _rtl_pci_deinit_trx_ring(काष्ठा ieee80211_hw *hw)
अणु
	u32 i, rxring_idx;

	/*मुक्त rx rings */
	क्रम (rxring_idx = 0; rxring_idx < RTL_PCI_MAX_RX_QUEUE; rxring_idx++)
		_rtl_pci_मुक्त_rx_ring(hw, rxring_idx);

	/*मुक्त tx rings */
	क्रम (i = 0; i < RTL_PCI_MAX_TX_QUEUE_COUNT; i++)
		_rtl_pci_मुक्त_tx_ring(hw, i);

	वापस 0;
पूर्ण

पूर्णांक rtl_pci_reset_trx_ring(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	पूर्णांक i, rxring_idx;
	अचिन्हित दीर्घ flags;
	u8 पंचांगp_one = 1;
	u32 bufferaddress;
	/* rxring_idx 0:RX_MPDU_QUEUE */
	/* rxring_idx 1:RX_CMD_QUEUE */
	क्रम (rxring_idx = 0; rxring_idx < RTL_PCI_MAX_RX_QUEUE; rxring_idx++) अणु
		/* क्रमce the rx_ring[RX_MPDU_QUEUE/
		 * RX_CMD_QUEUE].idx to the first one
		 *new trx flow, करो nothing
		 */
		अगर (!rtlpriv->use_new_trx_flow &&
		    rtlpci->rx_ring[rxring_idx].desc) अणु
			काष्ठा rtl_rx_desc *entry = शून्य;

			rtlpci->rx_ring[rxring_idx].idx = 0;
			क्रम (i = 0; i < rtlpci->rxringcount; i++) अणु
				entry = &rtlpci->rx_ring[rxring_idx].desc[i];
				bufferaddress =
				  rtlpriv->cfg->ops->get_desc(hw, (u8 *)entry,
				  false, HW_DESC_RXBUFF_ADDR);
				स_रखो((u8 *)entry, 0,
				       माप(*rtlpci->rx_ring
				       [rxring_idx].desc));/*clear one entry*/
				अगर (rtlpriv->use_new_trx_flow) अणु
					rtlpriv->cfg->ops->set_desc(hw,
					    (u8 *)entry, false,
					    HW_DESC_RX_PREPARE,
					    (u8 *)&bufferaddress);
				पूर्ण अन्यथा अणु
					rtlpriv->cfg->ops->set_desc(hw,
					    (u8 *)entry, false,
					    HW_DESC_RXBUFF_ADDR,
					    (u8 *)&bufferaddress);
					rtlpriv->cfg->ops->set_desc(hw,
					    (u8 *)entry, false,
					    HW_DESC_RXPKT_LEN,
					    (u8 *)&rtlpci->rxbuffersize);
					rtlpriv->cfg->ops->set_desc(hw,
					    (u8 *)entry, false,
					    HW_DESC_RXOWN,
					    (u8 *)&पंचांगp_one);
				पूर्ण
			पूर्ण
			rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RXERO, (u8 *)&पंचांगp_one);
		पूर्ण
		rtlpci->rx_ring[rxring_idx].idx = 0;
	पूर्ण

	/*after reset, release previous pending packet,
	 *and क्रमce the  tx idx to the first one
	 */
	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);
	क्रम (i = 0; i < RTL_PCI_MAX_TX_QUEUE_COUNT; i++) अणु
		अगर (rtlpci->tx_ring[i].desc ||
		    rtlpci->tx_ring[i].buffer_desc) अणु
			काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[i];

			जबतक (skb_queue_len(&ring->queue)) अणु
				u8 *entry;
				काष्ठा sk_buff *skb =
					__skb_dequeue(&ring->queue);
				अगर (rtlpriv->use_new_trx_flow)
					entry = (u8 *)(&ring->buffer_desc
								[ring->idx]);
				अन्यथा
					entry = (u8 *)(&ring->desc[ring->idx]);

				dma_unmap_single(&rtlpci->pdev->dev,
						 rtlpriv->cfg->ops->get_desc(hw, (u8 *)entry,
								true, HW_DESC_TXBUFF_ADDR),
						 skb->len, DMA_TO_DEVICE);
				dev_kमुक्त_skb_irq(skb);
				ring->idx = (ring->idx + 1) % ring->entries;
			पूर्ण

			अगर (rtlpriv->use_new_trx_flow) अणु
				rtlpci->tx_ring[i].cur_tx_rp = 0;
				rtlpci->tx_ring[i].cur_tx_wp = 0;
			पूर्ण

			ring->idx = 0;
			ring->entries = rtlpci->txringcount[i];
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);

	वापस 0;
पूर्ण

अटल bool rtl_pci_tx_chk_रुकोq_insert(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_sta *sta,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u8 tid = rtl_get_tid(skb);
	__le16 fc = rtl_get_fc(skb);

	अगर (!sta)
		वापस false;
	sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;

	अगर (!rtlpriv->rtlhal.earlymode_enable)
		वापस false;
	अगर (ieee80211_is_nullfunc(fc))
		वापस false;
	अगर (ieee80211_is_qos_nullfunc(fc))
		वापस false;
	अगर (ieee80211_is_pspoll(fc))
		वापस false;
	अगर (sta_entry->tids[tid].agg.agg_state != RTL_AGG_OPERATIONAL)
		वापस false;
	अगर (_rtl_mac_to_hwqueue(hw, skb) > VO_QUEUE)
		वापस false;
	अगर (tid > 7)
		वापस false;

	/* maybe every tid should be checked */
	अगर (!rtlpriv->link_info.higher_busytxtraffic[tid])
		वापस false;

	spin_lock_bh(&rtlpriv->locks.रुकोq_lock);
	skb_queue_tail(&rtlpriv->mac80211.skb_रुकोq[tid], skb);
	spin_unlock_bh(&rtlpriv->locks.रुकोq_lock);

	वापस true;
पूर्ण

अटल पूर्णांक rtl_pci_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_sta *sta,
		      काष्ठा sk_buff *skb,
		      काष्ठा rtl_tcb_desc *ptcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा rtl8192_tx_ring *ring;
	काष्ठा rtl_tx_desc *pdesc;
	काष्ठा rtl_tx_buffer_desc *ptx_bd_desc = शून्य;
	u16 idx;
	u8 hw_queue = _rtl_mac_to_hwqueue(hw, skb);
	अचिन्हित दीर्घ flags;
	काष्ठा ieee80211_hdr *hdr = rtl_get_hdr(skb);
	__le16 fc = rtl_get_fc(skb);
	u8 *pda_addr = hdr->addr1;
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 own;
	u8 temp_one = 1;

	अगर (ieee80211_is_mgmt(fc))
		rtl_tx_mgmt_proc(hw, skb);

	अगर (rtlpriv->psc.sw_ps_enabled) अणु
		अगर (ieee80211_is_data(fc) && !ieee80211_is_nullfunc(fc) &&
		    !ieee80211_has_pm(fc))
			hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);
	पूर्ण

	rtl_action_proc(hw, skb, true);

	अगर (is_multicast_ether_addr(pda_addr))
		rtlpriv->stats.txbytesmulticast += skb->len;
	अन्यथा अगर (is_broadcast_ether_addr(pda_addr))
		rtlpriv->stats.txbytesbroadcast += skb->len;
	अन्यथा
		rtlpriv->stats.txbytesunicast += skb->len;

	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);
	ring = &rtlpci->tx_ring[hw_queue];
	अगर (hw_queue != BEACON_QUEUE) अणु
		अगर (rtlpriv->use_new_trx_flow)
			idx = ring->cur_tx_wp;
		अन्यथा
			idx = (ring->idx + skb_queue_len(&ring->queue)) %
			      ring->entries;
	पूर्ण अन्यथा अणु
		idx = 0;
	पूर्ण

	pdesc = &ring->desc[idx];
	अगर (rtlpriv->use_new_trx_flow) अणु
		ptx_bd_desc = &ring->buffer_desc[idx];
	पूर्ण अन्यथा अणु
		own = (u8)rtlpriv->cfg->ops->get_desc(hw, (u8 *)pdesc,
				true, HW_DESC_OWN);

		अगर (own == 1 && hw_queue != BEACON_QUEUE) अणु
			rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
				"No more TX desc@%d, ring->idx = %d, idx = %d, skb_queue_len = 0x%x\n",
				hw_queue, ring->idx, idx,
				skb_queue_len(&ring->queue));

			spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock,
					       flags);
			वापस skb->len;
		पूर्ण
	पूर्ण

	अगर (rtlpriv->cfg->ops->get_available_desc &&
	    rtlpriv->cfg->ops->get_available_desc(hw, hw_queue) == 0) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"get_available_desc fail\n");
		spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);
		वापस skb->len;
	पूर्ण

	अगर (ieee80211_is_data(fc))
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_TX);

	rtlpriv->cfg->ops->fill_tx_desc(hw, hdr, (u8 *)pdesc,
			(u8 *)ptx_bd_desc, info, sta, skb, hw_queue, ptcb_desc);

	__skb_queue_tail(&ring->queue, skb);

	अगर (rtlpriv->use_new_trx_flow) अणु
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)pdesc, true,
					    HW_DESC_OWN, &hw_queue);
	पूर्ण अन्यथा अणु
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)pdesc, true,
					    HW_DESC_OWN, &temp_one);
	पूर्ण

	अगर ((ring->entries - skb_queue_len(&ring->queue)) < 2 &&
	    hw_queue != BEACON_QUEUE) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"less desc left, stop skb_queue@%d, ring->idx = %d, idx = %d, skb_queue_len = 0x%x\n",
			 hw_queue, ring->idx, idx,
			 skb_queue_len(&ring->queue));

		ieee80211_stop_queue(hw, skb_get_queue_mapping(skb));
	पूर्ण

	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);

	rtlpriv->cfg->ops->tx_polling(hw, hw_queue);

	वापस 0;
पूर्ण

अटल व्योम rtl_pci_flush(काष्ठा ieee80211_hw *hw, u32 queues, bool drop)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 i = 0;
	पूर्णांक queue_id;
	काष्ठा rtl8192_tx_ring *ring;

	अगर (mac->skip_scan)
		वापस;

	क्रम (queue_id = RTL_PCI_MAX_TX_QUEUE_COUNT - 1; queue_id >= 0;) अणु
		u32 queue_len;

		अगर (((queues >> queue_id) & 0x1) == 0) अणु
			queue_id--;
			जारी;
		पूर्ण
		ring = &pcipriv->dev.tx_ring[queue_id];
		queue_len = skb_queue_len(&ring->queue);
		अगर (queue_len == 0 || queue_id == BEACON_QUEUE ||
		    queue_id == TXCMD_QUEUE) अणु
			queue_id--;
			जारी;
		पूर्ण अन्यथा अणु
			msleep(20);
			i++;
		पूर्ण

		/* we just रुको 1s क्रम all queues */
		अगर (rtlpriv->psc.rfpwr_state == ERFOFF ||
		    is_hal_stop(rtlhal) || i >= 200)
			वापस;
	पूर्ण
पूर्ण

अटल व्योम rtl_pci_deinit(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	_rtl_pci_deinit_trx_ring(hw);

	synchronize_irq(rtlpci->pdev->irq);
	tasklet_समाप्त(&rtlpriv->works.irq_tasklet);
	cancel_work_sync(&rtlpriv->works.lps_change_work);

	flush_workqueue(rtlpriv->works.rtl_wq);
	destroy_workqueue(rtlpriv->works.rtl_wq);
पूर्ण

अटल पूर्णांक rtl_pci_init(काष्ठा ieee80211_hw *hw, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err;

	_rtl_pci_init_काष्ठा(hw, pdev);

	err = _rtl_pci_init_trx_ring(hw);
	अगर (err) अणु
		pr_err("tx ring initialization failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl_pci_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_btc_ops *btc_ops = rtlpriv->btcoexist.btc_ops;

	पूर्णांक err;

	rtl_pci_reset_trx_ring(hw);

	rtlpci->driver_is_goingto_unload = false;
	अगर (rtlpriv->cfg->ops->get_btc_status &&
	    rtlpriv->cfg->ops->get_btc_status()) अणु
		rtlpriv->btcoexist.btc_info.ap_num = 36;
		btc_ops->btc_init_variables(rtlpriv);
		btc_ops->btc_init_hal_vars(rtlpriv);
	पूर्ण अन्यथा अगर (btc_ops) अणु
		btc_ops->btc_init_variables_wअगरi_only(rtlpriv);
	पूर्ण

	err = rtlpriv->cfg->ops->hw_init(hw);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"Failed to config hardware!\n");
		kमुक्त(rtlpriv->btcoexist.btc_context);
		kमुक्त(rtlpriv->btcoexist.wअगरi_only_context);
		वापस err;
	पूर्ण
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RETRY_LIMIT,
			&rtlmac->retry_दीर्घ);

	rtlpriv->cfg->ops->enable_पूर्णांकerrupt(hw);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "enable_interrupt OK\n");

	rtl_init_rx_config(hw);

	/*should be after adapter start and पूर्णांकerrupt enable. */
	set_hal_start(rtlhal);

	RT_CLEAR_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);

	rtlpci->up_first_समय = false;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "%s OK\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम rtl_pci_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	अचिन्हित दीर्घ flags;
	u8 rf_समयout = 0;

	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_halt_notअगरy(rtlpriv);

	अगर (rtlpriv->btcoexist.btc_ops)
		rtlpriv->btcoexist.btc_ops->btc_deinit_variables(rtlpriv);

	/*should be beक्रमe disable पूर्णांकerrupt&adapter
	 *and will करो it immediately.
	 */
	set_hal_stop(rtlhal);

	rtlpci->driver_is_goingto_unload = true;
	rtlpriv->cfg->ops->disable_पूर्णांकerrupt(hw);
	cancel_work_sync(&rtlpriv->works.lps_change_work);

	spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flags);
	जबतक (ppsc->rfchange_inprogress) अणु
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flags);
		अगर (rf_समयout > 100) अणु
			spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flags);
			अवरोध;
		पूर्ण
		mdelay(1);
		rf_समयout++;
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flags);
	पूर्ण
	ppsc->rfchange_inprogress = true;
	spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flags);

	rtlpriv->cfg->ops->hw_disable(hw);
	/* some things are not needed अगर firmware not available */
	अगर (!rtlpriv->max_fw_size)
		वापस;
	rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);

	spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flags);
	ppsc->rfchange_inprogress = false;
	spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flags);

	rtl_pci_enable_aspm(hw);
पूर्ण

अटल bool _rtl_pci_find_adapter(काष्ठा pci_dev *pdev,
				  काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा pci_dev *bridge_pdev = pdev->bus->self;
	u16 venderid;
	u16 deviceid;
	u8 revisionid;
	u16 irqline;
	u8 पंचांगp;

	pcipriv->ndis_adapter.pcibridge_venकरोr = PCI_BRIDGE_VENDOR_UNKNOWN;
	venderid = pdev->venकरोr;
	deviceid = pdev->device;
	pci_पढ़ो_config_byte(pdev, 0x8, &revisionid);
	pci_पढ़ो_config_word(pdev, 0x3C, &irqline);

	/* PCI ID 0x10ec:0x8192 occurs क्रम both RTL8192E, which uses
	 * r8192e_pci, and RTL8192SE, which uses this driver. If the
	 * revision ID is RTL_PCI_REVISION_ID_8192PCIE (0x01), then
	 * the correct driver is r8192e_pci, thus this routine should
	 * वापस false.
	 */
	अगर (deviceid == RTL_PCI_8192SE_DID &&
	    revisionid == RTL_PCI_REVISION_ID_8192PCIE)
		वापस false;

	अगर (deviceid == RTL_PCI_8192_DID ||
	    deviceid == RTL_PCI_0044_DID ||
	    deviceid == RTL_PCI_0047_DID ||
	    deviceid == RTL_PCI_8192SE_DID ||
	    deviceid == RTL_PCI_8174_DID ||
	    deviceid == RTL_PCI_8173_DID ||
	    deviceid == RTL_PCI_8172_DID ||
	    deviceid == RTL_PCI_8171_DID) अणु
		चयन (revisionid) अणु
		हाल RTL_PCI_REVISION_ID_8192PCIE:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
				"8192 PCI-E is found - vid/did=%x/%x\n",
				venderid, deviceid);
			rtlhal->hw_type = HARDWARE_TYPE_RTL8192E;
			वापस false;
		हाल RTL_PCI_REVISION_ID_8192SE:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
				"8192SE is found - vid/did=%x/%x\n",
				venderid, deviceid);
			rtlhal->hw_type = HARDWARE_TYPE_RTL8192SE;
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
				"Err: Unknown device - vid/did=%x/%x\n",
				venderid, deviceid);
			rtlhal->hw_type = HARDWARE_TYPE_RTL8192SE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (deviceid == RTL_PCI_8723AE_DID) अणु
		rtlhal->hw_type = HARDWARE_TYPE_RTL8723AE;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"8723AE PCI-E is found - vid/did=%x/%x\n",
			venderid, deviceid);
	पूर्ण अन्यथा अगर (deviceid == RTL_PCI_8192CET_DID ||
		   deviceid == RTL_PCI_8192CE_DID ||
		   deviceid == RTL_PCI_8191CE_DID ||
		   deviceid == RTL_PCI_8188CE_DID) अणु
		rtlhal->hw_type = HARDWARE_TYPE_RTL8192CE;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"8192C PCI-E is found - vid/did=%x/%x\n",
			venderid, deviceid);
	पूर्ण अन्यथा अगर (deviceid == RTL_PCI_8192DE_DID ||
		   deviceid == RTL_PCI_8192DE_DID2) अणु
		rtlhal->hw_type = HARDWARE_TYPE_RTL8192DE;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"8192D PCI-E is found - vid/did=%x/%x\n",
			venderid, deviceid);
	पूर्ण अन्यथा अगर (deviceid == RTL_PCI_8188EE_DID) अणु
		rtlhal->hw_type = HARDWARE_TYPE_RTL8188EE;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Find adapter, Hardware type is 8188EE\n");
	पूर्ण अन्यथा अगर (deviceid == RTL_PCI_8723BE_DID) अणु
		rtlhal->hw_type = HARDWARE_TYPE_RTL8723BE;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Find adapter, Hardware type is 8723BE\n");
	पूर्ण अन्यथा अगर (deviceid == RTL_PCI_8192EE_DID) अणु
		rtlhal->hw_type = HARDWARE_TYPE_RTL8192EE;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Find adapter, Hardware type is 8192EE\n");
	पूर्ण अन्यथा अगर (deviceid == RTL_PCI_8821AE_DID) अणु
		rtlhal->hw_type = HARDWARE_TYPE_RTL8821AE;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Find adapter, Hardware type is 8821AE\n");
	पूर्ण अन्यथा अगर (deviceid == RTL_PCI_8812AE_DID) अणु
		rtlhal->hw_type = HARDWARE_TYPE_RTL8812AE;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Find adapter, Hardware type is 8812AE\n");
	पूर्ण अन्यथा अगर (deviceid == RTL_PCI_8822BE_DID) अणु
		rtlhal->hw_type = HARDWARE_TYPE_RTL8822BE;
		rtlhal->bandset = BAND_ON_BOTH;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Find adapter, Hardware type is 8822BE\n");
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Err: Unknown device - vid/did=%x/%x\n",
			 venderid, deviceid);

		rtlhal->hw_type = RTL_DEFAULT_HARDWARE_TYPE;
	पूर्ण

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192DE) अणु
		अगर (revisionid == 0 || revisionid == 1) अणु
			अगर (revisionid == 0) अणु
				rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
					"Find 92DE MAC0\n");
				rtlhal->पूर्णांकerfaceindex = 0;
			पूर्ण अन्यथा अगर (revisionid == 1) अणु
				rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
					"Find 92DE MAC1\n");
				rtlhal->पूर्णांकerfaceindex = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Unknown device - VendorID/DeviceID=%x/%x, Revision=%x\n",
				 venderid, deviceid, revisionid);
			rtlhal->पूर्णांकerfaceindex = 0;
		पूर्ण
	पूर्ण

	चयन (rtlhal->hw_type) अणु
	हाल HARDWARE_TYPE_RTL8192EE:
	हाल HARDWARE_TYPE_RTL8822BE:
		/* use new trx flow */
		rtlpriv->use_new_trx_flow = true;
		अवरोध;

	शेष:
		rtlpriv->use_new_trx_flow = false;
		अवरोध;
	पूर्ण

	/*find bus info */
	pcipriv->ndis_adapter.busnumber = pdev->bus->number;
	pcipriv->ndis_adapter.devnumber = PCI_SLOT(pdev->devfn);
	pcipriv->ndis_adapter.funcnumber = PCI_FUNC(pdev->devfn);

	/*find bridge info */
	pcipriv->ndis_adapter.pcibridge_venकरोr = PCI_BRIDGE_VENDOR_UNKNOWN;
	/* some ARM have no bridge_pdev and will crash here
	 * so we should check अगर bridge_pdev is शून्य
	 */
	अगर (bridge_pdev) अणु
		/*find bridge info अगर available */
		pcipriv->ndis_adapter.pcibridge_venकरोrid = bridge_pdev->venकरोr;
		क्रम (पंचांगp = 0; पंचांगp < PCI_BRIDGE_VENDOR_MAX; पंचांगp++) अणु
			अगर (bridge_pdev->venकरोr == pcibridge_venकरोrs[पंचांगp]) अणु
				pcipriv->ndis_adapter.pcibridge_venकरोr = पंचांगp;
				rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
					"Pci Bridge Vendor is found index: %d\n",
					पंचांगp);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pcipriv->ndis_adapter.pcibridge_venकरोr !=
		PCI_BRIDGE_VENDOR_UNKNOWN) अणु
		pcipriv->ndis_adapter.pcibridge_busnum =
		    bridge_pdev->bus->number;
		pcipriv->ndis_adapter.pcibridge_devnum =
		    PCI_SLOT(bridge_pdev->devfn);
		pcipriv->ndis_adapter.pcibridge_funcnum =
		    PCI_FUNC(bridge_pdev->devfn);
		pcipriv->ndis_adapter.pcibridge_pciehdr_offset =
		    pci_pcie_cap(bridge_pdev);
		pcipriv->ndis_adapter.num4bytes =
		    (pcipriv->ndis_adapter.pcibridge_pciehdr_offset + 0x10) / 4;

		rtl_pci_get_linkcontrol_field(hw);

		अगर (pcipriv->ndis_adapter.pcibridge_venकरोr ==
		    PCI_BRIDGE_VENDOR_AMD) अणु
			pcipriv->ndis_adapter.amd_l1_patch =
			    rtl_pci_get_amd_l1_patch(hw);
		पूर्ण
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
		"pcidev busnumber:devnumber:funcnumber:vendor:link_ctl %d:%d:%d:%x:%x\n",
		pcipriv->ndis_adapter.busnumber,
		pcipriv->ndis_adapter.devnumber,
		pcipriv->ndis_adapter.funcnumber,
		pdev->venकरोr, pcipriv->ndis_adapter.linkctrl_reg);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
		"pci_bridge busnumber:devnumber:funcnumber:vendor:pcie_cap:link_ctl_reg:amd %d:%d:%d:%x:%x:%x:%x\n",
		pcipriv->ndis_adapter.pcibridge_busnum,
		pcipriv->ndis_adapter.pcibridge_devnum,
		pcipriv->ndis_adapter.pcibridge_funcnum,
		pcibridge_venकरोrs[pcipriv->ndis_adapter.pcibridge_venकरोr],
		pcipriv->ndis_adapter.pcibridge_pciehdr_offset,
		pcipriv->ndis_adapter.pcibridge_linkctrlreg,
		pcipriv->ndis_adapter.amd_l1_patch);

	rtl_pci_parse_configuration(pdev, hw);
	list_add_tail(&rtlpriv->list, &rtlpriv->glb_var->glb_priv_list);

	वापस true;
पूर्ण

अटल पूर्णांक rtl_pci_पूर्णांकr_mode_msi(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(pcipriv);
	पूर्णांक ret;

	ret = pci_enable_msi(rtlpci->pdev);
	अगर (ret < 0)
		वापस ret;

	ret = request_irq(rtlpci->pdev->irq, &_rtl_pci_पूर्णांकerrupt,
			  IRQF_SHARED, KBUILD_MODNAME, hw);
	अगर (ret < 0) अणु
		pci_disable_msi(rtlpci->pdev);
		वापस ret;
	पूर्ण

	rtlpci->using_msi = true;

	rtl_dbg(rtlpriv, COMP_INIT | COMP_INTR, DBG_DMESG,
		"MSI Interrupt Mode!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक rtl_pci_पूर्णांकr_mode_legacy(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(pcipriv);
	पूर्णांक ret;

	ret = request_irq(rtlpci->pdev->irq, &_rtl_pci_पूर्णांकerrupt,
			  IRQF_SHARED, KBUILD_MODNAME, hw);
	अगर (ret < 0)
		वापस ret;

	rtlpci->using_msi = false;
	rtl_dbg(rtlpriv, COMP_INIT | COMP_INTR, DBG_DMESG,
		"Pin-based Interrupt Mode!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक rtl_pci_पूर्णांकr_mode_decide(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(pcipriv);
	पूर्णांक ret;

	अगर (rtlpci->msi_support) अणु
		ret = rtl_pci_पूर्णांकr_mode_msi(hw);
		अगर (ret < 0)
			ret = rtl_pci_पूर्णांकr_mode_legacy(hw);
	पूर्ण अन्यथा अणु
		ret = rtl_pci_पूर्णांकr_mode_legacy(hw);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम platक्रमm_enable_dma64(काष्ठा pci_dev *pdev, bool dma64)
अणु
	u8	value;

	pci_पढ़ो_config_byte(pdev, 0x719, &value);

	/* 0x719 Bit5 is DMA64 bit fetch. */
	अगर (dma64)
		value |= BIT(5);
	अन्यथा
		value &= ~BIT(5);

	pci_ग_लिखो_config_byte(pdev, 0x719, value);
पूर्ण

पूर्णांक rtl_pci_probe(काष्ठा pci_dev *pdev,
		  स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ieee80211_hw *hw = शून्य;

	काष्ठा rtl_priv *rtlpriv = शून्य;
	काष्ठा rtl_pci_priv *pcipriv = शून्य;
	काष्ठा rtl_pci *rtlpci;
	अचिन्हित दीर्घ pmem_start, pmem_len, pmem_flags;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		WARN_ONCE(true, "%s : Cannot enable new PCI device\n",
			  pci_name(pdev));
		वापस err;
	पूर्ण

	अगर (((काष्ठा rtl_hal_cfg *)id->driver_data)->mod_params->dma64 &&
	    !dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
		अगर (dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
			WARN_ONCE(true,
				  "Unable to obtain 64bit DMA for consistent allocations\n");
			err = -ENOMEM;
			जाओ fail1;
		पूर्ण

		platक्रमm_enable_dma64(pdev, true);
	पूर्ण अन्यथा अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		अगर (dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
			WARN_ONCE(true,
				  "rtlwifi: Unable to obtain 32bit DMA for consistent allocations\n");
			err = -ENOMEM;
			जाओ fail1;
		पूर्ण

		platक्रमm_enable_dma64(pdev, false);
	पूर्ण

	pci_set_master(pdev);

	hw = ieee80211_alloc_hw(माप(काष्ठा rtl_pci_priv) +
				माप(काष्ठा rtl_priv), &rtl_ops);
	अगर (!hw) अणु
		WARN_ONCE(true,
			  "%s : ieee80211 alloc failed\n", pci_name(pdev));
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	SET_IEEE80211_DEV(hw, &pdev->dev);
	pci_set_drvdata(pdev, hw);

	rtlpriv = hw->priv;
	rtlpriv->hw = hw;
	pcipriv = (व्योम *)rtlpriv->priv;
	pcipriv->dev.pdev = pdev;
	init_completion(&rtlpriv->firmware_loading_complete);
	/*proximity init here*/
	rtlpriv->proximity.proxim_on = false;

	pcipriv = (व्योम *)rtlpriv->priv;
	pcipriv->dev.pdev = pdev;

	/* init cfg & पूर्णांकf_ops */
	rtlpriv->rtlhal.पूर्णांकerface = INTF_PCI;
	rtlpriv->cfg = (काष्ठा rtl_hal_cfg *)(id->driver_data);
	rtlpriv->पूर्णांकf_ops = &rtl_pci_ops;
	rtlpriv->glb_var = &rtl_global_var;
	rtl_efuse_ops_init(hw);

	/* MEM map */
	err = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (err) अणु
		WARN_ONCE(true, "rtlwifi: Can't obtain PCI resources\n");
		जाओ fail1;
	पूर्ण

	pmem_start = pci_resource_start(pdev, rtlpriv->cfg->bar_id);
	pmem_len = pci_resource_len(pdev, rtlpriv->cfg->bar_id);
	pmem_flags = pci_resource_flags(pdev, rtlpriv->cfg->bar_id);

	/*shared mem start */
	rtlpriv->io.pci_mem_start =
			(अचिन्हित दीर्घ)pci_iomap(pdev,
			rtlpriv->cfg->bar_id, pmem_len);
	अगर (rtlpriv->io.pci_mem_start == 0) अणु
		WARN_ONCE(true, "rtlwifi: Can't map PCI mem\n");
		err = -ENOMEM;
		जाओ fail2;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
		"mem mapped space: start: 0x%08lx len:%08lx flags:%08lx, after map:0x%08lx\n",
		pmem_start, pmem_len, pmem_flags,
		rtlpriv->io.pci_mem_start);

	/* Disable Clk Request */
	pci_ग_लिखो_config_byte(pdev, 0x81, 0);
	/* leave D3 mode */
	pci_ग_लिखो_config_byte(pdev, 0x44, 0);
	pci_ग_लिखो_config_byte(pdev, 0x04, 0x06);
	pci_ग_लिखो_config_byte(pdev, 0x04, 0x07);

	/* find adapter */
	अगर (!_rtl_pci_find_adapter(pdev, hw)) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	/* Init IO handler */
	_rtl_pci_io_handler_init(&pdev->dev, hw);

	/*like पढ़ो eeprom and so on */
	rtlpriv->cfg->ops->पढ़ो_eeprom_info(hw);

	अगर (rtlpriv->cfg->ops->init_sw_vars(hw)) अणु
		pr_err("Can't init_sw_vars\n");
		err = -ENODEV;
		जाओ fail3;
	पूर्ण
	rtlpriv->cfg->ops->init_sw_leds(hw);

	/*aspm */
	rtl_pci_init_aspm(hw);

	/* Init mac80211 sw */
	err = rtl_init_core(hw);
	अगर (err) अणु
		pr_err("Can't allocate sw for mac80211\n");
		जाओ fail3;
	पूर्ण

	/* Init PCI sw */
	err = rtl_pci_init(hw, pdev);
	अगर (err) अणु
		pr_err("Failed to init PCI\n");
		जाओ fail3;
	पूर्ण

	err = ieee80211_रेजिस्टर_hw(hw);
	अगर (err) अणु
		pr_err("Can't register mac80211 hw.\n");
		err = -ENODEV;
		जाओ fail3;
	पूर्ण
	rtlpriv->mac80211.mac80211_रेजिस्टरed = 1;

	/* add क्रम debug */
	rtl_debug_add_one(hw);

	/*init rfसमाप्त */
	rtl_init_rfसमाप्त(hw);	/* Init PCI sw */

	rtlpci = rtl_pcidev(pcipriv);
	err = rtl_pci_पूर्णांकr_mode_decide(hw);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"%s: failed to register IRQ handler\n",
			wiphy_name(hw->wiphy));
		जाओ fail3;
	पूर्ण
	rtlpci->irq_alloc = 1;

	set_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status);
	वापस 0;

fail3:
	pci_set_drvdata(pdev, शून्य);
	rtl_deinit_core(hw);

fail2:
	अगर (rtlpriv->io.pci_mem_start != 0)
		pci_iounmap(pdev, (व्योम __iomem *)rtlpriv->io.pci_mem_start);

	pci_release_regions(pdev);
	complete(&rtlpriv->firmware_loading_complete);

fail1:
	अगर (hw)
		ieee80211_मुक्त_hw(hw);
	pci_disable_device(pdev);

	वापस err;
पूर्ण
EXPORT_SYMBOL(rtl_pci_probe);

व्योम rtl_pci_disconnect(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(pdev);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(pcipriv);
	काष्ठा rtl_mac *rtlmac = rtl_mac(rtlpriv);

	/* just in हाल driver is हटाओd beक्रमe firmware callback */
	रुको_क्रम_completion(&rtlpriv->firmware_loading_complete);
	clear_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status);

	/* हटाओ क्रमm debug */
	rtl_debug_हटाओ_one(hw);

	/*ieee80211_unरेजिस्टर_hw will call ops_stop */
	अगर (rtlmac->mac80211_रेजिस्टरed == 1) अणु
		ieee80211_unरेजिस्टर_hw(hw);
		rtlmac->mac80211_रेजिस्टरed = 0;
	पूर्ण अन्यथा अणु
		rtl_deinit_deferred_work(hw, false);
		rtlpriv->पूर्णांकf_ops->adapter_stop(hw);
	पूर्ण
	rtlpriv->cfg->ops->disable_पूर्णांकerrupt(hw);

	/*deinit rfसमाप्त */
	rtl_deinit_rfसमाप्त(hw);

	rtl_pci_deinit(hw);
	rtl_deinit_core(hw);
	rtlpriv->cfg->ops->deinit_sw_vars(hw);

	अगर (rtlpci->irq_alloc) अणु
		मुक्त_irq(rtlpci->pdev->irq, hw);
		rtlpci->irq_alloc = 0;
	पूर्ण

	अगर (rtlpci->using_msi)
		pci_disable_msi(rtlpci->pdev);

	list_del(&rtlpriv->list);
	अगर (rtlpriv->io.pci_mem_start != 0) अणु
		pci_iounmap(pdev, (व्योम __iomem *)rtlpriv->io.pci_mem_start);
		pci_release_regions(pdev);
	पूर्ण

	pci_disable_device(pdev);

	rtl_pci_disable_aspm(hw);

	pci_set_drvdata(pdev, शून्य);

	ieee80211_मुक्त_hw(hw);
पूर्ण
EXPORT_SYMBOL(rtl_pci_disconnect);

#अगर_घोषित CONFIG_PM_SLEEP
/***************************************
 * kernel pci घातer state define:
 * PCI_D0         ((pci_घातer_t __क्रमce) 0)
 * PCI_D1         ((pci_घातer_t __क्रमce) 1)
 * PCI_D2         ((pci_घातer_t __क्रमce) 2)
 * PCI_D3hot      ((pci_घातer_t __क्रमce) 3)
 * PCI_D3cold     ((pci_घातer_t __क्रमce) 4)
 * PCI_UNKNOWN    ((pci_घातer_t __क्रमce) 5)

 * This function is called when प्रणाली
 * goes पूर्णांकo suspend state mac80211 will
 * call rtl_mac_stop() from the mac80211
 * suspend function first, So there is
 * no need to call hw_disable here.
 ****************************************/
पूर्णांक rtl_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(dev);
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->cfg->ops->hw_suspend(hw);
	rtl_deinit_rfसमाप्त(hw);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtl_pci_suspend);

पूर्णांक rtl_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(dev);
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->cfg->ops->hw_resume(hw);
	rtl_init_rfसमाप्त(hw);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtl_pci_resume);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

स्थिर काष्ठा rtl_पूर्णांकf_ops rtl_pci_ops = अणु
	.पढ़ो_efuse_byte = पढ़ो_efuse_byte,
	.adapter_start = rtl_pci_start,
	.adapter_stop = rtl_pci_stop,
	.check_buddy_priv = rtl_pci_check_buddy_priv,
	.adapter_tx = rtl_pci_tx,
	.flush = rtl_pci_flush,
	.reset_trx_ring = rtl_pci_reset_trx_ring,
	.रुकोq_insert = rtl_pci_tx_chk_रुकोq_insert,

	.disable_aspm = rtl_pci_disable_aspm,
	.enable_aspm = rtl_pci_enable_aspm,
पूर्ण;
