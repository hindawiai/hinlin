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

#समावेश "fman_memac.h"
#समावेश "fman.h"

#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/of_mdपन.स>

/* PCS रेजिस्टरs */
#घोषणा MDIO_SGMII_CR			0x00
#घोषणा MDIO_SGMII_DEV_ABIL_SGMII	0x04
#घोषणा MDIO_SGMII_LINK_TMR_L		0x12
#घोषणा MDIO_SGMII_LINK_TMR_H		0x13
#घोषणा MDIO_SGMII_IF_MODE		0x14

/* SGMII Control defines */
#घोषणा SGMII_CR_AN_EN			0x1000
#घोषणा SGMII_CR_RESTART_AN		0x0200
#घोषणा SGMII_CR_FD			0x0100
#घोषणा SGMII_CR_SPEED_SEL1_1G		0x0040
#घोषणा SGMII_CR_DEF_VAL		(SGMII_CR_AN_EN | SGMII_CR_FD | \
					 SGMII_CR_SPEED_SEL1_1G)

/* SGMII Device Ability क्रम SGMII defines */
#घोषणा MDIO_SGMII_DEV_ABIL_SGMII_MODE	0x4001
#घोषणा MDIO_SGMII_DEV_ABIL_BASEX_MODE	0x01A0

/* Link समयr define */
#घोषणा LINK_TMR_L			0xa120
#घोषणा LINK_TMR_H			0x0007
#घोषणा LINK_TMR_L_BASEX		0xaf08
#घोषणा LINK_TMR_H_BASEX		0x002f

/* SGMII IF Mode defines */
#घोषणा IF_MODE_USE_SGMII_AN		0x0002
#घोषणा IF_MODE_SGMII_EN		0x0001
#घोषणा IF_MODE_SGMII_SPEED_100M	0x0004
#घोषणा IF_MODE_SGMII_SPEED_1G		0x0008
#घोषणा IF_MODE_SGMII_DUPLEX_HALF	0x0010

/* Num of additional exact match MAC adr regs */
#घोषणा MEMAC_NUM_OF_PADDRS 7

/* Control and Configuration Register (COMMAND_CONFIG) */
#घोषणा CMD_CFG_REG_LOWP_RXETY	0x01000000 /* 07 Rx low घातer indication */
#घोषणा CMD_CFG_TX_LOWP_ENA	0x00800000 /* 08 Tx Low Power Idle Enable */
#घोषणा CMD_CFG_PFC_MODE	0x00080000 /* 12 Enable PFC */
#घोषणा CMD_CFG_NO_LEN_CHK	0x00020000 /* 14 Payload length check disable */
#घोषणा CMD_CFG_SW_RESET	0x00001000 /* 19 S/W Reset, self clearing bit */
#घोषणा CMD_CFG_TX_PAD_EN	0x00000800 /* 20 Enable Tx padding of frames */
#घोषणा CMD_CFG_PAUSE_IGNORE	0x00000100 /* 23 Ignore Pause frame quanta */
#घोषणा CMD_CFG_CRC_FWD		0x00000040 /* 25 Terminate/frwd CRC of frames */
#घोषणा CMD_CFG_PAD_EN		0x00000020 /* 26 Frame padding removal */
#घोषणा CMD_CFG_PROMIS_EN	0x00000010 /* 27 Promiscuous operation enable */
#घोषणा CMD_CFG_RX_EN		0x00000002 /* 30 MAC receive path enable */
#घोषणा CMD_CFG_TX_EN		0x00000001 /* 31 MAC transmit path enable */

/* Transmit FIFO Sections Register (TX_FIFO_SECTIONS) */
#घोषणा TX_FIFO_SECTIONS_TX_EMPTY_MASK			0xFFFF0000
#घोषणा TX_FIFO_SECTIONS_TX_AVAIL_MASK			0x0000FFFF
#घोषणा TX_FIFO_SECTIONS_TX_EMPTY_DEFAULT_10G		0x00400000
#घोषणा TX_FIFO_SECTIONS_TX_EMPTY_DEFAULT_1G		0x00100000
#घोषणा TX_FIFO_SECTIONS_TX_AVAIL_10G			0x00000019
#घोषणा TX_FIFO_SECTIONS_TX_AVAIL_1G			0x00000020
#घोषणा TX_FIFO_SECTIONS_TX_AVAIL_SLOW_10G		0x00000060

#घोषणा GET_TX_EMPTY_DEFAULT_VALUE(_val)				\
करो अणु									\
	_val &= ~TX_FIFO_SECTIONS_TX_EMPTY_MASK;			\
	((_val == TX_FIFO_SECTIONS_TX_AVAIL_10G) ?			\
			(_val |= TX_FIFO_SECTIONS_TX_EMPTY_DEFAULT_10G) :\
			(_val |= TX_FIFO_SECTIONS_TX_EMPTY_DEFAULT_1G));\
पूर्ण जबतक (0)

/* Interface Mode Register (IF_MODE) */

#घोषणा IF_MODE_MASK		0x00000003 /* 30-31 Mask on i/f mode bits */
#घोषणा IF_MODE_10G		0x00000000 /* 30-31 10G पूर्णांकerface */
#घोषणा IF_MODE_MII		0x00000001 /* 30-31 MII पूर्णांकerface */
#घोषणा IF_MODE_GMII		0x00000002 /* 30-31 GMII (1G) पूर्णांकerface */
#घोषणा IF_MODE_RGMII		0x00000004
#घोषणा IF_MODE_RGMII_AUTO	0x00008000
#घोषणा IF_MODE_RGMII_1000	0x00004000 /* 10 - 1000Mbps RGMII */
#घोषणा IF_MODE_RGMII_100	0x00000000 /* 00 - 100Mbps RGMII */
#घोषणा IF_MODE_RGMII_10	0x00002000 /* 01 - 10Mbps RGMII */
#घोषणा IF_MODE_RGMII_SP_MASK	0x00006000 /* Setsp mask bits */
#घोषणा IF_MODE_RGMII_FD	0x00001000 /* Full duplex RGMII */
#घोषणा IF_MODE_HD		0x00000040 /* Half duplex operation */

