<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Network device driver क्रम Cell Processor-Based Blade and Celleb platक्रमm
 *
 * (C) Copyright IBM Corp. 2005
 * (C) Copyright 2006 TOSHIBA CORPORATION
 *
 * Authors : Utz Bacher <utz.bacher@de.ibm.com>
 *           Jens Osterkamp <Jens.Osterkamp@de.ibm.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/firmware.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gfp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <net/checksum.h>

#समावेश "spider_net.h"

MODULE_AUTHOR("Utz Bacher <utz.bacher@de.ibm.com> and Jens Osterkamp " \
	      "<Jens.Osterkamp@de.ibm.com>");
MODULE_DESCRIPTION("Spider Southbridge Gigabit Ethernet driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
MODULE_FIRMWARE(SPIDER_NET_FIRMWARE_NAME);

अटल पूर्णांक rx_descriptors = SPIDER_NET_RX_DESCRIPTORS_DEFAULT;
अटल पूर्णांक tx_descriptors = SPIDER_NET_TX_DESCRIPTORS_DEFAULT;

module_param(rx_descriptors, पूर्णांक, 0444);
module_param(tx_descriptors, पूर्णांक, 0444);

MODULE_PARM_DESC(rx_descriptors, "number of descriptors used " \
		 "in rx chains");
MODULE_PARM_DESC(tx_descriptors, "number of descriptors used " \
		 "in tx chain");

अक्षर spider_net_driver_name[] = "spidernet";

अटल स्थिर काष्ठा pci_device_id spider_net_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_TOSHIBA_2, PCI_DEVICE_ID_TOSHIBA_SPIDER_NET,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, spider_net_pci_tbl);

/**
 * spider_net_पढ़ो_reg - पढ़ोs an SMMIO रेजिस्टर of a card
 * @card: device काष्ठाure
 * @reg: रेजिस्टर to पढ़ो from
 *
 * वापसs the content of the specअगरied SMMIO रेजिस्टर.
 */
अटल अंतरभूत u32
spider_net_पढ़ो_reg(काष्ठा spider_net_card *card, u32 reg)
अणु
	/* We use the घातerpc specअगरic variants instead of पढ़ोl_be() because
	 * we know spidernet is not a real PCI device and we can thus aव्योम the
	 * perक्रमmance hit caused by the PCI workarounds.
	 */
	वापस in_be32(card->regs + reg);
पूर्ण

/**
 * spider_net_ग_लिखो_reg - ग_लिखोs to an SMMIO रेजिस्टर of a card
 * @card: device काष्ठाure
 * @reg: रेजिस्टर to ग_लिखो to
 * @value: value to ग_लिखो पूर्णांकo the specअगरied SMMIO रेजिस्टर
 */
अटल अंतरभूत व्योम
spider_net_ग_लिखो_reg(काष्ठा spider_net_card *card, u32 reg, u32 value)
अणु
	/* We use the घातerpc specअगरic variants instead of ग_लिखोl_be() because
	 * we know spidernet is not a real PCI device and we can thus aव्योम the
	 * perक्रमmance hit caused by the PCI workarounds.
	 */
	out_be32(card->regs + reg, value);
पूर्ण

/**
 * spider_net_ग_लिखो_phy - ग_लिखो to phy रेजिस्टर
 * @netdev: adapter to be written to
 * @mii_id: id of MII
 * @reg: PHY रेजिस्टर
 * @val: value to be written to phy रेजिस्टर
 *
 * spider_net_ग_लिखो_phy_रेजिस्टर ग_लिखोs to an arbitrary PHY
 * रेजिस्टर via the spider GPCWOPCMD रेजिस्टर. We assume the queue करोes
 * not run full (not more than 15 commands outstanding).
 **/
अटल व्योम
spider_net_ग_लिखो_phy(काष्ठा net_device *netdev, पूर्णांक mii_id,
		     पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा spider_net_card *card = netdev_priv(netdev);
	u32 ग_लिखोvalue;

	ग_लिखोvalue = ((u32)mii_id << 21) |
		((u32)reg << 16) | ((u32)val);

	spider_net_ग_लिखो_reg(card, SPIDER_NET_GPCWOPCMD, ग_लिखोvalue);
पूर्ण

/**
 * spider_net_पढ़ो_phy - पढ़ो from phy रेजिस्टर
 * @netdev: network device to be पढ़ो from
 * @mii_id: id of MII
 * @reg: PHY रेजिस्टर
 *
 * Returns value पढ़ो from PHY रेजिस्टर
 *
 * spider_net_ग_लिखो_phy पढ़ोs from an arbitrary PHY
 * रेजिस्टर via the spider GPCROPCMD रेजिस्टर
 **/
अटल पूर्णांक
spider_net_पढ़ो_phy(काष्ठा net_device *netdev, पूर्णांक mii_id, पूर्णांक reg)
अणु
	काष्ठा spider_net_card *card = netdev_priv(netdev);
	u32 पढ़ोvalue;

	पढ़ोvalue = ((u32)mii_id << 21) | ((u32)reg << 16);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GPCROPCMD, पढ़ोvalue);

	/* we करोn't use semaphores to रुको क्रम an SPIDER_NET_GPROPCMPINT
	 * पूर्णांकerrupt, as we poll क्रम the completion of the पढ़ो operation
	 * in spider_net_पढ़ो_phy. Should take about 50 us
	 */
	करो अणु
		पढ़ोvalue = spider_net_पढ़ो_reg(card, SPIDER_NET_GPCROPCMD);
	पूर्ण जबतक (पढ़ोvalue & SPIDER_NET_GPREXEC);

	पढ़ोvalue &= SPIDER_NET_GPRDAT_MASK;

	वापस पढ़ोvalue;
पूर्ण

/**
 * spider_net_setup_aneg - initial स्वतः-negotiation setup
 * @card: device काष्ठाure
 **/
अटल व्योम
spider_net_setup_aneg(काष्ठा spider_net_card *card)
अणु
	काष्ठा mii_phy *phy = &card->phy;
	u32 advertise = 0;
	u16 bmsr, estat;

	bmsr  = spider_net_पढ़ो_phy(card->netdev, phy->mii_id, MII_BMSR);
	estat = spider_net_पढ़ो_phy(card->netdev, phy->mii_id, MII_ESTATUS);

	अगर (bmsr & BMSR_10HALF)
		advertise |= ADVERTISED_10baseT_Half;
	अगर (bmsr & BMSR_10FULL)
		advertise |= ADVERTISED_10baseT_Full;
	अगर (bmsr & BMSR_100HALF)
		advertise |= ADVERTISED_100baseT_Half;
	अगर (bmsr & BMSR_100FULL)
		advertise |= ADVERTISED_100baseT_Full;

	अगर ((bmsr & BMSR_ESTATEN) && (estat & ESTATUS_1000_TFULL))
		advertise |= SUPPORTED_1000baseT_Full;
	अगर ((bmsr & BMSR_ESTATEN) && (estat & ESTATUS_1000_THALF))
		advertise |= SUPPORTED_1000baseT_Half;

	sungem_phy_probe(phy, phy->mii_id);
	phy->def->ops->setup_aneg(phy, advertise);

पूर्ण

/**
 * spider_net_rx_irq_off - चयन off rx irq on this spider card
 * @card: device काष्ठाure
 *
 * चयनes off rx irq by masking them out in the GHIINTnMSK रेजिस्टर
 */
अटल व्योम
spider_net_rx_irq_off(काष्ठा spider_net_card *card)
अणु
	u32 regvalue;

	regvalue = SPIDER_NET_INT0_MASK_VALUE & (~SPIDER_NET_RXINT);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT0MSK, regvalue);
पूर्ण

/**
 * spider_net_rx_irq_on - चयन on rx irq on this spider card
 * @card: device काष्ठाure
 *
 * चयनes on rx irq by enabling them in the GHIINTnMSK रेजिस्टर
 */
अटल व्योम
spider_net_rx_irq_on(काष्ठा spider_net_card *card)
अणु
	u32 regvalue;

	regvalue = SPIDER_NET_INT0_MASK_VALUE | SPIDER_NET_RXINT;
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT0MSK, regvalue);
पूर्ण

/**
 * spider_net_set_promisc - sets the unicast address or the promiscuous mode
 * @card: card काष्ठाure
 *
 * spider_net_set_promisc sets the unicast destination address filter and
 * thus either allows क्रम non-promisc mode or promisc mode
 */
अटल व्योम
spider_net_set_promisc(काष्ठा spider_net_card *card)
अणु
	u32 macu, macl;
	काष्ठा net_device *netdev = card->netdev;

	अगर (netdev->flags & IFF_PROMISC) अणु
		/* clear destination entry 0 */
		spider_net_ग_लिखो_reg(card, SPIDER_NET_GMRUAFILnR, 0);
		spider_net_ग_लिखो_reg(card, SPIDER_NET_GMRUAFILnR + 0x04, 0);
		spider_net_ग_लिखो_reg(card, SPIDER_NET_GMRUA0FIL15R,
				     SPIDER_NET_PROMISC_VALUE);
	पूर्ण अन्यथा अणु
		macu = netdev->dev_addr[0];
		macu <<= 8;
		macu |= netdev->dev_addr[1];
		स_नकल(&macl, &netdev->dev_addr[2], माप(macl));

		macu |= SPIDER_NET_UA_DESCR_VALUE;
		spider_net_ग_लिखो_reg(card, SPIDER_NET_GMRUAFILnR, macu);
		spider_net_ग_लिखो_reg(card, SPIDER_NET_GMRUAFILnR + 0x04, macl);
		spider_net_ग_लिखो_reg(card, SPIDER_NET_GMRUA0FIL15R,
				     SPIDER_NET_NONPROMISC_VALUE);
	पूर्ण
पूर्ण

/**
 * spider_net_get_descr_status -- वापसs the status of a descriptor
 * @hwdescr: descriptor to look at
 *
 * वापसs the status as in the dmac_cmd_status field of the descriptor
 */
अटल अंतरभूत पूर्णांक
spider_net_get_descr_status(काष्ठा spider_net_hw_descr *hwdescr)
अणु
	वापस hwdescr->dmac_cmd_status & SPIDER_NET_DESCR_IND_PROC_MASK;
पूर्ण

/**
 * spider_net_मुक्त_chain - मुक्त descriptor chain
 * @card: card काष्ठाure
 * @chain: address of chain
 *
 */
अटल व्योम
spider_net_मुक्त_chain(काष्ठा spider_net_card *card,
		      काष्ठा spider_net_descr_chain *chain)
अणु
	काष्ठा spider_net_descr *descr;

	descr = chain->ring;
	करो अणु
		descr->bus_addr = 0;
		descr->hwdescr->next_descr_addr = 0;
		descr = descr->next;
	पूर्ण जबतक (descr != chain->ring);

	dma_मुक्त_coherent(&card->pdev->dev, chain->num_desc * माप(काष्ठा spider_net_hw_descr),
			  chain->hwring, chain->dma_addr);
पूर्ण

/**
 * spider_net_init_chain - alloc and link descriptor chain
 * @card: card काष्ठाure
 * @chain: address of chain
 *
 * We manage a circular list that mirrors the hardware काष्ठाure,
 * except that the hardware uses bus addresses.
 *
 * Returns 0 on success, <0 on failure
 */
अटल पूर्णांक
spider_net_init_chain(काष्ठा spider_net_card *card,
		       काष्ठा spider_net_descr_chain *chain)
