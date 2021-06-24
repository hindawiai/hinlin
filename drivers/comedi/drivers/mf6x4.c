<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  comedi/drivers/mf6x4.c
 *  Driver क्रम Humusoft MF634 and MF624 Data acquisition cards
 *
 *  COMEDI - Linux Control and Measurement Device Interface
 *  Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */
/*
 * Driver: mf6x4
 * Description: Humusoft MF634 and MF624 Data acquisition card driver
 * Devices: [Humusoft] MF634 (mf634), MF624 (mf624)
 * Author: Rostislav Lisovy <lisovy@gmail.com>
 * Status: works
 * Updated:
 * Configuration Options: none
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश "../comedi_pci.h"

/* Registers present in BAR0 memory region */
#घोषणा MF624_GPIOC_REG		0x54

#घोषणा MF6X4_GPIOC_EOLC	BIT(17)	/* End Of Last Conversion */
#घोषणा MF6X4_GPIOC_LDAC	BIT(23)	/* Load DACs */
#घोषणा MF6X4_GPIOC_DACEN	BIT(26)

/* BAR1 रेजिस्टरs */
#घोषणा MF6X4_ADDATA_REG	0x00
#घोषणा MF6X4_ADCTRL_REG	0x00
#घोषणा MF6X4_ADCTRL_CHAN(x)	BIT(chan)
#घोषणा MF6X4_DIN_REG		0x10
#घोषणा MF6X4_DIN_MASK		0xff
#घोषणा MF6X4_DOUT_REG		0x10
#घोषणा MF6X4_ADSTART_REG	0x20
#घोषणा MF6X4_DAC_REG(x)	(0x20 + ((x) * 2))

/* BAR2 रेजिस्टरs */
#घोषणा MF634_GPIOC_REG		0x68

क्रमागत mf6x4_boardid अणु
	BOARD_MF634,
	BOARD_MF624,
पूर्ण;

काष्ठा mf6x4_board अणु
	स्थिर अक्षर *name;
	/* We need to keep track of the order of BARs used by the cards */
	अचिन्हित पूर्णांक bar_nums[3];
पूर्ण;

अटल स्थिर काष्ठा mf6x4_board mf6x4_boards[] = अणु
	[BOARD_MF634] = अणु
		.name           = "mf634",
		.bar_nums	= अणु0, 2, 3पूर्ण,
	पूर्ण,
	[BOARD_MF624] = अणु
		.name           = "mf624",
		.bar_nums	= अणु0, 2, 4पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा mf6x4_निजी अणु
	/*
	 * Documentation क्रम both MF634 and MF624 describes रेजिस्टरs
	 * present in BAR0, 1 and 2 regions.
	 * The real (i.e. in HW) BAR numbers are dअगरferent क्रम MF624
	 * and MF634 yet we will call them 0, 1, 2
	 */
	व्योम __iomem *bar0_mem;
	व्योम __iomem *bar2_mem;

	/*
	 * This configuration रेजिस्टर has the same function and fields
	 * क्रम both cards however it lies in dअगरferent BARs on dअगरferent
	 * offsets -- this variable makes the access easier
	 */
	व्योम __iomem *gpioc_reg;
पूर्ण;

अटल पूर्णांक mf6x4_di_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	data[1] = ioपढ़ो16(dev->mmio + MF6X4_DIN_REG) & MF6X4_DIN_MASK;

	वापस insn->n;
पूर्ण

