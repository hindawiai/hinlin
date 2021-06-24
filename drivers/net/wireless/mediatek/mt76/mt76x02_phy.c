<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/kernel.h>

#समावेश "mt76x02.h"
#समावेश "mt76x02_phy.h"

व्योम mt76x02_phy_set_rxpath(काष्ठा mt76x02_dev *dev)
अणु
	u32 val;

	val = mt76_rr(dev, MT_BBP(AGC, 0));
	val &= ~BIT(4);

	चयन (dev->mphy.chainmask & 0xf) अणु
	हाल 2:
		val |= BIT(3);
		अवरोध;
	शेष:
		val &= ~BIT(3);
		अवरोध;
	पूर्ण

	mt76_wr(dev, MT_BBP(AGC, 0), val);
	mb();
	val = mt76_rr(dev, MT_BBP(AGC, 0));
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_phy_set_rxpath);

व्योम mt76x02_phy_set_txdac(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक txpath;

	txpath = (dev->mphy.chainmask >> 8) & 0xf;
	चयन (txpath) अणु
	हाल 2:
		mt76_set(dev, MT_BBP(TXBE, 5), 0x3);
		अवरोध;
	शेष:
		mt76_clear(dev, MT_BBP(TXBE, 5), 0x3);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_phy_set_txdac);

अटल u32
mt76x02_tx_घातer_mask(u8 v1, u8 v2, u8 v3, u8 v4)
अणु
	u32 val = 0;

	val |= (v1 & (BIT(6) - 1)) << 0;
	val |= (v2 & (BIT(6) - 1)) << 8;
	val |= (v3 & (BIT(6) - 1)) << 16;
	val |= (v4 & (BIT(6) - 1)) << 24;
	वापस val;
पूर्ण

पूर्णांक mt76x02_get_max_rate_घातer(काष्ठा mt76_rate_घातer *r)
अणु
	s8 ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < माप(r->all); i++)
		ret = max(ret, r->all[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_get_max_rate_घातer);

व्योम mt76x02_limit_rate_घातer(काष्ठा mt76_rate_घातer *r, पूर्णांक limit)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < माप(r->all); i++)
		अगर (r->all[i] > limit)
			r->all[i] = limit;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_limit_rate_घातer);

व्योम mt76x02_add_rate_घातer_offset(काष्ठा mt76_rate_घातer *r, पूर्णांक offset)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < माप(r->all); i++)
		r->all[i] += offset;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_add_rate_घातer_offset);

व्योम mt76x02_phy_set_txघातer(काष्ठा mt76x02_dev *dev, पूर्णांक txp_0, पूर्णांक txp_1)
अणु
	काष्ठा mt76_rate_घातer *t = &dev->mt76.rate_घातer;

	mt76_rmw_field(dev, MT_TX_ALC_CFG_0, MT_TX_ALC_CFG_0_CH_INIT_0, txp_0);
	mt76_rmw_field(dev, MT_TX_ALC_CFG_0, MT_TX_ALC_CFG_0_CH_INIT_1, txp_1);

	mt76_wr(dev, MT_TX_PWR_CFG_0,
		mt76x02_tx_घातer_mask(t->cck[0], t->cck[2], t->ofdm[0],
				      t->ofdm[2]));
	mt76_wr(dev, MT_TX_PWR_CFG_1,
		mt76x02_tx_घातer_mask(t->ofdm[4], t->ofdm[6], t->ht[0],
				      t->ht[2]));
	mt76_wr(dev, MT_TX_PWR_CFG_2,
		mt76x02_tx_घातer_mask(t->ht[4], t->ht[6], t->ht[8],
				      t->ht[10]));
	mt76_wr(dev, MT_TX_PWR_CFG_3,
		mt76x02_tx_घातer_mask(t->ht[12], t->ht[14], t->stbc[0],
				      t->stbc[2]));
	mt76_wr(dev, MT_TX_PWR_CFG_4,
		mt76x02_tx_घातer_mask(t->stbc[4], t->stbc[6], 0, 0));
	mt76_wr(dev, MT_TX_PWR_CFG_7,
		mt76x02_tx_घातer_mask(t->ofdm[7], t->vht[8], t->ht[7],
				      t->vht[9]));
	mt76_wr(dev, MT_TX_PWR_CFG_8,
		mt76x02_tx_घातer_mask(t->ht[14], 0, t->vht[8], t->vht[9]));
	mt76_wr(dev, MT_TX_PWR_CFG_9,
		mt76x02_tx_घातer_mask(t->ht[7], 0, t->stbc[8], t->stbc[9]));
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_phy_set_txघातer);

