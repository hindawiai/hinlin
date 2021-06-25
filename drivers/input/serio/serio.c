<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  The Serio असलtraction module
 *
 *  Copyright (c) 1999-2004 Vojtech Pavlik
 *  Copyright (c) 2004 Dmitry Torokhov
 *  Copyright (c) 2003 Daniele Bellucci
 */

/*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/मानकघोष.स>
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Serio abstraction core");
MODULE_LICENSE("GPL");

/*
 * serio_mutex protects entire serio subप्रणाली and is taken every समय
 * serio port or driver रेजिस्टरed or unरेजिस्टरed.
 */
अटल DEFINE_MUTEX(serio_mutex);

अटल LIST_HEAD(serio_list);

अटल व्योम serio_add_port(काष्ठा serio *serio);
अटल पूर्णांक serio_reconnect_port(काष्ठा serio *serio);
अटल व्योम serio_disconnect_port(काष्ठा serio *serio);
अटल व्योम serio_reconnect_subtree(काष्ठा serio *serio);
अटल व्योम serio_attach_driver(काष्ठा serio_driver *drv);

अटल पूर्णांक serio_connect_driver(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	पूर्णांक retval;

	mutex_lock(&serio->drv_mutex);
	retval = drv->connect(serio, drv);
	mutex_unlock(&serio->drv_mutex);

	वापस retval;
पूर्ण

अटल पूर्णांक serio_reconnect_driver(काष्ठा serio *serio)
अणु
	पूर्णांक retval = -1;

	mutex_lock(&serio->drv_mutex);
	अगर (serio->drv && serio->drv->reconnect)
		retval = serio->drv->reconnect(serio);
	mutex_unlock(&serio->drv_mutex);

	वापस retval;
पूर्ण

अटल व्योम serio_disconnect_driver(काष्ठा serio *serio)
अणु
	mutex_lock(&serio->drv_mutex);
	अगर (serio->drv)
		serio->drv->disconnect(serio);
	mutex_unlock(&serio->drv_mutex);
पूर्ण

अटल पूर्णांक serio_match_port(स्थिर काष्ठा serio_device_id *ids, काष्ठा serio *serio)
अणु
	जबतक (ids->type || ids->proto) अणु
		अगर ((ids->type == SERIO_ANY || ids->type == serio->id.type) &&
		    (ids->proto == SERIO_ANY || ids->proto == serio->id.proto) &&
		    (ids->extra == SERIO_ANY || ids->extra == serio->id.extra) &&
		    (ids->id == SERIO_ANY || ids->id == serio->id.id))
			वापस 1;
		ids++;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Basic serio -> driver core mappings
 */

अटल पूर्णांक serio_bind_driver(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	पूर्णांक error;

	अगर (serio_match_port(drv->id_table, serio)) अणु

		serio->dev.driver = &drv->driver;
		अगर (serio_connect_driver(serio, drv)) अणु
			serio->dev.driver = शून्य;
			वापस -ENODEV;
		पूर्ण

		error = device_bind_driver(&serio->dev);
		अगर (error) अणु
			dev_warn(&serio->dev,
				 "device_bind_driver() failed for %s (%s) and %s, error: %d\n",
				 serio->phys, serio->name,
				 drv->description, error);
			serio_disconnect_driver(serio);
			serio->dev.driver = शून्य;
			वापस error;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम serio_find_driver(काष्ठा serio *serio)
अणु
	पूर्णांक error;

	error = device_attach(&serio->dev);
	अगर (error < 0 && error != -EPROBE_DEFER)
		dev_warn(&serio->dev,
			 "device_attach() failed for %s (%s), error: %d\n",
			 serio->phys, serio->name, error);
पूर्ण


/*
 * Serio event processing.
 */

क्रमागत serio_event_type अणु
	SERIO_RESCAN_PORT,
	SERIO_RECONNECT_PORT,
	SERIO_RECONNECT_SUBTREE,
	SERIO_REGISTER_PORT,
	SERIO_ATTACH_DRIVER,
पूर्ण;

काष्ठा serio_event अणु
	क्रमागत serio_event_type type;
	व्योम *object;
	काष्ठा module *owner;
	काष्ठा list_head node;
पूर्ण;

अटल DEFINE_SPINLOCK(serio_event_lock);	/* protects serio_event_list */
अटल LIST_HEAD(serio_event_list);

अटल काष्ठा serio_event *serio_get_event(व्योम)
अणु
	काष्ठा serio_event *event = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serio_event_lock, flags);

	अगर (!list_empty(&serio_event_list)) अणु
		event = list_first_entry(&serio_event_list,
					 काष्ठा serio_event, node);
		list_del_init(&event->node);
	पूर्ण

	spin_unlock_irqrestore(&serio_event_lock, flags);
	वापस event;
पूर्ण

अटल व्योम serio_मुक्त_event(काष्ठा serio_event *event)
अणु
	module_put(event->owner);
	kमुक्त(event);
पूर्ण

अटल व्योम serio_हटाओ_duplicate_events(व्योम *object,
					  क्रमागत serio_event_type type)
अणु
	काष्ठा serio_event *e, *next;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serio_event_lock, flags);

	list_क्रम_each_entry_safe(e, next, &serio_event_list, node) अणु
		अगर (object == e->object) अणु
			/*
			 * If this event is of dअगरferent type we should not
			 * look further - we only suppress duplicate events
			 * that were sent back-to-back.
			 */
			अगर (type != e->type)
				अवरोध;

			list_del_init(&e->node);
			serio_मुक्त_event(e);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&serio_event_lock, flags);
