<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   serial.c
 *   Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *                    Isaku Yamahata <yamahata@निजी.email.ne.jp>,
 *		      George Hansper <ghansper@apana.org.au>,
 *		      Hannu Savolainen
 *
 *   This code is based on the code from ALSA 0.5.9, but heavily rewritten.
 *
 * Sat Mar 31 17:27:57 PST 2001 tim.mann@compaq.com 
 *      Added support क्रम the Midiator MS-124T and क्रम the MS-124W in
 *      Single Addressed (S/A) or Multiple Burst (M/B) mode, with
 *      घातer derived either parasitically from the serial port or
 *      from a separate घातer supply.
 *
 *      More करोcumentation can be found in serial-u16550.txt.
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/initval.h>

#समावेश <linux/serial_reg.h>
#समावेश <linux/jअगरfies.h>

MODULE_DESCRIPTION("MIDI serial u16550");
MODULE_LICENSE("GPL");

#घोषणा SNDRV_SERIAL_SOUNDCANVAS 0 /* Roland Soundcanvas; F5 NN selects part */
#घोषणा SNDRV_SERIAL_MS124T 1      /* Midiator MS-124T */
#घोषणा SNDRV_SERIAL_MS124W_SA 2   /* Midiator MS-124W in S/A mode */
#घोषणा SNDRV_SERIAL_MS124W_MB 3   /* Midiator MS-124W in M/B mode */
#घोषणा SNDRV_SERIAL_GENERIC 4     /* Generic Interface */
#घोषणा SNDRV_SERIAL_MAX_ADAPTOR SNDRV_SERIAL_GENERIC
अटल स्थिर अक्षर * स्थिर adaptor_names[] = अणु
	"Soundcanvas",
        "MS-124T",
	"MS-124W S/A",
	"MS-124W M/B",
	"Generic"
पूर्ण;

