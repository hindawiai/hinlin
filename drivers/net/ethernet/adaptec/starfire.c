<शैली गुरु>
/* starfire.c: Linux device driver क्रम the Adaptec Starfire network adapter. */
/*
	Written 1998-2000 by Donald Becker.

	Current मुख्यtainer is Ion Badulescu <ionut ta badula tod org>. Please
	send all bug reports to me, and not to Donald Becker, as this code
	has been heavily modअगरied from Donald's original version.

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	The inक्रमmation below comes from Donald Becker's original driver:

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	Support and updates available at
	http://www.scyld.com/network/starfire.hपंचांगl
	[link no दीर्घer provides useful info -jgarzik]

*/

#घोषणा DRV_NAME	"starfire"

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/mm.h>
#समावेश <linux/firmware.h>
#समावेश <यंत्र/processor.h>		/* Processor type क्रम cache alignment. */
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

/*
 * The current frame processor firmware fails to checksum a fragment
 * of length 1. If and when this is fixed, the #घोषणा below can be हटाओd.
 */
#घोषणा HAS_BROKEN_FIRMWARE

/*
 * If using the broken firmware, data must be padded to the next 32-bit boundary.
 */
#अगर_घोषित HAS_BROKEN_FIRMWARE
#घोषणा PADDING_MASK 3
#पूर्ण_अगर

/*
 * Define this अगर using the driver with the zero-copy patch
 */
#घोषणा ZEROCOPY

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
#घोषणा VLAN_SUPPORT
#पूर्ण_अगर

/* The user-configurable values.
   These may be modअगरied when a driver module is loaded.*/

/* Used क्रम tuning पूर्णांकerrupt latency vs. overhead. */
अटल पूर्णांक पूर्णांकr_latency;
अटल पूर्णांक small_frames;

अटल पूर्णांक debug = 1;			/* 1 normal messages, 0 quiet .. 7 verbose. */
अटल पूर्णांक max_पूर्णांकerrupt_work = 20;
अटल पूर्णांक mtu;
/* Maximum number of multicast addresses to filter (vs. rx-all-multicast).
   The Starfire has a 512 element hash table based on the Ethernet CRC. */
अटल स्थिर पूर्णांक multicast_filter_limit = 512;
/* Whether to करो TCP/UDP checksums in hardware */
अटल पूर्णांक enable_hw_cksum = 1;

#घोषणा PKT_BUF_SZ	1536		/* Size of each temporary Rx buffer.*/
/*
 * Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
 * Setting to > 1518 effectively disables this feature.
 *
 * NOTE:
 * The ia64 करोesn't allow क्रम unaligned loads even of पूर्णांकegers being
 * misaligned on a 2 byte boundary. Thus always क्रमce copying of
 * packets as the starfire करोesn't allow क्रम misaligned DMAs ;-(
 * 23/10/2000 - Jes
 *
 * The Alpha and the Sparc करोn't like unaligned loads, either. On Sparc64,
 * at least, having unaligned frames leads to a rather serious perक्रमmance
 * penalty. -Ion
 */
#अगर defined(__ia64__) || defined(__alpha__) || defined(__sparc__)
अटल पूर्णांक rx_copyअवरोध = PKT_BUF_SZ;
#अन्यथा
अटल पूर्णांक rx_copyअवरोध /* = 0 */;
#पूर्ण_अगर

/* PCI DMA burst size -- on sparc64 we want to क्रमce it to 64 bytes, on the others the शेष of 128 is fine. */
#अगर_घोषित __sparc__
#घोषणा DMA_BURST_SIZE 64
#अन्यथा
#घोषणा DMA_BURST_SIZE 128
#पूर्ण_अगर

/* Operational parameters that are set at compile समय. */

/* The "native" ring sizes are either 256 or 2048.
   However in some modes a descriptor may be marked to wrap the ring earlier.
*/
#घोषणा RX_RING_SIZE	256
#घोषणा TX_RING_SIZE	32
/* The completion queues are fixed at 1024 entries i.e. 4K or 8KB. */
#घोषणा DONE_Q_SIZE	1024
/* All queues must be aligned on a 256-byte boundary */
#घोषणा QUEUE_ALIGN	256

#अगर RX_RING_SIZE > 256
#घोषणा RX_Q_ENTRIES Rx2048QEntries
#अन्यथा
#घोषणा RX_Q_ENTRIES Rx256QEntries
#पूर्ण_अगर

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT	(2 * HZ)

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
/* 64-bit dma_addr_t */
#घोषणा ADDR_64BITS	/* This chip uses 64 bit addresses. */
#घोषणा netdrv_addr_t __le64
#घोषणा cpu_to_dma(x) cpu_to_le64(x)
#घोषणा dma_to_cpu(x) le64_to_cpu(x)
#घोषणा RX_DESC_Q_ADDR_SIZE RxDescQAddr64bit
#घोषणा TX_DESC_Q_ADDR_SIZE TxDescQAddr64bit
#घोषणा RX_COMPL_Q_ADDR_SIZE RxComplQAddr64bit
#घोषणा TX_COMPL_Q_ADDR_SIZE TxComplQAddr64bit
#घोषणा RX_DESC_ADDR_SIZE RxDescAddr64bit
#अन्यथा  /* 32-bit dma_addr_t */
#घोषणा netdrv_addr_t __le32
#घोषणा cpu_to_dma(x) cpu_to_le32(x)
#घोषणा dma_to_cpu(x) le32_to_cpu(x)
#घोषणा RX_DESC_Q_ADDR_SIZE RxDescQAddr32bit
#घोषणा TX_DESC_Q_ADDR_SIZE TxDescQAddr32bit
#घोषणा RX_COMPL_Q_ADDR_SIZE RxComplQAddr32bit
#घोषणा TX_COMPL_Q_ADDR_SIZE TxComplQAddr32bit
#घोषणा RX_DESC_ADDR_SIZE RxDescAddr32bit
#पूर्ण_अगर

#घोषणा skb_first_frag_len(skb)	skb_headlen(skb)
#घोषणा skb_num_frags(skb) (skb_shinfo(skb)->nr_frags + 1)

/* Firmware names */
#घोषणा FIRMWARE_RX	"adaptec/starfire_rx.bin"
#घोषणा FIRMWARE_TX	"adaptec/starfire_tx.bin"

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("Adaptec Starfire Ethernet driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE_RX);
MODULE_FIRMWARE(FIRMWARE_TX);

module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
module_param(mtu, पूर्णांक, 0);
module_param(debug, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param(पूर्णांकr_latency, पूर्णांक, 0);
module_param(small_frames, पूर्णांक, 0);
module_param(enable_hw_cksum, पूर्णांक, 0);
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "Maximum events handled per interrupt");
MODULE_PARM_DESC(mtu, "MTU (all boards)");
MODULE_PARM_DESC(debug, "Debug level (0-6)");
MODULE_PARM_DESC(rx_copyअवरोध, "Copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(पूर्णांकr_latency, "Maximum interrupt latency, in microseconds");
MODULE_PARM_DESC(small_frames, "Maximum size of receive frames that bypass interrupt latency (0,64,128,256,512)");
MODULE_PARM_DESC(enable_hw_cksum, "Enable/disable hardware cksum support (0/1)");

/*
				Theory of Operation

I. Board Compatibility

This driver is क्रम the Adaptec 6915 "Starfire" 64 bit PCI Ethernet adapter.

II. Board-specअगरic settings

III. Driver operation

IIIa. Ring buffers

The Starfire hardware uses multiple fixed-size descriptor queues/rings.  The
ring sizes are set fixed by the hardware, but may optionally be wrapped
earlier by the END bit in the descriptor.
This driver uses that hardware queue size क्रम the Rx ring, where a large
number of entries has no ill effect beyond increases the potential backlog.
The Tx ring is wrapped with the END bit, since a large hardware Tx queue
disables the queue layer priority ordering and we have no mechanism to
utilize the hardware two-level priority queue.  When modअगरying the
RX/TX_RING_SIZE pay बंद attention to page sizes and the ring-empty warning
levels.

IIIb/c. Transmit/Receive Structure

See the Adaptec manual क्रम the many possible काष्ठाures, and options क्रम
each काष्ठाure.  There are far too many to करोcument all of them here.

For transmit this driver uses type 0/1 transmit descriptors (depending
on the 32/64 bitness of the architecture), and relies on स्वतःmatic
minimum-length padding.  It करोes not use the completion queue
consumer index, but instead checks क्रम non-zero status entries.

For receive this driver uses type 2/3 receive descriptors.  The driver
allocates full frame size skbuffs क्रम the Rx ring buffers, so all frames
should fit in a single descriptor.  The driver करोes not use the completion
queue consumer index, but instead checks क्रम non-zero status entries.

When an incoming frame is less than RX_COPYBREAK bytes दीर्घ, a fresh skbuff
is allocated and the frame is copied to the new skbuff.  When the incoming
frame is larger, the skbuff is passed directly up the protocol stack.
Buffers consumed this way are replaced by newly allocated skbuffs in a later
phase of receive.

A notable aspect of operation is that unaligned buffers are not permitted by
the Starfire hardware.  Thus the IP header at offset 14 in an ethernet frame
isn't दीर्घword aligned, which may cause problems on some machine
e.g. Alphas and IA64. For these architectures, the driver is क्रमced to copy
the frame पूर्णांकo a new skbuff unconditionally. Copied frames are put पूर्णांकo the
skbuff at an offset of "+2", thus 16-byte aligning the IP header.

IIId. Synchronization

The driver runs as two independent, single-thपढ़ोed flows of control.  One
is the send-packet routine, which enक्रमces single-thपढ़ोed use by the
dev->tbusy flag.  The other thपढ़ो is the पूर्णांकerrupt handler, which is single
thपढ़ोed by the hardware and पूर्णांकerrupt handling software.

The send packet thपढ़ो has partial control over the Tx ring and the netअगर_queue
status. If the number of मुक्त Tx slots in the ring falls below a certain number
(currently hardcoded to 4), it संकेतs the upper layer to stop the queue.

The पूर्णांकerrupt handler has exclusive control over the Rx ring and records stats
from the Tx ring.  After reaping the stats, it marks the Tx queue entry as
empty by incrementing the dirty_tx mark. Iff the netअगर_queue is stopped and the
number of मुक्त Tx slow is above the threshold, it संकेतs the upper layer to
restart the queue.

IV. Notes

IVb. References

The Adaptec Starfire manuals, available only from Adaptec.
http://www.scyld.com/expert/100mbps.hपंचांगl
http://www.scyld.com/expert/NWay.hपंचांगl

IVc. Errata

- StopOnPerr is broken, करोn't enable
- Hardware ethernet padding exposes अक्रमom data, perक्रमm software padding
  instead (unverअगरied -- works correctly क्रम all the hardware I have)

*/



क्रमागत chip_capability_flags अणुCanHaveMII=1, पूर्ण;

क्रमागत chipset अणु
	CH_6915 = 0,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id starfire_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ADAPTEC, 0x6915), CH_6915 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, starfire_pci_tbl);

