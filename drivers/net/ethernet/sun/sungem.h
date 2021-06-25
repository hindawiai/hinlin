<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Id: sungem.h,v 1.10.2.4 2002/03/11 08:54:48 davem Exp $
 * sungem.h: Definitions क्रम Sun GEM ethernet driver.
 *
 * Copyright (C) 2000 David S. Miller (davem@redhat.com)
 */

#अगर_अघोषित _SUNGEM_H
#घोषणा _SUNGEM_H

/* Global Registers */
#घोषणा GREG_SEBSTATE	0x0000UL	/* SEB State Register		*/
#घोषणा GREG_CFG	0x0004UL	/* Configuration Register	*/
#घोषणा GREG_STAT	0x000CUL	/* Status Register		*/
#घोषणा GREG_IMASK	0x0010UL	/* Interrupt Mask Register	*/
#घोषणा GREG_IACK	0x0014UL	/* Interrupt ACK Register	*/
#घोषणा GREG_STAT2	0x001CUL	/* Alias of GREG_STAT		*/
#घोषणा GREG_PCIESTAT	0x1000UL	/* PCI Error Status Register	*/
#घोषणा GREG_PCIEMASK	0x1004UL	/* PCI Error Mask Register	*/
#घोषणा GREG_BIFCFG	0x1008UL	/* BIF Configuration Register	*/
#घोषणा GREG_BIFDIAG	0x100CUL	/* BIF Diagnostics Register	*/
#घोषणा GREG_SWRST	0x1010UL	/* Software Reset Register	*/

/* Global SEB State Register */
#घोषणा GREG_SEBSTATE_ARB	0x00000003	/* State of Arbiter		*/
#घोषणा GREG_SEBSTATE_RXWON	0x00000004	/* RX won पूर्णांकernal arbitration	*/

/* Global Configuration Register */
#घोषणा GREG_CFG_IBURST		0x00000001	/* Infinite Burst		*/
#घोषणा GREG_CFG_TXDMALIM	0x0000003e	/* TX DMA grant limit		*/
#घोषणा GREG_CFG_RXDMALIM	0x000007c0	/* RX DMA grant limit		*/
#घोषणा GREG_CFG_RONPAULBIT	0x00000800	/* Use mem पढ़ो multiple क्रम PCI पढ़ो
						 * after infinite burst (Apple) */
#घोषणा GREG_CFG_ENBUG2FIX	0x00001000	/* Fix Rx hang after overflow */

/* Global Interrupt Status Register.
 *
 * Reading this रेजिस्टर स्वतःmatically clears bits 0 through 6.
 * This स्वतः-clearing करोes not occur when the alias at GREG_STAT2
 * is पढ़ो instead.  The rest of the पूर्णांकerrupt bits only clear when
 * the secondary पूर्णांकerrupt status रेजिस्टर corresponding to that
 * bit is पढ़ो (ie. अगर GREG_STAT_PCS is set, it will be cleared by
 * पढ़ोing PCS_ISTAT).
 */
#घोषणा GREG_STAT_TXINTME	0x00000001	/* TX INTME frame transferred	*/
#घोषणा GREG_STAT_TXALL		0x00000002	/* All TX frames transferred	*/
#घोषणा GREG_STAT_TXDONE	0x00000004	/* One TX frame transferred	*/
#घोषणा GREG_STAT_RXDONE	0x00000010	/* One RX frame arrived		*/
#घोषणा GREG_STAT_RXNOBUF	0x00000020	/* No मुक्त RX buffers available	*/
#घोषणा GREG_STAT_RXTAGERR	0x00000040	/* RX tag framing is corrupt	*/
#घोषणा GREG_STAT_PCS		0x00002000	/* PCS संकेतled पूर्णांकerrupt	*/
#घोषणा GREG_STAT_TXMAC		0x00004000	/* TX MAC संकेतled पूर्णांकerrupt	*/
#घोषणा GREG_STAT_RXMAC		0x00008000	/* RX MAC संकेतled पूर्णांकerrupt	*/
#घोषणा GREG_STAT_MAC		0x00010000	/* MAC Control संकेतled irq	*/
#घोषणा GREG_STAT_MIF		0x00020000	/* MIF संकेतled पूर्णांकerrupt	*/
#घोषणा GREG_STAT_PCIERR	0x00040000	/* PCI Error पूर्णांकerrupt		*/
#घोषणा GREG_STAT_TXNR		0xfff80000	/* == TXDMA_TXDONE reg val	*/
#घोषणा GREG_STAT_TXNR_SHIFT	19

#घोषणा GREG_STAT_ABNORMAL	(GREG_STAT_RXNOBUF | GREG_STAT_RXTAGERR | \
				 GREG_STAT_PCS | GREG_STAT_TXMAC | GREG_STAT_RXMAC | \
				 GREG_STAT_MAC | GREG_STAT_MIF | GREG_STAT_PCIERR)

#घोषणा GREG_STAT_NAPI		(GREG_STAT_TXALL  | GREG_STAT_TXINTME | \
				 GREG_STAT_RXDONE | GREG_STAT_ABNORMAL)

/* The layout of GREG_IMASK and GREG_IACK is identical to GREG_STAT.
 * Bits set in GREG_IMASK will prevent that पूर्णांकerrupt type from being
 * संकेतled to the cpu.  GREG_IACK can be used to clear specअगरic top-level
 * पूर्णांकerrupt conditions in GREG_STAT, ie. it only works क्रम bits 0 through 6.
 * Setting the bit will clear that पूर्णांकerrupt, clear bits will have no effect
 * on GREG_STAT.
 */

/* Global PCI Error Status Register */
#घोषणा GREG_PCIESTAT_BADACK	0x00000001	/* No ACK64# during ABS64 cycle	*/
#घोषणा GREG_PCIESTAT_DTRTO	0x00000002	/* Delayed transaction समयout	*/
#घोषणा GREG_PCIESTAT_OTHER	0x00000004	/* Other PCI error, check cfg space */

/* The layout of the GREG_PCIEMASK is identical to that of GREG_PCIESTAT.
 * Bits set in GREG_PCIEMASK will prevent that पूर्णांकerrupt type from being
 * संकेतled to the cpu.
 */

/* Global BIF Configuration Register */
#घोषणा GREG_BIFCFG_SLOWCLK	0x00000001	/* Set अगर PCI runs < 25Mhz	*/
#घोषणा GREG_BIFCFG_B64DIS	0x00000002	/* Disable 64bit wide data cycle*/
#घोषणा GREG_BIFCFG_M66EN	0x00000004	/* Set अगर on 66Mhz PCI segment	*/

/* Global BIF Diagnostics Register */
#घोषणा GREG_BIFDIAG_BURSTSM	0x007f0000	/* PCI Burst state machine	*/
#घोषणा GREG_BIFDIAG_BIFSM	0xff000000	/* BIF state machine		*/

/* Global Software Reset Register.
 *
 * This रेजिस्टर is used to perक्रमm a global reset of the RX and TX portions
 * of the GEM asic.  Setting the RX or TX reset bit will start the reset.
 * The driver _MUST_ poll these bits until they clear.  One may not attempt
 * to program any other part of GEM until the bits clear.
 */
#घोषणा GREG_SWRST_TXRST	0x00000001	/* TX Software Reset		*/
#घोषणा GREG_SWRST_RXRST	0x00000002	/* RX Software Reset		*/
#घोषणा GREG_SWRST_RSTOUT	0x00000004	/* Force RST# pin active	*/
#घोषणा GREG_SWRST_CACHESIZE	0x00ff0000	/* RIO only: cache line size	*/
#घोषणा GREG_SWRST_CACHE_SHIFT	16

