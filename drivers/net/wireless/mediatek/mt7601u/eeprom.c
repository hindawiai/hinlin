<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश <linux/of.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "mt7601u.h"
#समावेश "eeprom.h"
#समावेश "mac.h"

अटल bool
field_valid(u8 val)
अणु
	वापस val != 0xff;
पूर्ण

अटल s8
field_validate(u8 val)
अणु
	अगर (!field_valid(val))
		वापस 0;

	वापस val;
पूर्ण

अटल पूर्णांक
mt7601u_efuse_पढ़ो(काष्ठा mt7601u_dev *dev, u16 addr, u8 *data,
		   क्रमागत mt7601u_eeprom_access_modes mode)
अणु
	u32 val;
	पूर्णांक i;

	val = mt76_rr(dev, MT_EFUSE_CTRL);
	val &= ~(MT_EFUSE_CTRL_AIN |
		 MT_EFUSE_CTRL_MODE);
	val |= FIELD_PREP(MT_EFUSE_CTRL_AIN, addr & ~0xf) |
	       FIELD_PREP(MT_EFUSE_CTRL_MODE, mode) |
	       MT_EFUSE_CTRL_KICK;
	mt76_wr(dev, MT_EFUSE_CTRL, val);

	अगर (!mt76_poll(dev, MT_EFUSE_CTRL, MT_EFUSE_CTRL_KICK, 0, 1000))
		वापस -ETIMEDOUT;

	val = mt76_rr(dev, MT_EFUSE_CTRL);
	अगर ((val & MT_EFUSE_CTRL_AOUT) == MT_EFUSE_CTRL_AOUT) अणु
		/* Parts of eeprom not in the usage map (0x80-0xc0,0xf0)
		 * will not वापस valid data but it's ok.
		 */
		स_रखो(data, 0xff, 16);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		val = mt76_rr(dev, MT_EFUSE_DATA(i));
		put_unaligned_le32(val, data + 4 * i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7601u_efuse_physical_size_check(काष्ठा mt7601u_dev *dev)
अणु
	स्थिर पूर्णांक map_पढ़ोs = DIV_ROUND_UP(MT_EFUSE_USAGE_MAP_SIZE, 16);
	u8 data[round_up(MT_EFUSE_USAGE_MAP_SIZE, 16)];
	पूर्णांक ret, i;
	u32 start = 0, end = 0, cnt_मुक्त;

	क्रम (i = 0; i < map_पढ़ोs; i++) अणु
		ret = mt7601u_efuse_पढ़ो(dev, MT_EE_USAGE_MAP_START + i * 16,
					 data + i * 16, MT_EE_PHYSICAL_READ);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < MT_EFUSE_USAGE_MAP_SIZE; i++)
		अगर (!data[i]) अणु
			अगर (!start)
				start = MT_EE_USAGE_MAP_START + i;
			end = MT_EE_USAGE_MAP_START + i;
		पूर्ण
	cnt_मुक्त = end - start + 1;

	अगर (MT_EFUSE_USAGE_MAP_SIZE - cnt_मुक्त < 5) अणु
		dev_err(dev->dev, "Error: your device needs default EEPROM file and this driver doesn't support it!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
mt7601u_has_tssi(काष्ठा mt7601u_dev *dev, u8 *eeprom)
अणु
	u16 nic_conf1 = get_unaligned_le16(eeprom + MT_EE_NIC_CONF_1);

	वापस (u16)~nic_conf1 && (nic_conf1 & MT_EE_NIC_CONF_1_TX_ALC_EN);
पूर्ण

अटल व्योम
mt7601u_set_chip_cap(काष्ठा mt7601u_dev *dev, u8 *eeprom)
अणु
	u16 nic_conf0 = get_unaligned_le16(eeprom + MT_EE_NIC_CONF_0);
	u16 nic_conf1 = get_unaligned_le16(eeprom + MT_EE_NIC_CONF_1);

	अगर (!field_valid(nic_conf1 & 0xff))
		nic_conf1 &= 0xff00;

	dev->ee->tssi_enabled = mt7601u_has_tssi(dev, eeprom) &&
				!(nic_conf1 & MT_EE_NIC_CONF_1_TEMP_TX_ALC);

	अगर (nic_conf1 & MT_EE_NIC_CONF_1_HW_RF_CTRL)
		dev_err(dev->dev,
			"Error: this driver does not support HW RF ctrl\n");

	अगर (!field_valid(nic_conf0 >> 8))
		वापस;

	अगर (FIELD_GET(MT_EE_NIC_CONF_0_RX_PATH, nic_conf0) > 1 ||
	    FIELD_GET(MT_EE_NIC_CONF_0_TX_PATH, nic_conf0) > 1)
		dev_err(dev->dev,
			"Error: device has more than 1 RX/TX stream!\n");
पूर्ण

अटल व्योम mt7601u_set_channel_target_घातer(काष्ठा mt7601u_dev *dev,
					     u8 *eeprom, u8 max_pwr)
अणु
	u8 trgt_pwr = eeprom[MT_EE_TX_TSSI_TARGET_POWER];

	अगर (trgt_pwr > max_pwr || !trgt_pwr) अणु
		dev_warn(dev->dev, "Error: EEPROM trgt power invalid %hhx!\n",
			 trgt_pwr);
		trgt_pwr = 0x20;
	पूर्ण

	स_रखो(dev->ee->chan_pwr, trgt_pwr, माप(dev->ee->chan_pwr));
पूर्ण

अटल व्योम
mt7601u_set_channel_घातer(काष्ठा mt7601u_dev *dev, u8 *eeprom)
अणु
	u32 i, val;
	u8 max_pwr;

	val = mt7601u_rr(dev, MT_TX_ALC_CFG_0);
	max_pwr = FIELD_GET(MT_TX_ALC_CFG_0_LIMIT_0, val);

	अगर (mt7601u_has_tssi(dev, eeprom)) अणु
		mt7601u_set_channel_target_घातer(dev, eeprom, max_pwr);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 14; i++) अणु
		s8 घातer = field_validate(eeprom[MT_EE_TX_POWER_OFFSET + i]);

		अगर (घातer > max_pwr || घातer < 0)
			घातer = MT7601U_DEFAULT_TX_POWER;

		dev->ee->chan_pwr[i] = घातer;
	पूर्ण
