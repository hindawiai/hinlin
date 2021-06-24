<शैली गुरु>
/* 3c509.c: A 3c509 EtherLink3 ethernet driver क्रम linux. */
/*
	Written 1993-2000 by Donald Becker.

	Copyright 1994-2000 by Donald Becker.
	Copyright 1993 United States Government as represented by the
	Director, National Security Agency.	 This software may be used and
	distributed according to the terms of the GNU General Public License,
	incorporated herein by reference.

	This driver is क्रम the 3Com EtherLinkIII series.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	Known limitations:
	Because of the way 3c509 ISA detection works it's dअगरficult to predict
	a priori which of several ISA-mode cards will be detected first.

	This driver करोes not use predictive पूर्णांकerrupt mode, resulting in higher
	packet latency but lower overhead.  If पूर्णांकerrupts are disabled क्रम an
	unusually दीर्घ समय it could also result in missed packets, but in
	practice this rarely happens.


	FIXES:
		Alan Cox:       Removed the 'Unexpected interrupt' bug.
		Michael Meskes:	Upgraded to Donald Becker's version 1.07.
		Alan Cox:	Increased the eeprom delay. Regardless of
				what the करोcs say some people definitely
				get problems with lower (but in card spec)
				delays
		v1.10 4/21/97 Fixed module code so that multiple cards may be detected,
				other cleanups.  -djb
		Andrea Arcangeli:	Upgraded to Donald Becker's version 1.12.
		Rick Payne:	Fixed SMP race condition
		v1.13 9/8/97 Made 'max_interrupt_work' an insmod-settable variable -djb
		v1.14 10/15/97 Aव्योमed रुकोing..discard message क्रम fast machines -djb
		v1.15 1/31/98 Faster recovery क्रम Tx errors. -djb
		v1.16 2/3/98 Dअगरferent ID port handling to aव्योम sound cards. -djb
		v1.18 12Mar2001 Andrew Morton
			- Aव्योम bogus detect of 3c590's (Andrzej Krzysztofowicz)
			- Reviewed against 1.18 from scyld.com
		v1.18a 17Nov2001 Jeff Garzik <jgarzik@pobox.com>
			- ethtool support
		v1.18b 1Mar2002 Zwane Mwaikambo <zwane@commfireservices.com>
			- Power Management support
		v1.18c 1Mar2002 David Ruggiero <jdr@farfalle.com>
			- Full duplex support
		v1.19  16Oct2002 Zwane Mwaikambo <zwane@linuxघातer.ca>
			- Additional ethtool features
		v1.19a 28Oct2002 Davud Ruggiero <jdr@farfalle.com>
			- Increase *पढ़ो_eeprom udelay to workaround oops with 2 cards.
		v1.19b 08Nov2002 Marc Zyngier <maz@wild-wind.fr.eu.org>
			- Introduce driver model क्रम EISA cards.
		v1.20  04Feb2008 Ondrej Zary <linux@rainbow-software.org>
			- convert to isa_driver and pnp_driver and some cleanups
*/

#घोषणा DRV_NAME	"3c509"

/* A few values that may be tweaked. */

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (400*HZ/1000)

#समावेश <linux/module.h>
#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pm.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>	/* क्रम udelay() */
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/device.h>
#समावेश <linux/eisa.h>
#समावेश <linux/bitops.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#अगर_घोषित EL3_DEBUG
अटल पूर्णांक el3_debug = EL3_DEBUG;
#अन्यथा
अटल पूर्णांक el3_debug = 2;
#पूर्ण_अगर

/* Used to करो a global count of all the cards in the प्रणाली.  Must be
 * a global variable so that the eisa probe routines can increment
 * it */
अटल पूर्णांक el3_cards = 0;
#घोषणा EL3_MAX_CARDS 8

/* To minimize the size of the driver source I only define operating
   स्थिरants अगर they are used several बार.  You'll need the manual
   anyway अगर you want to understand driver details. */
/* Offsets from base I/O address. */
#घोषणा EL3_DATA 0x00
#घोषणा EL3_CMD 0x0e
#घोषणा EL3_STATUS 0x0e
#घोषणा	EEPROM_READ 0x80

#घोषणा EL3_IO_EXTENT	16

#घोषणा EL3WINDOW(win_num) outw(SelectWinकरोw + (win_num), ioaddr + EL3_CMD)


/* The top five bits written to EL3_CMD are a command, the lower
   11 bits are the parameter, अगर applicable. */
क्रमागत c509cmd अणु
	TotalReset = 0<<11, SelectWinकरोw = 1<<11, StartCoax = 2<<11,
	RxDisable = 3<<11, RxEnable = 4<<11, RxReset = 5<<11, RxDiscard = 8<<11,
	TxEnable = 9<<11, TxDisable = 10<<11, TxReset = 11<<11,
	FakeIntr = 12<<11, AckIntr = 13<<11, SetIntrEnb = 14<<11,
	SetStatusEnb = 15<<11, SetRxFilter = 16<<11, SetRxThreshold = 17<<11,
	SetTxThreshold = 18<<11, SetTxStart = 19<<11, StatsEnable = 21<<11,
	StatsDisable = 22<<11, StopCoax = 23<<11, PowerUp = 27<<11,
	PowerDown = 28<<11, PowerAuto = 29<<11पूर्ण;

क्रमागत c509status अणु
	IntLatch = 0x0001, AdapterFailure = 0x0002, TxComplete = 0x0004,
	TxAvailable = 0x0008, RxComplete = 0x0010, RxEarly = 0x0020,
	IntReq = 0x0040, StatsFull = 0x0080, CmdBusy = 0x1000, पूर्ण;

/* The SetRxFilter command accepts the following classes: */
क्रमागत RxFilter अणु
	RxStation = 1, RxMulticast = 2, RxBroadcast = 4, RxProm = 8 पूर्ण;

/* Register winकरोw 1 offsets, the winकरोw used in normal operation. */
#घोषणा TX_FIFO		0x00
#घोषणा RX_FIFO		0x00
#घोषणा RX_STATUS 	0x08
#घोषणा TX_STATUS 	0x0B
#घोषणा TX_FREE		0x0C		/* Reमुख्यing मुक्त bytes in Tx buffer. */

#घोषणा WN0_CONF_CTRL	0x04		/* Winकरोw 0: Configuration control रेजिस्टर */
#घोषणा WN0_ADDR_CONF	0x06		/* Winकरोw 0: Address configuration रेजिस्टर */
#घोषणा WN0_IRQ		0x08		/* Winकरोw 0: Set IRQ line in bits 12-15. */
#घोषणा WN4_MEDIA	0x0A		/* Winकरोw 4: Various transcvr/media bits. */
#घोषणा	MEDIA_TP	0x00C0		/* Enable link beat and jabber क्रम 10baseT. */
#घोषणा WN4_NETDIAG	0x06		/* Winकरोw 4: Net diagnostic */
#घोषणा FD_ENABLE	0x8000		/* Enable full-duplex ("external loopback") */

