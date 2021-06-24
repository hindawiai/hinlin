<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "mt76x2.h"
#समावेश "eeprom.h"

#घोषणा EE_FIELD(_name, _value) [MT_EE_##_name] = (_value) | 1

अटल पूर्णांक
mt76x2_eeprom_get_macaddr(काष्ठा mt76x02_dev *dev)
अणु
	व्योम *src = dev->mt76.eeprom.data + MT_EE_MAC_ADDR;

	स_नकल(dev->mphy.macaddr, src, ETH_ALEN);
	वापस 0;
पूर्ण

अटल bool
mt76x2_has_cal_मुक्त_data(काष्ठा mt76x02_dev *dev, u8 *efuse)
अणु
	u16 *efuse_w = (u16 *)efuse;

	अगर (efuse_w[MT_EE_NIC_CONF_0] != 0)
		वापस false;

	अगर (efuse_w[MT_EE_XTAL_TRIM_1] == 0xffff)
		वापस false;

	अगर (efuse_w[MT_EE_TX_POWER_DELTA_BW40] != 0)
		वापस false;

	अगर (efuse_w[MT_EE_TX_POWER_0_START_2G] == 0xffff)
		वापस false;

	अगर (efuse_w[MT_EE_TX_POWER_0_GRP3_TX_POWER_DELTA] != 0)
		वापस false;

	अगर (efuse_w[MT_EE_TX_POWER_0_GRP4_TSSI_SLOPE] == 0xffff)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम
mt76x2_apply_cal_मुक्त_data(काष्ठा mt76x02_dev *dev, u8 *efuse)
अणु
#घोषणा GROUP_5G(_id)							   \
	MT_EE_TX_POWER_0_START_5G + MT_TX_POWER_GROUP_SIZE_5G * (_id),	   \
	MT_EE_TX_POWER_0_START_5G + MT_TX_POWER_GROUP_SIZE_5G * (_id) + 1, \
	MT_EE_TX_POWER_1_START_5G + MT_TX_POWER_GROUP_SIZE_5G * (_id),	   \
	MT_EE_TX_POWER_1_START_5G + MT_TX_POWER_GROUP_SIZE_5G * (_id) + 1

	अटल स्थिर u8 cal_मुक्त_bytes[] = अणु
		MT_EE_XTAL_TRIM_1,
		MT_EE_TX_POWER_EXT_PA_5G + 1,
		MT_EE_TX_POWER_0_START_2G,
		MT_EE_TX_POWER_0_START_2G + 1,
		MT_EE_TX_POWER_1_START_2G,
		MT_EE_TX_POWER_1_START_2G + 1,
		GROUP_5G(0),
		GROUP_5G(1),
		GROUP_5G(2),
		GROUP_5G(3),
		GROUP_5G(4),
		GROUP_5G(5),
		MT_EE_RF_2G_TSSI_OFF_TXPOWER,
		MT_EE_RF_2G_RX_HIGH_GAIN + 1,
		MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN,
		MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN + 1,
		MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN,
		MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN + 1,
		MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN,
		MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN + 1,
	पूर्ण;
	काष्ठा device_node *np = dev->mt76.dev->of_node;
	u8 *eeprom = dev->mt76.eeprom.data;
	u8 prev_grp0[4] = अणु
		eeprom[MT_EE_TX_POWER_0_START_5G],
		eeprom[MT_EE_TX_POWER_0_START_5G + 1],
		eeprom[MT_EE_TX_POWER_1_START_5G],
		eeprom[MT_EE_TX_POWER_1_START_5G + 1]
	पूर्ण;
	u16 val;
	पूर्णांक i;

	अगर (!np || !of_property_पढ़ो_bool(np, "mediatek,eeprom-merge-otp"))
		वापस;

	अगर (!mt76x2_has_cal_मुक्त_data(dev, efuse))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(cal_मुक्त_bytes); i++) अणु
		पूर्णांक offset = cal_मुक्त_bytes[i];

		eeprom[offset] = efuse[offset];
	पूर्ण

	अगर (!(efuse[MT_EE_TX_POWER_0_START_5G] |
	      efuse[MT_EE_TX_POWER_0_START_5G + 1]))
		स_नकल(eeprom + MT_EE_TX_POWER_0_START_5G, prev_grp0, 2);
	अगर (!(efuse[MT_EE_TX_POWER_1_START_5G] |
	      efuse[MT_EE_TX_POWER_1_START_5G + 1]))
		स_नकल(eeprom + MT_EE_TX_POWER_1_START_5G, prev_grp0 + 2, 2);

	val = get_unaligned_le16(efuse + MT_EE_BT_RCAL_RESULT);
	अगर (val != 0xffff)
		eeprom[MT_EE_BT_RCAL_RESULT] = val & 0xff;

	val = get_unaligned_le16(efuse + MT_EE_BT_VCDL_CALIBRATION);
	अगर (val != 0xffff)
		eeprom[MT_EE_BT_VCDL_CALIBRATION + 1] = val >> 8;

	val = get_unaligned_le16(efuse + MT_EE_BT_PMUCFG);
	अगर (val != 0xffff)
		eeprom[MT_EE_BT_PMUCFG] = val & 0xff;
