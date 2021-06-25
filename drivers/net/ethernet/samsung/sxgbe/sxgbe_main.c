<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sxgbe_platक्रमm.h>

#समावेश "sxgbe_common.h"
#समावेश "sxgbe_desc.h"
#समावेश "sxgbe_dma.h"
#समावेश "sxgbe_mtl.h"
#समावेश "sxgbe_reg.h"

#घोषणा SXGBE_ALIGN(x)	L1_CACHE_ALIGN(x)
#घोषणा JUMBO_LEN	9000

/* Module parameters */
#घोषणा TX_TIMEO	5000
#घोषणा DMA_TX_SIZE	512
#घोषणा DMA_RX_SIZE	1024
#घोषणा TC_DEFAULT	64
#घोषणा DMA_BUFFER_SIZE	BUF_SIZE_2KiB
/* The शेष समयr value as per the sxgbe specअगरication 1 sec(1000 ms) */
#घोषणा SXGBE_DEFAULT_LPI_TIMER	1000

अटल पूर्णांक debug = -1;
अटल पूर्णांक eee_समयr = SXGBE_DEFAULT_LPI_TIMER;

module_param(eee_समयr, पूर्णांक, 0644);

module_param(debug, पूर्णांक, 0644);
अटल स्थिर u32 शेष_msg_level = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
				      NETIF_MSG_LINK | NETIF_MSG_IFUP |
				      NETIF_MSG_IFDOWN | NETIF_MSG_TIMER);

अटल irqवापस_t sxgbe_common_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t sxgbe_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t sxgbe_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

#घोषणा SXGBE_COAL_TIMER(x) (jअगरfies + usecs_to_jअगरfies(x))

#घोषणा SXGBE_LPI_TIMER(x) (jअगरfies + msecs_to_jअगरfies(x))

/**
 * sxgbe_verअगरy_args - verअगरy the driver parameters.
 * Description: it verअगरies अगर some wrong parameter is passed to the driver.
 * Note that wrong parameters are replaced with the शेष values.
 */
अटल व्योम sxgbe_verअगरy_args(व्योम)
अणु
	अगर (unlikely(eee_समयr < 0))
		eee_समयr = SXGBE_DEFAULT_LPI_TIMER;
पूर्ण

अटल व्योम sxgbe_enable_eee_mode(स्थिर काष्ठा sxgbe_priv_data *priv)
अणु
	/* Check and enter in LPI mode */
	अगर (!priv->tx_path_in_lpi_mode)
		priv->hw->mac->set_eee_mode(priv->ioaddr);
पूर्ण

व्योम sxgbe_disable_eee_mode(काष्ठा sxgbe_priv_data * स्थिर priv)
अणु
	/* Exit and disable EEE in हाल of we are are in LPI state. */
	priv->hw->mac->reset_eee_mode(priv->ioaddr);
	del_समयr_sync(&priv->eee_ctrl_समयr);
	priv->tx_path_in_lpi_mode = false;
पूर्ण

/**
 * sxgbe_eee_ctrl_समयr
 * @t: समयr list containing a data
 * Description:
 *  If there is no data transfer and अगर we are not in LPI state,
 *  then MAC Transmitter can be moved to LPI state.
 */
अटल व्योम sxgbe_eee_ctrl_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sxgbe_priv_data *priv = from_समयr(priv, t, eee_ctrl_समयr);

	sxgbe_enable_eee_mode(priv);
	mod_समयr(&priv->eee_ctrl_समयr, SXGBE_LPI_TIMER(eee_समयr));
पूर्ण

/**
 * sxgbe_eee_init
 * @priv: निजी device poपूर्णांकer
 * Description:
 *  If the EEE support has been enabled जबतक configuring the driver,
 *  अगर the GMAC actually supports the EEE (from the HW cap reg) and the
 *  phy can also manage EEE, so enable the LPI state and start the समयr
 *  to verअगरy अगर the tx path can enter in LPI state.
 */
bool sxgbe_eee_init(काष्ठा sxgbe_priv_data * स्थिर priv)
अणु
	काष्ठा net_device *ndev = priv->dev;
	bool ret = false;

	/* MAC core supports the EEE feature. */
	अगर (priv->hw_cap.eee) अणु
		/* Check अगर the PHY supports EEE */
		अगर (phy_init_eee(ndev->phydev, 1))
			वापस false;

		priv->eee_active = 1;
		समयr_setup(&priv->eee_ctrl_समयr, sxgbe_eee_ctrl_समयr, 0);
		priv->eee_ctrl_समयr.expires = SXGBE_LPI_TIMER(eee_समयr);
		add_समयr(&priv->eee_ctrl_समयr);

		priv->hw->mac->set_eee_समयr(priv->ioaddr,
					     SXGBE_DEFAULT_LPI_TIMER,
					     priv->tx_lpi_समयr);

		pr_info("Energy-Efficient Ethernet initialized\n");

		ret = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sxgbe_eee_adjust(स्थिर काष्ठा sxgbe_priv_data *priv)
अणु
	काष्ठा net_device *ndev = priv->dev;

	/* When the EEE has been alपढ़ोy initialised we have to
	 * modअगरy the PLS bit in the LPI ctrl & status reg according
	 * to the PHY link status. For this reason.
	 */
	अगर (priv->eee_enabled)
		priv->hw->mac->set_eee_pls(priv->ioaddr, ndev->phydev->link);
पूर्ण

/**
 * sxgbe_clk_csr_set - dynamically set the MDC घड़ी
 * @priv: driver निजी काष्ठाure
 * Description: this is to dynamically set the MDC घड़ी according to the csr
 * घड़ी input.
 */
अटल व्योम sxgbe_clk_csr_set(काष्ठा sxgbe_priv_data *priv)
अणु
	u32 clk_rate = clk_get_rate(priv->sxgbe_clk);

	/* assign the proper भागider, this will be used during
	 * mdio communication
	 */
	अगर (clk_rate < SXGBE_CSR_F_150M)
		priv->clk_csr = SXGBE_CSR_100_150M;
	अन्यथा अगर (clk_rate <= SXGBE_CSR_F_250M)
		priv->clk_csr = SXGBE_CSR_150_250M;
	अन्यथा अगर (clk_rate <= SXGBE_CSR_F_300M)
		priv->clk_csr = SXGBE_CSR_250_300M;
	अन्यथा अगर (clk_rate <= SXGBE_CSR_F_350M)
		priv->clk_csr = SXGBE_CSR_300_350M;
	अन्यथा अगर (clk_rate <= SXGBE_CSR_F_400M)
		priv->clk_csr = SXGBE_CSR_350_400M;
	अन्यथा अगर (clk_rate <= SXGBE_CSR_F_500M)
		priv->clk_csr = SXGBE_CSR_400_500M;
पूर्ण

/* minimum number of मुक्त TX descriptors required to wake up TX process */
#घोषणा SXGBE_TX_THRESH(x)	(x->dma_tx_size/4)

अटल अंतरभूत u32 sxgbe_tx_avail(काष्ठा sxgbe_tx_queue *queue, पूर्णांक tx_qsize)
अणु
	वापस queue->dirty_tx + tx_qsize - queue->cur_tx - 1;
पूर्ण

/**
 * sxgbe_adjust_link
 * @dev: net device काष्ठाure
 * Description: it adjusts the link parameters.
 */
अटल व्योम sxgbe_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	u8 new_state = 0;
	u8 speed = 0xff;

	अगर (!phydev)
		वापस;

	/* SXGBE is not supporting स्वतः-negotiation and
	 * half duplex mode. so, not handling duplex change
	 * in this function. only handling speed and link status
	 */
	अगर (phydev->link) अणु
		अगर (phydev->speed != priv->speed) अणु
			new_state = 1;
			चयन (phydev->speed) अणु
			हाल SPEED_10000:
				speed = SXGBE_SPEED_10G;
				अवरोध;
			हाल SPEED_2500:
				speed = SXGBE_SPEED_2_5G;
				अवरोध;
			हाल SPEED_1000:
				speed = SXGBE_SPEED_1G;
				अवरोध;
			शेष:
				netअगर_err(priv, link, dev,
					  "Speed (%d) not supported\n",
					  phydev->speed);
			पूर्ण

			priv->speed = phydev->speed;
			priv->hw->mac->set_speed(priv->ioaddr, speed);
		पूर्ण

		अगर (!priv->oldlink) अणु
			new_state = 1;
			priv->oldlink = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (priv->oldlink) अणु
		new_state = 1;
		priv->oldlink = 0;
		priv->speed = SPEED_UNKNOWN;
	पूर्ण

	अगर (new_state & netअगर_msg_link(priv))
		phy_prपूर्णांक_status(phydev);

	/* Alter the MAC settings क्रम EEE */
	sxgbe_eee_adjust(priv);
पूर्ण

/**
 * sxgbe_init_phy - PHY initialization
 * @ndev: net device काष्ठाure
 * Description: it initializes the driver's PHY state, and attaches the PHY
 * to the mac driver.
 *  Return value:
 *  0 on success
 */
