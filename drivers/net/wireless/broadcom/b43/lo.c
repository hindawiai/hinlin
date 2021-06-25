<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver

  G PHY LO (LocalOscillator) Measuring and Control routines

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>,
  Copyright (c) 2005, 2006 Stefano Brivio <stefano.brivio@polimi.it>
  Copyright (c) 2005-2007 Michael Buesch <m@bues.ch>
  Copyright (c) 2005, 2006 Danny van Dyk <kugelfang@gentoo.org>
  Copyright (c) 2005, 2006 Andreas Jaggi <andreas.jaggi@waterwave.ch>


*/

#समावेश "b43.h"
#समावेश "lo.h"
#समावेश "phy_g.h"
#समावेश "main.h"

#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>


अटल काष्ठा b43_lo_calib *b43_find_lo_calib(काष्ठा b43_txघातer_lo_control *lo,
					      स्थिर काष्ठा b43_bbatt *bbatt,
					       स्थिर काष्ठा b43_rfatt *rfatt)
अणु
	काष्ठा b43_lo_calib *c;

	list_क्रम_each_entry(c, &lo->calib_list, list) अणु
		अगर (!b43_compare_bbatt(&c->bbatt, bbatt))
			जारी;
		अगर (!b43_compare_rfatt(&c->rfatt, rfatt))
			जारी;
		वापस c;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Write the LocalOscillator Control (adjust) value-pair. */
अटल व्योम b43_lo_ग_लिखो(काष्ठा b43_wldev *dev, काष्ठा b43_loctl *control)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 value;

	अगर (B43_DEBUG) अणु
		अगर (unlikely(असल(control->i) > 16 || असल(control->q) > 16)) अणु
			b43dbg(dev->wl, "Invalid LO control pair "
			       "(I: %d, Q: %d)\n", control->i, control->q);
			dump_stack();
			वापस;
		पूर्ण
	पूर्ण
	B43_WARN_ON(phy->type != B43_PHYTYPE_G);

	value = (u8) (control->q);
	value |= ((u8) (control->i)) << 8;
	b43_phy_ग_लिखो(dev, B43_PHY_LO_CTL, value);
पूर्ण

अटल u16 lo_measure_feedthrough(काष्ठा b43_wldev *dev,
				  u16 lna, u16 pga, u16 trsw_rx)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 rfover;
	u16 feedthrough;

	अगर (phy->gmode) अणु
		lna <<= B43_PHY_RFOVERVAL_LNA_SHIFT;
		pga <<= B43_PHY_RFOVERVAL_PGA_SHIFT;

		B43_WARN_ON(lna & ~B43_PHY_RFOVERVAL_LNA);
		B43_WARN_ON(pga & ~B43_PHY_RFOVERVAL_PGA);
/*FIXME This निश्चितion fails		B43_WARN_ON(trsw_rx & ~(B43_PHY_RFOVERVAL_TRSWRX |
				    B43_PHY_RFOVERVAL_BW));
*/
		trsw_rx &= (B43_PHY_RFOVERVAL_TRSWRX | B43_PHY_RFOVERVAL_BW);

		/* Conकाष्ठा the RF Override Value */
		rfover = B43_PHY_RFOVERVAL_UNK;
		rfover |= pga;
		rfover |= lna;
		rfover |= trsw_rx;
		अगर ((dev->dev->bus_sprom->boardflags_lo & B43_BFL_EXTLNA)
		    && phy->rev > 6)
			rfover |= B43_PHY_RFOVERVAL_EXTLNA;

		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xE300);
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, rfover);
		udelay(10);
		rfover |= B43_PHY_RFOVERVAL_BW_LBW;
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, rfover);
		udelay(10);
		rfover |= B43_PHY_RFOVERVAL_BW_LPF;
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, rfover);
		udelay(10);
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xF300);
	पूर्ण अन्यथा अणु
		pga |= B43_PHY_PGACTL_UNKNOWN;
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, pga);
		udelay(10);
		pga |= B43_PHY_PGACTL_LOWBANDW;
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, pga);
		udelay(10);
		pga |= B43_PHY_PGACTL_LPF;
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, pga);
	पूर्ण
	udelay(21);
	feedthrough = b43_phy_पढ़ो(dev, B43_PHY_LO_LEAKAGE);

	/* This is a good place to check अगर we need to relax a bit,
	 * as this is the मुख्य function called regularly
	 * in the LO calibration. */
	cond_resched();

	वापस feedthrough;
पूर्ण

/* TXCTL Register and Value Table.
 * Returns the "TXCTL Register".
 * "value" is the "TXCTL Value".
 * "pad_mix_gain" is the PAD Mixer Gain.
 */
अटल u16 lo_txctl_रेजिस्टर_table(काष्ठा b43_wldev *dev,
				   u16 *value, u16 *pad_mix_gain)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 reg, v, padmix;

	अगर (phy->type == B43_PHYTYPE_B) अणु
		v = 0x30;
		अगर (phy->radio_rev <= 5) अणु
			reg = 0x43;
			padmix = 0;
		पूर्ण अन्यथा अणु
			reg = 0x52;
			padmix = 5;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (phy->rev >= 2 && phy->radio_rev == 8) अणु
			reg = 0x43;
			v = 0x10;
			padmix = 2;
		पूर्ण अन्यथा अणु
			reg = 0x52;
			v = 0x30;
			padmix = 5;
		पूर्ण
	पूर्ण
	अगर (value)
		*value = v;
	अगर (pad_mix_gain)
		*pad_mix_gain = padmix;

	वापस reg;
