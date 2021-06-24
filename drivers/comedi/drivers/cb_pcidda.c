<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/cb_pcidda.c
 * Driver क्रम the ComputerBoards / MeasurementComputing PCI-DDA series.
 *
 * Copyright (C) 2001 Ivan Martinez <ivanmr@altavista.com>
 * Copyright (C) 2001 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-8 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: cb_pcidda
 * Description: MeasurementComputing PCI-DDA series
 * Devices: [Measurement Computing] PCI-DDA08/12 (pci-dda08/12),
 *   PCI-DDA04/12 (pci-dda04/12), PCI-DDA02/12 (pci-dda02/12),
 *   PCI-DDA08/16 (pci-dda08/16), PCI-DDA04/16 (pci-dda04/16),
 *   PCI-DDA02/16 (pci-dda02/16)
 * Author: Ivan Martinez <ivanmr@altavista.com>
 *	   Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Status: works
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 *
 * Only simple analog output writing is supported.
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

#समावेश "8255.h"

#घोषणा EEPROM_SIZE	128	/*  number of entries in eeprom */
/* maximum number of ao channels क्रम supported boards */
#घोषणा MAX_AO_CHANNELS 8

/* Digital I/O रेजिस्टरs */
#घोषणा CB_DDA_DIO0_8255_BASE		0x00
#घोषणा CB_DDA_DIO1_8255_BASE		0x04

/* DAC रेजिस्टरs */
#घोषणा CB_DDA_DA_CTRL_REG		0x00	   /* D/A Control Register  */
#घोषणा CB_DDA_DA_CTRL_SU		BIT(0)   /*  Simultaneous update  */
#घोषणा CB_DDA_DA_CTRL_EN		BIT(1)   /*  Enable specअगरied DAC */
#घोषणा CB_DDA_DA_CTRL_DAC(x)		((x) << 2) /*  Specअगरy DAC channel  */
#घोषणा CB_DDA_DA_CTRL_RANGE2V5		(0 << 6)   /*  2.5V range           */
#घोषणा CB_DDA_DA_CTRL_RANGE5V		(2 << 6)   /*  5V range             */
#घोषणा CB_DDA_DA_CTRL_RANGE10V		(3 << 6)   /*  10V range            */
#घोषणा CB_DDA_DA_CTRL_UNIP		BIT(8)   /*  Unipolar range       */

#घोषणा DACALIBRATION1	4	/*  D/A CALIBRATION REGISTER 1 */
/* ग_लिखो bits */
/* serial data input क्रम eeprom, caldacs, reference dac */
#घोषणा SERIAL_IN_BIT   0x1
#घोषणा	CAL_CHANNEL_MASK	(0x7 << 1)
#घोषणा	CAL_CHANNEL_BITS(channel)	(((channel) << 1) & CAL_CHANNEL_MASK)
/* पढ़ो bits */
#घोषणा	CAL_COUNTER_MASK	0x1f
/* calibration counter overflow status bit */
#घोषणा CAL_COUNTER_OVERFLOW_BIT        0x20
/* analog output is less than reference dac voltage */
#घोषणा AO_BELOW_REF_BIT        0x40
#घोषणा	SERIAL_OUT_BIT	0x80	/*  serial data out, क्रम पढ़ोing from eeprom */

#घोषणा DACALIBRATION2	6	/*  D/A CALIBRATION REGISTER 2 */
#घोषणा	SELECT_EEPROM_BIT	0x1	/*  send serial data in to eeprom */
/* करोn't send serial data to MAX542 reference dac */
#घोषणा DESELECT_REF_DAC_BIT    0x2
/* करोn't send serial data to caldac n */
#घोषणा DESELECT_CALDAC_BIT(n)  (0x4 << (n))
/* manual says to set this bit with no explanation */
#घोषणा DUMMY_BIT       0x40

#घोषणा CB_DDA_DA_DATA_REG(x)		(0x08 + ((x) * 2))

