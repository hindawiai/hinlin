<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* sb1000.c: A General Instruments SB1000 driver क्रम linux. */
/*
	Written 1998 by Franco Venturi.

	Copyright 1998 by Franco Venturi.
	Copyright 1994,1995 by Donald Becker.
	Copyright 1993 United States Government as represented by the
	Director, National Security Agency.

	This driver is क्रम the General Instruments SB1000 (पूर्णांकernal SURFboard)

	The author may be reached as fventuri@mediaone.net


	Changes:

	981115 Steven Hirsch <shirsch@adelphia.net>

	Linus changed the समयr पूर्णांकerface.  Should work on all recent
	development kernels.

	980608 Steven Hirsch <shirsch@adelphia.net>

	Small changes to make it work with 2.1.x kernels. Hopefully,
	nothing major will change beक्रमe official release of Linux 2.2.

	Merged with 2.2 - Alan Cox
*/

अटल अक्षर version[] = "sb1000.c:v1.1.2 6/01/98 (fventuri@mediaone.net)\n";

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_cablemodem.h> /* क्रम SIOGCM/SIOSCM stuff */
#समावेश <linux/in.h>
#समावेश <linux/ioport.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>	/* क्रम udelay() */
#समावेश <linux/etherdevice.h>
#समावेश <linux/pnp.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>

#अगर_घोषित SB1000_DEBUG
अटल पूर्णांक sb1000_debug = SB1000_DEBUG;
#अन्यथा
अटल स्थिर पूर्णांक sb1000_debug = 1;
#पूर्ण_अगर

अटल स्थिर पूर्णांक SB1000_IO_EXTENT = 8;
/* SB1000 Maximum Receive Unit */
अटल स्थिर पूर्णांक SB1000_MRU = 1500; /* octects */

#घोषणा NPIDS 4
काष्ठा sb1000_निजी अणु
	काष्ठा sk_buff *rx_skb[NPIDS];
	लघु rx_dlen[NPIDS];
	अचिन्हित पूर्णांक rx_frames;
	लघु rx_error_count;
	लघु rx_error_dpc_count;
	अचिन्हित अक्षर rx_session_id[NPIDS];
	अचिन्हित अक्षर rx_frame_id[NPIDS];
	अचिन्हित अक्षर rx_pkt_type[NPIDS];
पूर्ण;

/* prototypes क्रम Linux पूर्णांकerface */
बाह्य पूर्णांक sb1000_probe(काष्ठा net_device *dev);
अटल पूर्णांक sb1000_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक sb1000_dev_ioctl (काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
अटल netdev_tx_t sb1000_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev);
अटल irqवापस_t sb1000_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक sb1000_बंद(काष्ठा net_device *dev);


/* SB1000 hardware routines to be used during खोलो/configuration phases */
अटल पूर्णांक card_रुको_क्रम_busy_clear(स्थिर पूर्णांक ioaddr[],
	स्थिर अक्षर* name);
अटल पूर्णांक card_रुको_क्रम_पढ़ोy(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	अचिन्हित अक्षर in[]);
अटल पूर्णांक card_send_command(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	स्थिर अचिन्हित अक्षर out[], अचिन्हित अक्षर in[]);

/* SB1000 hardware routines to be used during frame rx पूर्णांकerrupt */
अटल पूर्णांक sb1000_रुको_क्रम_पढ़ोy(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name);
अटल पूर्णांक sb1000_रुको_क्रम_पढ़ोy_clear(स्थिर पूर्णांक ioaddr[],
	स्थिर अक्षर* name);
अटल व्योम sb1000_send_command(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	स्थिर अचिन्हित अक्षर out[]);
अटल व्योम sb1000_पढ़ो_status(स्थिर पूर्णांक ioaddr[], अचिन्हित अक्षर in[]);
अटल व्योम sb1000_issue_पढ़ो_command(स्थिर पूर्णांक ioaddr[],
	स्थिर अक्षर* name);

/* SB1000 commands क्रम खोलो/configuration */
अटल पूर्णांक sb1000_reset(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name);
अटल पूर्णांक sb1000_check_CRC(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name);
अटल अंतरभूत पूर्णांक sb1000_start_get_set_command(स्थिर पूर्णांक ioaddr[],
	स्थिर अक्षर* name);
अटल पूर्णांक sb1000_end_get_set_command(स्थिर पूर्णांक ioaddr[],
	स्थिर अक्षर* name);
अटल पूर्णांक sb1000_activate(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name);
अटल पूर्णांक sb1000_get_firmware_version(स्थिर पूर्णांक ioaddr[],
	स्थिर अक्षर* name, अचिन्हित अक्षर version[], पूर्णांक करो_end);
अटल पूर्णांक sb1000_get_frequency(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	पूर्णांक* frequency);
अटल पूर्णांक sb1000_set_frequency(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	पूर्णांक frequency);
अटल पूर्णांक sb1000_get_PIDs(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	लघु PID[]);
अटल पूर्णांक sb1000_set_PIDs(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	स्थिर लघु PID[]);

/* SB1000 commands क्रम frame rx पूर्णांकerrupt */
अटल पूर्णांक sb1000_rx(काष्ठा net_device *dev);
अटल व्योम sb1000_error_dpc(काष्ठा net_device *dev);

अटल स्थिर काष्ठा pnp_device_id sb1000_pnp_ids[] = अणु
	अणु "GIC1000", 0 पूर्ण,
	अणु "", 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pnp, sb1000_pnp_ids);

अटल स्थिर काष्ठा net_device_ops sb1000_netdev_ops = अणु
	.nकरो_खोलो		= sb1000_खोलो,
	.nकरो_start_xmit		= sb1000_start_xmit,
	.nकरो_करो_ioctl		= sb1000_dev_ioctl,
	.nकरो_stop		= sb1000_बंद,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक
