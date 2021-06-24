<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#घोषणा pr_fmt(fmt) "R8188EU: " fmt
#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <recv_osdep.h>
#समावेश <xmit_osdep.h>
#समावेश <hal_पूर्णांकf.h>
#समावेश <linux/usb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <mon.h>
#समावेश <osdep_पूर्णांकf.h>

#समावेश <usb_ops_linux.h>
#समावेश <rtw_ioctl.h>

#समावेश "rtl8188e_hal.h"

#घोषणा USB_VENDER_ID_REALTEK		0x0bda

/* DID_USB_v916_20130116 */
अटल स्थिर काष्ठा usb_device_id rtw_usb_id_tbl[] = अणु
	/*=== Realtek demoboard ===*/
	अणुUSB_DEVICE(USB_VENDER_ID_REALTEK, 0x8179)पूर्ण, /* 8188EUS */
	अणुUSB_DEVICE(USB_VENDER_ID_REALTEK, 0x0179)पूर्ण, /* 8188ETV */
	/*=== Customer ID ===*/
	/****** 8188EUS ********/
	अणुUSB_DEVICE(0x056e, 0x4008)पूर्ण, /* Elecom WDC-150SU2M */
	अणुUSB_DEVICE(0x07b8, 0x8179)पूर्ण, /* Abocom - Abocom */
	अणुUSB_DEVICE(0x0B05, 0x18F0)पूर्ण, /* ASUS USB-N10 Nano B1 */
	अणुUSB_DEVICE(0x2001, 0x330F)पूर्ण, /* DLink DWA-125 REV D1 */
	अणुUSB_DEVICE(0x2001, 0x3310)पूर्ण, /* Dlink DWA-123 REV D1 */
	अणुUSB_DEVICE(0x2001, 0x3311)पूर्ण, /* DLink GO-USB-N150 REV B1 */
	अणुUSB_DEVICE(0x2001, 0x331B)पूर्ण, /* D-Link DWA-121 rev B1 */
	अणुUSB_DEVICE(0x2357, 0x010c)पूर्ण, /* TP-Link TL-WN722N v2 */
	अणुUSB_DEVICE(0x2357, 0x0111)पूर्ण, /* TP-Link TL-WN727N v5.21 */
	अणुUSB_DEVICE(0x2C4E, 0x0102)पूर्ण, /* MERCUSYS MW150US v2 */
	अणुUSB_DEVICE(0x0df6, 0x0076)पूर्ण, /* Sitecom N150 v2 */
	अणुUSB_DEVICE(0x7392, 0xb811)पूर्ण, /* Edimax EW-7811UN V2 */
	अणुUSB_DEVICE(USB_VENDER_ID_REALTEK, 0xffef)पूर्ण, /* Rosewill RNX-N150NUB */
	अणुपूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, rtw_usb_id_tbl);

