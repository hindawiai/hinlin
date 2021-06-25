<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/me_daq.c
 * Hardware driver क्रम Meilhaus data acquisition cards:
 *   ME-2000i, ME-2600i, ME-3000vm1
 *
 * Copyright (C) 2002 Michael Hillmann <hillmann@syscongroup.de>
 */

/*
 * Driver: me_daq
 * Description: Meilhaus PCI data acquisition cards
 * Devices: [Meilhaus] ME-2600i (me-2600i), ME-2000i (me-2000i)
 * Author: Michael Hillmann <hillmann@syscongroup.de>
 * Status: experimental
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 *
 * Supports:
 *    Analog Input, Analog Output, Digital I/O
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>

#समावेश "../comedi_pci.h"

#समावेश "plx9052.h"

#घोषणा ME2600_FIRMWARE		"me2600_firmware.bin"

#घोषणा XILINX_DOWNLOAD_RESET	0x42	/* Xilinx रेजिस्टरs */

/*
 * PCI BAR2 Memory map (dev->mmio)
 */
#घोषणा ME_CTRL1_REG			0x00	/* R (ai start) | W */
#घोषणा   ME_CTRL1_INT_ENA		BIT(15)
#घोषणा   ME_CTRL1_COUNTER_B_IRQ	BIT(12)
#घोषणा   ME_CTRL1_COUNTER_A_IRQ	BIT(11)
#घोषणा   ME_CTRL1_CHANLIST_READY_IRQ	BIT(10)
#घोषणा   ME_CTRL1_EXT_IRQ		BIT(9)
#घोषणा   ME_CTRL1_ADFIFO_HALFFULL_IRQ	BIT(8)
#घोषणा   ME_CTRL1_SCAN_COUNT_ENA	BIT(5)
#घोषणा   ME_CTRL1_SIMULTANEOUS_ENA	BIT(4)
#घोषणा   ME_CTRL1_TRIGGER_FALLING_EDGE	BIT(3)
#घोषणा   ME_CTRL1_CONTINUOUS_MODE	BIT(2)
#घोषणा   ME_CTRL1_ADC_MODE(x)		(((x) & 0x3) << 0)
#घोषणा   ME_CTRL1_ADC_MODE_DISABLE	ME_CTRL1_ADC_MODE(0)
#घोषणा   ME_CTRL1_ADC_MODE_SOFT_TRIG	ME_CTRL1_ADC_MODE(1)
#घोषणा   ME_CTRL1_ADC_MODE_SCAN_TRIG	ME_CTRL1_ADC_MODE(2)
#घोषणा   ME_CTRL1_ADC_MODE_EXT_TRIG	ME_CTRL1_ADC_MODE(3)
#घोषणा   ME_CTRL1_ADC_MODE_MASK	ME_CTRL1_ADC_MODE(3)
#घोषणा ME_CTRL2_REG			0x02	/* R (dac update) | W */
#घोषणा   ME_CTRL2_ADFIFO_ENA		BIT(10)
#घोषणा   ME_CTRL2_CHANLIST_ENA		BIT(9)
#घोषणा   ME_CTRL2_PORT_B_ENA		BIT(7)
#घोषणा   ME_CTRL2_PORT_A_ENA		BIT(6)
#घोषणा   ME_CTRL2_COUNTER_B_ENA	BIT(4)
#घोषणा   ME_CTRL2_COUNTER_A_ENA	BIT(3)
#घोषणा   ME_CTRL2_DAC_ENA		BIT(1)
#घोषणा   ME_CTRL2_BUFFERED_DAC		BIT(0)
#घोषणा ME_STATUS_REG			0x04	/* R | W (clears पूर्णांकerrupts) */
#घोषणा   ME_STATUS_COUNTER_B_IRQ	BIT(12)
#घोषणा   ME_STATUS_COUNTER_A_IRQ	BIT(11)
#घोषणा   ME_STATUS_CHANLIST_READY_IRQ	BIT(10)
#घोषणा   ME_STATUS_EXT_IRQ		BIT(9)
#घोषणा   ME_STATUS_ADFIFO_HALFFULL_IRQ	BIT(8)
#घोषणा   ME_STATUS_ADFIFO_FULL		BIT(4)
#घोषणा   ME_STATUS_ADFIFO_HALFFULL	BIT(3)
#घोषणा   ME_STATUS_ADFIFO_EMPTY	BIT(2)
#घोषणा   ME_STATUS_CHANLIST_FULL	BIT(1)
#घोषणा   ME_STATUS_FST_ACTIVE		BIT(0)
#घोषणा ME_DIO_PORT_A_REG		0x06	/* R | W */
#घोषणा ME_DIO_PORT_B_REG		0x08	/* R | W */
#घोषणा ME_TIMER_DATA_REG(x)		(0x0a + ((x) * 2))	/* - | W */
#घोषणा ME_AI_FIFO_REG			0x10	/* R (fअगरo) | W (chanlist) */
#घोषणा   ME_AI_FIFO_CHANLIST_DIFF	BIT(7)
#घोषणा   ME_AI_FIFO_CHANLIST_UNIPOLAR	BIT(6)
#घोषणा   ME_AI_FIFO_CHANLIST_GAIN(x)	(((x) & 0x3) << 4)
#घोषणा   ME_AI_FIFO_CHANLIST_CHAN(x)	(((x) & 0xf) << 0)
#घोषणा ME_DAC_CTRL_REG			0x12	/* R (updates) | W */
#घोषणा   ME_DAC_CTRL_BIPOLAR(x)	BIT(7 - ((x) & 0x3))
#घोषणा   ME_DAC_CTRL_GAIN(x)		BIT(11 - ((x) & 0x3))
#घोषणा   ME_DAC_CTRL_MASK(x)		(ME_DAC_CTRL_BIPOLAR(x) |	\
					 ME_DAC_CTRL_GAIN(x))
