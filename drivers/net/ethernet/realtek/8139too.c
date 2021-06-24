<शैली गुरु>
/*

	8139too.c: A RealTek RTL-8139 Fast Ethernet driver क्रम Linux.

	Maपूर्णांकained by Jeff Garzik <jgarzik@pobox.com>
	Copyright 2000-2002 Jeff Garzik

	Much code comes from Donald Becker's rtl8139.c driver,
	versions 1.13 and older.  This driver was originally based
	on rtl8139.c version 1.07.  Header of rtl8139.c version 1.13:

	-----<snip>-----

        	Written 1997-2001 by Donald Becker.
		This software may be used and distributed according to the
		terms of the GNU General Public License (GPL), incorporated
		herein by reference.  Drivers based on or derived from this
		code fall under the GPL and must retain the authorship,
		copyright and license notice.  This file is not a complete
		program and may only be used when the entire operating
		प्रणाली is licensed under the GPL.

		This driver is क्रम boards based on the RTL8129 and RTL8139
		PCI ethernet chips.

		The author may be reached as becker@scyld.com, or C/O Scyld
		Computing Corporation 410 Severn Ave., Suite 210 Annapolis
		MD 21403

		Support and updates available at
		http://www.scyld.com/network/rtl8139.hपंचांगl

		Twister-tuning table provided by Kinston
		<shangh@realtek.com.tw>.

	-----<snip>-----

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	Contributors:

		Donald Becker - he wrote the original driver, kuकरोs to him!
		(but please करोn't e-mail him for support, this isn't his driver)

		Tigran Aivazian - bug fixes, skbuff मुक्त cleanup

		Martin Mares - suggestions क्रम PCI cleanup

		David S. Miller - PCI DMA and softnet updates

		Ernst Gill - fixes ported from BSD driver

		Daniel Kobras - identअगरied specअगरic locations of
			posted MMIO ग_लिखो bugginess

		Gerard Sharp - bug fix, testing and feedback

		David Ford - Rx ring wrap fix

		Dan DeMaggio - swapped RTL8139 cards with me, and allowed me
		to find and fix a crucial bug on older chipsets.

		Donald Becker/Chris Butterworth/Marcus Westergren -
		Noticed various Rx packet size-related buglets.

		Santiago Garcia Mantinan - testing and feedback

		Jens David - 2.2.x kernel backports

		Martin Dennett - incredibly helpful insight on unकरोcumented
		features of the 8139 chips

		Jean-Jacques Michel - bug fix

		Tobias Ringstrथघm - Rx पूर्णांकerrupt status checking suggestion

		Andrew Morton - Clear blocked संकेतs, aव्योम
		buffer overrun setting current->comm.

		Kalle Olavi Niemitalo - Wake-on-LAN ioctls

		Robert Kuebel - Save kernel thपढ़ो from dying on any संकेत.

	Submitting bug reports:

		"rtl8139-diag -mmmaaavvveefN" output
		enable RTL8139_DEBUG below, and look at 'dmesg' or kernel log

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"8139too"
#घोषणा DRV_VERSION	"0.9.28"


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/completion.h>
#समावेश <linux/crc32.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <यंत्र/irq.h>

#घोषणा RTL8139_DRIVER_NAME   DRV_NAME " Fast Ethernet driver " DRV_VERSION

/* Default Message level */
#घोषणा RTL8139_DEF_MSG_ENABLE   (NETIF_MSG_DRV   | \
                                 NETIF_MSG_PROBE  | \
                                 NETIF_MSG_LINK)


/* define to 1, 2 or 3 to enable copious debugging info */
#घोषणा RTL8139_DEBUG 0

/* define to 1 to disable lightweight runसमय debugging checks */
#अघोषित RTL8139_न_संशोधन


