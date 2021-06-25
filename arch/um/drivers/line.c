<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/irqवापस.h>
#समावेश <linux/kd.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>

#समावेश "chan.h"
#समावेश <irq_kern.h>
#समावेश <irq_user.h>
#समावेश <kern_util.h>
#समावेश <os.h>

#घोषणा LINE_बफ_मानE 4096

अटल irqवापस_t line_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा chan *chan = data;
	काष्ठा line *line = chan->line;

	अगर (line)
		chan_पूर्णांकerrupt(line, irq);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Returns the मुक्त space inside the ring buffer of this line.
 *
 * Should be called जबतक holding line->lock (this करोes not modअगरy data).
 */
अटल पूर्णांक ग_लिखो_room(काष्ठा line *line)
अणु
	पूर्णांक n;

	अगर (line->buffer == शून्य)
		वापस LINE_बफ_मानE - 1;

	/* This is क्रम the हाल where the buffer is wrapped! */
	n = line->head - line->tail;

	अगर (n <= 0)
		n += LINE_बफ_मानE; /* The other हाल */
	वापस n - 1;
पूर्ण

पूर्णांक line_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा line *line = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक room;

	spin_lock_irqsave(&line->lock, flags);
	room = ग_लिखो_room(line);
	spin_unlock_irqrestore(&line->lock, flags);

	वापस room;
पूर्ण

पूर्णांक line_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा line *line = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&line->lock, flags);
	/* ग_लिखो_room subtracts 1 क्रम the needed शून्य, so we पढ़ोd it.*/
	ret = LINE_बफ_मानE - (ग_लिखो_room(line) + 1);
	spin_unlock_irqrestore(&line->lock, flags);

	वापस ret;
पूर्ण

/*
 * This copies the content of buf पूर्णांकo the circular buffer associated with
 * this line.
 * The वापस value is the number of अक्षरacters actually copied, i.e. the ones
 * क्रम which there was space: this function is not supposed to ever flush out
 * the circular buffer.
 *
 * Must be called जबतक holding line->lock!
 */
अटल पूर्णांक buffer_data(काष्ठा line *line, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक end, room;

	अगर (line->buffer == शून्य) अणु
		line->buffer = kदो_स्मृति(LINE_बफ_मानE, GFP_ATOMIC);
		अगर (line->buffer == शून्य) अणु
			prपूर्णांकk(KERN_ERR "buffer_data - atomic allocation "
			       "failed\n");
			वापस 0;
		पूर्ण
		line->head = line->buffer;
		line->tail = line->buffer;
	पूर्ण

	room = ग_लिखो_room(line);
	len = (len > room) ? room : len;

	end = line->buffer + LINE_बफ_मानE - line->tail;

	अगर (len < end) अणु
		स_नकल(line->tail, buf, len);
		line->tail += len;
	पूर्ण
	अन्यथा अणु
		/* The circular buffer is wrapping */
		स_नकल(line->tail, buf, end);
		buf += end;
		स_नकल(line->buffer, buf, len - end);
		line->tail = line->buffer + len - end;
	पूर्ण

	वापस len;
पूर्ण

/*
 * Flushes the ring buffer to the output channels. That is, ग_लिखो_chan is
 * called, passing it line->head as buffer, and an appropriate count.
 *
 * On निकास, वापसs 1 when the buffer is empty,
 * 0 when the buffer is not empty on निकास,
 * and -त्रुटि_सं when an error occurred.
 *
 * Must be called जबतक holding line->lock!*/
अटल पूर्णांक flush_buffer(काष्ठा line *line)
अणु
	पूर्णांक n, count;

	अगर ((line->buffer == शून्य) || (line->head == line->tail))
		वापस 1;

	अगर (line->tail < line->head) अणु
		/* line->buffer + LINE_बफ_मानE is the end of the buffer! */
		count = line->buffer + LINE_बफ_मानE - line->head;

		n = ग_लिखो_chan(line->chan_out, line->head, count,
			       line->driver->ग_लिखो_irq);
		अगर (n < 0)
			वापस n;
		अगर (n == count) अणु
			/*
			 * We have flushed from ->head to buffer end, now we
			 * must flush only from the beginning to ->tail.
			 */
			line->head = line->buffer;
		पूर्ण अन्यथा अणु
			line->head += n;
			वापस 0;
		पूर्ण
	पूर्ण

	count = line->tail - line->head;
	n = ग_लिखो_chan(line->chan_out, line->head, count,
		       line->driver->ग_लिखो_irq);

	अगर (n < 0)
		वापस n;

	line->head += n;
	वापस line->head == line->tail;
पूर्ण

व्योम line_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा line *line = tty->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&line->lock, flags);
	flush_buffer(line);
	spin_unlock_irqrestore(&line->lock, flags);
