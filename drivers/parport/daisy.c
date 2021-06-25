<शैली गुरु>
/*
 * IEEE 1284.3 Parallel port daisy chain and multiplexor code
 * 
 * Copyright (C) 1999, 2000  Tim Waugh <tim@cyberelk.demon.co.uk>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * ??-12-1998: Initial implementation.
 * 31-01-1999: Make port-cloning transparent.
 * 13-02-1999: Move DeviceID technique from parport_probe.
 * 13-03-1999: Get DeviceID from non-IEEE 1284.3 devices too.
 * 22-02-2000: Count devices that are actually detected.
 *
 * Any part of this program may be used in करोcuments licensed under
 * the GNU Free Documentation License, Version 1.1 or any later version
 * published by the Free Software Foundation.
 */

#समावेश <linux/module.h>
#समावेश <linux/parport.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/current.h>
#समावेश <linux/uaccess.h>

#अघोषित DEBUG

अटल काष्ठा daisydev अणु
	काष्ठा daisydev *next;
	काष्ठा parport *port;
	पूर्णांक daisy;
	पूर्णांक devnum;
पूर्ण *topology = शून्य;
अटल DEFINE_SPINLOCK(topology_lock);

अटल पूर्णांक numdevs;
अटल bool daisy_init_करोne;

/* Forward-declaration of lower-level functions. */
अटल पूर्णांक mux_present(काष्ठा parport *port);
अटल पूर्णांक num_mux_ports(काष्ठा parport *port);
अटल पूर्णांक select_port(काष्ठा parport *port);
अटल पूर्णांक assign_addrs(काष्ठा parport *port);

/* Add a device to the discovered topology. */
अटल व्योम add_dev(पूर्णांक devnum, काष्ठा parport *port, पूर्णांक daisy)
अणु
	काष्ठा daisydev *newdev, **p;
	newdev = kदो_स्मृति(माप(काष्ठा daisydev), GFP_KERNEL);
	अगर (newdev) अणु
		newdev->port = port;
		newdev->daisy = daisy;
		newdev->devnum = devnum;
		spin_lock(&topology_lock);
		क्रम (p = &topology; *p && (*p)->devnum<devnum; p = &(*p)->next)
			;
		newdev->next = *p;
		*p = newdev;
		spin_unlock(&topology_lock);
	पूर्ण
पूर्ण

/* Clone a parport (actually, make an alias). */
अटल काष्ठा parport *clone_parport(काष्ठा parport *real, पूर्णांक muxport)
अणु
	काष्ठा parport *extra = parport_रेजिस्टर_port(real->base,
						       real->irq,
						       real->dma,
						       real->ops);
	अगर (extra) अणु
		extra->portnum = real->portnum;
		extra->physport = real;
		extra->muxport = muxport;
		real->slaves[muxport-1] = extra;
	पूर्ण

	वापस extra;
पूर्ण

अटल पूर्णांक daisy_drv_probe(काष्ठा pardevice *par_dev)
अणु
	काष्ठा device_driver *drv = par_dev->dev.driver;

	अगर (म_भेद(drv->name, "daisy_drv"))
		वापस -ENODEV;
	अगर (म_भेद(par_dev->name, daisy_dev_name))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा parport_driver daisy_driver = अणु
	.name = "daisy_drv",
	.probe = daisy_drv_probe,
	.devmodel = true,
पूर्ण;

/* Discover the IEEE1284.3 topology on a port -- muxes and daisy chains.
 * Return value is number of devices actually detected. */
पूर्णांक parport_daisy_init(काष्ठा parport *port)
अणु
	पूर्णांक detected = 0;
	अक्षर *deviceid;
	अटल स्थिर अक्षर *th[] = अणु /*0*/"th", "st", "nd", "rd", "th" पूर्ण;
	पूर्णांक num_ports;
	पूर्णांक i;
	पूर्णांक last_try = 0;

	अगर (!daisy_init_करोne) अणु
		/*
		 * flag should be marked true first as
		 * parport_रेजिस्टर_driver() might try to load the low
		 * level driver which will lead to announcing new ports
		 * and which will again come back here at
		 * parport_daisy_init()
		 */
		daisy_init_करोne = true;
		i = parport_रेजिस्टर_driver(&daisy_driver);
		अगर (i) अणु
			pr_err("daisy registration failed\n");
			daisy_init_करोne = false;
			वापस i;
		पूर्ण
	पूर्ण

