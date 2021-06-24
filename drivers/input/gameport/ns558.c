<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 *  Copyright (c) 1999 Brian Gerst
 */

/*
 * NS558 based standard IBM game port driver क्रम Linux
 */

/*
 */

#समावेश <यंत्र/पन.स>

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/gameport.h>
#समावेश <linux/slab.h>
#समावेश <linux/pnp.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Classic gameport (ISA/PnP) driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक ns558_isa_portlist[] = अणु 0x201, 0x200, 0x202, 0x203, 0x204, 0x205, 0x207, 0x209,
				    0x20b, 0x20c, 0x20e, 0x20f, 0x211, 0x219, 0x101, 0 पूर्ण;

काष्ठा ns558 अणु
	पूर्णांक type;
	पूर्णांक io;
	पूर्णांक size;
	काष्ठा pnp_dev *dev;
	काष्ठा gameport *gameport;
	काष्ठा list_head node;
पूर्ण;

अटल LIST_HEAD(ns558_list);

/*
 * ns558_isa_probe() tries to find an isa gameport at the
 * specअगरied address, and also checks क्रम mirrors.
 * A joystick must be attached क्रम this to work.
 */

अटल पूर्णांक ns558_isa_probe(पूर्णांक io)
अणु
	पूर्णांक i, j, b;
	अचिन्हित अक्षर c, u, v;
	काष्ठा ns558 *ns558;
	काष्ठा gameport *port;

/*
 * No one should be using this address.
 */

	अगर (!request_region(io, 1, "ns558-isa"))
		वापस -EBUSY;

/*
 * We must not be able to ग_लिखो arbitrary values to the port.
 * The lower two axis bits must be 1 after a ग_लिखो.
 */

	c = inb(io);
	outb(~c & ~3, io);
	अगर (~(u = v = inb(io)) & 3) अणु
		outb(c, io);
		release_region(io, 1);
		वापस -ENODEV;
	पूर्ण
/*
 * After a trigger, there must be at least some bits changing.
 */

	क्रम (i = 0; i < 1000; i++) v &= inb(io);

	अगर (u == v) अणु
		outb(c, io);
		release_region(io, 1);
		वापस -ENODEV;
	पूर्ण
	msleep(3);
/*
 * After some समय (4ms) the axes shouldn't change anymore.
 */

	u = inb(io);
	क्रम (i = 0; i < 1000; i++)
		अगर ((u ^ inb(io)) & 0xf) अणु
			outb(c, io);
			release_region(io, 1);
			वापस -ENODEV;
		पूर्ण
/*
 * And now find the number of mirrors of the port.
 */

	क्रम (i = 1; i < 5; i++) अणु

		release_region(io & (-1 << (i - 1)), (1 << (i - 1)));

		अगर (!request_region(io & (-1 << i), (1 << i), "ns558-isa"))
			अवरोध;				/* Don't disturb anyone */

		outb(0xff, io & (-1 << i));
		क्रम (j = b = 0; j < 1000; j++)
			अगर (inb(io & (-1 << i)) != inb((io & (-1 << i)) + (1 << i) - 1)) b++;
		msleep(3);

		अगर (b > 300) अणु				/* We allow 30% dअगरference */
			release_region(io & (-1 << i), (1 << i));
			अवरोध;
		पूर्ण
	पूर्ण

	i--;

	अगर (i != 4) अणु
		अगर (!request_region(io & (-1 << i), (1 << i), "ns558-isa"))
			वापस -EBUSY;
	पूर्ण

	ns558 = kzalloc(माप(काष्ठा ns558), GFP_KERNEL);
	port = gameport_allocate_port();
	अगर (!ns558 || !port) अणु
		prपूर्णांकk(KERN_ERR "ns558: Memory allocation failed.\n");
		release_region(io & (-1 << i), (1 << i));
		kमुक्त(ns558);
		gameport_मुक्त_port(port);
		वापस -ENOMEM;
	पूर्ण

	ns558->io = io;
	ns558->size = 1 << i;
	ns558->gameport = port;

	port->io = io;
	gameport_set_name(port, "NS558 ISA Gameport");
	gameport_set_phys(port, "isa%04x/gameport0", io & (-1 << i));

	gameport_रेजिस्टर_port(port);

	list_add(&ns558->node, &ns558_list);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PNP