पूर्ण

अटल व्योम lo_measure_txctl_values(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_txघातer_lo_control *lo = gphy->lo_control;
	u16 reg, mask;
	u16 trsw_rx, pga;
	u16 radio_pctl_reg;

	अटल स्थिर u8 tx_bias_values[] = अणु
		0x09, 0x08, 0x0A, 0x01, 0x00,
		0x02, 0x05, 0x04, 0x06,
	पूर्ण;
	अटल स्थिर u8 tx_magn_values[] = अणु
		0x70, 0x40,
	पूर्ण;

	अगर (!has_loopback_gain(phy)) अणु
		radio_pctl_reg = 6;
		trsw_rx = 2;
		pga = 0;
	पूर्ण अन्यथा अणु
		पूर्णांक lb_gain;	/* Loopback gain (in dB) */

		trsw_rx = 0;
		lb_gain = gphy->max_lb_gain / 2;
		अगर (lb_gain > 10) अणु
			radio_pctl_reg = 0;
			pga = असल(10 - lb_gain) / 6;
			pga = clamp_val(pga, 0, 15);
		पूर्ण अन्यथा अणु
			पूर्णांक cmp_val;
			पूर्णांक पंचांगp;

			pga = 0;
			cmp_val = 0x24;
			अगर ((phy->rev >= 2) &&
			    (phy->radio_ver == 0x2050) && (phy->radio_rev == 8))
				cmp_val = 0x3C;
			पंचांगp = lb_gain;
			अगर ((10 - lb_gain) < cmp_val)
				पंचांगp = (10 - lb_gain);
			अगर (पंचांगp < 0)
				पंचांगp += 6;
			अन्यथा
				पंचांगp += 3;
			cmp_val /= 4;
			पंचांगp /= 4;
			अगर (पंचांगp >= cmp_val)
				radio_pctl_reg = cmp_val;
			अन्यथा
				radio_pctl_reg = पंचांगp;
		पूर्ण
	पूर्ण
	b43_radio_maskset(dev, 0x43, 0xFFF0, radio_pctl_reg);
	b43_gphy_set_baseband_attenuation(dev, 2);

	reg = lo_txctl_रेजिस्टर_table(dev, &mask, शून्य);
	mask = ~mask;
	b43_radio_mask(dev, reg, mask);

	अगर (has_tx_magnअगरication(phy)) अणु
		पूर्णांक i, j;
		पूर्णांक feedthrough;
		पूर्णांक min_feedth = 0xFFFF;
		u8 tx_magn, tx_bias;

		क्रम (i = 0; i < ARRAY_SIZE(tx_magn_values); i++) अणु
			tx_magn = tx_magn_values[i];
			b43_radio_maskset(dev, 0x52, 0xFF0F, tx_magn);
			क्रम (j = 0; j < ARRAY_SIZE(tx_bias_values); j++) अणु
				tx_bias = tx_bias_values[j];
				b43_radio_maskset(dev, 0x52, 0xFFF0, tx_bias);
				feedthrough =
				    lo_measure_feedthrough(dev, 0, pga,
							   trsw_rx);
				अगर (feedthrough < min_feedth) अणु
					lo->tx_bias = tx_bias;
					lo->tx_magn = tx_magn;
					min_feedth = feedthrough;
				पूर्ण
				अगर (lo->tx_bias == 0)
					अवरोध;
			पूर्ण
			b43_radio_ग_लिखो16(dev, 0x52,
					  (b43_radio_पढ़ो16(dev, 0x52)
					   & 0xFF00) | lo->tx_bias | lo->
					  tx_magn);
		पूर्ण
	पूर्ण अन्यथा अणु
		lo->tx_magn = 0;
		lo->tx_bias = 0;
		b43_radio_mask(dev, 0x52, 0xFFF0);	/* TX bias == 0 */
	पूर्ण
	lo->txctl_measured_समय = jअगरfies;
पूर्ण

अटल व्योम lo_पढ़ो_घातer_vector(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_txघातer_lo_control *lo = gphy->lo_control;
	पूर्णांक i;
	u64 पंचांगp;
	u64 घातer_vector = 0;

	क्रम (i = 0; i < 8; i += 2) अणु
		पंचांगp = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, 0x310 + i);
		घातer_vector |= (पंचांगp << (i * 8));
		/* Clear the vector on the device. */
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 0x310 + i, 0);
	पूर्ण
	अगर (घातer_vector)
		lo->घातer_vector = घातer_vector;
	lo->pwr_vec_पढ़ो_समय = jअगरfies;
पूर्ण

