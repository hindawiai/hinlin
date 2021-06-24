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

#समावेश "fman_tgec.h"
#समावेश "fman.h"

#समावेश <linux/slab.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/पन.स>
#समावेश <linux/crc32.h>

/* Transmit Inter-Packet Gap Length Register (TX_IPG_LENGTH) */
#घोषणा TGEC_TX_IPG_LENGTH_MASK	0x000003ff

/* Command and Configuration Register (COMMAND_CONFIG) */
#घोषणा CMD_CFG_EN_TIMESTAMP		0x00100000
#घोषणा CMD_CFG_NO_LEN_CHK		0x00020000
#घोषणा CMD_CFG_PAUSE_IGNORE		0x00000100
#घोषणा CMF_CFG_CRC_FWD			0x00000040
#घोषणा CMD_CFG_PROMIS_EN		0x00000010
#घोषणा CMD_CFG_RX_EN			0x00000002
#घोषणा CMD_CFG_TX_EN			0x00000001

/* Interrupt Mask Register (IMASK) */
#घोषणा TGEC_IMASK_MDIO_SCAN_EVENT	0x00010000
#घोषणा TGEC_IMASK_MDIO_CMD_CMPL	0x00008000
#घोषणा TGEC_IMASK_REM_FAULT		0x00004000
#घोषणा TGEC_IMASK_LOC_FAULT		0x00002000
#घोषणा TGEC_IMASK_TX_ECC_ER		0x00001000
#घोषणा TGEC_IMASK_TX_FIFO_UNFL	0x00000800
#घोषणा TGEC_IMASK_TX_FIFO_OVFL	0x00000400
#घोषणा TGEC_IMASK_TX_ER		0x00000200
#घोषणा TGEC_IMASK_RX_FIFO_OVFL	0x00000100
#घोषणा TGEC_IMASK_RX_ECC_ER		0x00000080
#घोषणा TGEC_IMASK_RX_JAB_FRM		0x00000040
#घोषणा TGEC_IMASK_RX_OVRSZ_FRM	0x00000020
#घोषणा TGEC_IMASK_RX_RUNT_FRM		0x00000010
#घोषणा TGEC_IMASK_RX_FRAG_FRM		0x00000008
#घोषणा TGEC_IMASK_RX_LEN_ER		0x00000004
#घोषणा TGEC_IMASK_RX_CRC_ER		0x00000002
#घोषणा TGEC_IMASK_RX_ALIGN_ER		0x00000001

/* Hashtable Control Register (HASHTABLE_CTRL) */
#घोषणा TGEC_HASH_MCAST_SHIFT		23
#घोषणा TGEC_HASH_MCAST_EN		0x00000200
#घोषणा TGEC_HASH_ADR_MSK		0x000001ff

#घोषणा DEFAULT_TX_IPG_LENGTH			12
#घोषणा DEFAULT_MAX_FRAME_LENGTH		0x600
#घोषणा DEFAULT_PAUSE_QUANT			0xf000

/* number of pattern match रेजिस्टरs (entries) */
#घोषणा TGEC_NUM_OF_PADDRS          1

/* Group address bit indication */
#घोषणा GROUP_ADDRESS               0x0000010000000000LL

/* Hash table size (= 32 bits*8 regs) */
#घोषणा TGEC_HASH_TABLE_SIZE             512

