<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
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

#अगर_अघोषित B43legacy_PHY_H_
#घोषणा B43legacy_PHY_H_

#समावेश <linux/types.h>

क्रमागत अणु
	B43legacy_ANTENNA0,	  /* Antenna 0 */
	B43legacy_ANTENNA1,	  /* Antenna 0 */
	B43legacy_ANTENNA_AUTO1,  /* Automatic, starting with antenna 1 */
	B43legacy_ANTENNA_AUTO0,  /* Automatic, starting with antenna 0 */

	B43legacy_ANTENNA_AUTO	= B43legacy_ANTENNA_AUTO0,
	B43legacy_ANTENNA_DEFAULT = B43legacy_ANTENNA_AUTO,
पूर्ण;

क्रमागत अणु
	B43legacy_INTERFMODE_NONE,
	B43legacy_INTERFMODE_NONWLAN,
	B43legacy_INTERFMODE_MANUALWLAN,
	B43legacy_INTERFMODE_AUTOWLAN,
पूर्ण;

/*** PHY Registers ***/

/* Routing */
#घोषणा B43legacy_PHYROUTE_OFDM_GPHY	0x400
#घोषणा B43legacy_PHYROUTE_EXT_GPHY	0x800

/* Base रेजिस्टरs. */
#घोषणा B43legacy_PHY_BASE(reg)	(reg)
/* OFDM (A) रेजिस्टरs of a G-PHY */
#घोषणा B43legacy_PHY_OFDM(reg)	((reg) | B43legacy_PHYROUTE_OFDM_GPHY)
/* Extended G-PHY रेजिस्टरs */
#घोषणा B43legacy_PHY_EXTG(reg)	((reg) | B43legacy_PHYROUTE_EXT_GPHY)


/* Extended G-PHY Registers */
#घोषणा B43legacy_PHY_CLASSCTL		B43legacy_PHY_EXTG(0x02)	/* Classअगरy control */
#घोषणा B43legacy_PHY_GTABCTL		B43legacy_PHY_EXTG(0x03)	/* G-PHY table control (see below) */
#घोषणा  B43legacy_PHY_GTABOFF		0x03FF			/* G-PHY table offset (see below) */
#घोषणा  B43legacy_PHY_GTABNR		0xFC00			/* G-PHY table number (see below) */
#घोषणा  B43legacy_PHY_GTABNR_SHIFT	10
#घोषणा B43legacy_PHY_GTABDATA		B43legacy_PHY_EXTG(0x04)	/* G-PHY table data */
#घोषणा B43legacy_PHY_LO_MASK		B43legacy_PHY_EXTG(0x0F)	/* Local Oscillator control mask */
#घोषणा B43legacy_PHY_LO_CTL		B43legacy_PHY_EXTG(0x10)	/* Local Oscillator control */
#घोषणा B43legacy_PHY_RFOVER		B43legacy_PHY_EXTG(0x11)	/* RF override */
#घोषणा B43legacy_PHY_RFOVERVAL		B43legacy_PHY_EXTG(0x12)	/* RF override value */
/*** OFDM table numbers ***/
#घोषणा B43legacy_OFDMTAB(number, offset)				\
			  (((number) << B43legacy_PHY_OTABLENR_SHIFT)	\
			  | (offset))
