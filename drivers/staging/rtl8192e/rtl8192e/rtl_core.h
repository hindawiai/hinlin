<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Based on the r8180 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित _RTL_CORE_H
#घोषणा _RTL_CORE_H

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/wireless.h>
#समावेश <linux/समयr.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/पन.स>

/* Need this defined beक्रमe including local include files */
#घोषणा DRV_NAME "rtl819xE"

#समावेश "../rtllib.h"

#समावेश "../dot11d.h"

#समावेश "r8192E_firmware.h"
#समावेश "r8192E_hw.h"

#समावेश "r8190P_def.h"
#समावेश "r8192E_dev.h"

#समावेश "rtl_eeprom.h"
#समावेश "rtl_ps.h"
#समावेश "rtl_pci.h"
#समावेश "rtl_cam.h"

#घोषणा DRV_COPYRIGHT		\
	"Copyright(c) 2008 - 2010 Realsil Semiconductor Corporation"
#घोषणा DRV_AUTHOR  "<wlanfae@realtek.com>"
#घोषणा DRV_VERSION  "0014.0401.2010"

#घोषणा IS_HARDWARE_TYPE_8192SE(_priv)		\
	(((काष्ठा r8192_priv *)rtllib_priv(dev))->card_8192 == NIC_8192SE)

#घोषणा RTL_PCI_DEVICE(vend, dev, cfg) \
	.venकरोr = (vend), .device = (dev), \
	.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID, \
	.driver_data = (kernel_uदीर्घ_t)&(cfg)

#घोषणा TOTAL_CAM_ENTRY		32
#घोषणा CAM_CONTENT_COUNT	8

#घोषणा HAL_HW_PCI_REVISION_ID_8192PCIE		0x01
#घोषणा HAL_HW_PCI_REVISION_ID_8192SE	0x10

#घोषणा RTL819X_DEFAULT_RF_TYPE		RF_1T2R

#घोषणा RTLLIB_WATCH_DOG_TIME		2000

#घोषणा MAX_DEV_ADDR_SIZE		8  /*support till 64 bit bus width OS*/
#घोषणा MAX_FIRMWARE_INFORMATION_SIZE   32
#घोषणा MAX_802_11_HEADER_LENGTH	(40 + MAX_FIRMWARE_INFORMATION_SIZE)
#घोषणा ENCRYPTION_MAX_OVERHEAD		128
#घोषणा MAX_FRAGMENT_COUNT		8
#घोषणा MAX_TRANSMIT_BUFFER_SIZE	\
	(1600 + (MAX_802_11_HEADER_LENGTH + ENCRYPTION_MAX_OVERHEAD) *	\
	 MAX_FRAGMENT_COUNT)

#घोषणा CMDPACKET_FRAG_SIZE (4 * (MAX_TRANSMIT_BUFFER_SIZE / 4) - 8)

#घोषणा DEFAULT_FRAG_THRESHOLD	2342U
#घोषणा MIN_FRAG_THRESHOLD	256U
#घोषणा DEFAULT_BEACONINTERVAL	0x64U

#घोषणा DEFAULT_RETRY_RTS	7
#घोषणा DEFAULT_RETRY_DATA	7

#घोषणा	PHY_RSSI_SLID_WIN_MAX			100

#घोषणा TxBBGainTableLength			37
#घोषणा CCKTxBBGainTableLength			23

#घोषणा CHANNEL_PLAN_LEN			10
#घोषणा sCrcLng					4

#घोषणा NIC_SEND_HANG_THRESHOLD_NORMAL		4
#घोषणा NIC_SEND_HANG_THRESHOLD_POWERSAVE	8

#घोषणा MAX_TX_QUEUE				9

#घोषणा MAX_RX_QUEUE				1

#घोषणा MAX_RX_COUNT				64
#घोषणा MAX_TX_QUEUE_COUNT			9

बाह्य पूर्णांक hwwep;

क्रमागत nic_t अणु
	NIC_UNKNOWN     = 0,
	NIC_8192E       = 1,
	NIC_8190P       = 2,
	NIC_8192SE      = 4,
	NIC_8192CE	= 5,
	NIC_8192CU	= 6,
	NIC_8192DE	= 7,
	NIC_8192DU	= 8,
