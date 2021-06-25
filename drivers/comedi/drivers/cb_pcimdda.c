<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/cb_pcimdda.c
 * Computer Boards PCIM-DDA06-16 Comedi driver
 * Author: Calin Culianu <calin@ajvar.org>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */
/*
 * Driver: cb_pcimdda
 * Description: Measurement Computing PCIM-DDA06-16
 * Devices: [Measurement Computing] PCIM-DDA06-16 (cb_pcimdda)
 * Author: Calin Culianu <calin@ajvar.org>
 * Updated: Mon, 14 Apr 2008 15:15:51 +0100
 * Status: works
 *
 * All features of the PCIM-DDA06-16 board are supported.
 * This board has 6 16-bit AO channels, and the usual 8255 DIO setup.
 * (24 channels, configurable in banks of 8 and 4, etc.).
 * This board करोes not support commands.
 *
 * The board has a peculiar way of specअगरying AO gain/range settings -- You have
 * 1 jumper bank on the card, which either makes all 6 AO channels either
 * 5 Volt unipolar, 5V bipolar, 10 Volt unipolar or 10V bipolar.
 *
 * Since there is असलolutely _no_ way to tell in software how this jumper is set
 * (well, at least according to the rather thin spec. from Measurement Computing
 * that comes with the board), the driver assumes the jumper is at its factory
 * शेष setting of +/-5V.
 *
 * Also of note is the fact that this board features another jumper, whose
 * state is also completely invisible to software.  It toggles two possible AO
 * output modes on the board:
 *
 *   - Update Mode: Writing to an AO channel instantaneously updates the actual
 *     संकेत output by the DAC on the board (this is the factory शेष).
 *   - Simultaneous XFER Mode: Writing to an AO channel has no effect until
 *     you पढ़ो from any one of the AO channels.  This is useful क्रम loading
 *     all 6 AO values, and then पढ़ोing from any one of the AO channels on the
 *     device to instantly update all 6 AO values in unison.  Useful क्रम some
 *     control apps, I would assume? If your jumper is in this setting, then you
 *     need to issue your comedi_data_ग_लिखो()s to load all the values you want,
 *     then issue one comedi_data_पढ़ो() on any channel on the AO subdevice
 *     to initiate the simultaneous XFER.
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 */

/*
 * This is a driver क्रम the Computer Boards PCIM-DDA06-16 Analog Output
 * card.  This board has a unique रेजिस्टर layout and as such probably
 * deserves its own driver file.
 *
 * It is theoretically possible to पूर्णांकegrate this board पूर्णांकo the cb_pcidda
 * file, but since that isn't my code, I didn't want to signअगरicantly
 * modअगरy that file to support this board (I thought it impolite to करो so).
 *
 * At any rate, अगर you feel ambitious, please feel मुक्त to take
 * the code out of this file and combine it with a more unअगरied driver
 * file.
 *
 * I would like to thank Timothy Curry <Timothy.Curry@rdec.redstone.army.mil>
 * क्रम lending me a board so that I could ग_लिखो this driver.
 *
 * -Calin Culianu <calin@ajvar.org>
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

#समावेश "8255.h"

/* device ids of the cards we support -- currently only 1 card supported */
#घोषणा PCI_ID_PCIM_DDA06_16		0x0053

/*
 * Register map, 8-bit access only
 */
#घोषणा PCIMDDA_DA_CHAN(x)		(0x00 + (x) * 2)
#घोषणा PCIMDDA_8255_BASE_REG		0x0c

अटल पूर्णांक cb_pcimdda_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित दीर्घ offset = dev->iobase + PCIMDDA_DA_CHAN(chan);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];

		/*
		 * Write the LSB then MSB.
		 *
		 * If the simultaneous xfer mode is selected by the
		 * jumper on the card, a पढ़ो inकाष्ठाion is needed
		 * in order to initiate the simultaneous transfer.
		 * Otherwise, the DAC will be updated when the MSB
		 * is written.
		 */
		outb(val & 0x00ff, offset);
		outb((val >> 8) & 0x00ff, offset + 1);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक cb_pcimdda_ao_insn_पढ़ो(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	/* Initiate the simultaneous transfer */
	inw(dev->iobase + PCIMDDA_DA_CHAN(chan));

	वापस comedi_पढ़ोback_insn_पढ़ो(dev, s, insn, data);
पूर्ण

अटल पूर्णांक cb_pcimdda_स्वतः_attach(काष्ठा comedi_device *dev,
				  अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 3);

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* analog output subdevice */
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
	s->n_chan	= 6;
	s->maxdata	= 0xffff;
	s->range_table	= &range_bipolar5;
	s->insn_ग_लिखो	= cb_pcimdda_ao_insn_ग_लिखो;
	s->insn_पढ़ो	= cb_pcimdda_ao_insn_पढ़ो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[1];
	/* digital i/o subdevice */
	वापस subdev_8255_init(dev, s, शून्य, PCIMDDA_8255_BASE_REG);
पूर्ण

अटल काष्ठा comedi_driver cb_pcimdda_driver = अणु
	.driver_name	= "cb_pcimdda",
	.module		= THIS_MODULE,
	.स्वतः_attach	= cb_pcimdda_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक cb_pcimdda_pci_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &cb_pcimdda_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cb_pcimdda_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CB, PCI_ID_PCIM_DDA06_16) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cb_pcimdda_pci_table);

अटल काष्ठा pci_driver cb_pcimdda_driver_pci_driver = अणु
	.name		= "cb_pcimdda",
	.id_table	= cb_pcimdda_pci_table,
	.probe		= cb_pcimdda_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(cb_pcimdda_driver, cb_pcimdda_driver_pci_driver);

MODULE_AUTHOR("Calin A. Culianu <calin@rtlab.org>");
MODULE_DESCRIPTION("Comedi low-level driver for the Computerboards PCIM-DDA series.  Currently only supports PCIM-DDA06-16 (which also happens to be the only board in this series. :) ) ");
MODULE_LICENSE("GPL");
