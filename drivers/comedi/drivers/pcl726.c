<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * pcl726.c
 * Comedi driver क्रम 6/12-Channel D/A Output and DIO cards
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: pcl726
 * Description: Advantech PCL-726 & compatibles
 * Author: David A. Schleef <ds@schleef.org>
 * Status: untested
 * Devices: [Advantech] PCL-726 (pcl726), PCL-727 (pcl727), PCL-728 (pcl728),
 *   [ADLink] ACL-6126 (acl6126), ACL-6128 (acl6128)
 *
 * Configuration Options:
 *   [0]  - IO Base
 *   [1]  - IRQ (ACL-6126 only)
 *   [2]  - D/A output range क्रम channel 0
 *   [3]  - D/A output range क्रम channel 1
 *
 * Boards with > 2 analog output channels:
 *   [4]  - D/A output range क्रम channel 2
 *   [5]  - D/A output range क्रम channel 3
 *   [6]  - D/A output range क्रम channel 4
 *   [7]  - D/A output range क्रम channel 5
 *
 * Boards with > 6 analog output channels:
 *   [8]  - D/A output range क्रम channel 6
 *   [9]  - D/A output range क्रम channel 7
 *   [10] - D/A output range क्रम channel 8
 *   [11] - D/A output range क्रम channel 9
 *   [12] - D/A output range क्रम channel 10
 *   [13] - D/A output range क्रम channel 11
 *
 * For PCL-726 the D/A output ranges are:
 *   0: 0-5V, 1: 0-10V, 2: +/-5V, 3: +/-10V, 4: 4-20mA, 5: unknown
 *
 * For PCL-727:
 *   0: 0-5V, 1: 0-10V, 2: +/-5V, 3: 4-20mA
 *
 * For PCL-728 and ACL-6128:
 *   0: 0-5V, 1: 0-10V, 2: +/-5V, 3: +/-10V, 4: 4-20mA, 5: 0-20mA
 *
 * For ACL-6126:
 *   0: 0-5V, 1: 0-10V, 2: +/-5V, 3: +/-10V, 4: 4-20mA
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

#घोषणा PCL726_AO_MSB_REG(x)	(0x00 + ((x) * 2))
#घोषणा PCL726_AO_LSB_REG(x)	(0x01 + ((x) * 2))
#घोषणा PCL726_DO_MSB_REG	0x0c
#घोषणा PCL726_DO_LSB_REG	0x0d
#घोषणा PCL726_DI_MSB_REG	0x0e
#घोषणा PCL726_DI_LSB_REG	0x0f

#घोषणा PCL727_DI_MSB_REG	0x00
#घोषणा PCL727_DI_LSB_REG	0x01
#घोषणा PCL727_DO_MSB_REG	0x18
#घोषणा PCL727_DO_LSB_REG	0x19

अटल स्थिर काष्ठा comedi_lrange *स्थिर rangelist_726[] = अणु
	&range_unipolar5,
	&range_unipolar10,
	&range_bipolar5,
	&range_bipolar10,
	&range_4_20mA,
	&range_unknown
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *स्थिर rangelist_727[] = अणु
	&range_unipolar5,
	&range_unipolar10,
	&range_bipolar5,
	&range_4_20mA
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *स्थिर rangelist_728[] = अणु
	&range_unipolar5,
	&range_unipolar10,
	&range_bipolar5,
	&range_bipolar10,
	&range_4_20mA,
	&range_0_20mA
पूर्ण;

काष्ठा pcl726_board अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ io_len;
	अचिन्हित पूर्णांक irq_mask;
	स्थिर काष्ठा comedi_lrange *स्थिर *ao_ranges;
	पूर्णांक ao_num_ranges;
	पूर्णांक ao_nchan;
	अचिन्हित पूर्णांक have_dio:1;
	अचिन्हित पूर्णांक is_pcl727:1;
पूर्ण;

अटल स्थिर काष्ठा pcl726_board pcl726_boards[] = अणु
	अणु
		.name		= "pcl726",
		.io_len		= 0x10,
		.ao_ranges	= &rangelist_726[0],
		.ao_num_ranges	= ARRAY_SIZE(rangelist_726),
		.ao_nchan	= 6,
		.have_dio	= 1,
	पूर्ण, अणु
		.name		= "pcl727",
		.io_len		= 0x20,
		.ao_ranges	= &rangelist_727[0],
		.ao_num_ranges	= ARRAY_SIZE(rangelist_727),
		.ao_nchan	= 12,
		.have_dio	= 1,
		.is_pcl727	= 1,
	पूर्ण, अणु
		.name		= "pcl728",
		.io_len		= 0x08,
		.ao_num_ranges	= ARRAY_SIZE(rangelist_728),
		.ao_ranges	= &rangelist_728[0],
		.ao_nchan	= 2,
	पूर्ण, अणु
		.name		= "acl6126",
		.io_len		= 0x10,
		.irq_mask	= 0x96e8,
		.ao_num_ranges	= ARRAY_SIZE(rangelist_726),
		.ao_ranges	= &rangelist_726[0],
		.ao_nchan	= 6,
		.have_dio	= 1,
	पूर्ण, अणु
		.name		= "acl6128",
		.io_len		= 0x08,
		.ao_num_ranges	= ARRAY_SIZE(rangelist_728),
		.ao_ranges	= &rangelist_728[0],
		.ao_nchan	= 2,
	पूर्ण,
पूर्ण;

काष्ठा pcl726_निजी अणु
	स्थिर काष्ठा comedi_lrange *rangelist[12];
	अचिन्हित पूर्णांक cmd_running:1;
पूर्ण;

