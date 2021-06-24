<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/export.h>
#समावेश <linux/moduleparam.h>

#समावेश "w1_internal.h"
#समावेश "w1_netlink.h"

अटल पूर्णांक w1_search_count = -1; /* Default is continual scan */
module_param_named(search_count, w1_search_count, पूर्णांक, 0);

अटल पूर्णांक w1_enable_pullup = 1;
module_param_named(enable_pullup, w1_enable_pullup, पूर्णांक, 0);

अटल काष्ठा w1_master *w1_alloc_dev(u32 id, पूर्णांक slave_count, पूर्णांक slave_ttl,
				       काष्ठा device_driver *driver,
				       काष्ठा device *device)
अणु
	काष्ठा w1_master *dev;
	पूर्णांक err;

	/*
	 * We are in process context(kernel thपढ़ो), so can sleep.
	 */
	dev = kzalloc(माप(काष्ठा w1_master) + माप(काष्ठा w1_bus_master), GFP_KERNEL);
	अगर (!dev) अणु
		pr_err("Failed to allocate %zd bytes for new w1 device.\n",
			माप(काष्ठा w1_master));
		वापस शून्य;
	पूर्ण


	dev->bus_master = (काष्ठा w1_bus_master *)(dev + 1);

	dev->owner		= THIS_MODULE;
	dev->max_slave_count	= slave_count;
	dev->slave_count	= 0;
	dev->attempts		= 0;
	dev->initialized	= 0;
	dev->id			= id;
	dev->slave_ttl		= slave_ttl;
	dev->search_count	= w1_search_count;
	dev->enable_pullup	= w1_enable_pullup;

	/* 1 क्रम w1_process to decrement
	 * 1 क्रम __w1_हटाओ_master_device to decrement
	 */
	atomic_set(&dev->refcnt, 2);

	INIT_LIST_HEAD(&dev->slist);
	INIT_LIST_HEAD(&dev->async_list);
	mutex_init(&dev->mutex);
	mutex_init(&dev->bus_mutex);
	mutex_init(&dev->list_mutex);

	स_नकल(&dev->dev, device, माप(काष्ठा device));
	dev_set_name(&dev->dev, "w1_bus_master%u", dev->id);
	snम_लिखो(dev->name, माप(dev->name), "w1_bus_master%u", dev->id);
	dev->dev.init_name = dev->name;

	dev->driver = driver;

	dev->seq = 1;

	err = device_रेजिस्टर(&dev->dev);
	अगर (err) अणु
		pr_err("Failed to register master device. err=%d\n", err);
		put_device(&dev->dev);
		dev = शून्य;
	पूर्ण

	वापस dev;
पूर्ण

अटल व्योम w1_मुक्त_dev(काष्ठा w1_master *dev)
अणु
	device_unरेजिस्टर(&dev->dev);
पूर्ण

/**
 * w1_add_master_device() - रेजिस्टरs a new master device
 * @master:	master bus device to रेजिस्टर
 */
पूर्णांक w1_add_master_device(काष्ठा w1_bus_master *master)
अणु
	काष्ठा w1_master *dev, *entry;
	पूर्णांक retval = 0;
	काष्ठा w1_netlink_msg msg;
	पूर्णांक id, found;

	/* validate minimum functionality */
	अगर (!(master->touch_bit && master->reset_bus) &&
	    !(master->ग_लिखो_bit && master->पढ़ो_bit) &&
	    !(master->ग_लिखो_byte && master->पढ़ो_byte && master->reset_bus)) अणु
		pr_err("w1_add_master_device: invalid function set\n");
		वापस(-EINVAL);
	पूर्ण

	/* Lock until the device is added (or not) to w1_masters. */
	mutex_lock(&w1_mlock);
	/* Search क्रम the first available id (starting at 1). */
	id = 0;
	करो अणु
		++id;
		found = 0;
		list_क्रम_each_entry(entry, &w1_masters, w1_master_entry) अणु
			अगर (entry->id == id) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (found);

	dev = w1_alloc_dev(id, w1_max_slave_count, w1_max_slave_ttl,
		&w1_master_driver, &w1_master_device);
	अगर (!dev) अणु
		mutex_unlock(&w1_mlock);
		वापस -ENOMEM;
	पूर्ण

	retval =  w1_create_master_attributes(dev);
	अगर (retval) अणु
		mutex_unlock(&w1_mlock);
		जाओ err_out_मुक्त_dev;
	पूर्ण

	स_नकल(dev->bus_master, master, माप(काष्ठा w1_bus_master));

	dev->initialized = 1;

	dev->thपढ़ो = kthपढ़ो_run(&w1_process, dev, "%s", dev->name);
	अगर (IS_ERR(dev->thपढ़ो)) अणु
		retval = PTR_ERR(dev->thपढ़ो);
		dev_err(&dev->dev,
			 "Failed to create new kernel thread. err=%d\n",
			 retval);
		mutex_unlock(&w1_mlock);
		जाओ err_out_rm_attr;
	पूर्ण

	list_add(&dev->w1_master_entry, &w1_masters);
	mutex_unlock(&w1_mlock);

	स_रखो(&msg, 0, माप(msg));
	msg.id.mst.id = dev->id;
	msg.type = W1_MASTER_ADD;
	w1_netlink_send(dev, &msg);

	वापस 0;

