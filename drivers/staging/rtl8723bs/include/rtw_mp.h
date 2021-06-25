<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_MP_H_
#घोषणा _RTW_MP_H_

#घोषणा MAX_MP_XMITBUF_SZ	2048
#घोषणा NR_MP_XMITFRAME		8

काष्ठा mp_xmit_frame अणु
	काष्ठा list_head	list;

	काष्ठा pkt_attrib attrib;

	काष्ठा sk_buff *pkt;

	पूर्णांक frame_tag;

	काष्ठा adapter *padapter;

	uपूर्णांक mem[(MAX_MP_XMITBUF_SZ >> 2)];
पूर्ण;

काष्ठा mp_wiparam अणु
	u32 bcompleted;
	u32 act_type;
	u32 io_offset;
	u32 io_value;
पूर्ण;

काष्ठा mp_tx अणु
	u8 stop;
	u32 count, sended;
	u8 payload;
	काष्ठा pkt_attrib attrib;
	/* काष्ठा tx_desc desc; */
	/* u8 resvdtx[7]; */
	u8 desc[TXDESC_SIZE];
	u8 *pallocated_buf;
	u8 *buf;
	u32 buf_size, ग_लिखो_size;
	व्योम *PktTxThपढ़ो;
पूर्ण;

#घोषणा MP_MAX_LINES		1000
#घोषणा MP_MAX_LINES_BYTES	256

प्रकार व्योम (*MPT_WORK_ITEM_HANDLER)(व्योम *Adapter);
काष्ठा mpt_context अणु
	/*  Indicate अगर we have started Mass Production Test. */
	bool			bMassProdTest;

	/*  Indicate अगर the driver is unloading or unloaded. */
	bool			bMptDrvUnload;

	काष्ठा समयr_list			MPh2c_समयout_समयr;
/*  Event used to sync H2c क्रम BT control */

	bool		MptH2cRspEvent;
	bool		MptBtC2hEvent;
	bool		bMPh2c_समयout;

	/* 8190 PCI करोes not support NDIS_WORK_ITEM. */
	/*  Work Item क्रम Mass Production Test. */
	/* NDIS_WORK_ITEM	MptWorkItem; */
/* 	RT_WORK_ITEM		MptWorkItem; */
	/*  Event used to sync the हाल unloading driver and MptWorkItem is still in progress. */
/* 	NDIS_EVENT		MptWorkItemEvent; */
	/*  To protect the following variables. */
