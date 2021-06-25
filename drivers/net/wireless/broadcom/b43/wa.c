<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver

  PHY workarounds.

  Copyright (c) 2005-2007 Stefano Brivio <stefano.brivio@polimi.it>
  Copyright (c) 2005-2007 Michael Buesch <m@bues.ch>


*/

#समावेश "b43.h"
#समावेश "main.h"
#समावेश "tables.h"
#समावेश "phy_common.h"
#समावेश "wa.h"

व्योम b43_wa_initgains(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	b43_phy_ग_लिखो(dev, B43_PHY_LNAHPFCTL, 0x1FF9);
	b43_phy_mask(dev, B43_PHY_LPFGAINCTL, 0xFF0F);
	अगर (phy->rev <= 2)
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_LPFGAIN, 0, 0x1FBF);
	b43_radio_ग_लिखो16(dev, 0x0002, 0x1FBF);

	b43_phy_ग_लिखो(dev, 0x0024, 0x4680);
	b43_phy_ग_लिखो(dev, 0x0020, 0x0003);
	b43_phy_ग_लिखो(dev, 0x001D, 0x0F40);
	b43_phy_ग_लिखो(dev, 0x001F, 0x1C00);
	अगर (phy->rev <= 3)
		b43_phy_maskset(dev, 0x002A, 0x00FF, 0x0400);
	अन्यथा अगर (phy->rev == 5) अणु
		b43_phy_maskset(dev, 0x002A, 0x00FF, 0x1A00);
		b43_phy_ग_लिखो(dev, 0x00CC, 0x2121);
	पूर्ण
	अगर (phy->rev >= 3)
		b43_phy_ग_लिखो(dev, 0x00BA, 0x3ED5);
पूर्ण

अटल व्योम b43_wa_rssi_lt(काष्ठा b43_wldev *dev) /* RSSI lookup table */
अणु
	पूर्णांक i;

	अगर (0 /* FIXME: For APHY.rev=2 this might be needed */) अणु
		क्रम (i = 0; i < 8; i++)
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_RSSI, i, i + 8);
		क्रम (i = 8; i < 16; i++)
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_RSSI, i, i - 8);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 64; i++)
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_RSSI, i, i);
	पूर्ण
पूर्ण

अटल व्योम b43_wa_analog(काष्ठा b43_wldev *dev)
अणु
	u16 ofdmrev;

	ofdmrev = b43_phy_पढ़ो(dev, B43_PHY_VERSION_OFDM) & B43_PHYVER_VERSION;
	अगर (ofdmrev > 2) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_PWRDOWN, 0x1000);
	पूर्ण अन्यथा अणु
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_DAC, 3, 0x1044);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_DAC, 4, 0x7201);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_DAC, 6, 0x0040);
	पूर्ण
पूर्ण

अटल व्योम b43_wa_fft(काष्ठा b43_wldev *dev) /* Fine frequency table */
अणु
	पूर्णांक i;

	क्रम (i = 0; i < B43_TAB_FINEFREQG_SIZE; i++)
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_DACRFPABB, i,
				    b43_tab_finefreqg[i]);
पूर्ण

अटल व्योम b43_wa_nft(काष्ठा b43_wldev *dev) /* Noise figure table */
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	पूर्णांक i;

	अगर (phy->rev == 1)
		क्रम (i = 0; i < B43_TAB_NOISEG1_SIZE; i++)
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC2, i,
					    b43_tab_noiseg1[i]);
	अन्यथा
		क्रम (i = 0; i < B43_TAB_NOISEG2_SIZE; i++)
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC2, i,
					    b43_tab_noiseg2[i]);
पूर्ण

अटल व्योम b43_wa_rt(काष्ठा b43_wldev *dev) /* Rotor table */
अणु
	पूर्णांक i;

	क्रम (i = 0; i < B43_TAB_ROTOR_SIZE; i++)
		b43_ofdmtab_ग_लिखो32(dev, B43_OFDMTAB_ROTOR, i, b43_tab_rotor[i]);
पूर्ण

अटल व्योम b43_ग_लिखो_nst(काष्ठा b43_wldev *dev, स्थिर u16 *nst)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < B43_TAB_NOISESCALE_SIZE; i++)
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_NOISESCALE, i, nst[i]);
पूर्ण

अटल व्योम b43_wa_nst(काष्ठा b43_wldev *dev) /* Noise scale table */
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (phy->rev >= 6) अणु
		अगर (b43_phy_पढ़ो(dev, B43_PHY_ENCORE) & B43_PHY_ENCORE_EN)
			b43_ग_लिखो_nst(dev, b43_tab_noisescaleg3);
		अन्यथा
			b43_ग_लिखो_nst(dev, b43_tab_noisescaleg2);
	पूर्ण अन्यथा अणु
		b43_ग_लिखो_nst(dev, b43_tab_noisescaleg1);
	पूर्ण
पूर्ण

