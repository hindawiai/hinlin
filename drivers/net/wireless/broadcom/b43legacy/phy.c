<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43legacy wireless driver

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>,
		     Stefano Brivio <stefano.brivio@polimi.it>
		     Michael Buesch <m@bues.ch>
		     Danny van Dyk <kugelfang@gentoo.org>
     Andreas Jaggi <andreas.jaggi@waterwave.ch>
  Copyright (c) 2007 Larry Finger <Larry.Finger@lwfinger.net>

  Some parts of the code in this file are derived from the ipw2200
  driver  Copyright(c) 2003 - 2004 Intel Corporation.


*/

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "b43legacy.h"
#समावेश "phy.h"
#समावेश "main.h"
#समावेश "radio.h"
#समावेश "ilt.h"


अटल स्थिर s8 b43legacy_tssi2dbm_b_table[] = अणु
	0x4D, 0x4C, 0x4B, 0x4A,
	0x4A, 0x49, 0x48, 0x47,
	0x47, 0x46, 0x45, 0x45,
	0x44, 0x43, 0x42, 0x42,
	0x41, 0x40, 0x3F, 0x3E,
	0x3D, 0x3C, 0x3B, 0x3A,
	0x39, 0x38, 0x37, 0x36,
	0x35, 0x34, 0x32, 0x31,
	0x30, 0x2F, 0x2D, 0x2C,
	0x2B, 0x29, 0x28, 0x26,
	0x25, 0x23, 0x21, 0x1F,
	0x1D, 0x1A, 0x17, 0x14,
	0x10, 0x0C, 0x06, 0x00,
	  -7,   -7,   -7,   -7,
	  -7,   -7,   -7,   -7,
	  -7,   -7,   -7,   -7,
पूर्ण;

अटल स्थिर s8 b43legacy_tssi2dbm_g_table[] = अणु
	 77,  77,  77,  76,
	 76,  76,  75,  75,
	 74,  74,  73,  73,
	 73,  72,  72,  71,
	 71,  70,  70,  69,
	 68,  68,  67,  67,
	 66,  65,  65,  64,
	 63,  63,  62,  61,
	 60,  59,  58,  57,
	 56,  55,  54,  53,
	 52,  50,  49,  47,
	 45,  43,  40,  37,
	 33,  28,  22,  14,
	  5,  -7, -20, -20,
	-20, -20, -20, -20,
	-20, -20, -20, -20,
पूर्ण;

अटल व्योम b43legacy_phy_initg(काष्ठा b43legacy_wldev *dev);

/* Lock the PHY रेजिस्टरs against concurrent access from the microcode.
 * This lock is nonrecursive. */
व्योम b43legacy_phy_lock(काष्ठा b43legacy_wldev *dev)
अणु
#अगर B43legacy_DEBUG
	B43legacy_WARN_ON(dev->phy.phy_locked);
	dev->phy.phy_locked = 1;
#पूर्ण_अगर

	अगर (dev->dev->id.revision < 3) अणु
		b43legacy_mac_suspend(dev);
	पूर्ण अन्यथा अणु
		अगर (!b43legacy_is_mode(dev->wl, NL80211_IFTYPE_AP))
			b43legacy_घातer_saving_ctl_bits(dev, -1, 1);
	पूर्ण
पूर्ण

व्योम b43legacy_phy_unlock(काष्ठा b43legacy_wldev *dev)
अणु
#अगर B43legacy_DEBUG
	B43legacy_WARN_ON(!dev->phy.phy_locked);
	dev->phy.phy_locked = 0;
#पूर्ण_अगर

	अगर (dev->dev->id.revision < 3) अणु
		b43legacy_mac_enable(dev);
	पूर्ण अन्यथा अणु
		अगर (!b43legacy_is_mode(dev->wl, NL80211_IFTYPE_AP))
			b43legacy_घातer_saving_ctl_bits(dev, -1, -1);
	पूर्ण
पूर्ण

u16 b43legacy_phy_पढ़ो(काष्ठा b43legacy_wldev *dev, u16 offset)
अणु
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_PHY_CONTROL, offset);
	वापस b43legacy_पढ़ो16(dev, B43legacy_MMIO_PHY_DATA);
पूर्ण

व्योम b43legacy_phy_ग_लिखो(काष्ठा b43legacy_wldev *dev, u16 offset, u16 val)
अणु
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_PHY_CONTROL, offset);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_PHY_DATA, val);
पूर्ण

व्योम b43legacy_phy_calibrate(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL); /* Dummy पढ़ो. */
	अगर (phy->calibrated)
		वापस;
	अगर (phy->type == B43legacy_PHYTYPE_G && phy->rev == 1) अणु
		b43legacy_wireless_core_reset(dev, 0);
		b43legacy_phy_initg(dev);
		b43legacy_wireless_core_reset(dev, B43legacy_TMSLOW_GMODE);
	पूर्ण
	phy->calibrated = 1;
पूर्ण

/* initialize B PHY घातer control
 * as described in https://bcm-specs.sipsolutions.net/InitPowerControl
 */
अटल व्योम b43legacy_phy_init_pctl(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 saved_batt = 0;
	u16 saved_ratt = 0;
	u16 saved_txctl1 = 0;
	पूर्णांक must_reset_txघातer = 0;

	B43legacy_BUG_ON(!(phy->type == B43legacy_PHYTYPE_B ||
			  phy->type == B43legacy_PHYTYPE_G));
	अगर (is_bcm_board_venकरोr(dev) &&
	    (dev->dev->bus->boardinfo.type == 0x0416))
		वापस;

	b43legacy_phy_ग_लिखो(dev, 0x0028, 0x8018);
	b43legacy_ग_लिखो16(dev, 0x03E6, b43legacy_पढ़ो16(dev, 0x03E6) & 0xFFDF);

	अगर (phy->type == B43legacy_PHYTYPE_G) अणु
		अगर (!phy->gmode)
			वापस;
		b43legacy_phy_ग_लिखो(dev, 0x047A, 0xC111);
	पूर्ण
	अगर (phy->savedpctlreg != 0xFFFF)
		वापस;
#अगर_घोषित CONFIG_B43LEGACY_DEBUG
	अगर (phy->manual_txघातer_control)
		वापस;
#पूर्ण_अगर

	अगर (phy->type == B43legacy_PHYTYPE_B &&
	    phy->rev >= 2 &&
	    phy->radio_ver == 0x2050)
		b43legacy_radio_ग_लिखो16(dev, 0x0076,
					b43legacy_radio_पढ़ो16(dev, 0x0076)
					| 0x0084);
	अन्यथा अणु
		saved_batt = phy->bbatt;
		saved_ratt = phy->rfatt;
		saved_txctl1 = phy->txctl1;
		अगर ((phy->radio_rev >= 6) && (phy->radio_rev <= 8)
		    && /*FIXME: incomplete specs क्रम 5 < revision < 9 */ 0)
			b43legacy_radio_set_txघातer_bg(dev, 0xB, 0x1F, 0);
		अन्यथा
			b43legacy_radio_set_txघातer_bg(dev, 0xB, 9, 0);
		must_reset_txघातer = 1;
	पूर्ण
	b43legacy_dummy_transmission(dev);

	phy->savedpctlreg = b43legacy_phy_पढ़ो(dev, B43legacy_PHY_G_PCTL);

	अगर (must_reset_txघातer)
		b43legacy_radio_set_txघातer_bg(dev, saved_batt, saved_ratt,
					       saved_txctl1);
	अन्यथा
		b43legacy_radio_ग_लिखो16(dev, 0x0076, b43legacy_radio_पढ़ो16(dev,
					0x0076) & 0xFF7B);
	b43legacy_radio_clear_tssi(dev);
पूर्ण

अटल व्योम b43legacy_phy_agcsetup(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 offset = 0x0000;

	अगर (phy->rev == 1)
		offset = 0x4C00;

	b43legacy_ilt_ग_लिखो(dev, offset, 0x00FE);
	b43legacy_ilt_ग_लिखो(dev, offset + 1, 0x000D);
	b43legacy_ilt_ग_लिखो(dev, offset + 2, 0x0013);
	b43legacy_ilt_ग_लिखो(dev, offset + 3, 0x0019);

	अगर (phy->rev == 1) अणु
		b43legacy_ilt_ग_लिखो(dev, 0x1800, 0x2710);
		b43legacy_ilt_ग_लिखो(dev, 0x1801, 0x9B83);
		b43legacy_ilt_ग_लिखो(dev, 0x1802, 0x9B83);
		b43legacy_ilt_ग_लिखो(dev, 0x1803, 0x0F8D);
		b43legacy_phy_ग_लिखो(dev, 0x0455, 0x0004);
	पूर्ण

	b43legacy_phy_ग_लिखो(dev, 0x04A5, (b43legacy_phy_पढ़ो(dev, 0x04A5)
					  & 0x00FF) | 0x5700);
	b43legacy_phy_ग_लिखो(dev, 0x041A, (b43legacy_phy_पढ़ो(dev, 0x041A)
					  & 0xFF80) | 0x000F);
	b43legacy_phy_ग_लिखो(dev, 0x041A, (b43legacy_phy_पढ़ो(dev, 0x041A)
					  & 0xC07F) | 0x2B80);
	b43legacy_phy_ग_लिखो(dev, 0x048C, (b43legacy_phy_पढ़ो(dev, 0x048C)
					  & 0xF0FF) | 0x0300);

	b43legacy_radio_ग_लिखो16(dev, 0x007A,
				b43legacy_radio_पढ़ो16(dev, 0x007A)
				| 0x0008);

	b43legacy_phy_ग_लिखो(dev, 0x04A0, (b43legacy_phy_पढ़ो(dev, 0x04A0)
			    & 0xFFF0) | 0x0008);
	b43legacy_phy_ग_लिखो(dev, 0x04A1, (b43legacy_phy_पढ़ो(dev, 0x04A1)
			    & 0xF0FF) | 0x0600);
	b43legacy_phy_ग_लिखो(dev, 0x04A2, (b43legacy_phy_पढ़ो(dev, 0x04A2)
			    & 0xF0FF) | 0x0700);
	b43legacy_phy_ग_लिखो(dev, 0x04A0, (b43legacy_phy_पढ़ो(dev, 0x04A0)
			    & 0xF0FF) | 0x0100);

	अगर (phy->rev == 1)
		b43legacy_phy_ग_लिखो(dev, 0x04A2,
				    (b43legacy_phy_पढ़ो(dev, 0x04A2)
				    & 0xFFF0) | 0x0007);

	b43legacy_phy_ग_लिखो(dev, 0x0488, (b43legacy_phy_पढ़ो(dev, 0x0488)
			    & 0xFF00) | 0x001C);
	b43legacy_phy_ग_लिखो(dev, 0x0488, (b43legacy_phy_पढ़ो(dev, 0x0488)
			    & 0xC0FF) | 0x0200);
	b43legacy_phy_ग_लिखो(dev, 0x0496, (b43legacy_phy_पढ़ो(dev, 0x0496)
			    & 0xFF00) | 0x001C);
	b43legacy_phy_ग_लिखो(dev, 0x0489, (b43legacy_phy_पढ़ो(dev, 0x0489)
			    & 0xFF00) | 0x0020);
	b43legacy_phy_ग_लिखो(dev, 0x0489, (b43legacy_phy_पढ़ो(dev, 0x0489)
			    & 0xC0FF) | 0x0200);
	b43legacy_phy_ग_लिखो(dev, 0x0482, (b43legacy_phy_पढ़ो(dev, 0x0482)
			    & 0xFF00) | 0x002E);
	b43legacy_phy_ग_लिखो(dev, 0x0496, (b43legacy_phy_पढ़ो(dev, 0x0496)
			    & 0x00FF) | 0x1A00);
	b43legacy_phy_ग_लिखो(dev, 0x0481, (b43legacy_phy_पढ़ो(dev, 0x0481)
			    & 0xFF00) | 0x0028);
	b43legacy_phy_ग_लिखो(dev, 0x0481, (b43legacy_phy_पढ़ो(dev, 0x0481)
			    & 0x00FF) | 0x2C00);

	अगर (phy->rev == 1) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0430, 0x092B);
		b43legacy_phy_ग_लिखो(dev, 0x041B,
				    (b43legacy_phy_पढ़ो(dev, 0x041B)
				    & 0xFFE1) | 0x0002);
	पूर्ण अन्यथा अणु
		b43legacy_phy_ग_लिखो(dev, 0x041B,
				    b43legacy_phy_पढ़ो(dev, 0x041B) & 0xFFE1);
		b43legacy_phy_ग_लिखो(dev, 0x041F, 0x287A);
		b43legacy_phy_ग_लिखो(dev, 0x0420,
				    (b43legacy_phy_पढ़ो(dev, 0x0420)
				    & 0xFFF0) | 0x0004);
	पूर्ण

	अगर (phy->rev > 2) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0422, 0x287A);
		b43legacy_phy_ग_लिखो(dev, 0x0420,
				    (b43legacy_phy_पढ़ो(dev, 0x0420)
				    & 0x0FFF) | 0x3000);
	पूर्ण

	b43legacy_phy_ग_लिखो(dev, 0x04A8, (b43legacy_phy_पढ़ो(dev, 0x04A8)
			    & 0x8080) | 0x7874);
	b43legacy_phy_ग_लिखो(dev, 0x048E, 0x1C00);

	अगर (phy->rev == 1) अणु
		b43legacy_phy_ग_लिखो(dev, 0x04AB,
				    (b43legacy_phy_पढ़ो(dev, 0x04AB)
				    & 0xF0FF) | 0x0600);
		b43legacy_phy_ग_लिखो(dev, 0x048B, 0x005E);
		b43legacy_phy_ग_लिखो(dev, 0x048C,
				    (b43legacy_phy_पढ़ो(dev, 0x048C) & 0xFF00)
				    | 0x001E);
		b43legacy_phy_ग_लिखो(dev, 0x048D, 0x0002);
	पूर्ण

	b43legacy_ilt_ग_लिखो(dev, offset + 0x0800, 0);
	b43legacy_ilt_ग_लिखो(dev, offset + 0x0801, 7);
	b43legacy_ilt_ग_लिखो(dev, offset + 0x0802, 16);
	b43legacy_ilt_ग_लिखो(dev, offset + 0x0803, 28);

	अगर (phy->rev >= 6) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0426,
				    (b43legacy_phy_पढ़ो(dev, 0x0426) & 0xFFFC));
		b43legacy_phy_ग_लिखो(dev, 0x0426,
				    (b43legacy_phy_पढ़ो(dev, 0x0426) & 0xEFFF));
	पूर्ण