पूर्ण

/*
 * We map both ->flush_अक्षरs and ->put_अक्षर (which go in pair) onto
 * ->flush_buffer and ->ग_लिखो. Hope it's not that bad.
 */
व्योम line_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	line_flush_buffer(tty);
पूर्ण

पूर्णांक line_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा line *line = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक n, ret = 0;

	spin_lock_irqsave(&line->lock, flags);
	अगर (line->head != line->tail)
		ret = buffer_data(line, buf, len);
	अन्यथा अणु
		n = ग_लिखो_chan(line->chan_out, buf, len,
			       line->driver->ग_लिखो_irq);
		अगर (n < 0) अणु
			ret = n;
			जाओ out_up;
		पूर्ण

		len -= n;
		ret += n;
		अगर (len > 0)
			ret += buffer_data(line, buf + n, len);
	पूर्ण
out_up:
	spin_unlock_irqrestore(&line->lock, flags);
	वापस ret;
पूर्ण

व्योम line_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios * old)
अणु
	/* nothing */
पूर्ण

व्योम line_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा line *line = tty->driver_data;

	deactivate_chan(line->chan_in, line->driver->पढ़ो_irq);
	line->throttled = 1;
पूर्ण

व्योम line_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा line *line = tty->driver_data;

	line->throttled = 0;
	chan_पूर्णांकerrupt(line, line->driver->पढ़ो_irq);
पूर्ण

अटल irqवापस_t line_ग_लिखो_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा chan *chan = data;
	काष्ठा line *line = chan->line;
	पूर्णांक err;

	/*
	 * Interrupts are disabled here because genirq keep irqs disabled when
	 * calling the action handler.
	 */

	spin_lock(&line->lock);
	err = flush_buffer(line);
	अगर (err == 0) अणु
		spin_unlock(&line->lock);
		वापस IRQ_NONE;
	पूर्ण अन्यथा अगर ((err < 0) && (err != -EAGAIN)) अणु
		line->head = line->buffer;
		line->tail = line->buffer;
	पूर्ण
	spin_unlock(&line->lock);

	tty_port_tty_wakeup(&line->port);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक line_setup_irq(पूर्णांक fd, पूर्णांक input, पूर्णांक output, काष्ठा line *line, व्योम *data)
अणु
	स्थिर काष्ठा line_driver *driver = line->driver;
	पूर्णांक err;

	अगर (input) अणु
		err = um_request_irq(driver->पढ़ो_irq, fd, IRQ_READ,
				     line_पूर्णांकerrupt, IRQF_SHARED,
				     driver->पढ़ो_irq_name, data);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (output) अणु
		err = um_request_irq(driver->ग_लिखो_irq, fd, IRQ_WRITE,
				     line_ग_लिखो_पूर्णांकerrupt, IRQF_SHARED,
				     driver->ग_लिखो_irq_name, data);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक line_activate(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक ret;
	काष्ठा line *line = tty->driver_data;

	ret = enable_chan(line);
	अगर (ret)
		वापस ret;

	अगर (!line->sigio) अणु
		chan_enable_winch(line->chan_out, port);
		line->sigio = 1;
	पूर्ण

	chan_winकरोw_size(line, &tty->winsize.ws_row,
		&tty->winsize.ws_col);

	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_winch(काष्ठा tty_काष्ठा *tty);

अटल व्योम line_deकाष्ठा(काष्ठा tty_port *port)
अणु
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(port);
	काष्ठा line *line = tty->driver_data;

	अगर (line->sigio) अणु
		unरेजिस्टर_winch(tty);
		line->sigio = 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tty_port_operations line_port_ops = अणु
	.activate = line_activate,
	.deकाष्ठा = line_deकाष्ठा,
पूर्ण;

पूर्णांक line_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा line *line = tty->driver_data;

	वापस tty_port_खोलो(&line->port, tty, filp);
पूर्ण

पूर्णांक line_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty,
		 काष्ठा line *line)
अणु
	पूर्णांक ret;

	ret = tty_standard_install(driver, tty);
	अगर (ret)
		वापस ret;

	tty->driver_data = line;

	वापस 0;
पूर्ण

व्योम line_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	काष्ठा line *line = tty->driver_data;

	tty_port_बंद(&line->port, tty, filp);
पूर्ण