sb1000_probe_one(काष्ठा pnp_dev *pdev, स्थिर काष्ठा pnp_device_id *id)
अणु
	काष्ठा net_device *dev;
	अचिन्हित लघु ioaddr[2], irq;
	अचिन्हित पूर्णांक serial_number;
	पूर्णांक error = -ENODEV;

	अगर (pnp_device_attach(pdev) < 0)
		वापस -ENODEV;
	अगर (pnp_activate_dev(pdev) < 0)
		जाओ out_detach;

	अगर (!pnp_port_valid(pdev, 0) || !pnp_port_valid(pdev, 1))
		जाओ out_disable;
	अगर (!pnp_irq_valid(pdev, 0))
		जाओ out_disable;

	serial_number = pdev->card->serial;

	ioaddr[0] = pnp_port_start(pdev, 0);
	ioaddr[1] = pnp_port_start(pdev, 0);

	irq = pnp_irq(pdev, 0);

	अगर (!request_region(ioaddr[0], 16, "sb1000"))
		जाओ out_disable;
	अगर (!request_region(ioaddr[1], 16, "sb1000"))
		जाओ out_release_region0;

	dev = alloc_etherdev(माप(काष्ठा sb1000_निजी));
	अगर (!dev) अणु
		error = -ENOMEM;
		जाओ out_release_regions;
	पूर्ण


	dev->base_addr = ioaddr[0];
	/* mem_start holds the second I/O address */
	dev->mem_start = ioaddr[1];
	dev->irq = irq;

	अगर (sb1000_debug > 0)
		prपूर्णांकk(KERN_NOTICE "%s: sb1000 at (%#3.3lx,%#3.3lx), "
			"S/N %#8.8x, IRQ %d.\n", dev->name, dev->base_addr,
			dev->mem_start, serial_number, dev->irq);

	/*
	 * The SB1000 is an rx-only cable modem device.  The uplink is a modem
	 * and we करो not want to arp on it.
	 */
	dev->flags = IFF_POINTOPOINT|IFF_NOARP;

	SET_NETDEV_DEV(dev, &pdev->dev);

	अगर (sb1000_debug > 0)
		prपूर्णांकk(KERN_NOTICE "%s", version);

	dev->netdev_ops	= &sb1000_netdev_ops;

	/* hardware address is 0:0:serial_number */
	dev->dev_addr[2]	= serial_number >> 24 & 0xff;
	dev->dev_addr[3]	= serial_number >> 16 & 0xff;
	dev->dev_addr[4]	= serial_number >>  8 & 0xff;
	dev->dev_addr[5]	= serial_number >>  0 & 0xff;

	pnp_set_drvdata(pdev, dev);

	error = रेजिस्टर_netdev(dev);
	अगर (error)
		जाओ out_मुक्त_netdev;
	वापस 0;

 out_मुक्त_netdev:
	मुक्त_netdev(dev);
 out_release_regions:
	release_region(ioaddr[1], 16);
 out_release_region0:
	release_region(ioaddr[0], 16);
 out_disable:
	pnp_disable_dev(pdev);
 out_detach:
	pnp_device_detach(pdev);
	वापस error;
पूर्ण

