<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IR SIR driver, (C) 2000 Milan Pikula <www@क्रमnax.sk>
 *
 * sir_ir - Device driver क्रम use with SIR (serial infra red)
 * mode of IrDA on many notebooks.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <media/rc-core.h>

/* SECTION: Definitions */
#घोषणा PULSE '['

/* 9bit * 1s/115200bit in milli seconds = 78.125ms*/
#घोषणा TIME_CONST (9000000ul / 115200ul)

/* समयout क्रम sequences in jअगरfies (=5/100s), must be दीर्घer than TIME_CONST */
#घोषणा SIR_TIMEOUT	(HZ * 5 / 100)

/* onboard sir ports are typically com3 */
अटल पूर्णांक io = 0x3e8;
अटल पूर्णांक irq = 4;
अटल पूर्णांक threshold = 3;

अटल DEFINE_SPINLOCK(समयr_lock);
अटल काष्ठा समयr_list समयrlist;
/* समय of last संकेत change detected */
अटल kसमय_प्रकार last;
/* समय of last UART data पढ़ोy पूर्णांकerrupt */
अटल kसमय_प्रकार last_पूर्णांकr_समय;
अटल पूर्णांक last_value;
अटल काष्ठा rc_dev *rcdev;

अटल काष्ठा platक्रमm_device *sir_ir_dev;

अटल DEFINE_SPINLOCK(hardware_lock);

/* SECTION: Prototypes */

/* Communication with user-space */
अटल व्योम add_पढ़ो_queue(पूर्णांक flag, अचिन्हित दीर्घ val);
/* Hardware */
अटल irqवापस_t sir_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल व्योम send_space(अचिन्हित दीर्घ len);
अटल व्योम send_pulse(अचिन्हित दीर्घ len);
अटल पूर्णांक init_hardware(व्योम);
अटल व्योम drop_hardware(व्योम);
/* Initialisation */

अटल अंतरभूत अचिन्हित पूर्णांक sinp(पूर्णांक offset)
अणु
	वापस inb(io + offset);
पूर्ण

अटल अंतरभूत व्योम soutp(पूर्णांक offset, पूर्णांक value)
अणु
	outb(value, io + offset);
पूर्ण