/* TX DMA Registers */
#घोषणा TXDMA_KICK	0x2000UL	/* TX Kick Register		*/
#घोषणा TXDMA_CFG	0x2004UL	/* TX Configuration Register	*/
#घोषणा TXDMA_DBLOW	0x2008UL	/* TX Desc. Base Low		*/
#घोषणा TXDMA_DBHI	0x200CUL	/* TX Desc. Base High		*/
#घोषणा TXDMA_FWPTR	0x2014UL	/* TX FIFO Write Poपूर्णांकer	*/
#घोषणा TXDMA_FSWPTR	0x2018UL	/* TX FIFO Shaकरोw Write Poपूर्णांकer	*/
#घोषणा TXDMA_FRPTR	0x201CUL	/* TX FIFO Read Poपूर्णांकer		*/
#घोषणा TXDMA_FSRPTR	0x2020UL	/* TX FIFO Shaकरोw Read Poपूर्णांकer	*/
#घोषणा TXDMA_PCNT	0x2024UL	/* TX FIFO Packet Counter	*/
#घोषणा TXDMA_SMACHINE	0x2028UL	/* TX State Machine Register	*/
#घोषणा TXDMA_DPLOW	0x2030UL	/* TX Data Poपूर्णांकer Low		*/
#घोषणा TXDMA_DPHI	0x2034UL	/* TX Data Poपूर्णांकer High		*/
#घोषणा TXDMA_TXDONE	0x2100UL	/* TX Completion Register	*/
#घोषणा TXDMA_FADDR	0x2104UL	/* TX FIFO Address		*/
#घोषणा TXDMA_FTAG	0x2108UL	/* TX FIFO Tag			*/
#घोषणा TXDMA_DLOW	0x210CUL	/* TX FIFO Data Low		*/
#घोषणा TXDMA_DHIT1	0x2110UL	/* TX FIFO Data HighT1		*/
#घोषणा TXDMA_DHIT0	0x2114UL	/* TX FIFO Data HighT0		*/
#घोषणा TXDMA_FSZ	0x2118UL	/* TX FIFO Size			*/

/* TX Kick Register.
 *
 * This 13-bit रेजिस्टर is programmed by the driver to hold the descriptor
 * entry index which follows the last valid transmit descriptor.
 */

/* TX Completion Register.
 *
 * This 13-bit रेजिस्टर is updated by GEM to hold to descriptor entry index
 * which follows the last descriptor alपढ़ोy processed by GEM.  Note that
 * this value is mirrored in GREG_STAT which eliminates the need to even
 * access this रेजिस्टर in the driver during पूर्णांकerrupt processing.
 */

/* TX Configuration Register.
 *
 * Note that TXDMA_CFG_FTHRESH, the TX FIFO Threshold, is an obsolete feature
 * that was meant to be used with jumbo packets.  It should be set to the
 * maximum value of 0x4ff, अन्यथा one risks getting TX MAC Underrun errors.
 */
#घोषणा TXDMA_CFG_ENABLE	0x00000001	/* Enable TX DMA channel	*/
#घोषणा TXDMA_CFG_RINGSZ	0x0000001e	/* TX descriptor ring size	*/
#घोषणा TXDMA_CFG_RINGSZ_32	0x00000000	/* 32 TX descriptors		*/
#घोषणा TXDMA_CFG_RINGSZ_64	0x00000002	/* 64 TX descriptors		*/
#घोषणा TXDMA_CFG_RINGSZ_128	0x00000004	/* 128 TX descriptors		*/
#घोषणा TXDMA_CFG_RINGSZ_256	0x00000006	/* 256 TX descriptors		*/
#घोषणा TXDMA_CFG_RINGSZ_512	0x00000008	/* 512 TX descriptors		*/
#घोषणा TXDMA_CFG_RINGSZ_1K	0x0000000a	/* 1024 TX descriptors		*/
#घोषणा TXDMA_CFG_RINGSZ_2K	0x0000000c	/* 2048 TX descriptors		*/
#घोषणा TXDMA_CFG_RINGSZ_4K	0x0000000e	/* 4096 TX descriptors		*/
#घोषणा TXDMA_CFG_RINGSZ_8K	0x00000010	/* 8192 TX descriptors		*/
#घोषणा TXDMA_CFG_PIOSEL	0x00000020	/* Enable TX FIFO PIO from cpu	*/
#घोषणा TXDMA_CFG_FTHRESH	0x001ffc00	/* TX FIFO Threshold, obsolete	*/
#घोषणा TXDMA_CFG_PMODE		0x00200000	/* TXALL irq means TX FIFO empty*/

/* TX Descriptor Base Low/High.
 *
 * These two रेजिस्टरs store the 53 most signअगरicant bits of the base address
 * of the TX descriptor table.  The 11 least signअगरicant bits are always
 * zero.  As a result, the TX descriptor table must be 2K aligned.
 */

/* The rest of the TXDMA_* रेजिस्टरs are क्रम diagnostics and debug, I will करोcument
 * them later. -DaveM
 */

/* WakeOnLan Registers	*/
#घोषणा WOL_MATCH0	0x3000UL
#घोषणा WOL_MATCH1	0x3004UL
#घोषणा WOL_MATCH2	0x3008UL
#घोषणा WOL_MCOUNT	0x300CUL
#घोषणा WOL_WAKECSR	0x3010UL

/* WOL Match count रेजिस्टर
 */
#घोषणा WOL_MCOUNT_N		0x00000010
#घोषणा WOL_MCOUNT_M		0x00000000 /* 0 << 8 */

#घोषणा WOL_WAKECSR_ENABLE	0x00000001
#घोषणा WOL_WAKECSR_MII		0x00000002
#घोषणा WOL_WAKECSR_SEEN	0x00000004
#घोषणा WOL_WAKECSR_FILT_UCAST	0x00000008
#घोषणा WOL_WAKECSR_FILT_MCAST	0x00000010
#घोषणा WOL_WAKECSR_FILT_BCAST	0x00000020
#घोषणा WOL_WAKECSR_FILT_SEEN	0x00000040


/* Receive DMA Registers */
#घोषणा RXDMA_CFG	0x4000UL	/* RX Configuration Register	*/
#घोषणा RXDMA_DBLOW	0x4004UL	/* RX Descriptor Base Low	*/
#घोषणा RXDMA_DBHI	0x4008UL	/* RX Descriptor Base High	*/
#घोषणा RXDMA_FWPTR	0x400CUL	/* RX FIFO Write Poपूर्णांकer	*/
#घोषणा RXDMA_FSWPTR	0x4010UL	/* RX FIFO Shaकरोw Write Poपूर्णांकer	*/
#घोषणा RXDMA_FRPTR	0x4014UL	/* RX FIFO Read Poपूर्णांकer		*/
#घोषणा RXDMA_PCNT	0x4018UL	/* RX FIFO Packet Counter	*/
#घोषणा RXDMA_SMACHINE	0x401CUL	/* RX State Machine Register	*/
#घोषणा RXDMA_PTHRESH	0x4020UL	/* Pause Thresholds		*/
#घोषणा RXDMA_DPLOW	0x4024UL	/* RX Data Poपूर्णांकer Low		*/
#घोषणा RXDMA_DPHI	0x4028UL	/* RX Data Poपूर्णांकer High		*/
#घोषणा RXDMA_KICK	0x4100UL	/* RX Kick Register		*/
#घोषणा RXDMA_DONE	0x4104UL	/* RX Completion Register	*/
#घोषणा RXDMA_BLANK	0x4108UL	/* RX Blanking Register		*/
#घोषणा RXDMA_FADDR	0x410CUL	/* RX FIFO Address		*/
#घोषणा RXDMA_FTAG	0x4110UL	/* RX FIFO Tag			*/
#घोषणा RXDMA_DLOW	0x4114UL	/* RX FIFO Data Low		*/
#घोषणा RXDMA_DHIT1	0x4118UL	/* RX FIFO Data HighT0		*/
#घोषणा RXDMA_DHIT0	0x411CUL	/* RX FIFO Data HighT1		*/
#घोषणा RXDMA_FSZ	0x4120UL	/* RX FIFO Size			*/

