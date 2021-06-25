<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/net/ethernet/8390/ax88796.c
 *
 * Copyright 2005,2007 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Asix AX88796 10/100 Ethernet controller support
 *	Based on ne.c, by Donald Becker, et-al.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/isapnp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mdio-bitbang.h>
#समावेश <linux/phy.h>
#समावेश <linux/eeprom_93cx6.h>
#समावेश <linux/slab.h>

#समावेश <net/ax88796.h>


/* Rename the lib8390.c functions to show that they are in this driver */
#घोषणा __ei_खोलो ax_ei_खोलो
#घोषणा __ei_बंद ax_ei_बंद
#घोषणा __ei_poll ax_ei_poll
#घोषणा __ei_start_xmit ax_ei_start_xmit
#घोषणा __ei_tx_समयout ax_ei_tx_समयout
#घोषणा __ei_get_stats ax_ei_get_stats
#घोषणा __ei_set_multicast_list ax_ei_set_multicast_list
#घोषणा __ei_पूर्णांकerrupt ax_ei_पूर्णांकerrupt
#घोषणा ____alloc_ei_netdev ax__alloc_ei_netdev
#घोषणा __NS8390_init ax_NS8390_init

/* क्रमce अचिन्हित दीर्घ back to 'void __iomem *' */
#घोषणा ax_convert_addr(_a) ((व्योम __क्रमce __iomem *)(_a))

#घोषणा ei_inb(_a) पढ़ोb(ax_convert_addr(_a))
#घोषणा ei_outb(_v, _a) ग_लिखोb(_v, ax_convert_addr(_a))

#घोषणा ei_inb_p(_a) ei_inb(_a)
#घोषणा ei_outb_p(_v, _a) ei_outb(_v, _a)

/* define EI_SHIFT() to take पूर्णांकo account our रेजिस्टर offsets */
#घोषणा EI_SHIFT(x) (ei_local->reg_offset[(x)])

/* Ensure we have our RCR base value */
#घोषणा AX88796_PLATFORM

अटल अचिन्हित अक्षर version[] = "ax88796.c: Copyright 2005,2007 Simtec Electronics\n";

#समावेश "lib8390.c"

#घोषणा DRV_NAME "ax88796"
#घोषणा DRV_VERSION "1.00"

/* from ne.c */
#घोषणा NE_CMD		EI_SHIFT(0x00)
#घोषणा NE_RESET	EI_SHIFT(0x1f)
#घोषणा NE_DATAPORT	EI_SHIFT(0x10)

#घोषणा NE1SM_START_PG	0x20	/* First page of TX buffer */
#घोषणा NE1SM_STOP_PG	0x40	/* Last page +1 of RX ring */
#घोषणा NESM_START_PG	0x40	/* First page of TX buffer */
#घोषणा NESM_STOP_PG	0x80	/* Last page +1 of RX ring */

#घोषणा AX_GPOC_PPDSET	BIT(6)

/* device निजी data */

काष्ठा ax_device अणु
	काष्ठा mii_bus *mii_bus;
	काष्ठा mdiobb_ctrl bb_ctrl;
	व्योम __iomem *addr_memr;
	u8 reg_memr;
	पूर्णांक link;
	पूर्णांक speed;
	पूर्णांक duplex;

	व्योम __iomem *map2;
	स्थिर काष्ठा ax_plat_data *plat;

	अचिन्हित अक्षर running;
	अचिन्हित अक्षर resume_खोलो;
	अचिन्हित पूर्णांक irqflags;

	u32 reg_offsets[0x20];
पूर्ण;

