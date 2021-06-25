<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Id: sunhme.h,v 1.33 2001/08/03 06:23:04 davem Exp $
 * sunhme.h: Definitions क्रम Sparc HME/BigMac 10/100baseT ethernet driver.
 *           Also known as the "Happy Meal".
 *
 * Copyright (C) 1996, 1999 David S. Miller (davem@redhat.com)
 */

#अगर_अघोषित _SUNHME_H
#घोषणा _SUNHME_H

#समावेश <linux/pci.h>

/* Happy Meal global रेजिस्टरs. */
#घोषणा GREG_SWRESET	0x000UL	/* Software Reset  */
#घोषणा GREG_CFG	0x004UL	/* Config Register */
#घोषणा GREG_STAT	0x100UL	/* Status          */
#घोषणा GREG_IMASK	0x104UL	/* Interrupt Mask  */
#घोषणा GREG_REG_SIZE	0x108UL

/* Global reset रेजिस्टर. */
#घोषणा GREG_RESET_ETX         0x01
#घोषणा GREG_RESET_ERX         0x02
#घोषणा GREG_RESET_ALL         0x03

/* Global config रेजिस्टर. */
#घोषणा GREG_CFG_BURSTMSK      0x03
#घोषणा GREG_CFG_BURST16       0x00
#घोषणा GREG_CFG_BURST32       0x01
#घोषणा GREG_CFG_BURST64       0x02
#घोषणा GREG_CFG_64BIT         0x04
#घोषणा GREG_CFG_PARITY        0x08
#घोषणा GREG_CFG_RESV          0x10

/* Global status रेजिस्टर. */
#घोषणा GREG_STAT_GOTFRAME     0x00000001 /* Received a frame                         */
#घोषणा GREG_STAT_RCNTEXP      0x00000002 /* Receive frame counter expired            */
#घोषणा GREG_STAT_ACNTEXP      0x00000004 /* Align-error counter expired              */
#घोषणा GREG_STAT_CCNTEXP      0x00000008 /* CRC-error counter expired                */
#घोषणा GREG_STAT_LCNTEXP      0x00000010 /* Length-error counter expired             */
#घोषणा GREG_STAT_RFIFOVF      0x00000020 /* Receive FIFO overflow                    */
#घोषणा GREG_STAT_CVCNTEXP     0x00000040 /* Code-violation counter expired           */
#घोषणा GREG_STAT_STSTERR      0x00000080 /* Test error in XIF क्रम SQE                */
#घोषणा GREG_STAT_SENTFRAME    0x00000100 /* Transmitted a frame                      */
#घोषणा GREG_STAT_TFIFO_UND    0x00000200 /* Transmit FIFO underrun                   */
#घोषणा GREG_STAT_MAXPKTERR    0x00000400 /* Max-packet size error                    */
#घोषणा GREG_STAT_NCNTEXP      0x00000800 /* Normal-collision counter expired         */
#घोषणा GREG_STAT_ECNTEXP      0x00001000 /* Excess-collision counter expired         */
#घोषणा GREG_STAT_LCCNTEXP     0x00002000 /* Late-collision counter expired           */
#घोषणा GREG_STAT_FCNTEXP      0x00004000 /* First-collision counter expired          */
#घोषणा GREG_STAT_DTIMEXP      0x00008000 /* Defer-समयr expired                      */
#घोषणा GREG_STAT_RXTOHOST     0x00010000 /* Moved from receive-FIFO to host memory   */
#घोषणा GREG_STAT_NORXD        0x00020000 /* No more receive descriptors              */
#घोषणा GREG_STAT_RXERR        0x00040000 /* Error during receive dma                 */
#घोषणा GREG_STAT_RXLATERR     0x00080000 /* Late error during receive dma            */
#घोषणा GREG_STAT_RXPERR       0x00100000 /* Parity error during receive dma          */
#घोषणा GREG_STAT_RXTERR       0x00200000 /* Tag error during receive dma             */
#घोषणा GREG_STAT_EOPERR       0x00400000 /* Transmit descriptor did not have EOP set */
#घोषणा GREG_STAT_MIFIRQ       0x00800000 /* MIF is संकेतing an पूर्णांकerrupt condition  */
#घोषणा GREG_STAT_HOSTTOTX     0x01000000 /* Moved from host memory to transmit-FIFO  */
#घोषणा GREG_STAT_TXALL        0x02000000 /* Transmitted all packets in the tx-fअगरo   */
#घोषणा GREG_STAT_TXEACK       0x04000000 /* Error during transmit dma                */
#घोषणा GREG_STAT_TXLERR       0x08000000 /* Late error during transmit dma           */
#घोषणा GREG_STAT_TXPERR       0x10000000 /* Parity error during transmit dma         */
#घोषणा GREG_STAT_TXTERR       0x20000000 /* Tag error during transmit dma            */
#घोषणा GREG_STAT_SLVERR       0x40000000 /* PIO access got an error                  */
#घोषणा GREG_STAT_SLVPERR      0x80000000 /* PIO access got a parity error            */