पूर्ण

अटल व्योम serio_handle_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा serio_event *event;

	mutex_lock(&serio_mutex);

	जबतक ((event = serio_get_event())) अणु

		चयन (event->type) अणु

		हाल SERIO_REGISTER_PORT:
			serio_add_port(event->object);
			अवरोध;

		हाल SERIO_RECONNECT_PORT:
			serio_reconnect_port(event->object);
			अवरोध;

		हाल SERIO_RESCAN_PORT:
			serio_disconnect_port(event->object);
			serio_find_driver(event->object);
			अवरोध;

		हाल SERIO_RECONNECT_SUBTREE:
			serio_reconnect_subtree(event->object);
			अवरोध;

		हाल SERIO_ATTACH_DRIVER:
			serio_attach_driver(event->object);
			अवरोध;
		पूर्ण

		serio_हटाओ_duplicate_events(event->object, event->type);
		serio_मुक्त_event(event);
	पूर्ण

	mutex_unlock(&serio_mutex);
पूर्ण

अटल DECLARE_WORK(serio_event_work, serio_handle_event);

अटल पूर्णांक serio_queue_event(व्योम *object, काष्ठा module *owner,
			     क्रमागत serio_event_type event_type)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा serio_event *event;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&serio_event_lock, flags);

	/*
	 * Scan event list क्रम the other events क्रम the same serio port,
	 * starting with the most recent one. If event is the same we
	 * करो not need add new one. If event is of dअगरferent type we
	 * need to add this event and should not look further because
	 * we need to preseve sequence of distinct events.
	 */
	list_क्रम_each_entry_reverse(event, &serio_event_list, node) अणु
		अगर (event->object == object) अणु
			अगर (event->type == event_type)
				जाओ out;
			अवरोध;
		पूर्ण
	पूर्ण

	event = kदो_स्मृति(माप(काष्ठा serio_event), GFP_ATOMIC);
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

	list_add_tail(&event->node, &serio_event_list);
	queue_work(प्रणाली_दीर्घ_wq, &serio_event_work);

out:
	spin_unlock_irqrestore(&serio_event_lock, flags);
	वापस retval;
पूर्ण

/*
 * Remove all events that have been submitted क्रम a given
 * object, be it serio port or driver.
 */
अटल व्योम serio_हटाओ_pending_events(व्योम *object)
अणु
	काष्ठा serio_event *event, *next;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serio_event_lock, flags);

	list_क्रम_each_entry_safe(event, next, &serio_event_list, node) अणु
		अगर (event->object == object) अणु
			list_del_init(&event->node);
			serio_मुक्त_event(event);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&serio_event_lock, flags);
पूर्ण

/*
 * Locate child serio port (अगर any) that has not been fully रेजिस्टरed yet.
 *
 * Children are रेजिस्टरed by driver's connect() handler so there can't be a
 * gअक्रमchild pending registration together with a child.
 */
