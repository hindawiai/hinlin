<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * cb_pcidas.c
 * Developed by Ivan Martinez and Frank Mori Hess, with valuable help from
 * David Schleef and the rest of the Comedi developers comunity.
 *
 * Copyright (C) 2001-2003 Ivan Martinez <imr@oersted.dtu.dk>
 * Copyright (C) 2001,2002 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-8 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: cb_pcidas
 * Description: MeasurementComputing PCI-DAS series
 *   with the AMCC S5933 PCI controller
 * Devices: [Measurement Computing] PCI-DAS1602/16 (cb_pcidas),
 *   PCI-DAS1602/16jr, PCI-DAS1602/12, PCI-DAS1200, PCI-DAS1200jr,
 *   PCI-DAS1000, PCI-DAS1001, PCI_DAS1002
 * Author: Ivan Martinez <imr@oersted.dtu.dk>,
 *   Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Updated: 2003-3-11
 *
 * Status:
 * There are many reports of the driver being used with most of the
 * supported cards. Despite no detailed log is मुख्यtained, it can
 * be said that the driver is quite tested and stable.
 *
 * The boards may be स्वतःcalibrated using the comedi_calibrate
 * utility.
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 *
 * For commands, the scanned channels must be consecutive
 * (i.e. 4-5-6-7, 2-3-4,...), and must all have the same
 * range and aref.
 *
 * AI Triggering:
 * For start_src == TRIG_EXT, the A/D EXTERNAL TRIGGER IN (pin 45) is used.
 * For 1602 series, the start_arg is पूर्णांकerpreted as follows:
 *	start_arg == 0                   => gated trigger (level high)
 *	start_arg == CR_INVERT           => gated trigger (level low)
 *	start_arg == CR_EDGE             => Rising edge
 *	start_arg == CR_EDGE | CR_INVERT => Falling edge
 * For the other boards the trigger will be करोne on rising edge
 */

/*
 * TODO:
 * analog triggering on 1602 series
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "comedi_8254.h"
#समावेश "8255.h"
#समावेश "amcc_s5933.h"

#घोषणा AI_BUFFER_SIZE		1024	/* max ai fअगरo size */
#घोषणा AO_BUFFER_SIZE		1024	/* max ao fअगरo size */

/*
 * PCI BAR1 Register map (devpriv->pcibar1)
 */
#घोषणा PCIDAS_CTRL_REG		0x00	/* INTERRUPT / ADC FIFO रेजिस्टर */
#घोषणा PCIDAS_CTRL_INT(x)	(((x) & 0x3) << 0)
#घोषणा PCIDAS_CTRL_INT_NONE	PCIDAS_CTRL_INT(0) /* no पूर्णांक selected */
#घोषणा PCIDAS_CTRL_INT_EOS	PCIDAS_CTRL_INT(1) /* पूर्णांक on end of scan */
#घोषणा PCIDAS_CTRL_INT_FHF	PCIDAS_CTRL_INT(2) /* पूर्णांक on fअगरo half full */
#घोषणा PCIDAS_CTRL_INT_FNE	PCIDAS_CTRL_INT(3) /* पूर्णांक on fअगरo not empty */
#घोषणा PCIDAS_CTRL_INT_MASK	PCIDAS_CTRL_INT(3) /* mask of पूर्णांक select bits */
#घोषणा PCIDAS_CTRL_INTE	BIT(2)	/* पूर्णांक enable */
#घोषणा PCIDAS_CTRL_DAHFIE	BIT(3)	/* dac half full पूर्णांक enable */
#घोषणा PCIDAS_CTRL_EOAIE	BIT(4)	/* end of acq. पूर्णांक enable */
#घोषणा PCIDAS_CTRL_DAHFI	BIT(5)	/* dac half full status / clear */
#घोषणा PCIDAS_CTRL_EOAI	BIT(6)	/* end of acq. पूर्णांक status / clear */
#घोषणा PCIDAS_CTRL_INT_CLR	BIT(7)	/* पूर्णांक status / clear */
#घोषणा PCIDAS_CTRL_EOBI	BIT(9)	/* end of burst पूर्णांक status */
#घोषणा PCIDAS_CTRL_ADHFI	BIT(10)	/* half-full पूर्णांक status */
#घोषणा PCIDAS_CTRL_ADNEI	BIT(11)	/* fअगरo not empty पूर्णांक status (latch) */
#घोषणा PCIDAS_CTRL_ADNE	BIT(12)	/* fअगरo not empty status (realसमय) */
#घोषणा PCIDAS_CTRL_DAEMIE	BIT(12)	/* dac empty पूर्णांक enable */
#घोषणा PCIDAS_CTRL_LADFUL	BIT(13)	/* fअगरo overflow / clear */
#घोषणा PCIDAS_CTRL_DAEMI	BIT(14)	/* dac fअगरo empty पूर्णांक status / clear */

#घोषणा PCIDAS_CTRL_AI_INT	(PCIDAS_CTRL_EOAI | PCIDAS_CTRL_EOBI |   \
				 PCIDAS_CTRL_ADHFI | PCIDAS_CTRL_ADNEI | \
				 PCIDAS_CTRL_LADFUL)
#घोषणा PCIDAS_CTRL_AO_INT	(PCIDAS_CTRL_DAHFI | PCIDAS_CTRL_DAEMI)

#घोषणा PCIDAS_AI_REG		0x02	/* ADC CHANNEL MUX AND CONTROL reg */
#घोषणा PCIDAS_AI_FIRST(x)	((x) & 0xf)
#घोषणा PCIDAS_AI_LAST(x)	(((x) & 0xf) << 4)
#घोषणा PCIDAS_AI_CHAN(x)	(PCIDAS_AI_FIRST(x) | PCIDAS_AI_LAST(x))
#घोषणा PCIDAS_AI_GAIN(x)	(((x) & 0x3) << 8)
#घोषणा PCIDAS_AI_SE		BIT(10)	/* Inमाला_दो in single-ended mode */
#घोषणा PCIDAS_AI_UNIP		BIT(11)	/* Analog front-end unipolar mode */
#घोषणा PCIDAS_AI_PACER(x)	(((x) & 0x3) << 12)
#घोषणा PCIDAS_AI_PACER_SW	PCIDAS_AI_PACER(0) /* software pacer */
#घोषणा PCIDAS_AI_PACER_INT	PCIDAS_AI_PACER(1) /* पूर्णांक. pacer */
#घोषणा PCIDAS_AI_PACER_EXTN	PCIDAS_AI_PACER(2) /* ext. falling edge */
#घोषणा PCIDAS_AI_PACER_EXTP	PCIDAS_AI_PACER(3) /* ext. rising edge */
#घोषणा PCIDAS_AI_PACER_MASK	PCIDAS_AI_PACER(3) /* pacer source bits */
#घोषणा PCIDAS_AI_EOC		BIT(14)	/* adc not busy */

