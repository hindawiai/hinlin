<शैली गुरु>
/* yellowfin.c: A Packet Engines G-NIC ethernet driver क्रम linux. */
/*
	Written 1997-2001 by Donald Becker.

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	This driver is क्रम the Packet Engines G-NIC PCI Gigabit Ethernet adapter.
	It also supports the Symbios Logic version of the same chip core.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	Support and updates available at
	http://www.scyld.com/network/yellowfin.hपंचांगl
	[link no दीर्घer provides useful info -jgarzik]

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"yellowfin"
#घोषणा DRV_VERSION	"2.1"
#घोषणा DRV_RELDATE	"Sep 11, 2006"

/* The user-configurable values.
   These may be modअगरied when a driver module is loaded.*/

अटल पूर्णांक debug = 1;			/* 1 normal messages, 0 quiet .. 7 verbose. */
/* Maximum events (Rx packets, etc.) to handle at each पूर्णांकerrupt. */
अटल पूर्णांक max_पूर्णांकerrupt_work = 20;
अटल पूर्णांक mtu;
#अगर_घोषित YF_PROTOTYPE			/* Support क्रम prototype hardware errata. */
/* System-wide count of bogus-rx frames. */
अटल पूर्णांक bogus_rx;
अटल पूर्णांक dma_ctrl = 0x004A0263; 			/* Constrained by errata */
अटल पूर्णांक fअगरo_cfg = 0x0020;				/* Bypass बाह्यal Tx FIFO. */
#या_अगर defined(YF_NEW)					/* A future perfect board :->.  */
अटल पूर्णांक dma_ctrl = 0x00CAC277;			/* Override when loading module! */
अटल पूर्णांक fअगरo_cfg = 0x0028;
#अन्यथा
अटल स्थिर पूर्णांक dma_ctrl = 0x004A0263; 			/* Constrained by errata */
अटल स्थिर पूर्णांक fअगरo_cfg = 0x0020;				/* Bypass बाह्यal Tx FIFO. */
#पूर्ण_अगर

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
   Setting to > 1514 effectively disables this feature. */
अटल पूर्णांक rx_copyअवरोध;

