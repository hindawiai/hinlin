<शैली गुरु>
/* winbond-840.c: A Linux PCI network adapter device driver. */
/*
	Written 1998-2001 by Donald Becker.

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
	http://www.scyld.com/network/drivers.hपंचांगl

	Do not हटाओ the copyright inक्रमmation.
	Do not change the version inक्रमmation unless an improvement has been made.
	Merely removing my name, as Compex has करोne in the past, करोes not count
	as an improvement.

	Changelog:
	* ported to 2.4
		???
	* spin lock update, memory barriers, new style dma mappings
		limit each tx buffer to < 1024 bytes
		हटाओ DescIntr from Rx descriptors (that's an Tx flag)
		हटाओ next poपूर्णांकer from Tx descriptors
		synchronize tx_q_bytes
		software reset in tx_समयout
			Copyright (C) 2000 Manfred Spraul
	* further cleanups
		घातer management.
		support क्रम big endian descriptors
			Copyright (C) 2001 Manfred Spraul
  	* ethtool support (jgarzik)
	* Replace some MII-related magic numbers with स्थिरants (jgarzik)

	TODO:
	* enable pci_घातer_off
	* Wake-On-LAN
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"winbond-840"

/* Automatically extracted configuration info:
probe-func: winbond840_probe
config-in: tristate 'Winbond W89c840 Ethernet support' CONFIG_WINBOND_840

c-help-name: Winbond W89c840 PCI Ethernet support
c-help-symbol: CONFIG_WINBOND_840
c-help: This driver is क्रम the Winbond W89c840 chip.  It also works with
c-help: the TX9882 chip on the Compex RL100-ATX board.
c-help: More specअगरic inक्रमmation and updates are available from
c-help: http://www.scyld.com/network/drivers.hपंचांगl
*/

/* The user-configurable values.
   These may be modअगरied when a driver module is loaded.*/

अटल पूर्णांक debug = 1;			/* 1 normal messages, 0 quiet .. 7 verbose. */
अटल पूर्णांक max_पूर्णांकerrupt_work = 20;
/* Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
   The '840 uses a 64 element hash table based on the Ethernet CRC.  */
अटल पूर्णांक multicast_filter_limit = 32;

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
   Setting to > 1518 effectively disables this feature. */
अटल पूर्णांक rx_copyअवरोध;

