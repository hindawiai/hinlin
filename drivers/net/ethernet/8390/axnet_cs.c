<शैली गुरु>
/*======================================================================

    A PCMCIA ethernet driver क्रम Asix AX88190-based cards

    The Asix AX88190 is a NS8390-derived chipset with a few nasty
    idiosyncracies that make it very inconvenient to support with a
    standard 8390 driver.  This driver is based on pcnet_cs, with the
    tweaked 8390 code grafted on the end.  Much of what I did was to
    clean up and update a similar driver supplied by Asix, which was
    adapted by William Lee, william@asix.com.tw.

    Copyright (C) 2001 David A. Hinds -- dahinds@users.sourceक्रमge.net

    axnet_cs.c 1.28 2002/06/29 06:27:37

    The network driver code is based on Donald Becker's NE2000 code:

    Written 1992,1993 by Donald Becker.
    Copyright 1993 United States Government as represented by the
    Director, National Security Agency.  This software may be used and
    distributed according to the terms of the GNU General Public License,
    incorporated herein by reference.
    Donald Becker may be reached at becker@scyld.com

======================================================================*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mii.h>
#समावेश "8390.h"

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

#घोषणा AXNET_CMD	0x00
#घोषणा AXNET_DATAPORT	0x10	/* NatSemi-defined port winकरोw offset. */
#घोषणा AXNET_RESET	0x1f	/* Issue a पढ़ो to reset, a ग_लिखो to clear. */
#घोषणा AXNET_MII_EEP	0x14	/* Offset of MII access port */
#घोषणा AXNET_TEST	0x15	/* Offset of TEST Register port */
#घोषणा AXNET_GPIO	0x17	/* Offset of General Purpose Register Port */

#घोषणा AXNET_START_PG	0x40	/* First page of TX buffer */
#घोषणा AXNET_STOP_PG	0x80	/* Last page +1 of RX ring */

#घोषणा AXNET_RDC_TIMEOUT 0x02	/* Max रुको in jअगरfies क्रम Tx RDC */

#घोषणा IS_AX88190	0x0001
#घोषणा IS_AX88790	0x0002

/*====================================================================*/

/* Module parameters */

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("Asix AX88190 PCMCIA ethernet driver");
MODULE_LICENSE("GPL");


/*====================================================================*/

अटल पूर्णांक axnet_config(काष्ठा pcmcia_device *link);
अटल व्योम axnet_release(काष्ठा pcmcia_device *link);
अटल पूर्णांक axnet_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक axnet_बंद(काष्ठा net_device *dev);
अटल पूर्णांक axnet_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल netdev_tx_t axnet_start_xmit(काष्ठा sk_buff *skb,
					  काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);
अटल व्योम axnet_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल irqवापस_t ei_irq_wrapper(पूर्णांक irq, व्योम *dev_id);
अटल व्योम ei_watchकरोg(काष्ठा समयr_list *t);
अटल व्योम axnet_reset_8390(काष्ठा net_device *dev);

अटल पूर्णांक mdio_पढ़ो(अचिन्हित पूर्णांक addr, पूर्णांक phy_id, पूर्णांक loc);
अटल व्योम mdio_ग_लिखो(अचिन्हित पूर्णांक addr, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक value);

अटल व्योम get_8390_hdr(काष्ठा net_device *,
			 काष्ठा e8390_pkt_hdr *, पूर्णांक);