/* RX Configuration Register. */
#घोषणा RXDMA_CFG_ENABLE	0x00000001	/* Enable RX DMA channel	*/
#घोषणा RXDMA_CFG_RINGSZ	0x0000001e	/* RX descriptor ring size	*/
#घोषणा RXDMA_CFG_RINGSZ_32	0x00000000	/* - 32   entries		*/
#घोषणा RXDMA_CFG_RINGSZ_64	0x00000002	/* - 64   entries		*/
#घोषणा RXDMA_CFG_RINGSZ_128	0x00000004	/* - 128  entries		*/
#घोषणा RXDMA_CFG_RINGSZ_256	0x00000006	/* - 256  entries		*/
#घोषणा RXDMA_CFG_RINGSZ_512	0x00000008	/* - 512  entries		*/
#घोषणा RXDMA_CFG_RINGSZ_1K	0x0000000a	/* - 1024 entries		*/
#घोषणा RXDMA_CFG_RINGSZ_2K	0x0000000c	/* - 2048 entries		*/
#घोषणा RXDMA_CFG_RINGSZ_4K	0x0000000e	/* - 4096 entries		*/
#घोषणा RXDMA_CFG_RINGSZ_8K	0x00000010	/* - 8192 entries		*/
#घोषणा RXDMA_CFG_RINGSZ_BDISAB	0x00000020	/* Disable RX desc batching	*/
#घोषणा RXDMA_CFG_FBOFF		0x00001c00	/* Offset of first data byte	*/
#घोषणा RXDMA_CFG_CSUMOFF	0x000fe000	/* Skip bytes beक्रमe csum calc	*/
#घोषणा RXDMA_CFG_FTHRESH	0x07000000	/* RX FIFO dma start threshold	*/
#घोषणा RXDMA_CFG_FTHRESH_64	0x00000000	/* - 64   bytes			*/
#घोषणा RXDMA_CFG_FTHRESH_128	0x01000000	/* - 128  bytes			*/
#घोषणा RXDMA_CFG_FTHRESH_256	0x02000000	/* - 256  bytes			*/
#घोषणा RXDMA_CFG_FTHRESH_512	0x03000000	/* - 512  bytes			*/
#घोषणा RXDMA_CFG_FTHRESH_1K	0x04000000	/* - 1024 bytes			*/
#घोषणा RXDMA_CFG_FTHRESH_2K	0x05000000	/* - 2048 bytes			*/

/* RX Descriptor Base Low/High.
 *
 * These two रेजिस्टरs store the 53 most signअगरicant bits of the base address
 * of the RX descriptor table.  The 11 least signअगरicant bits are always
 * zero.  As a result, the RX descriptor table must be 2K aligned.
 */

/* RX PAUSE Thresholds.
 *
 * These values determine when XOFF and XON PAUSE frames are emitted by
 * GEM.  The thresholds measure RX FIFO occupancy in units of 64 bytes.
 */
#घोषणा RXDMA_PTHRESH_OFF	0x000001ff	/* XOFF emitted w/FIFO > this	*/
#घोषणा RXDMA_PTHRESH_ON	0x001ff000	/* XON emitted w/FIFO < this	*/

/* RX Kick Register.
 *
 * This 13-bit रेजिस्टर is written by the host CPU and holds the last
 * valid RX descriptor number plus one.  This is, अगर 'N' is written to
 * this रेजिस्टर, it means that all RX descriptors up to but excluding
 * 'N' are valid.
 *
 * The hardware requires that RX descriptors are posted in increments
 * of 4.  This means 'N' must be a multiple of four.  For the best
 * perक्रमmance, the first new descriptor being posted should be (PCI)
 * cache line aligned.
 */

/* RX Completion Register.
 *
 * This 13-bit रेजिस्टर is updated by GEM to indicate which RX descriptors
 * have alपढ़ोy been used क्रम receive frames.  All descriptors up to but
 * excluding the value in this रेजिस्टर are पढ़ोy to be processed.  GEM
 * updates this रेजिस्टर value after the RX FIFO empties completely पूर्णांकo
 * the RX descriptor's buffer, but beक्रमe the RX_DONE bit is set in the
 * पूर्णांकerrupt status रेजिस्टर.
 */

/* RX Blanking Register. */
#घोषणा RXDMA_BLANK_IPKTS	0x000001ff	/* RX_DONE निश्चितed after this
						 * many packets received since
						 * previous RX_DONE.
						 */
#घोषणा RXDMA_BLANK_ITIME	0x000ff000	/* RX_DONE निश्चितed after this
						 * many घड़ीs (measured in 2048
						 * PCI घड़ीs) were counted since
						 * the previous RX_DONE.
						 */

/* RX FIFO Size.
 *
 * This 11-bit पढ़ो-only रेजिस्टर indicates how large, in units of 64-bytes,
 * the RX FIFO is.  The driver uses this to properly configure the RX PAUSE
 * thresholds.
 */

/* The rest of the RXDMA_* रेजिस्टरs are क्रम diagnostics and debug, I will करोcument
 * them later. -DaveM
 */

/* MAC Registers */
#घोषणा MAC_TXRST	0x6000UL	/* TX MAC Software Reset Command*/
#घोषणा MAC_RXRST	0x6004UL	/* RX MAC Software Reset Command*/
#घोषणा MAC_SNDPAUSE	0x6008UL	/* Send Pause Command Register	*/
#घोषणा MAC_TXSTAT	0x6010UL	/* TX MAC Status Register	*/
#घोषणा MAC_RXSTAT	0x6014UL	/* RX MAC Status Register	*/
#घोषणा MAC_CSTAT	0x6018UL	/* MAC Control Status Register	*/
#घोषणा MAC_TXMASK	0x6020UL	/* TX MAC Mask Register		*/
#घोषणा MAC_RXMASK	0x6024UL	/* RX MAC Mask Register		*/
#घोषणा MAC_MCMASK	0x6028UL	/* MAC Control Mask Register	*/
#घोषणा MAC_TXCFG	0x6030UL	/* TX MAC Configuration Register*/
#घोषणा MAC_RXCFG	0x6034UL	/* RX MAC Configuration Register*/
#घोषणा MAC_MCCFG	0x6038UL	/* MAC Control Config Register	*/
#घोषणा MAC_XIFCFG	0x603CUL	/* XIF Configuration Register	*/
#घोषणा MAC_IPG0	0x6040UL	/* InterPacketGap0 Register	*/
#घोषणा MAC_IPG1	0x6044UL	/* InterPacketGap1 Register	*/
#घोषणा MAC_IPG2	0x6048UL	/* InterPacketGap2 Register	*/
#घोषणा MAC_STIME	0x604CUL	/* SlotTime Register		*/
#घोषणा MAC_MINFSZ	0x6050UL	/* MinFrameSize Register	*/
#घोषणा MAC_MAXFSZ	0x6054UL	/* MaxFrameSize Register	*/
#घोषणा MAC_PASIZE	0x6058UL	/* PA Size Register		*/
#घोषणा MAC_JAMSIZE	0x605CUL	/* JamSize Register		*/
#घोषणा MAC_ATTLIM	0x6060UL	/* Attempt Limit Register	*/
#घोषणा MAC_MCTYPE	0x6064UL	/* MAC Control Type Register	*/
#घोषणा MAC_ADDR0	0x6080UL	/* MAC Address 0 Register	*/
#घोषणा MAC_ADDR1	0x6084UL	/* MAC Address 1 Register	*/
#घोषणा MAC_ADDR2	0x6088UL	/* MAC Address 2 Register	*/
#घोषणा MAC_ADDR3	0x608CUL	/* MAC Address 3 Register	*/
#घोषणा MAC_ADDR4	0x6090UL	/* MAC Address 4 Register	*/
#घोषणा MAC_ADDR5	0x6094UL	/* MAC Address 5 Register	*/
#घोषणा MAC_ADDR6	0x6098UL	/* MAC Address 6 Register	*/
#घोषणा MAC_ADDR7	0x609CUL	/* MAC Address 7 Register	*/
#घोषणा MAC_ADDR8	0x60A0UL	/* MAC Address 8 Register	*/
#घोषणा MAC_AFILT0	0x60A4UL	/* Address Filter 0 Register	*/
#घोषणा MAC_AFILT1	0x60A8UL	/* Address Filter 1 Register	*/
#घोषणा MAC_AFILT2	0x60ACUL	/* Address Filter 2 Register	*/
#घोषणा MAC_AF21MSK	0x60B0UL	/* Address Filter 2&1 Mask Reg	*/
#घोषणा MAC_AF0MSK	0x60B4UL	/* Address Filter 0 Mask Reg	*/
#घोषणा MAC_HASH0	0x60C0UL	/* Hash Table 0 Register	*/
#घोषणा MAC_HASH1	0x60C4UL	/* Hash Table 1 Register	*/
#घोषणा MAC_HASH2	0x60C8UL	/* Hash Table 2 Register	*/
#घोषणा MAC_HASH3	0x60CCUL	/* Hash Table 3 Register	*/
#घोषणा MAC_HASH4	0x60D0UL	/* Hash Table 4 Register	*/
#घोषणा MAC_HASH5	0x60D4UL	/* Hash Table 5 Register	*/
#घोषणा MAC_HASH6	0x60D8UL	/* Hash Table 6 Register	*/
#घोषणा MAC_HASH7	0x60DCUL	/* Hash Table 7 Register	*/
#घोषणा MAC_HASH8	0x60E0UL	/* Hash Table 8 Register	*/
#घोषणा MAC_HASH9	0x60E4UL	/* Hash Table 9 Register	*/
#घोषणा MAC_HASH10	0x60E8UL	/* Hash Table 10 Register	*/
#घोषणा MAC_HASH11	0x60ECUL	/* Hash Table 11 Register	*/
#घोषणा MAC_HASH12	0x60F0UL	/* Hash Table 12 Register	*/
#घोषणा MAC_HASH13	0x60F4UL	/* Hash Table 13 Register	*/
#घोषणा MAC_HASH14	0x60F8UL	/* Hash Table 14 Register	*/
#घोषणा MAC_HASH15	0x60FCUL	/* Hash Table 15 Register	*/
#घोषणा MAC_NCOLL	0x6100UL	/* Normal Collision Counter	*/
#घोषणा MAC_FASUCC	0x6104UL	/* First Atपंचांगpt. Succ Coll Ctr.	*/
#घोषणा MAC_ECOLL	0x6108UL	/* Excessive Collision Counter	*/
#घोषणा MAC_LCOLL	0x610CUL	/* Late Collision Counter	*/
#घोषणा MAC_DTIMER	0x6110UL	/* Defer Timer			*/
#घोषणा MAC_PATMPS	0x6114UL	/* Peak Attempts Register	*/
#घोषणा MAC_RFCTR	0x6118UL	/* Receive Frame Counter	*/
#घोषणा MAC_LERR	0x611CUL	/* Length Error Counter		*/
#घोषणा MAC_AERR	0x6120UL	/* Alignment Error Counter	*/
#घोषणा MAC_FCSERR	0x6124UL	/* FCS Error Counter		*/
#घोषणा MAC_RXCVERR	0x6128UL	/* RX code Violation Error Ctr	*/
#घोषणा MAC_RANDSEED	0x6130UL	/* Ranकरोm Number Seed Register	*/
#घोषणा MAC_SMACHINE	0x6134UL	/* State Machine Register	*/