/* Hash table Control Register (HASHTABLE_CTRL) */
#घोषणा HASH_CTRL_MCAST_EN	0x00000100
/* 26-31 Hash table address code */
#घोषणा HASH_CTRL_ADDR_MASK	0x0000003F
/* MAC mcast indication */
#घोषणा GROUP_ADDRESS		0x0000010000000000LL
#घोषणा HASH_TABLE_SIZE		64	/* Hash tbl size */

/* Interrupt Mask Register (IMASK) */
#घोषणा MEMAC_IMASK_MGI		0x40000000 /* 1 Magic pkt detect indication */
#घोषणा MEMAC_IMASK_TSECC_ER	0x20000000 /* 2 Timestamp FIFO ECC error evnt */
#घोषणा MEMAC_IMASK_TECC_ER	0x02000000 /* 6 Transmit frame ECC error evnt */
#घोषणा MEMAC_IMASK_RECC_ER	0x01000000 /* 7 Receive frame ECC error evnt */

#घोषणा MEMAC_ALL_ERRS_IMASK					\
		((u32)(MEMAC_IMASK_TSECC_ER	|	\
		       MEMAC_IMASK_TECC_ER		|	\
		       MEMAC_IMASK_RECC_ER		|	\
		       MEMAC_IMASK_MGI))

#घोषणा MEMAC_IEVNT_PCS			0x80000000 /* PCS (XG). Link sync (G) */
#घोषणा MEMAC_IEVNT_AN			0x40000000 /* Auto-negotiation */
#घोषणा MEMAC_IEVNT_LT			0x20000000 /* Link Training/New page */
#घोषणा MEMAC_IEVNT_MGI			0x00004000 /* Magic pkt detection */
#घोषणा MEMAC_IEVNT_TS_ECC_ER		0x00002000 /* Timestamp FIFO ECC error*/
#घोषणा MEMAC_IEVNT_RX_FIFO_OVFL	0x00001000 /* Rx FIFO overflow */
#घोषणा MEMAC_IEVNT_TX_FIFO_UNFL	0x00000800 /* Tx FIFO underflow */
#घोषणा MEMAC_IEVNT_TX_FIFO_OVFL	0x00000400 /* Tx FIFO overflow */
#घोषणा MEMAC_IEVNT_TX_ECC_ER		0x00000200 /* Tx frame ECC error */
#घोषणा MEMAC_IEVNT_RX_ECC_ER		0x00000100 /* Rx frame ECC error */
#घोषणा MEMAC_IEVNT_LI_FAULT		0x00000080 /* Link Interruption flt */
#घोषणा MEMAC_IEVNT_RX_EMPTY		0x00000040 /* Rx FIFO empty */
#घोषणा MEMAC_IEVNT_TX_EMPTY		0x00000020 /* Tx FIFO empty */
#घोषणा MEMAC_IEVNT_RX_LOWP		0x00000010 /* Low Power Idle */
#घोषणा MEMAC_IEVNT_PHY_LOS		0x00000004 /* Phy loss of संकेत */
#घोषणा MEMAC_IEVNT_REM_FAULT		0x00000002 /* Remote fault (XGMII) */
#घोषणा MEMAC_IEVNT_LOC_FAULT		0x00000001 /* Local fault (XGMII) */

#घोषणा DEFAULT_PAUSE_QUANTA	0xf000
#घोषणा DEFAULT_FRAME_LENGTH	0x600
#घोषणा DEFAULT_TX_IPG_LENGTH	12

#घोषणा CLXY_PAUSE_QUANTA_CLX_PQNT	0x0000FFFF
#घोषणा CLXY_PAUSE_QUANTA_CLY_PQNT	0xFFFF0000
#घोषणा CLXY_PAUSE_THRESH_CLX_QTH	0x0000FFFF
#घोषणा CLXY_PAUSE_THRESH_CLY_QTH	0xFFFF0000

काष्ठा mac_addr अणु
	/* Lower 32 bits of 48-bit MAC address */
	u32 mac_addr_l;
	/* Upper 16 bits of 48-bit MAC address */
	u32 mac_addr_u;
पूर्ण;

