<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "base.h"
#समावेश "ps.h"
#समावेश <linux/export.h>
#समावेश "btcoexist/rtl_btc.h"

bool rtl_ps_enable_nic(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));

	/*<1> reset trx ring */
	अगर (rtlhal->पूर्णांकerface == INTF_PCI)
		rtlpriv->पूर्णांकf_ops->reset_trx_ring(hw);

	अगर (is_hal_stop(rtlhal))
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Driver is already down!\n");

	/*<2> Enable Adapter */
	अगर (rtlpriv->cfg->ops->hw_init(hw))
		वापस false;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RETRY_LIMIT,
			&rtlmac->retry_दीर्घ);
	RT_CLEAR_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);

	rtlpriv->cfg->ops->चयन_channel(hw);
	rtlpriv->cfg->ops->set_channel_access(hw);
	rtlpriv->cfg->ops->set_bw_mode(hw,
			cfg80211_get_chandef_type(&hw->conf.chandef));

	/*<3> Enable Interrupt */
	rtlpriv->cfg->ops->enable_पूर्णांकerrupt(hw);

	/*<enable समयr> */
	rtl_watch_करोg_समयr_callback(&rtlpriv->works.watchकरोg_समयr);

	वापस true;
पूर्ण
EXPORT_SYMBOL(rtl_ps_enable_nic);

bool rtl_ps_disable_nic(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/*<1> Stop all समयr */
	rtl_deinit_deferred_work(hw, true);

	/*<2> Disable Interrupt */
	rtlpriv->cfg->ops->disable_पूर्णांकerrupt(hw);
	tasklet_समाप्त(&rtlpriv->works.irq_tasklet);

	/*<3> Disable Adapter */
	rtlpriv->cfg->ops->hw_disable(hw);

	वापस true;
पूर्ण
EXPORT_SYMBOL(rtl_ps_disable_nic);

अटल bool rtl_ps_set_rf_state(काष्ठा ieee80211_hw *hw,
				क्रमागत rf_pwrstate state_toset,
				u32 changesource)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool actionallowed = false;
	u16 rfरुको_cnt = 0;

	/*Only one thपढ़ो can change
	 *the RF state at one समय, and others
	 *should रुको to be executed.
	 */
	जबतक (true) अणु
		spin_lock(&rtlpriv->locks.rf_ps_lock);
		अगर (ppsc->rfchange_inprogress) अणु
			spin_unlock(&rtlpriv->locks.rf_ps_lock);

			rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
				"RF Change in progress! Wait to set..state_toset(%d).\n",
				state_toset);

			/* Set RF after the previous action is करोne.  */
			जबतक (ppsc->rfchange_inprogress) अणु
				rfरुको_cnt++;
				mdelay(1);
				/*Wait too दीर्घ, वापस false to aव्योम
				 *to be stuck here.
				 */
				अगर (rfरुको_cnt > 100)
					वापस false;
			पूर्ण
		पूर्ण अन्यथा अणु
			ppsc->rfchange_inprogress = true;
			spin_unlock(&rtlpriv->locks.rf_ps_lock);
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (state_toset) अणु
	हाल ERFON:
		ppsc->rfoff_reason &= (~changesource);

		अगर ((changesource == RF_CHANGE_BY_HW) &&
		    (ppsc->hwradiooff)) अणु
			ppsc->hwradiooff = false;
		पूर्ण

		अगर (!ppsc->rfoff_reason) अणु
			ppsc->rfoff_reason = 0;
			actionallowed = true;
		पूर्ण

		अवरोध;

	हाल ERFOFF:

		अगर ((changesource == RF_CHANGE_BY_HW) && !ppsc->hwradiooff) अणु
			ppsc->hwradiooff = true;
		पूर्ण

		ppsc->rfoff_reason |= changesource;
		actionallowed = true;
		अवरोध;

	हाल ERFSLEEP:
		ppsc->rfoff_reason |= changesource;
		actionallowed = true;
		अवरोध;

	शेष:
		pr_err("switch case %#x not processed\n", state_toset);
		अवरोध;
	पूर्ण

	अगर (actionallowed)
		rtlpriv->cfg->ops->set_rf_घातer_state(hw, state_toset);

	spin_lock(&rtlpriv->locks.rf_ps_lock);
	ppsc->rfchange_inprogress = false;
	spin_unlock(&rtlpriv->locks.rf_ps_lock);

	वापस actionallowed;