पूर्ण

अटल व्योम
mt7601u_set_country_reg(काष्ठा mt7601u_dev *dev, u8 *eeprom)
अणु
	/* Note: - region 31 is not valid क्रम mt7601u (see rपंचांगp_init.c)
	 *	 - comments in rपंचांगp_def.h are incorrect (see rt_channel.c)
	 */
	अटल स्थिर काष्ठा reg_channel_bounds chan_bounds[] = अणु
		/* EEPROM country regions 0 - 7 */
		अणु  1, 11 पूर्ण,	अणु  1, 13 पूर्ण,	अणु 10,  2 पूर्ण,	अणु 10,  4 पूर्ण,
		अणु 14,  1 पूर्ण,	अणु  1, 14 पूर्ण,	अणु  3,  7 पूर्ण,	अणु  5,  9 पूर्ण,
		/* EEPROM country regions 32 - 33 */
		अणु  1, 11 पूर्ण,	अणु  1, 14 पूर्ण
	पूर्ण;
	u8 val = eeprom[MT_EE_COUNTRY_REGION];
	पूर्णांक idx = -1;

	अगर (val < 8)
		idx = val;
	अगर (val > 31 && val < 33)
		idx = val - 32 + 8;

	अगर (idx != -1)
		dev_info(dev->dev,
			 "EEPROM country region %02hhx (channels %hhd-%hhd)\n",
			 val, chan_bounds[idx].start,
			 chan_bounds[idx].start + chan_bounds[idx].num - 1);
	अन्यथा
		idx = 5; /* channels 1 - 14 */

	dev->ee->reg = chan_bounds[idx];

	/* TODO: country region 33 is special - phy should be set to B-mode
	 *	 beक्रमe entering channel 14 (see sta/connect.c)
	 */
पूर्ण

