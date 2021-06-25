<शैली गुरु>
/* natsemi.c: A Linux PCI Ethernet driver क्रम the NatSemi DP8381x series. */
/*
	Written/copyright 1999-2001 by Donald Becker.
	Portions copyright (c) 2001,2002 Sun Microप्रणालीs (thockin@sun.com)
	Portions copyright 2001,2002 Manfred Spraul (manfred@colorfullअगरe.com)
	Portions copyright 2004 Harald Welte <laक्रमge@gnumonks.org>

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.  License क्रम under other terms may be
	available.  Contact the original author क्रम details.

	The original author may be reached as becker@scyld.com, or at
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	Support inक्रमmation and updates available at
	http://www.scyld.com/network/netsemi.hपंचांगl
	[link no दीर्घer provides useful info -jgarzik]


	TODO:
	* big endian support with CFG:BEM instead of cpu_to_le32
*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>
#समावेश <linux/bitops.h>
#समावेश <linux/prefetch.h>
#समावेश <यंत्र/processor.h>	/* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#घोषणा DRV_NAME	"natsemi"
#घोषणा DRV_VERSION	"2.1"
#घोषणा DRV_RELDATE	"Sept 11, 2006"

#घोषणा RX_OFFSET	2

/* Updated to recommendations in pci-skeleton v2.03. */

/* The user-configurable values.
   These may be modअगरied when a driver module is loaded.*/

#घोषणा NATSEMI_DEF_MSG		(NETIF_MSG_DRV		| \
				 NETIF_MSG_LINK		| \
				 NETIF_MSG_WOL		| \
				 NETIF_MSG_RX_ERR	| \
				 NETIF_MSG_TX_ERR)
अटल पूर्णांक debug = -1;

अटल पूर्णांक mtu;

/* Maximum number of multicast addresses to filter (vs. rx-all-multicast).
   This chip uses a 512 element hash table based on the Ethernet CRC.  */
अटल स्थिर पूर्णांक multicast_filter_limit = 100;

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
   Setting to > 1518 effectively disables this feature. */
अटल पूर्णांक rx_copyअवरोध;

अटल पूर्णांक dspcfg_workaround = 1;

/* Used to pass the media type, etc.
   Both 'options[]' and 'full_duplex[]' should exist क्रम driver
   पूर्णांकeroperability.
   The media type is usually passed in 'options[]'.
*/
#घोषणा MAX_UNITS 8		/* More are supported, limit only on options */
अटल पूर्णांक options[MAX_UNITS];
अटल पूर्णांक full_duplex[MAX_UNITS];

/* Operational parameters that are set at compile समय. */

/* Keep the ring sizes a घातer of two क्रम compile efficiency.
   The compiler will convert <अचिन्हित>'%'<2^N> पूर्णांकo a bit mask.
   Making the Tx ring too large decreases the effectiveness of channel
   bonding and packet priority.
   There are no ill effects from too-large receive rings. */
#घोषणा TX_RING_SIZE	16
#घोषणा TX_QUEUE_LEN	10 /* Limit ring entries actually used, min 4. */
#घोषणा RX_RING_SIZE	32

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (2*HZ)

#घोषणा NATSEMI_HW_TIMEOUT	400
#घोषणा NATSEMI_TIMER_FREQ	5*HZ
#घोषणा NATSEMI_PG0_NREGS	64
#घोषणा NATSEMI_RFDR_NREGS	8
#घोषणा NATSEMI_PG1_NREGS	4
#घोषणा NATSEMI_NREGS		(NATSEMI_PG0_NREGS + NATSEMI_RFDR_NREGS + \
				 NATSEMI_PG1_NREGS)
#घोषणा NATSEMI_REGS_VER	1 /* v1 added RFDR रेजिस्टरs */
#घोषणा NATSEMI_REGS_SIZE	(NATSEMI_NREGS * माप(u32))

/* Buffer sizes:
 * The nic ग_लिखोs 32-bit values, even अगर the upper bytes of
 * a 32-bit value are beyond the end of the buffer.
 */
#घोषणा NATSEMI_HEADERS		22	/* 2*mac,type,vlan,crc */
#घोषणा NATSEMI_PADDING		16	/* 2 bytes should be sufficient */
#घोषणा NATSEMI_LONGPKT		1518	/* limit क्रम normal packets */
#घोषणा NATSEMI_RX_LIMIT	2046	/* maximum supported by hardware */

/* These identअगरy the driver base version and may not be हटाओd. */
अटल स्थिर अक्षर version[] =
  KERN_INFO DRV_NAME " dp8381x driver, version "
      DRV_VERSION ", " DRV_RELDATE "\n"
  "  originally by Donald Becker <becker@scyld.com>\n"
  "  2.4.x kernel port by Jeff Garzik, Tjeerd Mulder\n";

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("National Semiconductor DP8381x series PCI Ethernet driver");
MODULE_LICENSE("GPL");

