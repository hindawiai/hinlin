<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic gameport layer
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 * Copyright (c) 2005 Dmitry Torokhov
 */


#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/मानकघोष.स>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/gameport.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>	/* HZ */
#समावेश <linux/mutex.h>
#समावेश <linux/समयkeeping.h>

/*#समावेश <यंत्र/पन.स>*/

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Generic gameport layer");
MODULE_LICENSE("GPL");

अटल bool use_kसमय = true;
module_param(use_kसमय, bool, 0400);
MODULE_PARM_DESC(use_kसमय, "Use ktime for measuring I/O speed");

/*
 * gameport_mutex protects entire gameport subप्रणाली and is taken
 * every समय gameport port or driver registrered or unरेजिस्टरed.
 */
अटल DEFINE_MUTEX(gameport_mutex);

अटल LIST_HEAD(gameport_list);

अटल काष्ठा bus_type gameport_bus;

अटल व्योम gameport_add_port(काष्ठा gameport *gameport);
अटल व्योम gameport_attach_driver(काष्ठा gameport_driver *drv);
अटल व्योम gameport_reconnect_port(काष्ठा gameport *gameport);
अटल व्योम gameport_disconnect_port(काष्ठा gameport *gameport);

#अगर defined(__i386__)

#समावेश <linux/i8253.h>

#घोषणा DELTA(x,y)      ((y)-(x)+((y)<(x)?1193182/HZ:0))
#घोषणा GET_TIME(x)     करो अणु x = get_समय_pit(); पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक get_समय_pit(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक count;

	raw_spin_lock_irqsave(&i8253_lock, flags);
	outb_p(0x00, 0x43);
	count = inb_p(0x40);
	count |= inb_p(0x40) << 8;
	raw_spin_unlock_irqrestore(&i8253_lock, flags);

	वापस count;
पूर्ण

#पूर्ण_अगर



/*
 * gameport_measure_speed() measures the gameport i/o speed.
 */

अटल पूर्णांक gameport_measure_speed(काष्ठा gameport *gameport)
अणु
	अचिन्हित पूर्णांक i, t, tx;
	u64 t1, t2, t3;
	अचिन्हित दीर्घ flags;

	अगर (gameport_खोलो(gameport, शून्य, GAMEPORT_MODE_RAW))
		वापस 0;

	tx = ~0;

	क्रम (i = 0; i < 50; i++) अणु
		local_irq_save(flags);
		t1 = kसमय_get_ns();
		क्रम (t = 0; t < 50; t++)
			gameport_पढ़ो(gameport);
		t2 = kसमय_get_ns();
		t3 = kसमय_get_ns();
		local_irq_restore(flags);
		udelay(i * 10);
		t = (t2 - t1) - (t3 - t2);
		अगर (t < tx)
			tx = t;
	पूर्ण

	gameport_बंद(gameport);
	t = 1000000 * 50;
	अगर (tx)
		t /= tx;
	वापस t;
पूर्ण

अटल पूर्णांक old_gameport_measure_speed(काष्ठा gameport *gameport)
अणु
#अगर defined(__i386__)

	अचिन्हित पूर्णांक i, t, t1, t2, t3, tx;
	अचिन्हित दीर्घ flags;

	अगर (gameport_खोलो(gameport, शून्य, GAMEPORT_MODE_RAW))
		वापस 0;

	tx = 1 << 30;

	क्रम(i = 0; i < 50; i++) अणु
		local_irq_save(flags);
		GET_TIME(t1);
		क्रम (t = 0; t < 50; t++) gameport_पढ़ो(gameport);
		GET_TIME(t2);
		GET_TIME(t3);
		local_irq_restore(flags);
		udelay(i * 10);
		अगर ((t = DELTA(t2,t1) - DELTA(t3,t2)) < tx) tx = t;
	पूर्ण

	gameport_बंद(gameport);
	वापस 59659 / (tx < 1 ? 1 : tx);