अटल व्योम
mt7601u_set_rf_freq_off(काष्ठा mt7601u_dev *dev, u8 *eeprom)
अणु
	u8 comp;

	dev->ee->rf_freq_off = field_validate(eeprom[MT_EE_FREQ_OFFSET]);
	comp = field_validate(eeprom[MT_EE_FREQ_OFFSET_COMPENSATION]);

	अगर (comp & BIT(7))
		dev->ee->rf_freq_off -= comp & 0x7f;
	अन्यथा
		dev->ee->rf_freq_off += comp;
पूर्ण

अटल व्योम
mt7601u_set_rssi_offset(काष्ठा mt7601u_dev *dev, u8 *eeprom)
अणु
	पूर्णांक i;
	s8 *rssi_offset = dev->ee->rssi_offset;

	क्रम (i = 0; i < 2; i++) अणु
		rssi_offset[i] = eeprom[MT_EE_RSSI_OFFSET + i];

		अगर (rssi_offset[i] < -10 || rssi_offset[i] > 10) अणु
			dev_warn(dev->dev,
				 "Warning: EEPROM RSSI is invalid %02hhx\n",
				 rssi_offset[i]);
			rssi_offset[i] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
mt7601u_extra_घातer_over_mac(काष्ठा mt7601u_dev *dev)
अणु
	u32 val;

	val = ((mt7601u_rr(dev, MT_TX_PWR_CFG_1) & 0x0000ff00) >> 8);
	val |= ((mt7601u_rr(dev, MT_TX_PWR_CFG_2) & 0x0000ff00) << 8);
	mt7601u_wr(dev, MT_TX_PWR_CFG_7, val);

	val = ((mt7601u_rr(dev, MT_TX_PWR_CFG_4) & 0x0000ff00) >> 8);
	mt7601u_wr(dev, MT_TX_PWR_CFG_9, val);
पूर्ण

अटल व्योम
mt7601u_set_घातer_rate(काष्ठा घातer_per_rate *rate, s8 delta, u8 value)
अणु
	/* Invalid? Note: venकरोr driver करोes not handle this */
	अगर (value == 0xff)
		वापस;

	rate->raw = s6_validate(value);
	rate->bw20 = s6_to_पूर्णांक(value);
	/* Note: venकरोr driver करोes cap the value to s6 right away */
	rate->bw40 = rate->bw20 + delta;
पूर्ण

अटल व्योम
mt7601u_save_घातer_rate(काष्ठा mt7601u_dev *dev, s8 delta, u32 val, पूर्णांक i)
अणु
	काष्ठा mt7601u_rate_घातer *t = &dev->ee->घातer_rate_table;

	चयन (i) अणु
	हाल 0:
		mt7601u_set_घातer_rate(&t->cck[0], delta, (val >> 0) & 0xff);
		mt7601u_set_घातer_rate(&t->cck[1], delta, (val >> 8) & 0xff);
		/* Save cck bw20 क्रम fixups of channel 14 */
		dev->ee->real_cck_bw20[0] = t->cck[0].bw20;
		dev->ee->real_cck_bw20[1] = t->cck[1].bw20;

		mt7601u_set_घातer_rate(&t->ofdm[0], delta, (val >> 16) & 0xff);
		mt7601u_set_घातer_rate(&t->ofdm[1], delta, (val >> 24) & 0xff);
		अवरोध;
	हाल 1:
		mt7601u_set_घातer_rate(&t->ofdm[2], delta, (val >> 0) & 0xff);
		mt7601u_set_घातer_rate(&t->ofdm[3], delta, (val >> 8) & 0xff);
		mt7601u_set_घातer_rate(&t->ht[0], delta, (val >> 16) & 0xff);
		mt7601u_set_घातer_rate(&t->ht[1], delta, (val >> 24) & 0xff);
		अवरोध;
	हाल 2:
		mt7601u_set_घातer_rate(&t->ht[2], delta, (val >> 0) & 0xff);
		mt7601u_set_घातer_rate(&t->ht[3], delta, (val >> 8) & 0xff);
		अवरोध;
	पूर्ण
