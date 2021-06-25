<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * mpc624.c
 * Hardware driver क्रम a Micro/sys inc. MPC-624 PC/104 board
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: mpc624
 * Description: Micro/sys MPC-624 PC/104 board
 * Devices: [Micro/sys] MPC-624 (mpc624)
 * Author: Stanislaw Raczynski <sraczynski@op.pl>
 * Updated: Thu, 15 Sep 2005 12:01:18 +0200
 * Status: working
 *
 * The Micro/sys MPC-624 board is based on the LTC2440 24-bit sigma-delta
 * ADC chip.
 *
 * Subdevices supported by the driver:
 * - Analog In:   supported
 * - Digital I/O: not supported
 * - LEDs:        not supported
 * - EEPROM:      not supported
 *
 * Configuration Options:
 *   [0] - I/O base address
 *   [1] - conversion rate
 *	   Conversion rate   RMS noise	Effective Number Of Bits
 *	   0	3.52kHz		23uV		17
 *	   1	1.76kHz		3.5uV		20
 *	   2	880Hz		2uV		21.3
 *	   3	440Hz		1.4uV		21.8
 *	   4	220Hz		1uV		22.4
 *	   5	110Hz		750uV		22.9
 *	   6	55Hz		510nV		23.4
 *	   7	27.5Hz		375nV		24
 *	   8	13.75Hz		250nV		24.4
 *	   9	6.875Hz		200nV		24.6
 *   [2] - voltage range
 *	   0	-1.01V .. +1.01V
 *	   1	-10.1V .. +10.1V
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश <linux/delay.h>

/* Offsets of dअगरferent ports */
#घोषणा MPC624_MASTER_CONTROL	0 /* not used */
#घोषणा MPC624_GNMUXCH		1 /* Gain, Mux, Channel of ADC */
#घोषणा MPC624_ADC		2 /* पढ़ो/ग_लिखो to/from ADC */
#घोषणा MPC624_EE		3 /* पढ़ो/ग_लिखो to/from serial EEPROM via I2C */
#घोषणा MPC624_LEDS		4 /* ग_लिखो to LEDs */
#घोषणा MPC624_DIO		5 /* पढ़ो/ग_लिखो to/from digital I/O ports */
#घोषणा MPC624_IRQ_MASK		6 /* IRQ masking enable/disable */

/* Register bits' names */
#घोषणा MPC624_ADBUSY		BIT(5)
#घोषणा MPC624_ADSDO		BIT(4)
#घोषणा MPC624_ADFO		BIT(3)
#घोषणा MPC624_ADCS		BIT(2)
#घोषणा MPC624_ADSCK		BIT(1)
#घोषणा MPC624_ADSDI		BIT(0)

/* 32-bit output value bits' names */
#घोषणा MPC624_EOC_BIT		BIT(31)
#घोषणा MPC624_DMY_BIT		BIT(30)
#घोषणा MPC624_SGN_BIT		BIT(29)

/* SDI Speed/Resolution Programming bits */
#घोषणा MPC624_OSR(x)		(((x) & 0x1f) << 27)
#घोषणा MPC624_SPEED_3_52_KHZ	MPC624_OSR(0x11)
#घोषणा MPC624_SPEED_1_76_KHZ	MPC624_OSR(0x12)
#घोषणा MPC624_SPEED_880_HZ	MPC624_OSR(0x13)
#घोषणा MPC624_SPEED_440_HZ	MPC624_OSR(0x14)
#घोषणा MPC624_SPEED_220_HZ	MPC624_OSR(0x15)
#घोषणा MPC624_SPEED_110_HZ	MPC624_OSR(0x16)
#घोषणा MPC624_SPEED_55_HZ	MPC624_OSR(0x17)
#घोषणा MPC624_SPEED_27_5_HZ	MPC624_OSR(0x18)
#घोषणा MPC624_SPEED_13_75_HZ	MPC624_OSR(0x19)
#घोषणा MPC624_SPEED_6_875_HZ	MPC624_OSR(0x1f)

काष्ठा mpc624_निजी अणु
	अचिन्हित पूर्णांक ai_speed;
पूर्ण;

/* -------------------------------------------------------------------------- */
अटल स्थिर काष्ठा comedi_lrange range_mpc624_bipolar1 = अणु
	1,
	अणु
/* BIP_RANGE(1.01)  this is correct, */
	 /*  but my MPC-624 actually seems to have a range of 2.02 */
	 BIP_RANGE(2.02)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_mpc624_bipolar10 = अणु
	1,
	अणु
/* BIP_RANGE(10.1)   this is correct, */
	 /*  but my MPC-624 actually seems to have a range of 20.2 */
	 BIP_RANGE(20.2)
	पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक mpc624_ai_get_sample(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s)
