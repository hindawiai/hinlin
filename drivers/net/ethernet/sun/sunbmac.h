<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Id: sunbmac.h,v 1.7 2000/07/11 22:35:22 davem Exp $
 * sunbmac.h: Defines क्रम the Sun "Big MAC" 100baseT ethernet cards.
 *
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SUNBMAC_H
#घोषणा _SUNBMAC_H

/* QEC global रेजिस्टरs. */
#घोषणा GLOB_CTRL	0x00UL	/* Control                  */
#घोषणा GLOB_STAT	0x04UL	/* Status                   */
#घोषणा GLOB_PSIZE	0x08UL	/* Packet Size              */
#घोषणा GLOB_MSIZE	0x0cUL	/* Local-mem size (64K)     */
#घोषणा GLOB_RSIZE	0x10UL	/* Receive partition size   */
#घोषणा GLOB_TSIZE	0x14UL	/* Transmit partition size  */
#घोषणा GLOB_REG_SIZE	0x18UL

#घोषणा GLOB_CTRL_MMODE       0x40000000 /* MACE qec mode            */
#घोषणा GLOB_CTRL_BMODE       0x10000000 /* BigMAC qec mode          */
#घोषणा GLOB_CTRL_EPAR        0x00000020 /* Enable parity            */
#घोषणा GLOB_CTRL_ACNTRL      0x00000018 /* SBUS arbitration control */
#घोषणा GLOB_CTRL_B64         0x00000004 /* 64 byte dvma bursts      */
#घोषणा GLOB_CTRL_B32         0x00000002 /* 32 byte dvma bursts      */
#घोषणा GLOB_CTRL_B16         0x00000000 /* 16 byte dvma bursts      */
#घोषणा GLOB_CTRL_RESET       0x00000001 /* Reset the QEC            */

#घोषणा GLOB_STAT_TX          0x00000008 /* BigMAC Transmit IRQ      */
#घोषणा GLOB_STAT_RX          0x00000004 /* BigMAC Receive IRQ       */
#घोषणा GLOB_STAT_BM          0x00000002 /* BigMAC Global IRQ        */
#घोषणा GLOB_STAT_ER          0x00000001 /* BigMAC Error IRQ         */

#घोषणा GLOB_PSIZE_2048       0x00       /* 2k packet size           */
#घोषणा GLOB_PSIZE_4096       0x01       /* 4k packet size           */
#घोषणा GLOB_PSIZE_6144       0x10       /* 6k packet size           */
#घोषणा GLOB_PSIZE_8192       0x11       /* 8k packet size           */

/* QEC BigMAC channel रेजिस्टरs. */
#घोषणा CREG_CTRL	0x00UL	/* Control                   */
#घोषणा CREG_STAT	0x04UL	/* Status                    */
#घोषणा CREG_RXDS	0x08UL	/* RX descriptor ring ptr    */
#घोषणा CREG_TXDS	0x0cUL	/* TX descriptor ring ptr    */
#घोषणा CREG_RIMASK	0x10UL	/* RX Interrupt Mask         */
#घोषणा CREG_TIMASK	0x14UL	/* TX Interrupt Mask         */
#घोषणा CREG_QMASK	0x18UL	/* QEC Error Interrupt Mask  */
#घोषणा CREG_BMASK	0x1cUL	/* BigMAC Error Interrupt Mask*/
#घोषणा CREG_RXWBUFPTR	0x20UL	/* Local memory rx ग_लिखो ptr */
#घोषणा CREG_RXRBUFPTR	0x24UL	/* Local memory rx पढ़ो ptr  */
#घोषणा CREG_TXWBUFPTR	0x28UL	/* Local memory tx ग_लिखो ptr */
#घोषणा CREG_TXRBUFPTR	0x2cUL	/* Local memory tx पढ़ो ptr  */
#घोषणा CREG_CCNT	0x30UL	/* Collision Counter         */
#घोषणा CREG_REG_SIZE	0x34UL

#घोषणा CREG_CTRL_TWAKEUP     0x00000001  /* Transmitter Wakeup, 'go'. */

