<शैली गुरु>
/* sundance.c: A Linux device driver क्रम the Sundance ST201 "Alta". */
/*
	Written 1999-2000 by Donald Becker.

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	Support and updates available at
	http://www.scyld.com/network/sundance.hपंचांगl
	[link no दीर्घer provides useful info -jgarzik]
	Archives of the mailing list are still available at
	https://www.beowulf.org/pipermail/netdrivers/

*/

#घोषणा DRV_NAME	"sundance"

/* The user-configurable values.
   These may be modअगरied when a driver module is loaded.*/
अटल पूर्णांक debug = 1;			/* 1 normal messages, 0 quiet .. 7 verbose. */
/* Maximum number of multicast addresses to filter (vs. rx-all-multicast).
   Typical is a 64 element hash table based on the Ethernet CRC.  */
अटल स्थिर पूर्णांक multicast_filter_limit = 32;

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
   Setting to > 1518 effectively disables this feature.
   This chip can receive पूर्णांकo offset buffers, so the Alpha करोes not
   need a copy-align. */
अटल पूर्णांक rx_copyअवरोध;
अटल पूर्णांक flowctrl=1;

/* media[] specअगरies the media type the NIC operates at.
		 स्वतःsense	Autosensing active media.
		 10mbps_hd 	10Mbps half duplex.
		 10mbps_fd 	10Mbps full duplex.
		 100mbps_hd 	100Mbps half duplex.
		 100mbps_fd 	100Mbps full duplex.
		 0		Autosensing active media.
		 1	 	10Mbps half duplex.
		 2	 	10Mbps full duplex.
		 3	 	100Mbps half duplex.
		 4	 	100Mbps full duplex.
*/
#घोषणा MAX_UNITS 8
अटल अक्षर *media[MAX_UNITS];


/* Operational parameters that are set at compile समय. */

/* Keep the ring sizes a घातer of two क्रम compile efficiency.
   The compiler will convert <अचिन्हित>'%'<2^N> पूर्णांकo a bit mask.
   Making the Tx ring too large decreases the effectiveness of channel
   bonding and packet priority, and more than 128 requires modअगरying the
   Tx error recovery.
   Large receive rings merely waste memory. */
#घोषणा TX_RING_SIZE	32
#घोषणा TX_QUEUE_LEN	(TX_RING_SIZE - 1) /* Limit ring entries actually used.  */
#घोषणा RX_RING_SIZE	64
#घोषणा RX_BUDGET	32
#घोषणा TX_TOTAL_SIZE	TX_RING_SIZE*माप(काष्ठा netdev_desc)
#घोषणा RX_TOTAL_SIZE	RX_RING_SIZE*माप(काष्ठा netdev_desc)

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (4*HZ)
#घोषणा PKT_BUF_SZ		1536	/* Size of each temporary Rx buffer.*/

/* Include files, deचिन्हित to support most kernel versions 2.0.0 and later. */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>		/* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/crc32.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("Sundance Alta Ethernet driver");
MODULE_LICENSE("GPL");

module_param(debug, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param_array(media, अक्षरp, शून्य, 0);
module_param(flowctrl, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Sundance Alta debug level (0-5)");
MODULE_PARM_DESC(rx_copyअवरोध, "Sundance Alta copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(flowctrl, "Sundance Alta flow control [0|1]");

/*
				Theory of Operation

I. Board Compatibility

This driver is deचिन्हित क्रम the Sundance Technologies "Alta" ST201 chip.

II. Board-specअगरic settings

III. Driver operation

IIIa. Ring buffers

This driver uses two अटलally allocated fixed-size descriptor lists
क्रमmed पूर्णांकo rings by a branch from the final descriptor to the beginning of
the list.  The ring sizes are set at compile समय by RX/TX_RING_SIZE.
Some chips explicitly use only 2^N sized rings, जबतक others use a
'next descriptor' poपूर्णांकer that the driver क्रमms पूर्णांकo rings.

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

A subtle aspect of the operation is that the IP header at offset 14 in an
ethernet frame isn't दीर्घword aligned क्रम further processing.
Unaligned buffers are permitted by the Sundance hardware, so
frames are received पूर्णांकo the skbuff at an offset of "+2", 16-byte aligning
the IP header.

IIId. Synchronization

The driver runs as two independent, single-thपढ़ोed flows of control.  One
is the send-packet routine, which enक्रमces single-thपढ़ोed use by the
dev->tbusy flag.  The other thपढ़ो is the पूर्णांकerrupt handler, which is single
thपढ़ोed by the hardware and पूर्णांकerrupt handling software.

The send packet thपढ़ो has partial control over the Tx ring and 'dev->tbusy'
flag.  It sets the tbusy flag whenever it's queuing a Tx packet. If the next
queue slot is empty, it clears the tbusy flag when finished otherwise it sets
the 'lp->tx_full' flag.

The पूर्णांकerrupt handler has exclusive control over the Rx ring and records stats
from the Tx ring.  After reaping the stats, it marks the Tx queue entry as
empty by incrementing the dirty_tx mark. Iff the 'lp->tx_full' flag is set, it
clears both the tx_full and tbusy flags.

IV. Notes

IVb. References

The Sundance ST201 datasheet, preliminary version.
The Kendin KS8723 datasheet, preliminary version.
The ICplus IP100 datasheet, preliminary version.
http://www.scyld.com/expert/100mbps.hपंचांगl
http://www.scyld.com/expert/NWay.hपंचांगl

IVc. Errata

*/

/* Work-around क्रम Kendin chip bugs. */
#अगर_अघोषित CONFIG_SUNDANCE_MMIO
#घोषणा USE_IO_OPS 1
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id sundance_pci_tbl[] = अणु
	अणु 0x1186, 0x1002, 0x1186, 0x1002, 0, 0, 0 पूर्ण,
	अणु 0x1186, 0x1002, 0x1186, 0x1003, 0, 0, 1 पूर्ण,
	अणु 0x1186, 0x1002, 0x1186, 0x1012, 0, 0, 2 पूर्ण,
	अणु 0x1186, 0x1002, 0x1186, 0x1040, 0, 0, 3 पूर्ण,
	अणु 0x1186, 0x1002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 4 पूर्ण,
	अणु 0x13F0, 0x0201, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 5 पूर्ण,
	अणु 0x13F0, 0x0200, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 6 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, sundance_pci_tbl);

क्रमागत अणु
	netdev_io_size = 128
पूर्ण;

काष्ठा pci_id_info अणु
        स्थिर अक्षर *name;
पूर्ण;
अटल स्थिर काष्ठा pci_id_info pci_id_tbl[] = अणु
	अणु"D-Link DFE-550TX FAST Ethernet Adapter"पूर्ण,
	अणु"D-Link DFE-550FX 100Mbps Fiber-optics Adapter"पूर्ण,
	अणु"D-Link DFE-580TX 4 port Server Adapter"पूर्ण,
	अणु"D-Link DFE-530TXS FAST Ethernet Adapter"पूर्ण,
	अणु"D-Link DL10050-based FAST Ethernet Adapter"पूर्ण,
	अणु"Sundance Technology Alta"पूर्ण,
	अणु"IC Plus Corporation IP100A FAST Ethernet Adapter"पूर्ण,
	अणु पूर्ण	/* terminate list. */
पूर्ण;

/* This driver was written to use PCI memory space, however x86-oriented
   hardware often uses I/O space accesses. */

/* Offsets to the device रेजिस्टरs.
   Unlike software-only प्रणालीs, device drivers पूर्णांकeract with complex hardware.
   It's not useful to define symbolic names क्रम every रेजिस्टर bit in the
   device.  The name can only partially करोcument the semantics and make
   the driver दीर्घer and more dअगरficult to पढ़ो.
   In general, only the important configuration values or bits changed
   multiple बार should be defined symbolically.
*/
क्रमागत alta_offsets अणु
	DMACtrl = 0x00,
	TxListPtr = 0x04,
	TxDMABurstThresh = 0x08,
	TxDMAUrgentThresh = 0x09,
	TxDMAPollPeriod = 0x0a,
	RxDMAStatus = 0x0c,
	RxListPtr = 0x10,
	DebugCtrl0 = 0x1a,
	DebugCtrl1 = 0x1c,
	RxDMABurstThresh = 0x14,
	RxDMAUrgentThresh = 0x15,
	RxDMAPollPeriod = 0x16,
	LEDCtrl = 0x1a,
	ASICCtrl = 0x30,
	EEData = 0x34,
	EECtrl = 0x36,
	FlashAddr = 0x40,
	FlashData = 0x44,
	WakeEvent = 0x45,
	TxStatus = 0x46,
	TxFrameId = 0x47,
	DownCounter = 0x18,
	IntrClear = 0x4a,
	IntrEnable = 0x4c,
	IntrStatus = 0x4e,
	MACCtrl0 = 0x50,
	MACCtrl1 = 0x52,
	StationAddr = 0x54,
	MaxFrameSize = 0x5A,
	RxMode = 0x5c,
	MIICtrl = 0x5e,
	MulticastFilter0 = 0x60,
	MulticastFilter1 = 0x64,
	RxOctetsLow = 0x68,
	RxOctetsHigh = 0x6a,
	TxOctetsLow = 0x6c,
	TxOctetsHigh = 0x6e,
	TxFramesOK = 0x70,
	RxFramesOK = 0x72,
	StatsCarrierError = 0x74,
	StatsLateColl = 0x75,
	StatsMultiColl = 0x76,
	StatsOneColl = 0x77,
	StatsTxDefer = 0x78,
	RxMissed = 0x79,
	StatsTxXSDefer = 0x7a,
	StatsTxAbort = 0x7b,
	StatsBcastTx = 0x7c,
	StatsBcastRx = 0x7d,
	StatsMcastTx = 0x7e,
	StatsMcastRx = 0x7f,
	/* Aliased and bogus values! */
	RxStatus = 0x0c,
