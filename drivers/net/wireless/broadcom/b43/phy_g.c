<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver
  IEEE 802.11g PHY driver

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>,
  Copyright (c) 2005-2007 Stefano Brivio <stefano.brivio@polimi.it>
  Copyright (c) 2005-2008 Michael Buesch <m@bues.ch>
  Copyright (c) 2005, 2006 Danny van Dyk <kugelfang@gentoo.org>
  Copyright (c) 2005, 2006 Andreas Jaggi <andreas.jaggi@waterwave.ch>


*/

#समावेश "b43.h"
#समावेश "phy_g.h"
#समावेश "phy_common.h"
#समावेश "lo.h"
#समावेश "main.h"
#समावेश "wa.h"

#समावेश <linux/bitrev.h>
#समावेश <linux/slab.h>


अटल स्थिर s8 b43_tssi2dbm_g_table[] = अणु
	77, 77, 77, 76,
	76, 76, 75, 75,
	74, 74, 73, 73,
	73, 72, 72, 71,
	71, 70, 70, 69,
	68, 68, 67, 67,
	66, 65, 65, 64,
	63, 63, 62, 61,
	60, 59, 58, 57,
	56, 55, 54, 53,
	52, 50, 49, 47,
	45, 43, 40, 37,
	33, 28, 22, 14,
	5, -7, -20, -20,
	-20, -20, -20, -20,
	-20, -20, -20, -20,
पूर्ण;

अटल स्थिर u8 b43_radio_channel_codes_bg[] = अणु
	12, 17, 22, 27,
	32, 37, 42, 47,
	52, 57, 62, 67,
	72, 84,
पूर्ण;


अटल व्योम b43_calc_nrssi_threshold(काष्ठा b43_wldev *dev);


#घोषणा bitrev4(पंचांगp) (bitrev8(पंचांगp) >> 4)


/* Get the freq, as it has to be written to the device. */
अटल अंतरभूत u16 channel2freq_bg(u8 channel)
अणु
	B43_WARN_ON(!(channel >= 1 && channel <= 14));

	वापस b43_radio_channel_codes_bg[channel - 1];
पूर्ण

अटल व्योम generate_rfatt_list(काष्ठा b43_wldev *dev,
				काष्ठा b43_rfatt_list *list)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	/* APHY.rev < 5 || GPHY.rev < 6 */
	अटल स्थिर काष्ठा b43_rfatt rfatt_0[] = अणु
		अणु.att = 3,.with_padmix = 0,पूर्ण,
		अणु.att = 1,.with_padmix = 0,पूर्ण,
		अणु.att = 5,.with_padmix = 0,पूर्ण,
		अणु.att = 7,.with_padmix = 0,पूर्ण,
		अणु.att = 9,.with_padmix = 0,पूर्ण,
		अणु.att = 2,.with_padmix = 0,पूर्ण,
		अणु.att = 0,.with_padmix = 0,पूर्ण,
		अणु.att = 4,.with_padmix = 0,पूर्ण,
		अणु.att = 6,.with_padmix = 0,पूर्ण,
		अणु.att = 8,.with_padmix = 0,पूर्ण,
		अणु.att = 1,.with_padmix = 1,पूर्ण,
		अणु.att = 2,.with_padmix = 1,पूर्ण,
		अणु.att = 3,.with_padmix = 1,पूर्ण,
		अणु.att = 4,.with_padmix = 1,पूर्ण,
	पूर्ण;
	/* Radio.rev == 8 && Radio.version == 0x2050 */
	अटल स्थिर काष्ठा b43_rfatt rfatt_1[] = अणु
		अणु.att = 2,.with_padmix = 1,पूर्ण,
		अणु.att = 4,.with_padmix = 1,पूर्ण,
		अणु.att = 6,.with_padmix = 1,पूर्ण,
		अणु.att = 8,.with_padmix = 1,पूर्ण,
		अणु.att = 10,.with_padmix = 1,पूर्ण,
		अणु.att = 12,.with_padmix = 1,पूर्ण,
		अणु.att = 14,.with_padmix = 1,पूर्ण,
	पूर्ण;
	/* Otherwise */
	अटल स्थिर काष्ठा b43_rfatt rfatt_2[] = अणु
		अणु.att = 0,.with_padmix = 1,पूर्ण,
		अणु.att = 2,.with_padmix = 1,पूर्ण,
		अणु.att = 4,.with_padmix = 1,पूर्ण,
		अणु.att = 6,.with_padmix = 1,पूर्ण,
		अणु.att = 8,.with_padmix = 1,पूर्ण,
		अणु.att = 9,.with_padmix = 1,पूर्ण,
		अणु.att = 9,.with_padmix = 1,पूर्ण,
	पूर्ण;

	अगर (!b43_has_hardware_pctl(dev)) अणु
		/* Software pctl */
		list->list = rfatt_0;
		list->len = ARRAY_SIZE(rfatt_0);
		list->min_val = 0;
		list->max_val = 9;
		वापस;
	पूर्ण
	अगर (phy->radio_ver == 0x2050 && phy->radio_rev == 8) अणु
		/* Hardware pctl */
		list->list = rfatt_1;
		list->len = ARRAY_SIZE(rfatt_1);
		list->min_val = 0;
		list->max_val = 14;
		वापस;
	पूर्ण
	/* Hardware pctl */
	list->list = rfatt_2;
	list->len = ARRAY_SIZE(rfatt_2);
	list->min_val = 0;
	list->max_val = 9;
पूर्ण

अटल व्योम generate_bbatt_list(काष्ठा b43_wldev *dev,
				काष्ठा b43_bbatt_list *list)
अणु
	अटल स्थिर काष्ठा b43_bbatt bbatt_0[] = अणु
		अणु.att = 0,पूर्ण,
		अणु.att = 1,पूर्ण,
		अणु.att = 2,पूर्ण,
		अणु.att = 3,पूर्ण,
		अणु.att = 4,पूर्ण,
		अणु.att = 5,पूर्ण,
		अणु.att = 6,पूर्ण,
		अणु.att = 7,पूर्ण,
		अणु.att = 8,पूर्ण,
	पूर्ण;

	list->list = bbatt_0;
	list->len = ARRAY_SIZE(bbatt_0);
	list->min_val = 0;
	list->max_val = 8;
पूर्ण

अटल व्योम b43_shm_clear_tssi(काष्ठा b43_wldev *dev)
अणु
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 0x0058, 0x7F7F);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 0x005a, 0x7F7F);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 0x0070, 0x7F7F);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 0x0072, 0x7F7F);
पूर्ण

/* Synthetic PU workaround */
अटल व्योम b43_synth_pu_workaround(काष्ठा b43_wldev *dev, u8 channel)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	might_sleep();

	अगर (phy->radio_ver != 0x2050 || phy->radio_rev >= 6) अणु
		/* We करो not need the workaround. */
		वापस;
	पूर्ण

	अगर (channel <= 10) अणु
		b43_ग_लिखो16(dev, B43_MMIO_CHANNEL,
			    channel2freq_bg(channel + 4));
	पूर्ण अन्यथा अणु
		b43_ग_लिखो16(dev, B43_MMIO_CHANNEL, channel2freq_bg(1));
	पूर्ण
	msleep(1);
	b43_ग_लिखो16(dev, B43_MMIO_CHANNEL, channel2freq_bg(channel));
पूर्ण

/* Set the baseband attenuation value on chip. */
व्योम b43_gphy_set_baseband_attenuation(काष्ठा b43_wldev *dev,
				       u16 baseband_attenuation)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (phy->analog == 0) अणु
		b43_ग_लिखो16(dev, B43_MMIO_PHY0, (b43_पढ़ो16(dev, B43_MMIO_PHY0)
						 & 0xFFF0) |
			    baseband_attenuation);
	पूर्ण अन्यथा अगर (phy->analog > 1) अणु
		b43_phy_maskset(dev, B43_PHY_DACCTL, 0xFFC3, (baseband_attenuation << 2));
	पूर्ण अन्यथा अणु
		b43_phy_maskset(dev, B43_PHY_DACCTL, 0xFF87, (baseband_attenuation << 3));
	पूर्ण
पूर्ण

/* Adjust the transmission घातer output (G-PHY) */
अटल व्योम b43_set_txघातer_g(काष्ठा b43_wldev *dev,
			      स्थिर काष्ठा b43_bbatt *bbatt,
			      स्थिर काष्ठा b43_rfatt *rfatt, u8 tx_control)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_txघातer_lo_control *lo = gphy->lo_control;
	u16 bb, rf;
	u16 tx_bias, tx_magn;

	bb = bbatt->att;
	rf = rfatt->att;
	tx_bias = lo->tx_bias;
	tx_magn = lo->tx_magn;
	अगर (unlikely(tx_bias == 0xFF))
		tx_bias = 0;

	/* Save the values क्रम later. Use स_हटाओ, because it's valid
	 * to pass &gphy->rfatt as rfatt poपूर्णांकer argument. Same क्रम bbatt. */
	gphy->tx_control = tx_control;
	स_हटाओ(&gphy->rfatt, rfatt, माप(*rfatt));
	gphy->rfatt.with_padmix = !!(tx_control & B43_TXCTL_TXMIX);
	स_हटाओ(&gphy->bbatt, bbatt, माप(*bbatt));

	अगर (b43_debug(dev, B43_DBG_XMITPOWER)) अणु
		b43dbg(dev->wl, "Tuning TX-power to bbatt(%u), "
		       "rfatt(%u), tx_control(0x%02X), "
		       "tx_bias(0x%02X), tx_magn(0x%02X)\n",
		       bb, rf, tx_control, tx_bias, tx_magn);
	पूर्ण

	b43_gphy_set_baseband_attenuation(dev, bb);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_RFATT, rf);
	अगर (phy->radio_ver == 0x2050 && phy->radio_rev == 8) अणु
		b43_radio_ग_लिखो16(dev, 0x43,
				  (rf & 0x000F) | (tx_control & 0x0070));
	पूर्ण अन्यथा अणु
		b43_radio_maskset(dev, 0x43, 0xFFF0, (rf & 0x000F));
		b43_radio_maskset(dev, 0x52, ~0x0070, (tx_control & 0x0070));
	पूर्ण
	अगर (has_tx_magnअगरication(phy)) अणु
		b43_radio_ग_लिखो16(dev, 0x52, tx_magn | tx_bias);
	पूर्ण अन्यथा अणु
		b43_radio_maskset(dev, 0x52, 0xFFF0, (tx_bias & 0x000F));
	पूर्ण
	b43_lo_g_adjust(dev);
पूर्ण

/* GPHY_TSSI_Power_Lookup_Table_Init */
अटल व्योम b43_gphy_tssi_घातer_lt_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_g *gphy = dev->phy.g;
	पूर्णांक i;
	u16 value;

	क्रम (i = 0; i < 32; i++)
		b43_ofdmtab_ग_लिखो16(dev, 0x3C20, i, gphy->tssi2dbm[i]);
	क्रम (i = 32; i < 64; i++)
		b43_ofdmtab_ग_लिखो16(dev, 0x3C00, i - 32, gphy->tssi2dbm[i]);
	क्रम (i = 0; i < 64; i += 2) अणु
		value = (u16) gphy->tssi2dbm[i];
		value |= ((u16) gphy->tssi2dbm[i + 1]) << 8;
		b43_phy_ग_लिखो(dev, 0x380 + (i / 2), value);
	पूर्ण
पूर्ण

/* GPHY_Gain_Lookup_Table_Init */
अटल व्योम b43_gphy_gain_lt_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_txघातer_lo_control *lo = gphy->lo_control;
	u16 nr_written = 0;
	u16 पंचांगp;
	u8 rf, bb;

	क्रम (rf = 0; rf < lo->rfatt_list.len; rf++) अणु
		क्रम (bb = 0; bb < lo->bbatt_list.len; bb++) अणु
			अगर (nr_written >= 0x40)
				वापस;
			पंचांगp = lo->bbatt_list.list[bb].att;
			पंचांगp <<= 8;
			अगर (phy->radio_rev == 8)
				पंचांगp |= 0x50;
			अन्यथा
				पंचांगp |= 0x40;
			पंचांगp |= lo->rfatt_list.list[rf].att;
			b43_phy_ग_लिखो(dev, 0x3C0 + nr_written, पंचांगp);
			nr_written++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43_set_all_gains(काष्ठा b43_wldev *dev,
			      s16 first, s16 second, s16 third)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 i;
	u16 start = 0x08, end = 0x18;
	u16 पंचांगp;
	u16 table;

	अगर (phy->rev <= 1) अणु
		start = 0x10;
		end = 0x20;
	पूर्ण

	table = B43_OFDMTAB_GAINX;
	अगर (phy->rev <= 1)
		table = B43_OFDMTAB_GAINX_R1;
	क्रम (i = 0; i < 4; i++)
		b43_ofdmtab_ग_लिखो16(dev, table, i, first);

	क्रम (i = start; i < end; i++)
		b43_ofdmtab_ग_लिखो16(dev, table, i, second);

	अगर (third != -1) अणु
		पंचांगp = ((u16) third << 14) | ((u16) third << 6);
		b43_phy_maskset(dev, 0x04A0, 0xBFBF, पंचांगp);
		b43_phy_maskset(dev, 0x04A1, 0xBFBF, पंचांगp);
		b43_phy_maskset(dev, 0x04A2, 0xBFBF, पंचांगp);
	पूर्ण
	b43_dummy_transmission(dev, false, true);
पूर्ण

