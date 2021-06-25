<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _OS_INTFS_C_

#समावेश <osdep_service.h>
#समावेश <osdep_पूर्णांकf.h>
#समावेश <drv_types.h>
#समावेश <xmit_osdep.h>
#समावेश <recv_osdep.h>
#समावेश <hal_पूर्णांकf.h>
#समावेश <rtw_ioctl.h>
#समावेश <rtl8188e_hal.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Realtek Wireless Lan Driver");
MODULE_AUTHOR("Realtek Semiconductor Corp.");
MODULE_VERSION(DRIVERVERSION);
MODULE_FIRMWARE("rtlwifi/rtl8188eufw.bin");

#घोषणा RTW_NOTCH_FILTER 0 /* 0:Disable, 1:Enable, */

/* module param शेषs */
/* Ndis802_11Infraकाष्ठाure; infra, ad-hoc, स्वतः */
अटल पूर्णांक rtw_channel = 1;/* ad-hoc support requirement */
अटल पूर्णांक rtw_wireless_mode = WIRELESS_11BG_24N;
अटल पूर्णांक rtw_vrtl_carrier_sense = AUTO_VCS;
अटल पूर्णांक rtw_vcs_type = RTS_CTS;/*  */
अटल पूर्णांक rtw_rts_thresh = 2347;/*  */
अटल पूर्णांक rtw_frag_thresh = 2346;/*  */
अटल पूर्णांक rtw_preamble = PREAMBLE_LONG;/* दीर्घ, लघु, स्वतः */
अटल पूर्णांक rtw_घातer_mgnt = 1;
अटल पूर्णांक rtw_ips_mode = IPS_NORMAL;

अटल पूर्णांक rtw_smart_ps = 2;

module_param(rtw_ips_mode, पूर्णांक, 0644);
MODULE_PARM_DESC(rtw_ips_mode, "The default IPS mode");

अटल पूर्णांक rtw_debug = 1;

अटल पूर्णांक rtw_acm_method;/*  0:By SW 1:By HW. */

अटल पूर्णांक rtw_wmm_enable = 1;/*  शेष is set to enable the wmm. */
अटल पूर्णांक rtw_uapsd_enable;

अटल पूर्णांक rtw_ht_enable = 1;
/* 0 :disable, bit(0): enable 2.4g, bit(1): enable 5g */
अटल पूर्णांक rtw_cbw40_enable = 3;
अटल पूर्णांक rtw_ampdu_enable = 1;/* क्रम enable tx_ampdu */

/* 0: disable
 * bit(0):enable 2.4g
 * bit(1):enable 5g
 * शेष is set to enable 2.4GHZ क्रम IOT issue with bufflao's AP at 5GHZ
 */
अटल पूर्णांक rtw_rx_stbc = 1;
अटल पूर्णांक rtw_ampdu_amsdu;/*  0: disabled, 1:enabled, 2:स्वतः */

अटल पूर्णांक rtw_wअगरi_spec;
अटल पूर्णांक rtw_channel_plan = RT_CHANNEL_DOMAIN_MAX;

अटल पूर्णांक rtw_antभाग_cfg = 2; /*  0:OFF , 1:ON, 2:decide by Efuse config */

/* 0: decide by efuse
 * 1: क्रम 88EE, 1Tx and 1RxCG are भागersity (2 Ant with SPDT)
 * 2: क्रम 88EE, 1Tx and 2Rx are भागersity (2 Ant, Tx and RxCG are both on aux
 *    port, RxCS is on मुख्य port)
 * 3: क्रम 88EE, 1Tx and 1RxCG are fixed (1Ant, Tx and RxCG are both on aux port)
 */
अटल पूर्णांक rtw_antभाग_प्रकारype;

अटल पूर्णांक rtw_enusbss;/* 0:disable, 1:enable */

अटल पूर्णांक rtw_hwpdn_mode = 2;/* 0:disable, 1:enable, 2: by EFUSE config */

पूर्णांक rtw_mc2u_disable;

अटल पूर्णांक rtw_80211d;

अटल अक्षर *अगरname = "wlan%d";
module_param(अगरname, अक्षरp, 0644);
MODULE_PARM_DESC(अगरname, "The default name to allocate for first interface");