पूर्ण

अटल पूर्णांक mt76x2_check_eeprom(काष्ठा mt76x02_dev *dev)
अणु
	u16 val = get_unaligned_le16(dev->mt76.eeprom.data);

	अगर (!val)
		val = get_unaligned_le16(dev->mt76.eeprom.data + MT_EE_PCI_ID);

	चयन (val) अणु
	हाल 0x7662:
	हाल 0x7612:
		वापस 0;
	शेष:
		dev_err(dev->mt76.dev, "EEPROM data check failed: %04x\n", val);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
mt76x2_eeprom_load(काष्ठा mt76x02_dev *dev)
अणु
	व्योम *efuse;
	bool found;
	पूर्णांक ret;

	ret = mt76_eeprom_init(&dev->mt76, MT7662_EEPROM_SIZE);
	अगर (ret < 0)
		वापस ret;

	found = ret;
	अगर (found)
		found = !mt76x2_check_eeprom(dev);

	dev->mt76.otp.data = devm_kzalloc(dev->mt76.dev, MT7662_EEPROM_SIZE,
					  GFP_KERNEL);
	dev->mt76.otp.size = MT7662_EEPROM_SIZE;
	अगर (!dev->mt76.otp.data)
		वापस -ENOMEM;

	efuse = dev->mt76.otp.data;

	अगर (mt76x02_get_efuse_data(dev, 0, efuse, MT7662_EEPROM_SIZE,
				   MT_EE_READ))
		जाओ out;

	अगर (found) अणु
		mt76x2_apply_cal_मुक्त_data(dev, efuse);
	पूर्ण अन्यथा अणु
		/* FIXME: check अगर efuse data is complete */
		found = true;
		स_नकल(dev->mt76.eeprom.data, efuse, MT7662_EEPROM_SIZE);
	पूर्ण

out:
	अगर (!found)
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल व्योम
mt76x2_set_rx_gain_group(काष्ठा mt76x02_dev *dev, u8 val)
अणु
	s8 *dest = dev->cal.rx.high_gain;

	अगर (!mt76x02_field_valid(val)) अणु
		dest[0] = 0;
		dest[1] = 0;
		वापस;
	पूर्ण

	dest[0] = mt76x02_sign_extend(val, 4);
	dest[1] = mt76x02_sign_extend(val >> 4, 4);
पूर्ण

अटल व्योम
mt76x2_set_rssi_offset(काष्ठा mt76x02_dev *dev, पूर्णांक chain, u8 val)
अणु
	s8 *dest = dev->cal.rx.rssi_offset;

	अगर (!mt76x02_field_valid(val)) अणु
		dest[chain] = 0;
		वापस;
	पूर्ण

	dest[chain] = mt76x02_sign_extend_optional(val, 7);
पूर्ण

