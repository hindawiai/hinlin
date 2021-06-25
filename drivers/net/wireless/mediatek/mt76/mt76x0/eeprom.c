<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "mt76x0.h"
#समावेश "eeprom.h"
#समावेश "../mt76x02_phy.h"

#घोषणा MT_MAP_READS	DIV_ROUND_UP(MT_EFUSE_USAGE_MAP_SIZE, 16)
अटल पूर्णांक
mt76x0_efuse_physical_size_check(काष्ठा mt76x02_dev *dev)
अणु
	u8 data[MT_MAP_READS * 16];
	पूर्णांक ret, i;
	u32 start = 0, end = 0, cnt_मुक्त;

	ret = mt76x02_get_efuse_data(dev, MT_EE_USAGE_MAP_START, data,
				     माप(data), MT_EE_PHYSICAL_READ);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < MT_EFUSE_USAGE_MAP_SIZE; i++)
		अगर (!data[i]) अणु
			अगर (!start)
				start = MT_EE_USAGE_MAP_START + i;
			end = MT_EE_USAGE_MAP_START + i;
		पूर्ण
	cnt_मुक्त = end - start + 1;

	अगर (MT_EFUSE_USAGE_MAP_SIZE - cnt_मुक्त < 5) अणु
		dev_err(dev->mt76.dev,
			"driver does not support default EEPROM\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt76x0_set_chip_cap(काष्ठा mt76x02_dev *dev)
अणु
	u16 nic_conf0 = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_0);
	u16 nic_conf1 = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1);

	mt76x02_eeprom_parse_hw_cap(dev);
	dev_dbg(dev->mt76.dev, "2GHz %d 5GHz %d\n",
		dev->mphy.cap.has_2ghz, dev->mphy.cap.has_5ghz);

	अगर (dev->no_2ghz) अणु
		dev->mphy.cap.has_2ghz = false;
		dev_dbg(dev->mt76.dev, "mask out 2GHz support\n");
	पूर्ण

	अगर (is_mt7630(dev)) अणु
		dev->mphy.cap.has_5ghz = false;
		dev_dbg(dev->mt76.dev, "mask out 5GHz support\n");
	पूर्ण

	अगर (!mt76x02_field_valid(nic_conf1 & 0xff))
		nic_conf1 &= 0xff00;

	अगर (nic_conf1 & MT_EE_NIC_CONF_1_HW_RF_CTRL)
		dev_err(dev->mt76.dev,
			"driver does not support HW RF ctrl\n");

	अगर (!mt76x02_field_valid(nic_conf0 >> 8))
		वापस;

	अगर (FIELD_GET(MT_EE_NIC_CONF_0_RX_PATH, nic_conf0) > 1 ||
	    FIELD_GET(MT_EE_NIC_CONF_0_TX_PATH, nic_conf0) > 1)
		dev_err(dev->mt76.dev, "invalid tx-rx stream\n");
पूर्ण

अटल व्योम mt76x0_set_temp_offset(काष्ठा mt76x02_dev *dev)
अणु
	u8 val;

	val = mt76x02_eeprom_get(dev, MT_EE_2G_TARGET_POWER) >> 8;
	अगर (mt76x02_field_valid(val))
		dev->cal.rx.temp_offset = mt76x02_sign_extend(val, 8);
	अन्यथा
		dev->cal.rx.temp_offset = -10;
पूर्ण

