<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Broadcom BCM7xxx System Port Ethernet MAC driver
 *
 * Copyright (C) 2014 Broadcom Corporation
 */

#अगर_अघोषित __BCM_SYSPORT_H
#घोषणा __BCM_SYSPORT_H

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/dim.h>

#समावेश "unimac.h"

/* Receive/transmit descriptor क्रमmat */
#घोषणा DESC_ADDR_HI_STATUS_LEN	0x00
#घोषणा  DESC_ADDR_HI_SHIFT	0
#घोषणा  DESC_ADDR_HI_MASK	0xff
#घोषणा  DESC_STATUS_SHIFT	8
#घोषणा  DESC_STATUS_MASK	0x3ff
#घोषणा  DESC_LEN_SHIFT		18
#घोषणा  DESC_LEN_MASK		0x7fff
#घोषणा DESC_ADDR_LO		0x04

/* HW supports 40-bit addressing hence the */
#घोषणा DESC_SIZE		(WORDS_PER_DESC * माप(u32))

/* Default RX buffer allocation size */
#घोषणा RX_BUF_LENGTH		2048

/* Body(1500) + EH_SIZE(14) + VLANTAG(4) + BRCMTAG(4) + FCS(4) = 1526.
 * 1536 is multiple of 256 bytes
 */
#घोषणा ENET_BRCM_TAG_LEN	4
#घोषणा ENET_PAD		10
#घोषणा UMAC_MAX_MTU_SIZE	(ETH_DATA_LEN + ETH_HLEN + VLAN_HLEN + \
				 ENET_BRCM_TAG_LEN + ETH_FCS_LEN + ENET_PAD)

/* Transmit status block */
काष्ठा bcm_tsb अणु
	u32 pcp_dei_vid;
#घोषणा PCP_DEI_MASK		0xf
#घोषणा VID_SHIFT		4
#घोषणा VID_MASK		0xfff
	u32 l4_ptr_dest_map;
#घोषणा L4_CSUM_PTR_MASK	0x1ff
#घोषणा L4_PTR_SHIFT		9
#घोषणा L4_PTR_MASK		0x1ff
#घोषणा L4_UDP			(1 << 18)
#घोषणा L4_LENGTH_VALID		(1 << 19)
#घोषणा DEST_MAP_SHIFT		20
#घोषणा DEST_MAP_MASK		0x1ff
पूर्ण;

/* Receive status block uses the same
 * definitions as the DMA descriptor
 */
काष्ठा bcm_rsb अणु
	u32 rx_status_len;
	u32 brcm_egress_tag;
पूर्ण;

/* Common Receive/Transmit status bits */
#घोषणा DESC_L4_CSUM		(1 << 7)
#घोषणा DESC_SOP		(1 << 8)
#घोषणा DESC_EOP		(1 << 9)

/* Receive Status bits */
#घोषणा RX_STATUS_UCAST			0
#घोषणा RX_STATUS_BCAST			0x04
#घोषणा RX_STATUS_MCAST			0x08
#घोषणा RX_STATUS_L2_MCAST		0x0c
#घोषणा RX_STATUS_ERR			(1 << 4)
#घोषणा RX_STATUS_OVFLOW		(1 << 5)
#घोषणा RX_STATUS_PARSE_FAIL		(1 << 6)

/* Transmit Status bits */
#घोषणा TX_STATUS_VLAN_NO_ACT		0x00
#घोषणा TX_STATUS_VLAN_PCP_TSB		0x01
#घोषणा TX_STATUS_VLAN_QUEUE		0x02
#घोषणा TX_STATUS_VLAN_VID_TSB		0x03
#घोषणा TX_STATUS_OWR_CRC		(1 << 2)
#घोषणा TX_STATUS_APP_CRC		(1 << 3)
#घोषणा TX_STATUS_BRCM_TAG_NO_ACT	0
#घोषणा TX_STATUS_BRCM_TAG_ZERO		0x10
#घोषणा TX_STATUS_BRCM_TAG_ONE_QUEUE	0x20
#घोषणा TX_STATUS_BRCM_TAG_ONE_TSB	0x30
#घोषणा TX_STATUS_SKIP_BYTES		(1 << 6)

/* Specअगरic रेजिस्टर definitions */
#घोषणा SYS_PORT_TOPCTRL_OFFSET		0
#घोषणा REV_CNTL			0x00
#घोषणा  REV_MASK			0xffff

#घोषणा RX_FLUSH_CNTL			0x04
#घोषणा  RX_FLUSH			(1 << 0)

#घोषणा TX_FLUSH_CNTL			0x08
#घोषणा  TX_FLUSH			(1 << 0)

#घोषणा MISC_CNTL			0x0c
#घोषणा  SYS_CLK_SEL			(1 << 0)
#घोषणा  TDMA_EOP_SEL			(1 << 1)

/* Level-2 Interrupt controller offsets and defines */
#घोषणा SYS_PORT_INTRL2_0_OFFSET	0x200
#घोषणा SYS_PORT_INTRL2_1_OFFSET	0x240
#घोषणा INTRL2_CPU_STATUS		0x00
#घोषणा INTRL2_CPU_SET			0x04
#घोषणा INTRL2_CPU_CLEAR		0x08
#घोषणा INTRL2_CPU_MASK_STATUS		0x0c
#घोषणा INTRL2_CPU_MASK_SET		0x10
#घोषणा INTRL2_CPU_MASK_CLEAR		0x14