#घोषणा B43legacy_OFDMTAB_AGC1		B43legacy_OFDMTAB(0x00, 0)
#घोषणा B43legacy_OFDMTAB_GAIN0		B43legacy_OFDMTAB(0x00, 0)
#घोषणा B43legacy_OFDMTAB_GAINX		B43legacy_OFDMTAB(0x01, 0)
#घोषणा B43legacy_OFDMTAB_GAIN1		B43legacy_OFDMTAB(0x01, 4)
#घोषणा B43legacy_OFDMTAB_AGC3		B43legacy_OFDMTAB(0x02, 0)
#घोषणा B43legacy_OFDMTAB_GAIN2		B43legacy_OFDMTAB(0x02, 3)
#घोषणा B43legacy_OFDMTAB_LNAHPFGAIN1	B43legacy_OFDMTAB(0x03, 0)
#घोषणा B43legacy_OFDMTAB_WRSSI		B43legacy_OFDMTAB(0x04, 0)
#घोषणा B43legacy_OFDMTAB_LNAHPFGAIN2	B43legacy_OFDMTAB(0x04, 0)
#घोषणा B43legacy_OFDMTAB_NOISESCALE	B43legacy_OFDMTAB(0x05, 0)
#घोषणा B43legacy_OFDMTAB_AGC2		B43legacy_OFDMTAB(0x06, 0)
#घोषणा B43legacy_OFDMTAB_ROTOR		B43legacy_OFDMTAB(0x08, 0)
#घोषणा B43legacy_OFDMTAB_ADVRETARD	B43legacy_OFDMTAB(0x09, 0)
#घोषणा B43legacy_OFDMTAB_DAC		B43legacy_OFDMTAB(0x0C, 0)
#घोषणा B43legacy_OFDMTAB_DC		B43legacy_OFDMTAB(0x0E, 7)
#घोषणा B43legacy_OFDMTAB_PWRDYN2	B43legacy_OFDMTAB(0x0E, 12)
#घोषणा B43legacy_OFDMTAB_LNAGAIN	B43legacy_OFDMTAB(0x0E, 13)

#घोषणा B43legacy_OFDMTAB_LPFGAIN	B43legacy_OFDMTAB(0x0F, 12)
#घोषणा B43legacy_OFDMTAB_RSSI		B43legacy_OFDMTAB(0x10, 0)

#घोषणा B43legacy_OFDMTAB_AGC1_R1	B43legacy_OFDMTAB(0x13, 0)
#घोषणा B43legacy_OFDMTAB_GAINX_R1	B43legacy_OFDMTAB(0x14, 0)
#घोषणा B43legacy_OFDMTAB_MINSIGSQ	B43legacy_OFDMTAB(0x14, 1)
#घोषणा B43legacy_OFDMTAB_AGC3_R1	B43legacy_OFDMTAB(0x15, 0)
#घोषणा B43legacy_OFDMTAB_WRSSI_R1	B43legacy_OFDMTAB(0x15, 4)
#घोषणा B43legacy_OFDMTAB_TSSI		B43legacy_OFDMTAB(0x15, 0)
#घोषणा B43legacy_OFDMTAB_DACRFPABB	B43legacy_OFDMTAB(0x16, 0)
#घोषणा B43legacy_OFDMTAB_DACOFF	B43legacy_OFDMTAB(0x17, 0)
#घोषणा B43legacy_OFDMTAB_DCBIAS	B43legacy_OFDMTAB(0x18, 0)

व्योम b43legacy_put_attenuation_पूर्णांकo_ranges(पूर्णांक *_bbatt, पूर्णांक *_rfatt);