/* All पूर्णांकeresting error conditions. */
#घोषणा GREG_STAT_ERRORS       0xfc7efefc

/* Global पूर्णांकerrupt mask रेजिस्टर. */
#घोषणा GREG_IMASK_GOTFRAME    0x00000001 /* Received a frame                         */
#घोषणा GREG_IMASK_RCNTEXP     0x00000002 /* Receive frame counter expired            */
#घोषणा GREG_IMASK_ACNTEXP     0x00000004 /* Align-error counter expired              */
#घोषणा GREG_IMASK_CCNTEXP     0x00000008 /* CRC-error counter expired                */
#घोषणा GREG_IMASK_LCNTEXP     0x00000010 /* Length-error counter expired             */
#घोषणा GREG_IMASK_RFIFOVF     0x00000020 /* Receive FIFO overflow                    */
#घोषणा GREG_IMASK_CVCNTEXP    0x00000040 /* Code-violation counter expired           */
#घोषणा GREG_IMASK_STSTERR     0x00000080 /* Test error in XIF क्रम SQE                */
#घोषणा GREG_IMASK_SENTFRAME   0x00000100 /* Transmitted a frame                      */
#घोषणा GREG_IMASK_TFIFO_UND   0x00000200 /* Transmit FIFO underrun                   */
#घोषणा GREG_IMASK_MAXPKTERR   0x00000400 /* Max-packet size error                    */
#घोषणा GREG_IMASK_NCNTEXP     0x00000800 /* Normal-collision counter expired         */
#घोषणा GREG_IMASK_ECNTEXP     0x00001000 /* Excess-collision counter expired         */
#घोषणा GREG_IMASK_LCCNTEXP    0x00002000 /* Late-collision counter expired           */
#घोषणा GREG_IMASK_FCNTEXP     0x00004000 /* First-collision counter expired          */
#घोषणा GREG_IMASK_DTIMEXP     0x00008000 /* Defer-समयr expired                      */
#घोषणा GREG_IMASK_RXTOHOST    0x00010000 /* Moved from receive-FIFO to host memory   */
#घोषणा GREG_IMASK_NORXD       0x00020000 /* No more receive descriptors              */
#घोषणा GREG_IMASK_RXERR       0x00040000 /* Error during receive dma                 */
#घोषणा GREG_IMASK_RXLATERR    0x00080000 /* Late error during receive dma            */
#घोषणा GREG_IMASK_RXPERR      0x00100000 /* Parity error during receive dma          */
#घोषणा GREG_IMASK_RXTERR      0x00200000 /* Tag error during receive dma             */
#घोषणा GREG_IMASK_EOPERR      0x00400000 /* Transmit descriptor did not have EOP set */
#घोषणा GREG_IMASK_MIFIRQ      0x00800000 /* MIF is संकेतing an पूर्णांकerrupt condition  */
#घोषणा GREG_IMASK_HOSTTOTX    0x01000000 /* Moved from host memory to transmit-FIFO  */
#घोषणा GREG_IMASK_TXALL       0x02000000 /* Transmitted all packets in the tx-fअगरo   */
#घोषणा GREG_IMASK_TXEACK      0x04000000 /* Error during transmit dma                */
#घोषणा GREG_IMASK_TXLERR      0x08000000 /* Late error during transmit dma           */
#घोषणा GREG_IMASK_TXPERR      0x10000000 /* Parity error during transmit dma         */
#घोषणा GREG_IMASK_TXTERR      0x20000000 /* Tag error during transmit dma            */
#घोषणा GREG_IMASK_SLVERR      0x40000000 /* PIO access got an error                  */
#घोषणा GREG_IMASK_SLVPERR     0x80000000 /* PIO access got a parity error            */

