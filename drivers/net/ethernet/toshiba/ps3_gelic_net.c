<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  PS3 gelic network driver.
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2006, 2007 Sony Corporation
 *
 * This file is based on: spider_net.c
 *
 * (C) Copyright IBM Corp. 2005
 *
 * Authors : Utz Bacher <utz.bacher@de.ibm.com>
 *           Jens Osterkamp <Jens.Osterkamp@de.ibm.com>
 */

#अघोषित DEBUG

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>

#समावेश <linux/dma-mapping.h>
#समावेश <net/checksum.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/ps3.h>
#समावेश <यंत्र/lv1call.h>

#समावेश "ps3_gelic_net.h"
#समावेश "ps3_gelic_wireless.h"

#घोषणा DRV_NAME "Gelic Network Driver"
#घोषणा DRV_VERSION "2.0"

MODULE_AUTHOR("SCE Inc.");
MODULE_DESCRIPTION("Gelic Network driver");
MODULE_LICENSE("GPL");


/* set irq_mask */
पूर्णांक gelic_card_set_irq_mask(काष्ठा gelic_card *card, u64 mask)
अणु
	पूर्णांक status;

	status = lv1_net_set_पूर्णांकerrupt_mask(bus_id(card), dev_id(card),
					    mask, 0);
	अगर (status)
		dev_info(ctodev(card),
			 "%s failed %d\n", __func__, status);
	वापस status;
पूर्ण

अटल व्योम gelic_card_rx_irq_on(काष्ठा gelic_card *card)
अणु
	card->irq_mask |= GELIC_CARD_RXINT;
	gelic_card_set_irq_mask(card, card->irq_mask);
पूर्ण
अटल व्योम gelic_card_rx_irq_off(काष्ठा gelic_card *card)
अणु
	card->irq_mask &= ~GELIC_CARD_RXINT;
	gelic_card_set_irq_mask(card, card->irq_mask);
पूर्ण

अटल व्योम gelic_card_get_ether_port_status(काष्ठा gelic_card *card,
					     पूर्णांक inक्रमm)
अणु
	u64 v2;
	काष्ठा net_device *ether_netdev;

	lv1_net_control(bus_id(card), dev_id(card),
			GELIC_LV1_GET_ETH_PORT_STATUS,
			GELIC_LV1_VLAN_TX_ETHERNET_0, 0, 0,
			&card->ether_port_status, &v2);

	अगर (inक्रमm) अणु
		ether_netdev = card->netdev[GELIC_PORT_ETHERNET_0];
		अगर (card->ether_port_status & GELIC_LV1_ETHER_LINK_UP)
			netअगर_carrier_on(ether_netdev);
		अन्यथा
			netअगर_carrier_off(ether_netdev);
	पूर्ण
पूर्ण

/**
 * gelic_descr_get_status -- वापसs the status of a descriptor
 * @descr: descriptor to look at
 *
 * वापसs the status as in the dmac_cmd_status field of the descriptor
 */
अटल क्रमागत gelic_descr_dma_status
gelic_descr_get_status(काष्ठा gelic_descr *descr)
अणु
	वापस be32_to_cpu(descr->dmac_cmd_status) & GELIC_DESCR_DMA_STAT_MASK;
पूर्ण

अटल पूर्णांक gelic_card_set_link_mode(काष्ठा gelic_card *card, पूर्णांक mode)
अणु
	पूर्णांक status;
	u64 v1, v2;

	status = lv1_net_control(bus_id(card), dev_id(card),
				 GELIC_LV1_SET_NEGOTIATION_MODE,
				 GELIC_LV1_PHY_ETHERNET_0, mode, 0, &v1, &v2);
	अगर (status) अणु
		pr_info("%s: failed setting negotiation mode %d\n", __func__,
			status);
		वापस -EBUSY;
	पूर्ण

	card->link_mode = mode;
	वापस 0;
पूर्ण

/**
 * gelic_card_disable_txdmac - disables the transmit DMA controller
 * @card: card काष्ठाure
 *
 * gelic_card_disable_txdmac terminates processing on the DMA controller by
 * turing off DMA and issuing a क्रमce end
 */
अटल व्योम gelic_card_disable_txdmac(काष्ठा gelic_card *card)
अणु
	पूर्णांक status;

	/* this hvc blocks until the DMA in progress really stopped */
	status = lv1_net_stop_tx_dma(bus_id(card), dev_id(card));
	अगर (status)
		dev_err(ctodev(card),
			"lv1_net_stop_tx_dma failed, status=%d\n", status);
पूर्ण

/**
 * gelic_card_enable_rxdmac - enables the receive DMA controller
 * @card: card काष्ठाure
 *
 * gelic_card_enable_rxdmac enables the DMA controller by setting RX_DMA_EN
 * in the GDADMACCNTR रेजिस्टर
 */
अटल व्योम gelic_card_enable_rxdmac(काष्ठा gelic_card *card)
अणु
	पूर्णांक status;

#अगर_घोषित DEBUG
	अगर (gelic_descr_get_status(card->rx_chain.head) !=
	    GELIC_DESCR_DMA_CARDOWNED) अणु
		prपूर्णांकk(KERN_ERR "%s: status=%x\n", __func__,
		       be32_to_cpu(card->rx_chain.head->dmac_cmd_status));
		prपूर्णांकk(KERN_ERR "%s: nextphy=%x\n", __func__,
		       be32_to_cpu(card->rx_chain.head->next_descr_addr));
		prपूर्णांकk(KERN_ERR "%s: head=%p\n", __func__,
		       card->rx_chain.head);
	पूर्ण
#पूर्ण_अगर
	status = lv1_net_start_rx_dma(bus_id(card), dev_id(card),
				card->rx_chain.head->bus_addr, 0);
	अगर (status)
		dev_info(ctodev(card),
			 "lv1_net_start_rx_dma failed, status=%d\n", status);
पूर्ण

/**
 * gelic_card_disable_rxdmac - disables the receive DMA controller
 * @card: card काष्ठाure
 *
 * gelic_card_disable_rxdmac terminates processing on the DMA controller by
 * turing off DMA and issuing a क्रमce end
 */
अटल व्योम gelic_card_disable_rxdmac(काष्ठा gelic_card *card)
अणु
	पूर्णांक status;

	/* this hvc blocks until the DMA in progress really stopped */
	status = lv1_net_stop_rx_dma(bus_id(card), dev_id(card));
	अगर (status)
		dev_err(ctodev(card),
			"lv1_net_stop_rx_dma failed, %d\n", status);
पूर्ण

/**
 * gelic_descr_set_status -- sets the status of a descriptor
 * @descr: descriptor to change
 * @status: status to set in the descriptor
 *
 * changes the status to the specअगरied value. Doesn't change other bits
 * in the status
 */
अटल व्योम gelic_descr_set_status(काष्ठा gelic_descr *descr,
				   क्रमागत gelic_descr_dma_status status)
अणु
	descr->dmac_cmd_status = cpu_to_be32(status |
			(be32_to_cpu(descr->dmac_cmd_status) &
			 ~GELIC_DESCR_DMA_STAT_MASK));
	/*
	 * dma_cmd_status field is used to indicate whether the descriptor
	 * is valid or not.
	 * Usually caller of this function wants to inक्रमm that to the
	 * hardware, so we assure here the hardware sees the change.
	 */
	wmb();
पूर्ण

/**
 * gelic_card_reset_chain - reset status of a descriptor chain
 * @card: card काष्ठाure
 * @chain: address of chain
 * @start_descr: address of descriptor array
 *
 * Reset the status of dma descriptors to पढ़ोy state
 * and re-initialize the hardware chain क्रम later use
 */
अटल व्योम gelic_card_reset_chain(काष्ठा gelic_card *card,
				   काष्ठा gelic_descr_chain *chain,
				   काष्ठा gelic_descr *start_descr)
अणु
	काष्ठा gelic_descr *descr;

	क्रम (descr = start_descr; start_descr != descr->next; descr++) अणु
		gelic_descr_set_status(descr, GELIC_DESCR_DMA_CARDOWNED);
		descr->next_descr_addr = cpu_to_be32(descr->next->bus_addr);
	पूर्ण

	chain->head = start_descr;
	chain->tail = (descr - 1);

	(descr - 1)->next_descr_addr = 0;
पूर्ण

