<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dave DNET Ethernet Controller driver
 *
 * Copyright (C) 2008 Dave S.r.l. <www.dave.eu>
 * Copyright (C) 2009 Ilya Yanok, Emcraft Systems Ltd, <yanok@emcraft.com>
 */
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>

#समावेश "dnet.h"

#अघोषित DEBUG

/* function क्रम पढ़ोing पूर्णांकernal MAC रेजिस्टर */
अटल u16 dnet_पढ़ोw_mac(काष्ठा dnet *bp, u16 reg)
अणु
	u16 data_पढ़ो;

	/* issue a पढ़ो */
	dnet_ग_लिखोl(bp, reg, MACREG_ADDR);

	/* since a पढ़ो/ग_लिखो op to the MAC is very slow,
	 * we must रुको beक्रमe पढ़ोing the data */
	ndelay(500);

	/* पढ़ो data पढ़ो from the MAC रेजिस्टर */
	data_पढ़ो = dnet_पढ़ोl(bp, MACREG_DATA);

	/* all करोne */
	वापस data_पढ़ो;
पूर्ण

/* function क्रम writing पूर्णांकernal MAC रेजिस्टर */
अटल व्योम dnet_ग_लिखोw_mac(काष्ठा dnet *bp, u16 reg, u16 val)
अणु
	/* load data to ग_लिखो */
	dnet_ग_लिखोl(bp, val, MACREG_DATA);

	/* issue a ग_लिखो */
	dnet_ग_लिखोl(bp, reg | DNET_INTERNAL_WRITE, MACREG_ADDR);

	/* since a पढ़ो/ग_लिखो op to the MAC is very slow,
	 * we must रुको beक्रमe निकासing */
	ndelay(500);
पूर्ण

अटल व्योम __dnet_set_hwaddr(काष्ठा dnet *bp)
अणु
	u16 पंचांगp;

	पंचांगp = be16_to_cpup((__be16 *)bp->dev->dev_addr);
	dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_MAC_ADDR_0_REG, पंचांगp);
	पंचांगp = be16_to_cpup((__be16 *)(bp->dev->dev_addr + 2));
	dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_MAC_ADDR_1_REG, पंचांगp);
	पंचांगp = be16_to_cpup((__be16 *)(bp->dev->dev_addr + 4));
	dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_MAC_ADDR_2_REG, पंचांगp);
पूर्ण

अटल व्योम dnet_get_hwaddr(काष्ठा dnet *bp)
अणु
	u16 पंचांगp;
	u8 addr[6];

	/*
	 * from MAC करोcs:
	 * "Note that the MAC address is stored in the रेजिस्टरs in Hexadecimal
	 * क्रमm. For example, to set the MAC Address to: AC-DE-48-00-00-80
	 * would require writing 0xAC (octet 0) to address 0x0B (high byte of
	 * Mac_addr[15:0]), 0xDE (octet 1) to address 0x0A (Low byte of
	 * Mac_addr[15:0]), 0x48 (octet 2) to address 0x0D (high byte of
	 * Mac_addr[15:0]), 0x00 (octet 3) to address 0x0C (Low byte of
	 * Mac_addr[15:0]), 0x00 (octet 4) to address 0x0F (high byte of
	 * Mac_addr[15:0]), and 0x80 (octet 5) to address * 0x0E (Low byte of
	 * Mac_addr[15:0]).
	 */
	पंचांगp = dnet_पढ़ोw_mac(bp, DNET_INTERNAL_MAC_ADDR_0_REG);
	*((__be16 *)addr) = cpu_to_be16(पंचांगp);
	पंचांगp = dnet_पढ़ोw_mac(bp, DNET_INTERNAL_MAC_ADDR_1_REG);
	*((__be16 *)(addr + 2)) = cpu_to_be16(पंचांगp);
	पंचांगp = dnet_पढ़ोw_mac(bp, DNET_INTERNAL_MAC_ADDR_2_REG);
	*((__be16 *)(addr + 4)) = cpu_to_be16(पंचांगp);

	अगर (is_valid_ether_addr(addr))
		स_नकल(bp->dev->dev_addr, addr, माप(addr));
पूर्ण

