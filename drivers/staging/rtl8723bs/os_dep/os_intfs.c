<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _OS_INTFS_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_data.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Realtek Wireless Lan Driver");
MODULE_AUTHOR("Realtek Semiconductor Corp.");
MODULE_VERSION(DRIVERVERSION);

/* module param शेषs */
अटल पूर्णांक rtw_chip_version;
अटल पूर्णांक rtw_rfपूर्णांकfs = HWPI;
अटल पूर्णांक rtw_lbkmode;/* RTL8712_AIR_TRX; */


अटल पूर्णांक rtw_network_mode = Ndis802_11IBSS;/* Ndis802_11Infraकाष्ठाure;infra, ad-hoc, स्वतः */
/* काष्ठा ndis_802_11_ssid	ssid; */
अटल पूर्णांक rtw_channel = 1;/* ad-hoc support requirement */
अटल पूर्णांक rtw_wireless_mode = WIRELESS_MODE_MAX;
अटल पूर्णांक rtw_vrtl_carrier_sense = AUTO_VCS;
अटल पूर्णांक rtw_vcs_type = RTS_CTS;/*  */
अटल पूर्णांक rtw_rts_thresh = 2347;/*  */
अटल पूर्णांक rtw_frag_thresh = 2346;/*  */
अटल पूर्णांक rtw_preamble = PREAMBLE_LONG;/* दीर्घ, लघु, स्वतः */
अटल पूर्णांक rtw_scan_mode = 1;/* active, passive */
अटल पूर्णांक rtw_adhoc_tx_pwr = 1;
अटल पूर्णांक rtw_soft_ap;
/* पूर्णांक smart_ps = 1; */
अटल पूर्णांक rtw_घातer_mgnt = 1;
अटल पूर्णांक rtw_ips_mode = IPS_NORMAL;
module_param(rtw_ips_mode, पूर्णांक, 0644);
MODULE_PARM_DESC(rtw_ips_mode, "The default IPS mode");

अटल पूर्णांक rtw_smart_ps = 2;

अटल पूर्णांक rtw_check_fw_ps = 1;

अटल पूर्णांक rtw_usb_rxagg_mode = 2;/* USB_RX_AGG_DMA = 1, USB_RX_AGG_USB =2 */
module_param(rtw_usb_rxagg_mode, पूर्णांक, 0644);

अटल पूर्णांक rtw_radio_enable = 1;
अटल पूर्णांक rtw_दीर्घ_retry_lmt = 7;
अटल पूर्णांक rtw_लघु_retry_lmt = 7;
अटल पूर्णांक rtw_busy_thresh = 40;
/* पूर्णांक qos_enable = 0; */
अटल पूर्णांक rtw_ack_policy = NORMAL_ACK;

अटल पूर्णांक rtw_software_encrypt;
अटल पूर्णांक rtw_software_decrypt;

अटल पूर्णांक rtw_acm_method;/*  0:By SW 1:By HW. */

अटल पूर्णांक rtw_wmm_enable = 1;/*  शेष is set to enable the wmm. */
अटल पूर्णांक rtw_uapsd_enable;
अटल पूर्णांक rtw_uapsd_max_sp = NO_LIMIT;
अटल पूर्णांक rtw_uapsd_acbk_en;
अटल पूर्णांक rtw_uapsd_acbe_en;
अटल पूर्णांक rtw_uapsd_acvi_en;
अटल पूर्णांक rtw_uapsd_acvo_en;

पूर्णांक rtw_ht_enable = 1;
/*  0: 20 MHz, 1: 40 MHz, 2: 80 MHz, 3: 160MHz, 4: 80+80MHz */
/*  2.4G use bit 0 ~ 3, 5G use bit 4 ~ 7 */
/*  0x21 means enable 2.4G 40MHz & 5G 80MHz */
अटल पूर्णांक rtw_bw_mode = 0x21;
अटल पूर्णांक rtw_ampdu_enable = 1;/* क्रम enable tx_ampdu ,0: disable, 0x1:enable (but wअगरi_spec should be 0), 0x2: क्रमce enable (करोn't care wअगरi_spec) */
अटल पूर्णांक rtw_rx_stbc = 1;/*  0: disable, 1:enable 2.4g */
अटल पूर्णांक rtw_ampdu_amsdu;/*  0: disabled, 1:enabled, 2:स्वतः . There is an IOT issu with DLINK सूची-629 when the flag turn on */
/*  Short GI support Bit Map */
/*  BIT0 - 20MHz, 0: non-support, 1: support */
/*  BIT1 - 40MHz, 0: non-support, 1: support */
/*  BIT2 - 80MHz, 0: non-support, 1: support */
/*  BIT3 - 160MHz, 0: non-support, 1: support */
अटल पूर्णांक rtw_लघु_gi = 0xf;
/*  BIT0: Enable VHT LDPC Rx, BIT1: Enable VHT LDPC Tx, BIT4: Enable HT LDPC Rx, BIT5: Enable HT LDPC Tx */
अटल पूर्णांक rtw_ldpc_cap = 0x33;
/*  BIT0: Enable VHT STBC Rx, BIT1: Enable VHT STBC Tx, BIT4: Enable HT STBC Rx, BIT5: Enable HT STBC Tx */
अटल पूर्णांक rtw_stbc_cap = 0x13;
/*  BIT0: Enable VHT Beamक्रमmer, BIT1: Enable VHT Beamक्रमmee, BIT4: Enable HT Beamक्रमmer, BIT5: Enable HT Beamक्रमmee */
अटल पूर्णांक rtw_beamक्रमm_cap = 0x2;

अटल पूर्णांक rtw_lowrate_two_xmit = 1;/* Use 2 path Tx to transmit MCS0~7 and legacy mode */

/* पूर्णांक rf_config = RF_1T2R;  1T2R */
अटल पूर्णांक rtw_rf_config = RF_MAX_TYPE;  /* स्वतः */
अटल पूर्णांक rtw_low_घातer;
अटल पूर्णांक rtw_wअगरi_spec;
अटल पूर्णांक rtw_channel_plan = RT_CHANNEL_DOMAIN_MAX;

