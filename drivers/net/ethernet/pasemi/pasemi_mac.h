<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2006 PA Semi, Inc
 *
 * Driver क्रम the PA6T-1682M onchip 1G/10G Ethernet MACs, soft state and
 * hardware रेजिस्टर layouts.
 */

#अगर_अघोषित PASEMI_MAC_H
#घोषणा PASEMI_MAC_H

#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/phy.h>

/* Must be a घातer of two */
#घोषणा RX_RING_SIZE 2048
#घोषणा TX_RING_SIZE 4096
#घोषणा CS_RING_SIZE (TX_RING_SIZE*2)


#घोषणा MAX_CS	2

काष्ठा pasemi_mac_txring अणु
	काष्ठा pasemi_dmachan chan; /* Must be first */
	spinlock_t	 lock;
	अचिन्हित पूर्णांक	 size;
	अचिन्हित पूर्णांक	 next_to_fill;
	अचिन्हित पूर्णांक	 next_to_clean;
	काष्ठा pasemi_mac_buffer *ring_info;
	काष्ठा pasemi_mac *mac;	/* Needed in पूर्णांकr handler */
	काष्ठा समयr_list clean_समयr;
पूर्ण;

काष्ठा pasemi_mac_rxring अणु
	काष्ठा pasemi_dmachan chan; /* Must be first */
	spinlock_t	 lock;
	u64		*buffers;	/* RX पूर्णांकerface buffer ring */
	dma_addr_t	 buf_dma;
	अचिन्हित पूर्णांक	 size;
	अचिन्हित पूर्णांक	 next_to_fill;
	अचिन्हित पूर्णांक	 next_to_clean;
	काष्ठा pasemi_mac_buffer *ring_info;
	काष्ठा pasemi_mac *mac;	/* Needed in पूर्णांकr handler */
पूर्ण;

काष्ठा pasemi_mac_csring अणु
	काष्ठा pasemi_dmachan chan;
	अचिन्हित पूर्णांक	size;
	अचिन्हित पूर्णांक	next_to_fill;
	पूर्णांक		events[2];
	पूर्णांक		last_event;
	पूर्णांक		fun;
पूर्ण;

काष्ठा pasemi_mac अणु
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;
	काष्ठा pci_dev *dma_pdev;
	काष्ठा pci_dev *iob_pdev;
	काष्ठा napi_काष्ठा napi;

	पूर्णांक		bufsz; /* RX ring buffer size */
	पूर्णांक		last_cs;
	पूर्णांक		num_cs;
	u32		dma_अगर;
	u8		type;
#घोषणा MAC_TYPE_GMAC	1
#घोषणा MAC_TYPE_XAUI	2

	u8		mac_addr[ETH_ALEN];

	काष्ठा समयr_list	rxसमयr;

	काष्ठा pasemi_mac_txring *tx;
	काष्ठा pasemi_mac_rxring *rx;
	काष्ठा pasemi_mac_csring *cs[MAX_CS];
	अक्षर		tx_irq_name[10];		/* "eth%d tx" */
	अक्षर		rx_irq_name[10];		/* "eth%d rx" */
	पूर्णांक	link;
	पूर्णांक	speed;
	पूर्णांक	duplex;

	अचिन्हित पूर्णांक	msg_enable;
पूर्ण;

/* Software status descriptor (ring_info) */
काष्ठा pasemi_mac_buffer अणु
	काष्ठा sk_buff *skb;
	dma_addr_t	dma;
पूर्ण;

#घोषणा TX_DESC(tx, num)	((tx)->chan.ring_virt[(num) & (TX_RING_SIZE-1)])
#घोषणा TX_DESC_INFO(tx, num)	((tx)->ring_info[(num) & (TX_RING_SIZE-1)])
#घोषणा RX_DESC(rx, num)	((rx)->chan.ring_virt[(num) & (RX_RING_SIZE-1)])
#घोषणा RX_DESC_INFO(rx, num)	((rx)->ring_info[(num) & (RX_RING_SIZE-1)])
#घोषणा RX_BUFF(rx, num)	((rx)->buffers[(num) & (RX_RING_SIZE-1)])
#घोषणा CS_DESC(cs, num)	((cs)->chan.ring_virt[(num) & (CS_RING_SIZE-1)])

