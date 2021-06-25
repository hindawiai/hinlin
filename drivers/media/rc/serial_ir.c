<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * serial_ir.c
 *
 * serial_ir - Device driver that records pulse- and छोड़ो-lengths
 *	       (space-lengths) between DDCD event on a serial port.
 *
 * Copyright (C) 1996,97 Ralph Metzler <rjkm@thp.uni-koeln.de>
 * Copyright (C) 1998 Trent Piepho <xyzzy@u.washington.edu>
 * Copyright (C) 1998 Ben Pfaff <blp@gnu.org>
 * Copyright (C) 1999 Christoph Bartelmus <lirc@bartelmus.de>
 * Copyright (C) 2007 Andrei Tanas <andrei@tanas.ca> (suspend/resume support)
 * Copyright (C) 2016 Sean Young <sean@mess.org> (port to rc-core)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <media/rc-core.h>

काष्ठा serial_ir_hw अणु
	पूर्णांक संकेत_pin;
	पूर्णांक संकेत_pin_change;
	u8 on;
	u8 off;
	अचिन्हित set_send_carrier:1;
	अचिन्हित set_duty_cycle:1;
	व्योम (*send_pulse)(अचिन्हित पूर्णांक length, kसमय_प्रकार edge);
	व्योम (*send_space)(व्योम);
	spinlock_t lock;
पूर्ण;

#घोषणा IR_HOMEBREW	0
#घोषणा IR_IRDEO	1
#घोषणा IR_IRDEO_REMOTE	2
#घोषणा IR_ANIMAX	3
#घोषणा IR_IGOR		4

/* module parameters */
अटल पूर्णांक type;
अटल पूर्णांक io;
अटल पूर्णांक irq;
अटल uदीर्घ iommap;
अटल पूर्णांक ioshअगरt;
अटल bool softcarrier = true;
अटल bool share_irq;
अटल पूर्णांक sense = -1;	/* -1 = स्वतः, 0 = active high, 1 = active low */
अटल bool txsense;	/* 0 = active high, 1 = active low */

/* क्रमward declarations */
अटल व्योम send_pulse_irdeo(अचिन्हित पूर्णांक length, kसमय_प्रकार edge);
अटल व्योम send_space_irdeo(व्योम);
#अगर_घोषित CONFIG_IR_SERIAL_TRANSMITTER
अटल व्योम send_pulse_homebrew(अचिन्हित पूर्णांक length, kसमय_प्रकार edge);
अटल व्योम send_space_homebrew(व्योम);
#पूर्ण_अगर

अटल काष्ठा serial_ir_hw hardware[] = अणु
	[IR_HOMEBREW] = अणु
		.lock = __SPIN_LOCK_UNLOCKED(hardware[IR_HOMEBREW].lock),
		.संकेत_pin	   = UART_MSR_DCD,
		.संकेत_pin_change = UART_MSR_DDCD,
		.on  = (UART_MCR_RTS | UART_MCR_OUT2 | UART_MCR_DTR),
		.off = (UART_MCR_RTS | UART_MCR_OUT2),
#अगर_घोषित CONFIG_IR_SERIAL_TRANSMITTER
		.send_pulse = send_pulse_homebrew,
		.send_space = send_space_homebrew,
		.set_send_carrier = true,
		.set_duty_cycle = true,