अणु
	पूर्णांक i;
	काष्ठा spider_net_descr *descr;
	काष्ठा spider_net_hw_descr *hwdescr;
	dma_addr_t buf;
	माप_प्रकार alloc_size;

	alloc_size = chain->num_desc * माप(काष्ठा spider_net_hw_descr);

	chain->hwring = dma_alloc_coherent(&card->pdev->dev, alloc_size,
					   &chain->dma_addr, GFP_KERNEL);
	अगर (!chain->hwring)
		वापस -ENOMEM;

	/* Set up the hardware poपूर्णांकers in each descriptor */
	descr = chain->ring;
	hwdescr = chain->hwring;
	buf = chain->dma_addr;
	क्रम (i=0; i < chain->num_desc; i++, descr++, hwdescr++) अणु
		hwdescr->dmac_cmd_status = SPIDER_NET_DESCR_NOT_IN_USE;
		hwdescr->next_descr_addr = 0;

		descr->hwdescr = hwdescr;
		descr->bus_addr = buf;
		descr->next = descr + 1;
		descr->prev = descr - 1;

		buf += माप(काष्ठा spider_net_hw_descr);
	पूर्ण
	/* करो actual circular list */
	(descr-1)->next = chain->ring;
	chain->ring->prev = descr-1;

	spin_lock_init(&chain->lock);
	chain->head = chain->ring;
	chain->tail = chain->ring;
	वापस 0;
पूर्ण

/**
 * spider_net_मुक्त_rx_chain_contents - मुक्तs descr contents in rx chain
 * @card: card काष्ठाure
 *
 * वापसs 0 on success, <0 on failure
 */
अटल व्योम
spider_net_मुक्त_rx_chain_contents(काष्ठा spider_net_card *card)
अणु
	काष्ठा spider_net_descr *descr;

	descr = card->rx_chain.head;
	करो अणु
		अगर (descr->skb) अणु
			pci_unmap_single(card->pdev, descr->hwdescr->buf_addr,
					 SPIDER_NET_MAX_FRAME,
					 PCI_DMA_BIसूचीECTIONAL);
			dev_kमुक्त_skb(descr->skb);
			descr->skb = शून्य;
		पूर्ण
		descr = descr->next;
	पूर्ण जबतक (descr != card->rx_chain.head);
पूर्ण

/**
 * spider_net_prepare_rx_descr - Reinitialize RX descriptor
 * @card: card काष्ठाure
 * @descr: descriptor to re-init
 *
 * Return 0 on success, <0 on failure.
 *
 * Allocates a new rx skb, iommu-maps it and attaches it to the
 * descriptor. Mark the descriptor as activated, पढ़ोy-to-use.
 */
अटल पूर्णांक
spider_net_prepare_rx_descr(काष्ठा spider_net_card *card,
			    काष्ठा spider_net_descr *descr)
अणु
	काष्ठा spider_net_hw_descr *hwdescr = descr->hwdescr;
	dma_addr_t buf;
	पूर्णांक offset;
	पूर्णांक bufsize;

	/* we need to round up the buffer size to a multiple of 128 */
	bufsize = (SPIDER_NET_MAX_FRAME + SPIDER_NET_RXBUF_ALIGN - 1) &
		(~(SPIDER_NET_RXBUF_ALIGN - 1));

	/* and we need to have it 128 byte aligned, thereक्रमe we allocate a
	 * bit more
	 */
	/* allocate an skb */
	descr->skb = netdev_alloc_skb(card->netdev,
				      bufsize + SPIDER_NET_RXBUF_ALIGN - 1);
	अगर (!descr->skb) अणु
		अगर (netअगर_msg_rx_err(card) && net_ratelimit())
			dev_err(&card->netdev->dev,
			        "Not enough memory to allocate rx buffer\n");
		card->spider_stats.alloc_rx_skb_error++;
		वापस -ENOMEM;
	पूर्ण
	hwdescr->buf_size = bufsize;
	hwdescr->result_size = 0;
	hwdescr->valid_size = 0;
	hwdescr->data_status = 0;
	hwdescr->data_error = 0;

	offset = ((अचिन्हित दीर्घ)descr->skb->data) &
		(SPIDER_NET_RXBUF_ALIGN - 1);
	अगर (offset)
		skb_reserve(descr->skb, SPIDER_NET_RXBUF_ALIGN - offset);
	/* iommu-map the skb */
	buf = pci_map_single(card->pdev, descr->skb->data,
			SPIDER_NET_MAX_FRAME, PCI_DMA_FROMDEVICE);
	अगर (pci_dma_mapping_error(card->pdev, buf)) अणु
		dev_kमुक्त_skb_any(descr->skb);
		descr->skb = शून्य;
		अगर (netअगर_msg_rx_err(card) && net_ratelimit())
			dev_err(&card->netdev->dev, "Could not iommu-map rx buffer\n");
		card->spider_stats.rx_iommu_map_error++;
		hwdescr->dmac_cmd_status = SPIDER_NET_DESCR_NOT_IN_USE;
	पूर्ण अन्यथा अणु
		hwdescr->buf_addr = buf;
		wmb();
		hwdescr->dmac_cmd_status = SPIDER_NET_DESCR_CARDOWNED |
					 SPIDER_NET_DMAC_NOINTR_COMPLETE;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spider_net_enable_rxchtails - sets RX dmac chain tail addresses
 * @card: card काष्ठाure
 *
 * spider_net_enable_rxchtails sets the RX DMAC chain tail addresses in the
 * chip by writing to the appropriate रेजिस्टर. DMA is enabled in
 * spider_net_enable_rxdmac.
 */
अटल अंतरभूत व्योम
spider_net_enable_rxchtails(काष्ठा spider_net_card *card)
अणु
	/* assume chain is aligned correctly */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GDADCHA ,
			     card->rx_chain.tail->bus_addr);
पूर्ण

/**
 * spider_net_enable_rxdmac - enables a receive DMA controller
 * @card: card काष्ठाure
 *
 * spider_net_enable_rxdmac enables the DMA controller by setting RX_DMA_EN
 * in the GDADMACCNTR रेजिस्टर
 */
अटल अंतरभूत व्योम
spider_net_enable_rxdmac(काष्ठा spider_net_card *card)
अणु
	wmb();
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GDADMACCNTR,
			     SPIDER_NET_DMA_RX_VALUE);
पूर्ण

/**
 * spider_net_disable_rxdmac - disables the receive DMA controller
 * @card: card काष्ठाure
 *
 * spider_net_disable_rxdmac terminates processing on the DMA controller
 * by turing off the DMA controller, with the क्रमce-end flag set.
 */
अटल अंतरभूत व्योम
spider_net_disable_rxdmac(काष्ठा spider_net_card *card)
अणु
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GDADMACCNTR,
			     SPIDER_NET_DMA_RX_FEND_VALUE);
पूर्ण

/**
 * spider_net_refill_rx_chain - refills descriptors/skbs in the rx chains
 * @card: card काष्ठाure
 *
 * refills descriptors in the rx chain: allocates skbs and iommu-maps them.
 */
अटल व्योम
spider_net_refill_rx_chain(काष्ठा spider_net_card *card)
अणु
	काष्ठा spider_net_descr_chain *chain = &card->rx_chain;
	अचिन्हित दीर्घ flags;

	/* one context करोing the refill (and a second context seeing that
	 * and omitting it) is ok. If called by NAPI, we'll be called again
	 * as spider_net_decode_one_descr is called several बार. If some
	 * पूर्णांकerrupt calls us, the NAPI is about to clean up anyway.
	 */
	अगर (!spin_trylock_irqsave(&chain->lock, flags))
		वापस;

	जबतक (spider_net_get_descr_status(chain->head->hwdescr) ==
			SPIDER_NET_DESCR_NOT_IN_USE) अणु
		अगर (spider_net_prepare_rx_descr(card, chain->head))
			अवरोध;
		chain->head = chain->head->next;
	पूर्ण

	spin_unlock_irqrestore(&chain->lock, flags);
पूर्ण

/**
 * spider_net_alloc_rx_skbs - Allocates rx skbs in rx descriptor chains
 * @card: card काष्ठाure
 *
 * Returns 0 on success, <0 on failure.
 */
अटल पूर्णांक
spider_net_alloc_rx_skbs(काष्ठा spider_net_card *card)
अणु
	काष्ठा spider_net_descr_chain *chain = &card->rx_chain;
	काष्ठा spider_net_descr *start = chain->tail;
	काष्ठा spider_net_descr *descr = start;

	/* Link up the hardware chain poपूर्णांकers */
	करो अणु
		descr->prev->hwdescr->next_descr_addr = descr->bus_addr;
		descr = descr->next;
	पूर्ण जबतक (descr != start);

	/* Put at least one buffer पूर्णांकo the chain. अगर this fails,
	 * we've got a problem. If not, spider_net_refill_rx_chain
	 * will करो the rest at the end of this function.
	 */
	अगर (spider_net_prepare_rx_descr(card, chain->head))
		जाओ error;
	अन्यथा
		chain->head = chain->head->next;

	/* This will allocate the rest of the rx buffers;
	 * अगर not, it's business as usual later on.
	 */
	spider_net_refill_rx_chain(card);
	spider_net_enable_rxdmac(card);
	वापस 0;

error:
	spider_net_मुक्त_rx_chain_contents(card);
	वापस -ENOMEM;
पूर्ण

/**
 * spider_net_get_multicast_hash - generates hash क्रम multicast filter table
 * @netdev: पूर्णांकerface device काष्ठाure
 * @addr: multicast address
 *
 * वापसs the hash value.
 *
 * spider_net_get_multicast_hash calculates a hash value क्रम a given multicast
 * address, that is used to set the multicast filter tables
 */
अटल u8
spider_net_get_multicast_hash(काष्ठा net_device *netdev, __u8 *addr)
अणु
	u32 crc;
	u8 hash;
	अक्षर addr_क्रम_crc[ETH_ALEN] = अणु 0, पूर्ण;
	पूर्णांक i, bit;

	क्रम (i = 0; i < ETH_ALEN * 8; i++) अणु
		bit = (addr[i / 8] >> (i % 8)) & 1;
		addr_क्रम_crc[ETH_ALEN - 1 - i / 8] += bit << (7 - (i % 8));
	पूर्ण

	crc = crc32_be(~0, addr_क्रम_crc, netdev->addr_len);

	hash = (crc >> 27);
	hash <<= 3;
	hash |= crc & 7;
	hash &= 0xff;

	वापस hash;
पूर्ण

/**
 * spider_net_set_multi - sets multicast addresses and promisc flags
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * spider_net_set_multi configures multicast addresses as needed क्रम the
 * netdev पूर्णांकerface. It also sets up multicast, allmulti and promisc
 * flags appropriately
 */
अटल व्योम
spider_net_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा netdev_hw_addr *ha;
	u8 hash;
	पूर्णांक i;
	u32 reg;
	काष्ठा spider_net_card *card = netdev_priv(netdev);
	DECLARE_BITMAP(biपंचांगask, SPIDER_NET_MULTICAST_HASHES) = अणुपूर्ण;

	spider_net_set_promisc(card);

	अगर (netdev->flags & IFF_ALLMULTI) अणु
		क्रम (i = 0; i < SPIDER_NET_MULTICAST_HASHES; i++) अणु
			set_bit(i, biपंचांगask);
		पूर्ण
		जाओ ग_लिखो_hash;
	पूर्ण

	/* well, we know, what the broadcast hash value is: it's xfd
	hash = spider_net_get_multicast_hash(netdev, netdev->broadcast); */
	set_bit(0xfd, biपंचांगask);

	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		hash = spider_net_get_multicast_hash(netdev, ha->addr);
		set_bit(hash, biपंचांगask);
	पूर्ण

ग_लिखो_hash:
	क्रम (i = 0; i < SPIDER_NET_MULTICAST_HASHES / 4; i++) अणु
		reg = 0;
		अगर (test_bit(i * 4, biपंचांगask))
			reg += 0x08;
		reg <<= 8;
		अगर (test_bit(i * 4 + 1, biपंचांगask))
			reg += 0x08;
		reg <<= 8;
		अगर (test_bit(i * 4 + 2, biपंचांगask))
			reg += 0x08;
		reg <<= 8;
		अगर (test_bit(i * 4 + 3, biपंचांगask))
			reg += 0x08;

		spider_net_ग_लिखो_reg(card, SPIDER_NET_GMRMHFILnR + i * 4, reg);
	पूर्ण
पूर्ण