अटल अक्षर *अगर2name = "wlan%d";
module_param(अगर2name, अक्षरp, 0644);
MODULE_PARM_DESC(अगर2name, "The default name to allocate for second interface");

/* temp mac address अगर users want to use instead of the mac address in Efuse */
अक्षर *rtw_iniपंचांगac;

module_param(rtw_iniपंचांगac, अक्षरp, 0644);
module_param(rtw_channel_plan, पूर्णांक, 0644);
module_param(rtw_channel, पूर्णांक, 0644);
module_param(rtw_wmm_enable, पूर्णांक, 0644);
module_param(rtw_vrtl_carrier_sense, पूर्णांक, 0644);
module_param(rtw_vcs_type, पूर्णांक, 0644);
module_param(rtw_ht_enable, पूर्णांक, 0644);
module_param(rtw_cbw40_enable, पूर्णांक, 0644);
module_param(rtw_ampdu_enable, पूर्णांक, 0644);
module_param(rtw_rx_stbc, पूर्णांक, 0644);
module_param(rtw_ampdu_amsdu, पूर्णांक, 0644);
module_param(rtw_घातer_mgnt, पूर्णांक, 0644);
module_param(rtw_smart_ps, पूर्णांक, 0644);
module_param(rtw_wअगरi_spec, पूर्णांक, 0644);
module_param(rtw_antभाग_cfg, पूर्णांक, 0644);
module_param(rtw_antभाग_प्रकारype, पूर्णांक, 0644);
module_param(rtw_enusbss, पूर्णांक, 0644);
module_param(rtw_hwpdn_mode, पूर्णांक, 0644);

अटल uपूर्णांक rtw_max_roaming_बार = 2;
module_param(rtw_max_roaming_बार, uपूर्णांक, 0644);
MODULE_PARM_DESC(rtw_max_roaming_बार, "The max roaming times to try");

अटल पूर्णांक rtw_fw_iol = 1;/*  0:Disable, 1:enable, 2:by usb speed */
module_param(rtw_fw_iol, पूर्णांक, 0644);
MODULE_PARM_DESC(rtw_fw_iol, "FW IOL");

module_param(rtw_mc2u_disable, पूर्णांक, 0644);

module_param(rtw_80211d, पूर्णांक, 0644);
MODULE_PARM_DESC(rtw_80211d, "Enable 802.11d mechanism");

अटल uपूर्णांक rtw_notch_filter = RTW_NOTCH_FILTER;
module_param(rtw_notch_filter, uपूर्णांक, 0644);
MODULE_PARM_DESC(rtw_notch_filter, "0:Disable, 1:Enable, 2:Enable only for P2P");
module_param_named(debug, rtw_debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "Set debug level (1-9) (default 1)");

अटल bool rtw_monitor_enable;
module_param_named(monitor_enable, rtw_monitor_enable, bool, 0444);
MODULE_PARM_DESC(monitor_enable, "Enable monitor interface (default: false)");

अटल पूर्णांक netdev_बंद(काष्ठा net_device *pnetdev);

