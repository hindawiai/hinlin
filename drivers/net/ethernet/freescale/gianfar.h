<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/मुक्तscale/gianfar.h
 *
 * Gianfar Ethernet Driver
 * Driver क्रम FEC on MPC8540 and TSEC on MPC8540/MPC8560
 * Based on 8260_io/fcc_enet.c
 *
 * Author: Andy Fleming
 * Maपूर्णांकainer: Kumar Gala
 * Modअगरier: Sandeep Gopalpet <sandeep.kumar@मुक्तscale.com>
 *
 * Copyright 2002-2009, 2011-2013 Freescale Semiconductor, Inc.
 *
 *  Still left to करो:
 *      -Add support क्रम module parameters
 *	-Add patch क्रम ethtool phys id
 */
#अगर_अघोषित __GIANFAR_H
#घोषणा __GIANFAR_H

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/crc32.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/ethtool.h>

काष्ठा ethtool_flow_spec_container अणु
	काष्ठा ethtool_rx_flow_spec fs;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ethtool_rx_list अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक count;
पूर्ण;

/* The maximum number of packets to be handled in one call of gfar_poll */
#घोषणा GFAR_DEV_WEIGHT 64

/* Length क्रम FCB */
#घोषणा GMAC_FCB_LEN 8

/* Length क्रम TxPAL */
#घोषणा GMAC_TXPAL_LEN 16

/* Default padding amount */
#घोषणा DEFAULT_PADDING 2

/* Number of bytes to align the rx bufs to */
#घोषणा RXBUF_ALIGNMENT 64

#घोषणा DRV_NAME "gfar-enet"

/* MAXIMUM NUMBER OF QUEUES SUPPORTED */
#घोषणा MAX_TX_QS	0x8
#घोषणा MAX_RX_QS	0x8

/* MAXIMUM NUMBER OF GROUPS SUPPORTED */
#घोषणा MAXGROUPS 0x2

/* These need to be घातers of 2 क्रम this driver */
#घोषणा DEFAULT_TX_RING_SIZE	256
#घोषणा DEFAULT_RX_RING_SIZE	256

#घोषणा GFAR_RX_BUFF_ALLOC	16

#घोषणा GFAR_RX_MAX_RING_SIZE   256
#घोषणा GFAR_TX_MAX_RING_SIZE   256

#घोषणा FBTHR_SHIFT        24
#घोषणा DEFAULT_RX_LFC_THR  16
#घोषणा DEFAULT_LFC_PTVVAL  4

#घोषणा GFAR_RXB_TRUESIZE 2048
#घोषणा GFAR_SKBFRAG_OVR (RXBUF_ALIGNMENT \
			  + SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))
#घोषणा GFAR_RXB_SIZE roundकरोwn(GFAR_RXB_TRUESIZE - GFAR_SKBFRAG_OVR, 64)
#घोषणा GFAR_SKBFRAG_SIZE (GFAR_RXB_SIZE + GFAR_SKBFRAG_OVR)

#घोषणा TX_RING_MOD_MASK(size) (size-1)
#घोषणा RX_RING_MOD_MASK(size) (size-1)
#घोषणा GFAR_JUMBO_FRAME_SIZE 9600

#घोषणा DEFAULT_FIFO_TX_THR 0x100
#घोषणा DEFAULT_FIFO_TX_STARVE 0x40
#घोषणा DEFAULT_FIFO_TX_STARVE_OFF 0x80

/* The number of Exact Match रेजिस्टरs */
#घोषणा GFAR_EM_NUM	15

/* Latency of पूर्णांकerface घड़ी in nanoseconds */
/* Interface घड़ी latency , in this हाल, means the
 * समय described by a value of 1 in the पूर्णांकerrupt
 * coalescing रेजिस्टरs' समय fields.  Since those fields
 * refer to the समय it takes क्रम 64 घड़ीs to pass, the
 * latencies are as such:
 * GBIT = 125MHz => 8ns/घड़ी => 8*64 ns / tick
 * 100 = 25 MHz => 40ns/घड़ी => 40*64 ns / tick
 * 10 = 2.5 MHz => 400ns/घड़ी => 400*64 ns / tick
 */
#घोषणा GFAR_GBIT_TIME  512
#घोषणा GFAR_100_TIME   2560
#घोषणा GFAR_10_TIME    25600

#घोषणा DEFAULT_TX_COALESCE 1
#घोषणा DEFAULT_TXCOUNT	16
#घोषणा DEFAULT_TXTIME	21

#घोषणा DEFAULT_RXTIME	21

#घोषणा DEFAULT_RX_COALESCE 0
#घोषणा DEFAULT_RXCOUNT	0

/* TBI रेजिस्टर addresses */
#घोषणा MII_TBICON		0x11

/* TBICON रेजिस्टर bit fields */
#घोषणा TBICON_CLK_SELECT	0x0020

/* MAC रेजिस्टर bits */
#घोषणा MACCFG1_SOFT_RESET	0x80000000
#घोषणा MACCFG1_RESET_RX_MC	0x00080000
#घोषणा MACCFG1_RESET_TX_MC	0x00040000
#घोषणा MACCFG1_RESET_RX_FUN	0x00020000
#घोषणा	MACCFG1_RESET_TX_FUN	0x00010000
#घोषणा MACCFG1_LOOPBACK	0x00000100
#घोषणा MACCFG1_RX_FLOW		0x00000020
#घोषणा MACCFG1_TX_FLOW		0x00000010
#घोषणा MACCFG1_SYNCD_RX_EN	0x00000008
#घोषणा MACCFG1_RX_EN		0x00000004
#घोषणा MACCFG1_SYNCD_TX_EN	0x00000002
#घोषणा MACCFG1_TX_EN		0x00000001

#घोषणा MACCFG2_INIT_SETTINGS	0x00007205
#घोषणा MACCFG2_FULL_DUPLEX	0x00000001
#घोषणा MACCFG2_IF              0x00000300
#घोषणा MACCFG2_MII             0x00000100
#घोषणा MACCFG2_GMII            0x00000200
#घोषणा MACCFG2_HUGEFRAME	0x00000020
#घोषणा MACCFG2_LENGTHCHECK	0x00000010
#घोषणा MACCFG2_MPEN		0x00000008

#घोषणा ECNTRL_FIFM		0x00008000
#घोषणा ECNTRL_INIT_SETTINGS	0x00001000
#घोषणा ECNTRL_TBI_MODE         0x00000020
#घोषणा ECNTRL_REDUCED_MODE	0x00000010
#घोषणा ECNTRL_R100		0x00000008
#घोषणा ECNTRL_REDUCED_MII_MODE	0x00000004
#घोषणा ECNTRL_SGMII_MODE	0x00000002

#घोषणा MINFLR_INIT_SETTINGS	0x00000040

/* Tqueue control */
#घोषणा TQUEUE_EN0		0x00008000
#घोषणा TQUEUE_EN1		0x00004000
#घोषणा TQUEUE_EN2		0x00002000
#घोषणा TQUEUE_EN3		0x00001000
#घोषणा TQUEUE_EN4		0x00000800
#घोषणा TQUEUE_EN5		0x00000400
#घोषणा TQUEUE_EN6		0x00000200
#घोषणा TQUEUE_EN7		0x00000100
#घोषणा TQUEUE_EN_ALL		0x0000FF00

#घोषणा TR03WT_WT0_MASK		0xFF000000
#घोषणा TR03WT_WT1_MASK		0x00FF0000
#घोषणा TR03WT_WT2_MASK		0x0000FF00
#घोषणा TR03WT_WT3_MASK		0x000000FF

#घोषणा TR47WT_WT4_MASK		0xFF000000
#घोषणा TR47WT_WT5_MASK		0x00FF0000
#घोषणा TR47WT_WT6_MASK		0x0000FF00
#घोषणा TR47WT_WT7_MASK		0x000000FF

/* Rqueue control */
#घोषणा RQUEUE_EX0		0x00800000
#घोषणा RQUEUE_EX1		0x00400000
#घोषणा RQUEUE_EX2		0x00200000
#घोषणा RQUEUE_EX3		0x00100000
#घोषणा RQUEUE_EX4		0x00080000
#घोषणा RQUEUE_EX5		0x00040000
#घोषणा RQUEUE_EX6		0x00020000
#घोषणा RQUEUE_EX7		0x00010000
#घोषणा RQUEUE_EX_ALL		0x00FF0000

#घोषणा RQUEUE_EN0		0x00000080
#घोषणा RQUEUE_EN1		0x00000040
#घोषणा RQUEUE_EN2		0x00000020
#घोषणा RQUEUE_EN3		0x00000010
#घोषणा RQUEUE_EN4		0x00000008
#घोषणा RQUEUE_EN5		0x00000004
#घोषणा RQUEUE_EN6		0x00000002
#घोषणा RQUEUE_EN7		0x00000001
#घोषणा RQUEUE_EN_ALL		0x000000FF

