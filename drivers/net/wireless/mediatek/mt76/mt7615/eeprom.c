<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 *         Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/of.h>
#समावेश "mt7615.h"
#समावेश "eeprom.h"

अटल पूर्णांक mt7615_efuse_पढ़ो(काष्ठा mt7615_dev *dev, u32 base,
			     u16 addr, u8 *data)
अणु
	u32 val;
	पूर्णांक i;

	val = mt76_rr(dev, base + MT_EFUSE_CTRL);
	val &= ~(MT_EFUSE_CTRL_AIN | MT_EFUSE_CTRL_MODE);
	val |= FIELD_PREP(MT_EFUSE_CTRL_AIN, addr & ~0xf);
	val |= MT_EFUSE_CTRL_KICK;
	mt76_wr(dev, base + MT_EFUSE_CTRL, val);

	अगर (!mt76_poll(dev, base + MT_EFUSE_CTRL, MT_EFUSE_CTRL_KICK, 0, 1000))
		वापस -ETIMEDOUT;

	udelay(2);

	val = mt76_rr(dev, base + MT_EFUSE_CTRL);
	अगर ((val & MT_EFUSE_CTRL_AOUT) == MT_EFUSE_CTRL_AOUT ||
	    WARN_ON_ONCE(!(val & MT_EFUSE_CTRL_VALID))) अणु
		स_रखो(data, 0x0, 16);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		val = mt76_rr(dev, base + MT_EFUSE_RDATA(i));
		put_unaligned_le32(val, data + 4 * i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7615_efuse_init(काष्ठा mt7615_dev *dev, u32 base)
अणु
	पूर्णांक i, len = MT7615_EEPROM_SIZE;
	व्योम *buf;
	u32 val;

	val = mt76_rr(dev, base + MT_EFUSE_BASE_CTRL);
	अगर (val & MT_EFUSE_BASE_CTRL_EMPTY)
		वापस 0;

	dev->mt76.otp.data = devm_kzalloc(dev->mt76.dev, len, GFP_KERNEL);
	dev->mt76.otp.size = len;
	अगर (!dev->mt76.otp.data)
		वापस -ENOMEM;

	buf = dev->mt76.otp.data;
	क्रम (i = 0; i + 16 <= len; i += 16) अणु
		पूर्णांक ret;

		ret = mt7615_efuse_पढ़ो(dev, base, i, buf + i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7615_eeprom_load(काष्ठा mt7615_dev *dev, u32 addr)
अणु
	पूर्णांक ret;

	ret = mt76_eeprom_init(&dev->mt76, MT7615_EEPROM_FULL_SIZE);
	अगर (ret < 0)
		वापस ret;

	वापस mt7615_efuse_init(dev, addr);
पूर्ण

अटल पूर्णांक mt7615_check_eeprom(काष्ठा mt76_dev *dev)
अणु
	u16 val = get_unaligned_le16(dev->eeprom.data);

	चयन (val) अणु
	हाल 0x7615:
	हाल 0x7622:
	हाल 0x7663:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम
mt7615_eeprom_parse_hw_band_cap(काष्ठा mt7615_dev *dev)
अणु
	u8 val, *eeprom = dev->mt76.eeprom.data;

	अगर (is_mt7663(&dev->mt76)) अणु
		/* dual band */
		dev->mphy.cap.has_2ghz = true;
		dev->mphy.cap.has_5ghz = true;
		वापस;
	पूर्ण

	अगर (is_mt7622(&dev->mt76)) अणु
		/* 2GHz only */
		dev->mphy.cap.has_2ghz = true;
		वापस;
	पूर्ण

	अगर (is_mt7611(&dev->mt76)) अणु
		/* 5GHz only */
		dev->mphy.cap.has_5ghz = true;
		वापस;
	पूर्ण

	val = FIELD_GET(MT_EE_NIC_WIFI_CONF_BAND_SEL,
			eeprom[MT_EE_WIFI_CONF]);
	चयन (val) अणु
	हाल MT_EE_5GHZ:
		dev->mphy.cap.has_5ghz = true;
		अवरोध;
	हाल MT_EE_2GHZ:
		dev->mphy.cap.has_2ghz = true;
		अवरोध;
	हाल MT_EE_DBDC:
		dev->dbdc_support = true;
		fallthrough;
	शेष:
		dev->mphy.cap.has_2ghz = true;
		dev->mphy.cap.has_5ghz = true;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mt7615_eeprom_parse_hw_cap(काष्ठा mt7615_dev *dev)
अणु
	u8 *eeprom = dev->mt76.eeprom.data;
	u8 tx_mask, max_nss;

	mt7615_eeprom_parse_hw_band_cap(dev);

	अगर (is_mt7663(&dev->mt76)) अणु
		max_nss = 2;
		tx_mask = FIELD_GET(MT_EE_HW_CONF1_TX_MASK,
				    eeprom[MT7663_EE_HW_CONF1]);
	पूर्ण अन्यथा अणु
		u32 val;

		/* पढ़ो tx-rx mask from eeprom */
		val = mt76_rr(dev, MT_TOP_STRAP_STA);
		max_nss = val & MT_TOP_3NSS ? 3 : 4;

		tx_mask =  FIELD_GET(MT_EE_NIC_CONF_TX_MASK,
				     eeprom[MT_EE_NIC_CONF_0]);
	पूर्ण
	अगर (!tx_mask || tx_mask > max_nss)
		tx_mask = max_nss;

	dev->chainmask = BIT(tx_mask) - 1;
	dev->mphy.antenna_mask = dev->chainmask;
	dev->mphy.chainmask = dev->chainmask;
पूर्ण

अटल पूर्णांक mt7663_eeprom_get_target_घातer_index(काष्ठा mt7615_dev *dev,
						काष्ठा ieee80211_channel *chan,
						u8 chain_idx)
अणु
	पूर्णांक index, group;

	अगर (chain_idx > 1)
		वापस -EINVAL;

	अगर (chan->band == NL80211_BAND_2GHZ)
		वापस MT7663_EE_TX0_2G_TARGET_POWER + (chain_idx << 4);

	group = mt7615_get_channel_group(chan->hw_value);
	अगर (chain_idx == 1)
		index = MT7663_EE_TX1_5G_G0_TARGET_POWER;
	अन्यथा
		index = MT7663_EE_TX0_5G_G0_TARGET_POWER;

	वापस index + group * 3;
पूर्ण

पूर्णांक mt7615_eeprom_get_target_घातer_index(काष्ठा mt7615_dev *dev,
					 काष्ठा ieee80211_channel *chan,
					 u8 chain_idx)
अणु
	पूर्णांक index;

	अगर (is_mt7663(&dev->mt76))
		वापस mt7663_eeprom_get_target_घातer_index(dev, chan,
							    chain_idx);

	अगर (chain_idx > 3)
		वापस -EINVAL;

	/* TSSI disabled */
	अगर (mt7615_ext_pa_enabled(dev, chan->band)) अणु
		अगर (chan->band == NL80211_BAND_2GHZ)
			वापस MT_EE_EXT_PA_2G_TARGET_POWER;
		अन्यथा
			वापस MT_EE_EXT_PA_5G_TARGET_POWER;
	पूर्ण

	/* TSSI enabled */
	अगर (chan->band == NL80211_BAND_2GHZ) अणु
		index = MT_EE_TX0_2G_TARGET_POWER + chain_idx * 6;
	पूर्ण अन्यथा अणु
		पूर्णांक group = mt7615_get_channel_group(chan->hw_value);

		चयन (chain_idx) अणु
		हाल 1:
			index = MT_EE_TX1_5G_G0_TARGET_POWER;
			अवरोध;
		हाल 2:
			index = MT_EE_TX2_5G_G0_TARGET_POWER;
			अवरोध;
		हाल 3:
			index = MT_EE_TX3_5G_G0_TARGET_POWER;
			अवरोध;
		हाल 0:
		शेष:
			index = MT_EE_TX0_5G_G0_TARGET_POWER;
			अवरोध;
		पूर्ण
		index += 5 * group;
	पूर्ण

	वापस index;
पूर्ण

पूर्णांक mt7615_eeprom_get_घातer_delta_index(काष्ठा mt7615_dev *dev,
					क्रमागत nl80211_band band)
अणु
	/* assume the first rate has the highest घातer offset */
	अगर (is_mt7663(&dev->mt76)) अणु
		अगर (band == NL80211_BAND_2GHZ)
			वापस MT_EE_TX0_5G_G0_TARGET_POWER;
		अन्यथा
			वापस MT7663_EE_5G_RATE_POWER;
	पूर्ण

	अगर (band == NL80211_BAND_2GHZ)
		वापस MT_EE_2G_RATE_POWER;
	अन्यथा
		वापस MT_EE_5G_RATE_POWER;
पूर्ण

अटल व्योम mt7615_apply_cal_मुक्त_data(काष्ठा mt7615_dev *dev)
अणु
	अटल स्थिर u16 ical[] = अणु
		0x53, 0x54, 0x55, 0x56, 0x57, 0x5c, 0x5d, 0x62, 0x63, 0x68,
		0x69, 0x6e, 0x6f, 0x73, 0x74, 0x78, 0x79, 0x82, 0x83, 0x87,
		0x88, 0x8c, 0x8d, 0x91, 0x92, 0x96, 0x97, 0x9b, 0x9c, 0xa0,
		0xa1, 0xaa, 0xab, 0xaf, 0xb0, 0xb4, 0xb5, 0xb9, 0xba, 0xf4,
		0xf7, 0xff,
		0x140, 0x141, 0x145, 0x146, 0x14a, 0x14b, 0x154, 0x155, 0x159,
		0x15a, 0x15e, 0x15f, 0x163, 0x164, 0x168, 0x169, 0x16d, 0x16e,
		0x172, 0x173, 0x17c, 0x17d, 0x181, 0x182, 0x186, 0x187, 0x18b,
		0x18c
	पूर्ण;
	अटल स्थिर u16 ical_nocheck[] = अणु
		0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117, 0x118,
		0x1b5, 0x1b6, 0x1b7, 0x3ac, 0x3ad, 0x3ae, 0x3af, 0x3b0, 0x3b1,
		0x3b2
	पूर्ण;
	u8 *eeprom = dev->mt76.eeprom.data;
	u8 *otp = dev->mt76.otp.data;
	पूर्णांक i;

	अगर (!otp)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(ical); i++)
		अगर (!otp[ical[i]])
			वापस;

	क्रम (i = 0; i < ARRAY_SIZE(ical); i++)
		eeprom[ical[i]] = otp[ical[i]];

	क्रम (i = 0; i < ARRAY_SIZE(ical_nocheck); i++)
		eeprom[ical_nocheck[i]] = otp[ical_nocheck[i]];
पूर्ण

अटल व्योम mt7622_apply_cal_मुक्त_data(काष्ठा mt7615_dev *dev)
अणु
	अटल स्थिर u16 ical[] = अणु
		0x53, 0x54, 0x55, 0x56, 0xf4, 0xf7, 0x144, 0x156, 0x15b
	पूर्ण;
	u8 *eeprom = dev->mt76.eeprom.data;
	u8 *otp = dev->mt76.otp.data;
	पूर्णांक i;

	अगर (!otp)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(ical); i++) अणु
		अगर (!otp[ical[i]])
			जारी;

		eeprom[ical[i]] = otp[ical[i]];
	पूर्ण