/**
 * spider_net_prepare_tx_descr - fill tx descriptor with skb data
 * @card: card काष्ठाure
 * @skb: packet to use
 *
 * वापसs 0 on success, <0 on failure.
 *
 * fills out the descriptor काष्ठाure with skb data and len. Copies data,
 * अगर needed (32bit DMA!)
 */
अटल पूर्णांक
spider_net_prepare_tx_descr(काष्ठा spider_net_card *card,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा spider_net_descr_chain *chain = &card->tx_chain;
	काष्ठा spider_net_descr *descr;
	काष्ठा spider_net_hw_descr *hwdescr;
	dma_addr_t buf;
	अचिन्हित दीर्घ flags;

	buf = pci_map_single(card->pdev, skb->data, skb->len, PCI_DMA_TODEVICE);
	अगर (pci_dma_mapping_error(card->pdev, buf)) अणु
		अगर (netअगर_msg_tx_err(card) && net_ratelimit())
			dev_err(&card->netdev->dev, "could not iommu-map packet (%p, %i). "
				  "Dropping packet\n", skb->data, skb->len);
		card->spider_stats.tx_iommu_map_error++;
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&chain->lock, flags);
	descr = card->tx_chain.head;
	अगर (descr->next == chain->tail->prev) अणु
		spin_unlock_irqrestore(&chain->lock, flags);
		pci_unmap_single(card->pdev, buf, skb->len, PCI_DMA_TODEVICE);
		वापस -ENOMEM;
	पूर्ण
	hwdescr = descr->hwdescr;
	chain->head = descr->next;

	descr->skb = skb;
	hwdescr->buf_addr = buf;
	hwdescr->buf_size = skb->len;
	hwdescr->next_descr_addr = 0;
	hwdescr->data_status = 0;

	hwdescr->dmac_cmd_status =
			SPIDER_NET_DESCR_CARDOWNED | SPIDER_NET_DMAC_TXFRMTL;
	spin_unlock_irqrestore(&chain->lock, flags);

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		चयन (ip_hdr(skb)->protocol) अणु
		हाल IPPROTO_TCP:
			hwdescr->dmac_cmd_status |= SPIDER_NET_DMAC_TCP;
			अवरोध;
		हाल IPPROTO_UDP:
			hwdescr->dmac_cmd_status |= SPIDER_NET_DMAC_UDP;
			अवरोध;
		पूर्ण

	/* Chain the bus address, so that the DMA engine finds this descr. */
	wmb();
	descr->prev->hwdescr->next_descr_addr = descr->bus_addr;

	netअगर_trans_update(card->netdev); /* set netdev watchकरोg समयr */
	वापस 0;
पूर्ण

अटल पूर्णांक
spider_net_set_low_watermark(काष्ठा spider_net_card *card)
अणु
	काष्ठा spider_net_descr *descr = card->tx_chain.tail;
	काष्ठा spider_net_hw_descr *hwdescr;
	अचिन्हित दीर्घ flags;
	पूर्णांक status;
	पूर्णांक cnt=0;
	पूर्णांक i;

	/* Measure the length of the queue. Measurement करोes not
	 * need to be precise -- करोes not need a lock.
	 */
	जबतक (descr != card->tx_chain.head) अणु
		status = descr->hwdescr->dmac_cmd_status & SPIDER_NET_DESCR_NOT_IN_USE;
		अगर (status == SPIDER_NET_DESCR_NOT_IN_USE)
			अवरोध;
		descr = descr->next;
		cnt++;
	पूर्ण

	/* If TX queue is लघु, करोn't even bother with पूर्णांकerrupts */
	अगर (cnt < card->tx_chain.num_desc/4)
		वापस cnt;

	/* Set low-watermark 3/4th's of the way पूर्णांकo the queue. */
	descr = card->tx_chain.tail;
	cnt = (cnt*3)/4;
	क्रम (i=0;i<cnt; i++)
		descr = descr->next;

	/* Set the new watermark, clear the old watermark */
	spin_lock_irqsave(&card->tx_chain.lock, flags);
	descr->hwdescr->dmac_cmd_status |= SPIDER_NET_DESCR_TXDESFLG;
	अगर (card->low_watermark && card->low_watermark != descr) अणु
		hwdescr = card->low_watermark->hwdescr;
		hwdescr->dmac_cmd_status =
		     hwdescr->dmac_cmd_status & ~SPIDER_NET_DESCR_TXDESFLG;
	पूर्ण
	card->low_watermark = descr;
	spin_unlock_irqrestore(&card->tx_chain.lock, flags);
	वापस cnt;
पूर्ण

/**
 * spider_net_release_tx_chain - processes sent tx descriptors
 * @card: adapter काष्ठाure
 * @brutal: अगर set, करोn't care about whether descriptor seems to be in use
 *
 * वापसs 0 अगर the tx ring is empty, otherwise 1.
 *
 * spider_net_release_tx_chain releases the tx descriptors that spider has
 * finished with (अगर non-brutal) or simply release tx descriptors (अगर brutal).
 * If some other context is calling this function, we वापस 1 so that we're
 * scheduled again (अगर we were scheduled) and will not lose initiative.
 */
अटल पूर्णांक
spider_net_release_tx_chain(काष्ठा spider_net_card *card, पूर्णांक brutal)
अणु
	काष्ठा net_device *dev = card->netdev;
	काष्ठा spider_net_descr_chain *chain = &card->tx_chain;
	काष्ठा spider_net_descr *descr;
	काष्ठा spider_net_hw_descr *hwdescr;
	काष्ठा sk_buff *skb;
	u32 buf_addr;
	अचिन्हित दीर्घ flags;
	पूर्णांक status;

	जबतक (1) अणु
		spin_lock_irqsave(&chain->lock, flags);
		अगर (chain->tail == chain->head) अणु
			spin_unlock_irqrestore(&chain->lock, flags);
			वापस 0;
		पूर्ण
		descr = chain->tail;
		hwdescr = descr->hwdescr;

		status = spider_net_get_descr_status(hwdescr);
		चयन (status) अणु
		हाल SPIDER_NET_DESCR_COMPLETE:
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += descr->skb->len;
			अवरोध;

		हाल SPIDER_NET_DESCR_CARDOWNED:
			अगर (!brutal) अणु
				spin_unlock_irqrestore(&chain->lock, flags);
				वापस 1;
			पूर्ण

			/* fallthrough, अगर we release the descriptors
			 * brutally (then we करोn't care about
			 * SPIDER_NET_DESCR_CARDOWNED)
			 */
			fallthrough;

		हाल SPIDER_NET_DESCR_RESPONSE_ERROR:
		हाल SPIDER_NET_DESCR_PROTECTION_ERROR:
		हाल SPIDER_NET_DESCR_FORCE_END:
			अगर (netअगर_msg_tx_err(card))
				dev_err(&card->netdev->dev, "forcing end of tx descriptor "
				       "with status x%02x\n", status);
			dev->stats.tx_errors++;
			अवरोध;

		शेष:
			dev->stats.tx_dropped++;
			अगर (!brutal) अणु
				spin_unlock_irqrestore(&chain->lock, flags);
				वापस 1;
			पूर्ण
		पूर्ण

		chain->tail = descr->next;
		hwdescr->dmac_cmd_status |= SPIDER_NET_DESCR_NOT_IN_USE;
		skb = descr->skb;
		descr->skb = शून्य;
		buf_addr = hwdescr->buf_addr;
		spin_unlock_irqrestore(&chain->lock, flags);

		/* unmap the skb */
		अगर (skb) अणु
			pci_unmap_single(card->pdev, buf_addr, skb->len,
					PCI_DMA_TODEVICE);
			dev_consume_skb_any(skb);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * spider_net_kick_tx_dma - enables TX DMA processing
 * @card: card काष्ठाure
 *
 * This routine will start the transmit DMA running अगर
 * it is not alपढ़ोy running. This routine ned only be
 * called when queueing a new packet to an empty tx queue.
 * Writes the current tx chain head as start address
 * of the tx descriptor chain and enables the transmission
 * DMA engine.
 */
अटल अंतरभूत व्योम
spider_net_kick_tx_dma(काष्ठा spider_net_card *card)
अणु
	काष्ठा spider_net_descr *descr;

	अगर (spider_net_पढ़ो_reg(card, SPIDER_NET_GDTDMACCNTR) &
			SPIDER_NET_TX_DMA_EN)
		जाओ out;

	descr = card->tx_chain.tail;
	क्रम (;;) अणु
		अगर (spider_net_get_descr_status(descr->hwdescr) ==
				SPIDER_NET_DESCR_CARDOWNED) अणु
			spider_net_ग_लिखो_reg(card, SPIDER_NET_GDTDCHA,
					descr->bus_addr);
			spider_net_ग_लिखो_reg(card, SPIDER_NET_GDTDMACCNTR,
					SPIDER_NET_DMA_TX_VALUE);
			अवरोध;
		पूर्ण
		अगर (descr == card->tx_chain.head)
			अवरोध;
		descr = descr->next;
	पूर्ण

out:
	mod_समयr(&card->tx_समयr, jअगरfies + SPIDER_NET_TX_TIMER);
पूर्ण

/**
 * spider_net_xmit - transmits a frame over the device
 * @skb: packet to send out
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * वापसs NETDEV_TX_OK on success, NETDEV_TX_BUSY on failure
 */