व्योम gelic_card_up(काष्ठा gelic_card *card)
अणु
	pr_debug("%s: called\n", __func__);
	mutex_lock(&card->upकरोwn_lock);
	अगर (atomic_inc_वापस(&card->users) == 1) अणु
		pr_debug("%s: real do\n", __func__);
		/* enable irq */
		gelic_card_set_irq_mask(card, card->irq_mask);
		/* start rx */
		gelic_card_enable_rxdmac(card);

		napi_enable(&card->napi);
	पूर्ण
	mutex_unlock(&card->upकरोwn_lock);
	pr_debug("%s: done\n", __func__);
पूर्ण

व्योम gelic_card_करोwn(काष्ठा gelic_card *card)
अणु
	u64 mask;
	pr_debug("%s: called\n", __func__);
	mutex_lock(&card->upकरोwn_lock);
	अगर (atomic_dec_अगर_positive(&card->users) == 0) अणु
		pr_debug("%s: real do\n", __func__);
		napi_disable(&card->napi);
		/*
		 * Disable irq. Wireless पूर्णांकerrupts will
		 * be disabled later अगर any
		 */
		mask = card->irq_mask & (GELIC_CARD_WLAN_EVENT_RECEIVED |
					 GELIC_CARD_WLAN_COMMAND_COMPLETED);
		gelic_card_set_irq_mask(card, mask);
		/* stop rx */
		gelic_card_disable_rxdmac(card);
		gelic_card_reset_chain(card, &card->rx_chain,
				       card->descr + GELIC_NET_TX_DESCRIPTORS);
		/* stop tx */
		gelic_card_disable_txdmac(card);
	पूर्ण
	mutex_unlock(&card->upकरोwn_lock);
	pr_debug("%s: done\n", __func__);
पूर्ण

/**
 * gelic_card_मुक्त_chain - मुक्त descriptor chain
 * @card: card काष्ठाure
 * @descr_in: address of desc
 */
अटल व्योम gelic_card_मुक्त_chain(काष्ठा gelic_card *card,
				  काष्ठा gelic_descr *descr_in)
अणु
	काष्ठा gelic_descr *descr;

	क्रम (descr = descr_in; descr && descr->bus_addr; descr = descr->next) अणु
		dma_unmap_single(ctodev(card), descr->bus_addr,
				 GELIC_DESCR_SIZE, DMA_BIसूचीECTIONAL);
		descr->bus_addr = 0;
	पूर्ण
पूर्ण

/**
 * gelic_card_init_chain - links descriptor chain
 * @card: card काष्ठाure
 * @chain: address of chain
 * @start_descr: address of descriptor array
 * @no: number of descriptors
 *
 * we manage a circular list that mirrors the hardware काष्ठाure,
 * except that the hardware uses bus addresses.
 *
 * वापसs 0 on success, <0 on failure
 */
अटल पूर्णांक gelic_card_init_chain(काष्ठा gelic_card *card,
				 काष्ठा gelic_descr_chain *chain,
				 काष्ठा gelic_descr *start_descr, पूर्णांक no)
अणु
	पूर्णांक i;
	काष्ठा gelic_descr *descr;

	descr = start_descr;
	स_रखो(descr, 0, माप(*descr) * no);

	/* set up the hardware poपूर्णांकers in each descriptor */
	क्रम (i = 0; i < no; i++, descr++) अणु
		gelic_descr_set_status(descr, GELIC_DESCR_DMA_NOT_IN_USE);
		descr->bus_addr =
			dma_map_single(ctodev(card), descr,
				       GELIC_DESCR_SIZE,
				       DMA_BIसूचीECTIONAL);

		अगर (!descr->bus_addr)
			जाओ iommu_error;

		descr->next = descr + 1;
		descr->prev = descr - 1;
	पूर्ण
	/* make them as ring */
	(descr - 1)->next = start_descr;
	start_descr->prev = (descr - 1);

	/* chain bus addr of hw descriptor */
	descr = start_descr;
	क्रम (i = 0; i < no; i++, descr++) अणु
		descr->next_descr_addr = cpu_to_be32(descr->next->bus_addr);
	पूर्ण

	chain->head = start_descr;
	chain->tail = start_descr;

	/* करो not chain last hw descriptor */
	(descr - 1)->next_descr_addr = 0;

	वापस 0;

iommu_error:
	क्रम (i--, descr--; 0 <= i; i--, descr--)
		अगर (descr->bus_addr)
			dma_unmap_single(ctodev(card), descr->bus_addr,
					 GELIC_DESCR_SIZE,
					 DMA_BIसूचीECTIONAL);
	वापस -ENOMEM;
पूर्ण

/**
 * gelic_descr_prepare_rx - reinitializes a rx descriptor
 * @card: card काष्ठाure
 * @descr: descriptor to re-init
 *
 * वापस 0 on success, <0 on failure
 *
 * allocates a new rx skb, iommu-maps it and attaches it to the descriptor.
 * Activate the descriptor state-wise
 */
अटल पूर्णांक gelic_descr_prepare_rx(काष्ठा gelic_card *card,
				  काष्ठा gelic_descr *descr)
अणु
	पूर्णांक offset;
	अचिन्हित पूर्णांक bufsize;

	अगर (gelic_descr_get_status(descr) !=  GELIC_DESCR_DMA_NOT_IN_USE)
		dev_info(ctodev(card), "%s: ERROR status\n", __func__);
	/* we need to round up the buffer size to a multiple of 128 */
	bufsize = ALIGN(GELIC_NET_MAX_MTU, GELIC_NET_RXBUF_ALIGN);

	/* and we need to have it 128 byte aligned, thereक्रमe we allocate a
	 * bit more */
	descr->skb = dev_alloc_skb(bufsize + GELIC_NET_RXBUF_ALIGN - 1);
	अगर (!descr->skb) अणु
		descr->buf_addr = 0; /* tell DMAC करोn't touch memory */
		वापस -ENOMEM;
	पूर्ण
	descr->buf_size = cpu_to_be32(bufsize);
	descr->dmac_cmd_status = 0;
	descr->result_size = 0;
	descr->valid_size = 0;
	descr->data_error = 0;

	offset = ((अचिन्हित दीर्घ)descr->skb->data) &
		(GELIC_NET_RXBUF_ALIGN - 1);
	अगर (offset)
		skb_reserve(descr->skb, GELIC_NET_RXBUF_ALIGN - offset);
	/* io-mmu-map the skb */
	descr->buf_addr = cpu_to_be32(dma_map_single(ctodev(card),
						     descr->skb->data,
						     GELIC_NET_MAX_MTU,
						     DMA_FROM_DEVICE));
	अगर (!descr->buf_addr) अणु
		dev_kमुक्त_skb_any(descr->skb);
		descr->skb = शून्य;
		dev_info(ctodev(card),
			 "%s:Could not iommu-map rx buffer\n", __func__);
		gelic_descr_set_status(descr, GELIC_DESCR_DMA_NOT_IN_USE);
		वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		gelic_descr_set_status(descr, GELIC_DESCR_DMA_CARDOWNED);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * gelic_card_release_rx_chain - मुक्त all skb of rx descr
 * @card: card काष्ठाure
 *
 */
अटल व्योम gelic_card_release_rx_chain(काष्ठा gelic_card *card)
अणु
	काष्ठा gelic_descr *descr = card->rx_chain.head;

	करो अणु
		अगर (descr->skb) अणु
			dma_unmap_single(ctodev(card),
					 be32_to_cpu(descr->buf_addr),
					 descr->skb->len,
					 DMA_FROM_DEVICE);
			descr->buf_addr = 0;
			dev_kमुक्त_skb_any(descr->skb);
			descr->skb = शून्य;
			gelic_descr_set_status(descr,
					       GELIC_DESCR_DMA_NOT_IN_USE);
		पूर्ण
		descr = descr->next;
	पूर्ण जबतक (descr != card->rx_chain.head);
पूर्ण

/**
 * gelic_card_fill_rx_chain - fills descriptors/skbs in the rx chains
 * @card: card काष्ठाure
 *
 * fills all descriptors in the rx chain: allocates skbs
 * and iommu-maps them.
 * वापसs 0 on success, < 0 on failure
 */
