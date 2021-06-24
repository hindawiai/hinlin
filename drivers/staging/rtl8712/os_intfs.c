<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * os_पूर्णांकfs.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>.
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _OS_INTFS_C_

#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/firmware.h>
#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "xmit_osdep.h"
#समावेश "recv_osdep.h"
#समावेश "rtl871x_ioctl.h"
#समावेश "usb_osintf.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("rtl871x wireless lan driver");
MODULE_AUTHOR("Larry Finger");

अटल अक्षर अगरname[IFNAMSIZ] = "wlan%d";

/* module param शेषs */
अटल पूर्णांक chip_version = RTL8712_2ndCUT;
अटल पूर्णांक rfपूर्णांकfs = HWPI;
अटल पूर्णांक lbkmode = RTL8712_AIR_TRX;
अटल पूर्णांक hci = RTL8712_USB;
अटल पूर्णांक ampdu_enable = 1;/*क्रम enable tx_ampdu*/

/* The video_mode variable is क्रम video mode.*/
/* It may be specअगरy when inserting module with video_mode=1 parameter.*/
अटल पूर्णांक video_mode = 1;   /* enable video mode*/

/*Ndis802_11Infraकाष्ठाure; infra, ad-hoc, स्वतः*/
अटल पूर्णांक network_mode = Ndis802_11IBSS;
अटल पूर्णांक channel = 1;/*ad-hoc support requirement*/
अटल पूर्णांक wireless_mode = WIRELESS_11BG;
अटल पूर्णांक vrtl_carrier_sense = AUTO_VCS;
अटल पूर्णांक vcs_type = RTS_CTS;
अटल पूर्णांक frag_thresh = 2346;
अटल पूर्णांक preamble = PREAMBLE_LONG;/*दीर्घ, लघु, स्वतः*/
अटल पूर्णांक scan_mode = 1;/*active, passive*/
अटल पूर्णांक adhoc_tx_pwr = 1;
अटल पूर्णांक soft_ap;
अटल पूर्णांक smart_ps = 1;
अटल पूर्णांक घातer_mgnt = PS_MODE_ACTIVE;
अटल पूर्णांक radio_enable = 1;
अटल पूर्णांक दीर्घ_retry_lmt = 7;
अटल पूर्णांक लघु_retry_lmt = 7;
अटल पूर्णांक busy_thresh = 40;
अटल पूर्णांक ack_policy = NORMAL_ACK;
अटल पूर्णांक mp_mode;
अटल पूर्णांक software_encrypt;
अटल पूर्णांक software_decrypt;

अटल पूर्णांक wmm_enable;/* शेष is set to disable the wmm.*/
अटल पूर्णांक uapsd_enable;
अटल पूर्णांक uapsd_max_sp = NO_LIMIT;
अटल पूर्णांक uapsd_acbk_en;
अटल पूर्णांक uapsd_acbe_en;
अटल पूर्णांक uapsd_acvi_en;
अटल पूर्णांक uapsd_acvo_en;

अटल पूर्णांक ht_enable = 1;
अटल पूर्णांक cbw40_enable = 1;
अटल पूर्णांक rf_config = RTL8712_RF_1T2R;  /* 1T2R*/
अटल पूर्णांक low_घातer;
/* mac address to use instead of the one stored in Efuse */
अक्षर *r8712_iniपंचांगac;
अटल अक्षर *iniपंचांगac;
/* अगर wअगरi_test = 1, driver will disable the turbo mode and pass it to
 * firmware निजी.
 */
अटल पूर्णांक wअगरi_test;

