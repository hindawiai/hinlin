<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
/*-------------------------------------------------------------------------------

	For type defines and data काष्ठाure defines

--------------------------------------------------------------------------------*/


#अगर_अघोषित __DRV_TYPES_H__
#घोषणा __DRV_TYPES_H__

#समावेश <linux/sched/संकेत.स>
#समावेश <स्वतःconf.h>
#समावेश <basic_types.h>
#समावेश <osdep_service.h>
#समावेश <rtw_byteorder.h>
#समावेश <wlan_bssdef.h>
#समावेश <wअगरi.h>
#समावेश <ieee80211.h>

#समावेश <rtw_rf.h>

#समावेश <rtw_ht.h>

#समावेश <rtw_cmd.h>
#समावेश <cmd_osdep.h>
#समावेश <rtw_security.h>
#समावेश <rtw_xmit.h>
#समावेश <xmit_osdep.h>
#समावेश <rtw_recv.h>

#समावेश <recv_osdep.h>
#समावेश <rtw_efuse.h>
#समावेश <hal_पूर्णांकf.h>
#समावेश <hal_com.h>
#समावेश <rtw_qos.h>
#समावेश <rtw_pwrctrl.h>
#समावेश <rtw_mlme.h>
#समावेश <mlme_osdep.h>
#समावेश <rtw_पन.स>
#समावेश <rtw_ioctl.h>
#समावेश <rtw_ioctl_set.h>
#समावेश <osdep_पूर्णांकf.h>
#समावेश <rtw_eeprom.h>
#समावेश <sta_info.h>
#समावेश <rtw_event.h>
#समावेश <rtw_mlme_ext.h>
#समावेश <rtw_ap.h>
#समावेश <rtw_version.h>
#समावेश <rtw_odm.h>

#समावेश "ioctl_cfg80211.h"

#समावेश <linux/ip.h>
#समावेश <linux/अगर_ether.h>
#समावेश <ethernet.h>

#घोषणा SPEC_DEV_ID_NONE BIT(0)
#घोषणा SPEC_DEV_ID_DISABLE_HT BIT(1)
#घोषणा SPEC_DEV_ID_ENABLE_PS BIT(2)
#घोषणा SPEC_DEV_ID_RF_CONFIG_1T1R BIT(3)
#घोषणा SPEC_DEV_ID_RF_CONFIG_2T2R BIT(4)
#घोषणा SPEC_DEV_ID_ASSIGN_IFNAME BIT(5)