अटल व्योम b43_set_original_gains(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 i, पंचांगp;
	u16 table;
	u16 start = 0x0008, end = 0x0018;

	अगर (phy->rev <= 1) अणु
		start = 0x0010;
		end = 0x0020;
	पूर्ण

	table = B43_OFDMTAB_GAINX;
	अगर (phy->rev <= 1)
		table = B43_OFDMTAB_GAINX_R1;
	क्रम (i = 0; i < 4; i++) अणु
		पंचांगp = (i & 0xFFFC);
		पंचांगp |= (i & 0x0001) << 1;
		पंचांगp |= (i & 0x0002) >> 1;

		b43_ofdmtab_ग_लिखो16(dev, table, i, पंचांगp);
	पूर्ण

	क्रम (i = start; i < end; i++)
		b43_ofdmtab_ग_लिखो16(dev, table, i, i - start);

	b43_phy_maskset(dev, 0x04A0, 0xBFBF, 0x4040);
	b43_phy_maskset(dev, 0x04A1, 0xBFBF, 0x4040);
	b43_phy_maskset(dev, 0x04A2, 0xBFBF, 0x4000);
	b43_dummy_transmission(dev, false, true);
पूर्ण

/* https://bcm-specs.sipsolutions.net/NRSSILookupTable */
अटल व्योम b43_nrssi_hw_ग_लिखो(काष्ठा b43_wldev *dev, u16 offset, s16 val)
अणु
	b43_phy_ग_लिखो(dev, B43_PHY_NRSSILT_CTRL, offset);
	b43_phy_ग_लिखो(dev, B43_PHY_NRSSILT_DATA, (u16) val);
पूर्ण

/* https://bcm-specs.sipsolutions.net/NRSSILookupTable */
अटल s16 b43_nrssi_hw_पढ़ो(काष्ठा b43_wldev *dev, u16 offset)
अणु
	u16 val;

	b43_phy_ग_लिखो(dev, B43_PHY_NRSSILT_CTRL, offset);
	val = b43_phy_पढ़ो(dev, B43_PHY_NRSSILT_DATA);

	वापस (s16) val;
पूर्ण

/* https://bcm-specs.sipsolutions.net/NRSSILookupTable */
अटल व्योम b43_nrssi_hw_update(काष्ठा b43_wldev *dev, u16 val)
अणु
	u16 i;
	s16 पंचांगp;

	क्रम (i = 0; i < 64; i++) अणु
		पंचांगp = b43_nrssi_hw_पढ़ो(dev, i);
		पंचांगp -= val;
		पंचांगp = clamp_val(पंचांगp, -32, 31);
		b43_nrssi_hw_ग_लिखो(dev, i, पंचांगp);
	पूर्ण
पूर्ण

/* https://bcm-specs.sipsolutions.net/NRSSILookupTable */
अटल व्योम b43_nrssi_mem_update(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_g *gphy = dev->phy.g;
	s16 i, delta;
	s32 पंचांगp;

	delta = 0x1F - gphy->nrssi[0];
	क्रम (i = 0; i < 64; i++) अणु
		पंचांगp = (i - delta) * gphy->nrssislope;
		पंचांगp /= 0x10000;
		पंचांगp += 0x3A;
		पंचांगp = clamp_val(पंचांगp, 0, 0x3F);
		gphy->nrssi_lt[i] = पंचांगp;
	पूर्ण
पूर्ण

अटल व्योम b43_calc_nrssi_offset(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 backup[20] = अणु 0 पूर्ण;
	s16 v47F;
	u16 i;
	u16 saved = 0xFFFF;

	backup[0] = b43_phy_पढ़ो(dev, 0x0001);
	backup[1] = b43_phy_पढ़ो(dev, 0x0811);
	backup[2] = b43_phy_पढ़ो(dev, 0x0812);
	अगर (phy->rev != 1) अणु	/* Not in specs, but needed to prevent PPC machine check */
		backup[3] = b43_phy_पढ़ो(dev, 0x0814);
		backup[4] = b43_phy_पढ़ो(dev, 0x0815);
	पूर्ण
	backup[5] = b43_phy_पढ़ो(dev, 0x005A);
	backup[6] = b43_phy_पढ़ो(dev, 0x0059);
	backup[7] = b43_phy_पढ़ो(dev, 0x0058);
	backup[8] = b43_phy_पढ़ो(dev, 0x000A);
	backup[9] = b43_phy_पढ़ो(dev, 0x0003);
	backup[10] = b43_radio_पढ़ो16(dev, 0x007A);
	backup[11] = b43_radio_पढ़ो16(dev, 0x0043);

	b43_phy_mask(dev, 0x0429, 0x7FFF);
	b43_phy_maskset(dev, 0x0001, 0x3FFF, 0x4000);
	b43_phy_set(dev, 0x0811, 0x000C);
	b43_phy_maskset(dev, 0x0812, 0xFFF3, 0x0004);
	b43_phy_mask(dev, 0x0802, ~(0x1 | 0x2));
	अगर (phy->rev >= 6) अणु
		backup[12] = b43_phy_पढ़ो(dev, 0x002E);
		backup[13] = b43_phy_पढ़ो(dev, 0x002F);
		backup[14] = b43_phy_पढ़ो(dev, 0x080F);
		backup[15] = b43_phy_पढ़ो(dev, 0x0810);
		backup[16] = b43_phy_पढ़ो(dev, 0x0801);
		backup[17] = b43_phy_पढ़ो(dev, 0x0060);
		backup[18] = b43_phy_पढ़ो(dev, 0x0014);
		backup[19] = b43_phy_पढ़ो(dev, 0x0478);

		b43_phy_ग_लिखो(dev, 0x002E, 0);
		b43_phy_ग_लिखो(dev, 0x002F, 0);
		b43_phy_ग_लिखो(dev, 0x080F, 0);
		b43_phy_ग_लिखो(dev, 0x0810, 0);
		b43_phy_set(dev, 0x0478, 0x0100);
		b43_phy_set(dev, 0x0801, 0x0040);
		b43_phy_set(dev, 0x0060, 0x0040);
		b43_phy_set(dev, 0x0014, 0x0200);
	पूर्ण
	b43_radio_set(dev, 0x007A, 0x0070);
	b43_radio_set(dev, 0x007A, 0x0080);
	udelay(30);

	v47F = (s16) ((b43_phy_पढ़ो(dev, 0x047F) >> 8) & 0x003F);
	अगर (v47F >= 0x20)
		v47F -= 0x40;
	अगर (v47F == 31) अणु
		क्रम (i = 7; i >= 4; i--) अणु
			b43_radio_ग_लिखो16(dev, 0x007B, i);
			udelay(20);
			v47F =
			    (s16) ((b43_phy_पढ़ो(dev, 0x047F) >> 8) & 0x003F);
			अगर (v47F >= 0x20)
				v47F -= 0x40;
			अगर (v47F < 31 && saved == 0xFFFF)
				saved = i;
		पूर्ण
		अगर (saved == 0xFFFF)
			saved = 4;
	पूर्ण अन्यथा अणु
		b43_radio_mask(dev, 0x007A, 0x007F);
		अगर (phy->rev != 1) अणु	/* Not in specs, but needed to prevent PPC machine check */
			b43_phy_set(dev, 0x0814, 0x0001);
			b43_phy_mask(dev, 0x0815, 0xFFFE);
		पूर्ण
		b43_phy_set(dev, 0x0811, 0x000C);
		b43_phy_set(dev, 0x0812, 0x000C);
		b43_phy_set(dev, 0x0811, 0x0030);
		b43_phy_set(dev, 0x0812, 0x0030);
		b43_phy_ग_लिखो(dev, 0x005A, 0x0480);
		b43_phy_ग_लिखो(dev, 0x0059, 0x0810);
		b43_phy_ग_लिखो(dev, 0x0058, 0x000D);
		अगर (phy->rev == 0) अणु
			b43_phy_ग_लिखो(dev, 0x0003, 0x0122);
		पूर्ण अन्यथा अणु
			b43_phy_set(dev, 0x000A, 0x2000);
		पूर्ण
		अगर (phy->rev != 1) अणु	/* Not in specs, but needed to prevent PPC machine check */
			b43_phy_set(dev, 0x0814, 0x0004);
			b43_phy_mask(dev, 0x0815, 0xFFFB);
		पूर्ण
		b43_phy_maskset(dev, 0x0003, 0xFF9F, 0x0040);
		b43_radio_set(dev, 0x007A, 0x000F);
		b43_set_all_gains(dev, 3, 0, 1);
		b43_radio_maskset(dev, 0x0043, 0x00F0, 0x000F);
		udelay(30);
		v47F = (s16) ((b43_phy_पढ़ो(dev, 0x047F) >> 8) & 0x003F);
		अगर (v47F >= 0x20)
			v47F -= 0x40;
		अगर (v47F == -32) अणु
			क्रम (i = 0; i < 4; i++) अणु
				b43_radio_ग_लिखो16(dev, 0x007B, i);
				udelay(20);
				v47F =
				    (s16) ((b43_phy_पढ़ो(dev, 0x047F) >> 8) &
					   0x003F);
				अगर (v47F >= 0x20)
					v47F -= 0x40;
				अगर (v47F > -31 && saved == 0xFFFF)
					saved = i;
			पूर्ण
			अगर (saved == 0xFFFF)
				saved = 3;
		पूर्ण अन्यथा
			saved = 0;
	पूर्ण
	b43_radio_ग_लिखो16(dev, 0x007B, saved);

	अगर (phy->rev >= 6) अणु
		b43_phy_ग_लिखो(dev, 0x002E, backup[12]);
		b43_phy_ग_लिखो(dev, 0x002F, backup[13]);
		b43_phy_ग_लिखो(dev, 0x080F, backup[14]);
		b43_phy_ग_लिखो(dev, 0x0810, backup[15]);
	पूर्ण
	अगर (phy->rev != 1) अणु	/* Not in specs, but needed to prevent PPC machine check */
		b43_phy_ग_लिखो(dev, 0x0814, backup[3]);
		b43_phy_ग_लिखो(dev, 0x0815, backup[4]);
	पूर्ण
	b43_phy_ग_लिखो(dev, 0x005A, backup[5]);
	b43_phy_ग_लिखो(dev, 0x0059, backup[6]);
	b43_phy_ग_लिखो(dev, 0x0058, backup[7]);
	b43_phy_ग_लिखो(dev, 0x000A, backup[8]);
	b43_phy_ग_लिखो(dev, 0x0003, backup[9]);
	b43_radio_ग_लिखो16(dev, 0x0043, backup[11]);
	b43_radio_ग_लिखो16(dev, 0x007A, backup[10]);
	b43_phy_ग_लिखो(dev, 0x0802, b43_phy_पढ़ो(dev, 0x0802) | 0x1 | 0x2);
	b43_phy_set(dev, 0x0429, 0x8000);
	b43_set_original_gains(dev);
	अगर (phy->rev >= 6) अणु
		b43_phy_ग_लिखो(dev, 0x0801, backup[16]);
		b43_phy_ग_लिखो(dev, 0x0060, backup[17]);
		b43_phy_ग_लिखो(dev, 0x0014, backup[18]);
		b43_phy_ग_लिखो(dev, 0x0478, backup[19]);
	पूर्ण
	b43_phy_ग_लिखो(dev, 0x0001, backup[0]);
	b43_phy_ग_लिखो(dev, 0x0812, backup[2]);
	b43_phy_ग_लिखो(dev, 0x0811, backup[1]);
पूर्ण

अटल व्योम b43_calc_nrssi_slope(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u16 backup[18] = अणु 0 पूर्ण;
	u16 पंचांगp;
	s16 nrssi0, nrssi1;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);

	अगर (phy->radio_rev >= 9)
		वापस;
	अगर (phy->radio_rev == 8)
		b43_calc_nrssi_offset(dev);

	b43_phy_mask(dev, B43_PHY_G_CRS, 0x7FFF);
	b43_phy_mask(dev, 0x0802, 0xFFFC);
	backup[7] = b43_पढ़ो16(dev, 0x03E2);
	b43_ग_लिखो16(dev, 0x03E2, b43_पढ़ो16(dev, 0x03E2) | 0x8000);
	backup[0] = b43_radio_पढ़ो16(dev, 0x007A);
	backup[1] = b43_radio_पढ़ो16(dev, 0x0052);
	backup[2] = b43_radio_पढ़ो16(dev, 0x0043);
	backup[3] = b43_phy_पढ़ो(dev, 0x0015);
	backup[4] = b43_phy_पढ़ो(dev, 0x005A);
	backup[5] = b43_phy_पढ़ो(dev, 0x0059);
	backup[6] = b43_phy_पढ़ो(dev, 0x0058);
	backup[8] = b43_पढ़ो16(dev, 0x03E6);
	backup[9] = b43_पढ़ो16(dev, B43_MMIO_CHANNEL_EXT);
	अगर (phy->rev >= 3) अणु
		backup[10] = b43_phy_पढ़ो(dev, 0x002E);
		backup[11] = b43_phy_पढ़ो(dev, 0x002F);
		backup[12] = b43_phy_पढ़ो(dev, 0x080F);
		backup[13] = b43_phy_पढ़ो(dev, B43_PHY_G_LO_CONTROL);
		backup[14] = b43_phy_पढ़ो(dev, 0x0801);
		backup[15] = b43_phy_पढ़ो(dev, 0x0060);
		backup[16] = b43_phy_पढ़ो(dev, 0x0014);
		backup[17] = b43_phy_पढ़ो(dev, 0x0478);
		b43_phy_ग_लिखो(dev, 0x002E, 0);
		b43_phy_ग_लिखो(dev, B43_PHY_G_LO_CONTROL, 0);
		चयन (phy->rev) अणु
		हाल 4:
		हाल 6:
		हाल 7:
			b43_phy_set(dev, 0x0478, 0x0100);
			b43_phy_set(dev, 0x0801, 0x0040);
			अवरोध;
		हाल 3:
		हाल 5:
			b43_phy_mask(dev, 0x0801, 0xFFBF);
			अवरोध;
		पूर्ण
		b43_phy_set(dev, 0x0060, 0x0040);
		b43_phy_set(dev, 0x0014, 0x0200);
	पूर्ण
	b43_radio_set(dev, 0x007A, 0x0070);
	b43_set_all_gains(dev, 0, 8, 0);
	b43_radio_mask(dev, 0x007A, 0x00F7);
	अगर (phy->rev >= 2) अणु
		b43_phy_maskset(dev, 0x0811, 0xFFCF, 0x0030);
		b43_phy_maskset(dev, 0x0812, 0xFFCF, 0x0010);
	पूर्ण
	b43_radio_set(dev, 0x007A, 0x0080);
	udelay(20);

	nrssi0 = (s16) ((b43_phy_पढ़ो(dev, 0x047F) >> 8) & 0x003F);
	अगर (nrssi0 >= 0x0020)
		nrssi0 -= 0x0040;

	b43_radio_mask(dev, 0x007A, 0x007F);
	अगर (phy->rev >= 2) अणु
		b43_phy_maskset(dev, 0x0003, 0xFF9F, 0x0040);
	पूर्ण

	b43_ग_लिखो16(dev, B43_MMIO_CHANNEL_EXT,
		    b43_पढ़ो16(dev, B43_MMIO_CHANNEL_EXT)
		    | 0x2000);
	b43_radio_set(dev, 0x007A, 0x000F);
	b43_phy_ग_लिखो(dev, 0x0015, 0xF330);
	अगर (phy->rev >= 2) अणु
		b43_phy_maskset(dev, 0x0812, 0xFFCF, 0x0020);
		b43_phy_maskset(dev, 0x0811, 0xFFCF, 0x0020);
	पूर्ण

	b43_set_all_gains(dev, 3, 0, 1);
	अगर (phy->radio_rev == 8) अणु
		b43_radio_ग_लिखो16(dev, 0x0043, 0x001F);
	पूर्ण अन्यथा अणु
		पंचांगp = b43_radio_पढ़ो16(dev, 0x0052) & 0xFF0F;
		b43_radio_ग_लिखो16(dev, 0x0052, पंचांगp | 0x0060);
		पंचांगp = b43_radio_पढ़ो16(dev, 0x0043) & 0xFFF0;
		b43_radio_ग_लिखो16(dev, 0x0043, पंचांगp | 0x0009);
	पूर्ण
	b43_phy_ग_लिखो(dev, 0x005A, 0x0480);
	b43_phy_ग_लिखो(dev, 0x0059, 0x0810);
	b43_phy_ग_लिखो(dev, 0x0058, 0x000D);
	udelay(20);
	nrssi1 = (s16) ((b43_phy_पढ़ो(dev, 0x047F) >> 8) & 0x003F);
	अगर (nrssi1 >= 0x0020)
		nrssi1 -= 0x0040;
	अगर (nrssi0 == nrssi1)
		gphy->nrssislope = 0x00010000;
	अन्यथा
		gphy->nrssislope = 0x00400000 / (nrssi0 - nrssi1);
	अगर (nrssi0 >= -4) अणु
		gphy->nrssi[0] = nrssi1;
		gphy->nrssi[1] = nrssi0;
	पूर्ण
	अगर (phy->rev >= 3) अणु
		b43_phy_ग_लिखो(dev, 0x002E, backup[10]);
		b43_phy_ग_लिखो(dev, 0x002F, backup[11]);
		b43_phy_ग_लिखो(dev, 0x080F, backup[12]);
		b43_phy_ग_लिखो(dev, B43_PHY_G_LO_CONTROL, backup[13]);
	पूर्ण
	अगर (phy->rev >= 2) अणु
		b43_phy_mask(dev, 0x0812, 0xFFCF);
		b43_phy_mask(dev, 0x0811, 0xFFCF);
	पूर्ण

	b43_radio_ग_लिखो16(dev, 0x007A, backup[0]);
	b43_radio_ग_लिखो16(dev, 0x0052, backup[1]);
	b43_radio_ग_लिखो16(dev, 0x0043, backup[2]);
	b43_ग_लिखो16(dev, 0x03E2, backup[7]);
	b43_ग_लिखो16(dev, 0x03E6, backup[8]);
	b43_ग_लिखो16(dev, B43_MMIO_CHANNEL_EXT, backup[9]);
	b43_phy_ग_लिखो(dev, 0x0015, backup[3]);
	b43_phy_ग_लिखो(dev, 0x005A, backup[4]);
	b43_phy_ग_लिखो(dev, 0x0059, backup[5]);
	b43_phy_ग_लिखो(dev, 0x0058, backup[6]);
	b43_synth_pu_workaround(dev, phy->channel);
	b43_phy_set(dev, 0x0802, (0x0001 | 0x0002));
	b43_set_original_gains(dev);
	b43_phy_set(dev, B43_PHY_G_CRS, 0x8000);
	अगर (phy->rev >= 3) अणु
		b43_phy_ग_लिखो(dev, 0x0801, backup[14]);
		b43_phy_ग_लिखो(dev, 0x0060, backup[15]);
		b43_phy_ग_लिखो(dev, 0x0014, backup[16]);
		b43_phy_ग_लिखो(dev, 0x0478, backup[17]);
	पूर्ण
	b43_nrssi_mem_update(dev);
	b43_calc_nrssi_threshold(dev);
पूर्ण

अटल व्योम b43_calc_nrssi_threshold(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	s32 a, b;
	s16 पंचांगp16;
	u16 पंचांगp_u16;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);

	अगर (!phy->gmode ||
	    !(dev->dev->bus_sprom->boardflags_lo & B43_BFL_RSSI)) अणु
		पंचांगp16 = b43_nrssi_hw_पढ़ो(dev, 0x20);
		अगर (पंचांगp16 >= 0x20)
			पंचांगp16 -= 0x40;
		अगर (पंचांगp16 < 3) अणु
			b43_phy_maskset(dev, 0x048A, 0xF000, 0x09EB);
		पूर्ण अन्यथा अणु
			b43_phy_maskset(dev, 0x048A, 0xF000, 0x0AED);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (gphy->पूर्णांकerभ_शेषe == B43_INTERFMODE_NONWLAN) अणु
			a = 0xE;
			b = 0xA;
		पूर्ण अन्यथा अगर (!gphy->aci_wlan_स्वतःmatic && gphy->aci_enable) अणु
			a = 0x13;
			b = 0x12;
		पूर्ण अन्यथा अणु
			a = 0xE;
			b = 0x11;
		पूर्ण

		a = a * (gphy->nrssi[1] - gphy->nrssi[0]);
		a += (gphy->nrssi[0] << 6);
		अगर (a < 32)
			a += 31;
		अन्यथा
			a += 32;
		a = a >> 6;
		a = clamp_val(a, -31, 31);

		b = b * (gphy->nrssi[1] - gphy->nrssi[0]);
		b += (gphy->nrssi[0] << 6);
		अगर (b < 32)
			b += 31;
		अन्यथा
			b += 32;
		b = b >> 6;
		b = clamp_val(b, -31, 31);

		पंचांगp_u16 = b43_phy_पढ़ो(dev, 0x048A) & 0xF000;
		पंचांगp_u16 |= ((u32) b & 0x0000003F);
		पंचांगp_u16 |= (((u32) a & 0x0000003F) << 6);
		b43_phy_ग_लिखो(dev, 0x048A, पंचांगp_u16);
	पूर्ण
पूर्ण

/* Stack implementation to save/restore values from the
 * पूर्णांकerference mitigation code.
 * It is save to restore values in अक्रमom order.
 */
अटल व्योम _stack_save(u32 *_stackptr, माप_प्रकार *stackidx,
			u8 id, u16 offset, u16 value)
अणु
	u32 *stackptr = &(_stackptr[*stackidx]);

	B43_WARN_ON(offset & 0xF000);
	B43_WARN_ON(id & 0xF0);
	*stackptr = offset;
	*stackptr |= ((u32) id) << 12;
	*stackptr |= ((u32) value) << 16;
	(*stackidx)++;
	B43_WARN_ON(*stackidx >= B43_INTERFSTACK_SIZE);
पूर्ण

अटल u16 _stack_restore(u32 *stackptr, u8 id, u16 offset)
अणु
	माप_प्रकार i;

	B43_WARN_ON(offset & 0xF000);
	B43_WARN_ON(id & 0xF0);
	क्रम (i = 0; i < B43_INTERFSTACK_SIZE; i++, stackptr++) अणु
		अगर ((*stackptr & 0x00000FFF) != offset)
			जारी;
		अगर (((*stackptr & 0x0000F000) >> 12) != id)
			जारी;
		वापस ((*stackptr & 0xFFFF0000) >> 16);
	पूर्ण
	B43_WARN_ON(1);

	वापस 0;
पूर्ण

#घोषणा phy_stacksave(offset)					\
	करो अणु							\
		_stack_save(stack, &stackidx, 0x1, (offset),	\
			    b43_phy_पढ़ो(dev, (offset)));	\
	पूर्ण जबतक (0)
#घोषणा phy_stackrestore(offset)				\
	करो अणु							\
		b43_phy_ग_लिखो(dev, (offset),		\
				  _stack_restore(stack, 0x1,	\
						 (offset)));	\
	पूर्ण जबतक (0)
#घोषणा radio_stacksave(offset)						\
	करो अणु								\
		_stack_save(stack, &stackidx, 0x2, (offset),		\
			    b43_radio_पढ़ो16(dev, (offset)));	\
	पूर्ण जबतक (0)
#घोषणा radio_stackrestore(offset)					\
	करो अणु								\
		b43_radio_ग_लिखो16(dev, (offset),			\
				      _stack_restore(stack, 0x2,	\
						     (offset)));	\
	पूर्ण जबतक (0)
#घोषणा ofdmtab_stacksave(table, offset)			\
	करो अणु							\
		_stack_save(stack, &stackidx, 0x3, (offset)|(table),	\
			    b43_ofdmtab_पढ़ो16(dev, (table), (offset)));	\
	पूर्ण जबतक (0)
#घोषणा ofdmtab_stackrestore(table, offset)			\
	करो अणु							\
		b43_ofdmtab_ग_लिखो16(dev, (table),	(offset),	\
				  _stack_restore(stack, 0x3,	\
						 (offset)|(table)));	\
	पूर्ण जबतक (0)

अटल व्योम
b43_radio_पूर्णांकerference_mitigation_enable(काष्ठा b43_wldev *dev, पूर्णांक mode)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u16 पंचांगp, flipped;
	माप_प्रकार stackidx = 0;
	u32 *stack = gphy->पूर्णांकerfstack;

	चयन (mode) अणु
	हाल B43_INTERFMODE_NONWLAN:
		अगर (phy->rev != 1) अणु
			b43_phy_set(dev, 0x042B, 0x0800);
			b43_phy_mask(dev, B43_PHY_G_CRS, ~0x4000);
			अवरोध;
		पूर्ण
		radio_stacksave(0x0078);
		पंचांगp = (b43_radio_पढ़ो16(dev, 0x0078) & 0x001E);
		B43_WARN_ON(पंचांगp > 15);
		flipped = bitrev4(पंचांगp);
		अगर (flipped < 10 && flipped >= 8)
			flipped = 7;
		अन्यथा अगर (flipped >= 10)
			flipped -= 3;
		flipped = (bitrev4(flipped) << 1) | 0x0020;
		b43_radio_ग_लिखो16(dev, 0x0078, flipped);

		b43_calc_nrssi_threshold(dev);

		phy_stacksave(0x0406);
		b43_phy_ग_लिखो(dev, 0x0406, 0x7E28);

		b43_phy_set(dev, 0x042B, 0x0800);
		b43_phy_set(dev, B43_PHY_RADIO_BITFIELD, 0x1000);

		phy_stacksave(0x04A0);
		b43_phy_maskset(dev, 0x04A0, 0xC0C0, 0x0008);
		phy_stacksave(0x04A1);
		b43_phy_maskset(dev, 0x04A1, 0xC0C0, 0x0605);
		phy_stacksave(0x04A2);
		b43_phy_maskset(dev, 0x04A2, 0xC0C0, 0x0204);
		phy_stacksave(0x04A8);
		b43_phy_maskset(dev, 0x04A8, 0xC0C0, 0x0803);
		phy_stacksave(0x04AB);
		b43_phy_maskset(dev, 0x04AB, 0xC0C0, 0x0605);

		phy_stacksave(0x04A7);
		b43_phy_ग_लिखो(dev, 0x04A7, 0x0002);
		phy_stacksave(0x04A3);
		b43_phy_ग_लिखो(dev, 0x04A3, 0x287A);
		phy_stacksave(0x04A9);
		b43_phy_ग_लिखो(dev, 0x04A9, 0x2027);
		phy_stacksave(0x0493);
		b43_phy_ग_लिखो(dev, 0x0493, 0x32F5);
		phy_stacksave(0x04AA);
		b43_phy_ग_लिखो(dev, 0x04AA, 0x2027);
		phy_stacksave(0x04AC);
		b43_phy_ग_लिखो(dev, 0x04AC, 0x32F5);
		अवरोध;
	हाल B43_INTERFMODE_MANUALWLAN:
		अगर (b43_phy_पढ़ो(dev, 0x0033) & 0x0800)
			अवरोध;

		gphy->aci_enable = true;

		phy_stacksave(B43_PHY_RADIO_BITFIELD);
		phy_stacksave(B43_PHY_G_CRS);
		अगर (phy->rev < 2) अणु
			phy_stacksave(0x0406);
		पूर्ण अन्यथा अणु
			phy_stacksave(0x04C0);
			phy_stacksave(0x04C1);
		पूर्ण
		phy_stacksave(0x0033);
		phy_stacksave(0x04A7);
		phy_stacksave(0x04A3);
		phy_stacksave(0x04A9);
		phy_stacksave(0x04AA);
		phy_stacksave(0x04AC);
		phy_stacksave(0x0493);
		phy_stacksave(0x04A1);
		phy_stacksave(0x04A0);
		phy_stacksave(0x04A2);
		phy_stacksave(0x048A);
		phy_stacksave(0x04A8);
		phy_stacksave(0x04AB);
		अगर (phy->rev == 2) अणु
			phy_stacksave(0x04AD);
			phy_stacksave(0x04AE);
		पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
			phy_stacksave(0x04AD);
			phy_stacksave(0x0415);
			phy_stacksave(0x0416);
			phy_stacksave(0x0417);
			ofdmtab_stacksave(0x1A00, 0x2);
			ofdmtab_stacksave(0x1A00, 0x3);
		पूर्ण
		phy_stacksave(0x042B);
		phy_stacksave(0x048C);

		b43_phy_mask(dev, B43_PHY_RADIO_BITFIELD, ~0x1000);
		b43_phy_maskset(dev, B43_PHY_G_CRS, 0xFFFC, 0x0002);

		b43_phy_ग_लिखो(dev, 0x0033, 0x0800);
		b43_phy_ग_लिखो(dev, 0x04A3, 0x2027);
		b43_phy_ग_लिखो(dev, 0x04A9, 0x1CA8);
		b43_phy_ग_लिखो(dev, 0x0493, 0x287A);
		b43_phy_ग_लिखो(dev, 0x04AA, 0x1CA8);
		b43_phy_ग_लिखो(dev, 0x04AC, 0x287A);

		b43_phy_maskset(dev, 0x04A0, 0xFFC0, 0x001A);
		b43_phy_ग_लिखो(dev, 0x04A7, 0x000D);

		अगर (phy->rev < 2) अणु
			b43_phy_ग_लिखो(dev, 0x0406, 0xFF0D);
		पूर्ण अन्यथा अगर (phy->rev == 2) अणु
			b43_phy_ग_लिखो(dev, 0x04C0, 0xFFFF);
			b43_phy_ग_लिखो(dev, 0x04C1, 0x00A9);
		पूर्ण अन्यथा अणु
			b43_phy_ग_लिखो(dev, 0x04C0, 0x00C1);
			b43_phy_ग_लिखो(dev, 0x04C1, 0x0059);
		पूर्ण

		b43_phy_maskset(dev, 0x04A1, 0xC0FF, 0x1800);
		b43_phy_maskset(dev, 0x04A1, 0xFFC0, 0x0015);
		b43_phy_maskset(dev, 0x04A8, 0xCFFF, 0x1000);
		b43_phy_maskset(dev, 0x04A8, 0xF0FF, 0x0A00);
		b43_phy_maskset(dev, 0x04AB, 0xCFFF, 0x1000);
		b43_phy_maskset(dev, 0x04AB, 0xF0FF, 0x0800);
		b43_phy_maskset(dev, 0x04AB, 0xFFCF, 0x0010);
		b43_phy_maskset(dev, 0x04AB, 0xFFF0, 0x0005);
		b43_phy_maskset(dev, 0x04A8, 0xFFCF, 0x0010);
		b43_phy_maskset(dev, 0x04A8, 0xFFF0, 0x0006);
		b43_phy_maskset(dev, 0x04A2, 0xF0FF, 0x0800);
		b43_phy_maskset(dev, 0x04A0, 0xF0FF, 0x0500);
		b43_phy_maskset(dev, 0x04A2, 0xFFF0, 0x000B);

		अगर (phy->rev >= 3) अणु
			b43_phy_mask(dev, 0x048A, 0x7FFF);
			b43_phy_maskset(dev, 0x0415, 0x8000, 0x36D8);
			b43_phy_maskset(dev, 0x0416, 0x8000, 0x36D8);
			b43_phy_maskset(dev, 0x0417, 0xFE00, 0x016D);
		पूर्ण अन्यथा अणु
			b43_phy_set(dev, 0x048A, 0x1000);
			b43_phy_maskset(dev, 0x048A, 0x9FFF, 0x2000);
			b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) | B43_HF_ACIW);
		पूर्ण
		अगर (phy->rev >= 2) अणु
			b43_phy_set(dev, 0x042B, 0x0800);
		पूर्ण
		b43_phy_maskset(dev, 0x048C, 0xF0FF, 0x0200);
		अगर (phy->rev == 2) अणु
			b43_phy_maskset(dev, 0x04AE, 0xFF00, 0x007F);
			b43_phy_maskset(dev, 0x04AD, 0x00FF, 0x1300);
		पूर्ण अन्यथा अगर (phy->rev >= 6) अणु
			b43_ofdmtab_ग_लिखो16(dev, 0x1A00, 0x3, 0x007F);
			b43_ofdmtab_ग_लिखो16(dev, 0x1A00, 0x2, 0x007F);
			b43_phy_mask(dev, 0x04AD, 0x00FF);
		पूर्ण
		b43_calc_nrssi_slope(dev);
		अवरोध;
	शेष:
		B43_WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम
b43_radio_पूर्णांकerference_mitigation_disable(काष्ठा b43_wldev *dev, पूर्णांक mode)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u32 *stack = gphy->पूर्णांकerfstack;

	चयन (mode) अणु
	हाल B43_INTERFMODE_NONWLAN:
		अगर (phy->rev != 1) अणु
			b43_phy_mask(dev, 0x042B, ~0x0800);
			b43_phy_set(dev, B43_PHY_G_CRS, 0x4000);
			अवरोध;
		पूर्ण
		radio_stackrestore(0x0078);
		b43_calc_nrssi_threshold(dev);
		phy_stackrestore(0x0406);
		b43_phy_mask(dev, 0x042B, ~0x0800);
		अगर (!dev->bad_frames_preempt) अणु
			b43_phy_mask(dev, B43_PHY_RADIO_BITFIELD, ~(1 << 11));
		पूर्ण
		b43_phy_set(dev, B43_PHY_G_CRS, 0x4000);
		phy_stackrestore(0x04A0);
		phy_stackrestore(0x04A1);
		phy_stackrestore(0x04A2);
		phy_stackrestore(0x04A8);
		phy_stackrestore(0x04AB);
		phy_stackrestore(0x04A7);
		phy_stackrestore(0x04A3);
		phy_stackrestore(0x04A9);
		phy_stackrestore(0x0493);
		phy_stackrestore(0x04AA);
		phy_stackrestore(0x04AC);
		अवरोध;
	हाल B43_INTERFMODE_MANUALWLAN:
		अगर (!(b43_phy_पढ़ो(dev, 0x0033) & 0x0800))
			अवरोध;

		gphy->aci_enable = false;

		phy_stackrestore(B43_PHY_RADIO_BITFIELD);
		phy_stackrestore(B43_PHY_G_CRS);
		phy_stackrestore(0x0033);
		phy_stackrestore(0x04A3);
		phy_stackrestore(0x04A9);
		phy_stackrestore(0x0493);
		phy_stackrestore(0x04AA);
		phy_stackrestore(0x04AC);
		phy_stackrestore(0x04A0);
		phy_stackrestore(0x04A7);
		अगर (phy->rev >= 2) अणु
			phy_stackrestore(0x04C0);
			phy_stackrestore(0x04C1);
		पूर्ण अन्यथा
			phy_stackrestore(0x0406);
		phy_stackrestore(0x04A1);
		phy_stackrestore(0x04AB);
		phy_stackrestore(0x04A8);
		अगर (phy->rev == 2) अणु
			phy_stackrestore(0x04AD);
			phy_stackrestore(0x04AE);
		पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
			phy_stackrestore(0x04AD);
			phy_stackrestore(0x0415);
			phy_stackrestore(0x0416);
			phy_stackrestore(0x0417);
			ofdmtab_stackrestore(0x1A00, 0x2);
			ofdmtab_stackrestore(0x1A00, 0x3);
		पूर्ण
		phy_stackrestore(0x04A2);
		phy_stackrestore(0x048A);
		phy_stackrestore(0x042B);
		phy_stackrestore(0x048C);
		b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) & ~B43_HF_ACIW);
		b43_calc_nrssi_slope(dev);
		अवरोध;
	शेष:
		B43_WARN_ON(1);
	पूर्ण