/* Level-2 instance 0 पूर्णांकerrupt bits */
#घोषणा INTRL2_0_GISB_ERR		(1 << 0)
#घोषणा INTRL2_0_RBUF_OVFLOW		(1 << 1)
#घोषणा INTRL2_0_TBUF_UNDFLOW		(1 << 2)
#घोषणा INTRL2_0_MPD			(1 << 3)
#घोषणा INTRL2_0_BRCM_MATCH_TAG		(1 << 4)
#घोषणा INTRL2_0_RDMA_MBDONE		(1 << 5)
#घोषणा INTRL2_0_OVER_MAX_THRESH	(1 << 6)
#घोषणा INTRL2_0_BELOW_HYST_THRESH	(1 << 7)
#घोषणा INTRL2_0_FREE_LIST_EMPTY	(1 << 8)
#घोषणा INTRL2_0_TX_RING_FULL		(1 << 9)
#घोषणा INTRL2_0_DESC_ALLOC_ERR		(1 << 10)
#घोषणा INTRL2_0_UNEXP_PKTSIZE_ACK	(1 << 11)

/* SYSTEMPORT Lite groups the TX queues पूर्णांकerrupts on instance 0 */
#घोषणा INTRL2_0_TDMA_MBDONE_SHIFT	12
#घोषणा INTRL2_0_TDMA_MBDONE_MASK	(0xffff << INTRL2_0_TDMA_MBDONE_SHIFT)

/* RXCHK offset and defines */
#घोषणा SYS_PORT_RXCHK_OFFSET		0x300

#घोषणा RXCHK_CONTROL			0x00
#घोषणा  RXCHK_EN			(1 << 0)
#घोषणा  RXCHK_SKIP_FCS			(1 << 1)
#घोषणा  RXCHK_BAD_CSUM_DIS		(1 << 2)
#घोषणा  RXCHK_BRCM_TAG_EN		(1 << 3)
#घोषणा  RXCHK_BRCM_TAG_MATCH_SHIFT	4
#घोषणा  RXCHK_BRCM_TAG_MATCH_MASK	0xff
#घोषणा  RXCHK_PARSE_TNL		(1 << 12)
#घोषणा  RXCHK_VIOL_EN			(1 << 13)
#घोषणा  RXCHK_VIOL_DIS			(1 << 14)
#घोषणा  RXCHK_INCOM_PKT		(1 << 15)
#घोषणा  RXCHK_V6_DUPEXT_EN		(1 << 16)
#घोषणा  RXCHK_V6_DUPEXT_DIS		(1 << 17)
#घोषणा  RXCHK_ETHERTYPE_DIS		(1 << 18)
#घोषणा  RXCHK_L2_HDR_DIS		(1 << 19)
#घोषणा  RXCHK_L3_HDR_DIS		(1 << 20)
#घोषणा  RXCHK_MAC_RX_ERR_DIS		(1 << 21)
#घोषणा  RXCHK_PARSE_AUTH		(1 << 22)

#घोषणा RXCHK_BRCM_TAG0			0x04
#घोषणा RXCHK_BRCM_TAG(i)		((i) * 0x4 + RXCHK_BRCM_TAG0)
#घोषणा RXCHK_BRCM_TAG0_MASK		0x24
#घोषणा RXCHK_BRCM_TAG_MASK(i)		((i) * 0x4 + RXCHK_BRCM_TAG0_MASK)
#घोषणा RXCHK_BRCM_TAG_MATCH_STATUS	0x44
#घोषणा RXCHK_ETHERTYPE			0x48
#घोषणा RXCHK_BAD_CSUM_CNTR		0x4C
#घोषणा RXCHK_OTHER_DISC_CNTR		0x50

#घोषणा RXCHK_BRCM_TAG_MAX		8
#घोषणा RXCHK_BRCM_TAG_CID_SHIFT	16
#घोषणा RXCHK_BRCM_TAG_CID_MASK		0xff

/* TXCHCK offsets and defines */
#घोषणा SYS_PORT_TXCHK_OFFSET		0x380
#घोषणा TXCHK_PKT_RDY_THRESH		0x00

/* Receive buffer offset and defines */
#घोषणा SYS_PORT_RBUF_OFFSET		0x400

#घोषणा RBUF_CONTROL			0x00
#घोषणा  RBUF_RSB_EN			(1 << 0)
#घोषणा  RBUF_4B_ALGN			(1 << 1)
#घोषणा  RBUF_BRCM_TAG_STRIP		(1 << 2)
#घोषणा  RBUF_BAD_PKT_DISC		(1 << 3)
#घोषणा  RBUF_RESUME_THRESH_SHIFT	4
#घोषणा  RBUF_RESUME_THRESH_MASK	0xff
#घोषणा  RBUF_OK_TO_SEND_SHIFT		12
#घोषणा  RBUF_OK_TO_SEND_MASK		0xff
#घोषणा  RBUF_CRC_REPLACE		(1 << 20)
#घोषणा  RBUF_OK_TO_SEND_MODE		(1 << 21)
/* SYSTEMPORT Lite uses two bits here */
#घोषणा  RBUF_RSB_SWAP0			(1 << 22)
#घोषणा  RBUF_RSB_SWAP1			(1 << 23)
#घोषणा  RBUF_ACPI_EN			(1 << 23)
#घोषणा  RBUF_ACPI_EN_LITE		(1 << 24)

