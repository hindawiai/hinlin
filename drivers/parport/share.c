<शैली गुरु>
/*
 * Parallel-port resource manager code.
 *
 * Authors: David Campbell <campbell@tirian.che.curtin.edu.au>
 *          Tim Waugh <tim@cyberelk.demon.co.uk>
 *          Jose Renau <renau@acm.org>
 *          Philip Blundell <philb@gnu.org>
 *	    Andrea Arcangeli
 *
 * based on work by Grant Guenther <grant@torque.net>
 *          and Philip Blundell
 *
 * Any part of this program may be used in करोcuments licensed under
 * the GNU Free Documentation License, Version 1.1 or any later version
 * published by the Free Software Foundation.
 */

#अघोषित PARPORT_DEBUG_SHARING		/* undef क्रम production */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/parport.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kmod.h>
#समावेश <linux/device.h>

#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/irq.h>

#अघोषित PARPORT_PARANOID

#घोषणा PARPORT_DEFAULT_TIMESLICE	(HZ/5)

अचिन्हित दीर्घ parport_शेष_बारlice = PARPORT_DEFAULT_TIMESLICE;
पूर्णांक parport_शेष_spपूर्णांकime =  DEFAULT_SPIN_TIME;

अटल LIST_HEAD(portlist);
अटल DEFINE_SPINLOCK(parportlist_lock);

/* list of all allocated ports, sorted by ->number */
अटल LIST_HEAD(all_ports);
अटल DEFINE_SPINLOCK(full_list_lock);

अटल LIST_HEAD(drivers);

अटल DEFINE_MUTEX(registration_lock);

/* What you can करो to a port that's gone away.. */
अटल व्योम dead_ग_लिखो_lines(काष्ठा parport *p, अचिन्हित अक्षर b)अणुपूर्ण
अटल अचिन्हित अक्षर dead_पढ़ो_lines(काष्ठा parport *p) अणु वापस 0; पूर्ण
अटल अचिन्हित अक्षर dead_frob_lines(काष्ठा parport *p, अचिन्हित अक्षर b,
			     अचिन्हित अक्षर c) अणु वापस 0; पूर्ण
अटल व्योम dead_onearg(काष्ठा parport *p)अणुपूर्ण
अटल व्योम dead_initstate(काष्ठा pardevice *d, काष्ठा parport_state *s) अणु पूर्ण
अटल व्योम dead_state(काष्ठा parport *p, काष्ठा parport_state *s) अणु पूर्ण
अटल माप_प्रकार dead_ग_लिखो(काष्ठा parport *p, स्थिर व्योम *b, माप_प्रकार l, पूर्णांक f)
अणु वापस 0; पूर्ण
अटल माप_प्रकार dead_पढ़ो(काष्ठा parport *p, व्योम *b, माप_प्रकार l, पूर्णांक f)
अणु वापस 0; पूर्ण
अटल काष्ठा parport_operations dead_ops = अणु
	.ग_लिखो_data	= dead_ग_लिखो_lines,	/* data */
	.पढ़ो_data	= dead_पढ़ो_lines,

	.ग_लिखो_control	= dead_ग_लिखो_lines,	/* control */
	.पढ़ो_control	= dead_पढ़ो_lines,
	.frob_control	= dead_frob_lines,

	.पढ़ो_status	= dead_पढ़ो_lines,	/* status */

	.enable_irq	= dead_onearg,		/* enable_irq */
	.disable_irq	= dead_onearg,		/* disable_irq */

	.data_क्रमward	= dead_onearg,		/* data_क्रमward */
	.data_reverse	= dead_onearg,		/* data_reverse */

	.init_state	= dead_initstate,	/* init_state */
	.save_state	= dead_state,
	.restore_state	= dead_state,

	.epp_ग_लिखो_data	= dead_ग_लिखो,		/* epp */
	.epp_पढ़ो_data	= dead_पढ़ो,
	.epp_ग_लिखो_addr	= dead_ग_लिखो,
	.epp_पढ़ो_addr	= dead_पढ़ो,

	.ecp_ग_लिखो_data	= dead_ग_लिखो,		/* ecp */
	.ecp_पढ़ो_data	= dead_पढ़ो,
	.ecp_ग_लिखो_addr	= dead_ग_लिखो,

	.compat_ग_लिखो_data	= dead_ग_लिखो,	/* compat */
	.nibble_पढ़ो_data	= dead_पढ़ो,	/* nibble */
	.byte_पढ़ो_data		= dead_पढ़ो,	/* byte */

	.owner		= शून्य,
पूर्ण;

अटल काष्ठा device_type parport_device_type = अणु
	.name = "parport",
पूर्ण;

अटल पूर्णांक is_parport(काष्ठा device *dev)
अणु
	वापस dev->type == &parport_device_type;
पूर्ण

अटल पूर्णांक parport_probe(काष्ठा device *dev)
अणु
	काष्ठा parport_driver *drv;

	अगर (is_parport(dev))
		वापस -ENODEV;

	drv = to_parport_driver(dev->driver);
	अगर (!drv->probe) अणु
		/* अगर driver has not defined a custom probe */
		काष्ठा pardevice *par_dev = to_pardevice(dev);

		अगर (म_भेद(par_dev->name, drv->name))
			वापस -ENODEV;
		वापस 0;
	पूर्ण
	/* अगर driver defined its own probe */
	वापस drv->probe(to_pardevice(dev));
पूर्ण

अटल काष्ठा bus_type parport_bus_type = अणु
	.name = "parport",
	.probe = parport_probe,
पूर्ण;

पूर्णांक parport_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&parport_bus_type);
पूर्ण

व्योम parport_bus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&parport_bus_type);
पूर्ण