पूर्ण

अटल व्योम _rtl_ps_inactive_ps(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	ppsc->swrf_processing = true;

	अगर (ppsc->inactive_pwrstate == ERFON &&
	    rtlhal->पूर्णांकerface == INTF_PCI) अणु
		अगर ((ppsc->reg_rfps_level & RT_RF_OFF_LEVL_ASPM) &&
		    RT_IN_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM)) अणु
			rtlpriv->पूर्णांकf_ops->disable_aspm(hw);
			RT_CLEAR_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM);
		पूर्ण
	पूर्ण

	rtl_ps_set_rf_state(hw, ppsc->inactive_pwrstate,
			    RF_CHANGE_BY_IPS);

	अगर (ppsc->inactive_pwrstate == ERFOFF &&
	    rtlhal->पूर्णांकerface == INTF_PCI) अणु
		अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_ASPM &&
		    !RT_IN_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM)) अणु
			rtlpriv->पूर्णांकf_ops->enable_aspm(hw);
			RT_SET_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM);
		पूर्ण
	पूर्ण

	ppsc->swrf_processing = false;
पूर्ण

व्योम rtl_ips_nic_off_wq_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl_works *rtlworks = container_of(work, काष्ठा rtl_works,
						  ips_nic_off_wq.work);
	काष्ठा ieee80211_hw *hw = rtlworks->hw;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	क्रमागत rf_pwrstate rtstate;

	अगर (mac->opmode != NL80211_IFTYPE_STATION) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"not station return\n");
		वापस;
	पूर्ण

	अगर (mac->p2p_in_use)
		वापस;

	अगर (mac->link_state > MAC80211_NOLINK)
		वापस;

	अगर (is_hal_stop(rtlhal))
		वापस;

	अगर (rtlpriv->sec.being_setkey)
		वापस;

	अगर (rtlpriv->cfg->ops->bt_coex_off_beक्रमe_lps)
		rtlpriv->cfg->ops->bt_coex_off_beक्रमe_lps(hw);

	अगर (ppsc->inactiveps) अणु
		rtstate = ppsc->rfpwr_state;

		/*
		 *Do not enter IPS in the following conditions:
		 *(1) RF is alपढ़ोy OFF or Sleep
		 *(2) swrf_processing (indicates the IPS is still under going)
		 *(3) Connectted (only disconnected can trigger IPS)
		 *(4) IBSS (send Beacon)
		 *(5) AP mode (send Beacon)
		 *(6) monitor mode (rcv packet)
		 */

		अगर (rtstate == ERFON &&
		    !ppsc->swrf_processing &&
		    (mac->link_state == MAC80211_NOLINK) &&
		    !mac->act_scanning) अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
				"IPSEnter(): Turn off RF\n");

			ppsc->inactive_pwrstate = ERFOFF;
			ppsc->in_घातersavemode = true;

			/* call beक्रमe RF off */
			अगर (rtlpriv->cfg->ops->get_btc_status())
				rtlpriv->btcoexist.btc_ops->btc_ips_notअगरy(rtlpriv,
									ppsc->inactive_pwrstate);

			/*rtl_pci_reset_trx_ring(hw); */
			_rtl_ps_inactive_ps(hw);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl_ips_nic_off(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* because when link with ap, mac80211 will ask us
	 * to disable nic quickly after scan beक्रमe linking,
	 * this will cause link failed, so we delay 100ms here
	 */
	queue_delayed_work(rtlpriv->works.rtl_wq,
			   &rtlpriv->works.ips_nic_off_wq, MSECS(100));
पूर्ण

/* NOTICE: any opmode should exc nic_on, or disable without
 * nic_on may something wrong, like adhoc TP
 */
व्योम rtl_ips_nic_on(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	क्रमागत rf_pwrstate rtstate;

	cancel_delayed_work_sync(&rtlpriv->works.ips_nic_off_wq);

	mutex_lock(&rtlpriv->locks.ips_mutex);
	अगर (ppsc->inactiveps) अणु
		rtstate = ppsc->rfpwr_state;

		अगर (rtstate != ERFON &&
		    !ppsc->swrf_processing &&
		    ppsc->rfoff_reason <= RF_CHANGE_BY_IPS) अणु

			ppsc->inactive_pwrstate = ERFON;
			ppsc->in_घातersavemode = false;
			_rtl_ps_inactive_ps(hw);
			/* call after RF on */
			अगर (rtlpriv->cfg->ops->get_btc_status())
				rtlpriv->btcoexist.btc_ops->btc_ips_notअगरy(rtlpriv,
									ppsc->inactive_pwrstate);
		पूर्ण
	पूर्ण
	mutex_unlock(&rtlpriv->locks.ips_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_ips_nic_on);

/*क्रम FW LPS*/

/*
 *Determine अगर we can set Fw पूर्णांकo PS mode
 *in current condition.Return TRUE अगर it
 *can enter PS mode.
 */
अटल bool rtl_get_fwlps_करोze(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u32 ps_समयdअगरf;

	ps_समयdअगरf = jअगरfies_to_msecs(jअगरfies -
				       ppsc->last_delaylps_stamp_jअगरfies);

	अगर (ps_समयdअगरf < 2000) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Delay enter Fw LPS for DHCP, ARP, or EAPOL exchanging state\n");
		वापस false;
	पूर्ण

	अगर (mac->link_state != MAC80211_LINKED)
		वापस false;

	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		वापस false;

	वापस true;
पूर्ण

/* Change current and शेष preamble mode.*/
व्योम rtl_lps_set_psmode(काष्ठा ieee80211_hw *hw, u8 rt_psmode)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool enter_fwlps;

	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		वापस;

	अगर (mac->link_state != MAC80211_LINKED)
		वापस;

	अगर (ppsc->करोt11_psmode == rt_psmode && rt_psmode == EACTIVE)
		वापस;

	/* Update घातer save mode configured. */
	ppsc->करोt11_psmode = rt_psmode;

	/*
	 *<FW control LPS>
	 *1. Enter PS mode
	 *   Set RPWM to Fw to turn RF off and send H2C fw_pwrmode
	 *   cmd to set Fw पूर्णांकo PS mode.
	 *2. Leave PS mode
	 *   Send H2C fw_pwrmode cmd to Fw to set Fw पूर्णांकo Active
	 *   mode and set RPWM to turn RF on.
	 */

	अगर ((ppsc->fwctrl_lps) && ppsc->report_linked) अणु
		अगर (ppsc->करोt11_psmode == EACTIVE) अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
				"FW LPS leave ps_mode:%x\n",
				FW_PS_ACTIVE_MODE);
			enter_fwlps = false;
			ppsc->pwr_mode = FW_PS_ACTIVE_MODE;
			ppsc->smart_ps = 0;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_LPS_ACTION,
						      (u8 *)(&enter_fwlps));
			अगर (ppsc->p2p_ps_info.opp_ps)
				rtl_p2p_ps_cmd(hw , P2P_PS_ENABLE);

			अगर (rtlpriv->cfg->ops->get_btc_status())
				rtlpriv->btcoexist.btc_ops->btc_lps_notअगरy(rtlpriv, rt_psmode);
		पूर्ण अन्यथा अणु
			अगर (rtl_get_fwlps_करोze(hw)) अणु
				rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
					"FW LPS enter ps_mode:%x\n",
					ppsc->fwctrl_psmode);
				अगर (rtlpriv->cfg->ops->get_btc_status())
					rtlpriv->btcoexist.btc_ops->btc_lps_notअगरy(rtlpriv, rt_psmode);
				enter_fwlps = true;
				ppsc->pwr_mode = ppsc->fwctrl_psmode;
				ppsc->smart_ps = 2;
				rtlpriv->cfg->ops->set_hw_reg(hw,
							HW_VAR_FW_LPS_ACTION,
							(u8 *)(&enter_fwlps));

			पूर्ण अन्यथा अणु
				/* Reset the घातer save related parameters. */
				ppsc->करोt11_psmode = EACTIVE;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Interrupt safe routine to enter the leisure घातer save mode.*/