अटल पूर्णांक rtw_btcoex_enable = 1;
module_param(rtw_btcoex_enable, पूर्णांक, 0644);
MODULE_PARM_DESC(rtw_btcoex_enable, "Enable BT co-existence mechanism");
अटल पूर्णांक rtw_bt_iso = 2;/*  0:Low, 1:High, 2:From Efuse */
अटल पूर्णांक rtw_bt_sco = 3;/*  0:Idle, 1:None-SCO, 2:SCO, 3:From Counter, 4.Busy, 5.OtherBusy */
अटल पूर्णांक rtw_bt_ampdu = 1 ;/*  0:Disable BT control A-MPDU, 1:Enable BT control A-MPDU. */
अटल पूर्णांक rtw_ant_num = -1; /*  <0: undefined, >0: Antenna number */
module_param(rtw_ant_num, पूर्णांक, 0644);
MODULE_PARM_DESC(rtw_ant_num, "Antenna number setting");

अटल पूर्णांक rtw_antभाग_cfg = 1; /*  0:OFF , 1:ON, 2:decide by Efuse config */
अटल पूर्णांक rtw_antभाग_प्रकारype; /* 0:decide by efuse  1: क्रम 88EE, 1Tx and 1RxCG are भागersity.(2 Ant with SPDT), 2:  क्रम 88EE, 1Tx and 2Rx are भागersity.(2 Ant, Tx and RxCG are both on aux port, RxCS is on मुख्य port), 3: क्रम 88EE, 1Tx and 1RxCG are fixed.(1Ant, Tx and RxCG are both on aux port) */


अटल पूर्णांक rtw_enusbss;/* 0:disable, 1:enable */

अटल पूर्णांक rtw_hwpdn_mode = 2;/* 0:disable, 1:enable, 2: by EFUSE config */

अटल पूर्णांक rtw_hwpwrp_detect; /* HW घातer  ping detect 0:disable , 1:enable */

अटल पूर्णांक rtw_hw_wps_pbc;

पूर्णांक rtw_mc2u_disable = 0;

अटल पूर्णांक rtw_80211d;

अटल पूर्णांक rtw_qos_opt_enable;/* 0: disable, 1:enable */
module_param(rtw_qos_opt_enable, पूर्णांक, 0644);

अटल अक्षर *अगरname = "wlan%d";
module_param(अगरname, अक्षरp, 0644);
MODULE_PARM_DESC(अगरname, "The default name to allocate for first interface");

अक्षर *rtw_iniपंचांगac = शून्य;  /*  temp mac address अगर users want to use instead of the mac address in Efuse */

module_param(rtw_iniपंचांगac, अक्षरp, 0644);
module_param(rtw_channel_plan, पूर्णांक, 0644);
module_param(rtw_chip_version, पूर्णांक, 0644);
module_param(rtw_rfपूर्णांकfs, पूर्णांक, 0644);
module_param(rtw_lbkmode, पूर्णांक, 0644);
module_param(rtw_network_mode, पूर्णांक, 0644);
module_param(rtw_channel, पूर्णांक, 0644);
module_param(rtw_wmm_enable, पूर्णांक, 0644);
module_param(rtw_vrtl_carrier_sense, पूर्णांक, 0644);
module_param(rtw_vcs_type, पूर्णांक, 0644);
module_param(rtw_busy_thresh, पूर्णांक, 0644);

module_param(rtw_ht_enable, पूर्णांक, 0644);
module_param(rtw_bw_mode, पूर्णांक, 0644);
module_param(rtw_ampdu_enable, पूर्णांक, 0644);
module_param(rtw_rx_stbc, पूर्णांक, 0644);
module_param(rtw_ampdu_amsdu, पूर्णांक, 0644);

module_param(rtw_lowrate_two_xmit, पूर्णांक, 0644);

module_param(rtw_rf_config, पूर्णांक, 0644);
module_param(rtw_घातer_mgnt, पूर्णांक, 0644);
module_param(rtw_smart_ps, पूर्णांक, 0644);
module_param(rtw_low_घातer, पूर्णांक, 0644);
module_param(rtw_wअगरi_spec, पूर्णांक, 0644);

module_param(rtw_antभाग_cfg, पूर्णांक, 0644);
module_param(rtw_antभाग_प्रकारype, पूर्णांक, 0644);

module_param(rtw_enusbss, पूर्णांक, 0644);
module_param(rtw_hwpdn_mode, पूर्णांक, 0644);
module_param(rtw_hwpwrp_detect, पूर्णांक, 0644);

module_param(rtw_hw_wps_pbc, पूर्णांक, 0644);

अटल uपूर्णांक rtw_max_roaming_बार = 2;
module_param(rtw_max_roaming_बार, uपूर्णांक, 0644);
MODULE_PARM_DESC(rtw_max_roaming_बार, "The max roaming times to try");

module_param(rtw_mc2u_disable, पूर्णांक, 0644);

module_param(rtw_80211d, पूर्णांक, 0644);
MODULE_PARM_DESC(rtw_80211d, "Enable 802.11d mechanism");

अटल uपूर्णांक rtw_notch_filter;
module_param(rtw_notch_filter, uपूर्णांक, 0644);
MODULE_PARM_DESC(rtw_notch_filter, "0:Disable, 1:Enable, 2:Enable only for P2P");

#घोषणा CONFIG_RTW_HIQ_FILTER 1

अटल uपूर्णांक rtw_hiq_filter = CONFIG_RTW_HIQ_FILTER;
module_param(rtw_hiq_filter, uपूर्णांक, 0644);
MODULE_PARM_DESC(rtw_hiq_filter, "0:allow all, 1:allow special, 2:deny all");

अटल पूर्णांक rtw_tx_pwr_lmt_enable;
अटल पूर्णांक rtw_tx_pwr_by_rate;

module_param(rtw_tx_pwr_lmt_enable, पूर्णांक, 0644);
MODULE_PARM_DESC(rtw_tx_pwr_lmt_enable, "0:Disable, 1:Enable, 2: Depend on efuse");

module_param(rtw_tx_pwr_by_rate, पूर्णांक, 0644);
MODULE_PARM_DESC(rtw_tx_pwr_by_rate, "0:Disable, 1:Enable, 2: Depend on efuse");

अटल पूर्णांक netdev_बंद(काष्ठा net_device *pnetdev);