/* Happy Meal बाह्यal transmitter रेजिस्टरs. */
#घोषणा ETX_PENDING	0x00UL	/* Transmit pending/wakeup रेजिस्टर */
#घोषणा ETX_CFG		0x04UL	/* Transmit config रेजिस्टर         */
#घोषणा ETX_RING	0x08UL	/* Transmit ring poपूर्णांकer            */
#घोषणा ETX_BBASE	0x0cUL	/* Transmit buffer base             */
#घोषणा ETX_BDISP	0x10UL	/* Transmit buffer displacement     */
#घोषणा ETX_FIFOWPTR	0x14UL	/* FIFO ग_लिखो ptr                   */
#घोषणा ETX_FIFOSWPTR	0x18UL	/* FIFO ग_लिखो ptr (shaकरोw रेजिस्टर) */
#घोषणा ETX_FIFORPTR	0x1cUL	/* FIFO पढ़ो ptr                    */
#घोषणा ETX_FIFOSRPTR	0x20UL	/* FIFO पढ़ो ptr (shaकरोw रेजिस्टर)  */
#घोषणा ETX_FIFOPCNT	0x24UL	/* FIFO packet counter              */
#घोषणा ETX_SMACHINE	0x28UL	/* Transmitter state machine        */
#घोषणा ETX_RSIZE	0x2cUL	/* Ring descriptor size             */
#घोषणा ETX_BPTR	0x30UL	/* Transmit data buffer ptr         */
#घोषणा ETX_REG_SIZE	0x34UL

/* ETX transmit pending रेजिस्टर. */
#घोषणा ETX_TP_DMAWAKEUP         0x00000001 /* Restart transmit dma             */

/* ETX config रेजिस्टर. */
#घोषणा ETX_CFG_DMAENABLE        0x00000001 /* Enable transmit dma              */
#घोषणा ETX_CFG_FIFOTHRESH       0x000003fe /* Transmit FIFO threshold          */
#घोषणा ETX_CFG_IRQDAFTER        0x00000400 /* Interrupt after TX-FIFO drained  */
#घोषणा ETX_CFG_IRQDBEFORE       0x00000000 /* Interrupt beक्रमe TX-FIFO drained */

#घोषणा ETX_RSIZE_SHIFT          4

/* Happy Meal बाह्यal receiver रेजिस्टरs. */
#घोषणा ERX_CFG		0x00UL	/* Receiver config रेजिस्टर         */
#घोषणा ERX_RING	0x04UL	/* Receiver ring ptr                */
#घोषणा ERX_BPTR	0x08UL	/* Receiver buffer ptr              */
#घोषणा ERX_FIFOWPTR	0x0cUL	/* FIFO ग_लिखो ptr                   */
#घोषणा ERX_FIFOSWPTR	0x10UL	/* FIFO ग_लिखो ptr (shaकरोw रेजिस्टर) */
#घोषणा ERX_FIFORPTR	0x14UL	/* FIFO पढ़ो ptr                    */
#घोषणा ERX_FIFOSRPTR	0x18UL	/* FIFO पढ़ो ptr (shaकरोw रेजिस्टर)  */
#घोषणा ERX_SMACHINE	0x1cUL	/* Receiver state machine           */
#घोषणा ERX_REG_SIZE	0x20UL

/* ERX config रेजिस्टर. */
#घोषणा ERX_CFG_DMAENABLE    0x00000001 /* Enable receive DMA        */
#घोषणा ERX_CFG_RESV1        0x00000006 /* Unused...                 */
#घोषणा ERX_CFG_BYTखातापूर्णFSET   0x00000038 /* Receive first byte offset */
#घोषणा ERX_CFG_RESV2        0x000001c0 /* Unused...                 */
#घोषणा ERX_CFG_SIZE32       0x00000000 /* Receive ring size == 32   */
#घोषणा ERX_CFG_SIZE64       0x00000200 /* Receive ring size == 64   */
#घोषणा ERX_CFG_SIZE128      0x00000400 /* Receive ring size == 128  */
#घोषणा ERX_CFG_SIZE256      0x00000600 /* Receive ring size == 256  */
#घोषणा ERX_CFG_RESV3        0x0000f800 /* Unused...                 */
#घोषणा ERX_CFG_CSUMSTART    0x007f0000 /* Offset of checksum start,
					 * in halfwords. */

/* I'd like a Big Mac, small fries, small coke, and SparcLinux please. */
#घोषणा BMAC_XIFCFG	0x0000UL	/* XIF config रेजिस्टर                */
	/* 0x4-->0x204, reserved */
