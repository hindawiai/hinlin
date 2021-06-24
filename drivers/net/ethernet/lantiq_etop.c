<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *   Copyright (C) 2011 John Crispin <blogic@खोलोwrt.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/in.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/checksum.h>

#समावेश <lantiq_soc.h>
#समावेश <xway_dma.h>
#समावेश <lantiq_platक्रमm.h>

#घोषणा LTQ_ETOP_MDIO		0x11804
#घोषणा MDIO_REQUEST		0x80000000
#घोषणा MDIO_READ		0x40000000
#घोषणा MDIO_ADDR_MASK		0x1f
#घोषणा MDIO_ADDR_OFFSET	0x15
#घोषणा MDIO_REG_MASK		0x1f
#घोषणा MDIO_REG_OFFSET		0x10
#घोषणा MDIO_VAL_MASK		0xffff

#घोषणा PPE32_CGEN		0x800
#घोषणा LQ_PPE32_ENET_MAC_CFG	0x1840

#घोषणा LTQ_ETOP_ENETS0		0x11850
#घोषणा LTQ_ETOP_MAC_DA0	0x1186C
#घोषणा LTQ_ETOP_MAC_DA1	0x11870
#घोषणा LTQ_ETOP_CFG		0x16020
#घोषणा LTQ_ETOP_IGPLEN		0x16080

#घोषणा MAX_DMA_CHAN		0x8
#घोषणा MAX_DMA_CRC_LEN		0x4
#घोषणा MAX_DMA_DATA_LEN	0x600

#घोषणा ETOP_FTCU		BIT(28)
#घोषणा ETOP_MII_MASK		0xf
#घोषणा ETOP_MII_NORMAL		0xd
#घोषणा ETOP_MII_REVERSE	0xe
#घोषणा ETOP_PLEN_UNDER		0x40
#घोषणा ETOP_CGEN		0x800

/* use 2 अटल channels क्रम TX/RX */
#घोषणा LTQ_ETOP_TX_CHANNEL	1
#घोषणा LTQ_ETOP_RX_CHANNEL	6
#घोषणा IS_TX(x)		(x == LTQ_ETOP_TX_CHANNEL)
#घोषणा IS_RX(x)		(x == LTQ_ETOP_RX_CHANNEL)

#घोषणा ltq_etop_r32(x)		ltq_r32(ltq_etop_membase + (x))
#घोषणा ltq_etop_w32(x, y)	ltq_w32(x, ltq_etop_membase + (y))
#घोषणा ltq_etop_w32_mask(x, y, z)	\
		ltq_w32_mask(x, y, ltq_etop_membase + (z))

#घोषणा DRV_VERSION	"1.0"

अटल व्योम __iomem *ltq_etop_membase;

काष्ठा ltq_etop_chan अणु
	पूर्णांक idx;
	पूर्णांक tx_मुक्त;
	काष्ठा net_device *netdev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा ltq_dma_channel dma;
	काष्ठा sk_buff *skb[LTQ_DESC_NUM];
पूर्ण;

काष्ठा ltq_etop_priv अणु
	काष्ठा net_device *netdev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा ltq_eth_data *pldata;
	काष्ठा resource *res;

	काष्ठा mii_bus *mii_bus;

	काष्ठा ltq_etop_chan ch[MAX_DMA_CHAN];
	पूर्णांक tx_मुक्त[MAX_DMA_CHAN >> 1];

	spinlock_t lock;
पूर्ण;

अटल पूर्णांक
ltq_etop_alloc_skb(काष्ठा ltq_etop_chan *ch)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(ch->netdev);

	ch->skb[ch->dma.desc] = netdev_alloc_skb(ch->netdev, MAX_DMA_DATA_LEN);
	अगर (!ch->skb[ch->dma.desc])
		वापस -ENOMEM;
	ch->dma.desc_base[ch->dma.desc].addr = dma_map_single(&priv->pdev->dev,
		ch->skb[ch->dma.desc]->data, MAX_DMA_DATA_LEN,
		DMA_FROM_DEVICE);
	ch->dma.desc_base[ch->dma.desc].addr =
		CPHYSADDR(ch->skb[ch->dma.desc]->data);
	ch->dma.desc_base[ch->dma.desc].ctl =
		LTQ_DMA_OWN | LTQ_DMA_RX_OFFSET(NET_IP_ALIGN) |
		MAX_DMA_DATA_LEN;
	skb_reserve(ch->skb[ch->dma.desc], NET_IP_ALIGN);
	वापस 0;