काष्ठा registry_priv अणु
	u8 chip_version;
	u8 rfपूर्णांकfs;
	u8 lbkmode;
	u8 hci;
	काष्ठा ndis_802_11_ssid	ssid;
	u8 network_mode;	/* infra, ad-hoc, स्वतः */
	u8 channel;/* ad-hoc support requirement */
	u8 wireless_mode;/* A, B, G, स्वतः */
	u8 scan_mode;/* active, passive */
	u8 radio_enable;
	u8 preamble;/* दीर्घ, लघु, स्वतः */
	u8 vrtl_carrier_sense;/* Enable, Disable, Auto */
	u8 vcs_type;/* RTS/CTS, CTS-to-self */
	u16 rts_thresh;
	u16  frag_thresh;
	u8 adhoc_tx_pwr;
	u8 soft_ap;
	u8 घातer_mgnt;
	u8 ips_mode;
	u8 smart_ps;
	u8   usb_rxagg_mode;
	u8 दीर्घ_retry_lmt;
	u8 लघु_retry_lmt;
	u16 busy_thresh;
	u8 ack_policy;
	u8  mp_dm;
	u8 software_encrypt;
	u8 software_decrypt;
	u8 acm_method;
	  /* UAPSD */
	u8 wmm_enable;
	u8 uapsd_enable;
	u8 uapsd_max_sp;
	u8 uapsd_acbk_en;
	u8 uapsd_acbe_en;
	u8 uapsd_acvi_en;
	u8 uapsd_acvo_en;

	काष्ठा wlan_bssid_ex    dev_network;

	u8 ht_enable;
	/*  0: 20 MHz, 1: 40 MHz, 2: 80 MHz, 3: 160MHz */
	/*  2.4G use bit 0 ~ 3, 5G use bit 4 ~ 7 */
	/*  0x21 means enable 2.4G 40MHz & 5G 80MHz */
	u8 bw_mode;
	u8 ampdu_enable;/* क्रम tx */
	u8 rx_stbc;
	u8 ampdu_amsdu;/* A-MPDU Supports A-MSDU is permitted */
	/*  Short GI support Bit Map */
	/*  BIT0 - 20MHz, 1: support, 0: non-support */
	/*  BIT1 - 40MHz, 1: support, 0: non-support */
	/*  BIT2 - 80MHz, 1: support, 0: non-support */
	/*  BIT3 - 160MHz, 1: support, 0: non-support */
	u8 लघु_gi;
	/*  BIT0: Enable VHT LDPC Rx, BIT1: Enable VHT LDPC Tx, BIT4: Enable HT LDPC Rx, BIT5: Enable HT LDPC Tx */
	u8 ldpc_cap;
	/*  BIT0: Enable VHT STBC Rx, BIT1: Enable VHT STBC Tx, BIT4: Enable HT STBC Rx, BIT5: Enable HT STBC Tx */
	u8 stbc_cap;
	/*  BIT0: Enable VHT Beamक्रमmer, BIT1: Enable VHT Beamक्रमmee, BIT4: Enable HT Beamक्रमmer, BIT5: Enable HT Beamक्रमmee */
	u8 beamक्रमm_cap;

	u8 lowrate_two_xmit;

	u8 rf_config;
	u8 low_घातer;

	u8 wअगरi_spec;/*  !turbo_mode */

	u8 channel_plan;

	u8 btcoex;
	u8 bt_iso;
	u8 bt_sco;
	u8 bt_ampdu;
	s8	ant_num;

	/* false:Reject AP's Add BA req, true:accept AP's Add BA req */
	bool	accept_addba_req;

	u8 antभाग_cfg;
	u8 antभाग_प्रकारype;

	u8 usbss_enable;/* 0:disable, 1:enable */
	u8 hwpdn_mode;/* 0:disable, 1:enable, 2:decide by EFUSE config */
	u8 hwpwrp_detect;/* 0:disable, 1:enable */

	u8 hw_wps_pbc;/* 0:disable, 1:enable */

	u8 max_roaming_बार; /*  the max number driver will try to roaming */

	u8 enable80211d;

	u8 अगरname[16];

	u8 notch_filter;

	/* define क्रम tx घातer adjust */
	u8 RegEnableTxPowerLimit;
	u8 RegEnableTxPowerByRate;
	u8 RegPowerBase;
	u8 RegPwrTblSel;
	s8	TxBBSwing_2G;
	s8	TxBBSwing_5G;
	u8 AmplअगरierType_2G;
	u8 AmplअगरierType_5G;
	u8 bEn_RFE;
	u8 RFE_Type;
	u8  check_fw_ps;

	u8 qos_opt_enable;

	u8 hiq_filter;
पूर्ण;


/* For registry parameters */
#घोषणा RGTRY_OFT(field) ((u32)FIELD_OFFSET(काष्ठा registry_priv, field))
#घोषणा RGTRY_SZ(field)   माप(((काष्ठा registry_priv *)0)->field)
#घोषणा BSSID_OFT(field) ((u32)FIELD_OFFSET(काष्ठा wlan_bssid_ex, field))
#घोषणा BSSID_SZ(field)   माप(((काष्ठा wlan_bssid_ex *) 0)->field)

#समावेश <drv_types_sdपन.स>

