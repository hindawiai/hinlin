<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ni_6527.c
 * Comedi driver क्रम National Instruments PCI-6527
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1999,2002,2003 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_6527
 * Description: National Instruments 6527
 * Devices: [National Instruments] PCI-6527 (pci-6527), PXI-6527 (pxi-6527)
 * Author: David A. Schleef <ds@schleef.org>
 * Updated: Sat, 25 Jan 2003 13:24:40 -0800
 * Status: works
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

/*
 * PCI BAR1 - Register memory map
 *
 * Manuals (available from ftp://ftp.natinst.com/support/manuals)
 *	370106b.pdf	6527 Register Level Programmer Manual
 */
#घोषणा NI6527_DI_REG(x)		(0x00 + (x))
#घोषणा NI6527_DO_REG(x)		(0x03 + (x))
#घोषणा NI6527_ID_REG			0x06
#घोषणा NI6527_CLR_REG			0x07
#घोषणा NI6527_CLR_EDGE			BIT(3)
#घोषणा NI6527_CLR_OVERFLOW		BIT(2)
#घोषणा NI6527_CLR_FILT			BIT(1)
#घोषणा NI6527_CLR_INTERVAL		BIT(0)
#घोषणा NI6527_CLR_IRQS			(NI6527_CLR_EDGE | NI6527_CLR_OVERFLOW)
#घोषणा NI6527_CLR_RESET_FILT		(NI6527_CLR_FILT | NI6527_CLR_INTERVAL)
#घोषणा NI6527_FILT_INTERVAL_REG(x)	(0x08 + (x))
#घोषणा NI6527_FILT_ENA_REG(x)		(0x0c + (x))
#घोषणा NI6527_STATUS_REG		0x14
#घोषणा NI6527_STATUS_IRQ		BIT(2)
#घोषणा NI6527_STATUS_OVERFLOW		BIT(1)
#घोषणा NI6527_STATUS_EDGE		BIT(0)
#घोषणा NI6527_CTRL_REG			0x15
#घोषणा NI6527_CTRL_FALLING		BIT(4)
#घोषणा NI6527_CTRL_RISING		BIT(3)
#घोषणा NI6527_CTRL_IRQ			BIT(2)
#घोषणा NI6527_CTRL_OVERFLOW		BIT(1)
#घोषणा NI6527_CTRL_EDGE		BIT(0)
#घोषणा NI6527_CTRL_DISABLE_IRQS	0
#घोषणा NI6527_CTRL_ENABLE_IRQS		(NI6527_CTRL_FALLING | \
					 NI6527_CTRL_RISING | \
					 NI6527_CTRL_IRQ | NI6527_CTRL_EDGE)
#घोषणा NI6527_RISING_EDGE_REG(x)	(0x18 + (x))
#घोषणा NI6527_FALLING_EDGE_REG(x)	(0x20 + (x))

क्रमागत ni6527_boardid अणु
	BOARD_PCI6527,
	BOARD_PXI6527,
पूर्ण;

काष्ठा ni6527_board अणु
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा ni6527_board ni6527_boards[] = अणु
	[BOARD_PCI6527] = अणु
		.name		= "pci-6527",
	पूर्ण,
	[BOARD_PXI6527] = अणु
		.name		= "pxi-6527",
	पूर्ण,
पूर्ण;

काष्ठा ni6527_निजी अणु
	अचिन्हित पूर्णांक filter_पूर्णांकerval;
	अचिन्हित पूर्णांक filter_enable;
पूर्ण;

अटल व्योम ni6527_set_filter_पूर्णांकerval(काष्ठा comedi_device *dev,
				       अचिन्हित पूर्णांक val)
अणु
	काष्ठा ni6527_निजी *devpriv = dev->निजी;

	अगर (val != devpriv->filter_पूर्णांकerval) अणु
		ग_लिखोb(val & 0xff, dev->mmio + NI6527_FILT_INTERVAL_REG(0));
		ग_लिखोb((val >> 8) & 0xff,
		       dev->mmio + NI6527_FILT_INTERVAL_REG(1));
		ग_लिखोb((val >> 16) & 0x0f,
		       dev->mmio + NI6527_FILT_INTERVAL_REG(2));

		ग_लिखोb(NI6527_CLR_INTERVAL, dev->mmio + NI6527_CLR_REG);

		devpriv->filter_पूर्णांकerval = val;
	पूर्ण
पूर्ण

