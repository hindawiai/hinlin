<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Altera Triple-Speed Ethernet MAC driver
 * Copyright (C) 2008-2014 Altera Corporation. All rights reserved
 *
 * Contributors:
 *   Dalon Westergreen
 *   Thomas Chou
 *   Ian Abbott
 *   Yuriy Kozlov
 *   Tobias Klauser
 *   Andriy Smolskyy
 *   Roman Bulgakov
 *   Dmytro Mytarchuk
 *   Matthew Gerlach
 *
 * Original driver contributed by SLS.
 * Major updates contributed by GlobalLogic
 */

#समावेश <linux/atomic.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/skbuff.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "altera_utils.h"
#समावेश "altera_tse.h"
#समावेश "altera_sgdma.h"
#समावेश "altera_msgdma.h"

अटल atomic_t instance_count = ATOMIC_INIT(~0);
/* Module parameters */
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Message Level (-1: default, 0: no output, 16: all)");

अटल स्थिर u32 शेष_msg_level = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
					NETIF_MSG_LINK | NETIF_MSG_IFUP |
					NETIF_MSG_IFDOWN);

#घोषणा RX_DESCRIPTORS 64
अटल पूर्णांक dma_rx_num = RX_DESCRIPTORS;
module_param(dma_rx_num, पूर्णांक, 0644);
MODULE_PARM_DESC(dma_rx_num, "Number of descriptors in the RX list");

#घोषणा TX_DESCRIPTORS 64
अटल पूर्णांक dma_tx_num = TX_DESCRIPTORS;
module_param(dma_tx_num, पूर्णांक, 0644);
MODULE_PARM_DESC(dma_tx_num, "Number of descriptors in the TX list");


#घोषणा POLL_PHY (-1)

/* Make sure DMA buffer size is larger than the max frame size
 * plus some alignment offset and a VLAN header. If the max frame size is
 * 1518, a VLAN header would be additional 4 bytes and additional
 * headroom क्रम alignment is 2 bytes, 2048 is just fine.
 */
#घोषणा ALTERA_RXDMABUFFER_SIZE	2048

/* Allow network stack to resume queueing packets after we've
 * finished transmitting at least 1/4 of the packets in the queue.
 */
#घोषणा TSE_TX_THRESH(x)	(x->tx_ring_size / 4)

#घोषणा TXQUEUESTOP_THRESHHOLD	2

अटल स्थिर काष्ठा of_device_id altera_tse_ids[];

अटल अंतरभूत u32 tse_tx_avail(काष्ठा altera_tse_निजी *priv)
अणु
	वापस priv->tx_cons + priv->tx_ring_size - priv->tx_prod - 1;
पूर्ण

/* PCS Register पढ़ो/ग_लिखो functions
 */
अटल u16 sgmii_pcs_पढ़ो(काष्ठा altera_tse_निजी *priv, पूर्णांक regnum)
अणु
	वापस csrrd32(priv->mac_dev,
		       tse_csroffs(mdio_phy0) + regnum * 4) & 0xffff;
पूर्ण

अटल व्योम sgmii_pcs_ग_लिखो(काष्ठा altera_tse_निजी *priv, पूर्णांक regnum,
				u16 value)
अणु
	csrwr32(value, priv->mac_dev, tse_csroffs(mdio_phy0) + regnum * 4);
पूर्ण

/* Check PCS scratch memory */
अटल पूर्णांक sgmii_pcs_scratch_test(काष्ठा altera_tse_निजी *priv, u16 value)
अणु
	sgmii_pcs_ग_लिखो(priv, SGMII_PCS_SCRATCH, value);
	वापस (sgmii_pcs_पढ़ो(priv, SGMII_PCS_SCRATCH) == value);
पूर्ण

/* MDIO specअगरic functions
 */
अटल पूर्णांक altera_tse_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा altera_tse_निजी *priv = netdev_priv(ndev);

	/* set MDIO address */
	csrwr32((mii_id & 0x1f), priv->mac_dev,
		tse_csroffs(mdio_phy1_addr));

	/* get the data */
	वापस csrrd32(priv->mac_dev,
		       tse_csroffs(mdio_phy1) + regnum * 4) & 0xffff;
पूर्ण

अटल पूर्णांक altera_tse_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum,
				 u16 value)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा altera_tse_निजी *priv = netdev_priv(ndev);

	/* set MDIO address */
	csrwr32((mii_id & 0x1f), priv->mac_dev,
		tse_csroffs(mdio_phy1_addr));

	/* ग_लिखो the data */
	csrwr32(value, priv->mac_dev, tse_csroffs(mdio_phy1) + regnum * 4);
	वापस 0;
पूर्ण

अटल पूर्णांक altera_tse_mdio_create(काष्ठा net_device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	पूर्णांक ret;
	काष्ठा device_node *mdio_node = शून्य;
	काष्ठा mii_bus *mdio = शून्य;
	काष्ठा device_node *child_node = शून्य;

	क्रम_each_child_of_node(priv->device->of_node, child_node) अणु
		अगर (of_device_is_compatible(child_node, "altr,tse-mdio")) अणु
			mdio_node = child_node;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mdio_node) अणु
		netdev_dbg(dev, "FOUND MDIO subnode\n");
	पूर्ण अन्यथा अणु
		netdev_dbg(dev, "NO MDIO subnode\n");
		वापस 0;
	पूर्ण

	mdio = mdiobus_alloc();
	अगर (mdio == शून्य) अणु
		netdev_err(dev, "Error allocating MDIO bus\n");
		वापस -ENOMEM;
	पूर्ण

	mdio->name = ALTERA_TSE_RESOURCE_NAME;
	mdio->पढ़ो = &altera_tse_mdio_पढ़ो;
	mdio->ग_लिखो = &altera_tse_mdio_ग_लिखो;
	snम_लिखो(mdio->id, MII_BUS_ID_SIZE, "%s-%u", mdio->name, id);

	mdio->priv = dev;
	mdio->parent = priv->device;

	ret = of_mdiobus_रेजिस्टर(mdio, mdio_node);
	अगर (ret != 0) अणु
		netdev_err(dev, "Cannot register MDIO bus %s\n",
			   mdio->id);
		जाओ out_मुक्त_mdio;
	पूर्ण

	अगर (netअगर_msg_drv(priv))
		netdev_info(dev, "MDIO bus %s: created\n", mdio->id);

	priv->mdio = mdio;
	वापस 0;
out_मुक्त_mdio:
	mdiobus_मुक्त(mdio);
	mdio = शून्य;
	वापस ret;
पूर्ण

अटल व्योम altera_tse_mdio_destroy(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);

	अगर (priv->mdio == शून्य)
		वापस;

	अगर (netअगर_msg_drv(priv))
		netdev_info(dev, "MDIO bus %s: removed\n",
			    priv->mdio->id);

	mdiobus_unरेजिस्टर(priv->mdio);
	mdiobus_मुक्त(priv->mdio);
	priv->mdio = शून्य;
पूर्ण

अटल पूर्णांक tse_init_rx_buffer(काष्ठा altera_tse_निजी *priv,
			      काष्ठा tse_buffer *rxbuffer, पूर्णांक len)
अणु
	rxbuffer->skb = netdev_alloc_skb_ip_align(priv->dev, len);
	अगर (!rxbuffer->skb)
		वापस -ENOMEM;

	rxbuffer->dma_addr = dma_map_single(priv->device, rxbuffer->skb->data,
						len,
						DMA_FROM_DEVICE);

	अगर (dma_mapping_error(priv->device, rxbuffer->dma_addr)) अणु
		netdev_err(priv->dev, "%s: DMA mapping error\n", __func__);
		dev_kमुक्त_skb_any(rxbuffer->skb);
		वापस -EINVAL;
	पूर्ण
	rxbuffer->dma_addr &= (dma_addr_t)~3;
	rxbuffer->len = len;
	वापस 0;