/* Used to pass the media type, etc.
   Both 'options[]' and 'full_duplex[]' should exist क्रम driver
   पूर्णांकeroperability.
   The media type is usually passed in 'options[]'.
*/
#घोषणा MAX_UNITS 8		/* More are supported, limit only on options */
अटल पूर्णांक options[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
अटल पूर्णांक full_duplex[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;

/* Operational parameters that are set at compile समय. */

/* Keep the ring sizes a घातer of two क्रम compile efficiency.
   The compiler will convert <अचिन्हित>'%'<2^N> पूर्णांकo a bit mask.
   Making the Tx ring too large decreases the effectiveness of channel
   bonding and packet priority.
   There are no ill effects from too-large receive rings. */
#घोषणा TX_QUEUE_LEN	10		/* Limit ring entries actually used.  */
#घोषणा TX_QUEUE_LEN_RESTART	5

#घोषणा TX_BUFLIMIT	(1024-128)

/* The presumed FIFO size क्रम working around the Tx-FIFO-overflow bug.
   To aव्योम overflowing we करोn't queue again until we have room क्रम a
   full-size packet.
 */
#घोषणा TX_FIFO_SIZE (2048)
#घोषणा TX_BUG_FIFO_LIMIT (TX_FIFO_SIZE-1514-16)


/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (2*HZ)

/* Include files, deचिन्हित to support most kernel versions 2.0.0 and later. */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/crc32.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>		/* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#समावेश "tulip.h"

#अघोषित PKT_BUF_SZ			/* tulip.h also defines this */
#घोषणा PKT_BUF_SZ		1536	/* Size of each temporary Rx buffer.*/

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("Winbond W89c840 Ethernet driver");
MODULE_LICENSE("GPL");

module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
module_param(debug, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param(multicast_filter_limit, पूर्णांक, 0);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "winbond-840 maximum events handled per interrupt");
MODULE_PARM_DESC(debug, "winbond-840 debug level (0-6)");
MODULE_PARM_DESC(rx_copyअवरोध, "winbond-840 copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(multicast_filter_limit, "winbond-840 maximum number of filtered multicast addresses");
MODULE_PARM_DESC(options, "winbond-840: Bits 0-3: media type, bit 17: full duplex");
MODULE_PARM_DESC(full_duplex, "winbond-840 full duplex setting(s) (1)");

/*
				Theory of Operation

I. Board Compatibility

This driver is क्रम the Winbond w89c840 chip.

II. Board-specअगरic settings

None.

III. Driver operation

This chip is very similar to the Digital 21*4* "Tulip" family.  The first
twelve रेजिस्टरs and the descriptor क्रमmat are nearly identical.  Read a
Tulip manual क्रम operational details.

A signअगरicant dअगरference is that the multicast filter and station address are
stored in रेजिस्टरs rather than loaded through a pseuकरो-transmit packet.

Unlike the Tulip, transmit buffers are limited to 1KB.  To transmit a
full-sized packet we must use both data buffers in a descriptor.  Thus the
driver uses ring mode where descriptors are implicitly sequential in memory,
rather than using the second descriptor address as a chain poपूर्णांकer to
subsequent descriptors.

IV. Notes

If you are going to almost clone a Tulip, why not go all the way and aव्योम
the need क्रम a new driver?

IVb. References

http://www.scyld.com/expert/100mbps.hपंचांगl
http://www.scyld.com/expert/NWay.hपंचांगl
http://www.winbond.com.tw/

IVc. Errata

A horrible bug exists in the transmit FIFO.  Apparently the chip करोesn't
correctly detect a full FIFO, and queuing more than 2048 bytes may result in
silent data corruption.

Test with 'ping -s 10000' on a fast computer.

*/



/*
  PCI probe table.
*/
क्रमागत chip_capability_flags अणु
	CanHaveMII=1, HasBrokenTx=2, AlwaysFDX=4, FDXOnNoMII=8,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id w840_pci_tbl[] = अणु
	अणु 0x1050, 0x0840, PCI_ANY_ID, 0x8153,     0, 0, 0 पूर्ण,
	अणु 0x1050, 0x0840, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1 पूर्ण,
	अणु 0x11f6, 0x2011, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 2 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, w840_pci_tbl);

क्रमागत अणु
	netdev_res_size		= 128,	/* size of PCI BAR resource */
पूर्ण;

काष्ठा pci_id_info अणु
        स्थिर अक्षर *name;
        पूर्णांक drv_flags;		/* Driver use, पूर्णांकended as capability flags. */
पूर्ण;

अटल स्थिर काष्ठा pci_id_info pci_id_tbl[] = अणु
	अणु 				/* Someसमय a Level-One चयन card. */
	  "Winbond W89c840",	CanHaveMII | HasBrokenTx | FDXOnNoMIIपूर्ण,
	अणु "Winbond W89c840",	CanHaveMII | HasBrokenTxपूर्ण,
	अणु "Compex RL100-ATX",	CanHaveMII | HasBrokenTxपूर्ण,
	अणु पूर्ण	/* terminate list. */
पूर्ण;

/* This driver was written to use PCI memory space, however some x86 प्रणालीs
   work only with I/O space accesses. See CONFIG_TULIP_MMIO in .config
*/

/* Offsets to the Command and Status Registers, "CSRs".
   While similar to the Tulip, these रेजिस्टरs are दीर्घword aligned.
   Note: It's not useful to define symbolic names क्रम every रेजिस्टर bit in
   the device.  The name can only partially करोcument the semantics and make
   the driver दीर्घer and more dअगरficult to पढ़ो.
*/
क्रमागत w840_offsets अणु
	PCIBusCfg=0x00, TxStartDemand=0x04, RxStartDemand=0x08,
	RxRingPtr=0x0C, TxRingPtr=0x10,
	IntrStatus=0x14, NetworkConfig=0x18, IntrEnable=0x1C,
	RxMissed=0x20, EECtrl=0x24, MIICtrl=0x24, BootRom=0x28, GPTimer=0x2C,
	CurRxDescAddr=0x30, CurRxBufAddr=0x34,			/* Debug use */
	MulticastFilter0=0x38, MulticastFilter1=0x3C, StationAddr=0x40,
	CurTxDescAddr=0x4C, CurTxBufAddr=0x50,
पूर्ण;

/* Bits in the NetworkConfig रेजिस्टर. */
क्रमागत rx_mode_bits अणु
	AcceptErr=0x80,
	RxAcceptBroadcast=0x20, AcceptMulticast=0x10,
	RxAcceptAllPhys=0x08, AcceptMyPhys=0x02,
पूर्ण;

क्रमागत mii_reg_bits अणु
	MDIO_ShअगरtClk=0x10000, MDIO_DataIn=0x80000, MDIO_DataOut=0x20000,
	MDIO_EnbOutput=0x40000, MDIO_EnbIn = 0x00000,
पूर्ण;

/* The Tulip Rx and Tx buffer descriptors. */
काष्ठा w840_rx_desc अणु
	s32 status;
	s32 length;
	u32 buffer1;
	u32 buffer2;
पूर्ण;

काष्ठा w840_tx_desc अणु
	s32 status;
	s32 length;
	u32 buffer1, buffer2;
पूर्ण;

#घोषणा MII_CNT		1 /* winbond only supports one MII */
काष्ठा netdev_निजी अणु
	काष्ठा w840_rx_desc *rx_ring;
	dma_addr_t	rx_addr[RX_RING_SIZE];
	काष्ठा w840_tx_desc *tx_ring;
	dma_addr_t	tx_addr[TX_RING_SIZE];
	dma_addr_t ring_dma_addr;
	/* The addresses of receive-in-place skbuffs. */
	काष्ठा sk_buff* rx_skbuff[RX_RING_SIZE];
	/* The saved address of a sent-in-place packet/buffer, क्रम later मुक्त(). */
	काष्ठा sk_buff* tx_skbuff[TX_RING_SIZE];
	काष्ठा net_device_stats stats;
	काष्ठा समयr_list समयr;	/* Media monitoring समयr. */
	/* Frequently used values: keep some adjacent क्रम cache effect. */
	spinlock_t lock;
	पूर्णांक chip_id, drv_flags;
	काष्ठा pci_dev *pci_dev;
	पूर्णांक csr6;
	काष्ठा w840_rx_desc *rx_head_desc;
	अचिन्हित पूर्णांक cur_rx, dirty_rx;		/* Producer/consumer ring indices */
	अचिन्हित पूर्णांक rx_buf_sz;				/* Based on MTU+slack. */
	अचिन्हित पूर्णांक cur_tx, dirty_tx;
	अचिन्हित पूर्णांक tx_q_bytes;
	अचिन्हित पूर्णांक tx_full;				/* The Tx queue is full. */
	/* MII transceiver section. */
	पूर्णांक mii_cnt;						/* MII device addresses. */
	अचिन्हित अक्षर phys[MII_CNT];		/* MII device addresses, but only the first is used */
	u32 mii;
	काष्ठा mii_अगर_info mii_अगर;
	व्योम __iomem *base_addr;
पूर्ण;

अटल पूर्णांक  eeprom_पढ़ो(व्योम __iomem *ioaddr, पूर्णांक location);
अटल पूर्णांक  mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value);
अटल पूर्णांक  netdev_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक  update_link(काष्ठा net_device *dev);
अटल व्योम netdev_समयr(काष्ठा समयr_list *t);
अटल व्योम init_rxtx_rings(काष्ठा net_device *dev);
अटल व्योम मुक्त_rxtx_rings(काष्ठा netdev_निजी *np);
अटल व्योम init_रेजिस्टरs(काष्ठा net_device *dev);
अटल व्योम tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल पूर्णांक alloc_ringdesc(काष्ठा net_device *dev);
अटल व्योम मुक्त_ringdesc(काष्ठा netdev_निजी *np);
अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance);
अटल व्योम netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status);
अटल पूर्णांक  netdev_rx(काष्ठा net_device *dev);
अटल u32 __set_rx_mode(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev);
अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;
अटल पूर्णांक  netdev_बंद(काष्ठा net_device *dev);

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= netdev_खोलो,
	.nकरो_stop		= netdev_बंद,
	.nकरो_start_xmit		= start_tx,
	.nकरो_get_stats		= get_stats,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_करो_ioctl		= netdev_ioctl,
	.nकरो_tx_समयout		= tx_समयout,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक w840_probe1(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा netdev_निजी *np;
	अटल पूर्णांक find_cnt;
	पूर्णांक chip_idx = ent->driver_data;
	पूर्णांक irq;
	पूर्णांक i, option = find_cnt < MAX_UNITS ? options[find_cnt] : 0;
	व्योम __iomem *ioaddr;

	i = pci_enable_device(pdev);
	अगर (i) वापस i;

	pci_set_master(pdev);

	irq = pdev->irq;

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		pr_warn("Device %s disabled due to DMA limitations\n",
			pci_name(pdev));
		वापस -EIO;
	पूर्ण
	dev = alloc_etherdev(माप(*np));
	अगर (!dev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);

	अगर (pci_request_regions(pdev, DRV_NAME))
		जाओ err_out_netdev;

	ioaddr = pci_iomap(pdev, TULIP_BAR, netdev_res_size);
	अगर (!ioaddr)
		जाओ err_out_मुक्त_res;

	क्रम (i = 0; i < 3; i++)
		((__le16 *)dev->dev_addr)[i] = cpu_to_le16(eeprom_पढ़ो(ioaddr, i));

	/* Reset the chip to erase previous misconfiguration.
	   No hold समय required! */
	ioग_लिखो32(0x00000001, ioaddr + PCIBusCfg);

	np = netdev_priv(dev);
	np->pci_dev = pdev;
	np->chip_id = chip_idx;
	np->drv_flags = pci_id_tbl[chip_idx].drv_flags;
	spin_lock_init(&np->lock);
	np->mii_अगर.dev = dev;
	np->mii_अगर.mdio_पढ़ो = mdio_पढ़ो;
	np->mii_अगर.mdio_ग_लिखो = mdio_ग_लिखो;
	np->base_addr = ioaddr;

	pci_set_drvdata(pdev, dev);

	अगर (dev->mem_start)
		option = dev->mem_start;

	/* The lower four bits are the media type. */
	अगर (option > 0) अणु
		अगर (option & 0x200)
			np->mii_अगर.full_duplex = 1;
		अगर (option & 15)
			dev_info(&dev->dev,
				 "ignoring user supplied media type %d",
				 option & 15);
	पूर्ण
	अगर (find_cnt < MAX_UNITS  &&  full_duplex[find_cnt] > 0)
		np->mii_अगर.full_duplex = 1;

	अगर (np->mii_अगर.full_duplex)
		np->mii_अगर.क्रमce_media = 1;

	/* The chip-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	i = रेजिस्टर_netdev(dev);
	अगर (i)
		जाओ err_out_cleardev;

	dev_info(&dev->dev, "%s at %p, %pM, IRQ %d\n",
		 pci_id_tbl[chip_idx].name, ioaddr, dev->dev_addr, irq);

	अगर (np->drv_flags & CanHaveMII) अणु
		पूर्णांक phy, phy_idx = 0;
		क्रम (phy = 1; phy < 32 && phy_idx < MII_CNT; phy++) अणु
			पूर्णांक mii_status = mdio_पढ़ो(dev, phy, MII_BMSR);
			अगर (mii_status != 0xffff  &&  mii_status != 0x0000) अणु
				np->phys[phy_idx++] = phy;
				np->mii_अगर.advertising = mdio_पढ़ो(dev, phy, MII_ADVERTISE);
				np->mii = (mdio_पढ़ो(dev, phy, MII_PHYSID1) << 16)+
						mdio_पढ़ो(dev, phy, MII_PHYSID2);
				dev_info(&dev->dev,
					 "MII PHY %08xh found at address %d, status 0x%04x advertising %04x\n",
					 np->mii, phy, mii_status,
					 np->mii_अगर.advertising);
			पूर्ण
		पूर्ण
		np->mii_cnt = phy_idx;
		np->mii_अगर.phy_id = np->phys[0];
		अगर (phy_idx == 0) अणु
			dev_warn(&dev->dev,
				 "MII PHY not found -- this device may not operate correctly\n");
		पूर्ण
	पूर्ण

	find_cnt++;
	वापस 0;

err_out_cleardev:
	pci_iounmap(pdev, ioaddr);
err_out_मुक्त_res:
	pci_release_regions(pdev);
err_out_netdev:
	मुक्त_netdev (dev);
	वापस -ENODEV;
पूर्ण


/* Read the EEPROM and MII Management Data I/O (MDIO) पूर्णांकerfaces.  These are
   often serial bit streams generated by the host processor.
   The example below is क्रम the common 93c46 EEPROM, 64 16 bit words. */

/* Delay between EEPROM घड़ी transitions.
   No extra delay is needed with 33Mhz PCI, but future 66Mhz access may need
   a delay.  Note that pre-2.0.34 kernels had a cache-alignment bug that
   made udelay() unreliable.
   The old method of using an ISA access as a delay, __SLOW_DOWN_IO__, is
   deprecated.
*/
#घोषणा eeprom_delay(ee_addr)	ioपढ़ो32(ee_addr)

क्रमागत EEPROM_Ctrl_Bits अणु
	EE_ShअगरtClk=0x02, EE_Write0=0x801, EE_Write1=0x805,
	EE_ChipSelect=0x801, EE_DataIn=0x08,
पूर्ण;

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
	ioग_लिखो32(EE_ChipSelect, ee_addr);

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 10; i >= 0; i--) अणु
		लघु dataval = (पढ़ो_cmd & (1 << i)) ? EE_Write1 : EE_Write0;
		ioग_लिखो32(dataval, ee_addr);
		eeprom_delay(ee_addr);
		ioग_लिखो32(dataval | EE_ShअगरtClk, ee_addr);
		eeprom_delay(ee_addr);
	पूर्ण
	ioग_लिखो32(EE_ChipSelect, ee_addr);
	eeprom_delay(ee_addr);

	क्रम (i = 16; i > 0; i--) अणु
		ioग_लिखो32(EE_ChipSelect | EE_ShअगरtClk, ee_addr);
		eeprom_delay(ee_addr);
		retval = (retval << 1) | ((ioपढ़ो32(ee_addr) & EE_DataIn) ? 1 : 0);
		ioग_लिखो32(EE_ChipSelect, ee_addr);
		eeprom_delay(ee_addr);
	पूर्ण

	/* Terminate the EEPROM access. */
	ioग_लिखो32(0, ee_addr);
	वापस retval;