#घोषणा CREG_STAT_BERROR      0x80000000  /* BigMAC error              */
#घोषणा CREG_STAT_TXIRQ       0x00200000  /* Transmit Interrupt        */
#घोषणा CREG_STAT_TXDERROR    0x00080000  /* TX Descriptor is bogus    */
#घोषणा CREG_STAT_TXLERR      0x00040000  /* Late Transmit Error       */
#घोषणा CREG_STAT_TXPERR      0x00020000  /* Transmit Parity Error     */
#घोषणा CREG_STAT_TXSERR      0x00010000  /* Transmit SBUS error ack   */
#घोषणा CREG_STAT_RXIRQ       0x00000020  /* Receive Interrupt         */
#घोषणा CREG_STAT_RXDROP      0x00000010  /* Dropped a RX'd packet     */
#घोषणा CREG_STAT_RXSMALL     0x00000008  /* Receive buffer too small  */
#घोषणा CREG_STAT_RXLERR      0x00000004  /* Receive Late Error        */
#घोषणा CREG_STAT_RXPERR      0x00000002  /* Receive Parity Error      */
#घोषणा CREG_STAT_RXSERR      0x00000001  /* Receive SBUS Error ACK    */

#घोषणा CREG_STAT_ERRORS      (CREG_STAT_BERROR|CREG_STAT_TXDERROR|CREG_STAT_TXLERR|   \
                               CREG_STAT_TXPERR|CREG_STAT_TXSERR|CREG_STAT_RXDROP|     \
                               CREG_STAT_RXSMALL|CREG_STAT_RXLERR|CREG_STAT_RXPERR|    \
                               CREG_STAT_RXSERR)

#घोषणा CREG_QMASK_TXDERROR   0x00080000  /* TXD error                 */
#घोषणा CREG_QMASK_TXLERR     0x00040000  /* TX late error             */
#घोषणा CREG_QMASK_TXPERR     0x00020000  /* TX parity error           */
#घोषणा CREG_QMASK_TXSERR     0x00010000  /* TX sbus error ack         */
#घोषणा CREG_QMASK_RXDROP     0x00000010  /* RX drop                   */
#घोषणा CREG_QMASK_RXBERROR   0x00000008  /* RX buffer error           */
#घोषणा CREG_QMASK_RXLEERR    0x00000004  /* RX late error             */
#घोषणा CREG_QMASK_RXPERR     0x00000002  /* RX parity error           */
#घोषणा CREG_QMASK_RXSERR     0x00000001  /* RX sbus error ack         */

/* BIGMAC core रेजिस्टरs */
#घोषणा BMAC_XIFCFG	0x000UL	/* XIF config रेजिस्टर                */
	/* 0x004-->0x0fc, reserved */
#घोषणा BMAC_STATUS	0x100UL	/* Status रेजिस्टर, clear on पढ़ो     */
#घोषणा BMAC_IMASK	0x104UL	/* Interrupt mask रेजिस्टर            */
	/* 0x108-->0x204, reserved */
#घोषणा BMAC_TXSWRESET	0x208UL	/* Transmitter software reset         */
#घोषणा BMAC_TXCFG	0x20cUL	/* Transmitter config रेजिस्टर        */
#घोषणा BMAC_IGAP1	0x210UL	/* Inter-packet gap 1                 */
#घोषणा BMAC_IGAP2	0x214UL	/* Inter-packet gap 2                 */
#घोषणा BMAC_ALIMIT	0x218UL	/* Transmit attempt limit             */
#घोषणा BMAC_STIME	0x21cUL	/* Transmit slot समय                 */
#घोषणा BMAC_PLEN	0x220UL	/* Size of transmit preamble          */
#घोषणा BMAC_PPAT	0x224UL	/* Pattern क्रम transmit preamble      */
#घोषणा BMAC_TXDELIM	0x228UL	/* Transmit delimiter                 */
#घोषणा BMAC_JSIZE	0x22cUL	/* Toe jam...                         */
#घोषणा BMAC_TXPMAX	0x230UL	/* Transmit max pkt size              */
#घोषणा BMAC_TXPMIN	0x234UL	/* Transmit min pkt size              */
#घोषणा BMAC_PATTEMPT	0x238UL	/* Count of transmit peak attempts    */
#घोषणा BMAC_DTCTR	0x23cUL	/* Transmit defer समयr               */
#घोषणा BMAC_NCCTR	0x240UL	/* Transmit normal-collision counter  */
#घोषणा BMAC_FCCTR	0x244UL	/* Transmit first-collision counter   */
#घोषणा BMAC_EXCTR	0x248UL	/* Transmit excess-collision counter  */
#घोषणा BMAC_LTCTR	0x24cUL	/* Transmit late-collision counter    */
#घोषणा BMAC_RSEED	0x250UL	/* Transmit अक्रमom number seed        */
#घोषणा BMAC_TXSMACHINE	0x254UL /* Transmit state machine             */
	/* 0x258-->0x304, reserved */