#घोषणा RBUF_PKT_RDY_THRESH		0x04

#घोषणा RBUF_STATUS			0x08
#घोषणा  RBUF_WOL_MODE			(1 << 0)
#घोषणा  RBUF_MPD			(1 << 1)
#घोषणा  RBUF_ACPI			(1 << 2)

#घोषणा RBUF_OVFL_DISC_CNTR		0x0c
#घोषणा RBUF_ERR_PKT_CNTR		0x10

/* Transmit buffer offset and defines */
#घोषणा SYS_PORT_TBUF_OFFSET		0x600

#घोषणा TBUF_CONTROL			0x00
#घोषणा  TBUF_BP_EN			(1 << 0)
#घोषणा  TBUF_MAX_PKT_THRESH_SHIFT	1
#घोषणा  TBUF_MAX_PKT_THRESH_MASK	0x1f
#घोषणा  TBUF_FULL_THRESH_SHIFT		8
#घोषणा  TBUF_FULL_THRESH_MASK		0x1f

/* UniMAC offset and defines */
#घोषणा SYS_PORT_UMAC_OFFSET		0x800

#घोषणा UMAC_MIB_START			0x400

/* There is a 0xC gap between the end of RX and beginning of TX stats and then
 * between the end of TX stats and the beginning of the RX RUNT
 */
#घोषणा UMAC_MIB_STAT_OFFSET		0xc

#घोषणा UMAC_MIB_CTRL			0x580
#घोषणा  MIB_RX_CNT_RST			(1 << 0)
#घोषणा  MIB_RUNT_CNT_RST		(1 << 1)
#घोषणा  MIB_TX_CNT_RST			(1 << 2)

/* These offsets are valid क्रम SYSTEMPORT and SYSTEMPORT Lite */
#घोषणा UMAC_MPD_CTRL			0x620
#घोषणा  MPD_EN				(1 << 0)
#घोषणा  MSEQ_LEN_SHIFT			16
#घोषणा  MSEQ_LEN_MASK			0xff
#घोषणा  PSW_EN				(1 << 27)

#घोषणा UMAC_PSW_MS			0x624
#घोषणा UMAC_PSW_LS			0x628
#घोषणा UMAC_MDF_CTRL			0x650
#घोषणा UMAC_MDF_ADDR			0x654

/* Only valid on SYSTEMPORT Lite */
#घोषणा SYS_PORT_GIB_OFFSET		0x1000

#घोषणा GIB_CONTROL			0x00
#घोषणा  GIB_TX_EN			(1 << 0)
#घोषणा  GIB_RX_EN			(1 << 1)
#घोषणा  GIB_TX_FLUSH			(1 << 2)
#घोषणा  GIB_RX_FLUSH			(1 << 3)
#घोषणा  GIB_GTX_CLK_SEL_SHIFT		4
#घोषणा  GIB_GTX_CLK_EXT_CLK		(0 << GIB_GTX_CLK_SEL_SHIFT)
#घोषणा  GIB_GTX_CLK_125MHZ		(1 << GIB_GTX_CLK_SEL_SHIFT)
#घोषणा  GIB_GTX_CLK_250MHZ		(2 << GIB_GTX_CLK_SEL_SHIFT)
#घोषणा  GIB_FCS_STRIP_SHIFT		6
#घोषणा  GIB_FCS_STRIP			(1 << GIB_FCS_STRIP_SHIFT)
#घोषणा  GIB_LCL_LOOP_EN		(1 << 7)
#घोषणा  GIB_LCL_LOOP_TXEN		(1 << 8)
#घोषणा  GIB_RMT_LOOP_EN		(1 << 9)
#घोषणा  GIB_RMT_LOOP_RXEN		(1 << 10)
#घोषणा  GIB_RX_PAUSE_EN		(1 << 11)
#घोषणा  GIB_PREAMBLE_LEN_SHIFT		12
#घोषणा  GIB_PREAMBLE_LEN_MASK		0xf
#घोषणा  GIB_IPG_LEN_SHIFT		16
#घोषणा  GIB_IPG_LEN_MASK		0x3f
#घोषणा  GIB_PAD_EXTENSION_SHIFT	22
#घोषणा  GIB_PAD_EXTENSION_MASK		0x3f

#घोषणा GIB_MAC1			0x08
#घोषणा GIB_MAC0			0x0c

/* Receive DMA offset and defines */
#घोषणा SYS_PORT_RDMA_OFFSET		0x2000

#घोषणा RDMA_CONTROL			0x1000
#घोषणा  RDMA_EN			(1 << 0)
#घोषणा  RDMA_RING_CFG			(1 << 1)
#घोषणा  RDMA_DISC_EN			(1 << 2)
#घोषणा  RDMA_BUF_DATA_OFFSET_SHIFT	4
#घोषणा  RDMA_BUF_DATA_OFFSET_MASK	0x3ff