/* memory map */
काष्ठा memac_regs अणु
	u32 res0000[2];			/* General Control and Status */
	u32 command_config;		/* 0x008 Ctrl and cfg */
	काष्ठा mac_addr mac_addr0;	/* 0x00C-0x010 MAC_ADDR_0...1 */
	u32 maxfrm;			/* 0x014 Max frame length */
	u32 res0018[1];
	u32 rx_fअगरo_sections;		/* Receive FIFO configuration reg */
	u32 tx_fअगरo_sections;		/* Transmit FIFO configuration reg */
	u32 res0024[2];
	u32 hashtable_ctrl;		/* 0x02C Hash table control */
	u32 res0030[4];
	u32 ievent;			/* 0x040 Interrupt event */
	u32 tx_ipg_length;		/* 0x044 Transmitter पूर्णांकer-packet-gap */
	u32 res0048;
	u32 imask;			/* 0x04C Interrupt mask */
	u32 res0050;
	u32 छोड़ो_quanta[4];		/* 0x054 Pause quanta */
	u32 छोड़ो_thresh[4];		/* 0x064 Pause quanta threshold */
	u32 rx_छोड़ो_status;		/* 0x074 Receive छोड़ो status */
	u32 res0078[2];
	काष्ठा mac_addr mac_addr[MEMAC_NUM_OF_PADDRS];/* 0x80-0x0B4 mac padr */
	u32 lpwake_समयr;		/* 0x0B8 Low Power Wakeup Timer */
	u32 sleep_समयr;		/* 0x0BC Transmit EEE Low Power Timer */
	u32 res00c0[8];
	u32 statn_config;		/* 0x0E0 Statistics configuration */
	u32 res00e4[7];
	/* Rx Statistics Counter */
	u32 reoct_l;
	u32 reoct_u;
	u32 roct_l;
	u32 roct_u;
	u32 raln_l;
	u32 raln_u;
	u32 rxpf_l;
	u32 rxpf_u;
	u32 rfrm_l;
	u32 rfrm_u;
	u32 rfcs_l;
	u32 rfcs_u;
	u32 rvlan_l;
	u32 rvlan_u;
	u32 rerr_l;
	u32 rerr_u;
	u32 ruca_l;
	u32 ruca_u;
	u32 rmca_l;
	u32 rmca_u;
	u32 rbca_l;
	u32 rbca_u;
	u32 rdrp_l;
	u32 rdrp_u;
	u32 rpkt_l;
	u32 rpkt_u;
	u32 rund_l;
	u32 rund_u;
	u32 r64_l;
	u32 r64_u;
	u32 r127_l;
	u32 r127_u;
	u32 r255_l;
	u32 r255_u;
	u32 r511_l;
	u32 r511_u;
	u32 r1023_l;
	u32 r1023_u;
	u32 r1518_l;
	u32 r1518_u;
	u32 r1519x_l;
	u32 r1519x_u;
	u32 rovr_l;
	u32 rovr_u;
	u32 rjbr_l;
	u32 rjbr_u;
	u32 rfrg_l;
	u32 rfrg_u;
	u32 rcnp_l;
	u32 rcnp_u;
	u32 rdrntp_l;
	u32 rdrntp_u;
	u32 res01d0[12];
	/* Tx Statistics Counter */
	u32 teoct_l;
	u32 teoct_u;
	u32 toct_l;
	u32 toct_u;
	u32 res0210[2];
	u32 txpf_l;
	u32 txpf_u;
	u32 tfrm_l;
	u32 tfrm_u;
	u32 tfcs_l;
	u32 tfcs_u;
	u32 tvlan_l;
	u32 tvlan_u;
	u32 terr_l;
	u32 terr_u;
	u32 tuca_l;
	u32 tuca_u;
	u32 पंचांगca_l;
	u32 पंचांगca_u;
	u32 tbca_l;
	u32 tbca_u;
	u32 res0258[2];
	u32 tpkt_l;
	u32 tpkt_u;
	u32 tund_l;
	u32 tund_u;
	u32 t64_l;
	u32 t64_u;
	u32 t127_l;
	u32 t127_u;
	u32 t255_l;
	u32 t255_u;
	u32 t511_l;
	u32 t511_u;
	u32 t1023_l;
	u32 t1023_u;
	u32 t1518_l;
	u32 t1518_u;
	u32 t1519x_l;
	u32 t1519x_u;
	u32 res02a8[6];
	u32 tcnp_l;
	u32 tcnp_u;
	u32 res02c8[14];
	/* Line Interface Control */
	u32 अगर_mode;		/* 0x300 Interface Mode Control */
	u32 अगर_status;		/* 0x304 Interface Status */
	u32 res0308[14];
	/* HiGig/2 */
	u32 hg_config;		/* 0x340 Control and cfg */
	u32 res0344[3];
	u32 hg_छोड़ो_quanta;	/* 0x350 Pause quanta */
	u32 res0354[3];
	u32 hg_छोड़ो_thresh;	/* 0x360 Pause quanta threshold */
	u32 res0364[3];
	u32 hgrx_छोड़ो_status;	/* 0x370 Receive छोड़ो status */
	u32 hg_fअगरos_status;	/* 0x374 fअगरos status */
	u32 rhm;		/* 0x378 rx messages counter */
	u32 thm;		/* 0x37C tx messages counter */
पूर्ण;

काष्ठा memac_cfg अणु
	bool reset_on_init;
	bool छोड़ो_ignore;
	bool promiscuous_mode_enable;
	काष्ठा fixed_phy_status *fixed_link;
	u16 max_frame_length;
	u16 छोड़ो_quanta;
	u32 tx_ipg_length;
पूर्ण;

काष्ठा fman_mac अणु
	/* Poपूर्णांकer to MAC memory mapped रेजिस्टरs */
	काष्ठा memac_regs __iomem *regs;
	/* MAC address of device */
	u64 addr;
	/* Ethernet physical पूर्णांकerface */
	phy_पूर्णांकerface_t phy_अगर;
	u16 max_speed;
	व्योम *dev_id; /* device cookie used by the exception cbs */
	fman_mac_exception_cb *exception_cb;
	fman_mac_exception_cb *event_cb;
	/* Poपूर्णांकer to driver's global address hash table  */
	काष्ठा eth_hash_t *multicast_addr_hash;
	/* Poपूर्णांकer to driver's inभागidual address hash table  */
	काष्ठा eth_hash_t *unicast_addr_hash;
	u8 mac_id;
	u32 exceptions;
	काष्ठा memac_cfg *memac_drv_param;
	व्योम *fm;
	काष्ठा fman_rev_info fm_rev_info;
	bool basex_अगर;
	काष्ठा phy_device *pcsphy;
	bool allmulti_enabled;
पूर्ण;

अटल व्योम add_addr_in_paddr(काष्ठा memac_regs __iomem *regs, u8 *adr,
			      u8 paddr_num)
अणु
	u32 पंचांगp0, पंचांगp1;

	पंचांगp0 = (u32)(adr[0] | adr[1] << 8 | adr[2] << 16 | adr[3] << 24);
	पंचांगp1 = (u32)(adr[4] | adr[5] << 8);

	अगर (paddr_num == 0) अणु
		ioग_लिखो32be(पंचांगp0, &regs->mac_addr0.mac_addr_l);
		ioग_लिखो32be(पंचांगp1, &regs->mac_addr0.mac_addr_u);
	पूर्ण अन्यथा अणु
		ioग_लिखो32be(पंचांगp0, &regs->mac_addr[paddr_num - 1].mac_addr_l);
		ioग_लिखो32be(पंचांगp1, &regs->mac_addr[paddr_num - 1].mac_addr_u);
	पूर्ण
पूर्ण