व्योम line_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा line *line = tty->driver_data;

	tty_port_hangup(&line->port);
पूर्ण

व्योम बंद_lines(काष्ठा line *lines, पूर्णांक nlines)
अणु
	पूर्णांक i;

	क्रम(i = 0; i < nlines; i++)
		बंद_chan(&lines[i]);
पूर्ण

पूर्णांक setup_one_line(काष्ठा line *lines, पूर्णांक n, अक्षर *init,
		   स्थिर काष्ठा chan_opts *opts, अक्षर **error_out)
अणु
	काष्ठा line *line = &lines[n];
	काष्ठा tty_driver *driver = line->driver->driver;
	पूर्णांक err = -EINVAL;

	अगर (line->port.count) अणु
		*error_out = "Device is already open";
		जाओ out;
	पूर्ण

	अगर (!म_भेद(init, "none")) अणु
		अगर (line->valid) अणु
			line->valid = 0;
			kमुक्त(line->init_str);
			tty_unरेजिस्टर_device(driver, n);
			parse_chan_pair(शून्य, line, n, opts, error_out);
			err = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अक्षर *new = kstrdup(init, GFP_KERNEL);
		अगर (!new) अणु
			*error_out = "Failed to allocate memory";
			वापस -ENOMEM;
		पूर्ण
		अगर (line->valid) अणु
			tty_unरेजिस्टर_device(driver, n);
			kमुक्त(line->init_str);
		पूर्ण
		line->init_str = new;
		line->valid = 1;
		err = parse_chan_pair(new, line, n, opts, error_out);
		अगर (!err) अणु
			काष्ठा device *d = tty_port_रेजिस्टर_device(&line->port,
					driver, n, शून्य);
			अगर (IS_ERR(d)) अणु
				*error_out = "Failed to register device";
				err = PTR_ERR(d);
				parse_chan_pair(शून्य, line, n, opts, error_out);
			पूर्ण
		पूर्ण
		अगर (err) अणु
			line->init_str = शून्य;
			line->valid = 0;
			kमुक्त(new);
		पूर्ण
	पूर्ण
out:
	वापस err;
पूर्ण

/*
 * Common setup code क्रम both startup command line and mconsole initialization.
 * @lines contains the array (of size @num) to modअगरy;
 * @init is the setup string;
 * @error_out is an error string in the हाल of failure;
 */

पूर्णांक line_setup(अक्षर **conf, अचिन्हित पूर्णांक num, अक्षर **def,
	       अक्षर *init, अक्षर *name)
अणु
	अक्षर *error;

	अगर (*init == '=') अणु
		/*
		 * We said con=/ssl= instead of con#=, so we are configuring all
		 * consoles at once.
		 */
		*def = init + 1;
	पूर्ण अन्यथा अणु
		अक्षर *end;
		अचिन्हित n = simple_म_से_अदीर्घ(init, &end, 0);

		अगर (*end != '=') अणु
			error = "Couldn't parse device number";
			जाओ out;
		पूर्ण
		अगर (n >= num) अणु
			error = "Device number out of range";
			जाओ out;
		पूर्ण
		conf[n] = end + 1;
	पूर्ण
	वापस 0;

out:
	prपूर्णांकk(KERN_ERR "Failed to set up %s with "
	       "configuration string \"%s\" : %s\n", name, init, error);
	वापस -EINVAL;
पूर्ण

पूर्णांक line_config(काष्ठा line *lines, अचिन्हित पूर्णांक num, अक्षर *str,
		स्थिर काष्ठा chan_opts *opts, अक्षर **error_out)
अणु
	अक्षर *end;
	पूर्णांक n;

	अगर (*str == '=') अणु
		*error_out = "Can't configure all devices from mconsole";
		वापस -EINVAL;
	पूर्ण

	n = simple_म_से_अदीर्घ(str, &end, 0);
	अगर (*end++ != '=') अणु
		*error_out = "Couldn't parse device number";
		वापस -EINVAL;
	पूर्ण
	अगर (n >= num) अणु
		*error_out = "Device number out of range";
		वापस -EINVAL;
	पूर्ण

	वापस setup_one_line(lines, n, end, opts, error_out);
पूर्ण

पूर्णांक line_get_config(अक्षर *name, काष्ठा line *lines, अचिन्हित पूर्णांक num, अक्षर *str,
		    पूर्णांक size, अक्षर **error_out)