/* A chip capabilities table, matching the CH_xxx entries in xxx_pci_tbl[] above. */
अटल स्थिर काष्ठा chip_info अणु
	स्थिर अक्षर *name;
	पूर्णांक drv_flags;
पूर्ण netdrv_tbl[] = अणु
	अणु "Adaptec Starfire 6915", CanHaveMII पूर्ण,
पूर्ण;


/* Offsets to the device रेजिस्टरs.
   Unlike software-only प्रणालीs, device drivers पूर्णांकeract with complex hardware.
   It's not useful to define symbolic names क्रम every रेजिस्टर bit in the
   device.  The name can only partially करोcument the semantics and make
   the driver दीर्घer and more dअगरficult to पढ़ो.
   In general, only the important configuration values or bits changed
   multiple बार should be defined symbolically.
*/
क्रमागत रेजिस्टर_offsets अणु
	PCIDeviceConfig=0x50040, GenCtrl=0x50070, IntrTimerCtrl=0x50074,
	IntrClear=0x50080, IntrStatus=0x50084, IntrEnable=0x50088,
	MIICtrl=0x52000, TxStationAddr=0x50120, EEPROMCtrl=0x51000,
	GPIOCtrl=0x5008C, TxDescCtrl=0x50090,
	TxRingPtr=0x50098, HiPriTxRingPtr=0x50094, /* Low and High priority. */
	TxRingHiAddr=0x5009C,		/* 64 bit address extension. */
	TxProducerIdx=0x500A0, TxConsumerIdx=0x500A4,
	TxThreshold=0x500B0,
	CompletionHiAddr=0x500B4, TxCompletionAddr=0x500B8,
	RxCompletionAddr=0x500BC, RxCompletionQ2Addr=0x500C0,
	CompletionQConsumerIdx=0x500C4, RxDMACtrl=0x500D0,
	RxDescQCtrl=0x500D4, RxDescQHiAddr=0x500DC, RxDescQAddr=0x500E0,
	RxDescQIdx=0x500E8, RxDMAStatus=0x500F0, RxFilterMode=0x500F4,
	TxMode=0x55000, VlanType=0x55064,
	PerfFilterTable=0x56000, HashTable=0x56100,
	TxGfpMem=0x58000, RxGfpMem=0x5a000,
पूर्ण;

/*
 * Bits in the पूर्णांकerrupt status/mask रेजिस्टरs.
 * Warning: setting Intr[Ab]NormalSummary in the IntrEnable रेजिस्टर
 * enables all the पूर्णांकerrupt sources that are or'ed पूर्णांकo those status bits.
 */
क्रमागत पूर्णांकr_status_bits अणु
	IntrLinkChange=0xf0000000, IntrStatsMax=0x08000000,
	IntrAbnormalSummary=0x02000000, IntrGeneralTimer=0x01000000,
	IntrSoftware=0x800000, IntrRxComplQ1Low=0x400000,
	IntrTxComplQLow=0x200000, IntrPCI=0x100000,
	IntrDMAErr=0x080000, IntrTxDataLow=0x040000,
	IntrRxComplQ2Low=0x020000, IntrRxDescQ1Low=0x010000,
	IntrNormalSummary=0x8000, IntrTxDone=0x4000,
	IntrTxDMADone=0x2000, IntrTxEmpty=0x1000,
	IntrEarlyRxQ2=0x0800, IntrEarlyRxQ1=0x0400,
	IntrRxQ2Done=0x0200, IntrRxQ1Done=0x0100,
	IntrRxGFPDead=0x80, IntrRxDescQ2Low=0x40,
	IntrNoTxCsum=0x20, IntrTxBadID=0x10,
	IntrHiPriTxBadID=0x08, IntrRxGfp=0x04,
	IntrTxGfp=0x02, IntrPCIPad=0x01,
	/* not quite bits */
	IntrRxDone=IntrRxQ2Done | IntrRxQ1Done,
	IntrRxEmpty=IntrRxDescQ1Low | IntrRxDescQ2Low,
	IntrNormalMask=0xff00, IntrAbnormalMask=0x3ff00fe,
पूर्ण;

/* Bits in the RxFilterMode रेजिस्टर. */
क्रमागत rx_mode_bits अणु
	AcceptBroadcast=0x04, AcceptAllMulticast=0x02, AcceptAll=0x01,
	AcceptMulticast=0x10, PerfectFilter=0x40, HashFilter=0x30,
	PerfectFilterVlan=0x80, MinVLANPrio=0xE000, VlanMode=0x0200,
	WakeupOnGFP=0x0800,
पूर्ण;

/* Bits in the TxMode रेजिस्टर */
क्रमागत tx_mode_bits अणु
	MiiSoftReset=0x8000, MIILoopback=0x4000,
	TxFlowEnable=0x0800, RxFlowEnable=0x0400,
	PadEnable=0x04, FullDuplex=0x02, HugeFrame=0x01,
पूर्ण;

/* Bits in the TxDescCtrl रेजिस्टर. */
क्रमागत tx_ctrl_bits अणु
	TxDescSpaceUnlim=0x00, TxDescSpace32=0x10, TxDescSpace64=0x20,
	TxDescSpace128=0x30, TxDescSpace256=0x40,
	TxDescType0=0x00, TxDescType1=0x01, TxDescType2=0x02,
	TxDescType3=0x03, TxDescType4=0x04,
	TxNoDMACompletion=0x08,
	TxDescQAddr64bit=0x80, TxDescQAddr32bit=0,
	TxHiPriFIFOThreshShअगरt=24, TxPadLenShअगरt=16,
	TxDMABurstSizeShअगरt=8,
पूर्ण;

/* Bits in the RxDescQCtrl रेजिस्टर. */
क्रमागत rx_ctrl_bits अणु
	RxBufferLenShअगरt=16, RxMinDescrThreshShअगरt=0,
	RxPrefetchMode=0x8000, RxVariableQ=0x2000,
	Rx2048QEntries=0x4000, Rx256QEntries=0,
	RxDescAddr64bit=0x1000, RxDescAddr32bit=0,
	RxDescQAddr64bit=0x0100, RxDescQAddr32bit=0,
	RxDescSpace4=0x000, RxDescSpace8=0x100,
	RxDescSpace16=0x200, RxDescSpace32=0x300,
	RxDescSpace64=0x400, RxDescSpace128=0x500,
	RxConsumerWrEn=0x80,
पूर्ण;

/* Bits in the RxDMACtrl रेजिस्टर. */
क्रमागत rx_dmactrl_bits अणु
	RxReportBadFrames=0x80000000, RxDMAShortFrames=0x40000000,
	RxDMABadFrames=0x20000000, RxDMACrcErrorFrames=0x10000000,
	RxDMAControlFrame=0x08000000, RxDMAPauseFrame=0x04000000,
	RxChecksumIgnore=0, RxChecksumRejectTCPUDP=0x02000000,
	RxChecksumRejectTCPOnly=0x01000000,
	RxCompletionQ2Enable=0x800000,
	RxDMAQ2Disable=0, RxDMAQ2FPOnly=0x100000,
	RxDMAQ2SmallPkt=0x200000, RxDMAQ2HighPrio=0x300000,
	RxDMAQ2NonIP=0x400000,
	RxUseBackupQueue=0x080000, RxDMACRC=0x040000,
	RxEarlyIntThreshShअगरt=12, RxHighPrioThreshShअगरt=8,
	RxBurstSizeShअगरt=0,
पूर्ण;

/* Bits in the RxCompletionAddr रेजिस्टर */
क्रमागत rx_compl_bits अणु
	RxComplQAddr64bit=0x80, RxComplQAddr32bit=0,
	RxComplProducerWrEn=0x40,
	RxComplType0=0x00, RxComplType1=0x10,
	RxComplType2=0x20, RxComplType3=0x30,
	RxComplThreshShअगरt=0,
पूर्ण;

/* Bits in the TxCompletionAddr रेजिस्टर */
क्रमागत tx_compl_bits अणु
	TxComplQAddr64bit=0x80, TxComplQAddr32bit=0,
	TxComplProducerWrEn=0x40,
	TxComplIntrStatus=0x20,
	CommonQueueMode=0x10,
	TxComplThreshShअगरt=0,
पूर्ण;

/* Bits in the GenCtrl रेजिस्टर */
क्रमागत gen_ctrl_bits अणु
	RxEnable=0x05, TxEnable=0x0a,
	RxGFPEnable=0x10, TxGFPEnable=0x20,
पूर्ण;

/* Bits in the IntrTimerCtrl रेजिस्टर */
क्रमागत पूर्णांकr_ctrl_bits अणु
	Timer10X=0x800, EnableIntrMasking=0x60, SmallFrameBypass=0x100,
	SmallFrame64=0, SmallFrame128=0x200, SmallFrame256=0x400, SmallFrame512=0x600,
	IntrLatencyMask=0x1f,
पूर्ण;

/* The Rx and Tx buffer descriptors. */
काष्ठा starfire_rx_desc अणु
	netdrv_addr_t rxaddr;
पूर्ण;
क्रमागत rx_desc_bits अणु
	RxDescValid=1, RxDescEndRing=2,
पूर्ण;

/* Completion queue entry. */
काष्ठा लघु_rx_करोne_desc अणु
	__le32 status;			/* Low 16 bits is length. */
पूर्ण;
काष्ठा basic_rx_करोne_desc अणु
	__le32 status;			/* Low 16 bits is length. */
	__le16 vlanid;
	__le16 status2;
पूर्ण;
काष्ठा csum_rx_करोne_desc अणु
	__le32 status;			/* Low 16 bits is length. */
	__le16 csum;			/* Partial checksum */
	__le16 status2;
पूर्ण;
काष्ठा full_rx_करोne_desc अणु
	__le32 status;			/* Low 16 bits is length. */
	__le16 status3;
	__le16 status2;
	__le16 vlanid;
	__le16 csum;			/* partial checksum */
	__le32 बारtamp;
पूर्ण;
/* XXX: this is ugly and I'm not sure it's worth the trouble -Ion */
#अगर_घोषित VLAN_SUPPORT
प्रकार काष्ठा full_rx_करोne_desc rx_करोne_desc;
#घोषणा RxComplType RxComplType3
#अन्यथा  /* not VLAN_SUPPORT */
प्रकार काष्ठा csum_rx_करोne_desc rx_करोne_desc;
#घोषणा RxComplType RxComplType2
#पूर्ण_अगर /* not VLAN_SUPPORT */

क्रमागत rx_करोne_bits अणु
	RxOK=0x20000000, RxFIFOErr=0x10000000, RxBufQ2=0x08000000,
पूर्ण;