पूर्ण

अटल व्योम
ltq_etop_hw_receive(काष्ठा ltq_etop_chan *ch)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(ch->netdev);
	काष्ठा ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];
	काष्ठा sk_buff *skb = ch->skb[ch->dma.desc];
	पूर्णांक len = (desc->ctl & LTQ_DMA_SIZE_MASK) - MAX_DMA_CRC_LEN;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (ltq_etop_alloc_skb(ch)) अणु
		netdev_err(ch->netdev,
			"failed to allocate new rx buffer, stopping DMA\n");
		ltq_dma_बंद(&ch->dma);
	पूर्ण
	ch->dma.desc++;
	ch->dma.desc %= LTQ_DESC_NUM;
	spin_unlock_irqrestore(&priv->lock, flags);

	skb_put(skb, len);
	skb->protocol = eth_type_trans(skb, ch->netdev);
	netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक
ltq_etop_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ltq_etop_chan *ch = container_of(napi,
				काष्ठा ltq_etop_chan, napi);
	पूर्णांक work_करोne = 0;

	जबतक (work_करोne < budget) अणु
		काष्ठा ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];

		अगर ((desc->ctl & (LTQ_DMA_OWN | LTQ_DMA_C)) != LTQ_DMA_C)
			अवरोध;
		ltq_etop_hw_receive(ch);
		work_करोne++;
	पूर्ण
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(&ch->napi, work_करोne);
		ltq_dma_ack_irq(&ch->dma);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल पूर्णांक
ltq_etop_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ltq_etop_chan *ch =
		container_of(napi, काष्ठा ltq_etop_chan, napi);
	काष्ठा ltq_etop_priv *priv = netdev_priv(ch->netdev);
	काष्ठा netdev_queue *txq =
		netdev_get_tx_queue(ch->netdev, ch->idx >> 1);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	जबतक ((ch->dma.desc_base[ch->tx_मुक्त].ctl &
			(LTQ_DMA_OWN | LTQ_DMA_C)) == LTQ_DMA_C) अणु
		dev_kमुक्त_skb_any(ch->skb[ch->tx_मुक्त]);
		ch->skb[ch->tx_मुक्त] = शून्य;
		स_रखो(&ch->dma.desc_base[ch->tx_मुक्त], 0,
			माप(काष्ठा ltq_dma_desc));
		ch->tx_मुक्त++;
		ch->tx_मुक्त %= LTQ_DESC_NUM;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (netअगर_tx_queue_stopped(txq))
		netअगर_tx_start_queue(txq);
	napi_complete(&ch->napi);
	ltq_dma_ack_irq(&ch->dma);
	वापस 1;
पूर्ण

अटल irqवापस_t
ltq_etop_dma_irq(पूर्णांक irq, व्योम *_priv)
अणु
	काष्ठा ltq_etop_priv *priv = _priv;
	पूर्णांक ch = irq - LTQ_DMA_CH0_INT;

	napi_schedule(&priv->ch[ch].napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
ltq_etop_मुक्त_channel(काष्ठा net_device *dev, काष्ठा ltq_etop_chan *ch)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);

	ltq_dma_मुक्त(&ch->dma);
	अगर (ch->dma.irq)
		मुक्त_irq(ch->dma.irq, priv);
	अगर (IS_RX(ch->idx)) अणु
		पूर्णांक desc;
		क्रम (desc = 0; desc < LTQ_DESC_NUM; desc++)
			dev_kमुक्त_skb_any(ch->skb[ch->dma.desc]);
	पूर्ण
पूर्ण

