<शैली गुरु>
/* via-rhine.c: A Linux Ethernet device driver क्रम VIA Rhine family chips. */
/*
	Written 1998-2001 by Donald Becker.

	Current Maपूर्णांकainer: Kevin Brace <kevinbrace@bracecomputerlab.com>

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	This driver is deचिन्हित क्रम the VIA VT86C100A Rhine-I.
	It also works with the Rhine-II (6102) and Rhine-III (6105/6105L/6105LOM
	and management NIC 6105M).

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403


	This driver contains some changes from the original Donald Becker
	version. He may or may not be पूर्णांकerested in bug reports on this
	code. You can find his versions at:
	http://www.scyld.com/network/via-rhine.hपंचांगl
	[link no दीर्घer provides useful info -jgarzik]

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"via-rhine"

#समावेश <linux/types.h>

/* A few user-configurable values.
   These may be modअगरied when a driver module is loaded. */
अटल पूर्णांक debug = 0;
#घोषणा RHINE_MSG_DEFAULT \
        (0x0000)

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
   Setting to > 1518 effectively disables this feature. */
#अगर defined(__alpha__) || defined(__arm__) || defined(__hppa__) || \
	defined(CONFIG_SPARC) || defined(__ia64__) ||		   \
	defined(__sh__) || defined(__mips__)
अटल पूर्णांक rx_copyअवरोध = 1518;
#अन्यथा
अटल पूर्णांक rx_copyअवरोध;
#पूर्ण_अगर

/* Work-around क्रम broken BIOSes: they are unable to get the chip back out of
   घातer state D3 so PXE booting fails. bootparam(7): via-rhine.aव्योम_D3=1 */
अटल bool aव्योम_D3;

/*
 * In हाल you are looking क्रम 'options[]' or 'full_duplex[]', they
 * are gone. Use ethtool(8) instead.
 */

/* Maximum number of multicast addresses to filter (vs. rx-all-multicast).
   The Rhine has a 64 element 8390-like hash table. */
अटल स्थिर पूर्णांक multicast_filter_limit = 32;


/* Operational parameters that are set at compile समय. */

/* Keep the ring sizes a घातer of two क्रम compile efficiency.
 * The compiler will convert <अचिन्हित>'%'<2^N> पूर्णांकo a bit mask.
 * Making the Tx ring too large decreases the effectiveness of channel
 * bonding and packet priority.
 * With BQL support, we can increase TX ring safely.
 * There are no ill effects from too-large receive rings.
 */
#घोषणा TX_RING_SIZE	64
#घोषणा TX_QUEUE_LEN	(TX_RING_SIZE - 6)	/* Limit ring entries actually used. */
#घोषणा RX_RING_SIZE	64

/* Operational parameters that usually are not changed. */

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT	(2*HZ)

#घोषणा PKT_BUF_SZ	1536	/* Size of each temporary Rx buffer.*/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/bitops.h>
#समावेश <linux/workqueue.h>
#समावेश <यंत्र/processor.h>	/* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/dmi.h>

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("VIA Rhine PCI Fast Ethernet driver");
MODULE_LICENSE("GPL");

module_param(debug, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param(aव्योम_D3, bool, 0);
MODULE_PARM_DESC(debug, "VIA Rhine debug message flags");
MODULE_PARM_DESC(rx_copyअवरोध, "VIA Rhine copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(aव्योम_D3, "Avoid power state D3 (work-around for broken BIOSes)");

#घोषणा MCAM_SIZE	32
#घोषणा VCAM_SIZE	32

/*
		Theory of Operation

I. Board Compatibility

This driver is deचिन्हित क्रम the VIA 86c100A Rhine-II PCI Fast Ethernet
controller.

II. Board-specअगरic settings

Boards with this chip are functional only in a bus-master PCI slot.

Many operational settings are loaded from the EEPROM to the Config word at
offset 0x78. For most of these settings, this driver assumes that they are
correct.
If this driver is compiled to use PCI memory space operations the EEPROM
must be configured to enable memory ops.

III. Driver operation

IIIa. Ring buffers

This driver uses two अटलally allocated fixed-size descriptor lists
क्रमmed पूर्णांकo rings by a branch from the final descriptor to the beginning of
the list. The ring sizes are set at compile समय by RX/TX_RING_SIZE.

IIIb/c. Transmit/Receive Structure

This driver attempts to use a zero-copy receive and transmit scheme.

Alas, all data buffers are required to start on a 32 bit boundary, so
the driver must often copy transmit packets पूर्णांकo bounce buffers.

The driver allocates full frame size skbuffs क्रम the Rx ring buffers at
खोलो() समय and passes the skb->data field to the chip as receive data
buffers. When an incoming frame is less than RX_COPYBREAK bytes दीर्घ,
a fresh skbuff is allocated and the frame is copied to the new skbuff.
When the incoming frame is larger, the skbuff is passed directly up the
protocol stack. Buffers consumed this way are replaced by newly allocated
skbuffs in the last phase of rhine_rx().

The RX_COPYBREAK value is chosen to trade-off the memory wasted by
using a full-sized skbuff क्रम small frames vs. the copying costs of larger
frames. New boards are typically used in generously configured machines
and the underfilled buffers have negligible impact compared to the benefit of
a single allocation size, so the शेष value of zero results in never
copying packets. When copying is करोne, the cost is usually mitigated by using
a combined copy/checksum routine. Copying also preloads the cache, which is
most useful with small frames.

Since the VIA chips are only able to transfer data to buffers on 32 bit
boundaries, the IP header at offset 14 in an ethernet frame isn't
दीर्घword aligned क्रम further processing. Copying these unaligned buffers
has the beneficial effect of 16-byte aligning the IP header.

IIId. Synchronization

The driver runs as two independent, single-thपढ़ोed flows of control. One
is the send-packet routine, which enक्रमces single-thपढ़ोed use by the
netdev_priv(dev)->lock spinlock. The other thपढ़ो is the पूर्णांकerrupt handler,
which is single thपढ़ोed by the hardware and पूर्णांकerrupt handling software.

The send packet thपढ़ो has partial control over the Tx ring. It locks the
netdev_priv(dev)->lock whenever it's queuing a Tx packet. If the next slot in
the ring is not available it stops the transmit queue by
calling netअगर_stop_queue.

The पूर्णांकerrupt handler has exclusive control over the Rx ring and records stats
from the Tx ring. After reaping the stats, it marks the Tx queue entry as
empty by incrementing the dirty_tx mark. If at least half of the entries in
the Rx ring are available the transmit queue is woken up अगर it was stopped.

IV. Notes

IVb. References

Preliminary VT86C100A manual from http://www.via.com.tw/
http://www.scyld.com/expert/100mbps.hपंचांगl
http://www.scyld.com/expert/NWay.hपंचांगl
ftp://ftp.via.com.tw/खुला/lan/Products/NIC/VT86C100A/Datasheet/VT86C100A03.pdf
ftp://ftp.via.com.tw/खुला/lan/Products/NIC/VT6102/Datasheet/VT6102_021.PDF


IVc. Errata

The VT86C100A manual is not reliable inक्रमmation.
The 3043 chip करोes not handle unaligned transmit or receive buffers, resulting
in signअगरicant perक्रमmance degradation क्रम bounce buffer copies on transmit
and unaligned IP headers on receive.
The chip करोes not pad to minimum transmit length.

*/


/* This table drives the PCI probe routines. It's mostly boilerplate in all
   of the drivers, and will likely be provided by some future kernel.
   Note the matching code -- the first table entry matchs all 56** cards but
   second only the 1234 card.
*/

क्रमागत rhine_revs अणु
	VT86C100A	= 0x00,
	VTunknown0	= 0x20,
	VT6102		= 0x40,
	VT8231		= 0x50,	/* Integrated MAC */
	VT8233		= 0x60,	/* Integrated MAC */
	VT8235		= 0x74,	/* Integrated MAC */
	VT8237		= 0x78,	/* Integrated MAC */
	VT8251		= 0x7C,	/* Integrated MAC */
	VT6105		= 0x80,
	VT6105_B0	= 0x83,
	VT6105L		= 0x8A,
	VT6107		= 0x8C,
	VTunknown2	= 0x8E,
	VT6105M		= 0x90,	/* Management adapter */
पूर्ण;

क्रमागत rhine_quirks अणु
	rqWOL		= 0x0001,	/* Wake-On-LAN support */
	rqForceReset	= 0x0002,
	rq6patterns	= 0x0040,	/* 6 instead of 4 patterns क्रम WOL */
	rqStatusWBRace	= 0x0080,	/* Tx Status Writeback Error possible */
	rqRhineI	= 0x0100,	/* See comment below */
	rqIntPHY	= 0x0200,	/* Integrated PHY */
	rqMgmt		= 0x0400,	/* Management adapter */
	rqNeedEnMMIO	= 0x0800,	/* Whether the core needs to be
					 * चयनed from PIO mode to MMIO
					 * (only applies to PCI)
					 */
पूर्ण;
/*
 * rqRhineI: VT86C100A (aka Rhine-I) uses dअगरferent bits to enable
 * MMIO as well as क्रम the collision counter and the Tx FIFO underflow
 * indicator. In addition, Tx and Rx buffers need to 4 byte aligned.
 */

/* Beware of PCI posted ग_लिखोs */
#घोषणा IOSYNC	करो अणु ioपढ़ो8(ioaddr + StationAddr); पूर्ण जबतक (0)

अटल स्थिर काष्ठा pci_device_id rhine_pci_tbl[] = अणु
	अणु 0x1106, 0x3043, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,	/* VT86C100A */
	अणु 0x1106, 0x3065, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,	/* VT6102 */
	अणु 0x1106, 0x3106, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,	/* 6105अणु,L,LOMपूर्ण */
	अणु 0x1106, 0x3053, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,	/* VT6105M */
	अणु पूर्ण	/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, rhine_pci_tbl);

/* OpenFirmware identअगरiers क्रम platक्रमm-bus devices
 * The .data field is currently only used to store quirks
 */
अटल u32 vt8500_quirks = rqWOL | rqForceReset | rq6patterns;
अटल स्थिर काष्ठा of_device_id rhine_of_tbl[] = अणु
	अणु .compatible = "via,vt8500-rhine", .data = &vt8500_quirks पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(of, rhine_of_tbl);

/* Offsets to the device रेजिस्टरs. */
क्रमागत रेजिस्टर_offsets अणु
	StationAddr=0x00, RxConfig=0x06, TxConfig=0x07, ChipCmd=0x08,
	ChipCmd1=0x09, TQWake=0x0A,
	IntrStatus=0x0C, IntrEnable=0x0E,
	MulticastFilter0=0x10, MulticastFilter1=0x14,
	RxRingPtr=0x18, TxRingPtr=0x1C, GFIFOTest=0x54,
	MIIPhyAddr=0x6C, MIIStatus=0x6D, PCIBusConfig=0x6E, PCIBusConfig1=0x6F,
	MIICmd=0x70, MIIRegAddr=0x71, MIIData=0x72, MACRegEEcsr=0x74,
	ConfigA=0x78, ConfigB=0x79, ConfigC=0x7A, ConfigD=0x7B,
	RxMissed=0x7C, RxCRCErrs=0x7E, MiscCmd=0x81,
	StickyHW=0x83, IntrStatus2=0x84,
	CamMask=0x88, CamCon=0x92, CamAddr=0x93,
	WOLcrSet=0xA0, PwcfgSet=0xA1, WOLcgSet=0xA3, WOLcrClr=0xA4,
	WOLcrClr1=0xA6, WOLcgClr=0xA7,
	PwrcsrSet=0xA8, PwrcsrSet1=0xA9, PwrcsrClr=0xAC, PwrcsrClr1=0xAD,
पूर्ण;

/* Bits in ConfigD */
क्रमागत backoff_bits अणु
	BackOptional=0x01, BackModअगरy=0x02,
	BackCaptureEffect=0x04, BackRanकरोm=0x08
पूर्ण;

/* Bits in the TxConfig (TCR) रेजिस्टर */
क्रमागत tcr_bits अणु
	TCR_PQEN=0x01,
	TCR_LB0=0x02,		/* loopback[0] */
	TCR_LB1=0x04,		/* loopback[1] */
	TCR_OFSET=0x08,
	TCR_RTGOPT=0x10,
	TCR_RTFT0=0x20,
	TCR_RTFT1=0x40,
	TCR_RTSF=0x80,
पूर्ण;

/* Bits in the CamCon (CAMC) रेजिस्टर */
क्रमागत camcon_bits अणु
	CAMC_CAMEN=0x01,
	CAMC_VCAMSL=0x02,
	CAMC_CAMWR=0x04,
	CAMC_CAMRD=0x08,
पूर्ण;

/* Bits in the PCIBusConfig1 (BCR1) रेजिस्टर */
क्रमागत bcr1_bits अणु
	BCR1_POT0=0x01,
	BCR1_POT1=0x02,
	BCR1_POT2=0x04,
	BCR1_CTFT0=0x08,
	BCR1_CTFT1=0x10,
	BCR1_CTSF=0x20,
	BCR1_TXQNOBK=0x40,	/* क्रम VT6105 */
	BCR1_VIDFR=0x80,	/* क्रम VT6105 */
	BCR1_MED0=0x40,		/* क्रम VT6102 */
	BCR1_MED1=0x80,		/* क्रम VT6102 */
पूर्ण;

/* Registers we check that mmio and reg are the same. */
अटल स्थिर पूर्णांक mmio_verअगरy_रेजिस्टरs[] = अणु
	RxConfig, TxConfig, IntrEnable, ConfigA, ConfigB, ConfigC, ConfigD,
	0
पूर्ण;

/* Bits in the पूर्णांकerrupt status/mask रेजिस्टरs. */
क्रमागत पूर्णांकr_status_bits अणु
	IntrRxDone	= 0x0001,
	IntrTxDone	= 0x0002,
	IntrRxErr	= 0x0004,
	IntrTxError	= 0x0008,
	IntrRxEmpty	= 0x0020,
	IntrPCIErr	= 0x0040,
	IntrStatsMax	= 0x0080,
	IntrRxEarly	= 0x0100,
	IntrTxUnderrun	= 0x0210,
	IntrRxOverflow	= 0x0400,
	IntrRxDropped	= 0x0800,
	IntrRxNoBuf	= 0x1000,
	IntrTxAborted	= 0x2000,
	IntrLinkChange	= 0x4000,
	IntrRxWakeUp	= 0x8000,
	IntrTxDescRace		= 0x080000,	/* mapped from IntrStatus2 */
	IntrNormalSummary	= IntrRxDone | IntrTxDone,
	IntrTxErrSummary	= IntrTxDescRace | IntrTxAborted | IntrTxError |
				  IntrTxUnderrun,
पूर्ण;

/* Bits in WOLcrSet/WOLcrClr and PwrcsrSet/PwrcsrClr */
क्रमागत wol_bits अणु
	WOLucast	= 0x10,
	WOLmagic	= 0x20,
	WOLbmcast	= 0x30,
	WOLlnkon	= 0x40,
	WOLlnkoff	= 0x80,
पूर्ण;

/* The Rx and Tx buffer descriptors. */
काष्ठा rx_desc अणु
	__le32 rx_status;
	__le32 desc_length; /* Chain flag, Buffer/frame length */
	__le32 addr;
	__le32 next_desc;
पूर्ण;
काष्ठा tx_desc अणु
	__le32 tx_status;
	__le32 desc_length; /* Chain flag, Tx Config, Frame length */
	__le32 addr;
	__le32 next_desc;
पूर्ण;

/* Initial value क्रम tx_desc.desc_length, Buffer size goes to bits 0-10 */
#घोषणा TXDESC		0x00e08000

क्रमागत rx_status_bits अणु
	RxOK=0x8000, RxWholePkt=0x0300, RxErr=0x008F
पूर्ण;

/* Bits in *_desc.*_status */
क्रमागत desc_status_bits अणु
	DescOwn=0x80000000
पूर्ण;

/* Bits in *_desc.*_length */
क्रमागत desc_length_bits अणु
	DescTag=0x00010000
पूर्ण;

/* Bits in ChipCmd. */
क्रमागत chip_cmd_bits अणु
	CmdInit=0x01, CmdStart=0x02, CmdStop=0x04, CmdRxOn=0x08,
	CmdTxOn=0x10, Cmd1TxDemand=0x20, CmdRxDemand=0x40,
	Cmd1EarlyRx=0x01, Cmd1EarlyTx=0x02, Cmd1FDuplex=0x04,
	Cmd1NoTxPoll=0x08, Cmd1Reset=0x80,
पूर्ण;

काष्ठा rhine_stats अणु
	u64		packets;
	u64		bytes;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

काष्ठा rhine_निजी अणु
	/* Bit mask क्रम configured VLAN ids */
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];

	/* Descriptor rings */
	काष्ठा rx_desc *rx_ring;
	काष्ठा tx_desc *tx_ring;
	dma_addr_t rx_ring_dma;
	dma_addr_t tx_ring_dma;

	/* The addresses of receive-in-place skbuffs. */
	काष्ठा sk_buff *rx_skbuff[RX_RING_SIZE];
	dma_addr_t rx_skbuff_dma[RX_RING_SIZE];

	/* The saved address of a sent-in-place packet/buffer, क्रम later मुक्त(). */
	काष्ठा sk_buff *tx_skbuff[TX_RING_SIZE];
	dma_addr_t tx_skbuff_dma[TX_RING_SIZE];

	/* Tx bounce buffers (Rhine-I only) */
	अचिन्हित अक्षर *tx_buf[TX_RING_SIZE];
	अचिन्हित अक्षर *tx_bufs;
	dma_addr_t tx_bufs_dma;

	पूर्णांक irq;
	दीर्घ pioaddr;
	काष्ठा net_device *dev;
	काष्ठा napi_काष्ठा napi;
	spinlock_t lock;
	काष्ठा mutex task_lock;
	bool task_enable;
	काष्ठा work_काष्ठा slow_event_task;
	काष्ठा work_काष्ठा reset_task;

	u32 msg_enable;

	/* Frequently used values: keep some adjacent क्रम cache effect. */
	u32 quirks;
	अचिन्हित पूर्णांक cur_rx;
	अचिन्हित पूर्णांक cur_tx, dirty_tx;
	अचिन्हित पूर्णांक rx_buf_sz;		/* Based on MTU+slack. */
	काष्ठा rhine_stats rx_stats;
	काष्ठा rhine_stats tx_stats;
	u8 wolopts;

	u8 tx_thresh, rx_thresh;

	काष्ठा mii_अगर_info mii_अगर;
	व्योम __iomem *base;