पूर्ण

अटल व्योम mt7615_cal_मुक्त_data(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा device_node *np = dev->mt76.dev->of_node;

	अगर (!np || !of_property_पढ़ो_bool(np, "mediatek,eeprom-merge-otp"))
		वापस;

	चयन (mt76_chip(&dev->mt76)) अणु
	हाल 0x7622:
		mt7622_apply_cal_मुक्त_data(dev);
		अवरोध;
	हाल 0x7615:
	हाल 0x7611:
		mt7615_apply_cal_मुक्त_data(dev);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक mt7615_eeprom_init(काष्ठा mt7615_dev *dev, u32 addr)
अणु
	पूर्णांक ret;

	ret = mt7615_eeprom_load(dev, addr);
	अगर (ret < 0)
		वापस ret;

	ret = mt7615_check_eeprom(&dev->mt76);
	अगर (ret && dev->mt76.otp.data) अणु
		स_नकल(dev->mt76.eeprom.data, dev->mt76.otp.data,
		       MT7615_EEPROM_SIZE);
	पूर्ण अन्यथा अणु
		dev->flash_eeprom = true;
		mt7615_cal_मुक्त_data(dev);
	पूर्ण

	mt7615_eeprom_parse_hw_cap(dev);
	स_नकल(dev->mphy.macaddr, dev->mt76.eeprom.data + MT_EE_MAC_ADDR,
	       ETH_ALEN);

	mt76_eeprom_override(&dev->mphy);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_eeprom_init);
