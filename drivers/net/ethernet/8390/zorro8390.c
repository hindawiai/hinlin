<शैली गुरु>
/*
 *  Amiga Linux/m68k and Linux/PPC Zorro NS8390 Ethernet Driver
 *
 *  (C) Copyright 1998-2000 by some Elitist 680x0 Users(TM)
 *
 *  ---------------------------------------------------------------------------
 *
 *  This program is based on all the other NE2000 drivers क्रम Linux
 *
 *  ---------------------------------------------------------------------------
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of the Linux
 *  distribution क्रम more details.
 *
 *  ---------------------------------------------------------------------------
 *
 *  The Ariadne II and X-Surf are Zorro-II boards containing Realtek RTL8019AS
 *  Ethernet Controllers.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/zorro.h>
#समावेश <linux/jअगरfies.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigahw.h>

#घोषणा EI_SHIFT(x)		(ei_local->reg_offset[x])
#घोषणा ei_inb(port)		in_8(port)
#घोषणा ei_outb(val, port)	out_8(port, val)
#घोषणा ei_inb_p(port)		in_8(port)
#घोषणा ei_outb_p(val, port)	out_8(port, val)

अटल स्थिर अक्षर version[] =
	"8390.c:v1.10cvs 9/23/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)\n";

#समावेश "lib8390.c"

#घोषणा DRV_NAME	"zorro8390"

#घोषणा NE_BASE		(dev->base_addr)
#घोषणा NE_CMD		(0x00 * 2)
#घोषणा NE_DATAPORT	(0x10 * 2)	/* NatSemi-defined port winकरोw offset */
#घोषणा NE_RESET	(0x1f * 2)	/* Issue a पढ़ो to reset,
					 * a ग_लिखो to clear. */
#घोषणा NE_IO_EXTENT	(0x20 * 2)

#घोषणा NE_EN0_ISR	(0x07 * 2)
#घोषणा NE_EN0_DCFG	(0x0e * 2)

#घोषणा NE_EN0_RSARLO	(0x08 * 2)
#घोषणा NE_EN0_RSARHI	(0x09 * 2)
#घोषणा NE_EN0_RCNTLO	(0x0a * 2)
#घोषणा NE_EN0_RXCR	(0x0c * 2)
#घोषणा NE_EN0_TXCR	(0x0d * 2)
#घोषणा NE_EN0_RCNTHI	(0x0b * 2)
#घोषणा NE_EN0_IMR	(0x0f * 2)

#घोषणा NESM_START_PG	0x40	/* First page of TX buffer */
#घोषणा NESM_STOP_PG	0x80	/* Last page +1 of RX ring */

#घोषणा WORDSWAP(a)	((((a) >> 8) & 0xff) | ((a) << 8))

अटल काष्ठा card_info अणु
	zorro_id id;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक offset;
पूर्ण cards[] = अणु
	अणु ZORRO_PROD_VILLAGE_TRONIC_ARIADNE2, "Ariadne II", 0x0600 पूर्ण,
	अणु ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF, "X-Surf", 0x8600 पूर्ण,
पूर्ण;

/* Hard reset the card.  This used to छोड़ो क्रम the same period that a
 * 8390 reset command required, but that shouldn't be necessary.
 */