#घोषणा BMAC_TXSWRESET	0x208UL	/* Transmitter software reset         */
#घोषणा BMAC_TXCFG	0x20cUL	/* Transmitter config रेजिस्टर        */
#घोषणा BMAC_IGAP1	0x210UL	/* Inter-packet gap 1                 */
#घोषणा BMAC_IGAP2	0x214UL	/* Inter-packet gap 2                 */
#घोषणा BMAC_ALIMIT	0x218UL	/* Transmit attempt limit             */
#घोषणा BMAC_STIME	0x21cUL	/* Transmit slot समय                 */
#घोषणा BMAC_PLEN	0x220UL	/* Size of transmit preamble          */
#घोषणा BMAC_PPAT	0x224UL	/* Pattern क्रम transmit preamble      */
#घोषणा BMAC_TXSDELIM	0x228UL	/* Transmit delimiter                 */
#घोषणा BMAC_JSIZE	0x22cUL	/* Jam size                           */
#घोषणा BMAC_TXMAX	0x230UL	/* Transmit max pkt size              */
#घोषणा BMAC_TXMIN	0x234UL	/* Transmit min pkt size              */
#घोषणा BMAC_PATTEMPT	0x238UL	/* Count of transmit peak attempts    */
#घोषणा BMAC_DTCTR	0x23cUL	/* Transmit defer समयr               */
#घोषणा BMAC_NCCTR	0x240UL	/* Transmit normal-collision counter  */
#घोषणा BMAC_FCCTR	0x244UL	/* Transmit first-collision counter   */
#घोषणा BMAC_EXCTR	0x248UL	/* Transmit excess-collision counter  */
#घोषणा BMAC_LTCTR	0x24cUL	/* Transmit late-collision counter    */
#घोषणा BMAC_RSEED	0x250UL	/* Transmit अक्रमom number seed        */
#घोषणा BMAC_TXSMACHINE	0x254UL	/* Transmit state machine             */
	/* 0x258-->0x304, reserved */
#घोषणा BMAC_RXSWRESET	0x308UL	/* Receiver software reset            */
#घोषणा BMAC_RXCFG	0x30cUL	/* Receiver config रेजिस्टर           */
#घोषणा BMAC_RXMAX	0x310UL	/* Receive max pkt size               */
#घोषणा BMAC_RXMIN	0x314UL	/* Receive min pkt size               */
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
#घोषणा BIGMAC_XCFG_ODENABLE  0x00000001 /* Output driver enable         */
#घोषणा BIGMAC_XCFG_XLBACK    0x00000002 /* Loopback-mode XIF enable     */
#घोषणा BIGMAC_XCFG_MLBACK    0x00000004 /* Loopback-mode MII enable     */
#घोषणा BIGMAC_XCFG_MIIDISAB  0x00000008 /* MII receive buffer disable   */
#घोषणा BIGMAC_XCFG_SQENABLE  0x00000010 /* SQE test enable              */
#घोषणा BIGMAC_XCFG_SQETWIN   0x000003e0 /* SQE समय winकरोw              */
#घोषणा BIGMAC_XCFG_LANCE     0x00000010 /* Lance mode enable            */
#घोषणा BIGMAC_XCFG_LIPG0     0x000003e0 /* Lance mode IPG0              */

/* BigMac transmit config रेजिस्टर. */
#घोषणा BIGMAC_TXCFG_ENABLE   0x00000001 /* Enable the transmitter       */
#घोषणा BIGMAC_TXCFG_SMODE    0x00000020 /* Enable slow transmit mode    */
#घोषणा BIGMAC_TXCFG_CIGN     0x00000040 /* Ignore transmit collisions   */
#घोषणा BIGMAC_TXCFG_FCSOFF   0x00000080 /* Do not emit FCS              */
#घोषणा BIGMAC_TXCFG_DBACKOFF 0x00000100 /* Disable backoff              */
#घोषणा BIGMAC_TXCFG_FULLDPLX 0x00000200 /* Enable full-duplex           */
#घोषणा BIGMAC_TXCFG_DGIVEUP  0x00000400 /* Don't give up on transmits   */