अटल व्योम block_input(काष्ठा net_device *dev, पूर्णांक count,
			काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम block_output(काष्ठा net_device *dev, पूर्णांक count,
			 स्थिर u_अक्षर *buf, स्थिर पूर्णांक start_page);

अटल व्योम axnet_detach(काष्ठा pcmcia_device *p_dev);

अटल व्योम AX88190_init(काष्ठा net_device *dev, पूर्णांक startp);
अटल पूर्णांक ax_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक ax_बंद(काष्ठा net_device *dev);
अटल irqवापस_t ax_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

/*====================================================================*/

काष्ठा axnet_dev अणु
	काष्ठा pcmcia_device	*p_dev;
	caddr_t	base;
	काष्ठा समयr_list	watchकरोg;
	पूर्णांक	stale, fast_poll;
	u_लघु	link_status;
	u_अक्षर	duplex_flag;
	पूर्णांक	phy_id;
	पूर्णांक	flags;
	पूर्णांक	active_low;
पूर्ण;

अटल अंतरभूत काष्ठा axnet_dev *PRIV(काष्ठा net_device *dev)
अणु
	व्योम *p = (अक्षर *)netdev_priv(dev) + माप(काष्ठा ei_device);
	वापस p;
पूर्ण

अटल स्थिर काष्ठा net_device_ops axnet_netdev_ops = अणु
	.nकरो_खोलो 		= axnet_खोलो,
	.nकरो_stop		= axnet_बंद,
	.nकरो_करो_ioctl		= axnet_ioctl,
	.nकरो_start_xmit		= axnet_start_xmit,
	.nकरो_tx_समयout		= axnet_tx_समयout,
	.nकरो_get_stats		= get_stats,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक axnet_probe(काष्ठा pcmcia_device *link)
अणु
    काष्ठा axnet_dev *info;
    काष्ठा net_device *dev;
    काष्ठा ei_device *ei_local;

    dev_dbg(&link->dev, "axnet_attach()\n");

    dev = alloc_etherdev(माप(काष्ठा ei_device) + माप(काष्ठा axnet_dev));
    अगर (!dev)
	वापस -ENOMEM;

    ei_local = netdev_priv(dev);
    spin_lock_init(&ei_local->page_lock);

    info = PRIV(dev);
    info->p_dev = link;
    link->priv = dev;
    link->config_flags |= CONF_ENABLE_IRQ;

    dev->netdev_ops = &axnet_netdev_ops;

    dev->watchकरोg_समयo = TX_TIMEOUT;

    वापस axnet_config(link);
पूर्ण /* axnet_attach */

अटल व्योम axnet_detach(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;

    dev_dbg(&link->dev, "axnet_detach(0x%p)\n", link);

    unरेजिस्टर_netdev(dev);

    axnet_release(link);

    मुक्त_netdev(dev);
पूर्ण /* axnet_detach */

/*======================================================================

    This probes क्रम a card's hardware address by पढ़ोing the PROM.

======================================================================*/

अटल पूर्णांक get_prom(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    पूर्णांक i, j;

    /* This is based on drivers/net/ethernet/8390/ne.c */
    काष्ठा अणु
	u_अक्षर value, offset;
    पूर्ण program_seq[] = अणु
	अणुE8390_NODMA+E8390_PAGE0+E8390_STOP, E8390_CMDपूर्ण, /* Select page 0*/
	अणु0x01,	EN0_DCFGपूर्ण,	/* Set word-wide access. */
	अणु0x00,	EN0_RCNTLOपूर्ण,	/* Clear the count regs. */
	अणु0x00,	EN0_RCNTHIपूर्ण,
	अणु0x00,	EN0_IMRपूर्ण,	/* Mask completion irq. */
	अणु0xFF,	EN0_ISRपूर्ण,
	अणुE8390_RXOFF|0x40, EN0_RXCRपूर्ण,	/* 0x60  Set to monitor */
	अणुE8390_TXOFF, EN0_TXCRपूर्ण,	/* 0x02  and loopback mode. */
	अणु0x10,	EN0_RCNTLOपूर्ण,
	अणु0x00,	EN0_RCNTHIपूर्ण,
	अणु0x00,	EN0_RSARLOपूर्ण,	/* DMA starting at 0x0400. */
	अणु0x04,	EN0_RSARHIपूर्ण,
	अणुE8390_RREAD+E8390_START, E8390_CMDपूर्ण,
    पूर्ण;

    /* Not much of a test, but the alternatives are messy */
    अगर (link->config_base != 0x03c0)
	वापस 0;

    axnet_reset_8390(dev);
    mdelay(10);

    क्रम (i = 0; i < ARRAY_SIZE(program_seq); i++)
	outb_p(program_seq[i].value, ioaddr + program_seq[i].offset);

    क्रम (i = 0; i < 6; i += 2) अणु
	j = inw(ioaddr + AXNET_DATAPORT);
	dev->dev_addr[i] = j & 0xff;
	dev->dev_addr[i+1] = j >> 8;
    पूर्ण
    वापस 1;
पूर्ण /* get_prom */

अटल पूर्णांक try_io_port(काष्ठा pcmcia_device *link)
अणु
    पूर्णांक j, ret;
    link->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
    link->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
    अगर (link->resource[0]->end == 32) अणु
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	/* क्रम master/slave multअगरunction cards */
	अगर (link->resource[1]->end > 0)
	    link->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
    पूर्ण अन्यथा अणु
	/* This should be two 16-port winकरोws */
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	link->resource[1]->flags |= IO_DATA_PATH_WIDTH_16;
    पूर्ण
    अगर (link->resource[0]->start == 0) अणु
	क्रम (j = 0; j < 0x400; j += 0x20) अणु
	    link->resource[0]->start = j ^ 0x300;
	    link->resource[1]->start = (j ^ 0x300) + 0x10;
	    link->io_lines = 16;
	    ret = pcmcia_request_io(link);
	    अगर (ret == 0)
		    वापस ret;
	पूर्ण
	वापस ret;
    पूर्ण अन्यथा अणु
	वापस pcmcia_request_io(link);
    पूर्ण
पूर्ण

अटल पूर्णांक axnet_configcheck(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	अगर (p_dev->config_index == 0)
		वापस -EINVAL;

	p_dev->config_index = 0x05;
	अगर (p_dev->resource[0]->end + p_dev->resource[1]->end < 32)
		वापस -ENODEV;

	वापस try_io_port(p_dev);
पूर्ण

अटल पूर्णांक axnet_config(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा axnet_dev *info = PRIV(dev);
    पूर्णांक i, j, j2, ret;

    dev_dbg(&link->dev, "axnet_config(0x%p)\n", link);

    /* करोn't trust the CIS on this; Linksys got it wrong */
    link->config_regs = 0x63;
    link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;
    ret = pcmcia_loop_config(link, axnet_configcheck, शून्य);
    अगर (ret != 0)
	जाओ failed;

    अगर (!link->irq)
	    जाओ failed;

    अगर (resource_size(link->resource[1]) == 8)
	link->config_flags |= CONF_ENABLE_SPKR;
    
    ret = pcmcia_enable_device(link);
    अगर (ret)
	    जाओ failed;

    dev->irq = link->irq;
    dev->base_addr = link->resource[0]->start;

    अगर (!get_prom(link)) अणु
	pr_notice("this is not an AX88190 card!\n");
	pr_notice("use pcnet_cs instead.\n");
	जाओ failed;
    पूर्ण

    ei_status.name = "AX88190";
    ei_status.word16 = 1;
    ei_status.tx_start_page = AXNET_START_PG;
    ei_status.rx_start_page = AXNET_START_PG + TX_PAGES;
    ei_status.stop_page = AXNET_STOP_PG;
    ei_status.reset_8390 = axnet_reset_8390;
    ei_status.get_8390_hdr = get_8390_hdr;
    ei_status.block_input = block_input;
    ei_status.block_output = block_output;

    अगर (inb(dev->base_addr + AXNET_TEST) != 0)
	info->flags |= IS_AX88790;
    अन्यथा
	info->flags |= IS_AX88190;

    अगर (info->flags & IS_AX88790)
	outb(0x10, dev->base_addr + AXNET_GPIO);  /* select Internal PHY */

    info->active_low = 0;

    क्रम (i = 0; i < 32; i++) अणु
	j = mdio_पढ़ो(dev->base_addr + AXNET_MII_EEP, i, 1);
	j2 = mdio_पढ़ो(dev->base_addr + AXNET_MII_EEP, i, 2);
	अगर (j == j2) जारी;
	अगर ((j != 0) && (j != 0xffff)) अवरोध;
    पूर्ण

    अगर (i == 32) अणु
	/* Maybe PHY is in घातer करोwn mode. (PPD_SET = 1)
	   Bit 2 of CCSR is active low. */
	pcmcia_ग_लिखो_config_byte(link, CISREG_CCSR, 0x04);
	क्रम (i = 0; i < 32; i++) अणु
	    j = mdio_पढ़ो(dev->base_addr + AXNET_MII_EEP, i, 1);
	    j2 = mdio_पढ़ो(dev->base_addr + AXNET_MII_EEP, i, 2);
	    अगर (j == j2) जारी;
	    अगर ((j != 0) && (j != 0xffff)) अणु
		info->active_low = 1;
		अवरोध;
	    पूर्ण
	पूर्ण
    पूर्ण

    info->phy_id = (i < 32) ? i : -1;
    SET_NETDEV_DEV(dev, &link->dev);

    अगर (रेजिस्टर_netdev(dev) != 0) अणु
	pr_notice("register_netdev() failed\n");
	जाओ failed;
    पूर्ण

    netdev_info(dev, "Asix AX88%d90: io %#3lx, irq %d, hw_addr %pM\n",
		((info->flags & IS_AX88790) ? 7 : 1),
		dev->base_addr, dev->irq, dev->dev_addr);
    अगर (info->phy_id != -1) अणु
	netdev_dbg(dev, "  MII transceiver at index %d, status %x\n",
		   info->phy_id, j);
    पूर्ण अन्यथा अणु
	netdev_notice(dev, "  No MII transceivers found!\n");
    पूर्ण
    वापस 0;

failed:
    axnet_release(link);
    वापस -ENODEV;
पूर्ण /* axnet_config */

अटल व्योम axnet_release(काष्ठा pcmcia_device *link)
अणु
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक axnet_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक axnet_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;
	काष्ठा axnet_dev *info = PRIV(dev);

	अगर (link->खोलो) अणु
		अगर (info->active_low == 1)
			pcmcia_ग_लिखो_config_byte(link, CISREG_CCSR, 0x04);

		axnet_reset_8390(dev);
		AX88190_init(dev, 1);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण


/*======================================================================

    MII पूर्णांकerface support

======================================================================*/

#घोषणा MDIO_SHIFT_CLK		0x01
#घोषणा MDIO_DATA_WRITE0	0x00
#घोषणा MDIO_DATA_WRITE1	0x08
#घोषणा MDIO_DATA_READ		0x04
#घोषणा MDIO_MASK		0x0f
#घोषणा MDIO_ENB_IN		0x02

अटल व्योम mdio_sync(अचिन्हित पूर्णांक addr)
अणु
    पूर्णांक bits;
    क्रम (bits = 0; bits < 32; bits++) अणु
	outb_p(MDIO_DATA_WRITE1, addr);
	outb_p(MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, addr);
    पूर्ण
पूर्ण

अटल पूर्णांक mdio_पढ़ो(अचिन्हित पूर्णांक addr, पूर्णांक phy_id, पूर्णांक loc)
अणु
    u_पूर्णांक cmd = (0xf6<<10)|(phy_id<<5)|loc;
    पूर्णांक i, retval = 0;

    mdio_sync(addr);
    क्रम (i = 14; i >= 0; i--) अणु
	पूर्णांक dat = (cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
	outb_p(dat, addr);
	outb_p(dat | MDIO_SHIFT_CLK, addr);
    पूर्ण
    क्रम (i = 19; i > 0; i--) अणु
	outb_p(MDIO_ENB_IN, addr);
	retval = (retval << 1) | ((inb_p(addr) & MDIO_DATA_READ) != 0);
	outb_p(MDIO_ENB_IN | MDIO_SHIFT_CLK, addr);
    पूर्ण
    वापस (retval>>1) & 0xffff;
पूर्ण

अटल व्योम mdio_ग_लिखो(अचिन्हित पूर्णांक addr, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक value)
अणु
    u_पूर्णांक cmd = (0x05<<28)|(phy_id<<23)|(loc<<18)|(1<<17)|value;
    पूर्णांक i;

    mdio_sync(addr);
    क्रम (i = 31; i >= 0; i--) अणु
	पूर्णांक dat = (cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
	outb_p(dat, addr);
	outb_p(dat | MDIO_SHIFT_CLK, addr);
    पूर्ण
    क्रम (i = 1; i >= 0; i--) अणु
	outb_p(MDIO_ENB_IN, addr);
	outb_p(MDIO_ENB_IN | MDIO_SHIFT_CLK, addr);
    पूर्ण
पूर्ण

/*====================================================================*/

अटल पूर्णांक axnet_खोलो(काष्ठा net_device *dev)
अणु
    पूर्णांक ret;
    काष्ठा axnet_dev *info = PRIV(dev);
    काष्ठा pcmcia_device *link = info->p_dev;
    अचिन्हित पूर्णांक nic_base = dev->base_addr;
    
    dev_dbg(&link->dev, "axnet_open('%s')\n", dev->name);

    अगर (!pcmcia_dev_present(link))
	वापस -ENODEV;

    outb_p(0xFF, nic_base + EN0_ISR); /* Clear bogus पूर्णांकr. */
    ret = request_irq(dev->irq, ei_irq_wrapper, IRQF_SHARED, "axnet_cs", dev);
    अगर (ret)
	    वापस ret;

    link->खोलो++;

    info->link_status = 0x00;
    समयr_setup(&info->watchकरोg, ei_watchकरोg, 0);
    mod_समयr(&info->watchकरोg, jअगरfies + HZ);

    वापस ax_खोलो(dev);
पूर्ण /* axnet_खोलो */

/*====================================================================*/

अटल पूर्णांक axnet_बंद(काष्ठा net_device *dev)
अणु
    काष्ठा axnet_dev *info = PRIV(dev);
    काष्ठा pcmcia_device *link = info->p_dev;

    dev_dbg(&link->dev, "axnet_close('%s')\n", dev->name);

    ax_बंद(dev);
    मुक्त_irq(dev->irq, dev);
    
    link->खोलो--;
    netअगर_stop_queue(dev);
    del_समयr_sync(&info->watchकरोg);

    वापस 0;
पूर्ण /* axnet_बंद */

/*======================================================================

    Hard reset the card.  This used to छोड़ो क्रम the same period that
    a 8390 reset command required, but that shouldn't be necessary.

======================================================================*/

अटल व्योम axnet_reset_8390(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक nic_base = dev->base_addr;
    पूर्णांक i;

    ei_status.txing = ei_status.dमुख्यg = 0;

    outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, nic_base + E8390_CMD);

    outb(inb(nic_base + AXNET_RESET), nic_base + AXNET_RESET);

    क्रम (i = 0; i < 100; i++) अणु
	अगर ((inb_p(nic_base+EN0_ISR) & ENISR_RESET) != 0)
	    अवरोध;
	udelay(100);
    पूर्ण
    outb_p(ENISR_RESET, nic_base + EN0_ISR); /* Ack पूर्णांकr. */
    
    अगर (i == 100)
	netdev_err(dev, "axnet_reset_8390() did not complete\n");
    
पूर्ण /* axnet_reset_8390 */

/*====================================================================*/

अटल irqवापस_t ei_irq_wrapper(पूर्णांक irq, व्योम *dev_id)
अणु
    काष्ठा net_device *dev = dev_id;
    PRIV(dev)->stale = 0;
    वापस ax_पूर्णांकerrupt(irq, dev_id);
पूर्ण

अटल व्योम ei_watchकरोg(काष्ठा समयr_list *t)
अणु
    काष्ठा axnet_dev *info = from_समयr(info, t, watchकरोg);
    काष्ठा net_device *dev = info->p_dev->priv;
    अचिन्हित पूर्णांक nic_base = dev->base_addr;
    अचिन्हित पूर्णांक mii_addr = nic_base + AXNET_MII_EEP;
    u_लघु link;

    अगर (!netअगर_device_present(dev)) जाओ reschedule;

    /* Check क्रम pending पूर्णांकerrupt with expired latency समयr: with
       this, we can limp aदीर्घ even अगर the पूर्णांकerrupt is blocked */
    अगर (info->stale++ && (inb_p(nic_base + EN0_ISR) & ENISR_ALL)) अणु
	अगर (!info->fast_poll)
	    netdev_info(dev, "interrupt(s) dropped!\n");
	ei_irq_wrapper(dev->irq, dev);
	info->fast_poll = HZ;
    पूर्ण
    अगर (info->fast_poll) अणु
	info->fast_poll--;
	info->watchकरोg.expires = jअगरfies + 1;
	add_समयr(&info->watchकरोg);
	वापस;
    पूर्ण

    अगर (info->phy_id < 0)
	जाओ reschedule;
    link = mdio_पढ़ो(mii_addr, info->phy_id, 1);
    अगर (!link || (link == 0xffff)) अणु
	netdev_info(dev, "MII is missing!\n");
	info->phy_id = -1;
	जाओ reschedule;
    पूर्ण

    link &= 0x0004;
    अगर (link != info->link_status) अणु
	u_लघु p = mdio_पढ़ो(mii_addr, info->phy_id, 5);
	netdev_info(dev, "%s link beat\n", link ? "found" : "lost");
	अगर (link) अणु
	    info->duplex_flag = (p & 0x0140) ? 0x80 : 0x00;
	    अगर (p)
		netdev_info(dev, "autonegotiation complete: %dbaseT-%cD selected\n",
			    (p & 0x0180) ? 100 : 10, (p & 0x0140) ? 'F' : 'H');
	    अन्यथा
		netdev_info(dev, "link partner did not autonegotiate\n");
	    AX88190_init(dev, 1);
	पूर्ण
	info->link_status = link;
    पूर्ण

reschedule:
    info->watchकरोg.expires = jअगरfies + HZ;
    add_समयr(&info->watchकरोg);
पूर्ण

/*====================================================================*/

अटल पूर्णांक axnet_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
    काष्ठा axnet_dev *info = PRIV(dev);
    काष्ठा mii_ioctl_data *data = अगर_mii(rq);
    अचिन्हित पूर्णांक mii_addr = dev->base_addr + AXNET_MII_EEP;
    चयन (cmd) अणु
    हाल SIOCGMIIPHY:
	data->phy_id = info->phy_id;
	fallthrough;
    हाल SIOCGMIIREG:		/* Read MII PHY रेजिस्टर. */
	data->val_out = mdio_पढ़ो(mii_addr, data->phy_id, data->reg_num & 0x1f);
	वापस 0;
    हाल SIOCSMIIREG:		/* Write MII PHY रेजिस्टर. */
	mdio_ग_लिखो(mii_addr, data->phy_id, data->reg_num & 0x1f, data->val_in);
	वापस 0;
    पूर्ण
    वापस -EOPNOTSUPP;
पूर्ण

/*====================================================================*/

अटल व्योम get_8390_hdr(काष्ठा net_device *dev,
			 काष्ठा e8390_pkt_hdr *hdr,
			 पूर्णांक ring_page)
अणु
    अचिन्हित पूर्णांक nic_base = dev->base_addr;

    outb_p(0, nic_base + EN0_RSARLO);		/* On page boundary */
    outb_p(ring_page, nic_base + EN0_RSARHI);
    outb_p(E8390_RREAD+E8390_START, nic_base + AXNET_CMD);

    insw(nic_base + AXNET_DATAPORT, hdr,
	    माप(काष्ठा e8390_pkt_hdr)>>1);
    /* Fix क्रम big endian प्रणालीs */
    hdr->count = le16_to_cpu(hdr->count);

पूर्ण

/*====================================================================*/

अटल व्योम block_input(काष्ठा net_device *dev, पूर्णांक count,
			काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
    अचिन्हित पूर्णांक nic_base = dev->base_addr;
    काष्ठा ei_device *ei_local = netdev_priv(dev);
    पूर्णांक xfer_count = count;
    अक्षर *buf = skb->data;

    अगर ((netअगर_msg_rx_status(ei_local)) && (count != 4))
	netdev_dbg(dev, "[bi=%d]\n", count+4);
    outb_p(ring_offset & 0xff, nic_base + EN0_RSARLO);
    outb_p(ring_offset >> 8, nic_base + EN0_RSARHI);
    outb_p(E8390_RREAD+E8390_START, nic_base + AXNET_CMD);

    insw(nic_base + AXNET_DATAPORT,buf,count>>1);
    अगर (count & 0x01) अणु
	buf[count-1] = inb(nic_base + AXNET_DATAPORT);
	xfer_count++;
    पूर्ण

पूर्ण

/*====================================================================*/

अटल व्योम block_output(काष्ठा net_device *dev, पूर्णांक count,
			 स्थिर u_अक्षर *buf, स्थिर पूर्णांक start_page)
अणु
    अचिन्हित पूर्णांक nic_base = dev->base_addr;

    pr_debug("%s: [bo=%d]\n", dev->name, count);

    /* Round the count up क्रम word ग_लिखोs.  Do we need to करो this?
       What effect will an odd byte count have on the 8390?
       I should check someday. */
    अगर (count & 0x01)
	count++;

    outb_p(0x00, nic_base + EN0_RSARLO);
    outb_p(start_page, nic_base + EN0_RSARHI);
    outb_p(E8390_RWRITE+E8390_START, nic_base + AXNET_CMD);
    outsw(nic_base + AXNET_DATAPORT, buf, count>>1);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id axnet_ids[] = अणु
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x016c, 0x0081),
	PCMCIA_DEVICE_MANF_CARD(0x018a, 0x0301),
	PCMCIA_DEVICE_MANF_CARD(0x01bf, 0x2328),
	PCMCIA_DEVICE_MANF_CARD(0x026f, 0x0301),
	PCMCIA_DEVICE_MANF_CARD(0x026f, 0x0303),
	PCMCIA_DEVICE_MANF_CARD(0x026f, 0x0309),
	PCMCIA_DEVICE_MANF_CARD(0x0274, 0x1106),
	PCMCIA_DEVICE_MANF_CARD(0x8a01, 0xc1ab),
	PCMCIA_DEVICE_MANF_CARD(0x021b, 0x0202), 
	PCMCIA_DEVICE_MANF_CARD(0xffff, 0x1090),
	PCMCIA_DEVICE_PROD_ID12("AmbiCom,Inc.", "Fast Ethernet PC Card(AMB8110)", 0x49b020a7, 0x119cc9fc),
	PCMCIA_DEVICE_PROD_ID124("Fast Ethernet", "16-bit PC Card", "AX88190", 0xb4be14e3, 0x9a12eb6a, 0xab9be5ef),
	PCMCIA_DEVICE_PROD_ID12("ASIX", "AX88190", 0x0959823b, 0xab9be5ef),
	PCMCIA_DEVICE_PROD_ID12("Billionton", "LNA-100B", 0x552ab682, 0xbc3b87e1),
	PCMCIA_DEVICE_PROD_ID12("CHEETAH ETHERCARD", "EN2228", 0x00fa7bc8, 0x00e990cc),
	PCMCIA_DEVICE_PROD_ID12("CNet", "CNF301", 0xbc477dde, 0x78c5f40b),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "corega FEther PCC-TXD", 0x5261440f, 0x436768c5),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "corega FEtherII PCC-TXD", 0x5261440f, 0x730df72e),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "corega FEther PCC-TXM", 0x5261440f, 0x3abbd061),
	PCMCIA_DEVICE_PROD_ID12("Dynalink", "L100C16", 0x55632fd5, 0x66bc2a90),
	PCMCIA_DEVICE_PROD_ID12("IO DATA", "ETXPCM", 0x547e66dc, 0x233adac2),
	PCMCIA_DEVICE_PROD_ID12("Linksys", "EtherFast 10/100 PC Card (PCMPC100 V3)", 0x0733cc81, 0x232019a8),
	PCMCIA_DEVICE_PROD_ID12("MELCO", "LPC3-TX", 0x481e0094, 0xf91af609),
	PCMCIA_DEVICE_PROD_ID12("NETGEAR", "FA411", 0x9aa79dc3, 0x40fad875),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "100BASE", 0x281f1c5d, 0x7c2add04),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "FastEtherCard", 0x281f1c5d, 0x7ef26116),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "FEP501", 0x281f1c5d, 0x2e272058),
	PCMCIA_DEVICE_PROD_ID14("Network Everywhere", "AX88190", 0x820a67b6,  0xab9be5ef),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, axnet_ids);