again:
	/* Because this is called beक्रमe any other devices exist,
	 * we करोn't have to claim exclusive access.  */

	/* If mux present on normal port, need to create new
	 * parports क्रम each extra port. */
	अगर (port->muxport < 0 && mux_present(port) &&
	    /* करोn't be fooled: a mux must have 2 or 4 ports. */
	    ((num_ports = num_mux_ports(port)) == 2 || num_ports == 4)) अणु
		/* Leave original as port zero. */
		port->muxport = 0;
		pr_info("%s: 1st (default) port of %d-way multiplexor\n",
			port->name, num_ports);
		क्रम (i = 1; i < num_ports; i++) अणु
			/* Clone the port. */
			काष्ठा parport *extra = clone_parport(port, i);
			अगर (!extra) अणु
				अगर (संकेत_pending(current))
					अवरोध;

				schedule();
				जारी;
			पूर्ण

			pr_info("%s: %d%s port of %d-way multiplexor on %s\n",
				extra->name, i + 1, th[i + 1], num_ports,
				port->name);

			/* Analyse that port too.  We won't recurse
			   क्रमever because of the 'port->muxport < 0'
			   test above. */
			parport_daisy_init(extra);
		पूर्ण
	पूर्ण

	अगर (port->muxport >= 0)
		select_port(port);

	parport_daisy_deselect_all(port);
	detected += assign_addrs(port);

	/* Count the potential legacy device at the end. */
	add_dev(numdevs++, port, -1);

	/* Find out the legacy device's IEEE 1284 device ID. */
	deviceid = kदो_स्मृति(1024, GFP_KERNEL);
	अगर (deviceid) अणु
		अगर (parport_device_id(numdevs - 1, deviceid, 1024) > 2)
			detected++;

		kमुक्त(deviceid);
	पूर्ण

	अगर (!detected && !last_try) अणु
		/* No devices were detected.  Perhaps they are in some
                   funny state; let's try to reset them and see अगर
                   they wake up. */
		parport_daisy_fini(port);
		parport_ग_लिखो_control(port, PARPORT_CONTROL_SELECT);
		udelay(50);
		parport_ग_लिखो_control(port,
				       PARPORT_CONTROL_SELECT |
				       PARPORT_CONTROL_INIT);
		udelay(50);
		last_try = 1;
		जाओ again;
	पूर्ण

	वापस detected;
पूर्ण

/* Forget about devices on a physical port. */
व्योम parport_daisy_fini(काष्ठा parport *port)
अणु
	काष्ठा daisydev **p;

	spin_lock(&topology_lock);
	p = &topology;
	जबतक (*p) अणु
		काष्ठा daisydev *dev = *p;
		अगर (dev->port != port) अणु
			p = &dev->next;
			जारी;
		पूर्ण
		*p = dev->next;
		kमुक्त(dev);
	पूर्ण

	/* Gaps in the numbering could be handled better.  How should
           someone क्रमागतerate through all IEEE1284.3 devices in the
           topology?. */
	अगर (!topology) numdevs = 0;
	spin_unlock(&topology_lock);
	वापस;
पूर्ण

/**
 *	parport_खोलो - find a device by canonical device number
 *	@devnum: canonical device number
 *	@name: name to associate with the device
 *
 *	This function is similar to parport_रेजिस्टर_device(), except
 *	that it locates a device by its number rather than by the port
 *	it is attached to.
 *
 *	All parameters except क्रम @devnum are the same as क्रम
 *	parport_रेजिस्टर_device().  The वापस value is the same as
 *	क्रम parport_रेजिस्टर_device().
 **/

काष्ठा pardevice *parport_खोलो(पूर्णांक devnum, स्थिर अक्षर *name)
अणु
	काष्ठा daisydev *p = topology;
	काष्ठा pardev_cb par_cb;
	काष्ठा parport *port;
	काष्ठा pardevice *dev;
	पूर्णांक daisy;

	स_रखो(&par_cb, 0, माप(par_cb));
	spin_lock(&topology_lock);
	जबतक (p && p->devnum != devnum)
		p = p->next;

	अगर (!p) अणु
		spin_unlock(&topology_lock);
		वापस शून्य;
	पूर्ण

	daisy = p->daisy;
	port = parport_get_port(p->port);
	spin_unlock(&topology_lock);

	dev = parport_रेजिस्टर_dev_model(port, name, &par_cb, devnum);
	parport_put_port(port);
	अगर (!dev)
		वापस शून्य;

	dev->daisy = daisy;

	/* Check that there really is a device to select. */
	अगर (daisy >= 0) अणु
		पूर्णांक selected;
		parport_claim_or_block(dev);
		selected = port->daisy;
		parport_release(dev);

		अगर (selected != daisy) अणु
			/* No corresponding device. */
			parport_unरेजिस्टर_device(dev);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस dev;
पूर्ण

/**
 *	parport_बंद - बंद a device खोलोed with parport_खोलो()
 *	@dev: device to बंद
 *
 *	This is to parport_खोलो() as parport_unरेजिस्टर_device() is to
 *	parport_रेजिस्टर_device().
 **/

