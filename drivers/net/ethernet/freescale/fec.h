<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	fec.h  --  Fast Ethernet Controller क्रम Motorola ColdFire SoC
 *		   processors.
 *
 *	(C) Copyright 2000-2005, Greg Ungerer (gerg@snapgear.com)
 *	(C) Copyright 2000-2001, Lineo (www.lineo.com)
 */

/****************************************************************************/
#अगर_अघोषित FEC_H
#घोषणा	FEC_H
/****************************************************************************/

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समयcounter.h>

#अगर defined(CONFIG_M523x) || defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
    defined(CONFIG_M520x) || defined(CONFIG_M532x) || defined(CONFIG_ARM) || \
    defined(CONFIG_ARM64) || defined(CONFIG_COMPILE_TEST)
/*
 *	Just figures, Motorola would have to change the offsets क्रम
 *	रेजिस्टरs in the same peripheral device on dअगरferent models
 *	of the ColdFire!
 */
#घोषणा FEC_IEVENT		0x004 /* Interrupt event reg */
#घोषणा FEC_IMASK		0x008 /* Interrupt mask reg */
#घोषणा FEC_R_DES_ACTIVE_0	0x010 /* Receive descriptor reg */
#घोषणा FEC_X_DES_ACTIVE_0	0x014 /* Transmit descriptor reg */
#घोषणा FEC_ECNTRL		0x024 /* Ethernet control reg */
#घोषणा FEC_MII_DATA		0x040 /* MII manage frame reg */
#घोषणा FEC_MII_SPEED		0x044 /* MII speed control reg */
#घोषणा FEC_MIB_CTRLSTAT	0x064 /* MIB control/status reg */
#घोषणा FEC_R_CNTRL		0x084 /* Receive control reg */
#घोषणा FEC_X_CNTRL		0x0c4 /* Transmit Control reg */
#घोषणा FEC_ADDR_LOW		0x0e4 /* Low 32bits MAC address */
#घोषणा FEC_ADDR_HIGH		0x0e8 /* High 16bits MAC address */
#घोषणा FEC_OPD			0x0ec /* Opcode + Pause duration */
#घोषणा FEC_TXIC0		0x0f0 /* Tx Interrupt Coalescing क्रम ring 0 */
#घोषणा FEC_TXIC1		0x0f4 /* Tx Interrupt Coalescing क्रम ring 1 */
#घोषणा FEC_TXIC2		0x0f8 /* Tx Interrupt Coalescing क्रम ring 2 */
#घोषणा FEC_RXIC0		0x100 /* Rx Interrupt Coalescing क्रम ring 0 */
#घोषणा FEC_RXIC1		0x104 /* Rx Interrupt Coalescing क्रम ring 1 */
#घोषणा FEC_RXIC2		0x108 /* Rx Interrupt Coalescing क्रम ring 2 */
#घोषणा FEC_HASH_TABLE_HIGH	0x118 /* High 32bits hash table */
#घोषणा FEC_HASH_TABLE_LOW	0x11c /* Low 32bits hash table */
#घोषणा FEC_GRP_HASH_TABLE_HIGH	0x120 /* High 32bits hash table */
#घोषणा FEC_GRP_HASH_TABLE_LOW	0x124 /* Low 32bits hash table */
#घोषणा FEC_X_WMRK		0x144 /* FIFO transmit water mark */
#घोषणा FEC_R_BOUND		0x14c /* FIFO receive bound reg */
#घोषणा FEC_R_FSTART		0x150 /* FIFO receive start reg */
#घोषणा FEC_R_DES_START_1	0x160 /* Receive descriptor ring 1 */
#घोषणा FEC_X_DES_START_1	0x164 /* Transmit descriptor ring 1 */
#घोषणा FEC_R_BUFF_SIZE_1	0x168 /* Maximum receive buff ring1 size */
#घोषणा FEC_R_DES_START_2	0x16c /* Receive descriptor ring 2 */
#घोषणा FEC_X_DES_START_2	0x170 /* Transmit descriptor ring 2 */
#घोषणा FEC_R_BUFF_SIZE_2	0x174 /* Maximum receive buff ring2 size */
#घोषणा FEC_R_DES_START_0	0x180 /* Receive descriptor ring */
#घोषणा FEC_X_DES_START_0	0x184 /* Transmit descriptor ring */
#घोषणा FEC_R_BUFF_SIZE_0	0x188 /* Maximum receive buff size */
#घोषणा FEC_R_FIFO_RSFL		0x190 /* Receive FIFO section full threshold */
#घोषणा FEC_R_FIFO_RSEM		0x194 /* Receive FIFO section empty threshold */
#घोषणा FEC_R_FIFO_RAEM		0x198 /* Receive FIFO almost empty threshold */
#घोषणा FEC_R_FIFO_RAFL		0x19c /* Receive FIFO almost full threshold */
#घोषणा FEC_FTRL		0x1b0 /* Frame truncation receive length*/
#घोषणा FEC_RACC		0x1c4 /* Receive Accelerator function */
#घोषणा FEC_RCMR_1		0x1c8 /* Receive classअगरication match ring 1 */
#घोषणा FEC_RCMR_2		0x1cc /* Receive classअगरication match ring 2 */
#घोषणा FEC_DMA_CFG_1		0x1d8 /* DMA class configuration क्रम ring 1 */
#घोषणा FEC_DMA_CFG_2		0x1dc /* DMA class Configuration क्रम ring 2 */
#घोषणा FEC_R_DES_ACTIVE_1	0x1e0 /* Rx descriptor active क्रम ring 1 */
#घोषणा FEC_X_DES_ACTIVE_1	0x1e4 /* Tx descriptor active क्रम ring 1 */
#घोषणा FEC_R_DES_ACTIVE_2	0x1e8 /* Rx descriptor active क्रम ring 2 */
#घोषणा FEC_X_DES_ACTIVE_2	0x1ec /* Tx descriptor active क्रम ring 2 */
#घोषणा FEC_QOS_SCHEME		0x1f0 /* Set multi queues Qos scheme */
#घोषणा FEC_MIIGSK_CFGR		0x300 /* MIIGSK Configuration reg */
#घोषणा FEC_MIIGSK_ENR		0x308 /* MIIGSK Enable reg */