अटल व्योम loadparam(काष्ठा adapter *padapter, काष्ठा net_device *pnetdev)
अणु
	काष्ठा registry_priv  *registry_par = &padapter->registrypriv;

	registry_par->chip_version = (u8)rtw_chip_version;
	registry_par->rfपूर्णांकfs = (u8)rtw_rfपूर्णांकfs;
	registry_par->lbkmode = (u8)rtw_lbkmode;
	/* registry_par->hci = (u8)hci; */
	registry_par->network_mode  = (u8)rtw_network_mode;

	स_नकल(registry_par->ssid.Ssid, "ANY", 3);
	registry_par->ssid.SsidLength = 3;

	registry_par->channel = (u8)rtw_channel;
	registry_par->wireless_mode = (u8)rtw_wireless_mode;

	registry_par->vrtl_carrier_sense = (u8)rtw_vrtl_carrier_sense;
	registry_par->vcs_type = (u8)rtw_vcs_type;
	registry_par->rts_thresh = (u16)rtw_rts_thresh;
	registry_par->frag_thresh = (u16)rtw_frag_thresh;
	registry_par->preamble = (u8)rtw_preamble;
	registry_par->scan_mode = (u8)rtw_scan_mode;
	registry_par->adhoc_tx_pwr = (u8)rtw_adhoc_tx_pwr;
	registry_par->soft_ap =  (u8)rtw_soft_ap;
	registry_par->smart_ps =  (u8)rtw_smart_ps;
	registry_par->check_fw_ps = (u8)rtw_check_fw_ps;
	registry_par->घातer_mgnt = (u8)rtw_घातer_mgnt;
	registry_par->ips_mode = (u8)rtw_ips_mode;
	registry_par->radio_enable = (u8)rtw_radio_enable;
	registry_par->दीर्घ_retry_lmt = (u8)rtw_दीर्घ_retry_lmt;
	registry_par->लघु_retry_lmt = (u8)rtw_लघु_retry_lmt;
	registry_par->busy_thresh = (u16)rtw_busy_thresh;
	/* registry_par->qos_enable = (u8)rtw_qos_enable; */
	registry_par->ack_policy = (u8)rtw_ack_policy;
	registry_par->software_encrypt = (u8)rtw_software_encrypt;
	registry_par->software_decrypt = (u8)rtw_software_decrypt;

	registry_par->acm_method = (u8)rtw_acm_method;
	registry_par->usb_rxagg_mode = (u8)rtw_usb_rxagg_mode;

	 /* UAPSD */
	registry_par->wmm_enable = (u8)rtw_wmm_enable;
	registry_par->uapsd_enable = (u8)rtw_uapsd_enable;
	registry_par->uapsd_max_sp = (u8)rtw_uapsd_max_sp;
	registry_par->uapsd_acbk_en = (u8)rtw_uapsd_acbk_en;
	registry_par->uapsd_acbe_en = (u8)rtw_uapsd_acbe_en;
	registry_par->uapsd_acvi_en = (u8)rtw_uapsd_acvi_en;
	registry_par->uapsd_acvo_en = (u8)rtw_uapsd_acvo_en;

	registry_par->ht_enable = (u8)rtw_ht_enable;
	registry_par->bw_mode = (u8)rtw_bw_mode;
	registry_par->ampdu_enable = (u8)rtw_ampdu_enable;
	registry_par->rx_stbc = (u8)rtw_rx_stbc;
	registry_par->ampdu_amsdu = (u8)rtw_ampdu_amsdu;
	registry_par->लघु_gi = (u8)rtw_लघु_gi;
	registry_par->ldpc_cap = (u8)rtw_ldpc_cap;
	registry_par->stbc_cap = (u8)rtw_stbc_cap;
	registry_par->beamक्रमm_cap = (u8)rtw_beamक्रमm_cap;

	registry_par->lowrate_two_xmit = (u8)rtw_lowrate_two_xmit;
	registry_par->rf_config = (u8)rtw_rf_config;
	registry_par->low_घातer = (u8)rtw_low_घातer;


	registry_par->wअगरi_spec = (u8)rtw_wअगरi_spec;

	registry_par->channel_plan = (u8)rtw_channel_plan;

	registry_par->btcoex = (u8)rtw_btcoex_enable;
	registry_par->bt_iso = (u8)rtw_bt_iso;
	registry_par->bt_sco = (u8)rtw_bt_sco;
	registry_par->bt_ampdu = (u8)rtw_bt_ampdu;
	registry_par->ant_num = (s8)rtw_ant_num;

	registry_par->accept_addba_req = true;

	registry_par->antभाग_cfg = (u8)rtw_antभाग_cfg;
	registry_par->antभाग_प्रकारype = (u8)rtw_antभाग_प्रकारype;

	registry_par->hw_wps_pbc = (u8)rtw_hw_wps_pbc;

	registry_par->max_roaming_बार = (u8)rtw_max_roaming_बार;

	registry_par->enable80211d = (u8)rtw_80211d;

	snम_लिखो(registry_par->अगरname, 16, "%s", अगरname);

	registry_par->notch_filter = (u8)rtw_notch_filter;

	registry_par->RegEnableTxPowerLimit = (u8)rtw_tx_pwr_lmt_enable;
	registry_par->RegEnableTxPowerByRate = (u8)rtw_tx_pwr_by_rate;

	registry_par->RegPowerBase = 14;
	registry_par->TxBBSwing_2G = 0xFF;
	registry_par->TxBBSwing_5G = 0xFF;
	registry_par->bEn_RFE = 1;
	registry_par->RFE_Type = 64;

	registry_par->qos_opt_enable = (u8)rtw_qos_opt_enable;

	registry_par->hiq_filter = (u8)rtw_hiq_filter;
पूर्ण