अटल netdev_tx_t
spider_net_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	पूर्णांक cnt;
	काष्ठा spider_net_card *card = netdev_priv(netdev);

	spider_net_release_tx_chain(card, 0);

	अगर (spider_net_prepare_tx_descr(card, skb) != 0) अणु
		netdev->stats.tx_dropped++;
		netअगर_stop_queue(netdev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	cnt = spider_net_set_low_watermark(card);
	अगर (cnt < 5)
		spider_net_kick_tx_dma(card);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * spider_net_cleanup_tx_ring - cleans up the TX ring
 * @t: समयr context used to obtain the poपूर्णांकer to net card data काष्ठाure
 *
 * spider_net_cleanup_tx_ring is called by either the tx_समयr
 * or from the NAPI polling routine.
 * This routine releases resources associted with transmitted
 * packets, including updating the queue tail poपूर्णांकer.
 */
अटल व्योम
spider_net_cleanup_tx_ring(काष्ठा समयr_list *t)
अणु
	काष्ठा spider_net_card *card = from_समयr(card, t, tx_समयr);
	अगर ((spider_net_release_tx_chain(card, 0) != 0) &&
	    (card->netdev->flags & IFF_UP)) अणु
		spider_net_kick_tx_dma(card);
		netअगर_wake_queue(card->netdev);
	पूर्ण
पूर्ण

/**
 * spider_net_करो_ioctl - called क्रम device ioctls
 * @netdev: पूर्णांकerface device काष्ठाure
 * @अगरr: request parameter काष्ठाure क्रम ioctl
 * @cmd: command code क्रम ioctl
 *
 * वापसs 0 on success, <0 on failure. Currently, we have no special ioctls.
 * -EOPNOTSUPP is वापसed, अगर an unknown ioctl was requested
 */
अटल पूर्णांक
spider_net_करो_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * spider_net_pass_skb_up - takes an skb from a descriptor and passes it on
 * @descr: descriptor to process
 * @card: card काष्ठाure
 *
 * Fills out skb काष्ठाure and passes the data to the stack.
 * The descriptor state is not changed.
 */
अटल व्योम
spider_net_pass_skb_up(काष्ठा spider_net_descr *descr,
		       काष्ठा spider_net_card *card)
अणु
	काष्ठा spider_net_hw_descr *hwdescr = descr->hwdescr;
	काष्ठा sk_buff *skb = descr->skb;
	काष्ठा net_device *netdev = card->netdev;
	u32 data_status = hwdescr->data_status;
	u32 data_error = hwdescr->data_error;

	skb_put(skb, hwdescr->valid_size);

	/* the card seems to add 2 bytes of junk in front
	 * of the ethernet frame
	 */
#घोषणा SPIDER_MISALIGN		2
	skb_pull(skb, SPIDER_MISALIGN);
	skb->protocol = eth_type_trans(skb, netdev);

	/* checksum offload */
	skb_checksum_none_निश्चित(skb);
	अगर (netdev->features & NETIF_F_RXCSUM) अणु
		अगर ( ( (data_status & SPIDER_NET_DATA_STATUS_CKSUM_MASK) ==
		       SPIDER_NET_DATA_STATUS_CKSUM_MASK) &&
		     !(data_error & SPIDER_NET_DATA_ERR_CKSUM_MASK))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	अगर (data_status & SPIDER_NET_VLAN_PACKET) अणु
		/* further enhancements: HW-accel VLAN */
	पूर्ण

	/* update netdevice statistics */
	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += skb->len;

	/* pass skb up to stack */
	netअगर_receive_skb(skb);
पूर्ण

अटल व्योम show_rx_chain(काष्ठा spider_net_card *card)
अणु
	काष्ठा spider_net_descr_chain *chain = &card->rx_chain;
	काष्ठा spider_net_descr *start= chain->tail;
	काष्ठा spider_net_descr *descr= start;
	काष्ठा spider_net_hw_descr *hwd = start->hwdescr;
	काष्ठा device *dev = &card->netdev->dev;
	u32 curr_desc, next_desc;
	पूर्णांक status;

	पूर्णांक tot = 0;
	पूर्णांक cnt = 0;
	पूर्णांक off = start - chain->ring;
	पूर्णांक cstat = hwd->dmac_cmd_status;

	dev_info(dev, "Total number of descrs=%d\n",
		chain->num_desc);
	dev_info(dev, "Chain tail located at descr=%d, status=0x%x\n",
		off, cstat);

	curr_desc = spider_net_पढ़ो_reg(card, SPIDER_NET_GDACTDPA);
	next_desc = spider_net_पढ़ो_reg(card, SPIDER_NET_GDACNEXTDA);

	status = cstat;
	करो
	अणु
		hwd = descr->hwdescr;
		off = descr - chain->ring;
		status = hwd->dmac_cmd_status;

		अगर (descr == chain->head)
			dev_info(dev, "Chain head is at %d, head status=0x%x\n",
			         off, status);

		अगर (curr_desc == descr->bus_addr)
			dev_info(dev, "HW curr desc (GDACTDPA) is at %d, status=0x%x\n",
			         off, status);

		अगर (next_desc == descr->bus_addr)
			dev_info(dev, "HW next desc (GDACNEXTDA) is at %d, status=0x%x\n",
			         off, status);

		अगर (hwd->next_descr_addr == 0)
			dev_info(dev, "chain is cut at %d\n", off);

		अगर (cstat != status) अणु
			पूर्णांक from = (chain->num_desc + off - cnt) % chain->num_desc;
			पूर्णांक to = (chain->num_desc + off - 1) % chain->num_desc;
			dev_info(dev, "Have %d (from %d to %d) descrs "
			         "with stat=0x%08x\n", cnt, from, to, cstat);
			cstat = status;
			cnt = 0;
		पूर्ण

		cnt ++;
		tot ++;
		descr = descr->next;
	पूर्ण जबतक (descr != start);

	dev_info(dev, "Last %d descrs with stat=0x%08x "
	         "for a total of %d descrs\n", cnt, cstat, tot);

#अगर_घोषित DEBUG
	/* Now dump the whole ring */
	descr = start;
	करो
	अणु
		काष्ठा spider_net_hw_descr *hwd = descr->hwdescr;
		status = spider_net_get_descr_status(hwd);
		cnt = descr - chain->ring;
		dev_info(dev, "Descr %d stat=0x%08x skb=%p\n",
		         cnt, status, descr->skb);
		dev_info(dev, "bus addr=%08x buf addr=%08x sz=%d\n",
		         descr->bus_addr, hwd->buf_addr, hwd->buf_size);
		dev_info(dev, "next=%08x result sz=%d valid sz=%d\n",
		         hwd->next_descr_addr, hwd->result_size,
		         hwd->valid_size);
		dev_info(dev, "dmac=%08x data stat=%08x data err=%08x\n",
		         hwd->dmac_cmd_status, hwd->data_status,
		         hwd->data_error);
		dev_info(dev, "\n");

		descr = descr->next;
	पूर्ण जबतक (descr != start);
#पूर्ण_अगर

पूर्ण

/**
 * spider_net_resync_head_ptr - Advance head ptr past empty descrs
 * @card: card काष्ठाure
 *
 * If the driver fails to keep up and empty the queue, then the
 * hardware wil run out of room to put incoming packets. This
 * will cause the hardware to skip descrs that are full (instead
 * of halting/retrying). Thus, once the driver runs, it wil need
 * to "catch up" to where the hardware chain poपूर्णांकer is at.
 */
अटल व्योम spider_net_resync_head_ptr(काष्ठा spider_net_card *card)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा spider_net_descr_chain *chain = &card->rx_chain;
	काष्ठा spider_net_descr *descr;
	पूर्णांक i, status;

	/* Advance head poपूर्णांकer past any empty descrs */
	descr = chain->head;
	status = spider_net_get_descr_status(descr->hwdescr);

	अगर (status == SPIDER_NET_DESCR_NOT_IN_USE)
		वापस;

	spin_lock_irqsave(&chain->lock, flags);

	descr = chain->head;
	status = spider_net_get_descr_status(descr->hwdescr);
	क्रम (i=0; i<chain->num_desc; i++) अणु
		अगर (status != SPIDER_NET_DESCR_CARDOWNED) अवरोध;
		descr = descr->next;
		status = spider_net_get_descr_status(descr->hwdescr);
	पूर्ण
	chain->head = descr;

	spin_unlock_irqrestore(&chain->lock, flags);
पूर्ण

अटल पूर्णांक spider_net_resync_tail_ptr(काष्ठा spider_net_card *card)
अणु
	काष्ठा spider_net_descr_chain *chain = &card->rx_chain;
	काष्ठा spider_net_descr *descr;
	पूर्णांक i, status;

	/* Advance tail poपूर्णांकer past any empty and reaped descrs */
	descr = chain->tail;
	status = spider_net_get_descr_status(descr->hwdescr);

	क्रम (i=0; i<chain->num_desc; i++) अणु
		अगर ((status != SPIDER_NET_DESCR_CARDOWNED) &&
		    (status != SPIDER_NET_DESCR_NOT_IN_USE)) अवरोध;
		descr = descr->next;
		status = spider_net_get_descr_status(descr->hwdescr);
	पूर्ण
	chain->tail = descr;

	अगर ((i == chain->num_desc) || (i == 0))
		वापस 1;
	वापस 0;
पूर्ण

/**
 * spider_net_decode_one_descr - processes an RX descriptor
 * @card: card काष्ठाure
 *
 * Returns 1 अगर a packet has been sent to the stack, otherwise 0.
 *
 * Processes an RX descriptor by iommu-unmapping the data buffer
 * and passing the packet up to the stack. This function is called
 * in softirq context, e.g. either bottom half from पूर्णांकerrupt or
 * NAPI polling context.
 */
अटल पूर्णांक
spider_net_decode_one_descr(काष्ठा spider_net_card *card)
अणु
	काष्ठा net_device *dev = card->netdev;
	काष्ठा spider_net_descr_chain *chain = &card->rx_chain;
	काष्ठा spider_net_descr *descr = chain->tail;
	काष्ठा spider_net_hw_descr *hwdescr = descr->hwdescr;
	u32 hw_buf_addr;
	पूर्णांक status;

	status = spider_net_get_descr_status(hwdescr);

	/* Nothing in the descriptor, or ring must be empty */
	अगर ((status == SPIDER_NET_DESCR_CARDOWNED) ||
	    (status == SPIDER_NET_DESCR_NOT_IN_USE))
		वापस 0;

	/* descriptor definitively used -- move on tail */
	chain->tail = descr->next;

	/* unmap descriptor */
	hw_buf_addr = hwdescr->buf_addr;
	hwdescr->buf_addr = 0xffffffff;
	pci_unmap_single(card->pdev, hw_buf_addr,
			SPIDER_NET_MAX_FRAME, PCI_DMA_FROMDEVICE);

	अगर ( (status == SPIDER_NET_DESCR_RESPONSE_ERROR) ||
	     (status == SPIDER_NET_DESCR_PROTECTION_ERROR) ||
	     (status == SPIDER_NET_DESCR_FORCE_END) ) अणु
		अगर (netअगर_msg_rx_err(card))
			dev_err(&dev->dev,
			       "dropping RX descriptor with state %d\n", status);
		dev->stats.rx_dropped++;
		जाओ bad_desc;
	पूर्ण

	अगर ( (status != SPIDER_NET_DESCR_COMPLETE) &&
	     (status != SPIDER_NET_DESCR_FRAME_END) ) अणु
		अगर (netअगर_msg_rx_err(card))
			dev_err(&card->netdev->dev,
			       "RX descriptor with unknown state %d\n", status);
		card->spider_stats.rx_desc_unk_state++;
		जाओ bad_desc;
	पूर्ण

	/* The हालs we'll throw away the packet immediately */
	अगर (hwdescr->data_error & SPIDER_NET_DESTROY_RX_FLAGS) अणु
		अगर (netअगर_msg_rx_err(card))
			dev_err(&card->netdev->dev,
			       "error in received descriptor found, "
			       "data_status=x%08x, data_error=x%08x\n",
			       hwdescr->data_status, hwdescr->data_error);
		जाओ bad_desc;
	पूर्ण

	अगर (hwdescr->dmac_cmd_status & SPIDER_NET_DESCR_BAD_STATUS) अणु
		dev_err(&card->netdev->dev, "bad status, cmd_status=x%08x\n",
			       hwdescr->dmac_cmd_status);
		pr_err("buf_addr=x%08x\n", hw_buf_addr);
		pr_err("buf_size=x%08x\n", hwdescr->buf_size);
		pr_err("next_descr_addr=x%08x\n", hwdescr->next_descr_addr);
		pr_err("result_size=x%08x\n", hwdescr->result_size);
		pr_err("valid_size=x%08x\n", hwdescr->valid_size);
		pr_err("data_status=x%08x\n", hwdescr->data_status);
		pr_err("data_error=x%08x\n", hwdescr->data_error);
		pr_err("which=%ld\n", descr - card->rx_chain.ring);

		card->spider_stats.rx_desc_error++;
		जाओ bad_desc;
	पूर्ण

	/* Ok, we've got a packet in descr */
	spider_net_pass_skb_up(descr, card);
	descr->skb = शून्य;
	hwdescr->dmac_cmd_status = SPIDER_NET_DESCR_NOT_IN_USE;
	वापस 1;

bad_desc:
	अगर (netअगर_msg_rx_err(card))
		show_rx_chain(card);
	dev_kमुक्त_skb_irq(descr->skb);
	descr->skb = शून्य;
	hwdescr->dmac_cmd_status = SPIDER_NET_DESCR_NOT_IN_USE;
	वापस 0;
पूर्ण

/**
 * spider_net_poll - NAPI poll function called by the stack to वापस packets
 * @napi: napi device काष्ठाure
 * @budget: number of packets we can pass to the stack at most
 *
 * वापसs 0 अगर no more packets available to the driver/stack. Returns 1,
 * अगर the quota is exceeded, but the driver has still packets.
 *
 * spider_net_poll वापसs all packets from the rx descriptors to the stack
 * (using netअगर_receive_skb). If all/enough packets are up, the driver
 * reenables पूर्णांकerrupts and वापसs 0. If not, 1 is वापसed.
 */
अटल पूर्णांक spider_net_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा spider_net_card *card = container_of(napi, काष्ठा spider_net_card, napi);
	पूर्णांक packets_करोne = 0;

	जबतक (packets_करोne < budget) अणु
		अगर (!spider_net_decode_one_descr(card))
			अवरोध;

		packets_करोne++;
	पूर्ण

	अगर ((packets_करोne == 0) && (card->num_rx_पूर्णांकs != 0)) अणु
		अगर (!spider_net_resync_tail_ptr(card))
			packets_करोne = budget;
		spider_net_resync_head_ptr(card);
	पूर्ण
	card->num_rx_पूर्णांकs = 0;

	spider_net_refill_rx_chain(card);
	spider_net_enable_rxdmac(card);

	spider_net_cleanup_tx_ring(&card->tx_समयr);

	/* अगर all packets are in the stack, enable पूर्णांकerrupts and वापस 0 */
	/* अगर not, वापस 1 */
	अगर (packets_करोne < budget) अणु
		napi_complete_करोne(napi, packets_करोne);
		spider_net_rx_irq_on(card);
		card->ignore_rx_ramfull = 0;
	पूर्ण

	वापस packets_करोne;
पूर्ण

/**
 * spider_net_set_mac - sets the MAC of an पूर्णांकerface
 * @netdev: पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to new MAC address
 *
 * Returns 0 on success, <0 on failure. Currently, we करोn't support this
 * and will always वापस EOPNOTSUPP.
 */
अटल पूर्णांक
spider_net_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा spider_net_card *card = netdev_priv(netdev);
	u32 macl, macu, regvalue;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, ETH_ALEN);

	/* चयन off GMACTPE and GMACRPE */
	regvalue = spider_net_पढ़ो_reg(card, SPIDER_NET_GMACOPEMD);
	regvalue &= ~((1 << 5) | (1 << 6));
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACOPEMD, regvalue);

	/* ग_लिखो mac */
	macu = (netdev->dev_addr[0]<<24) + (netdev->dev_addr[1]<<16) +
		(netdev->dev_addr[2]<<8) + (netdev->dev_addr[3]);
	macl = (netdev->dev_addr[4]<<8) + (netdev->dev_addr[5]);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACUNIMACU, macu);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACUNIMACL, macl);

	/* चयन GMACTPE and GMACRPE back on */
	regvalue = spider_net_पढ़ो_reg(card, SPIDER_NET_GMACOPEMD);
	regvalue |= ((1 << 5) | (1 << 6));
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACOPEMD, regvalue);

	spider_net_set_promisc(card);

	वापस 0;
