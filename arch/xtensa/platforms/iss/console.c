<शैली गुरु>
/*
 * arch/xtensa/platक्रमms/iss/console.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001-2005 Tensilica Inc.
 *   Authors	Christian Zankel, Joe Taylor
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/major.h>
#समावेश <linux/param.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/serial.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>

#समावेश <platक्रमm/simcall.h>

#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#घोषणा SERIAL_MAX_NUM_LINES 1
#घोषणा SERIAL_TIMER_VALUE (HZ / 10)

अटल व्योम rs_poll(काष्ठा समयr_list *);

अटल काष्ठा tty_driver *serial_driver;
अटल काष्ठा tty_port serial_port;
अटल DEFINE_TIMER(serial_समयr, rs_poll);
अटल DEFINE_SPINLOCK(समयr_lock);

अटल पूर्णांक rs_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	spin_lock_bh(&समयr_lock);
	अगर (tty->count == 1)
		mod_समयr(&serial_समयr, jअगरfies + SERIAL_TIMER_VALUE);
	spin_unlock_bh(&समयr_lock);

	वापस 0;
पूर्ण

अटल व्योम rs_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	spin_lock_bh(&समयr_lock);
	अगर (tty->count == 1)
		del_समयr_sync(&serial_समयr);
	spin_unlock_bh(&समयr_lock);
पूर्ण


अटल पूर्णांक rs_ग_लिखो(काष्ठा tty_काष्ठा * tty,
		    स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	/* see drivers/अक्षर/serialX.c to reference original version */

	simc_ग_लिखो(1, buf, count);
	वापस count;
पूर्ण

अटल व्योम rs_poll(काष्ठा समयr_list *unused)
अणु
	काष्ठा tty_port *port = &serial_port;
	पूर्णांक i = 0;
	पूर्णांक rd = 1;
	अचिन्हित अक्षर c;

	spin_lock(&समयr_lock);

	जबतक (simc_poll(0)) अणु
		rd = simc_पढ़ो(0, &c, 1);
		अगर (rd <= 0)
			अवरोध;
		tty_insert_flip_अक्षर(port, c, TTY_NORMAL);
		i++;
	पूर्ण

	अगर (i)
		tty_flip_buffer_push(port);
	अगर (rd)
		mod_समयr(&serial_समयr, jअगरfies + SERIAL_TIMER_VALUE);
	spin_unlock(&समयr_lock);
पूर्ण


अटल पूर्णांक rs_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	वापस rs_ग_लिखो(tty, &ch, 1);
पूर्ण

अटल व्योम rs_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
पूर्ण

अटल पूर्णांक rs_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	/* Let's say iss can always accept 2K अक्षरacters.. */
	वापस 2 * 1024;
पूर्ण

अटल पूर्णांक rs_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	/* the iss करोesn't buffer अक्षरacters */
	वापस 0;
पूर्ण

अटल व्योम rs_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	/* Stub, once again.. */
पूर्ण

अटल व्योम rs_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
	/* Stub, once again.. */
पूर्ण

अटल पूर्णांक rs_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "serinfo:1.0 driver:0.1\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tty_operations serial_ops = अणु
	.खोलो = rs_खोलो,
	.बंद = rs_बंद,
	.ग_लिखो = rs_ग_लिखो,
	.put_अक्षर = rs_put_अक्षर,
	.flush_अक्षरs = rs_flush_अक्षरs,
	.ग_लिखो_room = rs_ग_लिखो_room,
	.अक्षरs_in_buffer = rs_अक्षरs_in_buffer,
	.hangup = rs_hangup,
	.रुको_until_sent = rs_रुको_until_sent,
	.proc_show = rs_proc_show,
पूर्ण;

अटल पूर्णांक __init rs_init(व्योम)
अणु
	tty_port_init(&serial_port);

	serial_driver = alloc_tty_driver(SERIAL_MAX_NUM_LINES);

	/* Initialize the tty_driver काष्ठाure */

	serial_driver->driver_name = "iss_serial";
	serial_driver->name = "ttyS";
	serial_driver->major = TTY_MAJOR;
	serial_driver->minor_start = 64;
	serial_driver->type = TTY_DRIVER_TYPE_SERIAL;
	serial_driver->subtype = SERIAL_TYPE_NORMAL;
	serial_driver->init_termios = tty_std_termios;
	serial_driver->init_termios.c_cflag =
		B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	serial_driver->flags = TTY_DRIVER_REAL_RAW;

	tty_set_operations(serial_driver, &serial_ops);
	tty_port_link_device(&serial_port, serial_driver, 0);

	अगर (tty_रेजिस्टर_driver(serial_driver))
		panic("Couldn't register serial driver\n");
	वापस 0;
पूर्ण


अटल __निकास व्योम rs_निकास(व्योम)
अणु
	tty_unरेजिस्टर_driver(serial_driver);
	put_tty_driver(serial_driver);
	tty_port_destroy(&serial_port);
पूर्ण


/* We use `late_initcall' instead of just `__initcall' as a workaround क्रम
 * the fact that (1) simcons_tty_init can't be called beक्रमe tty_init,
 * (2) tty_init is called via `module_init', (3) अगर अटलally linked,
 * module_init == device_init, and (4) there's no ordering of init lists.
 * We can करो this easily because simcons is always अटलally linked, but
 * other tty drivers that depend on tty_init and which must use
 * `module_init' to declare their init routines are likely to be broken.
 */

late_initcall(rs_init);


#अगर_घोषित CONFIG_SERIAL_CONSOLE

अटल व्योम iss_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित count)
अणु
	पूर्णांक len = म_माप(s);

	अगर (s != 0 && *s != 0)
		simc_ग_लिखो(1, s, count < len ? count : len);
पूर्ण

अटल काष्ठा tty_driver* iss_console_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = c->index;
	वापस serial_driver;
पूर्ण


अटल काष्ठा console sercons = अणु
	.name = "ttyS",
	.ग_लिखो = iss_console_ग_लिखो,
	.device = iss_console_device,
	.flags = CON_PRINTBUFFER,
	.index = -1
पूर्ण;

अटल पूर्णांक __init iss_console_init(व्योम)
अणु
	रेजिस्टर_console(&sercons);
	वापस 0;
पूर्ण

console_initcall(iss_console_init);

#पूर्ण_अगर /* CONFIG_SERIAL_CONSOLE */

