<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver
  IEEE 802.11a/g LP-PHY driver

  Copyright (c) 2008-2009 Michael Buesch <m@bues.ch>
  Copyright (c) 2009 Gथँbor Stefanik <netrolller.3d@gmail.com>


*/

#समावेश <linux/cordic.h>
#समावेश <linux/slab.h>

#समावेश "b43.h"
#समावेश "main.h"
#समावेश "phy_lp.h"
#समावेश "phy_common.h"
#समावेश "tables_lpphy.h"


अटल अंतरभूत u16 channel2freq_lp(u8 channel)
अणु
	अगर (channel < 14)
		वापस (2407 + 5 * channel);
	अन्यथा अगर (channel == 14)
		वापस 2484;
	अन्यथा अगर (channel < 184)
		वापस (5000 + 5 * channel);
	अन्यथा
		वापस (4000 + 5 * channel);
पूर्ण

अटल अचिन्हित पूर्णांक b43_lpphy_op_get_शेष_chan(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		वापस 1;
	वापस 36;
पूर्ण

अटल पूर्णांक b43_lpphy_op_allocate(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy;

	lpphy = kzalloc(माप(*lpphy), GFP_KERNEL);
	अगर (!lpphy)
		वापस -ENOMEM;
	dev->phy.lp = lpphy;

	वापस 0;
पूर्ण

अटल व्योम b43_lpphy_op_prepare_काष्ठाs(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_lp *lpphy = phy->lp;

	स_रखो(lpphy, 0, माप(*lpphy));
	lpphy->antenna = B43_ANTENNA_DEFAULT;

	//TODO
पूर्ण

अटल व्योम b43_lpphy_op_मुक्त(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;

	kमुक्त(lpphy);
	dev->phy.lp = शून्य;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/LP/ReadBandSrom */
अटल व्योम lpphy_पढ़ो_band_sprom(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	u16 cckpo, maxpwr;
	u32 ofdmpo;
	पूर्णांक i;

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		lpphy->tx_isolation_med_band = sprom->tri2g;
		lpphy->bx_arch = sprom->bxa2g;
		lpphy->rx_pwr_offset = sprom->rxpo2g;
		lpphy->rssi_vf = sprom->rssismf2g;
		lpphy->rssi_vc = sprom->rssismc2g;
		lpphy->rssi_gs = sprom->rssisav2g;
		lpphy->txpa[0] = sprom->pa0b0;
		lpphy->txpa[1] = sprom->pa0b1;
		lpphy->txpa[2] = sprom->pa0b2;
		maxpwr = sprom->maxpwr_bg;
		lpphy->max_tx_pwr_med_band = maxpwr;
		cckpo = sprom->cck2gpo;
		अगर (cckpo) अणु
			ofdmpo = sprom->ofdm2gpo;
			क्रम (i = 0; i < 4; i++) अणु
				lpphy->tx_max_rate[i] =
					maxpwr - (ofdmpo & 0xF) * 2;
				ofdmpo >>= 4;
			पूर्ण
			ofdmpo = sprom->ofdm2gpo;
			क्रम (i = 4; i < 15; i++) अणु
				lpphy->tx_max_rate[i] =
					maxpwr - (ofdmpo & 0xF) * 2;
				ofdmpo >>= 4;
			पूर्ण
		पूर्ण अन्यथा अणु
			u8 opo = sprom->opo;
			क्रम (i = 0; i < 4; i++)
				lpphy->tx_max_rate[i] = maxpwr;
			क्रम (i = 4; i < 15; i++)
				lpphy->tx_max_rate[i] = maxpwr - opo;
		पूर्ण
	पूर्ण अन्यथा अणु /* 5GHz */
		lpphy->tx_isolation_low_band = sprom->tri5gl;
		lpphy->tx_isolation_med_band = sprom->tri5g;
		lpphy->tx_isolation_hi_band = sprom->tri5gh;
		lpphy->bx_arch = sprom->bxa5g;
		lpphy->rx_pwr_offset = sprom->rxpo5g;
		lpphy->rssi_vf = sprom->rssismf5g;
		lpphy->rssi_vc = sprom->rssismc5g;
		lpphy->rssi_gs = sprom->rssisav5g;
		lpphy->txpa[0] = sprom->pa1b0;
		lpphy->txpa[1] = sprom->pa1b1;
		lpphy->txpa[2] = sprom->pa1b2;
		lpphy->txpal[0] = sprom->pa1lob0;
		lpphy->txpal[1] = sprom->pa1lob1;
		lpphy->txpal[2] = sprom->pa1lob2;
		lpphy->txpah[0] = sprom->pa1hib0;
		lpphy->txpah[1] = sprom->pa1hib1;
		lpphy->txpah[2] = sprom->pa1hib2;
		maxpwr = sprom->maxpwr_al;
		ofdmpo = sprom->ofdm5glpo;
		lpphy->max_tx_pwr_low_band = maxpwr;
		क्रम (i = 4; i < 12; i++) अणु
			lpphy->tx_max_ratel[i] = maxpwr - (ofdmpo & 0xF) * 2;
			ofdmpo >>= 4;
		पूर्ण
		maxpwr = sprom->maxpwr_a;
		ofdmpo = sprom->ofdm5gpo;
		lpphy->max_tx_pwr_med_band = maxpwr;
		क्रम (i = 4; i < 12; i++) अणु
			lpphy->tx_max_rate[i] = maxpwr - (ofdmpo & 0xF) * 2;
			ofdmpo >>= 4;
		पूर्ण
		maxpwr = sprom->maxpwr_ah;
		ofdmpo = sprom->ofdm5ghpo;
		lpphy->max_tx_pwr_hi_band = maxpwr;
		क्रम (i = 4; i < 12; i++) अणु
			lpphy->tx_max_rateh[i] = maxpwr - (ofdmpo & 0xF) * 2;
			ofdmpo >>= 4;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम lpphy_adjust_gain_table(काष्ठा b43_wldev *dev, u32 freq)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	u16 temp[3];
	u16 isolation;

	B43_WARN_ON(dev->phy.rev >= 2);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		isolation = lpphy->tx_isolation_med_band;
	अन्यथा अगर (freq <= 5320)
		isolation = lpphy->tx_isolation_low_band;
	अन्यथा अगर (freq <= 5700)
		isolation = lpphy->tx_isolation_med_band;
	अन्यथा
		isolation = lpphy->tx_isolation_hi_band;

	temp[0] = ((isolation - 26) / 12) << 12;
	temp[1] = temp[0] + 0x1000;
	temp[2] = temp[0] + 0x2000;

	b43_lptab_ग_लिखो_bulk(dev, B43_LPTAB16(13, 0), 3, temp);
	b43_lptab_ग_लिखो_bulk(dev, B43_LPTAB16(12, 0), 3, temp);
पूर्ण

अटल व्योम lpphy_table_init(काष्ठा b43_wldev *dev)
अणु
	u32 freq = channel2freq_lp(b43_lpphy_op_get_शेष_chan(dev));

	अगर (dev->phy.rev < 2)
		lpphy_rev0_1_table_init(dev);
	अन्यथा
		lpphy_rev2plus_table_init(dev);

	lpphy_init_tx_gain_table(dev);

	अगर (dev->phy.rev < 2)
		lpphy_adjust_gain_table(dev, freq);
पूर्ण

अटल व्योम lpphy_baseband_rev0_1_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_bus *bus = dev->dev->sdev->bus;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	u16 पंचांगp, पंचांगp2;

	b43_phy_mask(dev, B43_LPPHY_AFE_DAC_CTL, 0xF7FF);
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_CTL, 0);
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_CTL_OVR, 0);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RF_OVERRIDE_0, 0);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RF_OVERRIDE_2, 0);
	b43_phy_set(dev, B43_LPPHY_AFE_DAC_CTL, 0x0004);
	b43_phy_maskset(dev, B43_LPPHY_OFDMSYNCTHRESH0, 0xFF00, 0x0078);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0x83FF, 0x5800);
	b43_phy_ग_लिखो(dev, B43_LPPHY_ADC_COMPENSATION_CTL, 0x0016);
	b43_phy_maskset(dev, B43_LPPHY_AFE_ADC_CTL_0, 0xFFF8, 0x0004);
	b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0x00FF, 0x5400);
	b43_phy_maskset(dev, B43_LPPHY_HIGAINDB, 0x00FF, 0x2400);
	b43_phy_maskset(dev, B43_LPPHY_LOWGAINDB, 0x00FF, 0x2100);
	b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0xFF00, 0x0006);
	b43_phy_mask(dev, B43_LPPHY_RX_RADIO_CTL, 0xFFFE);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0xFFE0, 0x0005);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0xFC1F, 0x0180);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0x83FF, 0x3C00);
	b43_phy_maskset(dev, B43_LPPHY_GAINसूचीECTMISMATCH, 0xFFF0, 0x0005);
	b43_phy_maskset(dev, B43_LPPHY_GAIN_MISMATCH_LIMIT, 0xFFC0, 0x001A);
	b43_phy_maskset(dev, B43_LPPHY_CRS_ED_THRESH, 0xFF00, 0x00B3);
	b43_phy_maskset(dev, B43_LPPHY_CRS_ED_THRESH, 0x00FF, 0xAD00);
	b43_phy_maskset(dev, B43_LPPHY_INPUT_PWRDB,
			0xFF00, lpphy->rx_pwr_offset);
	अगर ((sprom->boardflags_lo & B43_BFL_FEM) &&
	   ((b43_current_band(dev->wl) == NL80211_BAND_5GHZ) ||
	   (sprom->boardflags_hi & B43_BFH_PAREF))) अणु
		ssb_pmu_set_lकरो_voltage(&bus->chipco, LDO_PAREF, 0x28);
		ssb_pmu_set_lकरो_paref(&bus->chipco, true);
		अगर (dev->phy.rev == 0) अणु
			b43_phy_maskset(dev, B43_LPPHY_LP_RF_SIGNAL_LUT,
					0xFFCF, 0x0010);
		पूर्ण
		b43_lptab_ग_लिखो(dev, B43_LPTAB16(11, 7), 60);
	पूर्ण अन्यथा अणु
		ssb_pmu_set_lकरो_paref(&bus->chipco, false);
		b43_phy_maskset(dev, B43_LPPHY_LP_RF_SIGNAL_LUT,
				0xFFCF, 0x0020);
		b43_lptab_ग_लिखो(dev, B43_LPTAB16(11, 7), 100);
	पूर्ण
	पंचांगp = lpphy->rssi_vf | lpphy->rssi_vc << 4 | 0xA000;
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_RSSI_CTL_0, पंचांगp);
	अगर (sprom->boardflags_hi & B43_BFH_RSSIINV)
		b43_phy_maskset(dev, B43_LPPHY_AFE_RSSI_CTL_1, 0xF000, 0x0AAA);
	अन्यथा
		b43_phy_maskset(dev, B43_LPPHY_AFE_RSSI_CTL_1, 0xF000, 0x02AA);
	b43_lptab_ग_लिखो(dev, B43_LPTAB16(11, 1), 24);
	b43_phy_maskset(dev, B43_LPPHY_RX_RADIO_CTL,
			0xFFF9, (lpphy->bx_arch << 1));
	अगर (dev->phy.rev == 1 &&
	   (sprom->boardflags_hi & B43_BFH_FEM_BT)) अणु
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0x3F00, 0x0900);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xC0FF, 0x0400);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_5, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_5, 0xC0FF, 0x0900);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_6, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_6, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_7, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_7, 0xC0FF, 0x0900);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_8, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_8, 0xC0FF, 0x0B00);
	पूर्ण अन्यथा अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ ||
		   (dev->dev->board_type == SSB_BOARD_BU4312) ||
		   (dev->phy.rev == 0 && (sprom->boardflags_lo & B43_BFL_FEM))) अणु
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xFFC0, 0x0001);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xC0FF, 0x0400);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xFFC0, 0x0001);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xC0FF, 0x0500);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xC0FF, 0x0800);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xC0FF, 0x0A00);
	पूर्ण अन्यथा अगर (dev->phy.rev == 1 ||
		  (sprom->boardflags_lo & B43_BFL_FEM)) अणु
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xFFC0, 0x0004);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xC0FF, 0x0800);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xFFC0, 0x0004);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xC0FF, 0x0C00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xC0FF, 0x0100);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xC0FF, 0x0300);
	पूर्ण अन्यथा अणु
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xC0FF, 0x0900);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xFFC0, 0x0006);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xC0FF, 0x0500);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xFFC0, 0x0006);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xC0FF, 0x0700);
	पूर्ण
	अगर (dev->phy.rev == 1 && (sprom->boardflags_hi & B43_BFH_PAREF)) अणु
		b43_phy_copy(dev, B43_LPPHY_TR_LOOKUP_5, B43_LPPHY_TR_LOOKUP_1);
		b43_phy_copy(dev, B43_LPPHY_TR_LOOKUP_6, B43_LPPHY_TR_LOOKUP_2);
		b43_phy_copy(dev, B43_LPPHY_TR_LOOKUP_7, B43_LPPHY_TR_LOOKUP_3);
		b43_phy_copy(dev, B43_LPPHY_TR_LOOKUP_8, B43_LPPHY_TR_LOOKUP_4);
	पूर्ण
	अगर ((sprom->boardflags_hi & B43_BFH_FEM_BT) &&
	    (dev->dev->chip_id == 0x5354) &&
	    (dev->dev->chip_pkg == SSB_CHIPPACK_BCM4712S)) अणु
		b43_phy_set(dev, B43_LPPHY_CRSGAIN_CTL, 0x0006);
		b43_phy_ग_लिखो(dev, B43_LPPHY_GPIO_SELECT, 0x0005);
		b43_phy_ग_लिखो(dev, B43_LPPHY_GPIO_OUTEN, 0xFFFF);
		//FIXME the Broadcom driver caches & delays this HF ग_लिखो!
		b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) | B43_HF_PR45960W);
	पूर्ण
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		b43_phy_set(dev, B43_LPPHY_LP_PHY_CTL, 0x8000);
		b43_phy_set(dev, B43_LPPHY_CRSGAIN_CTL, 0x0040);
		b43_phy_maskset(dev, B43_LPPHY_MINPWR_LEVEL, 0x00FF, 0xA400);
		b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL, 0xF0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_SYNCPEAKCNT, 0xFFF8, 0x0007);
		b43_phy_maskset(dev, B43_LPPHY_DSSS_CONFIRM_CNT, 0xFFF8, 0x0003);
		b43_phy_maskset(dev, B43_LPPHY_DSSS_CONFIRM_CNT, 0xFFC7, 0x0020);
		b43_phy_mask(dev, B43_LPPHY_IDLEAFTERPKTRXTO, 0x00FF);
	पूर्ण अन्यथा अणु /* 5GHz */
		b43_phy_mask(dev, B43_LPPHY_LP_PHY_CTL, 0x7FFF);
		b43_phy_mask(dev, B43_LPPHY_CRSGAIN_CTL, 0xFFBF);
	पूर्ण
	अगर (dev->phy.rev == 1) अणु
		पंचांगp = b43_phy_पढ़ो(dev, B43_LPPHY_CLIPCTRTHRESH);
		पंचांगp2 = (पंचांगp & 0x03E0) >> 5;
		पंचांगp2 |= पंचांगp2 << 5;
		b43_phy_ग_लिखो(dev, B43_LPPHY_4C3, पंचांगp2);
		पंचांगp = b43_phy_पढ़ो(dev, B43_LPPHY_GAINसूचीECTMISMATCH);
		पंचांगp2 = (पंचांगp & 0x1F00) >> 8;
		पंचांगp2 |= पंचांगp2 << 5;
		b43_phy_ग_लिखो(dev, B43_LPPHY_4C4, पंचांगp2);
		पंचांगp = b43_phy_पढ़ो(dev, B43_LPPHY_VERYLOWGAINDB);
		पंचांगp2 = पंचांगp & 0x00FF;
		पंचांगp2 |= पंचांगp << 8;
		b43_phy_ग_लिखो(dev, B43_LPPHY_4C5, पंचांगp2);
	पूर्ण