अटल व्योम
ltq_etop_hw_निकास(काष्ठा net_device *dev)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	ltq_pmu_disable(PMU_PPE);
	क्रम (i = 0; i < MAX_DMA_CHAN; i++)
		अगर (IS_TX(i) || IS_RX(i))
			ltq_etop_मुक्त_channel(dev, &priv->ch[i]);
पूर्ण

अटल पूर्णांक
ltq_etop_hw_init(काष्ठा net_device *dev)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	ltq_pmu_enable(PMU_PPE);

	चयन (priv->pldata->mii_mode) अणु
	हाल PHY_INTERFACE_MODE_RMII:
		ltq_etop_w32_mask(ETOP_MII_MASK,
			ETOP_MII_REVERSE, LTQ_ETOP_CFG);
		अवरोध;

	हाल PHY_INTERFACE_MODE_MII:
		ltq_etop_w32_mask(ETOP_MII_MASK,
			ETOP_MII_NORMAL, LTQ_ETOP_CFG);
		अवरोध;

	शेष:
		netdev_err(dev, "unknown mii mode %d\n",
			priv->pldata->mii_mode);
		वापस -ENOTSUPP;
	पूर्ण

	/* enable crc generation */
	ltq_etop_w32(PPE32_CGEN, LQ_PPE32_ENET_MAC_CFG);

	ltq_dma_init_port(DMA_PORT_ETOP);

	क्रम (i = 0; i < MAX_DMA_CHAN; i++) अणु
		पूर्णांक irq = LTQ_DMA_CH0_INT + i;
		काष्ठा ltq_etop_chan *ch = &priv->ch[i];

		ch->idx = ch->dma.nr = i;
		ch->dma.dev = &priv->pdev->dev;

		अगर (IS_TX(i)) अणु
			ltq_dma_alloc_tx(&ch->dma);
			request_irq(irq, ltq_etop_dma_irq, 0, "etop_tx", priv);
		पूर्ण अन्यथा अगर (IS_RX(i)) अणु
			ltq_dma_alloc_rx(&ch->dma);
			क्रम (ch->dma.desc = 0; ch->dma.desc < LTQ_DESC_NUM;
					ch->dma.desc++)
				अगर (ltq_etop_alloc_skb(ch))
					वापस -ENOMEM;
			ch->dma.desc = 0;
			request_irq(irq, ltq_etop_dma_irq, 0, "etop_rx", priv);
		पूर्ण
		ch->dma.irq = irq;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
ltq_etop_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, "Lantiq ETOP", माप(info->driver));
	strlcpy(info->bus_info, "internal", माप(info->bus_info));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ltq_etop_ethtool_ops = अणु
	.get_drvinfo = ltq_etop_get_drvinfo,
	.nway_reset = phy_ethtool_nway_reset,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल पूर्णांक
ltq_etop_mdio_wr(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक phy_reg, u16 phy_data)
अणु
	u32 val = MDIO_REQUEST |
		((phy_addr & MDIO_ADDR_MASK) << MDIO_ADDR_OFFSET) |
		((phy_reg & MDIO_REG_MASK) << MDIO_REG_OFFSET) |
		phy_data;

	जबतक (ltq_etop_r32(LTQ_ETOP_MDIO) & MDIO_REQUEST)
		;
	ltq_etop_w32(val, LTQ_ETOP_MDIO);
	वापस 0;
पूर्ण

अटल पूर्णांक
ltq_etop_mdio_rd(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक phy_reg)
अणु
	u32 val = MDIO_REQUEST | MDIO_READ |
		((phy_addr & MDIO_ADDR_MASK) << MDIO_ADDR_OFFSET) |
		((phy_reg & MDIO_REG_MASK) << MDIO_REG_OFFSET);

	जबतक (ltq_etop_r32(LTQ_ETOP_MDIO) & MDIO_REQUEST)
		;
	ltq_etop_w32(val, LTQ_ETOP_MDIO);
	जबतक (ltq_etop_r32(LTQ_ETOP_MDIO) & MDIO_REQUEST)
		;
	val = ltq_etop_r32(LTQ_ETOP_MDIO) & MDIO_VAL_MASK;
	वापस val;