/* Type 1 Tx descriptor. */
काष्ठा starfire_tx_desc_1 अणु
	__le32 status;			/* Upper bits are status, lower 16 length. */
	__le32 addr;
पूर्ण;

/* Type 2 Tx descriptor. */
काष्ठा starfire_tx_desc_2 अणु
	__le32 status;			/* Upper bits are status, lower 16 length. */
	__le32 reserved;
	__le64 addr;
पूर्ण;

#अगर_घोषित ADDR_64BITS
प्रकार काष्ठा starfire_tx_desc_2 starfire_tx_desc;
#घोषणा TX_DESC_TYPE TxDescType2
#अन्यथा  /* not ADDR_64BITS */
प्रकार काष्ठा starfire_tx_desc_1 starfire_tx_desc;
#घोषणा TX_DESC_TYPE TxDescType1
#पूर्ण_अगर /* not ADDR_64BITS */
#घोषणा TX_DESC_SPACING TxDescSpaceUnlim

क्रमागत tx_desc_bits अणु
	TxDescID=0xB0000000,
	TxCRCEn=0x01000000, TxDescIntr=0x08000000,
	TxRingWrap=0x04000000, TxCalTCP=0x02000000,
पूर्ण;
काष्ठा tx_करोne_desc अणु
	__le32 status;			/* बारtamp, index. */
#अगर 0
	__le32 पूर्णांकrstatus;		/* पूर्णांकerrupt status */
#पूर्ण_अगर
पूर्ण;

काष्ठा rx_ring_info अणु
	काष्ठा sk_buff *skb;
	dma_addr_t mapping;
पूर्ण;
काष्ठा tx_ring_info अणु
	काष्ठा sk_buff *skb;
	dma_addr_t mapping;
	अचिन्हित पूर्णांक used_slots;
पूर्ण;

#घोषणा PHY_CNT		2
काष्ठा netdev_निजी अणु
	/* Descriptor rings first क्रम alignment. */
	काष्ठा starfire_rx_desc *rx_ring;
	starfire_tx_desc *tx_ring;
	dma_addr_t rx_ring_dma;
	dma_addr_t tx_ring_dma;
	/* The addresses of rx/tx-in-place skbuffs. */
	काष्ठा rx_ring_info rx_info[RX_RING_SIZE];
	काष्ठा tx_ring_info tx_info[TX_RING_SIZE];
	/* Poपूर्णांकers to completion queues (full pages). */
	rx_करोne_desc *rx_करोne_q;
	dma_addr_t rx_करोne_q_dma;
	अचिन्हित पूर्णांक rx_करोne;
	काष्ठा tx_करोne_desc *tx_करोne_q;
	dma_addr_t tx_करोne_q_dma;
	अचिन्हित पूर्णांक tx_करोne;
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *dev;
	काष्ठा pci_dev *pci_dev;
#अगर_घोषित VLAN_SUPPORT
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
#पूर्ण_अगर
	व्योम *queue_mem;
	dma_addr_t queue_mem_dma;
	माप_प्रकार queue_mem_size;

	/* Frequently used values: keep some adjacent क्रम cache effect. */
	spinlock_t lock;
	अचिन्हित पूर्णांक cur_rx, dirty_rx;	/* Producer/consumer ring indices */
	अचिन्हित पूर्णांक cur_tx, dirty_tx, reap_tx;
	अचिन्हित पूर्णांक rx_buf_sz;		/* Based on MTU+slack. */
	/* These values keep track of the transceiver/media in use. */
	पूर्णांक speed100;			/* Set अगर speed == 100MBit. */
	u32 tx_mode;
	u32 पूर्णांकr_समयr_ctrl;
	u8 tx_threshold;
	/* MII transceiver section. */
	काष्ठा mii_अगर_info mii_अगर;		/* MII lib hooks/info */
	पूर्णांक phy_cnt;			/* MII device addresses. */
	अचिन्हित अक्षर phys[PHY_CNT];	/* MII device addresses. */
	व्योम __iomem *base;
पूर्ण;