अटल व्योम
sb1000_हटाओ_one(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा net_device *dev = pnp_get_drvdata(pdev);

	unरेजिस्टर_netdev(dev);
	release_region(dev->base_addr, 16);
	release_region(dev->mem_start, 16);
	मुक्त_netdev(dev);
पूर्ण

अटल काष्ठा pnp_driver sb1000_driver = अणु
	.name		= "sb1000",
	.id_table	= sb1000_pnp_ids,
	.probe		= sb1000_probe_one,
	.हटाओ		= sb1000_हटाओ_one,
पूर्ण;


/*
 * SB1000 hardware routines to be used during खोलो/configuration phases
 */

अटल स्थिर पूर्णांक TimeOutJअगरfies = (875 * HZ) / 100;

/* Card Wait For Busy Clear (cannot be used during an पूर्णांकerrupt) */
अटल पूर्णांक
card_रुको_क्रम_busy_clear(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name)
अणु
	अचिन्हित अक्षर a;
	अचिन्हित दीर्घ समयout;

	a = inb(ioaddr[0] + 7);
	समयout = jअगरfies + TimeOutJअगरfies;
	जबतक (a & 0x80 || a & 0x40) अणु
		/* a little sleep */
		yield();

		a = inb(ioaddr[0] + 7);
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			prपूर्णांकk(KERN_WARNING "%s: card_wait_for_busy_clear timeout\n",
				name);
			वापस -ETIME;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Card Wait For Ready (cannot be used during an पूर्णांकerrupt) */
अटल पूर्णांक
card_रुको_क्रम_पढ़ोy(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name, अचिन्हित अक्षर in[])
अणु
	अचिन्हित अक्षर a;
	अचिन्हित दीर्घ समयout;

	a = inb(ioaddr[1] + 6);
	समयout = jअगरfies + TimeOutJअगरfies;
	जबतक (a & 0x80 || !(a & 0x40)) अणु
		/* a little sleep */
		yield();

		a = inb(ioaddr[1] + 6);
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			prपूर्णांकk(KERN_WARNING "%s: card_wait_for_ready timeout\n",
				name);
			वापस -ETIME;
		पूर्ण
	पूर्ण

	in[1] = inb(ioaddr[0] + 1);
	in[2] = inb(ioaddr[0] + 2);
	in[3] = inb(ioaddr[0] + 3);
	in[4] = inb(ioaddr[0] + 4);
	in[0] = inb(ioaddr[0] + 5);
	in[6] = inb(ioaddr[0] + 6);
	in[5] = inb(ioaddr[1] + 6);
	वापस 0;
पूर्ण

/* Card Send Command (cannot be used during an पूर्णांकerrupt) */
अटल पूर्णांक
card_send_command(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	स्थिर अचिन्हित अक्षर out[], अचिन्हित अक्षर in[])
अणु
	पूर्णांक status;

	अगर ((status = card_रुको_क्रम_busy_clear(ioaddr, name)))
		वापस status;
	outb(0xa0, ioaddr[0] + 6);
	outb(out[2], ioaddr[0] + 1);
	outb(out[3], ioaddr[0] + 2);
	outb(out[4], ioaddr[0] + 3);
	outb(out[5], ioaddr[0] + 4);
	outb(out[1], ioaddr[0] + 5);
	outb(0xa0, ioaddr[0] + 6);
	outb(out[0], ioaddr[0] + 7);
	अगर (out[0] != 0x20 && out[0] != 0x30) अणु
		अगर ((status = card_रुको_क्रम_पढ़ोy(ioaddr, name, in)))
			वापस status;
		inb(ioaddr[0] + 7);
		अगर (sb1000_debug > 3)
			prपूर्णांकk(KERN_DEBUG "%s: card_send_command "
				"out: %02x%02x%02x%02x%02x%02x  "
				"in: %02x%02x%02x%02x%02x%02x%02x\n", name,
				out[0], out[1], out[2], out[3], out[4], out[5],
				in[0], in[1], in[2], in[3], in[4], in[5], in[6]);
	पूर्ण अन्यथा अणु
		अगर (sb1000_debug > 3)
			prपूर्णांकk(KERN_DEBUG "%s: card_send_command "
				"out: %02x%02x%02x%02x%02x%02x\n", name,
				out[0], out[1], out[2], out[3], out[4], out[5]);
	पूर्ण

	अगर (out[1] != 0x1b) अणु
		अगर (out[0] >= 0x80 && in[0] != (out[1] | 0x80))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * SB1000 hardware routines to be used during frame rx पूर्णांकerrupt
 */
अटल स्थिर पूर्णांक Sb1000TimeOutJअगरfies = 7 * HZ;

/* Card Wait For Ready (to be used during frame rx) */
अटल पूर्णांक
sb1000_रुको_क्रम_पढ़ोy(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + Sb1000TimeOutJअगरfies;
	जबतक (inb(ioaddr[1] + 6) & 0x80) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			prपूर्णांकk(KERN_WARNING "%s: sb1000_wait_for_ready timeout\n",
				name);
			वापस -ETIME;
		पूर्ण
	पूर्ण
	समयout = jअगरfies + Sb1000TimeOutJअगरfies;
	जबतक (!(inb(ioaddr[1] + 6) & 0x40)) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			prपूर्णांकk(KERN_WARNING "%s: sb1000_wait_for_ready timeout\n",
				name);
			वापस -ETIME;
		पूर्ण
	पूर्ण
	inb(ioaddr[0] + 7);
	वापस 0;
पूर्ण

/* Card Wait For Ready Clear (to be used during frame rx) */
अटल पूर्णांक
sb1000_रुको_क्रम_पढ़ोy_clear(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + Sb1000TimeOutJअगरfies;
	जबतक (inb(ioaddr[1] + 6) & 0x80) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			prपूर्णांकk(KERN_WARNING "%s: sb1000_wait_for_ready_clear timeout\n",
				name);
			वापस -ETIME;
		पूर्ण
	पूर्ण
	समयout = jअगरfies + Sb1000TimeOutJअगरfies;
	जबतक (inb(ioaddr[1] + 6) & 0x40) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			prपूर्णांकk(KERN_WARNING "%s: sb1000_wait_for_ready_clear timeout\n",
				name);
			वापस -ETIME;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Card Send Command (to be used during frame rx) */
अटल व्योम
sb1000_send_command(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	स्थिर अचिन्हित अक्षर out[])
अणु
	outb(out[2], ioaddr[0] + 1);
	outb(out[3], ioaddr[0] + 2);
	outb(out[4], ioaddr[0] + 3);
	outb(out[5], ioaddr[0] + 4);
	outb(out[1], ioaddr[0] + 5);
	outb(out[0], ioaddr[0] + 7);
	अगर (sb1000_debug > 3)
		prपूर्णांकk(KERN_DEBUG "%s: sb1000_send_command out: %02x%02x%02x%02x"
			"%02x%02x\n", name, out[0], out[1], out[2], out[3], out[4], out[5]);
पूर्ण

/* Card Read Status (to be used during frame rx) */
अटल व्योम
sb1000_पढ़ो_status(स्थिर पूर्णांक ioaddr[], अचिन्हित अक्षर in[])
अणु
	in[1] = inb(ioaddr[0] + 1);
	in[2] = inb(ioaddr[0] + 2);
	in[3] = inb(ioaddr[0] + 3);
	in[4] = inb(ioaddr[0] + 4);
	in[0] = inb(ioaddr[0] + 5);
पूर्ण

/* Issue Read Command (to be used during frame rx) */
अटल व्योम
sb1000_issue_पढ़ो_command(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x20, 0x00, 0x00, 0x01, 0x00, 0x00पूर्ण;

	sb1000_रुको_क्रम_पढ़ोy_clear(ioaddr, name);
	outb(0xa0, ioaddr[0] + 6);
	sb1000_send_command(ioaddr, name, Command0);
पूर्ण


/*
 * SB1000 commands क्रम खोलो/configuration
 */
/* reset SB1000 card */
अटल पूर्णांक
sb1000_reset(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x16, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अचिन्हित अक्षर st[7];
	पूर्णांक port, status;

	port = ioaddr[1] + 6;
	outb(0x4, port);
	inb(port);
	udelay(1000);
	outb(0x0, port);
	inb(port);
	ssleep(1);
	outb(0x4, port);
	inb(port);
	udelay(1000);
	outb(0x0, port);
	inb(port);
	udelay(0);

	अगर ((status = card_send_command(ioaddr, name, Command0, st)))
		वापस status;
	अगर (st[3] != 0xf0)
		वापस -EIO;
	वापस 0;
पूर्ण

/* check SB1000 firmware CRC */
अटल पूर्णांक
sb1000_check_CRC(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x1f, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अचिन्हित अक्षर st[7];
	पूर्णांक status;

	/* check CRC */
	अगर ((status = card_send_command(ioaddr, name, Command0, st)))
		वापस status;
	अगर (st[1] != st[3] || st[2] != st[4])
		वापस -EIO;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
sb1000_start_get_set_command(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x1b, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अचिन्हित अक्षर st[7];

	वापस card_send_command(ioaddr, name, Command0, st);
पूर्ण

अटल पूर्णांक
sb1000_end_get_set_command(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x1b, 0x02, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर अचिन्हित अक्षर Command1[6] = अणु0x20, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अचिन्हित अक्षर st[7];
	पूर्णांक status;

	अगर ((status = card_send_command(ioaddr, name, Command0, st)))
		वापस status;
	वापस card_send_command(ioaddr, name, Command1, st);
पूर्ण

अटल पूर्णांक
sb1000_activate(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x11, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर अचिन्हित अक्षर Command1[6] = अणु0x80, 0x16, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अचिन्हित अक्षर st[7];
	पूर्णांक status;

	ssleep(1);
	status = card_send_command(ioaddr, name, Command0, st);
	अगर (status)
		वापस status;
	status = card_send_command(ioaddr, name, Command1, st);
	अगर (status)
		वापस status;
	अगर (st[3] != 0xf1) अणु
		status = sb1000_start_get_set_command(ioaddr, name);
		अगर (status)
			वापस status;
		वापस -EIO;
	पूर्ण
	udelay(1000);
	वापस sb1000_start_get_set_command(ioaddr, name);
पूर्ण

/* get SB1000 firmware version */
अटल पूर्णांक
sb1000_get_firmware_version(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name,
	अचिन्हित अक्षर version[], पूर्णांक करो_end)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x23, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अचिन्हित अक्षर st[7];
	पूर्णांक status;

	अगर ((status = sb1000_start_get_set_command(ioaddr, name)))
		वापस status;
	अगर ((status = card_send_command(ioaddr, name, Command0, st)))
		वापस status;
	अगर (st[0] != 0xa3)
		वापस -EIO;
	version[0] = st[1];
	version[1] = st[2];
	अगर (करो_end)
		वापस sb1000_end_get_set_command(ioaddr, name);
	अन्यथा
		वापस 0;
पूर्ण

/* get SB1000 frequency */
अटल पूर्णांक
sb1000_get_frequency(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name, पूर्णांक* frequency)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x44, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अचिन्हित अक्षर st[7];
	पूर्णांक status;

	udelay(1000);
	अगर ((status = sb1000_start_get_set_command(ioaddr, name)))
		वापस status;
	अगर ((status = card_send_command(ioaddr, name, Command0, st)))
		वापस status;
	*frequency = ((st[1] << 8 | st[2]) << 8 | st[3]) << 8 | st[4];
	वापस sb1000_end_get_set_command(ioaddr, name);
पूर्ण

/* set SB1000 frequency */
अटल पूर्णांक
sb1000_set_frequency(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name, पूर्णांक frequency)
अणु
	अचिन्हित अक्षर st[7];
	पूर्णांक status;
	अचिन्हित अक्षर Command0[6] = अणु0x80, 0x29, 0x00, 0x00, 0x00, 0x00पूर्ण;

	स्थिर पूर्णांक FrequencyLowerLimit = 57000;
	स्थिर पूर्णांक FrequencyUpperLimit = 804000;

	अगर (frequency < FrequencyLowerLimit || frequency > FrequencyUpperLimit) अणु
		prपूर्णांकk(KERN_ERR "%s: frequency chosen (%d kHz) is not in the range "
			"[%d,%d] kHz\n", name, frequency, FrequencyLowerLimit,
			FrequencyUpperLimit);
		वापस -EINVAL;
	पूर्ण
	udelay(1000);
	अगर ((status = sb1000_start_get_set_command(ioaddr, name)))
		वापस status;
	Command0[5] = frequency & 0xff;
	frequency >>= 8;
	Command0[4] = frequency & 0xff;
	frequency >>= 8;
	Command0[3] = frequency & 0xff;
	frequency >>= 8;
	Command0[2] = frequency & 0xff;
	वापस card_send_command(ioaddr, name, Command0, st);
पूर्ण

/* get SB1000 PIDs */
अटल पूर्णांक
sb1000_get_PIDs(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name, लघु PID[])
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x40, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर अचिन्हित अक्षर Command1[6] = अणु0x80, 0x41, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर अचिन्हित अक्षर Command2[6] = अणु0x80, 0x42, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर अचिन्हित अक्षर Command3[6] = अणु0x80, 0x43, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अचिन्हित अक्षर st[7];
	पूर्णांक status;

	udelay(1000);
	अगर ((status = sb1000_start_get_set_command(ioaddr, name)))
		वापस status;

	अगर ((status = card_send_command(ioaddr, name, Command0, st)))
		वापस status;
	PID[0] = st[1] << 8 | st[2];

	अगर ((status = card_send_command(ioaddr, name, Command1, st)))
		वापस status;
	PID[1] = st[1] << 8 | st[2];

	अगर ((status = card_send_command(ioaddr, name, Command2, st)))
		वापस status;
	PID[2] = st[1] << 8 | st[2];

	अगर ((status = card_send_command(ioaddr, name, Command3, st)))
		वापस status;
	PID[3] = st[1] << 8 | st[2];

	वापस sb1000_end_get_set_command(ioaddr, name);
पूर्ण

/* set SB1000 PIDs */
अटल पूर्णांक
sb1000_set_PIDs(स्थिर पूर्णांक ioaddr[], स्थिर अक्षर* name, स्थिर लघु PID[])
अणु
	अटल स्थिर अचिन्हित अक्षर Command4[6] = अणु0x80, 0x2e, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अचिन्हित अक्षर st[7];
	लघु p;
	पूर्णांक status;
	अचिन्हित अक्षर Command0[6] = अणु0x80, 0x31, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अचिन्हित अक्षर Command1[6] = अणु0x80, 0x32, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अचिन्हित अक्षर Command2[6] = अणु0x80, 0x33, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अचिन्हित अक्षर Command3[6] = अणु0x80, 0x34, 0x00, 0x00, 0x00, 0x00पूर्ण;

	udelay(1000);
	अगर ((status = sb1000_start_get_set_command(ioaddr, name)))
		वापस status;

	p = PID[0];
	Command0[3] = p & 0xff;
	p >>= 8;
	Command0[2] = p & 0xff;
	अगर ((status = card_send_command(ioaddr, name, Command0, st)))
		वापस status;

	p = PID[1];
	Command1[3] = p & 0xff;
	p >>= 8;
	Command1[2] = p & 0xff;
	अगर ((status = card_send_command(ioaddr, name, Command1, st)))
		वापस status;

	p = PID[2];
	Command2[3] = p & 0xff;
	p >>= 8;
	Command2[2] = p & 0xff;
	अगर ((status = card_send_command(ioaddr, name, Command2, st)))
		वापस status;

	p = PID[3];
	Command3[3] = p & 0xff;
	p >>= 8;
	Command3[2] = p & 0xff;
	अगर ((status = card_send_command(ioaddr, name, Command3, st)))
		वापस status;

	अगर ((status = card_send_command(ioaddr, name, Command4, st)))
		वापस status;
	वापस sb1000_end_get_set_command(ioaddr, name);
पूर्ण


अटल व्योम
sb1000_prपूर्णांक_status_buffer(स्थिर अक्षर* name, अचिन्हित अक्षर st[],
	अचिन्हित अक्षर buffer[], पूर्णांक size)
अणु
	पूर्णांक i, j, k;

	prपूर्णांकk(KERN_DEBUG "%s: status: %02x %02x\n", name, st[0], st[1]);
	अगर (buffer[24] == 0x08 && buffer[25] == 0x00 && buffer[26] == 0x45) अणु
		prपूर्णांकk(KERN_DEBUG "%s: length: %d protocol: %d from: %d.%d.%d.%d:%d "
			"to %d.%d.%d.%d:%d\n", name, buffer[28] << 8 | buffer[29],
			buffer[35], buffer[38], buffer[39], buffer[40], buffer[41],
            buffer[46] << 8 | buffer[47],
			buffer[42], buffer[43], buffer[44], buffer[45],
            buffer[48] << 8 | buffer[49]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0, k = 0; i < (size + 7) / 8; i++) अणु
			prपूर्णांकk(KERN_DEBUG "%s: %s", name, i ? "       " : "buffer:");
			क्रम (j = 0; j < 8 && k < size; j++, k++)
				prपूर्णांकk(" %02x", buffer[k]);
			prपूर्णांकk("\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * SB1000 commands क्रम frame rx पूर्णांकerrupt
 */
/* receive a single frame and assemble datagram
 * (this is the heart of the पूर्णांकerrupt routine)
 */
अटल पूर्णांक
sb1000_rx(काष्ठा net_device *dev)
अणु

#घोषणा FRAMESIZE 184
	अचिन्हित अक्षर st[2], buffer[FRAMESIZE], session_id, frame_id;
	लघु dlen;
	पूर्णांक ioaddr, ns;
	अचिन्हित पूर्णांक skbsize;
	काष्ठा sk_buff *skb;
	काष्ठा sb1000_निजी *lp = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;

	/* SB1000 frame स्थिरants */
	स्थिर पूर्णांक FrameSize = FRAMESIZE;
	स्थिर पूर्णांक NewDatagramHeaderSkip = 8;
	स्थिर पूर्णांक NewDatagramHeaderSize = NewDatagramHeaderSkip + 18;
	स्थिर पूर्णांक NewDatagramDataSize = FrameSize - NewDatagramHeaderSize;
	स्थिर पूर्णांक ContDatagramHeaderSkip = 7;
	स्थिर पूर्णांक ContDatagramHeaderSize = ContDatagramHeaderSkip + 1;
	स्थिर पूर्णांक ContDatagramDataSize = FrameSize - ContDatagramHeaderSize;
	स्थिर पूर्णांक TrailerSize = 4;

	ioaddr = dev->base_addr;

	insw(ioaddr, (अचिन्हित लघु*) st, 1);
#अगर_घोषित XXXDEBUG
prपूर्णांकk("cm0: received: %02x %02x\n", st[0], st[1]);
#पूर्ण_अगर /* XXXDEBUG */
	lp->rx_frames++;

	/* decide अगर it is a good or bad frame */
	क्रम (ns = 0; ns < NPIDS; ns++) अणु
		session_id = lp->rx_session_id[ns];
		frame_id = lp->rx_frame_id[ns];
		अगर (st[0] == session_id) अणु
			अगर (st[1] == frame_id || (!frame_id && (st[1] & 0xf0) == 0x30)) अणु
				जाओ good_frame;
			पूर्ण अन्यथा अगर ((st[1] & 0xf0) == 0x30 && (st[0] & 0x40)) अणु
				जाओ skipped_frame;
			पूर्ण अन्यथा अणु
				जाओ bad_frame;
			पूर्ण
		पूर्ण अन्यथा अगर (st[0] == (session_id | 0x40)) अणु
			अगर ((st[1] & 0xf0) == 0x30) अणु
				जाओ skipped_frame;
			पूर्ण अन्यथा अणु
				जाओ bad_frame;
			पूर्ण
		पूर्ण
	पूर्ण
	जाओ bad_frame;

skipped_frame:
	stats->rx_frame_errors++;
	skb = lp->rx_skb[ns];
	अगर (sb1000_debug > 1)
		prपूर्णांकk(KERN_WARNING "%s: missing frame(s): got %02x %02x "
			"expecting %02x %02x\n", dev->name, st[0], st[1],
			skb ? session_id : session_id | 0x40, frame_id);
	अगर (skb) अणु
		dev_kमुक्त_skb(skb);
		skb = शून्य;
	पूर्ण

good_frame:
	lp->rx_frame_id[ns] = 0x30 | ((st[1] + 1) & 0x0f);
	/* new datagram */
	अगर (st[0] & 0x40) अणु
		/* get data length */
		insw(ioaddr, buffer, NewDatagramHeaderSize / 2);
#अगर_घोषित XXXDEBUG
prपूर्णांकk("cm0: IP identification: %02x%02x  fragment offset: %02x%02x\n", buffer[30], buffer[31], buffer[32], buffer[33]);
#पूर्ण_अगर /* XXXDEBUG */
		अगर (buffer[0] != NewDatagramHeaderSkip) अणु
			अगर (sb1000_debug > 1)
				prपूर्णांकk(KERN_WARNING "%s: new datagram header skip error: "
					"got %02x expecting %02x\n", dev->name, buffer[0],
					NewDatagramHeaderSkip);
			stats->rx_length_errors++;
			insw(ioaddr, buffer, NewDatagramDataSize / 2);
			जाओ bad_frame_next;
		पूर्ण
		dlen = ((buffer[NewDatagramHeaderSkip + 3] & 0x0f) << 8 |
			buffer[NewDatagramHeaderSkip + 4]) - 17;
		अगर (dlen > SB1000_MRU) अणु
			अगर (sb1000_debug > 1)
				prपूर्णांकk(KERN_WARNING "%s: datagram length (%d) greater "
					"than MRU (%d)\n", dev->name, dlen, SB1000_MRU);
			stats->rx_length_errors++;
			insw(ioaddr, buffer, NewDatagramDataSize / 2);
			जाओ bad_frame_next;
		पूर्ण
		lp->rx_dlen[ns] = dlen;
		/* compute size to allocate क्रम datagram */
		skbsize = dlen + FrameSize;
		अगर ((skb = alloc_skb(skbsize, GFP_ATOMIC)) == शून्य) अणु
			अगर (sb1000_debug > 1)
				prपूर्णांकk(KERN_WARNING "%s: can't allocate %d bytes long "
					"skbuff\n", dev->name, skbsize);
			stats->rx_dropped++;
			insw(ioaddr, buffer, NewDatagramDataSize / 2);
			जाओ dropped_frame;
		पूर्ण
		skb->dev = dev;
		skb_reset_mac_header(skb);
		skb->protocol = (अचिन्हित लघु) buffer[NewDatagramHeaderSkip + 16];
		insw(ioaddr, skb_put(skb, NewDatagramDataSize),
			NewDatagramDataSize / 2);
		lp->rx_skb[ns] = skb;
	पूर्ण अन्यथा अणु
		/* continuation of previous datagram */
		insw(ioaddr, buffer, ContDatagramHeaderSize / 2);
		अगर (buffer[0] != ContDatagramHeaderSkip) अणु
			अगर (sb1000_debug > 1)
				prपूर्णांकk(KERN_WARNING "%s: cont datagram header skip error: "
					"got %02x expecting %02x\n", dev->name, buffer[0],
					ContDatagramHeaderSkip);
			stats->rx_length_errors++;
			insw(ioaddr, buffer, ContDatagramDataSize / 2);
			जाओ bad_frame_next;
		पूर्ण
		skb = lp->rx_skb[ns];
		insw(ioaddr, skb_put(skb, ContDatagramDataSize),
			ContDatagramDataSize / 2);
		dlen = lp->rx_dlen[ns];
	पूर्ण
	अगर (skb->len < dlen + TrailerSize) अणु
		lp->rx_session_id[ns] &= ~0x40;
		वापस 0;
	पूर्ण

	/* datagram completed: send to upper level */
	skb_trim(skb, dlen);
	netअगर_rx(skb);
	stats->rx_bytes+=dlen;
	stats->rx_packets++;
	lp->rx_skb[ns] = शून्य;
	lp->rx_session_id[ns] |= 0x40;
	वापस 0;

bad_frame:
	insw(ioaddr, buffer, FrameSize / 2);
	अगर (sb1000_debug > 1)
		prपूर्णांकk(KERN_WARNING "%s: frame error: got %02x %02x\n",
			dev->name, st[0], st[1]);
	stats->rx_frame_errors++;
bad_frame_next:
	अगर (sb1000_debug > 2)
		sb1000_prपूर्णांक_status_buffer(dev->name, st, buffer, FrameSize);
dropped_frame:
	stats->rx_errors++;
	अगर (ns < NPIDS) अणु
		अगर ((skb = lp->rx_skb[ns])) अणु
			dev_kमुक्त_skb(skb);
			lp->rx_skb[ns] = शून्य;
		पूर्ण
		lp->rx_session_id[ns] |= 0x40;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम
sb1000_error_dpc(काष्ठा net_device *dev)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x26, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अक्षर *name;
	अचिन्हित अक्षर st[5];
	पूर्णांक ioaddr[2];
	काष्ठा sb1000_निजी *lp = netdev_priv(dev);
	स्थिर पूर्णांक ErrorDpcCounterInitialize = 200;

	ioaddr[0] = dev->base_addr;
	/* mem_start holds the second I/O address */
	ioaddr[1] = dev->mem_start;
	name = dev->name;

	sb1000_रुको_क्रम_पढ़ोy_clear(ioaddr, name);
	sb1000_send_command(ioaddr, name, Command0);
	sb1000_रुको_क्रम_पढ़ोy(ioaddr, name);
	sb1000_पढ़ो_status(ioaddr, st);
	अगर (st[1] & 0x10)
		lp->rx_error_dpc_count = ErrorDpcCounterInitialize;
पूर्ण


/*
 * Linux पूर्णांकerface functions
 */
अटल पूर्णांक
sb1000_खोलो(काष्ठा net_device *dev)
अणु
	अक्षर *name;
	पूर्णांक ioaddr[2], status;
	काष्ठा sb1000_निजी *lp = netdev_priv(dev);
	स्थिर अचिन्हित लघु FirmwareVersion[] = अणु0x01, 0x01पूर्ण;

	ioaddr[0] = dev->base_addr;
	/* mem_start holds the second I/O address */
	ioaddr[1] = dev->mem_start;
	name = dev->name;

	/* initialize sb1000 */
	अगर ((status = sb1000_reset(ioaddr, name)))
		वापस status;
	ssleep(1);
	अगर ((status = sb1000_check_CRC(ioaddr, name)))
		वापस status;

	/* initialize निजी data beक्रमe board can catch पूर्णांकerrupts */
	lp->rx_skb[0] = शून्य;
	lp->rx_skb[1] = शून्य;
	lp->rx_skb[2] = शून्य;
	lp->rx_skb[3] = शून्य;
	lp->rx_dlen[0] = 0;
	lp->rx_dlen[1] = 0;
	lp->rx_dlen[2] = 0;
	lp->rx_dlen[3] = 0;
	lp->rx_frames = 0;
	lp->rx_error_count = 0;
	lp->rx_error_dpc_count = 0;
	lp->rx_session_id[0] = 0x50;
	lp->rx_session_id[1] = 0x48;
	lp->rx_session_id[2] = 0x44;
	lp->rx_session_id[3] = 0x42;
	lp->rx_frame_id[0] = 0;
	lp->rx_frame_id[1] = 0;
	lp->rx_frame_id[2] = 0;
	lp->rx_frame_id[3] = 0;
	अगर (request_irq(dev->irq, sb1000_पूर्णांकerrupt, 0, "sb1000", dev)) अणु
		वापस -EAGAIN;
	पूर्ण

	अगर (sb1000_debug > 2)
		prपूर्णांकk(KERN_DEBUG "%s: Opening, IRQ %d\n", name, dev->irq);

	/* Activate board and check firmware version */
	udelay(1000);
	अगर ((status = sb1000_activate(ioaddr, name)))
		वापस status;
	udelay(0);
	अगर ((status = sb1000_get_firmware_version(ioaddr, name, version, 0)))
		वापस status;
	अगर (version[0] != FirmwareVersion[0] || version[1] != FirmwareVersion[1])
		prपूर्णांकk(KERN_WARNING "%s: found firmware version %x.%02x "
			"(should be %x.%02x)\n", name, version[0], version[1],
			FirmwareVersion[0], FirmwareVersion[1]);


	netअगर_start_queue(dev);
	वापस 0;					/* Always succeed */
पूर्ण

अटल पूर्णांक sb1000_dev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	अक्षर* name;
	अचिन्हित अक्षर version[2];
	लघु PID[4];
	पूर्णांक ioaddr[2], status, frequency;
	अचिन्हित पूर्णांक stats[5];
	काष्ठा sb1000_निजी *lp = netdev_priv(dev);

	अगर (!(dev && dev->flags & IFF_UP))
		वापस -ENODEV;

	ioaddr[0] = dev->base_addr;
	/* mem_start holds the second I/O address */
	ioaddr[1] = dev->mem_start;
	name = dev->name;

	चयन (cmd) अणु
	हाल SIOCGCMSTATS:		/* get statistics */
		stats[0] = dev->stats.rx_bytes;
		stats[1] = lp->rx_frames;
		stats[2] = dev->stats.rx_packets;
		stats[3] = dev->stats.rx_errors;
		stats[4] = dev->stats.rx_dropped;
		अगर(copy_to_user(अगरr->अगरr_data, stats, माप(stats)))
			वापस -EFAULT;
		status = 0;
		अवरोध;

	हाल SIOCGCMFIRMWARE:		/* get firmware version */
		अगर ((status = sb1000_get_firmware_version(ioaddr, name, version, 1)))
			वापस status;
		अगर(copy_to_user(अगरr->अगरr_data, version, माप(version)))
			वापस -EFAULT;
		अवरोध;

	हाल SIOCGCMFREQUENCY:		/* get frequency */
		अगर ((status = sb1000_get_frequency(ioaddr, name, &frequency)))
			वापस status;
		अगर(put_user(frequency, (पूर्णांक __user *) अगरr->अगरr_data))
			वापस -EFAULT;
		अवरोध;

	हाल SIOCSCMFREQUENCY:		/* set frequency */
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर(get_user(frequency, (पूर्णांक __user *) अगरr->अगरr_data))
			वापस -EFAULT;
		अगर ((status = sb1000_set_frequency(ioaddr, name, frequency)))
			वापस status;
		अवरोध;

	हाल SIOCGCMPIDS:			/* get PIDs */
		अगर ((status = sb1000_get_PIDs(ioaddr, name, PID)))
			वापस status;
		अगर(copy_to_user(अगरr->अगरr_data, PID, माप(PID)))
			वापस -EFAULT;
		अवरोध;

	हाल SIOCSCMPIDS:			/* set PIDs */
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर(copy_from_user(PID, अगरr->अगरr_data, माप(PID)))
			वापस -EFAULT;
		अगर ((status = sb1000_set_PIDs(ioaddr, name, PID)))
			वापस status;
		/* set session_id, frame_id and pkt_type too */
		lp->rx_session_id[0] = 0x50 | (PID[0] & 0x0f);
		lp->rx_session_id[1] = 0x48;
		lp->rx_session_id[2] = 0x44;
		lp->rx_session_id[3] = 0x42;
		lp->rx_frame_id[0] = 0;
		lp->rx_frame_id[1] = 0;
		lp->rx_frame_id[2] = 0;
		lp->rx_frame_id[3] = 0;
		अवरोध;

	शेष:
		status = -EINVAL;
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

/* transmit function: करो nothing since SB1000 can't send anything out */
अटल netdev_tx_t
sb1000_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	prपूर्णांकk(KERN_WARNING "%s: trying to transmit!!!\n", dev->name);
	/* sb1000 can't xmit datagrams */
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/* SB1000 पूर्णांकerrupt handler. */
अटल irqवापस_t sb1000_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अटल स्थिर अचिन्हित अक्षर Command0[6] = अणु0x80, 0x2c, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर अचिन्हित अक्षर Command1[6] = अणु0x80, 0x2e, 0x00, 0x00, 0x00, 0x00पूर्ण;

	अक्षर *name;
	अचिन्हित अक्षर st;
	पूर्णांक ioaddr[2];
	काष्ठा net_device *dev = dev_id;
	काष्ठा sb1000_निजी *lp = netdev_priv(dev);

	स्थिर पूर्णांक MaxRxErrorCount = 6;

	ioaddr[0] = dev->base_addr;
	/* mem_start holds the second I/O address */
	ioaddr[1] = dev->mem_start;
	name = dev->name;

	/* is it a good पूर्णांकerrupt? */
	st = inb(ioaddr[1] + 6);
	अगर (!(st & 0x08 && st & 0x20)) अणु
		वापस IRQ_NONE;
	पूर्ण

	अगर (sb1000_debug > 3)
		prपूर्णांकk(KERN_DEBUG "%s: entering interrupt\n", dev->name);

	st = inb(ioaddr[0] + 7);
	अगर (sb1000_rx(dev))
		lp->rx_error_count++;
#अगर_घोषित SB1000_DELAY
	udelay(SB1000_DELAY);
#पूर्ण_अगर /* SB1000_DELAY */
	sb1000_issue_पढ़ो_command(ioaddr, name);
	अगर (st & 0x01) अणु
		sb1000_error_dpc(dev);
		sb1000_issue_पढ़ो_command(ioaddr, name);
	पूर्ण
	अगर (lp->rx_error_dpc_count && !(--lp->rx_error_dpc_count)) अणु
		sb1000_रुको_क्रम_पढ़ोy_clear(ioaddr, name);
		sb1000_send_command(ioaddr, name, Command0);
		sb1000_रुको_क्रम_पढ़ोy(ioaddr, name);
		sb1000_issue_पढ़ो_command(ioaddr, name);
	पूर्ण
	अगर (lp->rx_error_count >= MaxRxErrorCount) अणु
		sb1000_रुको_क्रम_पढ़ोy_clear(ioaddr, name);
		sb1000_send_command(ioaddr, name, Command1);
		sb1000_रुको_क्रम_पढ़ोy(ioaddr, name);
		sb1000_issue_पढ़ो_command(ioaddr, name);
		lp->rx_error_count = 0;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sb1000_बंद(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	पूर्णांक ioaddr[2];
	काष्ठा sb1000_निजी *lp = netdev_priv(dev);

	अगर (sb1000_debug > 2)
		prपूर्णांकk(KERN_DEBUG "%s: Shutting down sb1000.\n", dev->name);

	netअगर_stop_queue(dev);

	ioaddr[0] = dev->base_addr;
	/* mem_start holds the second I/O address */
	ioaddr[1] = dev->mem_start;

	मुक्त_irq(dev->irq, dev);
	/* If we करोn't do this, we can't re-insmod it later. */
	release_region(ioaddr[1], SB1000_IO_EXTENT);
	release_region(ioaddr[0], SB1000_IO_EXTENT);

	/* मुक्त rx_skb's अगर needed */
	क्रम (i=0; i<4; i++) अणु
		अगर (lp->rx_skb[i]) अणु
			dev_kमुक्त_skb(lp->rx_skb[i]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

MODULE_AUTHOR("Franco Venturi <fventuri@mediaone.net>");
MODULE_DESCRIPTION("General Instruments SB1000 driver");
MODULE_LICENSE("GPL");

module_pnp_driver(sb1000_driver);
