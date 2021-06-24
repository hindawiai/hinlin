<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
/*-----------------------------------------------------------------------------

	For type defines and data काष्ठाure defines

------------------------------------------------------------------------------*/

#अगर_अघोषित __DRV_TYPES_H__
#घोषणा __DRV_TYPES_H__

#घोषणा DRV_NAME "r8188eu"

#समावेश <osdep_service.h>
#समावेश <wlan_bssdef.h>
#समावेश <rtw_ht.h>
#समावेश <rtw_cmd.h>
#समावेश <rtw_xmit.h>
#समावेश <rtw_recv.h>
#समावेश <hal_पूर्णांकf.h>
#समावेश <hal_com.h>
#समावेश <rtw_security.h>
#समावेश <rtw_pwrctrl.h>
#समावेश <rtw_eeprom.h>
#समावेश <sta_info.h>

काष्ठा qos_priv अणु
	/* bit mask option: u-apsd, s-apsd, ts, block ack... */
	अचिन्हित पूर्णांक qos_option;
पूर्ण;

#समावेश <rtw_mlme.h>
#समावेश <rtw_debug.h>
#समावेश <rtw_rf.h>
#समावेश <rtw_event.h>
#समावेश <rtw_led.h>
#समावेश <rtw_mlme_ext.h>
#समावेश <rtw_ap.h>

#घोषणा SPEC_DEV_ID_NONE		BIT(0)
#घोषणा SPEC_DEV_ID_DISABLE_HT		BIT(1)
#घोषणा SPEC_DEV_ID_ENABLE_PS		BIT(2)
#घोषणा SPEC_DEV_ID_RF_CONFIG_1T1R	BIT(3)
#घोषणा SPEC_DEV_ID_RF_CONFIG_2T2R	BIT(4)
#घोषणा SPEC_DEV_ID_ASSIGN_IFNAME	BIT(5)

काष्ठा registry_priv अणु
	काष्ठा ndis_802_11_ssid	ssid;
	u8	channel;/* ad-hoc support requirement */
	u8	wireless_mode;/* A, B, G, स्वतः */
	u8	preamble;/* दीर्घ, लघु, स्वतः */
	u8	vrtl_carrier_sense;/* Enable, Disable, Auto */
	u8	vcs_type;/* RTS/CTS, CTS-to-self */
	u16	rts_thresh;
	u16	frag_thresh;
	u8	घातer_mgnt;
	u8	ips_mode;
	u8	smart_ps;
	u8	mp_mode;
	u8	acm_method;
	  /* UAPSD */
	u8	wmm_enable;
	u8	uapsd_enable;

	काष्ठा wlan_bssid_ex    dev_network;

	u8	ht_enable;
	u8	cbw40_enable;
	u8	ampdu_enable;/* क्रम tx */
	u8	rx_stbc;
	u8	ampdu_amsdu;/* A-MPDU Supports A-MSDU is permitted */

	u8	wअगरi_spec;/*  !turbo_mode */

	u8	channel_plan;
	bool	accept_addba_req; /* true = accept AP's Add BA req */

	u8	antभाग_cfg;
	u8	antभाग_प्रकारype;

	u8	usbss_enable;/* 0:disable,1:enable */
	u8	hwpdn_mode;/* 0:disable,1:enable,2:decide by EFUSE config */

	u8	max_roaming_बार; /*  the max number driver will try */

	u8	fw_iol; /* enable iol without other concern */

	u8	enable80211d;

	u8	अगरname[16];
	u8	अगर2name[16];

	u8	notch_filter;
	bool	monitor_enable;
पूर्ण;

#घोषणा MAX_CONTINUAL_URB_ERR		4

काष्ठा dvobj_priv अणु
	काष्ठा adapter *अगर1;
	/* For 92D, DMDP have 2 पूर्णांकerface. */
	u8	InterfaceNumber;
	u8	NumInterfaces;

	/* In /Out Pipe inक्रमmation */
	पूर्णांक	RtInPipe[2];
	पूर्णांक	RtOutPipe[3];
	u8	Queue2Pipe[HW_QUEUE_ENTRY];/* क्रम out pipe mapping */

/*-------- below is क्रम USB INTERFACE --------*/
	u8	ishighspeed;
	u8	RtNumInPipes;
	u8	RtNumOutPipes;
	काष्ठा mutex  usb_venकरोr_req_mutex;

	काष्ठा usb_पूर्णांकerface *pusbपूर्णांकf;
	काष्ठा usb_device *pusbdev;
पूर्ण;

अटल अंतरभूत काष्ठा device *dvobj_to_dev(काष्ठा dvobj_priv *dvobj)
अणु
	/* toकरो: get पूर्णांकerface type from dvobj and the वापस
	 * the dev accordingly
	 */
	वापस &dvobj->pusbपूर्णांकf->dev;
पूर्ण;

काष्ठा adapter अणु
	काष्ठा dvobj_priv *dvobj;
	काष्ठा	mlme_priv mlmepriv;
	काष्ठा	mlme_ext_priv mlmeextpriv;
	काष्ठा	cmd_priv	cmdpriv;
	काष्ठा	xmit_priv	xmitpriv;
	काष्ठा	recv_priv	recvpriv;
	काष्ठा	sta_priv	stapriv;
	काष्ठा	security_priv	securitypriv;
	काष्ठा	registry_priv	registrypriv;
	काष्ठा	pwrctrl_priv	pwrctrlpriv;
	काष्ठा	eeprom_priv eeprompriv;
	काष्ठा	led_priv	ledpriv;

	काष्ठा hal_data_8188e *HalData;

	s32	bDriverStopped;
	s32	bSurpriseRemoved;

	u8	hw_init_completed;

	काष्ठा task_काष्ठा *cmdThपढ़ो;
	काष्ठा  net_device *pnetdev;
	काष्ठा  net_device *pmondev;

	पूर्णांक bup;
	काष्ठा net_device_stats stats;
	काष्ठा iw_statistics iwstats;
	काष्ठा proc_dir_entry *dir_dev;/*  क्रम proc directory */

	पूर्णांक net_बंदd;
	u8 bFWReady;
	u8 bReadPortCancel;
	u8 bWritePortCancel;

	काष्ठा mutex hw_init_mutex;
पूर्ण;

#घोषणा adapter_to_dvobj(adapter) (adapter->dvobj)

अटल अंतरभूत u8 *myid(काष्ठा eeprom_priv *peepriv)
अणु
	वापस peepriv->mac_addr;
पूर्ण

#पूर्ण_अगर /* __DRV_TYPES_H__ */