अटल पूर्णांक dnet_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा dnet *bp = bus->priv;
	u16 value;

	जबतक (!(dnet_पढ़ोw_mac(bp, DNET_INTERNAL_GMII_MNG_CTL_REG)
				& DNET_INTERNAL_GMII_MNG_CMD_FIN))
		cpu_relax();

	/* only 5 bits allowed क्रम phy-addr and reg_offset */
	mii_id &= 0x1f;
	regnum &= 0x1f;

	/* prepare reg_value क्रम a पढ़ो */
	value = (mii_id << 8);
	value |= regnum;

	/* ग_लिखो control word */
	dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_GMII_MNG_CTL_REG, value);

	/* रुको क्रम end of transfer */
	जबतक (!(dnet_पढ़ोw_mac(bp, DNET_INTERNAL_GMII_MNG_CTL_REG)
				& DNET_INTERNAL_GMII_MNG_CMD_FIN))
		cpu_relax();

	value = dnet_पढ़ोw_mac(bp, DNET_INTERNAL_GMII_MNG_DAT_REG);

	pr_debug("mdio_read %02x:%02x <- %04x\n", mii_id, regnum, value);

	वापस value;
पूर्ण

अटल पूर्णांक dnet_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum,
			   u16 value)
अणु
	काष्ठा dnet *bp = bus->priv;
	u16 पंचांगp;

	pr_debug("mdio_write %02x:%02x <- %04x\n", mii_id, regnum, value);

	जबतक (!(dnet_पढ़ोw_mac(bp, DNET_INTERNAL_GMII_MNG_CTL_REG)
				& DNET_INTERNAL_GMII_MNG_CMD_FIN))
		cpu_relax();

	/* prepare क्रम a ग_लिखो operation */
	पंचांगp = (1 << 13);

	/* only 5 bits allowed क्रम phy-addr and reg_offset */
	mii_id &= 0x1f;
	regnum &= 0x1f;

	/* only 16 bits on data */
	value &= 0xffff;

	/* prepare reg_value क्रम a ग_लिखो */
	पंचांगp |= (mii_id << 8);
	पंचांगp |= regnum;

	/* ग_लिखो data to ग_लिखो first */
	dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_GMII_MNG_DAT_REG, value);

	/* ग_लिखो control word */
	dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_GMII_MNG_CTL_REG, पंचांगp);

	जबतक (!(dnet_पढ़ोw_mac(bp, DNET_INTERNAL_GMII_MNG_CTL_REG)
				& DNET_INTERNAL_GMII_MNG_CMD_FIN))
		cpu_relax();

	वापस 0;
पूर्ण

अटल व्योम dnet_handle_link_change(काष्ठा net_device *dev)
अणु
	काष्ठा dnet *bp = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	अचिन्हित दीर्घ flags;
	u32 mode_reg, ctl_reg;

	पूर्णांक status_change = 0;

	spin_lock_irqsave(&bp->lock, flags);

	mode_reg = dnet_पढ़ोw_mac(bp, DNET_INTERNAL_MODE_REG);
	ctl_reg = dnet_पढ़ोw_mac(bp, DNET_INTERNAL_RXTX_CONTROL_REG);

	अगर (phydev->link) अणु
		अगर (bp->duplex != phydev->duplex) अणु
			अगर (phydev->duplex)
				ctl_reg &=
				    ~(DNET_INTERNAL_RXTX_CONTROL_ENABLEHALFDUP);
			अन्यथा
				ctl_reg |=
				    DNET_INTERNAL_RXTX_CONTROL_ENABLEHALFDUP;

			bp->duplex = phydev->duplex;
			status_change = 1;
		पूर्ण

		अगर (bp->speed != phydev->speed) अणु
			status_change = 1;
			चयन (phydev->speed) अणु
			हाल 1000:
				mode_reg |= DNET_INTERNAL_MODE_GBITEN;
				अवरोध;
			हाल 100:
			हाल 10:
				mode_reg &= ~DNET_INTERNAL_MODE_GBITEN;
				अवरोध;
			शेष:
				prपूर्णांकk(KERN_WARNING
				       "%s: Ack!  Speed (%d) is not "
				       "10/100/1000!\n", dev->name,
				       phydev->speed);
				अवरोध;
			पूर्ण
			bp->speed = phydev->speed;
		पूर्ण
	पूर्ण

	अगर (phydev->link != bp->link) अणु
		अगर (phydev->link) अणु
			mode_reg |=
			    (DNET_INTERNAL_MODE_RXEN | DNET_INTERNAL_MODE_TXEN);
		पूर्ण अन्यथा अणु
			mode_reg &=
			    ~(DNET_INTERNAL_MODE_RXEN |
			      DNET_INTERNAL_MODE_TXEN);
			bp->speed = 0;
			bp->duplex = -1;
		पूर्ण
		bp->link = phydev->link;

		status_change = 1;
	पूर्ण

	अगर (status_change) अणु
		dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_RXTX_CONTROL_REG, ctl_reg);
		dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_MODE_REG, mode_reg);
	पूर्ण

	spin_unlock_irqrestore(&bp->lock, flags);

	अगर (status_change) अणु
		अगर (phydev->link)
			prपूर्णांकk(KERN_INFO "%s: link up (%d/%s)\n",
			       dev->name, phydev->speed,
			       DUPLEX_FULL == phydev->duplex ? "Full" : "Half");
		अन्यथा
			prपूर्णांकk(KERN_INFO "%s: link down\n", dev->name);
	पूर्ण
