<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __FW_COMMON_H__
#घोषणा __FW_COMMON_H__

#घोषणा REG_SYS_FUNC_EN				0x0002
#घोषणा REG_MCUFWDL				0x0080
#घोषणा FW_8192C_PAGE_SIZE			4096
#घोषणा FW_8723A_POLLING_TIMEOUT_COUNT		1000
#घोषणा FW_8723B_POLLING_TIMEOUT_COUNT		6000
#घोषणा FW_8192C_POLLING_DELAY			5

#घोषणा MCUFWDL_RDY				BIT(1)
#घोषणा FWDL_CHKSUM_RPT				BIT(2)
#घोषणा WINTINI_RDY				BIT(6)

#घोषणा REG_RSV_CTRL				0x001C
#घोषणा REG_HMETFR				0x01CC

क्रमागत version_8723e अणु
	VERSION_TEST_UMC_CHIP_8723 = 0x0081,
	VERSION_NORMAL_UMC_CHIP_8723_1T1R_A_CUT = 0x0089,
	VERSION_NORMAL_UMC_CHIP_8723_1T1R_B_CUT = 0x1089,
	VERSION_TEST_CHIP_1T1R_8723B = 0x0106,
	VERSION_NORMAL_SMIC_CHIP_1T1R_8723B = 0x010E,
	VERSION_UNKNOWN = 0xFF,
पूर्ण;

क्रमागत rtl8723be_cmd अणु
	H2C_8723BE_RSVDPAGE = 0,
	H2C_8723BE_JOINBSSRPT = 1,
	H2C_8723BE_SCAN = 2,
	H2C_8723BE_KEEP_ALIVE_CTRL = 3,
	H2C_8723BE_DISCONNECT_DECISION = 4,
	H2C_8723BE_INIT_OFFLOAD = 6,
	H2C_8723BE_AP_OFFLOAD = 8,
	H2C_8723BE_BCN_RSVDPAGE = 9,
	H2C_8723BE_PROBERSP_RSVDPAGE = 10,

	H2C_8723BE_SETPWRMODE = 0x20,
	H2C_8723BE_PS_TUNING_PARA = 0x21,
	H2C_8723BE_PS_TUNING_PARA2 = 0x22,
	H2C_8723BE_PS_LPS_PARA = 0x23,
	H2C_8723BE_P2P_PS_OFFLOAD = 0x24,

	H2C_8723BE_WO_WLAN = 0x80,
	H2C_8723BE_REMOTE_WAKE_CTRL = 0x81,
	H2C_8723BE_AOAC_GLOBAL_INFO = 0x82,
	H2C_8723BE_AOAC_RSVDPAGE = 0x83,
	H2C_8723BE_RSSI_REPORT = 0x42,
	H2C_8723BE_RA_MASK = 0x40,
	H2C_8723BE_SELECTIVE_SUSPEND_ROF_CMD,
	H2C_8723BE_P2P_PS_MODE,
	H2C_8723BE_PSD_RESULT,
	/*Not defined CTW CMD क्रम P2P yet*/
	H2C_8723BE_P2P_PS_CTW_CMD,
	MAX_8723BE_H2CCMD
पूर्ण;

व्योम rtl8723ae_firmware_selfreset(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_firmware_selfreset(काष्ठा ieee80211_hw *hw);
व्योम rtl8723_enable_fw_करोwnload(काष्ठा ieee80211_hw *hw, bool enable);
व्योम rtl8723_ग_लिखो_fw(काष्ठा ieee80211_hw *hw,
		      क्रमागत version_8723e version,
		      u8 *buffer, u32 size, u8 max_page);
पूर्णांक rtl8723_fw_मुक्त_to_go(काष्ठा ieee80211_hw *hw, bool is_8723be, पूर्णांक count);
पूर्णांक rtl8723_करोwnload_fw(काष्ठा ieee80211_hw *hw, bool is_8723be, पूर्णांक count);
bool rtl8723_cmd_send_packet(काष्ठा ieee80211_hw *hw,
			     काष्ठा sk_buff *skb);

#पूर्ण_अगर
