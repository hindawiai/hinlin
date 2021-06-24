<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ni_at_ao.c
 * Driver क्रम NI AT-AO-6/10 boards
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000,2002 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_at_ao
 * Description: National Instruments AT-AO-6/10
 * Devices: [National Instruments] AT-AO-6 (at-ao-6), AT-AO-10 (at-ao-10)
 * Status: should work
 * Author: David A. Schleef <ds@schleef.org>
 * Updated: Sun Dec 26 12:26:28 EST 2004
 *
 * Configuration options:
 *   [0] - I/O port base address
 *   [1] - IRQ (unused)
 *   [2] - DMA (unused)
 *   [3] - analog output range, set by jumpers on hardware
 *         0 क्रम -10 to 10V bipolar
 *         1 क्रम 0V to 10V unipolar
 */

#समावेश <linux/module.h>

#समावेश "../comedidev.h"

#समावेश "comedi_8254.h"

/*
 * Register map
 *
 * Register-level programming inक्रमmation can be found in NI
 * करोcument 320379.pdf.
 */
#घोषणा ATAO_DIO_REG		0x00
#घोषणा ATAO_CFG2_REG		0x02
#घोषणा ATAO_CFG2_CALLD_NOP	(0 << 14)
#घोषणा ATAO_CFG2_CALLD(x)	((((x) >> 3) + 1) << 14)
#घोषणा ATAO_CFG2_FFRTEN	BIT(13)
#घोषणा ATAO_CFG2_DACS(x)	(1 << (((x) / 2) + 8))
#घोषणा ATAO_CFG2_LDAC(x)	(1 << (((x) / 2) + 3))
#घोषणा ATAO_CFG2_PROMEN	BIT(2)
#घोषणा ATAO_CFG2_SCLK		BIT(1)
#घोषणा ATAO_CFG2_SDATA		BIT(0)
#घोषणा ATAO_CFG3_REG		0x04
#घोषणा ATAO_CFG3_DMAMODE	BIT(6)
#घोषणा ATAO_CFG3_CLKOUT	BIT(5)
#घोषणा ATAO_CFG3_RCLKEN	BIT(4)
#घोषणा ATAO_CFG3_DOUTEN2	BIT(3)
#घोषणा ATAO_CFG3_DOUTEN1	BIT(2)
#घोषणा ATAO_CFG3_EN2_5V	BIT(1)
#घोषणा ATAO_CFG3_SCANEN	BIT(0)
#घोषणा ATAO_82C53_BASE		0x06
#घोषणा ATAO_CFG1_REG		0x0a
#घोषणा ATAO_CFG1_EXTINT2EN	BIT(15)
#घोषणा ATAO_CFG1_EXTINT1EN	BIT(14)
#घोषणा ATAO_CFG1_CNTINT2EN	BIT(13)
#घोषणा ATAO_CFG1_CNTINT1EN	BIT(12)
#घोषणा ATAO_CFG1_TCINTEN	BIT(11)
#घोषणा ATAO_CFG1_CNT1SRC	BIT(10)
#घोषणा ATAO_CFG1_CNT2SRC	BIT(9)
#घोषणा ATAO_CFG1_FIFOEN	BIT(8)
#घोषणा ATAO_CFG1_GRP2WR	BIT(7)
#घोषणा ATAO_CFG1_EXTUPDEN	BIT(6)
#घोषणा ATAO_CFG1_DMARQ		BIT(5)
#घोषणा ATAO_CFG1_DMAEN		BIT(4)
#घोषणा ATAO_CFG1_CH(x)		(((x) & 0xf) << 0)
#घोषणा ATAO_STATUS_REG		0x0a
#घोषणा ATAO_STATUS_FH		BIT(6)
#घोषणा ATAO_STATUS_FE		BIT(5)
#घोषणा ATAO_STATUS_FF		BIT(4)
#घोषणा ATAO_STATUS_INT2	BIT(3)
#घोषणा ATAO_STATUS_INT1	BIT(2)
#घोषणा ATAO_STATUS_TCINT	BIT(1)
#घोषणा ATAO_STATUS_PROMOUT	BIT(0)
#घोषणा ATAO_FIFO_WRITE_REG	0x0c
#घोषणा ATAO_FIFO_CLEAR_REG	0x0c
#घोषणा ATAO_AO_REG(x)		(0x0c + ((x) * 2))