अटल व्योम rtl_lps_enter_core(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (!ppsc->fwctrl_lps)
		वापस;

	अगर (rtlpriv->sec.being_setkey)
		वापस;

	अगर (rtlpriv->link_info.busytraffic)
		वापस;

	/*sleep after linked 10s, to let DHCP and 4-way handshake ok enough!! */
	अगर (mac->cnt_after_linked < 5)
		वापस;

	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		वापस;

	अगर (mac->link_state != MAC80211_LINKED)
		वापस;

	mutex_lock(&rtlpriv->locks.lps_mutex);

	/* Don't need to check (ppsc->करोt11_psmode == EACTIVE), because
	 * bt_ccoexist may ask to enter lps.
	 * In normal हाल, this स्थिरraपूर्णांक move to rtl_lps_set_psmode().
	 */
	rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
		"Enter 802.11 power save mode...\n");
	rtl_lps_set_psmode(hw, EAUTOPS);

	mutex_unlock(&rtlpriv->locks.lps_mutex);
पूर्ण

/* Interrupt safe routine to leave the leisure घातer save mode.*/
अटल व्योम rtl_lps_leave_core(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	mutex_lock(&rtlpriv->locks.lps_mutex);

	अगर (ppsc->fwctrl_lps) अणु
		अगर (ppsc->करोt11_psmode != EACTIVE) अणु

			/*FIX ME */
			/*rtlpriv->cfg->ops->enable_पूर्णांकerrupt(hw); */

			अगर (ppsc->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM &&
			    RT_IN_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM) &&
			    rtlhal->पूर्णांकerface == INTF_PCI) अणु
				rtlpriv->पूर्णांकf_ops->disable_aspm(hw);
				RT_CLEAR_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM);
			पूर्ण

			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"Busy Traffic,Leave 802.11 power save..\n");

			rtl_lps_set_psmode(hw, EACTIVE);
		पूर्ण
	पूर्ण
	mutex_unlock(&rtlpriv->locks.lps_mutex);