अटल पूर्णांक gelic_card_fill_rx_chain(काष्ठा gelic_card *card)
अणु
	काष्ठा gelic_descr *descr = card->rx_chain.head;
	पूर्णांक ret;

	करो अणु
		अगर (!descr->skb) अणु
			ret = gelic_descr_prepare_rx(card, descr);
			अगर (ret)
				जाओ शुरुआत;
		पूर्ण
		descr = descr->next;
	पूर्ण जबतक (descr != card->rx_chain.head);

	वापस 0;
शुरुआत:
	gelic_card_release_rx_chain(card);
	वापस ret;
पूर्ण

/**
 * gelic_card_alloc_rx_skbs - allocates rx skbs in rx descriptor chains
 * @card: card काष्ठाure
 *
 * वापसs 0 on success, < 0 on failure
 */
अटल पूर्णांक gelic_card_alloc_rx_skbs(काष्ठा gelic_card *card)
अणु
	काष्ठा gelic_descr_chain *chain;
	पूर्णांक ret;
	chain = &card->rx_chain;
	ret = gelic_card_fill_rx_chain(card);
	chain->tail = card->rx_top->prev; /* poपूर्णांक to the last */
	वापस ret;
पूर्ण

/**
 * gelic_descr_release_tx - processes a used tx descriptor
 * @card: card काष्ठाure
 * @descr: descriptor to release
 *
 * releases a used tx descriptor (unmapping, मुक्तing of skb)
 */
अटल व्योम gelic_descr_release_tx(काष्ठा gelic_card *card,
				       काष्ठा gelic_descr *descr)
अणु
	काष्ठा sk_buff *skb = descr->skb;

	BUG_ON(!(be32_to_cpu(descr->data_status) & GELIC_DESCR_TX_TAIL));

	dma_unmap_single(ctodev(card), be32_to_cpu(descr->buf_addr), skb->len,
			 DMA_TO_DEVICE);
	dev_kमुक्त_skb_any(skb);

	descr->buf_addr = 0;
	descr->buf_size = 0;
	descr->next_descr_addr = 0;
	descr->result_size = 0;
	descr->valid_size = 0;
	descr->data_status = 0;
	descr->data_error = 0;
	descr->skb = शून्य;

	/* set descr status */
	gelic_descr_set_status(descr, GELIC_DESCR_DMA_NOT_IN_USE);
पूर्ण

अटल व्योम gelic_card_stop_queues(काष्ठा gelic_card *card)
अणु
	netअगर_stop_queue(card->netdev[GELIC_PORT_ETHERNET_0]);

	अगर (card->netdev[GELIC_PORT_WIRELESS])
		netअगर_stop_queue(card->netdev[GELIC_PORT_WIRELESS]);
पूर्ण
अटल व्योम gelic_card_wake_queues(काष्ठा gelic_card *card)
अणु
	netअगर_wake_queue(card->netdev[GELIC_PORT_ETHERNET_0]);

	अगर (card->netdev[GELIC_PORT_WIRELESS])
		netअगर_wake_queue(card->netdev[GELIC_PORT_WIRELESS]);
पूर्ण
/**
 * gelic_card_release_tx_chain - processes sent tx descriptors
 * @card: adapter काष्ठाure
 * @stop: net_stop sequence
 *
 * releases the tx descriptors that gelic has finished with
 */
अटल व्योम gelic_card_release_tx_chain(काष्ठा gelic_card *card, पूर्णांक stop)
अणु
	काष्ठा gelic_descr_chain *tx_chain;
	क्रमागत gelic_descr_dma_status status;
	काष्ठा net_device *netdev;
	पूर्णांक release = 0;

	क्रम (tx_chain = &card->tx_chain;
	     tx_chain->head != tx_chain->tail && tx_chain->tail;
	     tx_chain->tail = tx_chain->tail->next) अणु
		status = gelic_descr_get_status(tx_chain->tail);
		netdev = tx_chain->tail->skb->dev;
		चयन (status) अणु
		हाल GELIC_DESCR_DMA_RESPONSE_ERROR:
		हाल GELIC_DESCR_DMA_PROTECTION_ERROR:
		हाल GELIC_DESCR_DMA_FORCE_END:
			अगर (prपूर्णांकk_ratelimit())
				dev_info(ctodev(card),
					 "%s: forcing end of tx descriptor " \
					 "with status %x\n",
					 __func__, status);
			netdev->stats.tx_dropped++;
			अवरोध;

		हाल GELIC_DESCR_DMA_COMPLETE:
			अगर (tx_chain->tail->skb) अणु
				netdev->stats.tx_packets++;
				netdev->stats.tx_bytes +=
					tx_chain->tail->skb->len;
			पूर्ण
			अवरोध;

		हाल GELIC_DESCR_DMA_CARDOWNED:
			/* pending tx request */
		शेष:
			/* any other value (== GELIC_DESCR_DMA_NOT_IN_USE) */
			अगर (!stop)
				जाओ out;
		पूर्ण
		gelic_descr_release_tx(card, tx_chain->tail);
		release ++;
	पूर्ण
out:
	अगर (!stop && release)
		gelic_card_wake_queues(card);
पूर्ण

/**
 * gelic_net_set_multi - sets multicast addresses and promisc flags
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * gelic_net_set_multi configures multicast addresses as needed क्रम the
 * netdev पूर्णांकerface. It also sets up multicast, allmulti and promisc
 * flags appropriately
 */
व्योम gelic_net_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_card *card = netdev_card(netdev);
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित पूर्णांक i;
	uपूर्णांक8_t *p;
	u64 addr;
	पूर्णांक status;

	/* clear all multicast address */
	status = lv1_net_हटाओ_multicast_address(bus_id(card), dev_id(card),
						  0, 1);
	अगर (status)
		dev_err(ctodev(card),
			"lv1_net_remove_multicast_address failed %d\n",
			status);
	/* set broadcast address */
	status = lv1_net_add_multicast_address(bus_id(card), dev_id(card),
					       GELIC_NET_BROADCAST_ADDR, 0);
	अगर (status)
		dev_err(ctodev(card),
			"lv1_net_add_multicast_address failed, %d\n",
			status);

	अगर ((netdev->flags & IFF_ALLMULTI) ||
	    (netdev_mc_count(netdev) > GELIC_NET_MC_COUNT_MAX)) अणु
		status = lv1_net_add_multicast_address(bus_id(card),
						       dev_id(card),
						       0, 1);
		अगर (status)
			dev_err(ctodev(card),
				"lv1_net_add_multicast_address failed, %d\n",
				status);
		वापस;
	पूर्ण

	/* set multicast addresses */
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		addr = 0;
		p = ha->addr;
		क्रम (i = 0; i < ETH_ALEN; i++) अणु
			addr <<= 8;
			addr |= *p++;
		पूर्ण
		status = lv1_net_add_multicast_address(bus_id(card),
						       dev_id(card),
						       addr, 0);
		अगर (status)
			dev_err(ctodev(card),
				"lv1_net_add_multicast_address failed, %d\n",
				status);
	पूर्ण
पूर्ण

/**
 * gelic_net_stop - called upon अगरconfig करोwn
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * always वापसs 0
 */
पूर्णांक gelic_net_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_card *card;

	pr_debug("%s: start\n", __func__);

	netअगर_stop_queue(netdev);
	netअगर_carrier_off(netdev);

	card = netdev_card(netdev);
	gelic_card_करोwn(card);

	pr_debug("%s: done\n", __func__);
	वापस 0;
पूर्ण

/**
 * gelic_card_get_next_tx_descr - वापसs the next available tx descriptor
 * @card: device काष्ठाure to get descriptor from
 *
 * वापसs the address of the next descriptor, or शून्य अगर not available.
 */
अटल काष्ठा gelic_descr *
gelic_card_get_next_tx_descr(काष्ठा gelic_card *card)
अणु
	अगर (!card->tx_chain.head)
		वापस शून्य;
	/*  see अगर the next descriptor is मुक्त */
	अगर (card->tx_chain.tail != card->tx_chain.head->next &&
	    gelic_descr_get_status(card->tx_chain.head) ==
	    GELIC_DESCR_DMA_NOT_IN_USE)
		वापस card->tx_chain.head;
	अन्यथा
		वापस शून्य;

पूर्ण

