<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित	_BRCMU_WIFI_H_
#घोषणा	_BRCMU_WIFI_H_

#समावेश <linux/अगर_ether.h>		/* क्रम ETH_ALEN */
#समावेश <linux/ieee80211.h>		/* क्रम WLAN_PMKID_LEN */

/*
 * A chanspec (u16) holds the channel number, band, bandwidth and control
 * sideband
 */

/* channel defines */
#घोषणा CH_UPPER_SB			0x01
#घोषणा CH_LOWER_SB			0x02
#घोषणा CH_EWA_VALID			0x04
#घोषणा CH_70MHZ_APART			14
#घोषणा CH_50MHZ_APART			10
#घोषणा CH_30MHZ_APART			6
#घोषणा CH_20MHZ_APART			4
#घोषणा CH_10MHZ_APART			2
#घोषणा CH_5MHZ_APART			1 /* 2G band channels are 5 Mhz apart */
#घोषणा CH_MIN_2G_CHANNEL		1
#घोषणा CH_MAX_2G_CHANNEL		14	/* Max channel in 2G band */
#घोषणा CH_MIN_5G_CHANNEL		34

/* bandstate array indices */
#घोषणा BAND_2G_INDEX		0	/* wlc->bandstate[x] index */
#घोषणा BAND_5G_INDEX		1	/* wlc->bandstate[x] index */

/*
 * max # supported channels. The max channel no is 216, this is that + 1
 * rounded up to a multiple of NBBY (8). DO NOT MAKE it > 255: channels are
 * u8's all over
*/
#घोषणा	MAXCHANNEL		224

#घोषणा WL_CHANSPEC_CHAN_MASK		0x00ff
#घोषणा WL_CHANSPEC_CHAN_SHIFT		0

#घोषणा WL_CHANSPEC_CTL_SB_MASK		0x0300
#घोषणा WL_CHANSPEC_CTL_SB_SHIFT	     8
#घोषणा WL_CHANSPEC_CTL_SB_LOWER	0x0100
#घोषणा WL_CHANSPEC_CTL_SB_UPPER	0x0200
#घोषणा WL_CHANSPEC_CTL_SB_NONE		0x0300

#घोषणा WL_CHANSPEC_BW_MASK		0x0C00
#घोषणा WL_CHANSPEC_BW_SHIFT		    10
#घोषणा WL_CHANSPEC_BW_10		0x0400
#घोषणा WL_CHANSPEC_BW_20		0x0800
#घोषणा WL_CHANSPEC_BW_40		0x0C00
#घोषणा WL_CHANSPEC_BW_80		0x2000

#घोषणा WL_CHANSPEC_BAND_MASK		0xf000
#घोषणा WL_CHANSPEC_BAND_SHIFT		12
#घोषणा WL_CHANSPEC_BAND_5G		0x1000
#घोषणा WL_CHANSPEC_BAND_2G		0x2000
#घोषणा INVCHANSPEC			255

#घोषणा WL_CHAN_VALID_HW		(1 << 0) /* valid with current HW */
#घोषणा WL_CHAN_VALID_SW		(1 << 1) /* valid with country sett. */
#घोषणा WL_CHAN_BAND_5G			(1 << 2) /* 5GHz-band channel */
#घोषणा WL_CHAN_RADAR			(1 << 3) /* radar sensitive  channel */
#घोषणा WL_CHAN_INACTIVE		(1 << 4) /* inactive due to radar */
#घोषणा WL_CHAN_PASSIVE			(1 << 5) /* channel in passive mode */
#घोषणा WL_CHAN_RESTRICTED		(1 << 6) /* restricted use channel */

/* values क्रम band specअगरic 40MHz capabilities  */
#घोषणा WLC_N_BW_20ALL			0
#घोषणा WLC_N_BW_40ALL			1
#घोषणा WLC_N_BW_20IN2G_40IN5G		2

#घोषणा WLC_BW_20MHZ_BIT		BIT(0)
#घोषणा WLC_BW_40MHZ_BIT		BIT(1)
#घोषणा WLC_BW_80MHZ_BIT		BIT(2)
#घोषणा WLC_BW_160MHZ_BIT		BIT(3)

/* Bandwidth capabilities */
#घोषणा WLC_BW_CAP_20MHZ		(WLC_BW_20MHZ_BIT)
#घोषणा WLC_BW_CAP_40MHZ		(WLC_BW_40MHZ_BIT|WLC_BW_20MHZ_BIT)
#घोषणा WLC_BW_CAP_80MHZ		(WLC_BW_80MHZ_BIT|WLC_BW_40MHZ_BIT| \
					 WLC_BW_20MHZ_BIT)
