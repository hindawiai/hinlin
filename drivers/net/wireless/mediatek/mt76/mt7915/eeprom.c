<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt7915.h"
#समावेश "eeprom.h"

अटल u32 mt7915_eeprom_पढ़ो(काष्ठा mt7915_dev *dev, u32 offset)
अणु
	u8 *data = dev->mt76.eeprom.data;

	अगर (data[offset] == 0xff && !dev->flash_mode)
		mt7915_mcu_get_eeprom(dev, offset);

	वापस data[offset];
पूर्ण

अटल पूर्णांक mt7915_eeprom_load_precal(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt76_dev *mdev = &dev->mt76;
	u32 val;

	val = mt7915_eeprom_पढ़ो(dev, MT_EE_DO_PRE_CAL);
	अगर (val != (MT_EE_WIFI_CAL_DPD | MT_EE_WIFI_CAL_GROUP))
		वापस 0;

	val = MT_EE_CAL_GROUP_SIZE + MT_EE_CAL_DPD_SIZE;
	dev->cal = devm_kzalloc(mdev->dev, val, GFP_KERNEL);
	अगर (!dev->cal)
		वापस -ENOMEM;

	वापस mt76_get_of_eeprom(mdev, dev->cal, MT_EE_PRECAL, val);
पूर्ण

अटल पूर्णांक mt7915_eeprom_load(काष्ठा mt7915_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt76_eeprom_init(&dev->mt76, MT7915_EEPROM_SIZE);
	अगर (ret < 0)
		वापस ret;

	अगर (ret) अणु
		dev->flash_mode = true;
		ret = mt7915_eeprom_load_precal(dev);
	पूर्ण अन्यथा अणु
		स_रखो(dev->mt76.eeprom.data, -1, MT7915_EEPROM_SIZE);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt7915_check_eeprom(काष्ठा mt7915_dev *dev)
अणु
	u8 *eeprom = dev->mt76.eeprom.data;
	u16 val;

	mt7915_eeprom_पढ़ो(dev, MT_EE_CHIP_ID);
	val = get_unaligned_le16(eeprom);

	चयन (val) अणु
	हाल 0x7915:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

व्योम mt7915_eeprom_parse_band_config(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	u32 val;

	val = mt7915_eeprom_पढ़ो(dev, MT_EE_WIFI_CONF + ext_phy);
	val = FIELD_GET(MT_EE_WIFI_CONF0_BAND_SEL, val);
	अगर (val == MT_EE_BAND_SEL_DEFAULT && dev->dbdc_support)
		val = ext_phy ? MT_EE_BAND_SEL_5GHZ : MT_EE_BAND_SEL_2GHZ;

	चयन (val) अणु
	हाल MT_EE_BAND_SEL_5GHZ:
		phy->mt76->cap.has_5ghz = true;
		अवरोध;
	हाल MT_EE_BAND_SEL_2GHZ:
		phy->mt76->cap.has_2ghz = true;
		अवरोध;
	शेष:
		phy->mt76->cap.has_2ghz = true;
		phy->mt76->cap.has_5ghz = true;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mt7915_eeprom_parse_hw_cap(काष्ठा mt7915_dev *dev)
अणु
	u8 nss, nss_band, *eeprom = dev->mt76.eeprom.data;

	mt7915_eeprom_parse_band_config(&dev->phy);

	/* पढ़ो tx mask from eeprom */
	nss = FIELD_GET(MT_EE_WIFI_CONF0_TX_PATH, eeprom[MT_EE_WIFI_CONF]);
	अगर (!nss || nss > 4)
		nss = 4;

	nss_band = nss;

	अगर (dev->dbdc_support) अणु
		nss_band = FIELD_GET(MT_EE_WIFI_CONF3_TX_PATH_B0,
				     eeprom[MT_EE_WIFI_CONF + 3]);
		अगर (!nss_band || nss_band > 2)
			nss_band = 2;

		अगर (nss_band >= nss)
			nss = 4;
	पूर्ण

	dev->chainmask = BIT(nss) - 1;
	dev->mphy.antenna_mask = BIT(nss_band) - 1;
	dev->mphy.chainmask = dev->mphy.antenna_mask;
पूर्ण

पूर्णांक mt7915_eeprom_init(काष्ठा mt7915_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt7915_eeprom_load(dev);
	अगर (ret < 0)
		वापस ret;

	ret = mt7915_check_eeprom(dev);
	अगर (ret)
		वापस ret;

	mt7915_eeprom_parse_hw_cap(dev);
	स_नकल(dev->mphy.macaddr, dev->mt76.eeprom.data + MT_EE_MAC_ADDR,
	       ETH_ALEN);

	mt76_eeprom_override(&dev->mphy);

	वापस 0;
पूर्ण

पूर्णांक mt7915_eeprom_get_target_घातer(काष्ठा mt7915_dev *dev,
				   काष्ठा ieee80211_channel *chan,
				   u8 chain_idx)
अणु
	पूर्णांक index, target_घातer;
	bool tssi_on;

	अगर (chain_idx > 3)
		वापस -EINVAL;

	tssi_on = mt7915_tssi_enabled(dev, chan->band);

	अगर (chan->band == NL80211_BAND_2GHZ) अणु
		index = MT_EE_TX0_POWER_2G + chain_idx * 3;
		target_घातer = mt7915_eeprom_पढ़ो(dev, index);

		अगर (!tssi_on)
			target_घातer += mt7915_eeprom_पढ़ो(dev, index + 1);
	पूर्ण अन्यथा अणु
		पूर्णांक group = mt7915_get_channel_group(chan->hw_value);

		index = MT_EE_TX0_POWER_5G + chain_idx * 12;
		target_घातer = mt7915_eeprom_पढ़ो(dev, index + group);

		अगर (!tssi_on)
			target_घातer += mt7915_eeprom_पढ़ो(dev, index + 8);
	पूर्ण

	वापस target_घातer;
पूर्ण

s8 mt7915_eeprom_get_घातer_delta(काष्ठा mt7915_dev *dev, पूर्णांक band)
अणु
	u32 val;
	s8 delta;

	अगर (band == NL80211_BAND_2GHZ)
		val = mt7915_eeprom_पढ़ो(dev, MT_EE_RATE_DELTA_2G);
	अन्यथा
		val = mt7915_eeprom_पढ़ो(dev, MT_EE_RATE_DELTA_5G);

	अगर (!(val & MT_EE_RATE_DELTA_EN))
		वापस 0;

	delta = FIELD_GET(MT_EE_RATE_DELTA_MASK, val);

	वापस val & MT_EE_RATE_DELTA_SIGN ? delta : -delta;
पूर्ण

स्थिर u8 mt7915_sku_group_len[] = अणु
	[SKU_CCK] = 4,
	[SKU_OFDM] = 8,
	[SKU_HT_BW20] = 8,
	[SKU_HT_BW40] = 9,
	[SKU_VHT_BW20] = 12,
	[SKU_VHT_BW40] = 12,
	[SKU_VHT_BW80] = 12,
	[SKU_VHT_BW160] = 12,
	[SKU_HE_RU26] = 12,
	[SKU_HE_RU52] = 12,
	[SKU_HE_RU106] = 12,
	[SKU_HE_RU242] = 12,
	[SKU_HE_RU484] = 12,
	[SKU_HE_RU996] = 12,
	[SKU_HE_RU2x996] = 12
पूर्ण;