#घोषणा BMAC_RXSWRESET	0x308UL	/* Receiver software reset            */
#घोषणा BMAC_RXCFG	0x30cUL	/* Receiver config रेजिस्टर           */
#घोषणा BMAC_RXPMAX	0x310UL	/* Receive max pkt size               */
#घोषणा BMAC_RXPMIN	0x314UL	/* Receive min pkt size               */
#घोषणा BMAC_MACADDR2	0x318UL	/* Ether address रेजिस्टर 2           */
#घोषणा BMAC_MACADDR1	0x31cUL	/* Ether address रेजिस्टर 1           */
#घोषणा BMAC_MACADDR0	0x320UL	/* Ether address रेजिस्टर 0           */
#घोषणा BMAC_FRCTR	0x324UL	/* Receive frame receive counter      */
#घोषणा BMAC_GLECTR	0x328UL	/* Receive giant-length error counter */
#घोषणा BMAC_UNALECTR	0x32cUL	/* Receive unaligned error counter    */
#घोषणा BMAC_RCRCECTR	0x330UL	/* Receive CRC error counter          */
#घोषणा BMAC_RXSMACHINE	0x334UL	/* Receiver state machine             */
#घोषणा BMAC_RXCVALID	0x338UL	/* Receiver code violation            */
	/* 0x33c, reserved */
#घोषणा BMAC_HTABLE3	0x340UL	/* Hash table 3                       */
#घोषणा BMAC_HTABLE2	0x344UL	/* Hash table 2                       */
#घोषणा BMAC_HTABLE1	0x348UL	/* Hash table 1                       */
#घोषणा BMAC_HTABLE0	0x34cUL	/* Hash table 0                       */
#घोषणा BMAC_AFILTER2	0x350UL	/* Address filter 2                   */
#घोषणा BMAC_AFILTER1	0x354UL	/* Address filter 1                   */
#घोषणा BMAC_AFILTER0	0x358UL	/* Address filter 0                   */
#घोषणा BMAC_AFMASK	0x35cUL	/* Address filter mask                */
#घोषणा BMAC_REG_SIZE	0x360UL

/* BigMac XIF config रेजिस्टर. */
#घोषणा BIGMAC_XCFG_ODENABLE   0x00000001 /* Output driver enable                     */
#घोषणा BIGMAC_XCFG_RESV       0x00000002 /* Reserved, ग_लिखो always as 1              */
#घोषणा BIGMAC_XCFG_MLBACK     0x00000004 /* Loopback-mode MII enable                 */
#घोषणा BIGMAC_XCFG_SMODE      0x00000008 /* Enable serial mode                       */