पूर्ण;

क्रमागत rt_eeprom_type अणु
	EEPROM_93C46,
	EEPROM_93C56,
पूर्ण;

क्रमागत dcmg_txcmd_op अणु
	TXCMD_TXRA_HISTORY_CTRL		= 0xFF900000,
	TXCMD_RESET_TX_PKT_BUFF		= 0xFF900001,
	TXCMD_RESET_RX_PKT_BUFF		= 0xFF900002,
	TXCMD_SET_TX_DURATION		= 0xFF900003,
	TXCMD_SET_RX_RSSI		= 0xFF900004,
	TXCMD_SET_TX_PWR_TRACKING	= 0xFF900005,
	TXCMD_XXXX_CTRL,
पूर्ण;

क्रमागत rt_rf_type_819xu अणु
	RF_TYPE_MIN = 0,
	RF_8225,
	RF_8256,
	RF_8258,
	RF_6052 = 4,
	RF_PSEUDO_11N = 5,
पूर्ण;

क्रमागत rt_customer_id अणु
	RT_CID_DEFAULT	  = 0,
	RT_CID_8187_ALPHA0      = 1,
	RT_CID_8187_SERCOMM_PS  = 2,
	RT_CID_8187_HW_LED      = 3,
	RT_CID_8187_NETGEAR     = 4,
	RT_CID_WHQL	     = 5,
	RT_CID_819x_CAMEO       = 6,
	RT_CID_819x_RUNTOP      = 7,
	RT_CID_819x_Senao       = 8,
	RT_CID_TOSHIBA	  = 9,
	RT_CID_819x_Netcore     = 10,
	RT_CID_Nettronix	= 11,
	RT_CID_DLINK	    = 12,
	RT_CID_PRONET	   = 13,
	RT_CID_COREGA	   = 14,
	RT_CID_819x_ALPHA       = 15,
	RT_CID_819x_Sitecom     = 16,
	RT_CID_CCX	      = 17,
	RT_CID_819x_Lenovo      = 18,
	RT_CID_819x_QMI	 = 19,
	RT_CID_819x_Edimax_Belkin = 20,
	RT_CID_819x_Sercomm_Belkin = 21,
	RT_CID_819x_CAMEO1 = 22,
	RT_CID_819x_MSI = 23,
	RT_CID_819x_Acer = 24,
	RT_CID_819x_HP	= 27,
	RT_CID_819x_CLEVO = 28,
	RT_CID_819x_Arcadyan_Belkin = 29,
	RT_CID_819x_SAMSUNG = 30,
	RT_CID_819x_WNC_COREGA = 31,
पूर्ण;

क्रमागत reset_type अणु
	RESET_TYPE_NORESET = 0x00,
	RESET_TYPE_NORMAL = 0x01,
	RESET_TYPE_SILENT = 0x02
पूर्ण;

