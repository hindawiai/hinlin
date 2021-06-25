<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (C) 2019 MediaTek Inc. */

#अगर_अघोषित __MT7615_EEPROM_H
#घोषणा __MT7615_EEPROM_H

#समावेश "mt7615.h"


#घोषणा MT7615_EEPROM_DCOC_OFFSET		MT7615_EEPROM_SIZE
#घोषणा MT7615_EEPROM_DCOC_SIZE			256
#घोषणा MT7615_EEPROM_DCOC_COUNT		34

#घोषणा MT7615_EEPROM_TXDPD_OFFSET		(MT7615_EEPROM_SIZE + \
						 MT7615_EEPROM_DCOC_COUNT * \
						 MT7615_EEPROM_DCOC_SIZE)
#घोषणा MT7615_EEPROM_TXDPD_SIZE		216
#घोषणा MT7615_EEPROM_TXDPD_COUNT		(44 + 3)

#घोषणा MT7615_EEPROM_FULL_SIZE			(MT7615_EEPROM_TXDPD_OFFSET + \
						 MT7615_EEPROM_TXDPD_COUNT * \
						 MT7615_EEPROM_TXDPD_SIZE)

क्रमागत mt7615_eeprom_field अणु
	MT_EE_CHIP_ID =				0x000,
	MT_EE_VERSION =				0x002,
	MT_EE_MAC_ADDR =			0x004,
	MT_EE_NIC_CONF_0 =			0x034,
	MT_EE_NIC_CONF_1 =			0x036,
	MT_EE_WIFI_CONF =			0x03e,
	MT_EE_CALDATA_FLASH =			0x052,
	MT_EE_TX0_2G_TARGET_POWER =		0x058,
	MT_EE_TX0_5G_G0_TARGET_POWER =		0x070,
	MT7663_EE_5G_RATE_POWER =		0x089,
	MT_EE_TX1_5G_G0_TARGET_POWER =		0x098,
	MT_EE_2G_RATE_POWER =			0x0be,
	MT_EE_5G_RATE_POWER =			0x0d5,
	MT7663_EE_TX0_2G_TARGET_POWER =		0x0e3,
	MT_EE_EXT_PA_2G_TARGET_POWER =		0x0f2,
	MT_EE_EXT_PA_5G_TARGET_POWER =		0x0f3,
	MT_EE_TX2_5G_G0_TARGET_POWER =		0x142,
	MT_EE_TX3_5G_G0_TARGET_POWER =		0x16a,
	MT7663_EE_HW_CONF1 =			0x1b0,
	MT7663_EE_TX0_5G_G0_TARGET_POWER =	0x245,
	MT7663_EE_TX1_5G_G0_TARGET_POWER =	0x2b5,

	MT7615_EE_MAX =				0x3bf,
	MT7622_EE_MAX =				0x3db,
	MT7663_EE_MAX =				0x400,
पूर्ण;

#घोषणा MT_EE_RATE_POWER_MASK			GENMASK(5, 0)
#घोषणा MT_EE_RATE_POWER_SIGN			BIT(6)
#घोषणा MT_EE_RATE_POWER_EN			BIT(7)

#घोषणा MT_EE_CALDATA_FLASH_TX_DPD		BIT(0)
#घोषणा MT_EE_CALDATA_FLASH_RX_CAL		BIT(1)

#घोषणा MT_EE_NIC_CONF_TX_MASK			GENMASK(7, 4)
#घोषणा MT_EE_NIC_CONF_RX_MASK			GENMASK(3, 0)

#घोषणा MT_EE_HW_CONF1_TX_MASK			GENMASK(2, 0)

#घोषणा MT_EE_NIC_CONF_TSSI_2G			BIT(5)
#घोषणा MT_EE_NIC_CONF_TSSI_5G			BIT(6)

#घोषणा MT_EE_NIC_WIFI_CONF_BAND_SEL		GENMASK(5, 4)
क्रमागत mt7615_eeprom_band अणु
	MT_EE_DUAL_BAND,
	MT_EE_5GHZ,
	MT_EE_2GHZ,
	MT_EE_DBDC,
पूर्ण;

क्रमागत mt7615_channel_group अणु
	MT_CH_5G_JAPAN,
	MT_CH_5G_UNII_1,
	MT_CH_5G_UNII_2A,
	MT_CH_5G_UNII_2B,
	MT_CH_5G_UNII_2E_1,
	MT_CH_5G_UNII_2E_2,
	MT_CH_5G_UNII_2E_3,
	MT_CH_5G_UNII_3,
	__MT_CH_MAX
पूर्ण;

अटल अंतरभूत क्रमागत mt7615_channel_group
mt7615_get_channel_group(पूर्णांक channel)
अणु
	अगर (channel >= 184 && channel <= 196)
		वापस MT_CH_5G_JAPAN;
	अगर (channel <= 48)
		वापस MT_CH_5G_UNII_1;
	अगर (channel <= 64)
		वापस MT_CH_5G_UNII_2A;
	अगर (channel <= 114)
		वापस MT_CH_5G_UNII_2E_1;
	अगर (channel <= 144)
		वापस MT_CH_5G_UNII_2E_2;
	अगर (channel <= 161)
		वापस MT_CH_5G_UNII_2E_3;
	वापस MT_CH_5G_UNII_3;
पूर्ण

अटल अंतरभूत bool
mt7615_ext_pa_enabled(काष्ठा mt7615_dev *dev, क्रमागत nl80211_band band)
अणु
	u8 *eep = dev->mt76.eeprom.data;

	अगर (band == NL80211_BAND_5GHZ)
		वापस !(eep[MT_EE_NIC_CONF_1 + 1] & MT_EE_NIC_CONF_TSSI_5G);
	अन्यथा
		वापस !(eep[MT_EE_NIC_CONF_1 + 1] & MT_EE_NIC_CONF_TSSI_2G);
पूर्ण

#पूर्ण_अगर