व्योम parport_बंद(काष्ठा pardevice *dev)
अणु
	parport_unरेजिस्टर_device(dev);
पूर्ण

/* Send a daisy-chain-style CPP command packet. */
अटल पूर्णांक cpp_daisy(काष्ठा parport *port, पूर्णांक cmd)
अणु
	अचिन्हित अक्षर s;

	parport_data_क्रमward(port);
	parport_ग_लिखो_data(port, 0xaa); udelay(2);
	parport_ग_लिखो_data(port, 0x55); udelay(2);
	parport_ग_लिखो_data(port, 0x00); udelay(2);
	parport_ग_लिखो_data(port, 0xff); udelay(2);
	s = parport_पढ़ो_status(port) & (PARPORT_STATUS_BUSY
					  | PARPORT_STATUS_PAPEROUT
					  | PARPORT_STATUS_SELECT
					  | PARPORT_STATUS_ERROR);
	अगर (s != (PARPORT_STATUS_BUSY
		  | PARPORT_STATUS_PAPEROUT
		  | PARPORT_STATUS_SELECT
		  | PARPORT_STATUS_ERROR)) अणु
		pr_debug("%s: cpp_daisy: aa5500ff(%02x)\n", port->name, s);
		वापस -ENXIO;
	पूर्ण

	parport_ग_लिखो_data(port, 0x87); udelay(2);
	s = parport_पढ़ो_status(port) & (PARPORT_STATUS_BUSY
					  | PARPORT_STATUS_PAPEROUT
					  | PARPORT_STATUS_SELECT
					  | PARPORT_STATUS_ERROR);
	अगर (s != (PARPORT_STATUS_SELECT | PARPORT_STATUS_ERROR)) अणु
		pr_debug("%s: cpp_daisy: aa5500ff87(%02x)\n", port->name, s);
		वापस -ENXIO;
	पूर्ण

	parport_ग_लिखो_data(port, 0x78); udelay(2);
	parport_ग_लिखो_data(port, cmd); udelay(2);
	parport_frob_control(port,
			      PARPORT_CONTROL_STROBE,
			      PARPORT_CONTROL_STROBE);
	udelay(1);
	s = parport_पढ़ो_status(port);
	parport_frob_control(port, PARPORT_CONTROL_STROBE, 0);
	udelay(1);
	parport_ग_लिखो_data(port, 0xff); udelay(2);

	वापस s;
पूर्ण

/* Send a mux-style CPP command packet. */
अटल पूर्णांक cpp_mux(काष्ठा parport *port, पूर्णांक cmd)
अणु
	अचिन्हित अक्षर s;
	पूर्णांक rc;

	parport_data_क्रमward(port);
	parport_ग_लिखो_data(port, 0xaa); udelay(2);
	parport_ग_लिखो_data(port, 0x55); udelay(2);
	parport_ग_लिखो_data(port, 0xf0); udelay(2);
	parport_ग_लिखो_data(port, 0x0f); udelay(2);
	parport_ग_लिखो_data(port, 0x52); udelay(2);
	parport_ग_लिखो_data(port, 0xad); udelay(2);
	parport_ग_लिखो_data(port, cmd); udelay(2);

	s = parport_पढ़ो_status(port);
	अगर (!(s & PARPORT_STATUS_ACK)) अणु
		pr_debug("%s: cpp_mux: aa55f00f52ad%02x(%02x)\n",
			 port->name, cmd, s);
		वापस -EIO;
	पूर्ण

	rc = (((s & PARPORT_STATUS_SELECT   ? 1 : 0) << 0) |
	      ((s & PARPORT_STATUS_PAPEROUT ? 1 : 0) << 1) |
	      ((s & PARPORT_STATUS_BUSY     ? 0 : 1) << 2) |
	      ((s & PARPORT_STATUS_ERROR    ? 0 : 1) << 3));

	वापस rc;
पूर्ण

व्योम parport_daisy_deselect_all(काष्ठा parport *port)
अणु
	cpp_daisy(port, 0x30);
पूर्ण