/* Init to करो tx snooping क्रम buffers and descriptors */
#घोषणा DMACTRL_INIT_SETTINGS   0x000000c3
#घोषणा DMACTRL_GRS             0x00000010
#घोषणा DMACTRL_GTS             0x00000008

#घोषणा TSTAT_CLEAR_THALT_ALL	0xFF000000
#घोषणा TSTAT_CLEAR_THALT	0x80000000
#घोषणा TSTAT_CLEAR_THALT0	0x80000000
#घोषणा TSTAT_CLEAR_THALT1	0x40000000
#घोषणा TSTAT_CLEAR_THALT2	0x20000000
#घोषणा TSTAT_CLEAR_THALT3	0x10000000
#घोषणा TSTAT_CLEAR_THALT4	0x08000000
#घोषणा TSTAT_CLEAR_THALT5	0x04000000
#घोषणा TSTAT_CLEAR_THALT6	0x02000000
#घोषणा TSTAT_CLEAR_THALT7	0x01000000

/* Interrupt coalescing macros */
#घोषणा IC_ICEN			0x80000000
#घोषणा IC_ICFT_MASK		0x1fe00000
#घोषणा IC_ICFT_SHIFT		21
#घोषणा mk_ic_icft(x)		\
	(((अचिन्हित पूर्णांक)x << IC_ICFT_SHIFT)&IC_ICFT_MASK)
#घोषणा IC_ICTT_MASK		0x0000ffff
#घोषणा mk_ic_ictt(x)		(x&IC_ICTT_MASK)

#घोषणा mk_ic_value(count, समय) (IC_ICEN | \
				mk_ic_icft(count) | \
				mk_ic_ictt(समय))
#घोषणा get_icft_value(ic)	(((अचिन्हित दीर्घ)ic & IC_ICFT_MASK) >> \
				 IC_ICFT_SHIFT)
#घोषणा get_ictt_value(ic)	((अचिन्हित दीर्घ)ic & IC_ICTT_MASK)

#घोषणा DEFAULT_TXIC mk_ic_value(DEFAULT_TXCOUNT, DEFAULT_TXTIME)
#घोषणा DEFAULT_RXIC mk_ic_value(DEFAULT_RXCOUNT, DEFAULT_RXTIME)

#घोषणा RCTRL_TS_ENABLE 	0x01000000
#घोषणा RCTRL_PAL_MASK		0x001f0000
#घोषणा RCTRL_LFC		0x00004000
#घोषणा RCTRL_VLEX		0x00002000
#घोषणा RCTRL_FILREN		0x00001000
#घोषणा RCTRL_GHTX		0x00000400
#घोषणा RCTRL_IPCSEN		0x00000200
#घोषणा RCTRL_TUCSEN		0x00000100
#घोषणा RCTRL_PRSDEP_MASK	0x000000c0
#घोषणा RCTRL_PRSDEP_INIT	0x000000c0
#घोषणा RCTRL_PRSFM		0x00000020
#घोषणा RCTRL_PROM		0x00000008
#घोषणा RCTRL_EMEN		0x00000002
#घोषणा RCTRL_REQ_PARSER	(RCTRL_VLEX | RCTRL_IPCSEN | \
				 RCTRL_TUCSEN | RCTRL_FILREN)
#घोषणा RCTRL_CHECKSUMMING	(RCTRL_IPCSEN | RCTRL_TUCSEN | \
				RCTRL_PRSDEP_INIT)
#घोषणा RCTRL_EXTHASH		(RCTRL_GHTX)
#घोषणा RCTRL_VLAN		(RCTRL_PRSDEP_INIT)
#घोषणा RCTRL_PADDING(x)	((x << 16) & RCTRL_PAL_MASK)


#घोषणा RSTAT_CLEAR_RHALT	0x00800000
#घोषणा RSTAT_CLEAR_RXF0	0x00000080
#घोषणा RSTAT_RXF_MASK		0x000000ff

#घोषणा TCTRL_IPCSEN		0x00004000
#घोषणा TCTRL_TUCSEN		0x00002000
#घोषणा TCTRL_VLINS		0x00001000
#घोषणा TCTRL_THDF		0x00000800
#घोषणा TCTRL_RFCPAUSE		0x00000010
#घोषणा TCTRL_TFCPAUSE		0x00000008
#घोषणा TCTRL_TXSCHED_MASK	0x00000006
#घोषणा TCTRL_TXSCHED_INIT	0x00000000
/* priority scheduling */
#घोषणा TCTRL_TXSCHED_PRIO	0x00000002
/* weighted round-robin scheduling (WRRS) */
#घोषणा TCTRL_TXSCHED_WRRS	0x00000004
/* शेष WRRS weight and policy setting,
 * tailored to the tr03wt and tr47wt रेजिस्टरs:
 * equal weight क्रम all Tx Qs, measured in 64byte units
 */
#घोषणा DEFAULT_WRRS_WEIGHT	0x18181818

#घोषणा TCTRL_INIT_CSUM		(TCTRL_TUCSEN | TCTRL_IPCSEN)

#घोषणा IEVENT_INIT_CLEAR	0xffffffff
#घोषणा IEVENT_BABR		0x80000000
#घोषणा IEVENT_RXC		0x40000000
#घोषणा IEVENT_BSY		0x20000000
#घोषणा IEVENT_EBERR		0x10000000
#घोषणा IEVENT_MSRO		0x04000000
#घोषणा IEVENT_GTSC		0x02000000
#घोषणा IEVENT_BABT		0x01000000
#घोषणा IEVENT_TXC		0x00800000
#घोषणा IEVENT_TXE		0x00400000
#घोषणा IEVENT_TXB		0x00200000
#घोषणा IEVENT_TXF		0x00100000
#घोषणा IEVENT_LC		0x00040000
#घोषणा IEVENT_CRL		0x00020000
#घोषणा IEVENT_XFUN		0x00010000
#घोषणा IEVENT_RXB0		0x00008000
#घोषणा IEVENT_MAG		0x00000800
#घोषणा IEVENT_GRSC		0x00000100
#घोषणा IEVENT_RXF0		0x00000080
#घोषणा IEVENT_FGPI		0x00000010
#घोषणा IEVENT_FIR		0x00000008
#घोषणा IEVENT_FIQ		0x00000004
#घोषणा IEVENT_DPE		0x00000002
#घोषणा IEVENT_PERR		0x00000001
#घोषणा IEVENT_RX_MASK          (IEVENT_RXB0 | IEVENT_RXF0 | IEVENT_BSY)
#घोषणा IEVENT_TX_MASK          (IEVENT_TXB | IEVENT_TXF)
#घोषणा IEVENT_RTX_MASK         (IEVENT_RX_MASK | IEVENT_TX_MASK)
#घोषणा IEVENT_ERR_MASK         \
(IEVENT_RXC | IEVENT_BSY | IEVENT_EBERR | IEVENT_MSRO | \
 IEVENT_BABT | IEVENT_TXC | IEVENT_TXE | IEVENT_LC \
 | IEVENT_CRL | IEVENT_XFUN | IEVENT_DPE | IEVENT_PERR \
 | IEVENT_MAG | IEVENT_BABR)

#घोषणा IMASK_INIT_CLEAR	0x00000000
#घोषणा IMASK_BABR              0x80000000
#घोषणा IMASK_RXC               0x40000000
#घोषणा IMASK_BSY               0x20000000
#घोषणा IMASK_EBERR             0x10000000
#घोषणा IMASK_MSRO		0x04000000
#घोषणा IMASK_GTSC              0x02000000
#घोषणा IMASK_BABT		0x01000000
#घोषणा IMASK_TXC               0x00800000
#घोषणा IMASK_TXEEN		0x00400000
#घोषणा IMASK_TXBEN		0x00200000
#घोषणा IMASK_TXFEN             0x00100000
#घोषणा IMASK_LC		0x00040000
#घोषणा IMASK_CRL		0x00020000
#घोषणा IMASK_XFUN		0x00010000
#घोषणा IMASK_RXB0              0x00008000
#घोषणा IMASK_MAG		0x00000800
#घोषणा IMASK_GRSC              0x00000100
#घोषणा IMASK_RXFEN0		0x00000080
#घोषणा IMASK_FGPI		0x00000010
#घोषणा IMASK_FIR		0x00000008
#घोषणा IMASK_FIQ		0x00000004
#घोषणा IMASK_DPE		0x00000002
#घोषणा IMASK_PERR		0x00000001
#घोषणा IMASK_DEFAULT  (IMASK_TXEEN | IMASK_TXFEN | IMASK_TXBEN | \
		IMASK_RXFEN0 | IMASK_BSY | IMASK_EBERR | IMASK_BABR | \
		IMASK_XFUN | IMASK_RXC | IMASK_BABT | IMASK_DPE \
		| IMASK_PERR)