/* tGEC memory map */
काष्ठा tgec_regs अणु
	u32 tgec_id;		/* 0x000 Controller ID */
	u32 reserved001[1];	/* 0x004 */
	u32 command_config;	/* 0x008 Control and configuration */
	u32 mac_addr_0;		/* 0x00c Lower 32 bits of the MAC adr */
	u32 mac_addr_1;		/* 0x010 Upper 16 bits of the MAC adr */
	u32 maxfrm;		/* 0x014 Maximum frame length */
	u32 छोड़ो_quant;	/* 0x018 Pause quanta */
	u32 rx_fअगरo_sections;	/* 0x01c  */
	u32 tx_fअगरo_sections;	/* 0x020  */
	u32 rx_fअगरo_almost_f_e;	/* 0x024  */
	u32 tx_fअगरo_almost_f_e;	/* 0x028  */
	u32 hashtable_ctrl;	/* 0x02c Hash table control */
	u32 mdio_cfg_status;	/* 0x030  */
	u32 mdio_command;	/* 0x034  */
	u32 mdio_data;		/* 0x038  */
	u32 mdio_regaddr;	/* 0x03c  */
	u32 status;		/* 0x040  */
	u32 tx_ipg_len;		/* 0x044 Transmitter पूर्णांकer-packet-gap */
	u32 mac_addr_2;		/* 0x048 Lower 32 bits of 2nd MAC adr */
	u32 mac_addr_3;		/* 0x04c Upper 16 bits of 2nd MAC adr */
	u32 rx_fअगरo_ptr_rd;	/* 0x050  */
	u32 rx_fअगरo_ptr_wr;	/* 0x054  */
	u32 tx_fअगरo_ptr_rd;	/* 0x058  */
	u32 tx_fअगरo_ptr_wr;	/* 0x05c  */
	u32 imask;		/* 0x060 Interrupt mask */
	u32 ievent;		/* 0x064 Interrupt event */
	u32 udp_port;		/* 0x068 Defines a UDP Port number */
	u32 type_1588v2;	/* 0x06c Type field क्रम 1588v2 */
	u32 reserved070[4];	/* 0x070 */
	/* 10Ge Statistics Counter */
	u32 tfrm_u;		/* 80 aFramesTransmittedOK */
	u32 tfrm_l;		/* 84 aFramesTransmittedOK */
	u32 rfrm_u;		/* 88 aFramesReceivedOK */
	u32 rfrm_l;		/* 8c aFramesReceivedOK */
	u32 rfcs_u;		/* 90 aFrameCheckSequenceErrors */
	u32 rfcs_l;		/* 94 aFrameCheckSequenceErrors */
	u32 raln_u;		/* 98 aAlignmentErrors */
	u32 raln_l;		/* 9c aAlignmentErrors */
	u32 txpf_u;		/* A0 aPAUSEMACCtrlFramesTransmitted */
	u32 txpf_l;		/* A4 aPAUSEMACCtrlFramesTransmitted */
	u32 rxpf_u;		/* A8 aPAUSEMACCtrlFramesReceived */
	u32 rxpf_l;		/* Ac aPAUSEMACCtrlFramesReceived */
	u32 rदीर्घ_u;		/* B0 aFrameTooLongErrors */
	u32 rदीर्घ_l;		/* B4 aFrameTooLongErrors */
	u32 rflr_u;		/* B8 aInRangeLengthErrors */
	u32 rflr_l;		/* Bc aInRangeLengthErrors */
	u32 tvlan_u;		/* C0 VLANTransmittedOK */
	u32 tvlan_l;		/* C4 VLANTransmittedOK */
	u32 rvlan_u;		/* C8 VLANReceivedOK */
	u32 rvlan_l;		/* Cc VLANReceivedOK */
	u32 toct_u;		/* D0 अगर_out_octets */
	u32 toct_l;		/* D4 अगर_out_octets */
	u32 roct_u;		/* D8 अगर_in_octets */
	u32 roct_l;		/* Dc अगर_in_octets */
	u32 ruca_u;		/* E0 अगर_in_ucast_pkts */
	u32 ruca_l;		/* E4 अगर_in_ucast_pkts */
	u32 rmca_u;		/* E8 अगरInMulticastPkts */
	u32 rmca_l;		/* Ec अगरInMulticastPkts */
	u32 rbca_u;		/* F0 अगरInBroadcastPkts */
	u32 rbca_l;		/* F4 अगरInBroadcastPkts */
	u32 terr_u;		/* F8 अगर_out_errors */
	u32 terr_l;		/* Fc अगर_out_errors */
	u32 reserved100[2];	/* 100-108 */
	u32 tuca_u;		/* 108 अगर_out_ucast_pkts */
	u32 tuca_l;		/* 10c अगर_out_ucast_pkts */
	u32 पंचांगca_u;		/* 110 अगरOutMulticastPkts */
	u32 पंचांगca_l;		/* 114 अगरOutMulticastPkts */
	u32 tbca_u;		/* 118 अगरOutBroadcastPkts */
	u32 tbca_l;		/* 11c अगरOutBroadcastPkts */
	u32 rdrp_u;		/* 120 etherStatsDropEvents */
	u32 rdrp_l;		/* 124 etherStatsDropEvents */
	u32 reoct_u;		/* 128 etherStatsOctets */
	u32 reoct_l;		/* 12c etherStatsOctets */
	u32 rpkt_u;		/* 130 etherStatsPkts */
	u32 rpkt_l;		/* 134 etherStatsPkts */
	u32 trund_u;		/* 138 etherStatsUndersizePkts */
	u32 trund_l;		/* 13c etherStatsUndersizePkts */
	u32 r64_u;		/* 140 etherStatsPkts64Octets */
	u32 r64_l;		/* 144 etherStatsPkts64Octets */
	u32 r127_u;		/* 148 etherStatsPkts65to127Octets */
	u32 r127_l;		/* 14c etherStatsPkts65to127Octets */
	u32 r255_u;		/* 150 etherStatsPkts128to255Octets */
	u32 r255_l;		/* 154 etherStatsPkts128to255Octets */
	u32 r511_u;		/* 158 etherStatsPkts256to511Octets */
	u32 r511_l;		/* 15c etherStatsPkts256to511Octets */
	u32 r1023_u;		/* 160 etherStatsPkts512to1023Octets */
	u32 r1023_l;		/* 164 etherStatsPkts512to1023Octets */
	u32 r1518_u;		/* 168 etherStatsPkts1024to1518Octets */
	u32 r1518_l;		/* 16c etherStatsPkts1024to1518Octets */
	u32 r1519x_u;		/* 170 etherStatsPkts1519toX */
	u32 r1519x_l;		/* 174 etherStatsPkts1519toX */
	u32 trovr_u;		/* 178 etherStatsOversizePkts */
	u32 trovr_l;		/* 17c etherStatsOversizePkts */
	u32 trjbr_u;		/* 180 etherStatsJabbers */
	u32 trjbr_l;		/* 184 etherStatsJabbers */
	u32 trfrg_u;		/* 188 etherStatsFragments */
	u32 trfrg_l;		/* 18C etherStatsFragments */
	u32 rerr_u;		/* 190 अगर_in_errors */
	u32 rerr_l;		/* 194 अगर_in_errors */