/* BigMAC status रेजिस्टर. */
#घोषणा BIGMAC_STAT_GOTFRAME   0x00000001 /* Received a frame                         */
#घोषणा BIGMAC_STAT_RCNTEXP    0x00000002 /* Receive frame counter expired            */
#घोषणा BIGMAC_STAT_ACNTEXP    0x00000004 /* Align-error counter expired              */
#घोषणा BIGMAC_STAT_CCNTEXP    0x00000008 /* CRC-error counter expired                */
#घोषणा BIGMAC_STAT_LCNTEXP    0x00000010 /* Length-error counter expired             */
#घोषणा BIGMAC_STAT_RFIFOVF    0x00000020 /* Receive FIFO overflow                    */
#घोषणा BIGMAC_STAT_CVCNTEXP   0x00000040 /* Code-violation counter expired           */
#घोषणा BIGMAC_STAT_SENTFRAME  0x00000100 /* Transmitted a frame                      */
#घोषणा BIGMAC_STAT_TFIFO_UND  0x00000200 /* Transmit FIFO underrun                   */
#घोषणा BIGMAC_STAT_MAXPKTERR  0x00000400 /* Max-packet size error                    */
#घोषणा BIGMAC_STAT_NCNTEXP    0x00000800 /* Normal-collision counter expired         */
#घोषणा BIGMAC_STAT_ECNTEXP    0x00001000 /* Excess-collision counter expired         */
#घोषणा BIGMAC_STAT_LCCNTEXP   0x00002000 /* Late-collision counter expired           */
#घोषणा BIGMAC_STAT_FCNTEXP    0x00004000 /* First-collision counter expired          */
#घोषणा BIGMAC_STAT_DTIMEXP    0x00008000 /* Defer-समयr expired                      */

/* BigMAC पूर्णांकerrupt mask रेजिस्टर. */
#घोषणा BIGMAC_IMASK_GOTFRAME  0x00000001 /* Received a frame                         */
#घोषणा BIGMAC_IMASK_RCNTEXP   0x00000002 /* Receive frame counter expired            */
#घोषणा BIGMAC_IMASK_ACNTEXP   0x00000004 /* Align-error counter expired              */
#घोषणा BIGMAC_IMASK_CCNTEXP   0x00000008 /* CRC-error counter expired                */
#घोषणा BIGMAC_IMASK_LCNTEXP   0x00000010 /* Length-error counter expired             */
#घोषणा BIGMAC_IMASK_RFIFOVF   0x00000020 /* Receive FIFO overflow                    */
#घोषणा BIGMAC_IMASK_CVCNTEXP  0x00000040 /* Code-violation counter expired           */
#घोषणा BIGMAC_IMASK_SENTFRAME 0x00000100 /* Transmitted a frame                      */
#घोषणा BIGMAC_IMASK_TFIFO_UND 0x00000200 /* Transmit FIFO underrun                   */
#घोषणा BIGMAC_IMASK_MAXPKTERR 0x00000400 /* Max-packet size error                    */
#घोषणा BIGMAC_IMASK_NCNTEXP   0x00000800 /* Normal-collision counter expired         */
#घोषणा BIGMAC_IMASK_ECNTEXP   0x00001000 /* Excess-collision counter expired         */
#घोषणा BIGMAC_IMASK_LCCNTEXP  0x00002000 /* Late-collision counter expired           */
#घोषणा BIGMAC_IMASK_FCNTEXP   0x00004000 /* First-collision counter expired          */
#घोषणा BIGMAC_IMASK_DTIMEXP   0x00008000 /* Defer-समयr expired                      */

/* BigMac transmit config रेजिस्टर. */
#घोषणा BIGMAC_TXCFG_ENABLE    0x00000001 /* Enable the transmitter                   */
#घोषणा BIGMAC_TXCFG_FIFO      0x00000010 /* Default tx fthresh...                    */
#घोषणा BIGMAC_TXCFG_SMODE     0x00000020 /* Enable slow transmit mode                */
#घोषणा BIGMAC_TXCFG_CIGN      0x00000040 /* Ignore transmit collisions               */
#घोषणा BIGMAC_TXCFG_FCSOFF    0x00000080 /* Do not emit FCS                          */
#घोषणा BIGMAC_TXCFG_DBACKOFF  0x00000100 /* Disable backoff                          */
#घोषणा BIGMAC_TXCFG_FULLDPLX  0x00000200 /* Enable full-duplex                       */

