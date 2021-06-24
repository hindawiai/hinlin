<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/das08.c
 * comedi module क्रम common DAS08 support (used by ISA/PCI/PCMCIA drivers)
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 * Copyright (C) 2001,2002,2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Copyright (C) 2004 Salvaकरोr E. Tropea <set@users.sf.net> <set@ieee.org>
 */

#समावेश <linux/module.h>

#समावेश "../comedidev.h"

#समावेश "8255.h"
#समावेश "comedi_8254.h"
#समावेश "das08.h"

/*
 * Data क्रमmat of DAS08_AI_LSB_REG and DAS08_AI_MSB_REG depends on
 * 'ai_encoding' member of board काष्ठाure:
 *
 * das08_encode12     : DATA[11..4] = MSB[7..0], DATA[3..0] = LSB[7..4].
 * das08_pcm_encode12 : DATA[11..8] = MSB[3..0], DATA[7..9] = LSB[7..0].
 * das08_encode16     : SIGN = MSB[7], MAGNITUDE[14..8] = MSB[6..0],
 *                      MAGNITUDE[7..0] = LSB[7..0].
 *                      SIGN==0 क्रम negative input, SIGN==1 क्रम positive input.
 *                      Note: when पढ़ो a second समय after conversion
 *                            complete, MSB[7] is an "over-range" bit.
 */
#घोषणा DAS08_AI_LSB_REG	0x00	/* (R) AI least signअगरicant bits */
#घोषणा DAS08_AI_MSB_REG	0x01	/* (R) AI most signअगरicant bits */
#घोषणा DAS08_AI_TRIG_REG	0x01	/* (W) AI software trigger */
#घोषणा DAS08_STATUS_REG	0x02	/* (R) status */
#घोषणा DAS08_STATUS_AI_BUSY	BIT(7)	/* AI conversion in progress */
/*
 * The IRQ status bit is set to 1 by a rising edge on the बाह्यal पूर्णांकerrupt
 * input (which may be jumpered to the pacer output).  It is cleared by
 * setting the INTE control bit to 0.  Not present on "JR" boards.
 */
#घोषणा DAS08_STATUS_IRQ	BIT(3)	/* latched पूर्णांकerrupt input */
/* digital inमाला_दो (not "JR" boards) */
#घोषणा DAS08_STATUS_DI(x)	(((x) & 0x70) >> 4)
#घोषणा DAS08_CONTROL_REG	0x02	/* (W) control */
/*
 * Note: The AI multiplexor channel can also be पढ़ो from status रेजिस्टर using
 * the same mask.
 */
#घोषणा DAS08_CONTROL_MUX_MASK	0x7	/* multiplexor channel mask */
#घोषणा DAS08_CONTROL_MUX(x)	((x) & DAS08_CONTROL_MUX_MASK) /* mux channel */
#घोषणा DAS08_CONTROL_INTE	BIT(3)	/* पूर्णांकerrupt enable (not "JR" boards) */
#घोषणा DAS08_CONTROL_DO_MASK	0xf0	/* digital outमाला_दो mask (not "JR") */
/* digital outमाला_दो (not "JR" boards) */
#घोषणा DAS08_CONTROL_DO(x)	(((x) << 4) & DAS08_CONTROL_DO_MASK)
/*
 * (R/W) programmable AI gain ("PGx" and "AOx" boards):
 * + bits 3..0 (R/W) show/set the gain क्रम the current AI mux channel
 * + bits 6..4 (R) show the current AI mux channel
 * + bit 7 (R) not unused
 */
#घोषणा DAS08_GAIN_REG		0x03

#घोषणा DAS08JR_DI_REG		0x03	/* (R) digital inमाला_दो ("JR" boards) */
#घोषणा DAS08JR_DO_REG		0x03	/* (W) digital outमाला_दो ("JR" boards) */
/* (W) analog output l.s.b. रेजिस्टरs क्रम 2 channels ("JR" boards) */
#घोषणा DAS08JR_AO_LSB_REG(x)	((x) ? 0x06 : 0x04)
/* (W) analog output m.s.b. रेजिस्टरs क्रम 2 channels ("JR" boards) */
#घोषणा DAS08JR_AO_MSB_REG(x)	((x) ? 0x07 : 0x05)
/*
 * (R) update analog outमाला_दो ("JR" boards set क्रम simultaneous output)
 *     (same रेजिस्टर as digital inमाला_दो)
 */
