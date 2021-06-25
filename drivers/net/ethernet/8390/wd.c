<शैली गुरु>
/* wd.c: A WD80x3 ethernet driver क्रम linux. */
/*
	Written 1993-94 by Donald Becker.

	Copyright 1993 United States Government as represented by the
	Director, National Security Agency.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	This is a driver क्रम WD8003 and WD8013 "compatible" ethercards.

	Thanks to Russ Nelson (nelson@crnwyr.com) क्रम loaning me a WD8013.

	Changelog:

	Paul Gorपंचांगaker	: multiple card support क्रम module users, support
			  क्रम non-standard memory sizes.


*/

अटल स्थिर अक्षर version[] =
	"wd.c:v1.10 9/23/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)\n";

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>

#समावेश <यंत्र/पन.स>

#समावेश "8390.h"

#घोषणा DRV_NAME "wd"

/* A zero-terminated list of I/O addresses to be probed. */
अटल अचिन्हित पूर्णांक wd_portlist[] __initdata =
अणु0x300, 0x280, 0x380, 0x240, 0पूर्ण;

अटल पूर्णांक wd_probe1(काष्ठा net_device *dev, पूर्णांक ioaddr);

अटल पूर्णांक wd_खोलो(काष्ठा net_device *dev);
अटल व्योम wd_reset_8390(काष्ठा net_device *dev);
अटल व्योम wd_get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr,
						पूर्णांक ring_page);
