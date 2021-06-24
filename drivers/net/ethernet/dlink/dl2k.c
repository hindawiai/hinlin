<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  D-Link DL2000-based Gigabit Ethernet Adapter Linux driver */
/*
    Copyright (c) 2001, 2002 by D-Link Corporation
    Written by Edward Peng.<edward_peng@dlink.com.tw>
    Created 03-May-2001, base on Linux' sundance.c.

*/

#समावेश "dl2k.h"
#समावेश <linux/dma-mapping.h>

#घोषणा dw32(reg, val)	ioग_लिखो32(val, ioaddr + (reg))
#घोषणा dw16(reg, val)	ioग_लिखो16(val, ioaddr + (reg))
#घोषणा dw8(reg, val)	ioग_लिखो8(val, ioaddr + (reg))
#घोषणा dr32(reg)	ioपढ़ो32(ioaddr + (reg))
#घोषणा dr16(reg)	ioपढ़ो16(ioaddr + (reg))
#घोषणा dr8(reg)	ioपढ़ो8(ioaddr + (reg))

#घोषणा MAX_UNITS 8
अटल पूर्णांक mtu[MAX_UNITS];
अटल पूर्णांक vlan[MAX_UNITS];
अटल पूर्णांक jumbo[MAX_UNITS];
अटल अक्षर *media[MAX_UNITS];
अटल पूर्णांक tx_flow=-1;
अटल पूर्णांक rx_flow=-1;
अटल पूर्णांक copy_thresh;
अटल पूर्णांक rx_coalesce=10;	/* Rx frame count each पूर्णांकerrupt */
अटल पूर्णांक rx_समयout=200;	/* Rx DMA रुको समय in 640ns increments */
अटल पूर्णांक tx_coalesce=16;	/* HW xmit count each TxDMAComplete */


MODULE_AUTHOR ("Edward Peng");
MODULE_DESCRIPTION ("D-Link DL2000-based Gigabit Ethernet Adapter");
MODULE_LICENSE("GPL");
module_param_array(mtu, पूर्णांक, शून्य, 0);
module_param_array(media, अक्षरp, शून्य, 0);
module_param_array(vlan, पूर्णांक, शून्य, 0);
module_param_array(jumbo, पूर्णांक, शून्य, 0);
module_param(tx_flow, पूर्णांक, 0);
module_param(rx_flow, पूर्णांक, 0);
module_param(copy_thresh, पूर्णांक, 0);
module_param(rx_coalesce, पूर्णांक, 0);	/* Rx frame count each पूर्णांकerrupt */
module_param(rx_समयout, पूर्णांक, 0);	/* Rx DMA रुको समय in 64ns increments */
module_param(tx_coalesce, पूर्णांक, 0); /* HW xmit count each TxDMAComplete */


/* Enable the शेष पूर्णांकerrupts */
#घोषणा DEFAULT_INTR (RxDMAComplete | HostError | IntRequested | TxDMAComplete| \
       UpdateStats | LinkEvent)

अटल व्योम dl2k_enable_पूर्णांक(काष्ठा netdev_निजी *np)
अणु
	व्योम __iomem *ioaddr = np->ioaddr;

	dw16(IntEnable, DEFAULT_INTR);
पूर्ण

अटल स्थिर पूर्णांक max_पूर्णांकrloop = 50;
अटल स्थिर पूर्णांक multicast_filter_limit = 0x40;

