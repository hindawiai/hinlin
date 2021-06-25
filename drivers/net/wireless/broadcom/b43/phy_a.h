<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_B43_PHY_A_H_
#घोषणा LINUX_B43_PHY_A_H_

#समावेश "phy_common.h"


/* OFDM (A) PHY Registers */
#घोषणा B43_PHY_VERSION_OFDM		B43_PHY_OFDM(0x00)	/* Versioning रेजिस्टर क्रम A-PHY */
#घोषणा B43_PHY_BBANDCFG		B43_PHY_OFDM(0x01)	/* Baseband config */
#घोषणा  B43_PHY_BBANDCFG_RXANT		0x180	/* RX Antenna selection */
#घोषणा  B43_PHY_BBANDCFG_RXANT_SHIFT	7
#घोषणा B43_PHY_PWRDOWN			B43_PHY_OFDM(0x03)	/* Powerकरोwn */
#घोषणा B43_PHY_CRSTHRES1_R1		B43_PHY_OFDM(0x06)	/* CRS Threshold 1 (phy.rev 1 only) */
#घोषणा B43_PHY_LNAHPFCTL		B43_PHY_OFDM(0x1C)	/* LNA/HPF control */
#घोषणा B43_PHY_LPFGAINCTL		B43_PHY_OFDM(0x20)	/* LPF Gain control */
#घोषणा B43_PHY_ADIVRELATED		B43_PHY_OFDM(0x27)	/* FIXME नाम */
#घोषणा B43_PHY_CRS0			B43_PHY_OFDM(0x29)
#घोषणा  B43_PHY_CRS0_EN		0x4000
#घोषणा B43_PHY_PEAK_COUNT		B43_PHY_OFDM(0x30)
#घोषणा B43_PHY_ANTDWELL		B43_PHY_OFDM(0x2B)	/* Antenna dwell */
#घोषणा  B43_PHY_ANTDWELL_AUTODIV1	0x0100	/* Automatic RX भागersity start antenna */
#घोषणा B43_PHY_ENCORE			B43_PHY_OFDM(0x49)	/* "Encore" (RangeMax / BroadRange) */
#घोषणा  B43_PHY_ENCORE_EN		0x0200	/* Encore enable */
#घोषणा B43_PHY_LMS			B43_PHY_OFDM(0x55)
#घोषणा B43_PHY_OFDM61			B43_PHY_OFDM(0x61)	/* FIXME नाम */
#घोषणा  B43_PHY_OFDM61_10		0x0010	/* FIXME नाम */
#घोषणा B43_PHY_IQBAL			B43_PHY_OFDM(0x69)	/* I/Q balance */
#घोषणा B43_PHY_BBTXDC_BIAS		B43_PHY_OFDM(0x6B)	/* Baseband TX DC bias */
#घोषणा B43_PHY_OTABLECTL		B43_PHY_OFDM(0x72)	/* OFDM table control (see below) */
#घोषणा  B43_PHY_OTABLखातापूर्णF		0x03FF	/* OFDM table offset (see below) */
#घोषणा  B43_PHY_OTABLENR		0xFC00	/* OFDM table number (see below) */
#घोषणा  B43_PHY_OTABLENR_SHIFT		10
#घोषणा B43_PHY_OTABLEI			B43_PHY_OFDM(0x73)	/* OFDM table data I */
#घोषणा B43_PHY_OTABLEQ			B43_PHY_OFDM(0x74)	/* OFDM table data Q */
#घोषणा B43_PHY_HPWR_TSSICTL		B43_PHY_OFDM(0x78)	/* Hardware घातer TSSI control */
#घोषणा B43_PHY_ADCCTL			B43_PHY_OFDM(0x7A)	/* ADC control */
#घोषणा B43_PHY_IDLE_TSSI		B43_PHY_OFDM(0x7B)
#घोषणा B43_PHY_A_TEMP_SENSE		B43_PHY_OFDM(0x7C)	/* A PHY temperature sense */
#घोषणा B43_PHY_NRSSITHRES		B43_PHY_OFDM(0x8A)	/* NRSSI threshold */
#घोषणा B43_PHY_ANTWRSETT		B43_PHY_OFDM(0x8C)	/* Antenna WR settle */
#घोषणा  B43_PHY_ANTWRSETT_ARXDIV	0x2000	/* Automatic RX भागersity enabled */
#घोषणा B43_PHY_CLIPPWRDOWNT		B43_PHY_OFDM(0x93)	/* Clip घातerकरोwn threshold */
#घोषणा B43_PHY_OFDM9B			B43_PHY_OFDM(0x9B)	/* FIXME नाम */
#घोषणा B43_PHY_N1P1GAIN		B43_PHY_OFDM(0xA0)
#घोषणा B43_PHY_P1P2GAIN		B43_PHY_OFDM(0xA1)
#घोषणा B43_PHY_N1N2GAIN		B43_PHY_OFDM(0xA2)
#घोषणा B43_PHY_CLIPTHRES		B43_PHY_OFDM(0xA3)
#घोषणा B43_PHY_CLIPN1P2THRES		B43_PHY_OFDM(0xA4)
#घोषणा B43_PHY_CCKSHIFTBITS_WA		B43_PHY_OFDM(0xA5)	/* CCK shअगरtbits workaround, FIXME नाम */
#घोषणा B43_PHY_CCKSHIFTBITS		B43_PHY_OFDM(0xA7)	/* FIXME नाम */
#घोषणा B43_PHY_DIVSRCHIDX		B43_PHY_OFDM(0xA8)	/* Divider search gain/index */
#घोषणा B43_PHY_CLIPP2THRES		B43_PHY_OFDM(0xA9)
#घोषणा B43_PHY_CLIPP3THRES		B43_PHY_OFDM(0xAA)
#घोषणा B43_PHY_DIVP1P2GAIN		B43_PHY_OFDM(0xAB)
#घोषणा B43_PHY_DIVSRCHGAINBACK		B43_PHY_OFDM(0xAD)	/* Divider search gain back */
#घोषणा B43_PHY_DIVSRCHGAINCHNG		B43_PHY_OFDM(0xAE)	/* Divider search gain change */
#घोषणा B43_PHY_CRSTHRES1		B43_PHY_OFDM(0xC0)	/* CRS Threshold 1 (phy.rev >= 2 only) */
#घोषणा B43_PHY_CRSTHRES2		B43_PHY_OFDM(0xC1)	/* CRS Threshold 2 (phy.rev >= 2 only) */
#घोषणा B43_PHY_TSSIP_LTBASE		B43_PHY_OFDM(0x380)	/* TSSI घातer lookup table base */
#घोषणा B43_PHY_DC_LTBASE		B43_PHY_OFDM(0x3A0)	/* DC lookup table base */
#घोषणा B43_PHY_GAIN_LTBASE		B43_PHY_OFDM(0x3C0)	/* Gain lookup table base */

