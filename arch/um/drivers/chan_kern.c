<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश "chan.h"
#समावेश <os.h>
#समावेश <irq_kern.h>

#अगर_घोषित CONFIG_NOCONFIG_CHAN
अटल व्योम *not_configged_init(अक्षर *str, पूर्णांक device,
				स्थिर काष्ठा chan_opts *opts)
अणु
	prपूर्णांकk(KERN_ERR "Using a channel type which is configured out of "
	       "UML\n");
	वापस शून्य;
पूर्ण

अटल पूर्णांक not_configged_खोलो(पूर्णांक input, पूर्णांक output, पूर्णांक primary, व्योम *data,
			      अक्षर **dev_out)
अणु
	prपूर्णांकk(KERN_ERR "Using a channel type which is configured out of "
	       "UML\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम not_configged_बंद(पूर्णांक fd, व्योम *data)
अणु
	prपूर्णांकk(KERN_ERR "Using a channel type which is configured out of "
	       "UML\n");
पूर्ण

अटल पूर्णांक not_configged_पढ़ो(पूर्णांक fd, अक्षर *c_out, व्योम *data)
अणु
	prपूर्णांकk(KERN_ERR "Using a channel type which is configured out of "
	       "UML\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक not_configged_ग_लिखो(पूर्णांक fd, स्थिर अक्षर *buf, पूर्णांक len, व्योम *data)
अणु
	prपूर्णांकk(KERN_ERR "Using a channel type which is configured out of "
	       "UML\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक not_configged_console_ग_लिखो(पूर्णांक fd, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	prपूर्णांकk(KERN_ERR "Using a channel type which is configured out of "
	       "UML\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक not_configged_winकरोw_size(पूर्णांक fd, व्योम *data, अचिन्हित लघु *rows,
				     अचिन्हित लघु *cols)
अणु
	prपूर्णांकk(KERN_ERR "Using a channel type which is configured out of "
	       "UML\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम not_configged_मुक्त(व्योम *data)
अणु
	prपूर्णांकk(KERN_ERR "Using a channel type which is configured out of "
	       "UML\n");
पूर्ण

अटल स्थिर काष्ठा chan_ops not_configged_ops = अणु
	.init		= not_configged_init,
	.खोलो		= not_configged_खोलो,
	.बंद		= not_configged_बंद,
	.पढ़ो		= not_configged_पढ़ो,
	.ग_लिखो		= not_configged_ग_लिखो,
	.console_ग_लिखो	= not_configged_console_ग_लिखो,
	.winकरोw_size	= not_configged_winकरोw_size,
	.मुक्त		= not_configged_मुक्त,
	.winch		= 0,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NOCONFIG_CHAN */

अटल पूर्णांक खोलो_one_chan(काष्ठा chan *chan)
अणु
	पूर्णांक fd, err;

	अगर (chan->खोलोed)
		वापस 0;

	अगर (chan->ops->खोलो == शून्य)
		fd = 0;
	अन्यथा fd = (*chan->ops->खोलो)(chan->input, chan->output, chan->primary,
				     chan->data, &chan->dev);
	अगर (fd < 0)
		वापस fd;

	err = os_set_fd_block(fd, 0);
	अगर (err) अणु
		(*chan->ops->बंद)(fd, chan->data);
		वापस err;
	पूर्ण

	chan->fd = fd;

	chan->खोलोed = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक खोलो_chan(काष्ठा list_head *chans)
अणु
	काष्ठा list_head *ele;
	काष्ठा chan *chan;
	पूर्णांक ret, err = 0;

	list_क्रम_each(ele, chans) अणु
		chan = list_entry(ele, काष्ठा chan, list);
		ret = खोलो_one_chan(chan);
		अगर (chan->primary)
			err = ret;
	पूर्ण
	वापस err;
पूर्ण

व्योम chan_enable_winch(काष्ठा chan *chan, काष्ठा tty_port *port)
अणु
	अगर (chan && chan->primary && chan->ops->winch)
		रेजिस्टर_winch(chan->fd, port);
पूर्ण

अटल व्योम line_समयr_cb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा line *line = container_of(work, काष्ठा line, task.work);

	अगर (!line->throttled)
		chan_पूर्णांकerrupt(line, line->driver->पढ़ो_irq);
पूर्ण

पूर्णांक enable_chan(काष्ठा line *line)
अणु
	काष्ठा list_head *ele;
	काष्ठा chan *chan;
	पूर्णांक err;

	INIT_DELAYED_WORK(&line->task, line_समयr_cb);

	list_क्रम_each(ele, &line->chan_list) अणु
		chan = list_entry(ele, काष्ठा chan, list);
		err = खोलो_one_chan(chan);
		अगर (err) अणु
			अगर (chan->primary)
				जाओ out_बंद;

			जारी;
		पूर्ण

		अगर (chan->enabled)
			जारी;
		err = line_setup_irq(chan->fd, chan->input, chan->output, line,
				     chan);
		अगर (err)
			जाओ out_बंद;

		chan->enabled = 1;
	पूर्ण

	वापस 0;

 out_बंद:
	बंद_chan(line);
	वापस err;
पूर्ण

/* Items are added in IRQ context, when मुक्त_irq can't be called, and
 * हटाओd in process context, when it can.
 * This handles पूर्णांकerrupt sources which disappear, and which need to
 * be permanently disabled.  This is discovered in IRQ context, but
 * the मुक्तing of the IRQ must be करोne later.
 */
अटल DEFINE_SPINLOCK(irqs_to_मुक्त_lock);
अटल LIST_HEAD(irqs_to_मुक्त);

व्योम मुक्त_irqs(व्योम)
अणु
	काष्ठा chan *chan;
	LIST_HEAD(list);
	काष्ठा list_head *ele;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&irqs_to_मुक्त_lock, flags);
	list_splice_init(&irqs_to_मुक्त, &list);
	spin_unlock_irqrestore(&irqs_to_मुक्त_lock, flags);

	list_क्रम_each(ele, &list) अणु
		chan = list_entry(ele, काष्ठा chan, मुक्त_list);

		अगर (chan->input && chan->enabled)
			um_मुक्त_irq(chan->line->driver->पढ़ो_irq, chan);
		अगर (chan->output && chan->enabled)
			um_मुक्त_irq(chan->line->driver->ग_लिखो_irq, chan);
		chan->enabled = 0;
	पूर्ण
पूर्ण

अटल व्योम बंद_one_chan(काष्ठा chan *chan, पूर्णांक delay_मुक्त_irq)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!chan->खोलोed)
		वापस;

	अगर (delay_मुक्त_irq) अणु
		spin_lock_irqsave(&irqs_to_मुक्त_lock, flags);
		list_add(&chan->मुक्त_list, &irqs_to_मुक्त);
		spin_unlock_irqrestore(&irqs_to_मुक्त_lock, flags);
	पूर्ण अन्यथा अणु
		अगर (chan->input && chan->enabled)
			um_मुक्त_irq(chan->line->driver->पढ़ो_irq, chan);
		अगर (chan->output && chan->enabled)
			um_मुक्त_irq(chan->line->driver->ग_लिखो_irq, chan);
		chan->enabled = 0;
	पूर्ण
	अगर (chan->ops->बंद != शून्य)
		(*chan->ops->बंद)(chan->fd, chan->data);

	chan->खोलोed = 0;
	chan->fd = -1;
पूर्ण

व्योम बंद_chan(काष्ठा line *line)
अणु
	काष्ठा chan *chan;

	/* Close in reverse order as खोलो in हाल more than one of them
	 * refers to the same device and they save and restore that device's
	 * state.  Then, the first one खोलोed will have the original state,
	 * so it must be the last बंदd.
	 */
	list_क्रम_each_entry_reverse(chan, &line->chan_list, list) अणु
		बंद_one_chan(chan, 0);
	पूर्ण
पूर्ण

व्योम deactivate_chan(काष्ठा chan *chan, पूर्णांक irq)
अणु
	अगर (chan && chan->enabled)
		deactivate_fd(chan->fd, irq);
पूर्ण

पूर्णांक ग_लिखो_chan(काष्ठा chan *chan, स्थिर अक्षर *buf, पूर्णांक len,
	       पूर्णांक ग_लिखो_irq)
अणु
	पूर्णांक n, ret = 0;

	अगर (len == 0 || !chan || !chan->ops->ग_लिखो)
		वापस 0;

	n = chan->ops->ग_लिखो(chan->fd, buf, len, chan->data);
	अगर (chan->primary) अणु
		ret = n;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक console_ग_लिखो_chan(काष्ठा chan *chan, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक n, ret = 0;

	अगर (!chan || !chan->ops->console_ग_लिखो)
		वापस 0;

	n = chan->ops->console_ग_लिखो(chan->fd, buf, len);
	अगर (chan->primary)
		ret = n;
	वापस ret;
पूर्ण

पूर्णांक console_खोलो_chan(काष्ठा line *line, काष्ठा console *co)
अणु
	पूर्णांक err;

	err = खोलो_chan(&line->chan_list);
	अगर (err)
		वापस err;

	prपूर्णांकk(KERN_INFO "Console initialized on /dev/%s%d\n", co->name,
	       co->index);
	वापस 0;
पूर्ण

पूर्णांक chan_winकरोw_size(काष्ठा line *line, अचिन्हित लघु *rows_out,
		      अचिन्हित लघु *cols_out)
अणु
	काष्ठा chan *chan;

	chan = line->chan_in;
	अगर (chan && chan->primary) अणु
		अगर (chan->ops->winकरोw_size == शून्य)
			वापस 0;
		वापस chan->ops->winकरोw_size(chan->fd, chan->data,
					      rows_out, cols_out);
	पूर्ण
	chan = line->chan_out;
	अगर (chan && chan->primary) अणु
		अगर (chan->ops->winकरोw_size == शून्य)
			वापस 0;
		वापस chan->ops->winकरोw_size(chan->fd, chan->data,
					      rows_out, cols_out);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम मुक्त_one_chan(काष्ठा chan *chan)
अणु
	list_del(&chan->list);

	बंद_one_chan(chan, 0);

	अगर (chan->ops->मुक्त != शून्य)
		(*chan->ops->मुक्त)(chan->data);

	अगर (chan->primary && chan->output)
		ignore_sigio_fd(chan->fd);
	kमुक्त(chan);
पूर्ण

अटल व्योम मुक्त_chan(काष्ठा list_head *chans)
अणु
	काष्ठा list_head *ele, *next;
	काष्ठा chan *chan;

	list_क्रम_each_safe(ele, next, chans) अणु
		chan = list_entry(ele, काष्ठा chan, list);
		मुक्त_one_chan(chan);
	पूर्ण
पूर्ण

अटल पूर्णांक one_chan_config_string(काष्ठा chan *chan, अक्षर *str, पूर्णांक size,
				  अक्षर **error_out)
अणु
	पूर्णांक n = 0;

	अगर (chan == शून्य) अणु
		CONFIG_CHUNK(str, size, n, "none", 1);
		वापस n;
	पूर्ण

	CONFIG_CHUNK(str, size, n, chan->ops->type, 0);

	अगर (chan->dev == शून्य) अणु
		CONFIG_CHUNK(str, size, n, "", 1);
		वापस n;
	पूर्ण

	CONFIG_CHUNK(str, size, n, ":", 0);
	CONFIG_CHUNK(str, size, n, chan->dev, 0);

	वापस n;
पूर्ण

अटल पूर्णांक chan_pair_config_string(काष्ठा chan *in, काष्ठा chan *out,
				   अक्षर *str, पूर्णांक size, अक्षर **error_out)
अणु
	पूर्णांक n;

	n = one_chan_config_string(in, str, size, error_out);
	str += n;
	size -= n;

	अगर (in == out) अणु
		CONFIG_CHUNK(str, size, n, "", 1);
		वापस n;
	पूर्ण

	CONFIG_CHUNK(str, size, n, ",", 1);
	n = one_chan_config_string(out, str, size, error_out);
	str += n;
	size -= n;
	CONFIG_CHUNK(str, size, n, "", 1);

	वापस n;
पूर्ण

पूर्णांक chan_config_string(काष्ठा line *line, अक्षर *str, पूर्णांक size,
		       अक्षर **error_out)
अणु
	काष्ठा chan *in = line->chan_in, *out = line->chan_out;

	अगर (in && !in->primary)
		in = शून्य;
	अगर (out && !out->primary)
		out = शून्य;

	वापस chan_pair_config_string(in, out, str, size, error_out);
पूर्ण

काष्ठा chan_type अणु
	अक्षर *key;
	स्थिर काष्ठा chan_ops *ops;
पूर्ण;

अटल स्थिर काष्ठा chan_type chan_table[] = अणु
	अणु "fd", &fd_ops पूर्ण,

#अगर_घोषित CONFIG_शून्य_CHAN
	अणु "null", &null_ops पूर्ण,
#अन्यथा
	अणु "null", &not_configged_ops पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_PORT_CHAN
	अणु "port", &port_ops पूर्ण,
#अन्यथा
	अणु "port", &not_configged_ops पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_PTY_CHAN
	अणु "pty", &pty_ops पूर्ण,
	अणु "pts", &pts_ops पूर्ण,
#अन्यथा
	अणु "pty", &not_configged_ops पूर्ण,
	अणु "pts", &not_configged_ops पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TTY_CHAN
	अणु "tty", &tty_ops पूर्ण,
#अन्यथा
	अणु "tty", &not_configged_ops पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_XTERM_CHAN
	अणु "xterm", &xterm_ops पूर्ण,
#अन्यथा
	अणु "xterm", &not_configged_ops पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा chan *parse_chan(काष्ठा line *line, अक्षर *str, पूर्णांक device,
			       स्थिर काष्ठा chan_opts *opts, अक्षर **error_out)
अणु
	स्थिर काष्ठा chan_type *entry;
	स्थिर काष्ठा chan_ops *ops;
	काष्ठा chan *chan;
	व्योम *data;
	पूर्णांक i;

	ops = शून्य;
	data = शून्य;
	क्रम(i = 0; i < ARRAY_SIZE(chan_table); i++) अणु
		entry = &chan_table[i];
		अगर (!म_भेदन(str, entry->key, म_माप(entry->key))) अणु
			ops = entry->ops;
			str += म_माप(entry->key);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ops == शून्य) अणु
		*error_out = "No match for configured backends";
		वापस शून्य;
	पूर्ण

	data = (*ops->init)(str, device, opts);
	अगर (data == शून्य) अणु
		*error_out = "Configuration failed";
		वापस शून्य;
	पूर्ण

	chan = kदो_स्मृति(माप(*chan), GFP_ATOMIC);
	अगर (chan == शून्य) अणु
		*error_out = "Memory allocation failed";
		वापस शून्य;
	पूर्ण
	*chan = ((काष्ठा chan) अणु .list	 	= LIST_HEAD_INIT(chan->list),
				 .मुक्त_list 	=
				 	LIST_HEAD_INIT(chan->मुक्त_list),
				 .line		= line,
				 .primary	= 1,
				 .input		= 0,
				 .output 	= 0,
				 .खोलोed  	= 0,
				 .enabled  	= 0,
				 .fd 		= -1,
				 .ops 		= ops,
				 .data 		= data पूर्ण);
	वापस chan;
पूर्ण

पूर्णांक parse_chan_pair(अक्षर *str, काष्ठा line *line, पूर्णांक device,
		    स्थिर काष्ठा chan_opts *opts, अक्षर **error_out)
अणु
	काष्ठा list_head *chans = &line->chan_list;
	काष्ठा chan *new;
	अक्षर *in, *out;

	अगर (!list_empty(chans)) अणु
		line->chan_in = line->chan_out = शून्य;
		मुक्त_chan(chans);
		INIT_LIST_HEAD(chans);
	पूर्ण

	अगर (!str)
		वापस 0;

	out = म_अक्षर(str, ',');
	अगर (out != शून्य) अणु
		in = str;
		*out = '\0';
		out++;
		new = parse_chan(line, in, device, opts, error_out);
		अगर (new == शून्य)
			वापस -1;

		new->input = 1;
		list_add(&new->list, chans);
		line->chan_in = new;

		new = parse_chan(line, out, device, opts, error_out);
		अगर (new == शून्य)
			वापस -1;

		list_add(&new->list, chans);
		new->output = 1;
		line->chan_out = new;
	पूर्ण
	अन्यथा अणु
		new = parse_chan(line, str, device, opts, error_out);
		अगर (new == शून्य)
			वापस -1;

		list_add(&new->list, chans);
		new->input = 1;
		new->output = 1;
		line->chan_in = line->chan_out = new;
	पूर्ण
	वापस 0;
पूर्ण

व्योम chan_पूर्णांकerrupt(काष्ठा line *line, पूर्णांक irq)
अणु
	काष्ठा tty_port *port = &line->port;
	काष्ठा chan *chan = line->chan_in;
	पूर्णांक err;
	अक्षर c;

	अगर (!chan || !chan->ops->पढ़ो)
		जाओ out;

	करो अणु
		अगर (!tty_buffer_request_room(port, 1)) अणु
			schedule_delayed_work(&line->task, 1);
			जाओ out;
		पूर्ण
		err = chan->ops->पढ़ो(chan->fd, &c, chan->data);
		अगर (err > 0)
			tty_insert_flip_अक्षर(port, c, TTY_NORMAL);
	पूर्ण जबतक (err > 0);

	अगर (err == -EIO) अणु
		अगर (chan->primary) अणु
			tty_port_tty_hangup(&line->port, false);
			अगर (line->chan_out != chan)
				बंद_one_chan(line->chan_out, 1);
		पूर्ण
		बंद_one_chan(chan, 1);
		अगर (chan->primary)
			वापस;
	पूर्ण
 out:
	tty_flip_buffer_push(port);
पूर्ण