#घोषणा IMASK_RX_DEFAULT (IMASK_RXFEN0 | IMASK_BSY)
#घोषणा IMASK_TX_DEFAULT (IMASK_TXFEN | IMASK_TXBEN)

#घोषणा IMASK_RX_DISABLED ((~(IMASK_RX_DEFAULT)) & IMASK_DEFAULT)
#घोषणा IMASK_TX_DISABLED ((~(IMASK_TX_DEFAULT)) & IMASK_DEFAULT)

/* Attribute fields */

/* This enables rx snooping क्रम buffers and descriptors */
#घोषणा ATTR_BDSTASH		0x00000800

#घोषणा ATTR_BUFSTASH		0x00004000

#घोषणा ATTR_SNOOPING		0x000000c0
#घोषणा ATTR_INIT_SETTINGS      ATTR_SNOOPING

#घोषणा ATTRELI_INIT_SETTINGS   0x0
#घोषणा ATTRELI_EL_MASK		0x3fff0000
#घोषणा ATTRELI_EL(x) (x << 16)
#घोषणा ATTRELI_EI_MASK		0x00003fff
#घोषणा ATTRELI_EI(x) (x)

#घोषणा BD_LFLAG(flags) ((flags) << 16)
#घोषणा BD_LENGTH_MASK		0x0000ffff

#घोषणा FPR_खाताR_MASK	0xFFFFFFFF
#घोषणा MAX_खाताR_IDX	0xFF

/* This शेष RIR value directly corresponds
 * to the 3-bit hash value generated */
#घोषणा DEFAULT_8RXQ_RIR0	0x05397700
/* Map even hash values to Q0, and odd ones to Q1 */
#घोषणा DEFAULT_2RXQ_RIR0	0x04104100

/* RQFCR रेजिस्टर bits */
#घोषणा RQFCR_GPI		0x80000000
#घोषणा RQFCR_HASHTBL_Q		0x00000000
#घोषणा RQFCR_HASHTBL_0		0x00020000
#घोषणा RQFCR_HASHTBL_1		0x00040000
#घोषणा RQFCR_HASHTBL_2		0x00060000
#घोषणा RQFCR_HASHTBL_3		0x00080000
#घोषणा RQFCR_HASH		0x00010000
#घोषणा RQFCR_QUEUE		0x0000FC00
#घोषणा RQFCR_CLE		0x00000200
#घोषणा RQFCR_RJE		0x00000100
#घोषणा RQFCR_AND		0x00000080
#घोषणा RQFCR_CMP_EXACT		0x00000000
#घोषणा RQFCR_CMP_MATCH		0x00000020
#घोषणा RQFCR_CMP_NOEXACT	0x00000040
#घोषणा RQFCR_CMP_NOMATCH	0x00000060

/* RQFCR PID values */
#घोषणा	RQFCR_PID_MASK		0x00000000
#घोषणा	RQFCR_PID_PARSE		0x00000001
#घोषणा	RQFCR_PID_ARB		0x00000002
#घोषणा	RQFCR_PID_DAH		0x00000003
#घोषणा	RQFCR_PID_DAL		0x00000004
#घोषणा	RQFCR_PID_SAH		0x00000005
#घोषणा	RQFCR_PID_SAL		0x00000006
#घोषणा	RQFCR_PID_ETY		0x00000007
#घोषणा	RQFCR_PID_VID		0x00000008
#घोषणा	RQFCR_PID_PRI		0x00000009
#घोषणा	RQFCR_PID_TOS		0x0000000A
#घोषणा	RQFCR_PID_L4P		0x0000000B
#घोषणा	RQFCR_PID_DIA		0x0000000C
#घोषणा	RQFCR_PID_SIA		0x0000000D
#घोषणा	RQFCR_PID_DPT		0x0000000E
#घोषणा	RQFCR_PID_SPT		0x0000000F

/* RQFPR when PID is 0x0001 */
#घोषणा RQFPR_HDR_GE_512	0x00200000
#घोषणा RQFPR_LERR		0x00100000
#घोषणा RQFPR_RAR		0x00080000
#घोषणा RQFPR_RARQ		0x00040000
#घोषणा RQFPR_AR		0x00020000
#घोषणा RQFPR_ARQ		0x00010000
#घोषणा RQFPR_EBC		0x00008000
#घोषणा RQFPR_VLN		0x00004000
#घोषणा RQFPR_CFI		0x00002000
#घोषणा RQFPR_JUM		0x00001000
#घोषणा RQFPR_IPF		0x00000800
#घोषणा RQFPR_FIF		0x00000400
#घोषणा RQFPR_IPV4		0x00000200
#घोषणा RQFPR_IPV6		0x00000100
#घोषणा RQFPR_ICC		0x00000080
#घोषणा RQFPR_ICV		0x00000040
#घोषणा RQFPR_TCP		0x00000020
#घोषणा RQFPR_UDP		0x00000010
#घोषणा RQFPR_TUC		0x00000008
#घोषणा RQFPR_TUV		0x00000004
#घोषणा RQFPR_PER		0x00000002
#घोषणा RQFPR_EER		0x00000001

/* TxBD status field bits */
#घोषणा TXBD_READY		0x8000
#घोषणा TXBD_PADCRC		0x4000
#घोषणा TXBD_WRAP		0x2000
#घोषणा TXBD_INTERRUPT		0x1000
#घोषणा TXBD_LAST		0x0800
#घोषणा TXBD_CRC		0x0400
#घोषणा TXBD_DEF		0x0200
#घोषणा TXBD_HUGEFRAME		0x0080
#घोषणा TXBD_LATECOLLISION	0x0080
#घोषणा TXBD_RETRYLIMIT		0x0040
#घोषणा	TXBD_RETRYCOUNTMASK	0x003c
#घोषणा TXBD_UNDERRUN		0x0002
#घोषणा TXBD_TOE		0x0002

/* Tx FCB param bits */
#घोषणा TXFCB_VLN		0x80
#घोषणा TXFCB_IP		0x40
#घोषणा TXFCB_IP6		0x20
#घोषणा TXFCB_TUP		0x10
#घोषणा TXFCB_UDP		0x08
#घोषणा TXFCB_CIP		0x04
#घोषणा TXFCB_CTU		0x02
#घोषणा TXFCB_NPH		0x01
#घोषणा TXFCB_DEFAULT 		(TXFCB_IP|TXFCB_TUP|TXFCB_CTU|TXFCB_NPH)

/* RxBD status field bits */
#घोषणा RXBD_EMPTY		0x8000
#घोषणा RXBD_RO1		0x4000
#घोषणा RXBD_WRAP		0x2000
#घोषणा RXBD_INTERRUPT		0x1000
#घोषणा RXBD_LAST		0x0800
#घोषणा RXBD_FIRST		0x0400
#घोषणा RXBD_MISS		0x0100
#घोषणा RXBD_BROADCAST		0x0080
#घोषणा RXBD_MULTICAST		0x0040
#घोषणा RXBD_LARGE		0x0020
#घोषणा RXBD_NONOCTET		0x0010
#घोषणा RXBD_SHORT		0x0008
#घोषणा RXBD_CRCERR		0x0004
#घोषणा RXBD_OVERRUN		0x0002
#घोषणा RXBD_TRUNCATED		0x0001
#घोषणा RXBD_STATS		0x01ff
#घोषणा RXBD_ERR		(RXBD_LARGE | RXBD_SHORT | RXBD_NONOCTET 	\
				| RXBD_CRCERR | RXBD_OVERRUN			\
				| RXBD_TRUNCATED)

/* Rx FCB status field bits */
#घोषणा RXFCB_VLN		0x8000
#घोषणा RXFCB_IP		0x4000
#घोषणा RXFCB_IP6		0x2000
#घोषणा RXFCB_TUP		0x1000
#घोषणा RXFCB_CIP		0x0800
#घोषणा RXFCB_CTU		0x0400
#घोषणा RXFCB_EIP		0x0200
#घोषणा RXFCB_ETU		0x0100
#घोषणा RXFCB_CSUM_MASK		0x0f00
#घोषणा RXFCB_PERR_MASK		0x000c
#घोषणा RXFCB_PERR_BADL3	0x0008

#घोषणा GFAR_INT_NAME_MAX	(IFNAMSIZ + 6)	/* '_g#_xx' */