#या_अगर defined (__x86_64__)

	अचिन्हित पूर्णांक i, t;
	अचिन्हित दीर्घ tx, t1, t2, flags;

	अगर (gameport_खोलो(gameport, शून्य, GAMEPORT_MODE_RAW))
		वापस 0;

	tx = 1 << 30;

	क्रम(i = 0; i < 50; i++) अणु
		local_irq_save(flags);
		t1 = rdtsc();
		क्रम (t = 0; t < 50; t++) gameport_पढ़ो(gameport);
		t2 = rdtsc();
		local_irq_restore(flags);
		udelay(i * 10);
		अगर (t2 - t1 < tx) tx = t2 - t1;
	पूर्ण

	gameport_बंद(gameport);
	वापस (this_cpu_पढ़ो(cpu_info.loops_per_jअगरfy) *
		(अचिन्हित दीर्घ)HZ / (1000 / 50)) / (tx < 1 ? 1 : tx);

#अन्यथा

	अचिन्हित पूर्णांक j, t = 0;

	अगर (gameport_खोलो(gameport, शून्य, GAMEPORT_MODE_RAW))
		वापस 0;

	j = jअगरfies; जबतक (j == jअगरfies);
	j = jअगरfies; जबतक (j == jअगरfies) अणु t++; gameport_पढ़ो(gameport); पूर्ण

	gameport_बंद(gameport);
	वापस t * HZ / 1000;

#पूर्ण_अगर
पूर्ण

व्योम gameport_start_polling(काष्ठा gameport *gameport)
अणु
	spin_lock(&gameport->समयr_lock);

	अगर (!gameport->poll_cnt++) अणु
		BUG_ON(!gameport->poll_handler);
		BUG_ON(!gameport->poll_पूर्णांकerval);
		mod_समयr(&gameport->poll_समयr, jअगरfies + msecs_to_jअगरfies(gameport->poll_पूर्णांकerval));
	पूर्ण

	spin_unlock(&gameport->समयr_lock);
पूर्ण
EXPORT_SYMBOL(gameport_start_polling);

व्योम gameport_stop_polling(काष्ठा gameport *gameport)
अणु
	spin_lock(&gameport->समयr_lock);

	अगर (!--gameport->poll_cnt)
		del_समयr(&gameport->poll_समयr);

	spin_unlock(&gameport->समयr_lock);
पूर्ण
EXPORT_SYMBOL(gameport_stop_polling);

अटल व्योम gameport_run_poll_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा gameport *gameport = from_समयr(gameport, t, poll_समयr);

	gameport->poll_handler(gameport);
	अगर (gameport->poll_cnt)
		mod_समयr(&gameport->poll_समयr, jअगरfies + msecs_to_jअगरfies(gameport->poll_पूर्णांकerval));
पूर्ण

/*
 * Basic gameport -> driver core mappings
 */

अटल पूर्णांक gameport_bind_driver(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	पूर्णांक error;

	gameport->dev.driver = &drv->driver;
	अगर (drv->connect(gameport, drv)) अणु
		gameport->dev.driver = शून्य;
		वापस -ENODEV;
	पूर्ण

	error = device_bind_driver(&gameport->dev);
	अगर (error) अणु
		dev_warn(&gameport->dev,
			 "device_bind_driver() failed for %s (%s) and %s, error: %d\n",
			gameport->phys, gameport->name,
			drv->description, error);
		drv->disconnect(gameport);
		gameport->dev.driver = शून्य;
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gameport_find_driver(काष्ठा gameport *gameport)
अणु
	पूर्णांक error;

	error = device_attach(&gameport->dev);
	अगर (error < 0)
		dev_warn(&gameport->dev,
			 "device_attach() failed for %s (%s), error: %d\n",
			 gameport->phys, gameport->name, error);
पूर्ण


/*
 * Gameport event processing.
 */

क्रमागत gameport_event_type अणु
	GAMEPORT_REGISTER_PORT,
	GAMEPORT_ATTACH_DRIVER,
पूर्ण;

काष्ठा gameport_event अणु
	क्रमागत gameport_event_type type;
	व्योम *object;
	काष्ठा module *owner;
	काष्ठा list_head node;
पूर्ण;

अटल DEFINE_SPINLOCK(gameport_event_lock);	/* protects gameport_event_list */
अटल LIST_HEAD(gameport_event_list);

अटल काष्ठा gameport_event *gameport_get_event(व्योम)
अणु
	काष्ठा gameport_event *event = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gameport_event_lock, flags);

	अगर (!list_empty(&gameport_event_list)) अणु
		event = list_first_entry(&gameport_event_list,
					 काष्ठा gameport_event, node);
		list_del_init(&event->node);
	पूर्ण

	spin_unlock_irqrestore(&gameport_event_lock, flags);
	वापस event;
