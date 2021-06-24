<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम Data Translation DT2811
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: dt2811
 * Description: Data Translation DT2811
 * Author: ds
 * Devices: [Data Translation] DT2811-PGL (dt2811-pgl), DT2811-PGH (dt2811-pgh)
 * Status: works
 *
 * Configuration options:
 *   [0] - I/O port base address
 *   [1] - IRQ (optional, needed क्रम async command support)
 *   [2] - A/D reference (# of analog inमाला_दो)
 *	   0 = single-ended (16 channels)
 *	   1 = dअगरferential (8 channels)
 *	   2 = pseuकरो-dअगरferential (16 channels)
 *   [3] - A/D range (deprecated, see below)
 *   [4] - D/A 0 range (deprecated, see below)
 *   [5] - D/A 1 range (deprecated, see below)
 *
 * Notes:
 *   - A/D ranges are not programmable but the gain is. The AI subdevice has
 *     a range_table containing all the possible analog input range/gain
 *     options क्रम the dt2811-pgh or dt2811-pgl. Use the range that matches
 *     your board configuration and the desired gain to correctly convert
 *     between data values and physical units and to set the correct output
 *     gain.
 *   - D/A ranges are not programmable. The AO subdevice has a range_table
 *     containing all the possible analog output ranges. Use the range
 *     that matches your board configuration to convert between data
 *     values and physical units.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>

#समावेश "../comedidev.h"

/*
 * Register I/O map
 */
#घोषणा DT2811_ADCSR_REG		0x00	/* r/w  A/D Control/Status */
#घोषणा DT2811_ADCSR_ADDONE		BIT(7)	/* r      1=A/D conv करोne */
#घोषणा DT2811_ADCSR_ADERROR		BIT(6)	/* r      1=A/D error */
#घोषणा DT2811_ADCSR_ADBUSY		BIT(5)	/* r      1=A/D busy */
#घोषणा DT2811_ADCSR_CLRERROR		BIT(4)
#घोषणा DT2811_ADCSR_DMAENB		BIT(3)	/* r/w    1=dma ena */
#घोषणा DT2811_ADCSR_INTENB		BIT(2)	/* r/w    1=पूर्णांकerrupts ena */
#घोषणा DT2811_ADCSR_ADMODE(x)		(((x) & 0x3) << 0)

#घोषणा DT2811_ADGCR_REG		0x01	/* r/w  A/D Gain/Channel */
#घोषणा DT2811_ADGCR_GAIN(x)		(((x) & 0x3) << 6)
#घोषणा DT2811_ADGCR_CHAN(x)		(((x) & 0xf) << 0)

#घोषणा DT2811_ADDATA_LO_REG		0x02	/* r   A/D Data low byte */
#घोषणा DT2811_ADDATA_HI_REG		0x03	/* r   A/D Data high byte */

#घोषणा DT2811_DADATA_LO_REG(x)		(0x02 + ((x) * 2)) /* w D/A Data low */
#घोषणा DT2811_DADATA_HI_REG(x)		(0x03 + ((x) * 2)) /* w D/A Data high */

#घोषणा DT2811_DI_REG			0x06	/* r   Digital Input Port 0 */
#घोषणा DT2811_DO_REG			0x06	/* w   Digital Output Port 1 */

#घोषणा DT2811_TMRCTR_REG		0x07	/* r/w  Timer/Counter */
#घोषणा DT2811_TMRCTR_MANTISSA(x)	(((x) & 0x7) << 3)
#घोषणा DT2811_TMRCTR_EXPONENT(x)	(((x) & 0x7) << 0)

#घोषणा DT2811_OSC_BASE			1666	/* 600 kHz = 1666.6667ns */

/*
 * Timer frequency control:
 *   DT2811_TMRCTR_MANTISSA	DT2811_TMRCTR_EXPONENT
 *   val  भागisor  frequency	val  multiply भागisor/भागide frequency by
 *    0      1      600 kHz	 0   1
 *    1     10       60 kHz	 1   10
 *    2      2      300 kHz	 2   100
 *    3      3      200 kHz	 3   1000
 *    4      4      150 kHz	 4   10000
 *    5      5      120 kHz	 5   100000
 *    6      6      100 kHz	 6   1000000
 *    7     12       50 kHz	 7   10000000
 */
अटल स्थिर अचिन्हित पूर्णांक dt2811_clk_भागiders[] = अणु
	1, 10, 2, 3, 4, 5, 6, 12
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक dt2811_clk_multipliers[] = अणु
	1, 10, 100, 1000, 10000, 100000, 1000000, 10000000
पूर्ण;

/*
 * The Analog Input range is set using jumpers on the board.
 *
 * Input Range		W9  W10
 * -5V to +5V		In  Out
 * -2.5V to +2.5V	In  In
 * 0V to +5V		Out In
 *
 * The gain may be set to 1, 2, 4, or 8 (on the dt2811-pgh) or to
 * 1, 10, 100, 500 (on the dt2811-pgl).
 */
अटल स्थिर काष्ठा comedi_lrange dt2811_pgh_ai_ranges = अणु
	12, अणु
		BIP_RANGE(5),		/* range 0: gain=1 */
		BIP_RANGE(2.5),		/* range 1: gain=2 */
		BIP_RANGE(1.25),	/* range 2: gain=4 */
		BIP_RANGE(0.625),	/* range 3: gain=8 */

		BIP_RANGE(2.5),		/* range 0+4: gain=1 */
		BIP_RANGE(1.25),	/* range 1+4: gain=2 */
		BIP_RANGE(0.625),	/* range 2+4: gain=4 */
		BIP_RANGE(0.3125),	/* range 3+4: gain=8 */

		UNI_RANGE(5),		/* range 0+8: gain=1 */
		UNI_RANGE(2.5),		/* range 1+8: gain=2 */
		UNI_RANGE(1.25),	/* range 2+8: gain=4 */
		UNI_RANGE(0.625)	/* range 3+8: gain=8 */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange dt2811_pgl_ai_ranges = अणु
	12, अणु
		BIP_RANGE(5),		/* range 0: gain=1 */
		BIP_RANGE(0.5),		/* range 1: gain=10 */
		BIP_RANGE(0.05),	/* range 2: gain=100 */
		BIP_RANGE(0.01),	/* range 3: gain=500 */

		BIP_RANGE(2.5),		/* range 0+4: gain=1 */
		BIP_RANGE(0.25),	/* range 1+4: gain=10 */
		BIP_RANGE(0.025),	/* range 2+4: gain=100 */
		BIP_RANGE(0.005),	/* range 3+4: gain=500 */

		UNI_RANGE(5),		/* range 0+8: gain=1 */
		UNI_RANGE(0.5),		/* range 1+8: gain=10 */
		UNI_RANGE(0.05),	/* range 2+8: gain=100 */
		UNI_RANGE(0.01)		/* range 3+8: gain=500 */
	पूर्ण
पूर्ण;

/*
 * The Analog Output range is set per-channel using jumpers on the board.
 *
 *			DAC0 Jumpers		DAC1 Jumpers
 * Output Range		W5  W6  W7  W8		W1  W2  W3  W4
 * -5V to +5V		In  Out In  Out		In  Out In  Out
 * -2.5V to +2.5V	In  Out Out In		In  Out Out In
 * 0 to +5V		Out In  Out In		Out In  Out In
 */
अटल स्थिर काष्ठा comedi_lrange dt2811_ao_ranges = अणु
	3, अणु
		BIP_RANGE(5),	/* शेष setting from factory */
		BIP_RANGE(2.5),
		UNI_RANGE(5)
	पूर्ण
पूर्ण;

काष्ठा dt2811_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक is_pgh:1;
पूर्ण;

अटल स्थिर काष्ठा dt2811_board dt2811_boards[] = अणु
	अणु
		.name		= "dt2811-pgh",
		.is_pgh		= 1,
	पूर्ण, अणु
		.name		= "dt2811-pgl",
	पूर्ण,
पूर्ण;

काष्ठा dt2811_निजी अणु
	अचिन्हित पूर्णांक ai_भागisor;
पूर्ण;

अटल अचिन्हित पूर्णांक dt2811_ai_पढ़ो_sample(काष्ठा comedi_device *dev,
					  काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + DT2811_ADDATA_LO_REG) |
	      (inb(dev->iobase + DT2811_ADDATA_HI_REG) << 8);

	वापस val & s->maxdata;
पूर्ण

अटल irqवापस_t dt2811_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक status;

	अगर (!dev->attached)
		वापस IRQ_NONE;

	status = inb(dev->iobase + DT2811_ADCSR_REG);

	अगर (status & DT2811_ADCSR_ADERROR) अणु
		async->events |= COMEDI_CB_OVERFLOW;

		outb(status | DT2811_ADCSR_CLRERROR,
		     dev->iobase + DT2811_ADCSR_REG);
	पूर्ण

	अगर (status & DT2811_ADCSR_ADDONE) अणु
		अचिन्हित लघु val;

		val = dt2811_ai_पढ़ो_sample(dev, s);
		comedi_buf_ग_लिखो_samples(s, &val, 1);
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dt2811_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	/*
	 * Mode 0
	 * Single conversion
	 *
	 * Loading a chanspec will trigger a conversion.
	 */
	outb(DT2811_ADCSR_ADMODE(0), dev->iobase + DT2811_ADCSR_REG);

	वापस 0;
पूर्ण

अटल व्योम dt2811_ai_set_chanspec(काष्ठा comedi_device *dev,
				   अचिन्हित पूर्णांक chanspec)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);

	outb(DT2811_ADGCR_CHAN(chan) | DT2811_ADGCR_GAIN(range),
	     dev->iobase + DT2811_ADGCR_REG);