#घोषणा BM_MIIGSK_CFGR_MII		0x00
#घोषणा BM_MIIGSK_CFGR_RMII		0x01
#घोषणा BM_MIIGSK_CFGR_FRCONT_10M	0x40

#घोषणा RMON_T_DROP		0x200 /* Count of frames not cntd correctly */
#घोषणा RMON_T_PACKETS		0x204 /* RMON TX packet count */
#घोषणा RMON_T_BC_PKT		0x208 /* RMON TX broadcast pkts */
#घोषणा RMON_T_MC_PKT		0x20c /* RMON TX multicast pkts */
#घोषणा RMON_T_CRC_ALIGN	0x210 /* RMON TX pkts with CRC align err */
#घोषणा RMON_T_UNDERSIZE	0x214 /* RMON TX pkts < 64 bytes, good CRC */
#घोषणा RMON_T_OVERSIZE		0x218 /* RMON TX pkts > MAX_FL bytes good CRC */
#घोषणा RMON_T_FRAG		0x21c /* RMON TX pkts < 64 bytes, bad CRC */
#घोषणा RMON_T_JAB		0x220 /* RMON TX pkts > MAX_FL bytes, bad CRC */
#घोषणा RMON_T_COL		0x224 /* RMON TX collision count */
#घोषणा RMON_T_P64		0x228 /* RMON TX 64 byte pkts */
#घोषणा RMON_T_P65TO127		0x22c /* RMON TX 65 to 127 byte pkts */
#घोषणा RMON_T_P128TO255	0x230 /* RMON TX 128 to 255 byte pkts */
#घोषणा RMON_T_P256TO511	0x234 /* RMON TX 256 to 511 byte pkts */
#घोषणा RMON_T_P512TO1023	0x238 /* RMON TX 512 to 1023 byte pkts */
#घोषणा RMON_T_P1024TO2047	0x23c /* RMON TX 1024 to 2047 byte pkts */
#घोषणा RMON_T_P_GTE2048	0x240 /* RMON TX pkts > 2048 bytes */
#घोषणा RMON_T_OCTETS		0x244 /* RMON TX octets */
#घोषणा IEEE_T_DROP		0x248 /* Count of frames not counted crtly */
#घोषणा IEEE_T_FRAME_OK		0x24c /* Frames tx'd OK */
#घोषणा IEEE_T_1COL		0x250 /* Frames tx'd with single collision */
#घोषणा IEEE_T_MCOL		0x254 /* Frames tx'd with multiple collision */
#घोषणा IEEE_T_DEF		0x258 /* Frames tx'd after deferral delay */
#घोषणा IEEE_T_LCOL		0x25c /* Frames tx'd with late collision */
#घोषणा IEEE_T_EXCOL		0x260 /* Frames tx'd with excesv collisions */
#घोषणा IEEE_T_MACERR		0x264 /* Frames tx'd with TX FIFO underrun */
#घोषणा IEEE_T_CSERR		0x268 /* Frames tx'd with carrier sense err */
#घोषणा IEEE_T_SQE		0x26c /* Frames tx'd with SQE err */
#घोषणा IEEE_T_FDXFC		0x270 /* Flow control छोड़ो frames tx'd */
#घोषणा IEEE_T_OCTETS_OK	0x274 /* Octet count क्रम frames tx'd w/o err */
#घोषणा RMON_R_PACKETS		0x284 /* RMON RX packet count */
#घोषणा RMON_R_BC_PKT		0x288 /* RMON RX broadcast pkts */
#घोषणा RMON_R_MC_PKT		0x28c /* RMON RX multicast pkts */
#घोषणा RMON_R_CRC_ALIGN	0x290 /* RMON RX pkts with CRC alignment err */
#घोषणा RMON_R_UNDERSIZE	0x294 /* RMON RX pkts < 64 bytes, good CRC */
#घोषणा RMON_R_OVERSIZE		0x298 /* RMON RX pkts > MAX_FL bytes good CRC */
#घोषणा RMON_R_FRAG		0x29c /* RMON RX pkts < 64 bytes, bad CRC */
#घोषणा RMON_R_JAB		0x2a0 /* RMON RX pkts > MAX_FL bytes, bad CRC */
#घोषणा RMON_R_RESVD_O		0x2a4 /* Reserved */
#घोषणा RMON_R_P64		0x2a8 /* RMON RX 64 byte pkts */
#घोषणा RMON_R_P65TO127		0x2ac /* RMON RX 65 to 127 byte pkts */
#घोषणा RMON_R_P128TO255	0x2b0 /* RMON RX 128 to 255 byte pkts */
#घोषणा RMON_R_P256TO511	0x2b4 /* RMON RX 256 to 511 byte pkts */
#घोषणा RMON_R_P512TO1023	0x2b8 /* RMON RX 512 to 1023 byte pkts */
#घोषणा RMON_R_P1024TO2047	0x2bc /* RMON RX 1024 to 2047 byte pkts */
#घोषणा RMON_R_P_GTE2048	0x2c0 /* RMON RX pkts > 2048 bytes */
#घोषणा RMON_R_OCTETS		0x2c4 /* RMON RX octets */
#घोषणा IEEE_R_DROP		0x2c8 /* Count frames not counted correctly */
#घोषणा IEEE_R_FRAME_OK		0x2cc /* Frames rx'd OK */
#घोषणा IEEE_R_CRC		0x2d0 /* Frames rx'd with CRC err */
#घोषणा IEEE_R_ALIGN		0x2d4 /* Frames rx'd with alignment err */
#घोषणा IEEE_R_MACERR		0x2d8 /* Receive FIFO overflow count */
#घोषणा IEEE_R_FDXFC		0x2dc /* Flow control छोड़ो frames rx'd */
#घोषणा IEEE_R_OCTETS_OK	0x2e0 /* Octet cnt क्रम frames rx'd w/o err */