पूर्ण

अटल व्योम gameport_मुक्त_event(काष्ठा gameport_event *event)
अणु
	module_put(event->owner);
	kमुक्त(event);
पूर्ण

अटल व्योम gameport_हटाओ_duplicate_events(काष्ठा gameport_event *event)
अणु
	काष्ठा gameport_event *e, *next;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gameport_event_lock, flags);

	list_क्रम_each_entry_safe(e, next, &gameport_event_list, node) अणु
		अगर (event->object == e->object) अणु
			/*
			 * If this event is of dअगरferent type we should not
			 * look further - we only suppress duplicate events
			 * that were sent back-to-back.
			 */
			अगर (event->type != e->type)
				अवरोध;

			list_del_init(&e->node);
			gameport_मुक्त_event(e);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&gameport_event_lock, flags);
पूर्ण


अटल व्योम gameport_handle_events(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gameport_event *event;

	mutex_lock(&gameport_mutex);

	/*
	 * Note that we handle only one event here to give swsusp
	 * a chance to मुक्तze kgameportd thपढ़ो. Gameport events
	 * should be pretty rare so we are not concerned about
	 * taking perक्रमmance hit.
	 */
	अगर ((event = gameport_get_event())) अणु

		चयन (event->type) अणु

		हाल GAMEPORT_REGISTER_PORT:
			gameport_add_port(event->object);
			अवरोध;

		हाल GAMEPORT_ATTACH_DRIVER:
			gameport_attach_driver(event->object);
			अवरोध;
		पूर्ण

		gameport_हटाओ_duplicate_events(event);
		gameport_मुक्त_event(event);
	पूर्ण

	mutex_unlock(&gameport_mutex);
पूर्ण

अटल DECLARE_WORK(gameport_event_work, gameport_handle_events);

अटल पूर्णांक gameport_queue_event(व्योम *object, काष्ठा module *owner,
				क्रमागत gameport_event_type event_type)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा gameport_event *event;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&gameport_event_lock, flags);

	/*
	 * Scan event list क्रम the other events क्रम the same gameport port,
	 * starting with the most recent one. If event is the same we
	 * करो not need add new one. If event is of dअगरferent type we
	 * need to add this event and should not look further because
	 * we need to preserve sequence of distinct events.
	 */
	list_क्रम_each_entry_reverse(event, &gameport_event_list, node) अणु
		अगर (event->object == object) अणु
			अगर (event->type == event_type)
				जाओ out;
			अवरोध;
		पूर्ण
	पूर्ण

	event = kदो_स्मृति(माप(काष्ठा gameport_event), GFP_ATOMIC);
	अगर (!event) अणु
		pr_err("Not enough memory to queue event %d\n", event_type);
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (!try_module_get(owner)) अणु
		pr_warn("Can't get module reference, dropping event %d\n",
			event_type);
		kमुक्त(event);
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	event->type = event_type;
	event->object = object;
	event->owner = owner;

	list_add_tail(&event->node, &gameport_event_list);
	queue_work(प्रणाली_दीर्घ_wq, &gameport_event_work);

out:
	spin_unlock_irqrestore(&gameport_event_lock, flags);
	वापस retval;
पूर्ण

/*
 * Remove all events that have been submitted क्रम a given object,
 * be it a gameport port or a driver.
 */
अटल व्योम gameport_हटाओ_pending_events(व्योम *object)
अणु
	काष्ठा gameport_event *event, *next;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gameport_event_lock, flags);

	list_क्रम_each_entry_safe(event, next, &gameport_event_list, node) अणु
		अगर (event->object == object) अणु
			list_del_init(&event->node);
			gameport_मुक्त_event(event);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&gameport_event_lock, flags);
पूर्ण

/*
 * Destroy child gameport port (अगर any) that has not been fully रेजिस्टरed yet.
 *
 * Note that we rely on the fact that port can have only one child and thereक्रमe
 * only one child registration request can be pending. Additionally, children
 * are रेजिस्टरed by driver's connect() handler so there can't be a gअक्रमchild
 * pending registration together with a child.
 */
