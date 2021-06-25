<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/net/etherh.c
 *
 *  Copyright (C) 2000-2002 Russell King
 *
 * NS8390 I-cubed EtherH and ANT EtherM specअगरic driver
 * Thanks to I-Cubed क्रम inक्रमmation on their cards.
 * EtherM conversion (C) 1999 Chris Kemp and Tim Watterton
 * EtherM पूर्णांकegration (C) 2000 Aleph One Ltd (Tak-Shing Chan)
 * EtherM पूर्णांकegration re-engineered by Russell King.
 *
 * Changelog:
 *  08-12-1996	RMK	1.00	Created
 *		RMK	1.03	Added support क्रम EtherLan500 cards
 *  23-11-1997	RMK	1.04	Added media स्वतःdetection
 *  16-04-1998	RMK	1.05	Improved media स्वतःdetection
 *  10-02-2000	RMK	1.06	Updated क्रम 2.3.43
 *  13-05-2000	RMK	1.07	Updated क्रम 2.3.99-pre8
 *  12-10-1999  CK/TEW		EtherM driver first release
 *  21-12-2000	TTC		EtherH/EtherM पूर्णांकegration
 *  25-12-2000	RMK	1.08	Clean पूर्णांकegration of EtherM पूर्णांकo this driver.
 *  03-01-2002	RMK	1.09	Always enable IRQs अगर we're in the nic slot.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/jअगरfies.h>

#समावेश <यंत्र/ecard.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/प्रणाली_info.h>

#घोषणा EI_SHIFT(x)	(ei_local->reg_offset[x])

#घोषणा ei_inb(_p)	 पढ़ोb((व्योम __iomem *)_p)
#घोषणा ei_outb(_v,_p)	 ग_लिखोb(_v,(व्योम __iomem *)_p)
#घोषणा ei_inb_p(_p)	 पढ़ोb((व्योम __iomem *)_p)
#घोषणा ei_outb_p(_v,_p) ग_लिखोb(_v,(व्योम __iomem *)_p)

#घोषणा DRV_NAME	"etherh"
#घोषणा DRV_VERSION	"1.11"

अटल अक्षर version[] =
	"EtherH/EtherM Driver (c) 2002-2004 Russell King " DRV_VERSION "\n";

#समावेश "lib8390.c"

काष्ठा etherh_priv अणु
	व्योम __iomem	*ioc_fast;
	व्योम __iomem	*memc;
	व्योम __iomem	*dma_base;
	अचिन्हित पूर्णांक	id;
	व्योम __iomem	*ctrl_port;
	अचिन्हित अक्षर	ctrl;
	u32		supported;
पूर्ण;

काष्ठा etherh_data अणु
	अचिन्हित दीर्घ	ns8390_offset;
	अचिन्हित दीर्घ	dataport_offset;
	अचिन्हित दीर्घ	ctrlport_offset;
	पूर्णांक		ctrl_ioc;
	स्थिर अक्षर	name[16];
	u32		supported;
	अचिन्हित अक्षर	tx_start_page;
	अचिन्हित अक्षर	stop_page;
पूर्ण;

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("EtherH/EtherM driver");
MODULE_LICENSE("GPL");

#घोषणा ETHERH500_DATAPORT	0x800	/* MEMC */
#घोषणा ETHERH500_NS8390	0x000	/* MEMC */
#घोषणा ETHERH500_CTRLPORT	0x800	/* IOC  */

#घोषणा ETHERH600_DATAPORT	0x040	/* MEMC */
#घोषणा ETHERH600_NS8390	0x800	/* MEMC */
#घोषणा ETHERH600_CTRLPORT	0x200	/* MEMC */

#घोषणा ETHERH_CP_IE		1
#घोषणा ETHERH_CP_IF		2
#घोषणा ETHERH_CP_HEARTBEAT	2

#घोषणा ETHERH_TX_START_PAGE	1
#घोषणा ETHERH_STOP_PAGE	127

/*
 * These came from CK/TEW
 */
#घोषणा ETHERM_DATAPORT		0x200	/* MEMC */
#घोषणा ETHERM_NS8390		0x800	/* MEMC */
#घोषणा ETHERM_CTRLPORT		0x23c	/* MEMC */

