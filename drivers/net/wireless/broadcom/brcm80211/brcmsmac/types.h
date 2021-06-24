<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _BRCM_TYPES_H_
#घोषणा _BRCM_TYPES_H_

#समावेश <linux/types.h>
#समावेश <linux/पन.स>

#घोषणा WL_CHAN_FREQ_RANGE_2G      0
#घोषणा WL_CHAN_FREQ_RANGE_5GL     1
#घोषणा WL_CHAN_FREQ_RANGE_5GM     2
#घोषणा WL_CHAN_FREQ_RANGE_5GH     3

/* boardflags */

/* Board has gpio 9 controlling the PA */
#घोषणा	BFL_PACTRL		0x00000002
/* Not ok to घातer करोwn the chip pll and oscillator */
#घोषणा	BFL_NOPLLDOWN		0x00000020
/* Board supports the Front End Module */
#घोषणा BFL_FEM			0x00000800
/* Board has an बाह्यal LNA in 2.4GHz band */
#घोषणा BFL_EXTLNA		0x00001000
/* Board has no PA */
#घोषणा BFL_NOPA		0x00010000
/* Power topology uses BUCKBOOST */
#घोषणा BFL_BUCKBOOST		0x00200000
/* Board has FEM and चयन to share antenna w/ BT */
#घोषणा BFL_FEM_BT		0x00400000
/* Power topology करोesn't use CBUCK */
#घोषणा BFL_NOCBUCK		0x00800000
/* Power topology uses PALDO */
#घोषणा BFL_PALDO		0x02000000
/* Board has an बाह्यal LNA in 5GHz band */
#घोषणा BFL_EXTLNA_5GHz		0x10000000

/* boardflags2 */

/* Board has an बाह्यal rxbb regulator */
#घोषणा BFL2_RXBB_INT_REG_DIS	0x00000001
/* Flag to implement alternative A-band PLL settings */
#घोषणा BFL2_APLL_WAR		0x00000002
/* Board permits enabling TX Power Control */
#घोषणा BFL2_TXPWRCTRL_EN	0x00000004
/* Board supports the 2X4 भागersity चयन */
#घोषणा BFL2_2X4_DIV		0x00000008
/* Board supports 5G band घातer gain */
#घोषणा BFL2_5G_PWRGAIN		0x00000010
/* Board overrides ASPM and Clkreq settings */
#घोषणा BFL2_PCIEWAR_OVR	0x00000020
#घोषणा BFL2_LEGACY		0x00000080
/* 4321mcm93 board uses Skyworks FEM */
#घोषणा BFL2_SKWRKFEM_BRD	0x00000100
/* Board has a WAR क्रम घड़ी-harmonic spurs */
#घोषणा BFL2_SPUR_WAR		0x00000200
/* Flag to narrow G-band PLL loop b/w */
#घोषणा BFL2_GPLL_WAR		0x00000400
/* Tx CCK pkts on Ant 0 only */
#घोषणा BFL2_SINGLEANT_CCK	0x00001000
/* WAR to reduce and aव्योम घड़ी-harmonic spurs in 2G */
#घोषणा BFL2_2G_SPUR_WAR	0x00002000
/* Flag to widen G-band PLL loop b/w */
#घोषणा BFL2_GPLL_WAR2	        0x00010000
#घोषणा BFL2_IPALVLSHIFT_3P3    0x00020000
/* Use पूर्णांकernal envelope detector क्रम TX IQCAL */
#घोषणा BFL2_INTERNDET_TXIQCAL  0x00040000
/* Keep the buffered Xtal output from radio "ON". Most drivers will turn it
 * off without this flag to save घातer. */
#घोषणा BFL2_XTALBUFOUTEN       0x00080000

/*
 * board specअगरic GPIO assignment, gpio 0-3 are also customer-configurable
 * led
 */

/* bit 9 controls the PA on new 4306 boards */
#घोषणा	BOARD_GPIO_PACTRL	0x200
#घोषणा BOARD_GPIO_12		0x1000
#घोषणा BOARD_GPIO_13		0x2000

/* **** Core type/rev शेषs **** */
#घोषणा D11CONF		0x0fffffb0	/* Supported  D11 revs: 4, 5, 7-27
					 * also need to update wlc.h MAXCOREREV
					 */

#घोषणा NCONF		0x000001ff	/* Supported nphy revs:
					 *      0       4321a0
					 *      1       4321a1
					 *      2       4321b0/b1/c0/c1
					 *      3       4322a0
					 *      4       4322a1
					 *      5       4716a0
					 *      6       43222a0, 43224a0
					 *      7       43226a0
					 *      8       5357a0, 43236a0
					 */

#घोषणा LCNCONF		0x00000007	/* Supported lcnphy revs:
					 *      0       4313a0, 4336a0, 4330a0
					 *      1
					 *      2       4330a0
					 */