अटल व्योम b43_wa_art(काष्ठा b43_wldev *dev) /* ADV retard table */
अणु
	पूर्णांक i;

	क्रम (i = 0; i < B43_TAB_RETARD_SIZE; i++)
			b43_ofdmtab_ग_लिखो32(dev, B43_OFDMTAB_ADVRETARD,
				i, b43_tab_retard[i]);
पूर्ण

अटल व्योम b43_wa_msst(काष्ठा b43_wldev *dev) /* Min sigma square table */
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	पूर्णांक i;
	स्थिर u16 *tab;

	अगर (phy->type == B43_PHYTYPE_G) अणु
		tab = b43_tab_sigmasqr2;
	पूर्ण अन्यथा अणु
		B43_WARN_ON(1);
		वापस;
	पूर्ण

	क्रम (i = 0; i < B43_TAB_SIGMASQR_SIZE; i++) अणु
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_MINSIGSQ,
					i, tab[i]);
	पूर्ण
पूर्ण

अटल व्योम b43_wa_crs_ed(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (phy->rev == 1) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_CRSTHRES1_R1, 0x4F19);
	पूर्ण अन्यथा अगर (phy->rev == 2) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_CRSTHRES1, 0x1861);
		b43_phy_ग_लिखो(dev, B43_PHY_CRSTHRES2, 0x0271);
		b43_phy_set(dev, B43_PHY_ANTDWELL, 0x0800);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_PHY_CRSTHRES1, 0x0098);
		b43_phy_ग_लिखो(dev, B43_PHY_CRSTHRES2, 0x0070);
		b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0xC9), 0x0080);
		b43_phy_set(dev, B43_PHY_ANTDWELL, 0x0800);
	पूर्ण
पूर्ण

अटल व्योम b43_wa_crs_thr(काष्ठा b43_wldev *dev)
अणु
	b43_phy_maskset(dev, B43_PHY_CRS0, ~0x03C0, 0xD000);
पूर्ण

अटल व्योम b43_wa_crs_blank(काष्ठा b43_wldev *dev)
अणु
	b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0x2C), 0x005A);
पूर्ण

अटल व्योम b43_wa_cck_shअगरtbits(काष्ठा b43_wldev *dev)
अणु
	b43_phy_ग_लिखो(dev, B43_PHY_CCKSHIFTBITS, 0x0026);
पूर्ण

अटल व्योम b43_wa_wrssi_offset(काष्ठा b43_wldev *dev)
अणु
	पूर्णांक i;

	अगर (dev->phy.rev == 1) अणु
		क्रम (i = 0; i < 16; i++) अणु
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_WRSSI_R1,
						i, 0x0020);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 32; i++) अणु
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_WRSSI,
						i, 0x0820);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43_wa_txpuoff_rxpuon(काष्ठा b43_wldev *dev)
अणु
	b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_UNKNOWN_0F, 2, 15);
	b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_UNKNOWN_0F, 3, 20);
पूर्ण

अटल व्योम b43_wa_altagc(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (phy->rev == 1) अणु
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC1_R1, 0, 254);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC1_R1, 1, 13);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC1_R1, 2, 19);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC1_R1, 3, 25);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC2, 0, 0x2710);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC2, 1, 0x9B83);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC2, 2, 0x9B83);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC2, 3, 0x0F8D);
		b43_phy_ग_लिखो(dev, B43_PHY_LMS, 4);
	पूर्ण अन्यथा अणु
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC1, 0, 254);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC1, 1, 13);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC1, 2, 19);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC1, 3, 25);
	पूर्ण

	b43_phy_maskset(dev, B43_PHY_CCKSHIFTBITS_WA, 0x00FF, 0x5700);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x1A), ~0x007F, 0x000F);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x1A), ~0x3F80, 0x2B80);
	b43_phy_maskset(dev, B43_PHY_ANTWRSETT, 0xF0FF, 0x0300);
	b43_radio_set(dev, 0x7A, 0x0008);
	b43_phy_maskset(dev, B43_PHY_N1P1GAIN, ~0x000F, 0x0008);
	b43_phy_maskset(dev, B43_PHY_P1P2GAIN, ~0x0F00, 0x0600);
	b43_phy_maskset(dev, B43_PHY_N1N2GAIN, ~0x0F00, 0x0700);
	b43_phy_maskset(dev, B43_PHY_N1P1GAIN, ~0x0F00, 0x0100);
	अगर (phy->rev == 1) अणु
		b43_phy_maskset(dev, B43_PHY_N1N2GAIN, ~0x000F, 0x0007);
	पूर्ण
	b43_phy_maskset(dev, B43_PHY_OFDM(0x88), ~0x00FF, 0x001C);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x88), ~0x3F00, 0x0200);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x96), ~0x00FF, 0x001C);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x89), ~0x00FF, 0x0020);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x89), ~0x3F00, 0x0200);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x82), ~0x00FF, 0x002E);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x96), 0x00FF, 0x1A00);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x81), ~0x00FF, 0x0028);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x81), 0x00FF, 0x2C00);
	अगर (phy->rev == 1) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_PEAK_COUNT, 0x092B);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x1B), ~0x001E, 0x0002);
	पूर्ण अन्यथा अणु
		b43_phy_mask(dev, B43_PHY_OFDM(0x1B), ~0x001E);
		b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0x1F), 0x287A);
		b43_phy_maskset(dev, B43_PHY_LPFGAINCTL, ~0x000F, 0x0004);
		अगर (phy->rev >= 6) अणु
			b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0x22), 0x287A);
			b43_phy_maskset(dev, B43_PHY_LPFGAINCTL, 0x0FFF, 0x3000);
		पूर्ण
	पूर्ण
	b43_phy_maskset(dev, B43_PHY_DIVSRCHIDX, 0x8080, 0x7874);
	b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0x8E), 0x1C00);
	अगर (phy->rev == 1) अणु
		b43_phy_maskset(dev, B43_PHY_DIVP1P2GAIN, ~0x0F00, 0x0600);
		b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0x8B), 0x005E);
		b43_phy_maskset(dev, B43_PHY_ANTWRSETT, ~0x00FF, 0x001E);
		b43_phy_ग_लिखो(dev, B43_PHY_OFDM(0x8D), 0x0002);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC3_R1, 0, 0);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC3_R1, 1, 7);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC3_R1, 2, 16);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC3_R1, 3, 28);
	पूर्ण अन्यथा अणु
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC3, 0, 0);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC3, 1, 7);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC3, 2, 16);
		b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_AGC3, 3, 28);
	पूर्ण
	अगर (phy->rev >= 6) अणु
		b43_phy_mask(dev, B43_PHY_OFDM(0x26), ~0x0003);
		b43_phy_mask(dev, B43_PHY_OFDM(0x26), ~0x1000);
	पूर्ण
	b43_phy_पढ़ो(dev, B43_PHY_VERSION_OFDM); /* Dummy पढ़ो */