#घोषणा PCIDAS_TRIG_REG		0x04	/* TRIGGER CONTROL/STATUS रेजिस्टर */
#घोषणा PCIDAS_TRIG_SEL(x)	(((x) & 0x3) << 0)
#घोषणा PCIDAS_TRIG_SEL_NONE	PCIDAS_TRIG_SEL(0) /* no start trigger */
#घोषणा PCIDAS_TRIG_SEL_SW	PCIDAS_TRIG_SEL(1) /* software start trigger */
#घोषणा PCIDAS_TRIG_SEL_EXT	PCIDAS_TRIG_SEL(2) /* ext. start trigger */
#घोषणा PCIDAS_TRIG_SEL_ANALOG	PCIDAS_TRIG_SEL(3) /* ext. analog trigger */
#घोषणा PCIDAS_TRIG_SEL_MASK	PCIDAS_TRIG_SEL(3) /* start trigger mask */
#घोषणा PCIDAS_TRIG_POL		BIT(2)	/* invert trigger (1602 only) */
#घोषणा PCIDAS_TRIG_MODE	BIT(3)	/* edge/level triggered (1602 only) */
#घोषणा PCIDAS_TRIG_EN		BIT(4)	/* enable बाह्यal start trigger */
#घोषणा PCIDAS_TRIG_BURSTE	BIT(5)	/* burst mode enable */
#घोषणा PCIDAS_TRIG_CLR		BIT(7)	/* clear बाह्यal trigger */

#घोषणा PCIDAS_CALIB_REG	0x06	/* CALIBRATION रेजिस्टर */
#घोषणा PCIDAS_CALIB_8800_SEL	BIT(8)	/* select 8800 caldac */
#घोषणा PCIDAS_CALIB_TRIM_SEL	BIT(9)	/* select ad7376 trim pot */
#घोषणा PCIDAS_CALIB_DAC08_SEL	BIT(10)	/* select dac08 caldac */
#घोषणा PCIDAS_CALIB_SRC(x)	(((x) & 0x7) << 11)
#घोषणा PCIDAS_CALIB_EN		BIT(14)	/* calibration source enable */
#घोषणा PCIDAS_CALIB_DATA	BIT(15)	/* serial data bit going to caldac */

#घोषणा PCIDAS_AO_REG		0x08	/* dac control and status रेजिस्टर */
#घोषणा PCIDAS_AO_EMPTY		BIT(0)	/* fअगरo empty, ग_लिखो clear (1602) */
#घोषणा PCIDAS_AO_DACEN		BIT(1)	/* dac enable */
#घोषणा PCIDAS_AO_START		BIT(2)	/* start/arm fअगरo (1602) */
#घोषणा PCIDAS_AO_PACER(x)	(((x) & 0x3) << 3) /* (1602) */
#घोषणा PCIDAS_AO_PACER_SW	PCIDAS_AO_PACER(0) /* software pacer */
#घोषणा PCIDAS_AO_PACER_INT	PCIDAS_AO_PACER(1) /* पूर्णांक. pacer */
#घोषणा PCIDAS_AO_PACER_EXTN	PCIDAS_AO_PACER(2) /* ext. falling edge */
#घोषणा PCIDAS_AO_PACER_EXTP	PCIDAS_AO_PACER(3) /* ext. rising edge */
#घोषणा PCIDAS_AO_PACER_MASK	PCIDAS_AO_PACER(3) /* pacer source bits */
#घोषणा PCIDAS_AO_CHAN_EN(c)	BIT(5 + ((c) & 0x1))
#घोषणा PCIDAS_AO_CHAN_MASK	(PCIDAS_AO_CHAN_EN(0) | PCIDAS_AO_CHAN_EN(1))
#घोषणा PCIDAS_AO_UPDATE_BOTH	BIT(7)	/* update both dacs */
#घोषणा PCIDAS_AO_RANGE(c, r)	(((r) & 0x3) << (8 + 2 * ((c) & 0x1)))
#घोषणा PCIDAS_AO_RANGE_MASK(c)	PCIDAS_AO_RANGE((c), 0x3)

/*
 * PCI BAR2 Register map (devpriv->pcibar2)
 */
#घोषणा PCIDAS_AI_DATA_REG	0x00
#घोषणा PCIDAS_AI_FIFO_CLR_REG	0x02

/*
 * PCI BAR3 Register map (dev->iobase)
 */
#घोषणा PCIDAS_AI_8254_BASE	0x00
#घोषणा PCIDAS_8255_BASE	0x04
#घोषणा PCIDAS_AO_8254_BASE	0x08

/*
 * PCI BAR4 Register map (devpriv->pcibar4)
 */
#घोषणा PCIDAS_AO_DATA_REG(x)	(0x00 + ((x) * 2))
#घोषणा PCIDAS_AO_FIFO_REG	0x00
#घोषणा PCIDAS_AO_FIFO_CLR_REG	0x02

/* analog input ranges क्रम most boards */
अटल स्थिर काष्ठा comedi_lrange cb_pcidas_ranges = अणु
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

/* pci-das1001 input ranges */
अटल स्थिर काष्ठा comedi_lrange cb_pcidas_alt_ranges = अणु
	8, अणु
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.01),
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.01)
	पूर्ण
पूर्ण;

/* analog output ranges */
अटल स्थिर काष्ठा comedi_lrange cb_pcidas_ao_ranges = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

क्रमागत cb_pcidas_boardid अणु
	BOARD_PCIDAS1602_16,
	BOARD_PCIDAS1200,
	BOARD_PCIDAS1602_12,
	BOARD_PCIDAS1200_JR,
	BOARD_PCIDAS1602_16_JR,
	BOARD_PCIDAS1000,
	BOARD_PCIDAS1001,
	BOARD_PCIDAS1002,
पूर्ण;