/* रेजिस्टरs with _2_ are accessed when GRP2WR is set in CFG1 */
#घोषणा ATAO_2_DMATCCLR_REG	0x00
#घोषणा ATAO_2_INT1CLR_REG	0x02
#घोषणा ATAO_2_INT2CLR_REG	0x04
#घोषणा ATAO_2_RTSISHFT_REG	0x06
#घोषणा ATAO_2_RTSISHFT_RSI	BIT(0)
#घोषणा ATAO_2_RTSISTRB_REG	0x07

काष्ठा atao_board अणु
	स्थिर अक्षर *name;
	पूर्णांक n_ao_chans;
पूर्ण;

अटल स्थिर काष्ठा atao_board atao_boards[] = अणु
	अणु
		.name		= "at-ao-6",
		.n_ao_chans	= 6,
	पूर्ण, अणु
		.name		= "at-ao-10",
		.n_ao_chans	= 10,
	पूर्ण,
पूर्ण;

काष्ठा atao_निजी अणु
	अचिन्हित लघु cfg1;
	अचिन्हित लघु cfg3;

	/* Used क्रम caldac पढ़ोback */
	अचिन्हित अक्षर caldac[21];
पूर्ण;

अटल व्योम atao_select_reg_group(काष्ठा comedi_device *dev, पूर्णांक group)
अणु
	काष्ठा atao_निजी *devpriv = dev->निजी;

	अगर (group)
		devpriv->cfg1 |= ATAO_CFG1_GRP2WR;
	अन्यथा
		devpriv->cfg1 &= ~ATAO_CFG1_GRP2WR;
	outw(devpriv->cfg1, dev->iobase + ATAO_CFG1_REG);
पूर्ण