काष्ठा rt_stats अणु
	अचिन्हित दीर्घ rxrdu;
	अचिन्हित दीर्घ rxok;
	अचिन्हित दीर्घ rxdatacrcerr;
	अचिन्हित दीर्घ rxmgmtcrcerr;
	अचिन्हित दीर्घ rxcrcerrmin;
	अचिन्हित दीर्घ rxcrcerrmid;
	अचिन्हित दीर्घ rxcrcerrmax;
	अचिन्हित दीर्घ received_rate_histogram[4][32];
	अचिन्हित दीर्घ received_preamble_GI[2][32];
	अचिन्हित दीर्घ numpacket_matchbssid;
	अचिन्हित दीर्घ numpacket_toself;
	अचिन्हित दीर्घ num_process_phyinfo;
	अचिन्हित दीर्घ numqry_phystatus;
	अचिन्हित दीर्घ numqry_phystatusCCK;
	अचिन्हित दीर्घ numqry_phystatusHT;
	अचिन्हित दीर्घ received_bwtype[5];
	अचिन्हित दीर्घ rxoverflow;
	अचिन्हित दीर्घ rxपूर्णांक;
	अचिन्हित दीर्घ पूर्णांकs;
	अचिन्हित दीर्घ shपूर्णांकs;
	अचिन्हित दीर्घ txoverflow;
	अचिन्हित दीर्घ txbeokपूर्णांक;
	अचिन्हित दीर्घ txbkokपूर्णांक;
	अचिन्हित दीर्घ txviokपूर्णांक;
	अचिन्हित दीर्घ txvookपूर्णांक;
	अचिन्हित दीर्घ txbeaconokपूर्णांक;
	अचिन्हित दीर्घ txbeaconerr;
	अचिन्हित दीर्घ txmanageokपूर्णांक;
	अचिन्हित दीर्घ txcmdpktokपूर्णांक;
	अचिन्हित दीर्घ txbytesmulticast;
	अचिन्हित दीर्घ txbytesbroadcast;
	अचिन्हित दीर्घ txbytesunicast;
	अचिन्हित दीर्घ rxbytesunicast;
	अचिन्हित दीर्घ txretrycount;
	u8	last_packet_rate;
	अचिन्हित दीर्घ slide_संकेत_strength[100];
	अचिन्हित दीर्घ slide_evm[100];
	अचिन्हित दीर्घ	slide_rssi_total;
	अचिन्हित दीर्घ slide_evm_total;
	दीर्घ संकेत_strength;
	दीर्घ संकेत_quality;
	दीर्घ last_संकेत_strength_inpercent;
	दीर्घ	recv_संकेत_घातer;
	u8 rx_rssi_percentage[4];
	u8 rx_evm_percentage[2];
	दीर्घ rxSNRdB[4];
	u32 Slide_Beacon_pwdb[100];
	u32 Slide_Beacon_Total;
	u32	CurrentShowTxate;
पूर्ण;

काष्ठा channel_access_setting अणु
	u16 SIFS_Timer;
	u16 DIFS_Timer;
	u16 SlotTimeTimer;
	u16 EIFS_Timer;
	u16 CWminIndex;
	u16 CWmaxIndex;
पूर्ण;

काष्ठा init_gain अणु
	u8	xaagccore1;
	u8	xbagccore1;
	u8	xcagccore1;
	u8	xdagccore1;
	u8	cca;

पूर्ण;

काष्ठा tx_ring अणु
	u32 *desc;
	u8 nStuckCount;
	काष्ठा tx_ring *next;
पूर्ण __packed;

काष्ठा rtl8192_tx_ring अणु
	काष्ठा tx_desc *desc;
	dma_addr_t dma;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक entries;
	काष्ठा sk_buff_head queue;
पूर्ण;



काष्ठा rtl819x_ops अणु
	क्रमागत nic_t nic_type;
	व्योम (*get_eeprom_size)(काष्ठा net_device *dev);
	व्योम (*init_adapter_variable)(काष्ठा net_device *dev);
	व्योम (*init_beक्रमe_adapter_start)(काष्ठा net_device *dev);
	bool (*initialize_adapter)(काष्ठा net_device *dev);
	व्योम (*link_change)(काष्ठा net_device *dev);
	व्योम (*tx_fill_descriptor)(काष्ठा net_device *dev,
				   काष्ठा tx_desc *tx_desc,
				   काष्ठा cb_desc *cb_desc,
				   काष्ठा sk_buff *skb);
	व्योम (*tx_fill_cmd_descriptor)(काष्ठा net_device *dev,
				       काष्ठा tx_desc_cmd *entry,
				       काष्ठा cb_desc *cb_desc,
				       काष्ठा sk_buff *skb);
	bool (*rx_query_status_descriptor)(काष्ठा net_device *dev,
					   काष्ठा rtllib_rx_stats *stats,
					   काष्ठा rx_desc *pdesc,
					   काष्ठा sk_buff *skb);
	bool (*rx_command_packet_handler)(काष्ठा net_device *dev,
					  काष्ठा sk_buff *skb,
					  काष्ठा rx_desc *pdesc);
	व्योम (*stop_adapter)(काष्ठा net_device *dev, bool reset);
	व्योम (*update_ratr_table)(काष्ठा net_device *dev);
	व्योम (*irq_enable)(काष्ठा net_device *dev);
	व्योम (*irq_disable)(काष्ठा net_device *dev);
	व्योम (*irq_clear)(काष्ठा net_device *dev);
	व्योम (*rx_enable)(काष्ठा net_device *dev);
	व्योम (*tx_enable)(काष्ठा net_device *dev);
	व्योम (*पूर्णांकerrupt_recognized)(काष्ठा net_device *dev,
				     u32 *p_पूर्णांकa, u32 *p_पूर्णांकb);
	bool (*TxCheckStuckHandler)(काष्ठा net_device *dev);
	bool (*RxCheckStuckHandler)(काष्ठा net_device *dev);