अटल काष्ठा serio *serio_get_pending_child(काष्ठा serio *parent)
अणु
	काष्ठा serio_event *event;
	काष्ठा serio *serio, *child = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serio_event_lock, flags);

	list_क्रम_each_entry(event, &serio_event_list, node) अणु
		अगर (event->type == SERIO_REGISTER_PORT) अणु
			serio = event->object;
			अगर (serio->parent == parent) अणु
				child = serio;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&serio_event_lock, flags);
	वापस child;
पूर्ण

/*
 * Serio port operations
 */

अटल sमाप_प्रकार serio_show_description(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	वापस प्र_लिखो(buf, "%s\n", serio->name);
पूर्ण

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serio *serio = to_serio_port(dev);

	वापस प्र_लिखो(buf, "serio:ty%02Xpr%02Xid%02Xex%02X\n",
			serio->id.type, serio->id.proto, serio->id.id, serio->id.extra);
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	वापस प्र_लिखो(buf, "%02x\n", serio->id.type);
पूर्ण

अटल sमाप_प्रकार proto_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	वापस प्र_लिखो(buf, "%02x\n", serio->id.proto);
पूर्ण

अटल sमाप_प्रकार id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	वापस प्र_लिखो(buf, "%02x\n", serio->id.id);
पूर्ण

अटल sमाप_प्रकार extra_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	वापस प्र_लिखो(buf, "%02x\n", serio->id.extra);
पूर्ण

अटल sमाप_प्रकार drvctl_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा device_driver *drv;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&serio_mutex);
	अगर (error)
		वापस error;

	अगर (!म_भेदन(buf, "none", count)) अणु
		serio_disconnect_port(serio);
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "reconnect", count)) अणु
		serio_reconnect_subtree(serio);
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "rescan", count)) अणु
		serio_disconnect_port(serio);
		serio_find_driver(serio);
		serio_हटाओ_duplicate_events(serio, SERIO_RESCAN_PORT);
	पूर्ण अन्यथा अगर ((drv = driver_find(buf, &serio_bus)) != शून्य) अणु
		serio_disconnect_port(serio);
		error = serio_bind_driver(serio, to_serio_driver(drv));
		serio_हटाओ_duplicate_events(serio, SERIO_RESCAN_PORT);
	पूर्ण अन्यथा अणु
		error = -EINVAL;
	पूर्ण

	mutex_unlock(&serio_mutex);

	वापस error ? error : count;
पूर्ण

अटल sमाप_प्रकार serio_show_bind_mode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	वापस प्र_लिखो(buf, "%s\n", serio->manual_bind ? "manual" : "auto");
पूर्ण

अटल sमाप_प्रकार serio_set_bind_mode(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	पूर्णांक retval;

	retval = count;
	अगर (!म_भेदन(buf, "manual", count)) अणु
		serio->manual_bind = true;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "auto", count)) अणु
		serio->manual_bind = false;
	पूर्ण अन्यथा अणु
		retval = -EINVAL;
	पूर्ण

	वापस retval;
पूर्ण

अटल sमाप_प्रकार firmware_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serio *serio = to_serio_port(dev);

	वापस प्र_लिखो(buf, "%s\n", serio->firmware_id);
पूर्ण

अटल DEVICE_ATTR_RO(type);
अटल DEVICE_ATTR_RO(proto);
अटल DEVICE_ATTR_RO(id);
अटल DEVICE_ATTR_RO(extra);

अटल काष्ठा attribute *serio_device_id_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_proto.attr,
	&dev_attr_id.attr,
	&dev_attr_extra.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group serio_id_attr_group = अणु
	.name	= "id",
	.attrs	= serio_device_id_attrs,
पूर्ण;

अटल DEVICE_ATTR_RO(modalias);
अटल DEVICE_ATTR_WO(drvctl);
अटल DEVICE_ATTR(description, S_IRUGO, serio_show_description, शून्य);
अटल DEVICE_ATTR(bind_mode, S_IWUSR | S_IRUGO, serio_show_bind_mode, serio_set_bind_mode);
अटल DEVICE_ATTR_RO(firmware_id);

अटल काष्ठा attribute *serio_device_attrs[] = अणु
	&dev_attr_modalias.attr,
	&dev_attr_description.attr,
	&dev_attr_drvctl.attr,
	&dev_attr_bind_mode.attr,
	&dev_attr_firmware_id.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group serio_device_attr_group = अणु
	.attrs	= serio_device_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *serio_device_attr_groups[] = अणु
	&serio_id_attr_group,
	&serio_device_attr_group,
	शून्य
