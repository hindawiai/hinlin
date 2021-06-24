<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/cb_pcimdas.c
 * Comedi driver क्रम Computer Boards PCIM-DAS1602/16 and PCIe-DAS1602/16
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: cb_pcimdas
 * Description: Measurement Computing PCI Migration series boards
 * Devices: [ComputerBoards] PCIM-DAS1602/16 (cb_pcimdas), PCIe-DAS1602/16
 * Author: Riअक्षरd Bytheway
 * Updated: Mon, 13 Oct 2014 11:57:39 +0000
 * Status: experimental
 *
 * Written to support the PCIM-DAS1602/16 and PCIe-DAS1602/16.
 *
 * Configuration Options:
 *   none
 *
 * Manual configuration of PCI(e) cards is not supported; they are configured
 * स्वतःmatically.
 *
 * Developed from cb_pcidas and skel by Riअक्षरd Bytheway (mocelet@sucs.org).
 * Only supports DIO, AO and simple AI in it's present क्रमm.
 * No पूर्णांकerrupts, multi channel or FIFO AI,
 * although the card looks like it could support this.
 *
 * https://www.mccdaq.com/PDFs/Manuals/pcim-das1602-16.pdf
 * https://www.mccdaq.com/PDFs/Manuals/pcie-das1602-16.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "comedi_8254.h"
#समावेश "plx9052.h"
#समावेश "8255.h"

/*
 * PCI Bar 1 Register map
 * see plx9052.h क्रम रेजिस्टर and bit defines
 */

/*
 * PCI Bar 2 Register map (devpriv->daqio)
 */
#घोषणा PCIMDAS_AI_REG			0x00
#घोषणा PCIMDAS_AI_SOFTTRIG_REG		0x00
#घोषणा PCIMDAS_AO_REG(x)		(0x02 + ((x) * 2))

/*
 * PCI Bar 3 Register map (devpriv->BADR3)
 */
#घोषणा PCIMDAS_MUX_REG			0x00
#घोषणा PCIMDAS_MUX(_lo, _hi)		((_lo) | ((_hi) << 4))
#घोषणा PCIMDAS_DI_DO_REG		0x01
#घोषणा PCIMDAS_STATUS_REG		0x02
#घोषणा PCIMDAS_STATUS_EOC		BIT(7)
#घोषणा PCIMDAS_STATUS_UB		BIT(6)
#घोषणा PCIMDAS_STATUS_MUX		BIT(5)
#घोषणा PCIMDAS_STATUS_CLK		BIT(4)
#घोषणा PCIMDAS_STATUS_TO_CURR_MUX(x)	((x) & 0xf)
#घोषणा PCIMDAS_CONV_STATUS_REG		0x03
#घोषणा PCIMDAS_CONV_STATUS_EOC		BIT(7)
#घोषणा PCIMDAS_CONV_STATUS_EOB		BIT(6)
#घोषणा PCIMDAS_CONV_STATUS_EOA		BIT(5)
#घोषणा PCIMDAS_CONV_STATUS_FNE		BIT(4)
#घोषणा PCIMDAS_CONV_STATUS_FHF		BIT(3)
#घोषणा PCIMDAS_CONV_STATUS_OVERRUN	BIT(2)
#घोषणा PCIMDAS_IRQ_REG			0x04
#घोषणा PCIMDAS_IRQ_INTE		BIT(7)
#घोषणा PCIMDAS_IRQ_INT			BIT(6)
#घोषणा PCIMDAS_IRQ_OVERRUN		BIT(4)
#घोषणा PCIMDAS_IRQ_EOA			BIT(3)
#घोषणा PCIMDAS_IRQ_EOA_INT_SEL		BIT(2)
#घोषणा PCIMDAS_IRQ_INTSEL(x)		((x) << 0)
#घोषणा PCIMDAS_IRQ_INTSEL_EOC		PCIMDAS_IRQ_INTSEL(0)
#घोषणा PCIMDAS_IRQ_INTSEL_FNE		PCIMDAS_IRQ_INTSEL(1)
#घोषणा PCIMDAS_IRQ_INTSEL_EOB		PCIMDAS_IRQ_INTSEL(2)
#घोषणा PCIMDAS_IRQ_INTSEL_FHF_EOA	PCIMDAS_IRQ_INTSEL(3)
#घोषणा PCIMDAS_PACER_REG		0x05
#घोषणा PCIMDAS_PACER_GATE_STATUS	BIT(6)
#घोषणा PCIMDAS_PACER_GATE_POL		BIT(5)
#घोषणा PCIMDAS_PACER_GATE_LATCH	BIT(4)
#घोषणा PCIMDAS_PACER_GATE_EN		BIT(3)
#घोषणा PCIMDAS_PACER_EXT_PACER_POL	BIT(2)
#घोषणा PCIMDAS_PACER_SRC(x)		((x) << 0)
#घोषणा PCIMDAS_PACER_SRC_POLLED	PCIMDAS_PACER_SRC(0)
#घोषणा PCIMDAS_PACER_SRC_EXT		PCIMDAS_PACER_SRC(2)
#घोषणा PCIMDAS_PACER_SRC_INT		PCIMDAS_PACER_SRC(3)
#घोषणा PCIMDAS_PACER_SRC_MASK		(3 << 0)
#घोषणा PCIMDAS_BURST_REG		0x06
#घोषणा PCIMDAS_BURST_BME		BIT(1)
#घोषणा PCIMDAS_BURST_CONV_EN		BIT(0)
#घोषणा PCIMDAS_GAIN_REG		0x07
#घोषणा PCIMDAS_8254_BASE		0x08
#घोषणा PCIMDAS_USER_CNTR_REG		0x0c
#घोषणा PCIMDAS_USER_CNTR_CTR1_CLK_SEL	BIT(0)
#घोषणा PCIMDAS_RESIDUE_MSB_REG		0x0d
#घोषणा PCIMDAS_RESIDUE_LSB_REG		0x0e