#घोषणा WLC_BW_CAP_160MHZ		(WLC_BW_160MHZ_BIT|WLC_BW_80MHZ_BIT| \
					 WLC_BW_40MHZ_BIT|WLC_BW_20MHZ_BIT)
#घोषणा WLC_BW_CAP_UNRESTRICTED		0xFF

/* band types */
#घोषणा	WLC_BAND_AUTO			0	/* स्वतः-select */
#घोषणा	WLC_BAND_5G			1	/* 5 Ghz */
#घोषणा	WLC_BAND_2G			2	/* 2.4 Ghz */
#घोषणा	WLC_BAND_ALL			3	/* all bands */

#घोषणा CHSPEC_CHANNEL(chspec)	((u8)((chspec) & WL_CHANSPEC_CHAN_MASK))
#घोषणा CHSPEC_BAND(chspec)	((chspec) & WL_CHANSPEC_BAND_MASK)

#घोषणा CHSPEC_CTL_SB(chspec)	((chspec) & WL_CHANSPEC_CTL_SB_MASK)
#घोषणा CHSPEC_BW(chspec)	((chspec) & WL_CHANSPEC_BW_MASK)

#घोषणा CHSPEC_IS10(chspec) \
	(((chspec) & WL_CHANSPEC_BW_MASK) == WL_CHANSPEC_BW_10)

#घोषणा CHSPEC_IS20(chspec) \
	(((chspec) & WL_CHANSPEC_BW_MASK) == WL_CHANSPEC_BW_20)

#घोषणा CHSPEC_IS40(chspec) \
	(((chspec) & WL_CHANSPEC_BW_MASK) == WL_CHANSPEC_BW_40)

#घोषणा CHSPEC_IS80(chspec) \
	(((chspec) & WL_CHANSPEC_BW_MASK) == WL_CHANSPEC_BW_80)

#घोषणा CHSPEC_IS5G(chspec) \
	(((chspec) & WL_CHANSPEC_BAND_MASK) == WL_CHANSPEC_BAND_5G)

#घोषणा CHSPEC_IS2G(chspec) \
	(((chspec) & WL_CHANSPEC_BAND_MASK) == WL_CHANSPEC_BAND_2G)

#घोषणा CHSPEC_SB_NONE(chspec) \
	(((chspec) & WL_CHANSPEC_CTL_SB_MASK) == WL_CHANSPEC_CTL_SB_NONE)

#घोषणा CHSPEC_SB_UPPER(chspec) \
	(((chspec) & WL_CHANSPEC_CTL_SB_MASK) == WL_CHANSPEC_CTL_SB_UPPER)

#घोषणा CHSPEC_SB_LOWER(chspec) \
	(((chspec) & WL_CHANSPEC_CTL_SB_MASK) == WL_CHANSPEC_CTL_SB_LOWER)

#घोषणा CHSPEC_CTL_CHAN(chspec) \
	((CHSPEC_SB_LOWER(chspec)) ? \
	(lower_20_sb(((chspec) & WL_CHANSPEC_CHAN_MASK))) : \
	(upper_20_sb(((chspec) & WL_CHANSPEC_CHAN_MASK))))

#घोषणा CHSPEC2BAND(chspec) (CHSPEC_IS5G(chspec) ? BRCM_BAND_5G : BRCM_BAND_2G)

#घोषणा CHANSPEC_STR_LEN    8

अटल अंतरभूत पूर्णांक lower_20_sb(पूर्णांक channel)
अणु
	वापस channel > CH_10MHZ_APART ? (channel - CH_10MHZ_APART) : 0;
पूर्ण

अटल अंतरभूत पूर्णांक upper_20_sb(पूर्णांक channel)
अणु
	वापस (channel < (MAXCHANNEL - CH_10MHZ_APART)) ?
	       channel + CH_10MHZ_APART : 0;
पूर्ण

अटल अंतरभूत पूर्णांक chspec_bandunit(u16 chspec)
अणु
	वापस CHSPEC_IS5G(chspec) ? BAND_5G_INDEX : BAND_2G_INDEX;
पूर्ण

अटल अंतरभूत u16 ch20mhz_chspec(पूर्णांक channel)
अणु
	u16 rc = channel <= CH_MAX_2G_CHANNEL ?
		 WL_CHANSPEC_BAND_2G : WL_CHANSPEC_BAND_5G;

	वापस	(u16)((u16)channel | WL_CHANSPEC_BW_20 |
		      WL_CHANSPEC_CTL_SB_NONE | rc);
पूर्ण

अटल अंतरभूत पूर्णांक next_20mhz_chan(पूर्णांक channel)
अणु
	वापस channel < (MAXCHANNEL - CH_20MHZ_APART) ?
	       channel + CH_20MHZ_APART : 0;