अटल काष्ठा gameport *gameport_get_pending_child(काष्ठा gameport *parent)
अणु
	काष्ठा gameport_event *event;
	काष्ठा gameport *gameport, *child = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gameport_event_lock, flags);

	list_क्रम_each_entry(event, &gameport_event_list, node) अणु
		अगर (event->type == GAMEPORT_REGISTER_PORT) अणु
			gameport = event->object;
			अगर (gameport->parent == parent) अणु
				child = gameport;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&gameport_event_lock, flags);
	वापस child;
पूर्ण

/*
 * Gameport port operations
 */

अटल sमाप_प्रकार gameport_description_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gameport *gameport = to_gameport_port(dev);

	वापस प्र_लिखो(buf, "%s\n", gameport->name);
पूर्ण
अटल DEVICE_ATTR(description, S_IRUGO, gameport_description_show, शून्य);

अटल sमाप_प्रकार drvctl_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gameport *gameport = to_gameport_port(dev);
	काष्ठा device_driver *drv;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&gameport_mutex);
	अगर (error)
		वापस error;

	अगर (!म_भेदन(buf, "none", count)) अणु
		gameport_disconnect_port(gameport);
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "reconnect", count)) अणु
		gameport_reconnect_port(gameport);
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "rescan", count)) अणु
		gameport_disconnect_port(gameport);
		gameport_find_driver(gameport);
	पूर्ण अन्यथा अगर ((drv = driver_find(buf, &gameport_bus)) != शून्य) अणु
		gameport_disconnect_port(gameport);
		error = gameport_bind_driver(gameport, to_gameport_driver(drv));
	पूर्ण अन्यथा अणु
		error = -EINVAL;
	पूर्ण

	mutex_unlock(&gameport_mutex);

	वापस error ? error : count;
पूर्ण
अटल DEVICE_ATTR_WO(drvctl);

अटल काष्ठा attribute *gameport_device_attrs[] = अणु
	&dev_attr_description.attr,
	&dev_attr_drvctl.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(gameport_device);

अटल व्योम gameport_release_port(काष्ठा device *dev)
अणु
	काष्ठा gameport *gameport = to_gameport_port(dev);

	kमुक्त(gameport);
	module_put(THIS_MODULE);
पूर्ण