#घोषणा RING_USED(ring)	(((ring)->next_to_fill - (ring)->next_to_clean) \
				& ((ring)->size - 1))
#घोषणा RING_AVAIL(ring)	((ring->size) - RING_USED(ring))

/* PCI रेजिस्टर offsets and क्रमmats */


/* MAC CFG रेजिस्टर offsets */
क्रमागत अणु
	PAS_MAC_CFG_PCFG = 0x80,
	PAS_MAC_CFG_MACCFG = 0x84,
	PAS_MAC_CFG_ADR0 = 0x8c,
	PAS_MAC_CFG_ADR1 = 0x90,
	PAS_MAC_CFG_TXP = 0x98,
	PAS_MAC_CFG_RMON = 0x100,
	PAS_MAC_IPC_CHNL = 0x208,
पूर्ण;

/* MAC CFG रेजिस्टर fields */
#घोषणा PAS_MAC_CFG_PCFG_PE		0x80000000
#घोषणा PAS_MAC_CFG_PCFG_CE		0x40000000
#घोषणा PAS_MAC_CFG_PCFG_BU		0x20000000
#घोषणा PAS_MAC_CFG_PCFG_TT		0x10000000
#घोषणा PAS_MAC_CFG_PCFG_TSR_M		0x0c000000
#घोषणा PAS_MAC_CFG_PCFG_TSR_10M	0x00000000
#घोषणा PAS_MAC_CFG_PCFG_TSR_100M	0x04000000
#घोषणा PAS_MAC_CFG_PCFG_TSR_1G		0x08000000
#घोषणा PAS_MAC_CFG_PCFG_TSR_10G	0x0c000000
#घोषणा PAS_MAC_CFG_PCFG_T24		0x02000000
#घोषणा PAS_MAC_CFG_PCFG_PR		0x01000000
#घोषणा PAS_MAC_CFG_PCFG_CRO_M		0x00ff0000
#घोषणा PAS_MAC_CFG_PCFG_CRO_S	16
#घोषणा PAS_MAC_CFG_PCFG_IPO_M		0x0000ff00
#घोषणा PAS_MAC_CFG_PCFG_IPO_S	8
#घोषणा PAS_MAC_CFG_PCFG_S1		0x00000080
#घोषणा PAS_MAC_CFG_PCFG_IO_M		0x00000060
#घोषणा PAS_MAC_CFG_PCFG_IO_MAC		0x00000000
#घोषणा PAS_MAC_CFG_PCFG_IO_OFF		0x00000020
#घोषणा PAS_MAC_CFG_PCFG_IO_IND_ETH	0x00000040
#घोषणा PAS_MAC_CFG_PCFG_IO_IND_IP	0x00000060
#घोषणा PAS_MAC_CFG_PCFG_LP		0x00000010
#घोषणा PAS_MAC_CFG_PCFG_TS		0x00000008
#घोषणा PAS_MAC_CFG_PCFG_HD		0x00000004
#घोषणा PAS_MAC_CFG_PCFG_SPD_M		0x00000003
#घोषणा PAS_MAC_CFG_PCFG_SPD_10M	0x00000000
#घोषणा PAS_MAC_CFG_PCFG_SPD_100M	0x00000001
#घोषणा PAS_MAC_CFG_PCFG_SPD_1G		0x00000002
#घोषणा PAS_MAC_CFG_PCFG_SPD_10G	0x00000003