/* TX MAC Software Reset Command. */
#घोषणा MAC_TXRST_CMD	0x00000001	/* Start sw reset, self-clears	*/

/* RX MAC Software Reset Command. */
#घोषणा MAC_RXRST_CMD	0x00000001	/* Start sw reset, self-clears	*/

/* Send Pause Command. */
#घोषणा MAC_SNDPAUSE_TS	0x0000ffff	/* The छोड़ो_समय opeअक्रम used in
					 * Send_Pause and flow-control
					 * handshakes.
					 */
#घोषणा MAC_SNDPAUSE_SP	0x00010000	/* Setting this bit inकाष्ठाs the MAC
					 * to send a Pause Flow Control
					 * frame onto the network.
					 */

/* TX MAC Status Register. */
#घोषणा MAC_TXSTAT_XMIT	0x00000001	/* Frame Transmitted		*/
#घोषणा MAC_TXSTAT_URUN	0x00000002	/* TX Underrun			*/
#घोषणा MAC_TXSTAT_MPE	0x00000004	/* Max Packet Size Error	*/
#घोषणा MAC_TXSTAT_NCE	0x00000008	/* Normal Collision Cntr Expire	*/
#घोषणा MAC_TXSTAT_ECE	0x00000010	/* Excess Collision Cntr Expire	*/
#घोषणा MAC_TXSTAT_LCE	0x00000020	/* Late Collision Cntr Expire	*/
#घोषणा MAC_TXSTAT_FCE	0x00000040	/* First Collision Cntr Expire	*/
#घोषणा MAC_TXSTAT_DTE	0x00000080	/* Defer Timer Expire		*/
#घोषणा MAC_TXSTAT_PCE	0x00000100	/* Peak Attempts Cntr Expire	*/

/* RX MAC Status Register. */
#घोषणा MAC_RXSTAT_RCV	0x00000001	/* Frame Received		*/
#घोषणा MAC_RXSTAT_OFLW	0x00000002	/* Receive Overflow		*/
#घोषणा MAC_RXSTAT_FCE	0x00000004	/* Frame Cntr Expire		*/
#घोषणा MAC_RXSTAT_ACE	0x00000008	/* Align Error Cntr Expire	*/
#घोषणा MAC_RXSTAT_CCE	0x00000010	/* CRC Error Cntr Expire	*/
#घोषणा MAC_RXSTAT_LCE	0x00000020	/* Length Error Cntr Expire	*/
#घोषणा MAC_RXSTAT_VCE	0x00000040	/* Code Violation Cntr Expire	*/

/* MAC Control Status Register. */
#घोषणा MAC_CSTAT_PRCV	0x00000001	/* Pause Received		*/
#घोषणा MAC_CSTAT_PS	0x00000002	/* Paused State			*/
#घोषणा MAC_CSTAT_NPS	0x00000004	/* Not Paused State		*/
#घोषणा MAC_CSTAT_PTR	0xffff0000	/* Pause Time Received		*/

/* The layout of the MAC_अणुTX,RX,Cपूर्णMASK रेजिस्टरs is identical to that
 * of MAC_अणुTX,RX,Cपूर्णSTAT.  Bits set in MAC_अणुTX,RX,Cपूर्णMASK will prevent
 * that पूर्णांकerrupt type from being संकेतled to front end of GEM.  For
 * the पूर्णांकerrupt to actually get sent to the cpu, it is necessary to
 * properly set the appropriate GREG_IMASK_अणुTX,RX,पूर्णMAC bits as well.
 */

/* TX MAC Configuration Register.
 *
 * NOTE: The TX MAC Enable bit must be cleared and polled until
 *	 zero beक्रमe any other bits in this रेजिस्टर are changed.
 *
 *	 Also, enabling the Carrier Extension feature of GEM is
 *	 a 3 step process 1) Set TX Carrier Extension 2) Set
 *	 RX Carrier Extension 3) Set Slot Time to 0x200.  This
 *	 mode must be enabled when in half-duplex at 1Gbps, अन्यथा
 *	 it must be disabled.
 */
#घोषणा MAC_TXCFG_ENAB	0x00000001	/* TX MAC Enable		*/
#घोषणा MAC_TXCFG_ICS	0x00000002	/* Ignore Carrier Sense		*/
#घोषणा MAC_TXCFG_ICOLL	0x00000004	/* Ignore Collisions		*/
#घोषणा MAC_TXCFG_EIPG0	0x00000008	/* Enable IPG0			*/
#घोषणा MAC_TXCFG_NGU	0x00000010	/* Never Give Up		*/
#घोषणा MAC_TXCFG_NGUL	0x00000020	/* Never Give Up Limit		*/
#घोषणा MAC_TXCFG_NBO	0x00000040	/* No Backoff			*/
#घोषणा MAC_TXCFG_SD	0x00000080	/* Slow Down			*/
#घोषणा MAC_TXCFG_NFCS	0x00000100	/* No FCS			*/
#घोषणा MAC_TXCFG_TCE	0x00000200	/* TX Carrier Extension		*/

/* RX MAC Configuration Register.
 *
 * NOTE: The RX MAC Enable bit must be cleared and polled until
 *	 zero beक्रमe any other bits in this रेजिस्टर are changed.
 *
 *	 Similar rules apply to the Hash Filter Enable bit when
 *	 programming the hash table रेजिस्टरs, and the Address Filter
 *	 Enable bit when programming the address filter रेजिस्टरs.
 */