#घोषणा DAS08JR_AO_UPDATE_REG	0x03

/* (W) analog output l.s.b. रेजिस्टरs क्रम 2 channels ("AOx" boards) */
#घोषणा DAS08AOX_AO_LSB_REG(x)	((x) ? 0x0a : 0x08)
/* (W) analog output m.s.b. रेजिस्टरs क्रम 2 channels ("AOx" boards) */
#घोषणा DAS08AOX_AO_MSB_REG(x)	((x) ? 0x0b : 0x09)
/*
 * (R) update analog outमाला_दो ("AOx" boards set क्रम simultaneous output)
 *     (any of the analog output रेजिस्टरs could be used क्रम this)
 */
#घोषणा DAS08AOX_AO_UPDATE_REG	0x08

/* gainlist same as _pgx_ below */

अटल स्थिर काष्ठा comedi_lrange das08_pgl_ai_range = अणु
	9, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange das08_pgh_ai_range = अणु
	12, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(1),
		BIP_RANGE(0.5),
		BIP_RANGE(0.1),
		BIP_RANGE(0.05),
		BIP_RANGE(0.01),
		BIP_RANGE(0.005),
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange das08_pgm_ai_range = अणु
	9, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05),
		BIP_RANGE(0.01),
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *स्थिर das08_ai_lranges[] = अणु
	[das08_pg_none]		= &range_unknown,
	[das08_bipolar5]	= &range_bipolar5,
	[das08_pgh]		= &das08_pgh_ai_range,
	[das08_pgl]		= &das08_pgl_ai_range,
	[das08_pgm]		= &das08_pgm_ai_range,
पूर्ण;

अटल स्थिर पूर्णांक das08_pgh_ai_gainlist[] = अणु
	8, 0, 10, 2, 12, 4, 14, 6, 1, 3, 5, 7
पूर्ण;
अटल स्थिर पूर्णांक das08_pgl_ai_gainlist[] = अणु 8, 0, 2, 4, 6, 1, 3, 5, 7 पूर्ण;
अटल स्थिर पूर्णांक das08_pgm_ai_gainlist[] = अणु 8, 0, 10, 12, 14, 9, 11, 13, 15 पूर्ण;

अटल स्थिर पूर्णांक *स्थिर das08_ai_gainlists[] = अणु
	[das08_pg_none]		= शून्य,
	[das08_bipolar5]	= शून्य,
	[das08_pgh]		= das08_pgh_ai_gainlist,
	[das08_pgl]		= das08_pgl_ai_gainlist,
	[das08_pgm]		= das08_pgm_ai_gainlist,
पूर्ण;

