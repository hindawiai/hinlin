<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>

#समावेश "mt76x02_eeprom.h"

अटल पूर्णांक
mt76x02_efuse_पढ़ो(काष्ठा mt76x02_dev *dev, u16 addr, u8 *data,
		   क्रमागत mt76x02_eeprom_modes mode)
अणु
	u32 val;
	पूर्णांक i;

	val = mt76_rr(dev, MT_EFUSE_CTRL);
	val &= ~(MT_EFUSE_CTRL_AIN |
		 MT_EFUSE_CTRL_MODE);
	val |= FIELD_PREP(MT_EFUSE_CTRL_AIN, addr & ~0xf);
	val |= FIELD_PREP(MT_EFUSE_CTRL_MODE, mode);
	val |= MT_EFUSE_CTRL_KICK;
	mt76_wr(dev, MT_EFUSE_CTRL, val);

	अगर (!mt76_poll_msec(dev, MT_EFUSE_CTRL, MT_EFUSE_CTRL_KICK, 0, 1000))
		वापस -ETIMEDOUT;

	udelay(2);

	val = mt76_rr(dev, MT_EFUSE_CTRL);
	अगर ((val & MT_EFUSE_CTRL_AOUT) == MT_EFUSE_CTRL_AOUT) अणु
		स_रखो(data, 0xff, 16);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		val = mt76_rr(dev, MT_EFUSE_DATA(i));
		put_unaligned_le32(val, data + 4 * i);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mt76x02_eeprom_copy(काष्ठा mt76x02_dev *dev,
			क्रमागत mt76x02_eeprom_field field,
			व्योम *dest, पूर्णांक len)
अणु
	अगर (field + len > dev->mt76.eeprom.size)
		वापस -1;

	स_नकल(dest, dev->mt76.eeprom.data + field, len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_eeprom_copy);

पूर्णांक mt76x02_get_efuse_data(काष्ठा mt76x02_dev *dev, u16 base, व्योम *buf,
			   पूर्णांक len, क्रमागत mt76x02_eeprom_modes mode)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i + 16 <= len; i += 16) अणु
		ret = mt76x02_efuse_पढ़ो(dev, base + i, buf + i, mode);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_get_efuse_data);

व्योम mt76x02_eeprom_parse_hw_cap(काष्ठा mt76x02_dev *dev)
अणु
	u16 val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_0);

	चयन (FIELD_GET(MT_EE_NIC_CONF_0_BOARD_TYPE, val)) अणु
	हाल BOARD_TYPE_5GHZ:
		dev->mphy.cap.has_5ghz = true;
		अवरोध;
	हाल BOARD_TYPE_2GHZ:
		dev->mphy.cap.has_2ghz = true;
		अवरोध;
	शेष:
		dev->mphy.cap.has_2ghz = true;
		dev->mphy.cap.has_5ghz = true;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_eeprom_parse_hw_cap);

bool mt76x02_ext_pa_enabled(काष्ठा mt76x02_dev *dev, क्रमागत nl80211_band band)
अणु
	u16 conf0 = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_0);

	अगर (band == NL80211_BAND_5GHZ)
		वापस !(conf0 & MT_EE_NIC_CONF_0_PA_INT_5G);
	अन्यथा
		वापस !(conf0 & MT_EE_NIC_CONF_0_PA_INT_2G);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_ext_pa_enabled);

व्योम mt76x02_get_rx_gain(काष्ठा mt76x02_dev *dev, क्रमागत nl80211_band band,
			 u16 *rssi_offset, s8 *lna_2g, s8 *lna_5g)
अणु
	u16 val;

	val = mt76x02_eeprom_get(dev, MT_EE_LNA_GAIN);
	*lna_2g = val & 0xff;
	lna_5g[0] = val >> 8;

	val = mt76x02_eeprom_get(dev, MT_EE_RSSI_OFFSET_2G_1);
	lna_5g[1] = val >> 8;

	val = mt76x02_eeprom_get(dev, MT_EE_RSSI_OFFSET_5G_1);
	lna_5g[2] = val >> 8;

	अगर (!mt76x02_field_valid(lna_5g[1]))
		lna_5g[1] = lna_5g[0];

	अगर (!mt76x02_field_valid(lna_5g[2]))
		lna_5g[2] = lna_5g[0];

	अगर (band == NL80211_BAND_2GHZ)
		*rssi_offset = mt76x02_eeprom_get(dev, MT_EE_RSSI_OFFSET_2G_0);
	अन्यथा
		*rssi_offset = mt76x02_eeprom_get(dev, MT_EE_RSSI_OFFSET_5G_0);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_get_rx_gain);

u8 mt76x02_get_lna_gain(काष्ठा mt76x02_dev *dev,
			s8 *lna_2g, s8 *lna_5g,
			काष्ठा ieee80211_channel *chan)
अणु
	u16 val;
	u8 lna;

	val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1);
	अगर (val & MT_EE_NIC_CONF_1_LNA_EXT_2G)
		*lna_2g = 0;
	अगर (val & MT_EE_NIC_CONF_1_LNA_EXT_5G)
		स_रखो(lna_5g, 0, माप(s8) * 3);

	अगर (chan->band == NL80211_BAND_2GHZ)
		lna = *lna_2g;
	अन्यथा अगर (chan->hw_value <= 64)
		lna = lna_5g[0];
	अन्यथा अगर (chan->hw_value <= 128)
		lna = lna_5g[1];
	अन्यथा
		lna = lna_5g[2];

	वापस lna != 0xff ? lna : 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_get_lna_gain);