पूर्ण;

काष्ठा tgec_cfg अणु
	bool छोड़ो_ignore;
	bool promiscuous_mode_enable;
	u16 max_frame_length;
	u16 छोड़ो_quant;
	u32 tx_ipg_length;
पूर्ण;

काष्ठा fman_mac अणु
	/* Poपूर्णांकer to the memory mapped रेजिस्टरs. */
	काष्ठा tgec_regs __iomem *regs;
	/* MAC address of device; */
	u64 addr;
	u16 max_speed;
	व्योम *dev_id; /* device cookie used by the exception cbs */
	fman_mac_exception_cb *exception_cb;
	fman_mac_exception_cb *event_cb;
	/* poपूर्णांकer to driver's global address hash table  */
	काष्ठा eth_hash_t *multicast_addr_hash;
	/* poपूर्णांकer to driver's inभागidual address hash table  */
	काष्ठा eth_hash_t *unicast_addr_hash;
	u8 mac_id;
	u32 exceptions;
	काष्ठा tgec_cfg *cfg;
	व्योम *fm;
	काष्ठा fman_rev_info fm_rev_info;
	bool allmulti_enabled;
पूर्ण;

अटल व्योम set_mac_address(काष्ठा tgec_regs __iomem *regs, u8 *adr)
अणु
	u32 पंचांगp0, पंचांगp1;

	पंचांगp0 = (u32)(adr[0] | adr[1] << 8 | adr[2] << 16 | adr[3] << 24);
	पंचांगp1 = (u32)(adr[4] | adr[5] << 8);
	ioग_लिखो32be(पंचांगp0, &regs->mac_addr_0);
	ioग_लिखो32be(पंचांगp1, &regs->mac_addr_1);
पूर्ण

अटल व्योम set_dflts(काष्ठा tgec_cfg *cfg)
अणु
	cfg->promiscuous_mode_enable = false;
	cfg->छोड़ो_ignore = false;
	cfg->tx_ipg_length = DEFAULT_TX_IPG_LENGTH;
	cfg->max_frame_length = DEFAULT_MAX_FRAME_LENGTH;
	cfg->छोड़ो_quant = DEFAULT_PAUSE_QUANT;