पूर्ण

अटल व्योम lpphy_save_dig_flt_state(काष्ठा b43_wldev *dev)
अणु
	अटल स्थिर u16 addr[] = अणु
		B43_PHY_OFDM(0xC1),
		B43_PHY_OFDM(0xC2),
		B43_PHY_OFDM(0xC3),
		B43_PHY_OFDM(0xC4),
		B43_PHY_OFDM(0xC5),
		B43_PHY_OFDM(0xC6),
		B43_PHY_OFDM(0xC7),
		B43_PHY_OFDM(0xC8),
		B43_PHY_OFDM(0xCF),
	पूर्ण;

	अटल स्थिर u16 coefs[] = अणु
		0xDE5E, 0xE832, 0xE331, 0x4D26,
		0x0026, 0x1420, 0x0020, 0xFE08,
		0x0008,
	पूर्ण;

	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(addr); i++) अणु
		lpphy->dig_flt_state[i] = b43_phy_पढ़ो(dev, addr[i]);
		b43_phy_ग_लिखो(dev, addr[i], coefs[i]);
	पूर्ण
पूर्ण

अटल व्योम lpphy_restore_dig_flt_state(काष्ठा b43_wldev *dev)
अणु
	अटल स्थिर u16 addr[] = अणु
		B43_PHY_OFDM(0xC1),
		B43_PHY_OFDM(0xC2),
		B43_PHY_OFDM(0xC3),
		B43_PHY_OFDM(0xC4),
		B43_PHY_OFDM(0xC5),
		B43_PHY_OFDM(0xC6),
		B43_PHY_OFDM(0xC7),
		B43_PHY_OFDM(0xC8),
		B43_PHY_OFDM(0xCF),
	पूर्ण;

	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(addr); i++)
		b43_phy_ग_लिखो(dev, addr[i], lpphy->dig_flt_state[i]);
पूर्ण

अटल व्योम lpphy_baseband_rev2plus_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;

	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_DAC_CTL, 0x50);
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_CTL, 0x8800);
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_CTL_OVR, 0);
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RF_OVERRIDE_0, 0);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RF_OVERRIDE_2, 0);
	b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0xF9), 0);
	b43_phy_ग_लिखो(dev, B43_LPPHY_TR_LOOKUP_1, 0);
	b43_phy_set(dev, B43_LPPHY_ADC_COMPENSATION_CTL, 0x10);
	b43_phy_maskset(dev, B43_LPPHY_OFDMSYNCTHRESH0, 0xFF00, 0xB4);
	b43_phy_maskset(dev, B43_LPPHY_DCOFFSETTRANSIENT, 0xF8FF, 0x200);
	b43_phy_maskset(dev, B43_LPPHY_DCOFFSETTRANSIENT, 0xFF00, 0x7F);
	b43_phy_maskset(dev, B43_LPPHY_GAINसूचीECTMISMATCH, 0xFF0F, 0x40);
	b43_phy_maskset(dev, B43_LPPHY_PREAMBLECONFIRMTO, 0xFF00, 0x2);
	b43_phy_mask(dev, B43_LPPHY_CRSGAIN_CTL, ~0x4000);
	b43_phy_mask(dev, B43_LPPHY_CRSGAIN_CTL, ~0x2000);
	b43_phy_set(dev, B43_PHY_OFDM(0x10A), 0x1);
	अगर (dev->dev->board_rev >= 0x18) अणु
		b43_lptab_ग_लिखो(dev, B43_LPTAB32(17, 65), 0xEC);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x10A), 0xFF01, 0x14);
	पूर्ण अन्यथा अणु
		b43_phy_maskset(dev, B43_PHY_OFDM(0x10A), 0xFF01, 0x10);
	पूर्ण
	b43_phy_maskset(dev, B43_PHY_OFDM(0xDF), 0xFF00, 0xF4);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xDF), 0x00FF, 0xF100);
	b43_phy_ग_लिखो(dev, B43_LPPHY_CLIPTHRESH, 0x48);
	b43_phy_maskset(dev, B43_LPPHY_HIGAINDB, 0xFF00, 0x46);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xE4), 0xFF00, 0x10);
	b43_phy_maskset(dev, B43_LPPHY_PWR_THRESH1, 0xFFF0, 0x9);
	b43_phy_mask(dev, B43_LPPHY_GAINसूचीECTMISMATCH, ~0xF);
	b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0x00FF, 0x5500);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0xFC1F, 0xA0);
	b43_phy_maskset(dev, B43_LPPHY_GAINसूचीECTMISMATCH, 0xE0FF, 0x300);
	b43_phy_maskset(dev, B43_LPPHY_HIGAINDB, 0x00FF, 0x2A00);
	अगर ((dev->dev->chip_id == 0x4325) && (dev->dev->chip_rev == 0)) अणु
		b43_phy_maskset(dev, B43_LPPHY_LOWGAINDB, 0x00FF, 0x2100);
		b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0xFF00, 0xA);
	पूर्ण अन्यथा अणु
		b43_phy_maskset(dev, B43_LPPHY_LOWGAINDB, 0x00FF, 0x1E00);
		b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0xFF00, 0xD);
	पूर्ण
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFE), 0xFFE0, 0x1F);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFF), 0xFFE0, 0xC);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x100), 0xFF00, 0x19);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFF), 0x03FF, 0x3C00);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFE), 0xFC1F, 0x3E0);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFF), 0xFFE0, 0xC);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x100), 0x00FF, 0x1900);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0x83FF, 0x5800);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0xFFE0, 0x12);
	b43_phy_maskset(dev, B43_LPPHY_GAINMISMATCH, 0x0FFF, 0x9000);

	अगर ((dev->dev->chip_id == 0x4325) && (dev->dev->chip_rev == 0)) अणु
		b43_lptab_ग_लिखो(dev, B43_LPTAB16(0x08, 0x14), 0);
		b43_lptab_ग_लिखो(dev, B43_LPTAB16(0x08, 0x12), 0x40);
	पूर्ण

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		b43_phy_set(dev, B43_LPPHY_CRSGAIN_CTL, 0x40);
		b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL, 0xF0FF, 0xB00);
		b43_phy_maskset(dev, B43_LPPHY_SYNCPEAKCNT, 0xFFF8, 0x6);
		b43_phy_maskset(dev, B43_LPPHY_MINPWR_LEVEL, 0x00FF, 0x9D00);
		b43_phy_maskset(dev, B43_LPPHY_MINPWR_LEVEL, 0xFF00, 0xA1);
		b43_phy_mask(dev, B43_LPPHY_IDLEAFTERPKTRXTO, 0x00FF);
	पूर्ण अन्यथा /* 5GHz */
		b43_phy_mask(dev, B43_LPPHY_CRSGAIN_CTL, ~0x40);

	b43_phy_maskset(dev, B43_LPPHY_CRS_ED_THRESH, 0xFF00, 0xB3);
	b43_phy_maskset(dev, B43_LPPHY_CRS_ED_THRESH, 0x00FF, 0xAD00);
	b43_phy_maskset(dev, B43_LPPHY_INPUT_PWRDB, 0xFF00, lpphy->rx_pwr_offset);
	b43_phy_set(dev, B43_LPPHY_RESET_CTL, 0x44);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RESET_CTL, 0x80);
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_RSSI_CTL_0, 0xA954);
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_RSSI_CTL_1,
		      0x2000 | ((u16)lpphy->rssi_gs << 10) |
		      ((u16)lpphy->rssi_vc << 4) | lpphy->rssi_vf);

	अगर ((dev->dev->chip_id == 0x4325) && (dev->dev->chip_rev == 0)) अणु
		b43_phy_set(dev, B43_LPPHY_AFE_ADC_CTL_0, 0x1C);
		b43_phy_maskset(dev, B43_LPPHY_AFE_CTL, 0x00FF, 0x8800);
		b43_phy_maskset(dev, B43_LPPHY_AFE_ADC_CTL_1, 0xFC3C, 0x0400);
	पूर्ण

	lpphy_save_dig_flt_state(dev);
पूर्ण

अटल व्योम lpphy_baseband_init(काष्ठा b43_wldev *dev)
अणु
	lpphy_table_init(dev);
	अगर (dev->phy.rev >= 2)
		lpphy_baseband_rev2plus_init(dev);
	अन्यथा
		lpphy_baseband_rev0_1_init(dev);
पूर्ण

काष्ठा b2062_freqdata अणु
	u16 freq;
	u8 data[6];
पूर्ण;

/* Initialize the 2062 radio. */
अटल व्योम lpphy_2062_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	काष्ठा ssb_bus *bus = dev->dev->sdev->bus;
	u32 crystalfreq, पंचांगp, ref;
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा b2062_freqdata *fd = शून्य;

	अटल स्थिर काष्ठा b2062_freqdata freqdata_tab[] = अणु
		अणु .freq = 12000, .data[0] =  6, .data[1] =  6, .data[2] =  6,
				 .data[3] =  6, .data[4] = 10, .data[5] =  6, पूर्ण,
		अणु .freq = 13000, .data[0] =  4, .data[1] =  4, .data[2] =  4,
				 .data[3] =  4, .data[4] = 11, .data[5] =  7, पूर्ण,
		अणु .freq = 14400, .data[0] =  3, .data[1] =  3, .data[2] =  3,
				 .data[3] =  3, .data[4] = 12, .data[5] =  7, पूर्ण,
		अणु .freq = 16200, .data[0] =  3, .data[1] =  3, .data[2] =  3,
				 .data[3] =  3, .data[4] = 13, .data[5] =  8, पूर्ण,
		अणु .freq = 18000, .data[0] =  2, .data[1] =  2, .data[2] =  2,
				 .data[3] =  2, .data[4] = 14, .data[5] =  8, पूर्ण,
		अणु .freq = 19200, .data[0] =  1, .data[1] =  1, .data[2] =  1,
				 .data[3] =  1, .data[4] = 14, .data[5] =  9, पूर्ण,
	पूर्ण;

	b2062_upload_init_table(dev);

	b43_radio_ग_लिखो(dev, B2062_N_TX_CTL3, 0);
	b43_radio_ग_लिखो(dev, B2062_N_TX_CTL4, 0);
	b43_radio_ग_लिखो(dev, B2062_N_TX_CTL5, 0);
	b43_radio_ग_लिखो(dev, B2062_N_TX_CTL6, 0);
	b43_radio_ग_लिखो(dev, B2062_N_PDN_CTL0, 0x40);
	b43_radio_ग_लिखो(dev, B2062_N_PDN_CTL0, 0);
	b43_radio_ग_लिखो(dev, B2062_N_CALIB_TS, 0x10);
	b43_radio_ग_लिखो(dev, B2062_N_CALIB_TS, 0);
	अगर (dev->phy.rev > 0) अणु
		b43_radio_ग_लिखो(dev, B2062_S_BG_CTL1,
			(b43_radio_पढ़ो(dev, B2062_N_COMM2) >> 1) | 0x80);
	पूर्ण
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		b43_radio_set(dev, B2062_N_TSSI_CTL0, 0x1);
	अन्यथा
		b43_radio_mask(dev, B2062_N_TSSI_CTL0, ~0x1);

	/* Get the crystal freq, in Hz. */
	crystalfreq = bus->chipco.pmu.crystalfreq * 1000;

	B43_WARN_ON(!(bus->chipco.capabilities & SSB_CHIPCO_CAP_PMU));
	B43_WARN_ON(crystalfreq == 0);

	अगर (crystalfreq <= 30000000) अणु
		lpphy->pभाग = 1;
		b43_radio_mask(dev, B2062_S_RFPLL_CTL1, 0xFFFB);
	पूर्ण अन्यथा अणु
		lpphy->pभाग = 2;
		b43_radio_set(dev, B2062_S_RFPLL_CTL1, 0x4);
	पूर्ण

	पंचांगp = (((800000000 * lpphy->pभाग + crystalfreq) /
	      (2 * crystalfreq)) - 8) & 0xFF;
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL7, पंचांगp);

	पंचांगp = (((100 * crystalfreq + 16000000 * lpphy->pभाग) /
	      (32000000 * lpphy->pभाग)) - 1) & 0xFF;
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL18, पंचांगp);

	पंचांगp = (((2 * crystalfreq + 1000000 * lpphy->pभाग) /
	      (2000000 * lpphy->pभाग)) - 1) & 0xFF;
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL19, पंचांगp);

	ref = (1000 * lpphy->pभाग + 2 * crystalfreq) / (2000 * lpphy->pभाग);
	ref &= 0xFFFF;
	क्रम (i = 0; i < ARRAY_SIZE(freqdata_tab); i++) अणु
		अगर (ref < freqdata_tab[i].freq) अणु
			fd = &freqdata_tab[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!fd)
		fd = &freqdata_tab[ARRAY_SIZE(freqdata_tab) - 1];
	b43dbg(dev->wl, "b2062: Using crystal tab entry %u kHz.\n",
	       fd->freq); /* FIXME: Keep this prपूर्णांकk until the code is fully debugged. */

	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL8,
			((u16)(fd->data[1]) << 4) | fd->data[0]);
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL9,
			((u16)(fd->data[3]) << 4) | fd->data[2]);
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL10, fd->data[4]);
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL11, fd->data[5]);
पूर्ण

/* Initialize the 2063 radio. */
अटल व्योम lpphy_2063_init(काष्ठा b43_wldev *dev)
अणु
	b2063_upload_init_table(dev);
	b43_radio_ग_लिखो(dev, B2063_LOGEN_SP5, 0);
	b43_radio_set(dev, B2063_COMM8, 0x38);
	b43_radio_ग_लिखो(dev, B2063_REG_SP1, 0x56);
	b43_radio_mask(dev, B2063_RX_BB_CTL2, ~0x2);
	b43_radio_ग_लिखो(dev, B2063_PA_SP7, 0);
	b43_radio_ग_लिखो(dev, B2063_TX_RF_SP6, 0x20);
	b43_radio_ग_लिखो(dev, B2063_TX_RF_SP9, 0x40);
	अगर (dev->phy.rev == 2) अणु
		b43_radio_ग_लिखो(dev, B2063_PA_SP3, 0xa0);
		b43_radio_ग_लिखो(dev, B2063_PA_SP4, 0xa0);
		b43_radio_ग_लिखो(dev, B2063_PA_SP2, 0x18);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो(dev, B2063_PA_SP3, 0x20);
		b43_radio_ग_लिखो(dev, B2063_PA_SP2, 0x20);
	पूर्ण
पूर्ण

काष्ठा lpphy_stx_table_entry अणु
	u16 phy_offset;
	u16 phy_shअगरt;
	u16 rf_addr;
	u16 rf_shअगरt;
	u16 mask;
पूर्ण;