/* OFDM (A) PHY Registers */
#घोषणा B43legacy_PHY_VERSION_OFDM	B43legacy_PHY_OFDM(0x00)	/* Versioning रेजिस्टर क्रम A-PHY */
#घोषणा B43legacy_PHY_BBANDCFG		B43legacy_PHY_OFDM(0x01)	/* Baseband config */
#घोषणा  B43legacy_PHY_BBANDCFG_RXANT	0x180			/* RX Antenna selection */
#घोषणा  B43legacy_PHY_BBANDCFG_RXANT_SHIFT	7
#घोषणा B43legacy_PHY_PWRDOWN		B43legacy_PHY_OFDM(0x03)	/* Powerकरोwn */
#घोषणा B43legacy_PHY_CRSTHRES1		B43legacy_PHY_OFDM(0x06)	/* CRS Threshold 1 */
#घोषणा B43legacy_PHY_LNAHPFCTL		B43legacy_PHY_OFDM(0x1C)	/* LNA/HPF control */
#घोषणा B43legacy_PHY_ADIVRELATED	B43legacy_PHY_OFDM(0x27)	/* FIXME नाम */
#घोषणा B43legacy_PHY_CRS0		B43legacy_PHY_OFDM(0x29)
#घोषणा B43legacy_PHY_ANTDWELL		B43legacy_PHY_OFDM(0x2B)	/* Antenna dwell */
#घोषणा  B43legacy_PHY_ANTDWELL_AUTODIV1	0x0100			/* Automatic RX भागersity start antenna */
#घोषणा B43legacy_PHY_ENCORE		B43legacy_PHY_OFDM(0x49)	/* "Encore" (RangeMax / BroadRange) */
#घोषणा  B43legacy_PHY_ENCORE_EN	0x0200				/* Encore enable */
#घोषणा B43legacy_PHY_LMS		B43legacy_PHY_OFDM(0x55)
#घोषणा B43legacy_PHY_OFDM61		B43legacy_PHY_OFDM(0x61)	/* FIXME नाम */
#घोषणा  B43legacy_PHY_OFDM61_10	0x0010				/* FIXME नाम */
#घोषणा B43legacy_PHY_IQBAL		B43legacy_PHY_OFDM(0x69)	/* I/Q balance */
#घोषणा B43legacy_PHY_OTABLECTL		B43legacy_PHY_OFDM(0x72)	/* OFDM table control (see below) */
#घोषणा  B43legacy_PHY_OTABLखातापूर्णF	0x03FF				/* OFDM table offset (see below) */
#घोषणा  B43legacy_PHY_OTABLENR		0xFC00				/* OFDM table number (see below) */
#घोषणा  B43legacy_PHY_OTABLENR_SHIFT	10
#घोषणा B43legacy_PHY_OTABLEI		B43legacy_PHY_OFDM(0x73)	/* OFDM table data I */
#घोषणा B43legacy_PHY_OTABLEQ		B43legacy_PHY_OFDM(0x74)	/* OFDM table data Q */
#घोषणा B43legacy_PHY_HPWR_TSSICTL	B43legacy_PHY_OFDM(0x78)	/* Hardware घातer TSSI control */
#घोषणा B43legacy_PHY_NRSSITHRES	B43legacy_PHY_OFDM(0x8A)	/* NRSSI threshold */
#घोषणा B43legacy_PHY_ANTWRSETT		B43legacy_PHY_OFDM(0x8C)	/* Antenna WR settle */
#घोषणा  B43legacy_PHY_ANTWRSETT_ARXDIV	0x2000				/* Automatic RX भागersity enabled */
#घोषणा B43legacy_PHY_CLIPPWRDOWNT	B43legacy_PHY_OFDM(0x93)	/* Clip घातerकरोwn threshold */
#घोषणा B43legacy_PHY_OFDM9B		B43legacy_PHY_OFDM(0x9B)	/* FIXME नाम */
#घोषणा B43legacy_PHY_N1P1GAIN		B43legacy_PHY_OFDM(0xA0)
#घोषणा B43legacy_PHY_P1P2GAIN		B43legacy_PHY_OFDM(0xA1)
#घोषणा B43legacy_PHY_N1N2GAIN		B43legacy_PHY_OFDM(0xA2)
#घोषणा B43legacy_PHY_CLIPTHRES		B43legacy_PHY_OFDM(0xA3)
#घोषणा B43legacy_PHY_CLIPN1P2THRES	B43legacy_PHY_OFDM(0xA4)
#घोषणा B43legacy_PHY_DIVSRCHIDX	B43legacy_PHY_OFDM(0xA8)	/* Divider search gain/index */
#घोषणा B43legacy_PHY_CLIPP2THRES	B43legacy_PHY_OFDM(0xA9)
#घोषणा B43legacy_PHY_CLIPP3THRES	B43legacy_PHY_OFDM(0xAA)
#घोषणा B43legacy_PHY_DIVP1P2GAIN	B43legacy_PHY_OFDM(0xAB)
#घोषणा B43legacy_PHY_DIVSRCHGAINBACK	B43legacy_PHY_OFDM(0xAD)	/* Divider search gain back */
#घोषणा B43legacy_PHY_DIVSRCHGAINCHNG	B43legacy_PHY_OFDM(0xAE)	/* Divider search gain change */
#घोषणा B43legacy_PHY_CRSTHRES1_R1	B43legacy_PHY_OFDM(0xC0)	/* CRS Threshold 1 (rev 1 only) */
#घोषणा B43legacy_PHY_CRSTHRES2_R1	B43legacy_PHY_OFDM(0xC1)	/* CRS Threshold 2 (rev 1 only) */
#घोषणा B43legacy_PHY_TSSIP_LTBASE	B43legacy_PHY_OFDM(0x380)	/* TSSI घातer lookup table base */
#घोषणा B43legacy_PHY_DC_LTBASE		B43legacy_PHY_OFDM(0x3A0)	/* DC lookup table base */
#घोषणा B43legacy_PHY_GAIN_LTBASE	B43legacy_PHY_OFDM(0x3C0)	/* Gain lookup table base */

