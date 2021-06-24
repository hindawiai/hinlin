<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Axis Communications AB
 *
 * Based on ttyprपूर्णांकk.c:
 *  Copyright (C) 2010 Samo Pogacnik
 */

#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/tty.h>

अटल स्थिर काष्ठा tty_port_operations ttynull_port_ops;
अटल काष्ठा tty_driver *ttynull_driver;
अटल काष्ठा tty_port ttynull_port;

अटल पूर्णांक ttynull_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	वापस tty_port_खोलो(&ttynull_port, tty, filp);
पूर्ण

अटल व्योम ttynull_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	tty_port_बंद(&ttynull_port, tty, filp);
पूर्ण

अटल व्योम ttynull_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	tty_port_hangup(&ttynull_port);
पूर्ण

अटल पूर्णांक ttynull_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
			 पूर्णांक count)
अणु
	वापस count;
पूर्ण

अटल पूर्णांक ttynull_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 65536;
पूर्ण

अटल स्थिर काष्ठा tty_operations ttynull_ops = अणु
	.खोलो = ttynull_खोलो,
	.बंद = ttynull_बंद,
	.hangup = ttynull_hangup,
	.ग_लिखो = ttynull_ग_लिखो,
	.ग_लिखो_room = ttynull_ग_लिखो_room,
पूर्ण;

अटल काष्ठा tty_driver *ttynull_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = 0;
	वापस ttynull_driver;
पूर्ण

अटल काष्ठा console ttynull_console = अणु
	.name = "ttynull",
	.device = ttynull_device,
पूर्ण;

अटल पूर्णांक __init ttynull_init(व्योम)
अणु
	काष्ठा tty_driver *driver;
	पूर्णांक ret;

	driver = tty_alloc_driver(1,
		TTY_DRIVER_RESET_TERMIOS |
		TTY_DRIVER_REAL_RAW |
		TTY_DRIVER_UNNUMBERED_NODE);
	अगर (IS_ERR(driver))
		वापस PTR_ERR(driver);

	tty_port_init(&ttynull_port);
	ttynull_port.ops = &ttynull_port_ops;

	driver->driver_name = "ttynull";
	driver->name = "ttynull";
	driver->type = TTY_DRIVER_TYPE_CONSOLE;
	driver->init_termios = tty_std_termios;
	driver->init_termios.c_oflag = OPOST | OCRNL | ONOCR | ONLRET;
	tty_set_operations(driver, &ttynull_ops);
	tty_port_link_device(&ttynull_port, driver, 0);

	ret = tty_रेजिस्टर_driver(driver);
	अगर (ret < 0) अणु
		put_tty_driver(driver);
		tty_port_destroy(&ttynull_port);
		वापस ret;
	पूर्ण

	ttynull_driver = driver;
	रेजिस्टर_console(&ttynull_console);

	वापस 0;
पूर्ण

अटल व्योम __निकास ttynull_निकास(व्योम)
अणु
	unरेजिस्टर_console(&ttynull_console);
	tty_unरेजिस्टर_driver(ttynull_driver);
	put_tty_driver(ttynull_driver);
	tty_port_destroy(&ttynull_port);
पूर्ण

module_init(ttynull_init);
module_निकास(ttynull_निकास);

MODULE_LICENSE("GPL v2");