/* 802.11/LO/GPHY/MeasuringGains */
अटल व्योम lo_measure_gain_values(काष्ठा b43_wldev *dev,
				   s16 max_rx_gain, पूर्णांक use_trsw_rx)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u16 पंचांगp;

	अगर (max_rx_gain < 0)
		max_rx_gain = 0;

	अगर (has_loopback_gain(phy)) अणु
		पूर्णांक trsw_rx_gain;

		अगर (use_trsw_rx) अणु
			trsw_rx_gain = gphy->trsw_rx_gain / 2;
			अगर (max_rx_gain >= trsw_rx_gain) अणु
				trsw_rx_gain = max_rx_gain - trsw_rx_gain;
			पूर्ण
		पूर्ण अन्यथा
			trsw_rx_gain = max_rx_gain;
		अगर (trsw_rx_gain < 9) अणु
			gphy->lna_lod_gain = 0;
		पूर्ण अन्यथा अणु
			gphy->lna_lod_gain = 1;
			trsw_rx_gain -= 8;
		पूर्ण
		trsw_rx_gain = clamp_val(trsw_rx_gain, 0, 0x2D);
		gphy->pga_gain = trsw_rx_gain / 3;
		अगर (gphy->pga_gain >= 5) अणु
			gphy->pga_gain -= 5;
			gphy->lna_gain = 2;
		पूर्ण अन्यथा
			gphy->lna_gain = 0;
	पूर्ण अन्यथा अणु
		gphy->lna_gain = 0;
		gphy->trsw_rx_gain = 0x20;
		अगर (max_rx_gain >= 0x14) अणु
			gphy->lna_lod_gain = 1;
			gphy->pga_gain = 2;
		पूर्ण अन्यथा अगर (max_rx_gain >= 0x12) अणु
			gphy->lna_lod_gain = 1;
			gphy->pga_gain = 1;
		पूर्ण अन्यथा अगर (max_rx_gain >= 0xF) अणु
			gphy->lna_lod_gain = 1;
			gphy->pga_gain = 0;
		पूर्ण अन्यथा अणु
			gphy->lna_lod_gain = 0;
			gphy->pga_gain = 0;
		पूर्ण
	पूर्ण

	पंचांगp = b43_radio_पढ़ो16(dev, 0x7A);
	अगर (gphy->lna_lod_gain == 0)
		पंचांगp &= ~0x0008;
	अन्यथा
		पंचांगp |= 0x0008;
	b43_radio_ग_लिखो16(dev, 0x7A, पंचांगp);
पूर्ण

काष्ठा lo_g_saved_values अणु
	u8 old_channel;

	/* Core रेजिस्टरs */
	u16 reg_3F4;
	u16 reg_3E2;

	/* PHY रेजिस्टरs */
	u16 phy_lo_mask;
	u16 phy_extg_01;
	u16 phy_dacctl_hwpctl;
	u16 phy_dacctl;
	u16 phy_cck_14;
	u16 phy_hpwr_tssictl;
	u16 phy_analogover;
	u16 phy_analogoverval;
	u16 phy_rfover;
	u16 phy_rfoverval;
	u16 phy_classctl;
	u16 phy_cck_3E;
	u16 phy_crs0;
	u16 phy_pgactl;
	u16 phy_cck_2A;
	u16 phy_syncctl;
	u16 phy_cck_30;
	u16 phy_cck_06;

	/* Radio रेजिस्टरs */
	u16 radio_43;
	u16 radio_7A;
	u16 radio_52;
पूर्ण;

अटल व्योम lo_measure_setup(काष्ठा b43_wldev *dev,
			     काष्ठा lo_g_saved_values *sav)