पूर्ण

#अघोषित phy_stacksave
#अघोषित phy_stackrestore
#अघोषित radio_stacksave
#अघोषित radio_stackrestore
#अघोषित ofdmtab_stacksave
#अघोषित ofdmtab_stackrestore

अटल u16 b43_radio_core_calibration_value(काष्ठा b43_wldev *dev)
अणु
	u16 reg, index, ret;

	अटल स्थिर u8 rcc_table[] = अणु
		0x02, 0x03, 0x01, 0x0F,
		0x06, 0x07, 0x05, 0x0F,
		0x0A, 0x0B, 0x09, 0x0F,
		0x0E, 0x0F, 0x0D, 0x0F,
	पूर्ण;

	reg = b43_radio_पढ़ो16(dev, 0x60);
	index = (reg & 0x001E) >> 1;
	ret = rcc_table[index] << 1;
	ret |= (reg & 0x0001);
	ret |= 0x0020;

	वापस ret;
पूर्ण

#घोषणा LPD(L, P, D)	(((L) << 2) | ((P) << 1) | ((D) << 0))
अटल u16 radio2050_rfover_val(काष्ठा b43_wldev *dev,
				u16 phy_रेजिस्टर, अचिन्हित पूर्णांक lpd)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;

	अगर (!phy->gmode)
		वापस 0;

	अगर (has_loopback_gain(phy)) अणु
		पूर्णांक max_lb_gain = gphy->max_lb_gain;
		u16 extlna;
		u16 i;

		अगर (phy->radio_rev == 8)
			max_lb_gain += 0x3E;
		अन्यथा
			max_lb_gain += 0x26;
		अगर (max_lb_gain >= 0x46) अणु
			extlna = 0x3000;
			max_lb_gain -= 0x46;
		पूर्ण अन्यथा अगर (max_lb_gain >= 0x3A) अणु
			extlna = 0x1000;
			max_lb_gain -= 0x3A;
		पूर्ण अन्यथा अगर (max_lb_gain >= 0x2E) अणु
			extlna = 0x2000;
			max_lb_gain -= 0x2E;
		पूर्ण अन्यथा अणु
			extlna = 0;
			max_lb_gain -= 0x10;
		पूर्ण

		क्रम (i = 0; i < 16; i++) अणु
			max_lb_gain -= (i * 6);
			अगर (max_lb_gain < 6)
				अवरोध;
		पूर्ण

		अगर ((phy->rev < 7) ||
		    !(sprom->boardflags_lo & B43_BFL_EXTLNA)) अणु
			अगर (phy_रेजिस्टर == B43_PHY_RFOVER) अणु
				वापस 0x1B3;
			पूर्ण अन्यथा अगर (phy_रेजिस्टर == B43_PHY_RFOVERVAL) अणु
				extlna |= (i << 8);
				चयन (lpd) अणु
				हाल LPD(0, 1, 1):
					वापस 0x0F92;
				हाल LPD(0, 0, 1):
				हाल LPD(1, 0, 1):
					वापस (0x0092 | extlna);
				हाल LPD(1, 0, 0):
					वापस (0x0093 | extlna);
				पूर्ण
				B43_WARN_ON(1);
			पूर्ण
			B43_WARN_ON(1);
		पूर्ण अन्यथा अणु
			अगर (phy_रेजिस्टर == B43_PHY_RFOVER) अणु
				वापस 0x9B3;
			पूर्ण अन्यथा अगर (phy_रेजिस्टर == B43_PHY_RFOVERVAL) अणु
				अगर (extlna)
					extlna |= 0x8000;
				extlna |= (i << 8);
				चयन (lpd) अणु
				हाल LPD(0, 1, 1):
					वापस 0x8F92;
				हाल LPD(0, 0, 1):
					वापस (0x8092 | extlna);
				हाल LPD(1, 0, 1):
					वापस (0x2092 | extlna);
				हाल LPD(1, 0, 0):
					वापस (0x2093 | extlna);
				पूर्ण
				B43_WARN_ON(1);
			पूर्ण
			B43_WARN_ON(1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((phy->rev < 7) ||
		    !(sprom->boardflags_lo & B43_BFL_EXTLNA)) अणु
			अगर (phy_रेजिस्टर == B43_PHY_RFOVER) अणु
				वापस 0x1B3;
			पूर्ण अन्यथा अगर (phy_रेजिस्टर == B43_PHY_RFOVERVAL) अणु
				चयन (lpd) अणु
				हाल LPD(0, 1, 1):
					वापस 0x0FB2;
				हाल LPD(0, 0, 1):
					वापस 0x00B2;
				हाल LPD(1, 0, 1):
					वापस 0x30B2;
				हाल LPD(1, 0, 0):
					वापस 0x30B3;
				पूर्ण
				B43_WARN_ON(1);
			पूर्ण
			B43_WARN_ON(1);
		पूर्ण अन्यथा अणु
			अगर (phy_रेजिस्टर == B43_PHY_RFOVER) अणु
				वापस 0x9B3;
			पूर्ण अन्यथा अगर (phy_रेजिस्टर == B43_PHY_RFOVERVAL) अणु
				चयन (lpd) अणु
				हाल LPD(0, 1, 1):
					वापस 0x8FB2;
				हाल LPD(0, 0, 1):
					वापस 0x80B2;
				हाल LPD(1, 0, 1):
					वापस 0x20B2;
				हाल LPD(1, 0, 0):
					वापस 0x20B3;
				पूर्ण
				B43_WARN_ON(1);
			पूर्ण
			B43_WARN_ON(1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा init2050_saved_values अणु
	/* Core रेजिस्टरs */
	u16 reg_3EC;
	u16 reg_3E6;
	u16 reg_3F4;
	/* Radio रेजिस्टरs */
	u16 radio_43;
	u16 radio_51;
	u16 radio_52;
	/* PHY रेजिस्टरs */
	u16 phy_pgactl;
	u16 phy_cck_5A;
	u16 phy_cck_59;
	u16 phy_cck_58;
	u16 phy_cck_30;
	u16 phy_rfover;
	u16 phy_rfoverval;
	u16 phy_analogover;
	u16 phy_analogoverval;
	u16 phy_crs0;
	u16 phy_classctl;
	u16 phy_lo_mask;
	u16 phy_lo_ctl;
	u16 phy_syncctl;
पूर्ण;

अटल u16 b43_radio_init2050(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा init2050_saved_values sav;
	u16 rcc;
	u16 radio78;
	u16 ret;
	u16 i, j;
	u32 पंचांगp1 = 0, पंचांगp2 = 0;

	स_रखो(&sav, 0, माप(sav));	/* get rid of "may be used uninitialized..." */

	sav.radio_43 = b43_radio_पढ़ो16(dev, 0x43);
	sav.radio_51 = b43_radio_पढ़ो16(dev, 0x51);
	sav.radio_52 = b43_radio_पढ़ो16(dev, 0x52);
	sav.phy_pgactl = b43_phy_पढ़ो(dev, B43_PHY_PGACTL);
	sav.phy_cck_5A = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x5A));
	sav.phy_cck_59 = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x59));
	sav.phy_cck_58 = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x58));

	अगर (phy->type == B43_PHYTYPE_B) अणु
		sav.phy_cck_30 = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x30));
		sav.reg_3EC = b43_पढ़ो16(dev, 0x3EC);

		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x30), 0xFF);
		b43_ग_लिखो16(dev, 0x3EC, 0x3F3F);
	पूर्ण अन्यथा अगर (phy->gmode || phy->rev >= 2) अणु
		sav.phy_rfover = b43_phy_पढ़ो(dev, B43_PHY_RFOVER);
		sav.phy_rfoverval = b43_phy_पढ़ो(dev, B43_PHY_RFOVERVAL);
		sav.phy_analogover = b43_phy_पढ़ो(dev, B43_PHY_ANALOGOVER);
		sav.phy_analogoverval =
		    b43_phy_पढ़ो(dev, B43_PHY_ANALOGOVERVAL);
		sav.phy_crs0 = b43_phy_पढ़ो(dev, B43_PHY_CRS0);
		sav.phy_classctl = b43_phy_पढ़ो(dev, B43_PHY_CLASSCTL);

		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0003);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFC);
		b43_phy_mask(dev, B43_PHY_CRS0, 0x7FFF);
		b43_phy_mask(dev, B43_PHY_CLASSCTL, 0xFFFC);
		अगर (has_loopback_gain(phy)) अणु
			sav.phy_lo_mask = b43_phy_पढ़ो(dev, B43_PHY_LO_MASK);
			sav.phy_lo_ctl = b43_phy_पढ़ो(dev, B43_PHY_LO_CTL);

			अगर (phy->rev >= 3)
				b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, 0xC020);
			अन्यथा
				b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, 0x8020);
			b43_phy_ग_लिखो(dev, B43_PHY_LO_CTL, 0);
		पूर्ण

		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
			      radio2050_rfover_val(dev, B43_PHY_RFOVERVAL,
						   LPD(0, 1, 1)));
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVER,
			      radio2050_rfover_val(dev, B43_PHY_RFOVER, 0));
	पूर्ण
	b43_ग_लिखो16(dev, 0x3E2, b43_पढ़ो16(dev, 0x3E2) | 0x8000);

	sav.phy_syncctl = b43_phy_पढ़ो(dev, B43_PHY_SYNCCTL);
	b43_phy_mask(dev, B43_PHY_SYNCCTL, 0xFF7F);
	sav.reg_3E6 = b43_पढ़ो16(dev, 0x3E6);
	sav.reg_3F4 = b43_पढ़ो16(dev, 0x3F4);

	अगर (phy->analog == 0) अणु
		b43_ग_लिखो16(dev, 0x03E6, 0x0122);
	पूर्ण अन्यथा अणु
		अगर (phy->analog >= 2) अणु
			b43_phy_maskset(dev, B43_PHY_CCK(0x03), 0xFFBF, 0x40);
		पूर्ण
		b43_ग_लिखो16(dev, B43_MMIO_CHANNEL_EXT,
			    (b43_पढ़ो16(dev, B43_MMIO_CHANNEL_EXT) | 0x2000));
	पूर्ण

	rcc = b43_radio_core_calibration_value(dev);

	अगर (phy->type == B43_PHYTYPE_B)
		b43_radio_ग_लिखो16(dev, 0x78, 0x26);
	अगर (phy->gmode || phy->rev >= 2) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
			      radio2050_rfover_val(dev, B43_PHY_RFOVERVAL,
						   LPD(0, 1, 1)));
	पूर्ण
	b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xBFAF);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2B), 0x1403);
	अगर (phy->gmode || phy->rev >= 2) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
			      radio2050_rfover_val(dev, B43_PHY_RFOVERVAL,
						   LPD(0, 0, 1)));
	पूर्ण
	b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xBFA0);
	b43_radio_set(dev, 0x51, 0x0004);
	अगर (phy->radio_rev == 8) अणु
		b43_radio_ग_लिखो16(dev, 0x43, 0x1F);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो16(dev, 0x52, 0);
		b43_radio_maskset(dev, 0x43, 0xFFF0, 0x0009);
	पूर्ण
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x58), 0);

	क्रम (i = 0; i < 16; i++) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x5A), 0x0480);
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x59), 0xC810);
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x58), 0x000D);
		अगर (phy->gmode || phy->rev >= 2) अणु
			b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
				      radio2050_rfover_val(dev,
							   B43_PHY_RFOVERVAL,
							   LPD(1, 0, 1)));
		पूर्ण
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xAFB0);
		udelay(10);
		अगर (phy->gmode || phy->rev >= 2) अणु
			b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
				      radio2050_rfover_val(dev,
							   B43_PHY_RFOVERVAL,
							   LPD(1, 0, 1)));
		पूर्ण
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xEFB0);
		udelay(10);
		अगर (phy->gmode || phy->rev >= 2) अणु
			b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
				      radio2050_rfover_val(dev,
							   B43_PHY_RFOVERVAL,
							   LPD(1, 0, 0)));
		पूर्ण
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xFFF0);
		udelay(20);
		पंचांगp1 += b43_phy_पढ़ो(dev, B43_PHY_LO_LEAKAGE);
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x58), 0);
		अगर (phy->gmode || phy->rev >= 2) अणु
			b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
				      radio2050_rfover_val(dev,
							   B43_PHY_RFOVERVAL,
							   LPD(1, 0, 1)));
		पूर्ण
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xAFB0);
	पूर्ण
	udelay(10);

	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x58), 0);
	पंचांगp1++;
	पंचांगp1 >>= 9;

	क्रम (i = 0; i < 16; i++) अणु
		radio78 = (bitrev4(i) << 1) | 0x0020;
		b43_radio_ग_लिखो16(dev, 0x78, radio78);
		udelay(10);
		क्रम (j = 0; j < 16; j++) अणु
			b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x5A), 0x0D80);
			b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x59), 0xC810);
			b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x58), 0x000D);
			अगर (phy->gmode || phy->rev >= 2) अणु
				b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
					      radio2050_rfover_val(dev,
								   B43_PHY_RFOVERVAL,
								   LPD(1, 0,
								       1)));
			पूर्ण
			b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xAFB0);
			udelay(10);
			अगर (phy->gmode || phy->rev >= 2) अणु
				b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
					      radio2050_rfover_val(dev,
								   B43_PHY_RFOVERVAL,
								   LPD(1, 0,
								       1)));
			पूर्ण
			b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xEFB0);
			udelay(10);
			अगर (phy->gmode || phy->rev >= 2) अणु
				b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
					      radio2050_rfover_val(dev,
								   B43_PHY_RFOVERVAL,
								   LPD(1, 0,
								       0)));
			पूर्ण
			b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xFFF0);
			udelay(10);
			पंचांगp2 += b43_phy_पढ़ो(dev, B43_PHY_LO_LEAKAGE);
			b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x58), 0);
			अगर (phy->gmode || phy->rev >= 2) अणु
				b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
					      radio2050_rfover_val(dev,
								   B43_PHY_RFOVERVAL,
								   LPD(1, 0,
								       1)));
			पूर्ण
			b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xAFB0);
		पूर्ण
		पंचांगp2++;
		पंचांगp2 >>= 8;
		अगर (पंचांगp1 < पंचांगp2)
			अवरोध;
	पूर्ण

	/* Restore the रेजिस्टरs */
	b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, sav.phy_pgactl);
	b43_radio_ग_लिखो16(dev, 0x51, sav.radio_51);
	b43_radio_ग_लिखो16(dev, 0x52, sav.radio_52);
	b43_radio_ग_लिखो16(dev, 0x43, sav.radio_43);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x5A), sav.phy_cck_5A);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x59), sav.phy_cck_59);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x58), sav.phy_cck_58);
	b43_ग_लिखो16(dev, 0x3E6, sav.reg_3E6);
	अगर (phy->analog != 0)
		b43_ग_लिखो16(dev, 0x3F4, sav.reg_3F4);
	b43_phy_ग_लिखो(dev, B43_PHY_SYNCCTL, sav.phy_syncctl);
	b43_synth_pu_workaround(dev, phy->channel);
	अगर (phy->type == B43_PHYTYPE_B) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x30), sav.phy_cck_30);
		b43_ग_लिखो16(dev, 0x3EC, sav.reg_3EC);
	पूर्ण अन्यथा अगर (phy->gmode) अणु
		b43_ग_लिखो16(dev, B43_MMIO_PHY_RADIO,
			    b43_पढ़ो16(dev, B43_MMIO_PHY_RADIO)
			    & 0x7FFF);
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, sav.phy_rfover);
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, sav.phy_rfoverval);
		b43_phy_ग_लिखो(dev, B43_PHY_ANALOGOVER, sav.phy_analogover);
		b43_phy_ग_लिखो(dev, B43_PHY_ANALOGOVERVAL,
			      sav.phy_analogoverval);
		b43_phy_ग_लिखो(dev, B43_PHY_CRS0, sav.phy_crs0);
		b43_phy_ग_लिखो(dev, B43_PHY_CLASSCTL, sav.phy_classctl);
		अगर (has_loopback_gain(phy)) अणु
			b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, sav.phy_lo_mask);
			b43_phy_ग_लिखो(dev, B43_PHY_LO_CTL, sav.phy_lo_ctl);
		पूर्ण
	पूर्ण
	अगर (i > 15)
		ret = radio78;
	अन्यथा
		ret = rcc;

	वापस ret;