अटल व्योम loadparam(काष्ठा adapter *padapter, काष्ठा net_device *pnetdev)
अणु
	काष्ठा registry_priv *registry_par = &padapter->registrypriv;

	GlobalDebugLevel = rtw_debug;

	स_नकल(registry_par->ssid.ssid, "ANY", 3);
	registry_par->ssid.ssid_length = 3;

	registry_par->channel = (u8)rtw_channel;
	registry_par->wireless_mode = (u8)rtw_wireless_mode;
	registry_par->vrtl_carrier_sense = (u8)rtw_vrtl_carrier_sense;
	registry_par->vcs_type = (u8)rtw_vcs_type;
	registry_par->rts_thresh = (u16)rtw_rts_thresh;
	registry_par->frag_thresh = (u16)rtw_frag_thresh;
	registry_par->preamble = (u8)rtw_preamble;
	registry_par->smart_ps =  (u8)rtw_smart_ps;
	registry_par->घातer_mgnt = (u8)rtw_घातer_mgnt;
	registry_par->ips_mode = (u8)rtw_ips_mode;
	registry_par->mp_mode = 0;
	registry_par->acm_method = (u8)rtw_acm_method;

	 /* UAPSD */
	registry_par->wmm_enable = (u8)rtw_wmm_enable;
	registry_par->uapsd_enable = (u8)rtw_uapsd_enable;

	registry_par->ht_enable = (u8)rtw_ht_enable;
	registry_par->cbw40_enable = (u8)rtw_cbw40_enable;
	registry_par->ampdu_enable = (u8)rtw_ampdu_enable;
	registry_par->rx_stbc = (u8)rtw_rx_stbc;
	registry_par->ampdu_amsdu = (u8)rtw_ampdu_amsdu;
	registry_par->wअगरi_spec = (u8)rtw_wअगरi_spec;
	registry_par->channel_plan = (u8)rtw_channel_plan;
	registry_par->accept_addba_req = true;
	registry_par->antभाग_cfg = (u8)rtw_antभाग_cfg;
	registry_par->antभाग_प्रकारype = (u8)rtw_antभाग_प्रकारype;
	registry_par->hwpdn_mode = (u8)rtw_hwpdn_mode;

	registry_par->max_roaming_बार = (u8)rtw_max_roaming_बार;

	registry_par->fw_iol = rtw_fw_iol;

	registry_par->enable80211d = (u8)rtw_80211d;
	snम_लिखो(registry_par->अगरname, 16, "%s", अगरname);
	snम_लिखो(registry_par->अगर2name, 16, "%s", अगर2name);
	registry_par->notch_filter = (u8)rtw_notch_filter;
	registry_par->monitor_enable = rtw_monitor_enable;
पूर्ण

अटल पूर्णांक rtw_net_set_mac_address(काष्ठा net_device *pnetdev, व्योम *p)
अणु
	काष्ठा adapter *padapter = netdev_priv(pnetdev);
	काष्ठा sockaddr *addr = p;

	अगर (!padapter->bup)
		स_नकल(padapter->eeprompriv.mac_addr, addr->sa_data, ETH_ALEN);

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *rtw_net_get_stats(काष्ठा net_device *pnetdev)
अणु
	काष्ठा adapter *padapter = netdev_priv(pnetdev);
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;

	padapter->stats.tx_packets = pxmitpriv->tx_pkts;
	padapter->stats.rx_packets = precvpriv->rx_pkts;
	padapter->stats.tx_dropped = pxmitpriv->tx_drop;
	padapter->stats.rx_dropped = precvpriv->rx_drop;
	padapter->stats.tx_bytes = pxmitpriv->tx_bytes;
	padapter->stats.rx_bytes = precvpriv->rx_bytes;
	वापस &padapter->stats;
पूर्ण

/*
 * AC to queue mapping
 *
 * AC_VO -> queue 0
 * AC_VI -> queue 1
 * AC_BE -> queue 2
 * AC_BK -> queue 3
 */
अटल स्थिर u16 rtw_1d_to_queue[8] = अणु 2, 3, 3, 2, 1, 1, 0, 0 पूर्ण;

/* Given a data frame determine the 802.1p/1d tag to use. */
अटल अचिन्हित पूर्णांक rtw_classअगरy8021d(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक dscp;

	/* skb->priority values from 256->263 are magic values to
	 * directly indicate a specअगरic 802.1d priority.  This is used
	 * to allow 802.1d priority to be passed directly in from VLAN
	 * tags, etc.
	 */
	अगर (skb->priority >= 256 && skb->priority <= 263)
		वापस skb->priority - 256;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		dscp = ip_hdr(skb)->tos & 0xfc;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस dscp >> 5;
पूर्ण

अटल u16 rtw_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			    काष्ठा net_device *sb_dev)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	skb->priority = rtw_classअगरy8021d(skb);

	अगर (pmlmepriv->acm_mask != 0)
		skb->priority = qos_acm(pmlmepriv->acm_mask, skb->priority);

	वापस rtw_1d_to_queue[skb->priority];
पूर्ण