/* BigMac receive config रेजिस्टर. */
#घोषणा BIGMAC_RXCFG_ENABLE   0x00000001 /* Enable the receiver             */
#घोषणा BIGMAC_RXCFG_PSTRIP   0x00000020 /* Pad byte strip enable           */
#घोषणा BIGMAC_RXCFG_PMISC    0x00000040 /* Enable promiscuous mode          */
#घोषणा BIGMAC_RXCFG_DERR     0x00000080 /* Disable error checking          */
#घोषणा BIGMAC_RXCFG_DCRCS    0x00000100 /* Disable CRC stripping           */
#घोषणा BIGMAC_RXCFG_REJME    0x00000200 /* Reject packets addressed to me  */
#घोषणा BIGMAC_RXCFG_PGRP     0x00000400 /* Enable promisc group mode       */
#घोषणा BIGMAC_RXCFG_HENABLE  0x00000800 /* Enable the hash filter          */
#घोषणा BIGMAC_RXCFG_AENABLE  0x00001000 /* Enable the address filter       */

/* These are the "Management Interface" (ie. MIF) रेजिस्टरs of the transceiver. */
#घोषणा TCVR_BBCLOCK	0x00UL	/* Bit bang घड़ी रेजिस्टर          */
#घोषणा TCVR_BBDATA	0x04UL	/* Bit bang data रेजिस्टर           */
#घोषणा TCVR_BBOENAB	0x08UL	/* Bit bang output enable           */
#घोषणा TCVR_FRAME	0x0cUL	/* Frame control/data रेजिस्टर      */
#घोषणा TCVR_CFG	0x10UL	/* MIF config रेजिस्टर              */
#घोषणा TCVR_IMASK	0x14UL	/* MIF पूर्णांकerrupt mask               */
#घोषणा TCVR_STATUS	0x18UL	/* MIF status                       */
#घोषणा TCVR_SMACHINE	0x1cUL	/* MIF state machine                */
#घोषणा TCVR_REG_SIZE	0x20UL

/* Frame commands. */
#घोषणा FRAME_WRITE           0x50020000
#घोषणा FRAME_READ            0x60020000

/* Transceiver config रेजिस्टर */
#घोषणा TCV_CFG_PSELECT       0x00000001 /* Select PHY                      */
#घोषणा TCV_CFG_PENABLE       0x00000002 /* Enable MIF polling              */
#घोषणा TCV_CFG_BENABLE       0x00000004 /* Enable the "bit banger" oh baby */
#घोषणा TCV_CFG_PREGADDR      0x000000f8 /* Address of poll रेजिस्टर        */
#घोषणा TCV_CFG_MDIO0         0x00000100 /* MDIO zero, data/attached        */
#घोषणा TCV_CFG_MDIO1         0x00000200 /* MDIO one,  data/attached        */
#घोषणा TCV_CFG_PDADDR        0x00007c00 /* Device PHY address polling      */

/* Here are some PHY addresses. */
#घोषणा TCV_PADDR_ETX         0          /* Internal transceiver            */
#घोषणा TCV_PADDR_ITX         1          /* External transceiver            */

/* Transceiver status रेजिस्टर */
#घोषणा TCV_STAT_BASIC        0xffff0000 /* The "basic" part                */
#घोषणा TCV_STAT_NORMAL       0x0000ffff /* The "non-basic" part            */

/* Inside the Happy Meal transceiver is the physical layer, they use an
 * implementations क्रम National Semiconductor, part number DP83840VCE.
 * You can retrieve the data sheets and programming करोcs क्रम this beast
 * from http://www.national.com/
 *
 * The DP83840 is capable of both 10 and 100Mbps ethernet, in both
 * half and full duplex mode.  It also supports स्वतः negotiation.
 *
 * But.... THIS THING IS A PAIN IN THE ASS TO PROGRAM!
 * Debugging eeprom burnt code is more fun than programming this chip!
 */

/* Generic MII रेजिस्टरs defined in linux/mii.h, these below
 * are DP83840 specअगरic.
 */
#घोषणा DP83840_CSCONFIG        0x17        /* CS configuration            */

/* The Carrier Sense config रेजिस्टर. */
#घोषणा CSCONFIG_RESV1          0x0001  /* Unused...                   */
#घोषणा CSCONFIG_LED4           0x0002  /* Pin क्रम full-dplx LED4      */
#घोषणा CSCONFIG_LED1           0x0004  /* Pin क्रम conn-status LED1    */
#घोषणा CSCONFIG_RESV2          0x0008  /* Unused...                   */
#घोषणा CSCONFIG_TCVDISAB       0x0010  /* Turns off the transceiver   */
#घोषणा CSCONFIG_DFBYPASS       0x0020  /* Bypass disconnect function  */
#घोषणा CSCONFIG_GLFORCE        0x0040  /* Good link क्रमce क्रम 100mbps */
#घोषणा CSCONFIG_CLKTRISTATE    0x0080  /* Tristate 25m घड़ी          */
#घोषणा CSCONFIG_RESV3          0x0700  /* Unused...                   */
#घोषणा CSCONFIG_ENCODE         0x0800  /* 1=MLT-3, 0=binary           */
#घोषणा CSCONFIG_RENABLE        0x1000  /* Repeater mode enable        */
#घोषणा CSCONFIG_TCDISABLE      0x2000  /* Disable समयout counter     */
#घोषणा CSCONFIG_RESV4          0x4000  /* Unused...                   */
#घोषणा CSCONFIG_NDISABLE       0x8000  /* Disable NRZI                */