पूर्ण

अटल व्योम
ltq_etop_mdio_link(काष्ठा net_device *dev)
अणु
	/* nothing to करो  */
पूर्ण

अटल पूर्णांक
ltq_etop_mdio_probe(काष्ठा net_device *dev)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev;

	phydev = phy_find_first(priv->mii_bus);

	अगर (!phydev) अणु
		netdev_err(dev, "no PHY found\n");
		वापस -ENODEV;
	पूर्ण

	phydev = phy_connect(dev, phydev_name(phydev),
			     &ltq_etop_mdio_link, priv->pldata->mii_mode);

	अगर (IS_ERR(phydev)) अणु
		netdev_err(dev, "Could not attach to PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण

	phy_set_max_speed(phydev, SPEED_100);

	phy_attached_info(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक
ltq_etop_mdio_init(काष्ठा net_device *dev)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	priv->mii_bus = mdiobus_alloc();
	अगर (!priv->mii_bus) अणु
		netdev_err(dev, "failed to allocate mii bus\n");
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	priv->mii_bus->priv = dev;
	priv->mii_bus->पढ़ो = ltq_etop_mdio_rd;
	priv->mii_bus->ग_लिखो = ltq_etop_mdio_wr;
	priv->mii_bus->name = "ltq_mii";
	snम_लिखो(priv->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		priv->pdev->name, priv->pdev->id);
	अगर (mdiobus_रेजिस्टर(priv->mii_bus)) अणु
		err = -ENXIO;
		जाओ err_out_मुक्त_mdiobus;
	पूर्ण

	अगर (ltq_etop_mdio_probe(dev)) अणु
		err = -ENXIO;
		जाओ err_out_unरेजिस्टर_bus;
	पूर्ण
	वापस 0;

err_out_unरेजिस्टर_bus:
	mdiobus_unरेजिस्टर(priv->mii_bus);
err_out_मुक्त_mdiobus:
	mdiobus_मुक्त(priv->mii_bus);
err_out:
	वापस err;
पूर्ण

अटल व्योम
ltq_etop_mdio_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);

	phy_disconnect(dev->phydev);
	mdiobus_unरेजिस्टर(priv->mii_bus);
	mdiobus_मुक्त(priv->mii_bus);
पूर्ण

अटल पूर्णांक
ltq_etop_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < MAX_DMA_CHAN; i++) अणु
		काष्ठा ltq_etop_chan *ch = &priv->ch[i];

		अगर (!IS_TX(i) && (!IS_RX(i)))
			जारी;
		ltq_dma_खोलो(&ch->dma);
		ltq_dma_enable_irq(&ch->dma);
		napi_enable(&ch->napi);
	पूर्ण
	phy_start(dev->phydev);
	netअगर_tx_start_all_queues(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक
ltq_etop_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	netअगर_tx_stop_all_queues(dev);
	phy_stop(dev->phydev);
	क्रम (i = 0; i < MAX_DMA_CHAN; i++) अणु
		काष्ठा ltq_etop_chan *ch = &priv->ch[i];

		अगर (!IS_RX(i) && !IS_TX(i))
			जारी;
		napi_disable(&ch->napi);
		ltq_dma_बंद(&ch->dma);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
ltq_etop_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक queue = skb_get_queue_mapping(skb);
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, queue);
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	काष्ठा ltq_etop_chan *ch = &priv->ch[(queue << 1) | 1];
	काष्ठा ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];
	पूर्णांक len;
	अचिन्हित दीर्घ flags;
	u32 byte_offset;

	len = skb->len < ETH_ZLEN ? ETH_ZLEN : skb->len;

	अगर ((desc->ctl & (LTQ_DMA_OWN | LTQ_DMA_C)) || ch->skb[ch->dma.desc]) अणु
		dev_kमुक्त_skb_any(skb);
		netdev_err(dev, "tx ring full\n");
		netअगर_tx_stop_queue(txq);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* dma needs to start on a 16 byte aligned address */
	byte_offset = CPHYSADDR(skb->data) % 16;
	ch->skb[ch->dma.desc] = skb;

	netअगर_trans_update(dev);

	spin_lock_irqsave(&priv->lock, flags);
	desc->addr = ((अचिन्हित पूर्णांक) dma_map_single(&priv->pdev->dev, skb->data, len,
						DMA_TO_DEVICE)) - byte_offset;
	wmb();
	desc->ctl = LTQ_DMA_OWN | LTQ_DMA_SOP | LTQ_DMA_EOP |
		LTQ_DMA_TX_OFFSET(byte_offset) | (len & LTQ_DMA_SIZE_MASK);
	ch->dma.desc++;
	ch->dma.desc %= LTQ_DESC_NUM;
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (ch->dma.desc_base[ch->dma.desc].ctl & LTQ_DMA_OWN)
		netअगर_tx_stop_queue(txq);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक
ltq_etop_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	dev->mtu = new_mtu;

	spin_lock_irqsave(&priv->lock, flags);
	ltq_etop_w32((ETOP_PLEN_UNDER << 16) | new_mtu, LTQ_ETOP_IGPLEN);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
ltq_etop_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक ret = eth_mac_addr(dev, p);

	अगर (!ret) अणु
		काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
		अचिन्हित दीर्घ flags;

		/* store the mac क्रम the unicast filter */
		spin_lock_irqsave(&priv->lock, flags);
		ltq_etop_w32(*((u32 *)dev->dev_addr), LTQ_ETOP_MAC_DA0);
		ltq_etop_w32(*((u16 *)&dev->dev_addr[4]) << 16,
			LTQ_ETOP_MAC_DA1);
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
ltq_etop_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	/* ensure that the unicast filter is not enabled in promiscious mode */
	spin_lock_irqsave(&priv->lock, flags);
	अगर ((dev->flags & IFF_PROMISC) || (dev->flags & IFF_ALLMULTI))
		ltq_etop_w32_mask(ETOP_FTCU, 0, LTQ_ETOP_ENETS0);
	अन्यथा
		ltq_etop_w32_mask(0, ETOP_FTCU, LTQ_ETOP_ENETS0);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक
ltq_etop_init(काष्ठा net_device *dev)
अणु
	काष्ठा ltq_etop_priv *priv = netdev_priv(dev);
	काष्ठा sockaddr mac;
	पूर्णांक err;
	bool अक्रमom_mac = false;

	dev->watchकरोg_समयo = 10 * HZ;
	err = ltq_etop_hw_init(dev);
	अगर (err)
		जाओ err_hw;
	ltq_etop_change_mtu(dev, 1500);

	स_नकल(&mac, &priv->pldata->mac, माप(काष्ठा sockaddr));
	अगर (!is_valid_ether_addr(mac.sa_data)) अणु
		pr_warn("etop: invalid MAC, using random\n");
		eth_अक्रमom_addr(mac.sa_data);
		अक्रमom_mac = true;
	पूर्ण

	err = ltq_etop_set_mac_address(dev, &mac);
	अगर (err)
		जाओ err_netdev;

	/* Set addr_assign_type here, ltq_etop_set_mac_address would reset it. */
	अगर (अक्रमom_mac)
		dev->addr_assign_type = NET_ADDR_RANDOM;

	ltq_etop_set_multicast_list(dev);
	err = ltq_etop_mdio_init(dev);
	अगर (err)
		जाओ err_netdev;
	वापस 0;

err_netdev:
	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
err_hw:
	ltq_etop_hw_निकास(dev);
	वापस err;
पूर्ण

अटल व्योम
ltq_etop_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	पूर्णांक err;

	ltq_etop_hw_निकास(dev);
	err = ltq_etop_hw_init(dev);
	अगर (err)
		जाओ err_hw;
	netअगर_trans_update(dev);
	netअगर_wake_queue(dev);
	वापस;

err_hw:
	ltq_etop_hw_निकास(dev);
	netdev_err(dev, "failed to restart etop after TX timeout\n");