#पूर्ण_अगर
	पूर्ण,

	[IR_IRDEO] = अणु
		.lock = __SPIN_LOCK_UNLOCKED(hardware[IR_IRDEO].lock),
		.संकेत_pin	   = UART_MSR_DSR,
		.संकेत_pin_change = UART_MSR_DDSR,
		.on  = UART_MCR_OUT2,
		.off = (UART_MCR_RTS | UART_MCR_DTR | UART_MCR_OUT2),
		.send_pulse = send_pulse_irdeo,
		.send_space = send_space_irdeo,
		.set_duty_cycle = true,
	पूर्ण,

	[IR_IRDEO_REMOTE] = अणु
		.lock = __SPIN_LOCK_UNLOCKED(hardware[IR_IRDEO_REMOTE].lock),
		.संकेत_pin	   = UART_MSR_DSR,
		.संकेत_pin_change = UART_MSR_DDSR,
		.on  = (UART_MCR_RTS | UART_MCR_DTR | UART_MCR_OUT2),
		.off = (UART_MCR_RTS | UART_MCR_DTR | UART_MCR_OUT2),
		.send_pulse = send_pulse_irdeo,
		.send_space = send_space_irdeo,
		.set_duty_cycle = true,
	पूर्ण,

	[IR_ANIMAX] = अणु
		.lock = __SPIN_LOCK_UNLOCKED(hardware[IR_ANIMAX].lock),
		.संकेत_pin	   = UART_MSR_DCD,
		.संकेत_pin_change = UART_MSR_DDCD,
		.on  = 0,
		.off = (UART_MCR_RTS | UART_MCR_DTR | UART_MCR_OUT2),
	पूर्ण,

	[IR_IGOR] = अणु
		.lock = __SPIN_LOCK_UNLOCKED(hardware[IR_IGOR].lock),
		.संकेत_pin	   = UART_MSR_DSR,
		.संकेत_pin_change = UART_MSR_DDSR,
		.on  = (UART_MCR_RTS | UART_MCR_OUT2 | UART_MCR_DTR),
		.off = (UART_MCR_RTS | UART_MCR_OUT2),
#अगर_घोषित CONFIG_IR_SERIAL_TRANSMITTER
		.send_pulse = send_pulse_homebrew,
		.send_space = send_space_homebrew,
		.set_send_carrier = true,
		.set_duty_cycle = true,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

#घोषणा RS_ISR_PASS_LIMIT 256

काष्ठा serial_ir अणु
	kसमय_प्रकार lastkt;
	काष्ठा rc_dev *rcdev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा समयr_list समयout_समयr;

	अचिन्हित पूर्णांक carrier;
	अचिन्हित पूर्णांक duty_cycle;
पूर्ण;

अटल काष्ठा serial_ir serial_ir;

/* fetch serial input packet (1 byte) from रेजिस्टर offset */
अटल u8 sinp(पूर्णांक offset)
अणु
	अगर (iommap)
		/* the रेजिस्टर is memory-mapped */
		offset <<= ioshअगरt;

	वापस inb(io + offset);
पूर्ण

/* ग_लिखो serial output packet (1 byte) of value to रेजिस्टर offset */
अटल व्योम soutp(पूर्णांक offset, u8 value)
अणु
	अगर (iommap)
		/* the रेजिस्टर is memory-mapped */
		offset <<= ioshअगरt;

	outb(value, io + offset);
पूर्ण

अटल व्योम on(व्योम)
अणु
	अगर (txsense)
		soutp(UART_MCR, hardware[type].off);
	अन्यथा
		soutp(UART_MCR, hardware[type].on);
पूर्ण

अटल व्योम off(व्योम)
अणु
	अगर (txsense)
		soutp(UART_MCR, hardware[type].on);
	अन्यथा
		soutp(UART_MCR, hardware[type].off);
पूर्ण

अटल व्योम send_pulse_irdeo(अचिन्हित पूर्णांक length, kसमय_प्रकार target)
अणु
	दीर्घ rawbits;
	पूर्णांक i;
	अचिन्हित अक्षर output;
	अचिन्हित अक्षर chunk, shअगरted;

	/* how many bits have to be sent ? */
	rawbits = length * 1152 / 10000;
	अगर (serial_ir.duty_cycle > 50)
		chunk = 3;
	अन्यथा
		chunk = 1;
	क्रम (i = 0, output = 0x7f; rawbits > 0; rawbits -= 3) अणु
		shअगरted = chunk << (i * 3);
		shअगरted >>= 1;
		output &= (~shअगरted);
		i++;
		अगर (i == 3) अणु
			soutp(UART_TX, output);
			जबतक (!(sinp(UART_LSR) & UART_LSR_THRE))
				;
			output = 0x7f;
			i = 0;
		पूर्ण
	पूर्ण
	अगर (i != 0) अणु
		soutp(UART_TX, output);
		जबतक (!(sinp(UART_LSR) & UART_LSR_TEMT))
			;
	पूर्ण
