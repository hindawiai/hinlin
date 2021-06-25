<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>

#समावेश "spk_types.h"
#समावेश "speakup.h"
#समावेश "spk_priv.h"
#समावेश "serialio.h"

#समावेश <linux/serial_core.h>
/* WARNING:  Do not change this to <linux/serial.h> without testing that
 * SERIAL_PORT_DFNS करोes get defined to the appropriate value.
 */
#समावेश <यंत्र/serial.h>

#अगर_अघोषित SERIAL_PORT_DFNS
#घोषणा SERIAL_PORT_DFNS
#पूर्ण_अगर

अटल व्योम start_serial_पूर्णांकerrupt(पूर्णांक irq);

अटल स्थिर काष्ठा old_serial_port rs_table[] = अणु
	SERIAL_PORT_DFNS
पूर्ण;

अटल स्थिर काष्ठा old_serial_port *serstate;
अटल पूर्णांक समयouts;

अटल पूर्णांक spk_serial_out(काष्ठा spk_synth *in_synth, स्थिर अक्षर ch);
अटल व्योम spk_serial_send_xअक्षर(काष्ठा spk_synth *in_synth, अक्षर ch);
अटल व्योम spk_serial_tiocmset(काष्ठा spk_synth *in_synth, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल अचिन्हित अक्षर spk_serial_in(काष्ठा spk_synth *in_synth);
अटल अचिन्हित अक्षर spk_serial_in_noरुको(काष्ठा spk_synth *in_synth);
अटल व्योम spk_serial_flush_buffer(काष्ठा spk_synth *in_synth);
अटल पूर्णांक spk_serial_रुको_क्रम_xmitr(काष्ठा spk_synth *in_synth);

काष्ठा spk_io_ops spk_serial_io_ops = अणु
	.synth_out = spk_serial_out,
	.send_xअक्षर = spk_serial_send_xअक्षर,
	.tiocmset = spk_serial_tiocmset,
	.synth_in = spk_serial_in,
	.synth_in_noरुको = spk_serial_in_noरुको,
	.flush_buffer = spk_serial_flush_buffer,
	.रुको_क्रम_xmitr = spk_serial_रुको_क्रम_xmitr,
पूर्ण;
EXPORT_SYMBOL_GPL(spk_serial_io_ops);

स्थिर काष्ठा old_serial_port *spk_serial_init(पूर्णांक index)
अणु
	पूर्णांक baud = 9600, quot = 0;
	अचिन्हित पूर्णांक cval = 0;
	पूर्णांक cflag = CREAD | HUPCL | CLOCAL | B9600 | CS8;
	स्थिर काष्ठा old_serial_port *ser;
	पूर्णांक err;

	अगर (index >= ARRAY_SIZE(rs_table)) अणु
		pr_info("no port info for ttyS%d\n", index);
		वापस शून्य;
	पूर्ण
	ser = rs_table + index;

	/*	Divisor, bytesize and parity */
	quot = ser->baud_base / baud;
	cval = cflag & (CSIZE | CSTOPB);
#अगर defined(__घातerpc__) || defined(__alpha__)
	cval >>= 8;
#अन्यथा /* !__घातerpc__ && !__alpha__ */
	cval >>= 4;
#पूर्ण_अगर /* !__घातerpc__ && !__alpha__ */
	अगर (cflag & PARENB)
		cval |= UART_LCR_PARITY;
	अगर (!(cflag & PARODD))
		cval |= UART_LCR_EPAR;
	अगर (synth_request_region(ser->port, 8)) अणु
		/* try to take it back. */
		pr_info("Ports not available, trying to steal them\n");
		__release_region(&ioport_resource, ser->port, 8);
		err = synth_request_region(ser->port, 8);
		अगर (err) अणु
			pr_warn("Unable to allocate port at %x, errno %i",
				ser->port, err);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/*	Disable UART पूर्णांकerrupts, set DTR and RTS high
	 *	and set speed.
	 */
	outb(cval | UART_LCR_DLAB, ser->port + UART_LCR);	/* set DLAB */
	outb(quot & 0xff, ser->port + UART_DLL);	/* LS of भागisor */
	outb(quot >> 8, ser->port + UART_DLM);		/* MS of भागisor */
	outb(cval, ser->port + UART_LCR);		/* reset DLAB */

	/* Turn off Interrupts */
	outb(0, ser->port + UART_IER);
	outb(UART_MCR_DTR | UART_MCR_RTS, ser->port + UART_MCR);

	/* If we पढ़ो 0xff from the LSR, there is no UART here. */
	अगर (inb(ser->port + UART_LSR) == 0xff) अणु
		synth_release_region(ser->port, 8);
		serstate = शून्य;
		वापस शून्य;
	पूर्ण

	mdelay(1);
	speakup_info.port_tts = ser->port;
	serstate = ser;

	start_serial_पूर्णांकerrupt(ser->irq);

	वापस ser;
पूर्ण

अटल irqवापस_t synth_पढ़ोbuf_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक c;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	जबतक (inb_p(speakup_info.port_tts + UART_LSR) & UART_LSR_DR) अणु
		c = inb_p(speakup_info.port_tts + UART_RX);
		synth->पढ़ो_buff_add((u_अक्षर)c);
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम start_serial_पूर्णांकerrupt(पूर्णांक irq)
अणु
	पूर्णांक rv;

	अगर (!synth->पढ़ो_buff_add)
		वापस;

	rv = request_irq(irq, synth_पढ़ोbuf_handler, IRQF_SHARED,
			 "serial", (व्योम *)synth_पढ़ोbuf_handler);

	अगर (rv)
		pr_err("Unable to request Speakup serial I R Q\n");
	/* Set MCR */
	outb(UART_MCR_DTR | UART_MCR_RTS | UART_MCR_OUT2,
	     speakup_info.port_tts + UART_MCR);
	/* Turn on Interrupts */
	outb(UART_IER_MSI | UART_IER_RLSI | UART_IER_RDI,
	     speakup_info.port_tts + UART_IER);
	inb(speakup_info.port_tts + UART_LSR);
	inb(speakup_info.port_tts + UART_RX);
	inb(speakup_info.port_tts + UART_IIR);
	inb(speakup_info.port_tts + UART_MSR);
	outb(1, speakup_info.port_tts + UART_FCR);	/* Turn FIFO On */
पूर्ण

अटल व्योम spk_serial_send_xअक्षर(काष्ठा spk_synth *synth, अक्षर ch)
अणु
	पूर्णांक समयout = SPK_XMITR_TIMEOUT;

	जबतक (spk_serial_tx_busy()) अणु
		अगर (!--समयout)
			अवरोध;
		udelay(1);
	पूर्ण
	outb(ch, speakup_info.port_tts);
पूर्ण

अटल व्योम spk_serial_tiocmset(काष्ठा spk_synth *in_synth, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	पूर्णांक old = inb(speakup_info.port_tts + UART_MCR);

	outb((old & ~clear) | set, speakup_info.port_tts + UART_MCR);
पूर्ण

पूर्णांक spk_serial_synth_probe(काष्ठा spk_synth *synth)
अणु
	स्थिर काष्ठा old_serial_port *ser;
	पूर्णांक failed = 0;

	अगर ((synth->ser >= SPK_LO_TTY) && (synth->ser <= SPK_HI_TTY)) अणु
		ser = spk_serial_init(synth->ser);
		अगर (!ser) अणु
			failed = -1;
		पूर्ण अन्यथा अणु
			outb_p(0, ser->port);
			mdelay(1);
			outb_p('\r', ser->port);
		पूर्ण
	पूर्ण अन्यथा अणु
		failed = -1;
		pr_warn("ttyS%i is an invalid port\n", synth->ser);
	पूर्ण
	अगर (failed) अणु
		pr_info("%s: not found\n", synth->दीर्घ_name);
		वापस -ENODEV;
	पूर्ण
	pr_info("%s: ttyS%i, Driver Version %s\n",
		synth->दीर्घ_name, synth->ser, synth->version);
	synth->alive = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spk_serial_synth_probe);

व्योम spk_stop_serial_पूर्णांकerrupt(व्योम)
अणु
	अगर (speakup_info.port_tts == 0)
		वापस;

	अगर (!synth->पढ़ो_buff_add)
		वापस;

	/* Turn off पूर्णांकerrupts */
	outb(0, speakup_info.port_tts + UART_IER);
	/* Free IRQ */
	मुक्त_irq(serstate->irq, (व्योम *)synth_पढ़ोbuf_handler);
पूर्ण
EXPORT_SYMBOL_GPL(spk_stop_serial_पूर्णांकerrupt);

अटल पूर्णांक spk_serial_रुको_क्रम_xmitr(काष्ठा spk_synth *in_synth)
अणु
	पूर्णांक पंचांगout = SPK_XMITR_TIMEOUT;

	अगर ((in_synth->alive) && (समयouts >= NUM_DISABLE_TIMEOUTS)) अणु
		pr_warn("%s: too many timeouts, deactivating speakup\n",
			in_synth->दीर्घ_name);
		in_synth->alive = 0;
		/* No synth any more, so nobody will restart TTYs, and we thus
		 * need to करो it ourselves.  Now that there is no synth we can
		 * let application flood anyway
		 */
		speakup_start_ttys();
		समयouts = 0;
		वापस 0;
	पूर्ण
	जबतक (spk_serial_tx_busy()) अणु
		अगर (--पंचांगout == 0) अणु
			pr_warn("%s: timed out (tx busy)\n",
				in_synth->दीर्घ_name);
			समयouts++;
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	पंचांगout = SPK_CTS_TIMEOUT;
	जबतक (!((inb_p(speakup_info.port_tts + UART_MSR)) & UART_MSR_CTS)) अणु
		/* CTS */
		अगर (--पंचांगout == 0) अणु
			समयouts++;
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	समयouts = 0;
	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर spk_serial_in(काष्ठा spk_synth *in_synth)
अणु
	पूर्णांक पंचांगout = SPK_SERIAL_TIMEOUT;

	जबतक (!(inb_p(speakup_info.port_tts + UART_LSR) & UART_LSR_DR)) अणु
		अगर (--पंचांगout == 0) अणु
			pr_warn("time out while waiting for input.\n");
			वापस 0xff;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस inb_p(speakup_info.port_tts + UART_RX);
पूर्ण

अटल अचिन्हित अक्षर spk_serial_in_noरुको(काष्ठा spk_synth *in_synth)
अणु
	अचिन्हित अक्षर lsr;

	lsr = inb_p(speakup_info.port_tts + UART_LSR);
	अगर (!(lsr & UART_LSR_DR))
		वापस 0;
	वापस inb_p(speakup_info.port_tts + UART_RX);
पूर्ण

अटल व्योम spk_serial_flush_buffer(काष्ठा spk_synth *in_synth)
अणु
	/* TODO: flush the UART 16550 buffer */
पूर्ण

अटल पूर्णांक spk_serial_out(काष्ठा spk_synth *in_synth, स्थिर अक्षर ch)
अणु
	अगर (in_synth->alive && spk_serial_रुको_क्रम_xmitr(in_synth)) अणु
		outb_p(ch, speakup_info.port_tts);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर अक्षर *spk_serial_synth_immediate(काष्ठा spk_synth *synth,
				       स्थिर अक्षर *buff)
अणु
	u_अक्षर ch;

	जबतक ((ch = *buff)) अणु
		अगर (ch == '\n')
			ch = synth->procspeech;
		अगर (spk_serial_रुको_क्रम_xmitr(synth))
			outb(ch, speakup_info.port_tts);
		अन्यथा
			वापस buff;
		buff++;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(spk_serial_synth_immediate);

व्योम spk_serial_release(काष्ठा spk_synth *synth)
अणु
	spk_stop_serial_पूर्णांकerrupt();
	अगर (speakup_info.port_tts == 0)
		वापस;
	synth_release_region(speakup_info.port_tts, 8);
	speakup_info.port_tts = 0;
पूर्ण
EXPORT_SYMBOL_GPL(spk_serial_release);