#घोषणा RDMA_STATUS			0x1004
#घोषणा  RDMA_DISABLED			(1 << 0)
#घोषणा  RDMA_DESC_RAM_INIT_BUSY	(1 << 1)
#घोषणा  RDMA_BP_STATUS			(1 << 2)

#घोषणा RDMA_SCB_BURST_SIZE		0x1008

#घोषणा RDMA_RING_BUF_SIZE		0x100c
#घोषणा  RDMA_RING_SIZE_SHIFT		16

#घोषणा RDMA_WRITE_PTR_HI		0x1010
#घोषणा RDMA_WRITE_PTR_LO		0x1014
#घोषणा RDMA_PROD_INDEX			0x1018
#घोषणा  RDMA_PROD_INDEX_MASK		0xffff

#घोषणा RDMA_CONS_INDEX			0x101c
#घोषणा  RDMA_CONS_INDEX_MASK		0xffff

#घोषणा RDMA_START_ADDR_HI		0x1020
#घोषणा RDMA_START_ADDR_LO		0x1024
#घोषणा RDMA_END_ADDR_HI		0x1028
#घोषणा RDMA_END_ADDR_LO		0x102c

#घोषणा RDMA_MBDONE_INTR		0x1030
#घोषणा  RDMA_INTR_THRESH_MASK		0x1ff
#घोषणा  RDMA_TIMEOUT_SHIFT		16
#घोषणा  RDMA_TIMEOUT_MASK		0xffff

#घोषणा RDMA_XON_XOFF_THRESH		0x1034
#घोषणा  RDMA_XON_XOFF_THRESH_MASK	0xffff
#घोषणा  RDMA_XOFF_THRESH_SHIFT		16

#घोषणा RDMA_READ_PTR_HI		0x1038
#घोषणा RDMA_READ_PTR_LO		0x103c

#घोषणा RDMA_OVERRIDE			0x1040
#घोषणा  RDMA_LE_MODE			(1 << 0)
#घोषणा  RDMA_REG_MODE			(1 << 1)

#घोषणा RDMA_TEST			0x1044
#घोषणा  RDMA_TP_OUT_SEL		(1 << 0)
#घोषणा  RDMA_MEM_SEL			(1 << 1)

#घोषणा RDMA_DEBUG			0x1048

/* Transmit DMA offset and defines */
#घोषणा TDMA_NUM_RINGS			32	/* rings = queues */
#घोषणा TDMA_PORT_SIZE			DESC_SIZE /* two 32-bits words */

#घोषणा SYS_PORT_TDMA_OFFSET		0x4000
#घोषणा TDMA_WRITE_PORT_OFFSET		0x0000
#घोषणा TDMA_WRITE_PORT_HI(i)		(TDMA_WRITE_PORT_OFFSET + \
					(i) * TDMA_PORT_SIZE)
#घोषणा TDMA_WRITE_PORT_LO(i)		(TDMA_WRITE_PORT_OFFSET + \
					माप(u32) + (i) * TDMA_PORT_SIZE)

#घोषणा TDMA_READ_PORT_OFFSET		(TDMA_WRITE_PORT_OFFSET + \
					(TDMA_NUM_RINGS * TDMA_PORT_SIZE))
#घोषणा TDMA_READ_PORT_HI(i)		(TDMA_READ_PORT_OFFSET + \
					(i) * TDMA_PORT_SIZE)
#घोषणा TDMA_READ_PORT_LO(i)		(TDMA_READ_PORT_OFFSET + \
					माप(u32) + (i) * TDMA_PORT_SIZE)

#घोषणा TDMA_READ_PORT_CMD_OFFSET	(TDMA_READ_PORT_OFFSET + \
					(TDMA_NUM_RINGS * TDMA_PORT_SIZE))
#घोषणा TDMA_READ_PORT_CMD(i)		(TDMA_READ_PORT_CMD_OFFSET + \
					(i) * माप(u32))

#घोषणा TDMA_DESC_RING_00_BASE		(TDMA_READ_PORT_CMD_OFFSET + \
					(TDMA_NUM_RINGS * माप(u32)))

/* Register offsets and defines relatives to a specअगरic ring number */
#घोषणा RING_HEAD_TAIL_PTR		0x00
#घोषणा  RING_HEAD_MASK			0x7ff
#घोषणा  RING_TAIL_SHIFT		11
#घोषणा  RING_TAIL_MASK			0x7ff
#घोषणा  RING_FLUSH			(1 << 24)
#घोषणा  RING_EN			(1 << 25)

#घोषणा RING_COUNT			0x04
#घोषणा  RING_COUNT_MASK		0x7ff
#घोषणा  RING_BUFF_DONE_SHIFT		11
#घोषणा  RING_BUFF_DONE_MASK		0x7ff

#घोषणा RING_MAX_HYST			0x08
#घोषणा  RING_MAX_THRESH_MASK		0x7ff
#घोषणा  RING_HYST_THRESH_SHIFT		11
#घोषणा  RING_HYST_THRESH_MASK		0x7ff