#घोषणा MAC_RXCFG_ENAB	0x00000001	/* RX MAC Enable		*/
#घोषणा MAC_RXCFG_SPAD	0x00000002	/* Strip Pad			*/
#घोषणा MAC_RXCFG_SFCS	0x00000004	/* Strip FCS			*/
#घोषणा MAC_RXCFG_PROM	0x00000008	/* Promiscuous Mode		*/
#घोषणा MAC_RXCFG_PGRP	0x00000010	/* Promiscuous Group		*/
#घोषणा MAC_RXCFG_HFE	0x00000020	/* Hash Filter Enable		*/
#घोषणा MAC_RXCFG_AFE	0x00000040	/* Address Filter Enable	*/
#घोषणा MAC_RXCFG_DDE	0x00000080	/* Disable Discard on Error	*/
#घोषणा MAC_RXCFG_RCE	0x00000100	/* RX Carrier Extension		*/

/* MAC Control Config Register. */
#घोषणा MAC_MCCFG_SPE	0x00000001	/* Send Pause Enable		*/
#घोषणा MAC_MCCFG_RPE	0x00000002	/* Receive Pause Enable		*/
#घोषणा MAC_MCCFG_PMC	0x00000004	/* Pass MAC Control		*/

/* XIF Configuration Register.
 *
 * NOTE: When leaving or entering loopback mode, a global hardware
 *       init of GEM should be perक्रमmed.
 */
#घोषणा MAC_XIFCFG_OE	0x00000001	/* MII TX Output Driver Enable	*/
#घोषणा MAC_XIFCFG_LBCK	0x00000002	/* Loopback TX to RX		*/
#घोषणा MAC_XIFCFG_DISE	0x00000004	/* Disable RX path during TX	*/
#घोषणा MAC_XIFCFG_GMII	0x00000008	/* Use GMII घड़ीs + datapath	*/
#घोषणा MAC_XIFCFG_MBOE	0x00000010	/* Controls MII_BUF_EN pin	*/
#घोषणा MAC_XIFCFG_LLED	0x00000020	/* Force LINKLED# active (low)	*/
#घोषणा MAC_XIFCFG_FLED	0x00000040	/* Force FDPLXLED# active (low)	*/

/* InterPacketGap0 Register.  This 8-bit value is used as an extension
 * to the InterPacketGap1 Register.  Specअगरically it contributes to the
 * timing of the RX-to-TX IPG.  This value is ignored and presumed to
 * be zero क्रम TX-to-TX IPG calculations and/or when the Enable IPG0 bit
 * is cleared in the TX MAC Configuration Register.
 *
 * This value in this रेजिस्टर in terms of media byte समय.
 *
 * Recommended value: 0x00
 */

/* InterPacketGap1 Register.  This 8-bit value defines the first 2/3
 * portion of the Inter Packet Gap.
 *
 * This value in this रेजिस्टर in terms of media byte समय.
 *
 * Recommended value: 0x08
 */

/* InterPacketGap2 Register.  This 8-bit value defines the second 1/3
 * portion of the Inter Packet Gap.
 *
 * This value in this रेजिस्टर in terms of media byte समय.
 *
 * Recommended value: 0x04
 */

/* Slot Time Register.  This 10-bit value specअगरies the slot समय
 * parameter in units of media byte समय.  It determines the physical
 * span of the network.
 *
 * Recommended value: 0x40
 */

/* Minimum Frame Size Register.  This 10-bit रेजिस्टर specअगरies the
 * smallest sized frame the TXMAC will send onto the medium, and the
 * RXMAC will receive from the medium.
 *
 * Recommended value: 0x40
 */

/* Maximum Frame and Burst Size Register.
 *
 * This रेजिस्टर specअगरies two things.  First it specअगरies the maximum
 * sized frame the TXMAC will send and the RXMAC will recognize as
 * valid.  Second, it specअगरies the maximum run length of a burst of
 * packets sent in half-duplex gigabit modes.
 *
 * Recommended value: 0x200005ee
 */
#घोषणा MAC_MAXFSZ_MFS	0x00007fff	/* Max Frame Size		*/
#घोषणा MAC_MAXFSZ_MBS	0x7fff0000	/* Max Burst Size		*/

/* PA Size Register.  This 10-bit रेजिस्टर specअगरies the number of preamble
 * bytes which will be transmitted at the beginning of each frame.  A
 * value of two or greater should be programmed here.
 *
 * Recommended value: 0x07
 */

/* Jam Size Register.  This 4-bit रेजिस्टर specअगरies the duration of
 * the jam in units of media byte समय.
 *
 * Recommended value: 0x04
 */

/* Attempts Limit Register.  This 8-bit रेजिस्टर specअगरies the number
 * of attempts that the TXMAC will make to transmit a frame, beक्रमe it
 * resets its Attempts Counter.  After reaching the Attempts Limit the
 * TXMAC may or may not drop the frame, as determined by the NGU
 * (Never Give Up) and NGUL (Never Give Up Limit) bits in the TXMAC
 * Configuration Register.
 *
 * Recommended value: 0x10
 */

/* MAX Control Type Register.  This 16-bit रेजिस्टर specअगरies the
 * "type" field of a MAC Control frame.  The TXMAC uses this field to
 * encapsulate the MAC Control frame क्रम transmission, and the RXMAC
 * uses it क्रम decoding valid MAC Control frames received from the
 * network.
 *
 * Recommended value: 0x8808
 */

/* MAC Address Registers.  Each of these रेजिस्टरs specअगरy the
 * ethernet MAC of the पूर्णांकerface, 16-bits at a समय.  Register
 * 0 specअगरies bits [47:32], रेजिस्टर 1 bits [31:16], and रेजिस्टर
 * 2 bits [15:0].
 *
 * Registers 3 through and including 5 specअगरy an alternate
 * MAC address क्रम the पूर्णांकerface.
 *
 * Registers 6 through and including 8 specअगरy the MAC Control
 * Address, which must be the reserved multicast address क्रम MAC
 * Control frames.
 *
 * Example: To program primary station address a:b:c:d:e:f पूर्णांकo
 *	    the chip.
 *		MAC_Address_2 = (a << 8) | b
 *		MAC_Address_1 = (c << 8) | d
 *		MAC_Address_0 = (e << 8) | f
 */

/* Address Filter Registers.  Registers 0 through 2 specअगरy bit
 * fields [47:32] through [15:0], respectively, of the address
 * filter.  The Address Filter 2&1 Mask Register denotes the 8-bit
 * nibble mask क्रम Address Filter Registers 2 and 1.  The Address
 * Filter 0 Mask Register denotes the 16-bit mask क्रम the Address
 * Filter Register 0.
 */

/* Hash Table Registers.  Registers 0 through 15 specअगरy bit fields
 * [255:240] through [15:0], respectively, of the hash table.
 */

/* Statistics Registers.  All of these रेजिस्टरs are 16-bits and
 * track occurrences of a specअगरic event.  GEM can be configured
 * to पूर्णांकerrupt the host cpu when any of these counters overflow.
 * They should all be explicitly initialized to zero when the पूर्णांकerface
 * is brought up.
 */

/* Ranकरोm Number Seed Register.  This 10-bit value is used as the
 * RNG seed inside GEM क्रम the CSMA/CD backoff algorithm.  It is
 * recommended to program this रेजिस्टर to the 10 LSB of the
 * पूर्णांकerfaces MAC address.
 */

/* Pause Timer, पढ़ो-only.  This 16-bit समयr is used to समय the छोड़ो
 * पूर्णांकerval as indicated by a received छोड़ो flow control frame.
 * A non-zero value in this समयr indicates that the MAC is currently in
 * the छोड़ोd state.
 */

/* MIF Registers */
#घोषणा MIF_BBCLK	0x6200UL	/* MIF Bit-Bang Clock		*/
#घोषणा MIF_BBDATA	0x6204UL	/* MIF Bit-Band Data		*/
#घोषणा MIF_BBOENAB	0x6208UL	/* MIF Bit-Bang Output Enable	*/
#घोषणा MIF_FRAME	0x620CUL	/* MIF Frame/Output Register	*/
#घोषणा MIF_CFG		0x6210UL	/* MIF Configuration Register	*/
#घोषणा MIF_MASK	0x6214UL	/* MIF Mask Register		*/
#घोषणा MIF_STATUS	0x6218UL	/* MIF Status Register		*/
#घोषणा MIF_SMACHINE	0x621CUL	/* MIF State Machine Register	*/

