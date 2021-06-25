<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Event अक्षर devices, giving access to raw input device events.
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा EVDEV_MINOR_BASE	64
#घोषणा EVDEV_MINORS		32
#घोषणा EVDEV_MIN_BUFFER_SIZE	64U
#घोषणा EVDEV_BUF_PACKETS	8

#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/major.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश "input-compat.h"

काष्ठा evdev अणु
	पूर्णांक खोलो;
	काष्ठा input_handle handle;
	काष्ठा evdev_client __rcu *grab;
	काष्ठा list_head client_list;
	spinlock_t client_lock; /* protects client_list */
	काष्ठा mutex mutex;
	काष्ठा device dev;
	काष्ठा cdev cdev;
	bool exist;
पूर्ण;

काष्ठा evdev_client अणु
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;
	अचिन्हित पूर्णांक packet_head; /* [future] position of the first element of next packet */
	spinlock_t buffer_lock; /* protects access to buffer, head and tail */
	रुको_queue_head_t रुको;
	काष्ठा fasync_काष्ठा *fasync;
	काष्ठा evdev *evdev;
	काष्ठा list_head node;
	क्रमागत input_घड़ी_प्रकारype clk_type;
	bool revoked;
	अचिन्हित दीर्घ *evmasks[EV_CNT];
	अचिन्हित पूर्णांक bufsize;
	काष्ठा input_event buffer[];
पूर्ण;

अटल माप_प्रकार evdev_get_mask_cnt(अचिन्हित पूर्णांक type)
अणु
	अटल स्थिर माप_प्रकार counts[EV_CNT] = अणु
		/* EV_SYN==0 is EV_CNT, _not_ SYN_CNT, see EVIOCGBIT */
		[EV_SYN]	= EV_CNT,
		[EV_KEY]	= KEY_CNT,
		[EV_REL]	= REL_CNT,
		[EV_ABS]	= ABS_CNT,
		[EV_MSC]	= MSC_CNT,
		[EV_SW]		= SW_CNT,
		[EV_LED]	= LED_CNT,
		[EV_SND]	= SND_CNT,
		[EV_FF]		= FF_CNT,
	पूर्ण;

	वापस (type < EV_CNT) ? counts[type] : 0;
पूर्ण

/* requires the buffer lock to be held */
अटल bool __evdev_is_filtered(काष्ठा evdev_client *client,
				अचिन्हित पूर्णांक type,
				अचिन्हित पूर्णांक code)
अणु
	अचिन्हित दीर्घ *mask;
	माप_प्रकार cnt;

	/* EV_SYN and unknown codes are never filtered */
	अगर (type == EV_SYN || type >= EV_CNT)
		वापस false;

	/* first test whether the type is filtered */
	mask = client->evmasks[0];
	अगर (mask && !test_bit(type, mask))
		वापस true;

	/* unknown values are never filtered */
	cnt = evdev_get_mask_cnt(type);
	अगर (!cnt || code >= cnt)
		वापस false;

	mask = client->evmasks[type];
	वापस mask && !test_bit(code, mask);
पूर्ण

/* flush queued events of type @type, caller must hold client->buffer_lock */
अटल व्योम __evdev_flush_queue(काष्ठा evdev_client *client, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक i, head, num;
	अचिन्हित पूर्णांक mask = client->bufsize - 1;
	bool is_report;
	काष्ठा input_event *ev;

	BUG_ON(type == EV_SYN);

	head = client->tail;
	client->packet_head = client->tail;

	/* init to 1 so a leading SYN_REPORT will not be dropped */
	num = 1;

	क्रम (i = client->tail; i != client->head; i = (i + 1) & mask) अणु
		ev = &client->buffer[i];
		is_report = ev->type == EV_SYN && ev->code == SYN_REPORT;

		अगर (ev->type == type) अणु
			/* drop matched entry */
			जारी;
		पूर्ण अन्यथा अगर (is_report && !num) अणु
			/* drop empty SYN_REPORT groups */
			जारी;
		पूर्ण अन्यथा अगर (head != i) अणु
			/* move entry to fill the gap */
			client->buffer[head] = *ev;
		पूर्ण

		num++;
		head = (head + 1) & mask;

		अगर (is_report) अणु
			num = 0;
			client->packet_head = head;
		पूर्ण
	पूर्ण

	client->head = head;
पूर्ण

अटल व्योम __evdev_queue_syn_dropped(काष्ठा evdev_client *client)
अणु
	kसमय_प्रकार *ev_समय = input_get_बारtamp(client->evdev->handle.dev);
	काष्ठा बारpec64 ts = kसमय_प्रकारo_बारpec64(ev_समय[client->clk_type]);
	काष्ठा input_event ev;

	ev.input_event_sec = ts.tv_sec;
	ev.input_event_usec = ts.tv_nsec / NSEC_PER_USEC;
	ev.type = EV_SYN;
	ev.code = SYN_DROPPED;
	ev.value = 0;

	client->buffer[client->head++] = ev;
	client->head &= client->bufsize - 1;

	अगर (unlikely(client->head == client->tail)) अणु
		/* drop queue but keep our SYN_DROPPED event */
		client->tail = (client->head - 1) & (client->bufsize - 1);
		client->packet_head = client->tail;
	पूर्ण
पूर्ण

अटल व्योम evdev_queue_syn_dropped(काष्ठा evdev_client *client)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&client->buffer_lock, flags);
	__evdev_queue_syn_dropped(client);
	spin_unlock_irqrestore(&client->buffer_lock, flags);
पूर्ण