पूर्ण

अटल व्योम b43_phy_initb5(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u16 offset, value;
	u8 old_channel;

	अगर (phy->analog == 1) अणु
		b43_radio_set(dev, 0x007A, 0x0050);
	पूर्ण
	अगर ((dev->dev->board_venकरोr != SSB_BOARDVENDOR_BCM) &&
	    (dev->dev->board_type != SSB_BOARD_BU4306)) अणु
		value = 0x2120;
		क्रम (offset = 0x00A8; offset < 0x00C7; offset++) अणु
			b43_phy_ग_लिखो(dev, offset, value);
			value += 0x202;
		पूर्ण
	पूर्ण
	b43_phy_maskset(dev, 0x0035, 0xF0FF, 0x0700);
	अगर (phy->radio_ver == 0x2050)
		b43_phy_ग_लिखो(dev, 0x0038, 0x0667);

	अगर (phy->gmode || phy->rev >= 2) अणु
		अगर (phy->radio_ver == 0x2050) अणु
			b43_radio_set(dev, 0x007A, 0x0020);
			b43_radio_set(dev, 0x0051, 0x0004);
		पूर्ण
		b43_ग_लिखो16(dev, B43_MMIO_PHY_RADIO, 0x0000);

		b43_phy_set(dev, 0x0802, 0x0100);
		b43_phy_set(dev, 0x042B, 0x2000);

		b43_phy_ग_लिखो(dev, 0x001C, 0x186A);

		b43_phy_maskset(dev, 0x0013, 0x00FF, 0x1900);
		b43_phy_maskset(dev, 0x0035, 0xFFC0, 0x0064);
		b43_phy_maskset(dev, 0x005D, 0xFF80, 0x000A);
	पूर्ण

	अगर (dev->bad_frames_preempt) अणु
		b43_phy_set(dev, B43_PHY_RADIO_BITFIELD, (1 << 11));
	पूर्ण

	अगर (phy->analog == 1) अणु
		b43_phy_ग_लिखो(dev, 0x0026, 0xCE00);
		b43_phy_ग_लिखो(dev, 0x0021, 0x3763);
		b43_phy_ग_लिखो(dev, 0x0022, 0x1BC3);
		b43_phy_ग_लिखो(dev, 0x0023, 0x06F9);
		b43_phy_ग_लिखो(dev, 0x0024, 0x037E);
	पूर्ण अन्यथा
		b43_phy_ग_लिखो(dev, 0x0026, 0xCC00);
	b43_phy_ग_लिखो(dev, 0x0030, 0x00C6);
	b43_ग_लिखो16(dev, 0x03EC, 0x3F22);

	अगर (phy->analog == 1)
		b43_phy_ग_लिखो(dev, 0x0020, 0x3E1C);
	अन्यथा
		b43_phy_ग_लिखो(dev, 0x0020, 0x301C);

	अगर (phy->analog == 0)
		b43_ग_लिखो16(dev, 0x03E4, 0x3000);

	old_channel = phy->channel;
	/* Force to channel 7, even अगर not supported. */
	b43_gphy_channel_चयन(dev, 7, 0);

	अगर (phy->radio_ver != 0x2050) अणु
		b43_radio_ग_लिखो16(dev, 0x0075, 0x0080);
		b43_radio_ग_लिखो16(dev, 0x0079, 0x0081);
	पूर्ण

	b43_radio_ग_लिखो16(dev, 0x0050, 0x0020);
	b43_radio_ग_लिखो16(dev, 0x0050, 0x0023);

	अगर (phy->radio_ver == 0x2050) अणु
		b43_radio_ग_लिखो16(dev, 0x0050, 0x0020);
		b43_radio_ग_लिखो16(dev, 0x005A, 0x0070);
	पूर्ण

	b43_radio_ग_लिखो16(dev, 0x005B, 0x007B);
	b43_radio_ग_लिखो16(dev, 0x005C, 0x00B0);

	b43_radio_set(dev, 0x007A, 0x0007);

	b43_gphy_channel_चयन(dev, old_channel, 0);

	b43_phy_ग_लिखो(dev, 0x0014, 0x0080);
	b43_phy_ग_लिखो(dev, 0x0032, 0x00CA);
	b43_phy_ग_लिखो(dev, 0x002A, 0x88A3);

	b43_set_txघातer_g(dev, &gphy->bbatt, &gphy->rfatt, gphy->tx_control);

	अगर (phy->radio_ver == 0x2050)
		b43_radio_ग_लिखो16(dev, 0x005D, 0x000D);

	b43_ग_लिखो16(dev, 0x03E4, (b43_पढ़ो16(dev, 0x03E4) & 0xFFC0) | 0x0004);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/Init/B6 */
अटल व्योम b43_phy_initb6(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u16 offset, val;
	u8 old_channel;

	b43_phy_ग_लिखो(dev, 0x003E, 0x817A);
	b43_radio_ग_लिखो16(dev, 0x007A,
			  (b43_radio_पढ़ो16(dev, 0x007A) | 0x0058));
	अगर (phy->radio_rev == 4 || phy->radio_rev == 5) अणु
		b43_radio_ग_लिखो16(dev, 0x51, 0x37);
		b43_radio_ग_लिखो16(dev, 0x52, 0x70);
		b43_radio_ग_लिखो16(dev, 0x53, 0xB3);
		b43_radio_ग_लिखो16(dev, 0x54, 0x9B);
		b43_radio_ग_लिखो16(dev, 0x5A, 0x88);
		b43_radio_ग_लिखो16(dev, 0x5B, 0x88);
		b43_radio_ग_लिखो16(dev, 0x5D, 0x88);
		b43_radio_ग_लिखो16(dev, 0x5E, 0x88);
		b43_radio_ग_लिखो16(dev, 0x7D, 0x88);
		b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev)
			     | B43_HF_TSSIRPSMW);
	पूर्ण
	B43_WARN_ON(phy->radio_rev == 6 || phy->radio_rev == 7);	/* We had code क्रम these revs here... */
	अगर (phy->radio_rev == 8) अणु
		b43_radio_ग_लिखो16(dev, 0x51, 0);
		b43_radio_ग_लिखो16(dev, 0x52, 0x40);
		b43_radio_ग_लिखो16(dev, 0x53, 0xB7);
		b43_radio_ग_लिखो16(dev, 0x54, 0x98);
		b43_radio_ग_लिखो16(dev, 0x5A, 0x88);
		b43_radio_ग_लिखो16(dev, 0x5B, 0x6B);
		b43_radio_ग_लिखो16(dev, 0x5C, 0x0F);
		अगर (dev->dev->bus_sprom->boardflags_lo & B43_BFL_ALTIQ) अणु
			b43_radio_ग_लिखो16(dev, 0x5D, 0xFA);
			b43_radio_ग_लिखो16(dev, 0x5E, 0xD8);
		पूर्ण अन्यथा अणु
			b43_radio_ग_लिखो16(dev, 0x5D, 0xF5);
			b43_radio_ग_लिखो16(dev, 0x5E, 0xB8);
		पूर्ण
		b43_radio_ग_लिखो16(dev, 0x0073, 0x0003);
		b43_radio_ग_लिखो16(dev, 0x007D, 0x00A8);
		b43_radio_ग_लिखो16(dev, 0x007C, 0x0001);
		b43_radio_ग_लिखो16(dev, 0x007E, 0x0008);
	पूर्ण
	val = 0x1E1F;
	क्रम (offset = 0x0088; offset < 0x0098; offset++) अणु
		b43_phy_ग_लिखो(dev, offset, val);
		val -= 0x0202;
	पूर्ण
	val = 0x3E3F;
	क्रम (offset = 0x0098; offset < 0x00A8; offset++) अणु
		b43_phy_ग_लिखो(dev, offset, val);
		val -= 0x0202;
	पूर्ण
	val = 0x2120;
	क्रम (offset = 0x00A8; offset < 0x00C8; offset++) अणु
		b43_phy_ग_लिखो(dev, offset, (val & 0x3F3F));
		val += 0x0202;
	पूर्ण
	अगर (phy->type == B43_PHYTYPE_G) अणु
		b43_radio_set(dev, 0x007A, 0x0020);
		b43_radio_set(dev, 0x0051, 0x0004);
		b43_phy_set(dev, 0x0802, 0x0100);
		b43_phy_set(dev, 0x042B, 0x2000);
		b43_phy_ग_लिखो(dev, 0x5B, 0);
		b43_phy_ग_लिखो(dev, 0x5C, 0);
	पूर्ण

	old_channel = phy->channel;
	अगर (old_channel >= 8)
		b43_gphy_channel_चयन(dev, 1, 0);
	अन्यथा
		b43_gphy_channel_चयन(dev, 13, 0);

	b43_radio_ग_लिखो16(dev, 0x0050, 0x0020);
	b43_radio_ग_लिखो16(dev, 0x0050, 0x0023);
	udelay(40);
	अगर (phy->radio_rev < 6 || phy->radio_rev == 8) अणु
		b43_radio_ग_लिखो16(dev, 0x7C, (b43_radio_पढ़ो16(dev, 0x7C)
					      | 0x0002));
		b43_radio_ग_लिखो16(dev, 0x50, 0x20);
	पूर्ण
	अगर (phy->radio_rev <= 2) अणु
		b43_radio_ग_लिखो16(dev, 0x50, 0x20);
		b43_radio_ग_लिखो16(dev, 0x5A, 0x70);
		b43_radio_ग_लिखो16(dev, 0x5B, 0x7B);
		b43_radio_ग_लिखो16(dev, 0x5C, 0xB0);
	पूर्ण
	b43_radio_maskset(dev, 0x007A, 0x00F8, 0x0007);

	b43_gphy_channel_चयन(dev, old_channel, 0);

	b43_phy_ग_लिखो(dev, 0x0014, 0x0200);
	अगर (phy->radio_rev >= 6)
		b43_phy_ग_लिखो(dev, 0x2A, 0x88C2);
	अन्यथा
		b43_phy_ग_लिखो(dev, 0x2A, 0x8AC0);
	b43_phy_ग_लिखो(dev, 0x0038, 0x0668);
	b43_set_txघातer_g(dev, &gphy->bbatt, &gphy->rfatt, gphy->tx_control);
	अगर (phy->radio_rev == 4 || phy->radio_rev == 5)
		b43_phy_maskset(dev, 0x5D, 0xFF80, 0x0003);
	अगर (phy->radio_rev <= 2)
		b43_radio_ग_लिखो16(dev, 0x005D, 0x000D);

	अगर (phy->analog == 4) अणु
		b43_ग_लिखो16(dev, 0x3E4, 9);
		b43_phy_mask(dev, 0x61, 0x0FFF);
	पूर्ण अन्यथा अणु
		b43_phy_maskset(dev, 0x0002, 0xFFC0, 0x0004);
	पूर्ण
	अगर (phy->type == B43_PHYTYPE_B)
		B43_WARN_ON(1);
	अन्यथा अगर (phy->type == B43_PHYTYPE_G)
		b43_ग_लिखो16(dev, 0x03E6, 0x0);