अटल व्योम zorro8390_reset_8390(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ reset_start_समय = jअगरfies;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	netअगर_dbg(ei_local, hw, dev, "resetting - t=%ld...\n", jअगरfies);

	z_ग_लिखोb(z_पढ़ोb(NE_BASE + NE_RESET), NE_BASE + NE_RESET);

	ei_status.txing = 0;
	ei_status.dमुख्यg = 0;

	/* This check _should_not_ be necessary, omit eventually. */
	जबतक ((z_पढ़ोb(NE_BASE + NE_EN0_ISR) & ENISR_RESET) == 0)
		अगर (समय_after(jअगरfies, reset_start_समय + 2 * HZ / 100)) अणु
			netdev_warn(dev, "%s: did not complete\n", __func__);
			अवरोध;
		पूर्ण
	z_ग_लिखोb(ENISR_RESET, NE_BASE + NE_EN0_ISR);	/* Ack पूर्णांकr */
पूर्ण

/* Grab the 8390 specअगरic header. Similar to the block_input routine, but
 * we करोn't need to be concerned with ring wrap as the header will be at
 * the start of a page, so we optimize accordingly.
 */
अटल व्योम zorro8390_get_8390_hdr(काष्ठा net_device *dev,
				   काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु
	पूर्णांक nic_base = dev->base_addr;
	पूर्णांक cnt;
	लघु *ptrs;

	/* This *shouldn't* happen.
	 * If it करोes, it's the last thing you'll see
	 */
	अगर (ei_status.dमुख्यg) अणु
		netdev_warn(dev,
			    "%s: DMAing conflict [DMAstat:%d][irqlock:%d]\n",
			    __func__, ei_status.dमुख्यg, ei_status.irqlock);
		वापस;
	पूर्ण

	ei_status.dमुख्यg |= 0x01;
	z_ग_लिखोb(E8390_NODMA + E8390_PAGE0 + E8390_START, nic_base + NE_CMD);
	z_ग_लिखोb(ENISR_RDC, nic_base + NE_EN0_ISR);
	z_ग_लिखोb(माप(काष्ठा e8390_pkt_hdr), nic_base + NE_EN0_RCNTLO);
	z_ग_लिखोb(0, nic_base + NE_EN0_RCNTHI);
	z_ग_लिखोb(0, nic_base + NE_EN0_RSARLO);		/* On page boundary */
	z_ग_लिखोb(ring_page, nic_base + NE_EN0_RSARHI);
	z_ग_लिखोb(E8390_RREAD+E8390_START, nic_base + NE_CMD);

	ptrs = (लघु *)hdr;
	क्रम (cnt = 0; cnt < माप(काष्ठा e8390_pkt_hdr) >> 1; cnt++)
		*ptrs++ = z_पढ़ोw(NE_BASE + NE_DATAPORT);

	z_ग_लिखोb(ENISR_RDC, nic_base + NE_EN0_ISR);	/* Ack पूर्णांकr */

	hdr->count = WORDSWAP(hdr->count);

	ei_status.dमुख्यg &= ~0x01;
पूर्ण

/* Block input and output, similar to the Crynwr packet driver.
 * If you are porting to a new ethercard, look at the packet driver source
 * क्रम hपूर्णांकs. The NEx000 करोesn't share the on-board packet memory --
 * you have to put the packet out through the "remote DMA" dataport
 * using z_ग_लिखोb.
 */
अटल व्योम zorro8390_block_input(काष्ठा net_device *dev, पूर्णांक count,
				  काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	पूर्णांक nic_base = dev->base_addr;
	अक्षर *buf = skb->data;
	लघु *ptrs;
	पूर्णांक cnt;

	/* This *shouldn't* happen.
	 * If it करोes, it's the last thing you'll see
	 */
	अगर (ei_status.dमुख्यg) अणु
		netdev_err(dev, "%s: DMAing conflict [DMAstat:%d][irqlock:%d]\n",
			   __func__, ei_status.dमुख्यg, ei_status.irqlock);
		वापस;
	पूर्ण
	ei_status.dमुख्यg |= 0x01;
	z_ग_लिखोb(E8390_NODMA + E8390_PAGE0 + E8390_START, nic_base + NE_CMD);
	z_ग_लिखोb(ENISR_RDC, nic_base + NE_EN0_ISR);
	z_ग_लिखोb(count & 0xff, nic_base + NE_EN0_RCNTLO);
	z_ग_लिखोb(count >> 8, nic_base + NE_EN0_RCNTHI);
	z_ग_लिखोb(ring_offset & 0xff, nic_base + NE_EN0_RSARLO);
	z_ग_लिखोb(ring_offset >> 8, nic_base + NE_EN0_RSARHI);
	z_ग_लिखोb(E8390_RREAD+E8390_START, nic_base + NE_CMD);
	ptrs = (लघु *)buf;
	क्रम (cnt = 0; cnt < count >> 1; cnt++)
		*ptrs++ = z_पढ़ोw(NE_BASE + NE_DATAPORT);
	अगर (count & 0x01)
		buf[count - 1] = z_पढ़ोb(NE_BASE + NE_DATAPORT);

	z_ग_लिखोb(ENISR_RDC, nic_base + NE_EN0_ISR);	/* Ack पूर्णांकr */
	ei_status.dमुख्यg &= ~0x01;
पूर्ण

अटल व्योम zorro8390_block_output(काष्ठा net_device *dev, पूर्णांक count,
				   स्थिर अचिन्हित अक्षर *buf,
				   स्थिर पूर्णांक start_page)
अणु
	पूर्णांक nic_base = NE_BASE;
	अचिन्हित दीर्घ dma_start;
	लघु *ptrs;
	पूर्णांक cnt;

	/* Round the count up क्रम word ग_लिखोs.  Do we need to करो this?
	 * What effect will an odd byte count have on the 8390?
	 * I should check someday.
	 */
	अगर (count & 0x01)
		count++;

	/* This *shouldn't* happen.
	 * If it करोes, it's the last thing you'll see
	 */
	अगर (ei_status.dमुख्यg) अणु
		netdev_err(dev, "%s: DMAing conflict [DMAstat:%d][irqlock:%d]\n",
			   __func__, ei_status.dमुख्यg, ei_status.irqlock);
		वापस;
	पूर्ण
	ei_status.dमुख्यg |= 0x01;
	/* We should alपढ़ोy be in page 0, but to be safe... */
	z_ग_लिखोb(E8390_PAGE0+E8390_START+E8390_NODMA, nic_base + NE_CMD);

	z_ग_लिखोb(ENISR_RDC, nic_base + NE_EN0_ISR);

	/* Now the normal output. */
	z_ग_लिखोb(count & 0xff, nic_base + NE_EN0_RCNTLO);
	z_ग_लिखोb(count >> 8,   nic_base + NE_EN0_RCNTHI);
	z_ग_लिखोb(0x00, nic_base + NE_EN0_RSARLO);
	z_ग_लिखोb(start_page, nic_base + NE_EN0_RSARHI);

	z_ग_लिखोb(E8390_RWRITE + E8390_START, nic_base + NE_CMD);
	ptrs = (लघु *)buf;
	क्रम (cnt = 0; cnt < count >> 1; cnt++)
		z_ग_लिखोw(*ptrs++, NE_BASE + NE_DATAPORT);

	dma_start = jअगरfies;

	जबतक ((z_पढ़ोb(NE_BASE + NE_EN0_ISR) & ENISR_RDC) == 0)
		अगर (समय_after(jअगरfies, dma_start + 2 * HZ / 100)) अणु
					/* 20ms */
			netdev_warn(dev, "timeout waiting for Tx RDC\n");
			zorro8390_reset_8390(dev);
			__NS8390_init(dev, 1);
			अवरोध;
		पूर्ण

	z_ग_लिखोb(ENISR_RDC, nic_base + NE_EN0_ISR);	/* Ack पूर्णांकr */
	ei_status.dमुख्यg &= ~0x01;
पूर्ण

अटल पूर्णांक zorro8390_खोलो(काष्ठा net_device *dev)
अणु
	__ei_खोलो(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक zorro8390_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	netअगर_dbg(ei_local, अगरकरोwn, dev, "Shutting down ethercard\n");
	__ei_बंद(dev);
	वापस 0;
पूर्ण

अटल व्योम zorro8390_हटाओ_one(काष्ठा zorro_dev *z)
अणु
	काष्ठा net_device *dev = zorro_get_drvdata(z);

	unरेजिस्टर_netdev(dev);
	मुक्त_irq(IRQ_AMIGA_PORTS, dev);
	release_mem_region(ZTWO_PADDR(dev->base_addr), NE_IO_EXTENT * 2);
	मुक्त_netdev(dev);
पूर्ण

अटल काष्ठा zorro_device_id zorro8390_zorro_tbl[] = अणु
	अणु ZORRO_PROD_VILLAGE_TRONIC_ARIADNE2, पूर्ण,
	अणु ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF, पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, zorro8390_zorro_tbl);

अटल स्थिर काष्ठा net_device_ops zorro8390_netdev_ops = अणु
	.nकरो_खोलो		= zorro8390_खोलो,
	.nकरो_stop		= zorro8390_बंद,
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

अटल पूर्णांक zorro8390_init(काष्ठा net_device *dev, अचिन्हित दीर्घ board,
			  स्थिर अक्षर *name, व्योम __iomem *ioaddr)
अणु
	पूर्णांक i;
	पूर्णांक err;
	अचिन्हित अक्षर SA_prom[32];
	पूर्णांक start_page, stop_page;
	अटल u32 zorro8390_offsets[16] = अणु
		0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
		0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e,
	पूर्ण;

	/* Reset card. Who knows what dain-bramaged state it was left in. */
	अणु
		अचिन्हित दीर्घ reset_start_समय = jअगरfies;

		z_ग_लिखोb(z_पढ़ोb(ioaddr + NE_RESET), ioaddr + NE_RESET);

		जबतक ((z_पढ़ोb(ioaddr + NE_EN0_ISR) & ENISR_RESET) == 0)
			अगर (समय_after(jअगरfies,
				       reset_start_समय + 2 * HZ / 100)) अणु
				netdev_warn(dev, "not found (no reset ack)\n");
				वापस -ENODEV;
			पूर्ण

		z_ग_लिखोb(0xff, ioaddr + NE_EN0_ISR);	/* Ack all पूर्णांकr. */
	पूर्ण

	/* Read the 16 bytes of station address PROM.
	 * We must first initialize रेजिस्टरs,
	 * similar to NS8390_init(eअगरdev, 0).
	 * We can't reliably पढ़ो the SAPROM address without this.
	 * (I learned the hard way!).
	 */
	अणु
		अटल स्थिर काष्ठा अणु
			u32 value;
			u32 offset;
		पूर्ण program_seq[] = अणु
			अणुE8390_NODMA + E8390_PAGE0 + E8390_STOP, NE_CMDपूर्ण,
						/* Select page 0 */
			अणु0x48,	NE_EN0_DCFGपूर्ण,	/* 0x48: Set byte-wide access */
			अणु0x00,	NE_EN0_RCNTLOपूर्ण,	/* Clear the count regs */
			अणु0x00,	NE_EN0_RCNTHIपूर्ण,
			अणु0x00,	NE_EN0_IMRपूर्ण,	/* Mask completion irq */
			अणु0xFF,	NE_EN0_ISRपूर्ण,
			अणुE8390_RXOFF, NE_EN0_RXCRपूर्ण, /* 0x20 Set to monitor */
			अणुE8390_TXOFF, NE_EN0_TXCRपूर्ण, /* 0x02 and loopback mode */
			अणु32,	NE_EN0_RCNTLOपूर्ण,
			अणु0x00,	NE_EN0_RCNTHIपूर्ण,
			अणु0x00,	NE_EN0_RSARLOपूर्ण,	/* DMA starting at 0x0000 */
			अणु0x00,	NE_EN0_RSARHIपूर्ण,
			अणुE8390_RREAD + E8390_START, NE_CMDपूर्ण,
		पूर्ण;
		क्रम (i = 0; i < ARRAY_SIZE(program_seq); i++)
			z_ग_लिखोb(program_seq[i].value,
				 ioaddr + program_seq[i].offset);
	पूर्ण
	क्रम (i = 0; i < 16; i++) अणु
		SA_prom[i] = z_पढ़ोb(ioaddr + NE_DATAPORT);
		(व्योम)z_पढ़ोb(ioaddr + NE_DATAPORT);
	पूर्ण

	/* We must set the 8390 क्रम word mode. */
	z_ग_लिखोb(0x49, ioaddr + NE_EN0_DCFG);
	start_page = NESM_START_PG;
	stop_page = NESM_STOP_PG;

	dev->base_addr = (अचिन्हित दीर्घ)ioaddr;
	dev->irq = IRQ_AMIGA_PORTS;

	/* Install the Interrupt handler */
	i = request_irq(IRQ_AMIGA_PORTS, __ei_पूर्णांकerrupt,
			IRQF_SHARED, DRV_NAME, dev);
	अगर (i)
		वापस i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		dev->dev_addr[i] = SA_prom[i];

	pr_debug("Found ethernet address: %pM\n", dev->dev_addr);

	ei_status.name = name;
	ei_status.tx_start_page = start_page;
	ei_status.stop_page = stop_page;
	ei_status.word16 = 1;

	ei_status.rx_start_page = start_page + TX_PAGES;

	ei_status.reset_8390 = zorro8390_reset_8390;
	ei_status.block_input = zorro8390_block_input;
	ei_status.block_output = zorro8390_block_output;
	ei_status.get_8390_hdr = zorro8390_get_8390_hdr;
	ei_status.reg_offset = zorro8390_offsets;

	dev->netdev_ops = &zorro8390_netdev_ops;
	__NS8390_init(dev, 0);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		मुक्त_irq(IRQ_AMIGA_PORTS, dev);
		वापस err;
	पूर्ण

	netdev_info(dev, "%s at 0x%08lx, Ethernet Address %pM\n",
		    name, board, dev->dev_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक zorro8390_init_one(काष्ठा zorro_dev *z,
			      स्थिर काष्ठा zorro_device_id *ent)
अणु
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ board, ioaddr;
	पूर्णांक err, i;

	क्रम (i = ARRAY_SIZE(cards) - 1; i >= 0; i--)
		अगर (z->id == cards[i].id)
			अवरोध;
	अगर (i < 0)
		वापस -ENODEV;

	board = z->resource.start;
	ioaddr = board + cards[i].offset;
	dev = ____alloc_ei_netdev(0);
	अगर (!dev)
		वापस -ENOMEM;
	अगर (!request_mem_region(ioaddr, NE_IO_EXTENT * 2, DRV_NAME)) अणु
		मुक्त_netdev(dev);
		वापस -EBUSY;
	पूर्ण
	err = zorro8390_init(dev, board, cards[i].name, ZTWO_VADDR(ioaddr));
	अगर (err) अणु
		release_mem_region(ioaddr, NE_IO_EXTENT * 2);
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण
	zorro_set_drvdata(z, dev);
	वापस 0;
पूर्ण

अटल काष्ठा zorro_driver zorro8390_driver = अणु
	.name		= "zorro8390",
	.id_table	= zorro8390_zorro_tbl,
	.probe		= zorro8390_init_one,
	.हटाओ		= zorro8390_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init zorro8390_init_module(व्योम)
अणु
	वापस zorro_रेजिस्टर_driver(&zorro8390_driver);
पूर्ण

अटल व्योम __निकास zorro8390_cleanup_module(व्योम)
अणु
	zorro_unरेजिस्टर_driver(&zorro8390_driver);
पूर्ण

module_init(zorro8390_init_module);
module_निकास(zorro8390_cleanup_module);

MODULE_LICENSE("GPL");