#घोषणा RING_INTR_CONTROL		0x0c
#घोषणा  RING_INTR_THRESH_MASK		0x7ff
#घोषणा  RING_EMPTY_INTR_EN		(1 << 15)
#घोषणा  RING_TIMEOUT_SHIFT		16
#घोषणा  RING_TIMEOUT_MASK		0xffff

#घोषणा RING_PROD_CONS_INDEX		0x10
#घोषणा  RING_PROD_INDEX_MASK		0xffff
#घोषणा  RING_CONS_INDEX_SHIFT		16
#घोषणा  RING_CONS_INDEX_MASK		0xffff

#घोषणा RING_MAPPING			0x14
#घोषणा  RING_QID_MASK			0x7
#घोषणा  RING_PORT_ID_SHIFT		3
#घोषणा  RING_PORT_ID_MASK		0x7
#घोषणा  RING_IGNORE_STATUS		(1 << 6)
#घोषणा  RING_FAILOVER_EN		(1 << 7)
#घोषणा  RING_CREDIT_SHIFT		8
#घोषणा  RING_CREDIT_MASK		0xffff

#घोषणा RING_PCP_DEI_VID		0x18
#घोषणा  RING_VID_MASK			0x7ff
#घोषणा  RING_DEI			(1 << 12)
#घोषणा  RING_PCP_SHIFT			13
#घोषणा  RING_PCP_MASK			0x7
#घोषणा  RING_PKT_SIZE_ADJ_SHIFT	16
#घोषणा  RING_PKT_SIZE_ADJ_MASK		0xf

#घोषणा TDMA_DESC_RING_SIZE		28

/* Defininition क्रम a given TX ring base address */
#घोषणा TDMA_DESC_RING_BASE(i)		(TDMA_DESC_RING_00_BASE + \
					((i) * TDMA_DESC_RING_SIZE))

/* Ring indexed रेजिस्टर addreses */
#घोषणा TDMA_DESC_RING_HEAD_TAIL_PTR(i)	(TDMA_DESC_RING_BASE(i) + \
					RING_HEAD_TAIL_PTR)
#घोषणा TDMA_DESC_RING_COUNT(i)		(TDMA_DESC_RING_BASE(i) + \
					RING_COUNT)
#घोषणा TDMA_DESC_RING_MAX_HYST(i)	(TDMA_DESC_RING_BASE(i) + \
					RING_MAX_HYST)
#घोषणा TDMA_DESC_RING_INTR_CONTROL(i)	(TDMA_DESC_RING_BASE(i) + \
					RING_INTR_CONTROL)
#घोषणा TDMA_DESC_RING_PROD_CONS_INDEX(i) \
					(TDMA_DESC_RING_BASE(i) + \
					RING_PROD_CONS_INDEX)
#घोषणा TDMA_DESC_RING_MAPPING(i)	(TDMA_DESC_RING_BASE(i) + \
					RING_MAPPING)
#घोषणा TDMA_DESC_RING_PCP_DEI_VID(i)	(TDMA_DESC_RING_BASE(i) + \
					RING_PCP_DEI_VID)

#घोषणा TDMA_CONTROL			0x600
#घोषणा  TDMA_EN			0
#घोषणा  TSB_EN				1
/* Uses 2 bits on SYSTEMPORT Lite and shअगरts everything by 1 bit, we
 * keep the SYSTEMPORT layout here and adjust with tdma_control_bit()
 */
#घोषणा  TSB_SWAP0			2
#घोषणा  TSB_SWAP1			3
#घोषणा  ACB_ALGO			3
#घोषणा  BUF_DATA_OFFSET_SHIFT		4
#घोषणा  BUF_DATA_OFFSET_MASK		0x3ff
#घोषणा  VLAN_EN			14
#घोषणा  SW_BRCM_TAG			15
#घोषणा  WNC_KPT_SIZE_UPDATE		16
#घोषणा  SYNC_PKT_SIZE			17
#घोषणा  ACH_TXDONE_DELAY_SHIFT		18
#घोषणा  ACH_TXDONE_DELAY_MASK		0xff

#घोषणा TDMA_STATUS			0x604
#घोषणा  TDMA_DISABLED			(1 << 0)
#घोषणा  TDMA_LL_RAM_INIT_BUSY		(1 << 1)

#घोषणा TDMA_SCB_BURST_SIZE		0x608
#घोषणा TDMA_OVER_MAX_THRESH_STATUS	0x60c
#घोषणा TDMA_OVER_HYST_THRESH_STATUS	0x610
#घोषणा TDMA_TPID			0x614

#घोषणा TDMA_FREE_LIST_HEAD_TAIL_PTR	0x618
#घोषणा  TDMA_FREE_HEAD_MASK		0x7ff
#घोषणा  TDMA_FREE_TAIL_SHIFT		11
#घोषणा  TDMA_FREE_TAIL_MASK		0x7ff

#घोषणा TDMA_FREE_LIST_COUNT		0x61c
#घोषणा  TDMA_FREE_LIST_COUNT_MASK	0x7ff