अटल काष्ठा pcmcia_driver axnet_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "axnet_cs",
	.probe		= axnet_probe,
	.हटाओ		= axnet_detach,
	.id_table       = axnet_ids,
	.suspend	= axnet_suspend,
	.resume		= axnet_resume,
पूर्ण;
module_pcmcia_driver(axnet_cs_driver);

/*====================================================================*/

/* 8390.c: A general NS8390 ethernet driver core क्रम linux. */
/*
	Written 1992-94 by Donald Becker.
  
	Copyright 1993 United States Government as represented by the
	Director, National Security Agency.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

  This is the chip-specअगरic code क्रम many 8390-based ethernet adaptors.
  This is not a complete driver, it must be combined with board-specअगरic
  code such as ne.c, wd.c, 3c503.c, etc.

  Seeing how at least eight drivers use this code, (not counting the
  PCMCIA ones either) it is easy to अवरोध some card by what seems like
  a simple innocent change. Please contact me or Donald अगर you think
  you have found something that needs changing. -- PG

  Changelog:

  Paul Gorपंचांगaker	: हटाओ set_bit lock, other cleanups.
  Paul Gorपंचांगaker	: add ei_get_8390_hdr() so we can pass skb's to 
			  ei_block_input() क्रम eth_io_copy_and_sum().
  Paul Gorपंचांगaker	: exchange अटल पूर्णांक ei_pingpong क्रम a #घोषणा,
			  also add better Tx error handling.
  Paul Gorपंचांगaker	: reग_लिखो Rx overrun handling as per NS specs.
  Alexey Kuznetsov	: use the 8390's six bit hash multicast filter.
  Paul Gorपंचांगaker	: tweak ANK's above multicast changes a bit.
  Paul Gorपंचांगaker	: update packet statistics क्रम v2.1.x
  Alan Cox		: support arbitrary stupid port mappings on the
  			  68K Macपूर्णांकosh. Support >16bit I/O spaces
  Paul Gorपंचांगaker	: add kmod support क्रम स्वतः-loading of the 8390
			  module by all drivers that require it.
  Alan Cox		: Spinlocking work, added 'BUG_83C690'
  Paul Gorपंचांगaker	: Separate out Tx समयout code from Tx path.

  Sources:
  The National Semiconductor LAN Databook, and the 3Com 3c503 databook.

  */