#घोषणा is_primary_adapter(adapter) (1)
#घोषणा get_अगरace_type(adapter) (IFACE_PORT0)
#घोषणा GET_PRIMARY_ADAPTER(padapter) (((काष्ठा adapter *)padapter)->dvobj->अगर1)
#घोषणा GET_IFACE_NUMS(padapter) (((काष्ठा adapter *)padapter)->dvobj->अगरace_nums)
#घोषणा GET_ADAPTER(padapter, अगरace_id) (((काष्ठा adapter *)padapter)->dvobj->padapters[अगरace_id])

काष्ठा debug_priv अणु
	u32 dbg_sdio_मुक्त_irq_error_cnt;
	u32 dbg_sdio_alloc_irq_error_cnt;
	u32 dbg_sdio_मुक्त_irq_cnt;
	u32 dbg_sdio_alloc_irq_cnt;
	u32 dbg_sdio_deinit_error_cnt;
	u32 dbg_sdio_init_error_cnt;
	u32 dbg_suspend_error_cnt;
	u32 dbg_suspend_cnt;
	u32 dbg_resume_cnt;
	u32 dbg_resume_error_cnt;
	u32 dbg_deinit_fail_cnt;
	u32 dbg_carddisable_cnt;
	u32 dbg_carddisable_error_cnt;
	u32 dbg_ps_insuspend_cnt;
	u32 dbg_dev_unload_inIPS_cnt;
	u32 dbg_wow_leave_ps_fail_cnt;
	u32 dbg_scan_pwr_state_cnt;
	u32 dbg_करोwnloadfw_pwr_state_cnt;
	u32 dbg_fw_पढ़ो_ps_state_fail_cnt;
	u32 dbg_leave_ips_fail_cnt;
	u32 dbg_leave_lps_fail_cnt;
	u32 dbg_h2c_leave32k_fail_cnt;
	u32 dbg_diswow_dload_fw_fail_cnt;
	u32 dbg_enwow_dload_fw_fail_cnt;
	u32 dbg_ips_drvखोलो_fail_cnt;
	u32 dbg_poll_fail_cnt;
	u32 dbg_rpwm_toggle_cnt;
	u32 dbg_rpwm_समयout_fail_cnt;
	u64 dbg_rx_fअगरo_last_overflow;
	u64 dbg_rx_fअगरo_curr_overflow;
	u64 dbg_rx_fअगरo_dअगरf_overflow;
	u64 dbg_rx_ampdu_drop_count;
	u64 dbg_rx_ampdu_क्रमced_indicate_count;
	u64 dbg_rx_ampdu_loss_count;
	u64 dbg_rx_dup_mgt_frame_drop_count;
	u64 dbg_rx_ampdu_winकरोw_shअगरt_cnt;
पूर्ण;

काष्ठा rtw_traffic_statistics अणु
	/*  tx statistics */
	u64	tx_bytes;
	u64	tx_pkts;
	u64	tx_drop;
	u64	cur_tx_bytes;
	u64	last_tx_bytes;
	u32 cur_tx_tp; /*  Tx throughput in MBps. */

	/*  rx statistics */
	u64	rx_bytes;
	u64	rx_pkts;
	u64	rx_drop;
	u64	cur_rx_bytes;
	u64	last_rx_bytes;
	u32 cur_rx_tp; /*  Rx throughput in MBps. */
पूर्ण;

काष्ठा cam_ctl_t अणु
	spinlock_t lock;
	u64 biपंचांगap;
पूर्ण;

काष्ठा cam_entry_cache अणु
	u16 ctrl;
	u8 mac[ETH_ALEN];
	u8 key[16];
पूर्ण;