/* Used to pass the media type, etc.
   No media types are currently defined.  These exist क्रम driver
   पूर्णांकeroperability.
*/
#घोषणा MAX_UNITS 8				/* More are supported, limit only on options */
अटल पूर्णांक options[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
अटल पूर्णांक full_duplex[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;

/* Do ugly workaround क्रम GX server chipset errata. */
अटल पूर्णांक gx_fix;

/* Operational parameters that are set at compile समय. */

/* Keep the ring sizes a घातer of two क्रम efficiency.
   Making the Tx ring too दीर्घ decreases the effectiveness of channel
   bonding and packet priority.
   There are no ill effects from too-large receive rings. */
#घोषणा TX_RING_SIZE	16
#घोषणा TX_QUEUE_SIZE	12		/* Must be > 4 && <= TX_RING_SIZE */
#घोषणा RX_RING_SIZE	64
#घोषणा STATUS_TOTAL_SIZE	TX_RING_SIZE*माप(काष्ठा tx_status_words)
#घोषणा TX_TOTAL_SIZE		2*TX_RING_SIZE*माप(काष्ठा yellowfin_desc)
#घोषणा RX_TOTAL_SIZE		RX_RING_SIZE*माप(काष्ठा yellowfin_desc)

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (2*HZ)
#घोषणा PKT_BUF_SZ		1536			/* Size of each temporary Rx buffer.*/

#घोषणा yellowfin_debug debug

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/mii.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>		/* Processor type क्रम cache alignment. */
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/पन.स>

/* These identअगरy the driver base version and may not be हटाओd. */
अटल स्थिर अक्षर version[] =
  KERN_INFO DRV_NAME ".c:v1.05  1/09/2001  Written by Donald Becker <becker@scyld.com>\n"
  "  (unofficial 2.4.x port, " DRV_VERSION ", " DRV_RELDATE ")\n";

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("Packet Engines Yellowfin G-NIC Gigabit Ethernet driver");
MODULE_LICENSE("GPL");

module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
module_param(mtu, पूर्णांक, 0);
module_param(debug, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
module_param(gx_fix, पूर्णांक, 0);
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "G-NIC maximum events handled per interrupt");
MODULE_PARM_DESC(mtu, "G-NIC MTU (all boards)");
MODULE_PARM_DESC(debug, "G-NIC debug level (0-7)");
MODULE_PARM_DESC(rx_copyअवरोध, "G-NIC copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(options, "G-NIC: Bits 0-3: media type, bit 17: full duplex");
MODULE_PARM_DESC(full_duplex, "G-NIC full duplex setting(s) (1)");
MODULE_PARM_DESC(gx_fix, "G-NIC: enable GX server chipset bug workaround (0-1)");

/*
				Theory of Operation

I. Board Compatibility

This device driver is deचिन्हित क्रम the Packet Engines "Yellowfin" Gigabit
Ethernet adapter.  The G-NIC 64-bit PCI card is supported, as well as the
Symbios 53C885E dual function chip.

II. Board-specअगरic settings

PCI bus devices are configured by the प्रणाली at boot समय, so no jumpers
need to be set on the board.  The प्रणाली BIOS preferably should assign the
PCI INTA संकेत to an otherwise unused प्रणाली IRQ line.
Note: Kernel versions earlier than 1.3.73 करो not support shared PCI
पूर्णांकerrupt lines.

III. Driver operation

IIIa. Ring buffers

The Yellowfin uses the Descriptor Based DMA Architecture specअगरied by Apple.
This is a descriptor list scheme similar to that used by the EEPro100 and
Tulip.  This driver uses two अटलally allocated fixed-size descriptor lists
क्रमmed पूर्णांकo rings by a branch from the final descriptor to the beginning of
the list.  The ring sizes are set at compile समय by RX/TX_RING_SIZE.

The driver allocates full frame size skbuffs क्रम the Rx ring buffers at
खोलो() समय and passes the skb->data field to the Yellowfin as receive data
buffers.  When an incoming frame is less than RX_COPYBREAK bytes दीर्घ,
a fresh skbuff is allocated and the frame is copied to the new skbuff.
When the incoming frame is larger, the skbuff is passed directly up the
protocol stack and replaced by a newly allocated skbuff.

The RX_COPYBREAK value is chosen to trade-off the memory wasted by
using a full-sized skbuff क्रम small frames vs. the copying costs of larger
frames.  For small frames the copying cost is negligible (esp. considering
that we are pre-loading the cache with immediately useful header
inक्रमmation).  For large frames the copying cost is non-trivial, and the
larger copy might flush the cache of useful data.

IIIC. Synchronization

The driver runs as two independent, single-thपढ़ोed flows of control.  One
is the send-packet routine, which enक्रमces single-thपढ़ोed use by the
dev->tbusy flag.  The other thपढ़ो is the पूर्णांकerrupt handler, which is single
thपढ़ोed by the hardware and other software.

The send packet thपढ़ो has partial control over the Tx ring and 'dev->tbusy'
flag.  It sets the tbusy flag whenever it's queuing a Tx packet. If the next
queue slot is empty, it clears the tbusy flag when finished otherwise it sets
the 'yp->tx_full' flag.

The पूर्णांकerrupt handler has exclusive control over the Rx ring and records stats
from the Tx ring.  After reaping the stats, it marks the Tx queue entry as
empty by incrementing the dirty_tx mark. Iff the 'yp->tx_full' flag is set, it
clears both the tx_full and tbusy flags.

IV. Notes

Thanks to Kim Stearns of Packet Engines क्रम providing a pair of G-NIC boards.
Thanks to Bruce Faust of Digitalscape क्रम providing both their SYM53C885 board
and an AlphaStation to verअगरty the Alpha port!

IVb. References

Yellowfin Engineering Design Specअगरication, 4/23/97 Preliminary/Confidential
Symbios SYM53C885 PCI-SCSI/Fast Ethernet Multअगरunction Controller Preliminary
   Data Manual v3.0
http://cesdis.gsfc.nasa.gov/linux/misc/NWay.hपंचांगl
http://cesdis.gsfc.nasa.gov/linux/misc/100mbps.hपंचांगl

IVc. Errata

See Packet Engines confidential appendix (prototype chips only).
*/



क्रमागत capability_flags अणु
	HasMII=1, FullTxStatus=2, IsGigabit=4, HasMulticastBug=8, FullRxStatus=16,
	HasMACAddrBug=32, /* Only on early revs.  */
	DontUseEeprom=64, /* Don't पढ़ो the MAC from the EEPROm. */
पूर्ण;

/* The PCI I/O space extent. */
क्रमागत अणु
	YELLOWFIN_SIZE	= 0x100,
पूर्ण;

काष्ठा pci_id_info अणु
        स्थिर अक्षर *name;
        काष्ठा match_info अणु
                पूर्णांक     pci, pci_mask, subप्रणाली, subप्रणाली_mask;
                पूर्णांक revision, revision_mask;                            /* Only 8 bits. */
        पूर्ण id;
        पूर्णांक drv_flags;                          /* Driver use, पूर्णांकended as capability flags. */
पूर्ण;

अटल स्थिर काष्ठा pci_id_info pci_id_tbl[] = अणु
	अणु"Yellowfin G-NIC Gigabit Ethernet", अणु 0x07021000, 0xffffffffपूर्ण,
	 FullTxStatus | IsGigabit | HasMulticastBug | HasMACAddrBug | DontUseEepromपूर्ण,
	अणु"Symbios SYM83C885", अणु 0x07011000, 0xffffffffपूर्ण,
	  HasMII | DontUseEeprom पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id yellowfin_pci_tbl[] = अणु
	अणु 0x1000, 0x0702, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0x1000, 0x0701, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (pci, yellowfin_pci_tbl);


/* Offsets to the Yellowfin रेजिस्टरs.  Various sizes and alignments. */
क्रमागत yellowfin_offsets अणु
	TxCtrl=0x00, TxStatus=0x04, TxPtr=0x0C,
	TxIntrSel=0x10, TxBranchSel=0x14, TxWaitSel=0x18,
	RxCtrl=0x40, RxStatus=0x44, RxPtr=0x4C,
	RxIntrSel=0x50, RxBranchSel=0x54, RxWaitSel=0x58,
	EventStatus=0x80, IntrEnb=0x82, IntrClear=0x84, IntrStatus=0x86,
	ChipRev=0x8C, DMACtrl=0x90, TxThreshold=0x94,
	Cnfg=0xA0, FrameGap0=0xA2, FrameGap1=0xA4,
	MII_Cmd=0xA6, MII_Addr=0xA8, MII_Wr_Data=0xAA, MII_Rd_Data=0xAC,
	MII_Status=0xAE,
	RxDepth=0xB8, FlowCtrl=0xBC,
	AddrMode=0xD0, StnAddr=0xD2, HashTbl=0xD8, FIFOcfg=0xF8,
	EEStatus=0xF0, EECtrl=0xF1, EEAddr=0xF2, EERead=0xF3, EEWrite=0xF4,
	EEFeature=0xF5,
पूर्ण;

/* The Yellowfin Rx and Tx buffer descriptors.
   Elements are written as 32 bit क्रम endian portability. */
काष्ठा yellowfin_desc अणु
	__le32 dbdma_cmd;
	__le32 addr;
	__le32 branch_addr;
	__le32 result_status;
पूर्ण;

काष्ठा tx_status_words अणु
#अगर_घोषित __BIG_ENDIAN
	u16 tx_errs;
	u16 tx_cnt;
	u16 छोड़ोd;
	u16 total_tx_cnt;
#अन्यथा  /* Little endian chips. */
	u16 tx_cnt;
	u16 tx_errs;
	u16 total_tx_cnt;
	u16 छोड़ोd;
#पूर्ण_अगर /* __BIG_ENDIAN */
पूर्ण;

/* Bits in yellowfin_desc.cmd */
क्रमागत desc_cmd_bits अणु
	CMD_TX_PKT=0x10000000, CMD_RX_BUF=0x20000000, CMD_TXSTATUS=0x30000000,
	CMD_NOP=0x60000000, CMD_STOP=0x70000000,
	BRANCH_ALWAYS=0x0C0000, INTR_ALWAYS=0x300000, WAIT_ALWAYS=0x030000,
	BRANCH_IFTRUE=0x040000,
पूर्ण;

/* Bits in yellowfin_desc.status */
क्रमागत desc_status_bits अणु RX_EOP=0x0040, पूर्ण;

/* Bits in the पूर्णांकerrupt status/mask रेजिस्टरs. */
क्रमागत पूर्णांकr_status_bits अणु
	IntrRxDone=0x01, IntrRxInvalid=0x02, IntrRxPCIFault=0x04,IntrRxPCIErr=0x08,
	IntrTxDone=0x10, IntrTxInvalid=0x20, IntrTxPCIFault=0x40,IntrTxPCIErr=0x80,
	IntrEarlyRx=0x100, IntrWakeup=0x200, पूर्ण;

#घोषणा PRIV_ALIGN	31 	/* Required alignment mask */
#घोषणा MII_CNT		4
काष्ठा yellowfin_निजी अणु
	/* Descriptor rings first क्रम alignment.
	   Tx requires a second descriptor क्रम status. */
	काष्ठा yellowfin_desc *rx_ring;
	काष्ठा yellowfin_desc *tx_ring;
	काष्ठा sk_buff* rx_skbuff[RX_RING_SIZE];
	काष्ठा sk_buff* tx_skbuff[TX_RING_SIZE];
	dma_addr_t rx_ring_dma;
	dma_addr_t tx_ring_dma;

	काष्ठा tx_status_words *tx_status;
	dma_addr_t tx_status_dma;

	काष्ठा समयr_list समयr;	/* Media selection समयr. */
	/* Frequently used and paired value: keep adjacent क्रम cache effect. */
	पूर्णांक chip_id, drv_flags;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित पूर्णांक cur_rx, dirty_rx;		/* Producer/consumer ring indices */
	अचिन्हित पूर्णांक rx_buf_sz;				/* Based on MTU+slack. */
	काष्ठा tx_status_words *tx_tail_desc;
	अचिन्हित पूर्णांक cur_tx, dirty_tx;
	पूर्णांक tx_threshold;
	अचिन्हित पूर्णांक tx_full:1;				/* The Tx queue is full. */
	अचिन्हित पूर्णांक full_duplex:1;			/* Full-duplex operation requested. */
	अचिन्हित पूर्णांक duplex_lock:1;
	अचिन्हित पूर्णांक medialock:1;			/* Do not sense media. */
	अचिन्हित पूर्णांक शेष_port:4;		/* Last dev->अगर_port value. */
	/* MII transceiver section. */
	पूर्णांक mii_cnt;						/* MII device addresses. */
	u16 advertising;					/* NWay media advertisement */
	अचिन्हित अक्षर phys[MII_CNT];		/* MII device addresses, only first one used */
	spinlock_t lock;
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक पढ़ो_eeprom(व्योम __iomem *ioaddr, पूर्णांक location);
अटल पूर्णांक mdio_पढ़ो(व्योम __iomem *ioaddr, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(व्योम __iomem *ioaddr, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value);
अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल पूर्णांक yellowfin_खोलो(काष्ठा net_device *dev);
अटल व्योम yellowfin_समयr(काष्ठा समयr_list *t);
अटल व्योम yellowfin_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल पूर्णांक yellowfin_init_ring(काष्ठा net_device *dev);
अटल netdev_tx_t yellowfin_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev);
अटल irqवापस_t yellowfin_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल पूर्णांक yellowfin_rx(काष्ठा net_device *dev);
अटल व्योम yellowfin_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status);
अटल पूर्णांक yellowfin_बंद(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops ethtool_ops;

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो 		= yellowfin_खोलो,
	.nकरो_stop 		= yellowfin_बंद,
	.nकरो_start_xmit 	= yellowfin_start_xmit,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_करो_ioctl 		= netdev_ioctl,
	.nकरो_tx_समयout 	= yellowfin_tx_समयout,
पूर्ण;

अटल पूर्णांक yellowfin_init_one(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा yellowfin_निजी *np;
	पूर्णांक irq;
	पूर्णांक chip_idx = ent->driver_data;
	अटल पूर्णांक find_cnt;
	व्योम __iomem *ioaddr;
	पूर्णांक i, option = find_cnt < MAX_UNITS ? options[find_cnt] : 0;
	पूर्णांक drv_flags = pci_id_tbl[chip_idx].drv_flags;
        व्योम *ring_space;
        dma_addr_t ring_dma;
#अगर_घोषित USE_IO_OPS
	पूर्णांक bar = 0;
#अन्यथा
	पूर्णांक bar = 1;
#पूर्ण_अगर

/* when built पूर्णांकo the kernel, we only prपूर्णांक version अगर device is found */
#अगर_अघोषित MODULE
	अटल पूर्णांक prपूर्णांकed_version;
	अगर (!prपूर्णांकed_version++)
		prपूर्णांकk(version);
#पूर्ण_अगर

	i = pci_enable_device(pdev);
	अगर (i) वापस i;

	dev = alloc_etherdev(माप(*np));
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);

	np = netdev_priv(dev);

	अगर (pci_request_regions(pdev, DRV_NAME))
		जाओ err_out_मुक्त_netdev;

	pci_set_master (pdev);

	ioaddr = pci_iomap(pdev, bar, YELLOWFIN_SIZE);
	अगर (!ioaddr)
		जाओ err_out_मुक्त_res;

	irq = pdev->irq;

	अगर (drv_flags & DontUseEeprom)
		क्रम (i = 0; i < 6; i++)
			dev->dev_addr[i] = ioपढ़ो8(ioaddr + StnAddr + i);
	अन्यथा अणु
		पूर्णांक ee_offset = (पढ़ो_eeprom(ioaddr, 6) == 0xff ? 0x100 : 0);
		क्रम (i = 0; i < 6; i++)
			dev->dev_addr[i] = पढ़ो_eeprom(ioaddr, ee_offset + i);
	पूर्ण

	/* Reset the chip. */
	ioग_लिखो32(0x80000000, ioaddr + DMACtrl);

	pci_set_drvdata(pdev, dev);
	spin_lock_init(&np->lock);

	np->pci_dev = pdev;
	np->chip_id = chip_idx;
	np->drv_flags = drv_flags;
	np->base = ioaddr;

	ring_space = dma_alloc_coherent(&pdev->dev, TX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_cleardev;
	np->tx_ring = ring_space;
	np->tx_ring_dma = ring_dma;

	ring_space = dma_alloc_coherent(&pdev->dev, RX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_unmap_tx;
	np->rx_ring = ring_space;
	np->rx_ring_dma = ring_dma;

	ring_space = dma_alloc_coherent(&pdev->dev, STATUS_TOTAL_SIZE,
					&ring_dma, GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_unmap_rx;
	np->tx_status = ring_space;
	np->tx_status_dma = ring_dma;

	अगर (dev->mem_start)
		option = dev->mem_start;

	/* The lower four bits are the media type. */
	अगर (option > 0) अणु
		अगर (option & 0x200)
			np->full_duplex = 1;
		np->शेष_port = option & 15;
		अगर (np->शेष_port)
			np->medialock = 1;
	पूर्ण
	अगर (find_cnt < MAX_UNITS  &&  full_duplex[find_cnt] > 0)
		np->full_duplex = 1;

	अगर (np->full_duplex)
		np->duplex_lock = 1;

	/* The Yellowfin-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &netdev_ops;
	dev->ethtool_ops = &ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	अगर (mtu)
		dev->mtu = mtu;

	i = रेजिस्टर_netdev(dev);
	अगर (i)
		जाओ err_out_unmap_status;

	netdev_info(dev, "%s type %8x at %p, %pM, IRQ %d\n",
		    pci_id_tbl[chip_idx].name,
		    ioपढ़ो32(ioaddr + ChipRev), ioaddr,
		    dev->dev_addr, irq);

	अगर (np->drv_flags & HasMII) अणु
		पूर्णांक phy, phy_idx = 0;
		क्रम (phy = 0; phy < 32 && phy_idx < MII_CNT; phy++) अणु
			पूर्णांक mii_status = mdio_पढ़ो(ioaddr, phy, 1);
			अगर (mii_status != 0xffff  &&  mii_status != 0x0000) अणु
				np->phys[phy_idx++] = phy;
				np->advertising = mdio_पढ़ो(ioaddr, phy, 4);
				netdev_info(dev, "MII PHY found at address %d, status 0x%04x advertising %04x\n",
					    phy, mii_status, np->advertising);
			पूर्ण
		पूर्ण
		np->mii_cnt = phy_idx;
	पूर्ण

	find_cnt++;

	वापस 0;

err_out_unmap_status:
	dma_मुक्त_coherent(&pdev->dev, STATUS_TOTAL_SIZE, np->tx_status,
			  np->tx_status_dma);
err_out_unmap_rx:
	dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, np->rx_ring,
			  np->rx_ring_dma);
err_out_unmap_tx:
	dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, np->tx_ring,
			  np->tx_ring_dma);
err_out_cleardev:
	pci_iounmap(pdev, ioaddr);
err_out_मुक्त_res:
	pci_release_regions(pdev);
err_out_मुक्त_netdev:
	मुक्त_netdev (dev);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक पढ़ो_eeprom(व्योम __iomem *ioaddr, पूर्णांक location)
अणु
	पूर्णांक bogus_cnt = 10000;		/* Typical 33Mhz: 1050 ticks */

	ioग_लिखो8(location, ioaddr + EEAddr);
	ioग_लिखो8(0x30 | ((location >> 8) & 7), ioaddr + EECtrl);
	जबतक ((ioपढ़ो8(ioaddr + EEStatus) & 0x80)  &&  --bogus_cnt > 0)
		;
	वापस ioपढ़ो8(ioaddr + EERead);
पूर्ण

/* MII Managemen Data I/O accesses.
   These routines assume the MDIO controller is idle, and करो not निकास until
   the command is finished. */

अटल पूर्णांक mdio_पढ़ो(व्योम __iomem *ioaddr, पूर्णांक phy_id, पूर्णांक location)
अणु
	पूर्णांक i;

	ioग_लिखो16((phy_id<<8) + location, ioaddr + MII_Addr);
	ioग_लिखो16(1, ioaddr + MII_Cmd);
	क्रम (i = 10000; i >= 0; i--)
		अगर ((ioपढ़ो16(ioaddr + MII_Status) & 1) == 0)
			अवरोध;
	वापस ioपढ़ो16(ioaddr + MII_Rd_Data);
पूर्ण

अटल व्योम mdio_ग_लिखो(व्योम __iomem *ioaddr, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value)
अणु
	पूर्णांक i;

	ioग_लिखो16((phy_id<<8) + location, ioaddr + MII_Addr);
	ioग_लिखो16(value, ioaddr + MII_Wr_Data);

	/* Wait क्रम the command to finish. */
	क्रम (i = 10000; i >= 0; i--)
		अगर ((ioपढ़ो16(ioaddr + MII_Status) & 1) == 0)
			अवरोध;
पूर्ण


अटल पूर्णांक yellowfin_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा yellowfin_निजी *yp = netdev_priv(dev);
	स्थिर पूर्णांक irq = yp->pci_dev->irq;
	व्योम __iomem *ioaddr = yp->base;
	पूर्णांक i, rc;

	/* Reset the chip. */
	ioग_लिखो32(0x80000000, ioaddr + DMACtrl);

	rc = request_irq(irq, yellowfin_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (rc)
		वापस rc;

	rc = yellowfin_init_ring(dev);
	अगर (rc < 0)
		जाओ err_मुक्त_irq;

	ioग_लिखो32(yp->rx_ring_dma, ioaddr + RxPtr);
	ioग_लिखो32(yp->tx_ring_dma, ioaddr + TxPtr);

	क्रम (i = 0; i < 6; i++)
		ioग_लिखो8(dev->dev_addr[i], ioaddr + StnAddr + i);

	/* Set up various condition 'select' रेजिस्टरs.
	   There are no options here. */
	ioग_लिखो32(0x00800080, ioaddr + TxIntrSel); 	/* Interrupt on Tx पात */
	ioग_लिखो32(0x00800080, ioaddr + TxBranchSel);	/* Branch on Tx पात */
	ioग_लिखो32(0x00400040, ioaddr + TxWaitSel); 	/* Wait on Tx status */
	ioग_लिखो32(0x00400040, ioaddr + RxIntrSel);	/* Interrupt on Rx करोne */
	ioग_लिखो32(0x00400040, ioaddr + RxBranchSel);	/* Branch on Rx error */
	ioग_लिखो32(0x00400040, ioaddr + RxWaitSel);	/* Wait on Rx करोne */

	/* Initialize other रेजिस्टरs: with so many this eventually this will
	   converted to an offset/value list. */
	ioग_लिखो32(dma_ctrl, ioaddr + DMACtrl);
	ioग_लिखो16(fअगरo_cfg, ioaddr + FIFOcfg);
	/* Enable स्वतःmatic generation of flow control frames, period 0xffff. */
	ioग_लिखो32(0x0030FFFF, ioaddr + FlowCtrl);

	yp->tx_threshold = 32;
	ioग_लिखो32(yp->tx_threshold, ioaddr + TxThreshold);

	अगर (dev->अगर_port == 0)
		dev->अगर_port = yp->शेष_port;

	netअगर_start_queue(dev);

	/* Setting the Rx mode will start the Rx process. */
	अगर (yp->drv_flags & IsGigabit) अणु
		/* We are always in full-duplex mode with gigabit! */
		yp->full_duplex = 1;
		ioग_लिखो16(0x01CF, ioaddr + Cnfg);
	पूर्ण अन्यथा अणु
		ioग_लिखो16(0x0018, ioaddr + FrameGap0); /* 0060/4060 क्रम non-MII 10baseT */
		ioग_लिखो16(0x1018, ioaddr + FrameGap1);
		ioग_लिखो16(0x101C | (yp->full_duplex ? 2 : 0), ioaddr + Cnfg);
	पूर्ण
	set_rx_mode(dev);

	/* Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ioग_लिखो16(0x81ff, ioaddr + IntrEnb);			/* See क्रमागत पूर्णांकr_status_bits */
	ioग_लिखो16(0x0000, ioaddr + EventStatus);		/* Clear non-पूर्णांकerrupting events */
	ioग_लिखो32(0x80008000, ioaddr + RxCtrl);		/* Start Rx and Tx channels. */
	ioग_लिखो32(0x80008000, ioaddr + TxCtrl);

	अगर (yellowfin_debug > 2) अणु
		netdev_prपूर्णांकk(KERN_DEBUG, dev, "Done %s()\n", __func__);
	पूर्ण

	/* Set the समयr to check क्रम link beat. */
	समयr_setup(&yp->समयr, yellowfin_समयr, 0);
	yp->समयr.expires = jअगरfies + 3*HZ;
	add_समयr(&yp->समयr);
out:
	वापस rc;

err_मुक्त_irq:
	मुक्त_irq(irq, dev);
	जाओ out;
पूर्ण

अटल व्योम yellowfin_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा yellowfin_निजी *yp = from_समयr(yp, t, समयr);
	काष्ठा net_device *dev = pci_get_drvdata(yp->pci_dev);
	व्योम __iomem *ioaddr = yp->base;
	पूर्णांक next_tick = 60*HZ;

	अगर (yellowfin_debug > 3) अणु
		netdev_prपूर्णांकk(KERN_DEBUG, dev, "Yellowfin timer tick, status %08x\n",
			      ioपढ़ो16(ioaddr + IntrStatus));
	पूर्ण

	अगर (yp->mii_cnt) अणु
		पूर्णांक bmsr = mdio_पढ़ो(ioaddr, yp->phys[0], MII_BMSR);
		पूर्णांक lpa = mdio_पढ़ो(ioaddr, yp->phys[0], MII_LPA);
		पूर्णांक negotiated = lpa & yp->advertising;
		अगर (yellowfin_debug > 1)
			netdev_prपूर्णांकk(KERN_DEBUG, dev, "MII #%d status register is %04x, link partner capability %04x\n",
				      yp->phys[0], bmsr, lpa);

		yp->full_duplex = mii_duplex(yp->duplex_lock, negotiated);

		ioग_लिखो16(0x101C | (yp->full_duplex ? 2 : 0), ioaddr + Cnfg);

		अगर (bmsr & BMSR_LSTATUS)
			next_tick = 60*HZ;
		अन्यथा
			next_tick = 3*HZ;
	पूर्ण

	yp->समयr.expires = jअगरfies + next_tick;
	add_समयr(&yp->समयr);
पूर्ण

अटल व्योम yellowfin_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा yellowfin_निजी *yp = netdev_priv(dev);
	व्योम __iomem *ioaddr = yp->base;

	netdev_warn(dev, "Yellowfin transmit timed out at %d/%d Tx status %04x, Rx status %04x, resetting...\n",
		    yp->cur_tx, yp->dirty_tx,
		    ioपढ़ो32(ioaddr + TxStatus),
		    ioपढ़ो32(ioaddr + RxStatus));

	/* Note: these should be KERN_DEBUG. */
	अगर (yellowfin_debug) अणु
		पूर्णांक i;
		pr_warn("  Rx ring %p: ", yp->rx_ring);
		क्रम (i = 0; i < RX_RING_SIZE; i++)
			pr_cont(" %08x", yp->rx_ring[i].result_status);
		pr_cont("\n");
		pr_warn("  Tx ring %p: ", yp->tx_ring);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			pr_cont(" %04x /%08x",
			       yp->tx_status[i].tx_errs,
			       yp->tx_ring[i].result_status);
		pr_cont("\n");
	पूर्ण

	/* If the hardware is found to hang regularly, we will update the code
	   to reinitialize the chip here. */
	dev->अगर_port = 0;

	/* Wake the potentially-idle transmit channel. */
	ioग_लिखो32(0x10001000, yp->base + TxCtrl);
	अगर (yp->cur_tx - yp->dirty_tx < TX_QUEUE_SIZE)
		netअगर_wake_queue (dev);		/* Typical path */

	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;
पूर्ण

/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल पूर्णांक yellowfin_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा yellowfin_निजी *yp = netdev_priv(dev);
	पूर्णांक i, j;

	yp->tx_full = 0;
	yp->cur_rx = yp->cur_tx = 0;
	yp->dirty_tx = 0;

	yp->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		yp->rx_ring[i].dbdma_cmd =
			cpu_to_le32(CMD_RX_BUF | INTR_ALWAYS | yp->rx_buf_sz);
		yp->rx_ring[i].branch_addr = cpu_to_le32(yp->rx_ring_dma +
			((i+1)%RX_RING_SIZE)*माप(काष्ठा yellowfin_desc));
	पूर्ण

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, yp->rx_buf_sz + 2);
		yp->rx_skbuff[i] = skb;
		अगर (skb == शून्य)
			अवरोध;
		skb_reserve(skb, 2);	/* 16 byte align the IP header. */
		yp->rx_ring[i].addr = cpu_to_le32(dma_map_single(&yp->pci_dev->dev,
								 skb->data,
								 yp->rx_buf_sz,
								 DMA_FROM_DEVICE));
	पूर्ण
	अगर (i != RX_RING_SIZE) अणु
		क्रम (j = 0; j < i; j++)
			dev_kमुक्त_skb(yp->rx_skbuff[j]);
		वापस -ENOMEM;
	पूर्ण
	yp->rx_ring[i-1].dbdma_cmd = cpu_to_le32(CMD_STOP);
	yp->dirty_rx = (अचिन्हित पूर्णांक)(i - RX_RING_SIZE);

#घोषणा NO_TXSTATS
#अगर_घोषित NO_TXSTATS
	/* In this mode the Tx ring needs only a single descriptor. */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		yp->tx_skbuff[i] = शून्य;
		yp->tx_ring[i].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->tx_ring[i].branch_addr = cpu_to_le32(yp->tx_ring_dma +
			((i+1)%TX_RING_SIZE)*माप(काष्ठा yellowfin_desc));
	पूर्ण
	/* Wrap ring */
	yp->tx_ring[--i].dbdma_cmd = cpu_to_le32(CMD_STOP | BRANCH_ALWAYS);
#अन्यथा
अणु
	/* Tx ring needs a pair of descriptors, the second क्रम the status. */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		j = 2*i;
		yp->tx_skbuff[i] = 0;
		/* Branch on Tx error. */
		yp->tx_ring[j].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->tx_ring[j].branch_addr = cpu_to_le32(yp->tx_ring_dma +
			(j+1)*माप(काष्ठा yellowfin_desc));
		j++;
		अगर (yp->flags & FullTxStatus) अणु
			yp->tx_ring[j].dbdma_cmd =
				cpu_to_le32(CMD_TXSTATUS | माप(*yp->tx_status));
			yp->tx_ring[j].request_cnt = माप(*yp->tx_status);
			yp->tx_ring[j].addr = cpu_to_le32(yp->tx_status_dma +
				i*माप(काष्ठा tx_status_words));
		पूर्ण अन्यथा अणु
			/* Symbios chips ग_लिखो only tx_errs word. */
			yp->tx_ring[j].dbdma_cmd =
				cpu_to_le32(CMD_TXSTATUS | INTR_ALWAYS | 2);
			yp->tx_ring[j].request_cnt = 2;
			/* Om pade ummmmm... */
			yp->tx_ring[j].addr = cpu_to_le32(yp->tx_status_dma +
				i*माप(काष्ठा tx_status_words) +
				&(yp->tx_status[0].tx_errs) -
				&(yp->tx_status[0]));
		पूर्ण
		yp->tx_ring[j].branch_addr = cpu_to_le32(yp->tx_ring_dma +
			((j+1)%(2*TX_RING_SIZE))*माप(काष्ठा yellowfin_desc));
	पूर्ण
	/* Wrap ring */
	yp->tx_ring[++j].dbdma_cmd |= cpu_to_le32(BRANCH_ALWAYS | INTR_ALWAYS);
पूर्ण
#पूर्ण_अगर
	yp->tx_tail_desc = &yp->tx_status[0];
	वापस 0;
पूर्ण

अटल netdev_tx_t yellowfin_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	काष्ठा yellowfin_निजी *yp = netdev_priv(dev);
	अचिन्हित entry;
	पूर्णांक len = skb->len;

	netअगर_stop_queue (dev);

	/* Note: Ordering is important here, set the field with the
	   "ownership" bit last, and only then increment cur_tx. */

	/* Calculate the next Tx descriptor entry. */
	entry = yp->cur_tx % TX_RING_SIZE;

	अगर (gx_fix) अणु	/* Note: only works क्रम paddable protocols e.g.  IP. */
		पूर्णांक cacheline_end = ((अचिन्हित दीर्घ)skb->data + skb->len) % 32;
		/* Fix GX chipset errata. */
		अगर (cacheline_end > 24  || cacheline_end == 0) अणु
			len = skb->len + 32 - cacheline_end + 1;
			अगर (skb_padto(skb, len)) अणु
				yp->tx_skbuff[entry] = शून्य;
				netअगर_wake_queue(dev);
				वापस NETDEV_TX_OK;
			पूर्ण
		पूर्ण
	पूर्ण
	yp->tx_skbuff[entry] = skb;

#अगर_घोषित NO_TXSTATS
	yp->tx_ring[entry].addr = cpu_to_le32(dma_map_single(&yp->pci_dev->dev,
							     skb->data,
							     len, DMA_TO_DEVICE));
	yp->tx_ring[entry].result_status = 0;
	अगर (entry >= TX_RING_SIZE-1) अणु
		/* New stop command. */
		yp->tx_ring[0].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->tx_ring[TX_RING_SIZE-1].dbdma_cmd =
			cpu_to_le32(CMD_TX_PKT|BRANCH_ALWAYS | len);
	पूर्ण अन्यथा अणु
		yp->tx_ring[entry+1].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->tx_ring[entry].dbdma_cmd =
			cpu_to_le32(CMD_TX_PKT | BRANCH_IFTRUE | len);
	पूर्ण
	yp->cur_tx++;
#अन्यथा
	yp->tx_ring[entry<<1].request_cnt = len;
	yp->tx_ring[entry<<1].addr = cpu_to_le32(dma_map_single(&yp->pci_dev->dev,
								skb->data,
								len, DMA_TO_DEVICE));
	/* The input_last (status-ग_लिखो) command is स्थिरant, but we must
	   reग_लिखो the subsequent 'stop' command. */

	yp->cur_tx++;
	अणु
		अचिन्हित next_entry = yp->cur_tx % TX_RING_SIZE;
		yp->tx_ring[next_entry<<1].dbdma_cmd = cpu_to_le32(CMD_STOP);
	पूर्ण
	/* Final step -- overग_लिखो the old 'stop' command. */

	yp->tx_ring[entry<<1].dbdma_cmd =
		cpu_to_le32( ((entry % 6) == 0 ? CMD_TX_PKT|INTR_ALWAYS|BRANCH_IFTRUE :
					  CMD_TX_PKT | BRANCH_IFTRUE) | len);
#पूर्ण_अगर

	/* Non-x86 Toकरो: explicitly flush cache lines here. */

	/* Wake the potentially-idle transmit channel. */
	ioग_लिखो32(0x10001000, yp->base + TxCtrl);

	अगर (yp->cur_tx - yp->dirty_tx < TX_QUEUE_SIZE)
		netअगर_start_queue (dev);		/* Typical path */
	अन्यथा
		yp->tx_full = 1;

	अगर (yellowfin_debug > 4) अणु
		netdev_prपूर्णांकk(KERN_DEBUG, dev, "Yellowfin transmit frame #%d queued in slot %d\n",
			      yp->cur_tx, entry);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */
अटल irqवापस_t yellowfin_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा yellowfin_निजी *yp;
	व्योम __iomem *ioaddr;
	पूर्णांक boguscnt = max_पूर्णांकerrupt_work;
	अचिन्हित पूर्णांक handled = 0;

	yp = netdev_priv(dev);
	ioaddr = yp->base;

	spin_lock (&yp->lock);

	करो अणु
		u16 पूर्णांकr_status = ioपढ़ो16(ioaddr + IntrClear);

		अगर (yellowfin_debug > 4)
			netdev_prपूर्णांकk(KERN_DEBUG, dev, "Yellowfin interrupt, status %04x\n",
				      पूर्णांकr_status);

		अगर (पूर्णांकr_status == 0)
			अवरोध;
		handled = 1;

		अगर (पूर्णांकr_status & (IntrRxDone | IntrEarlyRx)) अणु
			yellowfin_rx(dev);
			ioग_लिखो32(0x10001000, ioaddr + RxCtrl);		/* Wake Rx engine. */
		पूर्ण

#अगर_घोषित NO_TXSTATS
		क्रम (; yp->cur_tx - yp->dirty_tx > 0; yp->dirty_tx++) अणु
			पूर्णांक entry = yp->dirty_tx % TX_RING_SIZE;
			काष्ठा sk_buff *skb;

			अगर (yp->tx_ring[entry].result_status == 0)
				अवरोध;
			skb = yp->tx_skbuff[entry];
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += skb->len;
			/* Free the original skb. */
			dma_unmap_single(&yp->pci_dev->dev,
					 le32_to_cpu(yp->tx_ring[entry].addr),
					 skb->len, DMA_TO_DEVICE);
			dev_consume_skb_irq(skb);
			yp->tx_skbuff[entry] = शून्य;
		पूर्ण
		अगर (yp->tx_full &&
		    yp->cur_tx - yp->dirty_tx < TX_QUEUE_SIZE - 4) अणु
			/* The ring is no दीर्घer full, clear tbusy. */
			yp->tx_full = 0;
			netअगर_wake_queue(dev);
		पूर्ण
#अन्यथा
		अगर ((पूर्णांकr_status & IntrTxDone) || (yp->tx_tail_desc->tx_errs)) अणु
			अचिन्हित dirty_tx = yp->dirty_tx;

			क्रम (dirty_tx = yp->dirty_tx; yp->cur_tx - dirty_tx > 0;
				 dirty_tx++) अणु
				/* Toकरो: optimize this. */
				पूर्णांक entry = dirty_tx % TX_RING_SIZE;
				u16 tx_errs = yp->tx_status[entry].tx_errs;
				काष्ठा sk_buff *skb;

#अगर_अघोषित final_version
				अगर (yellowfin_debug > 5)
					netdev_prपूर्णांकk(KERN_DEBUG, dev, "Tx queue %d check, Tx status %04x %04x %04x %04x\n",
						      entry,
						      yp->tx_status[entry].tx_cnt,
						      yp->tx_status[entry].tx_errs,
						      yp->tx_status[entry].total_tx_cnt,
						      yp->tx_status[entry].छोड़ोd);
#पूर्ण_अगर
				अगर (tx_errs == 0)
					अवरोध;	/* It still hasn't been Txed */
				skb = yp->tx_skbuff[entry];
				अगर (tx_errs & 0xF810) अणु
					/* There was an major error, log it. */
#अगर_अघोषित final_version
					अगर (yellowfin_debug > 1)
						netdev_prपूर्णांकk(KERN_DEBUG, dev, "Transmit error, Tx status %04x\n",
							      tx_errs);
#पूर्ण_अगर
					dev->stats.tx_errors++;
					अगर (tx_errs & 0xF800) dev->stats.tx_पातed_errors++;
					अगर (tx_errs & 0x0800) dev->stats.tx_carrier_errors++;
					अगर (tx_errs & 0x2000) dev->stats.tx_winकरोw_errors++;
					अगर (tx_errs & 0x8000) dev->stats.tx_fअगरo_errors++;
				पूर्ण अन्यथा अणु
#अगर_अघोषित final_version
					अगर (yellowfin_debug > 4)
						netdev_prपूर्णांकk(KERN_DEBUG, dev, "Normal transmit, Tx status %04x\n",
							      tx_errs);
#पूर्ण_अगर
					dev->stats.tx_bytes += skb->len;
					dev->stats.collisions += tx_errs & 15;
					dev->stats.tx_packets++;
				पूर्ण
				/* Free the original skb. */
				dma_unmap_single(&yp->pci_dev->dev,
						 yp->tx_ring[entry << 1].addr,
						 skb->len, DMA_TO_DEVICE);
				dev_consume_skb_irq(skb);
				yp->tx_skbuff[entry] = 0;
				/* Mark status as empty. */
				yp->tx_status[entry].tx_errs = 0;
			पूर्ण

#अगर_अघोषित final_version
			अगर (yp->cur_tx - dirty_tx > TX_RING_SIZE) अणु
				netdev_err(dev, "Out-of-sync dirty pointer, %d vs. %d, full=%d\n",
					   dirty_tx, yp->cur_tx, yp->tx_full);
				dirty_tx += TX_RING_SIZE;
			पूर्ण
#पूर्ण_अगर

			अगर (yp->tx_full &&
			    yp->cur_tx - dirty_tx < TX_QUEUE_SIZE - 2) अणु
				/* The ring is no दीर्घer full, clear tbusy. */
				yp->tx_full = 0;
				netअगर_wake_queue(dev);
			पूर्ण

			yp->dirty_tx = dirty_tx;
			yp->tx_tail_desc = &yp->tx_status[dirty_tx % TX_RING_SIZE];
		पूर्ण
#पूर्ण_अगर

		/* Log errors and other uncommon events. */
		अगर (पूर्णांकr_status & 0x2ee)	/* Abnormal error summary. */
			yellowfin_error(dev, पूर्णांकr_status);

		अगर (--boguscnt < 0) अणु
			netdev_warn(dev, "Too much work at interrupt, status=%#04x\n",
				    पूर्णांकr_status);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	अगर (yellowfin_debug > 3)
		netdev_prपूर्णांकk(KERN_DEBUG, dev, "exiting interrupt, status=%#04x\n",
			      ioपढ़ो16(ioaddr + IntrStatus));

	spin_unlock (&yp->lock);
	वापस IRQ_RETVAL(handled);
पूर्ण

/* This routine is logically part of the पूर्णांकerrupt handler, but separated
   क्रम clarity and better रेजिस्टर allocation. */
अटल पूर्णांक yellowfin_rx(काष्ठा net_device *dev)
अणु
	काष्ठा yellowfin_निजी *yp = netdev_priv(dev);
	पूर्णांक entry = yp->cur_rx % RX_RING_SIZE;
	पूर्णांक boguscnt = yp->dirty_rx + RX_RING_SIZE - yp->cur_rx;

	अगर (yellowfin_debug > 4) अणु
		prपूर्णांकk(KERN_DEBUG " In yellowfin_rx(), entry %d status %08x\n",
			   entry, yp->rx_ring[entry].result_status);
		prपूर्णांकk(KERN_DEBUG "   #%d desc. %08x %08x %08x\n",
			   entry, yp->rx_ring[entry].dbdma_cmd, yp->rx_ring[entry].addr,
			   yp->rx_ring[entry].result_status);
	पूर्ण

	/* If EOP is set on the next entry, it's a new packet. Send it up. */
	जबतक (1) अणु
		काष्ठा yellowfin_desc *desc = &yp->rx_ring[entry];
		काष्ठा sk_buff *rx_skb = yp->rx_skbuff[entry];
		s16 frame_status;
		u16 desc_status;
		पूर्णांक data_size, __maybe_unused yf_size;
		u8 *buf_addr;

		अगर(!desc->result_status)
			अवरोध;
		dma_sync_single_क्रम_cpu(&yp->pci_dev->dev,
					le32_to_cpu(desc->addr),
					yp->rx_buf_sz, DMA_FROM_DEVICE);
		desc_status = le32_to_cpu(desc->result_status) >> 16;
		buf_addr = rx_skb->data;
		data_size = (le32_to_cpu(desc->dbdma_cmd) -
			le32_to_cpu(desc->result_status)) & 0xffff;
		frame_status = get_unaligned_le16(&(buf_addr[data_size - 2]));
		अगर (yellowfin_debug > 4)
			prपूर्णांकk(KERN_DEBUG "  %s() status was %04x\n",
			       __func__, frame_status);
		अगर (--boguscnt < 0)
			अवरोध;

		yf_size = माप(काष्ठा yellowfin_desc);

		अगर ( ! (desc_status & RX_EOP)) अणु
			अगर (data_size != 0)
				netdev_warn(dev, "Oversized Ethernet frame spanned multiple buffers, status %04x, data_size %d!\n",
					    desc_status, data_size);
			dev->stats.rx_length_errors++;
		पूर्ण अन्यथा अगर ((yp->drv_flags & IsGigabit)  &&  (frame_status & 0x0038)) अणु
			/* There was a error. */
			अगर (yellowfin_debug > 3)
				prपूर्णांकk(KERN_DEBUG "  %s() Rx error was %04x\n",
				       __func__, frame_status);
			dev->stats.rx_errors++;
			अगर (frame_status & 0x0060) dev->stats.rx_length_errors++;
			अगर (frame_status & 0x0008) dev->stats.rx_frame_errors++;
			अगर (frame_status & 0x0010) dev->stats.rx_crc_errors++;
			अगर (frame_status < 0) dev->stats.rx_dropped++;
		पूर्ण अन्यथा अगर ( !(yp->drv_flags & IsGigabit)  &&
				   ((buf_addr[data_size-1] & 0x85) || buf_addr[data_size-2] & 0xC0)) अणु
			u8 status1 = buf_addr[data_size-2];
			u8 status2 = buf_addr[data_size-1];
			dev->stats.rx_errors++;
			अगर (status1 & 0xC0) dev->stats.rx_length_errors++;
			अगर (status2 & 0x03) dev->stats.rx_frame_errors++;
			अगर (status2 & 0x04) dev->stats.rx_crc_errors++;
			अगर (status2 & 0x80) dev->stats.rx_dropped++;
#अगर_घोषित YF_PROTOTYPE		/* Support क्रम prototype hardware errata. */
		पूर्ण अन्यथा अगर ((yp->flags & HasMACAddrBug)  &&
			!ether_addr_equal(le32_to_cpu(yp->rx_ring_dma +
						      entry * yf_size),
					  dev->dev_addr) &&
			!ether_addr_equal(le32_to_cpu(yp->rx_ring_dma +
						      entry * yf_size),
					  "\377\377\377\377\377\377")) अणु
			अगर (bogus_rx++ == 0)
				netdev_warn(dev, "Bad frame to %pM\n",
					    buf_addr);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb;
			पूर्णांक pkt_len = data_size -
				(yp->chip_id ? 7 : 8 + buf_addr[data_size - 8]);
			/* To verअगरy: Yellowfin Length should omit the CRC! */

#अगर_अघोषित final_version
			अगर (yellowfin_debug > 4)
				prपूर्णांकk(KERN_DEBUG "  %s() normal Rx pkt length %d of %d, bogus_cnt %d\n",
				       __func__, pkt_len, data_size, boguscnt);
#पूर्ण_अगर
			/* Check अगर the packet is दीर्घ enough to just pass up the skbuff
			   without copying to a properly sized skbuff. */
			अगर (pkt_len > rx_copyअवरोध) अणु
				skb_put(skb = rx_skb, pkt_len);
				dma_unmap_single(&yp->pci_dev->dev,
						 le32_to_cpu(yp->rx_ring[entry].addr),
						 yp->rx_buf_sz,
						 DMA_FROM_DEVICE);
				yp->rx_skbuff[entry] = शून्य;
			पूर्ण अन्यथा अणु
				skb = netdev_alloc_skb(dev, pkt_len + 2);
				अगर (skb == शून्य)
					अवरोध;
				skb_reserve(skb, 2);	/* 16 byte align the IP header */
				skb_copy_to_linear_data(skb, rx_skb->data, pkt_len);
				skb_put(skb, pkt_len);
				dma_sync_single_क्रम_device(&yp->pci_dev->dev,
							   le32_to_cpu(desc->addr),
							   yp->rx_buf_sz,
							   DMA_FROM_DEVICE);
			पूर्ण
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		पूर्ण
		entry = (++yp->cur_rx) % RX_RING_SIZE;
	पूर्ण

	/* Refill the Rx ring buffers. */
	क्रम (; yp->cur_rx - yp->dirty_rx > 0; yp->dirty_rx++) अणु
		entry = yp->dirty_rx % RX_RING_SIZE;
		अगर (yp->rx_skbuff[entry] == शून्य) अणु
			काष्ठा sk_buff *skb = netdev_alloc_skb(dev, yp->rx_buf_sz + 2);
			अगर (skb == शून्य)
				अवरोध;				/* Better luck next round. */
			yp->rx_skbuff[entry] = skb;
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			yp->rx_ring[entry].addr = cpu_to_le32(dma_map_single(&yp->pci_dev->dev,
									     skb->data,
									     yp->rx_buf_sz,
									     DMA_FROM_DEVICE));
		पूर्ण
		yp->rx_ring[entry].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->rx_ring[entry].result_status = 0;	/* Clear complete bit. */
		अगर (entry != 0)
			yp->rx_ring[entry - 1].dbdma_cmd =
				cpu_to_le32(CMD_RX_BUF | INTR_ALWAYS | yp->rx_buf_sz);
		अन्यथा
			yp->rx_ring[RX_RING_SIZE - 1].dbdma_cmd =
				cpu_to_le32(CMD_RX_BUF | INTR_ALWAYS | BRANCH_ALWAYS
							| yp->rx_buf_sz);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम yellowfin_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status)
अणु
	netdev_err(dev, "Something Wicked happened! %04x\n", पूर्णांकr_status);
	/* Hmmmmm, it's not clear what to करो here. */
	अगर (पूर्णांकr_status & (IntrTxPCIErr | IntrTxPCIFault))
		dev->stats.tx_errors++;
	अगर (पूर्णांकr_status & (IntrRxPCIErr | IntrRxPCIFault))
		dev->stats.rx_errors++;
पूर्ण

अटल पूर्णांक yellowfin_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा yellowfin_निजी *yp = netdev_priv(dev);
	व्योम __iomem *ioaddr = yp->base;
	पूर्णांक i;

	netअगर_stop_queue (dev);

	अगर (yellowfin_debug > 1) अणु
		netdev_prपूर्णांकk(KERN_DEBUG, dev, "Shutting down ethercard, status was Tx %04x Rx %04x Int %02x\n",
			      ioपढ़ो16(ioaddr + TxStatus),
			      ioपढ़ो16(ioaddr + RxStatus),
			      ioपढ़ो16(ioaddr + IntrStatus));
		netdev_prपूर्णांकk(KERN_DEBUG, dev, "Queue pointers were Tx %d / %d,  Rx %d / %d\n",
			      yp->cur_tx, yp->dirty_tx,
			      yp->cur_rx, yp->dirty_rx);
	पूर्ण

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	ioग_लिखो16(0x0000, ioaddr + IntrEnb);

	/* Stop the chip's Tx and Rx processes. */
	ioग_लिखो32(0x80000000, ioaddr + RxCtrl);
	ioग_लिखो32(0x80000000, ioaddr + TxCtrl);

	del_समयr(&yp->समयr);

#अगर defined(__i386__)
	अगर (yellowfin_debug > 2) अणु
		prपूर्णांकk(KERN_DEBUG "  Tx ring at %08llx:\n",
				(अचिन्हित दीर्घ दीर्घ)yp->tx_ring_dma);
		क्रम (i = 0; i < TX_RING_SIZE*2; i++)
			prपूर्णांकk(KERN_DEBUG " %c #%d desc. %08x %08x %08x %08x\n",
				   ioपढ़ो32(ioaddr + TxPtr) == (दीर्घ)&yp->tx_ring[i] ? '>' : ' ',
				   i, yp->tx_ring[i].dbdma_cmd, yp->tx_ring[i].addr,
				   yp->tx_ring[i].branch_addr, yp->tx_ring[i].result_status);
		prपूर्णांकk(KERN_DEBUG "  Tx status %p:\n", yp->tx_status);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			prपूर्णांकk(KERN_DEBUG "   #%d status %04x %04x %04x %04x\n",
				   i, yp->tx_status[i].tx_cnt, yp->tx_status[i].tx_errs,
				   yp->tx_status[i].total_tx_cnt, yp->tx_status[i].छोड़ोd);

		prपूर्णांकk(KERN_DEBUG "  Rx ring %08llx:\n",
				(अचिन्हित दीर्घ दीर्घ)yp->rx_ring_dma);
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			prपूर्णांकk(KERN_DEBUG " %c #%d desc. %08x %08x %08x\n",
				   ioपढ़ो32(ioaddr + RxPtr) == (दीर्घ)&yp->rx_ring[i] ? '>' : ' ',
				   i, yp->rx_ring[i].dbdma_cmd, yp->rx_ring[i].addr,
				   yp->rx_ring[i].result_status);
			अगर (yellowfin_debug > 6) अणु
				अगर (get_unaligned((u8*)yp->rx_ring[i].addr) != 0x69) अणु
					पूर्णांक j;

					prपूर्णांकk(KERN_DEBUG);
					क्रम (j = 0; j < 0x50; j++)
						pr_cont(" %04x",
							get_unaligned(((u16*)yp->rx_ring[i].addr) + j));
					pr_cont("\n");
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* __i386__ debugging only */

	मुक्त_irq(yp->pci_dev->irq, dev);

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		yp->rx_ring[i].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->rx_ring[i].addr = cpu_to_le32(0xBADF00D0); /* An invalid address. */
		अगर (yp->rx_skbuff[i]) अणु
			dev_kमुक्त_skb(yp->rx_skbuff[i]);
		पूर्ण
		yp->rx_skbuff[i] = शून्य;
	पूर्ण
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		dev_kमुक्त_skb(yp->tx_skbuff[i]);
		yp->tx_skbuff[i] = शून्य;
	पूर्ण

#अगर_घोषित YF_PROTOTYPE			/* Support क्रम prototype hardware errata. */
	अगर (yellowfin_debug > 0) अणु
		netdev_prपूर्णांकk(KERN_DEBUG, dev, "Received %d frames that we should not have\n",
			      bogus_rx);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor. */

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा yellowfin_निजी *yp = netdev_priv(dev);
	व्योम __iomem *ioaddr = yp->base;
	u16 cfg_value = ioपढ़ो16(ioaddr + Cnfg);

	/* Stop the Rx process to change any value. */
	ioग_लिखो16(cfg_value & ~0x1000, ioaddr + Cnfg);
	अगर (dev->flags & IFF_PROMISC) अणु			/* Set promiscuous. */
		ioग_लिखो16(0x000F, ioaddr + AddrMode);
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > 64) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to filter well, or accept all multicasts. */
		ioग_लिखो16(0x000B, ioaddr + AddrMode);
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु /* Must use the multicast hash table. */
		काष्ठा netdev_hw_addr *ha;
		u16 hash_table[4];
		पूर्णांक i;

		स_रखो(hash_table, 0, माप(hash_table));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अचिन्हित पूर्णांक bit;

			/* Due to a bug in the early chip versions, multiple filter
			   slots must be set क्रम each address. */
			अगर (yp->drv_flags & HasMulticastBug) अणु
				bit = (ether_crc_le(3, ha->addr) >> 3) & 0x3f;
				hash_table[bit >> 4] |= (1 << bit);
				bit = (ether_crc_le(4, ha->addr) >> 3) & 0x3f;
				hash_table[bit >> 4] |= (1 << bit);
				bit = (ether_crc_le(5, ha->addr) >> 3) & 0x3f;
				hash_table[bit >> 4] |= (1 << bit);
			पूर्ण
			bit = (ether_crc_le(6, ha->addr) >> 3) & 0x3f;
			hash_table[bit >> 4] |= (1 << bit);
		पूर्ण
		/* Copy the hash table to the chip. */
		क्रम (i = 0; i < 4; i++)
			ioग_लिखो16(hash_table[i], ioaddr + HashTbl + i*2);
		ioग_लिखो16(0x0003, ioaddr + AddrMode);
	पूर्ण अन्यथा अणु					/* Normal, unicast/broadcast-only mode. */
		ioग_लिखो16(0x0001, ioaddr + AddrMode);
	पूर्ण
	/* Restart the Rx process. */
	ioग_लिखो16(cfg_value | 0x1000, ioaddr + Cnfg);
पूर्ण

अटल व्योम yellowfin_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा yellowfin_निजी *np = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(np->pci_dev), माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.get_drvinfo = yellowfin_get_drvinfo
पूर्ण;

अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा yellowfin_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base;
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);

	चयन(cmd) अणु
	हाल SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = np->phys[0] & 0x1f;
		fallthrough;

	हाल SIOCGMIIREG:		/* Read MII PHY रेजिस्टर. */
		data->val_out = mdio_पढ़ो(ioaddr, data->phy_id & 0x1f, data->reg_num & 0x1f);
		वापस 0;

	हाल SIOCSMIIREG:		/* Write MII PHY रेजिस्टर. */
		अगर (data->phy_id == np->phys[0]) अणु
			u16 value = data->val_in;
			चयन (data->reg_num) अणु
			हाल 0:
				/* Check क्रम स्वतःnegotiation on or reset. */
				np->medialock = (value & 0x9000) ? 0 : 1;
				अगर (np->medialock)
					np->full_duplex = (value & 0x0100) ? 1 : 0;
				अवरोध;
			हाल 4: np->advertising = value; अवरोध;
			पूर्ण
			/* Perhaps check_duplex(dev), depending on chip semantics. */
		पूर्ण
		mdio_ग_लिखो(ioaddr, data->phy_id & 0x1f, data->reg_num & 0x1f, data->val_in);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण


अटल व्योम yellowfin_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा yellowfin_निजी *np;

	BUG_ON(!dev);
	np = netdev_priv(dev);

	dma_मुक्त_coherent(&pdev->dev, STATUS_TOTAL_SIZE, np->tx_status,
			  np->tx_status_dma);
	dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, np->rx_ring,
			  np->rx_ring_dma);
	dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, np->tx_ring,
			  np->tx_ring_dma);
	unरेजिस्टर_netdev (dev);

	pci_iounmap(pdev, np->base);

	pci_release_regions (pdev);

	मुक्त_netdev (dev);
पूर्ण


अटल काष्ठा pci_driver yellowfin_driver = अणु
	.name		= DRV_NAME,
	.id_table	= yellowfin_pci_tbl,
	.probe		= yellowfin_init_one,
	.हटाओ		= yellowfin_हटाओ_one,
पूर्ण;


अटल पूर्णांक __init yellowfin_init (व्योम)
अणु
/* when a module, this is prपूर्णांकed whether or not devices are found in probe */
#अगर_घोषित MODULE
	prपूर्णांकk(version);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&yellowfin_driver);
पूर्ण


अटल व्योम __निकास yellowfin_cleanup (व्योम)
अणु
	pci_unरेजिस्टर_driver (&yellowfin_driver);
पूर्ण


module_init(yellowfin_init);
module_निकास(yellowfin_cleanup);
