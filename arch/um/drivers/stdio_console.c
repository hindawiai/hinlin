<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* 
 * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)
 */

#समावेश <linux/posix_types.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/types.h>
#समावेश <linux/major.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/console.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/hardirq.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/irq.h>
#समावेश "stdio_console.h"
#समावेश "chan.h"
#समावेश <irq_user.h>
#समावेश "mconsole_kern.h"
#समावेश <init.h>

#घोषणा MAX_TTYS (16)

अटल व्योम stdio_announce(अक्षर *dev_name, पूर्णांक dev)
अणु
	prपूर्णांकk(KERN_INFO "Virtual console %d assigned device '%s'\n", dev,
	       dev_name);
पूर्ण

/* Almost स्थिर, except that xterm_title may be changed in an initcall */
अटल काष्ठा chan_opts opts = अणु
	.announce 	= stdio_announce,
	.xterm_title	= "Virtual Console #%d",
	.raw		= 1,
पूर्ण;

अटल पूर्णांक con_config(अक्षर *str, अक्षर **error_out);
अटल पूर्णांक con_get_config(अक्षर *dev, अक्षर *str, पूर्णांक size, अक्षर **error_out);
अटल पूर्णांक con_हटाओ(पूर्णांक n, अक्षर **con_हटाओ);


/* Const, except क्रम .mc.list */
अटल काष्ठा line_driver driver = अणु
	.name 			= "UML console",
	.device_name 		= "tty",
	.major 			= TTY_MAJOR,
	.minor_start 		= 0,
	.type 		 	= TTY_DRIVER_TYPE_CONSOLE,
	.subtype 	 	= SYSTEM_TYPE_CONSOLE,
	.पढ़ो_irq 		= CONSOLE_IRQ,
	.पढ़ो_irq_name 		= "console",
	.ग_लिखो_irq 		= CONSOLE_WRITE_IRQ,
	.ग_लिखो_irq_name 	= "console-write",
	.mc  = अणु
		.list		= LIST_HEAD_INIT(driver.mc.list),
		.name  		= "con",
		.config 	= con_config,
		.get_config 	= con_get_config,
		.id		= line_id,
		.हटाओ 	= con_हटाओ,
	पूर्ण,
पूर्ण;

/* The array is initialized by line_init, at initcall समय.  The
 * elements are locked inभागidually as needed.
 */
अटल अक्षर *vt_conf[MAX_TTYS];
अटल अक्षर *def_conf;
अटल काष्ठा line vts[MAX_TTYS];

अटल पूर्णांक con_config(अक्षर *str, अक्षर **error_out)
अणु
	वापस line_config(vts, ARRAY_SIZE(vts), str, &opts, error_out);
पूर्ण

अटल पूर्णांक con_get_config(अक्षर *dev, अक्षर *str, पूर्णांक size, अक्षर **error_out)
अणु
	वापस line_get_config(dev, vts, ARRAY_SIZE(vts), str, size, error_out);
पूर्ण

अटल पूर्णांक con_हटाओ(पूर्णांक n, अक्षर **error_out)
अणु
	वापस line_हटाओ(vts, ARRAY_SIZE(vts), n, error_out);
पूर्ण

/* Set in an initcall, checked in an निकासcall */
अटल पूर्णांक con_init_करोne = 0;

अटल पूर्णांक con_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	वापस line_install(driver, tty, &vts[tty->index]);
पूर्ण

अटल स्थिर काष्ठा tty_operations console_ops = अणु
	.खोलो 	 		= line_खोलो,
	.install		= con_install,
	.बंद 	 		= line_बंद,
	.ग_लिखो 	 		= line_ग_लिखो,
	.ग_लिखो_room		= line_ग_लिखो_room,
	.अक्षरs_in_buffer 	= line_अक्षरs_in_buffer,
	.flush_buffer 		= line_flush_buffer,
	.flush_अक्षरs 		= line_flush_अक्षरs,
	.set_termios 		= line_set_termios,
	.throttle 		= line_throttle,
	.unthrottle 		= line_unthrottle,
	.hangup			= line_hangup,
पूर्ण;

अटल व्योम uml_console_ग_लिखो(काष्ठा console *console, स्थिर अक्षर *string,
			      अचिन्हित len)
अणु
	काष्ठा line *line = &vts[console->index];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&line->lock, flags);
	console_ग_लिखो_chan(line->chan_out, string, len);
	spin_unlock_irqrestore(&line->lock, flags);
पूर्ण

अटल काष्ठा tty_driver *uml_console_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = c->index;
	वापस driver.driver;
पूर्ण

अटल पूर्णांक uml_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा line *line = &vts[co->index];

	वापस console_खोलो_chan(line, co);
पूर्ण

/* No locking क्रम रेजिस्टर_console call - relies on single-thपढ़ोed initcalls */
अटल काष्ठा console stdiocons = अणु
	.name		= "tty",
	.ग_लिखो		= uml_console_ग_लिखो,
	.device		= uml_console_device,
	.setup		= uml_console_setup,
	.flags		= CON_PRINTBUFFER|CON_ANYTIME,
	.index		= -1,
पूर्ण;

अटल पूर्णांक stdio_init(व्योम)
अणु
	अक्षर *new_title;
	पूर्णांक err;
	पूर्णांक i;

	err = रेजिस्टर_lines(&driver, &console_ops, vts,
					ARRAY_SIZE(vts));
	अगर (err)
		वापस err;

	prपूर्णांकk(KERN_INFO "Initialized stdio console driver\n");

	new_title = add_xterm_umid(opts.xterm_title);
	अगर(new_title != शून्य)
		opts.xterm_title = new_title;

	क्रम (i = 0; i < MAX_TTYS; i++) अणु
		अक्षर *error;
		अक्षर *s = vt_conf[i];
		अगर (!s)
			s = def_conf;
		अगर (!s)
			s = i ? CONFIG_CON_CHAN : CONFIG_CON_ZERO_CHAN;
		अगर (setup_one_line(vts, i, s, &opts, &error))
			prपूर्णांकk(KERN_ERR "setup_one_line failed for "
			       "device %d : %s\n", i, error);
	पूर्ण

	con_init_करोne = 1;
	रेजिस्टर_console(&stdiocons);
	वापस 0;
पूर्ण
late_initcall(stdio_init);

अटल व्योम console_निकास(व्योम)
अणु
	अगर (!con_init_करोne)
		वापस;
	बंद_lines(vts, ARRAY_SIZE(vts));
पूर्ण
__uml_निकासcall(console_निकास);

अटल पूर्णांक console_chan_setup(अक्षर *str)
अणु
	अगर (!म_भेदन(str, "sole=", 5))	/* console= option specअगरies tty */
		वापस 0;

	line_setup(vt_conf, MAX_TTYS, &def_conf, str, "console");
	वापस 1;
पूर्ण
__setup("con", console_chan_setup);
__channel_help(console_chan_setup, "con");