पूर्ण

/* For sw LPS*/
व्योम rtl_swlps_beacon(काष्ठा ieee80211_hw *hw, व्योम *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr = data;
	काष्ठा ieee80211_tim_ie *tim_ie;
	u8 *tim;
	u8 tim_len;
	bool u_buffed;
	bool m_buffed;

	अगर (mac->opmode != NL80211_IFTYPE_STATION)
		वापस;

	अगर (!rtlpriv->psc.swctrl_lps)
		वापस;

	अगर (rtlpriv->mac80211.link_state != MAC80211_LINKED)
		वापस;

	अगर (!rtlpriv->psc.sw_ps_enabled)
		वापस;

	अगर (rtlpriv->psc.fwctrl_lps)
		वापस;

	अगर (likely(!(hw->conf.flags & IEEE80211_CONF_PS)))
		वापस;

	/* check अगर this really is a beacon */
	अगर (!ieee80211_is_beacon(hdr->frame_control))
		वापस;

	/* min. beacon length + FCS_LEN */
	अगर (len <= 40 + FCS_LEN)
		वापस;

	/* and only beacons from the associated BSSID, please */
	अगर (!ether_addr_equal_64bits(hdr->addr3, rtlpriv->mac80211.bssid))
		वापस;

	rtlpriv->psc.last_beacon = jअगरfies;

	tim = rtl_find_ie(data, len - FCS_LEN, WLAN_EID_TIM);
	अगर (!tim)
		वापस;

	अगर (tim[1] < माप(*tim_ie))
		वापस;

	tim_len = tim[1];
	tim_ie = (काष्ठा ieee80211_tim_ie *) &tim[2];

	अगर (!WARN_ON_ONCE(!hw->conf.ps_dtim_period))
		rtlpriv->psc.dtim_counter = tim_ie->dtim_count;

	/* Check whenever the PHY can be turned off again. */

	/* 1. What about buffered unicast traffic क्रम our AID? */
	u_buffed = ieee80211_check_tim(tim_ie, tim_len,
				       rtlpriv->mac80211.assoc_id);

	/* 2. Maybe the AP wants to send multicast/broadcast data? */
	m_buffed = tim_ie->biपंचांगap_ctrl & 0x01;
	rtlpriv->psc.multi_buffered = m_buffed;

	/* unicast will process by mac80211 through
	 * set ~IEEE80211_CONF_PS, So we just check
	 * multicast frames here */
	अगर (!m_buffed) अणु
		/* back to low-घातer land. and delay is
		 * prevent null घातer save frame tx fail */
		queue_delayed_work(rtlpriv->works.rtl_wq,
				   &rtlpriv->works.ps_work, MSECS(5));
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"u_bufferd: %x, m_buffered: %x\n", u_buffed, m_buffed);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rtl_swlps_beacon);

व्योम rtl_swlps_rf_awake(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	अगर (!rtlpriv->psc.swctrl_lps)
		वापस;
	अगर (mac->link_state != MAC80211_LINKED)
		वापस;

	अगर (ppsc->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM &&
	    RT_IN_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM)) अणु
		rtlpriv->पूर्णांकf_ops->disable_aspm(hw);
		RT_CLEAR_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM);
	पूर्ण

	mutex_lock(&rtlpriv->locks.lps_mutex);
	rtl_ps_set_rf_state(hw, ERFON, RF_CHANGE_BY_PS);
	mutex_unlock(&rtlpriv->locks.lps_mutex);