#अन्यथा

#घोषणा FEC_ECNTRL		0x000 /* Ethernet control reg */
#घोषणा FEC_IEVENT		0x004 /* Interrupt even reg */
#घोषणा FEC_IMASK		0x008 /* Interrupt mask reg */
#घोषणा FEC_IVEC		0x00c /* Interrupt vec status reg */
#घोषणा FEC_R_DES_ACTIVE_0	0x010 /* Receive descriptor reg */
#घोषणा FEC_R_DES_ACTIVE_1	FEC_R_DES_ACTIVE_0
#घोषणा FEC_R_DES_ACTIVE_2	FEC_R_DES_ACTIVE_0
#घोषणा FEC_X_DES_ACTIVE_0	0x014 /* Transmit descriptor reg */
#घोषणा FEC_X_DES_ACTIVE_1	FEC_X_DES_ACTIVE_0
#घोषणा FEC_X_DES_ACTIVE_2	FEC_X_DES_ACTIVE_0
#घोषणा FEC_MII_DATA		0x040 /* MII manage frame reg */
#घोषणा FEC_MII_SPEED		0x044 /* MII speed control reg */
#घोषणा FEC_R_BOUND		0x08c /* FIFO receive bound reg */
#घोषणा FEC_R_FSTART		0x090 /* FIFO receive start reg */
#घोषणा FEC_X_WMRK		0x0a4 /* FIFO transmit water mark */
#घोषणा FEC_X_FSTART		0x0ac /* FIFO transmit start reg */
#घोषणा FEC_R_CNTRL		0x104 /* Receive control reg */
#घोषणा FEC_MAX_FRM_LEN		0x108 /* Maximum frame length reg */
#घोषणा FEC_X_CNTRL		0x144 /* Transmit Control reg */
#घोषणा FEC_ADDR_LOW		0x3c0 /* Low 32bits MAC address */
#घोषणा FEC_ADDR_HIGH		0x3c4 /* High 16bits MAC address */
#घोषणा FEC_GRP_HASH_TABLE_HIGH	0x3c8 /* High 32bits hash table */
#घोषणा FEC_GRP_HASH_TABLE_LOW	0x3cc /* Low 32bits hash table */
#घोषणा FEC_R_DES_START_0	0x3d0 /* Receive descriptor ring */
#घोषणा FEC_R_DES_START_1	FEC_R_DES_START_0
#घोषणा FEC_R_DES_START_2	FEC_R_DES_START_0
#घोषणा FEC_X_DES_START_0	0x3d4 /* Transmit descriptor ring */
#घोषणा FEC_X_DES_START_1	FEC_X_DES_START_0
#घोषणा FEC_X_DES_START_2	FEC_X_DES_START_0
#घोषणा FEC_R_BUFF_SIZE_0	0x3d8 /* Maximum receive buff size */
#घोषणा FEC_R_BUFF_SIZE_1	FEC_R_BUFF_SIZE_0
#घोषणा FEC_R_BUFF_SIZE_2	FEC_R_BUFF_SIZE_0
#घोषणा FEC_FIFO_RAM		0x400 /* FIFO RAM buffer */
/* Not existed in real chip
 * Just क्रम pass build.
 */