अणु
	काष्ठा line *line;
	अक्षर *end;
	पूर्णांक dev, n = 0;

	dev = simple_म_से_अदीर्घ(name, &end, 0);
	अगर ((*end != '\0') || (end == name)) अणु
		*error_out = "line_get_config failed to parse device number";
		वापस 0;
	पूर्ण

	अगर ((dev < 0) || (dev >= num)) अणु
		*error_out = "device number out of range";
		वापस 0;
	पूर्ण

	line = &lines[dev];

	अगर (!line->valid)
		CONFIG_CHUNK(str, size, n, "none", 1);
	अन्यथा अणु
		काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&line->port);
		अगर (tty == शून्य) अणु
			CONFIG_CHUNK(str, size, n, line->init_str, 1);
		पूर्ण अन्यथा अणु
			n = chan_config_string(line, str, size, error_out);
			tty_kref_put(tty);
		पूर्ण
	पूर्ण

	वापस n;
पूर्ण

पूर्णांक line_id(अक्षर **str, पूर्णांक *start_out, पूर्णांक *end_out)
अणु
	अक्षर *end;
	पूर्णांक n;

	n = simple_म_से_अदीर्घ(*str, &end, 0);
	अगर ((*end != '\0') || (end == *str))
		वापस -1;

	*str = end;
	*start_out = n;
	*end_out = n;
	वापस n;
पूर्ण

पूर्णांक line_हटाओ(काष्ठा line *lines, अचिन्हित पूर्णांक num, पूर्णांक n, अक्षर **error_out)
अणु
	अगर (n >= num) अणु
		*error_out = "Device number out of range";
		वापस -EINVAL;
	पूर्ण
	वापस setup_one_line(lines, n, "none", शून्य, error_out);
पूर्ण

पूर्णांक रेजिस्टर_lines(काष्ठा line_driver *line_driver,
		   स्थिर काष्ठा tty_operations *ops,
		   काष्ठा line *lines, पूर्णांक nlines)
अणु
	काष्ठा tty_driver *driver = alloc_tty_driver(nlines);
	पूर्णांक err;
	पूर्णांक i;

	अगर (!driver)
		वापस -ENOMEM;

	driver->driver_name = line_driver->name;
	driver->name = line_driver->device_name;
	driver->major = line_driver->major;
	driver->minor_start = line_driver->minor_start;
	driver->type = line_driver->type;
	driver->subtype = line_driver->subtype;
	driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	driver->init_termios = tty_std_termios;
	
	क्रम (i = 0; i < nlines; i++) अणु
		tty_port_init(&lines[i].port);
		lines[i].port.ops = &line_port_ops;
		spin_lock_init(&lines[i].lock);
		lines[i].driver = line_driver;
		INIT_LIST_HEAD(&lines[i].chan_list);
	पूर्ण
	tty_set_operations(driver, ops);

	err = tty_रेजिस्टर_driver(driver);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "register_lines : can't register %s driver\n",
		       line_driver->name);
		put_tty_driver(driver);
		क्रम (i = 0; i < nlines; i++)
			tty_port_destroy(&lines[i].port);
		वापस err;
	पूर्ण

	line_driver->driver = driver;
	mconsole_रेजिस्टर_dev(&line_driver->mc);
	वापस 0;
पूर्ण

अटल DEFINE_SPINLOCK(winch_handler_lock);
अटल LIST_HEAD(winch_handlers);