#घोषणा GFAR_WOL_MAGIC		0x00000001
#घोषणा GFAR_WOL_खाताR_UCAST	0x00000002

काष्ठा txbd8
अणु
	जोड़ अणु
		काष्ठा अणु
			__be16	status;	/* Status Fields */
			__be16	length;	/* Buffer length */
		पूर्ण;
		__be32 lstatus;
	पूर्ण;
	__be32	bufPtr;	/* Buffer Poपूर्णांकer */
पूर्ण;

काष्ठा txfcb अणु
	u8	flags;
	u8	ptp;    /* Flag to enable tx बारtamping */
	u8	l4os;	/* Level 4 Header Offset */
	u8	l3os; 	/* Level 3 Header Offset */
	__be16	phcs;	/* Pseuकरो-header Checksum */
	__be16	vlctl;	/* VLAN control word */
पूर्ण;

काष्ठा rxbd8
अणु
	जोड़ अणु
		काष्ठा अणु
			__be16	status;	/* Status Fields */
			__be16	length;	/* Buffer Length */
		पूर्ण;
		__be32 lstatus;
	पूर्ण;
	__be32	bufPtr;	/* Buffer Poपूर्णांकer */
पूर्ण;

काष्ठा rxfcb अणु
	__be16	flags;
	u8	rq;	/* Receive Queue index */
	u8	pro;	/* Layer 4 Protocol */
	u16	reserved;
	__be16	vlctl;	/* VLAN control word */
पूर्ण;

काष्ठा gianfar_skb_cb अणु
	अचिन्हित पूर्णांक bytes_sent; /* bytes-on-wire (i.e. no FCB) */
पूर्ण;

#घोषणा GFAR_CB(skb) ((काष्ठा gianfar_skb_cb *)((skb)->cb))

काष्ठा rmon_mib
अणु
	u32	tr64;	/* 0x.680 - Transmit and Receive 64-byte Frame Counter */
	u32	tr127;	/* 0x.684 - Transmit and Receive 65-127 byte Frame Counter */
	u32	tr255;	/* 0x.688 - Transmit and Receive 128-255 byte Frame Counter */
	u32	tr511;	/* 0x.68c - Transmit and Receive 256-511 byte Frame Counter */
	u32	tr1k;	/* 0x.690 - Transmit and Receive 512-1023 byte Frame Counter */
	u32	trmax;	/* 0x.694 - Transmit and Receive 1024-1518 byte Frame Counter */
	u32	trmgv;	/* 0x.698 - Transmit and Receive 1519-1522 byte Good VLAN Frame */
	u32	rbyt;	/* 0x.69c - Receive Byte Counter */
	u32	rpkt;	/* 0x.6a0 - Receive Packet Counter */
	u32	rfcs;	/* 0x.6a4 - Receive FCS Error Counter */
	u32	rmca;	/* 0x.6a8 - Receive Multicast Packet Counter */
	u32	rbca;	/* 0x.6ac - Receive Broadcast Packet Counter */
	u32	rxcf;	/* 0x.6b0 - Receive Control Frame Packet Counter */
	u32	rxpf;	/* 0x.6b4 - Receive Pause Frame Packet Counter */
	u32	rxuo;	/* 0x.6b8 - Receive Unknown OP Code Counter */
	u32	raln;	/* 0x.6bc - Receive Alignment Error Counter */
	u32	rflr;	/* 0x.6c0 - Receive Frame Length Error Counter */
	u32	rcde;	/* 0x.6c4 - Receive Code Error Counter */
	u32	rcse;	/* 0x.6c8 - Receive Carrier Sense Error Counter */
	u32	rund;	/* 0x.6cc - Receive Undersize Packet Counter */
	u32	rovr;	/* 0x.6d0 - Receive Oversize Packet Counter */
	u32	rfrg;	/* 0x.6d4 - Receive Fragments Counter */
	u32	rjbr;	/* 0x.6d8 - Receive Jabber Counter */
	u32	rdrp;	/* 0x.6dc - Receive Drop Counter */
	u32	tbyt;	/* 0x.6e0 - Transmit Byte Counter Counter */
	u32	tpkt;	/* 0x.6e4 - Transmit Packet Counter */
	u32	पंचांगca;	/* 0x.6e8 - Transmit Multicast Packet Counter */
	u32	tbca;	/* 0x.6ec - Transmit Broadcast Packet Counter */
	u32	txpf;	/* 0x.6f0 - Transmit Pause Control Frame Counter */
	u32	tdfr;	/* 0x.6f4 - Transmit Deferral Packet Counter */
	u32	tedf;	/* 0x.6f8 - Transmit Excessive Deferral Packet Counter */
	u32	tscl;	/* 0x.6fc - Transmit Single Collision Packet Counter */
	u32	पंचांगcl;	/* 0x.700 - Transmit Multiple Collision Packet Counter */
	u32	tlcl;	/* 0x.704 - Transmit Late Collision Packet Counter */
	u32	txcl;	/* 0x.708 - Transmit Excessive Collision Packet Counter */
	u32	tncl;	/* 0x.70c - Transmit Total Collision Counter */
	u8	res1[4];
	u32	tdrp;	/* 0x.714 - Transmit Drop Frame Counter */
	u32	tjbr;	/* 0x.718 - Transmit Jabber Frame Counter */
	u32	tfcs;	/* 0x.71c - Transmit FCS Error Counter */
	u32	txcf;	/* 0x.720 - Transmit Control Frame Counter */
	u32	tovr;	/* 0x.724 - Transmit Oversize Frame Counter */
	u32	tund;	/* 0x.728 - Transmit Undersize Frame Counter */
	u32	tfrg;	/* 0x.72c - Transmit Fragments Frame Counter */
	u32	car1;	/* 0x.730 - Carry Register One */
	u32	car2;	/* 0x.734 - Carry Register Two */
	u32	cam1;	/* 0x.738 - Carry Mask Register One */
	u32	cam2;	/* 0x.73c - Carry Mask Register Two */
पूर्ण;

काष्ठा gfar_extra_stats अणु
	atomic64_t rx_alloc_err;
	atomic64_t rx_large;
	atomic64_t rx_लघु;
	atomic64_t rx_nonoctet;
	atomic64_t rx_crcerr;
	atomic64_t rx_overrun;
	atomic64_t rx_bsy;
	atomic64_t rx_babr;
	atomic64_t rx_trunc;
	atomic64_t eberr;
	atomic64_t tx_babt;
	atomic64_t tx_underrun;
	atomic64_t tx_समयout;
पूर्ण;

#घोषणा GFAR_RMON_LEN ((माप(काष्ठा rmon_mib) - 16)/माप(u32))
#घोषणा GFAR_EXTRA_STATS_LEN \
	(माप(काष्ठा gfar_extra_stats)/माप(atomic64_t))

/* Number of stats exported via ethtool */
#घोषणा GFAR_STATS_LEN (GFAR_RMON_LEN + GFAR_EXTRA_STATS_LEN)