पूर्ण

अटल व्योम b43legacy_phy_setupg(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 i;

	B43legacy_BUG_ON(phy->type != B43legacy_PHYTYPE_G);
	अगर (phy->rev == 1) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0406, 0x4F19);
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
				    (b43legacy_phy_पढ़ो(dev,
				    B43legacy_PHY_G_CRS) & 0xFC3F) | 0x0340);
		b43legacy_phy_ग_लिखो(dev, 0x042C, 0x005A);
		b43legacy_phy_ग_लिखो(dev, 0x0427, 0x001A);

		क्रम (i = 0; i < B43legacy_ILT_FINEFREQG_SIZE; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x5800 + i,
					    b43legacy_ilt_finefreqg[i]);
		क्रम (i = 0; i < B43legacy_ILT_NOISEG1_SIZE; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x1800 + i,
					    b43legacy_ilt_noiseg1[i]);
		क्रम (i = 0; i < B43legacy_ILT_ROTOR_SIZE; i++)
			b43legacy_ilt_ग_लिखो32(dev, 0x2000 + i,
					      b43legacy_ilt_rotor[i]);
	पूर्ण अन्यथा अणु
		/* nrssi values are चिन्हित 6-bit values. Why 0x7654 here? */
		b43legacy_nrssi_hw_ग_लिखो(dev, 0xBA98, (s16)0x7654);

		अगर (phy->rev == 2) अणु
			b43legacy_phy_ग_लिखो(dev, 0x04C0, 0x1861);
			b43legacy_phy_ग_लिखो(dev, 0x04C1, 0x0271);
		पूर्ण अन्यथा अगर (phy->rev > 2) अणु
			b43legacy_phy_ग_लिखो(dev, 0x04C0, 0x0098);
			b43legacy_phy_ग_लिखो(dev, 0x04C1, 0x0070);
			b43legacy_phy_ग_लिखो(dev, 0x04C9, 0x0080);
		पूर्ण
		b43legacy_phy_ग_लिखो(dev, 0x042B, b43legacy_phy_पढ़ो(dev,
				    0x042B) | 0x800);

		क्रम (i = 0; i < 64; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x4000 + i, i);
		क्रम (i = 0; i < B43legacy_ILT_NOISEG2_SIZE; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x1800 + i,
					    b43legacy_ilt_noiseg2[i]);
	पूर्ण

	अगर (phy->rev <= 2)
		क्रम (i = 0; i < B43legacy_ILT_NOISESCALEG_SIZE; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x1400 + i,
					    b43legacy_ilt_noisescaleg1[i]);
	अन्यथा अगर ((phy->rev >= 7) && (b43legacy_phy_पढ़ो(dev, 0x0449) & 0x0200))
		क्रम (i = 0; i < B43legacy_ILT_NOISESCALEG_SIZE; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x1400 + i,
					    b43legacy_ilt_noisescaleg3[i]);
	अन्यथा
		क्रम (i = 0; i < B43legacy_ILT_NOISESCALEG_SIZE; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x1400 + i,
					    b43legacy_ilt_noisescaleg2[i]);

	अगर (phy->rev == 2)
		क्रम (i = 0; i < B43legacy_ILT_SIGMASQR_SIZE; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x5000 + i,
					    b43legacy_ilt_sigmasqr1[i]);
	अन्यथा अगर ((phy->rev > 2) && (phy->rev <= 8))
		क्रम (i = 0; i < B43legacy_ILT_SIGMASQR_SIZE; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x5000 + i,
					    b43legacy_ilt_sigmasqr2[i]);

	अगर (phy->rev == 1) अणु
		क्रम (i = 0; i < B43legacy_ILT_RETARD_SIZE; i++)
			b43legacy_ilt_ग_लिखो32(dev, 0x2400 + i,
					      b43legacy_ilt_retard[i]);
		क्रम (i = 4; i < 20; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x5400 + i, 0x0020);
		b43legacy_phy_agcsetup(dev);

		अगर (is_bcm_board_venकरोr(dev) &&
		    (dev->dev->bus->boardinfo.type == 0x0416) &&
		    (dev->dev->bus->sprom.board_rev == 0x0017))
			वापस;

		b43legacy_ilt_ग_लिखो(dev, 0x5001, 0x0002);
		b43legacy_ilt_ग_लिखो(dev, 0x5002, 0x0001);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i <= 0x20; i++)
			b43legacy_ilt_ग_लिखो(dev, 0x1000 + i, 0x0820);
		b43legacy_phy_agcsetup(dev);
		b43legacy_phy_पढ़ो(dev, 0x0400); /* dummy पढ़ो */
		b43legacy_phy_ग_लिखो(dev, 0x0403, 0x1000);
		b43legacy_ilt_ग_लिखो(dev, 0x3C02, 0x000F);
		b43legacy_ilt_ग_लिखो(dev, 0x3C03, 0x0014);

		अगर (is_bcm_board_venकरोr(dev) &&
		    (dev->dev->bus->boardinfo.type == 0x0416) &&
		    (dev->dev->bus->sprom.board_rev == 0x0017))
			वापस;

		b43legacy_ilt_ग_लिखो(dev, 0x0401, 0x0002);
		b43legacy_ilt_ग_लिखो(dev, 0x0402, 0x0001);
	पूर्ण
पूर्ण

/* Initialize the APHY portion of a GPHY. */
अटल व्योम b43legacy_phy_inita(काष्ठा b43legacy_wldev *dev)
अणु

	might_sleep();

	b43legacy_phy_setupg(dev);
	अगर (dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_PACTRL)
		b43legacy_phy_ग_लिखो(dev, 0x046E, 0x03CF);
पूर्ण

अटल व्योम b43legacy_phy_initb2(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 offset;
	पूर्णांक val;

	b43legacy_ग_लिखो16(dev, 0x03EC, 0x3F22);
	b43legacy_phy_ग_लिखो(dev, 0x0020, 0x301C);
	b43legacy_phy_ग_लिखो(dev, 0x0026, 0x0000);
	b43legacy_phy_ग_लिखो(dev, 0x0030, 0x00C6);
	b43legacy_phy_ग_लिखो(dev, 0x0088, 0x3E00);
	val = 0x3C3D;
	क्रम (offset = 0x0089; offset < 0x00A7; offset++) अणु
		b43legacy_phy_ग_लिखो(dev, offset, val);
		val -= 0x0202;
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x03E4, 0x3000);
	b43legacy_radio_selectchannel(dev, phy->channel, 0);
	अगर (phy->radio_ver != 0x2050) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0075, 0x0080);
		b43legacy_radio_ग_लिखो16(dev, 0x0079, 0x0081);
	पूर्ण
	b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0020);
	b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0023);
	अगर (phy->radio_ver == 0x2050) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0020);
		b43legacy_radio_ग_लिखो16(dev, 0x005A, 0x0070);
		b43legacy_radio_ग_लिखो16(dev, 0x005B, 0x007B);
		b43legacy_radio_ग_लिखो16(dev, 0x005C, 0x00B0);
		b43legacy_radio_ग_लिखो16(dev, 0x007A, 0x000F);
		b43legacy_phy_ग_लिखो(dev, 0x0038, 0x0677);
		b43legacy_radio_init2050(dev);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0014, 0x0080);
	b43legacy_phy_ग_लिखो(dev, 0x0032, 0x00CA);
	b43legacy_phy_ग_लिखो(dev, 0x0032, 0x00CC);
	b43legacy_phy_ग_लिखो(dev, 0x0035, 0x07C2);
	b43legacy_phy_lo_b_measure(dev);
	b43legacy_phy_ग_लिखो(dev, 0x0026, 0xCC00);
	अगर (phy->radio_ver != 0x2050)
		b43legacy_phy_ग_लिखो(dev, 0x0026, 0xCE00);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT, 0x1000);
	b43legacy_phy_ग_लिखो(dev, 0x002A, 0x88A3);
	अगर (phy->radio_ver != 0x2050)
		b43legacy_phy_ग_लिखो(dev, 0x002A, 0x88C2);
	b43legacy_radio_set_txघातer_bg(dev, 0xFFFF, 0xFFFF, 0xFFFF);
	b43legacy_phy_init_pctl(dev);
पूर्ण

अटल व्योम b43legacy_phy_initb4(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 offset;
	u16 val;

	b43legacy_ग_लिखो16(dev, 0x03EC, 0x3F22);
	b43legacy_phy_ग_लिखो(dev, 0x0020, 0x301C);
	b43legacy_phy_ग_लिखो(dev, 0x0026, 0x0000);
	b43legacy_phy_ग_लिखो(dev, 0x0030, 0x00C6);
	b43legacy_phy_ग_लिखो(dev, 0x0088, 0x3E00);
	val = 0x3C3D;
	क्रम (offset = 0x0089; offset < 0x00A7; offset++) अणु
		b43legacy_phy_ग_लिखो(dev, offset, val);
		val -= 0x0202;
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x03E4, 0x3000);
	b43legacy_radio_selectchannel(dev, phy->channel, 0);
	अगर (phy->radio_ver != 0x2050) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0075, 0x0080);
		b43legacy_radio_ग_लिखो16(dev, 0x0079, 0x0081);
	पूर्ण
	b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0020);
	b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0023);
	अगर (phy->radio_ver == 0x2050) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0020);
		b43legacy_radio_ग_लिखो16(dev, 0x005A, 0x0070);
		b43legacy_radio_ग_लिखो16(dev, 0x005B, 0x007B);
		b43legacy_radio_ग_लिखो16(dev, 0x005C, 0x00B0);
		b43legacy_radio_ग_लिखो16(dev, 0x007A, 0x000F);
		b43legacy_phy_ग_लिखो(dev, 0x0038, 0x0677);
		b43legacy_radio_init2050(dev);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0014, 0x0080);
	b43legacy_phy_ग_लिखो(dev, 0x0032, 0x00CA);
	अगर (phy->radio_ver == 0x2050)
		b43legacy_phy_ग_लिखो(dev, 0x0032, 0x00E0);
	b43legacy_phy_ग_लिखो(dev, 0x0035, 0x07C2);

	b43legacy_phy_lo_b_measure(dev);

	b43legacy_phy_ग_लिखो(dev, 0x0026, 0xCC00);
	अगर (phy->radio_ver == 0x2050)
		b43legacy_phy_ग_लिखो(dev, 0x0026, 0xCE00);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT, 0x1100);
	b43legacy_phy_ग_लिखो(dev, 0x002A, 0x88A3);
	अगर (phy->radio_ver == 0x2050)
		b43legacy_phy_ग_लिखो(dev, 0x002A, 0x88C2);
	b43legacy_radio_set_txघातer_bg(dev, 0xFFFF, 0xFFFF, 0xFFFF);
	अगर (dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_RSSI) अणु
		b43legacy_calc_nrssi_slope(dev);
		b43legacy_calc_nrssi_threshold(dev);
	पूर्ण
	b43legacy_phy_init_pctl(dev);
