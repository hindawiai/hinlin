<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * c6xdigio.c
 * Hardware driver क्रम Mechatronic Systems Inc. C6x_DIGIO DSP daughter card.
 * http://web.archive.org/web/%2A/http://robot0.ge.uiuc.edu/~spong/mecha/
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1999 Dan Block
 */

/*
 * Driver: c6xdigio
 * Description: Mechatronic Systems Inc. C6x_DIGIO DSP daughter card
 * Author: Dan Block
 * Status: unknown
 * Devices: [Mechatronic Systems Inc.] C6x_DIGIO DSP daughter card (c6xdigio)
 * Updated: Sun Nov 20 20:18:34 EST 2005
 *
 * Configuration Options:
 *	[0] - base address
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयx.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/pnp.h>

#समावेश "../comedidev.h"

/*
 * Register I/O map
 */
#घोषणा C6XDIGIO_DATA_REG	0x00
#घोषणा C6XDIGIO_DATA_CHAN(x)	(((x) + 1) << 4)
#घोषणा C6XDIGIO_DATA_PWM	BIT(5)
#घोषणा C6XDIGIO_DATA_ENCODER	BIT(6)
#घोषणा C6XDIGIO_STATUS_REG	0x01
#घोषणा C6XDIGIO_CTRL_REG	0x02

#घोषणा C6XDIGIO_TIME_OUT 20

अटल पूर्णांक c6xdigio_chk_status(काष्ठा comedi_device *dev, अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक समयout = 0;

	करो अणु
		status = inb(dev->iobase + C6XDIGIO_STATUS_REG);
		अगर ((status & 0x80) != context)
			वापस 0;
		समयout++;
	पूर्ण जबतक  (समयout < C6XDIGIO_TIME_OUT);

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक c6xdigio_ग_लिखो_data(काष्ठा comedi_device *dev,
			       अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक status)
अणु
	outb_p(val, dev->iobase + C6XDIGIO_DATA_REG);
	वापस c6xdigio_chk_status(dev, status);
पूर्ण

अटल पूर्णांक c6xdigio_get_encoder_bits(काष्ठा comedi_device *dev,
				     अचिन्हित पूर्णांक *bits,
				     अचिन्हित पूर्णांक cmd,
				     अचिन्हित पूर्णांक status)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + C6XDIGIO_STATUS_REG);
	val >>= 3;
	val &= 0x07;

	*bits = val;

	वापस c6xdigio_ग_लिखो_data(dev, cmd, status);
पूर्ण

अटल व्योम c6xdigio_pwm_ग_लिखो(काष्ठा comedi_device *dev,
			       अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक cmd = C6XDIGIO_DATA_PWM | C6XDIGIO_DATA_CHAN(chan);
	अचिन्हित पूर्णांक bits;

	अगर (val > 498)
		val = 498;
	अगर (val < 2)
		val = 2;

	bits = (val >> 0) & 0x03;
	c6xdigio_ग_लिखो_data(dev, cmd | bits | (0 << 2), 0x00);
	bits = (val >> 2) & 0x03;
	c6xdigio_ग_लिखो_data(dev, cmd | bits | (1 << 2), 0x80);
	bits = (val >> 4) & 0x03;
	c6xdigio_ग_लिखो_data(dev, cmd | bits | (0 << 2), 0x00);
	bits = (val >> 6) & 0x03;
	c6xdigio_ग_लिखो_data(dev, cmd | bits | (1 << 2), 0x80);
	bits = (val >> 8) & 0x03;
	c6xdigio_ग_लिखो_data(dev, cmd | bits | (0 << 2), 0x00);

	c6xdigio_ग_लिखो_data(dev, 0x00, 0x80);
पूर्ण

अटल पूर्णांक c6xdigio_encoder_पढ़ो(काष्ठा comedi_device *dev,
				 अचिन्हित पूर्णांक chan)
अणु
	अचिन्हित पूर्णांक cmd = C6XDIGIO_DATA_ENCODER | C6XDIGIO_DATA_CHAN(chan);
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक bits;

	c6xdigio_ग_लिखो_data(dev, cmd, 0x00);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (1 << 2), 0x80);
	val |= (bits << 0);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (0 << 2), 0x00);
	val |= (bits << 3);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (1 << 2), 0x80);
	val |= (bits << 6);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (0 << 2), 0x00);
	val |= (bits << 9);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (1 << 2), 0x80);
	val |= (bits << 12);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (0 << 2), 0x00);
	val |= (bits << 15);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (1 << 2), 0x80);
	val |= (bits << 18);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (0 << 2), 0x00);
	val |= (bits << 21);

	c6xdigio_ग_लिखो_data(dev, 0x00, 0x80);

	वापस val;
