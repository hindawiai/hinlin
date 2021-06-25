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
#अगर_अघोषित _RTL871X_MP_IOCTL_H
#घोषणा _RTL871X_MP_IOCTL_H

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "mp_custom_oid.h"
#समावेश "rtl871x_ioctl.h"
#समावेश "rtl871x_ioctl_rtl.h"
#समावेश "rtl8712_efuse.h"

#घोषणा TESTFWCMDNUMBER			1000000
#घोषणा TEST_H2CINT_WAIT_TIME		500
#घोषणा TEST_C2HINT_WAIT_TIME		500
#घोषणा HCI_TEST_SYSCFG_HWMASK		1
#घोषणा _BUSCLK_40M			(4 << 2)

काष्ठा CFG_DBG_MSG_STRUCT अणु
	u32 DebugLevel;
	u32 DebugComponent_H32;
	u32 DebugComponent_L32;
पूर्ण;

काष्ठा mp_rw_reg अणु
	uपूर्णांक offset;
	uपूर्णांक width;
	u32 value;
पूर्ण;

/* क्रम OID_RT_PRO_READ16_EEPROM & OID_RT_PRO_WRITE16_EEPROM */
काष्ठा eeprom_rw_param अणु
	uपूर्णांक offset;
	u16 value;
पूर्ण;

काष्ठा EFUSE_ACCESS_STRUCT अणु
	u16	start_addr;
	u16	cnts;
	u8	data[];
पूर्ण;

काष्ठा burst_rw_reg अणु
	uपूर्णांक offset;
	uपूर्णांक len;
	u8 Data[256];
पूर्ण;

काष्ठा usb_venकरोr_req अणु
	u8	bRequest;
	u16	wValue;
	u16	wIndex;
	u16	wLength;
	u8	u8Dir;/*0:OUT, 1:IN */
	u8	u8InData;
पूर्ण;

काष्ठा DR_VARIABLE_STRUCT अणु
	u8 offset;
	u32 variable;
पूर्ण;