/* Happy Meal descriptor rings and such.
 * All descriptor rings must be aligned on a 2K boundary.
 * All receive buffers must be 64 byte aligned.
 * Always ग_लिखो the address first beक्रमe setting the ownership
 * bits to aव्योम races with the hardware scanning the ring.
 */
प्रकार u32 __bitwise hme32;

काष्ठा happy_meal_rxd अणु
	hme32 rx_flags;
	hme32 rx_addr;
पूर्ण;

#घोषणा RXFLAG_OWN         0x80000000 /* 1 = hardware, 0 = software */
#घोषणा RXFLAG_OVERFLOW    0x40000000 /* 1 = buffer overflow        */
#घोषणा RXFLAG_SIZE        0x3fff0000 /* Size of the buffer         */
#घोषणा RXFLAG_CSUM        0x0000ffff /* HW computed checksum       */

काष्ठा happy_meal_txd अणु
	hme32 tx_flags;
	hme32 tx_addr;
पूर्ण;

#घोषणा TXFLAG_OWN         0x80000000 /* 1 = hardware, 0 = software */
#घोषणा TXFLAG_SOP         0x40000000 /* 1 = start of packet        */
#घोषणा TXFLAG_EOP         0x20000000 /* 1 = end of packet          */
#घोषणा TXFLAG_CSENABLE    0x10000000 /* 1 = enable hw-checksums    */
#घोषणा TXFLAG_CSLOCATION  0x0ff00000 /* Where to stick the csum    */
#घोषणा TXFLAG_CSBUFBEGIN  0x000fc000 /* Where to begin checksum    */
#घोषणा TXFLAG_SIZE        0x00003fff /* Size of the packet         */

#घोषणा TX_RING_SIZE       32         /* Must be >16 and <255, multiple of 16  */
#घोषणा RX_RING_SIZE       32         /* see ERX_CFG_SIZE* क्रम possible values */

#अगर (TX_RING_SIZE < 16 || TX_RING_SIZE > 256 || (TX_RING_SIZE % 16) != 0)
#त्रुटि TX_RING_SIZE holds illegal value
#पूर्ण_अगर

#घोषणा TX_RING_MAXSIZE    256
#घोषणा RX_RING_MAXSIZE    256

/* We use a 14 byte offset क्रम checksum computation. */
#अगर (RX_RING_SIZE == 32)
#घोषणा ERX_CFG_DEFAULT(off) (ERX_CFG_DMAENABLE|((off)<<3)|ERX_CFG_SIZE32|((14/2)<<16))
#अन्यथा
#अगर (RX_RING_SIZE == 64)
#घोषणा ERX_CFG_DEFAULT(off) (ERX_CFG_DMAENABLE|((off)<<3)|ERX_CFG_SIZE64|((14/2)<<16))
#अन्यथा
#अगर (RX_RING_SIZE == 128)
#घोषणा ERX_CFG_DEFAULT(off) (ERX_CFG_DMAENABLE|((off)<<3)|ERX_CFG_SIZE128|((14/2)<<16))
#अन्यथा
#अगर (RX_RING_SIZE == 256)
#घोषणा ERX_CFG_DEFAULT(off) (ERX_CFG_DMAENABLE|((off)<<3)|ERX_CFG_SIZE256|((14/2)<<16))
#अन्यथा
#त्रुटि RX_RING_SIZE holds illegal value
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा NEXT_RX(num)       (((num) + 1) & (RX_RING_SIZE - 1))
#घोषणा NEXT_TX(num)       (((num) + 1) & (TX_RING_SIZE - 1))
#घोषणा PREV_RX(num)       (((num) - 1) & (RX_RING_SIZE - 1))
#घोषणा PREV_TX(num)       (((num) - 1) & (TX_RING_SIZE - 1))