पूर्ण

/**
 * spider_net_link_reset
 * @netdev: net device काष्ठाure
 *
 * This is called when the PHY_LINK संकेत is निश्चितed. For the blade this is
 * not connected so we should never get here.
 *
 */
अटल व्योम
spider_net_link_reset(काष्ठा net_device *netdev)
अणु

	काष्ठा spider_net_card *card = netdev_priv(netdev);

	del_समयr_sync(&card->aneg_समयr);

	/* clear पूर्णांकerrupt, block further पूर्णांकerrupts */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACST,
			     spider_net_पढ़ो_reg(card, SPIDER_NET_GMACST));
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACINTEN, 0);

	/* reset phy and setup aneg */
	card->aneg_count = 0;
	card->medium = BCM54XX_COPPER;
	spider_net_setup_aneg(card);
	mod_समयr(&card->aneg_समयr, jअगरfies + SPIDER_NET_ANEG_TIMER);

पूर्ण

/**
 * spider_net_handle_error_irq - handles errors उठाओd by an पूर्णांकerrupt
 * @card: card काष्ठाure
 * @status_reg: पूर्णांकerrupt status रेजिस्टर 0 (GHIINT0STS)
 * @error_reg1: पूर्णांकerrupt status रेजिस्टर 1 (GHIINT1STS)
 * @error_reg2: पूर्णांकerrupt status रेजिस्टर 2 (GHIINT2STS)
 *
 * spider_net_handle_error_irq treats or ignores all error conditions
 * found when an पूर्णांकerrupt is presented
 */
अटल व्योम
spider_net_handle_error_irq(काष्ठा spider_net_card *card, u32 status_reg,
			    u32 error_reg1, u32 error_reg2)
अणु
	u32 i;
	पूर्णांक show_error = 1;

	/* check GHIINT0STS ************************************/
	अगर (status_reg)
		क्रम (i = 0; i < 32; i++)
			अगर (status_reg & (1<<i))
				चयन (i)
	अणु
	/* let error_reg1 and error_reg2 evaluation decide, what to करो
	हाल SPIDER_NET_PHYINT:
	हाल SPIDER_NET_GMAC2INT:
	हाल SPIDER_NET_GMAC1INT:
	हाल SPIDER_NET_GFIFOINT:
	हाल SPIDER_NET_DMACINT:
	हाल SPIDER_NET_GSYSINT:
		अवरोध; */

	हाल SPIDER_NET_GIPSINT:
		show_error = 0;
		अवरोध;

	हाल SPIDER_NET_GPWOPCMPINT:
		/* PHY ग_लिखो operation completed */
		show_error = 0;
		अवरोध;
	हाल SPIDER_NET_GPROPCMPINT:
		/* PHY पढ़ो operation completed */
		/* we करोn't use semaphores, as we poll क्रम the completion
		 * of the पढ़ो operation in spider_net_पढ़ो_phy. Should take
		 * about 50 us
		 */
		show_error = 0;
		अवरोध;
	हाल SPIDER_NET_GPWFFINT:
		/* PHY command queue full */
		अगर (netअगर_msg_पूर्णांकr(card))
			dev_err(&card->netdev->dev, "PHY write queue full\n");
		show_error = 0;
		अवरोध;

	/* हाल SPIDER_NET_GRMDADRINT: not used. prपूर्णांक a message */
	/* हाल SPIDER_NET_GRMARPINT: not used. prपूर्णांक a message */
	/* हाल SPIDER_NET_GRMMPINT: not used. prपूर्णांक a message */

	हाल SPIDER_NET_GDTDEN0INT:
		/* someone has set TX_DMA_EN to 0 */
		show_error = 0;
		अवरोध;

	हाल SPIDER_NET_GDDDEN0INT:
	हाल SPIDER_NET_GDCDEN0INT:
	हाल SPIDER_NET_GDBDEN0INT:
	हाल SPIDER_NET_GDADEN0INT:
		/* someone has set RX_DMA_EN to 0 */
		show_error = 0;
		अवरोध;

	/* RX पूर्णांकerrupts */
	हाल SPIDER_NET_GDDFDCINT:
	हाल SPIDER_NET_GDCFDCINT:
	हाल SPIDER_NET_GDBFDCINT:
	हाल SPIDER_NET_GDAFDCINT:
	/* हाल SPIDER_NET_GDNMINT: not used. prपूर्णांक a message */
	/* हाल SPIDER_NET_GCNMINT: not used. prपूर्णांक a message */
	/* हाल SPIDER_NET_GBNMINT: not used. prपूर्णांक a message */
	/* हाल SPIDER_NET_GANMINT: not used. prपूर्णांक a message */
	/* हाल SPIDER_NET_GRFNMINT: not used. prपूर्णांक a message */
		show_error = 0;
		अवरोध;

	/* TX पूर्णांकerrupts */
	हाल SPIDER_NET_GDTFDCINT:
		show_error = 0;
		अवरोध;
	हाल SPIDER_NET_GTTEDINT:
		show_error = 0;
		अवरोध;
	हाल SPIDER_NET_GDTDCEINT:
		/* chain end. If a descriptor should be sent, kick off
		 * tx dma
		अगर (card->tx_chain.tail != card->tx_chain.head)
			spider_net_kick_tx_dma(card);
		*/
		show_error = 0;
		अवरोध;

	/* हाल SPIDER_NET_G1TMCNTINT: not used. prपूर्णांक a message */
	/* हाल SPIDER_NET_GFREECNTINT: not used. prपूर्णांक a message */
	पूर्ण

	/* check GHIINT1STS ************************************/
	अगर (error_reg1)
		क्रम (i = 0; i < 32; i++)
			अगर (error_reg1 & (1<<i))
				चयन (i)
	अणु
	हाल SPIDER_NET_GTMFLLINT:
		/* TX RAM full may happen on a usual हाल.
		 * Logging is not needed.
		 */
		show_error = 0;
		अवरोध;
	हाल SPIDER_NET_GRFDFLLINT:
	हाल SPIDER_NET_GRFCFLLINT:
	हाल SPIDER_NET_GRFBFLLINT:
	हाल SPIDER_NET_GRFAFLLINT:
	हाल SPIDER_NET_GRMFLLINT:
		/* Could happen when rx chain is full */
		अगर (card->ignore_rx_ramfull == 0) अणु
			card->ignore_rx_ramfull = 1;
			spider_net_resync_head_ptr(card);
			spider_net_refill_rx_chain(card);
			spider_net_enable_rxdmac(card);
			card->num_rx_पूर्णांकs ++;
			napi_schedule(&card->napi);
		पूर्ण
		show_error = 0;
		अवरोध;

	/* हाल SPIDER_NET_GTMSHTINT: problem, prपूर्णांक a message */
	हाल SPIDER_NET_GDTINVDINT:
		/* allrighty. tx from previous descr ok */
		show_error = 0;
		अवरोध;

	/* chain end */
	हाल SPIDER_NET_GDDDCEINT:
	हाल SPIDER_NET_GDCDCEINT:
	हाल SPIDER_NET_GDBDCEINT:
	हाल SPIDER_NET_GDADCEINT:
		spider_net_resync_head_ptr(card);
		spider_net_refill_rx_chain(card);
		spider_net_enable_rxdmac(card);
		card->num_rx_पूर्णांकs ++;
		napi_schedule(&card->napi);
		show_error = 0;
		अवरोध;

	/* invalid descriptor */
	हाल SPIDER_NET_GDDINVDINT:
	हाल SPIDER_NET_GDCINVDINT:
	हाल SPIDER_NET_GDBINVDINT:
	हाल SPIDER_NET_GDAINVDINT:
		/* Could happen when rx chain is full */
		spider_net_resync_head_ptr(card);
		spider_net_refill_rx_chain(card);
		spider_net_enable_rxdmac(card);
		card->num_rx_पूर्णांकs ++;
		napi_schedule(&card->napi);
		show_error = 0;
		अवरोध;

	/* हाल SPIDER_NET_GDTRSERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDDRSERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDCRSERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDBRSERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDARSERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDSERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDTPTERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDDPTERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDCPTERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDBPTERINT: problem, prपूर्णांक a message */
	/* हाल SPIDER_NET_GDAPTERINT: problem, prपूर्णांक a message */
	शेष:
		show_error = 1;
		अवरोध;
	पूर्ण

	/* check GHIINT2STS ************************************/
	अगर (error_reg2)
		क्रम (i = 0; i < 32; i++)
			अगर (error_reg2 & (1<<i))
				चयन (i)
	अणु
	/* there is nothing we can (want  to) करो at this समय. Log a
	 * message, we can चयन on and off the specअगरic values later on
	हाल SPIDER_NET_GPROPERINT:
	हाल SPIDER_NET_GMCTCRSNGINT:
	हाल SPIDER_NET_GMCTLCOLINT:
	हाल SPIDER_NET_GMCTTMOTINT:
	हाल SPIDER_NET_GMCRCAERINT:
	हाल SPIDER_NET_GMCRCALERINT:
	हाल SPIDER_NET_GMCRALNERINT:
	हाल SPIDER_NET_GMCROVRINT:
	हाल SPIDER_NET_GMCRRNTINT:
	हाल SPIDER_NET_GMCRRXERINT:
	हाल SPIDER_NET_GTITCSERINT:
	हाल SPIDER_NET_GTIFMTERINT:
	हाल SPIDER_NET_GTIPKTRVKINT:
	हाल SPIDER_NET_GTISPINGINT:
	हाल SPIDER_NET_GTISADNGINT:
	हाल SPIDER_NET_GTISPDNGINT:
	हाल SPIDER_NET_GRIFMTERINT:
	हाल SPIDER_NET_GRIPKTRVKINT:
	हाल SPIDER_NET_GRISPINGINT:
	हाल SPIDER_NET_GRISADNGINT:
	हाल SPIDER_NET_GRISPDNGINT:
		अवरोध;
	*/
		शेष:
			अवरोध;
	पूर्ण

	अगर ((show_error) && (netअगर_msg_पूर्णांकr(card)) && net_ratelimit())
		dev_err(&card->netdev->dev, "Error interrupt, GHIINT0STS = 0x%08x, "
		       "GHIINT1STS = 0x%08x, GHIINT2STS = 0x%08x\n",
		       status_reg, error_reg1, error_reg2);

	/* clear पूर्णांकerrupt sources */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT1STS, error_reg1);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT2STS, error_reg2);