अटल पूर्णांक usb_dvobj_init(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	पूर्णांक	i;
	काष्ठा dvobj_priv *pdvobjpriv;
	काष्ठा usb_host_config		*phost_conf;
	काष्ठा usb_config_descriptor	*pconf_desc;
	काष्ठा usb_host_पूर्णांकerface	*phost_अगरace;
	काष्ठा usb_पूर्णांकerface_descriptor	*pअगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor	*pendp_desc;
	काष्ठा usb_device	*pusbd;

	pdvobjpriv = kzalloc(माप(*pdvobjpriv), GFP_KERNEL);
	अगर (!pdvobjpriv)
		वापस -ENOMEM;

	pdvobjpriv->pusbपूर्णांकf = usb_पूर्णांकf;
	pusbd = पूर्णांकerface_to_usbdev(usb_पूर्णांकf);
	pdvobjpriv->pusbdev = pusbd;
	usb_set_पूर्णांकfdata(usb_पूर्णांकf, pdvobjpriv);

	pdvobjpriv->RtNumInPipes = 0;
	pdvobjpriv->RtNumOutPipes = 0;

	phost_conf = pusbd->actconfig;
	pconf_desc = &phost_conf->desc;

	phost_अगरace = usb_पूर्णांकf->cur_altsetting;
	pअगरace_desc = &phost_अगरace->desc;

	pdvobjpriv->NumInterfaces = pconf_desc->bNumInterfaces;
	pdvobjpriv->InterfaceNumber = pअगरace_desc->bInterfaceNumber;

	क्रम (i = 0; i < pअगरace_desc->bNumEndpoपूर्णांकs; i++) अणु
		पूर्णांक ep_num;

		pendp_desc = &phost_अगरace->endpoपूर्णांक[i].desc;

		ep_num = usb_endpoपूर्णांक_num(pendp_desc);

		अगर (usb_endpoपूर्णांक_is_bulk_in(pendp_desc)) अणु
			pdvobjpriv->RtInPipe[pdvobjpriv->RtNumInPipes] = ep_num;
			pdvobjpriv->RtNumInPipes++;
		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_पूर्णांक_in(pendp_desc)) अणु
			pdvobjpriv->RtInPipe[pdvobjpriv->RtNumInPipes] = ep_num;
			pdvobjpriv->RtNumInPipes++;
		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(pendp_desc)) अणु
			pdvobjpriv->RtOutPipe[pdvobjpriv->RtNumOutPipes] =
				ep_num;
			pdvobjpriv->RtNumOutPipes++;
		पूर्ण
	पूर्ण

	अगर (pusbd->speed == USB_SPEED_HIGH)
		pdvobjpriv->ishighspeed = true;
	अन्यथा
		pdvobjpriv->ishighspeed = false;

	mutex_init(&pdvobjpriv->usb_venकरोr_req_mutex);
	usb_get_dev(pusbd);

	वापस 0;
पूर्ण

अटल व्योम usb_dvobj_deinit(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	काष्ठा dvobj_priv *dvobj = usb_get_पूर्णांकfdata(usb_पूर्णांकf);

	usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);
	अगर (dvobj) अणु
		/* Modअगरy condition क्रम 92DU DMDP 2010.11.18, by Thomas */
		अगर ((dvobj->NumInterfaces != 2 &&
		     dvobj->NumInterfaces != 3) ||
		    (dvobj->InterfaceNumber == 1)) अणु
			अगर (पूर्णांकerface_to_usbdev(usb_पूर्णांकf)->state !=
			    USB_STATE_NOTATTACHED) अणु
				/* If we didn't unplug usb करोngle and
				 * हटाओ/insert module, driver fails
				 * on sitesurvey क्रम the first समय when
				 * device is up . Reset usb port क्रम sitesurvey
				 * fail issue.
				 */
				pr_debug("usb attached..., try to reset usb device\n");
				usb_reset_device(पूर्णांकerface_to_usbdev(usb_पूर्णांकf));
			पूर्ण
		पूर्ण

		mutex_destroy(&dvobj->usb_venकरोr_req_mutex);
		kमुक्त(dvobj);
	पूर्ण

	usb_put_dev(पूर्णांकerface_to_usbdev(usb_पूर्णांकf));
पूर्ण

व्योम usb_पूर्णांकf_stop(काष्ठा adapter *padapter)
अणु
	RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_, ("+%s\n", __func__));

	/* disable_hw_पूर्णांकerrupt */
	अगर (!padapter->bSurpriseRemoved) अणु
		/* device still exists, so driver can करो i/o operation */
		/* TODO: */
		RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_,
			 ("SurpriseRemoved == false\n"));
	पूर्ण

	/* cancel in irp */
	rtw_hal_inirp_deinit(padapter);

	/* cancel out irp */
	usb_ग_लिखो_port_cancel(padapter);

	/* toकरो:cancel other irps */

	RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_, ("-%s\n", __func__));
पूर्ण

अटल व्योम rtw_dev_unload(काष्ठा adapter *padapter)
अणु
	RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_, ("+%s\n", __func__));

	अगर (padapter->bup) अणु
		pr_debug("===> %s\n", __func__);
		padapter->bDriverStopped = true;
		अगर (padapter->xmitpriv.ack_tx)
			rtw_ack_tx_करोne(&padapter->xmitpriv, RTW_SCTX_DONE_DRV_STOP);
		/* s3. */
		usb_पूर्णांकf_stop(padapter);
		/* s4. */
		अगर (!padapter->pwrctrlpriv.bInternalAutoSuspend)
			rtw_stop_drv_thपढ़ोs(padapter);

		/* s5. */
		अगर (!padapter->bSurpriseRemoved) अणु
			rtw_hal_deinit(padapter);
			padapter->bSurpriseRemoved = true;
		पूर्ण

		padapter->bup = false;
	पूर्ण अन्यथा अणु
		RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_,
			 ("r871x_dev_unload():padapter->bup == false\n"));
	पूर्ण

	pr_debug("<=== %s\n", __func__);

	RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_, ("-%s\n", __func__));