/* MIF Bit-Bang Clock.  This 1-bit रेजिस्टर is used to generate the
 * MDC घड़ी waveक्रमm on the MII Management Interface when the MIF is
 * programmed in the "Bit-Bang" mode.  Writing a '1' after a '0' पूर्णांकo
 * this रेजिस्टर will create a rising edge on the MDC, जबतक writing
 * a '0' after a '1' will create a falling edge.  For every bit that
 * is transferred on the management पूर्णांकerface, both edges have to be
 * generated.
 */

/* MIF Bit-Bang Data.  This 1-bit रेजिस्टर is used to generate the
 * outgoing data (MDO) on the MII Management Interface when the MIF
 * is programmed in the "Bit-Bang" mode.  The daa will be steered to the
 * appropriate MDIO based on the state of the PHY_Select bit in the MIF
 * Configuration Register.
 */

/* MIF Big-Band Output Enable.  THis 1-bit रेजिस्टर is used to enable
 * ('1') or disable ('0') the I-directional driver on the MII when the
 * MIF is programmed in the "Bit-Bang" mode.  The MDIO should be enabled
 * when data bits are transferred from the MIF to the transceiver, and it
 * should be disabled when the पूर्णांकerface is idle or when data bits are
 * transferred from the transceiver to the MIF (data portion of a पढ़ो
 * inकाष्ठाion).  Only one MDIO will be enabled at a given समय, depending
 * on the state of the PHY_Select bit in the MIF Configuration Register.
 */

/* MIF Configuration Register.  This 15-bit रेजिस्टर controls the operation
 * of the MIF.
 */
#घोषणा MIF_CFG_PSELECT	0x00000001	/* Xcvr slct: 0=mdio0 1=mdio1	*/
#घोषणा MIF_CFG_POLL	0x00000002	/* Enable polling mechanism	*/
#घोषणा MIF_CFG_BBMODE	0x00000004	/* 1=bit-bang 0=frame mode	*/
#घोषणा MIF_CFG_PRADDR	0x000000f8	/* Xcvr poll रेजिस्टर address	*/
#घोषणा MIF_CFG_MDI0	0x00000100	/* MDIO_0 present or पढ़ो-bit	*/
#घोषणा MIF_CFG_MDI1	0x00000200	/* MDIO_1 present or पढ़ो-bit	*/
#घोषणा MIF_CFG_PPADDR	0x00007c00	/* Xcvr poll PHY address	*/

/* MIF Frame/Output Register.  This 32-bit रेजिस्टर allows the host to
 * communicate with a transceiver in frame mode (as opposed to big-bang
 * mode).  Writes by the host specअगरy an instrution.  After being issued
 * the host must poll this रेजिस्टर क्रम completion.  Also, after
 * completion this रेजिस्टर holds the data वापसed by the transceiver
 * अगर applicable.
 */
#घोषणा MIF_FRAME_ST	0xc0000000	/* STart of frame		*/
#घोषणा MIF_FRAME_OP	0x30000000	/* OPcode			*/
#घोषणा MIF_FRAME_PHYAD	0x0f800000	/* PHY ADdress			*/
#घोषणा MIF_FRAME_REGAD	0x007c0000	/* REGister ADdress		*/
#घोषणा MIF_FRAME_TAMSB	0x00020000	/* Turn Around MSB		*/
#घोषणा MIF_FRAME_TALSB	0x00010000	/* Turn Around LSB		*/
#घोषणा MIF_FRAME_DATA	0x0000ffff	/* Inकाष्ठाion Payload		*/

/* MIF Status Register.  This रेजिस्टर reports status when the MIF is
 * operating in the poll mode.  The poll status field is स्वतः-clearing
 * on पढ़ो.
 */
#घोषणा MIF_STATUS_DATA	0xffff0000	/* Live image of XCVR reg	*/
#घोषणा MIF_STATUS_STAT	0x0000ffff	/* Which bits have changed	*/

/* MIF Mask Register.  This 16-bit रेजिस्टर is used when in poll mode
 * to say which bits of the polled रेजिस्टर will cause an पूर्णांकerrupt
 * when changed.
 */

/* PCS/Serialink Registers */
#घोषणा PCS_MIICTRL	0x9000UL	/* PCS MII Control Register	*/
#घोषणा PCS_MIISTAT	0x9004UL	/* PCS MII Status Register	*/
#घोषणा PCS_MIIADV	0x9008UL	/* PCS MII Advertisement Reg	*/
#घोषणा PCS_MIILP	0x900CUL	/* PCS MII Link Partner Ability	*/
#घोषणा PCS_CFG		0x9010UL	/* PCS Configuration Register	*/
#घोषणा PCS_SMACHINE	0x9014UL	/* PCS State Machine Register	*/
#घोषणा PCS_ISTAT	0x9018UL	/* PCS Interrupt Status Reg	*/
#घोषणा PCS_DMODE	0x9050UL	/* Datapath Mode Register	*/
#घोषणा PCS_SCTRL	0x9054UL	/* Serialink Control Register	*/
#घोषणा PCS_SOS		0x9058UL	/* Shared Output Select Reg	*/
#घोषणा PCS_SSTATE	0x905CUL	/* Serialink State Register	*/

/* PCD MII Control Register. */
#घोषणा PCS_MIICTRL_SPD	0x00000040	/* Read as one, ग_लिखोs ignored	*/
#घोषणा PCS_MIICTRL_CT	0x00000080	/* Force COL संकेत active	*/
#घोषणा PCS_MIICTRL_DM	0x00000100	/* Duplex mode, क्रमced low	*/
#घोषणा PCS_MIICTRL_RAN	0x00000200	/* Restart स्वतः-neg, self clear	*/
#घोषणा PCS_MIICTRL_ISO	0x00000400	/* Read as zero, ग_लिखोs ignored	*/
#घोषणा PCS_MIICTRL_PD	0x00000800	/* Read as zero, ग_लिखोs ignored	*/
#घोषणा PCS_MIICTRL_ANE	0x00001000	/* Auto-neg enable		*/
#घोषणा PCS_MIICTRL_SS	0x00002000	/* Read as zero, ग_लिखोs ignored	*/
#घोषणा PCS_MIICTRL_WB	0x00004000	/* Wrapback, loopback at 10-bit
					 * input side of Serialink
					 */
#घोषणा PCS_MIICTRL_RST	0x00008000	/* Resets PCS, self clearing	*/

/* PCS MII Status Register. */
#घोषणा PCS_MIISTAT_EC	0x00000001	/* Ext Capability: Read as zero	*/
#घोषणा PCS_MIISTAT_JD	0x00000002	/* Jabber Detect: Read as zero	*/
#घोषणा PCS_MIISTAT_LS	0x00000004	/* Link Status: 1=up 0=करोwn	*/
#घोषणा PCS_MIISTAT_ANA	0x00000008	/* Auto-neg Ability, always 1	*/
#घोषणा PCS_MIISTAT_RF	0x00000010	/* Remote Fault			*/
#घोषणा PCS_MIISTAT_ANC	0x00000020	/* Auto-neg complete		*/
#घोषणा PCS_MIISTAT_ES	0x00000100	/* Extended Status, always 1	*/

/* PCS MII Advertisement Register. */
#घोषणा PCS_MIIADV_FD	0x00000020	/* Advertise Full Duplex	*/
#घोषणा PCS_MIIADV_HD	0x00000040	/* Advertise Half Duplex	*/
#घोषणा PCS_MIIADV_SP	0x00000080	/* Advertise Symmetric Pause	*/
#घोषणा PCS_MIIADV_AP	0x00000100	/* Advertise Asymmetric Pause	*/
#घोषणा PCS_MIIADV_RF	0x00003000	/* Remote Fault			*/
#घोषणा PCS_MIIADV_ACK	0x00004000	/* Read-only			*/
#घोषणा PCS_MIIADV_NP	0x00008000	/* Next-page, क्रमced low	*/