अटल व्योम mt76x0_set_freq_offset(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x02_rx_freq_cal *caldata = &dev->cal.rx;
	u8 val;

	val = mt76x02_eeprom_get(dev, MT_EE_FREQ_OFFSET);
	अगर (!mt76x02_field_valid(val))
		val = 0;
	caldata->freq_offset = val;

	val = mt76x02_eeprom_get(dev, MT_EE_TSSI_BOUND4) >> 8;
	अगर (!mt76x02_field_valid(val))
		val = 0;

	caldata->freq_offset -= mt76x02_sign_extend(val, 8);
पूर्ण

व्योम mt76x0_पढ़ो_rx_gain(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	काष्ठा mt76x02_rx_freq_cal *caldata = &dev->cal.rx;
	s8 val, lna_5g[3], lna_2g;
	u16 rssi_offset;
	पूर्णांक i;

	mt76x02_get_rx_gain(dev, chan->band, &rssi_offset, &lna_2g, lna_5g);
	caldata->lna_gain = mt76x02_get_lna_gain(dev, &lna_2g, lna_5g, chan);

	क्रम (i = 0; i < ARRAY_SIZE(caldata->rssi_offset); i++) अणु
		val = rssi_offset >> (8 * i);
		अगर (val < -10 || val > 10)
			val = 0;

		caldata->rssi_offset[i] = val;
	पूर्ण
पूर्ण

अटल s8 mt76x0_get_delta(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा cfg80211_chan_def *chandef = &dev->mphy.chandef;
	u8 val;

	अगर (chandef->width == NL80211_CHAN_WIDTH_80) अणु
		val = mt76x02_eeprom_get(dev, MT_EE_5G_TARGET_POWER) >> 8;
	पूर्ण अन्यथा अगर (chandef->width == NL80211_CHAN_WIDTH_40) अणु
		u16 data;

		data = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_DELTA_BW40);
		अगर (chandef->chan->band == NL80211_BAND_5GHZ)
			val = data >> 8;
		अन्यथा
			val = data;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	वापस mt76x02_rate_घातer_val(val);
पूर्ण

व्योम mt76x0_get_tx_घातer_per_rate(काष्ठा mt76x02_dev *dev,
				  काष्ठा ieee80211_channel *chan,
				  काष्ठा mt76_rate_घातer *t)
अणु
	bool is_2ghz = chan->band == NL80211_BAND_2GHZ;
	u16 val, addr;
	s8 delta;

	स_रखो(t, 0, माप(*t));

	/* cck 1M, 2M, 5.5M, 11M */
	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_BYRATE_BASE);
	t->cck[0] = t->cck[1] = s6_to_s8(val);
	t->cck[2] = t->cck[3] = s6_to_s8(val >> 8);

	/* ofdm 6M, 9M, 12M, 18M */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 2 : 0x120;
	val = mt76x02_eeprom_get(dev, addr);
	t->ofdm[0] = t->ofdm[1] = s6_to_s8(val);
	t->ofdm[2] = t->ofdm[3] = s6_to_s8(val >> 8);

	/* ofdm 24M, 36M, 48M, 54M */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 4 : 0x122;
	val = mt76x02_eeprom_get(dev, addr);
	t->ofdm[4] = t->ofdm[5] = s6_to_s8(val);
	t->ofdm[6] = t->ofdm[7] = s6_to_s8(val >> 8);

	/* ht-vht mcs 1ss 0, 1, 2, 3 */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 6 : 0x124;
	val = mt76x02_eeprom_get(dev, addr);
	t->ht[0] = t->ht[1] = t->vht[0] = t->vht[1] = s6_to_s8(val);
	t->ht[2] = t->ht[3] = t->vht[2] = t->vht[3] = s6_to_s8(val >> 8);

	/* ht-vht mcs 1ss 4, 5, 6 */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 8 : 0x126;
	val = mt76x02_eeprom_get(dev, addr);
	t->ht[4] = t->ht[5] = t->vht[4] = t->vht[5] = s6_to_s8(val);
	t->ht[6] = t->ht[7] = t->vht[6] = t->vht[7] = s6_to_s8(val >> 8);

	/* ht-vht mcs 1ss 0, 1, 2, 3 stbc */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 14 : 0xec;
	val = mt76x02_eeprom_get(dev, addr);
	t->stbc[0] = t->stbc[1] = s6_to_s8(val);
	t->stbc[2] = t->stbc[3] = s6_to_s8(val >> 8);

	/* ht-vht mcs 1ss 4, 5, 6 stbc */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 16 : 0xee;
	val = mt76x02_eeprom_get(dev, addr);
	t->stbc[4] = t->stbc[5] = s6_to_s8(val);
	t->stbc[6] = t->stbc[7] = s6_to_s8(val >> 8);

	/* vht mcs 8, 9 5GHz */
	val = mt76x02_eeprom_get(dev, 0x132);
	t->vht[8] = s6_to_s8(val);
	t->vht[9] = s6_to_s8(val >> 8);

	delta = mt76x0_tssi_enabled(dev) ? 0 : mt76x0_get_delta(dev);
	mt76x02_add_rate_घातer_offset(t, delta);
पूर्ण

व्योम mt76x0_get_घातer_info(काष्ठा mt76x02_dev *dev,
			   काष्ठा ieee80211_channel *chan, s8 *tp)
अणु
	अटल स्थिर काष्ठा mt76x0_chan_map अणु
		u8 chan;
		u8 offset;
	पूर्ण chan_map[] = अणु
		अणु   2,  0 पूर्ण, अणु   4,  2 पूर्ण, अणु   6,  4 पूर्ण, अणु   8,  6 पूर्ण,
		अणु  10,  8 पूर्ण, अणु  12, 10 पूर्ण, अणु  14, 12 पूर्ण, अणु  38,  0 पूर्ण,
		अणु  44,  2 पूर्ण, अणु  48,  4 पूर्ण, अणु  54,  6 पूर्ण, अणु  60,  8 पूर्ण,
		अणु  64, 10 पूर्ण, अणु 102, 12 पूर्ण, अणु 108, 14 पूर्ण, अणु 112, 16 पूर्ण,
		अणु 118, 18 पूर्ण, अणु 124, 20 पूर्ण, अणु 128, 22 पूर्ण, अणु 134, 24 पूर्ण,
		अणु 140, 26 पूर्ण, अणु 151, 28 पूर्ण, अणु 157, 30 पूर्ण, अणु 161, 32 पूर्ण,
		अणु 167, 34 पूर्ण, अणु 171, 36 पूर्ण, अणु 175, 38 पूर्ण,
	पूर्ण;
	u8 offset, addr;
	पूर्णांक i, idx = 0;
	u16 data;

	अगर (mt76x0_tssi_enabled(dev)) अणु
		s8 target_घातer;

		अगर (chan->band == NL80211_BAND_5GHZ)
			data = mt76x02_eeprom_get(dev, MT_EE_5G_TARGET_POWER);
		अन्यथा
			data = mt76x02_eeprom_get(dev, MT_EE_2G_TARGET_POWER);
		target_घातer = (data & 0xff) - dev->mt76.rate_घातer.ofdm[7];
		*tp = target_घातer + mt76x0_get_delta(dev);

		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(chan_map); i++) अणु
		अगर (chan->hw_value <= chan_map[i].chan) अणु
			idx = (chan->hw_value == chan_map[i].chan);
			offset = chan_map[i].offset;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(chan_map))
		offset = chan_map[0].offset;

	अगर (chan->band == NL80211_BAND_2GHZ) अणु
		addr = MT_EE_TX_POWER_DELTA_BW80 + offset;
	पूर्ण अन्यथा अणु
		चयन (chan->hw_value) अणु
		हाल 42:
			offset = 2;
			अवरोध;
		हाल 58:
			offset = 8;
			अवरोध;
		हाल 106:
			offset = 14;
			अवरोध;
		हाल 122:
			offset = 20;
			अवरोध;
		हाल 155:
			offset = 30;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		addr = MT_EE_TX_POWER_0_GRP4_TSSI_SLOPE + 2 + offset;
	पूर्ण

	data = mt76x02_eeprom_get(dev, addr);
	*tp = data >> (8 * idx);
	अगर (*tp < 0 || *tp > 0x3f)
		*tp = 5;