पूर्ण

अटल पूर्णांक rtw_suspend(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf, pm_message_t message)
अणु
	काष्ठा dvobj_priv *dvobj = usb_get_पूर्णांकfdata(pusb_पूर्णांकf);
	काष्ठा adapter *padapter = dvobj->अगर1;
	काष्ठा net_device *pnetdev = padapter->pnetdev;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	अचिन्हित दीर्घ start_समय = jअगरfies;

	pr_debug("==> %s (%s:%d)\n", __func__, current->comm, current->pid);

	अगर ((!padapter->bup) || (padapter->bDriverStopped) ||
	    (padapter->bSurpriseRemoved)) अणु
		pr_debug("padapter->bup=%d bDriverStopped=%d bSurpriseRemoved = %d\n",
			 padapter->bup, padapter->bDriverStopped,
			 padapter->bSurpriseRemoved);
		जाओ निकास;
	पूर्ण

	pwrpriv->bInSuspend = true;
	rtw_cancel_all_समयr(padapter);
	LeaveAllPowerSaveMode(padapter);

	mutex_lock(&pwrpriv->mutex_lock);
	/* s1. */
	अगर (pnetdev) अणु
		netअगर_carrier_off(pnetdev);
		netअगर_tx_stop_all_queues(pnetdev);
	पूर्ण

	/* s2. */
	rtw_disassoc_cmd(padapter, 0, false);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) &&
	    check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		pr_debug("%s:%d %s(%pM), length:%d assoc_ssid.length:%d\n",
			 __func__, __LINE__,
			 pmlmepriv->cur_network.network.ssid.ssid,
			 pmlmepriv->cur_network.network.MacAddress,
			 pmlmepriv->cur_network.network.ssid.ssid_length,
			 pmlmepriv->assoc_ssid.ssid_length);

		pmlmepriv->to_roaming = 1;
	पूर्ण
	/* s2-2.  indicate disconnect to os */
	rtw_indicate_disconnect(padapter);
	/* s2-3. */
	rtw_मुक्त_assoc_resources(padapter);
	/* s2-4. */
	rtw_मुक्त_network_queue(padapter, true);

	rtw_dev_unload(padapter);
	mutex_unlock(&pwrpriv->mutex_lock);

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		rtw_indicate_scan_करोne(padapter, 1);

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING))
		rtw_indicate_disconnect(padapter);

निकास:
	pr_debug("<===  %s .............. in %dms\n", __func__,
		 jअगरfies_to_msecs(jअगरfies - start_समय));

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_resume_process(काष्ठा adapter *padapter)
अणु
	काष्ठा net_device *pnetdev;
	काष्ठा pwrctrl_priv *pwrpriv = शून्य;
	पूर्णांक ret = -1;
	अचिन्हित दीर्घ start_समय = jअगरfies;

	pr_debug("==> %s (%s:%d)\n", __func__, current->comm, current->pid);

	अगर (padapter) अणु
		pnetdev = padapter->pnetdev;
		pwrpriv = &padapter->pwrctrlpriv;
	पूर्ण अन्यथा अणु
		जाओ निकास;
	पूर्ण

	mutex_lock(&pwrpriv->mutex_lock);
	rtw_reset_drv_sw(padapter);
	pwrpriv->bkeepfwalive = false;

	pr_debug("bkeepfwalive(%x)\n", pwrpriv->bkeepfwalive);
	अगर (netdev_खोलो(pnetdev) != 0) अणु
		mutex_unlock(&pwrpriv->mutex_lock);
		जाओ निकास;
	पूर्ण

	netअगर_device_attach(pnetdev);
	netअगर_carrier_on(pnetdev);

	mutex_unlock(&pwrpriv->mutex_lock);

	rtw_roaming(padapter, शून्य);

	ret = 0;