पूर्ण

अटल व्योम b43_wa_tr_ltov(काष्ठा b43_wldev *dev) /* TR Lookup Table Original Values */
अणु
	b43_gtab_ग_लिखो(dev, B43_GTAB_ORIGTR, 0, 0x7654);
पूर्ण

अटल व्योम b43_wa_cpll_nonpilot(काष्ठा b43_wldev *dev)
अणु
	b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_UNKNOWN_11, 0, 0);
	b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_UNKNOWN_11, 1, 0);
पूर्ण

अटल व्योम b43_wa_boards_g(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (dev->dev->board_venकरोr != SSB_BOARDVENDOR_BCM ||
	    dev->dev->board_type != SSB_BOARD_BU4306 ||
	    dev->dev->board_rev != 0x17) अणु
		अगर (phy->rev < 2) अणु
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX_R1, 1, 0x0002);
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX_R1, 2, 0x0001);
		पूर्ण अन्यथा अणु
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX, 1, 0x0002);
			b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX, 2, 0x0001);
			अगर ((sprom->boardflags_lo & B43_BFL_EXTLNA) &&
			    (phy->rev >= 7)) अणु
				b43_phy_mask(dev, B43_PHY_EXTG(0x11), 0xF7FF);
				b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX, 0x0020, 0x0001);
				b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX, 0x0021, 0x0001);
				b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX, 0x0022, 0x0001);
				b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX, 0x0023, 0x0000);
				b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX, 0x0000, 0x0000);
				b43_ofdmtab_ग_लिखो16(dev, B43_OFDMTAB_GAINX, 0x0003, 0x0002);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (sprom->boardflags_lo & B43_BFL_FEM) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_GTABCTL, 0x3120);
		b43_phy_ग_लिखो(dev, B43_PHY_GTABDATA, 0xC480);
	पूर्ण
पूर्ण

व्योम b43_wa_all(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (phy->type == B43_PHYTYPE_G) अणु
		चयन (phy->rev) अणु
		हाल 1://XXX review rev1
			b43_wa_crs_ed(dev);
			b43_wa_crs_thr(dev);
			b43_wa_crs_blank(dev);
			b43_wa_cck_shअगरtbits(dev);
			b43_wa_fft(dev);
			b43_wa_nft(dev);
			b43_wa_rt(dev);
			b43_wa_nst(dev);
			b43_wa_art(dev);
			b43_wa_wrssi_offset(dev);
			b43_wa_altagc(dev);
			अवरोध;
		हाल 2:
		हाल 6:
		हाल 7:
		हाल 8:
		हाल 9:
			b43_wa_tr_ltov(dev);
			b43_wa_crs_ed(dev);
			b43_wa_rssi_lt(dev);
			b43_wa_nft(dev);
			b43_wa_nst(dev);
			b43_wa_msst(dev);
			b43_wa_wrssi_offset(dev);
			b43_wa_altagc(dev);
			b43_wa_analog(dev);
			b43_wa_txpuoff_rxpuon(dev);
			अवरोध;
		शेष:
			B43_WARN_ON(1);
		पूर्ण
		b43_wa_boards_g(dev);
	पूर्ण अन्यथा अणु /* No N PHY support so far, LP PHY is in phy_lp.c */
		B43_WARN_ON(1);
	पूर्ण

	b43_wa_cpll_nonpilot(dev);
पूर्ण
