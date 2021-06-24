<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_1032.c
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

/*
 * Driver: addi_apci_1032
 * Description: ADDI-DATA APCI-1032 Digital Input Board
 * Author: ADDI-DATA GmbH <info@addi-data.com>,
 *   H Hartley Sweeten <hsweeten@visionengravers.com>
 * Status: untested
 * Devices: [ADDI-DATA] APCI-1032 (addi_apci_1032)
 *
 * Configuration options:
 *   None; devices are configured स्वतःmatically.
 *
 * This driver models the APCI-1032 as a 32-channel, digital input subdevice
 * plus an additional digital input subdevice to handle change-of-state (COS)
 * पूर्णांकerrupts (अगर an पूर्णांकerrupt handler can be set up successfully).
 *
 * The COS subdevice supports comedi asynchronous पढ़ो commands.
 *
 * Change-Of-State (COS) पूर्णांकerrupt configuration:
 *
 * Channels 0 to 15 are पूर्णांकerruptible. These channels can be configured
 * to generate पूर्णांकerrupts based on AND/OR logic क्रम the desired channels.
 *
 *   OR logic:
 *   - reacts to rising or falling edges
 *   - पूर्णांकerrupt is generated when any enabled channel meets the desired
 *     पूर्णांकerrupt condition
 *
 *   AND logic:
 *   - reacts to changes in level of the selected inमाला_दो
 *   - पूर्णांकerrupt is generated when all enabled channels meet the desired
 *     पूर्णांकerrupt condition
 *   - after an पूर्णांकerrupt, a change in level must occur on the selected
 *     inमाला_दो to release the IRQ logic
 *
 * The COS subdevice must be configured beक्रमe setting up a comedi
 * asynchronous command:
 *
 *   data[0] : INSN_CONFIG_DIGITAL_TRIG
 *   data[1] : trigger number (= 0)
 *   data[2] : configuration operation:
 *             - COMEDI_DIGITAL_TRIG_DISABLE = no पूर्णांकerrupts
 *             - COMEDI_DIGITAL_TRIG_ENABLE_EDGES = OR (edge) पूर्णांकerrupts
 *             - COMEDI_DIGITAL_TRIG_ENABLE_LEVELS = AND (level) पूर्णांकerrupts
 *   data[3] : left-shअगरt क्रम data[4] and data[5]
 *   data[4] : rising-edge/high level channels
 *   data[5] : falling-edge/low level channels
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"
#समावेश "amcc_s5933.h"

/*
 * I/O Register Map
 */
#घोषणा APCI1032_DI_REG			0x00
#घोषणा APCI1032_MODE1_REG		0x04
#घोषणा APCI1032_MODE2_REG		0x08
#घोषणा APCI1032_STATUS_REG		0x0c
#घोषणा APCI1032_CTRL_REG		0x10
#घोषणा APCI1032_CTRL_INT_MODE(x)	(((x) & 0x1) << 1)
#घोषणा APCI1032_CTRL_INT_OR		APCI1032_CTRL_INT_MODE(0)
#घोषणा APCI1032_CTRL_INT_AND		APCI1032_CTRL_INT_MODE(1)
#घोषणा APCI1032_CTRL_INT_ENA		BIT(2)

काष्ठा apci1032_निजी अणु
	अचिन्हित दीर्घ amcc_iobase;	/* base of AMCC I/O रेजिस्टरs */
	अचिन्हित पूर्णांक mode1;	/* rising-edge/high level channels */
	अचिन्हित पूर्णांक mode2;	/* falling-edge/low level channels */
	अचिन्हित पूर्णांक ctrl;	/* पूर्णांकerrupt mode OR (edge) . AND (level) */
पूर्ण;