निकास:
	अगर (pwrpriv)
		pwrpriv->bInSuspend = false;
	pr_debug("<===  %s return %d.............. in %dms\n", __func__,
		 ret, jअगरfies_to_msecs(jअगरfies - start_समय));

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_resume(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf)
अणु
	काष्ठा dvobj_priv *dvobj = usb_get_पूर्णांकfdata(pusb_पूर्णांकf);
	काष्ठा adapter *padapter = dvobj->अगर1;

	वापस rtw_resume_process(padapter);
पूर्ण

/*
 * drv_init() - a device potentially क्रम us
 *
 * notes: drv_init() is called when the bus driver has located
 * a card क्रम us to support.
 *        We accept the new device by वापसing 0.
 */

अटल पूर्णांक rtw_usb_अगर1_init(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf)
अणु
	काष्ठा dvobj_priv *dvobj = usb_get_पूर्णांकfdata(pusb_पूर्णांकf);
	काष्ठा adapter *padapter;
	काष्ठा net_device *pnetdev;
	काष्ठा net_device *pmondev;
	पूर्णांक err = 0;

	pnetdev = rtw_init_netdev();
	अगर (!pnetdev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(pnetdev, dvobj_to_dev(dvobj));

	padapter = netdev_priv(pnetdev);
	padapter->dvobj = dvobj;
	dvobj->अगर1 = padapter;

	padapter->bDriverStopped = true;
	mutex_init(&padapter->hw_init_mutex);

	अगर (padapter->registrypriv.monitor_enable) अणु
		pmondev = rtl88eu_mon_init();
		अगर (!pmondev)
			netdev_warn(pnetdev, "Failed to initialize monitor interface");
		padapter->pmondev = pmondev;
	पूर्ण

	padapter->HalData = kzalloc(माप(काष्ठा hal_data_8188e), GFP_KERNEL);
	अगर (!padapter->HalData) अणु
		DBG_88E("Failed to allocate memory for HAL data\n");
		err = -ENOMEM;
		जाओ मुक्त_adapter;
	पूर्ण

	/* step पढ़ो_chip_version */
	rtw_hal_पढ़ो_chip_version(padapter);

	/* step usb endpoपूर्णांक mapping */
	rtw_hal_chip_configure(padapter);

	/* step पढ़ो efuse/eeprom data and get mac_addr */
	rtw_hal_पढ़ो_chip_info(padapter);

	/* step 5. */
	अगर (rtw_init_drv_sw(padapter) == _FAIL) अणु
		RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_,
			 ("Initialize driver software resource Failed!\n"));
		err = -ENOMEM;
		जाओ मुक्त_hal_data;
	पूर्ण

#अगर_घोषित CONFIG_PM
	अगर (padapter->pwrctrlpriv.bSupportRemoteWakeup) अणु
		dvobj->pusbdev->करो_remote_wakeup = 1;
		pusb_पूर्णांकf->needs_remote_wakeup = 1;
		device_init_wakeup(&pusb_पूर्णांकf->dev, 1);
		pr_debug("\n  padapter->pwrctrlpriv.bSupportRemoteWakeup~~~[%d]~~~\n",
			 device_may_wakeup(&pusb_पूर्णांकf->dev));
	पूर्ण
#पूर्ण_अगर

	/* 2012-07-11 Move here to prevent the 8723AS-VAU BT स्वतः suspend influence */
	अगर (usb_स्वतःpm_get_पूर्णांकerface(pusb_पूर्णांकf) < 0)
		pr_debug("can't get autopm:\n");

	/*  alloc dev name after पढ़ो efuse. */
	अगर (dev_alloc_name(pnetdev, padapter->registrypriv.अगरname) < 0)
		RT_TRACE(_module_os_पूर्णांकfs_c_, _drv_err_, ("dev_alloc_name, fail!\n"));

	netअगर_carrier_off(pnetdev);

	rtw_macaddr_cfg(padapter->eeprompriv.mac_addr);
	स_नकल(pnetdev->dev_addr, padapter->eeprompriv.mac_addr, ETH_ALEN);
	pr_debug("MAC Address from pnetdev->dev_addr =  %pM\n",
		 pnetdev->dev_addr);

	/* step 6. Tell the network stack we exist */
	err = रेजिस्टर_netdev(pnetdev);
	अगर (err) अणु
		RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_, ("register_netdev() failed\n"));
		जाओ मुक्त_hal_data;
	पूर्ण

	pr_debug("bDriverStopped:%d, bSurpriseRemoved:%d, bup:%d, hw_init_completed:%d\n"
		, padapter->bDriverStopped
		, padapter->bSurpriseRemoved
		, padapter->bup
		, padapter->hw_init_completed
	);

	वापस 0;

