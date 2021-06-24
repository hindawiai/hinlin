<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/srmcons.c
 *
 * Callback based driver क्रम SRM Console console device.
 * (TTY driver and console driver)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>

#समावेश <यंत्र/console.h>
#समावेश <linux/uaccess.h>


अटल DEFINE_SPINLOCK(srmcons_callback_lock);
अटल पूर्णांक srm_is_रेजिस्टरed_console = 0;

/* 
 * The TTY driver
 */
#घोषणा MAX_SRM_CONSOLE_DEVICES 1	/* only support 1 console device */

काष्ठा srmcons_निजी अणु
	काष्ठा tty_port port;
	काष्ठा समयr_list समयr;
पूर्ण srmcons_singleton;

प्रकार जोड़ _srmcons_result अणु
	काष्ठा अणु
		अचिन्हित दीर्घ c :61;
		अचिन्हित दीर्घ status :3;
	पूर्ण bits;
	दीर्घ as_दीर्घ;
पूर्ण srmcons_result;

/* called with callback_lock held */
अटल पूर्णांक
srmcons_करो_receive_अक्षरs(काष्ठा tty_port *port)
अणु
	srmcons_result result;
	पूर्णांक count = 0, loops = 0;

	करो अणु
		result.as_दीर्घ = callback_अ_लो(0);
		अगर (result.bits.status < 2) अणु
			tty_insert_flip_अक्षर(port, (अक्षर)result.bits.c, 0);
			count++;
		पूर्ण
	पूर्ण जबतक((result.bits.status & 1) && (++loops < 10));

	अगर (count)
		tty_schedule_flip(port);

	वापस count;
पूर्ण

अटल व्योम
srmcons_receive_अक्षरs(काष्ठा समयr_list *t)
अणु
	काष्ठा srmcons_निजी *srmconsp = from_समयr(srmconsp, t, समयr);
	काष्ठा tty_port *port = &srmconsp->port;
	अचिन्हित दीर्घ flags;
	पूर्णांक incr = 10;

	local_irq_save(flags);
	अगर (spin_trylock(&srmcons_callback_lock)) अणु
		अगर (!srmcons_करो_receive_अक्षरs(port))
			incr = 100;
		spin_unlock(&srmcons_callback_lock);
	पूर्ण 

	spin_lock(&port->lock);
	अगर (port->tty)
		mod_समयr(&srmconsp->समयr, jअगरfies + incr);
	spin_unlock(&port->lock);

	local_irq_restore(flags);
पूर्ण