#घोषणा FEC_RCMR_1		0xfff
#घोषणा FEC_RCMR_2		0xfff
#घोषणा FEC_DMA_CFG_1		0xfff
#घोषणा FEC_DMA_CFG_2		0xfff
#घोषणा FEC_TXIC0		0xfff
#घोषणा FEC_TXIC1		0xfff
#घोषणा FEC_TXIC2		0xfff
#घोषणा FEC_RXIC0		0xfff
#घोषणा FEC_RXIC1		0xfff
#घोषणा FEC_RXIC2		0xfff
#पूर्ण_अगर /* CONFIG_M5272 */


/*
 *	Define the buffer descriptor काष्ठाure.
 *
 *	Evidently, ARM SoCs have the FEC block generated in a
 *	little endian mode so adjust endianness accordingly.
 */
#अगर defined(CONFIG_ARM) || defined(CONFIG_ARM64)
#घोषणा fec32_to_cpu le32_to_cpu
#घोषणा fec16_to_cpu le16_to_cpu
#घोषणा cpu_to_fec32 cpu_to_le32
#घोषणा cpu_to_fec16 cpu_to_le16
#घोषणा __fec32 __le32
#घोषणा __fec16 __le16

काष्ठा bufdesc अणु
	__fec16 cbd_datlen;	/* Data length */
	__fec16 cbd_sc;		/* Control and status info */
	__fec32 cbd_bufaddr;	/* Buffer address */
पूर्ण;
#अन्यथा
#घोषणा fec32_to_cpu be32_to_cpu
#घोषणा fec16_to_cpu be16_to_cpu
#घोषणा cpu_to_fec32 cpu_to_be32
#घोषणा cpu_to_fec16 cpu_to_be16
#घोषणा __fec32 __be32
#घोषणा __fec16 __be16

काष्ठा bufdesc अणु
	__fec16	cbd_sc;		/* Control and status info */
	__fec16	cbd_datlen;	/* Data length */
	__fec32	cbd_bufaddr;	/* Buffer address */
पूर्ण;
#पूर्ण_अगर

काष्ठा bufdesc_ex अणु
	काष्ठा bufdesc desc;
	__fec32 cbd_esc;
	__fec32 cbd_prot;
	__fec32 cbd_bdu;
	__fec32 ts;
	__fec16 res0[4];
पूर्ण;

/*
 *	The following definitions courtesy of commproc.h, which where
 *	Copyright (c) 1997 Dan Malek (dmalek@jlc.net).
 */
#घोषणा BD_SC_EMPTY	((uलघु)0x8000)	/* Receive is empty */
#घोषणा BD_SC_READY	((uलघु)0x8000)	/* Transmit is पढ़ोy */
#घोषणा BD_SC_WRAP	((uलघु)0x2000)	/* Last buffer descriptor */
#घोषणा BD_SC_INTRPT	((uलघु)0x1000)	/* Interrupt on change */
#घोषणा BD_SC_CM	((uलघु)0x0200)	/* Continuous mode */
#घोषणा BD_SC_ID	((uलघु)0x0100)	/* Rec'd too many idles */
#घोषणा BD_SC_P		((uलघु)0x0100)	/* xmt preamble */
#घोषणा BD_SC_BR	((uलघु)0x0020)	/* Break received */
#घोषणा BD_SC_FR	((uलघु)0x0010)	/* Framing error */
#घोषणा BD_SC_PR	((uलघु)0x0008)	/* Parity error */
#घोषणा BD_SC_OV	((uलघु)0x0002)	/* Overrun */
#घोषणा BD_SC_CD	((uलघु)0x0001)	/* ?? */

/* Buffer descriptor control/status used by Ethernet receive.
 */
#घोषणा BD_ENET_RX_EMPTY	((uलघु)0x8000)
#घोषणा BD_ENET_RX_WRAP		((uलघु)0x2000)
#घोषणा BD_ENET_RX_INTR		((uलघु)0x1000)
#घोषणा BD_ENET_RX_LAST		((uलघु)0x0800)
#घोषणा BD_ENET_RX_FIRST	((uलघु)0x0400)
#घोषणा BD_ENET_RX_MISS		((uलघु)0x0100)
#घोषणा BD_ENET_RX_LG		((uलघु)0x0020)
#घोषणा BD_ENET_RX_NO		((uलघु)0x0010)
#घोषणा BD_ENET_RX_SH		((uलघु)0x0008)
#घोषणा BD_ENET_RX_CR		((uलघु)0x0004)
#घोषणा BD_ENET_RX_OV		((uलघु)0x0002)
#घोषणा BD_ENET_RX_CL		((uलघु)0x0001)
#घोषणा BD_ENET_RX_STATS	((uलघु)0x013f)	/* All status bits */