पूर्ण

अटल पूर्णांक init(काष्ठा tgec_regs __iomem *regs, काष्ठा tgec_cfg *cfg,
		u32 exception_mask)
अणु
	u32 पंचांगp;

	/* Config */
	पंचांगp = CMF_CFG_CRC_FWD;
	अगर (cfg->promiscuous_mode_enable)
		पंचांगp |= CMD_CFG_PROMIS_EN;
	अगर (cfg->छोड़ो_ignore)
		पंचांगp |= CMD_CFG_PAUSE_IGNORE;
	/* Payload length check disable */
	पंचांगp |= CMD_CFG_NO_LEN_CHK;
	ioग_लिखो32be(पंचांगp, &regs->command_config);

	/* Max Frame Length */
	ioग_लिखो32be((u32)cfg->max_frame_length, &regs->maxfrm);
	/* Pause Time */
	ioग_लिखो32be(cfg->छोड़ो_quant, &regs->छोड़ो_quant);

	/* clear all pending events and set-up पूर्णांकerrupts */
	ioग_लिखो32be(0xffffffff, &regs->ievent);
	ioग_लिखो32be(ioपढ़ो32be(&regs->imask) | exception_mask, &regs->imask);

	वापस 0;
पूर्ण

अटल पूर्णांक check_init_parameters(काष्ठा fman_mac *tgec)
अणु
	अगर (tgec->max_speed < SPEED_10000) अणु
		pr_err("10G MAC driver only support 10G speed\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tgec->exception_cb) अणु
		pr_err("uninitialized exception_cb\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tgec->event_cb) अणु
		pr_err("uninitialized event_cb\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_exception_flag(क्रमागत fman_mac_exceptions exception)
अणु
	u32 bit_mask;

	चयन (exception) अणु
	हाल FM_MAC_EX_10G_MDIO_SCAN_EVENT:
		bit_mask = TGEC_IMASK_MDIO_SCAN_EVENT;
		अवरोध;
	हाल FM_MAC_EX_10G_MDIO_CMD_CMPL:
		bit_mask = TGEC_IMASK_MDIO_CMD_CMPL;
		अवरोध;
	हाल FM_MAC_EX_10G_REM_FAULT:
		bit_mask = TGEC_IMASK_REM_FAULT;
		अवरोध;
	हाल FM_MAC_EX_10G_LOC_FAULT:
		bit_mask = TGEC_IMASK_LOC_FAULT;
		अवरोध;
	हाल FM_MAC_EX_10G_TX_ECC_ER:
		bit_mask = TGEC_IMASK_TX_ECC_ER;
		अवरोध;
	हाल FM_MAC_EX_10G_TX_FIFO_UNFL:
		bit_mask = TGEC_IMASK_TX_FIFO_UNFL;
		अवरोध;
	हाल FM_MAC_EX_10G_TX_FIFO_OVFL:
		bit_mask = TGEC_IMASK_TX_FIFO_OVFL;
		अवरोध;
	हाल FM_MAC_EX_10G_TX_ER:
		bit_mask = TGEC_IMASK_TX_ER;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_FIFO_OVFL:
		bit_mask = TGEC_IMASK_RX_FIFO_OVFL;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_ECC_ER:
		bit_mask = TGEC_IMASK_RX_ECC_ER;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_JAB_FRM:
		bit_mask = TGEC_IMASK_RX_JAB_FRM;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_OVRSZ_FRM:
		bit_mask = TGEC_IMASK_RX_OVRSZ_FRM;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_RUNT_FRM:
		bit_mask = TGEC_IMASK_RX_RUNT_FRM;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_FRAG_FRM:
		bit_mask = TGEC_IMASK_RX_FRAG_FRM;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_LEN_ER:
		bit_mask = TGEC_IMASK_RX_LEN_ER;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_CRC_ER:
		bit_mask = TGEC_IMASK_RX_CRC_ER;
		अवरोध;
	हाल FM_MAC_EX_10G_RX_ALIGN_ER:
		bit_mask = TGEC_IMASK_RX_ALIGN_ER;
		अवरोध;
	शेष:
		bit_mask = 0;
		अवरोध;
	पूर्ण

	वापस bit_mask;
पूर्ण

अटल व्योम tgec_err_exception(व्योम *handle)
अणु
	काष्ठा fman_mac *tgec = (काष्ठा fman_mac *)handle;
	काष्ठा tgec_regs __iomem *regs = tgec->regs;
	u32 event;

	/* करो not handle MDIO events */
	event = ioपढ़ो32be(&regs->ievent) &
			   ~(TGEC_IMASK_MDIO_SCAN_EVENT |
			   TGEC_IMASK_MDIO_CMD_CMPL);

	event &= ioपढ़ो32be(&regs->imask);

	ioग_लिखो32be(event, &regs->ievent);

	अगर (event & TGEC_IMASK_REM_FAULT)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_REM_FAULT);
	अगर (event & TGEC_IMASK_LOC_FAULT)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_LOC_FAULT);
	अगर (event & TGEC_IMASK_TX_ECC_ER)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_TX_ECC_ER);
	अगर (event & TGEC_IMASK_TX_FIFO_UNFL)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_TX_FIFO_UNFL);
	अगर (event & TGEC_IMASK_TX_FIFO_OVFL)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_TX_FIFO_OVFL);
	अगर (event & TGEC_IMASK_TX_ER)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_TX_ER);
	अगर (event & TGEC_IMASK_RX_FIFO_OVFL)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_RX_FIFO_OVFL);
	अगर (event & TGEC_IMASK_RX_ECC_ER)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_RX_ECC_ER);
	अगर (event & TGEC_IMASK_RX_JAB_FRM)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_RX_JAB_FRM);
	अगर (event & TGEC_IMASK_RX_OVRSZ_FRM)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_RX_OVRSZ_FRM);
	अगर (event & TGEC_IMASK_RX_RUNT_FRM)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_RX_RUNT_FRM);
	अगर (event & TGEC_IMASK_RX_FRAG_FRM)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_RX_FRAG_FRM);
	अगर (event & TGEC_IMASK_RX_LEN_ER)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_RX_LEN_ER);
	अगर (event & TGEC_IMASK_RX_CRC_ER)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_RX_CRC_ER);
	अगर (event & TGEC_IMASK_RX_ALIGN_ER)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_RX_ALIGN_ER);