पूर्ण;

#घोषणा BYTE_REG_BITS_ON(x, p)      करो अणु ioग_लिखो8((ioपढ़ो8((p))|(x)), (p)); पूर्ण जबतक (0)
#घोषणा WORD_REG_BITS_ON(x, p)      करो अणु ioग_लिखो16((ioपढ़ो16((p))|(x)), (p)); पूर्ण जबतक (0)
#घोषणा DWORD_REG_BITS_ON(x, p)     करो अणु ioग_लिखो32((ioपढ़ो32((p))|(x)), (p)); पूर्ण जबतक (0)

#घोषणा BYTE_REG_BITS_IS_ON(x, p)   (ioपढ़ो8((p)) & (x))
#घोषणा WORD_REG_BITS_IS_ON(x, p)   (ioपढ़ो16((p)) & (x))
#घोषणा DWORD_REG_BITS_IS_ON(x, p)  (ioपढ़ो32((p)) & (x))

#घोषणा BYTE_REG_BITS_OFF(x, p)     करो अणु ioग_लिखो8(ioपढ़ो8((p)) & (~(x)), (p)); पूर्ण जबतक (0)
#घोषणा WORD_REG_BITS_OFF(x, p)     करो अणु ioग_लिखो16(ioपढ़ो16((p)) & (~(x)), (p)); पूर्ण जबतक (0)
#घोषणा DWORD_REG_BITS_OFF(x, p)    करो अणु ioग_लिखो32(ioपढ़ो32((p)) & (~(x)), (p)); पूर्ण जबतक (0)

#घोषणा BYTE_REG_BITS_SET(x, m, p)   करो अणु ioग_लिखो8((ioपढ़ो8((p)) & (~(m)))|(x), (p)); पूर्ण जबतक (0)
#घोषणा WORD_REG_BITS_SET(x, m, p)   करो अणु ioग_लिखो16((ioपढ़ो16((p)) & (~(m)))|(x), (p)); पूर्ण जबतक (0)
#घोषणा DWORD_REG_BITS_SET(x, m, p)  करो अणु ioग_लिखो32((ioपढ़ो32((p)) & (~(m)))|(x), (p)); पूर्ण जबतक (0)


अटल पूर्णांक  mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value);
अटल पूर्णांक  rhine_खोलो(काष्ठा net_device *dev);
अटल व्योम rhine_reset_task(काष्ठा work_काष्ठा *work);
अटल व्योम rhine_slow_event_task(काष्ठा work_काष्ठा *work);
अटल व्योम rhine_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल netdev_tx_t rhine_start_tx(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev);
अटल irqवापस_t rhine_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल व्योम rhine_tx(काष्ठा net_device *dev);
अटल पूर्णांक rhine_rx(काष्ठा net_device *dev, पूर्णांक limit);
अटल व्योम rhine_set_rx_mode(काष्ठा net_device *dev);
अटल व्योम rhine_get_stats64(काष्ठा net_device *dev,
			      काष्ठा rtnl_link_stats64 *stats);
अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;
अटल पूर्णांक  rhine_बंद(काष्ठा net_device *dev);
अटल पूर्णांक rhine_vlan_rx_add_vid(काष्ठा net_device *dev,
				 __be16 proto, u16 vid);
अटल पूर्णांक rhine_vlan_rx_समाप्त_vid(काष्ठा net_device *dev,
				  __be16 proto, u16 vid);
अटल व्योम rhine_restart_tx(काष्ठा net_device *dev);

अटल व्योम rhine_रुको_bit(काष्ठा rhine_निजी *rp, u8 reg, u8 mask, bool low)
अणु
	व्योम __iomem *ioaddr = rp->base;
	पूर्णांक i;

	क्रम (i = 0; i < 1024; i++) अणु
		bool has_mask_bits = !!(ioपढ़ो8(ioaddr + reg) & mask);

		अगर (low ^ has_mask_bits)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (i > 64) अणु
		netअगर_dbg(rp, hw, rp->dev, "%s bit wait (%02x/%02x) cycle "
			  "count: %04d\n", low ? "low" : "high", reg, mask, i);
	पूर्ण
पूर्ण

अटल व्योम rhine_रुको_bit_high(काष्ठा rhine_निजी *rp, u8 reg, u8 mask)
अणु
	rhine_रुको_bit(rp, reg, mask, false);
पूर्ण

अटल व्योम rhine_रुको_bit_low(काष्ठा rhine_निजी *rp, u8 reg, u8 mask)
अणु
	rhine_रुको_bit(rp, reg, mask, true);
पूर्ण

अटल u32 rhine_get_events(काष्ठा rhine_निजी *rp)
अणु
	व्योम __iomem *ioaddr = rp->base;
	u32 पूर्णांकr_status;

	पूर्णांकr_status = ioपढ़ो16(ioaddr + IntrStatus);
	/* On Rhine-II, Bit 3 indicates Tx descriptor ग_लिखो-back race. */
	अगर (rp->quirks & rqStatusWBRace)
		पूर्णांकr_status |= ioपढ़ो8(ioaddr + IntrStatus2) << 16;
	वापस पूर्णांकr_status;
