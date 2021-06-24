<शैली गुरु>
/*
 * Amiga Linux/68k 8390 based PCMCIA Ethernet Driver क्रम the Amiga 1200
 *
 * (C) Copyright 1997 Alain Malek
 *                    (Alain.Malek@cryogen.com)
 *
 * ----------------------------------------------------------------------------
 *
 * This program is based on
 *
 * ne.c:       A general non-shared-memory NS8390 ethernet driver क्रम linux
 *             Written 1992-94 by Donald Becker.
 *
 * 8390.c:     A general NS8390 ethernet driver core क्रम linux.
 *             Written 1992-94 by Donald Becker.
 *
 * cnetdevice: A Sana-II ethernet driver क्रम AmigaOS
 *             Written by Bruce Abbott (bhabbott@inhb.co.nz)
 *
 * ----------------------------------------------------------------------------
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of the Linux
 * distribution क्रम more details.
 *
 * ----------------------------------------------------------------------------
 *
 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigayle.h>
#समावेश <यंत्र/amipcmcia.h>

#समावेश "8390.h"

/* ---- No user-serviceable parts below ---- */

#घोषणा DRV_NAME "apne"

#घोषणा NE_BASE	 (dev->base_addr)
#घोषणा NE_CMD	 		0x00
#घोषणा NE_DATAPORT		0x10            /* NatSemi-defined port winकरोw offset. */
#घोषणा NE_RESET		0x1f            /* Issue a पढ़ो to reset, a ग_लिखो to clear. */
#घोषणा NE_IO_EXTENT	        0x20

#घोषणा NE_EN0_ISR		0x07
#घोषणा NE_EN0_DCFG		0x0e

#घोषणा NE_EN0_RSARLO	        0x08
#घोषणा NE_EN0_RSARHI	        0x09
#घोषणा NE_EN0_RCNTLO	        0x0a
#घोषणा NE_EN0_RXCR		0x0c
#घोषणा NE_EN0_TXCR		0x0d
#घोषणा NE_EN0_RCNTHI	        0x0b
#घोषणा NE_EN0_IMR		0x0f

#घोषणा NE1SM_START_PG	0x20	/* First page of TX buffer */
#घोषणा NE1SM_STOP_PG 	0x40	/* Last page +1 of RX ring */
#घोषणा NESM_START_PG	0x40	/* First page of TX buffer */
#घोषणा NESM_STOP_PG	0x80	/* Last page +1 of RX ring */


काष्ठा net_device * __init apne_probe(पूर्णांक unit);
अटल पूर्णांक apne_probe1(काष्ठा net_device *dev, पूर्णांक ioaddr);

अटल व्योम apne_reset_8390(काष्ठा net_device *dev);
अटल व्योम apne_get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr,
			  पूर्णांक ring_page);