पूर्ण

अटल पूर्णांक dnet_mii_probe(काष्ठा net_device *dev)
अणु
	काष्ठा dnet *bp = netdev_priv(dev);
	काष्ठा phy_device *phydev = शून्य;

	/* find the first phy */
	phydev = phy_find_first(bp->mii_bus);

	अगर (!phydev) अणु
		prपूर्णांकk(KERN_ERR "%s: no PHY found\n", dev->name);
		वापस -ENODEV;
	पूर्ण

	/* TODO : add pin_irq */

	/* attach the mac to the phy */
	अगर (bp->capabilities & DNET_HAS_RMII) अणु
		phydev = phy_connect(dev, phydev_name(phydev),
				     &dnet_handle_link_change,
				     PHY_INTERFACE_MODE_RMII);
	पूर्ण अन्यथा अणु
		phydev = phy_connect(dev, phydev_name(phydev),
				     &dnet_handle_link_change,
				     PHY_INTERFACE_MODE_MII);
	पूर्ण

	अगर (IS_ERR(phydev)) अणु
		prपूर्णांकk(KERN_ERR "%s: Could not attach to PHY\n", dev->name);
		वापस PTR_ERR(phydev);
	पूर्ण

	/* mask with MAC supported features */
	अगर (bp->capabilities & DNET_HAS_GIGABIT)
		phy_set_max_speed(phydev, SPEED_1000);
	अन्यथा
		phy_set_max_speed(phydev, SPEED_100);

	phy_support_asym_छोड़ो(phydev);

	bp->link = 0;
	bp->speed = 0;
	bp->duplex = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक dnet_mii_init(काष्ठा dnet *bp)
अणु
	पूर्णांक err;

	bp->mii_bus = mdiobus_alloc();
	अगर (bp->mii_bus == शून्य)
		वापस -ENOMEM;

	bp->mii_bus->name = "dnet_mii_bus";
	bp->mii_bus->पढ़ो = &dnet_mdio_पढ़ो;
	bp->mii_bus->ग_लिखो = &dnet_mdio_ग_लिखो;

	snम_लिखो(bp->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		bp->pdev->name, bp->pdev->id);

	bp->mii_bus->priv = bp;

	अगर (mdiobus_रेजिस्टर(bp->mii_bus)) अणु
		err = -ENXIO;
		जाओ err_out;
	पूर्ण

	अगर (dnet_mii_probe(bp->dev) != 0) अणु
		err = -ENXIO;
		जाओ err_out_unरेजिस्टर_bus;
	पूर्ण

	वापस 0;

err_out_unरेजिस्टर_bus:
	mdiobus_unरेजिस्टर(bp->mii_bus);
err_out:
	mdiobus_मुक्त(bp->mii_bus);
	वापस err;
पूर्ण

/* For Neptune board: LINK1000 as Link LED and TX as activity LED */
अटल पूर्णांक dnet_phy_marvell_fixup(काष्ठा phy_device *phydev)
अणु
	वापस phy_ग_लिखो(phydev, 0x18, 0x4148);
पूर्ण

अटल व्योम dnet_update_stats(काष्ठा dnet *bp)
अणु
	u32 __iomem *reg = bp->regs + DNET_RX_PKT_IGNR_CNT;
	u32 *p = &bp->hw_stats.rx_pkt_ignr;
	u32 *end = &bp->hw_stats.rx_byte + 1;

	WARN_ON((अचिन्हित दीर्घ)(end - p - 1) !=
		(DNET_RX_BYTE_CNT - DNET_RX_PKT_IGNR_CNT) / 4);

	क्रम (; p < end; p++, reg++)
		*p += पढ़ोl(reg);

	reg = bp->regs + DNET_TX_UNICAST_CNT;
	p = &bp->hw_stats.tx_unicast;
	end = &bp->hw_stats.tx_byte + 1;

	WARN_ON((अचिन्हित दीर्घ)(end - p - 1) !=
		(DNET_TX_BYTE_CNT - DNET_TX_UNICAST_CNT) / 4);

	क्रम (; p < end; p++, reg++)
		*p += पढ़ोl(reg);