/*
 * iterates through all the drivers रेजिस्टरed with the bus and sends the port
 * details to the match_port callback of the driver, so that the driver can
 * know about the new port that just रेजिस्टरed with the bus and decide अगर it
 * wants to use this new port.
 */
अटल पूर्णांक driver_check(काष्ठा device_driver *dev_drv, व्योम *_port)
अणु
	काष्ठा parport *port = _port;
	काष्ठा parport_driver *drv = to_parport_driver(dev_drv);

	अगर (drv->match_port)
		drv->match_port(port);
	वापस 0;
पूर्ण

/* Call attach(port) क्रम each रेजिस्टरed driver. */
अटल व्योम attach_driver_chain(काष्ठा parport *port)
अणु
	/* caller has exclusive registration_lock */
	काष्ठा parport_driver *drv;

	list_क्रम_each_entry(drv, &drivers, list)
		drv->attach(port);

	/*
	 * call the driver_check function of the drivers रेजिस्टरed in
	 * new device model
	 */

	bus_क्रम_each_drv(&parport_bus_type, शून्य, port, driver_check);
पूर्ण

अटल पूर्णांक driver_detach(काष्ठा device_driver *_drv, व्योम *_port)
अणु
	काष्ठा parport *port = _port;
	काष्ठा parport_driver *drv = to_parport_driver(_drv);

	अगर (drv->detach)
		drv->detach(port);
	वापस 0;
पूर्ण

/* Call detach(port) क्रम each रेजिस्टरed driver. */
अटल व्योम detach_driver_chain(काष्ठा parport *port)
अणु
	काष्ठा parport_driver *drv;
	/* caller has exclusive registration_lock */
	list_क्रम_each_entry(drv, &drivers, list)
		drv->detach(port);

	/*
	 * call the detach function of the drivers रेजिस्टरed in
	 * new device model
	 */

	bus_क्रम_each_drv(&parport_bus_type, शून्य, port, driver_detach);
पूर्ण

/* Ask kmod क्रम some lowlevel drivers. */
अटल व्योम get_lowlevel_driver(व्योम)
अणु
	/*
	 * There is no actual module called this: you should set
	 * up an alias क्रम modutils.
	 */
	request_module("parport_lowlevel");
पूर्ण

/*
 * iterates through all the devices connected to the bus and sends the device
 * details to the match_port callback of the driver, so that the driver can
 * know what are all the ports that are connected to the bus and choose the
 * port to which it wants to रेजिस्टर its device.
 */
अटल पूर्णांक port_check(काष्ठा device *dev, व्योम *dev_drv)
अणु
	काष्ठा parport_driver *drv = dev_drv;

	/* only send ports, करो not send other devices connected to bus */
	अगर (is_parport(dev))
		drv->match_port(to_parport_dev(dev));
	वापस 0;
पूर्ण

/*
 * Iterates through all the devices connected to the bus and वापस 1
 * अगर the device is a parallel port.
 */

अटल पूर्णांक port_detect(काष्ठा device *dev, व्योम *dev_drv)
अणु
	अगर (is_parport(dev))
		वापस 1;
	वापस 0;
पूर्ण

/**
 *	__parport_रेजिस्टर_driver - रेजिस्टर a parallel port device driver
 *	@drv: काष्ठाure describing the driver
 *	@owner: owner module of drv
 *	@mod_name: module name string
 *
 *	This can be called by a parallel port device driver in order
 *	to receive notअगरications about ports being found in the
 *	प्रणाली, as well as ports no दीर्घer available.
 *
 *	If devmodel is true then the new device model is used
 *	क्रम registration.
 *
 *	The @drv काष्ठाure is allocated by the caller and must not be
 *	deallocated until after calling parport_unरेजिस्टर_driver().
 *
 *	If using the non device model:
 *	The driver's attach() function may block.  The port that
 *	attach() is given will be valid क्रम the duration of the
 *	callback, but अगर the driver wants to take a copy of the
 *	poपूर्णांकer it must call parport_get_port() to करो so.  Calling
 *	parport_रेजिस्टर_device() on that port will करो this क्रम you.
 *
 *	The driver's detach() function may block.  The port that
 *	detach() is given will be valid क्रम the duration of the
 *	callback, but अगर the driver wants to take a copy of the
 *	poपूर्णांकer it must call parport_get_port() to करो so.
 *
 *
 *	Returns 0 on success. The non device model will always succeeds.
 *	but the new device model can fail and will वापस the error code.
 **/

पूर्णांक __parport_रेजिस्टर_driver(काष्ठा parport_driver *drv, काष्ठा module *owner,
			      स्थिर अक्षर *mod_name)
अणु
	/* using device model */
	पूर्णांक ret;

	/* initialize common driver fields */
	drv->driver.name = drv->name;
	drv->driver.bus = &parport_bus_type;
	drv->driver.owner = owner;
	drv->driver.mod_name = mod_name;
	ret = driver_रेजिस्टर(&drv->driver);
	अगर (ret)
		वापस ret;

	/*
	 * check अगर bus has any parallel port रेजिस्टरed, अगर
	 * none is found then load the lowlevel driver.
	 */
	ret = bus_क्रम_each_dev(&parport_bus_type, शून्य, शून्य,
			       port_detect);
	अगर (!ret)
		get_lowlevel_driver();

	mutex_lock(&registration_lock);
	अगर (drv->match_port)
		bus_क्रम_each_dev(&parport_bus_type, शून्य, drv,
				 port_check);
	mutex_unlock(&registration_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__parport_रेजिस्टर_driver);

अटल पूर्णांक port_detach(काष्ठा device *dev, व्योम *_drv)
अणु
	काष्ठा parport_driver *drv = _drv;

	अगर (is_parport(dev) && drv->detach)
		drv->detach(to_parport_dev(dev));

	वापस 0;