पूर्ण;

अटल व्योम serio_release_port(काष्ठा device *dev)
अणु
	काष्ठा serio *serio = to_serio_port(dev);

	kमुक्त(serio);
	module_put(THIS_MODULE);
पूर्ण

/*
 * Prepare serio port क्रम registration.
 */
अटल व्योम serio_init_port(काष्ठा serio *serio)
अणु
	अटल atomic_t serio_no = ATOMIC_INIT(-1);

	__module_get(THIS_MODULE);

	INIT_LIST_HEAD(&serio->node);
	INIT_LIST_HEAD(&serio->child_node);
	INIT_LIST_HEAD(&serio->children);
	spin_lock_init(&serio->lock);
	mutex_init(&serio->drv_mutex);
	device_initialize(&serio->dev);
	dev_set_name(&serio->dev, "serio%lu",
		     (अचिन्हित दीर्घ)atomic_inc_वापस(&serio_no));
	serio->dev.bus = &serio_bus;
	serio->dev.release = serio_release_port;
	serio->dev.groups = serio_device_attr_groups;
	अगर (serio->parent) अणु
		serio->dev.parent = &serio->parent->dev;
		serio->depth = serio->parent->depth + 1;
	पूर्ण अन्यथा
		serio->depth = 0;
	lockdep_set_subclass(&serio->lock, serio->depth);
पूर्ण

/*
 * Complete serio port registration.
 * Driver core will attempt to find appropriate driver क्रम the port.
 */
अटल व्योम serio_add_port(काष्ठा serio *serio)
अणु
	काष्ठा serio *parent = serio->parent;
	पूर्णांक error;

	अगर (parent) अणु
		serio_छोड़ो_rx(parent);
		list_add_tail(&serio->child_node, &parent->children);
		serio_जारी_rx(parent);
	पूर्ण

	list_add_tail(&serio->node, &serio_list);

	अगर (serio->start)
		serio->start(serio);

	error = device_add(&serio->dev);
	अगर (error)
		dev_err(&serio->dev,
			"device_add() failed for %s (%s), error: %d\n",
			serio->phys, serio->name, error);
पूर्ण

/*
 * serio_destroy_port() completes unregistration process and हटाओs
 * port from the प्रणाली
 */
अटल व्योम serio_destroy_port(काष्ठा serio *serio)
अणु
	काष्ठा serio *child;

	जबतक ((child = serio_get_pending_child(serio)) != शून्य) अणु
		serio_हटाओ_pending_events(child);
		put_device(&child->dev);
	पूर्ण

	अगर (serio->stop)
		serio->stop(serio);

	अगर (serio->parent) अणु
		serio_छोड़ो_rx(serio->parent);
		list_del_init(&serio->child_node);
		serio_जारी_rx(serio->parent);
		serio->parent = शून्य;
	पूर्ण

	अगर (device_is_रेजिस्टरed(&serio->dev))
		device_del(&serio->dev);

	list_del_init(&serio->node);
	serio_हटाओ_pending_events(serio);
	put_device(&serio->dev);
पूर्ण

/*
 * Reconnect serio port (re-initialize attached device).
 * If reconnect fails (old device is no दीर्घer attached or
 * there was no device to begin with) we करो full rescan in
 * hope of finding a driver क्रम the port.
 */
अटल पूर्णांक serio_reconnect_port(काष्ठा serio *serio)
अणु
	पूर्णांक error = serio_reconnect_driver(serio);

	अगर (error) अणु
		serio_disconnect_port(serio);
		serio_find_driver(serio);
	पूर्ण

	वापस error;
पूर्ण

/*
 * Reconnect serio port and all its children (re-initialize attached
 * devices).
 */
अटल व्योम serio_reconnect_subtree(काष्ठा serio *root)
अणु
	काष्ठा serio *s = root;
	पूर्णांक error;

	करो अणु
		error = serio_reconnect_port(s);
		अगर (!error) अणु
			/*
			 * Reconnect was successful, move on to करो the
			 * first child.
			 */
			अगर (!list_empty(&s->children)) अणु
				s = list_first_entry(&s->children,
						     काष्ठा serio, child_node);
				जारी;
			पूर्ण
		पूर्ण

		/*
		 * Either it was a leaf node or reconnect failed and it
		 * became a leaf node. Continue reconnecting starting with
		 * the next sibling of the parent node.
		 */
		जबतक (s != root) अणु
			काष्ठा serio *parent = s->parent;

			अगर (!list_is_last(&s->child_node, &parent->children)) अणु
				s = list_entry(s->child_node.next,
					       काष्ठा serio, child_node);
				अवरोध;
			पूर्ण

			s = parent;
		पूर्ण
	पूर्ण जबतक (s != root);
