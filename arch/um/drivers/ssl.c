<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* 
 * Copyright (C) 2000, 2002 Jeff Dike (jdike@karaya.com)
 */

#समावेश <linux/fs.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/major.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <यंत्र/termbits.h>
#समावेश <यंत्र/irq.h>
#समावेश "chan.h"
#समावेश <init.h>
#समावेश <irq_user.h>
#समावेश "mconsole_kern.h"

अटल स्थिर पूर्णांक ssl_version = 1;

#घोषणा NR_PORTS 64

अटल व्योम ssl_announce(अक्षर *dev_name, पूर्णांक dev)
अणु
	prपूर्णांकk(KERN_INFO "Serial line %d assigned device '%s'\n", dev,
	       dev_name);
पूर्ण

/* Almost स्थिर, except that xterm_title may be changed in an initcall */
अटल काष्ठा chan_opts opts = अणु
	.announce 	= ssl_announce,
	.xterm_title	= "Serial Line #%d",
	.raw		= 1,
पूर्ण;

अटल पूर्णांक ssl_config(अक्षर *str, अक्षर **error_out);
अटल पूर्णांक ssl_get_config(अक्षर *dev, अक्षर *str, पूर्णांक size, अक्षर **error_out);
अटल पूर्णांक ssl_हटाओ(पूर्णांक n, अक्षर **error_out);


/* Const, except क्रम .mc.list */
अटल काष्ठा line_driver driver = अणु
	.name 			= "UML serial line",
	.device_name 		= "ttyS",
	.major 			= TTY_MAJOR,
	.minor_start 		= 64,
	.type 		 	= TTY_DRIVER_TYPE_SERIAL,
	.subtype 	 	= 0,
	.पढ़ो_irq 		= SSL_IRQ,
	.पढ़ो_irq_name 		= "ssl",
	.ग_लिखो_irq 		= SSL_WRITE_IRQ,
	.ग_लिखो_irq_name 	= "ssl-write",
	.mc  = अणु
		.list		= LIST_HEAD_INIT(driver.mc.list),
		.name  		= "ssl",
		.config 	= ssl_config,
		.get_config 	= ssl_get_config,
		.id		= line_id,
		.हटाओ 	= ssl_हटाओ,
	पूर्ण,
पूर्ण;

/* The array is initialized by line_init, at initcall समय.  The
 * elements are locked inभागidually as needed.
 */
अटल अक्षर *conf[NR_PORTS];
अटल अक्षर *def_conf = CONFIG_SSL_CHAN;
अटल काष्ठा line serial_lines[NR_PORTS];

अटल पूर्णांक ssl_config(अक्षर *str, अक्षर **error_out)
अणु
	वापस line_config(serial_lines, ARRAY_SIZE(serial_lines), str, &opts,
			   error_out);
पूर्ण

अटल पूर्णांक ssl_get_config(अक्षर *dev, अक्षर *str, पूर्णांक size, अक्षर **error_out)
अणु
	वापस line_get_config(dev, serial_lines, ARRAY_SIZE(serial_lines), str,
			       size, error_out);
पूर्ण

अटल पूर्णांक ssl_हटाओ(पूर्णांक n, अक्षर **error_out)
अणु
	वापस line_हटाओ(serial_lines, ARRAY_SIZE(serial_lines), n,
			   error_out);
पूर्ण

अटल पूर्णांक ssl_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	वापस line_install(driver, tty, &serial_lines[tty->index]);
पूर्ण

अटल स्थिर काष्ठा tty_operations ssl_ops = अणु
	.खोलो 	 		= line_खोलो,
	.बंद 	 		= line_बंद,
	.ग_लिखो 	 		= line_ग_लिखो,
	.ग_लिखो_room		= line_ग_लिखो_room,
	.अक्षरs_in_buffer 	= line_अक्षरs_in_buffer,
	.flush_buffer 		= line_flush_buffer,
	.flush_अक्षरs 		= line_flush_अक्षरs,
	.set_termios 		= line_set_termios,
	.throttle 		= line_throttle,
	.unthrottle 		= line_unthrottle,
	.install		= ssl_install,
	.hangup			= line_hangup,
पूर्ण;

/* Changed by ssl_init and referenced by ssl_निकास, which are both serialized
 * by being an initcall and निकासcall, respectively.
 */
अटल पूर्णांक ssl_init_करोne = 0;

अटल व्योम ssl_console_ग_लिखो(काष्ठा console *c, स्थिर अक्षर *string,
			      अचिन्हित len)
अणु
	काष्ठा line *line = &serial_lines[c->index];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&line->lock, flags);
	console_ग_लिखो_chan(line->chan_out, string, len);
	spin_unlock_irqrestore(&line->lock, flags);
पूर्ण

अटल काष्ठा tty_driver *ssl_console_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = c->index;
	वापस driver.driver;
पूर्ण

अटल पूर्णांक ssl_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा line *line = &serial_lines[co->index];

	वापस console_खोलो_chan(line, co);
पूर्ण

/* No locking क्रम रेजिस्टर_console call - relies on single-thपढ़ोed initcalls */
अटल काष्ठा console ssl_cons = अणु
	.name		= "ttyS",
	.ग_लिखो		= ssl_console_ग_लिखो,
	.device		= ssl_console_device,
	.setup		= ssl_console_setup,
	.flags		= CON_PRINTBUFFER|CON_ANYTIME,
	.index		= -1,
पूर्ण;

अटल पूर्णांक ssl_init(व्योम)
अणु
	अक्षर *new_title;
	पूर्णांक err;
	पूर्णांक i;

	prपूर्णांकk(KERN_INFO "Initializing software serial port version %d\n",
	       ssl_version);

	err = रेजिस्टर_lines(&driver, &ssl_ops, serial_lines,
				    ARRAY_SIZE(serial_lines));
	अगर (err)
		वापस err;

	new_title = add_xterm_umid(opts.xterm_title);
	अगर (new_title != शून्य)
		opts.xterm_title = new_title;

	क्रम (i = 0; i < NR_PORTS; i++) अणु
		अक्षर *error;
		अक्षर *s = conf[i];
		अगर (!s)
			s = def_conf;
		अगर (setup_one_line(serial_lines, i, s, &opts, &error))
			prपूर्णांकk(KERN_ERR "setup_one_line failed for "
			       "device %d : %s\n", i, error);
	पूर्ण

	ssl_init_करोne = 1;
	रेजिस्टर_console(&ssl_cons);
	वापस 0;
पूर्ण
late_initcall(ssl_init);

अटल व्योम ssl_निकास(व्योम)
अणु
	अगर (!ssl_init_करोne)
		वापस;
	बंद_lines(serial_lines, ARRAY_SIZE(serial_lines));
पूर्ण
__uml_निकासcall(ssl_निकास);

अटल पूर्णांक ssl_chan_setup(अक्षर *str)
अणु
	line_setup(conf, NR_PORTS, &def_conf, str, "serial line");
	वापस 1;
पूर्ण

__setup("ssl", ssl_chan_setup);
__channel_help(ssl_chan_setup, "ssl");

अटल पूर्णांक ssl_non_raw_setup(अक्षर *str)
अणु
	opts.raw = 0;
	वापस 1;
पूर्ण
__setup("ssl-non-raw", ssl_non_raw_setup);
__channel_help(ssl_non_raw_setup, "set serial lines to non-raw mode");
