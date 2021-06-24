<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * usb_पूर्णांकf.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _HCI_INTF_C_

#समावेश <linux/usb.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "recv_osdep.h"
#समावेश "xmit_osdep.h"
#समावेश "rtl8712_efuse.h"
#समावेश "usb_ops.h"
#समावेश "usb_osintf.h"

अटल काष्ठा usb_पूर्णांकerface *pपूर्णांकf;

अटल पूर्णांक r871xu_drv_init(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *pdid);

अटल व्योम r871xu_dev_हटाओ(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf);

अटल स्थिर काष्ठा usb_device_id rtl871x_usb_id_tbl[] = अणु

/* RTL8188SU */
	/* Realtek */
	अणुUSB_DEVICE(0x0BDA, 0x8171)पूर्ण,
	अणुUSB_DEVICE(0x0bda, 0x8173)पूर्ण,
	अणुUSB_DEVICE(0x0bda, 0x8712)पूर्ण,
	अणुUSB_DEVICE(0x0bda, 0x8713)पूर्ण,
	अणुUSB_DEVICE(0x0bda, 0xC512)पूर्ण,
	/* Abocom */
	अणुUSB_DEVICE(0x07B8, 0x8188)पूर्ण,
	/* ASUS */
	अणुUSB_DEVICE(0x0B05, 0x1786)पूर्ण,
	अणुUSB_DEVICE(0x0B05, 0x1791)पूर्ण, /* 11n mode disable */
	/* Belkin */
	अणुUSB_DEVICE(0x050D, 0x945A)पूर्ण,
	/* ISY IWL - Belkin clone */
	अणुUSB_DEVICE(0x050D, 0x11F1)पूर्ण,
	/* Corega */
	अणुUSB_DEVICE(0x07AA, 0x0047)पूर्ण,
	/* D-Link */
	अणुUSB_DEVICE(0x2001, 0x3306)पूर्ण,
	अणुUSB_DEVICE(0x07D1, 0x3306)पूर्ण, /* 11n mode disable */
	/* Edimax */
	अणुUSB_DEVICE(0x7392, 0x7611)पूर्ण,
	/* EnGenius */
	अणुUSB_DEVICE(0x1740, 0x9603)पूर्ण,
	/* Hawking */
	अणुUSB_DEVICE(0x0E66, 0x0016)पूर्ण,
	/* Hercules */
	अणुUSB_DEVICE(0x06F8, 0xE034)पूर्ण,
	अणुUSB_DEVICE(0x06F8, 0xE032)पूर्ण,
	/* Logitec */
	अणुUSB_DEVICE(0x0789, 0x0167)पूर्ण,
	/* PCI */
	अणुUSB_DEVICE(0x2019, 0xAB28)पूर्ण,
	अणुUSB_DEVICE(0x2019, 0xED16)पूर्ण,
	/* Sitecom */
	अणुUSB_DEVICE(0x0DF6, 0x0057)पूर्ण,
	अणुUSB_DEVICE(0x0DF6, 0x0045)पूर्ण,
	अणुUSB_DEVICE(0x0DF6, 0x0059)पूर्ण, /* 11n mode disable */
	अणुUSB_DEVICE(0x0DF6, 0x004B)पूर्ण,
	अणुUSB_DEVICE(0x0DF6, 0x005B)पूर्ण,
	अणुUSB_DEVICE(0x0DF6, 0x005D)पूर्ण,
	अणुUSB_DEVICE(0x0DF6, 0x0063)पूर्ण,
	/* Sweex */
	अणुUSB_DEVICE(0x177F, 0x0154)पूर्ण,
	/* Thinkware */
	अणुUSB_DEVICE(0x0BDA, 0x5077)पूर्ण,
	/* Toshiba */
	अणुUSB_DEVICE(0x1690, 0x0752)पूर्ण,
	/* - */
	अणुUSB_DEVICE(0x20F4, 0x646B)पूर्ण,
	अणुUSB_DEVICE(0x083A, 0xC512)पूर्ण,
	अणुUSB_DEVICE(0x25D4, 0x4CA1)पूर्ण,
	अणुUSB_DEVICE(0x25D4, 0x4CAB)पूर्ण,