/* 	NDIS_SPIN_LOCK		MptWorkItemSpinLock; */
	/*  Indicate a MptWorkItem is scheduled and not yet finished. */
	bool			bMptWorkItemInProgress;
	/*  An instance which implements function and context of MptWorkItem. */
	MPT_WORK_ITEM_HANDLER	CurrMptAct;

	/*  1 =Start, 0 =Stop from UI. */
	u32 		MptTestStart;
	/*  _TEST_MODE, defined in MPT_Req2.h */
	u32 		MptTestItem;
	/*  Variable needed in each implementation of CurrMptAct. */
	u32 		MptActType;	/*  Type of action perक्रमmed in CurrMptAct. */
	/*  The Offset of IO operation is depend of MptActType. */
	u32 		MptIoOffset;
	/*  The Value of IO operation is depend of MptActType. */
	u32 		MptIoValue;
	/*  The RfPath of IO operation is depend of MptActType. */
	u32 		MptRfPath;

	क्रमागत wireless_mode		MptWirelessModeToSw;	/*  Wireless mode to चयन. */
	u8 	MptChannelToSw;		/*  Channel to चयन. */
	u8 	MptInitGainToSet;	/*  Initial gain to set. */
	u32 		MptBandWidth;		/*  bandwidth to चयन. */
	u32 		MptRateIndex;		/*  rate index. */
	/*  Register value kept क्रम Single Carrier Tx test. */
	u8 	btMpCckTxPower;
	/*  Register value kept क्रम Single Carrier Tx test. */
	u8 	btMpOfdmTxPower;
	/*  For MP Tx Power index */
	u8 	TxPwrLevel[2];	/*  rf-A, rf-B */
	u32 		RegTxPwrLimit;
	/*  Content of RCR Register क्रम Mass Production Test. */
	u32 		MptRCR;
	/*  true अगर we only receive packets with specअगरic pattern. */
	bool			bMptFilterPattern;
	/*  Rx OK count, statistics used in Mass Production Test. */
	u32 		MptRxOkCnt;
	/*  Rx CRC32 error count, statistics used in Mass Production Test. */
	u32 		MptRxCrcErrCnt;

	bool			bCckContTx;	/*  true अगर we are in CCK Continuous Tx test. */
	bool			bOfdmContTx;	/*  true अगर we are in OFDM Continuous Tx test. */
	bool			bStartContTx;	/*  true अगर we have start Continuous Tx test. */
	/*  true अगर we are in Single Carrier Tx test. */
	bool			bSingleCarrier;
	/*  true अगर we are in Carrier Suppression Tx Test. */
	bool			bCarrierSuppression;
	/* true अगर we are in Single Tone Tx test. */
	bool			bSingleTone;

	/*  ACK counter asked by K.Y.. */
	bool			bMptEnableAckCounter;
	u32 		MptAckCounter;

	/*  SD3 Willis For 8192S to save 1T/2T RF table क्रम ACUT	Only fro ACUT delete later ~~~! */
	/* s8		BufOfLines[2][MAX_LINES_HWCONFIG_TXT][MAX_BYTES_LINE_HWCONFIG_TXT]; */
	/* s8			BufOfLines[2][MP_MAX_LINES][MP_MAX_LINES_BYTES]; */
	/* s32			RfReadLine[2]; */

	u8 APK_bound[2];	/* क्रम APK	path A/path B */
	bool		bMptIndexEven;

	u8 backup0xc50;
	u8 backup0xc58;
	u8 backup0xc30;
	u8 backup0x52_RF_A;
	u8 backup0x52_RF_B;

	u32 		backup0x58_RF_A;
	u32 		backup0x58_RF_B;

	u8 	h2cReqNum;
	u8 	c2hBuf[32];

    u8          btInBuf[100];
	u32 		mptOutLen;
    u8          mptOutBuf[100];

पूर्ण;
/* endअगर */

/* E-Fuse */
#घोषणा EFUSE_MAP_SIZE		512

#घोषणा EFUSE_MAX_SIZE		512
/* end of E-Fuse */

/* define RTPRIV_IOCTL_MP					(SIOCIWFIRSTPRIV + 0x17) */
क्रमागत अणु
	WRITE_REG = 1,
	READ_REG,
	WRITE_RF,
	READ_RF,
	MP_START,
	MP_STOP,
	MP_RATE,
	MP_CHANNEL,
	MP_BANDWIDTH,
	MP_TXPOWER,
	MP_ANT_TX,
	MP_ANT_RX,
	MP_CTX,
	MP_QUERY,
	MP_ARX,
	MP_PSD,
	MP_PWRTRK,
	MP_THER,
	MP_IOCTL,
	EFUSE_GET,
	EFUSE_SET,
	MP_RESET_STATS,
	MP_DUMP,
	MP_PHYPARA,
	MP_SetRFPathSwh,
	MP_QueryDrvStats,
	MP_SetBT,
	CTA_TEST,
	MP_DISABLE_BT_COEXIST,
	MP_PwrCtlDM,
	MP_शून्य,
	MP_GET_TXPOWER_INX,
पूर्ण;

काष्ठा mp_priv अणु
	काष्ठा adapter *papdater;

	/* Testing Flag */
	u32 mode;/* 0 क्रम normal type packet, 1 क्रम loopback packet (16bytes TXCMD) */

	u32 prev_fw_state;

	/* OID cmd handler */
	काष्ठा mp_wiparam workparam;
/* 	u8 act_in_progress; */

	/* Tx Section */
	u8 TID;
	u32 tx_pktcount;
	u32 pktInterval;
	काष्ठा mp_tx tx;

	/* Rx Section */
	u32 rx_bssidpktcount;
	u32 rx_pktcount;
	u32 rx_pktcount_filter_out;
	u32 rx_crcerrpktcount;
	u32 rx_pktloss;
	bool  rx_bindicatePkt;
	काष्ठा recv_stat rxstat;

	/* RF/BB relative */
	u8 channel;
	u8 bandwidth;
	u8 prime_channel_offset;
	u8 txघातeridx;
	u8 txघातeridx_b;
	u8 rateidx;
	u32 preamble;
/* 	u8 modem; */
	u32 CrystalCap;