मुक्त_hal_data:
	kमुक्त(padapter->HalData);
मुक्त_adapter:
	मुक्त_netdev(pnetdev);
	वापस err;
पूर्ण

अटल व्योम rtw_usb_अगर1_deinit(काष्ठा adapter *अगर1)
अणु
	काष्ठा net_device *pnetdev = अगर1->pnetdev;
	काष्ठा mlme_priv *pmlmepriv = &अगर1->mlmepriv;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED))
		rtw_disassoc_cmd(अगर1, 0, false);

#अगर_घोषित CONFIG_88EU_AP_MODE
	मुक्त_mlme_ap_info(अगर1);
#पूर्ण_अगर

	अगर (pnetdev)
		unरेजिस्टर_netdev(pnetdev); /* will call netdev_बंद() */

	rtl88eu_mon_deinit(अगर1->pmondev);
	rtw_cancel_all_समयr(अगर1);

	rtw_dev_unload(अगर1);
	pr_debug("+r871xu_dev_remove, hw_init_completed=%d\n",
		 अगर1->hw_init_completed);
	rtw_मुक्त_drv_sw(अगर1);
	अगर (pnetdev)
		मुक्त_netdev(pnetdev);
पूर्ण

अटल पूर्णांक rtw_drv_init(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf, स्थिर काष्ठा usb_device_id *pdid)
अणु
	पूर्णांक err;

	err = usb_dvobj_init(pusb_पूर्णांकf);
	अगर (err) अणु
		pr_debug("usb_dvobj_init failed\n");
		वापस err;
	पूर्ण

	err = rtw_usb_अगर1_init(pusb_पूर्णांकf);
	अगर (err) अणु
		pr_debug("rtw_usb_if1_init failed\n");
		usb_dvobj_deinit(pusb_पूर्णांकf);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * dev_हटाओ() - our device is being हटाओd
 *
 * rmmod module & unplug(SurpriseRemoved) will call r871xu_dev_हटाओ() => how to recognize both
 */
अटल व्योम rtw_dev_हटाओ(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf)
अणु
	काष्ठा dvobj_priv *dvobj = usb_get_पूर्णांकfdata(pusb_पूर्णांकf);
	काष्ठा adapter *padapter = dvobj->अगर1;

	pr_debug("+%s\n", __func__);
	RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_, ("+dev_remove()\n"));

	अगर (!pusb_पूर्णांकf->unरेजिस्टरing)
		padapter->bSurpriseRemoved = true;

	rtw_pm_set_ips(padapter, IPS_NONE);
	rtw_pm_set_lps(padapter, PS_MODE_ACTIVE);

	LeaveAllPowerSaveMode(padapter);

	rtw_usb_अगर1_deinit(padapter);

	usb_dvobj_deinit(pusb_पूर्णांकf);

	RT_TRACE(_module_hci_पूर्णांकfs_c_, _drv_err_, ("-dev_remove()\n"));
	pr_debug("-r871xu_dev_remove, done\n");
पूर्ण

अटल काष्ठा usb_driver rtl8188e_usb_drv = अणु
	.name = "r8188eu",
	.probe = rtw_drv_init,
	.disconnect = rtw_dev_हटाओ,
	.id_table = rtw_usb_id_tbl,
	.suspend =  rtw_suspend,
	.resume = rtw_resume,
	.reset_resume = rtw_resume,
पूर्ण;

module_usb_driver(rtl8188e_usb_drv)
