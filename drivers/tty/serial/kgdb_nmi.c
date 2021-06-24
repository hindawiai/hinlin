<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KGDB NMI serial console
 *
 * Copyright 2010 Google, Inc.
 *		  Arve Hjथचnnevथआg <arve@android.com>
 *		  Colin Cross <ccross@android.com>
 * Copyright 2012 Linaro Ltd.
 *		  Anton Vorontsov <anton.vorontsov@linaro.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/atomic.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/tick.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdb.h>

अटल पूर्णांक kgdb_nmi_knock = 1;
module_param_named(knock, kgdb_nmi_knock, पूर्णांक, 0600);
MODULE_PARM_DESC(knock, "if set to 1 (default), the special '$3#33' command " \
			"must be used to enter the debugger; when set to 0, " \
			"hitting return key is enough to enter the debugger; " \
			"when set to -1, the debugger is entered immediately " \
			"upon NMI");

अटल अक्षर *kgdb_nmi_magic = "$3#33";
module_param_named(magic, kgdb_nmi_magic, अक्षरp, 0600);
MODULE_PARM_DESC(magic, "magic sequence to enter NMI debugger (default $3#33)");

अटल atomic_t kgdb_nmi_num_पढ़ोers = ATOMIC_INIT(0);

अटल पूर्णांक kgdb_nmi_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	arch_kgdb_ops.enable_nmi(1);

	/* The NMI console uses the dbg_io_ops to issue console messages. To
	 * aव्योम duplicate messages during kdb sessions we must inक्रमm kdb's
	 * I/O utilities that messages sent to the console will स्वतःmatically
	 * be displayed on the dbg_io.
	 */
	dbg_io_ops->cons = co;

	वापस 0;
पूर्ण

अटल व्योम kgdb_nmi_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, uपूर्णांक c)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < c; i++)
		dbg_io_ops->ग_लिखो_अक्षर(s[i]);
पूर्ण

अटल काष्ठा tty_driver *kgdb_nmi_tty_driver;

अटल काष्ठा tty_driver *kgdb_nmi_console_device(काष्ठा console *co, पूर्णांक *idx)
अणु
	*idx = co->index;
	वापस kgdb_nmi_tty_driver;
पूर्ण

अटल काष्ठा console kgdb_nmi_console = अणु
	.name	= "ttyNMI",
	.setup  = kgdb_nmi_console_setup,
	.ग_लिखो	= kgdb_nmi_console_ग_लिखो,
	.device	= kgdb_nmi_console_device,
	.flags	= CON_PRINTBUFFER | CON_ANYTIME,
	.index	= -1,
पूर्ण;

/*
 * This is usually the maximum rate on debug ports. We make fअगरo large enough
 * to make copy-pasting to the terminal usable.
 */
#घोषणा KGDB_NMI_BAUD		115200
#घोषणा KGDB_NMI_FIFO_SIZE	roundup_घात_of_two(KGDB_NMI_BAUD / 8 / HZ)

काष्ठा kgdb_nmi_tty_priv अणु
	काष्ठा tty_port port;
	काष्ठा समयr_list समयr;
	STRUCT_KFIFO(अक्षर, KGDB_NMI_FIFO_SIZE) fअगरo;
पूर्ण;

अटल काष्ठा tty_port *kgdb_nmi_port;

अटल व्योम kgdb_tty_recv(पूर्णांक ch)
अणु
	काष्ठा kgdb_nmi_tty_priv *priv;
	अक्षर c = ch;

	अगर (!kgdb_nmi_port || ch < 0)
		वापस;
	/*
	 * Can't use port->tty->driver_data as tty might be not there. Timer
	 * will check क्रम tty and will get the ref, but here we करोn't have to
	 * करो that, and actually, we can't: we're in NMI context, no locks are
	 * possible.
	 */
	priv = container_of(kgdb_nmi_port, काष्ठा kgdb_nmi_tty_priv, port);
	kfअगरo_in(&priv->fअगरo, &c, 1);
पूर्ण

