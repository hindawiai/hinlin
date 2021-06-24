<शैली गुरु>
/*
 * userio kernel serio device emulation module
 * Copyright (C) 2015 Red Hat
 * Copyright (C) 2015 Stephen Chandler Paul <thatslyude@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
 * General Public License क्रम more details.
 */

#समावेश <linux/circ_buf.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/sched.h>
#समावेश <linux/poll.h>
#समावेश <uapi/linux/userपन.स>

#घोषणा USERIO_NAME		"userio"
#घोषणा USERIO_बफ_मानE		16

अटल काष्ठा miscdevice userio_misc;

काष्ठा userio_device अणु
	काष्ठा serio *serio;
	काष्ठा mutex mutex;

	bool running;

	u8 head;
	u8 tail;

	spinlock_t buf_lock;
	अचिन्हित अक्षर buf[USERIO_बफ_मानE];

	रुको_queue_head_t रुकोq;
पूर्ण;

/**
 * userio_device_ग_लिखो - Write data from serio to a userio device in userspace
 * @id: The serio port क्रम the userio device
 * @val: The data to ग_लिखो to the device
 */
अटल पूर्णांक userio_device_ग_लिखो(काष्ठा serio *id, अचिन्हित अक्षर val)
अणु
	काष्ठा userio_device *userio = id->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&userio->buf_lock, flags);

	userio->buf[userio->head] = val;
	userio->head = (userio->head + 1) % USERIO_बफ_मानE;

	अगर (userio->head == userio->tail)
		dev_warn(userio_misc.this_device,
			 "Buffer overflowed, userio client isn't keeping up");

	spin_unlock_irqrestore(&userio->buf_lock, flags);

	wake_up_पूर्णांकerruptible(&userio->रुकोq);

	वापस 0;
पूर्ण

अटल पूर्णांक userio_अक्षर_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा userio_device *userio;

	userio = kzalloc(माप(काष्ठा userio_device), GFP_KERNEL);
	अगर (!userio)
		वापस -ENOMEM;

	mutex_init(&userio->mutex);
	spin_lock_init(&userio->buf_lock);
	init_रुकोqueue_head(&userio->रुकोq);

	userio->serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!userio->serio) अणु
		kमुक्त(userio);
		वापस -ENOMEM;
	पूर्ण

	userio->serio->ग_लिखो = userio_device_ग_लिखो;
	userio->serio->port_data = userio;

	file->निजी_data = userio;

	वापस 0;
पूर्ण

अटल पूर्णांक userio_अक्षर_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा userio_device *userio = file->निजी_data;

	अगर (userio->running) अणु
		/*
		 * Don't मुक्त the serio port here, serio_unरेजिस्टर_port()
		 * करोes it क्रम us.
		 */
		serio_unरेजिस्टर_port(userio->serio);
	पूर्ण अन्यथा अणु
		kमुक्त(userio->serio);
	पूर्ण

	kमुक्त(userio);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार userio_अक्षर_पढ़ो(काष्ठा file *file, अक्षर __user *user_buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा userio_device *userio = file->निजी_data;
	पूर्णांक error;
	माप_प्रकार nonwrap_len, copylen;
	अचिन्हित अक्षर buf[USERIO_बफ_मानE];
	अचिन्हित दीर्घ flags;

	/*
	 * By the समय we get here, the data that was रुकोing might have
	 * been taken by another thपढ़ो. Grab the buffer lock and check अगर
	 * there's still any data रुकोing, otherwise repeat this process
	 * until we have data (unless the file descriptor is non-blocking
	 * of course).
	 */
	क्रम (;;) अणु
		spin_lock_irqsave(&userio->buf_lock, flags);

		nonwrap_len = CIRC_CNT_TO_END(userio->head,
					      userio->tail,
					      USERIO_बफ_मानE);
		copylen = min(nonwrap_len, count);
		अगर (copylen) अणु
			स_नकल(buf, &userio->buf[userio->tail], copylen);
			userio->tail = (userio->tail + copylen) %
							USERIO_बफ_मानE;
		पूर्ण

		spin_unlock_irqrestore(&userio->buf_lock, flags);

		अगर (nonwrap_len)
			अवरोध;

		/* buffer was/is empty */
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		/*
		 * count == 0 is special - no IO is करोne but we check
		 * क्रम error conditions (see above).
		 */
		अगर (count == 0)
			वापस 0;

		error = रुको_event_पूर्णांकerruptible(userio->रुकोq,
						 userio->head != userio->tail);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (copylen)
		अगर (copy_to_user(user_buffer, buf, copylen))
			वापस -EFAULT;

	वापस copylen;
पूर्ण

अटल sमाप_प्रकार userio_अक्षर_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा userio_device *userio = file->निजी_data;
	काष्ठा userio_cmd cmd;
	पूर्णांक error;

	अगर (count != माप(cmd)) अणु
		dev_warn(userio_misc.this_device, "Invalid payload size\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&cmd, buffer, माप(cmd)))
		वापस -EFAULT;

	error = mutex_lock_पूर्णांकerruptible(&userio->mutex);
	अगर (error)
		वापस error;

	चयन (cmd.type) अणु
	हाल USERIO_CMD_REGISTER:
		अगर (!userio->serio->id.type) अणु
			dev_warn(userio_misc.this_device,
				 "No port type given on /dev/userio\n");

			error = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (userio->running) अणु
			dev_warn(userio_misc.this_device,
				 "Begin command sent, but we're already running\n");
			error = -EBUSY;
			जाओ out;
		पूर्ण

		userio->running = true;
		serio_रेजिस्टर_port(userio->serio);
		अवरोध;

	हाल USERIO_CMD_SET_PORT_TYPE:
		अगर (userio->running) अणु
			dev_warn(userio_misc.this_device,
				 "Can't change port type on an already running userio instance\n");
			error = -EBUSY;
			जाओ out;
		पूर्ण

		userio->serio->id.type = cmd.data;
		अवरोध;

	हाल USERIO_CMD_SEND_INTERRUPT:
		अगर (!userio->running) अणु
			dev_warn(userio_misc.this_device,
				 "The device must be registered before sending interrupts\n");
			error = -ENODEV;
			जाओ out;
		पूर्ण

		serio_पूर्णांकerrupt(userio->serio, cmd.data, 0);
		अवरोध;

	शेष:
		error = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&userio->mutex);
	वापस error ?: count;
पूर्ण

अटल __poll_t userio_अक्षर_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा userio_device *userio = file->निजी_data;

	poll_रुको(file, &userio->रुकोq, रुको);

	अगर (userio->head != userio->tail)
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations userio_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= userio_अक्षर_खोलो,
	.release	= userio_अक्षर_release,
	.पढ़ो		= userio_अक्षर_पढ़ो,
	.ग_लिखो		= userio_अक्षर_ग_लिखो,
	.poll		= userio_अक्षर_poll,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice userio_misc = अणु
	.fops	= &userio_fops,
	.minor	= USERIO_MINOR,
	.name	= USERIO_NAME,
पूर्ण;
module_driver(userio_misc, misc_रेजिस्टर, misc_deरेजिस्टर);

MODULE_ALIAS_MISCDEV(USERIO_MINOR);
MODULE_ALIAS("devname:" USERIO_NAME);

MODULE_AUTHOR("Stephen Chandler Paul <thatslyude@gmail.com>");
MODULE_DESCRIPTION("Virtual Serio Device Support");
MODULE_LICENSE("GPL");