पूर्ण

/**
 *	parport_unरेजिस्टर_driver - deरेजिस्टर a parallel port device driver
 *	@drv: काष्ठाure describing the driver that was given to
 *	      parport_रेजिस्टर_driver()
 *
 *	This should be called by a parallel port device driver that
 *	has रेजिस्टरed itself using parport_रेजिस्टर_driver() when it
 *	is about to be unloaded.
 *
 *	When it वापसs, the driver's attach() routine will no दीर्घer
 *	be called, and क्रम each port that attach() was called क्रम, the
 *	detach() routine will have been called.
 *
 *	All the driver's attach() and detach() calls are guaranteed to have
 *	finished by the समय this function वापसs.
 **/

व्योम parport_unरेजिस्टर_driver(काष्ठा parport_driver *drv)
अणु
	mutex_lock(&registration_lock);
	bus_क्रम_each_dev(&parport_bus_type, शून्य, drv, port_detach);
	driver_unरेजिस्टर(&drv->driver);
	mutex_unlock(&registration_lock);
पूर्ण
EXPORT_SYMBOL(parport_unरेजिस्टर_driver);

अटल व्योम मुक्त_port(काष्ठा device *dev)
अणु
	पूर्णांक d;
	काष्ठा parport *port = to_parport_dev(dev);

	spin_lock(&full_list_lock);
	list_del(&port->full_list);
	spin_unlock(&full_list_lock);
	क्रम (d = 0; d < 5; d++) अणु
		kमुक्त(port->probe_info[d].class_name);
		kमुक्त(port->probe_info[d].mfr);
		kमुक्त(port->probe_info[d].model);
		kमुक्त(port->probe_info[d].cmdset);
		kमुक्त(port->probe_info[d].description);
	पूर्ण

	kमुक्त(port->name);
	kमुक्त(port);
पूर्ण

/**
 *	parport_get_port - increment a port's reference count
 *	@port: the port
 *
 *	This ensures that a काष्ठा parport poपूर्णांकer reमुख्यs valid
 *	until the matching parport_put_port() call.
 **/

काष्ठा parport *parport_get_port(काष्ठा parport *port)
अणु
	काष्ठा device *dev = get_device(&port->bus_dev);

	वापस to_parport_dev(dev);
पूर्ण
EXPORT_SYMBOL(parport_get_port);

व्योम parport_del_port(काष्ठा parport *port)
अणु
	device_unरेजिस्टर(&port->bus_dev);
पूर्ण
EXPORT_SYMBOL(parport_del_port);

/**
 *	parport_put_port - decrement a port's reference count
 *	@port: the port
 *
 *	This should be called once क्रम each call to parport_get_port(),
 *	once the port is no दीर्घer needed. When the reference count reaches
 *	zero (port is no दीर्घer used), मुक्त_port is called.
 **/

व्योम parport_put_port(काष्ठा parport *port)
अणु
	put_device(&port->bus_dev);
पूर्ण
EXPORT_SYMBOL(parport_put_port);

/**
 *	parport_रेजिस्टर_port - रेजिस्टर a parallel port
 *	@base: base I/O address
 *	@irq: IRQ line
 *	@dma: DMA channel
 *	@ops: poपूर्णांकer to the port driver's port operations काष्ठाure
 *
 *	When a parallel port (lowlevel) driver finds a port that
 *	should be made available to parallel port device drivers, it
 *	should call parport_रेजिस्टर_port().  The @base, @irq, and
 *	@dma parameters are क्रम the convenience of port drivers, and
 *	क्रम ports where they aren't meaningful needn't be set to
 *	anything special.  They can be altered afterwards by adjusting
 *	the relevant members of the parport काष्ठाure that is वापसed
 *	and represents the port.  They should not be tampered with
 *	after calling parport_announce_port, however.
 *
 *	If there are parallel port device drivers in the प्रणाली that
 *	have रेजिस्टरed themselves using parport_रेजिस्टर_driver(),
 *	they are not told about the port at this समय; that is करोne by
 *	parport_announce_port().
 *
 *	The @ops काष्ठाure is allocated by the caller, and must not be
 *	deallocated beक्रमe calling parport_हटाओ_port().
 *
 *	If there is no memory to allocate a new parport काष्ठाure,
 *	this function will वापस %शून्य.
 **/

काष्ठा parport *parport_रेजिस्टर_port(अचिन्हित दीर्घ base, पूर्णांक irq, पूर्णांक dma,
				      काष्ठा parport_operations *ops)