अटल पूर्णांक	mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम	mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value);
अटल पूर्णांक	netdev_खोलो(काष्ठा net_device *dev);
अटल व्योम	check_duplex(काष्ठा net_device *dev);
अटल व्योम	tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम	init_ring(काष्ठा net_device *dev);
अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance);
अटल व्योम	netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status);
अटल पूर्णांक	__netdev_rx(काष्ठा net_device *dev, पूर्णांक *quota);
अटल पूर्णांक	netdev_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
अटल व्योम	refill_rx_ring(काष्ठा net_device *dev);
अटल व्योम	netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status);
अटल व्योम	set_rx_mode(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev);
अटल पूर्णांक	netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल पूर्णांक	netdev_बंद(काष्ठा net_device *dev);
अटल व्योम	netdev_media_change(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops ethtool_ops;


#अगर_घोषित VLAN_SUPPORT
अटल पूर्णांक netdev_vlan_rx_add_vid(काष्ठा net_device *dev,
				  __be16 proto, u16 vid)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	spin_lock(&np->lock);
	अगर (debug > 1)
		prपूर्णांकk("%s: Adding vlanid %d to vlan filter\n", dev->name, vid);
	set_bit(vid, np->active_vlans);
	set_rx_mode(dev);
	spin_unlock(&np->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_vlan_rx_समाप्त_vid(काष्ठा net_device *dev,
				   __be16 proto, u16 vid)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	spin_lock(&np->lock);
	अगर (debug > 1)
		prपूर्णांकk("%s: removing vlanid %d from vlan filter\n", dev->name, vid);
	clear_bit(vid, np->active_vlans);
	set_rx_mode(dev);
	spin_unlock(&np->lock);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* VLAN_SUPPORT */


अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= netdev_खोलो,
	.nकरो_stop		= netdev_बंद,
	.nकरो_start_xmit		= start_tx,
	.nकरो_tx_समयout		= tx_समयout,
	.nकरो_get_stats		= get_stats,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_करो_ioctl		= netdev_ioctl,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित VLAN_SUPPORT
	.nकरो_vlan_rx_add_vid	= netdev_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= netdev_vlan_rx_समाप्त_vid,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक starfire_init_one(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *d = &pdev->dev;
	काष्ठा netdev_निजी *np;
	पूर्णांक i, irq, chip_idx = ent->driver_data;
	काष्ठा net_device *dev;
	दीर्घ ioaddr;
	व्योम __iomem *base;
	पूर्णांक drv_flags, io_size;
	पूर्णांक boguscnt;

	अगर (pci_enable_device (pdev))
		वापस -EIO;

	ioaddr = pci_resource_start(pdev, 0);
	io_size = pci_resource_len(pdev, 0);
	अगर (!ioaddr || ((pci_resource_flags(pdev, 0) & IORESOURCE_MEM) == 0)) अणु
		dev_err(d, "no PCI MEM resources, aborting\n");
		वापस -ENODEV;
	पूर्ण

	dev = alloc_etherdev(माप(*np));
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);

	irq = pdev->irq;

	अगर (pci_request_regions (pdev, DRV_NAME)) अणु
		dev_err(d, "cannot reserve PCI resources, aborting\n");
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	base = ioremap(ioaddr, io_size);
	अगर (!base) अणु
		dev_err(d, "cannot remap %#x @ %#lx, aborting\n",
			io_size, ioaddr);
		जाओ err_out_मुक्त_res;
	पूर्ण

	pci_set_master(pdev);

	/* enable MWI -- it vastly improves Rx perक्रमmance on sparc64 */
	pci_try_set_mwi(pdev);

#अगर_घोषित ZEROCOPY
	/* Starfire can करो TCP/UDP checksumming */
	अगर (enable_hw_cksum)
		dev->features |= NETIF_F_IP_CSUM | NETIF_F_SG;
#पूर्ण_अगर /* ZEROCOPY */

#अगर_घोषित VLAN_SUPPORT
	dev->features |= NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_CTAG_FILTER;
#पूर्ण_अगर /* VLAN_RX_KILL_VID */
#अगर_घोषित ADDR_64BITS
	dev->features |= NETIF_F_HIGHDMA;
#पूर्ण_अगर /* ADDR_64BITS */

	/* Serial EEPROM पढ़ोs are hidden by the hardware. */
	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = पढ़ोb(base + EEPROMCtrl + 20 - i);

#अगर ! defined(final_version) /* Dump the EEPROM contents during development. */
	अगर (debug > 4)
		क्रम (i = 0; i < 0x20; i++)
			prपूर्णांकk("%2.2x%s",
			       (अचिन्हित पूर्णांक)पढ़ोb(base + EEPROMCtrl + i),
			       i % 16 != 15 ? " " : "\n");
#पूर्ण_अगर

	/* Issue soft reset */
	ग_लिखोl(MiiSoftReset, base + TxMode);
	udelay(1000);
	ग_लिखोl(0, base + TxMode);

	/* Reset the chip to erase previous misconfiguration. */
	ग_लिखोl(1, base + PCIDeviceConfig);
	boguscnt = 1000;
	जबतक (--boguscnt > 0) अणु
		udelay(10);
		अगर ((पढ़ोl(base + PCIDeviceConfig) & 1) == 0)
			अवरोध;
	पूर्ण
	अगर (boguscnt == 0)
		prपूर्णांकk("%s: chipset reset never completed!\n", dev->name);
	/* रुको a little दीर्घer */
	udelay(1000);

	np = netdev_priv(dev);
	np->dev = dev;
	np->base = base;
	spin_lock_init(&np->lock);
	pci_set_drvdata(pdev, dev);

	np->pci_dev = pdev;

	np->mii_अगर.dev = dev;
	np->mii_अगर.mdio_पढ़ो = mdio_पढ़ो;
	np->mii_अगर.mdio_ग_लिखो = mdio_ग_लिखो;
	np->mii_अगर.phy_id_mask = 0x1f;
	np->mii_अगर.reg_num_mask = 0x1f;

	drv_flags = netdrv_tbl[chip_idx].drv_flags;

	np->speed100 = 1;

	/* समयr resolution is 128 * 0.8us */
	np->पूर्णांकr_समयr_ctrl = (((पूर्णांकr_latency * 10) / 1024) & IntrLatencyMask) |
		Timer10X | EnableIntrMasking;

	अगर (small_frames > 0) अणु
		np->पूर्णांकr_समयr_ctrl |= SmallFrameBypass;
		चयन (small_frames) अणु
		हाल 1 ... 64:
			np->पूर्णांकr_समयr_ctrl |= SmallFrame64;
			अवरोध;
		हाल 65 ... 128:
			np->पूर्णांकr_समयr_ctrl |= SmallFrame128;
			अवरोध;
		हाल 129 ... 256:
			np->पूर्णांकr_समयr_ctrl |= SmallFrame256;
			अवरोध;
		शेष:
			np->पूर्णांकr_समयr_ctrl |= SmallFrame512;
			अगर (small_frames > 512)
				prपूर्णांकk("Adjusting small_frames down to 512\n");
			अवरोध;
		पूर्ण
	पूर्ण

	dev->netdev_ops = &netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	dev->ethtool_ops = &ethtool_ops;

	netअगर_napi_add(dev, &np->napi, netdev_poll, max_पूर्णांकerrupt_work);

	अगर (mtu)
		dev->mtu = mtu;

	अगर (रेजिस्टर_netdev(dev))
		जाओ err_out_cleardev;

	prपूर्णांकk(KERN_INFO "%s: %s at %p, %pM, IRQ %d.\n",
	       dev->name, netdrv_tbl[chip_idx].name, base,
	       dev->dev_addr, irq);

	अगर (drv_flags & CanHaveMII) अणु
		पूर्णांक phy, phy_idx = 0;
		पूर्णांक mii_status;
		क्रम (phy = 0; phy < 32 && phy_idx < PHY_CNT; phy++) अणु
			mdio_ग_लिखो(dev, phy, MII_BMCR, BMCR_RESET);
			msleep(100);
			boguscnt = 1000;
			जबतक (--boguscnt > 0)
				अगर ((mdio_पढ़ो(dev, phy, MII_BMCR) & BMCR_RESET) == 0)
					अवरोध;
			अगर (boguscnt == 0) अणु
				prपूर्णांकk("%s: PHY#%d reset never completed!\n", dev->name, phy);
				जारी;
			पूर्ण
			mii_status = mdio_पढ़ो(dev, phy, MII_BMSR);
			अगर (mii_status != 0) अणु
				np->phys[phy_idx++] = phy;
				np->mii_अगर.advertising = mdio_पढ़ो(dev, phy, MII_ADVERTISE);
				prपूर्णांकk(KERN_INFO "%s: MII PHY found at address %d, status "
					   "%#4.4x advertising %#4.4x.\n",
					   dev->name, phy, mii_status, np->mii_अगर.advertising);
				/* there can be only one PHY on-board */
				अवरोध;
			पूर्ण
		पूर्ण
		np->phy_cnt = phy_idx;
		अगर (np->phy_cnt > 0)
			np->mii_अगर.phy_id = np->phys[0];
		अन्यथा
			स_रखो(&np->mii_अगर, 0, माप(np->mii_अगर));
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: scatter-gather and hardware TCP cksumming %s.\n",
	       dev->name, enable_hw_cksum ? "enabled" : "disabled");
	वापस 0;

err_out_cleardev:
	iounmap(base);
err_out_मुक्त_res:
	pci_release_regions (pdev);
err_out_मुक्त_netdev:
	मुक्त_netdev(dev);
	वापस -ENODEV;
पूर्ण


/* Read the MII Management Data I/O (MDIO) पूर्णांकerfaces. */
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *mdio_addr = np->base + MIICtrl + (phy_id<<7) + (location<<2);
	पूर्णांक result, boguscnt=1000;
	/* ??? Should we add a busy-रुको here? */
	करो अणु
		result = पढ़ोl(mdio_addr);
	पूर्ण जबतक ((result & 0xC0000000) != 0x80000000 && --boguscnt > 0);
	अगर (boguscnt == 0)
		वापस 0;
	अगर ((result & 0xffff) == 0xffff)
		वापस 0;
	वापस result & 0xffff;
पूर्ण


अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *mdio_addr = np->base + MIICtrl + (phy_id<<7) + (location<<2);
	ग_लिखोl(value, mdio_addr);
	/* The busy-रुको will occur beक्रमe a पढ़ो. */
पूर्ण


अटल पूर्णांक netdev_खोलो(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा firmware *fw_rx, *fw_tx;
	स्थिर __be32 *fw_rx_data, *fw_tx_data;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	स्थिर पूर्णांक irq = np->pci_dev->irq;
	पूर्णांक i, retval;
	माप_प्रकार tx_size, rx_size;
	माप_प्रकार tx_करोne_q_size, rx_करोne_q_size, tx_ring_size, rx_ring_size;

	/* Do we ever need to reset the chip??? */

	retval = request_irq(irq, पूर्णांकr_handler, IRQF_SHARED, dev->name, dev);
	अगर (retval)
		वापस retval;

	/* Disable the Rx and Tx, and reset the chip. */
	ग_लिखोl(0, ioaddr + GenCtrl);
	ग_लिखोl(1, ioaddr + PCIDeviceConfig);
	अगर (debug > 1)
		prपूर्णांकk(KERN_DEBUG "%s: netdev_open() irq %d.\n",
		       dev->name, irq);

	/* Allocate the various queues. */
	अगर (!np->queue_mem) अणु
		tx_करोne_q_size = ((माप(काष्ठा tx_करोne_desc) * DONE_Q_SIZE + QUEUE_ALIGN - 1) / QUEUE_ALIGN) * QUEUE_ALIGN;
		rx_करोne_q_size = ((माप(rx_करोne_desc) * DONE_Q_SIZE + QUEUE_ALIGN - 1) / QUEUE_ALIGN) * QUEUE_ALIGN;
		tx_ring_size = ((माप(starfire_tx_desc) * TX_RING_SIZE + QUEUE_ALIGN - 1) / QUEUE_ALIGN) * QUEUE_ALIGN;
		rx_ring_size = माप(काष्ठा starfire_rx_desc) * RX_RING_SIZE;
		np->queue_mem_size = tx_करोne_q_size + rx_करोne_q_size + tx_ring_size + rx_ring_size;
		np->queue_mem = dma_alloc_coherent(&np->pci_dev->dev,
						   np->queue_mem_size,
						   &np->queue_mem_dma, GFP_ATOMIC);
		अगर (np->queue_mem == शून्य) अणु
			मुक्त_irq(irq, dev);
			वापस -ENOMEM;
		पूर्ण

		np->tx_करोne_q     = np->queue_mem;
		np->tx_करोne_q_dma = np->queue_mem_dma;
		np->rx_करोne_q     = (व्योम *) np->tx_करोne_q + tx_करोne_q_size;
		np->rx_करोne_q_dma = np->tx_करोne_q_dma + tx_करोne_q_size;
		np->tx_ring       = (व्योम *) np->rx_करोne_q + rx_करोne_q_size;
		np->tx_ring_dma   = np->rx_करोne_q_dma + rx_करोne_q_size;
		np->rx_ring       = (व्योम *) np->tx_ring + tx_ring_size;
		np->rx_ring_dma   = np->tx_ring_dma + tx_ring_size;
	पूर्ण

	/* Start with no carrier, it माला_लो adjusted later */
	netअगर_carrier_off(dev);
	init_ring(dev);
	/* Set the size of the Rx buffers. */
	ग_लिखोl((np->rx_buf_sz << RxBufferLenShअगरt) |
	       (0 << RxMinDescrThreshShअगरt) |
	       RxPrefetchMode | RxVariableQ |
	       RX_Q_ENTRIES |
	       RX_DESC_Q_ADDR_SIZE | RX_DESC_ADDR_SIZE |
	       RxDescSpace4,
	       ioaddr + RxDescQCtrl);

	/* Set up the Rx DMA controller. */
	ग_लिखोl(RxChecksumIgnore |
	       (0 << RxEarlyIntThreshShअगरt) |
	       (6 << RxHighPrioThreshShअगरt) |
	       ((DMA_BURST_SIZE / 32) << RxBurstSizeShअगरt),
	       ioaddr + RxDMACtrl);

	/* Set Tx descriptor */
	ग_लिखोl((2 << TxHiPriFIFOThreshShअगरt) |
	       (0 << TxPadLenShअगरt) |
	       ((DMA_BURST_SIZE / 32) << TxDMABurstSizeShअगरt) |
	       TX_DESC_Q_ADDR_SIZE |
	       TX_DESC_SPACING | TX_DESC_TYPE,
	       ioaddr + TxDescCtrl);

	ग_लिखोl( (np->queue_mem_dma >> 16) >> 16, ioaddr + RxDescQHiAddr);
	ग_लिखोl( (np->queue_mem_dma >> 16) >> 16, ioaddr + TxRingHiAddr);
	ग_लिखोl( (np->queue_mem_dma >> 16) >> 16, ioaddr + CompletionHiAddr);
	ग_लिखोl(np->rx_ring_dma, ioaddr + RxDescQAddr);
	ग_लिखोl(np->tx_ring_dma, ioaddr + TxRingPtr);

	ग_लिखोl(np->tx_करोne_q_dma, ioaddr + TxCompletionAddr);
	ग_लिखोl(np->rx_करोne_q_dma |
	       RxComplType |
	       (0 << RxComplThreshShअगरt),
	       ioaddr + RxCompletionAddr);

	अगर (debug > 1)
		prपूर्णांकk(KERN_DEBUG "%s: Filling in the station address.\n", dev->name);

	/* Fill both the Tx SA रेजिस्टर and the Rx perfect filter. */
	क्रम (i = 0; i < 6; i++)
		ग_लिखोb(dev->dev_addr[i], ioaddr + TxStationAddr + 5 - i);
	/* The first entry is special because it bypasses the VLAN filter.
	   Don't use it. */
	ग_लिखोw(0, ioaddr + PerfFilterTable);
	ग_लिखोw(0, ioaddr + PerfFilterTable + 4);
	ग_लिखोw(0, ioaddr + PerfFilterTable + 8);
	क्रम (i = 1; i < 16; i++) अणु
		__be16 *eaddrs = (__be16 *)dev->dev_addr;
		व्योम __iomem *setup_frm = ioaddr + PerfFilterTable + i * 16;
		ग_लिखोw(be16_to_cpu(eaddrs[2]), setup_frm); setup_frm += 4;
		ग_लिखोw(be16_to_cpu(eaddrs[1]), setup_frm); setup_frm += 4;
		ग_लिखोw(be16_to_cpu(eaddrs[0]), setup_frm); setup_frm += 8;
	पूर्ण

	/* Initialize other रेजिस्टरs. */
	/* Configure the PCI bus bursts and FIFO thresholds. */
	np->tx_mode = TxFlowEnable|RxFlowEnable|PadEnable;	/* modअगरied when link is up. */
	ग_लिखोl(MiiSoftReset | np->tx_mode, ioaddr + TxMode);
	udelay(1000);
	ग_लिखोl(np->tx_mode, ioaddr + TxMode);
	np->tx_threshold = 4;
	ग_लिखोl(np->tx_threshold, ioaddr + TxThreshold);

	ग_लिखोl(np->पूर्णांकr_समयr_ctrl, ioaddr + IntrTimerCtrl);

	napi_enable(&np->napi);

	netअगर_start_queue(dev);

	अगर (debug > 1)
		prपूर्णांकk(KERN_DEBUG "%s: Setting the Rx and Tx modes.\n", dev->name);
	set_rx_mode(dev);

	np->mii_अगर.advertising = mdio_पढ़ो(dev, np->phys[0], MII_ADVERTISE);
	check_duplex(dev);

	/* Enable GPIO पूर्णांकerrupts on link change */
	ग_लिखोl(0x0f00ff00, ioaddr + GPIOCtrl);

	/* Set the पूर्णांकerrupt mask */
	ग_लिखोl(IntrRxDone | IntrRxEmpty | IntrDMAErr |
	       IntrTxDMADone | IntrStatsMax | IntrLinkChange |
	       IntrRxGFPDead | IntrNoTxCsum | IntrTxBadID,
	       ioaddr + IntrEnable);
	/* Enable PCI पूर्णांकerrupts. */
	ग_लिखोl(0x00800000 | पढ़ोl(ioaddr + PCIDeviceConfig),
	       ioaddr + PCIDeviceConfig);

#अगर_घोषित VLAN_SUPPORT
	/* Set VLAN type to 802.1q */
	ग_लिखोl(ETH_P_8021Q, ioaddr + VlanType);
#पूर्ण_अगर /* VLAN_SUPPORT */

	retval = request_firmware(&fw_rx, FIRMWARE_RX, &np->pci_dev->dev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "starfire: Failed to load firmware \"%s\"\n",
		       FIRMWARE_RX);
		जाओ out_init;
	पूर्ण
	अगर (fw_rx->size % 4) अणु
		prपूर्णांकk(KERN_ERR "starfire: bogus length %zu in \"%s\"\n",
		       fw_rx->size, FIRMWARE_RX);
		retval = -EINVAL;
		जाओ out_rx;
	पूर्ण
	retval = request_firmware(&fw_tx, FIRMWARE_TX, &np->pci_dev->dev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "starfire: Failed to load firmware \"%s\"\n",
		       FIRMWARE_TX);
		जाओ out_rx;
	पूर्ण
	अगर (fw_tx->size % 4) अणु
		prपूर्णांकk(KERN_ERR "starfire: bogus length %zu in \"%s\"\n",
		       fw_tx->size, FIRMWARE_TX);
		retval = -EINVAL;
		जाओ out_tx;
	पूर्ण
	fw_rx_data = (स्थिर __be32 *)&fw_rx->data[0];
	fw_tx_data = (स्थिर __be32 *)&fw_tx->data[0];
	rx_size = fw_rx->size / 4;
	tx_size = fw_tx->size / 4;

	/* Load Rx/Tx firmware पूर्णांकo the frame processors */
	क्रम (i = 0; i < rx_size; i++)
		ग_लिखोl(be32_to_cpup(&fw_rx_data[i]), ioaddr + RxGfpMem + i * 4);
	क्रम (i = 0; i < tx_size; i++)
		ग_लिखोl(be32_to_cpup(&fw_tx_data[i]), ioaddr + TxGfpMem + i * 4);
	अगर (enable_hw_cksum)
		/* Enable the Rx and Tx units, and the Rx/Tx frame processors. */
		ग_लिखोl(TxEnable|TxGFPEnable|RxEnable|RxGFPEnable, ioaddr + GenCtrl);
	अन्यथा
		/* Enable the Rx and Tx units only. */
		ग_लिखोl(TxEnable|RxEnable, ioaddr + GenCtrl);

	अगर (debug > 1)
		prपूर्णांकk(KERN_DEBUG "%s: Done netdev_open().\n",
		       dev->name);

out_tx:
	release_firmware(fw_tx);
out_rx:
	release_firmware(fw_rx);
out_init:
	अगर (retval)
		netdev_बंद(dev);
	वापस retval;
पूर्ण


अटल व्योम check_duplex(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u16 reg0;
	पूर्णांक silly_count = 1000;

	mdio_ग_लिखो(dev, np->phys[0], MII_ADVERTISE, np->mii_अगर.advertising);
	mdio_ग_लिखो(dev, np->phys[0], MII_BMCR, BMCR_RESET);
	udelay(500);
	जबतक (--silly_count && mdio_पढ़ो(dev, np->phys[0], MII_BMCR) & BMCR_RESET)
		/* करो nothing */;
	अगर (!silly_count) अणु
		prपूर्णांकk("%s: MII reset failed!\n", dev->name);
		वापस;
	पूर्ण

	reg0 = mdio_पढ़ो(dev, np->phys[0], MII_BMCR);

	अगर (!np->mii_अगर.क्रमce_media) अणु
		reg0 |= BMCR_ANENABLE | BMCR_ANRESTART;
	पूर्ण अन्यथा अणु
		reg0 &= ~(BMCR_ANENABLE | BMCR_ANRESTART);
		अगर (np->speed100)
			reg0 |= BMCR_SPEED100;
		अगर (np->mii_अगर.full_duplex)
			reg0 |= BMCR_FULLDPLX;
		prपूर्णांकk(KERN_DEBUG "%s: Link forced to %sMbit %s-duplex\n",
		       dev->name,
		       np->speed100 ? "100" : "10",
		       np->mii_अगर.full_duplex ? "full" : "half");
	पूर्ण
	mdio_ग_लिखो(dev, np->phys[0], MII_BMCR, reg0);
पूर्ण


अटल व्योम tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	पूर्णांक old_debug;

	prपूर्णांकk(KERN_WARNING "%s: Transmit timed out, status %#8.8x, "
	       "resetting...\n", dev->name, (पूर्णांक) पढ़ोl(ioaddr + IntrStatus));

	/* Perhaps we should reinitialize the hardware here. */

	/*
	 * Stop and restart the पूर्णांकerface.
	 * Cheat and increase the debug level temporarily.
	 */
	old_debug = debug;
	debug = 2;
	netdev_बंद(dev);
	netdev_खोलो(dev);
	debug = old_debug;

	/* Trigger an immediate transmit demand. */

	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;
	netअगर_wake_queue(dev);
पूर्ण


/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल व्योम init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	np->cur_rx = np->cur_tx = np->reap_tx = 0;
	np->dirty_rx = np->dirty_tx = np->rx_करोne = np->tx_करोne = 0;

	np->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, np->rx_buf_sz);
		np->rx_info[i].skb = skb;
		अगर (skb == शून्य)
			अवरोध;
		np->rx_info[i].mapping = dma_map_single(&np->pci_dev->dev,
							skb->data,
							np->rx_buf_sz,
							DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&np->pci_dev->dev, np->rx_info[i].mapping)) अणु
			dev_kमुक्त_skb(skb);
			np->rx_info[i].skb = शून्य;
			अवरोध;
		पूर्ण
		/* Grrr, we cannot offset to correctly align the IP header. */
		np->rx_ring[i].rxaddr = cpu_to_dma(np->rx_info[i].mapping | RxDescValid);
	पूर्ण
	ग_लिखोw(i - 1, np->base + RxDescQIdx);
	np->dirty_rx = (अचिन्हित पूर्णांक)(i - RX_RING_SIZE);

	/* Clear the reमुख्यder of the Rx buffer ring. */
	क्रम (  ; i < RX_RING_SIZE; i++) अणु
		np->rx_ring[i].rxaddr = 0;
		np->rx_info[i].skb = शून्य;
		np->rx_info[i].mapping = 0;
	पूर्ण
	/* Mark the last entry as wrapping the ring. */
	np->rx_ring[RX_RING_SIZE - 1].rxaddr |= cpu_to_dma(RxDescEndRing);

	/* Clear the completion rings. */
	क्रम (i = 0; i < DONE_Q_SIZE; i++) अणु
		np->rx_करोne_q[i].status = 0;
		np->tx_करोne_q[i].status = 0;
	पूर्ण

	क्रम (i = 0; i < TX_RING_SIZE; i++)
		स_रखो(&np->tx_info[i], 0, माप(np->tx_info[i]));
पूर्ण


अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	अचिन्हित पूर्णांक entry;
	अचिन्हित पूर्णांक prev_tx;
	u32 status;
	पूर्णांक i, j;

	/*
	 * be cautious here, wrapping the queue has weird semantics
	 * and we may not have enough slots even when it seems we करो.
	 */
	अगर ((np->cur_tx - np->dirty_tx) + skb_num_frags(skb) * 2 > TX_RING_SIZE) अणु
		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

#अगर defined(ZEROCOPY) && defined(HAS_BROKEN_FIRMWARE)
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (skb_padto(skb, (skb->len + PADDING_MASK) & ~PADDING_MASK))
			वापस NETDEV_TX_OK;
	पूर्ण
#पूर्ण_अगर /* ZEROCOPY && HAS_BROKEN_FIRMWARE */

	prev_tx = np->cur_tx;
	entry = np->cur_tx % TX_RING_SIZE;
	क्रम (i = 0; i < skb_num_frags(skb); i++) अणु
		पूर्णांक wrap_ring = 0;
		status = TxDescID;

		अगर (i == 0) अणु
			np->tx_info[entry].skb = skb;
			status |= TxCRCEn;
			अगर (entry >= TX_RING_SIZE - skb_num_frags(skb)) अणु
				status |= TxRingWrap;
				wrap_ring = 1;
			पूर्ण
			अगर (np->reap_tx) अणु
				status |= TxDescIntr;
				np->reap_tx = 0;
			पूर्ण
			अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
				status |= TxCalTCP;
				dev->stats.tx_compressed++;
			पूर्ण
			status |= skb_first_frag_len(skb) | (skb_num_frags(skb) << 16);

			np->tx_info[entry].mapping =
				dma_map_single(&np->pci_dev->dev, skb->data,
					       skb_first_frag_len(skb),
					       DMA_TO_DEVICE);
		पूर्ण अन्यथा अणु
			स्थिर skb_frag_t *this_frag = &skb_shinfo(skb)->frags[i - 1];
			status |= skb_frag_size(this_frag);
			np->tx_info[entry].mapping =
				dma_map_single(&np->pci_dev->dev,
					       skb_frag_address(this_frag),
					       skb_frag_size(this_frag),
					       DMA_TO_DEVICE);
		पूर्ण
		अगर (dma_mapping_error(&np->pci_dev->dev, np->tx_info[entry].mapping)) अणु
			dev->stats.tx_dropped++;
			जाओ err_out;
		पूर्ण

		np->tx_ring[entry].addr = cpu_to_dma(np->tx_info[entry].mapping);
		np->tx_ring[entry].status = cpu_to_le32(status);
		अगर (debug > 3)
			prपूर्णांकk(KERN_DEBUG "%s: Tx #%d/#%d slot %d status %#8.8x.\n",
			       dev->name, np->cur_tx, np->dirty_tx,
			       entry, status);
		अगर (wrap_ring) अणु
			np->tx_info[entry].used_slots = TX_RING_SIZE - entry;
			np->cur_tx += np->tx_info[entry].used_slots;
			entry = 0;
		पूर्ण अन्यथा अणु
			np->tx_info[entry].used_slots = 1;
			np->cur_tx += np->tx_info[entry].used_slots;
			entry++;
		पूर्ण
		/* scavenge the tx descriptors twice per TX_RING_SIZE */
		अगर (np->cur_tx % (TX_RING_SIZE / 2) == 0)
			np->reap_tx = 1;
	पूर्ण

	/* Non-x86: explicitly flush descriptor cache lines here. */
	/* Ensure all descriptors are written back beक्रमe the transmit is
	   initiated. - Jes */
	wmb();

	/* Update the producer index. */
	ग_लिखोl(entry * (माप(starfire_tx_desc) / 8), np->base + TxProducerIdx);

	/* 4 is arbitrary, but should be ok */
	अगर ((np->cur_tx - np->dirty_tx) + 4 > TX_RING_SIZE)
		netअगर_stop_queue(dev);

	वापस NETDEV_TX_OK;

err_out:
	entry = prev_tx % TX_RING_SIZE;
	np->tx_info[entry].skb = शून्य;
	अगर (i > 0) अणु
		dma_unmap_single(&np->pci_dev->dev,
				 np->tx_info[entry].mapping,
				 skb_first_frag_len(skb), DMA_TO_DEVICE);
		np->tx_info[entry].mapping = 0;
		entry = (entry + np->tx_info[entry].used_slots) % TX_RING_SIZE;
		क्रम (j = 1; j < i; j++) अणु
			dma_unmap_single(&np->pci_dev->dev,
					 np->tx_info[entry].mapping,
					 skb_frag_size(&skb_shinfo(skb)->frags[j - 1]),
					 DMA_TO_DEVICE);
			entry++;
		पूर्ण
	पूर्ण
	dev_kमुक्त_skb_any(skb);
	np->cur_tx = prev_tx;
	वापस NETDEV_TX_OK;
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	पूर्णांक boguscnt = max_पूर्णांकerrupt_work;
	पूर्णांक consumer;
	पूर्णांक tx_status;
	पूर्णांक handled = 0;

	करो अणु
		u32 पूर्णांकr_status = पढ़ोl(ioaddr + IntrClear);

		अगर (debug > 4)
			prपूर्णांकk(KERN_DEBUG "%s: Interrupt status %#8.8x.\n",
			       dev->name, पूर्णांकr_status);

		अगर (पूर्णांकr_status == 0 || पूर्णांकr_status == (u32) -1)
			अवरोध;

		handled = 1;

		अगर (पूर्णांकr_status & (IntrRxDone | IntrRxEmpty)) अणु
			u32 enable;

			अगर (likely(napi_schedule_prep(&np->napi))) अणु
				__napi_schedule(&np->napi);
				enable = पढ़ोl(ioaddr + IntrEnable);
				enable &= ~(IntrRxDone | IntrRxEmpty);
				ग_लिखोl(enable, ioaddr + IntrEnable);
				/* flush PCI posting buffers */
				पढ़ोl(ioaddr + IntrEnable);
			पूर्ण अन्यथा अणु
				/* Paranoia check */
				enable = पढ़ोl(ioaddr + IntrEnable);
				अगर (enable & (IntrRxDone | IntrRxEmpty)) अणु
					prपूर्णांकk(KERN_INFO
					       "%s: interrupt while in poll!\n",
					       dev->name);
					enable &= ~(IntrRxDone | IntrRxEmpty);
					ग_लिखोl(enable, ioaddr + IntrEnable);
				पूर्ण
			पूर्ण
		पूर्ण

		/* Scavenge the skbuff list based on the Tx-करोne queue.
		   There are redundant checks here that may be cleaned up
		   after the driver has proven to be reliable. */
		consumer = पढ़ोl(ioaddr + TxConsumerIdx);
		अगर (debug > 3)
			prपूर्णांकk(KERN_DEBUG "%s: Tx Consumer index is %d.\n",
			       dev->name, consumer);

		जबतक ((tx_status = le32_to_cpu(np->tx_करोne_q[np->tx_करोne].status)) != 0) अणु
			अगर (debug > 3)
				prपूर्णांकk(KERN_DEBUG "%s: Tx completion #%d entry %d is %#8.8x.\n",
				       dev->name, np->dirty_tx, np->tx_करोne, tx_status);
			अगर ((tx_status & 0xe0000000) == 0xa0000000) अणु
				dev->stats.tx_packets++;
			पूर्ण अन्यथा अगर ((tx_status & 0xe0000000) == 0x80000000) अणु
				u16 entry = (tx_status & 0x7fff) / माप(starfire_tx_desc);
				काष्ठा sk_buff *skb = np->tx_info[entry].skb;
				np->tx_info[entry].skb = शून्य;
				dma_unmap_single(&np->pci_dev->dev,
						 np->tx_info[entry].mapping,
						 skb_first_frag_len(skb),
						 DMA_TO_DEVICE);
				np->tx_info[entry].mapping = 0;
				np->dirty_tx += np->tx_info[entry].used_slots;
				entry = (entry + np->tx_info[entry].used_slots) % TX_RING_SIZE;
				अणु
					पूर्णांक i;
					क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
						dma_unmap_single(&np->pci_dev->dev,
								 np->tx_info[entry].mapping,
								 skb_frag_size(&skb_shinfo(skb)->frags[i]),
								 DMA_TO_DEVICE);
						np->dirty_tx++;
						entry++;
					पूर्ण
				पूर्ण

				dev_consume_skb_irq(skb);
			पूर्ण
			np->tx_करोne_q[np->tx_करोne].status = 0;
			np->tx_करोne = (np->tx_करोne + 1) % DONE_Q_SIZE;
		पूर्ण
		ग_लिखोw(np->tx_करोne, ioaddr + CompletionQConsumerIdx + 2);

		अगर (netअगर_queue_stopped(dev) &&
		    (np->cur_tx - np->dirty_tx + 4 < TX_RING_SIZE)) अणु
			/* The ring is no दीर्घer full, wake the queue. */
			netअगर_wake_queue(dev);
		पूर्ण

		/* Stats overflow */
		अगर (पूर्णांकr_status & IntrStatsMax)
			get_stats(dev);

		/* Media change पूर्णांकerrupt. */
		अगर (पूर्णांकr_status & IntrLinkChange)
			netdev_media_change(dev);

		/* Abnormal error summary/uncommon events handlers. */
		अगर (पूर्णांकr_status & IntrAbnormalSummary)
			netdev_error(dev, पूर्णांकr_status);

		अगर (--boguscnt < 0) अणु
			अगर (debug > 1)
				prपूर्णांकk(KERN_WARNING "%s: Too much work at interrupt, "
				       "status=%#8.8x.\n",
				       dev->name, पूर्णांकr_status);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	अगर (debug > 4)
		prपूर्णांकk(KERN_DEBUG "%s: exiting interrupt, status=%#8.8x.\n",
		       dev->name, (पूर्णांक) पढ़ोl(ioaddr + IntrStatus));
	वापस IRQ_RETVAL(handled);
पूर्ण


/*
 * This routine is logically part of the पूर्णांकerrupt/poll handler, but separated
 * क्रम clarity and better रेजिस्टर allocation.
 */
अटल पूर्णांक __netdev_rx(काष्ठा net_device *dev, पूर्णांक *quota)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u32 desc_status;
	पूर्णांक retcode = 0;

	/* If EOP is set on the next entry, it's a new packet. Send it up. */
	जबतक ((desc_status = le32_to_cpu(np->rx_करोne_q[np->rx_करोne].status)) != 0) अणु
		काष्ठा sk_buff *skb;
		u16 pkt_len;
		पूर्णांक entry;
		rx_करोne_desc *desc = &np->rx_करोne_q[np->rx_करोne];

		अगर (debug > 4)
			prपूर्णांकk(KERN_DEBUG "  netdev_rx() status of %d was %#8.8x.\n", np->rx_करोne, desc_status);
		अगर (!(desc_status & RxOK)) अणु
			/* There was an error. */
			अगर (debug > 2)
				prपूर्णांकk(KERN_DEBUG "  netdev_rx() Rx error was %#8.8x.\n", desc_status);
			dev->stats.rx_errors++;
			अगर (desc_status & RxFIFOErr)
				dev->stats.rx_fअगरo_errors++;
			जाओ next_rx;
		पूर्ण

		अगर (*quota <= 0) अणु	/* out of rx quota */
			retcode = 1;
			जाओ out;
		पूर्ण
		(*quota)--;

		pkt_len = desc_status;	/* Implicitly Truncate */
		entry = (desc_status >> 16) & 0x7ff;

		अगर (debug > 4)
			prपूर्णांकk(KERN_DEBUG "  netdev_rx() normal Rx pkt length %d, quota %d.\n", pkt_len, *quota);
		/* Check अगर the packet is दीर्घ enough to accept without copying
		   to a minimally-sized skbuff. */
		अगर (pkt_len < rx_copyअवरोध &&
		    (skb = netdev_alloc_skb(dev, pkt_len + 2)) != शून्य) अणु
			skb_reserve(skb, 2);	/* 16 byte align the IP header */
			dma_sync_single_क्रम_cpu(&np->pci_dev->dev,
						np->rx_info[entry].mapping,
						pkt_len, DMA_FROM_DEVICE);
			skb_copy_to_linear_data(skb, np->rx_info[entry].skb->data, pkt_len);
			dma_sync_single_क्रम_device(&np->pci_dev->dev,
						   np->rx_info[entry].mapping,
						   pkt_len, DMA_FROM_DEVICE);
			skb_put(skb, pkt_len);
		पूर्ण अन्यथा अणु
			dma_unmap_single(&np->pci_dev->dev,
					 np->rx_info[entry].mapping,
					 np->rx_buf_sz, DMA_FROM_DEVICE);
			skb = np->rx_info[entry].skb;
			skb_put(skb, pkt_len);
			np->rx_info[entry].skb = शून्य;
			np->rx_info[entry].mapping = 0;
		पूर्ण
#अगर_अघोषित final_version			/* Remove after testing. */
		/* You will want this info क्रम the initial debug. */
		अगर (debug > 5) अणु
			prपूर्णांकk(KERN_DEBUG "  Rx data %pM %pM %2.2x%2.2x.\n",
			       skb->data, skb->data + 6,
			       skb->data[12], skb->data[13]);
		पूर्ण
#पूर्ण_अगर

		skb->protocol = eth_type_trans(skb, dev);
#अगर_घोषित VLAN_SUPPORT
		अगर (debug > 4)
			prपूर्णांकk(KERN_DEBUG "  netdev_rx() status2 of %d was %#4.4x.\n", np->rx_करोne, le16_to_cpu(desc->status2));
#पूर्ण_अगर
		अगर (le16_to_cpu(desc->status2) & 0x0100) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			dev->stats.rx_compressed++;
		पूर्ण
		/*
		 * This feature करोesn't seem to be working, at least
		 * with the two firmware versions I have. If the GFP sees
		 * an IP fragment, it either ignores it completely, or reports
		 * "bad checksum" on it.
		 *
		 * Maybe I missed something -- corrections are welcome.
		 * Until then, the prपूर्णांकk stays. :-) -Ion
		 */
		अन्यथा अगर (le16_to_cpu(desc->status2) & 0x0040) अणु
			skb->ip_summed = CHECKSUM_COMPLETE;
			skb->csum = le16_to_cpu(desc->csum);
			prपूर्णांकk(KERN_DEBUG "%s: checksum_hw, status2 = %#x\n", dev->name, le16_to_cpu(desc->status2));
		पूर्ण
#अगर_घोषित VLAN_SUPPORT
		अगर (le16_to_cpu(desc->status2) & 0x0200) अणु
			u16 vlid = le16_to_cpu(desc->vlanid);

			अगर (debug > 4) अणु
				prपूर्णांकk(KERN_DEBUG "  netdev_rx() vlanid = %d\n",
				       vlid);
			पूर्ण
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlid);
		पूर्ण