पूर्ण

अटल व्योम मुक्त_init_resources(काष्ठा fman_mac *tgec)
अणु
	fman_unरेजिस्टर_पूर्णांकr(tgec->fm, FMAN_MOD_MAC, tgec->mac_id,
			     FMAN_INTR_TYPE_ERR);

	/* release the driver's group hash table */
	मुक्त_hash_table(tgec->multicast_addr_hash);
	tgec->multicast_addr_hash = शून्य;

	/* release the driver's inभागidual hash table */
	मुक्त_hash_table(tgec->unicast_addr_hash);
	tgec->unicast_addr_hash = शून्य;
पूर्ण

अटल bool is_init_करोne(काष्ठा tgec_cfg *cfg)
अणु
	/* Checks अगर tGEC driver parameters were initialized */
	अगर (!cfg)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक tgec_enable(काष्ठा fman_mac *tgec, क्रमागत comm_mode mode)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->command_config);
	अगर (mode & COMM_MODE_RX)
		पंचांगp |= CMD_CFG_RX_EN;
	अगर (mode & COMM_MODE_TX)
		पंचांगp |= CMD_CFG_TX_EN;
	ioग_लिखो32be(पंचांगp, &regs->command_config);

	वापस 0;
पूर्ण

पूर्णांक tgec_disable(काष्ठा fman_mac *tgec, क्रमागत comm_mode mode)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->command_config);
	अगर (mode & COMM_MODE_RX)
		पंचांगp &= ~CMD_CFG_RX_EN;
	अगर (mode & COMM_MODE_TX)
		पंचांगp &= ~CMD_CFG_TX_EN;
	ioग_लिखो32be(पंचांगp, &regs->command_config);

	वापस 0;
पूर्ण

पूर्णांक tgec_set_promiscuous(काष्ठा fman_mac *tgec, bool new_val)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->command_config);
	अगर (new_val)
		पंचांगp |= CMD_CFG_PROMIS_EN;
	अन्यथा
		पंचांगp &= ~CMD_CFG_PROMIS_EN;
	ioग_लिखो32be(पंचांगp, &regs->command_config);

	वापस 0;