काष्ठा gfar अणु
	u32	tsec_id;	/* 0x.000 - Controller ID रेजिस्टर */
	u32	tsec_id2;	/* 0x.004 - Controller ID2 रेजिस्टर */
	u8	res1[8];
	u32	ievent;		/* 0x.010 - Interrupt Event Register */
	u32	imask;		/* 0x.014 - Interrupt Mask Register */
	u32	edis;		/* 0x.018 - Error Disabled Register */
	u32	emapg;		/* 0x.01c - Group Error mapping रेजिस्टर */
	u32	ecntrl;		/* 0x.020 - Ethernet Control Register */
	u32	minflr;		/* 0x.024 - Minimum Frame Length Register */
	u32	ptv;		/* 0x.028 - Pause Time Value Register */
	u32	dmactrl;	/* 0x.02c - DMA Control Register */
	u32	tbipa;		/* 0x.030 - TBI PHY Address Register */
	u8	res2[28];
	u32	fअगरo_rx_छोड़ो;	/* 0x.050 - FIFO receive छोड़ो start threshold
					रेजिस्टर */
	u32	fअगरo_rx_छोड़ो_shutoff;	/* x.054 - FIFO receive starve shutoff
						रेजिस्टर */
	u32	fअगरo_rx_alarm;	/* 0x.058 - FIFO receive alarm start threshold
						रेजिस्टर */
	u32	fअगरo_rx_alarm_shutoff;	/*0x.05c - FIFO receive alarm  starve
						shutoff रेजिस्टर */
	u8	res3[44];
	u32	fअगरo_tx_thr;	/* 0x.08c - FIFO transmit threshold रेजिस्टर */
	u8	res4[8];
	u32	fअगरo_tx_starve;	/* 0x.098 - FIFO transmit starve रेजिस्टर */
	u32	fअगरo_tx_starve_shutoff;	/* 0x.09c - FIFO transmit starve shutoff रेजिस्टर */
	u8	res5[96];
	u32	tctrl;		/* 0x.100 - Transmit Control Register */
	u32	tstat;		/* 0x.104 - Transmit Status Register */
	u32	dfvlan;		/* 0x.108 - Default VLAN Control word */
	u32	tbdlen;		/* 0x.10c - Transmit Buffer Descriptor Data Length Register */
	u32	txic;		/* 0x.110 - Transmit Interrupt Coalescing Configuration Register */
	u32	tqueue;		/* 0x.114 - Transmit queue control रेजिस्टर */
	u8	res7[40];
	u32	tr03wt;		/* 0x.140 - TxBD Rings 0-3 round-robin weightings */
	u32	tr47wt;		/* 0x.144 - TxBD Rings 4-7 round-robin weightings */
	u8	res8[52];
	u32	tbdbph;		/* 0x.17c - Tx data buffer poपूर्णांकer high */
	u8	res9a[4];
	u32	tbptr0;		/* 0x.184 - TxBD Poपूर्णांकer क्रम ring 0 */
	u8	res9b[4];
	u32	tbptr1;		/* 0x.18c - TxBD Poपूर्णांकer क्रम ring 1 */
	u8	res9c[4];
	u32	tbptr2;		/* 0x.194 - TxBD Poपूर्णांकer क्रम ring 2 */
	u8	res9d[4];
	u32	tbptr3;		/* 0x.19c - TxBD Poपूर्णांकer क्रम ring 3 */
	u8	res9e[4];
	u32	tbptr4;		/* 0x.1a4 - TxBD Poपूर्णांकer क्रम ring 4 */
	u8	res9f[4];
	u32	tbptr5;		/* 0x.1ac - TxBD Poपूर्णांकer क्रम ring 5 */
	u8	res9g[4];
	u32	tbptr6;		/* 0x.1b4 - TxBD Poपूर्णांकer क्रम ring 6 */
	u8	res9h[4];
	u32	tbptr7;		/* 0x.1bc - TxBD Poपूर्णांकer क्रम ring 7 */
	u8	res9[64];
	u32	tbaseh;		/* 0x.200 - TxBD base address high */
	u32	tbase0;		/* 0x.204 - TxBD Base Address of ring 0 */
	u8	res10a[4];
	u32	tbase1;		/* 0x.20c - TxBD Base Address of ring 1 */
	u8	res10b[4];
	u32	tbase2;		/* 0x.214 - TxBD Base Address of ring 2 */
	u8	res10c[4];
	u32	tbase3;		/* 0x.21c - TxBD Base Address of ring 3 */
	u8	res10d[4];
	u32	tbase4;		/* 0x.224 - TxBD Base Address of ring 4 */
	u8	res10e[4];
	u32	tbase5;		/* 0x.22c - TxBD Base Address of ring 5 */
	u8	res10f[4];
	u32	tbase6;		/* 0x.234 - TxBD Base Address of ring 6 */
	u8	res10g[4];
	u32	tbase7;		/* 0x.23c - TxBD Base Address of ring 7 */
	u8	res10[192];
	u32	rctrl;		/* 0x.300 - Receive Control Register */
	u32	rstat;		/* 0x.304 - Receive Status Register */
	u8	res12[8];
	u32	rxic;		/* 0x.310 - Receive Interrupt Coalescing Configuration Register */
	u32	rqueue;		/* 0x.314 - Receive queue control रेजिस्टर */
	u32	rir0;		/* 0x.318 - Ring mapping रेजिस्टर 0 */
	u32	rir1;		/* 0x.31c - Ring mapping रेजिस्टर 1 */
	u32	rir2;		/* 0x.320 - Ring mapping रेजिस्टर 2 */
	u32	rir3;		/* 0x.324 - Ring mapping रेजिस्टर 3 */
	u8	res13[8];
	u32	rbअगरx;		/* 0x.330 - Receive bit field extract control रेजिस्टर */
	u32	rqfar;		/* 0x.334 - Receive queue filing table address रेजिस्टर */
	u32	rqfcr;		/* 0x.338 - Receive queue filing table control रेजिस्टर */
	u32	rqfpr;		/* 0x.33c - Receive queue filing table property रेजिस्टर */
	u32	mrblr;		/* 0x.340 - Maximum Receive Buffer Length Register */
	u8	res14[56];
	u32	rbdbph;		/* 0x.37c - Rx data buffer poपूर्णांकer high */
	u8	res15a[4];
	u32	rbptr0;		/* 0x.384 - RxBD poपूर्णांकer क्रम ring 0 */
	u8	res15b[4];
	u32	rbptr1;		/* 0x.38c - RxBD poपूर्णांकer क्रम ring 1 */
	u8	res15c[4];
	u32	rbptr2;		/* 0x.394 - RxBD poपूर्णांकer क्रम ring 2 */
	u8	res15d[4];
	u32	rbptr3;		/* 0x.39c - RxBD poपूर्णांकer क्रम ring 3 */
	u8	res15e[4];
	u32	rbptr4;		/* 0x.3a4 - RxBD poपूर्णांकer क्रम ring 4 */
	u8	res15f[4];
	u32	rbptr5;		/* 0x.3ac - RxBD poपूर्णांकer क्रम ring 5 */
	u8	res15g[4];
	u32	rbptr6;		/* 0x.3b4 - RxBD poपूर्णांकer क्रम ring 6 */
	u8	res15h[4];
	u32	rbptr7;		/* 0x.3bc - RxBD poपूर्णांकer क्रम ring 7 */
	u8	res16[64];
	u32	rbaseh;		/* 0x.400 - RxBD base address high */
	u32	rbase0;		/* 0x.404 - RxBD base address of ring 0 */
	u8	res17a[4];
	u32	rbase1;		/* 0x.40c - RxBD base address of ring 1 */
	u8	res17b[4];
	u32	rbase2;		/* 0x.414 - RxBD base address of ring 2 */
	u8	res17c[4];
	u32	rbase3;		/* 0x.41c - RxBD base address of ring 3 */
	u8	res17d[4];
	u32	rbase4;		/* 0x.424 - RxBD base address of ring 4 */
	u8	res17e[4];
	u32	rbase5;		/* 0x.42c - RxBD base address of ring 5 */
	u8	res17f[4];
	u32	rbase6;		/* 0x.434 - RxBD base address of ring 6 */
	u8	res17g[4];
	u32	rbase7;		/* 0x.43c - RxBD base address of ring 7 */
	u8	res17[192];
	u32	maccfg1;	/* 0x.500 - MAC Configuration 1 Register */
	u32	maccfg2;	/* 0x.504 - MAC Configuration 2 Register */
	u32	ipgअगरg;		/* 0x.508 - Inter Packet Gap/Inter Frame Gap Register */
	u32	hafdup;		/* 0x.50c - Half Duplex Register */
	u32	maxfrm;		/* 0x.510 - Maximum Frame Length Register */
	u8	res18[12];
	u8	gfar_mii_regs[24];	/* See gianfar_phy.h */
	u32	अगरctrl;		/* 0x.538 - Interface control रेजिस्टर */
	u32	अगरstat;		/* 0x.53c - Interface Status Register */
	u32	macstnaddr1;	/* 0x.540 - Station Address Part 1 Register */
	u32	macstnaddr2;	/* 0x.544 - Station Address Part 2 Register */
	u32	mac01addr1;	/* 0x.548 - MAC exact match address 1, part 1 */
	u32	mac01addr2;	/* 0x.54c - MAC exact match address 1, part 2 */
	u32	mac02addr1;	/* 0x.550 - MAC exact match address 2, part 1 */
	u32	mac02addr2;	/* 0x.554 - MAC exact match address 2, part 2 */
	u32	mac03addr1;	/* 0x.558 - MAC exact match address 3, part 1 */
	u32	mac03addr2;	/* 0x.55c - MAC exact match address 3, part 2 */
	u32	mac04addr1;	/* 0x.560 - MAC exact match address 4, part 1 */
	u32	mac04addr2;	/* 0x.564 - MAC exact match address 4, part 2 */
	u32	mac05addr1;	/* 0x.568 - MAC exact match address 5, part 1 */
	u32	mac05addr2;	/* 0x.56c - MAC exact match address 5, part 2 */
	u32	mac06addr1;	/* 0x.570 - MAC exact match address 6, part 1 */
	u32	mac06addr2;	/* 0x.574 - MAC exact match address 6, part 2 */
	u32	mac07addr1;	/* 0x.578 - MAC exact match address 7, part 1 */
	u32	mac07addr2;	/* 0x.57c - MAC exact match address 7, part 2 */
	u32	mac08addr1;	/* 0x.580 - MAC exact match address 8, part 1 */
	u32	mac08addr2;	/* 0x.584 - MAC exact match address 8, part 2 */
	u32	mac09addr1;	/* 0x.588 - MAC exact match address 9, part 1 */
	u32	mac09addr2;	/* 0x.58c - MAC exact match address 9, part 2 */
	u32	mac10addr1;	/* 0x.590 - MAC exact match address 10, part 1*/
	u32	mac10addr2;	/* 0x.594 - MAC exact match address 10, part 2*/
	u32	mac11addr1;	/* 0x.598 - MAC exact match address 11, part 1*/
	u32	mac11addr2;	/* 0x.59c - MAC exact match address 11, part 2*/
	u32	mac12addr1;	/* 0x.5a0 - MAC exact match address 12, part 1*/
	u32	mac12addr2;	/* 0x.5a4 - MAC exact match address 12, part 2*/
	u32	mac13addr1;	/* 0x.5a8 - MAC exact match address 13, part 1*/
	u32	mac13addr2;	/* 0x.5ac - MAC exact match address 13, part 2*/
	u32	mac14addr1;	/* 0x.5b0 - MAC exact match address 14, part 1*/
	u32	mac14addr2;	/* 0x.5b4 - MAC exact match address 14, part 2*/
	u32	mac15addr1;	/* 0x.5b8 - MAC exact match address 15, part 1*/
	u32	mac15addr2;	/* 0x.5bc - MAC exact match address 15, part 2*/
	u8	res20[192];
	काष्ठा rmon_mib	rmon;	/* 0x.680-0x.73c */
	u32	rrej;		/* 0x.740 - Receive filer rejected packet counter */
	u8	res21[188];
	u32	igaddr0;	/* 0x.800 - Inभागdual/Group address रेजिस्टर 0*/
	u32	igaddr1;	/* 0x.804 - Inभागdual/Group address रेजिस्टर 1*/
	u32	igaddr2;	/* 0x.808 - Inभागdual/Group address रेजिस्टर 2*/
	u32	igaddr3;	/* 0x.80c - Inभागdual/Group address रेजिस्टर 3*/
	u32	igaddr4;	/* 0x.810 - Inभागdual/Group address रेजिस्टर 4*/
	u32	igaddr5;	/* 0x.814 - Inभागdual/Group address रेजिस्टर 5*/
	u32	igaddr6;	/* 0x.818 - Inभागdual/Group address रेजिस्टर 6*/
	u32	igaddr7;	/* 0x.81c - Inभागdual/Group address रेजिस्टर 7*/
	u8	res22[96];
	u32	gaddr0;		/* 0x.880 - Group address रेजिस्टर 0 */
	u32	gaddr1;		/* 0x.884 - Group address रेजिस्टर 1 */
	u32	gaddr2;		/* 0x.888 - Group address रेजिस्टर 2 */
	u32	gaddr3;		/* 0x.88c - Group address रेजिस्टर 3 */
	u32	gaddr4;		/* 0x.890 - Group address रेजिस्टर 4 */
	u32	gaddr5;		/* 0x.894 - Group address रेजिस्टर 5 */
	u32	gaddr6;		/* 0x.898 - Group address रेजिस्टर 6 */
	u32	gaddr7;		/* 0x.89c - Group address रेजिस्टर 7 */
	u8	res23a[352];
	u32	fअगरocfg;	/* 0x.a00 - FIFO पूर्णांकerface config रेजिस्टर */
	u8	res23b[252];
	u8	res23c[248];
	u32	attr;		/* 0x.bf8 - Attributes Register */
	u32	attreli;	/* 0x.bfc - Attributes Extract Length and Extract Index Register */
	u32	rqprm0;	/* 0x.c00 - Receive queue parameters रेजिस्टर 0 */
	u32	rqprm1;	/* 0x.c04 - Receive queue parameters रेजिस्टर 1 */
	u32	rqprm2;	/* 0x.c08 - Receive queue parameters रेजिस्टर 2 */
	u32	rqprm3;	/* 0x.c0c - Receive queue parameters रेजिस्टर 3 */
	u32	rqprm4;	/* 0x.c10 - Receive queue parameters रेजिस्टर 4 */
	u32	rqprm5;	/* 0x.c14 - Receive queue parameters रेजिस्टर 5 */
	u32	rqprm6;	/* 0x.c18 - Receive queue parameters रेजिस्टर 6 */
	u32	rqprm7;	/* 0x.c1c - Receive queue parameters रेजिस्टर 7 */
	u8	res24[36];
	u32	rfbptr0; /* 0x.c44 - Last मुक्त RxBD poपूर्णांकer क्रम ring 0 */
	u8	res24a[4];
	u32	rfbptr1; /* 0x.c4c - Last मुक्त RxBD poपूर्णांकer क्रम ring 1 */
	u8	res24b[4];
	u32	rfbptr2; /* 0x.c54 - Last मुक्त RxBD poपूर्णांकer क्रम ring 2 */
	u8	res24c[4];
	u32	rfbptr3; /* 0x.c5c - Last मुक्त RxBD poपूर्णांकer क्रम ring 3 */
	u8	res24d[4];
	u32	rfbptr4; /* 0x.c64 - Last मुक्त RxBD poपूर्णांकer क्रम ring 4 */
	u8	res24e[4];
	u32	rfbptr5; /* 0x.c6c - Last मुक्त RxBD poपूर्णांकer क्रम ring 5 */
	u8	res24f[4];
	u32	rfbptr6; /* 0x.c74 - Last मुक्त RxBD poपूर्णांकer क्रम ring 6 */
	u8	res24g[4];
	u32	rfbptr7; /* 0x.c7c - Last मुक्त RxBD poपूर्णांकer क्रम ring 7 */
	u8	res24h[4];
	u8	res24x[556];
	u32	isrg0;		/* 0x.eb0 - Interrupt steering group 0 रेजिस्टर */
	u32	isrg1;		/* 0x.eb4 - Interrupt steering group 1 रेजिस्टर */
	u32	isrg2;		/* 0x.eb8 - Interrupt steering group 2 रेजिस्टर */
	u32	isrg3;		/* 0x.ebc - Interrupt steering group 3 रेजिस्टर */
	u8	res25[16];
	u32	rxic0;		/* 0x.ed0 - Ring 0 Rx पूर्णांकerrupt coalescing */
	u32	rxic1;		/* 0x.ed4 - Ring 1 Rx पूर्णांकerrupt coalescing */
	u32	rxic2;		/* 0x.ed8 - Ring 2 Rx पूर्णांकerrupt coalescing */
	u32	rxic3;		/* 0x.edc - Ring 3 Rx पूर्णांकerrupt coalescing */
	u32	rxic4;		/* 0x.ee0 - Ring 4 Rx पूर्णांकerrupt coalescing */
	u32	rxic5;		/* 0x.ee4 - Ring 5 Rx पूर्णांकerrupt coalescing */
	u32	rxic6;		/* 0x.ee8 - Ring 6 Rx पूर्णांकerrupt coalescing */
	u32	rxic7;		/* 0x.eec - Ring 7 Rx पूर्णांकerrupt coalescing */
	u8	res26[32];
	u32	txic0;		/* 0x.f10 - Ring 0 Tx पूर्णांकerrupt coalescing */
	u32	txic1;		/* 0x.f14 - Ring 1 Tx पूर्णांकerrupt coalescing */
	u32	txic2;		/* 0x.f18 - Ring 2 Tx पूर्णांकerrupt coalescing */
	u32	txic3;		/* 0x.f1c - Ring 3 Tx पूर्णांकerrupt coalescing */
	u32	txic4;		/* 0x.f20 - Ring 4 Tx पूर्णांकerrupt coalescing */
	u32	txic5;		/* 0x.f24 - Ring 5 Tx पूर्णांकerrupt coalescing */
	u32	txic6;		/* 0x.f28 - Ring 6 Tx पूर्णांकerrupt coalescing */
	u32	txic7;		/* 0x.f2c - Ring 7 Tx पूर्णांकerrupt coalescing */
	u8	res27[208];
