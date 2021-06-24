<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_INTF_H__
#घोषणा __HAL_INTF_H__

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <hal8188e_phy_cfg.h>

क्रमागत RTL871X_HCI_TYPE अणु
	RTW_PCIE	= BIT(0),
	RTW_USB		= BIT(1),
	RTW_SDIO	= BIT(2),
	RTW_GSPI	= BIT(3),
पूर्ण;

क्रमागत _CHIP_TYPE अणु
	शून्य_CHIP_TYPE,
	RTL8712_8188S_8191S_8192S,
	RTL8188C_8192C,
	RTL8192D,
	RTL8723A,
	RTL8188E,
	MAX_CHIP_TYPE
पूर्ण;

क्रमागत hw_variables अणु
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
	HW_VAR_BEACON_INTERVAL,
	HW_VAR_SLOT_TIME,
	HW_VAR_RESP_SIFS,
	HW_VAR_ACK_PREAMBLE,
	HW_VAR_SEC_CFG,
	HW_VAR_BCN_VALID,
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
	HW_VAR_H2C_FW_PWRMODE,
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
	HW_VAR_APFM_ON_MAC, /* Auto FSM to Turn On, include घड़ी, isolation,
			     * घातer control क्रम MAC only
			     */
	/*  The valid upper nav range क्रम the HW updating, अगर the true value is
	 *  larger than the upper range, the HW won't update it.
	 */
	/*  Unit in microsecond. 0 means disable this function. */
	HW_VAR_NAV_UPPER,
	HW_VAR_RPT_TIMER_SETTING,
	HW_VAR_TX_RPT_MAX_MACID,
	HW_VAR_H2C_MEDIA_STATUS_RPT,
	HW_VAR_CHK_HI_QUEUE_EMPTY,
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
	HW_VAR_MAX_RX_AMPDU_FACTOR,
	HW_DEF_RA_INFO_DUMP,
	HAL_DEF_DBG_DUMP_TXPKT,
	HW_DEF_FA_CNT_DUMP,
	HW_DEF_ODM_DBG_FLAG,
पूर्ण;

क्रमागत hal_odm_variable अणु
	HAL_ODM_STA_INFO,
	HAL_ODM_P2P_STATE,
	HAL_ODM_WIFI_DISPLAY_STATE,
पूर्ण;

क्रमागत hal_पूर्णांकf_ps_func अणु
	HAL_USB_SELECT_SUSPEND,
	HAL_MAX_ID,
पूर्ण;

क्रमागत rt_eeprom_type अणु
	EEPROM_93C46,
	EEPROM_93C56,
	EEPROM_BOOT_EFUSE,
पूर्ण;

#घोषणा RF_CHANGE_BY_INIT	0
#घोषणा RF_CHANGE_BY_IPS	BIT(28)
#घोषणा RF_CHANGE_BY_PS		BIT(29)
#घोषणा RF_CHANGE_BY_HW		BIT(30)
#घोषणा RF_CHANGE_BY_SW		BIT(31)

क्रमागत hardware_type अणु
	HARDWARE_TYPE_RTL8188EU,
	HARDWARE_TYPE_MAX,
पूर्ण;

#घोषणा GET_EEPROM_EFUSE_PRIV(adapter) (&adapter->eeprompriv)

#घोषणा is_boot_from_eeprom(adapter) (adapter->eeprompriv.EepromOrEfuse)

व्योम UpdateHalRAMask8188EUsb(काष्ठा adapter *adapt, u32 mac_id, u8 rssi_level);
u32 rtl8188eu_hal_deinit(काष्ठा adapter *Adapter);
u32 rtl8188eu_hal_init(काष्ठा adapter *Adapter);
व्योम rtw_hal_def_value_init(काष्ठा adapter *padapter);

व्योम	rtw_hal_मुक्त_data(काष्ठा adapter *padapter);

व्योम rtw_hal_dm_init(काष्ठा adapter *padapter);
व्योम rtw_hal_sw_led_init(काष्ठा adapter *padapter);
व्योम rtw_hal_sw_led_deinit(काष्ठा adapter *padapter);

u32 rtw_hal_घातer_on(काष्ठा adapter *padapter);
uपूर्णांक rtw_hal_init(काष्ठा adapter *padapter);
uपूर्णांक rtw_hal_deinit(काष्ठा adapter *padapter);
व्योम rtw_hal_stop(काष्ठा adapter *padapter);
व्योम rtw_hal_set_hwreg(काष्ठा adapter *padapter, u8 variable, u8 *val);
व्योम rtw_hal_get_hwreg(काष्ठा adapter *padapter, u8 variable, u8 *val);

व्योम rtw_hal_chip_configure(काष्ठा adapter *padapter);
व्योम rtw_hal_पढ़ो_chip_info(काष्ठा adapter *padapter);
व्योम rtw_hal_पढ़ो_chip_version(काष्ठा adapter *padapter);

u8 rtw_hal_get_def_var(काष्ठा adapter *padapter,
		       क्रमागत hal_def_variable eVariable, व्योम *pValue);

व्योम rtw_hal_set_odm_var(काष्ठा adapter *padapter,
			 क्रमागत hal_odm_variable eVariable, व्योम *pValue1,
			 bool bSet);

u32	rtw_hal_inirp_init(काष्ठा adapter *padapter);
व्योम	rtw_hal_inirp_deinit(काष्ठा adapter *padapter);
व्योम usb_पूर्णांकf_stop(काष्ठा adapter *padapter);

bool rtw_hal_xmit(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
s32	rtw_hal_mgnt_xmit(काष्ठा adapter *padapter,
			  काष्ठा xmit_frame *pmgntframe);

s32	rtw_hal_init_xmit_priv(काष्ठा adapter *padapter);

पूर्णांक	rtw_hal_init_recv_priv(काष्ठा adapter *padapter);
व्योम	rtw_hal_मुक्त_recv_priv(काष्ठा adapter *padapter);

व्योम rtw_hal_update_ra_mask(काष्ठा adapter *padapter, u32 mac_id, u8 level);
व्योम	rtw_hal_add_ra_tid(काष्ठा adapter *adapt, u32 biपंचांगap, u8 arg, u8 level);
व्योम	rtw_hal_clone_data(काष्ठा adapter *dst_adapt,
			   काष्ठा adapter *src_adapt);

व्योम beacon_timing_control(काष्ठा adapter *padapter);

u32	rtw_hal_पढ़ो_rfreg(काष्ठा adapter *padapter, क्रमागत rf_radio_path eRFPath,
			   u32 RegAddr, u32 BitMask);

व्योम	rtw_hal_set_bwmode(काष्ठा adapter *padapter,
			   क्रमागत ht_channel_width Bandwidth, u8 Offset);
व्योम	rtw_hal_set_chan(काष्ठा adapter *padapter, u8 channel);
व्योम	rtw_hal_dm_watchकरोg(काष्ठा adapter *padapter);

bool rtw_hal_antभाग_beक्रमe_linked(काष्ठा adapter *padapter);
व्योम	rtw_hal_antभाग_rssi_compared(काष्ठा adapter *padapter,
				     काष्ठा wlan_bssid_ex *dst,
				     काष्ठा wlan_bssid_ex *src);

व्योम rtw_hal_sreset_init(काष्ठा adapter *padapter);

व्योम rtw_hal_notch_filter(काष्ठा adapter *adapter, bool enable);

व्योम indicate_wx_scan_complete_event(काष्ठा adapter *padapter);
u8 rtw_करो_join(काष्ठा adapter *padapter);

#पूर्ण_अगर /* __HAL_INTF_H__ */