काष्ठा dvobj_priv अणु
	/*-------- below is common data --------*/
	काष्ठा adapter *अगर1; /* PRIMARY_ADAPTER */

	s32	processing_dev_हटाओ;

	काष्ठा debug_priv drv_dbg;

	/* क्रम local/global synchronization */
	/*  */
	spinlock_t	lock;
	पूर्णांक macid[NUM_STA];

	काष्ठा mutex hw_init_mutex;
	काष्ठा mutex h2c_fwcmd_mutex;
	काष्ठा mutex setch_mutex;
	काष्ठा mutex setbw_mutex;

	अचिन्हित अक्षर oper_channel; /* saved channel info when call set_channel_bw */
	अचिन्हित अक्षर oper_bwmode;
	अचिन्हित अक्षर oper_ch_offset;/* PRIME_CHNL_OFFSET */
	अचिन्हित दीर्घ on_oper_ch_समय;

	काष्ठा adapter *padapters;

	काष्ठा cam_ctl_t cam_ctl;
	काष्ठा cam_entry_cache cam_cache[TOTAL_CAM_ENTRY];

	/* In /Out Pipe inक्रमmation */
	पूर्णांक	RtInPipe[2];
	पूर्णांक	RtOutPipe[4];
	u8 Queue2Pipe[HW_QUEUE_ENTRY];/* क्रम out pipe mapping */

	u8 irq_alloc;
	atomic_t continual_io_error;

	atomic_t disable_func;

	काष्ठा pwrctrl_priv pwrctl_priv;

	काष्ठा rtw_traffic_statistics	traffic_stat;

/*-------- below is क्रम SDIO INTERFACE --------*/

काष्ठा sdio_data पूर्णांकf_data;

पूर्ण;

#घोषणा dvobj_to_pwrctl(dvobj) (&(dvobj->pwrctl_priv))
#घोषणा pwrctl_to_dvobj(pwrctl) container_of(pwrctl, काष्ठा dvobj_priv, pwrctl_priv)

अटल अंतरभूत काष्ठा device *dvobj_to_dev(काष्ठा dvobj_priv *dvobj)
अणु
	/* toकरो: get पूर्णांकerface type from dvobj and the वापस the dev accordingly */
#अगर_घोषित RTW_DVOBJ_CHIP_HW_TYPE
#पूर्ण_अगर

	वापस &dvobj->पूर्णांकf_data.func->dev;
पूर्ण

काष्ठा adapter *dvobj_get_port0_adapter(काष्ठा dvobj_priv *dvobj);

क्रमागत अणु
	IFACE_PORT0, /* mapping to port0 क्रम C/D series chips */
	IFACE_PORT1, /* mapping to port1 क्रम C/D series chip */
	MAX_IFACE_PORT,
पूर्ण;

क्रमागत अणु
	DRIVER_NORMAL = 0,
	DRIVER_DISAPPEAR = 1,
	DRIVER_REPLACE_DONGLE = 2,
पूर्ण;