/* RTL8191SU */
	/* Realtek */
	अणुUSB_DEVICE(0x0BDA, 0x8172)पूर्ण,
	अणुUSB_DEVICE(0x0BDA, 0x8192)पूर्ण,
	/* Amigo */
	अणुUSB_DEVICE(0x0EB0, 0x9061)पूर्ण,
	/* ASUS/EKB */
	अणुUSB_DEVICE(0x13D3, 0x3323)पूर्ण,
	अणुUSB_DEVICE(0x13D3, 0x3311)पूर्ण, /* 11n mode disable */
	अणुUSB_DEVICE(0x13D3, 0x3342)पूर्ण,
	/* ASUS/EKBLenovo */
	अणुUSB_DEVICE(0x13D3, 0x3333)पूर्ण,
	अणुUSB_DEVICE(0x13D3, 0x3334)पूर्ण,
	अणुUSB_DEVICE(0x13D3, 0x3335)पूर्ण, /* 11n mode disable */
	अणुUSB_DEVICE(0x13D3, 0x3336)पूर्ण, /* 11n mode disable */
	/* ASUS/Media BOX */
	अणुUSB_DEVICE(0x13D3, 0x3309)पूर्ण,
	/* Belkin */
	अणुUSB_DEVICE(0x050D, 0x815F)पूर्ण,
	/* D-Link */
	अणुUSB_DEVICE(0x07D1, 0x3302)पूर्ण,
	अणुUSB_DEVICE(0x07D1, 0x3300)पूर्ण,
	अणुUSB_DEVICE(0x07D1, 0x3303)पूर्ण,
	/* Edimax */
	अणुUSB_DEVICE(0x7392, 0x7612)पूर्ण,
	/* EnGenius */
	अणुUSB_DEVICE(0x1740, 0x9605)पूर्ण,
	/* Guillemot */
	अणुUSB_DEVICE(0x06F8, 0xE031)पूर्ण,
	/* Hawking */
	अणुUSB_DEVICE(0x0E66, 0x0015)पूर्ण,
	/* Mediao */
	अणुUSB_DEVICE(0x13D3, 0x3306)पूर्ण,
	/* PCI */
	अणुUSB_DEVICE(0x2019, 0xED18)पूर्ण,
	अणुUSB_DEVICE(0x2019, 0x4901)पूर्ण,
	/* Sitecom */
	अणुUSB_DEVICE(0x0DF6, 0x0058)पूर्ण,
	अणुUSB_DEVICE(0x0DF6, 0x0049)पूर्ण,
	अणुUSB_DEVICE(0x0DF6, 0x004C)पूर्ण,
	अणुUSB_DEVICE(0x0DF6, 0x006C)पूर्ण,
	अणुUSB_DEVICE(0x0DF6, 0x0064)पूर्ण,
	/* Skyworth */
	अणुUSB_DEVICE(0x14b2, 0x3300)पूर्ण,
	अणुUSB_DEVICE(0x14b2, 0x3301)पूर्ण,
	अणुUSB_DEVICE(0x14B2, 0x3302)पूर्ण,
	/* - */
	अणुUSB_DEVICE(0x04F2, 0xAFF2)पूर्ण,
	अणुUSB_DEVICE(0x04F2, 0xAFF5)पूर्ण,
	अणुUSB_DEVICE(0x04F2, 0xAFF6)पूर्ण,
	अणुUSB_DEVICE(0x13D3, 0x3339)पूर्ण,
	अणुUSB_DEVICE(0x13D3, 0x3340)पूर्ण, /* 11n mode disable */
	अणुUSB_DEVICE(0x13D3, 0x3341)पूर्ण, /* 11n mode disable */
	अणुUSB_DEVICE(0x13D3, 0x3310)पूर्ण,
	अणुUSB_DEVICE(0x13D3, 0x3325)पूर्ण,

/* RTL8192SU */
	/* Realtek */
	अणुUSB_DEVICE(0x0BDA, 0x8174)पूर्ण,
	/* Belkin */
	अणुUSB_DEVICE(0x050D, 0x845A)पूर्ण,
	/* Corega */
	अणुUSB_DEVICE(0x07AA, 0x0051)पूर्ण,
	/* Edimax */
	अणुUSB_DEVICE(0x7392, 0x7622)पूर्ण,
	/* NEC */
	अणुUSB_DEVICE(0x0409, 0x02B6)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, rtl871x_usb_id_tbl);