अटल क्रमागत mt76x2_cal_channel_group
mt76x2_get_cal_channel_group(पूर्णांक channel)
अणु
	अगर (channel >= 184 && channel <= 196)
		वापस MT_CH_5G_JAPAN;
	अगर (channel <= 48)
		वापस MT_CH_5G_UNII_1;
	अगर (channel <= 64)
		वापस MT_CH_5G_UNII_2;
	अगर (channel <= 114)
		वापस MT_CH_5G_UNII_2E_1;
	अगर (channel <= 144)
		वापस MT_CH_5G_UNII_2E_2;
	वापस MT_CH_5G_UNII_3;
पूर्ण

अटल u8
mt76x2_get_5g_rx_gain(काष्ठा mt76x02_dev *dev, u8 channel)
अणु
	क्रमागत mt76x2_cal_channel_group group;

	group = mt76x2_get_cal_channel_group(channel);
	चयन (group) अणु
	हाल MT_CH_5G_JAPAN:
		वापस mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN);
	हाल MT_CH_5G_UNII_1:
		वापस mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN) >> 8;
	हाल MT_CH_5G_UNII_2:
		वापस mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN);
	हाल MT_CH_5G_UNII_2E_1:
		वापस mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN) >> 8;
	हाल MT_CH_5G_UNII_2E_2:
		वापस mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN);
	शेष:
		वापस mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN) >> 8;
	पूर्ण
पूर्ण

व्योम mt76x2_पढ़ो_rx_gain(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	पूर्णांक channel = chan->hw_value;
	s8 lna_5g[3], lna_2g;
	u8 lna;
	u16 val;

	अगर (chan->band == NL80211_BAND_2GHZ)
		val = mt76x02_eeprom_get(dev, MT_EE_RF_2G_RX_HIGH_GAIN) >> 8;
	अन्यथा
		val = mt76x2_get_5g_rx_gain(dev, channel);

	mt76x2_set_rx_gain_group(dev, val);

	mt76x02_get_rx_gain(dev, chan->band, &val, &lna_2g, lna_5g);
	mt76x2_set_rssi_offset(dev, 0, val);
	mt76x2_set_rssi_offset(dev, 1, val >> 8);

	dev->cal.rx.mcu_gain =  (lna_2g & 0xff);
	dev->cal.rx.mcu_gain |= (lna_5g[0] & 0xff) << 8;
	dev->cal.rx.mcu_gain |= (lna_5g[1] & 0xff) << 16;
	dev->cal.rx.mcu_gain |= (lna_5g[2] & 0xff) << 24;

	lna = mt76x02_get_lna_gain(dev, &lna_2g, lna_5g, chan);
	dev->cal.rx.lna_gain = mt76x02_sign_extend(lna, 8);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_पढ़ो_rx_gain);

व्योम mt76x2_get_rate_घातer(काष्ठा mt76x02_dev *dev, काष्ठा mt76_rate_घातer *t,
			   काष्ठा ieee80211_channel *chan)
