<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_EFUSE_H_
#घोषणा __RTL_EFUSE_H_

#घोषणा EFUSE_IC_ID_OFFSET		506

#घोषणा EFUSE_MAX_WORD_UNIT		4

#घोषणा EFUSE_INIT_MAP			0
#घोषणा EFUSE_MODIFY_MAP		1

#घोषणा PG_STATE_HEADER			0x01
#घोषणा PG_STATE_WORD_0			0x02
#घोषणा PG_STATE_WORD_1			0x04
#घोषणा PG_STATE_WORD_2			0x08
#घोषणा PG_STATE_WORD_3			0x10
#घोषणा PG_STATE_DATA			0x20

#घोषणा EFUSE_REPEAT_THRESHOLD_		3
#घोषणा EFUSE_ERROE_HANDLE		1

काष्ठा efuse_map अणु
	u8 offset;
	u8 word_start;
	u8 byte_start;
	u8 byte_cnts;
पूर्ण;

काष्ठा pgpkt_काष्ठा अणु
	u8 offset;
	u8 word_en;
	u8 data[8];
पूर्ण;

क्रमागत efuse_data_item अणु
	EFUSE_CHIP_ID = 0,
	EFUSE_LDO_SETTING,
	EFUSE_CLK_SETTING,
	EFUSE_SDIO_SETTING,
	EFUSE_CCCR,
	EFUSE_SDIO_MODE,
	EFUSE_OCR,
	EFUSE_F0CIS,
	EFUSE_F1CIS,
	EFUSE_MAC_ADDR,
	EFUSE_EEPROM_VER,
	EFUSE_CHAN_PLAN,
	EFUSE_TXPW_TAB
पूर्ण;

क्रमागत अणु
	VOLTAGE_V25 = 0x03,
	LDOE25_SHIFT = 28,
पूर्ण;

काष्ठा efuse_priv अणु
	u8 id[2];
	u8 lकरो_setting[2];
	u8 clk_setting[2];
	u8 cccr;
	u8 sdio_mode;
	u8 ocr[3];
	u8 cis0[17];
	u8 cis1[48];
	u8 mac_addr[6];
	u8 eeprom_verno;
	u8 channel_plan;
	u8 tx_घातer_b[14];
	u8 tx_घातer_g[14];
पूर्ण;

व्योम पढ़ो_efuse_byte(काष्ठा ieee80211_hw *hw, u16 _offset, u8 *pbuf);
व्योम efuse_initialize(काष्ठा ieee80211_hw *hw);
u8 efuse_पढ़ो_1byte(काष्ठा ieee80211_hw *hw, u16 address);
पूर्णांक efuse_one_byte_पढ़ो(काष्ठा ieee80211_hw *hw, u16 addr, u8 *data);
व्योम efuse_ग_लिखो_1byte(काष्ठा ieee80211_hw *hw, u16 address, u8 value);
व्योम पढ़ो_efuse(काष्ठा ieee80211_hw *hw, u16 _offset,
		u16 _size_byte, u8 *pbuf);
व्योम efuse_shaकरोw_पढ़ो(काष्ठा ieee80211_hw *hw, u8 type,
		       u16 offset, u32 *value);
व्योम efuse_shaकरोw_ग_लिखो(काष्ठा ieee80211_hw *hw, u8 type,
			u16 offset, u32 value);
bool efuse_shaकरोw_update(काष्ठा ieee80211_hw *hw);
bool efuse_shaकरोw_update_chk(काष्ठा ieee80211_hw *hw);
व्योम rtl_efuse_shaकरोw_map_update(काष्ठा ieee80211_hw *hw);
व्योम efuse_क्रमce_ग_लिखो_venकरोr_id(काष्ठा ieee80211_hw *hw);
व्योम efuse_re_pg_section(काष्ठा ieee80211_hw *hw, u8 section_idx);
व्योम efuse_घातer_चयन(काष्ठा ieee80211_hw *hw, u8 ग_लिखो, u8 pwrstate);
पूर्णांक rtl_get_hwinfo(काष्ठा ieee80211_hw *hw, काष्ठा rtl_priv *rtlpriv,
		   पूर्णांक max_size, u8 *hwinfo, पूर्णांक *params);
व्योम rtl_fill_dummy(u8 *pfwbuf, u32 *pfwlen);
व्योम rtl_fw_page_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 page, स्थिर u8 *buffer,
		       u32 size);
व्योम rtl_fw_block_ग_लिखो(काष्ठा ieee80211_hw *hw, स्थिर u8 *buffer, u32 size);
व्योम rtl_efuse_ops_init(काष्ठा ieee80211_hw *hw);
#पूर्ण_अगर
