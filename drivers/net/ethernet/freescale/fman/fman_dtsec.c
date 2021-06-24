<शैली गुरु>
/*
 * Copyright 2008-2015 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "fman_dtsec.h"
#समावेश "fman.h"

#समावेश <linux/slab.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/phy.h>
#समावेश <linux/crc32.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/mii.h>

/* TBI रेजिस्टर addresses */
#घोषणा MII_TBICON		0x11

/* TBICON रेजिस्टर bit fields */
#घोषणा TBICON_SOFT_RESET	0x8000	/* Soft reset */
#घोषणा TBICON_DISABLE_RX_DIS	0x2000	/* Disable receive disparity */
#घोषणा TBICON_DISABLE_TX_DIS	0x1000	/* Disable transmit disparity */
#घोषणा TBICON_AN_SENSE		0x0100	/* Auto-negotiation sense enable */
#घोषणा TBICON_CLK_SELECT	0x0020	/* Clock select */
#घोषणा TBICON_MI_MODE		0x0010	/* GMII mode (TBI अगर not set) */

#घोषणा TBIANA_SGMII		0x4001
#घोषणा TBIANA_1000X		0x01a0

/* Interrupt Mask Register (IMASK) */
#घोषणा DTSEC_IMASK_BREN	0x80000000
#घोषणा DTSEC_IMASK_RXCEN	0x40000000
#घोषणा DTSEC_IMASK_MSROEN	0x04000000
#घोषणा DTSEC_IMASK_GTSCEN	0x02000000
#घोषणा DTSEC_IMASK_BTEN	0x01000000
#घोषणा DTSEC_IMASK_TXCEN	0x00800000
#घोषणा DTSEC_IMASK_TXEEN	0x00400000
#घोषणा DTSEC_IMASK_LCEN	0x00040000
#घोषणा DTSEC_IMASK_CRLEN	0x00020000
#घोषणा DTSEC_IMASK_XFUNEN	0x00010000
#घोषणा DTSEC_IMASK_ABRTEN	0x00008000
#घोषणा DTSEC_IMASK_IFERREN	0x00004000
#घोषणा DTSEC_IMASK_MAGEN	0x00000800
#घोषणा DTSEC_IMASK_MMRDEN	0x00000400
#घोषणा DTSEC_IMASK_MMWREN	0x00000200
#घोषणा DTSEC_IMASK_GRSCEN	0x00000100
#घोषणा DTSEC_IMASK_TDPEEN	0x00000002
#घोषणा DTSEC_IMASK_RDPEEN	0x00000001

#घोषणा DTSEC_EVENTS_MASK		\
	 ((u32)(DTSEC_IMASK_BREN    |	\
		DTSEC_IMASK_RXCEN   |	\
		DTSEC_IMASK_BTEN    |	\
		DTSEC_IMASK_TXCEN   |	\
		DTSEC_IMASK_TXEEN   |	\
		DTSEC_IMASK_ABRTEN  |	\
		DTSEC_IMASK_LCEN    |	\
		DTSEC_IMASK_CRLEN   |	\
		DTSEC_IMASK_XFUNEN  |	\
		DTSEC_IMASK_IFERREN |	\
		DTSEC_IMASK_MAGEN   |	\
		DTSEC_IMASK_TDPEEN  |	\
		DTSEC_IMASK_RDPEEN))

/* dtsec बारtamp event bits */
#घोषणा TMR_PEMASK_TSREEN	0x00010000
#घोषणा TMR_PEVENT_TSRE		0x00010000

/* Group address bit indication */
#घोषणा MAC_GROUP_ADDRESS	0x0000010000000000ULL

/* Defaults */
#घोषणा DEFAULT_HALFDUP_RETRANSMIT		0xf
#घोषणा DEFAULT_HALFDUP_COLL_WINDOW		0x37
#घोषणा DEFAULT_TX_PAUSE_TIME			0xf000
#घोषणा DEFAULT_RX_PREPEND			0
#घोषणा DEFAULT_PREAMBLE_LEN			7
#घोषणा DEFAULT_TX_PAUSE_TIME_EXTD		0
#घोषणा DEFAULT_NON_BACK_TO_BACK_IPG1		0x40
#घोषणा DEFAULT_NON_BACK_TO_BACK_IPG2		0x60
#घोषणा DEFAULT_MIN_IFG_ENFORCEMENT		0x50
#घोषणा DEFAULT_BACK_TO_BACK_IPG		0x60
#घोषणा DEFAULT_MAXIMUM_FRAME			0x600

/* रेजिस्टर related defines (bits, field offsets..) */
#घोषणा DTSEC_ID2_INT_REDUCED_OFF	0x00010000

#घोषणा DTSEC_ECNTRL_GMIIM		0x00000040
#घोषणा DTSEC_ECNTRL_TBIM		0x00000020
#घोषणा DTSEC_ECNTRL_SGMIIM		0x00000002
#घोषणा DTSEC_ECNTRL_RPM		0x00000010
#घोषणा DTSEC_ECNTRL_R100M		0x00000008
#घोषणा DTSEC_ECNTRL_QSGMIIM		0x00000001

#घोषणा TCTRL_TTSE			0x00000040
#घोषणा TCTRL_GTS			0x00000020

#घोषणा RCTRL_PAL_MASK			0x001f0000
#घोषणा RCTRL_PAL_SHIFT			16
#घोषणा RCTRL_GHTX			0x00000400
#घोषणा RCTRL_RTSE			0x00000040
#घोषणा RCTRL_GRS			0x00000020
#घोषणा RCTRL_MPROM			0x00000008
#घोषणा RCTRL_RSF			0x00000004
#घोषणा RCTRL_UPROM			0x00000001

#घोषणा MACCFG1_SOFT_RESET		0x80000000
#घोषणा MACCFG1_RX_FLOW			0x00000020
#घोषणा MACCFG1_TX_FLOW			0x00000010
#घोषणा MACCFG1_TX_EN			0x00000001
#घोषणा MACCFG1_RX_EN			0x00000004

#घोषणा MACCFG2_NIBBLE_MODE		0x00000100
#घोषणा MACCFG2_BYTE_MODE		0x00000200
#घोषणा MACCFG2_PAD_CRC_EN		0x00000004
#घोषणा MACCFG2_FULL_DUPLEX		0x00000001
#घोषणा MACCFG2_PREAMBLE_LENGTH_MASK	0x0000f000
#घोषणा MACCFG2_PREAMBLE_LENGTH_SHIFT	12

#घोषणा IPGIFG_NON_BACK_TO_BACK_IPG_1_SHIFT	24
#घोषणा IPGIFG_NON_BACK_TO_BACK_IPG_2_SHIFT	16
#घोषणा IPGIFG_MIN_IFG_ENFORCEMENT_SHIFT	8

#घोषणा IPGIFG_NON_BACK_TO_BACK_IPG_1	0x7F000000
#घोषणा IPGIFG_NON_BACK_TO_BACK_IPG_2	0x007F0000
#घोषणा IPGIFG_MIN_IFG_ENFORCEMENT	0x0000FF00
#घोषणा IPGIFG_BACK_TO_BACK_IPG	0x0000007F

#घोषणा HAFDUP_EXCESS_DEFER			0x00010000
#घोषणा HAFDUP_COLLISION_WINDOW		0x000003ff
#घोषणा HAFDUP_RETRANSMISSION_MAX_SHIFT	12
#घोषणा HAFDUP_RETRANSMISSION_MAX		0x0000f000

#घोषणा NUM_OF_HASH_REGS	8	/* Number of hash table रेजिस्टरs */

#घोषणा PTV_PTE_MASK		0xffff0000
#घोषणा PTV_PT_MASK		0x0000ffff
#घोषणा PTV_PTE_SHIFT		16

#घोषणा MAX_PACKET_ALIGNMENT		31
#घोषणा MAX_INTER_PACKET_GAP		0x7f
#घोषणा MAX_RETRANSMISSION		0x0f
#घोषणा MAX_COLLISION_WINDOW		0x03ff

/* Hash table size (32 bits*8 regs) */
#घोषणा DTSEC_HASH_TABLE_SIZE		256
/* Extended Hash table size (32 bits*16 regs) */
#घोषणा EXTENDED_HASH_TABLE_SIZE	512