पूर्ण

व्योम rtl_swlps_rfon_wq_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl_works *rtlworks = container_of(work, काष्ठा rtl_works,
						  ps_rfon_wq.work);
	काष्ठा ieee80211_hw *hw = rtlworks->hw;

	rtl_swlps_rf_awake(hw);
पूर्ण

व्योम rtl_swlps_rf_sleep(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 sleep_पूर्णांकv;

	अगर (!rtlpriv->psc.sw_ps_enabled)
		वापस;

	अगर ((rtlpriv->sec.being_setkey) ||
	    (mac->opmode == NL80211_IFTYPE_ADHOC))
		वापस;

	/*sleep after linked 10s, to let DHCP and 4-way handshake ok enough!! */
	अगर ((mac->link_state != MAC80211_LINKED) || (mac->cnt_after_linked < 5))
		वापस;

	अगर (rtlpriv->link_info.busytraffic)
		वापस;

	spin_lock(&rtlpriv->locks.rf_ps_lock);
	अगर (rtlpriv->psc.rfchange_inprogress) अणु
		spin_unlock(&rtlpriv->locks.rf_ps_lock);
		वापस;
	पूर्ण
	spin_unlock(&rtlpriv->locks.rf_ps_lock);

	mutex_lock(&rtlpriv->locks.lps_mutex);
	rtl_ps_set_rf_state(hw, ERFSLEEP, RF_CHANGE_BY_PS);
	mutex_unlock(&rtlpriv->locks.lps_mutex);

	अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_ASPM &&
	    !RT_IN_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM)) अणु
		rtlpriv->पूर्णांकf_ops->enable_aspm(hw);
		RT_SET_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM);
	पूर्ण

	/* here is घातer save alg, when this beacon is DTIM
	 * we will set sleep समय to dtim_period * n;
	 * when this beacon is not DTIM, we will set sleep
	 * समय to sleep_पूर्णांकv = rtlpriv->psc.dtim_counter or
	 * MAX_SW_LPS_SLEEP_INTV(शेष set to 5) */

	अगर (rtlpriv->psc.dtim_counter == 0) अणु
		अगर (hw->conf.ps_dtim_period == 1)
			sleep_पूर्णांकv = hw->conf.ps_dtim_period * 2;
		अन्यथा
			sleep_पूर्णांकv = hw->conf.ps_dtim_period;
	पूर्ण अन्यथा अणु
		sleep_पूर्णांकv = rtlpriv->psc.dtim_counter;
	पूर्ण

	अगर (sleep_पूर्णांकv > MAX_SW_LPS_SLEEP_INTV)
		sleep_पूर्णांकv = MAX_SW_LPS_SLEEP_INTV;

	/* this prपूर्णांक should always be dtim_conter = 0 &
	 * sleep  = dtim_period, that meaons, we should
	 * awake beक्रमe every dtim */
	rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
		"dtim_counter:%x will sleep :%d beacon_intv\n",
		rtlpriv->psc.dtim_counter, sleep_पूर्णांकv);

	/* we tested that 40ms is enough क्रम sw & hw sw delay */
	queue_delayed_work(rtlpriv->works.rtl_wq, &rtlpriv->works.ps_rfon_wq,
			MSECS(sleep_पूर्णांकv * mac->vअगर->bss_conf.beacon_पूर्णांक - 40));
पूर्ण

व्योम rtl_lps_change_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl_works *rtlworks =
	    container_of(work, काष्ठा rtl_works, lps_change_work);
	काष्ठा ieee80211_hw *hw = rtlworks->hw;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->enter_ps)
		rtl_lps_enter_core(hw);
	अन्यथा
		rtl_lps_leave_core(hw);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_lps_change_work_callback);

व्योम rtl_lps_enter(काष्ठा ieee80211_hw *hw, bool may_block)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (may_block)
		वापस rtl_lps_enter_core(hw);
	rtlpriv->enter_ps = true;
	schedule_work(&rtlpriv->works.lps_change_work);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_lps_enter);