u16 rtw_recv_select_queue(काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *piphdr;
	अचिन्हित पूर्णांक dscp;
	__be16 eth_type;
	u32 priority;
	u8 *pdata = skb->data;

	स_नकल(&eth_type, pdata + (ETH_ALEN << 1), 2);

	चयन (eth_type) अणु
	हाल htons(ETH_P_IP):
		piphdr = (काष्ठा iphdr *)(pdata + ETH_HLEN);
		dscp = piphdr->tos & 0xfc;
		priority = dscp >> 5;
		अवरोध;
	शेष:
		priority = 0;
	पूर्ण

	वापस rtw_1d_to_queue[priority];
पूर्ण

अटल स्थिर काष्ठा net_device_ops rtw_netdev_ops = अणु
	.nकरो_खोलो = netdev_खोलो,
	.nकरो_stop = netdev_बंद,
	.nकरो_start_xmit = rtw_xmit_entry,
	.nकरो_select_queue = rtw_select_queue,
	.nकरो_set_mac_address = rtw_net_set_mac_address,
	.nकरो_get_stats = rtw_net_get_stats,
	.nकरो_करो_ioctl = rtw_ioctl,
पूर्ण;

अटल स्थिर काष्ठा device_type wlan_type = अणु
	.name = "wlan",
पूर्ण;

काष्ठा net_device *rtw_init_netdev(व्योम)
अणु
	काष्ठा adapter *padapter;
	काष्ठा net_device *pnetdev;

	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("+init_net_dev\n"));

	pnetdev = alloc_etherdev_mq(माप(काष्ठा adapter), 4);
	अगर (!pnetdev)
		वापस शून्य;

	pnetdev->dev.type = &wlan_type;
	padapter = netdev_priv(pnetdev);
	padapter->pnetdev = pnetdev;
	DBG_88E("register rtw_netdev_ops to netdev_ops\n");
	pnetdev->netdev_ops = &rtw_netdev_ops;
	pnetdev->watchकरोg_समयo = HZ * 3; /* 3 second समयout */
	pnetdev->wireless_handlers = (काष्ठा iw_handler_def *)&rtw_handlers_def;

	loadparam(padapter, pnetdev);

	वापस pnetdev;
पूर्ण

अटल पूर्णांक rtw_start_drv_thपढ़ोs(काष्ठा adapter *padapter)
अणु
	पूर्णांक err = 0;

	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("+%s\n", __func__));

	padapter->cmdThपढ़ो = kthपढ़ो_run(rtw_cmd_thपढ़ो, padapter,
					  "RTW_CMD_THREAD");
	अगर (IS_ERR(padapter->cmdThपढ़ो))
		err = PTR_ERR(padapter->cmdThपढ़ो);
	अन्यथा
		/* रुको क्रम cmd_thपढ़ो to run */
		रुको_क्रम_completion_पूर्णांकerruptible(&padapter->cmdpriv.terminate_cmdthपढ़ो_comp);

	वापस err;
पूर्ण

व्योम rtw_stop_drv_thपढ़ोs(काष्ठा adapter *padapter)
अणु
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("+%s\n", __func__));

	/* Below is to terminate rtw_cmd_thपढ़ो & event_thपढ़ो... */
	complete(&padapter->cmdpriv.cmd_queue_comp);
	अगर (padapter->cmdThपढ़ो)
		रुको_क्रम_completion_पूर्णांकerruptible(&padapter->cmdpriv.terminate_cmdthपढ़ो_comp);
पूर्ण