/* Offsets क्रम the caldac channels */
#घोषणा CB_DDA_CALDAC_FINE_GAIN		0
#घोषणा CB_DDA_CALDAC_COURSE_GAIN	1
#घोषणा CB_DDA_CALDAC_COURSE_OFFSET	2
#घोषणा CB_DDA_CALDAC_FINE_OFFSET	3

अटल स्थिर काष्ठा comedi_lrange cb_pcidda_ranges = अणु
	6, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5)
	पूर्ण
पूर्ण;

क्रमागत cb_pcidda_boardid अणु
	BOARD_DDA02_12,
	BOARD_DDA04_12,
	BOARD_DDA08_12,
	BOARD_DDA02_16,
	BOARD_DDA04_16,
	BOARD_DDA08_16,
पूर्ण;

काष्ठा cb_pcidda_board अणु
	स्थिर अक्षर *name;
	पूर्णांक ao_chans;
	पूर्णांक ao_bits;
पूर्ण;

अटल स्थिर काष्ठा cb_pcidda_board cb_pcidda_boards[] = अणु
	[BOARD_DDA02_12] = अणु
		.name		= "pci-dda02/12",
		.ao_chans	= 2,
		.ao_bits	= 12,
	पूर्ण,
	[BOARD_DDA04_12] = अणु
		.name		= "pci-dda04/12",
		.ao_chans	= 4,
		.ao_bits	= 12,
	पूर्ण,
	[BOARD_DDA08_12] = अणु
		.name		= "pci-dda08/12",
		.ao_chans	= 8,
		.ao_bits	= 12,
	पूर्ण,
	[BOARD_DDA02_16] = अणु
		.name		= "pci-dda02/16",
		.ao_chans	= 2,
		.ao_bits	= 16,
	पूर्ण,
	[BOARD_DDA04_16] = अणु
		.name		= "pci-dda04/16",
		.ao_chans	= 4,
		.ao_bits	= 16,
	पूर्ण,
	[BOARD_DDA08_16] = अणु
		.name		= "pci-dda08/16",
		.ao_chans	= 8,
		.ao_bits	= 16,
	पूर्ण,
पूर्ण;

काष्ठा cb_pcidda_निजी अणु
	अचिन्हित दीर्घ daqio;
	/* bits last written to da calibration रेजिस्टर 1 */
	अचिन्हित पूर्णांक dac_cal1_bits;
	/* current range settings क्रम output channels */
	अचिन्हित पूर्णांक ao_range[MAX_AO_CHANNELS];
	u16 eeprom_data[EEPROM_SIZE];	/*  software copy of board's eeprom */
पूर्ण;

/* lowlevel पढ़ो from eeprom */
अटल अचिन्हित पूर्णांक cb_pcidda_serial_in(काष्ठा comedi_device *dev)
अणु
	काष्ठा cb_pcidda_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक value = 0;
	पूर्णांक i;
	स्थिर पूर्णांक value_width = 16;	/*  number of bits wide values are */

	क्रम (i = 1; i <= value_width; i++) अणु
		/*  पढ़ो bits most signअगरicant bit first */
		अगर (inw_p(devpriv->daqio + DACALIBRATION1) & SERIAL_OUT_BIT)
			value |= 1 << (value_width - i);
	पूर्ण

	वापस value;
पूर्ण

/* lowlevel ग_लिखो to eeprom/dac */
अटल व्योम cb_pcidda_serial_out(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक value,
				 अचिन्हित पूर्णांक num_bits)
अणु
	काष्ठा cb_pcidda_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	क्रम (i = 1; i <= num_bits; i++) अणु
		/*  send bits most signअगरicant bit first */
		अगर (value & (1 << (num_bits - i)))
			devpriv->dac_cal1_bits |= SERIAL_IN_BIT;
		अन्यथा
			devpriv->dac_cal1_bits &= ~SERIAL_IN_BIT;
		outw_p(devpriv->dac_cal1_bits, devpriv->daqio + DACALIBRATION1);
	पूर्ण
पूर्ण

/* पढ़ोs a 16 bit value from board's eeprom */
अटल अचिन्हित पूर्णांक cb_pcidda_पढ़ो_eeprom(काष्ठा comedi_device *dev,
					  अचिन्हित पूर्णांक address)