/*
 * Must be a घातer of two (we use a binary and in the
 * circular queue)
 */
#घोषणा SKB_QUEUE_SIZE	64

क्रमागत el3_cardtype अणु EL3_ISA, EL3_PNP, EL3_EISA पूर्ण;

काष्ठा el3_निजी अणु
	spinlock_t lock;
	/* skb send-queue */
	पूर्णांक head, size;
	काष्ठा sk_buff *queue[SKB_QUEUE_SIZE];
	क्रमागत el3_cardtype type;
पूर्ण;
अटल पूर्णांक id_port;
अटल पूर्णांक current_tag;
अटल काष्ठा net_device *el3_devs[EL3_MAX_CARDS];

/* Parameters that may be passed पूर्णांकo the module. */
अटल पूर्णांक debug = -1;
अटल पूर्णांक irq[] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
/* Maximum events (Rx packets, etc.) to handle at each पूर्णांकerrupt. */
अटल पूर्णांक max_पूर्णांकerrupt_work = 10;
#अगर_घोषित CONFIG_PNP
अटल पूर्णांक nopnp;
#पूर्ण_अगर

अटल पूर्णांक el3_common_init(काष्ठा net_device *dev);
अटल व्योम el3_common_हटाओ(काष्ठा net_device *dev);
अटल uलघु id_पढ़ो_eeprom(पूर्णांक index);
अटल uलघु पढ़ो_eeprom(पूर्णांक ioaddr, पूर्णांक index);
अटल पूर्णांक el3_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t el3_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल irqवापस_t el3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल व्योम update_stats(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *el3_get_stats(काष्ठा net_device *dev);
अटल पूर्णांक el3_rx(काष्ठा net_device *dev);
अटल पूर्णांक el3_बंद(काष्ठा net_device *dev);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);
अटल व्योम el3_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम el3_करोwn(काष्ठा net_device *dev);
अटल व्योम el3_up(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops ethtool_ops;
#अगर_घोषित CONFIG_PM
अटल पूर्णांक el3_suspend(काष्ठा device *, pm_message_t);
अटल पूर्णांक el3_resume(काष्ठा device *);
#अन्यथा
#घोषणा el3_suspend शून्य
#घोषणा el3_resume शून्य
#पूर्ण_अगर


/* generic device हटाओ क्रम all device types */
अटल पूर्णांक el3_device_हटाओ (काष्ठा device *device);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम el3_poll_controller(काष्ठा net_device *dev);
#पूर्ण_अगर

/* Return 0 on success, 1 on error, 2 when found alपढ़ोy detected PnP card */
अटल पूर्णांक el3_isa_id_sequence(__be16 *phys_addr)
अणु
	लघु lrs_state = 0xff;
	पूर्णांक i;

	/* ISA boards are detected by sending the ID sequence to the
	   ID_PORT.  We find cards past the first by setting the 'current_tag'
	   on cards as they are found.  Cards with their tag set will not
	   respond to subsequent ID sequences. */

	outb(0x00, id_port);
	outb(0x00, id_port);
	क्रम (i = 0; i < 255; i++) अणु
		outb(lrs_state, id_port);
		lrs_state <<= 1;
		lrs_state = lrs_state & 0x100 ? lrs_state ^ 0xcf : lrs_state;
	पूर्ण
	/* For the first probe, clear all board's tag रेजिस्टरs. */
	अगर (current_tag == 0)
		outb(0xd0, id_port);
	अन्यथा			/* Otherwise समाप्त off alपढ़ोy-found boards. */
		outb(0xd8, id_port);
	अगर (id_पढ़ो_eeprom(7) != 0x6d50)
		वापस 1;
	/* Read in EEPROM data, which करोes contention-select.
	   Only the lowest address board will stay "on-line".
	   3Com got the byte order backwards. */
	क्रम (i = 0; i < 3; i++)
		phys_addr[i] = htons(id_पढ़ो_eeprom(i));
#अगर_घोषित CONFIG_PNP
	अगर (!nopnp) अणु
		/* The ISA PnP 3c509 cards respond to the ID sequence too.
		   This check is needed in order not to रेजिस्टर them twice. */
		क्रम (i = 0; i < el3_cards; i++) अणु
			काष्ठा el3_निजी *lp = netdev_priv(el3_devs[i]);
			अगर (lp->type == EL3_PNP &&
			    ether_addr_equal((u8 *)phys_addr, el3_devs[i]->dev_addr)) अणु
				अगर (el3_debug > 3)
					pr_debug("3c509 with address %02x %02x %02x %02x %02x %02x was found by ISAPnP\n",
						phys_addr[0] & 0xff, phys_addr[0] >> 8,
						phys_addr[1] & 0xff, phys_addr[1] >> 8,
						phys_addr[2] & 0xff, phys_addr[2] >> 8);
				/* Set the adaptor tag so that the next card can be found. */
				outb(0xd0 + ++current_tag, id_port);
				वापस 2;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PNP */
	वापस 0;

पूर्ण

अटल व्योम el3_dev_fill(काष्ठा net_device *dev, __be16 *phys_addr, पूर्णांक ioaddr,
			 पूर्णांक irq, पूर्णांक अगर_port, क्रमागत el3_cardtype type)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);

	स_नकल(dev->dev_addr, phys_addr, ETH_ALEN);
	dev->base_addr = ioaddr;
	dev->irq = irq;
	dev->अगर_port = अगर_port;
	lp->type = type;
पूर्ण

अटल पूर्णांक el3_isa_match(काष्ठा device *pdev, अचिन्हित पूर्णांक ndev)
अणु
	काष्ठा net_device *dev;
	पूर्णांक ioaddr, isa_irq, अगर_port, err;
	अचिन्हित पूर्णांक iobase;
	__be16 phys_addr[3];

	जबतक ((err = el3_isa_id_sequence(phys_addr)) == 2)
		;	/* Skip to next card when PnP card found */
	अगर (err == 1)
		वापस 0;

	iobase = id_पढ़ो_eeprom(8);
	अगर_port = iobase >> 14;
	ioaddr = 0x200 + ((iobase & 0x1f) << 4);
	अगर (irq[el3_cards] > 1 && irq[el3_cards] < 16)
		isa_irq = irq[el3_cards];
	अन्यथा
		isa_irq = id_पढ़ो_eeprom(9) >> 12;

	dev = alloc_etherdev(माप(काष्ठा el3_निजी));
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, pdev);
	netdev_boot_setup_check(dev);

	अगर (!request_region(ioaddr, EL3_IO_EXTENT, "3c509-isa")) अणु
		मुक्त_netdev(dev);
		वापस 0;
	पूर्ण

	/* Set the adaptor tag so that the next card can be found. */
	outb(0xd0 + ++current_tag, id_port);

	/* Activate the adaptor at the EEPROM location. */
	outb((ioaddr >> 4) | 0xe0, id_port);

	EL3WINDOW(0);
	अगर (inw(ioaddr) != 0x6d50) अणु
		मुक्त_netdev(dev);
		वापस 0;
	पूर्ण

	/* Free the पूर्णांकerrupt so that some other card can use it. */
	outw(0x0f00, ioaddr + WN0_IRQ);

	el3_dev_fill(dev, phys_addr, ioaddr, isa_irq, अगर_port, EL3_ISA);
	dev_set_drvdata(pdev, dev);
	अगर (el3_common_init(dev)) अणु
		मुक्त_netdev(dev);
		वापस 0;
	पूर्ण

	el3_devs[el3_cards++] = dev;
	वापस 1;
