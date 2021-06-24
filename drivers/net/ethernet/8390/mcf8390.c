<शैली गुरु>
/*
 *  Support क्रम ColdFire CPU based boards using a NS8390 Ethernet device.
 *
 *  Derived from the many other 8390 drivers.
 *
 *  (C) Copyright 2012,  Greg Ungerer <gerg@uclinux.org>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of the Linux
 *  distribution क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mcf8390.h>

अटल स्थिर अक्षर version[] =
	"mcf8390.c: (15-06-2012) Greg Ungerer <gerg@uclinux.org>";

#घोषणा NE_CMD		0x00
#घोषणा NE_DATAPORT	0x10	/* NatSemi-defined port winकरोw offset */
#घोषणा NE_RESET	0x1f	/* Issue a पढ़ो to reset ,a ग_लिखो to clear */
#घोषणा NE_EN0_ISR	0x07
#घोषणा NE_EN0_DCFG	0x0e
#घोषणा NE_EN0_RSARLO	0x08
#घोषणा NE_EN0_RSARHI	0x09
#घोषणा NE_EN0_RCNTLO	0x0a
#घोषणा NE_EN0_RXCR	0x0c
#घोषणा NE_EN0_TXCR	0x0d
#घोषणा NE_EN0_RCNTHI	0x0b
#घोषणा NE_EN0_IMR	0x0f

#घोषणा NESM_START_PG	0x40	/* First page of TX buffer */
#घोषणा NESM_STOP_PG	0x80	/* Last page +1 of RX ring */

#अगर_घोषित NE2000_ODDOFFSET
/*
 * A lot of the ColdFire boards use a separate address region क्रम odd offset
 * रेजिस्टर addresses. The following functions convert and map as required.
 * Note that the data port accesses are treated a little dअगरferently, and
 * always accessed via the insX/outsX functions.
 */
अटल अंतरभूत u32 NE_PTR(u32 addr)
अणु
	अगर (addr & 1)
		वापस addr - 1 + NE2000_ODDOFFSET;
	वापस addr;
पूर्ण

अटल अंतरभूत u32 NE_DATA_PTR(u32 addr)
अणु
	वापस addr;
पूर्ण

व्योम ei_outb(u32 val, u32 addr)
अणु
	NE2000_BYTE *rp;

	rp = (NE2000_BYTE *) NE_PTR(addr);
	*rp = RSWAP(val);
पूर्ण

#घोषणा	ei_inb	ei_inb
u8 ei_inb(u32 addr)
अणु
	NE2000_BYTE *rp, val;

	rp = (NE2000_BYTE *) NE_PTR(addr);
	val = *rp;
	वापस (u8) (RSWAP(val) & 0xff);
पूर्ण

व्योम ei_insb(u32 addr, व्योम *vbuf, पूर्णांक len)
अणु
	NE2000_BYTE *rp, val;
	u8 *buf;

	buf = (u8 *) vbuf;
	rp = (NE2000_BYTE *) NE_DATA_PTR(addr);
	क्रम (; (len > 0); len--) अणु
		val = *rp;
		*buf++ = RSWAP(val);
	पूर्ण
पूर्ण

व्योम ei_insw(u32 addr, व्योम *vbuf, पूर्णांक len)
अणु
	अस्थिर u16 *rp;
	u16 w, *buf;

	buf = (u16 *) vbuf;
	rp = (अस्थिर u16 *) NE_DATA_PTR(addr);
	क्रम (; (len > 0); len--) अणु
		w = *rp;
		*buf++ = BSWAP(w);
	पूर्ण
पूर्ण

व्योम ei_outsb(u32 addr, स्थिर व्योम *vbuf, पूर्णांक len)
अणु
	NE2000_BYTE *rp, val;
	u8 *buf;

	buf = (u8 *) vbuf;
	rp = (NE2000_BYTE *) NE_DATA_PTR(addr);
	क्रम (; (len > 0); len--) अणु
		val = *buf++;
		*rp = RSWAP(val);
	पूर्ण
