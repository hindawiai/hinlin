<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8188E_HAL_H__
#घोषणा __RTL8188E_HAL_H__

/* include HAL Related header after HAL Related compiling flags */
#समावेश "rtl8188e_spec.h"
#समावेश "hal8188e_phy_reg.h"
#समावेश "hal8188e_phy_cfg.h"
#समावेश "rtl8188e_dm.h"
#समावेश "rtl8188e_recv.h"
#समावेश "rtl8188e_xmit.h"
#समावेश "rtl8188e_cmd.h"
#समावेश "pwrseq.h"
#समावेश "rtw_efuse.h"
#समावेश "rtw_sreset.h"
#समावेश "odm_precomp.h"

/*  Fw Array */
#घोषणा Rtl8188E_FwImageArray		Rtl8188EFwImgArray
#घोषणा Rtl8188E_FWImgArrayLength	Rtl8188EFWImgArrayLength

#घोषणा RTL8188E_FW_UMC_IMG			"rtl8188E\\rtl8188efw.bin"
#घोषणा RTL8188E_PHY_REG			"rtl8188E\\PHY_REG_1T.txt"
#घोषणा RTL8188E_PHY_RADIO_A			"rtl8188E\\radio_a_1T.txt"
#घोषणा RTL8188E_PHY_RADIO_B			"rtl8188E\\radio_b_1T.txt"
#घोषणा RTL8188E_AGC_TAB			"rtl8188E\\AGC_TAB_1T.txt"
#घोषणा RTL8188E_PHY_MACREG			"rtl8188E\\MAC_REG.txt"
#घोषणा RTL8188E_PHY_REG_PG			"rtl8188E\\PHY_REG_PG.txt"
#घोषणा RTL8188E_PHY_REG_MP			"rtl8188E\\PHY_REG_MP.txt"

/* RTL8188E Power Configuration CMDs क्रम USB/SDIO पूर्णांकerfaces */
#घोषणा Rtl8188E_NIC_PWR_ON_FLOW		rtl8188E_घातer_on_flow
#घोषणा Rtl8188E_NIC_RF_OFF_FLOW		rtl8188E_radio_off_flow
#घोषणा Rtl8188E_NIC_DISABLE_FLOW		rtl8188E_card_disable_flow
#घोषणा Rtl8188E_NIC_ENABLE_FLOW		rtl8188E_card_enable_flow
#घोषणा Rtl8188E_NIC_SUSPEND_FLOW		rtl8188E_suspend_flow
#घोषणा Rtl8188E_NIC_RESUME_FLOW		rtl8188E_resume_flow
#घोषणा Rtl8188E_NIC_PDN_FLOW			rtl8188E_hwpdn_flow
#घोषणा Rtl8188E_NIC_LPS_ENTER_FLOW		rtl8188E_enter_lps_flow
#घोषणा Rtl8188E_NIC_LPS_LEAVE_FLOW		rtl8188E_leave_lps_flow

#घोषणा DRVINFO_SZ	4 /*  unit is 8bytes */
#घोषणा PageNum_128(_Len)	(u32)(((_Len) >> 7) + ((_Len) & 0x7F ? 1 : 0))

/*  करोwnload firmware related data काष्ठाure */
#घोषणा FW_8188E_SIZE			0x4000 /* 16384,16k */
#घोषणा FW_8188E_START_ADDRESS		0x1000
#घोषणा FW_8188E_END_ADDRESS		0x1FFF /* 0x5FFF */

#घोषणा MAX_PAGE_SIZE			4096	/*  @ page : 4k bytes */

#घोषणा IS_FW_HEADER_EXIST(_pFwHdr)				 \
	((le16_to_cpu(_pFwHdr->signature) & 0xFFF0) == 0x92C0 || \
	(le16_to_cpu(_pFwHdr->signature) & 0xFFF0) == 0x88C0 ||  \
	(le16_to_cpu(_pFwHdr->signature) & 0xFFF0) == 0x2300 ||  \
	(le16_to_cpu(_pFwHdr->signature) & 0xFFF0) == 0x88E0)

#घोषणा DRIVER_EARLY_INT_TIME		0x05
#घोषणा BCN_DMA_ATIME_INT_TIME		0x02

क्रमागत usb_rx_agg_mode अणु
	USB_RX_AGG_DISABLE,
	USB_RX_AGG_DMA,
	USB_RX_AGG_USB,
	USB_RX_AGG_MIX
पूर्ण;

#घोषणा MAX_RX_DMA_BUFFER_SIZE_88E				\
      0x2400 /* 9k क्रम 88E nornal chip , MaxRxBuff=10k-max(TxReportSize(64*8),
	      * WOLPattern(16*24))
	      */