/* dTSEC Memory Map रेजिस्टरs */
काष्ठा dtsec_regs अणु
	/* dTSEC General Control and Status Registers */
	u32 tsec_id;		/* 0x000 ETSEC_ID रेजिस्टर */
	u32 tsec_id2;		/* 0x004 ETSEC_ID2 रेजिस्टर */
	u32 ievent;		/* 0x008 Interrupt event रेजिस्टर */
	u32 imask;		/* 0x00C Interrupt mask रेजिस्टर */
	u32 reserved0010[1];
	u32 ecntrl;		/* 0x014 E control रेजिस्टर */
	u32 ptv;		/* 0x018 Pause समय value रेजिस्टर */
	u32 tbipa;		/* 0x01C TBI PHY address रेजिस्टर */
	u32 पंचांगr_ctrl;		/* 0x020 Time-stamp Control रेजिस्टर */
	u32 पंचांगr_pevent;		/* 0x024 Time-stamp event रेजिस्टर */
	u32 पंचांगr_pemask;		/* 0x028 Timer event mask रेजिस्टर */
	u32 reserved002c[5];
	u32 tctrl;		/* 0x040 Transmit control रेजिस्टर */
	u32 reserved0044[3];
	u32 rctrl;		/* 0x050 Receive control रेजिस्टर */
	u32 reserved0054[11];
	u32 igaddr[8];		/* 0x080-0x09C Inभागidual/group address */
	u32 gaddr[8];		/* 0x0A0-0x0BC Group address रेजिस्टरs 0-7 */
	u32 reserved00c0[16];
	u32 maccfg1;		/* 0x100 MAC configuration #1 */
	u32 maccfg2;		/* 0x104 MAC configuration #2 */
	u32 ipgअगरg;		/* 0x108 IPG/IFG */
	u32 hafdup;		/* 0x10C Half-duplex */
	u32 maxfrm;		/* 0x110 Maximum frame */
	u32 reserved0114[10];
	u32 अगरstat;		/* 0x13C Interface status */
	u32 macstnaddr1;	/* 0x140 Station Address,part 1 */
	u32 macstnaddr2;	/* 0x144 Station Address,part 2 */
	काष्ठा अणु
		u32 exact_match1;	/* octets 1-4 */
		u32 exact_match2;	/* octets 5-6 */
	पूर्ण macaddr[15];		/* 0x148-0x1BC mac exact match addresses 1-15 */
	u32 reserved01c0[16];
	u32 tr64;	/* 0x200 Tx and Rx 64 byte frame counter */
	u32 tr127;	/* 0x204 Tx and Rx 65 to 127 byte frame counter */
	u32 tr255;	/* 0x208 Tx and Rx 128 to 255 byte frame counter */
	u32 tr511;	/* 0x20C Tx and Rx 256 to 511 byte frame counter */
	u32 tr1k;	/* 0x210 Tx and Rx 512 to 1023 byte frame counter */
	u32 trmax;	/* 0x214 Tx and Rx 1024 to 1518 byte frame counter */
	u32 trmgv;
	/* 0x218 Tx and Rx 1519 to 1522 byte good VLAN frame count */
	u32 rbyt;	/* 0x21C receive byte counter */
	u32 rpkt;	/* 0x220 receive packet counter */
	u32 rfcs;	/* 0x224 receive FCS error counter */
	u32 rmca;	/* 0x228 RMCA Rx multicast packet counter */
	u32 rbca;	/* 0x22C Rx broadcast packet counter */
	u32 rxcf;	/* 0x230 Rx control frame packet counter */
	u32 rxpf;	/* 0x234 Rx छोड़ो frame packet counter */
	u32 rxuo;	/* 0x238 Rx unknown OP code counter */
	u32 raln;	/* 0x23C Rx alignment error counter */
	u32 rflr;	/* 0x240 Rx frame length error counter */
	u32 rcde;	/* 0x244 Rx code error counter */
	u32 rcse;	/* 0x248 Rx carrier sense error counter */
	u32 rund;	/* 0x24C Rx undersize packet counter */
	u32 rovr;	/* 0x250 Rx oversize packet counter */
	u32 rfrg;	/* 0x254 Rx fragments counter */
	u32 rjbr;	/* 0x258 Rx jabber counter */
	u32 rdrp;	/* 0x25C Rx drop */
	u32 tbyt;	/* 0x260 Tx byte counter */
	u32 tpkt;	/* 0x264 Tx packet counter */
	u32 पंचांगca;	/* 0x268 Tx multicast packet counter */
	u32 tbca;	/* 0x26C Tx broadcast packet counter */
	u32 txpf;	/* 0x270 Tx छोड़ो control frame counter */
	u32 tdfr;	/* 0x274 Tx deferral packet counter */
	u32 tedf;	/* 0x278 Tx excessive deferral packet counter */
	u32 tscl;	/* 0x27C Tx single collision packet counter */
	u32 पंचांगcl;	/* 0x280 Tx multiple collision packet counter */
	u32 tlcl;	/* 0x284 Tx late collision packet counter */
	u32 txcl;	/* 0x288 Tx excessive collision packet counter */
	u32 tncl;	/* 0x28C Tx total collision counter */
	u32 reserved0290[1];
	u32 tdrp;	/* 0x294 Tx drop frame counter */
	u32 tjbr;	/* 0x298 Tx jabber frame counter */
	u32 tfcs;	/* 0x29C Tx FCS error counter */
	u32 txcf;	/* 0x2A0 Tx control frame counter */
	u32 tovr;	/* 0x2A4 Tx oversize frame counter */
	u32 tund;	/* 0x2A8 Tx undersize frame counter */
	u32 tfrg;	/* 0x2AC Tx fragments frame counter */
	u32 car1;	/* 0x2B0 carry रेजिस्टर one रेजिस्टर* */
	u32 car2;	/* 0x2B4 carry रेजिस्टर two रेजिस्टर* */
	u32 cam1;	/* 0x2B8 carry रेजिस्टर one mask रेजिस्टर */
	u32 cam2;	/* 0x2BC carry रेजिस्टर two mask रेजिस्टर */
	u32 reserved02c0[848];
पूर्ण;

/* काष्ठा dtsec_cfg - dTSEC configuration
 * Transmit half-duplex flow control, under software control क्रम 10/100-Mbps
 * half-duplex media. If set, back pressure is applied to media by raising
 * carrier.
 * halfdup_retransmit:
 * Number of retransmission attempts following a collision.
 * If this is exceeded dTSEC पातs transmission due to excessive collisions.
 * The standard specअगरies the attempt limit to be 15.
 * halfdup_coll_winकरोw:
 * The number of bytes of the frame during which collisions may occur.
 * The शेष value of 55 corresponds to the frame byte at the end of the
 * standard 512-bit slot समय winकरोw. If collisions are detected after this
 * byte, the late collision event is निश्चितed and transmission of current
 * frame is पातed.
 * tx_pad_crc:
 * Pad and append CRC. If set, the MAC pads all ransmitted लघु frames and
 * appends a CRC to every frame regardless of padding requirement.
 * tx_छोड़ो_समय:
 * Transmit छोड़ो समय value. This छोड़ो value is used as part of the छोड़ो
 * frame to be sent when a transmit छोड़ो frame is initiated.
 * If set to 0 this disables transmission of छोड़ो frames.
 * preamble_len:
 * Length, in bytes, of the preamble field preceding each Ethernet
 * start-of-frame delimiter byte. The शेष value of 0x7 should be used in
 * order to guarantee reliable operation with IEEE 802.3 compliant hardware.
 * rx_prepend:
 * Packet alignment padding length. The specअगरied number of bytes (1-31)
 * of zero padding are inserted beक्रमe the start of each received frame.
 * For Ethernet, where optional preamble extraction is enabled, the padding
 * appears beक्रमe the preamble, otherwise the padding precedes the
 * layer 2 header.
 *
 * This काष्ठाure contains basic dTSEC configuration and must be passed to
 * init() function. A शेष set of configuration values can be
 * obtained by calling set_dflts().
 */
काष्ठा dtsec_cfg अणु
	u16 halfdup_retransmit;
	u16 halfdup_coll_winकरोw;
	bool tx_pad_crc;
	u16 tx_छोड़ो_समय;
	bool ptp_tsu_en;
	bool ptp_exception_en;
	u32 preamble_len;
	u32 rx_prepend;
	u16 tx_छोड़ो_समय_extd;
	u16 maximum_frame;
	u32 non_back_to_back_ipg1;
	u32 non_back_to_back_ipg2;
	u32 min_अगरg_enक्रमcement;
	u32 back_to_back_ipg;
पूर्ण;