पूर्ण

अटल व्योम b43legacy_phy_initb5(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 offset;
	u16 value;
	u8 old_channel;

	अगर (phy->analog == 1)
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					| 0x0050);
	अगर (!is_bcm_board_venकरोr(dev) &&
	    (dev->dev->bus->boardinfo.type != 0x0416)) अणु
		value = 0x2120;
		क्रम (offset = 0x00A8 ; offset < 0x00C7; offset++) अणु
			b43legacy_phy_ग_लिखो(dev, offset, value);
			value += 0x0202;
		पूर्ण
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0035,
			    (b43legacy_phy_पढ़ो(dev, 0x0035) & 0xF0FF)
			    | 0x0700);
	अगर (phy->radio_ver == 0x2050)
		b43legacy_phy_ग_लिखो(dev, 0x0038, 0x0667);

	अगर (phy->gmode) अणु
		अगर (phy->radio_ver == 0x2050) अणु
			b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					| 0x0020);
			b43legacy_radio_ग_लिखो16(dev, 0x0051,
					b43legacy_radio_पढ़ो16(dev, 0x0051)
					| 0x0004);
		पूर्ण
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_PHY_RADIO, 0x0000);

		b43legacy_phy_ग_लिखो(dev, 0x0802, b43legacy_phy_पढ़ो(dev, 0x0802)
				    | 0x0100);
		b43legacy_phy_ग_लिखो(dev, 0x042B, b43legacy_phy_पढ़ो(dev, 0x042B)
				    | 0x2000);

		b43legacy_phy_ग_लिखो(dev, 0x001C, 0x186A);

		b43legacy_phy_ग_लिखो(dev, 0x0013, (b43legacy_phy_पढ़ो(dev,
				    0x0013) & 0x00FF) | 0x1900);
		b43legacy_phy_ग_लिखो(dev, 0x0035, (b43legacy_phy_पढ़ो(dev,
				    0x0035) & 0xFFC0) | 0x0064);
		b43legacy_phy_ग_लिखो(dev, 0x005D, (b43legacy_phy_पढ़ो(dev,
				    0x005D) & 0xFF80) | 0x000A);
		b43legacy_phy_ग_लिखो(dev, 0x5B, 0x0000);
		b43legacy_phy_ग_लिखो(dev, 0x5C, 0x0000);
	पूर्ण

	अगर (dev->bad_frames_preempt)
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_RADIO_BITFIELD,
				    b43legacy_phy_पढ़ो(dev,
				    B43legacy_PHY_RADIO_BITFIELD) | (1 << 12));

	अगर (phy->analog == 1) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0026, 0xCE00);
		b43legacy_phy_ग_लिखो(dev, 0x0021, 0x3763);
		b43legacy_phy_ग_लिखो(dev, 0x0022, 0x1BC3);
		b43legacy_phy_ग_लिखो(dev, 0x0023, 0x06F9);
		b43legacy_phy_ग_लिखो(dev, 0x0024, 0x037E);
	पूर्ण अन्यथा
		b43legacy_phy_ग_लिखो(dev, 0x0026, 0xCC00);
	b43legacy_phy_ग_लिखो(dev, 0x0030, 0x00C6);
	b43legacy_ग_लिखो16(dev, 0x03EC, 0x3F22);

	अगर (phy->analog == 1)
		b43legacy_phy_ग_लिखो(dev, 0x0020, 0x3E1C);
	अन्यथा
		b43legacy_phy_ग_लिखो(dev, 0x0020, 0x301C);

	अगर (phy->analog == 0)
		b43legacy_ग_लिखो16(dev, 0x03E4, 0x3000);

	old_channel = (phy->channel == 0xFF) ? 1 : phy->channel;
	/* Force to channel 7, even अगर not supported. */
	b43legacy_radio_selectchannel(dev, 7, 0);

	अगर (phy->radio_ver != 0x2050) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0075, 0x0080);
		b43legacy_radio_ग_लिखो16(dev, 0x0079, 0x0081);
	पूर्ण

	b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0020);
	b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0023);

	अगर (phy->radio_ver == 0x2050) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0020);
		b43legacy_radio_ग_लिखो16(dev, 0x005A, 0x0070);
	पूर्ण

	b43legacy_radio_ग_लिखो16(dev, 0x005B, 0x007B);
	b43legacy_radio_ग_लिखो16(dev, 0x005C, 0x00B0);

	b43legacy_radio_ग_लिखो16(dev, 0x007A, b43legacy_radio_पढ़ो16(dev,
				0x007A) | 0x0007);

	b43legacy_radio_selectchannel(dev, old_channel, 0);

	b43legacy_phy_ग_लिखो(dev, 0x0014, 0x0080);
	b43legacy_phy_ग_लिखो(dev, 0x0032, 0x00CA);
	b43legacy_phy_ग_लिखो(dev, 0x002A, 0x88A3);

	b43legacy_radio_set_txघातer_bg(dev, 0xFFFF, 0xFFFF, 0xFFFF);

	अगर (phy->radio_ver == 0x2050)
		b43legacy_radio_ग_लिखो16(dev, 0x005D, 0x000D);

	b43legacy_ग_लिखो16(dev, 0x03E4, (b43legacy_पढ़ो16(dev, 0x03E4) &
			  0xFFC0) | 0x0004);
पूर्ण

अटल व्योम b43legacy_phy_initb6(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 offset;
	u16 val;
	u8 old_channel;

	b43legacy_phy_ग_लिखो(dev, 0x003E, 0x817A);
	b43legacy_radio_ग_लिखो16(dev, 0x007A,
				(b43legacy_radio_पढ़ो16(dev, 0x007A) | 0x0058));
	अगर (phy->radio_rev == 4 ||
	     phy->radio_rev == 5) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0051, 0x0037);
		b43legacy_radio_ग_लिखो16(dev, 0x0052, 0x0070);
		b43legacy_radio_ग_लिखो16(dev, 0x0053, 0x00B3);
		b43legacy_radio_ग_लिखो16(dev, 0x0054, 0x009B);
		b43legacy_radio_ग_लिखो16(dev, 0x005A, 0x0088);
		b43legacy_radio_ग_लिखो16(dev, 0x005B, 0x0088);
		b43legacy_radio_ग_लिखो16(dev, 0x005D, 0x0088);
		b43legacy_radio_ग_लिखो16(dev, 0x005E, 0x0088);
		b43legacy_radio_ग_लिखो16(dev, 0x007D, 0x0088);
		b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED,
				      B43legacy_UCODEFLAGS_OFFSET,
				      (b43legacy_shm_पढ़ो32(dev,
				      B43legacy_SHM_SHARED,
				      B43legacy_UCODEFLAGS_OFFSET)
				      | 0x00000200));
	पूर्ण
	अगर (phy->radio_rev == 8) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0051, 0x0000);
		b43legacy_radio_ग_लिखो16(dev, 0x0052, 0x0040);
		b43legacy_radio_ग_लिखो16(dev, 0x0053, 0x00B7);
		b43legacy_radio_ग_लिखो16(dev, 0x0054, 0x0098);
		b43legacy_radio_ग_लिखो16(dev, 0x005A, 0x0088);
		b43legacy_radio_ग_लिखो16(dev, 0x005B, 0x006B);
		b43legacy_radio_ग_लिखो16(dev, 0x005C, 0x000F);
		अगर (dev->dev->bus->sprom.boardflags_lo & 0x8000) अणु
			b43legacy_radio_ग_लिखो16(dev, 0x005D, 0x00FA);
			b43legacy_radio_ग_लिखो16(dev, 0x005E, 0x00D8);
		पूर्ण अन्यथा अणु
			b43legacy_radio_ग_लिखो16(dev, 0x005D, 0x00F5);
			b43legacy_radio_ग_लिखो16(dev, 0x005E, 0x00B8);
		पूर्ण
		b43legacy_radio_ग_लिखो16(dev, 0x0073, 0x0003);
		b43legacy_radio_ग_लिखो16(dev, 0x007D, 0x00A8);
		b43legacy_radio_ग_लिखो16(dev, 0x007C, 0x0001);
		b43legacy_radio_ग_लिखो16(dev, 0x007E, 0x0008);
	पूर्ण
	val = 0x1E1F;
	क्रम (offset = 0x0088; offset < 0x0098; offset++) अणु
		b43legacy_phy_ग_लिखो(dev, offset, val);
		val -= 0x0202;
	पूर्ण
	val = 0x3E3F;
	क्रम (offset = 0x0098; offset < 0x00A8; offset++) अणु
		b43legacy_phy_ग_लिखो(dev, offset, val);
		val -= 0x0202;
	पूर्ण
	val = 0x2120;
	क्रम (offset = 0x00A8; offset < 0x00C8; offset++) अणु
		b43legacy_phy_ग_लिखो(dev, offset, (val & 0x3F3F));
		val += 0x0202;
	पूर्ण
	अगर (phy->type == B43legacy_PHYTYPE_G) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A) |
					0x0020);
		b43legacy_radio_ग_लिखो16(dev, 0x0051,
					b43legacy_radio_पढ़ो16(dev, 0x0051) |
					0x0004);
		b43legacy_phy_ग_लिखो(dev, 0x0802,
				    b43legacy_phy_पढ़ो(dev, 0x0802) | 0x0100);
		b43legacy_phy_ग_लिखो(dev, 0x042B,
				    b43legacy_phy_पढ़ो(dev, 0x042B) | 0x2000);
		b43legacy_phy_ग_लिखो(dev, 0x5B, 0x0000);
		b43legacy_phy_ग_लिखो(dev, 0x5C, 0x0000);
	पूर्ण

	old_channel = phy->channel;
	अगर (old_channel >= 8)
		b43legacy_radio_selectchannel(dev, 1, 0);
	अन्यथा
		b43legacy_radio_selectchannel(dev, 13, 0);

	b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0020);
	b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0023);
	udelay(40);
	अगर (phy->radio_rev < 6 || phy->radio_rev == 8) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x007C,
					(b43legacy_radio_पढ़ो16(dev, 0x007C)
					| 0x0002));
		b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0020);
	पूर्ण
	अगर (phy->radio_rev <= 2) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0050, 0x0020);
		b43legacy_radio_ग_लिखो16(dev, 0x005A, 0x0070);
		b43legacy_radio_ग_लिखो16(dev, 0x005B, 0x007B);
		b43legacy_radio_ग_लिखो16(dev, 0x005C, 0x00B0);
	पूर्ण
	b43legacy_radio_ग_लिखो16(dev, 0x007A,
				(b43legacy_radio_पढ़ो16(dev,
				0x007A) & 0x00F8) | 0x0007);

	b43legacy_radio_selectchannel(dev, old_channel, 0);

	b43legacy_phy_ग_लिखो(dev, 0x0014, 0x0200);
	अगर (phy->radio_rev >= 6)
		b43legacy_phy_ग_लिखो(dev, 0x002A, 0x88C2);
	अन्यथा
		b43legacy_phy_ग_लिखो(dev, 0x002A, 0x8AC0);
	b43legacy_phy_ग_लिखो(dev, 0x0038, 0x0668);
	b43legacy_radio_set_txघातer_bg(dev, 0xFFFF, 0xFFFF, 0xFFFF);
	अगर (phy->radio_rev == 4 || phy->radio_rev == 5)
		b43legacy_phy_ग_लिखो(dev, 0x005D, (b43legacy_phy_पढ़ो(dev,
				    0x005D) & 0xFF80) | 0x0003);
	अगर (phy->radio_rev <= 2)
		b43legacy_radio_ग_लिखो16(dev, 0x005D, 0x000D);

	अगर (phy->analog == 4) अणु
		b43legacy_ग_लिखो16(dev, 0x03E4, 0x0009);
		b43legacy_phy_ग_लिखो(dev, 0x61, b43legacy_phy_पढ़ो(dev, 0x61)
				    & 0xFFF);
	पूर्ण अन्यथा
		b43legacy_phy_ग_लिखो(dev, 0x0002, (b43legacy_phy_पढ़ो(dev,
				    0x0002) & 0xFFC0) | 0x0004);
	अगर (phy->type == B43legacy_PHYTYPE_G)
		b43legacy_ग_लिखो16(dev, 0x03E6, 0x0);
	अगर (phy->type == B43legacy_PHYTYPE_B) अणु
		b43legacy_ग_लिखो16(dev, 0x03E6, 0x8140);
		b43legacy_phy_ग_लिखो(dev, 0x0016, 0x0410);
		b43legacy_phy_ग_लिखो(dev, 0x0017, 0x0820);
		b43legacy_phy_ग_लिखो(dev, 0x0062, 0x0007);
		b43legacy_radio_init2050(dev);
		b43legacy_phy_lo_g_measure(dev);
		अगर (dev->dev->bus->sprom.boardflags_lo &
		    B43legacy_BFL_RSSI) अणु
			b43legacy_calc_nrssi_slope(dev);
			b43legacy_calc_nrssi_threshold(dev);
		पूर्ण
		b43legacy_phy_init_pctl(dev);
	पूर्ण