/* Enhanced buffer descriptor control/status used by Ethernet receive */
#घोषणा BD_ENET_RX_VLAN		0x00000004

/* Buffer descriptor control/status used by Ethernet transmit.
 */
#घोषणा BD_ENET_TX_READY	((uलघु)0x8000)
#घोषणा BD_ENET_TX_PAD		((uलघु)0x4000)
#घोषणा BD_ENET_TX_WRAP		((uलघु)0x2000)
#घोषणा BD_ENET_TX_INTR		((uलघु)0x1000)
#घोषणा BD_ENET_TX_LAST		((uलघु)0x0800)
#घोषणा BD_ENET_TX_TC		((uलघु)0x0400)
#घोषणा BD_ENET_TX_DEF		((uलघु)0x0200)
#घोषणा BD_ENET_TX_HB		((uलघु)0x0100)
#घोषणा BD_ENET_TX_LC		((uलघु)0x0080)
#घोषणा BD_ENET_TX_RL		((uलघु)0x0040)
#घोषणा BD_ENET_TX_RCMASK	((uलघु)0x003c)
#घोषणा BD_ENET_TX_UN		((uलघु)0x0002)
#घोषणा BD_ENET_TX_CSL		((uलघु)0x0001)
#घोषणा BD_ENET_TX_STATS	((uलघु)0x0fff)	/* All status bits */

/* enhanced buffer descriptor control/status used by Ethernet transmit */
#घोषणा BD_ENET_TX_INT		0x40000000
#घोषणा BD_ENET_TX_TS		0x20000000
#घोषणा BD_ENET_TX_PINS		0x10000000
#घोषणा BD_ENET_TX_IINS		0x08000000


/* This device has up to three irqs on some platक्रमms */
#घोषणा FEC_IRQ_NUM		3

/* Maximum number of queues supported
 * ENET with AVB IP can support up to 3 independent tx queues and rx queues.
 * User can poपूर्णांक the queue number that is less than or equal to 3.
 */
#घोषणा FEC_ENET_MAX_TX_QS	3
#घोषणा FEC_ENET_MAX_RX_QS	3

#घोषणा FEC_R_DES_START(X)	(((X) == 1) ? FEC_R_DES_START_1 : \
				(((X) == 2) ? \
					FEC_R_DES_START_2 : FEC_R_DES_START_0))
#घोषणा FEC_X_DES_START(X)	(((X) == 1) ? FEC_X_DES_START_1 : \
				(((X) == 2) ? \
					FEC_X_DES_START_2 : FEC_X_DES_START_0))
#घोषणा FEC_R_BUFF_SIZE(X)	(((X) == 1) ? FEC_R_BUFF_SIZE_1 : \
				(((X) == 2) ? \
					FEC_R_BUFF_SIZE_2 : FEC_R_BUFF_SIZE_0))

#घोषणा FEC_DMA_CFG(X)		(((X) == 2) ? FEC_DMA_CFG_2 : FEC_DMA_CFG_1)

#घोषणा DMA_CLASS_EN		(1 << 16)
#घोषणा FEC_RCMR(X)		(((X) == 2) ? FEC_RCMR_2 : FEC_RCMR_1)
#घोषणा IDLE_SLOPE_MASK		0xffff
#घोषणा IDLE_SLOPE_1		0x200 /* BW fraction: 0.5 */
#घोषणा IDLE_SLOPE_2		0x200 /* BW fraction: 0.5 */
#घोषणा IDLE_SLOPE(X)		(((X) == 1) ?				\
				(IDLE_SLOPE_1 & IDLE_SLOPE_MASK) :	\
				(IDLE_SLOPE_2 & IDLE_SLOPE_MASK))
#घोषणा RCMR_MATCHEN		(0x1 << 16)
#घोषणा RCMR_CMP_CFG(v, n)	(((v) & 0x7) <<  (n << 2))
#घोषणा RCMR_CMP_1		(RCMR_CMP_CFG(0, 0) | RCMR_CMP_CFG(1, 1) | \
				RCMR_CMP_CFG(2, 2) | RCMR_CMP_CFG(3, 3))
#घोषणा RCMR_CMP_2		(RCMR_CMP_CFG(4, 0) | RCMR_CMP_CFG(5, 1) | \
				RCMR_CMP_CFG(6, 2) | RCMR_CMP_CFG(7, 3))
#घोषणा RCMR_CMP(X)		(((X) == 1) ? RCMR_CMP_1 : RCMR_CMP_2)
#घोषणा FEC_TX_BD_FTYPE(X)	(((X) & 0xf) << 20)

/* The number of Tx and Rx buffers.  These are allocated from the page
 * pool.  The code may assume these are घातer of two, so it it best
 * to keep them that size.
 * We करोn't need to allocate pages क्रम the transmitter.  We just use
 * the skbuffer directly.
 */