#घोषणा MAX_TX_REPORT_BUFFER_SIZE		0x0400 /*  1k */

/*  BK, BE, VI, VO, HCCA, MANAGEMENT, COMMAND, HIGH, BEACON. */
#घोषणा MAX_TX_QUEUE			9

#घोषणा TX_SELE_HQ			BIT(0)		/*  High Queue */
#घोषणा TX_SELE_LQ			BIT(1)		/*  Low Queue */
#घोषणा TX_SELE_NQ			BIT(2)		/*  Normal Queue */

/*  Note: We will भागide number of page equally क्रम each queue other
 *  than खुला queue!
 */
/*  22k = 22528 bytes = 176 pages (@page =  128 bytes) */
/*  must reserved about 7 pages क्रम LPS =>  176-7 = 169 (0xA9) */
/*  2*BCN / 1*ps-poll / 1*null-data /1*prob_rsp /1*QOS null-data /1*BT QOS
 *  null-data
 */

#घोषणा TX_TOTAL_PAGE_NUMBER_88E		0xA9/*   169 (21632=> 21k) */

#घोषणा TX_PAGE_BOUNDARY_88E (TX_TOTAL_PAGE_NUMBER_88E + 1)

/* Note: For Normal Chip Setting ,modअगरy later */
#घोषणा WMM_NORMAL_TX_TOTAL_PAGE_NUMBER			\
	TX_TOTAL_PAGE_NUMBER_88E  /* 0xA9 , 0xb0=>176=>22k */
#घोषणा WMM_NORMAL_TX_PAGE_BOUNDARY_88E			\
	(WMM_NORMAL_TX_TOTAL_PAGE_NUMBER + 1) /* 0xA9 */

/* Chip specअगरic */
#घोषणा CHIP_BONDING_IDENTIFIER(_value)	(((_value) >> 22) & 0x3)
#घोषणा CHIP_BONDING_92C_1T2R	0x1
#घोषणा CHIP_BONDING_88C_USB_MCARD	0x2
#घोषणा CHIP_BONDING_88C_USB_HP	0x1
#समावेश "HalVerDef.h"
#समावेश "hal_com.h"

/* Channel Plan */
क्रमागत ChannelPlan अणु
	CHPL_FCC	= 0,
	CHPL_IC		= 1,
	CHPL_ETSI	= 2,
	CHPL_SPA	= 3,
	CHPL_FRANCE	= 4,
	CHPL_MKK	= 5,
	CHPL_MKK1	= 6,
	CHPL_ISRAEL	= 7,
	CHPL_TELEC	= 8,
	CHPL_GLOBAL	= 9,
	CHPL_WORLD	= 10,
पूर्ण;

काष्ठा txघातerinfo24g अणु
	u8 IndexCCK_Base[MAX_RF_PATH][MAX_CHNL_GROUP_24G];
	u8 IndexBW40_Base[MAX_RF_PATH][MAX_CHNL_GROUP_24G];
	/* If only one tx, only BW20 and OFDM are used. */
	s8 CCK_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8 OFDM_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8 BW20_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8 BW40_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
पूर्ण;

#घोषणा EFUSE_REAL_CONTENT_LEN		512
#घोषणा EFUSE_MAX_SECTION		16
#घोषणा EFUSE_IC_ID_OFFSET		506 /* For some inferior IC purpose*/
#घोषणा AVAILABLE_EFUSE_ADDR(addr)	(addr < EFUSE_REAL_CONTENT_LEN)
/*  To prevent out of boundary programming हाल, */
/*  leave 1byte and program full section */
/*  9bytes + 1byt + 5bytes and pre 1byte. */
/*  For worst हाल: */
/*  | 1byte|----8bytes----|1byte|--5bytes--| */
/*  |         |            Reserved(14bytes)	      | */

/*  PG data exclude header, dummy 6 bytes from CP test and reserved 1byte. */
#घोषणा EFUSE_OOB_PROTECT_BYTES			15

#घोषणा		HWSET_MAX_SIZE_88E		512

#घोषणा		EFUSE_REAL_CONTENT_LEN_88E	256
#घोषणा		EFUSE_MAP_LEN_88E		512
#घोषणा EFUSE_MAP_LEN			EFUSE_MAP_LEN_88E
#घोषणा		EFUSE_MAX_SECTION_88E		64
#घोषणा		EFUSE_MAX_WORD_UNIT_88E		4
#घोषणा		EFUSE_IC_ID_OFFSET_88E		506
#घोषणा		AVAILABLE_EFUSE_ADDR_88E(addr)			\
	(addr < EFUSE_REAL_CONTENT_LEN_88E)
