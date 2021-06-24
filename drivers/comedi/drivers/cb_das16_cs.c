<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * cb_das16_cs.c
 * Driver क्रम Computer Boards PC-CARD DAS16/16.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000, 2001, 2002 David A. Schleef <ds@schleef.org>
 *
 * PCMCIA support code क्रम this driver is adapted from the dummy_cs.c
 * driver of the Linux PCMCIA Card Services package.
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 */

/*
 * Driver: cb_das16_cs
 * Description: Computer Boards PC-CARD DAS16/16
 * Devices: [ComputerBoards] PC-CARD DAS16/16 (cb_das16_cs),
 *   PC-CARD DAS16/16-AO
 * Author: ds
 * Updated: Mon, 04 Nov 2002 20:04:21 -0800
 * Status: experimental
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>

#समावेश "../comedi_pcmcia.h"

#समावेश "comedi_8254.h"

/*
 * Register I/O map
 */
#घोषणा DAS16CS_AI_DATA_REG		0x00
#घोषणा DAS16CS_AI_MUX_REG		0x02
#घोषणा DAS16CS_AI_MUX_HI_CHAN(x)	(((x) & 0xf) << 4)
#घोषणा DAS16CS_AI_MUX_LO_CHAN(x)	(((x) & 0xf) << 0)
#घोषणा DAS16CS_AI_MUX_SINGLE_CHAN(x)	(DAS16CS_AI_MUX_HI_CHAN(x) |	\
					 DAS16CS_AI_MUX_LO_CHAN(x))