काष्ठा cb_pcidas_board अणु
	स्थिर अक्षर *name;
	पूर्णांक ai_speed;		/*  fastest conversion period in ns */
	पूर्णांक ao_scan_speed;	/*  analog output scan speed क्रम 1602 series */
	पूर्णांक fअगरo_size;		/*  number of samples fअगरo can hold */
	अचिन्हित पूर्णांक is_16bit;		/* ai/ao is 1=16-bit; 0=12-bit */
	अचिन्हित पूर्णांक use_alt_range:1;	/* use alternate ai range table */
	अचिन्हित पूर्णांक has_ao:1;		/* has 2 analog output channels */
	अचिन्हित पूर्णांक has_ao_fअगरo:1;	/* analog output has fअगरo */
	अचिन्हित पूर्णांक has_ad8402:1;	/* trimpot type 1=AD8402; 0=AD7376 */
	अचिन्हित पूर्णांक has_dac08:1;
	अचिन्हित पूर्णांक is_1602:1;
पूर्ण;

अटल स्थिर काष्ठा cb_pcidas_board cb_pcidas_boards[] = अणु
	[BOARD_PCIDAS1602_16] = अणु
		.name		= "pci-das1602/16",
		.ai_speed	= 5000,
		.ao_scan_speed	= 10000,
		.fअगरo_size	= 512,
		.is_16bit	= 1,
		.has_ao		= 1,
		.has_ao_fअगरo	= 1,
		.has_ad8402	= 1,
		.has_dac08	= 1,
		.is_1602	= 1,
	पूर्ण,
	[BOARD_PCIDAS1200] = अणु
		.name		= "pci-das1200",
		.ai_speed	= 3200,
		.fअगरo_size	= 1024,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_PCIDAS1602_12] = अणु
		.name		= "pci-das1602/12",
		.ai_speed	= 3200,
		.ao_scan_speed	= 4000,
		.fअगरo_size	= 1024,
		.has_ao		= 1,
		.has_ao_fअगरo	= 1,
		.is_1602	= 1,
	पूर्ण,
	[BOARD_PCIDAS1200_JR] = अणु
		.name		= "pci-das1200/jr",
		.ai_speed	= 3200,
		.fअगरo_size	= 1024,
	पूर्ण,
	[BOARD_PCIDAS1602_16_JR] = अणु
		.name		= "pci-das1602/16/jr",
		.ai_speed	= 5000,
		.fअगरo_size	= 512,
		.is_16bit	= 1,
		.has_ad8402	= 1,
		.has_dac08	= 1,
		.is_1602	= 1,
	पूर्ण,
	[BOARD_PCIDAS1000] = अणु
		.name		= "pci-das1000",
		.ai_speed	= 4000,
		.fअगरo_size	= 1024,
	पूर्ण,
	[BOARD_PCIDAS1001] = अणु
		.name		= "pci-das1001",
		.ai_speed	= 6800,
		.fअगरo_size	= 1024,
		.use_alt_range	= 1,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_PCIDAS1002] = अणु
		.name		= "pci-das1002",
		.ai_speed	= 6800,
		.fअगरo_size	= 1024,
		.has_ao		= 1,
	पूर्ण,
पूर्ण;

काष्ठा cb_pcidas_निजी अणु
	काष्ठा comedi_8254 *ao_pacer;
	/* base addresses */
	अचिन्हित दीर्घ amcc;	/* pcibar0 */
	अचिन्हित दीर्घ pcibar1;
	अचिन्हित दीर्घ pcibar2;
	अचिन्हित दीर्घ pcibar4;
	/* bits to ग_लिखो to रेजिस्टरs */
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक amcc_पूर्णांकcsr;
	अचिन्हित पूर्णांक ao_ctrl;
	/* fअगरo buffers */
	अचिन्हित लघु ai_buffer[AI_BUFFER_SIZE];
	अचिन्हित लघु ao_buffer[AO_BUFFER_SIZE];
	अचिन्हित पूर्णांक calib_src;
पूर्ण;