#घोषणा TX_BUFFS_AVAIL(hp)                                    \
        (((hp)->tx_old <= (hp)->tx_new) ?                     \
	  (hp)->tx_old + (TX_RING_SIZE - 1) - (hp)->tx_new :  \
			    (hp)->tx_old - (hp)->tx_new - 1)

#घोषणा RX_OFFSET          2
#घोषणा RX_BUF_ALLOC_SIZE  (1546 + RX_OFFSET + 64)

#घोषणा RX_COPY_THRESHOLD  256

काष्ठा hmeal_init_block अणु
	काष्ठा happy_meal_rxd happy_meal_rxd[RX_RING_MAXSIZE];
	काष्ठा happy_meal_txd happy_meal_txd[TX_RING_MAXSIZE];
पूर्ण;

#घोषणा hblock_offset(mem, elem) \
((__u32)((अचिन्हित दीर्घ)(&(((काष्ठा hmeal_init_block *)0)->mem[elem]))))

/* Now software state stuff. */
क्रमागत happy_transceiver अणु
	बाह्यal = 0,
	पूर्णांकernal = 1,
	none     = 2,
पूर्ण;

/* Timer state engine. */
क्रमागत happy_समयr_state अणु
	arbरुको  = 0,  /* Waiting क्रम स्वतः negotiation to complete.          */
	lupरुको  = 1,  /* Auto-neg complete, aरुकोing link-up status.        */
	ltryरुको = 2,  /* Forcing try of all modes, from fastest to slowest. */
	asleep   = 3,  /* Time inactive.                                     */
पूर्ण;

काष्ठा quattro;

/* Happy happy, joy joy! */
काष्ठा happy_meal अणु
	व्योम __iomem	*gregs;			/* Happy meal global रेजिस्टरs       */
	काष्ठा hmeal_init_block  *happy_block;	/* RX and TX descriptors (CPU addr)  */

#अगर defined(CONFIG_SBUS) && defined(CONFIG_PCI)
	u32 (*पढ़ो_desc32)(hme32 *);
	व्योम (*ग_लिखो_txd)(काष्ठा happy_meal_txd *, u32, u32);
	व्योम (*ग_लिखो_rxd)(काष्ठा happy_meal_rxd *, u32, u32);
#पूर्ण_अगर

	/* This is either an platक्रमm_device or a pci_dev. */
	व्योम			  *happy_dev;
	काष्ठा device		  *dma_dev;

	spinlock_t		  happy_lock;

	काष्ठा sk_buff           *rx_skbs[RX_RING_SIZE];
	काष्ठा sk_buff           *tx_skbs[TX_RING_SIZE];

	पूर्णांक rx_new, tx_new, rx_old, tx_old;

#अगर defined(CONFIG_SBUS) && defined(CONFIG_PCI)
	u32 (*पढ़ो32)(व्योम __iomem *);
	व्योम (*ग_लिखो32)(व्योम __iomem *, u32);
#पूर्ण_अगर

	व्योम __iomem	*etxregs;        /* External transmitter regs        */
	व्योम __iomem	*erxregs;        /* External receiver regs           */
	व्योम __iomem	*bigmacregs;     /* BIGMAC core regs		     */
	व्योम __iomem	*tcvregs;        /* MIF transceiver regs             */

	dma_addr_t                hblock_dvma;    /* DVMA visible address happy block  */
	अचिन्हित पूर्णांक              happy_flags;    /* Driver state flags                */
	पूर्णांक                       irq;
	क्रमागत happy_transceiver    tcvr_type;      /* Kind of transceiver in use        */
	अचिन्हित पूर्णांक              happy_bursts;   /* Get your mind out of the gutter   */
	अचिन्हित पूर्णांक              paddr;          /* PHY address क्रम transceiver       */
	अचिन्हित लघु            hm_revision;    /* Happy meal revision               */
	अचिन्हित लघु            sw_bmcr;        /* SW copy of BMCR                   */
	अचिन्हित लघु            sw_bmsr;        /* SW copy of BMSR                   */
	अचिन्हित लघु            sw_physid1;     /* SW copy of PHYSID1                */
	अचिन्हित लघु            sw_physid2;     /* SW copy of PHYSID2                */
	अचिन्हित लघु            sw_advertise;   /* SW copy of ADVERTISE              */
	अचिन्हित लघु            sw_lpa;         /* SW copy of LPA                    */
	अचिन्हित लघु            sw_expansion;   /* SW copy of EXPANSION              */
	अचिन्हित लघु            sw_csconfig;    /* SW copy of CSCONFIG               */
	अचिन्हित पूर्णांक              स्वतः_speed;     /* Auto-nego link speed              */
        अचिन्हित पूर्णांक              क्रमced_speed;   /* Force mode link speed             */
	अचिन्हित पूर्णांक              poll_data;      /* MIF poll data                     */
	अचिन्हित पूर्णांक              poll_flag;      /* MIF poll flag                     */
	अचिन्हित पूर्णांक              linkcheck;      /* Have we checked the link yet?     */
	अचिन्हित पूर्णांक              lnkup;          /* Is the link up as far as we know? */
	अचिन्हित पूर्णांक              lnkकरोwn;        /* Trying to क्रमce the link करोwn?    */
	अचिन्हित पूर्णांक              lnkcnt;         /* Counter क्रम link-up attempts.     */
	काष्ठा समयr_list         happy_समयr;    /* To watch the link when coming up. */
	क्रमागत happy_समयr_state    समयr_state;    /* State of the स्वतः-neg समयr.      */
	अचिन्हित पूर्णांक              समयr_ticks;    /* Number of clicks at each state.   */

	काष्ठा net_device	 *dev;		/* Backpoपूर्णांकer                       */
	काष्ठा quattro		 *qfe_parent;	/* For Quattro cards                 */
	पूर्णांक			  qfe_ent;	/* Which instance on quattro         */