अटल पूर्णांक reset(काष्ठा memac_regs __iomem *regs)
अणु
	u32 पंचांगp;
	पूर्णांक count;

	पंचांगp = ioपढ़ो32be(&regs->command_config);

	पंचांगp |= CMD_CFG_SW_RESET;

	ioग_लिखो32be(पंचांगp, &regs->command_config);

	count = 100;
	करो अणु
		udelay(1);
	पूर्ण जबतक ((ioपढ़ो32be(&regs->command_config) & CMD_CFG_SW_RESET) &&
		 --count);

	अगर (count == 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम set_exception(काष्ठा memac_regs __iomem *regs, u32 val,
			  bool enable)
अणु
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32be(&regs->imask);
	अगर (enable)
		पंचांगp |= val;
	अन्यथा
		पंचांगp &= ~val;

	ioग_लिखो32be(पंचांगp, &regs->imask);
पूर्ण

अटल पूर्णांक init(काष्ठा memac_regs __iomem *regs, काष्ठा memac_cfg *cfg,
		phy_पूर्णांकerface_t phy_अगर, u16 speed, bool slow_10g_अगर,
		u32 exceptions)
अणु
	u32 पंचांगp;

	/* Config */
	पंचांगp = 0;
	अगर (cfg->promiscuous_mode_enable)
		पंचांगp |= CMD_CFG_PROMIS_EN;
	अगर (cfg->छोड़ो_ignore)
		पंचांगp |= CMD_CFG_PAUSE_IGNORE;

	/* Payload length check disable */
	पंचांगp |= CMD_CFG_NO_LEN_CHK;
	/* Enable padding of frames in transmit direction */
	पंचांगp |= CMD_CFG_TX_PAD_EN;

	पंचांगp |= CMD_CFG_CRC_FWD;

	ioग_लिखो32be(पंचांगp, &regs->command_config);

	/* Max Frame Length */
	ioग_लिखो32be((u32)cfg->max_frame_length, &regs->maxfrm);

	/* Pause Time */
	ioग_लिखो32be((u32)cfg->छोड़ो_quanta, &regs->छोड़ो_quanta[0]);
	ioग_लिखो32be((u32)0, &regs->छोड़ो_thresh[0]);

	/* IF_MODE */
	पंचांगp = 0;
	चयन (phy_अगर) अणु
	हाल PHY_INTERFACE_MODE_XGMII:
		पंचांगp |= IF_MODE_10G;
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
		पंचांगp |= IF_MODE_MII;
		अवरोध;
	शेष:
		पंचांगp |= IF_MODE_GMII;
		अगर (phy_अगर == PHY_INTERFACE_MODE_RGMII ||
		    phy_अगर == PHY_INTERFACE_MODE_RGMII_ID ||
		    phy_अगर == PHY_INTERFACE_MODE_RGMII_RXID ||
		    phy_अगर == PHY_INTERFACE_MODE_RGMII_TXID)
			पंचांगp |= IF_MODE_RGMII | IF_MODE_RGMII_AUTO;
	पूर्ण
	ioग_लिखो32be(पंचांगp, &regs->अगर_mode);

	/* TX_FIFO_SECTIONS */
	पंचांगp = 0;
	अगर (phy_अगर == PHY_INTERFACE_MODE_XGMII) अणु
		अगर (slow_10g_अगर) अणु
			पंचांगp |= (TX_FIFO_SECTIONS_TX_AVAIL_SLOW_10G |
				TX_FIFO_SECTIONS_TX_EMPTY_DEFAULT_10G);
		पूर्ण अन्यथा अणु
			पंचांगp |= (TX_FIFO_SECTIONS_TX_AVAIL_10G |
				TX_FIFO_SECTIONS_TX_EMPTY_DEFAULT_10G);
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp |= (TX_FIFO_SECTIONS_TX_AVAIL_1G |
			TX_FIFO_SECTIONS_TX_EMPTY_DEFAULT_1G);
	पूर्ण
	ioग_लिखो32be(पंचांगp, &regs->tx_fअगरo_sections);

	/* clear all pending events and set-up पूर्णांकerrupts */
	ioग_लिखो32be(0xffffffff, &regs->ievent);
	set_exception(regs, exceptions, true);

	वापस 0;
पूर्ण

अटल व्योम set_dflts(काष्ठा memac_cfg *cfg)
अणु
	cfg->reset_on_init = false;
	cfg->promiscuous_mode_enable = false;
	cfg->छोड़ो_ignore = false;
	cfg->tx_ipg_length = DEFAULT_TX_IPG_LENGTH;
	cfg->max_frame_length = DEFAULT_FRAME_LENGTH;
	cfg->छोड़ो_quanta = DEFAULT_PAUSE_QUANTA;
पूर्ण

अटल u32 get_mac_addr_hash_code(u64 eth_addr)
अणु
	u64 mask1, mask2;
	u32 xor_val = 0;
	u8 i, j;

	क्रम (i = 0; i < 6; i++) अणु
		mask1 = eth_addr & (u64)0x01;
		eth_addr >>= 1;

		क्रम (j = 0; j < 7; j++) अणु
			mask2 = eth_addr & (u64)0x01;
			mask1 ^= mask2;
			eth_addr >>= 1;
		पूर्ण

		xor_val |= (mask1 << (5 - i));
	पूर्ण

	वापस xor_val;
पूर्ण

अटल व्योम setup_sgmii_पूर्णांकernal_phy(काष्ठा fman_mac *memac,
				     काष्ठा fixed_phy_status *fixed_link)
अणु
	u16 पंचांगp_reg16;

	अगर (WARN_ON(!memac->pcsphy))
		वापस;

	/* SGMII mode */
	पंचांगp_reg16 = IF_MODE_SGMII_EN;
	अगर (!fixed_link)
		/* AN enable */
		पंचांगp_reg16 |= IF_MODE_USE_SGMII_AN;
	अन्यथा अणु
		चयन (fixed_link->speed) अणु
		हाल 10:
			/* For 10M: IF_MODE[SPEED_10M] = 0 */
		अवरोध;
		हाल 100:
			पंचांगp_reg16 |= IF_MODE_SGMII_SPEED_100M;
		अवरोध;
		हाल 1000:
		शेष:
			पंचांगp_reg16 |= IF_MODE_SGMII_SPEED_1G;
		अवरोध;
		पूर्ण
		अगर (!fixed_link->duplex)
			पंचांगp_reg16 |= IF_MODE_SGMII_DUPLEX_HALF;
	पूर्ण
	phy_ग_लिखो(memac->pcsphy, MDIO_SGMII_IF_MODE, पंचांगp_reg16);

	/* Device ability according to SGMII specअगरication */
	पंचांगp_reg16 = MDIO_SGMII_DEV_ABIL_SGMII_MODE;
	phy_ग_लिखो(memac->pcsphy, MDIO_SGMII_DEV_ABIL_SGMII, पंचांगp_reg16);

	/* Adjust link समयr क्रम SGMII  -
	 * According to Cisco SGMII specअगरication the समयr should be 1.6 ms.
	 * The link_समयr रेजिस्टर is configured in units of the घड़ी.
	 * - When running as 1G SGMII, Serdes घड़ी is 125 MHz, so
	 * unit = 1 / (125*10^6 Hz) = 8 ns.
	 * 1.6 ms in units of 8 ns = 1.6ms / 8ns = 2*10^5 = 0x30d40
	 * - When running as 2.5G SGMII, Serdes घड़ी is 312.5 MHz, so
	 * unit = 1 / (312.5*10^6 Hz) = 3.2 ns.
	 * 1.6 ms in units of 3.2 ns = 1.6ms / 3.2ns = 5*10^5 = 0x7a120.
	 * Since link_समयr value of 1G SGMII will be too लघु क्रम 2.5 SGMII,
	 * we always set up here a value of 2.5 SGMII.
	 */
	phy_ग_लिखो(memac->pcsphy, MDIO_SGMII_LINK_TMR_H, LINK_TMR_H);
	phy_ग_लिखो(memac->pcsphy, MDIO_SGMII_LINK_TMR_L, LINK_TMR_L);

	अगर (!fixed_link)
		/* Restart AN */
		पंचांगp_reg16 = SGMII_CR_DEF_VAL | SGMII_CR_RESTART_AN;
	अन्यथा
		/* AN disabled */
		पंचांगp_reg16 = SGMII_CR_DEF_VAL & ~SGMII_CR_AN_EN;
	phy_ग_लिखो(memac->pcsphy, 0x0, पंचांगp_reg16);
पूर्ण

अटल व्योम setup_sgmii_पूर्णांकernal_phy_base_x(काष्ठा fman_mac *memac)
अणु
	u16 पंचांगp_reg16;

	/* AN Device capability  */
	पंचांगp_reg16 = MDIO_SGMII_DEV_ABIL_BASEX_MODE;
	phy_ग_लिखो(memac->pcsphy, MDIO_SGMII_DEV_ABIL_SGMII, पंचांगp_reg16);

	/* Adjust link समयr क्रम SGMII  -
	 * For Serdes 1000BaseX स्वतः-negotiation the समयr should be 10 ms.
	 * The link_समयr रेजिस्टर is configured in units of the घड़ी.
	 * - When running as 1G SGMII, Serdes घड़ी is 125 MHz, so
	 * unit = 1 / (125*10^6 Hz) = 8 ns.
	 * 10 ms in units of 8 ns = 10ms / 8ns = 1250000 = 0x1312d0
	 * - When running as 2.5G SGMII, Serdes घड़ी is 312.5 MHz, so
	 * unit = 1 / (312.5*10^6 Hz) = 3.2 ns.
	 * 10 ms in units of 3.2 ns = 10ms / 3.2ns = 3125000 = 0x2faf08.
	 * Since link_समयr value of 1G SGMII will be too लघु क्रम 2.5 SGMII,
	 * we always set up here a value of 2.5 SGMII.
	 */
	phy_ग_लिखो(memac->pcsphy, MDIO_SGMII_LINK_TMR_H, LINK_TMR_H_BASEX);
	phy_ग_लिखो(memac->pcsphy, MDIO_SGMII_LINK_TMR_L, LINK_TMR_L_BASEX);

	/* Restart AN */
	पंचांगp_reg16 = SGMII_CR_DEF_VAL | SGMII_CR_RESTART_AN;
	phy_ग_लिखो(memac->pcsphy, 0x0, पंचांगp_reg16);
पूर्ण

अटल पूर्णांक check_init_parameters(काष्ठा fman_mac *memac)
अणु
	अगर (!memac->exception_cb) अणु
		pr_err("Uninitialized exception handler\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!memac->event_cb) अणु
		pr_warn("Uninitialize event handler\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_exception_flag(क्रमागत fman_mac_exceptions exception)
अणु
	u32 bit_mask;

	चयन (exception) अणु
	हाल FM_MAC_EX_10G_TX_ECC_ER:
		bit_mask = MEMAC_IMASK_TECC_ER;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_ECC_ER:
		bit_mask = MEMAC_IMASK_RECC_ER;
		अवरोध;
	हाल FM_MAC_EX_TS_FIFO_ECC_ERR:
		bit_mask = MEMAC_IMASK_TSECC_ER;
		अवरोध;
	हाल FM_MAC_EX_MAGIC_PACKET_INDICATION:
		bit_mask = MEMAC_IMASK_MGI;
		अवरोध;
	शेष:
		bit_mask = 0;
		अवरोध;
	पूर्ण

	वापस bit_mask;
पूर्ण

अटल व्योम memac_err_exception(व्योम *handle)
अणु
	काष्ठा fman_mac *memac = (काष्ठा fman_mac *)handle;
	काष्ठा memac_regs __iomem *regs = memac->regs;
	u32 event, imask;

	event = ioपढ़ो32be(&regs->ievent);
	imask = ioपढ़ो32be(&regs->imask);

	/* Imask include both error and notअगरication/event bits.
	 * Leaving only error bits enabled by imask.
	 * The imask error bits are shअगरted by 16 bits offset from
	 * their corresponding location in the ievent - hence the >> 16
	 */
	event &= ((imask & MEMAC_ALL_ERRS_IMASK) >> 16);

	ioग_लिखो32be(event, &regs->ievent);

	अगर (event & MEMAC_IEVNT_TS_ECC_ER)
		memac->exception_cb(memac->dev_id, FM_MAC_EX_TS_FIFO_ECC_ERR);
	अगर (event & MEMAC_IEVNT_TX_ECC_ER)
		memac->exception_cb(memac->dev_id, FM_MAC_EX_10G_TX_ECC_ER);
	अगर (event & MEMAC_IEVNT_RX_ECC_ER)
		memac->exception_cb(memac->dev_id, FM_MAC_EX_10G_RX_ECC_ER);
पूर्ण

अटल व्योम memac_exception(व्योम *handle)
अणु
	काष्ठा fman_mac *memac = (काष्ठा fman_mac *)handle;
	काष्ठा memac_regs __iomem *regs = memac->regs;
	u32 event, imask;

	event = ioपढ़ो32be(&regs->ievent);
	imask = ioपढ़ो32be(&regs->imask);

	/* Imask include both error and notअगरication/event bits.
	 * Leaving only error bits enabled by imask.
	 * The imask error bits are shअगरted by 16 bits offset from
	 * their corresponding location in the ievent - hence the >> 16
	 */
	event &= ((imask & MEMAC_ALL_ERRS_IMASK) >> 16);

	ioग_लिखो32be(event, &regs->ievent);

	अगर (event & MEMAC_IEVNT_MGI)
		memac->exception_cb(memac->dev_id,
				    FM_MAC_EX_MAGIC_PACKET_INDICATION);
पूर्ण

अटल व्योम मुक्त_init_resources(काष्ठा fman_mac *memac)
अणु
	fman_unरेजिस्टर_पूर्णांकr(memac->fm, FMAN_MOD_MAC, memac->mac_id,
			     FMAN_INTR_TYPE_ERR);

	fman_unरेजिस्टर_पूर्णांकr(memac->fm, FMAN_MOD_MAC, memac->mac_id,
			     FMAN_INTR_TYPE_NORMAL);

	/* release the driver's group hash table */
	मुक्त_hash_table(memac->multicast_addr_hash);
	memac->multicast_addr_hash = शून्य;

	/* release the driver's inभागidual hash table */
	मुक्त_hash_table(memac->unicast_addr_hash);
	memac->unicast_addr_hash = शून्य;
पूर्ण

अटल bool is_init_करोne(काष्ठा memac_cfg *memac_drv_params)
अणु
	/* Checks अगर mEMAC driver parameters were initialized */
	अगर (!memac_drv_params)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक memac_enable(काष्ठा fman_mac *memac, क्रमागत comm_mode mode)
अणु
	काष्ठा memac_regs __iomem *regs = memac->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->command_config);
	अगर (mode & COMM_MODE_RX)
		पंचांगp |= CMD_CFG_RX_EN;
	अगर (mode & COMM_MODE_TX)
		पंचांगp |= CMD_CFG_TX_EN;

	ioग_लिखो32be(पंचांगp, &regs->command_config);

	वापस 0;
पूर्ण

पूर्णांक memac_disable(काष्ठा fman_mac *memac, क्रमागत comm_mode mode)
अणु
	काष्ठा memac_regs __iomem *regs = memac->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->command_config);
	अगर (mode & COMM_MODE_RX)
		पंचांगp &= ~CMD_CFG_RX_EN;
	अगर (mode & COMM_MODE_TX)
		पंचांगp &= ~CMD_CFG_TX_EN;

	ioग_लिखो32be(पंचांगp, &regs->command_config);

	वापस 0;
पूर्ण

पूर्णांक memac_set_promiscuous(काष्ठा fman_mac *memac, bool new_val)
अणु
	काष्ठा memac_regs __iomem *regs = memac->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->command_config);
	अगर (new_val)
		पंचांगp |= CMD_CFG_PROMIS_EN;
	अन्यथा
		पंचांगp &= ~CMD_CFG_PROMIS_EN;

	ioग_लिखो32be(पंचांगp, &regs->command_config);

	वापस 0;