module_param_string(अगरname, अगरname, माप(अगरname), 0644);
module_param(wअगरi_test, पूर्णांक, 0644);
module_param(iniपंचांगac, अक्षरp, 0644);
module_param(video_mode, पूर्णांक, 0644);
module_param(chip_version, पूर्णांक, 0644);
module_param(rfपूर्णांकfs, पूर्णांक, 0644);
module_param(lbkmode, पूर्णांक, 0644);
module_param(hci, पूर्णांक, 0644);
module_param(network_mode, पूर्णांक, 0644);
module_param(channel, पूर्णांक, 0644);
module_param(mp_mode, पूर्णांक, 0644);
module_param(wmm_enable, पूर्णांक, 0644);
module_param(vrtl_carrier_sense, पूर्णांक, 0644);
module_param(vcs_type, पूर्णांक, 0644);
module_param(busy_thresh, पूर्णांक, 0644);
module_param(ht_enable, पूर्णांक, 0644);
module_param(cbw40_enable, पूर्णांक, 0644);
module_param(ampdu_enable, पूर्णांक, 0644);
module_param(rf_config, पूर्णांक, 0644);
module_param(घातer_mgnt, पूर्णांक, 0644);
module_param(low_घातer, पूर्णांक, 0644);

MODULE_PARM_DESC(अगरname, " Net interface name, wlan%d=default");
MODULE_PARM_DESC(iniपंचांगac, "MAC-Address, default: use FUSE");

अटल पूर्णांक netdev_खोलो(काष्ठा net_device *pnetdev);
अटल पूर्णांक netdev_बंद(काष्ठा net_device *pnetdev);

अटल व्योम loadparam(काष्ठा _adapter *padapter, काष्ठा  net_device *pnetdev)
अणु
	काष्ठा registry_priv  *registry_par = &padapter->registrypriv;

	registry_par->chip_version = (u8)chip_version;
	registry_par->rfपूर्णांकfs = (u8)rfपूर्णांकfs;
	registry_par->lbkmode = (u8)lbkmode;
	registry_par->hci = (u8)hci;
	registry_par->network_mode  = (u8)network_mode;
	स_नकल(registry_par->ssid.Ssid, "ANY", 3);
	registry_par->ssid.SsidLength = 3;
	registry_par->channel = (u8)channel;
	registry_par->wireless_mode = (u8)wireless_mode;
	registry_par->vrtl_carrier_sense = (u8)vrtl_carrier_sense;
	registry_par->vcs_type = (u8)vcs_type;
	registry_par->frag_thresh = (u16)frag_thresh;
	registry_par->preamble = (u8)preamble;
	registry_par->scan_mode = (u8)scan_mode;
	registry_par->adhoc_tx_pwr = (u8)adhoc_tx_pwr;
	registry_par->soft_ap = (u8)soft_ap;
	registry_par->smart_ps = (u8)smart_ps;
	registry_par->घातer_mgnt = (u8)घातer_mgnt;
	registry_par->radio_enable = (u8)radio_enable;
	registry_par->दीर्घ_retry_lmt = (u8)दीर्घ_retry_lmt;
	registry_par->लघु_retry_lmt = (u8)लघु_retry_lmt;
	registry_par->busy_thresh = (u16)busy_thresh;
	registry_par->ack_policy = (u8)ack_policy;
	registry_par->mp_mode = (u8)mp_mode;
	registry_par->software_encrypt = (u8)software_encrypt;
	registry_par->software_decrypt = (u8)software_decrypt;
	/*UAPSD*/
	registry_par->wmm_enable = (u8)wmm_enable;
	registry_par->uapsd_enable = (u8)uapsd_enable;
	registry_par->uapsd_max_sp = (u8)uapsd_max_sp;
	registry_par->uapsd_acbk_en = (u8)uapsd_acbk_en;
	registry_par->uapsd_acbe_en = (u8)uapsd_acbe_en;
	registry_par->uapsd_acvi_en = (u8)uapsd_acvi_en;
	registry_par->uapsd_acvo_en = (u8)uapsd_acvo_en;
	registry_par->ht_enable = (u8)ht_enable;
	registry_par->cbw40_enable = (u8)cbw40_enable;
	registry_par->ampdu_enable = (u8)ampdu_enable;
	registry_par->rf_config = (u8)rf_config;
	registry_par->low_घातer = (u8)low_घातer;
	registry_par->wअगरi_test = (u8)wअगरi_test;
	r8712_iniपंचांगac = iniपंचांगac;
पूर्ण

अटल पूर्णांक r871x_net_set_mac_address(काष्ठा net_device *pnetdev, व्योम *p)
अणु
	काष्ठा _adapter *padapter = netdev_priv(pnetdev);
	काष्ठा sockaddr *addr = p;

	अगर (!padapter->bup)
		ether_addr_copy(pnetdev->dev_addr, addr->sa_data);
	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *r871x_net_get_stats(काष्ठा net_device *pnetdev)
