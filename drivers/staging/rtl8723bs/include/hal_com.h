<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_COMMON_H__
#घोषणा __HAL_COMMON_H__

#समावेश "HalVerDef.h"
#समावेश "hal_pg.h"
#समावेश "hal_phy.h"
#समावेश "hal_phy_reg.h"
#समावेश "hal_com_reg.h"
#समावेश "hal_com_phycfg.h"

/*------------------------------ Tx Desc definition Macro ------------------------*/
/* pragma mark -- Tx Desc related definition. -- */
/*  */
/*  */
/* 	Rate */
/*  */
/*  CCK Rates, TxHT = 0 */
#घोषणा DESC_RATE1M					0x00
#घोषणा DESC_RATE2M					0x01
#घोषणा DESC_RATE5_5M				0x02
#घोषणा DESC_RATE11M				0x03

/*  OFDM Rates, TxHT = 0 */
#घोषणा DESC_RATE6M					0x04
#घोषणा DESC_RATE9M					0x05
#घोषणा DESC_RATE12M				0x06
#घोषणा DESC_RATE18M				0x07
#घोषणा DESC_RATE24M				0x08
#घोषणा DESC_RATE36M				0x09
#घोषणा DESC_RATE48M				0x0a
#घोषणा DESC_RATE54M				0x0b

/*  MCS Rates, TxHT = 1 */
#घोषणा DESC_RATEMCS0				0x0c
#घोषणा DESC_RATEMCS1				0x0d
#घोषणा DESC_RATEMCS2				0x0e
#घोषणा DESC_RATEMCS3				0x0f
#घोषणा DESC_RATEMCS4				0x10
#घोषणा DESC_RATEMCS5				0x11
#घोषणा DESC_RATEMCS6				0x12
#घोषणा DESC_RATEMCS7				0x13
#घोषणा DESC_RATEMCS8				0x14
#घोषणा DESC_RATEMCS9				0x15
#घोषणा DESC_RATEMCS10				0x16
#घोषणा DESC_RATEMCS11				0x17
#घोषणा DESC_RATEMCS12				0x18
#घोषणा DESC_RATEMCS13				0x19
#घोषणा DESC_RATEMCS14				0x1a
#घोषणा DESC_RATEMCS15				0x1b
#घोषणा DESC_RATEMCS16				0x1C
#घोषणा DESC_RATEMCS17				0x1D
#घोषणा DESC_RATEMCS18				0x1E
#घोषणा DESC_RATEMCS19				0x1F
#घोषणा DESC_RATEMCS20				0x20
#घोषणा DESC_RATEMCS21				0x21
#घोषणा DESC_RATEMCS22				0x22
#घोषणा DESC_RATEMCS23				0x23
#घोषणा DESC_RATEMCS24				0x24
#घोषणा DESC_RATEMCS25				0x25
#घोषणा DESC_RATEMCS26				0x26
#घोषणा DESC_RATEMCS27				0x27
#घोषणा DESC_RATEMCS28				0x28
#घोषणा DESC_RATEMCS29				0x29
#घोषणा DESC_RATEMCS30				0x2A
#घोषणा DESC_RATEMCS31				0x2B
#घोषणा DESC_RATEVHTSS1MCS0		0x2C
#घोषणा DESC_RATEVHTSS1MCS1		0x2D
#घोषणा DESC_RATEVHTSS1MCS2		0x2E
#घोषणा DESC_RATEVHTSS1MCS3		0x2F
#घोषणा DESC_RATEVHTSS1MCS4		0x30
#घोषणा DESC_RATEVHTSS1MCS5		0x31
#घोषणा DESC_RATEVHTSS1MCS6		0x32
#घोषणा DESC_RATEVHTSS1MCS7		0x33
#घोषणा DESC_RATEVHTSS1MCS8		0x34
#घोषणा DESC_RATEVHTSS1MCS9		0x35
#घोषणा DESC_RATEVHTSS2MCS0		0x36
#घोषणा DESC_RATEVHTSS2MCS1		0x37
#घोषणा DESC_RATEVHTSS2MCS2		0x38
#घोषणा DESC_RATEVHTSS2MCS3		0x39
#घोषणा DESC_RATEVHTSS2MCS4		0x3A
#घोषणा DESC_RATEVHTSS2MCS5		0x3B
#घोषणा DESC_RATEVHTSS2MCS6		0x3C
#घोषणा DESC_RATEVHTSS2MCS7		0x3D
#घोषणा DESC_RATEVHTSS2MCS8		0x3E
#घोषणा DESC_RATEVHTSS2MCS9		0x3F
#घोषणा DESC_RATEVHTSS3MCS0		0x40
#घोषणा DESC_RATEVHTSS3MCS1		0x41
#घोषणा DESC_RATEVHTSS3MCS2		0x42
#घोषणा DESC_RATEVHTSS3MCS3		0x43
#घोषणा DESC_RATEVHTSS3MCS4		0x44
#घोषणा DESC_RATEVHTSS3MCS5		0x45
#घोषणा DESC_RATEVHTSS3MCS6		0x46
#घोषणा DESC_RATEVHTSS3MCS7		0x47
#घोषणा DESC_RATEVHTSS3MCS8		0x48
#घोषणा DESC_RATEVHTSS3MCS9		0x49
#घोषणा DESC_RATEVHTSS4MCS0		0x4A
#घोषणा DESC_RATEVHTSS4MCS1		0x4B
#घोषणा DESC_RATEVHTSS4MCS2		0x4C
#घोषणा DESC_RATEVHTSS4MCS3		0x4D
#घोषणा DESC_RATEVHTSS4MCS4		0x4E
#घोषणा DESC_RATEVHTSS4MCS5		0x4F
#घोषणा DESC_RATEVHTSS4MCS6		0x50
#घोषणा DESC_RATEVHTSS4MCS7		0x51
#घोषणा DESC_RATEVHTSS4MCS8		0x52
#घोषणा DESC_RATEVHTSS4MCS9		0x53