अटल पूर्णांक evdev_set_clk_type(काष्ठा evdev_client *client, अचिन्हित पूर्णांक clkid)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत input_घड़ी_प्रकारype clk_type;

	चयन (clkid) अणु

	हाल CLOCK_REALTIME:
		clk_type = INPUT_CLK_REAL;
		अवरोध;
	हाल CLOCK_MONOTONIC:
		clk_type = INPUT_CLK_MONO;
		अवरोध;
	हाल CLOCK_BOOTTIME:
		clk_type = INPUT_CLK_BOOT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (client->clk_type != clk_type) अणु
		client->clk_type = clk_type;

		/*
		 * Flush pending events and queue SYN_DROPPED event,
		 * but only अगर the queue is not empty.
		 */
		spin_lock_irqsave(&client->buffer_lock, flags);

		अगर (client->head != client->tail) अणु
			client->packet_head = client->head = client->tail;
			__evdev_queue_syn_dropped(client);
		पूर्ण

		spin_unlock_irqrestore(&client->buffer_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __pass_event(काष्ठा evdev_client *client,
			 स्थिर काष्ठा input_event *event)
अणु
	client->buffer[client->head++] = *event;
	client->head &= client->bufsize - 1;

	अगर (unlikely(client->head == client->tail)) अणु
		/*
		 * This effectively "drops" all unconsumed events, leaving
		 * EV_SYN/SYN_DROPPED plus the newest event in the queue.
		 */
		client->tail = (client->head - 2) & (client->bufsize - 1);

		client->buffer[client->tail] = (काष्ठा input_event) अणु
			.input_event_sec = event->input_event_sec,
			.input_event_usec = event->input_event_usec,
			.type = EV_SYN,
			.code = SYN_DROPPED,
			.value = 0,
		पूर्ण;

		client->packet_head = client->tail;
	पूर्ण

	अगर (event->type == EV_SYN && event->code == SYN_REPORT) अणु
		client->packet_head = client->head;
		समाप्त_fasync(&client->fasync, SIGIO, POLL_IN);
	पूर्ण
पूर्ण

अटल व्योम evdev_pass_values(काष्ठा evdev_client *client,
			स्थिर काष्ठा input_value *vals, अचिन्हित पूर्णांक count,
			kसमय_प्रकार *ev_समय)
अणु
	स्थिर काष्ठा input_value *v;
	काष्ठा input_event event;
	काष्ठा बारpec64 ts;
	bool wakeup = false;

	अगर (client->revoked)
		वापस;

	ts = kसमय_प्रकारo_बारpec64(ev_समय[client->clk_type]);
	event.input_event_sec = ts.tv_sec;
	event.input_event_usec = ts.tv_nsec / NSEC_PER_USEC;

	/* Interrupts are disabled, just acquire the lock. */
	spin_lock(&client->buffer_lock);

	क्रम (v = vals; v != vals + count; v++) अणु
		अगर (__evdev_is_filtered(client, v->type, v->code))
			जारी;

		अगर (v->type == EV_SYN && v->code == SYN_REPORT) अणु
			/* drop empty SYN_REPORT */
			अगर (client->packet_head == client->head)
				जारी;

			wakeup = true;
		पूर्ण

		event.type = v->type;
		event.code = v->code;
		event.value = v->value;
		__pass_event(client, &event);
	पूर्ण

	spin_unlock(&client->buffer_lock);

	अगर (wakeup)
		wake_up_पूर्णांकerruptible_poll(&client->रुको,
			EPOLLIN | EPOLLOUT | EPOLLRDNORM | EPOLLWRNORM);
पूर्ण

/*
 * Pass incoming events to all connected clients.
 */
अटल व्योम evdev_events(काष्ठा input_handle *handle,
			 स्थिर काष्ठा input_value *vals, अचिन्हित पूर्णांक count)
अणु
	काष्ठा evdev *evdev = handle->निजी;
	काष्ठा evdev_client *client;
	kसमय_प्रकार *ev_समय = input_get_बारtamp(handle->dev);

	rcu_पढ़ो_lock();

	client = rcu_dereference(evdev->grab);

	अगर (client)
		evdev_pass_values(client, vals, count, ev_समय);
	अन्यथा
		list_क्रम_each_entry_rcu(client, &evdev->client_list, node)
			evdev_pass_values(client, vals, count, ev_समय);

	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Pass incoming event to all connected clients.
 */
अटल व्योम evdev_event(काष्ठा input_handle *handle,
			अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा input_value vals[] = अणु अणु type, code, value पूर्ण पूर्ण;

	evdev_events(handle, vals, 1);
पूर्ण

अटल पूर्णांक evdev_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा evdev_client *client = file->निजी_data;

	वापस fasync_helper(fd, file, on, &client->fasync);
पूर्ण

अटल व्योम evdev_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा evdev *evdev = container_of(dev, काष्ठा evdev, dev);

	input_put_device(evdev->handle.dev);
	kमुक्त(evdev);
पूर्ण

/*
 * Grअसल an event device (aदीर्घ with underlying input device).
 * This function is called with evdev->mutex taken.
 */
अटल पूर्णांक evdev_grab(काष्ठा evdev *evdev, काष्ठा evdev_client *client)
अणु
	पूर्णांक error;

	अगर (evdev->grab)
		वापस -EBUSY;

	error = input_grab_device(&evdev->handle);
	अगर (error)
		वापस error;

	rcu_assign_poपूर्णांकer(evdev->grab, client);

	वापस 0;
पूर्ण

अटल पूर्णांक evdev_ungrab(काष्ठा evdev *evdev, काष्ठा evdev_client *client)
अणु
	काष्ठा evdev_client *grab = rcu_dereference_रक्षित(evdev->grab,
					lockdep_is_held(&evdev->mutex));

	अगर (grab != client)
		वापस  -EINVAL;

	rcu_assign_poपूर्णांकer(evdev->grab, शून्य);
	synchronize_rcu();
	input_release_device(&evdev->handle);

	वापस 0;
पूर्ण

अटल व्योम evdev_attach_client(काष्ठा evdev *evdev,
				काष्ठा evdev_client *client)
अणु
	spin_lock(&evdev->client_lock);
	list_add_tail_rcu(&client->node, &evdev->client_list);
	spin_unlock(&evdev->client_lock);
पूर्ण

अटल व्योम evdev_detach_client(काष्ठा evdev *evdev,
				काष्ठा evdev_client *client)
अणु
	spin_lock(&evdev->client_lock);
	list_del_rcu(&client->node);
	spin_unlock(&evdev->client_lock);
	synchronize_rcu();
पूर्ण

अटल पूर्णांक evdev_खोलो_device(काष्ठा evdev *evdev)
अणु
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&evdev->mutex);
	अगर (retval)
		वापस retval;

	अगर (!evdev->exist)
		retval = -ENODEV;
	अन्यथा अगर (!evdev->खोलो++) अणु
		retval = input_खोलो_device(&evdev->handle);
		अगर (retval)
			evdev->खोलो--;
	पूर्ण

	mutex_unlock(&evdev->mutex);
	वापस retval;
पूर्ण

अटल व्योम evdev_बंद_device(काष्ठा evdev *evdev)
अणु
	mutex_lock(&evdev->mutex);

	अगर (evdev->exist && !--evdev->खोलो)
		input_बंद_device(&evdev->handle);

	mutex_unlock(&evdev->mutex);
पूर्ण

/*
 * Wake up users रुकोing क्रम IO so they can disconnect from
 * dead device.
 */
अटल व्योम evdev_hangup(काष्ठा evdev *evdev)
अणु
	काष्ठा evdev_client *client;

	spin_lock(&evdev->client_lock);
	list_क्रम_each_entry(client, &evdev->client_list, node) अणु
		समाप्त_fasync(&client->fasync, SIGIO, POLL_HUP);
		wake_up_पूर्णांकerruptible_poll(&client->रुको, EPOLLHUP | EPOLLERR);
	पूर्ण
	spin_unlock(&evdev->client_lock);
पूर्ण

अटल पूर्णांक evdev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा evdev_client *client = file->निजी_data;
	काष्ठा evdev *evdev = client->evdev;
	अचिन्हित पूर्णांक i;

	mutex_lock(&evdev->mutex);

	अगर (evdev->exist && !client->revoked)
		input_flush_device(&evdev->handle, file);

	evdev_ungrab(evdev, client);
	mutex_unlock(&evdev->mutex);

	evdev_detach_client(evdev, client);

	क्रम (i = 0; i < EV_CNT; ++i)
		biपंचांगap_मुक्त(client->evmasks[i]);

	kvमुक्त(client);

	evdev_बंद_device(evdev);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक evdev_compute_buffer_size(काष्ठा input_dev *dev)
अणु
	अचिन्हित पूर्णांक n_events =
		max(dev->hपूर्णांक_events_per_packet * EVDEV_BUF_PACKETS,
		    EVDEV_MIN_BUFFER_SIZE);

	वापस roundup_घात_of_two(n_events);
पूर्ण

अटल पूर्णांक evdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा evdev *evdev = container_of(inode->i_cdev, काष्ठा evdev, cdev);
	अचिन्हित पूर्णांक bufsize = evdev_compute_buffer_size(evdev->handle.dev);
	काष्ठा evdev_client *client;
	पूर्णांक error;

	client = kvzalloc(काष्ठा_size(client, buffer, bufsize), GFP_KERNEL);
	अगर (!client)
		वापस -ENOMEM;

	init_रुकोqueue_head(&client->रुको);
	client->bufsize = bufsize;
	spin_lock_init(&client->buffer_lock);
	client->evdev = evdev;
	evdev_attach_client(evdev, client);

	error = evdev_खोलो_device(evdev);
	अगर (error)
		जाओ err_मुक्त_client;

	file->निजी_data = client;
	stream_खोलो(inode, file);

	वापस 0;

 err_मुक्त_client:
	evdev_detach_client(evdev, client);
	kvमुक्त(client);
	वापस error;
पूर्ण

अटल sमाप_प्रकार evdev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा evdev_client *client = file->निजी_data;
	काष्ठा evdev *evdev = client->evdev;
	काष्ठा input_event event;
	पूर्णांक retval = 0;

	अगर (count != 0 && count < input_event_size())
		वापस -EINVAL;

	retval = mutex_lock_पूर्णांकerruptible(&evdev->mutex);
	अगर (retval)
		वापस retval;

	अगर (!evdev->exist || client->revoked) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	जबतक (retval + input_event_size() <= count) अणु

		अगर (input_event_from_user(buffer + retval, &event)) अणु
			retval = -EFAULT;
			जाओ out;
		पूर्ण
		retval += input_event_size();

		input_inject_event(&evdev->handle,
				   event.type, event.code, event.value);
		cond_resched();
	पूर्ण

 out:
	mutex_unlock(&evdev->mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक evdev_fetch_next_event(काष्ठा evdev_client *client,
				  काष्ठा input_event *event)
अणु
	पूर्णांक have_event;

	spin_lock_irq(&client->buffer_lock);

	have_event = client->packet_head != client->tail;
	अगर (have_event) अणु
		*event = client->buffer[client->tail++];
		client->tail &= client->bufsize - 1;
	पूर्ण

	spin_unlock_irq(&client->buffer_lock);

	वापस have_event;
पूर्ण

अटल sमाप_प्रकार evdev_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा evdev_client *client = file->निजी_data;
	काष्ठा evdev *evdev = client->evdev;
	काष्ठा input_event event;
	माप_प्रकार पढ़ो = 0;
	पूर्णांक error;

	अगर (count != 0 && count < input_event_size())
		वापस -EINVAL;

	क्रम (;;) अणु
		अगर (!evdev->exist || client->revoked)
			वापस -ENODEV;

		अगर (client->packet_head == client->tail &&
		    (file->f_flags & O_NONBLOCK))
			वापस -EAGAIN;

		/*
		 * count == 0 is special - no IO is करोne but we check
		 * क्रम error conditions (see above).
		 */
		अगर (count == 0)
			अवरोध;

		जबतक (पढ़ो + input_event_size() <= count &&
		       evdev_fetch_next_event(client, &event)) अणु

			अगर (input_event_to_user(buffer + पढ़ो, &event))
				वापस -EFAULT;

			पढ़ो += input_event_size();
		पूर्ण

		अगर (पढ़ो)
			अवरोध;

		अगर (!(file->f_flags & O_NONBLOCK)) अणु
			error = रुको_event_पूर्णांकerruptible(client->रुको,
					client->packet_head != client->tail ||
					!evdev->exist || client->revoked);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	वापस पढ़ो;
पूर्ण

/* No kernel lock - fine */
अटल __poll_t evdev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा evdev_client *client = file->निजी_data;
	काष्ठा evdev *evdev = client->evdev;
	__poll_t mask;

	poll_रुको(file, &client->रुको, रुको);

	अगर (evdev->exist && !client->revoked)
		mask = EPOLLOUT | EPOLLWRNORM;
	अन्यथा
		mask = EPOLLHUP | EPOLLERR;

	अगर (client->packet_head != client->tail)
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

#घोषणा BITS_PER_LONG_COMPAT (माप(compat_दीर्घ_t) * 8)
#घोषणा BITS_TO_LONGS_COMPAT(x) ((((x) - 1) / BITS_PER_LONG_COMPAT) + 1)

#अगर_घोषित __BIG_ENDIAN
अटल पूर्णांक bits_to_user(अचिन्हित दीर्घ *bits, अचिन्हित पूर्णांक maxbit,
			अचिन्हित पूर्णांक maxlen, व्योम __user *p, पूर्णांक compat)
अणु
	पूर्णांक len, i;

	अगर (compat) अणु
		len = BITS_TO_LONGS_COMPAT(maxbit) * माप(compat_दीर्घ_t);
		अगर (len > maxlen)
			len = maxlen;

		क्रम (i = 0; i < len / माप(compat_दीर्घ_t); i++)
			अगर (copy_to_user((compat_दीर्घ_t __user *) p + i,
					 (compat_दीर्घ_t *) bits +
						i + 1 - ((i % 2) << 1),
					 माप(compat_दीर्घ_t)))
				वापस -EFAULT;
	पूर्ण अन्यथा अणु
		len = BITS_TO_LONGS(maxbit) * माप(दीर्घ);
		अगर (len > maxlen)
			len = maxlen;

		अगर (copy_to_user(p, bits, len))
			वापस -EFAULT;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक bits_from_user(अचिन्हित दीर्घ *bits, अचिन्हित पूर्णांक maxbit,
			  अचिन्हित पूर्णांक maxlen, स्थिर व्योम __user *p, पूर्णांक compat)
अणु
	पूर्णांक len, i;

	अगर (compat) अणु
		अगर (maxlen % माप(compat_दीर्घ_t))
			वापस -EINVAL;

		len = BITS_TO_LONGS_COMPAT(maxbit) * माप(compat_दीर्घ_t);
		अगर (len > maxlen)
			len = maxlen;

		क्रम (i = 0; i < len / माप(compat_दीर्घ_t); i++)
			अगर (copy_from_user((compat_दीर्घ_t *) bits +
						i + 1 - ((i % 2) << 1),
					   (compat_दीर्घ_t __user *) p + i,
					   माप(compat_दीर्घ_t)))
				वापस -EFAULT;
		अगर (i % 2)
			*((compat_दीर्घ_t *) bits + i - 1) = 0;

	पूर्ण अन्यथा अणु
		अगर (maxlen % माप(दीर्घ))
			वापस -EINVAL;

		len = BITS_TO_LONGS(maxbit) * माप(दीर्घ);
		अगर (len > maxlen)
			len = maxlen;

		अगर (copy_from_user(bits, p, len))
			वापस -EFAULT;
	पूर्ण

	वापस len;
पूर्ण

#अन्यथा

अटल पूर्णांक bits_to_user(अचिन्हित दीर्घ *bits, अचिन्हित पूर्णांक maxbit,
			अचिन्हित पूर्णांक maxlen, व्योम __user *p, पूर्णांक compat)
अणु
	पूर्णांक len = compat ?
			BITS_TO_LONGS_COMPAT(maxbit) * माप(compat_दीर्घ_t) :
			BITS_TO_LONGS(maxbit) * माप(दीर्घ);

	अगर (len > maxlen)
		len = maxlen;

	वापस copy_to_user(p, bits, len) ? -EFAULT : len;
पूर्ण

अटल पूर्णांक bits_from_user(अचिन्हित दीर्घ *bits, अचिन्हित पूर्णांक maxbit,
			  अचिन्हित पूर्णांक maxlen, स्थिर व्योम __user *p, पूर्णांक compat)
अणु
	माप_प्रकार chunk_size = compat ? माप(compat_दीर्घ_t) : माप(दीर्घ);
	पूर्णांक len;

	अगर (maxlen % chunk_size)
		वापस -EINVAL;

	len = compat ? BITS_TO_LONGS_COMPAT(maxbit) : BITS_TO_LONGS(maxbit);
	len *= chunk_size;
	अगर (len > maxlen)
		len = maxlen;

	वापस copy_from_user(bits, p, len) ? -EFAULT : len;
पूर्ण

#पूर्ण_अगर /* __BIG_ENDIAN */

#अन्यथा

अटल पूर्णांक bits_to_user(अचिन्हित दीर्घ *bits, अचिन्हित पूर्णांक maxbit,
			अचिन्हित पूर्णांक maxlen, व्योम __user *p, पूर्णांक compat)
अणु
	पूर्णांक len = BITS_TO_LONGS(maxbit) * माप(दीर्घ);

	अगर (len > maxlen)
		len = maxlen;

	वापस copy_to_user(p, bits, len) ? -EFAULT : len;
पूर्ण

अटल पूर्णांक bits_from_user(अचिन्हित दीर्घ *bits, अचिन्हित पूर्णांक maxbit,
			  अचिन्हित पूर्णांक maxlen, स्थिर व्योम __user *p, पूर्णांक compat)
अणु
	पूर्णांक len;

	अगर (maxlen % माप(दीर्घ))
		वापस -EINVAL;

	len = BITS_TO_LONGS(maxbit) * माप(दीर्घ);
	अगर (len > maxlen)
		len = maxlen;

	वापस copy_from_user(bits, p, len) ? -EFAULT : len;
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */

अटल पूर्णांक str_to_user(स्थिर अक्षर *str, अचिन्हित पूर्णांक maxlen, व्योम __user *p)
अणु
	पूर्णांक len;

	अगर (!str)
		वापस -ENOENT;

	len = म_माप(str) + 1;
	अगर (len > maxlen)
		len = maxlen;

	वापस copy_to_user(p, str, len) ? -EFAULT : len;
पूर्ण

अटल पूर्णांक handle_eviocgbit(काष्ठा input_dev *dev,
			    अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक size,
			    व्योम __user *p, पूर्णांक compat_mode)
अणु
	अचिन्हित दीर्घ *bits;
	पूर्णांक len;

	चयन (type) अणु

	हाल      0: bits = dev->evbit;  len = EV_MAX;  अवरोध;
	हाल EV_KEY: bits = dev->keybit; len = KEY_MAX; अवरोध;
	हाल EV_REL: bits = dev->relbit; len = REL_MAX; अवरोध;
	हाल EV_ABS: bits = dev->असलbit; len = ABS_MAX; अवरोध;
	हाल EV_MSC: bits = dev->mscbit; len = MSC_MAX; अवरोध;
	हाल EV_LED: bits = dev->ledbit; len = LED_MAX; अवरोध;
	हाल EV_SND: bits = dev->sndbit; len = SND_MAX; अवरोध;
	हाल EV_FF:  bits = dev->ffbit;  len = FF_MAX;  अवरोध;
	हाल EV_SW:  bits = dev->swbit;  len = SW_MAX;  अवरोध;
	शेष: वापस -EINVAL;
	पूर्ण

	वापस bits_to_user(bits, len, size, p, compat_mode);
पूर्ण

अटल पूर्णांक evdev_handle_get_keycode(काष्ठा input_dev *dev, व्योम __user *p)
अणु
	काष्ठा input_keymap_entry ke = अणु
		.len	= माप(अचिन्हित पूर्णांक),
		.flags	= 0,
	पूर्ण;
	पूर्णांक __user *ip = (पूर्णांक __user *)p;
	पूर्णांक error;

	/* legacy हाल */
	अगर (copy_from_user(ke.scancode, p, माप(अचिन्हित पूर्णांक)))
		वापस -EFAULT;

	error = input_get_keycode(dev, &ke);
	अगर (error)
		वापस error;

	अगर (put_user(ke.keycode, ip + 1))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक evdev_handle_get_keycode_v2(काष्ठा input_dev *dev, व्योम __user *p)
अणु
	काष्ठा input_keymap_entry ke;
	पूर्णांक error;

	अगर (copy_from_user(&ke, p, माप(ke)))
		वापस -EFAULT;

	error = input_get_keycode(dev, &ke);
	अगर (error)
		वापस error;

	अगर (copy_to_user(p, &ke, माप(ke)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक evdev_handle_set_keycode(काष्ठा input_dev *dev, व्योम __user *p)
अणु
	काष्ठा input_keymap_entry ke = अणु
		.len	= माप(अचिन्हित पूर्णांक),
		.flags	= 0,
	पूर्ण;
	पूर्णांक __user *ip = (पूर्णांक __user *)p;

	अगर (copy_from_user(ke.scancode, p, माप(अचिन्हित पूर्णांक)))
		वापस -EFAULT;

	अगर (get_user(ke.keycode, ip + 1))
		वापस -EFAULT;

	वापस input_set_keycode(dev, &ke);
पूर्ण

अटल पूर्णांक evdev_handle_set_keycode_v2(काष्ठा input_dev *dev, व्योम __user *p)
अणु
	काष्ठा input_keymap_entry ke;

	अगर (copy_from_user(&ke, p, माप(ke)))
		वापस -EFAULT;

	अगर (ke.len > माप(ke.scancode))
		वापस -EINVAL;

	वापस input_set_keycode(dev, &ke);
पूर्ण

/*
 * If we transfer state to the user, we should flush all pending events
 * of the same type from the client's queue. Otherwise, they might end up
 * with duplicate events, which can screw up client's state tracking.
 * If bits_to_user fails after flushing the queue, we queue a SYN_DROPPED
 * event so user-space will notice missing events.
 *
 * LOCKING:
 * We need to take event_lock beक्रमe buffer_lock to aव्योम dead-locks. But we
 * need the even_lock only to guarantee consistent state. We can safely release
 * it जबतक flushing the queue. This allows input-core to handle filters जबतक
 * we flush the queue.
 */
अटल पूर्णांक evdev_handle_get_val(काष्ठा evdev_client *client,
				काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
				अचिन्हित दीर्घ *bits, अचिन्हित पूर्णांक maxbit,
				अचिन्हित पूर्णांक maxlen, व्योम __user *p,
				पूर्णांक compat)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ *mem;

	mem = biपंचांगap_alloc(maxbit, GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	spin_lock_irq(&dev->event_lock);
	spin_lock(&client->buffer_lock);

	biपंचांगap_copy(mem, bits, maxbit);

	spin_unlock(&dev->event_lock);

	__evdev_flush_queue(client, type);

	spin_unlock_irq(&client->buffer_lock);

	ret = bits_to_user(mem, maxbit, maxlen, p, compat);
	अगर (ret < 0)
		evdev_queue_syn_dropped(client);

	biपंचांगap_मुक्त(mem);

	वापस ret;
पूर्ण

अटल पूर्णांक evdev_handle_mt_request(काष्ठा input_dev *dev,
				   अचिन्हित पूर्णांक size,
				   पूर्णांक __user *ip)
अणु
	स्थिर काष्ठा input_mt *mt = dev->mt;
	अचिन्हित पूर्णांक code;
	पूर्णांक max_slots;
	पूर्णांक i;

	अगर (get_user(code, &ip[0]))
		वापस -EFAULT;
	अगर (!mt || !input_is_mt_value(code))
		वापस -EINVAL;

	max_slots = (size - माप(__u32)) / माप(__s32);
	क्रम (i = 0; i < mt->num_slots && i < max_slots; i++) अणु
		पूर्णांक value = input_mt_get_value(&mt->slots[i], code);
		अगर (put_user(value, &ip[1 + i]))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evdev_revoke(काष्ठा evdev *evdev, काष्ठा evdev_client *client,
			काष्ठा file *file)
अणु
	client->revoked = true;
	evdev_ungrab(evdev, client);
	input_flush_device(&evdev->handle, file);
	wake_up_पूर्णांकerruptible_poll(&client->रुको, EPOLLHUP | EPOLLERR);

	वापस 0;
पूर्ण

/* must be called with evdev-mutex held */
अटल पूर्णांक evdev_set_mask(काष्ठा evdev_client *client,
			  अचिन्हित पूर्णांक type,
			  स्थिर व्योम __user *codes,
			  u32 codes_size,
			  पूर्णांक compat)
अणु
	अचिन्हित दीर्घ flags, *mask, *oldmask;
	माप_प्रकार cnt;
	पूर्णांक error;

	/* we allow unknown types and 'codes_size > size' क्रम क्रमward-compat */
	cnt = evdev_get_mask_cnt(type);
	अगर (!cnt)
		वापस 0;

	mask = biपंचांगap_zalloc(cnt, GFP_KERNEL);
	अगर (!mask)
		वापस -ENOMEM;

	error = bits_from_user(mask, cnt - 1, codes_size, codes, compat);
	अगर (error < 0) अणु
		biपंचांगap_मुक्त(mask);
		वापस error;
	पूर्ण

	spin_lock_irqsave(&client->buffer_lock, flags);
	oldmask = client->evmasks[type];
	client->evmasks[type] = mask;
	spin_unlock_irqrestore(&client->buffer_lock, flags);

	biपंचांगap_मुक्त(oldmask);

	वापस 0;
पूर्ण

/* must be called with evdev-mutex held */
अटल पूर्णांक evdev_get_mask(काष्ठा evdev_client *client,
			  अचिन्हित पूर्णांक type,
			  व्योम __user *codes,
			  u32 codes_size,
			  पूर्णांक compat)
अणु
	अचिन्हित दीर्घ *mask;
	माप_प्रकार cnt, size, xfer_size;
	पूर्णांक i;
	पूर्णांक error;

	/* we allow unknown types and 'codes_size > size' क्रम क्रमward-compat */
	cnt = evdev_get_mask_cnt(type);
	size = माप(अचिन्हित दीर्घ) * BITS_TO_LONGS(cnt);
	xfer_size = min_t(माप_प्रकार, codes_size, size);

	अगर (cnt > 0) अणु
		mask = client->evmasks[type];
		अगर (mask) अणु
			error = bits_to_user(mask, cnt - 1,
					     xfer_size, codes, compat);
			अगर (error < 0)
				वापस error;
		पूर्ण अन्यथा अणु
			/* fake mask with all bits set */
			क्रम (i = 0; i < xfer_size; i++)
				अगर (put_user(0xffU, (u8 __user *)codes + i))
					वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (xfer_size < codes_size)
		अगर (clear_user(codes + xfer_size, codes_size - xfer_size))
			वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ evdev_करो_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			   व्योम __user *p, पूर्णांक compat_mode)
अणु
	काष्ठा evdev_client *client = file->निजी_data;
	काष्ठा evdev *evdev = client->evdev;
	काष्ठा input_dev *dev = evdev->handle.dev;
	काष्ठा input_असलinfo असल;
	काष्ठा input_mask mask;
	काष्ठा ff_effect effect;
	पूर्णांक __user *ip = (पूर्णांक __user *)p;
	अचिन्हित पूर्णांक i, t, u, v;
	अचिन्हित पूर्णांक size;
	पूर्णांक error;

	/* First we check क्रम fixed-length commands */
	चयन (cmd) अणु

	हाल EVIOCGVERSION:
		वापस put_user(EV_VERSION, ip);

	हाल EVIOCGID:
		अगर (copy_to_user(p, &dev->id, माप(काष्ठा input_id)))
			वापस -EFAULT;
		वापस 0;

	हाल EVIOCGREP:
		अगर (!test_bit(EV_REP, dev->evbit))
			वापस -ENOSYS;
		अगर (put_user(dev->rep[REP_DELAY], ip))
			वापस -EFAULT;
		अगर (put_user(dev->rep[REP_PERIOD], ip + 1))
			वापस -EFAULT;
		वापस 0;

	हाल EVIOCSREP:
		अगर (!test_bit(EV_REP, dev->evbit))
			वापस -ENOSYS;
		अगर (get_user(u, ip))
			वापस -EFAULT;
		अगर (get_user(v, ip + 1))
			वापस -EFAULT;

		input_inject_event(&evdev->handle, EV_REP, REP_DELAY, u);
		input_inject_event(&evdev->handle, EV_REP, REP_PERIOD, v);

		वापस 0;

	हाल EVIOCRMFF:
		वापस input_ff_erase(dev, (पूर्णांक)(अचिन्हित दीर्घ) p, file);

	हाल EVIOCGEFFECTS:
		i = test_bit(EV_FF, dev->evbit) ?
				dev->ff->max_effects : 0;
		अगर (put_user(i, ip))
			वापस -EFAULT;
		वापस 0;

	हाल EVIOCGRAB:
		अगर (p)
			वापस evdev_grab(evdev, client);
		अन्यथा
			वापस evdev_ungrab(evdev, client);

	हाल EVIOCREVOKE:
		अगर (p)
			वापस -EINVAL;
		अन्यथा
			वापस evdev_revoke(evdev, client, file);

	हाल EVIOCGMASK: अणु
		व्योम __user *codes_ptr;

		अगर (copy_from_user(&mask, p, माप(mask)))
			वापस -EFAULT;

		codes_ptr = (व्योम __user *)(अचिन्हित दीर्घ)mask.codes_ptr;
		वापस evdev_get_mask(client,
				      mask.type, codes_ptr, mask.codes_size,
				      compat_mode);
	पूर्ण

	हाल EVIOCSMASK: अणु
		स्थिर व्योम __user *codes_ptr;

		अगर (copy_from_user(&mask, p, माप(mask)))
			वापस -EFAULT;

		codes_ptr = (स्थिर व्योम __user *)(अचिन्हित दीर्घ)mask.codes_ptr;
		वापस evdev_set_mask(client,
				      mask.type, codes_ptr, mask.codes_size,
				      compat_mode);
	पूर्ण

	हाल EVIOCSCLOCKID:
		अगर (copy_from_user(&i, p, माप(अचिन्हित पूर्णांक)))
			वापस -EFAULT;

		वापस evdev_set_clk_type(client, i);

	हाल EVIOCGKEYCODE:
		वापस evdev_handle_get_keycode(dev, p);

	हाल EVIOCSKEYCODE:
		वापस evdev_handle_set_keycode(dev, p);

	हाल EVIOCGKEYCODE_V2:
		वापस evdev_handle_get_keycode_v2(dev, p);

	हाल EVIOCSKEYCODE_V2:
		वापस evdev_handle_set_keycode_v2(dev, p);
	पूर्ण

	size = _IOC_SIZE(cmd);

	/* Now check variable-length commands */
#घोषणा EVIOC_MASK_SIZE(nr)	((nr) & ~(_IOC_SIZEMASK << _IOC_SIZESHIFT))
	चयन (EVIOC_MASK_SIZE(cmd)) अणु

	हाल EVIOCGPROP(0):
		वापस bits_to_user(dev->propbit, INPUT_PROP_MAX,
				    size, p, compat_mode);

	हाल EVIOCGMTSLOTS(0):
		वापस evdev_handle_mt_request(dev, size, ip);

	हाल EVIOCGKEY(0):
		वापस evdev_handle_get_val(client, dev, EV_KEY, dev->key,
					    KEY_MAX, size, p, compat_mode);

	हाल EVIOCGLED(0):
		वापस evdev_handle_get_val(client, dev, EV_LED, dev->led,
					    LED_MAX, size, p, compat_mode);

	हाल EVIOCGSND(0):
		वापस evdev_handle_get_val(client, dev, EV_SND, dev->snd,
					    SND_MAX, size, p, compat_mode);

	हाल EVIOCGSW(0):
		वापस evdev_handle_get_val(client, dev, EV_SW, dev->sw,
					    SW_MAX, size, p, compat_mode);

	हाल EVIOCGNAME(0):
		वापस str_to_user(dev->name, size, p);

	हाल EVIOCGPHYS(0):
		वापस str_to_user(dev->phys, size, p);

	हाल EVIOCGUNIQ(0):
		वापस str_to_user(dev->uniq, size, p);

	हाल EVIOC_MASK_SIZE(EVIOCSFF):
		अगर (input_ff_effect_from_user(p, size, &effect))
			वापस -EFAULT;

		error = input_ff_upload(dev, &effect, file);
		अगर (error)
			वापस error;

		अगर (put_user(effect.id, &(((काष्ठा ff_effect __user *)p)->id)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	/* Multi-number variable-length handlers */
	अगर (_IOC_TYPE(cmd) != 'E')
		वापस -EINVAL;

	अगर (_IOC_सूची(cmd) == _IOC_READ) अणु

		अगर ((_IOC_NR(cmd) & ~EV_MAX) == _IOC_NR(EVIOCGBIT(0, 0)))
			वापस handle_eviocgbit(dev,
						_IOC_NR(cmd) & EV_MAX, size,
						p, compat_mode);

		अगर ((_IOC_NR(cmd) & ~ABS_MAX) == _IOC_NR(EVIOCGABS(0))) अणु

			अगर (!dev->असलinfo)
				वापस -EINVAL;

			t = _IOC_NR(cmd) & ABS_MAX;
			असल = dev->असलinfo[t];

			अगर (copy_to_user(p, &असल, min_t(माप_प्रकार,
					size, माप(काष्ठा input_असलinfo))))
				वापस -EFAULT;

			वापस 0;
		पूर्ण
	पूर्ण

	अगर (_IOC_सूची(cmd) == _IOC_WRITE) अणु

		अगर ((_IOC_NR(cmd) & ~ABS_MAX) == _IOC_NR(EVIOCSABS(0))) अणु

			अगर (!dev->असलinfo)
				वापस -EINVAL;

			t = _IOC_NR(cmd) & ABS_MAX;

			अगर (copy_from_user(&असल, p, min_t(माप_प्रकार,
					size, माप(काष्ठा input_असलinfo))))
				वापस -EFAULT;

			अगर (size < माप(काष्ठा input_असलinfo))
				असल.resolution = 0;

			/* We can't change number of reserved MT slots */
			अगर (t == ABS_MT_SLOT)
				वापस -EINVAL;

			/*
			 * Take event lock to ensure that we are not
			 * changing device parameters in the middle
			 * of event.
			 */
			spin_lock_irq(&dev->event_lock);
			dev->असलinfo[t] = असल;
			spin_unlock_irq(&dev->event_lock);

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल दीर्घ evdev_ioctl_handler(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				व्योम __user *p, पूर्णांक compat_mode)
अणु
	काष्ठा evdev_client *client = file->निजी_data;
	काष्ठा evdev *evdev = client->evdev;
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&evdev->mutex);
	अगर (retval)
		वापस retval;

	अगर (!evdev->exist || client->revoked) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	retval = evdev_करो_ioctl(file, cmd, p, compat_mode);

 out:
	mutex_unlock(&evdev->mutex);
	वापस retval;
पूर्ण

अटल दीर्घ evdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस evdev_ioctl_handler(file, cmd, (व्योम __user *)arg, 0);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ evdev_ioctl_compat(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस evdev_ioctl_handler(file, cmd, compat_ptr(arg), 1);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations evdev_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= evdev_पढ़ो,
	.ग_लिखो		= evdev_ग_लिखो,
	.poll		= evdev_poll,
	.खोलो		= evdev_खोलो,
	.release	= evdev_release,
	.unlocked_ioctl	= evdev_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= evdev_ioctl_compat,
#पूर्ण_अगर
	.fasync		= evdev_fasync,
	.llseek		= no_llseek,
पूर्ण;

/*
 * Mark device non-existent. This disables ग_लिखोs, ioctls and
 * prevents new users from खोलोing the device. Alपढ़ोy posted
 * blocking पढ़ोs will stay, however new ones will fail.
 */
अटल व्योम evdev_mark_dead(काष्ठा evdev *evdev)
अणु
	mutex_lock(&evdev->mutex);
	evdev->exist = false;
	mutex_unlock(&evdev->mutex);
पूर्ण

अटल व्योम evdev_cleanup(काष्ठा evdev *evdev)
अणु
	काष्ठा input_handle *handle = &evdev->handle;

	evdev_mark_dead(evdev);
	evdev_hangup(evdev);

	/* evdev is marked dead so no one अन्यथा accesses evdev->खोलो */
	अगर (evdev->खोलो) अणु
		input_flush_device(handle, शून्य);
		input_बंद_device(handle);
	पूर्ण
पूर्ण

/*
 * Create new evdev device. Note that input core serializes calls
 * to connect and disconnect.
 */
अटल पूर्णांक evdev_connect(काष्ठा input_handler *handler, काष्ठा input_dev *dev,
			 स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा evdev *evdev;
	पूर्णांक minor;
	पूर्णांक dev_no;
	पूर्णांक error;

	minor = input_get_new_minor(EVDEV_MINOR_BASE, EVDEV_MINORS, true);
	अगर (minor < 0) अणु
		error = minor;
		pr_err("failed to reserve new minor: %d\n", error);
		वापस error;
	पूर्ण

	evdev = kzalloc(माप(काष्ठा evdev), GFP_KERNEL);
	अगर (!evdev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_minor;
	पूर्ण

	INIT_LIST_HEAD(&evdev->client_list);
	spin_lock_init(&evdev->client_lock);
	mutex_init(&evdev->mutex);
	evdev->exist = true;

	dev_no = minor;
	/* Normalize device number अगर it falls पूर्णांकo legacy range */
	अगर (dev_no < EVDEV_MINOR_BASE + EVDEV_MINORS)
		dev_no -= EVDEV_MINOR_BASE;
	dev_set_name(&evdev->dev, "event%d", dev_no);

	evdev->handle.dev = input_get_device(dev);
	evdev->handle.name = dev_name(&evdev->dev);
	evdev->handle.handler = handler;
	evdev->handle.निजी = evdev;

	evdev->dev.devt = MKDEV(INPUT_MAJOR, minor);
	evdev->dev.class = &input_class;
	evdev->dev.parent = &dev->dev;
	evdev->dev.release = evdev_मुक्त;
	device_initialize(&evdev->dev);

	error = input_रेजिस्टर_handle(&evdev->handle);
	अगर (error)
		जाओ err_मुक्त_evdev;

	cdev_init(&evdev->cdev, &evdev_fops);

	error = cdev_device_add(&evdev->cdev, &evdev->dev);
	अगर (error)
		जाओ err_cleanup_evdev;

	वापस 0;

 err_cleanup_evdev:
	evdev_cleanup(evdev);
	input_unरेजिस्टर_handle(&evdev->handle);
 err_मुक्त_evdev:
	put_device(&evdev->dev);
 err_मुक्त_minor:
	input_मुक्त_minor(minor);
	वापस error;
पूर्ण

अटल व्योम evdev_disconnect(काष्ठा input_handle *handle)
अणु
	काष्ठा evdev *evdev = handle->निजी;

	cdev_device_del(&evdev->cdev, &evdev->dev);
	evdev_cleanup(evdev);
	input_मुक्त_minor(MINOR(evdev->dev.devt));
	input_unरेजिस्टर_handle(handle);
	put_device(&evdev->dev);
पूर्ण

अटल स्थिर काष्ठा input_device_id evdev_ids[] = अणु
	अणु .driver_info = 1 पूर्ण,	/* Matches all devices */
	अणु पूर्ण,			/* Terminating zero entry */
पूर्ण;

MODULE_DEVICE_TABLE(input, evdev_ids);

अटल काष्ठा input_handler evdev_handler = अणु
	.event		= evdev_event,
	.events		= evdev_events,
	.connect	= evdev_connect,
	.disconnect	= evdev_disconnect,
	.legacy_minors	= true,
	.minor		= EVDEV_MINOR_BASE,
	.name		= "evdev",
	.id_table	= evdev_ids,
पूर्ण;

अटल पूर्णांक __init evdev_init(व्योम)
अणु
	वापस input_रेजिस्टर_handler(&evdev_handler);
पूर्ण

अटल व्योम __निकास evdev_निकास(व्योम)
अणु
	input_unरेजिस्टर_handler(&evdev_handler);
पूर्ण

module_init(evdev_init);
module_निकास(evdev_निकास);

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Input driver event char devices");
MODULE_LICENSE("GPL");