पूर्ण

/**
 * spider_net_पूर्णांकerrupt - पूर्णांकerrupt handler क्रम spider_net
 * @irq: पूर्णांकerrupt number
 * @ptr: poपूर्णांकer to net_device
 *
 * वापसs IRQ_HANDLED, अगर पूर्णांकerrupt was क्रम driver, or IRQ_NONE, अगर no
 * पूर्णांकerrupt found उठाओd by card.
 *
 * This is the पूर्णांकerrupt handler, that turns off
 * पूर्णांकerrupts क्रम this device and makes the stack poll the driver
 */
अटल irqवापस_t
spider_net_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा net_device *netdev = ptr;
	काष्ठा spider_net_card *card = netdev_priv(netdev);
	u32 status_reg, error_reg1, error_reg2;

	status_reg = spider_net_पढ़ो_reg(card, SPIDER_NET_GHIINT0STS);
	error_reg1 = spider_net_पढ़ो_reg(card, SPIDER_NET_GHIINT1STS);
	error_reg2 = spider_net_पढ़ो_reg(card, SPIDER_NET_GHIINT2STS);

	अगर (!(status_reg & SPIDER_NET_INT0_MASK_VALUE) &&
	    !(error_reg1 & SPIDER_NET_INT1_MASK_VALUE) &&
	    !(error_reg2 & SPIDER_NET_INT2_MASK_VALUE))
		वापस IRQ_NONE;

	अगर (status_reg & SPIDER_NET_RXINT ) अणु
		spider_net_rx_irq_off(card);
		napi_schedule(&card->napi);
		card->num_rx_पूर्णांकs ++;
	पूर्ण
	अगर (status_reg & SPIDER_NET_TXINT)
		napi_schedule(&card->napi);

	अगर (status_reg & SPIDER_NET_LINKINT)
		spider_net_link_reset(netdev);

	अगर (status_reg & SPIDER_NET_ERRINT )
		spider_net_handle_error_irq(card, status_reg,
					    error_reg1, error_reg2);

	/* clear पूर्णांकerrupt sources */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT0STS, status_reg);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * spider_net_poll_controller - artअगरicial पूर्णांकerrupt क्रम netconsole etc.
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * see Documentation/networking/netconsole.rst
 */
अटल व्योम
spider_net_poll_controller(काष्ठा net_device *netdev)
अणु
	disable_irq(netdev->irq);
	spider_net_पूर्णांकerrupt(netdev->irq, netdev);
	enable_irq(netdev->irq);
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_POLL_CONTROLLER */

/**
 * spider_net_enable_पूर्णांकerrupts - enable पूर्णांकerrupts
 * @card: card काष्ठाure
 *
 * spider_net_enable_पूर्णांकerrupt enables several पूर्णांकerrupts
 */
अटल व्योम
spider_net_enable_पूर्णांकerrupts(काष्ठा spider_net_card *card)
अणु
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT0MSK,
			     SPIDER_NET_INT0_MASK_VALUE);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT1MSK,
			     SPIDER_NET_INT1_MASK_VALUE);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT2MSK,
			     SPIDER_NET_INT2_MASK_VALUE);
पूर्ण

/**
 * spider_net_disable_पूर्णांकerrupts - disable पूर्णांकerrupts
 * @card: card काष्ठाure
 *
 * spider_net_disable_पूर्णांकerrupts disables all the पूर्णांकerrupts
 */
अटल व्योम
spider_net_disable_पूर्णांकerrupts(काष्ठा spider_net_card *card)
अणु
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT0MSK, 0);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT1MSK, 0);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GHIINT2MSK, 0);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACINTEN, 0);
पूर्ण

/**
 * spider_net_init_card - initializes the card
 * @card: card काष्ठाure
 *
 * spider_net_init_card initializes the card so that other रेजिस्टरs can
 * be used
 */
अटल व्योम
spider_net_init_card(काष्ठा spider_net_card *card)
अणु
	spider_net_ग_लिखो_reg(card, SPIDER_NET_CKRCTRL,
			     SPIDER_NET_CKRCTRL_STOP_VALUE);

	spider_net_ग_लिखो_reg(card, SPIDER_NET_CKRCTRL,
			     SPIDER_NET_CKRCTRL_RUN_VALUE);

	/* trigger ETOMOD संकेत */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACOPEMD,
		spider_net_पढ़ो_reg(card, SPIDER_NET_GMACOPEMD) | 0x4);

	spider_net_disable_पूर्णांकerrupts(card);
पूर्ण

/**
 * spider_net_enable_card - enables the card by setting all kinds of regs
 * @card: card काष्ठाure
 *
 * spider_net_enable_card sets a lot of SMMIO रेजिस्टरs to enable the device
 */
अटल व्योम
spider_net_enable_card(काष्ठा spider_net_card *card)
अणु
	पूर्णांक i;
	/* the following array consists of (रेजिस्टर),(value) pairs
	 * that are set in this function. A रेजिस्टर of 0 ends the list
	 */
	u32 regs[][2] = अणु
		अणु SPIDER_NET_GRESUMINTNUM, 0 पूर्ण,
		अणु SPIDER_NET_GREINTNUM, 0 पूर्ण,

		/* set पूर्णांकerrupt frame number रेजिस्टरs */
		/* clear the single DMA engine रेजिस्टरs first */
		अणु SPIDER_NET_GFAFRMNUM, SPIDER_NET_GFXFRAMES_VALUE पूर्ण,
		अणु SPIDER_NET_GFBFRMNUM, SPIDER_NET_GFXFRAMES_VALUE पूर्ण,
		अणु SPIDER_NET_GFCFRMNUM, SPIDER_NET_GFXFRAMES_VALUE पूर्ण,
		अणु SPIDER_NET_GFDFRMNUM, SPIDER_NET_GFXFRAMES_VALUE पूर्ण,
		/* then set, what we really need */
		अणु SPIDER_NET_GFFRMNUM, SPIDER_NET_FRAMENUM_VALUE पूर्ण,

		/* समयr counter रेजिस्टरs and stuff */
		अणु SPIDER_NET_GFREECNNUM, 0 पूर्ण,
		अणु SPIDER_NET_GONETIMENUM, 0 पूर्ण,
		अणु SPIDER_NET_GTOUTFRMNUM, 0 पूर्ण,

		/* RX mode setting */
		अणु SPIDER_NET_GRXMDSET, SPIDER_NET_RXMODE_VALUE पूर्ण,
		/* TX mode setting */
		अणु SPIDER_NET_GTXMDSET, SPIDER_NET_TXMODE_VALUE पूर्ण,
		/* IPSEC mode setting */
		अणु SPIDER_NET_GIPSECINIT, SPIDER_NET_IPSECINIT_VALUE पूर्ण,

		अणु SPIDER_NET_GFTRESTRT, SPIDER_NET_RESTART_VALUE पूर्ण,

		अणु SPIDER_NET_GMRWOLCTRL, 0 पूर्ण,
		अणु SPIDER_NET_GTESTMD, 0x10000000 पूर्ण,
		अणु SPIDER_NET_GTTQMSK, 0x00400040 पूर्ण,

		अणु SPIDER_NET_GMACINTEN, 0 पूर्ण,

		/* flow control stuff */
		अणु SPIDER_NET_GMACAPAUSE, SPIDER_NET_MACAPAUSE_VALUE पूर्ण,
		अणु SPIDER_NET_GMACTXPAUSE, SPIDER_NET_TXPAUSE_VALUE पूर्ण,

		अणु SPIDER_NET_GMACBSTLMT, SPIDER_NET_BURSTLMT_VALUE पूर्ण,
		अणु 0, 0पूर्ण
	पूर्ण;

	i = 0;
	जबतक (regs[i][0]) अणु
		spider_net_ग_लिखो_reg(card, regs[i][0], regs[i][1]);
		i++;
	पूर्ण

	/* clear unicast filter table entries 1 to 14 */
	क्रम (i = 1; i <= 14; i++) अणु
		spider_net_ग_लिखो_reg(card,
				     SPIDER_NET_GMRUAFILnR + i * 8,
				     0x00080000);
		spider_net_ग_लिखो_reg(card,
				     SPIDER_NET_GMRUAFILnR + i * 8 + 4,
				     0x00000000);
	पूर्ण

	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMRUA0FIL15R, 0x08080000);

	spider_net_ग_लिखो_reg(card, SPIDER_NET_ECMODE, SPIDER_NET_ECMODE_VALUE);

	/* set chain tail address क्रम RX chains and
	 * enable DMA
	 */
	spider_net_enable_rxchtails(card);
	spider_net_enable_rxdmac(card);

	spider_net_ग_लिखो_reg(card, SPIDER_NET_GRXDMAEN, SPIDER_NET_WOL_VALUE);

	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACLENLMT,
			     SPIDER_NET_LENLMT_VALUE);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACOPEMD,
			     SPIDER_NET_OPMODE_VALUE);

	spider_net_ग_लिखो_reg(card, SPIDER_NET_GDTDMACCNTR,
			     SPIDER_NET_GDTBSTA);
पूर्ण

/**
 * spider_net_करोwnload_firmware - loads firmware पूर्णांकo the adapter
 * @card: card काष्ठाure
 * @firmware_ptr: poपूर्णांकer to firmware data
 *
 * spider_net_करोwnload_firmware loads the firmware data पूर्णांकo the
 * adapter. It assumes the length etc. to be allright.
 */
अटल पूर्णांक
spider_net_करोwnload_firmware(काष्ठा spider_net_card *card,
			     स्थिर व्योम *firmware_ptr)
अणु
	पूर्णांक sequencer, i;
	स्थिर u32 *fw_ptr = firmware_ptr;

	/* stop sequencers */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GSINIT,
			     SPIDER_NET_STOP_SEQ_VALUE);

	क्रम (sequencer = 0; sequencer < SPIDER_NET_FIRMWARE_SEQS;
	     sequencer++) अणु
		spider_net_ग_लिखो_reg(card,
				     SPIDER_NET_GSnPRGADR + sequencer * 8, 0);
		क्रम (i = 0; i < SPIDER_NET_FIRMWARE_SEQWORDS; i++) अणु
			spider_net_ग_लिखो_reg(card, SPIDER_NET_GSnPRGDAT +
					     sequencer * 8, *fw_ptr);
			fw_ptr++;
		पूर्ण
	पूर्ण

	अगर (spider_net_पढ़ो_reg(card, SPIDER_NET_GSINIT))
		वापस -EIO;

	spider_net_ग_लिखो_reg(card, SPIDER_NET_GSINIT,
			     SPIDER_NET_RUN_SEQ_VALUE);

	वापस 0;
पूर्ण

/**
 * spider_net_init_firmware - पढ़ोs in firmware parts
 * @card: card काष्ठाure
 *
 * Returns 0 on success, <0 on failure
 *
 * spider_net_init_firmware खोलोs the sequencer firmware and करोes some basic
 * checks. This function खोलोs and releases the firmware काष्ठाure. A call
 * to करोwnload the firmware is perक्रमmed beक्रमe the release.
 *
 * Firmware क्रमmat
 * ===============
 * spider_fw.bin is expected to be a file containing 6*1024*4 bytes, 4k being
 * the program क्रम each sequencer. Use the command
 *    tail -q -n +2 Seq_code1_0x088.txt Seq_code2_0x090.txt              \
 *         Seq_code3_0x098.txt Seq_code4_0x0A0.txt Seq_code5_0x0A8.txt   \
 *         Seq_code6_0x0B0.txt | xxd -r -p -c4 > spider_fw.bin
 *
 * to generate spider_fw.bin, अगर you have sequencer programs with something
 * like the following contents क्रम each sequencer:
 *    <ONE LINE COMMENT>
 *    <FIRST 4-BYTES-WORD FOR SEQUENCER>
 *    <SECOND 4-BYTES-WORD FOR SEQUENCER>
 *     ...
 *    <1024th 4-BYTES-WORD FOR SEQUENCER>
 */