#समावेश <linux/bitops.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा BUG_83C690

/* These are the operational function पूर्णांकerfaces to board-specअगरic
   routines.
	व्योम reset_8390(काष्ठा net_device *dev)
		Resets the board associated with DEV, including a hardware reset of
		the 8390.  This is only called when there is a transmit समयout, and
		it is always followed by 8390_init().
	व्योम block_output(काष्ठा net_device *dev, पूर्णांक count, स्थिर अचिन्हित अक्षर *buf,
					  पूर्णांक start_page)
		Write the COUNT bytes of BUF to the packet buffer at START_PAGE.  The
		"page" value uses the 8390's 256-byte pages.
	व्योम get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_hdr *hdr, पूर्णांक ring_page)
		Read the 4 byte, page aligned 8390 header. *If* there is a
		subsequent पढ़ो, it will be of the rest of the packet.
	व्योम block_input(काष्ठा net_device *dev, पूर्णांक count, काष्ठा sk_buff *skb, पूर्णांक ring_offset)
		Read COUNT bytes from the packet buffer पूर्णांकo the skb data area. Start 
		पढ़ोing from RING_OFFSET, the address as the 8390 sees it.  This will always
		follow the पढ़ो of the 8390 header. 
*/
#घोषणा ei_reset_8390 (ei_local->reset_8390)
#घोषणा ei_block_output (ei_local->block_output)
#घोषणा ei_block_input (ei_local->block_input)
#घोषणा ei_get_8390_hdr (ei_local->get_8390_hdr)

/* Index to functions. */
अटल व्योम ei_tx_पूर्णांकr(काष्ठा net_device *dev);
अटल व्योम ei_tx_err(काष्ठा net_device *dev);
अटल व्योम ei_receive(काष्ठा net_device *dev);
अटल व्योम ei_rx_overrun(काष्ठा net_device *dev);

/* Routines generic to NS8390-based boards. */
अटल व्योम NS8390_trigger_send(काष्ठा net_device *dev, अचिन्हित पूर्णांक length,
								पूर्णांक start_page);
अटल व्योम करो_set_multicast_list(काष्ठा net_device *dev);

/*
 *	SMP and the 8390 setup.
 *
 *	The 8390 isn't exactly deचिन्हित to be multithपढ़ोed on RX/TX. There is
 *	a page रेजिस्टर that controls bank and packet buffer access. We guard
 *	this with ei_local->page_lock. Nobody should assume or set the page other
 *	than zero when the lock is not held. Lock holders must restore page 0
 *	beक्रमe unlocking. Even pure पढ़ोers must take the lock to protect in 
 *	page 0.
 *
 *	To make lअगरe dअगरficult the chip can also be very slow. We thereक्रमe can't
 *	just use spinlocks. For the दीर्घer lockups we disable the irq the device
 *	sits on and hold the lock. We must hold the lock because there is a dual
 *	processor हाल other than पूर्णांकerrupts (get stats/set multicast list in
 *	parallel with each other and transmit).
 *
 *	Note: in theory we can just disable the irq on the card _but_ there is
 *	a latency on SMP irq delivery. So we can easily go "disable irq" "sync irqs"
 *	enter lock, take the queued irq. So we waddle instead of flying.
 *
 *	Finally by special arrangement क्रम the purpose of being generally 
 *	annoying the transmit function is called bh atomic. That places
 *	restrictions on the user context callers as disable_irq won't save
 *	them.
 */
 