व्योम rtl_lps_leave(काष्ठा ieee80211_hw *hw, bool may_block)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (may_block)
		वापस rtl_lps_leave_core(hw);
	rtlpriv->enter_ps = false;
	schedule_work(&rtlpriv->works.lps_change_work);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_lps_leave);

व्योम rtl_swlps_wq_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl_works *rtlworks = container_of(work, काष्ठा rtl_works,
						  ps_work.work);
	काष्ठा ieee80211_hw *hw = rtlworks->hw;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool ps = false;

	ps = (hw->conf.flags & IEEE80211_CONF_PS);

	/* we can sleep after ps null send ok */
	अगर (rtlpriv->psc.state_inap) अणु
		rtl_swlps_rf_sleep(hw);

		अगर (rtlpriv->psc.state && !ps) अणु
			rtlpriv->psc.sleep_ms = jअगरfies_to_msecs(jअगरfies -
						 rtlpriv->psc.last_action);
		पूर्ण

		अगर (ps)
			rtlpriv->psc.last_slept = jअगरfies;

		rtlpriv->psc.last_action = jअगरfies;
		rtlpriv->psc.state = ps;
	पूर्ण
पूर्ण

अटल व्योम rtl_p2p_noa_ie(काष्ठा ieee80211_hw *hw, व्योम *data,
			   अचिन्हित पूर्णांक len)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_mgmt *mgmt = data;
	काष्ठा rtl_p2p_ps_info *p2pinfo = &(rtlpriv->psc.p2p_ps_info);
	u8 *pos, *end, *ie;
	u16 noa_len;
	अटल u8 p2p_oui_ie_type[4] = अणु0x50, 0x6f, 0x9a, 0x09पूर्ण;
	u8 noa_num, index , i, noa_index = 0;
	bool find_p2p_ie = false , find_p2p_ps_ie = false;

	pos = (u8 *)mgmt->u.beacon.variable;
	end = data + len;
	ie = शून्य;

	जबतक (pos + 1 < end) अणु
		अगर (pos + 2 + pos[1] > end)
			वापस;

		अगर (pos[0] == 221 && pos[1] > 4) अणु
			अगर (स_भेद(&pos[2], p2p_oui_ie_type, 4) == 0) अणु
				ie = pos + 2+4;
				अवरोध;
			पूर्ण
		पूर्ण
		pos += 2 + pos[1];
	पूर्ण

	अगर (ie == शून्य)
		वापस;
	find_p2p_ie = true;
	/*to find noa ie*/
	जबतक (ie + 1 < end) अणु
		noa_len = le16_to_cpu(*((__le16 *)&ie[1]));
		अगर (ie + 3 + ie[1] > end)
			वापस;

		अगर (ie[0] == 12) अणु
			find_p2p_ps_ie = true;
			अगर ((noa_len - 2) % 13 != 0) अणु
				rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
					"P2P notice of absence: invalid length.%d\n",
					noa_len);
				वापस;
			पूर्ण अन्यथा अणु
				noa_num = (noa_len - 2) / 13;
				अगर (noa_num > P2P_MAX_NOA_NUM)
					noa_num = P2P_MAX_NOA_NUM;

			पूर्ण
			noa_index = ie[3];
			अगर (rtlpriv->psc.p2p_ps_info.p2p_ps_mode ==
			    P2P_PS_NONE || noa_index != p2pinfo->noa_index) अणु
				rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD,
					"update NOA ie.\n");
				p2pinfo->noa_index = noa_index;
				p2pinfo->opp_ps = (ie[4] >> 7);
				p2pinfo->ctwinकरोw = ie[4] & 0x7F;
				p2pinfo->noa_num = noa_num;
				index = 5;
				क्रम (i = 0; i < noa_num; i++) अणु
					p2pinfo->noa_count_type[i] =
					 *(u8 *)(ie + index);
					index += 1;
					p2pinfo->noa_duration[i] =
					 le32_to_cpu(*(__le32 *)(ie + index));
					index += 4;
					p2pinfo->noa_पूर्णांकerval[i] =
					 le32_to_cpu(*(__le32 *)(ie + index));
					index += 4;
					p2pinfo->noa_start_समय[i] =
					 le32_to_cpu(*(__le32 *)(ie + index));
					index += 4;
				पूर्ण

				अगर (p2pinfo->opp_ps == 1) अणु
					p2pinfo->p2p_ps_mode = P2P_PS_CTWINDOW;
					/* Driver should रुको LPS entering
					 * CTWinकरोw
					 */
					अगर (rtlpriv->psc.fw_current_inpsmode)
						rtl_p2p_ps_cmd(hw,
							       P2P_PS_ENABLE);
				पूर्ण अन्यथा अगर (p2pinfo->noa_num > 0) अणु
					p2pinfo->p2p_ps_mode = P2P_PS_NOA;
					rtl_p2p_ps_cmd(hw, P2P_PS_ENABLE);
				पूर्ण अन्यथा अगर (p2pinfo->p2p_ps_mode > P2P_PS_NONE) अणु
					rtl_p2p_ps_cmd(hw, P2P_PS_DISABLE);
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
		ie += 3 + noa_len;
	पूर्ण

	अगर (find_p2p_ie) अणु
		अगर ((p2pinfo->p2p_ps_mode > P2P_PS_NONE) &&
		    (!find_p2p_ps_ie))
			rtl_p2p_ps_cmd(hw, P2P_PS_DISABLE);
	पूर्ण