पूर्ण

/* defined rate in 500kbps */
#घोषणा BRCM_MAXRATE	108	/* in 500kbps units */
#घोषणा BRCM_RATE_1M	2	/* in 500kbps units */
#घोषणा BRCM_RATE_2M	4	/* in 500kbps units */
#घोषणा BRCM_RATE_5M5	11	/* in 500kbps units */
#घोषणा BRCM_RATE_11M	22	/* in 500kbps units */
#घोषणा BRCM_RATE_6M	12	/* in 500kbps units */
#घोषणा BRCM_RATE_9M	18	/* in 500kbps units */
#घोषणा BRCM_RATE_12M	24	/* in 500kbps units */
#घोषणा BRCM_RATE_18M	36	/* in 500kbps units */
#घोषणा BRCM_RATE_24M	48	/* in 500kbps units */
#घोषणा BRCM_RATE_36M	72	/* in 500kbps units */
#घोषणा BRCM_RATE_48M	96	/* in 500kbps units */
#घोषणा BRCM_RATE_54M	108	/* in 500kbps units */

#घोषणा BRCM_2G_25MHZ_OFFSET		5	/* 2.4GHz band channel offset */

#घोषणा MCSSET_LEN	16

अटल अंतरभूत bool ac_biपंचांगap_tst(u8 biपंचांगap, पूर्णांक prec)
अणु
	वापस (biपंचांगap & (1 << (prec))) != 0;
पूर्ण

/* Enumerate crypto algorithms */
#घोषणा	CRYPTO_ALGO_OFF			0
#घोषणा	CRYPTO_ALGO_WEP1		1
#घोषणा	CRYPTO_ALGO_TKIP		2
#घोषणा	CRYPTO_ALGO_WEP128		3
#घोषणा CRYPTO_ALGO_AES_CCM		4
#घोषणा CRYPTO_ALGO_AES_RESERVED1	5
#घोषणा CRYPTO_ALGO_AES_RESERVED2	6
#घोषणा CRYPTO_ALGO_NALG		7

/* wireless security bitvec */

#घोषणा WEP_ENABLED		0x0001
#घोषणा TKIP_ENABLED		0x0002
#घोषणा AES_ENABLED		0x0004
#घोषणा WSEC_SWFLAG		0x0008
/* to go पूर्णांकo transition mode without setting wep */
#घोषणा SES_OW_ENABLED		0x0040
/* MFP */
#घोषणा MFP_CAPABLE		0x0200
#घोषणा MFP_REQUIRED		0x0400

/* WPA authentication mode bitvec */
#घोषणा WPA_AUTH_DISABLED	0x0000	/* Legacy (i.e., non-WPA) */
#घोषणा WPA_AUTH_NONE		0x0001	/* none (IBSS) */
#घोषणा WPA_AUTH_UNSPECIFIED	0x0002	/* over 802.1x */
#घोषणा WPA_AUTH_PSK		0x0004	/* Pre-shared key */
#घोषणा WPA_AUTH_RESERVED1	0x0008
#घोषणा WPA_AUTH_RESERVED2	0x0010

#घोषणा WPA2_AUTH_RESERVED1	0x0020
#घोषणा WPA2_AUTH_UNSPECIFIED	0x0040	/* over 802.1x */
#घोषणा WPA2_AUTH_PSK		0x0080	/* Pre-shared key */
#घोषणा WPA2_AUTH_RESERVED3	0x0200
#घोषणा WPA2_AUTH_RESERVED4	0x0400
#घोषणा WPA2_AUTH_RESERVED5	0x0800
#घोषणा WPA2_AUTH_1X_SHA256	0x1000  /* 1X with SHA256 key derivation */
#घोषणा WPA2_AUTH_FT		0x4000	/* Fast BSS Transition */
#घोषणा WPA2_AUTH_PSK_SHA256	0x8000	/* PSK with SHA256 key derivation */

#घोषणा WPA3_AUTH_SAE_PSK	0x40000	/* SAE with 4-way handshake */

#घोषणा DOT11_DEFAULT_RTS_LEN		2347
#घोषणा DOT11_DEFAULT_FRAG_LEN		2346

#घोषणा DOT11_ICV_AES_LEN		8
#घोषणा DOT11_QOS_LEN			2
#घोषणा DOT11_IV_MAX_LEN		8
#घोषणा DOT11_A4_HDR_LEN		30

#घोषणा HT_CAP_RX_STBC_NO		0x0
#घोषणा HT_CAP_RX_STBC_ONE_STREAM	0x1

#पूर्ण_अगर				/* _BRCMU_WIFI_H_ */