अटल काष्ठा specअगरic_device_id specअगरic_device_id_tbl[] = अणु
	अणु.idVenकरोr = 0x0b05, .idProduct = 0x1791,
		 .flags = SPEC_DEV_ID_DISABLE_HTपूर्ण,
	अणु.idVenकरोr = 0x0df6, .idProduct = 0x0059,
		 .flags = SPEC_DEV_ID_DISABLE_HTपूर्ण,
	अणु.idVenकरोr = 0x13d3, .idProduct = 0x3306,
		 .flags = SPEC_DEV_ID_DISABLE_HTपूर्ण,
	अणु.idVenकरोr = 0x13D3, .idProduct = 0x3311,
		 .flags = SPEC_DEV_ID_DISABLE_HTपूर्ण,
	अणु.idVenकरोr = 0x13d3, .idProduct = 0x3335,
		 .flags = SPEC_DEV_ID_DISABLE_HTपूर्ण,
	अणु.idVenकरोr = 0x13d3, .idProduct = 0x3336,
		 .flags = SPEC_DEV_ID_DISABLE_HTपूर्ण,
	अणु.idVenकरोr = 0x13d3, .idProduct = 0x3340,
		 .flags = SPEC_DEV_ID_DISABLE_HTपूर्ण,
	अणु.idVenकरोr = 0x13d3, .idProduct = 0x3341,
		 .flags = SPEC_DEV_ID_DISABLE_HTपूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा drv_priv अणु
	काष्ठा usb_driver r871xu_drv;
	पूर्णांक drv_रेजिस्टरed;
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक r871x_suspend(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf, pm_message_t state)
अणु
	काष्ठा net_device *pnetdev = usb_get_पूर्णांकfdata(pusb_पूर्णांकf);
	काष्ठा _adapter *padapter = netdev_priv(pnetdev);

	netdev_info(pnetdev, "Suspending...\n");
	padapter->suspended = true;
	rtl871x_पूर्णांकf_stop(padapter);
	अगर (pnetdev->netdev_ops->nकरो_stop)
		pnetdev->netdev_ops->nकरो_stop(pnetdev);
	mdelay(10);
	netअगर_device_detach(pnetdev);
	वापस 0;
पूर्ण

अटल व्योम rtl871x_पूर्णांकf_resume(काष्ठा _adapter *padapter)
अणु
	अगर (padapter->dvobjpriv.inirp_init)
		padapter->dvobjpriv.inirp_init(padapter);
पूर्ण

अटल पूर्णांक r871x_resume(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf)
अणु
	काष्ठा net_device *pnetdev = usb_get_पूर्णांकfdata(pusb_पूर्णांकf);
	काष्ठा _adapter *padapter = netdev_priv(pnetdev);

	netdev_info(pnetdev,  "Resuming...\n");
	netअगर_device_attach(pnetdev);
	अगर (pnetdev->netdev_ops->nकरो_खोलो)
		pnetdev->netdev_ops->nकरो_खोलो(pnetdev);
	padapter->suspended = false;
	rtl871x_पूर्णांकf_resume(padapter);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा drv_priv drvpriv = अणु
	.r871xu_drv.name = "r8712u",
	.r871xu_drv.id_table = rtl871x_usb_id_tbl,
	.r871xu_drv.probe = r871xu_drv_init,
	.r871xu_drv.disconnect = r871xu_dev_हटाओ,
#अगर_घोषित CONFIG_PM
	.r871xu_drv.suspend = r871x_suspend,
	.r871xu_drv.resume = r871x_resume,
#पूर्ण_अगर
पूर्ण;