#घोषणा DAS16CS_MISC1_REG		0x04
#घोषणा DAS16CS_MISC1_INTE		BIT(15)	/* 1=enable; 0=disable */
#घोषणा DAS16CS_MISC1_INT_SRC(x)	(((x) & 0x7) << 12) /* पूर्णांकerrupt src */
#घोषणा DAS16CS_MISC1_INT_SRC_NONE	DAS16CS_MISC1_INT_SRC(0)
#घोषणा DAS16CS_MISC1_INT_SRC_PACER	DAS16CS_MISC1_INT_SRC(1)
#घोषणा DAS16CS_MISC1_INT_SRC_EXT	DAS16CS_MISC1_INT_SRC(2)
#घोषणा DAS16CS_MISC1_INT_SRC_FNE	DAS16CS_MISC1_INT_SRC(3)
#घोषणा DAS16CS_MISC1_INT_SRC_FHF	DAS16CS_MISC1_INT_SRC(4)
#घोषणा DAS16CS_MISC1_INT_SRC_EOS	DAS16CS_MISC1_INT_SRC(5)
#घोषणा DAS16CS_MISC1_INT_SRC_MASK	DAS16CS_MISC1_INT_SRC(7)
#घोषणा DAS16CS_MISC1_OVR		BIT(10)	/* ro - 1=FIFO overflow */
#घोषणा DAS16CS_MISC1_AI_CONV(x)	(((x) & 0x3) << 8) /* AI convert src */
#घोषणा DAS16CS_MISC1_AI_CONV_SW	DAS16CS_MISC1_AI_CONV(0)
#घोषणा DAS16CS_MISC1_AI_CONV_EXT_NEG	DAS16CS_MISC1_AI_CONV(1)
#घोषणा DAS16CS_MISC1_AI_CONV_EXT_POS	DAS16CS_MISC1_AI_CONV(2)
#घोषणा DAS16CS_MISC1_AI_CONV_PACER	DAS16CS_MISC1_AI_CONV(3)
#घोषणा DAS16CS_MISC1_AI_CONV_MASK	DAS16CS_MISC1_AI_CONV(3)
#घोषणा DAS16CS_MISC1_EOC		BIT(7)	/* ro - 0=busy; 1=पढ़ोy */
#घोषणा DAS16CS_MISC1_SEDIFF		BIT(5)	/* 0=dअगरf; 1=se */
#घोषणा DAS16CS_MISC1_INTB		BIT(4)	/* ro - 0=latched; 1=cleared */
#घोषणा DAS16CS_MISC1_MA_MASK		(0xf << 0) /* ro - current ai mux */
#घोषणा DAS16CS_MISC1_DAC1CS		BIT(3)	/* wo - DAC1 chip select */
#घोषणा DAS16CS_MISC1_DACCLK		BIT(2)	/* wo - Serial DAC घड़ी */
#घोषणा DAS16CS_MISC1_DACSD		BIT(1)	/* wo - Serial DAC data */
#घोषणा DAS16CS_MISC1_DAC0CS		BIT(0)	/* wo - DAC0 chip select */
#घोषणा DAS16CS_MISC1_DAC_MASK		(0x0f << 0)
#घोषणा DAS16CS_MISC2_REG		0x06
#घोषणा DAS16CS_MISC2_BME		BIT(14)	/* 1=burst enable; 0=disable */
#घोषणा DAS16CS_MISC2_AI_GAIN(x)	(((x) & 0xf) << 8) /* AI gain */
#घोषणा DAS16CS_MISC2_AI_GAIN_1		DAS16CS_MISC2_AI_GAIN(4) /* +/-10V */
#घोषणा DAS16CS_MISC2_AI_GAIN_2		DAS16CS_MISC2_AI_GAIN(0) /* +/-5V */
#घोषणा DAS16CS_MISC2_AI_GAIN_4		DAS16CS_MISC2_AI_GAIN(1) /* +/-2.5V */
#घोषणा DAS16CS_MISC2_AI_GAIN_8		DAS16CS_MISC2_AI_GAIN(2) /* +-1.25V */
#घोषणा DAS16CS_MISC2_AI_GAIN_MASK	DAS16CS_MISC2_AI_GAIN(0xf)
#घोषणा DAS16CS_MISC2_Uसूची		BIT(7)	/* 1=dio7:4 output; 0=input */
#घोषणा DAS16CS_MISC2_Lसूची		BIT(6)	/* 1=dio3:0 output; 0=input */
#घोषणा DAS16CS_MISC2_TRGPOL		BIT(5)	/* 1=active lo; 0=hi */
#घोषणा DAS16CS_MISC2_TRGSEL		BIT(4)	/* 1=edge; 0=level */
#घोषणा DAS16CS_MISC2_FFNE		BIT(3)	/* ro - 1=FIFO not empty */
#घोषणा DAS16CS_MISC2_TRGCLR		BIT(3)	/* wo - 1=clr (monstable) */
#घोषणा DAS16CS_MISC2_CLK2		BIT(2)	/* 1=10 MHz; 0=1 MHz */
#घोषणा DAS16CS_MISC2_CTR1		BIT(1)	/* 1=पूर्णांक. 100 kHz; 0=ext. clk */
#घोषणा DAS16CS_MISC2_TRG0		BIT(0)	/* 1=enable; 0=disable */
#घोषणा DAS16CS_TIMER_BASE		0x08
#घोषणा DAS16CS_DIO_REG			0x10

काष्ठा das16cs_board अणु
	स्थिर अक्षर *name;
	पूर्णांक device_id;
	अचिन्हित पूर्णांक has_ao:1;
	अचिन्हित पूर्णांक has_4dio:1;
पूर्ण;

अटल स्थिर काष्ठा das16cs_board das16cs_boards[] = अणु
	अणु
		.name		= "PC-CARD DAS16/16-AO",
		.device_id	= 0x0039,
		.has_ao		= 1,
		.has_4dio	= 1,
	पूर्ण, अणु
		.name		= "PCM-DAS16s/16",
		.device_id	= 0x4009,
	पूर्ण, अणु
		.name		= "PC-CARD DAS16/16",
		.device_id	= 0x0000,	/* unknown */
	पूर्ण,
पूर्ण;

काष्ठा das16cs_निजी अणु
	अचिन्हित लघु misc1;
	अचिन्हित लघु misc2;
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange das16cs_ai_range = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
	पूर्ण
पूर्ण;