अटल पूर्णांक rio_खोलो (काष्ठा net_device *dev);
अटल व्योम rio_समयr (काष्ठा समयr_list *t);
अटल व्योम rio_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल netdev_tx_t start_xmit (काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल irqवापस_t rio_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_instance);
अटल व्योम rio_मुक्त_tx (काष्ठा net_device *dev, पूर्णांक irq);
अटल व्योम tx_error (काष्ठा net_device *dev, पूर्णांक tx_status);
अटल पूर्णांक receive_packet (काष्ठा net_device *dev);
अटल व्योम rio_error (काष्ठा net_device *dev, पूर्णांक पूर्णांक_status);
अटल व्योम set_multicast (काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *get_stats (काष्ठा net_device *dev);
अटल पूर्णांक clear_stats (काष्ठा net_device *dev);
अटल पूर्णांक rio_ioctl (काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल पूर्णांक rio_बंद (काष्ठा net_device *dev);
अटल पूर्णांक find_miiphy (काष्ठा net_device *dev);
अटल पूर्णांक parse_eeprom (काष्ठा net_device *dev);
अटल पूर्णांक पढ़ो_eeprom (काष्ठा netdev_निजी *, पूर्णांक eep_addr);
अटल पूर्णांक mii_रुको_link (काष्ठा net_device *dev, पूर्णांक रुको);
अटल पूर्णांक mii_set_media (काष्ठा net_device *dev);
अटल पूर्णांक mii_get_media (काष्ठा net_device *dev);
अटल पूर्णांक mii_set_media_pcs (काष्ठा net_device *dev);
अटल पूर्णांक mii_get_media_pcs (काष्ठा net_device *dev);
अटल पूर्णांक mii_पढ़ो (काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक reg_num);
अटल पूर्णांक mii_ग_लिखो (काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक reg_num,
		      u16 data);

अटल स्थिर काष्ठा ethtool_ops ethtool_ops;

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= rio_खोलो,
	.nकरो_start_xmit	= start_xmit,
	.nकरो_stop		= rio_बंद,
	.nकरो_get_stats		= get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_set_rx_mode	= set_multicast,
	.nकरो_करो_ioctl		= rio_ioctl,
	.nकरो_tx_समयout		= rio_tx_समयout,
पूर्ण;

अटल पूर्णांक
rio_probe1 (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा netdev_निजी *np;
	अटल पूर्णांक card_idx;
	पूर्णांक chip_idx = ent->driver_data;
	पूर्णांक err, irq;
	व्योम __iomem *ioaddr;
	व्योम *ring_space;
	dma_addr_t ring_dma;

	err = pci_enable_device (pdev);
	अगर (err)
		वापस err;

	irq = pdev->irq;
	err = pci_request_regions (pdev, "dl2k");
	अगर (err)
		जाओ err_out_disable;

	pci_set_master (pdev);

	err = -ENOMEM;

	dev = alloc_etherdev (माप (*np));
	अगर (!dev)
		जाओ err_out_res;
	SET_NETDEV_DEV(dev, &pdev->dev);

	np = netdev_priv(dev);

	/* IO रेजिस्टरs range. */
	ioaddr = pci_iomap(pdev, 0, 0);
	अगर (!ioaddr)
		जाओ err_out_dev;
	np->eeprom_addr = ioaddr;

#अगर_घोषित MEM_MAPPING
	/* MM रेजिस्टरs range. */
	ioaddr = pci_iomap(pdev, 1, 0);
	अगर (!ioaddr)
		जाओ err_out_iounmap;
#पूर्ण_अगर
	np->ioaddr = ioaddr;
	np->chip_id = chip_idx;
	np->pdev = pdev;
	spin_lock_init (&np->tx_lock);
	spin_lock_init (&np->rx_lock);

	/* Parse manual configuration */
	np->an_enable = 1;
	np->tx_coalesce = 1;
	अगर (card_idx < MAX_UNITS) अणु
		अगर (media[card_idx] != शून्य) अणु
			np->an_enable = 0;
			अगर (म_भेद (media[card_idx], "auto") == 0 ||
			    म_भेद (media[card_idx], "autosense") == 0 ||
			    म_भेद (media[card_idx], "0") == 0 ) अणु
				np->an_enable = 2;
			पूर्ण अन्यथा अगर (म_भेद (media[card_idx], "100mbps_fd") == 0 ||
			    म_भेद (media[card_idx], "4") == 0) अणु
				np->speed = 100;
				np->full_duplex = 1;
			पूर्ण अन्यथा अगर (म_भेद (media[card_idx], "100mbps_hd") == 0 ||
				   म_भेद (media[card_idx], "3") == 0) अणु
				np->speed = 100;
				np->full_duplex = 0;
			पूर्ण अन्यथा अगर (म_भेद (media[card_idx], "10mbps_fd") == 0 ||
				   म_भेद (media[card_idx], "2") == 0) अणु
				np->speed = 10;
				np->full_duplex = 1;
			पूर्ण अन्यथा अगर (म_भेद (media[card_idx], "10mbps_hd") == 0 ||
				   म_भेद (media[card_idx], "1") == 0) अणु
				np->speed = 10;
				np->full_duplex = 0;
			पूर्ण अन्यथा अगर (म_भेद (media[card_idx], "1000mbps_fd") == 0 ||
				 म_भेद (media[card_idx], "6") == 0) अणु
				np->speed=1000;
				np->full_duplex=1;
			पूर्ण अन्यथा अगर (म_भेद (media[card_idx], "1000mbps_hd") == 0 ||
				 म_भेद (media[card_idx], "5") == 0) अणु
				np->speed = 1000;
				np->full_duplex = 0;
			पूर्ण अन्यथा अणु
				np->an_enable = 1;
			पूर्ण
		पूर्ण
		अगर (jumbo[card_idx] != 0) अणु
			np->jumbo = 1;
			dev->mtu = MAX_JUMBO;
		पूर्ण अन्यथा अणु
			np->jumbo = 0;
			अगर (mtu[card_idx] > 0 && mtu[card_idx] < PACKET_SIZE)
				dev->mtu = mtu[card_idx];
		पूर्ण
		np->vlan = (vlan[card_idx] > 0 && vlan[card_idx] < 4096) ?
		    vlan[card_idx] : 0;
		अगर (rx_coalesce > 0 && rx_समयout > 0) अणु
			np->rx_coalesce = rx_coalesce;
			np->rx_समयout = rx_समयout;
			np->coalesce = 1;
		पूर्ण
		np->tx_flow = (tx_flow == 0) ? 0 : 1;
		np->rx_flow = (rx_flow == 0) ? 0 : 1;

		अगर (tx_coalesce < 1)
			tx_coalesce = 1;
		अन्यथा अगर (tx_coalesce > TX_RING_SIZE-1)
			tx_coalesce = TX_RING_SIZE - 1;
	पूर्ण
	dev->netdev_ops = &netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	dev->ethtool_ops = &ethtool_ops;
#अगर 0
	dev->features = NETIF_F_IP_CSUM;
#पूर्ण_अगर
	/* MTU range: 68 - 1536 or 8000 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = np->jumbo ? MAX_JUMBO : PACKET_SIZE;

	pci_set_drvdata (pdev, dev);

	ring_space = dma_alloc_coherent(&pdev->dev, TX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_iounmap;
	np->tx_ring = ring_space;
	np->tx_ring_dma = ring_dma;

	ring_space = dma_alloc_coherent(&pdev->dev, RX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_unmap_tx;
	np->rx_ring = ring_space;
	np->rx_ring_dma = ring_dma;

	/* Parse eeprom data */
	parse_eeprom (dev);

	/* Find PHY address */
	err = find_miiphy (dev);
	अगर (err)
		जाओ err_out_unmap_rx;

	/* Fiber device? */
	np->phy_media = (dr16(ASICCtrl) & PhyMedia) ? 1 : 0;
	np->link_status = 0;
	/* Set media and reset PHY */
	अगर (np->phy_media) अणु
		/* शेष Auto-Negotiation क्रम fiber deivices */
	 	अगर (np->an_enable == 2) अणु
			np->an_enable = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Auto-Negotiation is mandatory क्रम 1000BASE-T,
		   IEEE 802.3ab Annex 28D page 14 */
		अगर (np->speed == 1000)
			np->an_enable = 1;
	पूर्ण

	err = रेजिस्टर_netdev (dev);
	अगर (err)
		जाओ err_out_unmap_rx;

	card_idx++;

	prपूर्णांकk (KERN_INFO "%s: %s, %pM, IRQ %d\n",
		dev->name, np->name, dev->dev_addr, irq);
	अगर (tx_coalesce > 1)
		prपूर्णांकk(KERN_INFO "tx_coalesce:\t%d packets\n",
				tx_coalesce);
	अगर (np->coalesce)
		prपूर्णांकk(KERN_INFO
		       "rx_coalesce:\t%d packets\n"
		       "rx_timeout: \t%d ns\n",
				np->rx_coalesce, np->rx_समयout*640);
	अगर (np->vlan)
		prपूर्णांकk(KERN_INFO "vlan(id):\t%d\n", np->vlan);
	वापस 0;

err_out_unmap_rx:
	dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, np->rx_ring,
			  np->rx_ring_dma);
err_out_unmap_tx:
	dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, np->tx_ring,
			  np->tx_ring_dma);
err_out_iounmap:
#अगर_घोषित MEM_MAPPING
	pci_iounmap(pdev, np->ioaddr);
#पूर्ण_अगर
	pci_iounmap(pdev, np->eeprom_addr);
err_out_dev:
	मुक्त_netdev (dev);
err_out_res:
	pci_release_regions (pdev);
err_out_disable:
	pci_disable_device (pdev);
	वापस err;
पूर्ण

अटल पूर्णांक
find_miiphy (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i, phy_found = 0;

	np->phy_addr = 1;

	क्रम (i = 31; i >= 0; i--) अणु
		पूर्णांक mii_status = mii_पढ़ो (dev, i, 1);
		अगर (mii_status != 0xffff && mii_status != 0x0000) अणु
			np->phy_addr = i;
			phy_found++;
		पूर्ण
	पूर्ण
	अगर (!phy_found) अणु
		prपूर्णांकk (KERN_ERR "%s: No MII PHY found!\n", dev->name);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
parse_eeprom (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	पूर्णांक i, j;
	u8 sromdata[256];
	u8 *psib;
	u32 crc;
	PSROM_t psrom = (PSROM_t) sromdata;

	पूर्णांक cid, next;

	क्रम (i = 0; i < 128; i++)
		((__le16 *) sromdata)[i] = cpu_to_le16(पढ़ो_eeprom(np, i));

	अगर (np->pdev->venकरोr == PCI_VENDOR_ID_DLINK) अणु	/* D-Link Only */
		/* Check CRC */
		crc = ~ether_crc_le (256 - 4, sromdata);
		अगर (psrom->crc != cpu_to_le32(crc)) अणु
			prपूर्णांकk (KERN_ERR "%s: EEPROM data CRC error.\n",
					dev->name);
			वापस -1;
		पूर्ण
	पूर्ण

	/* Set MAC address */
	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = psrom->mac_addr[i];

	अगर (np->chip_id == CHIP_IP1000A) अणु
		np->led_mode = psrom->led_mode;
		वापस 0;
	पूर्ण

	अगर (np->pdev->venकरोr != PCI_VENDOR_ID_DLINK) अणु
		वापस 0;
	पूर्ण

	/* Parse Software Inक्रमmation Block */
	i = 0x30;
	psib = (u8 *) sromdata;
	करो अणु
		cid = psib[i++];
		next = psib[i++];
		अगर ((cid == 0 && next == 0) || (cid == 0xff && next == 0xff)) अणु
			prपूर्णांकk (KERN_ERR "Cell data error\n");
			वापस -1;
		पूर्ण
		चयन (cid) अणु
		हाल 0:	/* Format version */
			अवरोध;
		हाल 1:	/* End of cell */
			वापस 0;
		हाल 2:	/* Duplex Polarity */
			np->duplex_polarity = psib[i];
			dw8(PhyCtrl, dr8(PhyCtrl) | psib[i]);
			अवरोध;
		हाल 3:	/* Wake Polarity */
			np->wake_polarity = psib[i];
			अवरोध;
		हाल 9:	/* Adapter description */
			j = (next - i > 255) ? 255 : next - i;
			स_नकल (np->name, &(psib[i]), j);
			अवरोध;
		हाल 4:
		हाल 5:
		हाल 6:
		हाल 7:
		हाल 8:	/* Reversed */
			अवरोध;
		शेष:	/* Unknown cell */
			वापस -1;
		पूर्ण
		i = next;
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल व्योम rio_set_led_mode(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	u32 mode;

	अगर (np->chip_id != CHIP_IP1000A)
		वापस;

	mode = dr32(ASICCtrl);
	mode &= ~(IPG_AC_LED_MODE_BIT_1 | IPG_AC_LED_MODE | IPG_AC_LED_SPEED);

	अगर (np->led_mode & 0x01)
		mode |= IPG_AC_LED_MODE;
	अगर (np->led_mode & 0x02)
		mode |= IPG_AC_LED_MODE_BIT_1;
	अगर (np->led_mode & 0x08)
		mode |= IPG_AC_LED_SPEED;

	dw32(ASICCtrl, mode);
पूर्ण

अटल अंतरभूत dma_addr_t desc_to_dma(काष्ठा netdev_desc *desc)
अणु
	वापस le64_to_cpu(desc->fraginfo) & DMA_BIT_MASK(48);
पूर्ण

अटल व्योम मुक्त_list(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	/* Free all the skbuffs in the queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		skb = np->rx_skbuff[i];
		अगर (skb) अणु
			dma_unmap_single(&np->pdev->dev,
					 desc_to_dma(&np->rx_ring[i]),
					 skb->len, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(skb);
			np->rx_skbuff[i] = शून्य;
		पूर्ण
		np->rx_ring[i].status = 0;
		np->rx_ring[i].fraginfo = 0;
	पूर्ण
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		skb = np->tx_skbuff[i];
		अगर (skb) अणु
			dma_unmap_single(&np->pdev->dev,
					 desc_to_dma(&np->tx_ring[i]),
					 skb->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb(skb);
			np->tx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rio_reset_ring(काष्ठा netdev_निजी *np)
अणु
	पूर्णांक i;

	np->cur_rx = 0;
	np->cur_tx = 0;
	np->old_rx = 0;
	np->old_tx = 0;

	क्रम (i = 0; i < TX_RING_SIZE; i++)
		np->tx_ring[i].status = cpu_to_le64(TFDDone);

	क्रम (i = 0; i < RX_RING_SIZE; i++)
		np->rx_ring[i].status = 0;
पूर्ण

 /* allocate and initialize Tx and Rx descriptors */
अटल पूर्णांक alloc_list(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	rio_reset_ring(np);
	np->rx_buf_sz = (dev->mtu <= 1500 ? PACKET_SIZE : dev->mtu + 32);

	/* Initialize Tx descriptors, TFDListPtr leaves in start_xmit(). */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		np->tx_skbuff[i] = शून्य;
		np->tx_ring[i].next_desc = cpu_to_le64(np->tx_ring_dma +
					      ((i + 1) % TX_RING_SIZE) *
					      माप(काष्ठा netdev_desc));
	पूर्ण

	/* Initialize Rx descriptors & allocate buffers */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		/* Allocated fixed size of skbuff */
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(dev, np->rx_buf_sz);
		np->rx_skbuff[i] = skb;
		अगर (!skb) अणु
			मुक्त_list(dev);
			वापस -ENOMEM;
		पूर्ण

		np->rx_ring[i].next_desc = cpu_to_le64(np->rx_ring_dma +
						((i + 1) % RX_RING_SIZE) *
						माप(काष्ठा netdev_desc));
		/* Rubicon now supports 40 bits of addressing space. */
		np->rx_ring[i].fraginfo =
		    cpu_to_le64(dma_map_single(&np->pdev->dev, skb->data,
					       np->rx_buf_sz, DMA_FROM_DEVICE));
		np->rx_ring[i].fraginfo |= cpu_to_le64((u64)np->rx_buf_sz << 48);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rio_hw_init(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	पूर्णांक i;
	u16 macctrl;

	/* Reset all logic functions */
	dw16(ASICCtrl + 2,
	     GlobalReset | DMAReset | FIFOReset | NetworkReset | HostReset);
	mdelay(10);

	rio_set_led_mode(dev);

	/* DebugCtrl bit 4, 5, 9 must set */
	dw32(DebugCtrl, dr32(DebugCtrl) | 0x0230);

	अगर (np->chip_id == CHIP_IP1000A &&
	    (np->pdev->revision == 0x40 || np->pdev->revision == 0x41)) अणु
		/* PHY magic taken from ipg driver, unकरोcumented रेजिस्टरs */
		mii_ग_लिखो(dev, np->phy_addr, 31, 0x0001);
		mii_ग_लिखो(dev, np->phy_addr, 27, 0x01e0);
		mii_ग_लिखो(dev, np->phy_addr, 31, 0x0002);
		mii_ग_लिखो(dev, np->phy_addr, 27, 0xeb8e);
		mii_ग_लिखो(dev, np->phy_addr, 31, 0x0000);
		mii_ग_लिखो(dev, np->phy_addr, 30, 0x005e);
		/* advertise 1000BASE-T half & full duplex, prefer MASTER */
		mii_ग_लिखो(dev, np->phy_addr, MII_CTRL1000, 0x0700);
	पूर्ण

	अगर (np->phy_media)
		mii_set_media_pcs(dev);
	अन्यथा
		mii_set_media(dev);

	/* Jumbo frame */
	अगर (np->jumbo != 0)
		dw16(MaxFrameSize, MAX_JUMBO+14);

	/* Set RFDListPtr */
	dw32(RFDListPtr0, np->rx_ring_dma);
	dw32(RFDListPtr1, 0);

	/* Set station address */
	/* 16 or 32-bit access is required by TC9020 datasheet but 8-bit works
	 * too. However, it करोesn't work on IP1000A so we use 16-bit access.
	 */
	क्रम (i = 0; i < 3; i++)
		dw16(StationAddr0 + 2 * i,
		     cpu_to_le16(((u16 *)dev->dev_addr)[i]));

	set_multicast (dev);
	अगर (np->coalesce) अणु
		dw32(RxDMAIntCtrl, np->rx_coalesce | np->rx_समयout << 16);
	पूर्ण
	/* Set RIO to poll every N*320nsec. */
	dw8(RxDMAPollPeriod, 0x20);
	dw8(TxDMAPollPeriod, 0xff);
	dw8(RxDMABurstThresh, 0x30);
	dw8(RxDMAUrgentThresh, 0x30);
	dw32(RmonStatMask, 0x0007ffff);
	/* clear statistics */
	clear_stats (dev);

	/* VLAN supported */
	अगर (np->vlan) अणु
		/* priority field in RxDMAIntCtrl  */
		dw32(RxDMAIntCtrl, dr32(RxDMAIntCtrl) | 0x7 << 10);
		/* VLANId */
		dw16(VLANId, np->vlan);
		/* Length/Type should be 0x8100 */
		dw32(VLANTag, 0x8100 << 16 | np->vlan);
		/* Enable AutoVLANuntagging, but disable AutoVLANtagging.
		   VLAN inक्रमmation tagged by TFC' VID, CFI fields. */
		dw32(MACCtrl, dr32(MACCtrl) | AutoVLANuntagging);
	पूर्ण

	/* Start Tx/Rx */
	dw32(MACCtrl, dr32(MACCtrl) | StatsEnable | RxEnable | TxEnable);

	macctrl = 0;
	macctrl |= (np->vlan) ? AutoVLANuntagging : 0;
	macctrl |= (np->full_duplex) ? DuplexSelect : 0;
	macctrl |= (np->tx_flow) ? TxFlowControlEnable : 0;
	macctrl |= (np->rx_flow) ? RxFlowControlEnable : 0;
	dw16(MACCtrl, macctrl);
पूर्ण

अटल व्योम rio_hw_stop(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;

	/* Disable पूर्णांकerrupts */
	dw16(IntEnable, 0);

	/* Stop Tx and Rx logics */
	dw32(MACCtrl, TxDisable | RxDisable | StatsDisable);
पूर्ण

अटल पूर्णांक rio_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	स्थिर पूर्णांक irq = np->pdev->irq;
	पूर्णांक i;

	i = alloc_list(dev);
	अगर (i)
		वापस i;

	rio_hw_init(dev);

	i = request_irq(irq, rio_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (i) अणु
		rio_hw_stop(dev);
		मुक्त_list(dev);
		वापस i;
	पूर्ण

	समयr_setup(&np->समयr, rio_समयr, 0);
	np->समयr.expires = jअगरfies + 1 * HZ;
	add_समयr(&np->समयr);

	netअगर_start_queue (dev);

	dl2k_enable_पूर्णांक(np);
	वापस 0;
पूर्ण

अटल व्योम
rio_समयr (काष्ठा समयr_list *t)
अणु
	काष्ठा netdev_निजी *np = from_समयr(np, t, समयr);
	काष्ठा net_device *dev = pci_get_drvdata(np->pdev);
	अचिन्हित पूर्णांक entry;
	पूर्णांक next_tick = 1*HZ;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&np->rx_lock, flags);
	/* Recover rx ring exhausted error */
	अगर (np->cur_rx - np->old_rx >= RX_RING_SIZE) अणु
		prपूर्णांकk(KERN_INFO "Try to recover rx ring exhausted...\n");
		/* Re-allocate skbuffs to fill the descriptor ring */
		क्रम (; np->cur_rx - np->old_rx > 0; np->old_rx++) अणु
			काष्ठा sk_buff *skb;
			entry = np->old_rx % RX_RING_SIZE;
			/* Dropped packets करोn't need to re-allocate */
			अगर (np->rx_skbuff[entry] == शून्य) अणु
				skb = netdev_alloc_skb_ip_align(dev,
								np->rx_buf_sz);
				अगर (skb == शून्य) अणु
					np->rx_ring[entry].fraginfo = 0;
					prपूर्णांकk (KERN_INFO
						"%s: Still unable to re-allocate Rx skbuff.#%d\n",
						dev->name, entry);
					अवरोध;
				पूर्ण
				np->rx_skbuff[entry] = skb;
				np->rx_ring[entry].fraginfo =
				    cpu_to_le64 (dma_map_single(&np->pdev->dev, skb->data,
								np->rx_buf_sz, DMA_FROM_DEVICE));
			पूर्ण
			np->rx_ring[entry].fraginfo |=
			    cpu_to_le64((u64)np->rx_buf_sz << 48);
			np->rx_ring[entry].status = 0;
		पूर्ण /* end क्रम */
	पूर्ण /* end अगर */
	spin_unlock_irqrestore (&np->rx_lock, flags);
	np->समयr.expires = jअगरfies + next_tick;
	add_समयr(&np->समयr);
पूर्ण

अटल व्योम
rio_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;

	prपूर्णांकk (KERN_INFO "%s: Tx timed out (%4.4x), is buffer full?\n",
		dev->name, dr32(TxStatus));
	rio_मुक्त_tx(dev, 0);
	dev->अगर_port = 0;
	netअगर_trans_update(dev); /* prevent tx समयout */
पूर्ण

अटल netdev_tx_t
start_xmit (काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	काष्ठा netdev_desc *txdesc;
	अचिन्हित entry;
	u64 tfc_vlan_tag = 0;

	अगर (np->link_status == 0) अणु	/* Link Down */
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	entry = np->cur_tx % TX_RING_SIZE;
	np->tx_skbuff[entry] = skb;
	txdesc = &np->tx_ring[entry];

#अगर 0
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		txdesc->status |=
		    cpu_to_le64 (TCPChecksumEnable | UDPChecksumEnable |
				 IPChecksumEnable);
	पूर्ण
#पूर्ण_अगर
	अगर (np->vlan) अणु
		tfc_vlan_tag = VLANTagInsert |
		    ((u64)np->vlan << 32) |
		    ((u64)skb->priority << 45);
	पूर्ण
	txdesc->fraginfo = cpu_to_le64 (dma_map_single(&np->pdev->dev, skb->data,
						       skb->len, DMA_TO_DEVICE));
	txdesc->fraginfo |= cpu_to_le64((u64)skb->len << 48);

	/* DL2K bug: DMA fails to get next descriptor ptr in 10Mbps mode
	 * Work around: Always use 1 descriptor in 10Mbps mode */
	अगर (entry % np->tx_coalesce == 0 || np->speed == 10)
		txdesc->status = cpu_to_le64 (entry | tfc_vlan_tag |
					      WordAlignDisable |
					      TxDMAIndicate |
					      (1 << FragCountShअगरt));
	अन्यथा
		txdesc->status = cpu_to_le64 (entry | tfc_vlan_tag |
					      WordAlignDisable |
					      (1 << FragCountShअगरt));

	/* TxDMAPollNow */
	dw32(DMACtrl, dr32(DMACtrl) | 0x00001000);
	/* Schedule ISR */
	dw32(CountDown, 10000);
	np->cur_tx = (np->cur_tx + 1) % TX_RING_SIZE;
	अगर ((np->cur_tx - np->old_tx + TX_RING_SIZE) % TX_RING_SIZE
			< TX_QUEUE_LEN - 1 && np->speed != 10) अणु
		/* करो nothing */
	पूर्ण अन्यथा अगर (!netअगर_queue_stopped(dev)) अणु
		netअगर_stop_queue (dev);
	पूर्ण

	/* The first TFDListPtr */
	अगर (!dr32(TFDListPtr0)) अणु
		dw32(TFDListPtr0, np->tx_ring_dma +
		     entry * माप (काष्ठा netdev_desc));
		dw32(TFDListPtr1, 0);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल irqवापस_t
rio_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	अचिन्हित पूर्णांक_status;
	पूर्णांक cnt = max_पूर्णांकrloop;
	पूर्णांक handled = 0;

	जबतक (1) अणु
		पूर्णांक_status = dr16(IntStatus);
		dw16(IntStatus, पूर्णांक_status);
		पूर्णांक_status &= DEFAULT_INTR;
		अगर (पूर्णांक_status == 0 || --cnt < 0)
			अवरोध;
		handled = 1;
		/* Processing received packets */
		अगर (पूर्णांक_status & RxDMAComplete)
			receive_packet (dev);
		/* TxDMAComplete पूर्णांकerrupt */
		अगर ((पूर्णांक_status & (TxDMAComplete|IntRequested))) अणु
			पूर्णांक tx_status;
			tx_status = dr32(TxStatus);
			अगर (tx_status & 0x01)
				tx_error (dev, tx_status);
			/* Free used tx skbuffs */
			rio_मुक्त_tx (dev, 1);
		पूर्ण

		/* Handle uncommon events */
		अगर (पूर्णांक_status &
		    (HostError | LinkEvent | UpdateStats))
			rio_error (dev, पूर्णांक_status);
	पूर्ण
	अगर (np->cur_tx != np->old_tx)
		dw32(CountDown, 100);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम
rio_मुक्त_tx (काष्ठा net_device *dev, पूर्णांक irq)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक entry = np->old_tx % TX_RING_SIZE;
	पूर्णांक tx_use = 0;
	अचिन्हित दीर्घ flag = 0;

	अगर (irq)
		spin_lock(&np->tx_lock);
	अन्यथा
		spin_lock_irqsave(&np->tx_lock, flag);

	/* Free used tx skbuffs */
	जबतक (entry != np->cur_tx) अणु
		काष्ठा sk_buff *skb;

		अगर (!(np->tx_ring[entry].status & cpu_to_le64(TFDDone)))
			अवरोध;
		skb = np->tx_skbuff[entry];
		dma_unmap_single(&np->pdev->dev,
				 desc_to_dma(&np->tx_ring[entry]), skb->len,
				 DMA_TO_DEVICE);
		अगर (irq)
			dev_consume_skb_irq(skb);
		अन्यथा
			dev_kमुक्त_skb(skb);

		np->tx_skbuff[entry] = शून्य;
		entry = (entry + 1) % TX_RING_SIZE;
		tx_use++;
	पूर्ण
	अगर (irq)
		spin_unlock(&np->tx_lock);
	अन्यथा
		spin_unlock_irqrestore(&np->tx_lock, flag);
	np->old_tx = entry;

	/* If the ring is no दीर्घer full, clear tx_full and
	   call netअगर_wake_queue() */

	अगर (netअगर_queue_stopped(dev) &&
	    ((np->cur_tx - np->old_tx + TX_RING_SIZE) % TX_RING_SIZE
	    < TX_QUEUE_LEN - 1 || np->speed == 10)) अणु
		netअगर_wake_queue (dev);
	पूर्ण
पूर्ण

अटल व्योम
tx_error (काष्ठा net_device *dev, पूर्णांक tx_status)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	पूर्णांक frame_id;
	पूर्णांक i;

	frame_id = (tx_status & 0xffff0000);
	prपूर्णांकk (KERN_ERR "%s: Transmit error, TxStatus %4.4x, FrameId %d.\n",
		dev->name, tx_status, frame_id);
	dev->stats.tx_errors++;
	/* Ttransmit Underrun */
	अगर (tx_status & 0x10) अणु
		dev->stats.tx_fअगरo_errors++;
		dw16(TxStartThresh, dr16(TxStartThresh) + 0x10);
		/* Transmit Underrun need to set TxReset, DMARest, FIFOReset */
		dw16(ASICCtrl + 2,
		     TxReset | DMAReset | FIFOReset | NetworkReset);
		/* Wait क्रम ResetBusy bit clear */
		क्रम (i = 50; i > 0; i--) अणु
			अगर (!(dr16(ASICCtrl + 2) & ResetBusy))
				अवरोध;
			mdelay (1);
		पूर्ण
		rio_set_led_mode(dev);
		rio_मुक्त_tx (dev, 1);
		/* Reset TFDListPtr */
		dw32(TFDListPtr0, np->tx_ring_dma +
		     np->old_tx * माप (काष्ठा netdev_desc));
		dw32(TFDListPtr1, 0);

		/* Let TxStartThresh stay शेष value */
	पूर्ण
	/* Late Collision */
	अगर (tx_status & 0x04) अणु
		dev->stats.tx_fअगरo_errors++;
		/* TxReset and clear FIFO */
		dw16(ASICCtrl + 2, TxReset | FIFOReset);
		/* Wait reset करोne */
		क्रम (i = 50; i > 0; i--) अणु
			अगर (!(dr16(ASICCtrl + 2) & ResetBusy))
				अवरोध;
			mdelay (1);
		पूर्ण
		rio_set_led_mode(dev);
		/* Let TxStartThresh stay शेष value */
	पूर्ण
	/* Maximum Collisions */
	अगर (tx_status & 0x08)
		dev->stats.collisions++;
	/* Restart the Tx */
	dw32(MACCtrl, dr16(MACCtrl) | TxEnable);
पूर्ण

अटल पूर्णांक
receive_packet (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक entry = np->cur_rx % RX_RING_SIZE;
	पूर्णांक cnt = 30;

	/* If RFDDone, FrameStart and FrameEnd set, there is a new packet in. */
	जबतक (1) अणु
		काष्ठा netdev_desc *desc = &np->rx_ring[entry];
		पूर्णांक pkt_len;
		u64 frame_status;

		अगर (!(desc->status & cpu_to_le64(RFDDone)) ||
		    !(desc->status & cpu_to_le64(FrameStart)) ||
		    !(desc->status & cpu_to_le64(FrameEnd)))
			अवरोध;

		/* Chip omits the CRC. */
		frame_status = le64_to_cpu(desc->status);
		pkt_len = frame_status & 0xffff;
		अगर (--cnt < 0)
			अवरोध;
		/* Update rx error statistics, drop packet. */
		अगर (frame_status & RFS_Errors) अणु
			dev->stats.rx_errors++;
			अगर (frame_status & (RxRuntFrame | RxLengthError))
				dev->stats.rx_length_errors++;
			अगर (frame_status & RxFCSError)
				dev->stats.rx_crc_errors++;
			अगर (frame_status & RxAlignmentError && np->speed != 1000)
				dev->stats.rx_frame_errors++;
			अगर (frame_status & RxFIFOOverrun)
				dev->stats.rx_fअगरo_errors++;
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb;

			/* Small skbuffs क्रम लघु packets */
			अगर (pkt_len > copy_thresh) अणु
				dma_unmap_single(&np->pdev->dev,
						 desc_to_dma(desc),
						 np->rx_buf_sz,
						 DMA_FROM_DEVICE);
				skb_put (skb = np->rx_skbuff[entry], pkt_len);
				np->rx_skbuff[entry] = शून्य;
			पूर्ण अन्यथा अगर ((skb = netdev_alloc_skb_ip_align(dev, pkt_len))) अणु
				dma_sync_single_क्रम_cpu(&np->pdev->dev,
							desc_to_dma(desc),
							np->rx_buf_sz,
							DMA_FROM_DEVICE);
				skb_copy_to_linear_data (skb,
						  np->rx_skbuff[entry]->data,
						  pkt_len);
				skb_put (skb, pkt_len);
				dma_sync_single_क्रम_device(&np->pdev->dev,
							   desc_to_dma(desc),
							   np->rx_buf_sz,
							   DMA_FROM_DEVICE);
			पूर्ण
			skb->protocol = eth_type_trans (skb, dev);
#अगर 0
			/* Checksum करोne by hw, but csum value unavailable. */
			अगर (np->pdev->pci_rev_id >= 0x0c &&
				!(frame_status & (TCPError | UDPError | IPError))) अणु
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			पूर्ण
#पूर्ण_अगर
			netअगर_rx (skb);
		पूर्ण
		entry = (entry + 1) % RX_RING_SIZE;
	पूर्ण
	spin_lock(&np->rx_lock);
	np->cur_rx = entry;
	/* Re-allocate skbuffs to fill the descriptor ring */
	entry = np->old_rx;
	जबतक (entry != np->cur_rx) अणु
		काष्ठा sk_buff *skb;
		/* Dropped packets करोn't need to re-allocate */
		अगर (np->rx_skbuff[entry] == शून्य) अणु
			skb = netdev_alloc_skb_ip_align(dev, np->rx_buf_sz);
			अगर (skb == शून्य) अणु
				np->rx_ring[entry].fraginfo = 0;
				prपूर्णांकk (KERN_INFO
					"%s: receive_packet: "
					"Unable to re-allocate Rx skbuff.#%d\n",
					dev->name, entry);
				अवरोध;
			पूर्ण
			np->rx_skbuff[entry] = skb;
			np->rx_ring[entry].fraginfo =
			    cpu_to_le64(dma_map_single(&np->pdev->dev, skb->data,
						       np->rx_buf_sz, DMA_FROM_DEVICE));
		पूर्ण
		np->rx_ring[entry].fraginfo |=
		    cpu_to_le64((u64)np->rx_buf_sz << 48);
		np->rx_ring[entry].status = 0;
		entry = (entry + 1) % RX_RING_SIZE;
	पूर्ण
	np->old_rx = entry;
	spin_unlock(&np->rx_lock);
	वापस 0;
पूर्ण

अटल व्योम
rio_error (काष्ठा net_device *dev, पूर्णांक पूर्णांक_status)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	u16 macctrl;

	/* Link change event */
	अगर (पूर्णांक_status & LinkEvent) अणु
		अगर (mii_रुको_link (dev, 10) == 0) अणु
			prपूर्णांकk (KERN_INFO "%s: Link up\n", dev->name);
			अगर (np->phy_media)
				mii_get_media_pcs (dev);
			अन्यथा
				mii_get_media (dev);
			अगर (np->speed == 1000)
				np->tx_coalesce = tx_coalesce;
			अन्यथा
				np->tx_coalesce = 1;
			macctrl = 0;
			macctrl |= (np->vlan) ? AutoVLANuntagging : 0;
			macctrl |= (np->full_duplex) ? DuplexSelect : 0;
			macctrl |= (np->tx_flow) ?
				TxFlowControlEnable : 0;
			macctrl |= (np->rx_flow) ?
				RxFlowControlEnable : 0;
			dw16(MACCtrl, macctrl);
			np->link_status = 1;
			netअगर_carrier_on(dev);
		पूर्ण अन्यथा अणु
			prपूर्णांकk (KERN_INFO "%s: Link off\n", dev->name);
			np->link_status = 0;
			netअगर_carrier_off(dev);
		पूर्ण
	पूर्ण

	/* UpdateStats statistics रेजिस्टरs */
	अगर (पूर्णांक_status & UpdateStats) अणु
		get_stats (dev);
	पूर्ण

	/* PCI Error, a catastronphic error related to the bus पूर्णांकerface
	   occurs, set GlobalReset and HostReset to reset. */
	अगर (पूर्णांक_status & HostError) अणु
		prपूर्णांकk (KERN_ERR "%s: HostError! IntStatus %4.4x.\n",
			dev->name, पूर्णांक_status);
		dw16(ASICCtrl + 2, GlobalReset | HostReset);
		mdelay (500);
		rio_set_led_mode(dev);
	पूर्ण
पूर्ण

अटल काष्ठा net_device_stats *
get_stats (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
#अगर_घोषित MEM_MAPPING
	पूर्णांक i;
#पूर्ण_अगर
	अचिन्हित पूर्णांक stat_reg;

	/* All statistics रेजिस्टरs need to be acknowledged,
	   अन्यथा statistic overflow could cause problems */

	dev->stats.rx_packets += dr32(FramesRcvOk);
	dev->stats.tx_packets += dr32(FramesXmtOk);
	dev->stats.rx_bytes += dr32(OctetRcvOk);
	dev->stats.tx_bytes += dr32(OctetXmtOk);

	dev->stats.multicast = dr32(McstFramesRcvdOk);
	dev->stats.collisions += dr32(SingleColFrames)
			     +  dr32(MultiColFrames);

	/* detailed tx errors */
	stat_reg = dr16(FramesAbortXSColls);
	dev->stats.tx_पातed_errors += stat_reg;
	dev->stats.tx_errors += stat_reg;

	stat_reg = dr16(CarrierSenseErrors);
	dev->stats.tx_carrier_errors += stat_reg;
	dev->stats.tx_errors += stat_reg;

	/* Clear all other statistic रेजिस्टर. */
	dr32(McstOctetXmtOk);
	dr16(BcstFramesXmtdOk);
	dr32(McstFramesXmtdOk);
	dr16(BcstFramesRcvdOk);
	dr16(MacControlFramesRcvd);
	dr16(FrameTooLongErrors);
	dr16(InRangeLengthErrors);
	dr16(FramesCheckSeqErrors);
	dr16(FramesLostRxErrors);
	dr32(McstOctetXmtOk);
	dr32(BcstOctetXmtOk);
	dr32(McstFramesXmtdOk);
	dr32(FramesWDeferredXmt);
	dr32(LateCollisions);
	dr16(BcstFramesXmtdOk);
	dr16(MacControlFramesXmtd);
	dr16(FramesWEXDeferal);

#अगर_घोषित MEM_MAPPING
	क्रम (i = 0x100; i <= 0x150; i += 4)
		dr32(i);
#पूर्ण_अगर
	dr16(TxJumboFrames);
	dr16(RxJumboFrames);
	dr16(TCPCheckSumErrors);
	dr16(UDPCheckSumErrors);
	dr16(IPCheckSumErrors);
	वापस &dev->stats;
पूर्ण

अटल पूर्णांक
clear_stats (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
#अगर_घोषित MEM_MAPPING
	पूर्णांक i;
#पूर्ण_अगर

	/* All statistics रेजिस्टरs need to be acknowledged,
	   अन्यथा statistic overflow could cause problems */
	dr32(FramesRcvOk);
	dr32(FramesXmtOk);
	dr32(OctetRcvOk);
	dr32(OctetXmtOk);

	dr32(McstFramesRcvdOk);
	dr32(SingleColFrames);
	dr32(MultiColFrames);
	dr32(LateCollisions);
	/* detailed rx errors */
	dr16(FrameTooLongErrors);
	dr16(InRangeLengthErrors);
	dr16(FramesCheckSeqErrors);
	dr16(FramesLostRxErrors);

	/* detailed tx errors */
	dr16(FramesAbortXSColls);
	dr16(CarrierSenseErrors);

	/* Clear all other statistic रेजिस्टर. */
	dr32(McstOctetXmtOk);
	dr16(BcstFramesXmtdOk);
	dr32(McstFramesXmtdOk);
	dr16(BcstFramesRcvdOk);
	dr16(MacControlFramesRcvd);
	dr32(McstOctetXmtOk);
	dr32(BcstOctetXmtOk);
	dr32(McstFramesXmtdOk);
	dr32(FramesWDeferredXmt);
	dr16(BcstFramesXmtdOk);
	dr16(MacControlFramesXmtd);
	dr16(FramesWEXDeferal);
#अगर_घोषित MEM_MAPPING
	क्रम (i = 0x100; i <= 0x150; i += 4)
		dr32(i);
#पूर्ण_अगर
	dr16(TxJumboFrames);
	dr16(RxJumboFrames);
	dr16(TCPCheckSumErrors);
	dr16(UDPCheckSumErrors);
	dr16(IPCheckSumErrors);
	वापस 0;
पूर्ण

अटल व्योम
set_multicast (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	u32 hash_table[2];
	u16 rx_mode = 0;

	hash_table[0] = hash_table[1] = 0;
	/* RxFlowcontrol DA: 01-80-C2-00-00-01. Hash index=0x39 */
	hash_table[1] |= 0x02000000;
	अगर (dev->flags & IFF_PROMISC) अणु
		/* Receive all frames promiscuously. */
		rx_mode = ReceiveAllFrames;
	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI) ||
			(netdev_mc_count(dev) > multicast_filter_limit)) अणु
		/* Receive broadcast and multicast frames */
		rx_mode = ReceiveBroadcast | ReceiveMulticast | ReceiveUnicast;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;
		/* Receive broadcast frames and multicast frames filtering
		   by Hashtable */
		rx_mode =
		    ReceiveBroadcast | ReceiveMulticastHash | ReceiveUnicast;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			पूर्णांक bit, index = 0;
			पूर्णांक crc = ether_crc_le(ETH_ALEN, ha->addr);
			/* The inverted high signअगरicant 6 bits of CRC are
			   used as an index to hashtable */
			क्रम (bit = 0; bit < 6; bit++)
				अगर (crc & (1 << (31 - bit)))
					index |= (1 << bit);
			hash_table[index / 32] |= (1 << (index % 32));
		पूर्ण
	पूर्ण अन्यथा अणु
		rx_mode = ReceiveBroadcast | ReceiveUnicast;
	पूर्ण
	अगर (np->vlan) अणु
		/* ReceiveVLANMatch field in ReceiveMode */
		rx_mode |= ReceiveVLANMatch;
	पूर्ण

	dw32(HashTable0, hash_table[0]);
	dw32(HashTable1, hash_table[1]);
	dw16(ReceiveMode, rx_mode);
पूर्ण

अटल व्योम rio_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	strlcpy(info->driver, "dl2k", माप(info->driver));
	strlcpy(info->bus_info, pci_name(np->pdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक rio_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u32 supported, advertising;

	अगर (np->phy_media) अणु
		/* fiber device */
		supported = SUPPORTED_Autoneg | SUPPORTED_FIBRE;
		advertising = ADVERTISED_Autoneg | ADVERTISED_FIBRE;
		cmd->base.port = PORT_FIBRE;
	पूर्ण अन्यथा अणु
		/* copper device */
		supported = SUPPORTED_10baseT_Half |
			SUPPORTED_10baseT_Full | SUPPORTED_100baseT_Half
			| SUPPORTED_100baseT_Full | SUPPORTED_1000baseT_Full |
			SUPPORTED_Autoneg | SUPPORTED_MII;
		advertising = ADVERTISED_10baseT_Half |
			ADVERTISED_10baseT_Full | ADVERTISED_100baseT_Half |
			ADVERTISED_100baseT_Full | ADVERTISED_1000baseT_Full |
			ADVERTISED_Autoneg | ADVERTISED_MII;
		cmd->base.port = PORT_MII;
	पूर्ण
	अगर (np->link_status) अणु
		cmd->base.speed = np->speed;
		cmd->base.duplex = np->full_duplex ? DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण
	अगर (np->an_enable)
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	अन्यथा
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

	cmd->base.phy_address = np->phy_addr;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक rio_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	u8 duplex = cmd->base.duplex;

	netअगर_carrier_off(dev);
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (np->an_enable) अणु
			वापस 0;
		पूर्ण अन्यथा अणु
			np->an_enable = 1;
			mii_set_media(dev);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		np->an_enable = 0;
		अगर (np->speed == 1000) अणु
			speed = SPEED_100;
			duplex = DUPLEX_FULL;
			prपूर्णांकk("Warning!! Can't disable Auto negotiation in 1000Mbps, change to Manual 100Mbps, Full duplex.\n");
		पूर्ण
		चयन (speed) अणु
		हाल SPEED_10:
			np->speed = 10;
			np->full_duplex = (duplex == DUPLEX_FULL);
			अवरोध;
		हाल SPEED_100:
			np->speed = 100;
			np->full_duplex = (duplex == DUPLEX_FULL);
			अवरोध;
		हाल SPEED_1000: /* not supported */
		शेष:
			वापस -EINVAL;
		पूर्ण
		mii_set_media(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 rio_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस np->link_status;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.get_drvinfo = rio_get_drvinfo,
	.get_link = rio_get_link,
	.get_link_ksettings = rio_get_link_ksettings,
	.set_link_ksettings = rio_set_link_ksettings,
पूर्ण;

अटल पूर्णांक
rio_ioctl (काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	पूर्णांक phy_addr;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	काष्ठा mii_ioctl_data *miidata = अगर_mii(rq);

	phy_addr = np->phy_addr;
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		miidata->phy_id = phy_addr;
		अवरोध;
	हाल SIOCGMIIREG:
		miidata->val_out = mii_पढ़ो (dev, phy_addr, miidata->reg_num);
		अवरोध;
	हाल SIOCSMIIREG:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		mii_ग_लिखो (dev, phy_addr, miidata->reg_num, miidata->val_in);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा EEP_READ 0x0200
#घोषणा EEP_BUSY 0x8000
/* Read the EEPROM word */
/* We use I/O inकाष्ठाion to पढ़ो/ग_लिखो eeprom to aव्योम fail on some machines */
अटल पूर्णांक पढ़ो_eeprom(काष्ठा netdev_निजी *np, पूर्णांक eep_addr)
अणु
	व्योम __iomem *ioaddr = np->eeprom_addr;
	पूर्णांक i = 1000;

	dw16(EepromCtrl, EEP_READ | (eep_addr & 0xff));
	जबतक (i-- > 0) अणु
		अगर (!(dr16(EepromCtrl) & EEP_BUSY))
			वापस dr16(EepromData);
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत phy_ctrl_bits अणु
	MII_READ = 0x00, MII_CLK = 0x01, MII_DATA1 = 0x02, MII_WRITE = 0x04,
	MII_DUPLEX = 0x08,
पूर्ण;

#घोषणा mii_delay() dr8(PhyCtrl)
अटल व्योम
mii_sendbit (काष्ठा net_device *dev, u32 data)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;

	data = ((data) ? MII_DATA1 : 0) | (dr8(PhyCtrl) & 0xf8) | MII_WRITE;
	dw8(PhyCtrl, data);
	mii_delay ();
	dw8(PhyCtrl, data | MII_CLK);
	mii_delay ();
पूर्ण

अटल पूर्णांक
mii_getbit (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->ioaddr;
	u8 data;

	data = (dr8(PhyCtrl) & 0xf8) | MII_READ;
	dw8(PhyCtrl, data);
	mii_delay ();
	dw8(PhyCtrl, data | MII_CLK);
	mii_delay ();
	वापस (dr8(PhyCtrl) >> 1) & 1;
पूर्ण

अटल व्योम
mii_send_bits (काष्ठा net_device *dev, u32 data, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = len - 1; i >= 0; i--) अणु
		mii_sendbit (dev, data & (1 << i));
	पूर्ण
पूर्ण

अटल पूर्णांक
mii_पढ़ो (काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक reg_num)
अणु
	u32 cmd;
	पूर्णांक i;
	u32 retval = 0;

	/* Preamble */
	mii_send_bits (dev, 0xffffffff, 32);
	/* ST(2), OP(2), ADDR(5), REG#(5), TA(2), Data(16) total 32 bits */
	/* ST,OP = 0110'b क्रम पढ़ो operation */
	cmd = (0x06 << 10 | phy_addr << 5 | reg_num);
	mii_send_bits (dev, cmd, 14);
	/* Turnaround */
	अगर (mii_getbit (dev))
		जाओ err_out;
	/* Read data */
	क्रम (i = 0; i < 16; i++) अणु
		retval |= mii_getbit (dev);
		retval <<= 1;
	पूर्ण
	/* End cycle */
	mii_getbit (dev);
	वापस (retval >> 1) & 0xffff;

      err_out:
	वापस 0;
पूर्ण
अटल पूर्णांक
mii_ग_लिखो (काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक reg_num, u16 data)
अणु
	u32 cmd;

	/* Preamble */
	mii_send_bits (dev, 0xffffffff, 32);
	/* ST(2), OP(2), ADDR(5), REG#(5), TA(2), Data(16) total 32 bits */
	/* ST,OP,AAAAA,RRRRR,TA = 0101xxxxxxxxxx10'b = 0x5002 क्रम ग_लिखो */
	cmd = (0x5002 << 16) | (phy_addr << 23) | (reg_num << 18) | data;
	mii_send_bits (dev, cmd, 32);
	/* End cycle */
	mii_getbit (dev);
	वापस 0;
पूर्ण
अटल पूर्णांक
mii_रुको_link (काष्ठा net_device *dev, पूर्णांक रुको)
अणु
	__u16 bmsr;
	पूर्णांक phy_addr;
	काष्ठा netdev_निजी *np;

	np = netdev_priv(dev);
	phy_addr = np->phy_addr;

	करो अणु
		bmsr = mii_पढ़ो (dev, phy_addr, MII_BMSR);
		अगर (bmsr & BMSR_LSTATUS)
			वापस 0;
		mdelay (1);
	पूर्ण जबतक (--रुको > 0);
	वापस -1;
पूर्ण
अटल पूर्णांक
mii_get_media (काष्ठा net_device *dev)
अणु
	__u16 negotiate;
	__u16 bmsr;
	__u16 mscr;
	__u16 mssr;
	पूर्णांक phy_addr;
	काष्ठा netdev_निजी *np;

	np = netdev_priv(dev);
	phy_addr = np->phy_addr;

	bmsr = mii_पढ़ो (dev, phy_addr, MII_BMSR);
	अगर (np->an_enable) अणु
		अगर (!(bmsr & BMSR_ANEGCOMPLETE)) अणु
			/* Auto-Negotiation not completed */
			वापस -1;
		पूर्ण
		negotiate = mii_पढ़ो (dev, phy_addr, MII_ADVERTISE) &
			mii_पढ़ो (dev, phy_addr, MII_LPA);
		mscr = mii_पढ़ो (dev, phy_addr, MII_CTRL1000);
		mssr = mii_पढ़ो (dev, phy_addr, MII_STAT1000);
		अगर (mscr & ADVERTISE_1000FULL && mssr & LPA_1000FULL) अणु
			np->speed = 1000;
			np->full_duplex = 1;
			prपूर्णांकk (KERN_INFO "Auto 1000 Mbps, Full duplex\n");
		पूर्ण अन्यथा अगर (mscr & ADVERTISE_1000HALF && mssr & LPA_1000HALF) अणु
			np->speed = 1000;
			np->full_duplex = 0;
			prपूर्णांकk (KERN_INFO "Auto 1000 Mbps, Half duplex\n");
		पूर्ण अन्यथा अगर (negotiate & ADVERTISE_100FULL) अणु
			np->speed = 100;
			np->full_duplex = 1;
			prपूर्णांकk (KERN_INFO "Auto 100 Mbps, Full duplex\n");
		पूर्ण अन्यथा अगर (negotiate & ADVERTISE_100HALF) अणु
			np->speed = 100;
			np->full_duplex = 0;
			prपूर्णांकk (KERN_INFO "Auto 100 Mbps, Half duplex\n");
		पूर्ण अन्यथा अगर (negotiate & ADVERTISE_10FULL) अणु
			np->speed = 10;
			np->full_duplex = 1;
			prपूर्णांकk (KERN_INFO "Auto 10 Mbps, Full duplex\n");
		पूर्ण अन्यथा अगर (negotiate & ADVERTISE_10HALF) अणु
			np->speed = 10;
			np->full_duplex = 0;
			prपूर्णांकk (KERN_INFO "Auto 10 Mbps, Half duplex\n");
		पूर्ण
		अगर (negotiate & ADVERTISE_PAUSE_CAP) अणु
			np->tx_flow &= 1;
			np->rx_flow &= 1;
		पूर्ण अन्यथा अगर (negotiate & ADVERTISE_PAUSE_ASYM) अणु
			np->tx_flow = 0;
			np->rx_flow &= 1;
		पूर्ण
		/* अन्यथा tx_flow, rx_flow = user select  */
	पूर्ण अन्यथा अणु
		__u16 bmcr = mii_पढ़ो (dev, phy_addr, MII_BMCR);
		चयन (bmcr & (BMCR_SPEED100 | BMCR_SPEED1000)) अणु
		हाल BMCR_SPEED1000:
			prपूर्णांकk (KERN_INFO "Operating at 1000 Mbps, ");
			अवरोध;
		हाल BMCR_SPEED100:
			prपूर्णांकk (KERN_INFO "Operating at 100 Mbps, ");
			अवरोध;
		हाल 0:
			prपूर्णांकk (KERN_INFO "Operating at 10 Mbps, ");
		पूर्ण
		अगर (bmcr & BMCR_FULLDPLX) अणु
			prपूर्णांकk (KERN_CONT "Full duplex\n");
		पूर्ण अन्यथा अणु
			prपूर्णांकk (KERN_CONT "Half duplex\n");
		पूर्ण
	पूर्ण
	अगर (np->tx_flow)
		prपूर्णांकk(KERN_INFO "Enable Tx Flow Control\n");
	अन्यथा
		prपूर्णांकk(KERN_INFO "Disable Tx Flow Control\n");
	अगर (np->rx_flow)
		prपूर्णांकk(KERN_INFO "Enable Rx Flow Control\n");
	अन्यथा
		prपूर्णांकk(KERN_INFO "Disable Rx Flow Control\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
mii_set_media (काष्ठा net_device *dev)
अणु
	__u16 pscr;
	__u16 bmcr;
	__u16 bmsr;
	__u16 anar;
	पूर्णांक phy_addr;
	काष्ठा netdev_निजी *np;
	np = netdev_priv(dev);
	phy_addr = np->phy_addr;

	/* Does user set speed? */
	अगर (np->an_enable) अणु
		/* Advertise capabilities */
		bmsr = mii_पढ़ो (dev, phy_addr, MII_BMSR);
		anar = mii_पढ़ो (dev, phy_addr, MII_ADVERTISE) &
			~(ADVERTISE_100FULL | ADVERTISE_10FULL |
			  ADVERTISE_100HALF | ADVERTISE_10HALF |
			  ADVERTISE_100BASE4);
		अगर (bmsr & BMSR_100FULL)
			anar |= ADVERTISE_100FULL;
		अगर (bmsr & BMSR_100HALF)
			anar |= ADVERTISE_100HALF;
		अगर (bmsr & BMSR_100BASE4)
			anar |= ADVERTISE_100BASE4;
		अगर (bmsr & BMSR_10FULL)
			anar |= ADVERTISE_10FULL;
		अगर (bmsr & BMSR_10HALF)
			anar |= ADVERTISE_10HALF;
		anar |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
		mii_ग_लिखो (dev, phy_addr, MII_ADVERTISE, anar);

		/* Enable Auto crossover */
		pscr = mii_पढ़ो (dev, phy_addr, MII_PHY_SCR);
		pscr |= 3 << 5;	/* 11'b */
		mii_ग_लिखो (dev, phy_addr, MII_PHY_SCR, pscr);

		/* Soft reset PHY */
		mii_ग_लिखो (dev, phy_addr, MII_BMCR, BMCR_RESET);
		bmcr = BMCR_ANENABLE | BMCR_ANRESTART | BMCR_RESET;
		mii_ग_लिखो (dev, phy_addr, MII_BMCR, bmcr);
		mdelay(1);
	पूर्ण अन्यथा अणु
		/* Force speed setting */
		/* 1) Disable Auto crossover */
		pscr = mii_पढ़ो (dev, phy_addr, MII_PHY_SCR);
		pscr &= ~(3 << 5);
		mii_ग_लिखो (dev, phy_addr, MII_PHY_SCR, pscr);

		/* 2) PHY Reset */
		bmcr = mii_पढ़ो (dev, phy_addr, MII_BMCR);
		bmcr |= BMCR_RESET;
		mii_ग_लिखो (dev, phy_addr, MII_BMCR, bmcr);

		/* 3) Power Down */
		bmcr = 0x1940;	/* must be 0x1940 */
		mii_ग_लिखो (dev, phy_addr, MII_BMCR, bmcr);
		mdelay (100);	/* रुको a certain समय */

		/* 4) Advertise nothing */
		mii_ग_लिखो (dev, phy_addr, MII_ADVERTISE, 0);

		/* 5) Set media and Power Up */
		bmcr = BMCR_PDOWN;
		अगर (np->speed == 100) अणु
			bmcr |= BMCR_SPEED100;
			prपूर्णांकk (KERN_INFO "Manual 100 Mbps, ");
		पूर्ण अन्यथा अगर (np->speed == 10) अणु
			prपूर्णांकk (KERN_INFO "Manual 10 Mbps, ");
		पूर्ण
		अगर (np->full_duplex) अणु
			bmcr |= BMCR_FULLDPLX;
			prपूर्णांकk (KERN_CONT "Full duplex\n");
		पूर्ण अन्यथा अणु
			prपूर्णांकk (KERN_CONT "Half duplex\n");
		पूर्ण
#अगर 0
		/* Set 1000BaseT Master/Slave setting */
		mscr = mii_पढ़ो (dev, phy_addr, MII_CTRL1000);
		mscr |= MII_MSCR_CFG_ENABLE;
		mscr &= ~MII_MSCR_CFG_VALUE = 0;
#पूर्ण_अगर
		mii_ग_लिखो (dev, phy_addr, MII_BMCR, bmcr);
		mdelay(10);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mii_get_media_pcs (काष्ठा net_device *dev)
अणु
	__u16 negotiate;
	__u16 bmsr;
	पूर्णांक phy_addr;
	काष्ठा netdev_निजी *np;

	np = netdev_priv(dev);
	phy_addr = np->phy_addr;

	bmsr = mii_पढ़ो (dev, phy_addr, PCS_BMSR);
	अगर (np->an_enable) अणु
		अगर (!(bmsr & BMSR_ANEGCOMPLETE)) अणु
			/* Auto-Negotiation not completed */
			वापस -1;
		पूर्ण
		negotiate = mii_पढ़ो (dev, phy_addr, PCS_ANAR) &
			mii_पढ़ो (dev, phy_addr, PCS_ANLPAR);
		np->speed = 1000;
		अगर (negotiate & PCS_ANAR_FULL_DUPLEX) अणु
			prपूर्णांकk (KERN_INFO "Auto 1000 Mbps, Full duplex\n");
			np->full_duplex = 1;
		पूर्ण अन्यथा अणु
			prपूर्णांकk (KERN_INFO "Auto 1000 Mbps, half duplex\n");
			np->full_duplex = 0;
		पूर्ण
		अगर (negotiate & PCS_ANAR_PAUSE) अणु
			np->tx_flow &= 1;
			np->rx_flow &= 1;
		पूर्ण अन्यथा अगर (negotiate & PCS_ANAR_ASYMMETRIC) अणु
			np->tx_flow = 0;
			np->rx_flow &= 1;
		पूर्ण
		/* अन्यथा tx_flow, rx_flow = user select  */
	पूर्ण अन्यथा अणु
		__u16 bmcr = mii_पढ़ो (dev, phy_addr, PCS_BMCR);
		prपूर्णांकk (KERN_INFO "Operating at 1000 Mbps, ");
		अगर (bmcr & BMCR_FULLDPLX) अणु
			prपूर्णांकk (KERN_CONT "Full duplex\n");
		पूर्ण अन्यथा अणु
			prपूर्णांकk (KERN_CONT "Half duplex\n");
		पूर्ण
	पूर्ण
	अगर (np->tx_flow)
		prपूर्णांकk(KERN_INFO "Enable Tx Flow Control\n");
	अन्यथा
		prपूर्णांकk(KERN_INFO "Disable Tx Flow Control\n");
	अगर (np->rx_flow)
		prपूर्णांकk(KERN_INFO "Enable Rx Flow Control\n");
	अन्यथा
		prपूर्णांकk(KERN_INFO "Disable Rx Flow Control\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
mii_set_media_pcs (काष्ठा net_device *dev)
अणु
	__u16 bmcr;
	__u16 esr;
	__u16 anar;
	पूर्णांक phy_addr;
	काष्ठा netdev_निजी *np;
	np = netdev_priv(dev);
	phy_addr = np->phy_addr;

	/* Auto-Negotiation? */
	अगर (np->an_enable) अणु
		/* Advertise capabilities */
		esr = mii_पढ़ो (dev, phy_addr, PCS_ESR);
		anar = mii_पढ़ो (dev, phy_addr, MII_ADVERTISE) &
			~PCS_ANAR_HALF_DUPLEX &
			~PCS_ANAR_FULL_DUPLEX;
		अगर (esr & (MII_ESR_1000BT_HD | MII_ESR_1000BX_HD))
			anar |= PCS_ANAR_HALF_DUPLEX;
		अगर (esr & (MII_ESR_1000BT_FD | MII_ESR_1000BX_FD))
			anar |= PCS_ANAR_FULL_DUPLEX;
		anar |= PCS_ANAR_PAUSE | PCS_ANAR_ASYMMETRIC;
		mii_ग_लिखो (dev, phy_addr, MII_ADVERTISE, anar);

		/* Soft reset PHY */
		mii_ग_लिखो (dev, phy_addr, MII_BMCR, BMCR_RESET);
		bmcr = BMCR_ANENABLE | BMCR_ANRESTART | BMCR_RESET;
		mii_ग_लिखो (dev, phy_addr, MII_BMCR, bmcr);
		mdelay(1);
	पूर्ण अन्यथा अणु
		/* Force speed setting */
		/* PHY Reset */
		bmcr = BMCR_RESET;
		mii_ग_लिखो (dev, phy_addr, MII_BMCR, bmcr);
		mdelay(10);
		अगर (np->full_duplex) अणु
			bmcr = BMCR_FULLDPLX;
			prपूर्णांकk (KERN_INFO "Manual full duplex\n");
		पूर्ण अन्यथा अणु
			bmcr = 0;
			prपूर्णांकk (KERN_INFO "Manual half duplex\n");
		पूर्ण
		mii_ग_लिखो (dev, phy_addr, MII_BMCR, bmcr);
		mdelay(10);

		/*  Advertise nothing */
		mii_ग_लिखो (dev, phy_addr, MII_ADVERTISE, 0);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक
rio_बंद (काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	काष्ठा pci_dev *pdev = np->pdev;

	netअगर_stop_queue (dev);

	rio_hw_stop(dev);

	मुक्त_irq(pdev->irq, dev);
	del_समयr_sync (&np->समयr);

	मुक्त_list(dev);

	वापस 0;
पूर्ण

अटल व्योम
rio_हटाओ1 (काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata (pdev);

	अगर (dev) अणु
		काष्ठा netdev_निजी *np = netdev_priv(dev);

		unरेजिस्टर_netdev (dev);
		dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, np->rx_ring,
				  np->rx_ring_dma);
		dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, np->tx_ring,
				  np->tx_ring_dma);
#अगर_घोषित MEM_MAPPING
		pci_iounmap(pdev, np->ioaddr);
#पूर्ण_अगर
		pci_iounmap(pdev, np->eeprom_addr);
		मुक्त_netdev (dev);
		pci_release_regions (pdev);
		pci_disable_device (pdev);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rio_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_detach(dev);
	del_समयr_sync(&np->समयr);
	rio_hw_stop(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rio_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	rio_reset_ring(np);
	rio_hw_init(dev);
	np->समयr.expires = jअगरfies + 1 * HZ;
	add_समयr(&np->समयr);
	netअगर_device_attach(dev);
	dl2k_enable_पूर्णांक(np);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rio_pm_ops, rio_suspend, rio_resume);
#घोषणा RIO_PM_OPS    (&rio_pm_ops)

#अन्यथा

#घोषणा RIO_PM_OPS	शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver rio_driver = अणु
	.name		= "dl2k",
	.id_table	= rio_pci_tbl,
	.probe		= rio_probe1,
	.हटाओ		= rio_हटाओ1,
	.driver.pm	= RIO_PM_OPS,
पूर्ण;

module_pci_driver(rio_driver);

/* Read Documentation/networking/device_drivers/ethernet/dlink/dl2k.rst. */