अटल uपूर्णांक r8712_usb_dvobj_init(काष्ठा _adapter *padapter)
अणु
	uपूर्णांक	status = _SUCCESS;
	काष्ठा	usb_host_पूर्णांकerface		*phost_अगरace;
	काष्ठा	usb_पूर्णांकerface_descriptor	*pअगरace_desc;
	काष्ठा dvobj_priv *pdvobjpriv = &padapter->dvobjpriv;
	काष्ठा usb_device *pusbd = pdvobjpriv->pusbdev;

	pdvobjpriv->padapter = padapter;
	padapter->eeprom_address_size = 6;
	phost_अगरace = pपूर्णांकf->cur_altsetting;
	pअगरace_desc = &phost_अगरace->desc;
	pdvobjpriv->nr_endpoपूर्णांक = pअगरace_desc->bNumEndpoपूर्णांकs;
	अगर (pusbd->speed == USB_SPEED_HIGH) अणु
		pdvobjpriv->ishighspeed = true;
		dev_info(&pusbd->dev, "r8712u: USB_SPEED_HIGH with %d endpoints\n",
			 pdvobjpriv->nr_endpoपूर्णांक);
	पूर्ण अन्यथा अणु
		pdvobjpriv->ishighspeed = false;
		dev_info(&pusbd->dev, "r8712u: USB_SPEED_LOW with %d endpoints\n",
			 pdvobjpriv->nr_endpoपूर्णांक);
	पूर्ण
	अगर ((r8712_alloc_io_queue(padapter)) == _FAIL)
		status = _FAIL;
	वापस status;
पूर्ण

अटल व्योम r8712_usb_dvobj_deinit(काष्ठा _adapter *padapter)
अणु
पूर्ण

व्योम rtl871x_पूर्णांकf_stop(काष्ठा _adapter *padapter)
अणु
	/*disable_hw_पूर्णांकerrupt*/
	अगर (!padapter->surprise_हटाओd) अणु
		/*device still exists, so driver can करो i/o operation
		 * TODO:
		 */
	पूर्ण

	/* cancel in irp */
	अगर (padapter->dvobjpriv.inirp_deinit)
		padapter->dvobjpriv.inirp_deinit(padapter);
	/* cancel out irp */
	r8712_usb_ग_लिखो_port_cancel(padapter);
	/* TODO:cancel other irps */
पूर्ण

व्योम r871x_dev_unload(काष्ठा _adapter *padapter)
अणु
	अगर (padapter->bup) अणु
		/*s1.*/
		padapter->driver_stopped = true;

		/*s3.*/
		rtl871x_पूर्णांकf_stop(padapter);

		/*s4.*/
		r8712_stop_drv_thपढ़ोs(padapter);

		/*s5.*/
		अगर (!padapter->surprise_हटाओd) अणु
			padapter->hw_init_completed = false;
			rtl8712_hal_deinit(padapter);
		पूर्ण

		/*s6.*/
		अगर (padapter->dvobj_deinit)
			padapter->dvobj_deinit(padapter);
		padapter->bup = false;
	पूर्ण
पूर्ण

अटल व्योम disable_ht_क्रम_spec_devid(स्थिर काष्ठा usb_device_id *pdid,
				      काष्ठा _adapter *padapter)
अणु
	u16 vid, pid;
	u32 flags;
	पूर्णांक i;
	पूर्णांक num = ARRAY_SIZE(specअगरic_device_id_tbl);

	क्रम (i = 0; i < num; i++) अणु
		vid = specअगरic_device_id_tbl[i].idVenकरोr;
		pid = specअगरic_device_id_tbl[i].idProduct;
		flags = specअगरic_device_id_tbl[i].flags;

		अगर ((pdid->idVenकरोr == vid) && (pdid->idProduct == pid) &&
		    (flags & SPEC_DEV_ID_DISABLE_HT)) अणु
			padapter->registrypriv.ht_enable = 0;
			padapter->registrypriv.cbw40_enable = 0;
			padapter->registrypriv.ampdu_enable = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा device_type wlan_type = अणु
	.name = "wlan",
पूर्ण;

/*
 * drv_init() - a device potentially क्रम us
 *
 * notes: drv_init() is called when the bus driver has located a card क्रम us
 * to support. We accept the new device by वापसing 0.
 */