/*
 * PCI Bar 4 Register map (dev->iobase)
 */
#घोषणा PCIMDAS_8255_BASE		0x00

अटल स्थिर काष्ठा comedi_lrange cb_pcimdas_ai_bip_range = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange cb_pcimdas_ai_uni_range = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

/*
 * The Analog Output range is not programmable. The DAC ranges are
 * jumper-settable on the board. The settings are not software-पढ़ोable.
 */
अटल स्थिर काष्ठा comedi_lrange cb_pcimdas_ao_range = अणु
	6, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		UNI_RANGE(10),
		UNI_RANGE(5),
		RANGE_ext(-1, 1),
		RANGE_ext(0, 1)
	पूर्ण
पूर्ण;

/*
 * this काष्ठाure is क्रम data unique to this hardware driver.  If
 * several hardware drivers keep similar inक्रमmation in this काष्ठाure,
 * feel मुक्त to suggest moving the variable to the काष्ठा comedi_device
 * काष्ठा.
 */
काष्ठा cb_pcimdas_निजी अणु
	/* base addresses */
	अचिन्हित दीर्घ daqio;
	अचिन्हित दीर्घ BADR3;
पूर्ण;

अटल पूर्णांक cb_pcimdas_ai_eoc(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित दीर्घ context)
अणु
	काष्ठा cb_pcimdas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status;

	status = inb(devpriv->BADR3 + PCIMDAS_STATUS_REG);
	अगर ((status & PCIMDAS_STATUS_EOC) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक cb_pcimdas_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcimdas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक n;
	अचिन्हित पूर्णांक d;
	पूर्णांक ret;

	/*  only support sw initiated पढ़ोs from a single channel */

	/* configure क्रम sw initiated पढ़ो */
	d = inb(devpriv->BADR3 + PCIMDAS_PACER_REG);
	अगर ((d & PCIMDAS_PACER_SRC_MASK) != PCIMDAS_PACER_SRC_POLLED) अणु
		d &= ~PCIMDAS_PACER_SRC_MASK;
		d |= PCIMDAS_PACER_SRC_POLLED;
		outb(d, devpriv->BADR3 + PCIMDAS_PACER_REG);
	पूर्ण

	/* set bursting off, conversions on */
	outb(PCIMDAS_BURST_CONV_EN, devpriv->BADR3 + PCIMDAS_BURST_REG);

	/* set range */
	outb(range, devpriv->BADR3 + PCIMDAS_GAIN_REG);

	/* set mux क्रम single channel scan */
	outb(PCIMDAS_MUX(chan, chan), devpriv->BADR3 + PCIMDAS_MUX_REG);

	/* convert n samples */
	क्रम (n = 0; n < insn->n; n++) अणु
		/* trigger conversion */
		outw(0, devpriv->daqio + PCIMDAS_AI_SOFTTRIG_REG);

		/* रुको क्रम conversion to end */
		ret = comedi_समयout(dev, s, insn, cb_pcimdas_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		/* पढ़ो data */
		data[n] = inw(devpriv->daqio + PCIMDAS_AI_REG);
	पूर्ण

	/* वापस the number of samples पढ़ो/written */
	वापस n;
पूर्ण

अटल पूर्णांक cb_pcimdas_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcimdas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outw(val, devpriv->daqio + PCIMDAS_AO_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक cb_pcimdas_di_insn_bits(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcimdas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val;

	val = inb(devpriv->BADR3 + PCIMDAS_DI_DO_REG);

	data[1] = val & 0x0f;

	वापस insn->n;
पूर्ण

अटल पूर्णांक cb_pcimdas_करो_insn_bits(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcimdas_निजी *devpriv = dev->निजी;

	अगर (comedi_dio_update_state(s, data))
		outb(s->state, devpriv->BADR3 + PCIMDAS_DI_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक cb_pcimdas_counter_insn_config(काष्ठा comedi_device *dev,
					  काष्ठा comedi_subdevice *s,
					  काष्ठा comedi_insn *insn,
					  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcimdas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक ctrl;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		चयन (data[1]) अणु
		हाल 0:	/* पूर्णांकernal 100 kHz घड़ी */
			ctrl = PCIMDAS_USER_CNTR_CTR1_CLK_SEL;
			अवरोध;
		हाल 1:	/* बाह्यal clk on pin 21 */
			ctrl = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		outb(ctrl, devpriv->BADR3 + PCIMDAS_USER_CNTR_REG);
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		ctrl = inb(devpriv->BADR3 + PCIMDAS_USER_CNTR_REG);
		अगर (ctrl & PCIMDAS_USER_CNTR_CTR1_CLK_SEL) अणु
			data[1] = 0;
			data[2] = I8254_OSC_BASE_100KHZ;
		पूर्ण अन्यथा अणु
			data[1] = 1;
			data[2] = 0;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल अचिन्हित पूर्णांक cb_pcimdas_pacer_clk(काष्ठा comedi_device *dev)
अणु
	काष्ठा cb_pcimdas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status;

	/* The Pacer Clock jumper selects a 10 MHz or 1 MHz घड़ी */
	status = inb(devpriv->BADR3 + PCIMDAS_STATUS_REG);
	अगर (status & PCIMDAS_STATUS_CLK)
		वापस I8254_OSC_BASE_10MHZ;
	वापस I8254_OSC_BASE_1MHZ;
पूर्ण

अटल bool cb_pcimdas_is_ai_se(काष्ठा comedi_device *dev)
अणु
	काष्ठा cb_pcimdas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status;

	/*
	 * The number of Analog Input channels is set with the
	 * Analog Input Mode Switch on the board. The board can
	 * have 16 single-ended or 8 dअगरferential channels.
	 */
	status = inb(devpriv->BADR3 + PCIMDAS_STATUS_REG);
	वापस status & PCIMDAS_STATUS_MUX;
पूर्ण

अटल bool cb_pcimdas_is_ai_uni(काष्ठा comedi_device *dev)
अणु
	काष्ठा cb_pcimdas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status;

	/*
	 * The Analog Input range polarity is set with the
	 * Analog Input Polarity Switch on the board. The
	 * inमाला_दो can be set to Unipolar or Bipolar ranges.
	 */
	status = inb(devpriv->BADR3 + PCIMDAS_STATUS_REG);
	वापस status & PCIMDAS_STATUS_UB;
पूर्ण

अटल पूर्णांक cb_pcimdas_स्वतः_attach(काष्ठा comedi_device *dev,
				  अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा cb_pcimdas_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	devpriv->daqio = pci_resource_start(pcidev, 2);
	devpriv->BADR3 = pci_resource_start(pcidev, 3);
	dev->iobase = pci_resource_start(pcidev, 4);

	dev->pacer = comedi_8254_init(devpriv->BADR3 + PCIMDAS_8254_BASE,
				      cb_pcimdas_pacer_clk(dev),
				      I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 6);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE;
	अगर (cb_pcimdas_is_ai_se(dev)) अणु
		s->subdev_flags	|= SDF_GROUND;
		s->n_chan	= 16;
	पूर्ण अन्यथा अणु
		s->subdev_flags	|= SDF_DIFF;
		s->n_chan	= 8;
	पूर्ण
	s->maxdata	= 0xffff;
	s->range_table	= cb_pcimdas_is_ai_uni(dev) ? &cb_pcimdas_ai_uni_range
						    : &cb_pcimdas_ai_bip_range;
	s->insn_पढ़ो	= cb_pcimdas_ai_insn_पढ़ो;

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 0xfff;
	s->range_table	= &cb_pcimdas_ao_range;
	s->insn_ग_लिखो	= cb_pcimdas_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital I/O subdevice */
	s = &dev->subdevices[2];
	ret = subdev_8255_init(dev, s, शून्य, PCIMDAS_8255_BASE);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice (मुख्य connector) */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= cb_pcimdas_di_insn_bits;

	/* Digital Output subdevice (मुख्य connector) */
	s = &dev->subdevices[4];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= cb_pcimdas_करो_insn_bits;

	/* Counter subdevice (8254) */
	s = &dev->subdevices[5];
	comedi_8254_subdevice_init(s, dev->pacer);

	dev->pacer->insn_config = cb_pcimdas_counter_insn_config;

	/* counters 1 and 2 are used पूर्णांकernally क्रम the pacer */
	comedi_8254_set_busy(dev->pacer, 1, true);
	comedi_8254_set_busy(dev->pacer, 2, true);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver cb_pcimdas_driver = अणु
	.driver_name	= "cb_pcimdas",
	.module		= THIS_MODULE,
	.स्वतः_attach	= cb_pcimdas_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक cb_pcimdas_pci_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &cb_pcimdas_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cb_pcimdas_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CB, 0x0056) पूर्ण,	/* PCIM-DAS1602/16 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_CB, 0x0115) पूर्ण,	/* PCIe-DAS1602/16 */
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cb_pcimdas_pci_table);

अटल काष्ठा pci_driver cb_pcimdas_pci_driver = अणु
	.name		= "cb_pcimdas",
	.id_table	= cb_pcimdas_pci_table,
	.probe		= cb_pcimdas_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(cb_pcimdas_driver, cb_pcimdas_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for PCIM-DAS1602/16 and PCIe-DAS1602/16");
MODULE_LICENSE("GPL");
