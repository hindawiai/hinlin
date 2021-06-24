<शैली गुरु>
/* sis900.c: A SiS 900/7016 PCI Fast Ethernet driver क्रम Linux.
   Copyright 1999 Silicon Integrated System Corporation
   Revision:	1.08.10 Apr. 2 2006

   Modअगरied from the driver which is originally written by Donald Becker.

   This software may be used and distributed according to the terms
   of the GNU General Public License (GPL), incorporated herein by reference.
   Drivers based on this skeleton fall under the GPL and must retain
   the authorship (implicit copyright) notice.

   References:
   SiS 7016 Fast Ethernet PCI Bus 10/100 Mbps LAN Controller with OnNow Support,
   preliminary Rev. 1.0 Jan. 14, 1998
   SiS 900 Fast Ethernet PCI Bus 10/100 Mbps LAN Single Chip with OnNow Support,
   preliminary Rev. 1.0 Nov. 10, 1998
   SiS 7014 Single Chip 100BASE-TX/10BASE-T Physical Layer Solution,
   preliminary Rev. 1.0 Jan. 18, 1998

   Rev 1.08.10 Apr.  2 2006 Daniele Venzano add vlan (jumbo packets) support
   Rev 1.08.09 Sep. 19 2005 Daniele Venzano add Wake on LAN support
   Rev 1.08.08 Jan. 22 2005 Daniele Venzano use netअगर_msg क्रम debugging messages
   Rev 1.08.07 Nov.  2 2003 Daniele Venzano <venza@brownhat.org> add suspend/resume support
   Rev 1.08.06 Sep. 24 2002 Mufasa Yang bug fix क्रम Tx समयout & add SiS963 support
   Rev 1.08.05 Jun.  6 2002 Mufasa Yang bug fix क्रम पढ़ो_eeprom & Tx descriptor over-boundary
   Rev 1.08.04 Apr. 25 2002 Mufasa Yang <mufasa@sis.com.tw> added SiS962 support
   Rev 1.08.03 Feb.  1 2002 Matt Domsch <Matt_Domsch@dell.com> update to use library crc32 function
   Rev 1.08.02 Nov. 30 2001 Hui-Fen Hsu workaround क्रम EDB & bug fix क्रम dhcp problem
   Rev 1.08.01 Aug. 25 2001 Hui-Fen Hsu update क्रम 630ET & workaround क्रम ICS1893 PHY
   Rev 1.08.00 Jun. 11 2001 Hui-Fen Hsu workaround क्रम RTL8201 PHY and some bug fix
   Rev 1.07.11 Apr.  2 2001 Hui-Fen Hsu updates PCI drivers to use the new pci_set_dma_mask क्रम kernel 2.4.3
   Rev 1.07.10 Mar.  1 2001 Hui-Fen Hsu <hfhsu@sis.com.tw> some bug fix & 635M/B support
   Rev 1.07.09 Feb.  9 2001 Dave Jones <davej@suse.de> PCI enable cleanup
   Rev 1.07.08 Jan.  8 2001 Lei-Chun Chang added RTL8201 PHY support
   Rev 1.07.07 Nov. 29 2000 Lei-Chun Chang added kernel-करोc extractable करोcumentation and 630 workaround fix
   Rev 1.07.06 Nov.  7 2000 Jeff Garzik <jgarzik@pobox.com> some bug fix and cleaning
   Rev 1.07.05 Nov.  6 2000 metapirat<metapirat@gmx.de> contribute media type select by अगरconfig
   Rev 1.07.04 Sep.  6 2000 Lei-Chun Chang added ICS1893 PHY support
   Rev 1.07.03 Aug. 24 2000 Lei-Chun Chang (lcchang@sis.com.tw) modअगरied 630E equalizer workaround rule
   Rev 1.07.01 Aug. 08 2000 Ollie Lho minor update क्रम SiS 630E and SiS 630E A1
   Rev 1.07    Mar. 07 2000 Ollie Lho bug fix in Rx buffer ring
   Rev 1.06.04 Feb. 11 2000 Jeff Garzik <jgarzik@pobox.com> softnet and init क्रम kernel 2.4
   Rev 1.06.03 Dec. 23 1999 Ollie Lho Third release
   Rev 1.06.02 Nov. 23 1999 Ollie Lho bug in mac probing fixed
   Rev 1.06.01 Nov. 16 1999 Ollie Lho CRC calculation provide by Joseph Zbiciak (im14u2c@primenet.com)
   Rev 1.06 Nov. 4 1999 Ollie Lho (ollie@sis.com.tw) Second release
   Rev 1.05.05 Oct. 29 1999 Ollie Lho (ollie@sis.com.tw) Single buffer Tx/Rx
   Chin-Shan Li (lcs@sis.com.tw) Added AMD Am79c901 HomePNA PHY support
   Rev 1.05 Aug. 7 1999 Jim Huang (cmhuang@sis.com.tw) Initial release
*/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/mii.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/processor.h>      /* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>	/* User space memory access functions */

#समावेश "sis900.h"

#घोषणा SIS900_MODULE_NAME "sis900"
#घोषणा SIS900_DRV_VERSION "v1.08.10 Apr. 2 2006"

अटल स्थिर अक्षर version[] =
	KERN_INFO "sis900.c: " SIS900_DRV_VERSION "\n";

अटल पूर्णांक max_पूर्णांकerrupt_work = 40;
अटल पूर्णांक multicast_filter_limit = 128;

अटल पूर्णांक sis900_debug = -1; /* Use SIS900_DEF_MSG as value */

#घोषणा SIS900_DEF_MSG \
	(NETIF_MSG_DRV		| \
	 NETIF_MSG_LINK		| \
	 NETIF_MSG_RX_ERR	| \
	 NETIF_MSG_TX_ERR)

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (4*HZ)

क्रमागत अणु
	SIS_900 = 0,
	SIS_7016
पूर्ण;
अटल स्थिर अक्षर * card_names[] = अणु
	"SiS 900 PCI Fast Ethernet",
	"SiS 7016 PCI Fast Ethernet"
पूर्ण;

अटल स्थिर काष्ठा pci_device_id sis900_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_900,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, SIS_900पूर्ण,
	अणुPCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_7016,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, SIS_7016पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (pci, sis900_pci_tbl);

अटल व्योम sis900_पढ़ो_mode(काष्ठा net_device *net_dev, पूर्णांक *speed, पूर्णांक *duplex);

अटल स्थिर काष्ठा mii_chip_info अणु
	स्थिर अक्षर * name;
	u16 phy_id0;
	u16 phy_id1;
	u8  phy_types;
#घोषणा	HOME 	0x0001
#घोषणा LAN	0x0002
#घोषणा MIX	0x0003
#घोषणा UNKNOWN	0x0
पूर्ण mii_chip_table[] = अणु
	अणु "SiS 900 Internal MII PHY", 		0x001d, 0x8000, LAN पूर्ण,
	अणु "SiS 7014 Physical Layer Solution", 	0x0016, 0xf830, LAN पूर्ण,
	अणु "SiS 900 on Foxconn 661 7MI",         0x0143, 0xBC70, LAN पूर्ण,
	अणु "Altimata AC101LF PHY",               0x0022, 0x5520, LAN पूर्ण,
	अणु "ADM 7001 LAN PHY",			0x002e, 0xcc60, LAN पूर्ण,
	अणु "AMD 79C901 10BASE-T PHY",  		0x0000, 0x6B70, LAN पूर्ण,
	अणु "AMD 79C901 HomePNA PHY",		0x0000, 0x6B90, HOMEपूर्ण,
	अणु "ICS LAN PHY",			0x0015, 0xF440, LAN पूर्ण,
	अणु "ICS LAN PHY",			0x0143, 0xBC70, LAN पूर्ण,
	अणु "NS 83851 PHY",			0x2000, 0x5C20, MIX पूर्ण,
	अणु "NS 83847 PHY",                       0x2000, 0x5C30, MIX पूर्ण,
	अणु "Realtek RTL8201 PHY",		0x0000, 0x8200, LAN पूर्ण,
	अणु "VIA 6103 PHY",			0x0101, 0x8f20, LAN पूर्ण,
	अणुशून्य,पूर्ण,
पूर्ण;

काष्ठा mii_phy अणु
	काष्ठा mii_phy * next;
	पूर्णांक phy_addr;
	u16 phy_id0;
	u16 phy_id1;
	u16 status;
	u8  phy_types;
पूर्ण;

प्रकार काष्ठा _BufferDesc अणु
	u32 link;
	u32 cmdsts;
	u32 bufptr;
पूर्ण BufferDesc;

काष्ठा sis900_निजी अणु
	काष्ठा pci_dev * pci_dev;

	spinlock_t lock;

	काष्ठा mii_phy * mii;
	काष्ठा mii_phy * first_mii; /* record the first mii काष्ठाure */
	अचिन्हित पूर्णांक cur_phy;
	काष्ठा mii_अगर_info mii_info;

	व्योम __iomem	*ioaddr;

	काष्ठा समयr_list समयr; /* Link status detection समयr. */
	u8 स्वतःng_complete; /* 1: स्वतः-negotiate complete  */

	u32 msg_enable;

	अचिन्हित पूर्णांक cur_rx, dirty_rx; /* producer/consumer poपूर्णांकers क्रम Tx/Rx ring */
	अचिन्हित पूर्णांक cur_tx, dirty_tx;

	/* The saved address of a sent/receive-in-place packet buffer */
	काष्ठा sk_buff *tx_skbuff[NUM_TX_DESC];
	काष्ठा sk_buff *rx_skbuff[NUM_RX_DESC];
	BufferDesc *tx_ring;
	BufferDesc *rx_ring;

	dma_addr_t tx_ring_dma;
	dma_addr_t rx_ring_dma;

	अचिन्हित पूर्णांक tx_full; /* The Tx queue is full. */
	u8 host_bridge_rev;
	u8 chipset_rev;
	/* EEPROM data */
	पूर्णांक eeprom_size;
पूर्ण;

MODULE_AUTHOR("Jim Huang <cmhuang@sis.com.tw>, Ollie Lho <ollie@sis.com.tw>");
MODULE_DESCRIPTION("SiS 900 PCI Fast Ethernet driver");
MODULE_LICENSE("GPL");

module_param(multicast_filter_limit, पूर्णांक, 0444);
module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0444);
module_param(sis900_debug, पूर्णांक, 0444);
MODULE_PARM_DESC(multicast_filter_limit, "SiS 900/7016 maximum number of filtered multicast addresses");
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "SiS 900/7016 maximum events handled per interrupt");
MODULE_PARM_DESC(sis900_debug, "SiS 900/7016 bitmapped debugging message level");