#घोषणा ETHERM_TX_START_PAGE	64
#घोषणा ETHERM_STOP_PAGE	127

/* ------------------------------------------------------------------------ */

#घोषणा etherh_priv(dev) \
 ((काष्ठा etherh_priv *)(((अक्षर *)netdev_priv(dev)) + माप(काष्ठा ei_device)))

अटल अंतरभूत व्योम etherh_set_ctrl(काष्ठा etherh_priv *eh, अचिन्हित अक्षर mask)
अणु
	अचिन्हित अक्षर ctrl = eh->ctrl | mask;
	eh->ctrl = ctrl;
	ग_लिखोb(ctrl, eh->ctrl_port);
पूर्ण

अटल अंतरभूत व्योम etherh_clr_ctrl(काष्ठा etherh_priv *eh, अचिन्हित अक्षर mask)
अणु
	अचिन्हित अक्षर ctrl = eh->ctrl & ~mask;
	eh->ctrl = ctrl;
	ग_लिखोb(ctrl, eh->ctrl_port);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक etherh_get_stat(काष्ठा etherh_priv *eh)
अणु
	वापस पढ़ोb(eh->ctrl_port);
पूर्ण




अटल व्योम etherh_irq_enable(ecard_t *ec, पूर्णांक irqnr)
अणु
	काष्ठा etherh_priv *eh = ec->irq_data;

	etherh_set_ctrl(eh, ETHERH_CP_IE);
पूर्ण

अटल व्योम etherh_irq_disable(ecard_t *ec, पूर्णांक irqnr)
अणु
	काष्ठा etherh_priv *eh = ec->irq_data;

	etherh_clr_ctrl(eh, ETHERH_CP_IE);
पूर्ण

अटल expansioncard_ops_t etherh_ops = अणु
	.irqenable	= etherh_irq_enable,
	.irqdisable	= etherh_irq_disable,
पूर्ण;