पूर्ण

अटल व्योम send_space_irdeo(व्योम)
अणु
पूर्ण

#अगर_घोषित CONFIG_IR_SERIAL_TRANSMITTER
अटल व्योम send_pulse_homebrew_softcarrier(अचिन्हित पूर्णांक length, kसमय_प्रकार edge)
अणु
	kसमय_प्रकार now, target = kसमय_add_us(edge, length);
	/*
	 * delta should never exceed 4 seconds and on m68k
	 * ndelay(s64) करोes not compile; so use s32 rather than s64.
	 */
	s32 delta;
	अचिन्हित पूर्णांक pulse, space;

	/* Ensure the भागidend fits पूर्णांकo 32 bit */
	pulse = DIV_ROUND_CLOSEST(serial_ir.duty_cycle * (NSEC_PER_SEC / 100),
				  serial_ir.carrier);
	space = DIV_ROUND_CLOSEST((100 - serial_ir.duty_cycle) *
				  (NSEC_PER_SEC / 100), serial_ir.carrier);

	क्रम (;;) अणु
		now = kसमय_get();
		अगर (kसमय_compare(now, target) >= 0)
			अवरोध;
		on();
		edge = kसमय_add_ns(edge, pulse);
		delta = kसमय_प्रकारo_ns(kसमय_sub(edge, now));
		अगर (delta > 0)
			ndelay(delta);
		now = kसमय_get();
		off();
		अगर (kसमय_compare(now, target) >= 0)
			अवरोध;
		edge = kसमय_add_ns(edge, space);
		delta = kसमय_प्रकारo_ns(kसमय_sub(edge, now));
		अगर (delta > 0)
			ndelay(delta);
	पूर्ण
पूर्ण

अटल व्योम send_pulse_homebrew(अचिन्हित पूर्णांक length, kसमय_प्रकार edge)
अणु
	अगर (softcarrier)
		send_pulse_homebrew_softcarrier(length, edge);
	अन्यथा
		on();
पूर्ण

अटल व्योम send_space_homebrew(व्योम)
अणु
	off();
पूर्ण
#पूर्ण_अगर

अटल व्योम frbग_लिखो(अचिन्हित पूर्णांक l, bool is_pulse)
अणु
	/* simple noise filter */
	अटल अचिन्हित पूर्णांक ptr, pulse, space;
	काष्ठा ir_raw_event ev = अणुपूर्ण;

	अगर (ptr > 0 && is_pulse) अणु
		pulse += l;
		अगर (pulse > 250) अणु
			ev.duration = space;
			ev.pulse = false;
			ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
			ev.duration = pulse;
			ev.pulse = true;
			ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
			ptr = 0;
			pulse = 0;
		पूर्ण
		वापस;
	पूर्ण
	अगर (!is_pulse) अणु
		अगर (ptr == 0) अणु
			अगर (l > 20000) अणु
				space = l;
				ptr++;
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (l > 20000) अणु
				space += pulse;
				अगर (space > IR_MAX_DURATION)
					space = IR_MAX_DURATION;
				space += l;
				अगर (space > IR_MAX_DURATION)
					space = IR_MAX_DURATION;
				pulse = 0;
				वापस;
			पूर्ण

			ev.duration = space;
			ev.pulse = false;
			ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
			ev.duration = pulse;
			ev.pulse = true;
			ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
			ptr = 0;
			pulse = 0;
		पूर्ण
	पूर्ण

	ev.duration = l;
	ev.pulse = is_pulse;
	ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
पूर्ण