अणु
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_txघातer_lo_control *lo = gphy->lo_control;
	u16 पंचांगp;

	अगर (b43_has_hardware_pctl(dev)) अणु
		sav->phy_lo_mask = b43_phy_पढ़ो(dev, B43_PHY_LO_MASK);
		sav->phy_extg_01 = b43_phy_पढ़ो(dev, B43_PHY_EXTG(0x01));
		sav->phy_dacctl_hwpctl = b43_phy_पढ़ो(dev, B43_PHY_DACCTL);
		sav->phy_cck_14 = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x14));
		sav->phy_hpwr_tssictl = b43_phy_पढ़ो(dev, B43_PHY_HPWR_TSSICTL);

		b43_phy_set(dev, B43_PHY_HPWR_TSSICTL, 0x100);
		b43_phy_set(dev, B43_PHY_EXTG(0x01), 0x40);
		b43_phy_set(dev, B43_PHY_DACCTL, 0x40);
		b43_phy_set(dev, B43_PHY_CCK(0x14), 0x200);
	पूर्ण
	अगर (phy->type == B43_PHYTYPE_B &&
	    phy->radio_ver == 0x2050 && phy->radio_rev < 6) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x16), 0x410);
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x17), 0x820);
	पूर्ण
	अगर (phy->rev >= 2) अणु
		sav->phy_analogover = b43_phy_पढ़ो(dev, B43_PHY_ANALOGOVER);
		sav->phy_analogoverval =
		    b43_phy_पढ़ो(dev, B43_PHY_ANALOGOVERVAL);
		sav->phy_rfover = b43_phy_पढ़ो(dev, B43_PHY_RFOVER);
		sav->phy_rfoverval = b43_phy_पढ़ो(dev, B43_PHY_RFOVERVAL);
		sav->phy_classctl = b43_phy_पढ़ो(dev, B43_PHY_CLASSCTL);
		sav->phy_cck_3E = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x3E));
		sav->phy_crs0 = b43_phy_पढ़ो(dev, B43_PHY_CRS0);

		b43_phy_mask(dev, B43_PHY_CLASSCTL, 0xFFFC);
		b43_phy_mask(dev, B43_PHY_CRS0, 0x7FFF);
		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0003);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFC);
		अगर (phy->type == B43_PHYTYPE_G) अणु
			अगर ((phy->rev >= 7) &&
			    (sprom->boardflags_lo & B43_BFL_EXTLNA)) अणु
				b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, 0x933);
			पूर्ण अन्यथा अणु
				b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, 0x133);
			पूर्ण
		पूर्ण अन्यथा अणु
			b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, 0);
		पूर्ण
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x3E), 0);
	पूर्ण
	sav->reg_3F4 = b43_पढ़ो16(dev, 0x3F4);
	sav->reg_3E2 = b43_पढ़ो16(dev, 0x3E2);
	sav->radio_43 = b43_radio_पढ़ो16(dev, 0x43);
	sav->radio_7A = b43_radio_पढ़ो16(dev, 0x7A);
	sav->phy_pgactl = b43_phy_पढ़ो(dev, B43_PHY_PGACTL);
	sav->phy_cck_2A = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x2A));
	sav->phy_syncctl = b43_phy_पढ़ो(dev, B43_PHY_SYNCCTL);
	sav->phy_dacctl = b43_phy_पढ़ो(dev, B43_PHY_DACCTL);

	अगर (!has_tx_magnअगरication(phy)) अणु
		sav->radio_52 = b43_radio_पढ़ो16(dev, 0x52);
		sav->radio_52 &= 0x00F0;
	पूर्ण
	अगर (phy->type == B43_PHYTYPE_B) अणु
		sav->phy_cck_30 = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x30));
		sav->phy_cck_06 = b43_phy_पढ़ो(dev, B43_PHY_CCK(0x06));
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x30), 0x00FF);
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x06), 0x3F3F);
	पूर्ण अन्यथा अणु
		b43_ग_लिखो16(dev, 0x3E2, b43_पढ़ो16(dev, 0x3E2)
			    | 0x8000);
	पूर्ण
	b43_ग_लिखो16(dev, 0x3F4, b43_पढ़ो16(dev, 0x3F4)
		    & 0xF000);

	पंचांगp =
	    (phy->type == B43_PHYTYPE_G) ? B43_PHY_LO_MASK : B43_PHY_CCK(0x2E);
	b43_phy_ग_लिखो(dev, पंचांगp, 0x007F);

	पंचांगp = sav->phy_syncctl;
	b43_phy_ग_लिखो(dev, B43_PHY_SYNCCTL, पंचांगp & 0xFF7F);
	पंचांगp = sav->radio_7A;
	b43_radio_ग_लिखो16(dev, 0x007A, पंचांगp & 0xFFF0);

	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2A), 0x8A3);
	अगर (phy->type == B43_PHYTYPE_G ||
	    (phy->type == B43_PHYTYPE_B &&
	     phy->radio_ver == 0x2050 && phy->radio_rev >= 6)) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2B), 0x1003);
	पूर्ण अन्यथा
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2B), 0x0802);
	अगर (phy->rev >= 2)
		b43_dummy_transmission(dev, false, true);
	b43_gphy_channel_चयन(dev, 6, 0);
	b43_radio_पढ़ो16(dev, 0x51);	/* dummy पढ़ो */
	अगर (phy->type == B43_PHYTYPE_G)
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2F), 0);

	/* Re-measure the txctl values, अगर needed. */
	अगर (समय_beक्रमe(lo->txctl_measured_समय,
			jअगरfies - B43_LO_TXCTL_EXPIRE))
		lo_measure_txctl_values(dev);

	अगर (phy->type == B43_PHYTYPE_G && phy->rev >= 3) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, 0xC078);
	पूर्ण अन्यथा अणु
		अगर (phy->type == B43_PHYTYPE_B)
			b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2E), 0x8078);
		अन्यथा
			b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, 0x8078);
	पूर्ण
पूर्ण