काष्ठा winch अणु
	काष्ठा list_head list;
	पूर्णांक fd;
	पूर्णांक tty_fd;
	पूर्णांक pid;
	काष्ठा tty_port *port;
	अचिन्हित दीर्घ stack;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल व्योम __मुक्त_winch(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा winch *winch = container_of(work, काष्ठा winch, work);
	um_मुक्त_irq(WINCH_IRQ, winch);

	अगर (winch->pid != -1)
		os_समाप्त_process(winch->pid, 1);
	अगर (winch->stack != 0)
		मुक्त_stack(winch->stack, 0);
	kमुक्त(winch);
पूर्ण

अटल व्योम मुक्त_winch(काष्ठा winch *winch)
अणु
	पूर्णांक fd = winch->fd;
	winch->fd = -1;
	अगर (fd != -1)
		os_बंद_file(fd);
	__मुक्त_winch(&winch->work);
पूर्ण

अटल irqवापस_t winch_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा winch *winch = data;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा line *line;
	पूर्णांक fd = winch->fd;
	पूर्णांक err;
	अक्षर c;
	काष्ठा pid *pgrp;

	अगर (fd != -1) अणु
		err = generic_पढ़ो(fd, &c, शून्य);
		अगर (err < 0) अणु
			अगर (err != -EAGAIN) अणु
				winch->fd = -1;
				list_del(&winch->list);
				os_बंद_file(fd);
				prपूर्णांकk(KERN_ERR "winch_interrupt : "
				       "read failed, errno = %d\n", -err);
				prपूर्णांकk(KERN_ERR "fd %d is losing SIGWINCH "
				       "support\n", winch->tty_fd);
				INIT_WORK(&winch->work, __मुक्त_winch);
				schedule_work(&winch->work);
				वापस IRQ_HANDLED;
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण
	tty = tty_port_tty_get(winch->port);
	अगर (tty != शून्य) अणु
		line = tty->driver_data;
		अगर (line != शून्य) अणु
			chan_winकरोw_size(line, &tty->winsize.ws_row,
					 &tty->winsize.ws_col);
			pgrp = tty_get_pgrp(tty);
			अगर (pgrp)
				समाप्त_pgrp(pgrp, SIGWINCH, 1);
			put_pid(pgrp);
		पूर्ण
		tty_kref_put(tty);
	पूर्ण
 out:
	वापस IRQ_HANDLED;
पूर्ण

व्योम रेजिस्टर_winch_irq(पूर्णांक fd, पूर्णांक tty_fd, पूर्णांक pid, काष्ठा tty_port *port,
			अचिन्हित दीर्घ stack)
अणु
	काष्ठा winch *winch;

	winch = kदो_स्मृति(माप(*winch), GFP_KERNEL);
	अगर (winch == शून्य) अणु
		prपूर्णांकk(KERN_ERR "register_winch_irq - kmalloc failed\n");
		जाओ cleanup;
	पूर्ण

	*winch = ((काष्ठा winch) अणु .list  	= LIST_HEAD_INIT(winch->list),
				   .fd  	= fd,
				   .tty_fd 	= tty_fd,
				   .pid  	= pid,
				   .port 	= port,
				   .stack	= stack पूर्ण);

	अगर (um_request_irq(WINCH_IRQ, fd, IRQ_READ, winch_पूर्णांकerrupt,
			   IRQF_SHARED, "winch", winch) < 0) अणु
		prपूर्णांकk(KERN_ERR "register_winch_irq - failed to register "
		       "IRQ\n");
		जाओ out_मुक्त;
	पूर्ण

	spin_lock(&winch_handler_lock);
	list_add(&winch->list, &winch_handlers);
	spin_unlock(&winch_handler_lock);

	वापस;

 out_मुक्त:
	kमुक्त(winch);
 cleanup:
	os_समाप्त_process(pid, 1);
	os_बंद_file(fd);
	अगर (stack != 0)
		मुक्त_stack(stack, 0);
पूर्ण

अटल व्योम unरेजिस्टर_winch(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा list_head *ele, *next;
	काष्ठा winch *winch;
	काष्ठा tty_काष्ठा *wtty;

	spin_lock(&winch_handler_lock);

	list_क्रम_each_safe(ele, next, &winch_handlers) अणु
		winch = list_entry(ele, काष्ठा winch, list);
		wtty = tty_port_tty_get(winch->port);
		अगर (wtty == tty) अणु
			list_del(&winch->list);
			spin_unlock(&winch_handler_lock);
			मुक्त_winch(winch);
			अवरोध;
		पूर्ण
		tty_kref_put(wtty);
	पूर्ण
	spin_unlock(&winch_handler_lock);
पूर्ण

अटल व्योम winch_cleanup(व्योम)
अणु
	काष्ठा winch *winch;

	spin_lock(&winch_handler_lock);
	जबतक ((winch = list_first_entry_or_null(&winch_handlers,
						 काष्ठा winch, list))) अणु
		list_del(&winch->list);
		spin_unlock(&winch_handler_lock);

		मुक्त_winch(winch);

		spin_lock(&winch_handler_lock);
	पूर्ण

	spin_unlock(&winch_handler_lock);
पूर्ण
__uml_निकासcall(winch_cleanup);

अक्षर *add_xterm_umid(अक्षर *base)
अणु
	अक्षर *umid, *title;
	पूर्णांक len;

	umid = get_umid();
	अगर (*umid == '\0')
		वापस base;

	len = म_माप(base) + म_माप(" ()") + म_माप(umid) + 1;
	title = kदो_स्मृति(len, GFP_KERNEL);
	अगर (title == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Failed to allocate buffer for xterm title\n");
		वापस base;
	पूर्ण

	snम_लिखो(title, len, "%s (%s)", base, umid);
	वापस title;
पूर्ण
