<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_3501.c
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
 * Driver: addi_apci_3501
 * Description: ADDI-DATA APCI-3501 Analog output board
 * Devices: [ADDI-DATA] APCI-3501 (addi_apci_3501)
 * Author: H Hartley Sweeten <hsweeten@visionengravers.com>
 * Updated: Mon, 20 Jun 2016 10:57:01 -0700
 * Status: untested
 *
 * Configuration Options: not applicable, uses comedi PCI स्वतः config
 *
 * This board has the following features:
 *   - 4 or 8 analog output channels
 *   - 2 optically isolated digital inमाला_दो
 *   - 2 optically isolated digital outमाला_दो
 *   - 1 12-bit watchकरोg/समयr
 *
 * There are 2 versions of the APCI-3501:
 *   - APCI-3501-4  4 analog output channels
 *   - APCI-3501-8  8 analog output channels
 *
 * These boards use the same PCI Venकरोr/Device IDs. The number of output
 * channels used by this driver is determined by पढ़ोing the EEPROM on
 * the board.
 *
 * The watchकरोg/समयr subdevice is not currently supported.
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"
#समावेश "amcc_s5933.h"

/*
 * PCI bar 1 रेजिस्टर I/O map
 */
#घोषणा APCI3501_AO_CTRL_STATUS_REG		0x00
#घोषणा APCI3501_AO_CTRL_BIPOLAR		BIT(0)
#घोषणा APCI3501_AO_STATUS_READY		BIT(8)
#घोषणा APCI3501_AO_DATA_REG			0x04
#घोषणा APCI3501_AO_DATA_CHAN(x)		((x) << 0)
#घोषणा APCI3501_AO_DATA_VAL(x)			((x) << 8)
#घोषणा APCI3501_AO_DATA_BIPOLAR		BIT(31)
#घोषणा APCI3501_AO_TRIG_SCS_REG		0x08
#घोषणा APCI3501_TIMER_BASE			0x20
#घोषणा APCI3501_DO_REG				0x40
#घोषणा APCI3501_DI_REG				0x50

/*
 * AMCC S5933 NVRAM
 */
#घोषणा NVRAM_USER_DATA_START	0x100

#घोषणा NVCMD_BEGIN_READ	(0x7 << 5)
#घोषणा NVCMD_LOAD_LOW		(0x4 << 5)
#घोषणा NVCMD_LOAD_HIGH		(0x5 << 5)

/*
 * Function types stored in the eeprom
 */
#घोषणा EEPROM_DIGITALINPUT		0
#घोषणा EEPROM_DIGITALOUTPUT		1
#घोषणा EEPROM_ANALOGINPUT		2
#घोषणा EEPROM_ANALOGOUTPUT		3
#घोषणा EEPROM_TIMER			4
#घोषणा EEPROM_WATCHDOG			5
#घोषणा EEPROM_TIMER_WATCHDOG_COUNTER	10

काष्ठा apci3501_निजी अणु
	अचिन्हित दीर्घ amcc;
	अचिन्हित अक्षर समयr_mode;
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange apci3501_ao_range = अणु
	2, अणु
		BIP_RANGE(10),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