पूर्ण

अटल व्योम b43legacy_calc_loopback_gain(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 backup_phy[15] = अणु0पूर्ण;
	u16 backup_radio[3];
	u16 backup_bband;
	u16 i;
	u16 loop1_cnt;
	u16 loop1_करोne;
	u16 loop1_omitted;
	u16 loop2_करोne;

	backup_phy[0] = b43legacy_phy_पढ़ो(dev, 0x0429);
	backup_phy[1] = b43legacy_phy_पढ़ो(dev, 0x0001);
	backup_phy[2] = b43legacy_phy_पढ़ो(dev, 0x0811);
	backup_phy[3] = b43legacy_phy_पढ़ो(dev, 0x0812);
	अगर (phy->rev != 1) अणु
		backup_phy[4] = b43legacy_phy_पढ़ो(dev, 0x0814);
		backup_phy[5] = b43legacy_phy_पढ़ो(dev, 0x0815);
	पूर्ण
	backup_phy[6] = b43legacy_phy_पढ़ो(dev, 0x005A);
	backup_phy[7] = b43legacy_phy_पढ़ो(dev, 0x0059);
	backup_phy[8] = b43legacy_phy_पढ़ो(dev, 0x0058);
	backup_phy[9] = b43legacy_phy_पढ़ो(dev, 0x000A);
	backup_phy[10] = b43legacy_phy_पढ़ो(dev, 0x0003);
	backup_phy[11] = b43legacy_phy_पढ़ो(dev, 0x080F);
	backup_phy[12] = b43legacy_phy_पढ़ो(dev, 0x0810);
	backup_phy[13] = b43legacy_phy_पढ़ो(dev, 0x002B);
	backup_phy[14] = b43legacy_phy_पढ़ो(dev, 0x0015);
	b43legacy_phy_पढ़ो(dev, 0x002D); /* dummy पढ़ो */
	backup_bband = phy->bbatt;
	backup_radio[0] = b43legacy_radio_पढ़ो16(dev, 0x0052);
	backup_radio[1] = b43legacy_radio_पढ़ो16(dev, 0x0043);
	backup_radio[2] = b43legacy_radio_पढ़ो16(dev, 0x007A);

	b43legacy_phy_ग_लिखो(dev, 0x0429,
			    b43legacy_phy_पढ़ो(dev, 0x0429) & 0x3FFF);
	b43legacy_phy_ग_लिखो(dev, 0x0001,
			    b43legacy_phy_पढ़ो(dev, 0x0001) & 0x8000);
	b43legacy_phy_ग_लिखो(dev, 0x0811,
			    b43legacy_phy_पढ़ो(dev, 0x0811) | 0x0002);
	b43legacy_phy_ग_लिखो(dev, 0x0812,
			    b43legacy_phy_पढ़ो(dev, 0x0812) & 0xFFFD);
	b43legacy_phy_ग_लिखो(dev, 0x0811,
			    b43legacy_phy_पढ़ो(dev, 0x0811) | 0x0001);
	b43legacy_phy_ग_लिखो(dev, 0x0812,
			    b43legacy_phy_पढ़ो(dev, 0x0812) & 0xFFFE);
	अगर (phy->rev != 1) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0814,
				    b43legacy_phy_पढ़ो(dev, 0x0814) | 0x0001);
		b43legacy_phy_ग_लिखो(dev, 0x0815,
				    b43legacy_phy_पढ़ो(dev, 0x0815) & 0xFFFE);
		b43legacy_phy_ग_लिखो(dev, 0x0814,
				    b43legacy_phy_पढ़ो(dev, 0x0814) | 0x0002);
		b43legacy_phy_ग_लिखो(dev, 0x0815,
				    b43legacy_phy_पढ़ो(dev, 0x0815) & 0xFFFD);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0811, b43legacy_phy_पढ़ो(dev, 0x0811) |
			    0x000C);
	b43legacy_phy_ग_लिखो(dev, 0x0812, b43legacy_phy_पढ़ो(dev, 0x0812) |
			    0x000C);

	b43legacy_phy_ग_लिखो(dev, 0x0811, (b43legacy_phy_पढ़ो(dev, 0x0811)
			    & 0xFFCF) | 0x0030);
	b43legacy_phy_ग_लिखो(dev, 0x0812, (b43legacy_phy_पढ़ो(dev, 0x0812)
			    & 0xFFCF) | 0x0010);

	b43legacy_phy_ग_लिखो(dev, 0x005A, 0x0780);
	b43legacy_phy_ग_लिखो(dev, 0x0059, 0xC810);
	b43legacy_phy_ग_लिखो(dev, 0x0058, 0x000D);
	अगर (phy->analog == 0)
		b43legacy_phy_ग_लिखो(dev, 0x0003, 0x0122);
	अन्यथा
		b43legacy_phy_ग_लिखो(dev, 0x000A,
				    b43legacy_phy_पढ़ो(dev, 0x000A)
				    | 0x2000);
	अगर (phy->rev != 1) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0814,
				    b43legacy_phy_पढ़ो(dev, 0x0814) | 0x0004);
		b43legacy_phy_ग_लिखो(dev, 0x0815,
				    b43legacy_phy_पढ़ो(dev, 0x0815) & 0xFFFB);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0003,
			    (b43legacy_phy_पढ़ो(dev, 0x0003)
			     & 0xFF9F) | 0x0040);
	अगर (phy->radio_ver == 0x2050 && phy->radio_rev == 2) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0052, 0x0000);
		b43legacy_radio_ग_लिखो16(dev, 0x0043,
					(b43legacy_radio_पढ़ो16(dev, 0x0043)
					 & 0xFFF0) | 0x0009);
		loop1_cnt = 9;
	पूर्ण अन्यथा अगर (phy->radio_rev == 8) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0043, 0x000F);
		loop1_cnt = 15;
	पूर्ण अन्यथा
		loop1_cnt = 0;

	b43legacy_phy_set_baseband_attenuation(dev, 11);

	अगर (phy->rev >= 3)
		b43legacy_phy_ग_लिखो(dev, 0x080F, 0xC020);
	अन्यथा
		b43legacy_phy_ग_लिखो(dev, 0x080F, 0x8020);
	b43legacy_phy_ग_लिखो(dev, 0x0810, 0x0000);

	b43legacy_phy_ग_लिखो(dev, 0x002B,
			    (b43legacy_phy_पढ़ो(dev, 0x002B)
			     & 0xFFC0) | 0x0001);
	b43legacy_phy_ग_लिखो(dev, 0x002B,
			    (b43legacy_phy_पढ़ो(dev, 0x002B)
			     & 0xC0FF) | 0x0800);
	b43legacy_phy_ग_लिखो(dev, 0x0811,
			    b43legacy_phy_पढ़ो(dev, 0x0811) | 0x0100);
	b43legacy_phy_ग_लिखो(dev, 0x0812,
			    b43legacy_phy_पढ़ो(dev, 0x0812) & 0xCFFF);
	अगर (dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_EXTLNA) अणु
		अगर (phy->rev >= 7) अणु
			b43legacy_phy_ग_लिखो(dev, 0x0811,
					    b43legacy_phy_पढ़ो(dev, 0x0811)
					    | 0x0800);
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    b43legacy_phy_पढ़ो(dev, 0x0812)
					    | 0x8000);
		पूर्ण
	पूर्ण
	b43legacy_radio_ग_लिखो16(dev, 0x007A,
				b43legacy_radio_पढ़ो16(dev, 0x007A)
				& 0x00F7);

	क्रम (i = 0; i < loop1_cnt; i++) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0043, loop1_cnt);
		b43legacy_phy_ग_लिखो(dev, 0x0812,
				    (b43legacy_phy_पढ़ो(dev, 0x0812)
				     & 0xF0FF) | (i << 8));
		b43legacy_phy_ग_लिखो(dev, 0x0015,
				    (b43legacy_phy_पढ़ो(dev, 0x0015)
				     & 0x0FFF) | 0xA000);
		b43legacy_phy_ग_लिखो(dev, 0x0015,
				    (b43legacy_phy_पढ़ो(dev, 0x0015)
				     & 0x0FFF) | 0xF000);
		udelay(20);
		अगर (b43legacy_phy_पढ़ो(dev, 0x002D) >= 0x0DFC)
			अवरोध;
	पूर्ण
	loop1_करोne = i;
	loop1_omitted = loop1_cnt - loop1_करोne;

	loop2_करोne = 0;
	अगर (loop1_करोne >= 8) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0812,
				    b43legacy_phy_पढ़ो(dev, 0x0812)
				    | 0x0030);
		क्रम (i = loop1_करोne - 8; i < 16; i++) अणु
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    (b43legacy_phy_पढ़ो(dev, 0x0812)
					     & 0xF0FF) | (i << 8));
			b43legacy_phy_ग_लिखो(dev, 0x0015,
					    (b43legacy_phy_पढ़ो(dev, 0x0015)
					     & 0x0FFF) | 0xA000);
			b43legacy_phy_ग_लिखो(dev, 0x0015,
					    (b43legacy_phy_पढ़ो(dev, 0x0015)
					     & 0x0FFF) | 0xF000);
			udelay(20);
			अगर (b43legacy_phy_पढ़ो(dev, 0x002D) >= 0x0DFC)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (phy->rev != 1) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0814, backup_phy[4]);
		b43legacy_phy_ग_लिखो(dev, 0x0815, backup_phy[5]);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x005A, backup_phy[6]);
	b43legacy_phy_ग_लिखो(dev, 0x0059, backup_phy[7]);
	b43legacy_phy_ग_लिखो(dev, 0x0058, backup_phy[8]);
	b43legacy_phy_ग_लिखो(dev, 0x000A, backup_phy[9]);
	b43legacy_phy_ग_लिखो(dev, 0x0003, backup_phy[10]);
	b43legacy_phy_ग_लिखो(dev, 0x080F, backup_phy[11]);
	b43legacy_phy_ग_लिखो(dev, 0x0810, backup_phy[12]);
	b43legacy_phy_ग_लिखो(dev, 0x002B, backup_phy[13]);
	b43legacy_phy_ग_लिखो(dev, 0x0015, backup_phy[14]);

	b43legacy_phy_set_baseband_attenuation(dev, backup_bband);

	b43legacy_radio_ग_लिखो16(dev, 0x0052, backup_radio[0]);
	b43legacy_radio_ग_लिखो16(dev, 0x0043, backup_radio[1]);
	b43legacy_radio_ग_लिखो16(dev, 0x007A, backup_radio[2]);

	b43legacy_phy_ग_लिखो(dev, 0x0811, backup_phy[2] | 0x0003);
	udelay(10);
	b43legacy_phy_ग_लिखो(dev, 0x0811, backup_phy[2]);
	b43legacy_phy_ग_लिखो(dev, 0x0812, backup_phy[3]);
	b43legacy_phy_ग_लिखो(dev, 0x0429, backup_phy[0]);
	b43legacy_phy_ग_लिखो(dev, 0x0001, backup_phy[1]);

	phy->loopback_gain[0] = ((loop1_करोne * 6) - (loop1_omitted * 4)) - 11;
	phy->loopback_gain[1] = (24 - (3 * loop2_करोne)) * 2;
पूर्ण