पूर्ण

अटल व्योम b43_calc_loopback_gain(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u16 backup_phy[16] = अणु 0 पूर्ण;
	u16 backup_radio[3];
	u16 backup_bband;
	u16 i, j, loop_i_max;
	u16 trsw_rx;
	u16 loop1_outer_करोne, loop1_inner_करोne;

	backup_phy[0] = b43_phy_पढ़ो(dev, B43_PHY_CRS0);
	backup_phy[1] = b43_phy_पढ़ो(dev, B43_PHY_CCKBBANDCFG);
	backup_phy[2] = b43_phy_पढ़ो(dev, B43_PHY_RFOVER);
	backup_phy[3] = b43_phy_पढ़ो(dev, B43_PHY_RFOVERVAL);
	अगर (phy->rev != 1) अणु	/* Not in specs, but needed to prevent PPC machine check */
		backup_phy[4] = b43_phy_पढ़ो(dev, B43_PHY_ANALOGOVER);
		backup_phy[5] = b43_phy_पढ़ो(dev, B43_PHY_ANALOGOVERVAL);
	पूर्ण
	backup_phy[6] = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x5A));
	backup_phy[7] = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x59));
	backup_phy[8] = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x58));
	backup_phy[9] = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x0A));
	backup_phy[10] = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x03));
	backup_phy[11] = b43_phy_पढ़ो(dev, B43_PHY_LO_MASK);
	backup_phy[12] = b43_phy_पढ़ो(dev, B43_PHY_LO_CTL);
	backup_phy[13] = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x2B));
	backup_phy[14] = b43_phy_पढ़ो(dev, B43_PHY_PGACTL);
	backup_phy[15] = b43_phy_पढ़ो(dev, B43_PHY_LO_LEAKAGE);
	backup_bband = gphy->bbatt.att;
	backup_radio[0] = b43_radio_पढ़ो16(dev, 0x52);
	backup_radio[1] = b43_radio_पढ़ो16(dev, 0x43);
	backup_radio[2] = b43_radio_पढ़ो16(dev, 0x7A);

	b43_phy_mask(dev, B43_PHY_CRS0, 0x3FFF);
	b43_phy_set(dev, B43_PHY_CCKBBANDCFG, 0x8000);
	b43_phy_set(dev, B43_PHY_RFOVER, 0x0002);
	b43_phy_mask(dev, B43_PHY_RFOVERVAL, 0xFFFD);
	b43_phy_set(dev, B43_PHY_RFOVER, 0x0001);
	b43_phy_mask(dev, B43_PHY_RFOVERVAL, 0xFFFE);
	अगर (phy->rev != 1) अणु	/* Not in specs, but needed to prevent PPC machine check */
		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0001);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFE);
		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0002);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFD);
	पूर्ण
	b43_phy_set(dev, B43_PHY_RFOVER, 0x000C);
	b43_phy_set(dev, B43_PHY_RFOVERVAL, 0x000C);
	b43_phy_set(dev, B43_PHY_RFOVER, 0x0030);
	b43_phy_maskset(dev, B43_PHY_RFOVERVAL, 0xFFCF, 0x10);

	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x5A), 0x0780);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x59), 0xC810);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x58), 0x000D);

	b43_phy_set(dev, B43_PHY_CCK(0x0A), 0x2000);
	अगर (phy->rev != 1) अणु	/* Not in specs, but needed to prevent PPC machine check */
		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0004);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFB);
	पूर्ण
	b43_phy_maskset(dev, B43_PHY_CCK(0x03), 0xFF9F, 0x40);

	अगर (phy->radio_rev == 8) अणु
		b43_radio_ग_लिखो16(dev, 0x43, 0x000F);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो16(dev, 0x52, 0);
		b43_radio_maskset(dev, 0x43, 0xFFF0, 0x9);
	पूर्ण
	b43_gphy_set_baseband_attenuation(dev, 11);

	अगर (phy->rev >= 3)
		b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, 0xC020);
	अन्यथा
		b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, 0x8020);
	b43_phy_ग_लिखो(dev, B43_PHY_LO_CTL, 0);

	b43_phy_maskset(dev, B43_PHY_CCK(0x2B), 0xFFC0, 0x01);
	b43_phy_maskset(dev, B43_PHY_CCK(0x2B), 0xC0FF, 0x800);

	b43_phy_set(dev, B43_PHY_RFOVER, 0x0100);
	b43_phy_mask(dev, B43_PHY_RFOVERVAL, 0xCFFF);

	अगर (dev->dev->bus_sprom->boardflags_lo & B43_BFL_EXTLNA) अणु
		अगर (phy->rev >= 7) अणु
			b43_phy_set(dev, B43_PHY_RFOVER, 0x0800);
			b43_phy_set(dev, B43_PHY_RFOVERVAL, 0x8000);
		पूर्ण
	पूर्ण
	b43_radio_mask(dev, 0x7A, 0x00F7);

	j = 0;
	loop_i_max = (phy->radio_rev == 8) ? 15 : 9;
	क्रम (i = 0; i < loop_i_max; i++) अणु
		क्रम (j = 0; j < 16; j++) अणु
			b43_radio_ग_लिखो16(dev, 0x43, i);
			b43_phy_maskset(dev, B43_PHY_RFOVERVAL, 0xF0FF, (j << 8));
			b43_phy_maskset(dev, B43_PHY_PGACTL, 0x0FFF, 0xA000);
			b43_phy_set(dev, B43_PHY_PGACTL, 0xF000);
			udelay(20);
			अगर (b43_phy_पढ़ो(dev, B43_PHY_LO_LEAKAGE) >= 0xDFC)
				जाओ निकास_loop1;
		पूर्ण
	पूर्ण
      निकास_loop1:
	loop1_outer_करोne = i;
	loop1_inner_करोne = j;
	अगर (j >= 8) अणु
		b43_phy_set(dev, B43_PHY_RFOVERVAL, 0x30);
		trsw_rx = 0x1B;
		क्रम (j = j - 8; j < 16; j++) अणु
			b43_phy_maskset(dev, B43_PHY_RFOVERVAL, 0xF0FF, (j << 8));
			b43_phy_maskset(dev, B43_PHY_PGACTL, 0x0FFF, 0xA000);
			b43_phy_set(dev, B43_PHY_PGACTL, 0xF000);
			udelay(20);
			trsw_rx -= 3;
			अगर (b43_phy_पढ़ो(dev, B43_PHY_LO_LEAKAGE) >= 0xDFC)
				जाओ निकास_loop2;
		पूर्ण
	पूर्ण अन्यथा
		trsw_rx = 0x18;
      निकास_loop2:

	अगर (phy->rev != 1) अणु	/* Not in specs, but needed to prevent PPC machine check */
		b43_phy_ग_लिखो(dev, B43_PHY_ANALOGOVER, backup_phy[4]);
		b43_phy_ग_लिखो(dev, B43_PHY_ANALOGOVERVAL, backup_phy[5]);
	पूर्ण
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x5A), backup_phy[6]);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x59), backup_phy[7]);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x58), backup_phy[8]);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x0A), backup_phy[9]);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x03), backup_phy[10]);
	b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, backup_phy[11]);
	b43_phy_ग_लिखो(dev, B43_PHY_LO_CTL, backup_phy[12]);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2B), backup_phy[13]);
	b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, backup_phy[14]);

	b43_gphy_set_baseband_attenuation(dev, backup_bband);

	b43_radio_ग_लिखो16(dev, 0x52, backup_radio[0]);
	b43_radio_ग_लिखो16(dev, 0x43, backup_radio[1]);
	b43_radio_ग_लिखो16(dev, 0x7A, backup_radio[2]);

	b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, backup_phy[2] | 0x0003);
	udelay(10);
	b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, backup_phy[2]);
	b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, backup_phy[3]);
	b43_phy_ग_लिखो(dev, B43_PHY_CRS0, backup_phy[0]);
	b43_phy_ग_लिखो(dev, B43_PHY_CCKBBANDCFG, backup_phy[1]);

	gphy->max_lb_gain =
	    ((loop1_inner_करोne * 6) - (loop1_outer_करोne * 4)) - 11;
	gphy->trsw_rx_gain = trsw_rx * 2;
