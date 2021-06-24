<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * icp_multi.c
 * Comedi driver क्रम Inova ICP_MULTI board
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2002 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: icp_multi
 * Description: Inova ICP_MULTI
 * Devices: [Inova] ICP_MULTI (icp_multi)
 * Author: Anne Smorthit <anne.smorthit@sfwte.ch>
 * Status: works
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 *
 * The driver works क्रम analog input and output and digital input and
 * output. It करोes not work with पूर्णांकerrupts or with the counters. Currently
 * no support क्रम DMA.
 *
 * It has 16 single-ended or 8 dअगरferential Analogue Input channels with
 * 12-bit resolution.  Ranges : 5V, 10V, +/-5V, +/-10V, 0..20mA and 4..20mA.
 * Input ranges can be inभागidually programmed क्रम each channel.  Voltage or
 * current measurement is selected by jumper.
 *
 * There are 4 x 12-bit Analogue Outमाला_दो.  Ranges : 5V, 10V, +/-5V, +/-10V
 *
 * 16 x Digital Inमाला_दो, 24V
 *
 * 8 x Digital Outमाला_दो, 24V, 1A
 *
 * 4 x 16-bit counters - not implemented
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश "../comedi_pci.h"

#घोषणा ICP_MULTI_ADC_CSR	0x00	/* R/W: ADC command/status रेजिस्टर */
#घोषणा ICP_MULTI_ADC_CSR_ST	BIT(0)	/* Start ADC */
#घोषणा ICP_MULTI_ADC_CSR_BSY	BIT(0)	/* ADC busy */
#घोषणा ICP_MULTI_ADC_CSR_BI	BIT(4)	/* Bipolar input range */
#घोषणा ICP_MULTI_ADC_CSR_RA	BIT(5)	/* Input range 0 = 5V, 1 = 10V */
#घोषणा ICP_MULTI_ADC_CSR_DI	BIT(6)	/* Input mode 1 = dअगरferential */
#घोषणा ICP_MULTI_ADC_CSR_DI_CHAN(x) (((x) & 0x7) << 9)
#घोषणा ICP_MULTI_ADC_CSR_SE_CHAN(x) (((x) & 0xf) << 8)
#घोषणा ICP_MULTI_AI		2	/* R:   Analogue input data */
#घोषणा ICP_MULTI_DAC_CSR	0x04	/* R/W: DAC command/status रेजिस्टर */
#घोषणा ICP_MULTI_DAC_CSR_ST	BIT(0)	/* Start DAC */
#घोषणा ICP_MULTI_DAC_CSR_BSY	BIT(0)	/* DAC busy */
#घोषणा ICP_MULTI_DAC_CSR_BI	BIT(4)	/* Bipolar output range */
#घोषणा ICP_MULTI_DAC_CSR_RA	BIT(5)	/* Output range 0 = 5V, 1 = 10V */
#घोषणा ICP_MULTI_DAC_CSR_CHAN(x) (((x) & 0x3) << 8)
#घोषणा ICP_MULTI_AO		6	/* R/W: Analogue output data */
#घोषणा ICP_MULTI_DI		8	/* R/W: Digital inमाला_दो */
#घोषणा ICP_MULTI_DO		0x0A	/* R/W: Digital outमाला_दो */
#घोषणा ICP_MULTI_INT_EN	0x0c	/* R/W: Interrupt enable रेजिस्टर */
#घोषणा ICP_MULTI_INT_STAT	0x0e	/* R/W: Interrupt status रेजिस्टर */
#घोषणा ICP_MULTI_INT_ADC_RDY	BIT(0)	/* A/D conversion पढ़ोy पूर्णांकerrupt */
#घोषणा ICP_MULTI_INT_DAC_RDY	BIT(1)	/* D/A conversion पढ़ोy पूर्णांकerrupt */
#घोषणा ICP_MULTI_INT_DOUT_ERR	BIT(2)	/* Digital output error पूर्णांकerrupt */
#घोषणा ICP_MULTI_INT_DIN_STAT	BIT(3)	/* Digital input status change पूर्णांक. */
#घोषणा ICP_MULTI_INT_CIE0	BIT(4)	/* Counter 0 overrun पूर्णांकerrupt */
#घोषणा ICP_MULTI_INT_CIE1	BIT(5)	/* Counter 1 overrun पूर्णांकerrupt */
#घोषणा ICP_MULTI_INT_CIE2	BIT(6)	/* Counter 2 overrun पूर्णांकerrupt */
#घोषणा ICP_MULTI_INT_CIE3	BIT(7)	/* Counter 3 overrun पूर्णांकerrupt */
#घोषणा ICP_MULTI_INT_MASK	0xff	/* All पूर्णांकerrupts */
#घोषणा ICP_MULTI_CNTR0		0x10	/* R/W: Counter 0 */
#घोषणा ICP_MULTI_CNTR1		0x12	/* R/W: counter 1 */
#घोषणा ICP_MULTI_CNTR2		0x14	/* R/W: Counter 2 */
#घोषणा ICP_MULTI_CNTR3		0x16	/* R/W: Counter 3 */

/* analog input and output have the same range options */
अटल स्थिर काष्ठा comedi_lrange icp_multi_ranges = अणु
	4, अणु
		UNI_RANGE(5),
		UNI_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर range_codes_analog[] = अणु 0x00, 0x20, 0x10, 0x30 पूर्ण;