अटल u8 rtw_init_शेष_value(काष्ठा adapter *padapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	/* xmit_priv */
	pxmitpriv->vcs_setting = pregistrypriv->vrtl_carrier_sense;
	pxmitpriv->vcs = pregistrypriv->vcs_type;
	pxmitpriv->vcs_type = pregistrypriv->vcs_type;
	pxmitpriv->frag_len = pregistrypriv->frag_thresh;

	/* mlme_priv */
	pmlmepriv->scan_पूर्णांकerval = SCAN_INTERVAL;/*  30*2 sec = 60sec */
	pmlmepriv->scan_mode = SCAN_ACTIVE;

	/* ht_priv */
	pmlmepriv->htpriv.ampdu_enable = false;/* set to disabled */

	/* security_priv */
	psecuritypriv->binstallGrpkey = _FAIL;
	psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
	psecuritypriv->करोt11PrivacyAlgrthm = _NO_PRIVACY_;
	psecuritypriv->करोt11PrivacyKeyIndex = 0;
	psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
	psecuritypriv->करोt118021XGrpKeyid = 1;
	psecuritypriv->ndisauthtype = Ndis802_11AuthModeOpen;
	psecuritypriv->ndisencryptstatus = Ndis802_11WEPDisabled;

	/* registry_priv */
	rtw_init_registrypriv_dev_network(padapter);
	rtw_update_registrypriv_dev_network(padapter);

	/* hal_priv */
	rtw_hal_def_value_init(padapter);

	/* misc. */
	padapter->bReadPortCancel = false;
	padapter->bWritePortCancel = false;
	वापस _SUCCESS;
पूर्ण

u8 rtw_reset_drv_sw(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	/* hal_priv */
	rtw_hal_def_value_init(padapter);
	padapter->bReadPortCancel = false;
	padapter->bWritePortCancel = false;
	pmlmepriv->scan_पूर्णांकerval = SCAN_INTERVAL;/*  30*2 sec = 60sec */

	padapter->xmitpriv.tx_pkts = 0;
	padapter->recvpriv.rx_pkts = 0;

	pmlmepriv->LinkDetectInfo.bBusyTraffic = false;

	_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING);
	rtw_hal_sreset_init(padapter);
	pwrctrlpriv->pwr_state_check_cnts = 0;

	/* mlmeextpriv */
	padapter->mlmeextpriv.sitesurvey_res.state = SCAN_DISABLE;

	rtw_set_संकेत_stat_समयr(&padapter->recvpriv);

	वापस _SUCCESS;
पूर्ण

u8 rtw_init_drv_sw(काष्ठा adapter *padapter)
अणु
	u8 ret8 = _SUCCESS;

	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("+%s\n", __func__));

	अगर ((rtw_init_cmd_priv(&padapter->cmdpriv)) == _FAIL) अणु
		RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_err_, ("\n Can't init cmd_priv\n"));
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	padapter->cmdpriv.padapter = padapter;

	अगर (rtw_init_mlme_priv(padapter) == _FAIL) अणु
		RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_err_, ("\n Can't init mlme_priv\n"));
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (init_mlme_ext_priv(padapter) == _FAIL) अणु
		RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_err_, ("\n Can't init mlme_ext_priv\n"));
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (_rtw_init_xmit_priv(&padapter->xmitpriv, padapter) == _FAIL) अणु
		DBG_88E("Can't _rtw_init_xmit_priv\n");
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (_rtw_init_recv_priv(&padapter->recvpriv, padapter) == _FAIL) अणु
		DBG_88E("Can't _rtw_init_recv_priv\n");
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (_rtw_init_sta_priv(&padapter->stapriv) == _FAIL) अणु
		DBG_88E("Can't _rtw_init_sta_priv\n");
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	padapter->stapriv.padapter = padapter;

	rtw_init_bcmc_stainfo(padapter);

	rtw_init_pwrctrl_priv(padapter);

	ret8 = rtw_init_शेष_value(padapter);

	rtw_hal_dm_init(padapter);
	rtw_hal_sw_led_init(padapter);

	rtw_hal_sreset_init(padapter);

निकास:
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("-%s\n", __func__));

	वापस ret8;
पूर्ण

व्योम rtw_cancel_all_समयr(काष्ठा adapter *padapter)
अणु
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("+%s\n", __func__));

	del_समयr_sync(&padapter->mlmepriv.assoc_समयr);
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("%s:cancel association timer complete!\n", __func__));

	del_समयr_sync(&padapter->mlmepriv.scan_to_समयr);
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("%s:cancel scan_to_timer!\n", __func__));

	del_समयr_sync(&padapter->mlmepriv.dynamic_chk_समयr);
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("%s:cancel dynamic_chk_timer!\n", __func__));

	/*  cancel sw led समयr */
	rtw_hal_sw_led_deinit(padapter);
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("%s:cancel DeInitSwLeds!\n", __func__));

	del_समयr_sync(&padapter->pwrctrlpriv.pwr_state_check_समयr);

	del_समयr_sync(&padapter->recvpriv.संकेत_stat_समयr);