पूर्ण;

#घोषणा ASIC_HI_WORD(x)	((x) + 2)

क्रमागत ASICCtrl_HiWord_bit अणु
	GlobalReset = 0x0001,
	RxReset = 0x0002,
	TxReset = 0x0004,
	DMAReset = 0x0008,
	FIFOReset = 0x0010,
	NetworkReset = 0x0020,
	HostReset = 0x0040,
	ResetBusy = 0x0400,
पूर्ण;

/* Bits in the पूर्णांकerrupt status/mask रेजिस्टरs. */
क्रमागत पूर्णांकr_status_bits अणु
	IntrSummary=0x0001, IntrPCIErr=0x0002, IntrMACCtrl=0x0008,
	IntrTxDone=0x0004, IntrRxDone=0x0010, IntrRxStart=0x0020,
	IntrDrvRqst=0x0040,
	StatsMax=0x0080, LinkChange=0x0100,
	IntrTxDMADone=0x0200, IntrRxDMADone=0x0400,
पूर्ण;

/* Bits in the RxMode रेजिस्टर. */
क्रमागत rx_mode_bits अणु
	AcceptAllIPMulti=0x20, AcceptMultiHash=0x10, AcceptAll=0x08,
	AcceptBroadcast=0x04, AcceptMulticast=0x02, AcceptMyPhys=0x01,
पूर्ण;
/* Bits in MACCtrl. */
क्रमागत mac_ctrl0_bits अणु
	EnbFullDuplex=0x20, EnbRcvLargeFrame=0x40,
	EnbFlowCtrl=0x100, EnbPassRxCRC=0x200,
पूर्ण;
क्रमागत mac_ctrl1_bits अणु
	StatsEnable=0x0020,	StatsDisable=0x0040, StatsEnabled=0x0080,
	TxEnable=0x0100, TxDisable=0x0200, TxEnabled=0x0400,
	RxEnable=0x0800, RxDisable=0x1000, RxEnabled=0x2000,
पूर्ण;

/* Bits in WakeEvent रेजिस्टर. */
क्रमागत wake_event_bits अणु
	WakePktEnable = 0x01,
	MagicPktEnable = 0x02,
	LinkEventEnable = 0x04,
	WolEnable = 0x80,
पूर्ण;

/* The Rx and Tx buffer descriptors. */
/* Note that using only 32 bit fields simplअगरies conversion to big-endian
   architectures. */
काष्ठा netdev_desc अणु
	__le32 next_desc;
	__le32 status;
	काष्ठा desc_frag अणु __le32 addr, length; पूर्ण frag[1];
पूर्ण;

/* Bits in netdev_desc.status */
क्रमागत desc_status_bits अणु
	DescOwn=0x8000,
	DescEndPacket=0x4000,
	DescEndRing=0x2000,
	LastFrag=0x80000000,
	DescIntrOnTx=0x8000,
	DescIntrOnDMADone=0x80000000,
	DisableAlign = 0x00000001,
पूर्ण;

#घोषणा PRIV_ALIGN	15 	/* Required alignment mask */
/* Use  __attribute__((aligned (L1_CACHE_BYTES)))  to मुख्यtain alignment
   within the काष्ठाure. */
#घोषणा MII_CNT		4
काष्ठा netdev_निजी अणु
	/* Descriptor rings first क्रम alignment. */
	काष्ठा netdev_desc *rx_ring;
	काष्ठा netdev_desc *tx_ring;
	काष्ठा sk_buff* rx_skbuff[RX_RING_SIZE];
	काष्ठा sk_buff* tx_skbuff[TX_RING_SIZE];
        dma_addr_t tx_ring_dma;
        dma_addr_t rx_ring_dma;
	काष्ठा समयr_list समयr;		/* Media monitoring समयr. */
	काष्ठा net_device *ndev;		/* backpoपूर्णांकer */
	/* ethtool extra stats */
	काष्ठा अणु
		u64 tx_multiple_collisions;
		u64 tx_single_collisions;
		u64 tx_late_collisions;
		u64 tx_deferred;
		u64 tx_deferred_excessive;
		u64 tx_पातed;
		u64 tx_bcasts;
		u64 rx_bcasts;
		u64 tx_mcasts;
		u64 rx_mcasts;
	पूर्ण xstats;
	/* Frequently used values: keep some adjacent क्रम cache effect. */
	spinlock_t lock;
	पूर्णांक msg_enable;
	पूर्णांक chip_id;
	अचिन्हित पूर्णांक cur_rx, dirty_rx;		/* Producer/consumer ring indices */
	अचिन्हित पूर्णांक rx_buf_sz;			/* Based on MTU+slack. */
	काष्ठा netdev_desc *last_tx;		/* Last Tx descriptor used. */
	अचिन्हित पूर्णांक cur_tx, dirty_tx;
	/* These values are keep track of the transceiver/media in use. */
	अचिन्हित पूर्णांक flowctrl:1;
	अचिन्हित पूर्णांक शेष_port:4;		/* Last dev->अगर_port value. */
	अचिन्हित पूर्णांक an_enable:1;
	अचिन्हित पूर्णांक speed;
	अचिन्हित पूर्णांक wol_enabled:1;			/* Wake on LAN enabled */
	काष्ठा tasklet_काष्ठा rx_tasklet;
	काष्ठा tasklet_काष्ठा tx_tasklet;
	पूर्णांक budget;
	पूर्णांक cur_task;
	/* Multicast and receive mode. */
	spinlock_t mcastlock;			/* SMP lock multicast updates. */
	u16 mcast_filter[4];
	/* MII transceiver section. */
	काष्ठा mii_अगर_info mii_अगर;
	पूर्णांक mii_preamble_required;
	अचिन्हित अक्षर phys[MII_CNT];		/* MII device addresses, only first one used. */
	काष्ठा pci_dev *pci_dev;
	व्योम __iomem *base;
	spinlock_t statlock;
पूर्ण;

/* The station address location in the EEPROM. */
#घोषणा EEPROM_SA_OFFSET	0x10
#घोषणा DEFAULT_INTR (IntrRxDMADone | IntrPCIErr | \
			IntrDrvRqst | IntrTxDone | StatsMax | \
			LinkChange)