/* PCS MII Link Partner Ability Register.   This रेजिस्टर is equivalent
 * to the Link Partnet Ability Register of the standard MII रेजिस्टर set.
 * It's layout corresponds to the PCS MII Advertisement Register.
 */

/* PCS Configuration Register. */
#घोषणा PCS_CFG_ENABLE	0x00000001	/* Must be zero जबतक changing
					 * PCS MII advertisement reg.
					 */
#घोषणा PCS_CFG_SDO	0x00000002	/* Signal detect override	*/
#घोषणा PCS_CFG_SDL	0x00000004	/* Signal detect active low	*/
#घोषणा PCS_CFG_JS	0x00000018	/* Jitter-study:
					 * 0 = normal operation
					 * 1 = high-frequency test pattern
					 * 2 = low-frequency test pattern
					 * 3 = reserved
					 */
#घोषणा PCS_CFG_TO	0x00000020	/* 10ms स्वतः-neg समयr override	*/

/* PCS Interrupt Status Register.  This रेजिस्टर is self-clearing
 * when पढ़ो.
 */
#घोषणा PCS_ISTAT_LSC	0x00000004	/* Link Status Change		*/

/* Datapath Mode Register. */
#घोषणा PCS_DMODE_SM	0x00000001	/* 1 = use पूर्णांकernal Serialink	*/
#घोषणा PCS_DMODE_ESM	0x00000002	/* External SERDES mode		*/
#घोषणा PCS_DMODE_MGM	0x00000004	/* MII/GMII mode		*/
#घोषणा PCS_DMODE_GMOE	0x00000008	/* GMII Output Enable		*/

/* Serialink Control Register.
 *
 * NOTE: When in SERDES mode, the loopback bit has inverse logic.
 */
#घोषणा PCS_SCTRL_LOOP	0x00000001	/* Loopback enable		*/
#घोषणा PCS_SCTRL_ESCD	0x00000002	/* Enable sync अक्षर detection	*/
#घोषणा PCS_SCTRL_LOCK	0x00000004	/* Lock to reference घड़ी	*/
#घोषणा PCS_SCTRL_EMP	0x00000018	/* Output driver emphasis	*/
#घोषणा PCS_SCTRL_STEST	0x000001c0	/* Self test patterns		*/
#घोषणा PCS_SCTRL_PDWN	0x00000200	/* Software घातer-करोwn		*/
#घोषणा PCS_SCTRL_RXZ	0x00000c00	/* PLL input to Serialink	*/
#घोषणा PCS_SCTRL_RXP	0x00003000	/* PLL input to Serialink	*/
#घोषणा PCS_SCTRL_TXZ	0x0000c000	/* PLL input to Serialink	*/
#घोषणा PCS_SCTRL_TXP	0x00030000	/* PLL input to Serialink	*/

/* Shared Output Select Register.  For test and debug, allows multiplexing
 * test outमाला_दो पूर्णांकo the PROM address pins.  Set to zero क्रम normal
 * operation.
 */
#घोषणा PCS_SOS_PADDR	0x00000003	/* PROM Address			*/

/* PROM Image Space */
#घोषणा PROM_START	0x100000UL	/* Expansion ROM run समय access*/
#घोषणा PROM_SIZE	0x0fffffUL	/* Size of ROM			*/
#घोषणा PROM_END	0x200000UL	/* End of ROM			*/

/* MII definitions missing from mii.h */

#घोषणा BMCR_SPD2	0x0040		/* Gigabit enable? (bcm5411)	*/
#घोषणा LPA_PAUSE	0x0400

/* More PHY रेजिस्टरs (specअगरic to Broadcom models) */

/* MII BCM5201 MULTIPHY पूर्णांकerrupt रेजिस्टर */
#घोषणा MII_BCM5201_INTERRUPT			0x1A
#घोषणा MII_BCM5201_INTERRUPT_INTENABLE		0x4000

#घोषणा MII_BCM5201_AUXMODE2			0x1B
#घोषणा MII_BCM5201_AUXMODE2_LOWPOWER		0x0008

#घोषणा MII_BCM5201_MULTIPHY                    0x1E

/* MII BCM5201 MULTIPHY रेजिस्टर bits */
#घोषणा MII_BCM5201_MULTIPHY_SERIALMODE         0x0002
#घोषणा MII_BCM5201_MULTIPHY_SUPERISOLATE       0x0008

/* MII BCM5400 1000-BASET Control रेजिस्टर */
#घोषणा MII_BCM5400_GB_CONTROL			0x09
#घोषणा MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP	0x0200

/* MII BCM5400 AUXCONTROL रेजिस्टर */
#घोषणा MII_BCM5400_AUXCONTROL                  0x18
#घोषणा MII_BCM5400_AUXCONTROL_PWR10BASET       0x0004

/* MII BCM5400 AUXSTATUS रेजिस्टर */
#घोषणा MII_BCM5400_AUXSTATUS                   0x19
#घोषणा MII_BCM5400_AUXSTATUS_LINKMODE_MASK     0x0700
#घोषणा MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT    8

/* When it can, GEM पूर्णांकernally caches 4 aligned TX descriptors
 * at a समय, so that it can use full cacheline DMA पढ़ोs.
 *
 * Note that unlike HME, there is no ownership bit in the descriptor
 * control word.  The same functionality is obtained via the TX-Kick
 * and TX-Complete रेजिस्टरs.  As a result, GEM need not ग_लिखो back
 * updated values to the TX descriptor ring, it only perक्रमms पढ़ोs.
 *
 * Since TX descriptors are never modअगरied by GEM, the driver can
 * use the buffer DMA address as a place to keep track of allocated
 * DMA mappings क्रम a transmitted packet.
 */
काष्ठा gem_txd अणु
	__le64	control_word;
	__le64	buffer;
पूर्ण;

#घोषणा TXDCTRL_BUFSZ	0x0000000000007fffULL	/* Buffer Size		*/
#घोषणा TXDCTRL_CSTART	0x00000000001f8000ULL	/* CSUM Start Offset	*/
#घोषणा TXDCTRL_COFF	0x000000001fe00000ULL	/* CSUM Stuff Offset	*/
#घोषणा TXDCTRL_CENAB	0x0000000020000000ULL	/* CSUM Enable		*/
#घोषणा TXDCTRL_खातापूर्ण	0x0000000040000000ULL	/* End of Frame		*/
#घोषणा TXDCTRL_SOF	0x0000000080000000ULL	/* Start of Frame	*/
#घोषणा TXDCTRL_INTME	0x0000000100000000ULL	/* "Interrupt Me"	*/
#घोषणा TXDCTRL_NOCRC	0x0000000200000000ULL	/* No CRC Present	*/

/* GEM requires that RX descriptors are provided four at a समय,
 * aligned.  Also, the RX ring may not wrap around.  This means that
 * there will be at least 4 unused descriptor entries in the middle
 * of the RX ring at all बार.
 *
 * Similar to HME, GEM assumes that it can ग_लिखो garbage bytes beक्रमe
 * the beginning of the buffer and right after the end in order to DMA
 * whole cachelines.
 *
 * Unlike क्रम TX, GEM करोes update the status word in the RX descriptors
 * when packets arrive.  Thereक्रमe an ownership bit करोes exist in the
 * RX descriptors.  It is advisory, GEM clears it but करोes not check
 * it in any way.  So when buffers are posted to the RX ring (via the
 * RX Kick रेजिस्टर) by the driver it must make sure the buffers are
 * truly पढ़ोy and that the ownership bits are set properly.
 *
 * Even though GEM modअगरies the RX descriptors, it guarantees that the
 * buffer DMA address field will stay the same when it perक्रमms these
 * updates.  Thereक्रमe it can be used to keep track of DMA mappings
 * by the host driver just as in the TX descriptor हाल above.
 */
काष्ठा gem_rxd अणु
	__le64	status_word;
	__le64	buffer;
पूर्ण;