पूर्ण

अटल व्योम rhine_ack_events(काष्ठा rhine_निजी *rp, u32 mask)
अणु
	व्योम __iomem *ioaddr = rp->base;

	अगर (rp->quirks & rqStatusWBRace)
		ioग_लिखो8(mask >> 16, ioaddr + IntrStatus2);
	ioग_लिखो16(mask, ioaddr + IntrStatus);
पूर्ण

/*
 * Get घातer related रेजिस्टरs पूर्णांकo sane state.
 * Notअगरy user about past WOL event.
 */
अटल व्योम rhine_घातer_init(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;
	u16 wolstat;

	अगर (rp->quirks & rqWOL) अणु
		/* Make sure chip is in घातer state D0 */
		ioग_लिखो8(ioपढ़ो8(ioaddr + StickyHW) & 0xFC, ioaddr + StickyHW);

		/* Disable "force PME-enable" */
		ioग_लिखो8(0x80, ioaddr + WOLcgClr);

		/* Clear घातer-event config bits (WOL) */
		ioग_लिखो8(0xFF, ioaddr + WOLcrClr);
		/* More recent cards can manage two additional patterns */
		अगर (rp->quirks & rq6patterns)
			ioग_लिखो8(0x03, ioaddr + WOLcrClr1);

		/* Save घातer-event status bits */
		wolstat = ioपढ़ो8(ioaddr + PwrcsrSet);
		अगर (rp->quirks & rq6patterns)
			wolstat |= (ioपढ़ो8(ioaddr + PwrcsrSet1) & 0x03) << 8;

		/* Clear घातer-event status bits */
		ioग_लिखो8(0xFF, ioaddr + PwrcsrClr);
		अगर (rp->quirks & rq6patterns)
			ioग_लिखो8(0x03, ioaddr + PwrcsrClr1);

		अगर (wolstat) अणु
			अक्षर *reason;
			चयन (wolstat) अणु
			हाल WOLmagic:
				reason = "Magic packet";
				अवरोध;
			हाल WOLlnkon:
				reason = "Link went up";
				अवरोध;
			हाल WOLlnkoff:
				reason = "Link went down";
				अवरोध;
			हाल WOLucast:
				reason = "Unicast packet";
				अवरोध;
			हाल WOLbmcast:
				reason = "Multicast/broadcast packet";
				अवरोध;
			शेष:
				reason = "Unknown";
			पूर्ण
			netdev_info(dev, "Woke system up. Reason: %s\n",
				    reason);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rhine_chip_reset(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;
	u8 cmd1;

	ioग_लिखो8(Cmd1Reset, ioaddr + ChipCmd1);
	IOSYNC;

	अगर (ioपढ़ो8(ioaddr + ChipCmd1) & Cmd1Reset) अणु
		netdev_info(dev, "Reset not complete yet. Trying harder.\n");

		/* Force reset */
		अगर (rp->quirks & rqForceReset)
			ioग_लिखो8(0x40, ioaddr + MiscCmd);

		/* Reset can take somewhat दीर्घer (rare) */
		rhine_रुको_bit_low(rp, ChipCmd1, Cmd1Reset);
	पूर्ण

	cmd1 = ioपढ़ो8(ioaddr + ChipCmd1);
	netअगर_info(rp, hw, dev, "Reset %s\n", (cmd1 & Cmd1Reset) ?
		   "failed" : "succeeded");
पूर्ण

अटल व्योम enable_mmio(दीर्घ pioaddr, u32 quirks)
अणु
	पूर्णांक n;

	अगर (quirks & rqNeedEnMMIO) अणु
		अगर (quirks & rqRhineI) अणु
			/* More recent करोcs say that this bit is reserved */
			n = inb(pioaddr + ConfigA) | 0x20;
			outb(n, pioaddr + ConfigA);
		पूर्ण अन्यथा अणु
			n = inb(pioaddr + ConfigD) | 0x80;
			outb(n, pioaddr + ConfigD);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_mmio(काष्ठा device *hwdev,
			      दीर्घ pioaddr,
			      व्योम __iomem *ioaddr,
			      u32 quirks)
अणु
	अगर (quirks & rqNeedEnMMIO) अणु
		पूर्णांक i = 0;

		/* Check that selected MMIO रेजिस्टरs match the PIO ones */
		जबतक (mmio_verअगरy_रेजिस्टरs[i]) अणु
			पूर्णांक reg = mmio_verअगरy_रेजिस्टरs[i++];
			अचिन्हित अक्षर a = inb(pioaddr+reg);
			अचिन्हित अक्षर b = पढ़ोb(ioaddr+reg);

			अगर (a != b) अणु
				dev_err(hwdev,
					"MMIO do not match PIO [%02x] (%02x != %02x)\n",
					reg, a, b);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Loads bytes 0x00-0x05, 0x6E-0x6F, 0x78-0x7B from EEPROM
 * (plus 0x6C क्रम Rhine-I/II)
 */
अटल व्योम rhine_reload_eeprom(दीर्घ pioaddr, काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;
	पूर्णांक i;

	outb(0x20, pioaddr + MACRegEEcsr);
	क्रम (i = 0; i < 1024; i++) अणु
		अगर (!(inb(pioaddr + MACRegEEcsr) & 0x20))
			अवरोध;
	पूर्ण
	अगर (i > 512)
		pr_info("%4d cycles used @ %s:%d\n", i, __func__, __LINE__);

	/*
	 * Reloading from EEPROM overग_लिखोs ConfigA-D, so we must re-enable
	 * MMIO. If reloading EEPROM was करोne first this could be aव्योमed, but
	 * it is not known अगर that still works with the "win98-reboot" problem.
	 */
	enable_mmio(pioaddr, rp->quirks);

	/* Turn off EEPROM-controlled wake-up (magic packet) */
	अगर (rp->quirks & rqWOL)
		ioग_लिखो8(ioपढ़ो8(ioaddr + ConfigA) & 0xFC, ioaddr + ConfigA);

पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम rhine_poll(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	स्थिर पूर्णांक irq = rp->irq;

	disable_irq(irq);
	rhine_पूर्णांकerrupt(irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

अटल व्योम rhine_kick_tx_threshold(काष्ठा rhine_निजी *rp)
अणु
	अगर (rp->tx_thresh < 0xe0) अणु
		व्योम __iomem *ioaddr = rp->base;

		rp->tx_thresh += 0x20;
		BYTE_REG_BITS_SET(rp->tx_thresh, 0x80, ioaddr + TxConfig);
	पूर्ण
पूर्ण

अटल व्योम rhine_tx_err(काष्ठा rhine_निजी *rp, u32 status)
अणु
	काष्ठा net_device *dev = rp->dev;

	अगर (status & IntrTxAborted) अणु
		netअगर_info(rp, tx_err, dev,
			   "Abort %08x, frame dropped\n", status);
	पूर्ण

	अगर (status & IntrTxUnderrun) अणु
		rhine_kick_tx_threshold(rp);
		netअगर_info(rp, tx_err ,dev, "Transmitter underrun, "
			   "Tx threshold now %02x\n", rp->tx_thresh);
	पूर्ण

	अगर (status & IntrTxDescRace)
		netअगर_info(rp, tx_err, dev, "Tx descriptor write-back race\n");

	अगर ((status & IntrTxError) &&
	    (status & (IntrTxAborted | IntrTxUnderrun | IntrTxDescRace)) == 0) अणु
		rhine_kick_tx_threshold(rp);
		netअगर_info(rp, tx_err, dev, "Unspecified error. "
			   "Tx threshold now %02x\n", rp->tx_thresh);
	पूर्ण

	rhine_restart_tx(dev);
पूर्ण

अटल व्योम rhine_update_rx_crc_and_missed_errord(काष्ठा rhine_निजी *rp)
अणु
	व्योम __iomem *ioaddr = rp->base;
	काष्ठा net_device_stats *stats = &rp->dev->stats;

	stats->rx_crc_errors    += ioपढ़ो16(ioaddr + RxCRCErrs);
	stats->rx_missed_errors += ioपढ़ो16(ioaddr + RxMissed);

	/*
	 * Clears the "tally counters" क्रम CRC errors and missed frames(?).
	 * It has been reported that some chips need a ग_लिखो of 0 to clear
	 * these, क्रम others the counters are set to 1 when written to and
	 * instead cleared when पढ़ो. So we clear them both ways ...
	 */
	ioग_लिखो32(0, ioaddr + RxMissed);
	ioपढ़ो16(ioaddr + RxCRCErrs);
	ioपढ़ो16(ioaddr + RxMissed);
पूर्ण

#घोषणा RHINE_EVENT_NAPI_RX	(IntrRxDone | \
				 IntrRxErr | \
				 IntrRxEmpty | \
				 IntrRxOverflow	| \
				 IntrRxDropped | \
				 IntrRxNoBuf | \
				 IntrRxWakeUp)

#घोषणा RHINE_EVENT_NAPI_TX_ERR	(IntrTxError | \
				 IntrTxAborted | \
				 IntrTxUnderrun | \
				 IntrTxDescRace)
#घोषणा RHINE_EVENT_NAPI_TX	(IntrTxDone | RHINE_EVENT_NAPI_TX_ERR)

#घोषणा RHINE_EVENT_NAPI	(RHINE_EVENT_NAPI_RX | \
				 RHINE_EVENT_NAPI_TX | \
				 IntrStatsMax)
#घोषणा RHINE_EVENT_SLOW	(IntrPCIErr | IntrLinkChange)
#घोषणा RHINE_EVENT		(RHINE_EVENT_NAPI | RHINE_EVENT_SLOW)

अटल पूर्णांक rhine_napipoll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा rhine_निजी *rp = container_of(napi, काष्ठा rhine_निजी, napi);
	काष्ठा net_device *dev = rp->dev;
	व्योम __iomem *ioaddr = rp->base;
	u16 enable_mask = RHINE_EVENT & 0xffff;
	पूर्णांक work_करोne = 0;
	u32 status;

	status = rhine_get_events(rp);
	rhine_ack_events(rp, status & ~RHINE_EVENT_SLOW);

	अगर (status & RHINE_EVENT_NAPI_RX)
		work_करोne += rhine_rx(dev, budget);

	अगर (status & RHINE_EVENT_NAPI_TX) अणु
		अगर (status & RHINE_EVENT_NAPI_TX_ERR) अणु
			/* Aव्योम scavenging beक्रमe Tx engine turned off */
			rhine_रुको_bit_low(rp, ChipCmd, CmdTxOn);
			अगर (ioपढ़ो8(ioaddr + ChipCmd) & CmdTxOn)
				netअगर_warn(rp, tx_err, dev, "Tx still on\n");
		पूर्ण

		rhine_tx(dev);

		अगर (status & RHINE_EVENT_NAPI_TX_ERR)
			rhine_tx_err(rp, status);
	पूर्ण

	अगर (status & IntrStatsMax) अणु
		spin_lock(&rp->lock);
		rhine_update_rx_crc_and_missed_errord(rp);
		spin_unlock(&rp->lock);
	पूर्ण

	अगर (status & RHINE_EVENT_SLOW) अणु
		enable_mask &= ~RHINE_EVENT_SLOW;
		schedule_work(&rp->slow_event_task);
	पूर्ण

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		ioग_लिखो16(enable_mask, ioaddr + IntrEnable);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल व्योम rhine_hw_init(काष्ठा net_device *dev, दीर्घ pioaddr)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	/* Reset the chip to erase previous misconfiguration. */
	rhine_chip_reset(dev);

	/* Rhine-I needs extra समय to recuperate beक्रमe EEPROM reload */
	अगर (rp->quirks & rqRhineI)
		msleep(5);

	/* Reload EEPROM controlled bytes cleared by soft reset */
	अगर (dev_is_pci(dev->dev.parent))
		rhine_reload_eeprom(pioaddr, dev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops rhine_netdev_ops = अणु
	.nकरो_खोलो		 = rhine_खोलो,
	.nकरो_stop		 = rhine_बंद,
	.nकरो_start_xmit		 = rhine_start_tx,
	.nकरो_get_stats64	 = rhine_get_stats64,
	.nकरो_set_rx_mode	 = rhine_set_rx_mode,
	.nकरो_validate_addr	 = eth_validate_addr,
	.nकरो_set_mac_address 	 = eth_mac_addr,
	.nकरो_करो_ioctl		 = netdev_ioctl,
	.nकरो_tx_समयout 	 = rhine_tx_समयout,
	.nकरो_vlan_rx_add_vid	 = rhine_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	 = rhine_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	 = rhine_poll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक rhine_init_one_common(काष्ठा device *hwdev, u32 quirks,
				 दीर्घ pioaddr, व्योम __iomem *ioaddr, पूर्णांक irq)
अणु
	काष्ठा net_device *dev;
	काष्ठा rhine_निजी *rp;
	पूर्णांक i, rc, phy_id;
	स्थिर अक्षर *name;

	/* this should always be supported */
	rc = dma_set_mask(hwdev, DMA_BIT_MASK(32));
	अगर (rc) अणु
		dev_err(hwdev, "32-bit DMA addresses not supported by the card!?\n");
		जाओ err_out;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा rhine_निजी));
	अगर (!dev) अणु
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण
	SET_NETDEV_DEV(dev, hwdev);

	rp = netdev_priv(dev);
	rp->dev = dev;
	rp->quirks = quirks;
	rp->pioaddr = pioaddr;
	rp->base = ioaddr;
	rp->irq = irq;
	rp->msg_enable = netअगर_msg_init(debug, RHINE_MSG_DEFAULT);

	phy_id = rp->quirks & rqIntPHY ? 1 : 0;

	u64_stats_init(&rp->tx_stats.syncp);
	u64_stats_init(&rp->rx_stats.syncp);

	/* Get chip रेजिस्टरs पूर्णांकo a sane state */
	rhine_घातer_init(dev);
	rhine_hw_init(dev, pioaddr);

	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = ioपढ़ो8(ioaddr + StationAddr + i);

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		/* Report it and use a अक्रमom ethernet address instead */
		netdev_err(dev, "Invalid MAC address: %pM\n", dev->dev_addr);
		eth_hw_addr_अक्रमom(dev);
		netdev_info(dev, "Using random MAC address: %pM\n",
			    dev->dev_addr);
	पूर्ण

	/* For Rhine-I/II, phy_id is loaded from EEPROM */
	अगर (!phy_id)
		phy_id = ioपढ़ो8(ioaddr + 0x6C);

	spin_lock_init(&rp->lock);
	mutex_init(&rp->task_lock);
	INIT_WORK(&rp->reset_task, rhine_reset_task);
	INIT_WORK(&rp->slow_event_task, rhine_slow_event_task);

	rp->mii_अगर.dev = dev;
	rp->mii_अगर.mdio_पढ़ो = mdio_पढ़ो;
	rp->mii_अगर.mdio_ग_लिखो = mdio_ग_लिखो;
	rp->mii_अगर.phy_id_mask = 0x1f;
	rp->mii_अगर.reg_num_mask = 0x1f;

	/* The chip-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &rhine_netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	netअगर_napi_add(dev, &rp->napi, rhine_napipoll, 64);

	अगर (rp->quirks & rqRhineI)
		dev->features |= NETIF_F_SG|NETIF_F_HW_CSUM;

	अगर (rp->quirks & rqMgmt)
		dev->features |= NETIF_F_HW_VLAN_CTAG_TX |
				 NETIF_F_HW_VLAN_CTAG_RX |
				 NETIF_F_HW_VLAN_CTAG_FILTER;

	/* dev->name not defined beक्रमe रेजिस्टर_netdev()! */
	rc = रेजिस्टर_netdev(dev);
	अगर (rc)
		जाओ err_out_मुक्त_netdev;

	अगर (rp->quirks & rqRhineI)
		name = "Rhine";
	अन्यथा अगर (rp->quirks & rqStatusWBRace)
		name = "Rhine II";
	अन्यथा अगर (rp->quirks & rqMgmt)
		name = "Rhine III (Management Adapter)";
	अन्यथा
		name = "Rhine III";

	netdev_info(dev, "VIA %s at %p, %pM, IRQ %d\n",
		    name, ioaddr, dev->dev_addr, rp->irq);

	dev_set_drvdata(hwdev, dev);

	अणु
		u16 mii_cmd;
		पूर्णांक mii_status = mdio_पढ़ो(dev, phy_id, 1);
		mii_cmd = mdio_पढ़ो(dev, phy_id, MII_BMCR) & ~BMCR_ISOLATE;
		mdio_ग_लिखो(dev, phy_id, MII_BMCR, mii_cmd);
		अगर (mii_status != 0xffff && mii_status != 0x0000) अणु
			rp->mii_अगर.advertising = mdio_पढ़ो(dev, phy_id, 4);
			netdev_info(dev,
				    "MII PHY found at address %d, status 0x%04x advertising %04x Link %04x\n",
				    phy_id,
				    mii_status, rp->mii_अगर.advertising,
				    mdio_पढ़ो(dev, phy_id, 5));

			/* set IFF_RUNNING */
			अगर (mii_status & BMSR_LSTATUS)
				netअगर_carrier_on(dev);
			अन्यथा
				netअगर_carrier_off(dev);

		पूर्ण
	पूर्ण
	rp->mii_अगर.phy_id = phy_id;
	अगर (aव्योम_D3)
		netअगर_info(rp, probe, dev, "No D3 power state at shutdown\n");

	वापस 0;

err_out_मुक्त_netdev:
	मुक्त_netdev(dev);
err_out:
	वापस rc;
पूर्ण

अटल पूर्णांक rhine_init_one_pci(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *hwdev = &pdev->dev;
	पूर्णांक rc;
	दीर्घ pioaddr, memaddr;
	व्योम __iomem *ioaddr;
	पूर्णांक io_size = pdev->revision < VTunknown0 ? 128 : 256;

/* This driver was written to use PCI memory space. Some early versions
 * of the Rhine may only work correctly with I/O space accesses.
 * TODO: determine क्रम which revisions this is true and assign the flag
 *	 in code as opposed to this Kconfig option (???)
 */
#अगर_घोषित CONFIG_VIA_RHINE_MMIO
	u32 quirks = rqNeedEnMMIO;
#अन्यथा
	u32 quirks = 0;
#पूर्ण_अगर

	rc = pci_enable_device(pdev);
	अगर (rc)
		जाओ err_out;

	अगर (pdev->revision < VTunknown0) अणु
		quirks |= rqRhineI;
	पूर्ण अन्यथा अगर (pdev->revision >= VT6102) अणु
		quirks |= rqWOL | rqForceReset;
		अगर (pdev->revision < VT6105) अणु
			quirks |= rqStatusWBRace;
		पूर्ण अन्यथा अणु
			quirks |= rqIntPHY;
			अगर (pdev->revision >= VT6105_B0)
				quirks |= rq6patterns;
			अगर (pdev->revision >= VT6105M)
				quirks |= rqMgmt;
		पूर्ण
	पूर्ण

	/* sanity check */
	अगर ((pci_resource_len(pdev, 0) < io_size) ||
	    (pci_resource_len(pdev, 1) < io_size)) अणु
		rc = -EIO;
		dev_err(hwdev, "Insufficient PCI resources, aborting\n");
		जाओ err_out_pci_disable;
	पूर्ण

	pioaddr = pci_resource_start(pdev, 0);
	memaddr = pci_resource_start(pdev, 1);

	pci_set_master(pdev);

	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc)
		जाओ err_out_pci_disable;

	ioaddr = pci_iomap(pdev, (quirks & rqNeedEnMMIO ? 1 : 0), io_size);
	अगर (!ioaddr) अणु
		rc = -EIO;
		dev_err(hwdev,
			"ioremap failed for device %s, region 0x%X @ 0x%lX\n",
			dev_name(hwdev), io_size, memaddr);
		जाओ err_out_मुक्त_res;
	पूर्ण

	enable_mmio(pioaddr, quirks);

	rc = verअगरy_mmio(hwdev, pioaddr, ioaddr, quirks);
	अगर (rc)
		जाओ err_out_unmap;

	rc = rhine_init_one_common(&pdev->dev, quirks,
				   pioaddr, ioaddr, pdev->irq);
	अगर (!rc)
		वापस 0;

err_out_unmap:
	pci_iounmap(pdev, ioaddr);
err_out_मुक्त_res:
	pci_release_regions(pdev);
err_out_pci_disable:
	pci_disable_device(pdev);
err_out:
	वापस rc;
पूर्ण

अटल पूर्णांक rhine_init_one_platक्रमm(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर u32 *quirks;
	पूर्णांक irq;
	व्योम __iomem *ioaddr;

	match = of_match_device(rhine_of_tbl, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;

	ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ioaddr))
		वापस PTR_ERR(ioaddr);

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	अगर (!irq)
		वापस -EINVAL;

	quirks = match->data;
	अगर (!quirks)
		वापस -EINVAL;

	वापस rhine_init_one_common(&pdev->dev, *quirks,
				     (दीर्घ)ioaddr, ioaddr, irq);
पूर्ण

अटल पूर्णांक alloc_ring(काष्ठा net_device* dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	काष्ठा device *hwdev = dev->dev.parent;
	व्योम *ring;
	dma_addr_t ring_dma;

	ring = dma_alloc_coherent(hwdev,
				  RX_RING_SIZE * माप(काष्ठा rx_desc) +
				  TX_RING_SIZE * माप(काष्ठा tx_desc),
				  &ring_dma,
				  GFP_ATOMIC);
	अगर (!ring) अणु
		netdev_err(dev, "Could not allocate DMA memory\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (rp->quirks & rqRhineI) अणु
		rp->tx_bufs = dma_alloc_coherent(hwdev,
						 PKT_BUF_SZ * TX_RING_SIZE,
						 &rp->tx_bufs_dma,
						 GFP_ATOMIC);
		अगर (rp->tx_bufs == शून्य) अणु
			dma_मुक्त_coherent(hwdev,
					  RX_RING_SIZE * माप(काष्ठा rx_desc) +
					  TX_RING_SIZE * माप(काष्ठा tx_desc),
					  ring, ring_dma);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	rp->rx_ring = ring;
	rp->tx_ring = ring + RX_RING_SIZE * माप(काष्ठा rx_desc);
	rp->rx_ring_dma = ring_dma;
	rp->tx_ring_dma = ring_dma + RX_RING_SIZE * माप(काष्ठा rx_desc);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_ring(काष्ठा net_device* dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	काष्ठा device *hwdev = dev->dev.parent;

	dma_मुक्त_coherent(hwdev,
			  RX_RING_SIZE * माप(काष्ठा rx_desc) +
			  TX_RING_SIZE * माप(काष्ठा tx_desc),
			  rp->rx_ring, rp->rx_ring_dma);
	rp->tx_ring = शून्य;

	अगर (rp->tx_bufs)
		dma_मुक्त_coherent(hwdev, PKT_BUF_SZ * TX_RING_SIZE,
				  rp->tx_bufs, rp->tx_bufs_dma);

	rp->tx_bufs = शून्य;

पूर्ण

काष्ठा rhine_skb_dma अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
पूर्ण;

अटल अंतरभूत पूर्णांक rhine_skb_dma_init(काष्ठा net_device *dev,
				     काष्ठा rhine_skb_dma *sd)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	काष्ठा device *hwdev = dev->dev.parent;
	स्थिर पूर्णांक size = rp->rx_buf_sz;

	sd->skb = netdev_alloc_skb(dev, size);
	अगर (!sd->skb)
		वापस -ENOMEM;

	sd->dma = dma_map_single(hwdev, sd->skb->data, size, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(hwdev, sd->dma))) अणु
		netअगर_err(rp, drv, dev, "Rx DMA mapping failure\n");
		dev_kमुक्त_skb_any(sd->skb);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rhine_reset_rbufs(काष्ठा rhine_निजी *rp)
अणु
	पूर्णांक i;

	rp->cur_rx = 0;

	क्रम (i = 0; i < RX_RING_SIZE; i++)
		rp->rx_ring[i].rx_status = cpu_to_le32(DescOwn);
पूर्ण

अटल अंतरभूत व्योम rhine_skb_dma_nic_store(काष्ठा rhine_निजी *rp,
					   काष्ठा rhine_skb_dma *sd, पूर्णांक entry)
अणु
	rp->rx_skbuff_dma[entry] = sd->dma;
	rp->rx_skbuff[entry] = sd->skb;

	rp->rx_ring[entry].addr = cpu_to_le32(sd->dma);
	dma_wmb();
पूर्ण

अटल व्योम मुक्त_rbufs(काष्ठा net_device* dev);

अटल पूर्णांक alloc_rbufs(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	dma_addr_t next;
	पूर्णांक rc, i;

	rp->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);
	next = rp->rx_ring_dma;

	/* Init the ring entries */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		rp->rx_ring[i].rx_status = 0;
		rp->rx_ring[i].desc_length = cpu_to_le32(rp->rx_buf_sz);
		next += माप(काष्ठा rx_desc);
		rp->rx_ring[i].next_desc = cpu_to_le32(next);
		rp->rx_skbuff[i] = शून्य;
	पूर्ण
	/* Mark the last entry as wrapping the ring. */
	rp->rx_ring[i-1].next_desc = cpu_to_le32(rp->rx_ring_dma);

	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा rhine_skb_dma sd;

		rc = rhine_skb_dma_init(dev, &sd);
		अगर (rc < 0) अणु
			मुक्त_rbufs(dev);
			जाओ out;
		पूर्ण

		rhine_skb_dma_nic_store(rp, &sd, i);
	पूर्ण

	rhine_reset_rbufs(rp);
out:
	वापस rc;
पूर्ण

अटल व्योम मुक्त_rbufs(काष्ठा net_device* dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	काष्ठा device *hwdev = dev->dev.parent;
	पूर्णांक i;

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		rp->rx_ring[i].rx_status = 0;
		rp->rx_ring[i].addr = cpu_to_le32(0xBADF00D0); /* An invalid address. */
		अगर (rp->rx_skbuff[i]) अणु
			dma_unmap_single(hwdev,
					 rp->rx_skbuff_dma[i],
					 rp->rx_buf_sz, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(rp->rx_skbuff[i]);
		पूर्ण
		rp->rx_skbuff[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम alloc_tbufs(काष्ठा net_device* dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	dma_addr_t next;
	पूर्णांक i;

	rp->dirty_tx = rp->cur_tx = 0;
	next = rp->tx_ring_dma;
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		rp->tx_skbuff[i] = शून्य;
		rp->tx_ring[i].tx_status = 0;
		rp->tx_ring[i].desc_length = cpu_to_le32(TXDESC);
		next += माप(काष्ठा tx_desc);
		rp->tx_ring[i].next_desc = cpu_to_le32(next);
		अगर (rp->quirks & rqRhineI)
			rp->tx_buf[i] = &rp->tx_bufs[i * PKT_BUF_SZ];
	पूर्ण
	rp->tx_ring[i-1].next_desc = cpu_to_le32(rp->tx_ring_dma);

	netdev_reset_queue(dev);
पूर्ण

अटल व्योम मुक्त_tbufs(काष्ठा net_device* dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	काष्ठा device *hwdev = dev->dev.parent;
	पूर्णांक i;

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		rp->tx_ring[i].tx_status = 0;
		rp->tx_ring[i].desc_length = cpu_to_le32(TXDESC);
		rp->tx_ring[i].addr = cpu_to_le32(0xBADF00D0); /* An invalid address. */
		अगर (rp->tx_skbuff[i]) अणु
			अगर (rp->tx_skbuff_dma[i]) अणु
				dma_unmap_single(hwdev,
						 rp->tx_skbuff_dma[i],
						 rp->tx_skbuff[i]->len,
						 DMA_TO_DEVICE);
			पूर्ण
			dev_kमुक्त_skb(rp->tx_skbuff[i]);
		पूर्ण
		rp->tx_skbuff[i] = शून्य;
		rp->tx_buf[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम rhine_check_media(काष्ठा net_device *dev, अचिन्हित पूर्णांक init_media)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;

	अगर (!rp->mii_अगर.क्रमce_media)
		mii_check_media(&rp->mii_अगर, netअगर_msg_link(rp), init_media);

	अगर (rp->mii_अगर.full_duplex)
	    ioग_लिखो8(ioपढ़ो8(ioaddr + ChipCmd1) | Cmd1FDuplex,
		   ioaddr + ChipCmd1);
	अन्यथा
	    ioग_लिखो8(ioपढ़ो8(ioaddr + ChipCmd1) & ~Cmd1FDuplex,
		   ioaddr + ChipCmd1);

	netअगर_info(rp, link, dev, "force_media %d, carrier %d\n",
		   rp->mii_अगर.क्रमce_media, netअगर_carrier_ok(dev));
पूर्ण

/* Called after status of क्रमce_media possibly changed */
अटल व्योम rhine_set_carrier(काष्ठा mii_अगर_info *mii)
अणु
	काष्ठा net_device *dev = mii->dev;
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	अगर (mii->क्रमce_media) अणु
		/* स्वतःneg is off: Link is always assumed to be up */
		अगर (!netअगर_carrier_ok(dev))
			netअगर_carrier_on(dev);
	पूर्ण

	rhine_check_media(dev, 0);

	netअगर_info(rp, link, dev, "force_media %d, carrier %d\n",
		   mii->क्रमce_media, netअगर_carrier_ok(dev));
पूर्ण

/**
 * rhine_set_cam - set CAM multicast filters
 * @ioaddr: रेजिस्टर block of this Rhine
 * @idx: multicast CAM index [0..MCAM_SIZE-1]
 * @addr: multicast address (6 bytes)
 *
 * Load addresses पूर्णांकo multicast filters.
 */
अटल व्योम rhine_set_cam(व्योम __iomem *ioaddr, पूर्णांक idx, u8 *addr)
अणु
	पूर्णांक i;

	ioग_लिखो8(CAMC_CAMEN, ioaddr + CamCon);
	wmb();

	/* Paranoid -- idx out of range should never happen */
	idx &= (MCAM_SIZE - 1);

	ioग_लिखो8((u8) idx, ioaddr + CamAddr);

	क्रम (i = 0; i < 6; i++, addr++)
		ioग_लिखो8(*addr, ioaddr + MulticastFilter0 + i);
	udelay(10);
	wmb();

	ioग_लिखो8(CAMC_CAMWR | CAMC_CAMEN, ioaddr + CamCon);
	udelay(10);

	ioग_लिखो8(0, ioaddr + CamCon);
पूर्ण

/**
 * rhine_set_vlan_cam - set CAM VLAN filters
 * @ioaddr: रेजिस्टर block of this Rhine
 * @idx: VLAN CAM index [0..VCAM_SIZE-1]
 * @addr: VLAN ID (2 bytes)
 *
 * Load addresses पूर्णांकo VLAN filters.
 */
अटल व्योम rhine_set_vlan_cam(व्योम __iomem *ioaddr, पूर्णांक idx, u8 *addr)
अणु
	ioग_लिखो8(CAMC_CAMEN | CAMC_VCAMSL, ioaddr + CamCon);
	wmb();

	/* Paranoid -- idx out of range should never happen */
	idx &= (VCAM_SIZE - 1);

	ioग_लिखो8((u8) idx, ioaddr + CamAddr);

	ioग_लिखो16(*((u16 *) addr), ioaddr + MulticastFilter0 + 6);
	udelay(10);
	wmb();

	ioग_लिखो8(CAMC_CAMWR | CAMC_CAMEN, ioaddr + CamCon);
	udelay(10);

	ioग_लिखो8(0, ioaddr + CamCon);
पूर्ण

/**
 * rhine_set_cam_mask - set multicast CAM mask
 * @ioaddr: रेजिस्टर block of this Rhine
 * @mask: multicast CAM mask
 *
 * Mask sets multicast filters active/inactive.
 */
अटल व्योम rhine_set_cam_mask(व्योम __iomem *ioaddr, u32 mask)
अणु
	ioग_लिखो8(CAMC_CAMEN, ioaddr + CamCon);
	wmb();

	/* ग_लिखो mask */
	ioग_लिखो32(mask, ioaddr + CamMask);

	/* disable CAMEN */
	ioग_लिखो8(0, ioaddr + CamCon);
पूर्ण

/**
 * rhine_set_vlan_cam_mask - set VLAN CAM mask
 * @ioaddr: रेजिस्टर block of this Rhine
 * @mask: VLAN CAM mask
 *
 * Mask sets VLAN filters active/inactive.
 */
अटल व्योम rhine_set_vlan_cam_mask(व्योम __iomem *ioaddr, u32 mask)
अणु
	ioग_लिखो8(CAMC_CAMEN | CAMC_VCAMSL, ioaddr + CamCon);
	wmb();

	/* ग_लिखो mask */
	ioग_लिखो32(mask, ioaddr + CamMask);

	/* disable CAMEN */
	ioग_लिखो8(0, ioaddr + CamCon);
पूर्ण

/**
 * rhine_init_cam_filter - initialize CAM filters
 * @dev: network device
 *
 * Initialize (disable) hardware VLAN and multicast support on this
 * Rhine.
 */
अटल व्योम rhine_init_cam_filter(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;

	/* Disable all CAMs */
	rhine_set_vlan_cam_mask(ioaddr, 0);
	rhine_set_cam_mask(ioaddr, 0);

	/* disable hardware VLAN support */
	BYTE_REG_BITS_ON(TCR_PQEN, ioaddr + TxConfig);
	BYTE_REG_BITS_OFF(BCR1_VIDFR, ioaddr + PCIBusConfig1);
पूर्ण

/**
 * rhine_update_vcam - update VLAN CAM filters
 * @dev: rhine_निजी data of this Rhine
 *
 * Update VLAN CAM filters to match configuration change.
 */
अटल व्योम rhine_update_vcam(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;
	u16 vid;
	u32 vCAMmask = 0;	/* 32 vCAMs (6105M and better) */
	अचिन्हित पूर्णांक i = 0;

	क्रम_each_set_bit(vid, rp->active_vlans, VLAN_N_VID) अणु
		rhine_set_vlan_cam(ioaddr, i, (u8 *)&vid);
		vCAMmask |= 1 << i;
		अगर (++i >= VCAM_SIZE)
			अवरोध;
	पूर्ण
	rhine_set_vlan_cam_mask(ioaddr, vCAMmask);
पूर्ण

अटल पूर्णांक rhine_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	spin_lock_bh(&rp->lock);
	set_bit(vid, rp->active_vlans);
	rhine_update_vcam(dev);
	spin_unlock_bh(&rp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक rhine_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	spin_lock_bh(&rp->lock);
	clear_bit(vid, rp->active_vlans);
	rhine_update_vcam(dev);
	spin_unlock_bh(&rp->lock);
	वापस 0;
पूर्ण

अटल व्योम init_रेजिस्टरs(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		ioग_लिखो8(dev->dev_addr[i], ioaddr + StationAddr + i);

	/* Initialize other रेजिस्टरs. */
	ioग_लिखो16(0x0006, ioaddr + PCIBusConfig);	/* Tune configuration??? */
	/* Configure initial FIFO thresholds. */
	ioग_लिखो8(0x20, ioaddr + TxConfig);
	rp->tx_thresh = 0x20;
	rp->rx_thresh = 0x60;		/* Written in rhine_set_rx_mode(). */

	ioग_लिखो32(rp->rx_ring_dma, ioaddr + RxRingPtr);
	ioग_लिखो32(rp->tx_ring_dma, ioaddr + TxRingPtr);

	rhine_set_rx_mode(dev);

	अगर (rp->quirks & rqMgmt)
		rhine_init_cam_filter(dev);

	napi_enable(&rp->napi);

	ioग_लिखो16(RHINE_EVENT & 0xffff, ioaddr + IntrEnable);

	ioग_लिखो16(CmdStart | CmdTxOn | CmdRxOn | (Cmd1NoTxPoll << 8),
	       ioaddr + ChipCmd);
	rhine_check_media(dev, 1);
पूर्ण

/* Enable MII link status स्वतः-polling (required क्रम IntrLinkChange) */
अटल व्योम rhine_enable_linkmon(काष्ठा rhine_निजी *rp)
अणु
	व्योम __iomem *ioaddr = rp->base;

	ioग_लिखो8(0, ioaddr + MIICmd);
	ioग_लिखो8(MII_BMSR, ioaddr + MIIRegAddr);
	ioग_लिखो8(0x80, ioaddr + MIICmd);

	rhine_रुको_bit_high(rp, MIIRegAddr, 0x20);

	ioग_लिखो8(MII_BMSR | 0x40, ioaddr + MIIRegAddr);
पूर्ण

/* Disable MII link status स्वतः-polling (required क्रम MDIO access) */
अटल व्योम rhine_disable_linkmon(काष्ठा rhine_निजी *rp)
अणु
	व्योम __iomem *ioaddr = rp->base;

	ioग_लिखो8(0, ioaddr + MIICmd);

	अगर (rp->quirks & rqRhineI) अणु
		ioग_लिखो8(0x01, ioaddr + MIIRegAddr);	// MII_BMSR

		/* Can be called from ISR. Evil. */
		mdelay(1);

		/* 0x80 must be set immediately beक्रमe turning it off */
		ioग_लिखो8(0x80, ioaddr + MIICmd);

		rhine_रुको_bit_high(rp, MIIRegAddr, 0x20);

		/* Heh. Now clear 0x80 again. */
		ioग_लिखो8(0, ioaddr + MIICmd);
	पूर्ण
	अन्यथा
		rhine_रुको_bit_high(rp, MIIRegAddr, 0x80);
पूर्ण

/* Read and ग_लिखो over the MII Management Data I/O (MDIO) पूर्णांकerface. */

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक regnum)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;
	पूर्णांक result;

	rhine_disable_linkmon(rp);

	/* rhine_disable_linkmon alपढ़ोy cleared MIICmd */
	ioग_लिखो8(phy_id, ioaddr + MIIPhyAddr);
	ioग_लिखो8(regnum, ioaddr + MIIRegAddr);
	ioग_लिखो8(0x40, ioaddr + MIICmd);		/* Trigger पढ़ो */
	rhine_रुको_bit_low(rp, MIICmd, 0x40);
	result = ioपढ़ो16(ioaddr + MIIData);

	rhine_enable_linkmon(rp);
	वापस result;
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक regnum, पूर्णांक value)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;

	rhine_disable_linkmon(rp);

	/* rhine_disable_linkmon alपढ़ोy cleared MIICmd */
	ioग_लिखो8(phy_id, ioaddr + MIIPhyAddr);
	ioग_लिखो8(regnum, ioaddr + MIIRegAddr);
	ioग_लिखो16(value, ioaddr + MIIData);
	ioग_लिखो8(0x20, ioaddr + MIICmd);		/* Trigger ग_लिखो */
	rhine_रुको_bit_low(rp, MIICmd, 0x20);

	rhine_enable_linkmon(rp);
पूर्ण

अटल व्योम rhine_task_disable(काष्ठा rhine_निजी *rp)
अणु
	mutex_lock(&rp->task_lock);
	rp->task_enable = false;
	mutex_unlock(&rp->task_lock);

	cancel_work_sync(&rp->slow_event_task);
	cancel_work_sync(&rp->reset_task);
पूर्ण

अटल व्योम rhine_task_enable(काष्ठा rhine_निजी *rp)
अणु
	mutex_lock(&rp->task_lock);
	rp->task_enable = true;
	mutex_unlock(&rp->task_lock);
पूर्ण

अटल पूर्णांक rhine_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;
	पूर्णांक rc;

	rc = request_irq(rp->irq, rhine_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (rc)
		जाओ out;

	netअगर_dbg(rp, अगरup, dev, "%s() irq %d\n", __func__, rp->irq);

	rc = alloc_ring(dev);
	अगर (rc < 0)
		जाओ out_मुक्त_irq;

	rc = alloc_rbufs(dev);
	अगर (rc < 0)
		जाओ out_मुक्त_ring;

	alloc_tbufs(dev);
	enable_mmio(rp->pioaddr, rp->quirks);
	rhine_घातer_init(dev);
	rhine_chip_reset(dev);
	rhine_task_enable(rp);
	init_रेजिस्टरs(dev);

	netअगर_dbg(rp, अगरup, dev, "%s() Done - status %04x MII status: %04x\n",
		  __func__, ioपढ़ो16(ioaddr + ChipCmd),
		  mdio_पढ़ो(dev, rp->mii_अगर.phy_id, MII_BMSR));

	netअगर_start_queue(dev);

out:
	वापस rc;

out_मुक्त_ring:
	मुक्त_ring(dev);
out_मुक्त_irq:
	मुक्त_irq(rp->irq, dev);
	जाओ out;
पूर्ण

अटल व्योम rhine_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rhine_निजी *rp = container_of(work, काष्ठा rhine_निजी,
						reset_task);
	काष्ठा net_device *dev = rp->dev;

	mutex_lock(&rp->task_lock);

	अगर (!rp->task_enable)
		जाओ out_unlock;

	napi_disable(&rp->napi);
	netअगर_tx_disable(dev);
	spin_lock_bh(&rp->lock);

	/* clear all descriptors */
	मुक्त_tbufs(dev);
	alloc_tbufs(dev);

	rhine_reset_rbufs(rp);

	/* Reinitialize the hardware. */
	rhine_chip_reset(dev);
	init_रेजिस्टरs(dev);

	spin_unlock_bh(&rp->lock);

	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;
	netअगर_wake_queue(dev);

out_unlock:
	mutex_unlock(&rp->task_lock);
पूर्ण

अटल व्योम rhine_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;

	netdev_warn(dev, "Transmit timed out, status %04x, PHY status %04x, resetting...\n",
		    ioपढ़ो16(ioaddr + IntrStatus),
		    mdio_पढ़ो(dev, rp->mii_अगर.phy_id, MII_BMSR));

	schedule_work(&rp->reset_task);
पूर्ण

अटल अंतरभूत bool rhine_tx_queue_full(काष्ठा rhine_निजी *rp)
अणु
	वापस (rp->cur_tx - rp->dirty_tx) >= TX_QUEUE_LEN;
पूर्ण

अटल netdev_tx_t rhine_start_tx(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	काष्ठा device *hwdev = dev->dev.parent;
	व्योम __iomem *ioaddr = rp->base;
	अचिन्हित entry;

	/* Caution: the ग_लिखो order is important here, set the field
	   with the "ownership" bits last. */

	/* Calculate the next Tx descriptor entry. */
	entry = rp->cur_tx % TX_RING_SIZE;

	अगर (skb_padto(skb, ETH_ZLEN))
		वापस NETDEV_TX_OK;

	rp->tx_skbuff[entry] = skb;

	अगर ((rp->quirks & rqRhineI) &&
	    (((अचिन्हित दीर्घ)skb->data & 3) || skb_shinfo(skb)->nr_frags != 0 || skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		/* Must use alignment buffer. */
		अगर (skb->len > PKT_BUF_SZ) अणु
			/* packet too दीर्घ, drop it */
			dev_kमुक्त_skb_any(skb);
			rp->tx_skbuff[entry] = शून्य;
			dev->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण

		/* Padding is not copied and so must be reकरोne. */
		skb_copy_and_csum_dev(skb, rp->tx_buf[entry]);
		अगर (skb->len < ETH_ZLEN)
			स_रखो(rp->tx_buf[entry] + skb->len, 0,
			       ETH_ZLEN - skb->len);
		rp->tx_skbuff_dma[entry] = 0;
		rp->tx_ring[entry].addr = cpu_to_le32(rp->tx_bufs_dma +
						      (rp->tx_buf[entry] -
						       rp->tx_bufs));
	पूर्ण अन्यथा अणु
		rp->tx_skbuff_dma[entry] =
			dma_map_single(hwdev, skb->data, skb->len,
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(hwdev, rp->tx_skbuff_dma[entry])) अणु
			dev_kमुक्त_skb_any(skb);
			rp->tx_skbuff_dma[entry] = 0;
			dev->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण
		rp->tx_ring[entry].addr = cpu_to_le32(rp->tx_skbuff_dma[entry]);
	पूर्ण

	rp->tx_ring[entry].desc_length =
		cpu_to_le32(TXDESC | (skb->len >= ETH_ZLEN ? skb->len : ETH_ZLEN));

	अगर (unlikely(skb_vlan_tag_present(skb))) अणु
		u16 vid_pcp = skb_vlan_tag_get(skb);

		/* drop CFI/DEI bit, रेजिस्टर needs VID and PCP */
		vid_pcp = (vid_pcp & VLAN_VID_MASK) |
			  ((vid_pcp & VLAN_PRIO_MASK) >> 1);
		rp->tx_ring[entry].tx_status = cpu_to_le32((vid_pcp) << 16);
		/* request tagging */
		rp->tx_ring[entry].desc_length |= cpu_to_le32(0x020000);
	पूर्ण
	अन्यथा
		rp->tx_ring[entry].tx_status = 0;

	netdev_sent_queue(dev, skb->len);
	/* lock eth irq */
	dma_wmb();
	rp->tx_ring[entry].tx_status |= cpu_to_le32(DescOwn);
	wmb();

	rp->cur_tx++;
	/*
	 * Nobody wants cur_tx ग_लिखो to rot क्रम ages after the NIC will have
	 * seen the transmit request, especially as the transmit completion
	 * handler could miss it.
	 */
	smp_wmb();

	/* Non-x86 Toकरो: explicitly flush cache lines here. */

	अगर (skb_vlan_tag_present(skb))
		/* Tx queues are bits 7-0 (first Tx queue: bit 7) */
		BYTE_REG_BITS_ON(1 << 7, ioaddr + TQWake);

	/* Wake the potentially-idle transmit channel */
	ioग_लिखो8(ioपढ़ो8(ioaddr + ChipCmd1) | Cmd1TxDemand,
	       ioaddr + ChipCmd1);
	IOSYNC;

	/* dirty_tx may be pessimistically out-of-sync. See rhine_tx. */
	अगर (rhine_tx_queue_full(rp)) अणु
		netअगर_stop_queue(dev);
		smp_rmb();
		/* Rejuvenate. */
		अगर (!rhine_tx_queue_full(rp))
			netअगर_wake_queue(dev);
	पूर्ण

	netअगर_dbg(rp, tx_queued, dev, "Transmit frame #%d queued in slot %d\n",
		  rp->cur_tx - 1, entry);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम rhine_irq_disable(काष्ठा rhine_निजी *rp)
अणु
	ioग_लिखो16(0x0000, rp->base + IntrEnable);
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */
अटल irqवापस_t rhine_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	u32 status;
	पूर्णांक handled = 0;

	status = rhine_get_events(rp);

	netअगर_dbg(rp, पूर्णांकr, dev, "Interrupt, status %08x\n", status);

	अगर (status & RHINE_EVENT) अणु
		handled = 1;

		rhine_irq_disable(rp);
		napi_schedule(&rp->napi);
	पूर्ण

	अगर (status & ~(IntrLinkChange | IntrStatsMax | RHINE_EVENT_NAPI)) अणु
		netअगर_err(rp, पूर्णांकr, dev, "Something Wicked happened! %08x\n",
			  status);
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

/* This routine is logically part of the पूर्णांकerrupt handler, but isolated
   क्रम clarity. */
अटल व्योम rhine_tx(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	काष्ठा device *hwdev = dev->dev.parent;
	अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;
	अचिन्हित पूर्णांक dirty_tx = rp->dirty_tx;
	अचिन्हित पूर्णांक cur_tx;
	काष्ठा sk_buff *skb;

	/*
	 * The race with rhine_start_tx करोes not matter here as दीर्घ as the
	 * driver enक्रमces a value of cur_tx that was relevant when the
	 * packet was scheduled to the network chipset.
	 * Executive summary: smp_rmb() balances smp_wmb() in rhine_start_tx.
	 */
	smp_rmb();
	cur_tx = rp->cur_tx;
	/* find and cleanup dirty tx descriptors */
	जबतक (dirty_tx != cur_tx) अणु
		अचिन्हित पूर्णांक entry = dirty_tx % TX_RING_SIZE;
		u32 txstatus = le32_to_cpu(rp->tx_ring[entry].tx_status);

		netअगर_dbg(rp, tx_करोne, dev, "Tx scavenge %d status %08x\n",
			  entry, txstatus);
		अगर (txstatus & DescOwn)
			अवरोध;
		skb = rp->tx_skbuff[entry];
		अगर (txstatus & 0x8000) अणु
			netअगर_dbg(rp, tx_करोne, dev,
				  "Transmit error, Tx status %08x\n", txstatus);
			dev->stats.tx_errors++;
			अगर (txstatus & 0x0400)
				dev->stats.tx_carrier_errors++;
			अगर (txstatus & 0x0200)
				dev->stats.tx_winकरोw_errors++;
			अगर (txstatus & 0x0100)
				dev->stats.tx_पातed_errors++;
			अगर (txstatus & 0x0080)
				dev->stats.tx_heartbeat_errors++;
			अगर (((rp->quirks & rqRhineI) && txstatus & 0x0002) ||
			    (txstatus & 0x0800) || (txstatus & 0x1000)) अणु
				dev->stats.tx_fअगरo_errors++;
				rp->tx_ring[entry].tx_status = cpu_to_le32(DescOwn);
				अवरोध; /* Keep the skb - we try again */
			पूर्ण
			/* Transmitter restarted in 'abnormal' handler. */
		पूर्ण अन्यथा अणु
			अगर (rp->quirks & rqRhineI)
				dev->stats.collisions += (txstatus >> 3) & 0x0F;
			अन्यथा
				dev->stats.collisions += txstatus & 0x0F;
			netअगर_dbg(rp, tx_करोne, dev, "collisions: %1.1x:%1.1x\n",
				  (txstatus >> 3) & 0xF, txstatus & 0xF);

			u64_stats_update_begin(&rp->tx_stats.syncp);
			rp->tx_stats.bytes += skb->len;
			rp->tx_stats.packets++;
			u64_stats_update_end(&rp->tx_stats.syncp);
		पूर्ण
		/* Free the original skb. */
		अगर (rp->tx_skbuff_dma[entry]) अणु
			dma_unmap_single(hwdev,
					 rp->tx_skbuff_dma[entry],
					 skb->len,
					 DMA_TO_DEVICE);
		पूर्ण
		bytes_compl += skb->len;
		pkts_compl++;
		dev_consume_skb_any(skb);
		rp->tx_skbuff[entry] = शून्य;
		dirty_tx++;
	पूर्ण

	rp->dirty_tx = dirty_tx;
	/* Pity we can't rely on the nearby BQL completion implicit barrier. */
	smp_wmb();

	netdev_completed_queue(dev, pkts_compl, bytes_compl);

	/* cur_tx may be optimistically out-of-sync. See rhine_start_tx. */
	अगर (!rhine_tx_queue_full(rp) && netअगर_queue_stopped(dev)) अणु
		netअगर_wake_queue(dev);
		smp_rmb();
		/* Rejuvenate. */
		अगर (rhine_tx_queue_full(rp))
			netअगर_stop_queue(dev);
	पूर्ण
पूर्ण

/**
 * rhine_get_vlan_tci - extract TCI from Rx data buffer
 * @skb: poपूर्णांकer to sk_buff
 * @data_size: used data area of the buffer including CRC
 *
 * If hardware VLAN tag extraction is enabled and the chip indicates a 802.1Q
 * packet, the extracted 802.1Q header (2 bytes TPID + 2 bytes TCI) is 4-byte
 * aligned following the CRC.
 */
अटल अंतरभूत u16 rhine_get_vlan_tci(काष्ठा sk_buff *skb, पूर्णांक data_size)
अणु
	u8 *trailer = (u8 *)skb->data + ((data_size + 3) & ~3) + 2;
	वापस be16_to_cpup((__be16 *)trailer);
पूर्ण

अटल अंतरभूत व्योम rhine_rx_vlan_tag(काष्ठा sk_buff *skb, काष्ठा rx_desc *desc,
				     पूर्णांक data_size)
अणु
	dma_rmb();
	अगर (unlikely(desc->desc_length & cpu_to_le32(DescTag))) अणु
		u16 vlan_tci;

		vlan_tci = rhine_get_vlan_tci(skb, data_size);
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tci);
	पूर्ण
पूर्ण

/* Process up to limit frames from receive ring */
अटल पूर्णांक rhine_rx(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	काष्ठा device *hwdev = dev->dev.parent;
	पूर्णांक entry = rp->cur_rx % RX_RING_SIZE;
	पूर्णांक count;

	netअगर_dbg(rp, rx_status, dev, "%s(), entry %d status %08x\n", __func__,
		  entry, le32_to_cpu(rp->rx_ring[entry].rx_status));

	/* If EOP is set on the next entry, it's a new packet. Send it up. */
	क्रम (count = 0; count < limit; ++count) अणु
		काष्ठा rx_desc *desc = rp->rx_ring + entry;
		u32 desc_status = le32_to_cpu(desc->rx_status);
		पूर्णांक data_size = desc_status >> 16;

		अगर (desc_status & DescOwn)
			अवरोध;

		netअगर_dbg(rp, rx_status, dev, "%s() status %08x\n", __func__,
			  desc_status);

		अगर ((desc_status & (RxWholePkt | RxErr)) != RxWholePkt) अणु
			अगर ((desc_status & RxWholePkt) != RxWholePkt) अणु
				netdev_warn(dev,
	"Oversized Ethernet frame spanned multiple buffers, "
	"entry %#x length %d status %08x!\n",
					    entry, data_size,
					    desc_status);
				dev->stats.rx_length_errors++;
			पूर्ण अन्यथा अगर (desc_status & RxErr) अणु
				/* There was a error. */
				netअगर_dbg(rp, rx_err, dev,
					  "%s() Rx error %08x\n", __func__,
					  desc_status);
				dev->stats.rx_errors++;
				अगर (desc_status & 0x0030)
					dev->stats.rx_length_errors++;
				अगर (desc_status & 0x0048)
					dev->stats.rx_fअगरo_errors++;
				अगर (desc_status & 0x0004)
					dev->stats.rx_frame_errors++;
				अगर (desc_status & 0x0002) अणु
					/* this can also be updated outside the पूर्णांकerrupt handler */
					spin_lock(&rp->lock);
					dev->stats.rx_crc_errors++;
					spin_unlock(&rp->lock);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Length should omit the CRC */
			पूर्णांक pkt_len = data_size - 4;
			काष्ठा sk_buff *skb;

			/* Check अगर the packet is दीर्घ enough to accept without
			   copying to a minimally-sized skbuff. */
			अगर (pkt_len < rx_copyअवरोध) अणु
				skb = netdev_alloc_skb_ip_align(dev, pkt_len);
				अगर (unlikely(!skb))
					जाओ drop;

				dma_sync_single_क्रम_cpu(hwdev,
							rp->rx_skbuff_dma[entry],
							rp->rx_buf_sz,
							DMA_FROM_DEVICE);

				skb_copy_to_linear_data(skb,
						 rp->rx_skbuff[entry]->data,
						 pkt_len);

				dma_sync_single_क्रम_device(hwdev,
							   rp->rx_skbuff_dma[entry],
							   rp->rx_buf_sz,
							   DMA_FROM_DEVICE);
			पूर्ण अन्यथा अणु
				काष्ठा rhine_skb_dma sd;

				अगर (unlikely(rhine_skb_dma_init(dev, &sd) < 0))
					जाओ drop;

				skb = rp->rx_skbuff[entry];

				dma_unmap_single(hwdev,
						 rp->rx_skbuff_dma[entry],
						 rp->rx_buf_sz,
						 DMA_FROM_DEVICE);
				rhine_skb_dma_nic_store(rp, &sd, entry);
			पूर्ण

			skb_put(skb, pkt_len);

			rhine_rx_vlan_tag(skb, desc, data_size);

			skb->protocol = eth_type_trans(skb, dev);

			netअगर_receive_skb(skb);

			u64_stats_update_begin(&rp->rx_stats.syncp);
			rp->rx_stats.bytes += pkt_len;
			rp->rx_stats.packets++;
			u64_stats_update_end(&rp->rx_stats.syncp);
		पूर्ण
give_descriptor_to_nic:
		desc->rx_status = cpu_to_le32(DescOwn);
		entry = (++rp->cur_rx) % RX_RING_SIZE;
	पूर्ण

	वापस count;

drop:
	dev->stats.rx_dropped++;
	जाओ give_descriptor_to_nic;
पूर्ण

अटल व्योम rhine_restart_tx(काष्ठा net_device *dev) अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;
	पूर्णांक entry = rp->dirty_tx % TX_RING_SIZE;
	u32 पूर्णांकr_status;

	/*
	 * If new errors occurred, we need to sort them out beक्रमe करोing Tx.
	 * In that हाल the ISR will be back here RSN anyway.
	 */
	पूर्णांकr_status = rhine_get_events(rp);

	अगर ((पूर्णांकr_status & IntrTxErrSummary) == 0) अणु

		/* We know better than the chip where it should जारी. */
		ioग_लिखो32(rp->tx_ring_dma + entry * माप(काष्ठा tx_desc),
		       ioaddr + TxRingPtr);

		ioग_लिखो8(ioपढ़ो8(ioaddr + ChipCmd) | CmdTxOn,
		       ioaddr + ChipCmd);

		अगर (rp->tx_ring[entry].desc_length & cpu_to_le32(0x020000))
			/* Tx queues are bits 7-0 (first Tx queue: bit 7) */
			BYTE_REG_BITS_ON(1 << 7, ioaddr + TQWake);

		ioग_लिखो8(ioपढ़ो8(ioaddr + ChipCmd1) | Cmd1TxDemand,
		       ioaddr + ChipCmd1);
		IOSYNC;
	पूर्ण
	अन्यथा अणु
		/* This should never happen */
		netअगर_warn(rp, tx_err, dev, "another error occurred %08x\n",
			   पूर्णांकr_status);
	पूर्ण

पूर्ण

अटल व्योम rhine_slow_event_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rhine_निजी *rp =
		container_of(work, काष्ठा rhine_निजी, slow_event_task);
	काष्ठा net_device *dev = rp->dev;
	u32 पूर्णांकr_status;

	mutex_lock(&rp->task_lock);

	अगर (!rp->task_enable)
		जाओ out_unlock;

	पूर्णांकr_status = rhine_get_events(rp);
	rhine_ack_events(rp, पूर्णांकr_status & RHINE_EVENT_SLOW);

	अगर (पूर्णांकr_status & IntrLinkChange)
		rhine_check_media(dev, 0);

	अगर (पूर्णांकr_status & IntrPCIErr)
		netअगर_warn(rp, hw, dev, "PCI error\n");

	ioग_लिखो16(RHINE_EVENT & 0xffff, rp->base + IntrEnable);

out_unlock:
	mutex_unlock(&rp->task_lock);
पूर्ण

अटल व्योम
rhine_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	अचिन्हित पूर्णांक start;

	spin_lock_bh(&rp->lock);
	rhine_update_rx_crc_and_missed_errord(rp);
	spin_unlock_bh(&rp->lock);

	netdev_stats_to_stats64(stats, &dev->stats);

	करो अणु
		start = u64_stats_fetch_begin_irq(&rp->rx_stats.syncp);
		stats->rx_packets = rp->rx_stats.packets;
		stats->rx_bytes = rp->rx_stats.bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&rp->rx_stats.syncp, start));

	करो अणु
		start = u64_stats_fetch_begin_irq(&rp->tx_stats.syncp);
		stats->tx_packets = rp->tx_stats.packets;
		stats->tx_bytes = rp->tx_stats.bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&rp->tx_stats.syncp, start));
पूर्ण

अटल व्योम rhine_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;
	u32 mc_filter[2];	/* Multicast hash filter */
	u8 rx_mode = 0x0C;	/* Note: 0x02=accept runt, 0x01=accept errs */
	काष्ठा netdev_hw_addr *ha;

	अगर (dev->flags & IFF_PROMISC) अणु		/* Set promiscuous. */
		rx_mode = 0x1C;
		ioग_लिखो32(0xffffffff, ioaddr + MulticastFilter0);
		ioग_लिखो32(0xffffffff, ioaddr + MulticastFilter1);
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to match, or accept all multicasts. */
		ioग_लिखो32(0xffffffff, ioaddr + MulticastFilter0);
		ioग_लिखो32(0xffffffff, ioaddr + MulticastFilter1);
	पूर्ण अन्यथा अगर (rp->quirks & rqMgmt) अणु
		पूर्णांक i = 0;
		u32 mCAMmask = 0;	/* 32 mCAMs (6105M and better) */
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अगर (i == MCAM_SIZE)
				अवरोध;
			rhine_set_cam(ioaddr, i, ha->addr);
			mCAMmask |= 1 << i;
			i++;
		पूर्ण
		rhine_set_cam_mask(ioaddr, mCAMmask);
	पूर्ण अन्यथा अणु
		स_रखो(mc_filter, 0, माप(mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			पूर्णांक bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;

			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
		पूर्ण
		ioग_लिखो32(mc_filter[0], ioaddr + MulticastFilter0);
		ioग_लिखो32(mc_filter[1], ioaddr + MulticastFilter1);
	पूर्ण
	/* enable/disable VLAN receive filtering */
	अगर (rp->quirks & rqMgmt) अणु
		अगर (dev->flags & IFF_PROMISC)
			BYTE_REG_BITS_OFF(BCR1_VIDFR, ioaddr + PCIBusConfig1);
		अन्यथा
			BYTE_REG_BITS_ON(BCR1_VIDFR, ioaddr + PCIBusConfig1);
	पूर्ण
	BYTE_REG_BITS_ON(rx_mode, ioaddr + RxConfig);
पूर्ण

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा device *hwdev = dev->dev.parent;

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, dev_name(hwdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक netdev_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	mutex_lock(&rp->task_lock);
	mii_ethtool_get_link_ksettings(&rp->mii_अगर, cmd);
	mutex_unlock(&rp->task_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	पूर्णांक rc;

	mutex_lock(&rp->task_lock);
	rc = mii_ethtool_set_link_ksettings(&rp->mii_अगर, cmd);
	rhine_set_carrier(&rp->mii_अगर);
	mutex_unlock(&rp->task_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक netdev_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	वापस mii_nway_restart(&rp->mii_अगर);
पूर्ण

अटल u32 netdev_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	वापस mii_link_ok(&rp->mii_अगर);
पूर्ण

अटल u32 netdev_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	वापस rp->msg_enable;
पूर्ण

अटल व्योम netdev_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	rp->msg_enable = value;
पूर्ण

अटल व्योम rhine_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	अगर (!(rp->quirks & rqWOL))
		वापस;

	spin_lock_irq(&rp->lock);
	wol->supported = WAKE_PHY | WAKE_MAGIC |
			 WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;	/* Untested */
	wol->wolopts = rp->wolopts;
	spin_unlock_irq(&rp->lock);
पूर्ण

अटल पूर्णांक rhine_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	u32 support = WAKE_PHY | WAKE_MAGIC |
		      WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;	/* Untested */

	अगर (!(rp->quirks & rqWOL))
		वापस -EINVAL;

	अगर (wol->wolopts & ~support)
		वापस -EINVAL;

	spin_lock_irq(&rp->lock);
	rp->wolopts = wol->wolopts;
	spin_unlock_irq(&rp->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
	.nway_reset		= netdev_nway_reset,
	.get_link		= netdev_get_link,
	.get_msglevel		= netdev_get_msglevel,
	.set_msglevel		= netdev_set_msglevel,
	.get_wol		= rhine_get_wol,
	.set_wol		= rhine_set_wol,
	.get_link_ksettings	= netdev_get_link_ksettings,
	.set_link_ksettings	= netdev_set_link_ksettings,
पूर्ण;

अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	पूर्णांक rc;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	mutex_lock(&rp->task_lock);
	rc = generic_mii_ioctl(&rp->mii_अगर, अगर_mii(rq), cmd, शून्य);
	rhine_set_carrier(&rp->mii_अगर);
	mutex_unlock(&rp->task_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक rhine_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;

	rhine_task_disable(rp);
	napi_disable(&rp->napi);
	netअगर_stop_queue(dev);

	netअगर_dbg(rp, अगरकरोwn, dev, "Shutting down ethercard, status was %04x\n",
		  ioपढ़ो16(ioaddr + ChipCmd));

	/* Switch to loopback mode to aव्योम hardware races. */
	ioग_लिखो8(rp->tx_thresh | 0x02, ioaddr + TxConfig);

	rhine_irq_disable(rp);

	/* Stop the chip's Tx and Rx processes. */
	ioग_लिखो16(CmdStop, ioaddr + ChipCmd);

	मुक्त_irq(rp->irq, dev);
	मुक्त_rbufs(dev);
	मुक्त_tbufs(dev);
	मुक्त_ring(dev);

	वापस 0;
पूर्ण


अटल व्योम rhine_हटाओ_one_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);

	pci_iounmap(pdev, rp->base);
	pci_release_regions(pdev);

	मुक्त_netdev(dev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक rhine_हटाओ_one_platक्रमm(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);

	iounmap(rp->base);

	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल व्योम rhine_shutकरोwn_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा rhine_निजी *rp = netdev_priv(dev);
	व्योम __iomem *ioaddr = rp->base;

	अगर (!(rp->quirks & rqWOL))
		वापस; /* Nothing to करो क्रम non-WOL adapters */

	rhine_घातer_init(dev);

	/* Make sure we use pattern 0, 1 and not 4, 5 */
	अगर (rp->quirks & rq6patterns)
		ioग_लिखो8(0x04, ioaddr + WOLcgClr);

	spin_lock(&rp->lock);

	अगर (rp->wolopts & WAKE_MAGIC) अणु
		ioग_लिखो8(WOLmagic, ioaddr + WOLcrSet);
		/*
		 * Turn EEPROM-controlled wake-up back on -- some hardware may
		 * not cooperate otherwise.
		 */
		ioग_लिखो8(ioपढ़ो8(ioaddr + ConfigA) | 0x03, ioaddr + ConfigA);
	पूर्ण

	अगर (rp->wolopts & (WAKE_BCAST|WAKE_MCAST))
		ioग_लिखो8(WOLbmcast, ioaddr + WOLcgSet);

	अगर (rp->wolopts & WAKE_PHY)
		ioग_लिखो8(WOLlnkon | WOLlnkoff, ioaddr + WOLcrSet);

	अगर (rp->wolopts & WAKE_UCAST)
		ioग_लिखो8(WOLucast, ioaddr + WOLcrSet);

	अगर (rp->wolopts) अणु
		/* Enable legacy WOL (क्रम old motherboards) */
		ioग_लिखो8(0x01, ioaddr + PwcfgSet);
		ioग_लिखो8(ioपढ़ो8(ioaddr + StickyHW) | 0x04, ioaddr + StickyHW);
	पूर्ण

	spin_unlock(&rp->lock);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF && !aव्योम_D3) अणु
		ioग_लिखो8(ioपढ़ो8(ioaddr + StickyHW) | 0x03, ioaddr + StickyHW);

		pci_wake_from_d3(pdev, true);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rhine_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	rhine_task_disable(rp);
	rhine_irq_disable(rp);
	napi_disable(&rp->napi);

	netअगर_device_detach(dev);

	अगर (dev_is_pci(device))
		rhine_shutकरोwn_pci(to_pci_dev(device));

	वापस 0;
पूर्ण

अटल पूर्णांक rhine_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा rhine_निजी *rp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	enable_mmio(rp->pioaddr, rp->quirks);
	rhine_घातer_init(dev);
	मुक्त_tbufs(dev);
	alloc_tbufs(dev);
	rhine_reset_rbufs(rp);
	rhine_task_enable(rp);
	spin_lock_bh(&rp->lock);
	init_रेजिस्टरs(dev);
	spin_unlock_bh(&rp->lock);

	netअगर_device_attach(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rhine_pm_ops, rhine_suspend, rhine_resume);
#घोषणा RHINE_PM_OPS	(&rhine_pm_ops)

#अन्यथा

#घोषणा RHINE_PM_OPS	शून्य

#पूर्ण_अगर /* !CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver rhine_driver_pci = अणु
	.name		= DRV_NAME,
	.id_table	= rhine_pci_tbl,
	.probe		= rhine_init_one_pci,
	.हटाओ		= rhine_हटाओ_one_pci,
	.shutकरोwn	= rhine_shutकरोwn_pci,
	.driver.pm	= RHINE_PM_OPS,
पूर्ण;

अटल काष्ठा platक्रमm_driver rhine_driver_platक्रमm = अणु
	.probe		= rhine_init_one_platक्रमm,
	.हटाओ		= rhine_हटाओ_one_platक्रमm,
	.driver = अणु
		.name	= DRV_NAME,
		.of_match_table	= rhine_of_tbl,
		.pm		= RHINE_PM_OPS,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id rhine_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "EPIA-M",
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "Award Software International, Inc."),
			DMI_MATCH(DMI_BIOS_VERSION, "6.00 PG"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "KV7",
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies, LTD"),
			DMI_MATCH(DMI_BIOS_VERSION, "6.00 PG"),
		पूर्ण,
	पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल पूर्णांक __init rhine_init(व्योम)
अणु
	पूर्णांक ret_pci, ret_platक्रमm;

/* when a module, this is prपूर्णांकed whether or not devices are found in probe */
	अगर (dmi_check_प्रणाली(rhine_dmi_table)) अणु
		/* these BIOSes fail at PXE boot अगर chip is in D3 */
		aव्योम_D3 = true;
		pr_warn("Broken BIOS detected, avoid_D3 enabled\n");
	पूर्ण
	अन्यथा अगर (aव्योम_D3)
		pr_info("avoid_D3 set\n");

	ret_pci = pci_रेजिस्टर_driver(&rhine_driver_pci);
	ret_platक्रमm = platक्रमm_driver_रेजिस्टर(&rhine_driver_platक्रमm);
	अगर ((ret_pci < 0) && (ret_platक्रमm < 0))
		वापस ret_pci;

	वापस 0;
पूर्ण


अटल व्योम __निकास rhine_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rhine_driver_platक्रमm);
	pci_unरेजिस्टर_driver(&rhine_driver_pci);
पूर्ण


module_init(rhine_init);
module_निकास(rhine_cleanup);