पूर्ण

पूर्णांक tgec_cfg_max_frame_len(काष्ठा fman_mac *tgec, u16 new_val)
अणु
	अगर (is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	tgec->cfg->max_frame_length = new_val;

	वापस 0;
पूर्ण

पूर्णांक tgec_set_tx_छोड़ो_frames(काष्ठा fman_mac *tgec, u8 __maybe_unused priority,
			     u16 छोड़ो_समय, u16 __maybe_unused thresh_समय)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	ioग_लिखो32be((u32)छोड़ो_समय, &regs->छोड़ो_quant);

	वापस 0;
पूर्ण

पूर्णांक tgec_accept_rx_छोड़ो_frames(काष्ठा fman_mac *tgec, bool en)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->command_config);
	अगर (!en)
		पंचांगp |= CMD_CFG_PAUSE_IGNORE;
	अन्यथा
		पंचांगp &= ~CMD_CFG_PAUSE_IGNORE;
	ioग_लिखो32be(पंचांगp, &regs->command_config);

	वापस 0;
पूर्ण

पूर्णांक tgec_modअगरy_mac_address(काष्ठा fman_mac *tgec, enet_addr_t *p_enet_addr)
अणु
	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	tgec->addr = ENET_ADDR_TO_UINT64(*p_enet_addr);
	set_mac_address(tgec->regs, (u8 *)(*p_enet_addr));

	वापस 0;
पूर्ण

पूर्णांक tgec_add_hash_mac_address(काष्ठा fman_mac *tgec, enet_addr_t *eth_addr)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;
	काष्ठा eth_hash_entry *hash_entry;
	u32 crc = 0xFFFFFFFF, hash;
	u64 addr;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	addr = ENET_ADDR_TO_UINT64(*eth_addr);

	अगर (!(addr & GROUP_ADDRESS)) अणु
		/* Unicast addresses not supported in hash */
		pr_err("Unicast Address\n");
		वापस -EINVAL;
	पूर्ण
	/* CRC calculation */
	crc = crc32_le(crc, (u8 *)eth_addr, ETH_ALEN);
	crc = bitrev32(crc);
	/* Take 9 MSB bits */
	hash = (crc >> TGEC_HASH_MCAST_SHIFT) & TGEC_HASH_ADR_MSK;

	/* Create element to be added to the driver hash table */
	hash_entry = kदो_स्मृति(माप(*hash_entry), GFP_ATOMIC);
	अगर (!hash_entry)
		वापस -ENOMEM;
	hash_entry->addr = addr;
	INIT_LIST_HEAD(&hash_entry->node);

	list_add_tail(&hash_entry->node,
		      &tgec->multicast_addr_hash->lsts[hash]);
	ioग_लिखो32be((hash | TGEC_HASH_MCAST_EN), &regs->hashtable_ctrl);

	वापस 0;
पूर्ण

पूर्णांक tgec_set_allmulti(काष्ठा fman_mac *tgec, bool enable)
अणु
	u32 entry;
	काष्ठा tgec_regs __iomem *regs = tgec->regs;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	अगर (enable) अणु
		क्रम (entry = 0; entry < TGEC_HASH_TABLE_SIZE; entry++)
			ioग_लिखो32be(entry | TGEC_HASH_MCAST_EN,
				    &regs->hashtable_ctrl);
	पूर्ण अन्यथा अणु
		क्रम (entry = 0; entry < TGEC_HASH_TABLE_SIZE; entry++)
			ioग_लिखो32be(entry & ~TGEC_HASH_MCAST_EN,
				    &regs->hashtable_ctrl);
	पूर्ण

	tgec->allmulti_enabled = enable;

	वापस 0;
पूर्ण

पूर्णांक tgec_set_tstamp(काष्ठा fman_mac *tgec, bool enable)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;
	u32 पंचांगp;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32be(&regs->command_config);

	अगर (enable)
		पंचांगp |= CMD_CFG_EN_TIMESTAMP;
	अन्यथा
		पंचांगp &= ~CMD_CFG_EN_TIMESTAMP;

	ioग_लिखो32be(पंचांगp, &regs->command_config);

	वापस 0;