अटल व्योम lo_measure_restore(काष्ठा b43_wldev *dev,
			       काष्ठा lo_g_saved_values *sav)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	u16 पंचांगp;

	अगर (phy->rev >= 2) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, 0xE300);
		पंचांगp = (gphy->pga_gain << 8);
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, पंचांगp | 0xA0);
		udelay(5);
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, पंचांगp | 0xA2);
		udelay(2);
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, पंचांगp | 0xA3);
	पूर्ण अन्यथा अणु
		पंचांगp = (gphy->pga_gain | 0xEFA0);
		b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, पंचांगp);
	पूर्ण
	अगर (phy->type == B43_PHYTYPE_G) अणु
		अगर (phy->rev >= 3)
			b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2E), 0xC078);
		अन्यथा
			b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2E), 0x8078);
		अगर (phy->rev >= 2)
			b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2F), 0x0202);
		अन्यथा
			b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2F), 0x0101);
	पूर्ण
	b43_ग_लिखो16(dev, 0x3F4, sav->reg_3F4);
	b43_phy_ग_लिखो(dev, B43_PHY_PGACTL, sav->phy_pgactl);
	b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x2A), sav->phy_cck_2A);
	b43_phy_ग_लिखो(dev, B43_PHY_SYNCCTL, sav->phy_syncctl);
	b43_phy_ग_लिखो(dev, B43_PHY_DACCTL, sav->phy_dacctl);
	b43_radio_ग_लिखो16(dev, 0x43, sav->radio_43);
	b43_radio_ग_लिखो16(dev, 0x7A, sav->radio_7A);
	अगर (!has_tx_magnअगरication(phy)) अणु
		पंचांगp = sav->radio_52;
		b43_radio_maskset(dev, 0x52, 0xFF0F, पंचांगp);
	पूर्ण
	b43_ग_लिखो16(dev, 0x3E2, sav->reg_3E2);
	अगर (phy->type == B43_PHYTYPE_B &&
	    phy->radio_ver == 0x2050 && phy->radio_rev <= 5) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x30), sav->phy_cck_30);
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x06), sav->phy_cck_06);
	पूर्ण
	अगर (phy->rev >= 2) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_ANALOGOVER, sav->phy_analogover);
		b43_phy_ग_लिखो(dev, B43_PHY_ANALOGOVERVAL,
			      sav->phy_analogoverval);
		b43_phy_ग_लिखो(dev, B43_PHY_CLASSCTL, sav->phy_classctl);
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVER, sav->phy_rfover);
		b43_phy_ग_लिखो(dev, B43_PHY_RFOVERVAL, sav->phy_rfoverval);
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x3E), sav->phy_cck_3E);
		b43_phy_ग_लिखो(dev, B43_PHY_CRS0, sav->phy_crs0);
	पूर्ण
	अगर (b43_has_hardware_pctl(dev)) अणु
		पंचांगp = (sav->phy_lo_mask & 0xBFFF);
		b43_phy_ग_लिखो(dev, B43_PHY_LO_MASK, पंचांगp);
		b43_phy_ग_लिखो(dev, B43_PHY_EXTG(0x01), sav->phy_extg_01);
		b43_phy_ग_लिखो(dev, B43_PHY_DACCTL, sav->phy_dacctl_hwpctl);
		b43_phy_ग_लिखो(dev, B43_PHY_CCK(0x14), sav->phy_cck_14);
		b43_phy_ग_लिखो(dev, B43_PHY_HPWR_TSSICTL, sav->phy_hpwr_tssictl);
	पूर्ण
	b43_gphy_channel_चयन(dev, sav->old_channel, 1);
पूर्ण

काष्ठा b43_lo_g_statemachine अणु
	पूर्णांक current_state;
	पूर्णांक nr_measured;
	पूर्णांक state_val_multiplier;
	u16 lowest_feedth;
	काष्ठा b43_loctl min_loctl;
पूर्ण;

/* Loop over each possible value in this state. */
अटल पूर्णांक lo_probe_possible_loctls(काष्ठा b43_wldev *dev,
				    काष्ठा b43_loctl *probe_loctl,
				    काष्ठा b43_lo_g_statemachine *d)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_loctl test_loctl;
	काष्ठा b43_loctl orig_loctl;
	काष्ठा b43_loctl prev_loctl = अणु
		.i = -100,
		.q = -100,
	पूर्ण;
	पूर्णांक i;
	पूर्णांक begin, end;
	पूर्णांक found_lower = 0;
	u16 feedth;

	अटल स्थिर काष्ठा b43_loctl modअगरiers[] = अणु
		अणु.i = 1,.q = 1,पूर्ण,
		अणु.i = 1,.q = 0,पूर्ण,
		अणु.i = 1,.q = -1,पूर्ण,
		अणु.i = 0,.q = -1,पूर्ण,
		अणु.i = -1,.q = -1,पूर्ण,
		अणु.i = -1,.q = 0,पूर्ण,
		अणु.i = -1,.q = 1,पूर्ण,
		अणु.i = 0,.q = 1,पूर्ण,
	पूर्ण;

	अगर (d->current_state == 0) अणु
		begin = 1;
		end = 8;
	पूर्ण अन्यथा अगर (d->current_state % 2 == 0) अणु
		begin = d->current_state - 1;
		end = d->current_state + 1;
	पूर्ण अन्यथा अणु
		begin = d->current_state - 2;
		end = d->current_state + 2;
	पूर्ण
	अगर (begin < 1)
		begin += 8;
	अगर (end > 8)
		end -= 8;

	स_नकल(&orig_loctl, probe_loctl, माप(काष्ठा b43_loctl));
	i = begin;
	d->current_state = i;
	जबतक (1) अणु
		B43_WARN_ON(!(i >= 1 && i <= 8));
		स_नकल(&test_loctl, &orig_loctl, माप(काष्ठा b43_loctl));
		test_loctl.i += modअगरiers[i - 1].i * d->state_val_multiplier;
		test_loctl.q += modअगरiers[i - 1].q * d->state_val_multiplier;
		अगर ((test_loctl.i != prev_loctl.i ||
		     test_loctl.q != prev_loctl.q) &&
		    (असल(test_loctl.i) <= 16 && असल(test_loctl.q) <= 16)) अणु
			b43_lo_ग_लिखो(dev, &test_loctl);
			feedth = lo_measure_feedthrough(dev, gphy->lna_gain,
							gphy->pga_gain,
							gphy->trsw_rx_gain);
			अगर (feedth < d->lowest_feedth) अणु
				स_नकल(probe_loctl, &test_loctl,
				       माप(काष्ठा b43_loctl));
				found_lower = 1;
				d->lowest_feedth = feedth;
				अगर ((d->nr_measured < 2) &&
				    !has_loopback_gain(phy))
					अवरोध;
			पूर्ण
		पूर्ण
		स_नकल(&prev_loctl, &test_loctl, माप(prev_loctl));
		अगर (i == end)
			अवरोध;
		अगर (i == 8)
			i = 1;
		अन्यथा
			i++;
		d->current_state = i;
	पूर्ण

	वापस found_lower;