#घोषणा FEC_ENET_RX_PAGES	256
#घोषणा FEC_ENET_RX_FRSIZE	2048
#घोषणा FEC_ENET_RX_FRPPG	(PAGE_SIZE / FEC_ENET_RX_FRSIZE)
#घोषणा RX_RING_SIZE		(FEC_ENET_RX_FRPPG * FEC_ENET_RX_PAGES)
#घोषणा FEC_ENET_TX_FRSIZE	2048
#घोषणा FEC_ENET_TX_FRPPG	(PAGE_SIZE / FEC_ENET_TX_FRSIZE)
#घोषणा TX_RING_SIZE		512	/* Must be घातer of two */
#घोषणा TX_RING_MOD_MASK	511	/*   क्रम this to work */

#घोषणा BD_ENET_RX_INT		0x00800000
#घोषणा BD_ENET_RX_PTP		((uलघु)0x0400)
#घोषणा BD_ENET_RX_ICE		0x00000020
#घोषणा BD_ENET_RX_PCR		0x00000010
#घोषणा FLAG_RX_CSUM_ENABLED	(BD_ENET_RX_ICE | BD_ENET_RX_PCR)
#घोषणा FLAG_RX_CSUM_ERROR	(BD_ENET_RX_ICE | BD_ENET_RX_PCR)

/* Interrupt events/masks. */
#घोषणा FEC_ENET_HBERR  ((uपूर्णांक)0x80000000)      /* Heartbeat error */
#घोषणा FEC_ENET_BABR   ((uपूर्णांक)0x40000000)      /* Babbling receiver */
#घोषणा FEC_ENET_BABT   ((uपूर्णांक)0x20000000)      /* Babbling transmitter */
#घोषणा FEC_ENET_GRA    ((uपूर्णांक)0x10000000)      /* Graceful stop complete */
#घोषणा FEC_ENET_TXF_0	((uपूर्णांक)0x08000000)	/* Full frame transmitted */
#घोषणा FEC_ENET_TXF_1	((uपूर्णांक)0x00000008)	/* Full frame transmitted */
#घोषणा FEC_ENET_TXF_2	((uपूर्णांक)0x00000080)	/* Full frame transmitted */
#घोषणा FEC_ENET_TXB    ((uपूर्णांक)0x04000000)      /* A buffer was transmitted */
#घोषणा FEC_ENET_RXF_0	((uपूर्णांक)0x02000000)	/* Full frame received */
#घोषणा FEC_ENET_RXF_1	((uपूर्णांक)0x00000002)	/* Full frame received */
#घोषणा FEC_ENET_RXF_2	((uपूर्णांक)0x00000020)	/* Full frame received */
#घोषणा FEC_ENET_RXB    ((uपूर्णांक)0x01000000)      /* A buffer was received */
#घोषणा FEC_ENET_MII    ((uपूर्णांक)0x00800000)      /* MII पूर्णांकerrupt */
#घोषणा FEC_ENET_EBERR  ((uपूर्णांक)0x00400000)      /* SDMA bus error */
#घोषणा FEC_ENET_WAKEUP	((uपूर्णांक)0x00020000)	/* Wakeup request */
#घोषणा FEC_ENET_TXF	(FEC_ENET_TXF_0 | FEC_ENET_TXF_1 | FEC_ENET_TXF_2)
#घोषणा FEC_ENET_RXF	(FEC_ENET_RXF_0 | FEC_ENET_RXF_1 | FEC_ENET_RXF_2)
#घोषणा FEC_ENET_TS_AVAIL       ((uपूर्णांक)0x00010000)
#घोषणा FEC_ENET_TS_TIMER       ((uपूर्णांक)0x00008000)

#घोषणा FEC_DEFAULT_IMASK (FEC_ENET_TXF | FEC_ENET_RXF)
#घोषणा FEC_RX_DISABLED_IMASK (FEC_DEFAULT_IMASK & (~FEC_ENET_RXF))

/* ENET पूर्णांकerrupt coalescing macro define */
#घोषणा FEC_ITR_CLK_SEL		(0x1 << 30)
#घोषणा FEC_ITR_EN		(0x1 << 31)
#घोषणा FEC_ITR_ICFT(X)		(((X) & 0xff) << 20)
#घोषणा FEC_ITR_ICTT(X)		((X) & 0xffff)
#घोषणा FEC_ITR_ICFT_DEFAULT	200  /* Set 200 frame count threshold */
#घोषणा FEC_ITR_ICTT_DEFAULT	1000 /* Set 1000us समयr threshold */

#घोषणा FEC_VLAN_TAG_LEN	0x04
#घोषणा FEC_ETHTYPE_LEN		0x02

