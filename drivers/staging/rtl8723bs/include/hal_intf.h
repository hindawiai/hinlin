<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_INTF_H__
#घोषणा __HAL_INTF_H__


क्रमागत अणु
	RTW_PCIE	= BIT0,
	RTW_USB		= BIT1,
	RTW_SDIO	= BIT2,
	RTW_GSPI	= BIT3,
पूर्ण;

क्रमागत अणु
	HW_VAR_MEDIA_STATUS,
	HW_VAR_MEDIA_STATUS1,
	HW_VAR_SET_OPMODE,
	HW_VAR_MAC_ADDR,
	HW_VAR_BSSID,
	HW_VAR_INIT_RTS_RATE,
	HW_VAR_BASIC_RATE,
	HW_VAR_TXPAUSE,
	HW_VAR_BCN_FUNC,
	HW_VAR_CORRECT_TSF,
	HW_VAR_CHECK_BSSID,
	HW_VAR_MLME_DISCONNECT,
	HW_VAR_MLME_SITESURVEY,
	HW_VAR_MLME_JOIN,
	HW_VAR_ON_RCR_AM,
	HW_VAR_OFF_RCR_AM,
	HW_VAR_BEACON_INTERVAL,
	HW_VAR_SLOT_TIME,
	HW_VAR_RESP_SIFS,
	HW_VAR_ACK_PREAMBLE,
	HW_VAR_SEC_CFG,
	HW_VAR_SEC_DK_CFG,
	HW_VAR_BCN_VALID,
	HW_VAR_RF_TYPE,
	HW_VAR_DM_FLAG,
	HW_VAR_DM_FUNC_OP,
	HW_VAR_DM_FUNC_SET,
	HW_VAR_DM_FUNC_CLR,
	HW_VAR_CAM_EMPTY_ENTRY,
	HW_VAR_CAM_INVALID_ALL,
	HW_VAR_CAM_WRITE,
	HW_VAR_CAM_READ,
	HW_VAR_AC_PARAM_VO,
	HW_VAR_AC_PARAM_VI,
	HW_VAR_AC_PARAM_BE,
	HW_VAR_AC_PARAM_BK,
	HW_VAR_ACM_CTRL,
	HW_VAR_AMPDU_MIN_SPACE,
	HW_VAR_AMPDU_FACTOR,
	HW_VAR_RXDMA_AGG_PG_TH,
	HW_VAR_SET_RPWM,
	HW_VAR_CPWM,
	HW_VAR_H2C_FW_PWRMODE,
	HW_VAR_H2C_PS_TUNE_PARAM,
	HW_VAR_H2C_FW_JOINBSSRPT,
	HW_VAR_FWLPS_RF_ON,
	HW_VAR_H2C_FW_P2P_PS_OFFLOAD,
	HW_VAR_TDLS_WRCR,
	HW_VAR_TDLS_INIT_CH_SEN,
	HW_VAR_TDLS_RS_RCR,
	HW_VAR_TDLS_DONE_CH_SEN,
	HW_VAR_INITIAL_GAIN,
	HW_VAR_TRIGGER_GPIO_0,
	HW_VAR_BT_SET_COEXIST,
	HW_VAR_BT_ISSUE_DELBA,
	HW_VAR_CURRENT_ANTENNA,
	HW_VAR_ANTENNA_DIVERSITY_LINK,
	HW_VAR_ANTENNA_DIVERSITY_SELECT,
	HW_VAR_SWITCH_EPHY_WoWLAN,
	HW_VAR_EFUSE_USAGE,
	HW_VAR_EFUSE_BYTES,
	HW_VAR_EFUSE_BT_USAGE,
	HW_VAR_EFUSE_BT_BYTES,
	HW_VAR_FIFO_CLEARN_UP,
	HW_VAR_CHECK_TXBUF,
	HW_VAR_PCIE_STOP_TX_DMA,
	HW_VAR_APFM_ON_MAC, /* Auto FSM to Turn On, include घड़ी, isolation, घातer control क्रम MAC only */
	/*  The valid upper nav range क्रम the HW updating, अगर the true value is larger than the upper range, the HW won't update it. */
	/*  Unit in microsecond. 0 means disable this function. */
	HW_VAR_SYS_CLKR,
	HW_VAR_NAV_UPPER,
	HW_VAR_C2H_HANDLE,
	HW_VAR_RPT_TIMER_SETTING,
	HW_VAR_TX_RPT_MAX_MACID,
	HW_VAR_H2C_MEDIA_STATUS_RPT,
	HW_VAR_CHK_HI_QUEUE_EMPTY,
	HW_VAR_DL_BCN_SEL,
	HW_VAR_AMPDU_MAX_TIME,
	HW_VAR_WIRELESS_MODE,
	HW_VAR_USB_MODE,
	HW_VAR_PORT_SWITCH,
	HW_VAR_DO_IQK,
	HW_VAR_DM_IN_LPS,
	HW_VAR_SET_REQ_FW_PS,
	HW_VAR_FW_PS_STATE,
	HW_VAR_SOUNDING_ENTER,
	HW_VAR_SOUNDING_LEAVE,
	HW_VAR_SOUNDING_RATE,
	HW_VAR_SOUNDING_STATUS,
	HW_VAR_SOUNDING_FW_NDPA,
	HW_VAR_SOUNDING_CLK,
	HW_VAR_DL_RSVD_PAGE,
	HW_VAR_MACID_SLEEP,
	HW_VAR_MACID_WAKEUP,