#अगर_घोषित RTL8139_न_संशोधन
#  define निश्चित(expr) करो अणुपूर्ण जबतक (0)
#अन्यथा
#  define निश्चित(expr) \
        अगर (unlikely(!(expr))) अणु				\
		pr_err("Assertion failed! %s,%s,%s,line=%d\n",	\
		       #expr, __खाता__, __func__, __LINE__);	\
        पूर्ण
#पूर्ण_अगर


/* A few user-configurable values. */
/* media options */
#घोषणा MAX_UNITS 8
अटल पूर्णांक media[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
अटल पूर्णांक full_duplex[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;

/* Whether to use MMIO or PIO. Default to MMIO. */
#अगर_घोषित CONFIG_8139TOO_PIO
अटल bool use_io = true;
#अन्यथा
अटल bool use_io = false;
#पूर्ण_अगर

/* Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
   The RTL chips use a 64 element hash table based on the Ethernet CRC.  */
अटल पूर्णांक multicast_filter_limit = 32;

/* biपंचांगapped message enable number */
अटल पूर्णांक debug = -1;

/*
 * Receive ring size
 * Warning: 64K ring has hardware issues and may lock up.
 */
#अगर defined(CONFIG_SH_DREAMCAST)
#घोषणा RX_BUF_IDX 0	/* 8K ring */
#अन्यथा
#घोषणा RX_BUF_IDX	2	/* 32K ring */
#पूर्ण_अगर
#घोषणा RX_BUF_LEN	(8192 << RX_BUF_IDX)
#घोषणा RX_BUF_PAD	16
#घोषणा RX_BUF_WRAP_PAD 2048 /* spare padding to handle lack of packet wrap */

#अगर RX_BUF_LEN == 65536
#घोषणा RX_BUF_TOT_LEN	RX_BUF_LEN
#अन्यथा
#घोषणा RX_BUF_TOT_LEN	(RX_BUF_LEN + RX_BUF_PAD + RX_BUF_WRAP_PAD)
#पूर्ण_अगर

/* Number of Tx descriptor रेजिस्टरs. */
#घोषणा NUM_TX_DESC	4

/* max supported ethernet frame size -- must be at least (dev->mtu+18+4).*/
#घोषणा MAX_ETH_FRAME_SIZE	1792

/* max supported payload size */
#घोषणा MAX_ETH_DATA_SIZE (MAX_ETH_FRAME_SIZE - VLAN_ETH_HLEN - ETH_FCS_LEN)

/* Size of the Tx bounce buffers -- must be at least (dev->mtu+18+4). */
#घोषणा TX_BUF_SIZE	MAX_ETH_FRAME_SIZE
#घोषणा TX_BUF_TOT_LEN	(TX_BUF_SIZE * NUM_TX_DESC)

/* PCI Tuning Parameters
   Threshold is bytes transferred to chip beक्रमe transmission starts. */
#घोषणा TX_FIFO_THRESH 256	/* In bytes, rounded करोwn to 32 byte units. */

/* The following settings are log_2(bytes)-4:  0 == 16 bytes .. 6==1024, 7==end of packet. */
#घोषणा RX_FIFO_THRESH	7	/* Rx buffer level beक्रमe first PCI xfer.  */
#घोषणा RX_DMA_BURST	7	/* Maximum PCI burst, '6' is 1024 */
#घोषणा TX_DMA_BURST	6	/* Maximum PCI burst, '6' is 1024 */
#घोषणा TX_RETRY	8	/* 0-15.  retries = 16 + (TX_RETRY * 16) */

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (6*HZ)


क्रमागत अणु
	HAS_MII_XCVR = 0x010000,
	HAS_CHIP_XCVR = 0x020000,
	HAS_LNK_CHNG = 0x040000,
पूर्ण;

#घोषणा RTL_NUM_STATS 4		/* number of ETHTOOL_GSTATS u64's */
#घोषणा RTL_REGS_VER 1		/* version of reg. data in ETHTOOL_GREGS */
#घोषणा RTL_MIN_IO_SIZE 0x80
#घोषणा RTL8139B_IO_SIZE 256

#घोषणा RTL8129_CAPS	HAS_MII_XCVR
#घोषणा RTL8139_CAPS	(HAS_CHIP_XCVR|HAS_LNK_CHNG)

प्रकार क्रमागत अणु
	RTL8139 = 0,
	RTL8129,
पूर्ण board_t;


/* indexed by board_t, above */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	u32 hw_flags;
पूर्ण board_info[] = अणु
	अणु "RealTek RTL8139", RTL8139_CAPS पूर्ण,
	अणु "RealTek RTL8129", RTL8129_CAPS पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा pci_device_id rtl8139_pci_tbl[] = अणु
	अणु0x10ec, 0x8139, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x10ec, 0x8138, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x1113, 0x1211, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x1500, 0x1360, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x4033, 0x1360, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x1186, 0x1300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x1186, 0x1340, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x13d1, 0xab06, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x1259, 0xa117, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x1259, 0xa11e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x14ea, 0xab06, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x14ea, 0xab07, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x11db, 0x1234, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x1432, 0x9130, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x02ac, 0x1012, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x018a, 0x0106, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x126c, 0x1211, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x1743, 0x8139, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x021b, 0x8139, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
	अणु0x16ec, 0xab06, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,

#अगर_घोषित CONFIG_SH_SECUREEDGE5410
	/* Bogus 8139 silicon reports 8129 without बाह्यal PROM :-( */
	अणु0x10ec, 0x8129, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8139 पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_8139TOO_8129
	अणु0x10ec, 0x8129, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8129 पूर्ण,
#पूर्ण_अगर

	/* some crazy cards report invalid venकरोr ids like
	 * 0x0001 here.  The other ids are valid and स्थिरant,
	 * so we simply करोn't match on the मुख्य venकरोr id.
	 */
	अणुPCI_ANY_ID, 0x8139, 0x10ec, 0x8139, 0, 0, RTL8139 पूर्ण,
	अणुPCI_ANY_ID, 0x8139, 0x1186, 0x1300, 0, 0, RTL8139 पूर्ण,
	अणुPCI_ANY_ID, 0x8139, 0x13d1, 0xab06, 0, 0, RTL8139 पूर्ण,

	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (pci, rtl8139_pci_tbl);

अटल काष्ठा अणु
	स्थिर अक्षर str[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "early_rx" पूर्ण,
	अणु "tx_buf_mapped" पूर्ण,
	अणु "tx_timeouts" पूर्ण,
	अणु "rx_lost_in_ring" पूर्ण,
पूर्ण;

/* The rest of these values should never change. */

/* Symbolic offsets to रेजिस्टरs. */
क्रमागत RTL8139_रेजिस्टरs अणु
	MAC0		= 0,	 /* Ethernet hardware address. */
	MAR0		= 8,	 /* Multicast filter. */
	TxStatus0	= 0x10,	 /* Transmit status (Four 32bit रेजिस्टरs). */
	TxAddr0		= 0x20,	 /* Tx descriptors (also four 32bit). */
	RxBuf		= 0x30,
	ChipCmd		= 0x37,
	RxBufPtr	= 0x38,
	RxBufAddr	= 0x3A,
	IntrMask	= 0x3C,
	IntrStatus	= 0x3E,
	TxConfig	= 0x40,
	RxConfig	= 0x44,
	Timer		= 0x48,	 /* A general-purpose counter. */
	RxMissed	= 0x4C,  /* 24 bits valid, ग_लिखो clears. */
	Cfg9346		= 0x50,
	Config0		= 0x51,
	Config1		= 0x52,
	TimerInt	= 0x54,
	MediaStatus	= 0x58,
	Config3		= 0x59,
	Config4		= 0x5A,	 /* असलent on RTL-8139A */
	HltClk		= 0x5B,
	MultiIntr	= 0x5C,
	TxSummary	= 0x60,
	BasicModeCtrl	= 0x62,
	BasicModeStatus	= 0x64,
	NWayAdvert	= 0x66,
	NWayLPAR	= 0x68,
	NWayExpansion	= 0x6A,
	/* Unकरोcumented रेजिस्टरs, but required क्रम proper operation. */
	FIFOTMS		= 0x70,	 /* FIFO Control and test. */
	CSCR		= 0x74,	 /* Chip Status and Configuration Register. */
	PARA78		= 0x78,
	FlashReg	= 0xD4,	/* Communication with Flash ROM, four bytes. */
	PARA7c		= 0x7c,	 /* Magic transceiver parameter रेजिस्टर. */
	Config5		= 0xD8,	 /* असलent on RTL-8139A */
पूर्ण;

क्रमागत ClearBitMasks अणु
	MultiIntrClear	= 0xF000,
	ChipCmdClear	= 0xE2,
	Config1Clear	= (1<<7)|(1<<6)|(1<<3)|(1<<2)|(1<<1),
पूर्ण;

क्रमागत ChipCmdBits अणु
	CmdReset	= 0x10,
	CmdRxEnb	= 0x08,
	CmdTxEnb	= 0x04,
	RxBufEmpty	= 0x01,
पूर्ण;

/* Interrupt रेजिस्टर bits, using my own meaningful names. */
क्रमागत IntrStatusBits अणु
	PCIErr		= 0x8000,
	PCSTimeout	= 0x4000,
	RxFIFOOver	= 0x40,
	RxUnderrun	= 0x20,
	RxOverflow	= 0x10,
	TxErr		= 0x08,
	TxOK		= 0x04,
	RxErr		= 0x02,
	RxOK		= 0x01,

	RxAckBits	= RxFIFOOver | RxOverflow | RxOK,
पूर्ण;

क्रमागत TxStatusBits अणु
	TxHostOwns	= 0x2000,
	TxUnderrun	= 0x4000,
	TxStatOK	= 0x8000,
	TxOutOfWinकरोw	= 0x20000000,
	TxAborted	= 0x40000000,
	TxCarrierLost	= 0x80000000,
पूर्ण;
क्रमागत RxStatusBits अणु
	RxMulticast	= 0x8000,
	RxPhysical	= 0x4000,
	RxBroadcast	= 0x2000,
	RxBadSymbol	= 0x0020,
	RxRunt		= 0x0010,
	RxTooLong	= 0x0008,
	RxCRCErr	= 0x0004,
	RxBadAlign	= 0x0002,
	RxStatusOK	= 0x0001,
पूर्ण;

/* Bits in RxConfig. */
क्रमागत rx_mode_bits अणु
	AcceptErr	= 0x20,
	AcceptRunt	= 0x10,
	AcceptBroadcast	= 0x08,
	AcceptMulticast	= 0x04,
	AcceptMyPhys	= 0x02,
	AcceptAllPhys	= 0x01,
पूर्ण;

/* Bits in TxConfig. */
क्रमागत tx_config_bits अणु
        /* Interframe Gap Time. Only TxIFG96 करोesn't violate IEEE 802.3 */
        TxIFGShअगरt	= 24,
        TxIFG84		= (0 << TxIFGShअगरt), /* 8.4us / 840ns (10 / 100Mbps) */
        TxIFG88		= (1 << TxIFGShअगरt), /* 8.8us / 880ns (10 / 100Mbps) */
        TxIFG92		= (2 << TxIFGShअगरt), /* 9.2us / 920ns (10 / 100Mbps) */
        TxIFG96		= (3 << TxIFGShअगरt), /* 9.6us / 960ns (10 / 100Mbps) */

	TxLoopBack	= (1 << 18) | (1 << 17), /* enable loopback test mode */
	TxCRC		= (1 << 16),	/* DISABLE Tx pkt CRC append */
	TxClearAbt	= (1 << 0),	/* Clear पात (WO) */
	TxDMAShअगरt	= 8, /* DMA burst value (0-7) is shअगरted X many bits */
	TxRetryShअगरt	= 4, /* TXRR value (0-15) is shअगरted X many bits */

	TxVersionMask	= 0x7C800000, /* mask out version bits 30-26, 23 */
पूर्ण;

/* Bits in Config1 */
क्रमागत Config1Bits अणु
	Cfg1_PM_Enable	= 0x01,
	Cfg1_VPD_Enable	= 0x02,
	Cfg1_PIO	= 0x04,
	Cfg1_MMIO	= 0x08,
	LWAKE		= 0x10,		/* not on 8139, 8139A */
	Cfg1_Driver_Load = 0x20,
	Cfg1_LED0	= 0x40,
	Cfg1_LED1	= 0x80,
	SLEEP		= (1 << 1),	/* only on 8139, 8139A */
	PWRDN		= (1 << 0),	/* only on 8139, 8139A */
पूर्ण;

/* Bits in Config3 */
क्रमागत Config3Bits अणु
	Cfg3_FBtBEn   	= (1 << 0), /* 1	= Fast Back to Back */
	Cfg3_FuncRegEn	= (1 << 1), /* 1	= enable CardBus Function रेजिस्टरs */
	Cfg3_CLKRUN_En	= (1 << 2), /* 1	= enable CLKRUN */
	Cfg3_CardB_En 	= (1 << 3), /* 1	= enable CardBus रेजिस्टरs */
	Cfg3_LinkUp   	= (1 << 4), /* 1	= wake up on link up */
	Cfg3_Magic    	= (1 << 5), /* 1	= wake up on Magic Packet (पंचांग) */
	Cfg3_PARM_En  	= (1 << 6), /* 0	= software can set twister parameters */
	Cfg3_GNTSel   	= (1 << 7), /* 1	= delay 1 घड़ी from PCI GNT संकेत */
पूर्ण;

/* Bits in Config4 */
क्रमागत Config4Bits अणु
	LWPTN	= (1 << 2),	/* not on 8139, 8139A */
पूर्ण;

/* Bits in Config5 */
क्रमागत Config5Bits अणु
	Cfg5_PME_STS   	= (1 << 0), /* 1	= PCI reset resets PME_Status */
	Cfg5_LANWake   	= (1 << 1), /* 1	= enable LANWake संकेत */
	Cfg5_LDPS      	= (1 << 2), /* 0	= save घातer when link is करोwn */
	Cfg5_FIFOAddrPtr= (1 << 3), /* Realtek पूर्णांकernal SRAM testing */
	Cfg5_UWF        = (1 << 4), /* 1 = accept unicast wakeup frame */
	Cfg5_MWF        = (1 << 5), /* 1 = accept multicast wakeup frame */
	Cfg5_BWF        = (1 << 6), /* 1 = accept broadcast wakeup frame */
पूर्ण;

क्रमागत RxConfigBits अणु
	/* rx fअगरo threshold */
	RxCfgFIFOShअगरt	= 13,
	RxCfgFIFONone	= (7 << RxCfgFIFOShअगरt),

	/* Max DMA burst */
	RxCfgDMAShअगरt	= 8,
	RxCfgDMAUnlimited = (7 << RxCfgDMAShअगरt),

	/* rx ring buffer length */
	RxCfgRcv8K	= 0,
	RxCfgRcv16K	= (1 << 11),
	RxCfgRcv32K	= (1 << 12),
	RxCfgRcv64K	= (1 << 11) | (1 << 12),

	/* Disable packet wrap at end of Rx buffer. (not possible with 64k) */
	RxNoWrap	= (1 << 7),
पूर्ण;

/* Twister tuning parameters from RealTek.
   Completely unकरोcumented, but required to tune bad links on some boards. */
क्रमागत CSCRBits अणु
	CSCR_LinkOKBit		= 0x0400,
	CSCR_LinkChangeBit	= 0x0800,
	CSCR_LinkStatusBits	= 0x0f000,
	CSCR_LinkDownOffCmd	= 0x003c0,
	CSCR_LinkDownCmd	= 0x0f3c0,
पूर्ण;

क्रमागत Cfg9346Bits अणु
	Cfg9346_Lock	= 0x00,
	Cfg9346_Unlock	= 0xC0,
पूर्ण;

प्रकार क्रमागत अणु
	CH_8139	= 0,
	CH_8139_K,
	CH_8139A,
	CH_8139A_G,
	CH_8139B,
	CH_8130,
	CH_8139C,
	CH_8100,
	CH_8100B_8139D,
	CH_8101,
पूर्ण chip_t;

क्रमागत chip_flags अणु
	HasHltClk	= (1 << 0),
	HasLWake	= (1 << 1),
पूर्ण;

#घोषणा HW_REVID(b30, b29, b28, b27, b26, b23, b22) \
	(b30<<30 | b29<<29 | b28<<28 | b27<<27 | b26<<26 | b23<<23 | b22<<22)
#घोषणा HW_REVID_MASK	HW_REVID(1, 1, 1, 1, 1, 1, 1)

/* directly indexed by chip_t, above */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	u32 version; /* from RTL8139C/RTL8139D करोcs */
	u32 flags;
पूर्ण rtl_chip_info[] = अणु
	अणु "RTL-8139",
	  HW_REVID(1, 0, 0, 0, 0, 0, 0),
	  HasHltClk,
	पूर्ण,

	अणु "RTL-8139 rev K",
	  HW_REVID(1, 1, 0, 0, 0, 0, 0),
	  HasHltClk,
	पूर्ण,

	अणु "RTL-8139A",
	  HW_REVID(1, 1, 1, 0, 0, 0, 0),
	  HasHltClk, /* XXX unकरोcumented? */
	पूर्ण,

	अणु "RTL-8139A rev G",
	  HW_REVID(1, 1, 1, 0, 0, 1, 0),
	  HasHltClk, /* XXX unकरोcumented? */
	पूर्ण,

	अणु "RTL-8139B",
	  HW_REVID(1, 1, 1, 1, 0, 0, 0),
	  HasLWake,
	पूर्ण,

	अणु "RTL-8130",
	  HW_REVID(1, 1, 1, 1, 1, 0, 0),
	  HasLWake,
	पूर्ण,

	अणु "RTL-8139C",
	  HW_REVID(1, 1, 1, 0, 1, 0, 0),
	  HasLWake,
	पूर्ण,

	अणु "RTL-8100",
	  HW_REVID(1, 1, 1, 1, 0, 1, 0),
 	  HasLWake,
 	पूर्ण,

	अणु "RTL-8100B/8139D",
	  HW_REVID(1, 1, 1, 0, 1, 0, 1),
	  HasHltClk /* XXX unकरोcumented? */
	| HasLWake,
	पूर्ण,

	अणु "RTL-8101",
	  HW_REVID(1, 1, 1, 0, 1, 1, 1),
	  HasLWake,
	पूर्ण,
पूर्ण;

काष्ठा rtl_extra_stats अणु
	अचिन्हित दीर्घ early_rx;
	अचिन्हित दीर्घ tx_buf_mapped;
	अचिन्हित दीर्घ tx_समयouts;
	अचिन्हित दीर्घ rx_lost_in_ring;
पूर्ण;

काष्ठा rtl8139_stats अणु
	u64	packets;
	u64	bytes;
	काष्ठा u64_stats_sync	syncp;
पूर्ण;

काष्ठा rtl8139_निजी अणु
	व्योम __iomem		*mmio_addr;
	पूर्णांक			drv_flags;
	काष्ठा pci_dev		*pci_dev;
	u32			msg_enable;
	काष्ठा napi_काष्ठा	napi;
	काष्ठा net_device	*dev;

	अचिन्हित अक्षर		*rx_ring;
	अचिन्हित पूर्णांक		cur_rx;	/* RX buf index of next pkt */
	काष्ठा rtl8139_stats	rx_stats;
	dma_addr_t		rx_ring_dma;

	अचिन्हित पूर्णांक		tx_flag;
	अचिन्हित दीर्घ		cur_tx;
	अचिन्हित दीर्घ		dirty_tx;
	काष्ठा rtl8139_stats	tx_stats;
	अचिन्हित अक्षर		*tx_buf[NUM_TX_DESC];	/* Tx bounce buffers */
	अचिन्हित अक्षर		*tx_bufs;	/* Tx bounce buffer region. */
	dma_addr_t		tx_bufs_dma;

	चिन्हित अक्षर		phys[4];	/* MII device addresses. */

				/* Twister tune state. */
	अक्षर			twistie, twist_row, twist_col;

	अचिन्हित पूर्णांक		watchकरोg_fired : 1;
	अचिन्हित पूर्णांक		शेष_port : 4; /* Last dev->अगर_port value. */
	अचिन्हित पूर्णांक		have_thपढ़ो : 1;

	spinlock_t		lock;
	spinlock_t		rx_lock;

	chip_t			chipset;
	u32			rx_config;
	काष्ठा rtl_extra_stats	xstats;

	काष्ठा delayed_work	thपढ़ो;

	काष्ठा mii_अगर_info	mii;
	अचिन्हित पूर्णांक		regs_len;
	अचिन्हित दीर्घ		fअगरo_copy_समयout;
पूर्ण;

MODULE_AUTHOR ("Jeff Garzik <jgarzik@pobox.com>");
MODULE_DESCRIPTION ("RealTek RTL-8139 Fast Ethernet driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

module_param(use_io, bool, 0);
MODULE_PARM_DESC(use_io, "Force use of I/O access mode. 0=MMIO 1=PIO");
module_param(multicast_filter_limit, पूर्णांक, 0);
module_param_array(media, पूर्णांक, शून्य, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC (debug, "8139too bitmapped message enable number");
MODULE_PARM_DESC (multicast_filter_limit, "8139too maximum number of filtered multicast addresses");
MODULE_PARM_DESC (media, "8139too: Bits 4+9: force full duplex, bit 5: 100Mbps");
MODULE_PARM_DESC (full_duplex, "8139too: Force full duplex for board(s) (1)");

अटल पूर्णांक पढ़ो_eeprom (व्योम __iomem *ioaddr, पूर्णांक location, पूर्णांक addr_len);
अटल पूर्णांक rtl8139_खोलो (काष्ठा net_device *dev);
अटल पूर्णांक mdio_पढ़ो (काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो (काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location,
			पूर्णांक val);
अटल व्योम rtl8139_start_thपढ़ो(काष्ठा rtl8139_निजी *tp);
अटल व्योम rtl8139_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम rtl8139_init_ring (काष्ठा net_device *dev);
अटल netdev_tx_t rtl8139_start_xmit (काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम rtl8139_poll_controller(काष्ठा net_device *dev);
#पूर्ण_अगर
अटल पूर्णांक rtl8139_set_mac_address(काष्ठा net_device *dev, व्योम *p);
अटल पूर्णांक rtl8139_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
अटल irqवापस_t rtl8139_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_instance);
अटल पूर्णांक rtl8139_बंद (काष्ठा net_device *dev);
अटल पूर्णांक netdev_ioctl (काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल व्योम rtl8139_get_stats64(काष्ठा net_device *dev,
				काष्ठा rtnl_link_stats64 *stats);
अटल व्योम rtl8139_set_rx_mode (काष्ठा net_device *dev);
अटल व्योम __set_rx_mode (काष्ठा net_device *dev);
अटल व्योम rtl8139_hw_start (काष्ठा net_device *dev);
अटल व्योम rtl8139_thपढ़ो (काष्ठा work_काष्ठा *work);
अटल व्योम rtl8139_tx_समयout_task(काष्ठा work_काष्ठा *work);
अटल स्थिर काष्ठा ethtool_ops rtl8139_ethtool_ops;

/* ग_लिखो MMIO रेजिस्टर, with flush */
/* Flush aव्योमs rtl8139 bug w/ posted MMIO ग_लिखोs */
#घोषणा RTL_W8_F(reg, val8)	करो अणु ioग_लिखो8 ((val8), ioaddr + (reg)); ioपढ़ो8 (ioaddr + (reg)); पूर्ण जबतक (0)
#घोषणा RTL_W16_F(reg, val16)	करो अणु ioग_लिखो16 ((val16), ioaddr + (reg)); ioपढ़ो16 (ioaddr + (reg)); पूर्ण जबतक (0)
#घोषणा RTL_W32_F(reg, val32)	करो अणु ioग_लिखो32 ((val32), ioaddr + (reg)); ioपढ़ो32 (ioaddr + (reg)); पूर्ण जबतक (0)

/* ग_लिखो MMIO रेजिस्टर */
#घोषणा RTL_W8(reg, val8)	ioग_लिखो8 ((val8), ioaddr + (reg))
#घोषणा RTL_W16(reg, val16)	ioग_लिखो16 ((val16), ioaddr + (reg))
#घोषणा RTL_W32(reg, val32)	ioग_लिखो32 ((val32), ioaddr + (reg))

/* पढ़ो MMIO रेजिस्टर */
#घोषणा RTL_R8(reg)		ioपढ़ो8 (ioaddr + (reg))
#घोषणा RTL_R16(reg)		ioपढ़ो16 (ioaddr + (reg))
#घोषणा RTL_R32(reg)		ioपढ़ो32 (ioaddr + (reg))


अटल स्थिर u16 rtl8139_पूर्णांकr_mask =
	PCIErr | PCSTimeout | RxUnderrun | RxOverflow | RxFIFOOver |
	TxErr | TxOK | RxErr | RxOK;

अटल स्थिर u16 rtl8139_norx_पूर्णांकr_mask =
	PCIErr | PCSTimeout | RxUnderrun |
	TxErr | TxOK | RxErr ;

#अगर RX_BUF_IDX == 0
अटल स्थिर अचिन्हित पूर्णांक rtl8139_rx_config =
	RxCfgRcv8K | RxNoWrap |
	(RX_FIFO_THRESH << RxCfgFIFOShअगरt) |
	(RX_DMA_BURST << RxCfgDMAShअगरt);
#या_अगर RX_BUF_IDX == 1
अटल स्थिर अचिन्हित पूर्णांक rtl8139_rx_config =
	RxCfgRcv16K | RxNoWrap |
	(RX_FIFO_THRESH << RxCfgFIFOShअगरt) |
	(RX_DMA_BURST << RxCfgDMAShअगरt);
#या_अगर RX_BUF_IDX == 2
अटल स्थिर अचिन्हित पूर्णांक rtl8139_rx_config =
	RxCfgRcv32K | RxNoWrap |
	(RX_FIFO_THRESH << RxCfgFIFOShअगरt) |
	(RX_DMA_BURST << RxCfgDMAShअगरt);
#या_अगर RX_BUF_IDX == 3
अटल स्थिर अचिन्हित पूर्णांक rtl8139_rx_config =
	RxCfgRcv64K |
	(RX_FIFO_THRESH << RxCfgFIFOShअगरt) |
	(RX_DMA_BURST << RxCfgDMAShअगरt);
#अन्यथा
#त्रुटि "Invalid configuration for 8139_RXBUF_IDX"
#पूर्ण_अगर

अटल स्थिर अचिन्हित पूर्णांक rtl8139_tx_config =
	TxIFG96 | (TX_DMA_BURST << TxDMAShअगरt) | (TX_RETRY << TxRetryShअगरt);

अटल व्योम __rtl8139_cleanup_dev (काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	काष्ठा pci_dev *pdev;

	निश्चित (dev != शून्य);
	निश्चित (tp->pci_dev != शून्य);
	pdev = tp->pci_dev;

	अगर (tp->mmio_addr)
		pci_iounmap (pdev, tp->mmio_addr);

	/* it's ok to call this even अगर we have no regions to मुक्त */
	pci_release_regions (pdev);

	मुक्त_netdev(dev);
पूर्ण


अटल व्योम rtl8139_chip_reset (व्योम __iomem *ioaddr)
अणु
	पूर्णांक i;

	/* Soft reset the chip. */
	RTL_W8 (ChipCmd, CmdReset);

	/* Check that the chip has finished the reset. */
	क्रम (i = 1000; i > 0; i--) अणु
		barrier();
		अगर ((RTL_R8 (ChipCmd) & CmdReset) == 0)
			अवरोध;
		udelay (10);
	पूर्ण
पूर्ण


अटल काष्ठा net_device *rtl8139_init_board(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *d = &pdev->dev;
	व्योम __iomem *ioaddr;
	काष्ठा net_device *dev;
	काष्ठा rtl8139_निजी *tp;
	u8 पंचांगp8;
	पूर्णांक rc, disable_dev_on_err = 0;
	अचिन्हित पूर्णांक i, bar;
	अचिन्हित दीर्घ io_len;
	u32 version;
	अटल स्थिर काष्ठा अणु
		अचिन्हित दीर्घ mask;
		अक्षर *type;
	पूर्ण res[] = अणु
		अणु IORESOURCE_IO,  "PIO" पूर्ण,
		अणु IORESOURCE_MEM, "MMIO" पूर्ण
	पूर्ण;

	निश्चित (pdev != शून्य);

	/* dev and priv zeroed in alloc_etherdev */
	dev = alloc_etherdev (माप (*tp));
	अगर (dev == शून्य)
		वापस ERR_PTR(-ENOMEM);

	SET_NETDEV_DEV(dev, &pdev->dev);

	tp = netdev_priv(dev);
	tp->pci_dev = pdev;

	/* enable device (incl. PCI PM wakeup and hotplug setup) */
	rc = pci_enable_device (pdev);
	अगर (rc)
		जाओ err_out;

	disable_dev_on_err = 1;
	rc = pci_request_regions (pdev, DRV_NAME);
	अगर (rc)
		जाओ err_out;

	pci_set_master (pdev);

	u64_stats_init(&tp->rx_stats.syncp);
	u64_stats_init(&tp->tx_stats.syncp);

retry:
	/* PIO bar रेजिस्टर comes first. */
	bar = !use_io;

	io_len = pci_resource_len(pdev, bar);

	dev_dbg(d, "%s region size = 0x%02lX\n", res[bar].type, io_len);

	अगर (!(pci_resource_flags(pdev, bar) & res[bar].mask)) अणु
		dev_err(d, "region #%d not a %s resource, aborting\n", bar,
			res[bar].type);
		rc = -ENODEV;
		जाओ err_out;
	पूर्ण
	अगर (io_len < RTL_MIN_IO_SIZE) अणु
		dev_err(d, "Invalid PCI %s region size(s), aborting\n",
			res[bar].type);
		rc = -ENODEV;
		जाओ err_out;
	पूर्ण

	ioaddr = pci_iomap(pdev, bar, 0);
	अगर (!ioaddr) अणु
		dev_err(d, "cannot map %s\n", res[bar].type);
		अगर (!use_io) अणु
			use_io = true;
			जाओ retry;
		पूर्ण
		rc = -ENODEV;
		जाओ err_out;
	पूर्ण
	tp->regs_len = io_len;
	tp->mmio_addr = ioaddr;

	/* Bring old chips out of low-घातer mode. */
	RTL_W8 (HltClk, 'R');

	/* check क्रम missing/broken hardware */
	अगर (RTL_R32 (TxConfig) == 0xFFFFFFFF) अणु
		dev_err(&pdev->dev, "Chip not responding, ignoring board\n");
		rc = -EIO;
		जाओ err_out;
	पूर्ण

	/* identअगरy chip attached to board */
	version = RTL_R32 (TxConfig) & HW_REVID_MASK;
	क्रम (i = 0; i < ARRAY_SIZE (rtl_chip_info); i++)
		अगर (version == rtl_chip_info[i].version) अणु
			tp->chipset = i;
			जाओ match;
		पूर्ण

	/* अगर unknown chip, assume array element #0, original RTL-8139 in this हाल */
	i = 0;
	dev_dbg(&pdev->dev, "unknown chip version, assuming RTL-8139\n");
	dev_dbg(&pdev->dev, "TxConfig = 0x%x\n", RTL_R32 (TxConfig));
	tp->chipset = 0;

match:
	pr_debug("chipset id (%d) == index %d, '%s'\n",
		 version, i, rtl_chip_info[i].name);

	अगर (tp->chipset >= CH_8139B) अणु
		u8 new_पंचांगp8 = पंचांगp8 = RTL_R8 (Config1);
		pr_debug("PCI PM wakeup\n");
		अगर ((rtl_chip_info[tp->chipset].flags & HasLWake) &&
		    (पंचांगp8 & LWAKE))
			new_पंचांगp8 &= ~LWAKE;
		new_पंचांगp8 |= Cfg1_PM_Enable;
		अगर (new_पंचांगp8 != पंचांगp8) अणु
			RTL_W8 (Cfg9346, Cfg9346_Unlock);
			RTL_W8 (Config1, पंचांगp8);
			RTL_W8 (Cfg9346, Cfg9346_Lock);
		पूर्ण
		अगर (rtl_chip_info[tp->chipset].flags & HasLWake) अणु
			पंचांगp8 = RTL_R8 (Config4);
			अगर (पंचांगp8 & LWPTN) अणु
				RTL_W8 (Cfg9346, Cfg9346_Unlock);
				RTL_W8 (Config4, पंचांगp8 & ~LWPTN);
				RTL_W8 (Cfg9346, Cfg9346_Lock);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_debug("Old chip wakeup\n");
		पंचांगp8 = RTL_R8 (Config1);
		पंचांगp8 &= ~(SLEEP | PWRDN);
		RTL_W8 (Config1, पंचांगp8);
	पूर्ण

	rtl8139_chip_reset (ioaddr);

	वापस dev;

err_out:
	__rtl8139_cleanup_dev (dev);
	अगर (disable_dev_on_err)
		pci_disable_device (pdev);
	वापस ERR_PTR(rc);
पूर्ण

अटल पूर्णांक rtl8139_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	netdev_features_t changed = features ^ dev->features;
	व्योम __iomem *ioaddr = tp->mmio_addr;

	अगर (!(changed & (NETIF_F_RXALL)))
		वापस 0;

	spin_lock_irqsave(&tp->lock, flags);

	अगर (changed & NETIF_F_RXALL) अणु
		पूर्णांक rx_mode = tp->rx_config;
		अगर (features & NETIF_F_RXALL)
			rx_mode |= (AcceptErr | AcceptRunt);
		अन्यथा
			rx_mode &= ~(AcceptErr | AcceptRunt);
		tp->rx_config = rtl8139_rx_config | rx_mode;
		RTL_W32_F(RxConfig, tp->rx_config);
	पूर्ण

	spin_unlock_irqrestore(&tp->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops rtl8139_netdev_ops = अणु
	.nकरो_खोलो		= rtl8139_खोलो,
	.nकरो_stop		= rtl8139_बंद,
	.nकरो_get_stats64	= rtl8139_get_stats64,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= rtl8139_set_mac_address,
	.nकरो_start_xmit		= rtl8139_start_xmit,
	.nकरो_set_rx_mode	= rtl8139_set_rx_mode,
	.nकरो_करो_ioctl		= netdev_ioctl,
	.nकरो_tx_समयout		= rtl8139_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= rtl8139_poll_controller,
#पूर्ण_अगर
	.nकरो_set_features	= rtl8139_set_features,
पूर्ण;

अटल पूर्णांक rtl8139_init_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा rtl8139_निजी *tp;
	पूर्णांक i, addr_len, option;
	व्योम __iomem *ioaddr;
	अटल पूर्णांक board_idx = -1;

	निश्चित (pdev != शून्य);
	निश्चित (ent != शून्य);

	board_idx++;

	/* when we're built पूर्णांकo the kernel, the driver version message
	 * is only prपूर्णांकed अगर at least one 8139 board has been found
	 */
#अगर_अघोषित MODULE
	अणु
		अटल पूर्णांक prपूर्णांकed_version;
		अगर (!prपूर्णांकed_version++)
			pr_info(RTL8139_DRIVER_NAME "\n");
	पूर्ण
#पूर्ण_अगर

	अगर (pdev->venकरोr == PCI_VENDOR_ID_REALTEK &&
	    pdev->device == PCI_DEVICE_ID_REALTEK_8139 && pdev->revision >= 0x20) अणु
		dev_info(&pdev->dev,
			   "This (id %04x:%04x rev %02x) is an enhanced 8139C+ chip, use 8139cp\n",
		       	   pdev->venकरोr, pdev->device, pdev->revision);
		वापस -ENODEV;
	पूर्ण

	अगर (pdev->venकरोr == PCI_VENDOR_ID_REALTEK &&
	    pdev->device == PCI_DEVICE_ID_REALTEK_8139 &&
	    pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_ATHEROS &&
	    pdev->subप्रणाली_device == PCI_DEVICE_ID_REALTEK_8139) अणु
		pr_info("OQO Model 2 detected. Forcing PIO\n");
		use_io = true;
	पूर्ण

	dev = rtl8139_init_board (pdev);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	निश्चित (dev != शून्य);
	tp = netdev_priv(dev);
	tp->dev = dev;

	ioaddr = tp->mmio_addr;
	निश्चित (ioaddr != शून्य);

	addr_len = पढ़ो_eeprom (ioaddr, 0, 8) == 0x8129 ? 8 : 6;
	क्रम (i = 0; i < 3; i++)
		((__le16 *) (dev->dev_addr))[i] =
		    cpu_to_le16(पढ़ो_eeprom (ioaddr, i + 7, addr_len));

	/* The Rtl8139-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &rtl8139_netdev_ops;
	dev->ethtool_ops = &rtl8139_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	netअगर_napi_add(dev, &tp->napi, rtl8139_poll, 64);

	/* note: the hardware is not capable of sg/csum/highdma, however
	 * through the use of skb_copy_and_csum_dev we enable these
	 * features
	 */
	dev->features |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_HIGHDMA;
	dev->vlan_features = dev->features;

	dev->hw_features |= NETIF_F_RXALL;
	dev->hw_features |= NETIF_F_RXFCS;

	/* MTU range: 68 - 1770 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = MAX_ETH_DATA_SIZE;

	/* tp zeroed and aligned in alloc_etherdev */
	tp = netdev_priv(dev);

	/* note: tp->chipset set in rtl8139_init_board */
	tp->drv_flags = board_info[ent->driver_data].hw_flags;
	tp->mmio_addr = ioaddr;
	tp->msg_enable =
		(debug < 0 ? RTL8139_DEF_MSG_ENABLE : ((1 << debug) - 1));
	spin_lock_init (&tp->lock);
	spin_lock_init (&tp->rx_lock);
	INIT_DELAYED_WORK(&tp->thपढ़ो, rtl8139_thपढ़ो);
	tp->mii.dev = dev;
	tp->mii.mdio_पढ़ो = mdio_पढ़ो;
	tp->mii.mdio_ग_लिखो = mdio_ग_लिखो;
	tp->mii.phy_id_mask = 0x3f;
	tp->mii.reg_num_mask = 0x1f;

	/* dev is fully set up and पढ़ोy to use now */
	pr_debug("about to register device named %s (%p)...\n",
		 dev->name, dev);
	i = रेजिस्टर_netdev (dev);
	अगर (i) जाओ err_out;

	pci_set_drvdata (pdev, dev);

	netdev_info(dev, "%s at 0x%p, %pM, IRQ %d\n",
		    board_info[ent->driver_data].name,
		    ioaddr, dev->dev_addr, pdev->irq);

	netdev_dbg(dev, "Identified 8139 chip type '%s'\n",
		   rtl_chip_info[tp->chipset].name);

	/* Find the connected MII xcvrs.
	   Doing this in खोलो() would allow detecting बाह्यal xcvrs later, but
	   takes too much समय. */
#अगर_घोषित CONFIG_8139TOO_8129
	अगर (tp->drv_flags & HAS_MII_XCVR) अणु
		पूर्णांक phy, phy_idx = 0;
		क्रम (phy = 0; phy < 32 && phy_idx < माप(tp->phys); phy++) अणु
			पूर्णांक mii_status = mdio_पढ़ो(dev, phy, 1);
			अगर (mii_status != 0xffff  &&  mii_status != 0x0000) अणु
				u16 advertising = mdio_पढ़ो(dev, phy, 4);
				tp->phys[phy_idx++] = phy;
				netdev_info(dev, "MII transceiver %d status 0x%04x advertising %04x\n",
					    phy, mii_status, advertising);
			पूर्ण
		पूर्ण
		अगर (phy_idx == 0) अणु
			netdev_info(dev, "No MII transceivers found! Assuming SYM transceiver\n");
			tp->phys[0] = 32;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
		tp->phys[0] = 32;
	tp->mii.phy_id = tp->phys[0];

	/* The lower four bits are the media type. */
	option = (board_idx >= MAX_UNITS) ? 0 : media[board_idx];
	अगर (option > 0) अणु
		tp->mii.full_duplex = (option & 0x210) ? 1 : 0;
		tp->शेष_port = option & 0xFF;
		अगर (tp->शेष_port)
			tp->mii.क्रमce_media = 1;
	पूर्ण
	अगर (board_idx < MAX_UNITS  &&  full_duplex[board_idx] > 0)
		tp->mii.full_duplex = full_duplex[board_idx];
	अगर (tp->mii.full_duplex) अणु
		netdev_info(dev, "Media type forced to Full Duplex\n");
		/* Changing the MII-advertised media because might prevent
		   re-connection. */
		tp->mii.क्रमce_media = 1;
	पूर्ण
	अगर (tp->शेष_port) अणु
		netdev_info(dev, "  Forcing %dMbps %s-duplex operation\n",
			    (option & 0x20 ? 100 : 10),
			    (option & 0x10 ? "full" : "half"));
		mdio_ग_लिखो(dev, tp->phys[0], 0,
				   ((option & 0x20) ? 0x2000 : 0) | 	/* 100Mbps? */
				   ((option & 0x10) ? 0x0100 : 0)); /* Full duplex? */
	पूर्ण

	/* Put the chip पूर्णांकo low-घातer mode. */
	अगर (rtl_chip_info[tp->chipset].flags & HasHltClk)
		RTL_W8 (HltClk, 'H');	/* 'R' would leave the घड़ी running. */

	वापस 0;

err_out:
	__rtl8139_cleanup_dev (dev);
	pci_disable_device (pdev);
	वापस i;
पूर्ण


अटल व्योम rtl8139_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata (pdev);
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);

	निश्चित (dev != शून्य);

	cancel_delayed_work_sync(&tp->thपढ़ो);

	unरेजिस्टर_netdev (dev);

	__rtl8139_cleanup_dev (dev);
	pci_disable_device (pdev);
पूर्ण


/* Serial EEPROM section. */

/*  EEPROM_Ctrl bits. */
#घोषणा EE_SHIFT_CLK	0x04	/* EEPROM shअगरt घड़ी. */
#घोषणा EE_CS			0x08	/* EEPROM chip select. */
#घोषणा EE_DATA_WRITE	0x02	/* EEPROM chip data in. */
#घोषणा EE_WRITE_0		0x00
#घोषणा EE_WRITE_1		0x02
#घोषणा EE_DATA_READ	0x01	/* EEPROM chip data out. */
#घोषणा EE_ENB			(0x80 | EE_CS)

/* Delay between EEPROM घड़ी transitions.
   No extra delay is needed with 33Mhz PCI, but 66Mhz may change this.
 */

#घोषणा eeprom_delay()	(व्योम)RTL_R8(Cfg9346)

/* The EEPROM commands include the alway-set leading bit. */
#घोषणा EE_WRITE_CMD	(5)
#घोषणा EE_READ_CMD		(6)
#घोषणा EE_ERASE_CMD	(7)

अटल पूर्णांक पढ़ो_eeprom(व्योम __iomem *ioaddr, पूर्णांक location, पूर्णांक addr_len)
अणु
	पूर्णांक i;
	अचिन्हित retval = 0;
	पूर्णांक पढ़ो_cmd = location | (EE_READ_CMD << addr_len);

	RTL_W8 (Cfg9346, EE_ENB & ~EE_CS);
	RTL_W8 (Cfg9346, EE_ENB);
	eeprom_delay ();

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 4 + addr_len; i >= 0; i--) अणु
		पूर्णांक dataval = (पढ़ो_cmd & (1 << i)) ? EE_DATA_WRITE : 0;
		RTL_W8 (Cfg9346, EE_ENB | dataval);
		eeprom_delay ();
		RTL_W8 (Cfg9346, EE_ENB | dataval | EE_SHIFT_CLK);
		eeprom_delay ();
	पूर्ण
	RTL_W8 (Cfg9346, EE_ENB);
	eeprom_delay ();

	क्रम (i = 16; i > 0; i--) अणु
		RTL_W8 (Cfg9346, EE_ENB | EE_SHIFT_CLK);
		eeprom_delay ();
		retval =
		    (retval << 1) | ((RTL_R8 (Cfg9346) & EE_DATA_READ) ? 1 :
				     0);
		RTL_W8 (Cfg9346, EE_ENB);
		eeprom_delay ();
	पूर्ण

	/* Terminate the EEPROM access. */
	RTL_W8(Cfg9346, 0);
	eeprom_delay ();

	वापस retval;
पूर्ण

/* MII serial management: mostly bogus क्रम now. */
/* Read and ग_लिखो the MII management रेजिस्टरs using software-generated
   serial MDIO protocol.
   The maximum data घड़ी rate is 2.5 Mhz.  The minimum timing is usually
   met by back-to-back PCI I/O cycles, but we insert a delay to aव्योम
   "overclocking" issues. */
#घोषणा MDIO_सूची		0x80
#घोषणा MDIO_DATA_OUT	0x04
#घोषणा MDIO_DATA_IN	0x02
#घोषणा MDIO_CLK		0x01
#घोषणा MDIO_WRITE0 (MDIO_सूची)
#घोषणा MDIO_WRITE1 (MDIO_सूची | MDIO_DATA_OUT)

#घोषणा mdio_delay()	RTL_R8(Config4)


अटल स्थिर अक्षर mii_2_8139_map[8] = अणु
	BasicModeCtrl,
	BasicModeStatus,
	0,
	0,
	NWayAdvert,
	NWayLPAR,
	NWayExpansion,
	0
पूर्ण;


#अगर_घोषित CONFIG_8139TOO_8129
/* Syncronize the MII management पूर्णांकerface by shअगरting 32 one bits out. */
अटल व्योम mdio_sync (व्योम __iomem *ioaddr)
अणु
	पूर्णांक i;

	क्रम (i = 32; i >= 0; i--) अणु
		RTL_W8 (Config4, MDIO_WRITE1);
		mdio_delay ();
		RTL_W8 (Config4, MDIO_WRITE1 | MDIO_CLK);
		mdio_delay ();
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mdio_पढ़ो (काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	पूर्णांक retval = 0;
#अगर_घोषित CONFIG_8139TOO_8129
	व्योम __iomem *ioaddr = tp->mmio_addr;
	पूर्णांक mii_cmd = (0xf6 << 10) | (phy_id << 5) | location;
	पूर्णांक i;
#पूर्ण_अगर

	अगर (phy_id > 31) अणु	/* Really a 8139.  Use पूर्णांकernal रेजिस्टरs. */
		व्योम __iomem *ioaddr = tp->mmio_addr;
		वापस location < 8 && mii_2_8139_map[location] ?
		    RTL_R16 (mii_2_8139_map[location]) : 0;
	पूर्ण

#अगर_घोषित CONFIG_8139TOO_8129
	mdio_sync (ioaddr);
	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 15; i >= 0; i--) अणु
		पूर्णांक dataval = (mii_cmd & (1 << i)) ? MDIO_DATA_OUT : 0;

		RTL_W8 (Config4, MDIO_सूची | dataval);
		mdio_delay ();
		RTL_W8 (Config4, MDIO_सूची | dataval | MDIO_CLK);
		mdio_delay ();
	पूर्ण

	/* Read the two transition, 16 data, and wire-idle bits. */
	क्रम (i = 19; i > 0; i--) अणु
		RTL_W8 (Config4, 0);
		mdio_delay ();
		retval = (retval << 1) | ((RTL_R8 (Config4) & MDIO_DATA_IN) ? 1 : 0);
		RTL_W8 (Config4, MDIO_CLK);
		mdio_delay ();
	पूर्ण
#पूर्ण_अगर

	वापस (retval >> 1) & 0xffff;
पूर्ण


अटल व्योम mdio_ग_लिखो (काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location,
			पूर्णांक value)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
#अगर_घोषित CONFIG_8139TOO_8129
	व्योम __iomem *ioaddr = tp->mmio_addr;
	पूर्णांक mii_cmd = (0x5002 << 16) | (phy_id << 23) | (location << 18) | value;
	पूर्णांक i;
#पूर्ण_अगर

	अगर (phy_id > 31) अणु	/* Really a 8139.  Use पूर्णांकernal रेजिस्टरs. */
		व्योम __iomem *ioaddr = tp->mmio_addr;
		अगर (location == 0) अणु
			RTL_W8 (Cfg9346, Cfg9346_Unlock);
			RTL_W16 (BasicModeCtrl, value);
			RTL_W8 (Cfg9346, Cfg9346_Lock);
		पूर्ण अन्यथा अगर (location < 8 && mii_2_8139_map[location])
			RTL_W16 (mii_2_8139_map[location], value);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_8139TOO_8129
	mdio_sync (ioaddr);

	/* Shअगरt the command bits out. */
	क्रम (i = 31; i >= 0; i--) अणु
		पूर्णांक dataval =
		    (mii_cmd & (1 << i)) ? MDIO_WRITE1 : MDIO_WRITE0;
		RTL_W8 (Config4, dataval);
		mdio_delay ();
		RTL_W8 (Config4, dataval | MDIO_CLK);
		mdio_delay ();
	पूर्ण
	/* Clear out extra bits. */
	क्रम (i = 2; i > 0; i--) अणु
		RTL_W8 (Config4, 0);
		mdio_delay ();
		RTL_W8 (Config4, MDIO_CLK);
		mdio_delay ();
	पूर्ण
#पूर्ण_अगर
पूर्ण


अटल पूर्णांक rtl8139_खोलो (काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	स्थिर पूर्णांक irq = tp->pci_dev->irq;
	पूर्णांक retval;

	retval = request_irq(irq, rtl8139_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (retval)
		वापस retval;

	tp->tx_bufs = dma_alloc_coherent(&tp->pci_dev->dev, TX_BUF_TOT_LEN,
					   &tp->tx_bufs_dma, GFP_KERNEL);
	tp->rx_ring = dma_alloc_coherent(&tp->pci_dev->dev, RX_BUF_TOT_LEN,
					   &tp->rx_ring_dma, GFP_KERNEL);
	अगर (tp->tx_bufs == शून्य || tp->rx_ring == शून्य) अणु
		मुक्त_irq(irq, dev);

		अगर (tp->tx_bufs)
			dma_मुक्त_coherent(&tp->pci_dev->dev, TX_BUF_TOT_LEN,
					    tp->tx_bufs, tp->tx_bufs_dma);
		अगर (tp->rx_ring)
			dma_मुक्त_coherent(&tp->pci_dev->dev, RX_BUF_TOT_LEN,
					    tp->rx_ring, tp->rx_ring_dma);

		वापस -ENOMEM;

	पूर्ण

	napi_enable(&tp->napi);

	tp->mii.full_duplex = tp->mii.क्रमce_media;
	tp->tx_flag = (TX_FIFO_THRESH << 11) & 0x003f0000;

	rtl8139_init_ring (dev);
	rtl8139_hw_start (dev);
	netअगर_start_queue (dev);

	netअगर_dbg(tp, अगरup, dev,
		  "%s() ioaddr %#llx IRQ %d GP Pins %02x %s-duplex\n",
		  __func__,
		  (अचिन्हित दीर्घ दीर्घ)pci_resource_start (tp->pci_dev, 1),
		  irq, RTL_R8 (MediaStatus),
		  tp->mii.full_duplex ? "full" : "half");

	rtl8139_start_thपढ़ो(tp);

	वापस 0;
पूर्ण


अटल व्योम rtl_check_media (काष्ठा net_device *dev, अचिन्हित पूर्णांक init_media)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);

	अगर (tp->phys[0] >= 0) अणु
		mii_check_media(&tp->mii, netअगर_msg_link(tp), init_media);
	पूर्ण
पूर्ण

/* Start the hardware at खोलो or resume. */
अटल व्योम rtl8139_hw_start (काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u32 i;
	u8 पंचांगp;

	/* Bring old chips out of low-घातer mode. */
	अगर (rtl_chip_info[tp->chipset].flags & HasHltClk)
		RTL_W8 (HltClk, 'R');

	rtl8139_chip_reset (ioaddr);

	/* unlock Config[01234] and BMCR रेजिस्टर ग_लिखोs */
	RTL_W8_F (Cfg9346, Cfg9346_Unlock);
	/* Restore our idea of the MAC address. */
	RTL_W32_F (MAC0 + 0, le32_to_cpu (*(__le32 *) (dev->dev_addr + 0)));
	RTL_W32_F (MAC0 + 4, le16_to_cpu (*(__le16 *) (dev->dev_addr + 4)));

	tp->cur_rx = 0;

	/* init Rx ring buffer DMA address */
	RTL_W32_F (RxBuf, tp->rx_ring_dma);

	/* Must enable Tx/Rx beक्रमe setting transfer thresholds! */
	RTL_W8 (ChipCmd, CmdRxEnb | CmdTxEnb);

	tp->rx_config = rtl8139_rx_config | AcceptBroadcast | AcceptMyPhys;
	RTL_W32 (RxConfig, tp->rx_config);
	RTL_W32 (TxConfig, rtl8139_tx_config);

	rtl_check_media (dev, 1);

	अगर (tp->chipset >= CH_8139B) अणु
		/* Disable magic packet scanning, which is enabled
		 * when PM is enabled in Config1.  It can be reenabled
		 * via ETHTOOL_SWOL अगर desired.  */
		RTL_W8 (Config3, RTL_R8 (Config3) & ~Cfg3_Magic);
	पूर्ण

	netdev_dbg(dev, "init buffer addresses\n");

	/* Lock Config[01234] and BMCR रेजिस्टर ग_लिखोs */
	RTL_W8 (Cfg9346, Cfg9346_Lock);

	/* init Tx buffer DMA addresses */
	क्रम (i = 0; i < NUM_TX_DESC; i++)
		RTL_W32_F (TxAddr0 + (i * 4), tp->tx_bufs_dma + (tp->tx_buf[i] - tp->tx_bufs));

	RTL_W32 (RxMissed, 0);

	rtl8139_set_rx_mode (dev);

	/* no early-rx पूर्णांकerrupts */
	RTL_W16 (MultiIntr, RTL_R16 (MultiIntr) & MultiIntrClear);

	/* make sure RxTx has started */
	पंचांगp = RTL_R8 (ChipCmd);
	अगर ((!(पंचांगp & CmdRxEnb)) || (!(पंचांगp & CmdTxEnb)))
		RTL_W8 (ChipCmd, CmdRxEnb | CmdTxEnb);

	/* Enable all known पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	RTL_W16 (IntrMask, rtl8139_पूर्णांकr_mask);
पूर्ण


/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल व्योम rtl8139_init_ring (काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	पूर्णांक i;

	tp->cur_rx = 0;
	tp->cur_tx = 0;
	tp->dirty_tx = 0;

	क्रम (i = 0; i < NUM_TX_DESC; i++)
		tp->tx_buf[i] = &tp->tx_bufs[i * TX_BUF_SIZE];
पूर्ण


/* This must be global क्रम CONFIG_8139TOO_TUNE_TWISTER हाल */
अटल पूर्णांक next_tick = 3 * HZ;

#अगर_अघोषित CONFIG_8139TOO_TUNE_TWISTER
अटल अंतरभूत व्योम rtl8139_tune_twister (काष्ठा net_device *dev,
				  काष्ठा rtl8139_निजी *tp) अणुपूर्ण
#अन्यथा
क्रमागत TwisterParamVals अणु
	PARA78_शेष	= 0x78fa8388,
	PARA7c_शेष	= 0xcb38de43,	/* param[0][3] */
	PARA7c_xxx	= 0xcb38de43,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ param[4][4] = अणु
	अणु0xcb39de43, 0xcb39ce43, 0xfb38de03, 0xcb38de43पूर्ण,
	अणु0xcb39de43, 0xcb39ce43, 0xcb39ce83, 0xcb39ce83पूर्ण,
	अणु0xcb39de43, 0xcb39ce43, 0xcb39ce83, 0xcb39ce83पूर्ण,
	अणु0xbb39de43, 0xbb39ce43, 0xbb39ce83, 0xbb39ce83पूर्ण
पूर्ण;

अटल व्योम rtl8139_tune_twister (काष्ठा net_device *dev,
				  काष्ठा rtl8139_निजी *tp)
अणु
	पूर्णांक linkहाल;
	व्योम __iomem *ioaddr = tp->mmio_addr;

	/* This is a complicated state machine to configure the "twister" क्रम
	   impedance/echos based on the cable length.
	   All of this is magic and unकरोcumented.
	 */
	चयन (tp->twistie) अणु
	हाल 1:
		अगर (RTL_R16 (CSCR) & CSCR_LinkOKBit) अणु
			/* We have link beat, let us tune the twister. */
			RTL_W16 (CSCR, CSCR_LinkDownOffCmd);
			tp->twistie = 2;	/* Change to state 2. */
			next_tick = HZ / 10;
		पूर्ण अन्यथा अणु
			/* Just put in some reasonable शेषs क्रम when beat वापसs. */
			RTL_W16 (CSCR, CSCR_LinkDownCmd);
			RTL_W32 (FIFOTMS, 0x20);	/* Turn on cable test mode. */
			RTL_W32 (PARA78, PARA78_शेष);
			RTL_W32 (PARA7c, PARA7c_शेष);
			tp->twistie = 0;	/* Bail from future actions. */
		पूर्ण
		अवरोध;
	हाल 2:
		/* Read how दीर्घ it took to hear the echo. */
		linkहाल = RTL_R16 (CSCR) & CSCR_LinkStatusBits;
		अगर (linkहाल == 0x7000)
			tp->twist_row = 3;
		अन्यथा अगर (linkहाल == 0x3000)
			tp->twist_row = 2;
		अन्यथा अगर (linkहाल == 0x1000)
			tp->twist_row = 1;
		अन्यथा
			tp->twist_row = 0;
		tp->twist_col = 0;
		tp->twistie = 3;	/* Change to state 2. */
		next_tick = HZ / 10;
		अवरोध;
	हाल 3:
		/* Put out four tuning parameters, one per 100msec. */
		अगर (tp->twist_col == 0)
			RTL_W16 (FIFOTMS, 0);
		RTL_W32 (PARA7c, param[(पूर्णांक) tp->twist_row]
			 [(पूर्णांक) tp->twist_col]);
		next_tick = HZ / 10;
		अगर (++tp->twist_col >= 4) अणु
			/* For लघु cables we are करोne.
			   For दीर्घ cables (row == 3) check क्रम mistune. */
			tp->twistie =
			    (tp->twist_row == 3) ? 4 : 0;
		पूर्ण
		अवरोध;
	हाल 4:
		/* Special हाल क्रम दीर्घ cables: check क्रम mistune. */
		अगर ((RTL_R16 (CSCR) &
		     CSCR_LinkStatusBits) == 0x7000) अणु
			tp->twistie = 0;
			अवरोध;
		पूर्ण अन्यथा अणु
			RTL_W32 (PARA7c, 0xfb38de03);
			tp->twistie = 5;
			next_tick = HZ / 10;
		पूर्ण
		अवरोध;
	हाल 5:
		/* Retune क्रम लघुer cable (column 2). */
		RTL_W32 (FIFOTMS, 0x20);
		RTL_W32 (PARA78, PARA78_शेष);
		RTL_W32 (PARA7c, PARA7c_शेष);
		RTL_W32 (FIFOTMS, 0x00);
		tp->twist_row = 2;
		tp->twist_col = 0;
		tp->twistie = 3;
		next_tick = HZ / 10;
		अवरोध;

	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_8139TOO_TUNE_TWISTER */

अटल अंतरभूत व्योम rtl8139_thपढ़ो_iter (काष्ठा net_device *dev,
				 काष्ठा rtl8139_निजी *tp,
				 व्योम __iomem *ioaddr)
अणु
	पूर्णांक mii_lpa;

	mii_lpa = mdio_पढ़ो (dev, tp->phys[0], MII_LPA);

	अगर (!tp->mii.क्रमce_media && mii_lpa != 0xffff) अणु
		पूर्णांक duplex = ((mii_lpa & LPA_100FULL) ||
			      (mii_lpa & 0x01C0) == 0x0040);
		अगर (tp->mii.full_duplex != duplex) अणु
			tp->mii.full_duplex = duplex;

			अगर (mii_lpa) अणु
				netdev_info(dev, "Setting %s-duplex based on MII #%d link partner ability of %04x\n",
					    tp->mii.full_duplex ? "full" : "half",
					    tp->phys[0], mii_lpa);
			पूर्ण अन्यथा अणु
				netdev_info(dev, "media is unconnected, link down, or incompatible connection\n");
			पूर्ण
#अगर 0
			RTL_W8 (Cfg9346, Cfg9346_Unlock);
			RTL_W8 (Config1, tp->mii.full_duplex ? 0x60 : 0x20);
			RTL_W8 (Cfg9346, Cfg9346_Lock);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	next_tick = HZ * 60;

	rtl8139_tune_twister (dev, tp);

	netdev_dbg(dev, "Media selection tick, Link partner %04x\n",
		   RTL_R16(NWayLPAR));
	netdev_dbg(dev, "Other registers are IntMask %04x IntStatus %04x\n",
		   RTL_R16(IntrMask), RTL_R16(IntrStatus));
	netdev_dbg(dev, "Chip config %02x %02x\n",
		   RTL_R8(Config0), RTL_R8(Config1));
पूर्ण

अटल व्योम rtl8139_thपढ़ो (काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl8139_निजी *tp =
		container_of(work, काष्ठा rtl8139_निजी, thपढ़ो.work);
	काष्ठा net_device *dev = tp->mii.dev;
	अचिन्हित दीर्घ thr_delay = next_tick;

	rtnl_lock();

	अगर (!netअगर_running(dev))
		जाओ out_unlock;

	अगर (tp->watchकरोg_fired) अणु
		tp->watchकरोg_fired = 0;
		rtl8139_tx_समयout_task(work);
	पूर्ण अन्यथा
		rtl8139_thपढ़ो_iter(dev, tp, tp->mmio_addr);

	अगर (tp->have_thपढ़ो)
		schedule_delayed_work(&tp->thपढ़ो, thr_delay);
out_unlock:
	rtnl_unlock ();
पूर्ण

अटल व्योम rtl8139_start_thपढ़ो(काष्ठा rtl8139_निजी *tp)
अणु
	tp->twistie = 0;
	अगर (tp->chipset == CH_8139_K)
		tp->twistie = 1;
	अन्यथा अगर (tp->drv_flags & HAS_LNK_CHNG)
		वापस;

	tp->have_thपढ़ो = 1;
	tp->watchकरोg_fired = 0;

	schedule_delayed_work(&tp->thपढ़ो, next_tick);
पूर्ण

अटल अंतरभूत व्योम rtl8139_tx_clear (काष्ठा rtl8139_निजी *tp)
अणु
	tp->cur_tx = 0;
	tp->dirty_tx = 0;

	/* XXX account क्रम unsent Tx packets in tp->stats.tx_dropped */
पूर्ण

अटल व्योम rtl8139_tx_समयout_task (काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl8139_निजी *tp =
		container_of(work, काष्ठा rtl8139_निजी, thपढ़ो.work);
	काष्ठा net_device *dev = tp->mii.dev;
	व्योम __iomem *ioaddr = tp->mmio_addr;
	पूर्णांक i;
	u8 पंचांगp8;

	napi_disable(&tp->napi);
	netअगर_stop_queue(dev);
	synchronize_rcu();

	netdev_dbg(dev, "Transmit timeout, status %02x %04x %04x media %02x\n",
		   RTL_R8(ChipCmd), RTL_R16(IntrStatus),
		   RTL_R16(IntrMask), RTL_R8(MediaStatus));
	/* Emit info to figure out what went wrong. */
	netdev_dbg(dev, "Tx queue start entry %ld  dirty entry %ld\n",
		   tp->cur_tx, tp->dirty_tx);
	क्रम (i = 0; i < NUM_TX_DESC; i++)
		netdev_dbg(dev, "Tx descriptor %d is %08x%s\n",
			   i, RTL_R32(TxStatus0 + (i * 4)),
			   i == tp->dirty_tx % NUM_TX_DESC ?
			   " (queue head)" : "");

	tp->xstats.tx_समयouts++;

	/* disable Tx ASAP, अगर not alपढ़ोy */
	पंचांगp8 = RTL_R8 (ChipCmd);
	अगर (पंचांगp8 & CmdTxEnb)
		RTL_W8 (ChipCmd, CmdRxEnb);

	spin_lock_bh(&tp->rx_lock);
	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	RTL_W16 (IntrMask, 0x0000);

	/* Stop a shared पूर्णांकerrupt from scavenging जबतक we are. */
	spin_lock_irq(&tp->lock);
	rtl8139_tx_clear (tp);
	spin_unlock_irq(&tp->lock);

	/* ...and finally, reset everything */
	napi_enable(&tp->napi);
	rtl8139_hw_start(dev);
	netअगर_wake_queue(dev);

	spin_unlock_bh(&tp->rx_lock);
पूर्ण

अटल व्योम rtl8139_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);

	tp->watchकरोg_fired = 1;
	अगर (!tp->have_thपढ़ो) अणु
		INIT_DELAYED_WORK(&tp->thपढ़ो, rtl8139_thपढ़ो);
		schedule_delayed_work(&tp->thपढ़ो, next_tick);
	पूर्ण
पूर्ण

अटल netdev_tx_t rtl8139_start_xmit (काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	अचिन्हित पूर्णांक entry;
	अचिन्हित पूर्णांक len = skb->len;
	अचिन्हित दीर्घ flags;

	/* Calculate the next Tx descriptor entry. */
	entry = tp->cur_tx % NUM_TX_DESC;

	/* Note: the chip करोesn't have स्वतः-pad! */
	अगर (likely(len < TX_BUF_SIZE)) अणु
		अगर (len < ETH_ZLEN)
			स_रखो(tp->tx_buf[entry], 0, ETH_ZLEN);
		skb_copy_and_csum_dev(skb, tp->tx_buf[entry]);
		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	spin_lock_irqsave(&tp->lock, flags);
	/*
	 * Writing to TxStatus triggers a DMA transfer of the data
	 * copied to tp->tx_buf[entry] above. Use a memory barrier
	 * to make sure that the device sees the updated data.
	 */
	wmb();
	RTL_W32_F (TxStatus0 + (entry * माप (u32)),
		   tp->tx_flag | max(len, (अचिन्हित पूर्णांक)ETH_ZLEN));

	tp->cur_tx++;

	अगर ((tp->cur_tx - NUM_TX_DESC) == tp->dirty_tx)
		netअगर_stop_queue (dev);
	spin_unlock_irqrestore(&tp->lock, flags);

	netअगर_dbg(tp, tx_queued, dev, "Queued Tx packet size %u to slot %d\n",
		  len, entry);

	वापस NETDEV_TX_OK;
पूर्ण


अटल व्योम rtl8139_tx_पूर्णांकerrupt (काष्ठा net_device *dev,
				  काष्ठा rtl8139_निजी *tp,
				  व्योम __iomem *ioaddr)
अणु
	अचिन्हित दीर्घ dirty_tx, tx_left;

	निश्चित (dev != शून्य);
	निश्चित (ioaddr != शून्य);

	dirty_tx = tp->dirty_tx;
	tx_left = tp->cur_tx - dirty_tx;
	जबतक (tx_left > 0) अणु
		पूर्णांक entry = dirty_tx % NUM_TX_DESC;
		पूर्णांक txstatus;

		txstatus = RTL_R32 (TxStatus0 + (entry * माप (u32)));

		अगर (!(txstatus & (TxStatOK | TxUnderrun | TxAborted)))
			अवरोध;	/* It still hasn't been Txed */

		/* Note: TxCarrierLost is always निश्चितed at 100mbps. */
		अगर (txstatus & (TxOutOfWinकरोw | TxAborted)) अणु
			/* There was an major error, log it. */
			netअगर_dbg(tp, tx_err, dev, "Transmit error, Tx status %08x\n",
				  txstatus);
			dev->stats.tx_errors++;
			अगर (txstatus & TxAborted) अणु
				dev->stats.tx_पातed_errors++;
				RTL_W32 (TxConfig, TxClearAbt);
				RTL_W16 (IntrStatus, TxErr);
				wmb();
			पूर्ण
			अगर (txstatus & TxCarrierLost)
				dev->stats.tx_carrier_errors++;
			अगर (txstatus & TxOutOfWinकरोw)
				dev->stats.tx_winकरोw_errors++;
		पूर्ण अन्यथा अणु
			अगर (txstatus & TxUnderrun) अणु
				/* Add 64 to the Tx FIFO threshold. */
				अगर (tp->tx_flag < 0x00300000)
					tp->tx_flag += 0x00020000;
				dev->stats.tx_fअगरo_errors++;
			पूर्ण
			dev->stats.collisions += (txstatus >> 24) & 15;
			u64_stats_update_begin(&tp->tx_stats.syncp);
			tp->tx_stats.packets++;
			tp->tx_stats.bytes += txstatus & 0x7ff;
			u64_stats_update_end(&tp->tx_stats.syncp);
		पूर्ण

		dirty_tx++;
		tx_left--;
	पूर्ण

#अगर_अघोषित RTL8139_न_संशोधन
	अगर (tp->cur_tx - dirty_tx > NUM_TX_DESC) अणु
		netdev_err(dev, "Out-of-sync dirty pointer, %ld vs. %ld\n",
			   dirty_tx, tp->cur_tx);
		dirty_tx += NUM_TX_DESC;
	पूर्ण
#पूर्ण_अगर /* RTL8139_न_संशोधन */

	/* only wake the queue अगर we did work, and the queue is stopped */
	अगर (tp->dirty_tx != dirty_tx) अणु
		tp->dirty_tx = dirty_tx;
		mb();
		netअगर_wake_queue (dev);
	पूर्ण
पूर्ण


/* TODO: clean this up!  Rx reset need not be this पूर्णांकensive */
अटल व्योम rtl8139_rx_err (u32 rx_status, काष्ठा net_device *dev,
			    काष्ठा rtl8139_निजी *tp, व्योम __iomem *ioaddr)
अणु
	u8 पंचांगp8;
#अगर_घोषित CONFIG_8139_OLD_RX_RESET
	पूर्णांक पंचांगp_work;
#पूर्ण_अगर

	netअगर_dbg(tp, rx_err, dev, "Ethernet frame had errors, status %08x\n",
		  rx_status);
	dev->stats.rx_errors++;
	अगर (!(rx_status & RxStatusOK)) अणु
		अगर (rx_status & RxTooLong) अणु
			netdev_dbg(dev, "Oversized Ethernet frame, status %04x!\n",
				   rx_status);
			/* A.C.: The chip hangs here. */
		पूर्ण
		अगर (rx_status & (RxBadSymbol | RxBadAlign))
			dev->stats.rx_frame_errors++;
		अगर (rx_status & (RxRunt | RxTooLong))
			dev->stats.rx_length_errors++;
		अगर (rx_status & RxCRCErr)
			dev->stats.rx_crc_errors++;
	पूर्ण अन्यथा अणु
		tp->xstats.rx_lost_in_ring++;
	पूर्ण

#अगर_अघोषित CONFIG_8139_OLD_RX_RESET
	पंचांगp8 = RTL_R8 (ChipCmd);
	RTL_W8 (ChipCmd, पंचांगp8 & ~CmdRxEnb);
	RTL_W8 (ChipCmd, पंचांगp8);
	RTL_W32 (RxConfig, tp->rx_config);
	tp->cur_rx = 0;
#अन्यथा
	/* Reset the receiver, based on RealTek recommendation. (Bug?) */

	/* disable receive */
	RTL_W8_F (ChipCmd, CmdTxEnb);
	पंचांगp_work = 200;
	जबतक (--पंचांगp_work > 0) अणु
		udelay(1);
		पंचांगp8 = RTL_R8 (ChipCmd);
		अगर (!(पंचांगp8 & CmdRxEnb))
			अवरोध;
	पूर्ण
	अगर (पंचांगp_work <= 0)
		netdev_warn(dev, "rx stop wait too long\n");
	/* restart receive */
	पंचांगp_work = 200;
	जबतक (--पंचांगp_work > 0) अणु
		RTL_W8_F (ChipCmd, CmdRxEnb | CmdTxEnb);
		udelay(1);
		पंचांगp8 = RTL_R8 (ChipCmd);
		अगर ((पंचांगp8 & CmdRxEnb) && (पंचांगp8 & CmdTxEnb))
			अवरोध;
	पूर्ण
	अगर (पंचांगp_work <= 0)
		netdev_warn(dev, "tx/rx enable wait too long\n");

	/* and reinitialize all rx related रेजिस्टरs */
	RTL_W8_F (Cfg9346, Cfg9346_Unlock);
	/* Must enable Tx/Rx beक्रमe setting transfer thresholds! */
	RTL_W8 (ChipCmd, CmdRxEnb | CmdTxEnb);

	tp->rx_config = rtl8139_rx_config | AcceptBroadcast | AcceptMyPhys;
	RTL_W32 (RxConfig, tp->rx_config);
	tp->cur_rx = 0;

	netdev_dbg(dev, "init buffer addresses\n");

	/* Lock Config[01234] and BMCR रेजिस्टर ग_लिखोs */
	RTL_W8 (Cfg9346, Cfg9346_Lock);

	/* init Rx ring buffer DMA address */
	RTL_W32_F (RxBuf, tp->rx_ring_dma);

	/* A.C.: Reset the multicast list. */
	__set_rx_mode (dev);
#पूर्ण_अगर
पूर्ण

#अगर RX_BUF_IDX == 3
अटल अंतरभूत व्योम wrap_copy(काष्ठा sk_buff *skb, स्थिर अचिन्हित अक्षर *ring,
				 u32 offset, अचिन्हित पूर्णांक size)
अणु
	u32 left = RX_BUF_LEN - offset;

	अगर (size > left) अणु
		skb_copy_to_linear_data(skb, ring + offset, left);
		skb_copy_to_linear_data_offset(skb, left, ring, size - left);
	पूर्ण अन्यथा
		skb_copy_to_linear_data(skb, ring + offset, size);
पूर्ण
#पूर्ण_अगर

अटल व्योम rtl8139_isr_ack(काष्ठा rtl8139_निजी *tp)
अणु
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u16 status;

	status = RTL_R16 (IntrStatus) & RxAckBits;

	/* Clear out errors and receive पूर्णांकerrupts */
	अगर (likely(status != 0)) अणु
		अगर (unlikely(status & (RxFIFOOver | RxOverflow))) अणु
			tp->dev->stats.rx_errors++;
			अगर (status & RxFIFOOver)
				tp->dev->stats.rx_fअगरo_errors++;
		पूर्ण
		RTL_W16_F (IntrStatus, RxAckBits);
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8139_rx(काष्ठा net_device *dev, काष्ठा rtl8139_निजी *tp,
		      पूर्णांक budget)
अणु
	व्योम __iomem *ioaddr = tp->mmio_addr;
	पूर्णांक received = 0;
	अचिन्हित अक्षर *rx_ring = tp->rx_ring;
	अचिन्हित पूर्णांक cur_rx = tp->cur_rx;
	अचिन्हित पूर्णांक rx_size = 0;

	netdev_dbg(dev, "In %s(), current %04x BufAddr %04x, free to %04x, Cmd %02x\n",
		   __func__, (u16)cur_rx,
		   RTL_R16(RxBufAddr), RTL_R16(RxBufPtr), RTL_R8(ChipCmd));

	जबतक (netअगर_running(dev) && received < budget &&
	       (RTL_R8 (ChipCmd) & RxBufEmpty) == 0) अणु
		u32 ring_offset = cur_rx % RX_BUF_LEN;
		u32 rx_status;
		अचिन्हित पूर्णांक pkt_size;
		काष्ठा sk_buff *skb;

		rmb();

		/* पढ़ो size+status of next frame from DMA ring buffer */
		rx_status = le32_to_cpu (*(__le32 *) (rx_ring + ring_offset));
		rx_size = rx_status >> 16;
		अगर (likely(!(dev->features & NETIF_F_RXFCS)))
			pkt_size = rx_size - 4;
		अन्यथा
			pkt_size = rx_size;

		netअगर_dbg(tp, rx_status, dev, "%s() status %04x, size %04x, cur %04x\n",
			  __func__, rx_status, rx_size, cur_rx);
#अगर RTL8139_DEBUG > 2
		prपूर्णांक_hex_dump(KERN_DEBUG, "Frame contents: ",
			       DUMP_PREFIX_OFFSET, 16, 1,
			       &rx_ring[ring_offset], 70, true);
#पूर्ण_अगर

		/* Packet copy from FIFO still in progress.
		 * Theoretically, this should never happen
		 * since EarlyRx is disabled.
		 */
		अगर (unlikely(rx_size == 0xfff0)) अणु
			अगर (!tp->fअगरo_copy_समयout)
				tp->fअगरo_copy_समयout = jअगरfies + 2;
			अन्यथा अगर (समय_after(jअगरfies, tp->fअगरo_copy_समयout)) अणु
				netdev_dbg(dev, "hung FIFO. Reset\n");
				rx_size = 0;
				जाओ no_early_rx;
			पूर्ण
			netअगर_dbg(tp, पूर्णांकr, dev, "fifo copy in progress\n");
			tp->xstats.early_rx++;
			अवरोध;
		पूर्ण

no_early_rx:
		tp->fअगरo_copy_समयout = 0;

		/* If Rx err or invalid rx_size/rx_status received
		 * (which happens अगर we get lost in the ring),
		 * Rx process माला_लो reset, so we पात any further
		 * Rx processing.
		 */
		अगर (unlikely((rx_size > (MAX_ETH_FRAME_SIZE+4)) ||
			     (rx_size < 8) ||
			     (!(rx_status & RxStatusOK)))) अणु
			अगर ((dev->features & NETIF_F_RXALL) &&
			    (rx_size <= (MAX_ETH_FRAME_SIZE + 4)) &&
			    (rx_size >= 8) &&
			    (!(rx_status & RxStatusOK))) अणु
				/* Length is at least mostly OK, but pkt has
				 * error.  I'm hoping we can handle some of these
				 * errors without resetting the chip. --Ben
				 */
				dev->stats.rx_errors++;
				अगर (rx_status & RxCRCErr) अणु
					dev->stats.rx_crc_errors++;
					जाओ keep_pkt;
				पूर्ण
				अगर (rx_status & RxRunt) अणु
					dev->stats.rx_length_errors++;
					जाओ keep_pkt;
				पूर्ण
			पूर्ण
			rtl8139_rx_err (rx_status, dev, tp, ioaddr);
			received = -1;
			जाओ out;
		पूर्ण

keep_pkt:
		/* Malloc up new buffer, compatible with net-2e. */
		/* Omit the four octet CRC from the length. */

		skb = napi_alloc_skb(&tp->napi, pkt_size);
		अगर (likely(skb)) अणु
#अगर RX_BUF_IDX == 3
			wrap_copy(skb, rx_ring, ring_offset+4, pkt_size);
#अन्यथा
			skb_copy_to_linear_data (skb, &rx_ring[ring_offset + 4], pkt_size);
#पूर्ण_अगर
			skb_put (skb, pkt_size);

			skb->protocol = eth_type_trans (skb, dev);

			u64_stats_update_begin(&tp->rx_stats.syncp);
			tp->rx_stats.packets++;
			tp->rx_stats.bytes += pkt_size;
			u64_stats_update_end(&tp->rx_stats.syncp);

			netअगर_receive_skb (skb);
		पूर्ण अन्यथा अणु
			dev->stats.rx_dropped++;
		पूर्ण
		received++;

		cur_rx = (cur_rx + rx_size + 4 + 3) & ~3;
		RTL_W16 (RxBufPtr, (u16) (cur_rx - 16));

		rtl8139_isr_ack(tp);
	पूर्ण

	अगर (unlikely(!received || rx_size == 0xfff0))
		rtl8139_isr_ack(tp);

	netdev_dbg(dev, "Done %s(), current %04x BufAddr %04x, free to %04x, Cmd %02x\n",
		   __func__, cur_rx,
		   RTL_R16(RxBufAddr), RTL_R16(RxBufPtr), RTL_R8(ChipCmd));

	tp->cur_rx = cur_rx;

	/*
	 * The receive buffer should be mostly empty.
	 * Tell NAPI to reenable the Rx irq.
	 */
	अगर (tp->fअगरo_copy_समयout)
		received = budget;

out:
	वापस received;
पूर्ण


अटल व्योम rtl8139_weird_पूर्णांकerrupt (काष्ठा net_device *dev,
				     काष्ठा rtl8139_निजी *tp,
				     व्योम __iomem *ioaddr,
				     पूर्णांक status, पूर्णांक link_changed)
अणु
	netdev_dbg(dev, "Abnormal interrupt, status %08x\n", status);

	निश्चित (dev != शून्य);
	निश्चित (tp != शून्य);
	निश्चित (ioaddr != शून्य);

	/* Update the error count. */
	dev->stats.rx_missed_errors += RTL_R32 (RxMissed);
	RTL_W32 (RxMissed, 0);

	अगर ((status & RxUnderrun) && link_changed &&
	    (tp->drv_flags & HAS_LNK_CHNG)) अणु
		rtl_check_media(dev, 0);
		status &= ~RxUnderrun;
	पूर्ण

	अगर (status & (RxUnderrun | RxErr))
		dev->stats.rx_errors++;

	अगर (status & PCSTimeout)
		dev->stats.rx_length_errors++;
	अगर (status & RxUnderrun)
		dev->stats.rx_fअगरo_errors++;
	अगर (status & PCIErr) अणु
		u16 pci_cmd_status;
		pci_पढ़ो_config_word (tp->pci_dev, PCI_STATUS, &pci_cmd_status);
		pci_ग_लिखो_config_word (tp->pci_dev, PCI_STATUS, pci_cmd_status);

		netdev_err(dev, "PCI Bus error %04x\n", pci_cmd_status);
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8139_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा rtl8139_निजी *tp = container_of(napi, काष्ठा rtl8139_निजी, napi);
	काष्ठा net_device *dev = tp->dev;
	व्योम __iomem *ioaddr = tp->mmio_addr;
	पूर्णांक work_करोne;

	spin_lock(&tp->rx_lock);
	work_करोne = 0;
	अगर (likely(RTL_R16(IntrStatus) & RxAckBits))
		work_करोne += rtl8139_rx(dev, tp, budget);

	अगर (work_करोne < budget) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&tp->lock, flags);
		अगर (napi_complete_करोne(napi, work_करोne))
			RTL_W16_F(IntrMask, rtl8139_पूर्णांकr_mask);
		spin_unlock_irqrestore(&tp->lock, flags);
	पूर्ण
	spin_unlock(&tp->rx_lock);

	वापस work_करोne;
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */
अटल irqवापस_t rtl8139_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_instance;
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u16 status, ackstat;
	पूर्णांक link_changed = 0; /* aव्योम bogus "uninit" warning */
	पूर्णांक handled = 0;

	spin_lock (&tp->lock);
	status = RTL_R16 (IntrStatus);

	/* shared irq? */
	अगर (unlikely((status & rtl8139_पूर्णांकr_mask) == 0))
		जाओ out;

	handled = 1;

	/* h/w no दीर्घer present (hotplug?) or major error, bail */
	अगर (unlikely(status == 0xFFFF))
		जाओ out;

	/* बंद possible race's with dev_बंद */
	अगर (unlikely(!netअगर_running(dev))) अणु
		RTL_W16 (IntrMask, 0);
		जाओ out;
	पूर्ण

	/* Acknowledge all of the current पूर्णांकerrupt sources ASAP, but
	   an first get an additional status bit from CSCR. */
	अगर (unlikely(status & RxUnderrun))
		link_changed = RTL_R16 (CSCR) & CSCR_LinkChangeBit;

	ackstat = status & ~(RxAckBits | TxErr);
	अगर (ackstat)
		RTL_W16 (IntrStatus, ackstat);

	/* Receive packets are processed by poll routine.
	   If not running start it now. */
	अगर (status & RxAckBits)अणु
		अगर (napi_schedule_prep(&tp->napi)) अणु
			RTL_W16_F (IntrMask, rtl8139_norx_पूर्णांकr_mask);
			__napi_schedule(&tp->napi);
		पूर्ण
	पूर्ण

	/* Check uncommon events with one test. */
	अगर (unlikely(status & (PCIErr | PCSTimeout | RxUnderrun | RxErr)))
		rtl8139_weird_पूर्णांकerrupt (dev, tp, ioaddr,
					 status, link_changed);

	अगर (status & (TxOK | TxErr)) अणु
		rtl8139_tx_पूर्णांकerrupt (dev, tp, ioaddr);
		अगर (status & TxErr)
			RTL_W16 (IntrStatus, TxErr);
	पूर्ण
 out:
	spin_unlock (&tp->lock);

	netdev_dbg(dev, "exiting interrupt, intr_status=%#4.4x\n",
		   RTL_R16(IntrStatus));
	वापस IRQ_RETVAL(handled);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling receive - used by netconsole and other diagnostic tools
 * to allow network i/o with पूर्णांकerrupts disabled.
 */
अटल व्योम rtl8139_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	स्थिर पूर्णांक irq = tp->pci_dev->irq;

	disable_irq_nosync(irq);
	rtl8139_पूर्णांकerrupt(irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rtl8139_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	spin_lock_irq(&tp->lock);

	RTL_W8_F(Cfg9346, Cfg9346_Unlock);
	RTL_W32_F(MAC0 + 0, cpu_to_le32 (*(u32 *) (dev->dev_addr + 0)));
	RTL_W32_F(MAC0 + 4, cpu_to_le32 (*(u32 *) (dev->dev_addr + 4)));
	RTL_W8_F(Cfg9346, Cfg9346_Lock);

	spin_unlock_irq(&tp->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8139_बंद (काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue(dev);
	napi_disable(&tp->napi);

	netअगर_dbg(tp, अगरकरोwn, dev, "Shutting down ethercard, status was 0x%04x\n",
		  RTL_R16(IntrStatus));

	spin_lock_irqsave (&tp->lock, flags);

	/* Stop the chip's Tx and Rx DMA processes. */
	RTL_W8 (ChipCmd, 0);

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	RTL_W16 (IntrMask, 0);

	/* Update the error counts. */
	dev->stats.rx_missed_errors += RTL_R32 (RxMissed);
	RTL_W32 (RxMissed, 0);

	spin_unlock_irqrestore (&tp->lock, flags);

	मुक्त_irq(tp->pci_dev->irq, dev);

	rtl8139_tx_clear (tp);

	dma_मुक्त_coherent(&tp->pci_dev->dev, RX_BUF_TOT_LEN,
			  tp->rx_ring, tp->rx_ring_dma);
	dma_मुक्त_coherent(&tp->pci_dev->dev, TX_BUF_TOT_LEN,
			  tp->tx_bufs, tp->tx_bufs_dma);
	tp->rx_ring = शून्य;
	tp->tx_bufs = शून्य;

	/* Green! Put the chip in low-घातer mode. */
	RTL_W8 (Cfg9346, Cfg9346_Unlock);

	अगर (rtl_chip_info[tp->chipset].flags & HasHltClk)
		RTL_W8 (HltClk, 'H');	/* 'R' would leave the घड़ी running. */

	वापस 0;
पूर्ण


/* Get the ethtool Wake-on-LAN settings.  Assumes that wol poपूर्णांकs to
   kernel memory, *wol has been initialized as अणुETHTOOL_GWOLपूर्ण, and
   other thपढ़ोs or पूर्णांकerrupts aren't messing with the 8139.  */
अटल व्योम rtl8139_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;

	spin_lock_irq(&tp->lock);
	अगर (rtl_chip_info[tp->chipset].flags & HasLWake) अणु
		u8 cfg3 = RTL_R8 (Config3);
		u8 cfg5 = RTL_R8 (Config5);

		wol->supported = WAKE_PHY | WAKE_MAGIC
			| WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;

		wol->wolopts = 0;
		अगर (cfg3 & Cfg3_LinkUp)
			wol->wolopts |= WAKE_PHY;
		अगर (cfg3 & Cfg3_Magic)
			wol->wolopts |= WAKE_MAGIC;
		/* (KON)FIXME: See how netdev_set_wol() handles the
		   following स्थिरants.  */
		अगर (cfg5 & Cfg5_UWF)
			wol->wolopts |= WAKE_UCAST;
		अगर (cfg5 & Cfg5_MWF)
			wol->wolopts |= WAKE_MCAST;
		अगर (cfg5 & Cfg5_BWF)
			wol->wolopts |= WAKE_BCAST;
	पूर्ण
	spin_unlock_irq(&tp->lock);
पूर्ण


/* Set the ethtool Wake-on-LAN settings.  Return 0 or -त्रुटि_सं.  Assumes
   that wol poपूर्णांकs to kernel memory and other thपढ़ोs or पूर्णांकerrupts
   aren't messing with the 8139.  */
अटल पूर्णांक rtl8139_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u32 support;
	u8 cfg3, cfg5;

	support = ((rtl_chip_info[tp->chipset].flags & HasLWake)
		   ? (WAKE_PHY | WAKE_MAGIC
		      | WAKE_UCAST | WAKE_MCAST | WAKE_BCAST)
		   : 0);
	अगर (wol->wolopts & ~support)
		वापस -EINVAL;

	spin_lock_irq(&tp->lock);
	cfg3 = RTL_R8 (Config3) & ~(Cfg3_LinkUp | Cfg3_Magic);
	अगर (wol->wolopts & WAKE_PHY)
		cfg3 |= Cfg3_LinkUp;
	अगर (wol->wolopts & WAKE_MAGIC)
		cfg3 |= Cfg3_Magic;
	RTL_W8 (Cfg9346, Cfg9346_Unlock);
	RTL_W8 (Config3, cfg3);
	RTL_W8 (Cfg9346, Cfg9346_Lock);

	cfg5 = RTL_R8 (Config5) & ~(Cfg5_UWF | Cfg5_MWF | Cfg5_BWF);
	/* (KON)FIXME: These are untested.  We may have to set the
	   CRC0, Wakeup0 and LSBCRC0 रेजिस्टरs too, but I have no
	   करोcumentation.  */
	अगर (wol->wolopts & WAKE_UCAST)
		cfg5 |= Cfg5_UWF;
	अगर (wol->wolopts & WAKE_MCAST)
		cfg5 |= Cfg5_MWF;
	अगर (wol->wolopts & WAKE_BCAST)
		cfg5 |= Cfg5_BWF;
	RTL_W8 (Config5, cfg5);	/* need not unlock via Cfg9346 */
	spin_unlock_irq(&tp->lock);

	वापस 0;
पूर्ण

अटल व्योम rtl8139_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(tp->pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक rtl8139_get_link_ksettings(काष्ठा net_device *dev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	spin_lock_irq(&tp->lock);
	mii_ethtool_get_link_ksettings(&tp->mii, cmd);
	spin_unlock_irq(&tp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक rtl8139_set_link_ksettings(काष्ठा net_device *dev,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	पूर्णांक rc;
	spin_lock_irq(&tp->lock);
	rc = mii_ethtool_set_link_ksettings(&tp->mii, cmd);
	spin_unlock_irq(&tp->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक rtl8139_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	वापस mii_nway_restart(&tp->mii);
पूर्ण

अटल u32 rtl8139_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	वापस mii_link_ok(&tp->mii);
पूर्ण

अटल u32 rtl8139_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	वापस tp->msg_enable;
पूर्ण

अटल व्योम rtl8139_set_msglevel(काष्ठा net_device *dev, u32 datum)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	tp->msg_enable = datum;
पूर्ण

अटल पूर्णांक rtl8139_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp;
	/* TODO: we are too slack to करो reg dumping क्रम pio, क्रम now */
	अगर (use_io)
		वापस 0;
	tp = netdev_priv(dev);
	वापस tp->regs_len;
पूर्ण

अटल व्योम rtl8139_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *regbuf)
अणु
	काष्ठा rtl8139_निजी *tp;

	/* TODO: we are too slack to करो reg dumping क्रम pio, क्रम now */
	अगर (use_io)
		वापस;
	tp = netdev_priv(dev);

	regs->version = RTL_REGS_VER;

	spin_lock_irq(&tp->lock);
	स_नकल_fromio(regbuf, tp->mmio_addr, regs->len);
	spin_unlock_irq(&tp->lock);
पूर्ण

अटल पूर्णांक rtl8139_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस RTL_NUM_STATS;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम rtl8139_get_ethtool_stats(काष्ठा net_device *dev, काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);

	data[0] = tp->xstats.early_rx;
	data[1] = tp->xstats.tx_buf_mapped;
	data[2] = tp->xstats.tx_समयouts;
	data[3] = tp->xstats.rx_lost_in_ring;
पूर्ण

अटल व्योम rtl8139_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	स_नकल(data, ethtool_stats_keys, माप(ethtool_stats_keys));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops rtl8139_ethtool_ops = अणु
	.get_drvinfo		= rtl8139_get_drvinfo,
	.get_regs_len		= rtl8139_get_regs_len,
	.get_regs		= rtl8139_get_regs,
	.nway_reset		= rtl8139_nway_reset,
	.get_link		= rtl8139_get_link,
	.get_msglevel		= rtl8139_get_msglevel,
	.set_msglevel		= rtl8139_set_msglevel,
	.get_wol		= rtl8139_get_wol,
	.set_wol		= rtl8139_set_wol,
	.get_strings		= rtl8139_get_strings,
	.get_sset_count		= rtl8139_get_sset_count,
	.get_ethtool_stats	= rtl8139_get_ethtool_stats,
	.get_link_ksettings	= rtl8139_get_link_ksettings,
	.set_link_ksettings	= rtl8139_set_link_ksettings,
पूर्ण;

अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	पूर्णांक rc;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	spin_lock_irq(&tp->lock);
	rc = generic_mii_ioctl(&tp->mii, अगर_mii(rq), cmd, शून्य);
	spin_unlock_irq(&tp->lock);

	वापस rc;
पूर्ण


अटल व्योम
rtl8139_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक start;

	अगर (netअगर_running(dev)) अणु
		spin_lock_irqsave (&tp->lock, flags);
		dev->stats.rx_missed_errors += RTL_R32 (RxMissed);
		RTL_W32 (RxMissed, 0);
		spin_unlock_irqrestore (&tp->lock, flags);
	पूर्ण

	netdev_stats_to_stats64(stats, &dev->stats);

	करो अणु
		start = u64_stats_fetch_begin_irq(&tp->rx_stats.syncp);
		stats->rx_packets = tp->rx_stats.packets;
		stats->rx_bytes = tp->rx_stats.bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&tp->rx_stats.syncp, start));

	करो अणु
		start = u64_stats_fetch_begin_irq(&tp->tx_stats.syncp);
		stats->tx_packets = tp->tx_stats.packets;
		stats->tx_bytes = tp->tx_stats.bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&tp->tx_stats.syncp, start));
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor.
   This routine is not state sensitive and need not be SMP locked. */

अटल व्योम __set_rx_mode (काष्ठा net_device *dev)
अणु
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u32 mc_filter[2];	/* Multicast hash filter */
	पूर्णांक rx_mode;
	u32 पंचांगp;

	netdev_dbg(dev, "rtl8139_set_rx_mode(%04x) done -- Rx config %08x\n",
		   dev->flags, RTL_R32(RxConfig));

	/* Note: करो not reorder, GCC is clever about common statements. */
	अगर (dev->flags & IFF_PROMISC) अणु
		rx_mode =
		    AcceptBroadcast | AcceptMulticast | AcceptMyPhys |
		    AcceptAllPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to filter perfectly -- accept all multicasts. */
		rx_mode = AcceptBroadcast | AcceptMulticast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		rx_mode = AcceptBroadcast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			पूर्णांक bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;

			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
			rx_mode |= AcceptMulticast;
		पूर्ण
	पूर्ण

	अगर (dev->features & NETIF_F_RXALL)
		rx_mode |= (AcceptErr | AcceptRunt);

	/* We can safely update without stopping the chip. */
	पंचांगp = rtl8139_rx_config | rx_mode;
	अगर (tp->rx_config != पंचांगp) अणु
		RTL_W32_F (RxConfig, पंचांगp);
		tp->rx_config = पंचांगp;
	पूर्ण
	RTL_W32_F (MAR0 + 0, mc_filter[0]);
	RTL_W32_F (MAR0 + 4, mc_filter[1]);
पूर्ण

अटल व्योम rtl8139_set_rx_mode (काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);

	spin_lock_irqsave (&tp->lock, flags);
	__set_rx_mode(dev);
	spin_unlock_irqrestore (&tp->lock, flags);
पूर्ण

अटल पूर्णांक __maybe_unused rtl8139_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा rtl8139_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_running (dev))
		वापस 0;

	netअगर_device_detach (dev);

	spin_lock_irqsave (&tp->lock, flags);

	/* Disable पूर्णांकerrupts, stop Tx and Rx. */
	RTL_W16 (IntrMask, 0);
	RTL_W8 (ChipCmd, 0);

	/* Update the error counts. */
	dev->stats.rx_missed_errors += RTL_R32 (RxMissed);
	RTL_W32 (RxMissed, 0);

	spin_unlock_irqrestore (&tp->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rtl8139_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);

	अगर (!netअगर_running (dev))
		वापस 0;

	rtl8139_init_ring (dev);
	rtl8139_hw_start (dev);
	netअगर_device_attach (dev);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rtl8139_pm_ops, rtl8139_suspend, rtl8139_resume);

अटल काष्ठा pci_driver rtl8139_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= rtl8139_pci_tbl,
	.probe		= rtl8139_init_one,
	.हटाओ		= rtl8139_हटाओ_one,
	.driver.pm	= &rtl8139_pm_ops,
पूर्ण;


अटल पूर्णांक __init rtl8139_init_module (व्योम)
अणु
	/* when we're a module, we always prपूर्णांक a version message,
	 * even अगर no 8139 board is found.
	 */
#अगर_घोषित MODULE
	pr_info(RTL8139_DRIVER_NAME "\n");
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&rtl8139_pci_driver);
पूर्ण


अटल व्योम __निकास rtl8139_cleanup_module (व्योम)
अणु
	pci_unरेजिस्टर_driver (&rtl8139_pci_driver);
पूर्ण


module_init(rtl8139_init_module);
module_निकास(rtl8139_cleanup_module);