#घोषणा SNDRV_SERIAL_NORMALBUFF 0 /* Normal blocking buffer operation */
#घोषणा SNDRV_SERIAL_DROPBUFF   1 /* Non-blocking discard operation */

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE; /* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT; /* 0x3f8,0x2f8,0x3e8,0x2e8 */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ; 	/* 3,4,5,7,9,10,11,14,15 */
अटल पूर्णांक speed[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 38400पूर्ण; /* 9600,19200,38400,57600,115200 */
अटल पूर्णांक base[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 115200पूर्ण; /* baud base */
अटल पूर्णांक outs[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;	 /* 1 to 16 */
अटल पूर्णांक ins[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;	/* 1 to 16 */
अटल पूर्णांक adaptor[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = SNDRV_SERIAL_SOUNDCANVASपूर्ण;
अटल bool droponfull[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS -1)] = SNDRV_SERIAL_NORMALBUFF पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Serial MIDI.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Serial MIDI.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable UART16550A chip.");
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for UART16550A chip.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for UART16550A chip.");
module_param_array(speed, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(speed, "Speed in bauds.");
module_param_array(base, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(base, "Base for divisor in bauds.");
module_param_array(outs, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(outs, "Number of MIDI outputs.");
module_param_array(ins, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(ins, "Number of MIDI inputs.");
module_param_array(droponfull, bool, शून्य, 0444);
MODULE_PARM_DESC(droponfull, "Flag to enable drop-on-full buffer mode");

module_param_array(adaptor, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(adaptor, "Type of adaptor.");

/*#घोषणा SNDRV_SERIAL_MS124W_MB_NOCOMBO 1*/  /* Address outs as 0-3 instead of biपंचांगap */

#घोषणा SNDRV_SERIAL_MAX_OUTS	16		/* max 64, min 16 */
#घोषणा SNDRV_SERIAL_MAX_INS	16		/* max 64, min 16 */

#घोषणा TX_BUFF_SIZE		(1<<15)		/* Must be 2^n */
#घोषणा TX_BUFF_MASK		(TX_BUFF_SIZE - 1)

#घोषणा SERIAL_MODE_NOT_OPENED 		(0)
#घोषणा SERIAL_MODE_INPUT_OPEN		(1 << 0)
#घोषणा SERIAL_MODE_OUTPUT_OPEN		(1 << 1)
#घोषणा SERIAL_MODE_INPUT_TRIGGERED	(1 << 2)
#घोषणा SERIAL_MODE_OUTPUT_TRIGGERED	(1 << 3)

काष्ठा snd_uart16550 अणु
	काष्ठा snd_card *card;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *midi_output[SNDRV_SERIAL_MAX_OUTS];
	काष्ठा snd_rawmidi_substream *midi_input[SNDRV_SERIAL_MAX_INS];

	पूर्णांक filemode;		/* खोलो status of file */

	spinlock_t खोलो_lock;

	पूर्णांक irq;

	अचिन्हित दीर्घ base;
	काष्ठा resource *res_base;

	अचिन्हित पूर्णांक speed;
	अचिन्हित पूर्णांक speed_base;
	अचिन्हित अक्षर भागisor;

	अचिन्हित अक्षर old_भागisor_lsb;
	अचिन्हित अक्षर old_भागisor_msb;
	अचिन्हित अक्षर old_line_ctrl_reg;

	/* parameter क्रम using of ग_लिखो loop */
	लघु पूर्णांक fअगरo_limit;	/* used in uart16550 */
        लघु पूर्णांक fअगरo_count;	/* used in uart16550 */

	/* type of adaptor */
	पूर्णांक adaptor;

	/* inमाला_दो */
	पूर्णांक prev_in;
	अचिन्हित अक्षर rstatus;

	/* outमाला_दो */
	पूर्णांक prev_out;
	अचिन्हित अक्षर prev_status[SNDRV_SERIAL_MAX_OUTS];

	/* ग_लिखो buffer and its writing/पढ़ोing position */
	अचिन्हित अक्षर tx_buff[TX_BUFF_SIZE];
	पूर्णांक buff_in_count;
        पूर्णांक buff_in;
        पूर्णांक buff_out;
        पूर्णांक drop_on_full;

	/* रुको समयr */
	अचिन्हित पूर्णांक समयr_running:1;
	काष्ठा समयr_list buffer_समयr;

पूर्ण;

अटल काष्ठा platक्रमm_device *devices[SNDRV_CARDS];

अटल अंतरभूत व्योम snd_uart16550_add_समयr(काष्ठा snd_uart16550 *uart)
अणु
	अगर (!uart->समयr_running) अणु
		/* समयr 38600bps * 10bit * 16byte */
		mod_समयr(&uart->buffer_समयr, jअगरfies + (HZ + 255) / 256);
		uart->समयr_running = 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम snd_uart16550_del_समयr(काष्ठा snd_uart16550 *uart)
अणु
	अगर (uart->समयr_running) अणु
		del_समयr(&uart->buffer_समयr);
		uart->समयr_running = 0;
	पूर्ण
पूर्ण

/* This macro is only used in snd_uart16550_io_loop */
अटल अंतरभूत व्योम snd_uart16550_buffer_output(काष्ठा snd_uart16550 *uart)
अणु
	अचिन्हित लघु buff_out = uart->buff_out;
	अगर (uart->buff_in_count > 0) अणु
		outb(uart->tx_buff[buff_out], uart->base + UART_TX);
		uart->fअगरo_count++;
		buff_out++;
		buff_out &= TX_BUFF_MASK;
		uart->buff_out = buff_out;
		uart->buff_in_count--;
	पूर्ण
पूर्ण

/* This loop should be called with पूर्णांकerrupts disabled
 * We करोn't want to पूर्णांकerrupt this, 
 * as we're alपढ़ोy handling an पूर्णांकerrupt 
 */
अटल व्योम snd_uart16550_io_loop(काष्ठा snd_uart16550 * uart)
अणु
	अचिन्हित अक्षर c, status;
	पूर्णांक substream;

	/* recall previous stream */
	substream = uart->prev_in;

	/* Read Loop */
	जबतक ((status = inb(uart->base + UART_LSR)) & UART_LSR_DR) अणु
		/* जबतक receive data पढ़ोy */
		c = inb(uart->base + UART_RX);

		/* keep track of last status byte */
		अगर (c & 0x80)
			uart->rstatus = c;

		/* handle stream चयन */
		अगर (uart->adaptor == SNDRV_SERIAL_GENERIC) अणु
			अगर (uart->rstatus == 0xf5) अणु
				अगर (c <= SNDRV_SERIAL_MAX_INS && c > 0)
					substream = c - 1;
				अगर (c != 0xf5)
					/* prevent future bytes from being
					   पूर्णांकerpreted as streams */
					uart->rstatus = 0;
			पूर्ण अन्यथा अगर ((uart->filemode & SERIAL_MODE_INPUT_OPEN)
				   && uart->midi_input[substream])
				snd_rawmidi_receive(uart->midi_input[substream],
						    &c, 1);
		पूर्ण अन्यथा अगर ((uart->filemode & SERIAL_MODE_INPUT_OPEN) &&
			   uart->midi_input[substream])
			snd_rawmidi_receive(uart->midi_input[substream], &c, 1);

		अगर (status & UART_LSR_OE)
			snd_prपूर्णांकk(KERN_WARNING
				   "%s: Overrun on device at 0x%lx\n",
			       uart->rmidi->name, uart->base);
	पूर्ण

	/* remember the last stream */
	uart->prev_in = substream;

	/* no need of check SERIAL_MODE_OUTPUT_OPEN because अगर not,
	   buffer is never filled. */
	/* Check ग_लिखो status */
	अगर (status & UART_LSR_THRE)
		uart->fअगरo_count = 0;
	अगर (uart->adaptor == SNDRV_SERIAL_MS124W_SA
	   || uart->adaptor == SNDRV_SERIAL_GENERIC) अणु
		/* Can't use FIFO, must send only when CTS is true */
		status = inb(uart->base + UART_MSR);
		जबतक (uart->fअगरo_count == 0 && (status & UART_MSR_CTS) &&
		       uart->buff_in_count > 0) अणु
		       snd_uart16550_buffer_output(uart);
		       status = inb(uart->base + UART_MSR);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Write loop */
		जबतक (uart->fअगरo_count < uart->fअगरo_limit /* Can we ग_लिखो ? */
		       && uart->buff_in_count > 0)	/* Do we want to? */
			snd_uart16550_buffer_output(uart);
	पूर्ण
	अगर (uart->irq < 0 && uart->buff_in_count > 0)
		snd_uart16550_add_समयr(uart);
पूर्ण

/* NOTES ON SERVICING INTERUPTS
 * ---------------------------
 * After receiving a पूर्णांकerrupt, it is important to indicate to the UART that
 * this has been करोne. 
 * For a Rx पूर्णांकerrupt, this is करोne by पढ़ोing the received byte.
 * For a Tx पूर्णांकerrupt this is करोne by either:
 * a) Writing a byte
 * b) Reading the IIR
 * It is particularly important to पढ़ो the IIR अगर a Tx पूर्णांकerrupt is received
 * when there is no data in tx_buff[], as in this हाल there no other
 * indication that the पूर्णांकerrupt has been serviced, and it reमुख्यs outstanding
 * indefinitely. This has the curious side effect that and no further पूर्णांकerrupts
 * will be generated from this device AT ALL!!.
 * It is also desirable to clear outstanding पूर्णांकerrupts when the device is
 * खोलोed/बंदd.
 *
 *
 * Note that some devices need OUT2 to be set beक्रमe they will generate
 * पूर्णांकerrupts at all. (Possibly tied to an पूर्णांकernal pull-up on CTS?)
 */
अटल irqवापस_t snd_uart16550_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_uart16550 *uart;

	uart = dev_id;
	spin_lock(&uart->खोलो_lock);
	अगर (uart->filemode == SERIAL_MODE_NOT_OPENED) अणु
		spin_unlock(&uart->खोलो_lock);
		वापस IRQ_NONE;
	पूर्ण
	/* indicate to the UART that the पूर्णांकerrupt has been serviced */
	inb(uart->base + UART_IIR);
	snd_uart16550_io_loop(uart);
	spin_unlock(&uart->खोलो_lock);
	वापस IRQ_HANDLED;
पूर्ण

/* When the polling mode, this function calls snd_uart16550_io_loop. */
अटल व्योम snd_uart16550_buffer_समयr(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_uart16550 *uart;

	uart = from_समयr(uart, t, buffer_समयr);
	spin_lock_irqsave(&uart->खोलो_lock, flags);
	snd_uart16550_del_समयr(uart);
	snd_uart16550_io_loop(uart);
	spin_unlock_irqrestore(&uart->खोलो_lock, flags);
पूर्ण

/*
 *  this method probes, अगर an uart sits on given port
 *  वापस 0 अगर found
 *  वापस negative error अगर not found
 */
अटल पूर्णांक snd_uart16550_detect(काष्ठा snd_uart16550 *uart)
अणु
	अचिन्हित दीर्घ io_base = uart->base;
	पूर्णांक ok;
	अचिन्हित अक्षर c;

	/* Do some vague tests क्रम the presence of the uart */
	अगर (io_base == 0 || io_base == SNDRV_AUTO_PORT) अणु
		वापस -ENODEV;	/* Not configured */
	पूर्ण

	uart->res_base = request_region(io_base, 8, "Serial MIDI");
	अगर (uart->res_base == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "u16550: can't grab port 0x%lx\n", io_base);
		वापस -EBUSY;
	पूर्ण

	/* uart detected unless one of the following tests should fail */
	ok = 1;
	/* 8 data-bits, 1 stop-bit, parity off, DLAB = 0 */
	outb(UART_LCR_WLEN8, io_base + UART_LCR); /* Line Control Register */
	c = inb(io_base + UART_IER);
	/* The top four bits of the IER should always == 0 */
	अगर ((c & 0xf0) != 0)
		ok = 0;		/* failed */

	outb(0xaa, io_base + UART_SCR);
	/* Write arbitrary data पूर्णांकo the scratch reg */
	c = inb(io_base + UART_SCR);
	/* If it comes back, it's OK */
	अगर (c != 0xaa)
		ok = 0;		/* failed */

	outb(0x55, io_base + UART_SCR);
	/* Write arbitrary data पूर्णांकo the scratch reg */
	c = inb(io_base + UART_SCR);
	/* If it comes back, it's OK */
	अगर (c != 0x55)
		ok = 0;		/* failed */

	वापस ok;
पूर्ण

अटल व्योम snd_uart16550_करो_खोलो(काष्ठा snd_uart16550 * uart)
अणु
	अक्षर byte;

	/* Initialize basic variables */
	uart->buff_in_count = 0;
	uart->buff_in = 0;
	uart->buff_out = 0;
	uart->fअगरo_limit = 1;
	uart->fअगरo_count = 0;
	uart->समयr_running = 0;

	outb(UART_FCR_ENABLE_FIFO	/* Enable FIFO's (अगर available) */
	     | UART_FCR_CLEAR_RCVR	/* Clear receiver FIFO */
	     | UART_FCR_CLEAR_XMIT	/* Clear transmitter FIFO */
	     | UART_FCR_TRIGGER_4	/* Set FIFO trigger at 4-bytes */
	/* NOTE: पूर्णांकerrupt generated after T=(समय)4-bytes
	 * अगर less than UART_FCR_TRIGGER bytes received
	 */
	     ,uart->base + UART_FCR);	/* FIFO Control Register */

	अगर ((inb(uart->base + UART_IIR) & 0xf0) == 0xc0)
		uart->fअगरo_limit = 16;
	अगर (uart->भागisor != 0) अणु
		uart->old_line_ctrl_reg = inb(uart->base + UART_LCR);
		outb(UART_LCR_DLAB	/* Divisor latch access bit */
		     ,uart->base + UART_LCR);	/* Line Control Register */
		uart->old_भागisor_lsb = inb(uart->base + UART_DLL);
		uart->old_भागisor_msb = inb(uart->base + UART_DLM);

		outb(uart->भागisor
		     ,uart->base + UART_DLL);	/* Divisor Latch Low */
		outb(0
		     ,uart->base + UART_DLM);	/* Divisor Latch High */
		/* DLAB is reset to 0 in next outb() */
	पूर्ण
	/* Set serial parameters (parity off, etc) */
	outb(UART_LCR_WLEN8	/* 8 data-bits */
	     | 0		/* 1 stop-bit */
	     | 0		/* parity off */
	     | 0		/* DLAB = 0 */
	     ,uart->base + UART_LCR);	/* Line Control Register */

	चयन (uart->adaptor) अणु
	शेष:
		outb(UART_MCR_RTS	/* Set Request-To-Send line active */
		     | UART_MCR_DTR	/* Set Data-Terminal-Ready line active */
		     | UART_MCR_OUT2	/* Set OUT2 - not always required, but when
					 * it is, it is ESSENTIAL क्रम enabling पूर्णांकerrupts
				 */
		     ,uart->base + UART_MCR);	/* Modem Control Register */
		अवरोध;
	हाल SNDRV_SERIAL_MS124W_SA:
	हाल SNDRV_SERIAL_MS124W_MB:
		/* MS-124W can draw घातer from RTS and DTR अगर they
		   are in opposite states. */ 
		outb(UART_MCR_RTS | (0&UART_MCR_DTR) | UART_MCR_OUT2,
		     uart->base + UART_MCR);
		अवरोध;
	हाल SNDRV_SERIAL_MS124T:
		/* MS-124T can draw घातer from RTS and/or DTR (preferably
		   both) अगर they are both निश्चितed. */
		outb(UART_MCR_RTS | UART_MCR_DTR | UART_MCR_OUT2,
		     uart->base + UART_MCR);
		अवरोध;
	पूर्ण

	अगर (uart->irq < 0) अणु
		byte = (0 & UART_IER_RDI)	/* Disable Receiver data पूर्णांकerrupt */
		    |(0 & UART_IER_THRI)	/* Disable Transmitter holding रेजिस्टर empty पूर्णांकerrupt */
		    ;
	पूर्ण अन्यथा अगर (uart->adaptor == SNDRV_SERIAL_MS124W_SA) अणु
		byte = UART_IER_RDI	/* Enable Receiver data पूर्णांकerrupt */
		    | UART_IER_MSI	/* Enable Modem status पूर्णांकerrupt */
		    ;
	पूर्ण अन्यथा अगर (uart->adaptor == SNDRV_SERIAL_GENERIC) अणु
		byte = UART_IER_RDI	/* Enable Receiver data पूर्णांकerrupt */
		    | UART_IER_MSI	/* Enable Modem status पूर्णांकerrupt */
		    | UART_IER_THRI	/* Enable Transmitter holding रेजिस्टर empty पूर्णांकerrupt */
		    ;
	पूर्ण अन्यथा अणु
		byte = UART_IER_RDI	/* Enable Receiver data पूर्णांकerrupt */
		    | UART_IER_THRI	/* Enable Transmitter holding रेजिस्टर empty पूर्णांकerrupt */
		    ;
	पूर्ण
	outb(byte, uart->base + UART_IER);	/* Interrupt enable Register */

	inb(uart->base + UART_LSR);	/* Clear any pre-existing overrun indication */
	inb(uart->base + UART_IIR);	/* Clear any pre-existing transmit पूर्णांकerrupt */
	inb(uart->base + UART_RX);	/* Clear any pre-existing receive पूर्णांकerrupt */
पूर्ण

अटल व्योम snd_uart16550_करो_बंद(काष्ठा snd_uart16550 * uart)
अणु
	अगर (uart->irq < 0)
		snd_uart16550_del_समयr(uart);

	/* NOTE: may need to disable पूर्णांकerrupts beक्रमe de-रेजिस्टरing out handler.
	 * For now, the consequences are harmless.
	 */

	outb((0 & UART_IER_RDI)		/* Disable Receiver data पूर्णांकerrupt */
	     |(0 & UART_IER_THRI)	/* Disable Transmitter holding रेजिस्टर empty पूर्णांकerrupt */
	     ,uart->base + UART_IER);	/* Interrupt enable Register */

	चयन (uart->adaptor) अणु
	शेष:
		outb((0 & UART_MCR_RTS)		/* Deactivate Request-To-Send line  */
		     |(0 & UART_MCR_DTR)	/* Deactivate Data-Terminal-Ready line */
		     |(0 & UART_MCR_OUT2)	/* Deactivate OUT2 */
		     ,uart->base + UART_MCR);	/* Modem Control Register */
	  अवरोध;
	हाल SNDRV_SERIAL_MS124W_SA:
	हाल SNDRV_SERIAL_MS124W_MB:
		/* MS-124W can draw घातer from RTS and DTR अगर they
		   are in opposite states; leave it घातered. */ 
		outb(UART_MCR_RTS | (0&UART_MCR_DTR) | (0&UART_MCR_OUT2),
		     uart->base + UART_MCR);
		अवरोध;
	हाल SNDRV_SERIAL_MS124T:
		/* MS-124T can draw घातer from RTS and/or DTR (preferably
		   both) अगर they are both निश्चितed; leave it घातered. */
		outb(UART_MCR_RTS | UART_MCR_DTR | (0&UART_MCR_OUT2),
		     uart->base + UART_MCR);
		अवरोध;
	पूर्ण

	inb(uart->base + UART_IIR);	/* Clear any outstanding पूर्णांकerrupts */

	/* Restore old भागisor */
	अगर (uart->भागisor != 0) अणु
		outb(UART_LCR_DLAB		/* Divisor latch access bit */
		     ,uart->base + UART_LCR);	/* Line Control Register */
		outb(uart->old_भागisor_lsb
		     ,uart->base + UART_DLL);	/* Divisor Latch Low */
		outb(uart->old_भागisor_msb
		     ,uart->base + UART_DLM);	/* Divisor Latch High */
		/* Restore old LCR (data bits, stop bits, parity, DLAB) */
		outb(uart->old_line_ctrl_reg
		     ,uart->base + UART_LCR);	/* Line Control Register */
	पूर्ण
पूर्ण

अटल पूर्णांक snd_uart16550_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_uart16550 *uart = substream->rmidi->निजी_data;

	spin_lock_irqsave(&uart->खोलो_lock, flags);
	अगर (uart->filemode == SERIAL_MODE_NOT_OPENED)
		snd_uart16550_करो_खोलो(uart);
	uart->filemode |= SERIAL_MODE_INPUT_OPEN;
	uart->midi_input[substream->number] = substream;
	spin_unlock_irqrestore(&uart->खोलो_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_uart16550_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_uart16550 *uart = substream->rmidi->निजी_data;

	spin_lock_irqsave(&uart->खोलो_lock, flags);
	uart->filemode &= ~SERIAL_MODE_INPUT_OPEN;
	uart->midi_input[substream->number] = शून्य;
	अगर (uart->filemode == SERIAL_MODE_NOT_OPENED)
		snd_uart16550_करो_बंद(uart);
	spin_unlock_irqrestore(&uart->खोलो_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम snd_uart16550_input_trigger(काष्ठा snd_rawmidi_substream *substream,
					पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_uart16550 *uart = substream->rmidi->निजी_data;

	spin_lock_irqsave(&uart->खोलो_lock, flags);
	अगर (up)
		uart->filemode |= SERIAL_MODE_INPUT_TRIGGERED;
	अन्यथा
		uart->filemode &= ~SERIAL_MODE_INPUT_TRIGGERED;
	spin_unlock_irqrestore(&uart->खोलो_lock, flags);
पूर्ण

अटल पूर्णांक snd_uart16550_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_uart16550 *uart = substream->rmidi->निजी_data;

	spin_lock_irqsave(&uart->खोलो_lock, flags);
	अगर (uart->filemode == SERIAL_MODE_NOT_OPENED)
		snd_uart16550_करो_खोलो(uart);
	uart->filemode |= SERIAL_MODE_OUTPUT_OPEN;
	uart->midi_output[substream->number] = substream;
	spin_unlock_irqrestore(&uart->खोलो_lock, flags);
	वापस 0;
पूर्ण;

अटल पूर्णांक snd_uart16550_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_uart16550 *uart = substream->rmidi->निजी_data;

	spin_lock_irqsave(&uart->खोलो_lock, flags);
	uart->filemode &= ~SERIAL_MODE_OUTPUT_OPEN;
	uart->midi_output[substream->number] = शून्य;
	अगर (uart->filemode == SERIAL_MODE_NOT_OPENED)
		snd_uart16550_करो_बंद(uart);
	spin_unlock_irqrestore(&uart->खोलो_lock, flags);
	वापस 0;
पूर्ण;

अटल अंतरभूत पूर्णांक snd_uart16550_buffer_can_ग_लिखो(काष्ठा snd_uart16550 *uart,
						 पूर्णांक Num)
अणु
	अगर (uart->buff_in_count + Num < TX_BUFF_SIZE)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_uart16550_ग_लिखो_buffer(काष्ठा snd_uart16550 *uart,
					     अचिन्हित अक्षर byte)
अणु
	अचिन्हित लघु buff_in = uart->buff_in;
	अगर (uart->buff_in_count < TX_BUFF_SIZE) अणु
		uart->tx_buff[buff_in] = byte;
		buff_in++;
		buff_in &= TX_BUFF_MASK;
		uart->buff_in = buff_in;
		uart->buff_in_count++;
		अगर (uart->irq < 0) /* polling mode */
			snd_uart16550_add_समयr(uart);
		वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक snd_uart16550_output_byte(काष्ठा snd_uart16550 *uart,
				     काष्ठा snd_rawmidi_substream *substream,
				     अचिन्हित अक्षर midi_byte)
अणु
	अगर (uart->buff_in_count == 0                    /* Buffer empty? */
	    && ((uart->adaptor != SNDRV_SERIAL_MS124W_SA &&
	    uart->adaptor != SNDRV_SERIAL_GENERIC) ||
		(uart->fअगरo_count == 0                  /* FIFO empty? */
		 && (inb(uart->base + UART_MSR) & UART_MSR_CTS)))) अणु /* CTS? */

	        /* Tx Buffer Empty - try to ग_लिखो immediately */
		अगर ((inb(uart->base + UART_LSR) & UART_LSR_THRE) != 0) अणु
		        /* Transmitter holding रेजिस्टर (and Tx FIFO) empty */
		        uart->fअगरo_count = 1;
			outb(midi_byte, uart->base + UART_TX);
		पूर्ण अन्यथा अणु
		        अगर (uart->fअगरo_count < uart->fअगरo_limit) अणु
			        uart->fअगरo_count++;
				outb(midi_byte, uart->base + UART_TX);
			पूर्ण अन्यथा अणु
			        /* Cannot ग_लिखो (buffer empty) -
				 * put अक्षर in buffer */
				snd_uart16550_ग_लिखो_buffer(uart, midi_byte);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!snd_uart16550_ग_लिखो_buffer(uart, midi_byte)) अणु
			snd_prपूर्णांकk(KERN_WARNING
				   "%s: Buffer overrun on device at 0x%lx\n",
				   uart->rmidi->name, uart->base);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम snd_uart16550_output_ग_लिखो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर midi_byte, addr_byte;
	काष्ठा snd_uart16550 *uart = substream->rmidi->निजी_data;
	अक्षर first;
	अटल अचिन्हित दीर्घ lastसमय = 0;
	
	/* Interrupts are disabled during the updating of the tx_buff,
	 * since it is 'bad' to have two processes updating the same
	 * variables (ie buff_in & buff_out)
	 */

	spin_lock_irqsave(&uart->खोलो_lock, flags);

	अगर (uart->irq < 0)	/* polling */
		snd_uart16550_io_loop(uart);

	अगर (uart->adaptor == SNDRV_SERIAL_MS124W_MB) अणु
		जबतक (1) अणु
			/* buffer full? */
			/* in this mode we need two bytes of space */
			अगर (uart->buff_in_count > TX_BUFF_SIZE - 2)
				अवरोध;
			अगर (snd_rawmidi_transmit(substream, &midi_byte, 1) != 1)
				अवरोध;
#अगर_घोषित SNDRV_SERIAL_MS124W_MB_NOCOMBO
			/* select exactly one of the four ports */
			addr_byte = (1 << (substream->number + 4)) | 0x08;
#अन्यथा
			/* select any combination of the four ports */
			addr_byte = (substream->number << 4) | 0x08;
			/* ...except none */
			अगर (addr_byte == 0x08)
				addr_byte = 0xf8;
#पूर्ण_अगर
			snd_uart16550_output_byte(uart, substream, addr_byte);
			/* send midi byte */
			snd_uart16550_output_byte(uart, substream, midi_byte);
		पूर्ण
	पूर्ण अन्यथा अणु
		first = 0;
		जबतक (snd_rawmidi_transmit_peek(substream, &midi_byte, 1) == 1) अणु
			/* Also send F5 after 3 seconds with no data
			 * to handle device disconnect */
			अगर (first == 0 &&
			    (uart->adaptor == SNDRV_SERIAL_SOUNDCANVAS ||
			     uart->adaptor == SNDRV_SERIAL_GENERIC) &&
			    (uart->prev_out != substream->number ||
			     समय_after(jअगरfies, lastसमय + 3*HZ))) अणु

				अगर (snd_uart16550_buffer_can_ग_लिखो(uart, 3)) अणु
					/* Roland Soundcanvas part selection */
					/* If this substream of the data is
					 * dअगरferent previous substream
					 * in this uart, send the change part
					 * event
					 */
					uart->prev_out = substream->number;
					/* change part */
					snd_uart16550_output_byte(uart, substream,
								  0xf5);
					/* data */
					snd_uart16550_output_byte(uart, substream,
								  uart->prev_out + 1);
					/* If midi_byte is a data byte,
					 * send the previous status byte */
					अगर (midi_byte < 0x80 &&
					    uart->adaptor == SNDRV_SERIAL_SOUNDCANVAS)
						snd_uart16550_output_byte(uart, substream, uart->prev_status[uart->prev_out]);
				पूर्ण अन्यथा अगर (!uart->drop_on_full)
					अवरोध;

			पूर्ण

			/* send midi byte */
			अगर (!snd_uart16550_output_byte(uart, substream, midi_byte) &&
			    !uart->drop_on_full )
				अवरोध;

			अगर (midi_byte >= 0x80 && midi_byte < 0xf0)
				uart->prev_status[uart->prev_out] = midi_byte;
			first = 1;

			snd_rawmidi_transmit_ack( substream, 1 );
		पूर्ण
		lastसमय = jअगरfies;
	पूर्ण
	spin_unlock_irqrestore(&uart->खोलो_lock, flags);
पूर्ण

अटल व्योम snd_uart16550_output_trigger(काष्ठा snd_rawmidi_substream *substream,
					 पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_uart16550 *uart = substream->rmidi->निजी_data;

	spin_lock_irqsave(&uart->खोलो_lock, flags);
	अगर (up)
		uart->filemode |= SERIAL_MODE_OUTPUT_TRIGGERED;
	अन्यथा
		uart->filemode &= ~SERIAL_MODE_OUTPUT_TRIGGERED;
	spin_unlock_irqrestore(&uart->खोलो_lock, flags);
	अगर (up)
		snd_uart16550_output_ग_लिखो(substream);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_uart16550_output =
अणु
	.खोलो =		snd_uart16550_output_खोलो,
	.बंद =	snd_uart16550_output_बंद,
	.trigger =	snd_uart16550_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_uart16550_input =
अणु
	.खोलो =		snd_uart16550_input_खोलो,
	.बंद =	snd_uart16550_input_बंद,
	.trigger =	snd_uart16550_input_trigger,
पूर्ण;

अटल पूर्णांक snd_uart16550_मुक्त(काष्ठा snd_uart16550 *uart)
अणु
	अगर (uart->irq >= 0)
		मुक्त_irq(uart->irq, uart);
	release_and_मुक्त_resource(uart->res_base);
	kमुक्त(uart);
	वापस 0;
पूर्ण;

अटल पूर्णांक snd_uart16550_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_uart16550 *uart = device->device_data;
	वापस snd_uart16550_मुक्त(uart);
पूर्ण

अटल पूर्णांक snd_uart16550_create(काष्ठा snd_card *card,
				अचिन्हित दीर्घ iobase,
				पूर्णांक irq,
				अचिन्हित पूर्णांक speed,
				अचिन्हित पूर्णांक base,
				पूर्णांक adaptor,
				पूर्णांक droponfull,
				काष्ठा snd_uart16550 **ruart)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_uart16550_dev_मुक्त,
	पूर्ण;
	काष्ठा snd_uart16550 *uart;
	पूर्णांक err;


	अगर ((uart = kzalloc(माप(*uart), GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;
	uart->adaptor = adaptor;
	uart->card = card;
	spin_lock_init(&uart->खोलो_lock);
	uart->irq = -1;
	uart->base = iobase;
	uart->drop_on_full = droponfull;

	अगर ((err = snd_uart16550_detect(uart)) <= 0) अणु
		prपूर्णांकk(KERN_ERR "no UART detected at 0x%lx\n", iobase);
		snd_uart16550_मुक्त(uart);
		वापस -ENODEV;
	पूर्ण

	अगर (irq >= 0 && irq != SNDRV_AUTO_IRQ) अणु
		अगर (request_irq(irq, snd_uart16550_पूर्णांकerrupt,
				0, "Serial MIDI", uart)) अणु
			snd_prपूर्णांकk(KERN_WARNING
				   "irq %d busy. Using Polling.\n", irq);
		पूर्ण अन्यथा अणु
			uart->irq = irq;
		पूर्ण
	पूर्ण
	uart->भागisor = base / speed;
	uart->speed = base / (अचिन्हित पूर्णांक)uart->भागisor;
	uart->speed_base = base;
	uart->prev_out = -1;
	uart->prev_in = 0;
	uart->rstatus = 0;
	स_रखो(uart->prev_status, 0x80, माप(अचिन्हित अक्षर) * SNDRV_SERIAL_MAX_OUTS);
	समयr_setup(&uart->buffer_समयr, snd_uart16550_buffer_समयr, 0);
	uart->समयr_running = 0;

	/* Register device */
	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, uart, &ops)) < 0) अणु
		snd_uart16550_मुक्त(uart);
		वापस err;
	पूर्ण

	चयन (uart->adaptor) अणु
	हाल SNDRV_SERIAL_MS124W_SA:
	हाल SNDRV_SERIAL_MS124W_MB:
		/* MS-124W can draw घातer from RTS and DTR अगर they
		   are in opposite states. */ 
		outb(UART_MCR_RTS | (0&UART_MCR_DTR), uart->base + UART_MCR);
		अवरोध;
	हाल SNDRV_SERIAL_MS124T:
		/* MS-124T can draw घातer from RTS and/or DTR (preferably
		   both) अगर they are निश्चितed. */
		outb(UART_MCR_RTS | UART_MCR_DTR, uart->base + UART_MCR);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ruart)
		*ruart = uart;

	वापस 0;
पूर्ण

अटल व्योम snd_uart16550_substreams(काष्ठा snd_rawmidi_str *stream)
अणु
	काष्ठा snd_rawmidi_substream *substream;

	list_क्रम_each_entry(substream, &stream->substreams, list) अणु
		प्र_लिखो(substream->name, "Serial MIDI %d", substream->number + 1);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_uart16550_rmidi(काष्ठा snd_uart16550 *uart, पूर्णांक device,
			       पूर्णांक outs, पूर्णांक ins,
			       काष्ठा snd_rawmidi **rmidi)
अणु
	काष्ठा snd_rawmidi *rrawmidi;
	पूर्णांक err;

	err = snd_rawmidi_new(uart->card, "UART Serial MIDI", device,
			      outs, ins, &rrawmidi);
	अगर (err < 0)
		वापस err;
	snd_rawmidi_set_ops(rrawmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &snd_uart16550_input);
	snd_rawmidi_set_ops(rrawmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &snd_uart16550_output);
	म_नकल(rrawmidi->name, "Serial MIDI");
	snd_uart16550_substreams(&rrawmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT]);
	snd_uart16550_substreams(&rrawmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT]);
	rrawmidi->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
			       SNDRV_RAWMIDI_INFO_INPUT |
			       SNDRV_RAWMIDI_INFO_DUPLEX;
	rrawmidi->निजी_data = uart;
	अगर (rmidi)
		*rmidi = rrawmidi;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_serial_probe(काष्ठा platक्रमm_device *devptr)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_uart16550 *uart;
	पूर्णांक err;
	पूर्णांक dev = devptr->id;

	चयन (adaptor[dev]) अणु
	हाल SNDRV_SERIAL_SOUNDCANVAS:
		ins[dev] = 1;
		अवरोध;
	हाल SNDRV_SERIAL_MS124T:
	हाल SNDRV_SERIAL_MS124W_SA:
		outs[dev] = 1;
		ins[dev] = 1;
		अवरोध;
	हाल SNDRV_SERIAL_MS124W_MB:
		outs[dev] = 16;
		ins[dev] = 1;
		अवरोध;
	हाल SNDRV_SERIAL_GENERIC:
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_ERR
			   "Adaptor type is out of range 0-%d (%d)\n",
			   SNDRV_SERIAL_MAX_ADAPTOR, adaptor[dev]);
		वापस -ENODEV;
	पूर्ण

	अगर (outs[dev] < 1 || outs[dev] > SNDRV_SERIAL_MAX_OUTS) अणु
		snd_prपूर्णांकk(KERN_ERR
			   "Count of outputs is out of range 1-%d (%d)\n",
			   SNDRV_SERIAL_MAX_OUTS, outs[dev]);
		वापस -ENODEV;
	पूर्ण

	अगर (ins[dev] < 1 || ins[dev] > SNDRV_SERIAL_MAX_INS) अणु
		snd_prपूर्णांकk(KERN_ERR
			   "Count of inputs is out of range 1-%d (%d)\n",
			   SNDRV_SERIAL_MAX_INS, ins[dev]);
		वापस -ENODEV;
	पूर्ण

	err  = snd_card_new(&devptr->dev, index[dev], id[dev], THIS_MODULE,
			    0, &card);
	अगर (err < 0)
		वापस err;

	म_नकल(card->driver, "Serial");
	म_नकल(card->लघुname, "Serial MIDI (UART16550A)");

	अगर ((err = snd_uart16550_create(card,
					port[dev],
					irq[dev],
					speed[dev],
					base[dev],
					adaptor[dev],
					droponfull[dev],
					&uart)) < 0)
		जाओ _err;

	err = snd_uart16550_rmidi(uart, 0, outs[dev], ins[dev], &uart->rmidi);
	अगर (err < 0)
		जाओ _err;

	प्र_लिखो(card->दीर्घname, "%s [%s] at %#lx, irq %d",
		card->लघुname,
		adaptor_names[uart->adaptor],
		uart->base,
		uart->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0)
		जाओ _err;

	platक्रमm_set_drvdata(devptr, card);
	वापस 0;

 _err:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_serial_हटाओ(काष्ठा platक्रमm_device *devptr)
अणु
	snd_card_मुक्त(platक्रमm_get_drvdata(devptr));
	वापस 0;
पूर्ण

#घोषणा SND_SERIAL_DRIVER	"snd_serial_u16550"

अटल काष्ठा platक्रमm_driver snd_serial_driver = अणु
	.probe		= snd_serial_probe,
	.हटाओ		=  snd_serial_हटाओ,
	.driver		= अणु
		.name	= SND_SERIAL_DRIVER,
	पूर्ण,
पूर्ण;

अटल व्योम snd_serial_unरेजिस्टर_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(devices); ++i)
		platक्रमm_device_unरेजिस्टर(devices[i]);
	platक्रमm_driver_unरेजिस्टर(&snd_serial_driver);
पूर्ण

अटल पूर्णांक __init alsa_card_serial_init(व्योम)
अणु
	पूर्णांक i, cards, err;

	अगर ((err = platक्रमm_driver_रेजिस्टर(&snd_serial_driver)) < 0)
		वापस err;

	cards = 0;
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		काष्ठा platक्रमm_device *device;
		अगर (! enable[i])
			जारी;
		device = platक्रमm_device_रेजिस्टर_simple(SND_SERIAL_DRIVER,
							 i, शून्य, 0);
		अगर (IS_ERR(device))
			जारी;
		अगर (!platक्रमm_get_drvdata(device)) अणु
			platक्रमm_device_unरेजिस्टर(device);
			जारी;
		पूर्ण
		devices[i] = device;
		cards++;
	पूर्ण
	अगर (! cards) अणु
#अगर_घोषित MODULE
		prपूर्णांकk(KERN_ERR "serial midi soundcard not found or device busy\n");
#पूर्ण_अगर
		snd_serial_unरेजिस्टर_all();
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_card_serial_निकास(व्योम)
अणु
	snd_serial_unरेजिस्टर_all();
पूर्ण

module_init(alsa_card_serial_init)
module_निकास(alsa_card_serial_निकास)