पूर्ण

/*
 * serio_disconnect_port() unbinds a port from its driver. As a side effect
 * all children ports are unbound and destroyed.
 */
अटल व्योम serio_disconnect_port(काष्ठा serio *serio)
अणु
	काष्ठा serio *s = serio;

	/*
	 * Children ports should be disconnected and destroyed
	 * first; we travel the tree in depth-first order.
	 */
	जबतक (!list_empty(&serio->children)) अणु

		/* Locate a leaf */
		जबतक (!list_empty(&s->children))
			s = list_first_entry(&s->children,
					     काष्ठा serio, child_node);

		/*
		 * Prune this leaf node unless it is the one we
		 * started with.
		 */
		अगर (s != serio) अणु
			काष्ठा serio *parent = s->parent;

			device_release_driver(&s->dev);
			serio_destroy_port(s);

			s = parent;
		पूर्ण
	पूर्ण

	/*
	 * OK, no children left, now disconnect this port.
	 */
	device_release_driver(&serio->dev);
पूर्ण

व्योम serio_rescan(काष्ठा serio *serio)
अणु
	serio_queue_event(serio, शून्य, SERIO_RESCAN_PORT);
पूर्ण
EXPORT_SYMBOL(serio_rescan);

व्योम serio_reconnect(काष्ठा serio *serio)
अणु
	serio_queue_event(serio, शून्य, SERIO_RECONNECT_SUBTREE);
पूर्ण
EXPORT_SYMBOL(serio_reconnect);

/*
 * Submits रेजिस्टर request to kseriod क्रम subsequent execution.
 * Note that port registration is always asynchronous.
 */
व्योम __serio_रेजिस्टर_port(काष्ठा serio *serio, काष्ठा module *owner)
अणु
	serio_init_port(serio);
	serio_queue_event(serio, owner, SERIO_REGISTER_PORT);
पूर्ण
EXPORT_SYMBOL(__serio_रेजिस्टर_port);

/*
 * Synchronously unरेजिस्टरs serio port.
 */
व्योम serio_unरेजिस्टर_port(काष्ठा serio *serio)
अणु
	mutex_lock(&serio_mutex);
	serio_disconnect_port(serio);
	serio_destroy_port(serio);
	mutex_unlock(&serio_mutex);
पूर्ण
EXPORT_SYMBOL(serio_unरेजिस्टर_port);

/*
 * Safely unरेजिस्टरs children ports अगर they are present.
 */
व्योम serio_unरेजिस्टर_child_port(काष्ठा serio *serio)
अणु
	काष्ठा serio *s, *next;

	mutex_lock(&serio_mutex);
	list_क्रम_each_entry_safe(s, next, &serio->children, child_node) अणु
		serio_disconnect_port(s);
		serio_destroy_port(s);
	पूर्ण
	mutex_unlock(&serio_mutex);
पूर्ण
EXPORT_SYMBOL(serio_unरेजिस्टर_child_port);


/*
 * Serio driver operations
 */

अटल sमाप_प्रकार description_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	काष्ठा serio_driver *driver = to_serio_driver(drv);
	वापस प्र_लिखो(buf, "%s\n", driver->description ? driver->description : "(none)");
पूर्ण
अटल DRIVER_ATTR_RO(description);

अटल sमाप_प्रकार bind_mode_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	काष्ठा serio_driver *serio_drv = to_serio_driver(drv);
	वापस प्र_लिखो(buf, "%s\n", serio_drv->manual_bind ? "manual" : "auto");
पूर्ण

अटल sमाप_प्रकार bind_mode_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा serio_driver *serio_drv = to_serio_driver(drv);
	पूर्णांक retval;

	retval = count;
	अगर (!म_भेदन(buf, "manual", count)) अणु
		serio_drv->manual_bind = true;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "auto", count)) अणु
		serio_drv->manual_bind = false;
	पूर्ण अन्यथा अणु
		retval = -EINVAL;
	पूर्ण

	वापस retval;