पूर्ण

पूर्णांक tgec_del_hash_mac_address(काष्ठा fman_mac *tgec, enet_addr_t *eth_addr)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;
	काष्ठा eth_hash_entry *hash_entry = शून्य;
	काष्ठा list_head *pos;
	u32 crc = 0xFFFFFFFF, hash;
	u64 addr;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	addr = ((*(u64 *)eth_addr) >> 16);

	/* CRC calculation */
	crc = crc32_le(crc, (u8 *)eth_addr, ETH_ALEN);
	crc = bitrev32(crc);
	/* Take 9 MSB bits */
	hash = (crc >> TGEC_HASH_MCAST_SHIFT) & TGEC_HASH_ADR_MSK;

	list_क्रम_each(pos, &tgec->multicast_addr_hash->lsts[hash]) अणु
		hash_entry = ETH_HASH_ENTRY_OBJ(pos);
		अगर (hash_entry && hash_entry->addr == addr) अणु
			list_del_init(&hash_entry->node);
			kमुक्त(hash_entry);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!tgec->allmulti_enabled) अणु
		अगर (list_empty(&tgec->multicast_addr_hash->lsts[hash]))
			ioग_लिखो32be((hash & ~TGEC_HASH_MCAST_EN),
				    &regs->hashtable_ctrl);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tgec_get_version(काष्ठा fman_mac *tgec, u32 *mac_version)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	*mac_version = ioपढ़ो32be(&regs->tgec_id);

	वापस 0;
पूर्ण

पूर्णांक tgec_set_exception(काष्ठा fman_mac *tgec,
		       क्रमागत fman_mac_exceptions exception, bool enable)