अणु
	काष्ठा cb_pcidda_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक cal2_bits;
	अचिन्हित पूर्णांक value;
	/* one caldac क्रम every two dac channels */
	स्थिर पूर्णांक max_num_caldacs = 4;
	/* bits to send to tell eeprom we want to पढ़ो */
	स्थिर पूर्णांक पढ़ो_inकाष्ठाion = 0x6;
	स्थिर पूर्णांक inकाष्ठाion_length = 3;
	स्थिर पूर्णांक address_length = 8;

	/*  send serial output stream to eeprom */
	cal2_bits = SELECT_EEPROM_BIT | DESELECT_REF_DAC_BIT | DUMMY_BIT;
	/*  deactivate caldacs (one caldac क्रम every two channels) */
	क्रम (i = 0; i < max_num_caldacs; i++)
		cal2_bits |= DESELECT_CALDAC_BIT(i);
	outw_p(cal2_bits, devpriv->daqio + DACALIBRATION2);

	/*  tell eeprom we want to पढ़ो */
	cb_pcidda_serial_out(dev, पढ़ो_inकाष्ठाion, inकाष्ठाion_length);
	/*  send address we want to पढ़ो from */
	cb_pcidda_serial_out(dev, address, address_length);

	value = cb_pcidda_serial_in(dev);

	/*  deactivate eeprom */
	cal2_bits &= ~SELECT_EEPROM_BIT;
	outw_p(cal2_bits, devpriv->daqio + DACALIBRATION2);

	वापस value;
पूर्ण

/* ग_लिखोs to 8 bit calibration dacs */
अटल व्योम cb_pcidda_ग_लिखो_caldac(काष्ठा comedi_device *dev,
				   अचिन्हित पूर्णांक caldac, अचिन्हित पूर्णांक channel,
				   अचिन्हित पूर्णांक value)
अणु
	काष्ठा cb_pcidda_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक cal2_bits;
	अचिन्हित पूर्णांक i;
	/* caldacs use 3 bit channel specअगरication */
	स्थिर पूर्णांक num_channel_bits = 3;
	स्थिर पूर्णांक num_caldac_bits = 8;	/*  8 bit calibration dacs */
	/* one caldac क्रम every two dac channels */
	स्थिर पूर्णांक max_num_caldacs = 4;

	/* ग_लिखो 3 bit channel */
	cb_pcidda_serial_out(dev, channel, num_channel_bits);
	/*  ग_लिखो 8 bit caldac value */
	cb_pcidda_serial_out(dev, value, num_caldac_bits);

/*
 * latch stream पूर्णांकo appropriate caldac deselect reference dac
 */
	cal2_bits = DESELECT_REF_DAC_BIT | DUMMY_BIT;
	/*  deactivate caldacs (one caldac क्रम every two channels) */
	क्रम (i = 0; i < max_num_caldacs; i++)
		cal2_bits |= DESELECT_CALDAC_BIT(i);
	/*  activate the caldac we want */
	cal2_bits &= ~DESELECT_CALDAC_BIT(caldac);
	outw_p(cal2_bits, devpriv->daqio + DACALIBRATION2);
	/*  deactivate caldac */
	cal2_bits |= DESELECT_CALDAC_BIT(caldac);
	outw_p(cal2_bits, devpriv->daqio + DACALIBRATION2);
पूर्ण

/* set caldacs to eeprom values क्रम given channel and range */
अटल व्योम cb_pcidda_calibrate(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक channel,
				अचिन्हित पूर्णांक range)