/* SECTION: Communication with user-space */
अटल पूर्णांक sir_tx_ir(काष्ठा rc_dev *dev, अचिन्हित पूर्णांक *tx_buf,
		     अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	local_irq_save(flags);
	क्रम (i = 0; i < count;) अणु
		अगर (tx_buf[i])
			send_pulse(tx_buf[i]);
		i++;
		अगर (i >= count)
			अवरोध;
		अगर (tx_buf[i])
			send_space(tx_buf[i]);
		i++;
	पूर्ण
	local_irq_restore(flags);

	वापस count;
पूर्ण

अटल व्योम add_पढ़ो_queue(पूर्णांक flag, अचिन्हित दीर्घ val)
अणु
	काष्ठा ir_raw_event ev = अणुपूर्ण;

	pr_debug("add flag %d with val %lu\n", flag, val);

	/*
	 * statistically, pulses are ~TIME_CONST/2 too दीर्घ. we could
	 * maybe make this more exact, but this is good enough
	 */
	अगर (flag) अणु
		/* pulse */
		अगर (val > TIME_CONST / 2)
			val -= TIME_CONST / 2;
		अन्यथा /* should not ever happen */
			val = 1;
		ev.pulse = true;
	पूर्ण अन्यथा अणु
		val += TIME_CONST / 2;
	पूर्ण
	ev.duration = val;

	ir_raw_event_store_with_filter(rcdev, &ev);
पूर्ण

/* SECTION: Hardware */
अटल व्योम sir_समयout(काष्ठा समयr_list *unused)
अणु
	/*
	 * अगर last received संकेत was a pulse, but receiving stopped
	 * within the 9 bit frame, we need to finish this pulse and
	 * simulate a संकेत change to from pulse to space. Otherwise
	 * upper layers will receive two sequences next समय.
	 */

	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ pulse_end;

	/* aव्योम पूर्णांकerference with पूर्णांकerrupt */
	spin_lock_irqsave(&समयr_lock, flags);
	अगर (last_value) अणु
		/* clear unपढ़ो bits in UART and restart */
		outb(UART_FCR_CLEAR_RCVR, io + UART_FCR);
		/* determine 'virtual' pulse end: */
		pulse_end = min_t(अचिन्हित दीर्घ,
				  kसमय_us_delta(last, last_पूर्णांकr_समय),
				  IR_MAX_DURATION);
		dev_dbg(&sir_ir_dev->dev, "timeout add %d for %lu usec\n",
			last_value, pulse_end);
		add_पढ़ो_queue(last_value, pulse_end);
		last_value = 0;
		last = last_पूर्णांकr_समय;
	पूर्ण
	spin_unlock_irqrestore(&समयr_lock, flags);
	ir_raw_event_handle(rcdev);
पूर्ण

अटल irqवापस_t sir_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित अक्षर data;
	kसमय_प्रकार curr_समय;
	अचिन्हित दीर्घ delt;
	अचिन्हित दीर्घ deltपूर्णांकr;
	अचिन्हित दीर्घ flags;
	पूर्णांक counter = 0;
	पूर्णांक iir, lsr;

	जबतक ((iir = inb(io + UART_IIR) & UART_IIR_ID)) अणु
		अगर (++counter > 256) अणु
			dev_err(&sir_ir_dev->dev, "Trapped in interrupt");
			अवरोध;
		पूर्ण

		चयन (iir & UART_IIR_ID) अणु /* FIXME toto treba preriedit */
		हाल UART_IIR_MSI:
			(व्योम)inb(io + UART_MSR);
			अवरोध;
		हाल UART_IIR_RLSI:
		हाल UART_IIR_THRI:
			(व्योम)inb(io + UART_LSR);
			अवरोध;
		हाल UART_IIR_RDI:
			/* aव्योम पूर्णांकerference with समयr */
			spin_lock_irqsave(&समयr_lock, flags);
			करो अणु
				del_समयr(&समयrlist);
				data = inb(io + UART_RX);
				curr_समय = kसमय_get();
				delt = min_t(अचिन्हित दीर्घ,
					     kसमय_us_delta(last, curr_समय),
					     IR_MAX_DURATION);
				deltपूर्णांकr = min_t(अचिन्हित दीर्घ,
						 kसमय_us_delta(last_पूर्णांकr_समय,
								curr_समय),
						 IR_MAX_DURATION);
				dev_dbg(&sir_ir_dev->dev, "t %lu, d %d\n",
					deltपूर्णांकr, (पूर्णांक)data);
				/*
				 * अगर nothing came in last X cycles,
				 * it was gap
				 */
				अगर (deltपूर्णांकr > TIME_CONST * threshold) अणु
					अगर (last_value) अणु
						dev_dbg(&sir_ir_dev->dev, "GAP\n");
						/* simulate संकेत change */
						add_पढ़ो_queue(last_value,
							       delt -
							       deltपूर्णांकr);
						last_value = 0;
						last = last_पूर्णांकr_समय;
						delt = deltपूर्णांकr;
					पूर्ण
				पूर्ण
				data = 1;
				अगर (data ^ last_value) अणु
					/*
					 * deltपूर्णांकr > 2*TIME_CONST, remember?
					 * the other हाल is समयout
					 */
					add_पढ़ो_queue(last_value,
						       delt - TIME_CONST);
					last_value = data;
					last = curr_समय;
					last = kसमय_sub_us(last,
							    TIME_CONST);
				पूर्ण
				last_पूर्णांकr_समय = curr_समय;
				अगर (data) अणु
					/*
					 * start समयr क्रम end of
					 * sequence detection
					 */
					समयrlist.expires = jअगरfies +
								SIR_TIMEOUT;
					add_समयr(&समयrlist);
				पूर्ण

				lsr = inb(io + UART_LSR);
			पूर्ण जबतक (lsr & UART_LSR_DR); /* data पढ़ोy */
			spin_unlock_irqrestore(&समयr_lock, flags);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	ir_raw_event_handle(rcdev);
	वापस IRQ_RETVAL(IRQ_HANDLED);
पूर्ण

अटल व्योम send_space(अचिन्हित दीर्घ len)
अणु
	usleep_range(len, len + 25);
पूर्ण

अटल व्योम send_pulse(अचिन्हित दीर्घ len)
अणु
	दीर्घ bytes_out = len / TIME_CONST;

	अगर (bytes_out == 0)
		bytes_out++;

	जबतक (bytes_out--) अणु
		outb(PULSE, io + UART_TX);
		/* FIXME treba seriozne cakanie z अक्षर/serial.c */
		जबतक (!(inb(io + UART_LSR) & UART_LSR_THRE))
			;
	पूर्ण
पूर्ण

अटल पूर्णांक init_hardware(व्योम)
अणु
	u8 scratch, scratch2, scratch3;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hardware_lock, flags);

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
		spin_unlock_irqrestore(&hardware_lock, flags);
		pr_err("port existence test failed, cannot continue\n");
		वापस -ENODEV;
	पूर्ण

	/* reset UART */
	outb(0, io + UART_MCR);
	outb(0, io + UART_IER);
	/* init UART */
	/* set DLAB, speed = 115200 */
	outb(UART_LCR_DLAB | UART_LCR_WLEN7, io + UART_LCR);
	outb(1, io + UART_DLL); outb(0, io + UART_DLM);
	/* 7N1+start = 9 bits at 115200 ~ 3 bits at 44000 */
	outb(UART_LCR_WLEN7, io + UART_LCR);
	/* FIFO operation */
	outb(UART_FCR_ENABLE_FIFO, io + UART_FCR);
	/* पूर्णांकerrupts */
	/* outb(UART_IER_RLSI|UART_IER_RDI|UART_IER_THRI, io + UART_IER); */
	outb(UART_IER_RDI, io + UART_IER);
	/* turn on UART */
	outb(UART_MCR_DTR | UART_MCR_RTS | UART_MCR_OUT2, io + UART_MCR);
	spin_unlock_irqrestore(&hardware_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम drop_hardware(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hardware_lock, flags);

	/* turn off पूर्णांकerrupts */
	outb(0, io + UART_IER);

	spin_unlock_irqrestore(&hardware_lock, flags);
पूर्ण

/* SECTION: Initialisation */
अटल पूर्णांक sir_ir_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक retval;

	rcdev = devm_rc_allocate_device(&sir_ir_dev->dev, RC_DRIVER_IR_RAW);
	अगर (!rcdev)
		वापस -ENOMEM;

	rcdev->device_name = "SIR IrDA port";
	rcdev->input_phys = KBUILD_MODNAME "/input0";
	rcdev->input_id.bustype = BUS_HOST;
	rcdev->input_id.venकरोr = 0x0001;
	rcdev->input_id.product = 0x0001;
	rcdev->input_id.version = 0x0100;
	rcdev->tx_ir = sir_tx_ir;
	rcdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rcdev->driver_name = KBUILD_MODNAME;
	rcdev->map_name = RC_MAP_RC6_MCE;
	rcdev->समयout = IR_DEFAULT_TIMEOUT;
	rcdev->dev.parent = &sir_ir_dev->dev;

	समयr_setup(&समयrlist, sir_समयout, 0);

	/* get I/O port access and IRQ line */
	अगर (!devm_request_region(&sir_ir_dev->dev, io, 8, KBUILD_MODNAME)) अणु
		pr_err("i/o port 0x%.4x already in use.\n", io);
		वापस -EBUSY;
	पूर्ण
	retval = devm_request_irq(&sir_ir_dev->dev, irq, sir_पूर्णांकerrupt, 0,
				  KBUILD_MODNAME, शून्य);
	अगर (retval < 0) अणु
		pr_err("IRQ %d already in use.\n", irq);
		वापस retval;
	पूर्ण

	retval = init_hardware();
	अगर (retval) अणु
		del_समयr_sync(&समयrlist);
		वापस retval;
	पूर्ण

	pr_info("I/O port 0x%.4x, IRQ %d.\n", io, irq);

	retval = devm_rc_रेजिस्टर_device(&sir_ir_dev->dev, rcdev);
	अगर (retval < 0)
		वापस retval;

	वापस 0;
पूर्ण

अटल पूर्णांक sir_ir_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	drop_hardware();
	del_समयr_sync(&समयrlist);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sir_ir_driver = अणु
	.probe		= sir_ir_probe,
	.हटाओ		= sir_ir_हटाओ,
	.driver		= अणु
		.name	= "sir_ir",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sir_ir_init(व्योम)
अणु
	पूर्णांक retval;

	retval = platक्रमm_driver_रेजिस्टर(&sir_ir_driver);
	अगर (retval)
		वापस retval;

	sir_ir_dev = platक्रमm_device_alloc("sir_ir", 0);
	अगर (!sir_ir_dev) अणु
		retval = -ENOMEM;
		जाओ pdev_alloc_fail;
	पूर्ण

	retval = platक्रमm_device_add(sir_ir_dev);
	अगर (retval)
		जाओ pdev_add_fail;

	वापस 0;

pdev_add_fail:
	platक्रमm_device_put(sir_ir_dev);
pdev_alloc_fail:
	platक्रमm_driver_unरेजिस्टर(&sir_ir_driver);
	वापस retval;
पूर्ण

अटल व्योम __निकास sir_ir_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(sir_ir_dev);
	platक्रमm_driver_unरेजिस्टर(&sir_ir_driver);
पूर्ण

module_init(sir_ir_init);
module_निकास(sir_ir_निकास);

MODULE_DESCRIPTION("Infrared receiver driver for SIR type serial ports");
MODULE_AUTHOR("Milan Pikula");
MODULE_LICENSE("GPL");

module_param_hw(io, पूर्णांक, ioport, 0444);
MODULE_PARM_DESC(io, "I/O address base (0x3f8 or 0x2f8)");

module_param_hw(irq, पूर्णांक, irq, 0444);
MODULE_PARM_DESC(irq, "Interrupt (4 or 3)");

module_param(threshold, पूर्णांक, 0444);
MODULE_PARM_DESC(threshold, "space detection threshold (3)");