अटल पूर्णांक mf6x4_करो_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		ioग_लिखो16(s->state, dev->mmio + MF6X4_DOUT_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक mf6x4_ai_eoc(काष्ठा comedi_device *dev,
			काष्ठा comedi_subdevice *s,
			काष्ठा comedi_insn *insn,
			अचिन्हित दीर्घ context)
अणु
	काष्ठा mf6x4_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status;

	/* EOLC goes low at end of conversion. */
	status = ioपढ़ो32(devpriv->gpioc_reg);
	अगर ((status & MF6X4_GPIOC_EOLC) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक mf6x4_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक d;
	पूर्णांक ret;
	पूर्णांक i;

	/* Set the ADC channel number in the scan list */
	ioग_लिखो16(MF6X4_ADCTRL_CHAN(chan), dev->mmio + MF6X4_ADCTRL_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		/* Trigger ADC conversion by पढ़ोing ADSTART */
		ioपढ़ो16(dev->mmio + MF6X4_ADSTART_REG);

		ret = comedi_समयout(dev, s, insn, mf6x4_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		/* Read the actual value */
		d = ioपढ़ो16(dev->mmio + MF6X4_ADDATA_REG);
		d &= s->maxdata;
		/* munge the 2's complement data to offset binary */
		data[i] = comedi_offset_munge(s, d);
	पूर्ण

	ioग_लिखो16(0x0, dev->mmio + MF6X4_ADCTRL_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक mf6x4_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा mf6x4_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	अचिन्हित पूर्णांक gpioc;
	पूर्णांक i;

	/* Enable instantaneous update of converters outमाला_दो + Enable DACs */
	gpioc = ioपढ़ो32(devpriv->gpioc_reg);
	ioग_लिखो32((gpioc & ~MF6X4_GPIOC_LDAC) | MF6X4_GPIOC_DACEN,
		  devpriv->gpioc_reg);

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		ioग_लिखो16(val, dev->mmio + MF6X4_DAC_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक mf6x4_स्वतः_attach(काष्ठा comedi_device *dev, अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा mf6x4_board *board = शून्य;
	काष्ठा mf6x4_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(mf6x4_boards))
		board = &mf6x4_boards[context];
	अन्यथा
		वापस -ENODEV;

	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	devpriv->bar0_mem = pci_ioremap_bar(pcidev, board->bar_nums[0]);
	अगर (!devpriv->bar0_mem)
		वापस -ENODEV;

	dev->mmio = pci_ioremap_bar(pcidev, board->bar_nums[1]);
	अगर (!dev->mmio)
		वापस -ENODEV;

	devpriv->bar2_mem = pci_ioremap_bar(pcidev, board->bar_nums[2]);
	अगर (!devpriv->bar2_mem)
		वापस -ENODEV;

	अगर (board == &mf6x4_boards[BOARD_MF634])
		devpriv->gpioc_reg = devpriv->bar2_mem + MF634_GPIOC_REG;
	अन्यथा
		devpriv->gpioc_reg = devpriv->bar0_mem + MF624_GPIOC_REG;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND;
	s->n_chan	= 8;
	s->maxdata	= 0x3fff;
	s->range_table	= &range_bipolar10;
	s->insn_पढ़ो	= mf6x4_ai_insn_पढ़ो;

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 0x3fff;
	s->range_table	= &range_bipolar10;
	s->insn_ग_लिखो	= mf6x4_ao_insn_ग_लिखो;

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
	s->insn_bits	= mf6x4_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= mf6x4_करो_insn_bits;

	वापस 0;
पूर्ण

अटल व्योम mf6x4_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा mf6x4_निजी *devpriv = dev->निजी;

	अगर (devpriv) अणु
		अगर (devpriv->bar0_mem)
			iounmap(devpriv->bar0_mem);
		अगर (devpriv->bar2_mem)
			iounmap(devpriv->bar2_mem);
	पूर्ण
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver mf6x4_driver = अणु
	.driver_name    = "mf6x4",
	.module         = THIS_MODULE,
	.स्वतः_attach    = mf6x4_स्वतः_attach,
	.detach         = mf6x4_detach,
पूर्ण;

अटल पूर्णांक mf6x4_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &mf6x4_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id mf6x4_pci_table[] = अणु
	अणु PCI_VDEVICE(HUMUSOFT, 0x0634), BOARD_MF634 पूर्ण,
	अणु PCI_VDEVICE(HUMUSOFT, 0x0624), BOARD_MF624 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, mf6x4_pci_table);

अटल काष्ठा pci_driver mf6x4_pci_driver = अणु
	.name           = "mf6x4",
	.id_table       = mf6x4_pci_table,
	.probe          = mf6x4_pci_probe,
	.हटाओ         = comedi_pci_स्वतः_unconfig,
पूर्ण;

module_comedi_pci_driver(mf6x4_driver, mf6x4_pci_driver);

MODULE_AUTHOR("Rostislav Lisovy <lisovy@gmail.com>");
MODULE_DESCRIPTION("Comedi MF634 and MF624 DAQ cards driver");
MODULE_LICENSE("GPL");