अटल पूर्णांक r871xu_drv_init(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *pdid)
अणु
	uपूर्णांक status;
	काष्ठा _adapter *padapter = शून्य;
	काष्ठा dvobj_priv *pdvobjpriv;
	काष्ठा net_device *pnetdev;
	काष्ठा usb_device *udev;

	/* In this probe function, O.S. will provide the usb पूर्णांकerface poपूर्णांकer
	 * to driver. We have to increase the reference count of the usb device
	 * काष्ठाure by using the usb_get_dev function.
	 */
	udev = पूर्णांकerface_to_usbdev(pusb_पूर्णांकf);
	usb_get_dev(udev);
	pपूर्णांकf = pusb_पूर्णांकf;
	/* step 1. */
	pnetdev = r8712_init_netdev();
	अगर (!pnetdev)
		जाओ error;
	padapter = netdev_priv(pnetdev);
	disable_ht_क्रम_spec_devid(pdid, padapter);
	pdvobjpriv = &padapter->dvobjpriv;
	pdvobjpriv->padapter = padapter;
	padapter->dvobjpriv.pusbdev = udev;
	padapter->pusb_पूर्णांकf = pusb_पूर्णांकf;
	usb_set_पूर्णांकfdata(pusb_पूर्णांकf, pnetdev);
	SET_NETDEV_DEV(pnetdev, &pusb_पूर्णांकf->dev);
	pnetdev->dev.type = &wlan_type;
	/* step 2. */
	padapter->dvobj_init = r8712_usb_dvobj_init;
	padapter->dvobj_deinit = r8712_usb_dvobj_deinit;
	padapter->halpriv.hal_bus_init = r8712_usb_hal_bus_init;
	padapter->dvobjpriv.inirp_init = r8712_usb_inirp_init;
	padapter->dvobjpriv.inirp_deinit = r8712_usb_inirp_deinit;
	/* step 3.
	 * initialize the dvobj_priv
	 */
	अगर (!padapter->dvobj_init) अणु
		जाओ error;
	पूर्ण अन्यथा अणु
		status = padapter->dvobj_init(padapter);
		अगर (status != _SUCCESS)
			जाओ error;
	पूर्ण
	/* step 4. */
	status = r8712_init_drv_sw(padapter);
	अगर (status)
		जाओ error;
	/* step 5. पढ़ो efuse/eeprom data and get mac_addr */
	अणु
		पूर्णांक i, offset;
		u8 mac[6];
		u8 पंचांगpU1b, AutoloadFail, eeprom_CustomerID;
		u8 *pdata = padapter->eeprompriv.efuse_eeprom_data;

		पंचांगpU1b = r8712_पढ़ो8(padapter, EE_9346CR);/*CR9346*/

		/* To check प्रणाली boot selection.*/
		dev_info(&udev->dev, "r8712u: Boot from %s: Autoload %s\n",
			 (पंचांगpU1b & _9356SEL) ? "EEPROM" : "EFUSE",
			 (पंचांगpU1b & _EEPROM_EN) ? "OK" : "Failed");

		/* To check स्वतःload success or not.*/
		अगर (पंचांगpU1b & _EEPROM_EN) अणु
			AutoloadFail = true;
			/* The following operations prevent Efuse leakage by
			 * turning on 2.5V.
			 */
			पंचांगpU1b = r8712_पढ़ो8(padapter, EFUSE_TEST + 3);
			r8712_ग_लिखो8(padapter, EFUSE_TEST + 3, पंचांगpU1b | 0x80);
			msleep(20);
			r8712_ग_लिखो8(padapter, EFUSE_TEST + 3,
				     (पंचांगpU1b & (~BIT(7))));

			/* Retrieve Chip version.
			 * Recognize IC version by Reg0x4 BIT15.
			 */
			पंचांगpU1b = (u8)((r8712_पढ़ो32(padapter, PMC_FSM) >> 15) &
						    0x1F);
			अगर (पंचांगpU1b == 0x3)
				padapter->registrypriv.chip_version =
				     RTL8712_3rdCUT;
			अन्यथा
				padapter->registrypriv.chip_version =
				     (पंचांगpU1b >> 1) + 1;
			चयन (padapter->registrypriv.chip_version) अणु
			हाल RTL8712_1stCUT:
			हाल RTL8712_2ndCUT:
			हाल RTL8712_3rdCUT:
				अवरोध;
			शेष:
				padapter->registrypriv.chip_version =
				     RTL8712_2ndCUT;
				अवरोध;
			पूर्ण

			क्रम (i = 0, offset = 0; i < 128; i += 8, offset++)
				r8712_efuse_pg_packet_पढ़ो(padapter, offset,
						     &pdata[i]);

			अगर (!r8712_iniपंचांगac || !mac_pton(r8712_iniपंचांगac, mac)) अणु
				/* Use the mac address stored in the Efuse
				 * offset = 0x12 क्रम usb in efuse
				 */
				ether_addr_copy(mac, &pdata[0x12]);
			पूर्ण
			eeprom_CustomerID = pdata[0x52];
			चयन (eeprom_CustomerID) अणु
			हाल EEPROM_CID_ALPHA:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_ALPHA;
				अवरोध;
			हाल EEPROM_CID_CAMEO:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_CAMEO;
				अवरोध;
			हाल EEPROM_CID_SITECOM:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_Sitecom;
				अवरोध;
			हाल EEPROM_CID_COREGA:
				padapter->eeprompriv.CustomerID =
						 RT_CID_COREGA;
				अवरोध;
			हाल EEPROM_CID_Senao:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_Senao;
				अवरोध;
			हाल EEPROM_CID_EDIMAX_BELKIN:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_Edimax_Belkin;
				अवरोध;
			हाल EEPROM_CID_SERCOMM_BELKIN:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_Sercomm_Belkin;
				अवरोध;
			हाल EEPROM_CID_WNC_COREGA:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_WNC_COREGA;
				अवरोध;
			हाल EEPROM_CID_WHQL:
				अवरोध;
			हाल EEPROM_CID_NetCore:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_Netcore;
				अवरोध;
			हाल EEPROM_CID_CAMEO1:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_CAMEO1;
				अवरोध;
			हाल EEPROM_CID_CLEVO:
				padapter->eeprompriv.CustomerID =
						 RT_CID_819x_CLEVO;
				अवरोध;
			शेष:
				padapter->eeprompriv.CustomerID =
						 RT_CID_DEFAULT;
				अवरोध;
			पूर्ण
			dev_info(&udev->dev, "r8712u: CustomerID = 0x%.4x\n",
				 padapter->eeprompriv.CustomerID);
			/* Led mode */
			चयन (padapter->eeprompriv.CustomerID) अणु
			हाल RT_CID_DEFAULT:
			हाल RT_CID_819x_ALPHA:
			हाल RT_CID_819x_CAMEO:
				padapter->ledpriv.LedStrategy = SW_LED_MODE1;
				padapter->ledpriv.bRegUseLed = true;
				अवरोध;
			हाल RT_CID_819x_Sitecom:
				padapter->ledpriv.LedStrategy = SW_LED_MODE2;
				padapter->ledpriv.bRegUseLed = true;
				अवरोध;
			हाल RT_CID_COREGA:
			हाल RT_CID_819x_Senao:
				padapter->ledpriv.LedStrategy = SW_LED_MODE3;
				padapter->ledpriv.bRegUseLed = true;
				अवरोध;
			हाल RT_CID_819x_Edimax_Belkin:
				padapter->ledpriv.LedStrategy = SW_LED_MODE4;
				padapter->ledpriv.bRegUseLed = true;
				अवरोध;
			हाल RT_CID_819x_Sercomm_Belkin:
				padapter->ledpriv.LedStrategy = SW_LED_MODE5;
				padapter->ledpriv.bRegUseLed = true;
				अवरोध;
			हाल RT_CID_819x_WNC_COREGA:
				padapter->ledpriv.LedStrategy = SW_LED_MODE6;
				padapter->ledpriv.bRegUseLed = true;
				अवरोध;
			शेष:
				padapter->ledpriv.LedStrategy = SW_LED_MODE0;
				padapter->ledpriv.bRegUseLed = false;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			AutoloadFail = false;
		पूर्ण
		अगर (((mac[0] == 0xff) && (mac[1] == 0xff) &&
		     (mac[2] == 0xff) && (mac[3] == 0xff) &&
		     (mac[4] == 0xff) && (mac[5] == 0xff)) ||
		    ((mac[0] == 0x00) && (mac[1] == 0x00) &&
		     (mac[2] == 0x00) && (mac[3] == 0x00) &&
		     (mac[4] == 0x00) && (mac[5] == 0x00)) ||
		     (!AutoloadFail)) अणु
			mac[0] = 0x00;
			mac[1] = 0xe0;
			mac[2] = 0x4c;
			mac[3] = 0x87;
			mac[4] = 0x00;
			mac[5] = 0x00;
		पूर्ण
		अगर (r8712_iniपंचांगac) अणु
			/* Make sure the user did not select a multicast
			 * address by setting bit 1 of first octet.
			 */
			mac[0] &= 0xFE;
			dev_info(&udev->dev,
				"r8712u: MAC Address from user = %pM\n", mac);
		पूर्ण अन्यथा अणु
			dev_info(&udev->dev,
				"r8712u: MAC Address from efuse = %pM\n", mac);
		पूर्ण
		ether_addr_copy(pnetdev->dev_addr, mac);
	पूर्ण
	/* step 6. Load the firmware asynchronously */
	अगर (rtl871x_load_fw(padapter))
		जाओ error;
	spin_lock_init(&padapter->lock_rx_ff0_filter);
	mutex_init(&padapter->mutex_start);
	वापस 0;