#घोषणा SSLPNCONF	0x0000000f	/* Supported sslpnphy revs:
					 *      0       4329a0/k0
					 *      1       4329b0/4329C0
					 *      2       4319a0
					 *      3       5356a0
					 */

/********************************************************************
 * Phy/Core Configuration.  Defines macros to to check core phy/rev *
 * compile-समय configuration.  Defines शेष core support.       *
 * ******************************************************************
 */

/* Basic macros to check a configuration biपंचांगask */

#घोषणा CONF_HAS(config, val)	((config) & (1 << (val)))
#घोषणा CONF_MSK(config, mask)	((config) & (mask))
#घोषणा MSK_RANGE(low, hi)	((1 << ((hi)+1)) - (1 << (low)))
#घोषणा CONF_RANGE(config, low, hi) (CONF_MSK(config, MSK_RANGE(low, high)))

#घोषणा CONF_IS(config, val)	((config) == (1 << (val)))
#घोषणा CONF_GE(config, val)	((config) & (0-(1 << (val))))
#घोषणा CONF_GT(config, val)	((config) & (0-2*(1 << (val))))
#घोषणा CONF_LT(config, val)	((config) & ((1 << (val))-1))
#घोषणा CONF_LE(config, val)	((config) & (2*(1 << (val))-1))

/* Wrappers क्रम some of the above, specअगरic to config स्थिरants */

#घोषणा NCONF_HAS(val)	CONF_HAS(NCONF, val)
#घोषणा NCONF_MSK(mask)	CONF_MSK(NCONF, mask)
#घोषणा NCONF_IS(val)	CONF_IS(NCONF, val)
#घोषणा NCONF_GE(val)	CONF_GE(NCONF, val)
#घोषणा NCONF_GT(val)	CONF_GT(NCONF, val)
#घोषणा NCONF_LT(val)	CONF_LT(NCONF, val)
#घोषणा NCONF_LE(val)	CONF_LE(NCONF, val)

#घोषणा LCNCONF_HAS(val)	CONF_HAS(LCNCONF, val)
#घोषणा LCNCONF_MSK(mask)	CONF_MSK(LCNCONF, mask)
#घोषणा LCNCONF_IS(val)		CONF_IS(LCNCONF, val)
#घोषणा LCNCONF_GE(val)		CONF_GE(LCNCONF, val)
#घोषणा LCNCONF_GT(val)		CONF_GT(LCNCONF, val)
#घोषणा LCNCONF_LT(val)		CONF_LT(LCNCONF, val)
#घोषणा LCNCONF_LE(val)		CONF_LE(LCNCONF, val)

#घोषणा D11CONF_HAS(val) CONF_HAS(D11CONF, val)
#घोषणा D11CONF_MSK(mask) CONF_MSK(D11CONF, mask)
#घोषणा D11CONF_IS(val)	CONF_IS(D11CONF, val)
#घोषणा D11CONF_GE(val)	CONF_GE(D11CONF, val)
#घोषणा D11CONF_GT(val)	CONF_GT(D11CONF, val)
#घोषणा D11CONF_LT(val)	CONF_LT(D11CONF, val)
#घोषणा D11CONF_LE(val)	CONF_LE(D11CONF, val)

#घोषणा PHYCONF_HAS(val) CONF_HAS(PHYTYPE, val)
#घोषणा PHYCONF_IS(val)	CONF_IS(PHYTYPE, val)

#घोषणा NREV_IS(var, val) \
	(NCONF_HAS(val) && (NCONF_IS(val) || ((var) == (val))))

#घोषणा NREV_GE(var, val) \
	(NCONF_GE(val) && (!NCONF_LT(val) || ((var) >= (val))))

#घोषणा NREV_GT(var, val) \
	(NCONF_GT(val) && (!NCONF_LE(val) || ((var) > (val))))

#घोषणा NREV_LT(var, val) \
	(NCONF_LT(val) && (!NCONF_GE(val) || ((var) < (val))))

#घोषणा NREV_LE(var, val) \
	(NCONF_LE(val) && (!NCONF_GT(val) || ((var) <= (val))))

#घोषणा LCNREV_IS(var, val) \
	(LCNCONF_HAS(val) && (LCNCONF_IS(val) || ((var) == (val))))

#घोषणा LCNREV_GE(var, val) \
	(LCNCONF_GE(val) && (!LCNCONF_LT(val) || ((var) >= (val))))

#घोषणा LCNREV_GT(var, val) \
	(LCNCONF_GT(val) && (!LCNCONF_LE(val) || ((var) > (val))))

#घोषणा LCNREV_LT(var, val) \
	(LCNCONF_LT(val) && (!LCNCONF_GE(val) || ((var) < (val))))

#घोषणा LCNREV_LE(var, val) \
	(LCNCONF_LE(val) && (!LCNCONF_GT(val) || ((var) <= (val))))

#घोषणा D11REV_IS(var, val) \
	(D11CONF_HAS(val) && (D11CONF_IS(val) || ((var) == (val))))

