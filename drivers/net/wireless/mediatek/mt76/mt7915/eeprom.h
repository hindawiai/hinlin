<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (C) 2020 MediaTek Inc. */

#अगर_अघोषित __MT7915_EEPROM_H
#घोषणा __MT7915_EEPROM_H

#समावेश "mt7915.h"

काष्ठा cal_data अणु
	u8 count;
	u16 offset[60];
पूर्ण;

क्रमागत mt7915_eeprom_field अणु
	MT_EE_CHIP_ID =		0x000,
	MT_EE_VERSION =		0x002,
	MT_EE_MAC_ADDR =	0x004,
	MT_EE_MAC_ADDR2 =	0x00a,
	MT_EE_DDIE_FT_VERSION =	0x050,
	MT_EE_DO_PRE_CAL =	0x062,
	MT_EE_WIFI_CONF =	0x190,
	MT_EE_RATE_DELTA_2G =	0x252,
	MT_EE_RATE_DELTA_5G =	0x29d,
	MT_EE_TX0_POWER_2G =	0x2fc,
	MT_EE_TX0_POWER_5G =	0x34b,
	MT_EE_ADIE_FT_VERSION =	0x9a0,

	__MT_EE_MAX =		0xe00,
	/* 0xe10 ~ 0x5780 used to save group cal data */
	MT_EE_PRECAL =		0xe10
पूर्ण;

#घोषणा MT_EE_WIFI_CAL_GROUP			BIT(0)
#घोषणा MT_EE_WIFI_CAL_DPD			GENMASK(2, 1)
#घोषणा MT_EE_CAL_UNIT				1024
#घोषणा MT_EE_CAL_GROUP_SIZE			(44 * MT_EE_CAL_UNIT)
#घोषणा MT_EE_CAL_DPD_SIZE			(54 * MT_EE_CAL_UNIT)

#घोषणा MT_EE_WIFI_CONF0_TX_PATH		GENMASK(2, 0)
#घोषणा MT_EE_WIFI_CONF0_BAND_SEL		GENMASK(7, 6)
#घोषणा MT_EE_WIFI_CONF1_BAND_SEL		GENMASK(7, 6)
#घोषणा MT_EE_WIFI_CONF3_TX_PATH_B0		GENMASK(1, 0)
#घोषणा MT_EE_WIFI_CONF3_TX_PATH_B1		GENMASK(5, 4)
#घोषणा MT_EE_WIFI_CONF7_TSSI0_2G		BIT(0)
#घोषणा MT_EE_WIFI_CONF7_TSSI0_5G		BIT(2)
#घोषणा MT_EE_WIFI_CONF7_TSSI1_5G		BIT(4)

#घोषणा MT_EE_RATE_DELTA_MASK			GENMASK(5, 0)
#घोषणा MT_EE_RATE_DELTA_SIGN			BIT(6)
#घोषणा MT_EE_RATE_DELTA_EN			BIT(7)

क्रमागत mt7915_eeprom_band अणु
	MT_EE_BAND_SEL_DEFAULT,
	MT_EE_BAND_SEL_5GHZ,
	MT_EE_BAND_SEL_2GHZ,
	MT_EE_BAND_SEL_DUAL,
पूर्ण;

क्रमागत mt7915_sku_rate_group अणु
	SKU_CCK,
	SKU_OFDM,
	SKU_HT_BW20,
	SKU_HT_BW40,
	SKU_VHT_BW20,
	SKU_VHT_BW40,
	SKU_VHT_BW80,
	SKU_VHT_BW160,
	SKU_HE_RU26,
	SKU_HE_RU52,
	SKU_HE_RU106,
	SKU_HE_RU242,
	SKU_HE_RU484,
	SKU_HE_RU996,
	SKU_HE_RU2x996,
	MAX_SKU_RATE_GROUP_NUM,
पूर्ण;

अटल अंतरभूत पूर्णांक
mt7915_get_channel_group(पूर्णांक channel)
अणु
	अगर (channel >= 184 && channel <= 196)
		वापस 0;
	अगर (channel <= 48)
		वापस 1;
	अगर (channel <= 64)
		वापस 2;
	अगर (channel <= 96)
		वापस 3;
	अगर (channel <= 112)
		वापस 4;
	अगर (channel <= 128)
		वापस 5;
	अगर (channel <= 144)
		वापस 6;
	वापस 7;
पूर्ण

अटल अंतरभूत bool
mt7915_tssi_enabled(काष्ठा mt7915_dev *dev, क्रमागत nl80211_band band)
अणु
	u8 *eep = dev->mt76.eeprom.data;

	/* TODO: DBDC */
	अगर (band == NL80211_BAND_5GHZ)
		वापस eep[MT_EE_WIFI_CONF + 7] & MT_EE_WIFI_CONF7_TSSI0_5G;
	अन्यथा
		वापस eep[MT_EE_WIFI_CONF + 7] & MT_EE_WIFI_CONF7_TSSI0_2G;
पूर्ण

बाह्य स्थिर u8 mt7915_sku_group_len[MAX_SKU_RATE_GROUP_NUM];

#पूर्ण_अगर