अणु
	काष्ठा mpc624_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक data_out = devpriv->ai_speed;
	अचिन्हित पूर्णांक data_in = 0;
	अचिन्हित पूर्णांक bit;
	पूर्णांक i;

	/* Start पढ़ोing data */
	udelay(1);
	क्रम (i = 0; i < 32; i++) अणु
		/* Set the घड़ी low */
		outb(0, dev->iobase + MPC624_ADC);
		udelay(1);

		/* Set the ADSDI line क्रम the next bit (send to MPC624) */
		bit = (data_out & BIT(31)) ? MPC624_ADSDI : 0;
		outb(bit, dev->iobase + MPC624_ADC);
		udelay(1);

		/* Set the घड़ी high */
		outb(MPC624_ADSCK | bit, dev->iobase + MPC624_ADC);
		udelay(1);

		/* Read ADSDO on high घड़ी (receive from MPC624) */
		data_in <<= 1;
		data_in |= (inb(dev->iobase + MPC624_ADC) & MPC624_ADSDO) >> 4;
		udelay(1);

		data_out <<= 1;
	पूर्ण

	/*
	 * Received 32-bit दीर्घ value consist of:
	 *	31: EOC - (End Of Transmission) bit - should be 0
	 *	30: DMY - (Dummy) bit - should be 0
	 *	29: SIG - (Sign) bit - 1 अगर positive, 0 अगर negative
	 *	28: MSB - (Most Signअगरicant Bit) - the first bit of the
	 *					   conversion result
	 *	....
	 *	05: LSB - (Least Signअगरicant Bit)- the last bit of the
	 *					   conversion result
	 *	04-00: sub-LSB - sub-LSBs are basically noise, but when
	 *			 averaged properly, they can increase
	 *			 conversion precision up to 29 bits;
	 *			 they can be discarded without loss of
	 *			 resolution.
	 */
	अगर (data_in & MPC624_EOC_BIT)
		dev_dbg(dev->class_dev, "EOC bit is set!");
	अगर (data_in & MPC624_DMY_BIT)
		dev_dbg(dev->class_dev, "DMY bit is set!");

	अगर (data_in & MPC624_SGN_BIT) अणु
		/*
		 * Voltage is positive
		 *
		 * comedi operates on अचिन्हित numbers, so mask off EOC
		 * and DMY and करोn't clear the SGN bit
		 */
		data_in &= 0x3fffffff;
	पूर्ण अन्यथा अणु
		/*
		 * The voltage is negative
		 *
		 * data_in contains a number in 30-bit two's complement
		 * code and we must deal with it
		 */
		data_in |= MPC624_SGN_BIT;
		data_in = ~data_in;
		data_in += 1;
		/* clear EOC and DMY bits */
		data_in &= ~(MPC624_EOC_BIT | MPC624_DMY_BIT);
		data_in = 0x20000000 - data_in;
	पूर्ण
	वापस data_in;
पूर्ण

अटल पूर्णांक mpc624_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित अक्षर status;

	status = inb(dev->iobase + MPC624_ADC);
	अगर ((status & MPC624_ADBUSY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक mpc624_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 *  WARNING:
	 *  We always ग_लिखो 0 to GNSWA bit, so the channel range is +-/10.1Vdc
	 */
	outb(insn->chanspec, dev->iobase + MPC624_GNMUXCH);

	क्रम (i = 0; i < insn->n; i++) अणु
		/*  Trigger the conversion */
		outb(MPC624_ADSCK, dev->iobase + MPC624_ADC);
		udelay(1);
		outb(MPC624_ADCS | MPC624_ADSCK, dev->iobase + MPC624_ADC);
		udelay(1);
		outb(0, dev->iobase + MPC624_ADC);
		udelay(1);

		/*  Wait क्रम the conversion to end */
		ret = comedi_समयout(dev, s, insn, mpc624_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		data[i] = mpc624_ai_get_sample(dev, s);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक mpc624_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा mpc624_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	चयन (it->options[1]) अणु
	हाल 0:
		devpriv->ai_speed = MPC624_SPEED_3_52_KHZ;
		अवरोध;
	हाल 1:
		devpriv->ai_speed = MPC624_SPEED_1_76_KHZ;
		अवरोध;
	हाल 2:
		devpriv->ai_speed = MPC624_SPEED_880_HZ;
		अवरोध;
	हाल 3:
		devpriv->ai_speed = MPC624_SPEED_440_HZ;
		अवरोध;
	हाल 4:
		devpriv->ai_speed = MPC624_SPEED_220_HZ;
		अवरोध;
	हाल 5:
		devpriv->ai_speed = MPC624_SPEED_110_HZ;
		अवरोध;
	हाल 6:
		devpriv->ai_speed = MPC624_SPEED_55_HZ;
		अवरोध;
	हाल 7:
		devpriv->ai_speed = MPC624_SPEED_27_5_HZ;
		अवरोध;
	हाल 8:
		devpriv->ai_speed = MPC624_SPEED_13_75_HZ;
		अवरोध;
	हाल 9:
		devpriv->ai_speed = MPC624_SPEED_6_875_HZ;
		अवरोध;
	शेष:
		devpriv->ai_speed = MPC624_SPEED_3_52_KHZ;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_DIFF;
	s->n_chan	= 4;
	s->maxdata	= 0x3fffffff;
	s->range_table	= (it->options[1] == 0) ? &range_mpc624_bipolar1
						: &range_mpc624_bipolar10;
	s->insn_पढ़ो	= mpc624_ai_insn_पढ़ो;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver mpc624_driver = अणु
	.driver_name	= "mpc624",
	.module		= THIS_MODULE,
	.attach		= mpc624_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(mpc624_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Micro/sys MPC-624 PC/104 board");
MODULE_LICENSE("GPL");