अटल पूर्णांक apci3501_रुको_क्रम_dac(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक status;

	करो अणु
		status = inl(dev->iobase + APCI3501_AO_CTRL_STATUS_REG);
	पूर्ण जबतक (!(status & APCI3501_AO_STATUS_READY));

	वापस 0;
पूर्ण

अटल पूर्णांक apci3501_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक cfg = APCI3501_AO_DATA_CHAN(chan);
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * All analog output channels have the same output range.
	 *	14-bit bipolar: 0-10V
	 *	13-bit unipolar: +/-10V
	 * Changing the range of one channel changes all of them!
	 */
	अगर (range) अणु
		outl(0, dev->iobase + APCI3501_AO_CTRL_STATUS_REG);
	पूर्ण अन्यथा अणु
		cfg |= APCI3501_AO_DATA_BIPOLAR;
		outl(APCI3501_AO_CTRL_BIPOLAR,
		     dev->iobase + APCI3501_AO_CTRL_STATUS_REG);
	पूर्ण

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		अगर (range == 1) अणु
			अगर (data[i] > 0x1fff) अणु
				dev_err(dev->class_dev,
					"Unipolar resolution is only 13-bits\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		ret = apci3501_रुको_क्रम_dac(dev);
		अगर (ret)
			वापस ret;

		outl(cfg | APCI3501_AO_DATA_VAL(val),
		     dev->iobase + APCI3501_AO_DATA_REG);

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3501_di_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	data[1] = inl(dev->iobase + APCI3501_DI_REG) & 0x3;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3501_करो_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	s->state = inl(dev->iobase + APCI3501_DO_REG);

	अगर (comedi_dio_update_state(s, data))
		outl(s->state, dev->iobase + APCI3501_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम apci3501_eeprom_रुको(अचिन्हित दीर्घ iobase)
अणु
	अचिन्हित अक्षर val;

	करो अणु
		val = inb(iobase + AMCC_OP_REG_MCSR_NVCMD);
	पूर्ण जबतक (val & 0x80);
पूर्ण

अटल अचिन्हित लघु apci3501_eeprom_पढ़ोw(अचिन्हित दीर्घ iobase,
					    अचिन्हित लघु addr)
अणु
	अचिन्हित लघु val = 0;
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित अक्षर i;

	/* Add the offset to the start of the user data */
	addr += NVRAM_USER_DATA_START;

	क्रम (i = 0; i < 2; i++) अणु
		/* Load the low 8 bit address */
		outb(NVCMD_LOAD_LOW, iobase + AMCC_OP_REG_MCSR_NVCMD);
		apci3501_eeprom_रुको(iobase);
		outb((addr + i) & 0xff, iobase + AMCC_OP_REG_MCSR_NVDATA);
		apci3501_eeprom_रुको(iobase);

		/* Load the high 8 bit address */
		outb(NVCMD_LOAD_HIGH, iobase + AMCC_OP_REG_MCSR_NVCMD);
		apci3501_eeprom_रुको(iobase);
		outb(((addr + i) >> 8) & 0xff,
		     iobase + AMCC_OP_REG_MCSR_NVDATA);
		apci3501_eeprom_रुको(iobase);

		/* Read the eeprom data byte */
		outb(NVCMD_BEGIN_READ, iobase + AMCC_OP_REG_MCSR_NVCMD);
		apci3501_eeprom_रुको(iobase);
		पंचांगp = inb(iobase + AMCC_OP_REG_MCSR_NVDATA);
		apci3501_eeprom_रुको(iobase);

		अगर (i == 0)
			val |= पंचांगp;
		अन्यथा
			val |= (पंचांगp << 8);
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक apci3501_eeprom_get_ao_n_chan(काष्ठा comedi_device *dev)
अणु
	काष्ठा apci3501_निजी *devpriv = dev->निजी;
	अचिन्हित अक्षर nfuncs;
	पूर्णांक i;

	nfuncs = apci3501_eeprom_पढ़ोw(devpriv->amcc, 10) & 0xff;

	/* Read functionality details */
	क्रम (i = 0; i < nfuncs; i++) अणु
		अचिन्हित लघु offset = i * 4;
		अचिन्हित लघु addr;
		अचिन्हित अक्षर func;
		अचिन्हित लघु val;

		func = apci3501_eeprom_पढ़ोw(devpriv->amcc, 12 + offset) & 0x3f;
		addr = apci3501_eeprom_पढ़ोw(devpriv->amcc, 14 + offset);

		अगर (func == EEPROM_ANALOGOUTPUT) अणु
			val = apci3501_eeprom_पढ़ोw(devpriv->amcc, addr + 10);
			वापस (val >> 4) & 0x3ff;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक apci3501_eeprom_insn_पढ़ो(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci3501_निजी *devpriv = dev->निजी;
	अचिन्हित लघु addr = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक i;

	अगर (insn->n) अणु
		/* No poपूर्णांक पढ़ोing the same EEPROM location more than once. */
		val = apci3501_eeprom_पढ़ोw(devpriv->amcc, 2 * addr);
		क्रम (i = 0; i < insn->n; i++)
			data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3501_reset(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक chan;
	पूर्णांक ret;

	/* Reset all digital outमाला_दो to "0" */
	outl(0x0, dev->iobase + APCI3501_DO_REG);

	/* Default all analog outमाला_दो to 0V (bipolar) */
	outl(APCI3501_AO_CTRL_BIPOLAR,
	     dev->iobase + APCI3501_AO_CTRL_STATUS_REG);
	val = APCI3501_AO_DATA_BIPOLAR | APCI3501_AO_DATA_VAL(0);

	/* Set all analog output channels */
	क्रम (chan = 0; chan < 8; chan++) अणु
		ret = apci3501_रुको_क्रम_dac(dev);
		अगर (ret) अणु
			dev_warn(dev->class_dev,
				 "%s: DAC not-ready for channel %i\n",
				 __func__, chan);
		पूर्ण अन्यथा अणु
			outl(val | APCI3501_AO_DATA_CHAN(chan),
			     dev->iobase + APCI3501_AO_DATA_REG);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apci3501_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा apci3501_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ao_n_chan;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	devpriv->amcc = pci_resource_start(pcidev, 0);
	dev->iobase = pci_resource_start(pcidev, 1);

	ao_n_chan = apci3501_eeprom_get_ao_n_chan(dev);

	ret = comedi_alloc_subdevices(dev, 5);
	अगर (ret)
		वापस ret;

	/* Initialize the analog output subdevice */
	s = &dev->subdevices[0];
	अगर (ao_n_chan) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_GROUND | SDF_COMMON;
		s->n_chan	= ao_n_chan;
		s->maxdata	= 0x3fff;
		s->range_table	= &apci3501_ao_range;
		s->insn_ग_लिखो	= apci3501_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Initialize the digital input subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 2;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci3501_di_insn_bits;

	/* Initialize the digital output subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci3501_करो_insn_bits;

	/* Timer/Watchकरोg subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_UNUSED;

	/* Initialize the eeprom subdevice */
	s = &dev->subdevices[4];
	s->type		= COMEDI_SUBD_MEMORY;
	s->subdev_flags	= SDF_READABLE | SDF_INTERNAL;
	s->n_chan	= 256;
	s->maxdata	= 0xffff;
	s->insn_पढ़ो	= apci3501_eeprom_insn_पढ़ो;

	apci3501_reset(dev);
	वापस 0;
पूर्ण

अटल व्योम apci3501_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		apci3501_reset(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver apci3501_driver = अणु
	.driver_name	= "addi_apci_3501",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci3501_स्वतः_attach,
	.detach		= apci3501_detach,
पूर्ण;

अटल पूर्णांक apci3501_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci3501_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci3501_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADDIDATA, 0x3001) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci3501_pci_table);

अटल काष्ठा pci_driver apci3501_pci_driver = अणु
	.name		= "addi_apci_3501",
	.id_table	= apci3501_pci_table,
	.probe		= apci3501_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci3501_driver, apci3501_pci_driver);

MODULE_DESCRIPTION("ADDI-DATA APCI-3501 Analog output board");
MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_LICENSE("GPL");