अटल पूर्णांक
spider_net_init_firmware(काष्ठा spider_net_card *card)
अणु
	काष्ठा firmware *firmware = शून्य;
	काष्ठा device_node *dn;
	स्थिर u8 *fw_prop = शून्य;
	पूर्णांक err = -ENOENT;
	पूर्णांक fw_size;

	अगर (request_firmware((स्थिर काष्ठा firmware **)&firmware,
			     SPIDER_NET_FIRMWARE_NAME, &card->pdev->dev) == 0) अणु
		अगर ( (firmware->size != SPIDER_NET_FIRMWARE_LEN) &&
		     netअगर_msg_probe(card) ) अणु
			dev_err(&card->netdev->dev,
			       "Incorrect size of spidernet firmware in " \
			       "filesystem. Looking in host firmware...\n");
			जाओ try_host_fw;
		पूर्ण
		err = spider_net_करोwnload_firmware(card, firmware->data);

		release_firmware(firmware);
		अगर (err)
			जाओ try_host_fw;

		जाओ करोne;
	पूर्ण

try_host_fw:
	dn = pci_device_to_OF_node(card->pdev);
	अगर (!dn)
		जाओ out_err;

	fw_prop = of_get_property(dn, "firmware", &fw_size);
	अगर (!fw_prop)
		जाओ out_err;

	अगर ( (fw_size != SPIDER_NET_FIRMWARE_LEN) &&
	     netअगर_msg_probe(card) ) अणु
		dev_err(&card->netdev->dev,
		       "Incorrect size of spidernet firmware in host firmware\n");
		जाओ करोne;
	पूर्ण

	err = spider_net_करोwnload_firmware(card, fw_prop);

करोne:
	वापस err;
out_err:
	अगर (netअगर_msg_probe(card))
		dev_err(&card->netdev->dev,
		       "Couldn't find spidernet firmware in filesystem " \
		       "or host firmware\n");
	वापस err;
पूर्ण

/**
 * spider_net_खोलो - called upon अगरonfig up
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * वापसs 0 on success, <0 on failure
 *
 * spider_net_खोलो allocates all the descriptors and memory needed क्रम
 * operation, sets up multicast list and enables पूर्णांकerrupts
 */
पूर्णांक
spider_net_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा spider_net_card *card = netdev_priv(netdev);
	पूर्णांक result;

	result = spider_net_init_firmware(card);
	अगर (result)
		जाओ init_firmware_failed;

	/* start probing with copper */
	card->aneg_count = 0;
	card->medium = BCM54XX_COPPER;
	spider_net_setup_aneg(card);
	अगर (card->phy.def->phy_id)
		mod_समयr(&card->aneg_समयr, jअगरfies + SPIDER_NET_ANEG_TIMER);

	result = spider_net_init_chain(card, &card->tx_chain);
	अगर (result)
		जाओ alloc_tx_failed;
	card->low_watermark = शून्य;

	result = spider_net_init_chain(card, &card->rx_chain);
	अगर (result)
		जाओ alloc_rx_failed;

	/* Allocate rx skbs */
	result = spider_net_alloc_rx_skbs(card);
	अगर (result)
		जाओ alloc_skbs_failed;

	spider_net_set_multi(netdev);

	/* further enhancement: setup hw vlan, अगर needed */

	result = -EBUSY;
	अगर (request_irq(netdev->irq, spider_net_पूर्णांकerrupt,
			     IRQF_SHARED, netdev->name, netdev))
		जाओ रेजिस्टर_पूर्णांक_failed;

	spider_net_enable_card(card);

	netअगर_start_queue(netdev);
	netअगर_carrier_on(netdev);
	napi_enable(&card->napi);

	spider_net_enable_पूर्णांकerrupts(card);

	वापस 0;

रेजिस्टर_पूर्णांक_failed:
	spider_net_मुक्त_rx_chain_contents(card);
alloc_skbs_failed:
	spider_net_मुक्त_chain(card, &card->rx_chain);
alloc_rx_failed:
	spider_net_मुक्त_chain(card, &card->tx_chain);
alloc_tx_failed:
	del_समयr_sync(&card->aneg_समयr);
init_firmware_failed:
	वापस result;
पूर्ण

/**
 * spider_net_link_phy
 * @t: समयr context used to obtain the poपूर्णांकer to net card data काष्ठाure
 */
अटल व्योम spider_net_link_phy(काष्ठा समयr_list *t)
अणु
	काष्ठा spider_net_card *card = from_समयr(card, t, aneg_समयr);
	काष्ठा mii_phy *phy = &card->phy;

	/* अगर link didn't come up after SPIDER_NET_ANEG_TIMEOUT tries, setup phy again */
	अगर (card->aneg_count > SPIDER_NET_ANEG_TIMEOUT) अणु

		pr_debug("%s: link is down trying to bring it up\n",
			 card->netdev->name);

		चयन (card->medium) अणु
		हाल BCM54XX_COPPER:
			/* enable fiber with स्वतःnegotiation first */
			अगर (phy->def->ops->enable_fiber)
				phy->def->ops->enable_fiber(phy, 1);
			card->medium = BCM54XX_FIBER;
			अवरोध;

		हाल BCM54XX_FIBER:
			/* fiber didn't come up, try to disable fiber स्वतःneg */
			अगर (phy->def->ops->enable_fiber)
				phy->def->ops->enable_fiber(phy, 0);
			card->medium = BCM54XX_UNKNOWN;
			अवरोध;

		हाल BCM54XX_UNKNOWN:
			/* copper, fiber with and without failed,
			 * retry from beginning
			 */
			spider_net_setup_aneg(card);
			card->medium = BCM54XX_COPPER;
			अवरोध;
		पूर्ण

		card->aneg_count = 0;
		mod_समयr(&card->aneg_समयr, jअगरfies + SPIDER_NET_ANEG_TIMER);
		वापस;
	पूर्ण

	/* link still not up, try again later */
	अगर (!(phy->def->ops->poll_link(phy))) अणु
		card->aneg_count++;
		mod_समयr(&card->aneg_समयr, jअगरfies + SPIDER_NET_ANEG_TIMER);
		वापस;
	पूर्ण

	/* link came up, get abilities */
	phy->def->ops->पढ़ो_link(phy);

	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACST,
			     spider_net_पढ़ो_reg(card, SPIDER_NET_GMACST));
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACINTEN, 0x4);

	अगर (phy->speed == 1000)
		spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACMODE, 0x00000001);
	अन्यथा
		spider_net_ग_लिखो_reg(card, SPIDER_NET_GMACMODE, 0);

	card->aneg_count = 0;

	pr_info("%s: link up, %i Mbps, %s-duplex %sautoneg.\n",
		card->netdev->name, phy->speed,
		phy->duplex == 1 ? "Full" : "Half",
		phy->स्वतःneg == 1 ? "" : "no ");
पूर्ण

/**
 * spider_net_setup_phy - setup PHY
 * @card: card काष्ठाure
 *
 * वापसs 0 on success, <0 on failure
 *
 * spider_net_setup_phy is used as part of spider_net_probe.
 **/
अटल पूर्णांक
spider_net_setup_phy(काष्ठा spider_net_card *card)
अणु
	काष्ठा mii_phy *phy = &card->phy;

	spider_net_ग_लिखो_reg(card, SPIDER_NET_GDTDMASEL,
			     SPIDER_NET_DMASEL_VALUE);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GPCCTRL,
			     SPIDER_NET_PHY_CTRL_VALUE);

	phy->dev = card->netdev;
	phy->mdio_पढ़ो = spider_net_पढ़ो_phy;
	phy->mdio_ग_लिखो = spider_net_ग_लिखो_phy;

	क्रम (phy->mii_id = 1; phy->mii_id <= 31; phy->mii_id++) अणु
		अचिन्हित लघु id;
		id = spider_net_पढ़ो_phy(card->netdev, phy->mii_id, MII_BMSR);
		अगर (id != 0x0000 && id != 0xffff) अणु
			अगर (!sungem_phy_probe(phy, phy->mii_id)) अणु
				pr_info("Found %s.\n", phy->def->name);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spider_net_workaround_rxramfull - work around firmware bug
 * @card: card काष्ठाure
 *
 * no वापस value
 **/
अटल व्योम
spider_net_workaround_rxramfull(काष्ठा spider_net_card *card)
अणु
	पूर्णांक i, sequencer = 0;

	/* cancel reset */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_CKRCTRL,
			     SPIDER_NET_CKRCTRL_RUN_VALUE);

	/* empty sequencer data */
	क्रम (sequencer = 0; sequencer < SPIDER_NET_FIRMWARE_SEQS;
	     sequencer++) अणु
		spider_net_ग_लिखो_reg(card, SPIDER_NET_GSnPRGADR +
				     sequencer * 8, 0x0);
		क्रम (i = 0; i < SPIDER_NET_FIRMWARE_SEQWORDS; i++) अणु
			spider_net_ग_लिखो_reg(card, SPIDER_NET_GSnPRGDAT +
					     sequencer * 8, 0x0);
		पूर्ण
	पूर्ण

	/* set sequencer operation */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_GSINIT, 0x000000fe);

	/* reset */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_CKRCTRL,
			     SPIDER_NET_CKRCTRL_STOP_VALUE);
पूर्ण

/**
 * spider_net_stop - called upon अगरconfig करोwn
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * always वापसs 0
 */
पूर्णांक
spider_net_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा spider_net_card *card = netdev_priv(netdev);

	napi_disable(&card->napi);
	netअगर_carrier_off(netdev);
	netअगर_stop_queue(netdev);
	del_समयr_sync(&card->tx_समयr);
	del_समयr_sync(&card->aneg_समयr);

	spider_net_disable_पूर्णांकerrupts(card);

	मुक्त_irq(netdev->irq, netdev);

	spider_net_ग_लिखो_reg(card, SPIDER_NET_GDTDMACCNTR,
			     SPIDER_NET_DMA_TX_FEND_VALUE);

	/* turn off DMA, क्रमce end */
	spider_net_disable_rxdmac(card);

	/* release chains */
	spider_net_release_tx_chain(card, 1);
	spider_net_मुक्त_rx_chain_contents(card);

	spider_net_मुक्त_chain(card, &card->tx_chain);
	spider_net_मुक्त_chain(card, &card->rx_chain);

	वापस 0;
पूर्ण

/**
 * spider_net_tx_समयout_task - task scheduled by the watchकरोg समयout
 * function (to be called not under पूर्णांकerrupt status)
 * @work: work context used to obtain the poपूर्णांकer to net card data काष्ठाure
 *
 * called as task when tx hangs, resets पूर्णांकerface (अगर पूर्णांकerface is up)
 */
अटल व्योम
spider_net_tx_समयout_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा spider_net_card *card =
		container_of(work, काष्ठा spider_net_card, tx_समयout_task);
	काष्ठा net_device *netdev = card->netdev;

	अगर (!(netdev->flags & IFF_UP))
		जाओ out;

	netअगर_device_detach(netdev);
	spider_net_stop(netdev);

	spider_net_workaround_rxramfull(card);
	spider_net_init_card(card);

	अगर (spider_net_setup_phy(card))
		जाओ out;

	spider_net_खोलो(netdev);
	spider_net_kick_tx_dma(card);
	netअगर_device_attach(netdev);

out:
	atomic_dec(&card->tx_समयout_task_counter);
पूर्ण

/**
 * spider_net_tx_समयout - called when the tx समयout watchकरोg kicks in.
 * @netdev: पूर्णांकerface device काष्ठाure
 * @txqueue: unused
 *
 * called, अगर tx hangs. Schedules a task that resets the पूर्णांकerface
 */