काष्ठा fman_mac अणु
	/* poपूर्णांकer to dTSEC memory mapped रेजिस्टरs */
	काष्ठा dtsec_regs __iomem *regs;
	/* MAC address of device */
	u64 addr;
	/* Ethernet physical पूर्णांकerface */
	phy_पूर्णांकerface_t phy_अगर;
	u16 max_speed;
	व्योम *dev_id; /* device cookie used by the exception cbs */
	fman_mac_exception_cb *exception_cb;
	fman_mac_exception_cb *event_cb;
	/* Number of inभागidual addresses in रेजिस्टरs क्रम this station */
	u8 num_of_ind_addr_in_regs;
	/* poपूर्णांकer to driver's global address hash table */
	काष्ठा eth_hash_t *multicast_addr_hash;
	/* poपूर्णांकer to driver's inभागidual address hash table */
	काष्ठा eth_hash_t *unicast_addr_hash;
	u8 mac_id;
	u32 exceptions;
	bool ptp_tsu_enabled;
	bool en_tsu_err_exception;
	काष्ठा dtsec_cfg *dtsec_drv_param;
	व्योम *fm;
	काष्ठा fman_rev_info fm_rev_info;
	bool basex_अगर;
	काष्ठा phy_device *tbiphy;
पूर्ण;

अटल व्योम set_dflts(काष्ठा dtsec_cfg *cfg)
अणु
	cfg->halfdup_retransmit = DEFAULT_HALFDUP_RETRANSMIT;
	cfg->halfdup_coll_winकरोw = DEFAULT_HALFDUP_COLL_WINDOW;
	cfg->tx_pad_crc = true;
	cfg->tx_छोड़ो_समय = DEFAULT_TX_PAUSE_TIME;
	/* PHY address 0 is reserved (DPAA RM) */
	cfg->rx_prepend = DEFAULT_RX_PREPEND;
	cfg->ptp_tsu_en = true;
	cfg->ptp_exception_en = true;
	cfg->preamble_len = DEFAULT_PREAMBLE_LEN;
	cfg->tx_छोड़ो_समय_extd = DEFAULT_TX_PAUSE_TIME_EXTD;
	cfg->non_back_to_back_ipg1 = DEFAULT_NON_BACK_TO_BACK_IPG1;
	cfg->non_back_to_back_ipg2 = DEFAULT_NON_BACK_TO_BACK_IPG2;
	cfg->min_अगरg_enक्रमcement = DEFAULT_MIN_IFG_ENFORCEMENT;
	cfg->back_to_back_ipg = DEFAULT_BACK_TO_BACK_IPG;
	cfg->maximum_frame = DEFAULT_MAXIMUM_FRAME;
पूर्ण

अटल व्योम set_mac_address(काष्ठा dtsec_regs __iomem *regs, u8 *adr)
अणु
	u32 पंचांगp;

	पंचांगp = (u32)((adr[5] << 24) |
		    (adr[4] << 16) | (adr[3] << 8) | adr[2]);
	ioग_लिखो32be(पंचांगp, &regs->macstnaddr1);

	पंचांगp = (u32)((adr[1] << 24) | (adr[0] << 16));
	ioग_लिखो32be(पंचांगp, &regs->macstnaddr2);
पूर्ण

अटल पूर्णांक init(काष्ठा dtsec_regs __iomem *regs, काष्ठा dtsec_cfg *cfg,
		phy_पूर्णांकerface_t अगरace, u16 अगरace_speed, u64 addr,
		u32 exception_mask, u8 tbi_addr)