पूर्ण

अटल व्योम tse_मुक्त_rx_buffer(काष्ठा altera_tse_निजी *priv,
			       काष्ठा tse_buffer *rxbuffer)
अणु
	काष्ठा sk_buff *skb = rxbuffer->skb;
	dma_addr_t dma_addr = rxbuffer->dma_addr;

	अगर (skb != शून्य) अणु
		अगर (dma_addr)
			dma_unmap_single(priv->device, dma_addr,
					 rxbuffer->len,
					 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
		rxbuffer->skb = शून्य;
		rxbuffer->dma_addr = 0;
	पूर्ण
पूर्ण

/* Unmap and मुक्त Tx buffer resources
 */
अटल व्योम tse_मुक्त_tx_buffer(काष्ठा altera_tse_निजी *priv,
			       काष्ठा tse_buffer *buffer)
अणु
	अगर (buffer->dma_addr) अणु
		अगर (buffer->mapped_as_page)
			dma_unmap_page(priv->device, buffer->dma_addr,
				       buffer->len, DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(priv->device, buffer->dma_addr,
					 buffer->len, DMA_TO_DEVICE);
		buffer->dma_addr = 0;
	पूर्ण
	अगर (buffer->skb) अणु
		dev_kमुक्त_skb_any(buffer->skb);
		buffer->skb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_init_skbufs(काष्ठा altera_tse_निजी *priv)
अणु
	अचिन्हित पूर्णांक rx_descs = priv->rx_ring_size;
	अचिन्हित पूर्णांक tx_descs = priv->tx_ring_size;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i;

	/* Create Rx ring buffer */
	priv->rx_ring = kसुस्मृति(rx_descs, माप(काष्ठा tse_buffer),
				GFP_KERNEL);
	अगर (!priv->rx_ring)
		जाओ err_rx_ring;

	/* Create Tx ring buffer */
	priv->tx_ring = kसुस्मृति(tx_descs, माप(काष्ठा tse_buffer),
				GFP_KERNEL);
	अगर (!priv->tx_ring)
		जाओ err_tx_ring;

	priv->tx_cons = 0;
	priv->tx_prod = 0;

	/* Init Rx ring */
	क्रम (i = 0; i < rx_descs; i++) अणु
		ret = tse_init_rx_buffer(priv, &priv->rx_ring[i],
					 priv->rx_dma_buf_sz);
		अगर (ret)
			जाओ err_init_rx_buffers;
	पूर्ण

	priv->rx_cons = 0;
	priv->rx_prod = 0;

	वापस 0;
err_init_rx_buffers:
	जबतक (--i >= 0)
		tse_मुक्त_rx_buffer(priv, &priv->rx_ring[i]);
	kमुक्त(priv->tx_ring);
err_tx_ring:
	kमुक्त(priv->rx_ring);
err_rx_ring:
	वापस ret;
पूर्ण

अटल व्योम मुक्त_skbufs(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक rx_descs = priv->rx_ring_size;
	अचिन्हित पूर्णांक tx_descs = priv->tx_ring_size;
	पूर्णांक i;

	/* Release the DMA TX/RX socket buffers */
	क्रम (i = 0; i < rx_descs; i++)
		tse_मुक्त_rx_buffer(priv, &priv->rx_ring[i]);
	क्रम (i = 0; i < tx_descs; i++)
		tse_मुक्त_tx_buffer(priv, &priv->tx_ring[i]);


	kमुक्त(priv->tx_ring);
पूर्ण

/* Reallocate the skb क्रम the reception process
 */
अटल अंतरभूत व्योम tse_rx_refill(काष्ठा altera_tse_निजी *priv)
अणु
	अचिन्हित पूर्णांक rxsize = priv->rx_ring_size;
	अचिन्हित पूर्णांक entry;
	पूर्णांक ret;

	क्रम (; priv->rx_cons - priv->rx_prod > 0;
			priv->rx_prod++) अणु
		entry = priv->rx_prod % rxsize;
		अगर (likely(priv->rx_ring[entry].skb == शून्य)) अणु
			ret = tse_init_rx_buffer(priv, &priv->rx_ring[entry],
				priv->rx_dma_buf_sz);
			अगर (unlikely(ret != 0))
				अवरोध;
			priv->dmaops->add_rx_desc(priv, &priv->rx_ring[entry]);
		पूर्ण
	पूर्ण
पूर्ण

/* Pull out the VLAN tag and fix up the packet
 */
अटल अंतरभूत व्योम tse_rx_vlan(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eth_hdr;
	u16 vid;
	अगर ((dev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    !__vlan_get_tag(skb, &vid)) अणु
		eth_hdr = (काष्ठा ethhdr *)skb->data;
		स_हटाओ(skb->data + VLAN_HLEN, eth_hdr, ETH_ALEN * 2);
		skb_pull(skb, VLAN_HLEN);
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	पूर्ण
पूर्ण

/* Receive a packet: retrieve and pass over to upper levels
 */
अटल पूर्णांक tse_rx(काष्ठा altera_tse_निजी *priv, पूर्णांक limit)
अणु
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक next_entry;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक entry = priv->rx_cons % priv->rx_ring_size;
	u32 rxstatus;
	u16 pktlength;
	u16 pktstatus;

	/* Check क्रम count < limit first as get_rx_status is changing
	* the response-fअगरo so we must process the next packet
	* after calling get_rx_status अगर a response is pending.
	* (पढ़ोing the last byte of the response pops the value from the fअगरo.)
	*/
	जबतक ((count < limit) &&
	       ((rxstatus = priv->dmaops->get_rx_status(priv)) != 0)) अणु
		pktstatus = rxstatus >> 16;
		pktlength = rxstatus & 0xffff;

		अगर ((pktstatus & 0xFF) || (pktlength == 0))
			netdev_err(priv->dev,
				   "RCV pktstatus %08X pktlength %08X\n",
				   pktstatus, pktlength);

		/* DMA trasfer from TSE starts with 2 aditional bytes क्रम
		 * IP payload alignment. Status वापसed by get_rx_status()
		 * contains DMA transfer length. Packet is 2 bytes लघुer.
		 */
		pktlength -= 2;

		count++;
		next_entry = (++priv->rx_cons) % priv->rx_ring_size;

		skb = priv->rx_ring[entry].skb;
		अगर (unlikely(!skb)) अणु
			netdev_err(priv->dev,
				   "%s: Inconsistent Rx descriptor chain\n",
				   __func__);
			priv->dev->stats.rx_dropped++;
			अवरोध;
		पूर्ण
		priv->rx_ring[entry].skb = शून्य;

		skb_put(skb, pktlength);

		dma_unmap_single(priv->device, priv->rx_ring[entry].dma_addr,
				 priv->rx_ring[entry].len, DMA_FROM_DEVICE);

		अगर (netअगर_msg_pktdata(priv)) अणु
			netdev_info(priv->dev, "frame received %d bytes\n",
				    pktlength);
			prपूर्णांक_hex_dump(KERN_ERR, "data: ", DUMP_PREFIX_OFFSET,
				       16, 1, skb->data, pktlength, true);
		पूर्ण

		tse_rx_vlan(priv->dev, skb);

		skb->protocol = eth_type_trans(skb, priv->dev);
		skb_checksum_none_निश्चित(skb);

		napi_gro_receive(&priv->napi, skb);

		priv->dev->stats.rx_packets++;
		priv->dev->stats.rx_bytes += pktlength;

		entry = next_entry;

		tse_rx_refill(priv);
	पूर्ण

	वापस count;
पूर्ण

/* Reclaim resources after transmission completes
 */
अटल पूर्णांक tse_tx_complete(काष्ठा altera_tse_निजी *priv)
अणु
	अचिन्हित पूर्णांक txsize = priv->tx_ring_size;
	u32 पढ़ोy;
	अचिन्हित पूर्णांक entry;
	काष्ठा tse_buffer *tx_buff;
	पूर्णांक txcomplete = 0;

	spin_lock(&priv->tx_lock);

	पढ़ोy = priv->dmaops->tx_completions(priv);

	/* Free sent buffers */
	जबतक (पढ़ोy && (priv->tx_cons != priv->tx_prod)) अणु
		entry = priv->tx_cons % txsize;
		tx_buff = &priv->tx_ring[entry];

		अगर (netअगर_msg_tx_करोne(priv))
			netdev_dbg(priv->dev, "%s: curr %d, dirty %d\n",
				   __func__, priv->tx_prod, priv->tx_cons);

		अगर (likely(tx_buff->skb))
			priv->dev->stats.tx_packets++;

		tse_मुक्त_tx_buffer(priv, tx_buff);
		priv->tx_cons++;

		txcomplete++;
		पढ़ोy--;
	पूर्ण

	अगर (unlikely(netअगर_queue_stopped(priv->dev) &&
		     tse_tx_avail(priv) > TSE_TX_THRESH(priv))) अणु
		अगर (netअगर_queue_stopped(priv->dev) &&
		    tse_tx_avail(priv) > TSE_TX_THRESH(priv)) अणु
			अगर (netअगर_msg_tx_करोne(priv))
				netdev_dbg(priv->dev, "%s: restart transmit\n",
					   __func__);
			netअगर_wake_queue(priv->dev);
		पूर्ण
	पूर्ण

	spin_unlock(&priv->tx_lock);
	वापस txcomplete;
पूर्ण

/* NAPI polling function
 */
अटल पूर्णांक tse_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा altera_tse_निजी *priv =
			container_of(napi, काष्ठा altera_tse_निजी, napi);
	पूर्णांक rxcomplete = 0;
	अचिन्हित दीर्घ पूर्णांक flags;

	tse_tx_complete(priv);

	rxcomplete = tse_rx(priv, budget);

	अगर (rxcomplete < budget) अणु

		napi_complete_करोne(napi, rxcomplete);

		netdev_dbg(priv->dev,
			   "NAPI Complete, did %d packets with budget %d\n",
			   rxcomplete, budget);

		spin_lock_irqsave(&priv->rxdma_irq_lock, flags);
		priv->dmaops->enable_rxirq(priv);
		priv->dmaops->enable_txirq(priv);
		spin_unlock_irqrestore(&priv->rxdma_irq_lock, flags);
	पूर्ण
	वापस rxcomplete;
पूर्ण

/* DMA TX & RX FIFO पूर्णांकerrupt routing
 */
अटल irqवापस_t altera_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा altera_tse_निजी *priv;

	अगर (unlikely(!dev)) अणु
		pr_err("%s: invalid dev pointer\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	priv = netdev_priv(dev);

	spin_lock(&priv->rxdma_irq_lock);
	/* reset IRQs */
	priv->dmaops->clear_rxirq(priv);
	priv->dmaops->clear_txirq(priv);
	spin_unlock(&priv->rxdma_irq_lock);

	अगर (likely(napi_schedule_prep(&priv->napi))) अणु
		spin_lock(&priv->rxdma_irq_lock);
		priv->dmaops->disable_rxirq(priv);
		priv->dmaops->disable_txirq(priv);
		spin_unlock(&priv->rxdma_irq_lock);
		__napi_schedule(&priv->napi);
	पूर्ण


	वापस IRQ_HANDLED;
पूर्ण

/* Transmit a packet (called by the kernel). Dispatches
 * either the SGDMA method क्रम transmitting or the
 * MSGDMA method, assumes no scatter/gather support,
 * implying an assumption that there's only one
 * physically contiguous fragment starting at
 * skb->data, क्रम length of skb_headlen(skb).
 */
अटल netdev_tx_t tse_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक txsize = priv->tx_ring_size;
	अचिन्हित पूर्णांक entry;
	काष्ठा tse_buffer *buffer = शून्य;
	पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;
	अचिन्हित पूर्णांक nopaged_len = skb_headlen(skb);
	netdev_tx_t ret = NETDEV_TX_OK;
	dma_addr_t dma_addr;

	spin_lock_bh(&priv->tx_lock);

	अगर (unlikely(tse_tx_avail(priv) < nfrags + 1)) अणु
		अगर (!netअगर_queue_stopped(dev)) अणु
			netअगर_stop_queue(dev);
			/* This is a hard error, log it. */
			netdev_err(priv->dev,
				   "%s: Tx list full when queue awake\n",
				   __func__);
		पूर्ण
		ret = NETDEV_TX_BUSY;
		जाओ out;
	पूर्ण

	/* Map the first skb fragment */
	entry = priv->tx_prod % txsize;
	buffer = &priv->tx_ring[entry];

	dma_addr = dma_map_single(priv->device, skb->data, nopaged_len,
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(priv->device, dma_addr)) अणु
		netdev_err(priv->dev, "%s: DMA mapping error\n", __func__);
		ret = NETDEV_TX_OK;
		जाओ out;
	पूर्ण

	buffer->skb = skb;
	buffer->dma_addr = dma_addr;
	buffer->len = nopaged_len;

	priv->dmaops->tx_buffer(priv, buffer);

	skb_tx_बारtamp(skb);

	priv->tx_prod++;
	dev->stats.tx_bytes += skb->len;

	अगर (unlikely(tse_tx_avail(priv) <= TXQUEUESTOP_THRESHHOLD)) अणु
		अगर (netअगर_msg_hw(priv))
			netdev_dbg(priv->dev, "%s: stop transmitted packets\n",
				   __func__);
		netअगर_stop_queue(dev);
	पूर्ण

out:
	spin_unlock_bh(&priv->tx_lock);

	वापस ret;
पूर्ण

/* Called every समय the controller might need to be made
 * aware of new link state.  The PHY code conveys this
 * inक्रमmation through variables in the phydev काष्ठाure, and this
 * function converts those variables पूर्णांकo the appropriate
 * रेजिस्टर values, and can bring करोwn the device अगर needed.
 */
अटल व्योम altera_tse_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	पूर्णांक new_state = 0;

	/* only change config अगर there is a link */
	spin_lock(&priv->mac_cfg_lock);
	अगर (phydev->link) अणु
		/* Read old config */
		u32 cfg_reg = ioपढ़ो32(&priv->mac_dev->command_config);

		/* Check duplex */
		अगर (phydev->duplex != priv->oldduplex) अणु
			new_state = 1;
			अगर (!(phydev->duplex))
				cfg_reg |= MAC_CMDCFG_HD_ENA;
			अन्यथा
				cfg_reg &= ~MAC_CMDCFG_HD_ENA;

			netdev_dbg(priv->dev, "%s: Link duplex = 0x%x\n",
				   dev->name, phydev->duplex);

			priv->oldduplex = phydev->duplex;
		पूर्ण

		/* Check speed */
		अगर (phydev->speed != priv->oldspeed) अणु
			new_state = 1;
			चयन (phydev->speed) अणु
			हाल 1000:
				cfg_reg |= MAC_CMDCFG_ETH_SPEED;
				cfg_reg &= ~MAC_CMDCFG_ENA_10;
				अवरोध;
			हाल 100:
				cfg_reg &= ~MAC_CMDCFG_ETH_SPEED;
				cfg_reg &= ~MAC_CMDCFG_ENA_10;
				अवरोध;
			हाल 10:
				cfg_reg &= ~MAC_CMDCFG_ETH_SPEED;
				cfg_reg |= MAC_CMDCFG_ENA_10;
				अवरोध;
			शेष:
				अगर (netअगर_msg_link(priv))
					netdev_warn(dev, "Speed (%d) is not 10/100/1000!\n",
						    phydev->speed);
				अवरोध;
			पूर्ण
			priv->oldspeed = phydev->speed;
		पूर्ण
		ioग_लिखो32(cfg_reg, &priv->mac_dev->command_config);

		अगर (!priv->oldlink) अणु
			new_state = 1;
			priv->oldlink = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (priv->oldlink) अणु
		new_state = 1;
		priv->oldlink = 0;
		priv->oldspeed = 0;
		priv->oldduplex = -1;
	पूर्ण

	अगर (new_state && netअगर_msg_link(priv))
		phy_prपूर्णांक_status(phydev);

	spin_unlock(&priv->mac_cfg_lock);
पूर्ण
अटल काष्ठा phy_device *connect_local_phy(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = शून्य;
	अक्षर phy_id_fmt[MII_BUS_ID_SIZE + 3];

	अगर (priv->phy_addr != POLL_PHY) अणु
		snम_लिखो(phy_id_fmt, MII_BUS_ID_SIZE + 3, PHY_ID_FMT,
			 priv->mdio->id, priv->phy_addr);

		netdev_dbg(dev, "trying to attach to %s\n", phy_id_fmt);

		phydev = phy_connect(dev, phy_id_fmt, &altera_tse_adjust_link,
				     priv->phy_अगरace);
		अगर (IS_ERR(phydev)) अणु
			netdev_err(dev, "Could not attach to PHY\n");
			phydev = शून्य;
		पूर्ण

	पूर्ण अन्यथा अणु
		पूर्णांक ret;
		phydev = phy_find_first(priv->mdio);
		अगर (phydev == शून्य) अणु
			netdev_err(dev, "No PHY found\n");
			वापस phydev;
		पूर्ण

		ret = phy_connect_direct(dev, phydev, &altera_tse_adjust_link,
				priv->phy_अगरace);
		अगर (ret != 0) अणु
			netdev_err(dev, "Could not attach to PHY\n");
			phydev = शून्य;
		पूर्ण
	पूर्ण
	वापस phydev;
पूर्ण

अटल पूर्णांक altera_tse_phy_get_addr_mdio_create(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	काष्ठा device_node *np = priv->device->of_node;
	पूर्णांक ret;

	ret = of_get_phy_mode(np, &priv->phy_अगरace);

	/* Aव्योम get phy addr and create mdio अगर no phy is present */
	अगर (ret)
		वापस 0;

	/* try to get PHY address from device tree, use PHY स्वतःdetection अगर
	 * no valid address is given
	 */

	अगर (of_property_पढ़ो_u32(priv->device->of_node, "phy-addr",
			 &priv->phy_addr)) अणु
		priv->phy_addr = POLL_PHY;
	पूर्ण

	अगर (!((priv->phy_addr == POLL_PHY) ||
		  ((priv->phy_addr >= 0) && (priv->phy_addr < PHY_MAX_ADDR)))) अणु
		netdev_err(dev, "invalid phy-addr specified %d\n",
			priv->phy_addr);
		वापस -ENODEV;
	पूर्ण

	/* Create/attach to MDIO bus */
	ret = altera_tse_mdio_create(dev,
					 atomic_add_वापस(1, &instance_count));

	अगर (ret)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/* Initialize driver's PHY state, and attach to the PHY
 */
अटल पूर्णांक init_phy(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev;
	काष्ठा device_node *phynode;
	bool fixed_link = false;
	पूर्णांक rc = 0;

	/* Aव्योम init phy in हाल of no phy present */
	अगर (!priv->phy_अगरace)
		वापस 0;

	priv->oldlink = 0;
	priv->oldspeed = 0;
	priv->oldduplex = -1;

	phynode = of_parse_phandle(priv->device->of_node, "phy-handle", 0);

	अगर (!phynode) अणु
		/* check अगर a fixed-link is defined in device-tree */
		अगर (of_phy_is_fixed_link(priv->device->of_node)) अणु
			rc = of_phy_रेजिस्टर_fixed_link(priv->device->of_node);
			अगर (rc < 0) अणु
				netdev_err(dev, "cannot register fixed PHY\n");
				वापस rc;
			पूर्ण

			/* In the हाल of a fixed PHY, the DT node associated
			 * to the PHY is the Ethernet MAC DT node.
			 */
			phynode = of_node_get(priv->device->of_node);
			fixed_link = true;

			netdev_dbg(dev, "fixed-link detected\n");
			phydev = of_phy_connect(dev, phynode,
						&altera_tse_adjust_link,
						0, priv->phy_अगरace);
		पूर्ण अन्यथा अणु
			netdev_dbg(dev, "no phy-handle found\n");
			अगर (!priv->mdio) अणु
				netdev_err(dev, "No phy-handle nor local mdio specified\n");
				वापस -ENODEV;
			पूर्ण
			phydev = connect_local_phy(dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_dbg(dev, "phy-handle found\n");
		phydev = of_phy_connect(dev, phynode,
			&altera_tse_adjust_link, 0, priv->phy_अगरace);
	पूर्ण
	of_node_put(phynode);

	अगर (!phydev) अणु
		netdev_err(dev, "Could not find the PHY\n");
		अगर (fixed_link)
			of_phy_deरेजिस्टर_fixed_link(priv->device->of_node);
		वापस -ENODEV;
	पूर्ण

	/* Stop Advertising 1000BASE Capability अगर पूर्णांकerface is not GMII
	 */
	अगर ((priv->phy_अगरace == PHY_INTERFACE_MODE_MII) ||
	    (priv->phy_अगरace == PHY_INTERFACE_MODE_RMII))
		phy_set_max_speed(phydev, SPEED_100);

	/* Broken HW is someबार missing the pull-up resistor on the
	 * MDIO line, which results in पढ़ोs to non-existent devices वापसing
	 * 0 rather than 0xffff. Catch this here and treat 0 as a non-existent
	 * device as well. If a fixed-link is used the phy_id is always 0.
	 * Note: phydev->phy_id is the result of पढ़ोing the UID PHY रेजिस्टरs.
	 */
	अगर ((phydev->phy_id == 0) && !fixed_link) अणु
		netdev_err(dev, "Bad PHY UID 0x%08x\n", phydev->phy_id);
		phy_disconnect(phydev);
		वापस -ENODEV;
	पूर्ण

	netdev_dbg(dev, "attached to PHY %d UID 0x%08x Link = %d\n",
		   phydev->mdio.addr, phydev->phy_id, phydev->link);

	वापस 0;
पूर्ण

अटल व्योम tse_update_mac_addr(काष्ठा altera_tse_निजी *priv, u8 *addr)
अणु
	u32 msb;
	u32 lsb;

	msb = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	lsb = ((addr[5] << 8) | addr[4]) & 0xffff;

	/* Set primary MAC address */
	csrwr32(msb, priv->mac_dev, tse_csroffs(mac_addr_0));
	csrwr32(lsb, priv->mac_dev, tse_csroffs(mac_addr_1));
पूर्ण

/* MAC software reset.
 * When reset is triggered, the MAC function completes the current
 * transmission or reception, and subsequently disables the transmit and
 * receive logic, flushes the receive FIFO buffer, and resets the statistics
 * counters.
 */
अटल पूर्णांक reset_mac(काष्ठा altera_tse_निजी *priv)
अणु
	पूर्णांक counter;
	u32 dat;

	dat = csrrd32(priv->mac_dev, tse_csroffs(command_config));
	dat &= ~(MAC_CMDCFG_TX_ENA | MAC_CMDCFG_RX_ENA);
	dat |= MAC_CMDCFG_SW_RESET | MAC_CMDCFG_CNT_RESET;
	csrwr32(dat, priv->mac_dev, tse_csroffs(command_config));

	counter = 0;
	जबतक (counter++ < ALTERA_TSE_SW_RESET_WATCHDOG_CNTR) अणु
		अगर (tse_bit_is_clear(priv->mac_dev, tse_csroffs(command_config),
				     MAC_CMDCFG_SW_RESET))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (counter >= ALTERA_TSE_SW_RESET_WATCHDOG_CNTR) अणु
		dat = csrrd32(priv->mac_dev, tse_csroffs(command_config));
		dat &= ~MAC_CMDCFG_SW_RESET;
		csrwr32(dat, priv->mac_dev, tse_csroffs(command_config));
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/* Initialize MAC core रेजिस्टरs
*/
अटल पूर्णांक init_mac(काष्ठा altera_tse_निजी *priv)
अणु
	अचिन्हित पूर्णांक cmd = 0;
	u32 frm_length;

	/* Setup Rx FIFO */
	csrwr32(priv->rx_fअगरo_depth - ALTERA_TSE_RX_SECTION_EMPTY,
		priv->mac_dev, tse_csroffs(rx_section_empty));

	csrwr32(ALTERA_TSE_RX_SECTION_FULL, priv->mac_dev,
		tse_csroffs(rx_section_full));

	csrwr32(ALTERA_TSE_RX_ALMOST_EMPTY, priv->mac_dev,
		tse_csroffs(rx_almost_empty));

	csrwr32(ALTERA_TSE_RX_ALMOST_FULL, priv->mac_dev,
		tse_csroffs(rx_almost_full));

	/* Setup Tx FIFO */
	csrwr32(priv->tx_fअगरo_depth - ALTERA_TSE_TX_SECTION_EMPTY,
		priv->mac_dev, tse_csroffs(tx_section_empty));

	csrwr32(ALTERA_TSE_TX_SECTION_FULL, priv->mac_dev,
		tse_csroffs(tx_section_full));

	csrwr32(ALTERA_TSE_TX_ALMOST_EMPTY, priv->mac_dev,
		tse_csroffs(tx_almost_empty));

	csrwr32(ALTERA_TSE_TX_ALMOST_FULL, priv->mac_dev,
		tse_csroffs(tx_almost_full));

	/* MAC Address Configuration */
	tse_update_mac_addr(priv, priv->dev->dev_addr);

	/* MAC Function Configuration */
	frm_length = ETH_HLEN + priv->dev->mtu + ETH_FCS_LEN;
	csrwr32(frm_length, priv->mac_dev, tse_csroffs(frm_length));

	csrwr32(ALTERA_TSE_TX_IPG_LENGTH, priv->mac_dev,
		tse_csroffs(tx_ipg_length));

	/* Disable RX/TX shअगरt 16 क्रम alignment of all received frames on 16-bit
	 * start address
	 */
	tse_set_bit(priv->mac_dev, tse_csroffs(rx_cmd_stat),
		    ALTERA_TSE_RX_CMD_STAT_RX_SHIFT16);

	tse_clear_bit(priv->mac_dev, tse_csroffs(tx_cmd_stat),
		      ALTERA_TSE_TX_CMD_STAT_TX_SHIFT16 |
		      ALTERA_TSE_TX_CMD_STAT_OMIT_CRC);

	/* Set the MAC options */
	cmd = csrrd32(priv->mac_dev, tse_csroffs(command_config));
	cmd &= ~MAC_CMDCFG_PAD_EN;	/* No padding Removal on Receive */
	cmd &= ~MAC_CMDCFG_CRC_FWD;	/* CRC Removal */
	cmd |= MAC_CMDCFG_RX_ERR_DISC;	/* Automatically discard frames
					 * with CRC errors
					 */
	cmd |= MAC_CMDCFG_CNTL_FRM_ENA;
	cmd &= ~MAC_CMDCFG_TX_ENA;
	cmd &= ~MAC_CMDCFG_RX_ENA;

	/* Default speed and duplex setting, full/100 */
	cmd &= ~MAC_CMDCFG_HD_ENA;
	cmd &= ~MAC_CMDCFG_ETH_SPEED;
	cmd &= ~MAC_CMDCFG_ENA_10;

	csrwr32(cmd, priv->mac_dev, tse_csroffs(command_config));

	csrwr32(ALTERA_TSE_PAUSE_QUANTA, priv->mac_dev,
		tse_csroffs(छोड़ो_quanta));

	अगर (netअगर_msg_hw(priv))
		dev_dbg(priv->device,
			"MAC post-initialization: CMD_CONFIG = 0x%08x\n", cmd);

	वापस 0;
पूर्ण

/* Start/stop MAC transmission logic
 */
अटल व्योम tse_set_mac(काष्ठा altera_tse_निजी *priv, bool enable)
अणु
	u32 value = csrrd32(priv->mac_dev, tse_csroffs(command_config));

	अगर (enable)
		value |= MAC_CMDCFG_TX_ENA | MAC_CMDCFG_RX_ENA;
	अन्यथा
		value &= ~(MAC_CMDCFG_TX_ENA | MAC_CMDCFG_RX_ENA);

	csrwr32(value, priv->mac_dev, tse_csroffs(command_config));
पूर्ण

/* Change the MTU
 */
अटल पूर्णांक tse_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	अगर (netअगर_running(dev)) अणु
		netdev_err(dev, "must be stopped to change its MTU\n");
		वापस -EBUSY;
	पूर्ण

	dev->mtu = new_mtu;
	netdev_update_features(dev);

	वापस 0;
पूर्ण

अटल व्योम altera_tse_set_mcfilter(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	पूर्णांक i;
	काष्ठा netdev_hw_addr *ha;

	/* clear the hash filter */
	क्रम (i = 0; i < 64; i++)
		csrwr32(0, priv->mac_dev, tse_csroffs(hash_table) + i * 4);

	netdev_क्रम_each_mc_addr(ha, dev) अणु
		अचिन्हित पूर्णांक hash = 0;
		पूर्णांक mac_octet;

		क्रम (mac_octet = 5; mac_octet >= 0; mac_octet--) अणु
			अचिन्हित अक्षर xor_bit = 0;
			अचिन्हित अक्षर octet = ha->addr[mac_octet];
			अचिन्हित पूर्णांक bitshअगरt;

			क्रम (bitshअगरt = 0; bitshअगरt < 8; bitshअगरt++)
				xor_bit ^= ((octet >> bitshअगरt) & 0x01);

			hash = (hash << 1) | xor_bit;
		पूर्ण
		csrwr32(1, priv->mac_dev, tse_csroffs(hash_table) + hash * 4);
	पूर्ण
पूर्ण


अटल व्योम altera_tse_set_mcfilterall(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	पूर्णांक i;

	/* set the hash filter */
	क्रम (i = 0; i < 64; i++)
		csrwr32(1, priv->mac_dev, tse_csroffs(hash_table) + i * 4);
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor
 */
अटल व्योम tse_set_rx_mode_hashfilter(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);

	spin_lock(&priv->mac_cfg_lock);

	अगर (dev->flags & IFF_PROMISC)
		tse_set_bit(priv->mac_dev, tse_csroffs(command_config),
			    MAC_CMDCFG_PROMIS_EN);

	अगर (dev->flags & IFF_ALLMULTI)
		altera_tse_set_mcfilterall(dev);
	अन्यथा
		altera_tse_set_mcfilter(dev);

	spin_unlock(&priv->mac_cfg_lock);
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor
 */
अटल व्योम tse_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);

	spin_lock(&priv->mac_cfg_lock);

	अगर ((dev->flags & IFF_PROMISC) || (dev->flags & IFF_ALLMULTI) ||
	    !netdev_mc_empty(dev) || !netdev_uc_empty(dev))
		tse_set_bit(priv->mac_dev, tse_csroffs(command_config),
			    MAC_CMDCFG_PROMIS_EN);
	अन्यथा
		tse_clear_bit(priv->mac_dev, tse_csroffs(command_config),
			      MAC_CMDCFG_PROMIS_EN);

	spin_unlock(&priv->mac_cfg_lock);
पूर्ण

/* Initialise (अगर necessary) the SGMII PCS component
 */
अटल पूर्णांक init_sgmii_pcs(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	पूर्णांक n;
	अचिन्हित पूर्णांक पंचांगp_reg = 0;

	अगर (priv->phy_अगरace != PHY_INTERFACE_MODE_SGMII)
		वापस 0; /* Nothing to करो, not in SGMII mode */

	/* The TSE SGMII PCS block looks a little like a PHY, it is
	 * mapped पूर्णांकo the zeroth MDIO space of the MAC and it has
	 * ID रेजिस्टरs like a PHY would.  Sadly this is often
	 * configured to zeroes, so करोn't be surprised अगर it करोes
	 * show 0x00000000.
	 */

	अगर (sgmii_pcs_scratch_test(priv, 0x0000) &&
		sgmii_pcs_scratch_test(priv, 0xffff) &&
		sgmii_pcs_scratch_test(priv, 0xa5a5) &&
		sgmii_pcs_scratch_test(priv, 0x5a5a)) अणु
		netdev_info(dev, "PCS PHY ID: 0x%04x%04x\n",
				sgmii_pcs_पढ़ो(priv, MII_PHYSID1),
				sgmii_pcs_पढ़ो(priv, MII_PHYSID2));
	पूर्ण अन्यथा अणु
		netdev_err(dev, "SGMII PCS Scratch memory test failed.\n");
		वापस -ENOMEM;
	पूर्ण

	/* Starting on page 5-29 of the MegaCore Function User Guide
	 * Set SGMII Link समयr to 1.6ms
	 */
	sgmii_pcs_ग_लिखो(priv, SGMII_PCS_LINK_TIMER_0, 0x0D40);
	sgmii_pcs_ग_लिखो(priv, SGMII_PCS_LINK_TIMER_1, 0x03);

	/* Enable SGMII Interface and Enable SGMII Auto Negotiation */
	sgmii_pcs_ग_लिखो(priv, SGMII_PCS_IF_MODE, 0x3);

	/* Enable Autonegotiation */
	पंचांगp_reg = sgmii_pcs_पढ़ो(priv, MII_BMCR);
	पंचांगp_reg |= (BMCR_SPEED1000 | BMCR_FULLDPLX | BMCR_ANENABLE);
	sgmii_pcs_ग_लिखो(priv, MII_BMCR, पंचांगp_reg);

	/* Reset PCS block */
	पंचांगp_reg |= BMCR_RESET;
	sgmii_pcs_ग_लिखो(priv, MII_BMCR, पंचांगp_reg);
	क्रम (n = 0; n < SGMII_PCS_SW_RESET_TIMEOUT; n++) अणु
		अगर (!(sgmii_pcs_पढ़ो(priv, MII_BMCR) & BMCR_RESET)) अणु
			netdev_info(dev, "SGMII PCS block initialised OK\n");
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण

	/* We failed to reset the block, वापस a समयout */
	netdev_err(dev, "SGMII PCS block reset failed.\n");
	वापस -ETIMEDOUT;
पूर्ण

/* Open and initialize the पूर्णांकerface
 */
अटल पूर्णांक tse_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	पूर्णांक ret = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ पूर्णांक flags;

	/* Reset and configure TSE MAC and probe associated PHY */
	ret = priv->dmaops->init_dma(priv);
	अगर (ret != 0) अणु
		netdev_err(dev, "Cannot initialize DMA\n");
		जाओ phy_error;
	पूर्ण

	अगर (netअगर_msg_अगरup(priv))
		netdev_warn(dev, "device MAC address %pM\n",
			    dev->dev_addr);

	अगर ((priv->revision < 0xd00) || (priv->revision > 0xe00))
		netdev_warn(dev, "TSE revision %x\n", priv->revision);

	spin_lock(&priv->mac_cfg_lock);
	/* no-op अगर MAC not operating in SGMII mode*/
	ret = init_sgmii_pcs(dev);
	अगर (ret) अणु
		netdev_err(dev,
			   "Cannot init the SGMII PCS (error: %d)\n", ret);
		spin_unlock(&priv->mac_cfg_lock);
		जाओ phy_error;
	पूर्ण

	ret = reset_mac(priv);
	/* Note that reset_mac will fail अगर the घड़ीs are gated by the PHY
	 * due to the PHY being put पूर्णांकo isolation or घातer करोwn mode.
	 * This is not an error अगर reset fails due to no घड़ी.
	 */
	अगर (ret)
		netdev_dbg(dev, "Cannot reset MAC core (error: %d)\n", ret);

	ret = init_mac(priv);
	spin_unlock(&priv->mac_cfg_lock);
	अगर (ret) अणु
		netdev_err(dev, "Cannot init MAC core (error: %d)\n", ret);
		जाओ alloc_skbuf_error;
	पूर्ण

	priv->dmaops->reset_dma(priv);

	/* Create and initialize the TX/RX descriptors chains. */
	priv->rx_ring_size = dma_rx_num;
	priv->tx_ring_size = dma_tx_num;
	ret = alloc_init_skbufs(priv);
	अगर (ret) अणु
		netdev_err(dev, "DMA descriptors initialization failed\n");
		जाओ alloc_skbuf_error;
	पूर्ण


	/* Register RX पूर्णांकerrupt */
	ret = request_irq(priv->rx_irq, altera_isr, IRQF_SHARED,
			  dev->name, dev);
	अगर (ret) अणु
		netdev_err(dev, "Unable to register RX interrupt %d\n",
			   priv->rx_irq);
		जाओ init_error;
	पूर्ण

	/* Register TX पूर्णांकerrupt */
	ret = request_irq(priv->tx_irq, altera_isr, IRQF_SHARED,
			  dev->name, dev);
	अगर (ret) अणु
		netdev_err(dev, "Unable to register TX interrupt %d\n",
			   priv->tx_irq);
		जाओ tx_request_irq_error;
	पूर्ण

	/* Enable DMA पूर्णांकerrupts */
	spin_lock_irqsave(&priv->rxdma_irq_lock, flags);
	priv->dmaops->enable_rxirq(priv);
	priv->dmaops->enable_txirq(priv);

	/* Setup RX descriptor chain */
	क्रम (i = 0; i < priv->rx_ring_size; i++)
		priv->dmaops->add_rx_desc(priv, &priv->rx_ring[i]);

	spin_unlock_irqrestore(&priv->rxdma_irq_lock, flags);

	अगर (dev->phydev)
		phy_start(dev->phydev);

	napi_enable(&priv->napi);
	netअगर_start_queue(dev);

	priv->dmaops->start_rxdma(priv);

	/* Start MAC Rx/Tx */
	spin_lock(&priv->mac_cfg_lock);
	tse_set_mac(priv, true);
	spin_unlock(&priv->mac_cfg_lock);

	वापस 0;

tx_request_irq_error:
	मुक्त_irq(priv->rx_irq, dev);
init_error:
	मुक्त_skbufs(dev);
alloc_skbuf_error:
phy_error:
	वापस ret;
पूर्ण

/* Stop TSE MAC पूर्णांकerface and put the device in an inactive state
 */
अटल पूर्णांक tse_shutकरोwn(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	पूर्णांक ret;
	अचिन्हित दीर्घ पूर्णांक flags;

	/* Stop the PHY */
	अगर (dev->phydev)
		phy_stop(dev->phydev);

	netअगर_stop_queue(dev);
	napi_disable(&priv->napi);

	/* Disable DMA पूर्णांकerrupts */
	spin_lock_irqsave(&priv->rxdma_irq_lock, flags);
	priv->dmaops->disable_rxirq(priv);
	priv->dmaops->disable_txirq(priv);
	spin_unlock_irqrestore(&priv->rxdma_irq_lock, flags);

	/* Free the IRQ lines */
	मुक्त_irq(priv->rx_irq, dev);
	मुक्त_irq(priv->tx_irq, dev);

	/* disable and reset the MAC, empties fअगरo */
	spin_lock(&priv->mac_cfg_lock);
	spin_lock(&priv->tx_lock);

	ret = reset_mac(priv);
	/* Note that reset_mac will fail अगर the घड़ीs are gated by the PHY
	 * due to the PHY being put पूर्णांकo isolation or घातer करोwn mode.
	 * This is not an error अगर reset fails due to no घड़ी.
	 */
	अगर (ret)
		netdev_dbg(dev, "Cannot reset MAC core (error: %d)\n", ret);
	priv->dmaops->reset_dma(priv);
	मुक्त_skbufs(dev);

	spin_unlock(&priv->tx_lock);
	spin_unlock(&priv->mac_cfg_lock);

	priv->dmaops->uninit_dma(priv);

	वापस 0;
पूर्ण

अटल काष्ठा net_device_ops altera_tse_netdev_ops = अणु
	.nकरो_खोलो		= tse_खोलो,
	.nकरो_stop		= tse_shutकरोwn,
	.nकरो_start_xmit		= tse_start_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_set_rx_mode	= tse_set_rx_mode,
	.nकरो_change_mtu		= tse_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक request_and_map(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name,
			   काष्ठा resource **res, व्योम __iomem **ptr)
अणु
	काष्ठा resource *region;
	काष्ठा device *device = &pdev->dev;

	*res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, name);
	अगर (*res == शून्य) अणु
		dev_err(device, "resource %s not defined\n", name);
		वापस -ENODEV;
	पूर्ण

	region = devm_request_mem_region(device, (*res)->start,
					 resource_size(*res), dev_name(device));
	अगर (region == शून्य) अणु
		dev_err(device, "unable to request %s\n", name);
		वापस -EBUSY;
	पूर्ण

	*ptr = devm_ioremap(device, region->start,
				    resource_size(region));
	अगर (*ptr == शून्य) अणु
		dev_err(device, "ioremap of %s failed!", name);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* Probe Altera TSE MAC device
 */
अटल पूर्णांक altera_tse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev;
	पूर्णांक ret = -ENODEV;
	काष्ठा resource *control_port;
	काष्ठा resource *dma_res;
	काष्ठा altera_tse_निजी *priv;
	व्योम __iomem *descmap;
	स्थिर काष्ठा of_device_id *of_id = शून्य;

	ndev = alloc_etherdev(माप(काष्ठा altera_tse_निजी));
	अगर (!ndev) अणु
		dev_err(&pdev->dev, "Could not allocate network device\n");
		वापस -ENODEV;
	पूर्ण

	SET_NETDEV_DEV(ndev, &pdev->dev);

	priv = netdev_priv(ndev);
	priv->device = &pdev->dev;
	priv->dev = ndev;
	priv->msg_enable = netअगर_msg_init(debug, शेष_msg_level);

	of_id = of_match_device(altera_tse_ids, &pdev->dev);

	अगर (of_id)
		priv->dmaops = (काष्ठा altera_dmaops *)of_id->data;


	अगर (priv->dmaops &&
	    priv->dmaops->altera_dtype == ALTERA_DTYPE_SGDMA) अणु
		/* Get the mapped address to the SGDMA descriptor memory */
		ret = request_and_map(pdev, "s1", &dma_res, &descmap);
		अगर (ret)
			जाओ err_मुक्त_netdev;

		/* Start of that memory is क्रम transmit descriptors */
		priv->tx_dma_desc = descmap;

		/* First half is क्रम tx descriptors, other half क्रम tx */
		priv->txdescmem = resource_size(dma_res)/2;

		priv->txdescmem_busaddr = (dma_addr_t)dma_res->start;

		priv->rx_dma_desc = (व्योम __iomem *)((uपूर्णांकptr_t)(descmap +
						     priv->txdescmem));
		priv->rxdescmem = resource_size(dma_res)/2;
		priv->rxdescmem_busaddr = dma_res->start;
		priv->rxdescmem_busaddr += priv->txdescmem;

		अगर (upper_32_bits(priv->rxdescmem_busaddr)) अणु
			dev_dbg(priv->device,
				"SGDMA bus addresses greater than 32-bits\n");
			ret = -EINVAL;
			जाओ err_मुक्त_netdev;
		पूर्ण
		अगर (upper_32_bits(priv->txdescmem_busaddr)) अणु
			dev_dbg(priv->device,
				"SGDMA bus addresses greater than 32-bits\n");
			ret = -EINVAL;
			जाओ err_मुक्त_netdev;
		पूर्ण
	पूर्ण अन्यथा अगर (priv->dmaops &&
		   priv->dmaops->altera_dtype == ALTERA_DTYPE_MSGDMA) अणु
		ret = request_and_map(pdev, "rx_resp", &dma_res,
				      &priv->rx_dma_resp);
		अगर (ret)
			जाओ err_मुक्त_netdev;

		ret = request_and_map(pdev, "tx_desc", &dma_res,
				      &priv->tx_dma_desc);
		अगर (ret)
			जाओ err_मुक्त_netdev;

		priv->txdescmem = resource_size(dma_res);
		priv->txdescmem_busaddr = dma_res->start;

		ret = request_and_map(pdev, "rx_desc", &dma_res,
				      &priv->rx_dma_desc);
		अगर (ret)
			जाओ err_मुक्त_netdev;

		priv->rxdescmem = resource_size(dma_res);
		priv->rxdescmem_busaddr = dma_res->start;

	पूर्ण अन्यथा अणु
		जाओ err_मुक्त_netdev;
	पूर्ण

	अगर (!dma_set_mask(priv->device, DMA_BIT_MASK(priv->dmaops->dmamask)))
		dma_set_coherent_mask(priv->device,
				      DMA_BIT_MASK(priv->dmaops->dmamask));
	अन्यथा अगर (!dma_set_mask(priv->device, DMA_BIT_MASK(32)))
		dma_set_coherent_mask(priv->device, DMA_BIT_MASK(32));
	अन्यथा
		जाओ err_मुक्त_netdev;

	/* MAC address space */
	ret = request_and_map(pdev, "control_port", &control_port,
			      (व्योम __iomem **)&priv->mac_dev);
	अगर (ret)
		जाओ err_मुक्त_netdev;

	/* xSGDMA Rx Dispatcher address space */
	ret = request_and_map(pdev, "rx_csr", &dma_res,
			      &priv->rx_dma_csr);
	अगर (ret)
		जाओ err_मुक्त_netdev;


	/* xSGDMA Tx Dispatcher address space */
	ret = request_and_map(pdev, "tx_csr", &dma_res,
			      &priv->tx_dma_csr);
	अगर (ret)
		जाओ err_मुक्त_netdev;


	/* Rx IRQ */
	priv->rx_irq = platक्रमm_get_irq_byname(pdev, "rx_irq");
	अगर (priv->rx_irq == -ENXIO) अणु
		dev_err(&pdev->dev, "cannot obtain Rx IRQ\n");
		ret = -ENXIO;
		जाओ err_मुक्त_netdev;
	पूर्ण

	/* Tx IRQ */
	priv->tx_irq = platक्रमm_get_irq_byname(pdev, "tx_irq");
	अगर (priv->tx_irq == -ENXIO) अणु
		dev_err(&pdev->dev, "cannot obtain Tx IRQ\n");
		ret = -ENXIO;
		जाओ err_मुक्त_netdev;
	पूर्ण

	/* get FIFO depths from device tree */
	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "rx-fifo-depth",
				 &priv->rx_fअगरo_depth)) अणु
		dev_err(&pdev->dev, "cannot obtain rx-fifo-depth\n");
		ret = -ENXIO;
		जाओ err_मुक्त_netdev;
	पूर्ण

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "tx-fifo-depth",
				 &priv->tx_fअगरo_depth)) अणु
		dev_err(&pdev->dev, "cannot obtain tx-fifo-depth\n");
		ret = -ENXIO;
		जाओ err_मुक्त_netdev;
	पूर्ण

	/* get hash filter settings क्रम this instance */
	priv->hash_filter =
		of_property_पढ़ो_bool(pdev->dev.of_node,
				      "altr,has-hash-multicast-filter");

	/* Set hash filter to not set क्रम now until the
	 * multicast filter receive issue is debugged
	 */
	priv->hash_filter = 0;

	/* get supplemental address settings क्रम this instance */
	priv->added_unicast =
		of_property_पढ़ो_bool(pdev->dev.of_node,
				      "altr,has-supplementary-unicast");

	priv->dev->min_mtu = ETH_ZLEN + ETH_FCS_LEN;
	/* Max MTU is 1500, ETH_DATA_LEN */
	priv->dev->max_mtu = ETH_DATA_LEN;

	/* Get the max mtu from the device tree. Note that the
	 * "max-frame-size" parameter is actually max mtu. Definition
	 * in the ePAPR v1.1 spec and usage dअगरfer, so go with usage.
	 */
	of_property_पढ़ो_u32(pdev->dev.of_node, "max-frame-size",
			     &priv->dev->max_mtu);

	/* The DMA buffer size alपढ़ोy accounts क्रम an alignment bias
	 * to aव्योम unaligned access exceptions क्रम the NIOS processor,
	 */
	priv->rx_dma_buf_sz = ALTERA_RXDMABUFFER_SIZE;

	/* get शेष MAC address from device tree */
	ret = of_get_mac_address(pdev->dev.of_node, ndev->dev_addr);
	अगर (ret)
		eth_hw_addr_अक्रमom(ndev);

	/* get phy addr and create mdio */
	ret = altera_tse_phy_get_addr_mdio_create(ndev);

	अगर (ret)
		जाओ err_मुक्त_netdev;

	/* initialize netdev */
	ndev->mem_start = control_port->start;
	ndev->mem_end = control_port->end;
	ndev->netdev_ops = &altera_tse_netdev_ops;
	altera_tse_set_ethtool_ops(ndev);

	altera_tse_netdev_ops.nकरो_set_rx_mode = tse_set_rx_mode;

	अगर (priv->hash_filter)
		altera_tse_netdev_ops.nकरो_set_rx_mode =
			tse_set_rx_mode_hashfilter;

	/* Scatter/gather IO is not supported,
	 * so it is turned off
	 */
	ndev->hw_features &= ~NETIF_F_SG;
	ndev->features |= ndev->hw_features | NETIF_F_HIGHDMA;

	/* VLAN offloading of tagging, stripping and filtering is not
	 * supported by hardware, but driver will accommodate the
	 * extra 4-byte VLAN tag क्रम processing by upper layers
	 */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_RX;

	/* setup NAPI पूर्णांकerface */
	netअगर_napi_add(ndev, &priv->napi, tse_poll, NAPI_POLL_WEIGHT);

	spin_lock_init(&priv->mac_cfg_lock);
	spin_lock_init(&priv->tx_lock);
	spin_lock_init(&priv->rxdma_irq_lock);

	netअगर_carrier_off(ndev);
	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register TSE net device\n");
		जाओ err_रेजिस्टर_netdev;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ndev);

	priv->revision = ioपढ़ो32(&priv->mac_dev->megacore_revision);

	अगर (netअगर_msg_probe(priv))
		dev_info(&pdev->dev, "Altera TSE MAC version %d.%d at 0x%08lx irq %d/%d\n",
			 (priv->revision >> 8) & 0xff,
			 priv->revision & 0xff,
			 (अचिन्हित दीर्घ) control_port->start, priv->rx_irq,
			 priv->tx_irq);

	ret = init_phy(ndev);
	अगर (ret != 0) अणु
		netdev_err(ndev, "Cannot attach to PHY (error: %d)\n", ret);
		जाओ err_init_phy;
	पूर्ण
	वापस 0;

err_init_phy:
	unरेजिस्टर_netdev(ndev);
err_रेजिस्टर_netdev:
	netअगर_napi_del(&priv->napi);
	altera_tse_mdio_destroy(ndev);
err_मुक्त_netdev:
	मुक्त_netdev(ndev);
	वापस ret;
पूर्ण

/* Remove Altera TSE MAC device
 */
अटल पूर्णांक altera_tse_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा altera_tse_निजी *priv = netdev_priv(ndev);

	अगर (ndev->phydev) अणु
		phy_disconnect(ndev->phydev);

		अगर (of_phy_is_fixed_link(priv->device->of_node))
			of_phy_deरेजिस्टर_fixed_link(priv->device->of_node);
	पूर्ण

	platक्रमm_set_drvdata(pdev, शून्य);
	altera_tse_mdio_destroy(ndev);
	unरेजिस्टर_netdev(ndev);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा altera_dmaops altera_dtype_sgdma = अणु
	.altera_dtype = ALTERA_DTYPE_SGDMA,
	.dmamask = 32,
	.reset_dma = sgdma_reset,
	.enable_txirq = sgdma_enable_txirq,
	.enable_rxirq = sgdma_enable_rxirq,
	.disable_txirq = sgdma_disable_txirq,
	.disable_rxirq = sgdma_disable_rxirq,
	.clear_txirq = sgdma_clear_txirq,
	.clear_rxirq = sgdma_clear_rxirq,
	.tx_buffer = sgdma_tx_buffer,
	.tx_completions = sgdma_tx_completions,
	.add_rx_desc = sgdma_add_rx_desc,
	.get_rx_status = sgdma_rx_status,
	.init_dma = sgdma_initialize,
	.uninit_dma = sgdma_uninitialize,
	.start_rxdma = sgdma_start_rxdma,
पूर्ण;

अटल स्थिर काष्ठा altera_dmaops altera_dtype_msgdma = अणु
	.altera_dtype = ALTERA_DTYPE_MSGDMA,
	.dmamask = 64,
	.reset_dma = msgdma_reset,
	.enable_txirq = msgdma_enable_txirq,
	.enable_rxirq = msgdma_enable_rxirq,
	.disable_txirq = msgdma_disable_txirq,
	.disable_rxirq = msgdma_disable_rxirq,
	.clear_txirq = msgdma_clear_txirq,
	.clear_rxirq = msgdma_clear_rxirq,
	.tx_buffer = msgdma_tx_buffer,
	.tx_completions = msgdma_tx_completions,
	.add_rx_desc = msgdma_add_rx_desc,
	.get_rx_status = msgdma_rx_status,
	.init_dma = msgdma_initialize,
	.uninit_dma = msgdma_uninitialize,
	.start_rxdma = msgdma_start_rxdma,
पूर्ण;

अटल स्थिर काष्ठा of_device_id altera_tse_ids[] = अणु
	अणु .compatible = "altr,tse-msgdma-1.0", .data = &altera_dtype_msgdma, पूर्ण,
	अणु .compatible = "altr,tse-1.0", .data = &altera_dtype_sgdma, पूर्ण,
	अणु .compatible = "ALTR,tse-1.0", .data = &altera_dtype_sgdma, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altera_tse_ids);

अटल काष्ठा platक्रमm_driver altera_tse_driver = अणु
	.probe		= altera_tse_probe,
	.हटाओ		= altera_tse_हटाओ,
	.suspend	= शून्य,
	.resume		= शून्य,
	.driver		= अणु
		.name	= ALTERA_TSE_RESOURCE_NAME,
		.of_match_table = altera_tse_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(altera_tse_driver);

MODULE_AUTHOR("Altera Corporation");
MODULE_DESCRIPTION("Altera Triple Speed Ethernet MAC driver");
MODULE_LICENSE("GPL v2");