अटल पूर्णांक pcl726_पूर्णांकr_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	data[1] = 0;
	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl726_पूर्णांकr_cmdtest(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */

	वापस 0;
पूर्ण

अटल पूर्णांक pcl726_पूर्णांकr_cmd(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl726_निजी *devpriv = dev->निजी;

	devpriv->cmd_running = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pcl726_पूर्णांकr_cancel(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl726_निजी *devpriv = dev->निजी;

	devpriv->cmd_running = 0;

	वापस 0;
पूर्ण

अटल irqवापस_t pcl726_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा pcl726_निजी *devpriv = dev->निजी;

	अगर (devpriv->cmd_running) अणु
		अचिन्हित लघु val = 0;

		pcl726_पूर्णांकr_cancel(dev, s);

		comedi_buf_ग_लिखो_samples(s, &val, 1);
		comedi_handle_events(dev, s);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pcl726_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		s->पढ़ोback[chan] = val;

		/* bipolar data to the DAC is two's complement */
		अगर (comedi_chan_range_is_bipolar(s, chan, range))
			val = comedi_offset_munge(s, val);

		/* order is important, MSB then LSB */
		outb((val >> 8) & 0xff, dev->iobase + PCL726_AO_MSB_REG(chan));
		outb(val & 0xff, dev->iobase + PCL726_AO_LSB_REG(chan));
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl726_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा pcl726_board *board = dev->board_ptr;
	अचिन्हित पूर्णांक val;

	अगर (board->is_pcl727) अणु
		val = inb(dev->iobase + PCL727_DI_LSB_REG);
		val |= (inb(dev->iobase + PCL727_DI_MSB_REG) << 8);
	पूर्ण अन्यथा अणु
		val = inb(dev->iobase + PCL726_DI_LSB_REG);
		val |= (inb(dev->iobase + PCL726_DI_MSB_REG) << 8);
	पूर्ण

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl726_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा pcl726_board *board = dev->board_ptr;
	अचिन्हित दीर्घ io = dev->iobase;
	अचिन्हित पूर्णांक mask;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (board->is_pcl727) अणु
			अगर (mask & 0x00ff)
				outb(s->state & 0xff, io + PCL727_DO_LSB_REG);
			अगर (mask & 0xff00)
				outb((s->state >> 8), io + PCL727_DO_MSB_REG);
		पूर्ण अन्यथा अणु
			अगर (mask & 0x00ff)
				outb(s->state & 0xff, io + PCL726_DO_LSB_REG);
			अगर (mask & 0xff00)
				outb((s->state >> 8), io + PCL726_DO_MSB_REG);
		पूर्ण
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl726_attach(काष्ठा comedi_device *dev,
			 काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcl726_board *board = dev->board_ptr;
	काष्ठा pcl726_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक subdev;
	पूर्णांक ret;
	पूर्णांक i;

	ret = comedi_request_region(dev, it->options[0], board->io_len);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	/*
	 * Hook up the बाह्यal trigger source पूर्णांकerrupt only अगर the
	 * user config option is valid and the board supports पूर्णांकerrupts.
	 */
	अगर (it->options[1] && (board->irq_mask & (1 << it->options[1]))) अणु
		ret = request_irq(it->options[1], pcl726_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0) अणु
			/* External trigger source is from Pin-17 of CN3 */
			dev->irq = it->options[1];
		पूर्ण
	पूर्ण

	/* setup the per-channel analog output range_table_list */
	क्रम (i = 0; i < 12; i++) अणु
		अचिन्हित पूर्णांक opt = it->options[2 + i];

		अगर (opt < board->ao_num_ranges && i < board->ao_nchan)
			devpriv->rangelist[i] = board->ao_ranges[opt];
		अन्यथा
			devpriv->rangelist[i] = &range_unknown;
	पूर्ण

	subdev = board->have_dio ? 3 : 1;
	अगर (dev->irq)
		subdev++;
	ret = comedi_alloc_subdevices(dev, subdev);
	अगर (ret)
		वापस ret;

	subdev = 0;

	/* Analog Output subdevice */
	s = &dev->subdevices[subdev++];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_GROUND;
	s->n_chan	= board->ao_nchan;
	s->maxdata	= 0x0fff;
	s->range_table_list = devpriv->rangelist;
	s->insn_ग_लिखो	= pcl726_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	अगर (board->have_dio) अणु
		/* Digital Input subdevice */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->insn_bits	= pcl726_di_insn_bits;
		s->range_table	= &range_digital;

		/* Digital Output subdevice */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->insn_bits	= pcl726_करो_insn_bits;
		s->range_table	= &range_digital;
	पूर्ण

	अगर (dev->irq) अणु
		/* Digital Input subdevice - Interrupt support */
		s = &dev->subdevices[subdev++];
		dev->पढ़ो_subdev = s;
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE | SDF_CMD_READ;
		s->n_chan	= 1;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl726_पूर्णांकr_insn_bits;
		s->len_chanlist	= 1;
		s->करो_cmdtest	= pcl726_पूर्णांकr_cmdtest;
		s->करो_cmd	= pcl726_पूर्णांकr_cmd;
		s->cancel	= pcl726_पूर्णांकr_cancel;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pcl726_driver = अणु
	.driver_name	= "pcl726",
	.module		= THIS_MODULE,
	.attach		= pcl726_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &pcl726_boards[0].name,
	.num_names	= ARRAY_SIZE(pcl726_boards),
	.offset		= माप(काष्ठा pcl726_board),
पूर्ण;
module_comedi_driver(pcl726_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Advantech PCL-726 & compatibles");
MODULE_LICENSE("GPL");
