<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 
 *    PDC Console support - ie use firmware to dump text via boot console
 *
 *    Copyright (C) 1999-2003 Matthew Wilcox <willy at parisc-linux.org>
 *    Copyright (C) 2000 Martin K Petersen <mkp at mkp.net>
 *    Copyright (C) 2000 John Marvin <jsm at parisc-linux.org>
 *    Copyright (C) 2000-2003 Paul Bame <bame at parisc-linux.org>
 *    Copyright (C) 2000 Philipp Rumpf <prumpf with tux.org>
 *    Copyright (C) 2000 Michael Ang <mang with subcarrier.org>
 *    Copyright (C) 2000 Grant Grundler <grundler with parisc-linux.org>
 *    Copyright (C) 2001-2002 Ryan Bradetich <rbrad at parisc-linux.org>
 *    Copyright (C) 2001 Helge Deller <deller at parisc-linux.org>
 *    Copyright (C) 2001 Thomas Bogenकरोerfer <tsbogend at parisc-linux.org>
 *    Copyright (C) 2002 Ranकरोlph Chung <tausq with parisc-linux.org>
 *    Copyright (C) 2010 Guy Martin <gmsoft at tuxicoman.be>
 */

/*
 *  The PDC console is a simple console, which can be used क्रम debugging 
 *  boot related problems on HP PA-RISC machines. It is also useful when no
 *  other console works.
 *
 *  This code uses the ROM (=PDC) based functions to पढ़ो and ग_लिखो अक्षरacters
 *  from and to PDC's boot path.
 */

/* Define EARLY_BOOTUP_DEBUG to debug kernel related boot problems. 
 * On production kernels EARLY_BOOTUP_DEBUG should be undefined. */
#घोषणा EARLY_BOOTUP_DEBUG


#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/major.h>
#समावेश <linux/tty.h>
#समावेश <यंत्र/page.h>		/* क्रम PAGE0 */
#समावेश <यंत्र/pdc.h>		/* क्रम iodc_call() proto and मित्रs */

अटल DEFINE_SPINLOCK(pdc_console_lock);
अटल काष्ठा console pdc_cons;

अटल व्योम pdc_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित count)
अणु
	पूर्णांक i = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_console_lock, flags);
	करो अणु
		i += pdc_iodc_prपूर्णांक(s + i, count - i);
	पूर्ण जबतक (i < count);
	spin_unlock_irqrestore(&pdc_console_lock, flags);
पूर्ण

पूर्णांक pdc_console_poll_key(काष्ठा console *co)
अणु
	पूर्णांक c;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_console_lock, flags);
	c = pdc_iodc_अ_लो();
	spin_unlock_irqrestore(&pdc_console_lock, flags);

	वापस c;
पूर्ण

अटल पूर्णांक pdc_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	वापस 0;
पूर्ण

#अगर defined(CONFIG_PDC_CONSOLE)
#समावेश <linux/vt_kern.h>
#समावेश <linux/tty_flip.h>

#घोषणा PDC_CONS_POLL_DELAY (30 * HZ / 1000)