/* 	u32 curr_crystalcap; */

	u16 antenna_tx;
	u16 antenna_rx;
/* 	u8 curr_rfpath; */

	u8 check_mp_pkt;

	u8 bSetTxPower;
/* 	uपूर्णांक ForcedDataRate; */
	u8 mp_dm;
	u8 mac_filter[ETH_ALEN];
	u8 bmac_filter;

	काष्ठा wlan_network mp_network;
	NDIS_802_11_MAC_ADDRESS network_macaddr;

	u8 *pallocated_mp_xmitframe_buf;
	u8 *pmp_xmtframe_buf;
	काष्ठा __queue मुक्त_mp_xmitqueue;
	u32 मुक्त_mp_xmitframe_cnt;
	bool bSetRxBssid;
	bool bTxBufCkFail;

	काष्ठा mpt_context MptCtx;

	u8 *TXraकरोmBuffer;
पूर्ण;

#घोषणा LOWER	true
#घोषणा RAISE	false

/* Hardware Registers */
#घोषणा BB_REG_BASE_ADDR		0x800

#घोषणा MAX_RF_PATH_NUMS	RF_PATH_MAX

बाह्य u8 mpdatarate[NumRates];

#घोषणा MAX_TX_PWR_INDEX_N_MODE 64	/*  0x3F */

#घोषणा RX_PKT_BROADCAST	1
#घोषणा RX_PKT_DEST_ADDR	2
#घोषणा RX_PKT_PHY_MATCH	3

#घोषणा Mac_OFDM_OK			0x00000000
#घोषणा Mac_OFDM_Fail			0x10000000
#घोषणा Mac_OFDM_FasleAlarm	0x20000000
#घोषणा Mac_CCK_OK				0x30000000
#घोषणा Mac_CCK_Fail			0x40000000
#घोषणा Mac_CCK_FasleAlarm		0x50000000
#घोषणा Mac_HT_OK				0x60000000
#घोषणा Mac_HT_Fail			0x70000000
#घोषणा Mac_HT_FasleAlarm		0x90000000
#घोषणा Mac_DropPacket			0xA0000000

#घोषणा		REG_RF_BB_GAIN_OFFSET	0x7f
#घोषणा		RF_GAIN_OFFSET_MASK	0xfffff

/*  */
/* काष्ठा mp_xmit_frame *alloc_mp_xmitframe(काष्ठा mp_priv *pmp_priv); */
/* पूर्णांक मुक्त_mp_xmitframe(काष्ठा xmit_priv *pxmitpriv, काष्ठा mp_xmit_frame *pmp_xmitframe); */

s32 init_mp_priv(काष्ठा adapter *padapter);
व्योम मुक्त_mp_priv(काष्ठा mp_priv *pmp_priv);
s32 MPT_InitializeAdapter(काष्ठा adapter *padapter, u8 Channel);
व्योम MPT_DeInitAdapter(काष्ठा adapter *padapter);
s32 mp_start_test(काष्ठा adapter *padapter);
व्योम mp_stop_test(काष्ठा adapter *padapter);

u32 _पढ़ो_rfreg(काष्ठा adapter *padapter, u8 rfpath, u32 addr, u32 biपंचांगask);
व्योम _ग_लिखो_rfreg(काष्ठा adapter *padapter, u8 rfpath, u32 addr, u32 biपंचांगask, u32 val);

u32 पढ़ो_macreg(काष्ठा adapter *padapter, u32 addr, u32 sz);
व्योम ग_लिखो_macreg(काष्ठा adapter *padapter, u32 addr, u32 val, u32 sz);
u32 पढ़ो_bbreg(काष्ठा adapter *padapter, u32 addr, u32 biपंचांगask);
व्योम ग_लिखो_bbreg(काष्ठा adapter *padapter, u32 addr, u32 biपंचांगask, u32 val);
u32 पढ़ो_rfreg(काष्ठा adapter *padapter, u8 rfpath, u32 addr);
व्योम ग_लिखो_rfreg(काष्ठा adapter *padapter, u8 rfpath, u32 addr, u32 val);

व्योम SetChannel(काष्ठा adapter *padapter);
व्योम SetBandwidth(काष्ठा adapter *padapter);
पूर्णांक SetTxPower(काष्ठा adapter *padapter);
व्योम SetAntennaPathPower(काष्ठा adapter *padapter);
व्योम SetDataRate(काष्ठा adapter *padapter);