व्योम mt76x02_phy_set_bw(काष्ठा mt76x02_dev *dev, पूर्णांक width, u8 ctrl)
अणु
	पूर्णांक core_val, agc_val;

	चयन (width) अणु
	हाल NL80211_CHAN_WIDTH_80:
		core_val = 3;
		agc_val = 7;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		core_val = 2;
		agc_val = 3;
		अवरोध;
	शेष:
		core_val = 0;
		agc_val = 1;
		अवरोध;
	पूर्ण

	mt76_rmw_field(dev, MT_BBP(CORE, 1), MT_BBP_CORE_R1_BW, core_val);
	mt76_rmw_field(dev, MT_BBP(AGC, 0), MT_BBP_AGC_R0_BW, agc_val);
	mt76_rmw_field(dev, MT_BBP(AGC, 0), MT_BBP_AGC_R0_CTRL_CHAN, ctrl);
	mt76_rmw_field(dev, MT_BBP(TXBE, 0), MT_BBP_TXBE_R0_CTRL_CHAN, ctrl);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_phy_set_bw);

व्योम mt76x02_phy_set_band(काष्ठा mt76x02_dev *dev, पूर्णांक band,
			  bool primary_upper)
अणु
	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		mt76_set(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_2G);
		mt76_clear(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_5G);
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		mt76_clear(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_2G);
		mt76_set(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_5G);
		अवरोध;
	पूर्ण

	mt76_rmw_field(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_UPPER_40M,
		       primary_upper);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_phy_set_band);

bool mt76x02_phy_adjust_vga_gain(काष्ठा mt76x02_dev *dev)
अणु
	u8 limit = dev->cal.low_gain > 0 ? 16 : 4;
	bool ret = false;
	u32 false_cca;

	false_cca = FIELD_GET(MT_RX_STAT_1_CCA_ERRORS,
			      mt76_rr(dev, MT_RX_STAT_1));
	dev->cal.false_cca = false_cca;
	अगर (false_cca > 800 && dev->cal.agc_gain_adjust < limit) अणु
		dev->cal.agc_gain_adjust += 2;
		ret = true;
	पूर्ण अन्यथा अगर ((false_cca < 10 && dev->cal.agc_gain_adjust > 0) ||
		   (dev->cal.agc_gain_adjust >= limit && false_cca < 500)) अणु
		dev->cal.agc_gain_adjust -= 2;
		ret = true;
	पूर्ण

	dev->cal.agc_lowest_gain = dev->cal.agc_gain_adjust >= limit;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_phy_adjust_vga_gain);

व्योम mt76x02_init_agc_gain(काष्ठा mt76x02_dev *dev)
अणु
	dev->cal.agc_gain_init[0] = mt76_get_field(dev, MT_BBP(AGC, 8),
						   MT_BBP_AGC_GAIN);
	dev->cal.agc_gain_init[1] = mt76_get_field(dev, MT_BBP(AGC, 9),
						   MT_BBP_AGC_GAIN);
	स_नकल(dev->cal.agc_gain_cur, dev->cal.agc_gain_init,
	       माप(dev->cal.agc_gain_cur));
	dev->cal.low_gain = -1;
	dev->cal.gain_init_करोne = true;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_init_agc_gain);