पूर्ण

अटल पूर्णांक dt2811_ai_cmd(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dt2811_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक mode;

	अगर (cmd->start_src == TRIG_NOW) अणु
		/*
		 * Mode 1
		 * Continuous conversion, पूर्णांकernal trigger and घड़ी
		 *
		 * This resets the trigger flip-flop, disabling A/D strobes.
		 * The समयr/counter रेजिस्टर is loaded with the भागision
		 * ratio which will give the required sample rate.
		 *
		 * Loading the first chanspec sets the trigger flip-flop,
		 * enabling the समयr/counter. A/D strobes are then generated
		 * at the rate set by the पूर्णांकernal घड़ी/भागider.
		 */
		mode = DT2811_ADCSR_ADMODE(1);
	पूर्ण अन्यथा अणु /* TRIG_EXT */
		अगर (cmd->convert_src == TRIG_TIMER) अणु
			/*
			 * Mode 2
			 * Continuous conversion, बाह्यal trigger
			 *
			 * Similar to Mode 1, with the exception that the
			 * trigger flip-flop must be set by a negative edge
			 * on the बाह्यal trigger input.
			 */
			mode = DT2811_ADCSR_ADMODE(2);
		पूर्ण अन्यथा अणु /* TRIG_EXT */
			/*
			 * Mode 3
			 * Continuous conversion, बाह्यal trigger, घड़ी
			 *
			 * Similar to Mode 2, with the exception that the
			 * conversion rate is set by the frequency on the
			 * बाह्यal घड़ी/भागider.
			 */
			mode = DT2811_ADCSR_ADMODE(3);
		पूर्ण
	पूर्ण
	outb(mode | DT2811_ADCSR_INTENB, dev->iobase + DT2811_ADCSR_REG);

	/* load समयr */
	outb(devpriv->ai_भागisor, dev->iobase + DT2811_TMRCTR_REG);

	/* load chanspec - enables समयr */
	dt2811_ai_set_chanspec(dev, cmd->chanlist[0]);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक dt2811_ns_to_समयr(अचिन्हित पूर्णांक *nanosec,
				       अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित दीर्घ दीर्घ ns;
	अचिन्हित पूर्णांक ns_lo = COMEDI_MIN_SPEED;
	अचिन्हित पूर्णांक ns_hi = 0;
	अचिन्हित पूर्णांक भागisor_hi = 0;
	अचिन्हित पूर्णांक भागisor_lo = 0;
	अचिन्हित पूर्णांक _भाग;
	अचिन्हित पूर्णांक _mult;

	/*
	 * Work through all the भागider/multiplier values to find the two
	 * बंदst भागisors to generate the requested nanosecond timing.
	 */
	क्रम (_भाग = 0; _भाग <= 7; _भाग++) अणु
		क्रम (_mult = 0; _mult <= 7; _mult++) अणु
			अचिन्हित पूर्णांक भाग = dt2811_clk_भागiders[_भाग];
			अचिन्हित पूर्णांक mult = dt2811_clk_multipliers[_mult];
			अचिन्हित दीर्घ दीर्घ भागider = भाग * mult;
			अचिन्हित पूर्णांक भागisor = DT2811_TMRCTR_MANTISSA(_भाग) |
					       DT2811_TMRCTR_EXPONENT(_mult);

			/*
			 * The समयr can be configured to run at a slowest
			 * speed of 0.005hz (600 Khz/120000000), which requires
			 * 37-bits to represent the nanosecond value. Limit the
			 * slowest timing to what comedi handles (32-bits).
			 */
			ns = भागider * DT2811_OSC_BASE;
			अगर (ns > COMEDI_MIN_SPEED)
				जारी;

			/* Check क्रम fastest found timing */
			अगर (ns <= *nanosec && ns > ns_hi) अणु
				ns_hi = ns;
				भागisor_hi = भागisor;
			पूर्ण
			/* Check क्रम slowest found timing */
			अगर (ns >= *nanosec && ns < ns_lo) अणु
				ns_lo = ns;
				भागisor_lo = भागisor;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * The slowest found timing will be invalid अगर the requested timing
	 * is faster than what can be generated by the समयr. Fix it so that
	 * CMDF_ROUND_UP वापसs valid timing.
	 */
	अगर (ns_lo == COMEDI_MIN_SPEED) अणु
		ns_lo = ns_hi;
		भागisor_lo = भागisor_hi;
	पूर्ण
	/*
	 * The fastest found timing will be invalid अगर the requested timing
	 * is less than what can be generated by the समयr. Fix it so that
	 * CMDF_ROUND_NEAREST and CMDF_ROUND_DOWN वापस valid timing.
	 */
	अगर (ns_hi == 0) अणु
		ns_hi = ns_lo;
		भागisor_hi = भागisor_lo;
	पूर्ण

	चयन (flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_NEAREST:
	शेष:
		अगर (ns_hi - *nanosec < *nanosec - ns_lo) अणु
			*nanosec = ns_lo;
			वापस भागisor_lo;
		पूर्ण
		*nanosec = ns_hi;
		वापस भागisor_hi;
	हाल CMDF_ROUND_UP:
		*nanosec = ns_lo;
		वापस भागisor_lo;
	हाल CMDF_ROUND_DOWN:
		*nanosec = ns_hi;
		वापस भागisor_hi;
	पूर्ण
पूर्ण

अटल पूर्णांक dt2811_ai_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा dt2811_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक arg;
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (cmd->convert_src == TRIG_EXT && cmd->start_src != TRIG_EXT)
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	अगर (cmd->convert_src == TRIG_TIMER)
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg, 12500);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		arg = cmd->convert_arg;
		devpriv->ai_भागisor = dt2811_ns_to_समयr(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण अन्यथा अणु /* TRIG_EXT */
		/* The convert_arg is used to set the भागisor. */
		devpriv->ai_भागisor = cmd->convert_arg;
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */

	वापस 0;
पूर्ण

अटल पूर्णांक dt2811_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DT2811_ADCSR_REG);
	अगर ((status & DT2811_ADCSR_ADBUSY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक dt2811_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	/* We will alपढ़ोy be in Mode 0 */
	क्रम (i = 0; i < insn->n; i++) अणु
		/* load chanspec and trigger conversion */
		dt2811_ai_set_chanspec(dev, insn->chanspec);

		ret = comedi_समयout(dev, s, insn, dt2811_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		data[i] = dt2811_ai_पढ़ो_sample(dev, s);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt2811_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outb(val & 0xff, dev->iobase + DT2811_DADATA_LO_REG(chan));
		outb((val >> 8) & 0xff,
		     dev->iobase + DT2811_DADATA_HI_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt2811_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + DT2811_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt2811_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DT2811_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम dt2811_reset(काष्ठा comedi_device *dev)
अणु
	/* This is the initialization sequence from the users manual */
	outb(DT2811_ADCSR_ADMODE(0), dev->iobase + DT2811_ADCSR_REG);
	usleep_range(100, 1000);
	inb(dev->iobase + DT2811_ADDATA_LO_REG);
	inb(dev->iobase + DT2811_ADDATA_HI_REG);
	outb(DT2811_ADCSR_ADMODE(0) | DT2811_ADCSR_CLRERROR,
	     dev->iobase + DT2811_ADCSR_REG);
पूर्ण

अटल पूर्णांक dt2811_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा dt2811_board *board = dev->board_ptr;
	काष्ठा dt2811_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x8);
	अगर (ret)
		वापस ret;

	dt2811_reset(dev);

	/* IRQ's 2,3,5,7 are valid क्रम async command support */
	अगर (it->options[1] <= 7  && (BIT(it->options[1]) & 0xac)) अणु
		ret = request_irq(it->options[1], dt2811_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE |
			  ((it->options[2] == 1) ? SDF_DIFF :
			   (it->options[2] == 2) ? SDF_COMMON : SDF_GROUND);
	s->n_chan	= (it->options[2] == 1) ? 8 : 16;
	s->maxdata	= 0x0fff;
	s->range_table	= board->is_pgh ? &dt2811_pgh_ai_ranges
					: &dt2811_pgl_ai_ranges;
	s->insn_पढ़ो	= dt2811_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= 1;
		s->करो_cmdtest	= dt2811_ai_cmdtest;
		s->करो_cmd	= dt2811_ai_cmd;
		s->cancel	= dt2811_ai_cancel;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->range_table	= &dt2811_ao_ranges;
	s->insn_ग_लिखो	= dt2811_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= dt2811_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= dt2811_करो_insn_bits;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver dt2811_driver = अणु
	.driver_name	= "dt2811",
	.module		= THIS_MODULE,
	.attach		= dt2811_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &dt2811_boards[0].name,
	.num_names	= ARRAY_SIZE(dt2811_boards),
	.offset		= माप(काष्ठा dt2811_board),
पूर्ण;
module_comedi_driver(dt2811_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Data Translation DT2811 series boards");
MODULE_LICENSE("GPL");