/* BigMac receive config रेजिस्टर. */
#घोषणा BIGMAC_RXCFG_ENABLE    0x00000001 /* Enable the receiver                      */
#घोषणा BIGMAC_RXCFG_FIFO      0x0000000e /* Default rx fthresh...                    */
#घोषणा BIGMAC_RXCFG_PSTRIP    0x00000020 /* Pad byte strip enable                    */
#घोषणा BIGMAC_RXCFG_PMISC     0x00000040 /* Enable promiscuous mode                   */
#घोषणा BIGMAC_RXCFG_DERR      0x00000080 /* Disable error checking                   */
#घोषणा BIGMAC_RXCFG_DCRCS     0x00000100 /* Disable CRC stripping                    */
#घोषणा BIGMAC_RXCFG_ME        0x00000200 /* Receive packets addressed to me          */
#घोषणा BIGMAC_RXCFG_PGRP      0x00000400 /* Enable promisc group mode                */
#घोषणा BIGMAC_RXCFG_HENABLE   0x00000800 /* Enable the hash filter                   */
#घोषणा BIGMAC_RXCFG_AENABLE   0x00001000 /* Enable the address filter                */

/* The BigMAC PHY transceiver.  Not nearly as sophisticated as the happy meal
 * one.  But it करोes have the "bit banger", oh baby.
 */
#घोषणा TCVR_TPAL	0x00UL
#घोषणा TCVR_MPAL	0x04UL
#घोषणा TCVR_REG_SIZE	0x08UL

/* Frame commands. */
#घोषणा FRAME_WRITE           0x50020000
#घोषणा FRAME_READ            0x60020000

/* Tranceiver रेजिस्टरs. */
#घोषणा TCVR_PAL_SERIAL       0x00000001 /* Enable serial mode              */
#घोषणा TCVR_PAL_EXTLBACK     0x00000002 /* Enable बाह्यal loopback        */
#घोषणा TCVR_PAL_MSENSE       0x00000004 /* Media sense                     */
#घोषणा TCVR_PAL_LTENABLE     0x00000008 /* Link test enable                */
#घोषणा TCVR_PAL_LTSTATUS     0x00000010 /* Link test status  (P1 only)     */

/* Management PAL. */
#घोषणा MGMT_PAL_DCLOCK       0x00000001 /* Data घड़ी                      */
#घोषणा MGMT_PAL_OENAB        0x00000002 /* Output enabler                  */
#घोषणा MGMT_PAL_MDIO         0x00000004 /* MDIO Data/attached              */
#घोषणा MGMT_PAL_TIMEO        0x00000008 /* Transmit enable समयout error   */
#घोषणा MGMT_PAL_EXT_MDIO     MGMT_PAL_MDIO
#घोषणा MGMT_PAL_INT_MDIO     MGMT_PAL_TIMEO

/* Here are some PHY addresses. */
#घोषणा BIGMAC_PHY_EXTERNAL   0 /* External transceiver */
#घोषणा BIGMAC_PHY_INTERNAL   1 /* Internal transceiver */

/* Ring descriptors and such, same as Quad Ethernet. */
काष्ठा be_rxd अणु
	u32 rx_flags;
	u32 rx_addr;
पूर्ण;

#घोषणा RXD_OWN      0x80000000 /* Ownership.      */
#घोषणा RXD_UPDATE   0x10000000 /* Being Updated?  */
#घोषणा RXD_LENGTH   0x000007ff /* Packet Length.  */

काष्ठा be_txd अणु
	u32 tx_flags;
	u32 tx_addr;
पूर्ण;

#घोषणा TXD_OWN      0x80000000 /* Ownership.      */
#घोषणा TXD_SOP      0x40000000 /* Start Of Packet */
#घोषणा TXD_EOP      0x20000000 /* End Of Packet   */
#घोषणा TXD_UPDATE   0x10000000 /* Being Updated?  */
#घोषणा TXD_LENGTH   0x000007ff /* Packet Length.  */

#घोषणा TX_RING_MAXSIZE   256
#घोषणा RX_RING_MAXSIZE   256

#घोषणा TX_RING_SIZE      256
#घोषणा RX_RING_SIZE      256