module_param(mtu, पूर्णांक, 0);
module_param(debug, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param(dspcfg_workaround, पूर्णांक, 0);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(mtu, "DP8381x MTU (all boards)");
MODULE_PARM_DESC(debug, "DP8381x default debug level");
MODULE_PARM_DESC(rx_copyअवरोध,
	"DP8381x copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(dspcfg_workaround, "DP8381x: control DspCfg workaround");
MODULE_PARM_DESC(options,
	"DP8381x: Bits 0-3: media type, bit 17: full duplex");
MODULE_PARM_DESC(full_duplex, "DP8381x full duplex setting(s) (1)");

/*
				Theory of Operation

I. Board Compatibility

This driver is deचिन्हित क्रम National Semiconductor DP83815 PCI Ethernet NIC.
It also works with other chips in in the DP83810 series.

II. Board-specअगरic settings

This driver requires the PCI पूर्णांकerrupt line to be valid.
It honors the EEPROM-set values.

III. Driver operation

IIIa. Ring buffers

This driver uses two अटलally allocated fixed-size descriptor lists
क्रमmed पूर्णांकo rings by a branch from the final descriptor to the beginning of
the list.  The ring sizes are set at compile समय by RX/TX_RING_SIZE.
The NatSemi design uses a 'next descriptor' poपूर्णांकer that the driver क्रमms
पूर्णांकo a list.

IIIb/c. Transmit/Receive Structure

This driver uses a zero-copy receive and transmit scheme.
The driver allocates full frame size skbuffs क्रम the Rx ring buffers at
खोलो() समय and passes the skb->data field to the chip as receive data
buffers.  When an incoming frame is less than RX_COPYBREAK bytes दीर्घ,
a fresh skbuff is allocated and the frame is copied to the new skbuff.
When the incoming frame is larger, the skbuff is passed directly up the
protocol stack.  Buffers consumed this way are replaced by newly allocated
skbuffs in a later phase of receives.

The RX_COPYBREAK value is chosen to trade-off the memory wasted by
using a full-sized skbuff क्रम small frames vs. the copying costs of larger
frames.  New boards are typically used in generously configured machines
and the underfilled buffers have negligible impact compared to the benefit of
a single allocation size, so the शेष value of zero results in never
copying packets.  When copying is करोne, the cost is usually mitigated by using
a combined copy/checksum routine.  Copying also preloads the cache, which is
most useful with small frames.

A subtle aspect of the operation is that unaligned buffers are not permitted
by the hardware.  Thus the IP header at offset 14 in an ethernet frame isn't
दीर्घword aligned क्रम further processing.  On copies frames are put पूर्णांकo the
skbuff at an offset of "+2", 16-byte aligning the IP header.

IIId. Synchronization

Most operations are synchronized on the np->lock irq spinlock, except the
receive and transmit paths which are synchronised using a combination of
hardware descriptor ownership, disabling पूर्णांकerrupts and NAPI poll scheduling.

IVb. References

http://www.scyld.com/expert/100mbps.hपंचांगl
http://www.scyld.com/expert/NWay.hपंचांगl
Datasheet is available from:
http://www.national.com/pf/DP/DP83815.hपंचांगl

IVc. Errata

None अक्षरacterised.
*/



/*
 * Support क्रम fibre connections on Am79C874:
 * This phy needs a special setup when connected to a fibre cable.
 * http://www.amd.com/files/connectivitysolutions/networking/archivednetworking/22235.pdf
 */
#घोषणा PHYID_AM79C874	0x0022561b

क्रमागत अणु
	MII_MCTRL	= 0x15,		/* mode control रेजिस्टर */
	MII_FX_SEL	= 0x0001,	/* 100BASE-FX (fiber) */
	MII_EN_SCRM	= 0x0004,	/* enable scrambler (tp) */
पूर्ण;

क्रमागत अणु
	NATSEMI_FLAG_IGNORE_PHY		= 0x1,
पूर्ण;

/* array of board data directly indexed by pci_tbl[x].driver_data */
अटल काष्ठा अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक eeprom_size;
पूर्ण natsemi_pci_info[] = अणु
	अणु "Aculab E1/T1 PMXc cPCI carrier card", NATSEMI_FLAG_IGNORE_PHY, 128 पूर्ण,
	अणु "NatSemi DP8381[56]", 0, 24 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id natsemi_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_NS, 0x0020, 0x12d9,     0x000c,     0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_NS, 0x0020, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1 पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, natsemi_pci_tbl);

/* Offsets to the device रेजिस्टरs.
   Unlike software-only प्रणालीs, device drivers पूर्णांकeract with complex hardware.
   It's not useful to define symbolic names क्रम every रेजिस्टर bit in the
   device.
*/
क्रमागत रेजिस्टर_offsets अणु
	ChipCmd			= 0x00,
	ChipConfig		= 0x04,
	EECtrl			= 0x08,
	PCIBusCfg		= 0x0C,
	IntrStatus		= 0x10,
	IntrMask		= 0x14,
	IntrEnable		= 0x18,
	IntrHolकरोff		= 0x1C, /* DP83816 only */
	TxRingPtr		= 0x20,
	TxConfig		= 0x24,
	RxRingPtr		= 0x30,
	RxConfig		= 0x34,
	ClkRun			= 0x3C,
	WOLCmd			= 0x40,
	PauseCmd		= 0x44,
	RxFilterAddr		= 0x48,
	RxFilterData		= 0x4C,
	BootRomAddr		= 0x50,
	BootRomData		= 0x54,
	SiliconRev		= 0x58,
	StatsCtrl		= 0x5C,
	StatsData		= 0x60,
	RxPktErrs		= 0x60,
	RxMissed		= 0x68,
	RxCRCErrs		= 0x64,
	BasicControl		= 0x80,
	BasicStatus		= 0x84,
	AnegAdv			= 0x90,
	AnegPeer		= 0x94,
	PhyStatus		= 0xC0,
	MIntrCtrl		= 0xC4,
	MIntrStatus		= 0xC8,
	PhyCtrl			= 0xE4,

	/* These are from the spec, around page 78... on a separate table.
	 * The meaning of these रेजिस्टरs depend on the value of PGSEL. */
	PGSEL			= 0xCC,
	PMDCSR			= 0xE4,
	TSTDAT			= 0xFC,
	DSPCFG			= 0xF4,
	SDCFG			= 0xF8
पूर्ण;
/* the values क्रम the 'magic' रेजिस्टरs above (PGSEL=1) */
#घोषणा PMDCSR_VAL	0x189c	/* enable preferred adaptation circuitry */
#घोषणा TSTDAT_VAL	0x0
#घोषणा DSPCFG_VAL	0x5040
#घोषणा SDCFG_VAL	0x008c	/* set voltage thresholds क्रम Signal Detect */
#घोषणा DSPCFG_LOCK	0x20	/* coefficient lock bit in DSPCFG */
#घोषणा DSPCFG_COEF	0x1000	/* see coefficient (in TSTDAT) bit in DSPCFG */
#घोषणा TSTDAT_FIXED	0xe8	/* magic number क्रम bad coefficients */

/* misc PCI space रेजिस्टरs */
क्रमागत pci_रेजिस्टर_offsets अणु
	PCIPM			= 0x44,
पूर्ण;

क्रमागत ChipCmd_bits अणु
	ChipReset		= 0x100,
	RxReset			= 0x20,
	TxReset			= 0x10,
	RxOff			= 0x08,
	RxOn			= 0x04,
	TxOff			= 0x02,
	TxOn			= 0x01,
पूर्ण;

क्रमागत ChipConfig_bits अणु
	CfgPhyDis		= 0x200,
	CfgPhyRst		= 0x400,
	CfgExtPhy		= 0x1000,
	CfgAnegEnable		= 0x2000,
	CfgAneg100		= 0x4000,
	CfgAnegFull		= 0x8000,
	CfgAnegDone		= 0x8000000,
	CfgFullDuplex		= 0x20000000,
	CfgSpeed100		= 0x40000000,
	CfgLink			= 0x80000000,
पूर्ण;

क्रमागत EECtrl_bits अणु
	EE_ShअगरtClk		= 0x04,
	EE_DataIn		= 0x01,
	EE_ChipSelect		= 0x08,
	EE_DataOut		= 0x02,
	MII_Data 		= 0x10,
	MII_Write		= 0x20,
	MII_ShअगरtClk		= 0x40,
पूर्ण;

क्रमागत PCIBusCfg_bits अणु
	EepromReload		= 0x4,
पूर्ण;

/* Bits in the पूर्णांकerrupt status/mask रेजिस्टरs. */
क्रमागत IntrStatus_bits अणु
	IntrRxDone		= 0x0001,
	IntrRxIntr		= 0x0002,
	IntrRxErr		= 0x0004,
	IntrRxEarly		= 0x0008,
	IntrRxIdle		= 0x0010,
	IntrRxOverrun		= 0x0020,
	IntrTxDone		= 0x0040,
	IntrTxIntr		= 0x0080,
	IntrTxErr		= 0x0100,
	IntrTxIdle		= 0x0200,
	IntrTxUnderrun		= 0x0400,
	StatsMax		= 0x0800,
	SWInt			= 0x1000,
	WOLPkt			= 0x2000,
	LinkChange		= 0x4000,
	IntrHighBits		= 0x8000,
	RxStatusFIFOOver	= 0x10000,
	IntrPCIErr		= 0xf00000,
	RxResetDone		= 0x1000000,
	TxResetDone		= 0x2000000,
	IntrAbnormalSummary	= 0xCD20,
पूर्ण;

/*
 * Default Interrupts:
 * Rx OK, Rx Packet Error, Rx Overrun,
 * Tx OK, Tx Packet Error, Tx Underrun,
 * MIB Service, Phy Interrupt, High Bits,
 * Rx Status FIFO overrun,
 * Received Target Abort, Received Master Abort,
 * Signalled System Error, Received Parity Error
 */
#घोषणा DEFAULT_INTR 0x00f1cd65

क्रमागत TxConfig_bits अणु
	TxDrthMask		= 0x3f,
	TxFlthMask		= 0x3f00,
	TxMxdmaMask		= 0x700000,
	TxMxdma_512		= 0x0,
	TxMxdma_4		= 0x100000,
	TxMxdma_8		= 0x200000,
	TxMxdma_16		= 0x300000,
	TxMxdma_32		= 0x400000,
	TxMxdma_64		= 0x500000,
	TxMxdma_128		= 0x600000,
	TxMxdma_256		= 0x700000,
	TxCollRetry		= 0x800000,
	TxAutoPad		= 0x10000000,
	TxMacLoop		= 0x20000000,
	TxHeartIgn		= 0x40000000,
	TxCarrierIgn		= 0x80000000
पूर्ण;

/*
 * Tx Configuration:
 * - 256 byte DMA burst length
 * - fill threshold 512 bytes (i.e. restart DMA when 512 bytes are मुक्त)
 * - 64 bytes initial drain threshold (i.e. begin actual transmission
 *   when 64 byte are in the fअगरo)
 * - on tx underruns, increase drain threshold by 64.
 * - at most use a drain threshold of 1472 bytes: The sum of the fill
 *   threshold and the drain threshold must be less than 2016 bytes.
 *
 */
#घोषणा TX_FLTH_VAL		((512/32) << 8)
#घोषणा TX_DRTH_VAL_START	(64/32)
#घोषणा TX_DRTH_VAL_INC		2
#घोषणा TX_DRTH_VAL_LIMIT	(1472/32)

क्रमागत RxConfig_bits अणु
	RxDrthMask		= 0x3e,
	RxMxdmaMask		= 0x700000,
	RxMxdma_512		= 0x0,
	RxMxdma_4		= 0x100000,
	RxMxdma_8		= 0x200000,
	RxMxdma_16		= 0x300000,
	RxMxdma_32		= 0x400000,
	RxMxdma_64		= 0x500000,
	RxMxdma_128		= 0x600000,
	RxMxdma_256		= 0x700000,
	RxAcceptLong		= 0x8000000,
	RxAcceptTx		= 0x10000000,
	RxAcceptRunt		= 0x40000000,
	RxAcceptErr		= 0x80000000
पूर्ण;
#घोषणा RX_DRTH_VAL		(128/8)

क्रमागत ClkRun_bits अणु
	PMEEnable		= 0x100,
	PMEStatus		= 0x8000,
पूर्ण;

क्रमागत WolCmd_bits अणु
	WakePhy			= 0x1,
	WakeUnicast		= 0x2,
	WakeMulticast		= 0x4,
	WakeBroadcast		= 0x8,
	WakeArp			= 0x10,
	WakePMatch0		= 0x20,
	WakePMatch1		= 0x40,
	WakePMatch2		= 0x80,
	WakePMatch3		= 0x100,
	WakeMagic		= 0x200,
	WakeMagicSecure		= 0x400,
	SecureHack		= 0x100000,
	WokePhy			= 0x400000,
	WokeUnicast		= 0x800000,
	WokeMulticast		= 0x1000000,
	WokeBroadcast		= 0x2000000,
	WokeArp			= 0x4000000,
	WokePMatch0		= 0x8000000,
	WokePMatch1		= 0x10000000,
	WokePMatch2		= 0x20000000,
	WokePMatch3		= 0x40000000,
	WokeMagic		= 0x80000000,
	WakeOptsSummary		= 0x7ff
पूर्ण;

क्रमागत RxFilterAddr_bits अणु
	RFCRAddressMask		= 0x3ff,
	AcceptMulticast		= 0x00200000,
	AcceptMyPhys		= 0x08000000,
	AcceptAllPhys		= 0x10000000,
	AcceptAllMulticast	= 0x20000000,
	AcceptBroadcast		= 0x40000000,
	RxFilterEnable		= 0x80000000
पूर्ण;

क्रमागत StatsCtrl_bits अणु
	StatsWarn		= 0x1,
	StatsFreeze		= 0x2,
	StatsClear		= 0x4,
	StatsStrobe		= 0x8,
पूर्ण;

क्रमागत MIntrCtrl_bits अणु
	MICRIntEn		= 0x2,
पूर्ण;

क्रमागत PhyCtrl_bits अणु
	PhyAddrMask		= 0x1f,
पूर्ण;

#घोषणा PHY_ADDR_NONE		32
#घोषणा PHY_ADDR_INTERNAL	1

/* values we might find in the silicon revision रेजिस्टर */
#घोषणा SRR_DP83815_C	0x0302
#घोषणा SRR_DP83815_D	0x0403
#घोषणा SRR_DP83816_A4	0x0504
#घोषणा SRR_DP83816_A5	0x0505

/* The Rx and Tx buffer descriptors. */
/* Note that using only 32 bit fields simplअगरies conversion to big-endian
   architectures. */
काष्ठा netdev_desc अणु
	__le32 next_desc;
	__le32 cmd_status;
	__le32 addr;
	__le32 software_use;
पूर्ण;

/* Bits in network_desc.status */
क्रमागत desc_status_bits अणु
	DescOwn=0x80000000, DescMore=0x40000000, DescIntr=0x20000000,
	DescNoCRC=0x10000000, DescPktOK=0x08000000,
	DescSizeMask=0xfff,

	DescTxAbort=0x04000000, DescTxFIFO=0x02000000,
	DescTxCarrier=0x01000000, DescTxDefer=0x00800000,
	DescTxExcDefer=0x00400000, DescTxOOWCol=0x00200000,
	DescTxExcColl=0x00100000, DescTxCollCount=0x000f0000,

	DescRxAbort=0x04000000, DescRxOver=0x02000000,
	DescRxDest=0x01800000, DescRxLong=0x00400000,
	DescRxRunt=0x00200000, DescRxInvalid=0x00100000,
	DescRxCRC=0x00080000, DescRxAlign=0x00040000,
	DescRxLoop=0x00020000, DesRxColl=0x00010000,
पूर्ण;

काष्ठा netdev_निजी अणु
	/* Descriptor rings first क्रम alignment */
	dma_addr_t ring_dma;
	काष्ठा netdev_desc *rx_ring;
	काष्ठा netdev_desc *tx_ring;
	/* The addresses of receive-in-place skbuffs */
	काष्ठा sk_buff *rx_skbuff[RX_RING_SIZE];
	dma_addr_t rx_dma[RX_RING_SIZE];
	/* address of a sent-in-place packet/buffer, क्रम later मुक्त() */
	काष्ठा sk_buff *tx_skbuff[TX_RING_SIZE];
	dma_addr_t tx_dma[TX_RING_SIZE];
	काष्ठा net_device *dev;
	व्योम __iomem *ioaddr;
	काष्ठा napi_काष्ठा napi;
	/* Media monitoring समयr */
	काष्ठा समयr_list समयr;
	/* Frequently used values: keep some adjacent क्रम cache effect */
	काष्ठा pci_dev *pci_dev;
	काष्ठा netdev_desc *rx_head_desc;
	/* Producer/consumer ring indices */
	अचिन्हित पूर्णांक cur_rx, dirty_rx;
	अचिन्हित पूर्णांक cur_tx, dirty_tx;
	/* Based on MTU+slack. */
	अचिन्हित पूर्णांक rx_buf_sz;
	पूर्णांक oom;
	/* Interrupt status */
	u32 पूर्णांकr_status;
	/* Do not touch the nic रेजिस्टरs */
	पूर्णांक hands_off;
	/* Don't pay attention to the reported link state. */
	पूर्णांक ignore_phy;
	/* बाह्यal phy that is used: only valid अगर dev->अगर_port != PORT_TP */
	पूर्णांक mii;
	पूर्णांक phy_addr_बाह्यal;
	अचिन्हित पूर्णांक full_duplex;
	/* Rx filter */
	u32 cur_rx_mode;
	u32 rx_filter[16];
	/* FIFO and PCI burst thresholds */
	u32 tx_config, rx_config;
	/* original contents of ClkRun रेजिस्टर */
	u32 SavedClkRun;
	/* silicon revision */
	u32 srr;
	/* expected DSPCFG value */
	u16 dspcfg;
	पूर्णांक dspcfg_workaround;
	/* parms saved in ethtool क्रमmat */
	u16	speed;		/* The क्रमced speed, 10Mb, 100Mb, gigabit */
	u8	duplex;		/* Duplex, half or full */
	u8	स्वतःneg;	/* Autonegotiation enabled */
	/* MII transceiver section */
	u16 advertising;
	अचिन्हित पूर्णांक iosize;
	spinlock_t lock;
	u32 msg_enable;
	/* EEPROM data */
	पूर्णांक eeprom_size;
पूर्ण;

अटल व्योम move_पूर्णांक_phy(काष्ठा net_device *dev, पूर्णांक addr);
अटल पूर्णांक eeprom_पढ़ो(व्योम __iomem *ioaddr, पूर्णांक location);
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक reg);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक reg, u16 data);
अटल व्योम init_phy_fixup(काष्ठा net_device *dev);
अटल पूर्णांक miiport_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg);
अटल व्योम miiport_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg, u16 data);
अटल पूर्णांक find_mii(काष्ठा net_device *dev);
अटल व्योम natsemi_reset(काष्ठा net_device *dev);
अटल व्योम natsemi_reload_eeprom(काष्ठा net_device *dev);
अटल व्योम natsemi_stop_rxtx(काष्ठा net_device *dev);
अटल पूर्णांक netdev_खोलो(काष्ठा net_device *dev);
अटल व्योम करो_cable_magic(काष्ठा net_device *dev);
अटल व्योम unकरो_cable_magic(काष्ठा net_device *dev);
अटल व्योम check_link(काष्ठा net_device *dev);
अटल व्योम netdev_समयr(काष्ठा समयr_list *t);
अटल व्योम dump_ring(काष्ठा net_device *dev);
अटल व्योम ns_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल पूर्णांक alloc_ring(काष्ठा net_device *dev);
अटल व्योम refill_rx(काष्ठा net_device *dev);
अटल व्योम init_ring(काष्ठा net_device *dev);
अटल व्योम drain_tx(काष्ठा net_device *dev);
अटल व्योम drain_ring(काष्ठा net_device *dev);
अटल व्योम मुक्त_ring(काष्ठा net_device *dev);
अटल व्योम reinit_ring(काष्ठा net_device *dev);
अटल व्योम init_रेजिस्टरs(काष्ठा net_device *dev);
अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance);
अटल व्योम netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status);
अटल पूर्णांक natsemi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
अटल व्योम netdev_rx(काष्ठा net_device *dev, पूर्णांक *work_करोne, पूर्णांक work_to_करो);
अटल व्योम netdev_tx_करोne(काष्ठा net_device *dev);
अटल पूर्णांक natsemi_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम natsemi_poll_controller(काष्ठा net_device *dev);
#पूर्ण_अगर
अटल व्योम __set_rx_mode(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल व्योम __get_stats(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev);
अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल पूर्णांक netdev_set_wol(काष्ठा net_device *dev, u32 newval);
अटल पूर्णांक netdev_get_wol(काष्ठा net_device *dev, u32 *supported, u32 *cur);
अटल पूर्णांक netdev_set_sopass(काष्ठा net_device *dev, u8 *newval);
अटल पूर्णांक netdev_get_sopass(काष्ठा net_device *dev, u8 *data);
अटल पूर्णांक netdev_get_ecmd(काष्ठा net_device *dev,
			   काष्ठा ethtool_link_ksettings *ecmd);
अटल पूर्णांक netdev_set_ecmd(काष्ठा net_device *dev,
			   स्थिर काष्ठा ethtool_link_ksettings *ecmd);
अटल व्योम enable_wol_mode(काष्ठा net_device *dev, पूर्णांक enable_पूर्णांकr);
अटल पूर्णांक netdev_बंद(काष्ठा net_device *dev);
अटल पूर्णांक netdev_get_regs(काष्ठा net_device *dev, u8 *buf);
अटल पूर्णांक netdev_get_eeprom(काष्ठा net_device *dev, u8 *buf);
अटल स्थिर काष्ठा ethtool_ops ethtool_ops;

#घोषणा NATSEMI_ATTR(_name) \
अटल sमाप_प्रकार natsemi_show_##_name(काष्ठा device *dev, \
         काष्ठा device_attribute *attr, अक्षर *buf); \
	 अटल sमाप_प्रकार natsemi_set_##_name(काष्ठा device *dev, \
		काष्ठा device_attribute *attr, \
	        स्थिर अक्षर *buf, माप_प्रकार count); \
	 अटल DEVICE_ATTR(_name, 0644, natsemi_show_##_name, natsemi_set_##_name)

#घोषणा NATSEMI_CREATE_खाता(_dev, _name) \
         device_create_file(&_dev->dev, &dev_attr_##_name)
#घोषणा NATSEMI_REMOVE_खाता(_dev, _name) \
         device_हटाओ_file(&_dev->dev, &dev_attr_##_name)

NATSEMI_ATTR(dspcfg_workaround);

अटल sमाप_प्रकार natsemi_show_dspcfg_workaround(काष्ठा device *dev,
				  	      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(to_net_dev(dev));

	वापस प्र_लिखो(buf, "%s\n", np->dspcfg_workaround ? "on" : "off");
पूर्ण

अटल sमाप_प्रकार natsemi_set_dspcfg_workaround(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(to_net_dev(dev));
	पूर्णांक new_setting;
	अचिन्हित दीर्घ flags;

        /* Find out the new setting */
        अगर (!म_भेदन("on", buf, count - 1) || !म_भेदन("1", buf, count - 1))
                new_setting = 1;
        अन्यथा अगर (!म_भेदन("off", buf, count - 1) ||
                 !म_भेदन("0", buf, count - 1))
		new_setting = 0;
	अन्यथा
                 वापस count;

	spin_lock_irqsave(&np->lock, flags);

	np->dspcfg_workaround = new_setting;

	spin_unlock_irqrestore(&np->lock, flags);

	वापस count;
पूर्ण

अटल अंतरभूत व्योम __iomem *ns_ioaddr(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	वापस np->ioaddr;
पूर्ण

अटल अंतरभूत व्योम natsemi_irq_enable(काष्ठा net_device *dev)
अणु
	ग_लिखोl(1, ns_ioaddr(dev) + IntrEnable);
	पढ़ोl(ns_ioaddr(dev) + IntrEnable);
पूर्ण

अटल अंतरभूत व्योम natsemi_irq_disable(काष्ठा net_device *dev)
अणु
	ग_लिखोl(0, ns_ioaddr(dev) + IntrEnable);
	पढ़ोl(ns_ioaddr(dev) + IntrEnable);
पूर्ण

अटल व्योम move_पूर्णांक_phy(काष्ठा net_device *dev, पूर्णांक addr)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);
	पूर्णांक target = 31;

	/*
	 * The पूर्णांकernal phy is visible on the बाह्यal mii bus. Thereक्रमe we must
	 * move it away beक्रमe we can send commands to an बाह्यal phy.
	 * There are two addresses we must aव्योम:
	 * - the address on the बाह्यal phy that is used क्रम transmission.
	 * - the address that we want to access. User space can access phys
	 *   on the mii bus with SIOCGMIIREG/SIOCSMIIREG, independent from the
	 *   phy that is used क्रम transmission.
	 */

	अगर (target == addr)
		target--;
	अगर (target == np->phy_addr_बाह्यal)
		target--;
	ग_लिखोw(target, ioaddr + PhyCtrl);
	पढ़ोw(ioaddr + PhyCtrl);
	udelay(1);
पूर्ण

अटल व्योम natsemi_init_media(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u32 पंचांगp;

	अगर (np->ignore_phy)
		netअगर_carrier_on(dev);
	अन्यथा
		netअगर_carrier_off(dev);

	/* get the initial settings from hardware */
	पंचांगp            = mdio_पढ़ो(dev, MII_BMCR);
	np->speed      = (पंचांगp & BMCR_SPEED100)? SPEED_100     : SPEED_10;
	np->duplex     = (पंचांगp & BMCR_FULLDPLX)? DUPLEX_FULL   : DUPLEX_HALF;
	np->स्वतःneg    = (पंचांगp & BMCR_ANENABLE)? AUTONEG_ENABLE: AUTONEG_DISABLE;
	np->advertising= mdio_पढ़ो(dev, MII_ADVERTISE);

	अगर ((np->advertising & ADVERTISE_ALL) != ADVERTISE_ALL &&
	    netअगर_msg_probe(np)) अणु
		prपूर्णांकk(KERN_INFO "natsemi %s: Transceiver default autonegotiation %s "
			"10%s %s duplex.\n",
			pci_name(np->pci_dev),
			(mdio_पढ़ो(dev, MII_BMCR) & BMCR_ANENABLE)?
			  "enabled, advertise" : "disabled, force",
			(np->advertising &
			  (ADVERTISE_100FULL|ADVERTISE_100HALF))?
			    "0" : "",
			(np->advertising &
			  (ADVERTISE_100FULL|ADVERTISE_10FULL))?
			    "full" : "half");
	पूर्ण
	अगर (netअगर_msg_probe(np))
		prपूर्णांकk(KERN_INFO
			"natsemi %s: Transceiver status %#04x advertising %#04x.\n",
			pci_name(np->pci_dev), mdio_पढ़ो(dev, MII_BMSR),
			np->advertising);

पूर्ण

अटल स्थिर काष्ठा net_device_ops natsemi_netdev_ops = अणु
	.nकरो_खोलो		= netdev_खोलो,
	.nकरो_stop		= netdev_बंद,
	.nकरो_start_xmit		= start_tx,
	.nकरो_get_stats		= get_stats,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_change_mtu		= natsemi_change_mtu,
	.nकरो_करो_ioctl		= netdev_ioctl,
	.nकरो_tx_समयout 	= ns_tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= natsemi_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक natsemi_probe1(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा netdev_निजी *np;
	पूर्णांक i, option, irq, chip_idx = ent->driver_data;
	अटल पूर्णांक find_cnt = -1;
	resource_माप_प्रकार iostart;
	अचिन्हित दीर्घ iosize;
	व्योम __iomem *ioaddr;
	स्थिर पूर्णांक pcibar = 1; /* PCI base address रेजिस्टर */
	पूर्णांक prev_eedata;
	u32 पंचांगp;

/* when built पूर्णांकo the kernel, we only prपूर्णांक version अगर device is found */
#अगर_अघोषित MODULE
	अटल पूर्णांक prपूर्णांकed_version;
	अगर (!prपूर्णांकed_version++)
		prपूर्णांकk(version);
#पूर्ण_अगर

	i = pci_enable_device(pdev);
	अगर (i) वापस i;

	/* natsemi has a non-standard PM control रेजिस्टर
	 * in PCI config space.  Some boards apparently need
	 * to be brought to D0 in this manner.
	 */
	pci_पढ़ो_config_dword(pdev, PCIPM, &पंचांगp);
	अगर (पंचांगp & PCI_PM_CTRL_STATE_MASK) अणु
		/* D0 state, disable PME निश्चितion */
		u32 newपंचांगp = पंचांगp & ~PCI_PM_CTRL_STATE_MASK;
		pci_ग_लिखो_config_dword(pdev, PCIPM, newपंचांगp);
	पूर्ण

	find_cnt++;
	iostart = pci_resource_start(pdev, pcibar);
	iosize = pci_resource_len(pdev, pcibar);
	irq = pdev->irq;

	pci_set_master(pdev);

	dev = alloc_etherdev(माप (काष्ठा netdev_निजी));
	अगर (!dev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);

	i = pci_request_regions(pdev, DRV_NAME);
	अगर (i)
		जाओ err_pci_request_regions;

	ioaddr = ioremap(iostart, iosize);
	अगर (!ioaddr) अणु
		i = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	/* Work around the dropped serial bit. */
	prev_eedata = eeprom_पढ़ो(ioaddr, 6);
	क्रम (i = 0; i < 3; i++) अणु
		पूर्णांक eedata = eeprom_पढ़ो(ioaddr, i + 7);
		dev->dev_addr[i*2] = (eedata << 1) + (prev_eedata >> 15);
		dev->dev_addr[i*2+1] = eedata >> 7;
		prev_eedata = eedata;
	पूर्ण

	np = netdev_priv(dev);
	np->ioaddr = ioaddr;

	netअगर_napi_add(dev, &np->napi, natsemi_poll, 64);
	np->dev = dev;

	np->pci_dev = pdev;
	pci_set_drvdata(pdev, dev);
	np->iosize = iosize;
	spin_lock_init(&np->lock);
	np->msg_enable = (debug >= 0) ? (1<<debug)-1 : NATSEMI_DEF_MSG;
	np->hands_off = 0;
	np->पूर्णांकr_status = 0;
	np->eeprom_size = natsemi_pci_info[chip_idx].eeprom_size;
	अगर (natsemi_pci_info[chip_idx].flags & NATSEMI_FLAG_IGNORE_PHY)
		np->ignore_phy = 1;
	अन्यथा
		np->ignore_phy = 0;
	np->dspcfg_workaround = dspcfg_workaround;

	/* Initial port:
	 * - If configured to ignore the PHY set up क्रम बाह्यal.
	 * - If the nic was configured to use an बाह्यal phy and अगर find_mii
	 *   finds a phy: use बाह्यal port, first phy that replies.
	 * - Otherwise: पूर्णांकernal port.
	 * Note that the phy address क्रम the पूर्णांकernal phy करोesn't matter:
	 * The address would be used to access a phy over the mii bus, but
	 * the पूर्णांकernal phy is accessed through mapped रेजिस्टरs.
	 */
	अगर (np->ignore_phy || पढ़ोl(ioaddr + ChipConfig) & CfgExtPhy)
		dev->अगर_port = PORT_MII;
	अन्यथा
		dev->अगर_port = PORT_TP;
	/* Reset the chip to erase previous misconfiguration. */
	natsemi_reload_eeprom(dev);
	natsemi_reset(dev);

	अगर (dev->अगर_port != PORT_TP) अणु
		np->phy_addr_बाह्यal = find_mii(dev);
		/* If we're ignoring the PHY it doesn't matter if we can't
		 * find one. */
		अगर (!np->ignore_phy && np->phy_addr_बाह्यal == PHY_ADDR_NONE) अणु
			dev->अगर_port = PORT_TP;
			np->phy_addr_बाह्यal = PHY_ADDR_INTERNAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		np->phy_addr_बाह्यal = PHY_ADDR_INTERNAL;
	पूर्ण

	option = find_cnt < MAX_UNITS ? options[find_cnt] : 0;
	/* The lower four bits are the media type. */
	अगर (option) अणु
		अगर (option & 0x200)
			np->full_duplex = 1;
		अगर (option & 15)
			prपूर्णांकk(KERN_INFO
				"natsemi %s: ignoring user supplied media type %d",
				pci_name(np->pci_dev), option & 15);
	पूर्ण
	अगर (find_cnt < MAX_UNITS  &&  full_duplex[find_cnt])
		np->full_duplex = 1;

	dev->netdev_ops = &natsemi_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	dev->ethtool_ops = &ethtool_ops;

	/* MTU range: 64 - 2024 */
	dev->min_mtu = ETH_ZLEN + ETH_FCS_LEN;
	dev->max_mtu = NATSEMI_RX_LIMIT - NATSEMI_HEADERS;

	अगर (mtu)
		dev->mtu = mtu;

	natsemi_init_media(dev);

	/* save the silicon revision क्रम later querying */
	np->srr = पढ़ोl(ioaddr + SiliconRev);
	अगर (netअगर_msg_hw(np))
		prपूर्णांकk(KERN_INFO "natsemi %s: silicon revision %#04x.\n",
				pci_name(np->pci_dev), np->srr);

	i = रेजिस्टर_netdev(dev);
	अगर (i)
		जाओ err_रेजिस्टर_netdev;
	i = NATSEMI_CREATE_खाता(pdev, dspcfg_workaround);
	अगर (i)
		जाओ err_create_file;

	अगर (netअगर_msg_drv(np)) अणु
		prपूर्णांकk(KERN_INFO "natsemi %s: %s at %#08llx "
		       "(%s), %pM, IRQ %d",
		       dev->name, natsemi_pci_info[chip_idx].name,
		       (अचिन्हित दीर्घ दीर्घ)iostart, pci_name(np->pci_dev),
		       dev->dev_addr, irq);
		अगर (dev->अगर_port == PORT_TP)
			prपूर्णांकk(", port TP.\n");
		अन्यथा अगर (np->ignore_phy)
			prपूर्णांकk(", port MII, ignoring PHY\n");
		अन्यथा
			prपूर्णांकk(", port MII, phy ad %d.\n", np->phy_addr_बाह्यal);
	पूर्ण
	वापस 0;

 err_create_file:
 	unरेजिस्टर_netdev(dev);

 err_रेजिस्टर_netdev:
	iounmap(ioaddr);

 err_ioremap:
	pci_release_regions(pdev);

 err_pci_request_regions:
	मुक्त_netdev(dev);
	वापस i;
पूर्ण


/* Read the EEPROM and MII Management Data I/O (MDIO) पूर्णांकerfaces.
   The EEPROM code is क्रम the common 93c06/46 EEPROMs with 6 bit addresses. */

/* Delay between EEPROM घड़ी transitions.
   No extra delay is needed with 33Mhz PCI, but future 66Mhz access may need
   a delay.  Note that pre-2.0.34 kernels had a cache-alignment bug that
   made udelay() unreliable.
   The old method of using an ISA access as a delay, __SLOW_DOWN_IO__, is
   deprecated.
*/
#घोषणा eeprom_delay(ee_addr)	पढ़ोl(ee_addr)

#घोषणा EE_Write0 (EE_ChipSelect)
#घोषणा EE_Write1 (EE_ChipSelect | EE_DataIn)

/* The EEPROM commands include the alway-set leading bit. */
क्रमागत EEPROM_Cmds अणु
	EE_WriteCmd=(5 << 6), EE_ReadCmd=(6 << 6), EE_EraseCmd=(7 << 6),
पूर्ण;

अटल पूर्णांक eeprom_पढ़ो(व्योम __iomem *addr, पूर्णांक location)
अणु
	पूर्णांक i;
	पूर्णांक retval = 0;
	व्योम __iomem *ee_addr = addr + EECtrl;
	पूर्णांक पढ़ो_cmd = location | EE_ReadCmd;

	ग_लिखोl(EE_Write0, ee_addr);

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 10; i >= 0; i--) अणु
		लघु dataval = (पढ़ो_cmd & (1 << i)) ? EE_Write1 : EE_Write0;
		ग_लिखोl(dataval, ee_addr);
		eeprom_delay(ee_addr);
		ग_लिखोl(dataval | EE_ShअगरtClk, ee_addr);
		eeprom_delay(ee_addr);
	पूर्ण
	ग_लिखोl(EE_ChipSelect, ee_addr);
	eeprom_delay(ee_addr);

	क्रम (i = 0; i < 16; i++) अणु
		ग_लिखोl(EE_ChipSelect | EE_ShअगरtClk, ee_addr);
		eeprom_delay(ee_addr);
		retval |= (पढ़ोl(ee_addr) & EE_DataOut) ? 1 << i : 0;
		ग_लिखोl(EE_ChipSelect, ee_addr);
		eeprom_delay(ee_addr);
	पूर्ण

	/* Terminate the EEPROM access. */
	ग_लिखोl(EE_Write0, ee_addr);
	ग_लिखोl(0, ee_addr);
	वापस retval;
पूर्ण

/* MII transceiver control section.
 * The 83815 series has an पूर्णांकernal transceiver, and we present the
 * पूर्णांकernal management रेजिस्टरs as अगर they were MII connected.
 * External Phy रेजिस्टरs are referenced through the MII पूर्णांकerface.
 */

/* घड़ी transitions >= 20ns (25MHz)
 * One पढ़ोl should be good to PCI @ 100MHz
 */
#घोषणा mii_delay(ioaddr)  पढ़ोl(ioaddr + EECtrl)

अटल पूर्णांक mii_getbit (काष्ठा net_device *dev)
अणु
	पूर्णांक data;
	व्योम __iomem *ioaddr = ns_ioaddr(dev);

	ग_लिखोl(MII_ShअगरtClk, ioaddr + EECtrl);
	data = पढ़ोl(ioaddr + EECtrl);
	ग_लिखोl(0, ioaddr + EECtrl);
	mii_delay(ioaddr);
	वापस (data & MII_Data)? 1 : 0;
पूर्ण

अटल व्योम mii_send_bits (काष्ठा net_device *dev, u32 data, पूर्णांक len)
अणु
	u32 i;
	व्योम __iomem *ioaddr = ns_ioaddr(dev);

	क्रम (i = (1 << (len-1)); i; i >>= 1)
	अणु
		u32 mdio_val = MII_Write | ((data & i)? MII_Data : 0);
		ग_लिखोl(mdio_val, ioaddr + EECtrl);
		mii_delay(ioaddr);
		ग_लिखोl(mdio_val | MII_ShअगरtClk, ioaddr + EECtrl);
		mii_delay(ioaddr);
	पूर्ण
	ग_लिखोl(0, ioaddr + EECtrl);
	mii_delay(ioaddr);
पूर्ण

अटल पूर्णांक miiport_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg)
अणु
	u32 cmd;
	पूर्णांक i;
	u32 retval = 0;

	/* Ensure sync */
	mii_send_bits (dev, 0xffffffff, 32);
	/* ST(2), OP(2), ADDR(5), REG#(5), TA(2), Data(16) total 32 bits */
	/* ST,OP = 0110'b क्रम पढ़ो operation */
	cmd = (0x06 << 10) | (phy_id << 5) | reg;
	mii_send_bits (dev, cmd, 14);
	/* Turnaround */
	अगर (mii_getbit (dev))
		वापस 0;
	/* Read data */
	क्रम (i = 0; i < 16; i++) अणु
		retval <<= 1;
		retval |= mii_getbit (dev);
	पूर्ण
	/* End cycle */
	mii_getbit (dev);
	वापस retval;
पूर्ण

अटल व्योम miiport_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg, u16 data)
अणु
	u32 cmd;

	/* Ensure sync */
	mii_send_bits (dev, 0xffffffff, 32);
	/* ST(2), OP(2), ADDR(5), REG#(5), TA(2), Data(16) total 32 bits */
	/* ST,OP,AAAAA,RRRRR,TA = 0101xxxxxxxxxx10'b = 0x5002 क्रम ग_लिखो */
	cmd = (0x5002 << 16) | (phy_id << 23) | (reg << 18) | data;
	mii_send_bits (dev, cmd, 32);
	/* End cycle */
	mii_getbit (dev);
पूर्ण

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक reg)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);

	/* The 83815 series has two ports:
	 * - an पूर्णांकernal transceiver
	 * - an बाह्यal mii bus
	 */
	अगर (dev->अगर_port == PORT_TP)
		वापस पढ़ोw(ioaddr+BasicControl+(reg<<2));
	अन्यथा
		वापस miiport_पढ़ो(dev, np->phy_addr_बाह्यal, reg);
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक reg, u16 data)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);

	/* The 83815 series has an पूर्णांकernal transceiver; handle separately */
	अगर (dev->अगर_port == PORT_TP)
		ग_लिखोw(data, ioaddr+BasicControl+(reg<<2));
	अन्यथा
		miiport_ग_लिखो(dev, np->phy_addr_बाह्यal, reg, data);