अटल व्योम wd_block_input(काष्ठा net_device *dev, पूर्णांक count,
						  काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम wd_block_output(काष्ठा net_device *dev, पूर्णांक count,
							स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page);
अटल पूर्णांक wd_बंद(काष्ठा net_device *dev);

अटल u32 wd_msg_enable;

#घोषणा WD_START_PG		0x00	/* First page of TX buffer */
#घोषणा WD03_STOP_PG	0x20	/* Last page +1 of RX ring */
#घोषणा WD13_STOP_PG	0x40	/* Last page +1 of RX ring */

#घोषणा WD_CMDREG		0		/* Offset to ASIC command रेजिस्टर. */
#घोषणा	 WD_RESET		0x80	/* Board reset, in WD_CMDREG. */
#घोषणा	 WD_MEMENB		0x40	/* Enable the shared memory. */
#घोषणा WD_CMDREG5		5		/* Offset to 16-bit-only ASIC रेजिस्टर 5. */
#घोषणा	 ISA16			0x80	/* Enable 16 bit access from the ISA bus. */
#घोषणा	 NIC16			0x40	/* Enable 16 bit access from the 8390. */
#घोषणा WD_NIC_OFFSET	16		/* Offset to the 8390 from the base_addr. */
#घोषणा WD_IO_EXTENT	32


/*	Probe क्रम the WD8003 and WD8013.  These cards have the station
	address PROM at I/O ports <base>+8 to <base>+13, with a checksum
	following. A Soundblaster can have the same checksum as an WDethercard,
	so we have an extra exclusionary check क्रम it.

	The wd_probe1() routine initializes the card and fills the
	station address field. */

अटल पूर्णांक __init करो_wd_probe(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा resource *r;
	पूर्णांक base_addr = dev->base_addr;
	पूर्णांक irq = dev->irq;
	पूर्णांक mem_start = dev->mem_start;
	पूर्णांक mem_end = dev->mem_end;

	अगर (base_addr > 0x1ff) अणु	/* Check a user specअगरied location. */
		r = request_region(base_addr, WD_IO_EXTENT, "wd-probe");
		अगर ( r == शून्य)
			वापस -EBUSY;
		i = wd_probe1(dev, base_addr);
		अगर (i != 0)
			release_region(base_addr, WD_IO_EXTENT);
		अन्यथा
			r->name = dev->name;
		वापस i;
	पूर्ण
	अन्यथा अगर (base_addr != 0)	/* Don't probe at all. */
		वापस -ENXIO;

	क्रम (i = 0; wd_portlist[i]; i++) अणु
		पूर्णांक ioaddr = wd_portlist[i];
		r = request_region(ioaddr, WD_IO_EXTENT, "wd-probe");
		अगर (r == शून्य)
			जारी;
		अगर (wd_probe1(dev, ioaddr) == 0) अणु
			r->name = dev->name;
			वापस 0;
		पूर्ण
		release_region(ioaddr, WD_IO_EXTENT);
		dev->irq = irq;
		dev->mem_start = mem_start;
		dev->mem_end = mem_end;
	पूर्ण

	वापस -ENODEV;
पूर्ण

#अगर_अघोषित MODULE
काष्ठा net_device * __init wd_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev = alloc_ei_netdev();
	पूर्णांक err;

	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	प्र_लिखो(dev->name, "eth%d", unit);
	netdev_boot_setup_check(dev);

	err = करो_wd_probe(dev);
	अगर (err)
		जाओ out;
	वापस dev;
out:
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops wd_netdev_ops = अणु
	.nकरो_खोलो		= wd_खोलो,
	.nकरो_stop		= wd_बंद,
	.nकरो_start_xmit		= ei_start_xmit,
	.nकरो_tx_समयout		= ei_tx_समयout,
	.nकरो_get_stats		= ei_get_stats,
	.nकरो_set_rx_mode	= ei_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller 	= ei_poll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init wd_probe1(काष्ठा net_device *dev, पूर्णांक ioaddr)
अणु
	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक checksum = 0;
	पूर्णांक ancient = 0;			/* An old card without config रेजिस्टरs. */
	पूर्णांक word16 = 0;				/* 0 = 8 bit, 1 = 16 bit */
	स्थिर अक्षर *model_name;
	अटल अचिन्हित version_prपूर्णांकed;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	क्रम (i = 0; i < 8; i++)
		checksum += inb(ioaddr + 8 + i);
	अगर (inb(ioaddr + 8) == 0xff 	/* Extra check to aव्योम soundcard. */
		|| inb(ioaddr + 9) == 0xff
		|| (checksum & 0xff) != 0xFF)
		वापस -ENODEV;

	/* Check क्रम semi-valid mem_start/end values अगर supplied. */
	अगर ((dev->mem_start % 0x2000) || (dev->mem_end % 0x2000)) अणु
		netdev_warn(dev,
			    "wd.c: user supplied mem_start or mem_end not on 8kB boundary - ignored.\n");
		dev->mem_start = 0;
		dev->mem_end = 0;
	पूर्ण

	अगर ((wd_msg_enable & NETIF_MSG_DRV) && (version_prपूर्णांकed++ == 0))
		netdev_info(dev, version);

	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = inb(ioaddr + 8 + i);

	netdev_info(dev, "WD80x3 at %#3x, %pM", ioaddr, dev->dev_addr);

	/* The following PureData probe code was contributed by
	   Mike Jagdis <jaggy@purplet.demon.co.uk>. Puredata करोes software
	   configuration dअगरferently from others so we have to check क्रम them.
	   This detects an 8 bit, 16 bit or dumb (Toshiba, jumpered) card.
	   */
	अगर (inb(ioaddr+0) == 'P' && inb(ioaddr+1) == 'D') अणु
		अचिन्हित अक्षर reg5 = inb(ioaddr+5);

		चयन (inb(ioaddr+2)) अणु
		हाल 0x03: word16 = 0; model_name = "PDI8023-8";	अवरोध;
		हाल 0x05: word16 = 0; model_name = "PDUC8023";	अवरोध;
		हाल 0x0a: word16 = 1; model_name = "PDI8023-16"; अवरोध;
			/* Either 0x01 (dumb) or they've released a new version. */
		शेष:	 word16 = 0; model_name = "PDI8023";	अवरोध;
		पूर्ण
		dev->mem_start = ((reg5 & 0x1c) + 0xc0) << 12;
		dev->irq = (reg5 & 0xe0) == 0xe0 ? 10 : (reg5 >> 5) + 1;
	पूर्ण अन्यथा अणु								/* End of PureData probe */
		/* This method of checking क्रम a 16-bit board is borrowed from the
		   we.c driver.  A simpler method is just to look in ASIC reg. 0x03.
		   I'm comparing the two method in alpha test to make certain they
		   वापस the same result. */
		/* Check क्रम the old 8 bit board - it has रेजिस्टर 0/8 aliasing.
		   Do NOT check i>=6 here -- it hangs the old 8003 boards! */
		क्रम (i = 0; i < 6; i++)
			अगर (inb(ioaddr+i) != inb(ioaddr+8+i))
				अवरोध;
		अगर (i >= 6) अणु
			ancient = 1;
			model_name = "WD8003-old";
			word16 = 0;
		पूर्ण अन्यथा अणु
			पूर्णांक पंचांगp = inb(ioaddr+1); /* fiddle with 16bit bit */
			outb( पंचांगp ^ 0x01, ioaddr+1 ); /* attempt to clear 16bit bit */
			अगर (((inb( ioaddr+1) & 0x01) == 0x01) /* A 16 bit card */
				&& (पंचांगp & 0x01) == 0x01	) अणु				/* In a 16 slot. */
				पूर्णांक asic_reg5 = inb(ioaddr+WD_CMDREG5);
				/* Magic to set ASIC to word-wide mode. */
				outb( NIC16 | (asic_reg5&0x1f), ioaddr+WD_CMDREG5);
				outb(पंचांगp, ioaddr+1);
				model_name = "WD8013";
				word16 = 1;		/* We have a 16bit board here! */
			पूर्ण अन्यथा अणु
				model_name = "WD8003";
				word16 = 0;
			पूर्ण
			outb(पंचांगp, ioaddr+1);			/* Restore original reg1 value. */
		पूर्ण
#अगर_अघोषित final_version
		अगर ( !ancient && (inb(ioaddr+1) & 0x01) != (word16 & 0x01))
			pr_cont("\nWD80?3: Bus width conflict, %d (probe) != %d (reg report).",
				word16 ? 16 : 8,
				(inb(ioaddr+1) & 0x01) ? 16 : 8);
#पूर्ण_अगर
	पूर्ण

#अगर defined(WD_SHMEM) && WD_SHMEM > 0x80000
	/* Allow a compile-समय override.	 */
	dev->mem_start = WD_SHMEM;
#अन्यथा
	अगर (dev->mem_start == 0) अणु
		/* Sanity and old 8003 check */
		पूर्णांक reg0 = inb(ioaddr);
		अगर (reg0 == 0xff || reg0 == 0) अणु
			/* Future plan: this could check a few likely locations first. */
			dev->mem_start = 0xd0000;
			pr_cont(" assigning address %#lx", dev->mem_start);
		पूर्ण अन्यथा अणु
			पूर्णांक high_addr_bits = inb(ioaddr+WD_CMDREG5) & 0x1f;
			/* Some boards करोn't have the रेजिस्टर 5 -- it वापसs 0xff. */
			अगर (high_addr_bits == 0x1f || word16 == 0)
				high_addr_bits = 0x01;
			dev->mem_start = ((reg0&0x3f) << 13) + (high_addr_bits << 19);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* The 8390 isn't at the base address -- the ASIC regs are there! */
	dev->base_addr = ioaddr+WD_NIC_OFFSET;

	अगर (dev->irq < 2) अणु
		अटल स्थिर पूर्णांक irqmap[] = अणु9, 3, 5, 7, 10, 11, 15, 4पूर्ण;
		पूर्णांक reg1 = inb(ioaddr+1);
		पूर्णांक reg4 = inb(ioaddr+4);
		अगर (ancient || reg1 == 0xff) अणु	/* Ack!! No way to पढ़ो the IRQ! */
			लघु nic_addr = ioaddr+WD_NIC_OFFSET;
			अचिन्हित दीर्घ irq_mask;

			/* We have an old-style ethercard that करोesn't report its IRQ
			   line.  Do स्वतःirq to find the IRQ line. Note that this IS NOT
			   a reliable way to trigger an पूर्णांकerrupt. */
			outb_p(E8390_NODMA + E8390_STOP, nic_addr);
			outb(0x00, nic_addr+EN0_IMR);	/* Disable all पूर्णांकrs. */

			irq_mask = probe_irq_on();
			outb_p(0xff, nic_addr + EN0_IMR);	/* Enable all पूर्णांकerrupts. */
			outb_p(0x00, nic_addr + EN0_RCNTLO);
			outb_p(0x00, nic_addr + EN0_RCNTHI);
			outb(E8390_RREAD+E8390_START, nic_addr); /* Trigger it... */
			mdelay(20);
			dev->irq = probe_irq_off(irq_mask);

			outb_p(0x00, nic_addr+EN0_IMR);	/* Mask all पूर्णांकrs. again. */

			अगर (wd_msg_enable & NETIF_MSG_PROBE)
				pr_cont(" autoirq is %d", dev->irq);
			अगर (dev->irq < 2)
				dev->irq = word16 ? 10 : 5;
		पूर्ण अन्यथा
			dev->irq = irqmap[((reg4 >> 5) & 0x03) + (reg1 & 0x04)];
	पूर्ण अन्यथा अगर (dev->irq == 2)		/* Fixup bogosity: IRQ2 is really IRQ9 */
		dev->irq = 9;

	/* Snarf the पूर्णांकerrupt now.  There's no poपूर्णांक in रुकोing since we cannot
	   share and the board will usually be enabled. */
	i = request_irq(dev->irq, ei_पूर्णांकerrupt, 0, DRV_NAME, dev);
	अगर (i) अणु
		pr_cont(" unable to get IRQ %d.\n", dev->irq);
		वापस i;
	पूर्ण

	/* OK, were are certain this is going to work.  Setup the device. */
	ei_status.name = model_name;
	ei_status.word16 = word16;
	ei_status.tx_start_page = WD_START_PG;
	ei_status.rx_start_page = WD_START_PG + TX_PAGES;

	/* Don't map in the shared memory until the board is actually खोलोed. */

	/* Some cards (eg WD8003EBT) can be jumpered क्रम more (32k!) memory. */
	अगर (dev->mem_end != 0) अणु
		ei_status.stop_page = (dev->mem_end - dev->mem_start)/256;
		ei_status.priv = dev->mem_end - dev->mem_start;
	पूर्ण अन्यथा अणु
		ei_status.stop_page = word16 ? WD13_STOP_PG : WD03_STOP_PG;
		dev->mem_end = dev->mem_start + (ei_status.stop_page - WD_START_PG)*256;
		ei_status.priv = (ei_status.stop_page - WD_START_PG)*256;
	पूर्ण

	ei_status.mem = ioremap(dev->mem_start, ei_status.priv);
	अगर (!ei_status.mem) अणु
		मुक्त_irq(dev->irq, dev);
		वापस -ENOMEM;
	पूर्ण

	pr_cont(" %s, IRQ %d, shared memory at %#lx-%#lx.\n",
		model_name, dev->irq, dev->mem_start, dev->mem_end-1);

	ei_status.reset_8390 = wd_reset_8390;
	ei_status.block_input = wd_block_input;
	ei_status.block_output = wd_block_output;
	ei_status.get_8390_hdr = wd_get_8390_hdr;

	dev->netdev_ops = &wd_netdev_ops;
	NS8390_init(dev, 0);
	ei_local->msg_enable = wd_msg_enable;

#अगर 1
	/* Enable पूर्णांकerrupt generation on softconfig cards -- M.U */
	/* .. but possibly potentially unsafe - Donald */
	अगर (inb(ioaddr+14) & 0x20)
		outb(inb(ioaddr+4)|0x80, ioaddr+4);
#पूर्ण_अगर

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		मुक्त_irq(dev->irq, dev);
		iounmap(ei_status.mem);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
wd_खोलो(काष्ठा net_device *dev)
अणु
  पूर्णांक ioaddr = dev->base_addr - WD_NIC_OFFSET; /* WD_CMDREG */

  /* Map in the shared memory. Always set रेजिस्टर 0 last to reमुख्य
	 compatible with very old boards. */
  ei_status.reg0 = ((dev->mem_start>>13) & 0x3f) | WD_MEMENB;
  ei_status.reg5 = ((dev->mem_start>>19) & 0x1f) | NIC16;

  अगर (ei_status.word16)
	  outb(ei_status.reg5, ioaddr+WD_CMDREG5);
  outb(ei_status.reg0, ioaddr); /* WD_CMDREG */

  वापस ei_खोलो(dev);
पूर्ण

अटल व्योम
wd_reset_8390(काष्ठा net_device *dev)
अणु
	पूर्णांक wd_cmd_port = dev->base_addr - WD_NIC_OFFSET; /* WD_CMDREG */
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	outb(WD_RESET, wd_cmd_port);
	netअगर_dbg(ei_local, hw, dev, "resetting the WD80x3 t=%lu...\n",
		  jअगरfies);
	ei_status.txing = 0;

	/* Set up the ASIC रेजिस्टरs, just in हाल something changed them. */
	outb((((dev->mem_start>>13) & 0x3f)|WD_MEMENB), wd_cmd_port);
	अगर (ei_status.word16)
		outb(NIC16 | ((dev->mem_start>>19) & 0x1f), wd_cmd_port+WD_CMDREG5);

	netअगर_dbg(ei_local, hw, dev, "reset done\n");
पूर्ण

/* Grab the 8390 specअगरic header. Similar to the block_input routine, but
   we करोn't need to be concerned with ring wrap as the header will be at
   the start of a page, so we optimize accordingly. */

अटल व्योम
wd_get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु

	पूर्णांक wd_cmdreg = dev->base_addr - WD_NIC_OFFSET; /* WD_CMDREG */
	व्योम __iomem *hdr_start = ei_status.mem + ((ring_page - WD_START_PG)<<8);

	/* We'll always get a 4 byte header पढ़ो followed by a packet पढ़ो, so
	   we enable 16 bit mode beक्रमe the header, and disable after the body. */
	अगर (ei_status.word16)
		outb(ISA16 | ei_status.reg5, wd_cmdreg+WD_CMDREG5);

#अगर_घोषित __BIG_ENDIAN
	/* Officially this is what we are करोing, but the पढ़ोl() is faster */
	/* unक्रमtunately it isn't endian aware of the काष्ठा               */
	स_नकल_fromio(hdr, hdr_start, माप(काष्ठा e8390_pkt_hdr));
	hdr->count = le16_to_cpu(hdr->count);
#अन्यथा
	((अचिन्हित पूर्णांक*)hdr)[0] = पढ़ोl(hdr_start);
#पूर्ण_अगर
पूर्ण

/* Block input and output are easy on shared memory ethercards, and trivial
   on the Western digital card where there is no choice of how to करो it.
   The only complications are that the ring buffer wraps, and need to map
   चयन between 8- and 16-bit modes. */

अटल व्योम
wd_block_input(काष्ठा net_device *dev, पूर्णांक count, काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	पूर्णांक wd_cmdreg = dev->base_addr - WD_NIC_OFFSET; /* WD_CMDREG */
	अचिन्हित दीर्घ offset = ring_offset - (WD_START_PG<<8);
	व्योम __iomem *xfer_start = ei_status.mem + offset;

	अगर (offset + count > ei_status.priv) अणु
		/* We must wrap the input move. */
		पूर्णांक semi_count = ei_status.priv - offset;
		स_नकल_fromio(skb->data, xfer_start, semi_count);
		count -= semi_count;
		स_नकल_fromio(skb->data + semi_count, ei_status.mem + TX_PAGES * 256, count);
	पूर्ण अन्यथा अणु
		/* Packet is in one chunk -- we can copy + cksum. */
		स_नकल_fromio(skb->data, xfer_start, count);
	पूर्ण

	/* Turn off 16 bit access so that reboot works.	 ISA brain-damage */
	अगर (ei_status.word16)
		outb(ei_status.reg5, wd_cmdreg+WD_CMDREG5);
पूर्ण

अटल व्योम
wd_block_output(काष्ठा net_device *dev, पूर्णांक count, स्थिर अचिन्हित अक्षर *buf,
				पूर्णांक start_page)
अणु
	पूर्णांक wd_cmdreg = dev->base_addr - WD_NIC_OFFSET; /* WD_CMDREG */
	व्योम __iomem *shmem = ei_status.mem + ((start_page - WD_START_PG)<<8);


	अगर (ei_status.word16) अणु
		/* Turn on and off 16 bit access so that reboot works. */
		outb(ISA16 | ei_status.reg5, wd_cmdreg+WD_CMDREG5);
		स_नकल_toio(shmem, buf, count);
		outb(ei_status.reg5, wd_cmdreg+WD_CMDREG5);
	पूर्ण अन्यथा
		स_नकल_toio(shmem, buf, count);
पूर्ण


अटल पूर्णांक
wd_बंद(काष्ठा net_device *dev)
अणु
	पूर्णांक wd_cmdreg = dev->base_addr - WD_NIC_OFFSET; /* WD_CMDREG */
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	netअगर_dbg(ei_local, अगरकरोwn, dev, "Shutting down ethercard.\n");
	ei_बंद(dev);

	/* Change from 16-bit to 8-bit shared memory so reboot works. */
	अगर (ei_status.word16)
		outb(ei_status.reg5, wd_cmdreg + WD_CMDREG5 );

	/* And disable the shared memory. */
	outb(ei_status.reg0 & ~WD_MEMENB, wd_cmdreg);

	वापस 0;
पूर्ण


#अगर_घोषित MODULE
#घोषणा MAX_WD_CARDS	4	/* Max number of wd cards per module */
अटल काष्ठा net_device *dev_wd[MAX_WD_CARDS];
अटल पूर्णांक io[MAX_WD_CARDS];
अटल पूर्णांक irq[MAX_WD_CARDS];
अटल पूर्णांक mem[MAX_WD_CARDS];
अटल पूर्णांक mem_end[MAX_WD_CARDS];	/* क्रम non std. mem size */

module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
module_param_hw_array(mem, पूर्णांक, iomem, शून्य, 0);
module_param_hw_array(mem_end, पूर्णांक, iomem, शून्य, 0);
module_param_named(msg_enable, wd_msg_enable, uपूर्णांक, 0444);
MODULE_PARM_DESC(io, "I/O base address(es)");
MODULE_PARM_DESC(irq, "IRQ number(s) (ignored for PureData boards)");
MODULE_PARM_DESC(mem, "memory base address(es)(ignored for PureData boards)");
MODULE_PARM_DESC(mem_end, "memory end address(es)");
MODULE_PARM_DESC(msg_enable, "Debug message level (see linux/netdevice.h for bitmap)");
MODULE_DESCRIPTION("ISA Western Digital wd8003/wd8013 ; SMC Elite, Elite16 ethernet driver");
MODULE_LICENSE("GPL");

/* This is set up so that only a single स्वतःprobe takes place per call.
ISA device स्वतःprobes on a running machine are not recommended. */

पूर्णांक __init init_module(व्योम)
अणु
	काष्ठा net_device *dev;
	पूर्णांक this_dev, found = 0;

	क्रम (this_dev = 0; this_dev < MAX_WD_CARDS; this_dev++) अणु
		अगर (io[this_dev] == 0)  अणु
			अगर (this_dev != 0) अवरोध; /* only स्वतःprobe 1st one */
			prपूर्णांकk(KERN_NOTICE "wd.c: Presently autoprobing (not recommended) for a single card.\n");
		पूर्ण
		dev = alloc_ei_netdev();
		अगर (!dev)
			अवरोध;
		dev->irq = irq[this_dev];
		dev->base_addr = io[this_dev];
		dev->mem_start = mem[this_dev];
		dev->mem_end = mem_end[this_dev];
		अगर (करो_wd_probe(dev) == 0) अणु
			dev_wd[found++] = dev;
			जारी;
		पूर्ण
		मुक्त_netdev(dev);
		prपूर्णांकk(KERN_WARNING "wd.c: No wd80x3 card found (i/o = 0x%x).\n", io[this_dev]);
		अवरोध;
	पूर्ण
	अगर (found)
		वापस 0;
	वापस -ENXIO;
पूर्ण

अटल व्योम cleanup_card(काष्ठा net_device *dev)
अणु
	मुक्त_irq(dev->irq, dev);
	release_region(dev->base_addr - WD_NIC_OFFSET, WD_IO_EXTENT);
	iounmap(ei_status.mem);
पूर्ण

व्योम __निकास
cleanup_module(व्योम)
अणु
	पूर्णांक this_dev;

	क्रम (this_dev = 0; this_dev < MAX_WD_CARDS; this_dev++) अणु
		काष्ठा net_device *dev = dev_wd[this_dev];
		अगर (dev) अणु
			unरेजिस्टर_netdev(dev);
			cleanup_card(dev);
			मुक्त_netdev(dev);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* MODULE */