अटल व्योम b43legacy_phy_initg(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 पंचांगp;

	अगर (phy->rev == 1)
		b43legacy_phy_initb5(dev);
	अन्यथा
		b43legacy_phy_initb6(dev);
	अगर (phy->rev >= 2 && phy->gmode)
		b43legacy_phy_inita(dev);

	अगर (phy->rev >= 2) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0814, 0x0000);
		b43legacy_phy_ग_लिखो(dev, 0x0815, 0x0000);
	पूर्ण
	अगर (phy->rev == 2) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0811, 0x0000);
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0x00C0);
	पूर्ण
	अगर (phy->rev > 5) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0811, 0x0400);
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0x00C0);
	पूर्ण
	अगर (phy->gmode) अणु
		पंचांगp = b43legacy_phy_पढ़ो(dev, 0x0400) & 0xFF;
		अगर (पंचांगp == 3) अणु
			b43legacy_phy_ग_लिखो(dev, 0x04C2, 0x1816);
			b43legacy_phy_ग_लिखो(dev, 0x04C3, 0x8606);
		पूर्ण
		अगर (पंचांगp == 4 || पंचांगp == 5) अणु
			b43legacy_phy_ग_लिखो(dev, 0x04C2, 0x1816);
			b43legacy_phy_ग_लिखो(dev, 0x04C3, 0x8006);
			b43legacy_phy_ग_लिखो(dev, 0x04CC,
					    (b43legacy_phy_पढ़ो(dev,
					     0x04CC) & 0x00FF) |
					     0x1F00);
		पूर्ण
		अगर (phy->rev >= 2)
			b43legacy_phy_ग_लिखो(dev, 0x047E, 0x0078);
	पूर्ण
	अगर (phy->radio_rev == 8) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0801, b43legacy_phy_पढ़ो(dev, 0x0801)
				    | 0x0080);
		b43legacy_phy_ग_लिखो(dev, 0x043E, b43legacy_phy_पढ़ो(dev, 0x043E)
				    | 0x0004);
	पूर्ण
	अगर (phy->rev >= 2 && phy->gmode)
		b43legacy_calc_loopback_gain(dev);
	अगर (phy->radio_rev != 8) अणु
		अगर (phy->initval == 0xFFFF)
			phy->initval = b43legacy_radio_init2050(dev);
		अन्यथा
			b43legacy_radio_ग_लिखो16(dev, 0x0078, phy->initval);
	पूर्ण
	अगर (phy->txctl2 == 0xFFFF)
		b43legacy_phy_lo_g_measure(dev);
	अन्यथा अणु
		अगर (phy->radio_ver == 0x2050 && phy->radio_rev == 8)
			b43legacy_radio_ग_लिखो16(dev, 0x0052,
						(phy->txctl1 << 4) |
						phy->txctl2);
		अन्यथा
			b43legacy_radio_ग_लिखो16(dev, 0x0052,
						(b43legacy_radio_पढ़ो16(dev,
						 0x0052) & 0xFFF0) |
						 phy->txctl1);
		अगर (phy->rev >= 6)
			b43legacy_phy_ग_लिखो(dev, 0x0036,
					    (b43legacy_phy_पढ़ो(dev, 0x0036)
					     & 0x0FFF) | (phy->txctl2 << 12));
		अगर (dev->dev->bus->sprom.boardflags_lo &
		    B43legacy_BFL_PACTRL)
			b43legacy_phy_ग_लिखो(dev, 0x002E, 0x8075);
		अन्यथा
			b43legacy_phy_ग_लिखो(dev, 0x002E, 0x807F);
		अगर (phy->rev < 2)
			b43legacy_phy_ग_लिखो(dev, 0x002F, 0x0101);
		अन्यथा
			b43legacy_phy_ग_लिखो(dev, 0x002F, 0x0202);
	पूर्ण
	अगर (phy->gmode) अणु
		b43legacy_phy_lo_adjust(dev, 0);
		b43legacy_phy_ग_लिखो(dev, 0x080F, 0x8078);
	पूर्ण

	अगर (!(dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_RSSI)) अणु
		/* The specs state to update the NRSSI LT with
		 * the value 0x7FFFFFFF here. I think that is some weird
		 * compiler optimization in the original driver.
		 * Essentially, what we करो here is resetting all NRSSI LT
		 * entries to -32 (see the clamp_val() in nrssi_hw_update())
		 */
		b43legacy_nrssi_hw_update(dev, 0xFFFF);
		b43legacy_calc_nrssi_threshold(dev);
	पूर्ण अन्यथा अगर (phy->gmode || phy->rev >= 2) अणु
		अगर (phy->nrssi[0] == -1000) अणु
			B43legacy_WARN_ON(phy->nrssi[1] != -1000);
			b43legacy_calc_nrssi_slope(dev);
		पूर्ण अन्यथा अणु
			B43legacy_WARN_ON(phy->nrssi[1] == -1000);
			b43legacy_calc_nrssi_threshold(dev);
		पूर्ण
	पूर्ण
	अगर (phy->radio_rev == 8)
		b43legacy_phy_ग_लिखो(dev, 0x0805, 0x3230);
	b43legacy_phy_init_pctl(dev);
	अगर (dev->dev->bus->chip_id == 0x4306
	    && dev->dev->bus->chip_package == 2) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0429,
				    b43legacy_phy_पढ़ो(dev, 0x0429) & 0xBFFF);
		b43legacy_phy_ग_लिखो(dev, 0x04C3,
				    b43legacy_phy_पढ़ो(dev, 0x04C3) & 0x7FFF);
	पूर्ण
पूर्ण

अटल u16 b43legacy_phy_lo_b_r15_loop(काष्ठा b43legacy_wldev *dev)
अणु
	पूर्णांक i;
	u16 ret = 0;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	क्रम (i = 0; i < 10; i++) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xAFA0);
		udelay(1);
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xEFA0);
		udelay(10);
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xFFA0);
		udelay(40);
		ret += b43legacy_phy_पढ़ो(dev, 0x002C);
	पूर्ण
	local_irq_restore(flags);
	cond_resched();

	वापस ret;
पूर्ण

व्योम b43legacy_phy_lo_b_measure(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 regstack[12] = अणु 0 पूर्ण;
	u16 mls;
	u16 fval;
	पूर्णांक i;
	पूर्णांक j;

	regstack[0] = b43legacy_phy_पढ़ो(dev, 0x0015);
	regstack[1] = b43legacy_radio_पढ़ो16(dev, 0x0052) & 0xFFF0;

	अगर (phy->radio_ver == 0x2053) अणु
		regstack[2] = b43legacy_phy_पढ़ो(dev, 0x000A);
		regstack[3] = b43legacy_phy_पढ़ो(dev, 0x002A);
		regstack[4] = b43legacy_phy_पढ़ो(dev, 0x0035);
		regstack[5] = b43legacy_phy_पढ़ो(dev, 0x0003);
		regstack[6] = b43legacy_phy_पढ़ो(dev, 0x0001);
		regstack[7] = b43legacy_phy_पढ़ो(dev, 0x0030);

		regstack[8] = b43legacy_radio_पढ़ो16(dev, 0x0043);
		regstack[9] = b43legacy_radio_पढ़ो16(dev, 0x007A);
		regstack[10] = b43legacy_पढ़ो16(dev, 0x03EC);
		regstack[11] = b43legacy_radio_पढ़ो16(dev, 0x0052) & 0x00F0;

		b43legacy_phy_ग_लिखो(dev, 0x0030, 0x00FF);
		b43legacy_ग_लिखो16(dev, 0x03EC, 0x3F3F);
		b43legacy_phy_ग_लिखो(dev, 0x0035, regstack[4] & 0xFF7F);
		b43legacy_radio_ग_लिखो16(dev, 0x007A, regstack[9] & 0xFFF0);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0015, 0xB000);
	b43legacy_phy_ग_लिखो(dev, 0x002B, 0x0004);

	अगर (phy->radio_ver == 0x2053) अणु
		b43legacy_phy_ग_लिखो(dev, 0x002B, 0x0203);
		b43legacy_phy_ग_लिखो(dev, 0x002A, 0x08A3);
	पूर्ण

	phy->minlowsig[0] = 0xFFFF;

	क्रम (i = 0; i < 4; i++) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0052, regstack[1] | i);
		b43legacy_phy_lo_b_r15_loop(dev);
	पूर्ण
	क्रम (i = 0; i < 10; i++) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0052, regstack[1] | i);
		mls = b43legacy_phy_lo_b_r15_loop(dev) / 10;
		अगर (mls < phy->minlowsig[0]) अणु
			phy->minlowsig[0] = mls;
			phy->minlowsigpos[0] = i;
		पूर्ण
	पूर्ण
	b43legacy_radio_ग_लिखो16(dev, 0x0052, regstack[1]
				| phy->minlowsigpos[0]);

	phy->minlowsig[1] = 0xFFFF;

	क्रम (i = -4; i < 5; i += 2) अणु
		क्रम (j = -4; j < 5; j += 2) अणु
			अगर (j < 0)
				fval = (0x0100 * i) + j + 0x0100;
			अन्यथा
				fval = (0x0100 * i) + j;
			b43legacy_phy_ग_लिखो(dev, 0x002F, fval);
			mls = b43legacy_phy_lo_b_r15_loop(dev) / 10;
			अगर (mls < phy->minlowsig[1]) अणु
				phy->minlowsig[1] = mls;
				phy->minlowsigpos[1] = fval;
			पूर्ण
		पूर्ण
	पूर्ण
	phy->minlowsigpos[1] += 0x0101;

	b43legacy_phy_ग_लिखो(dev, 0x002F, phy->minlowsigpos[1]);
	अगर (phy->radio_ver == 0x2053) अणु
		b43legacy_phy_ग_लिखो(dev, 0x000A, regstack[2]);
		b43legacy_phy_ग_लिखो(dev, 0x002A, regstack[3]);
		b43legacy_phy_ग_लिखो(dev, 0x0035, regstack[4]);
		b43legacy_phy_ग_लिखो(dev, 0x0003, regstack[5]);
		b43legacy_phy_ग_लिखो(dev, 0x0001, regstack[6]);
		b43legacy_phy_ग_लिखो(dev, 0x0030, regstack[7]);

		b43legacy_radio_ग_लिखो16(dev, 0x0043, regstack[8]);
		b43legacy_radio_ग_लिखो16(dev, 0x007A, regstack[9]);

		b43legacy_radio_ग_लिखो16(dev, 0x0052,
					(b43legacy_radio_पढ़ो16(dev, 0x0052)
					& 0x000F) | regstack[11]);

		b43legacy_ग_लिखो16(dev, 0x03EC, regstack[10]);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0015, regstack[0]);
पूर्ण

अटल अंतरभूत
u16 b43legacy_phy_lo_g_deviation_subval(काष्ठा b43legacy_wldev *dev,
					u16 control)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 ret;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (phy->gmode) अणु
		b43legacy_phy_ग_लिखो(dev, 0x15, 0xE300);
		control <<= 8;
		b43legacy_phy_ग_लिखो(dev, 0x0812, control | 0x00B0);
		udelay(5);
		b43legacy_phy_ग_लिखो(dev, 0x0812, control | 0x00B2);
		udelay(2);
		b43legacy_phy_ग_लिखो(dev, 0x0812, control | 0x00B3);
		udelay(4);
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xF300);
		udelay(8);
	पूर्ण अन्यथा अणु
		b43legacy_phy_ग_लिखो(dev, 0x0015, control | 0xEFA0);
		udelay(2);
		b43legacy_phy_ग_लिखो(dev, 0x0015, control | 0xEFE0);
		udelay(4);
		b43legacy_phy_ग_लिखो(dev, 0x0015, control | 0xFFE0);
		udelay(8);
	पूर्ण
	ret = b43legacy_phy_पढ़ो(dev, 0x002D);
	local_irq_restore(flags);
	cond_resched();

	वापस ret;
पूर्ण

अटल u32 b43legacy_phy_lo_g_singledeviation(काष्ठा b43legacy_wldev *dev,
					      u16 control)
अणु
	पूर्णांक i;
	u32 ret = 0;

	क्रम (i = 0; i < 8; i++)
		ret += b43legacy_phy_lo_g_deviation_subval(dev, control);

	वापस ret;
पूर्ण

/* Write the LocalOscillator CONTROL */
अटल अंतरभूत
व्योम b43legacy_lo_ग_लिखो(काष्ठा b43legacy_wldev *dev,
			काष्ठा b43legacy_lopair *pair)
अणु
	u16 value;

	value = (u8)(pair->low);
	value |= ((u8)(pair->high)) << 8;

#अगर_घोषित CONFIG_B43LEGACY_DEBUG
	/* Sanity check. */
	अगर (pair->low < -8 || pair->low > 8 ||
	    pair->high < -8 || pair->high > 8) अणु
		b43legacydbg(dev->wl,
		       "WARNING: Writing invalid LOpair "
		       "(low: %d, high: %d)\n",
		       pair->low, pair->high);
		dump_stack();
	पूर्ण
#पूर्ण_अगर

	b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_LO_CONTROL, value);
पूर्ण

अटल अंतरभूत
काष्ठा b43legacy_lopair *b43legacy_find_lopair(काष्ठा b43legacy_wldev *dev,
					       u16 bbatt,
					       u16 rfatt,
					       u16 tx)
अणु
	अटल स्थिर u8 dict[10] = अणु 11, 10, 11, 12, 13, 12, 13, 12, 13, 12 पूर्ण;
	काष्ठा b43legacy_phy *phy = &dev->phy;

	अगर (bbatt > 6)
		bbatt = 6;
	B43legacy_WARN_ON(rfatt >= 10);

	अगर (tx == 3)
		वापस b43legacy_get_lopair(phy, rfatt, bbatt);
	वापस b43legacy_get_lopair(phy, dict[rfatt], bbatt);