अटल अंतरभूत काष्ठा ax_device *to_ax_dev(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	वापस (काष्ठा ax_device *)(ei_local + 1);
पूर्ण

/*
 * ax_initial_check
 *
 * करो an initial probe क्रम the card to check whether it exists
 * and is functional
 */
अटल पूर्णांक ax_initial_check(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	व्योम __iomem *ioaddr = ei_local->mem;
	पूर्णांक reg0;
	पूर्णांक regd;

	reg0 = ei_inb(ioaddr);
	अगर (reg0 == 0xFF)
		वापस -ENODEV;

	ei_outb(E8390_NODMA + E8390_PAGE1 + E8390_STOP, ioaddr + E8390_CMD);
	regd = ei_inb(ioaddr + 0x0d);
	ei_outb(0xff, ioaddr + 0x0d);
	ei_outb(E8390_NODMA + E8390_PAGE0, ioaddr + E8390_CMD);
	ei_inb(ioaddr + EN0_COUNTER0); /* Clear the counter by पढ़ोing. */
	अगर (ei_inb(ioaddr + EN0_COUNTER0) != 0) अणु
		ei_outb(reg0, ioaddr);
		ei_outb(regd, ioaddr + 0x0d);	/* Restore the old values. */
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Hard reset the card. This used to छोड़ो क्रम the same period that a
 * 8390 reset command required, but that shouldn't be necessary.
 */
अटल व्योम ax_reset_8390(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित दीर्घ reset_start_समय = jअगरfies;
	व्योम __iomem *addr = (व्योम __iomem *)dev->base_addr;

	netअगर_dbg(ei_local, hw, dev, "resetting the 8390 t=%ld...\n", jअगरfies);

	ei_outb(ei_inb(addr + NE_RESET), addr + NE_RESET);

	ei_local->txing = 0;
	ei_local->dमुख्यg = 0;

	/* This check _should_not_ be necessary, omit eventually. */
	जबतक ((ei_inb(addr + EN0_ISR) & ENISR_RESET) == 0) अणु
		अगर (समय_after(jअगरfies, reset_start_समय + 2 * HZ / 100)) अणु
			netdev_warn(dev, "%s: did not complete.\n", __func__);
			अवरोध;
		पूर्ण
	पूर्ण

	ei_outb(ENISR_RESET, addr + EN0_ISR);	/* Ack पूर्णांकr. */
पूर्ण

/* Wrapper क्रम __ei_पूर्णांकerrupt क्रम platक्रमms that have a platक्रमm-specअगरic
 * way to find out whether the पूर्णांकerrupt request might be caused by
 * the ax88796 chip.
 */
अटल irqवापस_t ax_ei_पूर्णांकerrupt_filtered(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा ax_device *ax = to_ax_dev(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev.parent);

	अगर (!ax->plat->check_irq(pdev))
		वापस IRQ_NONE;

	वापस ax_ei_पूर्णांकerrupt(irq, dev_id);
पूर्ण

अटल व्योम ax_get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr,
			    पूर्णांक ring_page)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	व्योम __iomem *nic_base = ei_local->mem;

	/* This *shouldn't* happen. If it does, it's the last thing you'll see */
	अगर (ei_local->dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in %s "
			"[DMAstat:%d][irqlock:%d].\n",
			__func__,
			ei_local->dमुख्यg, ei_local->irqlock);
		वापस;
	पूर्ण

	ei_local->dमुख्यg |= 0x01;
	ei_outb(E8390_NODMA + E8390_PAGE0 + E8390_START, nic_base + NE_CMD);
	ei_outb(माप(काष्ठा e8390_pkt_hdr), nic_base + EN0_RCNTLO);
	ei_outb(0, nic_base + EN0_RCNTHI);
	ei_outb(0, nic_base + EN0_RSARLO);		/* On page boundary */
	ei_outb(ring_page, nic_base + EN0_RSARHI);
	ei_outb(E8390_RREAD+E8390_START, nic_base + NE_CMD);

	अगर (ei_local->word16)
		ioपढ़ो16_rep(nic_base + NE_DATAPORT, hdr,
			     माप(काष्ठा e8390_pkt_hdr) >> 1);
	अन्यथा
		ioपढ़ो8_rep(nic_base + NE_DATAPORT, hdr,
			    माप(काष्ठा e8390_pkt_hdr));

	ei_outb(ENISR_RDC, nic_base + EN0_ISR);	/* Ack पूर्णांकr. */
	ei_local->dमुख्यg &= ~0x01;

	le16_to_cpus(&hdr->count);
पूर्ण


/*
 * Block input and output, similar to the Crynwr packet driver. If
 * you are porting to a new ethercard, look at the packet driver
 * source क्रम hपूर्णांकs. The NEx000 करोesn't share the on-board packet
 * memory -- you have to put the packet out through the "remote DMA"
 * dataport using ei_outb.
 */
अटल व्योम ax_block_input(काष्ठा net_device *dev, पूर्णांक count,
			   काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	व्योम __iomem *nic_base = ei_local->mem;
	अक्षर *buf = skb->data;

	अगर (ei_local->dमुख्यg) अणु
		netdev_err(dev,
			"DMAing conflict in %s "
			"[DMAstat:%d][irqlock:%d].\n",
			__func__,
			ei_local->dमुख्यg, ei_local->irqlock);
		वापस;
	पूर्ण

	ei_local->dमुख्यg |= 0x01;

	ei_outb(E8390_NODMA+E8390_PAGE0+E8390_START, nic_base + NE_CMD);
	ei_outb(count & 0xff, nic_base + EN0_RCNTLO);
	ei_outb(count >> 8, nic_base + EN0_RCNTHI);
	ei_outb(ring_offset & 0xff, nic_base + EN0_RSARLO);
	ei_outb(ring_offset >> 8, nic_base + EN0_RSARHI);
	ei_outb(E8390_RREAD+E8390_START, nic_base + NE_CMD);

	अगर (ei_local->word16) अणु
		ioपढ़ो16_rep(nic_base + NE_DATAPORT, buf, count >> 1);
		अगर (count & 0x01)
			buf[count-1] = ei_inb(nic_base + NE_DATAPORT);

	पूर्ण अन्यथा अणु
		ioपढ़ो8_rep(nic_base + NE_DATAPORT, buf, count);
	पूर्ण

	ei_local->dमुख्यg &= ~1;
पूर्ण

अटल व्योम ax_block_output(काष्ठा net_device *dev, पूर्णांक count,
			    स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	व्योम __iomem *nic_base = ei_local->mem;
	अचिन्हित दीर्घ dma_start;

	/*
	 * Round the count up क्रम word ग_लिखोs. Do we need to करो this?
	 * What effect will an odd byte count have on the 8390?  I
	 * should check someday.
	 */
	अगर (ei_local->word16 && (count & 0x01))
		count++;

	/* This *shouldn't* happen. If it does, it's the last thing you'll see */
	अगर (ei_local->dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in %s."
			"[DMAstat:%d][irqlock:%d]\n",
			__func__,
		       ei_local->dमुख्यg, ei_local->irqlock);
		वापस;
	पूर्ण

	ei_local->dमुख्यg |= 0x01;
	/* We should alपढ़ोy be in page 0, but to be safe... */
	ei_outb(E8390_PAGE0+E8390_START+E8390_NODMA, nic_base + NE_CMD);

	ei_outb(ENISR_RDC, nic_base + EN0_ISR);

	/* Now the normal output. */
	ei_outb(count & 0xff, nic_base + EN0_RCNTLO);
	ei_outb(count >> 8, nic_base + EN0_RCNTHI);
	ei_outb(0x00, nic_base + EN0_RSARLO);
	ei_outb(start_page, nic_base + EN0_RSARHI);

	ei_outb(E8390_RWRITE+E8390_START, nic_base + NE_CMD);
	अगर (ei_local->word16)
		ioग_लिखो16_rep(nic_base + NE_DATAPORT, buf, count >> 1);
	अन्यथा
		ioग_लिखो8_rep(nic_base + NE_DATAPORT, buf, count);

	dma_start = jअगरfies;

	जबतक ((ei_inb(nic_base + EN0_ISR) & ENISR_RDC) == 0) अणु
		अगर (समय_after(jअगरfies, dma_start + 2 * HZ / 100)) अणु /* 20ms */
			netdev_warn(dev, "timeout waiting for Tx RDC.\n");
			ax_reset_8390(dev);
			ax_NS8390_init(dev, 1);
			अवरोध;
		पूर्ण
	पूर्ण

	ei_outb(ENISR_RDC, nic_base + EN0_ISR);	/* Ack पूर्णांकr. */
	ei_local->dमुख्यg &= ~0x01;
पूर्ण

/* definitions क्रम accessing MII/EEPROM पूर्णांकerface */

#घोषणा AX_MEMR			EI_SHIFT(0x14)
#घोषणा AX_MEMR_MDC		BIT(0)
#घोषणा AX_MEMR_Mसूची		BIT(1)
#घोषणा AX_MEMR_MDI		BIT(2)
#घोषणा AX_MEMR_MDO		BIT(3)
#घोषणा AX_MEMR_EECS		BIT(4)
#घोषणा AX_MEMR_EEI		BIT(5)
#घोषणा AX_MEMR_EEO		BIT(6)
#घोषणा AX_MEMR_EECLK		BIT(7)

अटल व्योम ax_handle_link_change(काष्ठा net_device *dev)
अणु
	काष्ठा ax_device  *ax = to_ax_dev(dev);
	काष्ठा phy_device *phy_dev = dev->phydev;
	पूर्णांक status_change = 0;

	अगर (phy_dev->link && ((ax->speed != phy_dev->speed) ||
			     (ax->duplex != phy_dev->duplex))) अणु

		ax->speed = phy_dev->speed;
		ax->duplex = phy_dev->duplex;
		status_change = 1;
	पूर्ण

	अगर (phy_dev->link != ax->link) अणु
		अगर (!phy_dev->link) अणु
			ax->speed = 0;
			ax->duplex = -1;
		पूर्ण
		ax->link = phy_dev->link;

		status_change = 1;
	पूर्ण

	अगर (status_change)
		phy_prपूर्णांक_status(phy_dev);
पूर्ण

अटल पूर्णांक ax_mii_probe(काष्ठा net_device *dev)
अणु
	काष्ठा ax_device  *ax = to_ax_dev(dev);
	काष्ठा phy_device *phy_dev = शून्य;
	पूर्णांक ret;

	/* find the first phy */
	phy_dev = phy_find_first(ax->mii_bus);
	अगर (!phy_dev) अणु
		netdev_err(dev, "no PHY found\n");
		वापस -ENODEV;
	पूर्ण

	ret = phy_connect_direct(dev, phy_dev, ax_handle_link_change,
				 PHY_INTERFACE_MODE_MII);
	अगर (ret) अणु
		netdev_err(dev, "Could not attach to PHY\n");
		वापस ret;
	पूर्ण

	phy_set_max_speed(phy_dev, SPEED_100);

	netdev_info(dev, "PHY driver [%s] (mii_bus:phy_addr=%s, irq=%d)\n",
		    phy_dev->drv->name, phydev_name(phy_dev), phy_dev->irq);

	वापस 0;
पूर्ण

अटल व्योम ax_phy_चयन(काष्ठा net_device *dev, पूर्णांक on)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	काष्ठा ax_device *ax = to_ax_dev(dev);

	u8 reg_gpoc =  ax->plat->gpoc_val;

	अगर (!!on)
		reg_gpoc &= ~AX_GPOC_PPDSET;
	अन्यथा
		reg_gpoc |= AX_GPOC_PPDSET;

	ei_outb(reg_gpoc, ei_local->mem + EI_SHIFT(0x17));
पूर्ण

अटल व्योम ax_bb_mdc(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक level)
अणु
	काष्ठा ax_device *ax = container_of(ctrl, काष्ठा ax_device, bb_ctrl);

	अगर (level)
		ax->reg_memr |= AX_MEMR_MDC;
	अन्यथा
		ax->reg_memr &= ~AX_MEMR_MDC;

	ei_outb(ax->reg_memr, ax->addr_memr);
पूर्ण

अटल व्योम ax_bb_dir(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक output)
अणु
	काष्ठा ax_device *ax = container_of(ctrl, काष्ठा ax_device, bb_ctrl);

	अगर (output)
		ax->reg_memr &= ~AX_MEMR_Mसूची;
	अन्यथा
		ax->reg_memr |= AX_MEMR_Mसूची;

	ei_outb(ax->reg_memr, ax->addr_memr);
पूर्ण

अटल व्योम ax_bb_set_data(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक value)
अणु
	काष्ठा ax_device *ax = container_of(ctrl, काष्ठा ax_device, bb_ctrl);

	अगर (value)
		ax->reg_memr |= AX_MEMR_MDO;
	अन्यथा
		ax->reg_memr &= ~AX_MEMR_MDO;

	ei_outb(ax->reg_memr, ax->addr_memr);
पूर्ण

अटल पूर्णांक ax_bb_get_data(काष्ठा mdiobb_ctrl *ctrl)
अणु
	काष्ठा ax_device *ax = container_of(ctrl, काष्ठा ax_device, bb_ctrl);
	पूर्णांक reg_memr = ei_inb(ax->addr_memr);

	वापस reg_memr & AX_MEMR_MDI ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा mdiobb_ops bb_ops = अणु
	.owner = THIS_MODULE,
	.set_mdc = ax_bb_mdc,
	.set_mdio_dir = ax_bb_dir,
	.set_mdio_data = ax_bb_set_data,
	.get_mdio_data = ax_bb_get_data,
पूर्ण;

अटल पूर्णांक ax_mii_init(काष्ठा net_device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev.parent);
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	काष्ठा ax_device *ax = to_ax_dev(dev);
	पूर्णांक err;

	ax->bb_ctrl.ops = &bb_ops;
	ax->addr_memr = ei_local->mem + AX_MEMR;
	ax->mii_bus = alloc_mdio_bitbang(&ax->bb_ctrl);
	अगर (!ax->mii_bus) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	ax->mii_bus->name = "ax88796_mii_bus";
	ax->mii_bus->parent = dev->dev.parent;
	snम_लिखो(ax->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pdev->name, pdev->id);

	err = mdiobus_रेजिस्टर(ax->mii_bus);
	अगर (err)
		जाओ out_मुक्त_mdio_bitbang;

	वापस 0;

 out_मुक्त_mdio_bitbang:
	मुक्त_mdio_bitbang(ax->mii_bus);
 out:
	वापस err;
पूर्ण

अटल पूर्णांक ax_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ax_device *ax = to_ax_dev(dev);
	पूर्णांक ret;

	netdev_dbg(dev, "open\n");

	ret = ax_mii_init(dev);
	अगर (ret)
		जाओ failed_mii;

	अगर (ax->plat->check_irq)
		ret = request_irq(dev->irq, ax_ei_पूर्णांकerrupt_filtered,
				  ax->irqflags, dev->name, dev);
	अन्यथा
		ret = request_irq(dev->irq, ax_ei_पूर्णांकerrupt, ax->irqflags,
				  dev->name, dev);
	अगर (ret)
		जाओ failed_request_irq;

	/* turn the phy on (अगर turned off) */
	ax_phy_चयन(dev, 1);

	ret = ax_mii_probe(dev);
	अगर (ret)
		जाओ failed_mii_probe;
	phy_start(dev->phydev);

	ret = ax_ei_खोलो(dev);
	अगर (ret)
		जाओ failed_ax_ei_खोलो;

	ax->running = 1;

	वापस 0;

 failed_ax_ei_खोलो:
	phy_disconnect(dev->phydev);
 failed_mii_probe:
	ax_phy_चयन(dev, 0);
	मुक्त_irq(dev->irq, dev);
 failed_request_irq:
	/* unरेजिस्टर mdiobus */
	mdiobus_unरेजिस्टर(ax->mii_bus);
	मुक्त_mdio_bitbang(ax->mii_bus);
 failed_mii:
	वापस ret;
पूर्ण

अटल पूर्णांक ax_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ax_device *ax = to_ax_dev(dev);

	netdev_dbg(dev, "close\n");

	ax->running = 0;
	wmb();

	ax_ei_बंद(dev);

	/* turn the phy off */
	ax_phy_चयन(dev, 0);
	phy_disconnect(dev->phydev);

	मुक्त_irq(dev->irq, dev);

	mdiobus_unरेजिस्टर(ax->mii_bus);
	मुक्त_mdio_bitbang(ax->mii_bus);
	वापस 0;
पूर्ण

अटल पूर्णांक ax_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा phy_device *phy_dev = dev->phydev;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (!phy_dev)
		वापस -ENODEV;

	वापस phy_mii_ioctl(phy_dev, req, cmd);
पूर्ण

/* ethtool ops */

अटल व्योम ax_get_drvinfo(काष्ठा net_device *dev,
			   काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev.parent);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pdev->name, माप(info->bus_info));
पूर्ण

अटल u32 ax_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	वापस ei_local->msg_enable;
पूर्ण

अटल व्योम ax_set_msglevel(काष्ठा net_device *dev, u32 v)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	ei_local->msg_enable = v;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ax_ethtool_ops = अणु
	.get_drvinfo		= ax_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_msglevel		= ax_get_msglevel,
	.set_msglevel		= ax_set_msglevel,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
पूर्ण;

#अगर_घोषित CONFIG_AX88796_93CX6
अटल व्योम ax_eeprom_रेजिस्टर_पढ़ो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा ei_device *ei_local = eeprom->data;
	u8 reg = ei_inb(ei_local->mem + AX_MEMR);

	eeprom->reg_data_in = reg & AX_MEMR_EEI;
	eeprom->reg_data_out = reg & AX_MEMR_EEO; /* Input pin */
	eeprom->reg_data_घड़ी = reg & AX_MEMR_EECLK;
	eeprom->reg_chip_select = reg & AX_MEMR_EECS;
पूर्ण

अटल व्योम ax_eeprom_रेजिस्टर_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा ei_device *ei_local = eeprom->data;
	u8 reg = ei_inb(ei_local->mem + AX_MEMR);

	reg &= ~(AX_MEMR_EEI | AX_MEMR_EECLK | AX_MEMR_EECS);

	अगर (eeprom->reg_data_in)
		reg |= AX_MEMR_EEI;
	अगर (eeprom->reg_data_घड़ी)
		reg |= AX_MEMR_EECLK;
	अगर (eeprom->reg_chip_select)
		reg |= AX_MEMR_EECS;

	ei_outb(reg, ei_local->mem + AX_MEMR);
	udelay(10);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops ax_netdev_ops = अणु
	.nकरो_खोलो		= ax_खोलो,
	.nकरो_stop		= ax_बंद,
	.nकरो_करो_ioctl		= ax_ioctl,

	.nकरो_start_xmit		= ax_ei_start_xmit,
	.nकरो_tx_समयout		= ax_ei_tx_समयout,
	.nकरो_get_stats		= ax_ei_get_stats,
	.nकरो_set_rx_mode	= ax_ei_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= ax_ei_poll,
#पूर्ण_अगर
पूर्ण;

/* setup code */

अटल व्योम ax_initial_setup(काष्ठा net_device *dev, काष्ठा ei_device *ei_local)
अणु
	व्योम __iomem *ioaddr = ei_local->mem;
	काष्ठा ax_device *ax = to_ax_dev(dev);

	/* Select page 0 */
	ei_outb(E8390_NODMA + E8390_PAGE0 + E8390_STOP, ioaddr + E8390_CMD);

	/* set to byte access */
	ei_outb(ax->plat->dcr_val & ~1, ioaddr + EN0_DCFG);
	ei_outb(ax->plat->gpoc_val, ioaddr + EI_SHIFT(0x17));
पूर्ण

/*
 * ax_init_dev
 *
 * initialise the specअगरied device, taking care to note the MAC
 * address it may alपढ़ोy have (अगर configured), ensure
 * the device is पढ़ोy to be used by lib8390.c and रेजिस्टरd with
 * the network layer.
 */
अटल पूर्णांक ax_init_dev(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	काष्ठा ax_device *ax = to_ax_dev(dev);
	व्योम __iomem *ioaddr = ei_local->mem;
	अचिन्हित पूर्णांक start_page;
	अचिन्हित पूर्णांक stop_page;
	पूर्णांक ret;
	पूर्णांक i;

	ret = ax_initial_check(dev);
	अगर (ret)
		जाओ err_out;

	/* setup goes here */

	ax_initial_setup(dev, ei_local);

	/* पढ़ो the mac from the card prom अगर we need it */

	अगर (ax->plat->flags & AXFLG_HAS_EEPROM) अणु
		अचिन्हित अक्षर SA_prom[32];

		ei_outb(6, ioaddr + EN0_RCNTLO);
		ei_outb(0, ioaddr + EN0_RCNTHI);
		ei_outb(0, ioaddr + EN0_RSARLO);
		ei_outb(0, ioaddr + EN0_RSARHI);
		ei_outb(E8390_RREAD + E8390_START, ioaddr + NE_CMD);
		क्रम (i = 0; i < माप(SA_prom); i += 2) अणु
			SA_prom[i] = ei_inb(ioaddr + NE_DATAPORT);
			SA_prom[i + 1] = ei_inb(ioaddr + NE_DATAPORT);
		पूर्ण
		ei_outb(ENISR_RDC, ioaddr + EN0_ISR);	/* Ack पूर्णांकr. */

		अगर (ax->plat->wordlength == 2)
			क्रम (i = 0; i < 16; i++)
				SA_prom[i] = SA_prom[i+i];

		स_नकल(dev->dev_addr, SA_prom, ETH_ALEN);
	पूर्ण

#अगर_घोषित CONFIG_AX88796_93CX6
	अगर (ax->plat->flags & AXFLG_HAS_93CX6) अणु
		अचिन्हित अक्षर mac_addr[ETH_ALEN];
		काष्ठा eeprom_93cx6 eeprom;

		eeprom.data = ei_local;
		eeprom.रेजिस्टर_पढ़ो = ax_eeprom_रेजिस्टर_पढ़ो;
		eeprom.रेजिस्टर_ग_लिखो = ax_eeprom_रेजिस्टर_ग_लिखो;
		eeprom.width = PCI_EEPROM_WIDTH_93C56;

		eeprom_93cx6_multiपढ़ो(&eeprom, 0,
				       (__le16 __क्रमce *)mac_addr,
				       माप(mac_addr) >> 1);

		स_नकल(dev->dev_addr, mac_addr, ETH_ALEN);
	पूर्ण
#पूर्ण_अगर
	अगर (ax->plat->wordlength == 2) अणु
		/* We must set the 8390 क्रम word mode. */
		ei_outb(ax->plat->dcr_val, ei_local->mem + EN0_DCFG);
		start_page = NESM_START_PG;
		stop_page = NESM_STOP_PG;
	पूर्ण अन्यथा अणु
		start_page = NE1SM_START_PG;
		stop_page = NE1SM_STOP_PG;
	पूर्ण

	/* load the mac-address from the device */
	अगर (ax->plat->flags & AXFLG_MAC_FROMDEV) अणु
		ei_outb(E8390_NODMA + E8390_PAGE1 + E8390_STOP,
			ei_local->mem + E8390_CMD); /* 0x61 */
		क्रम (i = 0; i < ETH_ALEN; i++)
			dev->dev_addr[i] =
				ei_inb(ioaddr + EN1_PHYS_SHIFT(i));
	पूर्ण

	अगर ((ax->plat->flags & AXFLG_MAC_FROMPLATFORM) &&
	    ax->plat->mac_addr)
		स_नकल(dev->dev_addr, ax->plat->mac_addr, ETH_ALEN);

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		eth_hw_addr_अक्रमom(dev);
		dev_info(&dev->dev, "Using random MAC address: %pM\n",
			 dev->dev_addr);
	पूर्ण

	ax_reset_8390(dev);

	ei_local->name = "AX88796";
	ei_local->tx_start_page = start_page;
	ei_local->stop_page = stop_page;
	ei_local->word16 = (ax->plat->wordlength == 2);
	ei_local->rx_start_page = start_page + TX_PAGES;

#अगर_घोषित PACKETBUF_MEMSIZE
	/* Allow the packet buffer size to be overridden by know-it-alls. */
	ei_local->stop_page = ei_local->tx_start_page + PACKETBUF_MEMSIZE;
#पूर्ण_अगर

	ei_local->reset_8390 = &ax_reset_8390;
	अगर (ax->plat->block_input)
		ei_local->block_input = ax->plat->block_input;
	अन्यथा
		ei_local->block_input = &ax_block_input;
	अगर (ax->plat->block_output)
		ei_local->block_output = ax->plat->block_output;
	अन्यथा
		ei_local->block_output = &ax_block_output;
	ei_local->get_8390_hdr = &ax_get_8390_hdr;
	ei_local->priv = 0;

	dev->netdev_ops = &ax_netdev_ops;
	dev->ethtool_ops = &ax_ethtool_ops;

	ax_NS8390_init(dev, 0);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ err_out;

	netdev_info(dev, "%dbit, irq %d, %lx, MAC: %pM\n",
		    ei_local->word16 ? 16 : 8, dev->irq, dev->base_addr,
		    dev->dev_addr);

	वापस 0;

 err_out:
	वापस ret;
पूर्ण

अटल पूर्णांक ax_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	काष्ठा ax_device *ax = to_ax_dev(dev);
	काष्ठा resource *mem;

	unरेजिस्टर_netdev(dev);

	iounmap(ei_local->mem);
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(mem->start, resource_size(mem));

	अगर (ax->map2) अणु
		iounmap(ax->map2);
		mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		release_mem_region(mem->start, resource_size(mem));
	पूर्ण

	platक्रमm_set_drvdata(pdev, शून्य);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

/*
 * ax_probe
 *
 * This is the entry poपूर्णांक when the platक्रमm device प्रणाली uses to
 * notअगरy us of a new device to attach to. Allocate memory, find the
 * resources and inक्रमmation passed, and map the necessary रेजिस्टरs.
 */
अटल पूर्णांक ax_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा ei_device *ei_local;
	काष्ठा ax_device *ax;
	काष्ठा resource *irq, *mem, *mem2;
	अचिन्हित दीर्घ mem_size, mem2_size = 0;
	पूर्णांक ret = 0;

	dev = ax__alloc_ei_netdev(माप(काष्ठा ax_device));
	अगर (dev == शून्य)
		वापस -ENOMEM;

	/* ok, let's setup our device */
	SET_NETDEV_DEV(dev, &pdev->dev);
	ei_local = netdev_priv(dev);
	ax = to_ax_dev(dev);

	ax->plat = dev_get_platdata(&pdev->dev);
	platक्रमm_set_drvdata(pdev, dev);

	ei_local->rxcr_base = ax->plat->rcr_val;

	/* find the platक्रमm resources */
	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq) अणु
		dev_err(&pdev->dev, "no IRQ specified\n");
		ret = -ENXIO;
		जाओ निकास_mem;
	पूर्ण

	dev->irq = irq->start;
	ax->irqflags = irq->flags & IRQF_TRIGGER_MASK;

	अगर (irq->flags &  IORESOURCE_IRQ_SHAREABLE)
		ax->irqflags |= IRQF_SHARED;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem) अणु
		dev_err(&pdev->dev, "no MEM specified\n");
		ret = -ENXIO;
		जाओ निकास_mem;
	पूर्ण

	mem_size = resource_size(mem);

	/*
	 * setup the रेजिस्टर offsets from either the platक्रमm data or
	 * by using the size of the resource provided
	 */
	अगर (ax->plat->reg_offsets)
		ei_local->reg_offset = ax->plat->reg_offsets;
	अन्यथा अणु
		ei_local->reg_offset = ax->reg_offsets;
		क्रम (ret = 0; ret < 0x18; ret++)
			ax->reg_offsets[ret] = (mem_size / 0x18) * ret;
	पूर्ण

	अगर (!request_mem_region(mem->start, mem_size, pdev->name)) अणु
		dev_err(&pdev->dev, "cannot reserve registers\n");
		ret = -ENXIO;
		जाओ निकास_mem;
	पूर्ण

	ei_local->mem = ioremap(mem->start, mem_size);
	dev->base_addr = (अचिन्हित दीर्घ)ei_local->mem;

	अगर (ei_local->mem == शून्य) अणु
		dev_err(&pdev->dev, "Cannot ioremap area %pR\n", mem);

		ret = -ENXIO;
		जाओ निकास_req;
	पूर्ण

	/* look क्रम reset area */
	mem2 = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!mem2) अणु
		अगर (!ax->plat->reg_offsets) अणु
			क्रम (ret = 0; ret < 0x20; ret++)
				ax->reg_offsets[ret] = (mem_size / 0x20) * ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		mem2_size = resource_size(mem2);

		अगर (!request_mem_region(mem2->start, mem2_size, pdev->name)) अणु
			dev_err(&pdev->dev, "cannot reserve registers\n");
			ret = -ENXIO;
			जाओ निकास_mem1;
		पूर्ण

		ax->map2 = ioremap(mem2->start, mem2_size);
		अगर (!ax->map2) अणु
			dev_err(&pdev->dev, "cannot map reset register\n");
			ret = -ENXIO;
			जाओ निकास_mem2;
		पूर्ण

		ei_local->reg_offset[0x1f] = ax->map2 - ei_local->mem;
	पूर्ण

	/* got resources, now initialise and रेजिस्टर device */
	ret = ax_init_dev(dev);
	अगर (!ret)
		वापस 0;

	अगर (!ax->map2)
		जाओ निकास_mem1;

	iounmap(ax->map2);

 निकास_mem2:
	अगर (mem2)
		release_mem_region(mem2->start, mem2_size);

 निकास_mem1:
	iounmap(ei_local->mem);

 निकास_req:
	release_mem_region(mem->start, mem_size);

 निकास_mem:
	platक्रमm_set_drvdata(pdev, शून्य);
	मुक्त_netdev(dev);

	वापस ret;
पूर्ण

/* suspend and resume */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ax_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(dev);
	काष्ठा ax_device *ax = to_ax_dev(ndev);

	ax->resume_खोलो = ax->running;

	netअगर_device_detach(ndev);
	ax_बंद(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक ax_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा ax_device *ax = to_ax_dev(ndev);

	ax_initial_setup(ndev, netdev_priv(ndev));
	ax_NS8390_init(ndev, ax->resume_खोलो);
	netअगर_device_attach(ndev);

	अगर (ax->resume_खोलो)
		ax_खोलो(ndev);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा ax_suspend शून्य
#घोषणा ax_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver axdrv = अणु
	.driver	= अणु
		.name		= "ax88796",
	पूर्ण,
	.probe		= ax_probe,
	.हटाओ		= ax_हटाओ,
	.suspend	= ax_suspend,
	.resume		= ax_resume,
पूर्ण;

module_platक्रमm_driver(axdrv);

MODULE_DESCRIPTION("AX88796 10/100 Ethernet platform driver");
MODULE_AUTHOR("Ben Dooks, <ben@simtec.co.uk>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ax88796");