अटल पूर्णांक das08_ai_eoc(काष्ठा comedi_device *dev,
			काष्ठा comedi_subdevice *s,
			काष्ठा comedi_insn *insn,
			अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DAS08_STATUS_REG);
	अगर ((status & DAS08_STATUS_AI_BUSY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक das08_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा das08_board_काष्ठा *board = dev->board_ptr;
	काष्ठा das08_निजी_काष्ठा *devpriv = dev->निजी;
	पूर्णांक n;
	पूर्णांक chan;
	पूर्णांक range;
	पूर्णांक lsb, msb;
	पूर्णांक ret;

	chan = CR_CHAN(insn->chanspec);
	range = CR_RANGE(insn->chanspec);

	/* clear crap */
	inb(dev->iobase + DAS08_AI_LSB_REG);
	inb(dev->iobase + DAS08_AI_MSB_REG);

	/* set multiplexer */
	/* lock to prevent race with digital output */
	spin_lock(&dev->spinlock);
	devpriv->करो_mux_bits &= ~DAS08_CONTROL_MUX_MASK;
	devpriv->करो_mux_bits |= DAS08_CONTROL_MUX(chan);
	outb(devpriv->करो_mux_bits, dev->iobase + DAS08_CONTROL_REG);
	spin_unlock(&dev->spinlock);

	अगर (devpriv->pg_gainlist) अणु
		/* set gain/range */
		range = CR_RANGE(insn->chanspec);
		outb(devpriv->pg_gainlist[range],
		     dev->iobase + DAS08_GAIN_REG);
	पूर्ण

	क्रम (n = 0; n < insn->n; n++) अणु
		/* clear over-range bits क्रम 16-bit boards */
		अगर (board->ai_nbits == 16)
			अगर (inb(dev->iobase + DAS08_AI_MSB_REG) & 0x80)
				dev_info(dev->class_dev, "over-range\n");

		/* trigger conversion */
		outb_p(0, dev->iobase + DAS08_AI_TRIG_REG);

		ret = comedi_समयout(dev, s, insn, das08_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		msb = inb(dev->iobase + DAS08_AI_MSB_REG);
		lsb = inb(dev->iobase + DAS08_AI_LSB_REG);
		अगर (board->ai_encoding == das08_encode12) अणु
			data[n] = (lsb >> 4) | (msb << 4);
		पूर्ण अन्यथा अगर (board->ai_encoding == das08_pcm_encode12) अणु
			data[n] = (msb << 8) + lsb;
		पूर्ण अन्यथा अगर (board->ai_encoding == das08_encode16) अणु
			/*
			 * "JR" 16-bit boards are sign-magnitude.
			 *
			 * XXX The manual seems to imply that 0 is full-scale
			 * negative and 65535 is full-scale positive, but the
			 * original COMEDI patch to add support क्रम the
			 * DAS08/JR/16 and DAS08/JR/16-AO boards have it
			 * encoded as sign-magnitude.  Assume the original
			 * COMEDI code is correct क्रम now.
			 */
			अचिन्हित पूर्णांक magnitude = lsb | ((msb & 0x7f) << 8);

			/*
			 * MSB bit 7 is 0 क्रम negative, 1 क्रम positive voltage.
			 * COMEDI 16-bit bipolar data value क्रम 0V is 0x8000.
			 */
			अगर (msb & 0x80)
				data[n] = BIT(15) + magnitude;
			अन्यथा
				data[n] = BIT(15) - magnitude;
		पूर्ण अन्यथा अणु
			dev_err(dev->class_dev, "bug! unknown ai encoding\n");
			वापस -1;
		पूर्ण
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक das08_di_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	data[0] = 0;
	data[1] = DAS08_STATUS_DI(inb(dev->iobase + DAS08_STATUS_REG));

	वापस insn->n;
पूर्ण

अटल पूर्णांक das08_करो_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा das08_निजी_काष्ठा *devpriv = dev->निजी;

	अगर (comedi_dio_update_state(s, data)) अणु
		/* prevent race with setting of analog input mux */
		spin_lock(&dev->spinlock);
		devpriv->करो_mux_bits &= ~DAS08_CONTROL_DO_MASK;
		devpriv->करो_mux_bits |= DAS08_CONTROL_DO(s->state);
		outb(devpriv->करो_mux_bits, dev->iobase + DAS08_CONTROL_REG);
		spin_unlock(&dev->spinlock);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक das08jr_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	data[0] = 0;
	data[1] = inb(dev->iobase + DAS08JR_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक das08jr_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS08JR_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम das08_ao_set_data(काष्ठा comedi_device *dev,
			      अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक data)
अणु
	स्थिर काष्ठा das08_board_काष्ठा *board = dev->board_ptr;
	अचिन्हित अक्षर lsb;
	अचिन्हित अक्षर msb;

	lsb = data & 0xff;
	msb = (data >> 8) & 0xff;
	अगर (board->is_jr) अणु
		outb(lsb, dev->iobase + DAS08JR_AO_LSB_REG(chan));
		outb(msb, dev->iobase + DAS08JR_AO_MSB_REG(chan));
		/* load DACs */
		inb(dev->iobase + DAS08JR_AO_UPDATE_REG);
	पूर्ण अन्यथा अणु
		outb(lsb, dev->iobase + DAS08AOX_AO_LSB_REG(chan));
		outb(msb, dev->iobase + DAS08AOX_AO_MSB_REG(chan));
		/* load DACs */
		inb(dev->iobase + DAS08AOX_AO_UPDATE_REG);
	पूर्ण
पूर्ण

अटल पूर्णांक das08_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		das08_ao_set_data(dev, chan, val);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

पूर्णांक das08_common_attach(काष्ठा comedi_device *dev, अचिन्हित दीर्घ iobase)
अणु
	स्थिर काष्ठा das08_board_काष्ठा *board = dev->board_ptr;
	काष्ठा das08_निजी_काष्ठा *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;
	पूर्णांक i;

	dev->iobase = iobase;

	dev->board_name = board->name;

	ret = comedi_alloc_subdevices(dev, 6);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* ai */
	अगर (board->ai_nbits) अणु
		s->type = COMEDI_SUBD_AI;
		/*
		 * XXX some boards actually have dअगरferential
		 * inमाला_दो instead of single ended.
		 * The driver करोes nothing with arefs though,
		 * so it's no big deal.
		 */
		s->subdev_flags = SDF_READABLE | SDF_GROUND;
		s->n_chan = 8;
		s->maxdata = (1 << board->ai_nbits) - 1;
		s->range_table = das08_ai_lranges[board->ai_pg];
		s->insn_पढ़ो = das08_ai_insn_पढ़ो;
		devpriv->pg_gainlist = das08_ai_gainlists[board->ai_pg];
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[1];
	/* ao */
	अगर (board->ao_nbits) अणु
		s->type = COMEDI_SUBD_AO;
		s->subdev_flags = SDF_WRITABLE;
		s->n_chan = 2;
		s->maxdata = (1 << board->ao_nbits) - 1;
		s->range_table = &range_bipolar5;
		s->insn_ग_लिखो = das08_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		/* initialize all channels to 0V */
		क्रम (i = 0; i < s->n_chan; i++) अणु
			s->पढ़ोback[i] = s->maxdata / 2;
			das08_ao_set_data(dev, i, s->पढ़ोback[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[2];
	/* di */
	अगर (board->di_nchan) अणु
		s->type = COMEDI_SUBD_DI;
		s->subdev_flags = SDF_READABLE;
		s->n_chan = board->di_nchan;
		s->maxdata = 1;
		s->range_table = &range_digital;
		s->insn_bits = board->is_jr ? das08jr_di_insn_bits :
			       das08_di_insn_bits;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[3];
	/* करो */
	अगर (board->करो_nchan) अणु
		s->type = COMEDI_SUBD_DO;
		s->subdev_flags = SDF_WRITABLE;
		s->n_chan = board->करो_nchan;
		s->maxdata = 1;
		s->range_table = &range_digital;
		s->insn_bits = board->is_jr ? das08jr_करो_insn_bits :
			       das08_करो_insn_bits;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[4];
	/* 8255 */
	अगर (board->i8255_offset != 0) अणु
		ret = subdev_8255_init(dev, s, शून्य, board->i8255_offset);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Counter subdevice (8254) */
	s = &dev->subdevices[5];
	अगर (board->i8254_offset) अणु
		dev->pacer = comedi_8254_init(dev->iobase + board->i8254_offset,
					      0, I8254_IO8, 0);
		अगर (!dev->pacer)
			वापस -ENOMEM;

		comedi_8254_subdevice_init(s, dev->pacer);
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(das08_common_attach);

अटल पूर्णांक __init das08_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(das08_init);

अटल व्योम __निकास das08_निकास(व्योम)
अणु
पूर्ण
module_निकास(das08_निकास);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi common DAS08 support module");
MODULE_LICENSE("GPL");