#घोषणा ME_AO_DATA_REG(x)		(0x14 + ((x) * 2))	/* - | W */
#घोषणा ME_COUNTER_ENDDATA_REG(x)	(0x1c + ((x) * 2))	/* - | W */
#घोषणा ME_COUNTER_STARTDATA_REG(x)	(0x20 + ((x) * 2))	/* - | W */
#घोषणा ME_COUNTER_VALUE_REG(x)		(0x20 + ((x) * 2))	/* R | - */

अटल स्थिर काष्ठा comedi_lrange me_ai_range = अणु
	8, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange me_ao_range = अणु
	3, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

क्रमागत me_boardid अणु
	BOARD_ME2600,
	BOARD_ME2000,
पूर्ण;

काष्ठा me_board अणु
	स्थिर अक्षर *name;
	पूर्णांक needs_firmware;
	पूर्णांक has_ao;
पूर्ण;

अटल स्थिर काष्ठा me_board me_boards[] = अणु
	[BOARD_ME2600] = अणु
		.name		= "me-2600i",
		.needs_firmware	= 1,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_ME2000] = अणु
		.name		= "me-2000i",
	पूर्ण,
पूर्ण;

काष्ठा me_निजी_data अणु
	व्योम __iomem *plx_regbase;	/* PLX configuration base address */

	अचिन्हित लघु ctrl1;		/* Mirror of CONTROL_1 रेजिस्टर */
	अचिन्हित लघु ctrl2;		/* Mirror of CONTROL_2 रेजिस्टर */
	अचिन्हित लघु dac_ctrl;	/* Mirror of the DAC_CONTROL रेजिस्टर */
पूर्ण;

अटल अंतरभूत व्योम sleep(अचिन्हित पूर्णांक sec)
अणु
	schedule_समयout_पूर्णांकerruptible(sec * HZ);
पूर्ण