अणु
	काष्ठा list_head *l;
	काष्ठा parport *पंचांगp;
	पूर्णांक num;
	पूर्णांक device;
	अक्षर *name;
	पूर्णांक ret;

	पंचांगp = kzalloc(माप(काष्ठा parport), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस शून्य;

	/* Init our काष्ठाure */
	पंचांगp->base = base;
	पंचांगp->irq = irq;
	पंचांगp->dma = dma;
	पंचांगp->muxport = पंचांगp->daisy = पंचांगp->muxsel = -1;
	पंचांगp->modes = 0;
	INIT_LIST_HEAD(&पंचांगp->list);
	पंचांगp->devices = पंचांगp->cad = शून्य;
	पंचांगp->flags = 0;
	पंचांगp->ops = ops;
	पंचांगp->physport = पंचांगp;
	स_रखो(पंचांगp->probe_info, 0, 5 * माप(काष्ठा parport_device_info));
	rwlock_init(&पंचांगp->cad_lock);
	spin_lock_init(&पंचांगp->रुकोlist_lock);
	spin_lock_init(&पंचांगp->pardevice_lock);
	पंचांगp->ieee1284.mode = IEEE1284_MODE_COMPAT;
	पंचांगp->ieee1284.phase = IEEE1284_PH_FWD_IDLE;
	sema_init(&पंचांगp->ieee1284.irq, 0);
	पंचांगp->spपूर्णांकime = parport_शेष_spपूर्णांकime;
	atomic_set(&पंचांगp->ref_count, 1);
	INIT_LIST_HEAD(&पंचांगp->full_list);

	name = kदो_स्मृति(15, GFP_KERNEL);
	अगर (!name) अणु
		kमुक्त(पंचांगp);
		वापस शून्य;
	पूर्ण
	/* Search क्रम the lowest मुक्त parport number. */

	spin_lock(&full_list_lock);
	क्रम (l = all_ports.next, num = 0; l != &all_ports; l = l->next, num++) अणु
		काष्ठा parport *p = list_entry(l, काष्ठा parport, full_list);
		अगर (p->number != num)
			अवरोध;
	पूर्ण
	पंचांगp->portnum = पंचांगp->number = num;
	list_add_tail(&पंचांगp->full_list, l);
	spin_unlock(&full_list_lock);

	/*
	 * Now that the portnum is known finish करोing the Init.
	 */
	प्र_लिखो(name, "parport%d", पंचांगp->portnum = पंचांगp->number);
	पंचांगp->name = name;
	पंचांगp->bus_dev.bus = &parport_bus_type;
	पंचांगp->bus_dev.release = मुक्त_port;
	dev_set_name(&पंचांगp->bus_dev, name);
	पंचांगp->bus_dev.type = &parport_device_type;

	क्रम (device = 0; device < 5; device++)
		/* assume the worst */
		पंचांगp->probe_info[device].class = PARPORT_CLASS_LEGACY;

	पंचांगp->रुकोhead = पंचांगp->रुकोtail = शून्य;

	ret = device_रेजिस्टर(&पंचांगp->bus_dev);
	अगर (ret) अणु
		put_device(&पंचांगp->bus_dev);
		वापस शून्य;
	पूर्ण

	वापस पंचांगp;
पूर्ण
EXPORT_SYMBOL(parport_रेजिस्टर_port);

/**
 *	parport_announce_port - tell device drivers about a parallel port
 *	@port: parallel port to announce
 *
 *	After a port driver has रेजिस्टरed a parallel port with
 *	parport_रेजिस्टर_port, and perक्रमmed any necessary
 *	initialisation or adjusपंचांगents, it should call
 *	parport_announce_port() in order to notअगरy all device drivers
 *	that have called parport_रेजिस्टर_driver().  Their attach()
 *	functions will be called, with @port as the parameter.
 **/

व्योम parport_announce_port(काष्ठा parport *port)
अणु
	पूर्णांक i;

#अगर_घोषित CONFIG_PARPORT_1284
	/* Analyse the IEEE1284.3 topology of the port. */
	parport_daisy_init(port);
#पूर्ण_अगर

	अगर (!port->dev)
		pr_warn("%s: fix this legacy no-device port driver!\n",
			port->name);

	parport_proc_रेजिस्टर(port);
	mutex_lock(&registration_lock);
	spin_lock_irq(&parportlist_lock);
	list_add_tail(&port->list, &portlist);
	क्रम (i = 1; i < 3; i++) अणु
		काष्ठा parport *slave = port->slaves[i-1];
		अगर (slave)
			list_add_tail(&slave->list, &portlist);
	पूर्ण
	spin_unlock_irq(&parportlist_lock);

	/* Let drivers know that new port(s) has arrived. */
	attach_driver_chain(port);
	क्रम (i = 1; i < 3; i++) अणु
		काष्ठा parport *slave = port->slaves[i-1];
		अगर (slave)
			attach_driver_chain(slave);
	पूर्ण
	mutex_unlock(&registration_lock);
पूर्ण
EXPORT_SYMBOL(parport_announce_port);

/**
 *	parport_हटाओ_port - deरेजिस्टर a parallel port
 *	@port: parallel port to deरेजिस्टर
 *
 *	When a parallel port driver is क्रमcibly unloaded, or a
 *	parallel port becomes inaccessible, the port driver must call
 *	this function in order to deal with device drivers that still
 *	want to use it.
 *
 *	The parport काष्ठाure associated with the port has its
 *	operations काष्ठाure replaced with one containing 'null'
 *	operations that वापस errors or just करोn't करो anything.
 *
 *	Any drivers that have रेजिस्टरed themselves using
 *	parport_रेजिस्टर_driver() are notअगरied that the port is no
 *	दीर्घer accessible by having their detach() routines called
 *	with @port as the parameter.
 **/

व्योम parport_हटाओ_port(काष्ठा parport *port)
अणु
	पूर्णांक i;

	mutex_lock(&registration_lock);

	/* Spपढ़ो the word. */
	detach_driver_chain(port);

#अगर_घोषित CONFIG_PARPORT_1284
	/* Forget the IEEE1284.3 topology of the port. */
	parport_daisy_fini(port);
	क्रम (i = 1; i < 3; i++) अणु
		काष्ठा parport *slave = port->slaves[i-1];
		अगर (!slave)
			जारी;
		detach_driver_chain(slave);
		parport_daisy_fini(slave);
	पूर्ण
#पूर्ण_अगर

	port->ops = &dead_ops;
	spin_lock(&parportlist_lock);
	list_del_init(&port->list);
	क्रम (i = 1; i < 3; i++) अणु
		काष्ठा parport *slave = port->slaves[i-1];
		अगर (slave)
			list_del_init(&slave->list);
	पूर्ण
	spin_unlock(&parportlist_lock);

	mutex_unlock(&registration_lock);

	parport_proc_unरेजिस्टर(port);

	क्रम (i = 1; i < 3; i++) अणु
		काष्ठा parport *slave = port->slaves[i-1];
		अगर (slave)
			parport_put_port(slave);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(parport_हटाओ_port);

अटल व्योम मुक्त_pardevice(काष्ठा device *dev)
अणु
	काष्ठा pardevice *par_dev = to_pardevice(dev);

	kमुक्त(par_dev->name);
	kमुक्त(par_dev);
पूर्ण

/**
 *	parport_रेजिस्टर_dev_model - रेजिस्टर a device on a parallel port
 *	@port: port to which the device is attached
 *	@name: a name to refer to the device
 *	@par_dev_cb: काष्ठा containing callbacks
 *	@id: device number to be given to the device
 *
 *	This function, called by parallel port device drivers,
 *	declares that a device is connected to a port, and tells the
 *	प्रणाली all it needs to know.
 *
 *	The काष्ठा pardev_cb contains poपूर्णांकer to callbacks. preemption
 *	callback function, @preempt, is called when this device driver
 *	has claimed access to the port but another device driver wants
 *	to use it.  It is given, @निजी, as its parameter, and should
 *	वापस zero अगर it is willing क्रम the प्रणाली to release the port
 *	to another driver on its behalf. If it wants to keep control of
 *	the port it should वापस non-zero, and no action will be taken.
 *	It is good manners क्रम the driver to try to release the port at
 *	the earliest opportunity after its preemption callback rejects a
 *	preemption attempt. Note that अगर a preemption callback is happy
 *	क्रम preemption to go ahead, there is no need to release the
 *	port; it is करोne स्वतःmatically. This function may not block, as
 *	it may be called from पूर्णांकerrupt context. If the device driver
 *	करोes not support preemption, @preempt can be %शून्य.
 *
 *	The wake-up ("kick") callback function, @wakeup, is called when
 *	the port is available to be claimed क्रम exclusive access; that
 *	is, parport_claim() is guaranteed to succeed when called from
 *	inside the wake-up callback function.  If the driver wants to
 *	claim the port it should करो so; otherwise, it need not take
 *	any action.  This function may not block, as it may be called
 *	from पूर्णांकerrupt context.  If the device driver करोes not want to
 *	be explicitly invited to claim the port in this way, @wakeup can
 *	be %शून्य.
 *
 *	The पूर्णांकerrupt handler, @irq_func, is called when an पूर्णांकerrupt
 *	arrives from the parallel port.  Note that अगर a device driver
 *	wants to use पूर्णांकerrupts it should use parport_enable_irq(),
 *	and can also check the irq member of the parport काष्ठाure
 *	representing the port.
 *
 *	The parallel port (lowlevel) driver is the one that has called
 *	request_irq() and whose पूर्णांकerrupt handler is called first.
 *	This handler करोes whatever needs to be करोne to the hardware to
 *	acknowledge the पूर्णांकerrupt (क्रम PC-style ports there is nothing
 *	special to be करोne).  It then tells the IEEE 1284 code about
 *	the पूर्णांकerrupt, which may involve reacting to an IEEE 1284
 *	event depending on the current IEEE 1284 phase.  After this,
 *	it calls @irq_func.  Needless to say, @irq_func will be called
 *	from पूर्णांकerrupt context, and may not block.
 *
 *	The %PARPORT_DEV_EXCL flag is क्रम preventing port sharing, and
 *	so should only be used when sharing the port with other device
 *	drivers is impossible and would lead to incorrect behaviour.
 *	Use it sparingly!  Normally, @flags will be zero.
 *
 *	This function वापसs a poपूर्णांकer to a काष्ठाure that represents
 *	the device on the port, or %शून्य अगर there is not enough memory
 *	to allocate space क्रम that काष्ठाure.
 **/

काष्ठा pardevice *
parport_रेजिस्टर_dev_model(काष्ठा parport *port, स्थिर अक्षर *name,
			   स्थिर काष्ठा pardev_cb *par_dev_cb, पूर्णांक id)
अणु
	काष्ठा pardevice *par_dev;
	पूर्णांक ret;
	अक्षर *devname;

	अगर (port->physport->flags & PARPORT_FLAG_EXCL) अणु
		/* An exclusive device is रेजिस्टरed. */
		pr_err("%s: no more devices allowed\n", port->name);
		वापस शून्य;
	पूर्ण

	अगर (par_dev_cb->flags & PARPORT_DEV_LURK) अणु
		अगर (!par_dev_cb->preempt || !par_dev_cb->wakeup) अणु
			pr_info("%s: refused to register lurking device (%s) without callbacks\n",
				port->name, name);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (par_dev_cb->flags & PARPORT_DEV_EXCL) अणु
		अगर (port->physport->devices) अणु
			/*
			 * If a device is alपढ़ोy रेजिस्टरed and this new
			 * device wants exclusive access, then no need to
			 * जारी as we can not grant exclusive access to
			 * this device.
			 */
			pr_err("%s: cannot grant exclusive access for device %s\n",
			       port->name, name);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (!try_module_get(port->ops->owner))
		वापस शून्य;

	parport_get_port(port);

	par_dev = kzalloc(माप(*par_dev), GFP_KERNEL);
	अगर (!par_dev)
		जाओ err_put_port;

	par_dev->state = kzalloc(माप(*par_dev->state), GFP_KERNEL);
	अगर (!par_dev->state)
		जाओ err_put_par_dev;

	devname = kstrdup(name, GFP_KERNEL);
	अगर (!devname)
		जाओ err_मुक्त_par_dev;

	par_dev->name = devname;
	par_dev->port = port;
	par_dev->daisy = -1;
	par_dev->preempt = par_dev_cb->preempt;
	par_dev->wakeup = par_dev_cb->wakeup;
	par_dev->निजी = par_dev_cb->निजी;
	par_dev->flags = par_dev_cb->flags;
	par_dev->irq_func = par_dev_cb->irq_func;
	par_dev->रुकोing = 0;
	par_dev->समयout = 5 * HZ;

	par_dev->dev.parent = &port->bus_dev;
	par_dev->dev.bus = &parport_bus_type;
	ret = dev_set_name(&par_dev->dev, "%s.%d", devname, id);
	अगर (ret)
		जाओ err_मुक्त_devname;
	par_dev->dev.release = मुक्त_pardevice;
	par_dev->devmodel = true;
	ret = device_रेजिस्टर(&par_dev->dev);
	अगर (ret) अणु
		kमुक्त(par_dev->state);
		put_device(&par_dev->dev);
		जाओ err_put_port;
	पूर्ण

	/* Chain this onto the list */
	par_dev->prev = शून्य;
	/*
	 * This function must not run from an irq handler so we करोn' t need
	 * to clear irq on the local CPU. -arca
	 */
	spin_lock(&port->physport->pardevice_lock);

	अगर (par_dev_cb->flags & PARPORT_DEV_EXCL) अणु
		अगर (port->physport->devices) अणु
			spin_unlock(&port->physport->pardevice_lock);
			pr_debug("%s: cannot grant exclusive access for device %s\n",
				 port->name, name);
			kमुक्त(par_dev->state);
			device_unरेजिस्टर(&par_dev->dev);
			जाओ err_put_port;
		पूर्ण
		port->flags |= PARPORT_FLAG_EXCL;
	पूर्ण

	par_dev->next = port->physport->devices;
	wmb();	/*
		 * Make sure that पंचांगp->next is written beक्रमe it's
		 * added to the list; see comments marked 'no locking
		 * required'
		 */
	अगर (port->physport->devices)
		port->physport->devices->prev = par_dev;
	port->physport->devices = par_dev;
	spin_unlock(&port->physport->pardevice_lock);

	init_रुकोqueue_head(&par_dev->रुको_q);
	par_dev->बारlice = parport_शेष_बारlice;
	par_dev->रुकोnext = शून्य;
	par_dev->रुकोprev = शून्य;

	/*
	 * This has to be run as last thing since init_state may need other
	 * pardevice fields. -arca
	 */
	port->ops->init_state(par_dev, par_dev->state);
	अगर (!test_and_set_bit(PARPORT_DEVPROC_REGISTERED, &port->devflags)) अणु
		port->proc_device = par_dev;
		parport_device_proc_रेजिस्टर(par_dev);
	पूर्ण

	वापस par_dev;

err_मुक्त_devname:
	kमुक्त(devname);
err_मुक्त_par_dev:
	kमुक्त(par_dev->state);
err_put_par_dev:
	अगर (!par_dev->devmodel)
		kमुक्त(par_dev);
err_put_port:
	parport_put_port(port);
	module_put(port->ops->owner);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(parport_रेजिस्टर_dev_model);

/**
 *	parport_unरेजिस्टर_device - deरेजिस्टर a device on a parallel port
 *	@dev: poपूर्णांकer to काष्ठाure representing device
 *
 *	This unकरोes the effect of parport_रेजिस्टर_device().
 **/

व्योम parport_unरेजिस्टर_device(काष्ठा pardevice *dev)
अणु
	काष्ठा parport *port;

#अगर_घोषित PARPORT_PARANOID
	अगर (!dev) अणु
		pr_err("%s: passed NULL\n", __func__);
		वापस;
	पूर्ण
#पूर्ण_अगर

	port = dev->port->physport;

	अगर (port->proc_device == dev) अणु
		port->proc_device = शून्य;
		clear_bit(PARPORT_DEVPROC_REGISTERED, &port->devflags);
		parport_device_proc_unरेजिस्टर(dev);
	पूर्ण

	अगर (port->cad == dev) अणु
		prपूर्णांकk(KERN_DEBUG "%s: %s forgot to release port\n",
		       port->name, dev->name);
		parport_release(dev);
	पूर्ण

	spin_lock(&port->pardevice_lock);
	अगर (dev->next)
		dev->next->prev = dev->prev;
	अगर (dev->prev)
		dev->prev->next = dev->next;
	अन्यथा
		port->devices = dev->next;

	अगर (dev->flags & PARPORT_DEV_EXCL)
		port->flags &= ~PARPORT_FLAG_EXCL;

	spin_unlock(&port->pardevice_lock);

	/*
	 * Make sure we haven't left any poपूर्णांकers around in the रुको
	 * list.
	 */
	spin_lock_irq(&port->रुकोlist_lock);
	अगर (dev->रुकोprev || dev->रुकोnext || port->रुकोhead == dev) अणु
		अगर (dev->रुकोprev)
			dev->रुकोprev->रुकोnext = dev->रुकोnext;
		अन्यथा
			port->रुकोhead = dev->रुकोnext;
		अगर (dev->रुकोnext)
			dev->रुकोnext->रुकोprev = dev->रुकोprev;
		अन्यथा
			port->रुकोtail = dev->रुकोprev;
	पूर्ण
	spin_unlock_irq(&port->रुकोlist_lock);

	kमुक्त(dev->state);
	device_unरेजिस्टर(&dev->dev);

	module_put(port->ops->owner);
	parport_put_port(port);
पूर्ण
EXPORT_SYMBOL(parport_unरेजिस्टर_device);

/**
 *	parport_find_number - find a parallel port by number
 *	@number: parallel port number
 *
 *	This वापसs the parallel port with the specअगरied number, or
 *	%शून्य अगर there is none.
 *
 *	There is an implicit parport_get_port() करोne alपढ़ोy; to throw
 *	away the reference to the port that parport_find_number()
 *	gives you, use parport_put_port().
 */

काष्ठा parport *parport_find_number(पूर्णांक number)
अणु
	काष्ठा parport *port, *result = शून्य;

	अगर (list_empty(&portlist))
		get_lowlevel_driver();

	spin_lock(&parportlist_lock);
	list_क्रम_each_entry(port, &portlist, list) अणु
		अगर (port->number == number) अणु
			result = parport_get_port(port);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&parportlist_lock);
	वापस result;