अटल पूर्णांक apci1032_reset(काष्ठा comedi_device *dev)
अणु
	/* disable the पूर्णांकerrupts */
	outl(0x0, dev->iobase + APCI1032_CTRL_REG);
	/* Reset the पूर्णांकerrupt status रेजिस्टर */
	inl(dev->iobase + APCI1032_STATUS_REG);
	/* Disable the and/or पूर्णांकerrupt */
	outl(0x0, dev->iobase + APCI1032_MODE1_REG);
	outl(0x0, dev->iobase + APCI1032_MODE2_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक apci1032_cos_insn_config(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1032_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक shअगरt, oldmask, himask, lomask;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_DIGITAL_TRIG:
		अगर (data[1] != 0)
			वापस -EINVAL;
		shअगरt = data[3];
		अगर (shअगरt < 32) अणु
			oldmask = (1U << shअगरt) - 1;
			himask = data[4] << shअगरt;
			lomask = data[5] << shअगरt;
		पूर्ण अन्यथा अणु
			oldmask = 0xffffffffu;
			himask = 0;
			lomask = 0;
		पूर्ण
		चयन (data[2]) अणु
		हाल COMEDI_DIGITAL_TRIG_DISABLE:
			devpriv->ctrl = 0;
			devpriv->mode1 = 0;
			devpriv->mode2 = 0;
			apci1032_reset(dev);
			अवरोध;
		हाल COMEDI_DIGITAL_TRIG_ENABLE_EDGES:
			अगर (devpriv->ctrl != (APCI1032_CTRL_INT_ENA |
					      APCI1032_CTRL_INT_OR)) अणु
				/* चयनing to 'OR' mode */
				devpriv->ctrl = APCI1032_CTRL_INT_ENA |
						APCI1032_CTRL_INT_OR;
				/* wipe old channels */
				devpriv->mode1 = 0;
				devpriv->mode2 = 0;
			पूर्ण अन्यथा अणु
				/* preserve unspecअगरied channels */
				devpriv->mode1 &= oldmask;
				devpriv->mode2 &= oldmask;
			पूर्ण
			/* configure specअगरied channels */
			devpriv->mode1 |= himask;
			devpriv->mode2 |= lomask;
			अवरोध;
		हाल COMEDI_DIGITAL_TRIG_ENABLE_LEVELS:
			अगर (devpriv->ctrl != (APCI1032_CTRL_INT_ENA |
					      APCI1032_CTRL_INT_AND)) अणु
				/* चयनing to 'AND' mode */
				devpriv->ctrl = APCI1032_CTRL_INT_ENA |
						APCI1032_CTRL_INT_AND;
				/* wipe old channels */
				devpriv->mode1 = 0;
				devpriv->mode2 = 0;
			पूर्ण अन्यथा अणु
				/* preserve unspecअगरied channels */
				devpriv->mode1 &= oldmask;
				devpriv->mode2 &= oldmask;
			पूर्ण
			/* configure specअगरied channels */
			devpriv->mode1 |= himask;
			devpriv->mode2 |= lomask;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1032_cos_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	data[1] = s->state;

	वापस 0;
पूर्ण

अटल पूर्णांक apci1032_cos_cmdtest(काष्ठा comedi_device *dev,
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

/*
 * Change-Of-State (COS) 'do_cmd' operation
 *
 * Enable the COS पूर्णांकerrupt as configured by apci1032_cos_insn_config().
 */
अटल पूर्णांक apci1032_cos_cmd(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा apci1032_निजी *devpriv = dev->निजी;

	अगर (!devpriv->ctrl) अणु
		dev_warn(dev->class_dev,
			 "Interrupts disabled due to mode configuration!\n");
		वापस -EINVAL;
	पूर्ण

	outl(devpriv->mode1, dev->iobase + APCI1032_MODE1_REG);
	outl(devpriv->mode2, dev->iobase + APCI1032_MODE2_REG);
	outl(devpriv->ctrl, dev->iobase + APCI1032_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक apci1032_cos_cancel(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	वापस apci1032_reset(dev);
पूर्ण

अटल irqवापस_t apci1032_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा apci1032_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित लघु val;

	/* check पूर्णांकerrupt is from this device */
	अगर ((inl(devpriv->amcc_iobase + AMCC_OP_REG_INTCSR) &
	     INTCSR_INTR_ASSERTED) == 0)
		वापस IRQ_NONE;

	/* check पूर्णांकerrupt is enabled */
	ctrl = inl(dev->iobase + APCI1032_CTRL_REG);
	अगर ((ctrl & APCI1032_CTRL_INT_ENA) == 0)
		वापस IRQ_HANDLED;

	/* disable the पूर्णांकerrupt */
	outl(ctrl & ~APCI1032_CTRL_INT_ENA, dev->iobase + APCI1032_CTRL_REG);

	s->state = inl(dev->iobase + APCI1032_STATUS_REG) & 0xffff;
	val = s->state;
	comedi_buf_ग_लिखो_samples(s, &val, 1);
	comedi_handle_events(dev, s);

	/* enable the पूर्णांकerrupt */
	outl(ctrl, dev->iobase + APCI1032_CTRL_REG);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक apci1032_di_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	data[1] = inl(dev->iobase + APCI1032_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1032_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा apci1032_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	devpriv->amcc_iobase = pci_resource_start(pcidev, 0);
	dev->iobase = pci_resource_start(pcidev, 1);
	apci1032_reset(dev);
	अगर (pcidev->irq > 0) अणु
		ret = request_irq(pcidev->irq, apci1032_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	/*  Allocate and Initialise DI Subdevice Structures */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci1032_di_insn_bits;

	/* Change-Of-State (COS) पूर्णांकerrupt subdevice */
	s = &dev->subdevices[1];
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE | SDF_CMD_READ;
		s->n_chan	= 1;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_config	= apci1032_cos_insn_config;
		s->insn_bits	= apci1032_cos_insn_bits;
		s->len_chanlist	= 1;
		s->करो_cmdtest	= apci1032_cos_cmdtest;
		s->करो_cmd	= apci1032_cos_cmd;
		s->cancel	= apci1032_cos_cancel;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम apci1032_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		apci1032_reset(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver apci1032_driver = अणु
	.driver_name	= "addi_apci_1032",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci1032_स्वतः_attach,
	.detach		= apci1032_detach,
पूर्ण;

अटल पूर्णांक apci1032_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci1032_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci1032_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADDIDATA, 0x1003) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci1032_pci_table);

अटल काष्ठा pci_driver apci1032_pci_driver = अणु
	.name		= "addi_apci_1032",
	.id_table	= apci1032_pci_table,
	.probe		= apci1032_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci1032_driver, apci1032_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("ADDI-DATA APCI-1032, 32 channel DI boards");
MODULE_LICENSE("GPL");