/* oid_rtl_seg_87_11_00 */
uपूर्णांक oid_rt_pro_पढ़ो_रेजिस्टर_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_ग_लिखो_रेजिस्टर_hdl(काष्ठा oid_par_priv *poid_par_priv);
/* oid_rtl_seg_81_80_00 */
uपूर्णांक oid_rt_pro_set_data_rate_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_start_test_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_stop_test_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_set_channel_direct_call_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_set_antenna_bb_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_set_tx_घातer_control_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
/* oid_rtl_seg_81_80_20 */
uपूर्णांक oid_rt_pro_query_tx_packet_sent_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_query_rx_packet_received_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_query_rx_packet_crc32_error_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_reset_tx_packet_sent_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_reset_rx_packet_received_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_set_modulation_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_set_continuous_tx_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_set_single_carrier_tx_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_set_carrier_suppression_tx_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_set_single_tone_tx_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
/* oid_rtl_seg_81_87 */
uपूर्णांक oid_rt_pro_ग_लिखो_bb_reg_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_पढ़ो_bb_reg_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_ग_लिखो_rf_reg_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_पढ़ो_rf_reg_hdl(काष्ठा oid_par_priv *poid_par_priv);
/* oid_rtl_seg_81_85 */
uपूर्णांक oid_rt_wireless_mode_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_पढ़ो_efuse_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_ग_लिखो_efuse_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_efuse_current_size_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_efuse_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_efuse_map_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_set_bandwidth_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_set_rx_packet_type_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_efuse_max_size_hdl(काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_thermal_meter_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_reset_phy_rx_packet_count_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_phy_rx_packet_received_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_phy_rx_packet_crc32_error_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_set_घातer_करोwn_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_घातer_mode_hdl(
				काष्ठा oid_par_priv *poid_par_priv);
#अगर_घोषित _RTL871X_MP_IOCTL_C_ /* CAUTION!!! */
/* This अगरdef _MUST_ be left in!! */
अटल स्थिर काष्ठा oid_obj_priv oid_rtl_seg_81_80_00[] = अणु
	/* 0x00	OID_RT_PRO_RESET_DUT */
	अणु1, oid_null_functionपूर्ण,
	/* 0x01 */
	अणु1, oid_rt_pro_set_data_rate_hdlपूर्ण,
	/* 0x02 */
	अणु1, oid_rt_pro_start_test_hdlपूर्ण,
	/* 0x03 */
	अणु1, oid_rt_pro_stop_test_hdlपूर्ण,
	/* 0x04	OID_RT_PRO_SET_PREAMBLE */
	अणु1, oid_null_functionपूर्ण,
	/* 0x05	OID_RT_PRO_SET_SCRAMBLER */
	अणु1, oid_null_functionपूर्ण,
	/* 0x06	OID_RT_PRO_SET_FILTER_BB */
	अणु1, oid_null_functionपूर्ण,
	/* 0x07  OID_RT_PRO_SET_MANUAL_DIVERS_BB */
	अणु1, oid_null_functionपूर्ण,
	/* 0x08 */
	अणु1, oid_rt_pro_set_channel_direct_call_hdlपूर्ण,
	/* 0x09  OID_RT_PRO_SET_SLEEP_MODE_सूचीECT_CALL */
	अणु1, oid_null_functionपूर्ण,
	/* 0x0A  OID_RT_PRO_SET_WAKE_MODE_सूचीECT_CALL */
	अणु1, oid_null_functionपूर्ण,
	/* 0x0B OID_RT_PRO_SET_TX_CONTINUOUS_सूचीECT_CALL */
	अणु1, oid_rt_pro_set_continuous_tx_hdlपूर्ण,
	/* 0x0C OID_RT_PRO_SET_SINGLE_CARRIER_TX_CONTINUOUS */
	अणु1, oid_rt_pro_set_single_carrier_tx_hdlपूर्ण,
	/* 0x0D OID_RT_PRO_SET_TX_ANTENNA_BB */
	अणु1, oid_null_functionपूर्ण,
	/* 0x0E */
	अणु1, oid_rt_pro_set_antenna_bb_hdlपूर्ण,
	/* 0x0F	OID_RT_PRO_SET_CR_SCRAMBLER */
	अणु1, oid_null_functionपूर्ण,
	/* 0x10	OID_RT_PRO_SET_CR_NEW_FILTER */
	अणु1, oid_null_functionपूर्ण,
	/* 0x11 OID_RT_PRO_SET_TX_POWER_CONTROL */
	अणु1, oid_rt_pro_set_tx_घातer_control_hdlपूर्ण,
	/* 0x12	OID_RT_PRO_SET_CR_TX_CONFIG */
	अणु1, oid_null_functionपूर्ण,
	/* 0x13  OID_RT_PRO_GET_TX_POWER_CONTROL */
	अणु1, oid_null_functionपूर्ण,
	/* 0x14  OID_RT_PRO_GET_CR_SIGNAL_QUALITY */
	अणु1, oid_null_functionपूर्ण,
	/* 0x15	OID_RT_PRO_SET_CR_SETPOINT */
	अणु1, oid_null_functionपूर्ण,
	/* 0x16	OID_RT_PRO_SET_INTEGRATOR */
	अणु1, oid_null_functionपूर्ण,
	/* 0x17	OID_RT_PRO_SET_SIGNAL_QUALITY */
	अणु1, oid_null_functionपूर्ण,
	/* 0x18	OID_RT_PRO_GET_INTEGRATOR */
	अणु1, oid_null_functionपूर्ण,
	/* 0x19	OID_RT_PRO_GET_SIGNAL_QUALITY */
	अणु1, oid_null_functionपूर्ण,
	/* 0x1A	OID_RT_PRO_QUERY_EEPROM_TYPE */
	अणु1, oid_null_functionपूर्ण,
	/* 0x1B	OID_RT_PRO_WRITE_MAC_ADDRESS */
	अणु1, oid_null_functionपूर्ण,
	/* 0x1C	OID_RT_PRO_READ_MAC_ADDRESS */
	अणु1, oid_null_functionपूर्ण,
	/* 0x1D	OID_RT_PRO_WRITE_CIS_DATA */
	अणु1, oid_null_functionपूर्ण,
	/* 0x1E	OID_RT_PRO_READ_CIS_DATA */
	अणु1, oid_null_functionपूर्ण,
	/* 0x1F	OID_RT_PRO_WRITE_POWER_CONTROL */
	अणु1, oid_null_functionपूर्ण
पूर्ण;

अटल स्थिर काष्ठा oid_obj_priv oid_rtl_seg_81_80_20[] = अणु
	/* 0x20	OID_RT_PRO_READ_POWER_CONTROL */
	अणु1, oid_null_functionपूर्ण,
	/* 0x21	OID_RT_PRO_WRITE_EEPROM */
	अणु1, oid_null_functionपूर्ण,
	/* 0x22	OID_RT_PRO_READ_EEPROM */
	अणु1, oid_null_functionपूर्ण,
	/* 0x23 */
	अणु1, oid_rt_pro_reset_tx_packet_sent_hdlपूर्ण,
	/* 0x24 */
	अणु1, oid_rt_pro_query_tx_packet_sent_hdlपूर्ण,
	/* 0x25 */
	अणु1, oid_rt_pro_reset_rx_packet_received_hdlपूर्ण,
	/* 0x26 */
	अणु1, oid_rt_pro_query_rx_packet_received_hdlपूर्ण,
	/* 0x27 */
	अणु1, oid_rt_pro_query_rx_packet_crc32_error_hdlपूर्ण,
	/* 0x28 OID_RT_PRO_QUERY_CURRENT_ADDRESS */
	अणु1, oid_null_functionपूर्ण,
	/* 0x29 OID_RT_PRO_QUERY_PERMANENT_ADDRESS */
	अणु1, oid_null_functionपूर्ण,
	/* 0x2A OID_RT_PRO_SET_PHILIPS_RF_PARAMETERS */
	अणु1, oid_null_functionपूर्ण,
	/* 0x2B OID_RT_PRO_SET_CARRIER_SUPPRESSION_TX */
	अणु1, oid_rt_pro_set_carrier_suppression_tx_hdlपूर्ण,
	/* 0x2C	OID_RT_PRO_RECEIVE_PACKET */
	अणु1, oid_null_functionपूर्ण,
	/* 0x2D	OID_RT_PRO_WRITE_EEPROM_BYTE */
	अणु1, oid_null_functionपूर्ण,
	/* 0x2E	OID_RT_PRO_READ_EEPROM_BYTE */
	अणु1, oid_null_functionपूर्ण,
	/* 0x2F */
	अणु1, oid_rt_pro_set_modulation_hdlपूर्ण
पूर्ण;

अटल स्थिर काष्ठा oid_obj_priv oid_rtl_seg_81_80_40[] = अणु
	अणु1, oid_null_functionपूर्ण,				/* 0x40 */
	अणु1, oid_null_functionपूर्ण,				/* 0x41 */
	अणु1, oid_null_functionपूर्ण,				/* 0x42 */
	अणु1, oid_rt_pro_set_single_tone_tx_hdlपूर्ण,		/* 0x43 */
	अणु1, oid_null_functionपूर्ण,				/* 0x44 */
	अणु1, oid_null_functionपूर्ण				/* 0x45 */
पूर्ण;

अटल स्थिर काष्ठा oid_obj_priv oid_rtl_seg_81_80_80[] = अणु
	अणु1, oid_null_functionपूर्ण,		/* 0x80	OID_RT_DRIVER_OPTION */
	अणु1, oid_null_functionपूर्ण,		/* 0x81	OID_RT_RF_OFF */
	अणु1, oid_null_functionपूर्ण		/* 0x82	OID_RT_AUTH_STATUS */

पूर्ण;

अटल स्थिर काष्ठा oid_obj_priv oid_rtl_seg_81_85[] = अणु
	/* 0x00	OID_RT_WIRELESS_MODE */
	अणु1, oid_rt_wireless_mode_hdlपूर्ण
पूर्ण;

#अन्यथा /* _RTL871X_MP_IOCTL_C_ */
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_81_80_00[32];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_81_80_20[16];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_81_80_40[6];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_81_80_80[3];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_81_85[1];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_81_87[5];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_87_11_00[32];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_87_11_20[5];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_87_11_50[2];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_87_11_80[1];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_87_11_B0[1];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_87_11_F0[16];
बाह्य काष्ठा oid_obj_priv oid_rtl_seg_87_12_00[32];

#पूर्ण_अगर /* _RTL871X_MP_IOCTL_C_ */


क्रमागत MP_MODE अणु
	MP_START_MODE,
	MP_STOP_MODE,
	MP_ERR_MODE
पूर्ण;

काष्ठा rwreg_param अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक value;
पूर्ण;

काष्ठा bbreg_param अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक phymask;
	अचिन्हित पूर्णांक value;
पूर्ण;

काष्ठा txघातer_param अणु
	अचिन्हित पूर्णांक pwr_index;
पूर्ण;

काष्ठा datarate_param अणु
	अचिन्हित पूर्णांक rate_index;
पूर्ण;

काष्ठा rfपूर्णांकfs_parm अणु
	अचिन्हित पूर्णांक rfपूर्णांकfs;
पूर्ण;

काष्ठा mp_xmit_packet अणु
	अचिन्हित पूर्णांक len;
पूर्ण;

काष्ठा psmode_param अणु
	अचिन्हित पूर्णांक ps_mode;
	अचिन्हित पूर्णांक smart_ps;
पूर्ण;

काष्ठा mp_ioctl_handler अणु
	अचिन्हित पूर्णांक paramsize;
	अचिन्हित पूर्णांक (*handler)(काष्ठा oid_par_priv *poid_par_priv);
	अचिन्हित पूर्णांक oid;
पूर्ण;

काष्ठा mp_ioctl_param अणु
	अचिन्हित पूर्णांक subcode;
	अचिन्हित पूर्णांक len;
	अचिन्हित अक्षर data[];
पूर्ण;

#घोषणा GEN_MP_IOCTL_SUBCODE(code) _MP_IOCTL_ ## code ## _CMD_

क्रमागत RTL871X_MP_IOCTL_SUBCODE अणु
	GEN_MP_IOCTL_SUBCODE(MP_START),			/*0*/
	GEN_MP_IOCTL_SUBCODE(MP_STOP),			/*1*/
	GEN_MP_IOCTL_SUBCODE(READ_REG),			/*2*/
	GEN_MP_IOCTL_SUBCODE(WRITE_REG),
	GEN_MP_IOCTL_SUBCODE(SET_CHANNEL),		/*4*/
	GEN_MP_IOCTL_SUBCODE(SET_TXPOWER),		/*5*/
	GEN_MP_IOCTL_SUBCODE(SET_DATARATE),		/*6*/
	GEN_MP_IOCTL_SUBCODE(READ_BB_REG),		/*7*/
	GEN_MP_IOCTL_SUBCODE(WRITE_BB_REG),
	GEN_MP_IOCTL_SUBCODE(READ_RF_REG),		/*9*/
	GEN_MP_IOCTL_SUBCODE(WRITE_RF_REG),
	GEN_MP_IOCTL_SUBCODE(SET_RF_INTFS),
	GEN_MP_IOCTL_SUBCODE(IOCTL_XMIT_PACKET),	/*12*/
	GEN_MP_IOCTL_SUBCODE(PS_STATE),			/*13*/
	GEN_MP_IOCTL_SUBCODE(READ16_EEPROM),		/*14*/
	GEN_MP_IOCTL_SUBCODE(WRITE16_EEPROM),		/*15*/
	GEN_MP_IOCTL_SUBCODE(SET_PTM),			/*16*/
	GEN_MP_IOCTL_SUBCODE(READ_TSSI),		/*17*/
	GEN_MP_IOCTL_SUBCODE(CNTU_TX),			/*18*/
	GEN_MP_IOCTL_SUBCODE(SET_BANDWIDTH),		/*19*/
	GEN_MP_IOCTL_SUBCODE(SET_RX_PKT_TYPE),		/*20*/
	GEN_MP_IOCTL_SUBCODE(RESET_PHY_RX_PKT_CNT),	/*21*/
	GEN_MP_IOCTL_SUBCODE(GET_PHY_RX_PKT_RECV),	/*22*/
	GEN_MP_IOCTL_SUBCODE(GET_PHY_RX_PKT_ERROR),	/*23*/
	GEN_MP_IOCTL_SUBCODE(SET_POWER_DOWN),		/*24*/
	GEN_MP_IOCTL_SUBCODE(GET_THERMAL_METER),	/*25*/
	GEN_MP_IOCTL_SUBCODE(GET_POWER_MODE),		/*26*/
	GEN_MP_IOCTL_SUBCODE(EFUSE),			/*27*/
	GEN_MP_IOCTL_SUBCODE(EFUSE_MAP),		/*28*/
	GEN_MP_IOCTL_SUBCODE(GET_EFUSE_MAX_SIZE),	/*29*/
	GEN_MP_IOCTL_SUBCODE(GET_EFUSE_CURRENT_SIZE),	/*30*/
	GEN_MP_IOCTL_SUBCODE(SC_TX),			/*31*/
	GEN_MP_IOCTL_SUBCODE(CS_TX),			/*32*/
	GEN_MP_IOCTL_SUBCODE(ST_TX),			/*33*/
	GEN_MP_IOCTL_SUBCODE(SET_ANTENNA),		/*34*/
	MAX_MP_IOCTL_SUBCODE,
पूर्ण;

अचिन्हित पूर्णांक mp_ioctl_xmit_packet_hdl(काष्ठा oid_par_priv *poid_par_priv);

#अगर_घोषित _RTL871X_MP_IOCTL_C_ /* CAUTION!!! */
/* This अगरdef _MUST_ be left in!! */

अटल काष्ठा mp_ioctl_handler mp_ioctl_hdl[] = अणु
	अणुमाप(u32), oid_rt_pro_start_test_hdl,
			     OID_RT_PRO_START_TESTपूर्ण,/*0*/
	अणुमाप(u32), oid_rt_pro_stop_test_hdl,
			     OID_RT_PRO_STOP_TESTपूर्ण,/*1*/
	अणुमाप(काष्ठा rwreg_param),
			     oid_rt_pro_पढ़ो_रेजिस्टर_hdl,
			     OID_RT_PRO_READ_REGISTERपूर्ण,/*2*/
	अणुमाप(काष्ठा rwreg_param),
			     oid_rt_pro_ग_लिखो_रेजिस्टर_hdl,
			     OID_RT_PRO_WRITE_REGISTERपूर्ण,
	अणुमाप(u32),
			     oid_rt_pro_set_channel_direct_call_hdl,
			     OID_RT_PRO_SET_CHANNEL_सूचीECT_CALLपूर्ण,
	अणुमाप(काष्ठा txघातer_param),
			     oid_rt_pro_set_tx_घातer_control_hdl,
			     OID_RT_PRO_SET_TX_POWER_CONTROLपूर्ण,
	अणुमाप(u32),
			     oid_rt_pro_set_data_rate_hdl,
			     OID_RT_PRO_SET_DATA_RATEपूर्ण,
	अणुमाप(काष्ठा bb_reg_param),
			     oid_rt_pro_पढ़ो_bb_reg_hdl,
			     OID_RT_PRO_READ_BB_REGपूर्ण,/*7*/
	अणुमाप(काष्ठा bb_reg_param),
			     oid_rt_pro_ग_लिखो_bb_reg_hdl,
			     OID_RT_PRO_WRITE_BB_REGपूर्ण,
	अणुमाप(काष्ठा rwreg_param),
			     oid_rt_pro_पढ़ो_rf_reg_hdl,
			     OID_RT_PRO_RF_READ_REGISTRYपूर्ण,/*9*/
	अणुमाप(काष्ठा rwreg_param),
			     oid_rt_pro_ग_लिखो_rf_reg_hdl,
			     OID_RT_PRO_RF_WRITE_REGISTRYपूर्ण,
	अणुमाप(काष्ठा rfपूर्णांकfs_parm), शून्य, 0पूर्ण,
	अणु0, mp_ioctl_xmit_packet_hdl, 0पूर्ण,/*12*/
	अणुमाप(काष्ठा psmode_param), शून्य, 0पूर्ण,/*13*/
	अणुमाप(काष्ठा eeprom_rw_param), शून्य, 0पूर्ण,/*14*/
	अणुमाप(काष्ठा eeprom_rw_param), शून्य, 0पूर्ण,/*15*/
	अणुमाप(अचिन्हित अक्षर), शून्य, 0पूर्ण,/*16*/
	अणुमाप(u32), शून्य, 0पूर्ण,/*17*/
	अणुमाप(u32), oid_rt_pro_set_continuous_tx_hdl,
			     OID_RT_PRO_SET_CONTINUOUS_TXपूर्ण,/*18*/
	अणुमाप(u32), oid_rt_set_bandwidth_hdl,
			     OID_RT_SET_BANDWIDTHपूर्ण,/*19*/
	अणुमाप(u32), oid_rt_set_rx_packet_type_hdl,
			     OID_RT_SET_RX_PACKET_TYPEपूर्ण,/*20*/
	अणु0, oid_rt_reset_phy_rx_packet_count_hdl,
			     OID_RT_RESET_PHY_RX_PACKET_COUNTपूर्ण,/*21*/
	अणुमाप(u32), oid_rt_get_phy_rx_packet_received_hdl,
			     OID_RT_GET_PHY_RX_PACKET_RECEIVEDपूर्ण,/*22*/
	अणुमाप(u32), oid_rt_get_phy_rx_packet_crc32_error_hdl,
			     OID_RT_GET_PHY_RX_PACKET_CRC32_ERRORपूर्ण,/*23*/
	अणुमाप(अचिन्हित अक्षर), oid_rt_set_घातer_करोwn_hdl,
			     OID_RT_SET_POWER_DOWNपूर्ण,/*24*/
	अणुमाप(u32), oid_rt_get_thermal_meter_hdl,
			     OID_RT_PRO_GET_THERMAL_METERपूर्ण,/*25*/
	अणुमाप(u32), oid_rt_get_घातer_mode_hdl,
			     OID_RT_GET_POWER_MODEपूर्ण,/*26*/
	अणुमाप(काष्ठा EFUSE_ACCESS_STRUCT),
			     oid_rt_pro_efuse_hdl, OID_RT_PRO_EFUSEपूर्ण,/*27*/
	अणुEFUSE_MAP_MAX_SIZE, oid_rt_pro_efuse_map_hdl,
			     OID_RT_PRO_EFUSE_MAPपूर्ण,/*28*/
	अणुमाप(u32), oid_rt_get_efuse_max_size_hdl,
			     OID_RT_GET_EFUSE_MAX_SIZEपूर्ण,/*29*/
	अणुमाप(u32), oid_rt_get_efuse_current_size_hdl,
			     OID_RT_GET_EFUSE_CURRENT_SIZEपूर्ण,/*30*/
	अणुमाप(u32), oid_rt_pro_set_single_carrier_tx_hdl,
			     OID_RT_PRO_SET_SINGLE_CARRIER_TXपूर्ण,/*31*/
	अणुमाप(u32), oid_rt_pro_set_carrier_suppression_tx_hdl,
			     OID_RT_PRO_SET_CARRIER_SUPPRESSION_TXपूर्ण,/*32*/
	अणुमाप(u32), oid_rt_pro_set_single_tone_tx_hdl,
			     OID_RT_PRO_SET_SINGLE_TONE_TXपूर्ण,/*33*/
	अणुमाप(u32), oid_rt_pro_set_antenna_bb_hdl,
			     OID_RT_PRO_SET_ANTENNA_BBपूर्ण,/*34*/
पूर्ण;

#अन्यथा /* _RTL871X_MP_IOCTL_C_ */
बाह्य काष्ठा mp_ioctl_handler mp_ioctl_hdl[];
#पूर्ण_अगर /* _RTL871X_MP_IOCTL_C_ */

#पूर्ण_अगर