अटल स्थिर काष्ठा lpphy_stx_table_entry lpphy_stx_table[] = अणु
	अणु .phy_offset = 2, .phy_shअगरt = 6, .rf_addr = 0x3d, .rf_shअगरt = 3, .mask = 0x01, पूर्ण,
	अणु .phy_offset = 1, .phy_shअगरt = 12, .rf_addr = 0x4c, .rf_shअगरt = 1, .mask = 0x01, पूर्ण,
	अणु .phy_offset = 1, .phy_shअगरt = 8, .rf_addr = 0x50, .rf_shअगरt = 0, .mask = 0x7f, पूर्ण,
	अणु .phy_offset = 0, .phy_shअगरt = 8, .rf_addr = 0x44, .rf_shअगरt = 0, .mask = 0xff, पूर्ण,
	अणु .phy_offset = 1, .phy_shअगरt = 0, .rf_addr = 0x4a, .rf_shअगरt = 0, .mask = 0xff, पूर्ण,
	अणु .phy_offset = 0, .phy_shअगरt = 4, .rf_addr = 0x4d, .rf_shअगरt = 0, .mask = 0xff, पूर्ण,
	अणु .phy_offset = 1, .phy_shअगरt = 4, .rf_addr = 0x4e, .rf_shअगरt = 0, .mask = 0xff, पूर्ण,
	अणु .phy_offset = 0, .phy_shअगरt = 12, .rf_addr = 0x4f, .rf_shअगरt = 0, .mask = 0x0f, पूर्ण,
	अणु .phy_offset = 1, .phy_shअगरt = 0, .rf_addr = 0x4f, .rf_shअगरt = 4, .mask = 0x0f, पूर्ण,
	अणु .phy_offset = 3, .phy_shअगरt = 0, .rf_addr = 0x49, .rf_shअगरt = 0, .mask = 0x0f, पूर्ण,
	अणु .phy_offset = 4, .phy_shअगरt = 3, .rf_addr = 0x46, .rf_shअगरt = 4, .mask = 0x07, पूर्ण,
	अणु .phy_offset = 3, .phy_shअगरt = 15, .rf_addr = 0x46, .rf_shअगरt = 0, .mask = 0x01, पूर्ण,
	अणु .phy_offset = 4, .phy_shअगरt = 0, .rf_addr = 0x46, .rf_shअगरt = 1, .mask = 0x07, पूर्ण,
	अणु .phy_offset = 3, .phy_shअगरt = 8, .rf_addr = 0x48, .rf_shअगरt = 4, .mask = 0x07, पूर्ण,
	अणु .phy_offset = 3, .phy_shअगरt = 11, .rf_addr = 0x48, .rf_shअगरt = 0, .mask = 0x0f, पूर्ण,
	अणु .phy_offset = 3, .phy_shअगरt = 4, .rf_addr = 0x49, .rf_shअगरt = 4, .mask = 0x0f, पूर्ण,
	अणु .phy_offset = 2, .phy_shअगरt = 15, .rf_addr = 0x45, .rf_shअगरt = 0, .mask = 0x01, पूर्ण,
	अणु .phy_offset = 5, .phy_shअगरt = 13, .rf_addr = 0x52, .rf_shअगरt = 4, .mask = 0x07, पूर्ण,
	अणु .phy_offset = 6, .phy_shअगरt = 0, .rf_addr = 0x52, .rf_shअगरt = 7, .mask = 0x01, पूर्ण,
	अणु .phy_offset = 5, .phy_shअगरt = 3, .rf_addr = 0x41, .rf_shअगरt = 5, .mask = 0x07, पूर्ण,
	अणु .phy_offset = 5, .phy_shअगरt = 6, .rf_addr = 0x41, .rf_shअगरt = 0, .mask = 0x0f, पूर्ण,
	अणु .phy_offset = 5, .phy_shअगरt = 10, .rf_addr = 0x42, .rf_shअगरt = 5, .mask = 0x07, पूर्ण,
	अणु .phy_offset = 4, .phy_shअगरt = 15, .rf_addr = 0x42, .rf_shअगरt = 0, .mask = 0x01, पूर्ण,
	अणु .phy_offset = 5, .phy_shअगरt = 0, .rf_addr = 0x42, .rf_shअगरt = 1, .mask = 0x07, पूर्ण,
	अणु .phy_offset = 4, .phy_shअगरt = 11, .rf_addr = 0x43, .rf_shअगरt = 4, .mask = 0x0f, पूर्ण,
	अणु .phy_offset = 4, .phy_shअगरt = 7, .rf_addr = 0x43, .rf_shअगरt = 0, .mask = 0x0f, पूर्ण,
	अणु .phy_offset = 4, .phy_shअगरt = 6, .rf_addr = 0x45, .rf_shअगरt = 1, .mask = 0x01, पूर्ण,
	अणु .phy_offset = 2, .phy_shअगरt = 7, .rf_addr = 0x40, .rf_shअगरt = 4, .mask = 0x0f, पूर्ण,
	अणु .phy_offset = 2, .phy_shअगरt = 11, .rf_addr = 0x40, .rf_shअगरt = 0, .mask = 0x0f, पूर्ण,
पूर्ण;

अटल व्योम lpphy_sync_stx(काष्ठा b43_wldev *dev)
अणु
	स्थिर काष्ठा lpphy_stx_table_entry *e;
	अचिन्हित पूर्णांक i;
	u16 पंचांगp;

	क्रम (i = 0; i < ARRAY_SIZE(lpphy_stx_table); i++) अणु
		e = &lpphy_stx_table[i];
		पंचांगp = b43_radio_पढ़ो(dev, e->rf_addr);
		पंचांगp >>= e->rf_shअगरt;
		पंचांगp <<= e->phy_shअगरt;
		b43_phy_maskset(dev, B43_PHY_OFDM(0xF2 + e->phy_offset),
				~(e->mask << e->phy_shअगरt), पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम lpphy_radio_init(काष्ठा b43_wldev *dev)
अणु
	/* The radio is attached through the 4wire bus. */
	b43_phy_set(dev, B43_LPPHY_FOURWIRE_CTL, 0x2);
	udelay(1);
	b43_phy_mask(dev, B43_LPPHY_FOURWIRE_CTL, 0xFFFD);
	udelay(1);

	अगर (dev->phy.radio_ver == 0x2062) अणु
		lpphy_2062_init(dev);
	पूर्ण अन्यथा अणु
		lpphy_2063_init(dev);
		lpphy_sync_stx(dev);
		b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0xF0), 0x5F80);
		b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0xF1), 0);
		अगर (dev->dev->chip_id == 0x4325) अणु
			// TODO SSB PMU recalibration
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा lpphy_iq_est अणु u32 iq_prod, i_pwr, q_pwr; पूर्ण;

अटल व्योम lpphy_set_rc_cap(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;

	u8 rc_cap = (lpphy->rc_cap & 0x1F) >> 1;

	अगर (dev->phy.rev == 1) //FIXME check channel 14!
		rc_cap = min_t(u8, rc_cap + 5, 15);

	b43_radio_ग_लिखो(dev, B2062_N_RXBB_CALIB2,
			max_t(u8, lpphy->rc_cap - 4, 0x80));
	b43_radio_ग_लिखो(dev, B2062_N_TX_CTL_A, rc_cap | 0x80);
	b43_radio_ग_लिखो(dev, B2062_S_RXG_CNT16,
			((lpphy->rc_cap & 0x1F) >> 2) | 0x80);
पूर्ण

अटल u8 lpphy_get_bb_mult(काष्ठा b43_wldev *dev)
अणु
	वापस (b43_lptab_पढ़ो(dev, B43_LPTAB16(0, 87)) & 0xFF00) >> 8;
पूर्ण

अटल व्योम lpphy_set_bb_mult(काष्ठा b43_wldev *dev, u8 bb_mult)
अणु
	b43_lptab_ग_लिखो(dev, B43_LPTAB16(0, 87), (u16)bb_mult << 8);
पूर्ण

अटल व्योम lpphy_set_deaf(काष्ठा b43_wldev *dev, bool user)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;

	अगर (user)
		lpphy->crs_usr_disable = true;
	अन्यथा
		lpphy->crs_sys_disable = true;
	b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL, 0xFF1F, 0x80);
पूर्ण

अटल व्योम lpphy_clear_deaf(काष्ठा b43_wldev *dev, bool user)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;

	अगर (user)
		lpphy->crs_usr_disable = false;
	अन्यथा
		lpphy->crs_sys_disable = false;

	अगर (!lpphy->crs_usr_disable && !lpphy->crs_sys_disable) अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
			b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL,
					0xFF1F, 0x60);
		अन्यथा
			b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL,
					0xFF1F, 0x20);
	पूर्ण
पूर्ण

अटल व्योम lpphy_set_trsw_over(काष्ठा b43_wldev *dev, bool tx, bool rx)
अणु
	u16 trsw = (tx << 1) | rx;
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFFC, trsw);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x3);
पूर्ण

अटल व्योम lpphy_disable_crs(काष्ठा b43_wldev *dev, bool user)
अणु
	lpphy_set_deaf(dev, user);
	lpphy_set_trsw_over(dev, false, true);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFFB);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x4);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFF7);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x8);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x10);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x10);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFDF);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x20);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFBF);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x40);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0x7);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0x38);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFF3F);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0x100);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFDFF);
	b43_phy_ग_लिखो(dev, B43_LPPHY_PS_CTL_OVERRIDE_VAL0, 0);
	b43_phy_ग_लिखो(dev, B43_LPPHY_PS_CTL_OVERRIDE_VAL1, 1);
	b43_phy_ग_लिखो(dev, B43_LPPHY_PS_CTL_OVERRIDE_VAL2, 0x20);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFBFF);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xF7FF);
	b43_phy_ग_लिखो(dev, B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL, 0);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RX_GAIN_CTL_OVERRIDE_VAL, 0x45AF);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RF_OVERRIDE_2, 0x3FF);
पूर्ण

अटल व्योम lpphy_restore_crs(काष्ठा b43_wldev *dev, bool user)
अणु
	lpphy_clear_deaf(dev, user);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFF80);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xFC00);
पूर्ण

काष्ठा lpphy_tx_gains अणु u16 gm, pga, pad, dac; पूर्ण;

अटल व्योम lpphy_disable_rx_gain_override(काष्ठा b43_wldev *dev)
अणु
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFFFE);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFFEF);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFFBF);
	अगर (dev->phy.rev >= 2) अणु
		b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xFEFF);
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
			b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xFBFF);
			b43_phy_mask(dev, B43_PHY_OFDM(0xE5), 0xFFF7);
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xFDFF);
	पूर्ण
पूर्ण

अटल व्योम lpphy_enable_rx_gain_override(काष्ठा b43_wldev *dev)
अणु
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x1);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x10);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x40);
	अगर (dev->phy.rev >= 2) अणु
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x100);
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
			b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x400);
			b43_phy_set(dev, B43_PHY_OFDM(0xE5), 0x8);
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x200);
	पूर्ण
पूर्ण

अटल व्योम lpphy_disable_tx_gain_override(काष्ठा b43_wldev *dev)
अणु
	अगर (dev->phy.rev < 2)
		b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xFEFF);
	अन्यथा अणु
		b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xFF7F);
		b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xBFFF);
	पूर्ण
	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVR, 0xFFBF);
पूर्ण

अटल व्योम lpphy_enable_tx_gain_override(काष्ठा b43_wldev *dev)
अणु
	अगर (dev->phy.rev < 2)
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x100);
	अन्यथा अणु
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x80);
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x4000);
	पूर्ण
	b43_phy_set(dev, B43_LPPHY_AFE_CTL_OVR, 0x40);
पूर्ण

अटल काष्ठा lpphy_tx_gains lpphy_get_tx_gains(काष्ठा b43_wldev *dev)
अणु
	काष्ठा lpphy_tx_gains gains;
	u16 पंचांगp;

	gains.dac = (b43_phy_पढ़ो(dev, B43_LPPHY_AFE_DAC_CTL) & 0x380) >> 7;
	अगर (dev->phy.rev < 2) अणु
		पंचांगp = b43_phy_पढ़ो(dev,
				   B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL) & 0x7FF;
		gains.gm = पंचांगp & 0x0007;
		gains.pga = (पंचांगp & 0x0078) >> 3;
		gains.pad = (पंचांगp & 0x780) >> 7;
	पूर्ण अन्यथा अणु
		पंचांगp = b43_phy_पढ़ो(dev, B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL);
		gains.pad = b43_phy_पढ़ो(dev, B43_PHY_OFDM(0xFB)) & 0xFF;
		gains.gm = पंचांगp & 0xFF;
		gains.pga = (पंचांगp >> 8) & 0xFF;
	पूर्ण

	वापस gains;
पूर्ण

अटल व्योम lpphy_set_dac_gain(काष्ठा b43_wldev *dev, u16 dac)
अणु
	u16 ctl = b43_phy_पढ़ो(dev, B43_LPPHY_AFE_DAC_CTL) & 0xC7F;
	ctl |= dac << 7;
	b43_phy_maskset(dev, B43_LPPHY_AFE_DAC_CTL, 0xF000, ctl);
पूर्ण

अटल u16 lpphy_get_pa_gain(काष्ठा b43_wldev *dev)
अणु
	वापस b43_phy_पढ़ो(dev, B43_PHY_OFDM(0xFB)) & 0x7F;
पूर्ण

अटल व्योम lpphy_set_pa_gain(काष्ठा b43_wldev *dev, u16 gain)
अणु
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFB), 0xE03F, gain << 6);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFD), 0x80FF, gain << 8);
पूर्ण

अटल व्योम lpphy_set_tx_gains(काष्ठा b43_wldev *dev,
			       काष्ठा lpphy_tx_gains gains)
अणु
	u16 rf_gain, pa_gain;

	अगर (dev->phy.rev < 2) अणु
		rf_gain = (gains.pad << 7) | (gains.pga << 3) | gains.gm;
		b43_phy_maskset(dev, B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL,
				0xF800, rf_gain);
	पूर्ण अन्यथा अणु
		pa_gain = lpphy_get_pa_gain(dev);
		b43_phy_ग_लिखो(dev, B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL,
			      (gains.pga << 8) | gains.gm);
		/*
		 * SPEC FIXME The spec calls क्रम (pa_gain << 8) here, but that
		 * conflicts with the spec क्रम set_pa_gain! Venकरोr driver bug?
		 */
		b43_phy_maskset(dev, B43_PHY_OFDM(0xFB),
				0x8000, gains.pad | (pa_gain << 6));
		b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0xFC),
			      (gains.pga << 8) | gains.gm);
		b43_phy_maskset(dev, B43_PHY_OFDM(0xFD),
				0x8000, gains.pad | (pa_gain << 8));
	पूर्ण
	lpphy_set_dac_gain(dev, gains.dac);
	lpphy_enable_tx_gain_override(dev);
पूर्ण

अटल व्योम lpphy_rev0_1_set_rx_gain(काष्ठा b43_wldev *dev, u32 gain)
अणु
	u16 trsw = gain & 0x1;
	u16 lna = (gain & 0xFFFC) | ((gain & 0xC) >> 2);
	u16 ext_lna = (gain & 2) >> 1;

	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFFE, trsw);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL,
			0xFBFF, ext_lna << 10);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL,
			0xF7FF, ext_lna << 11);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RX_GAIN_CTL_OVERRIDE_VAL, lna);
पूर्ण

