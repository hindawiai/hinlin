<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * s526.c
 * Sensoray s526 Comedi driver
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: s526
 * Description: Sensoray 526 driver
 * Devices: [Sensoray] 526 (s526)
 * Author: Richie
 *	   Everett Wang <everett.wang@everteq.com>
 * Updated: Thu, 14 Sep. 2006
 * Status: experimental
 *
 * Encoder works
 * Analog input works
 * Analog output works
 * PWM output works
 * Commands are not supported yet.
 *
 * Configuration Options:
 *   [0] - I/O port base address
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

/*
 * Register I/O map
 */
#घोषणा S526_TIMER_REG		0x00
#घोषणा S526_TIMER_LOAD(x)	(((x) & 0xff) << 8)
#घोषणा S526_TIMER_MODE		((x) << 1)
#घोषणा S526_TIMER_MANUAL	S526_TIMER_MODE(0)
#घोषणा S526_TIMER_AUTO		S526_TIMER_MODE(1)
#घोषणा S526_TIMER_RESTART	BIT(0)
#घोषणा S526_WDOG_REG		0x02
#घोषणा S526_WDOG_INVERTED	BIT(4)
#घोषणा S526_WDOG_ENA		BIT(3)
#घोषणा S526_WDOG_INTERVAL(x)	(((x) & 0x7) << 0)
#घोषणा S526_AO_CTRL_REG	0x04
#घोषणा S526_AO_CTRL_RESET	BIT(3)
#घोषणा S526_AO_CTRL_CHAN(x)	(((x) & 0x3) << 1)
#घोषणा S526_AO_CTRL_START	BIT(0)
#घोषणा S526_AI_CTRL_REG	0x06
#घोषणा S526_AI_CTRL_DELAY	BIT(15)
#घोषणा S526_AI_CTRL_CONV(x)	(1 << (5 + ((x) & 0x9)))
#घोषणा S526_AI_CTRL_READ(x)	(((x) & 0xf) << 1)
#घोषणा S526_AI_CTRL_START	BIT(0)
#घोषणा S526_AO_REG		0x08
#घोषणा S526_AI_REG		0x08
#घोषणा S526_DIO_CTRL_REG	0x0a
#घोषणा S526_DIO_CTRL_DIO3_NEG	BIT(15)	/* irq on DIO3 neg/pos edge */
#घोषणा S526_DIO_CTRL_DIO2_NEG	BIT(14)	/* irq on DIO2 neg/pos edge */
#घोषणा S526_DIO_CTRL_DIO1_NEG	BIT(13)	/* irq on DIO1 neg/pos edge */
#घोषणा S526_DIO_CTRL_DIO0_NEG	BIT(12)	/* irq on DIO0 neg/pos edge */
#घोषणा S526_DIO_CTRL_GRP2_OUT	BIT(11)
#घोषणा S526_DIO_CTRL_GRP1_OUT	BIT(10)
#घोषणा S526_DIO_CTRL_GRP2_NEG	BIT(8)	/* irq on DIO[4-7] neg/pos edge */
#घोषणा S526_INT_ENA_REG	0x0c
#घोषणा S526_INT_STATUS_REG	0x0e
#घोषणा S526_INT_DIO(x)		BIT(8 + ((x) & 0x7))
#घोषणा S526_INT_EEPROM		BIT(7)	/* status only */
#घोषणा S526_INT_CNTR(x)	BIT(3 + (3 - ((x) & 0x3)))
#घोषणा S526_INT_AI		BIT(2)
#घोषणा S526_INT_AO		BIT(1)
#घोषणा S526_INT_TIMER		BIT(0)
#घोषणा S526_MISC_REG		0x10
#घोषणा S526_MISC_LED_OFF	BIT(0)
#घोषणा S526_GPCT_LSB_REG(x)	(0x12 + ((x) * 8))
#घोषणा S526_GPCT_MSB_REG(x)	(0x14 + ((x) * 8))
#घोषणा S526_GPCT_MODE_REG(x)	(0x16 + ((x) * 8))
#घोषणा S526_GPCT_MODE_COUT_SRC(x)	((x) << 0)
#घोषणा S526_GPCT_MODE_COUT_SRC_MASK	S526_GPCT_MODE_COUT_SRC(0x1)
#घोषणा S526_GPCT_MODE_COUT_SRC_RCAP	S526_GPCT_MODE_COUT_SRC(0)
#घोषणा S526_GPCT_MODE_COUT_SRC_RTGL	S526_GPCT_MODE_COUT_SRC(1)
#घोषणा S526_GPCT_MODE_COUT_POL(x)	((x) << 1)
#घोषणा S526_GPCT_MODE_COUT_POL_MASK	S526_GPCT_MODE_COUT_POL(0x1)
#घोषणा S526_GPCT_MODE_COUT_POL_NORM	S526_GPCT_MODE_COUT_POL(0)
#घोषणा S526_GPCT_MODE_COUT_POL_INV	S526_GPCT_MODE_COUT_POL(1)
#घोषणा S526_GPCT_MODE_AUTOLOAD(x)	((x) << 2)
#घोषणा S526_GPCT_MODE_AUTOLOAD_MASK	S526_GPCT_MODE_AUTOLOAD(0x7)
#घोषणा S526_GPCT_MODE_AUTOLOAD_NONE	S526_GPCT_MODE_AUTOLOAD(0)
/* these 3 bits can be OR'ed */
#घोषणा S526_GPCT_MODE_AUTOLOAD_RO	S526_GPCT_MODE_AUTOLOAD(0x1)
#घोषणा S526_GPCT_MODE_AUTOLOAD_IXFALL	S526_GPCT_MODE_AUTOLOAD(0x2)
#घोषणा S526_GPCT_MODE_AUTOLOAD_IXRISE	S526_GPCT_MODE_AUTOLOAD(0x4)
#घोषणा S526_GPCT_MODE_HWCTEN_SRC(x)	((x) << 5)
#घोषणा S526_GPCT_MODE_HWCTEN_SRC_MASK	S526_GPCT_MODE_HWCTEN_SRC(0x3)
#घोषणा S526_GPCT_MODE_HWCTEN_SRC_CEN	S526_GPCT_MODE_HWCTEN_SRC(0)
#घोषणा S526_GPCT_MODE_HWCTEN_SRC_IX	S526_GPCT_MODE_HWCTEN_SRC(1)
#घोषणा S526_GPCT_MODE_HWCTEN_SRC_IXRF	S526_GPCT_MODE_HWCTEN_SRC(2)
#घोषणा S526_GPCT_MODE_HWCTEN_SRC_NRCAP	S526_GPCT_MODE_HWCTEN_SRC(3)
#घोषणा S526_GPCT_MODE_CTEN_CTRL(x)	((x) << 7)
#घोषणा S526_GPCT_MODE_CTEN_CTRL_MASK	S526_GPCT_MODE_CTEN_CTRL(0x3)
#घोषणा S526_GPCT_MODE_CTEN_CTRL_DIS	S526_GPCT_MODE_CTEN_CTRL(0)
#घोषणा S526_GPCT_MODE_CTEN_CTRL_ENA	S526_GPCT_MODE_CTEN_CTRL(1)
#घोषणा S526_GPCT_MODE_CTEN_CTRL_HW	S526_GPCT_MODE_CTEN_CTRL(2)
#घोषणा S526_GPCT_MODE_CTEN_CTRL_INVHW	S526_GPCT_MODE_CTEN_CTRL(3)
#घोषणा S526_GPCT_MODE_CLK_SRC(x)	((x) << 9)
#घोषणा S526_GPCT_MODE_CLK_SRC_MASK	S526_GPCT_MODE_CLK_SRC(0x3)
/* अगर count direction control set to quadrature */
#घोषणा S526_GPCT_MODE_CLK_SRC_QUADX1	S526_GPCT_MODE_CLK_SRC(0)
#घोषणा S526_GPCT_MODE_CLK_SRC_QUADX2	S526_GPCT_MODE_CLK_SRC(1)
#घोषणा S526_GPCT_MODE_CLK_SRC_QUADX4	S526_GPCT_MODE_CLK_SRC(2)
#घोषणा S526_GPCT_MODE_CLK_SRC_QUADX4_	S526_GPCT_MODE_CLK_SRC(3)
/* अगर count direction control set to software control */
#घोषणा S526_GPCT_MODE_CLK_SRC_ARISE	S526_GPCT_MODE_CLK_SRC(0)
#घोषणा S526_GPCT_MODE_CLK_SRC_AFALL	S526_GPCT_MODE_CLK_SRC(1)
#घोषणा S526_GPCT_MODE_CLK_SRC_INT	S526_GPCT_MODE_CLK_SRC(2)
#घोषणा S526_GPCT_MODE_CLK_SRC_INTHALF	S526_GPCT_MODE_CLK_SRC(3)
#घोषणा S526_GPCT_MODE_CT_सूची(x)	((x) << 11)
#घोषणा S526_GPCT_MODE_CT_सूची_MASK	S526_GPCT_MODE_CT_सूची(0x1)
/* अगर count direction control set to software control */
#घोषणा S526_GPCT_MODE_CT_सूची_UP	S526_GPCT_MODE_CT_सूची(0)
#घोषणा S526_GPCT_MODE_CT_सूची_DOWN	S526_GPCT_MODE_CT_सूची(1)
#घोषणा S526_GPCT_MODE_CTसूची_CTRL(x)	((x) << 12)
#घोषणा S526_GPCT_MODE_CTसूची_CTRL_MASK	S526_GPCT_MODE_CTसूची_CTRL(0x1)
#घोषणा S526_GPCT_MODE_CTसूची_CTRL_QUAD	S526_GPCT_MODE_CTसूची_CTRL(0)
#घोषणा S526_GPCT_MODE_CTसूची_CTRL_SOFT	S526_GPCT_MODE_CTसूची_CTRL(1)
#घोषणा S526_GPCT_MODE_LATCH_CTRL(x)	((x) << 13)
#घोषणा S526_GPCT_MODE_LATCH_CTRL_MASK	S526_GPCT_MODE_LATCH_CTRL(0x1)
#घोषणा S526_GPCT_MODE_LATCH_CTRL_READ	S526_GPCT_MODE_LATCH_CTRL(0)
#घोषणा S526_GPCT_MODE_LATCH_CTRL_EVENT	S526_GPCT_MODE_LATCH_CTRL(1)
#घोषणा S526_GPCT_MODE_PR_SELECT(x)	((x) << 14)
#घोषणा S526_GPCT_MODE_PR_SELECT_MASK	S526_GPCT_MODE_PR_SELECT(0x1)
#घोषणा S526_GPCT_MODE_PR_SELECT_PR0	S526_GPCT_MODE_PR_SELECT(0)
#घोषणा S526_GPCT_MODE_PR_SELECT_PR1	S526_GPCT_MODE_PR_SELECT(1)
/* Control/Status - R = पढ़ोable, W = ग_लिखोable, C = ग_लिखो 1 to clear */
#घोषणा S526_GPCT_CTRL_REG(x)	(0x18 + ((x) * 8))
#घोषणा S526_GPCT_CTRL_EV_STATUS(x)	((x) << 0)		/* RC */
#घोषणा S526_GPCT_CTRL_EV_STATUS_MASK	S526_GPCT_EV_STATUS(0xf)
#घोषणा S526_GPCT_CTRL_EV_STATUS_NONE	S526_GPCT_EV_STATUS(0)
/* these 4 bits can be OR'ed */
#घोषणा S526_GPCT_CTRL_EV_STATUS_ECAP	S526_GPCT_EV_STATUS(0x1)
#घोषणा S526_GPCT_CTRL_EV_STATUS_ICAPN	S526_GPCT_EV_STATUS(0x2)
#घोषणा S526_GPCT_CTRL_EV_STATUS_ICAPP	S526_GPCT_EV_STATUS(0x4)
#घोषणा S526_GPCT_CTRL_EV_STATUS_RCAP	S526_GPCT_EV_STATUS(0x8)
#घोषणा S526_GPCT_CTRL_COUT_STATUS	BIT(4)			/* R */
#घोषणा S526_GPCT_CTRL_INDEX_STATUS	BIT(5)			/* R */
#घोषणा S525_GPCT_CTRL_INTEN(x)		((x) << 6)		/* W */
#घोषणा S525_GPCT_CTRL_INTEN_MASK	S526_GPCT_CTRL_INTEN(0xf)
#घोषणा S525_GPCT_CTRL_INTEN_NONE	S526_GPCT_CTRL_INTEN(0)
/* these 4 bits can be OR'ed */
#घोषणा S525_GPCT_CTRL_INTEN_ERROR	S526_GPCT_CTRL_INTEN(0x1)
#घोषणा S525_GPCT_CTRL_INTEN_IXFALL	S526_GPCT_CTRL_INTEN(0x2)
#घोषणा S525_GPCT_CTRL_INTEN_IXRISE	S526_GPCT_CTRL_INTEN(0x4)
#घोषणा S525_GPCT_CTRL_INTEN_RO		S526_GPCT_CTRL_INTEN(0x8)
#घोषणा S525_GPCT_CTRL_LATCH_SEL(x)	((x) << 10)		/* W */
#घोषणा S525_GPCT_CTRL_LATCH_SEL_MASK	S526_GPCT_CTRL_LATCH_SEL(0x7)
#घोषणा S525_GPCT_CTRL_LATCH_SEL_NONE	S526_GPCT_CTRL_LATCH_SEL(0)
/* these 3 bits can be OR'ed */
#घोषणा S525_GPCT_CTRL_LATCH_SEL_IXFALL	S526_GPCT_CTRL_LATCH_SEL(0x1)
#घोषणा S525_GPCT_CTRL_LATCH_SEL_IXRISE	S526_GPCT_CTRL_LATCH_SEL(0x2)
#घोषणा S525_GPCT_CTRL_LATCH_SEL_ITIMER	S526_GPCT_CTRL_LATCH_SEL(0x4)
#घोषणा S525_GPCT_CTRL_CT_ARM		BIT(13)			/* W */
#घोषणा S525_GPCT_CTRL_CT_LOAD		BIT(14)			/* W */
#घोषणा S526_GPCT_CTRL_CT_RESET		BIT(15)			/* W */
#घोषणा S526_EEPROM_DATA_REG	0x32
#घोषणा S526_EEPROM_CTRL_REG	0x34
#घोषणा S526_EEPROM_CTRL_ADDR(x) (((x) & 0x3f) << 3)
#घोषणा S526_EEPROM_CTRL(x)	(((x) & 0x3) << 1)
#घोषणा S526_EEPROM_CTRL_READ	S526_EEPROM_CTRL(2)
#घोषणा S526_EEPROM_CTRL_START	BIT(0)

