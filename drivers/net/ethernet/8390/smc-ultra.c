<शैली गुरु>
/* smc-ultra.c: A SMC Ultra ethernet driver क्रम linux. */
/*
	This is a driver क्रम the SMC Ultra and SMC EtherEZ ISA ethercards.

	Written 1993-1998 by Donald Becker.

	Copyright 1993 United States Government as represented by the
	Director, National Security Agency.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	This driver uses the cards in the 8390-compatible mode.
	Most of the run-समय complनिकासy is handled by the generic code in
	8390.c.  The code in this file is responsible क्रम

		ultra_probe()	 	Detecting and initializing the card.
		ultra_probe1()
		ultra_probe_isapnp()

		ultra_खोलो()		The card-specअगरic details of starting, stopping
		ultra_reset_8390()	and resetting the 8390 NIC core.
		ultra_बंद()

		ultra_block_input()		Routines क्रम पढ़ोing and writing blocks of
		ultra_block_output()	packet buffer memory.
		ultra_pio_input()
		ultra_pio_output()

	This driver enables the shared memory only when करोing the actual data
	transfers to aव्योम a bug in early version of the card that corrupted
	data transferred by a AHA1542.

	This driver now supports the programmed-I/O (PIO) data transfer mode of
	the EtherEZ. It करोes not use the non-8390-compatible "Altego" mode.
	That support (अगर available) is in smc-ez.c.

	Changelog:

	Paul Gorपंचांगaker	: multiple card support क्रम module users.
	Donald Becker	: 4/17/96 PIO support, minor potential problems aव्योमed.
	Donald Becker	: 6/6/96 correctly set स्वतः-wrap bit.
	Alexander Sotirov : 1/20/01 Added support क्रम ISAPnP cards

	Note about the ISA PnP support:

	This driver can not स्वतःprobe क्रम more than one SMC EtherEZ PnP card.
	You have to configure the second card manually through the /proc/isapnp
	पूर्णांकerface and then load the module with an explicit io=0x___ option.
*/

अटल स्थिर अक्षर version[] =
	"smc-ultra.c:v2.02 2/3/98 Donald Becker (becker@cesdis.gsfc.nasa.gov)\n";

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#समावेश "8390.h"

#घोषणा DRV_NAME "smc-ultra"

/* A zero-terminated list of I/O addresses to be probed. */
अटल अचिन्हित पूर्णांक ultra_portlist[] __initdata =
अणु0x200, 0x220, 0x240, 0x280, 0x300, 0x340, 0x380, 0पूर्ण;

अटल पूर्णांक ultra_probe1(काष्ठा net_device *dev, पूर्णांक ioaddr);

#अगर_घोषित __ISAPNP__
अटल पूर्णांक ultra_probe_isapnp(काष्ठा net_device *dev);
#पूर्ण_अगर

अटल पूर्णांक ultra_खोलो(काष्ठा net_device *dev);
अटल व्योम ultra_reset_8390(काष्ठा net_device *dev);
अटल व्योम ultra_get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr,
						पूर्णांक ring_page);
अटल व्योम ultra_block_input(काष्ठा net_device *dev, पूर्णांक count,
						  काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम ultra_block_output(काष्ठा net_device *dev, पूर्णांक count,
							स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page);
अटल व्योम ultra_pio_get_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr,
						पूर्णांक ring_page);