अटल व्योम lpphy_rev2plus_set_rx_gain(काष्ठा b43_wldev *dev, u32 gain)
अणु
	u16 low_gain = gain & 0xFFFF;
	u16 high_gain = (gain >> 16) & 0xF;
	u16 ext_lna = (gain >> 21) & 0x1;
	u16 trsw = ~(gain >> 20) & 0x1;
	u16 पंचांगp;

	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFFE, trsw);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL,
			0xFDFF, ext_lna << 9);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL,
			0xFBFF, ext_lna << 10);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RX_GAIN_CTL_OVERRIDE_VAL, low_gain);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS, 0xFFF0, high_gain);
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		पंचांगp = (gain >> 2) & 0x3;
		b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL,
				0xE7FF, पंचांगp<<11);
		b43_phy_maskset(dev, B43_PHY_OFDM(0xE6), 0xFFE7, पंचांगp << 3);
	पूर्ण
पूर्ण

अटल व्योम lpphy_set_rx_gain(काष्ठा b43_wldev *dev, u32 gain)
अणु
	अगर (dev->phy.rev < 2)
		lpphy_rev0_1_set_rx_gain(dev, gain);
	अन्यथा
		lpphy_rev2plus_set_rx_gain(dev, gain);
	lpphy_enable_rx_gain_override(dev);
पूर्ण

अटल व्योम lpphy_set_rx_gain_by_index(काष्ठा b43_wldev *dev, u16 idx)
अणु
	u32 gain = b43_lptab_पढ़ो(dev, B43_LPTAB16(12, idx));
	lpphy_set_rx_gain(dev, gain);
पूर्ण

अटल व्योम lpphy_stop_ddfs(काष्ठा b43_wldev *dev)
अणु
	b43_phy_mask(dev, B43_LPPHY_AFE_DDFS, 0xFFFD);
	b43_phy_mask(dev, B43_LPPHY_LP_PHY_CTL, 0xFFDF);
पूर्ण

अटल व्योम lpphy_run_ddfs(काष्ठा b43_wldev *dev, पूर्णांक i_on, पूर्णांक q_on,
			   पूर्णांक incr1, पूर्णांक incr2, पूर्णांक scale_idx)
अणु
	lpphy_stop_ddfs(dev);
	b43_phy_mask(dev, B43_LPPHY_AFE_DDFS_POINTER_INIT, 0xFF80);
	b43_phy_mask(dev, B43_LPPHY_AFE_DDFS_POINTER_INIT, 0x80FF);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS_INCR_INIT, 0xFF80, incr1);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS_INCR_INIT, 0x80FF, incr2 << 8);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS, 0xFFF7, i_on << 3);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS, 0xFFEF, q_on << 4);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS, 0xFF9F, scale_idx << 5);
	b43_phy_mask(dev, B43_LPPHY_AFE_DDFS, 0xFFFB);
	b43_phy_set(dev, B43_LPPHY_AFE_DDFS, 0x2);
	b43_phy_set(dev, B43_LPPHY_LP_PHY_CTL, 0x20);
पूर्ण

अटल bool lpphy_rx_iq_est(काष्ठा b43_wldev *dev, u16 samples, u8 समय,
			   काष्ठा lpphy_iq_est *iq_est)
अणु
	पूर्णांक i;

	b43_phy_mask(dev, B43_LPPHY_CRSGAIN_CTL, 0xFFF7);
	b43_phy_ग_लिखो(dev, B43_LPPHY_IQ_NUM_SMPLS_ADDR, samples);
	b43_phy_maskset(dev, B43_LPPHY_IQ_ENABLE_WAIT_TIME_ADDR, 0xFF00, समय);
	b43_phy_mask(dev, B43_LPPHY_IQ_ENABLE_WAIT_TIME_ADDR, 0xFEFF);
	b43_phy_set(dev, B43_LPPHY_IQ_ENABLE_WAIT_TIME_ADDR, 0x200);

	क्रम (i = 0; i < 500; i++) अणु
		अगर (!(b43_phy_पढ़ो(dev,
				B43_LPPHY_IQ_ENABLE_WAIT_TIME_ADDR) & 0x200))
			अवरोध;
		msleep(1);
	पूर्ण

	अगर ((b43_phy_पढ़ो(dev, B43_LPPHY_IQ_ENABLE_WAIT_TIME_ADDR) & 0x200)) अणु
		b43_phy_set(dev, B43_LPPHY_CRSGAIN_CTL, 0x8);
		वापस false;
	पूर्ण

	iq_est->iq_prod = b43_phy_पढ़ो(dev, B43_LPPHY_IQ_ACC_HI_ADDR);
	iq_est->iq_prod <<= 16;
	iq_est->iq_prod |= b43_phy_पढ़ो(dev, B43_LPPHY_IQ_ACC_LO_ADDR);

	iq_est->i_pwr = b43_phy_पढ़ो(dev, B43_LPPHY_IQ_I_PWR_ACC_HI_ADDR);
	iq_est->i_pwr <<= 16;
	iq_est->i_pwr |= b43_phy_पढ़ो(dev, B43_LPPHY_IQ_I_PWR_ACC_LO_ADDR);

	iq_est->q_pwr = b43_phy_पढ़ो(dev, B43_LPPHY_IQ_Q_PWR_ACC_HI_ADDR);
	iq_est->q_pwr <<= 16;
	iq_est->q_pwr |= b43_phy_पढ़ो(dev, B43_LPPHY_IQ_Q_PWR_ACC_LO_ADDR);

	b43_phy_set(dev, B43_LPPHY_CRSGAIN_CTL, 0x8);
	वापस true;
पूर्ण

अटल पूर्णांक lpphy_loopback(काष्ठा b43_wldev *dev)
अणु
	काष्ठा lpphy_iq_est iq_est;
	पूर्णांक i, index = -1;
	u32 पंचांगp;

	स_रखो(&iq_est, 0, माप(iq_est));

	lpphy_set_trsw_over(dev, true, true);
	b43_phy_set(dev, B43_LPPHY_AFE_CTL_OVR, 1);
	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0xFFFE);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x800);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x800);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x8);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x8);
	b43_radio_ग_लिखो(dev, B2062_N_TX_CTL_A, 0x80);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x80);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x80);
	क्रम (i = 0; i < 32; i++) अणु
		lpphy_set_rx_gain_by_index(dev, i);
		lpphy_run_ddfs(dev, 1, 1, 5, 5, 0);
		अगर (!(lpphy_rx_iq_est(dev, 1000, 32, &iq_est)))
			जारी;
		पंचांगp = (iq_est.i_pwr + iq_est.q_pwr) / 1000;
		अगर ((पंचांगp > 4000) && (पंचांगp < 10000)) अणु
			index = i;
			अवरोध;
		पूर्ण
	पूर्ण
	lpphy_stop_ddfs(dev);
	वापस index;
पूर्ण

/* Fixed-poपूर्णांक भागision algorithm using only पूर्णांकeger math. */
अटल u32 lpphy_qभाग_roundup(u32 भागidend, u32 भागisor, u8 precision)
अणु
	u32 quotient, reमुख्यder;

	अगर (भागisor == 0)
		वापस 0;

	quotient = भागidend / भागisor;
	reमुख्यder = भागidend % भागisor;

	जबतक (precision > 0) अणु
		quotient <<= 1;
		अगर (reमुख्यder << 1 >= भागisor) अणु
			quotient++;
			reमुख्यder = (reमुख्यder << 1) - भागisor;
		पूर्ण
		precision--;
	पूर्ण

	अगर (reमुख्यder << 1 >= भागisor)
		quotient++;

	वापस quotient;
पूर्ण

/* Read the TX घातer control mode from hardware. */
अटल व्योम lpphy_पढ़ो_tx_pctl_mode_from_hardware(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	u16 ctl;

	ctl = b43_phy_पढ़ो(dev, B43_LPPHY_TX_PWR_CTL_CMD);
	चयन (ctl & B43_LPPHY_TX_PWR_CTL_CMD_MODE) अणु
	हाल B43_LPPHY_TX_PWR_CTL_CMD_MODE_OFF:
		lpphy->txpctl_mode = B43_LPPHY_TXPCTL_OFF;
		अवरोध;
	हाल B43_LPPHY_TX_PWR_CTL_CMD_MODE_SW:
		lpphy->txpctl_mode = B43_LPPHY_TXPCTL_SW;
		अवरोध;
	हाल B43_LPPHY_TX_PWR_CTL_CMD_MODE_HW:
		lpphy->txpctl_mode = B43_LPPHY_TXPCTL_HW;
		अवरोध;
	शेष:
		lpphy->txpctl_mode = B43_LPPHY_TXPCTL_UNKNOWN;
		B43_WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

/* Set the TX घातer control mode in hardware. */
अटल व्योम lpphy_ग_लिखो_tx_pctl_mode_to_hardware(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	u16 ctl;

	चयन (lpphy->txpctl_mode) अणु
	हाल B43_LPPHY_TXPCTL_OFF:
		ctl = B43_LPPHY_TX_PWR_CTL_CMD_MODE_OFF;
		अवरोध;
	हाल B43_LPPHY_TXPCTL_HW:
		ctl = B43_LPPHY_TX_PWR_CTL_CMD_MODE_HW;
		अवरोध;
	हाल B43_LPPHY_TXPCTL_SW:
		ctl = B43_LPPHY_TX_PWR_CTL_CMD_MODE_SW;
		अवरोध;
	शेष:
		ctl = 0;
		B43_WARN_ON(1);
	पूर्ण
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_CMD,
			~B43_LPPHY_TX_PWR_CTL_CMD_MODE & 0xFFFF, ctl);
पूर्ण

अटल व्योम lpphy_set_tx_घातer_control(काष्ठा b43_wldev *dev,
				       क्रमागत b43_lpphy_txpctl_mode mode)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	क्रमागत b43_lpphy_txpctl_mode oldmode;

	lpphy_पढ़ो_tx_pctl_mode_from_hardware(dev);
	oldmode = lpphy->txpctl_mode;
	अगर (oldmode == mode)
		वापस;
	lpphy->txpctl_mode = mode;

	अगर (oldmode == B43_LPPHY_TXPCTL_HW) अणु
		//TODO Update TX Power NPT
		//TODO Clear all TX Power offsets
	पूर्ण अन्यथा अणु
		अगर (mode == B43_LPPHY_TXPCTL_HW) अणु
			//TODO Recalculate target TX घातer
			b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_CMD,
					0xFF80, lpphy->tssi_idx);
			b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_NNUM,
					0x8FFF, ((u16)lpphy->tssi_npt << 16));
			//TODO Set "TSSI Transmit Count" variable to total transmitted frame count
			lpphy_disable_tx_gain_override(dev);
			lpphy->tx_pwr_idx_over = -1;
		पूर्ण
	पूर्ण
	अगर (dev->phy.rev >= 2) अणु
		अगर (mode == B43_LPPHY_TXPCTL_HW)
			b43_phy_set(dev, B43_PHY_OFDM(0xD0), 0x2);
		अन्यथा
			b43_phy_mask(dev, B43_PHY_OFDM(0xD0), 0xFFFD);
	पूर्ण
	lpphy_ग_लिखो_tx_pctl_mode_to_hardware(dev);
पूर्ण

अटल पूर्णांक b43_lpphy_op_चयन_channel(काष्ठा b43_wldev *dev,
				       अचिन्हित पूर्णांक new_channel);

अटल व्योम lpphy_rev0_1_rc_calib(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	काष्ठा lpphy_iq_est iq_est;
	काष्ठा lpphy_tx_gains tx_gains;
	अटल स्थिर u32 ideal_pwr_table[21] = अणु
		0x10000, 0x10557, 0x10e2d, 0x113e0, 0x10f22, 0x0ff64,
		0x0eda2, 0x0e5d4, 0x0efd1, 0x0fbe8, 0x0b7b8, 0x04b35,
		0x01a5e, 0x00a0b, 0x00444, 0x001fd, 0x000ff, 0x00088,
		0x0004c, 0x0002c, 0x0001a,
	पूर्ण;
	bool old_txg_ovr;
	u8 old_bbmult;
	u16 old_rf_ovr, old_rf_ovrval, old_afe_ovr, old_afe_ovrval,
	    old_rf2_ovr, old_rf2_ovrval, old_phy_ctl;
	क्रमागत b43_lpphy_txpctl_mode old_txpctl;
	u32 normal_pwr, ideal_pwr, mean_sq_pwr, पंचांगp = 0, mean_sq_pwr_min = 0;
	पूर्णांक loopback, i, j, inner_sum, err;

	स_रखो(&iq_est, 0, माप(iq_est));

	err = b43_lpphy_op_चयन_channel(dev, 7);
	अगर (err) अणु
		b43dbg(dev->wl,
		       "RC calib: Failed to switch to channel 7, error = %d\n",
		       err);
	पूर्ण
	old_txg_ovr = !!(b43_phy_पढ़ो(dev, B43_LPPHY_AFE_CTL_OVR) & 0x40);
	old_bbmult = lpphy_get_bb_mult(dev);
	अगर (old_txg_ovr)
		tx_gains = lpphy_get_tx_gains(dev);
	old_rf_ovr = b43_phy_पढ़ो(dev, B43_LPPHY_RF_OVERRIDE_0);
	old_rf_ovrval = b43_phy_पढ़ो(dev, B43_LPPHY_RF_OVERRIDE_VAL_0);
	old_afe_ovr = b43_phy_पढ़ो(dev, B43_LPPHY_AFE_CTL_OVR);
	old_afe_ovrval = b43_phy_पढ़ो(dev, B43_LPPHY_AFE_CTL_OVRVAL);
	old_rf2_ovr = b43_phy_पढ़ो(dev, B43_LPPHY_RF_OVERRIDE_2);
	old_rf2_ovrval = b43_phy_पढ़ो(dev, B43_LPPHY_RF_OVERRIDE_2_VAL);
	old_phy_ctl = b43_phy_पढ़ो(dev, B43_LPPHY_LP_PHY_CTL);
	lpphy_पढ़ो_tx_pctl_mode_from_hardware(dev);
	old_txpctl = lpphy->txpctl_mode;

	lpphy_set_tx_घातer_control(dev, B43_LPPHY_TXPCTL_OFF);
	lpphy_disable_crs(dev, true);
	loopback = lpphy_loopback(dev);
	अगर (loopback == -1)
		जाओ finish;
	lpphy_set_rx_gain_by_index(dev, loopback);
	b43_phy_maskset(dev, B43_LPPHY_LP_PHY_CTL, 0xFFBF, 0x40);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFFF8, 0x1);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFFC7, 0x8);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFF3F, 0xC0);
	क्रम (i = 128; i <= 159; i++) अणु
		b43_radio_ग_लिखो(dev, B2062_N_RXBB_CALIB2, i);
		inner_sum = 0;
		क्रम (j = 5; j <= 25; j++) अणु
			lpphy_run_ddfs(dev, 1, 1, j, j, 0);
			अगर (!(lpphy_rx_iq_est(dev, 1000, 32, &iq_est)))
				जाओ finish;
			mean_sq_pwr = iq_est.i_pwr + iq_est.q_pwr;
			अगर (j == 5)
				पंचांगp = mean_sq_pwr;
			ideal_pwr = ((ideal_pwr_table[j-5] >> 3) + 1) >> 1;
			normal_pwr = lpphy_qभाग_roundup(mean_sq_pwr, पंचांगp, 12);
			mean_sq_pwr = ideal_pwr - normal_pwr;
			mean_sq_pwr *= mean_sq_pwr;
			inner_sum += mean_sq_pwr;
			अगर ((i == 128) || (inner_sum < mean_sq_pwr_min)) अणु
				lpphy->rc_cap = i;
				mean_sq_pwr_min = inner_sum;
			पूर्ण
		पूर्ण
	पूर्ण
	lpphy_stop_ddfs(dev);