काष्ठा adapter अणु
	पूर्णांक	DriverState;/*  क्रम disable driver using module, use करोngle to replace module. */
	पूर्णांक	pid[3];/* process id from UI, 0:wps, 1:hostapd, 2:dhcpcd */
	पूर्णांक	bDongle;/* build-in module or बाह्यal करोngle */

	काष्ठा dvobj_priv *dvobj;
	काष्ठा	mlme_priv mlmepriv;
	काष्ठा	mlme_ext_priv mlmeextpriv;
	काष्ठा	cmd_priv cmdpriv;
	काष्ठा	evt_priv evtpriv;
	/* काष्ठा	io_queue	*pio_queue; */
	काष्ठा	io_priv iopriv;
	काष्ठा	xmit_priv xmitpriv;
	काष्ठा	recv_priv recvpriv;
	काष्ठा	sta_priv stapriv;
	काष्ठा	security_priv securitypriv;
	spinlock_t   security_key_mutex; /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
	काष्ठा	registry_priv registrypriv;
	काष्ठा	eeprom_priv eeprompriv;

	काष्ठा	hostapd_priv *phostapdpriv;

	u32 setband;

	व्योम *HalData;
	u32 hal_data_sz;
	काष्ठा hal_ops	HalFunc;

	s32	bDriverStopped;
	s32	bSurpriseRemoved;
	s32  bCardDisableWOHSM;

	u32 IsrContent;
	u32 ImrContent;

	u8 EepromAddressSize;
	u8 hw_init_completed;
	u8 bDriverIsGoingToUnload;
	u8 init_adpt_in_progress;
	u8 bHaltInProgress;

	व्योम *cmdThपढ़ो;
	व्योम *evtThपढ़ो;
	व्योम *xmitThपढ़ो;
	व्योम *recvThपढ़ो;

	u32 (*पूर्णांकf_init)(काष्ठा dvobj_priv *dvobj);
	व्योम (*पूर्णांकf_deinit)(काष्ठा dvobj_priv *dvobj);
	पूर्णांक (*पूर्णांकf_alloc_irq)(काष्ठा dvobj_priv *dvobj);
	व्योम (*पूर्णांकf_मुक्त_irq)(काष्ठा dvobj_priv *dvobj);


	व्योम (*पूर्णांकf_start)(काष्ठा adapter *adapter);
	व्योम (*पूर्णांकf_stop)(काष्ठा adapter *adapter);

	काष्ठा net_device *pnetdev;
	अक्षर old_अगरname[IFNAMSIZ];

	/*  used by rtw_rereg_nd_name related function */
	काष्ठा rereg_nd_name_data अणु
		काष्ठा net_device *old_pnetdev;
		अक्षर old_अगरname[IFNAMSIZ];
		u8 old_bRegUseLed;
	पूर्ण rereg_nd_name_priv;

	पूर्णांक bup;
	काष्ठा net_device_stats stats;
	काष्ठा iw_statistics iwstats;

	काष्ठा wireless_dev *rtw_wdev;
	काष्ठा rtw_wdev_priv wdev_data;

	पूर्णांक net_बंदd;

	u8 netअगर_up;

	u8 bFWReady;
	u8 bBTFWReady;
	u8 bLinkInfoDump;
	u8 bRxRSSIDisplay;
	/* 	Added by Albert 2012/10/26 */
	/* 	The driver will show up the desired channel number when this flag is 1. */
	u8 bNotअगरyChannelChange;

	/* pbuddyकाष्ठा adapter is used only in two पूर्णांकerface हाल, (अगरace_nums =2 in काष्ठा dvobj_priv) */
	/* PRIMARY ADAPTER's buddy is SECONDARY_ADAPTER */
	/* SECONDARY_ADAPTER's buddy is PRIMARY_ADAPTER */
	/* क्रम अगरace_id > SECONDARY_ADAPTER(IFACE_ID1), refer to padapters[अगरace_id]  in काष्ठा dvobj_priv */
	/* and their pbuddyकाष्ठा adapter is PRIMARY_ADAPTER. */
	/* क्रम PRIMARY_ADAPTER(IFACE_ID0) can directly refer to अगर1 in काष्ठा dvobj_priv */
	काष्ठा adapter *pbuddy_adapter;

	/* extend to support multi पूर्णांकerface */
       /* IFACE_ID0 is equals to PRIMARY_ADAPTER */
       /* IFACE_ID1 is equals to SECONDARY_ADAPTER */
	u8 अगरace_id;

	/* क्रम debug purpose */
	u8 fix_rate;
	u8 driver_vcs_en; /* Enable = 1, Disable = 0 driver control vrtl_carrier_sense क्रम tx */
	u8 driver_vcs_type;/* क्रमce 0:disable VCS, 1:RTS-CTS, 2:CTS-to-self when vcs_en = 1. */
	u8 driver_ampdu_spacing;/* driver control AMPDU Density क्रम peer sta's rx */
	u8 driver_rx_ampdu_factor;/* 0xff: disable drv ctrl, 0:8k, 1:16k, 2:32k, 3:64k; */

	अचिन्हित अक्षर     in_cta_test;
