<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * adl_pci6208.c
 * Comedi driver क्रम ADLink 6208 series cards
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: adl_pci6208
 * Description: ADLink PCI-6208/6216 Series Multi-channel Analog Output Cards
 * Devices: [ADLink] PCI-6208 (adl_pci6208), PCI-6216
 * Author: nsyeow <nsyeow@pd.jaring.my>
 * Updated: Wed, 11 Feb 2015 11:37:18 +0000
 * Status: untested
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 *
 * All supported devices share the same PCI device ID and are treated as a
 * PCI-6216 with 16 analog output channels.  On a PCI-6208, the upper 8
 * channels exist in रेजिस्टरs, but करोn't go to DAC chips.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश "../comedi_pci.h"

/*
 * PCI-6208/6216-GL रेजिस्टर map
 */
#घोषणा PCI6208_AO_CONTROL(x)		(0x00 + (2 * (x)))
#घोषणा PCI6208_AO_STATUS		0x00
#घोषणा PCI6208_AO_STATUS_DATA_SEND	BIT(0)
#घोषणा PCI6208_DIO			0x40
#घोषणा PCI6208_DIO_DO_MASK		(0x0f)
#घोषणा PCI6208_DIO_DO_SHIFT		(0)
#घोषणा PCI6208_DIO_DI_MASK		(0xf0)
#घोषणा PCI6208_DIO_DI_SHIFT		(4)

अटल पूर्णांक pci6208_ao_eoc(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + PCI6208_AO_STATUS);
	अगर ((status & PCI6208_AO_STATUS_DATA_SEND) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pci6208_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		/* D/A transfer rate is 2.2us */
		ret = comedi_समयout(dev, s, insn, pci6208_ao_eoc, 0);
		अगर (ret)
			वापस ret;

		/* the hardware expects two's complement values */
		outw(comedi_offset_munge(s, val),
		     dev->iobase + PCI6208_AO_CONTROL(chan));

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci6208_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक val;

	val = inw(dev->iobase + PCI6208_DIO);
	val = (val & PCI6208_DIO_DI_MASK) >> PCI6208_DIO_DI_SHIFT;

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci6208_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PCI6208_DIO);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci6208_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 2);

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* analog output subdevice */
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;	/* Only 8 usable on PCI-6208 */
	s->maxdata	= 0xffff;
	s->range_table	= &range_bipolar10;
	s->insn_ग_लिखो	= pci6208_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[1];
	/* digital input subdevice */
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci6208_di_insn_bits;

	s = &dev->subdevices[2];
	/* digital output subdevice */
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci6208_करो_insn_bits;

	/*
	 * Get the पढ़ो back संकेतs from the digital outमाला_दो
	 * and save it as the initial state क्रम the subdevice.
	 */
	val = inw(dev->iobase + PCI6208_DIO);
	val = (val & PCI6208_DIO_DO_MASK) >> PCI6208_DIO_DO_SHIFT;
	s->state	= val;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver adl_pci6208_driver = अणु
	.driver_name	= "adl_pci6208",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci6208_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक adl_pci6208_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &adl_pci6208_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id adl_pci6208_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADLINK, 0x6208) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
			 0x9999, 0x6208) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adl_pci6208_pci_table);

अटल काष्ठा pci_driver adl_pci6208_pci_driver = अणु
	.name		= "adl_pci6208",
	.id_table	= adl_pci6208_pci_table,
	.probe		= adl_pci6208_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adl_pci6208_driver, adl_pci6208_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for ADLink 6208 series cards");
MODULE_LICENSE("GPL");