finish:
	lpphy_restore_crs(dev, true);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, old_rf_ovrval);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RF_OVERRIDE_0, old_rf_ovr);
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_CTL_OVRVAL, old_afe_ovrval);
	b43_phy_ग_लिखो(dev, B43_LPPHY_AFE_CTL_OVR, old_afe_ovr);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, old_rf2_ovrval);
	b43_phy_ग_लिखो(dev, B43_LPPHY_RF_OVERRIDE_2, old_rf2_ovr);
	b43_phy_ग_लिखो(dev, B43_LPPHY_LP_PHY_CTL, old_phy_ctl);

	lpphy_set_bb_mult(dev, old_bbmult);
	अगर (old_txg_ovr) अणु
		/*
		 * SPEC FIXME: The specs say "get_tx_gains" here, which is
		 * illogical. According to lwfinger, venकरोr driver v4.150.10.5
		 * has a Set here, जबतक v4.174.64.19 has a Get - regression in
		 * the venकरोr driver? This should be tested this once the code
		 * is testable.
		 */
		lpphy_set_tx_gains(dev, tx_gains);
	पूर्ण
	lpphy_set_tx_घातer_control(dev, old_txpctl);
	अगर (lpphy->rc_cap)
		lpphy_set_rc_cap(dev);
पूर्ण

अटल व्योम lpphy_rev2plus_rc_calib(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_bus *bus = dev->dev->sdev->bus;
	u32 crystal_freq = bus->chipco.pmu.crystalfreq * 1000;
	u8 पंचांगp = b43_radio_पढ़ो(dev, B2063_RX_BB_SP8) & 0xFF;
	पूर्णांक i;

	b43_radio_ग_लिखो(dev, B2063_RX_BB_SP8, 0x0);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL1, 0x7E);
	b43_radio_mask(dev, B2063_PLL_SP1, 0xF7);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL1, 0x7C);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL2, 0x15);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL3, 0x70);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL4, 0x52);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL5, 0x1);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL1, 0x7D);

	क्रम (i = 0; i < 10000; i++) अणु
		अगर (b43_radio_पढ़ो(dev, B2063_RC_CALIB_CTL6) & 0x2)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (!(b43_radio_पढ़ो(dev, B2063_RC_CALIB_CTL6) & 0x2))
		b43_radio_ग_लिखो(dev, B2063_RX_BB_SP8, पंचांगp);

	पंचांगp = b43_radio_पढ़ो(dev, B2063_TX_BB_SP3) & 0xFF;

	b43_radio_ग_लिखो(dev, B2063_TX_BB_SP3, 0x0);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL1, 0x7E);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL1, 0x7C);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL2, 0x55);
	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL3, 0x76);

	अगर (crystal_freq == 24000000) अणु
		b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL4, 0xFC);
		b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL5, 0x0);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL4, 0x13);
		b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL5, 0x1);
	पूर्ण

	b43_radio_ग_लिखो(dev, B2063_PA_SP7, 0x7D);

	क्रम (i = 0; i < 10000; i++) अणु
		अगर (b43_radio_पढ़ो(dev, B2063_RC_CALIB_CTL6) & 0x2)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (!(b43_radio_पढ़ो(dev, B2063_RC_CALIB_CTL6) & 0x2))
		b43_radio_ग_लिखो(dev, B2063_TX_BB_SP3, पंचांगp);

	b43_radio_ग_लिखो(dev, B2063_RC_CALIB_CTL1, 0x7E);
पूर्ण

अटल व्योम lpphy_calibrate_rc(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;

	अगर (dev->phy.rev >= 2) अणु
		lpphy_rev2plus_rc_calib(dev);
	पूर्ण अन्यथा अगर (!lpphy->rc_cap) अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
			lpphy_rev0_1_rc_calib(dev);
	पूर्ण अन्यथा अणु
		lpphy_set_rc_cap(dev);
	पूर्ण
पूर्ण

अटल व्योम b43_lpphy_op_set_rx_antenna(काष्ठा b43_wldev *dev, पूर्णांक antenna)
अणु
	अगर (dev->phy.rev >= 2)
		वापस; // rev2+ करोesn't support antenna भागersity

	अगर (B43_WARN_ON(antenna > B43_ANTENNA_AUTO1))
		वापस;

	b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) & ~B43_HF_ANTDIVHELP);

	b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL, 0xFFFD, antenna & 0x2);
	b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL, 0xFFFE, antenna & 0x1);

	b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) | B43_HF_ANTDIVHELP);

	dev->phy.lp->antenna = antenna;
पूर्ण

अटल व्योम lpphy_set_tx_iqcc(काष्ठा b43_wldev *dev, u16 a, u16 b)
अणु
	u16 पंचांगp[2];

	पंचांगp[0] = a;
	पंचांगp[1] = b;
	b43_lptab_ग_लिखो_bulk(dev, B43_LPTAB16(0, 80), 2, पंचांगp);
पूर्ण

अटल व्योम lpphy_set_tx_घातer_by_index(काष्ठा b43_wldev *dev, u8 index)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	काष्ठा lpphy_tx_gains gains;
	u32 iq_comp, tx_gain, coeff, rf_घातer;

	lpphy->tx_pwr_idx_over = index;
	lpphy_पढ़ो_tx_pctl_mode_from_hardware(dev);
	अगर (lpphy->txpctl_mode != B43_LPPHY_TXPCTL_OFF)
		lpphy_set_tx_घातer_control(dev, B43_LPPHY_TXPCTL_SW);
	अगर (dev->phy.rev >= 2) अणु
		iq_comp = b43_lptab_पढ़ो(dev, B43_LPTAB32(7, index + 320));
		tx_gain = b43_lptab_पढ़ो(dev, B43_LPTAB32(7, index + 192));
		gains.pad = (tx_gain >> 16) & 0xFF;
		gains.gm = tx_gain & 0xFF;
		gains.pga = (tx_gain >> 8) & 0xFF;
		gains.dac = (iq_comp >> 28) & 0xFF;
		lpphy_set_tx_gains(dev, gains);
	पूर्ण अन्यथा अणु
		iq_comp = b43_lptab_पढ़ो(dev, B43_LPTAB32(10, index + 320));
		tx_gain = b43_lptab_पढ़ो(dev, B43_LPTAB32(10, index + 192));
		b43_phy_maskset(dev, B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL,
				0xF800, (tx_gain >> 4) & 0x7FFF);
		lpphy_set_dac_gain(dev, tx_gain & 0x7);
		lpphy_set_pa_gain(dev, (tx_gain >> 24) & 0x7F);
	पूर्ण
	lpphy_set_bb_mult(dev, (iq_comp >> 20) & 0xFF);
	lpphy_set_tx_iqcc(dev, (iq_comp >> 10) & 0x3FF, iq_comp & 0x3FF);
	अगर (dev->phy.rev >= 2) अणु
		coeff = b43_lptab_पढ़ो(dev, B43_LPTAB32(7, index + 448));
	पूर्ण अन्यथा अणु
		coeff = b43_lptab_पढ़ो(dev, B43_LPTAB32(10, index + 448));
	पूर्ण
	b43_lptab_ग_लिखो(dev, B43_LPTAB16(0, 85), coeff & 0xFFFF);
	अगर (dev->phy.rev >= 2) अणु
		rf_घातer = b43_lptab_पढ़ो(dev, B43_LPTAB32(7, index + 576));
		b43_phy_maskset(dev, B43_LPPHY_RF_PWR_OVERRIDE, 0xFF00,
				rf_घातer & 0xFFFF);//SPEC FIXME mask & set != 0
	पूर्ण
	lpphy_enable_tx_gain_override(dev);
पूर्ण

अटल व्योम lpphy_btcoex_override(काष्ठा b43_wldev *dev)
अणु
	b43_ग_लिखो16(dev, B43_MMIO_BTCOEX_CTL, 0x3);
	b43_ग_लिखो16(dev, B43_MMIO_BTCOEX_TXCTL, 0xFF);
पूर्ण

अटल व्योम b43_lpphy_op_software_rfसमाप्त(काष्ठा b43_wldev *dev,
					 bool blocked)
अणु
	//TODO check MAC control रेजिस्टर
	अगर (blocked) अणु
		अगर (dev->phy.rev >= 2) अणु
			b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x83FF);
			b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x1F00);
			b43_phy_mask(dev, B43_LPPHY_AFE_DDFS, 0x80FF);
			b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xDFFF);
			b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x0808);
		पूर्ण अन्यथा अणु
			b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xE0FF);
			b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x1F00);
			b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFCFF);
			b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x0018);
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xE0FF);
		अगर (dev->phy.rev >= 2)
			b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xF7F7);
		अन्यथा
			b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xFFE7);
	पूर्ण
पूर्ण

/* This was previously called lpphy_japan_filter */
अटल व्योम lpphy_set_analog_filter(काष्ठा b43_wldev *dev, पूर्णांक channel)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	u16 पंचांगp = (channel == 14); //SPEC FIXME check japanwidefilter!

	अगर (dev->phy.rev < 2) अणु //SPEC FIXME Isn't this rev0/1-specअगरic?
		b43_phy_maskset(dev, B43_LPPHY_LP_PHY_CTL, 0xFCFF, पंचांगp << 9);
		अगर ((dev->phy.rev == 1) && (lpphy->rc_cap))
			lpphy_set_rc_cap(dev);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो(dev, B2063_TX_BB_SP3, 0x3F);
	पूर्ण
पूर्ण

अटल व्योम lpphy_set_tssi_mux(काष्ठा b43_wldev *dev, क्रमागत tssi_mux_mode mode)
अणु
	अगर (mode != TSSI_MUX_EXT) अणु
		b43_radio_set(dev, B2063_PA_SP1, 0x2);
		b43_phy_set(dev, B43_PHY_OFDM(0xF3), 0x1000);
		b43_radio_ग_लिखो(dev, B2063_PA_CTL10, 0x51);
		अगर (mode == TSSI_MUX_POSTPA) अणु
			b43_radio_mask(dev, B2063_PA_SP1, 0xFFFE);
			b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0xFFC7);
		पूर्ण अन्यथा अणु
			b43_radio_maskset(dev, B2063_PA_SP1, 0xFFFE, 0x1);
			b43_phy_maskset(dev, B43_LPPHY_AFE_CTL_OVRVAL,
					0xFFC7, 0x20);
		पूर्ण
	पूर्ण अन्यथा अणु
		B43_WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम lpphy_tx_pctl_init_hw(काष्ठा b43_wldev *dev)
अणु
	u16 पंचांगp;
	पूर्णांक i;

	//SPEC TODO Call LP PHY Clear TX Power offsets
	क्रम (i = 0; i < 64; i++) अणु
		अगर (dev->phy.rev >= 2)
			b43_lptab_ग_लिखो(dev, B43_LPTAB32(7, i + 1), i);
		अन्यथा
			b43_lptab_ग_लिखो(dev, B43_LPTAB32(10, i + 1), i);
	पूर्ण

	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_NNUM, 0xFF00, 0xFF);
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_NNUM, 0x8FFF, 0x5000);
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_IDLETSSI, 0xFFC0, 0x1F);
	अगर (dev->phy.rev < 2) अणु
		b43_phy_mask(dev, B43_LPPHY_LP_PHY_CTL, 0xEFFF);
		b43_phy_maskset(dev, B43_LPPHY_LP_PHY_CTL, 0xDFFF, 0x2000);
	पूर्ण अन्यथा अणु
		b43_phy_mask(dev, B43_PHY_OFDM(0x103), 0xFFFE);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x103), 0xFFFB, 0x4);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x103), 0xFFEF, 0x10);
		b43_radio_maskset(dev, B2063_IQ_CALIB_CTL2, 0xF3, 0x1);
		lpphy_set_tssi_mux(dev, TSSI_MUX_POSTPA);
	पूर्ण
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_IDLETSSI, 0x7FFF, 0x8000);
	b43_phy_mask(dev, B43_LPPHY_TX_PWR_CTL_DELTAPWR_LIMIT, 0xFF);
	b43_phy_ग_लिखो(dev, B43_LPPHY_TX_PWR_CTL_DELTAPWR_LIMIT, 0xA);
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_CMD,
			~B43_LPPHY_TX_PWR_CTL_CMD_MODE & 0xFFFF,
			B43_LPPHY_TX_PWR_CTL_CMD_MODE_OFF);
	b43_phy_mask(dev, B43_LPPHY_TX_PWR_CTL_NNUM, 0xF8FF);
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_CMD,
			~B43_LPPHY_TX_PWR_CTL_CMD_MODE & 0xFFFF,
			B43_LPPHY_TX_PWR_CTL_CMD_MODE_SW);

	अगर (dev->phy.rev < 2) अणु
		b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_0, 0xEFFF, 0x1000);
		b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xEFFF);
	पूर्ण अन्यथा अणु
		lpphy_set_tx_घातer_by_index(dev, 0x7F);
	पूर्ण

	b43_dummy_transmission(dev, true, true);

	पंचांगp = b43_phy_पढ़ो(dev, B43_LPPHY_TX_PWR_CTL_STAT);
	अगर (पंचांगp & 0x8000) अणु
		b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_IDLETSSI,
				0xFFC0, (पंचांगp & 0xFF) - 32);
	पूर्ण

	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xEFFF);

	// (SPEC?) TODO Set "Target TX frequency" variable to 0
	// SPEC FIXME "Set BB Multiplier to 0xE000" impossible - bb_mult is u8!
पूर्ण

अटल व्योम lpphy_tx_pctl_init_sw(काष्ठा b43_wldev *dev)
अणु
	काष्ठा lpphy_tx_gains gains;

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		gains.gm = 4;
		gains.pad = 12;
		gains.pga = 12;
		gains.dac = 0;
	पूर्ण अन्यथा अणु
		gains.gm = 7;
		gains.pad = 14;
		gains.pga = 15;
		gains.dac = 0;
	पूर्ण
	lpphy_set_tx_gains(dev, gains);
	lpphy_set_bb_mult(dev, 150);
पूर्ण

/* Initialize TX घातer control */
अटल व्योम lpphy_tx_pctl_init(काष्ठा b43_wldev *dev)
अणु
	अगर (0/*FIXME HWPCTL capable */) अणु
		lpphy_tx_pctl_init_hw(dev);
	पूर्ण अन्यथा अणु /* This device is only software TX घातer control capable. */
		lpphy_tx_pctl_init_sw(dev);
	पूर्ण
पूर्ण