पूर्ण

अटल पूर्णांक dnet_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा dnet *bp = container_of(napi, काष्ठा dnet, napi);
	काष्ठा net_device *dev = bp->dev;
	पूर्णांक npackets = 0;
	अचिन्हित पूर्णांक pkt_len;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक *data_ptr;
	u32 पूर्णांक_enable;
	u32 cmd_word;
	पूर्णांक i;

	जबतक (npackets < budget) अणु
		/*
		 * अवरोध out of जबतक loop अगर there are no more
		 * packets रुकोing
		 */
		अगर (!(dnet_पढ़ोl(bp, RX_FIFO_WCNT) >> 16))
			अवरोध;

		cmd_word = dnet_पढ़ोl(bp, RX_LEN_FIFO);
		pkt_len = cmd_word & 0xFFFF;

		अगर (cmd_word & 0xDF180000)
			prपूर्णांकk(KERN_ERR "%s packet receive error %x\n",
			       __func__, cmd_word);

		skb = netdev_alloc_skb(dev, pkt_len + 5);
		अगर (skb != शून्य) अणु
			/* Align IP on 16 byte boundaries */
			skb_reserve(skb, 2);
			/*
			 * 'skb_put()' poपूर्णांकs to the start of sk_buff
			 * data area.
			 */
			data_ptr = skb_put(skb, pkt_len);
			क्रम (i = 0; i < (pkt_len + 3) >> 2; i++)
				*data_ptr++ = dnet_पढ़ोl(bp, RX_DATA_FIFO);
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_receive_skb(skb);
			npackets++;
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_NOTICE
			       "%s: No memory to allocate a sk_buff of "
			       "size %u.\n", dev->name, pkt_len);
	पूर्ण

	अगर (npackets < budget) अणु
		/* We processed all packets available.  Tell NAPI it can
		 * stop polling then re-enable rx पूर्णांकerrupts.
		 */
		napi_complete_करोne(napi, npackets);
		पूर्णांक_enable = dnet_पढ़ोl(bp, INTR_ENB);
		पूर्णांक_enable |= DNET_INTR_SRC_RX_CMDFIFOAF;
		dnet_ग_लिखोl(bp, पूर्णांक_enable, INTR_ENB);
	पूर्ण

	वापस npackets;
पूर्ण