पूर्ण

अटल व्योम b43_hardware_pctl_early_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (!b43_has_hardware_pctl(dev)) अणु
		b43_phy_ग_लिखो(dev, 0x047A, 0xC111);
		वापस;
	पूर्ण

	b43_phy_mask(dev, 0x0036, 0xFEFF);
	b43_phy_ग_लिखो(dev, 0x002F, 0x0202);
	b43_phy_set(dev, 0x047C, 0x0002);
	b43_phy_set(dev, 0x047A, 0xF000);
	अगर (phy->radio_ver == 0x2050 && phy->radio_rev == 8) अणु
		b43_phy_maskset(dev, 0x047A, 0xFF0F, 0x0010);
		b43_phy_set(dev, 0x005D, 0x8000);
		b43_phy_maskset(dev, 0x004E, 0xFFC0, 0x0010);
		b43_phy_ग_लिखो(dev, 0x002E, 0xC07F);
		b43_phy_set(dev, 0x0036, 0x0400);
	पूर्ण अन्यथा अणु
		b43_phy_set(dev, 0x0036, 0x0200);
		b43_phy_set(dev, 0x0036, 0x0400);
		b43_phy_mask(dev, 0x005D, 0x7FFF);
		b43_phy_mask(dev, 0x004F, 0xFFFE);
		b43_phy_maskset(dev, 0x004E, 0xFFC0, 0x0010);
		b43_phy_ग_लिखो(dev, 0x002E, 0xC07F);
		b43_phy_maskset(dev, 0x047A, 0xFF0F, 0x0010);
	पूर्ण
पूर्ण

/* Hardware घातer control क्रम G-PHY */
अटल व्योम b43_hardware_pctl_init_gphy(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;

	अगर (!b43_has_hardware_pctl(dev)) अणु
		/* No hardware घातer control */
		b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) & ~B43_HF_HWPCTL);
		वापस;
	पूर्ण

	b43_phy_maskset(dev, 0x0036, 0xFFC0, (gphy->tgt_idle_tssi - gphy->cur_idle_tssi));
	b43_phy_maskset(dev, 0x0478, 0xFF00, (gphy->tgt_idle_tssi - gphy->cur_idle_tssi));
	b43_gphy_tssi_घातer_lt_init(dev);
	b43_gphy_gain_lt_init(dev);
	b43_phy_mask(dev, 0x0060, 0xFFBF);
	b43_phy_ग_लिखो(dev, 0x0014, 0x0000);

	B43_WARN_ON(phy->rev < 6);
	b43_phy_set(dev, 0x0478, 0x0800);
	b43_phy_mask(dev, 0x0478, 0xFEFF);
	b43_phy_mask(dev, 0x0801, 0xFFBF);

	b43_gphy_dc_lt_init(dev, 1);

	/* Enable hardware pctl in firmware. */
	b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) | B43_HF_HWPCTL);
पूर्ण

/* Initialize B/G PHY घातer control */
अटल व्योम b43_phy_init_pctl(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_rfatt old_rfatt;
	काष्ठा b43_bbatt old_bbatt;
	u8 old_tx_control = 0;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);

	अगर ((dev->dev->board_venकरोr == SSB_BOARDVENDOR_BCM) &&
	    (dev->dev->board_type == SSB_BOARD_BU4306))
		वापस;

	b43_phy_ग_लिखो(dev, 0x0028, 0x8018);

	/* This करोes something with the Analog... */
	b43_ग_लिखो16(dev, B43_MMIO_PHY0, b43_पढ़ो16(dev, B43_MMIO_PHY0)
		    & 0xFFDF);

	अगर (!phy->gmode)
		वापस;
	b43_hardware_pctl_early_init(dev);
	अगर (gphy->cur_idle_tssi == 0) अणु
		अगर (phy->radio_ver == 0x2050 && phy->analog == 0) अणु
			b43_radio_maskset(dev, 0x0076, 0x00F7, 0x0084);
		पूर्ण अन्यथा अणु
			काष्ठा b43_rfatt rfatt;
			काष्ठा b43_bbatt bbatt;

			स_नकल(&old_rfatt, &gphy->rfatt, माप(old_rfatt));
			स_नकल(&old_bbatt, &gphy->bbatt, माप(old_bbatt));
			old_tx_control = gphy->tx_control;

			bbatt.att = 11;
			अगर (phy->radio_rev == 8) अणु
				rfatt.att = 15;
				rfatt.with_padmix = true;
			पूर्ण अन्यथा अणु
				rfatt.att = 9;
				rfatt.with_padmix = false;
			पूर्ण
			b43_set_txघातer_g(dev, &bbatt, &rfatt, 0);
		पूर्ण
		b43_dummy_transmission(dev, false, true);
		gphy->cur_idle_tssi = b43_phy_पढ़ो(dev, B43_PHY_ITSSI);
		अगर (B43_DEBUG) अणु
			/* Current-Idle-TSSI sanity check. */
			अगर (असल(gphy->cur_idle_tssi - gphy->tgt_idle_tssi) >= 20) अणु
				b43dbg(dev->wl,
				       "!WARNING! Idle-TSSI phy->cur_idle_tssi "
				       "measuring failed. (cur=%d, tgt=%d). Disabling TX power "
				       "adjustment.\n", gphy->cur_idle_tssi,
				       gphy->tgt_idle_tssi);
				gphy->cur_idle_tssi = 0;
			पूर्ण
		पूर्ण
		अगर (phy->radio_ver == 0x2050 && phy->analog == 0) अणु
			b43_radio_mask(dev, 0x0076, 0xFF7B);
		पूर्ण अन्यथा अणु
			b43_set_txघातer_g(dev, &old_bbatt,
					  &old_rfatt, old_tx_control);
		पूर्ण
	पूर्ण
	b43_hardware_pctl_init_gphy(dev);
	b43_shm_clear_tssi(dev);
पूर्ण

अटल व्योम b43_phy_inita(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	might_sleep();

	अगर (phy->rev >= 6) अणु
		अगर (b43_phy_पढ़ो(dev, B43_PHY_ENCORE) & B43_PHY_ENCORE_EN)
			b43_phy_set(dev, B43_PHY_ENCORE, 0x0010);
		अन्यथा
			b43_phy_mask(dev, B43_PHY_ENCORE, ~0x1010);
	पूर्ण

	b43_wa_all(dev);

	अगर (dev->dev->bus_sprom->boardflags_lo & B43_BFL_PACTRL)
		b43_phy_maskset(dev, B43_PHY_OFDM(0x6E), 0xE000, 0x3CF);
पूर्ण

अटल व्योम b43_phy_initg(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u16 पंचांगp;

	अगर (phy->rev == 1)
		b43_phy_initb5(dev);
	अन्यथा
		b43_phy_initb6(dev);

	अगर (phy->rev >= 2 || phy->gmode)
		b43_phy_inita(dev);

	अगर (phy->rev >= 2) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_ANALOGOVER, 0);
		b43_phy_ग_लिखो(dev, B43_PHY_ANALOGOVERVAL, 0);
	पूर्ण
	अगर (phy->rev == 2) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, 0);
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xC0);
	पूर्ण
	अगर (phy->rev > 5) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, 0x400);
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xC0);
	पूर्ण
	अगर (phy->gmode || phy->rev >= 2) अणु
		पंचांगp = b43_phy_पढ़ो(dev, B43_PHY_VERSION_OFDM);
		पंचांगp &= B43_PHYVER_VERSION;
		अगर (पंचांगp == 3 || पंचांगp == 5) अणु
			b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0xC2), 0x1816);
			b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0xC3), 0x8006);
		पूर्ण
		अगर (पंचांगp == 5) अणु
			b43_phy_maskset(dev, B43_PHY_OFDM(0xCC), 0x00FF, 0x1F00);
		पूर्ण
	पूर्ण
	अगर ((phy->rev <= 2 && phy->gmode) || phy->rev >= 2)
		b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0x7E), 0x78);
	अगर (phy->radio_rev == 8) अणु
		b43_phy_set(dev, B43_PHY_EXTG(0x01), 0x80);
		b43_phy_set(dev, B43_PHY_OFDM(0x3E), 0x4);
	पूर्ण
	अगर (has_loopback_gain(phy))
		b43_calc_loopback_gain(dev);

	अगर (phy->radio_rev != 8) अणु
		अगर (gphy->initval == 0xFFFF)
			gphy->initval = b43_radio_init2050(dev);
		अन्यथा
			b43_radio_ग_लिखो16(dev, 0x0078, gphy->initval);
	पूर्ण
	b43_lo_g_init(dev);
	अगर (has_tx_magnअगरication(phy)) अणु
		b43_radio_ग_लिखो16(dev, 0x52,
				  (b43_radio_पढ़ो16(dev, 0x52) & 0xFF00)
				  | gphy->lo_control->tx_bias | gphy->
				  lo_control->tx_magn);
	पूर्ण अन्यथा अणु
		b43_radio_maskset(dev, 0x52, 0xFFF0, gphy->lo_control->tx_bias);
	पूर्ण
	अगर (phy->rev >= 6) अणु
		b43_phy_maskset(dev, B43_PHY_CCK(0x36), 0x0FFF, (gphy->lo_control->tx_bias << 12));
	पूर्ण
	अगर (dev->dev->bus_sprom->boardflags_lo & B43_BFL_PACTRL)
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2E), 0x8075);
	अन्यथा
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2E), 0x807F);
	अगर (phy->rev < 2)
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2F), 0x101);
	अन्यथा
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2F), 0x202);
	अगर (phy->gmode || phy->rev >= 2) अणु
		b43_lo_g_adjust(dev);
		b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, 0x8078);
	पूर्ण

	अगर (!(dev->dev->bus_sprom->boardflags_lo & B43_BFL_RSSI)) अणु
		/* The specs state to update the NRSSI LT with
		 * the value 0x7FFFFFFF here. I think that is some weird
		 * compiler optimization in the original driver.
		 * Essentially, what we करो here is resetting all NRSSI LT
		 * entries to -32 (see the clamp_val() in nrssi_hw_update())
		 */
		b43_nrssi_hw_update(dev, 0xFFFF);	//FIXME?
		b43_calc_nrssi_threshold(dev);
	पूर्ण अन्यथा अगर (phy->gmode || phy->rev >= 2) अणु
		अगर (gphy->nrssi[0] == -1000) अणु
			B43_WARN_ON(gphy->nrssi[1] != -1000);
			b43_calc_nrssi_slope(dev);
		पूर्ण अन्यथा
			b43_calc_nrssi_threshold(dev);
	पूर्ण
	अगर (phy->radio_rev == 8)
		b43_phy_ग_लिखो(dev, B43_PHY_EXTG(0x05), 0x3230);
	b43_phy_init_pctl(dev);
	/* FIXME: The spec says in the following अगर, the 0 should be replaced
	   'if OFDM may not be used in the current locale'
	   but OFDM is legal everywhere */
	अगर ((dev->dev->chip_id == 0x4306
	     && dev->dev->chip_pkg == 2) || 0) अणु
		b43_phy_mask(dev, B43_PHY_CRS0, 0xBFFF);
		b43_phy_mask(dev, B43_PHY_OFDM(0xC3), 0x7FFF);
	पूर्ण
पूर्ण

व्योम b43_gphy_channel_चयन(काष्ठा b43_wldev *dev,
			     अचिन्हित पूर्णांक channel,
			     bool synthetic_pu_workaround)
अणु
	अगर (synthetic_pu_workaround)
		b43_synth_pu_workaround(dev, channel);

	b43_ग_लिखो16(dev, B43_MMIO_CHANNEL, channel2freq_bg(channel));

	अगर (channel == 14) अणु
		अगर (dev->dev->bus_sprom->country_code ==
		    SSB_SPROM1CCODE_JAPAN)
			b43_hf_ग_लिखो(dev,
				     b43_hf_पढ़ो(dev) & ~B43_HF_ACPR);
		अन्यथा
			b43_hf_ग_लिखो(dev,
				     b43_hf_पढ़ो(dev) | B43_HF_ACPR);
		b43_ग_लिखो16(dev, B43_MMIO_CHANNEL_EXT,
			    b43_पढ़ो16(dev, B43_MMIO_CHANNEL_EXT)
			    | (1 << 11));
	पूर्ण अन्यथा अणु
		b43_ग_लिखो16(dev, B43_MMIO_CHANNEL_EXT,
			    b43_पढ़ो16(dev, B43_MMIO_CHANNEL_EXT)
			    & 0xF7BF);
	पूर्ण
पूर्ण

अटल व्योम शेष_baseband_attenuation(काष्ठा b43_wldev *dev,
					 काष्ठा b43_bbatt *bb)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (phy->radio_ver == 0x2050 && phy->radio_rev < 6)
		bb->att = 0;
	अन्यथा
		bb->att = 2;
पूर्ण

अटल व्योम शेष_radio_attenuation(काष्ठा b43_wldev *dev,
				      काष्ठा b43_rfatt *rf)
अणु
	काष्ठा b43_bus_dev *bdev = dev->dev;
	काष्ठा b43_phy *phy = &dev->phy;

	rf->with_padmix = false;

	अगर (dev->dev->board_venकरोr == SSB_BOARDVENDOR_BCM &&
	    dev->dev->board_type == SSB_BOARD_BCM4309G) अणु
		अगर (dev->dev->board_rev < 0x43) अणु
			rf->att = 2;
			वापस;
		पूर्ण अन्यथा अगर (dev->dev->board_rev < 0x51) अणु
			rf->att = 3;
			वापस;
		पूर्ण
	पूर्ण

	चयन (phy->radio_ver) अणु
	हाल 0x2053:
		चयन (phy->radio_rev) अणु
		हाल 1:
			rf->att = 6;
			वापस;
		पूर्ण
		अवरोध;
	हाल 0x2050:
		चयन (phy->radio_rev) अणु
		हाल 0:
			rf->att = 5;
			वापस;
		हाल 1:
			अगर (phy->type == B43_PHYTYPE_G) अणु
				अगर (bdev->board_venकरोr == SSB_BOARDVENDOR_BCM
				    && bdev->board_type == SSB_BOARD_BCM4309G
				    && bdev->board_rev >= 30)
					rf->att = 3;
				अन्यथा अगर (bdev->board_venकरोr ==
					 SSB_BOARDVENDOR_BCM
					 && bdev->board_type ==
					 SSB_BOARD_BU4306)
					rf->att = 3;
				अन्यथा
					rf->att = 1;
			पूर्ण अन्यथा अणु
				अगर (bdev->board_venकरोr == SSB_BOARDVENDOR_BCM
				    && bdev->board_type == SSB_BOARD_BCM4309G
				    && bdev->board_rev >= 30)
					rf->att = 7;
				अन्यथा
					rf->att = 6;
			पूर्ण
			वापस;
		हाल 2:
			अगर (phy->type == B43_PHYTYPE_G) अणु
				अगर (bdev->board_venकरोr == SSB_BOARDVENDOR_BCM
				    && bdev->board_type == SSB_BOARD_BCM4309G
				    && bdev->board_rev >= 30)
					rf->att = 3;
				अन्यथा अगर (bdev->board_venकरोr ==
					 SSB_BOARDVENDOR_BCM
					 && bdev->board_type ==
					 SSB_BOARD_BU4306)
					rf->att = 5;
				अन्यथा अगर (bdev->chip_id == 0x4320)
					rf->att = 4;
				अन्यथा
					rf->att = 3;
			पूर्ण अन्यथा
				rf->att = 6;
			वापस;
		हाल 3:
			rf->att = 5;
			वापस;
		हाल 4:
		हाल 5:
			rf->att = 1;
			वापस;
		हाल 6:
		हाल 7:
			rf->att = 5;
			वापस;
		हाल 8:
			rf->att = 0xA;
			rf->with_padmix = true;
			वापस;
		हाल 9:
		शेष:
			rf->att = 5;
			वापस;
		पूर्ण
	पूर्ण
	rf->att = 5;