पूर्ण

पूर्णांक memac_adjust_link(काष्ठा fman_mac *memac, u16 speed)
अणु
	काष्ठा memac_regs __iomem *regs = memac->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->अगर_mode);

	/* Set full duplex */
	पंचांगp &= ~IF_MODE_HD;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(memac->phy_अगर)) अणु
		/* Configure RGMII in manual mode */
		पंचांगp &= ~IF_MODE_RGMII_AUTO;
		पंचांगp &= ~IF_MODE_RGMII_SP_MASK;
		/* Full duplex */
		पंचांगp |= IF_MODE_RGMII_FD;

		चयन (speed) अणु
		हाल SPEED_1000:
			पंचांगp |= IF_MODE_RGMII_1000;
			अवरोध;
		हाल SPEED_100:
			पंचांगp |= IF_MODE_RGMII_100;
			अवरोध;
		हाल SPEED_10:
			पंचांगp |= IF_MODE_RGMII_10;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	ioग_लिखो32be(पंचांगp, &regs->अगर_mode);

	वापस 0;
पूर्ण

पूर्णांक memac_cfg_max_frame_len(काष्ठा fman_mac *memac, u16 new_val)
अणु
	अगर (is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	memac->memac_drv_param->max_frame_length = new_val;

	वापस 0;
पूर्ण

पूर्णांक memac_cfg_reset_on_init(काष्ठा fman_mac *memac, bool enable)
अणु
	अगर (is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	memac->memac_drv_param->reset_on_init = enable;

	वापस 0;
पूर्ण

पूर्णांक memac_cfg_fixed_link(काष्ठा fman_mac *memac,
			 काष्ठा fixed_phy_status *fixed_link)
अणु
	अगर (is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	memac->memac_drv_param->fixed_link = fixed_link;

	वापस 0;
पूर्ण

पूर्णांक memac_set_tx_छोड़ो_frames(काष्ठा fman_mac *memac, u8 priority,
			      u16 छोड़ो_समय, u16 thresh_समय)
अणु
	काष्ठा memac_regs __iomem *regs = memac->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->tx_fअगरo_sections);

	GET_TX_EMPTY_DEFAULT_VALUE(पंचांगp);
	ioग_लिखो32be(पंचांगp, &regs->tx_fअगरo_sections);

	पंचांगp = ioपढ़ो32be(&regs->command_config);
	पंचांगp &= ~CMD_CFG_PFC_MODE;

	ioग_लिखो32be(पंचांगp, &regs->command_config);

	पंचांगp = ioपढ़ो32be(&regs->छोड़ो_quanta[priority / 2]);
	अगर (priority % 2)
		पंचांगp &= CLXY_PAUSE_QUANTA_CLX_PQNT;
	अन्यथा
		पंचांगp &= CLXY_PAUSE_QUANTA_CLY_PQNT;
	पंचांगp |= ((u32)छोड़ो_समय << (16 * (priority % 2)));
	ioग_लिखो32be(पंचांगp, &regs->छोड़ो_quanta[priority / 2]);

	पंचांगp = ioपढ़ो32be(&regs->छोड़ो_thresh[priority / 2]);
	अगर (priority % 2)
		पंचांगp &= CLXY_PAUSE_THRESH_CLX_QTH;
	अन्यथा
		पंचांगp &= CLXY_PAUSE_THRESH_CLY_QTH;
	पंचांगp |= ((u32)thresh_समय << (16 * (priority % 2)));
	ioग_लिखो32be(पंचांगp, &regs->छोड़ो_thresh[priority / 2]);

	वापस 0;
पूर्ण

पूर्णांक memac_accept_rx_छोड़ो_frames(काष्ठा fman_mac *memac, bool en)
अणु
	काष्ठा memac_regs __iomem *regs = memac->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->command_config);
	अगर (en)
		पंचांगp &= ~CMD_CFG_PAUSE_IGNORE;
	अन्यथा
		पंचांगp |= CMD_CFG_PAUSE_IGNORE;

	ioग_लिखो32be(पंचांगp, &regs->command_config);

	वापस 0;
पूर्ण

पूर्णांक memac_modअगरy_mac_address(काष्ठा fman_mac *memac, enet_addr_t *enet_addr)
अणु
	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	add_addr_in_paddr(memac->regs, (u8 *)(*enet_addr), 0);

	वापस 0;
पूर्ण

पूर्णांक memac_add_hash_mac_address(काष्ठा fman_mac *memac, enet_addr_t *eth_addr)
अणु
	काष्ठा memac_regs __iomem *regs = memac->regs;
	काष्ठा eth_hash_entry *hash_entry;
	u32 hash;
	u64 addr;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	addr = ENET_ADDR_TO_UINT64(*eth_addr);

	अगर (!(addr & GROUP_ADDRESS)) अणु
		/* Unicast addresses not supported in hash */
		pr_err("Unicast Address\n");
		वापस -EINVAL;
	पूर्ण
	hash = get_mac_addr_hash_code(addr) & HASH_CTRL_ADDR_MASK;

	/* Create element to be added to the driver hash table */
	hash_entry = kदो_स्मृति(माप(*hash_entry), GFP_ATOMIC);
	अगर (!hash_entry)
		वापस -ENOMEM;
	hash_entry->addr = addr;
	INIT_LIST_HEAD(&hash_entry->node);

	list_add_tail(&hash_entry->node,
		      &memac->multicast_addr_hash->lsts[hash]);
	ioग_लिखो32be(hash | HASH_CTRL_MCAST_EN, &regs->hashtable_ctrl);

	वापस 0;
पूर्ण

पूर्णांक memac_set_allmulti(काष्ठा fman_mac *memac, bool enable)
अणु
	u32 entry;
	काष्ठा memac_regs __iomem *regs = memac->regs;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	अगर (enable) अणु
		क्रम (entry = 0; entry < HASH_TABLE_SIZE; entry++)
			ioग_लिखो32be(entry | HASH_CTRL_MCAST_EN,
				    &regs->hashtable_ctrl);
	पूर्ण अन्यथा अणु
		क्रम (entry = 0; entry < HASH_TABLE_SIZE; entry++)
			ioग_लिखो32be(entry & ~HASH_CTRL_MCAST_EN,
				    &regs->hashtable_ctrl);
	पूर्ण

	memac->allmulti_enabled = enable;

	वापस 0;
पूर्ण

पूर्णांक memac_set_tstamp(काष्ठा fman_mac *memac, bool enable)
अणु
	वापस 0; /* Always enabled. */
पूर्ण

पूर्णांक memac_del_hash_mac_address(काष्ठा fman_mac *memac, enet_addr_t *eth_addr)
अणु
	काष्ठा memac_regs __iomem *regs = memac->regs;
	काष्ठा eth_hash_entry *hash_entry = शून्य;
	काष्ठा list_head *pos;
	u32 hash;
	u64 addr;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	addr = ENET_ADDR_TO_UINT64(*eth_addr);

	hash = get_mac_addr_hash_code(addr) & HASH_CTRL_ADDR_MASK;

	list_क्रम_each(pos, &memac->multicast_addr_hash->lsts[hash]) अणु
		hash_entry = ETH_HASH_ENTRY_OBJ(pos);
		अगर (hash_entry && hash_entry->addr == addr) अणु
			list_del_init(&hash_entry->node);
			kमुक्त(hash_entry);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!memac->allmulti_enabled) अणु
		अगर (list_empty(&memac->multicast_addr_hash->lsts[hash]))
			ioग_लिखो32be(hash & ~HASH_CTRL_MCAST_EN,
				    &regs->hashtable_ctrl);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक memac_set_exception(काष्ठा fman_mac *memac,
			क्रमागत fman_mac_exceptions exception, bool enable)
