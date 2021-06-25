<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Raw serio device providing access to a raw byte stream from underlying
 * serio port. Closely emulates behavior of pre-2.6 /dev/psaux device
 *
 * Copyright (c) 2004 Dmitry Torokhov
 */

#समावेश <linux/kref.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/major.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>

#घोषणा DRIVER_DESC	"Raw serio driver"

MODULE_AUTHOR("Dmitry Torokhov <dtor@mail.ru>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा SERIO_RAW_QUEUE_LEN	64
काष्ठा serio_raw अणु
	अचिन्हित अक्षर queue[SERIO_RAW_QUEUE_LEN];
	अचिन्हित पूर्णांक tail, head;

	अक्षर name[16];
	काष्ठा kref kref;
	काष्ठा serio *serio;
	काष्ठा miscdevice dev;
	रुको_queue_head_t रुको;
	काष्ठा list_head client_list;
	काष्ठा list_head node;
	bool dead;
पूर्ण;

काष्ठा serio_raw_client अणु
	काष्ठा fasync_काष्ठा *fasync;
	काष्ठा serio_raw *serio_raw;
	काष्ठा list_head node;
पूर्ण;

अटल DEFINE_MUTEX(serio_raw_mutex);
अटल LIST_HEAD(serio_raw_list);

/*********************************************************************
 *             Interface with userspace (file operations)            *
 *********************************************************************/

अटल पूर्णांक serio_raw_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा serio_raw_client *client = file->निजी_data;

	वापस fasync_helper(fd, file, on, &client->fasync);
पूर्ण

अटल काष्ठा serio_raw *serio_raw_locate(पूर्णांक minor)
अणु
	काष्ठा serio_raw *serio_raw;

	list_क्रम_each_entry(serio_raw, &serio_raw_list, node) अणु
		अगर (serio_raw->dev.minor == minor)
			वापस serio_raw;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक serio_raw_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा serio_raw *serio_raw;
	काष्ठा serio_raw_client *client;
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&serio_raw_mutex);
	अगर (retval)
		वापस retval;

	serio_raw = serio_raw_locate(iminor(inode));
	अगर (!serio_raw) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (serio_raw->dead) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	client = kzalloc(माप(काष्ठा serio_raw_client), GFP_KERNEL);
	अगर (!client) अणु
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	client->serio_raw = serio_raw;
	file->निजी_data = client;

	kref_get(&serio_raw->kref);

	serio_छोड़ो_rx(serio_raw->serio);
	list_add_tail(&client->node, &serio_raw->client_list);
	serio_जारी_rx(serio_raw->serio);

out:
	mutex_unlock(&serio_raw_mutex);
	वापस retval;
पूर्ण

अटल व्योम serio_raw_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा serio_raw *serio_raw =
			container_of(kref, काष्ठा serio_raw, kref);

	put_device(&serio_raw->serio->dev);
	kमुक्त(serio_raw);
पूर्ण

अटल पूर्णांक serio_raw_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा serio_raw_client *client = file->निजी_data;
	काष्ठा serio_raw *serio_raw = client->serio_raw;

	serio_छोड़ो_rx(serio_raw->serio);
	list_del(&client->node);
	serio_जारी_rx(serio_raw->serio);

	kमुक्त(client);

	kref_put(&serio_raw->kref, serio_raw_मुक्त);

	वापस 0;
पूर्ण

अटल bool serio_raw_fetch_byte(काष्ठा serio_raw *serio_raw, अक्षर *c)
अणु
	bool empty;

	serio_छोड़ो_rx(serio_raw->serio);

	empty = serio_raw->head == serio_raw->tail;
	अगर (!empty) अणु
		*c = serio_raw->queue[serio_raw->tail];
		serio_raw->tail = (serio_raw->tail + 1) % SERIO_RAW_QUEUE_LEN;
	पूर्ण

	serio_जारी_rx(serio_raw->serio);

	वापस !empty;
पूर्ण