#अगर 0 /* Thपढ़ो cleanup code, not required currently. */
err_out_समाप्त_thपढ़ो:
	set_bit(W1_ABORT_SEARCH, &dev->flags);
	kthपढ़ो_stop(dev->thपढ़ो);
#पूर्ण_अगर
err_out_rm_attr:
	w1_destroy_master_attributes(dev);
err_out_मुक्त_dev:
	w1_मुक्त_dev(dev);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(w1_add_master_device);

व्योम __w1_हटाओ_master_device(काष्ठा w1_master *dev)
अणु
	काष्ठा w1_netlink_msg msg;
	काष्ठा w1_slave *sl, *sln;

	mutex_lock(&w1_mlock);
	list_del(&dev->w1_master_entry);
	mutex_unlock(&w1_mlock);

	set_bit(W1_ABORT_SEARCH, &dev->flags);
	kthपढ़ो_stop(dev->thपढ़ो);

	mutex_lock(&dev->mutex);
	mutex_lock(&dev->list_mutex);
	list_क्रम_each_entry_safe(sl, sln, &dev->slist, w1_slave_entry) अणु
		mutex_unlock(&dev->list_mutex);
		w1_slave_detach(sl);
		mutex_lock(&dev->list_mutex);
	पूर्ण
	w1_destroy_master_attributes(dev);
	mutex_unlock(&dev->list_mutex);
	mutex_unlock(&dev->mutex);
	atomic_dec(&dev->refcnt);

	जबतक (atomic_पढ़ो(&dev->refcnt)) अणु
		dev_info(&dev->dev, "Waiting for %s to become free: refcnt=%d.\n",
				dev->name, atomic_पढ़ो(&dev->refcnt));

		अगर (msleep_पूर्णांकerruptible(1000))
			flush_संकेतs(current);
		mutex_lock(&dev->list_mutex);
		w1_process_callbacks(dev);
		mutex_unlock(&dev->list_mutex);
	पूर्ण
	mutex_lock(&dev->list_mutex);
	w1_process_callbacks(dev);
	mutex_unlock(&dev->list_mutex);

	स_रखो(&msg, 0, माप(msg));
	msg.id.mst.id = dev->id;
	msg.type = W1_MASTER_REMOVE;
	w1_netlink_send(dev, &msg);

	w1_मुक्त_dev(dev);
पूर्ण

/**
 * w1_हटाओ_master_device() - unरेजिस्टर a master device
 * @bm:	master bus device to हटाओ
 */
व्योम w1_हटाओ_master_device(काष्ठा w1_bus_master *bm)
अणु
	काष्ठा w1_master *dev, *found = शून्य;

	list_क्रम_each_entry(dev, &w1_masters, w1_master_entry) अणु
		अगर (!dev->initialized)
			जारी;

		अगर (dev->bus_master->data == bm->data) अणु
			found = dev;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		pr_err("Device doesn't exist.\n");
		वापस;
	पूर्ण

	__w1_हटाओ_master_device(found);
पूर्ण
EXPORT_SYMBOL(w1_हटाओ_master_device);