#घोषणा PAS_MAC_CFG_MACCFG_TXT_M	0x70000000
#घोषणा PAS_MAC_CFG_MACCFG_TXT_S	28
#घोषणा PAS_MAC_CFG_MACCFG_PRES_M	0x0f000000
#घोषणा PAS_MAC_CFG_MACCFG_PRES_S	24
#घोषणा PAS_MAC_CFG_MACCFG_MAXF_M	0x00ffff00
#घोषणा PAS_MAC_CFG_MACCFG_MAXF_S	8
#घोषणा PAS_MAC_CFG_MACCFG_MAXF(x)	(((x) << PAS_MAC_CFG_MACCFG_MAXF_S) & \
					 PAS_MAC_CFG_MACCFG_MAXF_M)
#घोषणा PAS_MAC_CFG_MACCFG_MINF_M	0x000000ff
#घोषणा PAS_MAC_CFG_MACCFG_MINF_S	0

#घोषणा PAS_MAC_CFG_TXP_FCF		0x01000000
#घोषणा PAS_MAC_CFG_TXP_FCE		0x00800000
#घोषणा PAS_MAC_CFG_TXP_FC		0x00400000
#घोषणा PAS_MAC_CFG_TXP_FPC_M		0x00300000
#घोषणा PAS_MAC_CFG_TXP_FPC_S		20
#घोषणा PAS_MAC_CFG_TXP_FPC(x)		(((x) << PAS_MAC_CFG_TXP_FPC_S) & \
					 PAS_MAC_CFG_TXP_FPC_M)
#घोषणा PAS_MAC_CFG_TXP_RT		0x00080000
#घोषणा PAS_MAC_CFG_TXP_BL		0x00040000
#घोषणा PAS_MAC_CFG_TXP_SL_M		0x00030000
#घोषणा PAS_MAC_CFG_TXP_SL_S		16
#घोषणा PAS_MAC_CFG_TXP_SL(x)		(((x) << PAS_MAC_CFG_TXP_SL_S) & \
					 PAS_MAC_CFG_TXP_SL_M)
#घोषणा PAS_MAC_CFG_TXP_COB_M		0x0000f000
#घोषणा PAS_MAC_CFG_TXP_COB_S		12
#घोषणा PAS_MAC_CFG_TXP_COB(x)		(((x) << PAS_MAC_CFG_TXP_COB_S) & \
					 PAS_MAC_CFG_TXP_COB_M)
#घोषणा PAS_MAC_CFG_TXP_TIFT_M		0x00000f00
#घोषणा PAS_MAC_CFG_TXP_TIFT_S		8
#घोषणा PAS_MAC_CFG_TXP_TIFT(x)		(((x) << PAS_MAC_CFG_TXP_TIFT_S) & \
					 PAS_MAC_CFG_TXP_TIFT_M)
#घोषणा PAS_MAC_CFG_TXP_TIFG_M		0x000000ff
#घोषणा PAS_MAC_CFG_TXP_TIFG_S		0
#घोषणा PAS_MAC_CFG_TXP_TIFG(x)		(((x) << PAS_MAC_CFG_TXP_TIFG_S) & \
					 PAS_MAC_CFG_TXP_TIFG_M)

#घोषणा PAS_MAC_RMON(r)			(0x100+(r)*4)

#घोषणा PAS_MAC_IPC_CHNL_DCHNO_M	0x003f0000
#घोषणा PAS_MAC_IPC_CHNL_DCHNO_S	16
#घोषणा PAS_MAC_IPC_CHNL_DCHNO(x)	(((x) << PAS_MAC_IPC_CHNL_DCHNO_S) & \
					 PAS_MAC_IPC_CHNL_DCHNO_M)
#घोषणा PAS_MAC_IPC_CHNL_BCH_M		0x0000003f
#घोषणा PAS_MAC_IPC_CHNL_BCH_S		0
#घोषणा PAS_MAC_IPC_CHNL_BCH(x)		(((x) << PAS_MAC_IPC_CHNL_BCH_S) & \
					 PAS_MAC_IPC_CHNL_BCH_M)


#पूर्ण_अगर /* PASEMI_MAC_H */