अटल व्योम lpphy_pr41573_workaround(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	u32 *saved_tab;
	स्थिर अचिन्हित पूर्णांक saved_tab_size = 256;
	क्रमागत b43_lpphy_txpctl_mode txpctl_mode;
	s8 tx_pwr_idx_over;
	u16 tssi_npt, tssi_idx;

	saved_tab = kसुस्मृति(saved_tab_size, माप(saved_tab[0]), GFP_KERNEL);
	अगर (!saved_tab) अणु
		b43err(dev->wl, "PR41573 failed. Out of memory!\n");
		वापस;
	पूर्ण

	lpphy_पढ़ो_tx_pctl_mode_from_hardware(dev);
	txpctl_mode = lpphy->txpctl_mode;
	tx_pwr_idx_over = lpphy->tx_pwr_idx_over;
	tssi_npt = lpphy->tssi_npt;
	tssi_idx = lpphy->tssi_idx;

	अगर (dev->phy.rev < 2) अणु
		b43_lptab_पढ़ो_bulk(dev, B43_LPTAB32(10, 0x140),
				    saved_tab_size, saved_tab);
	पूर्ण अन्यथा अणु
		b43_lptab_पढ़ो_bulk(dev, B43_LPTAB32(7, 0x140),
				    saved_tab_size, saved_tab);
	पूर्ण
	//FIXME PHY reset
	lpphy_table_init(dev); //FIXME is table init needed?
	lpphy_baseband_init(dev);
	lpphy_tx_pctl_init(dev);
	b43_lpphy_op_software_rfसमाप्त(dev, false);
	lpphy_set_tx_घातer_control(dev, B43_LPPHY_TXPCTL_OFF);
	अगर (dev->phy.rev < 2) अणु
		b43_lptab_ग_लिखो_bulk(dev, B43_LPTAB32(10, 0x140),
				     saved_tab_size, saved_tab);
	पूर्ण अन्यथा अणु
		b43_lptab_ग_लिखो_bulk(dev, B43_LPTAB32(7, 0x140),
				     saved_tab_size, saved_tab);
	पूर्ण
	b43_ग_लिखो16(dev, B43_MMIO_CHANNEL, lpphy->channel);
	lpphy->tssi_npt = tssi_npt;
	lpphy->tssi_idx = tssi_idx;
	lpphy_set_analog_filter(dev, lpphy->channel);
	अगर (tx_pwr_idx_over != -1)
		lpphy_set_tx_घातer_by_index(dev, tx_pwr_idx_over);
	अगर (lpphy->rc_cap)
		lpphy_set_rc_cap(dev);
	b43_lpphy_op_set_rx_antenna(dev, lpphy->antenna);
	lpphy_set_tx_घातer_control(dev, txpctl_mode);
	kमुक्त(saved_tab);
पूर्ण

काष्ठा lpphy_rx_iq_comp अणु u8 chan; s8 c1, c0; पूर्ण;

अटल स्थिर काष्ठा lpphy_rx_iq_comp lpphy_5354_iq_table[] = अणु
	अणु .chan = 1, .c1 = -66, .c0 = 15, पूर्ण,
	अणु .chan = 2, .c1 = -66, .c0 = 15, पूर्ण,
	अणु .chan = 3, .c1 = -66, .c0 = 15, पूर्ण,
	अणु .chan = 4, .c1 = -66, .c0 = 15, पूर्ण,
	अणु .chan = 5, .c1 = -66, .c0 = 15, पूर्ण,
	अणु .chan = 6, .c1 = -66, .c0 = 15, पूर्ण,
	अणु .chan = 7, .c1 = -66, .c0 = 14, पूर्ण,
	अणु .chan = 8, .c1 = -66, .c0 = 14, पूर्ण,
	अणु .chan = 9, .c1 = -66, .c0 = 14, पूर्ण,
	अणु .chan = 10, .c1 = -66, .c0 = 14, पूर्ण,
	अणु .chan = 11, .c1 = -66, .c0 = 14, पूर्ण,
	अणु .chan = 12, .c1 = -66, .c0 = 13, पूर्ण,
	अणु .chan = 13, .c1 = -66, .c0 = 13, पूर्ण,
	अणु .chan = 14, .c1 = -66, .c0 = 13, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lpphy_rx_iq_comp lpphy_rev0_1_iq_table[] = अणु
	अणु .chan = 1, .c1 = -64, .c0 = 13, पूर्ण,
	अणु .chan = 2, .c1 = -64, .c0 = 13, पूर्ण,
	अणु .chan = 3, .c1 = -64, .c0 = 13, पूर्ण,
	अणु .chan = 4, .c1 = -64, .c0 = 13, पूर्ण,
	अणु .chan = 5, .c1 = -64, .c0 = 12, पूर्ण,
	अणु .chan = 6, .c1 = -64, .c0 = 12, पूर्ण,
	अणु .chan = 7, .c1 = -64, .c0 = 12, पूर्ण,
	अणु .chan = 8, .c1 = -64, .c0 = 12, पूर्ण,
	अणु .chan = 9, .c1 = -64, .c0 = 12, पूर्ण,
	अणु .chan = 10, .c1 = -64, .c0 = 11, पूर्ण,
	अणु .chan = 11, .c1 = -64, .c0 = 11, पूर्ण,
	अणु .chan = 12, .c1 = -64, .c0 = 11, पूर्ण,
	अणु .chan = 13, .c1 = -64, .c0 = 11, पूर्ण,
	अणु .chan = 14, .c1 = -64, .c0 = 10, पूर्ण,
	अणु .chan = 34, .c1 = -62, .c0 = 24, पूर्ण,
	अणु .chan = 38, .c1 = -62, .c0 = 24, पूर्ण,
	अणु .chan = 42, .c1 = -62, .c0 = 24, पूर्ण,
	अणु .chan = 46, .c1 = -62, .c0 = 23, पूर्ण,
	अणु .chan = 36, .c1 = -62, .c0 = 24, पूर्ण,
	अणु .chan = 40, .c1 = -62, .c0 = 24, पूर्ण,
	अणु .chan = 44, .c1 = -62, .c0 = 23, पूर्ण,
	अणु .chan = 48, .c1 = -62, .c0 = 23, पूर्ण,
	अणु .chan = 52, .c1 = -62, .c0 = 23, पूर्ण,
	अणु .chan = 56, .c1 = -62, .c0 = 22, पूर्ण,
	अणु .chan = 60, .c1 = -62, .c0 = 22, पूर्ण,
	अणु .chan = 64, .c1 = -62, .c0 = 22, पूर्ण,
	अणु .chan = 100, .c1 = -62, .c0 = 16, पूर्ण,
	अणु .chan = 104, .c1 = -62, .c0 = 16, पूर्ण,
	अणु .chan = 108, .c1 = -62, .c0 = 15, पूर्ण,
	अणु .chan = 112, .c1 = -62, .c0 = 14, पूर्ण,
	अणु .chan = 116, .c1 = -62, .c0 = 14, पूर्ण,
	अणु .chan = 120, .c1 = -62, .c0 = 13, पूर्ण,
	अणु .chan = 124, .c1 = -62, .c0 = 12, पूर्ण,
	अणु .chan = 128, .c1 = -62, .c0 = 12, पूर्ण,
	अणु .chan = 132, .c1 = -62, .c0 = 12, पूर्ण,
	अणु .chan = 136, .c1 = -62, .c0 = 11, पूर्ण,
	अणु .chan = 140, .c1 = -62, .c0 = 10, पूर्ण,
	अणु .chan = 149, .c1 = -61, .c0 = 9, पूर्ण,
	अणु .chan = 153, .c1 = -61, .c0 = 9, पूर्ण,
	अणु .chan = 157, .c1 = -61, .c0 = 9, पूर्ण,
	अणु .chan = 161, .c1 = -61, .c0 = 8, पूर्ण,
	अणु .chan = 165, .c1 = -61, .c0 = 8, पूर्ण,
	अणु .chan = 184, .c1 = -62, .c0 = 25, पूर्ण,
	अणु .chan = 188, .c1 = -62, .c0 = 25, पूर्ण,
	अणु .chan = 192, .c1 = -62, .c0 = 25, पूर्ण,
	अणु .chan = 196, .c1 = -62, .c0 = 25, पूर्ण,
	अणु .chan = 200, .c1 = -62, .c0 = 25, पूर्ण,
	अणु .chan = 204, .c1 = -62, .c0 = 25, पूर्ण,
	अणु .chan = 208, .c1 = -62, .c0 = 25, पूर्ण,
	अणु .chan = 212, .c1 = -62, .c0 = 25, पूर्ण,
	अणु .chan = 216, .c1 = -62, .c0 = 26, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lpphy_rx_iq_comp lpphy_rev2plus_iq_comp = अणु
	.chan = 0,
	.c1 = -64,
	.c0 = 0,
पूर्ण;

अटल पूर्णांक lpphy_calc_rx_iq_comp(काष्ठा b43_wldev *dev, u16 samples)
अणु
	काष्ठा lpphy_iq_est iq_est;
	u16 c0, c1;
	पूर्णांक prod, ipwr, qpwr, prod_msb, q_msb, पंचांगp1, पंचांगp2, पंचांगp3, पंचांगp4, ret;

	c1 = b43_phy_पढ़ो(dev, B43_LPPHY_RX_COMP_COEFF_S);
	c0 = c1 >> 8;
	c1 |= 0xFF;

	b43_phy_maskset(dev, B43_LPPHY_RX_COMP_COEFF_S, 0xFF00, 0x00C0);
	b43_phy_mask(dev, B43_LPPHY_RX_COMP_COEFF_S, 0x00FF);

	ret = lpphy_rx_iq_est(dev, samples, 32, &iq_est);
	अगर (!ret)
		जाओ out;

	prod = iq_est.iq_prod;
	ipwr = iq_est.i_pwr;
	qpwr = iq_est.q_pwr;

	अगर (ipwr + qpwr < 2) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	prod_msb = fls(असल(prod));
	q_msb = fls(असल(qpwr));
	पंचांगp1 = prod_msb - 20;

	अगर (पंचांगp1 >= 0) अणु
		पंचांगp3 = ((prod << (30 - prod_msb)) + (ipwr >> (1 + पंचांगp1))) /
			(ipwr >> पंचांगp1);
	पूर्ण अन्यथा अणु
		पंचांगp3 = ((prod << (30 - prod_msb)) + (ipwr << (-1 - पंचांगp1))) /
			(ipwr << -पंचांगp1);
	पूर्ण

	पंचांगp2 = q_msb - 11;

	अगर (पंचांगp2 >= 0)
		पंचांगp4 = (qpwr << (31 - q_msb)) / (ipwr >> पंचांगp2);
	अन्यथा
		पंचांगp4 = (qpwr << (31 - q_msb)) / (ipwr << -पंचांगp2);

	पंचांगp4 -= पंचांगp3 * पंचांगp3;
	पंचांगp4 = -पूर्णांक_वर्ग_मूल(पंचांगp4);

	c0 = पंचांगp3 >> 3;
	c1 = पंचांगp4 >> 4;

out:
	b43_phy_maskset(dev, B43_LPPHY_RX_COMP_COEFF_S, 0xFF00, c1);
	b43_phy_maskset(dev, B43_LPPHY_RX_COMP_COEFF_S, 0x00FF, c0 << 8);
	वापस ret;
पूर्ण

अटल व्योम lpphy_run_samples(काष्ठा b43_wldev *dev, u16 samples, u16 loops,
			      u16 रुको)
अणु
	b43_phy_maskset(dev, B43_LPPHY_SMPL_PLAY_BUFFER_CTL,
			0xFFC0, samples - 1);
	अगर (loops != 0xFFFF)
		loops--;
	b43_phy_maskset(dev, B43_LPPHY_SMPL_PLAY_COUNT, 0xF000, loops);
	b43_phy_maskset(dev, B43_LPPHY_SMPL_PLAY_BUFFER_CTL, 0x3F, रुको << 6);
	b43_phy_set(dev, B43_LPPHY_A_PHY_CTL_ADDR, 0x1);
पूर्ण

//SPEC FIXME what करोes a negative freq mean?
अटल व्योम lpphy_start_tx_tone(काष्ठा b43_wldev *dev, s32 freq, u16 max)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	u16 buf[64];
	पूर्णांक i, samples = 0, theta = 0;
	पूर्णांक rotation = (((36 * freq) / 20) << 16) / 100;
	काष्ठा cordic_iq sample;

	lpphy->tx_tone_freq = freq;

	अगर (freq) अणु
		/* Find i क्रम which असल(freq) पूर्णांकegrally भागides 20000 * i */
		क्रम (i = 1; samples * असल(freq) != 20000 * i; i++) अणु
			samples = (20000 * i) / असल(freq);
			अगर(B43_WARN_ON(samples > 63))
				वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		samples = 2;
	पूर्ण

	क्रम (i = 0; i < samples; i++) अणु
		sample = cordic_calc_iq(CORDIC_FIXED(theta));
		theta += rotation;
		buf[i] = CORDIC_FLOAT((sample.i * max) & 0xFF) << 8;
		buf[i] |= CORDIC_FLOAT((sample.q * max) & 0xFF);
	पूर्ण

	b43_lptab_ग_लिखो_bulk(dev, B43_LPTAB16(5, 0), samples, buf);

	lpphy_run_samples(dev, samples, 0xFFFF, 0);
पूर्ण

अटल व्योम lpphy_stop_tx_tone(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	पूर्णांक i;

	lpphy->tx_tone_freq = 0;

	b43_phy_mask(dev, B43_LPPHY_SMPL_PLAY_COUNT, 0xF000);
	क्रम (i = 0; i < 31; i++) अणु
		अगर (!(b43_phy_पढ़ो(dev, B43_LPPHY_A_PHY_CTL_ADDR) & 0x1))
			अवरोध;
		udelay(100);
	पूर्ण
पूर्ण


अटल व्योम lpphy_papd_cal_txpwr(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	काष्ठा lpphy_tx_gains oldgains;
	पूर्णांक old_txpctl, old_afe_ovr, old_rf, old_bbmult;

	lpphy_पढ़ो_tx_pctl_mode_from_hardware(dev);
	old_txpctl = lpphy->txpctl_mode;
	old_afe_ovr = b43_phy_पढ़ो(dev, B43_LPPHY_AFE_CTL_OVR) & 0x40;
	अगर (old_afe_ovr)
		oldgains = lpphy_get_tx_gains(dev);
	old_rf = b43_phy_पढ़ो(dev, B43_LPPHY_RF_PWR_OVERRIDE) & 0xFF;
	old_bbmult = lpphy_get_bb_mult(dev);

	lpphy_set_tx_घातer_control(dev, B43_LPPHY_TXPCTL_OFF);

	अगर (old_afe_ovr)
		lpphy_set_tx_gains(dev, oldgains);
	lpphy_set_bb_mult(dev, old_bbmult);
	lpphy_set_tx_घातer_control(dev, old_txpctl);
	b43_phy_maskset(dev, B43_LPPHY_RF_PWR_OVERRIDE, 0xFF00, old_rf);
पूर्ण

अटल पूर्णांक lpphy_rx_iq_cal(काष्ठा b43_wldev *dev, bool noise, bool tx,
			    bool rx, bool pa, काष्ठा lpphy_tx_gains *gains)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	स्थिर काष्ठा lpphy_rx_iq_comp *iqcomp = शून्य;
	काष्ठा lpphy_tx_gains nogains, oldgains;
	u16 पंचांगp;
	पूर्णांक i, ret;

	स_रखो(&nogains, 0, माप(nogains));
	स_रखो(&oldgains, 0, माप(oldgains));

	अगर (dev->dev->chip_id == 0x5354) अणु
		क्रम (i = 0; i < ARRAY_SIZE(lpphy_5354_iq_table); i++) अणु
			अगर (lpphy_5354_iq_table[i].chan == lpphy->channel) अणु
				iqcomp = &lpphy_5354_iq_table[i];
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (dev->phy.rev >= 2) अणु
		iqcomp = &lpphy_rev2plus_iq_comp;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(lpphy_rev0_1_iq_table); i++) अणु
			अगर (lpphy_rev0_1_iq_table[i].chan == lpphy->channel) अणु
				iqcomp = &lpphy_rev0_1_iq_table[i];
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (B43_WARN_ON(!iqcomp))
		वापस 0;

	b43_phy_maskset(dev, B43_LPPHY_RX_COMP_COEFF_S, 0xFF00, iqcomp->c1);
	b43_phy_maskset(dev, B43_LPPHY_RX_COMP_COEFF_S,
			0x00FF, iqcomp->c0 << 8);

	अगर (noise) अणु
		tx = true;
		rx = false;
		pa = false;
	पूर्ण

	lpphy_set_trsw_over(dev, tx, rx);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x8);
		b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_VAL_0,
				0xFFF7, pa << 3);
	पूर्ण अन्यथा अणु
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x20);
		b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_VAL_0,
				0xFFDF, pa << 5);
	पूर्ण

	पंचांगp = b43_phy_पढ़ो(dev, B43_LPPHY_AFE_CTL_OVR) & 0x40;

	अगर (noise)
		lpphy_set_rx_gain(dev, 0x2D5D);
	अन्यथा अणु
		अगर (पंचांगp)
			oldgains = lpphy_get_tx_gains(dev);
		अगर (!gains)
			gains = &nogains;
		lpphy_set_tx_gains(dev, *gains);
	पूर्ण

	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVR, 0xFFFE);
	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0xFFFE);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x800);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x800);
	lpphy_set_deaf(dev, false);
	अगर (noise)
		ret = lpphy_calc_rx_iq_comp(dev, 0xFFF0);
	अन्यथा अणु
		lpphy_start_tx_tone(dev, 4000, 100);
		ret = lpphy_calc_rx_iq_comp(dev, 0x4000);
		lpphy_stop_tx_tone(dev);
	पूर्ण
	lpphy_clear_deaf(dev, false);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFFFC);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFFF7);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFFDF);
	अगर (!noise) अणु
		अगर (पंचांगp)
			lpphy_set_tx_gains(dev, oldgains);
		अन्यथा
			lpphy_disable_tx_gain_override(dev);
	पूर्ण
	lpphy_disable_rx_gain_override(dev);
	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVR, 0xFFFE);
	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0xF7FF);
	वापस ret;