पूर्ण
EXPORT_SYMBOL(parport_find_number);

/**
 *	parport_find_base - find a parallel port by base address
 *	@base: base I/O address
 *
 *	This वापसs the parallel port with the specअगरied base
 *	address, or %शून्य अगर there is none.
 *
 *	There is an implicit parport_get_port() करोne alपढ़ोy; to throw
 *	away the reference to the port that parport_find_base()
 *	gives you, use parport_put_port().
 */

काष्ठा parport *parport_find_base(अचिन्हित दीर्घ base)
अणु
	काष्ठा parport *port, *result = शून्य;

	अगर (list_empty(&portlist))
		get_lowlevel_driver();

	spin_lock(&parportlist_lock);
	list_क्रम_each_entry(port, &portlist, list) अणु
		अगर (port->base == base) अणु
			result = parport_get_port(port);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&parportlist_lock);
	वापस result;
पूर्ण
EXPORT_SYMBOL(parport_find_base);

/**
 *	parport_claim - claim access to a parallel port device
 *	@dev: poपूर्णांकer to काष्ठाure representing a device on the port
 *
 *	This function will not block and so can be used from पूर्णांकerrupt
 *	context.  If parport_claim() succeeds in claiming access to
 *	the port it वापसs zero and the port is available to use.  It
 *	may fail (वापसing non-zero) अगर the port is in use by another
 *	driver and that driver is not willing to relinquish control of
 *	the port.
 **/