/**
 * gelic_net_set_txdescr_cmdstat - sets the tx descriptor command field
 * @descr: descriptor काष्ठाure to fill out
 * @skb: packet to consider
 *
 * fills out the command and status field of the descriptor काष्ठाure,
 * depending on hardware checksum settings. This function assumes a wmb()
 * has executed beक्रमe.
 */
अटल व्योम gelic_descr_set_tx_cmdstat(काष्ठा gelic_descr *descr,
				       काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		descr->dmac_cmd_status =
			cpu_to_be32(GELIC_DESCR_DMA_CMD_NO_CHKSUM |
				    GELIC_DESCR_TX_DMA_FRAME_TAIL);
	अन्यथा अणु
		/* is packet ip?
		 * अगर yes: tcp? udp? */
		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			अगर (ip_hdr(skb)->protocol == IPPROTO_TCP)
				descr->dmac_cmd_status =
				cpu_to_be32(GELIC_DESCR_DMA_CMD_TCP_CHKSUM |
					    GELIC_DESCR_TX_DMA_FRAME_TAIL);

			अन्यथा अगर (ip_hdr(skb)->protocol == IPPROTO_UDP)
				descr->dmac_cmd_status =
				cpu_to_be32(GELIC_DESCR_DMA_CMD_UDP_CHKSUM |
					    GELIC_DESCR_TX_DMA_FRAME_TAIL);
			अन्यथा	/*
				 * the stack should checksum non-tcp and non-udp
				 * packets on his own: NETIF_F_IP_CSUM
				 */
				descr->dmac_cmd_status =
				cpu_to_be32(GELIC_DESCR_DMA_CMD_NO_CHKSUM |
					    GELIC_DESCR_TX_DMA_FRAME_TAIL);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *gelic_put_vlan_tag(काष्ठा sk_buff *skb,
						 अचिन्हित लघु tag)
अणु
	काष्ठा vlan_ethhdr *veth;
	अटल अचिन्हित पूर्णांक c;

	अगर (skb_headroom(skb) < VLAN_HLEN) अणु
		काष्ठा sk_buff *sk_पंचांगp = skb;
		pr_debug("%s: hd=%d c=%ud\n", __func__, skb_headroom(skb), c);
		skb = skb_पुनः_स्मृति_headroom(sk_पंचांगp, VLAN_HLEN);
		अगर (!skb)
			वापस शून्य;
		dev_kमुक्त_skb_any(sk_पंचांगp);
	पूर्ण
	veth = skb_push(skb, VLAN_HLEN);

	/* Move the mac addresses to the top of buffer */
	स_हटाओ(skb->data, skb->data + VLAN_HLEN, 2 * ETH_ALEN);

	veth->h_vlan_proto = cpu_to_be16(ETH_P_8021Q);
	veth->h_vlan_TCI = htons(tag);

	वापस skb;
पूर्ण

/**
 * gelic_descr_prepare_tx - setup a descriptor क्रम sending packets
 * @card: card काष्ठाure
 * @descr: descriptor काष्ठाure
 * @skb: packet to use
 *
 * वापसs 0 on success, <0 on failure.
 *
 */
अटल पूर्णांक gelic_descr_prepare_tx(काष्ठा gelic_card *card,
				  काष्ठा gelic_descr *descr,
				  काष्ठा sk_buff *skb)
अणु
	dma_addr_t buf;

	अगर (card->vlan_required) अणु
		काष्ठा sk_buff *skb_पंचांगp;
		क्रमागत gelic_port_type type;

		type = netdev_port(skb->dev)->type;
		skb_पंचांगp = gelic_put_vlan_tag(skb,
					     card->vlan[type].tx);
		अगर (!skb_पंचांगp)
			वापस -ENOMEM;
		skb = skb_पंचांगp;
	पूर्ण

	buf = dma_map_single(ctodev(card), skb->data, skb->len, DMA_TO_DEVICE);

	अगर (!buf) अणु
		dev_err(ctodev(card),
			"dma map 2 failed (%p, %i). Dropping packet\n",
			skb->data, skb->len);
		वापस -ENOMEM;
	पूर्ण

	descr->buf_addr = cpu_to_be32(buf);
	descr->buf_size = cpu_to_be32(skb->len);
	descr->skb = skb;
	descr->data_status = 0;
	descr->next_descr_addr = 0; /* terminate hw descr */
	gelic_descr_set_tx_cmdstat(descr, skb);

	/* bump मुक्त descriptor poपूर्णांकer */
	card->tx_chain.head = descr->next;
	वापस 0;
पूर्ण

/**
 * gelic_card_kick_txdma - enables TX DMA processing
 * @card: card काष्ठाure
 * @descr: descriptor address to enable TX processing at
 *
 */
अटल पूर्णांक gelic_card_kick_txdma(काष्ठा gelic_card *card,
				 काष्ठा gelic_descr *descr)
अणु
	पूर्णांक status = 0;

	अगर (card->tx_dma_progress)
		वापस 0;

	अगर (gelic_descr_get_status(descr) == GELIC_DESCR_DMA_CARDOWNED) अणु
		card->tx_dma_progress = 1;
		status = lv1_net_start_tx_dma(bus_id(card), dev_id(card),
					      descr->bus_addr, 0);
		अगर (status) अणु
			card->tx_dma_progress = 0;
			dev_info(ctodev(card), "lv1_net_start_txdma failed," \
				 "status=%d\n", status);
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**
 * gelic_net_xmit - transmits a frame over the device
 * @skb: packet to send out
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * वापसs NETDEV_TX_OK on success, NETDEV_TX_BUSY on failure
 */
netdev_tx_t gelic_net_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_card *card = netdev_card(netdev);
	काष्ठा gelic_descr *descr;
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->tx_lock, flags);

	gelic_card_release_tx_chain(card, 0);

	descr = gelic_card_get_next_tx_descr(card);
	अगर (!descr) अणु
		/*
		 * no more descriptors मुक्त
		 */
		gelic_card_stop_queues(card);
		spin_unlock_irqrestore(&card->tx_lock, flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	result = gelic_descr_prepare_tx(card, descr, skb);
	अगर (result) अणु
		/*
		 * DMA map failed.  As chances are that failure
		 * would जारी, just release skb and वापस
		 */
		netdev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
		spin_unlock_irqrestore(&card->tx_lock, flags);
		वापस NETDEV_TX_OK;
	पूर्ण
	/*
	 * link this prepared descriptor to previous one
	 * to achieve high perक्रमmance
	 */
	descr->prev->next_descr_addr = cpu_to_be32(descr->bus_addr);
	/*
	 * as hardware descriptor is modअगरied in the above lines,
	 * ensure that the hardware sees it
	 */
	wmb();
	अगर (gelic_card_kick_txdma(card, descr)) अणु
		/*
		 * kick failed.
		 * release descriptor which was just prepared
		 */
		netdev->stats.tx_dropped++;
		/* करोn't trigger BUG_ON() in gelic_descr_release_tx */
		descr->data_status = cpu_to_be32(GELIC_DESCR_TX_TAIL);
		gelic_descr_release_tx(card, descr);
		/* reset head */
		card->tx_chain.head = descr;
		/* reset hw termination */
		descr->prev->next_descr_addr = 0;
		dev_info(ctodev(card), "%s: kick failure\n", __func__);
	पूर्ण

	spin_unlock_irqrestore(&card->tx_lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * gelic_net_pass_skb_up - takes an skb from a descriptor and passes it on
 * @descr: descriptor to process
 * @card: card काष्ठाure
 * @netdev: net_device काष्ठाure to be passed packet
 *
 * iommu-unmaps the skb, fills out skb काष्ठाure and passes the data to the
 * stack. The descriptor state is not changed.
 */
अटल व्योम gelic_net_pass_skb_up(काष्ठा gelic_descr *descr,
				  काष्ठा gelic_card *card,
				  काष्ठा net_device *netdev)

अणु
	काष्ठा sk_buff *skb = descr->skb;
	u32 data_status, data_error;

	data_status = be32_to_cpu(descr->data_status);
	data_error = be32_to_cpu(descr->data_error);
	/* unmap skb buffer */
	dma_unmap_single(ctodev(card), be32_to_cpu(descr->buf_addr),
			 GELIC_NET_MAX_MTU,
			 DMA_FROM_DEVICE);

	skb_put(skb, be32_to_cpu(descr->valid_size)?
		be32_to_cpu(descr->valid_size) :
		be32_to_cpu(descr->result_size));
	अगर (!descr->valid_size)
		dev_info(ctodev(card), "buffer full %x %x %x\n",
			 be32_to_cpu(descr->result_size),
			 be32_to_cpu(descr->buf_size),
			 be32_to_cpu(descr->dmac_cmd_status));

	descr->skb = शून्य;
	/*
	 * the card put 2 bytes vlan tag in front
	 * of the ethernet frame
	 */
	skb_pull(skb, 2);
	skb->protocol = eth_type_trans(skb, netdev);

	/* checksum offload */
	अगर (netdev->features & NETIF_F_RXCSUM) अणु
		अगर ((data_status & GELIC_DESCR_DATA_STATUS_CHK_MASK) &&
		    (!(data_error & GELIC_DESCR_DATA_ERROR_CHK_MASK)))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		अन्यथा
			skb_checksum_none_निश्चित(skb);
	पूर्ण अन्यथा
		skb_checksum_none_निश्चित(skb);

	/* update netdevice statistics */
	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += skb->len;

	/* pass skb up to stack */
	netअगर_receive_skb(skb);
पूर्ण

/**
 * gelic_card_decode_one_descr - processes an rx descriptor
 * @card: card काष्ठाure
 *
 * वापसs 1 अगर a packet has been sent to the stack, otherwise 0
 *
 * processes an rx descriptor by iommu-unmapping the data buffer and passing
 * the packet up to the stack
 */
अटल पूर्णांक gelic_card_decode_one_descr(काष्ठा gelic_card *card)
अणु
	क्रमागत gelic_descr_dma_status status;
	काष्ठा gelic_descr_chain *chain = &card->rx_chain;
	काष्ठा gelic_descr *descr = chain->head;
	काष्ठा net_device *netdev = शून्य;
	पूर्णांक dmac_chain_ended;

	status = gelic_descr_get_status(descr);

	अगर (status == GELIC_DESCR_DMA_CARDOWNED)
		वापस 0;

	अगर (status == GELIC_DESCR_DMA_NOT_IN_USE) अणु
		dev_dbg(ctodev(card), "dormant descr? %p\n", descr);
		वापस 0;
	पूर्ण

	/* netdevice select */
	अगर (card->vlan_required) अणु
		अचिन्हित पूर्णांक i;
		u16 vid;
		vid = *(u16 *)(descr->skb->data) & VLAN_VID_MASK;
		क्रम (i = 0; i < GELIC_PORT_MAX; i++) अणु
			अगर (card->vlan[i].rx == vid) अणु
				netdev = card->netdev[i];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (GELIC_PORT_MAX <= i) अणु
			pr_info("%s: unknown packet vid=%x\n", __func__, vid);
			जाओ refill;
		पूर्ण
	पूर्ण अन्यथा
		netdev = card->netdev[GELIC_PORT_ETHERNET_0];

	अगर ((status == GELIC_DESCR_DMA_RESPONSE_ERROR) ||
	    (status == GELIC_DESCR_DMA_PROTECTION_ERROR) ||
	    (status == GELIC_DESCR_DMA_FORCE_END)) अणु
		dev_info(ctodev(card), "dropping RX descriptor with state %x\n",
			 status);
		netdev->stats.rx_dropped++;
		जाओ refill;
	पूर्ण

	अगर (status == GELIC_DESCR_DMA_BUFFER_FULL) अणु
		/*
		 * Buffer full would occur अगर and only अगर
		 * the frame length was दीर्घer than the size of this
		 * descriptor's buffer.  If the frame length was equal
		 * to or लघुer than buffer'size, FRAME_END condition
		 * would occur.
		 * Anyway this frame was दीर्घer than the MTU,
		 * just drop it.
		 */
		dev_info(ctodev(card), "overlength frame\n");
		जाओ refill;
	पूर्ण
	/*
	 * descriptors any other than FRAME_END here should
	 * be treated as error.
	 */
	अगर (status != GELIC_DESCR_DMA_FRAME_END) अणु
		dev_dbg(ctodev(card), "RX descriptor with state %x\n",
			status);
		जाओ refill;
	पूर्ण

	/* ok, we've got a packet in descr */
	gelic_net_pass_skb_up(descr, card, netdev);
refill:

	/* is the current descriptor terminated with next_descr == शून्य? */
	dmac_chain_ended =
		be32_to_cpu(descr->dmac_cmd_status) &
		GELIC_DESCR_RX_DMA_CHAIN_END;
	/*
	 * So that always DMAC can see the end
	 * of the descriptor chain to aव्योम
	 * from unwanted DMAC overrun.
	 */
	descr->next_descr_addr = 0;

	/* change the descriptor state: */
	gelic_descr_set_status(descr, GELIC_DESCR_DMA_NOT_IN_USE);

	/*
	 * this call can fail, but क्रम now, just leave this
	 * descriptor without skb
	 */
	gelic_descr_prepare_rx(card, descr);

	chain->tail = descr;
	chain->head = descr->next;

	/*
	 * Set this descriptor the end of the chain.
	 */
	descr->prev->next_descr_addr = cpu_to_be32(descr->bus_addr);

	/*
	 * If dmac chain was met, DMAC stopped.
	 * thus re-enable it
	 */

	अगर (dmac_chain_ended)
		gelic_card_enable_rxdmac(card);

	वापस 1;
पूर्ण

/**
 * gelic_net_poll - NAPI poll function called by the stack to वापस packets
 * @napi: napi काष्ठाure
 * @budget: number of packets we can pass to the stack at most
 *
 * वापसs the number of the processed packets
 *
 */
अटल पूर्णांक gelic_net_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा gelic_card *card = container_of(napi, काष्ठा gelic_card, napi);
	पूर्णांक packets_करोne = 0;

	जबतक (packets_करोne < budget) अणु
		अगर (!gelic_card_decode_one_descr(card))
			अवरोध;

		packets_करोne++;
	पूर्ण

	अगर (packets_करोne < budget) अणु
		napi_complete_करोne(napi, packets_करोne);
		gelic_card_rx_irq_on(card);
	पूर्ण
	वापस packets_करोne;
पूर्ण

/*
 * gelic_card_पूर्णांकerrupt - event handler क्रम gelic_net
 */
अटल irqवापस_t gelic_card_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा gelic_card *card = ptr;
	u64 status;

	status = card->irq_status;

	अगर (!status)
		वापस IRQ_NONE;

	status &= card->irq_mask;

	अगर (status & GELIC_CARD_RXINT) अणु
		gelic_card_rx_irq_off(card);
		napi_schedule(&card->napi);
	पूर्ण

	अगर (status & GELIC_CARD_TXINT) अणु
		spin_lock_irqsave(&card->tx_lock, flags);
		card->tx_dma_progress = 0;
		gelic_card_release_tx_chain(card, 0);
		/* kick outstanding tx descriptor अगर any */
		gelic_card_kick_txdma(card, card->tx_chain.tail);
		spin_unlock_irqrestore(&card->tx_lock, flags);
	पूर्ण

	/* ether port status changed */
	अगर (status & GELIC_CARD_PORT_STATUS_CHANGED)
		gelic_card_get_ether_port_status(card, 1);

#अगर_घोषित CONFIG_GELIC_WIRELESS
	अगर (status & (GELIC_CARD_WLAN_EVENT_RECEIVED |
		      GELIC_CARD_WLAN_COMMAND_COMPLETED))
		gelic_wl_पूर्णांकerrupt(card->netdev[GELIC_PORT_WIRELESS], status);
#पूर्ण_अगर

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * gelic_net_poll_controller - artअगरicial पूर्णांकerrupt क्रम netconsole etc.
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * see Documentation/networking/netconsole.rst
 */
व्योम gelic_net_poll_controller(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_card *card = netdev_card(netdev);

	gelic_card_set_irq_mask(card, 0);
	gelic_card_पूर्णांकerrupt(netdev->irq, netdev);
	gelic_card_set_irq_mask(card, card->irq_mask);
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_POLL_CONTROLLER */

/**
 * gelic_net_खोलो - called upon अगरconfig up
 * @netdev: पूर्णांकerface device काष्ठाure
 *
 * वापसs 0 on success, <0 on failure
 *
 * gelic_net_खोलो allocates all the descriptors and memory needed क्रम
 * operation, sets up multicast list and enables पूर्णांकerrupts
 */
पूर्णांक gelic_net_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_card *card = netdev_card(netdev);

	dev_dbg(ctodev(card), " -> %s %p\n", __func__, netdev);

	gelic_card_up(card);

	netअगर_start_queue(netdev);
	gelic_card_get_ether_port_status(card, 1);

	dev_dbg(ctodev(card), " <- %s\n", __func__);
	वापस 0;
पूर्ण

व्योम gelic_net_get_drvinfo(काष्ठा net_device *netdev,
			   काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
पूर्ण

अटल पूर्णांक gelic_ether_get_link_ksettings(काष्ठा net_device *netdev,
					  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा gelic_card *card = netdev_card(netdev);
	u32 supported, advertising;

	gelic_card_get_ether_port_status(card, 0);

	अगर (card->ether_port_status & GELIC_LV1_ETHER_FULL_DUPLEX)
		cmd->base.duplex = DUPLEX_FULL;
	अन्यथा
		cmd->base.duplex = DUPLEX_HALF;

	चयन (card->ether_port_status & GELIC_LV1_ETHER_SPEED_MASK) अणु
	हाल GELIC_LV1_ETHER_SPEED_10:
		cmd->base.speed = SPEED_10;
		अवरोध;
	हाल GELIC_LV1_ETHER_SPEED_100:
		cmd->base.speed = SPEED_100;
		अवरोध;
	हाल GELIC_LV1_ETHER_SPEED_1000:
		cmd->base.speed = SPEED_1000;
		अवरोध;
	शेष:
		pr_info("%s: speed unknown\n", __func__);
		cmd->base.speed = SPEED_10;
		अवरोध;
	पूर्ण

	supported = SUPPORTED_TP | SUPPORTED_Autoneg |
			SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
			SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
			SUPPORTED_1000baseT_Full;
	advertising = supported;
	अगर (card->link_mode & GELIC_LV1_ETHER_AUTO_NEG) अणु
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	पूर्ण अन्यथा अणु
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
		advertising &= ~ADVERTISED_Autoneg;
	पूर्ण
	cmd->base.port = PORT_TP;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक
gelic_ether_set_link_ksettings(काष्ठा net_device *netdev,
			       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा gelic_card *card = netdev_card(netdev);
	u64 mode;
	पूर्णांक ret;

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		mode = GELIC_LV1_ETHER_AUTO_NEG;
	पूर्ण अन्यथा अणु
		चयन (cmd->base.speed) अणु
		हाल SPEED_10:
			mode = GELIC_LV1_ETHER_SPEED_10;
			अवरोध;
		हाल SPEED_100:
			mode = GELIC_LV1_ETHER_SPEED_100;
			अवरोध;
		हाल SPEED_1000:
			mode = GELIC_LV1_ETHER_SPEED_1000;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (cmd->base.duplex == DUPLEX_FULL) अणु
			mode |= GELIC_LV1_ETHER_FULL_DUPLEX;
		पूर्ण अन्यथा अगर (cmd->base.speed == SPEED_1000) अणु
			pr_info("1000 half duplex is not supported.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = gelic_card_set_link_mode(card, mode);

	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम gelic_net_get_wol(काष्ठा net_device *netdev,
			      काष्ठा ethtool_wolinfo *wol)
अणु
	अगर (0 <= ps3_compare_firmware_version(2, 2, 0))
		wol->supported = WAKE_MAGIC;
	अन्यथा
		wol->supported = 0;

	wol->wolopts = ps3_sys_manager_get_wol() ? wol->supported : 0;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण
अटल पूर्णांक gelic_net_set_wol(काष्ठा net_device *netdev,
			     काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक status;
	काष्ठा gelic_card *card;
	u64 v1, v2;

	अगर (ps3_compare_firmware_version(2, 2, 0) < 0 ||
	    !capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EINVAL;

	card = netdev_card(netdev);
	अगर (wol->wolopts & WAKE_MAGIC) अणु
		status = lv1_net_control(bus_id(card), dev_id(card),
					 GELIC_LV1_SET_WOL,
					 GELIC_LV1_WOL_MAGIC_PACKET,
					 0, GELIC_LV1_WOL_MP_ENABLE,
					 &v1, &v2);
		अगर (status) अणु
			pr_info("%s: enabling WOL failed %d\n", __func__,
				status);
			status = -EIO;
			जाओ करोne;
		पूर्ण
		status = lv1_net_control(bus_id(card), dev_id(card),
					 GELIC_LV1_SET_WOL,
					 GELIC_LV1_WOL_ADD_MATCH_ADDR,
					 0, GELIC_LV1_WOL_MATCH_ALL,
					 &v1, &v2);
		अगर (!status)
			ps3_sys_manager_set_wol(1);
		अन्यथा अणु
			pr_info("%s: enabling WOL filter failed %d\n",
				__func__, status);
			status = -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = lv1_net_control(bus_id(card), dev_id(card),
					 GELIC_LV1_SET_WOL,
					 GELIC_LV1_WOL_MAGIC_PACKET,
					 0, GELIC_LV1_WOL_MP_DISABLE,
					 &v1, &v2);
		अगर (status) अणु
			pr_info("%s: disabling WOL failed %d\n", __func__,
				status);
			status = -EIO;
			जाओ करोne;
		पूर्ण
		status = lv1_net_control(bus_id(card), dev_id(card),
					 GELIC_LV1_SET_WOL,
					 GELIC_LV1_WOL_DELETE_MATCH_ADDR,
					 0, GELIC_LV1_WOL_MATCH_ALL,
					 &v1, &v2);
		अगर (!status)
			ps3_sys_manager_set_wol(0);
		अन्यथा अणु
			pr_info("%s: removing WOL filter failed %d\n",
				__func__, status);
			status = -EIO;
		पूर्ण
	पूर्ण
करोne:
	वापस status;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops gelic_ether_ethtool_ops = अणु
	.get_drvinfo	= gelic_net_get_drvinfo,
	.get_link	= ethtool_op_get_link,
	.get_wol	= gelic_net_get_wol,
	.set_wol	= gelic_net_set_wol,
	.get_link_ksettings = gelic_ether_get_link_ksettings,
	.set_link_ksettings = gelic_ether_set_link_ksettings,
पूर्ण;

/**
 * gelic_net_tx_समयout_task - task scheduled by the watchकरोg समयout
 * function (to be called not under पूर्णांकerrupt status)
 * @work: work is context of tx timout task
 *
 * called as task when tx hangs, resets पूर्णांकerface (अगर पूर्णांकerface is up)
 */
अटल व्योम gelic_net_tx_समयout_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gelic_card *card =
		container_of(work, काष्ठा gelic_card, tx_समयout_task);
	काष्ठा net_device *netdev = card->netdev[GELIC_PORT_ETHERNET_0];

	dev_info(ctodev(card), "%s:Timed out. Restarting...\n", __func__);

	अगर (!(netdev->flags & IFF_UP))
		जाओ out;

	netअगर_device_detach(netdev);
	gelic_net_stop(netdev);

	gelic_net_खोलो(netdev);
	netअगर_device_attach(netdev);

out:
	atomic_dec(&card->tx_समयout_task_counter);
पूर्ण

/**
 * gelic_net_tx_समयout - called when the tx समयout watchकरोg kicks in.
 * @netdev: पूर्णांकerface device काष्ठाure
 * @txqueue: unused
 *
 * called, अगर tx hangs. Schedules a task that resets the पूर्णांकerface
 */
व्योम gelic_net_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा gelic_card *card;

	card = netdev_card(netdev);
	atomic_inc(&card->tx_समयout_task_counter);
	अगर (netdev->flags & IFF_UP)
		schedule_work(&card->tx_समयout_task);
	अन्यथा
		atomic_dec(&card->tx_समयout_task_counter);
पूर्ण

अटल स्थिर काष्ठा net_device_ops gelic_netdevice_ops = अणु
	.nकरो_खोलो = gelic_net_खोलो,
	.nकरो_stop = gelic_net_stop,
	.nकरो_start_xmit = gelic_net_xmit,
	.nकरो_set_rx_mode = gelic_net_set_multi,
	.nकरो_tx_समयout = gelic_net_tx_समयout,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_validate_addr = eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = gelic_net_poll_controller,
#पूर्ण_अगर
पूर्ण;

/**
 * gelic_ether_setup_netdev_ops - initialization of net_device operations
 * @netdev: net_device काष्ठाure
 * @napi: napi काष्ठाure
 *
 * fills out function poपूर्णांकers in the net_device काष्ठाure
 */
अटल व्योम gelic_ether_setup_netdev_ops(काष्ठा net_device *netdev,
					 काष्ठा napi_काष्ठा *napi)
अणु
	netdev->watchकरोg_समयo = GELIC_NET_WATCHDOG_TIMEOUT;
	/* NAPI */
	netअगर_napi_add(netdev, napi, gelic_net_poll, NAPI_POLL_WEIGHT);
	netdev->ethtool_ops = &gelic_ether_ethtool_ops;
	netdev->netdev_ops = &gelic_netdevice_ops;
पूर्ण

/**
 * gelic_ether_setup_netdev - initialization of net_device
 * @netdev: net_device काष्ठाure
 * @card: card काष्ठाure
 *
 * Returns 0 on success or <0 on failure
 *
 * gelic_ether_setup_netdev initializes the net_device काष्ठाure
 * and रेजिस्टर it.
 **/
पूर्णांक gelic_net_setup_netdev(काष्ठा net_device *netdev, काष्ठा gelic_card *card)
अणु
	पूर्णांक status;
	u64 v1, v2;

	netdev->hw_features = NETIF_F_IP_CSUM | NETIF_F_RXCSUM;

	netdev->features = NETIF_F_IP_CSUM;
	अगर (GELIC_CARD_RX_CSUM_DEFAULT)
		netdev->features |= NETIF_F_RXCSUM;

	status = lv1_net_control(bus_id(card), dev_id(card),
				 GELIC_LV1_GET_MAC_ADDRESS,
				 0, 0, 0, &v1, &v2);
	v1 <<= 16;
	अगर (status || !is_valid_ether_addr((u8 *)&v1)) अणु
		dev_info(ctodev(card),
			 "%s:lv1_net_control GET_MAC_ADDR failed %d\n",
			 __func__, status);
		वापस -EINVAL;
	पूर्ण
	स_नकल(netdev->dev_addr, &v1, ETH_ALEN);

	अगर (card->vlan_required) अणु
		netdev->hard_header_len += VLAN_HLEN;
		/*
		 * As vlan is पूर्णांकernally used,
		 * we can not receive vlan packets
		 */
		netdev->features |= NETIF_F_VLAN_CHALLENGED;
	पूर्ण

	/* MTU range: 64 - 1518 */
	netdev->min_mtu = GELIC_NET_MIN_MTU;
	netdev->max_mtu = GELIC_NET_MAX_MTU;

	status = रेजिस्टर_netdev(netdev);
	अगर (status) अणु
		dev_err(ctodev(card), "%s:Couldn't register %s %d\n",
			__func__, netdev->name, status);
		वापस status;
	पूर्ण
	dev_info(ctodev(card), "%s: MAC addr %pM\n",
		 netdev->name, netdev->dev_addr);

	वापस 0;
पूर्ण

/**
 * gelic_alloc_card_net - allocates net_device and card काष्ठाure
 *
 * वापसs the card काष्ठाure or शून्य in हाल of errors
 *
 * the card and net_device काष्ठाures are linked to each other
 */
#घोषणा GELIC_ALIGN (32)
अटल काष्ठा gelic_card *gelic_alloc_card_net(काष्ठा net_device **netdev)
अणु
	काष्ठा gelic_card *card;
	काष्ठा gelic_port *port;
	व्योम *p;
	माप_प्रकार alloc_size;
	/*
	 * gelic requires dma descriptor is 32 bytes aligned and
	 * the hypervisor requires irq_status is 8 bytes aligned.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा gelic_card, irq_status) % 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा gelic_card, descr) % 32);
	alloc_size =
		माप(काष्ठा gelic_card) +
		माप(काष्ठा gelic_descr) * GELIC_NET_RX_DESCRIPTORS +
		माप(काष्ठा gelic_descr) * GELIC_NET_TX_DESCRIPTORS +
		GELIC_ALIGN - 1;

	p  = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!p)
		वापस शून्य;
	card = PTR_ALIGN(p, GELIC_ALIGN);
	card->unalign = p;

	/*
	 * alloc netdev
	 */
	*netdev = alloc_etherdev(माप(काष्ठा gelic_port));
	अगर (!*netdev) अणु
		kमुक्त(card->unalign);
		वापस शून्य;
	पूर्ण
	port = netdev_priv(*netdev);

	/* gelic_port */
	port->netdev = *netdev;
	port->card = card;
	port->type = GELIC_PORT_ETHERNET_0;

	/* gelic_card */
	card->netdev[GELIC_PORT_ETHERNET_0] = *netdev;

	INIT_WORK(&card->tx_समयout_task, gelic_net_tx_समयout_task);
	init_रुकोqueue_head(&card->रुकोq);
	atomic_set(&card->tx_समयout_task_counter, 0);
	mutex_init(&card->upकरोwn_lock);
	atomic_set(&card->users, 0);

	वापस card;
पूर्ण

अटल व्योम gelic_card_get_vlan_info(काष्ठा gelic_card *card)
अणु
	u64 v1, v2;
	पूर्णांक status;
	अचिन्हित पूर्णांक i;
	काष्ठा अणु
		पूर्णांक tx;
		पूर्णांक rx;
	पूर्ण vlan_id_ix[2] = अणु
		[GELIC_PORT_ETHERNET_0] = अणु
			.tx = GELIC_LV1_VLAN_TX_ETHERNET_0,
			.rx = GELIC_LV1_VLAN_RX_ETHERNET_0
		पूर्ण,
		[GELIC_PORT_WIRELESS] = अणु
			.tx = GELIC_LV1_VLAN_TX_WIRELESS,
			.rx = GELIC_LV1_VLAN_RX_WIRELESS
		पूर्ण
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(vlan_id_ix); i++) अणु
		/* tx tag */
		status = lv1_net_control(bus_id(card), dev_id(card),
					 GELIC_LV1_GET_VLAN_ID,
					 vlan_id_ix[i].tx,
					 0, 0, &v1, &v2);
		अगर (status || !v1) अणु
			अगर (status != LV1_NO_ENTRY)
				dev_dbg(ctodev(card),
					"get vlan id for tx(%d) failed(%d)\n",
					vlan_id_ix[i].tx, status);
			card->vlan[i].tx = 0;
			card->vlan[i].rx = 0;
			जारी;
		पूर्ण
		card->vlan[i].tx = (u16)v1;

		/* rx tag */
		status = lv1_net_control(bus_id(card), dev_id(card),
					 GELIC_LV1_GET_VLAN_ID,
					 vlan_id_ix[i].rx,
					 0, 0, &v1, &v2);
		अगर (status || !v1) अणु
			अगर (status != LV1_NO_ENTRY)
				dev_info(ctodev(card),
					 "get vlan id for rx(%d) failed(%d)\n",
					 vlan_id_ix[i].rx, status);
			card->vlan[i].tx = 0;
			card->vlan[i].rx = 0;
			जारी;
		पूर्ण
		card->vlan[i].rx = (u16)v1;

		dev_dbg(ctodev(card), "vlan_id[%d] tx=%02x rx=%02x\n",
			i, card->vlan[i].tx, card->vlan[i].rx);
	पूर्ण

	अगर (card->vlan[GELIC_PORT_ETHERNET_0].tx) अणु
		BUG_ON(!card->vlan[GELIC_PORT_WIRELESS].tx);
		card->vlan_required = 1;
	पूर्ण अन्यथा
		card->vlan_required = 0;

	/* check wirelss capable firmware */
	अगर (ps3_compare_firmware_version(1, 6, 0) < 0) अणु
		card->vlan[GELIC_PORT_WIRELESS].tx = 0;
		card->vlan[GELIC_PORT_WIRELESS].rx = 0;
	पूर्ण

	dev_info(ctodev(card), "internal vlan %s\n",
		 card->vlan_required? "enabled" : "disabled");
पूर्ण
/*
 * ps3_gelic_driver_probe - add a device to the control of this driver
 */
अटल पूर्णांक ps3_gelic_driver_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा gelic_card *card;
	काष्ठा net_device *netdev;
	पूर्णांक result;

	pr_debug("%s: called\n", __func__);

	udbg_shutकरोwn_ps3gelic();

	result = ps3_खोलो_hv_device(dev);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:ps3_open_hv_device failed\n",
			__func__);
		जाओ fail_खोलो;
	पूर्ण

	result = ps3_dma_region_create(dev->d_region);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:ps3_dma_region_create failed(%d)\n",
			__func__, result);
		BUG_ON("check region type");
		जाओ fail_dma_region;
	पूर्ण

	/* alloc card/netdevice */
	card = gelic_alloc_card_net(&netdev);
	अगर (!card) अणु
		dev_info(&dev->core, "%s:gelic_net_alloc_card failed\n",
			 __func__);
		result = -ENOMEM;
		जाओ fail_alloc_card;
	पूर्ण
	ps3_प्रणाली_bus_set_drvdata(dev, card);
	card->dev = dev;

	/* get पूर्णांकernal vlan info */
	gelic_card_get_vlan_info(card);

	card->link_mode = GELIC_LV1_ETHER_AUTO_NEG;

	/* setup पूर्णांकerrupt */
	result = lv1_net_set_पूर्णांकerrupt_status_indicator(bus_id(card),
							dev_id(card),
		ps3_mm_phys_to_lpar(__pa(&card->irq_status)),
		0);

	अगर (result) अणु
		dev_dbg(&dev->core,
			"%s:set_interrupt_status_indicator failed: %s\n",
			__func__, ps3_result(result));
		result = -EIO;
		जाओ fail_status_indicator;
	पूर्ण

	result = ps3_sb_event_receive_port_setup(dev, PS3_BINDING_CPU_ANY,
		&card->irq);

	अगर (result) अणु
		dev_info(ctodev(card),
			 "%s:gelic_net_open_device failed (%d)\n",
			 __func__, result);
		result = -EPERM;
		जाओ fail_alloc_irq;
	पूर्ण
	result = request_irq(card->irq, gelic_card_पूर्णांकerrupt,
			     0, netdev->name, card);

	अगर (result) अणु
		dev_info(ctodev(card), "%s:request_irq failed (%d)\n",
			__func__, result);
		जाओ fail_request_irq;
	पूर्ण

	/* setup card काष्ठाure */
	card->irq_mask = GELIC_CARD_RXINT | GELIC_CARD_TXINT |
		GELIC_CARD_PORT_STATUS_CHANGED;


	result = gelic_card_init_chain(card, &card->tx_chain,
				       card->descr, GELIC_NET_TX_DESCRIPTORS);
	अगर (result)
		जाओ fail_alloc_tx;
	result = gelic_card_init_chain(card, &card->rx_chain,
				       card->descr + GELIC_NET_TX_DESCRIPTORS,
				       GELIC_NET_RX_DESCRIPTORS);
	अगर (result)
		जाओ fail_alloc_rx;

	/* head of chain */
	card->tx_top = card->tx_chain.head;
	card->rx_top = card->rx_chain.head;
	dev_dbg(ctodev(card), "descr rx %p, tx %p, size %#lx, num %#x\n",
		card->rx_top, card->tx_top, माप(काष्ठा gelic_descr),
		GELIC_NET_RX_DESCRIPTORS);
	/* allocate rx skbs */
	result = gelic_card_alloc_rx_skbs(card);
	अगर (result)
		जाओ fail_alloc_skbs;

	spin_lock_init(&card->tx_lock);
	card->tx_dma_progress = 0;

	/* setup net_device काष्ठाure */
	netdev->irq = card->irq;
	SET_NETDEV_DEV(netdev, &card->dev->core);
	gelic_ether_setup_netdev_ops(netdev, &card->napi);
	result = gelic_net_setup_netdev(netdev, card);
	अगर (result) अणु
		dev_dbg(&dev->core, "%s: setup_netdev failed %d\n",
			__func__, result);
		जाओ fail_setup_netdev;
	पूर्ण

#अगर_घोषित CONFIG_GELIC_WIRELESS
	result = gelic_wl_driver_probe(card);
	अगर (result) अणु
		dev_dbg(&dev->core, "%s: WL init failed\n", __func__);
		जाओ fail_setup_netdev;
	पूर्ण
#पूर्ण_अगर
	pr_debug("%s: done\n", __func__);
	वापस 0;

fail_setup_netdev:
fail_alloc_skbs:
	gelic_card_मुक्त_chain(card, card->rx_chain.head);
fail_alloc_rx:
	gelic_card_मुक्त_chain(card, card->tx_chain.head);
fail_alloc_tx:
	मुक्त_irq(card->irq, card);
	netdev->irq = 0;
fail_request_irq:
	ps3_sb_event_receive_port_destroy(dev, card->irq);
fail_alloc_irq:
	lv1_net_set_पूर्णांकerrupt_status_indicator(bus_id(card),
					       bus_id(card),
					       0, 0);
fail_status_indicator:
	ps3_प्रणाली_bus_set_drvdata(dev, शून्य);
	kमुक्त(netdev_card(netdev)->unalign);
	मुक्त_netdev(netdev);
fail_alloc_card:
	ps3_dma_region_मुक्त(dev->d_region);
fail_dma_region:
	ps3_बंद_hv_device(dev);
fail_खोलो:
	वापस result;
पूर्ण

/*
 * ps3_gelic_driver_हटाओ - हटाओ a device from the control of this driver
 */

अटल व्योम ps3_gelic_driver_हटाओ(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा gelic_card *card = ps3_प्रणाली_bus_get_drvdata(dev);
	काष्ठा net_device *netdev0;
	pr_debug("%s: called\n", __func__);

	/* set स्वतः-negotiation */
	gelic_card_set_link_mode(card, GELIC_LV1_ETHER_AUTO_NEG);

#अगर_घोषित CONFIG_GELIC_WIRELESS
	gelic_wl_driver_हटाओ(card);
#पूर्ण_अगर
	/* stop पूर्णांकerrupt */
	gelic_card_set_irq_mask(card, 0);

	/* turn off DMA, क्रमce end */
	gelic_card_disable_rxdmac(card);
	gelic_card_disable_txdmac(card);

	/* release chains */
	gelic_card_release_tx_chain(card, 1);
	gelic_card_release_rx_chain(card);

	gelic_card_मुक्त_chain(card, card->tx_top);
	gelic_card_मुक्त_chain(card, card->rx_top);

	netdev0 = card->netdev[GELIC_PORT_ETHERNET_0];
	/* disconnect event port */
	मुक्त_irq(card->irq, card);
	netdev0->irq = 0;
	ps3_sb_event_receive_port_destroy(card->dev, card->irq);

	रुको_event(card->रुकोq,
		   atomic_पढ़ो(&card->tx_समयout_task_counter) == 0);

	lv1_net_set_पूर्णांकerrupt_status_indicator(bus_id(card), dev_id(card),
					       0 , 0);

	unरेजिस्टर_netdev(netdev0);
	kमुक्त(netdev_card(netdev0)->unalign);
	मुक्त_netdev(netdev0);

	ps3_प्रणाली_bus_set_drvdata(dev, शून्य);

	ps3_dma_region_मुक्त(dev->d_region);

	ps3_बंद_hv_device(dev);

	pr_debug("%s: done\n", __func__);
पूर्ण

अटल काष्ठा ps3_प्रणाली_bus_driver ps3_gelic_driver = अणु
	.match_id = PS3_MATCH_ID_GELIC,
	.probe = ps3_gelic_driver_probe,
	.हटाओ = ps3_gelic_driver_हटाओ,
	.shutकरोwn = ps3_gelic_driver_हटाओ,
	.core.name = "ps3_gelic_driver",
	.core.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ps3_gelic_driver_init (व्योम)
अणु
	वापस firmware_has_feature(FW_FEATURE_PS3_LV1)
		? ps3_प्रणाली_bus_driver_रेजिस्टर(&ps3_gelic_driver)
		: -ENODEV;
पूर्ण

अटल व्योम __निकास ps3_gelic_driver_निकास (व्योम)
अणु
	ps3_प्रणाली_bus_driver_unरेजिस्टर(&ps3_gelic_driver);
पूर्ण

module_init(ps3_gelic_driver_init);
module_निकास(ps3_gelic_driver_निकास);

MODULE_ALIAS(PS3_MODULE_ALIAS_GELIC);