पूर्ण

अटल अंतरभूत
काष्ठा b43legacy_lopair *b43legacy_current_lopair(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	वापस b43legacy_find_lopair(dev, phy->bbatt,
				     phy->rfatt, phy->txctl1);
पूर्ण

/* Adjust B/G LO */
व्योम b43legacy_phy_lo_adjust(काष्ठा b43legacy_wldev *dev, पूर्णांक fixed)
अणु
	काष्ठा b43legacy_lopair *pair;

	अगर (fixed) अणु
		/* Use fixed values. Only क्रम initialization. */
		pair = b43legacy_find_lopair(dev, 2, 3, 0);
	पूर्ण अन्यथा
		pair = b43legacy_current_lopair(dev);
	b43legacy_lo_ग_लिखो(dev, pair);
पूर्ण

अटल व्योम b43legacy_phy_lo_g_measure_txctl2(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 txctl2 = 0;
	u16 i;
	u32 smallest;
	u32 पंचांगp;

	b43legacy_radio_ग_लिखो16(dev, 0x0052, 0x0000);
	udelay(10);
	smallest = b43legacy_phy_lo_g_singledeviation(dev, 0);
	क्रम (i = 0; i < 16; i++) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0052, i);
		udelay(10);
		पंचांगp = b43legacy_phy_lo_g_singledeviation(dev, 0);
		अगर (पंचांगp < smallest) अणु
			smallest = पंचांगp;
			txctl2 = i;
		पूर्ण
	पूर्ण
	phy->txctl2 = txctl2;
पूर्ण

अटल
व्योम b43legacy_phy_lo_g_state(काष्ठा b43legacy_wldev *dev,
			      स्थिर काष्ठा b43legacy_lopair *in_pair,
			      काष्ठा b43legacy_lopair *out_pair,
			      u16 r27)
अणु
	अटल स्थिर काष्ठा b43legacy_lopair transitions[8] = अणु
		अणु .high =  1,  .low =  1, पूर्ण,
		अणु .high =  1,  .low =  0, पूर्ण,
		अणु .high =  1,  .low = -1, पूर्ण,
		अणु .high =  0,  .low = -1, पूर्ण,
		अणु .high = -1,  .low = -1, पूर्ण,
		अणु .high = -1,  .low =  0, पूर्ण,
		अणु .high = -1,  .low =  1, पूर्ण,
		अणु .high =  0,  .low =  1, पूर्ण,
	पूर्ण;
	काष्ठा b43legacy_lopair lowest_transition = अणु
		.high = in_pair->high,
		.low = in_pair->low,
	पूर्ण;
	काष्ठा b43legacy_lopair पंचांगp_pair;
	काष्ठा b43legacy_lopair transition;
	पूर्णांक i = 12;
	पूर्णांक state = 0;
	पूर्णांक found_lower;
	पूर्णांक j;
	पूर्णांक begin;
	पूर्णांक end;
	u32 lowest_deviation;
	u32 पंचांगp;

	/* Note that in_pair and out_pair can poपूर्णांक to the same pair.
	 * Be careful. */

	b43legacy_lo_ग_लिखो(dev, &lowest_transition);
	lowest_deviation = b43legacy_phy_lo_g_singledeviation(dev, r27);
	करो अणु
		found_lower = 0;
		B43legacy_WARN_ON(!(state >= 0 && state <= 8));
		अगर (state == 0) अणु
			begin = 1;
			end = 8;
		पूर्ण अन्यथा अगर (state % 2 == 0) अणु
			begin = state - 1;
			end = state + 1;
		पूर्ण अन्यथा अणु
			begin = state - 2;
			end = state + 2;
		पूर्ण
		अगर (begin < 1)
			begin += 8;
		अगर (end > 8)
			end -= 8;

		j = begin;
		पंचांगp_pair.high = lowest_transition.high;
		पंचांगp_pair.low = lowest_transition.low;
		जबतक (1) अणु
			B43legacy_WARN_ON(!(j >= 1 && j <= 8));
			transition.high = पंचांगp_pair.high +
					  transitions[j - 1].high;
			transition.low = पंचांगp_pair.low + transitions[j - 1].low;
			अगर ((असल(transition.low) < 9)
			     && (असल(transition.high) < 9)) अणु
				b43legacy_lo_ग_लिखो(dev, &transition);
				पंचांगp = b43legacy_phy_lo_g_singledeviation(dev,
								       r27);
				अगर (पंचांगp < lowest_deviation) अणु
					lowest_deviation = पंचांगp;
					state = j;
					found_lower = 1;

					lowest_transition.high =
								transition.high;
					lowest_transition.low = transition.low;
				पूर्ण
			पूर्ण
			अगर (j == end)
				अवरोध;
			अगर (j == 8)
				j = 1;
			अन्यथा
				j++;
		पूर्ण
	पूर्ण जबतक (i-- && found_lower);

	out_pair->high = lowest_transition.high;
	out_pair->low = lowest_transition.low;
पूर्ण

/* Set the baseband attenuation value on chip. */
व्योम b43legacy_phy_set_baseband_attenuation(काष्ठा b43legacy_wldev *dev,
					    u16 bbatt)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 value;

	अगर (phy->analog == 0) अणु
		value = (b43legacy_पढ़ो16(dev, 0x03E6) & 0xFFF0);
		value |= (bbatt & 0x000F);
		b43legacy_ग_लिखो16(dev, 0x03E6, value);
		वापस;
	पूर्ण

	अगर (phy->analog > 1) अणु
		value = b43legacy_phy_पढ़ो(dev, 0x0060) & 0xFFC3;
		value |= (bbatt << 2) & 0x003C;
	पूर्ण अन्यथा अणु
		value = b43legacy_phy_पढ़ो(dev, 0x0060) & 0xFF87;
		value |= (bbatt << 3) & 0x0078;
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0060, value);
पूर्ण

/* https://bcm-specs.sipsolutions.net/LocalOscillator/Measure */
व्योम b43legacy_phy_lo_g_measure(काष्ठा b43legacy_wldev *dev)
अणु
	अटल स्थिर u8 pairorder[10] = अणु 3, 1, 5, 7, 9, 2, 0, 4, 6, 8 पूर्ण;
	स्थिर पूर्णांक is_initializing = (b43legacy_status(dev)
				     < B43legacy_STAT_STARTED);
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 h;
	u16 i;
	u16 oldi = 0;
	u16 j;
	काष्ठा b43legacy_lopair control;
	काष्ठा b43legacy_lopair *पंचांगp_control;
	u16 पंचांगp;
	u16 regstack[16] = अणु 0 पूर्ण;
	u8 oldchannel;

	/* XXX: What are these? */
	u8 r27 = 0;
	u16 r31;

	oldchannel = phy->channel;
	/* Setup */
	अगर (phy->gmode) अणु
		regstack[0] = b43legacy_phy_पढ़ो(dev, B43legacy_PHY_G_CRS);
		regstack[1] = b43legacy_phy_पढ़ो(dev, 0x0802);
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS, regstack[0]
				    & 0x7FFF);
		b43legacy_phy_ग_लिखो(dev, 0x0802, regstack[1] & 0xFFFC);
	पूर्ण
	regstack[3] = b43legacy_पढ़ो16(dev, 0x03E2);
	b43legacy_ग_लिखो16(dev, 0x03E2, regstack[3] | 0x8000);
	regstack[4] = b43legacy_पढ़ो16(dev, B43legacy_MMIO_CHANNEL_EXT);
	regstack[5] = b43legacy_phy_पढ़ो(dev, 0x15);
	regstack[6] = b43legacy_phy_पढ़ो(dev, 0x2A);
	regstack[7] = b43legacy_phy_पढ़ो(dev, 0x35);
	regstack[8] = b43legacy_phy_पढ़ो(dev, 0x60);
	regstack[9] = b43legacy_radio_पढ़ो16(dev, 0x43);
	regstack[10] = b43legacy_radio_पढ़ो16(dev, 0x7A);
	regstack[11] = b43legacy_radio_पढ़ो16(dev, 0x52);
	अगर (phy->gmode) अणु
		regstack[12] = b43legacy_phy_पढ़ो(dev, 0x0811);
		regstack[13] = b43legacy_phy_पढ़ो(dev, 0x0812);
		regstack[14] = b43legacy_phy_पढ़ो(dev, 0x0814);
		regstack[15] = b43legacy_phy_पढ़ो(dev, 0x0815);
	पूर्ण
	b43legacy_radio_selectchannel(dev, 6, 0);
	अगर (phy->gmode) अणु
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS, regstack[0]
				    & 0x7FFF);
		b43legacy_phy_ग_लिखो(dev, 0x0802, regstack[1] & 0xFFFC);
		b43legacy_dummy_transmission(dev);
	पूर्ण
	b43legacy_radio_ग_लिखो16(dev, 0x0043, 0x0006);

	b43legacy_phy_set_baseband_attenuation(dev, 2);

	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT, 0x0000);
	b43legacy_phy_ग_लिखो(dev, 0x002E, 0x007F);
	b43legacy_phy_ग_लिखो(dev, 0x080F, 0x0078);
	b43legacy_phy_ग_लिखो(dev, 0x0035, regstack[7] & ~(1 << 7));
	b43legacy_radio_ग_लिखो16(dev, 0x007A, regstack[10] & 0xFFF0);
	b43legacy_phy_ग_लिखो(dev, 0x002B, 0x0203);
	b43legacy_phy_ग_लिखो(dev, 0x002A, 0x08A3);
	अगर (phy->gmode) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0814, regstack[14] | 0x0003);
		b43legacy_phy_ग_लिखो(dev, 0x0815, regstack[15] & 0xFFFC);
		b43legacy_phy_ग_लिखो(dev, 0x0811, 0x01B3);
		b43legacy_phy_ग_लिखो(dev, 0x0812, 0x00B2);
	पूर्ण
	अगर (is_initializing)
		b43legacy_phy_lo_g_measure_txctl2(dev);
	b43legacy_phy_ग_लिखो(dev, 0x080F, 0x8078);

	/* Measure */
	control.low = 0;
	control.high = 0;
	क्रम (h = 0; h < 10; h++) अणु
		/* Loop over each possible RadioAttenuation (0-9) */
		i = pairorder[h];
		अगर (is_initializing) अणु
			अगर (i == 3) अणु
				control.low = 0;
				control.high = 0;
			पूर्ण अन्यथा अगर (((i % 2 == 1) && (oldi % 2 == 1)) ||
				  ((i % 2 == 0) && (oldi % 2 == 0))) अणु
				पंचांगp_control = b43legacy_get_lopair(phy, oldi,
								   0);
				स_नकल(&control, पंचांगp_control, माप(control));
			पूर्ण अन्यथा अणु
				पंचांगp_control = b43legacy_get_lopair(phy, 3, 0);
				स_नकल(&control, पंचांगp_control, माप(control));
			पूर्ण
		पूर्ण
		/* Loop over each possible BasebandAttenuation/2 */
		क्रम (j = 0; j < 4; j++) अणु
			अगर (is_initializing) अणु
				पंचांगp = i * 2 + j;
				r27 = 0;
				r31 = 0;
				अगर (पंचांगp > 14) अणु
					r31 = 1;
					अगर (पंचांगp > 17)
						r27 = 1;
					अगर (पंचांगp > 19)
						r27 = 2;
				पूर्ण
			पूर्ण अन्यथा अणु
				पंचांगp_control = b43legacy_get_lopair(phy, i,
								   j * 2);
				अगर (!पंचांगp_control->used)
					जारी;
				स_नकल(&control, पंचांगp_control, माप(control));
				r27 = 3;
				r31 = 0;
			पूर्ण
			b43legacy_radio_ग_लिखो16(dev, 0x43, i);
			b43legacy_radio_ग_लिखो16(dev, 0x52, phy->txctl2);
			udelay(10);
			cond_resched();

			b43legacy_phy_set_baseband_attenuation(dev, j * 2);

			पंचांगp = (regstack[10] & 0xFFF0);
			अगर (r31)
				पंचांगp |= 0x0008;
			b43legacy_radio_ग_लिखो16(dev, 0x007A, पंचांगp);

			पंचांगp_control = b43legacy_get_lopair(phy, i, j * 2);
			b43legacy_phy_lo_g_state(dev, &control, पंचांगp_control,
						 r27);
		पूर्ण
		oldi = i;
	पूर्ण
	/* Loop over each possible RadioAttenuation (10-13) */
	क्रम (i = 10; i < 14; i++) अणु
		/* Loop over each possible BasebandAttenuation/2 */
		क्रम (j = 0; j < 4; j++) अणु
			अगर (is_initializing) अणु
				पंचांगp_control = b43legacy_get_lopair(phy, i - 9,
								 j * 2);
				स_नकल(&control, पंचांगp_control, माप(control));
				/* FIXME: The next line is wrong, as the
				 * following अगर statement can never trigger. */
				पंचांगp = (i - 9) * 2 + j - 5;
				r27 = 0;
				r31 = 0;
				अगर (पंचांगp > 14) अणु
					r31 = 1;
					अगर (पंचांगp > 17)
						r27 = 1;
					अगर (पंचांगp > 19)
						r27 = 2;
				पूर्ण
			पूर्ण अन्यथा अणु
				पंचांगp_control = b43legacy_get_lopair(phy, i - 9,
								   j * 2);
				अगर (!पंचांगp_control->used)
					जारी;
				स_नकल(&control, पंचांगp_control, माप(control));
				r27 = 3;
				r31 = 0;
			पूर्ण
			b43legacy_radio_ग_लिखो16(dev, 0x43, i - 9);
			/* FIXME: shouldn't txctl1 be zero in the next line
			 * and 3 in the loop above? */
			b43legacy_radio_ग_लिखो16(dev, 0x52,
					      phy->txctl2
					      | (3/*txctl1*/ << 4));
			udelay(10);
			cond_resched();

			b43legacy_phy_set_baseband_attenuation(dev, j * 2);

			पंचांगp = (regstack[10] & 0xFFF0);
			अगर (r31)
				पंचांगp |= 0x0008;
			b43legacy_radio_ग_लिखो16(dev, 0x7A, पंचांगp);

			पंचांगp_control = b43legacy_get_lopair(phy, i, j * 2);
			b43legacy_phy_lo_g_state(dev, &control, पंचांगp_control,
						 r27);
		पूर्ण
	पूर्ण

	/* Restoration */
	अगर (phy->gmode) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xE300);
		b43legacy_phy_ग_लिखो(dev, 0x0812, (r27 << 8) | 0xA0);
		udelay(5);
		b43legacy_phy_ग_लिखो(dev, 0x0812, (r27 << 8) | 0xA2);
		udelay(2);
		b43legacy_phy_ग_लिखो(dev, 0x0812, (r27 << 8) | 0xA3);
		cond_resched();
	पूर्ण अन्यथा
		b43legacy_phy_ग_लिखो(dev, 0x0015, r27 | 0xEFA0);
	b43legacy_phy_lo_adjust(dev, is_initializing);
	b43legacy_phy_ग_लिखो(dev, 0x002E, 0x807F);
	अगर (phy->gmode)
		b43legacy_phy_ग_लिखो(dev, 0x002F, 0x0202);
	अन्यथा
		b43legacy_phy_ग_लिखो(dev, 0x002F, 0x0101);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT, regstack[4]);
	b43legacy_phy_ग_लिखो(dev, 0x0015, regstack[5]);
	b43legacy_phy_ग_लिखो(dev, 0x002A, regstack[6]);
	b43legacy_phy_ग_लिखो(dev, 0x0035, regstack[7]);
	b43legacy_phy_ग_लिखो(dev, 0x0060, regstack[8]);
	b43legacy_radio_ग_लिखो16(dev, 0x0043, regstack[9]);
	b43legacy_radio_ग_लिखो16(dev, 0x007A, regstack[10]);
	regstack[11] &= 0x00F0;
	regstack[11] |= (b43legacy_radio_पढ़ो16(dev, 0x52) & 0x000F);
	b43legacy_radio_ग_लिखो16(dev, 0x52, regstack[11]);
	b43legacy_ग_लिखो16(dev, 0x03E2, regstack[3]);
	अगर (phy->gmode) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0811, regstack[12]);
		b43legacy_phy_ग_लिखो(dev, 0x0812, regstack[13]);
		b43legacy_phy_ग_लिखो(dev, 0x0814, regstack[14]);
		b43legacy_phy_ग_लिखो(dev, 0x0815, regstack[15]);
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS, regstack[0]);
		b43legacy_phy_ग_लिखो(dev, 0x0802, regstack[1]);
	पूर्ण
	b43legacy_radio_selectchannel(dev, oldchannel, 1);