अटल irqवापस_t serial_ir_irq_handler(पूर्णांक i, व्योम *blah)
अणु
	kसमय_प्रकार kt;
	पूर्णांक counter, dcd;
	u8 status;
	kसमय_प्रकार delkt;
	अचिन्हित पूर्णांक data;
	अटल पूर्णांक last_dcd = -1;

	अगर ((sinp(UART_IIR) & UART_IIR_NO_INT)) अणु
		/* not our पूर्णांकerrupt */
		वापस IRQ_NONE;
	पूर्ण

	counter = 0;
	करो अणु
		counter++;
		status = sinp(UART_MSR);
		अगर (counter > RS_ISR_PASS_LIMIT) अणु
			dev_err(&serial_ir.pdev->dev, "Trapped in interrupt");
			अवरोध;
		पूर्ण
		अगर ((status & hardware[type].संकेत_pin_change) &&
		    sense != -1) अणु
			/* get current समय */
			kt = kसमय_get();

			/*
			 * The driver needs to know अगर your receiver is
			 * active high or active low, or the space/pulse
			 * sense could be inverted.
			 */

			/* calc समय since last पूर्णांकerrupt in nanoseconds */
			dcd = (status & hardware[type].संकेत_pin) ? 1 : 0;

			अगर (dcd == last_dcd) अणु
				dev_dbg(&serial_ir.pdev->dev,
					"ignoring spike: %d %d %lldns %lldns\n",
					dcd, sense, kसमय_प्रकारo_ns(kt),
					kसमय_प्रकारo_ns(serial_ir.lastkt));
				जारी;
			पूर्ण

			delkt = kसमय_sub(kt, serial_ir.lastkt);
			अगर (kसमय_compare(delkt, kसमय_set(15, 0)) > 0) अणु
				data = IR_MAX_DURATION; /* really दीर्घ समय */
				अगर (!(dcd ^ sense)) अणु
					/* sanity check */
					dev_err(&serial_ir.pdev->dev,
						"dcd unexpected: %d %d %lldns %lldns\n",
						dcd, sense, kसमय_प्रकारo_ns(kt),
						kसमय_प्रकारo_ns(serial_ir.lastkt));
					/*
					 * detecting pulse जबतक this
					 * MUST be a space!
					 */
					sense = sense ? 0 : 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				data = kसमय_प्रकारo_us(delkt);
			पूर्ण
			frbग_लिखो(data, !(dcd ^ sense));
			serial_ir.lastkt = kt;
			last_dcd = dcd;
		पूर्ण
	पूर्ण जबतक (!(sinp(UART_IIR) & UART_IIR_NO_INT)); /* still pending ? */

	mod_समयr(&serial_ir.समयout_समयr,
		  jअगरfies + usecs_to_jअगरfies(serial_ir.rcdev->समयout));

	ir_raw_event_handle(serial_ir.rcdev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hardware_init_port(व्योम)
अणु
	u8 scratch, scratch2, scratch3;

	/*
	 * This is a simple port existence test, borrowed from the स्वतःconfig
	 * function in drivers/tty/serial/8250/8250_port.c
	 */
	scratch = sinp(UART_IER);
	soutp(UART_IER, 0);
#अगर_घोषित __i386__
	outb(0xff, 0x080);
#पूर्ण_अगर
	scratch2 = sinp(UART_IER) & 0x0f;
	soutp(UART_IER, 0x0f);
#अगर_घोषित __i386__
	outb(0x00, 0x080);
#पूर्ण_अगर
	scratch3 = sinp(UART_IER) & 0x0f;
	soutp(UART_IER, scratch);
	अगर (scratch2 != 0 || scratch3 != 0x0f) अणु
		/* we fail, there's nothing here */
		pr_err("port existence test failed, cannot continue\n");
		वापस -ENODEV;
	पूर्ण

	/* Set DLAB 0. */
	soutp(UART_LCR, sinp(UART_LCR) & (~UART_LCR_DLAB));

	/* First of all, disable all पूर्णांकerrupts */
	soutp(UART_IER, sinp(UART_IER) &
	      (~(UART_IER_MSI | UART_IER_RLSI | UART_IER_THRI | UART_IER_RDI)));

	/* Clear रेजिस्टरs. */
	sinp(UART_LSR);
	sinp(UART_RX);
	sinp(UART_IIR);
	sinp(UART_MSR);

	/* Set line क्रम घातer source */
	off();

	/* Clear रेजिस्टरs again to be sure. */
	sinp(UART_LSR);
	sinp(UART_RX);
	sinp(UART_IIR);
	sinp(UART_MSR);

	चयन (type) अणु
	हाल IR_IRDEO:
	हाल IR_IRDEO_REMOTE:
		/* setup port to 7N1 @ 115200 Baud */
		/* 7N1+start = 9 bits at 115200 ~ 3 bits at 38kHz */

		/* Set DLAB 1. */
		soutp(UART_LCR, sinp(UART_LCR) | UART_LCR_DLAB);
		/* Set भागisor to 1 => 115200 Baud */
		soutp(UART_DLM, 0);
		soutp(UART_DLL, 1);
		/* Set DLAB 0 +  7N1 */
		soutp(UART_LCR, UART_LCR_WLEN7);
		/* THR पूर्णांकerrupt alपढ़ोy disabled at this poपूर्णांक */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम serial_ir_समयout(काष्ठा समयr_list *unused)
अणु
	काष्ठा ir_raw_event ev = अणु
		.समयout = true,
		.duration = serial_ir.rcdev->समयout
	पूर्ण;
	ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
	ir_raw_event_handle(serial_ir.rcdev);
पूर्ण

/* Needed by serial_ir_probe() */
अटल पूर्णांक serial_ir_tx(काष्ठा rc_dev *dev, अचिन्हित पूर्णांक *txbuf,
			अचिन्हित पूर्णांक count);
अटल पूर्णांक serial_ir_tx_duty_cycle(काष्ठा rc_dev *dev, u32 cycle);
अटल पूर्णांक serial_ir_tx_carrier(काष्ठा rc_dev *dev, u32 carrier);
अटल पूर्णांक serial_ir_खोलो(काष्ठा rc_dev *rcdev);
अटल व्योम serial_ir_बंद(काष्ठा rc_dev *rcdev);

अटल पूर्णांक serial_ir_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा rc_dev *rcdev;
	पूर्णांक i, nlow, nhigh, result;

	rcdev = devm_rc_allocate_device(&dev->dev, RC_DRIVER_IR_RAW);
	अगर (!rcdev)
		वापस -ENOMEM;

	अगर (hardware[type].send_pulse && hardware[type].send_space)
		rcdev->tx_ir = serial_ir_tx;
	अगर (hardware[type].set_send_carrier)
		rcdev->s_tx_carrier = serial_ir_tx_carrier;
	अगर (hardware[type].set_duty_cycle)
		rcdev->s_tx_duty_cycle = serial_ir_tx_duty_cycle;

	चयन (type) अणु
	हाल IR_HOMEBREW:
		rcdev->device_name = "Serial IR type home-brew";
		अवरोध;
	हाल IR_IRDEO:
		rcdev->device_name = "Serial IR type IRdeo";
		अवरोध;
	हाल IR_IRDEO_REMOTE:
		rcdev->device_name = "Serial IR type IRdeo remote";
		अवरोध;
	हाल IR_ANIMAX:
		rcdev->device_name = "Serial IR type AnimaX";
		अवरोध;
	हाल IR_IGOR:
		rcdev->device_name = "Serial IR type IgorPlug";
		अवरोध;
	पूर्ण

	rcdev->input_phys = KBUILD_MODNAME "/input0";
	rcdev->input_id.bustype = BUS_HOST;
	rcdev->input_id.venकरोr = 0x0001;
	rcdev->input_id.product = 0x0001;
	rcdev->input_id.version = 0x0100;
	rcdev->खोलो = serial_ir_खोलो;
	rcdev->बंद = serial_ir_बंद;
	rcdev->dev.parent = &serial_ir.pdev->dev;
	rcdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rcdev->driver_name = KBUILD_MODNAME;
	rcdev->map_name = RC_MAP_RC6_MCE;
	rcdev->min_समयout = 1;
	rcdev->समयout = IR_DEFAULT_TIMEOUT;
	rcdev->max_समयout = 10 * IR_DEFAULT_TIMEOUT;
	rcdev->rx_resolution = 250;

	serial_ir.rcdev = rcdev;

	समयr_setup(&serial_ir.समयout_समयr, serial_ir_समयout, 0);

	result = devm_request_irq(&dev->dev, irq, serial_ir_irq_handler,
				  share_irq ? IRQF_SHARED : 0,
				  KBUILD_MODNAME, &hardware);
	अगर (result < 0) अणु
		अगर (result == -EBUSY)
			dev_err(&dev->dev, "IRQ %d busy\n", irq);
		अन्यथा अगर (result == -EINVAL)
			dev_err(&dev->dev, "Bad irq number or handler\n");
		वापस result;
	पूर्ण

	/* Reserve io region. */
	अगर ((iommap &&
	     (devm_request_mem_region(&dev->dev, iommap, 8UL << ioshअगरt,
				      KBUILD_MODNAME) == शून्य)) ||
	     (!iommap && (devm_request_region(&dev->dev, io, 8,
			  KBUILD_MODNAME) == शून्य))) अणु
		dev_err(&dev->dev, "port %04x already in use\n", io);
		dev_warn(&dev->dev, "use 'setserial /dev/ttySX uart none'\n");
		dev_warn(&dev->dev,
			 "or compile the serial port driver as module and\n");
		dev_warn(&dev->dev, "make sure this module is loaded first\n");
		वापस -EBUSY;
	पूर्ण

	result = hardware_init_port();
	अगर (result < 0)
		वापस result;

	/* Initialize pulse/space widths */
	serial_ir.duty_cycle = 50;
	serial_ir.carrier = 38000;

	/* If pin is high, then this must be an active low receiver. */
	अगर (sense == -1) अणु
		/* रुको 1/2 sec क्रम the घातer supply */
		msleep(500);

		/*
		 * probe 9 बार every 0.04s, collect "votes" क्रम
		 * active high/low
		 */
		nlow = 0;
		nhigh = 0;
		क्रम (i = 0; i < 9; i++) अणु
			अगर (sinp(UART_MSR) & hardware[type].संकेत_pin)
				nlow++;
			अन्यथा
				nhigh++;
			msleep(40);
		पूर्ण
		sense = nlow >= nhigh ? 1 : 0;
		dev_info(&dev->dev, "auto-detected active %s receiver\n",
			 sense ? "low" : "high");
	पूर्ण अन्यथा
		dev_info(&dev->dev, "Manually using active %s receiver\n",
			 sense ? "low" : "high");

	dev_dbg(&dev->dev, "Interrupt %d, port %04x obtained\n", irq, io);

	वापस devm_rc_रेजिस्टर_device(&dev->dev, rcdev);
पूर्ण

अटल पूर्णांक serial_ir_खोलो(काष्ठा rc_dev *rcdev)
अणु
	अचिन्हित दीर्घ flags;

	/* initialize बारtamp */
	serial_ir.lastkt = kसमय_get();

	spin_lock_irqsave(&hardware[type].lock, flags);

	/* Set DLAB 0. */
	soutp(UART_LCR, sinp(UART_LCR) & (~UART_LCR_DLAB));

	soutp(UART_IER, sinp(UART_IER) | UART_IER_MSI);

	spin_unlock_irqrestore(&hardware[type].lock, flags);

	वापस 0;
पूर्ण

अटल व्योम serial_ir_बंद(काष्ठा rc_dev *rcdev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hardware[type].lock, flags);

	/* Set DLAB 0. */
	soutp(UART_LCR, sinp(UART_LCR) & (~UART_LCR_DLAB));

	/* First of all, disable all पूर्णांकerrupts */
	soutp(UART_IER, sinp(UART_IER) &
	      (~(UART_IER_MSI | UART_IER_RLSI | UART_IER_THRI | UART_IER_RDI)));
	spin_unlock_irqrestore(&hardware[type].lock, flags);
पूर्ण

अटल पूर्णांक serial_ir_tx(काष्ठा rc_dev *dev, अचिन्हित पूर्णांक *txbuf,
			अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार edge;
	s64 delta;
	पूर्णांक i;

	spin_lock_irqsave(&hardware[type].lock, flags);
	अगर (type == IR_IRDEO) अणु
		/* DTR, RTS करोwn */
		on();
	पूर्ण

	edge = kसमय_get();
	क्रम (i = 0; i < count; i++) अणु
		अगर (i % 2)
			hardware[type].send_space();
		अन्यथा
			hardware[type].send_pulse(txbuf[i], edge);

		edge = kसमय_add_us(edge, txbuf[i]);
		delta = kसमय_us_delta(edge, kसमय_get());
		अगर (delta > 25) अणु
			spin_unlock_irqrestore(&hardware[type].lock, flags);
			usleep_range(delta - 25, delta + 25);
			spin_lock_irqsave(&hardware[type].lock, flags);
		पूर्ण अन्यथा अगर (delta > 0) अणु
			udelay(delta);
		पूर्ण
	पूर्ण
	off();
	spin_unlock_irqrestore(&hardware[type].lock, flags);
	वापस count;
पूर्ण

अटल पूर्णांक serial_ir_tx_duty_cycle(काष्ठा rc_dev *dev, u32 cycle)
अणु
	serial_ir.duty_cycle = cycle;
	वापस 0;
पूर्ण

अटल पूर्णांक serial_ir_tx_carrier(काष्ठा rc_dev *dev, u32 carrier)
अणु
	अगर (carrier > 500000 || carrier < 20000)
		वापस -EINVAL;

	serial_ir.carrier = carrier;
	वापस 0;
पूर्ण

अटल पूर्णांक serial_ir_suspend(काष्ठा platक्रमm_device *dev,
			     pm_message_t state)
अणु
	/* Set DLAB 0. */
	soutp(UART_LCR, sinp(UART_LCR) & (~UART_LCR_DLAB));

	/* Disable all पूर्णांकerrupts */
	soutp(UART_IER, sinp(UART_IER) &
	      (~(UART_IER_MSI | UART_IER_RLSI | UART_IER_THRI | UART_IER_RDI)));

	/* Clear रेजिस्टरs. */
	sinp(UART_LSR);
	sinp(UART_RX);
	sinp(UART_IIR);
	sinp(UART_MSR);

	वापस 0;
पूर्ण

अटल पूर्णांक serial_ir_resume(काष्ठा platक्रमm_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	result = hardware_init_port();
	अगर (result < 0)
		वापस result;

	spin_lock_irqsave(&hardware[type].lock, flags);
	/* Enable Interrupt */
	serial_ir.lastkt = kसमय_get();
	soutp(UART_IER, sinp(UART_IER) | UART_IER_MSI);
	off();

	spin_unlock_irqrestore(&hardware[type].lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver serial_ir_driver = अणु
	.probe		= serial_ir_probe,
	.suspend	= serial_ir_suspend,
	.resume		= serial_ir_resume,
	.driver		= अणु
		.name	= "serial_ir",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init serial_ir_init(व्योम)
अणु
	पूर्णांक result;

	result = platक्रमm_driver_रेजिस्टर(&serial_ir_driver);
	अगर (result)
		वापस result;

	serial_ir.pdev = platक्रमm_device_alloc("serial_ir", 0);
	अगर (!serial_ir.pdev) अणु
		result = -ENOMEM;
		जाओ निकास_driver_unरेजिस्टर;
	पूर्ण

	result = platक्रमm_device_add(serial_ir.pdev);
	अगर (result)
		जाओ निकास_device_put;

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(serial_ir.pdev);
निकास_driver_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&serial_ir_driver);
	वापस result;
पूर्ण

अटल व्योम serial_ir_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(serial_ir.pdev);
	platक्रमm_driver_unरेजिस्टर(&serial_ir_driver);
पूर्ण

अटल पूर्णांक __init serial_ir_init_module(व्योम)
अणु
	चयन (type) अणु
	हाल IR_HOMEBREW:
	हाल IR_IRDEO:
	हाल IR_IRDEO_REMOTE:
	हाल IR_ANIMAX:
	हाल IR_IGOR:
		/* अगर nothing specअगरied, use ttyS0/com1 and irq 4 */
		io = io ? io : 0x3f8;
		irq = irq ? irq : 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (!softcarrier) अणु
		चयन (type) अणु
		हाल IR_HOMEBREW:
		हाल IR_IGOR:
			hardware[type].set_send_carrier = false;
			hardware[type].set_duty_cycle = false;
			अवरोध;
		पूर्ण
	पूर्ण

	/* make sure sense is either -1, 0, or 1 */
	अगर (sense != -1)
		sense = !!sense;

	वापस serial_ir_init();
पूर्ण

अटल व्योम __निकास serial_ir_निकास_module(व्योम)
अणु
	del_समयr_sync(&serial_ir.समयout_समयr);
	serial_ir_निकास();
पूर्ण

module_init(serial_ir_init_module);
module_निकास(serial_ir_निकास_module);

MODULE_DESCRIPTION("Infra-red receiver driver for serial ports.");
MODULE_AUTHOR("Ralph Metzler, Trent Piepho, Ben Pfaff, Christoph Bartelmus, Andrei Tanas");
MODULE_LICENSE("GPL");

module_param(type, पूर्णांक, 0444);
MODULE_PARM_DESC(type, "Hardware type (0 = home-brew, 1 = IRdeo, 2 = IRdeo Remote, 3 = AnimaX, 4 = IgorPlug");

module_param_hw(io, पूर्णांक, ioport, 0444);
MODULE_PARM_DESC(io, "I/O address base (0x3f8 or 0x2f8)");

/* some architectures (e.g. पूर्णांकel xscale) have memory mapped रेजिस्टरs */
module_param_hw(iommap, uदीर्घ, other, 0444);
MODULE_PARM_DESC(iommap, "physical base for memory mapped I/O (0 = no memory mapped io)");

/*
 * some architectures (e.g. पूर्णांकel xscale) align the 8bit serial रेजिस्टरs
 * on 32bit word boundaries.
 * See linux-kernel/drivers/tty/serial/8250/8250.c serial_in()/out()
 */
module_param_hw(ioshअगरt, पूर्णांक, other, 0444);
MODULE_PARM_DESC(ioshअगरt, "shift I/O register offset (0 = no shift)");

module_param_hw(irq, पूर्णांक, irq, 0444);
MODULE_PARM_DESC(irq, "Interrupt (4 or 3)");

module_param_hw(share_irq, bool, other, 0444);
MODULE_PARM_DESC(share_irq, "Share interrupts (0 = off, 1 = on)");

module_param(sense, पूर्णांक, 0444);
MODULE_PARM_DESC(sense, "Override autodetection of IR receiver circuit (0 = active high, 1 = active low )");

#अगर_घोषित CONFIG_IR_SERIAL_TRANSMITTER
module_param(txsense, bool, 0444);
MODULE_PARM_DESC(txsense, "Sense of transmitter circuit (0 = active high, 1 = active low )");
#पूर्ण_अगर

module_param(softcarrier, bool, 0444);
MODULE_PARM_DESC(softcarrier, "Software carrier (0 = off, 1 = on, default on)");
