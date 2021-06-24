<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
/* ---------------------------------------------------------------------
 *
 *	For type defines and data काष्ठाure defines
 *
 * ---------------------------------------------------------------------
 */
#अगर_अघोषित __DRV_TYPES_H__
#घोषणा __DRV_TYPES_H__

काष्ठा _adapter;

#समावेश "osdep_service.h"
#समावेश "wlan_bssdef.h"
#समावेश "rtl8712_spec.h"
#समावेश "rtl8712_hal.h"
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>

क्रमागत _NIC_VERSION अणु
	RTL8711_NIC,
	RTL8712_NIC,
	RTL8713_NIC,
	RTL8716_NIC
पूर्ण;

काष्ठा	qos_priv	अणु
	/* bit mask option: u-apsd, s-apsd, ts, block ack... */
	अचिन्हित पूर्णांक qos_option;
पूर्ण;

#समावेश "rtl871x_ht.h"
#समावेश "rtl871x_cmd.h"
#समावेश "rtl871x_xmit.h"
#समावेश "rtl871x_recv.h"
#समावेश "rtl871x_security.h"
#समावेश "rtl871x_pwrctrl.h"
#समावेश "rtl871x_io.h"
#समावेश "rtl871x_eeprom.h"
#समावेश "sta_info.h"
#समावेश "rtl871x_mlme.h"
#समावेश "rtl871x_mp.h"
#समावेश "rtl871x_debug.h"
#समावेश "rtl871x_rf.h"
#समावेश "rtl871x_event.h"
#समावेश "rtl871x_led.h"

#घोषणा SPEC_DEV_ID_DISABLE_HT BIT(1)

काष्ठा specअगरic_device_id अणु
	u32		flags;
	u16		idVenकरोr;
	u16		idProduct;

पूर्ण;

काष्ठा registry_priv अणु
	u8	chip_version;
	u8	rfपूर्णांकfs;
	u8	lbkmode;
	u8	hci;
	u8	network_mode;	/*infra, ad-hoc, स्वतः*/
	काष्ठा ndis_802_11_ssid	ssid;
	u8	channel;/* ad-hoc support requirement */
	u8	wireless_mode;/* A, B, G, स्वतः */
	u8	vrtl_carrier_sense; /*Enable, Disable, Auto*/
	u8	vcs_type;/*RTS/CTS, CTS-to-self*/
	u16	rts_thresh;
	u16  frag_thresh;
	u8	preamble;/*दीर्घ, लघु, स्वतः*/
	u8  scan_mode;/*active, passive*/
	u8  adhoc_tx_pwr;
	u8  soft_ap;
	u8  smart_ps;
	u8 घातer_mgnt;
	u8 radio_enable;
	u8 दीर्घ_retry_lmt;
	u8 लघु_retry_lmt;
	u16 busy_thresh;
	u8 ack_policy;
	u8 mp_mode;
	u8 software_encrypt;
	u8 software_decrypt;
	/* UAPSD */
	u8 wmm_enable;
	u8 uapsd_enable;
	u8 uapsd_max_sp;
	u8 uapsd_acbk_en;
	u8 uapsd_acbe_en;
	u8 uapsd_acvi_en;
	u8 uapsd_acvo_en;

	काष्ठा wlan_bssid_ex dev_network;

	u8 ht_enable;
	u8 cbw40_enable;
	u8 ampdu_enable;/*क्रम tx*/
	u8 rf_config;
	u8 low_घातer;
	u8 wअगरi_test;
पूर्ण;

काष्ठा dvobj_priv अणु
	काष्ठा _adapter *padapter;
	u32 nr_endpoपूर्णांक;
	u8   ishighspeed;
	uपूर्णांक (*inirp_init)(काष्ठा _adapter *adapter);
	uपूर्णांक (*inirp_deinit)(काष्ठा _adapter *adapter);
	काष्ठा usb_device *pusbdev;
पूर्ण;

/**
 * काष्ठा _adapter - the मुख्य adapter काष्ठाure क्रम this device.
 *
 * bup: True indicates that the पूर्णांकerface is up.
 */
काष्ठा _adapter अणु
	काष्ठा	dvobj_priv dvobjpriv;
	काष्ठा	mlme_priv mlmepriv;
	काष्ठा	cmd_priv	cmdpriv;
	काष्ठा	evt_priv	evtpriv;
	काष्ठा	io_queue	*pio_queue;
	काष्ठा	xmit_priv	xmitpriv;
	काष्ठा	recv_priv	recvpriv;
	काष्ठा	sta_priv	stapriv;
	काष्ठा	security_priv	securitypriv;
	काष्ठा	registry_priv	registrypriv;
	काष्ठा	wlan_acl_pool	acl_list;
	काष्ठा	pwrctrl_priv	pwrctrlpriv;
	काष्ठा	eeprom_priv eeprompriv;
	काष्ठा	hal_priv	halpriv;
	काष्ठा	led_priv	ledpriv;
	काष्ठा mp_priv  mppriv;
	bool	driver_stopped;
	bool	surprise_हटाओd;
	bool	suspended;
	u8	eeprom_address_size;
	u8	hw_init_completed;
	काष्ठा task_काष्ठा *cmd_thपढ़ो;
	uपूर्णांक (*dvobj_init)(काष्ठा _adapter *adapter);
	व्योम (*dvobj_deinit)(काष्ठा _adapter *adapter);
	काष्ठा net_device *pnetdev;
	पूर्णांक bup;
	काष्ठा net_device_stats stats;
	काष्ठा iw_statistics iwstats;
	पूर्णांक pid; /*process id from UI*/
	काष्ठा work_काष्ठा wk_filter_rx_ff0;
	u8 blnEnableRxFF0Filter;
	spinlock_t lock_rx_ff0_filter;
	स्थिर काष्ठा firmware *fw;
	काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf;
	काष्ठा mutex mutex_start;
	काष्ठा completion rtl8712_fw_पढ़ोy;
पूर्ण;

अटल अंतरभूत u8 *myid(काष्ठा eeprom_priv *peepriv)
अणु
	वापस peepriv->mac_addr;
पूर्ण

u8 r8712_usb_hal_bus_init(काष्ठा _adapter *adapter);

#पूर्ण_अगर /*__DRV_TYPES_H__*/