पूर्ण
अटल DRIVER_ATTR_RW(bind_mode);

अटल काष्ठा attribute *serio_driver_attrs[] = अणु
	&driver_attr_description.attr,
	&driver_attr_bind_mode.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(serio_driver);

अटल पूर्णांक serio_driver_probe(काष्ठा device *dev)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा serio_driver *drv = to_serio_driver(dev->driver);

	वापस serio_connect_driver(serio, drv);
पूर्ण

अटल पूर्णांक serio_driver_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा serio *serio = to_serio_port(dev);

	serio_disconnect_driver(serio);
	वापस 0;
पूर्ण

अटल व्योम serio_cleanup(काष्ठा serio *serio)
अणु
	mutex_lock(&serio->drv_mutex);
	अगर (serio->drv && serio->drv->cleanup)
		serio->drv->cleanup(serio);
	mutex_unlock(&serio->drv_mutex);
पूर्ण

अटल व्योम serio_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा serio *serio = to_serio_port(dev);

	serio_cleanup(serio);
पूर्ण

अटल व्योम serio_attach_driver(काष्ठा serio_driver *drv)
अणु
	पूर्णांक error;

	error = driver_attach(&drv->driver);
	अगर (error)
		pr_warn("driver_attach() failed for %s with error %d\n",
			drv->driver.name, error);
पूर्ण

पूर्णांक __serio_रेजिस्टर_driver(काष्ठा serio_driver *drv, काष्ठा module *owner, स्थिर अक्षर *mod_name)
अणु
	bool manual_bind = drv->manual_bind;
	पूर्णांक error;

	drv->driver.bus = &serio_bus;
	drv->driver.owner = owner;
	drv->driver.mod_name = mod_name;

	/*
	 * Temporarily disable स्वतःmatic binding because probing
	 * takes दीर्घ समय and we are better off करोing it in kseriod
	 */
	drv->manual_bind = true;

	error = driver_रेजिस्टर(&drv->driver);
	अगर (error) अणु
		pr_err("driver_register() failed for %s, error: %d\n",
			drv->driver.name, error);
		वापस error;
	पूर्ण

	/*
	 * Restore original bind mode and let kseriod bind the
	 * driver to मुक्त ports
	 */
	अगर (!manual_bind) अणु
		drv->manual_bind = false;
		error = serio_queue_event(drv, शून्य, SERIO_ATTACH_DRIVER);
		अगर (error) अणु
			driver_unरेजिस्टर(&drv->driver);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__serio_रेजिस्टर_driver);

व्योम serio_unरेजिस्टर_driver(काष्ठा serio_driver *drv)
अणु
	काष्ठा serio *serio;

	mutex_lock(&serio_mutex);

	drv->manual_bind = true;	/* so serio_find_driver ignores it */
	serio_हटाओ_pending_events(drv);

start_over:
	list_क्रम_each_entry(serio, &serio_list, node) अणु
		अगर (serio->drv == drv) अणु
			serio_disconnect_port(serio);
			serio_find_driver(serio);
			/* we could've deleted some ports, restart */
			जाओ start_over;
		पूर्ण
	पूर्ण

	driver_unरेजिस्टर(&drv->driver);
	mutex_unlock(&serio_mutex);
पूर्ण
EXPORT_SYMBOL(serio_unरेजिस्टर_driver);