अटल पूर्णांक  change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);
अटल पूर्णांक  eeprom_पढ़ो(व्योम __iomem *ioaddr, पूर्णांक location);
अटल पूर्णांक  mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value);
अटल पूर्णांक  mdio_रुको_link(काष्ठा net_device *dev, पूर्णांक रुको);
अटल पूर्णांक  netdev_खोलो(काष्ठा net_device *dev);
अटल व्योम check_duplex(काष्ठा net_device *dev);
अटल व्योम netdev_समयr(काष्ठा समयr_list *t);
अटल व्योम tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम init_ring(काष्ठा net_device *dev);
अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल पूर्णांक reset_tx (काष्ठा net_device *dev);
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance);
अटल व्योम rx_poll(काष्ठा tasklet_काष्ठा *t);
अटल व्योम tx_poll(काष्ठा tasklet_काष्ठा *t);
अटल व्योम refill_rx (काष्ठा net_device *dev);
अटल व्योम netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status);
अटल व्योम netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल पूर्णांक __set_mac_addr(काष्ठा net_device *dev);
अटल पूर्णांक sundance_set_mac_addr(काष्ठा net_device *dev, व्योम *data);
अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev);
अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल पूर्णांक  netdev_बंद(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops ethtool_ops;

अटल व्योम sundance_reset(काष्ठा net_device *dev, अचिन्हित दीर्घ reset_cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base + ASICCtrl;
	पूर्णांक countकरोwn;

	/* ST201 करोcumentation states ASICCtrl is a 32bit रेजिस्टर */
	ioग_लिखो32 (reset_cmd | ioपढ़ो32 (ioaddr), ioaddr);
	/* ST201 करोcumentation states reset can take up to 1 ms */
	countकरोwn = 10 + 1;
	जबतक (ioपढ़ो32 (ioaddr) & (ResetBusy << 16)) अणु
		अगर (--countकरोwn == 0) अणु
			prपूर्णांकk(KERN_WARNING "%s : reset not completed !!\n", dev->name);
			अवरोध;
		पूर्ण
		udelay(100);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम sundance_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	disable_irq(np->pci_dev->irq);
	पूर्णांकr_handler(np->pci_dev->irq, dev);
	enable_irq(np->pci_dev->irq);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= netdev_खोलो,
	.nकरो_stop		= netdev_बंद,
	.nकरो_start_xmit		= start_tx,
	.nकरो_get_stats 		= get_stats,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_करो_ioctl 		= netdev_ioctl,
	.nकरो_tx_समयout		= tx_समयout,
	.nकरो_change_mtu		= change_mtu,
	.nकरो_set_mac_address 	= sundance_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller 	= sundance_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक sundance_probe1(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा netdev_निजी *np;
	अटल पूर्णांक card_idx;
	पूर्णांक chip_idx = ent->driver_data;
	पूर्णांक irq;
	पूर्णांक i;
	व्योम __iomem *ioaddr;
	u16 mii_ctl;
	व्योम *ring_space;
	dma_addr_t ring_dma;
#अगर_घोषित USE_IO_OPS
	पूर्णांक bar = 0;
#अन्यथा
	पूर्णांक bar = 1;
#पूर्ण_अगर
	पूर्णांक phy, phy_end, phy_idx = 0;

	अगर (pci_enable_device(pdev))
		वापस -EIO;
	pci_set_master(pdev);

	irq = pdev->irq;

	dev = alloc_etherdev(माप(*np));
	अगर (!dev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);

	अगर (pci_request_regions(pdev, DRV_NAME))
		जाओ err_out_netdev;

	ioaddr = pci_iomap(pdev, bar, netdev_io_size);
	अगर (!ioaddr)
		जाओ err_out_res;

	क्रम (i = 0; i < 3; i++)
		((__le16 *)dev->dev_addr)[i] =
			cpu_to_le16(eeprom_पढ़ो(ioaddr, i + EEPROM_SA_OFFSET));

	np = netdev_priv(dev);
	np->ndev = dev;
	np->base = ioaddr;
	np->pci_dev = pdev;
	np->chip_id = chip_idx;
	np->msg_enable = (1 << debug) - 1;
	spin_lock_init(&np->lock);
	spin_lock_init(&np->statlock);
	tasklet_setup(&np->rx_tasklet, rx_poll);
	tasklet_setup(&np->tx_tasklet, tx_poll);

	ring_space = dma_alloc_coherent(&pdev->dev, TX_TOTAL_SIZE,
			&ring_dma, GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_cleardev;
	np->tx_ring = (काष्ठा netdev_desc *)ring_space;
	np->tx_ring_dma = ring_dma;

	ring_space = dma_alloc_coherent(&pdev->dev, RX_TOTAL_SIZE,
			&ring_dma, GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_unmap_tx;
	np->rx_ring = (काष्ठा netdev_desc *)ring_space;
	np->rx_ring_dma = ring_dma;

	np->mii_अगर.dev = dev;
	np->mii_अगर.mdio_पढ़ो = mdio_पढ़ो;
	np->mii_अगर.mdio_ग_लिखो = mdio_ग_लिखो;
	np->mii_अगर.phy_id_mask = 0x1f;
	np->mii_अगर.reg_num_mask = 0x1f;

	/* The chip-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &netdev_ops;
	dev->ethtool_ops = &ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	/* MTU range: 68 - 8191 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = 8191;

	pci_set_drvdata(pdev, dev);

	i = रेजिस्टर_netdev(dev);
	अगर (i)
		जाओ err_out_unmap_rx;

	prपूर्णांकk(KERN_INFO "%s: %s at %p, %pM, IRQ %d.\n",
	       dev->name, pci_id_tbl[chip_idx].name, ioaddr,
	       dev->dev_addr, irq);

	np->phys[0] = 1;		/* Default setting */
	np->mii_preamble_required++;

	/*
	 * It seems some phys करोesn't deal well with address 0 being accessed
	 * first
	 */
	अगर (sundance_pci_tbl[np->chip_id].device == 0x0200) अणु
		phy = 0;
		phy_end = 31;
	पूर्ण अन्यथा अणु
		phy = 1;
		phy_end = 32;	/* wraps to zero, due to 'phy & 0x1f' */
	पूर्ण
	क्रम (; phy <= phy_end && phy_idx < MII_CNT; phy++) अणु
		पूर्णांक phyx = phy & 0x1f;
		पूर्णांक mii_status = mdio_पढ़ो(dev, phyx, MII_BMSR);
		अगर (mii_status != 0xffff  &&  mii_status != 0x0000) अणु
			np->phys[phy_idx++] = phyx;
			np->mii_अगर.advertising = mdio_पढ़ो(dev, phyx, MII_ADVERTISE);
			अगर ((mii_status & 0x0040) == 0)
				np->mii_preamble_required++;
			prपूर्णांकk(KERN_INFO "%s: MII PHY found at address %d, status "
				   "0x%4.4x advertising %4.4x.\n",
				   dev->name, phyx, mii_status, np->mii_अगर.advertising);
		पूर्ण
	पूर्ण
	np->mii_preamble_required--;

	अगर (phy_idx == 0) अणु
		prपूर्णांकk(KERN_INFO "%s: No MII transceiver found, aborting.  ASIC status %x\n",
			   dev->name, ioपढ़ो32(ioaddr + ASICCtrl));
		जाओ err_out_unरेजिस्टर;
	पूर्ण

	np->mii_अगर.phy_id = np->phys[0];

	/* Parse override configuration */
	np->an_enable = 1;
	अगर (card_idx < MAX_UNITS) अणु
		अगर (media[card_idx] != शून्य) अणु
			np->an_enable = 0;
			अगर (म_भेद (media[card_idx], "100mbps_fd") == 0 ||
			    म_भेद (media[card_idx], "4") == 0) अणु
				np->speed = 100;
				np->mii_अगर.full_duplex = 1;
			पूर्ण अन्यथा अगर (म_भेद (media[card_idx], "100mbps_hd") == 0 ||
				   म_भेद (media[card_idx], "3") == 0) अणु
				np->speed = 100;
				np->mii_अगर.full_duplex = 0;
			पूर्ण अन्यथा अगर (म_भेद (media[card_idx], "10mbps_fd") == 0 ||
				   म_भेद (media[card_idx], "2") == 0) अणु
				np->speed = 10;
				np->mii_अगर.full_duplex = 1;
			पूर्ण अन्यथा अगर (म_भेद (media[card_idx], "10mbps_hd") == 0 ||
				   म_भेद (media[card_idx], "1") == 0) अणु
				np->speed = 10;
				np->mii_अगर.full_duplex = 0;
			पूर्ण अन्यथा अणु
				np->an_enable = 1;
			पूर्ण
		पूर्ण
		अगर (flowctrl == 1)
			np->flowctrl = 1;
	पूर्ण

	/* Fibre PHY? */
	अगर (ioपढ़ो32 (ioaddr + ASICCtrl) & 0x80) अणु
		/* Default 100Mbps Full */
		अगर (np->an_enable) अणु
			np->speed = 100;
			np->mii_अगर.full_duplex = 1;
			np->an_enable = 0;
		पूर्ण
	पूर्ण
	/* Reset PHY */
	mdio_ग_लिखो (dev, np->phys[0], MII_BMCR, BMCR_RESET);
	mdelay (300);
	/* If flow control enabled, we need to advertise it.*/
	अगर (np->flowctrl)
		mdio_ग_लिखो (dev, np->phys[0], MII_ADVERTISE, np->mii_अगर.advertising | 0x0400);
	mdio_ग_लिखो (dev, np->phys[0], MII_BMCR, BMCR_ANENABLE|BMCR_ANRESTART);
	/* Force media type */
	अगर (!np->an_enable) अणु
		mii_ctl = 0;
		mii_ctl |= (np->speed == 100) ? BMCR_SPEED100 : 0;
		mii_ctl |= (np->mii_अगर.full_duplex) ? BMCR_FULLDPLX : 0;
		mdio_ग_लिखो (dev, np->phys[0], MII_BMCR, mii_ctl);
		prपूर्णांकk (KERN_INFO "Override speed=%d, %s duplex\n",
			np->speed, np->mii_अगर.full_duplex ? "Full" : "Half");

	पूर्ण

	/* Perhaps move the reset here? */
	/* Reset the chip to erase previous misconfiguration. */
	अगर (netअगर_msg_hw(np))
		prपूर्णांकk("ASIC Control is %x.\n", ioपढ़ो32(ioaddr + ASICCtrl));
	sundance_reset(dev, 0x00ff << 16);
	अगर (netअगर_msg_hw(np))
		prपूर्णांकk("ASIC Control is now %x.\n", ioपढ़ो32(ioaddr + ASICCtrl));

	card_idx++;
	वापस 0;

err_out_unरेजिस्टर:
	unरेजिस्टर_netdev(dev);
err_out_unmap_rx:
	dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE,
		np->rx_ring, np->rx_ring_dma);
err_out_unmap_tx:
	dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE,
		np->tx_ring, np->tx_ring_dma);
err_out_cleardev:
	pci_iounmap(pdev, ioaddr);
err_out_res:
	pci_release_regions(pdev);
err_out_netdev:
	मुक्त_netdev (dev);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	अगर (netअगर_running(dev))
		वापस -EBUSY;
	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

#घोषणा eeprom_delay(ee_addr)	ioपढ़ो32(ee_addr)
/* Read the EEPROM and MII Management Data I/O (MDIO) पूर्णांकerfaces. */
अटल पूर्णांक eeprom_पढ़ो(व्योम __iomem *ioaddr, पूर्णांक location)
अणु
	पूर्णांक boguscnt = 10000;		/* Typical 1900 ticks. */
	ioग_लिखो16(0x0200 | (location & 0xff), ioaddr + EECtrl);
	करो अणु
		eeprom_delay(ioaddr + EECtrl);
		अगर (! (ioपढ़ो16(ioaddr + EECtrl) & 0x8000)) अणु
			वापस ioपढ़ो16(ioaddr + EEData);
		पूर्ण
	पूर्ण जबतक (--boguscnt > 0);
	वापस 0;
पूर्ण

/*  MII transceiver control section.
	Read and ग_लिखो the MII रेजिस्टरs using software-generated serial
	MDIO protocol.  See the MII specअगरications or DP83840A data sheet
	क्रम details.

	The maximum data घड़ी rate is 2.5 Mhz.  The minimum timing is usually
	met by back-to-back 33Mhz PCI cycles. */
#घोषणा mdio_delay() ioपढ़ो8(mdio_addr)

क्रमागत mii_reg_bits अणु
	MDIO_ShअगरtClk=0x0001, MDIO_Data=0x0002, MDIO_EnbOutput=0x0004,
पूर्ण;
#घोषणा MDIO_EnbIn  (0)
#घोषणा MDIO_WRITE0 (MDIO_EnbOutput)
#घोषणा MDIO_WRITE1 (MDIO_Data | MDIO_EnbOutput)

/* Generate the preamble required क्रम initial synchronization and
   a few older transceivers. */
अटल व्योम mdio_sync(व्योम __iomem *mdio_addr)
अणु
	पूर्णांक bits = 32;

	/* Establish sync by sending at least 32 logic ones. */
	जबतक (--bits >= 0) अणु
		ioग_लिखो8(MDIO_WRITE1, mdio_addr);
		mdio_delay();
		ioग_लिखो8(MDIO_WRITE1 | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay();
	पूर्ण
पूर्ण

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *mdio_addr = np->base + MIICtrl;
	पूर्णांक mii_cmd = (0xf6 << 10) | (phy_id << 5) | location;
	पूर्णांक i, retval = 0;

	अगर (np->mii_preamble_required)
		mdio_sync(mdio_addr);

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 15; i >= 0; i--) अणु
		पूर्णांक dataval = (mii_cmd & (1 << i)) ? MDIO_WRITE1 : MDIO_WRITE0;

		ioग_लिखो8(dataval, mdio_addr);
		mdio_delay();
		ioग_लिखो8(dataval | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay();
	पूर्ण
	/* Read the two transition, 16 data, and wire-idle bits. */
	क्रम (i = 19; i > 0; i--) अणु
		ioग_लिखो8(MDIO_EnbIn, mdio_addr);
		mdio_delay();
		retval = (retval << 1) | ((ioपढ़ो8(mdio_addr) & MDIO_Data) ? 1 : 0);
		ioग_लिखो8(MDIO_EnbIn | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay();
	पूर्ण
	वापस (retval>>1) & 0xffff;
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *mdio_addr = np->base + MIICtrl;
	पूर्णांक mii_cmd = (0x5002 << 16) | (phy_id << 23) | (location<<18) | value;
	पूर्णांक i;

	अगर (np->mii_preamble_required)
		mdio_sync(mdio_addr);

	/* Shअगरt the command bits out. */
	क्रम (i = 31; i >= 0; i--) अणु
		पूर्णांक dataval = (mii_cmd & (1 << i)) ? MDIO_WRITE1 : MDIO_WRITE0;

		ioग_लिखो8(dataval, mdio_addr);
		mdio_delay();
		ioग_लिखो8(dataval | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay();
	पूर्ण
	/* Clear out extra bits. */
	क्रम (i = 2; i > 0; i--) अणु
		ioग_लिखो8(MDIO_EnbIn, mdio_addr);
		mdio_delay();
		ioग_लिखो8(MDIO_EnbIn | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay();
	पूर्ण
पूर्ण

अटल पूर्णांक mdio_रुको_link(काष्ठा net_device *dev, पूर्णांक रुको)
अणु
	पूर्णांक bmsr;
	पूर्णांक phy_id;
	काष्ठा netdev_निजी *np;

	np = netdev_priv(dev);
	phy_id = np->phys[0];

	करो अणु
		bmsr = mdio_पढ़ो(dev, phy_id, MII_BMSR);
		अगर (bmsr & 0x0004)
			वापस 0;
		mdelay(1);
	पूर्ण जबतक (--रुको > 0);
	वापस -1;
पूर्ण

अटल पूर्णांक netdev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	स्थिर पूर्णांक irq = np->pci_dev->irq;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	sundance_reset(dev, 0x00ff << 16);

	i = request_irq(irq, पूर्णांकr_handler, IRQF_SHARED, dev->name, dev);
	अगर (i)
		वापस i;

	अगर (netअगर_msg_अगरup(np))
		prपूर्णांकk(KERN_DEBUG "%s: netdev_open() irq %d\n", dev->name, irq);

	init_ring(dev);

	ioग_लिखो32(np->rx_ring_dma, ioaddr + RxListPtr);
	/* The Tx list poपूर्णांकer is written as packets are queued. */

	/* Initialize other रेजिस्टरs. */
	__set_mac_addr(dev);
#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
	ioग_लिखो16(dev->mtu + 18, ioaddr + MaxFrameSize);
#अन्यथा
	ioग_लिखो16(dev->mtu + 14, ioaddr + MaxFrameSize);
#पूर्ण_अगर
	अगर (dev->mtu > 2047)
		ioग_लिखो32(ioपढ़ो32(ioaddr + ASICCtrl) | 0x0C, ioaddr + ASICCtrl);

	/* Configure the PCI bus bursts and FIFO thresholds. */

	अगर (dev->अगर_port == 0)
		dev->अगर_port = np->शेष_port;

	spin_lock_init(&np->mcastlock);

	set_rx_mode(dev);
	ioग_लिखो16(0, ioaddr + IntrEnable);
	ioग_लिखो16(0, ioaddr + DownCounter);
	/* Set the chip to poll every N*320nsec. */
	ioग_लिखो8(100, ioaddr + RxDMAPollPeriod);
	ioग_लिखो8(127, ioaddr + TxDMAPollPeriod);
	/* Fix DFE-580TX packet drop issue */
	अगर (np->pci_dev->revision >= 0x14)
		ioग_लिखो8(0x01, ioaddr + DebugCtrl1);
	netअगर_start_queue(dev);

	spin_lock_irqsave(&np->lock, flags);
	reset_tx(dev);
	spin_unlock_irqrestore(&np->lock, flags);

	ioग_लिखो16 (StatsEnable | RxEnable | TxEnable, ioaddr + MACCtrl1);

	/* Disable Wol */
	ioग_लिखो8(ioपढ़ो8(ioaddr + WakeEvent) | 0x00, ioaddr + WakeEvent);
	np->wol_enabled = 0;

	अगर (netअगर_msg_अगरup(np))
		prपूर्णांकk(KERN_DEBUG "%s: Done netdev_open(), status: Rx %x Tx %x "
			   "MAC Control %x, %4.4x %4.4x.\n",
			   dev->name, ioपढ़ो32(ioaddr + RxStatus), ioपढ़ो8(ioaddr + TxStatus),
			   ioपढ़ो32(ioaddr + MACCtrl0),
			   ioपढ़ो16(ioaddr + MACCtrl1), ioपढ़ो16(ioaddr + MACCtrl0));

	/* Set the समयr to check क्रम link beat. */
	समयr_setup(&np->समयr, netdev_समयr, 0);
	np->समयr.expires = jअगरfies + 3*HZ;
	add_समयr(&np->समयr);

	/* Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ioग_लिखो16(DEFAULT_INTR, ioaddr + IntrEnable);

	वापस 0;
पूर्ण

अटल व्योम check_duplex(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	पूर्णांक mii_lpa = mdio_पढ़ो(dev, np->phys[0], MII_LPA);
	पूर्णांक negotiated = mii_lpa & np->mii_अगर.advertising;
	पूर्णांक duplex;

	/* Force media */
	अगर (!np->an_enable || mii_lpa == 0xffff) अणु
		अगर (np->mii_अगर.full_duplex)
			ioग_लिखो16 (ioपढ़ो16 (ioaddr + MACCtrl0) | EnbFullDuplex,
				ioaddr + MACCtrl0);
		वापस;
	पूर्ण

	/* Autonegotiation */
	duplex = (negotiated & 0x0100) || (negotiated & 0x01C0) == 0x0040;
	अगर (np->mii_अगर.full_duplex != duplex) अणु
		np->mii_अगर.full_duplex = duplex;
		अगर (netअगर_msg_link(np))
			prपूर्णांकk(KERN_INFO "%s: Setting %s-duplex based on MII #%d "
				   "negotiated capability %4.4x.\n", dev->name,
				   duplex ? "full" : "half", np->phys[0], negotiated);
		ioग_लिखो16(ioपढ़ो16(ioaddr + MACCtrl0) | (duplex ? 0x20 : 0), ioaddr + MACCtrl0);
	पूर्ण
पूर्ण

अटल व्योम netdev_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा netdev_निजी *np = from_समयr(np, t, समयr);
	काष्ठा net_device *dev = np->mii_अगर.dev;
	व्योम __iomem *ioaddr = np->base;
	पूर्णांक next_tick = 10*HZ;

	अगर (netअगर_msg_समयr(np)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Media selection timer tick, intr status %4.4x, "
			   "Tx %x Rx %x.\n",
			   dev->name, ioपढ़ो16(ioaddr + IntrEnable),
			   ioपढ़ो8(ioaddr + TxStatus), ioपढ़ो32(ioaddr + RxStatus));
	पूर्ण
	check_duplex(dev);
	np->समयr.expires = jअगरfies + next_tick;
	add_समयr(&np->समयr);
पूर्ण

अटल व्योम tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	अचिन्हित दीर्घ flag;

	netअगर_stop_queue(dev);
	tasklet_disable_in_atomic(&np->tx_tasklet);
	ioग_लिखो16(0, ioaddr + IntrEnable);
	prपूर्णांकk(KERN_WARNING "%s: Transmit timed out, TxStatus %2.2x "
		   "TxFrameId %2.2x,"
		   " resetting...\n", dev->name, ioपढ़ो8(ioaddr + TxStatus),
		   ioपढ़ो8(ioaddr + TxFrameId));

	अणु
		पूर्णांक i;
		क्रम (i=0; i<TX_RING_SIZE; i++) अणु
			prपूर्णांकk(KERN_DEBUG "%02x %08llx %08x %08x(%02x) %08x %08x\n", i,
				(अचिन्हित दीर्घ दीर्घ)(np->tx_ring_dma + i*माप(*np->tx_ring)),
				le32_to_cpu(np->tx_ring[i].next_desc),
				le32_to_cpu(np->tx_ring[i].status),
				(le32_to_cpu(np->tx_ring[i].status) >> 2) & 0xff,
				le32_to_cpu(np->tx_ring[i].frag[0].addr),
				le32_to_cpu(np->tx_ring[i].frag[0].length));
		पूर्ण
		prपूर्णांकk(KERN_DEBUG "TxListPtr=%08x netif_queue_stopped=%d\n",
			ioपढ़ो32(np->base + TxListPtr),
			netअगर_queue_stopped(dev));
		prपूर्णांकk(KERN_DEBUG "cur_tx=%d(%02x) dirty_tx=%d(%02x)\n",
			np->cur_tx, np->cur_tx % TX_RING_SIZE,
			np->dirty_tx, np->dirty_tx % TX_RING_SIZE);
		prपूर्णांकk(KERN_DEBUG "cur_rx=%d dirty_rx=%d\n", np->cur_rx, np->dirty_rx);
		prपूर्णांकk(KERN_DEBUG "cur_task=%d\n", np->cur_task);
	पूर्ण
	spin_lock_irqsave(&np->lock, flag);

	/* Stop and restart the chip's Tx processes . */
	reset_tx(dev);
	spin_unlock_irqrestore(&np->lock, flag);

	dev->अगर_port = 0;

	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;
	अगर (np->cur_tx - np->dirty_tx < TX_QUEUE_LEN - 4) अणु
		netअगर_wake_queue(dev);
	पूर्ण
	ioग_लिखो16(DEFAULT_INTR, ioaddr + IntrEnable);
	tasklet_enable(&np->tx_tasklet);
पूर्ण


/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल व्योम init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	np->cur_rx = np->cur_tx = 0;
	np->dirty_rx = np->dirty_tx = 0;
	np->cur_task = 0;

	np->rx_buf_sz = (dev->mtu <= 1520 ? PKT_BUF_SZ : dev->mtu + 16);

	/* Initialize all Rx descriptors. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		np->rx_ring[i].next_desc = cpu_to_le32(np->rx_ring_dma +
			((i+1)%RX_RING_SIZE)*माप(*np->rx_ring));
		np->rx_ring[i].status = 0;
		np->rx_ring[i].frag[0].length = 0;
		np->rx_skbuff[i] = शून्य;
	पूर्ण

	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb =
			netdev_alloc_skb(dev, np->rx_buf_sz + 2);
		np->rx_skbuff[i] = skb;
		अगर (skb == शून्य)
			अवरोध;
		skb_reserve(skb, 2);	/* 16 byte align the IP header. */
		np->rx_ring[i].frag[0].addr = cpu_to_le32(
			dma_map_single(&np->pci_dev->dev, skb->data,
				np->rx_buf_sz, DMA_FROM_DEVICE));
		अगर (dma_mapping_error(&np->pci_dev->dev,
					np->rx_ring[i].frag[0].addr)) अणु
			dev_kमुक्त_skb(skb);
			np->rx_skbuff[i] = शून्य;
			अवरोध;
		पूर्ण
		np->rx_ring[i].frag[0].length = cpu_to_le32(np->rx_buf_sz | LastFrag);
	पूर्ण
	np->dirty_rx = (अचिन्हित पूर्णांक)(i - RX_RING_SIZE);

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		np->tx_skbuff[i] = शून्य;
		np->tx_ring[i].status = 0;
	पूर्ण
पूर्ण

अटल व्योम tx_poll(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा netdev_निजी *np = from_tasklet(np, t, tx_tasklet);
	अचिन्हित head = np->cur_task % TX_RING_SIZE;
	काष्ठा netdev_desc *txdesc =
		&np->tx_ring[(np->cur_tx - 1) % TX_RING_SIZE];

	/* Chain the next poपूर्णांकer */
	क्रम (; np->cur_tx - np->cur_task > 0; np->cur_task++) अणु
		पूर्णांक entry = np->cur_task % TX_RING_SIZE;
		txdesc = &np->tx_ring[entry];
		अगर (np->last_tx) अणु
			np->last_tx->next_desc = cpu_to_le32(np->tx_ring_dma +
				entry*माप(काष्ठा netdev_desc));
		पूर्ण
		np->last_tx = txdesc;
	पूर्ण
	/* Indicate the latest descriptor of tx ring */
	txdesc->status |= cpu_to_le32(DescIntrOnTx);

	अगर (ioपढ़ो32 (np->base + TxListPtr) == 0)
		ioग_लिखो32 (np->tx_ring_dma + head * माप(काष्ठा netdev_desc),
			np->base + TxListPtr);
पूर्ण

अटल netdev_tx_t
start_tx (काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	काष्ठा netdev_desc *txdesc;
	अचिन्हित entry;

	/* Calculate the next Tx descriptor entry. */
	entry = np->cur_tx % TX_RING_SIZE;
	np->tx_skbuff[entry] = skb;
	txdesc = &np->tx_ring[entry];

	txdesc->next_desc = 0;
	txdesc->status = cpu_to_le32 ((entry << 2) | DisableAlign);
	txdesc->frag[0].addr = cpu_to_le32(dma_map_single(&np->pci_dev->dev,
				skb->data, skb->len, DMA_TO_DEVICE));
	अगर (dma_mapping_error(&np->pci_dev->dev,
				txdesc->frag[0].addr))
			जाओ drop_frame;
	txdesc->frag[0].length = cpu_to_le32 (skb->len | LastFrag);

	/* Increment cur_tx beक्रमe tasklet_schedule() */
	np->cur_tx++;
	mb();
	/* Schedule a tx_poll() task */
	tasklet_schedule(&np->tx_tasklet);

	/* On some architectures: explicitly flush cache lines here. */
	अगर (np->cur_tx - np->dirty_tx < TX_QUEUE_LEN - 1 &&
	    !netअगर_queue_stopped(dev)) अणु
		/* करो nothing */
	पूर्ण अन्यथा अणु
		netअगर_stop_queue (dev);
	पूर्ण
	अगर (netअगर_msg_tx_queued(np)) अणु
		prपूर्णांकk (KERN_DEBUG
			"%s: Transmit frame #%d queued in slot %d.\n",
			dev->name, np->cur_tx, entry);
	पूर्ण
	वापस NETDEV_TX_OK;

drop_frame:
	dev_kमुक्त_skb_any(skb);
	np->tx_skbuff[entry] = शून्य;
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

/* Reset hardware tx and मुक्त all of tx buffers */
अटल पूर्णांक
reset_tx (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	/* Reset tx logic, TxListPtr will be cleaned */
	ioग_लिखो16 (TxDisable, ioaddr + MACCtrl1);
	sundance_reset(dev, (NetworkReset|FIFOReset|DMAReset|TxReset) << 16);

	/* मुक्त all tx skbuff */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		np->tx_ring[i].next_desc = 0;

		skb = np->tx_skbuff[i];
		अगर (skb) अणु
			dma_unmap_single(&np->pci_dev->dev,
				le32_to_cpu(np->tx_ring[i].frag[0].addr),
				skb->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(skb);
			np->tx_skbuff[i] = शून्य;
			dev->stats.tx_dropped++;
		पूर्ण
	पूर्ण
	np->cur_tx = np->dirty_tx = 0;
	np->cur_task = 0;

	np->last_tx = शून्य;
	ioग_लिखो8(127, ioaddr + TxDMAPollPeriod);

	ioग_लिखो16 (StatsEnable | RxEnable | TxEnable, ioaddr + MACCtrl1);
	वापस 0;
पूर्ण

/* The पूर्णांकerrupt handler cleans up after the Tx thपढ़ो,
   and schedule a Rx thपढ़ो work */
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_instance;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	पूर्णांक hw_frame_id;
	पूर्णांक tx_cnt;
	पूर्णांक tx_status;
	पूर्णांक handled = 0;
	पूर्णांक i;

	करो अणु
		पूर्णांक पूर्णांकr_status = ioपढ़ो16(ioaddr + IntrStatus);
		ioग_लिखो16(पूर्णांकr_status, ioaddr + IntrStatus);

		अगर (netअगर_msg_पूर्णांकr(np))
			prपूर्णांकk(KERN_DEBUG "%s: Interrupt, status %4.4x.\n",
				   dev->name, पूर्णांकr_status);

		अगर (!(पूर्णांकr_status & DEFAULT_INTR))
			अवरोध;

		handled = 1;

		अगर (पूर्णांकr_status & (IntrRxDMADone)) अणु
			ioग_लिखो16(DEFAULT_INTR & ~(IntrRxDone|IntrRxDMADone),
					ioaddr + IntrEnable);
			अगर (np->budget < 0)
				np->budget = RX_BUDGET;
			tasklet_schedule(&np->rx_tasklet);
		पूर्ण
		अगर (पूर्णांकr_status & (IntrTxDone | IntrDrvRqst)) अणु
			tx_status = ioपढ़ो16 (ioaddr + TxStatus);
			क्रम (tx_cnt=32; tx_status & 0x80; --tx_cnt) अणु
				अगर (netअगर_msg_tx_करोne(np))
					prपूर्णांकk
					    ("%s: Transmit status is %2.2x.\n",
				     	dev->name, tx_status);
				अगर (tx_status & 0x1e) अणु
					अगर (netअगर_msg_tx_err(np))
						prपूर्णांकk("%s: Transmit error status %4.4x.\n",
							   dev->name, tx_status);
					dev->stats.tx_errors++;
					अगर (tx_status & 0x10)
						dev->stats.tx_fअगरo_errors++;
					अगर (tx_status & 0x08)
						dev->stats.collisions++;
					अगर (tx_status & 0x04)
						dev->stats.tx_fअगरo_errors++;
					अगर (tx_status & 0x02)
						dev->stats.tx_winकरोw_errors++;

					/*
					** This reset has been verअगरied on
					** DFE-580TX boards ! phdm@macqel.be.
					*/
					अगर (tx_status & 0x10) अणु	/* TxUnderrun */
						/* Restart Tx FIFO and transmitter */
						sundance_reset(dev, (NetworkReset|FIFOReset|TxReset) << 16);
						/* No need to reset the Tx poपूर्णांकer here */
					पूर्ण
					/* Restart the Tx. Need to make sure tx enabled */
					i = 10;
					करो अणु
						ioग_लिखो16(ioपढ़ो16(ioaddr + MACCtrl1) | TxEnable, ioaddr + MACCtrl1);
						अगर (ioपढ़ो16(ioaddr + MACCtrl1) & TxEnabled)
							अवरोध;
						mdelay(1);
					पूर्ण जबतक (--i);
				पूर्ण
				/* Yup, this is a करोcumentation bug.  It cost me *hours*. */
				ioग_लिखो16 (0, ioaddr + TxStatus);
				अगर (tx_cnt < 0) अणु
					ioग_लिखो32(5000, ioaddr + DownCounter);
					अवरोध;
				पूर्ण
				tx_status = ioपढ़ो16 (ioaddr + TxStatus);
			पूर्ण
			hw_frame_id = (tx_status >> 8) & 0xff;
		पूर्ण अन्यथा 	अणु
			hw_frame_id = ioपढ़ो8(ioaddr + TxFrameId);
		पूर्ण

		अगर (np->pci_dev->revision >= 0x14) अणु
			spin_lock(&np->lock);
			क्रम (; np->cur_tx - np->dirty_tx > 0; np->dirty_tx++) अणु
				पूर्णांक entry = np->dirty_tx % TX_RING_SIZE;
				काष्ठा sk_buff *skb;
				पूर्णांक sw_frame_id;
				sw_frame_id = (le32_to_cpu(
					np->tx_ring[entry].status) >> 2) & 0xff;
				अगर (sw_frame_id == hw_frame_id &&
					!(le32_to_cpu(np->tx_ring[entry].status)
					& 0x00010000))
						अवरोध;
				अगर (sw_frame_id == (hw_frame_id + 1) %
					TX_RING_SIZE)
						अवरोध;
				skb = np->tx_skbuff[entry];
				/* Free the original skb. */
				dma_unmap_single(&np->pci_dev->dev,
					le32_to_cpu(np->tx_ring[entry].frag[0].addr),
					skb->len, DMA_TO_DEVICE);
				dev_consume_skb_irq(np->tx_skbuff[entry]);
				np->tx_skbuff[entry] = शून्य;
				np->tx_ring[entry].frag[0].addr = 0;
				np->tx_ring[entry].frag[0].length = 0;
			पूर्ण
			spin_unlock(&np->lock);
		पूर्ण अन्यथा अणु
			spin_lock(&np->lock);
			क्रम (; np->cur_tx - np->dirty_tx > 0; np->dirty_tx++) अणु
				पूर्णांक entry = np->dirty_tx % TX_RING_SIZE;
				काष्ठा sk_buff *skb;
				अगर (!(le32_to_cpu(np->tx_ring[entry].status)
							& 0x00010000))
					अवरोध;
				skb = np->tx_skbuff[entry];
				/* Free the original skb. */
				dma_unmap_single(&np->pci_dev->dev,
					le32_to_cpu(np->tx_ring[entry].frag[0].addr),
					skb->len, DMA_TO_DEVICE);
				dev_consume_skb_irq(np->tx_skbuff[entry]);
				np->tx_skbuff[entry] = शून्य;
				np->tx_ring[entry].frag[0].addr = 0;
				np->tx_ring[entry].frag[0].length = 0;
			पूर्ण
			spin_unlock(&np->lock);
		पूर्ण

		अगर (netअगर_queue_stopped(dev) &&
			np->cur_tx - np->dirty_tx < TX_QUEUE_LEN - 4) अणु
			/* The ring is no दीर्घer full, clear busy flag. */
			netअगर_wake_queue (dev);
		पूर्ण
		/* Abnormal error summary/uncommon events handlers. */
		अगर (पूर्णांकr_status & (IntrPCIErr | LinkChange | StatsMax))
			netdev_error(dev, पूर्णांकr_status);
	पूर्ण जबतक (0);
	अगर (netअगर_msg_पूर्णांकr(np))
		prपूर्णांकk(KERN_DEBUG "%s: exiting interrupt, status=%#4.4x.\n",
			   dev->name, ioपढ़ो16(ioaddr + IntrStatus));
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम rx_poll(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा netdev_निजी *np = from_tasklet(np, t, rx_tasklet);
	काष्ठा net_device *dev = np->ndev;
	पूर्णांक entry = np->cur_rx % RX_RING_SIZE;
	पूर्णांक boguscnt = np->budget;
	व्योम __iomem *ioaddr = np->base;
	पूर्णांक received = 0;

	/* If EOP is set on the next entry, it's a new packet. Send it up. */
	जबतक (1) अणु
		काष्ठा netdev_desc *desc = &(np->rx_ring[entry]);
		u32 frame_status = le32_to_cpu(desc->status);
		पूर्णांक pkt_len;

		अगर (--boguscnt < 0) अणु
			जाओ not_करोne;
		पूर्ण
		अगर (!(frame_status & DescOwn))
			अवरोध;
		pkt_len = frame_status & 0x1fff;	/* Chip omits the CRC. */
		अगर (netअगर_msg_rx_status(np))
			prपूर्णांकk(KERN_DEBUG "  netdev_rx() status was %8.8x.\n",
				   frame_status);
		अगर (frame_status & 0x001f4000) अणु
			/* There was a error. */
			अगर (netअगर_msg_rx_err(np))
				prपूर्णांकk(KERN_DEBUG "  netdev_rx() Rx error was %8.8x.\n",
					   frame_status);
			dev->stats.rx_errors++;
			अगर (frame_status & 0x00100000)
				dev->stats.rx_length_errors++;
			अगर (frame_status & 0x00010000)
				dev->stats.rx_fअगरo_errors++;
			अगर (frame_status & 0x00060000)
				dev->stats.rx_frame_errors++;
			अगर (frame_status & 0x00080000)
				dev->stats.rx_crc_errors++;
			अगर (frame_status & 0x00100000) अणु
				prपूर्णांकk(KERN_WARNING "%s: Oversized Ethernet frame,"
					   " status %8.8x.\n",
					   dev->name, frame_status);
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb;
#अगर_अघोषित final_version
			अगर (netअगर_msg_rx_status(np))
				prपूर्णांकk(KERN_DEBUG "  netdev_rx() normal Rx pkt length %d"
					   ", bogus_cnt %d.\n",
					   pkt_len, boguscnt);
#पूर्ण_अगर
			/* Check अगर the packet is दीर्घ enough to accept without copying
			   to a minimally-sized skbuff. */
			अगर (pkt_len < rx_copyअवरोध &&
			    (skb = netdev_alloc_skb(dev, pkt_len + 2)) != शून्य) अणु
				skb_reserve(skb, 2);	/* 16 byte align the IP header */
				dma_sync_single_क्रम_cpu(&np->pci_dev->dev,
						le32_to_cpu(desc->frag[0].addr),
						np->rx_buf_sz, DMA_FROM_DEVICE);
				skb_copy_to_linear_data(skb, np->rx_skbuff[entry]->data, pkt_len);
				dma_sync_single_क्रम_device(&np->pci_dev->dev,
						le32_to_cpu(desc->frag[0].addr),
						np->rx_buf_sz, DMA_FROM_DEVICE);
				skb_put(skb, pkt_len);
			पूर्ण अन्यथा अणु
				dma_unmap_single(&np->pci_dev->dev,
					le32_to_cpu(desc->frag[0].addr),
					np->rx_buf_sz, DMA_FROM_DEVICE);
				skb_put(skb = np->rx_skbuff[entry], pkt_len);
				np->rx_skbuff[entry] = शून्य;
			पूर्ण
			skb->protocol = eth_type_trans(skb, dev);
			/* Note: checksum -> skb->ip_summed = CHECKSUM_UNNECESSARY; */
			netअगर_rx(skb);
		पूर्ण
		entry = (entry + 1) % RX_RING_SIZE;
		received++;
	पूर्ण
	np->cur_rx = entry;
	refill_rx (dev);
	np->budget -= received;
	ioग_लिखो16(DEFAULT_INTR, ioaddr + IntrEnable);
	वापस;

not_करोne:
	np->cur_rx = entry;
	refill_rx (dev);
	अगर (!received)
		received = 1;
	np->budget -= received;
	अगर (np->budget <= 0)
		np->budget = RX_BUDGET;
	tasklet_schedule(&np->rx_tasklet);
पूर्ण

अटल व्योम refill_rx (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक entry;
	पूर्णांक cnt = 0;

	/* Refill the Rx ring buffers. */
	क्रम (;(np->cur_rx - np->dirty_rx + RX_RING_SIZE) % RX_RING_SIZE > 0;
		np->dirty_rx = (np->dirty_rx + 1) % RX_RING_SIZE) अणु
		काष्ठा sk_buff *skb;
		entry = np->dirty_rx % RX_RING_SIZE;
		अगर (np->rx_skbuff[entry] == शून्य) अणु
			skb = netdev_alloc_skb(dev, np->rx_buf_sz + 2);
			np->rx_skbuff[entry] = skb;
			अगर (skb == शून्य)
				अवरोध;		/* Better luck next round. */
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			np->rx_ring[entry].frag[0].addr = cpu_to_le32(
				dma_map_single(&np->pci_dev->dev, skb->data,
					np->rx_buf_sz, DMA_FROM_DEVICE));
			अगर (dma_mapping_error(&np->pci_dev->dev,
				    np->rx_ring[entry].frag[0].addr)) अणु
			    dev_kमुक्त_skb_irq(skb);
			    np->rx_skbuff[entry] = शून्य;
			    अवरोध;
			पूर्ण
		पूर्ण
		/* Perhaps we need not reset this field. */
		np->rx_ring[entry].frag[0].length =
			cpu_to_le32(np->rx_buf_sz | LastFrag);
		np->rx_ring[entry].status = 0;
		cnt++;
	पूर्ण
पूर्ण
अटल व्योम netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	u16 mii_ctl, mii_advertise, mii_lpa;
	पूर्णांक speed;

	अगर (पूर्णांकr_status & LinkChange) अणु
		अगर (mdio_रुको_link(dev, 10) == 0) अणु
			prपूर्णांकk(KERN_INFO "%s: Link up\n", dev->name);
			अगर (np->an_enable) अणु
				mii_advertise = mdio_पढ़ो(dev, np->phys[0],
							   MII_ADVERTISE);
				mii_lpa = mdio_पढ़ो(dev, np->phys[0], MII_LPA);
				mii_advertise &= mii_lpa;
				prपूर्णांकk(KERN_INFO "%s: Link changed: ",
					dev->name);
				अगर (mii_advertise & ADVERTISE_100FULL) अणु
					np->speed = 100;
					prपूर्णांकk("100Mbps, full duplex\n");
				पूर्ण अन्यथा अगर (mii_advertise & ADVERTISE_100HALF) अणु
					np->speed = 100;
					prपूर्णांकk("100Mbps, half duplex\n");
				पूर्ण अन्यथा अगर (mii_advertise & ADVERTISE_10FULL) अणु
					np->speed = 10;
					prपूर्णांकk("10Mbps, full duplex\n");
				पूर्ण अन्यथा अगर (mii_advertise & ADVERTISE_10HALF) अणु
					np->speed = 10;
					prपूर्णांकk("10Mbps, half duplex\n");
				पूर्ण अन्यथा
					prपूर्णांकk("\n");

			पूर्ण अन्यथा अणु
				mii_ctl = mdio_पढ़ो(dev, np->phys[0], MII_BMCR);
				speed = (mii_ctl & BMCR_SPEED100) ? 100 : 10;
				np->speed = speed;
				prपूर्णांकk(KERN_INFO "%s: Link changed: %dMbps ,",
					dev->name, speed);
				prपूर्णांकk("%s duplex.\n",
					(mii_ctl & BMCR_FULLDPLX) ?
						"full" : "half");
			पूर्ण
			check_duplex(dev);
			अगर (np->flowctrl && np->mii_अगर.full_duplex) अणु
				ioग_लिखो16(ioपढ़ो16(ioaddr + MulticastFilter1+2) | 0x0200,
					ioaddr + MulticastFilter1+2);
				ioग_लिखो16(ioपढ़ो16(ioaddr + MACCtrl0) | EnbFlowCtrl,
					ioaddr + MACCtrl0);
			पूर्ण
			netअगर_carrier_on(dev);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_INFO "%s: Link down\n", dev->name);
			netअगर_carrier_off(dev);
		पूर्ण
	पूर्ण
	अगर (पूर्णांकr_status & StatsMax) अणु
		get_stats(dev);
	पूर्ण
	अगर (पूर्णांकr_status & IntrPCIErr) अणु
		prपूर्णांकk(KERN_ERR "%s: Something Wicked happened! %4.4x.\n",
			   dev->name, पूर्णांकr_status);
		/* We must करो a global reset of DMA to जारी. */
	पूर्ण
पूर्ण

अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	अचिन्हित दीर्घ flags;
	u8 late_coll, single_coll, mult_coll;

	spin_lock_irqsave(&np->statlock, flags);
	/* The chip only need report frame silently dropped. */
	dev->stats.rx_missed_errors	+= ioपढ़ो8(ioaddr + RxMissed);
	dev->stats.tx_packets += ioपढ़ो16(ioaddr + TxFramesOK);
	dev->stats.rx_packets += ioपढ़ो16(ioaddr + RxFramesOK);
	dev->stats.tx_carrier_errors += ioपढ़ो8(ioaddr + StatsCarrierError);

	mult_coll = ioपढ़ो8(ioaddr + StatsMultiColl);
	np->xstats.tx_multiple_collisions += mult_coll;
	single_coll = ioपढ़ो8(ioaddr + StatsOneColl);
	np->xstats.tx_single_collisions += single_coll;
	late_coll = ioपढ़ो8(ioaddr + StatsLateColl);
	np->xstats.tx_late_collisions += late_coll;
	dev->stats.collisions += mult_coll
		+ single_coll
		+ late_coll;

	np->xstats.tx_deferred += ioपढ़ो8(ioaddr + StatsTxDefer);
	np->xstats.tx_deferred_excessive += ioपढ़ो8(ioaddr + StatsTxXSDefer);
	np->xstats.tx_पातed += ioपढ़ो8(ioaddr + StatsTxAbort);
	np->xstats.tx_bcasts += ioपढ़ो8(ioaddr + StatsBcastTx);
	np->xstats.rx_bcasts += ioपढ़ो8(ioaddr + StatsBcastRx);
	np->xstats.tx_mcasts += ioपढ़ो8(ioaddr + StatsMcastTx);
	np->xstats.rx_mcasts += ioपढ़ो8(ioaddr + StatsMcastRx);

	dev->stats.tx_bytes += ioपढ़ो16(ioaddr + TxOctetsLow);
	dev->stats.tx_bytes += ioपढ़ो16(ioaddr + TxOctetsHigh) << 16;
	dev->stats.rx_bytes += ioपढ़ो16(ioaddr + RxOctetsLow);
	dev->stats.rx_bytes += ioपढ़ो16(ioaddr + RxOctetsHigh) << 16;

	spin_unlock_irqrestore(&np->statlock, flags);

	वापस &dev->stats;
पूर्ण

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	u16 mc_filter[4];			/* Multicast hash filter */
	u32 rx_mode;
	पूर्णांक i;

	अगर (dev->flags & IFF_PROMISC) अणु			/* Set promiscuous. */
		स_रखो(mc_filter, 0xff, माप(mc_filter));
		rx_mode = AcceptBroadcast | AcceptMulticast | AcceptAll | AcceptMyPhys;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to match, or accept all multicasts. */
		स_रखो(mc_filter, 0xff, माप(mc_filter));
		rx_mode = AcceptBroadcast | AcceptMulticast | AcceptMyPhys;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक bit;
		पूर्णांक index;
		पूर्णांक crc;
		स_रखो (mc_filter, 0, माप (mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			crc = ether_crc_le(ETH_ALEN, ha->addr);
			क्रम (index=0, bit=0; bit < 6; bit++, crc <<= 1)
				अगर (crc & 0x80000000) index |= 1 << bit;
			mc_filter[index/16] |= (1 << (index % 16));
		पूर्ण
		rx_mode = AcceptBroadcast | AcceptMultiHash | AcceptMyPhys;
	पूर्ण अन्यथा अणु
		ioग_लिखो8(AcceptBroadcast | AcceptMyPhys, ioaddr + RxMode);
		वापस;
	पूर्ण
	अगर (np->mii_अगर.full_duplex && np->flowctrl)
		mc_filter[3] |= 0x0200;

	क्रम (i = 0; i < 4; i++)
		ioग_लिखो16(mc_filter[i], ioaddr + MulticastFilter0 + i*2);
	ioग_लिखो8(rx_mode, ioaddr + RxMode);
पूर्ण

अटल पूर्णांक __set_mac_addr(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u16 addr16;

	addr16 = (dev->dev_addr[0] | (dev->dev_addr[1] << 8));
	ioग_लिखो16(addr16, np->base + StationAddr);
	addr16 = (dev->dev_addr[2] | (dev->dev_addr[3] << 8));
	ioग_लिखो16(addr16, np->base + StationAddr+2);
	addr16 = (dev->dev_addr[4] | (dev->dev_addr[5] << 8));
	ioग_लिखो16(addr16, np->base + StationAddr+4);
	वापस 0;
पूर्ण

/* Invoked with rtnl_lock held */
अटल पूर्णांक sundance_set_mac_addr(काष्ठा net_device *dev, व्योम *data)
अणु
	स्थिर काष्ठा sockaddr *addr = data;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;
	स_नकल(dev->dev_addr, addr->sa_data, ETH_ALEN);
	__set_mac_addr(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर name[ETH_GSTRING_LEN];
पूर्ण sundance_stats[] = अणु
	अणु "tx_multiple_collisions" पूर्ण,
	अणु "tx_single_collisions" पूर्ण,
	अणु "tx_late_collisions" पूर्ण,
	अणु "tx_deferred" पूर्ण,
	अणु "tx_deferred_excessive" पूर्ण,
	अणु "tx_aborted" पूर्ण,
	अणु "tx_bcasts" पूर्ण,
	अणु "rx_bcasts" पूर्ण,
	अणु "tx_mcasts" पूर्ण,
	अणु "rx_mcasts" पूर्ण,
पूर्ण;

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
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस np->msg_enable;
पूर्ण

अटल व्योम set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	np->msg_enable = val;
पूर्ण

अटल व्योम get_strings(काष्ठा net_device *dev, u32 stringset,
		u8 *data)
अणु
	अगर (stringset == ETH_SS_STATS)
		स_नकल(data, sundance_stats, माप(sundance_stats));
पूर्ण

अटल पूर्णांक get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(sundance_stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम get_ethtool_stats(काष्ठा net_device *dev,
		काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i = 0;

	get_stats(dev);
	data[i++] = np->xstats.tx_multiple_collisions;
	data[i++] = np->xstats.tx_single_collisions;
	data[i++] = np->xstats.tx_late_collisions;
	data[i++] = np->xstats.tx_deferred;
	data[i++] = np->xstats.tx_deferred_excessive;
	data[i++] = np->xstats.tx_पातed;
	data[i++] = np->xstats.tx_bcasts;
	data[i++] = np->xstats.rx_bcasts;
	data[i++] = np->xstats.tx_mcasts;
	data[i++] = np->xstats.rx_mcasts;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल व्योम sundance_get_wol(काष्ठा net_device *dev,
		काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	u8 wol_bits;

	wol->wolopts = 0;

	wol->supported = (WAKE_PHY | WAKE_MAGIC);
	अगर (!np->wol_enabled)
		वापस;

	wol_bits = ioपढ़ो8(ioaddr + WakeEvent);
	अगर (wol_bits & MagicPktEnable)
		wol->wolopts |= WAKE_MAGIC;
	अगर (wol_bits & LinkEventEnable)
		wol->wolopts |= WAKE_PHY;
पूर्ण

अटल पूर्णांक sundance_set_wol(काष्ठा net_device *dev,
	काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	u8 wol_bits;

	अगर (!device_can_wakeup(&np->pci_dev->dev))
		वापस -EOPNOTSUPP;

	np->wol_enabled = !!(wol->wolopts);
	wol_bits = ioपढ़ो8(ioaddr + WakeEvent);
	wol_bits &= ~(WakePktEnable | MagicPktEnable |
			LinkEventEnable | WolEnable);

	अगर (np->wol_enabled) अणु
		अगर (wol->wolopts & WAKE_MAGIC)
			wol_bits |= (MagicPktEnable | WolEnable);
		अगर (wol->wolopts & WAKE_PHY)
			wol_bits |= (LinkEventEnable | WolEnable);
	पूर्ण
	ioग_लिखो8(wol_bits, ioaddr + WakeEvent);

	device_set_wakeup_enable(&np->pci_dev->dev, np->wol_enabled);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा sundance_get_wol शून्य
#घोषणा sundance_set_wol शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.begin = check_अगर_running,
	.get_drvinfo = get_drvinfo,
	.nway_reset = nway_reset,
	.get_link = get_link,
	.get_wol = sundance_get_wol,
	.set_wol = sundance_set_wol,
	.get_msglevel = get_msglevel,
	.set_msglevel = set_msglevel,
	.get_strings = get_strings,
	.get_sset_count = get_sset_count,
	.get_ethtool_stats = get_ethtool_stats,
	.get_link_ksettings = get_link_ksettings,
	.set_link_ksettings = set_link_ksettings,
पूर्ण;

अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक rc;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	spin_lock_irq(&np->lock);
	rc = generic_mii_ioctl(&np->mii_अगर, अगर_mii(rq), cmd, शून्य);
	spin_unlock_irq(&np->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक netdev_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	/* Wait and समाप्त tasklet */
	tasklet_समाप्त(&np->rx_tasklet);
	tasklet_समाप्त(&np->tx_tasklet);
	np->cur_tx = 0;
	np->dirty_tx = 0;
	np->cur_task = 0;
	np->last_tx = शून्य;

	netअगर_stop_queue(dev);

	अगर (netअगर_msg_अगरकरोwn(np)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Shutting down ethercard, status was Tx %2.2x "
			   "Rx %4.4x Int %2.2x.\n",
			   dev->name, ioपढ़ो8(ioaddr + TxStatus),
			   ioपढ़ो32(ioaddr + RxStatus), ioपढ़ो16(ioaddr + IntrStatus));
		prपूर्णांकk(KERN_DEBUG "%s: Queue pointers were Tx %d / %d,  Rx %d / %d.\n",
			   dev->name, np->cur_tx, np->dirty_tx, np->cur_rx, np->dirty_rx);
	पूर्ण

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	ioग_लिखो16(0x0000, ioaddr + IntrEnable);

	/* Disable Rx and Tx DMA क्रम safely release resource */
	ioग_लिखो32(0x500, ioaddr + DMACtrl);

	/* Stop the chip's Tx and Rx processes. */
	ioग_लिखो16(TxDisable | RxDisable | StatsDisable, ioaddr + MACCtrl1);

    	क्रम (i = 2000; i > 0; i--) अणु
 		अगर ((ioपढ़ो32(ioaddr + DMACtrl) & 0xc000) == 0)
			अवरोध;
		mdelay(1);
    	पूर्ण

    	ioग_लिखो16(GlobalReset | DMAReset | FIFOReset | NetworkReset,
			ioaddr + ASIC_HI_WORD(ASICCtrl));

    	क्रम (i = 2000; i > 0; i--) अणु
		अगर ((ioपढ़ो16(ioaddr + ASIC_HI_WORD(ASICCtrl)) & ResetBusy) == 0)
			अवरोध;
		mdelay(1);
    	पूर्ण

#अगर_घोषित __i386__
	अगर (netअगर_msg_hw(np)) अणु
		prपूर्णांकk(KERN_DEBUG "  Tx ring at %8.8x:\n",
			   (पूर्णांक)(np->tx_ring_dma));
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			prपूर्णांकk(KERN_DEBUG " #%d desc. %4.4x %8.8x %8.8x.\n",
				   i, np->tx_ring[i].status, np->tx_ring[i].frag[0].addr,
				   np->tx_ring[i].frag[0].length);
		prपूर्णांकk(KERN_DEBUG "  Rx ring %8.8x:\n",
			   (पूर्णांक)(np->rx_ring_dma));
		क्रम (i = 0; i < /*RX_RING_SIZE*/4 ; i++) अणु
			prपूर्णांकk(KERN_DEBUG " #%d desc. %4.4x %4.4x %8.8x\n",
				   i, np->rx_ring[i].status, np->rx_ring[i].frag[0].addr,
				   np->rx_ring[i].frag[0].length);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* __i386__ debugging only */

	मुक्त_irq(np->pci_dev->irq, dev);

	del_समयr_sync(&np->समयr);

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		np->rx_ring[i].status = 0;
		skb = np->rx_skbuff[i];
		अगर (skb) अणु
			dma_unmap_single(&np->pci_dev->dev,
				le32_to_cpu(np->rx_ring[i].frag[0].addr),
				np->rx_buf_sz, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(skb);
			np->rx_skbuff[i] = शून्य;
		पूर्ण
		np->rx_ring[i].frag[0].addr = cpu_to_le32(0xBADF00D0); /* poison */
	पूर्ण
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		np->tx_ring[i].next_desc = 0;
		skb = np->tx_skbuff[i];
		अगर (skb) अणु
			dma_unmap_single(&np->pci_dev->dev,
				le32_to_cpu(np->tx_ring[i].frag[0].addr),
				skb->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb(skb);
			np->tx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sundance_हटाओ1(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
	    काष्ठा netdev_निजी *np = netdev_priv(dev);
	    unरेजिस्टर_netdev(dev);
	    dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE,
		    np->rx_ring, np->rx_ring_dma);
	    dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE,
		    np->tx_ring, np->tx_ring_dma);
	    pci_iounmap(pdev, np->base);
	    pci_release_regions(pdev);
	    मुक्त_netdev(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused sundance_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;

	अगर (!netअगर_running(dev))
		वापस 0;

	netdev_बंद(dev);
	netअगर_device_detach(dev);

	अगर (np->wol_enabled) अणु
		ioग_लिखो8(AcceptBroadcast | AcceptMyPhys, ioaddr + RxMode);
		ioग_लिखो16(RxEnable, ioaddr + MACCtrl1);
	पूर्ण

	device_set_wakeup_enable(dev_d, np->wol_enabled);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sundance_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	पूर्णांक err = 0;

	अगर (!netअगर_running(dev))
		वापस 0;

	err = netdev_खोलो(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Can't resume interface!\n",
				dev->name);
		जाओ out;
	पूर्ण

	netअगर_device_attach(dev);

out:
	वापस err;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sundance_pm_ops, sundance_suspend, sundance_resume);

अटल काष्ठा pci_driver sundance_driver = अणु
	.name		= DRV_NAME,
	.id_table	= sundance_pci_tbl,
	.probe		= sundance_probe1,
	.हटाओ		= sundance_हटाओ1,
	.driver.pm	= &sundance_pm_ops,
पूर्ण;

module_pci_driver(sundance_driver);