व्योम SetAntenna(काष्ठा adapter *padapter);

s32 SetThermalMeter(काष्ठा adapter *padapter, u8 target_ther);
व्योम GetThermalMeter(काष्ठा adapter *padapter, u8 *value);

व्योम SetContinuousTx(काष्ठा adapter *padapter, u8 bStart);
व्योम SetSingleCarrierTx(काष्ठा adapter *padapter, u8 bStart);
व्योम SetSingleToneTx(काष्ठा adapter *padapter, u8 bStart);
व्योम SetCarrierSuppressionTx(काष्ठा adapter *padapter, u8 bStart);
व्योम PhySetTxPowerLevel(काष्ठा adapter *padapter);

व्योम fill_txdesc_क्रम_mp(काष्ठा adapter *padapter, u8 *ptxdesc);
व्योम SetPacketTx(काष्ठा adapter *padapter);
व्योम SetPacketRx(काष्ठा adapter *padapter, u8 bStartRx);

व्योम ResetPhyRxPktCount(काष्ठा adapter *padapter);
u32 GetPhyRxPktReceived(काष्ठा adapter *padapter);
u32 GetPhyRxPktCRC32Error(काष्ठा adapter *padapter);

s32	SetPowerTracking(काष्ठा adapter *padapter, u8 enable);
व्योम GetPowerTracking(काष्ठा adapter *padapter, u8 *enable);

u32 mp_query_psd(काष्ठा adapter *padapter, u8 *data);

व्योम Hal_SetAntenna(काष्ठा adapter *padapter);
व्योम Hal_SetBandwidth(काष्ठा adapter *padapter);

व्योम Hal_SetTxPower(काष्ठा adapter *padapter);
व्योम Hal_SetCarrierSuppressionTx(काष्ठा adapter *padapter, u8 bStart);
व्योम Hal_SetSingleToneTx(काष्ठा adapter *padapter, u8 bStart);
व्योम Hal_SetSingleCarrierTx(काष्ठा adapter *padapter, u8 bStart);
व्योम Hal_SetContinuousTx(काष्ठा adapter *padapter, u8 bStart);
व्योम Hal_SetBandwidth(काष्ठा adapter *padapter);

व्योम Hal_SetDataRate(काष्ठा adapter *padapter);
व्योम Hal_SetChannel(काष्ठा adapter *padapter);
व्योम Hal_SetAntennaPathPower(काष्ठा adapter *padapter);
s32 Hal_SetThermalMeter(काष्ठा adapter *padapter, u8 target_ther);
s32 Hal_SetPowerTracking(काष्ठा adapter *padapter, u8 enable);
व्योम Hal_GetPowerTracking(काष्ठा adapter *padapter, u8 *enable);
व्योम Hal_GetThermalMeter(काष्ठा adapter *padapter, u8 *value);
व्योम Hal_mpt_SwitchRfSetting(काष्ठा adapter *padapter);
व्योम Hal_MPT_CCKTxPowerAdjust(काष्ठा adapter *Adapter, bool bInCH14);
व्योम Hal_MPT_CCKTxPowerAdjustbyIndex(काष्ठा adapter *padapter, bool beven);
व्योम Hal_SetCCKTxPower(काष्ठा adapter *padapter, u8 *TxPower);
व्योम Hal_SetOFDMTxPower(काष्ठा adapter *padapter, u8 *TxPower);
व्योम Hal_TriggerRFThermalMeter(काष्ठा adapter *padapter);
u8 Hal_ReadRFThermalMeter(काष्ठा adapter *padapter);
व्योम Hal_SetCCKContinuousTx(काष्ठा adapter *padapter, u8 bStart);
व्योम Hal_SetOFDMContinuousTx(काष्ठा adapter *padapter, u8 bStart);
व्योम Hal_ProSetCrystalCap(काष्ठा adapter *padapter, u32 CrystalCapVal);
व्योम MP_PHY_SetRFPathSwitch(काष्ठा adapter *padapter, bool bMain);
u32 mpt_ProQueryCalTxPower(काष्ठा adapter *padapter, u8 RfPath);
व्योम MPT_PwrCtlDM(काष्ठा adapter *padapter, u32 bstart);
u8 MptToMgntRate(u32 MptRateIdx);

#पूर्ण_अगर /* _RTW_MP_H_ */