अणु
	u32 bit_mask = 0;

	अगर (!is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	bit_mask = get_exception_flag(exception);
	अगर (bit_mask) अणु
		अगर (enable)
			memac->exceptions |= bit_mask;
		अन्यथा
			memac->exceptions &= ~bit_mask;
	पूर्ण अन्यथा अणु
		pr_err("Undefined exception\n");
		वापस -EINVAL;
	पूर्ण
	set_exception(memac->regs, bit_mask, enable);

	वापस 0;
पूर्ण

पूर्णांक memac_init(काष्ठा fman_mac *memac)
अणु
	काष्ठा memac_cfg *memac_drv_param;
	u8 i;
	enet_addr_t eth_addr;
	bool slow_10g_अगर = false;
	काष्ठा fixed_phy_status *fixed_link;
	पूर्णांक err;
	u32 reg32 = 0;

	अगर (is_init_करोne(memac->memac_drv_param))
		वापस -EINVAL;

	err = check_init_parameters(memac);
	अगर (err)
		वापस err;

	memac_drv_param = memac->memac_drv_param;

	अगर (memac->fm_rev_info.major == 6 && memac->fm_rev_info.minor == 4)
		slow_10g_अगर = true;

	/* First, reset the MAC अगर desired. */
	अगर (memac_drv_param->reset_on_init) अणु
		err = reset(memac->regs);
		अगर (err) अणु
			pr_err("mEMAC reset failed\n");
			वापस err;
		पूर्ण
	पूर्ण

	/* MAC Address */
	अगर (memac->addr != 0) अणु
		MAKE_ENET_ADDR_FROM_UINT64(memac->addr, eth_addr);
		add_addr_in_paddr(memac->regs, (u8 *)eth_addr, 0);
	पूर्ण

	fixed_link = memac_drv_param->fixed_link;

	init(memac->regs, memac->memac_drv_param, memac->phy_अगर,
	     memac->max_speed, slow_10g_अगर, memac->exceptions);

	/* FM_RX_FIFO_CORRUPT_ERRATA_10GMAC_A006320 errata workaround
	 * Exists only in FMan 6.0 and 6.3.
	 */
	अगर ((memac->fm_rev_info.major == 6) &&
	    ((memac->fm_rev_info.minor == 0) ||
	    (memac->fm_rev_info.minor == 3))) अणु
		/* MAC strips CRC from received frames - this workaround
		 * should decrease the likelihood of bug appearance
		 */
		reg32 = ioपढ़ो32be(&memac->regs->command_config);
		reg32 &= ~CMD_CFG_CRC_FWD;
		ioग_लिखो32be(reg32, &memac->regs->command_config);
	पूर्ण

	अगर (memac->phy_अगर == PHY_INTERFACE_MODE_SGMII) अणु
		/* Configure पूर्णांकernal SGMII PHY */
		अगर (memac->basex_अगर)
			setup_sgmii_पूर्णांकernal_phy_base_x(memac);
		अन्यथा
			setup_sgmii_पूर्णांकernal_phy(memac, fixed_link);
	पूर्ण अन्यथा अगर (memac->phy_अगर == PHY_INTERFACE_MODE_QSGMII) अणु
		/* Configure 4 पूर्णांकernal SGMII PHYs */
		क्रम (i = 0; i < 4; i++) अणु
			u8 qsmgii_phy_addr, phy_addr;
			/* QSGMII PHY address occupies 3 upper bits of 5-bit
			 * phy_address; the lower 2 bits are used to extend
			 * रेजिस्टर address space and access each one of 4
			 * ports inside QSGMII.
			 */
			phy_addr = memac->pcsphy->mdio.addr;
			qsmgii_phy_addr = (u8)((phy_addr << 2) | i);
			memac->pcsphy->mdio.addr = qsmgii_phy_addr;
			अगर (memac->basex_अगर)
				setup_sgmii_पूर्णांकernal_phy_base_x(memac);
			अन्यथा
				setup_sgmii_पूर्णांकernal_phy(memac, fixed_link);

			memac->pcsphy->mdio.addr = phy_addr;
		पूर्ण
	पूर्ण

	/* Max Frame Length */
	err = fman_set_mac_max_frame(memac->fm, memac->mac_id,
				     memac_drv_param->max_frame_length);
	अगर (err) अणु
		pr_err("settings Mac max frame length is FAILED\n");
		वापस err;
	पूर्ण

	memac->multicast_addr_hash = alloc_hash_table(HASH_TABLE_SIZE);
	अगर (!memac->multicast_addr_hash) अणु
		मुक्त_init_resources(memac);
		pr_err("allocation hash table is FAILED\n");
		वापस -ENOMEM;
	पूर्ण

	memac->unicast_addr_hash = alloc_hash_table(HASH_TABLE_SIZE);
	अगर (!memac->unicast_addr_hash) अणु
		मुक्त_init_resources(memac);
		pr_err("allocation hash table is FAILED\n");
		वापस -ENOMEM;
	पूर्ण

	fman_रेजिस्टर_पूर्णांकr(memac->fm, FMAN_MOD_MAC, memac->mac_id,
			   FMAN_INTR_TYPE_ERR, memac_err_exception, memac);

	fman_रेजिस्टर_पूर्णांकr(memac->fm, FMAN_MOD_MAC, memac->mac_id,
			   FMAN_INTR_TYPE_NORMAL, memac_exception, memac);

	kमुक्त(memac_drv_param);
	memac->memac_drv_param = शून्य;

	वापस 0;
पूर्ण

पूर्णांक memac_मुक्त(काष्ठा fman_mac *memac)
अणु
	मुक्त_init_resources(memac);

	अगर (memac->pcsphy)
		put_device(&memac->pcsphy->mdio.dev);

	kमुक्त(memac->memac_drv_param);
	kमुक्त(memac);

	वापस 0;
पूर्ण

काष्ठा fman_mac *memac_config(काष्ठा fman_mac_params *params)
अणु
	काष्ठा fman_mac *memac;
	काष्ठा memac_cfg *memac_drv_param;
	व्योम __iomem *base_addr;

	base_addr = params->base_addr;
	/* allocate memory क्रम the m_emac data काष्ठाure */
	memac = kzalloc(माप(*memac), GFP_KERNEL);
	अगर (!memac)
		वापस शून्य;

	/* allocate memory क्रम the m_emac driver parameters data काष्ठाure */
	memac_drv_param = kzalloc(माप(*memac_drv_param), GFP_KERNEL);
	अगर (!memac_drv_param) अणु
		memac_मुक्त(memac);
		वापस शून्य;
	पूर्ण

	/* Plant parameter काष्ठाure poपूर्णांकer */
	memac->memac_drv_param = memac_drv_param;

	set_dflts(memac_drv_param);

	memac->addr = ENET_ADDR_TO_UINT64(params->addr);

	memac->regs = base_addr;
	memac->max_speed = params->max_speed;
	memac->phy_अगर = params->phy_अगर;
	memac->mac_id = params->mac_id;
	memac->exceptions = (MEMAC_IMASK_TSECC_ER | MEMAC_IMASK_TECC_ER |
			     MEMAC_IMASK_RECC_ER | MEMAC_IMASK_MGI);
	memac->exception_cb = params->exception_cb;
	memac->event_cb = params->event_cb;
	memac->dev_id = params->dev_id;
	memac->fm = params->fm;
	memac->basex_अगर = params->basex_अगर;

	/* Save FMan revision */
	fman_get_revision(memac->fm, &memac->fm_rev_info);

	अगर (memac->phy_अगर == PHY_INTERFACE_MODE_SGMII ||
	    memac->phy_अगर == PHY_INTERFACE_MODE_QSGMII) अणु
		अगर (!params->पूर्णांकernal_phy_node) अणु
			pr_err("PCS PHY node is not available\n");
			memac_मुक्त(memac);
			वापस शून्य;
		पूर्ण

		memac->pcsphy = of_phy_find_device(params->पूर्णांकernal_phy_node);
		अगर (!memac->pcsphy) अणु
			pr_err("of_phy_find_device (PCS PHY) failed\n");
			memac_मुक्त(memac);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस memac;
पूर्ण