अटल पूर्णांक rtw_net_set_mac_address(काष्ठा net_device *pnetdev, व्योम *p)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(pnetdev);
	काष्ठा sockaddr *addr = p;

	अगर (!padapter->bup) अणु
		/* addr->sa_data[4], addr->sa_data[5]); */
		स_नकल(padapter->eeprompriv.mac_addr, addr->sa_data, ETH_ALEN);
		/* स_नकल(pnetdev->dev_addr, addr->sa_data, ETH_ALEN); */
		/* padapter->bset_hwaddr = true; */
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *rtw_net_get_stats(काष्ठा net_device *pnetdev)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(pnetdev);
	काष्ठा xmit_priv *pxmitpriv = &(padapter->xmitpriv);
	काष्ठा recv_priv *precvpriv = &(padapter->recvpriv);

	padapter->stats.tx_packets = pxmitpriv->tx_pkts;/* pxmitpriv->tx_pkts++; */
	padapter->stats.rx_packets = precvpriv->rx_pkts;/* precvpriv->rx_pkts++; */
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
	काष्ठा adapter	*padapter = rtw_netdev_priv(dev);
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
	__be16	eth_type;
	u32 priority;
	u8 *pdata = skb->data;

	स_नकल(&eth_type, pdata + (ETH_ALEN << 1), 2);

	चयन (be16_to_cpu(eth_type)) अणु
	हाल ETH_P_IP:

		piphdr = (काष्ठा iphdr *)(pdata + ETH_HLEN);

		dscp = piphdr->tos & 0xfc;

		priority = dscp >> 5;

		अवरोध;
	शेष:
		priority = 0;
	पूर्ण

	वापस rtw_1d_to_queue[priority];
पूर्ण

अटल पूर्णांक rtw_ndev_notअगरier_call(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ state, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (dev->netdev_ops->nकरो_करो_ioctl != rtw_ioctl)
		वापस NOTIFY_DONE;

	netdev_info(dev, FUNC_NDEV_FMT " state:%lu\n", FUNC_NDEV_ARG(dev),
		    state);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rtw_ndev_notअगरier = अणु
	.notअगरier_call = rtw_ndev_notअगरier_call,
पूर्ण;

पूर्णांक rtw_ndev_notअगरier_रेजिस्टर(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&rtw_ndev_notअगरier);
पूर्ण

व्योम rtw_ndev_notअगरier_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&rtw_ndev_notअगरier);
पूर्ण