अटल व्योम
etherh_setअगर(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr;

	local_irq_save(flags);

	/* set the पूर्णांकerface type */
	चयन (etherh_priv(dev)->id) अणु
	हाल PROD_I3_ETHERLAN600:
	हाल PROD_I3_ETHERLAN600A:
		addr = (व्योम __iomem *)dev->base_addr + EN0_RCNTHI;

		चयन (dev->अगर_port) अणु
		हाल IF_PORT_10BASE2:
			ग_लिखोb((पढ़ोb(addr) & 0xf8) | 1, addr);
			अवरोध;
		हाल IF_PORT_10BASET:
			ग_लिखोb((पढ़ोb(addr) & 0xf8), addr);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल PROD_I3_ETHERLAN500:
		चयन (dev->अगर_port) अणु
		हाल IF_PORT_10BASE2:
			etherh_clr_ctrl(etherh_priv(dev), ETHERH_CP_IF);
			अवरोध;

		हाल IF_PORT_10BASET:
			etherh_set_ctrl(etherh_priv(dev), ETHERH_CP_IF);
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक
etherh_getअगरstat(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	व्योम __iomem *addr;
	पूर्णांक stat = 0;

	चयन (etherh_priv(dev)->id) अणु
	हाल PROD_I3_ETHERLAN600:
	हाल PROD_I3_ETHERLAN600A:
		addr = (व्योम __iomem *)dev->base_addr + EN0_RCNTHI;
		चयन (dev->अगर_port) अणु
		हाल IF_PORT_10BASE2:
			stat = 1;
			अवरोध;
		हाल IF_PORT_10BASET:
			stat = पढ़ोb(addr) & 4;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल PROD_I3_ETHERLAN500:
		चयन (dev->अगर_port) अणु
		हाल IF_PORT_10BASE2:
			stat = 1;
			अवरोध;
		हाल IF_PORT_10BASET:
			stat = etherh_get_stat(etherh_priv(dev)) & ETHERH_CP_HEARTBEAT;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		stat = 0;
		अवरोध;
	पूर्ण

	वापस stat != 0;
पूर्ण

/*
 * Configure the पूर्णांकerface.  Note that we ignore the other
 * parts of अगरmap, since its mostly meaningless क्रम this driver.
 */
अटल पूर्णांक etherh_set_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)
अणु
	चयन (map->port) अणु
	हाल IF_PORT_10BASE2:
	हाल IF_PORT_10BASET:
		/*
		 * If the user explicitly sets the पूर्णांकerface
		 * media type, turn off स्वतःmedia detection.
		 */
		dev->flags &= ~IFF_AUTOMEDIA;
		dev->अगर_port = map->port;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	etherh_setअगर(dev);

	वापस 0;
पूर्ण

/*
 * Reset the 8390 (hard reset).  Note that we can't actually करो this.
 */
अटल व्योम
etherh_reset(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	व्योम __iomem *addr = (व्योम __iomem *)dev->base_addr;

	ग_लिखोb(E8390_NODMA+E8390_PAGE0+E8390_STOP, addr);

	/*
	 * See अगर we need to change the पूर्णांकerface type.
	 * Note that we use 'interface_num' as a flag
	 * to indicate that we need to change the media.
	 */
	अगर (dev->flags & IFF_AUTOMEDIA && ei_local->पूर्णांकerface_num) अणु
		ei_local->पूर्णांकerface_num = 0;

		अगर (dev->अगर_port == IF_PORT_10BASET)
			dev->अगर_port = IF_PORT_10BASE2;
		अन्यथा
			dev->अगर_port = IF_PORT_10BASET;

		etherh_setअगर(dev);
	पूर्ण
पूर्ण

/*
 * Write a block of data out to the 8390
 */
अटल व्योम
etherh_block_output (काष्ठा net_device *dev, पूर्णांक count, स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित दीर्घ dma_start;
	व्योम __iomem *dma_base, *addr;

	अगर (ei_local->dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in etherh_block_input: "
			   " DMAstat %d irqlock %d\n",
			   ei_local->dमुख्यg, ei_local->irqlock);
		वापस;
	पूर्ण

	/*
	 * Make sure we have a round number of bytes अगर we're in word mode.
	 */
	अगर (count & 1 && ei_local->word16)
		count++;

	ei_local->dमुख्यg = 1;

	addr = (व्योम __iomem *)dev->base_addr;
	dma_base = etherh_priv(dev)->dma_base;

	count = (count + 1) & ~1;
	ग_लिखोb (E8390_NODMA | E8390_PAGE0 | E8390_START, addr + E8390_CMD);

	ग_लिखोb (0x42, addr + EN0_RCNTLO);
	ग_लिखोb (0x00, addr + EN0_RCNTHI);
	ग_लिखोb (0x42, addr + EN0_RSARLO);
	ग_लिखोb (0x00, addr + EN0_RSARHI);
	ग_लिखोb (E8390_RREAD | E8390_START, addr + E8390_CMD);

	udelay (1);

	ग_लिखोb (ENISR_RDC, addr + EN0_ISR);
	ग_लिखोb (count, addr + EN0_RCNTLO);
	ग_लिखोb (count >> 8, addr + EN0_RCNTHI);
	ग_लिखोb (0, addr + EN0_RSARLO);
	ग_लिखोb (start_page, addr + EN0_RSARHI);
	ग_लिखोb (E8390_RWRITE | E8390_START, addr + E8390_CMD);

	अगर (ei_local->word16)
		ग_लिखोsw (dma_base, buf, count >> 1);
	अन्यथा
		ग_लिखोsb (dma_base, buf, count);

	dma_start = jअगरfies;

	जबतक ((पढ़ोb (addr + EN0_ISR) & ENISR_RDC) == 0)
		अगर (समय_after(jअगरfies, dma_start + 2*HZ/100)) अणु /* 20ms */
			netdev_warn(dev, "timeout waiting for TX RDC\n");
			etherh_reset (dev);
			__NS8390_init (dev, 1);
			अवरोध;
		पूर्ण

	ग_लिखोb (ENISR_RDC, addr + EN0_ISR);
	ei_local->dमुख्यg = 0;
पूर्ण

/*
 * Read a block of data from the 8390
 */
अटल व्योम
etherh_block_input (काष्ठा net_device *dev, पूर्णांक count, काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित अक्षर *buf;
	व्योम __iomem *dma_base, *addr;

	अगर (ei_local->dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in etherh_block_input: "
			   " DMAstat %d irqlock %d\n",
			   ei_local->dमुख्यg, ei_local->irqlock);
		वापस;
	पूर्ण

	ei_local->dमुख्यg = 1;

	addr = (व्योम __iomem *)dev->base_addr;
	dma_base = etherh_priv(dev)->dma_base;

	buf = skb->data;
	ग_लिखोb (E8390_NODMA | E8390_PAGE0 | E8390_START, addr + E8390_CMD);
	ग_लिखोb (count, addr + EN0_RCNTLO);
	ग_लिखोb (count >> 8, addr + EN0_RCNTHI);
	ग_लिखोb (ring_offset, addr + EN0_RSARLO);
	ग_लिखोb (ring_offset >> 8, addr + EN0_RSARHI);
	ग_लिखोb (E8390_RREAD | E8390_START, addr + E8390_CMD);

	अगर (ei_local->word16) अणु
		पढ़ोsw (dma_base, buf, count >> 1);
		अगर (count & 1)
			buf[count - 1] = पढ़ोb (dma_base);
	पूर्ण अन्यथा
		पढ़ोsb (dma_base, buf, count);

	ग_लिखोb (ENISR_RDC, addr + EN0_ISR);
	ei_local->dमुख्यg = 0;
पूर्ण

/*
 * Read a header from the 8390
 */
अटल व्योम
etherh_get_header (काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	व्योम __iomem *dma_base, *addr;

	अगर (ei_local->dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in etherh_get_header: "
			   " DMAstat %d irqlock %d\n",
			   ei_local->dमुख्यg, ei_local->irqlock);
		वापस;
	पूर्ण

	ei_local->dमुख्यg = 1;

	addr = (व्योम __iomem *)dev->base_addr;
	dma_base = etherh_priv(dev)->dma_base;

	ग_लिखोb (E8390_NODMA | E8390_PAGE0 | E8390_START, addr + E8390_CMD);
	ग_लिखोb (माप (*hdr), addr + EN0_RCNTLO);
	ग_लिखोb (0, addr + EN0_RCNTHI);
	ग_लिखोb (0, addr + EN0_RSARLO);
	ग_लिखोb (ring_page, addr + EN0_RSARHI);
	ग_लिखोb (E8390_RREAD | E8390_START, addr + E8390_CMD);

	अगर (ei_local->word16)
		पढ़ोsw (dma_base, hdr, माप (*hdr) >> 1);
	अन्यथा
		पढ़ोsb (dma_base, hdr, माप (*hdr));

	ग_लिखोb (ENISR_RDC, addr + EN0_ISR);
	ei_local->dमुख्यg = 0;
पूर्ण

/*
 * Open/initialize the board.  This is called (in the current kernel)
 * someसमय after booting when the 'ifconfig' program is run.
 *
 * This routine should set everything up anew at each खोलो, even
 * रेजिस्टरs that "should" only need to be set once at boot, so that
 * there is non-reboot way to recover अगर something goes wrong.
 */
अटल पूर्णांक
etherh_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	अगर (request_irq(dev->irq, __ei_पूर्णांकerrupt, 0, dev->name, dev))
		वापस -EAGAIN;

	/*
	 * Make sure that we aren't going to change the
	 * media type on the next reset - we are about to
	 * करो स्वतःmedia manually now.
	 */
	ei_local->पूर्णांकerface_num = 0;

	/*
	 * If we are करोing स्वतःmedia detection, करो it now.
	 * This is more reliable than the 8390's detection.
	 */
	अगर (dev->flags & IFF_AUTOMEDIA) अणु
		dev->अगर_port = IF_PORT_10BASET;
		etherh_setअगर(dev);
		mdelay(1);
		अगर (!etherh_getअगरstat(dev)) अणु
			dev->अगर_port = IF_PORT_10BASE2;
			etherh_setअगर(dev);
		पूर्ण
	पूर्ण अन्यथा
		etherh_setअगर(dev);

	etherh_reset(dev);
	__ei_खोलो(dev);

	वापस 0;
पूर्ण

/*
 * The inverse routine to etherh_खोलो().
 */
अटल पूर्णांक
etherh_बंद(काष्ठा net_device *dev)
अणु
	__ei_बंद (dev);
	मुक्त_irq (dev->irq, dev);
	वापस 0;
पूर्ण

/*
 * Read the ethernet address string from the on board rom.
 * This is an ascii string...
 */
अटल पूर्णांक etherh_addr(अक्षर *addr, काष्ठा expansion_card *ec)
अणु
	काष्ठा in_chunk_dir cd;
	अक्षर *s;
	
	अगर (!ecard_पढ़ोchunk(&cd, ec, 0xf5, 0)) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to read module description string\n",
		       dev_name(&ec->dev));
		जाओ no_addr;
	पूर्ण

	s = म_अक्षर(cd.d.string, '(');
	अगर (s) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 6; i++) अणु
			addr[i] = simple_म_से_अदीर्घ(s + 1, &s, 0x10);
			अगर (*s != (i == 5? ')' : ':'))
				अवरोध;
		पूर्ण

		अगर (i == 6)
			वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_ERR "%s: unable to parse MAC address: %s\n",
	       dev_name(&ec->dev), cd.d.string);

 no_addr:
	वापस -ENODEV;
पूर्ण

/*
 * Create an ethernet address from the प्रणाली serial number.
 */
अटल पूर्णांक __init etherm_addr(अक्षर *addr)
अणु
	अचिन्हित पूर्णांक serial;

	अगर (प्रणाली_serial_low == 0 && प्रणाली_serial_high == 0)
		वापस -ENODEV;

	serial = प्रणाली_serial_low | प्रणाली_serial_high;

	addr[0] = 0;
	addr[1] = 0;
	addr[2] = 0xa4;
	addr[3] = 0x10 + (serial >> 24);
	addr[4] = serial >> 16;
	addr[5] = serial >> 8;
	वापस 0;
पूर्ण

अटल व्योम etherh_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, dev_name(dev->dev.parent),
		माप(info->bus_info));
पूर्ण

अटल पूर्णांक etherh_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						etherh_priv(dev)->supported);
	cmd->base.speed = SPEED_10;
	cmd->base.duplex = DUPLEX_HALF;
	cmd->base.port = dev->अगर_port == IF_PORT_10BASET ? PORT_TP : PORT_BNC;
	cmd->base.स्वतःneg = (dev->flags & IFF_AUTOMEDIA ? AUTONEG_ENABLE :
							  AUTONEG_DISABLE);
	वापस 0;