#घोषणा sw32(reg, val)	ioग_लिखो32(val, ioaddr + (reg))
#घोषणा sw8(reg, val)	ioग_लिखो8(val, ioaddr + (reg))
#घोषणा sr32(reg)	ioपढ़ो32(ioaddr + (reg))
#घोषणा sr16(reg)	ioपढ़ो16(ioaddr + (reg))

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम sis900_poll(काष्ठा net_device *dev);
#पूर्ण_अगर
अटल पूर्णांक sis900_खोलो(काष्ठा net_device *net_dev);
अटल पूर्णांक sis900_mii_probe (काष्ठा net_device * net_dev);
अटल व्योम sis900_init_rxfilter (काष्ठा net_device * net_dev);
अटल u16 पढ़ो_eeprom(व्योम __iomem *ioaddr, पूर्णांक location);
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *net_dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *net_dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक val);
अटल व्योम sis900_समयr(काष्ठा समयr_list *t);
अटल व्योम sis900_check_mode (काष्ठा net_device *net_dev, काष्ठा mii_phy *mii_phy);
अटल व्योम sis900_tx_समयout(काष्ठा net_device *net_dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम sis900_init_tx_ring(काष्ठा net_device *net_dev);
अटल व्योम sis900_init_rx_ring(काष्ठा net_device *net_dev);
अटल netdev_tx_t sis900_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *net_dev);
अटल पूर्णांक sis900_rx(काष्ठा net_device *net_dev);
अटल व्योम sis900_finish_xmit (काष्ठा net_device *net_dev);
अटल irqवापस_t sis900_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल पूर्णांक sis900_बंद(काष्ठा net_device *net_dev);
अटल पूर्णांक mii_ioctl(काष्ठा net_device *net_dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल u16 sis900_mcast_bitnr(u8 *addr, u8 revision);
अटल व्योम set_rx_mode(काष्ठा net_device *net_dev);
अटल व्योम sis900_reset(काष्ठा net_device *net_dev);
अटल व्योम sis630_set_eq(काष्ठा net_device *net_dev, u8 revision);
अटल पूर्णांक sis900_set_config(काष्ठा net_device *dev, काष्ठा अगरmap *map);
अटल u16 sis900_शेष_phy(काष्ठा net_device * net_dev);
अटल व्योम sis900_set_capability( काष्ठा net_device *net_dev ,काष्ठा mii_phy *phy);
अटल u16 sis900_reset_phy(काष्ठा net_device *net_dev, पूर्णांक phy_addr);
अटल व्योम sis900_स्वतः_negotiate(काष्ठा net_device *net_dev, पूर्णांक phy_addr);
अटल व्योम sis900_set_mode(काष्ठा sis900_निजी *, पूर्णांक speed, पूर्णांक duplex);
अटल स्थिर काष्ठा ethtool_ops sis900_ethtool_ops;

/**
 *	sis900_get_mac_addr - Get MAC address क्रम stand alone SiS900 model
 *	@pci_dev: the sis900 pci device
 *	@net_dev: the net device to get address क्रम
 *
 *	Older SiS900 and मित्रs, use EEPROM to store MAC address.
 *	MAC address is पढ़ो from पढ़ो_eeprom() पूर्णांकo @net_dev->dev_addr.
 */

अटल पूर्णांक sis900_get_mac_addr(काष्ठा pci_dev *pci_dev,
			       काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	u16 signature;
	पूर्णांक i;

	/* check to see अगर we have sane EEPROM */
	signature = (u16) पढ़ो_eeprom(ioaddr, EEPROMSignature);
	अगर (signature == 0xffff || signature == 0x0000) अणु
		prपूर्णांकk (KERN_WARNING "%s: Error EEPROM read %x\n",
			pci_name(pci_dev), signature);
		वापस 0;
	पूर्ण

	/* get MAC address from EEPROM */
	क्रम (i = 0; i < 3; i++)
	        ((u16 *)(net_dev->dev_addr))[i] = पढ़ो_eeprom(ioaddr, i+EEPROMMACAddr);

	वापस 1;
पूर्ण

/**
 *	sis630e_get_mac_addr - Get MAC address क्रम SiS630E model
 *	@pci_dev: the sis900 pci device
 *	@net_dev: the net device to get address क्रम
 *
 *	SiS630E model, use APC CMOS RAM to store MAC address.
 *	APC CMOS RAM is accessed through ISA bridge.
 *	MAC address is पढ़ो पूर्णांकo @net_dev->dev_addr.
 */

अटल पूर्णांक sis630e_get_mac_addr(काष्ठा pci_dev *pci_dev,
				काष्ठा net_device *net_dev)
अणु
	काष्ठा pci_dev *isa_bridge = शून्य;
	u8 reg;
	पूर्णांक i;

	isa_bridge = pci_get_device(PCI_VENDOR_ID_SI, 0x0008, isa_bridge);
	अगर (!isa_bridge)
		isa_bridge = pci_get_device(PCI_VENDOR_ID_SI, 0x0018, isa_bridge);
	अगर (!isa_bridge) अणु
		prपूर्णांकk(KERN_WARNING "%s: Can not find ISA bridge\n",
		       pci_name(pci_dev));
		वापस 0;
	पूर्ण
	pci_पढ़ो_config_byte(isa_bridge, 0x48, &reg);
	pci_ग_लिखो_config_byte(isa_bridge, 0x48, reg | 0x40);

	क्रम (i = 0; i < 6; i++) अणु
		outb(0x09 + i, 0x70);
		((u8 *)(net_dev->dev_addr))[i] = inb(0x71);
	पूर्ण

	pci_ग_लिखो_config_byte(isa_bridge, 0x48, reg & ~0x40);
	pci_dev_put(isa_bridge);

	वापस 1;
पूर्ण


/**
 *	sis635_get_mac_addr - Get MAC address क्रम SIS635 model
 *	@pci_dev: the sis900 pci device
 *	@net_dev: the net device to get address क्रम
 *
 *	SiS635 model, set MAC Reload Bit to load Mac address from APC
 *	to rfdr. rfdr is accessed through rfcr. MAC address is पढ़ो पूर्णांकo
 *	@net_dev->dev_addr.
 */

अटल पूर्णांक sis635_get_mac_addr(काष्ठा pci_dev *pci_dev,
			       काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	u32 rfcrSave;
	u32 i;

	rfcrSave = sr32(rfcr);

	sw32(cr, rfcrSave | RELOAD);
	sw32(cr, 0);

	/* disable packet filtering beक्रमe setting filter */
	sw32(rfcr, rfcrSave & ~RFEN);

	/* load MAC addr to filter data रेजिस्टर */
	क्रम (i = 0 ; i < 3 ; i++) अणु
		sw32(rfcr, (i << RFADDR_shअगरt));
		*( ((u16 *)net_dev->dev_addr) + i) = sr16(rfdr);
	पूर्ण

	/* enable packet filtering */
	sw32(rfcr, rfcrSave | RFEN);

	वापस 1;
पूर्ण

/**
 *	sis96x_get_mac_addr - Get MAC address क्रम SiS962 or SiS963 model
 *	@pci_dev: the sis900 pci device
 *	@net_dev: the net device to get address क्रम
 *
 *	SiS962 or SiS963 model, use EEPROM to store MAC address. And EEPROM
 *	is shared by
 *	LAN and 1394. When accessing EEPROM, send EEREQ संकेत to hardware first
 *	and रुको क्रम EEGNT. If EEGNT is ON, EEPROM is permitted to be accessed
 *	by LAN, otherwise it is not. After MAC address is पढ़ो from EEPROM, send
 *	EEDONE संकेत to refuse EEPROM access by LAN.
 *	The EEPROM map of SiS962 or SiS963 is dअगरferent to SiS900.
 *	The signature field in SiS962 or SiS963 spec is meaningless.
 *	MAC address is पढ़ो पूर्णांकo @net_dev->dev_addr.
 */

अटल पूर्णांक sis96x_get_mac_addr(काष्ठा pci_dev *pci_dev,
			       काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	पूर्णांक रुको, rc = 0;

	sw32(mear, EEREQ);
	क्रम (रुको = 0; रुको < 2000; रुको++) अणु
		अगर (sr32(mear) & EEGNT) अणु
			u16 *mac = (u16 *)net_dev->dev_addr;
			पूर्णांक i;

			/* get MAC address from EEPROM */
			क्रम (i = 0; i < 3; i++)
			        mac[i] = पढ़ो_eeprom(ioaddr, i + EEPROMMACAddr);

			rc = 1;
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
	sw32(mear, EEDONE);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sis900_netdev_ops = अणु
	.nकरो_खोलो		 = sis900_खोलो,
	.nकरो_stop		= sis900_बंद,
	.nकरो_start_xmit		= sis900_start_xmit,
	.nकरो_set_config		= sis900_set_config,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_करो_ioctl		= mii_ioctl,
	.nकरो_tx_समयout		= sis900_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
        .nकरो_poll_controller	= sis900_poll,
#पूर्ण_अगर
पूर्ण;

/**
 *	sis900_probe - Probe क्रम sis900 device
 *	@pci_dev: the sis900 pci device
 *	@pci_id: the pci device ID
 *
 *	Check and probe sis900 net device क्रम @pci_dev.
 *	Get mac address according to the chip revision,
 *	and assign SiS900-specअगरic entries in the device काष्ठाure.
 *	ie: sis900_खोलो(), sis900_start_xmit(), sis900_बंद(), etc.
 */

अटल पूर्णांक sis900_probe(काष्ठा pci_dev *pci_dev,
			स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा sis900_निजी *sis_priv;
	काष्ठा net_device *net_dev;
	काष्ठा pci_dev *dev;
	dma_addr_t ring_dma;
	व्योम *ring_space;
	व्योम __iomem *ioaddr;
	पूर्णांक i, ret;
	स्थिर अक्षर *card_name = card_names[pci_id->driver_data];
	स्थिर अक्षर *dev_name = pci_name(pci_dev);

/* when built पूर्णांकo the kernel, we only prपूर्णांक version अगर device is found */
#अगर_अघोषित MODULE
	अटल पूर्णांक prपूर्णांकed_version;
	अगर (!prपूर्णांकed_version++)
		prपूर्णांकk(version);
#पूर्ण_अगर

	/* setup various bits in PCI command रेजिस्टर */
	ret = pci_enable_device(pci_dev);
	अगर(ret) वापस ret;

	i = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	अगर(i)अणु
		prपूर्णांकk(KERN_ERR "sis900.c: architecture does not support "
			"32bit PCI busmaster DMA\n");
		वापस i;
	पूर्ण

	pci_set_master(pci_dev);

	net_dev = alloc_etherdev(माप(काष्ठा sis900_निजी));
	अगर (!net_dev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(net_dev, &pci_dev->dev);

	/* We करो a request_region() to रेजिस्टर /proc/ioports info. */
	ret = pci_request_regions(pci_dev, "sis900");
	अगर (ret)
		जाओ err_out;

	/* IO region. */
	ioaddr = pci_iomap(pci_dev, 0, 0);
	अगर (!ioaddr) अणु
		ret = -ENOMEM;
		जाओ err_out_cleardev;
	पूर्ण

	sis_priv = netdev_priv(net_dev);
	sis_priv->ioaddr = ioaddr;
	sis_priv->pci_dev = pci_dev;
	spin_lock_init(&sis_priv->lock);

	sis_priv->eeprom_size = 24;

	pci_set_drvdata(pci_dev, net_dev);

	ring_space = dma_alloc_coherent(&pci_dev->dev, TX_TOTAL_SIZE,
					&ring_dma, GFP_KERNEL);
	अगर (!ring_space) अणु
		ret = -ENOMEM;
		जाओ err_out_unmap;
	पूर्ण
	sis_priv->tx_ring = ring_space;
	sis_priv->tx_ring_dma = ring_dma;

	ring_space = dma_alloc_coherent(&pci_dev->dev, RX_TOTAL_SIZE,
					&ring_dma, GFP_KERNEL);
	अगर (!ring_space) अणु
		ret = -ENOMEM;
		जाओ err_unmap_tx;
	पूर्ण
	sis_priv->rx_ring = ring_space;
	sis_priv->rx_ring_dma = ring_dma;

	/* The SiS900-specअगरic entries in the device काष्ठाure. */
	net_dev->netdev_ops = &sis900_netdev_ops;
	net_dev->watchकरोg_समयo = TX_TIMEOUT;
	net_dev->ethtool_ops = &sis900_ethtool_ops;

	अगर (sis900_debug > 0)
		sis_priv->msg_enable = sis900_debug;
	अन्यथा
		sis_priv->msg_enable = SIS900_DEF_MSG;

	sis_priv->mii_info.dev = net_dev;
	sis_priv->mii_info.mdio_पढ़ो = mdio_पढ़ो;
	sis_priv->mii_info.mdio_ग_लिखो = mdio_ग_लिखो;
	sis_priv->mii_info.phy_id_mask = 0x1f;
	sis_priv->mii_info.reg_num_mask = 0x1f;

	/* Get Mac address according to the chip revision */
	sis_priv->chipset_rev = pci_dev->revision;
	अगर(netअगर_msg_probe(sis_priv))
		prपूर्णांकk(KERN_DEBUG "%s: detected revision %2.2x, "
				"trying to get MAC address...\n",
				dev_name, sis_priv->chipset_rev);

	ret = 0;
	अगर (sis_priv->chipset_rev == SIS630E_900_REV)
		ret = sis630e_get_mac_addr(pci_dev, net_dev);
	अन्यथा अगर ((sis_priv->chipset_rev > 0x81) && (sis_priv->chipset_rev <= 0x90) )
		ret = sis635_get_mac_addr(pci_dev, net_dev);
	अन्यथा अगर (sis_priv->chipset_rev == SIS96x_900_REV)
		ret = sis96x_get_mac_addr(pci_dev, net_dev);
	अन्यथा
		ret = sis900_get_mac_addr(pci_dev, net_dev);

	अगर (!ret || !is_valid_ether_addr(net_dev->dev_addr)) अणु
		eth_hw_addr_अक्रमom(net_dev);
		prपूर्णांकk(KERN_WARNING "%s: Unreadable or invalid MAC address,"
				"using random generated one\n", dev_name);
	पूर्ण

	/* 630ET : set the mii access mode as software-mode */
	अगर (sis_priv->chipset_rev == SIS630ET_900_REV)
		sw32(cr, ACCESSMODE | sr32(cr));

	/* probe क्रम mii transceiver */
	अगर (sis900_mii_probe(net_dev) == 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: Error probing MII device.\n",
		       dev_name);
		ret = -ENODEV;
		जाओ err_unmap_rx;
	पूर्ण

	/* save our host bridge revision */
	dev = pci_get_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_630, शून्य);
	अगर (dev) अणु
		sis_priv->host_bridge_rev = dev->revision;
		pci_dev_put(dev);
	पूर्ण

	ret = रेजिस्टर_netdev(net_dev);
	अगर (ret)
		जाओ err_unmap_rx;

	/* prपूर्णांक some inक्रमmation about our NIC */
	prपूर्णांकk(KERN_INFO "%s: %s at 0x%p, IRQ %d, %pM\n",
	       net_dev->name, card_name, ioaddr, pci_dev->irq,
	       net_dev->dev_addr);

	/* Detect Wake on Lan support */
	ret = (sr32(CFGPMC) & PMESP) >> 27;
	अगर (netअगर_msg_probe(sis_priv) && (ret & PME_D3C) == 0)
		prपूर्णांकk(KERN_INFO "%s: Wake on LAN only available from suspend to RAM.", net_dev->name);

	वापस 0;

err_unmap_rx:
	dma_मुक्त_coherent(&pci_dev->dev, RX_TOTAL_SIZE, sis_priv->rx_ring,
			  sis_priv->rx_ring_dma);
err_unmap_tx:
	dma_मुक्त_coherent(&pci_dev->dev, TX_TOTAL_SIZE, sis_priv->tx_ring,
			  sis_priv->tx_ring_dma);
err_out_unmap:
	pci_iounmap(pci_dev, ioaddr);
err_out_cleardev:
	pci_release_regions(pci_dev);
 err_out:
	मुक्त_netdev(net_dev);
	वापस ret;
पूर्ण

/**
 *	sis900_mii_probe - Probe MII PHY क्रम sis900
 *	@net_dev: the net device to probe क्रम
 *
 *	Search क्रम total of 32 possible mii phy addresses.
 *	Identअगरy and set current phy अगर found one,
 *	वापस error अगर it failed to found.
 */

अटल पूर्णांक sis900_mii_probe(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	स्थिर अक्षर *dev_name = pci_name(sis_priv->pci_dev);
	u16 poll_bit = MII_STAT_LINK, status = 0;
	अचिन्हित दीर्घ समयout = jअगरfies + 5 * HZ;
	पूर्णांक phy_addr;

	sis_priv->mii = शून्य;

	/* search क्रम total of 32 possible mii phy addresses */
	क्रम (phy_addr = 0; phy_addr < 32; phy_addr++) अणु
		काष्ठा mii_phy * mii_phy = शून्य;
		u16 mii_status;
		पूर्णांक i;

		mii_phy = शून्य;
		क्रम(i = 0; i < 2; i++)
			mii_status = mdio_पढ़ो(net_dev, phy_addr, MII_STATUS);

		अगर (mii_status == 0xffff || mii_status == 0x0000) अणु
			अगर (netअगर_msg_probe(sis_priv))
				prपूर्णांकk(KERN_DEBUG "%s: MII at address %d"
						" not accessible\n",
						dev_name, phy_addr);
			जारी;
		पूर्ण

		अगर ((mii_phy = kदो_स्मृति(माप(काष्ठा mii_phy), GFP_KERNEL)) == शून्य) अणु
			mii_phy = sis_priv->first_mii;
			जबतक (mii_phy) अणु
				काष्ठा mii_phy *phy;
				phy = mii_phy;
				mii_phy = mii_phy->next;
				kमुक्त(phy);
			पूर्ण
			वापस 0;
		पूर्ण

		mii_phy->phy_id0 = mdio_पढ़ो(net_dev, phy_addr, MII_PHY_ID0);
		mii_phy->phy_id1 = mdio_पढ़ो(net_dev, phy_addr, MII_PHY_ID1);
		mii_phy->phy_addr = phy_addr;
		mii_phy->status = mii_status;
		mii_phy->next = sis_priv->mii;
		sis_priv->mii = mii_phy;
		sis_priv->first_mii = mii_phy;

		क्रम (i = 0; mii_chip_table[i].phy_id1; i++)
			अगर ((mii_phy->phy_id0 == mii_chip_table[i].phy_id0 ) &&
			    ((mii_phy->phy_id1 & 0xFFF0) == mii_chip_table[i].phy_id1))अणु
				mii_phy->phy_types = mii_chip_table[i].phy_types;
				अगर (mii_chip_table[i].phy_types == MIX)
					mii_phy->phy_types =
					    (mii_status & (MII_STAT_CAN_TX_FDX | MII_STAT_CAN_TX)) ? LAN : HOME;
				prपूर्णांकk(KERN_INFO "%s: %s transceiver found "
							"at address %d.\n",
							dev_name,
							mii_chip_table[i].name,
							phy_addr);
				अवरोध;
			पूर्ण

		अगर( !mii_chip_table[i].phy_id1 ) अणु
			prपूर्णांकk(KERN_INFO "%s: Unknown PHY transceiver found at address %d.\n",
			       dev_name, phy_addr);
			mii_phy->phy_types = UNKNOWN;
		पूर्ण
	पूर्ण

	अगर (sis_priv->mii == शून्य) अणु
		prपूर्णांकk(KERN_INFO "%s: No MII transceivers found!\n", dev_name);
		वापस 0;
	पूर्ण

	/* select शेष PHY क्रम mac */
	sis_priv->mii = शून्य;
	sis900_शेष_phy( net_dev );

	/* Reset phy अगर शेष phy is पूर्णांकernal sis900 */
        अगर ((sis_priv->mii->phy_id0 == 0x001D) &&
	    ((sis_priv->mii->phy_id1&0xFFF0) == 0x8000))
        	status = sis900_reset_phy(net_dev, sis_priv->cur_phy);

        /* workaround क्रम ICS1893 PHY */
        अगर ((sis_priv->mii->phy_id0 == 0x0015) &&
            ((sis_priv->mii->phy_id1&0xFFF0) == 0xF440))
            	mdio_ग_लिखो(net_dev, sis_priv->cur_phy, 0x0018, 0xD200);

	अगर(status & MII_STAT_LINK)अणु
		जबतक (poll_bit) अणु
			yield();

			poll_bit ^= (mdio_पढ़ो(net_dev, sis_priv->cur_phy, MII_STATUS) & poll_bit);
			अगर (समय_after_eq(jअगरfies, समयout)) अणु
				prपूर्णांकk(KERN_WARNING "%s: reset phy and link down now\n",
				       dev_name);
				वापस -ETIME;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (sis_priv->chipset_rev == SIS630E_900_REV) अणु
		/* SiS 630E has some bugs on शेष value of PHY रेजिस्टरs */
		mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_ANADV, 0x05e1);
		mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_CONFIG1, 0x22);
		mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_CONFIG2, 0xff00);
		mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_MASK, 0xffc0);
		//mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_CONTROL, 0x1000);
	पूर्ण

	अगर (sis_priv->mii->status & MII_STAT_LINK)
		netअगर_carrier_on(net_dev);
	अन्यथा
		netअगर_carrier_off(net_dev);

	वापस 1;
पूर्ण

/**
 *	sis900_शेष_phy - Select शेष PHY क्रम sis900 mac.
 *	@net_dev: the net device to probe क्रम
 *
 *	Select first detected PHY with link as शेष.
 *	If no one is link on, select PHY whose types is HOME as शेष.
 *	If HOME करोesn't exist, select LAN.
 */

अटल u16 sis900_शेष_phy(काष्ठा net_device * net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
 	काष्ठा mii_phy *phy = शून्य, *phy_home = शून्य,
		*शेष_phy = शून्य, *phy_lan = शून्य;
	u16 status;

        क्रम (phy=sis_priv->first_mii; phy; phy=phy->next) अणु
		status = mdio_पढ़ो(net_dev, phy->phy_addr, MII_STATUS);
		status = mdio_पढ़ो(net_dev, phy->phy_addr, MII_STATUS);

		/* Link ON & Not select शेष PHY & not ghost PHY */
		अगर ((status & MII_STAT_LINK) && !शेष_phy &&
		    (phy->phy_types != UNKNOWN)) अणु
			शेष_phy = phy;
		पूर्ण अन्यथा अणु
			status = mdio_पढ़ो(net_dev, phy->phy_addr, MII_CONTROL);
			mdio_ग_लिखो(net_dev, phy->phy_addr, MII_CONTROL,
				status | MII_CNTL_AUTO | MII_CNTL_ISOLATE);
			अगर (phy->phy_types == HOME)
				phy_home = phy;
			अन्यथा अगर(phy->phy_types == LAN)
				phy_lan = phy;
		पूर्ण
	पूर्ण

	अगर (!शेष_phy && phy_home)
		शेष_phy = phy_home;
	अन्यथा अगर (!शेष_phy && phy_lan)
		शेष_phy = phy_lan;
	अन्यथा अगर (!शेष_phy)
		शेष_phy = sis_priv->first_mii;

	अगर (sis_priv->mii != शेष_phy) अणु
		sis_priv->mii = शेष_phy;
		sis_priv->cur_phy = शेष_phy->phy_addr;
		prपूर्णांकk(KERN_INFO "%s: Using transceiver found at address %d as default\n",
		       pci_name(sis_priv->pci_dev), sis_priv->cur_phy);
	पूर्ण

	sis_priv->mii_info.phy_id = sis_priv->cur_phy;

	status = mdio_पढ़ो(net_dev, sis_priv->cur_phy, MII_CONTROL);
	status &= (~MII_CNTL_ISOLATE);

	mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_CONTROL, status);
	status = mdio_पढ़ो(net_dev, sis_priv->cur_phy, MII_STATUS);
	status = mdio_पढ़ो(net_dev, sis_priv->cur_phy, MII_STATUS);

	वापस status;
पूर्ण


/**
 * 	sis900_set_capability - set the media capability of network adapter.
 *	@net_dev : the net device to probe क्रम
 *	@phy : शेष PHY
 *
 *	Set the media capability of network adapter according to
 *	mii status रेजिस्टर. It's necessary beक्रमe स्वतः-negotiate.
 */

अटल व्योम sis900_set_capability(काष्ठा net_device *net_dev, काष्ठा mii_phy *phy)
अणु
	u16 cap;

	mdio_पढ़ो(net_dev, phy->phy_addr, MII_STATUS);
	mdio_पढ़ो(net_dev, phy->phy_addr, MII_STATUS);

	cap = MII_NWAY_CSMA_CD |
		((phy->status & MII_STAT_CAN_TX_FDX)? MII_NWAY_TX_FDX:0) |
		((phy->status & MII_STAT_CAN_TX)    ? MII_NWAY_TX:0) |
		((phy->status & MII_STAT_CAN_T_FDX) ? MII_NWAY_T_FDX:0)|
		((phy->status & MII_STAT_CAN_T)     ? MII_NWAY_T:0);

	mdio_ग_लिखो(net_dev, phy->phy_addr, MII_ANADV, cap);
पूर्ण


/* Delay between EEPROM घड़ी transitions. */
#घोषणा eeprom_delay()	sr32(mear)

/**
 *	पढ़ो_eeprom - Read Serial EEPROM
 *	@ioaddr: base i/o address
 *	@location: the EEPROM location to पढ़ो
 *
 *	Read Serial EEPROM through EEPROM Access Register.
 *	Note that location is in word (16 bits) unit
 */

अटल u16 पढ़ो_eeprom(व्योम __iomem *ioaddr, पूर्णांक location)
अणु
	u32 पढ़ो_cmd = location | EEपढ़ो;
	पूर्णांक i;
	u16 retval = 0;

	sw32(mear, 0);
	eeprom_delay();
	sw32(mear, EECS);
	eeprom_delay();

	/* Shअगरt the पढ़ो command (9) bits out. */
	क्रम (i = 8; i >= 0; i--) अणु
		u32 dataval = (पढ़ो_cmd & (1 << i)) ? EEDI | EECS : EECS;

		sw32(mear, dataval);
		eeprom_delay();
		sw32(mear, dataval | EECLK);
		eeprom_delay();
	पूर्ण
	sw32(mear, EECS);
	eeprom_delay();

	/* पढ़ो the 16-bits data in */
	क्रम (i = 16; i > 0; i--) अणु
		sw32(mear, EECS);
		eeprom_delay();
		sw32(mear, EECS | EECLK);
		eeprom_delay();
		retval = (retval << 1) | ((sr32(mear) & EEDO) ? 1 : 0);
		eeprom_delay();
	पूर्ण

	/* Terminate the EEPROM access. */
	sw32(mear, 0);
	eeprom_delay();

	वापस retval;
पूर्ण

/* Read and ग_लिखो the MII management रेजिस्टरs using software-generated
   serial MDIO protocol. Note that the command bits and data bits are
   send out separately */
#घोषणा mdio_delay()	sr32(mear)

अटल व्योम mdio_idle(काष्ठा sis900_निजी *sp)
अणु
	व्योम __iomem *ioaddr = sp->ioaddr;

	sw32(mear, MDIO | MDसूची);
	mdio_delay();
	sw32(mear, MDIO | MDसूची | MDC);
पूर्ण

/* Synchronize the MII management पूर्णांकerface by shअगरting 32 one bits out. */
अटल व्योम mdio_reset(काष्ठा sis900_निजी *sp)
अणु
	व्योम __iomem *ioaddr = sp->ioaddr;
	पूर्णांक i;

	क्रम (i = 31; i >= 0; i--) अणु
		sw32(mear, MDसूची | MDIO);
		mdio_delay();
		sw32(mear, MDसूची | MDIO | MDC);
		mdio_delay();
	पूर्ण
पूर्ण

/**
 *	mdio_पढ़ो - पढ़ो MII PHY रेजिस्टर
 *	@net_dev: the net device to पढ़ो
 *	@phy_id: the phy address to पढ़ो
 *	@location: the phy रेजिस्टर id to पढ़ो
 *
 *	Read MII रेजिस्टरs through MDIO and MDC
 *	using MDIO management frame काष्ठाure and protocol(defined by ISO/IEC).
 *	Please see SiS7014 or ICS spec
 */

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *net_dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	पूर्णांक mii_cmd = MIIपढ़ो|(phy_id<<MIIpmdShअगरt)|(location<<MIIregShअगरt);
	काष्ठा sis900_निजी *sp = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sp->ioaddr;
	u16 retval = 0;
	पूर्णांक i;

	mdio_reset(sp);
	mdio_idle(sp);

	क्रम (i = 15; i >= 0; i--) अणु
		पूर्णांक dataval = (mii_cmd & (1 << i)) ? MDसूची | MDIO : MDसूची;

		sw32(mear, dataval);
		mdio_delay();
		sw32(mear, dataval | MDC);
		mdio_delay();
	पूर्ण

	/* Read the 16 data bits. */
	क्रम (i = 16; i > 0; i--) अणु
		sw32(mear, 0);
		mdio_delay();
		retval = (retval << 1) | ((sr32(mear) & MDIO) ? 1 : 0);
		sw32(mear, MDC);
		mdio_delay();
	पूर्ण
	sw32(mear, 0x00);

	वापस retval;
पूर्ण

/**
 *	mdio_ग_लिखो - ग_लिखो MII PHY रेजिस्टर
 *	@net_dev: the net device to ग_लिखो
 *	@phy_id: the phy address to ग_लिखो
 *	@location: the phy रेजिस्टर id to ग_लिखो
 *	@value: the रेजिस्टर value to ग_लिखो with
 *
 *	Write MII रेजिस्टरs with @value through MDIO and MDC
 *	using MDIO management frame काष्ठाure and protocol(defined by ISO/IEC)
 *	please see SiS7014 or ICS spec
 */

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *net_dev, पूर्णांक phy_id, पूर्णांक location,
			पूर्णांक value)
अणु
	पूर्णांक mii_cmd = MIIग_लिखो|(phy_id<<MIIpmdShअगरt)|(location<<MIIregShअगरt);
	काष्ठा sis900_निजी *sp = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sp->ioaddr;
	पूर्णांक i;

	mdio_reset(sp);
	mdio_idle(sp);

	/* Shअगरt the command bits out. */
	क्रम (i = 15; i >= 0; i--) अणु
		पूर्णांक dataval = (mii_cmd & (1 << i)) ? MDसूची | MDIO : MDसूची;

		sw8(mear, dataval);
		mdio_delay();
		sw8(mear, dataval | MDC);
		mdio_delay();
	पूर्ण
	mdio_delay();

	/* Shअगरt the value bits out. */
	क्रम (i = 15; i >= 0; i--) अणु
		पूर्णांक dataval = (value & (1 << i)) ? MDसूची | MDIO : MDसूची;

		sw32(mear, dataval);
		mdio_delay();
		sw32(mear, dataval | MDC);
		mdio_delay();
	पूर्ण
	mdio_delay();

	/* Clear out extra bits. */
	क्रम (i = 2; i > 0; i--) अणु
		sw8(mear, 0);
		mdio_delay();
		sw8(mear, MDC);
		mdio_delay();
	पूर्ण
	sw32(mear, 0x00);
पूर्ण


/**
 *	sis900_reset_phy - reset sis900 mii phy.
 *	@net_dev: the net device to ग_लिखो
 *	@phy_addr: शेष phy address
 *
 *	Some specअगरic phy can't work properly without reset.
 *	This function will be called during initialization and
 *	link status change from ON to DOWN.
 */

अटल u16 sis900_reset_phy(काष्ठा net_device *net_dev, पूर्णांक phy_addr)
अणु
	पूर्णांक i;
	u16 status;

	क्रम (i = 0; i < 2; i++)
		status = mdio_पढ़ो(net_dev, phy_addr, MII_STATUS);

	mdio_ग_लिखो( net_dev, phy_addr, MII_CONTROL, MII_CNTL_RESET );

	वापस status;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
*/
अटल व्योम sis900_poll(काष्ठा net_device *dev)
अणु
	काष्ठा sis900_निजी *sp = netdev_priv(dev);
	स्थिर पूर्णांक irq = sp->pci_dev->irq;

	disable_irq(irq);
	sis900_पूर्णांकerrupt(irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

/**
 *	sis900_खोलो - खोलो sis900 device
 *	@net_dev: the net device to खोलो
 *
 *	Do some initialization and start net पूर्णांकerface.
 *	enable पूर्णांकerrupts and set sis900 समयr.
 */

अटल पूर्णांक
sis900_खोलो(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	पूर्णांक ret;

	/* Soft reset the chip. */
	sis900_reset(net_dev);

	/* Equalizer workaround Rule */
	sis630_set_eq(net_dev, sis_priv->chipset_rev);

	ret = request_irq(sis_priv->pci_dev->irq, sis900_पूर्णांकerrupt, IRQF_SHARED,
			  net_dev->name, net_dev);
	अगर (ret)
		वापस ret;

	sis900_init_rxfilter(net_dev);

	sis900_init_tx_ring(net_dev);
	sis900_init_rx_ring(net_dev);

	set_rx_mode(net_dev);

	netअगर_start_queue(net_dev);

	/* Workaround क्रम EDB */
	sis900_set_mode(sis_priv, HW_SPEED_10_MBPS, FDX_CAPABLE_HALF_SELECTED);

	/* Enable all known पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	sw32(imr, RxSOVR | RxORN | RxERR | RxOK | TxURN | TxERR | TxDESC);
	sw32(cr, RxENA | sr32(cr));
	sw32(ier, IE);

	sis900_check_mode(net_dev, sis_priv->mii);

	/* Set the समयr to चयन to check क्रम link beat and perhaps चयन
	   to an alternate media type. */
	समयr_setup(&sis_priv->समयr, sis900_समयr, 0);
	sis_priv->समयr.expires = jअगरfies + HZ;
	add_समयr(&sis_priv->समयr);

	वापस 0;
पूर्ण

/**
 *	sis900_init_rxfilter - Initialize the Rx filter
 *	@net_dev: the net device to initialize क्रम
 *
 *	Set receive filter address to our MAC address
 *	and enable packet filtering.
 */

अटल व्योम
sis900_init_rxfilter (काष्ठा net_device * net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	u32 rfcrSave;
	u32 i;

	rfcrSave = sr32(rfcr);

	/* disable packet filtering beक्रमe setting filter */
	sw32(rfcr, rfcrSave & ~RFEN);

	/* load MAC addr to filter data रेजिस्टर */
	क्रम (i = 0 ; i < 3 ; i++) अणु
		u32 w = (u32) *((u16 *)(net_dev->dev_addr)+i);

		sw32(rfcr, i << RFADDR_shअगरt);
		sw32(rfdr, w);

		अगर (netअगर_msg_hw(sis_priv)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: Receive Filter Address[%d]=%x\n",
			       net_dev->name, i, sr32(rfdr));
		पूर्ण
	पूर्ण

	/* enable packet filtering */
	sw32(rfcr, rfcrSave | RFEN);
पूर्ण

/**
 *	sis900_init_tx_ring - Initialize the Tx descriptor ring
 *	@net_dev: the net device to initialize क्रम
 *
 *	Initialize the Tx descriptor ring,
 */

अटल व्योम
sis900_init_tx_ring(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	पूर्णांक i;

	sis_priv->tx_full = 0;
	sis_priv->dirty_tx = sis_priv->cur_tx = 0;

	क्रम (i = 0; i < NUM_TX_DESC; i++) अणु
		sis_priv->tx_skbuff[i] = शून्य;

		sis_priv->tx_ring[i].link = sis_priv->tx_ring_dma +
			((i+1)%NUM_TX_DESC)*माप(BufferDesc);
		sis_priv->tx_ring[i].cmdsts = 0;
		sis_priv->tx_ring[i].bufptr = 0;
	पूर्ण

	/* load Transmit Descriptor Register */
	sw32(txdp, sis_priv->tx_ring_dma);
	अगर (netअगर_msg_hw(sis_priv))
		prपूर्णांकk(KERN_DEBUG "%s: TX descriptor register loaded with: %8.8x\n",
		       net_dev->name, sr32(txdp));
पूर्ण

/**
 *	sis900_init_rx_ring - Initialize the Rx descriptor ring
 *	@net_dev: the net device to initialize क्रम
 *
 *	Initialize the Rx descriptor ring,
 *	and pre-allocate receive buffers (socket buffer)
 */

अटल व्योम
sis900_init_rx_ring(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	पूर्णांक i;

	sis_priv->cur_rx = 0;
	sis_priv->dirty_rx = 0;

	/* init RX descriptor */
	क्रम (i = 0; i < NUM_RX_DESC; i++) अणु
		sis_priv->rx_skbuff[i] = शून्य;

		sis_priv->rx_ring[i].link = sis_priv->rx_ring_dma +
			((i+1)%NUM_RX_DESC)*माप(BufferDesc);
		sis_priv->rx_ring[i].cmdsts = 0;
		sis_priv->rx_ring[i].bufptr = 0;
	पूर्ण

	/* allocate sock buffers */
	क्रम (i = 0; i < NUM_RX_DESC; i++) अणु
		काष्ठा sk_buff *skb;

		अगर ((skb = netdev_alloc_skb(net_dev, RX_BUF_SIZE)) == शून्य) अणु
			/* not enough memory क्रम skbuff, this makes a "hole"
			   on the buffer ring, it is not clear how the
			   hardware will react to this kind of degenerated
			   buffer */
			अवरोध;
		पूर्ण
		sis_priv->rx_skbuff[i] = skb;
		sis_priv->rx_ring[i].cmdsts = RX_BUF_SIZE;
		sis_priv->rx_ring[i].bufptr = dma_map_single(&sis_priv->pci_dev->dev,
							     skb->data,
							     RX_BUF_SIZE,
							     DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(&sis_priv->pci_dev->dev,
					       sis_priv->rx_ring[i].bufptr))) अणु
			dev_kमुक्त_skb(skb);
			sis_priv->rx_skbuff[i] = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	sis_priv->dirty_rx = (अचिन्हित पूर्णांक) (i - NUM_RX_DESC);

	/* load Receive Descriptor Register */
	sw32(rxdp, sis_priv->rx_ring_dma);
	अगर (netअगर_msg_hw(sis_priv))
		prपूर्णांकk(KERN_DEBUG "%s: RX descriptor register loaded with: %8.8x\n",
		       net_dev->name, sr32(rxdp));
पूर्ण

/**
 *	sis630_set_eq - set phy equalizer value क्रम 630 LAN
 *	@net_dev: the net device to set equalizer value
 *	@revision: 630 LAN revision number
 *
 *	630E equalizer workaround rule(Cyrus Huang 08/15)
 *	PHY रेजिस्टर 14h(Test)
 *	Bit 14: 0 -- Automatically detect (शेष)
 *		1 -- Manually set Equalizer filter
 *	Bit 13: 0 -- (Default)
 *		1 -- Speed up convergence of equalizer setting
 *	Bit 9 : 0 -- (Default)
 *		1 -- Disable Baseline Wander
 *	Bit 3~7   -- Equalizer filter setting
 *	Link ON: Set Bit 9, 13 to 1, Bit 14 to 0
 *	Then calculate equalizer value
 *	Then set equalizer value, and set Bit 14 to 1, Bit 9 to 0
 *	Link Off:Set Bit 13 to 1, Bit 14 to 0
 *	Calculate Equalizer value:
 *	When Link is ON and Bit 14 is 0, SIS900PHY will स्वतः-detect proper equalizer value.
 *	When the equalizer is stable, this value is not a fixed value. It will be within
 *	a small range(eg. 7~9). Then we get a minimum and a maximum value(eg. min=7, max=9)
 *	0 <= max <= 4  --> set equalizer to max
 *	5 <= max <= 14 --> set equalizer to max+1 or set equalizer to max+2 अगर max == min
 *	max >= 15      --> set equalizer to max+5 or set equalizer to max+6 अगर max == min
 */

अटल व्योम sis630_set_eq(काष्ठा net_device *net_dev, u8 revision)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	u16 reg14h, eq_value=0, max_value=0, min_value=0;
	पूर्णांक i, maxcount=10;

	अगर ( !(revision == SIS630E_900_REV || revision == SIS630EA1_900_REV ||
	       revision == SIS630A_900_REV || revision ==  SIS630ET_900_REV) )
		वापस;

	अगर (netअगर_carrier_ok(net_dev)) अणु
		reg14h = mdio_पढ़ो(net_dev, sis_priv->cur_phy, MII_RESV);
		mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_RESV,
					(0x2200 | reg14h) & 0xBFFF);
		क्रम (i=0; i < maxcount; i++) अणु
			eq_value = (0x00F8 & mdio_पढ़ो(net_dev,
					sis_priv->cur_phy, MII_RESV)) >> 3;
			अगर (i == 0)
				max_value=min_value=eq_value;
			max_value = (eq_value > max_value) ?
						eq_value : max_value;
			min_value = (eq_value < min_value) ?
						eq_value : min_value;
		पूर्ण
		/* 630E rule to determine the equalizer value */
		अगर (revision == SIS630E_900_REV || revision == SIS630EA1_900_REV ||
		    revision == SIS630ET_900_REV) अणु
			अगर (max_value < 5)
				eq_value = max_value;
			अन्यथा अगर (max_value >= 5 && max_value < 15)
				eq_value = (max_value == min_value) ?
						max_value+2 : max_value+1;
			अन्यथा अगर (max_value >= 15)
				eq_value=(max_value == min_value) ?
						max_value+6 : max_value+5;
		पूर्ण
		/* 630B0&B1 rule to determine the equalizer value */
		अगर (revision == SIS630A_900_REV &&
		    (sis_priv->host_bridge_rev == SIS630B0 ||
		     sis_priv->host_bridge_rev == SIS630B1)) अणु
			अगर (max_value == 0)
				eq_value = 3;
			अन्यथा
				eq_value = (max_value + min_value + 1)/2;
		पूर्ण
		/* ग_लिखो equalizer value and setting */
		reg14h = mdio_पढ़ो(net_dev, sis_priv->cur_phy, MII_RESV);
		reg14h = (reg14h & 0xFF07) | ((eq_value << 3) & 0x00F8);
		reg14h = (reg14h | 0x6000) & 0xFDFF;
		mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_RESV, reg14h);
	पूर्ण अन्यथा अणु
		reg14h = mdio_पढ़ो(net_dev, sis_priv->cur_phy, MII_RESV);
		अगर (revision == SIS630A_900_REV &&
		    (sis_priv->host_bridge_rev == SIS630B0 ||
		     sis_priv->host_bridge_rev == SIS630B1))
			mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_RESV,
						(reg14h | 0x2200) & 0xBFFF);
		अन्यथा
			mdio_ग_लिखो(net_dev, sis_priv->cur_phy, MII_RESV,
						(reg14h | 0x2000) & 0xBFFF);
	पूर्ण
पूर्ण

/**
 *	sis900_समयr - sis900 समयr routine
 *	@t: समयr list containing a poपूर्णांकer to sis900 net device
 *
 *	On each समयr ticks we check two things,
 *	link status (ON/OFF) and link mode (10/100/Full/Half)
 */

अटल व्योम sis900_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sis900_निजी *sis_priv = from_समयr(sis_priv, t, समयr);
	काष्ठा net_device *net_dev = sis_priv->mii_info.dev;
	काष्ठा mii_phy *mii_phy = sis_priv->mii;
	अटल स्थिर पूर्णांक next_tick = 5*HZ;
	पूर्णांक speed = 0, duplex = 0;
	u16 status;

	status = mdio_पढ़ो(net_dev, sis_priv->cur_phy, MII_STATUS);
	status = mdio_पढ़ो(net_dev, sis_priv->cur_phy, MII_STATUS);

	/* Link OFF -> ON */
	अगर (!netअगर_carrier_ok(net_dev)) अणु
	LookForLink:
		/* Search क्रम new PHY */
		status = sis900_शेष_phy(net_dev);
		mii_phy = sis_priv->mii;

		अगर (status & MII_STAT_LINK) अणु
			WARN_ON(!(status & MII_STAT_AUTO_DONE));

			sis900_पढ़ो_mode(net_dev, &speed, &duplex);
			अगर (duplex) अणु
				sis900_set_mode(sis_priv, speed, duplex);
				sis630_set_eq(net_dev, sis_priv->chipset_rev);
				netअगर_carrier_on(net_dev);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
	/* Link ON -> OFF */
                अगर (!(status & MII_STAT_LINK))अणु
                	netअगर_carrier_off(net_dev);
			अगर(netअगर_msg_link(sis_priv))
                		prपूर्णांकk(KERN_INFO "%s: Media Link Off\n", net_dev->name);

                	/* Change mode issue */
                	अगर ((mii_phy->phy_id0 == 0x001D) &&
			    ((mii_phy->phy_id1 & 0xFFF0) == 0x8000))
               			sis900_reset_phy(net_dev,  sis_priv->cur_phy);

			sis630_set_eq(net_dev, sis_priv->chipset_rev);

                	जाओ LookForLink;
                पूर्ण
	पूर्ण

	sis_priv->समयr.expires = jअगरfies + next_tick;
	add_समयr(&sis_priv->समयr);
पूर्ण

/**
 *	sis900_check_mode - check the media mode क्रम sis900
 *	@net_dev: the net device to be checked
 *	@mii_phy: the mii phy
 *
 *	Older driver माला_लो the media mode from mii status output
 *	रेजिस्टर. Now we set our media capability and स्वतः-negotiate
 *	to get the upper bound of speed and duplex between two ends.
 *	If the types of mii phy is HOME, it करोesn't need to स्वतः-negotiate
 *	and स्वतःng_complete should be set to 1.
 */

अटल व्योम sis900_check_mode(काष्ठा net_device *net_dev, काष्ठा mii_phy *mii_phy)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	पूर्णांक speed, duplex;

	अगर (mii_phy->phy_types == LAN) अणु
		sw32(cfg, ~EXD & sr32(cfg));
		sis900_set_capability(net_dev , mii_phy);
		sis900_स्वतः_negotiate(net_dev, sis_priv->cur_phy);
	पूर्ण अन्यथा अणु
		sw32(cfg, EXD | sr32(cfg));
		speed = HW_SPEED_HOME;
		duplex = FDX_CAPABLE_HALF_SELECTED;
		sis900_set_mode(sis_priv, speed, duplex);
		sis_priv->स्वतःng_complete = 1;
	पूर्ण
पूर्ण

/**
 *	sis900_set_mode - Set the media mode of mac रेजिस्टर.
 *	@sp:     the device निजी data
 *	@speed : the transmit speed to be determined
 *	@duplex: the duplex mode to be determined
 *
 *	Set the media mode of mac रेजिस्टर txcfg/rxcfg according to
 *	speed and duplex of phy. Bit EDB_MASTER_EN indicates the EDB
 *	bus is used instead of PCI bus. When this bit is set 1, the
 *	Max DMA Burst Size क्रम TX/RX DMA should be no larger than 16
 *	द्विगुन words.
 */

अटल व्योम sis900_set_mode(काष्ठा sis900_निजी *sp, पूर्णांक speed, पूर्णांक duplex)
अणु
	व्योम __iomem *ioaddr = sp->ioaddr;
	u32 tx_flags = 0, rx_flags = 0;

	अगर (sr32( cfg) & EDB_MASTER_EN) अणु
		tx_flags = TxATP | (DMA_BURST_64 << TxMXDMA_shअगरt) |
					(TX_FILL_THRESH << TxFILLT_shअगरt);
		rx_flags = DMA_BURST_64 << RxMXDMA_shअगरt;
	पूर्ण अन्यथा अणु
		tx_flags = TxATP | (DMA_BURST_512 << TxMXDMA_shअगरt) |
					(TX_FILL_THRESH << TxFILLT_shअगरt);
		rx_flags = DMA_BURST_512 << RxMXDMA_shअगरt;
	पूर्ण

	अगर (speed == HW_SPEED_HOME || speed == HW_SPEED_10_MBPS) अणु
		rx_flags |= (RxDRNT_10 << RxDRNT_shअगरt);
		tx_flags |= (TxDRNT_10 << TxDRNT_shअगरt);
	पूर्ण अन्यथा अणु
		rx_flags |= (RxDRNT_100 << RxDRNT_shअगरt);
		tx_flags |= (TxDRNT_100 << TxDRNT_shअगरt);
	पूर्ण

	अगर (duplex == FDX_CAPABLE_FULL_SELECTED) अणु
		tx_flags |= (TxCSI | TxHBI);
		rx_flags |= RxATX;
	पूर्ण

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
	/* Can accept Jumbo packet */
	rx_flags |= RxAJAB;
#पूर्ण_अगर

	sw32(txcfg, tx_flags);
	sw32(rxcfg, rx_flags);
पूर्ण

/**
 *	sis900_स्वतः_negotiate - Set the Auto-Negotiation Enable/Reset bit.
 *	@net_dev: the net device to पढ़ो mode क्रम
 *	@phy_addr: mii phy address
 *
 *	If the adapter is link-on, set the स्वतः-negotiate enable/reset bit.
 *	स्वतःng_complete should be set to 0 when starting स्वतः-negotiation.
 *	स्वतःng_complete should be set to 1 अगर we didn't start स्वतः-negotiation.
 *	sis900_समयr will रुको क्रम link on again अगर स्वतःng_complete = 0.
 */

अटल व्योम sis900_स्वतः_negotiate(काष्ठा net_device *net_dev, पूर्णांक phy_addr)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	पूर्णांक i = 0;
	u32 status;

	क्रम (i = 0; i < 2; i++)
		status = mdio_पढ़ो(net_dev, phy_addr, MII_STATUS);

	अगर (!(status & MII_STAT_LINK))अणु
		अगर(netअगर_msg_link(sis_priv))
			prपूर्णांकk(KERN_INFO "%s: Media Link Off\n", net_dev->name);
		sis_priv->स्वतःng_complete = 1;
		netअगर_carrier_off(net_dev);
		वापस;
	पूर्ण

	/* (Re)start AutoNegotiate */
	mdio_ग_लिखो(net_dev, phy_addr, MII_CONTROL,
		   MII_CNTL_AUTO | MII_CNTL_RST_AUTO);
	sis_priv->स्वतःng_complete = 0;
पूर्ण


/**
 *	sis900_पढ़ो_mode - पढ़ो media mode क्रम sis900 पूर्णांकernal phy
 *	@net_dev: the net device to पढ़ो mode क्रम
 *	@speed  : the transmit speed to be determined
 *	@duplex : the duplex mode to be determined
 *
 *	The capability of remote end will be put in mii रेजिस्टर स्वतःrec
 *	after स्वतः-negotiation. Use AND operation to get the upper bound
 *	of speed and duplex between two ends.
 */

अटल व्योम sis900_पढ़ो_mode(काष्ठा net_device *net_dev, पूर्णांक *speed, पूर्णांक *duplex)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	काष्ठा mii_phy *phy = sis_priv->mii;
	पूर्णांक phy_addr = sis_priv->cur_phy;
	u32 status;
	u16 स्वतःadv, स्वतःrec;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		status = mdio_पढ़ो(net_dev, phy_addr, MII_STATUS);

	अगर (!(status & MII_STAT_LINK))
		वापस;

	/* AutoNegotiate completed */
	स्वतःadv = mdio_पढ़ो(net_dev, phy_addr, MII_ANADV);
	स्वतःrec = mdio_पढ़ो(net_dev, phy_addr, MII_ANLPAR);
	status = स्वतःadv & स्वतःrec;

	*speed = HW_SPEED_10_MBPS;
	*duplex = FDX_CAPABLE_HALF_SELECTED;

	अगर (status & (MII_NWAY_TX | MII_NWAY_TX_FDX))
		*speed = HW_SPEED_100_MBPS;
	अगर (status & ( MII_NWAY_TX_FDX | MII_NWAY_T_FDX))
		*duplex = FDX_CAPABLE_FULL_SELECTED;

	sis_priv->स्वतःng_complete = 1;

	/* Workaround क्रम Realtek RTL8201 PHY issue */
	अगर ((phy->phy_id0 == 0x0000) && ((phy->phy_id1 & 0xFFF0) == 0x8200)) अणु
		अगर (mdio_पढ़ो(net_dev, phy_addr, MII_CONTROL) & MII_CNTL_FDX)
			*duplex = FDX_CAPABLE_FULL_SELECTED;
		अगर (mdio_पढ़ो(net_dev, phy_addr, 0x0019) & 0x01)
			*speed = HW_SPEED_100_MBPS;
	पूर्ण

	अगर(netअगर_msg_link(sis_priv))
		prपूर्णांकk(KERN_INFO "%s: Media Link On %s %s-duplex\n",
	       				net_dev->name,
	       				*speed == HW_SPEED_100_MBPS ?
	       					"100mbps" : "10mbps",
	       				*duplex == FDX_CAPABLE_FULL_SELECTED ?
	       					"full" : "half");
पूर्ण

/**
 *	sis900_tx_समयout - sis900 transmit समयout routine
 *	@net_dev: the net device to transmit
 *	@txqueue: index of hanging queue
 *
 *	prपूर्णांक transmit समयout status
 *	disable पूर्णांकerrupts and करो some tasks
 */

अटल व्योम sis900_tx_समयout(काष्ठा net_device *net_dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (netअगर_msg_tx_err(sis_priv)) अणु
		prपूर्णांकk(KERN_INFO "%s: Transmit timeout, status %8.8x %8.8x\n",
			net_dev->name, sr32(cr), sr32(isr));
	पूर्ण

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	sw32(imr, 0x0000);

	/* use spinlock to prevent पूर्णांकerrupt handler accessing buffer ring */
	spin_lock_irqsave(&sis_priv->lock, flags);

	/* discard unsent packets */
	sis_priv->dirty_tx = sis_priv->cur_tx = 0;
	क्रम (i = 0; i < NUM_TX_DESC; i++) अणु
		काष्ठा sk_buff *skb = sis_priv->tx_skbuff[i];

		अगर (skb) अणु
			dma_unmap_single(&sis_priv->pci_dev->dev,
					 sis_priv->tx_ring[i].bufptr,
					 skb->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb_irq(skb);
			sis_priv->tx_skbuff[i] = शून्य;
			sis_priv->tx_ring[i].cmdsts = 0;
			sis_priv->tx_ring[i].bufptr = 0;
			net_dev->stats.tx_dropped++;
		पूर्ण
	पूर्ण
	sis_priv->tx_full = 0;
	netअगर_wake_queue(net_dev);

	spin_unlock_irqrestore(&sis_priv->lock, flags);

	netअगर_trans_update(net_dev); /* prevent tx समयout */

	/* load Transmit Descriptor Register */
	sw32(txdp, sis_priv->tx_ring_dma);

	/* Enable all known पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	sw32(imr, RxSOVR | RxORN | RxERR | RxOK | TxURN | TxERR | TxDESC);
पूर्ण

/**
 *	sis900_start_xmit - sis900 start transmit routine
 *	@skb: socket buffer poपूर्णांकer to put the data being transmitted
 *	@net_dev: the net device to transmit with
 *
 *	Set the transmit buffer descriptor,
 *	and ग_लिखो TxENA to enable transmit state machine.
 *	tell upper layer अगर the buffer is full
 */

अटल netdev_tx_t
sis900_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	अचिन्हित पूर्णांक  entry;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक  index_cur_tx, index_dirty_tx;
	अचिन्हित पूर्णांक  count_dirty_tx;

	spin_lock_irqsave(&sis_priv->lock, flags);

	/* Calculate the next Tx descriptor entry. */
	entry = sis_priv->cur_tx % NUM_TX_DESC;
	sis_priv->tx_skbuff[entry] = skb;

	/* set the transmit buffer descriptor and enable Transmit State Machine */
	sis_priv->tx_ring[entry].bufptr = dma_map_single(&sis_priv->pci_dev->dev,
							 skb->data, skb->len,
							 DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(&sis_priv->pci_dev->dev,
				       sis_priv->tx_ring[entry].bufptr))) अणु
			dev_kमुक्त_skb_any(skb);
			sis_priv->tx_skbuff[entry] = शून्य;
			net_dev->stats.tx_dropped++;
			spin_unlock_irqrestore(&sis_priv->lock, flags);
			वापस NETDEV_TX_OK;
	पूर्ण
	sis_priv->tx_ring[entry].cmdsts = (OWN | INTR | skb->len);
	sw32(cr, TxENA | sr32(cr));

	sis_priv->cur_tx ++;
	index_cur_tx = sis_priv->cur_tx;
	index_dirty_tx = sis_priv->dirty_tx;

	क्रम (count_dirty_tx = 0; index_cur_tx != index_dirty_tx; index_dirty_tx++)
		count_dirty_tx ++;

	अगर (index_cur_tx == index_dirty_tx) अणु
		/* dirty_tx is met in the cycle of cur_tx, buffer full */
		sis_priv->tx_full = 1;
		netअगर_stop_queue(net_dev);
	पूर्ण अन्यथा अगर (count_dirty_tx < NUM_TX_DESC) अणु
		/* Typical path, tell upper layer that more transmission is possible */
		netअगर_start_queue(net_dev);
	पूर्ण अन्यथा अणु
		/* buffer full, tell upper layer no more transmission */
		sis_priv->tx_full = 1;
		netअगर_stop_queue(net_dev);
	पूर्ण

	spin_unlock_irqrestore(&sis_priv->lock, flags);

	अगर (netअगर_msg_tx_queued(sis_priv))
		prपूर्णांकk(KERN_DEBUG "%s: Queued Tx packet at %p size %d "
		       "to slot %d.\n",
		       net_dev->name, skb->data, (पूर्णांक)skb->len, entry);

	वापस NETDEV_TX_OK;
पूर्ण

/**
 *	sis900_पूर्णांकerrupt - sis900 पूर्णांकerrupt handler
 *	@irq: the irq number
 *	@dev_instance: the client data object
 *
 *	The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work,
 *	and cleans up after the Tx thपढ़ो
 */

अटल irqवापस_t sis900_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *net_dev = dev_instance;
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	पूर्णांक boguscnt = max_पूर्णांकerrupt_work;
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	u32 status;
	अचिन्हित पूर्णांक handled = 0;

	spin_lock (&sis_priv->lock);

	करो अणु
		status = sr32(isr);

		अगर ((status & (HIBERR|TxURN|TxERR|TxDESC|RxORN|RxERR|RxOK)) == 0)
			/* nothing पूर्णांकeresting happened */
			अवरोध;
		handled = 1;

		/* why करोw't we अवरोध after Tx/Rx हाल ?? keyword: full-duplex */
		अगर (status & (RxORN | RxERR | RxOK))
			/* Rx पूर्णांकerrupt */
			sis900_rx(net_dev);

		अगर (status & (TxURN | TxERR | TxDESC))
			/* Tx पूर्णांकerrupt */
			sis900_finish_xmit(net_dev);

		/* something strange happened !!! */
		अगर (status & HIBERR) अणु
			अगर(netअगर_msg_पूर्णांकr(sis_priv))
				prपूर्णांकk(KERN_INFO "%s: Abnormal interrupt, "
					"status %#8.8x.\n", net_dev->name, status);
			अवरोध;
		पूर्ण
		अगर (--boguscnt < 0) अणु
			अगर(netअगर_msg_पूर्णांकr(sis_priv))
				prपूर्णांकk(KERN_INFO "%s: Too much work at interrupt, "
					"interrupt status = %#8.8x.\n",
					net_dev->name, status);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	अगर(netअगर_msg_पूर्णांकr(sis_priv))
		prपूर्णांकk(KERN_DEBUG "%s: exiting interrupt, "
		       "interrupt status = %#8.8x\n",
		       net_dev->name, sr32(isr));

	spin_unlock (&sis_priv->lock);
	वापस IRQ_RETVAL(handled);
पूर्ण

/**
 *	sis900_rx - sis900 receive routine
 *	@net_dev: the net device which receives data
 *
 *	Process receive पूर्णांकerrupt events,
 *	put buffer to higher layer and refill buffer pool
 *	Note: This function is called by पूर्णांकerrupt handler,
 *	करोn't करो "too much" work here
 */

अटल पूर्णांक sis900_rx(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	अचिन्हित पूर्णांक entry = sis_priv->cur_rx % NUM_RX_DESC;
	u32 rx_status = sis_priv->rx_ring[entry].cmdsts;
	पूर्णांक rx_work_limit;

	अगर (netअगर_msg_rx_status(sis_priv))
		prपूर्णांकk(KERN_DEBUG "sis900_rx, cur_rx:%4.4d, dirty_rx:%4.4d "
		       "status:0x%8.8x\n",
		       sis_priv->cur_rx, sis_priv->dirty_rx, rx_status);
	rx_work_limit = sis_priv->dirty_rx + NUM_RX_DESC - sis_priv->cur_rx;

	जबतक (rx_status & OWN) अणु
		अचिन्हित पूर्णांक rx_size;
		अचिन्हित पूर्णांक data_size;

		अगर (--rx_work_limit < 0)
			अवरोध;

		data_size = rx_status & DSIZE;
		rx_size = data_size - CRC_SIZE;

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
		/* ``TOOLONG'' flag means jumbo packet received. */
		अगर ((rx_status & TOOLONG) && data_size <= MAX_FRAME_SIZE)
			rx_status &= (~ ((अचिन्हित पूर्णांक)TOOLONG));
#पूर्ण_अगर

		अगर (rx_status & (ABORT|OVERRUN|TOOLONG|RUNT|RXISERR|CRCERR|FAERR)) अणु
			/* corrupted packet received */
			अगर (netअगर_msg_rx_err(sis_priv))
				prपूर्णांकk(KERN_DEBUG "%s: Corrupted packet "
				       "received, buffer status = 0x%8.8x/%d.\n",
				       net_dev->name, rx_status, data_size);
			net_dev->stats.rx_errors++;
			अगर (rx_status & OVERRUN)
				net_dev->stats.rx_over_errors++;
			अगर (rx_status & (TOOLONG|RUNT))
				net_dev->stats.rx_length_errors++;
			अगर (rx_status & (RXISERR | FAERR))
				net_dev->stats.rx_frame_errors++;
			अगर (rx_status & CRCERR)
				net_dev->stats.rx_crc_errors++;
			/* reset buffer descriptor state */
			sis_priv->rx_ring[entry].cmdsts = RX_BUF_SIZE;
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff * skb;
			काष्ठा sk_buff * rx_skb;

			dma_unmap_single(&sis_priv->pci_dev->dev,
					 sis_priv->rx_ring[entry].bufptr,
					 RX_BUF_SIZE, DMA_FROM_DEVICE);

			/* refill the Rx buffer, what अगर there is not enough
			 * memory क्रम new socket buffer ?? */
			अगर ((skb = netdev_alloc_skb(net_dev, RX_BUF_SIZE)) == शून्य) अणु
				/*
				 * Not enough memory to refill the buffer
				 * so we need to recycle the old one so
				 * as to aव्योम creating a memory hole
				 * in the rx ring
				 */
				skb = sis_priv->rx_skbuff[entry];
				net_dev->stats.rx_dropped++;
				जाओ refill_rx_ring;
			पूर्ण

			/* This situation should never happen, but due to
			   some unknown bugs, it is possible that
			   we are working on शून्य sk_buff :-( */
			अगर (sis_priv->rx_skbuff[entry] == शून्य) अणु
				अगर (netअगर_msg_rx_err(sis_priv))
					prपूर्णांकk(KERN_WARNING "%s: NULL pointer "
					      "encountered in Rx ring\n"
					      "cur_rx:%4.4d, dirty_rx:%4.4d\n",
					      net_dev->name, sis_priv->cur_rx,
					      sis_priv->dirty_rx);
				dev_kमुक्त_skb(skb);
				अवरोध;
			पूर्ण

			/* give the socket buffer to upper layers */
			rx_skb = sis_priv->rx_skbuff[entry];
			skb_put(rx_skb, rx_size);
			rx_skb->protocol = eth_type_trans(rx_skb, net_dev);
			netअगर_rx(rx_skb);

			/* some network statistics */
			अगर ((rx_status & BCAST) == MCAST)
				net_dev->stats.multicast++;
			net_dev->stats.rx_bytes += rx_size;
			net_dev->stats.rx_packets++;
			sis_priv->dirty_rx++;
refill_rx_ring:
			sis_priv->rx_skbuff[entry] = skb;
			sis_priv->rx_ring[entry].cmdsts = RX_BUF_SIZE;
			sis_priv->rx_ring[entry].bufptr =
				dma_map_single(&sis_priv->pci_dev->dev,
					       skb->data, RX_BUF_SIZE,
					       DMA_FROM_DEVICE);
			अगर (unlikely(dma_mapping_error(&sis_priv->pci_dev->dev,
						       sis_priv->rx_ring[entry].bufptr))) अणु
				dev_kमुक्त_skb_irq(skb);
				sis_priv->rx_skbuff[entry] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		sis_priv->cur_rx++;
		entry = sis_priv->cur_rx % NUM_RX_DESC;
		rx_status = sis_priv->rx_ring[entry].cmdsts;
	पूर्ण // जबतक

	/* refill the Rx buffer, what अगर the rate of refilling is slower
	 * than consuming ?? */
	क्रम (; sis_priv->cur_rx != sis_priv->dirty_rx; sis_priv->dirty_rx++) अणु
		काष्ठा sk_buff *skb;

		entry = sis_priv->dirty_rx % NUM_RX_DESC;

		अगर (sis_priv->rx_skbuff[entry] == शून्य) अणु
			skb = netdev_alloc_skb(net_dev, RX_BUF_SIZE);
			अगर (skb == शून्य) अणु
				/* not enough memory क्रम skbuff, this makes a
				 * "hole" on the buffer ring, it is not clear
				 * how the hardware will react to this kind
				 * of degenerated buffer */
				net_dev->stats.rx_dropped++;
				अवरोध;
			पूर्ण
			sis_priv->rx_skbuff[entry] = skb;
			sis_priv->rx_ring[entry].cmdsts = RX_BUF_SIZE;
			sis_priv->rx_ring[entry].bufptr =
				dma_map_single(&sis_priv->pci_dev->dev,
					       skb->data, RX_BUF_SIZE,
					       DMA_FROM_DEVICE);
			अगर (unlikely(dma_mapping_error(&sis_priv->pci_dev->dev,
						       sis_priv->rx_ring[entry].bufptr))) अणु
				dev_kमुक्त_skb_irq(skb);
				sis_priv->rx_skbuff[entry] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/* re-enable the potentially idle receive state matchine */
	sw32(cr , RxENA | sr32(cr));

	वापस 0;
पूर्ण

/**
 *	sis900_finish_xmit - finish up transmission of packets
 *	@net_dev: the net device to be transmitted on
 *
 *	Check क्रम error condition and मुक्त socket buffer etc
 *	schedule क्रम more transmission as needed
 *	Note: This function is called by पूर्णांकerrupt handler,
 *	करोn't करो "too much" work here
 */

अटल व्योम sis900_finish_xmit (काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);

	क्रम (; sis_priv->dirty_tx != sis_priv->cur_tx; sis_priv->dirty_tx++) अणु
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक entry;
		u32 tx_status;

		entry = sis_priv->dirty_tx % NUM_TX_DESC;
		tx_status = sis_priv->tx_ring[entry].cmdsts;

		अगर (tx_status & OWN) अणु
			/* The packet is not transmitted yet (owned by hardware) !
			 * Note: this is an almost impossible condition
			 * on TxDESC पूर्णांकerrupt ('descriptor interrupt') */
			अवरोध;
		पूर्ण

		अगर (tx_status & (ABORT | UNDERRUN | OWCOLL)) अणु
			/* packet unsuccessfully transmitted */
			अगर (netअगर_msg_tx_err(sis_priv))
				prपूर्णांकk(KERN_DEBUG "%s: Transmit "
				       "error, Tx status %8.8x.\n",
				       net_dev->name, tx_status);
			net_dev->stats.tx_errors++;
			अगर (tx_status & UNDERRUN)
				net_dev->stats.tx_fअगरo_errors++;
			अगर (tx_status & ABORT)
				net_dev->stats.tx_पातed_errors++;
			अगर (tx_status & NOCARRIER)
				net_dev->stats.tx_carrier_errors++;
			अगर (tx_status & OWCOLL)
				net_dev->stats.tx_winकरोw_errors++;
		पूर्ण अन्यथा अणु
			/* packet successfully transmitted */
			net_dev->stats.collisions += (tx_status & COLCNT) >> 16;
			net_dev->stats.tx_bytes += tx_status & DSIZE;
			net_dev->stats.tx_packets++;
		पूर्ण
		/* Free the original skb. */
		skb = sis_priv->tx_skbuff[entry];
		dma_unmap_single(&sis_priv->pci_dev->dev,
				 sis_priv->tx_ring[entry].bufptr, skb->len,
				 DMA_TO_DEVICE);
		dev_consume_skb_irq(skb);
		sis_priv->tx_skbuff[entry] = शून्य;
		sis_priv->tx_ring[entry].bufptr = 0;
		sis_priv->tx_ring[entry].cmdsts = 0;
	पूर्ण

	अगर (sis_priv->tx_full && netअगर_queue_stopped(net_dev) &&
	    sis_priv->cur_tx - sis_priv->dirty_tx < NUM_TX_DESC - 4) अणु
		/* The ring is no दीर्घer full, clear tx_full and schedule
		 * more transmission by netअगर_wake_queue(net_dev) */
		sis_priv->tx_full = 0;
		netअगर_wake_queue (net_dev);
	पूर्ण
पूर्ण

/**
 *	sis900_बंद - बंद sis900 device
 *	@net_dev: the net device to be बंदd
 *
 *	Disable पूर्णांकerrupts, stop the Tx and Rx Status Machine
 *	मुक्त Tx and RX socket buffer
 */

अटल पूर्णांक sis900_बंद(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	काष्ठा pci_dev *pdev = sis_priv->pci_dev;
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	netअगर_stop_queue(net_dev);

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	sw32(imr, 0x0000);
	sw32(ier, 0x0000);

	/* Stop the chip's Tx and Rx Status Machine */
	sw32(cr, RxDIS | TxDIS | sr32(cr));

	del_समयr(&sis_priv->समयr);

	मुक्त_irq(pdev->irq, net_dev);

	/* Free Tx and RX skbuff */
	क्रम (i = 0; i < NUM_RX_DESC; i++) अणु
		skb = sis_priv->rx_skbuff[i];
		अगर (skb) अणु
			dma_unmap_single(&pdev->dev,
					 sis_priv->rx_ring[i].bufptr,
					 RX_BUF_SIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(skb);
			sis_priv->rx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < NUM_TX_DESC; i++) अणु
		skb = sis_priv->tx_skbuff[i];
		अगर (skb) अणु
			dma_unmap_single(&pdev->dev,
					 sis_priv->tx_ring[i].bufptr,
					 skb->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb(skb);
			sis_priv->tx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण

	/* Green! Put the chip in low-घातer mode. */

	वापस 0;
पूर्ण

/**
 *	sis900_get_drvinfo - Return inक्रमmation about driver
 *	@net_dev: the net device to probe
 *	@info: container क्रम info वापसed
 *
 *	Process ethtool command such as "ehtool -i" to show inक्रमmation
 */

अटल व्योम sis900_get_drvinfo(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);

	strlcpy(info->driver, SIS900_MODULE_NAME, माप(info->driver));
	strlcpy(info->version, SIS900_DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(sis_priv->pci_dev),
		माप(info->bus_info));
पूर्ण

अटल u32 sis900_get_msglevel(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	वापस sis_priv->msg_enable;
पूर्ण

अटल व्योम sis900_set_msglevel(काष्ठा net_device *net_dev, u32 value)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	sis_priv->msg_enable = value;
पूर्ण

अटल u32 sis900_get_link(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	वापस mii_link_ok(&sis_priv->mii_info);
पूर्ण

अटल पूर्णांक sis900_get_link_ksettings(काष्ठा net_device *net_dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	spin_lock_irq(&sis_priv->lock);
	mii_ethtool_get_link_ksettings(&sis_priv->mii_info, cmd);
	spin_unlock_irq(&sis_priv->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक sis900_set_link_ksettings(काष्ठा net_device *net_dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	पूर्णांक rt;
	spin_lock_irq(&sis_priv->lock);
	rt = mii_ethtool_set_link_ksettings(&sis_priv->mii_info, cmd);
	spin_unlock_irq(&sis_priv->lock);
	वापस rt;
पूर्ण

अटल पूर्णांक sis900_nway_reset(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	वापस mii_nway_restart(&sis_priv->mii_info);
पूर्ण

/**
 *	sis900_set_wol - Set up Wake on Lan रेजिस्टरs
 *	@net_dev: the net device to probe
 *	@wol: container क्रम info passed to the driver
 *
 *	Process ethtool command "wol" to setup wake on lan features.
 *	SiS900 supports sending WoL events अगर a correct packet is received,
 *	but there is no simple way to filter them to only a subset (broadcast,
 *	multicast, unicast or arp).
 */

अटल पूर्णांक sis900_set_wol(काष्ठा net_device *net_dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	u32 cfgpmcsr = 0, pmctrl_bits = 0;

	अगर (wol->wolopts == 0) अणु
		pci_पढ़ो_config_dword(sis_priv->pci_dev, CFGPMCSR, &cfgpmcsr);
		cfgpmcsr &= ~PME_EN;
		pci_ग_लिखो_config_dword(sis_priv->pci_dev, CFGPMCSR, cfgpmcsr);
		sw32(pmctrl, pmctrl_bits);
		अगर (netअगर_msg_wol(sis_priv))
			prपूर्णांकk(KERN_DEBUG "%s: Wake on LAN disabled\n", net_dev->name);
		वापस 0;
	पूर्ण

	अगर (wol->wolopts & (WAKE_MAGICSECURE | WAKE_UCAST | WAKE_MCAST
				| WAKE_BCAST | WAKE_ARP))
		वापस -EINVAL;

	अगर (wol->wolopts & WAKE_MAGIC)
		pmctrl_bits |= MAGICPKT;
	अगर (wol->wolopts & WAKE_PHY)
		pmctrl_bits |= LINKON;

	sw32(pmctrl, pmctrl_bits);

	pci_पढ़ो_config_dword(sis_priv->pci_dev, CFGPMCSR, &cfgpmcsr);
	cfgpmcsr |= PME_EN;
	pci_ग_लिखो_config_dword(sis_priv->pci_dev, CFGPMCSR, cfgpmcsr);
	अगर (netअगर_msg_wol(sis_priv))
		prपूर्णांकk(KERN_DEBUG "%s: Wake on LAN enabled\n", net_dev->name);

	वापस 0;
पूर्ण

अटल व्योम sis900_get_wol(काष्ठा net_device *net_dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा sis900_निजी *sp = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sp->ioaddr;
	u32 pmctrl_bits;

	pmctrl_bits = sr32(pmctrl);
	अगर (pmctrl_bits & MAGICPKT)
		wol->wolopts |= WAKE_MAGIC;
	अगर (pmctrl_bits & LINKON)
		wol->wolopts |= WAKE_PHY;

	wol->supported = (WAKE_PHY | WAKE_MAGIC);
पूर्ण

अटल पूर्णांक sis900_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(dev);

	वापस sis_priv->eeprom_size;
पूर्ण

अटल पूर्णांक sis900_पढ़ो_eeprom(काष्ठा net_device *net_dev, u8 *buf)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	पूर्णांक रुको, ret = -EAGAIN;
	u16 signature;
	u16 *ebuf = (u16 *)buf;
	पूर्णांक i;

	अगर (sis_priv->chipset_rev == SIS96x_900_REV) अणु
		sw32(mear, EEREQ);
		क्रम (रुको = 0; रुको < 2000; रुको++) अणु
			अगर (sr32(mear) & EEGNT) अणु
				/* पढ़ो 16 bits, and index by 16 bits */
				क्रम (i = 0; i < sis_priv->eeprom_size / 2; i++)
					ebuf[i] = (u16)पढ़ो_eeprom(ioaddr, i);
				ret = 0;
				अवरोध;
			पूर्ण
			udelay(1);
		पूर्ण
		sw32(mear, EEDONE);
	पूर्ण अन्यथा अणु
		signature = (u16)पढ़ो_eeprom(ioaddr, EEPROMSignature);
		अगर (signature != 0xffff && signature != 0x0000) अणु
			/* पढ़ो 16 bits, and index by 16 bits */
			क्रम (i = 0; i < sis_priv->eeprom_size / 2; i++)
				ebuf[i] = (u16)पढ़ो_eeprom(ioaddr, i);
			ret = 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा SIS900_EEPROM_MAGIC	0xBABE
अटल पूर्णांक sis900_get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(dev);
	u8 *eebuf;
	पूर्णांक res;

	eebuf = kदो_स्मृति(sis_priv->eeprom_size, GFP_KERNEL);
	अगर (!eebuf)
		वापस -ENOMEM;

	eeprom->magic = SIS900_EEPROM_MAGIC;
	spin_lock_irq(&sis_priv->lock);
	res = sis900_पढ़ो_eeprom(dev, eebuf);
	spin_unlock_irq(&sis_priv->lock);
	अगर (!res)
		स_नकल(data, eebuf + eeprom->offset, eeprom->len);
	kमुक्त(eebuf);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sis900_ethtool_ops = अणु
	.get_drvinfo 	= sis900_get_drvinfo,
	.get_msglevel	= sis900_get_msglevel,
	.set_msglevel	= sis900_set_msglevel,
	.get_link	= sis900_get_link,
	.nway_reset	= sis900_nway_reset,
	.get_wol	= sis900_get_wol,
	.set_wol	= sis900_set_wol,
	.get_link_ksettings = sis900_get_link_ksettings,
	.set_link_ksettings = sis900_set_link_ksettings,
	.get_eeprom_len = sis900_get_eeprom_len,
	.get_eeprom = sis900_get_eeprom,
पूर्ण;

/**
 *	mii_ioctl - process MII i/o control command
 *	@net_dev: the net device to command क्रम
 *	@rq: parameter क्रम command
 *	@cmd: the i/o command
 *
 *	Process MII command like पढ़ो/ग_लिखो MII रेजिस्टर
 */

अटल पूर्णांक mii_ioctl(काष्ठा net_device *net_dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);

	चयन(cmd) अणु
	हाल SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = sis_priv->mii->phy_addr;
		fallthrough;

	हाल SIOCGMIIREG:		/* Read MII PHY रेजिस्टर. */
		data->val_out = mdio_पढ़ो(net_dev, data->phy_id & 0x1f, data->reg_num & 0x1f);
		वापस 0;

	हाल SIOCSMIIREG:		/* Write MII PHY रेजिस्टर. */
		mdio_ग_लिखो(net_dev, data->phy_id & 0x1f, data->reg_num & 0x1f, data->val_in);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 *	sis900_set_config - Set media type by net_device.set_config
 *	@dev: the net device क्रम media type change
 *	@map: अगरmap passed by अगरconfig
 *
 *	Set media type to 10baseT, 100baseT or 0(क्रम स्वतः) by अगरconfig
 *	we support only port changes. All other runसमय configuration
 *	changes will be ignored
 */

अटल पूर्णांक sis900_set_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(dev);
	काष्ठा mii_phy *mii_phy = sis_priv->mii;

	u16 status;

	अगर ((map->port != (u_अक्षर)(-1)) && (map->port != dev->अगर_port)) अणु
		/* we चयन on the अगरmap->port field. I couldn't find anything
		 * like a definition or standard क्रम the values of that field.
		 * I think the meaning of those values is device specअगरic. But
		 * since I would like to change the media type via the अगरconfig
		 * command I use the definition from linux/netdevice.h
		 * (which seems to be dअगरferent from the अगरport(pcmcia) definition) */
		चयन(map->port)अणु
		हाल IF_PORT_UNKNOWN: /* use स्वतः here */
			dev->अगर_port = map->port;
			/* we are going to change the media type, so the Link
			 * will be temporary करोwn and we need to reflect that
			 * here. When the Link comes up again, it will be
			 * sensed by the sis_समयr procedure, which also करोes
			 * all the rest क्रम us */
			netअगर_carrier_off(dev);

			/* पढ़ो current state */
			status = mdio_पढ़ो(dev, mii_phy->phy_addr, MII_CONTROL);

			/* enable स्वतः negotiation and reset the negotioation
			 * (I करोn't really know what the स्वतः negatiotiation
			 * reset really means, but it sounds क्रम me right to
			 * करो one here) */
			mdio_ग_लिखो(dev, mii_phy->phy_addr,
				   MII_CONTROL, status | MII_CNTL_AUTO | MII_CNTL_RST_AUTO);

			अवरोध;

		हाल IF_PORT_10BASET: /* 10BaseT */
			dev->अगर_port = map->port;

			/* we are going to change the media type, so the Link
			 * will be temporary करोwn and we need to reflect that
			 * here. When the Link comes up again, it will be
			 * sensed by the sis_समयr procedure, which also करोes
			 * all the rest क्रम us */
			netअगर_carrier_off(dev);

			/* set Speed to 10Mbps */
			/* पढ़ो current state */
			status = mdio_पढ़ो(dev, mii_phy->phy_addr, MII_CONTROL);

			/* disable स्वतः negotiation and क्रमce 10MBit mode*/
			mdio_ग_लिखो(dev, mii_phy->phy_addr,
				   MII_CONTROL, status & ~(MII_CNTL_SPEED |
					MII_CNTL_AUTO));
			अवरोध;

		हाल IF_PORT_100BASET: /* 100BaseT */
		हाल IF_PORT_100BASETX: /* 100BaseTx */
			dev->अगर_port = map->port;

			/* we are going to change the media type, so the Link
			 * will be temporary करोwn and we need to reflect that
			 * here. When the Link comes up again, it will be
			 * sensed by the sis_समयr procedure, which also करोes
			 * all the rest क्रम us */
			netअगर_carrier_off(dev);

			/* set Speed to 100Mbps */
			/* disable स्वतः negotiation and enable 100MBit Mode */
			status = mdio_पढ़ो(dev, mii_phy->phy_addr, MII_CONTROL);
			mdio_ग_लिखो(dev, mii_phy->phy_addr,
				   MII_CONTROL, (status & ~MII_CNTL_SPEED) |
				   MII_CNTL_SPEED);

			अवरोध;

		हाल IF_PORT_10BASE2: /* 10Base2 */
		हाल IF_PORT_AUI: /* AUI */
		हाल IF_PORT_100BASEFX: /* 100BaseFx */
                	/* These Modes are not supported (are they?)*/
			वापस -EOPNOTSUPP;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	sis900_mcast_bitnr - compute hashtable index
 *	@addr: multicast address
 *	@revision: revision id of chip
 *
 *	SiS 900 uses the most sigअगरicant 7 bits to index a 128 bits multicast
 *	hash table, which makes this function a little bit dअगरferent from other drivers
 *	SiS 900 B0 & 635 M/B uses the most signअगरicat 8 bits to index 256 bits
 *   	multicast hash table.
 */

अटल अंतरभूत u16 sis900_mcast_bitnr(u8 *addr, u8 revision)
अणु

	u32 crc = ether_crc(6, addr);

	/* leave 8 or 7 most siginअगरant bits */
	अगर ((revision >= SIS635A_900_REV) || (revision == SIS900B_900_REV))
		वापस (पूर्णांक)(crc >> 24);
	अन्यथा
		वापस (पूर्णांक)(crc >> 25);
पूर्ण

/**
 *	set_rx_mode - Set SiS900 receive mode
 *	@net_dev: the net device to be set
 *
 *	Set SiS900 receive mode क्रम promiscuous, multicast, or broadcast mode.
 *	And set the appropriate multicast filter.
 *	Multicast hash table changes from 128 to 256 bits क्रम 635M/B & 900B0.
 */

अटल व्योम set_rx_mode(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	u16 mc_filter[16] = अणु0पूर्ण;	/* 256/128 bits multicast hash table */
	पूर्णांक i, table_entries;
	u32 rx_mode;

	/* 635 Hash Table entries = 256(2^16) */
	अगर((sis_priv->chipset_rev >= SIS635A_900_REV) ||
			(sis_priv->chipset_rev == SIS900B_900_REV))
		table_entries = 16;
	अन्यथा
		table_entries = 8;

	अगर (net_dev->flags & IFF_PROMISC) अणु
		/* Accept any kinds of packets */
		rx_mode = RFPromiscuous;
		क्रम (i = 0; i < table_entries; i++)
			mc_filter[i] = 0xffff;
	पूर्ण अन्यथा अगर ((netdev_mc_count(net_dev) > multicast_filter_limit) ||
		   (net_dev->flags & IFF_ALLMULTI)) अणु
		/* too many multicast addresses or accept all multicast packet */
		rx_mode = RFAAB | RFAAM;
		क्रम (i = 0; i < table_entries; i++)
			mc_filter[i] = 0xffff;
	पूर्ण अन्यथा अणु
		/* Accept Broadcast packet, destination address matchs our
		 * MAC address, use Receive Filter to reject unwanted MCAST
		 * packets */
		काष्ठा netdev_hw_addr *ha;
		rx_mode = RFAAB;

		netdev_क्रम_each_mc_addr(ha, net_dev) अणु
			अचिन्हित पूर्णांक bit_nr;

			bit_nr = sis900_mcast_bitnr(ha->addr,
						    sis_priv->chipset_rev);
			mc_filter[bit_nr >> 4] |= (1 << (bit_nr & 0xf));
		पूर्ण
	पूर्ण

	/* update Multicast Hash Table in Receive Filter */
	क्रम (i = 0; i < table_entries; i++) अणु
                /* why plus 0x04 ??, That makes the correct value क्रम hash table. */
		sw32(rfcr, (u32)(0x00000004 + i) << RFADDR_shअगरt);
		sw32(rfdr, mc_filter[i]);
	पूर्ण

	sw32(rfcr, RFEN | rx_mode);

	/* sis900 is capable of looping back packets at MAC level क्रम
	 * debugging purpose */
	अगर (net_dev->flags & IFF_LOOPBACK) अणु
		u32 cr_saved;
		/* We must disable Tx/Rx beक्रमe setting loopback mode */
		cr_saved = sr32(cr);
		sw32(cr, cr_saved | TxDIS | RxDIS);
		/* enable loopback */
		sw32(txcfg, sr32(txcfg) | TxMLB);
		sw32(rxcfg, sr32(rxcfg) | RxATX);
		/* restore cr */
		sw32(cr, cr_saved);
	पूर्ण
पूर्ण

/**
 *	sis900_reset - Reset sis900 MAC
 *	@net_dev: the net device to reset
 *
 *	reset sis900 MAC and रुको until finished
 *	reset through command रेजिस्टर
 *	change backoff algorithm क्रम 900B0 & 635 M/B
 */

अटल व्योम sis900_reset(काष्ठा net_device *net_dev)
अणु
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;
	u32 status = TxRCMP | RxRCMP;
	पूर्णांक i;

	sw32(ier, 0);
	sw32(imr, 0);
	sw32(rfcr, 0);

	sw32(cr, RxRESET | TxRESET | RESET | sr32(cr));

	/* Check that the chip has finished the reset. */
	क्रम (i = 0; status && (i < 1000); i++)
		status ^= sr32(isr) & status;

	अगर (sis_priv->chipset_rev >= SIS635A_900_REV ||
	    sis_priv->chipset_rev == SIS900B_900_REV)
		sw32(cfg, PESEL | RND_CNT);
	अन्यथा
		sw32(cfg, PESEL);
पूर्ण

/**
 *	sis900_हटाओ - Remove sis900 device
 *	@pci_dev: the pci device to be हटाओd
 *
 *	हटाओ and release SiS900 net device
 */

अटल व्योम sis900_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा net_device *net_dev = pci_get_drvdata(pci_dev);
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);

	unरेजिस्टर_netdev(net_dev);

	जबतक (sis_priv->first_mii) अणु
		काष्ठा mii_phy *phy = sis_priv->first_mii;

		sis_priv->first_mii = phy->next;
		kमुक्त(phy);
	पूर्ण

	dma_मुक्त_coherent(&pci_dev->dev, RX_TOTAL_SIZE, sis_priv->rx_ring,
			  sis_priv->rx_ring_dma);
	dma_मुक्त_coherent(&pci_dev->dev, TX_TOTAL_SIZE, sis_priv->tx_ring,
			  sis_priv->tx_ring_dma);
	pci_iounmap(pci_dev, sis_priv->ioaddr);
	मुक्त_netdev(net_dev);
	pci_release_regions(pci_dev);
पूर्ण

अटल पूर्णांक __maybe_unused sis900_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *net_dev = dev_get_drvdata(dev);
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;

	अगर(!netअगर_running(net_dev))
		वापस 0;

	netअगर_stop_queue(net_dev);
	netअगर_device_detach(net_dev);

	/* Stop the chip's Tx and Rx Status Machine */
	sw32(cr, RxDIS | TxDIS | sr32(cr));

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sis900_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *net_dev = dev_get_drvdata(dev);
	काष्ठा sis900_निजी *sis_priv = netdev_priv(net_dev);
	व्योम __iomem *ioaddr = sis_priv->ioaddr;

	अगर(!netअगर_running(net_dev))
		वापस 0;

	sis900_init_rxfilter(net_dev);

	sis900_init_tx_ring(net_dev);
	sis900_init_rx_ring(net_dev);

	set_rx_mode(net_dev);

	netअगर_device_attach(net_dev);
	netअगर_start_queue(net_dev);

	/* Workaround क्रम EDB */
	sis900_set_mode(sis_priv, HW_SPEED_10_MBPS, FDX_CAPABLE_HALF_SELECTED);

	/* Enable all known पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	sw32(imr, RxSOVR | RxORN | RxERR | RxOK | TxURN | TxERR | TxDESC);
	sw32(cr, RxENA | sr32(cr));
	sw32(ier, IE);

	sis900_check_mode(net_dev, sis_priv->mii);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sis900_pm_ops, sis900_suspend, sis900_resume);

अटल काष्ठा pci_driver sis900_pci_driver = अणु
	.name		= SIS900_MODULE_NAME,
	.id_table	= sis900_pci_tbl,
	.probe		= sis900_probe,
	.हटाओ		= sis900_हटाओ,
	.driver.pm	= &sis900_pm_ops,
पूर्ण;

अटल पूर्णांक __init sis900_init_module(व्योम)
अणु
/* when a module, this is prपूर्णांकed whether or not devices are found in probe */
#अगर_घोषित MODULE
	prपूर्णांकk(version);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&sis900_pci_driver);
पूर्ण

अटल व्योम __निकास sis900_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sis900_pci_driver);
पूर्ण

module_init(sis900_init_module);
module_निकास(sis900_cleanup_module);