पूर्ण

अटल व्योम lo_probe_loctls_statemachine(काष्ठा b43_wldev *dev,
					 काष्ठा b43_loctl *loctl,
					 पूर्णांक *max_rx_gain)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_lo_g_statemachine d;
	u16 feedth;
	पूर्णांक found_lower;
	काष्ठा b43_loctl probe_loctl;
	पूर्णांक max_repeat = 1, repeat_cnt = 0;

	d.nr_measured = 0;
	d.state_val_multiplier = 1;
	अगर (has_loopback_gain(phy))
		d.state_val_multiplier = 3;

	स_नकल(&d.min_loctl, loctl, माप(काष्ठा b43_loctl));
	अगर (has_loopback_gain(phy))
		max_repeat = 4;
	करो अणु
		b43_lo_ग_लिखो(dev, &d.min_loctl);
		feedth = lo_measure_feedthrough(dev, gphy->lna_gain,
						gphy->pga_gain,
						gphy->trsw_rx_gain);
		अगर (feedth < 0x258) अणु
			अगर (feedth >= 0x12C)
				*max_rx_gain += 6;
			अन्यथा
				*max_rx_gain += 3;
			feedth = lo_measure_feedthrough(dev, gphy->lna_gain,
							gphy->pga_gain,
							gphy->trsw_rx_gain);
		पूर्ण
		d.lowest_feedth = feedth;

		d.current_state = 0;
		करो अणु
			B43_WARN_ON(!
				    (d.current_state >= 0
				     && d.current_state <= 8));
			स_नकल(&probe_loctl, &d.min_loctl,
			       माप(काष्ठा b43_loctl));
			found_lower =
			    lo_probe_possible_loctls(dev, &probe_loctl, &d);
			अगर (!found_lower)
				अवरोध;
			अगर ((probe_loctl.i == d.min_loctl.i) &&
			    (probe_loctl.q == d.min_loctl.q))
				अवरोध;
			स_नकल(&d.min_loctl, &probe_loctl,
			       माप(काष्ठा b43_loctl));
			d.nr_measured++;
		पूर्ण जबतक (d.nr_measured < 24);
		स_नकल(loctl, &d.min_loctl, माप(काष्ठा b43_loctl));

		अगर (has_loopback_gain(phy)) अणु
			अगर (d.lowest_feedth > 0x1194)
				*max_rx_gain -= 6;
			अन्यथा अगर (d.lowest_feedth < 0x5DC)
				*max_rx_gain += 3;
			अगर (repeat_cnt == 0) अणु
				अगर (d.lowest_feedth <= 0x5DC) अणु
					d.state_val_multiplier = 1;
					repeat_cnt++;
				पूर्ण अन्यथा
					d.state_val_multiplier = 2;
			पूर्ण अन्यथा अगर (repeat_cnt == 2)
				d.state_val_multiplier = 1;
		पूर्ण
		lo_measure_gain_values(dev, *max_rx_gain,
				       has_loopback_gain(phy));
	पूर्ण जबतक (++repeat_cnt < max_repeat);
पूर्ण

अटल
काष्ठा b43_lo_calib *b43_calibrate_lo_setting(काष्ठा b43_wldev *dev,
					      स्थिर काष्ठा b43_bbatt *bbatt,
					      स्थिर काष्ठा b43_rfatt *rfatt)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_loctl loctl = अणु
		.i = 0,
		.q = 0,
	पूर्ण;
	पूर्णांक max_rx_gain;
	काष्ठा b43_lo_calib *cal;
	काष्ठा lo_g_saved_values saved_regs;
	/* Values from the "TXCTL Register and Value Table" */
	u16 txctl_reg;
	u16 txctl_value;
	u16 pad_mix_gain;

	saved_regs.old_channel = phy->channel;
	b43_mac_suspend(dev);
	lo_measure_setup(dev, &saved_regs);

	txctl_reg = lo_txctl_रेजिस्टर_table(dev, &txctl_value, &pad_mix_gain);

	b43_radio_maskset(dev, 0x43, 0xFFF0, rfatt->att);
	b43_radio_maskset(dev, txctl_reg, ~txctl_value, (rfatt->with_padmix ? txctl_value :0));

	max_rx_gain = rfatt->att * 2;
	max_rx_gain += bbatt->att / 2;
	अगर (rfatt->with_padmix)
		max_rx_gain -= pad_mix_gain;
	अगर (has_loopback_gain(phy))
		max_rx_gain += gphy->max_lb_gain;
	lo_measure_gain_values(dev, max_rx_gain,
			       has_loopback_gain(phy));

	b43_gphy_set_baseband_attenuation(dev, bbatt->att);
	lo_probe_loctls_statemachine(dev, &loctl, &max_rx_gain);

	lo_measure_restore(dev, &saved_regs);
	b43_mac_enable(dev);

	अगर (b43_debug(dev, B43_DBG_LO)) अणु
		b43dbg(dev->wl, "LO: Calibrated for BB(%u), RF(%u,%u) "
		       "=> I=%d Q=%d\n",
		       bbatt->att, rfatt->att, rfatt->with_padmix,
		       loctl.i, loctl.q);
	पूर्ण

	cal = kदो_स्मृति(माप(*cal), GFP_KERNEL);
	अगर (!cal) अणु
		b43warn(dev->wl, "LO calib: out of memory\n");
		वापस शून्य;
	पूर्ण
	स_नकल(&cal->bbatt, bbatt, माप(*bbatt));
	स_नकल(&cal->rfatt, rfatt, माप(*rfatt));
	स_नकल(&cal->ctl, &loctl, माप(loctl));
	cal->calib_समय = jअगरfies;
	INIT_LIST_HEAD(&cal->list);

	वापस cal;