अटल व्योम ultra_pio_input(काष्ठा net_device *dev, पूर्णांक count,
						  काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम ultra_pio_output(काष्ठा net_device *dev, पूर्णांक count,
							 स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page);
अटल पूर्णांक ultra_बंद_card(काष्ठा net_device *dev);

#अगर_घोषित __ISAPNP__
अटल काष्ठा isapnp_device_id ultra_device_ids[] __initdata = अणु
        अणु       ISAPNP_VENDOR('S','M','C'), ISAPNP_FUNCTION(0x8416),
                ISAPNP_VENDOR('S','M','C'), ISAPNP_FUNCTION(0x8416),
                (दीर्घ) "SMC EtherEZ (8416)" पूर्ण,
        अणु पूर्ण	/* terminate list */
पूर्ण;

MODULE_DEVICE_TABLE(isapnp, ultra_device_ids);
#पूर्ण_अगर

अटल u32 ultra_msg_enable;

#घोषणा START_PG		0x00	/* First page of TX buffer */

#घोषणा ULTRA_CMDREG	0		/* Offset to ASIC command रेजिस्टर. */
#घोषणा	 ULTRA_RESET	0x80	/* Board reset, in ULTRA_CMDREG. */
#घोषणा	 ULTRA_MEMENB	0x40	/* Enable the shared memory. */
#घोषणा IOPD	0x02			/* I/O Pipe Data (16 bits), PIO operation. */
#घोषणा IOPA	0x07			/* I/O Pipe Address क्रम PIO operation. */
#घोषणा ULTRA_NIC_OFFSET  16	/* NIC रेजिस्टर offset from the base_addr. */
#घोषणा ULTRA_IO_EXTENT 32
#घोषणा EN0_ERWCNT		0x08	/* Early receive warning count. */

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम ultra_poll(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	ei_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर
/*	Probe क्रम the Ultra.  This looks like a 8013 with the station
	address PROM at I/O ports <base>+8 to <base>+13, with a checksum
	following.
*/

अटल पूर्णांक __init करो_ultra_probe(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	पूर्णांक base_addr = dev->base_addr;
	पूर्णांक irq = dev->irq;

	अगर (base_addr > 0x1ff)		/* Check a single specअगरied location. */
		वापस ultra_probe1(dev, base_addr);
	अन्यथा अगर (base_addr != 0)	/* Don't probe at all. */
		वापस -ENXIO;

#अगर_घोषित __ISAPNP__
	/* Look क्रम any installed ISAPnP cards */
	अगर (isapnp_present() && (ultra_probe_isapnp(dev) == 0))
		वापस 0;
#पूर्ण_अगर

	क्रम (i = 0; ultra_portlist[i]; i++) अणु
		dev->irq = irq;
		अगर (ultra_probe1(dev, ultra_portlist[i]) == 0)
			वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

#अगर_अघोषित MODULE
काष्ठा net_device * __init ultra_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev = alloc_ei_netdev();
	पूर्णांक err;

	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	प्र_लिखो(dev->name, "eth%d", unit);
	netdev_boot_setup_check(dev);

	err = करो_ultra_probe(dev);
	अगर (err)
		जाओ out;
	वापस dev;
out:
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops ultra_netdev_ops = अणु
	.nकरो_खोलो		= ultra_खोलो,
	.nकरो_stop		= ultra_बंद_card,

	.nकरो_start_xmit		= ei_start_xmit,
	.nकरो_tx_समयout		= ei_tx_समयout,
	.nकरो_get_stats		= ei_get_stats,
	.nकरो_set_rx_mode	= ei_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller 	= ultra_poll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init ultra_probe1(काष्ठा net_device *dev, पूर्णांक ioaddr)
अणु
	पूर्णांक i, retval;
	पूर्णांक checksum = 0;
	स्थिर अक्षर *model_name;
	अचिन्हित अक्षर eeprom_irq = 0;
	अटल अचिन्हित version_prपूर्णांकed;
	/* Values from various config regs. */
	अचिन्हित अक्षर num_pages, irqreg, addr, piomode;
	अचिन्हित अक्षर idreg = inb(ioaddr + 7);
	अचिन्हित अक्षर reg4 = inb(ioaddr + 4) & 0x7f;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	अगर (!request_region(ioaddr, ULTRA_IO_EXTENT, DRV_NAME))
		वापस -EBUSY;

	/* Check the ID nibble. */
	अगर ((idreg & 0xF0) != 0x20 			/* SMC Ultra */
		&& (idreg & 0xF0) != 0x40) अणु		/* SMC EtherEZ */
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	/* Select the station address रेजिस्टर set. */
	outb(reg4, ioaddr + 4);

	क्रम (i = 0; i < 8; i++)
		checksum += inb(ioaddr + 8 + i);
	अगर ((checksum & 0xff) != 0xFF) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	अगर ((ultra_msg_enable & NETIF_MSG_DRV) && (version_prपूर्णांकed++ == 0))
		netdev_info(dev, version);

	model_name = (idreg & 0xF0) == 0x20 ? "SMC Ultra" : "SMC EtherEZ";

	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = inb(ioaddr + 8 + i);

	netdev_info(dev, "%s at %#3x, %pM", model_name,
		    ioaddr, dev->dev_addr);

	/* Switch from the station address to the alternate रेजिस्टर set and
	   पढ़ो the useful रेजिस्टरs there. */
	outb(0x80 | reg4, ioaddr + 4);

	/* Enabled FINE16 mode to aव्योम BIOS ROM width mismatches @ reboot. */
	outb(0x80 | inb(ioaddr + 0x0c), ioaddr + 0x0c);
	piomode = inb(ioaddr + 0x8);
	addr = inb(ioaddr + 0xb);
	irqreg = inb(ioaddr + 0xd);

	/* Switch back to the station address रेजिस्टर set so that the MS-DOS driver
	   can find the card after a warm boot. */
	outb(reg4, ioaddr + 4);

	अगर (dev->irq < 2) अणु
		अचिन्हित अक्षर irqmap[] = अणु0, 9, 3, 5, 7, 10, 11, 15पूर्ण;
		पूर्णांक irq;

		/* The IRQ bits are split. */
		irq = irqmap[((irqreg & 0x40) >> 4) + ((irqreg & 0x0c) >> 2)];

		अगर (irq == 0) अणु
			pr_cont(", failed to detect IRQ line.\n");
			retval =  -EAGAIN;
			जाओ out;
		पूर्ण
		dev->irq = irq;
		eeprom_irq = 1;
	पूर्ण

	/* The 8390 isn't at the base address, so fake the offset */
	dev->base_addr = ioaddr+ULTRA_NIC_OFFSET;

	अणु
		अटल स्थिर पूर्णांक addr_tbl[4] = अणु
			0x0C0000, 0x0E0000, 0xFC0000, 0xFE0000
		पूर्ण;
		अटल स्थिर लघु num_pages_tbl[4] = अणु
			0x20, 0x40, 0x80, 0xff
		पूर्ण;

		dev->mem_start = ((addr & 0x0f) << 13) + addr_tbl[(addr >> 6) & 3] ;
		num_pages = num_pages_tbl[(addr >> 4) & 3];
	पूर्ण

	ei_status.name = model_name;
	ei_status.word16 = 1;
	ei_status.tx_start_page = START_PG;
	ei_status.rx_start_page = START_PG + TX_PAGES;
	ei_status.stop_page = num_pages;

	ei_status.mem = ioremap(dev->mem_start, (ei_status.stop_page - START_PG)*256);
	अगर (!ei_status.mem) अणु
		pr_cont(", failed to ioremap.\n");
		retval =  -ENOMEM;
		जाओ out;
	पूर्ण

	dev->mem_end = dev->mem_start + (ei_status.stop_page - START_PG)*256;

	अगर (piomode) अणु
		pr_cont(", %s IRQ %d programmed-I/O mode.\n",
			eeprom_irq ? "EEPROM" : "assigned ", dev->irq);
		ei_status.block_input = &ultra_pio_input;
		ei_status.block_output = &ultra_pio_output;
		ei_status.get_8390_hdr = &ultra_pio_get_hdr;
	पूर्ण अन्यथा अणु
		pr_cont(", %s IRQ %d memory %#lx-%#lx.\n",
			eeprom_irq ? "" : "assigned ", dev->irq, dev->mem_start,
			dev->mem_end-1);
		ei_status.block_input = &ultra_block_input;
		ei_status.block_output = &ultra_block_output;
		ei_status.get_8390_hdr = &ultra_get_8390_hdr;
	पूर्ण
	ei_status.reset_8390 = &ultra_reset_8390;

	dev->netdev_ops = &ultra_netdev_ops;
	NS8390_init(dev, 0);
	ei_local->msg_enable = ultra_msg_enable;

	retval = रेजिस्टर_netdev(dev);
	अगर (retval)
		जाओ out;
	वापस 0;
out:
	release_region(ioaddr, ULTRA_IO_EXTENT);
	वापस retval;
पूर्ण

#अगर_घोषित __ISAPNP__
अटल पूर्णांक __init ultra_probe_isapnp(काष्ठा net_device *dev)
अणु
        पूर्णांक i;

        क्रम (i = 0; ultra_device_ids[i].venकरोr != 0; i++) अणु
		काष्ठा pnp_dev *idev = शून्य;

                जबतक ((idev = pnp_find_dev(शून्य,
                                            ultra_device_ids[i].venकरोr,
                                            ultra_device_ids[i].function,
                                            idev))) अणु
                        /* Aव्योम alपढ़ोy found cards from previous calls */
                        अगर (pnp_device_attach(idev) < 0)
                        	जारी;
                        अगर (pnp_activate_dev(idev) < 0) अणु
                              __again:
                        	pnp_device_detach(idev);
                        	जारी;
                        पूर्ण
			/* अगर no io and irq, search क्रम next */
			अगर (!pnp_port_valid(idev, 0) || !pnp_irq_valid(idev, 0))
				जाओ __again;
                        /* found it */
			dev->base_addr = pnp_port_start(idev, 0);
			dev->irq = pnp_irq(idev, 0);
			netdev_info(dev,
				    "smc-ultra.c: ISAPnP reports %s at i/o %#lx, irq %d.\n",
				    (अक्षर *) ultra_device_ids[i].driver_data,
				    dev->base_addr, dev->irq);
                        अगर (ultra_probe1(dev, dev->base_addr) != 0) अणु      /* Shouldn't happen. */
				netdev_err(dev,
					   "smc-ultra.c: Probe of ISAPnP card at %#lx failed.\n",
					   dev->base_addr);
				pnp_device_detach(idev);
				वापस -ENXIO;
                        पूर्ण
                        ei_status.priv = (अचिन्हित दीर्घ)idev;
                        अवरोध;
                पूर्ण
                अगर (!idev)
                        जारी;
                वापस 0;
        पूर्ण

        वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
ultra_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक retval;
	पूर्णांक ioaddr = dev->base_addr - ULTRA_NIC_OFFSET; /* ASIC addr */
	अचिन्हित अक्षर irq2reg[] = अणु0, 0, 0x04, 0x08, 0, 0x0C, 0, 0x40,
				   0, 0x04, 0x44, 0x48, 0, 0, 0, 0x4C, पूर्ण;

	retval = request_irq(dev->irq, ei_पूर्णांकerrupt, 0, dev->name, dev);
	अगर (retval)
		वापस retval;

	outb(0x00, ioaddr);	/* Disable shared memory क्रम safety. */
	outb(0x80, ioaddr + 5);
	/* Set the IRQ line. */
	outb(inb(ioaddr + 4) | 0x80, ioaddr + 4);
	outb((inb(ioaddr + 13) & ~0x4C) | irq2reg[dev->irq], ioaddr + 13);
	outb(inb(ioaddr + 4) & 0x7f, ioaddr + 4);

	अगर (ei_status.block_input == &ultra_pio_input) अणु
		outb(0x11, ioaddr + 6);		/* Enable पूर्णांकerrupts and PIO. */
		outb(0x01, ioaddr + 0x19);  	/* Enable ring पढ़ो स्वतः-wrap. */
	पूर्ण अन्यथा
		outb(0x01, ioaddr + 6);		/* Enable पूर्णांकerrupts and memory. */
	/* Set the early receive warning level in winकरोw 0 high enough not
	   to receive ERW पूर्णांकerrupts. */
	outb_p(E8390_NODMA+E8390_PAGE0, dev->base_addr);
	outb(0xff, dev->base_addr + EN0_ERWCNT);
	ei_खोलो(dev);
	वापस 0;
पूर्ण

अटल व्योम
ultra_reset_8390(काष्ठा net_device *dev)
अणु
	पूर्णांक cmd_port = dev->base_addr - ULTRA_NIC_OFFSET; /* ASIC base addr */
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	outb(ULTRA_RESET, cmd_port);
	netअगर_dbg(ei_local, hw, dev, "resetting Ultra, t=%ld...\n", jअगरfies);
	ei_status.txing = 0;

	outb(0x00, cmd_port);	/* Disable shared memory क्रम safety. */
	outb(0x80, cmd_port + 5);
	अगर (ei_status.block_input == &ultra_pio_input)
		outb(0x11, cmd_port + 6);		/* Enable पूर्णांकerrupts and PIO. */
	अन्यथा
		outb(0x01, cmd_port + 6);		/* Enable पूर्णांकerrupts and memory. */

	netअगर_dbg(ei_local, hw, dev, "reset done\n");
पूर्ण

/* Grab the 8390 specअगरic header. Similar to the block_input routine, but
   we करोn't need to be concerned with ring wrap as the header will be at
   the start of a page, so we optimize accordingly. */

अटल व्योम
ultra_get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु
	व्योम __iomem *hdr_start = ei_status.mem + ((ring_page - START_PG)<<8);

	outb(ULTRA_MEMENB, dev->base_addr - ULTRA_NIC_OFFSET);	/* shmem on */
#अगर_घोषित __BIG_ENDIAN
	/* Officially this is what we are करोing, but the पढ़ोl() is faster */
	/* unक्रमtunately it isn't endian aware of the काष्ठा               */
	स_नकल_fromio(hdr, hdr_start, माप(काष्ठा e8390_pkt_hdr));
	hdr->count = le16_to_cpu(hdr->count);
#अन्यथा
	((अचिन्हित पूर्णांक*)hdr)[0] = पढ़ोl(hdr_start);
#पूर्ण_अगर
	outb(0x00, dev->base_addr - ULTRA_NIC_OFFSET); /* shmem off */
पूर्ण

/* Block input and output are easy on shared memory ethercards, the only
   complication is when the ring buffer wraps. */

अटल व्योम
ultra_block_input(काष्ठा net_device *dev, पूर्णांक count, काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	व्योम __iomem *xfer_start = ei_status.mem + ring_offset - (START_PG<<8);

	/* Enable shared memory. */
	outb(ULTRA_MEMENB, dev->base_addr - ULTRA_NIC_OFFSET);

	अगर (ring_offset + count > ei_status.stop_page*256) अणु
		/* We must wrap the input move. */
		पूर्णांक semi_count = ei_status.stop_page*256 - ring_offset;
		स_नकल_fromio(skb->data, xfer_start, semi_count);
		count -= semi_count;
		स_नकल_fromio(skb->data + semi_count, ei_status.mem + TX_PAGES * 256, count);
	पूर्ण अन्यथा अणु
		स_नकल_fromio(skb->data, xfer_start, count);
	पूर्ण

	outb(0x00, dev->base_addr - ULTRA_NIC_OFFSET);	/* Disable memory. */
पूर्ण

अटल व्योम
ultra_block_output(काष्ठा net_device *dev, पूर्णांक count, स्थिर अचिन्हित अक्षर *buf,
				पूर्णांक start_page)
अणु
	व्योम __iomem *shmem = ei_status.mem + ((start_page - START_PG)<<8);

	/* Enable shared memory. */
	outb(ULTRA_MEMENB, dev->base_addr - ULTRA_NIC_OFFSET);

	स_नकल_toio(shmem, buf, count);

	outb(0x00, dev->base_addr - ULTRA_NIC_OFFSET); /* Disable memory. */
पूर्ण

/* The identical operations क्रम programmed I/O cards.
   The PIO model is trivial to use: the 16 bit start address is written
   byte-sequentially to IOPA, with no पूर्णांकervening I/O operations, and the
   data is पढ़ो or written to the IOPD data port.
   The only potential complication is that the address रेजिस्टर is shared
   and must be always be rewritten between each पढ़ो/ग_लिखो direction change.
   This is no problem क्रम us, as the 8390 code ensures that we are single
   thपढ़ोed. */
अटल व्योम ultra_pio_get_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr,
						पूर्णांक ring_page)
अणु
	पूर्णांक ioaddr = dev->base_addr - ULTRA_NIC_OFFSET; /* ASIC addr */
	outb(0x00, ioaddr + IOPA);	/* Set the address, LSB first. */
	outb(ring_page, ioaddr + IOPA);
	insw(ioaddr + IOPD, hdr, माप(काष्ठा e8390_pkt_hdr)>>1);
पूर्ण

अटल व्योम ultra_pio_input(काष्ठा net_device *dev, पूर्णांक count,
						  काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	पूर्णांक ioaddr = dev->base_addr - ULTRA_NIC_OFFSET; /* ASIC addr */
    अक्षर *buf = skb->data;

	/* For now set the address again, although it should alपढ़ोy be correct. */
	outb(ring_offset, ioaddr + IOPA);	/* Set the address, LSB first. */
	outb(ring_offset >> 8, ioaddr + IOPA);
	/* We know skbuffs are padded to at least word alignment. */
	insw(ioaddr + IOPD, buf, (count+1)>>1);
पूर्ण

अटल व्योम ultra_pio_output(काष्ठा net_device *dev, पूर्णांक count,
							स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page)
अणु
	पूर्णांक ioaddr = dev->base_addr - ULTRA_NIC_OFFSET; /* ASIC addr */
	outb(0x00, ioaddr + IOPA);	/* Set the address, LSB first. */
	outb(start_page, ioaddr + IOPA);
	/* An extra odd byte is OK here as well. */
	outsw(ioaddr + IOPD, buf, (count+1)>>1);
पूर्ण

अटल पूर्णांक
ultra_बंद_card(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr - ULTRA_NIC_OFFSET; /* CMDREG */
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	netअगर_stop_queue(dev);

	netअगर_dbg(ei_local, अगरकरोwn, dev, "Shutting down ethercard.\n");

	outb(0x00, ioaddr + 6);		/* Disable पूर्णांकerrupts. */
	मुक्त_irq(dev->irq, dev);

	NS8390_init(dev, 0);

	/* We should someday disable shared memory and change to 8-bit mode
	   "just in case"... */

	वापस 0;
पूर्ण


#अगर_घोषित MODULE
#घोषणा MAX_ULTRA_CARDS	4	/* Max number of Ultra cards per module */
अटल काष्ठा net_device *dev_ultra[MAX_ULTRA_CARDS];
अटल पूर्णांक io[MAX_ULTRA_CARDS];
अटल पूर्णांक irq[MAX_ULTRA_CARDS];

module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
module_param_named(msg_enable, ultra_msg_enable, uपूर्णांक, 0444);
MODULE_PARM_DESC(io, "I/O base address(es)");
MODULE_PARM_DESC(irq, "IRQ number(s) (assigned)");
MODULE_PARM_DESC(msg_enable, "Debug message level (see linux/netdevice.h for bitmap)");
MODULE_DESCRIPTION("SMC Ultra/EtherEZ ISA/PnP Ethernet driver");
MODULE_LICENSE("GPL");

/* This is set up so that only a single स्वतःprobe takes place per call.
ISA device स्वतःprobes on a running machine are not recommended. */
पूर्णांक __init
init_module(व्योम)
अणु
	काष्ठा net_device *dev;
	पूर्णांक this_dev, found = 0;

	क्रम (this_dev = 0; this_dev < MAX_ULTRA_CARDS; this_dev++) अणु
		अगर (io[this_dev] == 0)  अणु
			अगर (this_dev != 0) अवरोध; /* only स्वतःprobe 1st one */
			prपूर्णांकk(KERN_NOTICE "smc-ultra.c: Presently autoprobing (not recommended) for a single card.\n");
		पूर्ण
		dev = alloc_ei_netdev();
		अगर (!dev)
			अवरोध;
		dev->irq = irq[this_dev];
		dev->base_addr = io[this_dev];
		अगर (करो_ultra_probe(dev) == 0) अणु
			dev_ultra[found++] = dev;
			जारी;
		पूर्ण
		मुक्त_netdev(dev);
		prपूर्णांकk(KERN_WARNING "smc-ultra.c: No SMC Ultra card found (i/o = 0x%x).\n", io[this_dev]);
		अवरोध;
	पूर्ण
	अगर (found)
		वापस 0;
	वापस -ENXIO;
पूर्ण

अटल व्योम cleanup_card(काष्ठा net_device *dev)
अणु
	/* NB: ultra_बंद_card() करोes मुक्त_irq */
#अगर_घोषित __ISAPNP__
	काष्ठा pnp_dev *idev = (काष्ठा pnp_dev *)ei_status.priv;
	अगर (idev)
		pnp_device_detach(idev);
#पूर्ण_अगर
	release_region(dev->base_addr - ULTRA_NIC_OFFSET, ULTRA_IO_EXTENT);
	iounmap(ei_status.mem);
पूर्ण

व्योम __निकास
cleanup_module(व्योम)
अणु
	पूर्णांक this_dev;

	क्रम (this_dev = 0; this_dev < MAX_ULTRA_CARDS; this_dev++) अणु
		काष्ठा net_device *dev = dev_ultra[this_dev];
		अगर (dev) अणु
			unरेजिस्टर_netdev(dev);
			cleanup_card(dev);
			मुक्त_netdev(dev);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* MODULE */