पूर्णांक parport_daisy_select(काष्ठा parport *port, पूर्णांक daisy, पूर्णांक mode)
अणु
	चयन (mode)
	अणु
		// For these modes we should चयन to EPP mode:
		हाल IEEE1284_MODE_EPP:
		हाल IEEE1284_MODE_EPPSL:
		हाल IEEE1284_MODE_EPPSWE:
			वापस !(cpp_daisy(port, 0x20 + daisy) &
				 PARPORT_STATUS_ERROR);

		// For these modes we should चयन to ECP mode:
		हाल IEEE1284_MODE_ECP:
		हाल IEEE1284_MODE_ECPRLE:
		हाल IEEE1284_MODE_ECPSWE: 
			वापस !(cpp_daisy(port, 0xd0 + daisy) &
				 PARPORT_STATUS_ERROR);

		// Nothing was told क्रम BECP in Daisy chain specअगरication.
		// May be it's wise to use ECP?
		हाल IEEE1284_MODE_BECP:
		// Others use compat mode
		हाल IEEE1284_MODE_NIBBLE:
		हाल IEEE1284_MODE_BYTE:
		हाल IEEE1284_MODE_COMPAT:
		शेष:
			वापस !(cpp_daisy(port, 0xe0 + daisy) &
				 PARPORT_STATUS_ERROR);
	पूर्ण
पूर्ण

अटल पूर्णांक mux_present(काष्ठा parport *port)
अणु
	वापस cpp_mux(port, 0x51) == 3;
पूर्ण

अटल पूर्णांक num_mux_ports(काष्ठा parport *port)
अणु
	वापस cpp_mux(port, 0x58);
पूर्ण

अटल पूर्णांक select_port(काष्ठा parport *port)
अणु
	पूर्णांक muxport = port->muxport;
	वापस cpp_mux(port, 0x60 + muxport) == muxport;
पूर्ण

अटल पूर्णांक assign_addrs(काष्ठा parport *port)
अणु
	अचिन्हित अक्षर s;
	अचिन्हित अक्षर daisy;
	पूर्णांक thisdev = numdevs;
	पूर्णांक detected;
	अक्षर *deviceid;

	parport_data_क्रमward(port);
	parport_ग_लिखो_data(port, 0xaa); udelay(2);
	parport_ग_लिखो_data(port, 0x55); udelay(2);
	parport_ग_लिखो_data(port, 0x00); udelay(2);
	parport_ग_लिखो_data(port, 0xff); udelay(2);
	s = parport_पढ़ो_status(port) & (PARPORT_STATUS_BUSY
					  | PARPORT_STATUS_PAPEROUT
					  | PARPORT_STATUS_SELECT
					  | PARPORT_STATUS_ERROR);
	अगर (s != (PARPORT_STATUS_BUSY
		  | PARPORT_STATUS_PAPEROUT
		  | PARPORT_STATUS_SELECT
		  | PARPORT_STATUS_ERROR)) अणु
		pr_debug("%s: assign_addrs: aa5500ff(%02x)\n", port->name, s);
		वापस 0;
	पूर्ण

	parport_ग_लिखो_data(port, 0x87); udelay(2);
	s = parport_पढ़ो_status(port) & (PARPORT_STATUS_BUSY
					  | PARPORT_STATUS_PAPEROUT
					  | PARPORT_STATUS_SELECT
					  | PARPORT_STATUS_ERROR);
	अगर (s != (PARPORT_STATUS_SELECT | PARPORT_STATUS_ERROR)) अणु
		pr_debug("%s: assign_addrs: aa5500ff87(%02x)\n", port->name, s);
		वापस 0;
	पूर्ण

	parport_ग_लिखो_data(port, 0x78); udelay(2);
	s = parport_पढ़ो_status(port);

	क्रम (daisy = 0;
	     (s & (PARPORT_STATUS_PAPEROUT|PARPORT_STATUS_SELECT))
		     == (PARPORT_STATUS_PAPEROUT|PARPORT_STATUS_SELECT)
		     && daisy < 4;
	     ++daisy) अणु
		parport_ग_लिखो_data(port, daisy);
		udelay(2);
		parport_frob_control(port,
				      PARPORT_CONTROL_STROBE,
				      PARPORT_CONTROL_STROBE);
		udelay(1);
		parport_frob_control(port, PARPORT_CONTROL_STROBE, 0);
		udelay(1);

		add_dev(numdevs++, port, daisy);

		/* See अगर this device thought it was the last in the
		 * chain. */
		अगर (!(s & PARPORT_STATUS_BUSY))
			अवरोध;

		/* We are seeing pass through status now. We see
		   last_dev from next device or अगर last_dev करोes not
		   work status lines from some non-daisy chain
		   device. */
		s = parport_पढ़ो_status(port);
	पूर्ण

	parport_ग_लिखो_data(port, 0xff); udelay(2);
	detected = numdevs - thisdev;
	pr_debug("%s: Found %d daisy-chained devices\n", port->name, detected);

	/* Ask the new devices to पूर्णांकroduce themselves. */
	deviceid = kदो_स्मृति(1024, GFP_KERNEL);
	अगर (!deviceid) वापस 0;

	क्रम (daisy = 0; thisdev < numdevs; thisdev++, daisy++)
		parport_device_id(thisdev, deviceid, 1024);

	kमुक्त(deviceid);
	वापस detected;
पूर्ण