पूर्ण

अटल व्योम rtl_p2p_action_ie(काष्ठा ieee80211_hw *hw, व्योम *data,
			      अचिन्हित पूर्णांक len)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_mgmt *mgmt = data;
	काष्ठा rtl_p2p_ps_info *p2pinfo = &(rtlpriv->psc.p2p_ps_info);
	u8 noa_num, index , i , noa_index = 0;
	u8 *pos, *end, *ie;
	u16 noa_len;
	अटल u8 p2p_oui_ie_type[4] = अणु0x50, 0x6f, 0x9a, 0x09पूर्ण;

	pos = (u8 *)&mgmt->u.action.category;
	end = data + len;
	ie = शून्य;

	अगर (pos[0] == 0x7f) अणु
		अगर (स_भेद(&pos[1], p2p_oui_ie_type, 4) == 0)
			ie = pos + 3+4;
	पूर्ण

	अगर (ie == शून्य)
		वापस;

	rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "action frame find P2P IE.\n");
	/*to find noa ie*/
	जबतक (ie + 1 < end) अणु
		noa_len = le16_to_cpu(*(__le16 *)&ie[1]);
		अगर (ie + 3 + ie[1] > end)
			वापस;

		अगर (ie[0] == 12) अणु
			rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "find NOA IE.\n");
			RT_PRINT_DATA(rtlpriv, COMP_FW, DBG_LOUD, "noa ie ",
				      ie, noa_len);
			अगर ((noa_len - 2) % 13 != 0) अणु
				rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD,
					"P2P notice of absence: invalid length.%d\n",
					noa_len);
				वापस;
			पूर्ण अन्यथा अणु
				noa_num = (noa_len - 2) / 13;
				अगर (noa_num > P2P_MAX_NOA_NUM)
					noa_num = P2P_MAX_NOA_NUM;

			पूर्ण
			noa_index = ie[3];
			अगर (rtlpriv->psc.p2p_ps_info.p2p_ps_mode ==
			    P2P_PS_NONE || noa_index != p2pinfo->noa_index) अणु
				p2pinfo->noa_index = noa_index;
				p2pinfo->opp_ps = (ie[4] >> 7);
				p2pinfo->ctwinकरोw = ie[4] & 0x7F;
				p2pinfo->noa_num = noa_num;
				index = 5;
				क्रम (i = 0; i < noa_num; i++) अणु
					p2pinfo->noa_count_type[i] =
					 *(u8 *)(ie + index);
					index += 1;
					p2pinfo->noa_duration[i] =
					 le32_to_cpu(*(__le32 *)(ie + index));
					index += 4;
					p2pinfo->noa_पूर्णांकerval[i] =
					 le32_to_cpu(*(__le32 *)(ie + index));
					index += 4;
					p2pinfo->noa_start_समय[i] =
					 le32_to_cpu(*(__le32 *)(ie + index));
					index += 4;
				पूर्ण

				अगर (p2pinfo->opp_ps == 1) अणु
					p2pinfo->p2p_ps_mode = P2P_PS_CTWINDOW;
					/* Driver should रुको LPS entering
					 * CTWinकरोw
					 */
					अगर (rtlpriv->psc.fw_current_inpsmode)
						rtl_p2p_ps_cmd(hw,
							       P2P_PS_ENABLE);
				पूर्ण अन्यथा अगर (p2pinfo->noa_num > 0) अणु
					p2pinfo->p2p_ps_mode = P2P_PS_NOA;
					rtl_p2p_ps_cmd(hw, P2P_PS_ENABLE);
				पूर्ण अन्यथा अगर (p2pinfo->p2p_ps_mode > P2P_PS_NONE) अणु
					rtl_p2p_ps_cmd(hw, P2P_PS_DISABLE);
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
		ie += 3 + noa_len;
	पूर्ण