#पूर्ण_अगर /* VLAN_SUPPORT */
		netअगर_receive_skb(skb);
		dev->stats.rx_packets++;

	next_rx:
		np->cur_rx++;
		desc->status = 0;
		np->rx_करोne = (np->rx_करोne + 1) % DONE_Q_SIZE;
	पूर्ण

	अगर (*quota == 0) अणु	/* out of rx quota */
		retcode = 1;
		जाओ out;
	पूर्ण
	ग_लिखोw(np->rx_करोne, np->base + CompletionQConsumerIdx);

 out:
	refill_rx_ring(dev);
	अगर (debug > 5)
		prपूर्णांकk(KERN_DEBUG "  exiting netdev_rx(): %d, status of %d was %#8.8x.\n",
		       retcode, np->rx_करोne, desc_status);
	वापस retcode;
पूर्ण

अटल पूर्णांक netdev_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा netdev_निजी *np = container_of(napi, काष्ठा netdev_निजी, napi);
	काष्ठा net_device *dev = np->dev;
	u32 पूर्णांकr_status;
	व्योम __iomem *ioaddr = np->base;
	पूर्णांक quota = budget;

	करो अणु
		ग_लिखोl(IntrRxDone | IntrRxEmpty, ioaddr + IntrClear);

		अगर (__netdev_rx(dev, &quota))
			जाओ out;

		पूर्णांकr_status = पढ़ोl(ioaddr + IntrStatus);
	पूर्ण जबतक (पूर्णांकr_status & (IntrRxDone | IntrRxEmpty));

	napi_complete(napi);
	पूर्णांकr_status = पढ़ोl(ioaddr + IntrEnable);
	पूर्णांकr_status |= IntrRxDone | IntrRxEmpty;
	ग_लिखोl(पूर्णांकr_status, ioaddr + IntrEnable);

 out:
	अगर (debug > 5)
		prपूर्णांकk(KERN_DEBUG "  exiting netdev_poll(): %d.\n",
		       budget - quota);

	/* Restart Rx engine अगर stopped. */
	वापस budget - quota;