पूर्ण

अटल पूर्णांक etherh_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	चयन (cmd->base.स्वतःneg) अणु
	हाल AUTONEG_ENABLE:
		dev->flags |= IFF_AUTOMEDIA;
		अवरोध;

	हाल AUTONEG_DISABLE:
		चयन (cmd->base.port) अणु
		हाल PORT_TP:
			dev->अगर_port = IF_PORT_10BASET;
			अवरोध;

		हाल PORT_BNC:
			dev->अगर_port = IF_PORT_10BASE2;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
		dev->flags &= ~IFF_AUTOMEDIA;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	etherh_setअगर(dev);

	वापस 0;
पूर्ण

अटल u32 etherh_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	वापस ei_local->msg_enable;
पूर्ण

अटल व्योम etherh_set_msglevel(काष्ठा net_device *dev, u32 v)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	ei_local->msg_enable = v;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops etherh_ethtool_ops = अणु
	.get_drvinfo		= etherh_get_drvinfo,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_msglevel		= etherh_get_msglevel,
	.set_msglevel		= etherh_set_msglevel,
	.get_link_ksettings	= etherh_get_link_ksettings,
	.set_link_ksettings	= etherh_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops etherh_netdev_ops = अणु
	.nकरो_खोलो		= etherh_खोलो,
	.nकरो_stop		= etherh_बंद,
	.nकरो_set_config		= etherh_set_config,
	.nकरो_start_xmit		= __ei_start_xmit,
	.nकरो_tx_समयout		= __ei_tx_समयout,
	.nकरो_get_stats		= __ei_get_stats,
	.nकरो_set_rx_mode	= __ei_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= __ei_poll,