पूर्ण;

/* Flags related to gianfar device features */
#घोषणा FSL_GIANFAR_DEV_HAS_GIGABIT		0x00000001
#घोषणा FSL_GIANFAR_DEV_HAS_COALESCE		0x00000002
#घोषणा FSL_GIANFAR_DEV_HAS_RMON		0x00000004
#घोषणा FSL_GIANFAR_DEV_HAS_MULTI_INTR		0x00000008
#घोषणा FSL_GIANFAR_DEV_HAS_CSUM		0x00000010
#घोषणा FSL_GIANFAR_DEV_HAS_VLAN		0x00000020
#घोषणा FSL_GIANFAR_DEV_HAS_EXTENDED_HASH	0x00000040
#घोषणा FSL_GIANFAR_DEV_HAS_MAGIC_PACKET	0x00000100
#घोषणा FSL_GIANFAR_DEV_HAS_BD_STASHING		0x00000200
#घोषणा FSL_GIANFAR_DEV_HAS_BUF_STASHING	0x00000400
#घोषणा FSL_GIANFAR_DEV_HAS_TIMER		0x00000800
#घोषणा FSL_GIANFAR_DEV_HAS_WAKE_ON_खाताR	0x00001000
#घोषणा FSL_GIANFAR_DEV_HAS_RX_खाताR		0x00002000

