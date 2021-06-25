<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_2032.c
 * Copyright (C) 2004,2005  ADDI-DATA GmbH क्रम the source code of this module.
 * Project manager: Eric Stolz
 *
 *	ADDI-DATA GmbH
 *	Dieselstrasse 3
 *	D-77833 Ottersweier
 *	Tel: +19(0)7223/9493-0
 *	Fax: +49(0)7223/9493-92
 *	http://www.addi-data.com
 *	info@addi-data.com
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश "../comedi_pci.h"
#समावेश "addi_watchdog.h"

/*
 * PCI bar 1 I/O Register map
 */
#घोषणा APCI2032_DO_REG			0x00
#घोषणा APCI2032_INT_CTRL_REG		0x04
#घोषणा APCI2032_INT_CTRL_VCC_ENA	BIT(0)
#घोषणा APCI2032_INT_CTRL_CC_ENA	BIT(1)
#घोषणा APCI2032_INT_STATUS_REG		0x08
#घोषणा APCI2032_INT_STATUS_VCC		BIT(0)
#घोषणा APCI2032_INT_STATUS_CC		BIT(1)
#घोषणा APCI2032_STATUS_REG		0x0c
#घोषणा APCI2032_STATUS_IRQ		BIT(0)
#घोषणा APCI2032_WDOG_REG		0x10

काष्ठा apci2032_पूर्णांक_निजी अणु
	spinlock_t spinlock;		/* protects the following members */
	bool active;			/* an async command is running */
	अचिन्हित अक्षर enabled_isns;	/* mask of enabled पूर्णांकerrupt channels */
पूर्ण;

अटल पूर्णांक apci2032_करो_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	s->state = inl(dev->iobase + APCI2032_DO_REG);

	अगर (comedi_dio_update_state(s, data))
		outl(s->state, dev->iobase + APCI2032_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci2032_पूर्णांक_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	data[1] = inl(dev->iobase + APCI2032_INT_STATUS_REG) & 3;
	वापस insn->n;
पूर्ण

अटल व्योम apci2032_पूर्णांक_stop(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा apci2032_पूर्णांक_निजी *subpriv = s->निजी;

	subpriv->active = false;
	subpriv->enabled_isns = 0;
	outl(0x0, dev->iobase + APCI2032_INT_CTRL_REG);
पूर्ण

अटल पूर्णांक apci2032_पूर्णांक_cmdtest(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */

	वापस 0;
पूर्ण

अटल पूर्णांक apci2032_पूर्णांक_cmd(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	काष्ठा apci2032_पूर्णांक_निजी *subpriv = s->निजी;
	अचिन्हित अक्षर enabled_isns;
	अचिन्हित पूर्णांक n;
	अचिन्हित दीर्घ flags;

	enabled_isns = 0;
	क्रम (n = 0; n < cmd->chanlist_len; n++)
		enabled_isns |= 1 << CR_CHAN(cmd->chanlist[n]);

	spin_lock_irqsave(&subpriv->spinlock, flags);

	subpriv->enabled_isns = enabled_isns;
	subpriv->active = true;
	outl(enabled_isns, dev->iobase + APCI2032_INT_CTRL_REG);

	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक apci2032_पूर्णांक_cancel(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा apci2032_पूर्णांक_निजी *subpriv = s->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpriv->spinlock, flags);
	अगर (subpriv->active)
		apci2032_पूर्णांक_stop(dev, s);
	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	वापस 0;
पूर्ण

अटल irqवापस_t apci2032_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	काष्ठा apci2032_पूर्णांक_निजी *subpriv;
	अचिन्हित पूर्णांक val;

	अगर (!dev->attached)
		वापस IRQ_NONE;

	/* Check अगर VCC OR CC पूर्णांकerrupt has occurred */
	val = inl(dev->iobase + APCI2032_STATUS_REG) & APCI2032_STATUS_IRQ;
	अगर (!val)
		वापस IRQ_NONE;

	subpriv = s->निजी;
	spin_lock(&subpriv->spinlock);

	val = inl(dev->iobase + APCI2032_INT_STATUS_REG) & 3;
	/* Disable triggered पूर्णांकerrupt sources. */
	outl(~val & 3, dev->iobase + APCI2032_INT_CTRL_REG);
	/*
	 * Note: We करोn't reenable the triggered पूर्णांकerrupt sources because they
	 * are level-sensitive, hardware error status पूर्णांकerrupt sources and
	 * they'd keep triggering पूर्णांकerrupts repeatedly.
	 */

	अगर (subpriv->active && (val & subpriv->enabled_isns) != 0) अणु
		अचिन्हित लघु bits = 0;
		पूर्णांक i;

		/* Bits in scan data correspond to indices in channel list. */
		क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
			अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

			अगर (val & (1 << chan))
				bits |= (1 << i);
		पूर्ण

		comedi_buf_ग_लिखो_samples(s, &bits, 1);

		अगर (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_करोne >= cmd->stop_arg)
			s->async->events |= COMEDI_CB_EOA;
	पूर्ण

	spin_unlock(&subpriv->spinlock);

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक apci2032_reset(काष्ठा comedi_device *dev)
अणु
	outl(0x0, dev->iobase + APCI2032_DO_REG);
	outl(0x0, dev->iobase + APCI2032_INT_CTRL_REG);

	addi_watchकरोg_reset(dev->iobase + APCI2032_WDOG_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक apci2032_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 1);
	apci2032_reset(dev);

	अगर (pcidev->irq > 0) अणु
		ret = request_irq(pcidev->irq, apci2032_पूर्णांकerrupt,
				  IRQF_SHARED, dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Initialize the digital output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci2032_करो_insn_bits;

	/* Initialize the watchकरोg subdevice */
	s = &dev->subdevices[1];
	ret = addi_watchकरोg_init(s, dev->iobase + APCI2032_WDOG_REG);
	अगर (ret)
		वापस ret;

	/* Initialize the पूर्णांकerrupt subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 2;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci2032_पूर्णांक_insn_bits;
	अगर (dev->irq) अणु
		काष्ठा apci2032_पूर्णांक_निजी *subpriv;

		dev->पढ़ो_subdev = s;
		subpriv = kzalloc(माप(*subpriv), GFP_KERNEL);
		अगर (!subpriv)
			वापस -ENOMEM;
		spin_lock_init(&subpriv->spinlock);
		s->निजी	= subpriv;
		s->subdev_flags	= SDF_READABLE | SDF_CMD_READ | SDF_PACKED;
		s->len_chanlist = 2;
		s->करो_cmdtest	= apci2032_पूर्णांक_cmdtest;
		s->करो_cmd	= apci2032_पूर्णांक_cmd;
		s->cancel	= apci2032_पूर्णांक_cancel;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम apci2032_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		apci2032_reset(dev);
	comedi_pci_detach(dev);
	अगर (dev->पढ़ो_subdev)
		kमुक्त(dev->पढ़ो_subdev->निजी);
पूर्ण

अटल काष्ठा comedi_driver apci2032_driver = अणु
	.driver_name	= "addi_apci_2032",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci2032_स्वतः_attach,
	.detach		= apci2032_detach,
पूर्ण;

अटल पूर्णांक apci2032_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci2032_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci2032_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADDIDATA, 0x1004) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci2032_pci_table);

अटल काष्ठा pci_driver apci2032_pci_driver = अणु
	.name		= "addi_apci_2032",
	.id_table	= apci2032_pci_table,
	.probe		= apci2032_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci2032_driver, apci2032_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("ADDI-DATA APCI-2032, 32 channel DO boards");
MODULE_LICENSE("GPL");