पूर्ण;

क्रमागत hal_def_variable अणु
	HAL_DEF_UNDERCORATEDSMOOTHEDPWDB,
	HAL_DEF_IS_SUPPORT_ANT_DIV,
	HAL_DEF_CURRENT_ANTENNA,
	HAL_DEF_DRVINFO_SZ,
	HAL_DEF_MAX_RECVBUF_SZ,
	HAL_DEF_RX_PACKET_OFFSET,
	HAL_DEF_DBG_DUMP_RXPKT,/* क्रम dbg */
	HAL_DEF_DBG_DM_FUNC,/* क्रम dbg */
	HAL_DEF_RA_DECISION_RATE,
	HAL_DEF_RA_SGI,
	HAL_DEF_PT_PWR_STATUS,
	HAL_DEF_TX_LDPC,				/*  LDPC support */
	HAL_DEF_RX_LDPC,				/*  LDPC support */
	HAL_DEF_TX_STBC,				/*  TX STBC support */
	HAL_DEF_RX_STBC,				/*  RX STBC support */
	HAL_DEF_EXPLICIT_BEAMFORMER,/*  Explicit  Compressed Steering Capable */
	HAL_DEF_EXPLICIT_BEAMFORMEE,/*  Explicit Compressed Beamक्रमming Feedback Capable */
	HW_VAR_MAX_RX_AMPDU_FACTOR,
	HW_DEF_RA_INFO_DUMP,
	HAL_DEF_DBG_DUMP_TXPKT,
	HW_DEF_FA_CNT_DUMP,
	HW_DEF_ODM_DBG_FLAG,
	HW_DEF_ODM_DBG_LEVEL,
	HAL_DEF_TX_PAGE_SIZE,
	HAL_DEF_TX_PAGE_BOUNDARY,
	HAL_DEF_TX_PAGE_BOUNDARY_WOWLAN,
	HAL_DEF_ANT_DETECT,/* to करो क्रम 8723a */
	HAL_DEF_PCI_SUUPORT_L1_BACKDOOR, /*  Determine अगर the L1 Backकरोor setting is turned on. */
	HAL_DEF_PCI_AMD_L1_SUPPORT,
	HAL_DEF_PCI_ASPM_OSC, /*  Support क्रम ASPM OSC, added by Roger, 2013.03.27. */
	HAL_DEF_MACID_SLEEP, /*  Support क्रम MACID sleep */
	HAL_DEF_DBG_RX_INFO_DUMP,