पूर्ण

अटल u16 शेष_tx_control(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (phy->radio_ver != 0x2050)
		वापस 0;
	अगर (phy->radio_rev == 1)
		वापस B43_TXCTL_PA2DB | B43_TXCTL_TXMIX;
	अगर (phy->radio_rev < 6)
		वापस B43_TXCTL_PA2DB;
	अगर (phy->radio_rev == 8)
		वापस B43_TXCTL_TXMIX;
	वापस 0;
पूर्ण

अटल u8 b43_gphy_aci_detect(काष्ठा b43_wldev *dev, u8 channel)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u8 ret = 0;
	u16 saved, rssi, temp;
	पूर्णांक i, j = 0;

	saved = b43_phy_पढ़ो(dev, 0x0403);
	b43_चयन_channel(dev, channel);
	b43_phy_ग_लिखो(dev, 0x0403, (saved & 0xFFF8) | 5);
	अगर (gphy->aci_hw_rssi)
		rssi = b43_phy_पढ़ो(dev, 0x048A) & 0x3F;
	अन्यथा
		rssi = saved & 0x3F;
	/* clamp temp to चिन्हित 5bit */
	अगर (rssi > 32)
		rssi -= 64;
	क्रम (i = 0; i < 100; i++) अणु
		temp = (b43_phy_पढ़ो(dev, 0x047F) >> 8) & 0x3F;
		अगर (temp > 32)
			temp -= 64;
		अगर (temp < rssi)
			j++;
		अगर (j >= 20)
			ret = 1;
	पूर्ण
	b43_phy_ग_लिखो(dev, 0x0403, saved);

	वापस ret;
पूर्ण

अटल u8 b43_gphy_aci_scan(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u8 ret[13] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक channel = phy->channel;
	अचिन्हित पूर्णांक i, j, start, end;

	अगर (!((phy->type == B43_PHYTYPE_G) && (phy->rev > 0)))
		वापस 0;

	b43_phy_lock(dev);
	b43_radio_lock(dev);
	b43_phy_mask(dev, 0x0802, 0xFFFC);
	b43_phy_mask(dev, B43_PHY_G_CRS, 0x7FFF);
	b43_set_all_gains(dev, 3, 8, 1);

	start = (channel - 5 > 0) ? channel - 5 : 1;
	end = (channel + 5 < 14) ? channel + 5 : 13;

	क्रम (i = start; i <= end; i++) अणु
		अगर (असल(channel - i) > 2)
			ret[i - 1] = b43_gphy_aci_detect(dev, i);
	पूर्ण
	b43_चयन_channel(dev, channel);
	b43_phy_maskset(dev, 0x0802, 0xFFFC, 0x0003);
	b43_phy_mask(dev, 0x0403, 0xFFF8);
	b43_phy_set(dev, B43_PHY_G_CRS, 0x8000);
	b43_set_original_gains(dev);
	क्रम (i = 0; i < 13; i++) अणु
		अगर (!ret[i])
			जारी;
		end = (i + 5 < 13) ? i + 5 : 13;
		क्रम (j = i; j < end; j++)
			ret[j] = 1;
	पूर्ण
	b43_radio_unlock(dev);
	b43_phy_unlock(dev);

	वापस ret[channel - 1];
पूर्ण

अटल s32 b43_tssi2dbm_ad(s32 num, s32 den)
अणु
	अगर (num < 0)
		वापस num / den;
	अन्यथा
		वापस (num + den / 2) / den;
पूर्ण

अटल s8 b43_tssi2dbm_entry(s8 entry[], u8 index,
			     s16 pab0, s16 pab1, s16 pab2)
अणु
	s32 m1, m2, f = 256, q, delta;
	s8 i = 0;

	m1 = b43_tssi2dbm_ad(16 * pab0 + index * pab1, 32);
	m2 = max(b43_tssi2dbm_ad(32768 + index * pab2, 256), 1);
	करो अणु
		अगर (i > 15)
			वापस -EINVAL;
		q = b43_tssi2dbm_ad(f * 4096 -
				    b43_tssi2dbm_ad(m2 * f, 16) * f, 2048);
		delta = असल(q - f);
		f = q;
		i++;
	पूर्ण जबतक (delta >= 2);
	entry[index] = clamp_val(b43_tssi2dbm_ad(m1 * f, 8192), -127, 128);
	वापस 0;
पूर्ण

u8 *b43_generate_dyn_tssi2dbm_tab(काष्ठा b43_wldev *dev,
				  s16 pab0, s16 pab1, s16 pab2)
अणु
	अचिन्हित पूर्णांक i;
	u8 *tab;
	पूर्णांक err;

	tab = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!tab) अणु
		b43err(dev->wl, "Could not allocate memory "
		       "for tssi2dbm table\n");
		वापस शून्य;
	पूर्ण
	क्रम (i = 0; i < 64; i++) अणु
		err = b43_tssi2dbm_entry(tab, i, pab0, pab1, pab2);
		अगर (err) अणु
			b43err(dev->wl, "Could not generate "
			       "tssi2dBm table\n");
			kमुक्त(tab);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस tab;
पूर्ण

/* Initialise the TSSI->dBm lookup table */
अटल पूर्णांक b43_gphy_init_tssi2dbm_table(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	s16 pab0, pab1, pab2;

	pab0 = (s16) (dev->dev->bus_sprom->pa0b0);
	pab1 = (s16) (dev->dev->bus_sprom->pa0b1);
	pab2 = (s16) (dev->dev->bus_sprom->pa0b2);

	B43_WARN_ON((dev->dev->chip_id == 0x4301) &&
		    (phy->radio_ver != 0x2050)); /* Not supported anymore */

	gphy->dyn_tssi_tbl = false;

	अगर (pab0 != 0 && pab1 != 0 && pab2 != 0 &&
	    pab0 != -1 && pab1 != -1 && pab2 != -1) अणु
		/* The pabX values are set in SPROM. Use them. */
		अगर ((s8) dev->dev->bus_sprom->itssi_bg != 0 &&
		    (s8) dev->dev->bus_sprom->itssi_bg != -1) अणु
			gphy->tgt_idle_tssi =
				(s8) (dev->dev->bus_sprom->itssi_bg);
		पूर्ण अन्यथा
			gphy->tgt_idle_tssi = 62;
		gphy->tssi2dbm = b43_generate_dyn_tssi2dbm_tab(dev, pab0,
							       pab1, pab2);
		अगर (!gphy->tssi2dbm)
			वापस -ENOMEM;
		gphy->dyn_tssi_tbl = true;
	पूर्ण अन्यथा अणु
		/* pabX values not set in SPROM. */
		gphy->tgt_idle_tssi = 52;
		gphy->tssi2dbm = b43_tssi2dbm_g_table;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक b43_gphy_op_allocate(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_g *gphy;
	काष्ठा b43_txघातer_lo_control *lo;
	पूर्णांक err;

	gphy = kzalloc(माप(*gphy), GFP_KERNEL);
	अगर (!gphy) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	dev->phy.g = gphy;

	lo = kzalloc(माप(*lo), GFP_KERNEL);
	अगर (!lo) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_gphy;
	पूर्ण
	gphy->lo_control = lo;

	err = b43_gphy_init_tssi2dbm_table(dev);
	अगर (err)
		जाओ err_मुक्त_lo;

	वापस 0;

err_मुक्त_lo:
	kमुक्त(lo);
err_मुक्त_gphy:
	kमुक्त(gphy);
error:
	वापस err;
पूर्ण

अटल व्योम b43_gphy_op_prepare_काष्ठाs(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	स्थिर व्योम *tssi2dbm;
	पूर्णांक tgt_idle_tssi;
	काष्ठा b43_txघातer_lo_control *lo;
	अचिन्हित पूर्णांक i;

	/* tssi2dbm table is स्थिरant, so it is initialized at alloc समय.
	 * Save a copy of the poपूर्णांकer. */
	tssi2dbm = gphy->tssi2dbm;
	tgt_idle_tssi = gphy->tgt_idle_tssi;
	/* Save the LO poपूर्णांकer. */
	lo = gphy->lo_control;

	/* Zero out the whole PHY काष्ठाure. */
	स_रखो(gphy, 0, माप(*gphy));

	/* Restore poपूर्णांकers. */
	gphy->tssi2dbm = tssi2dbm;
	gphy->tgt_idle_tssi = tgt_idle_tssi;
	gphy->lo_control = lo;

	स_रखो(gphy->minlowsig, 0xFF, माप(gphy->minlowsig));

	/* NRSSI */
	क्रम (i = 0; i < ARRAY_SIZE(gphy->nrssi); i++)
		gphy->nrssi[i] = -1000;
	क्रम (i = 0; i < ARRAY_SIZE(gphy->nrssi_lt); i++)
		gphy->nrssi_lt[i] = i;

	gphy->lofcal = 0xFFFF;
	gphy->initval = 0xFFFF;

	gphy->पूर्णांकerभ_शेषe = B43_INTERFMODE_NONE;

	/* OFDM-table address caching. */
	gphy->ofdmtab_addr_direction = B43_OFDMTAB_सूचीECTION_UNKNOWN;

	gphy->average_tssi = 0xFF;

	/* Local Osciallator काष्ठाure */
	lo->tx_bias = 0xFF;
	INIT_LIST_HEAD(&lo->calib_list);
पूर्ण

अटल व्योम b43_gphy_op_मुक्त(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;

	kमुक्त(gphy->lo_control);

	अगर (gphy->dyn_tssi_tbl)
		kमुक्त(gphy->tssi2dbm);
	gphy->dyn_tssi_tbl = false;
	gphy->tssi2dbm = शून्य;

	kमुक्त(gphy);
	dev->phy.g = शून्य;
पूर्ण

अटल पूर्णांक b43_gphy_op_prepare_hardware(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_txघातer_lo_control *lo = gphy->lo_control;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);

	शेष_baseband_attenuation(dev, &gphy->bbatt);
	शेष_radio_attenuation(dev, &gphy->rfatt);
	gphy->tx_control = (शेष_tx_control(dev) << 4);
	generate_rfatt_list(dev, &lo->rfatt_list);
	generate_bbatt_list(dev, &lo->bbatt_list);

	/* Commit previous ग_लिखोs */
	b43_पढ़ो32(dev, B43_MMIO_MACCTL);

	अगर (phy->rev == 1) अणु
		/* Workaround: Temporarly disable gmode through the early init
		 * phase, as the gmode stuff is not needed क्रम phy rev 1 */
		phy->gmode = false;
		b43_wireless_core_reset(dev, 0);
		b43_phy_initg(dev);
		phy->gmode = true;
		b43_wireless_core_reset(dev, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक b43_gphy_op_init(काष्ठा b43_wldev *dev)
अणु
	b43_phy_initg(dev);

	वापस 0;
पूर्ण

अटल व्योम b43_gphy_op_निकास(काष्ठा b43_wldev *dev)
अणु
	b43_lo_g_cleanup(dev);
पूर्ण

अटल u16 b43_gphy_op_पढ़ो(काष्ठा b43_wldev *dev, u16 reg)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_PHY_CONTROL, reg);
	वापस b43_पढ़ो16(dev, B43_MMIO_PHY_DATA);
पूर्ण

अटल व्योम b43_gphy_op_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg, u16 value)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_PHY_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_PHY_DATA, value);
पूर्ण

अटल u16 b43_gphy_op_radio_पढ़ो(काष्ठा b43_wldev *dev, u16 reg)
अणु
	/* Register 1 is a 32-bit रेजिस्टर. */
	B43_WARN_ON(reg == 1);
	/* G-PHY needs 0x80 क्रम पढ़ो access. */
	reg |= 0x80;

	b43_ग_लिखो16f(dev, B43_MMIO_RADIO_CONTROL, reg);
	वापस b43_पढ़ो16(dev, B43_MMIO_RADIO_DATA_LOW);
पूर्ण

अटल व्योम b43_gphy_op_radio_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg, u16 value)
अणु
	/* Register 1 is a 32-bit रेजिस्टर. */
	B43_WARN_ON(reg == 1);

	b43_ग_लिखो16f(dev, B43_MMIO_RADIO_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_RADIO_DATA_LOW, value);
पूर्ण

अटल bool b43_gphy_op_supports_hwpctl(काष्ठा b43_wldev *dev)
अणु
	वापस (dev->phy.rev >= 6);
पूर्ण

अटल व्योम b43_gphy_op_software_rfसमाप्त(काष्ठा b43_wldev *dev,
					bool blocked)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	अचिन्हित पूर्णांक channel;

	might_sleep();

	अगर (!blocked) अणु
		/* Turn radio ON */
		अगर (phy->radio_on)
			वापस;

		b43_phy_ग_लिखो(dev, 0x0015, 0x8000);
		b43_phy_ग_लिखो(dev, 0x0015, 0xCC00);
		b43_phy_ग_लिखो(dev, 0x0015, (phy->gmode ? 0x00C0 : 0x0000));
		अगर (gphy->radio_off_context.valid) अणु
			/* Restore the RFover values. */
			b43_phy_ग_लिखो(dev, B43_PHY_RFOVER,
				      gphy->radio_off_context.rfover);
			b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL,
				      gphy->radio_off_context.rfoverval);
			gphy->radio_off_context.valid = false;
		पूर्ण
		channel = phy->channel;
		b43_gphy_channel_चयन(dev, 6, 1);
		b43_gphy_channel_चयन(dev, channel, 0);
	पूर्ण अन्यथा अणु
		/* Turn radio OFF */
		u16 rfover, rfoverval;

		rfover = b43_phy_पढ़ो(dev, B43_PHY_RFOVER);
		rfoverval = b43_phy_पढ़ो(dev, B43_PHY_RFOVERVAL);
		gphy->radio_off_context.rfover = rfover;
		gphy->radio_off_context.rfoverval = rfoverval;
		gphy->radio_off_context.valid = true;
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, rfover | 0x008C);
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, rfoverval & 0xFF73);
	पूर्ण
पूर्ण

अटल पूर्णांक b43_gphy_op_चयन_channel(काष्ठा b43_wldev *dev,
				      अचिन्हित पूर्णांक new_channel)
अणु
	अगर ((new_channel < 1) || (new_channel > 14))
		वापस -EINVAL;
	b43_gphy_channel_चयन(dev, new_channel, 0);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक b43_gphy_op_get_शेष_chan(काष्ठा b43_wldev *dev)
अणु
	वापस 1; /* Default to channel 1 */
पूर्ण