व्योम b43legacy_put_attenuation_पूर्णांकo_ranges(पूर्णांक *_bbatt, पूर्णांक *_rfatt);

/* Masks क्रम the dअगरferent PHY versioning रेजिस्टरs. */
#घोषणा B43legacy_PHYVER_ANALOG		0xF000
#घोषणा B43legacy_PHYVER_ANALOG_SHIFT	12
#घोषणा B43legacy_PHYVER_TYPE		0x0F00
#घोषणा B43legacy_PHYVER_TYPE_SHIFT	8
#घोषणा B43legacy_PHYVER_VERSION	0x00FF

काष्ठा b43legacy_wldev;

व्योम b43legacy_phy_lock(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_phy_unlock(काष्ठा b43legacy_wldev *dev);

/* Card uses the loopback gain stuff */
#घोषणा has_loopback_gain(phy)			 \
	(((phy)->rev > 1) || ((phy)->gmode))

u16 b43legacy_phy_पढ़ो(काष्ठा b43legacy_wldev *dev, u16 offset);
व्योम b43legacy_phy_ग_लिखो(काष्ठा b43legacy_wldev *dev, u16 offset, u16 val);

पूर्णांक b43legacy_phy_init_tssi2dbm_table(काष्ठा b43legacy_wldev *dev);
पूर्णांक b43legacy_phy_init(काष्ठा b43legacy_wldev *dev);

व्योम b43legacy_set_rx_antenna(काष्ठा b43legacy_wldev *dev, पूर्णांक antenna);

व्योम b43legacy_phy_set_antenna_भागersity(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_phy_calibrate(काष्ठा b43legacy_wldev *dev);
पूर्णांक b43legacy_phy_connect(काष्ठा b43legacy_wldev *dev, पूर्णांक connect);

व्योम b43legacy_phy_lo_b_measure(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_phy_lo_g_measure(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_phy_xmitघातer(काष्ठा b43legacy_wldev *dev);

/* Adjust the LocalOscillator to the saved values.
 * "fixed" is only set to 1 once in initialization. Set to 0 otherwise.
 */
व्योम b43legacy_phy_lo_adjust(काष्ठा b43legacy_wldev *dev, पूर्णांक fixed);
व्योम b43legacy_phy_lo_mark_all_unused(काष्ठा b43legacy_wldev *dev);

व्योम b43legacy_phy_set_baseband_attenuation(काष्ठा b43legacy_wldev *dev,
					    u16 baseband_attenuation);

व्योम b43legacy_घातer_saving_ctl_bits(काष्ठा b43legacy_wldev *dev,
				     पूर्णांक bit25, पूर्णांक bit26);

#पूर्ण_अगर /* B43legacy_PHY_H_ */