पूर्ण

/* Get a calibrated LO setting क्रम the given attenuation values.
 * Might वापस a शून्य poपूर्णांकer under OOM! */
अटल
काष्ठा b43_lo_calib *b43_get_calib_lo_settings(काष्ठा b43_wldev *dev,
					       स्थिर काष्ठा b43_bbatt *bbatt,
					       स्थिर काष्ठा b43_rfatt *rfatt)
अणु
	काष्ठा b43_txघातer_lo_control *lo = dev->phy.g->lo_control;
	काष्ठा b43_lo_calib *c;

	c = b43_find_lo_calib(lo, bbatt, rfatt);
	अगर (c)
		वापस c;
	/* Not in the list of calibrated LO settings.
	 * Calibrate it now. */
	c = b43_calibrate_lo_setting(dev, bbatt, rfatt);
	अगर (!c)
		वापस शून्य;
	list_add(&c->list, &lo->calib_list);

	वापस c;
पूर्ण

व्योम b43_gphy_dc_lt_init(काष्ठा b43_wldev *dev, bool update_all)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_txघातer_lo_control *lo = gphy->lo_control;
	पूर्णांक i;
	पूर्णांक rf_offset, bb_offset;
	स्थिर काष्ठा b43_rfatt *rfatt;
	स्थिर काष्ठा b43_bbatt *bbatt;
	u64 घातer_vector;
	bool table_changed = false;

	BUILD_BUG_ON(B43_DC_LT_SIZE != 32);
	B43_WARN_ON(lo->rfatt_list.len * lo->bbatt_list.len > 64);

	घातer_vector = lo->घातer_vector;
	अगर (!update_all && !घातer_vector)
		वापस; /* Nothing to करो. */

	/* Suspend the MAC now to aव्योम continuous suspend/enable
	 * cycles in the loop. */
	b43_mac_suspend(dev);

	क्रम (i = 0; i < B43_DC_LT_SIZE * 2; i++) अणु
		काष्ठा b43_lo_calib *cal;
		पूर्णांक idx;
		u16 val;

		अगर (!update_all && !(घातer_vector & (((u64)1ULL) << i)))
			जारी;
		/* Update the table entry क्रम this घातer_vector bit.
		 * The table rows are RFatt entries and columns are BBatt. */
		bb_offset = i / lo->rfatt_list.len;
		rf_offset = i % lo->rfatt_list.len;
		bbatt = &(lo->bbatt_list.list[bb_offset]);
		rfatt = &(lo->rfatt_list.list[rf_offset]);

		cal = b43_calibrate_lo_setting(dev, bbatt, rfatt);
		अगर (!cal) अणु
			b43warn(dev->wl, "LO: Could not "
				"calibrate DC table entry\n");
			जारी;
		पूर्ण
		/*FIXME: Is Q really in the low nibble? */
		val = (u8)(cal->ctl.q);
		val |= ((u8)(cal->ctl.i)) << 4;
		kमुक्त(cal);

		/* Get the index पूर्णांकo the hardware DC LT. */
		idx = i / 2;
		/* Change the table in memory. */
		अगर (i % 2) अणु
			/* Change the high byte. */
			lo->dc_lt[idx] = (lo->dc_lt[idx] & 0x00FF)
					 | ((val & 0x00FF) << 8);
		पूर्ण अन्यथा अणु
			/* Change the low byte. */
			lo->dc_lt[idx] = (lo->dc_lt[idx] & 0xFF00)
					 | (val & 0x00FF);
		पूर्ण
		table_changed = true;
	पूर्ण
	अगर (table_changed) अणु
		/* The table changed in memory. Update the hardware table. */
		क्रम (i = 0; i < B43_DC_LT_SIZE; i++)
			b43_phy_ग_लिखो(dev, 0x3A0 + i, lo->dc_lt[i]);
	पूर्ण
	b43_mac_enable(dev);
पूर्ण