पूर्ण

अटल व्योम el3_isa_हटाओ(काष्ठा device *pdev,
				    अचिन्हित पूर्णांक ndev)
अणु
	el3_device_हटाओ(pdev);
	dev_set_drvdata(pdev, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक el3_isa_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n,
			   pm_message_t state)
अणु
	current_tag = 0;
	वापस el3_suspend(dev, state);
पूर्ण

अटल पूर्णांक el3_isa_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	पूर्णांक ioaddr = ndev->base_addr, err;
	__be16 phys_addr[3];

	जबतक ((err = el3_isa_id_sequence(phys_addr)) == 2)
		;	/* Skip to next card when PnP card found */
	अगर (err == 1)
		वापस 0;
	/* Set the adaptor tag so that the next card can be found. */
	outb(0xd0 + ++current_tag, id_port);
	/* Enable the card */
	outb((ioaddr >> 4) | 0xe0, id_port);
	EL3WINDOW(0);
	अगर (inw(ioaddr) != 0x6d50)
		वापस 1;
	/* Free the पूर्णांकerrupt so that some other card can use it. */
	outw(0x0f00, ioaddr + WN0_IRQ);
	वापस el3_resume(dev);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा isa_driver el3_isa_driver = अणु
	.match		= el3_isa_match,
	.हटाओ		= el3_isa_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= el3_isa_suspend,
	.resume		= el3_isa_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= "3c509"
	पूर्ण,
पूर्ण;
अटल पूर्णांक isa_रेजिस्टरed;

#अगर_घोषित CONFIG_PNP
अटल स्थिर काष्ठा pnp_device_id el3_pnp_ids[] = अणु
	अणु .id = "TCM5090" पूर्ण, /* 3Com Etherlink III (TP) */
	अणु .id = "TCM5091" पूर्ण, /* 3Com Etherlink III */
	अणु .id = "TCM5094" पूर्ण, /* 3Com Etherlink III (combo) */
	अणु .id = "TCM5095" पूर्ण, /* 3Com Etherlink III (TPO) */
	अणु .id = "TCM5098" पूर्ण, /* 3Com Etherlink III (TPC) */
	अणु .id = "PNP80f7" पूर्ण, /* 3Com Etherlink III compatible */
	अणु .id = "PNP80f8" पूर्ण, /* 3Com Etherlink III compatible */
	अणु .id = "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pnp, el3_pnp_ids);

अटल पूर्णांक el3_pnp_probe(काष्ठा pnp_dev *pdev, स्थिर काष्ठा pnp_device_id *id)
अणु
	लघु i;
	पूर्णांक ioaddr, irq, अगर_port;
	__be16 phys_addr[3];
	काष्ठा net_device *dev = शून्य;
	पूर्णांक err;

	ioaddr = pnp_port_start(pdev, 0);
	अगर (!request_region(ioaddr, EL3_IO_EXTENT, "3c509-pnp"))
		वापस -EBUSY;
	irq = pnp_irq(pdev, 0);
	EL3WINDOW(0);
	क्रम (i = 0; i < 3; i++)
		phys_addr[i] = htons(पढ़ो_eeprom(ioaddr, i));
	अगर_port = पढ़ो_eeprom(ioaddr, 8) >> 14;
	dev = alloc_etherdev(माप(काष्ठा el3_निजी));
	अगर (!dev) अणु
		release_region(ioaddr, EL3_IO_EXTENT);
		वापस -ENOMEM;
	पूर्ण
	SET_NETDEV_DEV(dev, &pdev->dev);
	netdev_boot_setup_check(dev);

	el3_dev_fill(dev, phys_addr, ioaddr, irq, अगर_port, EL3_PNP);
	pnp_set_drvdata(pdev, dev);
	err = el3_common_init(dev);

	अगर (err) अणु
		pnp_set_drvdata(pdev, शून्य);
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण

	el3_devs[el3_cards++] = dev;
	वापस 0;
पूर्ण