/*  To prevent out of boundary programming हाल, leave 1byte and program
 *  full section
 */
/*  9bytes + 1byt + 5bytes and pre 1byte. */
/*  For worst हाल: */
/*  | 2byte|----8bytes----|1byte|--7bytes--| 92D */
/*  PG data exclude header, dummy 7 bytes from CP test and reserved 1byte. */
#घोषणा		EFUSE_OOB_PROTECT_BYTES_88E	18
#घोषणा		EFUSE_PROTECT_BYTES_BANK_88E	16

/* EFUSE क्रम BT definition */
#घोषणा EFUSE_BT_REAL_CONTENT_LEN	1536	/*  512*3 */
#घोषणा EFUSE_BT_MAP_LEN		1024	/*  1k bytes */
#घोषणा EFUSE_BT_MAX_SECTION		128	/*  1024/8 */

#घोषणा EFUSE_PROTECT_BYTES_BANK	16

काष्ठा hal_data_8188e अणु
	काष्ठा HAL_VERSION	VersionID;
	u16	CustomerID;
	u16	FirmwareVersion;
	u16	FirmwareVersionRev;
	u16	FirmwareSubVersion;
	u16	FirmwareSignature;
	u8	PGMaxGroup;
	/* current WIFI_PHY values */
	u32	ReceiveConfig;
	क्रमागत wireless_mode CurrentWirelessMode;
	क्रमागत ht_channel_width CurrentChannelBW;
	u8	CurrentChannel;
	u8	nCur40MhzPrimeSC;/*  Control channel sub-carrier */

	u16	BasicRateSet;

	u8	BoardType;

	/*  EEPROM setting. */
	u16	EEPROMVID;
	u16	EEPROMPID;
	u16	EEPROMSVID;
	u16	EEPROMSDID;
	u8	EEPROMCustomerID;
	u8	EEPROMSubCustomerID;
	u8	EEPROMVersion;
	u8	EEPROMRegulatory;

	u8	bTXPowerDataReadFromEEPORM;
	u8	EEPROMThermalMeter;
	u8	bAPKThermalMeterIgnore;

	bool	EepromOrEfuse;

	u8	Index24G_CCK_Base[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
	u8	Index24G_BW40_Base[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
	/* If only one tx, only BW20 and OFDM are used. */
	s8	CCK_24G_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8	OFDM_24G_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8	BW20_24G_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8	BW40_24G_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];

	u8	TxPwrLevelCck[RF_PATH_MAX][CHANNEL_MAX_NUMBER];
	/*  For HT 40MHZ pwr */
	u8	TxPwrLevelHT40_1S[RF_PATH_MAX][CHANNEL_MAX_NUMBER];
	/*  For HT 40MHZ pwr */
	u8	TxPwrLevelHT40_2S[RF_PATH_MAX][CHANNEL_MAX_NUMBER];
	/*  HT 20<->40 Pwr dअगरf */
	u8	TxPwrHt20Dअगरf[RF_PATH_MAX][CHANNEL_MAX_NUMBER];
	/*  For HT<->legacy pwr dअगरf */
	u8	TxPwrLegacyHtDअगरf[RF_PATH_MAX][CHANNEL_MAX_NUMBER];
	/*  For घातer group */
	u8	PwrGroupHT20[RF_PATH_MAX][CHANNEL_MAX_NUMBER];
	u8	PwrGroupHT40[RF_PATH_MAX][CHANNEL_MAX_NUMBER];

	u8	LegacyHTTxPowerDअगरf;/*  Legacy to HT rate घातer dअगरf */
	/*  The current Tx Power Level */
	u8	CurrentCckTxPwrIdx;
	u8	CurrentOfdm24GTxPwrIdx;
	u8	CurrentBW2024GTxPwrIdx;
	u8	CurrentBW4024GTxPwrIdx;

	/*  Read/ग_लिखो are allow क्रम following hardware inक्रमmation variables */
	u8	framesync;
	u32	framesyncC34;
	u8	framesyncMonitor;
	u8	DefaultInitialGain[4];
	u8	pwrGroupCnt;
	u32	MCSTxPowerLevelOriginalOffset[MAX_PG_GROUP][16];
	u32	CCKTxPowerLevelOriginalOffset;

	u8	CrystalCap;

	u32	AcParam_BE; /* Original parameter क्रम BE, use क्रम EDCA turbo. */

	काष्ठा bb_reg_def PHYRegDef[4];	/* Radio A/B/C/D */

	u32	RfRegChnlVal[2];

	/* RDG enable */
	bool	 bRDGEnable;

	/* क्रम host message to fw */
	u8	LastHMEBoxNum;

	u8	RegTxPause;
	/*  Beacon function related global variable. */
	u32	RegBcnCtrlVal;
	u8	RegFwHwTxQCtrl;
	u8	RegReg542;
	u8	RegCR_1;

	काष्ठा dm_priv	dmpriv;
	काष्ठा odm_dm_काष्ठा odmpriv;
	काष्ठा sreset_priv srestpriv;

	u8	CurAntenna;
	u8	AntDivCfg;
	u8	TRxAntDivType;

	u8	bDumpRxPkt;/* क्रम debug */
	u8	bDumpTxPkt;/* क्रम debug */
	u8	FwRsvdPageStartOffset; /* Reserve page start offset except
					*  beacon in TxQ.
					*/

	/*  2010/08/09 MH Add CU घातer करोwn mode. */
	bool		pwrकरोwn;

	/*  Add क्रम dual MAC  0--Mac0 1--Mac1 */
	u32	पूर्णांकerfaceIndex;

	u8	OutEpQueueSel;
	u8	OutEpNumber;

	u16	EfuseUsedBytes;

	/*  Auto FSM to Turn On, include घड़ी, isolation, घातer control
	 *  क्रम MAC only
	 */
	u8	bMacPwrCtrlOn;

	u32	UsbBulkOutSize;

	/*  Interrupt relatd रेजिस्टर inक्रमmation. */
	u32	IntArray[3];/* HISR0,HISR1,HSISR */
	u32	IntrMask[3];
	u8	C2hArray[16];
	u8	UsbTxAggMode;
	u8	UsbTxAggDescNum;
	u16	HwRxPageSize;		/*  Hardware setting */
	u32	MaxUsbRxAggBlock;

	क्रमागत usb_rx_agg_mode UsbRxAggMode;
	u8	UsbRxAggBlockCount;	/*  USB Block count. Block size is
					 * 512-byte in high speed and 64-byte
					 * in full speed
					 */
	u8	UsbRxAggBlockTimeout;
	u8	UsbRxAggPageCount;	/*  8192C DMA page count */
	u8	UsbRxAggPageTimeout;
पूर्ण;

व्योम Hal_GetChnlGroup88E(u8 chnl, u8 *group);

/*  rtl8188e_hal_init.c */
व्योम _8051Reset88E(काष्ठा adapter *padapter);
व्योम rtl8188e_InitializeFirmwareVars(काष्ठा adapter *padapter);

s32 InitLLTTable(काष्ठा adapter *padapter, u8 txpktbuf_bndy);

/*  EFuse */
व्योम Hal_InitPGData88E(काष्ठा adapter *padapter);
व्योम Hal_EfuseParseIDCode88E(काष्ठा adapter *padapter, u8 *hwinfo);
व्योम Hal_ReadTxPowerInfo88E(काष्ठा adapter *padapter, u8 *hwinfo,
			    bool AutoLoadFail);

व्योम Hal_EfuseParseEEPROMVer88E(काष्ठा adapter *padapter, u8 *hwinfo,
				bool AutoLoadFail);
व्योम rtl8188e_EfuseParseChnlPlan(काष्ठा adapter *padapter, u8 *hwinfo,
				 bool AutoLoadFail);
व्योम Hal_EfuseParseCustomerID88E(काष्ठा adapter *padapter, u8 *hwinfo,
				 bool AutoLoadFail);
व्योम Hal_ReadAntennaDiversity88E(काष्ठा adapter *pAdapter, u8 *PROMContent,
				 bool AutoLoadFail);
व्योम Hal_ReadThermalMeter_88E(काष्ठा adapter *dapter, u8 *PROMContent,
			      bool AutoloadFail);
व्योम Hal_EfuseParseXtal_8188E(काष्ठा adapter *pAdapter, u8 *hwinfo,
			      bool AutoLoadFail);
व्योम Hal_EfuseParseBoardType88E(काष्ठा adapter *pAdapter, u8 *hwinfo,
				bool AutoLoadFail);
व्योम Hal_ReadPowerSavingMode88E(काष्ठा adapter *pAdapter, u8 *hwinfo,
				bool AutoLoadFail);

/*  रेजिस्टर */

व्योम rtl8188e_start_thपढ़ो(काष्ठा adapter *padapter);
व्योम rtl8188e_stop_thपढ़ो(काष्ठा adapter *padapter);

s32 iol_execute(काष्ठा adapter *padapter, u8 control);
व्योम iol_mode_enable(काष्ठा adapter *padapter, u8 enable);
s32 rtl8188e_iol_efuse_patch(काष्ठा adapter *padapter);
व्योम rtw_cancel_all_समयr(काष्ठा adapter *padapter);

#पूर्ण_अगर /* __RTL8188E_HAL_H__ */