अणु
	bool is_5ghz;
	u16 val;

	is_5ghz = chan->band == NL80211_BAND_5GHZ;

	स_रखो(t, 0, माप(*t));

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_CCK);
	t->cck[0] = t->cck[1] = mt76x02_rate_घातer_val(val);
	t->cck[2] = t->cck[3] = mt76x02_rate_घातer_val(val >> 8);

	अगर (is_5ghz)
		val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_OFDM_5G_6M);
	अन्यथा
		val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_OFDM_2G_6M);
	t->ofdm[0] = t->ofdm[1] = mt76x02_rate_घातer_val(val);
	t->ofdm[2] = t->ofdm[3] = mt76x02_rate_घातer_val(val >> 8);

	अगर (is_5ghz)
		val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_OFDM_5G_24M);
	अन्यथा
		val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_OFDM_2G_24M);
	t->ofdm[4] = t->ofdm[5] = mt76x02_rate_घातer_val(val);
	t->ofdm[6] = t->ofdm[7] = mt76x02_rate_घातer_val(val >> 8);

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_HT_MCS0);
	t->ht[0] = t->ht[1] = mt76x02_rate_घातer_val(val);
	t->ht[2] = t->ht[3] = mt76x02_rate_घातer_val(val >> 8);

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_HT_MCS4);
	t->ht[4] = t->ht[5] = mt76x02_rate_घातer_val(val);
	t->ht[6] = t->ht[7] = mt76x02_rate_घातer_val(val >> 8);

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_HT_MCS8);
	t->ht[8] = t->ht[9] = mt76x02_rate_घातer_val(val);
	t->ht[10] = t->ht[11] = mt76x02_rate_घातer_val(val >> 8);

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_HT_MCS12);
	t->ht[12] = t->ht[13] = mt76x02_rate_घातer_val(val);
	t->ht[14] = t->ht[15] = mt76x02_rate_घातer_val(val >> 8);

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_VHT_MCS0);
	t->vht[0] = t->vht[1] = mt76x02_rate_घातer_val(val);
	t->vht[2] = t->vht[3] = mt76x02_rate_घातer_val(val >> 8);

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_VHT_MCS4);
	t->vht[4] = t->vht[5] = mt76x02_rate_घातer_val(val);
	t->vht[6] = t->vht[7] = mt76x02_rate_घातer_val(val >> 8);

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_VHT_MCS8);
	अगर (!is_5ghz)
		val >>= 8;
	t->vht[8] = t->vht[9] = mt76x02_rate_घातer_val(val >> 8);

	स_नकल(t->stbc, t->ht, माप(t->stbc[0]) * 8);
	t->stbc[8] = t->vht[8];
	t->stbc[9] = t->vht[9];
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_get_rate_घातer);

अटल व्योम
mt76x2_get_घातer_info_2g(काष्ठा mt76x02_dev *dev,
			 काष्ठा mt76x2_tx_घातer_info *t,
			 काष्ठा ieee80211_channel *chan,
			 पूर्णांक chain, पूर्णांक offset)
अणु
	पूर्णांक channel = chan->hw_value;
	पूर्णांक delta_idx;
	u8 data[6];
	u16 val;

	अगर (channel < 6)
		delta_idx = 3;
	अन्यथा अगर (channel < 11)
		delta_idx = 4;
	अन्यथा
		delta_idx = 5;

	mt76x02_eeprom_copy(dev, offset, data, माप(data));

	t->chain[chain].tssi_slope = data[0];
	t->chain[chain].tssi_offset = data[1];
	t->chain[chain].target_घातer = data[2];
	t->chain[chain].delta =
		mt76x02_sign_extend_optional(data[delta_idx], 7);

	val = mt76x02_eeprom_get(dev, MT_EE_RF_2G_TSSI_OFF_TXPOWER);
	t->target_घातer = val >> 8;
पूर्ण

अटल व्योम
mt76x2_get_घातer_info_5g(काष्ठा mt76x02_dev *dev,
			 काष्ठा mt76x2_tx_घातer_info *t,
			 काष्ठा ieee80211_channel *chan,
			 पूर्णांक chain, पूर्णांक offset)
अणु
	पूर्णांक channel = chan->hw_value;
	क्रमागत mt76x2_cal_channel_group group;
	पूर्णांक delta_idx;
	u16 val;
	u8 data[5];

	group = mt76x2_get_cal_channel_group(channel);
	offset += group * MT_TX_POWER_GROUP_SIZE_5G;

	अगर (channel >= 192)
		delta_idx = 4;
	अन्यथा अगर (channel >= 184)
		delta_idx = 3;
	अन्यथा अगर (channel < 44)
		delta_idx = 3;
	अन्यथा अगर (channel < 52)
		delta_idx = 4;
	अन्यथा अगर (channel < 58)
		delta_idx = 3;
	अन्यथा अगर (channel < 98)
		delta_idx = 4;
	अन्यथा अगर (channel < 106)
		delta_idx = 3;
	अन्यथा अगर (channel < 116)
		delta_idx = 4;
	अन्यथा अगर (channel < 130)
		delta_idx = 3;
	अन्यथा अगर (channel < 149)
		delta_idx = 4;
	अन्यथा अगर (channel < 157)
		delta_idx = 3;
	अन्यथा
		delta_idx = 4;

	mt76x02_eeprom_copy(dev, offset, data, माप(data));

	t->chain[chain].tssi_slope = data[0];
	t->chain[chain].tssi_offset = data[1];
	t->chain[chain].target_घातer = data[2];
	t->chain[chain].delta =
		mt76x02_sign_extend_optional(data[delta_idx], 7);

	val = mt76x02_eeprom_get(dev, MT_EE_RF_2G_RX_HIGH_GAIN);
	t->target_घातer = val & 0xff;