/* called with callback_lock held */
अटल पूर्णांक
srmcons_करो_ग_लिखो(काष्ठा tty_port *port, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	अटल अक्षर str_cr[1] = "\r";
	दीर्घ c, reमुख्यing = count;
	srmcons_result result;
	अक्षर *cur;
	पूर्णांक need_cr;

	क्रम (cur = (अक्षर *)buf; reमुख्यing > 0; ) अणु
		need_cr = 0;
		/* 
		 * Break it up पूर्णांकo reasonable size chunks to allow a chance
		 * क्रम input to get in
		 */
		क्रम (c = 0; c < min_t(दीर्घ, 128L, reमुख्यing) && !need_cr; c++)
			अगर (cur[c] == '\n')
				need_cr = 1;
		
		जबतक (c > 0) अणु
			result.as_दीर्घ = callback_माला_दो(0, cur, c);
			c -= result.bits.c;
			reमुख्यing -= result.bits.c;
			cur += result.bits.c;

			/*
			 * Check क्रम pending input अगरf a tty port was provided
			 */
			अगर (port)
				srmcons_करो_receive_अक्षरs(port);
		पूर्ण

		जबतक (need_cr) अणु
			result.as_दीर्घ = callback_माला_दो(0, str_cr, 1);
			अगर (result.bits.c > 0)
				need_cr = 0;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक
srmcons_ग_लिखो(काष्ठा tty_काष्ठा *tty,
	      स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&srmcons_callback_lock, flags);
	srmcons_करो_ग_लिखो(tty->port, (स्थिर अक्षर *) buf, count);
	spin_unlock_irqrestore(&srmcons_callback_lock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक
srmcons_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 512;
पूर्ण

अटल पूर्णांक
srmcons_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
srmcons_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा srmcons_निजी *srmconsp = &srmcons_singleton;
	काष्ठा tty_port *port = &srmconsp->port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	अगर (!port->tty) अणु
		tty->driver_data = srmconsp;
		tty->port = port;
		port->tty = tty; /* XXX proper refcounting */
		mod_समयr(&srmconsp->समयr, jअगरfies + 10);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम
srmcons_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा srmcons_निजी *srmconsp = tty->driver_data;
	काष्ठा tty_port *port = &srmconsp->port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	अगर (tty->count == 1) अणु
		port->tty = शून्य;
		del_समयr(&srmconsp->समयr);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण


अटल काष्ठा tty_driver *srmcons_driver;

अटल स्थिर काष्ठा tty_operations srmcons_ops = अणु
	.खोलो		= srmcons_खोलो,
	.बंद		= srmcons_बंद,
	.ग_लिखो		= srmcons_ग_लिखो,
	.ग_लिखो_room	= srmcons_ग_लिखो_room,
	.अक्षरs_in_buffer= srmcons_अक्षरs_in_buffer,
पूर्ण;

अटल पूर्णांक __init
srmcons_init(व्योम)
अणु
	समयr_setup(&srmcons_singleton.समयr, srmcons_receive_अक्षरs, 0);
	अगर (srm_is_रेजिस्टरed_console) अणु
		काष्ठा tty_driver *driver;
		पूर्णांक err;

		driver = alloc_tty_driver(MAX_SRM_CONSOLE_DEVICES);
		अगर (!driver)
			वापस -ENOMEM;

		tty_port_init(&srmcons_singleton.port);

		driver->driver_name = "srm";
		driver->name = "srm";
		driver->major = 0; 	/* dynamic */
		driver->minor_start = 0;
		driver->type = TTY_DRIVER_TYPE_SYSTEM;
		driver->subtype = SYSTEM_TYPE_SYSCONS;
		driver->init_termios = tty_std_termios;
		tty_set_operations(driver, &srmcons_ops);
		tty_port_link_device(&srmcons_singleton.port, driver, 0);
		err = tty_रेजिस्टर_driver(driver);
		अगर (err) अणु
			put_tty_driver(driver);
			tty_port_destroy(&srmcons_singleton.port);
			वापस err;
		पूर्ण
		srmcons_driver = driver;
	पूर्ण

	वापस -ENODEV;
पूर्ण
device_initcall(srmcons_init);


/*
 * The console driver
 */
अटल व्योम
srm_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित count)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&srmcons_callback_lock, flags);
	srmcons_करो_ग_लिखो(शून्य, s, count);
	spin_unlock_irqrestore(&srmcons_callback_lock, flags);
पूर्ण

अटल काष्ठा tty_driver *
srm_console_device(काष्ठा console *co, पूर्णांक *index)
अणु
	*index = co->index;
	वापस srmcons_driver;
पूर्ण

अटल पूर्णांक
srm_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा console srmcons = अणु
	.name		= "srm",
	.ग_लिखो		= srm_console_ग_लिखो,
	.device		= srm_console_device,
	.setup		= srm_console_setup,
	.flags		= CON_PRINTBUFFER | CON_BOOT,
	.index		= -1,
पूर्ण;

व्योम __init
रेजिस्टर_srm_console(व्योम)
अणु
	अगर (!srm_is_रेजिस्टरed_console) अणु
		callback_खोलो_console();
		रेजिस्टर_console(&srmcons);
		srm_is_रेजिस्टरed_console = 1;
	पूर्ण
पूर्ण

व्योम __init
unरेजिस्टर_srm_console(व्योम)
अणु
	अगर (srm_is_रेजिस्टरed_console) अणु
		callback_बंद_console();
		unरेजिस्टर_console(&srmcons);
		srm_is_रेजिस्टरed_console = 0;
	पूर्ण
पूर्ण