अटल पूर्णांक das16cs_ai_eoc(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + DAS16CS_MISC1_REG);
	अगर (status & DAS16CS_MISC1_EOC)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक das16cs_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा das16cs_निजी *devpriv = dev->निजी;
	पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक aref = CR_AREF(insn->chanspec);
	पूर्णांक ret;
	पूर्णांक i;

	outw(DAS16CS_AI_MUX_SINGLE_CHAN(chan),
	     dev->iobase + DAS16CS_AI_MUX_REG);

	/* disable पूर्णांकerrupts, software convert */
	devpriv->misc1 &= ~(DAS16CS_MISC1_INTE | DAS16CS_MISC1_INT_SRC_MASK |
			      DAS16CS_MISC1_AI_CONV_MASK);
	अगर (aref == AREF_DIFF)
		devpriv->misc1 &= ~DAS16CS_MISC1_SEDIFF;
	अन्यथा
		devpriv->misc1 |= DAS16CS_MISC1_SEDIFF;
	outw(devpriv->misc1, dev->iobase + DAS16CS_MISC1_REG);

	devpriv->misc2 &= ~(DAS16CS_MISC2_BME | DAS16CS_MISC2_AI_GAIN_MASK);
	चयन (range) अणु
	हाल 0:
		devpriv->misc2 |= DAS16CS_MISC2_AI_GAIN_1;
		अवरोध;
	हाल 1:
		devpriv->misc2 |= DAS16CS_MISC2_AI_GAIN_2;
		अवरोध;
	हाल 2:
		devpriv->misc2 |= DAS16CS_MISC2_AI_GAIN_4;
		अवरोध;
	हाल 3:
		devpriv->misc2 |= DAS16CS_MISC2_AI_GAIN_8;
		अवरोध;
	पूर्ण
	outw(devpriv->misc2, dev->iobase + DAS16CS_MISC2_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		outw(0, dev->iobase + DAS16CS_AI_DATA_REG);

		ret = comedi_समयout(dev, s, insn, das16cs_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		data[i] = inw(dev->iobase + DAS16CS_AI_DATA_REG);
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक das16cs_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा das16cs_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	अचिन्हित लघु misc1;
	पूर्णांक bit;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];

		outw(devpriv->misc1, dev->iobase + DAS16CS_MISC1_REG);
		udelay(1);

		/* उठाओ the DACxCS line क्रम the non-selected channel */
		misc1 = devpriv->misc1 & ~DAS16CS_MISC1_DAC_MASK;
		अगर (chan)
			misc1 |= DAS16CS_MISC1_DAC0CS;
		अन्यथा
			misc1 |= DAS16CS_MISC1_DAC1CS;

		outw(misc1, dev->iobase + DAS16CS_MISC1_REG);
		udelay(1);

		क्रम (bit = 15; bit >= 0; bit--) अणु
			अगर ((val >> bit) & 0x1)
				misc1 |= DAS16CS_MISC1_DACSD;
			अन्यथा
				misc1 &= ~DAS16CS_MISC1_DACSD;
			outw(misc1, dev->iobase + DAS16CS_MISC1_REG);
			udelay(1);
			outw(misc1 | DAS16CS_MISC1_DACCLK,
			     dev->iobase + DAS16CS_MISC1_REG);
			udelay(1);
		पूर्ण
		/*
		 * Make both DAC0CS and DAC1CS high to load
		 * the new data and update analog the output
		 */
		outw(misc1 | DAS16CS_MISC1_DAC0CS | DAS16CS_MISC1_DAC1CS,
		     dev->iobase + DAS16CS_MISC1_REG);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक das16cs_dio_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + DAS16CS_DIO_REG);

	data[1] = inw(dev->iobase + DAS16CS_DIO_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक das16cs_dio_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा das16cs_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 4)
		mask = 0x0f;
	अन्यथा
		mask = 0xf0;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	अगर (s->io_bits & 0xf0)
		devpriv->misc2 |= DAS16CS_MISC2_Uसूची;
	अन्यथा
		devpriv->misc2 &= ~DAS16CS_MISC2_Uसूची;
	अगर (s->io_bits & 0x0f)
		devpriv->misc2 |= DAS16CS_MISC2_Lसूची;
	अन्यथा
		devpriv->misc2 &= ~DAS16CS_MISC2_Lसूची;
	outw(devpriv->misc2, dev->iobase + DAS16CS_MISC2_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक das16cs_counter_insn_config(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_insn *insn,
				       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा das16cs_निजी *devpriv = dev->निजी;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		चयन (data[1]) अणु
		हाल 0:	/* पूर्णांकernal 100 kHz */
			devpriv->misc2 |= DAS16CS_MISC2_CTR1;
			अवरोध;
		हाल 1:	/* बाह्यal */
			devpriv->misc2 &= ~DAS16CS_MISC2_CTR1;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		outw(devpriv->misc2, dev->iobase + DAS16CS_MISC2_REG);
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		अगर (devpriv->misc2 & DAS16CS_MISC2_CTR1) अणु
			data[1] = 0;
			data[2] = I8254_OSC_BASE_100KHZ;
		पूर्ण अन्यथा अणु
			data[1] = 1;
			data[2] = 0;	/* unknown */
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल स्थिर व्योम *das16cs_find_boardinfo(काष्ठा comedi_device *dev,
					  काष्ठा pcmcia_device *link)
अणु
	स्थिर काष्ठा das16cs_board *board;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(das16cs_boards); i++) अणु
		board = &das16cs_boards[i];
		अगर (board->device_id == link->card_id)
			वापस board;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक das16cs_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	स्थिर काष्ठा das16cs_board *board;
	काष्ठा das16cs_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	board = das16cs_find_boardinfo(dev, link);
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	link->config_flags |= CONF_AUTO_SET_IO | CONF_ENABLE_IRQ;
	ret = comedi_pcmcia_enable(dev, शून्य);
	अगर (ret)
		वापस ret;
	dev->iobase = link->resource[0]->start;

	link->priv = dev;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	dev->pacer = comedi_8254_init(dev->iobase + DAS16CS_TIMER_BASE,
				      I8254_OSC_BASE_10MHZ, I8254_IO16, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= 0xffff;
	s->range_table	= &das16cs_ai_range;
	s->insn_पढ़ो	= das16cs_ai_insn_पढ़ो;

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= 2;
		s->maxdata	= 0xffff;
		s->range_table	= &range_bipolar10;
		s->insn_ग_लिखो	= &das16cs_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Digital I/O subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= board->has_4dio ? 4 : 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das16cs_dio_insn_bits;
	s->insn_config	= das16cs_dio_insn_config;

	/* Counter subdevice (8254) */
	s = &dev->subdevices[3];
	comedi_8254_subdevice_init(s, dev->pacer);

	dev->pacer->insn_config = das16cs_counter_insn_config;

	/* counters 1 and 2 are used पूर्णांकernally क्रम the pacer */
	comedi_8254_set_busy(dev->pacer, 1, true);
	comedi_8254_set_busy(dev->pacer, 2, true);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver driver_das16cs = अणु
	.driver_name	= "cb_das16_cs",
	.module		= THIS_MODULE,
	.स्वतः_attach	= das16cs_स्वतः_attach,
	.detach		= comedi_pcmcia_disable,
पूर्ण;

अटल पूर्णांक das16cs_pcmcia_attach(काष्ठा pcmcia_device *link)
अणु
	वापस comedi_pcmcia_स्वतः_config(link, &driver_das16cs);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id das16cs_id_table[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x01c5, 0x0039),
	PCMCIA_DEVICE_MANF_CARD(0x01c5, 0x4009),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, das16cs_id_table);

अटल काष्ठा pcmcia_driver das16cs_driver = अणु
	.name		= "cb_das16_cs",
	.owner		= THIS_MODULE,
	.id_table	= das16cs_id_table,
	.probe		= das16cs_pcmcia_attach,
	.हटाओ		= comedi_pcmcia_स्वतः_unconfig,
पूर्ण;
module_comedi_pcmcia_driver(driver_das16cs, das16cs_driver);

MODULE_AUTHOR("David A. Schleef <ds@schleef.org>");
MODULE_DESCRIPTION("Comedi driver for Computer Boards PC-CARD DAS16/16");
MODULE_LICENSE("GPL");