अटल व्योम el3_pnp_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	el3_common_हटाओ(pnp_get_drvdata(pdev));
	pnp_set_drvdata(pdev, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक el3_pnp_suspend(काष्ठा pnp_dev *pdev, pm_message_t state)
अणु
	वापस el3_suspend(&pdev->dev, state);
पूर्ण

अटल पूर्णांक el3_pnp_resume(काष्ठा pnp_dev *pdev)
अणु
	वापस el3_resume(&pdev->dev);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_driver el3_pnp_driver = अणु
	.name		= "3c509",
	.id_table	= el3_pnp_ids,
	.probe		= el3_pnp_probe,
	.हटाओ		= el3_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= el3_pnp_suspend,
	.resume		= el3_pnp_resume,
#पूर्ण_अगर
पूर्ण;
अटल पूर्णांक pnp_रेजिस्टरed;
#पूर्ण_अगर /* CONFIG_PNP */

#अगर_घोषित CONFIG_EISA
अटल स्थिर काष्ठा eisa_device_id el3_eisa_ids[] = अणु
		अणु "TCM5090" पूर्ण,
		अणु "TCM5091" पूर्ण,
		अणु "TCM5092" पूर्ण,
		अणु "TCM5093" पूर्ण,
		अणु "TCM5094" पूर्ण,
		अणु "TCM5095" पूर्ण,
		अणु "TCM5098" पूर्ण,
		अणु "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(eisa, el3_eisa_ids);

अटल पूर्णांक el3_eisa_probe (काष्ठा device *device);

अटल काष्ठा eisa_driver el3_eisa_driver = अणु
		.id_table = el3_eisa_ids,
		.driver   = अणु
				.name    = "3c579",
				.probe   = el3_eisa_probe,
				.हटाओ  = el3_device_हटाओ,
				.suspend = el3_suspend,
				.resume  = el3_resume,
		पूर्ण
पूर्ण;
अटल पूर्णांक eisa_रेजिस्टरed;
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो 		= el3_खोलो,
	.nकरो_stop	 	= el3_बंद,
	.nकरो_start_xmit 	= el3_start_xmit,
	.nकरो_get_stats 		= el3_get_stats,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_tx_समयout 	= el3_tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= el3_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक el3_common_init(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	पूर्णांक err;
	स्थिर अक्षर *अगर_names[] = अणु"10baseT", "AUI", "undefined", "BNC"पूर्ण;

	spin_lock_init(&lp->lock);

	अगर (dev->mem_start & 0x05) अणु /* xcvr codes 1/3/4/12 */
		dev->अगर_port = (dev->mem_start & 0x0f);
	पूर्ण अन्यथा अणु /* xcvr codes 0/8 */
		/* use eeprom value, but save user's full-duplex selection */
		dev->अगर_port |= (dev->mem_start & 0x08);
	पूर्ण

	/* The EL3-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	dev->ethtool_ops = &ethtool_ops;

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		pr_err("Failed to register 3c5x9 at %#3.3lx, IRQ %d.\n",
			dev->base_addr, dev->irq);
		release_region(dev->base_addr, EL3_IO_EXTENT);
		वापस err;
	पूर्ण

	pr_info("%s: 3c5x9 found at %#3.3lx, %s port, address %pM, IRQ %d.\n",
	       dev->name, dev->base_addr, अगर_names[(dev->अगर_port & 0x03)],
	       dev->dev_addr, dev->irq);

	वापस 0;

पूर्ण

अटल व्योम el3_common_हटाओ (काष्ठा net_device *dev)
अणु
	unरेजिस्टर_netdev (dev);
	release_region(dev->base_addr, EL3_IO_EXTENT);
	मुक्त_netdev (dev);
पूर्ण

#अगर_घोषित CONFIG_EISA
अटल पूर्णांक el3_eisa_probe(काष्ठा device *device)
अणु
	लघु i;
	पूर्णांक ioaddr, irq, अगर_port;
	__be16 phys_addr[3];
	काष्ठा net_device *dev = शून्य;
	काष्ठा eisa_device *edev;
	पूर्णांक err;

	/* Yeepee, The driver framework is calling us ! */
	edev = to_eisa_device (device);
	ioaddr = edev->base_addr;

	अगर (!request_region(ioaddr, EL3_IO_EXTENT, "3c579-eisa"))
		वापस -EBUSY;

	/* Change the रेजिस्टर set to the configuration winकरोw 0. */
	outw(SelectWinकरोw | 0, ioaddr + 0xC80 + EL3_CMD);

	irq = inw(ioaddr + WN0_IRQ) >> 12;
	अगर_port = inw(ioaddr + 6)>>14;
	क्रम (i = 0; i < 3; i++)
		phys_addr[i] = htons(पढ़ो_eeprom(ioaddr, i));

	/* Restore the "Product ID" to the EEPROM पढ़ो रेजिस्टर. */
	पढ़ो_eeprom(ioaddr, 3);

	dev = alloc_etherdev(माप (काष्ठा el3_निजी));
	अगर (dev == शून्य) अणु
		release_region(ioaddr, EL3_IO_EXTENT);
		वापस -ENOMEM;
	पूर्ण

	SET_NETDEV_DEV(dev, device);
	netdev_boot_setup_check(dev);

	el3_dev_fill(dev, phys_addr, ioaddr, irq, अगर_port, EL3_EISA);
	eisa_set_drvdata (edev, dev);
	err = el3_common_init(dev);

	अगर (err) अणु
		eisa_set_drvdata (edev, शून्य);
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण

	el3_devs[el3_cards++] = dev;
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* This हटाओ works क्रम all device types.
 *
 * The net dev must be stored in the driver data field */
अटल पूर्णांक el3_device_हटाओ(काष्ठा device *device)
अणु
	काष्ठा net_device *dev;

	dev = dev_get_drvdata(device);

	el3_common_हटाओ (dev);
	वापस 0;
पूर्ण

/* Read a word from the EEPROM using the regular EEPROM access रेजिस्टर.
   Assume that we are in रेजिस्टर winकरोw zero.
 */
अटल uलघु पढ़ो_eeprom(पूर्णांक ioaddr, पूर्णांक index)
अणु
	outw(EEPROM_READ + index, ioaddr + 10);
	/* Pause क्रम at least 162 us. क्रम the पढ़ो to take place.
	   Some chips seem to require much दीर्घer */
	mdelay(2);
	वापस inw(ioaddr + 12);
पूर्ण

/* Read a word from the EEPROM when in the ISA ID probe state. */
अटल uलघु id_पढ़ो_eeprom(पूर्णांक index)
अणु
	पूर्णांक bit, word = 0;

	/* Issue पढ़ो command, and छोड़ो क्रम at least 162 us. क्रम it to complete.
	   Assume extra-fast 16Mhz bus. */
	outb(EEPROM_READ + index, id_port);

	/* Pause क्रम at least 162 us. क्रम the पढ़ो to take place. */
	/* Some chips seem to require much दीर्घer */
	mdelay(4);

	क्रम (bit = 15; bit >= 0; bit--)
		word = (word << 1) + (inb(id_port) & 0x01);

	अगर (el3_debug > 3)
		pr_debug("  3c509 EEPROM word %d %#4.4x.\n", index, word);

	वापस word;
पूर्ण


अटल पूर्णांक
el3_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक i;

	outw(TxReset, ioaddr + EL3_CMD);
	outw(RxReset, ioaddr + EL3_CMD);
	outw(SetStatusEnb | 0x00, ioaddr + EL3_CMD);

	i = request_irq(dev->irq, el3_पूर्णांकerrupt, 0, dev->name, dev);
	अगर (i)
		वापस i;

	EL3WINDOW(0);
	अगर (el3_debug > 3)
		pr_debug("%s: Opening, IRQ %d	 status@%x %4.4x.\n", dev->name,
			   dev->irq, ioaddr + EL3_STATUS, inw(ioaddr + EL3_STATUS));

	el3_up(dev);

	अगर (el3_debug > 3)
		pr_debug("%s: Opened 3c509  IRQ %d  status %4.4x.\n",
			   dev->name, dev->irq, inw(ioaddr + EL3_STATUS));

	वापस 0;
पूर्ण

अटल व्योम
el3_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	पूर्णांक ioaddr = dev->base_addr;

	/* Transmitter समयout, serious problems. */
	pr_warn("%s: transmit timed out, Tx_status %2.2x status %4.4x Tx FIFO room %d\n",
		dev->name, inb(ioaddr + TX_STATUS), inw(ioaddr + EL3_STATUS),
		inw(ioaddr + TX_FREE));
	dev->stats.tx_errors++;
	netअगर_trans_update(dev); /* prevent tx समयout */
	/* Issue TX_RESET and TX_START commands. */
	outw(TxReset, ioaddr + EL3_CMD);
	outw(TxEnable, ioaddr + EL3_CMD);
	netअगर_wake_queue(dev);
पूर्ण


अटल netdev_tx_t
el3_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	पूर्णांक ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue (dev);

	dev->stats.tx_bytes += skb->len;

	अगर (el3_debug > 4) अणु
		pr_debug("%s: el3_start_xmit(length = %u) called, status %4.4x.\n",
			   dev->name, skb->len, inw(ioaddr + EL3_STATUS));
	पूर्ण
	/*
	 *	We lock the driver against other processors. Note
	 *	we करोn't need to lock versus the IRQ as we suspended
	 *	that. This means that we lose the ability to take
	 *	an RX during a TX upload. That sucks a bit with SMP
	 *	on an original 3c509 (2K buffer)
	 *
	 *	Using disable_irq stops us crapping on other
	 *	समय sensitive devices.
	 */

	spin_lock_irqsave(&lp->lock, flags);

	/* Put out the द्विगुनword header... */
	outw(skb->len, ioaddr + TX_FIFO);
	outw(0x00, ioaddr + TX_FIFO);
	/* ... and the packet rounded to a द्विगुनword. */
	outsl(ioaddr + TX_FIFO, skb->data, (skb->len + 3) >> 2);

	अगर (inw(ioaddr + TX_FREE) > 1536)
		netअगर_start_queue(dev);
	अन्यथा
		/* Interrupt us when the FIFO has room क्रम max-sized packet. */
		outw(SetTxThreshold + 1536, ioaddr + EL3_CMD);

	spin_unlock_irqrestore(&lp->lock, flags);

	dev_consume_skb_any (skb);

	/* Clear the Tx status stack. */
	अणु
		लघु tx_status;
		पूर्णांक i = 4;

		जबतक (--i > 0	&&	(tx_status = inb(ioaddr + TX_STATUS)) > 0) अणु
			अगर (tx_status & 0x38) dev->stats.tx_पातed_errors++;
			अगर (tx_status & 0x30) outw(TxReset, ioaddr + EL3_CMD);
			अगर (tx_status & 0x3C) outw(TxEnable, ioaddr + EL3_CMD);
			outb(0x00, ioaddr + TX_STATUS); /* Pop the status stack. */
		पूर्ण
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

/* The EL3 पूर्णांकerrupt handler. */
अटल irqवापस_t
el3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा el3_निजी *lp;
	पूर्णांक ioaddr, status;
	पूर्णांक i = max_पूर्णांकerrupt_work;

	lp = netdev_priv(dev);
	spin_lock(&lp->lock);

	ioaddr = dev->base_addr;

	अगर (el3_debug > 4) अणु
		status = inw(ioaddr + EL3_STATUS);
		pr_debug("%s: interrupt, status %4.4x.\n", dev->name, status);
	पूर्ण

	जबतक ((status = inw(ioaddr + EL3_STATUS)) &
		   (IntLatch | RxComplete | StatsFull)) अणु

		अगर (status & RxComplete)
			el3_rx(dev);

		अगर (status & TxAvailable) अणु
			अगर (el3_debug > 5)
				pr_debug("	TX room bit was handled.\n");
			/* There's room in the FIFO क्रम a full-sized packet. */
			outw(AckIntr | TxAvailable, ioaddr + EL3_CMD);
			netअगर_wake_queue (dev);
		पूर्ण
		अगर (status & (AdapterFailure | RxEarly | StatsFull | TxComplete)) अणु
			/* Handle all uncommon पूर्णांकerrupts. */
			अगर (status & StatsFull)				/* Empty statistics. */
				update_stats(dev);
			अगर (status & RxEarly) अणु				/* Rx early is unused. */
				el3_rx(dev);
				outw(AckIntr | RxEarly, ioaddr + EL3_CMD);
			पूर्ण
			अगर (status & TxComplete) अणु			/* Really Tx error. */
				लघु tx_status;
				पूर्णांक i = 4;

				जबतक (--i>0 && (tx_status = inb(ioaddr + TX_STATUS)) > 0) अणु
					अगर (tx_status & 0x38) dev->stats.tx_पातed_errors++;
					अगर (tx_status & 0x30) outw(TxReset, ioaddr + EL3_CMD);
					अगर (tx_status & 0x3C) outw(TxEnable, ioaddr + EL3_CMD);
					outb(0x00, ioaddr + TX_STATUS); /* Pop the status stack. */
				पूर्ण
			पूर्ण
			अगर (status & AdapterFailure) अणु
				/* Adapter failure requires Rx reset and reinit. */
				outw(RxReset, ioaddr + EL3_CMD);
				/* Set the Rx filter to the current state. */
				outw(SetRxFilter | RxStation | RxBroadcast
					 | (dev->flags & IFF_ALLMULTI ? RxMulticast : 0)
					 | (dev->flags & IFF_PROMISC ? RxProm : 0),
					 ioaddr + EL3_CMD);
				outw(RxEnable, ioaddr + EL3_CMD); /* Re-enable the receiver. */
				outw(AckIntr | AdapterFailure, ioaddr + EL3_CMD);
			पूर्ण
		पूर्ण

		अगर (--i < 0) अणु
			pr_err("%s: Infinite loop in interrupt, status %4.4x.\n",
				   dev->name, status);
			/* Clear all पूर्णांकerrupts. */
			outw(AckIntr | 0xFF, ioaddr + EL3_CMD);
			अवरोध;
		पूर्ण
		/* Acknowledge the IRQ. */
		outw(AckIntr | IntReq | IntLatch, ioaddr + EL3_CMD); /* Ack IRQ */
	पूर्ण

	अगर (el3_debug > 4) अणु
		pr_debug("%s: exiting interrupt, status %4.4x.\n", dev->name,
			   inw(ioaddr + EL3_STATUS));
	पूर्ण
	spin_unlock(&lp->lock);
	वापस IRQ_HANDLED;
पूर्ण


#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling receive - used by netconsole and other diagnostic tools
 * to allow network i/o with पूर्णांकerrupts disabled.
 */
अटल व्योम el3_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	el3_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा net_device_stats *
el3_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	/*
	 *	This is fast enough not to bother with disable IRQ
	 *	stuff.
	 */

	spin_lock_irqsave(&lp->lock, flags);
	update_stats(dev);
	spin_unlock_irqrestore(&lp->lock, flags);
	वापस &dev->stats;
पूर्ण

/*  Update statistics.  We change to रेजिस्टर winकरोw 6, so this should be run
	single-thपढ़ोed अगर the device is active. This is expected to be a rare
	operation, and it's simpler क्रम the rest of the driver to assume that
	winकरोw 1 is always valid rather than use a special winकरोw-state variable.
	*/
अटल व्योम update_stats(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;

	अगर (el3_debug > 5)
		pr_debug("   Updating the statistics.\n");
	/* Turn off statistics updates जबतक पढ़ोing. */
	outw(StatsDisable, ioaddr + EL3_CMD);
	/* Switch to the stats winकरोw, and पढ़ो everything. */
	EL3WINDOW(6);
	dev->stats.tx_carrier_errors 	+= inb(ioaddr + 0);
	dev->stats.tx_heartbeat_errors	+= inb(ioaddr + 1);
	/* Multiple collisions. */	   inb(ioaddr + 2);
	dev->stats.collisions		+= inb(ioaddr + 3);
	dev->stats.tx_winकरोw_errors	+= inb(ioaddr + 4);
	dev->stats.rx_fअगरo_errors	+= inb(ioaddr + 5);
	dev->stats.tx_packets		+= inb(ioaddr + 6);
	/* Rx packets	*/		   inb(ioaddr + 7);
	/* Tx deferrals */		   inb(ioaddr + 8);
	inw(ioaddr + 10);	/* Total Rx and Tx octets. */
	inw(ioaddr + 12);

	/* Back to winकरोw 1, and turn statistics back on. */
	EL3WINDOW(1);
	outw(StatsEnable, ioaddr + EL3_CMD);
पूर्ण

अटल पूर्णांक
el3_rx(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	लघु rx_status;

	अगर (el3_debug > 5)
		pr_debug("   In rx_packet(), status %4.4x, rx_status %4.4x.\n",
			   inw(ioaddr+EL3_STATUS), inw(ioaddr+RX_STATUS));
	जबतक ((rx_status = inw(ioaddr + RX_STATUS)) > 0) अणु
		अगर (rx_status & 0x4000) अणु /* Error, update stats. */
			लघु error = rx_status & 0x3800;

			outw(RxDiscard, ioaddr + EL3_CMD);
			dev->stats.rx_errors++;
			चयन (error) अणु
			हाल 0x0000:		dev->stats.rx_over_errors++; अवरोध;
			हाल 0x0800:		dev->stats.rx_length_errors++; अवरोध;
			हाल 0x1000:		dev->stats.rx_frame_errors++; अवरोध;
			हाल 0x1800:		dev->stats.rx_length_errors++; अवरोध;
			हाल 0x2000:		dev->stats.rx_frame_errors++; अवरोध;
			हाल 0x2800:		dev->stats.rx_crc_errors++; अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			लघु pkt_len = rx_status & 0x7ff;
			काष्ठा sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 5);
			अगर (el3_debug > 4)
				pr_debug("Receiving packet size %d status %4.4x.\n",
					   pkt_len, rx_status);
			अगर (skb != शून्य) अणु
				skb_reserve(skb, 2);     /* Align IP on 16 byte */

				/* 'skb->data' poपूर्णांकs to the start of sk_buff data area. */
				insl(ioaddr + RX_FIFO, skb_put(skb,pkt_len),
					 (pkt_len + 3) >> 2);

				outw(RxDiscard, ioaddr + EL3_CMD); /* Pop top Rx packet. */
				skb->protocol = eth_type_trans(skb,dev);
				netअगर_rx(skb);
				dev->stats.rx_bytes += pkt_len;
				dev->stats.rx_packets++;
				जारी;
			पूर्ण
			outw(RxDiscard, ioaddr + EL3_CMD);
			dev->stats.rx_dropped++;
			अगर (el3_debug)
				pr_debug("%s: Couldn't allocate a sk_buff of size %d.\n",
					   dev->name, pkt_len);
		पूर्ण
		inw(ioaddr + EL3_STATUS); 				/* Delay. */
		जबतक (inw(ioaddr + EL3_STATUS) & 0x1000)
			pr_debug("	Waiting for 3c509 to discard packet, status %x.\n",
				   inw(ioaddr + EL3_STATUS) );
	पूर्ण

	वापस 0;
पूर्ण

/*
 *     Set or clear the multicast filter क्रम this adaptor.
 */
अटल व्योम
set_multicast_list(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक mc_count = netdev_mc_count(dev);

	अगर (el3_debug > 1) अणु
		अटल पूर्णांक old;
		अगर (old != mc_count) अणु
			old = mc_count;
			pr_debug("%s: Setting Rx mode to %d addresses.\n",
				 dev->name, mc_count);
		पूर्ण
	पूर्ण
	spin_lock_irqsave(&lp->lock, flags);
	अगर (dev->flags&IFF_PROMISC) अणु
		outw(SetRxFilter | RxStation | RxMulticast | RxBroadcast | RxProm,
			 ioaddr + EL3_CMD);
	पूर्ण
	अन्यथा अगर (mc_count || (dev->flags&IFF_ALLMULTI)) अणु
		outw(SetRxFilter | RxStation | RxMulticast | RxBroadcast, ioaddr + EL3_CMD);
	पूर्ण
	अन्यथा
		outw(SetRxFilter | RxStation | RxBroadcast, ioaddr + EL3_CMD);
	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

अटल पूर्णांक
el3_बंद(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	काष्ठा el3_निजी *lp = netdev_priv(dev);

	अगर (el3_debug > 2)
		pr_debug("%s: Shutting down ethercard.\n", dev->name);

	el3_करोwn(dev);

	मुक्त_irq(dev->irq, dev);
	/* Switching back to winकरोw 0 disables the IRQ. */
	EL3WINDOW(0);
	अगर (lp->type != EL3_EISA) अणु
		/* But we explicitly zero the IRQ line select anyway. Don't करो
		 * it on EISA cards, it prevents the module from getting an
		 * IRQ after unload+reload... */
		outw(0x0f00, ioaddr + WN0_IRQ);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
el3_link_ok(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	u16 पंचांगp;

	EL3WINDOW(4);
	पंचांगp = inw(ioaddr + WN4_MEDIA);
	EL3WINDOW(1);
	वापस पंचांगp & (1<<11);
पूर्ण

अटल व्योम
el3_netdev_get_ecmd(काष्ठा net_device *dev, काष्ठा ethtool_link_ksettings *cmd)
अणु
	u16 पंचांगp;
	पूर्णांक ioaddr = dev->base_addr;
	u32 supported;

	EL3WINDOW(0);
	/* obtain current transceiver via WN4_MEDIA? */
	पंचांगp = inw(ioaddr + WN0_ADDR_CONF);
	चयन (पंचांगp >> 14) अणु
	हाल 0:
		cmd->base.port = PORT_TP;
		अवरोध;
	हाल 1:
		cmd->base.port = PORT_AUI;
		अवरोध;
	हाल 3:
		cmd->base.port = PORT_BNC;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	cmd->base.duplex = DUPLEX_HALF;
	supported = 0;
	पंचांगp = inw(ioaddr + WN0_CONF_CTRL);
	अगर (पंचांगp & (1<<13))
		supported |= SUPPORTED_AUI;
	अगर (पंचांगp & (1<<12))
		supported |= SUPPORTED_BNC;
	अगर (पंचांगp & (1<<9)) अणु
		supported |= SUPPORTED_TP | SUPPORTED_10baseT_Half |
				SUPPORTED_10baseT_Full;	/* hmm... */
		EL3WINDOW(4);
		पंचांगp = inw(ioaddr + WN4_NETDIAG);
		अगर (पंचांगp & FD_ENABLE)
			cmd->base.duplex = DUPLEX_FULL;
	पूर्ण

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	cmd->base.speed = SPEED_10;
	EL3WINDOW(1);
पूर्ण

अटल पूर्णांक
el3_netdev_set_ecmd(काष्ठा net_device *dev,
		    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	u16 पंचांगp;
	पूर्णांक ioaddr = dev->base_addr;

	अगर (cmd->base.speed != SPEED_10)
		वापस -EINVAL;
	अगर ((cmd->base.duplex != DUPLEX_HALF) &&
	    (cmd->base.duplex != DUPLEX_FULL))
		वापस -EINVAL;

	/* change XCVR type */
	EL3WINDOW(0);
	पंचांगp = inw(ioaddr + WN0_ADDR_CONF);
	चयन (cmd->base.port) अणु
	हाल PORT_TP:
		पंचांगp &= ~(3<<14);
		dev->अगर_port = 0;
		अवरोध;
	हाल PORT_AUI:
		पंचांगp |= (1<<14);
		dev->अगर_port = 1;
		अवरोध;
	हाल PORT_BNC:
		पंचांगp |= (3<<14);
		dev->अगर_port = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	outw(पंचांगp, ioaddr + WN0_ADDR_CONF);
	अगर (dev->अगर_port == 3) अणु
		/* fire up the DC-DC convertor अगर BNC माला_लो enabled */
		पंचांगp = inw(ioaddr + WN0_ADDR_CONF);
		अगर (पंचांगp & (3 << 14)) अणु
			outw(StartCoax, ioaddr + EL3_CMD);
			udelay(800);
		पूर्ण अन्यथा
			वापस -EIO;
	पूर्ण

	EL3WINDOW(4);
	पंचांगp = inw(ioaddr + WN4_NETDIAG);
	अगर (cmd->base.duplex == DUPLEX_FULL)
		पंचांगp |= FD_ENABLE;
	अन्यथा
		पंचांगp &= ~FD_ENABLE;
	outw(पंचांगp, ioaddr + WN4_NETDIAG);
	EL3WINDOW(1);

	वापस 0;
पूर्ण

अटल व्योम el3_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
पूर्ण

अटल पूर्णांक el3_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);

	spin_lock_irq(&lp->lock);
	el3_netdev_get_ecmd(dev, cmd);
	spin_unlock_irq(&lp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक el3_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	पूर्णांक ret;

	spin_lock_irq(&lp->lock);
	ret = el3_netdev_set_ecmd(dev, cmd);
	spin_unlock_irq(&lp->lock);
	वापस ret;
पूर्ण

अटल u32 el3_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	u32 ret;

	spin_lock_irq(&lp->lock);
	ret = el3_link_ok(dev);
	spin_unlock_irq(&lp->lock);
	वापस ret;
पूर्ण

अटल u32 el3_get_msglevel(काष्ठा net_device *dev)
अणु
	वापस el3_debug;
पूर्ण

अटल व्योम el3_set_msglevel(काष्ठा net_device *dev, u32 v)
अणु
	el3_debug = v;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.get_drvinfo = el3_get_drvinfo,
	.get_link = el3_get_link,
	.get_msglevel = el3_get_msglevel,
	.set_msglevel = el3_set_msglevel,
	.get_link_ksettings = el3_get_link_ksettings,
	.set_link_ksettings = el3_set_link_ksettings,
पूर्ण;

अटल व्योम
el3_करोwn(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;

	netअगर_stop_queue(dev);

	/* Turn off statistics ASAP.  We update lp->stats below. */
	outw(StatsDisable, ioaddr + EL3_CMD);

	/* Disable the receiver and transmitter. */
	outw(RxDisable, ioaddr + EL3_CMD);
	outw(TxDisable, ioaddr + EL3_CMD);

	अगर (dev->अगर_port == 3)
		/* Turn off thinnet घातer.  Green! */
		outw(StopCoax, ioaddr + EL3_CMD);
	अन्यथा अगर (dev->अगर_port == 0) अणु
		/* Disable link beat and jabber, अगर_port may change here next खोलो(). */
		EL3WINDOW(4);
		outw(inw(ioaddr + WN4_MEDIA) & ~MEDIA_TP, ioaddr + WN4_MEDIA);
	पूर्ण

	outw(SetIntrEnb | 0x0000, ioaddr + EL3_CMD);

	update_stats(dev);
पूर्ण

अटल व्योम
el3_up(काष्ठा net_device *dev)
अणु
	पूर्णांक i, sw_info, net_diag;
	पूर्णांक ioaddr = dev->base_addr;

	/* Activating the board required and करोes no harm otherwise */
	outw(0x0001, ioaddr + 4);

	/* Set the IRQ line. */
	outw((dev->irq << 12) | 0x0f00, ioaddr + WN0_IRQ);

	/* Set the station address in winकरोw 2 each समय खोलोed. */
	EL3WINDOW(2);

	क्रम (i = 0; i < 6; i++)
		outb(dev->dev_addr[i], ioaddr + i);

	अगर ((dev->अगर_port & 0x03) == 3) /* BNC पूर्णांकerface */
		/* Start the thinnet transceiver. We should really रुको 50ms...*/
		outw(StartCoax, ioaddr + EL3_CMD);
	अन्यथा अगर ((dev->अगर_port & 0x03) == 0) अणु /* 10baseT पूर्णांकerface */
		/* Combine secondary sw_info word (the adapter level) and primary
			sw_info word (duplex setting plus other useless bits) */
		EL3WINDOW(0);
		sw_info = (पढ़ो_eeprom(ioaddr, 0x14) & 0x400f) |
			(पढ़ो_eeprom(ioaddr, 0x0d) & 0xBff0);

		EL3WINDOW(4);
		net_diag = inw(ioaddr + WN4_NETDIAG);
		net_diag = (net_diag | FD_ENABLE); /* temporarily assume full-duplex will be set */
		pr_info("%s: ", dev->name);
		चयन (dev->अगर_port & 0x0c) अणु
			हाल 12:
				/* क्रमce full-duplex mode अगर 3c5x9b */
				अगर (sw_info & 0x000f) अणु
					pr_cont("Forcing 3c5x9b full-duplex mode");
					अवरोध;
				पूर्ण
				fallthrough;
			हाल 8:
				/* set full-duplex mode based on eeprom config setting */
				अगर ((sw_info & 0x000f) && (sw_info & 0x8000)) अणु
					pr_cont("Setting 3c5x9b full-duplex mode (from EEPROM configuration bit)");
					अवरोध;
				पूर्ण
				fallthrough;
			शेष:
				/* xcvr=(0 || 4) OR user has an old 3c5x9 non "B" model */
				pr_cont("Setting 3c5x9/3c5x9B half-duplex mode");
				net_diag = (net_diag & ~FD_ENABLE); /* disable full duplex */
		पूर्ण

		outw(net_diag, ioaddr + WN4_NETDIAG);
		pr_cont(" if_port: %d, sw_info: %4.4x\n", dev->अगर_port, sw_info);
		अगर (el3_debug > 3)
			pr_debug("%s: 3c5x9 net diag word is now: %4.4x.\n", dev->name, net_diag);
		/* Enable link beat and jabber check. */
		outw(inw(ioaddr + WN4_MEDIA) | MEDIA_TP, ioaddr + WN4_MEDIA);
	पूर्ण

	/* Switch to the stats winकरोw, and clear all stats by पढ़ोing. */
	outw(StatsDisable, ioaddr + EL3_CMD);
	EL3WINDOW(6);
	क्रम (i = 0; i < 9; i++)
		inb(ioaddr + i);
	inw(ioaddr + 10);
	inw(ioaddr + 12);

	/* Switch to रेजिस्टर set 1 क्रम normal use. */
	EL3WINDOW(1);

	/* Accept b-हाल and phys addr only. */
	outw(SetRxFilter | RxStation | RxBroadcast, ioaddr + EL3_CMD);
	outw(StatsEnable, ioaddr + EL3_CMD); /* Turn on statistics. */

	outw(RxEnable, ioaddr + EL3_CMD); /* Enable the receiver. */
	outw(TxEnable, ioaddr + EL3_CMD); /* Enable transmitter. */
	/* Allow status bits to be seen. */
	outw(SetStatusEnb | 0xff, ioaddr + EL3_CMD);
	/* Ack all pending events, and set active indicator mask. */
	outw(AckIntr | IntLatch | TxAvailable | RxEarly | IntReq,
		 ioaddr + EL3_CMD);
	outw(SetIntrEnb | IntLatch|TxAvailable|TxComplete|RxComplete|StatsFull,
		 ioaddr + EL3_CMD);

	netअगर_start_queue(dev);
पूर्ण

/* Power Management support functions */
#अगर_घोषित CONFIG_PM

अटल पूर्णांक
el3_suspend(काष्ठा device *pdev, pm_message_t state)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा net_device *dev;
	काष्ठा el3_निजी *lp;
	पूर्णांक ioaddr;

	dev = dev_get_drvdata(pdev);
	lp = netdev_priv(dev);
	ioaddr = dev->base_addr;

	spin_lock_irqsave(&lp->lock, flags);

	अगर (netअगर_running(dev))
		netअगर_device_detach(dev);

	el3_करोwn(dev);
	outw(PowerDown, ioaddr + EL3_CMD);

	spin_unlock_irqrestore(&lp->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
el3_resume(काष्ठा device *pdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा net_device *dev;
	काष्ठा el3_निजी *lp;
	पूर्णांक ioaddr;

	dev = dev_get_drvdata(pdev);
	lp = netdev_priv(dev);
	ioaddr = dev->base_addr;

	spin_lock_irqsave(&lp->lock, flags);

	outw(PowerUp, ioaddr + EL3_CMD);
	EL3WINDOW(0);
	el3_up(dev);

	अगर (netअगर_running(dev))
		netअगर_device_attach(dev);

	spin_unlock_irqrestore(&lp->lock, flags);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

module_param(debug,पूर्णांक, 0);
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "debug level (0-6)");
MODULE_PARM_DESC(irq, "IRQ number(s) (assigned)");
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "maximum events handled per interrupt");
#अगर_घोषित CONFIG_PNP
module_param(nopnp, पूर्णांक, 0);
MODULE_PARM_DESC(nopnp, "disable ISA PnP support (0-1)");
#पूर्ण_अगर	/* CONFIG_PNP */
MODULE_DESCRIPTION("3Com Etherlink III (3c509, 3c509B, 3c529, 3c579) ethernet driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init el3_init_module(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (debug >= 0)
		el3_debug = debug;

#अगर_घोषित CONFIG_PNP
	अगर (!nopnp) अणु
		ret = pnp_रेजिस्टर_driver(&el3_pnp_driver);
		अगर (!ret)
			pnp_रेजिस्टरed = 1;
	पूर्ण
#पूर्ण_अगर
	/* Select an खोलो I/O location at 0x1*0 to करो ISA contention select. */
	/* Start with 0x110 to aव्योम some sound cards.*/
	क्रम (id_port = 0x110 ; id_port < 0x200; id_port += 0x10) अणु
		अगर (!request_region(id_port, 1, "3c509-control"))
			जारी;
		outb(0x00, id_port);
		outb(0xff, id_port);
		अगर (inb(id_port) & 0x01)
			अवरोध;
		अन्यथा
			release_region(id_port, 1);
	पूर्ण
	अगर (id_port >= 0x200) अणु
		id_port = 0;
		pr_err("No I/O port available for 3c509 activation.\n");
	पूर्ण अन्यथा अणु
		ret = isa_रेजिस्टर_driver(&el3_isa_driver, EL3_MAX_CARDS);
		अगर (!ret)
			isa_रेजिस्टरed = 1;
	पूर्ण
#अगर_घोषित CONFIG_EISA
	ret = eisa_driver_रेजिस्टर(&el3_eisa_driver);
	अगर (!ret)
		eisa_रेजिस्टरed = 1;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		ret = 0;
#पूर्ण_अगर
	अगर (isa_रेजिस्टरed)
		ret = 0;
#अगर_घोषित CONFIG_EISA
	अगर (eisa_रेजिस्टरed)
		ret = 0;
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम __निकास el3_cleanup_module(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&el3_pnp_driver);
#पूर्ण_अगर
	अगर (isa_रेजिस्टरed)
		isa_unरेजिस्टर_driver(&el3_isa_driver);
	अगर (id_port)
		release_region(id_port, 1);
#अगर_घोषित CONFIG_EISA
	अगर (eisa_रेजिस्टरed)
		eisa_driver_unरेजिस्टर(&el3_eisa_driver);
#पूर्ण_अगर
पूर्ण

module_init (el3_init_module);
module_निकास (el3_cleanup_module);