पूर्ण;

काष्ठा r8192_priv अणु
	काष्ठा pci_dev *pdev;
	काष्ठा pci_dev *bridge_pdev;

	bool		bfirst_init;
	bool		bfirst_after_करोwn;
	bool		initialized_at_probe;
	bool		being_init_adapter;
	bool		bDriverIsGoingToUnload;

	पूर्णांक		irq;
	लघु	irq_enabled;

	लघु	up;
	लघु	up_first_समय;
	काष्ठा delayed_work		update_beacon_wq;
	काष्ठा delayed_work		watch_करोg_wq;
	काष्ठा delayed_work		txघातer_tracking_wq;
	काष्ठा delayed_work		rfpath_check_wq;
	काष्ठा delayed_work		gpio_change_rf_wq;

	काष्ठा channel_access_setting ChannelAccessSetting;

	काष्ठा rtl819x_ops			*ops;
	काष्ठा rtllib_device			*rtllib;

	काष्ठा work_काष्ठा				reset_wq;

	काष्ठा log_पूर्णांक_8190 InterruptLog;

	क्रमागत rt_customer_id CustomerID;


	क्रमागत rt_rf_type_819xu rf_chip;
	क्रमागत ht_channel_width CurrentChannelBW;
	काष्ठा bb_reg_definition PHYRegDef[4];
	काष्ठा rate_adaptive rate_adaptive;

	क्रमागत acm_method AcmMethod;

	काष्ठा rt_firmware			*pFirmware;
	क्रमागत rtl819x_loopback LoopbackMode;

	काष्ठा समयr_list			watch_करोg_समयr;
	काष्ठा समयr_list			fsync_समयr;
	काष्ठा समयr_list			gpio_polling_समयr;

	spinlock_t				irq_th_lock;
	spinlock_t				tx_lock;
	spinlock_t				rf_ps_lock;
	spinlock_t				ps_lock;

	काष्ठा sk_buff_head		skb_queue;

	काष्ठा tasklet_काष्ठा		irq_rx_tasklet;
	काष्ठा tasklet_काष्ठा		irq_tx_tasklet;
	काष्ठा tasklet_काष्ठा		irq_prepare_beacon_tasklet;

	काष्ठा mutex				wx_mutex;
	काष्ठा mutex				rf_mutex;
	काष्ठा mutex				mutex;

	काष्ठा rt_stats stats;
	काष्ठा iw_statistics			wstats;

	लघु (*rf_set_sens)(काष्ठा net_device *dev, लघु sens);
	u8 (*rf_set_chan)(काष्ठा net_device *dev, u8 ch);

	काष्ठा rx_desc *rx_ring[MAX_RX_QUEUE];
	काष्ठा sk_buff	*rx_buf[MAX_RX_QUEUE][MAX_RX_COUNT];
	dma_addr_t	rx_ring_dma[MAX_RX_QUEUE];
	अचिन्हित पूर्णांक	rx_idx[MAX_RX_QUEUE];
	पूर्णांक		rxringcount;
	u16		rxbuffersize;

	u64		LastRxDescTSF;

	u32		ReceiveConfig;
	u8		retry_data;
	u8		retry_rts;
	u16		rts;

	काष्ठा rtl8192_tx_ring tx_ring[MAX_TX_QUEUE_COUNT];
	पूर्णांक		 txringcount;
	atomic_t	tx_pending[0x10];

	u16		ShortRetryLimit;
	u16		LongRetryLimit;

	bool		bHwRadioOff;
	bool		blinked_ingpio;
	u8		polling_समयr_on;

	/**********************************************************/

	क्रमागत card_type अणु
		PCI, MINIPCI,
		CARDBUS, USB
	पूर्ण card_type;

	काष्ठा work_काष्ठा qos_activate;

	लघु	promisc;

	लघु	chan;
	लघु	sens;
	लघु	max_sens;

	u8 ScanDelay;
	bool ps_क्रमce;

	u32 irq_mask[2];

	u8 Rf_Mode;
	क्रमागत nic_t card_8192;
	u8 card_8192_version;

	u8 rf_type;
	u8 IC_Cut;
	अक्षर nick[IW_ESSID_MAX_SIZE + 1];
	u8 check_roaming_cnt;

	u32 SilentResetRxSlotIndex;
	u32 SilentResetRxStuckEvent[MAX_SILENT_RESET_RX_SLOT_NUM];

	u16 basic_rate;
	u8 लघु_preamble;
	u8 करोt11CurrentPreambleMode;
	u8 slot_समय;
	u16 SअगरsTime;

	bool AutoloadFailFlag;

	लघु	epromtype;
	u16 eeprom_vid;
	u16 eeprom_did;
	u8 eeprom_CustomerID;
	u16 eeprom_ChannelPlan;

	u8 EEPROMTxPowerLevelCCK[14];
	u8 EEPROMTxPowerLevelOFDM24G[14];
	u8 EEPROMRfACCKChnl1TxPwLevel[3];
	u8 EEPROMRfAOfdmChnlTxPwLevel[3];
	u8 EEPROMRfCCCKChnl1TxPwLevel[3];
	u8 EEPROMRfCOfdmChnlTxPwLevel[3];
	u16 EEPROMAntPwDअगरf;
	u8 EEPROMThermalMeter;
	u8 EEPROMCrystalCap;

	u8 EEPROMLegacyHTTxPowerDअगरf;

	u8 CrystalCap;
	u8 ThermalMeter[2];

	u8 SwChnlInProgress;
	u8 SwChnlStage;
	u8 SwChnlStep;
	u8 SetBWModeInProgress;

	u8 nCur40MhzPrimeSC;

	u32 RfReg0Value[4];
	u8 NumTotalRFPath;
	bool brfpath_rxenable[4];

	bool bTXPowerDataReadFromEEPORM;

	u16 RegChannelPlan;
	u16 ChannelPlan;

	bool RegRfOff;
	bool isRFOff;
	bool bInPowerSaveMode;
	u8 bHwRfOffAction;

	bool RFChangeInProgress;
	bool SetRFPowerStateInProgress;
	bool bdisable_nic;

	u8 DM_Type;

	u8 CckPwEnl;
	u16 TSSI_13dBm;
	u32 Pwr_Track;
	u8 CCKPresentAttentuation_20Mशेष;
	u8 CCKPresentAttentuation_40Mशेष;
	s8 CCKPresentAttentuation_dअगरference;
	s8 CCKPresentAttentuation;
	दीर्घ undecorated_smoothed_pwdb;

	u32 MCSTxPowerLevelOriginalOffset[6];
	u8 TxPowerLevelCCK[14];
	u8 TxPowerLevelCCK_A[14];
	u8 TxPowerLevelCCK_C[14];
	u8		TxPowerLevelOFDM24G[14];
	u8		TxPowerLevelOFDM24G_A[14];
	u8		TxPowerLevelOFDM24G_C[14];
	u8		LegacyHTTxPowerDअगरf;
	s8		RF_C_TxPwDअगरf;
	u8		AntennaTxPwDअगरf[3];

	bool		bDynamicTxHighPower;
	bool		bDynamicTxLowPower;
	bool		bLastDTPFlag_High;
	bool		bLastDTPFlag_Low;

	u8		rfa_txघातertrackingindex;
	u8		rfa_txघातertrackingindex_real;
	u8		rfa_txघातertracking_शेष;
	u8		rfc_txघातertrackingindex;
	u8		rfc_txघातertrackingindex_real;
	bool		btxघातer_tracking;
	bool		bcck_in_ch14;

	u8		txघातer_count;
	bool		btxघातer_trackingInit;

	u8		OFDM_index[2];
	u8		CCK_index;

	u8		Record_CCK_20Mindex;
	u8		Record_CCK_40Mindex;

	काष्ठा init_gain initgain_backup;
	u8		DefaultInitialGain[4];
	bool		bis_any_nonbepkts;
	bool		bcurrent_turbo_EDCA;
	bool		bis_cur_rdlstate;

	bool		bfsync_processing;
	u32		rate_record;
	u32		rateCountDअगरfRecord;
	u32		ContinueDअगरfCount;
	bool		bचयन_fsync;
	u8		framesync;
	u32		framesyncC34;
	u8		framesyncMonitor;

	u32		reset_count;

	क्रमागत reset_type ResetProgress;
	bool		bForcedSilentReset;
	bool		bDisableNormalResetCheck;
	u16		TxCounter;
	u16		RxCounter;
	bool		bResetInProgress;
	bool		क्रमce_reset;
	bool		क्रमce_lps;

	bool		chan_क्रमced;

	u8		PwrDoमुख्यProtect;
	u8		H2CTxCmdSeq;