अटल पूर्णांक me_dio_insn_config(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा me_निजी_data *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 16)
		mask = 0x0000ffff;
	अन्यथा
		mask = 0xffff0000;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	अगर (s->io_bits & 0x0000ffff)
		devpriv->ctrl2 |= ME_CTRL2_PORT_A_ENA;
	अन्यथा
		devpriv->ctrl2 &= ~ME_CTRL2_PORT_A_ENA;
	अगर (s->io_bits & 0xffff0000)
		devpriv->ctrl2 |= ME_CTRL2_PORT_B_ENA;
	अन्यथा
		devpriv->ctrl2 &= ~ME_CTRL2_PORT_B_ENA;

	ग_लिखोw(devpriv->ctrl2, dev->mmio + ME_CTRL2_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक me_dio_insn_bits(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn,
			    अचिन्हित पूर्णांक *data)
अणु
	व्योम __iomem *mmio_porta = dev->mmio + ME_DIO_PORT_A_REG;
	व्योम __iomem *mmio_portb = dev->mmio + ME_DIO_PORT_B_REG;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (mask & 0x0000ffff)
			ग_लिखोw((s->state & 0xffff), mmio_porta);
		अगर (mask & 0xffff0000)
			ग_लिखोw(((s->state >> 16) & 0xffff), mmio_portb);
	पूर्ण

	अगर (s->io_bits & 0x0000ffff)
		val = s->state & 0xffff;
	अन्यथा
		val = पढ़ोw(mmio_porta);

	अगर (s->io_bits & 0xffff0000)
		val |= (s->state & 0xffff0000);
	अन्यथा
		val |= (पढ़ोw(mmio_portb) << 16);

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक me_ai_eoc(काष्ठा comedi_device *dev,
		     काष्ठा comedi_subdevice *s,
		     काष्ठा comedi_insn *insn,
		     अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = पढ़ोw(dev->mmio + ME_STATUS_REG);
	अगर ((status & ME_STATUS_ADFIFO_EMPTY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक me_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा me_निजी_data *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/*
	 * For dअगरferential operation, there are only 8 input channels
	 * and only bipolar ranges are available.
	 */
	अगर (aref & AREF_DIFF) अणु
		अगर (chan > 7 || comedi_range_is_unipolar(s, range))
			वापस -EINVAL;
	पूर्ण

	/* clear chanlist and ad fअगरo */
	devpriv->ctrl2 &= ~(ME_CTRL2_ADFIFO_ENA | ME_CTRL2_CHANLIST_ENA);
	ग_लिखोw(devpriv->ctrl2, dev->mmio + ME_CTRL2_REG);

	ग_लिखोw(0x00, dev->mmio + ME_STATUS_REG);	/* clear पूर्णांकerrupts */

	/* enable the chanlist and ADC fअगरo */
	devpriv->ctrl2 |= (ME_CTRL2_ADFIFO_ENA | ME_CTRL2_CHANLIST_ENA);
	ग_लिखोw(devpriv->ctrl2, dev->mmio + ME_CTRL2_REG);

	/* ग_लिखो to channel list fअगरo */
	val = ME_AI_FIFO_CHANLIST_CHAN(chan) | ME_AI_FIFO_CHANLIST_GAIN(range);
	अगर (comedi_range_is_unipolar(s, range))
		val |= ME_AI_FIFO_CHANLIST_UNIPOLAR;
	अगर (aref & AREF_DIFF)
		val |= ME_AI_FIFO_CHANLIST_DIFF;
	ग_लिखोw(val, dev->mmio + ME_AI_FIFO_REG);

	/* set ADC mode to software trigger */
	devpriv->ctrl1 |= ME_CTRL1_ADC_MODE_SOFT_TRIG;
	ग_लिखोw(devpriv->ctrl1, dev->mmio + ME_CTRL1_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		/* start ai conversion */
		पढ़ोw(dev->mmio + ME_CTRL1_REG);

		/* रुको क्रम ADC fअगरo not empty flag */
		ret = comedi_समयout(dev, s, insn, me_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		/* get value from ADC fअगरo */
		val = पढ़ोw(dev->mmio + ME_AI_FIFO_REG) & s->maxdata;

		/* munge 2's complement value to offset binary */
		data[i] = comedi_offset_munge(s, val);
	पूर्ण

	/* stop any running conversion */
	devpriv->ctrl1 &= ~ME_CTRL1_ADC_MODE_MASK;
	ग_लिखोw(devpriv->ctrl1, dev->mmio + ME_CTRL1_REG);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक me_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn,
			    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा me_निजी_data *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	/* Enable all DAC */
	devpriv->ctrl2 |= ME_CTRL2_DAC_ENA;
	ग_लिखोw(devpriv->ctrl2, dev->mmio + ME_CTRL2_REG);

	/* and set DAC to "buffered" mode */
	devpriv->ctrl2 |= ME_CTRL2_BUFFERED_DAC;
	ग_लिखोw(devpriv->ctrl2, dev->mmio + ME_CTRL2_REG);

	/* Set dac-control रेजिस्टर */
	devpriv->dac_ctrl &= ~ME_DAC_CTRL_MASK(chan);
	अगर (range == 0)
		devpriv->dac_ctrl |= ME_DAC_CTRL_GAIN(chan);
	अगर (comedi_range_is_bipolar(s, range))
		devpriv->dac_ctrl |= ME_DAC_CTRL_BIPOLAR(chan);
	ग_लिखोw(devpriv->dac_ctrl, dev->mmio + ME_DAC_CTRL_REG);

	/* Update dac-control रेजिस्टर */
	पढ़ोw(dev->mmio + ME_DAC_CTRL_REG);

	/* Set data रेजिस्टर */
	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];

		ग_लिखोw(val, dev->mmio + ME_AO_DATA_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	/* Update dac with data रेजिस्टरs */
	पढ़ोw(dev->mmio + ME_CTRL2_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक me2600_xilinx_करोwnload(काष्ठा comedi_device *dev,
				  स्थिर u8 *data, माप_प्रकार size,
				  अचिन्हित दीर्घ context)
अणु
	काष्ठा me_निजी_data *devpriv = dev->निजी;
	अचिन्हित पूर्णांक value;
	अचिन्हित पूर्णांक file_length;
	अचिन्हित पूर्णांक i;

	/* disable irq's on PLX */
	ग_लिखोl(0x00, devpriv->plx_regbase + PLX9052_INTCSR);

	/* First, make a dummy पढ़ो to reset xilinx */
	value = पढ़ोw(dev->mmio + XILINX_DOWNLOAD_RESET);

	/* Wait until reset is over */
	sleep(1);

	/* Write a dummy value to Xilinx */
	ग_लिखोb(0x00, dev->mmio + 0x0);
	sleep(1);

	/*
	 * Format of the firmware
	 * Build दीर्घs from the byte-wise coded header
	 * Byte 1-3:   length of the array
	 * Byte 4-7:   version
	 * Byte 8-11:  date
	 * Byte 12-15: reserved
	 */
	अगर (size < 16)
		वापस -EINVAL;

	file_length = (((अचिन्हित पूर्णांक)data[0] & 0xff) << 24) +
	    (((अचिन्हित पूर्णांक)data[1] & 0xff) << 16) +
	    (((अचिन्हित पूर्णांक)data[2] & 0xff) << 8) +
	    ((अचिन्हित पूर्णांक)data[3] & 0xff);

	/*
	 * Loop क्रम writing firmware byte by byte to xilinx
	 * Firmware data start at offset 16
	 */
	क्रम (i = 0; i < file_length; i++)
		ग_लिखोb((data[16 + i] & 0xff), dev->mmio + 0x0);

	/* Write 5 dummy values to xilinx */
	क्रम (i = 0; i < 5; i++)
		ग_लिखोb(0x00, dev->mmio + 0x0);

	/* Test अगर there was an error during करोwnload -> INTB was thrown */
	value = पढ़ोl(devpriv->plx_regbase + PLX9052_INTCSR);
	अगर (value & PLX9052_INTCSR_LI2STAT) अणु
		/* Disable पूर्णांकerrupt */
		ग_लिखोl(0x00, devpriv->plx_regbase + PLX9052_INTCSR);
		dev_err(dev->class_dev, "Xilinx download failed\n");
		वापस -EIO;
	पूर्ण

	/* Wait until the Xilinx is पढ़ोy क्रम real work */
	sleep(1);

	/* Enable PLX-Interrupts */
	ग_लिखोl(PLX9052_INTCSR_LI1ENAB |
	       PLX9052_INTCSR_LI1POL |
	       PLX9052_INTCSR_PCIENAB,
	       devpriv->plx_regbase + PLX9052_INTCSR);

	वापस 0;
पूर्ण

अटल पूर्णांक me_reset(काष्ठा comedi_device *dev)
अणु
	काष्ठा me_निजी_data *devpriv = dev->निजी;

	/* Reset board */
	ग_लिखोw(0x00, dev->mmio + ME_CTRL1_REG);
	ग_लिखोw(0x00, dev->mmio + ME_CTRL2_REG);
	ग_लिखोw(0x00, dev->mmio + ME_STATUS_REG);	/* clear पूर्णांकerrupts */
	ग_लिखोw(0x00, dev->mmio + ME_DAC_CTRL_REG);

	/* Save values in the board context */
	devpriv->dac_ctrl = 0;
	devpriv->ctrl1 = 0;
	devpriv->ctrl2 = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक me_स्वतः_attach(काष्ठा comedi_device *dev,
			  अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा me_board *board = शून्य;
	काष्ठा me_निजी_data *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(me_boards))
		board = &me_boards[context];
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

	devpriv->plx_regbase = pci_ioremap_bar(pcidev, 0);
	अगर (!devpriv->plx_regbase)
		वापस -ENOMEM;

	dev->mmio = pci_ioremap_bar(pcidev, 2);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	/* Download firmware and reset card */
	अगर (board->needs_firmware) अणु
		ret = comedi_load_firmware(dev, &comedi_to_pci_dev(dev)->dev,
					   ME2600_FIRMWARE,
					   me2600_xilinx_करोwnload, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	me_reset(dev);

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_COMMON | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= 0x0fff;
	s->len_chanlist	= 16;
	s->range_table	= &me_ai_range;
	s->insn_पढ़ो	= me_ai_insn_पढ़ो;

	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_COMMON;
		s->n_chan	= 4;
		s->maxdata	= 0x0fff;
		s->len_chanlist	= 4;
		s->range_table	= &me_ao_range;
		s->insn_ग_लिखो	= me_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->len_chanlist	= 32;
	s->range_table	= &range_digital;
	s->insn_bits	= me_dio_insn_bits;
	s->insn_config	= me_dio_insn_config;

	वापस 0;
पूर्ण

अटल व्योम me_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा me_निजी_data *devpriv = dev->निजी;

	अगर (devpriv) अणु
		अगर (dev->mmio)
			me_reset(dev);
		अगर (devpriv->plx_regbase)
			iounmap(devpriv->plx_regbase);
	पूर्ण
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver me_daq_driver = अणु
	.driver_name	= "me_daq",
	.module		= THIS_MODULE,
	.स्वतः_attach	= me_स्वतः_attach,
	.detach		= me_detach,
पूर्ण;

अटल पूर्णांक me_daq_pci_probe(काष्ठा pci_dev *dev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &me_daq_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id me_daq_pci_table[] = अणु
	अणु PCI_VDEVICE(MEILHAUS, 0x2600), BOARD_ME2600 पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x2000), BOARD_ME2000 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, me_daq_pci_table);

अटल काष्ठा pci_driver me_daq_pci_driver = अणु
	.name		= "me_daq",
	.id_table	= me_daq_pci_table,
	.probe		= me_daq_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(me_daq_driver, me_daq_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(ME2600_FIRMWARE);