error:
	usb_put_dev(udev);
	usb_set_पूर्णांकfdata(pusb_पूर्णांकf, शून्य);
	अगर (padapter && padapter->dvobj_deinit)
		padapter->dvobj_deinit(padapter);
	अगर (pnetdev)
		मुक्त_netdev(pnetdev);
	वापस -ENODEV;
पूर्ण

/* rmmod module & unplug(SurpriseRemoved) will call r871xu_dev_हटाओ()
 * => how to recognize both
 */
अटल व्योम r871xu_dev_हटाओ(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf)
अणु
	काष्ठा net_device *pnetdev = usb_get_पूर्णांकfdata(pusb_पूर्णांकf);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(pusb_पूर्णांकf);

	अगर (pnetdev) अणु
		काष्ठा _adapter *padapter = netdev_priv(pnetdev);

		/* never निकास with a firmware callback pending */
		रुको_क्रम_completion(&padapter->rtl8712_fw_पढ़ोy);
		pnetdev = usb_get_पूर्णांकfdata(pusb_पूर्णांकf);
		usb_set_पूर्णांकfdata(pusb_पूर्णांकf, शून्य);
		अगर (!pnetdev)
			जाओ firmware_load_fail;
		release_firmware(padapter->fw);
		अगर (drvpriv.drv_रेजिस्टरed)
			padapter->surprise_हटाओd = true;
		अगर (pnetdev->reg_state != NETREG_UNINITIALIZED)
			unरेजिस्टर_netdev(pnetdev); /* will call netdev_बंद() */
		flush_scheduled_work();
		udelay(1);
		/* Stop driver mlme relation समयr */
		r8712_stop_drv_समयrs(padapter);
		r871x_dev_unload(padapter);
		r8712_मुक्त_drv_sw(padapter);

		/* decrease the reference count of the usb device काष्ठाure
		 * when disconnect
		 */
		usb_put_dev(udev);
	पूर्ण
firmware_load_fail:
	/* If we didn't unplug usb करोngle and हटाओ/insert module, driver
	 * fails on sitesurvey क्रम the first समय when device is up.
	 * Reset usb port क्रम sitesurvey fail issue.
	 */
	अगर (udev->state != USB_STATE_NOTATTACHED)
		usb_reset_device(udev);
पूर्ण

अटल पूर्णांक __init r8712u_drv_entry(व्योम)
अणु
	drvpriv.drv_रेजिस्टरed = true;
	वापस usb_रेजिस्टर(&drvpriv.r871xu_drv);
पूर्ण

अटल व्योम __निकास r8712u_drv_halt(व्योम)
अणु
	drvpriv.drv_रेजिस्टरed = false;
	usb_deरेजिस्टर(&drvpriv.r871xu_drv);
पूर्ण

module_init(r8712u_drv_entry);
module_निकास(r8712u_drv_halt);