काष्ठा s526_निजी अणु
	अचिन्हित पूर्णांक gpct_config[4];
	अचिन्हित लघु ai_ctrl;
पूर्ण;

अटल व्योम s526_gpct_ग_लिखो(काष्ठा comedi_device *dev,
			    अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक val)
अणु
	/* ग_लिखो high word then low word */
	outw((val >> 16) & 0xffff, dev->iobase + S526_GPCT_MSB_REG(chan));
	outw(val & 0xffff, dev->iobase + S526_GPCT_LSB_REG(chan));
पूर्ण

अटल अचिन्हित पूर्णांक s526_gpct_पढ़ो(काष्ठा comedi_device *dev,
				   अचिन्हित पूर्णांक chan)
अणु
	अचिन्हित पूर्णांक val;

	/* पढ़ो the low word then high word */
	val = inw(dev->iobase + S526_GPCT_LSB_REG(chan)) & 0xffff;
	val |= (inw(dev->iobase + S526_GPCT_MSB_REG(chan)) & 0xff) << 16;

	वापस val;
पूर्ण

अटल पूर्णांक s526_gpct_rinsn(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++)
		data[i] = s526_gpct_पढ़ो(dev, chan);

	वापस insn->n;
पूर्ण

अटल पूर्णांक s526_gpct_insn_config(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा s526_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val;

	/*
	 * Check what type of Counter the user requested
	 * data[0] contains the Application type
	 */
	चयन (data[0]) अणु
	हाल INSN_CONFIG_GPCT_QUADRATURE_ENCODER:
		/*
		 * data[0]: Application Type
		 * data[1]: Counter Mode Register Value
		 * data[2]: Pre-load Register Value
		 * data[3]: Conter Control Register
		 */
		devpriv->gpct_config[chan] = data[0];

#अगर 1
		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/*  Reset the counter अगर it is software preload */
		अगर ((val & S526_GPCT_MODE_AUTOLOAD_MASK) ==
		    S526_GPCT_MODE_AUTOLOAD_NONE) अणु
			/*  Reset the counter */
			outw(S526_GPCT_CTRL_CT_RESET,
			     dev->iobase + S526_GPCT_CTRL_REG(chan));
			/*
			 * Load the counter from PR0
			 * outw(S526_GPCT_CTRL_CT_LOAD,
			 *      dev->iobase + S526_GPCT_CTRL_REG(chan));
			 */
		पूर्ण
#अन्यथा
		val = S526_GPCT_MODE_CTसूची_CTRL_QUAD;

		/*  data[1] contains GPCT_X1, GPCT_X2 or GPCT_X4 */
		अगर (data[1] == GPCT_X2)
			val |= S526_GPCT_MODE_CLK_SRC_QUADX2;
		अन्यथा अगर (data[1] == GPCT_X4)
			val |= S526_GPCT_MODE_CLK_SRC_QUADX4;
		अन्यथा
			val |= S526_GPCT_MODE_CLK_SRC_QUADX1;

		/*  When to take पूर्णांकo account the indexpulse: */
		/*
		 * अगर (data[2] == GPCT_IndexPhaseLowLow) अणु
		 * पूर्ण अन्यथा अगर (data[2] == GPCT_IndexPhaseLowHigh) अणु
		 * पूर्ण अन्यथा अगर (data[2] == GPCT_IndexPhaseHighLow) अणु
		 * पूर्ण अन्यथा अगर (data[2] == GPCT_IndexPhaseHighHigh) अणु
		 * पूर्ण
		 */
		/*  Take पूर्णांकo account the index pulse? */
		अगर (data[3] == GPCT_RESET_COUNTER_ON_INDEX) अणु
			/*  Auto load with INDEX^ */
			val |= S526_GPCT_MODE_AUTOLOAD_IXRISE;
		पूर्ण

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/*  Load the pre-load रेजिस्टर */
		s526_gpct_ग_लिखो(dev, chan, data[2]);

		/*  Write the Counter Control Register */
		अगर (data[3])
			outw(data[3] & 0xffff,
			     dev->iobase + S526_GPCT_CTRL_REG(chan));

		/*  Reset the counter अगर it is software preload */
		अगर ((val & S526_GPCT_MODE_AUTOLOAD_MASK) ==
		    S526_GPCT_MODE_AUTOLOAD_NONE) अणु
			/*  Reset the counter */
			outw(S526_GPCT_CTRL_CT_RESET,
			     dev->iobase + S526_GPCT_CTRL_REG(chan));
			/*  Load the counter from PR0 */
			outw(S526_GPCT_CTRL_CT_LOAD,
			     dev->iobase + S526_GPCT_CTRL_REG(chan));
		पूर्ण
#पूर्ण_अगर
		अवरोध;

	हाल INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR:
		/*
		 * data[0]: Application Type
		 * data[1]: Counter Mode Register Value
		 * data[2]: Pre-load Register 0 Value
		 * data[3]: Pre-load Register 1 Value
		 * data[4]: Conter Control Register
		 */
		devpriv->gpct_config[chan] = data[0];

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		/* Select PR0 */
		val &= ~S526_GPCT_MODE_PR_SELECT_MASK;
		val |= S526_GPCT_MODE_PR_SELECT_PR0;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/* Load the pre-load रेजिस्टर 0 */
		s526_gpct_ग_लिखो(dev, chan, data[2]);

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		/* Select PR1 */
		val &= ~S526_GPCT_MODE_PR_SELECT_MASK;
		val |= S526_GPCT_MODE_PR_SELECT_PR1;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/* Load the pre-load रेजिस्टर 1 */
		s526_gpct_ग_लिखो(dev, chan, data[3]);

		/*  Write the Counter Control Register */
		अगर (data[4]) अणु
			val = data[4] & 0xffff;
			outw(val, dev->iobase + S526_GPCT_CTRL_REG(chan));
		पूर्ण
		अवरोध;

	हाल INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR:
		/*
		 * data[0]: Application Type
		 * data[1]: Counter Mode Register Value
		 * data[2]: Pre-load Register 0 Value
		 * data[3]: Pre-load Register 1 Value
		 * data[4]: Conter Control Register
		 */
		devpriv->gpct_config[chan] = data[0];

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		/* Select PR0 */
		val &= ~S526_GPCT_MODE_PR_SELECT_MASK;
		val |= S526_GPCT_MODE_PR_SELECT_PR0;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/* Load the pre-load रेजिस्टर 0 */
		s526_gpct_ग_लिखो(dev, chan, data[2]);

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		/* Select PR1 */
		val &= ~S526_GPCT_MODE_PR_SELECT_MASK;
		val |= S526_GPCT_MODE_PR_SELECT_PR1;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/* Load the pre-load रेजिस्टर 1 */
		s526_gpct_ग_लिखो(dev, chan, data[3]);

		/*  Write the Counter Control Register */
		अगर (data[4]) अणु
			val = data[4] & 0xffff;
			outw(val, dev->iobase + S526_GPCT_CTRL_REG(chan));
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक s526_gpct_winsn(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा s526_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	inw(dev->iobase + S526_GPCT_MODE_REG(chan));	/* Is this required? */

	/*  Check what Application of Counter this channel is configured क्रम */
	चयन (devpriv->gpct_config[chan]) अणु
	हाल INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR:
		/*
		 * data[0] contains the PULSE_WIDTH
		 * data[1] contains the PULSE_PERIOD
		 * @pre PULSE_PERIOD > PULSE_WIDTH > 0
		 * The above periods must be expressed as a multiple of the
		 * pulse frequency on the selected source
		 */
		अगर ((data[1] <= data[0]) || !data[0])
			वापस -EINVAL;
		/* to ग_लिखो the PULSE_WIDTH */
		fallthrough;
	हाल INSN_CONFIG_GPCT_QUADRATURE_ENCODER:
	हाल INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR:
		s526_gpct_ग_लिखो(dev, chan, data[0]);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक s526_eoc(काष्ठा comedi_device *dev,
		    काष्ठा comedi_subdevice *s,
		    काष्ठा comedi_insn *insn,
		    अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + S526_INT_STATUS_REG);
	अगर (status & context) अणु
		/* we got our eoc event, clear it */
		outw(context, dev->iobase + S526_INT_STATUS_REG);
		वापस 0;
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक s526_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा s526_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	ctrl = S526_AI_CTRL_CONV(chan) | S526_AI_CTRL_READ(chan) |
	       S526_AI_CTRL_START;
	अगर (ctrl != devpriv->ai_ctrl) अणु
		/*
		 * The multiplexor needs to change, enable the 15us
		 * delay क्रम the first sample.
		 */
		devpriv->ai_ctrl = ctrl;
		ctrl |= S526_AI_CTRL_DELAY;
	पूर्ण

	क्रम (i = 0; i < insn->n; i++) अणु
		/* trigger conversion */
		outw(ctrl, dev->iobase + S526_AI_CTRL_REG);
		ctrl &= ~S526_AI_CTRL_DELAY;

		/* रुको क्रम conversion to end */
		ret = comedi_समयout(dev, s, insn, s526_eoc, S526_INT_AI);
		अगर (ret)
			वापस ret;

		val = inw(dev->iobase + S526_AI_REG);
		data[i] = comedi_offset_munge(s, val);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक s526_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक ctrl = S526_AO_CTRL_CHAN(chan);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक ret;
	पूर्णांक i;

	outw(ctrl, dev->iobase + S526_AO_CTRL_REG);
	ctrl |= S526_AO_CTRL_START;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outw(val, dev->iobase + S526_AO_REG);
		outw(ctrl, dev->iobase + S526_AO_CTRL_REG);

		/* रुको क्रम conversion to end */
		ret = comedi_समयout(dev, s, insn, s526_eoc, S526_INT_AO);
		अगर (ret)
			वापस ret;
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक s526_dio_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + S526_DIO_CTRL_REG);

	data[1] = inw(dev->iobase + S526_DIO_CTRL_REG) & 0xff;

	वापस insn->n;
पूर्ण

अटल पूर्णांक s526_dio_insn_config(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	/*
	 * Digital I/O can be configured as inमाला_दो or outमाला_दो in
	 * groups of 4; DIO group 1 (DIO0-3) and DIO group 2 (DIO4-7).
	 */
	अगर (chan < 4)
		mask = 0x0f;
	अन्यथा
		mask = 0xf0;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	अगर (s->io_bits & 0x0f)
		s->state |= S526_DIO_CTRL_GRP1_OUT;
	अन्यथा
		s->state &= ~S526_DIO_CTRL_GRP1_OUT;
	अगर (s->io_bits & 0xf0)
		s->state |= S526_DIO_CTRL_GRP2_OUT;
	अन्यथा
		s->state &= ~S526_DIO_CTRL_GRP2_OUT;

	outw(s->state, dev->iobase + S526_DIO_CTRL_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक s526_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा s526_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x40);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* General-Purpose Counter/Timer (GPCT) */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_LSAMPL;
	s->n_chan	= 4;
	s->maxdata	= 0x00ffffff;
	s->insn_पढ़ो	= s526_gpct_rinsn;
	s->insn_config	= s526_gpct_insn_config;
	s->insn_ग_लिखो	= s526_gpct_winsn;

	/*
	 * Analog Input subdevice
	 * channels 0 to 7 are the regular dअगरferential inमाला_दो
	 * channel 8 is "reference 0" (+10V)
	 * channel 9 is "reference 1" (0V)
	 */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_DIFF;
	s->n_chan	= 10;
	s->maxdata	= 0xffff;
	s->range_table	= &range_bipolar10;
	s->len_chanlist	= 16;
	s->insn_पढ़ो	= s526_ai_insn_पढ़ो;

	/* Analog Output subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->range_table	= &range_bipolar10;
	s->insn_ग_लिखो	= s526_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital I/O subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= s526_dio_insn_bits;
	s->insn_config	= s526_dio_insn_config;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver s526_driver = अणु
	.driver_name	= "s526",
	.module		= THIS_MODULE,
	.attach		= s526_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(s526_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