पूर्ण

अटल व्योम init_phy_fixup(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);
	पूर्णांक i;
	u32 cfg;
	u16 पंचांगp;

	/* restore stuff lost when घातer was out */
	पंचांगp = mdio_पढ़ो(dev, MII_BMCR);
	अगर (np->स्वतःneg == AUTONEG_ENABLE) अणु
		/* renegotiate अगर something changed */
		अगर ((पंचांगp & BMCR_ANENABLE) == 0 ||
		    np->advertising != mdio_पढ़ो(dev, MII_ADVERTISE))
		अणु
			/* turn on स्वतःnegotiation and क्रमce negotiation */
			पंचांगp |= (BMCR_ANENABLE | BMCR_ANRESTART);
			mdio_ग_लिखो(dev, MII_ADVERTISE, np->advertising);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* turn off स्वतः negotiation, set speed and duplनिकासy */
		पंचांगp &= ~(BMCR_ANENABLE | BMCR_SPEED100 | BMCR_FULLDPLX);
		अगर (np->speed == SPEED_100)
			पंचांगp |= BMCR_SPEED100;
		अगर (np->duplex == DUPLEX_FULL)
			पंचांगp |= BMCR_FULLDPLX;
		/*
		 * Note: there is no good way to inक्रमm the link partner
		 * that our capabilities changed. The user has to unplug
		 * and replug the network cable after some changes, e.g.
		 * after चयनing from 10HD, स्वतःneg off to 100 HD,
		 * स्वतःneg off.
		 */
	पूर्ण
	mdio_ग_लिखो(dev, MII_BMCR, पंचांगp);
	पढ़ोl(ioaddr + ChipConfig);
	udelay(1);

	/* find out what phy this is */
	np->mii = (mdio_पढ़ो(dev, MII_PHYSID1) << 16)
				+ mdio_पढ़ो(dev, MII_PHYSID2);

	/* handle बाह्यal phys here */
	चयन (np->mii) अणु
	हाल PHYID_AM79C874:
		/* phy specअगरic configuration क्रम fibre/tp operation */
		पंचांगp = mdio_पढ़ो(dev, MII_MCTRL);
		पंचांगp &= ~(MII_FX_SEL | MII_EN_SCRM);
		अगर (dev->अगर_port == PORT_FIBRE)
			पंचांगp |= MII_FX_SEL;
		अन्यथा
			पंचांगp |= MII_EN_SCRM;
		mdio_ग_लिखो(dev, MII_MCTRL, पंचांगp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	cfg = पढ़ोl(ioaddr + ChipConfig);
	अगर (cfg & CfgExtPhy)
		वापस;

	/* On page 78 of the spec, they recommend some settings क्रम "optimum
	   perक्रमmance" to be करोne in sequence.  These settings optimize some
	   of the 100Mbit स्वतःdetection circuitry.  They say we only want to
	   करो this क्रम rev C of the chip, but engineers at NSC (Bradley
	   Kennedy) recommends always setting them.  If you करोn't, you get
	   errors on some स्वतःnegotiations that make the device unusable.

	   It seems that the DSP needs a few usec to reinitialize after
	   the start of the phy. Just retry writing these values until they
	   stick.
	*/
	क्रम (i=0;i<NATSEMI_HW_TIMEOUT;i++) अणु

		पूर्णांक dspcfg;
		ग_लिखोw(1, ioaddr + PGSEL);
		ग_लिखोw(PMDCSR_VAL, ioaddr + PMDCSR);
		ग_लिखोw(TSTDAT_VAL, ioaddr + TSTDAT);
		np->dspcfg = (np->srr <= SRR_DP83815_C)?
			DSPCFG_VAL : (DSPCFG_COEF | पढ़ोw(ioaddr + DSPCFG));
		ग_लिखोw(np->dspcfg, ioaddr + DSPCFG);
		ग_लिखोw(SDCFG_VAL, ioaddr + SDCFG);
		ग_लिखोw(0, ioaddr + PGSEL);
		पढ़ोl(ioaddr + ChipConfig);
		udelay(10);

		ग_लिखोw(1, ioaddr + PGSEL);
		dspcfg = पढ़ोw(ioaddr + DSPCFG);
		ग_लिखोw(0, ioaddr + PGSEL);
		अगर (np->dspcfg == dspcfg)
			अवरोध;
	पूर्ण

	अगर (netअगर_msg_link(np)) अणु
		अगर (i==NATSEMI_HW_TIMEOUT) अणु
			prपूर्णांकk(KERN_INFO
				"%s: DSPCFG mismatch after retrying for %d usec.\n",
				dev->name, i*10);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_INFO
				"%s: DSPCFG accepted after %d usec.\n",
				dev->name, i*10);
		पूर्ण
	पूर्ण
	/*
	 * Enable PHY Specअगरic event based पूर्णांकerrupts.  Link state change
	 * and Auto-Negotiation Completion are among the affected.
	 * Read the पूर्णांकr status to clear it (needed क्रम wake events).
	 */
	पढ़ोw(ioaddr + MIntrStatus);
	ग_लिखोw(MICRIntEn, ioaddr + MIntrCtrl);