/**
 * ax_खोलो - Open/initialize the board.
 * @dev: network device to initialize
 *
 * This routine goes all-out, setting everything
 * up anew at each खोलो, even though many of these रेजिस्टरs should only
 * need to be set once at boot.
 */
अटल पूर्णांक ax_खोलो(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	/*
	 *	Grab the page lock so we own the रेजिस्टर set, then call
	 *	the init function.
	 */
      
      	spin_lock_irqsave(&ei_local->page_lock, flags);
	AX88190_init(dev, 1);
	/* Set the flag beक्रमe we drop the lock, That way the IRQ arrives
	   after its set and we get no silly warnings */
	netअगर_start_queue(dev);
      	spin_unlock_irqrestore(&ei_local->page_lock, flags);
	ei_local->irqlock = 0;
	वापस 0;
पूर्ण

#घोषणा dev_lock(dev) (((काष्ठा ei_device *)netdev_priv(dev))->page_lock)

/**
 * ax_बंद - shut करोwn network device
 * @dev: network device to बंद
 *
 * Opposite of ax_खोलो(). Only used when "ifconfig <devname> down" is करोne.
 */
अटल पूर्णांक ax_बंद(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 *      Hold the page lock during बंद
	 */

	spin_lock_irqsave(&dev_lock(dev), flags);
	AX88190_init(dev, 0);
	spin_unlock_irqrestore(&dev_lock(dev), flags);
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

/**
 * axnet_tx_समयout - handle transmit समय out condition
 * @dev: network device which has apparently fallen asleep
 * @txqueue: unused
 *
 * Called by kernel when device never acknowledges a transmit has
 * completed (or failed) - i.e. never posted a Tx related पूर्णांकerrupt.
 */

अटल व्योम axnet_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	पूर्णांक txsr, isr, tickssofar = jअगरfies - dev_trans_start(dev);
	अचिन्हित दीर्घ flags;

	dev->stats.tx_errors++;

	spin_lock_irqsave(&ei_local->page_lock, flags);
	txsr = inb(e8390_base+EN0_TSR);
	isr = inb(e8390_base+EN0_ISR);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);

	netdev_dbg(dev, "Tx timed out, %s TSR=%#2x, ISR=%#2x, t=%d.\n",
		   (txsr & ENTSR_ABT) ? "excess collisions." :
		   (isr) ? "lost interrupt?" : "cable problem?",
		   txsr, isr, tickssofar);

	अगर (!isr && !dev->stats.tx_packets) 
	अणु
		/* The 8390 probably hasn't gotten on the cable yet. */
		ei_local->पूर्णांकerface_num ^= 1;   /* Try a dअगरferent xcvr.  */
	पूर्ण

	/* Ugly but a reset can be slow, yet must be रक्षित */
		
	spin_lock_irqsave(&ei_local->page_lock, flags);
		
	/* Try to restart the card.  Perhaps the user has fixed something. */
	ei_reset_8390(dev);
	AX88190_init(dev, 1);
		
	spin_unlock_irqrestore(&ei_local->page_lock, flags);
	netअगर_wake_queue(dev);
पूर्ण
    
/**
 * axnet_start_xmit - begin packet transmission
 * @skb: packet to be sent
 * @dev: network device to which packet is sent
 *
 * Sends a packet to an 8390 network device.
 */
 
अटल netdev_tx_t axnet_start_xmit(काष्ठा sk_buff *skb,
					  काष्ठा net_device *dev)
अणु
	दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	पूर्णांक length, send_length, output_page;
	अचिन्हित दीर्घ flags;
	u8 packet[ETH_ZLEN];
	
	netअगर_stop_queue(dev);

	length = skb->len;

	/* Mask पूर्णांकerrupts from the ethercard. 
	   SMP: We have to grab the lock here otherwise the IRQ handler
	   on another CPU can flip winकरोw and race the IRQ mask set. We end
	   up trashing the mcast filter not disabling irqs अगर we करोn't lock */
	   
	spin_lock_irqsave(&ei_local->page_lock, flags);
	outb_p(0x00, e8390_base + EN0_IMR);
	
	/*
	 *	Slow phase with lock held.
	 */
	 
	ei_local->irqlock = 1;

	send_length = max(length, ETH_ZLEN);

	/*
	 * We have two Tx slots available क्रम use. Find the first मुक्त
	 * slot, and then perक्रमm some sanity checks. With two Tx bufs,
	 * you get very बंद to transmitting back-to-back packets. With
	 * only one Tx buf, the transmitter sits idle जबतक you reload the
	 * card, leaving a substantial gap between each transmitted packet.
	 */

	अगर (ei_local->tx1 == 0) 
	अणु
		output_page = ei_local->tx_start_page;
		ei_local->tx1 = send_length;
		अगर ((netअगर_msg_tx_queued(ei_local)) &&
		    ei_local->tx2 > 0)
			netdev_dbg(dev,
				   "idle transmitter tx2=%d, lasttx=%d, txing=%d\n",
				   ei_local->tx2, ei_local->lasttx,
				   ei_local->txing);
	पूर्ण
	अन्यथा अगर (ei_local->tx2 == 0) 
	अणु
		output_page = ei_local->tx_start_page + TX_PAGES/2;
		ei_local->tx2 = send_length;
		अगर ((netअगर_msg_tx_queued(ei_local)) &&
		    ei_local->tx1 > 0)
			netdev_dbg(dev,
				   "idle transmitter, tx1=%d, lasttx=%d, txing=%d\n",
				   ei_local->tx1, ei_local->lasttx,
				   ei_local->txing);
	पूर्ण
	अन्यथा
	अणु	/* We should never get here. */
		netअगर_dbg(ei_local, tx_err, dev,
			  "No Tx buffers free! tx1=%d tx2=%d last=%d\n",
			  ei_local->tx1, ei_local->tx2,
			  ei_local->lasttx);
		ei_local->irqlock = 0;
		netअगर_stop_queue(dev);
		outb_p(ENISR_ALL, e8390_base + EN0_IMR);
		spin_unlock_irqrestore(&ei_local->page_lock, flags);
		dev->stats.tx_errors++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/*
	 * Okay, now upload the packet and trigger a send अगर the transmitter
	 * isn't alपढ़ोy sending. If it is busy, the पूर्णांकerrupt handler will
	 * trigger the send later, upon receiving a Tx करोne पूर्णांकerrupt.
	 */

	अगर (length == skb->len)
		ei_block_output(dev, length, skb->data, output_page);
	अन्यथा अणु
		स_रखो(packet, 0, ETH_ZLEN);
		skb_copy_from_linear_data(skb, packet, skb->len);
		ei_block_output(dev, length, packet, output_page);
	पूर्ण
	
	अगर (! ei_local->txing) 
	अणु
		ei_local->txing = 1;
		NS8390_trigger_send(dev, send_length, output_page);
		netअगर_trans_update(dev);
		अगर (output_page == ei_local->tx_start_page) 
		अणु
			ei_local->tx1 = -1;
			ei_local->lasttx = -1;
		पूर्ण
		अन्यथा 
		अणु
			ei_local->tx2 = -1;
			ei_local->lasttx = -2;
		पूर्ण
	पूर्ण
	अन्यथा ei_local->txqueue++;

	अगर (ei_local->tx1  &&  ei_local->tx2)
		netअगर_stop_queue(dev);
	अन्यथा
		netअगर_start_queue(dev);

	/* Turn 8390 पूर्णांकerrupts back on. */
	ei_local->irqlock = 0;
	outb_p(ENISR_ALL, e8390_base + EN0_IMR);
	
	spin_unlock_irqrestore(&ei_local->page_lock, flags);

	dev_kमुक्त_skb (skb);
	dev->stats.tx_bytes += send_length;
    
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * ax_पूर्णांकerrupt - handle the पूर्णांकerrupts from an 8390
 * @irq: पूर्णांकerrupt number
 * @dev_id: a poपूर्णांकer to the net_device
 *
 * Handle the ether पूर्णांकerface पूर्णांकerrupts. We pull packets from
 * the 8390 via the card specअगरic functions and fire them at the networking
 * stack. We also handle transmit completions and wake the transmit path अगर
 * necessary. We also update the counters and करो other housekeeping as
 * needed.
 */

अटल irqवापस_t ax_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	दीर्घ e8390_base;
	पूर्णांक पूर्णांकerrupts, nr_serviced = 0, i;
	काष्ठा ei_device *ei_local;
    	पूर्णांक handled = 0;
	अचिन्हित दीर्घ flags;

	e8390_base = dev->base_addr;
	ei_local = netdev_priv(dev);

	/*
	 *	Protect the irq test too.
	 */
	 
	spin_lock_irqsave(&ei_local->page_lock, flags);

	अगर (ei_local->irqlock) अणु
#अगर 1 /* This might just be an पूर्णांकerrupt क्रम a PCI device sharing this line */
		स्थिर अक्षर *msg;
		/* The "irqlock" check is only क्रम testing. */
		अगर (ei_local->irqlock)
			msg = "Interrupted while interrupts are masked!";
		अन्यथा
			msg = "Reentering the interrupt handler!";
		netdev_info(dev, "%s, isr=%#2x imr=%#2x\n",
			    msg,
			    inb_p(e8390_base + EN0_ISR),
			    inb_p(e8390_base + EN0_IMR));
#पूर्ण_अगर
		spin_unlock_irqrestore(&ei_local->page_lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	netअगर_dbg(ei_local, पूर्णांकr, dev, "interrupt(isr=%#2.2x)\n",
		  inb_p(e8390_base + EN0_ISR));

	outb_p(0x00, e8390_base + EN0_ISR);
	ei_local->irqlock = 1;
   
	/* !!Assumption!! -- we stay in page 0.	 Don't अवरोध this. */
	जबतक ((पूर्णांकerrupts = inb_p(e8390_base + EN0_ISR)) != 0 &&
	       ++nr_serviced < MAX_SERVICE)
	अणु
		अगर (!netअगर_running(dev) || (पूर्णांकerrupts == 0xff)) अणु
			netअगर_warn(ei_local, पूर्णांकr, dev,
				   "interrupt from stopped card\n");
			outb_p(पूर्णांकerrupts, e8390_base + EN0_ISR);
			पूर्णांकerrupts = 0;
			अवरोध;
		पूर्ण
		handled = 1;

		/* AX88190 bug fix. */
		outb_p(पूर्णांकerrupts, e8390_base + EN0_ISR);
		क्रम (i = 0; i < 10; i++) अणु
			अगर (!(inb(e8390_base + EN0_ISR) & पूर्णांकerrupts))
				अवरोध;
			outb_p(0, e8390_base + EN0_ISR);
			outb_p(पूर्णांकerrupts, e8390_base + EN0_ISR);
		पूर्ण
		अगर (पूर्णांकerrupts & ENISR_OVER) 
			ei_rx_overrun(dev);
		अन्यथा अगर (पूर्णांकerrupts & (ENISR_RX+ENISR_RX_ERR)) 
		अणु
			/* Got a good (?) packet. */
			ei_receive(dev);
		पूर्ण
		/* Push the next to-transmit packet through. */
		अगर (पूर्णांकerrupts & ENISR_TX)
			ei_tx_पूर्णांकr(dev);
		अन्यथा अगर (पूर्णांकerrupts & ENISR_TX_ERR)
			ei_tx_err(dev);

		अगर (पूर्णांकerrupts & ENISR_COUNTERS) 
		अणु
			dev->stats.rx_frame_errors += inb_p(e8390_base + EN0_COUNTER0);
			dev->stats.rx_crc_errors   += inb_p(e8390_base + EN0_COUNTER1);
			dev->stats.rx_missed_errors+= inb_p(e8390_base + EN0_COUNTER2);
		पूर्ण
	पूर्ण
    
	अगर (पूर्णांकerrupts && (netअगर_msg_पूर्णांकr(ei_local)))
	अणु
		handled = 1;
		अगर (nr_serviced >= MAX_SERVICE) 
		अणु
			/* 0xFF is valid क्रम a card removal */
			अगर (पूर्णांकerrupts != 0xFF)
				netdev_warn(dev,
					    "Too much work at interrupt, status %#2.2x\n",
					    पूर्णांकerrupts);
			outb_p(ENISR_ALL, e8390_base + EN0_ISR); /* Ack. most पूर्णांकrs. */
		पूर्ण अन्यथा अणु
			netdev_warn(dev, "unknown interrupt %#2x\n",
				    पूर्णांकerrupts);
			outb_p(0xff, e8390_base + EN0_ISR); /* Ack. all पूर्णांकrs. */
		पूर्ण
	पूर्ण

	/* Turn 8390 पूर्णांकerrupts back on. */
	ei_local->irqlock = 0;
	outb_p(ENISR_ALL, e8390_base + EN0_IMR);

	spin_unlock_irqrestore(&ei_local->page_lock, flags);
	वापस IRQ_RETVAL(handled);
पूर्ण

/**
 * ei_tx_err - handle transmitter error
 * @dev: network device which threw the exception
 *
 * A transmitter error has happened. Most likely excess collisions (which
 * is a fairly normal condition). If the error is one where the Tx will
 * have been पातed, we try and send another one right away, instead of
 * letting the failed packet sit and collect dust in the Tx buffer. This
 * is a much better solution as it aव्योमs kernel based Tx समयouts, and
 * an unnecessary card reset.
 *
 * Called with lock held.
 */

अटल व्योम ei_tx_err(काष्ठा net_device *dev)
अणु
	दीर्घ e8390_base = dev->base_addr;
	अचिन्हित अक्षर txsr = inb_p(e8390_base+EN0_TSR);
	अचिन्हित अक्षर tx_was_पातed = txsr & (ENTSR_ABT+ENTSR_FU);

#अगर_घोषित VERBOSE_ERROR_DUMP
	netdev_dbg(dev, "transmitter error (%#2x):", txsr);
	अगर (txsr & ENTSR_ABT)
		pr_cont(" excess-collisions");
	अगर (txsr & ENTSR_ND)
		pr_cont(" non-deferral");
	अगर (txsr & ENTSR_CRS)
		pr_cont(" lost-carrier");
	अगर (txsr & ENTSR_FU)
		pr_cont(" FIFO-underrun");
	अगर (txsr & ENTSR_CDH)
		pr_cont(" lost-heartbeat");
	pr_cont("\n");
#पूर्ण_अगर

	अगर (tx_was_पातed)
		ei_tx_पूर्णांकr(dev);
	अन्यथा 
	अणु
		dev->stats.tx_errors++;
		अगर (txsr & ENTSR_CRS) dev->stats.tx_carrier_errors++;
		अगर (txsr & ENTSR_CDH) dev->stats.tx_heartbeat_errors++;
		अगर (txsr & ENTSR_OWC) dev->stats.tx_winकरोw_errors++;
	पूर्ण
पूर्ण

/**
 * ei_tx_पूर्णांकr - transmit पूर्णांकerrupt handler
 * @dev: network device क्रम which tx पूर्णांकr is handled
 *
 * We have finished a transmit: check क्रम errors and then trigger the next
 * packet to be sent. Called with lock held.
 */

अटल व्योम ei_tx_पूर्णांकr(काष्ठा net_device *dev)
अणु
	दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	पूर्णांक status = inb(e8390_base + EN0_TSR);
    
	/*
	 * There are two Tx buffers, see which one finished, and trigger
	 * the send of another one अगर it exists.
	 */
	ei_local->txqueue--;

	अगर (ei_local->tx1 < 0) 
	अणु
		अगर (ei_local->lasttx != 1 && ei_local->lasttx != -1)
			netdev_err(dev, "%s: bogus last_tx_buffer %d, tx1=%d\n",
				   ei_local->name, ei_local->lasttx,
				   ei_local->tx1);
		ei_local->tx1 = 0;
		अगर (ei_local->tx2 > 0) 
		अणु
			ei_local->txing = 1;
			NS8390_trigger_send(dev, ei_local->tx2, ei_local->tx_start_page + 6);
			netअगर_trans_update(dev);
			ei_local->tx2 = -1;
			ei_local->lasttx = 2;
		पूर्ण अन्यथा अणु
			ei_local->lasttx = 20;
			ei_local->txing = 0;
		पूर्ण
	पूर्ण
	अन्यथा अगर (ei_local->tx2 < 0) 
	अणु
		अगर (ei_local->lasttx != 2  &&  ei_local->lasttx != -2)
			netdev_err(dev, "%s: bogus last_tx_buffer %d, tx2=%d\n",
				   ei_local->name, ei_local->lasttx,
				   ei_local->tx2);
		ei_local->tx2 = 0;
		अगर (ei_local->tx1 > 0) 
		अणु
			ei_local->txing = 1;
			NS8390_trigger_send(dev, ei_local->tx1, ei_local->tx_start_page);
			netअगर_trans_update(dev);
			ei_local->tx1 = -1;
			ei_local->lasttx = 1;
		पूर्ण अन्यथा अणु
			ei_local->lasttx = 10;
			ei_local->txing = 0;
		पूर्ण
	पूर्ण
//	अन्यथा
//		netdev_warn(dev, "unexpected TX-done interrupt, lasttx=%d\n",
//			    ei_local->lasttx);

	/* Minimize Tx latency: update the statistics after we restart TXing. */
	अगर (status & ENTSR_COL)
		dev->stats.collisions++;
	अगर (status & ENTSR_PTX)
		dev->stats.tx_packets++;
	अन्यथा 
	अणु
		dev->stats.tx_errors++;
		अगर (status & ENTSR_ABT) 
		अणु
			dev->stats.tx_पातed_errors++;
			dev->stats.collisions += 16;
		पूर्ण
		अगर (status & ENTSR_CRS) 
			dev->stats.tx_carrier_errors++;
		अगर (status & ENTSR_FU) 
			dev->stats.tx_fअगरo_errors++;
		अगर (status & ENTSR_CDH)
			dev->stats.tx_heartbeat_errors++;
		अगर (status & ENTSR_OWC)
			dev->stats.tx_winकरोw_errors++;
	पूर्ण
	netअगर_wake_queue(dev);
पूर्ण

/**
 * ei_receive - receive some packets
 * @dev: network device with which receive will be run
 *
 * We have a good packet(s), get it/them out of the buffers. 
 * Called with lock held.
 */

अटल व्योम ei_receive(काष्ठा net_device *dev)
अणु
	दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित अक्षर rxing_page, this_frame, next_frame;
	अचिन्हित लघु current_offset;
	पूर्णांक rx_pkt_count = 0;
	काष्ठा e8390_pkt_hdr rx_frame;
    
	जबतक (++rx_pkt_count < 10) 
	अणु
		पूर्णांक pkt_len, pkt_stat;
		
		/* Get the rx page (incoming packet poपूर्णांकer). */
		rxing_page = inb_p(e8390_base + EN1_CURPAG -1);
		
		/* Remove one frame from the ring.  Boundary is always a page behind. */
		this_frame = inb_p(e8390_base + EN0_BOUNDARY) + 1;
		अगर (this_frame >= ei_local->stop_page)
			this_frame = ei_local->rx_start_page;
		
		/* Someday we'll omit the previous, अगरf we never get this message.
		   (There is at least one clone claimed to have a problem.)  
		   
		   Keep quiet अगर it looks like a card removal. One problem here
		   is that some clones crash in roughly the same way.
		 */
		अगर ((netअगर_msg_rx_err(ei_local)) &&
		    this_frame != ei_local->current_page &&
		    (this_frame != 0x0 || rxing_page != 0xFF))
			netdev_err(dev, "mismatched read page pointers %2x vs %2x\n",
				   this_frame, ei_local->current_page);
		
		अगर (this_frame == rxing_page)	/* Read all the frames? */
			अवरोध;				/* Done क्रम now */
		
		current_offset = this_frame << 8;
		ei_get_8390_hdr(dev, &rx_frame, this_frame);
		
		pkt_len = rx_frame.count - माप(काष्ठा e8390_pkt_hdr);
		pkt_stat = rx_frame.status;
		
		next_frame = this_frame + 1 + ((pkt_len+4)>>8);
		
		अगर (pkt_len < 60  ||  pkt_len > 1518) 
		अणु
			netअगर_err(ei_local, rx_err, dev,
				  "bogus packet size: %d, status=%#2x nxpg=%#2x\n",
				  rx_frame.count, rx_frame.status,
				  rx_frame.next);
			dev->stats.rx_errors++;
			dev->stats.rx_length_errors++;
		पूर्ण
		 अन्यथा अगर ((pkt_stat & 0x0F) == ENRSR_RXOK) 
		अणु
			काष्ठा sk_buff *skb;
			
			skb = netdev_alloc_skb(dev, pkt_len + 2);
			अगर (skb == शून्य) 
			अणु
				netअगर_err(ei_local, rx_err, dev,
					  "Couldn't allocate a sk_buff of size %d\n",
					  pkt_len);
				dev->stats.rx_dropped++;
				अवरोध;
			पूर्ण
			अन्यथा
			अणु
				skb_reserve(skb,2);	/* IP headers on 16 byte boundaries */
				skb_put(skb, pkt_len);	/* Make room */
				ei_block_input(dev, pkt_len, skb, current_offset + माप(rx_frame));
				skb->protocol=eth_type_trans(skb,dev);
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
				अगर (pkt_stat & ENRSR_PHY)
					dev->stats.multicast++;
			पूर्ण
		पूर्ण 
		अन्यथा 
		अणु
			netअगर_err(ei_local, rx_err, dev,
				  "bogus packet: status=%#2x nxpg=%#2x size=%d\n",
				  rx_frame.status, rx_frame.next,
				  rx_frame.count);
			dev->stats.rx_errors++;
			/* NB: The NIC counts CRC, frame and missed errors. */
			अगर (pkt_stat & ENRSR_FO)
				dev->stats.rx_fअगरo_errors++;
		पूर्ण
		next_frame = rx_frame.next;
		
		/* This _should_ never happen: it's here क्रम aव्योमing bad clones. */
		अगर (next_frame >= ei_local->stop_page) अणु
			netdev_info(dev, "next frame inconsistency, %#2x\n",
				    next_frame);
			next_frame = ei_local->rx_start_page;
		पूर्ण
		ei_local->current_page = next_frame;
		outb_p(next_frame-1, e8390_base+EN0_BOUNDARY);
	पूर्ण
पूर्ण

/**
 * ei_rx_overrun - handle receiver overrun
 * @dev: network device which threw exception
 *
 * We have a receiver overrun: we have to kick the 8390 to get it started
 * again. Problem is that you have to kick it exactly as NS prescribes in
 * the updated datasheets, or "the NIC may act in an unpredictable manner."
 * This includes causing "the NIC to defer indefinitely when it is stopped
 * on a busy network."  Ugh.
 * Called with lock held. Don't call this with the पूर्णांकerrupts off or your
 * computer will hate you - it takes 10ms or so. 
 */

अटल व्योम ei_rx_overrun(काष्ठा net_device *dev)
अणु
	काष्ठा axnet_dev *info = PRIV(dev);
	दीर्घ e8390_base = dev->base_addr;
	अचिन्हित अक्षर was_txing, must_resend = 0;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
    
	/*
	 * Record whether a Tx was in progress and then issue the
	 * stop command.
	 */
	was_txing = inb_p(e8390_base+E8390_CMD) & E8390_TRANS;
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD);

	netअगर_dbg(ei_local, rx_err, dev, "Receiver overrun\n");
	dev->stats.rx_over_errors++;
    
	/* 
	 * Wait a full Tx समय (1.2ms) + some guard समय, NS says 1.6ms total.
	 * We रुको at least 2ms.
	 */

	mdelay(2);

	/*
	 * Reset RBCR[01] back to zero as per magic incantation.
	 */
	outb_p(0x00, e8390_base+EN0_RCNTLO);
	outb_p(0x00, e8390_base+EN0_RCNTHI);

	/*
	 * See अगर any Tx was पूर्णांकerrupted or not. According to NS, this
	 * step is vital, and skipping it will cause no end of havoc.
	 */

	अगर (was_txing)
	अणु 
		अचिन्हित अक्षर tx_completed = inb_p(e8390_base+EN0_ISR) & (ENISR_TX+ENISR_TX_ERR);
		अगर (!tx_completed)
			must_resend = 1;
	पूर्ण

	/*
	 * Have to enter loopback mode and then restart the NIC beक्रमe
	 * you are allowed to slurp packets up off the ring.
	 */
	outb_p(E8390_TXOFF, e8390_base + EN0_TXCR);
	outb_p(E8390_NODMA + E8390_PAGE0 + E8390_START, e8390_base + E8390_CMD);

	/*
	 * Clear the Rx ring of all the debris, and ack the पूर्णांकerrupt.
	 */
	ei_receive(dev);

	/*
	 * Leave loopback mode, and resend any packet that got stopped.
	 */
	outb_p(E8390_TXCONFIG | info->duplex_flag, e8390_base + EN0_TXCR); 
	अगर (must_resend)
    		outb_p(E8390_NODMA + E8390_PAGE0 + E8390_START + E8390_TRANS, e8390_base + E8390_CMD);
पूर्ण

/*
 *	Collect the stats. This is called unlocked and from several contexts.
 */
 
अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev)
अणु
	दीर्घ ioaddr = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
    
	/* If the card is stopped, just वापस the present stats. */
	अगर (!netअगर_running(dev))
		वापस &dev->stats;

	spin_lock_irqsave(&ei_local->page_lock,flags);
	/* Read the counter रेजिस्टरs, assuming we are in page 0. */
	dev->stats.rx_frame_errors += inb_p(ioaddr + EN0_COUNTER0);
	dev->stats.rx_crc_errors   += inb_p(ioaddr + EN0_COUNTER1);
	dev->stats.rx_missed_errors+= inb_p(ioaddr + EN0_COUNTER2);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);
    
	वापस &dev->stats;