#घोषणा RXDCTRL_TCPCSUM	0x000000000000ffffULL	/* TCP Pseuकरो-CSUM	*/
#घोषणा RXDCTRL_BUFSZ	0x000000007fff0000ULL	/* Buffer Size		*/
#घोषणा RXDCTRL_OWN	0x0000000080000000ULL	/* GEM owns this entry	*/
#घोषणा RXDCTRL_HASHVAL	0x0ffff00000000000ULL	/* Hash Value		*/
#घोषणा RXDCTRL_HPASS	0x1000000000000000ULL	/* Passed Hash Filter	*/
#घोषणा RXDCTRL_ALTMAC	0x2000000000000000ULL	/* Matched ALT MAC	*/
#घोषणा RXDCTRL_BAD	0x4000000000000000ULL	/* Frame has bad CRC	*/

#घोषणा RXDCTRL_FRESH(gp)	\
	((((RX_BUF_ALLOC_SIZE(gp) - RX_OFFSET) << 16) & RXDCTRL_BUFSZ) | \
	 RXDCTRL_OWN)

#घोषणा TX_RING_SIZE 128
#घोषणा RX_RING_SIZE 128

#अगर TX_RING_SIZE == 32
#घोषणा TXDMA_CFG_BASE	TXDMA_CFG_RINGSZ_32
#या_अगर TX_RING_SIZE == 64
#घोषणा TXDMA_CFG_BASE	TXDMA_CFG_RINGSZ_64
#या_अगर TX_RING_SIZE == 128
#घोषणा TXDMA_CFG_BASE	TXDMA_CFG_RINGSZ_128
#या_अगर TX_RING_SIZE == 256
#घोषणा TXDMA_CFG_BASE	TXDMA_CFG_RINGSZ_256
#या_अगर TX_RING_SIZE == 512
#घोषणा TXDMA_CFG_BASE	TXDMA_CFG_RINGSZ_512
#या_अगर TX_RING_SIZE == 1024
#घोषणा TXDMA_CFG_BASE	TXDMA_CFG_RINGSZ_1K
#या_अगर TX_RING_SIZE == 2048
#घोषणा TXDMA_CFG_BASE	TXDMA_CFG_RINGSZ_2K
#या_अगर TX_RING_SIZE == 4096
#घोषणा TXDMA_CFG_BASE	TXDMA_CFG_RINGSZ_4K
#या_अगर TX_RING_SIZE == 8192
#घोषणा TXDMA_CFG_BASE	TXDMA_CFG_RINGSZ_8K
#अन्यथा
#त्रुटि TX_RING_SIZE value is illegal...
#पूर्ण_अगर

#अगर RX_RING_SIZE == 32
#घोषणा RXDMA_CFG_BASE	RXDMA_CFG_RINGSZ_32
#या_अगर RX_RING_SIZE == 64
#घोषणा RXDMA_CFG_BASE	RXDMA_CFG_RINGSZ_64
#या_अगर RX_RING_SIZE == 128
#घोषणा RXDMA_CFG_BASE	RXDMA_CFG_RINGSZ_128
#या_अगर RX_RING_SIZE == 256
#घोषणा RXDMA_CFG_BASE	RXDMA_CFG_RINGSZ_256
#या_अगर RX_RING_SIZE == 512
#घोषणा RXDMA_CFG_BASE	RXDMA_CFG_RINGSZ_512
#या_अगर RX_RING_SIZE == 1024
#घोषणा RXDMA_CFG_BASE	RXDMA_CFG_RINGSZ_1K
#या_अगर RX_RING_SIZE == 2048
#घोषणा RXDMA_CFG_BASE	RXDMA_CFG_RINGSZ_2K
#या_अगर RX_RING_SIZE == 4096
#घोषणा RXDMA_CFG_BASE	RXDMA_CFG_RINGSZ_4K
#या_अगर RX_RING_SIZE == 8192
#घोषणा RXDMA_CFG_BASE	RXDMA_CFG_RINGSZ_8K
#अन्यथा
#त्रुटि RX_RING_SIZE is illegal...
#पूर्ण_अगर

#घोषणा NEXT_TX(N)	(((N) + 1) & (TX_RING_SIZE - 1))
#घोषणा NEXT_RX(N)	(((N) + 1) & (RX_RING_SIZE - 1))

#घोषणा TX_BUFFS_AVAIL(GP)					\
	(((GP)->tx_old <= (GP)->tx_new) ?			\
	  (GP)->tx_old + (TX_RING_SIZE - 1) - (GP)->tx_new :	\
	  (GP)->tx_old - (GP)->tx_new - 1)

#घोषणा RX_OFFSET          2
#घोषणा RX_BUF_ALLOC_SIZE(gp)	((gp)->rx_buf_sz + 28 + RX_OFFSET + 64)

#घोषणा RX_COPY_THRESHOLD  256

#अगर TX_RING_SIZE < 128
#घोषणा INIT_BLOCK_TX_RING_SIZE		128
#अन्यथा
#घोषणा INIT_BLOCK_TX_RING_SIZE		TX_RING_SIZE
#पूर्ण_अगर

#अगर RX_RING_SIZE < 128
#घोषणा INIT_BLOCK_RX_RING_SIZE		128
#अन्यथा
#घोषणा INIT_BLOCK_RX_RING_SIZE		RX_RING_SIZE
#पूर्ण_अगर

काष्ठा gem_init_block अणु
	काष्ठा gem_txd	txd[INIT_BLOCK_TX_RING_SIZE];
	काष्ठा gem_rxd	rxd[INIT_BLOCK_RX_RING_SIZE];
पूर्ण;

क्रमागत gem_phy_type अणु
	phy_mii_mdio0,
	phy_mii_mdio1,
	phy_serialink,
	phy_serdes,
पूर्ण;

क्रमागत link_state अणु
	link_करोwn = 0,	/* No link, will retry */
	link_aneg,	/* Autoneg in progress */
	link_क्रमce_try,	/* Try Forced link speed */
	link_क्रमce_ret,	/* Forced mode worked, retrying स्वतःneg */
	link_क्रमce_ok,	/* Stay in क्रमced mode */
	link_up		/* Link is up */
पूर्ण;

काष्ठा gem अणु
	व्योम __iomem		*regs;
	पूर्णांक			rx_new, rx_old;
	पूर्णांक			tx_new, tx_old;

	अचिन्हित पूर्णांक has_wol : 1;	/* chip supports wake-on-lan */
	अचिन्हित पूर्णांक asleep_wol : 1;	/* was asleep with WOL enabled */

	पूर्णांक			cell_enabled;
	u32			msg_enable;
	u32			status;

	काष्ठा napi_काष्ठा	napi;

	पूर्णांक			tx_fअगरo_sz;
	पूर्णांक			rx_fअगरo_sz;
	पूर्णांक			rx_छोड़ो_off;
	पूर्णांक			rx_छोड़ो_on;
	पूर्णांक			rx_buf_sz;
	u64			छोड़ो_entered;
	u16			छोड़ो_last_समय_recvd;
	u32			mac_rx_cfg;
	u32			swrst_base;

	पूर्णांक			want_स्वतःneg;
	पूर्णांक			last_क्रमced_speed;
	क्रमागत link_state		lstate;
	काष्ठा समयr_list	link_समयr;
	पूर्णांक			समयr_ticks;
	पूर्णांक			wake_on_lan;
	काष्ठा work_काष्ठा	reset_task;
	अस्थिर पूर्णांक		reset_task_pending;

	क्रमागत gem_phy_type	phy_type;
	काष्ठा mii_phy		phy_mii;
	पूर्णांक			mii_phy_addr;

	काष्ठा gem_init_block	*init_block;
	काष्ठा sk_buff		*rx_skbs[RX_RING_SIZE];
	काष्ठा sk_buff		*tx_skbs[TX_RING_SIZE];
	dma_addr_t		gblock_dvma;

	काष्ठा pci_dev		*pdev;
	काष्ठा net_device	*dev;
#अगर defined(CONFIG_PPC_PMAC) || defined(CONFIG_SPARC)
	काष्ठा device_node	*of_node;
#पूर्ण_अगर
पूर्ण;

#घोषणा found_mii_phy(gp) ((gp->phy_type == phy_mii_mdio0 || gp->phy_type == phy_mii_mdio1) && \
			   gp->phy_mii.def && gp->phy_mii.def->ops)

#पूर्ण_अगर /* _SUNGEM_H */