पूर्ण

अटल पूर्णांक चयन_port_बाह्यal(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);
	u32 cfg;

	cfg = पढ़ोl(ioaddr + ChipConfig);
	अगर (cfg & CfgExtPhy)
		वापस 0;

	अगर (netअगर_msg_link(np)) अणु
		prपूर्णांकk(KERN_INFO "%s: switching to external transceiver.\n",
				dev->name);
	पूर्ण

	/* 1) चयन back to बाह्यal phy */
	ग_लिखोl(cfg | (CfgExtPhy | CfgPhyDis), ioaddr + ChipConfig);
	पढ़ोl(ioaddr + ChipConfig);
	udelay(1);

	/* 2) reset the बाह्यal phy: */
	/* resetting the बाह्यal PHY has been known to cause a hub supplying
	 * घातer over Ethernet to समाप्त the घातer.  We करोn't want to समाप्त
	 * घातer to this computer, so we aव्योम resetting the phy.
	 */

	/* 3) reinit the phy fixup, it got lost during घातer करोwn. */
	move_पूर्णांक_phy(dev, np->phy_addr_बाह्यal);
	init_phy_fixup(dev);

	वापस 1;
पूर्ण

अटल पूर्णांक चयन_port_पूर्णांकernal(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);
	पूर्णांक i;
	u32 cfg;
	u16 bmcr;

	cfg = पढ़ोl(ioaddr + ChipConfig);
	अगर (!(cfg &CfgExtPhy))
		वापस 0;

	अगर (netअगर_msg_link(np)) अणु
		prपूर्णांकk(KERN_INFO "%s: switching to internal transceiver.\n",
				dev->name);
	पूर्ण
	/* 1) चयन back to पूर्णांकernal phy: */
	cfg = cfg & ~(CfgExtPhy | CfgPhyDis);
	ग_लिखोl(cfg, ioaddr + ChipConfig);
	पढ़ोl(ioaddr + ChipConfig);
	udelay(1);

	/* 2) reset the पूर्णांकernal phy: */
	bmcr = पढ़ोw(ioaddr+BasicControl+(MII_BMCR<<2));
	ग_लिखोl(bmcr | BMCR_RESET, ioaddr+BasicControl+(MII_BMCR<<2));
	पढ़ोl(ioaddr + ChipConfig);
	udelay(10);
	क्रम (i=0;i<NATSEMI_HW_TIMEOUT;i++) अणु
		bmcr = पढ़ोw(ioaddr+BasicControl+(MII_BMCR<<2));
		अगर (!(bmcr & BMCR_RESET))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (i==NATSEMI_HW_TIMEOUT && netअगर_msg_link(np)) अणु
		prपूर्णांकk(KERN_INFO
			"%s: phy reset did not complete in %d usec.\n",
			dev->name, i*10);
	पूर्ण
	/* 3) reinit the phy fixup, it got lost during घातer करोwn. */
	init_phy_fixup(dev);

	वापस 1;
पूर्ण

/* Scan क्रम a PHY on the बाह्यal mii bus.
 * There are two tricky poपूर्णांकs:
 * - Do not scan जबतक the पूर्णांकernal phy is enabled. The पूर्णांकernal phy will
 *   crash: e.g. पढ़ोs from the DSPCFG रेजिस्टर will वापस odd values and
 *   the nasty अक्रमom phy reset code will reset the nic every few seconds.
 * - The पूर्णांकernal phy must be moved around, an बाह्यal phy could
 *   have the same address as the पूर्णांकernal phy.
 */