अटल sमाप_प्रकार serio_raw_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा serio_raw_client *client = file->निजी_data;
	काष्ठा serio_raw *serio_raw = client->serio_raw;
	अक्षर c;
	sमाप_प्रकार पढ़ो = 0;
	पूर्णांक error;

	क्रम (;;) अणु
		अगर (serio_raw->dead)
			वापस -ENODEV;

		अगर (serio_raw->head == serio_raw->tail &&
		    (file->f_flags & O_NONBLOCK))
			वापस -EAGAIN;

		अगर (count == 0)
			अवरोध;

		जबतक (पढ़ो < count && serio_raw_fetch_byte(serio_raw, &c)) अणु
			अगर (put_user(c, buffer++))
				वापस -EFAULT;
			पढ़ो++;
		पूर्ण

		अगर (पढ़ो)
			अवरोध;

		अगर (!(file->f_flags & O_NONBLOCK)) अणु
			error = रुको_event_पूर्णांकerruptible(serio_raw->रुको,
					serio_raw->head != serio_raw->tail ||
					serio_raw->dead);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	वापस पढ़ो;
पूर्ण

अटल sमाप_प्रकार serio_raw_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा serio_raw_client *client = file->निजी_data;
	काष्ठा serio_raw *serio_raw = client->serio_raw;
	पूर्णांक retval = 0;
	अचिन्हित अक्षर c;

	retval = mutex_lock_पूर्णांकerruptible(&serio_raw_mutex);
	अगर (retval)
		वापस retval;

	अगर (serio_raw->dead) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (count > 32)
		count = 32;

	जबतक (count--) अणु
		अगर (get_user(c, buffer++)) अणु
			retval = -EFAULT;
			जाओ out;
		पूर्ण

		अगर (serio_ग_लिखो(serio_raw->serio, c)) अणु
			/* Either संकेत error or partial ग_लिखो */
			अगर (retval == 0)
				retval = -EIO;
			जाओ out;
		पूर्ण

		retval++;
	पूर्ण

out:
	mutex_unlock(&serio_raw_mutex);
	वापस retval;
पूर्ण

अटल __poll_t serio_raw_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा serio_raw_client *client = file->निजी_data;
	काष्ठा serio_raw *serio_raw = client->serio_raw;
	__poll_t mask;

	poll_रुको(file, &serio_raw->रुको, रुको);

	mask = serio_raw->dead ? EPOLLHUP | EPOLLERR : EPOLLOUT | EPOLLWRNORM;
	अगर (serio_raw->head != serio_raw->tail)
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations serio_raw_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= serio_raw_खोलो,
	.release	= serio_raw_release,
	.पढ़ो		= serio_raw_पढ़ो,
	.ग_लिखो		= serio_raw_ग_लिखो,
	.poll		= serio_raw_poll,
	.fasync		= serio_raw_fasync,
	.llseek		= noop_llseek,
पूर्ण;


/*********************************************************************
 *                   Interface with serio port                       *
 *********************************************************************/

अटल irqवापस_t serio_raw_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data,
					अचिन्हित पूर्णांक dfl)