पूर्ण;

बाह्य स्थिर काष्ठा ethtool_ops rtl819x_ethtool_ops;

u8 rtl92e_पढ़ोb(काष्ठा net_device *dev, पूर्णांक x);
u32 rtl92e_पढ़ोl(काष्ठा net_device *dev, पूर्णांक x);
u16 rtl92e_पढ़ोw(काष्ठा net_device *dev, पूर्णांक x);
व्योम rtl92e_ग_लिखोb(काष्ठा net_device *dev, पूर्णांक x, u8 y);
व्योम rtl92e_ग_लिखोw(काष्ठा net_device *dev, पूर्णांक x, u16 y);
व्योम rtl92e_ग_लिखोl(काष्ठा net_device *dev, पूर्णांक x, u32 y);

व्योम क्रमce_pci_posting(काष्ठा net_device *dev);

व्योम rtl92e_rx_enable(काष्ठा net_device *);
व्योम rtl92e_tx_enable(काष्ठा net_device *);

व्योम rtl92e_hw_sleep_wq(व्योम *data);
व्योम rtl92e_commit(काष्ठा net_device *dev);

व्योम rtl92e_check_rfctrl_gpio_समयr(काष्ठा समयr_list *t);

व्योम rtl92e_hw_wakeup_wq(व्योम *data);

