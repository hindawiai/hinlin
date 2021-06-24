<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * pcmda12.c
 * Driver क्रम Winप्रणालीs PC-104 based PCM-D/A-12 8-channel AO board.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2006 Calin A. Culianu <calin@ajvar.org>
 */

/*
 * Driver: pcmda12
 * Description: A driver क्रम the Winप्रणालीs PCM-D/A-12
 * Devices: [Winप्रणालीs] PCM-D/A-12 (pcmda12)
 * Author: Calin Culianu <calin@ajvar.org>
 * Updated: Fri, 13 Jan 2006 12:01:01 -0500
 * Status: works
 *
 * A driver क्रम the relatively straightक्रमward-to-program PCM-D/A-12.
 * This board करोesn't support commands, and the only way to set its
 * analog output range is to jumper the board. As such,
 * comedi_data_ग_लिखो() ignores the range value specअगरied.
 *
 * The board uses 16 consecutive I/O addresses starting at the I/O port
 * base address. Each address corresponds to the LSB then MSB of a
 * particular channel from 0-7.
 *
 * Note that the board is not ISA-PNP capable and thus needs the I/O
 * port comedi_config parameter.
 *
 * Note that passing a nonzero value as the second config option will
 * enable "simultaneous xfer" mode क्रम this board, in which AO ग_लिखोs
 * will not take effect until a subsequent पढ़ो of any AO channel. This
 * is so that one can speed up programming by preloading all AO रेजिस्टरs
 * with values beक्रमe simultaneously setting them to take effect with one
 * पढ़ो command.
 *
 * Configuration Options:
 *   [0] - I/O port base address
 *   [1] - Do Simultaneous Xfer (see description)
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

/* AI range is not configurable, it's set by jumpers on the board */
अटल स्थिर काष्ठा comedi_lrange pcmda12_ranges = अणु
	3, अणु
		UNI_RANGE(5),
		UNI_RANGE(10),
		BIP_RANGE(5)
	पूर्ण
पूर्ण;

काष्ठा pcmda12_निजी अणु
	पूर्णांक simultaneous_xfer_mode;
पूर्ण;

अटल पूर्णांक pcmda12_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pcmda12_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	अचिन्हित दीर्घ ioreg = dev->iobase + (chan * 2);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; ++i) अणु
		val = data[i];
		outb(val & 0xff, ioreg);
		outb((val >> 8) & 0xff, ioreg + 1);

		/*
		 * Initiate transfer अगर not in simultaneaous xfer
		 * mode by पढ़ोing one of the AO रेजिस्टरs.
		 */
		अगर (!devpriv->simultaneous_xfer_mode)
			inb(ioreg);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcmda12_ao_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pcmda12_निजी *devpriv = dev->निजी;

	/*
	 * Initiate simultaneaous xfer mode by पढ़ोing one of the
	 * AO रेजिस्टरs. All analog outमाला_दो will then be updated.
	 */
	अगर (devpriv->simultaneous_xfer_mode)
		inb(dev->iobase);

	वापस comedi_पढ़ोback_insn_पढ़ो(dev, s, insn, data);
पूर्ण

अटल व्योम pcmda12_ao_reset(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < s->n_chan; ++i) अणु
		outb(0, dev->iobase + (i * 2));
		outb(0, dev->iobase + (i * 2) + 1);
	पूर्ण
	/* Initiate transfer by पढ़ोing one of the AO रेजिस्टरs. */
	inb(dev->iobase);
पूर्ण

अटल पूर्णांक pcmda12_attach(काष्ठा comedi_device *dev,
			  काष्ठा comedi_devconfig *it)
अणु
	काष्ठा pcmda12_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	devpriv->simultaneous_xfer_mode = it->options[1];

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 0x0fff;
	s->range_table	= &pcmda12_ranges;
	s->insn_ग_लिखो	= pcmda12_ao_insn_ग_लिखो;
	s->insn_पढ़ो	= pcmda12_ao_insn_पढ़ो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	pcmda12_ao_reset(dev, s);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pcmda12_driver = अणु
	.driver_name	= "pcmda12",
	.module		= THIS_MODULE,
	.attach		= pcmda12_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(pcmda12_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