पूर्ण

अटल व्योम refill_rx_ring(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक entry = -1;

	/* Refill the Rx ring buffers. */
	क्रम (; np->cur_rx - np->dirty_rx > 0; np->dirty_rx++) अणु
		entry = np->dirty_rx % RX_RING_SIZE;
		अगर (np->rx_info[entry].skb == शून्य) अणु
			skb = netdev_alloc_skb(dev, np->rx_buf_sz);
			np->rx_info[entry].skb = skb;
			अगर (skb == शून्य)
				अवरोध;	/* Better luck next round. */
			np->rx_info[entry].mapping =
				dma_map_single(&np->pci_dev->dev, skb->data,
					       np->rx_buf_sz, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&np->pci_dev->dev, np->rx_info[entry].mapping)) अणु
				dev_kमुक्त_skb(skb);
				np->rx_info[entry].skb = शून्य;
				अवरोध;
			पूर्ण
			np->rx_ring[entry].rxaddr =
				cpu_to_dma(np->rx_info[entry].mapping | RxDescValid);
		पूर्ण
		अगर (entry == RX_RING_SIZE - 1)
			np->rx_ring[entry].rxaddr |= cpu_to_dma(RxDescEndRing);
	पूर्ण
	अगर (entry >= 0)
		ग_लिखोw(entry, np->base + RxDescQIdx);
