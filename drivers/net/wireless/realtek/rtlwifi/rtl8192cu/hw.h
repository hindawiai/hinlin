<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92CU_HW_H__
#घोषणा __RTL92CU_HW_H__

#घोषणा H2C_RA_MASK	6

#घोषणा LLT_LAST_ENTRY_OF_TX_PKT_BUFFER		255

#घोषणा RX_PAGE_SIZE_REG_VALUE			PBP_128
/* Note: We will भागide number of page equally क्रम each queue
 * other than खुला queue! */
#घोषणा TX_TOTAL_PAGE_NUMBER			0xF8
#घोषणा TX_PAGE_BOUNDARY			(TX_TOTAL_PAGE_NUMBER + 1)

#घोषणा CHIP_B_PAGE_NUM_PUBQ			0xE7

/* For Test Chip Setting
 * (HPQ + LPQ + PUBQ) shall be TX_TOTAL_PAGE_NUMBER */
#घोषणा CHIP_A_PAGE_NUM_PUBQ			0x7E

/* For Chip A Setting */
#घोषणा WMM_CHIP_A_TX_TOTAL_PAGE_NUMBER		0xF5
#घोषणा WMM_CHIP_A_TX_PAGE_BOUNDARY		\
	(WMM_CHIP_A_TX_TOTAL_PAGE_NUMBER + 1) /* F6 */

#घोषणा WMM_CHIP_A_PAGE_NUM_PUBQ		0xA3
#घोषणा WMM_CHIP_A_PAGE_NUM_HPQ			0x29
#घोषणा WMM_CHIP_A_PAGE_NUM_LPQ			0x29

/* Note: For Chip B Setting ,modअगरy later */
#घोषणा WMM_CHIP_B_TX_TOTAL_PAGE_NUMBER		0xF5
#घोषणा WMM_CHIP_B_TX_PAGE_BOUNDARY		\
	(WMM_CHIP_B_TX_TOTAL_PAGE_NUMBER + 1) /* F6 */

#घोषणा WMM_CHIP_B_PAGE_NUM_PUBQ		0xB0
#घोषणा WMM_CHIP_B_PAGE_NUM_HPQ			0x29
#घोषणा WMM_CHIP_B_PAGE_NUM_LPQ			0x1C
#घोषणा WMM_CHIP_B_PAGE_NUM_NPQ			0x1C

#घोषणा BOARD_TYPE_NORMAL_MASK			0xE0
#घोषणा BOARD_TYPE_TEST_MASK			0x0F

/* should be नामd and moved to another file */
क्रमागत _BOARD_TYPE_8192CUSB अणु
	BOARD_USB_DONGLE		= 0,	/* USB करोngle */
	BOARD_USB_HIGH_PA		= 1,	/* USB करोngle - high घातer PA */
	BOARD_MINICARD			= 2,	/* Minicard */
	BOARD_USB_SOLO			= 3,	/* USB solo-Slim module */
	BOARD_USB_COMBO			= 4,	/* USB Combo-Slim module */
पूर्ण;

#घोषणा IS_HIGHT_PA(boardtype)		\
	((boardtype == BOARD_USB_HIGH_PA) ? true : false)

#घोषणा RTL92C_DRIVER_INFO_SIZE				4
व्योम rtl92cu_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw);
व्योम rtl92cu_enable_hw_security_config(काष्ठा ieee80211_hw *hw);
पूर्णांक rtl92cu_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92cu_card_disable(काष्ठा ieee80211_hw *hw);
पूर्णांक rtl92cu_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type);
व्योम rtl92cu_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw);
व्योम rtl92cu_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw);
व्योम rtl92cu_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
				   u32 add_msr, u32 rm_msr);
व्योम rtl92cu_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
व्योम rtl92cu_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);

व्योम rtl92cu_update_channel_access_setting(काष्ठा ieee80211_hw *hw);
bool rtl92cu_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 * valid);
व्योम rtl92cu_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid);
पूर्णांक rtl92c_करोwnload_fw(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_set_fw_pwrmode_cmd(काष्ठा ieee80211_hw *hw, u8 mode);
व्योम rtl92c_set_fw_joinbss_report_cmd(काष्ठा ieee80211_hw *hw, u8 mstatus);
व्योम rtl92c_fill_h2c_cmd(काष्ठा ieee80211_hw *hw,
			 u8 element_id, u32 cmd_len, u8 *p_cmdbuffer);
bool rtl92cu_phy_mac_config(काष्ठा ieee80211_hw *hw);
व्योम rtl92cu_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_sta *sta,
				 u8 rssi_level, bool update_bw);

#पूर्ण_अगर
