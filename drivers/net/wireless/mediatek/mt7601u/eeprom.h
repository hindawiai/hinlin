<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#अगर_अघोषित __MT7601U_EEPROM_H
#घोषणा __MT7601U_EEPROM_H

काष्ठा mt7601u_dev;

#घोषणा MT7601U_EE_MAX_VER			0x0d
#घोषणा MT7601U_EEPROM_SIZE			256

#घोषणा MT7601U_DEFAULT_TX_POWER		6

क्रमागत mt76_eeprom_field अणु
	MT_EE_CHIP_ID =				0x00,
	MT_EE_VERSION_FAE =			0x02,
	MT_EE_VERSION_EE =			0x03,
	MT_EE_MAC_ADDR =			0x04,
	MT_EE_NIC_CONF_0 =			0x34,
	MT_EE_NIC_CONF_1 =			0x36,
	MT_EE_COUNTRY_REGION =			0x39,
	MT_EE_FREQ_OFFSET =			0x3a,
	MT_EE_NIC_CONF_2 =			0x42,

	MT_EE_LNA_GAIN =			0x44,
	MT_EE_RSSI_OFFSET =			0x46,

	MT_EE_TX_POWER_DELTA_BW40 =		0x50,
	MT_EE_TX_POWER_OFFSET =			0x52,

	MT_EE_TX_TSSI_SLOPE =			0x6e,
	MT_EE_TX_TSSI_OFFSET_GROUP =		0x6f,
	MT_EE_TX_TSSI_OFFSET =			0x76,

	MT_EE_TX_TSSI_TARGET_POWER =		0xd0,
	MT_EE_REF_TEMP =			0xd1,
	MT_EE_FREQ_OFFSET_COMPENSATION =	0xdb,
	MT_EE_TX_POWER_BYRATE_BASE =		0xde,

	MT_EE_USAGE_MAP_START =			0x1e0,
	MT_EE_USAGE_MAP_END =			0x1fc,
पूर्ण;

#घोषणा MT_EE_NIC_CONF_0_RX_PATH		GENMASK(3, 0)
#घोषणा MT_EE_NIC_CONF_0_TX_PATH		GENMASK(7, 4)
#घोषणा MT_EE_NIC_CONF_0_BOARD_TYPE		GENMASK(13, 12)

#घोषणा MT_EE_NIC_CONF_1_HW_RF_CTRL		BIT(0)
#घोषणा MT_EE_NIC_CONF_1_TEMP_TX_ALC		BIT(1)
#घोषणा MT_EE_NIC_CONF_1_LNA_EXT_2G		BIT(2)
#घोषणा MT_EE_NIC_CONF_1_LNA_EXT_5G		BIT(3)
#घोषणा MT_EE_NIC_CONF_1_TX_ALC_EN		BIT(13)

#घोषणा MT_EE_NIC_CONF_2_RX_STREAM		GENMASK(3, 0)
#घोषणा MT_EE_NIC_CONF_2_TX_STREAM		GENMASK(7, 4)
#घोषणा MT_EE_NIC_CONF_2_HW_ANTDIV		BIT(8)
#घोषणा MT_EE_NIC_CONF_2_XTAL_OPTION		GENMASK(10, 9)
#घोषणा MT_EE_NIC_CONF_2_TEMP_DISABLE		BIT(11)
#घोषणा MT_EE_NIC_CONF_2_COEX_METHOD		GENMASK(15, 13)

#घोषणा MT_EE_TX_POWER_BYRATE(i)		(MT_EE_TX_POWER_BYRATE_BASE + \
						 (i) * 4)

#घोषणा MT_EFUSE_USAGE_MAP_SIZE			(MT_EE_USAGE_MAP_END -	\
						 MT_EE_USAGE_MAP_START + 1)

क्रमागत mt7601u_eeprom_access_modes अणु
	MT_EE_READ = 0,
	MT_EE_PHYSICAL_READ = 1,
पूर्ण;

काष्ठा घातer_per_rate  अणु
	u8 raw;  /* validated s6 value */
	s8 bw20; /* sign-extended पूर्णांक */
	s8 bw40; /* sign-extended पूर्णांक */
पूर्ण;

/* Power per rate - one value per two rates */
काष्ठा mt7601u_rate_घातer अणु
	काष्ठा घातer_per_rate cck[2];
	काष्ठा घातer_per_rate ofdm[4];
	काष्ठा घातer_per_rate ht[4];
पूर्ण;

काष्ठा reg_channel_bounds अणु
	u8 start;
	u8 num;
पूर्ण;

काष्ठा mt7601u_eeprom_params अणु
	bool tssi_enabled;
	u8 rf_freq_off;
	s8 rssi_offset[2];
	s8 ref_temp;
	s8 lna_gain;

	u8 chan_pwr[14];
	काष्ठा mt7601u_rate_घातer घातer_rate_table;
	s8 real_cck_bw20[2];

	/* TSSI stuff - only with पूर्णांकernal TX ALC */
	काष्ठा tssi_data अणु
		पूर्णांक tx0_delta_offset;
		u8 slope;
		u8 offset[3];
	पूर्ण tssi_data;

	काष्ठा reg_channel_bounds reg;
पूर्ण;

पूर्णांक mt7601u_eeprom_init(काष्ठा mt7601u_dev *dev);

अटल अंतरभूत u32 s6_validate(u32 reg)
अणु
	WARN_ON(reg & ~GENMASK(5, 0));
	वापस reg & GENMASK(5, 0);
पूर्ण

अटल अंतरभूत पूर्णांक s6_to_पूर्णांक(u32 reg)
अणु
	पूर्णांक s6;

	s6 = s6_validate(reg);
	अगर (s6 & BIT(5))
		s6 -= BIT(6);

	वापस s6;
पूर्ण

अटल अंतरभूत u32 पूर्णांक_to_s6(पूर्णांक val)
अणु
	अगर (val < -0x20)
		वापस 0x20;
	अगर (val > 0x1f)
		वापस 0x1f;

	वापस val & 0x3f;
पूर्ण

#पूर्ण_अगर