अटल व्योम ni6527_set_filter_enable(काष्ठा comedi_device *dev,
				     अचिन्हित पूर्णांक val)
अणु
	ग_लिखोb(val & 0xff, dev->mmio + NI6527_FILT_ENA_REG(0));
	ग_लिखोb((val >> 8) & 0xff, dev->mmio + NI6527_FILT_ENA_REG(1));
	ग_लिखोb((val >> 16) & 0xff, dev->mmio + NI6527_FILT_ENA_REG(2));
पूर्ण

अटल पूर्णांक ni6527_di_insn_config(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni6527_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक पूर्णांकerval;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_FILTER:
		/*
		 * The deglitch filter पूर्णांकerval is specअगरied in nanoseconds.
		 * The hardware supports पूर्णांकervals in 200ns increments. Round
		 * the user values up and वापस the actual पूर्णांकerval.
		 */
		पूर्णांकerval = (data[1] + 100) / 200;
		data[1] = पूर्णांकerval * 200;

		अगर (पूर्णांकerval) अणु
			ni6527_set_filter_पूर्णांकerval(dev, पूर्णांकerval);
			devpriv->filter_enable |= 1 << chan;
		पूर्ण अन्यथा अणु
			devpriv->filter_enable &= ~(1 << chan);
		पूर्ण
		ni6527_set_filter_enable(dev, devpriv->filter_enable);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni6527_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक val;

	val = पढ़ोb(dev->mmio + NI6527_DI_REG(0));
	val |= (पढ़ोb(dev->mmio + NI6527_DI_REG(1)) << 8);
	val |= (पढ़ोb(dev->mmio + NI6527_DI_REG(2)) << 16);

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni6527_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक mask;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		/* Outमाला_दो are inverted */
		अचिन्हित पूर्णांक val = s->state ^ 0xffffff;

		अगर (mask & 0x0000ff)
			ग_लिखोb(val & 0xff, dev->mmio + NI6527_DO_REG(0));
		अगर (mask & 0x00ff00)
			ग_लिखोb((val >> 8) & 0xff,
			       dev->mmio + NI6527_DO_REG(1));
		अगर (mask & 0xff0000)
			ग_लिखोb((val >> 16) & 0xff,
			       dev->mmio + NI6527_DO_REG(2));
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल irqवापस_t ni6527_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक status;

	status = पढ़ोb(dev->mmio + NI6527_STATUS_REG);
	अगर (!(status & NI6527_STATUS_IRQ))
		वापस IRQ_NONE;

	अगर (status & NI6527_STATUS_EDGE) अणु
		अचिन्हित लघु val = 0;

		comedi_buf_ग_लिखो_samples(s, &val, 1);
		comedi_handle_events(dev, s);
	पूर्ण

	ग_लिखोb(NI6527_CLR_IRQS, dev->mmio + NI6527_CLR_REG);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ni6527_पूर्णांकr_cmdtest(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_OTHER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT);

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

अटल पूर्णांक ni6527_पूर्णांकr_cmd(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	ग_लिखोb(NI6527_CLR_IRQS, dev->mmio + NI6527_CLR_REG);
	ग_लिखोb(NI6527_CTRL_ENABLE_IRQS, dev->mmio + NI6527_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ni6527_पूर्णांकr_cancel(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	ग_लिखोb(NI6527_CTRL_DISABLE_IRQS, dev->mmio + NI6527_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ni6527_पूर्णांकr_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	data[1] = 0;
	वापस insn->n;
पूर्ण

अटल व्योम ni6527_set_edge_detection(काष्ठा comedi_device *dev,
				      अचिन्हित पूर्णांक mask,
				      अचिन्हित पूर्णांक rising,
				      अचिन्हित पूर्णांक falling)
अणु
	अचिन्हित पूर्णांक i;

	rising &= mask;
	falling &= mask;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (mask & 0xff) अणु
			अगर (~mask & 0xff) अणु
				/* preserve rising-edge detection channels */
				rising |= पढ़ोb(dev->mmio +
						NI6527_RISING_EDGE_REG(i)) &
					  (~mask & 0xff);
				/* preserve falling-edge detection channels */
				falling |= पढ़ोb(dev->mmio +
						 NI6527_FALLING_EDGE_REG(i)) &
					   (~mask & 0xff);
			पूर्ण
			/* update rising-edge detection channels */
			ग_लिखोb(rising & 0xff,
			       dev->mmio + NI6527_RISING_EDGE_REG(i));
			/* update falling-edge detection channels */
			ग_लिखोb(falling & 0xff,
			       dev->mmio + NI6527_FALLING_EDGE_REG(i));
		पूर्ण
		rising >>= 8;
		falling >>= 8;
		mask >>= 8;
	पूर्ण
पूर्ण

अटल पूर्णांक ni6527_पूर्णांकr_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक mask = 0xffffffff;
	अचिन्हित पूर्णांक rising, falling, shअगरt;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_CHANGE_NOTIFY:
		/* check_insn_config_length() करोes not check this inकाष्ठाion */
		अगर (insn->n != 3)
			वापस -EINVAL;
		rising = data[1];
		falling = data[2];
		ni6527_set_edge_detection(dev, mask, rising, falling);
		अवरोध;
	हाल INSN_CONFIG_DIGITAL_TRIG:
		/* check trigger number */
		अगर (data[1] != 0)
			वापस -EINVAL;
		/* check digital trigger operation */
		चयन (data[2]) अणु
		हाल COMEDI_DIGITAL_TRIG_DISABLE:
			rising = 0;
			falling = 0;
			अवरोध;
		हाल COMEDI_DIGITAL_TRIG_ENABLE_EDGES:
			/* check shअगरt amount */
			shअगरt = data[3];
			अगर (shअगरt >= 32) अणु
				mask = 0;
				rising = 0;
				falling = 0;
			पूर्ण अन्यथा अणु
				mask <<= shअगरt;
				rising = data[4] << shअगरt;
				falling = data[5] << shअगरt;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		ni6527_set_edge_detection(dev, mask, rising, falling);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम ni6527_reset(काष्ठा comedi_device *dev)
अणु
	/* disable deglitch filters on all channels */
	ni6527_set_filter_enable(dev, 0);

	/* disable edge detection */
	ni6527_set_edge_detection(dev, 0xffffffff, 0, 0);

	ग_लिखोb(NI6527_CLR_IRQS | NI6527_CLR_RESET_FILT,
	       dev->mmio + NI6527_CLR_REG);
	ग_लिखोb(NI6527_CTRL_DISABLE_IRQS, dev->mmio + NI6527_CTRL_REG);
पूर्ण

अटल पूर्णांक ni6527_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा ni6527_board *board = शून्य;
	काष्ठा ni6527_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(ni6527_boards))
		board = &ni6527_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->mmio = pci_ioremap_bar(pcidev, 1);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	/* make sure this is actually a 6527 device */
	अगर (पढ़ोb(dev->mmio + NI6527_ID_REG) != 0x27)
		वापस -ENODEV;

	ni6527_reset(dev);

	ret = request_irq(pcidev->irq, ni6527_पूर्णांकerrupt, IRQF_SHARED,
			  dev->board_name, dev);
	अगर (ret == 0)
		dev->irq = pcidev->irq;

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_config	= ni6527_di_insn_config;
	s->insn_bits	= ni6527_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= ni6527_करो_insn_bits;

	/* Edge detection पूर्णांकerrupt subdevice */
	s = &dev->subdevices[2];
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE | SDF_CMD_READ;
		s->n_chan	= 1;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_config	= ni6527_पूर्णांकr_insn_config;
		s->insn_bits	= ni6527_पूर्णांकr_insn_bits;
		s->len_chanlist	= 1;
		s->करो_cmdtest	= ni6527_पूर्णांकr_cmdtest;
		s->करो_cmd	= ni6527_पूर्णांकr_cmd;
		s->cancel	= ni6527_पूर्णांकr_cancel;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ni6527_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->mmio)
		ni6527_reset(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver ni6527_driver = अणु
	.driver_name	= "ni_6527",
	.module		= THIS_MODULE,
	.स्वतः_attach	= ni6527_स्वतः_attach,
	.detach		= ni6527_detach,
पूर्ण;

अटल पूर्णांक ni6527_pci_probe(काष्ठा pci_dev *dev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &ni6527_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ni6527_pci_table[] = अणु
	अणु PCI_VDEVICE(NI, 0x2b10), BOARD_PXI6527 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2b20), BOARD_PCI6527 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ni6527_pci_table);

अटल काष्ठा pci_driver ni6527_pci_driver = अणु
	.name		= "ni_6527",
	.id_table	= ni6527_pci_table,
	.probe		= ni6527_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(ni6527_driver, ni6527_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for National Instruments PCI-6527");
MODULE_LICENSE("GPL");