पूर्ण

व्योम rtl_p2p_ps_cmd(काष्ठा ieee80211_hw *hw , u8 p2p_ps_state)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *rtlps = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_p2p_ps_info  *p2pinfo = &(rtlpriv->psc.p2p_ps_info);

	rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, " p2p state %x\n", p2p_ps_state);
	चयन (p2p_ps_state) अणु
	हाल P2P_PS_DISABLE:
		p2pinfo->p2p_ps_state = p2p_ps_state;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_P2P_PS_OFFLOAD,
					      &p2p_ps_state);
		p2pinfo->noa_index = 0;
		p2pinfo->ctwinकरोw = 0;
		p2pinfo->opp_ps = 0;
		p2pinfo->noa_num = 0;
		p2pinfo->p2p_ps_mode = P2P_PS_NONE;
		अगर (rtlps->fw_current_inpsmode) अणु
			अगर (rtlps->smart_ps == 0) अणु
				rtlps->smart_ps = 2;
				rtlpriv->cfg->ops->set_hw_reg(hw,
					 HW_VAR_H2C_FW_PWRMODE,
					 &rtlps->pwr_mode);
			पूर्ण

		पूर्ण
		अवरोध;
	हाल P2P_PS_ENABLE:
		अगर (p2pinfo->p2p_ps_mode > P2P_PS_NONE) अणु
			p2pinfo->p2p_ps_state = p2p_ps_state;

			अगर (p2pinfo->ctwinकरोw > 0) अणु
				अगर (rtlps->smart_ps != 0) अणु
					rtlps->smart_ps = 0;
					rtlpriv->cfg->ops->set_hw_reg(hw,
						 HW_VAR_H2C_FW_PWRMODE,
						 &rtlps->pwr_mode);
				पूर्ण
			पूर्ण
			rtlpriv->cfg->ops->set_hw_reg(hw,
				 HW_VAR_H2C_FW_P2P_PS_OFFLOAD,
				 &p2p_ps_state);

		पूर्ण
		अवरोध;
	हाल P2P_PS_SCAN:
	हाल P2P_PS_SCAN_DONE:
	हाल P2P_PS_ALLSTASLEEP:
		अगर (p2pinfo->p2p_ps_mode > P2P_PS_NONE) अणु
			p2pinfo->p2p_ps_state = p2p_ps_state;
			rtlpriv->cfg->ops->set_hw_reg(hw,
				 HW_VAR_H2C_FW_P2P_PS_OFFLOAD,
				 &p2p_ps_state);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD,
		"ctwindow %x oppps %x\n",
		p2pinfo->ctwinकरोw, p2pinfo->opp_ps);
	rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD,
		"count %x duration %x index %x interval %x start time %x noa num %x\n",
		p2pinfo->noa_count_type[0],
		p2pinfo->noa_duration[0],
		p2pinfo->noa_index,
		p2pinfo->noa_पूर्णांकerval[0],
		p2pinfo->noa_start_समय[0],
		p2pinfo->noa_num);
	rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "end\n");
पूर्ण

व्योम rtl_p2p_info(काष्ठा ieee80211_hw *hw, व्योम *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr = data;

	अगर (!mac->p2p)
		वापस;
	अगर (mac->link_state != MAC80211_LINKED)
		वापस;
	/* min. beacon length + FCS_LEN */
	अगर (len <= 40 + FCS_LEN)
		वापस;

	/* and only beacons from the associated BSSID, please */
	अगर (!ether_addr_equal_64bits(hdr->addr3, rtlpriv->mac80211.bssid))
		वापस;

	/* check अगर this really is a beacon */
	अगर (!(ieee80211_is_beacon(hdr->frame_control) ||
	      ieee80211_is_probe_resp(hdr->frame_control) ||
	      ieee80211_is_action(hdr->frame_control)))
		वापस;

	अगर (ieee80211_is_action(hdr->frame_control))
		rtl_p2p_action_ie(hw , data , len - FCS_LEN);
	अन्यथा
		rtl_p2p_noa_ie(hw , data , len - FCS_LEN);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_p2p_info);