अटल पूर्णांक rtw_ndev_init(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adapter = rtw_netdev_priv(dev);

	netdev_dbg(dev, FUNC_ADPT_FMT "\n", FUNC_ADPT_ARG(adapter));
	म_नकलन(adapter->old_अगरname, dev->name, IFNAMSIZ);

	वापस 0;
पूर्ण

अटल व्योम rtw_ndev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adapter = rtw_netdev_priv(dev);

	netdev_dbg(dev, FUNC_ADPT_FMT "\n", FUNC_ADPT_ARG(adapter));
पूर्ण

अटल स्थिर काष्ठा net_device_ops rtw_netdev_ops = अणु
	.nकरो_init = rtw_ndev_init,
	.nकरो_uninit = rtw_ndev_uninit,
	.nकरो_खोलो = netdev_खोलो,
	.nकरो_stop = netdev_बंद,
	.nकरो_start_xmit = rtw_xmit_entry,
	.nकरो_select_queue	= rtw_select_queue,
	.nकरो_set_mac_address = rtw_net_set_mac_address,
	.nकरो_get_stats = rtw_net_get_stats,
	.nकरो_करो_ioctl = rtw_ioctl,
पूर्ण;

पूर्णांक rtw_init_netdev_name(काष्ठा net_device *pnetdev, स्थिर अक्षर *अगरname)
अणु
	अगर (dev_alloc_name(pnetdev, अगरname) < 0) अणु
		pr_err("dev_alloc_name, fail for %s\n", अगरname);
		वापस 1;
	पूर्ण
	netअगर_carrier_off(pnetdev);
	/* rtw_netअगर_stop_queue(pnetdev); */

	वापस 0;
पूर्ण

काष्ठा net_device *rtw_init_netdev(काष्ठा adapter *old_padapter)
अणु
	काष्ठा adapter *padapter;
	काष्ठा net_device *pnetdev;

	अगर (old_padapter)
		pnetdev = rtw_alloc_etherdev_with_old_priv(माप(काष्ठा adapter), (व्योम *)old_padapter);
	अन्यथा
		pnetdev = rtw_alloc_etherdev(माप(काष्ठा adapter));

	pr_info("pnetdev = %p\n", pnetdev);
	अगर (!pnetdev)
		वापस शून्य;

	padapter = rtw_netdev_priv(pnetdev);
	padapter->pnetdev = pnetdev;

	/* pnetdev->init = शून्य; */

	pnetdev->netdev_ops = &rtw_netdev_ops;

	/* pnetdev->tx_समयout = शून्य; */
	pnetdev->watchकरोg_समयo = HZ * 3; /* 3 second समयout */
	pnetdev->wireless_handlers = (काष्ठा iw_handler_def *)&rtw_handlers_def;

	/* step 2. */
	loadparam(padapter, pnetdev);

	वापस pnetdev;
पूर्ण

व्योम rtw_unरेजिस्टर_netdevs(काष्ठा dvobj_priv *dvobj)
अणु
	काष्ठा adapter *padapter = शून्य;
	काष्ठा net_device *pnetdev = शून्य;

	padapter = dvobj->padapters;

	अगर (padapter == शून्य)
		वापस;

	pnetdev = padapter->pnetdev;

	अगर ((padapter->DriverState != DRIVER_DISAPPEAR) && pnetdev)
		unरेजिस्टर_netdev(pnetdev); /* will call netdev_बंद() */
	rtw_wdev_unरेजिस्टर(padapter->rtw_wdev);
पूर्ण

u32 rtw_start_drv_thपढ़ोs(काष्ठा adapter *padapter)
अणु
	u32 _status = _SUCCESS;

	padapter->xmitThपढ़ो = kthपढ़ो_run(rtw_xmit_thपढ़ो, padapter, "RTW_XMIT_THREAD");
	अगर (IS_ERR(padapter->xmitThपढ़ो))
		_status = _FAIL;

	padapter->cmdThपढ़ो = kthपढ़ो_run(rtw_cmd_thपढ़ो, padapter, "RTW_CMD_THREAD");
	अगर (IS_ERR(padapter->cmdThपढ़ो))
		_status = _FAIL;
	अन्यथा
		रुको_क्रम_completion(&padapter->cmdpriv.terminate_cmdthपढ़ो_comp); /* रुको क्रम cmd_thपढ़ो to run */

	rtw_hal_start_thपढ़ो(padapter);
	वापस _status;
पूर्ण

व्योम rtw_stop_drv_thपढ़ोs(काष्ठा adapter *padapter)
अणु
	rtw_stop_cmd_thपढ़ो(padapter);

	/*  Below is to termindate tx_thपढ़ो... */
	complete(&padapter->xmitpriv.xmit_comp);
	रुको_क्रम_completion(&padapter->xmitpriv.terminate_xmitthपढ़ो_comp);

	rtw_hal_stop_thपढ़ो(padapter);
पूर्ण

अटल व्योम rtw_init_शेष_value(काष्ठा adapter *padapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	/* xmit_priv */
	pxmitpriv->vcs_setting = pregistrypriv->vrtl_carrier_sense;
	pxmitpriv->vcs = pregistrypriv->vcs_type;
	pxmitpriv->vcs_type = pregistrypriv->vcs_type;
	/* pxmitpriv->rts_thresh = pregistrypriv->rts_thresh; */
	pxmitpriv->frag_len = pregistrypriv->frag_thresh;

	/* recv_priv */

	/* mlme_priv */
	pmlmepriv->scan_mode = SCAN_ACTIVE;

	/* qos_priv */
	/* pmlmepriv->qospriv.qos_option = pregistrypriv->wmm_enable; */

	/* ht_priv */
	pmlmepriv->htpriv.ampdu_enable = false;/* set to disabled */

	/* security_priv */
	/* rtw_get_encrypt_decrypt_from_registrypriv(padapter); */
	psecuritypriv->binstallGrpkey = _FAIL;
	psecuritypriv->sw_encrypt = pregistrypriv->software_encrypt;
	psecuritypriv->sw_decrypt = pregistrypriv->software_decrypt;

	psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open; /* खोलो प्रणाली */
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
	RTW_ENABLE_FUNC(padapter, DF_RX_BIT);
	RTW_ENABLE_FUNC(padapter, DF_TX_BIT);
	padapter->bLinkInfoDump = 0;
	padapter->bNotअगरyChannelChange = 0;

	/* क्रम debug purpose */
	padapter->fix_rate = 0xFF;
	padapter->driver_ampdu_spacing = 0xFF;
	padapter->driver_rx_ampdu_factor =  0xFF;

पूर्ण

काष्ठा dvobj_priv *devobj_init(व्योम)
अणु
	काष्ठा dvobj_priv *pdvobj = शून्य;

	pdvobj = rtw_zदो_स्मृति(माप(*pdvobj));
	अगर (pdvobj == शून्य)
		वापस शून्य;

	mutex_init(&pdvobj->hw_init_mutex);
	mutex_init(&pdvobj->h2c_fwcmd_mutex);
	mutex_init(&pdvobj->setch_mutex);
	mutex_init(&pdvobj->setbw_mutex);

	spin_lock_init(&pdvobj->lock);

	pdvobj->macid[1] = true; /* macid = 1 क्रम bc/mc stainfo */

	pdvobj->processing_dev_हटाओ = false;

	atomic_set(&pdvobj->disable_func, 0);

	spin_lock_init(&pdvobj->cam_ctl.lock);

	वापस pdvobj;
पूर्ण

व्योम devobj_deinit(काष्ठा dvobj_priv *pdvobj)
अणु
	अगर (!pdvobj)
		वापस;

	mutex_destroy(&pdvobj->hw_init_mutex);
	mutex_destroy(&pdvobj->h2c_fwcmd_mutex);
	mutex_destroy(&pdvobj->setch_mutex);
	mutex_destroy(&pdvobj->setbw_mutex);

	kमुक्त(pdvobj);
पूर्ण

व्योम rtw_reset_drv_sw(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(padapter);

	/* hal_priv */
	अगर (is_primary_adapter(padapter))
		rtw_hal_def_value_init(padapter);

	RTW_ENABLE_FUNC(padapter, DF_RX_BIT);
	RTW_ENABLE_FUNC(padapter, DF_TX_BIT);
	padapter->bLinkInfoDump = 0;

	padapter->xmitpriv.tx_pkts = 0;
	padapter->recvpriv.rx_pkts = 0;

	pmlmepriv->LinkDetectInfo.bBusyTraffic = false;

	/* pmlmepriv->LinkDetectInfo.TrafficBusyState = false; */
	pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 0;
	pmlmepriv->LinkDetectInfo.LowPowerTransitionCount = 0;

	_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING);

	pwrctrlpriv->pwr_state_check_cnts = 0;

	/* mlmeextpriv */
	padapter->mlmeextpriv.sitesurvey_res.state = SCAN_DISABLE;

	rtw_set_संकेत_stat_समयr(&padapter->recvpriv);

पूर्ण


u8 rtw_init_drv_sw(काष्ठा adapter *padapter)
अणु
	u8 ret8 = _SUCCESS;

	rtw_init_शेष_value(padapter);

	rtw_init_hal_com_शेष_value(padapter);

	अगर (rtw_init_cmd_priv(&padapter->cmdpriv)) अणु
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	padapter->cmdpriv.padapter = padapter;

	अगर (rtw_init_evt_priv(&padapter->evtpriv)) अणु
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण


	अगर (rtw_init_mlme_priv(padapter) == _FAIL) अणु
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	init_mlme_ext_priv(padapter);

	अगर (_rtw_init_xmit_priv(&padapter->xmitpriv, padapter) == _FAIL) अणु
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (_rtw_init_recv_priv(&padapter->recvpriv, padapter) == _FAIL) अणु
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण
	/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
	spin_lock_init(&padapter->security_key_mutex);

	/*  We करोn't need to स_रखो padapter->XXX to zero, because adapter is allocated by vzalloc(). */
	/* स_रखो((अचिन्हित अक्षर *)&padapter->securitypriv, 0, माप (काष्ठा security_priv)); */

	अगर (_rtw_init_sta_priv(&padapter->stapriv) == _FAIL) अणु
		ret8 = _FAIL;
		जाओ निकास;
	पूर्ण

	padapter->stapriv.padapter = padapter;
	padapter->setband = GHZ24_50;
	padapter->fix_rate = 0xFF;
	rtw_init_bcmc_stainfo(padapter);

	rtw_init_pwrctrl_priv(padapter);

	rtw_hal_dm_init(padapter);

निकास:

	वापस ret8;
पूर्ण

व्योम rtw_cancel_all_समयr(काष्ठा adapter *padapter)
अणु
	del_समयr_sync(&padapter->mlmepriv.assoc_समयr);

	del_समयr_sync(&padapter->mlmepriv.scan_to_समयr);

	del_समयr_sync(&padapter->mlmepriv.dynamic_chk_समयr);

	del_समयr_sync(&(adapter_to_pwrctl(padapter)->pwr_state_check_समयr));

	del_समयr_sync(&padapter->mlmepriv.set_scan_deny_समयr);
	rtw_clear_scan_deny(padapter);

	del_समयr_sync(&padapter->recvpriv.संकेत_stat_समयr);

	/* cancel dm समयr */
	rtw_hal_dm_deinit(padapter);
पूर्ण

u8 rtw_मुक्त_drv_sw(काष्ठा adapter *padapter)
अणु
	मुक्त_mlme_ext_priv(&padapter->mlmeextpriv);

	rtw_मुक्त_cmd_priv(&padapter->cmdpriv);

	rtw_मुक्त_evt_priv(&padapter->evtpriv);

	rtw_मुक्त_mlme_priv(&padapter->mlmepriv);

	/* मुक्त_io_queue(padapter); */

	_rtw_मुक्त_xmit_priv(&padapter->xmitpriv);

	_rtw_मुक्त_sta_priv(&padapter->stapriv); /* will मुक्त bcmc_stainfo here */

	_rtw_मुक्त_recv_priv(&padapter->recvpriv);

	rtw_मुक्त_pwrctrl_priv(padapter);

	/* kमुक्त((व्योम *)padapter); */

	rtw_hal_मुक्त_data(padapter);

	/* मुक्त the old_pnetdev */
	अगर (padapter->rereg_nd_name_priv.old_pnetdev) अणु
		मुक्त_netdev(padapter->rereg_nd_name_priv.old_pnetdev);
		padapter->rereg_nd_name_priv.old_pnetdev = शून्य;
	पूर्ण

	/*  clear pbuddyकाष्ठा adapter to aव्योम access wrong poपूर्णांकer. */
	अगर (padapter->pbuddy_adapter)
		padapter->pbuddy_adapter->pbuddy_adapter = शून्य;

	वापस _SUCCESS;
पूर्ण

अटल पूर्णांक _rtw_drv_रेजिस्टर_netdev(काष्ठा adapter *padapter, अक्षर *name)
अणु
	पूर्णांक ret = _SUCCESS;
	काष्ठा net_device *pnetdev = padapter->pnetdev;

	/* alloc netdev name */
	अगर (rtw_init_netdev_name(pnetdev, name))
		वापस _FAIL;

	स_नकल(pnetdev->dev_addr, padapter->eeprompriv.mac_addr, ETH_ALEN);

	/* Tell the network stack we exist */
	अगर (रेजिस्टर_netdev(pnetdev) != 0) अणु
		ret = _FAIL;
		जाओ error_रेजिस्टर_netdev;
	पूर्ण

	वापस ret;

error_रेजिस्टर_netdev:

	rtw_मुक्त_drv_sw(padapter);

	rtw_मुक्त_netdev(pnetdev);

	वापस ret;
पूर्ण

पूर्णांक rtw_drv_रेजिस्टर_netdev(काष्ठा adapter *अगर1)
अणु
	काष्ठा dvobj_priv *dvobj = अगर1->dvobj;
	काष्ठा adapter *padapter = dvobj->padapters;
	अक्षर *name = अगर1->registrypriv.अगरname;

	वापस _rtw_drv_रेजिस्टर_netdev(padapter, name);
पूर्ण

अटल पूर्णांक _netdev_खोलो(काष्ठा net_device *pnetdev)
अणु
	uपूर्णांक status;
	काष्ठा adapter *padapter = rtw_netdev_priv(pnetdev);
	काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(padapter);

	padapter->netअगर_up = true;

	अगर (pwrctrlpriv->ps_flag) अणु
		padapter->net_बंदd = false;
		जाओ netdev_खोलो_normal_process;
	पूर्ण

	अगर (!padapter->bup) अणु
		padapter->bDriverStopped = false;
		padapter->bSurpriseRemoved = false;
		padapter->bCardDisableWOHSM = false;

		status = rtw_hal_init(padapter);
		अगर (status == _FAIL)
			जाओ netdev_खोलो_error;

		status = rtw_start_drv_thपढ़ोs(padapter);
		अगर (status == _FAIL)
			जाओ netdev_खोलो_error;

		अगर (padapter->पूर्णांकf_start)
			padapter->पूर्णांकf_start(padapter);

		rtw_cfg80211_init_wiphy(padapter);

		padapter->bup = true;
		pwrctrlpriv->bips_processing = false;
	पूर्ण
	padapter->net_बंदd = false;

	_set_समयr(&padapter->mlmepriv.dynamic_chk_समयr, 2000);

	अगर (!rtw_netअगर_queue_stopped(pnetdev))
		rtw_netअगर_start_queue(pnetdev);
	अन्यथा
		rtw_netअगर_wake_queue(pnetdev);

netdev_खोलो_normal_process:

	वापस 0;

netdev_खोलो_error:

	padapter->bup = false;

	netअगर_carrier_off(pnetdev);
	rtw_netअगर_stop_queue(pnetdev);

	वापस (-1);
पूर्ण

पूर्णांक netdev_खोलो(काष्ठा net_device *pnetdev)
अणु
	पूर्णांक ret;
	काष्ठा adapter *padapter = rtw_netdev_priv(pnetdev);
	काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(padapter);

	अगर (pwrctrlpriv->bInSuspend)
		वापस 0;

	अगर (mutex_lock_पूर्णांकerruptible(&(adapter_to_dvobj(padapter)->hw_init_mutex)))
		वापस -1;

	ret = _netdev_खोलो(pnetdev);
	mutex_unlock(&(adapter_to_dvobj(padapter)->hw_init_mutex));

	वापस ret;
पूर्ण

अटल पूर्णांक  ips_netdrv_खोलो(काष्ठा adapter *padapter)
अणु
	पूर्णांक status = _SUCCESS;
	/* काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter); */

	padapter->net_बंदd = false;

	padapter->bDriverStopped = false;
	padapter->bCardDisableWOHSM = false;
	/* padapter->bup = true; */

	status = rtw_hal_init(padapter);
	अगर (status == _FAIL)
		जाओ netdev_खोलो_error;

	अगर (padapter->पूर्णांकf_start)
		padapter->पूर्णांकf_start(padapter);

	_set_समयr(&padapter->mlmepriv.dynamic_chk_समयr, 2000);

	वापस _SUCCESS;

netdev_खोलो_error:

	वापस _FAIL;
पूर्ण


पूर्णांक rtw_ips_pwr_up(काष्ठा adapter *padapter)
अणु
	पूर्णांक result;

	result = ips_netdrv_खोलो(padapter);

	वापस result;
पूर्ण

व्योम rtw_ips_pwr_करोwn(काष्ठा adapter *padapter)
अणु
	padapter->bCardDisableWOHSM = true;
	padapter->net_बंदd = true;

	rtw_ips_dev_unload(padapter);
	padapter->bCardDisableWOHSM = false;
पूर्ण

व्योम rtw_ips_dev_unload(काष्ठा adapter *padapter)
अणु

	अगर (!padapter->bSurpriseRemoved)
		rtw_hal_deinit(padapter);
पूर्ण

अटल पूर्णांक pm_netdev_खोलो(काष्ठा net_device *pnetdev, u8 bnormal)
अणु
	पूर्णांक status = -1;

	काष्ठा adapter *padapter = rtw_netdev_priv(pnetdev);

	अगर (bnormal) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&(adapter_to_dvobj(padapter)->hw_init_mutex)) == 0) अणु
			status = _netdev_खोलो(pnetdev);
			mutex_unlock(&(adapter_to_dvobj(padapter)->hw_init_mutex));
		पूर्ण
	पूर्ण अन्यथा अणु
		status =  (_SUCCESS == ips_netdrv_खोलो(padapter)) ? (0) : (-1);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक netdev_बंद(काष्ठा net_device *pnetdev)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(pnetdev);
	काष्ठा pwrctrl_priv *pwrctl = adapter_to_pwrctl(padapter);

	अगर (pwrctl->bInternalAutoSuspend) अणु
		/* rtw_pwr_wakeup(padapter); */
		अगर (pwrctl->rf_pwrstate == rf_off)
			pwrctl->ps_flag = true;
	पूर्ण
	padapter->net_बंदd = true;
	padapter->netअगर_up = false;

