<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Universal/legacy driver क्रम 8250/16550-type serial ports
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  Copyright (C) 2001 Russell King.
 *
 *  Supports: ISA-compatible 8250/16550 ports
 *	      PNP 8250/16550 ports
 *	      early_serial_setup() ports
 *	      userspace-configurable "phantom" ports
 *	      "serial8250" platक्रमm devices
 *	      serial8250_रेजिस्टर_8250_port() ports
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/tty.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/nmi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पन.स>
#अगर_घोषित CONFIG_SPARC
#समावेश <linux/sunserialcore.h>
#पूर्ण_अगर

#समावेश <यंत्र/irq.h>

#समावेश "8250.h"

/*
 * Configuration:
 *   share_irqs - whether we pass IRQF_SHARED to request_irq().  This option
 *                is unsafe when used on edge-triggered पूर्णांकerrupts.
 */
अटल अचिन्हित पूर्णांक share_irqs = SERIAL8250_SHARE_IRQS;

अटल अचिन्हित पूर्णांक nr_uarts = CONFIG_SERIAL_8250_RUNTIME_UARTS;

अटल काष्ठा uart_driver serial8250_reg;

अटल अचिन्हित पूर्णांक skip_txen_test; /* क्रमce skip of txen test at init समय */

#घोषणा PASS_LIMIT	512

#समावेश <यंत्र/serial.h>
/*
 * SERIAL_PORT_DFNS tells us about built-in ports that have no
 * standard क्रमागतeration mechanism.   Platक्रमms that can find all
 * serial ports via mechanisms like ACPI or PCI need not supply it.
 */
#अगर_अघोषित SERIAL_PORT_DFNS
#घोषणा SERIAL_PORT_DFNS
#पूर्ण_अगर

अटल स्थिर काष्ठा old_serial_port old_serial_port[] = अणु
	SERIAL_PORT_DFNS /* defined in यंत्र/serial.h */
पूर्ण;

#घोषणा UART_NR	CONFIG_SERIAL_8250_NR_UARTS

#अगर_घोषित CONFIG_SERIAL_8250_RSA

#घोषणा PORT_RSA_MAX 4
अटल अचिन्हित दीर्घ probe_rsa[PORT_RSA_MAX];
अटल अचिन्हित पूर्णांक probe_rsa_count;
#पूर्ण_अगर /* CONFIG_SERIAL_8250_RSA  */

काष्ठा irq_info अणु
	काष्ठा			hlist_node node;
	पूर्णांक			irq;
	spinlock_t		lock;	/* Protects list not the hash */
	काष्ठा list_head	*head;
पूर्ण;

#घोषणा NR_IRQ_HASH		32	/* Can be adjusted later */
अटल काष्ठा hlist_head irq_lists[NR_IRQ_HASH];
अटल DEFINE_MUTEX(hash_mutex);	/* Used to walk the hash */

/*
 * This is the serial driver's पूर्णांकerrupt routine.
 *
 * Arjan thinks the old way was overly complex, so it got simplअगरied.
 * Alan disagrees, saying that need the complनिकासy to handle the weird
 * nature of ISA shared पूर्णांकerrupts.  (This is a special exception.)
 *
 * In order to handle ISA shared पूर्णांकerrupts properly, we need to check
 * that all ports have been serviced, and thereक्रमe the ISA पूर्णांकerrupt
 * line has been de-निश्चितed.
 *
 * This means we need to loop through all ports. checking that they
 * करोn't have an पूर्णांकerrupt pending.
 */
अटल irqवापस_t serial8250_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा irq_info *i = dev_id;
	काष्ठा list_head *l, *end = शून्य;
	पूर्णांक pass_counter = 0, handled = 0;

	pr_debug("%s(%d): start\n", __func__, irq);

	spin_lock(&i->lock);

	l = i->head;
	करो अणु
		काष्ठा uart_8250_port *up;
		काष्ठा uart_port *port;

		up = list_entry(l, काष्ठा uart_8250_port, list);
		port = &up->port;

		अगर (port->handle_irq(port)) अणु
			handled = 1;
			end = शून्य;
		पूर्ण अन्यथा अगर (end == शून्य)
			end = l;

		l = l->next;

		अगर (l == i->head && pass_counter++ > PASS_LIMIT)
			अवरोध;
	पूर्ण जबतक (l != end);

	spin_unlock(&i->lock);

	pr_debug("%s(%d): end\n", __func__, irq);

	वापस IRQ_RETVAL(handled);
पूर्ण

/*
 * To support ISA shared पूर्णांकerrupts, we need to have one पूर्णांकerrupt
 * handler that ensures that the IRQ line has been deनिश्चितed
 * beक्रमe वापसing.  Failing to करो this will result in the IRQ
 * line being stuck active, and, since ISA irqs are edge triggered,
 * no more IRQs will be seen.
 */
अटल व्योम serial_करो_unlink(काष्ठा irq_info *i, काष्ठा uart_8250_port *up)
अणु
	spin_lock_irq(&i->lock);

	अगर (!list_empty(i->head)) अणु
		अगर (i->head == &up->list)
			i->head = i->head->next;
		list_del(&up->list);
	पूर्ण अन्यथा अणु
		BUG_ON(i->head != &up->list);
		i->head = शून्य;
	पूर्ण
	spin_unlock_irq(&i->lock);
	/* List empty so throw away the hash node */
	अगर (i->head == शून्य) अणु
		hlist_del(&i->node);
		kमुक्त(i);
	पूर्ण
पूर्ण