अणु
	काष्ठा _adapter *padapter = netdev_priv(pnetdev);
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

अटल स्थिर काष्ठा net_device_ops rtl8712_netdev_ops = अणु
	.nकरो_खोलो = netdev_खोलो,
	.nकरो_stop = netdev_बंद,
	.nकरो_start_xmit = r8712_xmit_entry,
	.nकरो_set_mac_address = r871x_net_set_mac_address,
	.nकरो_get_stats = r871x_net_get_stats,
	.nकरो_करो_ioctl = r871x_ioctl,
पूर्ण;

काष्ठा net_device *r8712_init_netdev(व्योम)
अणु
	काष्ठा _adapter *padapter;
	काष्ठा net_device *pnetdev;

	pnetdev = alloc_etherdev(माप(काष्ठा _adapter));
	अगर (!pnetdev)
		वापस शून्य;
	अगर (dev_alloc_name(pnetdev, अगरname) < 0) अणु
		म_नकल(अगरname, "wlan%d");
		dev_alloc_name(pnetdev, अगरname);
	पूर्ण
	padapter = netdev_priv(pnetdev);
	padapter->pnetdev = pnetdev;
	pr_info("r8712u: register rtl8712_netdev_ops to netdev_ops\n");
	pnetdev->netdev_ops = &rtl8712_netdev_ops;
	pnetdev->watchकरोg_समयo = HZ; /* 1 second समयout */
	pnetdev->wireless_handlers = (काष्ठा iw_handler_def *)
				     &r871x_handlers_def;
	loadparam(padapter, pnetdev);
	netअगर_carrier_off(pnetdev);
	padapter->pid = 0;  /* Initial the PID value used क्रम HW PBC.*/
	वापस pnetdev;
पूर्ण

अटल u32 start_drv_thपढ़ोs(काष्ठा _adapter *padapter)
अणु
	padapter->cmd_thपढ़ो = kthपढ़ो_run(r8712_cmd_thपढ़ो, padapter, "%s",
					  padapter->pnetdev->name);
	अगर (IS_ERR(padapter->cmd_thपढ़ो))
		वापस _FAIL;
	वापस _SUCCESS;
पूर्ण

व्योम r8712_stop_drv_thपढ़ोs(काष्ठा _adapter *padapter)
अणु
	काष्ठा completion *completion =
		&padapter->cmdpriv.terminate_cmdthपढ़ो_comp;

	/*Below is to terminate r8712_cmd_thपढ़ो & event_thपढ़ो...*/
	complete(&padapter->cmdpriv.cmd_queue_comp);
	अगर (padapter->cmd_thपढ़ो)
		रुको_क्रम_completion_पूर्णांकerruptible(completion);
	padapter->cmdpriv.cmd_seq = 1;
पूर्ण

अटल व्योम start_drv_समयrs(काष्ठा _adapter *padapter)
अणु
	mod_समयr(&padapter->mlmepriv.sitesurveyctrl.sitesurvey_ctrl_समयr,
		  jअगरfies + msecs_to_jअगरfies(5000));
	mod_समयr(&padapter->mlmepriv.wdg_समयr,
		  jअगरfies + msecs_to_jअगरfies(2000));
पूर्ण

व्योम r8712_stop_drv_समयrs(काष्ठा _adapter *padapter)
अणु
	del_समयr_sync(&padapter->mlmepriv.assoc_समयr);
	del_समयr_sync(&padapter->securitypriv.tkip_समयr);
	del_समयr_sync(&padapter->mlmepriv.scan_to_समयr);
	del_समयr_sync(&padapter->mlmepriv.dhcp_समयr);
	del_समयr_sync(&padapter->mlmepriv.wdg_समयr);
	del_समयr_sync(&padapter->mlmepriv.sitesurveyctrl.sitesurvey_ctrl_समयr);
पूर्ण