/* Fixup the RF attenuation value क्रम the हाल where we are
 * using the PAD mixer. */
अटल अंतरभूत व्योम b43_lo_fixup_rfatt(काष्ठा b43_rfatt *rf)
अणु
	अगर (!rf->with_padmix)
		वापस;
	अगर ((rf->att != 1) && (rf->att != 2) && (rf->att != 3))
		rf->att = 4;
पूर्ण

व्योम b43_lo_g_adjust(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_g *gphy = dev->phy.g;
	काष्ठा b43_lo_calib *cal;
	काष्ठा b43_rfatt rf;

	स_नकल(&rf, &gphy->rfatt, माप(rf));
	b43_lo_fixup_rfatt(&rf);

	cal = b43_get_calib_lo_settings(dev, &gphy->bbatt, &rf);
	अगर (!cal)
		वापस;
	b43_lo_ग_लिखो(dev, &cal->ctl);
पूर्ण

व्योम b43_lo_g_adjust_to(काष्ठा b43_wldev *dev,
			u16 rfatt, u16 bbatt, u16 tx_control)
अणु
	काष्ठा b43_rfatt rf;
	काष्ठा b43_bbatt bb;
	काष्ठा b43_lo_calib *cal;

	स_रखो(&rf, 0, माप(rf));
	स_रखो(&bb, 0, माप(bb));
	rf.att = rfatt;
	bb.att = bbatt;
	b43_lo_fixup_rfatt(&rf);
	cal = b43_get_calib_lo_settings(dev, &bb, &rf);
	अगर (!cal)
		वापस;
	b43_lo_ग_लिखो(dev, &cal->ctl);
पूर्ण

/* Periodic LO मुख्यtenance work */
व्योम b43_lo_g_मुख्यtenance_work(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
	काष्ठा b43_txघातer_lo_control *lo = gphy->lo_control;
	अचिन्हित दीर्घ now;
	अचिन्हित दीर्घ expire;
	काष्ठा b43_lo_calib *cal, *पंचांगp;
	bool current_item_expired = false;
	bool hwpctl;

	अगर (!lo)
		वापस;
	now = jअगरfies;
	hwpctl = b43_has_hardware_pctl(dev);

	अगर (hwpctl) अणु
		/* Read the घातer vector and update it, अगर needed. */
		expire = now - B43_LO_PWRVEC_EXPIRE;
		अगर (समय_beक्रमe(lo->pwr_vec_पढ़ो_समय, expire)) अणु
			lo_पढ़ो_घातer_vector(dev);
			b43_gphy_dc_lt_init(dev, 0);
		पूर्ण
		//FIXME Recalc the whole DC table from समय to समय?
	पूर्ण

	अगर (hwpctl)
		वापस;
	/* Search क्रम expired LO settings. Remove them.
	 * Recalibrate the current setting, अगर expired. */
	expire = now - B43_LO_CALIB_EXPIRE;
	list_क्रम_each_entry_safe(cal, पंचांगp, &lo->calib_list, list) अणु
		अगर (!समय_beक्रमe(cal->calib_समय, expire))
			जारी;
		/* This item expired. */
		अगर (b43_compare_bbatt(&cal->bbatt, &gphy->bbatt) &&
		    b43_compare_rfatt(&cal->rfatt, &gphy->rfatt)) अणु
			B43_WARN_ON(current_item_expired);
			current_item_expired = true;
		पूर्ण
		अगर (b43_debug(dev, B43_DBG_LO)) अणु
			b43dbg(dev->wl, "LO: Item BB(%u), RF(%u,%u), "
			       "I=%d, Q=%d expired\n",
			       cal->bbatt.att, cal->rfatt.att,
			       cal->rfatt.with_padmix,
			       cal->ctl.i, cal->ctl.q);
		पूर्ण
		list_del(&cal->list);
		kमुक्त(cal);
	पूर्ण
	अगर (current_item_expired || unlikely(list_empty(&lo->calib_list))) अणु
		/* Recalibrate currently used LO setting. */
		अगर (b43_debug(dev, B43_DBG_LO))
			b43dbg(dev->wl, "LO: Recalibrating current LO setting\n");
		cal = b43_calibrate_lo_setting(dev, &gphy->bbatt, &gphy->rfatt);
		अगर (cal) अणु
			list_add(&cal->list, &lo->calib_list);
			b43_lo_ग_लिखो(dev, &cal->ctl);
		पूर्ण अन्यथा
			b43warn(dev->wl, "Failed to recalibrate current LO setting\n");
	पूर्ण
पूर्ण

व्योम b43_lo_g_cleanup(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_txघातer_lo_control *lo = dev->phy.g->lo_control;
	काष्ठा b43_lo_calib *cal, *पंचांगp;

	अगर (!lo)
		वापस;
	list_क्रम_each_entry_safe(cal, पंचांगp, &lo->calib_list, list) अणु
		list_del(&cal->list);
		kमुक्त(cal);
	पूर्ण
पूर्ण

/* LO Initialization */
व्योम b43_lo_g_init(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_has_hardware_pctl(dev)) अणु
		lo_पढ़ो_घातer_vector(dev);
		b43_gphy_dc_lt_init(dev, 1);
	पूर्ण
पूर्ण
