<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_16xx.c
 * Copyright (C) 2004,2005  ADDI-DATA GmbH क्रम the source code of this module.
 * Project manager: S. Weber
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

#समावेश "../comedi_pci.h"

/*
 * Register I/O map
 */
#घोषणा APCI16XX_IN_REG(x)		(((x) * 4) + 0x08)
#घोषणा APCI16XX_OUT_REG(x)		(((x) * 4) + 0x14)
#घोषणा APCI16XX_सूची_REG(x)		(((x) * 4) + 0x20)

क्रमागत apci16xx_boardid अणु
	BOARD_APCI1648,
	BOARD_APCI1696,
पूर्ण;

काष्ठा apci16xx_boardinfo अणु
	स्थिर अक्षर *name;
	पूर्णांक n_chan;
पूर्ण;

अटल स्थिर काष्ठा apci16xx_boardinfo apci16xx_boardtypes[] = अणु
	[BOARD_APCI1648] = अणु
		.name		= "apci1648",
		.n_chan		= 48,		/* 2 subdevices */
	पूर्ण,
	[BOARD_APCI1696] = अणु
		.name		= "apci1696",
		.n_chan		= 96,		/* 3 subdevices */
	पूर्ण,
पूर्ण;

अटल पूर्णांक apci16xx_insn_config(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 8)
		mask = 0x000000ff;
	अन्यथा अगर (chan < 16)
		mask = 0x0000ff00;
	अन्यथा अगर (chan < 24)
		mask = 0x00ff0000;
	अन्यथा
		mask = 0xff000000;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	outl(s->io_bits, dev->iobase + APCI16XX_सूची_REG(s->index));

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci16xx_dio_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outl(s->state, dev->iobase + APCI16XX_OUT_REG(s->index));

	data[1] = inl(dev->iobase + APCI16XX_IN_REG(s->index));

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci16xx_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा apci16xx_boardinfo *board = शून्य;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक n_subdevs;
	अचिन्हित पूर्णांक last;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(apci16xx_boardtypes))
		board = &apci16xx_boardtypes[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->iobase = pci_resource_start(pcidev, 0);

	/*
	 * Work out the number of subdevices needed to support all the
	 * digital i/o channels on the board. Each subdevice supports
	 * up to 32 channels.
	 */
	n_subdevs = board->n_chan / 32;
	अगर ((n_subdevs * 32) < board->n_chan) अणु
		last = board->n_chan - (n_subdevs * 32);
		n_subdevs++;
	पूर्ण अन्यथा अणु
		last = 0;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, n_subdevs);
	अगर (ret)
		वापस ret;

	/* Initialize the TTL digital i/o subdevices */
	क्रम (i = 0; i < n_subdevs; i++) अणु
		s = &dev->subdevices[i];
		s->type		= COMEDI_SUBD_DIO;
		s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
		s->n_chan	= ((i * 32) < board->n_chan) ? 32 : last;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_config	= apci16xx_insn_config;
		s->insn_bits	= apci16xx_dio_insn_bits;

		/* Default all channels to inमाला_दो */
		s->io_bits	= 0;
		outl(s->io_bits, dev->iobase + APCI16XX_सूची_REG(i));
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver apci16xx_driver = अणु
	.driver_name	= "addi_apci_16xx",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci16xx_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक apci16xx_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci16xx_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci16xx_pci_table[] = अणु
	अणु PCI_VDEVICE(ADDIDATA, 0x1009), BOARD_APCI1648 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x100a), BOARD_APCI1696 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci16xx_pci_table);

अटल काष्ठा pci_driver apci16xx_pci_driver = अणु
	.name		= "addi_apci_16xx",
	.id_table	= apci16xx_pci_table,
	.probe		= apci16xx_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci16xx_driver, apci16xx_pci_driver);

MODULE_DESCRIPTION("ADDI-DATA APCI-1648/1696, TTL I/O boards");
MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_LICENSE("GPL");