अणु
	bool is_rgmii, is_sgmii, is_qsgmii;
	enet_addr_t eth_addr;
	u32 पंचांगp;
	पूर्णांक i;

	/* Soft reset */
	ioग_लिखो32be(MACCFG1_SOFT_RESET, &regs->maccfg1);
	ioग_लिखो32be(0, &regs->maccfg1);

	/* dtsec_id2 */
	पंचांगp = ioपढ़ो32be(&regs->tsec_id2);

	/* check RGMII support */
	अगर (अगरace == PHY_INTERFACE_MODE_RGMII ||
	    अगरace == PHY_INTERFACE_MODE_RGMII_ID ||
	    अगरace == PHY_INTERFACE_MODE_RGMII_RXID ||
	    अगरace == PHY_INTERFACE_MODE_RGMII_TXID ||
	    अगरace == PHY_INTERFACE_MODE_RMII)
		अगर (पंचांगp & DTSEC_ID2_INT_REDUCED_OFF)
			वापस -EINVAL;

	अगर (अगरace == PHY_INTERFACE_MODE_SGMII ||
	    अगरace == PHY_INTERFACE_MODE_MII)
		अगर (पंचांगp & DTSEC_ID2_INT_REDUCED_OFF)
			वापस -EINVAL;

	is_rgmii = अगरace == PHY_INTERFACE_MODE_RGMII ||
		   अगरace == PHY_INTERFACE_MODE_RGMII_ID ||
		   अगरace == PHY_INTERFACE_MODE_RGMII_RXID ||
		   अगरace == PHY_INTERFACE_MODE_RGMII_TXID;
	is_sgmii = अगरace == PHY_INTERFACE_MODE_SGMII;
	is_qsgmii = अगरace == PHY_INTERFACE_MODE_QSGMII;

	पंचांगp = 0;
	अगर (is_rgmii || अगरace == PHY_INTERFACE_MODE_GMII)
		पंचांगp |= DTSEC_ECNTRL_GMIIM;
	अगर (is_sgmii)
		पंचांगp |= (DTSEC_ECNTRL_SGMIIM | DTSEC_ECNTRL_TBIM);
	अगर (is_qsgmii)
		पंचांगp |= (DTSEC_ECNTRL_SGMIIM | DTSEC_ECNTRL_TBIM |
			DTSEC_ECNTRL_QSGMIIM);
	अगर (is_rgmii)
		पंचांगp |= DTSEC_ECNTRL_RPM;
	अगर (अगरace_speed == SPEED_100)
		पंचांगp |= DTSEC_ECNTRL_R100M;

	ioग_लिखो32be(पंचांगp, &regs->ecntrl);

	पंचांगp = 0;

	अगर (cfg->tx_छोड़ो_समय)
		पंचांगp |= cfg->tx_छोड़ो_समय;
	अगर (cfg->tx_छोड़ो_समय_extd)
		पंचांगp |= cfg->tx_छोड़ो_समय_extd << PTV_PTE_SHIFT;
	ioग_लिखो32be(पंचांगp, &regs->ptv);

	पंचांगp = 0;
	पंचांगp |= (cfg->rx_prepend << RCTRL_PAL_SHIFT) & RCTRL_PAL_MASK;
	/* Accept लघु frames */
	पंचांगp |= RCTRL_RSF;

	ioग_लिखो32be(पंचांगp, &regs->rctrl);

	/* Assign a Phy Address to the TBI (TBIPA).
	 * Done also in हालs where TBI is not selected to aव्योम conflict with
	 * the बाह्यal PHY's Physical address
	 */
	ioग_लिखो32be(tbi_addr, &regs->tbipa);

	ioग_लिखो32be(0, &regs->पंचांगr_ctrl);

	अगर (cfg->ptp_tsu_en) अणु
		पंचांगp = 0;
		पंचांगp |= TMR_PEVENT_TSRE;
		ioग_लिखो32be(पंचांगp, &regs->पंचांगr_pevent);

		अगर (cfg->ptp_exception_en) अणु
			पंचांगp = 0;
			पंचांगp |= TMR_PEMASK_TSREEN;
			ioग_लिखो32be(पंचांगp, &regs->पंचांगr_pemask);
		पूर्ण
	पूर्ण

	पंचांगp = 0;
	पंचांगp |= MACCFG1_RX_FLOW;
	पंचांगp |= MACCFG1_TX_FLOW;
	ioग_लिखो32be(पंचांगp, &regs->maccfg1);

	पंचांगp = 0;

	अगर (अगरace_speed < SPEED_1000)
		पंचांगp |= MACCFG2_NIBBLE_MODE;
	अन्यथा अगर (अगरace_speed == SPEED_1000)
		पंचांगp |= MACCFG2_BYTE_MODE;

	पंचांगp |= (cfg->preamble_len << MACCFG2_PREAMBLE_LENGTH_SHIFT) &
		MACCFG2_PREAMBLE_LENGTH_MASK;
	अगर (cfg->tx_pad_crc)
		पंचांगp |= MACCFG2_PAD_CRC_EN;
	/* Full Duplex */
	पंचांगp |= MACCFG2_FULL_DUPLEX;
	ioग_लिखो32be(पंचांगp, &regs->maccfg2);

	पंचांगp = (((cfg->non_back_to_back_ipg1 <<
		 IPGIFG_NON_BACK_TO_BACK_IPG_1_SHIFT)
		& IPGIFG_NON_BACK_TO_BACK_IPG_1)
	       | ((cfg->non_back_to_back_ipg2 <<
		   IPGIFG_NON_BACK_TO_BACK_IPG_2_SHIFT)
		 & IPGIFG_NON_BACK_TO_BACK_IPG_2)
	       | ((cfg->min_अगरg_enक्रमcement << IPGIFG_MIN_IFG_ENFORCEMENT_SHIFT)
		 & IPGIFG_MIN_IFG_ENFORCEMENT)
	       | (cfg->back_to_back_ipg & IPGIFG_BACK_TO_BACK_IPG));
	ioग_लिखो32be(पंचांगp, &regs->ipgअगरg);

	पंचांगp = 0;
	पंचांगp |= HAFDUP_EXCESS_DEFER;
	पंचांगp |= ((cfg->halfdup_retransmit << HAFDUP_RETRANSMISSION_MAX_SHIFT)
		& HAFDUP_RETRANSMISSION_MAX);
	पंचांगp |= (cfg->halfdup_coll_winकरोw & HAFDUP_COLLISION_WINDOW);

	ioग_लिखो32be(पंचांगp, &regs->hafdup);

	/* Initialize Maximum frame length */
	ioग_लिखो32be(cfg->maximum_frame, &regs->maxfrm);

	ioग_लिखो32be(0xffffffff, &regs->cam1);
	ioग_लिखो32be(0xffffffff, &regs->cam2);

	ioग_लिखो32be(exception_mask, &regs->imask);

	ioग_लिखो32be(0xffffffff, &regs->ievent);

	अगर (addr) अणु
		MAKE_ENET_ADDR_FROM_UINT64(addr, eth_addr);
		set_mac_address(regs, (u8 *)eth_addr);
	पूर्ण

	/* HASH */
	क्रम (i = 0; i < NUM_OF_HASH_REGS; i++) अणु
		/* Initialize IADDRx */
		ioग_लिखो32be(0, &regs->igaddr[i]);
		/* Initialize GADDRx */
		ioग_लिखो32be(0, &regs->gaddr[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_bucket(काष्ठा dtsec_regs __iomem *regs, पूर्णांक bucket,
		       bool enable)
अणु
	पूर्णांक reg_idx = (bucket >> 5) & 0xf;
	पूर्णांक bit_idx = bucket & 0x1f;
	u32 bit_mask = 0x80000000 >> bit_idx;
	u32 __iomem *reg;

	अगर (reg_idx > 7)
		reg = &regs->gaddr[reg_idx - 8];
	अन्यथा
		reg = &regs->igaddr[reg_idx];

	अगर (enable)
		ioग_लिखो32be(ioपढ़ो32be(reg) | bit_mask, reg);
	अन्यथा
		ioग_लिखो32be(ioपढ़ो32be(reg) & (~bit_mask), reg);
पूर्ण

अटल पूर्णांक check_init_parameters(काष्ठा fman_mac *dtsec)
अणु
	अगर (dtsec->max_speed >= SPEED_10000) अणु
		pr_err("1G MAC driver supports 1G or lower speeds\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((dtsec->dtsec_drv_param)->rx_prepend >
	    MAX_PACKET_ALIGNMENT) अणु
		pr_err("packetAlignmentPadding can't be > than %d\n",
		       MAX_PACKET_ALIGNMENT);
		वापस -EINVAL;
	पूर्ण
	अगर (((dtsec->dtsec_drv_param)->non_back_to_back_ipg1 >
	     MAX_INTER_PACKET_GAP) ||
	    ((dtsec->dtsec_drv_param)->non_back_to_back_ipg2 >
	     MAX_INTER_PACKET_GAP) ||
	     ((dtsec->dtsec_drv_param)->back_to_back_ipg >
	      MAX_INTER_PACKET_GAP)) अणु
		pr_err("Inter packet gap can't be greater than %d\n",
		       MAX_INTER_PACKET_GAP);
		वापस -EINVAL;
	पूर्ण
	अगर ((dtsec->dtsec_drv_param)->halfdup_retransmit >
	    MAX_RETRANSMISSION) अणु
		pr_err("maxRetransmission can't be greater than %d\n",
		       MAX_RETRANSMISSION);
		वापस -EINVAL;
	पूर्ण
	अगर ((dtsec->dtsec_drv_param)->halfdup_coll_winकरोw >
	    MAX_COLLISION_WINDOW) अणु
		pr_err("collisionWindow can't be greater than %d\n",
		       MAX_COLLISION_WINDOW);
		वापस -EINVAL;
	/* If Auto negotiation process is disabled, need to set up the PHY
	 * using the MII Management Interface
	 */
	पूर्ण
	अगर (!dtsec->exception_cb) अणु
		pr_err("uninitialized exception_cb\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!dtsec->event_cb) अणु
		pr_err("uninitialized event_cb\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_exception_flag(क्रमागत fman_mac_exceptions exception)
अणु
	u32 bit_mask;

	चयन (exception) अणु
	हाल FM_MAC_EX_1G_BAB_RX:
		bit_mask = DTSEC_IMASK_BREN;
		अवरोध;
	हाल FM_MAC_EX_1G_RX_CTL:
		bit_mask = DTSEC_IMASK_RXCEN;
		अवरोध;
	हाल FM_MAC_EX_1G_GRATEFUL_TX_STP_COMPLET:
		bit_mask = DTSEC_IMASK_GTSCEN;
		अवरोध;
	हाल FM_MAC_EX_1G_BAB_TX:
		bit_mask = DTSEC_IMASK_BTEN;
		अवरोध;
	हाल FM_MAC_EX_1G_TX_CTL:
		bit_mask = DTSEC_IMASK_TXCEN;
		अवरोध;
	हाल FM_MAC_EX_1G_TX_ERR:
		bit_mask = DTSEC_IMASK_TXEEN;
		अवरोध;
	हाल FM_MAC_EX_1G_LATE_COL:
		bit_mask = DTSEC_IMASK_LCEN;
		अवरोध;
	हाल FM_MAC_EX_1G_COL_RET_LMT:
		bit_mask = DTSEC_IMASK_CRLEN;
		अवरोध;
	हाल FM_MAC_EX_1G_TX_FIFO_UNDRN:
		bit_mask = DTSEC_IMASK_XFUNEN;
		अवरोध;
	हाल FM_MAC_EX_1G_MAG_PCKT:
		bit_mask = DTSEC_IMASK_MAGEN;
		अवरोध;
	हाल FM_MAC_EX_1G_MII_MNG_RD_COMPLET:
		bit_mask = DTSEC_IMASK_MMRDEN;
		अवरोध;
	हाल FM_MAC_EX_1G_MII_MNG_WR_COMPLET:
		bit_mask = DTSEC_IMASK_MMWREN;
		अवरोध;
	हाल FM_MAC_EX_1G_GRATEFUL_RX_STP_COMPLET:
		bit_mask = DTSEC_IMASK_GRSCEN;
		अवरोध;
	हाल FM_MAC_EX_1G_DATA_ERR:
		bit_mask = DTSEC_IMASK_TDPEEN;
		अवरोध;
	हाल FM_MAC_EX_1G_RX_MIB_CNT_OVFL:
		bit_mask = DTSEC_IMASK_MSROEN;
		अवरोध;
	शेष:
		bit_mask = 0;
		अवरोध;
	पूर्ण

	वापस bit_mask;
पूर्ण

अटल bool is_init_करोne(काष्ठा dtsec_cfg *dtsec_drv_params)
अणु
	/* Checks अगर dTSEC driver parameters were initialized */
	अगर (!dtsec_drv_params)
		वापस true;

	वापस false;
पूर्ण

अटल u16 dtsec_get_max_frame_length(काष्ठा fman_mac *dtsec)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;

	अगर (is_init_करोne(dtsec->dtsec_drv_param))
		वापस 0;

	वापस (u16)ioपढ़ो32be(&regs->maxfrm);
पूर्ण

अटल व्योम dtsec_isr(व्योम *handle)
अणु
	काष्ठा fman_mac *dtsec = (काष्ठा fman_mac *)handle;
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	u32 event;

	/* करो not handle MDIO events */
	event = ioपढ़ो32be(&regs->ievent) &
		(u32)(~(DTSEC_IMASK_MMRDEN | DTSEC_IMASK_MMWREN));

	event &= ioपढ़ो32be(&regs->imask);

	ioग_लिखो32be(event, &regs->ievent);

	अगर (event & DTSEC_IMASK_BREN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_BAB_RX);
	अगर (event & DTSEC_IMASK_RXCEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_RX_CTL);
	अगर (event & DTSEC_IMASK_GTSCEN)
		dtsec->exception_cb(dtsec->dev_id,
				    FM_MAC_EX_1G_GRATEFUL_TX_STP_COMPLET);
	अगर (event & DTSEC_IMASK_BTEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_BAB_TX);
	अगर (event & DTSEC_IMASK_TXCEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_TX_CTL);
	अगर (event & DTSEC_IMASK_TXEEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_TX_ERR);
	अगर (event & DTSEC_IMASK_LCEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_LATE_COL);
	अगर (event & DTSEC_IMASK_CRLEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_COL_RET_LMT);
	अगर (event & DTSEC_IMASK_XFUNEN) अणु
		/* FM_TX_LOCKUP_ERRATA_DTSEC6 Errata workaround */
		अगर (dtsec->fm_rev_info.major == 2) अणु
			u32 tpkt1, पंचांगp_reg1, tpkt2, पंचांगp_reg2, i;
			/* a. Write 0x00E0_0C00 to DTSEC_ID
			 *	This is a पढ़ो only रेजिस्टर
			 * b. Read and save the value of TPKT
			 */
			tpkt1 = ioपढ़ो32be(&regs->tpkt);

			/* c. Read the रेजिस्टर at dTSEC address offset 0x32C */
			पंचांगp_reg1 = ioपढ़ो32be(&regs->reserved02c0[27]);

			/* d. Compare bits [9:15] to bits [25:31] of the
			 * रेजिस्टर at address offset 0x32C.
			 */
			अगर ((पंचांगp_reg1 & 0x007F0000) !=
				(पंचांगp_reg1 & 0x0000007F)) अणु
				/* If they are not equal, save the value of
				 * this रेजिस्टर and रुको क्रम at least
				 * MAXFRM*16 ns
				 */
				usleep_range((u32)(min
					(dtsec_get_max_frame_length(dtsec) *
					16 / 1000, 1)), (u32)
					(min(dtsec_get_max_frame_length
					(dtsec) * 16 / 1000, 1) + 1));
			पूर्ण

			/* e. Read and save TPKT again and पढ़ो the रेजिस्टर
			 * at dTSEC address offset 0x32C again
			 */
			tpkt2 = ioपढ़ो32be(&regs->tpkt);
			पंचांगp_reg2 = ioपढ़ो32be(&regs->reserved02c0[27]);

			/* f. Compare the value of TPKT saved in step b to
			 * value पढ़ो in step e. Also compare bits [9:15] of
			 * the रेजिस्टर at offset 0x32C saved in step d to the
			 * value of bits [9:15] saved in step e. If the two
			 * रेजिस्टरs values are unchanged, then the transmit
			 * portion of the dTSEC controller is locked up and
			 * the user should proceed to the recover sequence.
			 */
			अगर ((tpkt1 == tpkt2) && ((पंचांगp_reg1 & 0x007F0000) ==
				(पंचांगp_reg2 & 0x007F0000))) अणु
				/* recover sequence */

				/* a.Write a 1 to RCTRL[GRS] */

				ioग_लिखो32be(ioपढ़ो32be(&regs->rctrl) |
					    RCTRL_GRS, &regs->rctrl);

				/* b.Wait until IEVENT[GRSC]=1, or at least
				 * 100 us has elapsed.
				 */
				क्रम (i = 0; i < 100; i++) अणु
					अगर (ioपढ़ो32be(&regs->ievent) &
					    DTSEC_IMASK_GRSCEN)
						अवरोध;
					udelay(1);
				पूर्ण
				अगर (ioपढ़ो32be(&regs->ievent) &
				    DTSEC_IMASK_GRSCEN)
					ioग_लिखो32be(DTSEC_IMASK_GRSCEN,
						    &regs->ievent);
				अन्यथा
					pr_debug("Rx lockup due to Tx lockup\n");

				/* c.Write a 1 to bit n of FM_RSTC
				 * (offset 0x0CC of FPM)
				 */
				fman_reset_mac(dtsec->fm, dtsec->mac_id);

				/* d.Wait 4 Tx घड़ीs (32 ns) */
				udelay(1);

				/* e.Write a 0 to bit n of FM_RSTC. */
				/* cleared by FMAN
				 */
			पूर्ण
		पूर्ण

		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_TX_FIFO_UNDRN);
	पूर्ण
	अगर (event & DTSEC_IMASK_MAGEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_MAG_PCKT);
	अगर (event & DTSEC_IMASK_GRSCEN)
		dtsec->exception_cb(dtsec->dev_id,
				    FM_MAC_EX_1G_GRATEFUL_RX_STP_COMPLET);
	अगर (event & DTSEC_IMASK_TDPEEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_DATA_ERR);
	अगर (event & DTSEC_IMASK_RDPEEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_1G_RX_DATA_ERR);

	/* masked पूर्णांकerrupts */
	WARN_ON(event & DTSEC_IMASK_ABRTEN);
	WARN_ON(event & DTSEC_IMASK_IFERREN);
पूर्ण

अटल व्योम dtsec_1588_isr(व्योम *handle)
अणु
	काष्ठा fman_mac *dtsec = (काष्ठा fman_mac *)handle;
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	u32 event;

	अगर (dtsec->ptp_tsu_enabled) अणु
		event = ioपढ़ो32be(&regs->पंचांगr_pevent);
		event &= ioपढ़ो32be(&regs->पंचांगr_pemask);

		अगर (event) अणु
			ioग_लिखो32be(event, &regs->पंचांगr_pevent);
			WARN_ON(event & TMR_PEVENT_TSRE);
			dtsec->exception_cb(dtsec->dev_id,
					    FM_MAC_EX_1G_1588_TS_RX_ERR);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम मुक्त_init_resources(काष्ठा fman_mac *dtsec)
अणु
	fman_unरेजिस्टर_पूर्णांकr(dtsec->fm, FMAN_MOD_MAC, dtsec->mac_id,
			     FMAN_INTR_TYPE_ERR);
	fman_unरेजिस्टर_पूर्णांकr(dtsec->fm, FMAN_MOD_MAC, dtsec->mac_id,
			     FMAN_INTR_TYPE_NORMAL);

	/* release the driver's group hash table */
	मुक्त_hash_table(dtsec->multicast_addr_hash);
	dtsec->multicast_addr_hash = शून्य;

	/* release the driver's inभागidual hash table */
	मुक्त_hash_table(dtsec->unicast_addr_hash);
	dtsec->unicast_addr_hash = शून्य;
पूर्ण

पूर्णांक dtsec_cfg_max_frame_len(काष्ठा fman_mac *dtsec, u16 new_val)
अणु
	अगर (is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	dtsec->dtsec_drv_param->maximum_frame = new_val;

	वापस 0;
पूर्ण

पूर्णांक dtsec_cfg_pad_and_crc(काष्ठा fman_mac *dtsec, bool new_val)
अणु
	अगर (is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	dtsec->dtsec_drv_param->tx_pad_crc = new_val;

	वापस 0;
पूर्ण

अटल व्योम graceful_start(काष्ठा fman_mac *dtsec, क्रमागत comm_mode mode)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;

	अगर (mode & COMM_MODE_TX)
		ioग_लिखो32be(ioपढ़ो32be(&regs->tctrl) &
				~TCTRL_GTS, &regs->tctrl);
	अगर (mode & COMM_MODE_RX)
		ioग_लिखो32be(ioपढ़ो32be(&regs->rctrl) &
				~RCTRL_GRS, &regs->rctrl);
पूर्ण

अटल व्योम graceful_stop(काष्ठा fman_mac *dtsec, क्रमागत comm_mode mode)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	u32 पंचांगp;

	/* Graceful stop - Assert the graceful Rx stop bit */
	अगर (mode & COMM_MODE_RX) अणु
		पंचांगp = ioपढ़ो32be(&regs->rctrl) | RCTRL_GRS;
		ioग_लिखो32be(पंचांगp, &regs->rctrl);

		अगर (dtsec->fm_rev_info.major == 2) अणु
			/* Workaround क्रम dTSEC Errata A002 */
			usleep_range(100, 200);
		पूर्ण अन्यथा अणु
			/* Workaround क्रम dTSEC Errata A004839 */
			usleep_range(10, 50);
		पूर्ण
	पूर्ण

	/* Graceful stop - Assert the graceful Tx stop bit */
	अगर (mode & COMM_MODE_TX) अणु
		अगर (dtsec->fm_rev_info.major == 2) अणु
			/* dTSEC Errata A004: Do not use TCTRL[GTS]=1 */
			pr_debug("GTS not supported due to DTSEC_A004 Errata.\n");
		पूर्ण अन्यथा अणु
			पंचांगp = ioपढ़ो32be(&regs->tctrl) | TCTRL_GTS;
			ioग_लिखो32be(पंचांगp, &regs->tctrl);

			/* Workaround क्रम dTSEC Errata A0012, A0014 */
			usleep_range(10, 50);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक dtsec_enable(काष्ठा fman_mac *dtsec, क्रमागत comm_mode mode)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	/* Enable */
	पंचांगp = ioपढ़ो32be(&regs->maccfg1);
	अगर (mode & COMM_MODE_RX)
		पंचांगp |= MACCFG1_RX_EN;
	अगर (mode & COMM_MODE_TX)
		पंचांगp |= MACCFG1_TX_EN;

	ioग_लिखो32be(पंचांगp, &regs->maccfg1);

	/* Graceful start - clear the graceful Rx/Tx stop bit */
	graceful_start(dtsec, mode);

	वापस 0;
पूर्ण

पूर्णांक dtsec_disable(काष्ठा fman_mac *dtsec, क्रमागत comm_mode mode)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	/* Graceful stop - Assert the graceful Rx/Tx stop bit */
	graceful_stop(dtsec, mode);

	पंचांगp = ioपढ़ो32be(&regs->maccfg1);
	अगर (mode & COMM_MODE_RX)
		पंचांगp &= ~MACCFG1_RX_EN;
	अगर (mode & COMM_MODE_TX)
		पंचांगp &= ~MACCFG1_TX_EN;

	ioग_लिखो32be(पंचांगp, &regs->maccfg1);

	वापस 0;
पूर्ण

पूर्णांक dtsec_set_tx_छोड़ो_frames(काष्ठा fman_mac *dtsec,
			      u8 __maybe_unused priority,
			      u16 छोड़ो_समय, u16 __maybe_unused thresh_समय)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	क्रमागत comm_mode mode = COMM_MODE_NONE;
	u32 ptv = 0;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	अगर ((ioपढ़ो32be(&regs->rctrl) & RCTRL_GRS) == 0)
		mode |= COMM_MODE_RX;
	अगर ((ioपढ़ो32be(&regs->tctrl) & TCTRL_GTS) == 0)
		mode |= COMM_MODE_TX;

	graceful_stop(dtsec, mode);

	अगर (छोड़ो_समय) अणु
		/* FM_BAD_TX_TS_IN_B_2_B_ERRATA_DTSEC_A003 Errata workaround */
		अगर (dtsec->fm_rev_info.major == 2 && छोड़ो_समय <= 320) अणु
			pr_warn("pause-time: %d illegal.Should be > 320\n",
				छोड़ो_समय);
			वापस -EINVAL;
		पूर्ण

		ptv = ioपढ़ो32be(&regs->ptv);
		ptv &= PTV_PTE_MASK;
		ptv |= छोड़ो_समय & PTV_PT_MASK;
		ioग_लिखो32be(ptv, &regs->ptv);

		/* trigger the transmission of a flow-control छोड़ो frame */
		ioग_लिखो32be(ioपढ़ो32be(&regs->maccfg1) | MACCFG1_TX_FLOW,
			    &regs->maccfg1);
	पूर्ण अन्यथा
		ioग_लिखो32be(ioपढ़ो32be(&regs->maccfg1) & ~MACCFG1_TX_FLOW,
			    &regs->maccfg1);

	graceful_start(dtsec, mode);

	वापस 0;
पूर्ण

पूर्णांक dtsec_accept_rx_छोड़ो_frames(काष्ठा fman_mac *dtsec, bool en)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	क्रमागत comm_mode mode = COMM_MODE_NONE;
	u32 पंचांगp;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	अगर ((ioपढ़ो32be(&regs->rctrl) & RCTRL_GRS) == 0)
		mode |= COMM_MODE_RX;
	अगर ((ioपढ़ो32be(&regs->tctrl) & TCTRL_GTS) == 0)
		mode |= COMM_MODE_TX;

	graceful_stop(dtsec, mode);

	पंचांगp = ioपढ़ो32be(&regs->maccfg1);
	अगर (en)
		पंचांगp |= MACCFG1_RX_FLOW;
	अन्यथा
		पंचांगp &= ~MACCFG1_RX_FLOW;
	ioग_लिखो32be(पंचांगp, &regs->maccfg1);

	graceful_start(dtsec, mode);

	वापस 0;
पूर्ण

पूर्णांक dtsec_modअगरy_mac_address(काष्ठा fman_mac *dtsec, enet_addr_t *enet_addr)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	क्रमागत comm_mode mode = COMM_MODE_NONE;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	अगर ((ioपढ़ो32be(&regs->rctrl) & RCTRL_GRS) == 0)
		mode |= COMM_MODE_RX;
	अगर ((ioपढ़ो32be(&regs->tctrl) & TCTRL_GTS) == 0)
		mode |= COMM_MODE_TX;

	graceful_stop(dtsec, mode);

	/* Initialize MAC Station Address रेजिस्टरs (1 & 2)
	 * Station address have to be swapped (big endian to little endian
	 */
	dtsec->addr = ENET_ADDR_TO_UINT64(*enet_addr);
	set_mac_address(dtsec->regs, (u8 *)(*enet_addr));

	graceful_start(dtsec, mode);

	वापस 0;
पूर्ण

पूर्णांक dtsec_add_hash_mac_address(काष्ठा fman_mac *dtsec, enet_addr_t *eth_addr)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	काष्ठा eth_hash_entry *hash_entry;
	u64 addr;
	s32 bucket;
	u32 crc = 0xFFFFFFFF;
	bool mcast, ghtx;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	addr = ENET_ADDR_TO_UINT64(*eth_addr);

	ghtx = (bool)((ioपढ़ो32be(&regs->rctrl) & RCTRL_GHTX) ? true : false);
	mcast = (bool)((addr & MAC_GROUP_ADDRESS) ? true : false);

	/* Cannot handle unicast mac addr when GHTX is on */
	अगर (ghtx && !mcast) अणु
		pr_err("Could not compute hash bucket\n");
		वापस -EINVAL;
	पूर्ण
	crc = crc32_le(crc, (u8 *)eth_addr, ETH_ALEN);
	crc = bitrev32(crc);

	/* considering the 9 highest order bits in crc H[8:0]:
	 *अगर ghtx = 0 H[8:6] (highest order 3 bits) identअगरy the hash रेजिस्टर
	 *and H[5:1] (next 5 bits) identअगरy the hash bit
	 *अगर ghts = 1 H[8:5] (highest order 4 bits) identअगरy the hash रेजिस्टर
	 *and H[4:0] (next 5 bits) identअगरy the hash bit.
	 *
	 *In bucket index output the low 5 bits identअगरy the hash रेजिस्टर
	 *bit, जबतक the higher 4 bits identअगरy the hash रेजिस्टर
	 */

	अगर (ghtx) अणु
		bucket = (s32)((crc >> 23) & 0x1ff);
	पूर्ण अन्यथा अणु
		bucket = (s32)((crc >> 24) & 0xff);
		/* अगर !ghtx and mcast the bit must be set in gaddr instead of
		 *igaddr.
		 */
		अगर (mcast)
			bucket += 0x100;
	पूर्ण

	set_bucket(dtsec->regs, bucket, true);

	/* Create element to be added to the driver hash table */
	hash_entry = kदो_स्मृति(माप(*hash_entry), GFP_ATOMIC);
	अगर (!hash_entry)
		वापस -ENOMEM;
	hash_entry->addr = addr;
	INIT_LIST_HEAD(&hash_entry->node);

	अगर (addr & MAC_GROUP_ADDRESS)
		/* Group Address */
		list_add_tail(&hash_entry->node,
			      &dtsec->multicast_addr_hash->lsts[bucket]);
	अन्यथा
		list_add_tail(&hash_entry->node,
			      &dtsec->unicast_addr_hash->lsts[bucket]);

	वापस 0;
पूर्ण

पूर्णांक dtsec_set_allmulti(काष्ठा fman_mac *dtsec, bool enable)
अणु
	u32 पंचांगp;
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->rctrl);
	अगर (enable)
		पंचांगp |= RCTRL_MPROM;
	अन्यथा
		पंचांगp &= ~RCTRL_MPROM;

	ioग_लिखो32be(पंचांगp, &regs->rctrl);

	वापस 0;
पूर्ण

पूर्णांक dtsec_set_tstamp(काष्ठा fman_mac *dtsec, bool enable)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	u32 rctrl, tctrl;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	rctrl = ioपढ़ो32be(&regs->rctrl);
	tctrl = ioपढ़ो32be(&regs->tctrl);

	अगर (enable) अणु
		rctrl |= RCTRL_RTSE;
		tctrl |= TCTRL_TTSE;
	पूर्ण अन्यथा अणु
		rctrl &= ~RCTRL_RTSE;
		tctrl &= ~TCTRL_TTSE;
	पूर्ण

	ioग_लिखो32be(rctrl, &regs->rctrl);
	ioग_लिखो32be(tctrl, &regs->tctrl);

	वापस 0;
पूर्ण

पूर्णांक dtsec_del_hash_mac_address(काष्ठा fman_mac *dtsec, enet_addr_t *eth_addr)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	काष्ठा list_head *pos;
	काष्ठा eth_hash_entry *hash_entry = शून्य;
	u64 addr;
	s32 bucket;
	u32 crc = 0xFFFFFFFF;
	bool mcast, ghtx;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	addr = ENET_ADDR_TO_UINT64(*eth_addr);

	ghtx = (bool)((ioपढ़ो32be(&regs->rctrl) & RCTRL_GHTX) ? true : false);
	mcast = (bool)((addr & MAC_GROUP_ADDRESS) ? true : false);

	/* Cannot handle unicast mac addr when GHTX is on */
	अगर (ghtx && !mcast) अणु
		pr_err("Could not compute hash bucket\n");
		वापस -EINVAL;
	पूर्ण
	crc = crc32_le(crc, (u8 *)eth_addr, ETH_ALEN);
	crc = bitrev32(crc);

	अगर (ghtx) अणु
		bucket = (s32)((crc >> 23) & 0x1ff);
	पूर्ण अन्यथा अणु
		bucket = (s32)((crc >> 24) & 0xff);
		/* अगर !ghtx and mcast the bit must be set
		 * in gaddr instead of igaddr.
		 */
		अगर (mcast)
			bucket += 0x100;
	पूर्ण

	अगर (addr & MAC_GROUP_ADDRESS) अणु
		/* Group Address */
		list_क्रम_each(pos,
			      &dtsec->multicast_addr_hash->lsts[bucket]) अणु
			hash_entry = ETH_HASH_ENTRY_OBJ(pos);
			अगर (hash_entry && hash_entry->addr == addr) अणु
				list_del_init(&hash_entry->node);
				kमुक्त(hash_entry);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (list_empty(&dtsec->multicast_addr_hash->lsts[bucket]))
			set_bucket(dtsec->regs, bucket, false);
	पूर्ण अन्यथा अणु
		/* Inभागidual Address */
		list_क्रम_each(pos,
			      &dtsec->unicast_addr_hash->lsts[bucket]) अणु
			hash_entry = ETH_HASH_ENTRY_OBJ(pos);
			अगर (hash_entry && hash_entry->addr == addr) अणु
				list_del_init(&hash_entry->node);
				kमुक्त(hash_entry);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (list_empty(&dtsec->unicast_addr_hash->lsts[bucket]))
			set_bucket(dtsec->regs, bucket, false);
	पूर्ण

	/* address करोes not exist */
	WARN_ON(!hash_entry);

	वापस 0;
पूर्ण

पूर्णांक dtsec_set_promiscuous(काष्ठा fman_mac *dtsec, bool new_val)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	/* Set unicast promiscuous */
	पंचांगp = ioपढ़ो32be(&regs->rctrl);
	अगर (new_val)
		पंचांगp |= RCTRL_UPROM;
	अन्यथा
		पंचांगp &= ~RCTRL_UPROM;

	ioग_लिखो32be(पंचांगp, &regs->rctrl);

	/* Set multicast promiscuous */
	पंचांगp = ioपढ़ो32be(&regs->rctrl);
	अगर (new_val)
		पंचांगp |= RCTRL_MPROM;
	अन्यथा
		पंचांगp &= ~RCTRL_MPROM;

	ioग_लिखो32be(पंचांगp, &regs->rctrl);

	वापस 0;
पूर्ण

पूर्णांक dtsec_adjust_link(काष्ठा fman_mac *dtsec, u16 speed)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	क्रमागत comm_mode mode = COMM_MODE_NONE;
	u32 पंचांगp;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	अगर ((ioपढ़ो32be(&regs->rctrl) & RCTRL_GRS) == 0)
		mode |= COMM_MODE_RX;
	अगर ((ioपढ़ो32be(&regs->tctrl) & TCTRL_GTS) == 0)
		mode |= COMM_MODE_TX;

	graceful_stop(dtsec, mode);

	पंचांगp = ioपढ़ो32be(&regs->maccfg2);

	/* Full Duplex */
	पंचांगp |= MACCFG2_FULL_DUPLEX;

	पंचांगp &= ~(MACCFG2_NIBBLE_MODE | MACCFG2_BYTE_MODE);
	अगर (speed < SPEED_1000)
		पंचांगp |= MACCFG2_NIBBLE_MODE;
	अन्यथा अगर (speed == SPEED_1000)
		पंचांगp |= MACCFG2_BYTE_MODE;
	ioग_लिखो32be(पंचांगp, &regs->maccfg2);

	पंचांगp = ioपढ़ो32be(&regs->ecntrl);
	अगर (speed == SPEED_100)
		पंचांगp |= DTSEC_ECNTRL_R100M;
	अन्यथा
		पंचांगp &= ~DTSEC_ECNTRL_R100M;
	ioग_लिखो32be(पंचांगp, &regs->ecntrl);

	graceful_start(dtsec, mode);

	वापस 0;
पूर्ण

पूर्णांक dtsec_restart_स्वतःneg(काष्ठा fman_mac *dtsec)
अणु
	u16 पंचांगp_reg16;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	पंचांगp_reg16 = phy_पढ़ो(dtsec->tbiphy, MII_BMCR);

	पंचांगp_reg16 &= ~(BMCR_SPEED100 | BMCR_SPEED1000);
	पंचांगp_reg16 |= (BMCR_ANENABLE | BMCR_ANRESTART |
		      BMCR_FULLDPLX | BMCR_SPEED1000);

	phy_ग_लिखो(dtsec->tbiphy, MII_BMCR, पंचांगp_reg16);

	वापस 0;
पूर्ण

पूर्णांक dtsec_get_version(काष्ठा fman_mac *dtsec, u32 *mac_version)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	*mac_version = ioपढ़ो32be(&regs->tsec_id);

	वापस 0;
पूर्ण

पूर्णांक dtsec_set_exception(काष्ठा fman_mac *dtsec,
			क्रमागत fman_mac_exceptions exception, bool enable)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	u32 bit_mask = 0;

	अगर (!is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	अगर (exception != FM_MAC_EX_1G_1588_TS_RX_ERR) अणु
		bit_mask = get_exception_flag(exception);
		अगर (bit_mask) अणु
			अगर (enable)
				dtsec->exceptions |= bit_mask;
			अन्यथा
				dtsec->exceptions &= ~bit_mask;
		पूर्ण अन्यथा अणु
			pr_err("Undefined exception\n");
			वापस -EINVAL;
		पूर्ण
		अगर (enable)
			ioग_लिखो32be(ioपढ़ो32be(&regs->imask) | bit_mask,
				    &regs->imask);
		अन्यथा
			ioग_लिखो32be(ioपढ़ो32be(&regs->imask) & ~bit_mask,
				    &regs->imask);
	पूर्ण अन्यथा अणु
		अगर (!dtsec->ptp_tsu_enabled) अणु
			pr_err("Exception valid for 1588 only\n");
			वापस -EINVAL;
		पूर्ण
		चयन (exception) अणु
		हाल FM_MAC_EX_1G_1588_TS_RX_ERR:
			अगर (enable) अणु
				dtsec->en_tsu_err_exception = true;
				ioग_लिखो32be(ioपढ़ो32be(&regs->पंचांगr_pemask) |
					    TMR_PEMASK_TSREEN,
					    &regs->पंचांगr_pemask);
			पूर्ण अन्यथा अणु
				dtsec->en_tsu_err_exception = false;
				ioग_लिखो32be(ioपढ़ो32be(&regs->पंचांगr_pemask) &
					    ~TMR_PEMASK_TSREEN,
					    &regs->पंचांगr_pemask);
			पूर्ण
			अवरोध;
		शेष:
			pr_err("Undefined exception\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dtsec_init(काष्ठा fman_mac *dtsec)
अणु
	काष्ठा dtsec_regs __iomem *regs = dtsec->regs;
	काष्ठा dtsec_cfg *dtsec_drv_param;
	u16 max_frm_ln;
	पूर्णांक err;

	अगर (is_init_करोne(dtsec->dtsec_drv_param))
		वापस -EINVAL;

	अगर (DEFAULT_RESET_ON_INIT &&
	    (fman_reset_mac(dtsec->fm, dtsec->mac_id) != 0)) अणु
		pr_err("Can't reset MAC!\n");
		वापस -EINVAL;
	पूर्ण

	err = check_init_parameters(dtsec);
	अगर (err)
		वापस err;

	dtsec_drv_param = dtsec->dtsec_drv_param;

	err = init(dtsec->regs, dtsec_drv_param, dtsec->phy_अगर,
		   dtsec->max_speed, dtsec->addr, dtsec->exceptions,
		   dtsec->tbiphy->mdio.addr);
	अगर (err) अणु
		मुक्त_init_resources(dtsec);
		pr_err("DTSEC version doesn't support this i/f mode\n");
		वापस err;
	पूर्ण

	अगर (dtsec->phy_अगर == PHY_INTERFACE_MODE_SGMII) अणु
		u16 पंचांगp_reg16;

		/* Configure the TBI PHY Control Register */
		पंचांगp_reg16 = TBICON_CLK_SELECT | TBICON_SOFT_RESET;
		phy_ग_लिखो(dtsec->tbiphy, MII_TBICON, पंचांगp_reg16);

		पंचांगp_reg16 = TBICON_CLK_SELECT;
		phy_ग_लिखो(dtsec->tbiphy, MII_TBICON, पंचांगp_reg16);

		पंचांगp_reg16 = (BMCR_RESET | BMCR_ANENABLE |
			     BMCR_FULLDPLX | BMCR_SPEED1000);
		phy_ग_लिखो(dtsec->tbiphy, MII_BMCR, पंचांगp_reg16);

		अगर (dtsec->basex_अगर)
			पंचांगp_reg16 = TBIANA_1000X;
		अन्यथा
			पंचांगp_reg16 = TBIANA_SGMII;
		phy_ग_लिखो(dtsec->tbiphy, MII_ADVERTISE, पंचांगp_reg16);

		पंचांगp_reg16 = (BMCR_ANENABLE | BMCR_ANRESTART |
			     BMCR_FULLDPLX | BMCR_SPEED1000);

		phy_ग_लिखो(dtsec->tbiphy, MII_BMCR, पंचांगp_reg16);
	पूर्ण

	/* Max Frame Length */
	max_frm_ln = (u16)ioपढ़ो32be(&regs->maxfrm);
	err = fman_set_mac_max_frame(dtsec->fm, dtsec->mac_id, max_frm_ln);
	अगर (err) अणु
		pr_err("Setting max frame length failed\n");
		मुक्त_init_resources(dtsec);
		वापस -EINVAL;
	पूर्ण

	dtsec->multicast_addr_hash =
	alloc_hash_table(EXTENDED_HASH_TABLE_SIZE);
	अगर (!dtsec->multicast_addr_hash) अणु
		मुक्त_init_resources(dtsec);
		pr_err("MC hash table is failed\n");
		वापस -ENOMEM;
	पूर्ण

	dtsec->unicast_addr_hash = alloc_hash_table(DTSEC_HASH_TABLE_SIZE);
	अगर (!dtsec->unicast_addr_hash) अणु
		मुक्त_init_resources(dtsec);
		pr_err("UC hash table is failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* रेजिस्टर err पूर्णांकr handler क्रम dtsec to FPM (err) */
	fman_रेजिस्टर_पूर्णांकr(dtsec->fm, FMAN_MOD_MAC, dtsec->mac_id,
			   FMAN_INTR_TYPE_ERR, dtsec_isr, dtsec);
	/* रेजिस्टर 1588 पूर्णांकr handler क्रम TMR to FPM (normal) */
	fman_रेजिस्टर_पूर्णांकr(dtsec->fm, FMAN_MOD_MAC, dtsec->mac_id,
			   FMAN_INTR_TYPE_NORMAL, dtsec_1588_isr, dtsec);

	kमुक्त(dtsec_drv_param);
	dtsec->dtsec_drv_param = शून्य;

	वापस 0;
पूर्ण

पूर्णांक dtsec_मुक्त(काष्ठा fman_mac *dtsec)
अणु
	मुक्त_init_resources(dtsec);

	kमुक्त(dtsec->dtsec_drv_param);
	dtsec->dtsec_drv_param = शून्य;
	kमुक्त(dtsec);

	वापस 0;
पूर्ण

काष्ठा fman_mac *dtsec_config(काष्ठा fman_mac_params *params)
अणु
	काष्ठा fman_mac *dtsec;
	काष्ठा dtsec_cfg *dtsec_drv_param;
	व्योम __iomem *base_addr;

	base_addr = params->base_addr;

	/* allocate memory क्रम the UCC GETH data काष्ठाure. */
	dtsec = kzalloc(माप(*dtsec), GFP_KERNEL);
	अगर (!dtsec)
		वापस शून्य;

	/* allocate memory क्रम the d_tsec driver parameters data काष्ठाure. */
	dtsec_drv_param = kzalloc(माप(*dtsec_drv_param), GFP_KERNEL);
	अगर (!dtsec_drv_param)
		जाओ err_dtsec;

	/* Plant parameter काष्ठाure poपूर्णांकer */
	dtsec->dtsec_drv_param = dtsec_drv_param;

	set_dflts(dtsec_drv_param);

	dtsec->regs = base_addr;
	dtsec->addr = ENET_ADDR_TO_UINT64(params->addr);
	dtsec->max_speed = params->max_speed;
	dtsec->phy_अगर = params->phy_अगर;
	dtsec->mac_id = params->mac_id;
	dtsec->exceptions = (DTSEC_IMASK_BREN	|
			     DTSEC_IMASK_RXCEN	|
			     DTSEC_IMASK_BTEN	|
			     DTSEC_IMASK_TXCEN	|
			     DTSEC_IMASK_TXEEN	|
			     DTSEC_IMASK_ABRTEN	|
			     DTSEC_IMASK_LCEN	|
			     DTSEC_IMASK_CRLEN	|
			     DTSEC_IMASK_XFUNEN	|
			     DTSEC_IMASK_IFERREN |
			     DTSEC_IMASK_MAGEN	|
			     DTSEC_IMASK_TDPEEN	|
			     DTSEC_IMASK_RDPEEN);
	dtsec->exception_cb = params->exception_cb;
	dtsec->event_cb = params->event_cb;
	dtsec->dev_id = params->dev_id;
	dtsec->ptp_tsu_enabled = dtsec->dtsec_drv_param->ptp_tsu_en;
	dtsec->en_tsu_err_exception = dtsec->dtsec_drv_param->ptp_exception_en;

	dtsec->fm = params->fm;
	dtsec->basex_अगर = params->basex_अगर;

	अगर (!params->पूर्णांकernal_phy_node) अणु
		pr_err("TBI PHY node is not available\n");
		जाओ err_dtsec_drv_param;
	पूर्ण

	dtsec->tbiphy = of_phy_find_device(params->पूर्णांकernal_phy_node);
	अगर (!dtsec->tbiphy) अणु
		pr_err("of_phy_find_device (TBI PHY) failed\n");
		जाओ err_dtsec_drv_param;
	पूर्ण

	put_device(&dtsec->tbiphy->mdio.dev);

	/* Save FMan revision */
	fman_get_revision(dtsec->fm, &dtsec->fm_rev_info);

	वापस dtsec;

err_dtsec_drv_param:
	kमुक्त(dtsec_drv_param);
err_dtsec:
	kमुक्त(dtsec);
	वापस शून्य;
पूर्ण
