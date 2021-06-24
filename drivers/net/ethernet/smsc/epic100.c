<शैली गुरु>
/* epic100.c: A SMC 83c170 EPIC/100 Fast Ethernet driver क्रम Linux. */
/*
	Written/copyright 1997-2001 by Donald Becker.

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	This driver is क्रम the SMC83c170/175 "EPIC" series, as used on the
	SMC EtherPower II 9432 PCI adapter, and several CardBus cards.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	Inक्रमmation and updates available at
	http://www.scyld.com/network/epic100.hपंचांगl
	[this link no दीर्घer provides anything useful -jgarzik]

	---------------------------------------------------------------------

*/

#घोषणा DRV_NAME        "epic100"
#घोषणा DRV_VERSION     "2.1"
#घोषणा DRV_RELDATE     "Sept 11, 2006"

/* The user-configurable values.
   These may be modअगरied when a driver module is loaded.*/

अटल पूर्णांक debug = 1;			/* 1 normal messages, 0 quiet .. 7 verbose. */

/* Used to pass the full-duplex flag, etc. */
#घोषणा MAX_UNITS 8		/* More are supported, limit only on options */
अटल पूर्णांक options[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
अटल पूर्णांक full_duplex[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
   Setting to > 1518 effectively disables this feature. */
अटल पूर्णांक rx_copyअवरोध;

/* Operational parameters that are set at compile समय. */

/* Keep the ring sizes a घातer of two क्रम operational efficiency.
   The compiler will convert <अचिन्हित>'%'<2^N> पूर्णांकo a bit mask.
   Making the Tx ring too large decreases the effectiveness of channel
   bonding and packet priority.
   There are no ill effects from too-large receive rings. */
#घोषणा TX_RING_SIZE	256
#घोषणा TX_QUEUE_LEN	240		/* Limit ring entries actually used.  */
#घोषणा RX_RING_SIZE	256
#घोषणा TX_TOTAL_SIZE	TX_RING_SIZE*माप(काष्ठा epic_tx_desc)
#घोषणा RX_TOTAL_SIZE	RX_RING_SIZE*माप(काष्ठा epic_rx_desc)

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (2*HZ)

#घोषणा PKT_BUF_SZ		1536			/* Size of each temporary Rx buffer.*/

/* Bytes transferred to chip beक्रमe transmission starts. */
/* Initial threshold, increased on underflow, rounded करोwn to 4 byte units. */
#घोषणा TX_FIFO_THRESH 256
#घोषणा RX_FIFO_THRESH 1		/* 0-3, 0==32, 64,96, or 3==128 bytes  */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>

/* These identअगरy the driver base version and may not be हटाओd. */
अटल अक्षर version[] =
DRV_NAME ".c:v1.11 1/7/2001 Written by Donald Becker <becker@scyld.com>";
अटल अक्षर version2[] =
"  (unofficial 2.4.x kernel port, version " DRV_VERSION ", " DRV_RELDATE ")";

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("SMC 83c170 EPIC series Ethernet driver");
MODULE_LICENSE("GPL");

module_param(debug, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(debug, "EPIC/100 debug level (0-5)");
MODULE_PARM_DESC(options, "EPIC/100: Bits 0-3: media type, bit 4: full duplex");
MODULE_PARM_DESC(rx_copyअवरोध, "EPIC/100 copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(full_duplex, "EPIC/100 full duplex setting(s) (1)");

/*
				Theory of Operation

I. Board Compatibility

This device driver is deचिन्हित क्रम the SMC "EPIC/100", the SMC
single-chip Ethernet controllers क्रम PCI.  This chip is used on
the SMC EtherPower II boards.

II. Board-specअगरic settings

PCI bus devices are configured by the प्रणाली at boot समय, so no jumpers
need to be set on the board.  The प्रणाली BIOS will assign the
PCI INTA संकेत to a (preferably otherwise unused) प्रणाली IRQ line.
Note: Kernel versions earlier than 1.3.73 करो not support shared PCI
पूर्णांकerrupt lines.

III. Driver operation

IIIa. Ring buffers

IVb. References

http://www.smsc.com/media/Downloads_Public/disजारीd/83c171.pdf
http://www.smsc.com/media/Downloads_Public/disजारीd/83c175.pdf
http://scyld.com/expert/NWay.hपंचांगl
http://www.national.com/pf/DP/DP83840A.hपंचांगl

IVc. Errata

*/


क्रमागत chip_capability_flags अणु MII_PWRDWN=1, TYPE2_INTR=2, NO_MII=4 पूर्ण;

#घोषणा EPIC_TOTAL_SIZE 0x100
#घोषणा USE_IO_OPS 1

#अगर_घोषित USE_IO_OPS
#घोषणा EPIC_BAR	0
#अन्यथा
#घोषणा EPIC_BAR	1
#पूर्ण_अगर

प्रकार क्रमागत अणु
	SMSC_83C170_0,
	SMSC_83C170,
	SMSC_83C175,
पूर्ण chip_t;


काष्ठा epic_chip_info अणु
	स्थिर अक्षर *name;
        पूर्णांक drv_flags;                          /* Driver use, पूर्णांकended as capability flags. */
पूर्ण;


/* indexed by chip_t */
अटल स्थिर काष्ठा epic_chip_info pci_id_tbl[] = अणु
	अणु "SMSC EPIC/100 83c170",	TYPE2_INTR | NO_MII | MII_PWRDWN पूर्ण,
	अणु "SMSC EPIC/100 83c170",	TYPE2_INTR पूर्ण,
	अणु "SMSC EPIC/C 83c175",		TYPE2_INTR | MII_PWRDWN पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा pci_device_id epic_pci_tbl[] = अणु
	अणु 0x10B8, 0x0005, 0x1092, 0x0AB4, 0, 0, SMSC_83C170_0 पूर्ण,
	अणु 0x10B8, 0x0005, PCI_ANY_ID, PCI_ANY_ID, 0, 0, SMSC_83C170 पूर्ण,
	अणु 0x10B8, 0x0006, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_NETWORK_ETHERNET << 8, 0xffff00, SMSC_83C175 पूर्ण,
	अणु 0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (pci, epic_pci_tbl);

#घोषणा ew16(reg, val)	ioग_लिखो16(val, ioaddr + (reg))
#घोषणा ew32(reg, val)	ioग_लिखो32(val, ioaddr + (reg))
#घोषणा er8(reg)	ioपढ़ो8(ioaddr + (reg))
#घोषणा er16(reg)	ioपढ़ो16(ioaddr + (reg))
#घोषणा er32(reg)	ioपढ़ो32(ioaddr + (reg))

/* Offsets to रेजिस्टरs, using the (ugh) SMC names. */
क्रमागत epic_रेजिस्टरs अणु
  COMMAND=0, INTSTAT=4, INTMASK=8, GENCTL=0x0C, NVCTL=0x10, EECTL=0x14,
  PCIBurstCnt=0x18,
  TEST1=0x1C, CRCCNT=0x20, ALICNT=0x24, MPCNT=0x28,	/* Rx error counters. */
  MIICtrl=0x30, MIIData=0x34, MIICfg=0x38,
  LAN0=64,						/* MAC address. */
  MC0=80,						/* Multicast filter table. */
  RxCtrl=96, TxCtrl=112, TxSTAT=0x74,
  PRxCDAR=0x84, RxSTAT=0xA4, EarlyRx=0xB0, PTxCDAR=0xC4, TxThresh=0xDC,
पूर्ण;

/* Interrupt रेजिस्टर bits, using my own meaningful names. */
क्रमागत IntrStatus अणु
	TxIdle=0x40000, RxIdle=0x20000, IntrSummary=0x010000,
	PCIBusErr170=0x7000, PCIBusErr175=0x1000, PhyEvent175=0x8000,
	RxStarted=0x0800, RxEarlyWarn=0x0400, CntFull=0x0200, TxUnderrun=0x0100,
	TxEmpty=0x0080, TxDone=0x0020, RxError=0x0010,
	RxOverflow=0x0008, RxFull=0x0004, RxHeader=0x0002, RxDone=0x0001,
पूर्ण;
क्रमागत CommandBits अणु
	StopRx=1, StartRx=2, TxQueued=4, RxQueued=8,
	StopTxDMA=0x20, StopRxDMA=0x40, RestartTx=0x80,
पूर्ण;

#घोषणा EpicRemoved	0xffffffff	/* Chip failed or हटाओd (CardBus) */

#घोषणा EpicNapiEvent	(TxEmpty | TxDone | \
			 RxDone | RxStarted | RxEarlyWarn | RxOverflow | RxFull)
#घोषणा EpicNormalEvent	(0x0000ffff & ~EpicNapiEvent)

अटल स्थिर u16 media2miictl[16] = अणु
	0, 0x0C00, 0x0C00, 0x2000,  0x0100, 0x2100, 0, 0,
	0, 0, 0, 0,  0, 0, 0, 0 पूर्ण;

/*
 * The EPIC100 Rx and Tx buffer descriptors.  Note that these
 * really ARE host-endian; it's not a misannotation.  We tell
 * the card to byteswap them पूर्णांकernally on big-endian hosts -
 * look क्रम #अगर_घोषित __BIG_ENDIAN in epic_खोलो().
 */

काष्ठा epic_tx_desc अणु
	u32 txstatus;
	u32 bufaddr;
	u32 buflength;
	u32 next;
पूर्ण;

काष्ठा epic_rx_desc अणु
	u32 rxstatus;
	u32 bufaddr;
	u32 buflength;
	u32 next;
पूर्ण;

क्रमागत desc_status_bits अणु
	DescOwn=0x8000,
पूर्ण;

#घोषणा PRIV_ALIGN	15 	/* Required alignment mask */
काष्ठा epic_निजी अणु
	काष्ठा epic_rx_desc *rx_ring;
	काष्ठा epic_tx_desc *tx_ring;
	/* The saved address of a sent-in-place packet/buffer, क्रम skमुक्त(). */
	काष्ठा sk_buff* tx_skbuff[TX_RING_SIZE];
	/* The addresses of receive-in-place skbuffs. */
	काष्ठा sk_buff* rx_skbuff[RX_RING_SIZE];

	dma_addr_t tx_ring_dma;
	dma_addr_t rx_ring_dma;

	/* Ring poपूर्णांकers. */
	spinlock_t lock;				/* Group with Tx control cache line. */
	spinlock_t napi_lock;
	काष्ठा napi_काष्ठा napi;
	अचिन्हित पूर्णांक cur_tx, dirty_tx;

	अचिन्हित पूर्णांक cur_rx, dirty_rx;
	u32 irq_mask;
	अचिन्हित पूर्णांक rx_buf_sz;				/* Based on MTU+slack. */

	व्योम __iomem *ioaddr;
	काष्ठा pci_dev *pci_dev;			/* PCI bus location. */
	पूर्णांक chip_id, chip_flags;

	काष्ठा समयr_list समयr;			/* Media selection समयr. */
	पूर्णांक tx_threshold;
	अचिन्हित अक्षर mc_filter[8];
	चिन्हित अक्षर phys[4];				/* MII device addresses. */
	u16 advertising;					/* NWay media advertisement */
	पूर्णांक mii_phy_cnt;
	u32 ethtool_ops_nesting;
	काष्ठा mii_अगर_info mii;
	अचिन्हित पूर्णांक tx_full:1;				/* The Tx queue is full. */
	अचिन्हित पूर्णांक शेष_port:4;		/* Last dev->अगर_port value. */
पूर्ण;

अटल पूर्णांक epic_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक पढ़ो_eeprom(काष्ठा epic_निजी *, पूर्णांक);
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक val);
अटल व्योम epic_restart(काष्ठा net_device *dev);
अटल व्योम epic_समयr(काष्ठा समयr_list *t);
अटल व्योम epic_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम epic_init_ring(काष्ठा net_device *dev);
अटल netdev_tx_t epic_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev);
अटल पूर्णांक epic_rx(काष्ठा net_device *dev, पूर्णांक budget);
अटल पूर्णांक epic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
अटल irqवापस_t epic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;
अटल पूर्णांक epic_बंद(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *epic_get_stats(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);

अटल स्थिर काष्ठा net_device_ops epic_netdev_ops = अणु
	.nकरो_खोलो		= epic_खोलो,
	.nकरो_stop		= epic_बंद,
	.nकरो_start_xmit		= epic_start_xmit,
	.nकरो_tx_समयout 	= epic_tx_समयout,
	.nकरो_get_stats		= epic_get_stats,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_करो_ioctl 		= netdev_ioctl,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक epic_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल पूर्णांक card_idx = -1;
	व्योम __iomem *ioaddr;
	पूर्णांक chip_idx = (पूर्णांक) ent->driver_data;
	काष्ठा net_device *dev;
	काष्ठा epic_निजी *ep;
	पूर्णांक i, ret, option = 0, duplex = 0;
	व्योम *ring_space;
	dma_addr_t ring_dma;

/* when built पूर्णांकo the kernel, we only prपूर्णांक version अगर device is found */
#अगर_अघोषित MODULE
	pr_info_once("%s%s\n", version, version2);
#पूर्ण_अगर

	card_idx++;

	ret = pci_enable_device(pdev);
	अगर (ret)
		जाओ out;

	अगर (pci_resource_len(pdev, 0) < EPIC_TOTAL_SIZE) अणु
		dev_err(&pdev->dev, "no PCI region space\n");
		ret = -ENODEV;
		जाओ err_out_disable;
	पूर्ण

	pci_set_master(pdev);

	ret = pci_request_regions(pdev, DRV_NAME);
	अगर (ret < 0)
		जाओ err_out_disable;

	ret = -ENOMEM;

	dev = alloc_etherdev(माप (*ep));
	अगर (!dev)
		जाओ err_out_मुक्त_res;

	SET_NETDEV_DEV(dev, &pdev->dev);

	ioaddr = pci_iomap(pdev, EPIC_BAR, 0);
	अगर (!ioaddr) अणु
		dev_err(&pdev->dev, "ioremap failed\n");
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	pci_set_drvdata(pdev, dev);
	ep = netdev_priv(dev);
	ep->ioaddr = ioaddr;
	ep->mii.dev = dev;
	ep->mii.mdio_पढ़ो = mdio_पढ़ो;
	ep->mii.mdio_ग_लिखो = mdio_ग_लिखो;
	ep->mii.phy_id_mask = 0x1f;
	ep->mii.reg_num_mask = 0x1f;

	ring_space = dma_alloc_coherent(&pdev->dev, TX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_iounmap;
	ep->tx_ring = ring_space;
	ep->tx_ring_dma = ring_dma;

	ring_space = dma_alloc_coherent(&pdev->dev, RX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_unmap_tx;
	ep->rx_ring = ring_space;
	ep->rx_ring_dma = ring_dma;

	अगर (dev->mem_start) अणु
		option = dev->mem_start;
		duplex = (dev->mem_start & 16) ? 1 : 0;
	पूर्ण अन्यथा अगर (card_idx >= 0  &&  card_idx < MAX_UNITS) अणु
		अगर (options[card_idx] >= 0)
			option = options[card_idx];
		अगर (full_duplex[card_idx] >= 0)
			duplex = full_duplex[card_idx];
	पूर्ण

	spin_lock_init(&ep->lock);
	spin_lock_init(&ep->napi_lock);

	/* Bring the chip out of low-घातer mode. */
	ew32(GENCTL, 0x4200);
	/* Magic?!  If we करोn't set this bit the MII interface won't work. */
	/* This magic is करोcumented in SMSC app note 7.15 */
	क्रम (i = 16; i > 0; i--)
		ew32(TEST1, 0x0008);

	/* Turn on the MII transceiver. */
	ew32(MIICfg, 0x12);
	अगर (chip_idx == 1)
		ew32(NVCTL, (er32(NVCTL) & ~0x003c) | 0x4800);
	ew32(GENCTL, 0x0200);

	/* Note: the '175 करोes not have a serial EEPROM. */
	क्रम (i = 0; i < 3; i++)
		((__le16 *)dev->dev_addr)[i] = cpu_to_le16(er16(LAN0 + i*4));

	अगर (debug > 2) अणु
		dev_dbg(&pdev->dev, "EEPROM contents:\n");
		क्रम (i = 0; i < 64; i++)
			pr_cont(" %4.4x%s", पढ़ो_eeprom(ep, i),
				   i % 16 == 15 ? "\n" : "");
	पूर्ण

	ep->pci_dev = pdev;
	ep->chip_id = chip_idx;
	ep->chip_flags = pci_id_tbl[chip_idx].drv_flags;
	ep->irq_mask =
		(ep->chip_flags & TYPE2_INTR ?  PCIBusErr175 : PCIBusErr170)
		 | CntFull | TxUnderrun | EpicNapiEvent;

	/* Find the connected MII xcvrs.
	   Doing this in खोलो() would allow detecting बाह्यal xcvrs later, but
	   takes much समय and no cards have बाह्यal MII. */
	अणु
		पूर्णांक phy, phy_idx = 0;
		क्रम (phy = 1; phy < 32 && phy_idx < माप(ep->phys); phy++) अणु
			पूर्णांक mii_status = mdio_पढ़ो(dev, phy, MII_BMSR);
			अगर (mii_status != 0xffff  &&  mii_status != 0x0000) अणु
				ep->phys[phy_idx++] = phy;
				dev_info(&pdev->dev,
					"MII transceiver #%d control "
					"%4.4x status %4.4x.\n",
					phy, mdio_पढ़ो(dev, phy, 0), mii_status);
			पूर्ण
		पूर्ण
		ep->mii_phy_cnt = phy_idx;
		अगर (phy_idx != 0) अणु
			phy = ep->phys[0];
			ep->mii.advertising = mdio_पढ़ो(dev, phy, MII_ADVERTISE);
			dev_info(&pdev->dev,
				"Autonegotiation advertising %4.4x link "
				   "partner %4.4x.\n",
				   ep->mii.advertising, mdio_पढ़ो(dev, phy, 5));
		पूर्ण अन्यथा अगर ( ! (ep->chip_flags & NO_MII)) अणु
			dev_warn(&pdev->dev,
				"***WARNING***: No MII transceiver found!\n");
			/* Use the known PHY address of the EPII. */
			ep->phys[0] = 3;
		पूर्ण
		ep->mii.phy_id = ep->phys[0];
	पूर्ण

	/* Turn off the MII xcvr (175 only!), leave the chip in low-घातer mode. */
	अगर (ep->chip_flags & MII_PWRDWN)
		ew32(NVCTL, er32(NVCTL) & ~0x483c);
	ew32(GENCTL, 0x0008);

	/* The lower four bits are the media type. */
	अगर (duplex) अणु
		ep->mii.क्रमce_media = ep->mii.full_duplex = 1;
		dev_info(&pdev->dev, "Forced full duplex requested.\n");
	पूर्ण
	dev->अगर_port = ep->शेष_port = option;

	/* The Epic-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &epic_netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	netअगर_napi_add(dev, &ep->napi, epic_poll, 64);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret < 0)
		जाओ err_out_unmap_rx;

	netdev_info(dev, "%s at %lx, IRQ %d, %pM\n",
		    pci_id_tbl[chip_idx].name,
		    (दीर्घ)pci_resource_start(pdev, EPIC_BAR), pdev->irq,
		    dev->dev_addr);

out:
	वापस ret;

err_out_unmap_rx:
	dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, ep->rx_ring,
			  ep->rx_ring_dma);
err_out_unmap_tx:
	dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, ep->tx_ring,
			  ep->tx_ring_dma);
err_out_iounmap:
	pci_iounmap(pdev, ioaddr);
err_out_मुक्त_netdev:
	मुक्त_netdev(dev);
err_out_मुक्त_res:
	pci_release_regions(pdev);
err_out_disable:
	pci_disable_device(pdev);
	जाओ out;
पूर्ण

/* Serial EEPROM section. */

/*  EEPROM_Ctrl bits. */
#घोषणा EE_SHIFT_CLK	0x04	/* EEPROM shअगरt घड़ी. */
#घोषणा EE_CS			0x02	/* EEPROM chip select. */
#घोषणा EE_DATA_WRITE	0x08	/* EEPROM chip data in. */
#घोषणा EE_WRITE_0		0x01
#घोषणा EE_WRITE_1		0x09
#घोषणा EE_DATA_READ	0x10	/* EEPROM chip data out. */
#घोषणा EE_ENB			(0x0001 | EE_CS)

/* Delay between EEPROM घड़ी transitions.
   This serves to flush the operation to the PCI bus.
 */

#घोषणा eeprom_delay()	er32(EECTL)

/* The EEPROM commands include the alway-set leading bit. */
#घोषणा EE_WRITE_CMD	(5 << 6)
#घोषणा EE_READ64_CMD	(6 << 6)
#घोषणा EE_READ256_CMD	(6 << 8)
#घोषणा EE_ERASE_CMD	(7 << 6)

अटल व्योम epic_disable_पूर्णांक(काष्ठा net_device *dev, काष्ठा epic_निजी *ep)
अणु
	व्योम __iomem *ioaddr = ep->ioaddr;

	ew32(INTMASK, 0x00000000);
पूर्ण

अटल अंतरभूत व्योम __epic_pci_commit(व्योम __iomem *ioaddr)
अणु
#अगर_अघोषित USE_IO_OPS
	er32(INTMASK);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम epic_napi_irq_off(काष्ठा net_device *dev,
				     काष्ठा epic_निजी *ep)
अणु
	व्योम __iomem *ioaddr = ep->ioaddr;

	ew32(INTMASK, ep->irq_mask & ~EpicNapiEvent);
	__epic_pci_commit(ioaddr);
पूर्ण

अटल अंतरभूत व्योम epic_napi_irq_on(काष्ठा net_device *dev,
				    काष्ठा epic_निजी *ep)
अणु
	व्योम __iomem *ioaddr = ep->ioaddr;

	/* No need to commit possible posted ग_लिखो */
	ew32(INTMASK, ep->irq_mask | EpicNapiEvent);
पूर्ण

अटल पूर्णांक पढ़ो_eeprom(काष्ठा epic_निजी *ep, पूर्णांक location)
अणु
	व्योम __iomem *ioaddr = ep->ioaddr;
	पूर्णांक i;
	पूर्णांक retval = 0;
	पूर्णांक पढ़ो_cmd = location |
		(er32(EECTL) & 0x40 ? EE_READ64_CMD : EE_READ256_CMD);

	ew32(EECTL, EE_ENB & ~EE_CS);
	ew32(EECTL, EE_ENB);

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 12; i >= 0; i--) अणु
		लघु dataval = (पढ़ो_cmd & (1 << i)) ? EE_WRITE_1 : EE_WRITE_0;
		ew32(EECTL, EE_ENB | dataval);
		eeprom_delay();
		ew32(EECTL, EE_ENB | dataval | EE_SHIFT_CLK);
		eeprom_delay();
	पूर्ण
	ew32(EECTL, EE_ENB);

	क्रम (i = 16; i > 0; i--) अणु
		ew32(EECTL, EE_ENB | EE_SHIFT_CLK);
		eeprom_delay();
		retval = (retval << 1) | ((er32(EECTL) & EE_DATA_READ) ? 1 : 0);
		ew32(EECTL, EE_ENB);
		eeprom_delay();
	पूर्ण

	/* Terminate the EEPROM access. */
	ew32(EECTL, EE_ENB & ~EE_CS);
	वापस retval;
पूर्ण

#घोषणा MII_READOP		1
#घोषणा MII_WRITEOP		2
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;
	पूर्णांक पढ़ो_cmd = (phy_id << 9) | (location << 4) | MII_READOP;
	पूर्णांक i;

	ew32(MIICtrl, पढ़ो_cmd);
	/* Typical operation takes 25 loops. */
	क्रम (i = 400; i > 0; i--) अणु
		barrier();
		अगर ((er32(MIICtrl) & MII_READOP) == 0) अणु
			/* Work around पढ़ो failure bug. */
			अगर (phy_id == 1 && location < 6 &&
			    er16(MIIData) == 0xffff) अणु
				ew32(MIICtrl, पढ़ो_cmd);
				जारी;
			पूर्ण
			वापस er16(MIIData);
		पूर्ण
	पूर्ण
	वापस 0xffff;
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक value)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;
	पूर्णांक i;

	ew16(MIIData, value);
	ew32(MIICtrl, (phy_id << 9) | (loc << 4) | MII_WRITEOP);
	क्रम (i = 10000; i > 0; i--) अणु
		barrier();
		अगर ((er32(MIICtrl) & MII_WRITEOP) == 0)
			अवरोध;
	पूर्ण
पूर्ण


अटल पूर्णांक epic_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;
	स्थिर पूर्णांक irq = ep->pci_dev->irq;
	पूर्णांक rc, i;

	/* Soft reset the chip. */
	ew32(GENCTL, 0x4001);

	napi_enable(&ep->napi);
	rc = request_irq(irq, epic_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (rc) अणु
		napi_disable(&ep->napi);
		वापस rc;
	पूर्ण

	epic_init_ring(dev);

	ew32(GENCTL, 0x4000);
	/* This magic is करोcumented in SMSC app note 7.15 */
	क्रम (i = 16; i > 0; i--)
		ew32(TEST1, 0x0008);

	/* Pull the chip out of low-घातer mode, enable पूर्णांकerrupts, and set क्रम
	   PCI पढ़ो multiple.  The MIIcfg setting and strange ग_लिखो order are
	   required by the details of which bits are reset and the transceiver
	   wiring on the Ositech CardBus card.
	*/
#अगर 0
	ew32(MIICfg, dev->अगर_port == 1 ? 0x13 : 0x12);
#पूर्ण_अगर
	अगर (ep->chip_flags & MII_PWRDWN)
		ew32(NVCTL, (er32(NVCTL) & ~0x003c) | 0x4800);

	/* Tell the chip to byteswap descriptors on big-endian hosts */
#अगर_घोषित __BIG_ENDIAN
	ew32(GENCTL, 0x4432 | (RX_FIFO_THRESH << 8));
	er32(GENCTL);
	ew32(GENCTL, 0x0432 | (RX_FIFO_THRESH << 8));
#अन्यथा
	ew32(GENCTL, 0x4412 | (RX_FIFO_THRESH << 8));
	er32(GENCTL);
	ew32(GENCTL, 0x0412 | (RX_FIFO_THRESH << 8));
#पूर्ण_अगर

	udelay(20); /* Looks like EPII needs that अगर you want reliable RX init. FIXME: pci posting bug? */

	क्रम (i = 0; i < 3; i++)
		ew32(LAN0 + i*4, le16_to_cpu(((__le16*)dev->dev_addr)[i]));

	ep->tx_threshold = TX_FIFO_THRESH;
	ew32(TxThresh, ep->tx_threshold);

	अगर (media2miictl[dev->अगर_port & 15]) अणु
		अगर (ep->mii_phy_cnt)
			mdio_ग_लिखो(dev, ep->phys[0], MII_BMCR, media2miictl[dev->अगर_port&15]);
		अगर (dev->अगर_port == 1) अणु
			अगर (debug > 1)
				netdev_info(dev, "Using the 10base2 transceiver, MII status %4.4x.\n",
					    mdio_पढ़ो(dev, ep->phys[0], MII_BMSR));
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक mii_lpa = mdio_पढ़ो(dev, ep->phys[0], MII_LPA);
		अगर (mii_lpa != 0xffff) अणु
			अगर ((mii_lpa & LPA_100FULL) || (mii_lpa & 0x01C0) == LPA_10FULL)
				ep->mii.full_duplex = 1;
			अन्यथा अगर (! (mii_lpa & LPA_LPACK))
				mdio_ग_लिखो(dev, ep->phys[0], MII_BMCR, BMCR_ANENABLE|BMCR_ANRESTART);
			अगर (debug > 1)
				netdev_info(dev, "Setting %s-duplex based on MII xcvr %d register read of %4.4x.\n",
					    ep->mii.full_duplex ? "full"
								: "half",
					    ep->phys[0], mii_lpa);
		पूर्ण
	पूर्ण

	ew32(TxCtrl, ep->mii.full_duplex ? 0x7f : 0x79);
	ew32(PRxCDAR, ep->rx_ring_dma);
	ew32(PTxCDAR, ep->tx_ring_dma);

	/* Start the chip's Rx process. */
	set_rx_mode(dev);
	ew32(COMMAND, StartRx | RxQueued);

	netअगर_start_queue(dev);

	/* Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ew32(INTMASK, RxError | RxHeader | EpicNapiEvent | CntFull |
	     ((ep->chip_flags & TYPE2_INTR) ? PCIBusErr175 : PCIBusErr170) |
	     TxUnderrun);

	अगर (debug > 1) अणु
		netdev_dbg(dev, "epic_open() ioaddr %p IRQ %d status %4.4x %s-duplex.\n",
			   ioaddr, irq, er32(GENCTL),
			   ep->mii.full_duplex ? "full" : "half");
	पूर्ण

	/* Set the समयr to चयन to check क्रम link beat and perhaps चयन
	   to an alternate media type. */
	समयr_setup(&ep->समयr, epic_समयr, 0);
	ep->समयr.expires = jअगरfies + 3*HZ;
	add_समयr(&ep->समयr);

	वापस rc;
पूर्ण

/* Reset the chip to recover from a PCI transaction error.
   This may occur at पूर्णांकerrupt समय. */
अटल व्योम epic_छोड़ो(काष्ठा net_device *dev)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;

	netअगर_stop_queue (dev);

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	ew32(INTMASK, 0x00000000);
	/* Stop the chip's Tx and Rx DMA processes. */
	ew16(COMMAND, StopRx | StopTxDMA | StopRxDMA);

	/* Update the error counts. */
	अगर (er16(COMMAND) != 0xffff) अणु
		stats->rx_missed_errors	+= er8(MPCNT);
		stats->rx_frame_errors	+= er8(ALICNT);
		stats->rx_crc_errors	+= er8(CRCCNT);
	पूर्ण

	/* Remove the packets on the Rx queue. */
	epic_rx(dev, RX_RING_SIZE);
पूर्ण

अटल व्योम epic_restart(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;
	पूर्णांक i;

	/* Soft reset the chip. */
	ew32(GENCTL, 0x4001);

	netdev_dbg(dev, "Restarting the EPIC chip, Rx %d/%d Tx %d/%d.\n",
		   ep->cur_rx, ep->dirty_rx, ep->dirty_tx, ep->cur_tx);
	udelay(1);

	/* This magic is करोcumented in SMSC app note 7.15 */
	क्रम (i = 16; i > 0; i--)
		ew32(TEST1, 0x0008);

#अगर_घोषित __BIG_ENDIAN
	ew32(GENCTL, 0x0432 | (RX_FIFO_THRESH << 8));
#अन्यथा
	ew32(GENCTL, 0x0412 | (RX_FIFO_THRESH << 8));
#पूर्ण_अगर
	ew32(MIICfg, dev->अगर_port == 1 ? 0x13 : 0x12);
	अगर (ep->chip_flags & MII_PWRDWN)
		ew32(NVCTL, (er32(NVCTL) & ~0x003c) | 0x4800);

	क्रम (i = 0; i < 3; i++)
		ew32(LAN0 + i*4, le16_to_cpu(((__le16*)dev->dev_addr)[i]));

	ep->tx_threshold = TX_FIFO_THRESH;
	ew32(TxThresh, ep->tx_threshold);
	ew32(TxCtrl, ep->mii.full_duplex ? 0x7f : 0x79);
	ew32(PRxCDAR, ep->rx_ring_dma +
	     (ep->cur_rx % RX_RING_SIZE) * माप(काष्ठा epic_rx_desc));
	ew32(PTxCDAR, ep->tx_ring_dma +
	     (ep->dirty_tx % TX_RING_SIZE) * माप(काष्ठा epic_tx_desc));

	/* Start the chip's Rx process. */
	set_rx_mode(dev);
	ew32(COMMAND, StartRx | RxQueued);

	/* Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ew32(INTMASK, RxError | RxHeader | EpicNapiEvent | CntFull |
	     ((ep->chip_flags & TYPE2_INTR) ? PCIBusErr175 : PCIBusErr170) |
	     TxUnderrun);

	netdev_dbg(dev, "epic_restart() done, cmd status %4.4x, ctl %4.4x interrupt %4.4x.\n",
		   er32(COMMAND), er32(GENCTL), er32(INTSTAT));
पूर्ण

अटल व्योम check_media(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;
	पूर्णांक mii_lpa = ep->mii_phy_cnt ? mdio_पढ़ो(dev, ep->phys[0], MII_LPA) : 0;
	पूर्णांक negotiated = mii_lpa & ep->mii.advertising;
	पूर्णांक duplex = (negotiated & 0x0100) || (negotiated & 0x01C0) == 0x0040;

	अगर (ep->mii.क्रमce_media)
		वापस;
	अगर (mii_lpa == 0xffff)		/* Bogus पढ़ो */
		वापस;
	अगर (ep->mii.full_duplex != duplex) अणु
		ep->mii.full_duplex = duplex;
		netdev_info(dev, "Setting %s-duplex based on MII #%d link partner capability of %4.4x.\n",
			    ep->mii.full_duplex ? "full" : "half",
			    ep->phys[0], mii_lpa);
		ew32(TxCtrl, ep->mii.full_duplex ? 0x7F : 0x79);
	पूर्ण
पूर्ण

अटल व्योम epic_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा epic_निजी *ep = from_समयr(ep, t, समयr);
	काष्ठा net_device *dev = ep->mii.dev;
	व्योम __iomem *ioaddr = ep->ioaddr;
	पूर्णांक next_tick = 5*HZ;

	अगर (debug > 3) अणु
		netdev_dbg(dev, "Media monitor tick, Tx status %8.8x.\n",
			   er32(TxSTAT));
		netdev_dbg(dev, "Other registers are IntMask %4.4x IntStatus %4.4x RxStatus %4.4x.\n",
			   er32(INTMASK), er32(INTSTAT), er32(RxSTAT));
	पूर्ण

	check_media(dev);

	ep->समयr.expires = jअगरfies + next_tick;
	add_समयr(&ep->समयr);
पूर्ण

अटल व्योम epic_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;

	अगर (debug > 0) अणु
		netdev_warn(dev, "Transmit timeout using MII device, Tx status %4.4x.\n",
			    er16(TxSTAT));
		अगर (debug > 1) अणु
			netdev_dbg(dev, "Tx indices: dirty_tx %d, cur_tx %d.\n",
				   ep->dirty_tx, ep->cur_tx);
		पूर्ण
	पूर्ण
	अगर (er16(TxSTAT) & 0x10) अणु		/* Tx FIFO underflow. */
		dev->stats.tx_fअगरo_errors++;
		ew32(COMMAND, RestartTx);
	पूर्ण अन्यथा अणु
		epic_restart(dev);
		ew32(COMMAND, TxQueued);
	पूर्ण

	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;
	अगर (!ep->tx_full)
		netअगर_wake_queue(dev);
पूर्ण

/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल व्योम epic_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	पूर्णांक i;

	ep->tx_full = 0;
	ep->dirty_tx = ep->cur_tx = 0;
	ep->cur_rx = ep->dirty_rx = 0;
	ep->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	/* Initialize all Rx descriptors. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		ep->rx_ring[i].rxstatus = 0;
		ep->rx_ring[i].buflength = ep->rx_buf_sz;
		ep->rx_ring[i].next = ep->rx_ring_dma +
				      (i+1)*माप(काष्ठा epic_rx_desc);
		ep->rx_skbuff[i] = शून्य;
	पूर्ण
	/* Mark the last entry as wrapping the ring. */
	ep->rx_ring[i-1].next = ep->rx_ring_dma;

	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, ep->rx_buf_sz + 2);
		ep->rx_skbuff[i] = skb;
		अगर (skb == शून्य)
			अवरोध;
		skb_reserve(skb, 2);	/* 16 byte align the IP header. */
		ep->rx_ring[i].bufaddr = dma_map_single(&ep->pci_dev->dev,
							skb->data,
							ep->rx_buf_sz,
							DMA_FROM_DEVICE);
		ep->rx_ring[i].rxstatus = DescOwn;
	पूर्ण
	ep->dirty_rx = (अचिन्हित पूर्णांक)(i - RX_RING_SIZE);

	/* The Tx buffer descriptor is filled in as needed, but we
	   करो need to clear the ownership bit. */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		ep->tx_skbuff[i] = शून्य;
		ep->tx_ring[i].txstatus = 0x0000;
		ep->tx_ring[i].next = ep->tx_ring_dma +
			(i+1)*माप(काष्ठा epic_tx_desc);
	पूर्ण
	ep->tx_ring[i-1].next = ep->tx_ring_dma;
पूर्ण

अटल netdev_tx_t epic_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;
	पूर्णांक entry, मुक्त_count;
	u32 ctrl_word;
	अचिन्हित दीर्घ flags;

	अगर (skb_padto(skb, ETH_ZLEN))
		वापस NETDEV_TX_OK;

	/* Caution: the ग_लिखो order is important here, set the field with the
	   "ownership" bit last. */

	/* Calculate the next Tx descriptor entry. */
	spin_lock_irqsave(&ep->lock, flags);
	मुक्त_count = ep->cur_tx - ep->dirty_tx;
	entry = ep->cur_tx % TX_RING_SIZE;

	ep->tx_skbuff[entry] = skb;
	ep->tx_ring[entry].bufaddr = dma_map_single(&ep->pci_dev->dev,
						    skb->data, skb->len,
						    DMA_TO_DEVICE);
	अगर (मुक्त_count < TX_QUEUE_LEN/2) अणु/* Typical path */
		ctrl_word = 0x100000; /* No पूर्णांकerrupt */
	पूर्ण अन्यथा अगर (मुक्त_count == TX_QUEUE_LEN/2) अणु
		ctrl_word = 0x140000; /* Tx-करोne पूर्णांकr. */
	पूर्ण अन्यथा अगर (मुक्त_count < TX_QUEUE_LEN - 1) अणु
		ctrl_word = 0x100000; /* No Tx-करोne पूर्णांकr. */
	पूर्ण अन्यथा अणु
		/* Leave room क्रम an additional entry. */
		ctrl_word = 0x140000; /* Tx-करोne पूर्णांकr. */
		ep->tx_full = 1;
	पूर्ण
	ep->tx_ring[entry].buflength = ctrl_word | skb->len;
	ep->tx_ring[entry].txstatus =
		((skb->len >= ETH_ZLEN ? skb->len : ETH_ZLEN) << 16)
			    | DescOwn;

	ep->cur_tx++;
	अगर (ep->tx_full)
		netअगर_stop_queue(dev);

	spin_unlock_irqrestore(&ep->lock, flags);
	/* Trigger an immediate transmit demand. */
	ew32(COMMAND, TxQueued);

	अगर (debug > 4)
		netdev_dbg(dev, "Queued Tx packet size %d to slot %d, flag %2.2x Tx status %8.8x.\n",
			   skb->len, entry, ctrl_word, er32(TxSTAT));

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम epic_tx_error(काष्ठा net_device *dev, काष्ठा epic_निजी *ep,
			  पूर्णांक status)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;

#अगर_अघोषित final_version
	/* There was an major error, log it. */
	अगर (debug > 1)
		netdev_dbg(dev, "Transmit error, Tx status %8.8x.\n",
			   status);
#पूर्ण_अगर
	stats->tx_errors++;
	अगर (status & 0x1050)
		stats->tx_पातed_errors++;
	अगर (status & 0x0008)
		stats->tx_carrier_errors++;
	अगर (status & 0x0040)
		stats->tx_winकरोw_errors++;
	अगर (status & 0x0010)
		stats->tx_fअगरo_errors++;
पूर्ण

अटल व्योम epic_tx(काष्ठा net_device *dev, काष्ठा epic_निजी *ep)
अणु
	अचिन्हित पूर्णांक dirty_tx, cur_tx;

	/*
	 * Note: अगर this lock becomes a problem we can narrow the locked
	 * region at the cost of occasionally grabbing the lock more बार.
	 */
	cur_tx = ep->cur_tx;
	क्रम (dirty_tx = ep->dirty_tx; cur_tx - dirty_tx > 0; dirty_tx++) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक entry = dirty_tx % TX_RING_SIZE;
		पूर्णांक txstatus = ep->tx_ring[entry].txstatus;

		अगर (txstatus & DescOwn)
			अवरोध;	/* It still hasn't been Txed */

		अगर (likely(txstatus & 0x0001)) अणु
			dev->stats.collisions += (txstatus >> 8) & 15;
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += ep->tx_skbuff[entry]->len;
		पूर्ण अन्यथा
			epic_tx_error(dev, ep, txstatus);

		/* Free the original skb. */
		skb = ep->tx_skbuff[entry];
		dma_unmap_single(&ep->pci_dev->dev,
				 ep->tx_ring[entry].bufaddr, skb->len,
				 DMA_TO_DEVICE);
		dev_consume_skb_irq(skb);
		ep->tx_skbuff[entry] = शून्य;
	पूर्ण

#अगर_अघोषित final_version
	अगर (cur_tx - dirty_tx > TX_RING_SIZE) अणु
		netdev_warn(dev, "Out-of-sync dirty pointer, %d vs. %d, full=%d.\n",
			    dirty_tx, cur_tx, ep->tx_full);
		dirty_tx += TX_RING_SIZE;
	पूर्ण
#पूर्ण_अगर
	ep->dirty_tx = dirty_tx;
	अगर (ep->tx_full && cur_tx - dirty_tx < TX_QUEUE_LEN - 4) अणु
		/* The ring is no दीर्घer full, allow new TX entries. */
		ep->tx_full = 0;
		netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */
अटल irqवापस_t epic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;
	अचिन्हित पूर्णांक handled = 0;
	पूर्णांक status;

	status = er32(INTSTAT);
	/* Acknowledge all of the current पूर्णांकerrupt sources ASAP. */
	ew32(INTSTAT, status & EpicNormalEvent);

	अगर (debug > 4) अणु
		netdev_dbg(dev, "Interrupt, status=%#8.8x new intstat=%#8.8x.\n",
			   status, er32(INTSTAT));
	पूर्ण

	अगर ((status & IntrSummary) == 0)
		जाओ out;

	handled = 1;

	अगर (status & EpicNapiEvent) अणु
		spin_lock(&ep->napi_lock);
		अगर (napi_schedule_prep(&ep->napi)) अणु
			epic_napi_irq_off(dev, ep);
			__napi_schedule(&ep->napi);
		पूर्ण
		spin_unlock(&ep->napi_lock);
	पूर्ण
	status &= ~EpicNapiEvent;

	/* Check uncommon events all at once. */
	अगर (status & (CntFull | TxUnderrun | PCIBusErr170 | PCIBusErr175)) अणु
		काष्ठा net_device_stats *stats = &dev->stats;

		अगर (status == EpicRemoved)
			जाओ out;

		/* Always update the error counts to aव्योम overhead later. */
		stats->rx_missed_errors	+= er8(MPCNT);
		stats->rx_frame_errors	+= er8(ALICNT);
		stats->rx_crc_errors	+= er8(CRCCNT);

		अगर (status & TxUnderrun) अणु /* Tx FIFO underflow. */
			stats->tx_fअगरo_errors++;
			ew32(TxThresh, ep->tx_threshold += 128);
			/* Restart the transmit process. */
			ew32(COMMAND, RestartTx);
		पूर्ण
		अगर (status & PCIBusErr170) अणु
			netdev_err(dev, "PCI Bus Error! status %4.4x.\n",
				   status);
			epic_छोड़ो(dev);
			epic_restart(dev);
		पूर्ण
		/* Clear all error sources. */
		ew32(INTSTAT, status & 0x7f18);
	पूर्ण

out:
	अगर (debug > 3) अणु
		netdev_dbg(dev, "exit interrupt, intr_status=%#4.4x.\n",
			   status);
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक epic_rx(काष्ठा net_device *dev, पूर्णांक budget)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	पूर्णांक entry = ep->cur_rx % RX_RING_SIZE;
	पूर्णांक rx_work_limit = ep->dirty_rx + RX_RING_SIZE - ep->cur_rx;
	पूर्णांक work_करोne = 0;

	अगर (debug > 4)
		netdev_dbg(dev, " In epic_rx(), entry %d %8.8x.\n", entry,
			   ep->rx_ring[entry].rxstatus);

	अगर (rx_work_limit > budget)
		rx_work_limit = budget;

	/* If we own the next entry, it's a new packet. Send it up. */
	जबतक ((ep->rx_ring[entry].rxstatus & DescOwn) == 0) अणु
		पूर्णांक status = ep->rx_ring[entry].rxstatus;

		अगर (debug > 4)
			netdev_dbg(dev, "  epic_rx() status was %8.8x.\n",
				   status);
		अगर (--rx_work_limit < 0)
			अवरोध;
		अगर (status & 0x2006) अणु
			अगर (debug > 2)
				netdev_dbg(dev, "epic_rx() error status was %8.8x.\n",
					   status);
			अगर (status & 0x2000) अणु
				netdev_warn(dev, "Oversized Ethernet frame spanned multiple buffers, status %4.4x!\n",
					    status);
				dev->stats.rx_length_errors++;
			पूर्ण अन्यथा अगर (status & 0x0006)
				/* Rx Frame errors are counted in hardware. */
				dev->stats.rx_errors++;
		पूर्ण अन्यथा अणु
			/* Malloc up new buffer, compatible with net-2e. */
			/* Omit the four octet CRC from the length. */
			लघु pkt_len = (status >> 16) - 4;
			काष्ठा sk_buff *skb;

			अगर (pkt_len > PKT_BUF_SZ - 4) अणु
				netdev_err(dev, "Oversized Ethernet frame, status %x %d bytes.\n",
					   status, pkt_len);
				pkt_len = 1514;
			पूर्ण
			/* Check अगर the packet is दीर्घ enough to accept without copying
			   to a minimally-sized skbuff. */
			अगर (pkt_len < rx_copyअवरोध &&
			    (skb = netdev_alloc_skb(dev, pkt_len + 2)) != शून्य) अणु
				skb_reserve(skb, 2);	/* 16 byte align the IP header */
				dma_sync_single_क्रम_cpu(&ep->pci_dev->dev,
							ep->rx_ring[entry].bufaddr,
							ep->rx_buf_sz,
							DMA_FROM_DEVICE);
				skb_copy_to_linear_data(skb, ep->rx_skbuff[entry]->data, pkt_len);
				skb_put(skb, pkt_len);
				dma_sync_single_क्रम_device(&ep->pci_dev->dev,
							   ep->rx_ring[entry].bufaddr,
							   ep->rx_buf_sz,
							   DMA_FROM_DEVICE);
			पूर्ण अन्यथा अणु
				dma_unmap_single(&ep->pci_dev->dev,
						 ep->rx_ring[entry].bufaddr,
						 ep->rx_buf_sz,
						 DMA_FROM_DEVICE);
				skb_put(skb = ep->rx_skbuff[entry], pkt_len);
				ep->rx_skbuff[entry] = शून्य;
			पूर्ण
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_receive_skb(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		पूर्ण
		work_करोne++;
		entry = (++ep->cur_rx) % RX_RING_SIZE;
	पूर्ण

	/* Refill the Rx ring buffers. */
	क्रम (; ep->cur_rx - ep->dirty_rx > 0; ep->dirty_rx++) अणु
		entry = ep->dirty_rx % RX_RING_SIZE;
		अगर (ep->rx_skbuff[entry] == शून्य) अणु
			काष्ठा sk_buff *skb;
			skb = ep->rx_skbuff[entry] = netdev_alloc_skb(dev, ep->rx_buf_sz + 2);
			अगर (skb == शून्य)
				अवरोध;
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			ep->rx_ring[entry].bufaddr = dma_map_single(&ep->pci_dev->dev,
								    skb->data,
								    ep->rx_buf_sz,
								    DMA_FROM_DEVICE);
			work_करोne++;
		पूर्ण
		/* AV: shouldn't we add a barrier here? */
		ep->rx_ring[entry].rxstatus = DescOwn;
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल व्योम epic_rx_err(काष्ठा net_device *dev, काष्ठा epic_निजी *ep)
अणु
	व्योम __iomem *ioaddr = ep->ioaddr;
	पूर्णांक status;

	status = er32(INTSTAT);

	अगर (status == EpicRemoved)
		वापस;
	अगर (status & RxOverflow) 	/* Missed a Rx frame. */
		dev->stats.rx_errors++;
	अगर (status & (RxOverflow | RxFull))
		ew16(COMMAND, RxQueued);
पूर्ण

अटल पूर्णांक epic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा epic_निजी *ep = container_of(napi, काष्ठा epic_निजी, napi);
	काष्ठा net_device *dev = ep->mii.dev;
	व्योम __iomem *ioaddr = ep->ioaddr;
	पूर्णांक work_करोne;

	epic_tx(dev, ep);

	work_करोne = epic_rx(dev, budget);

	epic_rx_err(dev, ep);

	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&ep->napi_lock, flags);

		ew32(INTSTAT, EpicNapiEvent);
		epic_napi_irq_on(dev, ep);
		spin_unlock_irqrestore(&ep->napi_lock, flags);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक epic_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	काष्ठा pci_dev *pdev = ep->pci_dev;
	व्योम __iomem *ioaddr = ep->ioaddr;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	netअगर_stop_queue(dev);
	napi_disable(&ep->napi);

	अगर (debug > 1)
		netdev_dbg(dev, "Shutting down ethercard, status was %2.2x.\n",
			   er32(INTSTAT));

	del_समयr_sync(&ep->समयr);

	epic_disable_पूर्णांक(dev, ep);

	मुक्त_irq(pdev->irq, dev);

	epic_छोड़ो(dev);

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		skb = ep->rx_skbuff[i];
		ep->rx_skbuff[i] = शून्य;
		ep->rx_ring[i].rxstatus = 0;		/* Not owned by Epic chip. */
		ep->rx_ring[i].buflength = 0;
		अगर (skb) अणु
			dma_unmap_single(&pdev->dev, ep->rx_ring[i].bufaddr,
					 ep->rx_buf_sz, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(skb);
		पूर्ण
		ep->rx_ring[i].bufaddr = 0xBADF00D0; /* An invalid address. */
	पूर्ण
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		skb = ep->tx_skbuff[i];
		ep->tx_skbuff[i] = शून्य;
		अगर (!skb)
			जारी;
		dma_unmap_single(&pdev->dev, ep->tx_ring[i].bufaddr, skb->len,
				 DMA_TO_DEVICE);
		dev_kमुक्त_skb(skb);
	पूर्ण

	/* Green! Leave the chip in low-घातer mode. */
	ew32(GENCTL, 0x0008);

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *epic_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;

	अगर (netअगर_running(dev)) अणु
		काष्ठा net_device_stats *stats = &dev->stats;

		stats->rx_missed_errors	+= er8(MPCNT);
		stats->rx_frame_errors	+= er8(ALICNT);
		stats->rx_crc_errors	+= er8(CRCCNT);
	पूर्ण

	वापस &dev->stats;
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor.
   Note that we only use exclusion around actually queueing the
   new frame, not around filling ep->setup_frame.  This is non-deterministic
   when re-entered but still correct. */

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;
	अचिन्हित अक्षर mc_filter[8];		 /* Multicast hash filter */
	पूर्णांक i;

	अगर (dev->flags & IFF_PROMISC) अणु			/* Set promiscuous. */
		ew32(RxCtrl, 0x002c);
		/* Unconditionally log net taps. */
		स_रखो(mc_filter, 0xff, माप(mc_filter));
	पूर्ण अन्यथा अगर ((!netdev_mc_empty(dev)) || (dev->flags & IFF_ALLMULTI)) अणु
		/* There is apparently a chip bug, so the multicast filter
		   is never enabled. */
		/* Too many to filter perfectly -- accept all multicasts. */
		स_रखो(mc_filter, 0xff, माप(mc_filter));
		ew32(RxCtrl, 0x000c);
	पूर्ण अन्यथा अगर (netdev_mc_empty(dev)) अणु
		ew32(RxCtrl, 0x0004);
		वापस;
	पूर्ण अन्यथा अणु					/* Never executed, क्रम now. */
		काष्ठा netdev_hw_addr *ha;

		स_रखो(mc_filter, 0, माप(mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अचिन्हित पूर्णांक bit_nr =
				ether_crc_le(ETH_ALEN, ha->addr) & 0x3f;
			mc_filter[bit_nr >> 3] |= (1 << bit_nr);
		पूर्ण
	पूर्ण
	/* ToDo: perhaps we need to stop the Tx and Rx process here? */
	अगर (स_भेद(mc_filter, ep->mc_filter, माप(mc_filter))) अणु
		क्रम (i = 0; i < 4; i++)
			ew16(MC0 + i*4, ((u16 *)mc_filter)[i]);
		स_नकल(ep->mc_filter, mc_filter, माप(mc_filter));
	पूर्ण
पूर्ण

अटल व्योम netdev_get_drvinfo (काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा epic_निजी *np = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(np->pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक netdev_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा epic_निजी *np = netdev_priv(dev);

	spin_lock_irq(&np->lock);
	mii_ethtool_get_link_ksettings(&np->mii, cmd);
	spin_unlock_irq(&np->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा epic_निजी *np = netdev_priv(dev);
	पूर्णांक rc;

	spin_lock_irq(&np->lock);
	rc = mii_ethtool_set_link_ksettings(&np->mii, cmd);
	spin_unlock_irq(&np->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक netdev_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *np = netdev_priv(dev);
	वापस mii_nway_restart(&np->mii);
पूर्ण

अटल u32 netdev_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *np = netdev_priv(dev);
	वापस mii_link_ok(&np->mii);
पूर्ण

अटल u32 netdev_get_msglevel(काष्ठा net_device *dev)
अणु
	वापस debug;
पूर्ण

अटल व्योम netdev_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	debug = value;
पूर्ण

अटल पूर्णांक ethtool_begin(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;

	अगर (ep->ethtool_ops_nesting == U32_MAX)
		वापस -EBUSY;
	/* घातer-up, अगर पूर्णांकerface is करोwn */
	अगर (!ep->ethtool_ops_nesting++ && !netअगर_running(dev)) अणु
		ew32(GENCTL, 0x0200);
		ew32(NVCTL, (er32(NVCTL) & ~0x003c) | 0x4800);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ethtool_complete(काष्ठा net_device *dev)
अणु
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;

	/* घातer-करोwn, अगर पूर्णांकerface is करोwn */
	अगर (!--ep->ethtool_ops_nesting && !netअगर_running(dev)) अणु
		ew32(GENCTL, 0x0008);
		ew32(NVCTL, (er32(NVCTL) & ~0x483c) | 0x0000);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
	.nway_reset		= netdev_nway_reset,
	.get_link		= netdev_get_link,
	.get_msglevel		= netdev_get_msglevel,
	.set_msglevel		= netdev_set_msglevel,
	.begin			= ethtool_begin,
	.complete		= ethtool_complete,
	.get_link_ksettings	= netdev_get_link_ksettings,
	.set_link_ksettings	= netdev_set_link_ksettings,
पूर्ण;

अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा epic_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	पूर्णांक rc;

	/* घातer-up, अगर पूर्णांकerface is करोwn */
	अगर (! netअगर_running(dev)) अणु
		ew32(GENCTL, 0x0200);
		ew32(NVCTL, (er32(NVCTL) & ~0x003c) | 0x4800);
	पूर्ण

	/* all non-ethtool ioctls (the SIOC[GS]MIIxxx ioctls) */
	spin_lock_irq(&np->lock);
	rc = generic_mii_ioctl(&np->mii, data, cmd, शून्य);
	spin_unlock_irq(&np->lock);

	/* घातer-करोwn, अगर पूर्णांकerface is करोwn */
	अगर (! netअगर_running(dev)) अणु
		ew32(GENCTL, 0x0008);
		ew32(NVCTL, (er32(NVCTL) & ~0x483c) | 0x0000);
	पूर्ण
	वापस rc;
पूर्ण


अटल व्योम epic_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा epic_निजी *ep = netdev_priv(dev);

	dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, ep->tx_ring,
			  ep->tx_ring_dma);
	dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, ep->rx_ring,
			  ep->rx_ring_dma);
	unरेजिस्टर_netdev(dev);
	pci_iounmap(pdev, ep->ioaddr);
	pci_release_regions(pdev);
	मुक्त_netdev(dev);
	pci_disable_device(pdev);
	/* pci_घातer_off(pdev, -1); */
पूर्ण

अटल पूर्णांक __maybe_unused epic_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा epic_निजी *ep = netdev_priv(dev);
	व्योम __iomem *ioaddr = ep->ioaddr;

	अगर (!netअगर_running(dev))
		वापस 0;
	epic_छोड़ो(dev);
	/* Put the chip पूर्णांकo low-घातer mode. */
	ew32(GENCTL, 0x0008);
	/* pci_घातer_off(pdev, -1); */
	वापस 0;
पूर्ण


अटल पूर्णांक __maybe_unused epic_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	अगर (!netअगर_running(dev))
		वापस 0;
	epic_restart(dev);
	/* pci_घातer_on(pdev); */
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(epic_pm_ops, epic_suspend, epic_resume);

अटल काष्ठा pci_driver epic_driver = अणु
	.name		= DRV_NAME,
	.id_table	= epic_pci_tbl,
	.probe		= epic_init_one,
	.हटाओ		= epic_हटाओ_one,
	.driver.pm	= &epic_pm_ops,
पूर्ण;


अटल पूर्णांक __init epic_init (व्योम)
अणु
/* when a module, this is prपूर्णांकed whether or not devices are found in probe */
#अगर_घोषित MODULE
	pr_info("%s%s\n", version, version2);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&epic_driver);
पूर्ण


अटल व्योम __निकास epic_cleanup (व्योम)
अणु
	pci_unरेजिस्टर_driver (&epic_driver);
पूर्ण


module_init(epic_init);
module_निकास(epic_cleanup);