/*अगर (!padapter->hw_init_completed)
	अणु

		padapter->bDriverStopped = true;

		rtw_dev_unload(padapter);
	पूर्ण
	अन्यथा*/
	अगर (pwrctl->rf_pwrstate == rf_on) अणु
		/* s1. */
		अगर (pnetdev) अणु
			अगर (!rtw_netअगर_queue_stopped(pnetdev))
				rtw_netअगर_stop_queue(pnetdev);
		पूर्ण

		/* s2. */
		LeaveAllPowerSaveMode(padapter);
		rtw_disassoc_cmd(padapter, 500, false);
		/* s2-2.  indicate disconnect to os */
		rtw_indicate_disconnect(padapter);
		/* s2-3. */
		rtw_मुक्त_assoc_resources(padapter, 1);
		/* s2-4. */
		rtw_मुक्त_network_queue(padapter, true);
	पूर्ण

	rtw_scan_पात(padapter);
	adapter_wdev_data(padapter)->bandroid_scan = false;

	वापस 0;
पूर्ण

व्योम rtw_ndev_deकाष्ठाor(काष्ठा net_device *ndev)
अणु
	kमुक्त(ndev->ieee80211_ptr);
पूर्ण

व्योम rtw_dev_unload(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrctl = adapter_to_pwrctl(padapter);
	काष्ठा dvobj_priv *pobjpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &pobjpriv->drv_dbg;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 cnt = 0;

	अगर (padapter->bup) अणु

		padapter->bDriverStopped = true;
		अगर (padapter->xmitpriv.ack_tx)
			rtw_ack_tx_करोne(&padapter->xmitpriv, RTW_SCTX_DONE_DRV_STOP);

		अगर (padapter->पूर्णांकf_stop)
			padapter->पूर्णांकf_stop(padapter);

		अगर (!pwrctl->bInternalAutoSuspend)
			rtw_stop_drv_thपढ़ोs(padapter);

		जबतक (atomic_पढ़ो(&pcmdpriv->cmdthd_running)) अणु
			अगर (cnt > 5) अणु
				अवरोध;
			पूर्ण अन्यथा अणु
				cnt++;
				msleep(10);
			पूर्ण
		पूर्ण

		/* check the status of IPS */
		अगर (rtw_hal_check_ips_status(padapter) || pwrctl->rf_pwrstate == rf_off) अणु
			/* check HW status and SW state */
			netdev_dbg(padapter->pnetdev,
				   "%s: driver in IPS-FWLPS\n", __func__);
			pdbgpriv->dbg_dev_unload_inIPS_cnt++;
			LeaveAllPowerSaveMode(padapter);
		पूर्ण अन्यथा अणु
			netdev_dbg(padapter->pnetdev,
				   "%s: driver not in IPS\n", __func__);
		पूर्ण

		अगर (!padapter->bSurpriseRemoved) अणु
			hal_btcoex_IpsNotअगरy(padapter, pwrctl->ips_mode_req);

			/* amy modअगरy 20120221 क्रम घातer seq is dअगरferent between driver खोलो and ips */
			rtw_hal_deinit(padapter);

			padapter->bSurpriseRemoved = true;
		पूर्ण

		padapter->bup = false;

	पूर्ण
पूर्ण

अटल पूर्णांक rtw_suspend_मुक्त_assoc_resource(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (rtw_chk_roam_flags(padapter, RTW_ROAM_ON_RESUME)) अणु
		अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)
			&& check_fwstate(pmlmepriv, _FW_LINKED)) अणु
			rtw_set_to_roam(padapter, 1);
		पूर्ण
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) && check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		rtw_disassoc_cmd(padapter, 0, false);
		/* s2-2.  indicate disconnect to os */
		rtw_indicate_disconnect(padapter);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		rtw_sta_flush(padapter);
	पूर्ण

	/* s2-3. */
	rtw_मुक्त_assoc_resources(padapter, 1);

	/* s2-4. */
	rtw_मुक्त_network_queue(padapter, true);

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		rtw_indicate_scan_करोne(padapter, 1);

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) अणु
		netdev_dbg(padapter->pnetdev, "%s: fw_under_linking\n",
			   __func__);
		rtw_indicate_disconnect(padapter);
	पूर्ण

	वापस _SUCCESS;
