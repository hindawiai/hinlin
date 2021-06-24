<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * adv_pci1724.c
 * Comedi driver क्रम the Advantech PCI-1724U card.
 *
 * Author:  Frank Mori Hess <fmh6jj@gmail.com>
 * Copyright (C) 2013 GnuBIO Inc
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-8 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: adv_pci1724
 * Description: Advantech PCI-1724U
 * Devices: [Advantech] PCI-1724U (adv_pci1724)
 * Author: Frank Mori Hess <fmh6jj@gmail.com>
 * Updated: 2013-02-09
 * Status: works
 *
 * Configuration Options: not applicable, uses comedi PCI स्वतः config
 *
 * Subdevice 0 is the analog output.
 * Subdevice 1 is the offset calibration क्रम the analog output.
 * Subdevice 2 is the gain calibration क्रम the analog output.
 *
 * The calibration offset and gains have quite a large effect on the
 * analog output, so it is possible to adjust the analog output to
 * have an output range signअगरicantly dअगरferent from the board's
 * nominal output ranges. For a calibrated +/-10V range, the analog
 * output's offset will be set somewhere near mid-range (0x2000) and
 * its gain will be near maximum (0x3fff).
 *
 * There is really no dअगरference between the board's करोcumented 0-20mA
 * versus 4-20mA output ranges. To pick one or the other is simply a
 * matter of adjusting the offset and gain calibration until the board
 * outमाला_दो in the desired range.
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

/*
 * PCI bar 2 Register I/O map (dev->iobase)
 */
#घोषणा PCI1724_DAC_CTRL_REG		0x00
#घोषणा PCI1724_DAC_CTRL_GX(x)		BIT(20 + ((x) / 8))
#घोषणा PCI1724_DAC_CTRL_CX(x)		(((x) % 8) << 16)
#घोषणा PCI1724_DAC_CTRL_MODE(x)	(((x) & 0x3) << 14)
#घोषणा PCI1724_DAC_CTRL_MODE_GAIN	PCI1724_DAC_CTRL_MODE(1)
#घोषणा PCI1724_DAC_CTRL_MODE_OFFSET	PCI1724_DAC_CTRL_MODE(2)
#घोषणा PCI1724_DAC_CTRL_MODE_NORMAL	PCI1724_DAC_CTRL_MODE(3)
#घोषणा PCI1724_DAC_CTRL_MODE_MASK	PCI1724_DAC_CTRL_MODE(3)
#घोषणा PCI1724_DAC_CTRL_DATA(x)	(((x) & 0x3fff) << 0)
#घोषणा PCI1724_SYNC_CTRL_REG		0x04
#घोषणा PCI1724_SYNC_CTRL_DACSTAT	BIT(1)
#घोषणा PCI1724_SYNC_CTRL_SYN		BIT(0)
#घोषणा PCI1724_EEPROM_CTRL_REG		0x08
#घोषणा PCI1724_SYNC_TRIG_REG		0x0c  /* any value works */
#घोषणा PCI1724_BOARD_ID_REG		0x10
#घोषणा PCI1724_BOARD_ID_MASK		(0xf << 0)

अटल स्थिर काष्ठा comedi_lrange adv_pci1724_ao_ranges = अणु
	4, अणु
		BIP_RANGE(10),
		RANGE_mA(0, 20),
		RANGE_mA(4, 20),
		RANGE_unitless(0, 1)
	पूर्ण
पूर्ण;

अटल पूर्णांक adv_pci1724_dac_idle(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inl(dev->iobase + PCI1724_SYNC_CTRL_REG);
	अगर ((status & PCI1724_SYNC_CTRL_DACSTAT) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक adv_pci1724_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ mode = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक ctrl;
	पूर्णांक ret;
	पूर्णांक i;

	ctrl = PCI1724_DAC_CTRL_GX(chan) | PCI1724_DAC_CTRL_CX(chan) | mode;

	/* turn off synchronous mode */
	outl(0, dev->iobase + PCI1724_SYNC_CTRL_REG);

	क्रम (i = 0; i < insn->n; ++i) अणु
		अचिन्हित पूर्णांक val = data[i];

		ret = comedi_समयout(dev, s, insn, adv_pci1724_dac_idle, 0);
		अगर (ret)
			वापस ret;

		outl(ctrl | PCI1724_DAC_CTRL_DATA(val),
		     dev->iobase + PCI1724_DAC_CTRL_REG);

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक adv_pci1724_स्वतः_attach(काष्ठा comedi_device *dev,
				   अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक board_id;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->iobase = pci_resource_start(pcidev, 2);
	board_id = inl(dev->iobase + PCI1724_BOARD_ID_REG);
	dev_info(dev->class_dev, "board id: %d\n",
		 board_id & PCI1724_BOARD_ID_MASK);

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Analog Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_GROUND;
	s->n_chan	= 32;
	s->maxdata	= 0x3fff;
	s->range_table	= &adv_pci1724_ao_ranges;
	s->insn_ग_लिखो	= adv_pci1724_insn_ग_लिखो;
	s->निजी	= (व्योम *)PCI1724_DAC_CTRL_MODE_NORMAL;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Offset Calibration subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_CALIB;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_INTERNAL;
	s->n_chan	= 32;
	s->maxdata	= 0x3fff;
	s->insn_ग_लिखो	= adv_pci1724_insn_ग_लिखो;
	s->निजी	= (व्योम *)PCI1724_DAC_CTRL_MODE_OFFSET;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Gain Calibration subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_CALIB;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_INTERNAL;
	s->n_chan	= 32;
	s->maxdata	= 0x3fff;
	s->insn_ग_लिखो	= adv_pci1724_insn_ग_लिखो;
	s->निजी	= (व्योम *)PCI1724_DAC_CTRL_MODE_GAIN;

	वापस comedi_alloc_subdev_पढ़ोback(s);
पूर्ण

अटल काष्ठा comedi_driver adv_pci1724_driver = अणु
	.driver_name	= "adv_pci1724",
	.module		= THIS_MODULE,
	.स्वतः_attach	= adv_pci1724_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक adv_pci1724_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &adv_pci1724_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id adv_pci1724_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADVANTECH, 0x1724) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adv_pci1724_pci_table);

अटल काष्ठा pci_driver adv_pci1724_pci_driver = अणु
	.name		= "adv_pci1724",
	.id_table	= adv_pci1724_pci_table,
	.probe		= adv_pci1724_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adv_pci1724_driver, adv_pci1724_pci_driver);

MODULE_AUTHOR("Frank Mori Hess <fmh6jj@gmail.com>");
MODULE_DESCRIPTION("Advantech PCI-1724U Comedi driver");
MODULE_LICENSE("GPL");