पूर्ण

व्योम mt76x2_get_घातer_info(काष्ठा mt76x02_dev *dev,
			   काष्ठा mt76x2_tx_घातer_info *t,
			   काष्ठा ieee80211_channel *chan)
अणु
	u16 bw40, bw80;

	स_रखो(t, 0, माप(*t));

	bw40 = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_DELTA_BW40);
	bw80 = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_DELTA_BW80);

	अगर (chan->band == NL80211_BAND_5GHZ) अणु
		bw40 >>= 8;
		mt76x2_get_घातer_info_5g(dev, t, chan, 0,
					 MT_EE_TX_POWER_0_START_5G);
		mt76x2_get_घातer_info_5g(dev, t, chan, 1,
					 MT_EE_TX_POWER_1_START_5G);
	पूर्ण अन्यथा अणु
		mt76x2_get_घातer_info_2g(dev, t, chan, 0,
					 MT_EE_TX_POWER_0_START_2G);
		mt76x2_get_घातer_info_2g(dev, t, chan, 1,
					 MT_EE_TX_POWER_1_START_2G);
	पूर्ण

	अगर (mt76x2_tssi_enabled(dev) ||
	    !mt76x02_field_valid(t->target_घातer))
		t->target_घातer = t->chain[0].target_घातer;

	t->delta_bw40 = mt76x02_rate_घातer_val(bw40);
	t->delta_bw80 = mt76x02_rate_घातer_val(bw80);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_get_घातer_info);

पूर्णांक mt76x2_get_temp_comp(काष्ठा mt76x02_dev *dev, काष्ठा mt76x2_temp_comp *t)
अणु
	क्रमागत nl80211_band band = dev->mphy.chandef.chan->band;
	u16 val, slope;
	u8 bounds;

	स_रखो(t, 0, माप(*t));

	अगर (!mt76x2_temp_tx_alc_enabled(dev))
		वापस -EINVAL;

	अगर (!mt76x02_ext_pa_enabled(dev, band))
		वापस -EINVAL;

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_EXT_PA_5G) >> 8;
	t->temp_25_ref = val & 0x7f;
	अगर (band == NL80211_BAND_5GHZ) अणु
		slope = mt76x02_eeprom_get(dev, MT_EE_RF_TEMP_COMP_SLOPE_5G);
		bounds = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_EXT_PA_5G);
	पूर्ण अन्यथा अणु
		slope = mt76x02_eeprom_get(dev, MT_EE_RF_TEMP_COMP_SLOPE_2G);
		bounds = mt76x02_eeprom_get(dev,
					    MT_EE_TX_POWER_DELTA_BW80) >> 8;
	पूर्ण

	t->high_slope = slope & 0xff;
	t->low_slope = slope >> 8;
	t->lower_bound = 0 - (bounds & 0xf);
	t->upper_bound = (bounds >> 4) & 0xf;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_get_temp_comp);

पूर्णांक mt76x2_eeprom_init(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt76x2_eeprom_load(dev);
	अगर (ret)
		वापस ret;

	mt76x02_eeprom_parse_hw_cap(dev);
	mt76x2_eeprom_get_macaddr(dev);
	mt76_eeprom_override(&dev->mphy);
	dev->mphy.macaddr[0] &= ~BIT(1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_eeprom_init);

MODULE_LICENSE("Dual BSD/GPL");