पूर्ण

/*
 * Form the 64 bit 8390 multicast table from the linked list of addresses
 * associated with this dev काष्ठाure.
 */
 
अटल अंतरभूत व्योम make_mc_bits(u8 *bits, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	u32 crc;

	netdev_क्रम_each_mc_addr(ha, dev) अणु
		crc = ether_crc(ETH_ALEN, ha->addr);
		/* 
		 * The 8390 uses the 6 most signअगरicant bits of the
		 * CRC to index the multicast table.
		 */
		bits[crc>>29] |= (1<<((crc>>26)&7));
	पूर्ण
पूर्ण

/**
 * करो_set_multicast_list - set/clear multicast filter
 * @dev: net device क्रम which multicast filter is adjusted
 *
 *	Set or clear the multicast filter क्रम this adaptor.
 *	Must be called with lock held. 
 */
 
अटल व्योम करो_set_multicast_list(काष्ठा net_device *dev)
अणु
	दीर्घ e8390_base = dev->base_addr;
	पूर्णांक i;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	अगर (!(dev->flags&(IFF_PROMISC|IFF_ALLMULTI))) अणु
		स_रखो(ei_local->mcfilter, 0, 8);
		अगर (!netdev_mc_empty(dev))
			make_mc_bits(ei_local->mcfilter, dev);
	पूर्ण अन्यथा अणु
		/* set to accept-all */
		स_रखो(ei_local->mcfilter, 0xFF, 8);
	पूर्ण

	outb_p(E8390_NODMA + E8390_PAGE1, e8390_base + E8390_CMD);
	क्रम(i = 0; i < 8; i++) 
	अणु
		outb_p(ei_local->mcfilter[i], e8390_base + EN1_MULT_SHIFT(i));
	पूर्ण
	outb_p(E8390_NODMA + E8390_PAGE0, e8390_base + E8390_CMD);

  	अगर(dev->flags&IFF_PROMISC)
  		outb_p(E8390_RXCONFIG | 0x58, e8390_base + EN0_RXCR);
	अन्यथा अगर (dev->flags & IFF_ALLMULTI || !netdev_mc_empty(dev))
  		outb_p(E8390_RXCONFIG | 0x48, e8390_base + EN0_RXCR);
  	अन्यथा
  		outb_p(E8390_RXCONFIG | 0x40, e8390_base + EN0_RXCR);

	outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, e8390_base+E8390_CMD);
