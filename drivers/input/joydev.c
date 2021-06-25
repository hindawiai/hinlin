<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Joystick device driver क्रम the input driver suite.
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 * Copyright (c) 1999 Colin Van Dyke
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <यंत्र/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/joystick.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/major.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Joystick device interfaces");
MODULE_LICENSE("GPL");

#घोषणा JOYDEV_MINOR_BASE	0
#घोषणा JOYDEV_MINORS		16
#घोषणा JOYDEV_BUFFER_SIZE	64

काष्ठा joydev अणु
	पूर्णांक खोलो;
	काष्ठा input_handle handle;
	रुको_queue_head_t रुको;
	काष्ठा list_head client_list;
	spinlock_t client_lock; /* protects client_list */
	काष्ठा mutex mutex;
	काष्ठा device dev;
	काष्ठा cdev cdev;
	bool exist;

	काष्ठा js_corr corr[ABS_CNT];
	काष्ठा JS_DATA_SAVE_TYPE glue;
	पूर्णांक nअसल;
	पूर्णांक nkey;
	__u16 keymap[KEY_MAX - BTN_MISC + 1];
	__u16 keypam[KEY_MAX - BTN_MISC + 1];
	__u8 असलmap[ABS_CNT];
	__u8 असलpam[ABS_CNT];
	__s16 असल[ABS_CNT];
पूर्ण;

काष्ठा joydev_client अणु
	काष्ठा js_event buffer[JOYDEV_BUFFER_SIZE];
	पूर्णांक head;
	पूर्णांक tail;
	पूर्णांक startup;
	spinlock_t buffer_lock; /* protects access to buffer, head and tail */
	काष्ठा fasync_काष्ठा *fasync;
	काष्ठा joydev *joydev;
	काष्ठा list_head node;
पूर्ण;

अटल पूर्णांक joydev_correct(पूर्णांक value, काष्ठा js_corr *corr)
अणु
	चयन (corr->type) अणु

	हाल JS_CORR_NONE:
		अवरोध;

	हाल JS_CORR_BROKEN:
		value = value > corr->coef[0] ? (value < corr->coef[1] ? 0 :
			((corr->coef[3] * (value - corr->coef[1])) >> 14)) :
			((corr->coef[2] * (value - corr->coef[0])) >> 14);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस clamp(value, -32767, 32767);
पूर्ण

अटल व्योम joydev_pass_event(काष्ठा joydev_client *client,
			      काष्ठा js_event *event)
अणु
	काष्ठा joydev *joydev = client->joydev;

	/*
	 * IRQs alपढ़ोy disabled, just acquire the lock
	 */
	spin_lock(&client->buffer_lock);

	client->buffer[client->head] = *event;

	अगर (client->startup == joydev->nअसल + joydev->nkey) अणु
		client->head++;
		client->head &= JOYDEV_BUFFER_SIZE - 1;
		अगर (client->tail == client->head)
			client->startup = 0;
	पूर्ण

	spin_unlock(&client->buffer_lock);

	समाप्त_fasync(&client->fasync, SIGIO, POLL_IN);
पूर्ण