पूर्ण

अटल व्योम rtw_suspend_normal(काष्ठा adapter *padapter)
अणु
	काष्ठा net_device *pnetdev = padapter->pnetdev;

	अगर (pnetdev) अणु
		netअगर_carrier_off(pnetdev);
		rtw_netअगर_stop_queue(pnetdev);
	पूर्ण

	rtw_suspend_मुक्त_assoc_resource(padapter);

	अगर ((rtw_hal_check_ips_status(padapter)) || (adapter_to_pwrctl(padapter)->rf_pwrstate == rf_off))
		netdev_dbg(padapter->pnetdev,
			   "%s: ### ERROR #### driver in IPS ####ERROR###!!!\n",
			   __func__);

	rtw_dev_unload(padapter);

	/* sdio_deinit(adapter_to_dvobj(padapter)); */
	अगर (padapter->पूर्णांकf_deinit)
		padapter->पूर्णांकf_deinit(adapter_to_dvobj(padapter));
पूर्ण

पूर्णांक rtw_suspend_common(काष्ठा adapter *padapter)
अणु
	काष्ठा dvobj_priv *psdpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;
	काष्ठा pwrctrl_priv *pwrpriv = dvobj_to_pwrctl(psdpriv);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	पूर्णांक ret = 0;
	अचिन्हित दीर्घ start_समय = jअगरfies;

	netdev_dbg(padapter->pnetdev, " suspend start\n");
	pdbgpriv->dbg_suspend_cnt++;

	pwrpriv->bInSuspend = true;

	जबतक (pwrpriv->bips_processing)
		msleep(1);

	अगर ((!padapter->bup) || (padapter->bDriverStopped) || (padapter->bSurpriseRemoved)) अणु
		pdbgpriv->dbg_suspend_error_cnt++;
		जाओ निकास;
	पूर्ण
	rtw_ps_deny(padapter, PS_DENY_SUSPEND);

	rtw_cancel_all_समयr(padapter);

	LeaveAllPowerSaveModeDirect(padapter);

	rtw_stop_cmd_thपढ़ो(padapter);

	/*  रुको क्रम the latest FW to हटाओ this condition. */
	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		hal_btcoex_SuspendNotअगरy(padapter, 0);
	अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		hal_btcoex_SuspendNotअगरy(padapter, 1);

	rtw_ps_deny_cancel(padapter, PS_DENY_SUSPEND);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		rtw_suspend_normal(padapter);
	अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		rtw_suspend_normal(padapter);
	अन्यथा
		rtw_suspend_normal(padapter);

	netdev_dbg(padapter->pnetdev, "rtw suspend success in %d ms\n",
		   jअगरfies_to_msecs(jअगरfies - start_समय));

