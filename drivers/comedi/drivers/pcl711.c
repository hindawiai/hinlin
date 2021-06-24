<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * pcl711.c
 * Comedi driver क्रम PC-LabCard PCL-711 and AdSys ACL-8112 and compatibles
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 *		      Janne Jalkanen <jalkanen@cs.hut.fi>
 *		      Eric Bunn <ebu@cs.hut.fi>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: pcl711
 * Description: Advantech PCL-711 and 711b, ADLink ACL-8112
 * Devices: [Advantech] PCL-711 (pcl711), PCL-711B (pcl711b),
 *   [ADLink] ACL-8112HG (acl8112hg), ACL-8112DG (acl8112dg)
 * Author: David A. Schleef <ds@schleef.org>
 *	   Janne Jalkanen <jalkanen@cs.hut.fi>
 *	   Eric Bunn <ebu@cs.hut.fi>
 * Updated:
 * Status: mostly complete
 *
 * Configuration Options:
 *   [0] - I/O port base
 *   [1] - IRQ, optional
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

#समावेश "comedi_8254.h"

/*
 * I/O port रेजिस्टर map
 */
#घोषणा PCL711_TIMER_BASE	0x00
#घोषणा PCL711_AI_LSB_REG	0x04
#घोषणा PCL711_AI_MSB_REG	0x05
#घोषणा PCL711_AI_MSB_DRDY	BIT(4)
#घोषणा PCL711_AO_LSB_REG(x)	(0x04 + ((x) * 2))
#घोषणा PCL711_AO_MSB_REG(x)	(0x05 + ((x) * 2))
#घोषणा PCL711_DI_LSB_REG	0x06
#घोषणा PCL711_DI_MSB_REG	0x07
#घोषणा PCL711_INT_STAT_REG	0x08
#घोषणा PCL711_INT_STAT_CLR	(0 << 0)  /* any value will work */
#घोषणा PCL711_AI_GAIN_REG	0x09
#घोषणा PCL711_AI_GAIN(x)	(((x) & 0xf) << 0)
#घोषणा PCL711_MUX_REG		0x0a
#घोषणा PCL711_MUX_CHAN(x)	(((x) & 0xf) << 0)
#घोषणा PCL711_MUX_CS0		BIT(4)
#घोषणा PCL711_MUX_CS1		BIT(5)
#घोषणा PCL711_MUX_DIFF		(PCL711_MUX_CS0 | PCL711_MUX_CS1)
#घोषणा PCL711_MODE_REG		0x0b
#घोषणा PCL711_MODE(x)		(((x) & 0x7) << 0)
#घोषणा PCL711_MODE_DEFAULT	PCL711_MODE(0)
#घोषणा PCL711_MODE_SOFTTRIG	PCL711_MODE(1)
#घोषणा PCL711_MODE_EXT		PCL711_MODE(2)
#घोषणा PCL711_MODE_EXT_IRQ	PCL711_MODE(3)
#घोषणा PCL711_MODE_PACER	PCL711_MODE(4)
#घोषणा PCL711_MODE_PACER_IRQ	PCL711_MODE(6)
#घोषणा PCL711_MODE_IRQ(x)	(((x) & 0x7) << 4)
#घोषणा PCL711_SOFTTRIG_REG	0x0c
#घोषणा PCL711_SOFTTRIG		(0 << 0)  /* any value will work */
#घोषणा PCL711_DO_LSB_REG	0x0d
#घोषणा PCL711_DO_MSB_REG	0x0e

अटल स्थिर काष्ठा comedi_lrange range_pcl711b_ai = अणु
	5, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		BIP_RANGE(0.3125)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_acl8112hg_ai = अणु
	12, अणु
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05),
		BIP_RANGE(0.005),
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.01),
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_acl8112dg_ai = अणु
	9, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

काष्ठा pcl711_board अणु
	स्थिर अक्षर *name;
	पूर्णांक n_aichan;
	पूर्णांक n_aochan;
	पूर्णांक maxirq;
	स्थिर काष्ठा comedi_lrange *ai_range_type;
पूर्ण;

अटल स्थिर काष्ठा pcl711_board boardtypes[] = अणु
	अणु
		.name		= "pcl711",
		.n_aichan	= 8,
		.n_aochan	= 1,
		.ai_range_type	= &range_bipolar5,
	पूर्ण, अणु
		.name		= "pcl711b",
		.n_aichan	= 8,
		.n_aochan	= 1,
		.maxirq		= 7,
		.ai_range_type	= &range_pcl711b_ai,
	पूर्ण, अणु
		.name		= "acl8112hg",
		.n_aichan	= 16,
		.n_aochan	= 2,
		.maxirq		= 15,
		.ai_range_type	= &range_acl8112hg_ai,
	पूर्ण, अणु
		.name		= "acl8112dg",
		.n_aichan	= 16,
		.n_aochan	= 2,
		.maxirq		= 15,
		.ai_range_type	= &range_acl8112dg_ai,
	पूर्ण,
पूर्ण;

अटल व्योम pcl711_ai_set_mode(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक mode)
अणु
	/*
	 * The pcl711b board uses bits in the mode रेजिस्टर to select the
	 * पूर्णांकerrupt. The other boards supported by this driver all use
	 * jumpers on the board.
	 *
	 * Enables the पूर्णांकerrupt when needed on the pcl711b board. These
	 * bits करो nothing on the other boards.
	 */
	अगर (mode == PCL711_MODE_EXT_IRQ || mode == PCL711_MODE_PACER_IRQ)
		mode |= PCL711_MODE_IRQ(dev->irq);

	outb(mode, dev->iobase + PCL711_MODE_REG);
पूर्ण