पूर्ण


अटल व्योम netdev_media_change(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	u16 reg0, reg1, reg4, reg5;
	u32 new_tx_mode;
	u32 new_पूर्णांकr_समयr_ctrl;

	/* reset status first */
	mdio_पढ़ो(dev, np->phys[0], MII_BMCR);
	mdio_पढ़ो(dev, np->phys[0], MII_BMSR);

	reg0 = mdio_पढ़ो(dev, np->phys[0], MII_BMCR);
	reg1 = mdio_पढ़ो(dev, np->phys[0], MII_BMSR);

	अगर (reg1 & BMSR_LSTATUS) अणु
		/* link is up */
		अगर (reg0 & BMCR_ANENABLE) अणु
			/* स्वतःnegotiation is enabled */
			reg4 = mdio_पढ़ो(dev, np->phys[0], MII_ADVERTISE);
			reg5 = mdio_पढ़ो(dev, np->phys[0], MII_LPA);
			अगर (reg4 & ADVERTISE_100FULL && reg5 & LPA_100FULL) अणु
				np->speed100 = 1;
				np->mii_अगर.full_duplex = 1;
			पूर्ण अन्यथा अगर (reg4 & ADVERTISE_100HALF && reg5 & LPA_100HALF) अणु
				np->speed100 = 1;
				np->mii_अगर.full_duplex = 0;
			पूर्ण अन्यथा अगर (reg4 & ADVERTISE_10FULL && reg5 & LPA_10FULL) अणु
				np->speed100 = 0;
				np->mii_अगर.full_duplex = 1;
			पूर्ण अन्यथा अणु
				np->speed100 = 0;
				np->mii_अगर.full_duplex = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* स्वतःnegotiation is disabled */
			अगर (reg0 & BMCR_SPEED100)
				np->speed100 = 1;
			अन्यथा
				np->speed100 = 0;
			अगर (reg0 & BMCR_FULLDPLX)
				np->mii_अगर.full_duplex = 1;
			अन्यथा
				np->mii_अगर.full_duplex = 0;
		पूर्ण
		netअगर_carrier_on(dev);
		prपूर्णांकk(KERN_DEBUG "%s: Link is up, running at %sMbit %s-duplex\n",
		       dev->name,
		       np->speed100 ? "100" : "10",
		       np->mii_अगर.full_duplex ? "full" : "half");

		new_tx_mode = np->tx_mode & ~FullDuplex;	/* duplex setting */
		अगर (np->mii_अगर.full_duplex)
			new_tx_mode |= FullDuplex;
		अगर (np->tx_mode != new_tx_mode) अणु
			np->tx_mode = new_tx_mode;
			ग_लिखोl(np->tx_mode | MiiSoftReset, ioaddr + TxMode);
			udelay(1000);
			ग_लिखोl(np->tx_mode, ioaddr + TxMode);
		पूर्ण

		new_पूर्णांकr_समयr_ctrl = np->पूर्णांकr_समयr_ctrl & ~Timer10X;
		अगर (np->speed100)
			new_पूर्णांकr_समयr_ctrl |= Timer10X;
		अगर (np->पूर्णांकr_समयr_ctrl != new_पूर्णांकr_समयr_ctrl) अणु
			np->पूर्णांकr_समयr_ctrl = new_पूर्णांकr_समयr_ctrl;
			ग_लिखोl(new_पूर्णांकr_समयr_ctrl, ioaddr + IntrTimerCtrl);
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(dev);
		prपूर्णांकk(KERN_DEBUG "%s: Link is down\n", dev->name);
	पूर्ण
पूर्ण


अटल व्योम netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	/* Came बंद to underrunning the Tx FIFO, increase threshold. */
	अगर (पूर्णांकr_status & IntrTxDataLow) अणु
		अगर (np->tx_threshold <= PKT_BUF_SZ / 16) अणु
			ग_लिखोl(++np->tx_threshold, np->base + TxThreshold);
			prपूर्णांकk(KERN_NOTICE "%s: PCI bus congestion, increasing Tx FIFO threshold to %d bytes\n",
			       dev->name, np->tx_threshold * 16);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_WARNING "%s: PCI Tx underflow -- adapter is probably malfunctioning\n", dev->name);
	पूर्ण
	अगर (पूर्णांकr_status & IntrRxGFPDead) अणु
		dev->stats.rx_fअगरo_errors++;
		dev->stats.rx_errors++;
	पूर्ण
	अगर (पूर्णांकr_status & (IntrNoTxCsum | IntrDMAErr)) अणु
		dev->stats.tx_fअगरo_errors++;
		dev->stats.tx_errors++;
	पूर्ण
	अगर ((पूर्णांकr_status & ~(IntrNormalMask | IntrAbnormalSummary | IntrLinkChange | IntrStatsMax | IntrTxDataLow | IntrRxGFPDead | IntrNoTxCsum | IntrPCIPad)) && debug)
		prपूर्णांकk(KERN_ERR "%s: Something Wicked happened! %#8.8x.\n",
		       dev->name, पूर्णांकr_status);
पूर्ण


अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;

	/* This adapter architecture needs no SMP locks. */
	dev->stats.tx_bytes = पढ़ोl(ioaddr + 0x57010);
	dev->stats.rx_bytes = पढ़ोl(ioaddr + 0x57044);
	dev->stats.tx_packets = पढ़ोl(ioaddr + 0x57000);
	dev->stats.tx_पातed_errors =
		पढ़ोl(ioaddr + 0x57024) + पढ़ोl(ioaddr + 0x57028);
	dev->stats.tx_winकरोw_errors = पढ़ोl(ioaddr + 0x57018);
	dev->stats.collisions =
		पढ़ोl(ioaddr + 0x57004) + पढ़ोl(ioaddr + 0x57008);

	/* The chip only need report frame silently dropped. */
	dev->stats.rx_dropped += पढ़ोw(ioaddr + RxDMAStatus);
	ग_लिखोw(0, ioaddr + RxDMAStatus);
	dev->stats.rx_crc_errors = पढ़ोl(ioaddr + 0x5703C);
	dev->stats.rx_frame_errors = पढ़ोl(ioaddr + 0x57040);
	dev->stats.rx_length_errors = पढ़ोl(ioaddr + 0x57058);
	dev->stats.rx_missed_errors = पढ़ोl(ioaddr + 0x5707C);

	वापस &dev->stats;
पूर्ण