अटल पूर्णांक find_mii(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक पंचांगp;
	पूर्णांक i;
	पूर्णांक did_चयन;

	/* Switch to बाह्यal phy */
	did_चयन = चयन_port_बाह्यal(dev);

	/* Scan the possible phy addresses:
	 *
	 * PHY address 0 means that the phy is in isolate mode. Not yet
	 * supported due to lack of test hardware. User space should
	 * handle it through ethtool.
	 */
	क्रम (i = 1; i <= 31; i++) अणु
		move_पूर्णांक_phy(dev, i);
		पंचांगp = miiport_पढ़ो(dev, i, MII_BMSR);
		अगर (पंचांगp != 0xffff && पंचांगp != 0x0000) अणु
			/* found something! */
			np->mii = (mdio_पढ़ो(dev, MII_PHYSID1) << 16)
					+ mdio_पढ़ो(dev, MII_PHYSID2);
	 		अगर (netअगर_msg_probe(np)) अणु
				prपूर्णांकk(KERN_INFO "natsemi %s: found external phy %08x at address %d.\n",
						pci_name(np->pci_dev), np->mii, i);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	/* And चयन back to पूर्णांकernal phy: */
	अगर (did_चयन)
		चयन_port_पूर्णांकernal(dev);
	वापस i;
पूर्ण

/* CFG bits [13:16] [18:23] */
#घोषणा CFG_RESET_SAVE 0xfde000
/* WCSR bits [0:4] [9:10] */
#घोषणा WCSR_RESET_SAVE 0x61f
/* RFCR bits [20] [22] [27:31] */
#घोषणा RFCR_RESET_SAVE 0xf8500000

अटल व्योम natsemi_reset(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	u32 cfg;
	u32 wcsr;
	u32 rfcr;
	u16 pmatch[3];
	u16 sopass[3];
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);

	/*
	 * Resetting the chip causes some रेजिस्टरs to be lost.
	 * Natsemi suggests NOT reloading the EEPROM जबतक live, so instead
	 * we save the state that would have been loaded from EEPROM
	 * on a normal घातer-up (see the spec EEPROM map).  This assumes
	 * whoever calls this will follow up with init_रेजिस्टरs() eventually.
	 */

	/* CFG */
	cfg = पढ़ोl(ioaddr + ChipConfig) & CFG_RESET_SAVE;
	/* WCSR */
	wcsr = पढ़ोl(ioaddr + WOLCmd) & WCSR_RESET_SAVE;
	/* RFCR */
	rfcr = पढ़ोl(ioaddr + RxFilterAddr) & RFCR_RESET_SAVE;
	/* PMATCH */
	क्रम (i = 0; i < 3; i++) अणु
		ग_लिखोl(i*2, ioaddr + RxFilterAddr);
		pmatch[i] = पढ़ोw(ioaddr + RxFilterData);
	पूर्ण
	/* SOPAS */
	क्रम (i = 0; i < 3; i++) अणु
		ग_लिखोl(0xa+(i*2), ioaddr + RxFilterAddr);
		sopass[i] = पढ़ोw(ioaddr + RxFilterData);
	पूर्ण

	/* now whack the chip */
	ग_लिखोl(ChipReset, ioaddr + ChipCmd);
	क्रम (i=0;i<NATSEMI_HW_TIMEOUT;i++) अणु
		अगर (!(पढ़ोl(ioaddr + ChipCmd) & ChipReset))
			अवरोध;
		udelay(5);
	पूर्ण
	अगर (i==NATSEMI_HW_TIMEOUT) अणु
		prपूर्णांकk(KERN_WARNING "%s: reset did not complete in %d usec.\n",
			dev->name, i*5);
	पूर्ण अन्यथा अगर (netअगर_msg_hw(np)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: reset completed in %d usec.\n",
			dev->name, i*5);
	पूर्ण

	/* restore CFG */
	cfg |= पढ़ोl(ioaddr + ChipConfig) & ~CFG_RESET_SAVE;
	/* turn on बाह्यal phy अगर it was selected */
	अगर (dev->अगर_port == PORT_TP)
		cfg &= ~(CfgExtPhy | CfgPhyDis);
	अन्यथा
		cfg |= (CfgExtPhy | CfgPhyDis);
	ग_लिखोl(cfg, ioaddr + ChipConfig);
	/* restore WCSR */
	wcsr |= पढ़ोl(ioaddr + WOLCmd) & ~WCSR_RESET_SAVE;
	ग_लिखोl(wcsr, ioaddr + WOLCmd);
	/* पढ़ो RFCR */
	rfcr |= पढ़ोl(ioaddr + RxFilterAddr) & ~RFCR_RESET_SAVE;
	/* restore PMATCH */
	क्रम (i = 0; i < 3; i++) अणु
		ग_लिखोl(i*2, ioaddr + RxFilterAddr);
		ग_लिखोw(pmatch[i], ioaddr + RxFilterData);
	पूर्ण
	क्रम (i = 0; i < 3; i++) अणु
		ग_लिखोl(0xa+(i*2), ioaddr + RxFilterAddr);
		ग_लिखोw(sopass[i], ioaddr + RxFilterData);
	पूर्ण
	/* restore RFCR */
	ग_लिखोl(rfcr, ioaddr + RxFilterAddr);
पूर्ण

अटल व्योम reset_rx(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);

	np->पूर्णांकr_status &= ~RxResetDone;

	ग_लिखोl(RxReset, ioaddr + ChipCmd);

	क्रम (i=0;i<NATSEMI_HW_TIMEOUT;i++) अणु
		np->पूर्णांकr_status |= पढ़ोl(ioaddr + IntrStatus);
		अगर (np->पूर्णांकr_status & RxResetDone)
			अवरोध;
		udelay(15);
	पूर्ण
	अगर (i==NATSEMI_HW_TIMEOUT) अणु
		prपूर्णांकk(KERN_WARNING "%s: RX reset did not complete in %d usec.\n",
		       dev->name, i*15);
	पूर्ण अन्यथा अगर (netअगर_msg_hw(np)) अणु
		prपूर्णांकk(KERN_WARNING "%s: RX reset took %d usec.\n",
		       dev->name, i*15);
	पूर्ण
पूर्ण

अटल व्योम natsemi_reload_eeprom(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);
	पूर्णांक i;

	ग_लिखोl(EepromReload, ioaddr + PCIBusCfg);
	क्रम (i=0;i<NATSEMI_HW_TIMEOUT;i++) अणु
		udelay(50);
		अगर (!(पढ़ोl(ioaddr + PCIBusCfg) & EepromReload))
			अवरोध;
	पूर्ण
	अगर (i==NATSEMI_HW_TIMEOUT) अणु
		prपूर्णांकk(KERN_WARNING "natsemi %s: EEPROM did not reload in %d usec.\n",
			pci_name(np->pci_dev), i*50);
	पूर्ण अन्यथा अगर (netअगर_msg_hw(np)) अणु
		prपूर्णांकk(KERN_DEBUG "natsemi %s: EEPROM reloaded in %d usec.\n",
			pci_name(np->pci_dev), i*50);
	पूर्ण
पूर्ण

अटल व्योम natsemi_stop_rxtx(काष्ठा net_device *dev)
अणु
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	ग_लिखोl(RxOff | TxOff, ioaddr + ChipCmd);
	क्रम(i=0;i< NATSEMI_HW_TIMEOUT;i++) अणु
		अगर ((पढ़ोl(ioaddr + ChipCmd) & (TxOn|RxOn)) == 0)
			अवरोध;
		udelay(5);
	पूर्ण
	अगर (i==NATSEMI_HW_TIMEOUT) अणु
		prपूर्णांकk(KERN_WARNING "%s: Tx/Rx process did not stop in %d usec.\n",
			dev->name, i*5);
	पूर्ण अन्यथा अगर (netअगर_msg_hw(np)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Tx/Rx process stopped in %d usec.\n",
			dev->name, i*5);
	पूर्ण
पूर्ण

अटल पूर्णांक netdev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	स्थिर पूर्णांक irq = np->pci_dev->irq;
	पूर्णांक i;

	/* Reset the chip, just in हाल. */
	natsemi_reset(dev);

	i = request_irq(irq, पूर्णांकr_handler, IRQF_SHARED, dev->name, dev);
	अगर (i) वापस i;

	अगर (netअगर_msg_अगरup(np))
		prपूर्णांकk(KERN_DEBUG "%s: netdev_open() irq %d.\n",
			dev->name, irq);
	i = alloc_ring(dev);
	अगर (i < 0) अणु
		मुक्त_irq(irq, dev);
		वापस i;
	पूर्ण
	napi_enable(&np->napi);

	init_ring(dev);
	spin_lock_irq(&np->lock);
	init_रेजिस्टरs(dev);
	/* now set the MAC address according to dev->dev_addr */
	क्रम (i = 0; i < 3; i++) अणु
		u16 mac = (dev->dev_addr[2*i+1]<<8) + dev->dev_addr[2*i];

		ग_लिखोl(i*2, ioaddr + RxFilterAddr);
		ग_लिखोw(mac, ioaddr + RxFilterData);
	पूर्ण
	ग_लिखोl(np->cur_rx_mode, ioaddr + RxFilterAddr);
	spin_unlock_irq(&np->lock);

	netअगर_start_queue(dev);

	अगर (netअगर_msg_अगरup(np))
		prपूर्णांकk(KERN_DEBUG "%s: Done netdev_open(), status: %#08x.\n",
			dev->name, (पूर्णांक)पढ़ोl(ioaddr + ChipCmd));

	/* Set the समयr to check क्रम link beat. */
	समयr_setup(&np->समयr, netdev_समयr, 0);
	np->समयr.expires = round_jअगरfies(jअगरfies + NATSEMI_TIMER_FREQ);
	add_समयr(&np->समयr);

	वापस 0;
पूर्ण

अटल व्योम करो_cable_magic(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = ns_ioaddr(dev);

	अगर (dev->अगर_port != PORT_TP)
		वापस;

	अगर (np->srr >= SRR_DP83816_A5)
		वापस;

	/*
	 * 100 MBit links with लघु cables can trip an issue with the chip.
	 * The problem manअगरests as lots of CRC errors and/or flickering
	 * activity LED जबतक idle.  This process is based on inकाष्ठाions
	 * from engineers at National.
	 */
	अगर (पढ़ोl(ioaddr + ChipConfig) & CfgSpeed100) अणु
		u16 data;

		ग_लिखोw(1, ioaddr + PGSEL);
		/*
		 * coefficient visibility should alपढ़ोy be enabled via
		 * DSPCFG | 0x1000
		 */
		data = पढ़ोw(ioaddr + TSTDAT) & 0xff;
		/*
		 * the value must be negative, and within certain values
		 * (these values all come from National)
		 */
		अगर (!(data & 0x80) || ((data >= 0xd8) && (data <= 0xff))) अणु
			np = netdev_priv(dev);

			/* the bug has been triggered - fix the coefficient */
			ग_लिखोw(TSTDAT_FIXED, ioaddr + TSTDAT);
			/* lock the value */
			data = पढ़ोw(ioaddr + DSPCFG);
			np->dspcfg = data | DSPCFG_LOCK;
			ग_लिखोw(np->dspcfg, ioaddr + DSPCFG);
		पूर्ण
		ग_लिखोw(0, ioaddr + PGSEL);
	पूर्ण
पूर्ण

अटल व्योम unकरो_cable_magic(काष्ठा net_device *dev)
अणु
	u16 data;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);

	अगर (dev->अगर_port != PORT_TP)
		वापस;

	अगर (np->srr >= SRR_DP83816_A5)
		वापस;

	ग_लिखोw(1, ioaddr + PGSEL);
	/* make sure the lock bit is clear */
	data = पढ़ोw(ioaddr + DSPCFG);
	np->dspcfg = data & ~DSPCFG_LOCK;
	ग_लिखोw(np->dspcfg, ioaddr + DSPCFG);
	ग_लिखोw(0, ioaddr + PGSEL);
पूर्ण

अटल व्योम check_link(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	पूर्णांक duplex = np->duplex;
	u16 bmsr;

	/* If we are ignoring the PHY then करोn't try पढ़ोing it. */
	अगर (np->ignore_phy)
		जाओ propagate_state;

	/* The link status field is latched: it reमुख्यs low after a temporary
	 * link failure until it's पढ़ो. We need the current link status,
	 * thus पढ़ो twice.
	 */
	mdio_पढ़ो(dev, MII_BMSR);
	bmsr = mdio_पढ़ो(dev, MII_BMSR);

	अगर (!(bmsr & BMSR_LSTATUS)) अणु
		अगर (netअगर_carrier_ok(dev)) अणु
			अगर (netअगर_msg_link(np))
				prपूर्णांकk(KERN_NOTICE "%s: link down.\n",
				       dev->name);
			netअगर_carrier_off(dev);
			unकरो_cable_magic(dev);
		पूर्ण
		वापस;
	पूर्ण
	अगर (!netअगर_carrier_ok(dev)) अणु
		अगर (netअगर_msg_link(np))
			prपूर्णांकk(KERN_NOTICE "%s: link up.\n", dev->name);
		netअगर_carrier_on(dev);
		करो_cable_magic(dev);
	पूर्ण

	duplex = np->full_duplex;
	अगर (!duplex) अणु
		अगर (bmsr & BMSR_ANEGCOMPLETE) अणु
			पूर्णांक पंचांगp = mii_nway_result(
				np->advertising & mdio_पढ़ो(dev, MII_LPA));
			अगर (पंचांगp == LPA_100FULL || पंचांगp == LPA_10FULL)
				duplex = 1;
		पूर्ण अन्यथा अगर (mdio_पढ़ो(dev, MII_BMCR) & BMCR_FULLDPLX)
			duplex = 1;
	पूर्ण

propagate_state:
	/* अगर duplex is set then bit 28 must be set, too */
	अगर (duplex ^ !!(np->rx_config & RxAcceptTx)) अणु
		अगर (netअगर_msg_link(np))
			prपूर्णांकk(KERN_INFO
				"%s: Setting %s-duplex based on negotiated "
				"link capability.\n", dev->name,
				duplex ? "full" : "half");
		अगर (duplex) अणु
			np->rx_config |= RxAcceptTx;
			np->tx_config |= TxCarrierIgn | TxHeartIgn;
		पूर्ण अन्यथा अणु
			np->rx_config &= ~RxAcceptTx;
			np->tx_config &= ~(TxCarrierIgn | TxHeartIgn);
		पूर्ण
		ग_लिखोl(np->tx_config, ioaddr + TxConfig);
		ग_लिखोl(np->rx_config, ioaddr + RxConfig);
	पूर्ण
पूर्ण

अटल व्योम init_रेजिस्टरs(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);

	init_phy_fixup(dev);

	/* clear any पूर्णांकerrupts that are pending, such as wake events */
	पढ़ोl(ioaddr + IntrStatus);

	ग_लिखोl(np->ring_dma, ioaddr + RxRingPtr);
	ग_लिखोl(np->ring_dma + RX_RING_SIZE * माप(काष्ठा netdev_desc),
		ioaddr + TxRingPtr);

	/* Initialize other रेजिस्टरs.
	 * Configure the PCI bus bursts and FIFO thresholds.
	 * Configure क्रम standard, in-spec Ethernet.
	 * Start with half-duplex. check_link will update
	 * to the correct settings.
	 */

	/* DRTH: 2: start tx अगर 64 bytes are in the fअगरo
	 * FLTH: 0x10: refill with next packet अगर 512 bytes are मुक्त
	 * MXDMA: 0: up to 256 byte bursts.
	 * 	MXDMA must be <= FLTH
	 * ECRETRY=1
	 * ATP=1
	 */
	np->tx_config = TxAutoPad | TxCollRetry | TxMxdma_256 |
				TX_FLTH_VAL | TX_DRTH_VAL_START;
	ग_लिखोl(np->tx_config, ioaddr + TxConfig);

	/* DRTH 0x10: start copying to memory अगर 128 bytes are in the fअगरo
	 * MXDMA 0: up to 256 byte bursts
	 */
	np->rx_config = RxMxdma_256 | RX_DRTH_VAL;
	/* अगर receive ring now has bigger buffers than normal, enable jumbo */
	अगर (np->rx_buf_sz > NATSEMI_LONGPKT)
		np->rx_config |= RxAcceptLong;

	ग_लिखोl(np->rx_config, ioaddr + RxConfig);

	/* Disable PME:
	 * The PME bit is initialized from the EEPROM contents.
	 * PCI cards probably have PME disabled, but motherboard
	 * implementations may have PME set to enable WakeOnLan.
	 * With PME set the chip will scan incoming packets but
	 * nothing will be written to memory. */
	np->SavedClkRun = पढ़ोl(ioaddr + ClkRun);
	ग_लिखोl(np->SavedClkRun & ~PMEEnable, ioaddr + ClkRun);
	अगर (np->SavedClkRun & PMEStatus && netअगर_msg_wol(np)) अणु
		prपूर्णांकk(KERN_NOTICE "%s: Wake-up event %#08x\n",
			dev->name, पढ़ोl(ioaddr + WOLCmd));
	पूर्ण

	check_link(dev);
	__set_rx_mode(dev);

	/* Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ग_लिखोl(DEFAULT_INTR, ioaddr + IntrMask);
	natsemi_irq_enable(dev);

	ग_लिखोl(RxOn | TxOn, ioaddr + ChipCmd);
	ग_लिखोl(StatsClear, ioaddr + StatsCtrl); /* Clear Stats */
पूर्ण

/*
 * netdev_समयr:
 * Purpose:
 * 1) check क्रम link changes. Usually they are handled by the MII पूर्णांकerrupt
 *    but it करोesn't hurt to check twice.
 * 2) check क्रम sudden death of the NIC:
 *    It seems that a reference set क्रम this chip went out with incorrect info,
 *    and there exist boards that aren't quite right.  An unexpected voltage
 *    drop can cause the PHY to get itself in a weird state (basically reset).
 *    NOTE: this only seems to affect revC chips.  The user can disable
 *    this check via dspcfg_workaround sysfs option.
 * 3) check of death of the RX path due to OOM
 */
अटल व्योम netdev_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा netdev_निजी *np = from_समयr(np, t, समयr);
	काष्ठा net_device *dev = np->dev;
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	पूर्णांक next_tick = NATSEMI_TIMER_FREQ;
	स्थिर पूर्णांक irq = np->pci_dev->irq;

	अगर (netअगर_msg_समयr(np)) अणु
		/* DO NOT पढ़ो the IntrStatus रेजिस्टर,
		 * a पढ़ो clears any pending पूर्णांकerrupts.
		 */
		prपूर्णांकk(KERN_DEBUG "%s: Media selection timer tick.\n",
			dev->name);
	पूर्ण

	अगर (dev->अगर_port == PORT_TP) अणु
		u16 dspcfg;

		spin_lock_irq(&np->lock);
		/* check क्रम a nasty अक्रमom phy-reset - use dspcfg as a flag */
		ग_लिखोw(1, ioaddr+PGSEL);
		dspcfg = पढ़ोw(ioaddr+DSPCFG);
		ग_लिखोw(0, ioaddr+PGSEL);
		अगर (np->dspcfg_workaround && dspcfg != np->dspcfg) अणु
			अगर (!netअगर_queue_stopped(dev)) अणु
				spin_unlock_irq(&np->lock);
				अगर (netअगर_msg_drv(np))
					prपूर्णांकk(KERN_NOTICE "%s: possible phy reset: "
						"re-initializing\n", dev->name);
				disable_irq(irq);
				spin_lock_irq(&np->lock);
				natsemi_stop_rxtx(dev);
				dump_ring(dev);
				reinit_ring(dev);
				init_रेजिस्टरs(dev);
				spin_unlock_irq(&np->lock);
				enable_irq(irq);
			पूर्ण अन्यथा अणु
				/* hurry back */
				next_tick = HZ;
				spin_unlock_irq(&np->lock);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* init_रेजिस्टरs() calls check_link() क्रम the above हाल */
			check_link(dev);
			spin_unlock_irq(&np->lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_lock_irq(&np->lock);
		check_link(dev);
		spin_unlock_irq(&np->lock);
	पूर्ण
	अगर (np->oom) अणु
		disable_irq(irq);
		np->oom = 0;
		refill_rx(dev);
		enable_irq(irq);
		अगर (!np->oom) अणु
			ग_लिखोl(RxOn, ioaddr + ChipCmd);
		पूर्ण अन्यथा अणु
			next_tick = 1;
		पूर्ण
	पूर्ण

	अगर (next_tick > 1)
		mod_समयr(&np->समयr, round_jअगरfies(jअगरfies + next_tick));
	अन्यथा
		mod_समयr(&np->समयr, jअगरfies + next_tick);
पूर्ण

अटल व्योम dump_ring(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	अगर (netअगर_msg_pktdata(np)) अणु
		पूर्णांक i;
		prपूर्णांकk(KERN_DEBUG "  Tx ring at %p:\n", np->tx_ring);
		क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
			prपूर्णांकk(KERN_DEBUG " #%d desc. %#08x %#08x %#08x.\n",
				i, np->tx_ring[i].next_desc,
				np->tx_ring[i].cmd_status,
				np->tx_ring[i].addr);
		पूर्ण
		prपूर्णांकk(KERN_DEBUG "  Rx ring %p:\n", np->rx_ring);
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			prपूर्णांकk(KERN_DEBUG " #%d desc. %#08x %#08x %#08x.\n",
				i, np->rx_ring[i].next_desc,
				np->rx_ring[i].cmd_status,
				np->rx_ring[i].addr);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ns_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	स्थिर पूर्णांक irq = np->pci_dev->irq;

	disable_irq(irq);
	spin_lock_irq(&np->lock);
	अगर (!np->hands_off) अणु
		अगर (netअगर_msg_tx_err(np))
			prपूर्णांकk(KERN_WARNING
				"%s: Transmit timed out, status %#08x,"
				" resetting...\n",
				dev->name, पढ़ोl(ioaddr + IntrStatus));
		dump_ring(dev);

		natsemi_reset(dev);
		reinit_ring(dev);
		init_रेजिस्टरs(dev);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING
			"%s: tx_timeout while in hands_off state?\n",
			dev->name);
	पूर्ण
	spin_unlock_irq(&np->lock);
	enable_irq(irq);

	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;
	netअगर_wake_queue(dev);
पूर्ण

अटल पूर्णांक alloc_ring(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	np->rx_ring = dma_alloc_coherent(&np->pci_dev->dev,
					 माप(काष्ठा netdev_desc) * (RX_RING_SIZE + TX_RING_SIZE),
					 &np->ring_dma, GFP_KERNEL);
	अगर (!np->rx_ring)
		वापस -ENOMEM;
	np->tx_ring = &np->rx_ring[RX_RING_SIZE];
	वापस 0;
पूर्ण

अटल व्योम refill_rx(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	/* Refill the Rx ring buffers. */
	क्रम (; np->cur_rx - np->dirty_rx > 0; np->dirty_rx++) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक entry = np->dirty_rx % RX_RING_SIZE;
		अगर (np->rx_skbuff[entry] == शून्य) अणु
			अचिन्हित पूर्णांक buflen = np->rx_buf_sz+NATSEMI_PADDING;
			skb = netdev_alloc_skb(dev, buflen);
			np->rx_skbuff[entry] = skb;
			अगर (skb == शून्य)
				अवरोध; /* Better luck next round. */
			np->rx_dma[entry] = dma_map_single(&np->pci_dev->dev,
							   skb->data, buflen,
							   DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&np->pci_dev->dev, np->rx_dma[entry])) अणु
				dev_kमुक्त_skb_any(skb);
				np->rx_skbuff[entry] = शून्य;
				अवरोध; /* Better luck next round. */
			पूर्ण
			np->rx_ring[entry].addr = cpu_to_le32(np->rx_dma[entry]);
		पूर्ण
		np->rx_ring[entry].cmd_status = cpu_to_le32(np->rx_buf_sz);
	पूर्ण
	अगर (np->cur_rx - np->dirty_rx == RX_RING_SIZE) अणु
		अगर (netअगर_msg_rx_err(np))
			prपूर्णांकk(KERN_WARNING "%s: going OOM.\n", dev->name);
		np->oom = 1;
	पूर्ण
पूर्ण

अटल व्योम set_bufsize(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	अगर (dev->mtu <= ETH_DATA_LEN)
		np->rx_buf_sz = ETH_DATA_LEN + NATSEMI_HEADERS;
	अन्यथा
		np->rx_buf_sz = dev->mtu + NATSEMI_HEADERS;
पूर्ण

/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल व्योम init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	/* 1) TX ring */
	np->dirty_tx = np->cur_tx = 0;
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		np->tx_skbuff[i] = शून्य;
		np->tx_ring[i].next_desc = cpu_to_le32(np->ring_dma
			+माप(काष्ठा netdev_desc)
			*((i+1)%TX_RING_SIZE+RX_RING_SIZE));
		np->tx_ring[i].cmd_status = 0;
	पूर्ण

	/* 2) RX ring */
	np->dirty_rx = 0;
	np->cur_rx = RX_RING_SIZE;
	np->oom = 0;
	set_bufsize(dev);

	np->rx_head_desc = &np->rx_ring[0];

	/* Please be careful beक्रमe changing this loop - at least gcc-2.95.1
	 * miscompiles it otherwise.
	 */
	/* Initialize all Rx descriptors. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		np->rx_ring[i].next_desc = cpu_to_le32(np->ring_dma
				+माप(काष्ठा netdev_desc)
				*((i+1)%RX_RING_SIZE));
		np->rx_ring[i].cmd_status = cpu_to_le32(DescOwn);
		np->rx_skbuff[i] = शून्य;
	पूर्ण
	refill_rx(dev);
	dump_ring(dev);
पूर्ण

अटल व्योम drain_tx(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		अगर (np->tx_skbuff[i]) अणु
			dma_unmap_single(&np->pci_dev->dev, np->tx_dma[i],
					 np->tx_skbuff[i]->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb(np->tx_skbuff[i]);
			dev->stats.tx_dropped++;
		पूर्ण
		np->tx_skbuff[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम drain_rx(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	अचिन्हित पूर्णांक buflen = np->rx_buf_sz;
	पूर्णांक i;

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		np->rx_ring[i].cmd_status = 0;
		np->rx_ring[i].addr = cpu_to_le32(0xBADF00D0); /* An invalid address. */
		अगर (np->rx_skbuff[i]) अणु
			dma_unmap_single(&np->pci_dev->dev, np->rx_dma[i],
					 buflen + NATSEMI_PADDING,
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(np->rx_skbuff[i]);
		पूर्ण
		np->rx_skbuff[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम drain_ring(काष्ठा net_device *dev)
अणु
	drain_rx(dev);
	drain_tx(dev);
पूर्ण

अटल व्योम मुक्त_ring(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	dma_मुक्त_coherent(&np->pci_dev->dev,
			  माप(काष्ठा netdev_desc) * (RX_RING_SIZE + TX_RING_SIZE),
			  np->rx_ring, np->ring_dma);
पूर्ण

अटल व्योम reinit_rx(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	/* RX Ring */
	np->dirty_rx = 0;
	np->cur_rx = RX_RING_SIZE;
	np->rx_head_desc = &np->rx_ring[0];
	/* Initialize all Rx descriptors. */
	क्रम (i = 0; i < RX_RING_SIZE; i++)
		np->rx_ring[i].cmd_status = cpu_to_le32(DescOwn);

	refill_rx(dev);
पूर्ण

अटल व्योम reinit_ring(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	/* drain TX ring */
	drain_tx(dev);
	np->dirty_tx = np->cur_tx = 0;
	क्रम (i=0;i<TX_RING_SIZE;i++)
		np->tx_ring[i].cmd_status = 0;

	reinit_rx(dev);
पूर्ण

अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	अचिन्हित entry;
	अचिन्हित दीर्घ flags;

	/* Note: Ordering is important here, set the field with the
	   "ownership" bit last, and only then increment cur_tx. */

	/* Calculate the next Tx descriptor entry. */
	entry = np->cur_tx % TX_RING_SIZE;

	np->tx_skbuff[entry] = skb;
	np->tx_dma[entry] = dma_map_single(&np->pci_dev->dev, skb->data,
					   skb->len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&np->pci_dev->dev, np->tx_dma[entry])) अणु
		np->tx_skbuff[entry] = शून्य;
		dev_kमुक्त_skb_irq(skb);
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	np->tx_ring[entry].addr = cpu_to_le32(np->tx_dma[entry]);

	spin_lock_irqsave(&np->lock, flags);

	अगर (!np->hands_off) अणु
		np->tx_ring[entry].cmd_status = cpu_to_le32(DescOwn | skb->len);
		/* StrongARM: Explicitly cache flush np->tx_ring and
		 * skb->data,skb->len. */
		wmb();
		np->cur_tx++;
		अगर (np->cur_tx - np->dirty_tx >= TX_QUEUE_LEN - 1) अणु
			netdev_tx_करोne(dev);
			अगर (np->cur_tx - np->dirty_tx >= TX_QUEUE_LEN - 1)
				netअगर_stop_queue(dev);
		पूर्ण
		/* Wake the potentially-idle transmit channel. */
		ग_लिखोl(TxOn, ioaddr + ChipCmd);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_irq(skb);
		dev->stats.tx_dropped++;
	पूर्ण
	spin_unlock_irqrestore(&np->lock, flags);

	अगर (netअगर_msg_tx_queued(np)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Transmit frame #%d queued in slot %d.\n",
			dev->name, np->cur_tx, entry);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम netdev_tx_करोne(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	क्रम (; np->cur_tx - np->dirty_tx > 0; np->dirty_tx++) अणु
		पूर्णांक entry = np->dirty_tx % TX_RING_SIZE;
		अगर (np->tx_ring[entry].cmd_status & cpu_to_le32(DescOwn))
			अवरोध;
		अगर (netअगर_msg_tx_करोne(np))
			prपूर्णांकk(KERN_DEBUG
				"%s: tx frame #%d finished, status %#08x.\n",
					dev->name, np->dirty_tx,
					le32_to_cpu(np->tx_ring[entry].cmd_status));
		अगर (np->tx_ring[entry].cmd_status & cpu_to_le32(DescPktOK)) अणु
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += np->tx_skbuff[entry]->len;
		पूर्ण अन्यथा अणु /* Various Tx errors */
			पूर्णांक tx_status =
				le32_to_cpu(np->tx_ring[entry].cmd_status);
			अगर (tx_status & (DescTxAbort|DescTxExcColl))
				dev->stats.tx_पातed_errors++;
			अगर (tx_status & DescTxFIFO)
				dev->stats.tx_fअगरo_errors++;
			अगर (tx_status & DescTxCarrier)
				dev->stats.tx_carrier_errors++;
			अगर (tx_status & DescTxOOWCol)
				dev->stats.tx_winकरोw_errors++;
			dev->stats.tx_errors++;
		पूर्ण
		dma_unmap_single(&np->pci_dev->dev, np->tx_dma[entry],
				 np->tx_skbuff[entry]->len, DMA_TO_DEVICE);
		/* Free the original skb. */
		dev_consume_skb_irq(np->tx_skbuff[entry]);
		np->tx_skbuff[entry] = शून्य;
	पूर्ण
	अगर (netअगर_queue_stopped(dev) &&
	    np->cur_tx - np->dirty_tx < TX_QUEUE_LEN - 4) अणु
		/* The ring is no दीर्घer full, wake queue. */
		netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

/* The पूर्णांकerrupt handler करोesn't actually handle पूर्णांकerrupts itself, it
 * schedules a NAPI poll अगर there is anything to करो. */
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);

	/* Reading IntrStatus स्वतःmatically acknowledges so करोn't करो
	 * that जबतक पूर्णांकerrupts are disabled, (क्रम example, जबतक a
	 * poll is scheduled).  */
	अगर (np->hands_off || !पढ़ोl(ioaddr + IntrEnable))
		वापस IRQ_NONE;

	np->पूर्णांकr_status = पढ़ोl(ioaddr + IntrStatus);

	अगर (!np->पूर्णांकr_status)
		वापस IRQ_NONE;

	अगर (netअगर_msg_पूर्णांकr(np))
		prपूर्णांकk(KERN_DEBUG
		       "%s: Interrupt, status %#08x, mask %#08x.\n",
		       dev->name, np->पूर्णांकr_status,
		       पढ़ोl(ioaddr + IntrMask));

	prefetch(&np->rx_skbuff[np->cur_rx % RX_RING_SIZE]);

	अगर (napi_schedule_prep(&np->napi)) अणु
		/* Disable पूर्णांकerrupts and रेजिस्टर क्रम poll */
		natsemi_irq_disable(dev);
		__napi_schedule(&np->napi);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_WARNING
	       	       "%s: Ignoring interrupt, status %#08x, mask %#08x.\n",
		       dev->name, np->पूर्णांकr_status,
		       पढ़ोl(ioaddr + IntrMask));

	वापस IRQ_HANDLED;
पूर्ण

/* This is the NAPI poll routine.  As well as the standard RX handling
 * it also handles all other पूर्णांकerrupts that the chip might उठाओ.
 */
अटल पूर्णांक natsemi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा netdev_निजी *np = container_of(napi, काष्ठा netdev_निजी, napi);
	काष्ठा net_device *dev = np->dev;
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	पूर्णांक work_करोne = 0;

	करो अणु
		अगर (netअगर_msg_पूर्णांकr(np))
			prपूर्णांकk(KERN_DEBUG
			       "%s: Poll, status %#08x, mask %#08x.\n",
			       dev->name, np->पूर्णांकr_status,
			       पढ़ोl(ioaddr + IntrMask));

		/* netdev_rx() may पढ़ो IntrStatus again अगर the RX state
		 * machine falls over so करो it first. */
		अगर (np->पूर्णांकr_status &
		    (IntrRxDone | IntrRxIntr | RxStatusFIFOOver |
		     IntrRxErr | IntrRxOverrun)) अणु
			netdev_rx(dev, &work_करोne, budget);
		पूर्ण

		अगर (np->पूर्णांकr_status &
		    (IntrTxDone | IntrTxIntr | IntrTxIdle | IntrTxErr)) अणु
			spin_lock(&np->lock);
			netdev_tx_करोne(dev);
			spin_unlock(&np->lock);
		पूर्ण

		/* Abnormal error summary/uncommon events handlers. */
		अगर (np->पूर्णांकr_status & IntrAbnormalSummary)
			netdev_error(dev, np->पूर्णांकr_status);

		अगर (work_करोne >= budget)
			वापस work_करोne;

		np->पूर्णांकr_status = पढ़ोl(ioaddr + IntrStatus);
	पूर्ण जबतक (np->पूर्णांकr_status);

	napi_complete_करोne(napi, work_करोne);

	/* Reenable पूर्णांकerrupts providing nothing is trying to shut
	 * the chip करोwn. */
	spin_lock(&np->lock);
	अगर (!np->hands_off)
		natsemi_irq_enable(dev);
	spin_unlock(&np->lock);

	वापस work_करोne;
पूर्ण

/* This routine is logically part of the पूर्णांकerrupt handler, but separated
   क्रम clarity and better रेजिस्टर allocation. */
अटल व्योम netdev_rx(काष्ठा net_device *dev, पूर्णांक *work_करोne, पूर्णांक work_to_करो)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक entry = np->cur_rx % RX_RING_SIZE;
	पूर्णांक boguscnt = np->dirty_rx + RX_RING_SIZE - np->cur_rx;
	s32 desc_status = le32_to_cpu(np->rx_head_desc->cmd_status);
	अचिन्हित पूर्णांक buflen = np->rx_buf_sz;
	व्योम __iomem * ioaddr = ns_ioaddr(dev);

	/* If the driver owns the next entry it's a new packet. Send it up. */
	जबतक (desc_status < 0) अणु /* e.g. & DescOwn */
		पूर्णांक pkt_len;
		अगर (netअगर_msg_rx_status(np))
			prपूर्णांकk(KERN_DEBUG
				"  netdev_rx() entry %d status was %#08x.\n",
				entry, desc_status);
		अगर (--boguscnt < 0)
			अवरोध;

		अगर (*work_करोne >= work_to_करो)
			अवरोध;

		(*work_करोne)++;

		pkt_len = (desc_status & DescSizeMask) - 4;
		अगर ((desc_status&(DescMore|DescPktOK|DescRxLong)) != DescPktOK)अणु
			अगर (desc_status & DescMore) अणु
				अचिन्हित दीर्घ flags;

				अगर (netअगर_msg_rx_err(np))
					prपूर्णांकk(KERN_WARNING
						"%s: Oversized(?) Ethernet "
						"frame spanned multiple "
						"buffers, entry %#08x "
						"status %#08x.\n", dev->name,
						np->cur_rx, desc_status);
				dev->stats.rx_length_errors++;

				/* The RX state machine has probably
				 * locked up beneath us.  Follow the
				 * reset procedure करोcumented in
				 * AN-1287. */

				spin_lock_irqsave(&np->lock, flags);
				reset_rx(dev);
				reinit_rx(dev);
				ग_लिखोl(np->ring_dma, ioaddr + RxRingPtr);
				check_link(dev);
				spin_unlock_irqrestore(&np->lock, flags);

				/* We'll enable RX on निकास from this
				 * function. */
				अवरोध;

			पूर्ण अन्यथा अणु
				/* There was an error. */
				dev->stats.rx_errors++;
				अगर (desc_status & (DescRxAbort|DescRxOver))
					dev->stats.rx_over_errors++;
				अगर (desc_status & (DescRxLong|DescRxRunt))
					dev->stats.rx_length_errors++;
				अगर (desc_status & (DescRxInvalid|DescRxAlign))
					dev->stats.rx_frame_errors++;
				अगर (desc_status & DescRxCRC)
					dev->stats.rx_crc_errors++;
			पूर्ण
		पूर्ण अन्यथा अगर (pkt_len > np->rx_buf_sz) अणु
			/* अगर this is the tail of a द्विगुन buffer
			 * packet, we've alपढ़ोy counted the error
			 * on the first part.  Ignore the second half.
			 */
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb;
			/* Omit CRC size. */
			/* Check अगर the packet is दीर्घ enough to accept
			 * without copying to a minimally-sized skbuff. */
			अगर (pkt_len < rx_copyअवरोध &&
			    (skb = netdev_alloc_skb(dev, pkt_len + RX_OFFSET)) != शून्य) अणु
				/* 16 byte align the IP header */
				skb_reserve(skb, RX_OFFSET);
				dma_sync_single_क्रम_cpu(&np->pci_dev->dev,
							np->rx_dma[entry],
							buflen,
							DMA_FROM_DEVICE);
				skb_copy_to_linear_data(skb,
					np->rx_skbuff[entry]->data, pkt_len);
				skb_put(skb, pkt_len);
				dma_sync_single_क्रम_device(&np->pci_dev->dev,
							   np->rx_dma[entry],
							   buflen,
							   DMA_FROM_DEVICE);
			पूर्ण अन्यथा अणु
				dma_unmap_single(&np->pci_dev->dev,
						 np->rx_dma[entry],
						 buflen + NATSEMI_PADDING,
						 DMA_FROM_DEVICE);
				skb_put(skb = np->rx_skbuff[entry], pkt_len);
				np->rx_skbuff[entry] = शून्य;
			पूर्ण
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_receive_skb(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		पूर्ण
		entry = (++np->cur_rx) % RX_RING_SIZE;
		np->rx_head_desc = &np->rx_ring[entry];
		desc_status = le32_to_cpu(np->rx_head_desc->cmd_status);
	पूर्ण
	refill_rx(dev);

	/* Restart Rx engine अगर stopped. */
	अगर (np->oom)
		mod_समयr(&np->समयr, jअगरfies + 1);
	अन्यथा
		ग_लिखोl(RxOn, ioaddr + ChipCmd);
पूर्ण

अटल व्योम netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);

	spin_lock(&np->lock);
	अगर (पूर्णांकr_status & LinkChange) अणु
		u16 lpa = mdio_पढ़ो(dev, MII_LPA);
		अगर (mdio_पढ़ो(dev, MII_BMCR) & BMCR_ANENABLE &&
		    netअगर_msg_link(np)) अणु
			prपूर्णांकk(KERN_INFO
				"%s: Autonegotiation advertising"
				" %#04x  partner %#04x.\n", dev->name,
				np->advertising, lpa);
		पूर्ण

		/* पढ़ो MII पूर्णांक status to clear the flag */
		पढ़ोw(ioaddr + MIntrStatus);
		check_link(dev);
	पूर्ण
	अगर (पूर्णांकr_status & StatsMax) अणु
		__get_stats(dev);
	पूर्ण
	अगर (पूर्णांकr_status & IntrTxUnderrun) अणु
		अगर ((np->tx_config & TxDrthMask) < TX_DRTH_VAL_LIMIT) अणु
			np->tx_config += TX_DRTH_VAL_INC;
			अगर (netअगर_msg_tx_err(np))
				prपूर्णांकk(KERN_NOTICE
					"%s: increased tx threshold, txcfg %#08x.\n",
					dev->name, np->tx_config);
		पूर्ण अन्यथा अणु
			अगर (netअगर_msg_tx_err(np))
				prपूर्णांकk(KERN_NOTICE
					"%s: tx underrun with maximum tx threshold, txcfg %#08x.\n",
					dev->name, np->tx_config);
		पूर्ण
		ग_लिखोl(np->tx_config, ioaddr + TxConfig);
	पूर्ण
	अगर (पूर्णांकr_status & WOLPkt && netअगर_msg_wol(np)) अणु
		पूर्णांक wol_status = पढ़ोl(ioaddr + WOLCmd);
		prपूर्णांकk(KERN_NOTICE "%s: Link wake-up event %#08x\n",
			dev->name, wol_status);
	पूर्ण
	अगर (पूर्णांकr_status & RxStatusFIFOOver) अणु
		अगर (netअगर_msg_rx_err(np) && netअगर_msg_पूर्णांकr(np)) अणु
			prपूर्णांकk(KERN_NOTICE "%s: Rx status FIFO overrun\n",
				dev->name);
		पूर्ण
		dev->stats.rx_fअगरo_errors++;
		dev->stats.rx_errors++;
	पूर्ण
	/* Hmmmmm, it's not clear how to recover from PCI faults. */
	अगर (पूर्णांकr_status & IntrPCIErr) अणु
		prपूर्णांकk(KERN_NOTICE "%s: PCI error %#08x\n", dev->name,
			पूर्णांकr_status & IntrPCIErr);
		dev->stats.tx_fअगरo_errors++;
		dev->stats.tx_errors++;
		dev->stats.rx_fअगरo_errors++;
		dev->stats.rx_errors++;
	पूर्ण
	spin_unlock(&np->lock);
पूर्ण

अटल व्योम __get_stats(काष्ठा net_device *dev)
अणु
	व्योम __iomem * ioaddr = ns_ioaddr(dev);

	/* The chip only need report frame silently dropped. */
	dev->stats.rx_crc_errors += पढ़ोl(ioaddr + RxCRCErrs);
	dev->stats.rx_missed_errors += पढ़ोl(ioaddr + RxMissed);
पूर्ण

अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	/* The chip only need report frame silently dropped. */
	spin_lock_irq(&np->lock);
	अगर (netअगर_running(dev) && !np->hands_off)
		__get_stats(dev);
	spin_unlock_irq(&np->lock);

	वापस &dev->stats;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम natsemi_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	स्थिर पूर्णांक irq = np->pci_dev->irq;

	disable_irq(irq);
	पूर्णांकr_handler(irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

#घोषणा HASH_TABLE	0x200
अटल व्योम __set_rx_mode(काष्ठा net_device *dev)
अणु
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u8 mc_filter[64]; /* Multicast hash filter */
	u32 rx_mode;

	अगर (dev->flags & IFF_PROMISC) अणु /* Set promiscuous. */
		rx_mode = RxFilterEnable | AcceptBroadcast
			| AcceptAllMulticast | AcceptAllPhys | AcceptMyPhys;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		rx_mode = RxFilterEnable | AcceptBroadcast
			| AcceptAllMulticast | AcceptMyPhys;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक i;

		स_रखो(mc_filter, 0, माप(mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			पूर्णांक b = (ether_crc(ETH_ALEN, ha->addr) >> 23) & 0x1ff;
			mc_filter[b/8] |= (1 << (b & 0x07));
		पूर्ण
		rx_mode = RxFilterEnable | AcceptBroadcast
			| AcceptMulticast | AcceptMyPhys;
		क्रम (i = 0; i < 64; i += 2) अणु
			ग_लिखोl(HASH_TABLE + i, ioaddr + RxFilterAddr);
			ग_लिखोl((mc_filter[i + 1] << 8) + mc_filter[i],
			       ioaddr + RxFilterData);
		पूर्ण
	पूर्ण
	ग_लिखोl(rx_mode, ioaddr + RxFilterAddr);
	np->cur_rx_mode = rx_mode;
पूर्ण

अटल पूर्णांक natsemi_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	dev->mtu = new_mtu;

	/* synchronized against खोलो : rtnl_lock() held by caller */
	अगर (netअगर_running(dev)) अणु
		काष्ठा netdev_निजी *np = netdev_priv(dev);
		व्योम __iomem * ioaddr = ns_ioaddr(dev);
		स्थिर पूर्णांक irq = np->pci_dev->irq;

		disable_irq(irq);
		spin_lock(&np->lock);
		/* stop engines */
		natsemi_stop_rxtx(dev);
		/* drain rx queue */
		drain_rx(dev);
		/* change buffers */
		set_bufsize(dev);
		reinit_rx(dev);
		ग_लिखोl(np->ring_dma, ioaddr + RxRingPtr);
		/* restart engines */
		ग_लिखोl(RxOn | TxOn, ioaddr + ChipCmd);
		spin_unlock(&np->lock);
		enable_irq(irq);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	spin_lock_irq(&np->lock);
	अगर (!np->hands_off)
		__set_rx_mode(dev);
	spin_unlock_irq(&np->lock);
पूर्ण

अटल व्योम get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(np->pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक get_regs_len(काष्ठा net_device *dev)
अणु
	वापस NATSEMI_REGS_SIZE;
पूर्ण

अटल पूर्णांक get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस np->eeprom_size;
पूर्ण

अटल पूर्णांक get_link_ksettings(काष्ठा net_device *dev,
			      काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	spin_lock_irq(&np->lock);
	netdev_get_ecmd(dev, ecmd);
	spin_unlock_irq(&np->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक set_link_ksettings(काष्ठा net_device *dev,
			      स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक res;
	spin_lock_irq(&np->lock);
	res = netdev_set_ecmd(dev, ecmd);
	spin_unlock_irq(&np->lock);
	वापस res;
पूर्ण

अटल व्योम get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	spin_lock_irq(&np->lock);
	netdev_get_wol(dev, &wol->supported, &wol->wolopts);
	netdev_get_sopass(dev, wol->sopass);
	spin_unlock_irq(&np->lock);
पूर्ण

अटल पूर्णांक set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक res;
	spin_lock_irq(&np->lock);
	netdev_set_wol(dev, wol->wolopts);
	res = netdev_set_sopass(dev, wol->sopass);
	spin_unlock_irq(&np->lock);
	वापस res;
पूर्ण

अटल व्योम get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *buf)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	regs->version = NATSEMI_REGS_VER;
	spin_lock_irq(&np->lock);
	netdev_get_regs(dev, buf);
	spin_unlock_irq(&np->lock);
पूर्ण

अटल u32 get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस np->msg_enable;
पूर्ण

अटल व्योम set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	np->msg_enable = val;
पूर्ण

अटल पूर्णांक nway_reset(काष्ठा net_device *dev)
अणु
	पूर्णांक पंचांगp;
	पूर्णांक r = -EINVAL;
	/* अगर स्वतःneg is off, it's an error */
	पंचांगp = mdio_पढ़ो(dev, MII_BMCR);
	अगर (पंचांगp & BMCR_ANENABLE) अणु
		पंचांगp |= (BMCR_ANRESTART);
		mdio_ग_लिखो(dev, MII_BMCR, पंचांगp);
		r = 0;
	पूर्ण
	वापस r;
पूर्ण

अटल u32 get_link(काष्ठा net_device *dev)
अणु
	/* LSTATUS is latched low until a पढ़ो - so पढ़ो twice */
	mdio_पढ़ो(dev, MII_BMSR);
	वापस (mdio_पढ़ो(dev, MII_BMSR)&BMSR_LSTATUS) ? 1:0;
पूर्ण

अटल पूर्णांक get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u8 *eebuf;
	पूर्णांक res;

	eebuf = kदो_स्मृति(np->eeprom_size, GFP_KERNEL);
	अगर (!eebuf)
		वापस -ENOMEM;

	eeprom->magic = PCI_VENDOR_ID_NS | (PCI_DEVICE_ID_NS_83815<<16);
	spin_lock_irq(&np->lock);
	res = netdev_get_eeprom(dev, eebuf);
	spin_unlock_irq(&np->lock);
	अगर (!res)
		स_नकल(data, eebuf+eeprom->offset, eeprom->len);
	kमुक्त(eebuf);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.get_drvinfo = get_drvinfo,
	.get_regs_len = get_regs_len,
	.get_eeprom_len = get_eeprom_len,
	.get_wol = get_wol,
	.set_wol = set_wol,
	.get_regs = get_regs,
	.get_msglevel = get_msglevel,
	.set_msglevel = set_msglevel,
	.nway_reset = nway_reset,
	.get_link = get_link,
	.get_eeprom = get_eeprom,
	.get_link_ksettings = get_link_ksettings,
	.set_link_ksettings = set_link_ksettings,
पूर्ण;

अटल पूर्णांक netdev_set_wol(काष्ठा net_device *dev, u32 newval)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	u32 data = पढ़ोl(ioaddr + WOLCmd) & ~WakeOptsSummary;

	/* translate to biपंचांगasks this chip understands */
	अगर (newval & WAKE_PHY)
		data |= WakePhy;
	अगर (newval & WAKE_UCAST)
		data |= WakeUnicast;
	अगर (newval & WAKE_MCAST)
		data |= WakeMulticast;
	अगर (newval & WAKE_BCAST)
		data |= WakeBroadcast;
	अगर (newval & WAKE_ARP)
		data |= WakeArp;
	अगर (newval & WAKE_MAGIC)
		data |= WakeMagic;
	अगर (np->srr >= SRR_DP83815_D) अणु
		अगर (newval & WAKE_MAGICSECURE) अणु
			data |= WakeMagicSecure;
		पूर्ण
	पूर्ण

	ग_लिखोl(data, ioaddr + WOLCmd);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_get_wol(काष्ठा net_device *dev, u32 *supported, u32 *cur)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	u32 regval = पढ़ोl(ioaddr + WOLCmd);

	*supported = (WAKE_PHY | WAKE_UCAST | WAKE_MCAST | WAKE_BCAST
			| WAKE_ARP | WAKE_MAGIC);

	अगर (np->srr >= SRR_DP83815_D) अणु
		/* SOPASS works on revD and higher */
		*supported |= WAKE_MAGICSECURE;
	पूर्ण
	*cur = 0;

	/* translate from chip biपंचांगasks */
	अगर (regval & WakePhy)
		*cur |= WAKE_PHY;
	अगर (regval & WakeUnicast)
		*cur |= WAKE_UCAST;
	अगर (regval & WakeMulticast)
		*cur |= WAKE_MCAST;
	अगर (regval & WakeBroadcast)
		*cur |= WAKE_BCAST;
	अगर (regval & WakeArp)
		*cur |= WAKE_ARP;
	अगर (regval & WakeMagic)
		*cur |= WAKE_MAGIC;
	अगर (regval & WakeMagicSecure) अणु
		/* this can be on in revC, but it's broken */
		*cur |= WAKE_MAGICSECURE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_set_sopass(काष्ठा net_device *dev, u8 *newval)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	u16 *sval = (u16 *)newval;
	u32 addr;

	अगर (np->srr < SRR_DP83815_D) अणु
		वापस 0;
	पूर्ण

	/* enable writing to these रेजिस्टरs by disabling the RX filter */
	addr = पढ़ोl(ioaddr + RxFilterAddr) & ~RFCRAddressMask;
	addr &= ~RxFilterEnable;
	ग_लिखोl(addr, ioaddr + RxFilterAddr);

	/* ग_लिखो the three words to (unकरोcumented) RFCR vals 0xa, 0xc, 0xe */
	ग_लिखोl(addr | 0xa, ioaddr + RxFilterAddr);
	ग_लिखोw(sval[0], ioaddr + RxFilterData);

	ग_लिखोl(addr | 0xc, ioaddr + RxFilterAddr);
	ग_लिखोw(sval[1], ioaddr + RxFilterData);

	ग_लिखोl(addr | 0xe, ioaddr + RxFilterAddr);
	ग_लिखोw(sval[2], ioaddr + RxFilterData);

	/* re-enable the RX filter */
	ग_लिखोl(addr | RxFilterEnable, ioaddr + RxFilterAddr);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_get_sopass(काष्ठा net_device *dev, u8 *data)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	u16 *sval = (u16 *)data;
	u32 addr;

	अगर (np->srr < SRR_DP83815_D) अणु
		sval[0] = sval[1] = sval[2] = 0;
		वापस 0;
	पूर्ण

	/* पढ़ो the three words from (unकरोcumented) RFCR vals 0xa, 0xc, 0xe */
	addr = पढ़ोl(ioaddr + RxFilterAddr) & ~RFCRAddressMask;

	ग_लिखोl(addr | 0xa, ioaddr + RxFilterAddr);
	sval[0] = पढ़ोw(ioaddr + RxFilterData);

	ग_लिखोl(addr | 0xc, ioaddr + RxFilterAddr);
	sval[1] = पढ़ोw(ioaddr + RxFilterData);

	ग_लिखोl(addr | 0xe, ioaddr + RxFilterAddr);
	sval[2] = पढ़ोw(ioaddr + RxFilterData);

	ग_लिखोl(addr, ioaddr + RxFilterAddr);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_get_ecmd(काष्ठा net_device *dev,
			   काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u32 supported, advertising;
	u32 पंचांगp;

	ecmd->base.port   = dev->अगर_port;
	ecmd->base.speed  = np->speed;
	ecmd->base.duplex = np->duplex;
	ecmd->base.स्वतःneg = np->स्वतःneg;
	advertising = 0;

	अगर (np->advertising & ADVERTISE_10HALF)
		advertising |= ADVERTISED_10baseT_Half;
	अगर (np->advertising & ADVERTISE_10FULL)
		advertising |= ADVERTISED_10baseT_Full;
	अगर (np->advertising & ADVERTISE_100HALF)
		advertising |= ADVERTISED_100baseT_Half;
	अगर (np->advertising & ADVERTISE_100FULL)
		advertising |= ADVERTISED_100baseT_Full;
	supported   = (SUPPORTED_Autoneg |
		SUPPORTED_10baseT_Half  | SUPPORTED_10baseT_Full  |
		SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
		SUPPORTED_TP | SUPPORTED_MII | SUPPORTED_FIBRE);
	ecmd->base.phy_address = np->phy_addr_बाह्यal;
	/*
	 * We पूर्णांकentionally report the phy address of the बाह्यal
	 * phy, even अगर the पूर्णांकernal phy is used. This is necessary
	 * to work around a deficiency of the ethtool पूर्णांकerface:
	 * It's only possible to query the settings of the active
	 * port. Thereक्रमe
	 * # ethtool -s ethX port mii
	 * actually sends an ioctl to चयन to port mii with the
	 * settings that are used क्रम the current active port.
	 * If we would report a dअगरferent phy address in this
	 * command, then
	 * # ethtool -s ethX port tp;ethtool -s ethX port mii
	 * would unपूर्णांकentionally change the phy address.
	 *
	 * Fortunately the phy address करोesn't matter with the
	 * पूर्णांकernal phy...
	 */

	/* set inक्रमmation based on active port type */
	चयन (ecmd->base.port) अणु
	शेष:
	हाल PORT_TP:
		advertising |= ADVERTISED_TP;
		अवरोध;
	हाल PORT_MII:
		advertising |= ADVERTISED_MII;
		अवरोध;
	हाल PORT_FIBRE:
		advertising |= ADVERTISED_FIBRE;
		अवरोध;
	पूर्ण

	/* अगर स्वतःnegotiation is on, try to वापस the active speed/duplex */
	अगर (ecmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		advertising |= ADVERTISED_Autoneg;
		पंचांगp = mii_nway_result(
			np->advertising & mdio_पढ़ो(dev, MII_LPA));
		अगर (पंचांगp == LPA_100FULL || पंचांगp == LPA_100HALF)
			ecmd->base.speed = SPEED_100;
		अन्यथा
			ecmd->base.speed = SPEED_10;
		अगर (पंचांगp == LPA_100FULL || पंचांगp == LPA_10FULL)
			ecmd->base.duplex = DUPLEX_FULL;
		अन्यथा
			ecmd->base.duplex = DUPLEX_HALF;
	पूर्ण

	/* ignore maxtxpkt, maxrxpkt क्रम now */

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_set_ecmd(काष्ठा net_device *dev,
			   स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						ecmd->link_modes.advertising);

	अगर (ecmd->base.port != PORT_TP &&
	    ecmd->base.port != PORT_MII &&
	    ecmd->base.port != PORT_FIBRE)
		वापस -EINVAL;
	अगर (ecmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		अगर ((advertising & (ADVERTISED_10baseT_Half |
					  ADVERTISED_10baseT_Full |
					  ADVERTISED_100baseT_Half |
					  ADVERTISED_100baseT_Full)) == 0) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (ecmd->base.स्वतःneg == AUTONEG_DISABLE) अणु
		u32 speed = ecmd->base.speed;
		अगर (speed != SPEED_10 && speed != SPEED_100)
			वापस -EINVAL;
		अगर (ecmd->base.duplex != DUPLEX_HALF &&
		    ecmd->base.duplex != DUPLEX_FULL)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/*
	 * If we're ignoring the PHY then स्वतःneg and the पूर्णांकernal
	 * transceiver are really not going to work so करोn't let the
	 * user select them.
	 */
	अगर (np->ignore_phy && (ecmd->base.स्वतःneg == AUTONEG_ENABLE ||
			       ecmd->base.port == PORT_TP))
		वापस -EINVAL;

	/*
	 * maxtxpkt, maxrxpkt: ignored क्रम now.
	 *
	 * transceiver:
	 * PORT_TP is always XCVR_INTERNAL, PORT_MII and PORT_FIBRE are always
	 * XCVR_EXTERNAL. The implementation thus ignores ecmd->transceiver and
	 * selects based on ecmd->port.
	 *
	 * Actually PORT_FIBRE is nearly identical to PORT_MII: it's क्रम fibre
	 * phys that are connected to the mii bus. It's used to apply fibre
	 * specअगरic updates.
	 */

	/* WHEW! now lets bang some bits */

	/* save the parms */
	dev->अगर_port          = ecmd->base.port;
	np->स्वतःneg           = ecmd->base.स्वतःneg;
	np->phy_addr_बाह्यal = ecmd->base.phy_address & PhyAddrMask;
	अगर (np->स्वतःneg == AUTONEG_ENABLE) अणु
		/* advertise only what has been requested */
		np->advertising &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
		अगर (advertising & ADVERTISED_10baseT_Half)
			np->advertising |= ADVERTISE_10HALF;
		अगर (advertising & ADVERTISED_10baseT_Full)
			np->advertising |= ADVERTISE_10FULL;
		अगर (advertising & ADVERTISED_100baseT_Half)
			np->advertising |= ADVERTISE_100HALF;
		अगर (advertising & ADVERTISED_100baseT_Full)
			np->advertising |= ADVERTISE_100FULL;
	पूर्ण अन्यथा अणु
		np->speed  = ecmd->base.speed;
		np->duplex = ecmd->base.duplex;
		/* user overriding the initial full duplex parm? */
		अगर (np->duplex == DUPLEX_HALF)
			np->full_duplex = 0;
	पूर्ण

	/* get the right phy enabled */
	अगर (ecmd->base.port == PORT_TP)
		चयन_port_पूर्णांकernal(dev);
	अन्यथा
		चयन_port_बाह्यal(dev);

	/* set parms and see how this affected our link status */
	init_phy_fixup(dev);
	check_link(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक netdev_get_regs(काष्ठा net_device *dev, u8 *buf)
अणु
	पूर्णांक i;
	पूर्णांक j;
	u32 rfcr;
	u32 *rbuf = (u32 *)buf;
	व्योम __iomem * ioaddr = ns_ioaddr(dev);

	/* पढ़ो non-mii page 0 of रेजिस्टरs */
	क्रम (i = 0; i < NATSEMI_PG0_NREGS/2; i++) अणु
		rbuf[i] = पढ़ोl(ioaddr + i*4);
	पूर्ण

	/* पढ़ो current mii रेजिस्टरs */
	क्रम (i = NATSEMI_PG0_NREGS/2; i < NATSEMI_PG0_NREGS; i++)
		rbuf[i] = mdio_पढ़ो(dev, i & 0x1f);

	/* पढ़ो only the 'magic' रेजिस्टरs from page 1 */
	ग_लिखोw(1, ioaddr + PGSEL);
	rbuf[i++] = पढ़ोw(ioaddr + PMDCSR);
	rbuf[i++] = पढ़ोw(ioaddr + TSTDAT);
	rbuf[i++] = पढ़ोw(ioaddr + DSPCFG);
	rbuf[i++] = पढ़ोw(ioaddr + SDCFG);
	ग_लिखोw(0, ioaddr + PGSEL);

	/* पढ़ो RFCR indexed रेजिस्टरs */
	rfcr = पढ़ोl(ioaddr + RxFilterAddr);
	क्रम (j = 0; j < NATSEMI_RFDR_NREGS; j++) अणु
		ग_लिखोl(j*2, ioaddr + RxFilterAddr);
		rbuf[i++] = पढ़ोw(ioaddr + RxFilterData);
	पूर्ण
	ग_लिखोl(rfcr, ioaddr + RxFilterAddr);

	/* the पूर्णांकerrupt status is clear-on-पढ़ो - see अगर we missed any */
	अगर (rbuf[4] & rbuf[5]) अणु
		prपूर्णांकk(KERN_WARNING
			"%s: shoot, we dropped an interrupt (%#08x)\n",
			dev->name, rbuf[4] & rbuf[5]);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा SWAP_BITS(x)	( (((x) & 0x0001) << 15) | (((x) & 0x0002) << 13) \
			| (((x) & 0x0004) << 11) | (((x) & 0x0008) << 9)  \
			| (((x) & 0x0010) << 7)  | (((x) & 0x0020) << 5)  \
			| (((x) & 0x0040) << 3)  | (((x) & 0x0080) << 1)  \
			| (((x) & 0x0100) >> 1)  | (((x) & 0x0200) >> 3)  \
			| (((x) & 0x0400) >> 5)  | (((x) & 0x0800) >> 7)  \
			| (((x) & 0x1000) >> 9)  | (((x) & 0x2000) >> 11) \
			| (((x) & 0x4000) >> 13) | (((x) & 0x8000) >> 15) )

अटल पूर्णांक netdev_get_eeprom(काष्ठा net_device *dev, u8 *buf)
अणु
	पूर्णांक i;
	u16 *ebuf = (u16 *)buf;
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	/* eeprom_पढ़ो पढ़ोs 16 bits, and indexes by 16 bits */
	क्रम (i = 0; i < np->eeprom_size/2; i++) अणु
		ebuf[i] = eeprom_पढ़ो(ioaddr, i);
		/* The EEPROM itself stores data bit-swapped, but eeprom_पढ़ो
		 * पढ़ोs it back "sanely". So we swap it back here in order to
		 * present it to userland as it is stored. */
		ebuf[i] = SWAP_BITS(ebuf[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	चयन(cmd) अणु
	हाल SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = np->phy_addr_बाह्यal;
		fallthrough;

	हाल SIOCGMIIREG:		/* Read MII PHY रेजिस्टर. */
		/* The phy_id is not enough to uniquely identअगरy
		 * the पूर्णांकended target. Thereक्रमe the command is sent to
		 * the given mii on the current port.
		 */
		अगर (dev->अगर_port == PORT_TP) अणु
			अगर ((data->phy_id & 0x1f) == np->phy_addr_बाह्यal)
				data->val_out = mdio_पढ़ो(dev,
							data->reg_num & 0x1f);
			अन्यथा
				data->val_out = 0;
		पूर्ण अन्यथा अणु
			move_पूर्णांक_phy(dev, data->phy_id & 0x1f);
			data->val_out = miiport_पढ़ो(dev, data->phy_id & 0x1f,
							data->reg_num & 0x1f);
		पूर्ण
		वापस 0;

	हाल SIOCSMIIREG:		/* Write MII PHY रेजिस्टर. */
		अगर (dev->अगर_port == PORT_TP) अणु
			अगर ((data->phy_id & 0x1f) == np->phy_addr_बाह्यal) अणु
 				अगर ((data->reg_num & 0x1f) == MII_ADVERTISE)
					np->advertising = data->val_in;
				mdio_ग_लिखो(dev, data->reg_num & 0x1f,
							data->val_in);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((data->phy_id & 0x1f) == np->phy_addr_बाह्यal) अणु
 				अगर ((data->reg_num & 0x1f) == MII_ADVERTISE)
					np->advertising = data->val_in;
			पूर्ण
			move_पूर्णांक_phy(dev, data->phy_id & 0x1f);
			miiport_ग_लिखो(dev, data->phy_id & 0x1f,
						data->reg_num & 0x1f,
						data->val_in);
		पूर्ण
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम enable_wol_mode(काष्ठा net_device *dev, पूर्णांक enable_पूर्णांकr)
अणु
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	अगर (netअगर_msg_wol(np))
		prपूर्णांकk(KERN_INFO "%s: remaining active for wake-on-lan\n",
			dev->name);

	/* For WOL we must restart the rx process in silent mode.
	 * Write शून्य to the RxRingPtr. Only possible अगर
	 * rx process is stopped
	 */
	ग_लिखोl(0, ioaddr + RxRingPtr);

	/* पढ़ो WoL status to clear */
	पढ़ोl(ioaddr + WOLCmd);

	/* PME on, clear status */
	ग_लिखोl(np->SavedClkRun | PMEEnable | PMEStatus, ioaddr + ClkRun);

	/* and restart the rx process */
	ग_लिखोl(RxOn, ioaddr + ChipCmd);

	अगर (enable_पूर्णांकr) अणु
		/* enable the WOL पूर्णांकerrupt.
		 * Could be used to send a netlink message.
		 */
		ग_लिखोl(WOLPkt | LinkChange, ioaddr + IntrMask);
		natsemi_irq_enable(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक netdev_बंद(काष्ठा net_device *dev)
अणु
	व्योम __iomem * ioaddr = ns_ioaddr(dev);
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	स्थिर पूर्णांक irq = np->pci_dev->irq;

	अगर (netअगर_msg_अगरकरोwn(np))
		prपूर्णांकk(KERN_DEBUG
			"%s: Shutting down ethercard, status was %#04x.\n",
			dev->name, (पूर्णांक)पढ़ोl(ioaddr + ChipCmd));
	अगर (netअगर_msg_pktdata(np))
		prपूर्णांकk(KERN_DEBUG
			"%s: Queue pointers were Tx %d / %d,  Rx %d / %d.\n",
			dev->name, np->cur_tx, np->dirty_tx,
			np->cur_rx, np->dirty_rx);

	napi_disable(&np->napi);

	/*
	 * FIXME: what अगर someone tries to बंद a device
	 * that is suspended?
	 * Should we reenable the nic to चयन to
	 * the final WOL settings?
	 */

	del_समयr_sync(&np->समयr);
	disable_irq(irq);
	spin_lock_irq(&np->lock);
	natsemi_irq_disable(dev);
	np->hands_off = 1;
	spin_unlock_irq(&np->lock);
	enable_irq(irq);

	मुक्त_irq(irq, dev);

	/* Interrupt disabled, पूर्णांकerrupt handler released,
	 * queue stopped, समयr deleted, rtnl_lock held
	 * All async codepaths that access the driver are disabled.
	 */
	spin_lock_irq(&np->lock);
	np->hands_off = 0;
	पढ़ोl(ioaddr + IntrMask);
	पढ़ोw(ioaddr + MIntrStatus);

	/* Freeze Stats */
	ग_लिखोl(StatsFreeze, ioaddr + StatsCtrl);

	/* Stop the chip's Tx and Rx processes. */
	natsemi_stop_rxtx(dev);

	__get_stats(dev);
	spin_unlock_irq(&np->lock);

	/* clear the carrier last - an पूर्णांकerrupt could reenable it otherwise */
	netअगर_carrier_off(dev);
	netअगर_stop_queue(dev);

	dump_ring(dev);
	drain_ring(dev);
	मुक्त_ring(dev);

	अणु
		u32 wol = पढ़ोl(ioaddr + WOLCmd) & WakeOptsSummary;
		अगर (wol) अणु
			/* restart the NIC in WOL mode.
			 * The nic must be stopped क्रम this.
			 */
			enable_wol_mode(dev, 0);
		पूर्ण अन्यथा अणु
			/* Restore PME enable bit unmolested */
			ग_लिखोl(np->SavedClkRun, ioaddr + ClkRun);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम natsemi_हटाओ1(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);

	NATSEMI_REMOVE_खाता(pdev, dspcfg_workaround);
	unरेजिस्टर_netdev (dev);
	pci_release_regions (pdev);
	iounmap(ioaddr);
	मुक्त_netdev (dev);
पूर्ण

/*
 * The ns83815 chip करोesn't have explicit RxStop bits.
 * Kicking the Rx or Tx process क्रम a new packet reenables the Rx process
 * of the nic, thus this function must be very careful:
 *
 * suspend/resume synchronization:
 * entry poपूर्णांकs:
 *   netdev_खोलो, netdev_बंद, netdev_ioctl, set_rx_mode, पूर्णांकr_handler,
 *   start_tx, ns_tx_समयout
 *
 * No function accesses the hardware without checking np->hands_off.
 *	the check occurs under spin_lock_irq(&np->lock);
 * exceptions:
 *	* netdev_ioctl: noncritical access.
 *	* netdev_खोलो: cannot happen due to the device_detach
 *	* netdev_बंद: करोesn't hurt.
 *	* netdev_समयr: समयr stopped by natsemi_suspend.
 *	* पूर्णांकr_handler: करोesn't acquire the spinlock. suspend calls
 *		disable_irq() to enक्रमce synchronization.
 *      * natsemi_poll: checks beक्रमe reenabling पूर्णांकerrupts.  suspend
 *              sets hands_off, disables पूर्णांकerrupts and then रुकोs with
 *              napi_disable().
 *
 * Interrupts must be disabled, otherwise hands_off can cause irq storms.
 */

अटल पूर्णांक __maybe_unused natsemi_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem * ioaddr = ns_ioaddr(dev);

	rtnl_lock();
	अगर (netअगर_running (dev)) अणु
		स्थिर पूर्णांक irq = np->pci_dev->irq;

		del_समयr_sync(&np->समयr);

		disable_irq(irq);
		spin_lock_irq(&np->lock);

		natsemi_irq_disable(dev);
		np->hands_off = 1;
		natsemi_stop_rxtx(dev);
		netअगर_stop_queue(dev);

		spin_unlock_irq(&np->lock);
		enable_irq(irq);

		napi_disable(&np->napi);

		/* Update the error counts. */
		__get_stats(dev);

		/* pci_घातer_off(pdev, -1); */
		drain_ring(dev);
		अणु
			u32 wol = पढ़ोl(ioaddr + WOLCmd) & WakeOptsSummary;
			/* Restore PME enable bit */
			अगर (wol) अणु
				/* restart the NIC in WOL mode.
				 * The nic must be stopped क्रम this.
				 * FIXME: use the WOL पूर्णांकerrupt
				 */
				enable_wol_mode(dev, 0);
			पूर्ण अन्यथा अणु
				/* Restore PME enable bit unmolested */
				ग_लिखोl(np->SavedClkRun, ioaddr + ClkRun);
			पूर्ण
		पूर्ण
	पूर्ण
	netअगर_device_detach(dev);
	rtnl_unlock();
	वापस 0;
पूर्ण


अटल पूर्णांक __maybe_unused natsemi_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	rtnl_lock();
	अगर (netअगर_device_present(dev))
		जाओ out;
	अगर (netअगर_running(dev)) अणु
		स्थिर पूर्णांक irq = np->pci_dev->irq;

		BUG_ON(!np->hands_off);
	/*	pci_घातer_on(pdev); */

		napi_enable(&np->napi);

		natsemi_reset(dev);
		init_ring(dev);
		disable_irq(irq);
		spin_lock_irq(&np->lock);
		np->hands_off = 0;
		init_रेजिस्टरs(dev);
		netअगर_device_attach(dev);
		spin_unlock_irq(&np->lock);
		enable_irq(irq);

		mod_समयr(&np->समयr, round_jअगरfies(jअगरfies + 1*HZ));
	पूर्ण
	netअगर_device_attach(dev);
out:
	rtnl_unlock();
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(natsemi_pm_ops, natsemi_suspend, natsemi_resume);

अटल काष्ठा pci_driver natsemi_driver = अणु
	.name		= DRV_NAME,
	.id_table	= natsemi_pci_tbl,
	.probe		= natsemi_probe1,
	.हटाओ		= natsemi_हटाओ1,
	.driver.pm	= &natsemi_pm_ops,
पूर्ण;

अटल पूर्णांक __init natsemi_init_mod (व्योम)
अणु
/* when a module, this is prपूर्णांकed whether or not devices are found in probe */
#अगर_घोषित MODULE
	prपूर्णांकk(version);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&natsemi_driver);
पूर्ण

अटल व्योम __निकास natsemi_निकास_mod (व्योम)
अणु
	pci_unरेजिस्टर_driver (&natsemi_driver);
पूर्ण

module_init(natsemi_init_mod);
module_निकास(natsemi_निकास_mod);