#पूर्ण_अगर
पूर्ण;

अटल u32 etherh_regoffsets[16];
अटल u32 etherm_regoffsets[16];

अटल पूर्णांक
etherh_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	स्थिर काष्ठा etherh_data *data = id->data;
	काष्ठा ei_device *ei_local;
	काष्ठा net_device *dev;
	काष्ठा etherh_priv *eh;
	पूर्णांक ret;

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	dev = ____alloc_ei_netdev(माप(काष्ठा etherh_priv));
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	SET_NETDEV_DEV(dev, &ec->dev);

	dev->netdev_ops		= &etherh_netdev_ops;
	dev->irq		= ec->irq;
	dev->ethtool_ops	= &etherh_ethtool_ops;

	अगर (data->supported & SUPPORTED_Autoneg)
		dev->flags |= IFF_AUTOMEDIA;
	अगर (data->supported & SUPPORTED_TP) अणु
		dev->flags |= IFF_PORTSEL;
		dev->अगर_port = IF_PORT_10BASET;
	पूर्ण अन्यथा अगर (data->supported & SUPPORTED_BNC) अणु
		dev->flags |= IFF_PORTSEL;
		dev->अगर_port = IF_PORT_10BASE2;
	पूर्ण अन्यथा
		dev->अगर_port = IF_PORT_UNKNOWN;

	eh = etherh_priv(dev);
	eh->supported		= data->supported;
	eh->ctrl		= 0;
	eh->id			= ec->cid.product;
	eh->memc		= ecardm_iomap(ec, ECARD_RES_MEMC, 0, PAGE_SIZE);
	अगर (!eh->memc) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	eh->ctrl_port = eh->memc;
	अगर (data->ctrl_ioc) अणु
		eh->ioc_fast = ecardm_iomap(ec, ECARD_RES_IOCFAST, 0, PAGE_SIZE);
		अगर (!eh->ioc_fast) अणु
			ret = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
		eh->ctrl_port = eh->ioc_fast;
	पूर्ण

	dev->base_addr = (अचिन्हित दीर्घ)eh->memc + data->ns8390_offset;
	eh->dma_base = eh->memc + data->dataport_offset;
	eh->ctrl_port += data->ctrlport_offset;

	/*
	 * IRQ and control port handling - only क्रम non-NIC slot cards.
	 */
	अगर (ec->slot_no != 8) अणु
		ecard_setirq(ec, &etherh_ops, eh);
	पूर्ण अन्यथा अणु
		/*
		 * If we're in the NIC slot, make sure the IRQ is enabled
		 */
		etherh_set_ctrl(eh, ETHERH_CP_IE);
	पूर्ण

	ei_local = netdev_priv(dev);
	spin_lock_init(&ei_local->page_lock);

	अगर (ec->cid.product == PROD_ANT_ETHERM) अणु
		etherm_addr(dev->dev_addr);
		ei_local->reg_offset = etherm_regoffsets;
	पूर्ण अन्यथा अणु
		etherh_addr(dev->dev_addr, ec);
		ei_local->reg_offset = etherh_regoffsets;
	पूर्ण

	ei_local->name          = dev->name;
	ei_local->word16        = 1;
	ei_local->tx_start_page = data->tx_start_page;
	ei_local->rx_start_page = ei_local->tx_start_page + TX_PAGES;
	ei_local->stop_page     = data->stop_page;
	ei_local->reset_8390    = etherh_reset;
	ei_local->block_input   = etherh_block_input;
	ei_local->block_output  = etherh_block_output;
	ei_local->get_8390_hdr  = etherh_get_header;
	ei_local->पूर्णांकerface_num = 0;

	etherh_reset(dev);
	__NS8390_init(dev, 0);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ मुक्त;

	netdev_info(dev, "%s in slot %d, %pM\n",
		    data->name, ec->slot_no, dev->dev_addr);

	ecard_set_drvdata(ec, dev);

	वापस 0;

 मुक्त:
	मुक्त_netdev(dev);
 release:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम etherh_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा net_device *dev = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, शून्य);

	unरेजिस्टर_netdev(dev);

	मुक्त_netdev(dev);

	ecard_release_resources(ec);