#अगर_घोषित VLAN_SUPPORT
अटल u32 set_vlan_mode(काष्ठा netdev_निजी *np)
अणु
	u32 ret = VlanMode;
	u16 vid;
	व्योम __iomem *filter_addr = np->base + HashTable + 8;
	पूर्णांक vlan_count = 0;

	क्रम_each_set_bit(vid, np->active_vlans, VLAN_N_VID) अणु
		अगर (vlan_count == 32)
			अवरोध;
		ग_लिखोw(vid, filter_addr);
		filter_addr += 16;
		vlan_count++;
	पूर्ण
	अगर (vlan_count == 32) अणु
		ret |= PerfectFilterVlan;
		जबतक (vlan_count < 32) अणु
			ग_लिखोw(0, filter_addr);
			filter_addr += 16;
			vlan_count++;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर /* VLAN_SUPPORT */

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	u32 rx_mode = MinVLANPrio;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;

#अगर_घोषित VLAN_SUPPORT
	rx_mode |= set_vlan_mode(np);
#पूर्ण_अगर /* VLAN_SUPPORT */

	अगर (dev->flags & IFF_PROMISC) अणु	/* Set promiscuous. */
		rx_mode |= AcceptAll;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to match, or accept all multicasts. */
		rx_mode |= AcceptBroadcast|AcceptAllMulticast|PerfectFilter;
	पूर्ण अन्यथा अगर (netdev_mc_count(dev) <= 14) अणु
		/* Use the 16 element perfect filter, skip first two entries. */
		व्योम __iomem *filter_addr = ioaddr + PerfFilterTable + 2 * 16;
		__be16 *eaddrs;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			eaddrs = (__be16 *) ha->addr;
			ग_लिखोw(be16_to_cpu(eaddrs[2]), filter_addr); filter_addr += 4;
			ग_लिखोw(be16_to_cpu(eaddrs[1]), filter_addr); filter_addr += 4;
			ग_लिखोw(be16_to_cpu(eaddrs[0]), filter_addr); filter_addr += 8;
		पूर्ण
		eaddrs = (__be16 *)dev->dev_addr;
		i = netdev_mc_count(dev) + 2;
		जबतक (i++ < 16) अणु
			ग_लिखोw(be16_to_cpu(eaddrs[0]), filter_addr); filter_addr += 4;
			ग_लिखोw(be16_to_cpu(eaddrs[1]), filter_addr); filter_addr += 4;
			ग_लिखोw(be16_to_cpu(eaddrs[2]), filter_addr); filter_addr += 8;
		पूर्ण
		rx_mode |= AcceptBroadcast|PerfectFilter;
	पूर्ण अन्यथा अणु
		/* Must use a multicast hash table. */
		व्योम __iomem *filter_addr;
		__be16 *eaddrs;
		__le16 mc_filter[32] __attribute__ ((aligned(माप(दीर्घ))));	/* Multicast hash filter */

		स_रखो(mc_filter, 0, माप(mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			/* The chip uses the upper 9 CRC bits
			   as index पूर्णांकo the hash table */
			पूर्णांक bit_nr = ether_crc_le(ETH_ALEN, ha->addr) >> 23;
			__le32 *fptr = (__le32 *) &mc_filter[(bit_nr >> 4) & ~1];

			*fptr |= cpu_to_le32(1 << (bit_nr & 31));
		पूर्ण
		/* Clear the perfect filter list, skip first two entries. */
		filter_addr = ioaddr + PerfFilterTable + 2 * 16;
		eaddrs = (__be16 *)dev->dev_addr;
		क्रम (i = 2; i < 16; i++) अणु
			ग_लिखोw(be16_to_cpu(eaddrs[0]), filter_addr); filter_addr += 4;
			ग_लिखोw(be16_to_cpu(eaddrs[1]), filter_addr); filter_addr += 4;
			ग_लिखोw(be16_to_cpu(eaddrs[2]), filter_addr); filter_addr += 8;
		पूर्ण
		क्रम (filter_addr = ioaddr + HashTable, i = 0; i < 32; filter_addr+= 16, i++)
			ग_लिखोw(mc_filter[i], filter_addr);
		rx_mode |= AcceptBroadcast|PerfectFilter|HashFilter;
	पूर्ण
	ग_लिखोl(rx_mode, ioaddr + RxFilterMode);
पूर्ण

अटल पूर्णांक check_अगर_running(काष्ठा net_device *dev)
अणु
	अगर (!netअगर_running(dev))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(np->pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक get_link_ksettings(काष्ठा net_device *dev,
			      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	spin_lock_irq(&np->lock);
	mii_ethtool_get_link_ksettings(&np->mii_अगर, cmd);
	spin_unlock_irq(&np->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक set_link_ksettings(काष्ठा net_device *dev,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक res;
	spin_lock_irq(&np->lock);
	res = mii_ethtool_set_link_ksettings(&np->mii_अगर, cmd);
	spin_unlock_irq(&np->lock);
	check_duplex(dev);
	वापस res;
पूर्ण

अटल पूर्णांक nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस mii_nway_restart(&np->mii_अगर);
पूर्ण

अटल u32 get_link(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस mii_link_ok(&np->mii_अगर);
पूर्ण

अटल u32 get_msglevel(काष्ठा net_device *dev)
अणु
	वापस debug;
पूर्ण

अटल व्योम set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	debug = val;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.begin = check_अगर_running,
	.get_drvinfo = get_drvinfo,
	.nway_reset = nway_reset,
	.get_link = get_link,
	.get_msglevel = get_msglevel,
	.set_msglevel = set_msglevel,
	.get_link_ksettings = get_link_ksettings,
	.set_link_ksettings = set_link_ksettings,
पूर्ण;

अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	पूर्णांक rc;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	spin_lock_irq(&np->lock);
	rc = generic_mii_ioctl(&np->mii_अगर, data, cmd, शून्य);
	spin_unlock_irq(&np->lock);

	अगर ((cmd == SIOCSMIIREG) && (data->phy_id == np->phys[0]))
		check_duplex(dev);

	वापस rc;
पूर्ण

अटल पूर्णांक netdev_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	पूर्णांक i;

	netअगर_stop_queue(dev);

	napi_disable(&np->napi);

	अगर (debug > 1) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Shutting down ethercard, Intr status %#8.8x.\n",
			   dev->name, (पूर्णांक) पढ़ोl(ioaddr + IntrStatus));
		prपूर्णांकk(KERN_DEBUG "%s: Queue pointers were Tx %d / %d, Rx %d / %d.\n",
		       dev->name, np->cur_tx, np->dirty_tx,
		       np->cur_rx, np->dirty_rx);
	पूर्ण

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	ग_लिखोl(0, ioaddr + IntrEnable);

	/* Stop the chip's Tx and Rx processes. */
	ग_लिखोl(0, ioaddr + GenCtrl);
	पढ़ोl(ioaddr + GenCtrl);

	अगर (debug > 5) अणु
		prपूर्णांकk(KERN_DEBUG"  Tx ring at %#llx:\n",
		       (दीर्घ दीर्घ) np->tx_ring_dma);
		क्रम (i = 0; i < 8 /* TX_RING_SIZE is huge! */; i++)
			prपूर्णांकk(KERN_DEBUG " #%d desc. %#8.8x %#llx -> %#8.8x.\n",
			       i, le32_to_cpu(np->tx_ring[i].status),
			       (दीर्घ दीर्घ) dma_to_cpu(np->tx_ring[i].addr),
			       le32_to_cpu(np->tx_करोne_q[i].status));
		prपूर्णांकk(KERN_DEBUG "  Rx ring at %#llx -> %p:\n",
		       (दीर्घ दीर्घ) np->rx_ring_dma, np->rx_करोne_q);
		अगर (np->rx_करोne_q)
			क्रम (i = 0; i < 8 /* RX_RING_SIZE */; i++) अणु
				prपूर्णांकk(KERN_DEBUG " #%d desc. %#llx -> %#8.8x\n",
				       i, (दीर्घ दीर्घ) dma_to_cpu(np->rx_ring[i].rxaddr), le32_to_cpu(np->rx_करोne_q[i].status));
		पूर्ण
	पूर्ण

	मुक्त_irq(np->pci_dev->irq, dev);

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		np->rx_ring[i].rxaddr = cpu_to_dma(0xBADF00D0); /* An invalid address. */
		अगर (np->rx_info[i].skb != शून्य) अणु
			dma_unmap_single(&np->pci_dev->dev,
					 np->rx_info[i].mapping,
					 np->rx_buf_sz, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(np->rx_info[i].skb);
		पूर्ण
		np->rx_info[i].skb = शून्य;
		np->rx_info[i].mapping = 0;
	पूर्ण
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = np->tx_info[i].skb;
		अगर (skb == शून्य)
			जारी;
		dma_unmap_single(&np->pci_dev->dev, np->tx_info[i].mapping,
				 skb_first_frag_len(skb), DMA_TO_DEVICE);
		np->tx_info[i].mapping = 0;
		dev_kमुक्त_skb(skb);
		np->tx_info[i].skb = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused starfire_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	अगर (netअगर_running(dev)) अणु
		netअगर_device_detach(dev);
		netdev_बंद(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused starfire_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	अगर (netअगर_running(dev)) अणु
		netdev_खोलो(dev);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम starfire_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	BUG_ON(!dev);

	unरेजिस्टर_netdev(dev);

	अगर (np->queue_mem)
		dma_मुक्त_coherent(&pdev->dev, np->queue_mem_size,
				  np->queue_mem, np->queue_mem_dma);


	/* XXX: add wakeup code -- requires firmware क्रम MagicPacket */
	pci_set_घातer_state(pdev, PCI_D3hot);	/* go to sleep in D3 mode */
	pci_disable_device(pdev);

	iounmap(np->base);
	pci_release_regions(pdev);

	मुक्त_netdev(dev);			/* Will also मुक्त np!! */
पूर्ण

अटल SIMPLE_DEV_PM_OPS(starfire_pm_ops, starfire_suspend, starfire_resume);

अटल काष्ठा pci_driver starfire_driver = अणु
	.name		= DRV_NAME,
	.probe		= starfire_init_one,
	.हटाओ		= starfire_हटाओ_one,
	.driver.pm	= &starfire_pm_ops,
	.id_table	= starfire_pci_tbl,
पूर्ण;


अटल पूर्णांक __init starfire_init (व्योम)
अणु
/* when a module, this is prपूर्णांकed whether or not devices are found in probe */
#अगर_घोषित MODULE
	prपूर्णांकk(KERN_INFO DRV_NAME ": polling (NAPI) enabled\n");
#पूर्ण_अगर

	BUILD_BUG_ON(माप(dma_addr_t) != माप(netdrv_addr_t));

	वापस pci_रेजिस्टर_driver(&starfire_driver);
पूर्ण


अटल व्योम __निकास starfire_cleanup (व्योम)
अणु
	pci_unरेजिस्टर_driver (&starfire_driver);
पूर्ण


module_init(starfire_init);
module_निकास(starfire_cleanup);