पूर्ण;

/* Here are the happy flags. */
#घोषणा HFLAG_POLL                0x00000001      /* We are करोing MIF polling          */
#घोषणा HFLAG_FENABLE             0x00000002      /* The MII frame is enabled          */
#घोषणा HFLAG_LANCE               0x00000004      /* We are using lance-mode           */
#घोषणा HFLAG_RXENABLE            0x00000008      /* Receiver is enabled               */
#घोषणा HFLAG_AUTO                0x00000010      /* Using स्वतः-negotiation, 0 = क्रमce */
#घोषणा HFLAG_FULL                0x00000020      /* Full duplex enable                */
#घोषणा HFLAG_MACFULL             0x00000040      /* Using full duplex in the MAC      */
#घोषणा HFLAG_POLLENABLE          0x00000080      /* Actually try MIF polling          */
#घोषणा HFLAG_RXCV                0x00000100      /* XXX RXCV ENABLE                   */
#घोषणा HFLAG_INIT                0x00000200      /* Init called at least once         */
#घोषणा HFLAG_LINKUP              0x00000400      /* 1 = Link is up                    */
#घोषणा HFLAG_PCI                 0x00000800      /* PCI based Happy Meal              */
#घोषणा HFLAG_QUATTRO		  0x00001000      /* On QFE/Quattro card	       */

#घोषणा HFLAG_20_21  (HFLAG_POLLENABLE | HFLAG_FENABLE)
#घोषणा HFLAG_NOT_A0 (HFLAG_POLLENABLE | HFLAG_FENABLE | HFLAG_LANCE | HFLAG_RXCV)

/* Support क्रम QFE/Quattro cards. */
काष्ठा quattro अणु
	काष्ठा net_device	*happy_meals[4];

	/* This is either a sbus_dev or a pci_dev. */
	व्योम			*quattro_dev;

	काष्ठा quattro		*next;

	/* PROM ranges, अगर any. */
#अगर_घोषित CONFIG_SBUS
	काष्ठा linux_prom_ranges  ranges[8];
#पूर्ण_अगर
	पूर्णांक			  nranges;
पूर्ण;

/* We use this to acquire receive skb's that we can DMA directly पूर्णांकo. */
#घोषणा ALIGNED_RX_SKB_ADDR(addr) \
        ((((अचिन्हित दीर्घ)(addr) + (64UL - 1UL)) & ~(64UL - 1UL)) - (अचिन्हित दीर्घ)(addr))
#घोषणा happy_meal_alloc_skb(__length, __gfp_flags) \
(अणु	काष्ठा sk_buff *__skb; \
	__skb = alloc_skb((__length) + 64, (__gfp_flags)); \
	अगर(__skb) अणु \
		पूर्णांक __offset = (पूर्णांक) ALIGNED_RX_SKB_ADDR(__skb->data); \
		अगर(__offset) \
			skb_reserve(__skb, __offset); \
	पूर्ण \
	__skb; \
पूर्ण)

#पूर्ण_अगर /* !(_SUNHME_H) */