पूर्ण

अटल काष्ठा etherh_data etherm_data = अणु
	.ns8390_offset		= ETHERM_NS8390,
	.dataport_offset	= ETHERM_NS8390 + ETHERM_DATAPORT,
	.ctrlport_offset	= ETHERM_NS8390 + ETHERM_CTRLPORT,
	.name			= "ANT EtherM",
	.supported		= SUPPORTED_10baseT_Half,
	.tx_start_page		= ETHERM_TX_START_PAGE,
	.stop_page		= ETHERM_STOP_PAGE,
पूर्ण;

अटल काष्ठा etherh_data etherlan500_data = अणु
	.ns8390_offset		= ETHERH500_NS8390,
	.dataport_offset	= ETHERH500_NS8390 + ETHERH500_DATAPORT,
	.ctrlport_offset	= ETHERH500_CTRLPORT,
	.ctrl_ioc		= 1,
	.name			= "i3 EtherH 500",
	.supported		= SUPPORTED_10baseT_Half,
	.tx_start_page		= ETHERH_TX_START_PAGE,
	.stop_page		= ETHERH_STOP_PAGE,
पूर्ण;

अटल काष्ठा etherh_data etherlan600_data = अणु
	.ns8390_offset		= ETHERH600_NS8390,
	.dataport_offset	= ETHERH600_NS8390 + ETHERH600_DATAPORT,
	.ctrlport_offset	= ETHERH600_NS8390 + ETHERH600_CTRLPORT,
	.name			= "i3 EtherH 600",
	.supported		= SUPPORTED_10baseT_Half | SUPPORTED_TP | SUPPORTED_BNC | SUPPORTED_Autoneg,
	.tx_start_page		= ETHERH_TX_START_PAGE,
	.stop_page		= ETHERH_STOP_PAGE,