पूर्ण

अटल s8
get_delta(u8 val)
अणु
	s8 ret;

	अगर (!field_valid(val) || !(val & BIT(7)))
		वापस 0;

	ret = val & 0x1f;
	अगर (ret > 8)
		ret = 8;
	अगर (val & BIT(6))
		ret = -ret;

	वापस ret;
पूर्ण

अटल व्योम
mt7601u_config_tx_घातer_per_rate(काष्ठा mt7601u_dev *dev, u8 *eeprom)
अणु
	u32 val;
	s8 bw40_delta;
	पूर्णांक i;

	bw40_delta = get_delta(eeprom[MT_EE_TX_POWER_DELTA_BW40]);

	क्रम (i = 0; i < 5; i++) अणु
		val = get_unaligned_le32(eeprom + MT_EE_TX_POWER_BYRATE(i));

		mt7601u_save_घातer_rate(dev, bw40_delta, val, i);

		अगर (~val)
			mt7601u_wr(dev, MT_TX_PWR_CFG_0 + i * 4, val);
	पूर्ण

	mt7601u_extra_घातer_over_mac(dev);
पूर्ण

अटल व्योम
mt7601u_init_tssi_params(काष्ठा mt7601u_dev *dev, u8 *eeprom)
अणु
	काष्ठा tssi_data *d = &dev->ee->tssi_data;

	अगर (!dev->ee->tssi_enabled)
		वापस;

	d->slope = eeprom[MT_EE_TX_TSSI_SLOPE];
	d->tx0_delta_offset = eeprom[MT_EE_TX_TSSI_OFFSET] * 1024;
	d->offset[0] = eeprom[MT_EE_TX_TSSI_OFFSET_GROUP];
	d->offset[1] = eeprom[MT_EE_TX_TSSI_OFFSET_GROUP + 1];
	d->offset[2] = eeprom[MT_EE_TX_TSSI_OFFSET_GROUP + 2];
पूर्ण

पूर्णांक
mt7601u_eeprom_init(काष्ठा mt7601u_dev *dev)
अणु
	u8 *eeprom;
	पूर्णांक i, ret;

	ret = mt7601u_efuse_physical_size_check(dev);
	अगर (ret)
		वापस ret;

	dev->ee = devm_kzalloc(dev->dev, माप(*dev->ee), GFP_KERNEL);
	अगर (!dev->ee)
		वापस -ENOMEM;

	eeprom = kदो_स्मृति(MT7601U_EEPROM_SIZE, GFP_KERNEL);
	अगर (!eeprom)
		वापस -ENOMEM;

	क्रम (i = 0; i + 16 <= MT7601U_EEPROM_SIZE; i += 16) अणु
		ret = mt7601u_efuse_पढ़ो(dev, i, eeprom + i, MT_EE_READ);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (eeprom[MT_EE_VERSION_EE] > MT7601U_EE_MAX_VER)
		dev_warn(dev->dev,
			 "Warning: unsupported EEPROM version %02hhx\n",
			 eeprom[MT_EE_VERSION_EE]);
	dev_info(dev->dev, "EEPROM ver:%02hhx fae:%02hhx\n",
		 eeprom[MT_EE_VERSION_EE], eeprom[MT_EE_VERSION_FAE]);

	mt7601u_set_macaddr(dev, eeprom + MT_EE_MAC_ADDR);
	mt7601u_set_chip_cap(dev, eeprom);
	mt7601u_set_channel_घातer(dev, eeprom);
	mt7601u_set_country_reg(dev, eeprom);
	mt7601u_set_rf_freq_off(dev, eeprom);
	mt7601u_set_rssi_offset(dev, eeprom);
	dev->ee->ref_temp = eeprom[MT_EE_REF_TEMP];
	dev->ee->lna_gain = eeprom[MT_EE_LNA_GAIN];

	mt7601u_config_tx_घातer_per_rate(dev, eeprom);

	mt7601u_init_tssi_params(dev, eeprom);
out:
	kमुक्त(eeprom);
	वापस ret;
पूर्ण