अटल व्योम init_शेष_value(काष्ठा _adapter *padapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	/*xmit_priv*/
	pxmitpriv->vcs_setting = pregistrypriv->vrtl_carrier_sense;
	pxmitpriv->vcs = pregistrypriv->vcs_type;
	pxmitpriv->vcs_type = pregistrypriv->vcs_type;
	pxmitpriv->rts_thresh = pregistrypriv->rts_thresh;
	pxmitpriv->frag_len = pregistrypriv->frag_thresh;
	/* mlme_priv */
	/* Maybe someday we should नाम this variable to "active_mode"(Jeff)*/
	pmlmepriv->passive_mode = 1; /* 1: active, 0: passive. */
	/*ht_priv*/
	अणु
		पूर्णांक i;
		काष्ठा ht_priv	 *phtpriv = &pmlmepriv->htpriv;

		phtpriv->ampdu_enable = false;/*set to disabled*/
		क्रम (i = 0; i < 16; i++)
			phtpriv->baddbareq_issued[i] = false;
	पूर्ण
	/*security_priv*/
	psecuritypriv->sw_encrypt = pregistrypriv->software_encrypt;
	psecuritypriv->sw_decrypt = pregistrypriv->software_decrypt;
	psecuritypriv->binstallGrpkey = _FAIL;
	/*pwrctrl_priv*/
	/*registry_priv*/
	r8712_init_registrypriv_dev_network(padapter);
	r8712_update_registrypriv_dev_network(padapter);
	/*misc.*/
पूर्ण

पूर्णांक r8712_init_drv_sw(काष्ठा _adapter *padapter)
अणु
	पूर्णांक ret;

	ret = r8712_init_cmd_priv(&padapter->cmdpriv);
	अगर (ret)
		वापस ret;
	padapter->cmdpriv.padapter = padapter;
	ret = r8712_init_evt_priv(&padapter->evtpriv);
	अगर (ret)
		वापस ret;
	ret = r8712_init_mlme_priv(padapter);
	अगर (ret)
		वापस ret;
	_r8712_init_xmit_priv(&padapter->xmitpriv, padapter);
	_r8712_init_recv_priv(&padapter->recvpriv, padapter);
	स_रखो((अचिन्हित अक्षर *)&padapter->securitypriv, 0,
	       माप(काष्ठा security_priv));
	समयr_setup(&padapter->securitypriv.tkip_समयr,
		    r8712_use_tkipkey_handler, 0);
	ret = _r8712_init_sta_priv(&padapter->stapriv);
	अगर (ret)
		वापस ret;
	padapter->stapriv.padapter = padapter;
	r8712_init_bcmc_stainfo(padapter);
	r8712_init_pwrctrl_priv(padapter);
	mp871xinit(padapter);
	init_शेष_value(padapter);
	r8712_InitSwLeds(padapter);
	वापस ret;
पूर्ण

व्योम r8712_मुक्त_drv_sw(काष्ठा _adapter *padapter)
अणु
	काष्ठा net_device *pnetdev = padapter->pnetdev;

	r8712_मुक्त_cmd_priv(&padapter->cmdpriv);
	r8712_मुक्त_evt_priv(&padapter->evtpriv);
	r8712_DeInitSwLeds(padapter);
	r8712_मुक्त_mlme_priv(&padapter->mlmepriv);
	r8712_मुक्त_io_queue(padapter);
	_मुक्त_xmit_priv(&padapter->xmitpriv);
	_r8712_मुक्त_sta_priv(&padapter->stapriv);
	_r8712_मुक्त_recv_priv(&padapter->recvpriv);
	mp871xdeinit(padapter);
	अगर (pnetdev)
		मुक्त_netdev(pnetdev);
पूर्ण

अटल व्योम enable_video_mode(काष्ठा _adapter *padapter, पूर्णांक cbw40_value)
अणु
	/*   bit 8:
	 *   1 -> enable video mode to 96B AP
	 *   0 -> disable video mode to 96B AP
	 *   bit 9:
	 *   1 -> enable 40MHz mode
	 *   0 -> disable 40MHz mode
	 *   bit 10:
	 *   1 -> enable STBC
	 *   0 -> disable STBC
	 */
	u32  पूर्णांकcmd = 0xf4000500;   /* enable bit8, bit10*/

	अगर (cbw40_value) अणु
		/* अगर the driver supports the 40M bandwidth,
		 * we can enable the bit 9.
		 */
		पूर्णांकcmd |= 0x200;
	पूर्ण
	r8712_fw_cmd(padapter, पूर्णांकcmd);
पूर्ण

/*
 *
 * This function पूर्णांकends to handle the activation of an पूर्णांकerface
 * i.e. when it is brought Up/Active from a Down state.
 *
 */
अटल पूर्णांक netdev_खोलो(काष्ठा net_device *pnetdev)
अणु
	काष्ठा _adapter *padapter = netdev_priv(pnetdev);

	mutex_lock(&padapter->mutex_start);
	अगर (!padapter->bup) अणु
		padapter->driver_stopped = false;
		padapter->surprise_हटाओd = false;
		padapter->bup = true;
		अगर (rtl871x_hal_init(padapter) != _SUCCESS)
			जाओ netdev_खोलो_error;
		अगर (!r8712_iniपंचांगac) अणु
			/* Use the mac address stored in the Efuse */
			स_नकल(pnetdev->dev_addr,
			       padapter->eeprompriv.mac_addr, ETH_ALEN);
		पूर्ण अन्यथा अणु
			/* We have to inक्रमm f/w to use user-supplied MAC
			 * address.
			 */
			msleep(200);
			r8712_setMacAddr_cmd(padapter, (u8 *)pnetdev->dev_addr);
			/*
			 * The "myid" function will get the wअगरi mac address
			 * from eeprompriv काष्ठाure instead of netdev
			 * काष्ठाure. So, we have to overग_लिखो the mac_addr
			 * stored in the eeprompriv काष्ठाure. In this हाल,
			 * the real mac address won't be used anymore. So that,
			 * the eeprompriv.mac_addr should store the mac which
			 * users specअगरy.
			 */
			स_नकल(padapter->eeprompriv.mac_addr,
			       pnetdev->dev_addr, ETH_ALEN);
		पूर्ण
		अगर (start_drv_thपढ़ोs(padapter) != _SUCCESS)
			जाओ netdev_खोलो_error;
		अगर (!padapter->dvobjpriv.inirp_init)
			जाओ netdev_खोलो_error;
		अन्यथा
			padapter->dvobjpriv.inirp_init(padapter);
		r8712_set_ps_mode(padapter, padapter->registrypriv.घातer_mgnt,
				  padapter->registrypriv.smart_ps);
	पूर्ण
	अगर (!netअगर_queue_stopped(pnetdev))
		netअगर_start_queue(pnetdev);
	अन्यथा
		netअगर_wake_queue(pnetdev);

	अगर (video_mode)
		enable_video_mode(padapter, cbw40_enable);
	/* start driver mlme relation समयr */
	start_drv_समयrs(padapter);
	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_NO_LINK);
	mutex_unlock(&padapter->mutex_start);
	वापस 0;