पूर्ण

अटल व्योम lpphy_calibration(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	क्रमागत b43_lpphy_txpctl_mode saved_pctl_mode;
	bool full_cal = false;

	अगर (lpphy->full_calib_chan != lpphy->channel) अणु
		full_cal = true;
		lpphy->full_calib_chan = lpphy->channel;
	पूर्ण

	b43_mac_suspend(dev);

	lpphy_btcoex_override(dev);
	अगर (dev->phy.rev >= 2)
		lpphy_save_dig_flt_state(dev);
	lpphy_पढ़ो_tx_pctl_mode_from_hardware(dev);
	saved_pctl_mode = lpphy->txpctl_mode;
	lpphy_set_tx_घातer_control(dev, B43_LPPHY_TXPCTL_OFF);
	//TODO Perक्रमm transmit घातer table I/Q LO calibration
	अगर ((dev->phy.rev == 0) && (saved_pctl_mode != B43_LPPHY_TXPCTL_OFF))
		lpphy_pr41573_workaround(dev);
	अगर ((dev->phy.rev >= 2) && full_cal) अणु
		lpphy_papd_cal_txpwr(dev);
	पूर्ण
	lpphy_set_tx_घातer_control(dev, saved_pctl_mode);
	अगर (dev->phy.rev >= 2)
		lpphy_restore_dig_flt_state(dev);
	lpphy_rx_iq_cal(dev, true, true, false, false, शून्य);

	b43_mac_enable(dev);
पूर्ण

अटल व्योम b43_lpphy_op_maskset(काष्ठा b43_wldev *dev, u16 reg, u16 mask,
				 u16 set)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_PHY_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_PHY_DATA,
		    (b43_पढ़ो16(dev, B43_MMIO_PHY_DATA) & mask) | set);
पूर्ण

अटल u16 b43_lpphy_op_radio_पढ़ो(काष्ठा b43_wldev *dev, u16 reg)
अणु
	/* Register 1 is a 32-bit रेजिस्टर. */
	B43_WARN_ON(reg == 1);
	/* LP-PHY needs a special bit set क्रम पढ़ो access */
	अगर (dev->phy.rev < 2) अणु
		अगर (reg != 0x4001)
			reg |= 0x100;
	पूर्ण अन्यथा
		reg |= 0x200;

	b43_ग_लिखो16f(dev, B43_MMIO_RADIO_CONTROL, reg);
	वापस b43_पढ़ो16(dev, B43_MMIO_RADIO_DATA_LOW);
पूर्ण

अटल व्योम b43_lpphy_op_radio_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg, u16 value)
अणु
	/* Register 1 is a 32-bit रेजिस्टर. */
	B43_WARN_ON(reg == 1);

	b43_ग_लिखो16f(dev, B43_MMIO_RADIO_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_RADIO_DATA_LOW, value);
पूर्ण

काष्ठा b206x_channel अणु
	u8 channel;
	u16 freq;
	u8 data[12];
पूर्ण;

अटल स्थिर काष्ठा b206x_channel b2062_chantbl[] = अणु
	अणु .channel = 1, .freq = 2412, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 2, .freq = 2417, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 3, .freq = 2422, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 4, .freq = 2427, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 5, .freq = 2432, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 6, .freq = 2437, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 7, .freq = 2442, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 8, .freq = 2447, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 9, .freq = 2452, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 10, .freq = 2457, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 11, .freq = 2462, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 12, .freq = 2467, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 13, .freq = 2472, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 14, .freq = 2484, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, पूर्ण,
	अणु .channel = 34, .freq = 5170, .data[0] = 0x00, .data[1] = 0x22,
	  .data[2] = 0x20, .data[3] = 0x84, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 38, .freq = 5190, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x10, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 42, .freq = 5210, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x10, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 46, .freq = 5230, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 36, .freq = 5180, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x20, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 40, .freq = 5200, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x10, .data[3] = 0x84, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 44, .freq = 5220, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 48, .freq = 5240, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 52, .freq = 5260, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 56, .freq = 5280, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 60, .freq = 5300, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x63, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 64, .freq = 5320, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x62, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 100, .freq = 5500, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x30, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 104, .freq = 5520, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x20, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 108, .freq = 5540, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x20, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 112, .freq = 5560, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x20, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 116, .freq = 5580, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x10, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 120, .freq = 5600, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 124, .freq = 5620, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 128, .freq = 5640, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 132, .freq = 5660, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 136, .freq = 5680, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 140, .freq = 5700, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 149, .freq = 5745, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 153, .freq = 5765, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 157, .freq = 5785, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 161, .freq = 5805, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 165, .freq = 5825, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 184, .freq = 4920, .data[0] = 0x55, .data[1] = 0x77,
	  .data[2] = 0x90, .data[3] = 0xF7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, पूर्ण,
	अणु .channel = 188, .freq = 4940, .data[0] = 0x44, .data[1] = 0x77,
	  .data[2] = 0x80, .data[3] = 0xE7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, पूर्ण,
	अणु .channel = 192, .freq = 4960, .data[0] = 0x44, .data[1] = 0x66,
	  .data[2] = 0x80, .data[3] = 0xE7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, पूर्ण,
	अणु .channel = 196, .freq = 4980, .data[0] = 0x33, .data[1] = 0x66,
	  .data[2] = 0x70, .data[3] = 0xC7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, पूर्ण,
	अणु .channel = 200, .freq = 5000, .data[0] = 0x22, .data[1] = 0x55,
	  .data[2] = 0x60, .data[3] = 0xD7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, पूर्ण,
	अणु .channel = 204, .freq = 5020, .data[0] = 0x22, .data[1] = 0x55,
	  .data[2] = 0x60, .data[3] = 0xC7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, पूर्ण,
	अणु .channel = 208, .freq = 5040, .data[0] = 0x22, .data[1] = 0x44,
	  .data[2] = 0x50, .data[3] = 0xC7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, पूर्ण,
	अणु .channel = 212, .freq = 5060, .data[0] = 0x11, .data[1] = 0x44,
	  .data[2] = 0x50, .data[3] = 0xA5, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
	अणु .channel = 216, .freq = 5080, .data[0] = 0x00, .data[1] = 0x44,
	  .data[2] = 0x40, .data[3] = 0xB6, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा b206x_channel b2063_chantbl[] = अणु
	अणु .channel = 1, .freq = 2412, .data[0] = 0x6F, .data[1] = 0x3C,
	  .data[2] = 0x3C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 2, .freq = 2417, .data[0] = 0x6F, .data[1] = 0x3C,
	  .data[2] = 0x3C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 3, .freq = 2422, .data[0] = 0x6F, .data[1] = 0x3C,
	  .data[2] = 0x3C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 4, .freq = 2427, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 5, .freq = 2432, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 6, .freq = 2437, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 7, .freq = 2442, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 8, .freq = 2447, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 9, .freq = 2452, .data[0] = 0x6F, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 10, .freq = 2457, .data[0] = 0x6F, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 11, .freq = 2462, .data[0] = 0x6E, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 12, .freq = 2467, .data[0] = 0x6E, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 13, .freq = 2472, .data[0] = 0x6E, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 14, .freq = 2484, .data[0] = 0x6E, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, पूर्ण,
	अणु .channel = 34, .freq = 5170, .data[0] = 0x6A, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x02, .data[5] = 0x05,
	  .data[6] = 0x0D, .data[7] = 0x0D, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x20, .data[11] = 0x00, पूर्ण,
	अणु .channel = 36, .freq = 5180, .data[0] = 0x6A, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x01, .data[5] = 0x05,
	  .data[6] = 0x0D, .data[7] = 0x0C, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x20, .data[11] = 0x00, पूर्ण,
	अणु .channel = 38, .freq = 5190, .data[0] = 0x6A, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x01, .data[5] = 0x04,
	  .data[6] = 0x0C, .data[7] = 0x0C, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x20, .data[11] = 0x00, पूर्ण,
	अणु .channel = 40, .freq = 5200, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x01, .data[5] = 0x04,
	  .data[6] = 0x0C, .data[7] = 0x0C, .data[8] = 0x77, .data[9] = 0x70,
	  .data[10] = 0x20, .data[11] = 0x00, पूर्ण,
	अणु .channel = 42, .freq = 5210, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x01, .data[5] = 0x04,
	  .data[6] = 0x0B, .data[7] = 0x0C, .data[8] = 0x77, .data[9] = 0x70,
	  .data[10] = 0x20, .data[11] = 0x00, पूर्ण,
	अणु .channel = 44, .freq = 5220, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x04,
	  .data[6] = 0x0B, .data[7] = 0x0B, .data[8] = 0x77, .data[9] = 0x60,
	  .data[10] = 0x20, .data[11] = 0x00, पूर्ण,
	अणु .channel = 46, .freq = 5230, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x03,
	  .data[6] = 0x0A, .data[7] = 0x0B, .data[8] = 0x77, .data[9] = 0x60,
	  .data[10] = 0x20, .data[11] = 0x00, पूर्ण,
	अणु .channel = 48, .freq = 5240, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x03,
	  .data[6] = 0x0A, .data[7] = 0x0A, .data[8] = 0x77, .data[9] = 0x60,
	  .data[10] = 0x20, .data[11] = 0x00, पूर्ण,
	अणु .channel = 52, .freq = 5260, .data[0] = 0x68, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x02,
	  .data[6] = 0x09, .data[7] = 0x09, .data[8] = 0x77, .data[9] = 0x60,
	  .data[10] = 0x20, .data[11] = 0x00, पूर्ण,
	अणु .channel = 56, .freq = 5280, .data[0] = 0x68, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x01,
	  .data[6] = 0x08, .data[7] = 0x08, .data[8] = 0x77, .data[9] = 0x50,
	  .data[10] = 0x10, .data[11] = 0x00, पूर्ण,
	अणु .channel = 60, .freq = 5300, .data[0] = 0x68, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x01,
	  .data[6] = 0x08, .data[7] = 0x08, .data[8] = 0x77, .data[9] = 0x50,
	  .data[10] = 0x10, .data[11] = 0x00, पूर्ण,
	अणु .channel = 64, .freq = 5320, .data[0] = 0x67, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x08, .data[7] = 0x08, .data[8] = 0x77, .data[9] = 0x50,
	  .data[10] = 0x10, .data[11] = 0x00, पूर्ण,
	अणु .channel = 100, .freq = 5500, .data[0] = 0x64, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x02, .data[7] = 0x01, .data[8] = 0x77, .data[9] = 0x20,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 104, .freq = 5520, .data[0] = 0x64, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x01, .data[7] = 0x01, .data[8] = 0x77, .data[9] = 0x20,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 108, .freq = 5540, .data[0] = 0x63, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x01, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x10,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 112, .freq = 5560, .data[0] = 0x63, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x10,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 116, .freq = 5580, .data[0] = 0x62, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x10,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 120, .freq = 5600, .data[0] = 0x62, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 124, .freq = 5620, .data[0] = 0x62, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 128, .freq = 5640, .data[0] = 0x61, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 132, .freq = 5660, .data[0] = 0x61, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 136, .freq = 5680, .data[0] = 0x61, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 140, .freq = 5700, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 149, .freq = 5745, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 153, .freq = 5765, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 157, .freq = 5785, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 161, .freq = 5805, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 165, .freq = 5825, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, पूर्ण,
	अणु .channel = 184, .freq = 4920, .data[0] = 0x6E, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x09, .data[5] = 0x0E,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xC0,
	  .data[10] = 0x50, .data[11] = 0x00, पूर्ण,
	अणु .channel = 188, .freq = 4940, .data[0] = 0x6E, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x09, .data[5] = 0x0D,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xB0,
	  .data[10] = 0x50, .data[11] = 0x00, पूर्ण,
	अणु .channel = 192, .freq = 4960, .data[0] = 0x6E, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x08, .data[5] = 0x0C,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xB0,
	  .data[10] = 0x50, .data[11] = 0x00, पूर्ण,
	अणु .channel = 196, .freq = 4980, .data[0] = 0x6D, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x08, .data[5] = 0x0C,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xA0,
	  .data[10] = 0x40, .data[11] = 0x00, पूर्ण,
	अणु .channel = 200, .freq = 5000, .data[0] = 0x6D, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x08, .data[5] = 0x0B,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xA0,
	  .data[10] = 0x40, .data[11] = 0x00, पूर्ण,
	अणु .channel = 204, .freq = 5020, .data[0] = 0x6D, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x08, .data[5] = 0x0A,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xA0,
	  .data[10] = 0x40, .data[11] = 0x00, पूर्ण,
	अणु .channel = 208, .freq = 5040, .data[0] = 0x6C, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x07, .data[5] = 0x09,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0x90,
	  .data[10] = 0x40, .data[11] = 0x00, पूर्ण,
	अणु .channel = 212, .freq = 5060, .data[0] = 0x6C, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x06, .data[5] = 0x08,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0x90,
	  .data[10] = 0x40, .data[11] = 0x00, पूर्ण,
	अणु .channel = 216, .freq = 5080, .data[0] = 0x6C, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x05, .data[5] = 0x08,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0x90,
	  .data[10] = 0x40, .data[11] = 0x00, पूर्ण,
पूर्ण;

अटल व्योम lpphy_b2062_reset_pll_bias(काष्ठा b43_wldev *dev)
अणु
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL2, 0xFF);
	udelay(20);
	अगर (dev->dev->chip_id == 0x5354) अणु
		b43_radio_ग_लिखो(dev, B2062_N_COMM1, 4);
		b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL2, 4);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL2, 0);
	पूर्ण
	udelay(5);
पूर्ण

अटल व्योम lpphy_b2062_vco_calib(काष्ठा b43_wldev *dev)
अणु
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL21, 0x42);
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL21, 0x62);
	udelay(200);