अटल पूर्णांक kgdb_nmi_poll_one_knock(व्योम)
अणु
	अटल पूर्णांक n;
	पूर्णांक c = -1;
	स्थिर अक्षर *magic = kgdb_nmi_magic;
	माप_प्रकार m = म_माप(magic);
	bool prपूर्णांकch = false;

	c = dbg_io_ops->पढ़ो_अक्षर();
	अगर (c == NO_POLL_CHAR)
		वापस c;

	अगर (!kgdb_nmi_knock && (c == '\r' || c == '\n')) अणु
		वापस 1;
	पूर्ण अन्यथा अगर (c == magic[n]) अणु
		n = (n + 1) % m;
		अगर (!n)
			वापस 1;
		prपूर्णांकch = true;
	पूर्ण अन्यथा अणु
		n = 0;
	पूर्ण

	अगर (atomic_पढ़ो(&kgdb_nmi_num_पढ़ोers)) अणु
		kgdb_tty_recv(c);
		वापस 0;
	पूर्ण

	अगर (prपूर्णांकch) अणु
		kdb_म_लिखो("%c", c);
		वापस 0;
	पूर्ण

	kdb_म_लिखो("\r%s %s to enter the debugger> %*s",
		   kgdb_nmi_knock ? "Type" : "Hit",
		   kgdb_nmi_knock ? magic  : "<return>", (पूर्णांक)m, "");
	जबतक (m--)
		kdb_म_लिखो("\b");
	वापस 0;
पूर्ण

/**
 * kgdb_nmi_poll_knock - Check अगर it is समय to enter the debugger
 *
 * "Serial ports are often noisy, especially when muxed over another port (we
 * often use serial over the headset connector). Noise on the async command
 * line just causes अक्षरacters that are ignored, on a command line that blocked
 * execution noise would be catastrophic." -- Colin Cross
 *
 * So, this function implements KGDB/KDB knocking on the serial line: we won't
 * enter the debugger until we receive a known magic phrase (which is actually
 * "$3#33", known as "escape to KDB" command. There is also a relaxed variant
 * of knocking, i.e. just pressing the वापस key is enough to enter the
 * debugger. And अगर knocking is disabled, the function always वापसs 1.
 */
bool kgdb_nmi_poll_knock(व्योम)
अणु
	अगर (kgdb_nmi_knock < 0)
		वापस true;

	जबतक (1) अणु
		पूर्णांक ret;

		ret = kgdb_nmi_poll_one_knock();
		अगर (ret == NO_POLL_CHAR)
			वापस false;
		अन्यथा अगर (ret == 1)
			अवरोध;
	पूर्ण
	वापस true;
पूर्ण

/*
 * The tasklet is cheap, it करोes not cause wakeups when reschedules itself,
 * instead it रुकोs क्रम the next tick.
 */
अटल व्योम kgdb_nmi_tty_receiver(काष्ठा समयr_list *t)
अणु
	काष्ठा kgdb_nmi_tty_priv *priv = from_समयr(priv, t, समयr);
	अक्षर ch;

	priv->समयr.expires = jअगरfies + (HZ/100);
	add_समयr(&priv->समयr);

	अगर (likely(!atomic_पढ़ो(&kgdb_nmi_num_पढ़ोers) ||
		   !kfअगरo_len(&priv->fअगरo)))
		वापस;

	जबतक (kfअगरo_out(&priv->fअगरo, &ch, 1))
		tty_insert_flip_अक्षर(&priv->port, ch, TTY_NORMAL);
	tty_flip_buffer_push(&priv->port);
पूर्ण