पूर्ण

u8 rtw_मुक्त_drv_sw(काष्ठा adapter *padapter)
अणु
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("==>%s", __func__));

	मुक्त_mlme_ext_priv(&padapter->mlmeextpriv);

	rtw_मुक्त_mlme_priv(&padapter->mlmepriv);
	_rtw_मुक्त_xmit_priv(&padapter->xmitpriv);

	/* will मुक्त bcmc_stainfo here */
	_rtw_मुक्त_sta_priv(&padapter->stapriv);

	_rtw_मुक्त_recv_priv(&padapter->recvpriv);

	rtw_hal_मुक्त_data(padapter);

	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("<== %s\n", __func__));

	mutex_destroy(&padapter->hw_init_mutex);

	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("-%s\n", __func__));

	वापस _SUCCESS;
पूर्ण

अटल पूर्णांक _netdev_खोलो(काष्ठा net_device *pnetdev)
अणु
	uपूर्णांक status;
	पूर्णांक err;
	काष्ठा adapter *padapter = netdev_priv(pnetdev);
	काष्ठा pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("+88eu_drv - dev_open\n"));
	DBG_88E("+88eu_drv - drv_open, bup =%d\n", padapter->bup);

	अगर (pwrctrlpriv->ps_flag) अणु
		padapter->net_बंदd = false;
		जाओ netdev_खोलो_normal_process;
	पूर्ण

	अगर (!padapter->bup) अणु
		padapter->bDriverStopped = false;
		padapter->bSurpriseRemoved = false;

		status = rtw_hal_init(padapter);
		अगर (status == _FAIL) अणु
			RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_err_, ("rtl88eu_hal_init(): Can't init h/w!\n"));
			जाओ netdev_खोलो_error;
		पूर्ण

		pr_info("MAC Address = %pM\n", pnetdev->dev_addr);

		err = rtw_start_drv_thपढ़ोs(padapter);
		अगर (err) अणु
			pr_info("Initialize driver software resource Failed!\n");
			जाओ netdev_खोलो_error;
		पूर्ण

		अगर (init_hw_mlme_ext(padapter) == _FAIL) अणु
			pr_info("can't init mlme_ext_priv\n");
			जाओ netdev_खोलो_error;
		पूर्ण
		rtw_hal_inirp_init(padapter);

		led_control_8188eu(padapter, LED_CTL_NO_LINK);

		padapter->bup = true;
	पूर्ण
	padapter->net_बंदd = false;

	mod_समयr(&padapter->mlmepriv.dynamic_chk_समयr,
		  jअगरfies + msecs_to_jअगरfies(2000));

	padapter->pwrctrlpriv.bips_processing = false;
	rtw_set_pwr_state_check_समयr(&padapter->pwrctrlpriv);

	अगर (!rtw_netअगर_queue_stopped(pnetdev))
		netअगर_tx_start_all_queues(pnetdev);
	अन्यथा
		netअगर_tx_wake_all_queues(pnetdev);

netdev_खोलो_normal_process:
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("-88eu_drv - dev_open\n"));
	DBG_88E("-88eu_drv - drv_open, bup =%d\n", padapter->bup);
	वापस 0;

netdev_खोलो_error:
	padapter->bup = false;
	netअगर_carrier_off(pnetdev);
	netअगर_tx_stop_all_queues(pnetdev);
	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_err_, ("-88eu_drv - dev_open, fail!\n"));
	DBG_88E("-88eu_drv - drv_open fail, bup =%d\n", padapter->bup);
	वापस -1;
पूर्ण

पूर्णांक netdev_खोलो(काष्ठा net_device *pnetdev)
अणु
	पूर्णांक ret;
	काष्ठा adapter *padapter = netdev_priv(pnetdev);

	अगर (mutex_lock_पूर्णांकerruptible(&padapter->hw_init_mutex))
		वापस -ERESTARTSYS;
	ret = _netdev_खोलो(pnetdev);
	mutex_unlock(&padapter->hw_init_mutex);
	वापस ret;
पूर्ण