#घोषणा TDMA_TIER2_ARB_CTRL		0x620
#घोषणा  TDMA_ARB_MODE_RR		0
#घोषणा  TDMA_ARB_MODE_WEIGHT_RR	0x1
#घोषणा  TDMA_ARB_MODE_STRICT		0x2
#घोषणा  TDMA_ARB_MODE_DEFICIT_RR	0x3
#घोषणा  TDMA_CREDIT_SHIFT		4
#घोषणा  TDMA_CREDIT_MASK		0xffff

#घोषणा TDMA_TIER1_ARB_0_CTRL		0x624
#घोषणा  TDMA_ARB_EN			(1 << 0)

#घोषणा TDMA_TIER1_ARB_0_QUEUE_EN	0x628
#घोषणा TDMA_TIER1_ARB_1_CTRL		0x62c
#घोषणा TDMA_TIER1_ARB_1_QUEUE_EN	0x630
#घोषणा TDMA_TIER1_ARB_2_CTRL		0x634
#घोषणा TDMA_TIER1_ARB_2_QUEUE_EN	0x638
#घोषणा TDMA_TIER1_ARB_3_CTRL		0x63c
#घोषणा TDMA_TIER1_ARB_3_QUEUE_EN	0x640

#घोषणा TDMA_SCB_ENDIAN_OVERRIDE	0x644
#घोषणा  TDMA_LE_MODE			(1 << 0)
#घोषणा  TDMA_REG_MODE			(1 << 1)

#घोषणा TDMA_TEST			0x648
#घोषणा  TDMA_TP_OUT_SEL		(1 << 0)
#घोषणा  TDMA_MEM_TM			(1 << 1)

#घोषणा TDMA_DEBUG			0x64c

/* Number of Receive hardware descriptor words */
#घोषणा SP_NUM_HW_RX_DESC_WORDS		1024
#घोषणा SP_LT_NUM_HW_RX_DESC_WORDS	256

/* Internal linked-list RAM size */
#घोषणा SP_NUM_TX_DESC			1536
#घोषणा SP_LT_NUM_TX_DESC		256

#घोषणा WORDS_PER_DESC			2

/* Rx/Tx common counter group.*/
काष्ठा bcm_sysport_pkt_counters अणु
	u32	cnt_64;		/* RO Received/Transmited 64 bytes packet */
	u32	cnt_127;	/* RO Rx/Tx 127 bytes packet */
	u32	cnt_255;	/* RO Rx/Tx 65-255 bytes packet */
	u32	cnt_511;	/* RO Rx/Tx 256-511 bytes packet */
	u32	cnt_1023;	/* RO Rx/Tx 512-1023 bytes packet */
	u32	cnt_1518;	/* RO Rx/Tx 1024-1518 bytes packet */
	u32	cnt_mgv;	/* RO Rx/Tx 1519-1522 good VLAN packet */
	u32	cnt_2047;	/* RO Rx/Tx 1522-2047 bytes packet*/
	u32	cnt_4095;	/* RO Rx/Tx 2048-4095 bytes packet*/
	u32	cnt_9216;	/* RO Rx/Tx 4096-9216 bytes packet*/
पूर्ण;

/* RSV, Receive Status Vector */
काष्ठा bcm_sysport_rx_counters अणु
	काष्ठा  bcm_sysport_pkt_counters pkt_cnt;
	u32	pkt;		/* RO (0x428) Received pkt count*/
	u32	bytes;		/* RO Received byte count */
	u32	mca;		/* RO # of Received multicast pkt */
	u32	bca;		/* RO # of Receive broadcast pkt */
	u32	fcs;		/* RO # of Received FCS error  */
	u32	cf;		/* RO # of Received control frame pkt*/
	u32	pf;		/* RO # of Received छोड़ो frame pkt */
	u32	uo;		/* RO # of unknown op code pkt */
	u32	aln;		/* RO # of alignment error count */
	u32	flr;		/* RO # of frame length out of range count */
	u32	cde;		/* RO # of code error pkt */
	u32	fcr;		/* RO # of carrier sense error pkt */
	u32	ovr;		/* RO # of oversize pkt*/
	u32	jbr;		/* RO # of jabber count */
	u32	mtue;		/* RO # of MTU error pkt*/
	u32	pok;		/* RO # of Received good pkt */
	u32	uc;		/* RO # of unicast pkt */
	u32	ppp;		/* RO # of PPP pkt */
	u32	rcrc;		/* RO (0x470),# of CRC match pkt */
पूर्ण;

/* TSV, Transmit Status Vector */
काष्ठा bcm_sysport_tx_counters अणु
	काष्ठा bcm_sysport_pkt_counters pkt_cnt;
	u32	pkts;		/* RO (0x4a8) Transmited pkt */
	u32	mca;		/* RO # of xmited multicast pkt */
	u32	bca;		/* RO # of xmited broadcast pkt */
	u32	pf;		/* RO # of xmited छोड़ो frame count */
	u32	cf;		/* RO # of xmited control frame count */
	u32	fcs;		/* RO # of xmited FCS error count */
	u32	ovr;		/* RO # of xmited oversize pkt */
	u32	drf;		/* RO # of xmited deferral pkt */
	u32	edf;		/* RO # of xmited Excessive deferral pkt*/
	u32	scl;		/* RO # of xmited single collision pkt */
	u32	mcl;		/* RO # of xmited multiple collision pkt*/
	u32	lcl;		/* RO # of xmited late collision pkt */
	u32	ecl;		/* RO # of xmited excessive collision pkt*/
	u32	frg;		/* RO # of xmited fragments pkt*/
	u32	ncl;		/* RO # of xmited total collision count */
	u32	jbr;		/* RO # of xmited jabber count*/
	u32	bytes;		/* RO # of xmited byte count */
	u32	pok;		/* RO # of xmited good pkt */
	u32	uc;		/* RO (0x4f0) # of xmited unicast pkt */