/* Controller is ENET-MAC */
#घोषणा FEC_QUIRK_ENET_MAC		(1 << 0)
/* Controller needs driver to swap frame */
#घोषणा FEC_QUIRK_SWAP_FRAME		(1 << 1)
/* Controller uses gasket */
#घोषणा FEC_QUIRK_USE_GASKET		(1 << 2)
/* Controller has GBIT support */
#घोषणा FEC_QUIRK_HAS_GBIT		(1 << 3)
/* Controller has extend desc buffer */
#घोषणा FEC_QUIRK_HAS_BUFDESC_EX	(1 << 4)
/* Controller has hardware checksum support */
#घोषणा FEC_QUIRK_HAS_CSUM		(1 << 5)
/* Controller has hardware vlan support */
#घोषणा FEC_QUIRK_HAS_VLAN		(1 << 6)
/* ENET IP errata ERR006358
 *
 * If the पढ़ोy bit in the transmit buffer descriptor (TxBD[R]) is previously
 * detected as not set during a prior frame transmission, then the
 * ENET_TDAR[TDAR] bit is cleared at a later समय, even अगर additional TxBDs
 * were added to the ring and the ENET_TDAR[TDAR] bit is set. This results in
 * frames not being transmitted until there is a 0-to-1 transition on
 * ENET_TDAR[TDAR].
 */
#घोषणा FEC_QUIRK_ERR006358		(1 << 7)
/* ENET IP hw AVB
 *
 * i.MX6SX ENET IP add Audio Video Bridging (AVB) feature support.
 * - Two class indicators on receive with configurable priority
 * - Two class indicators and line speed समयr on transmit allowing
 *   implementation class credit based shapers बाह्यally
 * - Additional DMA रेजिस्टरs provisioned to allow managing up to 3
 *   independent rings
 */
#घोषणा FEC_QUIRK_HAS_AVB		(1 << 8)
/* There is a TDAR race condition क्रम mutliQ when the software sets TDAR
 * and the UDMA clears TDAR simultaneously or in a small winकरोw (2-4 cycles).
 * This will cause the udma_tx and udma_tx_arbiter state machines to hang.
 * The issue exist at i.MX6SX enet IP.
 */
#घोषणा FEC_QUIRK_ERR007885		(1 << 9)
/* ENET Block Guide/ Chapter क्रम the iMX6SX (PELE) address one issue:
 * After set ENET_ATCR[Capture], there need some समय cycles beक्रमe the counter
 * value is capture in the रेजिस्टर घड़ी करोमुख्य.
 * The रुको-समय-cycles is at least 6 घड़ी cycles of the slower घड़ी between
 * the रेजिस्टर घड़ी and the 1588 घड़ी. The 1588 ts_clk is fixed to 25Mhz,
 * रेजिस्टर घड़ी is 66Mhz, so the रुको-समय-cycles must be greater than 240ns
 * (40ns * 6).
 */
#घोषणा FEC_QUIRK_BUG_CAPTURE		(1 << 10)
/* Controller has only one MDIO bus */
#घोषणा FEC_QUIRK_SINGLE_MDIO		(1 << 11)
/* Controller supports RACC रेजिस्टर */
#घोषणा FEC_QUIRK_HAS_RACC		(1 << 12)
/* Controller supports पूर्णांकerrupt coalesc */
#घोषणा FEC_QUIRK_HAS_COALESCE		(1 << 13)
/* Interrupt करोesn't wake CPU from deep idle */
#घोषणा FEC_QUIRK_ERR006687		(1 << 14)
/* The MIB counters should be cleared and enabled during
 * initialisation.
 */
#घोषणा FEC_QUIRK_MIB_CLEAR		(1 << 15)
/* Only i.MX25/i.MX27/i.MX28 controller supports FRBR,FRSR रेजिस्टरs,
 * those FIFO receive रेजिस्टरs are resolved in other platक्रमms.
 */
#घोषणा FEC_QUIRK_HAS_FRREG		(1 << 16)

/* Some FEC hardware blocks need the MMFR cleared at setup समय to aव्योम
 * the generation of an MII event. This must be aव्योमed in the older
 * FEC blocks where it will stop MII events being generated.
 */
#घोषणा FEC_QUIRK_CLEAR_SETUP_MII	(1 << 17)

/* Some link partners करो not tolerate the momentary reset of the REF_CLK
 * frequency when the RNCTL रेजिस्टर is cleared by hardware reset.
 */
#घोषणा FEC_QUIRK_NO_HARD_RESET		(1 << 18)

काष्ठा bufdesc_prop अणु
	पूर्णांक qid;
	/* Address of Rx and Tx buffers */
	काष्ठा bufdesc	*base;
	काष्ठा bufdesc	*last;
	काष्ठा bufdesc	*cur;
	व्योम __iomem	*reg_desc_active;
	dma_addr_t	dma;
	अचिन्हित लघु ring_size;
	अचिन्हित अक्षर dsize;
	अचिन्हित अक्षर dsize_log2;
पूर्ण;

काष्ठा fec_enet_priv_tx_q अणु
	काष्ठा bufdesc_prop bd;
	अचिन्हित अक्षर *tx_bounce[TX_RING_SIZE];
	काष्ठा  sk_buff *tx_skbuff[TX_RING_SIZE];

	अचिन्हित लघु tx_stop_threshold;
	अचिन्हित लघु tx_wake_threshold;

	काष्ठा bufdesc	*dirty_tx;
	अक्षर *tso_hdrs;
	dma_addr_t tso_hdrs_dma;