netdev_खोलो_error:
	padapter->bup = false;
	netअगर_carrier_off(pnetdev);
	netअगर_stop_queue(pnetdev);
	mutex_unlock(&padapter->mutex_start);
	वापस -1;
पूर्ण

/*
 *
 * This function पूर्णांकends to handle the shutकरोwn of an पूर्णांकerface
 * i.e. when it is brought Down from an Up/Active state.
 *
 */
अटल पूर्णांक netdev_बंद(काष्ठा net_device *pnetdev)
अणु
	काष्ठा _adapter *padapter = netdev_priv(pnetdev);

	/* Close LED*/
	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_POWER_OFF);
	msleep(200);

	/*s1.*/
	अगर (pnetdev) अणु
		अगर (!netअगर_queue_stopped(pnetdev))
			netअगर_stop_queue(pnetdev);
	पूर्ण
	/*s2.*/
	/*s2-1.  issue disassoc_cmd to fw*/
	r8712_disassoc_cmd(padapter);
	/*s2-2.  indicate disconnect to os*/
	r8712_ind_disconnect(padapter);
	/*s2-3.*/
	r8712_मुक्त_assoc_resources(padapter);
	/*s2-4.*/
	r8712_मुक्त_network_queue(padapter);
	वापस 0;
पूर्ण

#समावेश "mlme_osdep.h"