पूर्ण;

काष्ठा bcm_sysport_mib अणु
	काष्ठा bcm_sysport_rx_counters rx;
	काष्ठा bcm_sysport_tx_counters tx;
	u32 rx_runt_cnt;
	u32 rx_runt_fcs;
	u32 rx_runt_fcs_align;
	u32 rx_runt_bytes;
	u32 rxchk_bad_csum;
	u32 rxchk_other_pkt_disc;
	u32 rbuf_ovflow_cnt;
	u32 rbuf_err_cnt;
	u32 alloc_rx_buff_failed;
	u32 rx_dma_failed;
	u32 tx_dma_failed;
	u32 tx_पुनः_स्मृति_tsb;
	u32 tx_पुनः_स्मृति_tsb_failed;
पूर्ण;

/* HW मुख्यtains a large list of counters */
क्रमागत bcm_sysport_stat_type अणु
	BCM_SYSPORT_STAT_NETDEV = -1,
	BCM_SYSPORT_STAT_NETDEV64,
	BCM_SYSPORT_STAT_MIB_RX,
	BCM_SYSPORT_STAT_MIB_TX,
	BCM_SYSPORT_STAT_RUNT,
	BCM_SYSPORT_STAT_RXCHK,
	BCM_SYSPORT_STAT_RBUF,
	BCM_SYSPORT_STAT_SOFT,
पूर्ण;

/* Macros to help define ethtool statistics */
#घोषणा STAT_NETDEV(m) अणु \
	.stat_string = __stringअगरy(m), \
	.stat_माप = माप(((काष्ठा net_device_stats *)0)->m), \
	.stat_offset = दुरत्व(काष्ठा net_device_stats, m), \
	.type = BCM_SYSPORT_STAT_NETDEV, \
पूर्ण

#घोषणा STAT_NETDEV64(m) अणु \
	.stat_string = __stringअगरy(m), \
	.stat_माप = माप(((काष्ठा bcm_sysport_stats64 *)0)->m), \
	.stat_offset = दुरत्व(काष्ठा bcm_sysport_stats64, m), \
	.type = BCM_SYSPORT_STAT_NETDEV64, \
पूर्ण

#घोषणा STAT_MIB(str, m, _type) अणु \
	.stat_string = str, \
	.stat_माप = माप(((काष्ठा bcm_sysport_priv *)0)->m), \
	.stat_offset = दुरत्व(काष्ठा bcm_sysport_priv, m), \
	.type = _type, \
पूर्ण

#घोषणा STAT_MIB_RX(str, m) STAT_MIB(str, m, BCM_SYSPORT_STAT_MIB_RX)
#घोषणा STAT_MIB_TX(str, m) STAT_MIB(str, m, BCM_SYSPORT_STAT_MIB_TX)
#घोषणा STAT_RUNT(str, m) STAT_MIB(str, m, BCM_SYSPORT_STAT_RUNT)
#घोषणा STAT_MIB_SOFT(str, m) STAT_MIB(str, m, BCM_SYSPORT_STAT_SOFT)

#घोषणा STAT_RXCHK(str, m, ofs) अणु \
	.stat_string = str, \
	.stat_माप = माप(((काष्ठा bcm_sysport_priv *)0)->m), \
	.stat_offset = दुरत्व(काष्ठा bcm_sysport_priv, m), \
	.type = BCM_SYSPORT_STAT_RXCHK, \
	.reg_offset = ofs, \
पूर्ण

#घोषणा STAT_RBUF(str, m, ofs) अणु \
	.stat_string = str, \
	.stat_माप = माप(((काष्ठा bcm_sysport_priv *)0)->m), \
	.stat_offset = दुरत्व(काष्ठा bcm_sysport_priv, m), \
	.type = BCM_SYSPORT_STAT_RBUF, \
	.reg_offset = ofs, \
पूर्ण

/* TX bytes and packets */
#घोषणा NUM_SYSPORT_TXQ_STAT	2

काष्ठा bcm_sysport_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक stat_माप;
	पूर्णांक stat_offset;
	क्रमागत bcm_sysport_stat_type type;
	/* reg offset from UMAC base क्रम misc counters */
	u16 reg_offset;
पूर्ण;

काष्ठा bcm_sysport_stats64 अणु
	/* 64bit stats on 32bit/64bit Machine */
	u64	rx_packets;
	u64	rx_bytes;
	u64	tx_packets;
	u64	tx_bytes;
पूर्ण;