पूर्ण

अटल पूर्णांक lpphy_b2062_tune(काष्ठा b43_wldev *dev,
			    अचिन्हित पूर्णांक channel)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	काष्ठा ssb_bus *bus = dev->dev->sdev->bus;
	स्थिर काष्ठा b206x_channel *chandata = शून्य;
	u32 crystal_freq = bus->chipco.pmu.crystalfreq * 1000;
	u32 पंचांगp1, पंचांगp2, पंचांगp3, पंचांगp4, पंचांगp5, पंचांगp6, पंचांगp7, पंचांगp8, पंचांगp9;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < ARRAY_SIZE(b2062_chantbl); i++) अणु
		अगर (b2062_chantbl[i].channel == channel) अणु
			chandata = &b2062_chantbl[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (B43_WARN_ON(!chandata))
		वापस -EINVAL;

	b43_radio_set(dev, B2062_S_RFPLL_CTL14, 0x04);
	b43_radio_ग_लिखो(dev, B2062_N_LGENA_TUNE0, chandata->data[0]);
	b43_radio_ग_लिखो(dev, B2062_N_LGENA_TUNE2, chandata->data[1]);
	b43_radio_ग_लिखो(dev, B2062_N_LGENA_TUNE3, chandata->data[2]);
	b43_radio_ग_लिखो(dev, B2062_N_TX_TUNE, chandata->data[3]);
	b43_radio_ग_लिखो(dev, B2062_S_LGENG_CTL1, chandata->data[4]);
	b43_radio_ग_लिखो(dev, B2062_N_LGENA_CTL5, chandata->data[5]);
	b43_radio_ग_लिखो(dev, B2062_N_LGENA_CTL6, chandata->data[6]);
	b43_radio_ग_लिखो(dev, B2062_N_TX_PGA, chandata->data[7]);
	b43_radio_ग_लिखो(dev, B2062_N_TX_PAD, chandata->data[8]);

	पंचांगp1 = crystal_freq / 1000;
	पंचांगp2 = lpphy->pभाग * 1000;
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL33, 0xCC);
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL34, 0x07);
	lpphy_b2062_reset_pll_bias(dev);
	पंचांगp3 = पंचांगp2 * channel2freq_lp(channel);
	अगर (channel2freq_lp(channel) < 4000)
		पंचांगp3 *= 2;
	पंचांगp4 = 48 * पंचांगp1;
	पंचांगp6 = पंचांगp3 / पंचांगp4;
	पंचांगp7 = पंचांगp3 % पंचांगp4;
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL26, पंचांगp6);
	पंचांगp5 = पंचांगp7 * 0x100;
	पंचांगp6 = पंचांगp5 / पंचांगp4;
	पंचांगp7 = पंचांगp5 % पंचांगp4;
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL27, पंचांगp6);
	पंचांगp5 = पंचांगp7 * 0x100;
	पंचांगp6 = पंचांगp5 / पंचांगp4;
	पंचांगp7 = पंचांगp5 % पंचांगp4;
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL28, पंचांगp6);
	पंचांगp5 = पंचांगp7 * 0x100;
	पंचांगp6 = पंचांगp5 / पंचांगp4;
	पंचांगp7 = पंचांगp5 % पंचांगp4;
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL29, पंचांगp6 + ((2 * पंचांगp7) / पंचांगp4));
	पंचांगp8 = b43_radio_पढ़ो(dev, B2062_S_RFPLL_CTL19);
	पंचांगp9 = ((2 * पंचांगp3 * (पंचांगp8 + 1)) + (3 * पंचांगp1)) / (6 * पंचांगp1);
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL23, (पंचांगp9 >> 8) + 16);
	b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL24, पंचांगp9 & 0xFF);

	lpphy_b2062_vco_calib(dev);
	अगर (b43_radio_पढ़ो(dev, B2062_S_RFPLL_CTL3) & 0x10) अणु
		b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL33, 0xFC);
		b43_radio_ग_लिखो(dev, B2062_S_RFPLL_CTL34, 0);
		lpphy_b2062_reset_pll_bias(dev);
		lpphy_b2062_vco_calib(dev);
		अगर (b43_radio_पढ़ो(dev, B2062_S_RFPLL_CTL3) & 0x10)
			err = -EIO;
	पूर्ण

	b43_radio_mask(dev, B2062_S_RFPLL_CTL14, ~0x04);
	वापस err;
पूर्ण

अटल व्योम lpphy_b2063_vco_calib(काष्ठा b43_wldev *dev)
अणु
	u16 पंचांगp;

	b43_radio_mask(dev, B2063_PLL_SP1, ~0x40);
	पंचांगp = b43_radio_पढ़ो(dev, B2063_PLL_JTAG_CALNRST) & 0xF8;
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_CALNRST, पंचांगp);
	udelay(1);
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_CALNRST, पंचांगp | 0x4);
	udelay(1);
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_CALNRST, पंचांगp | 0x6);
	udelay(1);
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_CALNRST, पंचांगp | 0x7);
	udelay(300);
	b43_radio_set(dev, B2063_PLL_SP1, 0x40);
पूर्ण

अटल पूर्णांक lpphy_b2063_tune(काष्ठा b43_wldev *dev,
			    अचिन्हित पूर्णांक channel)
अणु
	काष्ठा ssb_bus *bus = dev->dev->sdev->bus;

	अटल स्थिर काष्ठा b206x_channel *chandata = शून्य;
	u32 crystal_freq = bus->chipco.pmu.crystalfreq * 1000;
	u32 freqref, vco_freq, val1, val2, val3, समयout, समयoutref, count;
	u16 old_comm15, scale;
	u32 पंचांगp1, पंचांगp2, पंचांगp3, पंचांगp4, पंचांगp5, पंचांगp6;
	पूर्णांक i, भाग = (crystal_freq <= 26000000 ? 1 : 2);

	क्रम (i = 0; i < ARRAY_SIZE(b2063_chantbl); i++) अणु
		अगर (b2063_chantbl[i].channel == channel) अणु
			chandata = &b2063_chantbl[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (B43_WARN_ON(!chandata))
		वापस -EINVAL;

	b43_radio_ग_लिखो(dev, B2063_LOGEN_VCOBUF1, chandata->data[0]);
	b43_radio_ग_लिखो(dev, B2063_LOGEN_MIXER2, chandata->data[1]);
	b43_radio_ग_लिखो(dev, B2063_LOGEN_BUF2, chandata->data[2]);
	b43_radio_ग_लिखो(dev, B2063_LOGEN_RCCR1, chandata->data[3]);
	b43_radio_ग_लिखो(dev, B2063_A_RX_1ST3, chandata->data[4]);
	b43_radio_ग_लिखो(dev, B2063_A_RX_2ND1, chandata->data[5]);
	b43_radio_ग_लिखो(dev, B2063_A_RX_2ND4, chandata->data[6]);
	b43_radio_ग_लिखो(dev, B2063_A_RX_2ND7, chandata->data[7]);
	b43_radio_ग_लिखो(dev, B2063_A_RX_PS6, chandata->data[8]);
	b43_radio_ग_लिखो(dev, B2063_TX_RF_CTL2, chandata->data[9]);
	b43_radio_ग_लिखो(dev, B2063_TX_RF_CTL5, chandata->data[10]);
	b43_radio_ग_लिखो(dev, B2063_PA_CTL11, chandata->data[11]);

	old_comm15 = b43_radio_पढ़ो(dev, B2063_COMM15);
	b43_radio_set(dev, B2063_COMM15, 0x1E);

	अगर (chandata->freq > 4000) /* spec says 2484, but 4000 is safer */
		vco_freq = chandata->freq << 1;
	अन्यथा
		vco_freq = chandata->freq << 2;

	freqref = crystal_freq * 3;
	val1 = lpphy_qभाग_roundup(crystal_freq, 1000000, 16);
	val2 = lpphy_qभाग_roundup(crystal_freq, 1000000 * भाग, 16);
	val3 = lpphy_qभाग_roundup(vco_freq, 3, 16);
	समयout = ((((8 * crystal_freq) / (भाग * 5000000)) + 1) >> 1) - 1;
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_PLL_VCO_CALIB3, 0x2);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_VCO_CALIB6,
			  0xFFF8, समयout >> 2);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_VCO_CALIB7,
			  0xFF9F,समयout << 5);

	समयoutref = ((((8 * crystal_freq) / (भाग * (समयout + 1))) +
						999999) / 1000000) + 1;
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_PLL_VCO_CALIB5, समयoutref);

	count = lpphy_qभाग_roundup(val3, val2 + 16, 16);
	count *= (समयout + 1) * (समयoutref + 1);
	count--;
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_VCO_CALIB7,
						0xF0, count >> 8);
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_PLL_VCO_CALIB8, count & 0xFF);

	पंचांगp1 = ((val3 * 62500) / freqref) << 4;
	पंचांगp2 = ((val3 * 62500) % freqref) << 4;
	जबतक (पंचांगp2 >= freqref) अणु
		पंचांगp1++;
		पंचांगp2 -= freqref;
	पूर्ण
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_SG1, 0xFFE0, पंचांगp1 >> 4);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_SG2, 0xFE0F, पंचांगp1 << 4);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_SG2, 0xFFF0, पंचांगp1 >> 16);
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_PLL_SG3, (पंचांगp2 >> 8) & 0xFF);
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_PLL_SG4, पंचांगp2 & 0xFF);

	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_PLL_LF1, 0xB9);
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_PLL_LF2, 0x88);
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_PLL_LF3, 0x28);
	b43_radio_ग_लिखो(dev, B2063_PLL_JTAG_PLL_LF4, 0x63);

	पंचांगp3 = ((41 * (val3 - 3000)) /1200) + 27;
	पंचांगp4 = lpphy_qभाग_roundup(132000 * पंचांगp1, 8451, 16);

	अगर ((पंचांगp4 + पंचांगp3 - 1) / पंचांगp3 > 60) अणु
		scale = 1;
		पंचांगp5 = ((पंचांगp4 + पंचांगp3) / (पंचांगp3 << 1)) - 8;
	पूर्ण अन्यथा अणु
		scale = 0;
		पंचांगp5 = ((पंचांगp4 + (पंचांगp3 >> 1)) / पंचांगp3) - 8;
	पूर्ण
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_CP2, 0xFFC0, पंचांगp5);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_CP2, 0xFFBF, scale << 6);

	पंचांगp6 = lpphy_qभाग_roundup(100 * val1, val3, 16);
	पंचांगp6 *= (पंचांगp5 * 8) * (scale + 1);
	अगर (पंचांगp6 > 150)
		पंचांगp6 = 0;

	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_CP3, 0xFFE0, पंचांगp6);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_CP3, 0xFFDF, scale << 5);

	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_XTAL_12, 0xFFFB, 0x4);
	अगर (crystal_freq > 26000000)
		b43_radio_set(dev, B2063_PLL_JTAG_PLL_XTAL_12, 0x2);
	अन्यथा
		b43_radio_mask(dev, B2063_PLL_JTAG_PLL_XTAL_12, 0xFD);

	अगर (val1 == 45)
		b43_radio_set(dev, B2063_PLL_JTAG_PLL_VCO1, 0x2);
	अन्यथा
		b43_radio_mask(dev, B2063_PLL_JTAG_PLL_VCO1, 0xFD);

	b43_radio_set(dev, B2063_PLL_SP2, 0x3);
	udelay(1);
	b43_radio_mask(dev, B2063_PLL_SP2, 0xFFFC);
	lpphy_b2063_vco_calib(dev);
	b43_radio_ग_लिखो(dev, B2063_COMM15, old_comm15);

	वापस 0;
पूर्ण

अटल पूर्णांक b43_lpphy_op_चयन_channel(काष्ठा b43_wldev *dev,
				       अचिन्हित पूर्णांक new_channel)
अणु
	काष्ठा b43_phy_lp *lpphy = dev->phy.lp;
	पूर्णांक err;

	अगर (dev->phy.radio_ver == 0x2063) अणु
		err = lpphy_b2063_tune(dev, new_channel);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = lpphy_b2062_tune(dev, new_channel);
		अगर (err)
			वापस err;
		lpphy_set_analog_filter(dev, new_channel);
		lpphy_adjust_gain_table(dev, channel2freq_lp(new_channel));
	पूर्ण

	lpphy->channel = new_channel;
	b43_ग_लिखो16(dev, B43_MMIO_CHANNEL, new_channel);

	वापस 0;
पूर्ण

अटल पूर्णांक b43_lpphy_op_init(काष्ठा b43_wldev *dev)
अणु
	पूर्णांक err;

	अगर (dev->dev->bus_type != B43_BUS_SSB) अणु
		b43err(dev->wl, "LP-PHY is supported only on SSB!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	lpphy_पढ़ो_band_sprom(dev); //FIXME should this be in prepare_काष्ठाs?
	lpphy_baseband_init(dev);
	lpphy_radio_init(dev);
	lpphy_calibrate_rc(dev);
	err = b43_lpphy_op_चयन_channel(dev, 7);
	अगर (err) अणु
		b43dbg(dev->wl, "Switch to channel 7 failed, error = %d.\n",
		       err);
	पूर्ण
	lpphy_tx_pctl_init(dev);
	lpphy_calibration(dev);
	//TODO ACI init

	वापस 0;
पूर्ण

अटल व्योम b43_lpphy_op_adjust_txघातer(काष्ठा b43_wldev *dev)
अणु
	//TODO
पूर्ण

अटल क्रमागत b43_txpwr_result b43_lpphy_op_recalc_txघातer(काष्ठा b43_wldev *dev,
							 bool ignore_tssi)
अणु
	//TODO
	वापस B43_TXPWR_RES_DONE;
पूर्ण

अटल व्योम b43_lpphy_op_चयन_analog(काष्ठा b43_wldev *dev, bool on)
अणु
       अगर (on) अणु
               b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVR, 0xfff8);
       पूर्ण अन्यथा अणु
               b43_phy_set(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0x0007);
               b43_phy_set(dev, B43_LPPHY_AFE_CTL_OVR, 0x0007);
       पूर्ण
पूर्ण

अटल व्योम b43_lpphy_op_pwork_15sec(काष्ठा b43_wldev *dev)
अणु
	//TODO
पूर्ण

स्थिर काष्ठा b43_phy_operations b43_phyops_lp = अणु
	.allocate		= b43_lpphy_op_allocate,
	.मुक्त			= b43_lpphy_op_मुक्त,
	.prepare_काष्ठाs	= b43_lpphy_op_prepare_काष्ठाs,
	.init			= b43_lpphy_op_init,
	.phy_maskset		= b43_lpphy_op_maskset,
	.radio_पढ़ो		= b43_lpphy_op_radio_पढ़ो,
	.radio_ग_लिखो		= b43_lpphy_op_radio_ग_लिखो,
	.software_rfसमाप्त	= b43_lpphy_op_software_rfसमाप्त,
	.चयन_analog		= b43_lpphy_op_चयन_analog,
	.चयन_channel		= b43_lpphy_op_चयन_channel,
	.get_शेष_chan	= b43_lpphy_op_get_शेष_chan,
	.set_rx_antenna		= b43_lpphy_op_set_rx_antenna,
	.recalc_txघातer		= b43_lpphy_op_recalc_txघातer,
	.adjust_txघातer		= b43_lpphy_op_adjust_txघातer,
	.pwork_15sec		= b43_lpphy_op_pwork_15sec,
	.pwork_60sec		= lpphy_calibration,
पूर्ण;