#घोषणा HDATA_RATE(rate)\
(rate == DESC_RATE1M) ? "CCK_1M" : \
(rate == DESC_RATE2M) ? "CCK_2M" : \
(rate == DESC_RATE5_5M) ? "CCK5_5M" : \
(rate == DESC_RATE11M) ? "CCK_11M" : \
(rate == DESC_RATE6M) ? "OFDM_6M" : \
(rate == DESC_RATE9M) ? "OFDM_9M" : \
(rate == DESC_RATE12M) ? "OFDM_12M" : \
(rate == DESC_RATE18M) ? "OFDM_18M" : \
(rate == DESC_RATE24M) ? "OFDM_24M" : \
(rate == DESC_RATE36M) ? "OFDM_36M" : \
(rate == DESC_RATE48M) ? "OFDM_48M" : \
(rate == DESC_RATE54M) ? "OFDM_54M" : \
(rate == DESC_RATEMCS0) ? "MCS0" : \
(rate == DESC_RATEMCS1) ? "MCS1" : \
(rate == DESC_RATEMCS2) ? "MCS2" : \
(rate == DESC_RATEMCS3) ? "MCS3" : \
(rate == DESC_RATEMCS4) ? "MCS4" : \
(rate == DESC_RATEMCS5) ? "MCS5" : \
(rate == DESC_RATEMCS6) ? "MCS6" : \
(rate == DESC_RATEMCS7) ? "MCS7" : \
(rate == DESC_RATEMCS8) ? "MCS8" : \
(rate == DESC_RATEMCS9) ? "MCS9" : \
(rate == DESC_RATEMCS10) ? "MCS10" : \
(rate == DESC_RATEMCS11) ? "MCS11" : \
(rate == DESC_RATEMCS12) ? "MCS12" : \
(rate == DESC_RATEMCS13) ? "MCS13" : \
(rate == DESC_RATEMCS14) ? "MCS14" : \
(rate == DESC_RATEMCS15) ? "MCS15" : \
(rate == DESC_RATEVHTSS1MCS0) ? "VHTSS1MCS0" : \
(rate == DESC_RATEVHTSS1MCS1) ? "VHTSS1MCS1" : \
(rate == DESC_RATEVHTSS1MCS2) ? "VHTSS1MCS2" : \
(rate == DESC_RATEVHTSS1MCS3) ? "VHTSS1MCS3" : \
(rate == DESC_RATEVHTSS1MCS4) ? "VHTSS1MCS4" : \
(rate == DESC_RATEVHTSS1MCS5) ? "VHTSS1MCS5" : \
(rate == DESC_RATEVHTSS1MCS6) ? "VHTSS1MCS6" : \
(rate == DESC_RATEVHTSS1MCS7) ? "VHTSS1MCS7" : \
(rate == DESC_RATEVHTSS1MCS8) ? "VHTSS1MCS8" : \
(rate == DESC_RATEVHTSS1MCS9) ? "VHTSS1MCS9" : \
(rate == DESC_RATEVHTSS2MCS0) ? "VHTSS2MCS0" : \
(rate == DESC_RATEVHTSS2MCS1) ? "VHTSS2MCS1" : \
(rate == DESC_RATEVHTSS2MCS2) ? "VHTSS2MCS2" : \
(rate == DESC_RATEVHTSS2MCS3) ? "VHTSS2MCS3" : \
(rate == DESC_RATEVHTSS2MCS4) ? "VHTSS2MCS4" : \
(rate == DESC_RATEVHTSS2MCS5) ? "VHTSS2MCS5" : \
(rate == DESC_RATEVHTSS2MCS6) ? "VHTSS2MCS6" : \
(rate == DESC_RATEVHTSS2MCS7) ? "VHTSS2MCS7" : \
(rate == DESC_RATEVHTSS2MCS8) ? "VHTSS2MCS8" : \
(rate == DESC_RATEVHTSS2MCS9) ? "VHTSS2MCS9" : "UNKNOWN"


क्रमागतअणु
	UP_LINK,
	DOWN_LINK,
पूर्ण;
क्रमागत rt_media_status अणु
	RT_MEDIA_DISCONNECT = 0,
	RT_MEDIA_CONNECT       = 1