अटल irqवापस_t dnet_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा dnet *bp = netdev_priv(dev);
	u32 पूर्णांक_src, पूर्णांक_enable, पूर्णांक_current;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक handled = 0;

	spin_lock_irqsave(&bp->lock, flags);

	/* पढ़ो and clear the DNET irq (clear on पढ़ो) */
	पूर्णांक_src = dnet_पढ़ोl(bp, INTR_SRC);
	पूर्णांक_enable = dnet_पढ़ोl(bp, INTR_ENB);
	पूर्णांक_current = पूर्णांक_src & पूर्णांक_enable;

	/* restart the queue अगर we had stopped it क्रम TX fअगरo almost full */
	अगर (पूर्णांक_current & DNET_INTR_SRC_TX_FIFOAE) अणु
		पूर्णांक_enable = dnet_पढ़ोl(bp, INTR_ENB);
		पूर्णांक_enable &= ~DNET_INTR_ENB_TX_FIFOAE;
		dnet_ग_लिखोl(bp, पूर्णांक_enable, INTR_ENB);
		netअगर_wake_queue(dev);
		handled = 1;
	पूर्ण

	/* RX FIFO error checking */
	अगर (पूर्णांक_current &
	    (DNET_INTR_SRC_RX_CMDFIFOFF | DNET_INTR_SRC_RX_DATAFIFOFF)) अणु
		prपूर्णांकk(KERN_ERR "%s: RX fifo error %x, irq %x\n", __func__,
		       dnet_पढ़ोl(bp, RX_STATUS), पूर्णांक_current);
		/* we can only flush the RX FIFOs */
		dnet_ग_लिखोl(bp, DNET_SYS_CTL_RXFIFOFLUSH, SYS_CTL);
		ndelay(500);
		dnet_ग_लिखोl(bp, 0, SYS_CTL);
		handled = 1;
	पूर्ण

	/* TX FIFO error checking */
	अगर (पूर्णांक_current &
	    (DNET_INTR_SRC_TX_FIFOFULL | DNET_INTR_SRC_TX_DISCFRM)) अणु
		prपूर्णांकk(KERN_ERR "%s: TX fifo error %x, irq %x\n", __func__,
		       dnet_पढ़ोl(bp, TX_STATUS), पूर्णांक_current);
		/* we can only flush the TX FIFOs */
		dnet_ग_लिखोl(bp, DNET_SYS_CTL_TXFIFOFLUSH, SYS_CTL);
		ndelay(500);
		dnet_ग_लिखोl(bp, 0, SYS_CTL);
		handled = 1;
	पूर्ण

	अगर (पूर्णांक_current & DNET_INTR_SRC_RX_CMDFIFOAF) अणु
		अगर (napi_schedule_prep(&bp->napi)) अणु
			/*
			 * There's no poपूर्णांक taking any more पूर्णांकerrupts
			 * until we have processed the buffers
			 */
			/* Disable Rx पूर्णांकerrupts and schedule NAPI poll */
			पूर्णांक_enable = dnet_पढ़ोl(bp, INTR_ENB);
			पूर्णांक_enable &= ~DNET_INTR_SRC_RX_CMDFIFOAF;
			dnet_ग_लिखोl(bp, पूर्णांक_enable, INTR_ENB);
			__napi_schedule(&bp->napi);
		पूर्ण
		handled = 1;
	पूर्ण

	अगर (!handled)
		pr_debug("%s: irq %x remains\n", __func__, पूर्णांक_current);

	spin_unlock_irqrestore(&bp->lock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण

#अगर_घोषित DEBUG
अटल अंतरभूत व्योम dnet_prपूर्णांक_skb(काष्ठा sk_buff *skb)
अणु
	पूर्णांक k;
	prपूर्णांकk(KERN_DEBUG PFX "data:");
	क्रम (k = 0; k < skb->len; k++)
		prपूर्णांकk(" %02x", (अचिन्हित पूर्णांक)skb->data[k]);
	prपूर्णांकk("\n");
पूर्ण
#अन्यथा
#घोषणा dnet_prपूर्णांक_skb(skb)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल netdev_tx_t dnet_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु

	काष्ठा dnet *bp = netdev_priv(dev);
	अचिन्हित पूर्णांक i, tx_cmd, wrsz;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक *bufp;
	u32 irq_enable;

	dnet_पढ़ोl(bp, TX_STATUS);

	pr_debug("start_xmit: len %u head %p data %p\n",
	       skb->len, skb->head, skb->data);
	dnet_prपूर्णांक_skb(skb);

	spin_lock_irqsave(&bp->lock, flags);

	dnet_पढ़ोl(bp, TX_STATUS);

	bufp = (अचिन्हित पूर्णांक *)(((अचिन्हित दीर्घ) skb->data) & ~0x3UL);
	wrsz = (u32) skb->len + 3;
	wrsz += ((अचिन्हित दीर्घ) skb->data) & 0x3;
	wrsz >>= 2;
	tx_cmd = ((((अचिन्हित दीर्घ)(skb->data)) & 0x03) << 16) | (u32) skb->len;

	/* check अगर there is enough room क्रम the current frame */
	अगर (wrsz < (DNET_FIFO_SIZE - dnet_पढ़ोl(bp, TX_FIFO_WCNT))) अणु
		क्रम (i = 0; i < wrsz; i++)
			dnet_ग_लिखोl(bp, *bufp++, TX_DATA_FIFO);

		/*
		 * inक्रमm MAC that a packet's written and पढ़ोy to be
		 * shipped out
		 */
		dnet_ग_लिखोl(bp, tx_cmd, TX_LEN_FIFO);
	पूर्ण

	अगर (dnet_पढ़ोl(bp, TX_FIFO_WCNT) > DNET_FIFO_TX_DATA_AF_TH) अणु
		netअगर_stop_queue(dev);
		dnet_पढ़ोl(bp, INTR_SRC);
		irq_enable = dnet_पढ़ोl(bp, INTR_ENB);
		irq_enable |= DNET_INTR_ENB_TX_FIFOAE;
		dnet_ग_लिखोl(bp, irq_enable, INTR_ENB);
	पूर्ण

	skb_tx_बारtamp(skb);

	/* मुक्त the buffer */
	dev_kमुक्त_skb(skb);

	spin_unlock_irqrestore(&bp->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम dnet_reset_hw(काष्ठा dnet *bp)
अणु
	/* put ts_mac in IDLE state i.e. disable rx/tx */
	dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_MODE_REG, DNET_INTERNAL_MODE_FCEN);

	/*
	 * RX FIFO almost full threshold: only cmd FIFO almost full is
	 * implemented क्रम RX side
	 */
	dnet_ग_लिखोl(bp, DNET_FIFO_RX_CMD_AF_TH, RX_FIFO_TH);
	/*
	 * TX FIFO almost empty threshold: only data FIFO almost empty
	 * is implemented क्रम TX side
	 */
	dnet_ग_लिखोl(bp, DNET_FIFO_TX_DATA_AE_TH, TX_FIFO_TH);

	/* flush rx/tx fअगरos */
	dnet_ग_लिखोl(bp, DNET_SYS_CTL_RXFIFOFLUSH | DNET_SYS_CTL_TXFIFOFLUSH,
			SYS_CTL);
	msleep(1);
	dnet_ग_लिखोl(bp, 0, SYS_CTL);
पूर्ण

अटल व्योम dnet_init_hw(काष्ठा dnet *bp)
अणु
	u32 config;

	dnet_reset_hw(bp);
	__dnet_set_hwaddr(bp);

	config = dnet_पढ़ोw_mac(bp, DNET_INTERNAL_RXTX_CONTROL_REG);

	अगर (bp->dev->flags & IFF_PROMISC)
		/* Copy All Frames */
		config |= DNET_INTERNAL_RXTX_CONTROL_ENPROMISC;
	अगर (!(bp->dev->flags & IFF_BROADCAST))
		/* No BroadCast */
		config |= DNET_INTERNAL_RXTX_CONTROL_RXMULTICAST;

	config |= DNET_INTERNAL_RXTX_CONTROL_RXPAUSE |
	    DNET_INTERNAL_RXTX_CONTROL_RXBROADCAST |
	    DNET_INTERNAL_RXTX_CONTROL_DROPCONTROL |
	    DNET_INTERNAL_RXTX_CONTROL_DISCFXFCS;

	dnet_ग_लिखोw_mac(bp, DNET_INTERNAL_RXTX_CONTROL_REG, config);

	/* clear irq beक्रमe enabling them */
	config = dnet_पढ़ोl(bp, INTR_SRC);

	/* enable RX/TX पूर्णांकerrupt, recv packet पढ़ोy पूर्णांकerrupt */
	dnet_ग_लिखोl(bp, DNET_INTR_ENB_GLOBAL_ENABLE | DNET_INTR_ENB_RX_SUMMARY |
			DNET_INTR_ENB_TX_SUMMARY | DNET_INTR_ENB_RX_FIFOERR |
			DNET_INTR_ENB_RX_ERROR | DNET_INTR_ENB_RX_FIFOFULL |
			DNET_INTR_ENB_TX_FIFOFULL | DNET_INTR_ENB_TX_DISCFRM |
			DNET_INTR_ENB_RX_PKTRDY, INTR_ENB);
पूर्ण

अटल पूर्णांक dnet_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा dnet *bp = netdev_priv(dev);

	/* अगर the phy is not yet रेजिस्टर, retry later */
	अगर (!dev->phydev)
		वापस -EAGAIN;

	napi_enable(&bp->napi);
	dnet_init_hw(bp);

	phy_start_aneg(dev->phydev);

	/* schedule a link state check */
	phy_start(dev->phydev);

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dnet_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा dnet *bp = netdev_priv(dev);

	netअगर_stop_queue(dev);
	napi_disable(&bp->napi);

	अगर (dev->phydev)
		phy_stop(dev->phydev);

	dnet_reset_hw(bp);
	netअगर_carrier_off(dev);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dnet_prपूर्णांक_pretty_hwstats(काष्ठा dnet_stats *hwstat)
अणु
	pr_debug("%s\n", __func__);
	pr_debug("----------------------------- RX statistics "
		 "-------------------------------\n");
	pr_debug("RX_PKT_IGNR_CNT %-8x\n", hwstat->rx_pkt_ignr);
	pr_debug("RX_LEN_CHK_ERR_CNT %-8x\n", hwstat->rx_len_chk_err);
	pr_debug("RX_LNG_FRM_CNT %-8x\n", hwstat->rx_lng_frm);
	pr_debug("RX_SHRT_FRM_CNT %-8x\n", hwstat->rx_shrt_frm);
	pr_debug("RX_IPG_VIOL_CNT %-8x\n", hwstat->rx_ipg_viol);
	pr_debug("RX_CRC_ERR_CNT %-8x\n", hwstat->rx_crc_err);
	pr_debug("RX_OK_PKT_CNT %-8x\n", hwstat->rx_ok_pkt);
	pr_debug("RX_CTL_FRM_CNT %-8x\n", hwstat->rx_ctl_frm);
	pr_debug("RX_PAUSE_FRM_CNT %-8x\n", hwstat->rx_छोड़ो_frm);
	pr_debug("RX_MULTICAST_CNT %-8x\n", hwstat->rx_multicast);
	pr_debug("RX_BROADCAST_CNT %-8x\n", hwstat->rx_broadcast);
	pr_debug("RX_VLAN_TAG_CNT %-8x\n", hwstat->rx_vlan_tag);
	pr_debug("RX_PRE_SHRINK_CNT %-8x\n", hwstat->rx_pre_shrink);
	pr_debug("RX_DRIB_NIB_CNT %-8x\n", hwstat->rx_drib_nib);
	pr_debug("RX_UNSUP_OPCD_CNT %-8x\n", hwstat->rx_unsup_opcd);
	pr_debug("RX_BYTE_CNT %-8x\n", hwstat->rx_byte);
	pr_debug("----------------------------- TX statistics "
		 "-------------------------------\n");
	pr_debug("TX_UNICAST_CNT %-8x\n", hwstat->tx_unicast);
	pr_debug("TX_PAUSE_FRM_CNT %-8x\n", hwstat->tx_छोड़ो_frm);
	pr_debug("TX_MULTICAST_CNT %-8x\n", hwstat->tx_multicast);
	pr_debug("TX_BRDCAST_CNT %-8x\n", hwstat->tx_brdcast);
	pr_debug("TX_VLAN_TAG_CNT %-8x\n", hwstat->tx_vlan_tag);
	pr_debug("TX_BAD_FCS_CNT %-8x\n", hwstat->tx_bad_fcs);
	pr_debug("TX_JUMBO_CNT %-8x\n", hwstat->tx_jumbo);
	pr_debug("TX_BYTE_CNT %-8x\n", hwstat->tx_byte);
पूर्ण

अटल काष्ठा net_device_stats *dnet_get_stats(काष्ठा net_device *dev)
अणु

	काष्ठा dnet *bp = netdev_priv(dev);
	काष्ठा net_device_stats *nstat = &dev->stats;
	काष्ठा dnet_stats *hwstat = &bp->hw_stats;

	/* पढ़ो stats from hardware */
	dnet_update_stats(bp);

	/* Convert HW stats पूर्णांकo netdevice stats */
	nstat->rx_errors = (hwstat->rx_len_chk_err +
			    hwstat->rx_lng_frm + hwstat->rx_shrt_frm +
			    /* ignore IGP violation error
			    hwstat->rx_ipg_viol + */
			    hwstat->rx_crc_err +
			    hwstat->rx_pre_shrink +
			    hwstat->rx_drib_nib + hwstat->rx_unsup_opcd);
	nstat->tx_errors = hwstat->tx_bad_fcs;
	nstat->rx_length_errors = (hwstat->rx_len_chk_err +
				   hwstat->rx_lng_frm +
				   hwstat->rx_shrt_frm + hwstat->rx_pre_shrink);
	nstat->rx_crc_errors = hwstat->rx_crc_err;
	nstat->rx_frame_errors = hwstat->rx_pre_shrink + hwstat->rx_drib_nib;
	nstat->rx_packets = hwstat->rx_ok_pkt;
	nstat->tx_packets = (hwstat->tx_unicast +
			     hwstat->tx_multicast + hwstat->tx_brdcast);
	nstat->rx_bytes = hwstat->rx_byte;
	nstat->tx_bytes = hwstat->tx_byte;
	nstat->multicast = hwstat->rx_multicast;
	nstat->rx_missed_errors = hwstat->rx_pkt_ignr;

	dnet_prपूर्णांक_pretty_hwstats(hwstat);

	वापस nstat;
पूर्ण

अटल व्योम dnet_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, "0", माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops dnet_ethtool_ops = अणु
	.get_drvinfo		= dnet_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_link_ksettings     = phy_ethtool_get_link_ksettings,
	.set_link_ksettings     = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops dnet_netdev_ops = अणु
	.nकरो_खोलो		= dnet_खोलो,
	.nकरो_stop		= dnet_बंद,
	.nकरो_get_stats		= dnet_get_stats,
	.nकरो_start_xmit		= dnet_start_xmit,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक dnet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा net_device *dev;
	काष्ठा dnet *bp;
	काष्ठा phy_device *phydev;
	पूर्णांक err;
	अचिन्हित पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);

	dev = alloc_etherdev(माप(*bp));
	अगर (!dev)
		वापस -ENOMEM;

	/* TODO: Actually, we have some पूर्णांकeresting features... */
	dev->features |= 0;

	bp = netdev_priv(dev);
	bp->dev = dev;

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	spin_lock_init(&bp->lock);

	bp->regs = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(bp->regs)) अणु
		err = PTR_ERR(bp->regs);
		जाओ err_out_मुक्त_dev;
	पूर्ण

	dev->irq = irq;
	err = request_irq(dev->irq, dnet_पूर्णांकerrupt, 0, DRV_NAME, dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to request IRQ %d (error %d)\n",
		       irq, err);
		जाओ err_out_मुक्त_dev;
	पूर्ण

	dev->netdev_ops = &dnet_netdev_ops;
	netअगर_napi_add(dev, &bp->napi, dnet_poll, 64);
	dev->ethtool_ops = &dnet_ethtool_ops;

	dev->base_addr = (अचिन्हित दीर्घ)bp->regs;

	bp->capabilities = dnet_पढ़ोl(bp, VERCAPS) & DNET_CAPS_MASK;

	dnet_get_hwaddr(bp);

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		/* choose a अक्रमom ethernet address */
		eth_hw_addr_अक्रमom(dev);
		__dnet_set_hwaddr(bp);
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot register net device, aborting.\n");
		जाओ err_out_मुक्त_irq;
	पूर्ण

	/* रेजिस्टर the PHY board fixup (क्रम Marvell 88E1111) */
	err = phy_रेजिस्टर_fixup_क्रम_uid(0x01410cc0, 0xfffffff0,
					 dnet_phy_marvell_fixup);
	/* we can live without it, so just issue a warning */
	अगर (err)
		dev_warn(&pdev->dev, "Cannot register PHY board fixup.\n");

	err = dnet_mii_init(bp);
	अगर (err)
		जाओ err_out_unरेजिस्टर_netdev;

	dev_info(&pdev->dev, "Dave DNET at 0x%p (0x%08x) irq %d %pM\n",
	       bp->regs, (अचिन्हित पूर्णांक)res->start, dev->irq, dev->dev_addr);
	dev_info(&pdev->dev, "has %smdio, %sirq, %sgigabit, %sdma\n",
	       (bp->capabilities & DNET_HAS_MDIO) ? "" : "no ",
	       (bp->capabilities & DNET_HAS_IRQ) ? "" : "no ",
	       (bp->capabilities & DNET_HAS_GIGABIT) ? "" : "no ",
	       (bp->capabilities & DNET_HAS_DMA) ? "" : "no ");
	phydev = dev->phydev;
	phy_attached_info(phydev);

	वापस 0;

err_out_unरेजिस्टर_netdev:
	unरेजिस्टर_netdev(dev);
err_out_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
err_out_मुक्त_dev:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक dnet_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु

	काष्ठा net_device *dev;
	काष्ठा dnet *bp;

	dev = platक्रमm_get_drvdata(pdev);

	अगर (dev) अणु
		bp = netdev_priv(dev);
		अगर (dev->phydev)
			phy_disconnect(dev->phydev);
		mdiobus_unरेजिस्टर(bp->mii_bus);
		mdiobus_मुक्त(bp->mii_bus);
		unरेजिस्टर_netdev(dev);
		मुक्त_irq(dev->irq, dev);
		मुक्त_netdev(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dnet_driver = अणु
	.probe		= dnet_probe,
	.हटाओ		= dnet_हटाओ,
	.driver		= अणु
		.name		= "dnet",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dnet_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Dave DNET Ethernet driver");
MODULE_AUTHOR("Ilya Yanok <yanok@emcraft.com>, "
	      "Matteo Vit <matteo.vit@dave.eu>");