#घोषणा D11REV_GE(var, val) \
	(D11CONF_GE(val) && (!D11CONF_LT(val) || ((var) >= (val))))

#घोषणा D11REV_GT(var, val) \
	(D11CONF_GT(val) && (!D11CONF_LE(val) || ((var) > (val))))

#घोषणा D11REV_LT(var, val) \
	(D11CONF_LT(val) && (!D11CONF_GE(val) || ((var) < (val))))

#घोषणा D11REV_LE(var, val) \
	(D11CONF_LE(val) && (!D11CONF_GT(val) || ((var) <= (val))))

#घोषणा PHYTYPE_IS(var, val)\
	(PHYCONF_HAS(val) && (PHYCONF_IS(val) || ((var) == (val))))

/* Set up PHYTYPE स्वतःmatically: (depends on PHY_TYPE_X, from d11.h) */

#घोषणा _PHYCONF_N (1 << PHY_TYPE_N)
#घोषणा _PHYCONF_LCN (1 << PHY_TYPE_LCN)
#घोषणा _PHYCONF_SSLPN (1 << PHY_TYPE_SSN)

#घोषणा PHYTYPE (_PHYCONF_N | _PHYCONF_LCN | _PHYCONF_SSLPN)

/* Utility macro to identअगरy 802.11n (HT) capable PHYs */
#घोषणा PHYTYPE_11N_CAP(phytype) \
	(PHYTYPE_IS(phytype, PHY_TYPE_N) ||	\
	 PHYTYPE_IS(phytype, PHY_TYPE_LCN) || \
	 PHYTYPE_IS(phytype, PHY_TYPE_SSN))

/* Last but not least: लघुer wlc-specअगरic var checks */
#घोषणा BRCMS_ISNPHY(band)		PHYTYPE_IS((band)->phytype, PHY_TYPE_N)
#घोषणा BRCMS_ISLCNPHY(band)	PHYTYPE_IS((band)->phytype, PHY_TYPE_LCN)
#घोषणा BRCMS_ISSSLPNPHY(band)	PHYTYPE_IS((band)->phytype, PHY_TYPE_SSN)

#घोषणा BRCMS_PHY_11N_CAP(band)	PHYTYPE_11N_CAP((band)->phytype)

/**********************************************************************
 * ------------- End of Core phy/rev configuration. ----------------- *
 * ********************************************************************
 */

#घोषणा BCMMSG(dev, fmt, args...)		\
करो अणु						\
	अगर (brcm_msg_level & BRCM_DL_INFO)	\
		wiphy_err(dev, "%s: " fmt, __func__, ##args);	\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_BCM47XX
/*
 * bcm4716 (which includes 4717 & 4718), plus 4706 on PCIe can reorder
 * transactions. As a fix, a पढ़ो after ग_लिखो is perक्रमmed on certain places
 * in the code. Older chips and the newer 5357 family करोn't require this fix.
 */
#घोषणा bcma_wflush16(c, o, v) \
	(अणु bcma_ग_लिखो16(c, o, v); (व्योम)bcma_पढ़ो16(c, o); पूर्ण)
#अन्यथा
#घोषणा bcma_wflush16(c, o, v)	bcma_ग_लिखो16(c, o, v)
#पूर्ण_अगर				/* CONFIG_BCM47XX */

/* multi-bool data type: set of bools, mbool is true अगर any is set */

/* set one bool */
#घोषणा mboolset(mb, bit)		((mb) |= (bit))
/* clear one bool */
#घोषणा mboolclr(mb, bit)		((mb) &= ~(bit))
/* true अगर one bool is set */
#घोषणा mboolisset(mb, bit)		(((mb) & (bit)) != 0)
#घोषणा	mboolmaskset(mb, mask, val)	((mb) = (((mb) & ~(mask)) | (val)))

#घोषणा CEIL(x, y)		(((x) + ((y)-1)) / (y))

/* क्रमward declarations */
काष्ठा wiphy;
काष्ठा ieee80211_sta;
काष्ठा ieee80211_tx_queue_params;
काष्ठा brcms_info;
काष्ठा brcms_c_info;
काष्ठा brcms_hardware;
काष्ठा brcms_band;
काष्ठा dma_pub;
काष्ठा si_pub;
काष्ठा tx_status;
काष्ठा d11rxhdr;
काष्ठा txpwr_limits;

/* iovar काष्ठाure */
काष्ठा brcmu_iovar अणु
	स्थिर अक्षर *name;	/* name क्रम lookup and display */
	u16 varid;	/* id क्रम चयन */
	u16 flags;	/* driver-specअगरic flag bits */
	u16 type;	/* base type of argument */
	u16 minlen;	/* min length क्रम buffer vars */
पूर्ण;

/* brcm_msg_level is a bit vector with defs in defs.h */
बाह्य u32 brcm_msg_level;

#पूर्ण_अगर				/* _BRCM_TYPES_H_ */