पूर्ण;

#घोषणा MAX_DLFW_PAGE_SIZE			4096	/*  @ page : 4k bytes */

/*  BK, BE, VI, VO, HCCA, MANAGEMENT, COMMAND, HIGH, BEACON. */
/* define MAX_TX_QUEUE		9 */

#घोषणा TX_SELE_HQ			BIT(0)		/*  High Queue */
#घोषणा TX_SELE_LQ			BIT(1)		/*  Low Queue */
#घोषणा TX_SELE_NQ			BIT(2)		/*  Normal Queue */
#घोषणा TX_SELE_EQ			BIT(3)		/*  Extern Queue */

#घोषणा PageNum_128(_Len)		((u32)(((_Len) >> 7) + ((_Len) & 0x7F ? 1 : 0)))

u8 rtw_hal_data_init(काष्ठा adapter *padapter);
व्योम rtw_hal_data_deinit(काष्ठा adapter *padapter);

व्योम dump_chip_info(काष्ठा hal_version	ChipVersion);

u8 /* वापस the final channel plan decision */
hal_com_config_channel_plan(
काष्ठा adapter *padapter,
u8 	hw_channel_plan,	/* channel plan from HW (efuse/eeprom) */
u8 	sw_channel_plan,	/* channel plan from SW (registry/module param) */
u8 	def_channel_plan,	/* channel plan used when the क्रमmer two is invalid */
bool		AutoLoadFail
	);

bool
HAL_IsLegalChannel(
काष्ठा adapter *Adapter,
u32 		Channel
	);

u8 MRateToHwRate(u8 rate);

u8 HwRateToMRate(u8 rate);

व्योम HalSetBrateCfg(
	काष्ठा adapter *Adapter,
	u8 *mBratesOS,
	u16	*pBrateCfg);

bool
Hal_MappingOutPipe(
काष्ठा adapter *padapter,
u8 NumOutPipe
	);

व्योम hal_init_macaddr(काष्ठा adapter *adapter);

व्योम rtw_init_hal_com_शेष_value(काष्ठा adapter *Adapter);

व्योम c2h_evt_clear(काष्ठा adapter *adapter);
s32 c2h_evt_पढ़ो_88xx(काष्ठा adapter *adapter, u8 *buf);

u8 rtw_get_mgntframe_raid(काष्ठा adapter *adapter, अचिन्हित अक्षर network_type);
व्योम rtw_hal_update_sta_rate_mask(काष्ठा adapter *padapter, काष्ठा sta_info *psta);

व्योम hw_var_port_चयन(काष्ठा adapter *adapter);

व्योम SetHwReg(काष्ठा adapter *padapter, u8 variable, u8 *val);
व्योम GetHwReg(काष्ठा adapter *padapter, u8 variable, u8 *val);
व्योम rtw_hal_check_rxfअगरo_full(काष्ठा adapter *adapter);

u8 SetHalDefVar(काष्ठा adapter *adapter, क्रमागत hal_def_variable variable,
		व्योम *value);
u8 GetHalDefVar(काष्ठा adapter *adapter, क्रमागत hal_def_variable variable,
		व्योम *value);

bool eqNByte(u8 *str1, u8 *str2, u32 num);

bool IsHexDigit(अक्षर chTmp);

u32 MapCharToHexDigit(अक्षर chTmp);

bool GetHexValueFromString(अक्षर *szStr, u32 *pu4bVal, u32 *pu4bMove);

bool GetFractionValueFromString(अक्षर *szStr, u8 *pInteger, u8 *pFraction,
				u32 *pu4bMove);

bool IsCommentString(अक्षर *szStr);

bool ParseQualअगरiedString(अक्षर *In, u32 *Start, अक्षर *Out, अक्षर LeftQualअगरier,
			  अक्षर RightQualअगरier);

bool GetU1ByteIntegerFromStringInDecimal(अक्षर *str, u8 *in);

bool isAllSpaceOrTab(u8 *data, u8 size);

व्योम linked_info_dump(काष्ठा adapter *padapter, u8 benable);
#अगर_घोषित DBG_RX_SIGNAL_DISPLAY_RAW_DATA
व्योम rtw_get_raw_rssi_info(व्योम *sel, काष्ठा adapter *padapter);
व्योम rtw_store_phy_info(काष्ठा adapter *padapter, जोड़ recv_frame *prframe);
व्योम rtw_dump_raw_rssi_info(काष्ठा adapter *padapter);
#पूर्ण_अगर

#घोषणा		HWSET_MAX_SIZE			512

व्योम rtw_bb_rf_gain_offset(काष्ठा adapter *padapter);

व्योम GetHalODMVar(काष्ठा adapter *Adapter,
	क्रमागत hal_odm_variable		eVariable,
	व्योम *pValue1,
	व्योम *pValue2);
व्योम SetHalODMVar(
	काष्ठा adapter *Adapter,
	क्रमागत hal_odm_variable		eVariable,
	व्योम *pValue1,
	bool					bSet);
#पूर्ण_अगर /* __HAL_COMMON_H__ */