#अगर (MAXGROUPS == 2)
#घोषणा DEFAULT_MAPPING 	0xAA
#अन्यथा
#घोषणा DEFAULT_MAPPING 	0xFF
#पूर्ण_अगर

#घोषणा ISRG_RR0	0x80000000
#घोषणा ISRG_TR0	0x00800000

/* The same driver can operate in two modes */
/* SQ_SG_MODE: Single Queue Single Group Mode
 * 		(Backward compatible mode)
 * MQ_MG_MODE: Multi Queue Multi Group mode
 */
क्रमागत अणु
	SQ_SG_MODE = 0,
	MQ_MG_MODE
पूर्ण;

/*
 * Per TX queue stats
 */
काष्ठा tx_q_stats अणु
	अचिन्हित दीर्घ tx_packets;
	अचिन्हित दीर्घ tx_bytes;
पूर्ण;

/**
 *	काष्ठा gfar_priv_tx_q - per tx queue काष्ठाure
 *	@txlock: per queue tx spin lock
 *	@tx_skbuff:skb poपूर्णांकers
 *	@skb_curtx: to be used skb poपूर्णांकer
 *	@skb_dirtytx:the last used skb poपूर्णांकer
 *	@stats: bytes/packets stats
 *	@qindex: index of this queue
 *	@dev: back poपूर्णांकer to the dev काष्ठाure
 *	@grp: back poपूर्णांकer to the group to which this queue beदीर्घs
 *	@tx_bd_base: First tx buffer descriptor
 *	@cur_tx: Next मुक्त ring entry
 *	@dirty_tx: First buffer in line to be transmitted
 *	@tx_ring_size: Tx ring size
 *	@num_txbdमुक्त: number of मुक्त TxBds
 *	@txcoalescing: enable/disable tx coalescing
 *	@txic: transmit पूर्णांकerrupt coalescing value
 *	@txcount: coalescing value अगर based on tx frame count
 *	@txसमय: coalescing value अगर based on समय
 */
काष्ठा gfar_priv_tx_q अणु
	/* cacheline 1 */
	spinlock_t txlock __attribute__ ((aligned (SMP_CACHE_BYTES)));
	काष्ठा	txbd8 *tx_bd_base;
	काष्ठा	txbd8 *cur_tx;
	अचिन्हित पूर्णांक num_txbdमुक्त;
	अचिन्हित लघु skb_curtx;
	अचिन्हित लघु tx_ring_size;
	काष्ठा tx_q_stats stats;
	काष्ठा gfar_priv_grp *grp;
	/* cacheline 2 */
	काष्ठा net_device *dev;
	काष्ठा sk_buff **tx_skbuff;
	काष्ठा	txbd8 *dirty_tx;
	अचिन्हित लघु skb_dirtytx;
	अचिन्हित लघु qindex;
	/* Configuration info क्रम the coalescing features */
	अचिन्हित पूर्णांक txcoalescing;
	अचिन्हित दीर्घ txic;
	dma_addr_t tx_bd_dma_base;
पूर्ण;

/*
 * Per RX queue stats
 */
काष्ठा rx_q_stats अणु
	अचिन्हित दीर्घ rx_packets;
	अचिन्हित दीर्घ rx_bytes;
	अचिन्हित दीर्घ rx_dropped;
पूर्ण;

काष्ठा gfar_rx_buff अणु
	dma_addr_t dma;
	काष्ठा page *page;
	अचिन्हित पूर्णांक page_offset;
पूर्ण;

/**
 *	काष्ठा gfar_priv_rx_q - per rx queue काष्ठाure
 *	@rx_buff: Array of buffer info metadata काष्ठाs
 *	@rx_bd_base: First rx buffer descriptor
 *	@next_to_use: index of the next buffer to be alloc'd
 *	@next_to_clean: index of the next buffer to be cleaned
 *	@qindex: index of this queue
 *	@ndev: back poपूर्णांकer to net_device
 *	@rx_ring_size: Rx ring size
 *	@rxcoalescing: enable/disable rx-coalescing
 *	@rxic: receive पूर्णांकerrupt coalescing vlaue
 */

काष्ठा gfar_priv_rx_q अणु
	काष्ठा	gfar_rx_buff *rx_buff __aligned(SMP_CACHE_BYTES);
	काष्ठा	rxbd8 *rx_bd_base;
	काष्ठा	net_device *ndev;
	काष्ठा	device *dev;
	u16 rx_ring_size;
	u16 qindex;
	काष्ठा	gfar_priv_grp *grp;
	u16 next_to_clean;
	u16 next_to_use;
	u16 next_to_alloc;
	काष्ठा	sk_buff *skb;
	काष्ठा rx_q_stats stats;
	u32 __iomem *rfbptr;
	अचिन्हित अक्षर rxcoalescing;
	अचिन्हित दीर्घ rxic;
	dma_addr_t rx_bd_dma_base;
पूर्ण;

क्रमागत gfar_irqinfo_id अणु
	GFAR_TX = 0,
	GFAR_RX = 1,
	GFAR_ER = 2,
	GFAR_NUM_IRQS = 3
पूर्ण;

काष्ठा gfar_irqinfo अणु
	अचिन्हित पूर्णांक irq;
	अक्षर name[GFAR_INT_NAME_MAX];
पूर्ण;

/**
 *	काष्ठा gfar_priv_grp - per group काष्ठाure
 *	@napi: the napi poll function
 *	@priv: back poपूर्णांकer to the priv काष्ठाure
 *	@regs: the ioremapped रेजिस्टर space क्रम this group
 *	@irqinfo: TX/RX/ER irq data क्रम this group
 */

काष्ठा gfar_priv_grp अणु
	spinlock_t grplock __aligned(SMP_CACHE_BYTES);
	काष्ठा	napi_काष्ठा napi_rx;
	काष्ठा	napi_काष्ठा napi_tx;
	काष्ठा gfar __iomem *regs;
	काष्ठा gfar_priv_tx_q *tx_queue;
	काष्ठा gfar_priv_rx_q *rx_queue;
	अचिन्हित पूर्णांक tstat;
	अचिन्हित पूर्णांक rstat;

	काष्ठा gfar_निजी *priv;
	अचिन्हित दीर्घ num_tx_queues;
	अचिन्हित दीर्घ tx_bit_map;
	अचिन्हित दीर्घ num_rx_queues;
	अचिन्हित दीर्घ rx_bit_map;

	काष्ठा gfar_irqinfo *irqinfo[GFAR_NUM_IRQS];
पूर्ण;