अटल व्योम
spider_net_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा spider_net_card *card;

	card = netdev_priv(netdev);
	atomic_inc(&card->tx_समयout_task_counter);
	अगर (netdev->flags & IFF_UP)
		schedule_work(&card->tx_समयout_task);
	अन्यथा
		atomic_dec(&card->tx_समयout_task_counter);
	card->spider_stats.tx_समयouts++;
पूर्ण

अटल स्थिर काष्ठा net_device_ops spider_net_ops = अणु
	.nकरो_खोलो		= spider_net_खोलो,
	.nकरो_stop		= spider_net_stop,
	.nकरो_start_xmit		= spider_net_xmit,
	.nकरो_set_rx_mode	= spider_net_set_multi,
	.nकरो_set_mac_address	= spider_net_set_mac,
	.nकरो_करो_ioctl		= spider_net_करो_ioctl,
	.nकरो_tx_समयout		= spider_net_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	/* HW VLAN */
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	/* poll controller */
	.nकरो_poll_controller	= spider_net_poll_controller,
#पूर्ण_अगर /* CONFIG_NET_POLL_CONTROLLER */
पूर्ण;

/**
 * spider_net_setup_netdev_ops - initialization of net_device operations
 * @netdev: net_device काष्ठाure
 *
 * fills out function poपूर्णांकers in the net_device काष्ठाure
 */
अटल व्योम
spider_net_setup_netdev_ops(काष्ठा net_device *netdev)
अणु
	netdev->netdev_ops = &spider_net_ops;
	netdev->watchकरोg_समयo = SPIDER_NET_WATCHDOG_TIMEOUT;
	/* ethtool ops */
	netdev->ethtool_ops = &spider_net_ethtool_ops;
पूर्ण

/**
 * spider_net_setup_netdev - initialization of net_device
 * @card: card काष्ठाure
 *
 * Returns 0 on success or <0 on failure
 *
 * spider_net_setup_netdev initializes the net_device काष्ठाure
 **/
अटल पूर्णांक
spider_net_setup_netdev(काष्ठा spider_net_card *card)
अणु
	पूर्णांक result;
	काष्ठा net_device *netdev = card->netdev;
	काष्ठा device_node *dn;
	काष्ठा sockaddr addr;
	स्थिर u8 *mac;

	SET_NETDEV_DEV(netdev, &card->pdev->dev);

	pci_set_drvdata(card->pdev, netdev);

	समयr_setup(&card->tx_समयr, spider_net_cleanup_tx_ring, 0);
	netdev->irq = card->pdev->irq;

	card->aneg_count = 0;
	समयr_setup(&card->aneg_समयr, spider_net_link_phy, 0);

	netअगर_napi_add(netdev, &card->napi,
		       spider_net_poll, SPIDER_NET_NAPI_WEIGHT);

	spider_net_setup_netdev_ops(netdev);

	netdev->hw_features = NETIF_F_RXCSUM | NETIF_F_IP_CSUM;
	अगर (SPIDER_NET_RX_CSUM_DEFAULT)
		netdev->features |= NETIF_F_RXCSUM;
	netdev->features |= NETIF_F_IP_CSUM | NETIF_F_LLTX;
	/* some समय: NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
	 *		NETIF_F_HW_VLAN_CTAG_FILTER
	 */

	/* MTU range: 64 - 2294 */
	netdev->min_mtu = SPIDER_NET_MIN_MTU;
	netdev->max_mtu = SPIDER_NET_MAX_MTU;

	netdev->irq = card->pdev->irq;
	card->num_rx_पूर्णांकs = 0;
	card->ignore_rx_ramfull = 0;

	dn = pci_device_to_OF_node(card->pdev);
	अगर (!dn)
		वापस -EIO;

	mac = of_get_property(dn, "local-mac-address", शून्य);
	अगर (!mac)
		वापस -EIO;
	स_नकल(addr.sa_data, mac, ETH_ALEN);

	result = spider_net_set_mac(netdev, &addr);
	अगर ((result) && (netअगर_msg_probe(card)))
		dev_err(&card->netdev->dev,
		        "Failed to set MAC address: %i\n", result);

	result = रेजिस्टर_netdev(netdev);
	अगर (result) अणु
		अगर (netअगर_msg_probe(card))
			dev_err(&card->netdev->dev,
			        "Couldn't register net_device: %i\n", result);
		वापस result;
	पूर्ण

	अगर (netअगर_msg_probe(card))
		pr_info("Initialized device %s.\n", netdev->name);

	वापस 0;
पूर्ण

/**
 * spider_net_alloc_card - allocates net_device and card काष्ठाure
 *
 * वापसs the card काष्ठाure or शून्य in हाल of errors
 *
 * the card and net_device काष्ठाures are linked to each other
 */
अटल काष्ठा spider_net_card *
spider_net_alloc_card(व्योम)
अणु
	काष्ठा net_device *netdev;
	काष्ठा spider_net_card *card;

	netdev = alloc_etherdev(काष्ठा_size(card, darray,
					    tx_descriptors + rx_descriptors));
	अगर (!netdev)
		वापस शून्य;

	card = netdev_priv(netdev);
	card->netdev = netdev;
	card->msg_enable = SPIDER_NET_DEFAULT_MSG;
	INIT_WORK(&card->tx_समयout_task, spider_net_tx_समयout_task);
	init_रुकोqueue_head(&card->रुकोq);
	atomic_set(&card->tx_समयout_task_counter, 0);

	card->rx_chain.num_desc = rx_descriptors;
	card->rx_chain.ring = card->darray;
	card->tx_chain.num_desc = tx_descriptors;
	card->tx_chain.ring = card->darray + rx_descriptors;

	वापस card;
पूर्ण

/**
 * spider_net_unकरो_pci_setup - releases PCI ressources
 * @card: card काष्ठाure
 *
 * spider_net_unकरो_pci_setup releases the mapped regions
 */
अटल व्योम
spider_net_unकरो_pci_setup(काष्ठा spider_net_card *card)
अणु
	iounmap(card->regs);
	pci_release_regions(card->pdev);
पूर्ण

/**
 * spider_net_setup_pci_dev - sets up the device in terms of PCI operations
 * @pdev: PCI device
 *
 * Returns the card काष्ठाure or शून्य अगर any errors occur
 *
 * spider_net_setup_pci_dev initializes pdev and together with the
 * functions called in spider_net_खोलो configures the device so that
 * data can be transferred over it
 * The net_device काष्ठाure is attached to the card काष्ठाure, अगर the
 * function वापसs without error.
 **/
अटल काष्ठा spider_net_card *
spider_net_setup_pci_dev(काष्ठा pci_dev *pdev)
अणु
	काष्ठा spider_net_card *card;
	अचिन्हित दीर्घ mmio_start, mmio_len;

	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev, "Couldn't enable PCI device\n");
		वापस शून्य;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev,
		        "Couldn't find proper PCI device base address.\n");
		जाओ out_disable_dev;
	पूर्ण

	अगर (pci_request_regions(pdev, spider_net_driver_name)) अणु
		dev_err(&pdev->dev,
		        "Couldn't obtain PCI resources, aborting.\n");
		जाओ out_disable_dev;
	पूर्ण

	pci_set_master(pdev);

	card = spider_net_alloc_card();
	अगर (!card) अणु
		dev_err(&pdev->dev,
		        "Couldn't allocate net_device structure, aborting.\n");
		जाओ out_release_regions;
	पूर्ण
	card->pdev = pdev;

	/* fetch base address and length of first resource */
	mmio_start = pci_resource_start(pdev, 0);
	mmio_len = pci_resource_len(pdev, 0);

	card->netdev->mem_start = mmio_start;
	card->netdev->mem_end = mmio_start + mmio_len;
	card->regs = ioremap(mmio_start, mmio_len);

	अगर (!card->regs) अणु
		dev_err(&pdev->dev,
		        "Couldn't obtain PCI resources, aborting.\n");
		जाओ out_release_regions;
	पूर्ण

	वापस card;

out_release_regions:
	pci_release_regions(pdev);
out_disable_dev:
	pci_disable_device(pdev);
	वापस शून्य;
पूर्ण

/**
 * spider_net_probe - initialization of a device
 * @pdev: PCI device
 * @ent: entry in the device id list
 *
 * Returns 0 on success, <0 on failure
 *
 * spider_net_probe initializes pdev and रेजिस्टरs a net_device
 * काष्ठाure क्रम it. After that, the device can be अगरconfig'ed up
 **/
अटल पूर्णांक
spider_net_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err = -EIO;
	काष्ठा spider_net_card *card;

	card = spider_net_setup_pci_dev(pdev);
	अगर (!card)
		जाओ out;

	spider_net_workaround_rxramfull(card);
	spider_net_init_card(card);

	err = spider_net_setup_phy(card);
	अगर (err)
		जाओ out_unकरो_pci;

	err = spider_net_setup_netdev(card);
	अगर (err)
		जाओ out_unकरो_pci;

	वापस 0;

out_unकरो_pci:
	spider_net_unकरो_pci_setup(card);
	मुक्त_netdev(card->netdev);
out:
	वापस err;
पूर्ण

/**
 * spider_net_हटाओ - removal of a device
 * @pdev: PCI device
 *
 * Returns 0 on success, <0 on failure
 *
 * spider_net_हटाओ is called to हटाओ the device and unरेजिस्टरs the
 * net_device
 **/
अटल व्योम
spider_net_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev;
	काष्ठा spider_net_card *card;

	netdev = pci_get_drvdata(pdev);
	card = netdev_priv(netdev);

	रुको_event(card->रुकोq,
		   atomic_पढ़ो(&card->tx_समयout_task_counter) == 0);

	unरेजिस्टर_netdev(netdev);

	/* चयन off card */
	spider_net_ग_लिखो_reg(card, SPIDER_NET_CKRCTRL,
			     SPIDER_NET_CKRCTRL_STOP_VALUE);
	spider_net_ग_लिखो_reg(card, SPIDER_NET_CKRCTRL,
			     SPIDER_NET_CKRCTRL_RUN_VALUE);

	spider_net_unकरो_pci_setup(card);
	मुक्त_netdev(netdev);
पूर्ण

अटल काष्ठा pci_driver spider_net_driver = अणु
	.name		= spider_net_driver_name,
	.id_table	= spider_net_pci_tbl,
	.probe		= spider_net_probe,
	.हटाओ		= spider_net_हटाओ
पूर्ण;

/**
 * spider_net_init - init function when the driver is loaded
 *
 * spider_net_init रेजिस्टरs the device driver
 */
अटल पूर्णांक __init spider_net_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Spidernet version %s.\n", VERSION);

	अगर (rx_descriptors < SPIDER_NET_RX_DESCRIPTORS_MIN) अणु
		rx_descriptors = SPIDER_NET_RX_DESCRIPTORS_MIN;
		pr_info("adjusting rx descriptors to %i.\n", rx_descriptors);
	पूर्ण
	अगर (rx_descriptors > SPIDER_NET_RX_DESCRIPTORS_MAX) अणु
		rx_descriptors = SPIDER_NET_RX_DESCRIPTORS_MAX;
		pr_info("adjusting rx descriptors to %i.\n", rx_descriptors);
	पूर्ण
	अगर (tx_descriptors < SPIDER_NET_TX_DESCRIPTORS_MIN) अणु
		tx_descriptors = SPIDER_NET_TX_DESCRIPTORS_MIN;
		pr_info("adjusting tx descriptors to %i.\n", tx_descriptors);
	पूर्ण
	अगर (tx_descriptors > SPIDER_NET_TX_DESCRIPTORS_MAX) अणु
		tx_descriptors = SPIDER_NET_TX_DESCRIPTORS_MAX;
		pr_info("adjusting tx descriptors to %i.\n", tx_descriptors);
	पूर्ण

	वापस pci_रेजिस्टर_driver(&spider_net_driver);
पूर्ण

/**
 * spider_net_cleanup - निकास function when driver is unloaded
 *
 * spider_net_cleanup unरेजिस्टरs the device driver
 */
अटल व्योम __निकास spider_net_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&spider_net_driver);
पूर्ण

module_init(spider_net_init);
module_निकास(spider_net_cleanup);