पूर्णांक  ips_netdrv_खोलो(काष्ठा adapter *padapter)
अणु
	पूर्णांक status = _SUCCESS;

	padapter->net_बंदd = false;
	DBG_88E("===> %s.........\n", __func__);

	padapter->bDriverStopped = false;
	padapter->bSurpriseRemoved = false;

	status = rtw_hal_init(padapter);
	अगर (status == _FAIL) अणु
		RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_err_, ("%s(): Can't init h/w!\n", __func__));
		जाओ netdev_खोलो_error;
	पूर्ण

	rtw_hal_inirp_init(padapter);

	rtw_set_pwr_state_check_समयr(&padapter->pwrctrlpriv);
	mod_समयr(&padapter->mlmepriv.dynamic_chk_समयr,
		  jअगरfies + msecs_to_jअगरfies(5000));

	वापस _SUCCESS;

netdev_खोलो_error:
	DBG_88E("-%s - drv_open failure, bup =%d\n", __func__, padapter->bup);

	वापस _FAIL;
पूर्ण

पूर्णांक rtw_ips_pwr_up(काष्ठा adapter *padapter)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ start_समय = jअगरfies;

	DBG_88E("===>  %s..............\n", __func__);
	rtw_reset_drv_sw(padapter);

	result = ips_netdrv_खोलो(padapter);

	led_control_8188eu(padapter, LED_CTL_NO_LINK);

	DBG_88E("<===  %s.............. in %dms\n", __func__,
		jअगरfies_to_msecs(jअगरfies - start_समय));
	वापस result;
पूर्ण

व्योम rtw_ips_pwr_करोwn(काष्ठा adapter *padapter)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;

	DBG_88E("===> %s...................\n", __func__);

	padapter->net_बंदd = true;

	led_control_8188eu(padapter, LED_CTL_POWER_OFF);

	rtw_ips_dev_unload(padapter);
	DBG_88E("<=== %s..................... in %dms\n", __func__,
		jअगरfies_to_msecs(jअगरfies - start_समय));
पूर्ण

व्योम rtw_ips_dev_unload(काष्ठा adapter *padapter)
अणु
	DBG_88E("====> %s...\n", __func__);

	rtw_hal_set_hwreg(padapter, HW_VAR_FIFO_CLEARN_UP, शून्य);

	usb_पूर्णांकf_stop(padapter);

	/* s5. */
	अगर (!padapter->bSurpriseRemoved)
		rtw_hal_deinit(padapter);
पूर्ण

अटल पूर्णांक netdev_बंद(काष्ठा net_device *pnetdev)
अणु
	काष्ठा adapter *padapter = netdev_priv(pnetdev);

	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("+88eu_drv - drv_close\n"));

	अगर (padapter->pwrctrlpriv.bInternalAutoSuspend) अणु
		अगर (padapter->pwrctrlpriv.rf_pwrstate == rf_off)
			padapter->pwrctrlpriv.ps_flag = true;
	पूर्ण
	padapter->net_बंदd = true;

	अगर (padapter->pwrctrlpriv.rf_pwrstate == rf_on) अणु
		DBG_88E("(2)88eu_drv - drv_close, bup =%d, hw_init_completed =%d\n",
			padapter->bup, padapter->hw_init_completed);

		/* s1. */
		अगर (pnetdev) अणु
			अगर (!rtw_netअगर_queue_stopped(pnetdev))
				netअगर_tx_stop_all_queues(pnetdev);
		पूर्ण

		/* s2. */
		LeaveAllPowerSaveMode(padapter);
		rtw_disassoc_cmd(padapter, 500, false);
		/* s2-2.  indicate disconnect to os */
		rtw_indicate_disconnect(padapter);
		/* s2-3. */
		rtw_मुक्त_assoc_resources(padapter);
		/* s2-4. */
		rtw_मुक्त_network_queue(padapter, true);
		/*  Close LED */
		led_control_8188eu(padapter, LED_CTL_POWER_OFF);
	पूर्ण

	RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_info_, ("-88eu_drv - drv_close\n"));
	DBG_88E("-88eu_drv - drv_close, bup =%d\n", padapter->bup);
	वापस 0;
पूर्ण