अटल व्योम joydev_event(काष्ठा input_handle *handle,
			 अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा joydev *joydev = handle->निजी;
	काष्ठा joydev_client *client;
	काष्ठा js_event event;

	चयन (type) अणु

	हाल EV_KEY:
		अगर (code < BTN_MISC || value == 2)
			वापस;
		event.type = JS_EVENT_BUTTON;
		event.number = joydev->keymap[code - BTN_MISC];
		event.value = value;
		अवरोध;

	हाल EV_ABS:
		event.type = JS_EVENT_AXIS;
		event.number = joydev->असलmap[code];
		event.value = joydev_correct(value,
					&joydev->corr[event.number]);
		अगर (event.value == joydev->असल[event.number])
			वापस;
		joydev->असल[event.number] = event.value;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	event.समय = jअगरfies_to_msecs(jअगरfies);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(client, &joydev->client_list, node)
		joydev_pass_event(client, &event);
	rcu_पढ़ो_unlock();

	wake_up_पूर्णांकerruptible(&joydev->रुको);
पूर्ण

अटल पूर्णांक joydev_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा joydev_client *client = file->निजी_data;

	वापस fasync_helper(fd, file, on, &client->fasync);
पूर्ण

अटल व्योम joydev_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा joydev *joydev = container_of(dev, काष्ठा joydev, dev);

	input_put_device(joydev->handle.dev);
	kमुक्त(joydev);
पूर्ण

अटल व्योम joydev_attach_client(काष्ठा joydev *joydev,
				 काष्ठा joydev_client *client)
अणु
	spin_lock(&joydev->client_lock);
	list_add_tail_rcu(&client->node, &joydev->client_list);
	spin_unlock(&joydev->client_lock);
पूर्ण

अटल व्योम joydev_detach_client(काष्ठा joydev *joydev,
				 काष्ठा joydev_client *client)
अणु
	spin_lock(&joydev->client_lock);
	list_del_rcu(&client->node);
	spin_unlock(&joydev->client_lock);
	synchronize_rcu();
पूर्ण

अटल व्योम joydev_refresh_state(काष्ठा joydev *joydev)
अणु
	काष्ठा input_dev *dev = joydev->handle.dev;
	पूर्णांक i, val;

	क्रम (i = 0; i < joydev->nअसल; i++) अणु
		val = input_असल_get_val(dev, joydev->असलpam[i]);
		joydev->असल[i] = joydev_correct(val, &joydev->corr[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक joydev_खोलो_device(काष्ठा joydev *joydev)
अणु
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&joydev->mutex);
	अगर (retval)
		वापस retval;

	अगर (!joydev->exist)
		retval = -ENODEV;
	अन्यथा अगर (!joydev->खोलो++) अणु
		retval = input_खोलो_device(&joydev->handle);
		अगर (retval)
			joydev->खोलो--;
		अन्यथा
			joydev_refresh_state(joydev);
	पूर्ण

	mutex_unlock(&joydev->mutex);
	वापस retval;
पूर्ण

अटल व्योम joydev_बंद_device(काष्ठा joydev *joydev)
अणु
	mutex_lock(&joydev->mutex);

	अगर (joydev->exist && !--joydev->खोलो)
		input_बंद_device(&joydev->handle);

	mutex_unlock(&joydev->mutex);
पूर्ण

/*
 * Wake up users रुकोing क्रम IO so they can disconnect from
 * dead device.
 */
अटल व्योम joydev_hangup(काष्ठा joydev *joydev)
अणु
	काष्ठा joydev_client *client;

	spin_lock(&joydev->client_lock);
	list_क्रम_each_entry(client, &joydev->client_list, node)
		समाप्त_fasync(&client->fasync, SIGIO, POLL_HUP);
	spin_unlock(&joydev->client_lock);

	wake_up_पूर्णांकerruptible(&joydev->रुको);
पूर्ण

अटल पूर्णांक joydev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा joydev_client *client = file->निजी_data;
	काष्ठा joydev *joydev = client->joydev;

	joydev_detach_client(joydev, client);
	kमुक्त(client);

	joydev_बंद_device(joydev);

	वापस 0;
पूर्ण

अटल पूर्णांक joydev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा joydev *joydev =
			container_of(inode->i_cdev, काष्ठा joydev, cdev);
	काष्ठा joydev_client *client;
	पूर्णांक error;

	client = kzalloc(माप(काष्ठा joydev_client), GFP_KERNEL);
	अगर (!client)
		वापस -ENOMEM;

	spin_lock_init(&client->buffer_lock);
	client->joydev = joydev;
	joydev_attach_client(joydev, client);

	error = joydev_खोलो_device(joydev);
	अगर (error)
		जाओ err_मुक्त_client;

	file->निजी_data = client;
	stream_खोलो(inode, file);

	वापस 0;

 err_मुक्त_client:
	joydev_detach_client(joydev, client);
	kमुक्त(client);
	वापस error;
पूर्ण

अटल पूर्णांक joydev_generate_startup_event(काष्ठा joydev_client *client,
					 काष्ठा input_dev *input,
					 काष्ठा js_event *event)
अणु
	काष्ठा joydev *joydev = client->joydev;
	पूर्णांक have_event;

	spin_lock_irq(&client->buffer_lock);

	have_event = client->startup < joydev->nअसल + joydev->nkey;

	अगर (have_event) अणु

		event->समय = jअगरfies_to_msecs(jअगरfies);
		अगर (client->startup < joydev->nkey) अणु
			event->type = JS_EVENT_BUTTON | JS_EVENT_INIT;
			event->number = client->startup;
			event->value = !!test_bit(joydev->keypam[event->number],
						  input->key);
		पूर्ण अन्यथा अणु
			event->type = JS_EVENT_AXIS | JS_EVENT_INIT;
			event->number = client->startup - joydev->nkey;
			event->value = joydev->असल[event->number];
		पूर्ण
		client->startup++;
	पूर्ण

	spin_unlock_irq(&client->buffer_lock);

	वापस have_event;
पूर्ण

अटल पूर्णांक joydev_fetch_next_event(काष्ठा joydev_client *client,
				   काष्ठा js_event *event)
अणु
	पूर्णांक have_event;

	spin_lock_irq(&client->buffer_lock);

	have_event = client->head != client->tail;
	अगर (have_event) अणु
		*event = client->buffer[client->tail++];
		client->tail &= JOYDEV_BUFFER_SIZE - 1;
	पूर्ण

	spin_unlock_irq(&client->buffer_lock);

	वापस have_event;
पूर्ण

/*
 * Old joystick पूर्णांकerface
 */
अटल sमाप_प्रकार joydev_0x_पढ़ो(काष्ठा joydev_client *client,
			      काष्ठा input_dev *input,
			      अक्षर __user *buf)
अणु
	काष्ठा joydev *joydev = client->joydev;
	काष्ठा JS_DATA_TYPE data;
	पूर्णांक i;

	spin_lock_irq(&input->event_lock);

	/*
	 * Get device state
	 */
	क्रम (data.buttons = i = 0; i < 32 && i < joydev->nkey; i++)
		data.buttons |=
			test_bit(joydev->keypam[i], input->key) ? (1 << i) : 0;
	data.x = (joydev->असल[0] / 256 + 128) >> joydev->glue.JS_CORR.x;
	data.y = (joydev->असल[1] / 256 + 128) >> joydev->glue.JS_CORR.y;

	/*
	 * Reset पढ़ोer's event queue
	 */
	spin_lock(&client->buffer_lock);
	client->startup = 0;
	client->tail = client->head;
	spin_unlock(&client->buffer_lock);

	spin_unlock_irq(&input->event_lock);

	अगर (copy_to_user(buf, &data, माप(काष्ठा JS_DATA_TYPE)))
		वापस -EFAULT;

	वापस माप(काष्ठा JS_DATA_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक joydev_data_pending(काष्ठा joydev_client *client)
अणु
	काष्ठा joydev *joydev = client->joydev;

	वापस client->startup < joydev->nअसल + joydev->nkey ||
		client->head != client->tail;
पूर्ण

अटल sमाप_प्रकार joydev_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा joydev_client *client = file->निजी_data;
	काष्ठा joydev *joydev = client->joydev;
	काष्ठा input_dev *input = joydev->handle.dev;
	काष्ठा js_event event;
	पूर्णांक retval;

	अगर (!joydev->exist)
		वापस -ENODEV;

	अगर (count < माप(काष्ठा js_event))
		वापस -EINVAL;

	अगर (count == माप(काष्ठा JS_DATA_TYPE))
		वापस joydev_0x_पढ़ो(client, input, buf);

	अगर (!joydev_data_pending(client) && (file->f_flags & O_NONBLOCK))
		वापस -EAGAIN;

	retval = रुको_event_पूर्णांकerruptible(joydev->रुको,
			!joydev->exist || joydev_data_pending(client));
	अगर (retval)
		वापस retval;

	अगर (!joydev->exist)
		वापस -ENODEV;

	जबतक (retval + माप(काष्ठा js_event) <= count &&
	       joydev_generate_startup_event(client, input, &event)) अणु

		अगर (copy_to_user(buf + retval, &event, माप(काष्ठा js_event)))
			वापस -EFAULT;

		retval += माप(काष्ठा js_event);
	पूर्ण

	जबतक (retval + माप(काष्ठा js_event) <= count &&
	       joydev_fetch_next_event(client, &event)) अणु

		अगर (copy_to_user(buf + retval, &event, माप(काष्ठा js_event)))
			वापस -EFAULT;

		retval += माप(काष्ठा js_event);
	पूर्ण

	वापस retval;
पूर्ण

/* No kernel lock - fine */
अटल __poll_t joydev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा joydev_client *client = file->निजी_data;
	काष्ठा joydev *joydev = client->joydev;

	poll_रुको(file, &joydev->रुको, रुको);
	वापस (joydev_data_pending(client) ? (EPOLLIN | EPOLLRDNORM) : 0) |
		(joydev->exist ?  0 : (EPOLLHUP | EPOLLERR));
पूर्ण

अटल पूर्णांक joydev_handle_JSIOCSAXMAP(काष्ठा joydev *joydev,
				     व्योम __user *argp, माप_प्रकार len)
अणु
	__u8 *असलpam;
	पूर्णांक i;
	पूर्णांक retval = 0;

	len = min(len, माप(joydev->असलpam));

	/* Validate the map. */
	असलpam = memdup_user(argp, len);
	अगर (IS_ERR(असलpam))
		वापस PTR_ERR(असलpam);

	क्रम (i = 0; i < len && i < joydev->nअसल; i++) अणु
		अगर (असलpam[i] > ABS_MAX) अणु
			retval = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	स_नकल(joydev->असलpam, असलpam, len);

	क्रम (i = 0; i < joydev->nअसल; i++)
		joydev->असलmap[joydev->असलpam[i]] = i;

 out:
	kमुक्त(असलpam);
	वापस retval;
पूर्ण

अटल पूर्णांक joydev_handle_JSIOCSBTNMAP(काष्ठा joydev *joydev,
				      व्योम __user *argp, माप_प्रकार len)
अणु
	__u16 *keypam;
	पूर्णांक i;
	पूर्णांक retval = 0;

	अगर (len % माप(*keypam))
		वापस -EINVAL;

	len = min(len, माप(joydev->keypam));

	/* Validate the map. */
	keypam = memdup_user(argp, len);
	अगर (IS_ERR(keypam))
		वापस PTR_ERR(keypam);

	क्रम (i = 0; i < (len / 2) && i < joydev->nkey; i++) अणु
		अगर (keypam[i] > KEY_MAX || keypam[i] < BTN_MISC) अणु
			retval = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	स_नकल(joydev->keypam, keypam, len);

	क्रम (i = 0; i < joydev->nkey; i++)
		joydev->keymap[keypam[i] - BTN_MISC] = i;

 out:
	kमुक्त(keypam);
	वापस retval;
पूर्ण


अटल पूर्णांक joydev_ioctl_common(काष्ठा joydev *joydev,
				अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा input_dev *dev = joydev->handle.dev;
	माप_प्रकार len;
	पूर्णांक i;
	स्थिर अक्षर *name;

	/* Process fixed-sized commands. */
	चयन (cmd) अणु

	हाल JS_SET_CAL:
		वापस copy_from_user(&joydev->glue.JS_CORR, argp,
				माप(joydev->glue.JS_CORR)) ? -EFAULT : 0;

	हाल JS_GET_CAL:
		वापस copy_to_user(argp, &joydev->glue.JS_CORR,
				माप(joydev->glue.JS_CORR)) ? -EFAULT : 0;

	हाल JS_SET_TIMEOUT:
		वापस get_user(joydev->glue.JS_TIMEOUT, (s32 __user *) argp);

	हाल JS_GET_TIMEOUT:
		वापस put_user(joydev->glue.JS_TIMEOUT, (s32 __user *) argp);

	हाल JSIOCGVERSION:
		वापस put_user(JS_VERSION, (__u32 __user *) argp);

	हाल JSIOCGAXES:
		वापस put_user(joydev->nअसल, (__u8 __user *) argp);

	हाल JSIOCGBUTTONS:
		वापस put_user(joydev->nkey, (__u8 __user *) argp);

	हाल JSIOCSCORR:
		अगर (copy_from_user(joydev->corr, argp,
			      माप(joydev->corr[0]) * joydev->nअसल))
			वापस -EFAULT;

		क्रम (i = 0; i < joydev->nअसल; i++) अणु
			पूर्णांक val = input_असल_get_val(dev, joydev->असलpam[i]);
			joydev->असल[i] = joydev_correct(val, &joydev->corr[i]);
		पूर्ण
		वापस 0;

	हाल JSIOCGCORR:
		वापस copy_to_user(argp, joydev->corr,
			माप(joydev->corr[0]) * joydev->nअसल) ? -EFAULT : 0;

	पूर्ण

	/*
	 * Process variable-sized commands (the axis and button map commands
	 * are considered variable-sized to decouple them from the values of
	 * ABS_MAX and KEY_MAX).
	 */
	चयन (cmd & ~IOCSIZE_MASK) अणु

	हाल (JSIOCSAXMAP & ~IOCSIZE_MASK):
		वापस joydev_handle_JSIOCSAXMAP(joydev, argp, _IOC_SIZE(cmd));

	हाल (JSIOCGAXMAP & ~IOCSIZE_MASK):
		len = min_t(माप_प्रकार, _IOC_SIZE(cmd), माप(joydev->असलpam));
		वापस copy_to_user(argp, joydev->असलpam, len) ? -EFAULT : len;

	हाल (JSIOCSBTNMAP & ~IOCSIZE_MASK):
		वापस joydev_handle_JSIOCSBTNMAP(joydev, argp, _IOC_SIZE(cmd));

	हाल (JSIOCGBTNMAP & ~IOCSIZE_MASK):
		len = min_t(माप_प्रकार, _IOC_SIZE(cmd), माप(joydev->keypam));
		वापस copy_to_user(argp, joydev->keypam, len) ? -EFAULT : len;

	हाल JSIOCGNAME(0):
		name = dev->name;
		अगर (!name)
			वापस 0;

		len = min_t(माप_प्रकार, _IOC_SIZE(cmd), म_माप(name) + 1);
		वापस copy_to_user(argp, name, len) ? -EFAULT : len;
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ joydev_compat_ioctl(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा joydev_client *client = file->निजी_data;
	काष्ठा joydev *joydev = client->joydev;
	व्योम __user *argp = (व्योम __user *)arg;
	s32 पंचांगp32;
	काष्ठा JS_DATA_SAVE_TYPE_32 ds32;
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&joydev->mutex);
	अगर (retval)
		वापस retval;

	अगर (!joydev->exist) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (cmd) अणु

	हाल JS_SET_TIMELIMIT:
		retval = get_user(पंचांगp32, (s32 __user *) arg);
		अगर (retval == 0)
			joydev->glue.JS_TIMELIMIT = पंचांगp32;
		अवरोध;

	हाल JS_GET_TIMELIMIT:
		पंचांगp32 = joydev->glue.JS_TIMELIMIT;
		retval = put_user(पंचांगp32, (s32 __user *) arg);
		अवरोध;

	हाल JS_SET_ALL:
		retval = copy_from_user(&ds32, argp,
					माप(ds32)) ? -EFAULT : 0;
		अगर (retval == 0) अणु
			joydev->glue.JS_TIMEOUT    = ds32.JS_TIMEOUT;
			joydev->glue.BUSY          = ds32.BUSY;
			joydev->glue.JS_EXPIRETIME = ds32.JS_EXPIRETIME;
			joydev->glue.JS_TIMELIMIT  = ds32.JS_TIMELIMIT;
			joydev->glue.JS_SAVE       = ds32.JS_SAVE;
			joydev->glue.JS_CORR       = ds32.JS_CORR;
		पूर्ण
		अवरोध;

	हाल JS_GET_ALL:
		ds32.JS_TIMEOUT    = joydev->glue.JS_TIMEOUT;
		ds32.BUSY          = joydev->glue.BUSY;
		ds32.JS_EXPIRETIME = joydev->glue.JS_EXPIRETIME;
		ds32.JS_TIMELIMIT  = joydev->glue.JS_TIMELIMIT;
		ds32.JS_SAVE       = joydev->glue.JS_SAVE;
		ds32.JS_CORR       = joydev->glue.JS_CORR;

		retval = copy_to_user(argp, &ds32, माप(ds32)) ? -EFAULT : 0;
		अवरोध;

	शेष:
		retval = joydev_ioctl_common(joydev, cmd, argp);
		अवरोध;
	पूर्ण

 out:
	mutex_unlock(&joydev->mutex);
	वापस retval;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल दीर्घ joydev_ioctl(काष्ठा file *file,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा joydev_client *client = file->निजी_data;
	काष्ठा joydev *joydev = client->joydev;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&joydev->mutex);
	अगर (retval)
		वापस retval;

	अगर (!joydev->exist) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (cmd) अणु

	हाल JS_SET_TIMELIMIT:
		retval = get_user(joydev->glue.JS_TIMELIMIT,
				  (दीर्घ __user *) arg);
		अवरोध;

	हाल JS_GET_TIMELIMIT:
		retval = put_user(joydev->glue.JS_TIMELIMIT,
				  (दीर्घ __user *) arg);
		अवरोध;

	हाल JS_SET_ALL:
		retval = copy_from_user(&joydev->glue, argp,
					माप(joydev->glue)) ? -EFAULT : 0;
		अवरोध;

	हाल JS_GET_ALL:
		retval = copy_to_user(argp, &joydev->glue,
				      माप(joydev->glue)) ? -EFAULT : 0;
		अवरोध;

	शेष:
		retval = joydev_ioctl_common(joydev, cmd, argp);
		अवरोध;
	पूर्ण
 out:
	mutex_unlock(&joydev->mutex);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations joydev_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= joydev_पढ़ो,
	.poll		= joydev_poll,
	.खोलो		= joydev_खोलो,
	.release	= joydev_release,
	.unlocked_ioctl	= joydev_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= joydev_compat_ioctl,
#पूर्ण_अगर
	.fasync		= joydev_fasync,
	.llseek		= no_llseek,
पूर्ण;

/*
 * Mark device non-existent. This disables ग_लिखोs, ioctls and
 * prevents new users from खोलोing the device. Alपढ़ोy posted
 * blocking पढ़ोs will stay, however new ones will fail.
 */
अटल व्योम joydev_mark_dead(काष्ठा joydev *joydev)
अणु
	mutex_lock(&joydev->mutex);
	joydev->exist = false;
	mutex_unlock(&joydev->mutex);
पूर्ण

अटल व्योम joydev_cleanup(काष्ठा joydev *joydev)
अणु
	काष्ठा input_handle *handle = &joydev->handle;

	joydev_mark_dead(joydev);
	joydev_hangup(joydev);

	/* joydev is marked dead so no one अन्यथा accesses joydev->खोलो */
	अगर (joydev->खोलो)
		input_बंद_device(handle);
पूर्ण

/*
 * These codes are copied from from hid-ids.h, unक्रमtunately there is no common
 * usb_ids/bt_ids.h header.
 */
#घोषणा USB_VENDOR_ID_SONY			0x054c
#घोषणा USB_DEVICE_ID_SONY_PS3_CONTROLLER		0x0268
#घोषणा USB_DEVICE_ID_SONY_PS4_CONTROLLER		0x05c4
#घोषणा USB_DEVICE_ID_SONY_PS4_CONTROLLER_2		0x09cc
#घोषणा USB_DEVICE_ID_SONY_PS4_CONTROLLER_DONGLE	0x0ba0

#घोषणा USB_VENDOR_ID_THQ			0x20d6
#घोषणा USB_DEVICE_ID_THQ_PS3_UDRAW			0xcb17

#घोषणा ACCEL_DEV(vnd, prd)						\
	अणु								\
		.flags = INPUT_DEVICE_ID_MATCH_VENDOR |			\
				INPUT_DEVICE_ID_MATCH_PRODUCT |		\
				INPUT_DEVICE_ID_MATCH_PROPBIT,		\
		.venकरोr = (vnd),					\
		.product = (prd),					\
		.propbit = अणु BIT_MASK(INPUT_PROP_ACCELEROMETER) पूर्ण,	\
	पूर्ण

अटल स्थिर काष्ठा input_device_id joydev_blacklist[] = अणु
	/* Aव्योम touchpads and touchscreens */
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH) पूर्ण,
	पूर्ण,
	/* Aव्योम tablets, digitisers and similar devices */
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(BTN_DIGI)] = BIT_MASK(BTN_DIGI) पूर्ण,
	पूर्ण,
	/* Disable accelerometers on composite devices */
	ACCEL_DEV(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS3_CONTROLLER),
	ACCEL_DEV(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER),
	ACCEL_DEV(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER_2),
	ACCEL_DEV(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER_DONGLE),
	ACCEL_DEV(USB_VENDOR_ID_THQ, USB_DEVICE_ID_THQ_PS3_UDRAW),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल bool joydev_dev_is_blacklisted(काष्ठा input_dev *dev)
अणु
	स्थिर काष्ठा input_device_id *id;

	क्रम (id = joydev_blacklist; id->flags; id++) अणु
		अगर (input_match_device_id(dev, id)) अणु
			dev_dbg(&dev->dev,
				"joydev: blacklisting '%s'\n", dev->name);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool joydev_dev_is_असलolute_mouse(काष्ठा input_dev *dev)
अणु
	DECLARE_BITMAP(jd_scratch, KEY_CNT);
	bool ev_match = false;

	BUILD_BUG_ON(ABS_CNT > KEY_CNT || EV_CNT > KEY_CNT);

	/*
	 * Virtualization (VMware, etc) and remote management (HP
	 * ILO2) solutions use असलolute coordinates क्रम their भव
	 * poपूर्णांकing devices so that there is one-to-one relationship
	 * between poपूर्णांकer position on the host screen and भव
	 * guest screen, and so their mice use ABS_X, ABS_Y and 3
	 * primary button events. This clashes with what joydev
	 * considers to be joysticks (a device with at minimum ABS_X
	 * axis).
	 *
	 * Here we are trying to separate असलolute mice from
	 * joysticks. A device is, क्रम joystick detection purposes,
	 * considered to be an असलolute mouse अगर the following is
	 * true:
	 *
	 * 1) Event types are exactly
	 *      EV_ABS, EV_KEY and EV_SYN
	 *    or
	 *      EV_ABS, EV_KEY, EV_SYN and EV_MSC
	 *    or
	 *      EV_ABS, EV_KEY, EV_SYN, EV_MSC and EV_REL.
	 * 2) Absolute events are exactly ABS_X and ABS_Y.
	 * 3) Keys are exactly BTN_LEFT, BTN_RIGHT and BTN_MIDDLE.
	 * 4) Device is not on "Amiga" bus.
	 */

	biपंचांगap_zero(jd_scratch, EV_CNT);
	/* VMware VMMouse, HP ILO2 */
	__set_bit(EV_ABS, jd_scratch);
	__set_bit(EV_KEY, jd_scratch);
	__set_bit(EV_SYN, jd_scratch);
	अगर (biपंचांगap_equal(jd_scratch, dev->evbit, EV_CNT))
		ev_match = true;

	/* HP ILO2, AMI BMC firmware */
	__set_bit(EV_MSC, jd_scratch);
	अगर (biपंचांगap_equal(jd_scratch, dev->evbit, EV_CNT))
		ev_match = true;

	/* VMware Virtual USB Mouse, QEMU USB Tablet, ATEN BMC firmware */
	__set_bit(EV_REL, jd_scratch);
	अगर (biपंचांगap_equal(jd_scratch, dev->evbit, EV_CNT))
		ev_match = true;

	अगर (!ev_match)
		वापस false;

	biपंचांगap_zero(jd_scratch, ABS_CNT);
	__set_bit(ABS_X, jd_scratch);
	__set_bit(ABS_Y, jd_scratch);
	अगर (!biपंचांगap_equal(dev->असलbit, jd_scratch, ABS_CNT))
		वापस false;

	biपंचांगap_zero(jd_scratch, KEY_CNT);
	__set_bit(BTN_LEFT, jd_scratch);
	__set_bit(BTN_RIGHT, jd_scratch);
	__set_bit(BTN_MIDDLE, jd_scratch);

	अगर (!biपंचांगap_equal(dev->keybit, jd_scratch, KEY_CNT))
		वापस false;

	/*
	 * Amiga joystick (amijoy) historically uses left/middle/right
	 * button events.
	 */
	अगर (dev->id.bustype == BUS_AMIGA)
		वापस false;

	वापस true;
पूर्ण

अटल bool joydev_match(काष्ठा input_handler *handler, काष्ठा input_dev *dev)
अणु
	/* Disable blacklisted devices */
	अगर (joydev_dev_is_blacklisted(dev))
		वापस false;

	/* Aव्योम असलolute mice */
	अगर (joydev_dev_is_असलolute_mouse(dev))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक joydev_connect(काष्ठा input_handler *handler, काष्ठा input_dev *dev,
			  स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा joydev *joydev;
	पूर्णांक i, j, t, minor, dev_no;
	पूर्णांक error;

	minor = input_get_new_minor(JOYDEV_MINOR_BASE, JOYDEV_MINORS, true);
	अगर (minor < 0) अणु
		error = minor;
		pr_err("failed to reserve new minor: %d\n", error);
		वापस error;
	पूर्ण

	joydev = kzalloc(माप(काष्ठा joydev), GFP_KERNEL);
	अगर (!joydev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_minor;
	पूर्ण

	INIT_LIST_HEAD(&joydev->client_list);
	spin_lock_init(&joydev->client_lock);
	mutex_init(&joydev->mutex);
	init_रुकोqueue_head(&joydev->रुको);
	joydev->exist = true;

	dev_no = minor;
	/* Normalize device number अगर it falls पूर्णांकo legacy range */
	अगर (dev_no < JOYDEV_MINOR_BASE + JOYDEV_MINORS)
		dev_no -= JOYDEV_MINOR_BASE;
	dev_set_name(&joydev->dev, "js%d", dev_no);

	joydev->handle.dev = input_get_device(dev);
	joydev->handle.name = dev_name(&joydev->dev);
	joydev->handle.handler = handler;
	joydev->handle.निजी = joydev;

	क्रम_each_set_bit(i, dev->असलbit, ABS_CNT) अणु
		joydev->असलmap[i] = joydev->nअसल;
		joydev->असलpam[joydev->nअसल] = i;
		joydev->nअसल++;
	पूर्ण

	क्रम (i = BTN_JOYSTICK - BTN_MISC; i < KEY_MAX - BTN_MISC + 1; i++)
		अगर (test_bit(i + BTN_MISC, dev->keybit)) अणु
			joydev->keymap[i] = joydev->nkey;
			joydev->keypam[joydev->nkey] = i + BTN_MISC;
			joydev->nkey++;
		पूर्ण

	क्रम (i = 0; i < BTN_JOYSTICK - BTN_MISC; i++)
		अगर (test_bit(i + BTN_MISC, dev->keybit)) अणु
			joydev->keymap[i] = joydev->nkey;
			joydev->keypam[joydev->nkey] = i + BTN_MISC;
			joydev->nkey++;
		पूर्ण

	क्रम (i = 0; i < joydev->nअसल; i++) अणु
		j = joydev->असलpam[i];
		अगर (input_असल_get_max(dev, j) == input_असल_get_min(dev, j)) अणु
			joydev->corr[i].type = JS_CORR_NONE;
			जारी;
		पूर्ण
		joydev->corr[i].type = JS_CORR_BROKEN;
		joydev->corr[i].prec = input_असल_get_fuzz(dev, j);

		t = (input_असल_get_max(dev, j) + input_असल_get_min(dev, j)) / 2;
		joydev->corr[i].coef[0] = t - input_असल_get_flat(dev, j);
		joydev->corr[i].coef[1] = t + input_असल_get_flat(dev, j);

		t = (input_असल_get_max(dev, j) - input_असल_get_min(dev, j)) / 2
			- 2 * input_असल_get_flat(dev, j);
		अगर (t) अणु
			joydev->corr[i].coef[2] = (1 << 29) / t;
			joydev->corr[i].coef[3] = (1 << 29) / t;
		पूर्ण
	पूर्ण

	joydev->dev.devt = MKDEV(INPUT_MAJOR, minor);
	joydev->dev.class = &input_class;
	joydev->dev.parent = &dev->dev;
	joydev->dev.release = joydev_मुक्त;
	device_initialize(&joydev->dev);

	error = input_रेजिस्टर_handle(&joydev->handle);
	अगर (error)
		जाओ err_मुक्त_joydev;

	cdev_init(&joydev->cdev, &joydev_fops);

	error = cdev_device_add(&joydev->cdev, &joydev->dev);
	अगर (error)
		जाओ err_cleanup_joydev;

	वापस 0;

 err_cleanup_joydev:
	joydev_cleanup(joydev);
	input_unरेजिस्टर_handle(&joydev->handle);
 err_मुक्त_joydev:
	put_device(&joydev->dev);
 err_मुक्त_minor:
	input_मुक्त_minor(minor);
	वापस error;
पूर्ण

अटल व्योम joydev_disconnect(काष्ठा input_handle *handle)
अणु
	काष्ठा joydev *joydev = handle->निजी;

	cdev_device_del(&joydev->cdev, &joydev->dev);
	joydev_cleanup(joydev);
	input_मुक्त_minor(MINOR(joydev->dev.devt));
	input_unरेजिस्टर_handle(handle);
	put_device(&joydev->dev);
पूर्ण

अटल स्थिर काष्ठा input_device_id joydev_ids[] = अणु
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = अणु BIT_MASK(EV_ABS) पूर्ण,
		.असलbit = अणु BIT_MASK(ABS_X) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = अणु BIT_MASK(EV_ABS) पूर्ण,
		.असलbit = अणु BIT_MASK(ABS_Z) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = अणु BIT_MASK(EV_ABS) पूर्ण,
		.असलbit = अणु BIT_MASK(ABS_WHEEL) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = अणु BIT_MASK(EV_ABS) पूर्ण,
		.असलbit = अणु BIT_MASK(ABS_THROTTLE) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु[BIT_WORD(BTN_JOYSTICK)] = BIT_MASK(BTN_JOYSTICK) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(BTN_GAMEPAD)] = BIT_MASK(BTN_GAMEPAD) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(BTN_TRIGGER_HAPPY)] = BIT_MASK(BTN_TRIGGER_HAPPY) पूर्ण,
	पूर्ण,
	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(input, joydev_ids);

अटल काष्ठा input_handler joydev_handler = अणु
	.event		= joydev_event,
	.match		= joydev_match,
	.connect	= joydev_connect,
	.disconnect	= joydev_disconnect,
	.legacy_minors	= true,
	.minor		= JOYDEV_MINOR_BASE,
	.name		= "joydev",
	.id_table	= joydev_ids,
पूर्ण;

अटल पूर्णांक __init joydev_init(व्योम)
अणु
	वापस input_रेजिस्टर_handler(&joydev_handler);
पूर्ण

अटल व्योम __निकास joydev_निकास(व्योम)
अणु
	input_unरेजिस्टर_handler(&joydev_handler);
पूर्ण

module_init(joydev_init);
module_निकास(joydev_निकास);