अटल अचिन्हित पूर्णांक pcl711_ai_get_sample(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + PCL711_AI_MSB_REG) << 8;
	val |= inb(dev->iobase + PCL711_AI_LSB_REG);

	वापस val & s->maxdata;
पूर्ण

अटल पूर्णांक pcl711_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	outb(PCL711_INT_STAT_CLR, dev->iobase + PCL711_INT_STAT_REG);
	pcl711_ai_set_mode(dev, PCL711_MODE_SOFTTRIG);
	वापस 0;
पूर्ण

अटल irqवापस_t pcl711_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित लघु data;

	अगर (!dev->attached) अणु
		dev_err(dev->class_dev, "spurious interrupt\n");
		वापस IRQ_HANDLED;
	पूर्ण

	data = pcl711_ai_get_sample(dev, s);

	outb(PCL711_INT_STAT_CLR, dev->iobase + PCL711_INT_STAT_REG);

	comedi_buf_ग_लिखो_samples(s, &data, 1);

	अगर (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_करोne >= cmd->stop_arg)
		s->async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pcl711_set_changain(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				अचिन्हित पूर्णांक chanspec)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(chanspec);
	अचिन्हित पूर्णांक mux = 0;

	outb(PCL711_AI_GAIN(range), dev->iobase + PCL711_AI_GAIN_REG);

	अगर (s->n_chan > 8) अणु
		/* Select the correct MPC508A chip */
		अगर (aref == AREF_DIFF) अणु
			chan &= 0x7;
			mux |= PCL711_MUX_DIFF;
		पूर्ण अन्यथा अणु
			अगर (chan < 8)
				mux |= PCL711_MUX_CS0;
			अन्यथा
				mux |= PCL711_MUX_CS1;
		पूर्ण
	पूर्ण
	outb(mux | PCL711_MUX_CHAN(chan), dev->iobase + PCL711_MUX_REG);
पूर्ण

अटल पूर्णांक pcl711_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + PCL711_AI_MSB_REG);
	अगर ((status & PCL711_AI_MSB_DRDY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pcl711_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	pcl711_set_changain(dev, s, insn->chanspec);

	pcl711_ai_set_mode(dev, PCL711_MODE_SOFTTRIG);

	क्रम (i = 0; i < insn->n; i++) अणु
		outb(PCL711_SOFTTRIG, dev->iobase + PCL711_SOFTTRIG_REG);

		ret = comedi_समयout(dev, s, insn, pcl711_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		data[i] = pcl711_ai_get_sample(dev, s);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl711_ai_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_EXT) अणु
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	पूर्ण अन्यथा अणु
#घोषणा MAX_SPEED 1000
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    MAX_SPEED);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4 */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		अचिन्हित पूर्णांक arg = cmd->scan_begin_arg;

		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक pcl711_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	pcl711_set_changain(dev, s, cmd->chanlist[0]);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		comedi_8254_update_भागisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
		outb(PCL711_INT_STAT_CLR, dev->iobase + PCL711_INT_STAT_REG);
		pcl711_ai_set_mode(dev, PCL711_MODE_PACER_IRQ);
	पूर्ण अन्यथा अणु
		pcl711_ai_set_mode(dev, PCL711_MODE_EXT_IRQ);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pcl711_ao_ग_लिखो(काष्ठा comedi_device *dev,
			    अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक val)
अणु
	outb(val & 0xff, dev->iobase + PCL711_AO_LSB_REG(chan));
	outb((val >> 8) & 0xff, dev->iobase + PCL711_AO_MSB_REG(chan));
पूर्ण

अटल पूर्णांक pcl711_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		pcl711_ao_ग_लिखो(dev, chan, val);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl711_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + PCL711_DI_LSB_REG);
	val |= (inb(dev->iobase + PCL711_DI_MSB_REG) << 8);

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl711_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक mask;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (mask & 0x00ff)
			outb(s->state & 0xff, dev->iobase + PCL711_DO_LSB_REG);
		अगर (mask & 0xff00)
			outb((s->state >> 8), dev->iobase + PCL711_DO_MSB_REG);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl711_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcl711_board *board = dev->board_ptr;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	अगर (it->options[1] && it->options[1] <= board->maxirq) अणु
		ret = request_irq(it->options[1], pcl711_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	dev->pacer = comedi_8254_init(dev->iobase + PCL711_TIMER_BASE,
				      I8254_OSC_BASE_2MHZ, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND;
	अगर (board->n_aichan > 8)
		s->subdev_flags	|= SDF_DIFF;
	s->n_chan	= board->n_aichan;
	s->maxdata	= 0xfff;
	s->range_table	= board->ai_range_type;
	s->insn_पढ़ो	= pcl711_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= 1;
		s->करो_cmdtest	= pcl711_ai_cmdtest;
		s->करो_cmd	= pcl711_ai_cmd;
		s->cancel	= pcl711_ai_cancel;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= board->n_aochan;
	s->maxdata	= 0xfff;
	s->range_table	= &range_bipolar5;
	s->insn_ग_लिखो	= pcl711_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcl711_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcl711_करो_insn_bits;

	/* clear DAC */
	pcl711_ao_ग_लिखो(dev, 0, 0x0);
	pcl711_ao_ग_लिखो(dev, 1, 0x0);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pcl711_driver = अणु
	.driver_name	= "pcl711",
	.module		= THIS_MODULE,
	.attach		= pcl711_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &boardtypes[0].name,
	.num_names	= ARRAY_SIZE(boardtypes),
	.offset		= माप(काष्ठा pcl711_board),
पूर्ण;
module_comedi_driver(pcl711_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for PCL-711 compatible boards");
MODULE_LICENSE("GPL");