अटल व्योम pdc_console_poll(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(pdc_console_समयr, pdc_console_poll);
अटल काष्ठा tty_port tty_port;

अटल पूर्णांक pdc_console_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	tty_port_tty_set(&tty_port, tty);
	mod_समयr(&pdc_console_समयr, jअगरfies + PDC_CONS_POLL_DELAY);

	वापस 0;
पूर्ण

अटल व्योम pdc_console_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	अगर (tty->count == 1) अणु
		del_समयr_sync(&pdc_console_समयr);
		tty_port_tty_set(&tty_port, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक pdc_console_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	pdc_console_ग_लिखो(शून्य, buf, count);
	वापस count;
पूर्ण

अटल पूर्णांक pdc_console_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 32768; /* no limit, no buffer used */
पूर्ण

अटल पूर्णांक pdc_console_tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 0; /* no buffer */
पूर्ण

अटल स्थिर काष्ठा tty_operations pdc_console_tty_ops = अणु
	.खोलो = pdc_console_tty_खोलो,
	.बंद = pdc_console_tty_बंद,
	.ग_लिखो = pdc_console_tty_ग_लिखो,
	.ग_लिखो_room = pdc_console_tty_ग_लिखो_room,
	.अक्षरs_in_buffer = pdc_console_tty_अक्षरs_in_buffer,
पूर्ण;

अटल व्योम pdc_console_poll(काष्ठा समयr_list *unused)
अणु
	पूर्णांक data, count = 0;

	जबतक (1) अणु
		data = pdc_console_poll_key(शून्य);
		अगर (data == -1)
			अवरोध;
		tty_insert_flip_अक्षर(&tty_port, data & 0xFF, TTY_NORMAL);
		count ++;
	पूर्ण

	अगर (count)
		tty_flip_buffer_push(&tty_port);

	अगर (pdc_cons.flags & CON_ENABLED)
		mod_समयr(&pdc_console_समयr, jअगरfies + PDC_CONS_POLL_DELAY);
पूर्ण

अटल काष्ठा tty_driver *pdc_console_tty_driver;

अटल पूर्णांक __init pdc_console_tty_driver_init(व्योम)
अणु
	पूर्णांक err;

	/* Check अगर the console driver is still रेजिस्टरed.
	 * It is unरेजिस्टरed अगर the pdc console was not selected as the
	 * primary console. */

	काष्ठा console *पंचांगp;

	console_lock();
	क्रम_each_console(पंचांगp)
		अगर (पंचांगp == &pdc_cons)
			अवरोध;
	console_unlock();

	अगर (!पंचांगp) अणु
		prपूर्णांकk(KERN_INFO "PDC console driver not registered anymore, not creating %s\n", pdc_cons.name);
		वापस -ENODEV;
	पूर्ण

	prपूर्णांकk(KERN_INFO "The PDC console driver is still registered, removing CON_BOOT flag\n");
	pdc_cons.flags &= ~CON_BOOT;

	pdc_console_tty_driver = alloc_tty_driver(1);

	अगर (!pdc_console_tty_driver)
		वापस -ENOMEM;

	tty_port_init(&tty_port);

	pdc_console_tty_driver->driver_name = "pdc_cons";
	pdc_console_tty_driver->name = "ttyB";
	pdc_console_tty_driver->major = MUX_MAJOR;
	pdc_console_tty_driver->minor_start = 0;
	pdc_console_tty_driver->type = TTY_DRIVER_TYPE_SYSTEM;
	pdc_console_tty_driver->init_termios = tty_std_termios;
	pdc_console_tty_driver->flags = TTY_DRIVER_REAL_RAW |
		TTY_DRIVER_RESET_TERMIOS;
	tty_set_operations(pdc_console_tty_driver, &pdc_console_tty_ops);
	tty_port_link_device(&tty_port, pdc_console_tty_driver, 0);

	err = tty_रेजिस्टर_driver(pdc_console_tty_driver);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Unable to register the PDC console TTY driver\n");
		tty_port_destroy(&tty_port);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(pdc_console_tty_driver_init);

अटल काष्ठा tty_driver * pdc_console_device (काष्ठा console *c, पूर्णांक *index)
अणु
	*index = c->index;
	वापस pdc_console_tty_driver;
पूर्ण
#अन्यथा
#घोषणा pdc_console_device शून्य
#पूर्ण_अगर

अटल काष्ठा console pdc_cons = अणु
	.name =		"ttyB",
	.ग_लिखो =	pdc_console_ग_लिखो,
	.device =	pdc_console_device,
	.setup =	pdc_console_setup,
	.flags =	CON_BOOT | CON_PRINTBUFFER,
	.index =	-1,
पूर्ण;

अटल पूर्णांक pdc_console_initialized;

अटल व्योम pdc_console_init_क्रमce(व्योम)
अणु
	अगर (pdc_console_initialized)
		वापस;
	++pdc_console_initialized;
	
	/* If the console is duplex then copy the COUT parameters to CIN. */
	अगर (PAGE0->mem_cons.cl_class == CL_DUPLEX)
		स_नकल(&PAGE0->mem_kbd, &PAGE0->mem_cons, माप(PAGE0->mem_cons));

	/* रेजिस्टर the pdc console */
	रेजिस्टर_console(&pdc_cons);
पूर्ण

व्योम __init pdc_console_init(व्योम)
अणु
#अगर defined(EARLY_BOOTUP_DEBUG) || defined(CONFIG_PDC_CONSOLE)
	pdc_console_init_क्रमce();
#पूर्ण_अगर
#अगर_घोषित EARLY_BOOTUP_DEBUG
	prपूर्णांकk(KERN_INFO "Initialized PDC Console for debugging.\n");
#पूर्ण_अगर
पूर्ण


/*
 * Used क्रम emergencies. Currently only used अगर an HPMC occurs. If an
 * HPMC occurs, it is possible that the current console may not be
 * properly initialised after the PDC IO reset. This routine unरेजिस्टरs
 * all of the current consoles, reinitializes the pdc console and
 * रेजिस्टरs it.
 */

व्योम pdc_console_restart(व्योम)
अणु
	काष्ठा console *console;

	अगर (pdc_console_initialized)
		वापस;

	/* If we've already seen the output, don't bother to prपूर्णांक it again */
	अगर (console_drivers != शून्य)
		pdc_cons.flags &= ~CON_PRINTBUFFER;

	जबतक ((console = console_drivers) != शून्य)
		unरेजिस्टर_console(console_drivers);

	/* क्रमce रेजिस्टरing the pdc console */
	pdc_console_init_क्रमce();
पूर्ण