व्योम gameport_set_phys(काष्ठा gameport *gameport, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(gameport->phys, माप(gameport->phys), fmt, args);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(gameport_set_phys);

/*
 * Prepare gameport port क्रम registration.
 */
अटल व्योम gameport_init_port(काष्ठा gameport *gameport)
अणु
	अटल atomic_t gameport_no = ATOMIC_INIT(-1);

	__module_get(THIS_MODULE);

	mutex_init(&gameport->drv_mutex);
	device_initialize(&gameport->dev);
	dev_set_name(&gameport->dev, "gameport%lu",
			(अचिन्हित दीर्घ)atomic_inc_वापस(&gameport_no));
	gameport->dev.bus = &gameport_bus;
	gameport->dev.release = gameport_release_port;
	अगर (gameport->parent)
		gameport->dev.parent = &gameport->parent->dev;

	INIT_LIST_HEAD(&gameport->node);
	spin_lock_init(&gameport->समयr_lock);
	समयr_setup(&gameport->poll_समयr, gameport_run_poll_handler, 0);
पूर्ण

/*
 * Complete gameport port registration.
 * Driver core will attempt to find appropriate driver क्रम the port.
 */
अटल व्योम gameport_add_port(काष्ठा gameport *gameport)
अणु
	पूर्णांक error;

	अगर (gameport->parent)
		gameport->parent->child = gameport;

	gameport->speed = use_kसमय ?
		gameport_measure_speed(gameport) :
		old_gameport_measure_speed(gameport);

	list_add_tail(&gameport->node, &gameport_list);

	अगर (gameport->io)
		dev_info(&gameport->dev, "%s is %s, io %#x, speed %dkHz\n",
			 gameport->name, gameport->phys, gameport->io, gameport->speed);
	अन्यथा
		dev_info(&gameport->dev, "%s is %s, speed %dkHz\n",
			gameport->name, gameport->phys, gameport->speed);

	error = device_add(&gameport->dev);
	अगर (error)
		dev_err(&gameport->dev,
			"device_add() failed for %s (%s), error: %d\n",
			gameport->phys, gameport->name, error);
पूर्ण

/*
 * gameport_destroy_port() completes deregistration process and हटाओs
 * port from the प्रणाली
 */
अटल व्योम gameport_destroy_port(काष्ठा gameport *gameport)
अणु
	काष्ठा gameport *child;

	child = gameport_get_pending_child(gameport);
	अगर (child) अणु
		gameport_हटाओ_pending_events(child);
		put_device(&child->dev);
	पूर्ण

	अगर (gameport->parent) अणु
		gameport->parent->child = शून्य;
		gameport->parent = शून्य;
	पूर्ण

	अगर (device_is_रेजिस्टरed(&gameport->dev))
		device_del(&gameport->dev);

	list_del_init(&gameport->node);

	gameport_हटाओ_pending_events(gameport);
	put_device(&gameport->dev);
पूर्ण

/*
 * Reconnect gameport port and all its children (re-initialize attached devices)
 */
अटल व्योम gameport_reconnect_port(काष्ठा gameport *gameport)
अणु
	करो अणु
		अगर (!gameport->drv || !gameport->drv->reconnect || gameport->drv->reconnect(gameport)) अणु
			gameport_disconnect_port(gameport);
			gameport_find_driver(gameport);
			/* Ok, old children are now gone, we are करोne */
			अवरोध;
		पूर्ण
		gameport = gameport->child;
	पूर्ण जबतक (gameport);
पूर्ण

/*
 * gameport_disconnect_port() unbinds a port from its driver. As a side effect
 * all child ports are unbound and destroyed.
 */
अटल व्योम gameport_disconnect_port(काष्ठा gameport *gameport)
अणु
	काष्ठा gameport *s, *parent;

	अगर (gameport->child) अणु
		/*
		 * Children ports should be disconnected and destroyed
		 * first, staring with the leaf one, since we करोn't want
		 * to करो recursion
		 */
		क्रम (s = gameport; s->child; s = s->child)
			/* empty */;

		करो अणु
			parent = s->parent;

			device_release_driver(&s->dev);
			gameport_destroy_port(s);
		पूर्ण जबतक ((s = parent) != gameport);
	पूर्ण

	/*
	 * Ok, no children left, now disconnect this port
	 */
	device_release_driver(&gameport->dev);
पूर्ण

/*
 * Submits रेजिस्टर request to kgameportd क्रम subsequent execution.
 * Note that port registration is always asynchronous.
 */
व्योम __gameport_रेजिस्टर_port(काष्ठा gameport *gameport, काष्ठा module *owner)
अणु
	gameport_init_port(gameport);
	gameport_queue_event(gameport, owner, GAMEPORT_REGISTER_PORT);
पूर्ण
EXPORT_SYMBOL(__gameport_रेजिस्टर_port);

/*
 * Synchronously unरेजिस्टरs gameport port.
 */
व्योम gameport_unरेजिस्टर_port(काष्ठा gameport *gameport)
अणु
	mutex_lock(&gameport_mutex);
	gameport_disconnect_port(gameport);
	gameport_destroy_port(gameport);
	mutex_unlock(&gameport_mutex);
पूर्ण
EXPORT_SYMBOL(gameport_unरेजिस्टर_port);


/*
 * Gameport driver operations
 */

अटल sमाप_प्रकार description_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	काष्ठा gameport_driver *driver = to_gameport_driver(drv);
	वापस प्र_लिखो(buf, "%s\n", driver->description ? driver->description : "(none)");
पूर्ण
अटल DRIVER_ATTR_RO(description);

अटल काष्ठा attribute *gameport_driver_attrs[] = अणु
	&driver_attr_description.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(gameport_driver);

अटल पूर्णांक gameport_driver_probe(काष्ठा device *dev)
अणु
	काष्ठा gameport *gameport = to_gameport_port(dev);
	काष्ठा gameport_driver *drv = to_gameport_driver(dev->driver);

	drv->connect(gameport, drv);
	वापस gameport->drv ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक gameport_driver_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा gameport *gameport = to_gameport_port(dev);
	काष्ठा gameport_driver *drv = to_gameport_driver(dev->driver);

	drv->disconnect(gameport);
	वापस 0;
पूर्ण

अटल व्योम gameport_attach_driver(काष्ठा gameport_driver *drv)
अणु
	पूर्णांक error;

	error = driver_attach(&drv->driver);
	अगर (error)
		pr_err("driver_attach() failed for %s, error: %d\n",
			drv->driver.name, error);
पूर्ण

पूर्णांक __gameport_रेजिस्टर_driver(काष्ठा gameport_driver *drv, काष्ठा module *owner,
				स्थिर अक्षर *mod_name)
अणु
	पूर्णांक error;

	drv->driver.bus = &gameport_bus;
	drv->driver.owner = owner;
	drv->driver.mod_name = mod_name;

	/*
	 * Temporarily disable स्वतःmatic binding because probing
	 * takes दीर्घ समय and we are better off करोing it in kgameportd
	 */
	drv->ignore = true;

	error = driver_रेजिस्टर(&drv->driver);
	अगर (error) अणु
		pr_err("driver_register() failed for %s, error: %d\n",
			drv->driver.name, error);
		वापस error;
	पूर्ण

	/*
	 * Reset ignore flag and let kgameportd bind the driver to मुक्त ports
	 */
	drv->ignore = false;
	error = gameport_queue_event(drv, शून्य, GAMEPORT_ATTACH_DRIVER);
	अगर (error) अणु
		driver_unरेजिस्टर(&drv->driver);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__gameport_रेजिस्टर_driver);