अटल पूर्णांक kgdb_nmi_tty_activate(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा kgdb_nmi_tty_priv *priv =
	    container_of(port, काष्ठा kgdb_nmi_tty_priv, port);

	kgdb_nmi_port = port;
	priv->समयr.expires = jअगरfies + (HZ/100);
	add_समयr(&priv->समयr);

	वापस 0;
पूर्ण

अटल व्योम kgdb_nmi_tty_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा kgdb_nmi_tty_priv *priv =
	    container_of(port, काष्ठा kgdb_nmi_tty_priv, port);

	del_समयr(&priv->समयr);
	kgdb_nmi_port = शून्य;
पूर्ण

अटल स्थिर काष्ठा tty_port_operations kgdb_nmi_tty_port_ops = अणु
	.activate	= kgdb_nmi_tty_activate,
	.shutकरोwn	= kgdb_nmi_tty_shutकरोwn,
पूर्ण;

अटल पूर्णांक kgdb_nmi_tty_install(काष्ठा tty_driver *drv, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा kgdb_nmi_tty_priv *priv;
	पूर्णांक ret;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	INIT_KFIFO(priv->fअगरo);
	समयr_setup(&priv->समयr, kgdb_nmi_tty_receiver, 0);
	tty_port_init(&priv->port);
	priv->port.ops = &kgdb_nmi_tty_port_ops;
	tty->driver_data = priv;

	ret = tty_port_install(&priv->port, drv, tty);
	अगर (ret) अणु
		pr_err("%s: can't install tty port: %d\n", __func__, ret);
		जाओ err;
	पूर्ण
	वापस 0;
err:
	tty_port_destroy(&priv->port);
	kमुक्त(priv);
	वापस ret;
पूर्ण

अटल व्योम kgdb_nmi_tty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा kgdb_nmi_tty_priv *priv = tty->driver_data;

	tty->driver_data = शून्य;
	tty_port_destroy(&priv->port);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक kgdb_nmi_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा kgdb_nmi_tty_priv *priv = tty->driver_data;
	अचिन्हित पूर्णांक mode = file->f_flags & O_ACCMODE;
	पूर्णांक ret;

	ret = tty_port_खोलो(&priv->port, tty, file);
	अगर (!ret && (mode == O_RDONLY || mode == O_RDWR))
		atomic_inc(&kgdb_nmi_num_पढ़ोers);

	वापस ret;
पूर्ण

अटल व्योम kgdb_nmi_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा kgdb_nmi_tty_priv *priv = tty->driver_data;
	अचिन्हित पूर्णांक mode = file->f_flags & O_ACCMODE;

	अगर (mode == O_RDONLY || mode == O_RDWR)
		atomic_dec(&kgdb_nmi_num_पढ़ोers);

	tty_port_बंद(&priv->port, tty, file);
पूर्ण

अटल व्योम kgdb_nmi_tty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा kgdb_nmi_tty_priv *priv = tty->driver_data;

	tty_port_hangup(&priv->port);
पूर्ण

अटल पूर्णांक kgdb_nmi_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	/* Actually, we can handle any amount as we use polled ग_लिखोs. */
	वापस 2048;
पूर्ण

अटल पूर्णांक kgdb_nmi_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर unअक्षर *buf, पूर्णांक c)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < c; i++)
		dbg_io_ops->ग_लिखो_अक्षर(buf[i]);
	वापस c;
पूर्ण

अटल स्थिर काष्ठा tty_operations kgdb_nmi_tty_ops = अणु
	.खोलो		= kgdb_nmi_tty_खोलो,
	.बंद		= kgdb_nmi_tty_बंद,
	.install	= kgdb_nmi_tty_install,
	.cleanup	= kgdb_nmi_tty_cleanup,
	.hangup		= kgdb_nmi_tty_hangup,
	.ग_लिखो_room	= kgdb_nmi_tty_ग_लिखो_room,
	.ग_लिखो		= kgdb_nmi_tty_ग_लिखो,
पूर्ण;

पूर्णांक kgdb_रेजिस्टर_nmi_console(व्योम)
अणु
	पूर्णांक ret;

	अगर (!arch_kgdb_ops.enable_nmi)
		वापस 0;

	kgdb_nmi_tty_driver = alloc_tty_driver(1);
	अगर (!kgdb_nmi_tty_driver) अणु
		pr_err("%s: cannot allocate tty\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	kgdb_nmi_tty_driver->driver_name	= "ttyNMI";
	kgdb_nmi_tty_driver->name		= "ttyNMI";
	kgdb_nmi_tty_driver->num		= 1;
	kgdb_nmi_tty_driver->type		= TTY_DRIVER_TYPE_SERIAL;
	kgdb_nmi_tty_driver->subtype		= SERIAL_TYPE_NORMAL;
	kgdb_nmi_tty_driver->flags		= TTY_DRIVER_REAL_RAW;
	kgdb_nmi_tty_driver->init_termios	= tty_std_termios;
	tty_termios_encode_baud_rate(&kgdb_nmi_tty_driver->init_termios,
				     KGDB_NMI_BAUD, KGDB_NMI_BAUD);
	tty_set_operations(kgdb_nmi_tty_driver, &kgdb_nmi_tty_ops);

	ret = tty_रेजिस्टर_driver(kgdb_nmi_tty_driver);
	अगर (ret) अणु
		pr_err("%s: can't register tty driver: %d\n", __func__, ret);
		जाओ err_drv_reg;
	पूर्ण

	रेजिस्टर_console(&kgdb_nmi_console);

	वापस 0;
err_drv_reg:
	put_tty_driver(kgdb_nmi_tty_driver);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kgdb_रेजिस्टर_nmi_console);

पूर्णांक kgdb_unरेजिस्टर_nmi_console(व्योम)
अणु
	पूर्णांक ret;

	अगर (!arch_kgdb_ops.enable_nmi)
		वापस 0;
	arch_kgdb_ops.enable_nmi(0);

	ret = unरेजिस्टर_console(&kgdb_nmi_console);
	अगर (ret)
		वापस ret;

	tty_unरेजिस्टर_driver(kgdb_nmi_tty_driver);
	put_tty_driver(kgdb_nmi_tty_driver);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kgdb_unरेजिस्टर_nmi_console);