निकास:

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_resume_process_normal(काष्ठा adapter *padapter)
अणु
	काष्ठा net_device *pnetdev;
	काष्ठा pwrctrl_priv *pwrpriv;
	काष्ठा mlme_priv *pmlmepriv;
	काष्ठा dvobj_priv *psdpriv;
	काष्ठा debug_priv *pdbgpriv;

	पूर्णांक ret = _SUCCESS;

	अगर (!padapter) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	pnetdev = padapter->pnetdev;
	pwrpriv = adapter_to_pwrctl(padapter);
	pmlmepriv = &padapter->mlmepriv;
	psdpriv = padapter->dvobj;
	pdbgpriv = &psdpriv->drv_dbg;
	/*  पूर्णांकerface init */
	/* अगर (sdio_init(adapter_to_dvobj(padapter)) != _SUCCESS) */
	अगर ((padapter->पूर्णांकf_init) && (padapter->पूर्णांकf_init(adapter_to_dvobj(padapter)) != _SUCCESS)) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण
	rtw_hal_disable_पूर्णांकerrupt(padapter);
	/* अगर (sdio_alloc_irq(adapter_to_dvobj(padapter)) != _SUCCESS) */
	अगर ((padapter->पूर्णांकf_alloc_irq) && (padapter->पूर्णांकf_alloc_irq(adapter_to_dvobj(padapter)) != _SUCCESS)) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	rtw_reset_drv_sw(padapter);
	pwrpriv->bkeepfwalive = false;

	अगर (pm_netdev_खोलो(pnetdev, true) != 0) अणु
		ret = -1;
		pdbgpriv->dbg_resume_error_cnt++;
		जाओ निकास;
	पूर्ण

	netअगर_device_attach(pnetdev);
	netअगर_carrier_on(pnetdev);

	अगर (padapter->pid[1] != 0)
		rtw_संकेत_process(padapter->pid[1], SIGUSR2);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
		अगर (rtw_chk_roam_flags(padapter, RTW_ROAM_ON_RESUME))
			rtw_roaming(padapter, शून्य);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		rtw_ap_restore_network(padapter);
	पूर्ण

निकास:
	वापस ret;
पूर्ण

पूर्णांक rtw_resume_common(काष्ठा adapter *padapter)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ start_समय = jअगरfies;
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	netdev_dbg(padapter->pnetdev, "resume start\n");

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
		rtw_resume_process_normal(padapter);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		rtw_resume_process_normal(padapter);
	पूर्ण अन्यथा अणु
		rtw_resume_process_normal(padapter);
	पूर्ण

	hal_btcoex_SuspendNotअगरy(padapter, 0);

	अगर (pwrpriv) अणु
		pwrpriv->bInSuspend = false;
	पूर्ण
	netdev_dbg(padapter->pnetdev, "%s:%d in %d ms\n", __func__, ret,
		   jअगरfies_to_msecs(jअगरfies - start_समय));

	वापस ret;
पूर्ण