#अगर_घोषित CONFIG_B43LEGACY_DEBUG
	अणु
		/* Sanity check क्रम all lopairs. */
		क्रम (i = 0; i < B43legacy_LO_COUNT; i++) अणु
			पंचांगp_control = phy->_lo_pairs + i;
			अगर (पंचांगp_control->low < -8 || पंचांगp_control->low > 8 ||
			    पंचांगp_control->high < -8 || पंचांगp_control->high > 8)
				b43legacywarn(dev->wl,
				       "WARNING: Invalid LOpair (low: %d, high:"
				       " %d, index: %d)\n",
				       पंचांगp_control->low, पंचांगp_control->high, i);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_B43LEGACY_DEBUG */
पूर्ण

अटल
व्योम b43legacy_phy_lo_mark_current_used(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_lopair *pair;

	pair = b43legacy_current_lopair(dev);
	pair->used = 1;
पूर्ण

व्योम b43legacy_phy_lo_mark_all_unused(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	काष्ठा b43legacy_lopair *pair;
	पूर्णांक i;

	क्रम (i = 0; i < B43legacy_LO_COUNT; i++) अणु
		pair = phy->_lo_pairs + i;
		pair->used = 0;
	पूर्ण
पूर्ण

/* https://bcm-specs.sipsolutions.net/EstimatePowerOut
 * This function converts a TSSI value to dBm in Q5.2
 */
अटल s8 b43legacy_phy_estimate_घातer_out(काष्ठा b43legacy_wldev *dev, s8 tssi)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	s8 dbm = 0;
	s32 पंचांगp;

	पंचांगp = phy->idle_tssi;
	पंचांगp += tssi;
	पंचांगp -= phy->savedpctlreg;

	चयन (phy->type) अणु
	हाल B43legacy_PHYTYPE_B:
	हाल B43legacy_PHYTYPE_G:
		पंचांगp = clamp_val(पंचांगp, 0x00, 0x3F);
		dbm = phy->tssi2dbm[पंचांगp];
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण

	वापस dbm;
पूर्ण

/* https://bcm-specs.sipsolutions.net/RecalculateTransmissionPower */
व्योम b43legacy_phy_xmitघातer(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 पंचांगp;
	u16 txघातer;
	s8 v0;
	s8 v1;
	s8 v2;
	s8 v3;
	s8 average;
	पूर्णांक max_pwr;
	s16 desired_pwr;
	s16 estimated_pwr;
	s16 pwr_adjust;
	s16 radio_att_delta;
	s16 baseband_att_delta;
	s16 radio_attenuation;
	s16 baseband_attenuation;

	अगर (phy->savedpctlreg == 0xFFFF)
		वापस;
	अगर ((dev->dev->bus->boardinfo.type == 0x0416) &&
	    is_bcm_board_venकरोr(dev))
		वापस;
#अगर_घोषित CONFIG_B43LEGACY_DEBUG
	अगर (phy->manual_txघातer_control)
		वापस;
#पूर्ण_अगर

	B43legacy_BUG_ON(!(phy->type == B43legacy_PHYTYPE_B ||
			 phy->type == B43legacy_PHYTYPE_G));
	पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED, 0x0058);
	v0 = (s8)(पंचांगp & 0x00FF);
	v1 = (s8)((पंचांगp & 0xFF00) >> 8);
	पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED, 0x005A);
	v2 = (s8)(पंचांगp & 0x00FF);
	v3 = (s8)((पंचांगp & 0xFF00) >> 8);
	पंचांगp = 0;

	अगर (v0 == 0x7F || v1 == 0x7F || v2 == 0x7F || v3 == 0x7F) अणु
		पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
					 0x0070);
		v0 = (s8)(पंचांगp & 0x00FF);
		v1 = (s8)((पंचांगp & 0xFF00) >> 8);
		पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
					 0x0072);
		v2 = (s8)(पंचांगp & 0x00FF);
		v3 = (s8)((पंचांगp & 0xFF00) >> 8);
		अगर (v0 == 0x7F || v1 == 0x7F || v2 == 0x7F || v3 == 0x7F)
			वापस;
		v0 = (v0 + 0x20) & 0x3F;
		v1 = (v1 + 0x20) & 0x3F;
		v2 = (v2 + 0x20) & 0x3F;
		v3 = (v3 + 0x20) & 0x3F;
		पंचांगp = 1;
	पूर्ण
	b43legacy_radio_clear_tssi(dev);

	average = (v0 + v1 + v2 + v3 + 2) / 4;

	अगर (पंचांगp && (b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED, 0x005E)
	    & 0x8))
		average -= 13;

	estimated_pwr = b43legacy_phy_estimate_घातer_out(dev, average);

	max_pwr = dev->dev->bus->sprom.maxpwr_bg;

	अगर ((dev->dev->bus->sprom.boardflags_lo
	     & B43legacy_BFL_PACTRL) &&
	    (phy->type == B43legacy_PHYTYPE_G))
		max_pwr -= 0x3;
	अगर (unlikely(max_pwr <= 0)) अणु
		b43legacywarn(dev->wl, "Invalid max-TX-power value in SPROM."
			"\n");
		max_pwr = 74; /* fake it */
		dev->dev->bus->sprom.maxpwr_bg = max_pwr;
	पूर्ण

	/* Use regulatory inक्रमmation to get the maximum घातer.
	 * In the असलence of such data from mac80211, we will use 20 dBm, which
	 * is the value क्रम the EU, US, Canada, and most of the world.
	 * The regulatory maximum is reduced by the antenna gain (from sprom)
	 * and 1.5 dBm (a safety factor??). The result is in Q5.2 क्रमmat
	 * which accounts क्रम the factor of 4 */
#घोषणा REG_MAX_PWR 20
	max_pwr = min(REG_MAX_PWR * 4
		      - dev->dev->bus->sprom.antenna_gain.a0
		      - 0x6, max_pwr);

	/* find the desired घातer in Q5.2 - घातer_level is in dBm
	 * and limit it - max_pwr is alपढ़ोy in Q5.2 */
	desired_pwr = clamp_val(phy->घातer_level << 2, 0, max_pwr);
	अगर (b43legacy_debug(dev, B43legacy_DBG_XMITPOWER))
		b43legacydbg(dev->wl, "Current TX power output: " Q52_FMT
		       " dBm, Desired TX power output: " Q52_FMT
		       " dBm\n", Q52_ARG(estimated_pwr),
		       Q52_ARG(desired_pwr));
	/* Check अगर we need to adjust the current घातer. The factor of 2 is
	 * क्रम damping */
	pwr_adjust = (desired_pwr - estimated_pwr) / 2;
	/* RF attenuation delta
	 * The minus sign is because lower attenuation => more घातer */
	radio_att_delta = -(pwr_adjust + 7) >> 3;
	/* Baseband attenuation delta */
	baseband_att_delta = -(pwr_adjust >> 1) - (4 * radio_att_delta);
	/* Do we need to adjust anything? */
	अगर ((radio_att_delta == 0) && (baseband_att_delta == 0)) अणु
		b43legacy_phy_lo_mark_current_used(dev);
		वापस;
	पूर्ण

	/* Calculate the new attenuation values. */
	baseband_attenuation = phy->bbatt;
	baseband_attenuation += baseband_att_delta;
	radio_attenuation = phy->rfatt;
	radio_attenuation += radio_att_delta;

	/* Get baseband and radio attenuation values पूर्णांकo permitted ranges.
	 * baseband 0-11, radio 0-9.
	 * Radio attenuation affects घातer level 4 बार as much as baseband.
	 */
	अगर (radio_attenuation < 0) अणु
		baseband_attenuation -= (4 * -radio_attenuation);
		radio_attenuation = 0;
	पूर्ण अन्यथा अगर (radio_attenuation > 9) अणु
		baseband_attenuation += (4 * (radio_attenuation - 9));
		radio_attenuation = 9;
	पूर्ण अन्यथा अणु
		जबतक (baseband_attenuation < 0 && radio_attenuation > 0) अणु
			baseband_attenuation += 4;
			radio_attenuation--;
		पूर्ण
		जबतक (baseband_attenuation > 11 && radio_attenuation < 9) अणु
			baseband_attenuation -= 4;
			radio_attenuation++;
		पूर्ण
	पूर्ण
	baseband_attenuation = clamp_val(baseband_attenuation, 0, 11);

	txघातer = phy->txctl1;
	अगर ((phy->radio_ver == 0x2050) && (phy->radio_rev == 2)) अणु
		अगर (radio_attenuation <= 1) अणु
			अगर (txघातer == 0) अणु
				txघातer = 3;
				radio_attenuation += 2;
				baseband_attenuation += 2;
			पूर्ण अन्यथा अगर (dev->dev->bus->sprom.boardflags_lo
				   & B43legacy_BFL_PACTRL) अणु
				baseband_attenuation += 4 *
						     (radio_attenuation - 2);
				radio_attenuation = 2;
			पूर्ण
		पूर्ण अन्यथा अगर (radio_attenuation > 4 && txघातer != 0) अणु
			txघातer = 0;
			अगर (baseband_attenuation < 3) अणु
				radio_attenuation -= 3;
				baseband_attenuation += 2;
			पूर्ण अन्यथा अणु
				radio_attenuation -= 2;
				baseband_attenuation -= 2;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Save the control values */
	phy->txctl1 = txघातer;
	baseband_attenuation = clamp_val(baseband_attenuation, 0, 11);
	radio_attenuation = clamp_val(radio_attenuation, 0, 9);
	phy->rfatt = radio_attenuation;
	phy->bbatt = baseband_attenuation;

	/* Adjust the hardware */
	b43legacy_phy_lock(dev);
	b43legacy_radio_lock(dev);
	b43legacy_radio_set_txघातer_bg(dev, baseband_attenuation,
				       radio_attenuation, txघातer);
	b43legacy_phy_lo_mark_current_used(dev);
	b43legacy_radio_unlock(dev);
	b43legacy_phy_unlock(dev);