अटल व्योम serio_set_drv(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	serio_छोड़ो_rx(serio);
	serio->drv = drv;
	serio_जारी_rx(serio);
पूर्ण

अटल पूर्णांक serio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा serio_driver *serio_drv = to_serio_driver(drv);

	अगर (serio->manual_bind || serio_drv->manual_bind)
		वापस 0;

	वापस serio_match_port(serio_drv->id_table, serio);
पूर्ण

#घोषणा SERIO_ADD_UEVENT_VAR(fmt, val...)				\
	करो अणु								\
		पूर्णांक err = add_uevent_var(env, fmt, val);		\
		अगर (err)						\
			वापस err;					\
	पूर्ण जबतक (0)

अटल पूर्णांक serio_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा serio *serio;

	अगर (!dev)
		वापस -ENODEV;

	serio = to_serio_port(dev);

	SERIO_ADD_UEVENT_VAR("SERIO_TYPE=%02x", serio->id.type);
	SERIO_ADD_UEVENT_VAR("SERIO_PROTO=%02x", serio->id.proto);
	SERIO_ADD_UEVENT_VAR("SERIO_ID=%02x", serio->id.id);
	SERIO_ADD_UEVENT_VAR("SERIO_EXTRA=%02x", serio->id.extra);

	SERIO_ADD_UEVENT_VAR("MODALIAS=serio:ty%02Xpr%02Xid%02Xex%02X",
				serio->id.type, serio->id.proto, serio->id.id, serio->id.extra);

	अगर (serio->firmware_id[0])
		SERIO_ADD_UEVENT_VAR("SERIO_FIRMWARE_ID=%s",
				     serio->firmware_id);

	वापस 0;
पूर्ण
#अघोषित SERIO_ADD_UEVENT_VAR

#अगर_घोषित CONFIG_PM
अटल पूर्णांक serio_suspend(काष्ठा device *dev)
अणु
	काष्ठा serio *serio = to_serio_port(dev);

	serio_cleanup(serio);

	वापस 0;
पूर्ण

अटल पूर्णांक serio_resume(काष्ठा device *dev)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	पूर्णांक error = -ENOENT;

	mutex_lock(&serio->drv_mutex);
	अगर (serio->drv && serio->drv->fast_reconnect) अणु
		error = serio->drv->fast_reconnect(serio);
		अगर (error && error != -ENOENT)
			dev_warn(dev, "fast reconnect failed with error %d\n",
				 error);
	पूर्ण
	mutex_unlock(&serio->drv_mutex);

	अगर (error) अणु
		/*
		 * Driver reconnect can take a जबतक, so better let
		 * kseriod deal with it.
		 */
		serio_queue_event(serio, शून्य, SERIO_RECONNECT_PORT);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops serio_pm_ops = अणु
	.suspend	= serio_suspend,
	.resume		= serio_resume,
	.घातeroff	= serio_suspend,
	.restore	= serio_resume,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM */

/* called from serio_driver->connect/disconnect methods under serio_mutex */
पूर्णांक serio_खोलो(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	serio_set_drv(serio, drv);

	अगर (serio->खोलो && serio->खोलो(serio)) अणु
		serio_set_drv(serio, शून्य);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(serio_खोलो);

/* called from serio_driver->connect/disconnect methods under serio_mutex */
व्योम serio_बंद(काष्ठा serio *serio)
अणु
	अगर (serio->बंद)
		serio->बंद(serio);

	serio_set_drv(serio, शून्य);
पूर्ण
EXPORT_SYMBOL(serio_बंद);

irqवापस_t serio_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक dfl)
अणु
	अचिन्हित दीर्घ flags;
	irqवापस_t ret = IRQ_NONE;

	spin_lock_irqsave(&serio->lock, flags);

        अगर (likely(serio->drv)) अणु
                ret = serio->drv->पूर्णांकerrupt(serio, data, dfl);
	पूर्ण अन्यथा अगर (!dfl && device_is_रेजिस्टरed(&serio->dev)) अणु
		serio_rescan(serio);
		ret = IRQ_HANDLED;
	पूर्ण

	spin_unlock_irqrestore(&serio->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(serio_पूर्णांकerrupt);

काष्ठा bus_type serio_bus = अणु
	.name		= "serio",
	.drv_groups	= serio_driver_groups,
	.match		= serio_bus_match,
	.uevent		= serio_uevent,
	.probe		= serio_driver_probe,
	.हटाओ		= serio_driver_हटाओ,
	.shutकरोwn	= serio_shutकरोwn,
#अगर_घोषित CONFIG_PM
	.pm		= &serio_pm_ops,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(serio_bus);

अटल पूर्णांक __init serio_init(व्योम)
अणु
	पूर्णांक error;

	error = bus_रेजिस्टर(&serio_bus);
	अगर (error) अणु
		pr_err("Failed to register serio bus, error: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास serio_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&serio_bus);

	/*
	 * There should not be any outstanding events but work may
	 * still be scheduled so simply cancel it.
	 */
	cancel_work_sync(&serio_event_work);
पूर्ण

subsys_initcall(serio_init);
module_निकास(serio_निकास);