#घोषणा gfar_irq(grp, ID) \
	((grp)->irqinfo[GFAR_##ID])

क्रमागत gfar_errata अणु
	GFAR_ERRATA_74		= 0x01,
	GFAR_ERRATA_76		= 0x02,
	GFAR_ERRATA_A002	= 0x04,
	GFAR_ERRATA_12		= 0x08, /* a.k.a errata eTSEC49 */
पूर्ण;

क्रमागत gfar_dev_state अणु
	GFAR_DOWN = 1,
	GFAR_RESETTING
पूर्ण;

/* Struct stolen almost completely (and shamelessly) from the FCC enet source
 * (Ok, that's not so true anymore, but there is a family resemblance)
 * The GFAR buffer descriptors track the ring buffers.  The rx_bd_base
 * and tx_bd_base always poपूर्णांक to the currently available buffer.
 * The dirty_tx tracks the current buffer that is being sent by the
 * controller.  The cur_tx and dirty_tx are equal under both completely
 * empty and completely full conditions.  The empty/पढ़ोy indicator in
 * the buffer descriptor determines the actual condition.
 */
काष्ठा gfar_निजी अणु
	काष्ठा device *dev;
	काष्ठा net_device *ndev;
	क्रमागत gfar_errata errata;

	u16 uses_rxfcb;
	u16 padding;
	u32 device_flags;

	/* HW समय stamping enabled flag */
	पूर्णांक hwts_rx_en;
	पूर्णांक hwts_tx_en;

	काष्ठा gfar_priv_tx_q *tx_queue[MAX_TX_QS];
	काष्ठा gfar_priv_rx_q *rx_queue[MAX_RX_QS];
	काष्ठा gfar_priv_grp gfargrp[MAXGROUPS];

	अचिन्हित दीर्घ state;

	अचिन्हित लघु mode;
	अचिन्हित पूर्णांक num_tx_queues;
	अचिन्हित पूर्णांक num_rx_queues;
	अचिन्हित पूर्णांक num_grps;
	पूर्णांक tx_actual_en;

	/* Network Statistics */
	काष्ठा gfar_extra_stats extra_stats;

	/* PHY stuff */
	phy_पूर्णांकerface_t पूर्णांकerface;
	काष्ठा device_node *phy_node;
	काष्ठा device_node *tbi_node;
	काष्ठा mii_bus *mii_bus;
	पूर्णांक oldspeed;
	पूर्णांक oldduplex;
	पूर्णांक oldlink;

	uपूर्णांक32_t msg_enable;

	काष्ठा work_काष्ठा reset_task;

	काष्ठा platक्रमm_device *ofdev;
	अचिन्हित अक्षर
		extended_hash:1,
		bd_stash_en:1,
		rx_filer_enable:1,
		/* Enable priorty based Tx scheduling in Hw */
		prio_sched_en:1,
		/* Flow control flags */
		छोड़ो_aneg_en:1,
		tx_छोड़ो_en:1,
		rx_छोड़ो_en:1;

	/* The total tx and rx ring size क्रम the enabled queues */
	अचिन्हित पूर्णांक total_tx_ring_size;
	अचिन्हित पूर्णांक total_rx_ring_size;

	u32 rqueue;
	u32 tqueue;

	/* RX per device parameters */
	अचिन्हित पूर्णांक rx_stash_size;
	अचिन्हित पूर्णांक rx_stash_index;

	u32 cur_filer_idx;

	/* RX queue filer rule set*/
	काष्ठा ethtool_rx_list rx_list;
	काष्ठा mutex rx_queue_access;

	/* Hash रेजिस्टरs and their width */
	u32 __iomem *hash_regs[16];
	पूर्णांक hash_width;

	/* wake-on-lan settings */
	u16 wol_opts;
	u16 wol_supported;

	/*Filer table*/
	अचिन्हित पूर्णांक ftp_rqfpr[MAX_खाताR_IDX + 1];
	अचिन्हित पूर्णांक ftp_rqfcr[MAX_खाताR_IDX + 1];
पूर्ण;


अटल अंतरभूत पूर्णांक gfar_has_errata(काष्ठा gfar_निजी *priv,
				  क्रमागत gfar_errata err)
अणु
	वापस priv->errata & err;
पूर्ण

अटल अंतरभूत u32 gfar_पढ़ो(अचिन्हित __iomem *addr)
अणु
	u32 val;
	val = ioपढ़ो32be(addr);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम gfar_ग_लिखो(अचिन्हित __iomem *addr, u32 val)
अणु
	ioग_लिखो32be(val, addr);
पूर्ण

अटल अंतरभूत व्योम gfar_ग_लिखो_filer(काष्ठा gfar_निजी *priv,
		अचिन्हित पूर्णांक far, अचिन्हित पूर्णांक fcr, अचिन्हित पूर्णांक fpr)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;

	gfar_ग_लिखो(&regs->rqfar, far);
	gfar_ग_लिखो(&regs->rqfcr, fcr);
	gfar_ग_लिखो(&regs->rqfpr, fpr);
पूर्ण

अटल अंतरभूत व्योम gfar_पढ़ो_filer(काष्ठा gfar_निजी *priv,
		अचिन्हित पूर्णांक far, अचिन्हित पूर्णांक *fcr, अचिन्हित पूर्णांक *fpr)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;

	gfar_ग_लिखो(&regs->rqfar, far);
	*fcr = gfar_पढ़ो(&regs->rqfcr);
	*fpr = gfar_पढ़ो(&regs->rqfpr);
पूर्ण

अटल अंतरभूत व्योम gfar_ग_लिखो_isrg(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 __iomem *baddr = &regs->isrg0;
	u32 isrg = 0;
	पूर्णांक grp_idx, i;

	क्रम (grp_idx = 0; grp_idx < priv->num_grps; grp_idx++) अणु
		काष्ठा gfar_priv_grp *grp = &priv->gfargrp[grp_idx];

		क्रम_each_set_bit(i, &grp->rx_bit_map, priv->num_rx_queues) अणु
			isrg |= (ISRG_RR0 >> i);
		पूर्ण

		क्रम_each_set_bit(i, &grp->tx_bit_map, priv->num_tx_queues) अणु
			isrg |= (ISRG_TR0 >> i);
		पूर्ण

		gfar_ग_लिखो(baddr, isrg);

		baddr++;
		isrg = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक gfar_is_dma_stopped(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;

	वापस ((gfar_पढ़ो(&regs->ievent) & (IEVENT_GRSC | IEVENT_GTSC)) ==
	       (IEVENT_GRSC | IEVENT_GTSC));
पूर्ण

अटल अंतरभूत पूर्णांक gfar_is_rx_dma_stopped(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;

	वापस gfar_पढ़ो(&regs->ievent) & IEVENT_GRSC;
पूर्ण

अटल अंतरभूत व्योम gfar_wmb(व्योम)
अणु
#अगर defined(CONFIG_PPC)
	/* The घातerpc-specअगरic eieio() is used, as wmb() has too strong
	 * semantics (it requires synchronization between cacheable and
	 * uncacheable mappings, which eieio() करोesn't provide and which we
	 * करोn't need), thus requiring a more expensive sync inकाष्ठाion.  At
	 * some poपूर्णांक, the set of architecture-independent barrier functions
	 * should be expanded to include weaker barriers.
	 */
	eieio();
#अन्यथा
	wmb(); /* order ग_लिखो acesses क्रम BD (or FCB) fields */
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम gfar_clear_txbd_status(काष्ठा txbd8 *bdp)
अणु
	u32 lstatus = be32_to_cpu(bdp->lstatus);

	lstatus &= BD_LFLAG(TXBD_WRAP);
	bdp->lstatus = cpu_to_be32(lstatus);
पूर्ण

अटल अंतरभूत पूर्णांक gfar_rxbd_unused(काष्ठा gfar_priv_rx_q *rxq)
अणु
	अगर (rxq->next_to_clean > rxq->next_to_use)
		वापस rxq->next_to_clean - rxq->next_to_use - 1;

	वापस rxq->rx_ring_size + rxq->next_to_clean - rxq->next_to_use - 1;
पूर्ण

अटल अंतरभूत u32 gfar_rxbd_dma_lastमुक्त(काष्ठा gfar_priv_rx_q *rxq)
अणु
	काष्ठा rxbd8 *bdp;
	u32 bdp_dma;
	पूर्णांक i;

	i = rxq->next_to_use ? rxq->next_to_use - 1 : rxq->rx_ring_size - 1;
	bdp = &rxq->rx_bd_base[i];
	bdp_dma = lower_32_bits(rxq->rx_bd_dma_base);
	bdp_dma += (uपूर्णांकptr_t)bdp - (uपूर्णांकptr_t)rxq->rx_bd_base;

	वापस bdp_dma;
पूर्ण

पूर्णांक startup_gfar(काष्ठा net_device *dev);
व्योम stop_gfar(काष्ठा net_device *dev);
व्योम gfar_mac_reset(काष्ठा gfar_निजी *priv);
पूर्णांक gfar_set_features(काष्ठा net_device *dev, netdev_features_t features);

बाह्य स्थिर काष्ठा ethtool_ops gfar_ethtool_ops;

#घोषणा MAX_खाताR_CACHE_IDX (2*(MAX_खाताR_IDX))

#घोषणा RQFCR_PID_PRI_MASK 0xFFFFFFF8
#घोषणा RQFCR_PID_L4P_MASK 0xFFFFFF00
#घोषणा RQFCR_PID_VID_MASK 0xFFFFF000
#घोषणा RQFCR_PID_PORT_MASK 0xFFFF0000
#घोषणा RQFCR_PID_MAC_MASK 0xFF000000

/* Represents a receive filer table entry */
काष्ठा gfar_filer_entry अणु
	u32 ctrl;
	u32 prop;
पूर्ण;


/* The 20 additional entries are a shaकरोw क्रम one extra element */
काष्ठा filer_table अणु
	u32 index;
	काष्ठा gfar_filer_entry fe[MAX_खाताR_CACHE_IDX + 20];
पूर्ण;

#पूर्ण_अगर /* __GIANFAR_H */