अटल पूर्णांक serial_link_irq_chain(काष्ठा uart_8250_port *up)
अणु
	काष्ठा hlist_head *h;
	काष्ठा hlist_node *n;
	काष्ठा irq_info *i;
	पूर्णांक ret;

	mutex_lock(&hash_mutex);

	h = &irq_lists[up->port.irq % NR_IRQ_HASH];

	hlist_क्रम_each(n, h) अणु
		i = hlist_entry(n, काष्ठा irq_info, node);
		अगर (i->irq == up->port.irq)
			अवरोध;
	पूर्ण

	अगर (n == शून्य) अणु
		i = kzalloc(माप(काष्ठा irq_info), GFP_KERNEL);
		अगर (i == शून्य) अणु
			mutex_unlock(&hash_mutex);
			वापस -ENOMEM;
		पूर्ण
		spin_lock_init(&i->lock);
		i->irq = up->port.irq;
		hlist_add_head(&i->node, h);
	पूर्ण
	mutex_unlock(&hash_mutex);

	spin_lock_irq(&i->lock);

	अगर (i->head) अणु
		list_add(&up->list, i->head);
		spin_unlock_irq(&i->lock);

		ret = 0;
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&up->list);
		i->head = &up->list;
		spin_unlock_irq(&i->lock);
		ret = request_irq(up->port.irq, serial8250_पूर्णांकerrupt,
				  up->port.irqflags, up->port.name, i);
		अगर (ret < 0)
			serial_करो_unlink(i, up);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम serial_unlink_irq_chain(काष्ठा uart_8250_port *up)
अणु
	/*
	 * yes, some broken gcc emit "warning: 'i' may be used uninitialized"
	 * but no, we are not going to take a patch that assigns शून्य below.
	 */
	काष्ठा irq_info *i;
	काष्ठा hlist_node *n;
	काष्ठा hlist_head *h;

	mutex_lock(&hash_mutex);

	h = &irq_lists[up->port.irq % NR_IRQ_HASH];

	hlist_क्रम_each(n, h) अणु
		i = hlist_entry(n, काष्ठा irq_info, node);
		अगर (i->irq == up->port.irq)
			अवरोध;
	पूर्ण

	BUG_ON(n == शून्य);
	BUG_ON(i->head == शून्य);

	अगर (list_empty(i->head))
		मुक्त_irq(up->port.irq, i);

	serial_करो_unlink(i, up);
	mutex_unlock(&hash_mutex);
पूर्ण

/*
 * This function is used to handle ports that करो not have an
 * पूर्णांकerrupt.  This करोesn't work very well for 16450's, but gives
 * barely passable results क्रम a 16550A.  (Although at the expense
 * of much CPU overhead).
 */
अटल व्योम serial8250_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा uart_8250_port *up = from_समयr(up, t, समयr);

	up->port.handle_irq(&up->port);
	mod_समयr(&up->समयr, jअगरfies + uart_poll_समयout(&up->port));
पूर्ण

अटल व्योम serial8250_backup_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा uart_8250_port *up = from_समयr(up, t, समयr);
	अचिन्हित पूर्णांक iir, ier = 0, lsr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Must disable पूर्णांकerrupts or अन्यथा we risk racing with the पूर्णांकerrupt
	 * based handler.
	 */
	अगर (up->port.irq) अणु
		ier = serial_in(up, UART_IER);
		serial_out(up, UART_IER, 0);
	पूर्ण

	iir = serial_in(up, UART_IIR);

	/*
	 * This should be a safe test क्रम anyone who करोesn't trust the
	 * IIR bits on their UART, but it's specअगरically deचिन्हित क्रम
	 * the "Diva" UART used on the management processor on many HP
	 * ia64 and parisc boxes.
	 */
	lsr = serial_in(up, UART_LSR);
	up->lsr_saved_flags |= lsr & LSR_SAVE_FLAGS;
	अगर ((iir & UART_IIR_NO_INT) && (up->ier & UART_IER_THRI) &&
	    (!uart_circ_empty(&up->port.state->xmit) || up->port.x_अक्षर) &&
	    (lsr & UART_LSR_THRE)) अणु
		iir &= ~(UART_IIR_ID | UART_IIR_NO_INT);
		iir |= UART_IIR_THRI;
	पूर्ण

	अगर (!(iir & UART_IIR_NO_INT))
		serial8250_tx_अक्षरs(up);

	अगर (up->port.irq)
		serial_out(up, UART_IER, ier);

	spin_unlock_irqrestore(&up->port.lock, flags);

	/* Standard समयr पूर्णांकerval plus 0.2s to keep the port running */
	mod_समयr(&up->समयr,
		jअगरfies + uart_poll_समयout(&up->port) + HZ / 5);
पूर्ण