पूर्ण

व्योम ei_outsw(u32 addr, स्थिर व्योम *vbuf, पूर्णांक len)
अणु
	अस्थिर u16 *rp;
	u16 w, *buf;

	buf = (u16 *) vbuf;
	rp = (अस्थिर u16 *) NE_DATA_PTR(addr);
	क्रम (; (len > 0); len--) अणु
		w = *buf++;
		*rp = BSWAP(w);
	पूर्ण
पूर्ण

#अन्यथा /* !NE2000_ODDOFFSET */

#घोषणा	ei_inb		inb
#घोषणा	ei_outb		outb
#घोषणा	ei_insb		insb
#घोषणा	ei_insw		insw
#घोषणा	ei_outsb	outsb
#घोषणा	ei_outsw	outsw

#पूर्ण_अगर /* !NE2000_ODDOFFSET */

#घोषणा	ei_inb_p	ei_inb
#घोषणा	ei_outb_p	ei_outb

#समावेश "lib8390.c"

/*
 * Hard reset the card. This used to छोड़ो क्रम the same period that a
 * 8390 reset command required, but that shouldn't be necessary.
 */
अटल व्योम mcf8390_reset_8390(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ reset_start_समय = jअगरfies;
	u32 addr = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	netअगर_dbg(ei_local, hw, dev, "resetting the 8390 t=%ld...\n", jअगरfies);

	ei_outb(ei_inb(addr + NE_RESET), addr + NE_RESET);

	ei_status.txing = 0;
	ei_status.dमुख्यg = 0;

	/* This check _should_not_ be necessary, omit eventually. */
	जबतक ((ei_inb(addr + NE_EN0_ISR) & ENISR_RESET) == 0) अणु
		अगर (समय_after(jअगरfies, reset_start_समय + 2 * HZ / 100)) अणु
			netdev_warn(dev, "%s: did not complete\n", __func__);
			अवरोध;
		पूर्ण
	पूर्ण

	ei_outb(ENISR_RESET, addr + NE_EN0_ISR);
पूर्ण

/*
 * This *shouldn't* happen.
 * If it करोes, it's the last thing you'll see
 */
अटल व्योम mcf8390_dमुख्यg_err(स्थिर अक्षर *func, काष्ठा net_device *dev,
			       काष्ठा ei_device *ei_local)
अणु
	netdev_err(dev, "%s: DMAing conflict [DMAstat:%d][irqlock:%d]\n",
		func, ei_local->dमुख्यg, ei_local->irqlock);
पूर्ण

/*
 * Grab the 8390 specअगरic header. Similar to the block_input routine, but
 * we करोn't need to be concerned with ring wrap as the header will be at
 * the start of a page, so we optimize accordingly.
 */
अटल व्योम mcf8390_get_8390_hdr(काष्ठा net_device *dev,
				 काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	u32 addr = dev->base_addr;

	अगर (ei_local->dमुख्यg) अणु
		mcf8390_dमुख्यg_err(__func__, dev, ei_local);
		वापस;
	पूर्ण

	ei_local->dमुख्यg |= 0x01;
	ei_outb(E8390_NODMA + E8390_PAGE0 + E8390_START, addr + NE_CMD);
	ei_outb(ENISR_RDC, addr + NE_EN0_ISR);
	ei_outb(माप(काष्ठा e8390_pkt_hdr), addr + NE_EN0_RCNTLO);
	ei_outb(0, addr + NE_EN0_RCNTHI);
	ei_outb(0, addr + NE_EN0_RSARLO);		/* On page boundary */
	ei_outb(ring_page, addr + NE_EN0_RSARHI);
	ei_outb(E8390_RREAD + E8390_START, addr + NE_CMD);

	ei_insw(addr + NE_DATAPORT, hdr, माप(काष्ठा e8390_pkt_hdr) >> 1);

	outb(ENISR_RDC, addr + NE_EN0_ISR);	/* Ack पूर्णांकr */
	ei_local->dमुख्यg &= ~0x01;

	hdr->count = cpu_to_le16(hdr->count);
पूर्ण

/*
 * Block input and output, similar to the Crynwr packet driver.
 * If you are porting to a new ethercard, look at the packet driver source
 * क्रम hपूर्णांकs. The NEx000 करोesn't share the on-board packet memory --
 * you have to put the packet out through the "remote DMA" dataport
 * using z_ग_लिखोb.
 */
अटल व्योम mcf8390_block_input(काष्ठा net_device *dev, पूर्णांक count,
				काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	u32 addr = dev->base_addr;
	अक्षर *buf = skb->data;

	अगर (ei_local->dमुख्यg) अणु
		mcf8390_dमुख्यg_err(__func__, dev, ei_local);
		वापस;
	पूर्ण

	ei_local->dमुख्यg |= 0x01;
	ei_outb(E8390_NODMA + E8390_PAGE0 + E8390_START, addr + NE_CMD);
	ei_outb(ENISR_RDC, addr + NE_EN0_ISR);
	ei_outb(count & 0xff, addr + NE_EN0_RCNTLO);
	ei_outb(count >> 8, addr + NE_EN0_RCNTHI);
	ei_outb(ring_offset & 0xff, addr + NE_EN0_RSARLO);
	ei_outb(ring_offset >> 8, addr + NE_EN0_RSARHI);
	ei_outb(E8390_RREAD + E8390_START, addr + NE_CMD);

	ei_insw(addr + NE_DATAPORT, buf, count >> 1);
	अगर (count & 1)
		buf[count - 1] = ei_inb(addr + NE_DATAPORT);

	ei_outb(ENISR_RDC, addr + NE_EN0_ISR);	/* Ack पूर्णांकr */
	ei_local->dमुख्यg &= ~0x01;
पूर्ण

अटल व्योम mcf8390_block_output(काष्ठा net_device *dev, पूर्णांक count,
				 स्थिर अचिन्हित अक्षर *buf,
				 स्थिर पूर्णांक start_page)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	u32 addr = dev->base_addr;
	अचिन्हित दीर्घ dma_start;

	/* Make sure we transfer all bytes अगर 16bit IO ग_लिखोs */
	अगर (count & 0x1)
		count++;

	अगर (ei_local->dमुख्यg) अणु
		mcf8390_dमुख्यg_err(__func__, dev, ei_local);
		वापस;
	पूर्ण

	ei_local->dमुख्यg |= 0x01;
	/* We should alपढ़ोy be in page 0, but to be safe... */
	ei_outb(E8390_PAGE0 + E8390_START + E8390_NODMA, addr + NE_CMD);

	ei_outb(ENISR_RDC, addr + NE_EN0_ISR);

	/* Now the normal output. */
	ei_outb(count & 0xff, addr + NE_EN0_RCNTLO);
	ei_outb(count >> 8, addr + NE_EN0_RCNTHI);
	ei_outb(0x00, addr + NE_EN0_RSARLO);
	ei_outb(start_page, addr + NE_EN0_RSARHI);
	ei_outb(E8390_RWRITE + E8390_START, addr + NE_CMD);

	ei_outsw(addr + NE_DATAPORT, buf, count >> 1);

	dma_start = jअगरfies;
	जबतक ((ei_inb(addr + NE_EN0_ISR) & ENISR_RDC) == 0) अणु
		अगर (समय_after(jअगरfies, dma_start + 2 * HZ / 100)) अणु /* 20ms */
			netdev_warn(dev, "timeout waiting for Tx RDC\n");
			mcf8390_reset_8390(dev);
			__NS8390_init(dev, 1);
			अवरोध;
		पूर्ण
	पूर्ण

	ei_outb(ENISR_RDC, addr + NE_EN0_ISR);	/* Ack पूर्णांकr */
	ei_local->dमुख्यg &= ~0x01;
पूर्ण

अटल स्थिर काष्ठा net_device_ops mcf8390_netdev_ops = अणु
	.nकरो_खोलो		= __ei_खोलो,
	.nकरो_stop		= __ei_बंद,
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

अटल पूर्णांक mcf8390_init(काष्ठा net_device *dev)
अणु
	अटल u32 offsets[] = अणु
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	पूर्ण;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित अक्षर SA_prom[32];
	u32 addr = dev->base_addr;
	पूर्णांक start_page, stop_page;
	पूर्णांक i, ret;

	mcf8390_reset_8390(dev);

	/*
	 * Read the 16 bytes of station address PROM.
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
		क्रम (i = 0; i < ARRAY_SIZE(program_seq); i++) अणु
			ei_outb(program_seq[i].value,
				 addr + program_seq[i].offset);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 16; i++) अणु
		SA_prom[i] = ei_inb(addr + NE_DATAPORT);
		ei_inb(addr + NE_DATAPORT);
	पूर्ण

	/* We must set the 8390 क्रम word mode. */
	ei_outb(0x49, addr + NE_EN0_DCFG);
	start_page = NESM_START_PG;
	stop_page = NESM_STOP_PG;

	/* Install the Interrupt handler */
	ret = request_irq(dev->irq, __ei_पूर्णांकerrupt, 0, dev->name, dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ETH_ALEN; i++)
		dev->dev_addr[i] = SA_prom[i];

	netdev_dbg(dev, "Found ethernet address: %pM\n", dev->dev_addr);

	ei_local->name = "mcf8390";
	ei_local->tx_start_page = start_page;
	ei_local->stop_page = stop_page;
	ei_local->word16 = 1;
	ei_local->rx_start_page = start_page + TX_PAGES;
	ei_local->reset_8390 = mcf8390_reset_8390;
	ei_local->block_input = mcf8390_block_input;
	ei_local->block_output = mcf8390_block_output;
	ei_local->get_8390_hdr = mcf8390_get_8390_hdr;
	ei_local->reg_offset = offsets;

	dev->netdev_ops = &mcf8390_netdev_ops;
	__NS8390_init(dev, 0);
	ret = रेजिस्टर_netdev(dev);
	अगर (ret) अणु
		मुक्त_irq(dev->irq, dev);
		वापस ret;
	पूर्ण

	netdev_info(dev, "addr=0x%08x irq=%d, Ethernet Address %pM\n",
		addr, dev->irq, dev->dev_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक mcf8390_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा resource *mem, *irq;
	resource_माप_प्रकार msize;
	पूर्णांक ret;

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (irq == शून्य) अणु
		dev_err(&pdev->dev, "no IRQ specified?\n");
		वापस -ENXIO;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (mem == शून्य) अणु
		dev_err(&pdev->dev, "no memory address specified?\n");
		वापस -ENXIO;
	पूर्ण
	msize = resource_size(mem);
	अगर (!request_mem_region(mem->start, msize, pdev->name))
		वापस -EBUSY;

	dev = ____alloc_ei_netdev(0);
	अगर (dev == शून्य) अणु
		release_mem_region(mem->start, msize);
		वापस -ENOMEM;
	पूर्ण

	SET_NETDEV_DEV(dev, &pdev->dev);
	platक्रमm_set_drvdata(pdev, dev);

	dev->irq = irq->start;
	dev->base_addr = mem->start;

	ret = mcf8390_init(dev);
	अगर (ret) अणु
		release_mem_region(mem->start, msize);
		मुक्त_netdev(dev);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mcf8390_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *mem;

	unरेजिस्टर_netdev(dev);
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (mem)
		release_mem_region(mem->start, resource_size(mem));
	मुक्त_netdev(dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mcf8390_drv = अणु
	.driver = अणु
		.name	= "mcf8390",
	पूर्ण,
	.probe		= mcf8390_probe,
	.हटाओ		= mcf8390_हटाओ,
पूर्ण;

module_platक्रमm_driver(mcf8390_drv);

MODULE_DESCRIPTION("MCF8390 ColdFire NS8390 driver");
MODULE_AUTHOR("Greg Ungerer <gerg@uclinux.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mcf8390");