पूर्ण;

काष्ठा fec_enet_priv_rx_q अणु
	काष्ठा bufdesc_prop bd;
	काष्ठा  sk_buff *rx_skbuff[RX_RING_SIZE];
पूर्ण;

काष्ठा fec_stop_mode_gpr अणु
	काष्ठा regmap *gpr;
	u8 reg;
	u8 bit;
पूर्ण;

/* The FEC buffer descriptors track the ring buffers.  The rx_bd_base and
 * tx_bd_base always poपूर्णांक to the base of the buffer descriptors.  The
 * cur_rx and cur_tx poपूर्णांक to the currently available buffer.
 * The dirty_tx tracks the current buffer that is being sent by the
 * controller.  The cur_tx and dirty_tx are equal under both completely
 * empty and completely full conditions.  The empty/पढ़ोy indicator in
 * the buffer descriptor determines the actual condition.
 */
काष्ठा fec_enet_निजी अणु
	/* Hardware रेजिस्टरs of the FEC device */
	व्योम __iomem *hwp;

	काष्ठा net_device *netdev;

	काष्ठा clk *clk_ipg;
	काष्ठा clk *clk_ahb;
	काष्ठा clk *clk_ref;
	काष्ठा clk *clk_enet_out;
	काष्ठा clk *clk_ptp;

	bool ptp_clk_on;
	काष्ठा mutex ptp_clk_mutex;
	अचिन्हित पूर्णांक num_tx_queues;
	अचिन्हित पूर्णांक num_rx_queues;

	/* The saved address of a sent-in-place packet/buffer, क्रम skमुक्त(). */
	काष्ठा fec_enet_priv_tx_q *tx_queue[FEC_ENET_MAX_TX_QS];
	काष्ठा fec_enet_priv_rx_q *rx_queue[FEC_ENET_MAX_RX_QS];

	अचिन्हित पूर्णांक total_tx_ring_size;
	अचिन्हित पूर्णांक total_rx_ring_size;

	काष्ठा	platक्रमm_device *pdev;

	पूर्णांक	dev_id;

	/* Phylib and MDIO पूर्णांकerface */
	काष्ठा	mii_bus *mii_bus;
	uपूर्णांक	phy_speed;
	phy_पूर्णांकerface_t	phy_पूर्णांकerface;
	काष्ठा device_node *phy_node;
	पूर्णांक	link;
	पूर्णांक	full_duplex;
	पूर्णांक	speed;
	पूर्णांक	irq[FEC_IRQ_NUM];
	bool	bufdesc_ex;
	पूर्णांक	छोड़ो_flag;
	पूर्णांक	wol_flag;
	u32	quirks;

	काष्ठा	napi_काष्ठा napi;
	पूर्णांक	csum_flags;

	काष्ठा work_काष्ठा tx_समयout_work;

	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_caps;
	अचिन्हित दीर्घ last_overflow_check;
	spinlock_t पंचांगreg_lock;
	काष्ठा cyclecounter cc;
	काष्ठा समयcounter tc;
	पूर्णांक rx_hwtstamp_filter;
	u32 base_incval;
	u32 cycle_speed;
	पूर्णांक hwts_rx_en;
	पूर्णांक hwts_tx_en;
	काष्ठा delayed_work समय_keep;
	काष्ठा regulator *reg_phy;
	काष्ठा fec_stop_mode_gpr stop_gpr;

	अचिन्हित पूर्णांक tx_align;
	अचिन्हित पूर्णांक rx_align;

	/* hw पूर्णांकerrupt coalesce */
	अचिन्हित पूर्णांक rx_pkts_itr;
	अचिन्हित पूर्णांक rx_समय_itr;
	अचिन्हित पूर्णांक tx_pkts_itr;
	अचिन्हित पूर्णांक tx_समय_itr;
	अचिन्हित पूर्णांक itr_clk_rate;

	u32 rx_copyअवरोध;

	/* ptp घड़ी period in ns*/
	अचिन्हित पूर्णांक ptp_inc;

	/* pps  */
	पूर्णांक pps_channel;
	अचिन्हित पूर्णांक reload_period;
	पूर्णांक pps_enable;
	अचिन्हित पूर्णांक next_counter;

	u64 ethtool_stats[];
पूर्ण;

व्योम fec_ptp_init(काष्ठा platक्रमm_device *pdev, पूर्णांक irq_idx);
व्योम fec_ptp_stop(काष्ठा platक्रमm_device *pdev);
व्योम fec_ptp_start_cyclecounter(काष्ठा net_device *ndev);
व्योम fec_ptp_disable_hwts(काष्ठा net_device *ndev);
पूर्णांक fec_ptp_set(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरr);
पूर्णांक fec_ptp_get(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरr);

/****************************************************************************/
#पूर्ण_अगर /* FEC_H */