अटल व्योम b43_gphy_op_set_rx_antenna(काष्ठा b43_wldev *dev, पूर्णांक antenna)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 पंचांगp;
	पूर्णांक स्वतःभाग = 0;

	अगर (antenna == B43_ANTENNA_AUTO0 || antenna == B43_ANTENNA_AUTO1)
		स्वतःभाग = 1;

	b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) & ~B43_HF_ANTDIVHELP);

	b43_phy_maskset(dev, B43_PHY_BBANDCFG, ~B43_PHY_BBANDCFG_RXANT,
			(स्वतःभाग ? B43_ANTENNA_AUTO1 : antenna) <<
			B43_PHY_BBANDCFG_RXANT_SHIFT);

	अगर (स्वतःभाग) अणु
		पंचांगp = b43_phy_पढ़ो(dev, B43_PHY_ANTDWELL);
		अगर (antenna == B43_ANTENNA_AUTO1)
			पंचांगp &= ~B43_PHY_ANTDWELL_AUTODIV1;
		अन्यथा
			पंचांगp |= B43_PHY_ANTDWELL_AUTODIV1;
		b43_phy_ग_लिखो(dev, B43_PHY_ANTDWELL, पंचांगp);
	पूर्ण

	पंचांगp = b43_phy_पढ़ो(dev, B43_PHY_ANTWRSETT);
	अगर (स्वतःभाग)
		पंचांगp |= B43_PHY_ANTWRSETT_ARXDIV;
	अन्यथा
		पंचांगp &= ~B43_PHY_ANTWRSETT_ARXDIV;
	b43_phy_ग_लिखो(dev, B43_PHY_ANTWRSETT, पंचांगp);

	अगर (स्वतःभाग)
		b43_phy_set(dev, B43_PHY_ANTWRSETT, B43_PHY_ANTWRSETT_ARXDIV);
	अन्यथा अणु
		b43_phy_mask(dev, B43_PHY_ANTWRSETT,
			     B43_PHY_ANTWRSETT_ARXDIV);
	पूर्ण

	अगर (phy->rev >= 2) अणु
		b43_phy_set(dev, B43_PHY_OFDM61, B43_PHY_OFDM61_10);
		b43_phy_maskset(dev, B43_PHY_DIVSRCHGAINBACK, 0xFF00, 0x15);

		अगर (phy->rev == 2)
			b43_phy_ग_लिखो(dev, B43_PHY_ADIVRELATED, 8);
		अन्यथा
			b43_phy_maskset(dev, B43_PHY_ADIVRELATED, 0xFF00, 8);
	पूर्ण
	अगर (phy->rev >= 6)
		b43_phy_ग_लिखो(dev, B43_PHY_OFDM9B, 0xDC);

	b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) | B43_HF_ANTDIVHELP);
पूर्ण

अटल पूर्णांक b43_gphy_op_पूर्णांकerf_mitigation(काष्ठा b43_wldev *dev,
					 क्रमागत b43_पूर्णांकerference_mitigation mode)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	पूर्णांक currenपंचांगode;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);
	अगर ((phy->rev == 0) || (!phy->gmode))
		वापस -ENODEV;

	gphy->aci_wlan_स्वतःmatic = false;
	चयन (mode) अणु
	हाल B43_INTERFMODE_AUTOWLAN:
		gphy->aci_wlan_स्वतःmatic = true;
		अगर (gphy->aci_enable)
			mode = B43_INTERFMODE_MANUALWLAN;
		अन्यथा
			mode = B43_INTERFMODE_NONE;
		अवरोध;
	हाल B43_INTERFMODE_NONE:
	हाल B43_INTERFMODE_NONWLAN:
	हाल B43_INTERFMODE_MANUALWLAN:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	currenपंचांगode = gphy->पूर्णांकerभ_शेषe;
	अगर (currenपंचांगode == mode)
		वापस 0;
	अगर (currenपंचांगode != B43_INTERFMODE_NONE)
		b43_radio_पूर्णांकerference_mitigation_disable(dev, currenपंचांगode);

	अगर (mode == B43_INTERFMODE_NONE) अणु
		gphy->aci_enable = false;
		gphy->aci_hw_rssi = false;
	पूर्ण अन्यथा
		b43_radio_पूर्णांकerference_mitigation_enable(dev, mode);
	gphy->पूर्णांकerभ_शेषe = mode;

	वापस 0;
पूर्ण

/* https://bcm-specs.sipsolutions.net/EstimatePowerOut
 * This function converts a TSSI value to dBm in Q5.2
 */
अटल s8 b43_gphy_estimate_घातer_out(काष्ठा b43_wldev *dev, s8 tssi)
अणु
	काष्ठा b43_phy_g *gphy = dev->phy.g;
	s8 dbm;
	s32 पंचांगp;

	पंचांगp = (gphy->tgt_idle_tssi - gphy->cur_idle_tssi + tssi);
	पंचांगp = clamp_val(पंचांगp, 0x00, 0x3F);
	dbm = gphy->tssi2dbm[पंचांगp];

	वापस dbm;
पूर्ण

अटल व्योम b43_put_attenuation_पूर्णांकo_ranges(काष्ठा b43_wldev *dev,
					    पूर्णांक *_bbatt, पूर्णांक *_rfatt)
अणु
	पूर्णांक rfatt = *_rfatt;
	पूर्णांक bbatt = *_bbatt;
	काष्ठा b43_txघातer_lo_control *lo = dev->phy.g->lo_control;

	/* Get baseband and radio attenuation values पूर्णांकo their permitted ranges.
	 * Radio attenuation affects घातer level 4 बार as much as baseband. */

	/* Range स्थिरants */
	स्थिर पूर्णांक rf_min = lo->rfatt_list.min_val;
	स्थिर पूर्णांक rf_max = lo->rfatt_list.max_val;
	स्थिर पूर्णांक bb_min = lo->bbatt_list.min_val;
	स्थिर पूर्णांक bb_max = lo->bbatt_list.max_val;

	जबतक (1) अणु
		अगर (rfatt > rf_max && bbatt > bb_max - 4)
			अवरोध;	/* Can not get it पूर्णांकo ranges */
		अगर (rfatt < rf_min && bbatt < bb_min + 4)
			अवरोध;	/* Can not get it पूर्णांकo ranges */
		अगर (bbatt > bb_max && rfatt > rf_max - 1)
			अवरोध;	/* Can not get it पूर्णांकo ranges */
		अगर (bbatt < bb_min && rfatt < rf_min + 1)
			अवरोध;	/* Can not get it पूर्णांकo ranges */

		अगर (bbatt > bb_max) अणु
			bbatt -= 4;
			rfatt += 1;
			जारी;
		पूर्ण
		अगर (bbatt < bb_min) अणु
			bbatt += 4;
			rfatt -= 1;
			जारी;
		पूर्ण
		अगर (rfatt > rf_max) अणु
			rfatt -= 1;
			bbatt += 4;
			जारी;
		पूर्ण
		अगर (rfatt < rf_min) अणु
			rfatt += 1;
			bbatt -= 4;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	*_rfatt = clamp_val(rfatt, rf_min, rf_max);
	*_bbatt = clamp_val(bbatt, bb_min, bb_max);
पूर्ण

अटल व्योम b43_gphy_op_adjust_txघातer(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	पूर्णांक rfatt, bbatt;
	u8 tx_control;

	b43_mac_suspend(dev);

	/* Calculate the new attenuation values. */
	bbatt = gphy->bbatt.att;
	bbatt += gphy->bbatt_delta;
	rfatt = gphy->rfatt.att;
	rfatt += gphy->rfatt_delta;

	b43_put_attenuation_पूर्णांकo_ranges(dev, &bbatt, &rfatt);
	tx_control = gphy->tx_control;
	अगर ((phy->radio_ver == 0x2050) && (phy->radio_rev == 2)) अणु
		अगर (rfatt <= 1) अणु
			अगर (tx_control == 0) अणु
				tx_control =
				    B43_TXCTL_PA2DB |
				    B43_TXCTL_TXMIX;
				rfatt += 2;
				bbatt += 2;
			पूर्ण अन्यथा अगर (dev->dev->bus_sprom->
				   boardflags_lo &
				   B43_BFL_PACTRL) अणु
				bbatt += 4 * (rfatt - 2);
				rfatt = 2;
			पूर्ण
		पूर्ण अन्यथा अगर (rfatt > 4 && tx_control) अणु
			tx_control = 0;
			अगर (bbatt < 3) अणु
				rfatt -= 3;
				bbatt += 2;
			पूर्ण अन्यथा अणु
				rfatt -= 2;
				bbatt -= 2;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Save the control values */
	gphy->tx_control = tx_control;
	b43_put_attenuation_पूर्णांकo_ranges(dev, &bbatt, &rfatt);
	gphy->rfatt.att = rfatt;
	gphy->bbatt.att = bbatt;

	अगर (b43_debug(dev, B43_DBG_XMITPOWER))
		b43dbg(dev->wl, "Adjusting TX power\n");

	/* Adjust the hardware */
	b43_phy_lock(dev);
	b43_radio_lock(dev);
	b43_set_txघातer_g(dev, &gphy->bbatt, &gphy->rfatt,
			  gphy->tx_control);
	b43_radio_unlock(dev);
	b43_phy_unlock(dev);

	b43_mac_enable(dev);
पूर्ण

अटल क्रमागत b43_txpwr_result b43_gphy_op_recalc_txघातer(काष्ठा b43_wldev *dev,
							bool ignore_tssi)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	अचिन्हित पूर्णांक average_tssi;
	पूर्णांक cck_result, ofdm_result;
	पूर्णांक estimated_pwr, desired_pwr, pwr_adjust;
	पूर्णांक rfatt_delta, bbatt_delta;
	अचिन्हित पूर्णांक max_pwr;

	/* First get the average TSSI */
	cck_result = b43_phy_shm_tssi_पढ़ो(dev, B43_SHM_SH_TSSI_CCK);
	ofdm_result = b43_phy_shm_tssi_पढ़ो(dev, B43_SHM_SH_TSSI_OFDM_G);
	अगर ((cck_result < 0) && (ofdm_result < 0)) अणु
		/* No TSSI inक्रमmation available */
		अगर (!ignore_tssi)
			जाओ no_adjusपंचांगent_needed;
		cck_result = 0;
		ofdm_result = 0;
	पूर्ण
	अगर (cck_result < 0)
		average_tssi = ofdm_result;
	अन्यथा अगर (ofdm_result < 0)
		average_tssi = cck_result;
	अन्यथा
		average_tssi = (cck_result + ofdm_result) / 2;
	/* Merge the average with the stored value. */
	अगर (likely(gphy->average_tssi != 0xFF))
		average_tssi = (average_tssi + gphy->average_tssi) / 2;
	gphy->average_tssi = average_tssi;
	B43_WARN_ON(average_tssi >= B43_TSSI_MAX);

	/* Estimate the TX घातer emission based on the TSSI */
	estimated_pwr = b43_gphy_estimate_घातer_out(dev, average_tssi);

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);
	max_pwr = dev->dev->bus_sprom->maxpwr_bg;
	अगर (dev->dev->bus_sprom->boardflags_lo & B43_BFL_PACTRL)
		max_pwr -= 3; /* minus 0.75 */
	अगर (unlikely(max_pwr >= INT_TO_Q52(30/*dBm*/))) अणु
		b43warn(dev->wl,
			"Invalid max-TX-power value in SPROM.\n");
		max_pwr = INT_TO_Q52(20); /* fake it */
		dev->dev->bus_sprom->maxpwr_bg = max_pwr;
	पूर्ण

	/* Get desired घातer (in Q5.2) */
	अगर (phy->desired_txघातer < 0)
		desired_pwr = INT_TO_Q52(0);
	अन्यथा
		desired_pwr = INT_TO_Q52(phy->desired_txघातer);
	/* And limit it. max_pwr alपढ़ोy is Q5.2 */
	desired_pwr = clamp_val(desired_pwr, 0, max_pwr);
	अगर (b43_debug(dev, B43_DBG_XMITPOWER)) अणु
		b43dbg(dev->wl,
		       "[TX power]  current = " Q52_FMT
		       " dBm,  desired = " Q52_FMT
		       " dBm,  max = " Q52_FMT "\n",
		       Q52_ARG(estimated_pwr),
		       Q52_ARG(desired_pwr),
		       Q52_ARG(max_pwr));
	पूर्ण

	/* Calculate the adjusपंचांगent delta. */
	pwr_adjust = desired_pwr - estimated_pwr;
	अगर (pwr_adjust == 0)
		जाओ no_adjusपंचांगent_needed;

	/* RF attenuation delta. */
	rfatt_delta = ((pwr_adjust + 7) / 8);
	/* Lower attenuation => Bigger घातer output. Negate it. */
	rfatt_delta = -rfatt_delta;

	/* Baseband attenuation delta. */
	bbatt_delta = pwr_adjust / 2;
	/* Lower attenuation => Bigger घातer output. Negate it. */
	bbatt_delta = -bbatt_delta;
	/* RF att affects घातer level 4 बार as much as
	 * Baseband attennuation. Subtract it. */
	bbatt_delta -= 4 * rfatt_delta;

#अगर B43_DEBUG
	अगर (b43_debug(dev, B43_DBG_XMITPOWER)) अणु
		पूर्णांक dbm = pwr_adjust < 0 ? -pwr_adjust : pwr_adjust;
		b43dbg(dev->wl,
		       "[TX power deltas]  %s" Q52_FMT " dBm   =>   "
		       "bbatt-delta = %d,  rfatt-delta = %d\n",
		       (pwr_adjust < 0 ? "-" : ""), Q52_ARG(dbm),
		       bbatt_delta, rfatt_delta);
	पूर्ण
#पूर्ण_अगर /* DEBUG */

	/* So करो we finally need to adjust something in hardware? */
	अगर ((rfatt_delta == 0) && (bbatt_delta == 0))
		जाओ no_adjusपंचांगent_needed;

	/* Save the deltas क्रम later when we adjust the घातer. */
	gphy->bbatt_delta = bbatt_delta;
	gphy->rfatt_delta = rfatt_delta;

	/* We need to adjust the TX घातer on the device. */
	वापस B43_TXPWR_RES_NEED_ADJUST;

no_adjusपंचांगent_needed:
	वापस B43_TXPWR_RES_DONE;
पूर्ण

अटल व्योम b43_gphy_op_pwork_15sec(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;

	b43_mac_suspend(dev);
	//TODO: update_aci_moving_average
	अगर (gphy->aci_enable && gphy->aci_wlan_स्वतःmatic) अणु
		अगर (!gphy->aci_enable && 1 /*TODO: not scanning? */ ) अणु
			अगर (0 /*TODO: bunch of conditions */ ) अणु
				phy->ops->पूर्णांकerf_mitigation(dev,
					B43_INTERFMODE_MANUALWLAN);
			पूर्ण
		पूर्ण अन्यथा अगर (0 /*TODO*/) अणु
			   अगर (/*(aci_average > 1000) &&*/ !b43_gphy_aci_scan(dev))
				phy->ops->पूर्णांकerf_mitigation(dev, B43_INTERFMODE_NONE);
		पूर्ण
	पूर्ण अन्यथा अगर (gphy->पूर्णांकerभ_शेषe == B43_INTERFMODE_NONWLAN &&
		   phy->rev == 1) अणु
		//TODO: implement rev1 workaround
	पूर्ण
	b43_lo_g_मुख्यtenance_work(dev);
	b43_mac_enable(dev);
पूर्ण

अटल व्योम b43_gphy_op_pwork_60sec(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (!(dev->dev->bus_sprom->boardflags_lo & B43_BFL_RSSI))
		वापस;

	b43_mac_suspend(dev);
	b43_calc_nrssi_slope(dev);
	अगर ((phy->radio_ver == 0x2050) && (phy->radio_rev == 8)) अणु
		u8 old_chan = phy->channel;

		/* VCO Calibration */
		अगर (old_chan >= 8)
			b43_चयन_channel(dev, 1);
		अन्यथा
			b43_चयन_channel(dev, 13);
		b43_चयन_channel(dev, old_chan);
	पूर्ण
	b43_mac_enable(dev);
पूर्ण

स्थिर काष्ठा b43_phy_operations b43_phyops_g = अणु
	.allocate		= b43_gphy_op_allocate,
	.मुक्त			= b43_gphy_op_मुक्त,
	.prepare_काष्ठाs	= b43_gphy_op_prepare_काष्ठाs,
	.prepare_hardware	= b43_gphy_op_prepare_hardware,
	.init			= b43_gphy_op_init,
	.निकास			= b43_gphy_op_निकास,
	.phy_पढ़ो		= b43_gphy_op_पढ़ो,
	.phy_ग_लिखो		= b43_gphy_op_ग_लिखो,
	.radio_पढ़ो		= b43_gphy_op_radio_पढ़ो,
	.radio_ग_लिखो		= b43_gphy_op_radio_ग_लिखो,
	.supports_hwpctl	= b43_gphy_op_supports_hwpctl,
	.software_rfसमाप्त	= b43_gphy_op_software_rfसमाप्त,
	.चयन_analog		= b43_phyop_चयन_analog_generic,
	.चयन_channel		= b43_gphy_op_चयन_channel,
	.get_शेष_chan	= b43_gphy_op_get_शेष_chan,
	.set_rx_antenna		= b43_gphy_op_set_rx_antenna,
	.पूर्णांकerf_mitigation	= b43_gphy_op_पूर्णांकerf_mitigation,
	.recalc_txघातer		= b43_gphy_op_recalc_txघातer,
	.adjust_txघातer		= b43_gphy_op_adjust_txघातer,
	.pwork_15sec		= b43_gphy_op_pwork_15sec,
	.pwork_60sec		= b43_gphy_op_pwork_60sec,
पूर्ण;