पूर्ण

अटल पूर्णांक mt76x0_check_eeprom(काष्ठा mt76x02_dev *dev)
अणु
	u16 val;

	val = get_unaligned_le16(dev->mt76.eeprom.data);
	अगर (!val)
		val = get_unaligned_le16(dev->mt76.eeprom.data +
					 MT_EE_PCI_ID);

	चयन (val) अणु
	हाल 0x7650:
	हाल 0x7610:
		वापस 0;
	शेष:
		dev_err(dev->mt76.dev, "EEPROM data check failed: %04x\n",
			val);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mt76x0_load_eeprom(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक found;

	found = mt76_eeprom_init(&dev->mt76, MT76X0_EEPROM_SIZE);
	अगर (found < 0)
		वापस found;

	अगर (found && !mt76x0_check_eeprom(dev))
		वापस 0;

	found = mt76x0_efuse_physical_size_check(dev);
	अगर (found < 0)
		वापस found;

	वापस mt76x02_get_efuse_data(dev, 0, dev->mt76.eeprom.data,
				      MT76X0_EEPROM_SIZE, MT_EE_READ);
पूर्ण

पूर्णांक mt76x0_eeprom_init(काष्ठा mt76x02_dev *dev)
अणु
	u8 version, fae;
	u16 data;
	पूर्णांक err;

	err = mt76x0_load_eeprom(dev);
	अगर (err < 0)
		वापस err;

	data = mt76x02_eeprom_get(dev, MT_EE_VERSION);
	version = data >> 8;
	fae = data;

	अगर (version > MT76X0U_EE_MAX_VER)
		dev_warn(dev->mt76.dev,
			 "Warning: unsupported EEPROM version %02hhx\n",
			 version);
	dev_info(dev->mt76.dev, "EEPROM ver:%02hhx fae:%02hhx\n",
		 version, fae);

	स_नकल(dev->mphy.macaddr, (u8 *)dev->mt76.eeprom.data + MT_EE_MAC_ADDR,
	       ETH_ALEN);
	mt76_eeprom_override(&dev->mphy);
	mt76x02_mac_setaddr(dev, dev->mphy.macaddr);

	mt76x0_set_chip_cap(dev);
	mt76x0_set_freq_offset(dev);
	mt76x0_set_temp_offset(dev);

	वापस 0;
पूर्ण

MODULE_LICENSE("Dual BSD/GPL");