पूर्णांक parport_claim(काष्ठा pardevice *dev)
अणु
	काष्ठा pardevice *oldcad;
	काष्ठा parport *port = dev->port->physport;
	अचिन्हित दीर्घ flags;

	अगर (port->cad == dev) अणु
		pr_info("%s: %s already owner\n", dev->port->name, dev->name);
		वापस 0;
	पूर्ण

	/* Preempt any current device */
	ग_लिखो_lock_irqsave(&port->cad_lock, flags);
	oldcad = port->cad;
	अगर (oldcad) अणु
		अगर (oldcad->preempt) अणु
			अगर (oldcad->preempt(oldcad->निजी))
				जाओ blocked;
			port->ops->save_state(port, dev->state);
		पूर्ण अन्यथा
			जाओ blocked;

		अगर (port->cad != oldcad) अणु
			/*
			 * I think we'll actually deadlock rather than
			 * get here, but just in हाल..
			 */
			pr_warn("%s: %s released port when preempted!\n",
				port->name, oldcad->name);
			अगर (port->cad)
				जाओ blocked;
		पूर्ण
	पूर्ण

	/* Can't fail from now on, so mark ourselves as no दीर्घer रुकोing.  */
	अगर (dev->रुकोing & 1) अणु
		dev->रुकोing = 0;

		/* Take ourselves out of the रुको list again.  */
		spin_lock_irq(&port->रुकोlist_lock);
		अगर (dev->रुकोprev)
			dev->रुकोprev->रुकोnext = dev->रुकोnext;
		अन्यथा
			port->रुकोhead = dev->रुकोnext;
		अगर (dev->रुकोnext)
			dev->रुकोnext->रुकोprev = dev->रुकोprev;
		अन्यथा
			port->रुकोtail = dev->रुकोprev;
		spin_unlock_irq(&port->रुकोlist_lock);
		dev->रुकोprev = dev->रुकोnext = शून्य;
	पूर्ण

	/* Now we करो the change of devices */
	port->cad = dev;

