<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम NI 670x devices
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2001 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_670x
 * Description: National Instruments 670x
 * Author: Bart Joris <bjoris@advalvas.be>
 * Updated: Wed, 11 Dec 2002 18:25:35 -0800
 * Devices: [National Instruments] PCI-6703 (ni_670x), PCI-6704
 * Status: unknown
 *
 * Commands are not supported.
 *
 * Manuals:
 *   322110a.pdf	PCI/PXI-6704 User Manual
 *   322110b.pdf	PCI/PXI-6703/6704 User Manual
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश "../comedi_pci.h"

#घोषणा AO_VALUE_OFFSET			0x00
#घोषणा	AO_CHAN_OFFSET			0x0c
#घोषणा	AO_STATUS_OFFSET		0x10
#घोषणा AO_CONTROL_OFFSET		0x10
#घोषणा	DIO_PORT0_सूची_OFFSET	0x20
#घोषणा	DIO_PORT0_DATA_OFFSET	0x24
#घोषणा	DIO_PORT1_सूची_OFFSET	0x28
#घोषणा	DIO_PORT1_DATA_OFFSET	0x2c
#घोषणा	MISC_STATUS_OFFSET		0x14
#घोषणा	MISC_CONTROL_OFFSET		0x14

क्रमागत ni_670x_boardid अणु
	BOARD_PCI6703,
	BOARD_PXI6704,
	BOARD_PCI6704,
पूर्ण;

काष्ठा ni_670x_board अणु
	स्थिर अक्षर *name;
	अचिन्हित लघु ao_chans;
पूर्ण;

अटल स्थिर काष्ठा ni_670x_board ni_670x_boards[] = अणु
	[BOARD_PCI6703] = अणु
		.name		= "PCI-6703",
		.ao_chans	= 16,
	पूर्ण,
	[BOARD_PXI6704] = अणु
		.name		= "PXI-6704",
		.ao_chans	= 32,
	पूर्ण,
	[BOARD_PCI6704] = अणु
		.name		= "PCI-6704",
		.ao_chans	= 32,
	पूर्ण,
पूर्ण;

काष्ठा ni_670x_निजी अणु
	पूर्णांक boardtype;
	पूर्णांक dio;
पूर्ण;

अटल पूर्णांक ni_670x_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	/*
	 * Channel number mapping:
	 *
	 * NI 6703/ NI 6704 | NI 6704 Only
	 * -------------------------------
	 * vch(0)  :  0     | ich(16) :  1
	 * vch(1)  :  2     | ich(17) :  3
	 * ...              | ...
	 * vch(15) : 30     | ich(31) : 31
	 */
	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		/* First ग_लिखो in channel रेजिस्टर which channel to use */
		ग_लिखोl(((chan & 15) << 1) | ((chan & 16) >> 4),
		       dev->mmio + AO_CHAN_OFFSET);
		/* ग_लिखो channel value */
		ग_लिखोl(val, dev->mmio + AO_VALUE_OFFSET);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_670x_dio_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		ग_लिखोl(s->state, dev->mmio + DIO_PORT0_DATA_OFFSET);

	data[1] = पढ़ोl(dev->mmio + DIO_PORT0_DATA_OFFSET);

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_670x_dio_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	ग_लिखोl(s->io_bits, dev->mmio + DIO_PORT0_सूची_OFFSET);

	वापस insn->n;
पूर्ण

/* ripped from mite.h and mite_setup2() to aव्योम mite dependency */
#घोषणा MITE_IODWBSR	0xc0	 /* IO Device Winकरोw Base Size Register */
#घोषणा WENAB		BIT(7) /* winकरोw enable */

अटल पूर्णांक ni_670x_mite_init(काष्ठा pci_dev *pcidev)
अणु
	व्योम __iomem *mite_base;
	u32 मुख्य_phys_addr;

	/* ioremap the MITE रेजिस्टरs (BAR 0) temporarily */
	mite_base = pci_ioremap_bar(pcidev, 0);
	अगर (!mite_base)
		वापस -ENOMEM;

	/* set data winकरोw to मुख्य रेजिस्टरs (BAR 1) */
	मुख्य_phys_addr = pci_resource_start(pcidev, 1);
	ग_लिखोl(मुख्य_phys_addr | WENAB, mite_base + MITE_IODWBSR);

	/* finished with MITE रेजिस्टरs */
	iounmap(mite_base);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_670x_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा ni_670x_board *board = शून्य;
	काष्ठा ni_670x_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (context < ARRAY_SIZE(ni_670x_boards))
		board = &ni_670x_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = ni_670x_mite_init(pcidev);
	अगर (ret)
		वापस ret;

	dev->mmio = pci_ioremap_bar(pcidev, 1);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* analog output subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = board->ao_chans;
	s->maxdata = 0xffff;
	अगर (s->n_chan == 32) अणु
		स्थिर काष्ठा comedi_lrange **range_table_list;

		range_table_list = kदो_स्मृति_array(32,
						 माप(काष्ठा comedi_lrange *),
						 GFP_KERNEL);
		अगर (!range_table_list)
			वापस -ENOMEM;
		s->range_table_list = range_table_list;
		क्रम (i = 0; i < 16; i++) अणु
			range_table_list[i] = &range_bipolar10;
			range_table_list[16 + i] = &range_0_20mA;
		पूर्ण
	पूर्ण अन्यथा अणु
		s->range_table = &range_bipolar10;
	पूर्ण
	s->insn_ग_लिखो = ni_670x_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[1];
	/* digital i/o subdevice */
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = 8;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = ni_670x_dio_insn_bits;
	s->insn_config = ni_670x_dio_insn_config;

	/* Config of misc रेजिस्टरs */
	ग_लिखोl(0x10, dev->mmio + MISC_CONTROL_OFFSET);
	/* Config of ao रेजिस्टरs */
	ग_लिखोl(0x00, dev->mmio + AO_CONTROL_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम ni_670x_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा comedi_subdevice *s;

	comedi_pci_detach(dev);
	अगर (dev->n_subdevices) अणु
		s = &dev->subdevices[0];
		अगर (s)
			kमुक्त(s->range_table_list);
	पूर्ण
पूर्ण

अटल काष्ठा comedi_driver ni_670x_driver = अणु
	.driver_name	= "ni_670x",
	.module		= THIS_MODULE,
	.स्वतः_attach	= ni_670x_स्वतः_attach,
	.detach		= ni_670x_detach,
पूर्ण;

अटल पूर्णांक ni_670x_pci_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &ni_670x_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ni_670x_pci_table[] = अणु
	अणु PCI_VDEVICE(NI, 0x1290), BOARD_PCI6704 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1920), BOARD_PXI6704 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2c90), BOARD_PCI6703 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ni_670x_pci_table);

अटल काष्ठा pci_driver ni_670x_pci_driver = अणु
	.name		= "ni_670x",
	.id_table	= ni_670x_pci_table,
	.probe		= ni_670x_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(ni_670x_driver, ni_670x_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