अणु
	काष्ठा serio_raw *serio_raw = serio_get_drvdata(serio);
	काष्ठा serio_raw_client *client;
	अचिन्हित पूर्णांक head = serio_raw->head;

	/* we are holding serio->lock here so we are रक्षित */
	serio_raw->queue[head] = data;
	head = (head + 1) % SERIO_RAW_QUEUE_LEN;
	अगर (likely(head != serio_raw->tail)) अणु
		serio_raw->head = head;
		list_क्रम_each_entry(client, &serio_raw->client_list, node)
			समाप्त_fasync(&client->fasync, SIGIO, POLL_IN);
		wake_up_पूर्णांकerruptible(&serio_raw->रुको);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक serio_raw_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	अटल atomic_t serio_raw_no = ATOMIC_INIT(-1);
	काष्ठा serio_raw *serio_raw;
	पूर्णांक err;

	serio_raw = kzalloc(माप(काष्ठा serio_raw), GFP_KERNEL);
	अगर (!serio_raw) अणु
		dev_dbg(&serio->dev, "can't allocate memory for a device\n");
		वापस -ENOMEM;
	पूर्ण

	snम_लिखो(serio_raw->name, माप(serio_raw->name),
		 "serio_raw%ld", (दीर्घ)atomic_inc_वापस(&serio_raw_no));
	kref_init(&serio_raw->kref);
	INIT_LIST_HEAD(&serio_raw->client_list);
	init_रुकोqueue_head(&serio_raw->रुको);

	serio_raw->serio = serio;
	get_device(&serio->dev);

	serio_set_drvdata(serio, serio_raw);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ err_मुक्त;

	err = mutex_lock_समाप्तable(&serio_raw_mutex);
	अगर (err)
		जाओ err_बंद;

	list_add_tail(&serio_raw->node, &serio_raw_list);
	mutex_unlock(&serio_raw_mutex);

	serio_raw->dev.minor = PSMOUSE_MINOR;
	serio_raw->dev.name = serio_raw->name;
	serio_raw->dev.parent = &serio->dev;
	serio_raw->dev.fops = &serio_raw_fops;

	err = misc_रेजिस्टर(&serio_raw->dev);
	अगर (err) अणु
		serio_raw->dev.minor = MISC_DYNAMIC_MINOR;
		err = misc_रेजिस्टर(&serio_raw->dev);
	पूर्ण

	अगर (err) अणु
		dev_err(&serio->dev,
			"failed to register raw access device for %s\n",
			serio->phys);
		जाओ err_unlink;
	पूर्ण

	dev_info(&serio->dev, "raw access enabled on %s (%s, minor %d)\n",
		 serio->phys, serio_raw->name, serio_raw->dev.minor);
	वापस 0;

err_unlink:
	list_del_init(&serio_raw->node);
err_बंद:
	serio_बंद(serio);
err_मुक्त:
	serio_set_drvdata(serio, शून्य);
	kref_put(&serio_raw->kref, serio_raw_मुक्त);
	वापस err;
पूर्ण

अटल पूर्णांक serio_raw_reconnect(काष्ठा serio *serio)
अणु
	काष्ठा serio_raw *serio_raw = serio_get_drvdata(serio);
	काष्ठा serio_driver *drv = serio->drv;

	अगर (!drv || !serio_raw) अणु
		dev_dbg(&serio->dev,
			"reconnect request, but serio is disconnected, ignoring...\n");
		वापस -1;
	पूर्ण

	/*
	 * Nothing needs to be करोne here, we just need this method to
	 * keep the same device.
	 */
	वापस 0;
पूर्ण

/*
 * Wake up users रुकोing क्रम IO so they can disconnect from
 * dead device.
 */
अटल व्योम serio_raw_hangup(काष्ठा serio_raw *serio_raw)
अणु
	काष्ठा serio_raw_client *client;

	serio_छोड़ो_rx(serio_raw->serio);
	list_क्रम_each_entry(client, &serio_raw->client_list, node)
		समाप्त_fasync(&client->fasync, SIGIO, POLL_HUP);
	serio_जारी_rx(serio_raw->serio);

	wake_up_पूर्णांकerruptible(&serio_raw->रुको);
पूर्ण


अटल व्योम serio_raw_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा serio_raw *serio_raw = serio_get_drvdata(serio);

	misc_deरेजिस्टर(&serio_raw->dev);

	mutex_lock(&serio_raw_mutex);
	serio_raw->dead = true;
	list_del_init(&serio_raw->node);
	mutex_unlock(&serio_raw_mutex);

	serio_raw_hangup(serio_raw);

	serio_बंद(serio);
	kref_put(&serio_raw->kref, serio_raw_मुक्त);

	serio_set_drvdata(serio, शून्य);
पूर्ण

अटल स्थिर काष्ठा serio_device_id serio_raw_serio_ids[] = अणु
	अणु
		.type	= SERIO_8042,
		.proto	= SERIO_ANY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_8042_XL,
		.proto	= SERIO_ANY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, serio_raw_serio_ids);

अटल काष्ठा serio_driver serio_raw_drv = अणु
	.driver		= अणु
		.name	= "serio_raw",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= serio_raw_serio_ids,
	.पूर्णांकerrupt	= serio_raw_पूर्णांकerrupt,
	.connect	= serio_raw_connect,
	.reconnect	= serio_raw_reconnect,
	.disconnect	= serio_raw_disconnect,
	.manual_bind	= true,
पूर्ण;

module_serio_driver(serio_raw_drv);