पूर्ण;

#घोषणा adapter_to_dvobj(adapter) (adapter->dvobj)
#घोषणा adapter_to_pwrctl(adapter) (dvobj_to_pwrctl(adapter->dvobj))
#घोषणा adapter_wdev_data(adapter) (&((adapter)->wdev_data))

/*  */
/*  Function disabled. */
/*  */
#घोषणा DF_TX_BIT		BIT0
#घोषणा DF_RX_BIT		BIT1
#घोषणा DF_IO_BIT		BIT2

/* define RTW_DISABLE_FUNC(padapter, func) (atomic_add(&adapter_to_dvobj(padapter)->disable_func, (func))) */
/* define RTW_ENABLE_FUNC(padapter, func) (atomic_sub(&adapter_to_dvobj(padapter)->disable_func, (func))) */
अटल अंतरभूत व्योम RTW_DISABLE_FUNC(काष्ठा adapter *padapter, पूर्णांक func_bit)
अणु
	पूर्णांक	df = atomic_पढ़ो(&adapter_to_dvobj(padapter)->disable_func);
	df |= func_bit;
	atomic_set(&adapter_to_dvobj(padapter)->disable_func, df);
पूर्ण

अटल अंतरभूत व्योम RTW_ENABLE_FUNC(काष्ठा adapter *padapter, पूर्णांक func_bit)
अणु
	पूर्णांक	df = atomic_पढ़ो(&adapter_to_dvobj(padapter)->disable_func);
	df &= ~(func_bit);
	atomic_set(&adapter_to_dvobj(padapter)->disable_func, df);
पूर्ण

#घोषणा RTW_IS_FUNC_DISABLED(padapter, func_bit) (atomic_पढ़ो(&adapter_to_dvobj(padapter)->disable_func) & (func_bit))

#घोषणा RTW_CANNOT_IO(padapter) \
			((padapter)->bSurpriseRemoved || \
			 RTW_IS_FUNC_DISABLED((padapter), DF_IO_BIT))

#घोषणा RTW_CANNOT_RX(padapter) \
			((padapter)->bDriverStopped || \
			 (padapter)->bSurpriseRemoved || \
			 RTW_IS_FUNC_DISABLED((padapter), DF_RX_BIT))

#घोषणा RTW_CANNOT_TX(padapter) \
			((padapter)->bDriverStopped || \
			 (padapter)->bSurpriseRemoved || \
			 RTW_IS_FUNC_DISABLED((padapter), DF_TX_BIT))

अटल अंतरभूत u8 *myid(काष्ठा eeprom_priv *peepriv)
अणु
	वापस peepriv->mac_addr;
पूर्ण

/*  HCI Related header file */
#समावेश <sdio_osपूर्णांकf.h>
#समावेश <sdio_ops.h>
#समावेश <sdio_hal.h>

#समावेश <rtw_btcoex.h>

व्योम rtw_indicate_wx_disassoc_event(काष्ठा adapter *padapter);
व्योम rtw_indicate_wx_assoc_event(काष्ठा adapter *padapter);
व्योम rtw_indicate_wx_disassoc_event(काष्ठा adapter *padapter);
व्योम indicate_wx_scan_complete_event(काष्ठा adapter *padapter);
पूर्णांक rtw_change_अगरname(काष्ठा adapter *padapter, स्थिर अक्षर *अगरname);

बाह्य अक्षर *rtw_iniपंचांगac;
बाह्य पूर्णांक rtw_mc2u_disable;
बाह्य पूर्णांक rtw_ht_enable;
बाह्य u32 g_रुको_hiq_empty;
बाह्य u8 g_fwdl_wपूर्णांकपूर्णांक_rdy_fail;
बाह्य u8 g_fwdl_chksum_fail;

#पूर्ण_अगर /* __DRV_TYPES_H__ */