अटल स्थिर काष्ठा pnp_device_id pnp_devids[] = अणु
	अणु .id = "@P@0001", .driver_data = 0 पूर्ण, /* ALS 100 */
	अणु .id = "@P@0020", .driver_data = 0 पूर्ण, /* ALS 200 */
	अणु .id = "@P@1001", .driver_data = 0 पूर्ण, /* ALS 100+ */
	अणु .id = "@P@2001", .driver_data = 0 पूर्ण, /* ALS 120 */
	अणु .id = "ASB16fd", .driver_data = 0 पूर्ण, /* AdLib NSC16 */
	अणु .id = "AZT3001", .driver_data = 0 पूर्ण, /* AZT1008 */
	अणु .id = "CDC0001", .driver_data = 0 पूर्ण, /* Opl3-SAx */
	अणु .id = "CSC0001", .driver_data = 0 पूर्ण, /* CS4232 */
	अणु .id = "CSC000f", .driver_data = 0 पूर्ण, /* CS4236 */
	अणु .id = "CSC0101", .driver_data = 0 पूर्ण, /* CS4327 */
	अणु .id = "CTL7001", .driver_data = 0 पूर्ण, /* SB16 */
	अणु .id = "CTL7002", .driver_data = 0 पूर्ण, /* AWE64 */
	अणु .id = "CTL7005", .driver_data = 0 पूर्ण, /* Vibra16 */
	अणु .id = "ENS2020", .driver_data = 0 पूर्ण, /* SoundscapeVIVO */
	अणु .id = "ESS0001", .driver_data = 0 पूर्ण, /* ES1869 */
	अणु .id = "ESS0005", .driver_data = 0 पूर्ण, /* ES1878 */
	अणु .id = "ESS6880", .driver_data = 0 पूर्ण, /* ES688 */
	अणु .id = "IBM0012", .driver_data = 0 पूर्ण, /* CS4232 */
	अणु .id = "OPT0001", .driver_data = 0 पूर्ण, /* OPTi Audio16 */
	अणु .id = "YMH0006", .driver_data = 0 पूर्ण, /* Opl3-SA */
	अणु .id = "YMH0022", .driver_data = 0 पूर्ण, /* Opl3-SAx */
	अणु .id = "PNPb02f", .driver_data = 0 पूर्ण, /* Generic */
	अणु .id = "", पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pnp, pnp_devids);

अटल पूर्णांक ns558_pnp_probe(काष्ठा pnp_dev *dev, स्थिर काष्ठा pnp_device_id *did)
अणु
	पूर्णांक ioport, iolen;
	काष्ठा ns558 *ns558;
	काष्ठा gameport *port;

	अगर (!pnp_port_valid(dev, 0)) अणु
		prपूर्णांकk(KERN_WARNING "ns558: No i/o ports on a gameport? Weird\n");
		वापस -ENODEV;
	पूर्ण

	ioport = pnp_port_start(dev, 0);
	iolen = pnp_port_len(dev, 0);

	अगर (!request_region(ioport, iolen, "ns558-pnp"))
		वापस -EBUSY;

	ns558 = kzalloc(माप(काष्ठा ns558), GFP_KERNEL);
	port = gameport_allocate_port();
	अगर (!ns558 || !port) अणु
		prपूर्णांकk(KERN_ERR "ns558: Memory allocation failed\n");
		kमुक्त(ns558);
		gameport_मुक्त_port(port);
		वापस -ENOMEM;
	पूर्ण

	ns558->io = ioport;
	ns558->size = iolen;
	ns558->dev = dev;
	ns558->gameport = port;

	gameport_set_name(port, "NS558 PnP Gameport");
	gameport_set_phys(port, "pnp%s/gameport0", dev_name(&dev->dev));
	port->dev.parent = &dev->dev;
	port->io = ioport;

	gameport_रेजिस्टर_port(port);

	list_add_tail(&ns558->node, &ns558_list);
	वापस 0;
पूर्ण

अटल काष्ठा pnp_driver ns558_pnp_driver = अणु
	.name		= "ns558",
	.id_table	= pnp_devids,
	.probe		= ns558_pnp_probe,
पूर्ण;

#अन्यथा

अटल काष्ठा pnp_driver ns558_pnp_driver;

#पूर्ण_अगर

अटल पूर्णांक __init ns558_init(व्योम)
अणु
	पूर्णांक i = 0;
	पूर्णांक error;

	error = pnp_रेजिस्टर_driver(&ns558_pnp_driver);
	अगर (error && error != -ENODEV)	/* should be ENOSYS really */
		वापस error;

/*
 * Probe ISA ports after PnP, so that PnP ports that are alपढ़ोy
 * enabled get detected as PnP. This may be suboptimal in multi-device
 * configurations, but saves hassle with simple setups.
 */

	जबतक (ns558_isa_portlist[i])
		ns558_isa_probe(ns558_isa_portlist[i++]);

	वापस list_empty(&ns558_list) && error ? -ENODEV : 0;
पूर्ण

अटल व्योम __निकास ns558_निकास(व्योम)
अणु
	काष्ठा ns558 *ns558, *safe;

	list_क्रम_each_entry_safe(ns558, safe, &ns558_list, node) अणु
		gameport_unरेजिस्टर_port(ns558->gameport);
		release_region(ns558->io & ~(ns558->size - 1), ns558->size);
		kमुक्त(ns558);
	पूर्ण

	pnp_unरेजिस्टर_driver(&ns558_pnp_driver);
पूर्ण

module_init(ns558_init);
module_निकास(ns558_निकास);