अटल पूर्णांक atao_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	अगर (chan == 0)
		atao_select_reg_group(dev, 1);

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];

		/* the hardware expects two's complement values */
		outw(comedi_offset_munge(s, val),
		     dev->iobase + ATAO_AO_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	अगर (chan == 0)
		atao_select_reg_group(dev, 0);

	वापस insn->n;
पूर्ण

अटल पूर्णांक atao_dio_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + ATAO_DIO_REG);

	data[1] = inw(dev->iobase + ATAO_DIO_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक atao_dio_insn_config(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा atao_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 4)
		mask = 0x0f;
	अन्यथा
		mask = 0xf0;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	अगर (s->io_bits & 0x0f)
		devpriv->cfg3 |= ATAO_CFG3_DOUTEN1;
	अन्यथा
		devpriv->cfg3 &= ~ATAO_CFG3_DOUTEN1;
	अगर (s->io_bits & 0xf0)
		devpriv->cfg3 |= ATAO_CFG3_DOUTEN2;
	अन्यथा
		devpriv->cfg3 &= ~ATAO_CFG3_DOUTEN2;

	outw(devpriv->cfg3, dev->iobase + ATAO_CFG3_REG);

	वापस insn->n;
पूर्ण

/*
 * There are three DAC8800 TrimDACs on the board. These are 8-channel,
 * 8-bit DACs that are used to calibrate the Analog Output channels.
 * The factory शेष calibration values are stored in the EEPROM.
 * The TrimDACs, and EEPROM addresses, are mapped as:
 *
 *        Channel       EEPROM  Description
 *   -----------------  ------  -----------------------------------
 *    0 - DAC0 Chan 0    0x30   AO Channel 0 Offset
 *    1 - DAC0 Chan 1    0x31   AO Channel 0 Gain
 *    2 - DAC0 Chan 2    0x32   AO Channel 1 Offset
 *    3 - DAC0 Chan 3    0x33   AO Channel 1 Gain
 *    4 - DAC0 Chan 4    0x34   AO Channel 2 Offset
 *    5 - DAC0 Chan 5    0x35   AO Channel 2 Gain
 *    6 - DAC0 Chan 6    0x36   AO Channel 3 Offset
 *    7 - DAC0 Chan 7    0x37   AO Channel 3 Gain
 *    8 - DAC1 Chan 0    0x38   AO Channel 4 Offset
 *    9 - DAC1 Chan 1    0x39   AO Channel 4 Gain
 *   10 - DAC1 Chan 2    0x3a   AO Channel 5 Offset
 *   11 - DAC1 Chan 3    0x3b   AO Channel 5 Gain
 *   12 - DAC1 Chan 4    0x3c   2.5V Offset
 *   13 - DAC1 Chan 5    0x3d   AO Channel 6 Offset (at-ao-10 only)
 *   14 - DAC1 Chan 6    0x3e   AO Channel 6 Gain   (at-ao-10 only)
 *   15 - DAC1 Chan 7    0x3f   AO Channel 7 Offset (at-ao-10 only)
 *   16 - DAC2 Chan 0    0x40   AO Channel 7 Gain   (at-ao-10 only)
 *   17 - DAC2 Chan 1    0x41   AO Channel 8 Offset (at-ao-10 only)
 *   18 - DAC2 Chan 2    0x42   AO Channel 8 Gain   (at-ao-10 only)
 *   19 - DAC2 Chan 3    0x43   AO Channel 9 Offset (at-ao-10 only)
 *   20 - DAC2 Chan 4    0x44   AO Channel 9 Gain   (at-ao-10 only)
 *        DAC2 Chan 5    0x45   Reserved
 *        DAC2 Chan 6    0x46   Reserved
 *        DAC2 Chan 7    0x47   Reserved
 */
अटल पूर्णांक atao_calib_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	अगर (insn->n) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];
		अचिन्हित पूर्णांक bitstring = ((chan & 0x7) << 8) | val;
		अचिन्हित पूर्णांक bits;
		पूर्णांक bit;

		/* ग_लिखो the channel and last data value to the caldac */
		/* घड़ी the bitstring to the caldac; MSB -> LSB */
		क्रम (bit = BIT(10); bit; bit >>= 1) अणु
			bits = (bit & bitstring) ? ATAO_CFG2_SDATA : 0;

			outw(bits, dev->iobase + ATAO_CFG2_REG);
			outw(bits | ATAO_CFG2_SCLK,
			     dev->iobase + ATAO_CFG2_REG);
		पूर्ण

		/* strobe the caldac to load the value */
		outw(ATAO_CFG2_CALLD(chan), dev->iobase + ATAO_CFG2_REG);
		outw(ATAO_CFG2_CALLD_NOP, dev->iobase + ATAO_CFG2_REG);

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम atao_reset(काष्ठा comedi_device *dev)
अणु
	काष्ठा atao_निजी *devpriv = dev->निजी;

	/* This is the reset sequence described in the manual */

	devpriv->cfg1 = 0;
	outw(devpriv->cfg1, dev->iobase + ATAO_CFG1_REG);

	/* Put outमाला_दो of counter 1 and counter 2 in a high state */
	comedi_8254_set_mode(dev->pacer, 0, I8254_MODE4 | I8254_BINARY);
	comedi_8254_set_mode(dev->pacer, 1, I8254_MODE4 | I8254_BINARY);
	comedi_8254_ग_लिखो(dev->pacer, 0, 0x0003);

	outw(ATAO_CFG2_CALLD_NOP, dev->iobase + ATAO_CFG2_REG);

	devpriv->cfg3 = 0;
	outw(devpriv->cfg3, dev->iobase + ATAO_CFG3_REG);

	inw(dev->iobase + ATAO_FIFO_CLEAR_REG);

	atao_select_reg_group(dev, 1);
	outw(0, dev->iobase + ATAO_2_INT1CLR_REG);
	outw(0, dev->iobase + ATAO_2_INT2CLR_REG);
	outw(0, dev->iobase + ATAO_2_DMATCCLR_REG);
	atao_select_reg_group(dev, 0);
पूर्ण

अटल पूर्णांक atao_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा atao_board *board = dev->board_ptr;
	काष्ठा atao_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x20);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	dev->pacer = comedi_8254_init(dev->iobase + ATAO_82C53_BASE,
				      0, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= board->n_ao_chans;
	s->maxdata	= 0x0fff;
	s->range_table	= it->options[3] ? &range_unipolar10 : &range_bipolar10;
	s->insn_ग_लिखो	= atao_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital I/O subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= atao_dio_insn_bits;
	s->insn_config	= atao_dio_insn_config;

	/* caldac subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_CALIB;
	s->subdev_flags	= SDF_WRITABLE | SDF_INTERNAL;
	s->n_chan	= (board->n_ao_chans * 2) + 1;
	s->maxdata	= 0xff;
	s->insn_ग_लिखो	= atao_calib_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* EEPROM subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_UNUSED;

	atao_reset(dev);

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver ni_at_ao_driver = अणु
	.driver_name	= "ni_at_ao",
	.module		= THIS_MODULE,
	.attach		= atao_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &atao_boards[0].name,
	.offset		= माप(काष्ठा atao_board),
	.num_names	= ARRAY_SIZE(atao_boards),
पूर्ण;
module_comedi_driver(ni_at_ao_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for NI AT-AO-6/10 boards");
MODULE_LICENSE("GPL");