व्योम rtl92e_reset_desc_ring(काष्ठा net_device *dev);
व्योम rtl92e_set_wireless_mode(काष्ठा net_device *dev, u8 wireless_mode);
व्योम rtl92e_irq_enable(काष्ठा net_device *dev);
व्योम rtl92e_config_rate(काष्ठा net_device *dev, u16 *rate_config);
व्योम rtl92e_irq_disable(काष्ठा net_device *dev);

व्योम rtl92e_update_rx_pkt_बारtamp(काष्ठा net_device *dev,
				    काष्ठा rtllib_rx_stats *stats);
दीर्घ rtl92e_translate_to_dbm(काष्ठा r8192_priv *priv, u8 संकेत_strength_index);
व्योम rtl92e_update_rx_statistics(काष्ठा r8192_priv *priv,
				 काष्ठा rtllib_rx_stats *pprevious_stats);
u8 rtl92e_evm_db_to_percent(s8 value);
u8 rtl92e_rx_db_to_percent(s8 antघातer);
व्योम rtl92e_copy_mpdu_stats(काष्ठा rtllib_rx_stats *psrc_stats,
			    काष्ठा rtllib_rx_stats *ptarget_stats);
bool rtl92e_enable_nic(काष्ठा net_device *dev);
bool rtl92e_disable_nic(काष्ठा net_device *dev);

bool rtl92e_set_rf_state(काष्ठा net_device *dev,
			 क्रमागत rt_rf_घातer_state StateToSet,
			 RT_RF_CHANGE_SOURCE ChangeSource);
#पूर्ण_अगर