अटल पूर्णांक sxgbe_init_phy(काष्ठा net_device *ndev)
अणु
	अक्षर phy_id_fmt[MII_BUS_ID_SIZE + 3];
	अक्षर bus_id[MII_BUS_ID_SIZE];
	काष्ठा phy_device *phydev;
	काष्ठा sxgbe_priv_data *priv = netdev_priv(ndev);
	पूर्णांक phy_अगरace = priv->plat->पूर्णांकerface;

	/* assign शेष link status */
	priv->oldlink = 0;
	priv->speed = SPEED_UNKNOWN;
	priv->oldduplex = DUPLEX_UNKNOWN;

	अगर (priv->plat->phy_bus_name)
		snम_लिखो(bus_id, MII_BUS_ID_SIZE, "%s-%x",
			 priv->plat->phy_bus_name, priv->plat->bus_id);
	अन्यथा
		snम_लिखो(bus_id, MII_BUS_ID_SIZE, "sxgbe-%x",
			 priv->plat->bus_id);

	snम_लिखो(phy_id_fmt, MII_BUS_ID_SIZE + 3, PHY_ID_FMT, bus_id,
		 priv->plat->phy_addr);
	netdev_dbg(ndev, "%s: trying to attach to %s\n", __func__, phy_id_fmt);

	phydev = phy_connect(ndev, phy_id_fmt, &sxgbe_adjust_link, phy_अगरace);

	अगर (IS_ERR(phydev)) अणु
		netdev_err(ndev, "Could not attach to PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण

	/* Stop Advertising 1000BASE Capability अगर पूर्णांकerface is not GMII */
	अगर ((phy_अगरace == PHY_INTERFACE_MODE_MII) ||
	    (phy_अगरace == PHY_INTERFACE_MODE_RMII))
		phy_set_max_speed(phydev, SPEED_1000);

	अगर (phydev->phy_id == 0) अणु
		phy_disconnect(phydev);
		वापस -ENODEV;
	पूर्ण

	netdev_dbg(ndev, "%s: attached to PHY (UID 0x%x) Link = %d\n",
		   __func__, phydev->phy_id, phydev->link);

	वापस 0;
पूर्ण

/**
 * sxgbe_clear_descriptors: clear descriptors
 * @priv: driver निजी काष्ठाure
 * Description: this function is called to clear the tx and rx descriptors
 * in हाल of both basic and extended descriptors are used.
 */
अटल व्योम sxgbe_clear_descriptors(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक i, j;
	अचिन्हित पूर्णांक txsize = priv->dma_tx_size;
	अचिन्हित पूर्णांक rxsize = priv->dma_rx_size;

	/* Clear the Rx/Tx descriptors */
	क्रम (j = 0; j < SXGBE_RX_QUEUES; j++) अणु
		क्रम (i = 0; i < rxsize; i++)
			priv->hw->desc->init_rx_desc(&priv->rxq[j]->dma_rx[i],
						     priv->use_riwt, priv->mode,
						     (i == rxsize - 1));
	पूर्ण

	क्रम (j = 0; j < SXGBE_TX_QUEUES; j++) अणु
		क्रम (i = 0; i < txsize; i++)
			priv->hw->desc->init_tx_desc(&priv->txq[j]->dma_tx[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक sxgbe_init_rx_buffers(काष्ठा net_device *dev,
				 काष्ठा sxgbe_rx_norm_desc *p, पूर्णांक i,
				 अचिन्हित पूर्णांक dma_buf_sz,
				 काष्ठा sxgbe_rx_queue *rx_ring)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	काष्ठा sk_buff *skb;

	skb = __netdev_alloc_skb_ip_align(dev, dma_buf_sz, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	rx_ring->rx_skbuff[i] = skb;
	rx_ring->rx_skbuff_dma[i] = dma_map_single(priv->device, skb->data,
						   dma_buf_sz, DMA_FROM_DEVICE);

	अगर (dma_mapping_error(priv->device, rx_ring->rx_skbuff_dma[i])) अणु
		netdev_err(dev, "%s: DMA mapping error\n", __func__);
		dev_kमुक्त_skb_any(skb);
		वापस -EINVAL;
	पूर्ण

	p->rdes23.rx_rd_des23.buf2_addr = rx_ring->rx_skbuff_dma[i];

	वापस 0;
पूर्ण

/**
 * sxgbe_मुक्त_rx_buffers - मुक्त what sxgbe_init_rx_buffers() allocated
 * @dev: net device काष्ठाure
 * @p: dec poपूर्णांकer
 * @i: index
 * @dma_buf_sz: size
 * @rx_ring: ring to be मुक्तd
 *
 * Description:  this function initializes the DMA RX descriptor
 */
अटल व्योम sxgbe_मुक्त_rx_buffers(काष्ठा net_device *dev,
				  काष्ठा sxgbe_rx_norm_desc *p, पूर्णांक i,
				  अचिन्हित पूर्णांक dma_buf_sz,
				  काष्ठा sxgbe_rx_queue *rx_ring)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);

	kमुक्त_skb(rx_ring->rx_skbuff[i]);
	dma_unmap_single(priv->device, rx_ring->rx_skbuff_dma[i],
			 dma_buf_sz, DMA_FROM_DEVICE);
पूर्ण

/**
 * init_tx_ring - init the TX descriptor ring
 * @dev: net device काष्ठाure
 * @queue_no: queue
 * @tx_ring: ring to be initialised
 * @tx_rsize: ring size
 * Description:  this function initializes the DMA TX descriptor
 */
अटल पूर्णांक init_tx_ring(काष्ठा device *dev, u8 queue_no,
			काष्ठा sxgbe_tx_queue *tx_ring,	पूर्णांक tx_rsize)
अणु
	/* TX ring is not allcoated */
	अगर (!tx_ring) अणु
		dev_err(dev, "No memory for TX queue of SXGBE\n");
		वापस -ENOMEM;
	पूर्ण

	/* allocate memory क्रम TX descriptors */
	tx_ring->dma_tx = dma_alloc_coherent(dev,
					     tx_rsize * माप(काष्ठा sxgbe_tx_norm_desc),
					     &tx_ring->dma_tx_phy, GFP_KERNEL);
	अगर (!tx_ring->dma_tx)
		वापस -ENOMEM;

	/* allocate memory क्रम TX skbuff array */
	tx_ring->tx_skbuff_dma = devm_kसुस्मृति(dev, tx_rsize,
					      माप(dma_addr_t), GFP_KERNEL);
	अगर (!tx_ring->tx_skbuff_dma)
		जाओ dmamem_err;

	tx_ring->tx_skbuff = devm_kसुस्मृति(dev, tx_rsize,
					  माप(काष्ठा sk_buff *), GFP_KERNEL);

	अगर (!tx_ring->tx_skbuff)
		जाओ dmamem_err;

	/* assign queue number */
	tx_ring->queue_no = queue_no;

	/* initialise counters */
	tx_ring->dirty_tx = 0;
	tx_ring->cur_tx = 0;

	वापस 0;

dmamem_err:
	dma_मुक्त_coherent(dev, tx_rsize * माप(काष्ठा sxgbe_tx_norm_desc),
			  tx_ring->dma_tx, tx_ring->dma_tx_phy);
	वापस -ENOMEM;
पूर्ण

/**
 * मुक्त_rx_ring - मुक्त the RX descriptor ring
 * @dev: net device काष्ठाure
 * @rx_ring: ring to be initialised
 * @rx_rsize: ring size
 * Description:  this function initializes the DMA RX descriptor
 */
अटल व्योम मुक्त_rx_ring(काष्ठा device *dev, काष्ठा sxgbe_rx_queue *rx_ring,
			 पूर्णांक rx_rsize)
अणु
	dma_मुक्त_coherent(dev, rx_rsize * माप(काष्ठा sxgbe_rx_norm_desc),
			  rx_ring->dma_rx, rx_ring->dma_rx_phy);
	kमुक्त(rx_ring->rx_skbuff_dma);
	kमुक्त(rx_ring->rx_skbuff);
पूर्ण

/**
 * init_rx_ring - init the RX descriptor ring
 * @dev: net device काष्ठाure
 * @queue_no: queue
 * @rx_ring: ring to be initialised
 * @rx_rsize: ring size
 * Description:  this function initializes the DMA RX descriptor
 */
अटल पूर्णांक init_rx_ring(काष्ठा net_device *dev, u8 queue_no,
			काष्ठा sxgbe_rx_queue *rx_ring,	पूर्णांक rx_rsize)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	पूर्णांक desc_index;
	अचिन्हित पूर्णांक bfsize = 0;
	अचिन्हित पूर्णांक ret = 0;

	/* Set the max buffer size according to the MTU. */
	bfsize = ALIGN(dev->mtu + ETH_HLEN + ETH_FCS_LEN + NET_IP_ALIGN, 8);

	netअगर_dbg(priv, probe, dev, "%s: bfsize %d\n", __func__, bfsize);

	/* RX ring is not allcoated */
	अगर (rx_ring == शून्य) अणु
		netdev_err(dev, "No memory for RX queue\n");
		वापस -ENOMEM;
	पूर्ण

	/* assign queue number */
	rx_ring->queue_no = queue_no;

	/* allocate memory क्रम RX descriptors */
	rx_ring->dma_rx = dma_alloc_coherent(priv->device,
					     rx_rsize * माप(काष्ठा sxgbe_rx_norm_desc),
					     &rx_ring->dma_rx_phy, GFP_KERNEL);

	अगर (rx_ring->dma_rx == शून्य)
		वापस -ENOMEM;

	/* allocate memory क्रम RX skbuff array */
	rx_ring->rx_skbuff_dma = kदो_स्मृति_array(rx_rsize,
					       माप(dma_addr_t), GFP_KERNEL);
	अगर (!rx_ring->rx_skbuff_dma) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_dma_rx;
	पूर्ण

	rx_ring->rx_skbuff = kदो_स्मृति_array(rx_rsize,
					   माप(काष्ठा sk_buff *), GFP_KERNEL);
	अगर (!rx_ring->rx_skbuff) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_skbuff_dma;
	पूर्ण

	/* initialise the buffers */
	क्रम (desc_index = 0; desc_index < rx_rsize; desc_index++) अणु
		काष्ठा sxgbe_rx_norm_desc *p;
		p = rx_ring->dma_rx + desc_index;
		ret = sxgbe_init_rx_buffers(dev, p, desc_index,
					    bfsize, rx_ring);
		अगर (ret)
			जाओ err_मुक्त_rx_buffers;
	पूर्ण

	/* initialise counters */
	rx_ring->cur_rx = 0;
	rx_ring->dirty_rx = (अचिन्हित पूर्णांक)(desc_index - rx_rsize);
	priv->dma_buf_sz = bfsize;

	वापस 0;

err_मुक्त_rx_buffers:
	जबतक (--desc_index >= 0) अणु
		काष्ठा sxgbe_rx_norm_desc *p;

		p = rx_ring->dma_rx + desc_index;
		sxgbe_मुक्त_rx_buffers(dev, p, desc_index, bfsize, rx_ring);
	पूर्ण
	kमुक्त(rx_ring->rx_skbuff);
err_मुक्त_skbuff_dma:
	kमुक्त(rx_ring->rx_skbuff_dma);
err_मुक्त_dma_rx:
	dma_मुक्त_coherent(priv->device,
			  rx_rsize * माप(काष्ठा sxgbe_rx_norm_desc),
			  rx_ring->dma_rx, rx_ring->dma_rx_phy);

	वापस ret;
पूर्ण
/**
 * मुक्त_tx_ring - मुक्त the TX descriptor ring
 * @dev: net device काष्ठाure
 * @tx_ring: ring to be initialised
 * @tx_rsize: ring size
 * Description:  this function initializes the DMA TX descriptor
 */
अटल व्योम मुक्त_tx_ring(काष्ठा device *dev, काष्ठा sxgbe_tx_queue *tx_ring,
			 पूर्णांक tx_rsize)
अणु
	dma_मुक्त_coherent(dev, tx_rsize * माप(काष्ठा sxgbe_tx_norm_desc),
			  tx_ring->dma_tx, tx_ring->dma_tx_phy);
पूर्ण

/**
 * init_dma_desc_rings - init the RX/TX descriptor rings
 * @netd: net device काष्ठाure
 * Description:  this function initializes the DMA RX/TX descriptors
 * and allocates the socket buffers. It suppors the chained and ring
 * modes.
 */
अटल पूर्णांक init_dma_desc_rings(काष्ठा net_device *netd)
अणु
	पूर्णांक queue_num, ret;
	काष्ठा sxgbe_priv_data *priv = netdev_priv(netd);
	पूर्णांक tx_rsize = priv->dma_tx_size;
	पूर्णांक rx_rsize = priv->dma_rx_size;

	/* Allocate memory क्रम queue काष्ठाures and TX descs */
	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
		ret = init_tx_ring(priv->device, queue_num,
				   priv->txq[queue_num], tx_rsize);
		अगर (ret) अणु
			dev_err(&netd->dev, "TX DMA ring allocation failed!\n");
			जाओ txalloc_err;
		पूर्ण

		/* save निजी poपूर्णांकer in each ring this
		 * poपूर्णांकer is needed during cleaing TX queue
		 */
		priv->txq[queue_num]->priv_ptr = priv;
	पूर्ण

	/* Allocate memory क्रम queue काष्ठाures and RX descs */
	SXGBE_FOR_EACH_QUEUE(SXGBE_RX_QUEUES, queue_num) अणु
		ret = init_rx_ring(netd, queue_num,
				   priv->rxq[queue_num], rx_rsize);
		अगर (ret) अणु
			netdev_err(netd, "RX DMA ring allocation failed!!\n");
			जाओ rxalloc_err;
		पूर्ण

		/* save निजी poपूर्णांकer in each ring this
		 * poपूर्णांकer is needed during cleaing TX queue
		 */
		priv->rxq[queue_num]->priv_ptr = priv;
	पूर्ण

	sxgbe_clear_descriptors(priv);

	वापस 0;

txalloc_err:
	जबतक (queue_num--)
		मुक्त_tx_ring(priv->device, priv->txq[queue_num], tx_rsize);
	वापस ret;

rxalloc_err:
	जबतक (queue_num--)
		मुक्त_rx_ring(priv->device, priv->rxq[queue_num], rx_rsize);
	वापस ret;
पूर्ण

अटल व्योम tx_मुक्त_ring_skbufs(काष्ठा sxgbe_tx_queue *txqueue)
अणु
	पूर्णांक dma_desc;
	काष्ठा sxgbe_priv_data *priv = txqueue->priv_ptr;
	पूर्णांक tx_rsize = priv->dma_tx_size;

	क्रम (dma_desc = 0; dma_desc < tx_rsize; dma_desc++) अणु
		काष्ठा sxgbe_tx_norm_desc *tdesc = txqueue->dma_tx + dma_desc;

		अगर (txqueue->tx_skbuff_dma[dma_desc])
			dma_unmap_single(priv->device,
					 txqueue->tx_skbuff_dma[dma_desc],
					 priv->hw->desc->get_tx_len(tdesc),
					 DMA_TO_DEVICE);

		dev_kमुक्त_skb_any(txqueue->tx_skbuff[dma_desc]);
		txqueue->tx_skbuff[dma_desc] = शून्य;
		txqueue->tx_skbuff_dma[dma_desc] = 0;
	पूर्ण
पूर्ण


अटल व्योम dma_मुक्त_tx_skbufs(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक queue_num;

	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
		काष्ठा sxgbe_tx_queue *tqueue = priv->txq[queue_num];
		tx_मुक्त_ring_skbufs(tqueue);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_dma_desc_resources(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक queue_num;
	पूर्णांक tx_rsize = priv->dma_tx_size;
	पूर्णांक rx_rsize = priv->dma_rx_size;

	/* Release the DMA TX buffers */
	dma_मुक्त_tx_skbufs(priv);

	/* Release the TX ring memory also */
	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
		मुक्त_tx_ring(priv->device, priv->txq[queue_num], tx_rsize);
	पूर्ण

	/* Release the RX ring memory also */
	SXGBE_FOR_EACH_QUEUE(SXGBE_RX_QUEUES, queue_num) अणु
		मुक्त_rx_ring(priv->device, priv->rxq[queue_num], rx_rsize);
	पूर्ण
पूर्ण

अटल पूर्णांक txring_mem_alloc(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक queue_num;

	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
		priv->txq[queue_num] = devm_kदो_स्मृति(priv->device,
						    माप(काष्ठा sxgbe_tx_queue), GFP_KERNEL);
		अगर (!priv->txq[queue_num])
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rxring_mem_alloc(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक queue_num;

	SXGBE_FOR_EACH_QUEUE(SXGBE_RX_QUEUES, queue_num) अणु
		priv->rxq[queue_num] = devm_kदो_स्मृति(priv->device,
						    माप(काष्ठा sxgbe_rx_queue), GFP_KERNEL);
		अगर (!priv->rxq[queue_num])
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  sxgbe_mtl_operation_mode - HW MTL operation mode
 *  @priv: driver निजी काष्ठाure
 *  Description: it sets the MTL operation mode: tx/rx MTL thresholds
 *  or Store-And-Forward capability.
 */
अटल व्योम sxgbe_mtl_operation_mode(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक queue_num;

	/* TX/RX threshold control */
	अगर (likely(priv->plat->क्रमce_sf_dma_mode)) अणु
		/* set TC mode क्रम TX QUEUES */
		SXGBE_FOR_EACH_QUEUE(priv->hw_cap.tx_mtl_queues, queue_num)
			priv->hw->mtl->set_tx_mtl_mode(priv->ioaddr, queue_num,
						       SXGBE_MTL_SFMODE);
		priv->tx_tc = SXGBE_MTL_SFMODE;

		/* set TC mode क्रम RX QUEUES */
		SXGBE_FOR_EACH_QUEUE(priv->hw_cap.rx_mtl_queues, queue_num)
			priv->hw->mtl->set_rx_mtl_mode(priv->ioaddr, queue_num,
						       SXGBE_MTL_SFMODE);
		priv->rx_tc = SXGBE_MTL_SFMODE;
	पूर्ण अन्यथा अगर (unlikely(priv->plat->क्रमce_thresh_dma_mode)) अणु
		/* set TC mode क्रम TX QUEUES */
		SXGBE_FOR_EACH_QUEUE(priv->hw_cap.tx_mtl_queues, queue_num)
			priv->hw->mtl->set_tx_mtl_mode(priv->ioaddr, queue_num,
						       priv->tx_tc);
		/* set TC mode क्रम RX QUEUES */
		SXGBE_FOR_EACH_QUEUE(priv->hw_cap.rx_mtl_queues, queue_num)
			priv->hw->mtl->set_rx_mtl_mode(priv->ioaddr, queue_num,
						       priv->rx_tc);
	पूर्ण अन्यथा अणु
		pr_err("ERROR: %s: Invalid TX threshold mode\n", __func__);
	पूर्ण
पूर्ण

/**
 * sxgbe_tx_queue_clean:
 * @tqueue: queue poपूर्णांकer
 * Description: it reclaims resources after transmission completes.
 */
अटल व्योम sxgbe_tx_queue_clean(काष्ठा sxgbe_tx_queue *tqueue)
अणु
	काष्ठा sxgbe_priv_data *priv = tqueue->priv_ptr;
	अचिन्हित पूर्णांक tx_rsize = priv->dma_tx_size;
	काष्ठा netdev_queue *dev_txq;
	u8 queue_no = tqueue->queue_no;

	dev_txq = netdev_get_tx_queue(priv->dev, queue_no);

	__netअगर_tx_lock(dev_txq, smp_processor_id());

	priv->xstats.tx_clean++;
	जबतक (tqueue->dirty_tx != tqueue->cur_tx) अणु
		अचिन्हित पूर्णांक entry = tqueue->dirty_tx % tx_rsize;
		काष्ठा sk_buff *skb = tqueue->tx_skbuff[entry];
		काष्ठा sxgbe_tx_norm_desc *p;

		p = tqueue->dma_tx + entry;

		/* Check अगर the descriptor is owned by the DMA. */
		अगर (priv->hw->desc->get_tx_owner(p))
			अवरोध;

		अगर (netअगर_msg_tx_करोne(priv))
			pr_debug("%s: curr %d, dirty %d\n",
				 __func__, tqueue->cur_tx, tqueue->dirty_tx);

		अगर (likely(tqueue->tx_skbuff_dma[entry])) अणु
			dma_unmap_single(priv->device,
					 tqueue->tx_skbuff_dma[entry],
					 priv->hw->desc->get_tx_len(p),
					 DMA_TO_DEVICE);
			tqueue->tx_skbuff_dma[entry] = 0;
		पूर्ण

		अगर (likely(skb)) अणु
			dev_kमुक्त_skb(skb);
			tqueue->tx_skbuff[entry] = शून्य;
		पूर्ण

		priv->hw->desc->release_tx_desc(p);

		tqueue->dirty_tx++;
	पूर्ण

	/* wake up queue */
	अगर (unlikely(netअगर_tx_queue_stopped(dev_txq) &&
	    sxgbe_tx_avail(tqueue, tx_rsize) > SXGBE_TX_THRESH(priv))) अणु
		अगर (netअगर_msg_tx_करोne(priv))
			pr_debug("%s: restart transmit\n", __func__);
		netअगर_tx_wake_queue(dev_txq);
	पूर्ण

	__netअगर_tx_unlock(dev_txq);
पूर्ण

/**
 * sxgbe_tx_clean:
 * @priv: driver निजी काष्ठाure
 * Description: it reclaims resources after transmission completes.
 */
अटल व्योम sxgbe_tx_all_clean(काष्ठा sxgbe_priv_data * स्थिर priv)
अणु
	u8 queue_num;

	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
		काष्ठा sxgbe_tx_queue *tqueue = priv->txq[queue_num];

		sxgbe_tx_queue_clean(tqueue);
	पूर्ण

	अगर ((priv->eee_enabled) && (!priv->tx_path_in_lpi_mode)) अणु
		sxgbe_enable_eee_mode(priv);
		mod_समयr(&priv->eee_ctrl_समयr, SXGBE_LPI_TIMER(eee_समयr));
	पूर्ण
पूर्ण

/**
 * sxgbe_restart_tx_queue: irq tx error mng function
 * @priv: driver निजी काष्ठाure
 * @queue_num: queue number
 * Description: it cleans the descriptors and restarts the transmission
 * in हाल of errors.
 */
अटल व्योम sxgbe_restart_tx_queue(काष्ठा sxgbe_priv_data *priv, पूर्णांक queue_num)
अणु
	काष्ठा sxgbe_tx_queue *tx_ring = priv->txq[queue_num];
	काष्ठा netdev_queue *dev_txq = netdev_get_tx_queue(priv->dev,
							   queue_num);

	/* stop the queue */
	netअगर_tx_stop_queue(dev_txq);

	/* stop the tx dma */
	priv->hw->dma->stop_tx_queue(priv->ioaddr, queue_num);

	/* मुक्त the skbuffs of the ring */
	tx_मुक्त_ring_skbufs(tx_ring);

	/* initialise counters */
	tx_ring->cur_tx = 0;
	tx_ring->dirty_tx = 0;

	/* start the tx dma */
	priv->hw->dma->start_tx_queue(priv->ioaddr, queue_num);

	priv->dev->stats.tx_errors++;

	/* wakeup the queue */
	netअगर_tx_wake_queue(dev_txq);
पूर्ण

/**
 * sxgbe_reset_all_tx_queues: irq tx error mng function
 * @priv: driver निजी काष्ठाure
 * Description: it cleans all the descriptors and
 * restarts the transmission on all queues in हाल of errors.
 */
अटल व्योम sxgbe_reset_all_tx_queues(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक queue_num;

	/* On TX समयout of net device, resetting of all queues
	 * may not be proper way, revisit this later अगर needed
	 */
	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num)
		sxgbe_restart_tx_queue(priv, queue_num);
पूर्ण

/**
 * sxgbe_get_hw_features: get XMAC capabilities from the HW cap. रेजिस्टर.
 * @priv: driver निजी काष्ठाure
 * Description:
 *  new GMAC chip generations have a new रेजिस्टर to indicate the
 *  presence of the optional feature/functions.
 *  This can be also used to override the value passed through the
 *  platक्रमm and necessary क्रम old MAC10/100 and GMAC chips.
 */
अटल पूर्णांक sxgbe_get_hw_features(काष्ठा sxgbe_priv_data * स्थिर priv)
अणु
	पूर्णांक rval = 0;
	काष्ठा sxgbe_hw_features *features = &priv->hw_cap;

	/* Read First Capability Register CAP[0] */
	rval = priv->hw->mac->get_hw_feature(priv->ioaddr, 0);
	अगर (rval) अणु
		features->pmt_remote_wake_up =
			SXGBE_HW_FEAT_PMT_TEMOTE_WOP(rval);
		features->pmt_magic_frame = SXGBE_HW_FEAT_PMT_MAGIC_PKT(rval);
		features->aसमय_stamp = SXGBE_HW_FEAT_IEEE1500_2008(rval);
		features->tx_csum_offload =
			SXGBE_HW_FEAT_TX_CSUM_OFFLOAD(rval);
		features->rx_csum_offload =
			SXGBE_HW_FEAT_RX_CSUM_OFFLOAD(rval);
		features->multi_macaddr = SXGBE_HW_FEAT_MACADDR_COUNT(rval);
		features->tstamp_srcselect = SXGBE_HW_FEAT_TSTMAP_SRC(rval);
		features->sa_vlan_insert = SXGBE_HW_FEAT_SRCADDR_VLAN(rval);
		features->eee = SXGBE_HW_FEAT_EEE(rval);
	पूर्ण

	/* Read First Capability Register CAP[1] */
	rval = priv->hw->mac->get_hw_feature(priv->ioaddr, 1);
	अगर (rval) अणु
		features->rxfअगरo_size = SXGBE_HW_FEAT_RX_FIFO_SIZE(rval);
		features->txfअगरo_size = SXGBE_HW_FEAT_TX_FIFO_SIZE(rval);
		features->atsपंचांगap_hword = SXGBE_HW_FEAT_TX_FIFO_SIZE(rval);
		features->dcb_enable = SXGBE_HW_FEAT_DCB(rval);
		features->splithead_enable = SXGBE_HW_FEAT_SPLIT_HDR(rval);
		features->tcpseg_offload = SXGBE_HW_FEAT_TSO(rval);
		features->debug_mem = SXGBE_HW_FEAT_DEBUG_MEM_IFACE(rval);
		features->rss_enable = SXGBE_HW_FEAT_RSS(rval);
		features->hash_tsize = SXGBE_HW_FEAT_HASH_TABLE_SIZE(rval);
		features->l3l4_filer_size = SXGBE_HW_FEAT_L3L4_FILTER_NUM(rval);
	पूर्ण

	/* Read First Capability Register CAP[2] */
	rval = priv->hw->mac->get_hw_feature(priv->ioaddr, 2);
	अगर (rval) अणु
		features->rx_mtl_queues = SXGBE_HW_FEAT_RX_MTL_QUEUES(rval);
		features->tx_mtl_queues = SXGBE_HW_FEAT_TX_MTL_QUEUES(rval);
		features->rx_dma_channels = SXGBE_HW_FEAT_RX_DMA_CHANNELS(rval);
		features->tx_dma_channels = SXGBE_HW_FEAT_TX_DMA_CHANNELS(rval);
		features->pps_output_count = SXGBE_HW_FEAT_PPS_OUTPUTS(rval);
		features->aux_input_count = SXGBE_HW_FEAT_AUX_SNAPSHOTS(rval);
	पूर्ण

	वापस rval;
पूर्ण

/**
 * sxgbe_check_ether_addr: check अगर the MAC addr is valid
 * @priv: driver निजी काष्ठाure
 * Description:
 * it is to verअगरy अगर the MAC address is valid, in हाल of failures it
 * generates a अक्रमom MAC address
 */
अटल व्योम sxgbe_check_ether_addr(काष्ठा sxgbe_priv_data *priv)
अणु
	अगर (!is_valid_ether_addr(priv->dev->dev_addr)) अणु
		priv->hw->mac->get_umac_addr((व्योम __iomem *)
					     priv->ioaddr,
					     priv->dev->dev_addr, 0);
		अगर (!is_valid_ether_addr(priv->dev->dev_addr))
			eth_hw_addr_अक्रमom(priv->dev);
	पूर्ण
	dev_info(priv->device, "device MAC address %pM\n",
		 priv->dev->dev_addr);
पूर्ण

/**
 * sxgbe_init_dma_engine: DMA init.
 * @priv: driver निजी काष्ठाure
 * Description:
 * It inits the DMA invoking the specअगरic SXGBE callback.
 * Some DMA parameters can be passed from the platक्रमm;
 * in हाल of these are not passed a शेष is kept क्रम the MAC or GMAC.
 */
अटल पूर्णांक sxgbe_init_dma_engine(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक pbl = DEFAULT_DMA_PBL, fixed_burst = 0, burst_map = 0;
	पूर्णांक queue_num;

	अगर (priv->plat->dma_cfg) अणु
		pbl = priv->plat->dma_cfg->pbl;
		fixed_burst = priv->plat->dma_cfg->fixed_burst;
		burst_map = priv->plat->dma_cfg->burst_map;
	पूर्ण

	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num)
		priv->hw->dma->cha_init(priv->ioaddr, queue_num,
					fixed_burst, pbl,
					(priv->txq[queue_num])->dma_tx_phy,
					(priv->rxq[queue_num])->dma_rx_phy,
					priv->dma_tx_size, priv->dma_rx_size);

	वापस priv->hw->dma->init(priv->ioaddr, fixed_burst, burst_map);
पूर्ण

/**
 * sxgbe_init_mtl_engine: MTL init.
 * @priv: driver निजी काष्ठाure
 * Description:
 * It inits the MTL invoking the specअगरic SXGBE callback.
 */
अटल व्योम sxgbe_init_mtl_engine(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक queue_num;

	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
		priv->hw->mtl->mtl_set_txfअगरosize(priv->ioaddr, queue_num,
						  priv->hw_cap.tx_mtl_qsize);
		priv->hw->mtl->mtl_enable_txqueue(priv->ioaddr, queue_num);
	पूर्ण
पूर्ण

/**
 * sxgbe_disable_mtl_engine: MTL disable.
 * @priv: driver निजी काष्ठाure
 * Description:
 * It disables the MTL queues by invoking the specअगरic SXGBE callback.
 */
अटल व्योम sxgbe_disable_mtl_engine(काष्ठा sxgbe_priv_data *priv)
अणु
	पूर्णांक queue_num;

	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num)
		priv->hw->mtl->mtl_disable_txqueue(priv->ioaddr, queue_num);
पूर्ण


/**
 * sxgbe_tx_समयr: mitigation sw समयr क्रम tx.
 * @t: समयr poपूर्णांकer
 * Description:
 * This is the समयr handler to directly invoke the sxgbe_tx_clean.
 */
अटल व्योम sxgbe_tx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sxgbe_tx_queue *p = from_समयr(p, t, txसमयr);
	sxgbe_tx_queue_clean(p);
पूर्ण

/**
 * sxgbe_init_tx_coalesce: init tx mitigation options.
 * @priv: driver निजी काष्ठाure
 * Description:
 * This inits the transmit coalesce parameters: i.e. समयr rate,
 * समयr handler and शेष threshold used क्रम enabling the
 * पूर्णांकerrupt on completion bit.
 */
अटल व्योम sxgbe_tx_init_coalesce(काष्ठा sxgbe_priv_data *priv)
अणु
	u8 queue_num;

	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
		काष्ठा sxgbe_tx_queue *p = priv->txq[queue_num];
		p->tx_coal_frames =  SXGBE_TX_FRAMES;
		p->tx_coal_समयr = SXGBE_COAL_TX_TIMER;
		समयr_setup(&p->txसमयr, sxgbe_tx_समयr, 0);
		p->txसमयr.expires = SXGBE_COAL_TIMER(p->tx_coal_समयr);
		add_समयr(&p->txसमयr);
	पूर्ण
पूर्ण

अटल व्योम sxgbe_tx_del_समयr(काष्ठा sxgbe_priv_data *priv)
अणु
	u8 queue_num;

	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
		काष्ठा sxgbe_tx_queue *p = priv->txq[queue_num];
		del_समयr_sync(&p->txसमयr);
	पूर्ण
पूर्ण

/**
 *  sxgbe_खोलो - खोलो entry poपूर्णांक of the driver
 *  @dev : poपूर्णांकer to the device काष्ठाure.
 *  Description:
 *  This function is the खोलो entry poपूर्णांक of the driver.
 *  Return value:
 *  0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *  file on failure.
 */
अटल पूर्णांक sxgbe_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	पूर्णांक ret, queue_num;

	clk_prepare_enable(priv->sxgbe_clk);

	sxgbe_check_ether_addr(priv);

	/* Init the phy */
	ret = sxgbe_init_phy(dev);
	अगर (ret) अणु
		netdev_err(dev, "%s: Cannot attach to PHY (error: %d)\n",
			   __func__, ret);
		जाओ phy_error;
	पूर्ण

	/* Create and initialize the TX/RX descriptors chains. */
	priv->dma_tx_size = SXGBE_ALIGN(DMA_TX_SIZE);
	priv->dma_rx_size = SXGBE_ALIGN(DMA_RX_SIZE);
	priv->dma_buf_sz = SXGBE_ALIGN(DMA_BUFFER_SIZE);
	priv->tx_tc = TC_DEFAULT;
	priv->rx_tc = TC_DEFAULT;
	init_dma_desc_rings(dev);

	/* DMA initialization and SW reset */
	ret = sxgbe_init_dma_engine(priv);
	अगर (ret < 0) अणु
		netdev_err(dev, "%s: DMA initialization failed\n", __func__);
		जाओ init_error;
	पूर्ण

	/*  MTL initialization */
	sxgbe_init_mtl_engine(priv);

	/* Copy the MAC addr पूर्णांकo the HW  */
	priv->hw->mac->set_umac_addr(priv->ioaddr, dev->dev_addr, 0);

	/* Initialize the MAC Core */
	priv->hw->mac->core_init(priv->ioaddr);
	SXGBE_FOR_EACH_QUEUE(SXGBE_RX_QUEUES, queue_num) अणु
		priv->hw->mac->enable_rxqueue(priv->ioaddr, queue_num);
	पूर्ण

	/* Request the IRQ lines */
	ret = devm_request_irq(priv->device, priv->irq, sxgbe_common_पूर्णांकerrupt,
			       IRQF_SHARED, dev->name, dev);
	अगर (unlikely(ret < 0)) अणु
		netdev_err(dev, "%s: ERROR: allocating the IRQ %d (error: %d)\n",
			   __func__, priv->irq, ret);
		जाओ init_error;
	पूर्ण

	/* If the LPI irq is dअगरferent from the mac irq
	 * रेजिस्टर a dedicated handler
	 */
	अगर (priv->lpi_irq != dev->irq) अणु
		ret = devm_request_irq(priv->device, priv->lpi_irq,
				       sxgbe_common_पूर्णांकerrupt,
				       IRQF_SHARED, dev->name, dev);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(dev, "%s: ERROR: allocating the LPI IRQ %d (%d)\n",
				   __func__, priv->lpi_irq, ret);
			जाओ init_error;
		पूर्ण
	पूर्ण

	/* Request TX DMA irq lines */
	SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
		ret = devm_request_irq(priv->device,
				       (priv->txq[queue_num])->irq_no,
				       sxgbe_tx_पूर्णांकerrupt, 0,
				       dev->name, priv->txq[queue_num]);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(dev, "%s: ERROR: allocating TX IRQ %d (error: %d)\n",
				   __func__, priv->irq, ret);
			जाओ init_error;
		पूर्ण
	पूर्ण

	/* Request RX DMA irq lines */
	SXGBE_FOR_EACH_QUEUE(SXGBE_RX_QUEUES, queue_num) अणु
		ret = devm_request_irq(priv->device,
				       (priv->rxq[queue_num])->irq_no,
				       sxgbe_rx_पूर्णांकerrupt, 0,
				       dev->name, priv->rxq[queue_num]);
		अगर (unlikely(ret < 0)) अणु
			netdev_err(dev, "%s: ERROR: allocating TX IRQ %d (error: %d)\n",
				   __func__, priv->irq, ret);
			जाओ init_error;
		पूर्ण
	पूर्ण

	/* Enable the MAC Rx/Tx */
	priv->hw->mac->enable_tx(priv->ioaddr, true);
	priv->hw->mac->enable_rx(priv->ioaddr, true);

	/* Set the HW DMA mode and the COE */
	sxgbe_mtl_operation_mode(priv);

	/* Extra statistics */
	स_रखो(&priv->xstats, 0, माप(काष्ठा sxgbe_extra_stats));

	priv->xstats.tx_threshold = priv->tx_tc;
	priv->xstats.rx_threshold = priv->rx_tc;

	/* Start the ball rolling... */
	netdev_dbg(dev, "DMA RX/TX processes started...\n");
	priv->hw->dma->start_tx(priv->ioaddr, SXGBE_TX_QUEUES);
	priv->hw->dma->start_rx(priv->ioaddr, SXGBE_RX_QUEUES);

	अगर (dev->phydev)
		phy_start(dev->phydev);

	/* initialise TX coalesce parameters */
	sxgbe_tx_init_coalesce(priv);

	अगर ((priv->use_riwt) && (priv->hw->dma->rx_watchकरोg)) अणु
		priv->rx_riwt = SXGBE_MAX_DMA_RIWT;
		priv->hw->dma->rx_watchकरोg(priv->ioaddr, SXGBE_MAX_DMA_RIWT);
	पूर्ण

	priv->tx_lpi_समयr = SXGBE_DEFAULT_LPI_TIMER;
	priv->eee_enabled = sxgbe_eee_init(priv);

	napi_enable(&priv->napi);
	netअगर_start_queue(dev);

	वापस 0;

init_error:
	मुक्त_dma_desc_resources(priv);
	अगर (dev->phydev)
		phy_disconnect(dev->phydev);
phy_error:
	clk_disable_unprepare(priv->sxgbe_clk);

	वापस ret;
पूर्ण

/**
 *  sxgbe_release - बंद entry poपूर्णांक of the driver
 *  @dev : device poपूर्णांकer.
 *  Description:
 *  This is the stop entry poपूर्णांक of the driver.
 */
अटल पूर्णांक sxgbe_release(काष्ठा net_device *dev)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);

	अगर (priv->eee_enabled)
		del_समयr_sync(&priv->eee_ctrl_समयr);

	/* Stop and disconnect the PHY */
	अगर (dev->phydev) अणु
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
	पूर्ण

	netअगर_tx_stop_all_queues(dev);

	napi_disable(&priv->napi);

	/* delete TX समयrs */
	sxgbe_tx_del_समयr(priv);

	/* Stop TX/RX DMA and clear the descriptors */
	priv->hw->dma->stop_tx(priv->ioaddr, SXGBE_TX_QUEUES);
	priv->hw->dma->stop_rx(priv->ioaddr, SXGBE_RX_QUEUES);

	/* disable MTL queue */
	sxgbe_disable_mtl_engine(priv);

	/* Release and मुक्त the Rx/Tx resources */
	मुक्त_dma_desc_resources(priv);

	/* Disable the MAC Rx/Tx */
	priv->hw->mac->enable_tx(priv->ioaddr, false);
	priv->hw->mac->enable_rx(priv->ioaddr, false);

	clk_disable_unprepare(priv->sxgbe_clk);

	वापस 0;
पूर्ण
/* Prepare first Tx descriptor क्रम करोing TSO operation */
अटल व्योम sxgbe_tso_prepare(काष्ठा sxgbe_priv_data *priv,
			      काष्ठा sxgbe_tx_norm_desc *first_desc,
			      काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक total_hdr_len, tcp_hdr_len;

	/* Write first Tx descriptor with appropriate value */
	tcp_hdr_len = tcp_hdrlen(skb);
	total_hdr_len = skb_transport_offset(skb) + tcp_hdr_len;

	first_desc->tdes01 = dma_map_single(priv->device, skb->data,
					    total_hdr_len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(priv->device, first_desc->tdes01))
		pr_err("%s: TX dma mapping failed!!\n", __func__);

	first_desc->tdes23.tx_rd_des23.first_desc = 1;
	priv->hw->desc->tx_desc_enable_tse(first_desc, 1, total_hdr_len,
					   tcp_hdr_len,
					   skb->len - total_hdr_len);
पूर्ण

/**
 *  sxgbe_xmit: Tx entry poपूर्णांक of the driver
 *  @skb : the socket buffer
 *  @dev : device poपूर्णांकer
 *  Description : this is the tx entry poपूर्णांक of the driver.
 *  It programs the chain or the ring and supports oversized frames
 *  and SG feature.
 */
अटल netdev_tx_t sxgbe_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक entry, frag_num;
	पूर्णांक cksum_flag = 0;
	काष्ठा netdev_queue *dev_txq;
	अचिन्हित txq_index = skb_get_queue_mapping(skb);
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक tx_rsize = priv->dma_tx_size;
	काष्ठा sxgbe_tx_queue *tqueue = priv->txq[txq_index];
	काष्ठा sxgbe_tx_norm_desc *tx_desc, *first_desc;
	काष्ठा sxgbe_tx_ctxt_desc *ctxt_desc = शून्य;
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक no_pagedlen = skb_headlen(skb);
	पूर्णांक is_jumbo = 0;
	u16 cur_mss = skb_shinfo(skb)->gso_size;
	u32 ctxt_desc_req = 0;

	/* get the TX queue handle */
	dev_txq = netdev_get_tx_queue(dev, txq_index);

	अगर (unlikely(skb_is_gso(skb) && tqueue->prev_mss != cur_mss))
		ctxt_desc_req = 1;

	अगर (unlikely(skb_vlan_tag_present(skb) ||
		     ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
		      tqueue->hwts_tx_en)))
		ctxt_desc_req = 1;

	अगर (priv->tx_path_in_lpi_mode)
		sxgbe_disable_eee_mode(priv);

	अगर (unlikely(sxgbe_tx_avail(tqueue, tx_rsize) < nr_frags + 1)) अणु
		अगर (!netअगर_tx_queue_stopped(dev_txq)) अणु
			netअगर_tx_stop_queue(dev_txq);
			netdev_err(dev, "%s: Tx Ring is full when %d queue is awake\n",
				   __func__, txq_index);
		पूर्ण
		वापस NETDEV_TX_BUSY;
	पूर्ण

	entry = tqueue->cur_tx % tx_rsize;
	tx_desc = tqueue->dma_tx + entry;

	first_desc = tx_desc;
	अगर (ctxt_desc_req)
		ctxt_desc = (काष्ठा sxgbe_tx_ctxt_desc *)first_desc;

	/* save the skb address */
	tqueue->tx_skbuff[entry] = skb;

	अगर (!is_jumbo) अणु
		अगर (likely(skb_is_gso(skb))) अणु
			/* TSO support */
			अगर (unlikely(tqueue->prev_mss != cur_mss)) अणु
				priv->hw->desc->tx_ctxt_desc_set_mss(
						ctxt_desc, cur_mss);
				priv->hw->desc->tx_ctxt_desc_set_tcmssv(
						ctxt_desc);
				priv->hw->desc->tx_ctxt_desc_reset_ostc(
						ctxt_desc);
				priv->hw->desc->tx_ctxt_desc_set_ctxt(
						ctxt_desc);
				priv->hw->desc->tx_ctxt_desc_set_owner(
						ctxt_desc);

				entry = (++tqueue->cur_tx) % tx_rsize;
				first_desc = tqueue->dma_tx + entry;

				tqueue->prev_mss = cur_mss;
			पूर्ण
			sxgbe_tso_prepare(priv, first_desc, skb);
		पूर्ण अन्यथा अणु
			tx_desc->tdes01 = dma_map_single(priv->device,
							 skb->data, no_pagedlen, DMA_TO_DEVICE);
			अगर (dma_mapping_error(priv->device, tx_desc->tdes01))
				netdev_err(dev, "%s: TX dma mapping failed!!\n",
					   __func__);

			priv->hw->desc->prepare_tx_desc(tx_desc, 1, no_pagedlen,
							no_pagedlen, cksum_flag);
		पूर्ण
	पूर्ण

	क्रम (frag_num = 0; frag_num < nr_frags; frag_num++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[frag_num];
		पूर्णांक len = skb_frag_size(frag);

		entry = (++tqueue->cur_tx) % tx_rsize;
		tx_desc = tqueue->dma_tx + entry;
		tx_desc->tdes01 = skb_frag_dma_map(priv->device, frag, 0, len,
						   DMA_TO_DEVICE);

		tqueue->tx_skbuff_dma[entry] = tx_desc->tdes01;
		tqueue->tx_skbuff[entry] = शून्य;

		/* prepare the descriptor */
		priv->hw->desc->prepare_tx_desc(tx_desc, 0, len,
						len, cksum_flag);
		/* memory barrier to flush descriptor */
		wmb();

		/* set the owner */
		priv->hw->desc->set_tx_owner(tx_desc);
	पूर्ण

	/* बंद the descriptors */
	priv->hw->desc->बंद_tx_desc(tx_desc);

	/* memory barrier to flush descriptor */
	wmb();

	tqueue->tx_count_frames += nr_frags + 1;
	अगर (tqueue->tx_count_frames > tqueue->tx_coal_frames) अणु
		priv->hw->desc->clear_tx_ic(tx_desc);
		priv->xstats.tx_reset_ic_bit++;
		mod_समयr(&tqueue->txसमयr,
			  SXGBE_COAL_TIMER(tqueue->tx_coal_समयr));
	पूर्ण अन्यथा अणु
		tqueue->tx_count_frames = 0;
	पूर्ण

	/* set owner क्रम first desc */
	priv->hw->desc->set_tx_owner(first_desc);

	/* memory barrier to flush descriptor */
	wmb();

	tqueue->cur_tx++;

	/* display current ring */
	netअगर_dbg(priv, pktdata, dev, "%s: curr %d dirty=%d entry=%d, first=%p, nfrags=%d\n",
		  __func__, tqueue->cur_tx % tx_rsize,
		  tqueue->dirty_tx % tx_rsize, entry,
		  first_desc, nr_frags);

	अगर (unlikely(sxgbe_tx_avail(tqueue, tx_rsize) <= (MAX_SKB_FRAGS + 1))) अणु
		netअगर_dbg(priv, hw, dev, "%s: stop transmitted packets\n",
			  __func__);
		netअगर_tx_stop_queue(dev_txq);
	पूर्ण

	dev->stats.tx_bytes += skb->len;

	अगर (unlikely((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
		     tqueue->hwts_tx_en)) अणु
		/* declare that device is करोing बारtamping */
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		priv->hw->desc->tx_enable_tstamp(first_desc);
	पूर्ण

	skb_tx_बारtamp(skb);

	priv->hw->dma->enable_dma_transmission(priv->ioaddr, txq_index);

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * sxgbe_rx_refill: refill used skb pपुनः_स्मृतिated buffers
 * @priv: driver निजी काष्ठाure
 * Description : this is to पुनः_स्मृतिate the skb क्रम the reception process
 * that is based on zero-copy.
 */
अटल व्योम sxgbe_rx_refill(काष्ठा sxgbe_priv_data *priv)
अणु
	अचिन्हित पूर्णांक rxsize = priv->dma_rx_size;
	पूर्णांक bfsize = priv->dma_buf_sz;
	u8 qnum = priv->cur_rx_qnum;

	क्रम (; priv->rxq[qnum]->cur_rx - priv->rxq[qnum]->dirty_rx > 0;
	     priv->rxq[qnum]->dirty_rx++) अणु
		अचिन्हित पूर्णांक entry = priv->rxq[qnum]->dirty_rx % rxsize;
		काष्ठा sxgbe_rx_norm_desc *p;

		p = priv->rxq[qnum]->dma_rx + entry;

		अगर (likely(priv->rxq[qnum]->rx_skbuff[entry] == शून्य)) अणु
			काष्ठा sk_buff *skb;

			skb = netdev_alloc_skb_ip_align(priv->dev, bfsize);

			अगर (unlikely(skb == शून्य))
				अवरोध;

			priv->rxq[qnum]->rx_skbuff[entry] = skb;
			priv->rxq[qnum]->rx_skbuff_dma[entry] =
				dma_map_single(priv->device, skb->data, bfsize,
					       DMA_FROM_DEVICE);

			p->rdes23.rx_rd_des23.buf2_addr =
				priv->rxq[qnum]->rx_skbuff_dma[entry];
		पूर्ण

		/* Added memory barrier क्रम RX descriptor modअगरication */
		wmb();
		priv->hw->desc->set_rx_owner(p);
		priv->hw->desc->set_rx_पूर्णांक_on_com(p);
		/* Added memory barrier क्रम RX descriptor modअगरication */
		wmb();
	पूर्ण
पूर्ण

/**
 * sxgbe_rx: receive the frames from the remote host
 * @priv: driver निजी काष्ठाure
 * @limit: napi bugget.
 * Description :  this the function called by the napi poll method.
 * It माला_लो all the frames inside the ring.
 */
अटल पूर्णांक sxgbe_rx(काष्ठा sxgbe_priv_data *priv, पूर्णांक limit)
अणु
	u8 qnum = priv->cur_rx_qnum;
	अचिन्हित पूर्णांक rxsize = priv->dma_rx_size;
	अचिन्हित पूर्णांक entry = priv->rxq[qnum]->cur_rx;
	अचिन्हित पूर्णांक next_entry = 0;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक checksum;
	पूर्णांक status;

	जबतक (count < limit) अणु
		काष्ठा sxgbe_rx_norm_desc *p;
		काष्ठा sk_buff *skb;
		पूर्णांक frame_len;

		p = priv->rxq[qnum]->dma_rx + entry;

		अगर (priv->hw->desc->get_rx_owner(p))
			अवरोध;

		count++;

		next_entry = (++priv->rxq[qnum]->cur_rx) % rxsize;
		prefetch(priv->rxq[qnum]->dma_rx + next_entry);

		/* Read the status of the incoming frame and also get checksum
		 * value based on whether it is enabled in SXGBE hardware or
		 * not.
		 */
		status = priv->hw->desc->rx_wbstatus(p, &priv->xstats,
						     &checksum);
		अगर (unlikely(status < 0)) अणु
			entry = next_entry;
			जारी;
		पूर्ण
		अगर (unlikely(!priv->rxcsum_insertion))
			checksum = CHECKSUM_NONE;

		skb = priv->rxq[qnum]->rx_skbuff[entry];

		अगर (unlikely(!skb))
			netdev_err(priv->dev, "rx descriptor is not consistent\n");

		prefetch(skb->data - NET_IP_ALIGN);
		priv->rxq[qnum]->rx_skbuff[entry] = शून्य;

		frame_len = priv->hw->desc->get_rx_frame_len(p);

		skb_put(skb, frame_len);

		skb->ip_summed = checksum;
		अगर (checksum == CHECKSUM_NONE)
			netअगर_receive_skb(skb);
		अन्यथा
			napi_gro_receive(&priv->napi, skb);

		entry = next_entry;
	पूर्ण

	sxgbe_rx_refill(priv);

	वापस count;
पूर्ण

/**
 *  sxgbe_poll - sxgbe poll method (NAPI)
 *  @napi : poपूर्णांकer to the napi काष्ठाure.
 *  @budget : maximum number of packets that the current CPU can receive from
 *	      all पूर्णांकerfaces.
 *  Description :
 *  To look at the incoming frames and clear the tx resources.
 */
अटल पूर्णांक sxgbe_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा sxgbe_priv_data *priv = container_of(napi,
						    काष्ठा sxgbe_priv_data, napi);
	पूर्णांक work_करोne = 0;
	u8 qnum = priv->cur_rx_qnum;

	priv->xstats.napi_poll++;
	/* first, clean the tx queues */
	sxgbe_tx_all_clean(priv);

	work_करोne = sxgbe_rx(priv, budget);
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		priv->hw->dma->enable_dma_irq(priv->ioaddr, qnum);
	पूर्ण

	वापस work_करोne;
पूर्ण

/**
 *  sxgbe_tx_समयout
 *  @dev : Poपूर्णांकer to net device काष्ठाure
 *  @txqueue: index of the hanging queue
 *  Description: this function is called when a packet transmission fails to
 *   complete within a reasonable समय. The driver will mark the error in the
 *   netdev काष्ठाure and arrange क्रम the device to be reset to a sane state
 *   in order to transmit a new packet.
 */
अटल व्योम sxgbe_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);

	sxgbe_reset_all_tx_queues(priv);
पूर्ण

/**
 *  sxgbe_common_पूर्णांकerrupt - मुख्य ISR
 *  @irq: पूर्णांकerrupt number.
 *  @dev_id: to pass the net device poपूर्णांकer.
 *  Description: this is the मुख्य driver पूर्णांकerrupt service routine.
 *  It calls the DMA ISR and also the core ISR to manage PMT, MMC, LPI
 *  पूर्णांकerrupts.
 */
अटल irqवापस_t sxgbe_common_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *netdev = (काष्ठा net_device *)dev_id;
	काष्ठा sxgbe_priv_data *priv = netdev_priv(netdev);
	पूर्णांक status;

	status = priv->hw->mac->host_irq_status(priv->ioaddr, &priv->xstats);
	/* For LPI we need to save the tx status */
	अगर (status & TX_ENTRY_LPI_MODE) अणु
		priv->xstats.tx_lpi_entry_n++;
		priv->tx_path_in_lpi_mode = true;
	पूर्ण
	अगर (status & TX_EXIT_LPI_MODE) अणु
		priv->xstats.tx_lpi_निकास_n++;
		priv->tx_path_in_lpi_mode = false;
	पूर्ण
	अगर (status & RX_ENTRY_LPI_MODE)
		priv->xstats.rx_lpi_entry_n++;
	अगर (status & RX_EXIT_LPI_MODE)
		priv->xstats.rx_lpi_निकास_n++;

	वापस IRQ_HANDLED;
पूर्ण

/**
 *  sxgbe_tx_पूर्णांकerrupt - TX DMA ISR
 *  @irq: पूर्णांकerrupt number.
 *  @dev_id: to pass the net device poपूर्णांकer.
 *  Description: this is the tx dma पूर्णांकerrupt service routine.
 */
अटल irqवापस_t sxgbe_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक status;
	काष्ठा sxgbe_tx_queue *txq = (काष्ठा sxgbe_tx_queue *)dev_id;
	काष्ठा sxgbe_priv_data *priv = txq->priv_ptr;

	/* get the channel status */
	status = priv->hw->dma->tx_dma_पूर्णांक_status(priv->ioaddr, txq->queue_no,
						  &priv->xstats);
	/* check क्रम normal path */
	अगर (likely((status & handle_tx)))
		napi_schedule(&priv->napi);

	/* check क्रम unrecoverable error */
	अगर (unlikely((status & tx_hard_error)))
		sxgbe_restart_tx_queue(priv, txq->queue_no);

	/* check क्रम TC configuration change */
	अगर (unlikely((status & tx_bump_tc) &&
		     (priv->tx_tc != SXGBE_MTL_SFMODE) &&
		     (priv->tx_tc < 512))) अणु
		/* step of TX TC is 32 till 128, otherwise 64 */
		priv->tx_tc += (priv->tx_tc < 128) ? 32 : 64;
		priv->hw->mtl->set_tx_mtl_mode(priv->ioaddr,
					       txq->queue_no, priv->tx_tc);
		priv->xstats.tx_threshold = priv->tx_tc;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 *  sxgbe_rx_पूर्णांकerrupt - RX DMA ISR
 *  @irq: पूर्णांकerrupt number.
 *  @dev_id: to pass the net device poपूर्णांकer.
 *  Description: this is the rx dma पूर्णांकerrupt service routine.
 */
अटल irqवापस_t sxgbe_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक status;
	काष्ठा sxgbe_rx_queue *rxq = (काष्ठा sxgbe_rx_queue *)dev_id;
	काष्ठा sxgbe_priv_data *priv = rxq->priv_ptr;

	/* get the channel status */
	status = priv->hw->dma->rx_dma_पूर्णांक_status(priv->ioaddr, rxq->queue_no,
						  &priv->xstats);

	अगर (likely((status & handle_rx) && (napi_schedule_prep(&priv->napi)))) अणु
		priv->hw->dma->disable_dma_irq(priv->ioaddr, rxq->queue_no);
		__napi_schedule(&priv->napi);
	पूर्ण

	/* check क्रम TC configuration change */
	अगर (unlikely((status & rx_bump_tc) &&
		     (priv->rx_tc != SXGBE_MTL_SFMODE) &&
		     (priv->rx_tc < 128))) अणु
		/* step of TC is 32 */
		priv->rx_tc += 32;
		priv->hw->mtl->set_rx_mtl_mode(priv->ioaddr,
					       rxq->queue_no, priv->rx_tc);
		priv->xstats.rx_threshold = priv->rx_tc;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत u64 sxgbe_get_stat64(व्योम __iomem *ioaddr, पूर्णांक reg_lo, पूर्णांक reg_hi)
अणु
	u64 val = पढ़ोl(ioaddr + reg_lo);

	val |= ((u64)पढ़ोl(ioaddr + reg_hi)) << 32;

	वापस val;
पूर्ण


/*  sxgbe_get_stats64 - entry poपूर्णांक to see statistical inक्रमmation of device
 *  @dev : device poपूर्णांकer.
 *  @stats : poपूर्णांकer to hold all the statistical inक्रमmation of device.
 *  Description:
 *  This function is a driver entry poपूर्णांक whenever अगरconfig command माला_लो
 *  executed to see device statistics. Statistics are number of
 *  bytes sent or received, errors occurred etc.
 */
अटल व्योम sxgbe_get_stats64(काष्ठा net_device *dev,
			      काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = priv->ioaddr;
	u64 count;

	spin_lock(&priv->stats_lock);
	/* Freeze the counter रेजिस्टरs beक्रमe पढ़ोing value otherwise it may
	 * get updated by hardware जबतक we are पढ़ोing them
	 */
	ग_लिखोl(SXGBE_MMC_CTRL_CNT_FRZ, ioaddr + SXGBE_MMC_CTL_REG);

	stats->rx_bytes = sxgbe_get_stat64(ioaddr,
					   SXGBE_MMC_RXOCTETLO_GCNT_REG,
					   SXGBE_MMC_RXOCTETHI_GCNT_REG);

	stats->rx_packets = sxgbe_get_stat64(ioaddr,
					     SXGBE_MMC_RXFRAMELO_GBCNT_REG,
					     SXGBE_MMC_RXFRAMEHI_GBCNT_REG);

	stats->multicast = sxgbe_get_stat64(ioaddr,
					    SXGBE_MMC_RXMULTILO_GCNT_REG,
					    SXGBE_MMC_RXMULTIHI_GCNT_REG);

	stats->rx_crc_errors = sxgbe_get_stat64(ioaddr,
						SXGBE_MMC_RXCRCERRLO_REG,
						SXGBE_MMC_RXCRCERRHI_REG);

	stats->rx_length_errors = sxgbe_get_stat64(ioaddr,
						  SXGBE_MMC_RXLENERRLO_REG,
						  SXGBE_MMC_RXLENERRHI_REG);

	stats->rx_missed_errors = sxgbe_get_stat64(ioaddr,
						   SXGBE_MMC_RXFIFOOVERFLOWLO_GBCNT_REG,
						   SXGBE_MMC_RXFIFOOVERFLOWHI_GBCNT_REG);

	stats->tx_bytes = sxgbe_get_stat64(ioaddr,
					   SXGBE_MMC_TXOCTETLO_GCNT_REG,
					   SXGBE_MMC_TXOCTETHI_GCNT_REG);

	count = sxgbe_get_stat64(ioaddr, SXGBE_MMC_TXFRAMELO_GBCNT_REG,
				 SXGBE_MMC_TXFRAMEHI_GBCNT_REG);

	stats->tx_errors = sxgbe_get_stat64(ioaddr, SXGBE_MMC_TXFRAMELO_GCNT_REG,
					    SXGBE_MMC_TXFRAMEHI_GCNT_REG);
	stats->tx_errors = count - stats->tx_errors;
	stats->tx_packets = count;
	stats->tx_fअगरo_errors = sxgbe_get_stat64(ioaddr, SXGBE_MMC_TXUFLWLO_GBCNT_REG,
						 SXGBE_MMC_TXUFLWHI_GBCNT_REG);
	ग_लिखोl(0, ioaddr + SXGBE_MMC_CTL_REG);
	spin_unlock(&priv->stats_lock);
पूर्ण

/*  sxgbe_set_features - entry poपूर्णांक to set offload features of the device.
 *  @dev : device poपूर्णांकer.
 *  @features : features which are required to be set.
 *  Description:
 *  This function is a driver entry poपूर्णांक and called by Linux kernel whenever
 *  any device features are set or reset by user.
 *  Return value:
 *  This function वापसs 0 after setting or resetting device features.
 */
अटल पूर्णांक sxgbe_set_features(काष्ठा net_device *dev,
			      netdev_features_t features)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	netdev_features_t changed = dev->features ^ features;

	अगर (changed & NETIF_F_RXCSUM) अणु
		अगर (features & NETIF_F_RXCSUM) अणु
			priv->hw->mac->enable_rx_csum(priv->ioaddr);
			priv->rxcsum_insertion = true;
		पूर्ण अन्यथा अणु
			priv->hw->mac->disable_rx_csum(priv->ioaddr);
			priv->rxcsum_insertion = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*  sxgbe_change_mtu - entry poपूर्णांक to change MTU size क्रम the device.
 *  @dev : device poपूर्णांकer.
 *  @new_mtu : the new MTU size क्रम the device.
 *  Description: the Maximum Transfer Unit (MTU) is used by the network layer
 *  to drive packet transmission. Ethernet has an MTU of 1500 octets
 *  (ETH_DATA_LEN). This value can be changed with अगरconfig.
 *  Return value:
 *  0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *  file on failure.
 */
अटल पूर्णांक sxgbe_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	dev->mtu = new_mtu;

	अगर (!netअगर_running(dev))
		वापस 0;

	/* Recevice ring buffer size is needed to be set based on MTU. If MTU is
	 * changed then reinitilisation of the receive ring buffers need to be
	 * करोne. Hence bring पूर्णांकerface करोwn and bring पूर्णांकerface back up
	 */
	sxgbe_release(dev);
	वापस sxgbe_खोलो(dev);
पूर्ण

अटल व्योम sxgbe_set_umac_addr(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
				अचिन्हित पूर्णांक reg_n)
अणु
	अचिन्हित दीर्घ data;

	data = (addr[5] << 8) | addr[4];
	/* For MAC Addr रेजिस्टरs se have to set the Address Enable (AE)
	 * bit that has no effect on the High Reg 0 where the bit 31 (MO)
	 * is RO.
	 */
	ग_लिखोl(data | SXGBE_HI_REG_AE, ioaddr + SXGBE_ADDR_HIGH(reg_n));
	data = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	ग_लिखोl(data, ioaddr + SXGBE_ADDR_LOW(reg_n));
पूर्ण

/**
 * sxgbe_set_rx_mode - entry poपूर्णांक क्रम setting dअगरferent receive mode of
 * a device. unicast, multicast addressing
 * @dev : poपूर्णांकer to the device काष्ठाure
 * Description:
 * This function is a driver entry poपूर्णांक which माला_लो called by the kernel
 * whenever dअगरferent receive mode like unicast, multicast and promiscuous
 * must be enabled/disabled.
 * Return value:
 * व्योम.
 */
अटल व्योम sxgbe_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = (व्योम __iomem *)priv->ioaddr;
	अचिन्हित पूर्णांक value = 0;
	u32 mc_filter[2];
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक reg = 1;

	netdev_dbg(dev, "%s: # mcasts %d, # unicast %d\n",
		   __func__, netdev_mc_count(dev), netdev_uc_count(dev));

	अगर (dev->flags & IFF_PROMISC) अणु
		value = SXGBE_FRAME_FILTER_PR;

	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > SXGBE_HASH_TABLE_SIZE) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		value = SXGBE_FRAME_FILTER_PM;	/* pass all multi */
		ग_लिखोl(0xffffffff, ioaddr + SXGBE_HASH_HIGH);
		ग_लिखोl(0xffffffff, ioaddr + SXGBE_HASH_LOW);

	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		/* Hash filter क्रम multicast */
		value = SXGBE_FRAME_FILTER_HMC;

		स_रखो(mc_filter, 0, माप(mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			/* The upper 6 bits of the calculated CRC are used to
			 * index the contens of the hash table
			 */
			पूर्णांक bit_nr = bitrev32(~crc32_le(~0, ha->addr, 6)) >> 26;

			/* The most signअगरicant bit determines the रेजिस्टर to
			 * use (H/L) जबतक the other 5 bits determine the bit
			 * within the रेजिस्टर.
			 */
			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
		पूर्ण
		ग_लिखोl(mc_filter[0], ioaddr + SXGBE_HASH_LOW);
		ग_लिखोl(mc_filter[1], ioaddr + SXGBE_HASH_HIGH);
	पूर्ण

	/* Handle multiple unicast addresses (perfect filtering) */
	अगर (netdev_uc_count(dev) > SXGBE_MAX_PERFECT_ADDRESSES)
		/* Switch to promiscuous mode अगर more than 16 addrs
		 * are required
		 */
		value |= SXGBE_FRAME_FILTER_PR;
	अन्यथा अणु
		netdev_क्रम_each_uc_addr(ha, dev) अणु
			sxgbe_set_umac_addr(ioaddr, ha->addr, reg);
			reg++;
		पूर्ण
	पूर्ण
#अगर_घोषित FRAME_FILTER_DEBUG
	/* Enable Receive all mode (to debug filtering_fail errors) */
	value |= SXGBE_FRAME_FILTER_RA;
#पूर्ण_अगर
	ग_लिखोl(value, ioaddr + SXGBE_FRAME_FILTER);

	netdev_dbg(dev, "Filter: 0x%08x\n\tHash: HI 0x%08x, LO 0x%08x\n",
		   पढ़ोl(ioaddr + SXGBE_FRAME_FILTER),
		   पढ़ोl(ioaddr + SXGBE_HASH_HIGH),
		   पढ़ोl(ioaddr + SXGBE_HASH_LOW));
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * sxgbe_poll_controller - entry poपूर्णांक क्रम polling receive by device
 * @dev : poपूर्णांकer to the device काष्ठाure
 * Description:
 * This function is used by NETCONSOLE and other diagnostic tools
 * to allow network I/O with पूर्णांकerrupts disabled.
 * Return value:
 * Void.
 */
अटल व्योम sxgbe_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);

	disable_irq(priv->irq);
	sxgbe_rx_पूर्णांकerrupt(priv->irq, dev);
	enable_irq(priv->irq);
पूर्ण
#पूर्ण_अगर

/*  sxgbe_ioctl - Entry poपूर्णांक क्रम the Ioctl
 *  @dev: Device poपूर्णांकer.
 *  @rq: An IOCTL specefic काष्ठाure, that can contain a poपूर्णांकer to
 *  a proprietary काष्ठाure used to pass inक्रमmation to the driver.
 *  @cmd: IOCTL command
 *  Description:
 *  Currently it supports the phy_mii_ioctl(...) and HW समय stamping.
 */
अटल पूर्णांक sxgbe_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		ret = phy_करो_ioctl(dev, rq, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sxgbe_netdev_ops = अणु
	.nकरो_खोलो		= sxgbe_खोलो,
	.nकरो_start_xmit		= sxgbe_xmit,
	.nकरो_stop		= sxgbe_release,
	.nकरो_get_stats64	= sxgbe_get_stats64,
	.nकरो_change_mtu		= sxgbe_change_mtu,
	.nकरो_set_features	= sxgbe_set_features,
	.nकरो_set_rx_mode	= sxgbe_set_rx_mode,
	.nकरो_tx_समयout		= sxgbe_tx_समयout,
	.nकरो_करो_ioctl		= sxgbe_ioctl,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= sxgbe_poll_controller,
#पूर्ण_अगर
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

/* Get the hardware ops */
अटल व्योम sxgbe_get_ops(काष्ठा sxgbe_ops * स्थिर ops_ptr)
अणु
	ops_ptr->mac		= sxgbe_get_core_ops();
	ops_ptr->desc		= sxgbe_get_desc_ops();
	ops_ptr->dma		= sxgbe_get_dma_ops();
	ops_ptr->mtl		= sxgbe_get_mtl_ops();

	/* set the MDIO communication Address/Data regisers */
	ops_ptr->mii.addr	= SXGBE_MDIO_SCMD_ADD_REG;
	ops_ptr->mii.data	= SXGBE_MDIO_SCMD_DATA_REG;

	/* Assigning the शेष link settings
	 * no SXGBE defined शेष values to be set in रेजिस्टरs,
	 * so assigning as 0 क्रम port and duplex
	 */
	ops_ptr->link.port	= 0;
	ops_ptr->link.duplex	= 0;
	ops_ptr->link.speed	= SXGBE_SPEED_10G;
पूर्ण

/**
 *  sxgbe_hw_init - Init the GMAC device
 *  @priv: driver निजी काष्ठाure
 *  Description: this function checks the HW capability
 *  (अगर supported) and sets the driver's features.
 */
अटल पूर्णांक sxgbe_hw_init(काष्ठा sxgbe_priv_data * स्थिर priv)
अणु
	u32 ctrl_ids;

	priv->hw = kदो_स्मृति(माप(*priv->hw), GFP_KERNEL);
	अगर(!priv->hw)
		वापस -ENOMEM;

	/* get the hardware ops */
	sxgbe_get_ops(priv->hw);

	/* get the controller id */
	ctrl_ids = priv->hw->mac->get_controller_version(priv->ioaddr);
	priv->hw->ctrl_uid = (ctrl_ids & 0x00ff0000) >> 16;
	priv->hw->ctrl_id = (ctrl_ids & 0x000000ff);
	pr_info("user ID: 0x%x, Controller ID: 0x%x\n",
		priv->hw->ctrl_uid, priv->hw->ctrl_id);

	/* get the H/W features */
	अगर (!sxgbe_get_hw_features(priv))
		pr_info("Hardware features not found\n");

	अगर (priv->hw_cap.tx_csum_offload)
		pr_info("TX Checksum offload supported\n");

	अगर (priv->hw_cap.rx_csum_offload)
		pr_info("RX Checksum offload supported\n");

	वापस 0;
पूर्ण

अटल पूर्णांक sxgbe_sw_reset(व्योम __iomem *addr)
अणु
	पूर्णांक retry_count = 10;

	ग_लिखोl(SXGBE_DMA_SOFT_RESET, addr + SXGBE_DMA_MODE_REG);
	जबतक (retry_count--) अणु
		अगर (!(पढ़ोl(addr + SXGBE_DMA_MODE_REG) &
		      SXGBE_DMA_SOFT_RESET))
			अवरोध;
		mdelay(10);
	पूर्ण

	अगर (retry_count < 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण

/**
 * sxgbe_drv_probe
 * @device: device poपूर्णांकer
 * @plat_dat: platक्रमm data poपूर्णांकer
 * @addr: iobase memory address
 * Description: this is the मुख्य probe function used to
 * call the alloc_etherdev, allocate the priv काष्ठाure.
 */
काष्ठा sxgbe_priv_data *sxgbe_drv_probe(काष्ठा device *device,
					काष्ठा sxgbe_plat_data *plat_dat,
					व्योम __iomem *addr)
अणु
	काष्ठा sxgbe_priv_data *priv;
	काष्ठा net_device *ndev;
	पूर्णांक ret;
	u8 queue_num;

	ndev = alloc_etherdev_mqs(माप(काष्ठा sxgbe_priv_data),
				  SXGBE_TX_QUEUES, SXGBE_RX_QUEUES);
	अगर (!ndev)
		वापस शून्य;

	SET_NETDEV_DEV(ndev, device);

	priv = netdev_priv(ndev);
	priv->device = device;
	priv->dev = ndev;

	sxgbe_set_ethtool_ops(ndev);
	priv->plat = plat_dat;
	priv->ioaddr = addr;

	ret = sxgbe_sw_reset(priv->ioaddr);
	अगर (ret)
		जाओ error_मुक्त_netdev;

	/* Verअगरy driver arguments */
	sxgbe_verअगरy_args();

	/* Init MAC and get the capabilities */
	ret = sxgbe_hw_init(priv);
	अगर (ret)
		जाओ error_मुक्त_netdev;

	/* allocate memory resources क्रम Descriptor rings */
	ret = txring_mem_alloc(priv);
	अगर (ret)
		जाओ error_मुक्त_hw;

	ret = rxring_mem_alloc(priv);
	अगर (ret)
		जाओ error_मुक्त_hw;

	ndev->netdev_ops = &sxgbe_netdev_ops;

	ndev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_RXCSUM | NETIF_F_TSO | NETIF_F_TSO6 |
		NETIF_F_GRO;
	ndev->features |= ndev->hw_features | NETIF_F_HIGHDMA;
	ndev->watchकरोg_समयo = msecs_to_jअगरfies(TX_TIMEO);

	/* assign filtering support */
	ndev->priv_flags |= IFF_UNICAST_FLT;

	/* MTU range: 68 - 9000 */
	ndev->min_mtu = MIN_MTU;
	ndev->max_mtu = MAX_MTU;

	priv->msg_enable = netअगर_msg_init(debug, शेष_msg_level);

	/* Enable TCP segmentation offload क्रम all DMA channels */
	अगर (priv->hw_cap.tcpseg_offload) अणु
		SXGBE_FOR_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) अणु
			priv->hw->dma->enable_tso(priv->ioaddr, queue_num);
		पूर्ण
	पूर्ण

	/* Enable Rx checksum offload */
	अगर (priv->hw_cap.rx_csum_offload) अणु
		priv->hw->mac->enable_rx_csum(priv->ioaddr);
		priv->rxcsum_insertion = true;
	पूर्ण

	/* Initialise छोड़ो frame settings */
	priv->rx_छोड़ो = 1;
	priv->tx_छोड़ो = 1;

	/* Rx Watchकरोg is available, enable depend on platक्रमm data */
	अगर (!priv->plat->riwt_off) अणु
		priv->use_riwt = 1;
		pr_info("Enable RX Mitigation via HW Watchdog Timer\n");
	पूर्ण

	netअगर_napi_add(ndev, &priv->napi, sxgbe_poll, 64);

	spin_lock_init(&priv->stats_lock);

	priv->sxgbe_clk = clk_get(priv->device, SXGBE_RESOURCE_NAME);
	अगर (IS_ERR(priv->sxgbe_clk)) अणु
		netdev_warn(ndev, "%s: warning: cannot get CSR clock\n",
			    __func__);
		जाओ error_napi_del;
	पूर्ण

	/* If a specअगरic clk_csr value is passed from the platक्रमm
	 * this means that the CSR Clock Range selection cannot be
	 * changed at run-समय and it is fixed. Viceversa the driver'll try to
	 * set the MDC घड़ी dynamically according to the csr actual
	 * घड़ी input.
	 */
	अगर (!priv->plat->clk_csr)
		sxgbe_clk_csr_set(priv);
	अन्यथा
		priv->clk_csr = priv->plat->clk_csr;

	/* MDIO bus Registration */
	ret = sxgbe_mdio_रेजिस्टर(ndev);
	अगर (ret < 0) अणु
		netdev_dbg(ndev, "%s: MDIO bus (id: %d) registration failed\n",
			   __func__, priv->plat->bus_id);
		जाओ error_clk_put;
	पूर्ण

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		pr_err("%s: ERROR %i registering the device\n", __func__, ret);
		जाओ error_mdio_unरेजिस्टर;
	पूर्ण

	sxgbe_check_ether_addr(priv);

	वापस priv;

error_mdio_unरेजिस्टर:
	sxgbe_mdio_unरेजिस्टर(ndev);
error_clk_put:
	clk_put(priv->sxgbe_clk);
error_napi_del:
	netअगर_napi_del(&priv->napi);
error_मुक्त_hw:
	kमुक्त(priv->hw);
error_मुक्त_netdev:
	मुक्त_netdev(ndev);

	वापस शून्य;
पूर्ण

/**
 * sxgbe_drv_हटाओ
 * @ndev: net device poपूर्णांकer
 * Description: this function resets the TX/RX processes, disables the MAC RX/TX
 * changes the link status, releases the DMA descriptor rings.
 */
पूर्णांक sxgbe_drv_हटाओ(काष्ठा net_device *ndev)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(ndev);
	u8 queue_num;

	netdev_info(ndev, "%s: removing driver\n", __func__);

	SXGBE_FOR_EACH_QUEUE(SXGBE_RX_QUEUES, queue_num) अणु
		priv->hw->mac->disable_rxqueue(priv->ioaddr, queue_num);
	पूर्ण

	priv->hw->dma->stop_rx(priv->ioaddr, SXGBE_RX_QUEUES);
	priv->hw->dma->stop_tx(priv->ioaddr, SXGBE_TX_QUEUES);

	priv->hw->mac->enable_tx(priv->ioaddr, false);
	priv->hw->mac->enable_rx(priv->ioaddr, false);

	unरेजिस्टर_netdev(ndev);

	sxgbe_mdio_unरेजिस्टर(ndev);

	clk_put(priv->sxgbe_clk);

	netअगर_napi_del(&priv->napi);

	kमुक्त(priv->hw);

	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
पूर्णांक sxgbe_suspend(काष्ठा net_device *ndev)
अणु
	वापस 0;
पूर्ण

पूर्णांक sxgbe_resume(काष्ठा net_device *ndev)
अणु
	वापस 0;
पूर्ण

पूर्णांक sxgbe_मुक्तze(काष्ठा net_device *ndev)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक sxgbe_restore(काष्ठा net_device *ndev)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

/* Driver is configured as Platक्रमm driver */
अटल पूर्णांक __init sxgbe_init(व्योम)
अणु
	पूर्णांक ret;

	ret = sxgbe_रेजिस्टर_platक्रमm();
	अगर (ret)
		जाओ err;
	वापस 0;
err:
	pr_err("driver registration failed\n");
	वापस ret;
पूर्ण

अटल व्योम __निकास sxgbe_निकास(व्योम)
अणु
	sxgbe_unरेजिस्टर_platक्रमm();
पूर्ण

module_init(sxgbe_init);
module_निकास(sxgbe_निकास);

#अगर_अघोषित MODULE
अटल पूर्णांक __init sxgbe_cmdline_opt(अक्षर *str)
अणु
	अक्षर *opt;

	अगर (!str || !*str)
		वापस -EINVAL;
	जबतक ((opt = strsep(&str, ",")) != शून्य) अणु
		अगर (!म_भेदन(opt, "eee_timer:", 10)) अणु
			अगर (kstrtoपूर्णांक(opt + 10, 0, &eee_समयr))
				जाओ err;
		पूर्ण
	पूर्ण
	वापस 0;

err:
	pr_err("%s: ERROR broken module parameter conversion\n", __func__);
	वापस -EINVAL;
पूर्ण

__setup("sxgbeeth=", sxgbe_cmdline_opt);
#पूर्ण_अगर /* MODULE */



MODULE_DESCRIPTION("Samsung 10G/2.5G/1G Ethernet PLATFORM driver");

MODULE_PARM_DESC(debug, "Message Level (-1: default, 0: no output, 16: all)");
MODULE_PARM_DESC(eee_समयr, "EEE-LPI Default LS timer value");

MODULE_AUTHOR("Siva Reddy Kallam <siva.kallam@samsung.com>");
MODULE_AUTHOR("ByungHo An <bh74.an@samsung.com>");
MODULE_AUTHOR("Girish K S <ks.giri@samsung.com>");
MODULE_AUTHOR("Vipul Pandya <vipul.pandya@samsung.com>");

MODULE_LICENSE("GPL");