#घोषणा NEXT_RX(num)       (((num) + 1) & (RX_RING_SIZE - 1))
#घोषणा NEXT_TX(num)       (((num) + 1) & (TX_RING_SIZE - 1))
#घोषणा PREV_RX(num)       (((num) - 1) & (RX_RING_SIZE - 1))
#घोषणा PREV_TX(num)       (((num) - 1) & (TX_RING_SIZE - 1))

#घोषणा TX_BUFFS_AVAIL(bp)                                    \
        (((bp)->tx_old <= (bp)->tx_new) ?                     \
	  (bp)->tx_old + (TX_RING_SIZE - 1) - (bp)->tx_new :  \
			    (bp)->tx_old - (bp)->tx_new - 1)


#घोषणा RX_COPY_THRESHOLD  256
#घोषणा RX_BUF_ALLOC_SIZE  (ETH_FRAME_LEN + (64 * 3))

काष्ठा bmac_init_block अणु
	काष्ठा be_rxd be_rxd[RX_RING_MAXSIZE];
	काष्ठा be_txd be_txd[TX_RING_MAXSIZE];
पूर्ण;

#घोषणा bib_offset(mem, elem) \
((__u32)((अचिन्हित दीर्घ)(&(((काष्ठा bmac_init_block *)0)->mem[elem]))))

/* Now software state stuff. */
क्रमागत bigmac_transceiver अणु
	बाह्यal = 0,
	पूर्णांकernal = 1,
	none     = 2,
पूर्ण;

/* Timer state engine. */
क्रमागत bigmac_समयr_state अणु
	ltryरुको = 1,  /* Forcing try of all modes, from fastest to slowest. */
	asleep   = 2,  /* Timer inactive.                                    */
पूर्ण;

काष्ठा bigmac अणु
	व्योम __iomem	*gregs;	/* QEC Global Registers               */
	व्योम __iomem	*creg;	/* QEC BigMAC Channel Registers       */
	व्योम __iomem	*bregs;	/* BigMAC Registers                   */
	व्योम __iomem	*tregs;	/* BigMAC Transceiver                 */
	काष्ठा bmac_init_block	*bmac_block;	/* RX and TX descriptors */
	dma_addr_t		bblock_dvma;	/* RX and TX descriptors */

	spinlock_t		lock;

	काष्ठा sk_buff		*rx_skbs[RX_RING_SIZE];
	काष्ठा sk_buff		*tx_skbs[TX_RING_SIZE];

	पूर्णांक rx_new, tx_new, rx_old, tx_old;

	पूर्णांक board_rev;				/* BigMAC board revision.             */

	क्रमागत bigmac_transceiver	tcvr_type;
	अचिन्हित पूर्णांक		bigmac_bursts;
	अचिन्हित पूर्णांक		paddr;
	अचिन्हित लघु		sw_bmsr;         /* SW copy of PHY BMSR               */
	अचिन्हित लघु		sw_bmcr;         /* SW copy of PHY BMCR               */
	काष्ठा समयr_list	bigmac_समयr;
	क्रमागत bigmac_समयr_state	समयr_state;
	अचिन्हित पूर्णांक		समयr_ticks;

	काष्ठा platक्रमm_device	*qec_op;
	काष्ठा platक्रमm_device	*bigmac_op;
	काष्ठा net_device	*dev;
पूर्ण;

/* We use this to acquire receive skb's that we can DMA directly पूर्णांकo. */
#घोषणा ALIGNED_RX_SKB_ADDR(addr) \
        ((((अचिन्हित दीर्घ)(addr) + (64 - 1)) & ~(64 - 1)) - (अचिन्हित दीर्घ)(addr))

अटल अंतरभूत काष्ठा sk_buff *big_mac_alloc_skb(अचिन्हित पूर्णांक length, gfp_t gfp_flags)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(length + 64, gfp_flags);
	अगर(skb) अणु
		पूर्णांक offset = ALIGNED_RX_SKB_ADDR(skb->data);

		अगर(offset)
			skb_reserve(skb, offset);
	पूर्ण
	वापस skb;
पूर्ण

#पूर्ण_अगर /* !(_SUNBMAC_H) */