/* Software house keeping helper काष्ठाure */
काष्ठा bcm_sysport_cb अणु
	काष्ठा sk_buff	*skb;		/* SKB क्रम RX packets */
	व्योम __iomem	*bd_addr;	/* Buffer descriptor PHYS addr */

	DEFINE_DMA_UNMAP_ADDR(dma_addr);
	DEFINE_DMA_UNMAP_LEN(dma_len);
पूर्ण;

क्रमागत bcm_sysport_type अणु
	SYSTEMPORT = 0,
	SYSTEMPORT_LITE,
पूर्ण;

काष्ठा bcm_sysport_hw_params अणु
	bool		is_lite;
	अचिन्हित पूर्णांक	num_rx_desc_words;
पूर्ण;

काष्ठा bcm_sysport_net_dim अणु
	u16			use_dim;
	u16			event_ctr;
	अचिन्हित दीर्घ		packets;
	अचिन्हित दीर्घ		bytes;
	काष्ठा dim		dim;
पूर्ण;

/* Software view of the TX ring */
काष्ठा bcm_sysport_tx_ring अणु
	spinlock_t	lock;		/* Ring lock क्रम tx reclaim/xmit */
	काष्ठा napi_काष्ठा napi;	/* NAPI per tx queue */
	अचिन्हित पूर्णांक	index;		/* Ring index */
	अचिन्हित पूर्णांक	size;		/* Ring current size */
	अचिन्हित पूर्णांक	alloc_size;	/* Ring one-समय allocated size */
	अचिन्हित पूर्णांक	desc_count;	/* Number of descriptors */
	अचिन्हित पूर्णांक	curr_desc;	/* Current descriptor */
	अचिन्हित पूर्णांक	c_index;	/* Last consumer index */
	अचिन्हित पूर्णांक	clean_index;	/* Current clean index */
	काष्ठा bcm_sysport_cb *cbs;	/* Transmit control blocks */
	काष्ठा bcm_sysport_priv *priv;	/* निजी context backpoपूर्णांकer */
	अचिन्हित दीर्घ	packets;	/* packets statistics */
	अचिन्हित दीर्घ	bytes;		/* bytes statistics */
	अचिन्हित पूर्णांक	चयन_queue;	/* चयन port queue number */
	अचिन्हित पूर्णांक	चयन_port;	/* चयन port queue number */
	bool		inspect;	/* inspect चयन port and queue */
पूर्ण;

/* Driver निजी काष्ठाure */
काष्ठा bcm_sysport_priv अणु
	व्योम __iomem		*base;
	u32			irq0_stat;
	u32			irq0_mask;
	u32			irq1_stat;
	u32			irq1_mask;
	bool			is_lite;
	अचिन्हित पूर्णांक		num_rx_desc_words;
	काष्ठा napi_काष्ठा	napi ____cacheline_aligned;
	काष्ठा net_device	*netdev;
	काष्ठा platक्रमm_device	*pdev;
	पूर्णांक			irq0;
	पूर्णांक			irq1;
	पूर्णांक			wol_irq;

	/* Transmit rings */
	काष्ठा bcm_sysport_tx_ring *tx_rings;

	/* Receive queue */
	व्योम __iomem		*rx_bds;
	काष्ठा bcm_sysport_cb	*rx_cbs;
	अचिन्हित पूर्णांक		num_rx_bds;
	अचिन्हित पूर्णांक		rx_पढ़ो_ptr;
	अचिन्हित पूर्णांक		rx_c_index;

	काष्ठा bcm_sysport_net_dim	dim;
	u32			rx_max_coalesced_frames;
	u32			rx_coalesce_usecs;

	/* PHY device */
	काष्ठा device_node	*phy_dn;
	phy_पूर्णांकerface_t		phy_पूर्णांकerface;
	पूर्णांक			old_छोड़ो;
	पूर्णांक			old_link;
	पूर्णांक			old_duplex;

	/* Misc fields */
	अचिन्हित पूर्णांक		rx_chk_en:1;
	अचिन्हित पूर्णांक		tsb_en:1;
	अचिन्हित पूर्णांक		crc_fwd:1;
	u16			rev;
	u32			wolopts;
	u8			sopass[SOPASS_MAX];
	अचिन्हित पूर्णांक		wol_irq_disabled:1;
	काष्ठा clk		*clk;
	काष्ठा clk		*wol_clk;

	/* MIB related fields */
	काष्ठा bcm_sysport_mib	mib;

	/* Ethtool */
	u32			msg_enable;
	DECLARE_BITMAP(filters, RXCHK_BRCM_TAG_MAX);
	u32			filters_loc[RXCHK_BRCM_TAG_MAX];

	काष्ठा bcm_sysport_stats64	stats64;

	/* For atomic update generic 64bit value on 32bit Machine */
	काष्ठा u64_stats_sync	syncp;

	/* map inक्रमmation between चयन port queues and local queues */
	काष्ठा notअगरier_block	netdev_notअगरier;
	अचिन्हित पूर्णांक		per_port_num_tx_queues;
	काष्ठा bcm_sysport_tx_ring *ring_map[DSA_MAX_PORTS * 8];

पूर्ण;
#पूर्ण_अगर /* __BCM_SYSPORT_H */