पूर्ण

/*
 *	Called without lock held. This is invoked from user context and may
 *	be parallel to just about everything अन्यथा. Its also fairly quick and
 *	not called too often. Must protect against both bh and irq users
 */

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev_lock(dev), flags);
	करो_set_multicast_list(dev);
	spin_unlock_irqrestore(&dev_lock(dev), flags);
पूर्ण	

/* This page of functions should be 8390 generic */
/* Follow National Semi's recommendations क्रम initializing the "NIC". */

/**
 * AX88190_init - initialize 8390 hardware
 * @dev: network device to initialize
 * @startp: boolean.  non-zero value to initiate chip processing
 *
 *	Must be called with lock held.
 */

अटल व्योम AX88190_init(काष्ठा net_device *dev, पूर्णांक startp)
अणु
	काष्ठा axnet_dev *info = PRIV(dev);
	दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	पूर्णांक i;
	पूर्णांक endcfg = ei_local->word16 ? (0x48 | ENDCFG_WTS) : 0x48;
    
	अगर(माप(काष्ठा e8390_pkt_hdr)!=4)
    		panic("8390.c: header struct mispacked\n");    
	/* Follow National Semi's recommendations क्रम initing the DP83902. */
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD); /* 0x21 */
	outb_p(endcfg, e8390_base + EN0_DCFG);	/* 0x48 or 0x49 */
	/* Clear the remote byte count रेजिस्टरs. */
	outb_p(0x00,  e8390_base + EN0_RCNTLO);
	outb_p(0x00,  e8390_base + EN0_RCNTHI);
	/* Set to monitor and loopback mode -- this is vital!. */
	outb_p(E8390_RXOFF|0x40, e8390_base + EN0_RXCR); /* 0x60 */
	outb_p(E8390_TXOFF, e8390_base + EN0_TXCR); /* 0x02 */
	/* Set the transmit page and receive ring. */
	outb_p(ei_local->tx_start_page, e8390_base + EN0_TPSR);
	ei_local->tx1 = ei_local->tx2 = 0;
	outb_p(ei_local->rx_start_page, e8390_base + EN0_STARTPG);
	outb_p(ei_local->stop_page-1, e8390_base + EN0_BOUNDARY);	/* 3c503 says 0x3f,NS0x26*/
	ei_local->current_page = ei_local->rx_start_page;		/* निश्चित boundary+1 */
	outb_p(ei_local->stop_page, e8390_base + EN0_STOPPG);
	/* Clear the pending पूर्णांकerrupts and mask. */
	outb_p(0xFF, e8390_base + EN0_ISR);
	outb_p(0x00,  e8390_base + EN0_IMR);
    
	/* Copy the station address पूर्णांकo the DS8390 रेजिस्टरs. */

	outb_p(E8390_NODMA + E8390_PAGE1 + E8390_STOP, e8390_base+E8390_CMD); /* 0x61 */
	क्रम(i = 0; i < 6; i++) 
	अणु
		outb_p(dev->dev_addr[i], e8390_base + EN1_PHYS_SHIFT(i));
		अगर(inb_p(e8390_base + EN1_PHYS_SHIFT(i))!=dev->dev_addr[i])
			netdev_err(dev, "Hw. address read/write mismap %d\n", i);
	पूर्ण

	outb_p(ei_local->rx_start_page, e8390_base + EN1_CURPAG);
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD);

	netअगर_start_queue(dev);
	ei_local->tx1 = ei_local->tx2 = 0;
	ei_local->txing = 0;

	अगर (info->flags & IS_AX88790)	/* select Internal PHY */
		outb(0x10, e8390_base + AXNET_GPIO);

	अगर (startp) 
	अणु
		outb_p(0xff,  e8390_base + EN0_ISR);
		outb_p(ENISR_ALL,  e8390_base + EN0_IMR);
		outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, e8390_base+E8390_CMD);
		outb_p(E8390_TXCONFIG | info->duplex_flag,
		       e8390_base + EN0_TXCR); /* xmit on. */
		/* 3c503 TechMan says rxconfig only after the NIC is started. */
		outb_p(E8390_RXCONFIG | 0x40, e8390_base + EN0_RXCR); /* rx on, */
		करो_set_multicast_list(dev);	/* (re)load the mcast table */
	पूर्ण
पूर्ण

/* Trigger a transmit start, assuming the length is valid. 
   Always called with the page lock held */
   
अटल व्योम NS8390_trigger_send(काष्ठा net_device *dev, अचिन्हित पूर्णांक length,
								पूर्णांक start_page)
अणु
	दीर्घ e8390_base = dev->base_addr;
 	काष्ठा ei_device *ei_local __attribute((unused)) = netdev_priv(dev);
    
	अगर (inb_p(e8390_base) & E8390_TRANS) 
	अणु
		netdev_warn(dev, "trigger_send() called with the transmitter busy\n");
		वापस;
	पूर्ण
	outb_p(length & 0xff, e8390_base + EN0_TCNTLO);
	outb_p(length >> 8, e8390_base + EN0_TCNTHI);
	outb_p(start_page, e8390_base + EN0_TPSR);
	outb_p(E8390_NODMA+E8390_TRANS+E8390_START, e8390_base+E8390_CMD);
पूर्ण