अटल पूर्णांक cb_pcidas_ai_eoc(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn,
			    अचिन्हित दीर्घ context)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status;

	status = inw(devpriv->pcibar1 + PCIDAS_AI_REG);
	अगर (status & PCIDAS_AI_EOC)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक cb_pcidas_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(insn->chanspec);
	अचिन्हित पूर्णांक bits;
	पूर्णांक ret;
	पूर्णांक n;

	/* enable calibration input अगर appropriate */
	अगर (insn->chanspec & CR_ALT_SOURCE) अणु
		outw(PCIDAS_CALIB_EN | PCIDAS_CALIB_SRC(devpriv->calib_src),
		     devpriv->pcibar1 + PCIDAS_CALIB_REG);
		chan = 0;
	पूर्ण अन्यथा अणु
		outw(0, devpriv->pcibar1 + PCIDAS_CALIB_REG);
	पूर्ण

	/* set mux limits and gain */
	bits = PCIDAS_AI_CHAN(chan) | PCIDAS_AI_GAIN(range);
	/* set unipolar/bipolar */
	अगर (comedi_range_is_unipolar(s, range))
		bits |= PCIDAS_AI_UNIP;
	/* set single-ended/dअगरferential */
	अगर (aref != AREF_DIFF)
		bits |= PCIDAS_AI_SE;
	outw(bits, devpriv->pcibar1 + PCIDAS_AI_REG);

	/* clear fअगरo */
	outw(0, devpriv->pcibar2 + PCIDAS_AI_FIFO_CLR_REG);

	/* convert n samples */
	क्रम (n = 0; n < insn->n; n++) अणु
		/* trigger conversion */
		outw(0, devpriv->pcibar2 + PCIDAS_AI_DATA_REG);

		/* रुको क्रम conversion to end */
		ret = comedi_समयout(dev, s, insn, cb_pcidas_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		/* पढ़ो data */
		data[n] = inw(devpriv->pcibar2 + PCIDAS_AI_DATA_REG);
	पूर्ण

	/* वापस the number of samples पढ़ो/written */
	वापस n;
पूर्ण

अटल पूर्णांक cb_pcidas_ai_insn_config(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	पूर्णांक id = data[0];
	अचिन्हित पूर्णांक source = data[1];

	चयन (id) अणु
	हाल INSN_CONFIG_ALT_SOURCE:
		अगर (source >= 8) अणु
			dev_err(dev->class_dev,
				"invalid calibration source: %i\n",
				source);
			वापस -EINVAL;
		पूर्ण
		devpriv->calib_src = source;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस insn->n;
पूर्ण

/* analog output insn क्रम pcidas-1000 and 1200 series */
अटल पूर्णांक cb_pcidas_ao_nofअगरo_insn_ग_लिखो(काष्ठा comedi_device *dev,
					  काष्ठा comedi_subdevice *s,
					  काष्ठा comedi_insn *insn,
					  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* set channel and range */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->ao_ctrl &= ~(PCIDAS_AO_UPDATE_BOTH |
			      PCIDAS_AO_RANGE_MASK(chan));
	devpriv->ao_ctrl |= PCIDAS_AO_DACEN | PCIDAS_AO_RANGE(chan, range);
	outw(devpriv->ao_ctrl, devpriv->pcibar1 + PCIDAS_AO_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outw(val, devpriv->pcibar4 + PCIDAS_AO_DATA_REG(chan));
	पूर्ण

	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

/* analog output insn क्रम pcidas-1602 series */
अटल पूर्णांक cb_pcidas_ao_fअगरo_insn_ग_लिखो(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					काष्ठा comedi_insn *insn,
					अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* clear dac fअगरo */
	outw(0, devpriv->pcibar4 + PCIDAS_AO_FIFO_CLR_REG);

	/* set channel and range */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->ao_ctrl &= ~(PCIDAS_AO_CHAN_MASK | PCIDAS_AO_RANGE_MASK(chan) |
			      PCIDAS_AO_PACER_MASK);
	devpriv->ao_ctrl |= PCIDAS_AO_DACEN | PCIDAS_AO_RANGE(chan, range) |
			    PCIDAS_AO_CHAN_EN(chan) | PCIDAS_AO_START;
	outw(devpriv->ao_ctrl, devpriv->pcibar1 + PCIDAS_AO_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outw(val, devpriv->pcibar4 + PCIDAS_AO_FIFO_REG);
	पूर्ण

	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक cb_pcidas_eeprom_पढ़ोy(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित दीर्घ context)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status;

	status = inb(devpriv->amcc + AMCC_OP_REG_MCSR_NVCMD);
	अगर ((status & MCSR_NV_BUSY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक cb_pcidas_eeprom_insn_पढ़ो(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		/* make sure eeprom is पढ़ोy */
		ret = comedi_समयout(dev, s, insn, cb_pcidas_eeprom_पढ़ोy, 0);
		अगर (ret)
			वापस ret;

		/* set address (chan) and पढ़ो operation */
		outb(MCSR_NV_ENABLE | MCSR_NV_LOAD_LOW_ADDR,
		     devpriv->amcc + AMCC_OP_REG_MCSR_NVCMD);
		outb(chan & 0xff, devpriv->amcc + AMCC_OP_REG_MCSR_NVDATA);
		outb(MCSR_NV_ENABLE | MCSR_NV_LOAD_HIGH_ADDR,
		     devpriv->amcc + AMCC_OP_REG_MCSR_NVCMD);
		outb((chan >> 8) & 0xff,
		     devpriv->amcc + AMCC_OP_REG_MCSR_NVDATA);
		outb(MCSR_NV_ENABLE | MCSR_NV_READ,
		     devpriv->amcc + AMCC_OP_REG_MCSR_NVCMD);

		/* रुको क्रम data to be वापसed */
		ret = comedi_समयout(dev, s, insn, cb_pcidas_eeprom_पढ़ोy, 0);
		अगर (ret)
			वापस ret;

		data[i] = inb(devpriv->amcc + AMCC_OP_REG_MCSR_NVDATA);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम cb_pcidas_calib_ग_लिखो(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक len,
				  bool trimpot)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक calib_bits;
	अचिन्हित पूर्णांक bit;

	calib_bits = PCIDAS_CALIB_EN | PCIDAS_CALIB_SRC(devpriv->calib_src);
	अगर (trimpot) अणु
		/* select trimpot */
		calib_bits |= PCIDAS_CALIB_TRIM_SEL;
		outw(calib_bits, devpriv->pcibar1 + PCIDAS_CALIB_REG);
	पूर्ण

	/* ग_लिखो bitstream to calibration device */
	क्रम (bit = 1 << (len - 1); bit; bit >>= 1) अणु
		अगर (val & bit)
			calib_bits |= PCIDAS_CALIB_DATA;
		अन्यथा
			calib_bits &= ~PCIDAS_CALIB_DATA;
		udelay(1);
		outw(calib_bits, devpriv->pcibar1 + PCIDAS_CALIB_REG);
	पूर्ण
	udelay(1);

	calib_bits = PCIDAS_CALIB_EN | PCIDAS_CALIB_SRC(devpriv->calib_src);

	अगर (!trimpot) अणु
		/* select caldac */
		outw(calib_bits | PCIDAS_CALIB_8800_SEL,
		     devpriv->pcibar1 + PCIDAS_CALIB_REG);
		udelay(1);
	पूर्ण

	/* latch value to trimpot/caldac */
	outw(calib_bits, devpriv->pcibar1 + PCIDAS_CALIB_REG);
पूर्ण

अटल पूर्णांक cb_pcidas_caldac_insn_ग_लिखो(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_insn *insn,
				       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	अगर (insn->n) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		अगर (s->पढ़ोback[chan] != val) अणु
			/* ग_लिखो 11-bit channel/value to caldac */
			cb_pcidas_calib_ग_लिखो(dev, (chan << 8) | val, 11,
					      false);
			s->पढ़ोback[chan] = val;
		पूर्ण
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम cb_pcidas_dac08_ग_लिखो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक val)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;

	val |= PCIDAS_CALIB_EN | PCIDAS_CALIB_SRC(devpriv->calib_src);

	/* latch the new value पूर्णांकo the caldac */
	outw(val, devpriv->pcibar1 + PCIDAS_CALIB_REG);
	udelay(1);
	outw(val | PCIDAS_CALIB_DAC08_SEL,
	     devpriv->pcibar1 + PCIDAS_CALIB_REG);
	udelay(1);
	outw(val, devpriv->pcibar1 + PCIDAS_CALIB_REG);
	udelay(1);
पूर्ण

अटल पूर्णांक cb_pcidas_dac08_insn_ग_लिखो(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	अगर (insn->n) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		अगर (s->पढ़ोback[chan] != val) अणु
			cb_pcidas_dac08_ग_लिखो(dev, val);
			s->पढ़ोback[chan] = val;
		पूर्ण
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम cb_pcidas_trimpot_ग_लिखो(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक val)
अणु
	स्थिर काष्ठा cb_pcidas_board *board = dev->board_ptr;

	अगर (board->has_ad8402) अणु
		/* ग_लिखो 10-bit channel/value to AD8402 trimpot */
		cb_pcidas_calib_ग_लिखो(dev, (chan << 8) | val, 10, true);
	पूर्ण अन्यथा अणु
		/* ग_लिखो 7-bit value to AD7376 trimpot */
		cb_pcidas_calib_ग_लिखो(dev, val, 7, true);
	पूर्ण
पूर्ण

अटल पूर्णांक cb_pcidas_trimpot_insn_ग_लिखो(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					काष्ठा comedi_insn *insn,
					अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	अगर (insn->n) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		अगर (s->पढ़ोback[chan] != val) अणु
			cb_pcidas_trimpot_ग_लिखो(dev, chan, val);
			s->पढ़ोback[chan] = val;
		पूर्ण
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक cb_pcidas_ai_check_chanlist(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);

		अगर (chan != (chan0 + i) % s->n_chan) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must be consecutive channels, counting upwards\n");
			वापस -EINVAL;
		पूर्ण

		अगर (range != range0) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must all have the same gain\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cb_pcidas_ai_cmdtest(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा cb_pcidas_board *board = dev->board_ptr;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_FOLLOW | TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (cmd->scan_begin_src == TRIG_FOLLOW && cmd->convert_src == TRIG_NOW)
		err |= -EINVAL;
	अगर (cmd->scan_begin_src != TRIG_FOLLOW && cmd->convert_src != TRIG_NOW)
		err |= -EINVAL;
	अगर (cmd->start_src == TRIG_EXT &&
	    (cmd->convert_src == TRIG_EXT || cmd->scan_begin_src == TRIG_EXT))
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	चयन (cmd->start_src) अणु
	हाल TRIG_NOW:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		अवरोध;
	हाल TRIG_EXT:
		/* External trigger, only CR_EDGE and CR_INVERT flags allowed */
		अगर ((cmd->start_arg
		     & (CR_FLAGS_MASK & ~(CR_EDGE | CR_INVERT))) != 0) अणु
			cmd->start_arg &= ~(CR_FLAGS_MASK &
						~(CR_EDGE | CR_INVERT));
			err |= -EINVAL;
		पूर्ण
		अगर (!board->is_1602 && (cmd->start_arg & CR_INVERT)) अणु
			cmd->start_arg &= (CR_FLAGS_MASK & ~CR_INVERT);
			err |= -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    board->ai_speed *
						    cmd->chanlist_len);
	पूर्ण

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_speed);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		arg = cmd->convert_arg;
		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= cb_pcidas_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक cb_pcidas_ai_cmd(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा cb_pcidas_board *board = dev->board_ptr;
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	अचिन्हित पूर्णांक bits;
	अचिन्हित दीर्घ flags;

	/*  make sure PCIDAS_CALIB_EN is disabled */
	outw(0, devpriv->pcibar1 + PCIDAS_CALIB_REG);
	/*  initialize beक्रमe settings pacer source and count values */
	outw(PCIDAS_TRIG_SEL_NONE, devpriv->pcibar1 + PCIDAS_TRIG_REG);
	/*  clear fअगरo */
	outw(0, devpriv->pcibar2 + PCIDAS_AI_FIFO_CLR_REG);

	/*  set mux limits, gain and pacer source */
	bits = PCIDAS_AI_FIRST(CR_CHAN(cmd->chanlist[0])) |
	       PCIDAS_AI_LAST(CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1])) |
	       PCIDAS_AI_GAIN(range0);
	/*  set unipolar/bipolar */
	अगर (comedi_range_is_unipolar(s, range0))
		bits |= PCIDAS_AI_UNIP;
	/*  set singleended/dअगरferential */
	अगर (CR_AREF(cmd->chanlist[0]) != AREF_DIFF)
		bits |= PCIDAS_AI_SE;
	/*  set pacer source */
	अगर (cmd->convert_src == TRIG_EXT || cmd->scan_begin_src == TRIG_EXT)
		bits |= PCIDAS_AI_PACER_EXTP;
	अन्यथा
		bits |= PCIDAS_AI_PACER_INT;
	outw(bits, devpriv->pcibar1 + PCIDAS_AI_REG);

	/*  load counters */
	अगर (cmd->scan_begin_src == TRIG_TIMER ||
	    cmd->convert_src == TRIG_TIMER) अणु
		comedi_8254_update_भागisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
	पूर्ण

	/*  enable पूर्णांकerrupts */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->ctrl |= PCIDAS_CTRL_INTE;
	devpriv->ctrl &= ~PCIDAS_CTRL_INT_MASK;
	अगर (cmd->flags & CMDF_WAKE_EOS) अणु
		अगर (cmd->convert_src == TRIG_NOW && cmd->chanlist_len > 1) अणु
			/* पूर्णांकerrupt end of burst */
			devpriv->ctrl |= PCIDAS_CTRL_INT_EOS;
		पूर्ण अन्यथा अणु
			/* पूर्णांकerrupt fअगरo not empty */
			devpriv->ctrl |= PCIDAS_CTRL_INT_FNE;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* पूर्णांकerrupt fअगरo half full */
		devpriv->ctrl |= PCIDAS_CTRL_INT_FHF;
	पूर्ण

	/*  enable (and clear) पूर्णांकerrupts */
	outw(devpriv->ctrl |
	     PCIDAS_CTRL_EOAI | PCIDAS_CTRL_INT_CLR | PCIDAS_CTRL_LADFUL,
	     devpriv->pcibar1 + PCIDAS_CTRL_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  set start trigger and burst mode */
	bits = 0;
	अगर (cmd->start_src == TRIG_NOW) अणु
		bits |= PCIDAS_TRIG_SEL_SW;
	पूर्ण अन्यथा अणु	/* TRIG_EXT */
		bits |= PCIDAS_TRIG_SEL_EXT | PCIDAS_TRIG_EN | PCIDAS_TRIG_CLR;
		अगर (board->is_1602) अणु
			अगर (cmd->start_arg & CR_INVERT)
				bits |= PCIDAS_TRIG_POL;
			अगर (cmd->start_arg & CR_EDGE)
				bits |= PCIDAS_TRIG_MODE;
		पूर्ण
	पूर्ण
	अगर (cmd->convert_src == TRIG_NOW && cmd->chanlist_len > 1)
		bits |= PCIDAS_TRIG_BURSTE;
	outw(bits, devpriv->pcibar1 + PCIDAS_TRIG_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक cb_pcidas_ao_check_chanlist(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);

	अगर (cmd->chanlist_len > 1) अणु
		अचिन्हित पूर्णांक chan1 = CR_CHAN(cmd->chanlist[1]);

		अगर (chan0 != 0 || chan1 != 1) अणु
			dev_dbg(dev->class_dev,
				"channels must be ordered channel 0, channel 1 in chanlist\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cb_pcidas_ao_cmdtest(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा cb_pcidas_board *board = dev->board_ptr;
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    board->ao_scan_speed);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		अचिन्हित पूर्णांक arg = cmd->scan_begin_arg;

		comedi_8254_cascade_ns_to_समयr(devpriv->ao_pacer,
						&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= cb_pcidas_ao_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक cb_pcidas_ai_cancel(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	/*  disable पूर्णांकerrupts */
	devpriv->ctrl &= ~(PCIDAS_CTRL_INTE | PCIDAS_CTRL_EOAIE);
	outw(devpriv->ctrl, devpriv->pcibar1 + PCIDAS_CTRL_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  disable start trigger source and burst mode */
	outw(PCIDAS_TRIG_SEL_NONE, devpriv->pcibar1 + PCIDAS_TRIG_REG);
	outw(PCIDAS_AI_PACER_SW, devpriv->pcibar1 + PCIDAS_AI_REG);

	वापस 0;
पूर्ण

अटल व्योम cb_pcidas_ao_load_fअगरo(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक nsamples)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक nbytes;

	nsamples = comedi_nsamples_left(s, nsamples);
	nbytes = comedi_buf_पढ़ो_samples(s, devpriv->ao_buffer, nsamples);

	nsamples = comedi_bytes_to_samples(s, nbytes);
	outsw(devpriv->pcibar4 + PCIDAS_AO_FIFO_REG,
	      devpriv->ao_buffer, nsamples);
पूर्ण

अटल पूर्णांक cb_pcidas_ao_पूर्णांकtrig(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				अचिन्हित पूर्णांक trig_num)
अणु
	स्थिर काष्ठा cb_pcidas_board *board = dev->board_ptr;
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित दीर्घ flags;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	cb_pcidas_ao_load_fअगरo(dev, s, board->fअगरo_size);

	/*  enable dac half-full and empty पूर्णांकerrupts */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->ctrl |= PCIDAS_CTRL_DAEMIE | PCIDAS_CTRL_DAHFIE;

	/*  enable and clear पूर्णांकerrupts */
	outw(devpriv->ctrl | PCIDAS_CTRL_DAEMI | PCIDAS_CTRL_DAHFI,
	     devpriv->pcibar1 + PCIDAS_CTRL_REG);

	/*  start dac */
	devpriv->ao_ctrl |= PCIDAS_AO_START | PCIDAS_AO_DACEN | PCIDAS_AO_EMPTY;
	outw(devpriv->ao_ctrl, devpriv->pcibar1 + PCIDAS_AO_REG);

	spin_unlock_irqrestore(&dev->spinlock, flags);

	async->पूर्णांकtrig = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक cb_pcidas_ao_cmd(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	/*  set channel limits, gain */
	spin_lock_irqsave(&dev->spinlock, flags);
	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);

		/*  enable channel */
		devpriv->ao_ctrl |= PCIDAS_AO_CHAN_EN(chan);
		/*  set range */
		devpriv->ao_ctrl |= PCIDAS_AO_RANGE(chan, range);
	पूर्ण

	/*  disable analog out beक्रमe settings pacer source and count values */
	outw(devpriv->ao_ctrl, devpriv->pcibar1 + PCIDAS_AO_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  clear fअगरo */
	outw(0, devpriv->pcibar4 + PCIDAS_AO_FIFO_CLR_REG);

	/*  load counters */
	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		comedi_8254_update_भागisors(devpriv->ao_pacer);
		comedi_8254_pacer_enable(devpriv->ao_pacer, 1, 2, true);
	पूर्ण

	/*  set pacer source */
	spin_lock_irqsave(&dev->spinlock, flags);
	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_TIMER:
		devpriv->ao_ctrl |= PCIDAS_AO_PACER_INT;
		अवरोध;
	हाल TRIG_EXT:
		devpriv->ao_ctrl |= PCIDAS_AO_PACER_EXTP;
		अवरोध;
	शेष:
		spin_unlock_irqrestore(&dev->spinlock, flags);
		dev_err(dev->class_dev, "error setting dac pacer source\n");
		वापस -1;
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);

	async->पूर्णांकtrig = cb_pcidas_ao_पूर्णांकtrig;

	वापस 0;
पूर्ण

अटल पूर्णांक cb_pcidas_ao_cancel(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	/*  disable पूर्णांकerrupts */
	devpriv->ctrl &= ~(PCIDAS_CTRL_DAHFIE | PCIDAS_CTRL_DAEMIE);
	outw(devpriv->ctrl, devpriv->pcibar1 + PCIDAS_CTRL_REG);

	/*  disable output */
	devpriv->ao_ctrl &= ~(PCIDAS_AO_DACEN | PCIDAS_AO_PACER_MASK);
	outw(devpriv->ao_ctrl, devpriv->pcibar1 + PCIDAS_AO_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक cb_pcidas_ao_पूर्णांकerrupt(काष्ठा comedi_device *dev,
					   अचिन्हित पूर्णांक status)
अणु
	स्थिर काष्ठा cb_pcidas_board *board = dev->board_ptr;
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->ग_लिखो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक irq_clr = 0;

	अगर (status & PCIDAS_CTRL_DAEMI) अणु
		irq_clr |= PCIDAS_CTRL_DAEMI;

		अगर (inw(devpriv->pcibar4 + PCIDAS_AO_REG) & PCIDAS_AO_EMPTY) अणु
			अगर (cmd->stop_src == TRIG_COUNT &&
			    async->scans_करोne >= cmd->stop_arg) अणु
				async->events |= COMEDI_CB_EOA;
			पूर्ण अन्यथा अणु
				dev_err(dev->class_dev, "dac fifo underflow\n");
				async->events |= COMEDI_CB_ERROR;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (status & PCIDAS_CTRL_DAHFI) अणु
		irq_clr |= PCIDAS_CTRL_DAHFI;

		cb_pcidas_ao_load_fअगरo(dev, s, board->fअगरo_size / 2);
	पूर्ण

	comedi_handle_events(dev, s);

	वापस irq_clr;
पूर्ण

अटल अचिन्हित पूर्णांक cb_pcidas_ai_पूर्णांकerrupt(काष्ठा comedi_device *dev,
					   अचिन्हित पूर्णांक status)
अणु
	स्थिर काष्ठा cb_pcidas_board *board = dev->board_ptr;
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक irq_clr = 0;

	अगर (status & PCIDAS_CTRL_ADHFI) अणु
		अचिन्हित पूर्णांक num_samples;

		irq_clr |= PCIDAS_CTRL_INT_CLR;

		/* FIFO is half-full - पढ़ो data */
		num_samples = comedi_nsamples_left(s, board->fअगरo_size / 2);
		insw(devpriv->pcibar2 + PCIDAS_AI_DATA_REG,
		     devpriv->ai_buffer, num_samples);
		comedi_buf_ग_लिखो_samples(s, devpriv->ai_buffer, num_samples);

		अगर (cmd->stop_src == TRIG_COUNT &&
		    async->scans_करोne >= cmd->stop_arg)
			async->events |= COMEDI_CB_EOA;
	पूर्ण अन्यथा अगर (status & (PCIDAS_CTRL_ADNEI | PCIDAS_CTRL_EOBI)) अणु
		अचिन्हित पूर्णांक i;

		irq_clr |= PCIDAS_CTRL_INT_CLR;

		/* FIFO is not empty - पढ़ो data until empty or समयoout */
		क्रम (i = 0; i < 10000; i++) अणु
			अचिन्हित लघु val;

			/*  अवरोध अगर fअगरo is empty */
			अगर ((inw(devpriv->pcibar1 + PCIDAS_CTRL_REG) &
			    PCIDAS_CTRL_ADNE) == 0)
				अवरोध;
			val = inw(devpriv->pcibar2 + PCIDAS_AI_DATA_REG);
			comedi_buf_ग_लिखो_samples(s, &val, 1);

			अगर (cmd->stop_src == TRIG_COUNT &&
			    async->scans_करोne >= cmd->stop_arg) अणु
				async->events |= COMEDI_CB_EOA;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (status & PCIDAS_CTRL_EOAI) अणु
		irq_clr |= PCIDAS_CTRL_EOAI;

		dev_err(dev->class_dev,
			"bug! encountered end of acquisition interrupt?\n");
	पूर्ण

	/* check क्रम fअगरo overflow */
	अगर (status & PCIDAS_CTRL_LADFUL) अणु
		irq_clr |= PCIDAS_CTRL_LADFUL;

		dev_err(dev->class_dev, "fifo overflow\n");
		async->events |= COMEDI_CB_ERROR;
	पूर्ण

	comedi_handle_events(dev, s);

	वापस irq_clr;
पूर्ण

अटल irqवापस_t cb_pcidas_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक irq_clr = 0;
	अचिन्हित पूर्णांक amcc_status;
	अचिन्हित पूर्णांक status;

	अगर (!dev->attached)
		वापस IRQ_NONE;

	amcc_status = inl(devpriv->amcc + AMCC_OP_REG_INTCSR);

	अगर ((INTCSR_INTR_ASSERTED & amcc_status) == 0)
		वापस IRQ_NONE;

	/*  make sure mailbox 4 is empty */
	inl_p(devpriv->amcc + AMCC_OP_REG_IMB4);
	/*  clear पूर्णांकerrupt on amcc s5933 */
	outl(devpriv->amcc_पूर्णांकcsr | INTCSR_INBOX_INTR_STATUS,
	     devpriv->amcc + AMCC_OP_REG_INTCSR);

	status = inw(devpriv->pcibar1 + PCIDAS_CTRL_REG);

	/* handle analog output पूर्णांकerrupts */
	अगर (status & PCIDAS_CTRL_AO_INT)
		irq_clr |= cb_pcidas_ao_पूर्णांकerrupt(dev, status);

	/* handle analog input पूर्णांकerrupts */
	अगर (status & PCIDAS_CTRL_AI_INT)
		irq_clr |= cb_pcidas_ai_पूर्णांकerrupt(dev, status);

	अगर (irq_clr) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dev->spinlock, flags);
		outw(devpriv->ctrl | irq_clr,
		     devpriv->pcibar1 + PCIDAS_CTRL_REG);
		spin_unlock_irqrestore(&dev->spinlock, flags);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cb_pcidas_स्वतः_attach(काष्ठा comedi_device *dev,
				 अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा cb_pcidas_board *board = शून्य;
	काष्ठा cb_pcidas_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(cb_pcidas_boards))
		board = &cb_pcidas_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr  = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	devpriv->amcc = pci_resource_start(pcidev, 0);
	devpriv->pcibar1 = pci_resource_start(pcidev, 1);
	devpriv->pcibar2 = pci_resource_start(pcidev, 2);
	dev->iobase = pci_resource_start(pcidev, 3);
	अगर (board->has_ao)
		devpriv->pcibar4 = pci_resource_start(pcidev, 4);

	/*  disable and clear पूर्णांकerrupts on amcc s5933 */
	outl(INTCSR_INBOX_INTR_STATUS,
	     devpriv->amcc + AMCC_OP_REG_INTCSR);

	ret = request_irq(pcidev->irq, cb_pcidas_पूर्णांकerrupt, IRQF_SHARED,
			  "cb_pcidas", dev);
	अगर (ret) अणु
		dev_dbg(dev->class_dev, "unable to allocate irq %d\n",
			pcidev->irq);
		वापस ret;
	पूर्ण
	dev->irq = pcidev->irq;

	dev->pacer = comedi_8254_init(dev->iobase + PCIDAS_AI_8254_BASE,
				      I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	devpriv->ao_pacer = comedi_8254_init(dev->iobase + PCIDAS_AO_8254_BASE,
					     I8254_OSC_BASE_10MHZ,
					     I8254_IO8, 0);
	अगर (!devpriv->ao_pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 7);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= board->is_16bit ? 0xffff : 0x0fff;
	s->range_table	= board->use_alt_range ? &cb_pcidas_alt_ranges
					       : &cb_pcidas_ranges;
	s->insn_पढ़ो	= cb_pcidas_ai_insn_पढ़ो;
	s->insn_config	= cb_pcidas_ai_insn_config;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->करो_cmd	= cb_pcidas_ai_cmd;
		s->करो_cmdtest	= cb_pcidas_ai_cmdtest;
		s->cancel	= cb_pcidas_ai_cancel;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_GROUND;
		s->n_chan	= 2;
		s->maxdata	= board->is_16bit ? 0xffff : 0x0fff;
		s->range_table	= &cb_pcidas_ao_ranges;
		s->insn_ग_लिखो	= (board->has_ao_fअगरo)
					? cb_pcidas_ao_fअगरo_insn_ग_लिखो
					: cb_pcidas_ao_nofअगरo_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		अगर (dev->irq && board->has_ao_fअगरo) अणु
			dev->ग_लिखो_subdev = s;
			s->subdev_flags	|= SDF_CMD_WRITE;
			s->len_chanlist	= s->n_chan;
			s->करो_cmdtest	= cb_pcidas_ao_cmdtest;
			s->करो_cmd	= cb_pcidas_ao_cmd;
			s->cancel	= cb_pcidas_ao_cancel;
		पूर्ण
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* 8255 */
	s = &dev->subdevices[2];
	ret = subdev_8255_init(dev, s, शून्य, PCIDAS_8255_BASE);
	अगर (ret)
		वापस ret;

	/* Memory subdevice - serial EEPROM */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_MEMORY;
	s->subdev_flags	= SDF_READABLE | SDF_INTERNAL;
	s->n_chan	= 256;
	s->maxdata	= 0xff;
	s->insn_पढ़ो	= cb_pcidas_eeprom_insn_पढ़ो;

	/* Calibration subdevice - 8800 caldac */
	s = &dev->subdevices[4];
	s->type		= COMEDI_SUBD_CALIB;
	s->subdev_flags	= SDF_WRITABLE | SDF_INTERNAL;
	s->n_chan	= 8;
	s->maxdata	= 0xff;
	s->insn_ग_लिखो	= cb_pcidas_caldac_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < s->n_chan; i++) अणु
		अचिन्हित पूर्णांक val = s->maxdata / 2;

		/* ग_लिखो 11-bit channel/value to caldac */
		cb_pcidas_calib_ग_लिखो(dev, (i << 8) | val, 11, false);
		s->पढ़ोback[i] = val;
	पूर्ण

	/* Calibration subdevice - trim potentiometer */
	s = &dev->subdevices[5];
	s->type		= COMEDI_SUBD_CALIB;
	s->subdev_flags	= SDF_WRITABLE | SDF_INTERNAL;
	अगर (board->has_ad8402) अणु
		/*
		 * pci-das1602/16 have an AD8402 trimpot:
		 *   chan 0 : adc gain
		 *   chan 1 : adc postgain offset
		 */
		s->n_chan	= 2;
		s->maxdata	= 0xff;
	पूर्ण अन्यथा अणु
		/* all other boards have an AD7376 trimpot */
		s->n_chan	= 1;
		s->maxdata	= 0x7f;
	पूर्ण
	s->insn_ग_लिखो	= cb_pcidas_trimpot_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < s->n_chan; i++) अणु
		cb_pcidas_trimpot_ग_लिखो(dev, i, s->maxdata / 2);
		s->पढ़ोback[i] = s->maxdata / 2;
	पूर्ण

	/* Calibration subdevice - pci-das1602/16 pregain offset (dac08) */
	s = &dev->subdevices[6];
	अगर (board->has_dac08) अणु
		s->type		= COMEDI_SUBD_CALIB;
		s->subdev_flags	= SDF_WRITABLE | SDF_INTERNAL;
		s->n_chan	= 1;
		s->maxdata	= 0xff;
		s->insn_ग_लिखो	= cb_pcidas_dac08_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < s->n_chan; i++) अणु
			cb_pcidas_dac08_ग_लिखो(dev, s->maxdata / 2);
			s->पढ़ोback[i] = s->maxdata / 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/*  make sure mailbox 4 is empty */
	inl(devpriv->amcc + AMCC_OP_REG_IMB4);
	/* Set bits to enable incoming mailbox पूर्णांकerrupts on amcc s5933. */
	devpriv->amcc_पूर्णांकcsr = INTCSR_INBOX_BYTE(3) | INTCSR_INBOX_SELECT(3) |
			       INTCSR_INBOX_FULL_INT;
	/*  clear and enable पूर्णांकerrupt on amcc s5933 */
	outl(devpriv->amcc_पूर्णांकcsr | INTCSR_INBOX_INTR_STATUS,
	     devpriv->amcc + AMCC_OP_REG_INTCSR);

	वापस 0;
पूर्ण

अटल व्योम cb_pcidas_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा cb_pcidas_निजी *devpriv = dev->निजी;

	अगर (devpriv) अणु
		अगर (devpriv->amcc)
			outl(INTCSR_INBOX_INTR_STATUS,
			     devpriv->amcc + AMCC_OP_REG_INTCSR);
		kमुक्त(devpriv->ao_pacer);
	पूर्ण
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver cb_pcidas_driver = अणु
	.driver_name	= "cb_pcidas",
	.module		= THIS_MODULE,
	.स्वतः_attach	= cb_pcidas_स्वतः_attach,
	.detach		= cb_pcidas_detach,
पूर्ण;

अटल पूर्णांक cb_pcidas_pci_probe(काष्ठा pci_dev *dev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &cb_pcidas_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cb_pcidas_pci_table[] = अणु
	अणु PCI_VDEVICE(CB, 0x0001), BOARD_PCIDAS1602_16 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x000f), BOARD_PCIDAS1200 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0010), BOARD_PCIDAS1602_12 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0019), BOARD_PCIDAS1200_JR पूर्ण,
	अणु PCI_VDEVICE(CB, 0x001c), BOARD_PCIDAS1602_16_JR पूर्ण,
	अणु PCI_VDEVICE(CB, 0x004c), BOARD_PCIDAS1000 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x001a), BOARD_PCIDAS1001 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x001b), BOARD_PCIDAS1002 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cb_pcidas_pci_table);

अटल काष्ठा pci_driver cb_pcidas_pci_driver = अणु
	.name		= "cb_pcidas",
	.id_table	= cb_pcidas_pci_table,
	.probe		= cb_pcidas_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(cb_pcidas_driver, cb_pcidas_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for MeasurementComputing PCI-DAS series");
MODULE_LICENSE("GPL");