पूर्ण;

अटल काष्ठा etherh_data etherlan600a_data = अणु
	.ns8390_offset		= ETHERH600_NS8390,
	.dataport_offset	= ETHERH600_NS8390 + ETHERH600_DATAPORT,
	.ctrlport_offset	= ETHERH600_NS8390 + ETHERH600_CTRLPORT,
	.name			= "i3 EtherH 600A",
	.supported		= SUPPORTED_10baseT_Half | SUPPORTED_TP | SUPPORTED_BNC | SUPPORTED_Autoneg,
	.tx_start_page		= ETHERH_TX_START_PAGE,
	.stop_page		= ETHERH_STOP_PAGE,
पूर्ण;

अटल स्थिर काष्ठा ecard_id etherh_ids[] = अणु
	अणु MANU_ANT, PROD_ANT_ETHERM,      &etherm_data       पूर्ण,
	अणु MANU_I3,  PROD_I3_ETHERLAN500,  &etherlan500_data  पूर्ण,
	अणु MANU_I3,  PROD_I3_ETHERLAN600,  &etherlan600_data  पूर्ण,
	अणु MANU_I3,  PROD_I3_ETHERLAN600A, &etherlan600a_data पूर्ण,
	अणु 0xffff,   0xffff पूर्ण
पूर्ण;

अटल काष्ठा ecard_driver etherh_driver = अणु
	.probe		= etherh_probe,
	.हटाओ		= etherh_हटाओ,
	.id_table	= etherh_ids,
	.drv = अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init etherh_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		etherh_regoffsets[i] = i << 2;
		etherm_regoffsets[i] = i << 5;
	पूर्ण

	वापस ecard_रेजिस्टर_driver(&etherh_driver);
पूर्ण

अटल व्योम __निकास etherh_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&etherh_driver);
पूर्ण

module_init(etherh_init);
module_निकास(etherh_निकास);