अटल व्योम apne_block_input(काष्ठा net_device *dev, पूर्णांक count,
								काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम apne_block_output(काष्ठा net_device *dev, स्थिर पूर्णांक count,
							स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page);
अटल irqवापस_t apne_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

अटल पूर्णांक init_pcmcia(व्योम);

/* IO base address used क्रम nic */

#घोषणा IOBASE 0x300

/*
   use MANUAL_CONFIG and MANUAL_OFFSET क्रम enabling IO by hand
   you can find the values to use by looking at the cnet.device
   config file example (the शेष values are क्रम the CNET40BC card)
*/

/*
#घोषणा MANUAL_CONFIG 0x20
#घोषणा MANUAL_OFFSET 0x3f8

#घोषणा MANUAL_HWADDR0 0x00
#घोषणा MANUAL_HWADDR1 0x12
#घोषणा MANUAL_HWADDR2 0x34
#घोषणा MANUAL_HWADDR3 0x56
#घोषणा MANUAL_HWADDR4 0x78
#घोषणा MANUAL_HWADDR5 0x9a
*/

अटल स्थिर अक्षर version[] =
    "apne.c:v1.1 7/10/98 Alain Malek (Alain.Malek@cryogen.ch)\n";

अटल पूर्णांक apne_owned;	/* संकेत अगर card alपढ़ोy owned */

अटल u32 apne_msg_enable;
module_param_named(msg_enable, apne_msg_enable, uपूर्णांक, 0444);
MODULE_PARM_DESC(msg_enable, "Debug message level (see linux/netdevice.h for bitmap)");

काष्ठा net_device * __init apne_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev;
	काष्ठा ei_device *ei_local;

#अगर_अघोषित MANUAL_CONFIG
	अक्षर tuple[8];
#पूर्ण_अगर
	पूर्णांक err;

	अगर (!MACH_IS_AMIGA)
		वापस ERR_PTR(-ENODEV);

	अगर (apne_owned)
		वापस ERR_PTR(-ENODEV);

	अगर ( !(AMIGAHW_PRESENT(PCMCIA)) )
		वापस ERR_PTR(-ENODEV);

	pr_info("Looking for PCMCIA ethernet card : ");

	/* check अगर a card is inserted */
	अगर (!(PCMCIA_INSERTED)) अणु
		pr_cont("NO PCMCIA card inserted\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	dev = alloc_ei_netdev();
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);
	अगर (unit >= 0) अणु
		प्र_लिखो(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
	पूर्ण
	ei_local = netdev_priv(dev);
	ei_local->msg_enable = apne_msg_enable;

	/* disable pcmcia irq क्रम पढ़ोtuple */
	pcmcia_disable_irq();

#अगर_अघोषित MANUAL_CONFIG
	अगर ((pcmcia_copy_tuple(CISTPL_FUNCID, tuple, 8) < 3) ||
		(tuple[2] != CISTPL_FUNCID_NETWORK)) अणु
		pr_cont("not an ethernet card\n");
		/* XXX: shouldn't we re-enable irq here? */
		मुक्त_netdev(dev);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
#पूर्ण_अगर

	pr_cont("ethernet PCMCIA card inserted\n");

	अगर (!init_pcmcia()) अणु
		/* XXX: shouldn't we re-enable irq here? */
		मुक्त_netdev(dev);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	अगर (!request_region(IOBASE, 0x20, DRV_NAME)) अणु
		मुक्त_netdev(dev);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	err = apne_probe1(dev, IOBASE);
	अगर (err) अणु
		release_region(IOBASE, 0x20);
		मुक्त_netdev(dev);
		वापस ERR_PTR(err);
	पूर्ण
	err = रेजिस्टर_netdev(dev);
	अगर (!err)
		वापस dev;

	pcmcia_disable_irq();
	मुक्त_irq(IRQ_AMIGA_PORTS, dev);
	pcmcia_reset();
	release_region(IOBASE, 0x20);
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक __init apne_probe1(काष्ठा net_device *dev, पूर्णांक ioaddr)
अणु
    पूर्णांक i;
    अचिन्हित अक्षर SA_prom[32];
    पूर्णांक wordlength = 2;
    स्थिर अक्षर *name = शून्य;
    पूर्णांक start_page, stop_page;
#अगर_अघोषित MANUAL_HWADDR0
    पूर्णांक neX000, ctron;
#पूर्ण_अगर
    अटल अचिन्हित version_prपूर्णांकed;

    अगर ((apne_msg_enable & NETIF_MSG_DRV) && (version_prपूर्णांकed++ == 0))
		netdev_info(dev, version);

    netdev_info(dev, "PCMCIA NE*000 ethercard probe");

    /* Reset card. Who knows what dain-bramaged state it was left in. */
    अणु	अचिन्हित दीर्घ reset_start_समय = jअगरfies;

	outb(inb(ioaddr + NE_RESET), ioaddr + NE_RESET);

	जबतक ((inb(ioaddr + NE_EN0_ISR) & ENISR_RESET) == 0)
		अगर (समय_after(jअगरfies, reset_start_समय + 2*HZ/100)) अणु
			pr_cont(" not found (no reset ack).\n");
			वापस -ENODEV;
		पूर्ण

	outb(0xff, ioaddr + NE_EN0_ISR);		/* Ack all पूर्णांकr. */
    पूर्ण

#अगर_अघोषित MANUAL_HWADDR0

    /* Read the 16 bytes of station address PROM.
       We must first initialize रेजिस्टरs, similar to NS8390_init(eअगरdev, 0).
       We can't reliably पढ़ो the SAPROM address without this.
       (I learned the hard way!). */
    अणु
	काष्ठा अणुअचिन्हित दीर्घ value, offset; पूर्ण program_seq[] = अणु
	    अणुE8390_NODMA+E8390_PAGE0+E8390_STOP, NE_CMDपूर्ण, /* Select page 0*/
	    अणु0x48,	NE_EN0_DCFGपूर्ण,	/* Set byte-wide (0x48) access. */
	    अणु0x00,	NE_EN0_RCNTLOपूर्ण,	/* Clear the count regs. */
	    अणु0x00,	NE_EN0_RCNTHIपूर्ण,
	    अणु0x00,	NE_EN0_IMRपूर्ण,	/* Mask completion irq. */
	    अणु0xFF,	NE_EN0_ISRपूर्ण,
	    अणुE8390_RXOFF, NE_EN0_RXCRपूर्ण,	/* 0x20  Set to monitor */
	    अणुE8390_TXOFF, NE_EN0_TXCRपूर्ण,	/* 0x02  and loopback mode. */
	    अणु32,	NE_EN0_RCNTLOपूर्ण,
	    अणु0x00,	NE_EN0_RCNTHIपूर्ण,
	    अणु0x00,	NE_EN0_RSARLOपूर्ण,	/* DMA starting at 0x0000. */
	    अणु0x00,	NE_EN0_RSARHIपूर्ण,
	    अणुE8390_RREAD+E8390_START, NE_CMDपूर्ण,
	पूर्ण;
	क्रम (i = 0; i < ARRAY_SIZE(program_seq); i++) अणु
	    outb(program_seq[i].value, ioaddr + program_seq[i].offset);
	पूर्ण

    पूर्ण
    क्रम(i = 0; i < 32 /*माप(SA_prom)*/; i+=2) अणु
	SA_prom[i] = inb(ioaddr + NE_DATAPORT);
	SA_prom[i+1] = inb(ioaddr + NE_DATAPORT);
	अगर (SA_prom[i] != SA_prom[i+1])
	    wordlength = 1;
    पूर्ण

    /*	At this poपूर्णांक, wordlength *only* tells us अगर the SA_prom is द्विगुनd
	up or not because some broken PCI cards करोn't respect the byte-wide
	request in program_seq above, and hence करोn't have द्विगुनd up values.
	These broken cards would otherwise be detected as an ne1000.  */

    अगर (wordlength == 2)
	क्रम (i = 0; i < 16; i++)
		SA_prom[i] = SA_prom[i+i];

    अगर (wordlength == 2) अणु
	/* We must set the 8390 क्रम word mode. */
	outb(0x49, ioaddr + NE_EN0_DCFG);
	start_page = NESM_START_PG;
	stop_page = NESM_STOP_PG;
    पूर्ण अन्यथा अणु
	start_page = NE1SM_START_PG;
	stop_page = NE1SM_STOP_PG;
    पूर्ण

    neX000 = (SA_prom[14] == 0x57  &&  SA_prom[15] == 0x57);
    ctron =  (SA_prom[0] == 0x00 && SA_prom[1] == 0x00 && SA_prom[2] == 0x1d);

    /* Set up the rest of the parameters. */
    अगर (neX000) अणु
	name = (wordlength == 2) ? "NE2000" : "NE1000";
    पूर्ण अन्यथा अगर (ctron) अणु
	name = (wordlength == 2) ? "Ctron-8" : "Ctron-16";
	start_page = 0x01;
	stop_page = (wordlength == 2) ? 0x40 : 0x20;
    पूर्ण अन्यथा अणु
	pr_cont(" not found.\n");
	वापस -ENXIO;

    पूर्ण

#अन्यथा
    wordlength = 2;
    /* We must set the 8390 क्रम word mode. */
    outb(0x49, ioaddr + NE_EN0_DCFG);
    start_page = NESM_START_PG;
    stop_page = NESM_STOP_PG;

    SA_prom[0] = MANUAL_HWADDR0;
    SA_prom[1] = MANUAL_HWADDR1;
    SA_prom[2] = MANUAL_HWADDR2;
    SA_prom[3] = MANUAL_HWADDR3;
    SA_prom[4] = MANUAL_HWADDR4;
    SA_prom[5] = MANUAL_HWADDR5;
    name = "NE2000";
#पूर्ण_अगर

    dev->base_addr = ioaddr;
    dev->irq = IRQ_AMIGA_PORTS;
    dev->netdev_ops = &ei_netdev_ops;

    /* Install the Interrupt handler */
    i = request_irq(dev->irq, apne_पूर्णांकerrupt, IRQF_SHARED, DRV_NAME, dev);
    अगर (i) वापस i;

    क्रम (i = 0; i < ETH_ALEN; i++)
	dev->dev_addr[i] = SA_prom[i];

    pr_cont(" %pM\n", dev->dev_addr);

    netdev_info(dev, "%s found.\n", name);

    ei_status.name = name;
    ei_status.tx_start_page = start_page;
    ei_status.stop_page = stop_page;
    ei_status.word16 = (wordlength == 2);

    ei_status.rx_start_page = start_page + TX_PAGES;

    ei_status.reset_8390 = &apne_reset_8390;
    ei_status.block_input = &apne_block_input;
    ei_status.block_output = &apne_block_output;
    ei_status.get_8390_hdr = &apne_get_8390_hdr;

    NS8390_init(dev, 0);

    pcmcia_ack_पूर्णांक(pcmcia_get_पूर्णांकreq());		/* ack PCMCIA पूर्णांक req */
    pcmcia_enable_irq();

    apne_owned = 1;

    वापस 0;
पूर्ण

/* Hard reset the card.  This used to छोड़ो क्रम the same period that a
   8390 reset command required, but that shouldn't be necessary. */
अटल व्योम
apne_reset_8390(काष्ठा net_device *dev)
अणु
    अचिन्हित दीर्घ reset_start_समय = jअगरfies;
    काष्ठा ei_device *ei_local = netdev_priv(dev);

    init_pcmcia();

    netअगर_dbg(ei_local, hw, dev, "resetting the 8390 t=%ld...\n", jअगरfies);

    outb(inb(NE_BASE + NE_RESET), NE_BASE + NE_RESET);

    ei_status.txing = 0;
    ei_status.dमुख्यg = 0;

    /* This check _should_not_ be necessary, omit eventually. */
    जबतक ((inb(NE_BASE+NE_EN0_ISR) & ENISR_RESET) == 0)
	अगर (समय_after(jअगरfies, reset_start_समय + 2*HZ/100)) अणु
		netdev_err(dev, "ne_reset_8390() did not complete.\n");
		अवरोध;
	पूर्ण
    outb(ENISR_RESET, NE_BASE + NE_EN0_ISR);	/* Ack पूर्णांकr. */
पूर्ण

/* Grab the 8390 specअगरic header. Similar to the block_input routine, but
   we करोn't need to be concerned with ring wrap as the header will be at
   the start of a page, so we optimize accordingly. */

अटल व्योम
apne_get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु

    पूर्णांक nic_base = dev->base_addr;
    पूर्णांक cnt;
    अक्षर *ptrc;
    लघु *ptrs;

    /* This *shouldn't* happen. If it does, it's the last thing you'll see */
    अगर (ei_status.dमुख्यg) अणु
	netdev_err(dev, "DMAing conflict in ne_get_8390_hdr "
		   "[DMAstat:%d][irqlock:%d][intr:%d].\n",
		   ei_status.dमुख्यg, ei_status.irqlock, dev->irq);
	वापस;
    पूर्ण

    ei_status.dमुख्यg |= 0x01;
    outb(E8390_NODMA+E8390_PAGE0+E8390_START, nic_base+ NE_CMD);
    outb(ENISR_RDC, nic_base + NE_EN0_ISR);
    outb(माप(काष्ठा e8390_pkt_hdr), nic_base + NE_EN0_RCNTLO);
    outb(0, nic_base + NE_EN0_RCNTHI);
    outb(0, nic_base + NE_EN0_RSARLO);		/* On page boundary */
    outb(ring_page, nic_base + NE_EN0_RSARHI);
    outb(E8390_RREAD+E8390_START, nic_base + NE_CMD);

    अगर (ei_status.word16) अणु
        ptrs = (लघु*)hdr;
        क्रम(cnt = 0; cnt < (माप(काष्ठा e8390_pkt_hdr)>>1); cnt++)
            *ptrs++ = inw(NE_BASE + NE_DATAPORT);
    पूर्ण अन्यथा अणु
        ptrc = (अक्षर*)hdr;
        क्रम(cnt = 0; cnt < माप(काष्ठा e8390_pkt_hdr); cnt++)
            *ptrc++ = inb(NE_BASE + NE_DATAPORT);
    पूर्ण

    outb(ENISR_RDC, nic_base + NE_EN0_ISR);	/* Ack पूर्णांकr. */
    ei_status.dमुख्यg &= ~0x01;

    le16_to_cpus(&hdr->count);
पूर्ण

/* Block input and output, similar to the Crynwr packet driver.  If you
   are porting to a new ethercard, look at the packet driver source क्रम hपूर्णांकs.
   The NEx000 करोesn't share the on-board packet memory -- you have to put
   the packet out through the "remote DMA" dataport using outb. */

अटल व्योम
apne_block_input(काष्ठा net_device *dev, पूर्णांक count, काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
    पूर्णांक nic_base = dev->base_addr;
    अक्षर *buf = skb->data;
    अक्षर *ptrc;
    लघु *ptrs;
    पूर्णांक cnt;

    /* This *shouldn't* happen. If it does, it's the last thing you'll see */
    अगर (ei_status.dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in ne_block_input "
			   "[DMAstat:%d][irqlock:%d][intr:%d].\n",
			   ei_status.dमुख्यg, ei_status.irqlock, dev->irq);
	वापस;
    पूर्ण
    ei_status.dमुख्यg |= 0x01;
    outb(E8390_NODMA+E8390_PAGE0+E8390_START, nic_base+ NE_CMD);
    outb(ENISR_RDC, nic_base + NE_EN0_ISR);
    outb(count & 0xff, nic_base + NE_EN0_RCNTLO);
    outb(count >> 8, nic_base + NE_EN0_RCNTHI);
    outb(ring_offset & 0xff, nic_base + NE_EN0_RSARLO);
    outb(ring_offset >> 8, nic_base + NE_EN0_RSARHI);
    outb(E8390_RREAD+E8390_START, nic_base + NE_CMD);
    अगर (ei_status.word16) अणु
      ptrs = (लघु*)buf;
      क्रम (cnt = 0; cnt < (count>>1); cnt++)
        *ptrs++ = inw(NE_BASE + NE_DATAPORT);
      अगर (count & 0x01) अणु
	buf[count-1] = inb(NE_BASE + NE_DATAPORT);
      पूर्ण
    पूर्ण अन्यथा अणु
      ptrc = buf;
      क्रम (cnt = 0; cnt < count; cnt++)
        *ptrc++ = inb(NE_BASE + NE_DATAPORT);
    पूर्ण

    outb(ENISR_RDC, nic_base + NE_EN0_ISR);	/* Ack पूर्णांकr. */
    ei_status.dमुख्यg &= ~0x01;
पूर्ण

अटल व्योम
apne_block_output(काष्ठा net_device *dev, पूर्णांक count,
		स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page)
अणु
    पूर्णांक nic_base = NE_BASE;
    अचिन्हित दीर्घ dma_start;
    अक्षर *ptrc;
    लघु *ptrs;
    पूर्णांक cnt;

    /* Round the count up क्रम word ग_लिखोs.  Do we need to करो this?
       What effect will an odd byte count have on the 8390?
       I should check someday. */
    अगर (ei_status.word16 && (count & 0x01))
      count++;

    /* This *shouldn't* happen. If it does, it's the last thing you'll see */
    अगर (ei_status.dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in ne_block_output."
			   "[DMAstat:%d][irqlock:%d][intr:%d]\n",
			   ei_status.dमुख्यg, ei_status.irqlock, dev->irq);
	वापस;
    पूर्ण
    ei_status.dमुख्यg |= 0x01;
    /* We should alपढ़ोy be in page 0, but to be safe... */
    outb(E8390_PAGE0+E8390_START+E8390_NODMA, nic_base + NE_CMD);

    outb(ENISR_RDC, nic_base + NE_EN0_ISR);

   /* Now the normal output. */
    outb(count & 0xff, nic_base + NE_EN0_RCNTLO);
    outb(count >> 8,   nic_base + NE_EN0_RCNTHI);
    outb(0x00, nic_base + NE_EN0_RSARLO);
    outb(start_page, nic_base + NE_EN0_RSARHI);

    outb(E8390_RWRITE+E8390_START, nic_base + NE_CMD);
    अगर (ei_status.word16) अणु
        ptrs = (लघु*)buf;
        क्रम (cnt = 0; cnt < count>>1; cnt++)
            outw(*ptrs++, NE_BASE+NE_DATAPORT);
    पूर्ण अन्यथा अणु
        ptrc = (अक्षर*)buf;
        क्रम (cnt = 0; cnt < count; cnt++)
	    outb(*ptrc++, NE_BASE + NE_DATAPORT);
    पूर्ण

    dma_start = jअगरfies;

    जबतक ((inb(NE_BASE + NE_EN0_ISR) & ENISR_RDC) == 0)
	अगर (समय_after(jअगरfies, dma_start + 2*HZ/100)) अणु	/* 20ms */
		netdev_warn(dev, "timeout waiting for Tx RDC.\n");
		apne_reset_8390(dev);
		NS8390_init(dev,1);
		अवरोध;
	पूर्ण

    outb(ENISR_RDC, nic_base + NE_EN0_ISR);	/* Ack पूर्णांकr. */
    ei_status.dमुख्यg &= ~0x01;
पूर्ण

अटल irqवापस_t apne_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
    अचिन्हित अक्षर pcmcia_पूर्णांकreq;

    अगर (!(gayle.पूर्णांकen & GAYLE_IRQ_IRQ))
        वापस IRQ_NONE;

    pcmcia_पूर्णांकreq = pcmcia_get_पूर्णांकreq();

    अगर (!(pcmcia_पूर्णांकreq & GAYLE_IRQ_IRQ)) अणु
        pcmcia_ack_पूर्णांक(pcmcia_पूर्णांकreq);
        वापस IRQ_NONE;
    पूर्ण
    अगर (apne_msg_enable & NETIF_MSG_INTR)
	pr_debug("pcmcia intreq = %x\n", pcmcia_पूर्णांकreq);
    pcmcia_disable_irq();			/* to get rid of the sti() within ei_पूर्णांकerrupt */
    ei_पूर्णांकerrupt(irq, dev_id);
    pcmcia_ack_पूर्णांक(pcmcia_get_पूर्णांकreq());
    pcmcia_enable_irq();
    वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित MODULE
अटल काष्ठा net_device *apne_dev;

अटल पूर्णांक __init apne_module_init(व्योम)
अणु
	apne_dev = apne_probe(-1);
	वापस PTR_ERR_OR_ZERO(apne_dev);
पूर्ण

अटल व्योम __निकास apne_module_निकास(व्योम)
अणु
	unरेजिस्टर_netdev(apne_dev);

	pcmcia_disable_irq();

	मुक्त_irq(IRQ_AMIGA_PORTS, apne_dev);

	pcmcia_reset();

	release_region(IOBASE, 0x20);

	मुक्त_netdev(apne_dev);
पूर्ण
module_init(apne_module_init);
module_निकास(apne_module_निकास);
#पूर्ण_अगर

अटल पूर्णांक init_pcmcia(व्योम)
अणु
	u_अक्षर config;
#अगर_अघोषित MANUAL_CONFIG
	u_अक्षर tuple[32];
	पूर्णांक offset_len;
#पूर्ण_अगर
	u_दीर्घ offset;

	pcmcia_reset();
	pcmcia_program_voltage(PCMCIA_0V);
	pcmcia_access_speed(PCMCIA_SPEED_250NS);
	pcmcia_ग_लिखो_enable();

#अगर_घोषित MANUAL_CONFIG
	config = MANUAL_CONFIG;
#अन्यथा
	/* get and ग_लिखो config byte to enable IO port */

	अगर (pcmcia_copy_tuple(CISTPL_CFTABLE_ENTRY, tuple, 32) < 3)
		वापस 0;

	config = tuple[2] & 0x3f;
#पूर्ण_अगर
#अगर_घोषित MANUAL_OFFSET
	offset = MANUAL_OFFSET;
#अन्यथा
	अगर (pcmcia_copy_tuple(CISTPL_CONFIG, tuple, 32) < 6)
		वापस 0;

	offset_len = (tuple[2] & 0x3) + 1;
	offset = 0;
	जबतक(offset_len--) अणु
		offset = (offset << 8) | tuple[4+offset_len];
	पूर्ण
#पूर्ण_अगर

	out_8(GAYLE_ATTRIBUTE+offset, config);

	वापस 1;
पूर्ण

MODULE_LICENSE("GPL");