व्योम gameport_unरेजिस्टर_driver(काष्ठा gameport_driver *drv)
अणु
	काष्ठा gameport *gameport;

	mutex_lock(&gameport_mutex);

	drv->ignore = true;	/* so gameport_find_driver ignores it */
	gameport_हटाओ_pending_events(drv);

start_over:
	list_क्रम_each_entry(gameport, &gameport_list, node) अणु
		अगर (gameport->drv == drv) अणु
			gameport_disconnect_port(gameport);
			gameport_find_driver(gameport);
			/* we could've deleted some ports, restart */
			जाओ start_over;
		पूर्ण
	पूर्ण

	driver_unरेजिस्टर(&drv->driver);

	mutex_unlock(&gameport_mutex);
पूर्ण
EXPORT_SYMBOL(gameport_unरेजिस्टर_driver);

अटल पूर्णांक gameport_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा gameport_driver *gameport_drv = to_gameport_driver(drv);

	वापस !gameport_drv->ignore;
पूर्ण

अटल काष्ठा bus_type gameport_bus = अणु
	.name		= "gameport",
	.dev_groups	= gameport_device_groups,
	.drv_groups	= gameport_driver_groups,
	.match		= gameport_bus_match,
	.probe		= gameport_driver_probe,
	.हटाओ		= gameport_driver_हटाओ,
पूर्ण;

अटल व्योम gameport_set_drv(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	mutex_lock(&gameport->drv_mutex);
	gameport->drv = drv;
	mutex_unlock(&gameport->drv_mutex);
पूर्ण

पूर्णांक gameport_खोलो(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv, पूर्णांक mode)
अणु
	अगर (gameport->खोलो) अणु
		अगर (gameport->खोलो(gameport, mode)) अणु
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mode != GAMEPORT_MODE_RAW)
			वापस -1;
	पूर्ण

	gameport_set_drv(gameport, drv);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(gameport_खोलो);

व्योम gameport_बंद(काष्ठा gameport *gameport)
अणु
	del_समयr_sync(&gameport->poll_समयr);
	gameport->poll_handler = शून्य;
	gameport->poll_पूर्णांकerval = 0;
	gameport_set_drv(gameport, शून्य);
	अगर (gameport->बंद)
		gameport->बंद(gameport);
पूर्ण
EXPORT_SYMBOL(gameport_बंद);

अटल पूर्णांक __init gameport_init(व्योम)
अणु
	पूर्णांक error;

	error = bus_रेजिस्टर(&gameport_bus);
	अगर (error) अणु
		pr_err("failed to register gameport bus, error: %d\n", error);
		वापस error;
	पूर्ण


	वापस 0;
पूर्ण

अटल व्योम __निकास gameport_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&gameport_bus);

	/*
	 * There should not be any outstanding events but work may
	 * still be scheduled so simply cancel it.
	 */
	cancel_work_sync(&gameport_event_work);
पूर्ण

subsys_initcall(gameport_init);
module_निकास(gameport_निकास);