#अगर_घोषित CONFIG_PARPORT_1284
	/* If it's a mux port, select it. */
	अगर (dev->port->muxport >= 0) अणु
		/* FIXME */
		port->muxsel = dev->port->muxport;
	पूर्ण

	/* If it's a daisy chain device, select it. */
	अगर (dev->daisy >= 0) अणु
		/* This could be lazier. */
		अगर (!parport_daisy_select(port, dev->daisy,
					   IEEE1284_MODE_COMPAT))
			port->daisy = dev->daisy;
	पूर्ण
#पूर्ण_अगर /* IEEE1284.3 support */

	/* Restore control रेजिस्टरs */
	port->ops->restore_state(port, dev->state);
	ग_लिखो_unlock_irqrestore(&port->cad_lock, flags);
	dev->समय = jअगरfies;
	वापस 0;

blocked:
	/*
	 * If this is the first समय we tried to claim the port, रेजिस्टर an
	 * पूर्णांकerest.  This is only allowed क्रम devices sleeping in
	 * parport_claim_or_block(), or those with a wakeup function.
	 */

	/* The cad_lock is still held क्रम writing here */
	अगर (dev->रुकोing & 2 || dev->wakeup) अणु
		spin_lock(&port->रुकोlist_lock);
		अगर (test_and_set_bit(0, &dev->रुकोing) == 0) अणु
			/* First add ourselves to the end of the रुको list. */
			dev->रुकोnext = शून्य;
			dev->रुकोprev = port->रुकोtail;
			अगर (port->रुकोtail) अणु
				port->रुकोtail->रुकोnext = dev;
				port->रुकोtail = dev;
			पूर्ण अन्यथा
				port->रुकोhead = port->रुकोtail = dev;
		पूर्ण
		spin_unlock(&port->रुकोlist_lock);
	पूर्ण
	ग_लिखो_unlock_irqrestore(&port->cad_lock, flags);
	वापस -EAGAIN;