पूर्ण

अटल पूर्णांक c6xdigio_pwm_insn_ग_लिखो(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = (s->state >> (16 * chan)) & 0xffff;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		c6xdigio_pwm_ग_लिखो(dev, chan, val);
	पूर्ण

	/*
	 * There are only 2 PWM channels and they have a maxdata of 500.
	 * Instead of allocating निजी data to save the values in क्रम
	 * पढ़ोback this driver just packs the values क्रम the two channels
	 * in the s->state.
	 */
	s->state &= (0xffff << (16 * chan));
	s->state |= (val << (16 * chan));

	वापस insn->n;
पूर्ण

अटल पूर्णांक c6xdigio_pwm_insn_पढ़ो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	val = (s->state >> (16 * chan)) & 0xffff;

	क्रम (i = 0; i < insn->n; i++)
		data[i] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक c6xdigio_encoder_insn_पढ़ो(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = c6xdigio_encoder_पढ़ो(dev, chan);

		/* munge two's complement value to offset binary */
		data[i] = comedi_offset_munge(s, val);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम c6xdigio_init(काष्ठा comedi_device *dev)
अणु
	/* Initialize the PWM */
	c6xdigio_ग_लिखो_data(dev, 0x70, 0x00);
	c6xdigio_ग_लिखो_data(dev, 0x74, 0x80);
	c6xdigio_ग_लिखो_data(dev, 0x70, 0x00);
	c6xdigio_ग_लिखो_data(dev, 0x00, 0x80);

	/* Reset the encoders */
	c6xdigio_ग_लिखो_data(dev, 0x68, 0x00);
	c6xdigio_ग_लिखो_data(dev, 0x6c, 0x80);
	c6xdigio_ग_लिखो_data(dev, 0x68, 0x00);
	c6xdigio_ग_लिखो_data(dev, 0x00, 0x80);
पूर्ण

अटल स्थिर काष्ठा pnp_device_id c6xdigio_pnp_tbl[] = अणु
	/* Standard LPT Prपूर्णांकer Port */
	अणु.id = "PNP0400", .driver_data = 0पूर्ण,
	/* ECP Prपूर्णांकer Port */
	अणु.id = "PNP0401", .driver_data = 0पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा pnp_driver c6xdigio_pnp_driver = अणु
	.name = "c6xdigio",
	.id_table = c6xdigio_pnp_tbl,
पूर्ण;

अटल पूर्णांक c6xdigio_attach(काष्ठा comedi_device *dev,
			   काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x03);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	/*  Make sure that PnP ports get activated */
	pnp_रेजिस्टर_driver(&c6xdigio_pnp_driver);

	s = &dev->subdevices[0];
	/* pwm output subdevice */
	s->type		= COMEDI_SUBD_PWM;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 500;
	s->range_table	= &range_unknown;
	s->insn_ग_लिखो	= c6xdigio_pwm_insn_ग_लिखो;
	s->insn_पढ़ो	= c6xdigio_pwm_insn_पढ़ो;

	s = &dev->subdevices[1];
	/* encoder (counter) subdevice */
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_READABLE | SDF_LSAMPL;
	s->n_chan	= 2;
	s->maxdata	= 0xffffff;
	s->range_table	= &range_unknown;
	s->insn_पढ़ो	= c6xdigio_encoder_insn_पढ़ो;

	/*  I will call this init anyway but more than likely the DSP board */
	/*  will not be connected when device driver is loaded. */
	c6xdigio_init(dev);

	वापस 0;
पूर्ण

अटल व्योम c6xdigio_detach(काष्ठा comedi_device *dev)
अणु
	comedi_legacy_detach(dev);
	pnp_unरेजिस्टर_driver(&c6xdigio_pnp_driver);
पूर्ण

अटल काष्ठा comedi_driver c6xdigio_driver = अणु
	.driver_name	= "c6xdigio",
	.module		= THIS_MODULE,
	.attach		= c6xdigio_attach,
	.detach		= c6xdigio_detach,
पूर्ण;
module_comedi_driver(c6xdigio_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for the C6x_DIGIO DSP daughter card");
MODULE_LICENSE("GPL");