पूर्ण

अटल स्थिर काष्ठा net_device_ops ltq_eth_netdev_ops = अणु
	.nकरो_खोलो = ltq_etop_खोलो,
	.nकरो_stop = ltq_etop_stop,
	.nकरो_start_xmit = ltq_etop_tx,
	.nकरो_change_mtu = ltq_etop_change_mtu,
	.nकरो_करो_ioctl = phy_करो_ioctl,
	.nकरो_set_mac_address = ltq_etop_set_mac_address,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_set_rx_mode = ltq_etop_set_multicast_list,
	.nकरो_select_queue = dev_pick_tx_zero,
	.nकरो_init = ltq_etop_init,
	.nकरो_tx_समयout = ltq_etop_tx_समयout,
पूर्ण;

अटल पूर्णांक __init
ltq_etop_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा ltq_etop_priv *priv;
	काष्ठा resource *res;
	पूर्णांक err;
	पूर्णांक i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "failed to get etop resource\n");
		err = -ENOENT;
		जाओ err_out;
	पूर्ण

	res = devm_request_mem_region(&pdev->dev, res->start,
		resource_size(res), dev_name(&pdev->dev));
	अगर (!res) अणु
		dev_err(&pdev->dev, "failed to request etop resource\n");
		err = -EBUSY;
		जाओ err_out;
	पूर्ण

	ltq_etop_membase = devm_ioremap(&pdev->dev,
		res->start, resource_size(res));
	अगर (!ltq_etop_membase) अणु
		dev_err(&pdev->dev, "failed to remap etop engine %d\n",
			pdev->id);
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	dev = alloc_etherdev_mq(माप(काष्ठा ltq_etop_priv), 4);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	म_नकल(dev->name, "eth%d");
	dev->netdev_ops = &ltq_eth_netdev_ops;
	dev->ethtool_ops = &ltq_etop_ethtool_ops;
	priv = netdev_priv(dev);
	priv->res = res;
	priv->pdev = pdev;
	priv->pldata = dev_get_platdata(&pdev->dev);
	priv->netdev = dev;
	spin_lock_init(&priv->lock);
	SET_NETDEV_DEV(dev, &pdev->dev);

	क्रम (i = 0; i < MAX_DMA_CHAN; i++) अणु
		अगर (IS_TX(i))
			netअगर_napi_add(dev, &priv->ch[i].napi,
				ltq_etop_poll_tx, 8);
		अन्यथा अगर (IS_RX(i))
			netअगर_napi_add(dev, &priv->ch[i].napi,
				ltq_etop_poll_rx, 32);
		priv->ch[i].netdev = dev;
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ err_मुक्त;

	platक्रमm_set_drvdata(pdev, dev);
	वापस 0;

err_मुक्त:
	मुक्त_netdev(dev);
err_out:
	वापस err;
पूर्ण

अटल पूर्णांक
ltq_etop_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	अगर (dev) अणु
		netअगर_tx_stop_all_queues(dev);
		ltq_etop_hw_निकास(dev);
		ltq_etop_mdio_cleanup(dev);
		unरेजिस्टर_netdev(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ltq_mii_driver = अणु
	.हटाओ = ltq_etop_हटाओ,
	.driver = अणु
		.name = "ltq_etop",
	पूर्ण,
पूर्ण;

पूर्णांक __init
init_ltq_etop(व्योम)
अणु
	पूर्णांक ret = platक्रमm_driver_probe(&ltq_mii_driver, ltq_etop_probe);

	अगर (ret)
		pr_err("ltq_etop: Error registering platform driver!");
	वापस ret;
पूर्ण

अटल व्योम __निकास
निकास_ltq_etop(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ltq_mii_driver);
पूर्ण

module_init(init_ltq_etop);
module_निकास(निकास_ltq_etop);

MODULE_AUTHOR("John Crispin <blogic@openwrt.org>");
MODULE_DESCRIPTION("Lantiq SoC ETOP");
MODULE_LICENSE("GPL");