अणु
	काष्ठा cb_pcidda_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक caldac = channel / 2;	/* two caldacs per channel */
	अचिन्हित पूर्णांक chan = 4 * (channel % 2);	/* caldac channel base */
	अचिन्हित पूर्णांक index = 2 * range + 12 * channel;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक gain;

	/* save range so we can tell when we need to पढ़ोjust calibration */
	devpriv->ao_range[channel] = range;

	/* get values from eeprom data */
	offset = devpriv->eeprom_data[0x7 + index];
	gain = devpriv->eeprom_data[0x8 + index];

	/* set caldacs */
	cb_pcidda_ग_लिखो_caldac(dev, caldac, chan + CB_DDA_CALDAC_COURSE_OFFSET,
			       (offset >> 8) & 0xff);
	cb_pcidda_ग_लिखो_caldac(dev, caldac, chan + CB_DDA_CALDAC_FINE_OFFSET,
			       offset & 0xff);
	cb_pcidda_ग_लिखो_caldac(dev, caldac, chan + CB_DDA_CALDAC_COURSE_GAIN,
			       (gain >> 8) & 0xff);
	cb_pcidda_ग_लिखो_caldac(dev, caldac, chan + CB_DDA_CALDAC_FINE_GAIN,
			       gain & 0xff);
पूर्ण

अटल पूर्णांक cb_pcidda_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcidda_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक channel = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक i;

	अगर (range != devpriv->ao_range[channel])
		cb_pcidda_calibrate(dev, channel, range);

	ctrl = CB_DDA_DA_CTRL_EN | CB_DDA_DA_CTRL_DAC(channel);

	चयन (range) अणु
	हाल 0:
	हाल 3:
		ctrl |= CB_DDA_DA_CTRL_RANGE10V;
		अवरोध;
	हाल 1:
	हाल 4:
		ctrl |= CB_DDA_DA_CTRL_RANGE5V;
		अवरोध;
	हाल 2:
	हाल 5:
		ctrl |= CB_DDA_DA_CTRL_RANGE2V5;
		अवरोध;
	पूर्ण

	अगर (range > 2)
		ctrl |= CB_DDA_DA_CTRL_UNIP;

	outw(ctrl, devpriv->daqio + CB_DDA_DA_CTRL_REG);

	क्रम (i = 0; i < insn->n; i++)
		outw(data[i], devpriv->daqio + CB_DDA_DA_DATA_REG(channel));

	वापस insn->n;
पूर्ण

अटल पूर्णांक cb_pcidda_स्वतः_attach(काष्ठा comedi_device *dev,
				 अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा cb_pcidda_board *board = शून्य;
	काष्ठा cb_pcidda_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(cb_pcidda_boards))
		board = &cb_pcidda_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 2);
	devpriv->daqio = pci_resource_start(pcidev, 3);

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* analog output subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = board->ao_chans;
	s->maxdata = (1 << board->ao_bits) - 1;
	s->range_table = &cb_pcidda_ranges;
	s->insn_ग_लिखो = cb_pcidda_ao_insn_ग_लिखो;

	/* two 8255 digital io subdevices */
	क्रम (i = 0; i < 2; i++) अणु
		s = &dev->subdevices[1 + i];
		ret = subdev_8255_init(dev, s, शून्य, i * I8255_SIZE);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Read the caldac eeprom data */
	क्रम (i = 0; i < EEPROM_SIZE; i++)
		devpriv->eeprom_data[i] = cb_pcidda_पढ़ो_eeprom(dev, i);

	/*  set calibrations dacs */
	क्रम (i = 0; i < board->ao_chans; i++)
		cb_pcidda_calibrate(dev, i, devpriv->ao_range[i]);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver cb_pcidda_driver = अणु
	.driver_name	= "cb_pcidda",
	.module		= THIS_MODULE,
	.स्वतः_attach	= cb_pcidda_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक cb_pcidda_pci_probe(काष्ठा pci_dev *dev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &cb_pcidda_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cb_pcidda_pci_table[] = अणु
	अणु PCI_VDEVICE(CB, 0x0020), BOARD_DDA02_12 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0021), BOARD_DDA04_12 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0022), BOARD_DDA08_12 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0023), BOARD_DDA02_16 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0024), BOARD_DDA04_16 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0025), BOARD_DDA08_16 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cb_pcidda_pci_table);

अटल काष्ठा pci_driver cb_pcidda_pci_driver = अणु
	.name		= "cb_pcidda",
	.id_table	= cb_pcidda_pci_table,
	.probe		= cb_pcidda_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(cb_pcidda_driver, cb_pcidda_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