अटल पूर्णांक univ8250_setup_irq(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_port *port = &up->port;
	पूर्णांक retval = 0;

	/*
	 * The above check will only give an accurate result the first समय
	 * the port is खोलोed so this value needs to be preserved.
	 */
	अगर (up->bugs & UART_BUG_THRE) अणु
		pr_debug("%s - using backup timer\n", port->name);

		up->समयr.function = serial8250_backup_समयout;
		mod_समयr(&up->समयr, jअगरfies +
			  uart_poll_समयout(port) + HZ / 5);
	पूर्ण

	/*
	 * If the "interrupt" क्रम this port करोesn't correspond with any
	 * hardware पूर्णांकerrupt, we use a समयr-based प्रणाली.  The original
	 * driver used to करो this with IRQ0.
	 */
	अगर (!port->irq) अणु
		mod_समयr(&up->समयr, jअगरfies + uart_poll_समयout(port));
	पूर्ण अन्यथा
		retval = serial_link_irq_chain(up);

	वापस retval;
पूर्ण

अटल व्योम univ8250_release_irq(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_port *port = &up->port;

	del_समयr_sync(&up->समयr);
	up->समयr.function = serial8250_समयout;
	अगर (port->irq)
		serial_unlink_irq_chain(up);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_RSA
अटल पूर्णांक serial8250_request_rsa_resource(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित दीर्घ start = UART_RSA_BASE << up->port.regshअगरt;
	अचिन्हित पूर्णांक size = 8 << up->port.regshअगरt;
	काष्ठा uart_port *port = &up->port;
	पूर्णांक ret = -EINVAL;

	चयन (port->iotype) अणु
	हाल UPIO_HUB6:
	हाल UPIO_PORT:
		start += port->iobase;
		अगर (request_region(start, size, "serial-rsa"))
			ret = 0;
		अन्यथा
			ret = -EBUSY;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम serial8250_release_rsa_resource(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित दीर्घ offset = UART_RSA_BASE << up->port.regshअगरt;
	अचिन्हित पूर्णांक size = 8 << up->port.regshअगरt;
	काष्ठा uart_port *port = &up->port;

	चयन (port->iotype) अणु
	हाल UPIO_HUB6:
	हाल UPIO_PORT:
		release_region(port->iobase + offset, size);
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops *base_ops;
अटल काष्ठा uart_ops univ8250_port_ops;

अटल स्थिर काष्ठा uart_8250_ops univ8250_driver_ops = अणु
	.setup_irq	= univ8250_setup_irq,
	.release_irq	= univ8250_release_irq,
पूर्ण;

अटल काष्ठा uart_8250_port serial8250_ports[UART_NR];

/**
 * serial8250_get_port - retrieve काष्ठा uart_8250_port
 * @line: serial line number
 *
 * This function retrieves काष्ठा uart_8250_port क्रम the specअगरic line.
 * This काष्ठा *must* *not* be used to perक्रमm a 8250 or serial core operation
 * which is not accessible otherwise. Its only purpose is to make the काष्ठा
 * accessible to the runसमय-pm callbacks क्रम context suspend/restore.
 * The lock assumption made here is none because runसमय-pm suspend/resume
 * callbacks should not be invoked अगर there is any operation perक्रमmed on the
 * port.
 */
काष्ठा uart_8250_port *serial8250_get_port(पूर्णांक line)
अणु
	वापस &serial8250_ports[line];
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_get_port);

अटल व्योम (*serial8250_isa_config)(पूर्णांक port, काष्ठा uart_port *up,
	u32 *capabilities);

व्योम serial8250_set_isa_configurator(
	व्योम (*v)(पूर्णांक port, काष्ठा uart_port *up, u32 *capabilities))
अणु
	serial8250_isa_config = v;
पूर्ण
EXPORT_SYMBOL(serial8250_set_isa_configurator);

#अगर_घोषित CONFIG_SERIAL_8250_RSA

अटल व्योम univ8250_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	up->probe &= ~UART_PROBE_RSA;
	अगर (port->type == PORT_RSA) अणु
		अगर (serial8250_request_rsa_resource(up) == 0)
			up->probe |= UART_PROBE_RSA;
	पूर्ण अन्यथा अगर (flags & UART_CONFIG_TYPE) अणु
		पूर्णांक i;

		क्रम (i = 0; i < probe_rsa_count; i++) अणु
			अगर (probe_rsa[i] == up->port.iobase) अणु
				अगर (serial8250_request_rsa_resource(up) == 0)
					up->probe |= UART_PROBE_RSA;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	base_ops->config_port(port, flags);

	अगर (port->type != PORT_RSA && up->probe & UART_PROBE_RSA)
		serial8250_release_rsa_resource(up);
पूर्ण

अटल पूर्णांक univ8250_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	पूर्णांक ret;

	ret = base_ops->request_port(port);
	अगर (ret == 0 && port->type == PORT_RSA) अणु
		ret = serial8250_request_rsa_resource(up);
		अगर (ret < 0)
			base_ops->release_port(port);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम univ8250_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	अगर (port->type == PORT_RSA)
		serial8250_release_rsa_resource(up);
	base_ops->release_port(port);
पूर्ण

अटल व्योम univ8250_rsa_support(काष्ठा uart_ops *ops)
अणु
	ops->config_port  = univ8250_config_port;
	ops->request_port = univ8250_request_port;
	ops->release_port = univ8250_release_port;
पूर्ण

#अन्यथा
#घोषणा univ8250_rsa_support(x)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_SERIAL_8250_RSA */

अटल अंतरभूत व्योम serial8250_apply_quirks(काष्ठा uart_8250_port *up)
अणु
	up->port.quirks |= skip_txen_test ? UPQ_NO_TXEN_TEST : 0;
पूर्ण

अटल व्योम __init serial8250_isa_init_ports(व्योम)
अणु
	काष्ठा uart_8250_port *up;
	अटल पूर्णांक first = 1;
	पूर्णांक i, irqflag = 0;

	अगर (!first)
		वापस;
	first = 0;

	अगर (nr_uarts > UART_NR)
		nr_uarts = UART_NR;

	क्रम (i = 0; i < nr_uarts; i++) अणु
		काष्ठा uart_8250_port *up = &serial8250_ports[i];
		काष्ठा uart_port *port = &up->port;

		port->line = i;
		serial8250_init_port(up);
		अगर (!base_ops)
			base_ops = port->ops;
		port->ops = &univ8250_port_ops;

		समयr_setup(&up->समयr, serial8250_समयout, 0);

		up->ops = &univ8250_driver_ops;

		/*
		 * ALPHA_KLUDGE_MCR needs to be समाप्तed.
		 */
		up->mcr_mask = ~ALPHA_KLUDGE_MCR;
		up->mcr_क्रमce = ALPHA_KLUDGE_MCR;
		serial8250_set_शेषs(up);
	पूर्ण

	/* chain base port ops to support Remote Supervisor Adapter */
	univ8250_port_ops = *base_ops;
	univ8250_rsa_support(&univ8250_port_ops);

	अगर (share_irqs)
		irqflag = IRQF_SHARED;

	क्रम (i = 0, up = serial8250_ports;
	     i < ARRAY_SIZE(old_serial_port) && i < nr_uarts;
	     i++, up++) अणु
		काष्ठा uart_port *port = &up->port;

		port->iobase   = old_serial_port[i].port;
		port->irq      = irq_canonicalize(old_serial_port[i].irq);
		port->irqflags = 0;
		port->uartclk  = old_serial_port[i].baud_base * 16;
		port->flags    = old_serial_port[i].flags;
		port->hub6     = 0;
		port->membase  = old_serial_port[i].iomem_base;
		port->iotype   = old_serial_port[i].io_type;
		port->regshअगरt = old_serial_port[i].iomem_reg_shअगरt;

		port->irqflags |= irqflag;
		अगर (serial8250_isa_config != शून्य)
			serial8250_isa_config(i, &up->port, &up->capabilities);
	पूर्ण
पूर्ण

अटल व्योम __init
serial8250_रेजिस्टर_ports(काष्ठा uart_driver *drv, काष्ठा device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_uarts; i++) अणु
		काष्ठा uart_8250_port *up = &serial8250_ports[i];

		अगर (up->port.type == PORT_8250_CIR)
			जारी;

		अगर (up->port.dev)
			जारी;

		up->port.dev = dev;

		serial8250_apply_quirks(up);
		uart_add_one_port(drv, &up->port);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE

अटल व्योम univ8250_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				   अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_8250_port *up = &serial8250_ports[co->index];

	serial8250_console_ग_लिखो(up, s, count);
पूर्ण

अटल पूर्णांक univ8250_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक retval;

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index >= nr_uarts)
		co->index = 0;
	port = &serial8250_ports[co->index].port;
	/* link port to console */
	port->cons = co;

	retval = serial8250_console_setup(port, options, false);
	अगर (retval != 0)
		port->cons = शून्य;
	वापस retval;
पूर्ण

अटल पूर्णांक univ8250_console_निकास(काष्ठा console *co)
अणु
	काष्ठा uart_port *port;

	port = &serial8250_ports[co->index].port;
	वापस serial8250_console_निकास(port);
पूर्ण

/**
 *	univ8250_console_match - non-standard console matching
 *	@co:	  रेजिस्टरing console
 *	@name:	  name from console command line
 *	@idx:	  index from console command line
 *	@options: ptr to option string from console command line
 *
 *	Only attempts to match console command lines of the क्रमm:
 *	    console=uart[8250],io|mmio|mmio16|mmio32,<addr>[,<options>]
 *	    console=uart[8250],0x<addr>[,<options>]
 *	This क्रमm is used to रेजिस्टर an initial earlycon boot console and
 *	replace it with the serial8250_console at 8250 driver init.
 *
 *	Perक्रमms console setup क्रम a match (as required by पूर्णांकerface)
 *	If no <options> are specअगरied, then assume the h/w is alपढ़ोy setup.
 *
 *	Returns 0 अगर console matches; otherwise non-zero to use शेष matching
 */
अटल पूर्णांक univ8250_console_match(काष्ठा console *co, अक्षर *name, पूर्णांक idx,
				  अक्षर *options)
अणु
	अक्षर match[] = "uart";	/* 8250-specअगरic earlycon name */
	अचिन्हित अक्षर iotype;
	resource_माप_प्रकार addr;
	पूर्णांक i;

	अगर (म_भेदन(name, match, 4) != 0)
		वापस -ENODEV;

	अगर (uart_parse_earlycon(options, &iotype, &addr, &options))
		वापस -ENODEV;

	/* try to match the port specअगरied on the command line */
	क्रम (i = 0; i < nr_uarts; i++) अणु
		काष्ठा uart_port *port = &serial8250_ports[i].port;

		अगर (port->iotype != iotype)
			जारी;
		अगर ((iotype == UPIO_MEM || iotype == UPIO_MEM16 ||
		     iotype == UPIO_MEM32 || iotype == UPIO_MEM32BE)
		    && (port->mapbase != addr))
			जारी;
		अगर (iotype == UPIO_PORT && port->iobase != addr)
			जारी;

		co->index = i;
		port->cons = co;
		वापस serial8250_console_setup(port, options, true);
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल काष्ठा console univ8250_console = अणु
	.name		= "ttyS",
	.ग_लिखो		= univ8250_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= univ8250_console_setup,
	.निकास		= univ8250_console_निकास,
	.match		= univ8250_console_match,
	.flags		= CON_PRINTBUFFER | CON_ANYTIME,
	.index		= -1,
	.data		= &serial8250_reg,
पूर्ण;

अटल पूर्णांक __init univ8250_console_init(व्योम)
अणु
	अगर (nr_uarts == 0)
		वापस -ENODEV;

	serial8250_isa_init_ports();
	रेजिस्टर_console(&univ8250_console);
	वापस 0;
पूर्ण
console_initcall(univ8250_console_init);

#घोषणा SERIAL8250_CONSOLE	(&univ8250_console)
#अन्यथा
#घोषणा SERIAL8250_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver serial8250_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "serial",
	.dev_name		= "ttyS",
	.major			= TTY_MAJOR,
	.minor			= 64,
	.cons			= SERIAL8250_CONSOLE,
पूर्ण;

/*
 * early_serial_setup - early registration क्रम 8250 ports
 *
 * Setup an 8250 port काष्ठाure prior to console initialisation.  Use
 * after console initialisation will cause undefined behaviour.
 */
पूर्णांक __init early_serial_setup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_port *p;

	अगर (port->line >= ARRAY_SIZE(serial8250_ports) || nr_uarts == 0)
		वापस -ENODEV;

	serial8250_isa_init_ports();
	p = &serial8250_ports[port->line].port;
	p->iobase       = port->iobase;
	p->membase      = port->membase;
	p->irq          = port->irq;
	p->irqflags     = port->irqflags;
	p->uartclk      = port->uartclk;
	p->fअगरosize     = port->fअगरosize;
	p->regshअगरt     = port->regshअगरt;
	p->iotype       = port->iotype;
	p->flags        = port->flags;
	p->mapbase      = port->mapbase;
	p->mapsize      = port->mapsize;
	p->निजी_data = port->निजी_data;
	p->type		= port->type;
	p->line		= port->line;

	serial8250_set_शेषs(up_to_u8250p(p));

	अगर (port->serial_in)
		p->serial_in = port->serial_in;
	अगर (port->serial_out)
		p->serial_out = port->serial_out;
	अगर (port->handle_irq)
		p->handle_irq = port->handle_irq;

	वापस 0;
पूर्ण

/**
 *	serial8250_suspend_port - suspend one serial port
 *	@line:  serial line number
 *
 *	Suspend one serial port.
 */
व्योम serial8250_suspend_port(पूर्णांक line)
अणु
	काष्ठा uart_8250_port *up = &serial8250_ports[line];
	काष्ठा uart_port *port = &up->port;

	अगर (!console_suspend_enabled && uart_console(port) &&
	    port->type != PORT_8250) अणु
		अचिन्हित अक्षर canary = 0xa5;
		serial_out(up, UART_SCR, canary);
		अगर (serial_in(up, UART_SCR) == canary)
			up->canary = canary;
	पूर्ण

	uart_suspend_port(&serial8250_reg, port);
पूर्ण
EXPORT_SYMBOL(serial8250_suspend_port);

/**
 *	serial8250_resume_port - resume one serial port
 *	@line:  serial line number
 *
 *	Resume one serial port.
 */
व्योम serial8250_resume_port(पूर्णांक line)
अणु
	काष्ठा uart_8250_port *up = &serial8250_ports[line];
	काष्ठा uart_port *port = &up->port;

	up->canary = 0;

	अगर (up->capabilities & UART_NATSEMI) अणु
		/* Ensure it's still in high speed mode */
		serial_port_out(port, UART_LCR, 0xE0);

		ns16550a_जाओ_highspeed(up);

		serial_port_out(port, UART_LCR, 0);
		port->uartclk = 921600*16;
	पूर्ण
	uart_resume_port(&serial8250_reg, port);
पूर्ण
EXPORT_SYMBOL(serial8250_resume_port);

/*
 * Register a set of serial devices attached to a platक्रमm device.  The
 * list is terminated with a zero flags entry, which means we expect
 * all entries to have at least UPF_BOOT_AUTOCONF set.
 */
अटल पूर्णांक serial8250_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा plat_serial8250_port *p = dev_get_platdata(&dev->dev);
	काष्ठा uart_8250_port uart;
	पूर्णांक ret, i, irqflag = 0;

	स_रखो(&uart, 0, माप(uart));

	अगर (share_irqs)
		irqflag = IRQF_SHARED;

	क्रम (i = 0; p && p->flags != 0; p++, i++) अणु
		uart.port.iobase	= p->iobase;
		uart.port.membase	= p->membase;
		uart.port.irq		= p->irq;
		uart.port.irqflags	= p->irqflags;
		uart.port.uartclk	= p->uartclk;
		uart.port.regshअगरt	= p->regshअगरt;
		uart.port.iotype	= p->iotype;
		uart.port.flags		= p->flags;
		uart.port.mapbase	= p->mapbase;
		uart.port.hub6		= p->hub6;
		uart.port.has_sysrq	= p->has_sysrq;
		uart.port.निजी_data	= p->निजी_data;
		uart.port.type		= p->type;
		uart.port.serial_in	= p->serial_in;
		uart.port.serial_out	= p->serial_out;
		uart.port.handle_irq	= p->handle_irq;
		uart.port.handle_अवरोध	= p->handle_अवरोध;
		uart.port.set_termios	= p->set_termios;
		uart.port.set_ldisc	= p->set_ldisc;
		uart.port.get_mctrl	= p->get_mctrl;
		uart.port.pm		= p->pm;
		uart.port.dev		= &dev->dev;
		uart.port.irqflags	|= irqflag;
		ret = serial8250_रेजिस्टर_8250_port(&uart);
		अगर (ret < 0) अणु
			dev_err(&dev->dev, "unable to register port at index %d "
				"(IO%lx MEM%llx IRQ%d): %d\n", i,
				p->iobase, (अचिन्हित दीर्घ दीर्घ)p->mapbase,
				p->irq, ret);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Remove serial ports रेजिस्टरed against a platक्रमm device.
 */
अटल पूर्णांक serial8250_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_uarts; i++) अणु
		काष्ठा uart_8250_port *up = &serial8250_ports[i];

		अगर (up->port.dev == &dev->dev)
			serial8250_unरेजिस्टर_port(i);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक serial8250_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < UART_NR; i++) अणु
		काष्ठा uart_8250_port *up = &serial8250_ports[i];

		अगर (up->port.type != PORT_UNKNOWN && up->port.dev == &dev->dev)
			uart_suspend_port(&serial8250_reg, &up->port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक serial8250_resume(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < UART_NR; i++) अणु
		काष्ठा uart_8250_port *up = &serial8250_ports[i];

		अगर (up->port.type != PORT_UNKNOWN && up->port.dev == &dev->dev)
			serial8250_resume_port(i);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver serial8250_isa_driver = अणु
	.probe		= serial8250_probe,
	.हटाओ		= serial8250_हटाओ,
	.suspend	= serial8250_suspend,
	.resume		= serial8250_resume,
	.driver		= अणु
		.name	= "serial8250",
	पूर्ण,
पूर्ण;

/*
 * This "device" covers _all_ ISA 8250-compatible serial devices listed
 * in the table in include/यंत्र/serial.h
 */
अटल काष्ठा platक्रमm_device *serial8250_isa_devs;

/*
 * serial8250_रेजिस्टर_8250_port and serial8250_unरेजिस्टर_port allows क्रम
 * 16x50 serial ports to be configured at run-समय, to support PCMCIA
 * modems and PCI multiport cards.
 */
अटल DEFINE_MUTEX(serial_mutex);

अटल काष्ठा uart_8250_port *serial8250_find_match_or_unused(काष्ठा uart_port *port)
अणु
	पूर्णांक i;

	/*
	 * First, find a port entry which matches.
	 */
	क्रम (i = 0; i < nr_uarts; i++)
		अगर (uart_match_port(&serial8250_ports[i].port, port))
			वापस &serial8250_ports[i];

	/* try line number first अगर still available */
	i = port->line;
	अगर (i < nr_uarts && serial8250_ports[i].port.type == PORT_UNKNOWN &&
			serial8250_ports[i].port.iobase == 0)
		वापस &serial8250_ports[i];
	/*
	 * We didn't find a matching entry, so look क्रम the first
	 * मुक्त entry.  We look क्रम one which hasn't been previously
	 * used (indicated by zero iobase).
	 */
	क्रम (i = 0; i < nr_uarts; i++)
		अगर (serial8250_ports[i].port.type == PORT_UNKNOWN &&
		    serial8250_ports[i].port.iobase == 0)
			वापस &serial8250_ports[i];

	/*
	 * That also failed.  Last resort is to find any entry which
	 * करोesn't have a real port associated with it.
	 */
	क्रम (i = 0; i < nr_uarts; i++)
		अगर (serial8250_ports[i].port.type == PORT_UNKNOWN)
			वापस &serial8250_ports[i];

	वापस शून्य;
पूर्ण

अटल व्योम serial_8250_overrun_backoff_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uart_8250_port *up =
	    container_of(to_delayed_work(work), काष्ठा uart_8250_port,
			 overrun_backoff);
	काष्ठा uart_port *port = &up->port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	up->ier |= UART_IER_RLSI | UART_IER_RDI;
	up->port.पढ़ो_status_mask |= UART_LSR_DR;
	serial_out(up, UART_IER, up->ier);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/**
 *	serial8250_रेजिस्टर_8250_port - रेजिस्टर a serial port
 *	@up: serial port ढाँचा
 *
 *	Configure the serial port specअगरied by the request. If the
 *	port exists and is in use, it is hung up and unरेजिस्टरed
 *	first.
 *
 *	The port is then probed and अगर necessary the IRQ is स्वतःdetected
 *	If this fails an error is वापसed.
 *
 *	On success the port is पढ़ोy to use and the line number is वापसed.
 */
पूर्णांक serial8250_रेजिस्टर_8250_port(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_8250_port *uart;
	पूर्णांक ret = -ENOSPC;

	अगर (up->port.uartclk == 0)
		वापस -EINVAL;

	mutex_lock(&serial_mutex);

	uart = serial8250_find_match_or_unused(&up->port);
	अगर (uart && uart->port.type != PORT_8250_CIR) अणु
		काष्ठा mctrl_gpios *gpios;

		अगर (uart->port.dev)
			uart_हटाओ_one_port(&serial8250_reg, &uart->port);

		uart->port.iobase       = up->port.iobase;
		uart->port.membase      = up->port.membase;
		uart->port.irq          = up->port.irq;
		uart->port.irqflags     = up->port.irqflags;
		uart->port.uartclk      = up->port.uartclk;
		uart->port.fअगरosize     = up->port.fअगरosize;
		uart->port.regshअगरt     = up->port.regshअगरt;
		uart->port.iotype       = up->port.iotype;
		uart->port.flags        = up->port.flags | UPF_BOOT_AUTOCONF;
		uart->bugs		= up->bugs;
		uart->port.mapbase      = up->port.mapbase;
		uart->port.mapsize      = up->port.mapsize;
		uart->port.निजी_data = up->port.निजी_data;
		uart->tx_loadsz		= up->tx_loadsz;
		uart->capabilities	= up->capabilities;
		uart->port.throttle	= up->port.throttle;
		uart->port.unthrottle	= up->port.unthrottle;
		uart->port.rs485_config	= up->port.rs485_config;
		uart->port.rs485	= up->port.rs485;
		uart->rs485_start_tx	= up->rs485_start_tx;
		uart->rs485_stop_tx	= up->rs485_stop_tx;
		uart->dma		= up->dma;

		/* Take tx_loadsz from fअगरosize अगर it wasn't set separately */
		अगर (uart->port.fअगरosize && !uart->tx_loadsz)
			uart->tx_loadsz = uart->port.fअगरosize;

		अगर (up->port.dev) अणु
			uart->port.dev = up->port.dev;
			ret = uart_get_rs485_mode(&uart->port);
			अगर (ret)
				जाओ err;
		पूर्ण

		अगर (up->port.flags & UPF_FIXED_TYPE)
			uart->port.type = up->port.type;

		/*
		 * Only call mctrl_gpio_init(), अगर the device has no ACPI
		 * companion device
		 */
		अगर (!has_acpi_companion(uart->port.dev)) अणु
			gpios = mctrl_gpio_init(&uart->port, 0);
			अगर (IS_ERR(gpios)) अणु
				ret = PTR_ERR(gpios);
				जाओ err;
			पूर्ण अन्यथा अणु
				uart->gpios = gpios;
			पूर्ण
		पूर्ण

		serial8250_set_शेषs(uart);

		/* Possibly override शेष I/O functions.  */
		अगर (up->port.serial_in)
			uart->port.serial_in = up->port.serial_in;
		अगर (up->port.serial_out)
			uart->port.serial_out = up->port.serial_out;
		अगर (up->port.handle_irq)
			uart->port.handle_irq = up->port.handle_irq;
		/*  Possibly override set_termios call */
		अगर (up->port.set_termios)
			uart->port.set_termios = up->port.set_termios;
		अगर (up->port.set_ldisc)
			uart->port.set_ldisc = up->port.set_ldisc;
		अगर (up->port.get_mctrl)
			uart->port.get_mctrl = up->port.get_mctrl;
		अगर (up->port.set_mctrl)
			uart->port.set_mctrl = up->port.set_mctrl;
		अगर (up->port.get_भागisor)
			uart->port.get_भागisor = up->port.get_भागisor;
		अगर (up->port.set_भागisor)
			uart->port.set_भागisor = up->port.set_भागisor;
		अगर (up->port.startup)
			uart->port.startup = up->port.startup;
		अगर (up->port.shutकरोwn)
			uart->port.shutकरोwn = up->port.shutकरोwn;
		अगर (up->port.pm)
			uart->port.pm = up->port.pm;
		अगर (up->port.handle_अवरोध)
			uart->port.handle_अवरोध = up->port.handle_अवरोध;
		अगर (up->dl_पढ़ो)
			uart->dl_पढ़ो = up->dl_पढ़ो;
		अगर (up->dl_ग_लिखो)
			uart->dl_ग_लिखो = up->dl_ग_लिखो;

		अगर (uart->port.type != PORT_8250_CIR) अणु
			अगर (serial8250_isa_config != शून्य)
				serial8250_isa_config(0, &uart->port,
						&uart->capabilities);

			serial8250_apply_quirks(uart);
			ret = uart_add_one_port(&serial8250_reg,
						&uart->port);
			अगर (ret)
				जाओ err;

			ret = uart->port.line;
		पूर्ण अन्यथा अणु
			dev_info(uart->port.dev,
				"skipping CIR port at 0x%lx / 0x%llx, IRQ %d\n",
				uart->port.iobase,
				(अचिन्हित दीर्घ दीर्घ)uart->port.mapbase,
				uart->port.irq);

			ret = 0;
		पूर्ण

		/* Initialise पूर्णांकerrupt backoff work अगर required */
		अगर (up->overrun_backoff_समय_ms > 0) अणु
			uart->overrun_backoff_समय_ms =
				up->overrun_backoff_समय_ms;
			INIT_DELAYED_WORK(&uart->overrun_backoff,
					serial_8250_overrun_backoff_work);
		पूर्ण अन्यथा अणु
			uart->overrun_backoff_समय_ms = 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&serial_mutex);

	वापस ret;

err:
	uart->port.dev = शून्य;
	mutex_unlock(&serial_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(serial8250_रेजिस्टर_8250_port);

/**
 *	serial8250_unरेजिस्टर_port - हटाओ a 16x50 serial port at runसमय
 *	@line: serial line number
 *
 *	Remove one serial port.  This may not be called from पूर्णांकerrupt
 *	context.  We hand the port back to the our control.
 */
व्योम serial8250_unरेजिस्टर_port(पूर्णांक line)
अणु
	काष्ठा uart_8250_port *uart = &serial8250_ports[line];

	mutex_lock(&serial_mutex);

	अगर (uart->em485) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&uart->port.lock, flags);
		serial8250_em485_destroy(uart);
		spin_unlock_irqrestore(&uart->port.lock, flags);
	पूर्ण

	uart_हटाओ_one_port(&serial8250_reg, &uart->port);
	अगर (serial8250_isa_devs) अणु
		uart->port.flags &= ~UPF_BOOT_AUTOCONF;
		uart->port.type = PORT_UNKNOWN;
		uart->port.dev = &serial8250_isa_devs->dev;
		uart->capabilities = 0;
		serial8250_apply_quirks(uart);
		uart_add_one_port(&serial8250_reg, &uart->port);
	पूर्ण अन्यथा अणु
		uart->port.dev = शून्य;
	पूर्ण
	mutex_unlock(&serial_mutex);
पूर्ण
EXPORT_SYMBOL(serial8250_unरेजिस्टर_port);

अटल पूर्णांक __init serial8250_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (nr_uarts == 0)
		वापस -ENODEV;

	serial8250_isa_init_ports();

	pr_info("Serial: 8250/16550 driver, %d ports, IRQ sharing %sabled\n",
		nr_uarts, share_irqs ? "en" : "dis");

#अगर_घोषित CONFIG_SPARC
	ret = sunserial_रेजिस्टर_minors(&serial8250_reg, UART_NR);
#अन्यथा
	serial8250_reg.nr = UART_NR;
	ret = uart_रेजिस्टर_driver(&serial8250_reg);
#पूर्ण_अगर
	अगर (ret)
		जाओ out;

	ret = serial8250_pnp_init();
	अगर (ret)
		जाओ unreg_uart_drv;

	serial8250_isa_devs = platक्रमm_device_alloc("serial8250",
						    PLAT8250_DEV_LEGACY);
	अगर (!serial8250_isa_devs) अणु
		ret = -ENOMEM;
		जाओ unreg_pnp;
	पूर्ण

	ret = platक्रमm_device_add(serial8250_isa_devs);
	अगर (ret)
		जाओ put_dev;

	serial8250_रेजिस्टर_ports(&serial8250_reg, &serial8250_isa_devs->dev);

	ret = platक्रमm_driver_रेजिस्टर(&serial8250_isa_driver);
	अगर (ret == 0)
		जाओ out;

	platक्रमm_device_del(serial8250_isa_devs);
put_dev:
	platक्रमm_device_put(serial8250_isa_devs);
unreg_pnp:
	serial8250_pnp_निकास();
unreg_uart_drv:
#अगर_घोषित CONFIG_SPARC
	sunserial_unरेजिस्टर_minors(&serial8250_reg, UART_NR);
#अन्यथा
	uart_unरेजिस्टर_driver(&serial8250_reg);
#पूर्ण_अगर
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास serial8250_निकास(व्योम)
अणु
	काष्ठा platक्रमm_device *isa_dev = serial8250_isa_devs;

	/*
	 * This tells serial8250_unरेजिस्टर_port() not to re-रेजिस्टर
	 * the ports (thereby making serial8250_isa_driver permanently
	 * in use.)
	 */
	serial8250_isa_devs = शून्य;

	platक्रमm_driver_unरेजिस्टर(&serial8250_isa_driver);
	platक्रमm_device_unरेजिस्टर(isa_dev);

	serial8250_pnp_निकास();

#अगर_घोषित CONFIG_SPARC
	sunserial_unरेजिस्टर_minors(&serial8250_reg, UART_NR);
#अन्यथा
	uart_unरेजिस्टर_driver(&serial8250_reg);
#पूर्ण_अगर
पूर्ण

module_init(serial8250_init);
module_निकास(serial8250_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Generic 8250/16x50 serial driver");

module_param_hw(share_irqs, uपूर्णांक, other, 0644);
MODULE_PARM_DESC(share_irqs, "Share IRQs with other non-8250/16x50 devices (unsafe)");

module_param(nr_uarts, uपूर्णांक, 0644);
MODULE_PARM_DESC(nr_uarts, "Maximum number of UARTs supported. (1-" __MODULE_STRING(CONFIG_SERIAL_8250_NR_UARTS) ")");

module_param(skip_txen_test, uपूर्णांक, 0644);
MODULE_PARM_DESC(skip_txen_test, "Skip checking for the TXEN bug at init time");

#अगर_घोषित CONFIG_SERIAL_8250_RSA
module_param_hw_array(probe_rsa, uदीर्घ, ioport, &probe_rsa_count, 0444);
MODULE_PARM_DESC(probe_rsa, "Probe I/O ports for RSA");
#पूर्ण_अगर
MODULE_ALIAS_CHARDEV_MAJOR(TTY_MAJOR);

#अगर_घोषित CONFIG_SERIAL_8250_DEPRECATED_OPTIONS
#अगर_अघोषित MODULE
/* This module was नामd to 8250_core in 3.7.  Keep the old "8250" name
 * working as well क्रम the module options so we करोn't अवरोध people.  We
 * need to keep the names identical and the convenient macros will happily
 * refuse to let us करो that by failing the build with redefinition errors
 * of global variables.  So we stick them inside a dummy function to aव्योम
 * those conflicts.  The options still get parsed, and the redefined
 * MODULE_PARAM_PREFIX lets us keep the "8250." syntax alive.
 *
 * This is hacky.  I'm sorry.
 */
अटल व्योम __used s8250_options(व्योम)
अणु
#अघोषित MODULE_PARAM_PREFIX
#घोषणा MODULE_PARAM_PREFIX "8250_core."

	module_param_cb(share_irqs, &param_ops_uपूर्णांक, &share_irqs, 0644);
	module_param_cb(nr_uarts, &param_ops_uपूर्णांक, &nr_uarts, 0644);
	module_param_cb(skip_txen_test, &param_ops_uपूर्णांक, &skip_txen_test, 0644);
#अगर_घोषित CONFIG_SERIAL_8250_RSA
	__module_param_call(MODULE_PARAM_PREFIX, probe_rsa,
		&param_array_ops, .arr = &__param_arr_probe_rsa,
		0444, -1, 0);
#पूर्ण_अगर
पूर्ण
#अन्यथा
MODULE_ALIAS("8250_core");
#पूर्ण_अगर
#पूर्ण_अगर