अणु
	काष्ठा tgec_regs __iomem *regs = tgec->regs;
	u32 bit_mask = 0;

	अगर (!is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	bit_mask = get_exception_flag(exception);
	अगर (bit_mask) अणु
		अगर (enable)
			tgec->exceptions |= bit_mask;
		अन्यथा
			tgec->exceptions &= ~bit_mask;
	पूर्ण अन्यथा अणु
		pr_err("Undefined exception\n");
		वापस -EINVAL;
	पूर्ण
	अगर (enable)
		ioग_लिखो32be(ioपढ़ो32be(&regs->imask) | bit_mask, &regs->imask);
	अन्यथा
		ioग_लिखो32be(ioपढ़ो32be(&regs->imask) & ~bit_mask, &regs->imask);

	वापस 0;
पूर्ण

पूर्णांक tgec_init(काष्ठा fman_mac *tgec)
अणु
	काष्ठा tgec_cfg *cfg;
	enet_addr_t eth_addr;
	पूर्णांक err;

	अगर (is_init_करोne(tgec->cfg))
		वापस -EINVAL;

	अगर (DEFAULT_RESET_ON_INIT &&
	    (fman_reset_mac(tgec->fm, tgec->mac_id) != 0)) अणु
		pr_err("Can't reset MAC!\n");
		वापस -EINVAL;
	पूर्ण

	err = check_init_parameters(tgec);
	अगर (err)
		वापस err;

	cfg = tgec->cfg;

	अगर (tgec->addr) अणु
		MAKE_ENET_ADDR_FROM_UINT64(tgec->addr, eth_addr);
		set_mac_address(tgec->regs, (u8 *)eth_addr);
	पूर्ण

	/* पूर्णांकerrupts */
	/* FM_10G_REM_N_LCL_FLT_EX_10GMAC_ERRATA_SW005 Errata workaround */
	अगर (tgec->fm_rev_info.major <= 2)
		tgec->exceptions &= ~(TGEC_IMASK_REM_FAULT |
				      TGEC_IMASK_LOC_FAULT);

	err = init(tgec->regs, cfg, tgec->exceptions);
	अगर (err) अणु
		मुक्त_init_resources(tgec);
		pr_err("TGEC version doesn't support this i/f mode\n");
		वापस err;
	पूर्ण

	/* Max Frame Length */
	err = fman_set_mac_max_frame(tgec->fm, tgec->mac_id,
				     cfg->max_frame_length);
	अगर (err) अणु
		pr_err("Setting max frame length FAILED\n");
		मुक्त_init_resources(tgec);
		वापस -EINVAL;
	पूर्ण

	/* FM_TX_FIFO_CORRUPTION_ERRATA_10GMAC_A007 Errata workaround */
	अगर (tgec->fm_rev_info.major == 2) अणु
		काष्ठा tgec_regs __iomem *regs = tgec->regs;
		u32 पंचांगp;

		/* restore the शेष tx ipg Length */
		पंचांगp = (ioपढ़ो32be(&regs->tx_ipg_len) &
		       ~TGEC_TX_IPG_LENGTH_MASK) | 12;

		ioग_लिखो32be(पंचांगp, &regs->tx_ipg_len);
	पूर्ण

	tgec->multicast_addr_hash = alloc_hash_table(TGEC_HASH_TABLE_SIZE);
	अगर (!tgec->multicast_addr_hash) अणु
		मुक्त_init_resources(tgec);
		pr_err("allocation hash table is FAILED\n");
		वापस -ENOMEM;
	पूर्ण

	tgec->unicast_addr_hash = alloc_hash_table(TGEC_HASH_TABLE_SIZE);
	अगर (!tgec->unicast_addr_hash) अणु
		मुक्त_init_resources(tgec);
		pr_err("allocation hash table is FAILED\n");
		वापस -ENOMEM;
	पूर्ण

	fman_रेजिस्टर_पूर्णांकr(tgec->fm, FMAN_MOD_MAC, tgec->mac_id,
			   FMAN_INTR_TYPE_ERR, tgec_err_exception, tgec);

	kमुक्त(cfg);
	tgec->cfg = शून्य;

	वापस 0;
पूर्ण

पूर्णांक tgec_मुक्त(काष्ठा fman_mac *tgec)
अणु
	मुक्त_init_resources(tgec);

	kमुक्त(tgec->cfg);
	kमुक्त(tgec);

	वापस 0;
पूर्ण

काष्ठा fman_mac *tgec_config(काष्ठा fman_mac_params *params)
अणु
	काष्ठा fman_mac *tgec;
	काष्ठा tgec_cfg *cfg;
	व्योम __iomem *base_addr;

	base_addr = params->base_addr;
	/* allocate memory क्रम the UCC GETH data काष्ठाure. */
	tgec = kzalloc(माप(*tgec), GFP_KERNEL);
	अगर (!tgec)
		वापस शून्य;

	/* allocate memory क्रम the 10G MAC driver parameters data काष्ठाure. */
	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg) अणु
		tgec_मुक्त(tgec);
		वापस शून्य;
	पूर्ण

	/* Plant parameter काष्ठाure poपूर्णांकer */
	tgec->cfg = cfg;

	set_dflts(cfg);

	tgec->regs = base_addr;
	tgec->addr = ENET_ADDR_TO_UINT64(params->addr);
	tgec->max_speed = params->max_speed;
	tgec->mac_id = params->mac_id;
	tgec->exceptions = (TGEC_IMASK_MDIO_SCAN_EVENT	|
			    TGEC_IMASK_REM_FAULT	|
			    TGEC_IMASK_LOC_FAULT	|
			    TGEC_IMASK_TX_ECC_ER	|
			    TGEC_IMASK_TX_FIFO_UNFL	|
			    TGEC_IMASK_TX_FIFO_OVFL	|
			    TGEC_IMASK_TX_ER		|
			    TGEC_IMASK_RX_FIFO_OVFL	|
			    TGEC_IMASK_RX_ECC_ER	|
			    TGEC_IMASK_RX_JAB_FRM	|
			    TGEC_IMASK_RX_OVRSZ_FRM	|
			    TGEC_IMASK_RX_RUNT_FRM	|
			    TGEC_IMASK_RX_FRAG_FRM	|
			    TGEC_IMASK_RX_CRC_ER	|
			    TGEC_IMASK_RX_ALIGN_ER);
	tgec->exception_cb = params->exception_cb;
	tgec->event_cb = params->event_cb;
	tgec->dev_id = params->dev_id;
	tgec->fm = params->fm;

	/* Save FMan revision */
	fman_get_revision(tgec->fm, &tgec->fm_rev_info);

	वापस tgec;
पूर्ण