अटल पूर्णांक icp_multi_ai_eoc(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn,
			    अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = पढ़ोw(dev->mmio + ICP_MULTI_ADC_CSR);
	अगर ((status & ICP_MULTI_ADC_CSR_BSY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक icp_multi_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(insn->chanspec);
	अचिन्हित पूर्णांक adc_csr;
	पूर्णांक ret = 0;
	पूर्णांक n;

	/* Set mode and range data क्रम specअगरied channel */
	अगर (aref == AREF_DIFF) अणु
		adc_csr = ICP_MULTI_ADC_CSR_DI_CHAN(chan) |
			  ICP_MULTI_ADC_CSR_DI;
	पूर्ण अन्यथा अणु
		adc_csr = ICP_MULTI_ADC_CSR_SE_CHAN(chan);
	पूर्ण
	adc_csr |= range_codes_analog[range];
	ग_लिखोw(adc_csr, dev->mmio + ICP_MULTI_ADC_CSR);

	क्रम (n = 0; n < insn->n; n++) अणु
		/*  Set start ADC bit */
		ग_लिखोw(adc_csr | ICP_MULTI_ADC_CSR_ST,
		       dev->mmio + ICP_MULTI_ADC_CSR);

		udelay(1);

		/*  Wait क्रम conversion to complete, or get fed up रुकोing */
		ret = comedi_समयout(dev, s, insn, icp_multi_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		data[n] = (पढ़ोw(dev->mmio + ICP_MULTI_AI) >> 4) & 0x0fff;
	पूर्ण

	वापस ret ? ret : n;
पूर्ण

अटल पूर्णांक icp_multi_ao_पढ़ोy(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = पढ़ोw(dev->mmio + ICP_MULTI_DAC_CSR);
	अगर ((status & ICP_MULTI_DAC_CSR_BSY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक icp_multi_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक dac_csr;
	पूर्णांक i;

	/* Select channel and range */
	dac_csr = ICP_MULTI_DAC_CSR_CHAN(chan);
	dac_csr |= range_codes_analog[range];
	ग_लिखोw(dac_csr, dev->mmio + ICP_MULTI_DAC_CSR);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];
		पूर्णांक ret;

		/* Wait क्रम analog output to be पढ़ोy क्रम new data */
		ret = comedi_समयout(dev, s, insn, icp_multi_ao_पढ़ोy, 0);
		अगर (ret)
			वापस ret;

		ग_लिखोw(val, dev->mmio + ICP_MULTI_AO);

		/* Set start conversion bit to ग_लिखो data to channel */
		ग_लिखोw(dac_csr | ICP_MULTI_DAC_CSR_ST,
		       dev->mmio + ICP_MULTI_DAC_CSR);

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक icp_multi_di_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	data[1] = पढ़ोw(dev->mmio + ICP_MULTI_DI);

	वापस insn->n;
पूर्ण

अटल पूर्णांक icp_multi_करो_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		ग_लिखोw(s->state, dev->mmio + ICP_MULTI_DO);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक icp_multi_reset(काष्ठा comedi_device *dev)
अणु
	पूर्णांक i;

	/* Disable all पूर्णांकerrupts and clear any requests */
	ग_लिखोw(0, dev->mmio + ICP_MULTI_INT_EN);
	ग_लिखोw(ICP_MULTI_INT_MASK, dev->mmio + ICP_MULTI_INT_STAT);

	/* Reset the analog output channels to 0V */
	क्रम (i = 0; i < 4; i++) अणु
		अचिन्हित पूर्णांक dac_csr = ICP_MULTI_DAC_CSR_CHAN(i);

		/* Select channel and 0..5V range */
		ग_लिखोw(dac_csr, dev->mmio + ICP_MULTI_DAC_CSR);

		/* Output 0V */
		ग_लिखोw(0, dev->mmio + ICP_MULTI_AO);

		/* Set start conversion bit to ग_लिखो data to channel */
		ग_लिखोw(dac_csr | ICP_MULTI_DAC_CSR_ST,
		       dev->mmio + ICP_MULTI_DAC_CSR);
		udelay(1);
	पूर्ण

	/* Digital outमाला_दो to 0 */
	ग_लिखोw(0, dev->mmio + ICP_MULTI_DO);

	वापस 0;
पूर्ण

अटल पूर्णांक icp_multi_स्वतः_attach(काष्ठा comedi_device *dev,
				 अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->mmio = pci_ioremap_bar(pcidev, 2);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	icp_multi_reset(dev);

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_COMMON | SDF_GROUND | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= 0x0fff;
	s->range_table	= &icp_multi_ranges;
	s->insn_पढ़ो	= icp_multi_ai_insn_पढ़ो;

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_GROUND | SDF_COMMON;
	s->n_chan	= 4;
	s->maxdata	= 0x0fff;
	s->range_table	= &icp_multi_ranges;
	s->insn_ग_लिखो	= icp_multi_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= icp_multi_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= icp_multi_करो_insn_bits;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver icp_multi_driver = अणु
	.driver_name	= "icp_multi",
	.module		= THIS_MODULE,
	.स्वतः_attach	= icp_multi_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक icp_multi_pci_probe(काष्ठा pci_dev *dev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &icp_multi_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id icp_multi_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ICP, 0x8000) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, icp_multi_pci_table);

अटल काष्ठा pci_driver icp_multi_pci_driver = अणु
	.name		= "icp_multi",
	.id_table	= icp_multi_pci_table,
	.probe		= icp_multi_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(icp_multi_driver, icp_multi_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Inova ICP_MULTI board");
MODULE_LICENSE("GPL");