पूर्ण

अटल अंतरभूत
s32 b43legacy_tssi2dbm_ad(s32 num, s32 den)
अणु
	अगर (num < 0)
		वापस num/den;
	अन्यथा
		वापस (num+den/2)/den;
पूर्ण

अटल अंतरभूत
s8 b43legacy_tssi2dbm_entry(s8 entry [], u8 index, s16 pab0, s16 pab1, s16 pab2)
अणु
	s32 m1;
	s32 m2;
	s32 f = 256;
	s32 q;
	s32 delta;
	s8 i = 0;

	m1 = b43legacy_tssi2dbm_ad(16 * pab0 + index * pab1, 32);
	m2 = max(b43legacy_tssi2dbm_ad(32768 + index * pab2, 256), 1);
	करो अणु
		अगर (i > 15)
			वापस -EINVAL;
		q = b43legacy_tssi2dbm_ad(f * 4096 -
					  b43legacy_tssi2dbm_ad(m2 * f, 16) *
					  f, 2048);
		delta = असल(q - f);
		f = q;
		i++;
	पूर्ण जबतक (delta >= 2);
	entry[index] = clamp_val(b43legacy_tssi2dbm_ad(m1 * f, 8192),
				   -127, 128);
	वापस 0;
पूर्ण

/* http://bcm-specs.sipsolutions.net/TSSI_to_DBM_Table */
पूर्णांक b43legacy_phy_init_tssi2dbm_table(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	s16 pab0;
	s16 pab1;
	s16 pab2;
	u8 idx;
	s8 *dyn_tssi2dbm;

	B43legacy_WARN_ON(!(phy->type == B43legacy_PHYTYPE_B ||
			  phy->type == B43legacy_PHYTYPE_G));
	pab0 = (s16)(dev->dev->bus->sprom.pa0b0);
	pab1 = (s16)(dev->dev->bus->sprom.pa0b1);
	pab2 = (s16)(dev->dev->bus->sprom.pa0b2);

	अगर ((dev->dev->bus->chip_id == 0x4301) && (phy->radio_ver != 0x2050)) अणु
		phy->idle_tssi = 0x34;
		phy->tssi2dbm = b43legacy_tssi2dbm_b_table;
		वापस 0;
	पूर्ण

	अगर (pab0 != 0 && pab1 != 0 && pab2 != 0 &&
	    pab0 != -1 && pab1 != -1 && pab2 != -1) अणु
		/* The pabX values are set in SPROM. Use them. */
		अगर ((s8)dev->dev->bus->sprom.itssi_bg != 0 &&
		    (s8)dev->dev->bus->sprom.itssi_bg != -1)
			phy->idle_tssi = (s8)(dev->dev->bus->sprom.
					  itssi_bg);
		अन्यथा
			phy->idle_tssi = 62;
		dyn_tssi2dbm = kदो_स्मृति(64, GFP_KERNEL);
		अगर (dyn_tssi2dbm == शून्य) अणु
			b43legacyerr(dev->wl, "Could not allocate memory "
			       "for tssi2dbm table\n");
			वापस -ENOMEM;
		पूर्ण
		क्रम (idx = 0; idx < 64; idx++)
			अगर (b43legacy_tssi2dbm_entry(dyn_tssi2dbm, idx, pab0,
						     pab1, pab2)) अणु
				phy->tssi2dbm = शून्य;
				b43legacyerr(dev->wl, "Could not generate "
				       "tssi2dBm table\n");
				kमुक्त(dyn_tssi2dbm);
				वापस -ENODEV;
			पूर्ण
		phy->tssi2dbm = dyn_tssi2dbm;
		phy->dyn_tssi_tbl = 1;
	पूर्ण अन्यथा अणु
		/* pabX values not set in SPROM. */
		चयन (phy->type) अणु
		हाल B43legacy_PHYTYPE_B:
			phy->idle_tssi = 0x34;
			phy->tssi2dbm = b43legacy_tssi2dbm_b_table;
			अवरोध;
		हाल B43legacy_PHYTYPE_G:
			phy->idle_tssi = 0x34;
			phy->tssi2dbm = b43legacy_tssi2dbm_g_table;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक b43legacy_phy_init(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	पूर्णांक err = -ENODEV;

	चयन (phy->type) अणु
	हाल B43legacy_PHYTYPE_B:
		चयन (phy->rev) अणु
		हाल 2:
			b43legacy_phy_initb2(dev);
			err = 0;
			अवरोध;
		हाल 4:
			b43legacy_phy_initb4(dev);
			err = 0;
			अवरोध;
		हाल 5:
			b43legacy_phy_initb5(dev);
			err = 0;
			अवरोध;
		हाल 6:
			b43legacy_phy_initb6(dev);
			err = 0;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल B43legacy_PHYTYPE_G:
		b43legacy_phy_initg(dev);
		err = 0;
		अवरोध;
	पूर्ण
	अगर (err)
		b43legacyerr(dev->wl, "Unknown PHYTYPE found\n");

	वापस err;
पूर्ण

व्योम b43legacy_phy_set_antenna_भागersity(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 antennaभाग;
	u16 offset;
	u16 value;
	u32 ucodeflags;

	antennaभाग = phy->antenna_भागersity;

	अगर (antennaभाग == 0xFFFF)
		antennaभाग = 3;
	B43legacy_WARN_ON(antennaभाग > 3);

	ucodeflags = b43legacy_shm_पढ़ो32(dev, B43legacy_SHM_SHARED,
					  B43legacy_UCODEFLAGS_OFFSET);
	b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED,
			      B43legacy_UCODEFLAGS_OFFSET,
			      ucodeflags & ~B43legacy_UCODEFLAG_AUTODIV);

	चयन (phy->type) अणु
	हाल B43legacy_PHYTYPE_G:
		offset = 0x0400;

		अगर (antennaभाग == 2)
			value = (3/*स्वतःmatic*/ << 7);
		अन्यथा
			value = (antennaभाग << 7);
		b43legacy_phy_ग_लिखो(dev, offset + 1,
				    (b43legacy_phy_पढ़ो(dev, offset + 1)
				    & 0x7E7F) | value);

		अगर (antennaभाग >= 2) अणु
			अगर (antennaभाग == 2)
				value = (antennaभाग << 7);
			अन्यथा
				value = (0/*क्रमce0*/ << 7);
			b43legacy_phy_ग_लिखो(dev, offset + 0x2B,
					    (b43legacy_phy_पढ़ो(dev,
					    offset + 0x2B)
					    & 0xFEFF) | value);
		पूर्ण

		अगर (phy->type == B43legacy_PHYTYPE_G) अणु
			अगर (antennaभाग >= 2)
				b43legacy_phy_ग_लिखो(dev, 0x048C,
						    b43legacy_phy_पढ़ो(dev,
						    0x048C) | 0x2000);
			अन्यथा
				b43legacy_phy_ग_लिखो(dev, 0x048C,
						    b43legacy_phy_पढ़ो(dev,
						    0x048C) & ~0x2000);
			अगर (phy->rev >= 2) अणु
				b43legacy_phy_ग_लिखो(dev, 0x0461,
						    b43legacy_phy_पढ़ो(dev,
						    0x0461) | 0x0010);
				b43legacy_phy_ग_लिखो(dev, 0x04AD,
						    (b43legacy_phy_पढ़ो(dev,
						    0x04AD)
						    & 0x00FF) | 0x0015);
				अगर (phy->rev == 2)
					b43legacy_phy_ग_लिखो(dev, 0x0427,
							    0x0008);
				अन्यथा
					b43legacy_phy_ग_लिखो(dev, 0x0427,
						(b43legacy_phy_पढ़ो(dev, 0x0427)
						 & 0x00FF) | 0x0008);
			पूर्ण अन्यथा अगर (phy->rev >= 6)
				b43legacy_phy_ग_लिखो(dev, 0x049B, 0x00DC);
		पूर्ण अन्यथा अणु
			अगर (phy->rev < 3)
				b43legacy_phy_ग_लिखो(dev, 0x002B,
						    (b43legacy_phy_पढ़ो(dev,
						    0x002B) & 0x00FF)
						    | 0x0024);
			अन्यथा अणु
				b43legacy_phy_ग_लिखो(dev, 0x0061,
						    b43legacy_phy_पढ़ो(dev,
						    0x0061) | 0x0010);
				अगर (phy->rev == 3) अणु
					b43legacy_phy_ग_लिखो(dev, 0x0093,
							    0x001D);
					b43legacy_phy_ग_लिखो(dev, 0x0027,
							    0x0008);
				पूर्ण अन्यथा अणु
					b43legacy_phy_ग_लिखो(dev, 0x0093,
							    0x003A);
					b43legacy_phy_ग_लिखो(dev, 0x0027,
						(b43legacy_phy_पढ़ो(dev, 0x0027)
						 & 0x00FF) | 0x0008);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल B43legacy_PHYTYPE_B:
		अगर (dev->dev->id.revision == 2)
			value = (3/*स्वतःmatic*/ << 7);
		अन्यथा
			value = (antennaभाग << 7);
		b43legacy_phy_ग_लिखो(dev, 0x03E2,
				    (b43legacy_phy_पढ़ो(dev, 0x03E2)
				    & 0xFE7F) | value);
		अवरोध;
	शेष:
		B43legacy_WARN_ON(1);
	पूर्ण

	अगर (antennaभाग >= 2) अणु
		ucodeflags = b43legacy_shm_पढ़ो32(dev, B43legacy_SHM_SHARED,
						  B43legacy_UCODEFLAGS_OFFSET);
		b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED,
				      B43legacy_UCODEFLAGS_OFFSET,
				      ucodeflags | B43legacy_UCODEFLAG_AUTODIV);
	पूर्ण

	phy->antenna_भागersity = antennaभाग;
पूर्ण

/* Set the PowerSavingControlBits.
 * Bitvalues:
 *   0  => unset the bit
 *   1  => set the bit
 *   -1 => calculate the bit
 */
व्योम b43legacy_घातer_saving_ctl_bits(काष्ठा b43legacy_wldev *dev,
				     पूर्णांक bit25, पूर्णांक bit26)
अणु
	पूर्णांक i;
	u32 status;

/* FIXME: Force 25 to off and 26 to on क्रम now: */
bit25 = 0;
bit26 = 1;

	अगर (bit25 == -1) अणु
		/* TODO: If घातersave is not off and FIXME is not set and we
		 *	are not in adhoc and thus is not an AP and we arei
		 *	associated, set bit 25 */
	पूर्ण
	अगर (bit26 == -1) अणु
		/* TODO: If the device is awake or this is an AP, or we are
		 *	scanning, or FIXME, or we are associated, or FIXME,
		 *	or the latest PS-Poll packet sent was successful,
		 *	set bit26  */
	पूर्ण
	status = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	अगर (bit25)
		status |= B43legacy_MACCTL_HWPS;
	अन्यथा
		status &= ~B43legacy_MACCTL_HWPS;
	अगर (bit26)
		status |= B43legacy_MACCTL_AWAKE;
	अन्यथा
		status &= ~B43legacy_MACCTL_AWAKE;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, status);
	अगर (bit26 && dev->dev->id.revision >= 5) अणु
		क्रम (i = 0; i < 100; i++) अणु
			अगर (b43legacy_shm_पढ़ो32(dev, B43legacy_SHM_SHARED,
						 0x0040) != 4)
				अवरोध;
			udelay(10);
		पूर्ण
	पूर्ण
पूर्ण