पूर्ण
EXPORT_SYMBOL(parport_claim);

/**
 *	parport_claim_or_block - claim access to a parallel port device
 *	@dev: poपूर्णांकer to काष्ठाure representing a device on the port
 *
 *	This behaves like parport_claim(), but will block अगर necessary
 *	to रुको क्रम the port to be मुक्त.  A वापस value of 1
 *	indicates that it slept; 0 means that it succeeded without
 *	needing to sleep.  A negative error code indicates failure.
 **/

पूर्णांक parport_claim_or_block(काष्ठा pardevice *dev)
अणु
	पूर्णांक r;

	/*
	 * Signal to parport_claim() that we can रुको even without a
	 * wakeup function.
	 */
	dev->रुकोing = 2;

	/* Try to claim the port.  If this fails, we need to sleep.  */
	r = parport_claim(dev);
	अगर (r == -EAGAIN) अणु
#अगर_घोषित PARPORT_DEBUG_SHARING
		prपूर्णांकk(KERN_DEBUG "%s: parport_claim() returned -EAGAIN\n",
		       dev->name);
#पूर्ण_अगर
		/*
		 * FIXME!!! Use the proper locking क्रम dev->रुकोing,
		 * and make this use the "wait_event_interruptible()"
		 * पूर्णांकerfaces. The cli/sti that used to be here
		 * did nothing.
		 *
		 * See also parport_release()
		 */

		/*
		 * If dev->रुकोing is clear now, an पूर्णांकerrupt
		 * gave us the port and we would deadlock अगर we slept.
		 */
		अगर (dev->रुकोing) अणु
			रुको_event_पूर्णांकerruptible(dev->रुको_q,
						 !dev->रुकोing);
			अगर (संकेत_pending(current))
				वापस -EINTR;
			r = 1;
		पूर्ण अन्यथा अणु
			r = 0;
#अगर_घोषित PARPORT_DEBUG_SHARING
			prपूर्णांकk(KERN_DEBUG "%s: didn't sleep in parport_claim_or_block()\n",
			       dev->name);
#पूर्ण_अगर
		पूर्ण

#अगर_घोषित PARPORT_DEBUG_SHARING
		अगर (dev->port->physport->cad != dev)
			prपूर्णांकk(KERN_DEBUG "%s: exiting parport_claim_or_block but %s owns port!\n",
			       dev->name, dev->port->physport->cad ?
			       dev->port->physport->cad->name : "nobody");
#पूर्ण_अगर
	पूर्ण
	dev->रुकोing = 0;
	वापस r;
पूर्ण
EXPORT_SYMBOL(parport_claim_or_block);

/**
 *	parport_release - give up access to a parallel port device
 *	@dev: poपूर्णांकer to काष्ठाure representing parallel port device
 *
 *	This function cannot fail, but it should not be called without
 *	the port claimed.  Similarly, अगर the port is alपढ़ोy claimed
 *	you should not try claiming it again.
 **/

व्योम parport_release(काष्ठा pardevice *dev)
अणु
	काष्ठा parport *port = dev->port->physport;
	काष्ठा pardevice *pd;
	अचिन्हित दीर्घ flags;

	/* Make sure that dev is the current device */
	ग_लिखो_lock_irqsave(&port->cad_lock, flags);
	अगर (port->cad != dev) अणु
		ग_लिखो_unlock_irqrestore(&port->cad_lock, flags);
		pr_warn("%s: %s tried to release parport when not owner\n",
			port->name, dev->name);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_PARPORT_1284
	/* If this is on a mux port, deselect it. */
	अगर (dev->port->muxport >= 0) अणु
		/* FIXME */
		port->muxsel = -1;
	पूर्ण

	/* If this is a daisy device, deselect it. */
	अगर (dev->daisy >= 0) अणु
		parport_daisy_deselect_all(port);
		port->daisy = -1;
	पूर्ण
#पूर्ण_अगर

	port->cad = शून्य;
	ग_लिखो_unlock_irqrestore(&port->cad_lock, flags);

	/* Save control रेजिस्टरs */
	port->ops->save_state(port, dev->state);

	/*
	 * If anybody is रुकोing, find out who's been there दीर्घest and
	 * then wake them up. (Note: no locking required)
	 */
	/* !!! LOCKING IS NEEDED HERE */
	क्रम (pd = port->रुकोhead; pd; pd = pd->रुकोnext) अणु
		अगर (pd->रुकोing & 2) अणु /* sleeping in claim_or_block */
			parport_claim(pd);
			अगर (रुकोqueue_active(&pd->रुको_q))
				wake_up_पूर्णांकerruptible(&pd->रुको_q);
			वापस;
		पूर्ण अन्यथा अगर (pd->wakeup) अणु
			pd->wakeup(pd->निजी);
			अगर (dev->port->cad) /* racy but no matter */
				वापस;
		पूर्ण अन्यथा अणु
			pr_err("%s: don't know how to wake %s\n",
			       port->name, pd->name);
		पूर्ण
	पूर्ण

	/*
	 * Nobody was रुकोing, so walk the list to see अगर anyone is
	 * पूर्णांकerested in being woken up. (Note: no locking required)
	 */
	/* !!! LOCKING IS NEEDED HERE */
	क्रम (pd = port->devices; !port->cad && pd; pd = pd->next) अणु
		अगर (pd->wakeup && pd != dev)
			pd->wakeup(pd->निजी);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(parport_release);

irqवापस_t parport_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा parport *port = dev_id;

	parport_generic_irq(port);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(parport_irq_handler);

MODULE_LICENSE("GPL");