पूर्ण

/*  MII transceiver control section.
	Read and ग_लिखो the MII रेजिस्टरs using software-generated serial
	MDIO protocol.  See the MII specअगरications or DP83840A data sheet
	क्रम details.

	The maximum data घड़ी rate is 2.5 Mhz.  The minimum timing is usually
	met by back-to-back 33Mhz PCI cycles. */
#घोषणा mdio_delay(mdio_addr) ioपढ़ो32(mdio_addr)

/* Set अगरf a MII transceiver on any पूर्णांकerface requires mdio preamble.
   This only set with older transceivers, so the extra
   code size of a per-पूर्णांकerface flag is not worthजबतक. */
अटल अक्षर mii_preamble_required = 1;

#घोषणा MDIO_WRITE0 (MDIO_EnbOutput)
#घोषणा MDIO_WRITE1 (MDIO_DataOut | MDIO_EnbOutput)

/* Generate the preamble required क्रम initial synchronization and
   a few older transceivers. */
अटल व्योम mdio_sync(व्योम __iomem *mdio_addr)
अणु
	पूर्णांक bits = 32;

	/* Establish sync by sending at least 32 logic ones. */
	जबतक (--bits >= 0) अणु
		ioग_लिखो32(MDIO_WRITE1, mdio_addr);
		mdio_delay(mdio_addr);
		ioग_लिखो32(MDIO_WRITE1 | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay(mdio_addr);
	पूर्ण
पूर्ण

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *mdio_addr = np->base_addr + MIICtrl;
	पूर्णांक mii_cmd = (0xf6 << 10) | (phy_id << 5) | location;
	पूर्णांक i, retval = 0;

	अगर (mii_preamble_required)
		mdio_sync(mdio_addr);

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 15; i >= 0; i--) अणु
		पूर्णांक dataval = (mii_cmd & (1 << i)) ? MDIO_WRITE1 : MDIO_WRITE0;

		ioग_लिखो32(dataval, mdio_addr);
		mdio_delay(mdio_addr);
		ioग_लिखो32(dataval | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay(mdio_addr);
	पूर्ण
	/* Read the two transition, 16 data, and wire-idle bits. */
	क्रम (i = 20; i > 0; i--) अणु
		ioग_लिखो32(MDIO_EnbIn, mdio_addr);
		mdio_delay(mdio_addr);
		retval = (retval << 1) | ((ioपढ़ो32(mdio_addr) & MDIO_DataIn) ? 1 : 0);
		ioग_लिखो32(MDIO_EnbIn | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay(mdio_addr);
	पूर्ण
	वापस (retval>>1) & 0xffff;
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *mdio_addr = np->base_addr + MIICtrl;
	पूर्णांक mii_cmd = (0x5002 << 16) | (phy_id << 23) | (location<<18) | value;
	पूर्णांक i;

	अगर (location == 4  &&  phy_id == np->phys[0])
		np->mii_अगर.advertising = value;

	अगर (mii_preamble_required)
		mdio_sync(mdio_addr);

	/* Shअगरt the command bits out. */
	क्रम (i = 31; i >= 0; i--) अणु
		पूर्णांक dataval = (mii_cmd & (1 << i)) ? MDIO_WRITE1 : MDIO_WRITE0;

		ioग_लिखो32(dataval, mdio_addr);
		mdio_delay(mdio_addr);
		ioग_लिखो32(dataval | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay(mdio_addr);
	पूर्ण
	/* Clear out extra bits. */
	क्रम (i = 2; i > 0; i--) अणु
		ioग_लिखो32(MDIO_EnbIn, mdio_addr);
		mdio_delay(mdio_addr);
		ioग_लिखो32(MDIO_EnbIn | MDIO_ShअगरtClk, mdio_addr);
		mdio_delay(mdio_addr);
	पूर्ण
पूर्ण


अटल पूर्णांक netdev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;
	स्थिर पूर्णांक irq = np->pci_dev->irq;
	पूर्णांक i;

	ioग_लिखो32(0x00000001, ioaddr + PCIBusCfg);		/* Reset */

	netअगर_device_detach(dev);
	i = request_irq(irq, पूर्णांकr_handler, IRQF_SHARED, dev->name, dev);
	अगर (i)
		जाओ out_err;

	अगर (debug > 1)
		netdev_dbg(dev, "%s() irq %d\n", __func__, irq);

	i = alloc_ringdesc(dev);
	अगर (i)
		जाओ out_err;

	spin_lock_irq(&np->lock);
	netअगर_device_attach(dev);
	init_रेजिस्टरs(dev);
	spin_unlock_irq(&np->lock);

	netअगर_start_queue(dev);
	अगर (debug > 2)
		netdev_dbg(dev, "Done %s()\n", __func__);

	/* Set the समयr to check क्रम link beat. */
	समयr_setup(&np->समयr, netdev_समयr, 0);
	np->समयr.expires = jअगरfies + 1*HZ;
	add_समयr(&np->समयr);
	वापस 0;
out_err:
	netअगर_device_attach(dev);
	वापस i;
पूर्ण

#घोषणा MII_DAVICOM_DM9101	0x0181b800

अटल पूर्णांक update_link(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक duplex, fasteth, result, mii_reg;

	/* BSMR */
	mii_reg = mdio_पढ़ो(dev, np->phys[0], MII_BMSR);

	अगर (mii_reg == 0xffff)
		वापस np->csr6;
	/* reपढ़ो: the link status bit is sticky */
	mii_reg = mdio_पढ़ो(dev, np->phys[0], MII_BMSR);
	अगर (!(mii_reg & 0x4)) अणु
		अगर (netअगर_carrier_ok(dev)) अणु
			अगर (debug)
				dev_info(&dev->dev,
					 "MII #%d reports no link. Disabling watchdog\n",
					 np->phys[0]);
			netअगर_carrier_off(dev);
		पूर्ण
		वापस np->csr6;
	पूर्ण
	अगर (!netअगर_carrier_ok(dev)) अणु
		अगर (debug)
			dev_info(&dev->dev,
				 "MII #%d link is back. Enabling watchdog\n",
				 np->phys[0]);
		netअगर_carrier_on(dev);
	पूर्ण

	अगर ((np->mii & ~0xf) == MII_DAVICOM_DM9101) अणु
		/* If the link partner करोesn't support स्वतःnegotiation
		 * the MII detects it's abilities with the "parallel detection".
		 * Some MIIs update the LPA रेजिस्टर to the result of the parallel
		 * detection, some करोn't.
		 * The Davicom PHY [at least 0181b800] करोesn't.
		 * Instead bit 9 and 13 of the BMCR are updated to the result
		 * of the negotiation..
		 */
		mii_reg = mdio_पढ़ो(dev, np->phys[0], MII_BMCR);
		duplex = mii_reg & BMCR_FULLDPLX;
		fasteth = mii_reg & BMCR_SPEED100;
	पूर्ण अन्यथा अणु
		पूर्णांक negotiated;
		mii_reg	= mdio_पढ़ो(dev, np->phys[0], MII_LPA);
		negotiated = mii_reg & np->mii_अगर.advertising;

		duplex = (negotiated & LPA_100FULL) || ((negotiated & 0x02C0) == LPA_10FULL);
		fasteth = negotiated & 0x380;
	पूर्ण
	duplex |= np->mii_अगर.क्रमce_media;
	/* हटाओ fastether and fullduplex */
	result = np->csr6 & ~0x20000200;
	अगर (duplex)
		result |= 0x200;
	अगर (fasteth)
		result |= 0x20000000;
	अगर (result != np->csr6 && debug)
		dev_info(&dev->dev,
			 "Setting %dMBit-%s-duplex based on MII#%d\n",
			 fasteth ? 100 : 10, duplex ? "full" : "half",
			 np->phys[0]);
	वापस result;
पूर्ण

#घोषणा RXTX_TIMEOUT	2000
अटल अंतरभूत व्योम update_csr6(काष्ठा net_device *dev, पूर्णांक new)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;
	पूर्णांक limit = RXTX_TIMEOUT;

	अगर (!netअगर_device_present(dev))
		new = 0;
	अगर (new==np->csr6)
		वापस;
	/* stop both Tx and Rx processes */
	ioग_लिखो32(np->csr6 & ~0x2002, ioaddr + NetworkConfig);
	/* रुको until they have really stopped */
	क्रम (;;) अणु
		पूर्णांक csr5 = ioपढ़ो32(ioaddr + IntrStatus);
		पूर्णांक t;

		t = (csr5 >> 17) & 0x07;
		अगर (t==0||t==1) अणु
			/* rx stopped */
			t = (csr5 >> 20) & 0x07;
			अगर (t==0||t==1)
				अवरोध;
		पूर्ण

		limit--;
		अगर(!limit) अणु
			dev_info(&dev->dev,
				 "couldn't stop rxtx, IntrStatus %xh\n", csr5);
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
	np->csr6 = new;
	/* and restart them with the new configuration */
	ioग_लिखो32(np->csr6, ioaddr + NetworkConfig);
	अगर (new & 0x200)
		np->mii_अगर.full_duplex = 1;
पूर्ण

अटल व्योम netdev_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा netdev_निजी *np = from_समयr(np, t, समयr);
	काष्ठा net_device *dev = pci_get_drvdata(np->pci_dev);
	व्योम __iomem *ioaddr = np->base_addr;

	अगर (debug > 2)
		netdev_dbg(dev, "Media selection timer tick, status %08x config %08x\n",
			   ioपढ़ो32(ioaddr + IntrStatus),
			   ioपढ़ो32(ioaddr + NetworkConfig));
	spin_lock_irq(&np->lock);
	update_csr6(dev, update_link(dev));
	spin_unlock_irq(&np->lock);
	np->समयr.expires = jअगरfies + 10*HZ;
	add_समयr(&np->समयr);
पूर्ण

अटल व्योम init_rxtx_rings(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	np->rx_head_desc = &np->rx_ring[0];
	np->tx_ring = (काष्ठा w840_tx_desc*)&np->rx_ring[RX_RING_SIZE];

	/* Initial all Rx descriptors. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		np->rx_ring[i].length = np->rx_buf_sz;
		np->rx_ring[i].status = 0;
		np->rx_skbuff[i] = शून्य;
	पूर्ण
	/* Mark the last entry as wrapping the ring. */
	np->rx_ring[i-1].length |= DescEndRing;

	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, np->rx_buf_sz);
		np->rx_skbuff[i] = skb;
		अगर (skb == शून्य)
			अवरोध;
		np->rx_addr[i] = dma_map_single(&np->pci_dev->dev, skb->data,
						np->rx_buf_sz,
						DMA_FROM_DEVICE);

		np->rx_ring[i].buffer1 = np->rx_addr[i];
		np->rx_ring[i].status = DescOwned;
	पूर्ण

	np->cur_rx = 0;
	np->dirty_rx = (अचिन्हित पूर्णांक)(i - RX_RING_SIZE);

	/* Initialize the Tx descriptors */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		np->tx_skbuff[i] = शून्य;
		np->tx_ring[i].status = 0;
	पूर्ण
	np->tx_full = 0;
	np->tx_q_bytes = np->dirty_tx = np->cur_tx = 0;

	ioग_लिखो32(np->ring_dma_addr, np->base_addr + RxRingPtr);
	ioग_लिखो32(np->ring_dma_addr+माप(काष्ठा w840_rx_desc)*RX_RING_SIZE,
		np->base_addr + TxRingPtr);

पूर्ण

अटल व्योम मुक्त_rxtx_rings(काष्ठा netdev_निजी* np)
अणु
	पूर्णांक i;
	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		np->rx_ring[i].status = 0;
		अगर (np->rx_skbuff[i]) अणु
			dma_unmap_single(&np->pci_dev->dev, np->rx_addr[i],
					 np->rx_skbuff[i]->len,
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(np->rx_skbuff[i]);
		पूर्ण
		np->rx_skbuff[i] = शून्य;
	पूर्ण
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		अगर (np->tx_skbuff[i]) अणु
			dma_unmap_single(&np->pci_dev->dev, np->tx_addr[i],
					 np->tx_skbuff[i]->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb(np->tx_skbuff[i]);
		पूर्ण
		np->tx_skbuff[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम init_रेजिस्टरs(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		ioग_लिखो8(dev->dev_addr[i], ioaddr + StationAddr + i);

	/* Initialize other रेजिस्टरs. */
#अगर_घोषित __BIG_ENDIAN
	i = (1<<20);	/* Big-endian descriptors */
#अन्यथा
	i = 0;
#पूर्ण_अगर
	i |= (0x04<<2);		/* skip length 4 u32 */
	i |= 0x02;		/* give Rx priority */

	/* Configure the PCI bus bursts and FIFO thresholds.
	   486: Set 8 दीर्घword cache alignment, 8 दीर्घword burst.
	   586: Set 16 दीर्घword cache alignment, no burst limit.
	   Cache alignment bits 15:14	     Burst length 13:8
		0000	<not allowed> 		0000 align to cache	0800 8 दीर्घwords
		4000	8  दीर्घwords		0100 1 दीर्घword		1000 16 दीर्घwords
		8000	16 दीर्घwords		0200 2 दीर्घwords	2000 32 दीर्घwords
		C000	32  दीर्घwords		0400 4 दीर्घwords */

#अगर defined (__i386__) && !defined(MODULE)
	/* When not a module we can work around broken '486 PCI boards. */
	अगर (boot_cpu_data.x86 <= 4) अणु
		i |= 0x4800;
		dev_info(&dev->dev,
			 "This is a 386/486 PCI system, setting cache alignment to 8 longwords\n");
	पूर्ण अन्यथा अणु
		i |= 0xE000;
	पूर्ण
#या_अगर defined(__घातerpc__) || defined(__i386__) || defined(__alpha__) || defined(__ia64__) || defined(__x86_64__)
	i |= 0xE000;
#या_अगर defined(CONFIG_SPARC) || defined (CONFIG_PARISC) || defined(CONFIG_ARM)
	i |= 0x4800;
#अन्यथा
	dev_warn(&dev->dev, "unknown CPU architecture, using default csr0 setting\n");
	i |= 0x4800;
#पूर्ण_अगर
	ioग_लिखो32(i, ioaddr + PCIBusCfg);

	np->csr6 = 0;
	/* 128 byte Tx threshold;
		Transmit on; Receive on; */
	update_csr6(dev, 0x00022002 | update_link(dev) | __set_rx_mode(dev));

	/* Clear and Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ioग_लिखो32(0x1A0F5, ioaddr + IntrStatus);
	ioग_लिखो32(0x1A0F5, ioaddr + IntrEnable);

	ioग_लिखो32(0, ioaddr + RxStartDemand);
पूर्ण

अटल व्योम tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;
	स्थिर पूर्णांक irq = np->pci_dev->irq;

	dev_warn(&dev->dev, "Transmit timed out, status %08x, resetting...\n",
		 ioपढ़ो32(ioaddr + IntrStatus));

	अणु
		पूर्णांक i;
		prपूर्णांकk(KERN_DEBUG "  Rx ring %p: ", np->rx_ring);
		क्रम (i = 0; i < RX_RING_SIZE; i++)
			prपूर्णांकk(KERN_CONT " %08x", (अचिन्हित पूर्णांक)np->rx_ring[i].status);
		prपूर्णांकk(KERN_CONT "\n");
		prपूर्णांकk(KERN_DEBUG "  Tx ring %p: ", np->tx_ring);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			prपूर्णांकk(KERN_CONT " %08x", np->tx_ring[i].status);
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "Tx cur %d Tx dirty %d Tx Full %d, q bytes %d\n",
	       np->cur_tx, np->dirty_tx, np->tx_full, np->tx_q_bytes);
	prपूर्णांकk(KERN_DEBUG "Tx Descriptor addr %xh\n", ioपढ़ो32(ioaddr+0x4C));

	disable_irq(irq);
	spin_lock_irq(&np->lock);
	/*
	 * Under high load dirty_tx and the पूर्णांकernal tx descriptor poपूर्णांकer
	 * come out of sync, thus perक्रमm a software reset and reinitialize
	 * everything.
	 */

	ioग_लिखो32(1, np->base_addr+PCIBusCfg);
	udelay(1);

	मुक्त_rxtx_rings(np);
	init_rxtx_rings(dev);
	init_रेजिस्टरs(dev);
	spin_unlock_irq(&np->lock);
	enable_irq(irq);

	netअगर_wake_queue(dev);
	netअगर_trans_update(dev); /* prevent tx समयout */
	np->stats.tx_errors++;
पूर्ण

/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल पूर्णांक alloc_ringdesc(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	np->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	np->rx_ring = dma_alloc_coherent(&np->pci_dev->dev,
					 माप(काष्ठा w840_rx_desc) * RX_RING_SIZE +
					 माप(काष्ठा w840_tx_desc) * TX_RING_SIZE,
					 &np->ring_dma_addr, GFP_KERNEL);
	अगर(!np->rx_ring)
		वापस -ENOMEM;
	init_rxtx_rings(dev);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_ringdesc(काष्ठा netdev_निजी *np)
अणु
	dma_मुक्त_coherent(&np->pci_dev->dev,
			  माप(काष्ठा w840_rx_desc) * RX_RING_SIZE +
			  माप(काष्ठा w840_tx_desc) * TX_RING_SIZE,
			  np->rx_ring, np->ring_dma_addr);

पूर्ण

अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	अचिन्हित entry;

	/* Caution: the ग_लिखो order is important here, set the field
	   with the "ownership" bits last. */

	/* Calculate the next Tx descriptor entry. */
	entry = np->cur_tx % TX_RING_SIZE;

	np->tx_addr[entry] = dma_map_single(&np->pci_dev->dev, skb->data,
					    skb->len, DMA_TO_DEVICE);
	np->tx_skbuff[entry] = skb;

	np->tx_ring[entry].buffer1 = np->tx_addr[entry];
	अगर (skb->len < TX_BUFLIMIT) अणु
		np->tx_ring[entry].length = DescWholePkt | skb->len;
	पूर्ण अन्यथा अणु
		पूर्णांक len = skb->len - TX_BUFLIMIT;

		np->tx_ring[entry].buffer2 = np->tx_addr[entry]+TX_BUFLIMIT;
		np->tx_ring[entry].length = DescWholePkt | (len << 11) | TX_BUFLIMIT;
	पूर्ण
	अगर(entry == TX_RING_SIZE-1)
		np->tx_ring[entry].length |= DescEndRing;

	/* Now acquire the irq spinlock.
	 * The dअगरficult race is the ordering between
	 * increasing np->cur_tx and setting DescOwned:
	 * - अगर np->cur_tx is increased first the पूर्णांकerrupt
	 *   handler could consider the packet as transmitted
	 *   since DescOwned is cleared.
	 * - If DescOwned is set first the NIC could report the
	 *   packet as sent, but the पूर्णांकerrupt handler would ignore it
	 *   since the np->cur_tx was not yet increased.
	 */
	spin_lock_irq(&np->lock);
	np->cur_tx++;

	wmb(); /* flush length, buffer1, buffer2 */
	np->tx_ring[entry].status = DescOwned;
	wmb(); /* flush status and kick the hardware */
	ioग_लिखो32(0, np->base_addr + TxStartDemand);
	np->tx_q_bytes += skb->len;
	/* Work around horrible bug in the chip by marking the queue as full
	   when we करो not have FIFO room क्रम a maximum sized packet. */
	अगर (np->cur_tx - np->dirty_tx > TX_QUEUE_LEN ||
		((np->drv_flags & HasBrokenTx) && np->tx_q_bytes > TX_BUG_FIFO_LIMIT)) अणु
		netअगर_stop_queue(dev);
		wmb();
		np->tx_full = 1;
	पूर्ण
	spin_unlock_irq(&np->lock);

	अगर (debug > 4) अणु
		netdev_dbg(dev, "Transmit frame #%d queued in slot %d\n",
			   np->cur_tx, entry);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम netdev_tx_करोne(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	क्रम (; np->cur_tx - np->dirty_tx > 0; np->dirty_tx++) अणु
		पूर्णांक entry = np->dirty_tx % TX_RING_SIZE;
		पूर्णांक tx_status = np->tx_ring[entry].status;

		अगर (tx_status < 0)
			अवरोध;
		अगर (tx_status & 0x8000) अणु 	/* There was an error, log it. */
#अगर_अघोषित final_version
			अगर (debug > 1)
				netdev_dbg(dev, "Transmit error, Tx status %08x\n",
					   tx_status);
#पूर्ण_अगर
			np->stats.tx_errors++;
			अगर (tx_status & 0x0104) np->stats.tx_पातed_errors++;
			अगर (tx_status & 0x0C80) np->stats.tx_carrier_errors++;
			अगर (tx_status & 0x0200) np->stats.tx_winकरोw_errors++;
			अगर (tx_status & 0x0002) np->stats.tx_fअगरo_errors++;
			अगर ((tx_status & 0x0080) && np->mii_अगर.full_duplex == 0)
				np->stats.tx_heartbeat_errors++;
		पूर्ण अन्यथा अणु
#अगर_अघोषित final_version
			अगर (debug > 3)
				netdev_dbg(dev, "Transmit slot %d ok, Tx status %08x\n",
					   entry, tx_status);
#पूर्ण_अगर
			np->stats.tx_bytes += np->tx_skbuff[entry]->len;
			np->stats.collisions += (tx_status >> 3) & 15;
			np->stats.tx_packets++;
		पूर्ण
		/* Free the original skb. */
		dma_unmap_single(&np->pci_dev->dev, np->tx_addr[entry],
				 np->tx_skbuff[entry]->len, DMA_TO_DEVICE);
		np->tx_q_bytes -= np->tx_skbuff[entry]->len;
		dev_kमुक्त_skb_irq(np->tx_skbuff[entry]);
		np->tx_skbuff[entry] = शून्य;
	पूर्ण
	अगर (np->tx_full &&
		np->cur_tx - np->dirty_tx < TX_QUEUE_LEN_RESTART &&
		np->tx_q_bytes < TX_BUG_FIFO_LIMIT) अणु
		/* The ring is no दीर्घer full, clear tbusy. */
		np->tx_full = 0;
		wmb();
		netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_instance;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;
	पूर्णांक work_limit = max_पूर्णांकerrupt_work;
	पूर्णांक handled = 0;

	अगर (!netअगर_device_present(dev))
		वापस IRQ_NONE;
	करो अणु
		u32 पूर्णांकr_status = ioपढ़ो32(ioaddr + IntrStatus);

		/* Acknowledge all of the current पूर्णांकerrupt sources ASAP. */
		ioग_लिखो32(पूर्णांकr_status & 0x001ffff, ioaddr + IntrStatus);

		अगर (debug > 4)
			netdev_dbg(dev, "Interrupt, status %04x\n", पूर्णांकr_status);

		अगर ((पूर्णांकr_status & (NormalIntr|AbnormalIntr)) == 0)
			अवरोध;

		handled = 1;

		अगर (पूर्णांकr_status & (RxIntr | RxNoBuf))
			netdev_rx(dev);
		अगर (पूर्णांकr_status & RxNoBuf)
			ioग_लिखो32(0, ioaddr + RxStartDemand);

		अगर (पूर्णांकr_status & (TxNoBuf | TxIntr) &&
			np->cur_tx != np->dirty_tx) अणु
			spin_lock(&np->lock);
			netdev_tx_करोne(dev);
			spin_unlock(&np->lock);
		पूर्ण

		/* Abnormal error summary/uncommon events handlers. */
		अगर (पूर्णांकr_status & (AbnormalIntr | TxFIFOUnderflow | SystemError |
						   TimerInt | TxDied))
			netdev_error(dev, पूर्णांकr_status);

		अगर (--work_limit < 0) अणु
			dev_warn(&dev->dev,
				 "Too much work at interrupt, status=0x%04x\n",
				 पूर्णांकr_status);
			/* Set the समयr to re-enable the other पूर्णांकerrupts after
			   10*82usec ticks. */
			spin_lock(&np->lock);
			अगर (netअगर_device_present(dev)) अणु
				ioग_लिखो32(AbnormalIntr | TimerInt, ioaddr + IntrEnable);
				ioग_लिखो32(10, ioaddr + GPTimer);
			पूर्ण
			spin_unlock(&np->lock);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	अगर (debug > 3)
		netdev_dbg(dev, "exiting interrupt, status=%#4.4x\n",
			   ioपढ़ो32(ioaddr + IntrStatus));
	वापस IRQ_RETVAL(handled);
पूर्ण

/* This routine is logically part of the पूर्णांकerrupt handler, but separated
   क्रम clarity and better रेजिस्टर allocation. */
अटल पूर्णांक netdev_rx(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक entry = np->cur_rx % RX_RING_SIZE;
	पूर्णांक work_limit = np->dirty_rx + RX_RING_SIZE - np->cur_rx;

	अगर (debug > 4) अणु
		netdev_dbg(dev, " In netdev_rx(), entry %d status %04x\n",
			   entry, np->rx_ring[entry].status);
	पूर्ण

	/* If EOP is set on the next entry, it's a new packet. Send it up. */
	जबतक (--work_limit >= 0) अणु
		काष्ठा w840_rx_desc *desc = np->rx_head_desc;
		s32 status = desc->status;

		अगर (debug > 4)
			netdev_dbg(dev, "  netdev_rx() status was %08x\n",
				   status);
		अगर (status < 0)
			अवरोध;
		अगर ((status & 0x38008300) != 0x0300) अणु
			अगर ((status & 0x38000300) != 0x0300) अणु
				/* Ingore earlier buffers. */
				अगर ((status & 0xffff) != 0x7fff) अणु
					dev_warn(&dev->dev,
						 "Oversized Ethernet frame spanned multiple buffers, entry %#x status %04x!\n",
						 np->cur_rx, status);
					np->stats.rx_length_errors++;
				पूर्ण
			पूर्ण अन्यथा अगर (status & 0x8000) अणु
				/* There was a fatal error. */
				अगर (debug > 2)
					netdev_dbg(dev, "Receive error, Rx status %08x\n",
						   status);
				np->stats.rx_errors++; /* end of a packet.*/
				अगर (status & 0x0890) np->stats.rx_length_errors++;
				अगर (status & 0x004C) np->stats.rx_frame_errors++;
				अगर (status & 0x0002) np->stats.rx_crc_errors++;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb;
			/* Omit the four octet CRC from the length. */
			पूर्णांक pkt_len = ((status >> 16) & 0x7ff) - 4;

#अगर_अघोषित final_version
			अगर (debug > 4)
				netdev_dbg(dev, "  netdev_rx() normal Rx pkt length %d status %x\n",
					   pkt_len, status);
#पूर्ण_अगर
			/* Check अगर the packet is दीर्घ enough to accept without copying
			   to a minimally-sized skbuff. */
			अगर (pkt_len < rx_copyअवरोध &&
			    (skb = netdev_alloc_skb(dev, pkt_len + 2)) != शून्य) अणु
				skb_reserve(skb, 2);	/* 16 byte align the IP header */
				dma_sync_single_क्रम_cpu(&np->pci_dev->dev,
							np->rx_addr[entry],
							np->rx_skbuff[entry]->len,
							DMA_FROM_DEVICE);
				skb_copy_to_linear_data(skb, np->rx_skbuff[entry]->data, pkt_len);
				skb_put(skb, pkt_len);
				dma_sync_single_क्रम_device(&np->pci_dev->dev,
							   np->rx_addr[entry],
							   np->rx_skbuff[entry]->len,
							   DMA_FROM_DEVICE);
			पूर्ण अन्यथा अणु
				dma_unmap_single(&np->pci_dev->dev,
						 np->rx_addr[entry],
						 np->rx_skbuff[entry]->len,
						 DMA_FROM_DEVICE);
				skb_put(skb = np->rx_skbuff[entry], pkt_len);
				np->rx_skbuff[entry] = शून्य;
			पूर्ण
#अगर_अघोषित final_version				/* Remove after testing. */
			/* You will want this info क्रम the initial debug. */
			अगर (debug > 5)
				netdev_dbg(dev, "  Rx data %pM %pM %02x%02x %pI4\n",
					   &skb->data[0], &skb->data[6],
					   skb->data[12], skb->data[13],
					   &skb->data[14]);
#पूर्ण_अगर
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			np->stats.rx_packets++;
			np->stats.rx_bytes += pkt_len;
		पूर्ण
		entry = (++np->cur_rx) % RX_RING_SIZE;
		np->rx_head_desc = &np->rx_ring[entry];
	पूर्ण

	/* Refill the Rx ring buffers. */
	क्रम (; np->cur_rx - np->dirty_rx > 0; np->dirty_rx++) अणु
		काष्ठा sk_buff *skb;
		entry = np->dirty_rx % RX_RING_SIZE;
		अगर (np->rx_skbuff[entry] == शून्य) अणु
			skb = netdev_alloc_skb(dev, np->rx_buf_sz);
			np->rx_skbuff[entry] = skb;
			अगर (skb == शून्य)
				अवरोध;			/* Better luck next round. */
			np->rx_addr[entry] = dma_map_single(&np->pci_dev->dev,
							    skb->data,
							    np->rx_buf_sz,
							    DMA_FROM_DEVICE);
			np->rx_ring[entry].buffer1 = np->rx_addr[entry];
		पूर्ण
		wmb();
		np->rx_ring[entry].status = DescOwned;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम netdev_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;

	अगर (debug > 2)
		netdev_dbg(dev, "Abnormal event, %08x\n", पूर्णांकr_status);
	अगर (पूर्णांकr_status == 0xffffffff)
		वापस;
	spin_lock(&np->lock);
	अगर (पूर्णांकr_status & TxFIFOUnderflow) अणु
		पूर्णांक new;
		/* Bump up the Tx threshold */
#अगर 0
		/* This causes lots of dropped packets,
		 * and under high load even tx_समयouts
		 */
		new = np->csr6 + 0x4000;
#अन्यथा
		new = (np->csr6 >> 14)&0x7f;
		अगर (new < 64)
			new *= 2;
		 अन्यथा
		 	new = 127; /* load full packet beक्रमe starting */
		new = (np->csr6 & ~(0x7F << 14)) | (new<<14);
#पूर्ण_अगर
		netdev_dbg(dev, "Tx underflow, new csr6 %08x\n", new);
		update_csr6(dev, new);
	पूर्ण
	अगर (पूर्णांकr_status & RxDied) अणु		/* Missed a Rx frame. */
		np->stats.rx_errors++;
	पूर्ण
	अगर (पूर्णांकr_status & TimerInt) अणु
		/* Re-enable other पूर्णांकerrupts. */
		अगर (netअगर_device_present(dev))
			ioग_लिखो32(0x1A0F5, ioaddr + IntrEnable);
	पूर्ण
	np->stats.rx_missed_errors += ioपढ़ो32(ioaddr + RxMissed) & 0xffff;
	ioग_लिखो32(0, ioaddr + RxStartDemand);
	spin_unlock(&np->lock);
पूर्ण

अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;

	/* The chip only need report frame silently dropped. */
	spin_lock_irq(&np->lock);
	अगर (netअगर_running(dev) && netअगर_device_present(dev))
		np->stats.rx_missed_errors += ioपढ़ो32(ioaddr + RxMissed) & 0xffff;
	spin_unlock_irq(&np->lock);

	वापस &np->stats;
पूर्ण


अटल u32 __set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;
	u32 mc_filter[2];			/* Multicast hash filter */
	u32 rx_mode;

	अगर (dev->flags & IFF_PROMISC) अणु			/* Set promiscuous. */
		स_रखो(mc_filter, 0xff, माप(mc_filter));
		rx_mode = RxAcceptBroadcast | AcceptMulticast | RxAcceptAllPhys
			| AcceptMyPhys;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to match, or accept all multicasts. */
		स_रखो(mc_filter, 0xff, माप(mc_filter));
		rx_mode = RxAcceptBroadcast | AcceptMulticast | AcceptMyPhys;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;

		स_रखो(mc_filter, 0, माप(mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			पूर्णांक filbit;

			filbit = (ether_crc(ETH_ALEN, ha->addr) >> 26) ^ 0x3F;
			filbit &= 0x3f;
			mc_filter[filbit >> 5] |= 1 << (filbit & 31);
		पूर्ण
		rx_mode = RxAcceptBroadcast | AcceptMulticast | AcceptMyPhys;
	पूर्ण
	ioग_लिखो32(mc_filter[0], ioaddr + MulticastFilter0);
	ioग_लिखो32(mc_filter[1], ioaddr + MulticastFilter1);
	वापस rx_mode;
पूर्ण

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u32 rx_mode = __set_rx_mode(dev);
	spin_lock_irq(&np->lock);
	update_csr6(dev, (np->csr6 & ~0x00F8) | rx_mode);
	spin_unlock_irq(&np->lock);
पूर्ण

अटल व्योम netdev_get_drvinfo (काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(np->pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक netdev_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	spin_lock_irq(&np->lock);
	mii_ethtool_get_link_ksettings(&np->mii_अगर, cmd);
	spin_unlock_irq(&np->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक rc;

	spin_lock_irq(&np->lock);
	rc = mii_ethtool_set_link_ksettings(&np->mii_अगर, cmd);
	spin_unlock_irq(&np->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक netdev_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस mii_nway_restart(&np->mii_अगर);
पूर्ण

अटल u32 netdev_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस mii_link_ok(&np->mii_अगर);
पूर्ण

अटल u32 netdev_get_msglevel(काष्ठा net_device *dev)
अणु
	वापस debug;
पूर्ण

अटल व्योम netdev_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	debug = value;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
	.nway_reset		= netdev_nway_reset,
	.get_link		= netdev_get_link,
	.get_msglevel		= netdev_get_msglevel,
	.set_msglevel		= netdev_set_msglevel,
	.get_link_ksettings	= netdev_get_link_ksettings,
	.set_link_ksettings	= netdev_set_link_ksettings,
पूर्ण;

अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	चयन(cmd) अणु
	हाल SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = ((काष्ठा netdev_निजी *)netdev_priv(dev))->phys[0] & 0x1f;
		fallthrough;

	हाल SIOCGMIIREG:		/* Read MII PHY रेजिस्टर. */
		spin_lock_irq(&np->lock);
		data->val_out = mdio_पढ़ो(dev, data->phy_id & 0x1f, data->reg_num & 0x1f);
		spin_unlock_irq(&np->lock);
		वापस 0;

	हाल SIOCSMIIREG:		/* Write MII PHY रेजिस्टर. */
		spin_lock_irq(&np->lock);
		mdio_ग_लिखो(dev, data->phy_id & 0x1f, data->reg_num & 0x1f, data->val_in);
		spin_unlock_irq(&np->lock);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक netdev_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;

	netअगर_stop_queue(dev);

	अगर (debug > 1) अणु
		netdev_dbg(dev, "Shutting down ethercard, status was %08x Config %08x\n",
			   ioपढ़ो32(ioaddr + IntrStatus),
			   ioपढ़ो32(ioaddr + NetworkConfig));
		netdev_dbg(dev, "Queue pointers were Tx %d / %d,  Rx %d / %d\n",
			   np->cur_tx, np->dirty_tx,
			   np->cur_rx, np->dirty_rx);
	पूर्ण

 	/* Stop the chip's Tx and Rx processes. */
	spin_lock_irq(&np->lock);
	netअगर_device_detach(dev);
	update_csr6(dev, 0);
	ioग_लिखो32(0x0000, ioaddr + IntrEnable);
	spin_unlock_irq(&np->lock);

	मुक्त_irq(np->pci_dev->irq, dev);
	wmb();
	netअगर_device_attach(dev);

	अगर (ioपढ़ो32(ioaddr + NetworkConfig) != 0xffffffff)
		np->stats.rx_missed_errors += ioपढ़ो32(ioaddr + RxMissed) & 0xffff;

#अगर_घोषित __i386__
	अगर (debug > 2) अणु
		पूर्णांक i;

		prपूर्णांकk(KERN_DEBUG"  Tx ring at %p:\n", np->tx_ring);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			prपूर्णांकk(KERN_DEBUG " #%d desc. %04x %04x %08x\n",
			       i, np->tx_ring[i].length,
			       np->tx_ring[i].status, np->tx_ring[i].buffer1);
		prपूर्णांकk(KERN_DEBUG "  Rx ring %p:\n", np->rx_ring);
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			prपूर्णांकk(KERN_DEBUG " #%d desc. %04x %04x %08x\n",
			       i, np->rx_ring[i].length,
			       np->rx_ring[i].status, np->rx_ring[i].buffer1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* __i386__ debugging only */

	del_समयr_sync(&np->समयr);

	मुक्त_rxtx_rings(np);
	मुक्त_ringdesc(np);

	वापस 0;
पूर्ण

अटल व्योम w840_हटाओ1(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		काष्ठा netdev_निजी *np = netdev_priv(dev);
		unरेजिस्टर_netdev(dev);
		pci_release_regions(pdev);
		pci_iounmap(pdev, np->base_addr);
		मुक्त_netdev(dev);
	पूर्ण
पूर्ण

/*
 * suspend/resume synchronization:
 * - खोलो, बंद, करो_ioctl:
 * 	rtnl_lock, & netअगर_device_detach after the rtnl_unlock.
 * - get_stats:
 * 	spin_lock_irq(np->lock), करोesn't touch hw अगर not present
 * - start_xmit:
 * 	synchronize_irq + netअगर_tx_disable;
 * - tx_समयout:
 * 	netअगर_device_detach + netअगर_tx_disable;
 * - set_multicast_list
 * 	netअगर_device_detach + netअगर_tx_disable;
 * - पूर्णांकerrupt handler
 * 	करोesn't touch hw अगर not present, synchronize_irq रुकोs क्रम
 * 	running instances of the पूर्णांकerrupt handler.
 *
 * Disabling hw requires clearing csr6 & IntrEnable.
 * update_csr6 & all function that ग_लिखो IntrEnable check netअगर_device_present
 * beक्रमe settings any bits.
 *
 * Detach must occur under spin_unlock_irq(), पूर्णांकerrupts from a detached
 * device would cause an irq storm.
 */
अटल पूर्णांक __maybe_unused w840_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->base_addr;

	rtnl_lock();
	अगर (netअगर_running (dev)) अणु
		del_समयr_sync(&np->समयr);

		spin_lock_irq(&np->lock);
		netअगर_device_detach(dev);
		update_csr6(dev, 0);
		ioग_लिखो32(0, ioaddr + IntrEnable);
		spin_unlock_irq(&np->lock);

		synchronize_irq(np->pci_dev->irq);
		netअगर_tx_disable(dev);

		np->stats.rx_missed_errors += ioपढ़ो32(ioaddr + RxMissed) & 0xffff;

		/* no more hardware accesses behind this line. */

		BUG_ON(np->csr6 || ioपढ़ो32(ioaddr + IntrEnable));

		/* pci_घातer_off(pdev, -1); */

		मुक्त_rxtx_rings(np);
	पूर्ण अन्यथा अणु
		netअगर_device_detach(dev);
	पूर्ण
	rtnl_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused w840_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	rtnl_lock();
	अगर (netअगर_device_present(dev))
		जाओ out; /* device not suspended */
	अगर (netअगर_running(dev)) अणु
		spin_lock_irq(&np->lock);
		ioग_लिखो32(1, np->base_addr+PCIBusCfg);
		ioपढ़ो32(np->base_addr+PCIBusCfg);
		udelay(1);
		netअगर_device_attach(dev);
		init_rxtx_rings(dev);
		init_रेजिस्टरs(dev);
		spin_unlock_irq(&np->lock);

		netअगर_wake_queue(dev);

		mod_समयr(&np->समयr, jअगरfies + 1*HZ);
	पूर्ण अन्यथा अणु
		netअगर_device_attach(dev);
	पूर्ण
out:
	rtnl_unlock();
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(w840_pm_ops, w840_suspend, w840_resume);

अटल काष्ठा pci_driver w840_driver = अणु
	.name		= DRV_NAME,
	.id_table	= w840_pci_tbl,
	.probe		= w840_probe1,
	.हटाओ		= w840_हटाओ1,
	.driver.pm	= &w840_pm_ops,
पूर्ण;

module_pci_driver(w840_driver);