पूर्ण;

क्रमागत hal_odm_variable अणु
	HAL_ODM_STA_INFO,
	HAL_ODM_P2P_STATE,
	HAL_ODM_WIFI_DISPLAY_STATE,
	HAL_ODM_NOISE_MONITOR,
पूर्ण;

क्रमागत hal_पूर्णांकf_ps_func अणु
	HAL_USB_SELECT_SUSPEND,
	HAL_MAX_ID,
पूर्ण;

प्रकार s32 (*c2h_id_filter)(u8 *c2h_evt);

काष्ठा hal_ops अणु
	u32 (*hal_घातer_on)(काष्ठा adapter *padapter);
	व्योम (*hal_घातer_off)(काष्ठा adapter *padapter);
	u32 (*hal_init)(काष्ठा adapter *padapter);
	u32 (*hal_deinit)(काष्ठा adapter *padapter);

	व्योम (*मुक्त_hal_data)(काष्ठा adapter *padapter);

	u32 (*inirp_init)(काष्ठा adapter *padapter);
	u32 (*inirp_deinit)(काष्ठा adapter *padapter);
	व्योम (*irp_reset)(काष्ठा adapter *padapter);

	s32	(*init_xmit_priv)(काष्ठा adapter *padapter);
	व्योम (*मुक्त_xmit_priv)(काष्ठा adapter *padapter);

	s32	(*init_recv_priv)(काष्ठा adapter *padapter);
	व्योम (*मुक्त_recv_priv)(काष्ठा adapter *padapter);

	व्योम (*dm_init)(काष्ठा adapter *padapter);
	व्योम (*dm_deinit)(काष्ठा adapter *padapter);
	व्योम (*पढ़ो_chip_version)(काष्ठा adapter *padapter);

	व्योम (*init_शेष_value)(काष्ठा adapter *padapter);

	व्योम (*पूर्णांकf_chip_configure)(काष्ठा adapter *padapter);

	व्योम (*पढ़ो_adapter_info)(काष्ठा adapter *padapter);

	व्योम (*enable_पूर्णांकerrupt)(काष्ठा adapter *padapter);
	व्योम (*disable_पूर्णांकerrupt)(काष्ठा adapter *padapter);
	u8 (*check_ips_status)(काष्ठा adapter *padapter);
	s32		(*पूर्णांकerrupt_handler)(काष्ठा adapter *padapter);
	व्योम    (*clear_पूर्णांकerrupt)(काष्ठा adapter *padapter);
	व्योम (*set_bwmode_handler)(काष्ठा adapter *padapter, क्रमागत channel_width Bandwidth, u8 Offset);
	व्योम (*set_channel_handler)(काष्ठा adapter *padapter, u8 channel);
	व्योम (*set_chnl_bw_handler)(काष्ठा adapter *padapter, u8 channel, क्रमागत channel_width Bandwidth, u8 Offset40, u8 Offset80);

	व्योम (*set_tx_घातer_level_handler)(काष्ठा adapter *padapter, u8 channel);
	व्योम (*get_tx_घातer_level_handler)(काष्ठा adapter *padapter, s32 *घातerlevel);

	व्योम (*hal_dm_watchकरोg)(काष्ठा adapter *padapter);
	व्योम (*hal_dm_watchकरोg_in_lps)(काष्ठा adapter *padapter);


	व्योम (*SetHwRegHandler)(काष्ठा adapter *padapter, u8 variable, u8 *val);
	व्योम (*GetHwRegHandler)(काष्ठा adapter *padapter, u8 variable, u8 *val);

	व्योम (*SetHwRegHandlerWithBuf)(काष्ठा adapter *padapter, u8 variable, u8 *pbuf, पूर्णांक len);

	u8 (*GetHalDefVarHandler)(काष्ठा adapter *padapter, क्रमागत hal_def_variable eVariable, व्योम *pValue);
	u8 (*SetHalDefVarHandler)(काष्ठा adapter *padapter, क्रमागत hal_def_variable eVariable, व्योम *pValue);

	व्योम (*GetHalODMVarHandler)(काष्ठा adapter *padapter, क्रमागत hal_odm_variable eVariable, व्योम *pValue1, व्योम *pValue2);
	व्योम (*SetHalODMVarHandler)(काष्ठा adapter *padapter, क्रमागत hal_odm_variable eVariable, व्योम *pValue1, bool bSet);

	व्योम (*UpdateRAMaskHandler)(काष्ठा adapter *padapter, u32 mac_id, u8 rssi_level);
	व्योम (*SetBeaconRelatedRegistersHandler)(काष्ठा adapter *padapter);

	व्योम (*Add_RateATid)(काष्ठा adapter *padapter, u32 biपंचांगap, u8 *arg, u8 rssi_level);

	व्योम (*run_thपढ़ो)(काष्ठा adapter *padapter);
	व्योम (*cancel_thपढ़ो)(काष्ठा adapter *padapter);

	u8 (*पूर्णांकerface_ps_func)(काष्ठा adapter *padapter, क्रमागत hal_पूर्णांकf_ps_func efunc_id, u8 *val);

	s32	(*hal_xmit)(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
	/*
	 * mgnt_xmit should be implemented to run in पूर्णांकerrupt context
	 */
	s32 (*mgnt_xmit)(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe);
	s32	(*hal_xmitframe_enqueue)(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);

	u32 (*पढ़ो_bbreg)(काष्ठा adapter *padapter, u32 RegAddr, u32 BitMask);
	व्योम (*ग_लिखो_bbreg)(काष्ठा adapter *padapter, u32 RegAddr, u32 BitMask, u32 Data);
	u32 (*पढ़ो_rfreg)(काष्ठा adapter *padapter, u8 eRFPath, u32 RegAddr, u32 BitMask);
	व्योम (*ग_लिखो_rfreg)(काष्ठा adapter *padapter, u8 eRFPath, u32 RegAddr, u32 BitMask, u32 Data);

	व्योम (*EfusePowerSwitch)(काष्ठा adapter *padapter, u8 bWrite, u8 PwrState);
	व्योम (*BTEfusePowerSwitch)(काष्ठा adapter *padapter, u8 bWrite, u8 PwrState);
	व्योम (*ReadEFuse)(काष्ठा adapter *padapter, u8 efuseType, u16 _offset, u16 _size_byte, u8 *pbuf, bool bPseuकरोTest);
	व्योम (*EFUSEGetEfuseDefinition)(काष्ठा adapter *padapter, u8 efuseType, u8 type, व्योम *pOut, bool bPseuकरोTest);
	u16 (*EfuseGetCurrentSize)(काष्ठा adapter *padapter, u8 efuseType, bool bPseuकरोTest);
	पूर्णांक	(*Efuse_PgPacketRead)(काष्ठा adapter *padapter, u8 offset, u8 *data, bool bPseuकरोTest);
	पूर्णांक	(*Efuse_PgPacketWrite)(काष्ठा adapter *padapter, u8 offset, u8 word_en, u8 *data, bool bPseuकरोTest);
	u8 (*Efuse_WordEnableDataWrite)(काष्ठा adapter *padapter, u16 efuse_addr, u8 word_en, u8 *data, bool bPseuकरोTest);
	bool	(*Efuse_PgPacketWrite_BT)(काष्ठा adapter *padapter, u8 offset, u8 word_en, u8 *data, bool bPseuकरोTest);

	s32 (*xmit_thपढ़ो_handler)(काष्ठा adapter *padapter);
	व्योम (*hal_notch_filter)(काष्ठा adapter *adapter, bool enable);
	व्योम (*hal_reset_security_engine)(काष्ठा adapter *adapter);
	s32 (*c2h_handler)(काष्ठा adapter *padapter, u8 *c2h_evt);
	c2h_id_filter c2h_id_filter_ccx;

	s32 (*fill_h2c_cmd)(काष्ठा adapter *, u8 ElementID, u32 CmdLen, u8 *pCmdBuffer);
पूर्ण;

#घोषणा RF_CHANGE_BY_INIT	0
#घोषणा RF_CHANGE_BY_IPS	BIT28
#घोषणा RF_CHANGE_BY_PS		BIT29
#घोषणा RF_CHANGE_BY_HW		BIT30
#घोषणा RF_CHANGE_BY_SW		BIT31

#घोषणा GET_EEPROM_EFUSE_PRIV(adapter) (&adapter->eeprompriv)
#घोषणा is_boot_from_eeprom(adapter) (adapter->eeprompriv.EepromOrEfuse)

#घोषणा Rx_Pairwisekey			0x01
#घोषणा Rx_GTK					0x02
#घोषणा Rx_DisAssoc				0x04
#घोषणा Rx_DeAuth				0x08
#घोषणा Rx_ARPReq				0x09
#घोषणा FWDecisionDisconnect	0x10
#घोषणा Rx_MagicPkt				0x21
#घोषणा Rx_UnicastPkt			0x22
#घोषणा Rx_PatternPkt			0x23
#घोषणा	RX_PNOWakeUp			0x55
#घोषणा	AP_WakeUp			0x66

व्योम rtw_hal_def_value_init(काष्ठा adapter *padapter);

व्योम rtw_hal_मुक्त_data(काष्ठा adapter *padapter);

व्योम rtw_hal_dm_init(काष्ठा adapter *padapter);
व्योम rtw_hal_dm_deinit(काष्ठा adapter *padapter);

uपूर्णांक rtw_hal_init(काष्ठा adapter *padapter);
uपूर्णांक rtw_hal_deinit(काष्ठा adapter *padapter);
व्योम rtw_hal_stop(काष्ठा adapter *padapter);
व्योम rtw_hal_set_hwreg(काष्ठा adapter *padapter, u8 variable, u8 *val);
व्योम rtw_hal_get_hwreg(काष्ठा adapter *padapter, u8 variable, u8 *val);

व्योम rtw_hal_set_hwreg_with_buf(काष्ठा adapter *padapter, u8 variable, u8 *pbuf, पूर्णांक len);

व्योम rtw_hal_chip_configure(काष्ठा adapter *padapter);
व्योम rtw_hal_पढ़ो_chip_info(काष्ठा adapter *padapter);
व्योम rtw_hal_पढ़ो_chip_version(काष्ठा adapter *padapter);

u8 rtw_hal_set_def_var(काष्ठा adapter *padapter, क्रमागत hal_def_variable eVariable, व्योम *pValue);
u8 rtw_hal_get_def_var(काष्ठा adapter *padapter, क्रमागत hal_def_variable eVariable, व्योम *pValue);

व्योम rtw_hal_set_odm_var(काष्ठा adapter *padapter, क्रमागत hal_odm_variable eVariable, व्योम *pValue1, bool bSet);
व्योम rtw_hal_get_odm_var(काष्ठा adapter *padapter, क्रमागत hal_odm_variable eVariable, व्योम *pValue1, व्योम *pValue2);

व्योम rtw_hal_enable_पूर्णांकerrupt(काष्ठा adapter *padapter);
व्योम rtw_hal_disable_पूर्णांकerrupt(काष्ठा adapter *padapter);

u8 rtw_hal_check_ips_status(काष्ठा adapter *padapter);

s32	rtw_hal_xmitframe_enqueue(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
s32	rtw_hal_xmit(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
s32	rtw_hal_mgnt_xmit(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe);

s32	rtw_hal_init_xmit_priv(काष्ठा adapter *padapter);
व्योम rtw_hal_मुक्त_xmit_priv(काष्ठा adapter *padapter);

s32	rtw_hal_init_recv_priv(काष्ठा adapter *padapter);
व्योम rtw_hal_मुक्त_recv_priv(काष्ठा adapter *padapter);

व्योम rtw_hal_update_ra_mask(काष्ठा sta_info *psta, u8 rssi_level);
व्योम rtw_hal_add_ra_tid(काष्ठा adapter *padapter, u32 biपंचांगap, u8 *arg, u8 rssi_level);

व्योम rtw_hal_start_thपढ़ो(काष्ठा adapter *padapter);
व्योम rtw_hal_stop_thपढ़ो(काष्ठा adapter *padapter);

व्योम beacon_timing_control(काष्ठा adapter *padapter);

u32 rtw_hal_पढ़ो_bbreg(काष्ठा adapter *padapter, u32 RegAddr, u32 BitMask);
व्योम rtw_hal_ग_लिखो_bbreg(काष्ठा adapter *padapter, u32 RegAddr, u32 BitMask, u32 Data);
u32 rtw_hal_पढ़ो_rfreg(काष्ठा adapter *padapter, u32 eRFPath, u32 RegAddr, u32 BitMask);
व्योम rtw_hal_ग_लिखो_rfreg(काष्ठा adapter *padapter, u32 eRFPath, u32 RegAddr, u32 BitMask, u32 Data);

#घोषणा PHY_QueryBBReg(Adapter, RegAddr, BitMask) rtw_hal_पढ़ो_bbreg((Adapter), (RegAddr), (BitMask))
#घोषणा PHY_SetBBReg(Adapter, RegAddr, BitMask, Data) rtw_hal_ग_लिखो_bbreg((Adapter), (RegAddr), (BitMask), (Data))
#घोषणा PHY_QueryRFReg(Adapter, eRFPath, RegAddr, BitMask) rtw_hal_पढ़ो_rfreg((Adapter), (eRFPath), (RegAddr), (BitMask))
#घोषणा PHY_SetRFReg(Adapter, eRFPath, RegAddr, BitMask, Data) rtw_hal_ग_लिखो_rfreg((Adapter), (eRFPath), (RegAddr), (BitMask), (Data))

#घोषणा PHY_SetMacReg	PHY_SetBBReg
#घोषणा PHY_QueryMacReg PHY_QueryBBReg

व्योम rtw_hal_set_chan(काष्ठा adapter *padapter, u8 channel);
व्योम rtw_hal_set_chnl_bw(काष्ठा adapter *padapter, u8 channel, क्रमागत channel_width Bandwidth, u8 Offset40, u8 Offset80);
व्योम rtw_hal_dm_watchकरोg(काष्ठा adapter *padapter);
व्योम rtw_hal_dm_watchकरोg_in_lps(काष्ठा adapter *padapter);

s32 rtw_hal_xmit_thपढ़ो_handler(काष्ठा adapter *padapter);

व्योम rtw_hal_notch_filter(काष्ठा adapter *adapter, bool enable);
व्योम rtw_hal_reset_security_engine(काष्ठा adapter *adapter);

bool rtw_hal_c2h_valid(काष्ठा adapter *adapter, u8 *buf);
s32 rtw_hal_c2h_handler(काष्ठा adapter *adapter, u8 *c2h_evt);
c2h_id_filter rtw_hal_c2h_id_filter_ccx(काष्ठा adapter *adapter);

s32 rtw_hal_is_disable_sw_channel_plan(काष्ठा adapter *padapter);

s32 rtw_hal_macid_sleep(काष्ठा adapter *padapter, u32 macid);
s32 rtw_hal_macid_wakeup(काष्ठा adapter *padapter, u32 macid);

s32 rtw_hal_fill_h2c_cmd(काष्ठा adapter *, u8 ElementID, u32 CmdLen, u8 *pCmdBuffer);

#पूर्ण_अगर /* __HAL_INTF_H__ */