/*** OFDM table numbers ***/
#घोषणा B43_OFDMTAB(number, offset)	(((number) << B43_PHY_OTABLENR_SHIFT) | (offset))
#घोषणा B43_OFDMTAB_AGC1		B43_OFDMTAB(0x00, 0)
#घोषणा B43_OFDMTAB_GAIN0		B43_OFDMTAB(0x00, 0)
#घोषणा B43_OFDMTAB_GAINX		B43_OFDMTAB(0x01, 0)	//TODO नाम
#घोषणा B43_OFDMTAB_GAIN1		B43_OFDMTAB(0x01, 4)
#घोषणा B43_OFDMTAB_AGC3		B43_OFDMTAB(0x02, 0)
#घोषणा B43_OFDMTAB_GAIN2		B43_OFDMTAB(0x02, 3)
#घोषणा B43_OFDMTAB_LNAHPFGAIN1		B43_OFDMTAB(0x03, 0)
#घोषणा B43_OFDMTAB_WRSSI		B43_OFDMTAB(0x04, 0)
#घोषणा B43_OFDMTAB_LNAHPFGAIN2		B43_OFDMTAB(0x04, 0)
#घोषणा B43_OFDMTAB_NOISESCALE		B43_OFDMTAB(0x05, 0)
#घोषणा B43_OFDMTAB_AGC2		B43_OFDMTAB(0x06, 0)
#घोषणा B43_OFDMTAB_ROTOR		B43_OFDMTAB(0x08, 0)
#घोषणा B43_OFDMTAB_ADVRETARD		B43_OFDMTAB(0x09, 0)
#घोषणा B43_OFDMTAB_DAC			B43_OFDMTAB(0x0C, 0)
#घोषणा B43_OFDMTAB_DC			B43_OFDMTAB(0x0E, 7)
#घोषणा B43_OFDMTAB_PWRDYN2		B43_OFDMTAB(0x0E, 12)
#घोषणा B43_OFDMTAB_LNAGAIN		B43_OFDMTAB(0x0E, 13)
#घोषणा B43_OFDMTAB_UNKNOWN_0F		B43_OFDMTAB(0x0F, 0)	//TODO नाम
#घोषणा B43_OFDMTAB_UNKNOWN_APHY	B43_OFDMTAB(0x0F, 7)	//TODO नाम
#घोषणा B43_OFDMTAB_LPFGAIN		B43_OFDMTAB(0x0F, 12)
#घोषणा B43_OFDMTAB_RSSI		B43_OFDMTAB(0x10, 0)
#घोषणा B43_OFDMTAB_UNKNOWN_11		B43_OFDMTAB(0x11, 4)	//TODO नाम
#घोषणा B43_OFDMTAB_AGC1_R1		B43_OFDMTAB(0x13, 0)
#घोषणा B43_OFDMTAB_GAINX_R1		B43_OFDMTAB(0x14, 0)	//TODO हटाओ!
#घोषणा B43_OFDMTAB_MINSIGSQ		B43_OFDMTAB(0x14, 0)
#घोषणा B43_OFDMTAB_AGC3_R1		B43_OFDMTAB(0x15, 0)
#घोषणा B43_OFDMTAB_WRSSI_R1		B43_OFDMTAB(0x15, 4)
#घोषणा B43_OFDMTAB_TSSI		B43_OFDMTAB(0x15, 0)
#घोषणा B43_OFDMTAB_DACRFPABB		B43_OFDMTAB(0x16, 0)
#घोषणा B43_OFDMTAB_DACOFF		B43_OFDMTAB(0x17, 0)
#घोषणा B43_OFDMTAB_DCBIAS		B43_OFDMTAB(0x18, 0)

u16 b43_ofdmtab_पढ़ो16(काष्ठा b43_wldev *dev, u16 table, u16 offset);
व्योम b43_ofdmtab_ग_लिखो16(काष्ठा b43_wldev *dev, u16 table,
			 u16 offset, u16 value);
u32 b43_ofdmtab_पढ़ो32(काष्ठा b43_wldev *dev, u16 table, u16 offset);
व्योम b43_ofdmtab_ग_लिखो32(काष्ठा b43_wldev *dev, u16 table,
			 u16 offset, u32 value);

#पूर्ण_अगर /* LINUX_B43_PHY_A_H_ */
