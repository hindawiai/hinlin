<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the ADC present in the Aपंचांगel AT91 evaluation boards.
 *
 * Copyright 2011 Free Electrons
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/pinctrl/consumer.h>

/* Registers */
#घोषणा AT91_ADC_CR		0x00		/* Control Register */
#घोषणा		AT91_ADC_SWRST		(1 << 0)	/* Software Reset */
#घोषणा		AT91_ADC_START		(1 << 1)	/* Start Conversion */

#घोषणा AT91_ADC_MR		0x04		/* Mode Register */
#घोषणा		AT91_ADC_TSAMOD		(3 << 0)	/* ADC mode */
#घोषणा		AT91_ADC_TSAMOD_ADC_ONLY_MODE		(0 << 0)	/* ADC Mode */
#घोषणा		AT91_ADC_TSAMOD_TS_ONLY_MODE		(1 << 0)	/* Touch Screen Only Mode */
#घोषणा		AT91_ADC_TRGEN		(1 << 0)	/* Trigger Enable */
#घोषणा		AT91_ADC_TRGSEL		(7 << 1)	/* Trigger Selection */
#घोषणा			AT91_ADC_TRGSEL_TC0		(0 << 1)
#घोषणा			AT91_ADC_TRGSEL_TC1		(1 << 1)
#घोषणा			AT91_ADC_TRGSEL_TC2		(2 << 1)
#घोषणा			AT91_ADC_TRGSEL_EXTERNAL	(6 << 1)
#घोषणा		AT91_ADC_LOWRES		(1 << 4)	/* Low Resolution */
#घोषणा		AT91_ADC_SLEEP		(1 << 5)	/* Sleep Mode */
#घोषणा		AT91_ADC_PENDET		(1 << 6)	/* Pen contact detection enable */
#घोषणा		AT91_ADC_PRESCAL_9260	(0x3f << 8)	/* Prescalar Rate Selection */
#घोषणा		AT91_ADC_PRESCAL_9G45	(0xff << 8)
#घोषणा			AT91_ADC_PRESCAL_(x)	((x) << 8)
#घोषणा		AT91_ADC_STARTUP_9260	(0x1f << 16)	/* Startup Up Time */
#घोषणा		AT91_ADC_STARTUP_9G45	(0x7f << 16)
#घोषणा		AT91_ADC_STARTUP_9X5	(0xf << 16)
#घोषणा			AT91_ADC_STARTUP_(x)	((x) << 16)
#घोषणा		AT91_ADC_SHTIM		(0xf  << 24)	/* Sample & Hold Time */
#घोषणा			AT91_ADC_SHTIM_(x)	((x) << 24)
#घोषणा		AT91_ADC_PENDBC		(0x0f << 28)	/* Pen Debounce समय */
#घोषणा			AT91_ADC_PENDBC_(x)	((x) << 28)

#घोषणा AT91_ADC_TSR		0x0C
#घोषणा		AT91_ADC_TSR_SHTIM	(0xf  << 24)	/* Sample & Hold Time */
#घोषणा			AT91_ADC_TSR_SHTIM_(x)	((x) << 24)

#घोषणा AT91_ADC_CHER		0x10		/* Channel Enable Register */
#घोषणा AT91_ADC_CHDR		0x14		/* Channel Disable Register */
#घोषणा AT91_ADC_CHSR		0x18		/* Channel Status Register */
#घोषणा		AT91_ADC_CH(n)		(1 << (n))	/* Channel Number */

#घोषणा AT91_ADC_SR		0x1C		/* Status Register */
#घोषणा		AT91_ADC_EOC(n)		(1 << (n))	/* End of Conversion on Channel N */
#घोषणा		AT91_ADC_OVRE(n)	(1 << ((n) + 8))/* Overrun Error on Channel N */
#घोषणा		AT91_ADC_DRDY		(1 << 16)	/* Data Ready */
#घोषणा		AT91_ADC_GOVRE		(1 << 17)	/* General Overrun Error */
#घोषणा		AT91_ADC_ENDRX		(1 << 18)	/* End of RX Buffer */
#घोषणा		AT91_ADC_RXFUFF		(1 << 19)	/* RX Buffer Full */

#घोषणा AT91_ADC_SR_9X5		0x30		/* Status Register क्रम 9x5 */
#घोषणा		AT91_ADC_SR_DRDY_9X5	(1 << 24)	/* Data Ready */

#घोषणा AT91_ADC_LCDR		0x20		/* Last Converted Data Register */
#घोषणा		AT91_ADC_LDATA		(0x3ff)

#घोषणा AT91_ADC_IER		0x24		/* Interrupt Enable Register */
#घोषणा AT91_ADC_IDR		0x28		/* Interrupt Disable Register */
#घोषणा AT91_ADC_IMR		0x2C		/* Interrupt Mask Register */
#घोषणा		AT91RL_ADC_IER_PEN	(1 << 20)
#घोषणा		AT91RL_ADC_IER_NOPEN	(1 << 21)
#घोषणा		AT91_ADC_IER_PEN	(1 << 29)
#घोषणा		AT91_ADC_IER_NOPEN	(1 << 30)
#घोषणा		AT91_ADC_IER_XRDY	(1 << 20)
#घोषणा		AT91_ADC_IER_YRDY	(1 << 21)
#घोषणा		AT91_ADC_IER_PRDY	(1 << 22)
#घोषणा		AT91_ADC_ISR_PENS	(1 << 31)

#घोषणा AT91_ADC_CHR(n)		(0x30 + ((n) * 4))	/* Channel Data Register N */
#घोषणा		AT91_ADC_DATA		(0x3ff)

#घोषणा AT91_ADC_CDR0_9X5	(0x50)			/* Channel Data Register 0 क्रम 9X5 */

#घोषणा AT91_ADC_ACR		0x94	/* Analog Control Register */
#घोषणा		AT91_ADC_ACR_PENDETSENS	(0x3 << 0)	/* pull-up resistor */

#घोषणा AT91_ADC_TSMR		0xB0
#घोषणा		AT91_ADC_TSMR_TSMODE	(3 << 0)	/* Touch Screen Mode */
#घोषणा			AT91_ADC_TSMR_TSMODE_NONE		(0 << 0)
#घोषणा			AT91_ADC_TSMR_TSMODE_4WIRE_NO_PRESS	(1 << 0)
#घोषणा			AT91_ADC_TSMR_TSMODE_4WIRE_PRESS	(2 << 0)
#घोषणा			AT91_ADC_TSMR_TSMODE_5WIRE		(3 << 0)
#घोषणा		AT91_ADC_TSMR_TSAV	(3 << 4)	/* Averages samples */
#घोषणा			AT91_ADC_TSMR_TSAV_(x)		((x) << 4)
#घोषणा		AT91_ADC_TSMR_SCTIM	(0x0f << 16)	/* Switch closure समय */
#घोषणा			AT91_ADC_TSMR_SCTIM_(x)		((x) << 16)
#घोषणा		AT91_ADC_TSMR_PENDBC	(0x0f << 28)	/* Pen Debounce समय */
#घोषणा			AT91_ADC_TSMR_PENDBC_(x)	((x) << 28)
#घोषणा		AT91_ADC_TSMR_NOTSDMA	(1 << 22)	/* No Touchscreen DMA */
#घोषणा		AT91_ADC_TSMR_PENDET_DIS	(0 << 24)	/* Pen contact detection disable */
#घोषणा		AT91_ADC_TSMR_PENDET_ENA	(1 << 24)	/* Pen contact detection enable */

#घोषणा AT91_ADC_TSXPOSR	0xB4
#घोषणा AT91_ADC_TSYPOSR	0xB8
#घोषणा AT91_ADC_TSPRESSR	0xBC

#घोषणा AT91_ADC_TRGR_9260	AT91_ADC_MR
#घोषणा AT91_ADC_TRGR_9G45	0x08
#घोषणा AT91_ADC_TRGR_9X5	0xC0

/* Trigger Register bit field */
#घोषणा		AT91_ADC_TRGR_TRGPER	(0xffff << 16)
#घोषणा			AT91_ADC_TRGR_TRGPER_(x)	((x) << 16)
#घोषणा		AT91_ADC_TRGR_TRGMOD	(0x7 << 0)
#घोषणा			AT91_ADC_TRGR_NONE		(0 << 0)
#घोषणा			AT91_ADC_TRGR_MOD_PERIOD_TRIG	(5 << 0)

#घोषणा AT91_ADC_CHAN(st, ch) \
	(st->रेजिस्टरs->channel_base + (ch * 4))
#घोषणा at91_adc_पढ़ोl(st, reg) \
	(पढ़ोl_relaxed(st->reg_base + reg))
#घोषणा at91_adc_ग_लिखोl(st, reg, val) \
	(ग_लिखोl_relaxed(val, st->reg_base + reg))

#घोषणा DRIVER_NAME		"at91_adc"
#घोषणा MAX_POS_BITS		12

#घोषणा TOUCH_SAMPLE_PERIOD_US		2000	/* 2ms */
#घोषणा TOUCH_PEN_DETECT_DEBOUNCE_US	200

#घोषणा MAX_RLPOS_BITS         10
#घोषणा TOUCH_SAMPLE_PERIOD_US_RL      10000   /* 10ms, the SoC can't keep up with 2ms */
#घोषणा TOUCH_SHTIM                    0xa
#घोषणा TOUCH_SCTIM_US		10		/* 10us क्रम the Touchscreen Switches Closure Time */

क्रमागत aपंचांगel_adc_ts_type अणु
	ATMEL_ADC_TOUCHSCREEN_NONE = 0,
	ATMEL_ADC_TOUCHSCREEN_4WIRE = 4,
	ATMEL_ADC_TOUCHSCREEN_5WIRE = 5,
पूर्ण;

/**
 * काष्ठा at91_adc_trigger - description of triggers
 * @name:		name of the trigger advertised to the user
 * @value:		value to set in the ADC's trigger setup रेजिस्टर
 *			to enable the trigger
 * @is_बाह्यal:	Does the trigger rely on an बाह्यal pin?
 */
काष्ठा at91_adc_trigger अणु
	स्थिर अक्षर	*name;
	u8		value;
	bool		is_बाह्यal;
पूर्ण;

/**
 * काष्ठा at91_adc_reg_desc - Various inक्रमmations relative to रेजिस्टरs
 * @channel_base:	Base offset क्रम the channel data रेजिस्टरs
 * @drdy_mask:		Mask of the DRDY field in the relevant रेजिस्टरs
 *			(Interruptions रेजिस्टरs mostly)
 * @status_रेजिस्टर:	Offset of the Interrupt Status Register
 * @trigger_रेजिस्टर:	Offset of the Trigger setup रेजिस्टर
 * @mr_prescal_mask:	Mask of the PRESCAL field in the adc MR रेजिस्टर
 * @mr_startup_mask:	Mask of the STARTUP field in the adc MR रेजिस्टर
 */
काष्ठा at91_adc_reg_desc अणु
	u8	channel_base;
	u32	drdy_mask;
	u8	status_रेजिस्टर;
	u8	trigger_रेजिस्टर;
	u32	mr_prescal_mask;
	u32	mr_startup_mask;
पूर्ण;

काष्ठा at91_adc_caps अणु
	bool	has_ts;		/* Support touch screen */
	bool	has_tsmr;	/* only at91sam9x5, sama5d3 have TSMR reg */
	/*
	 * Numbers of sampling data will be averaged. Can be 0~3.
	 * Hardware can average (2 ^ ts_filter_average) sample data.
	 */
	u8	ts_filter_average;
	/* Pen Detection input pull-up resistor, can be 0~3 */
	u8	ts_pen_detect_sensitivity;

	/* startup समय calculate function */
	u32 (*calc_startup_ticks)(u32 startup_समय, u32 adc_clk_khz);

	u8	num_channels;

	u8	low_res_bits;
	u8	high_res_bits;
	u32	trigger_number;
	स्थिर काष्ठा at91_adc_trigger *triggers;
	काष्ठा at91_adc_reg_desc रेजिस्टरs;
पूर्ण;

काष्ठा at91_adc_state अणु
	काष्ठा clk		*adc_clk;
	u16			*buffer;
	अचिन्हित दीर्घ		channels_mask;
	काष्ठा clk		*clk;
	bool			करोne;
	पूर्णांक			irq;
	u16			last_value;
	पूर्णांक			chnb;
	काष्ठा mutex		lock;
	u8			num_channels;
	व्योम __iomem		*reg_base;
	स्थिर काष्ठा at91_adc_reg_desc *रेजिस्टरs;
	u32			startup_समय;
	u8			sample_hold_समय;
	bool			sleep_mode;
	काष्ठा iio_trigger	**trig;
	bool			use_बाह्यal;
	u32			vref_mv;
	u32			res;		/* resolution used क्रम convertions */
	रुको_queue_head_t	wq_data_avail;
	स्थिर काष्ठा at91_adc_caps	*caps;

	/*
	 * Following ADC channels are shared by touchscreen:
	 *
	 * CH0 -- Touch screen XP/UL
	 * CH1 -- Touch screen XM/UR
	 * CH2 -- Touch screen YP/LL
	 * CH3 -- Touch screen YM/Sense
	 * CH4 -- Touch screen LR(5-wire only)
	 *
	 * The bitfields below represents the reserved channel in the
	 * touchscreen mode.
	 */
#घोषणा CHAN_MASK_TOUCHSCREEN_4WIRE	(0xf << 0)
#घोषणा CHAN_MASK_TOUCHSCREEN_5WIRE	(0x1f << 0)
	क्रमागत aपंचांगel_adc_ts_type	touchscreen_type;
	काष्ठा input_dev	*ts_input;

	u16			ts_sample_period_val;
	u32			ts_pressure_threshold;
	u16			ts_pendbc;

	bool			ts_bufferedmeasure;
	u32			ts_prev_असलx;
	u32			ts_prev_असलy;
पूर्ण;

अटल irqवापस_t at91_adc_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *idev = pf->indio_dev;
	काष्ठा at91_adc_state *st = iio_priv(idev);
	काष्ठा iio_chan_spec स्थिर *chan;
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < idev->masklength; i++) अणु
		अगर (!test_bit(i, idev->active_scan_mask))
			जारी;
		chan = idev->channels + i;
		st->buffer[j] = at91_adc_पढ़ोl(st, AT91_ADC_CHAN(st, chan->channel));
		j++;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(idev, st->buffer, pf->बारtamp);

	iio_trigger_notअगरy_करोne(idev->trig);

	/* Needed to ACK the DRDY पूर्णांकerruption */
	at91_adc_पढ़ोl(st, AT91_ADC_LCDR);

	enable_irq(st->irq);

	वापस IRQ_HANDLED;
पूर्ण

/* Handler क्रम classic adc channel eoc trigger */
अटल व्योम handle_adc_eoc_trigger(पूर्णांक irq, काष्ठा iio_dev *idev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(idev);

	अगर (iio_buffer_enabled(idev)) अणु
		disable_irq_nosync(irq);
		iio_trigger_poll(idev->trig);
	पूर्ण अन्यथा अणु
		st->last_value = at91_adc_पढ़ोl(st, AT91_ADC_CHAN(st, st->chnb));
		/* Needed to ACK the DRDY पूर्णांकerruption */
		at91_adc_पढ़ोl(st, AT91_ADC_LCDR);
		st->करोne = true;
		wake_up_पूर्णांकerruptible(&st->wq_data_avail);
	पूर्ण
पूर्ण

अटल पूर्णांक at91_ts_sample(काष्ठा iio_dev *idev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(idev);
	अचिन्हित पूर्णांक xscale, yscale, reg, z1, z2;
	अचिन्हित पूर्णांक x, y, pres, xpos, ypos;
	अचिन्हित पूर्णांक rxp = 1;
	अचिन्हित पूर्णांक factor = 1000;

	अचिन्हित पूर्णांक xyz_mask_bits = st->res;
	अचिन्हित पूर्णांक xyz_mask = (1 << xyz_mask_bits) - 1;

	/* calculate position */
	/* x position = (x / xscale) * max, max = 2^MAX_POS_BITS - 1 */
	reg = at91_adc_पढ़ोl(st, AT91_ADC_TSXPOSR);
	xpos = reg & xyz_mask;
	x = (xpos << MAX_POS_BITS) - xpos;
	xscale = (reg >> 16) & xyz_mask;
	अगर (xscale == 0) अणु
		dev_err(&idev->dev, "Error: xscale == 0!\n");
		वापस -1;
	पूर्ण
	x /= xscale;

	/* y position = (y / yscale) * max, max = 2^MAX_POS_BITS - 1 */
	reg = at91_adc_पढ़ोl(st, AT91_ADC_TSYPOSR);
	ypos = reg & xyz_mask;
	y = (ypos << MAX_POS_BITS) - ypos;
	yscale = (reg >> 16) & xyz_mask;
	अगर (yscale == 0) अणु
		dev_err(&idev->dev, "Error: yscale == 0!\n");
		वापस -1;
	पूर्ण
	y /= yscale;

	/* calculate the pressure */
	reg = at91_adc_पढ़ोl(st, AT91_ADC_TSPRESSR);
	z1 = reg & xyz_mask;
	z2 = (reg >> 16) & xyz_mask;

	अगर (z1 != 0)
		pres = rxp * (x * factor / 1024) * (z2 * factor / z1 - factor)
			/ factor;
	अन्यथा
		pres = st->ts_pressure_threshold;	/* no pen contacted */

	dev_dbg(&idev->dev, "xpos = %d, xscale = %d, ypos = %d, yscale = %d, z1 = %d, z2 = %d, press = %d\n",
				xpos, xscale, ypos, yscale, z1, z2, pres);

	अगर (pres < st->ts_pressure_threshold) अणु
		dev_dbg(&idev->dev, "x = %d, y = %d, pressure = %d\n",
					x, y, pres / factor);
		input_report_असल(st->ts_input, ABS_X, x);
		input_report_असल(st->ts_input, ABS_Y, y);
		input_report_असल(st->ts_input, ABS_PRESSURE, pres);
		input_report_key(st->ts_input, BTN_TOUCH, 1);
		input_sync(st->ts_input);
	पूर्ण अन्यथा अणु
		dev_dbg(&idev->dev, "pressure too low: not reporting\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t at91_adc_rl_पूर्णांकerrupt(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *idev = निजी;
	काष्ठा at91_adc_state *st = iio_priv(idev);
	u32 status = at91_adc_पढ़ोl(st, st->रेजिस्टरs->status_रेजिस्टर);
	अचिन्हित पूर्णांक reg;

	status &= at91_adc_पढ़ोl(st, AT91_ADC_IMR);
	अगर (status & GENMASK(st->num_channels - 1, 0))
		handle_adc_eoc_trigger(irq, idev);

	अगर (status & AT91RL_ADC_IER_PEN) अणु
		/* Disabling pen debounce is required to get a NOPEN irq */
		reg = at91_adc_पढ़ोl(st, AT91_ADC_MR);
		reg &= ~AT91_ADC_PENDBC;
		at91_adc_ग_लिखोl(st, AT91_ADC_MR, reg);

		at91_adc_ग_लिखोl(st, AT91_ADC_IDR, AT91RL_ADC_IER_PEN);
		at91_adc_ग_लिखोl(st, AT91_ADC_IER, AT91RL_ADC_IER_NOPEN
				| AT91_ADC_EOC(3));
		/* Set up period trigger क्रम sampling */
		at91_adc_ग_लिखोl(st, st->रेजिस्टरs->trigger_रेजिस्टर,
			AT91_ADC_TRGR_MOD_PERIOD_TRIG |
			AT91_ADC_TRGR_TRGPER_(st->ts_sample_period_val));
	पूर्ण अन्यथा अगर (status & AT91RL_ADC_IER_NOPEN) अणु
		reg = at91_adc_पढ़ोl(st, AT91_ADC_MR);
		reg |= AT91_ADC_PENDBC_(st->ts_pendbc) & AT91_ADC_PENDBC;
		at91_adc_ग_लिखोl(st, AT91_ADC_MR, reg);
		at91_adc_ग_लिखोl(st, st->रेजिस्टरs->trigger_रेजिस्टर,
			AT91_ADC_TRGR_NONE);

		at91_adc_ग_लिखोl(st, AT91_ADC_IDR, AT91RL_ADC_IER_NOPEN
				| AT91_ADC_EOC(3));
		at91_adc_ग_लिखोl(st, AT91_ADC_IER, AT91RL_ADC_IER_PEN);
		st->ts_bufferedmeasure = false;
		input_report_key(st->ts_input, BTN_TOUCH, 0);
		input_sync(st->ts_input);
	पूर्ण अन्यथा अगर (status & AT91_ADC_EOC(3) && st->ts_input) अणु
		/* Conversion finished and we've a touchscreen */
		अगर (st->ts_bufferedmeasure) अणु
			/*
			 * Last measurement is always discarded, since it can
			 * be erroneous.
			 * Always report previous measurement
			 */
			input_report_असल(st->ts_input, ABS_X, st->ts_prev_असलx);
			input_report_असल(st->ts_input, ABS_Y, st->ts_prev_असलy);
			input_report_key(st->ts_input, BTN_TOUCH, 1);
			input_sync(st->ts_input);
		पूर्ण अन्यथा
			st->ts_bufferedmeasure = true;

		/* Now make new measurement */
		st->ts_prev_असलx = at91_adc_पढ़ोl(st, AT91_ADC_CHAN(st, 3))
				   << MAX_RLPOS_BITS;
		st->ts_prev_असलx /= at91_adc_पढ़ोl(st, AT91_ADC_CHAN(st, 2));

		st->ts_prev_असलy = at91_adc_पढ़ोl(st, AT91_ADC_CHAN(st, 1))
				   << MAX_RLPOS_BITS;
		st->ts_prev_असलy /= at91_adc_पढ़ोl(st, AT91_ADC_CHAN(st, 0));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t at91_adc_9x5_पूर्णांकerrupt(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *idev = निजी;
	काष्ठा at91_adc_state *st = iio_priv(idev);
	u32 status = at91_adc_पढ़ोl(st, st->रेजिस्टरs->status_रेजिस्टर);
	स्थिर uपूर्णांक32_t ts_data_irq_mask =
		AT91_ADC_IER_XRDY |
		AT91_ADC_IER_YRDY |
		AT91_ADC_IER_PRDY;

	अगर (status & GENMASK(st->num_channels - 1, 0))
		handle_adc_eoc_trigger(irq, idev);

	अगर (status & AT91_ADC_IER_PEN) अणु
		at91_adc_ग_लिखोl(st, AT91_ADC_IDR, AT91_ADC_IER_PEN);
		at91_adc_ग_लिखोl(st, AT91_ADC_IER, AT91_ADC_IER_NOPEN |
			ts_data_irq_mask);
		/* Set up period trigger क्रम sampling */
		at91_adc_ग_लिखोl(st, st->रेजिस्टरs->trigger_रेजिस्टर,
			AT91_ADC_TRGR_MOD_PERIOD_TRIG |
			AT91_ADC_TRGR_TRGPER_(st->ts_sample_period_val));
	पूर्ण अन्यथा अगर (status & AT91_ADC_IER_NOPEN) अणु
		at91_adc_ग_लिखोl(st, st->रेजिस्टरs->trigger_रेजिस्टर, 0);
		at91_adc_ग_लिखोl(st, AT91_ADC_IDR, AT91_ADC_IER_NOPEN |
			ts_data_irq_mask);
		at91_adc_ग_लिखोl(st, AT91_ADC_IER, AT91_ADC_IER_PEN);

		input_report_key(st->ts_input, BTN_TOUCH, 0);
		input_sync(st->ts_input);
	पूर्ण अन्यथा अगर ((status & ts_data_irq_mask) == ts_data_irq_mask) अणु
		/* Now all touchscreen data is पढ़ोy */

		अगर (status & AT91_ADC_ISR_PENS) अणु
			/* validate data by pen contact */
			at91_ts_sample(idev);
		पूर्ण अन्यथा अणु
			/* triggered by event that is no pen contact, just पढ़ो
			 * them to clean the पूर्णांकerrupt and discard all.
			 */
			at91_adc_पढ़ोl(st, AT91_ADC_TSXPOSR);
			at91_adc_पढ़ोl(st, AT91_ADC_TSYPOSR);
			at91_adc_पढ़ोl(st, AT91_ADC_TSPRESSR);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक at91_adc_channel_init(काष्ठा iio_dev *idev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(idev);
	काष्ठा iio_chan_spec *chan_array, *बारtamp;
	पूर्णांक bit, idx = 0;
	अचिन्हित दीर्घ rsvd_mask = 0;

	/* If touchscreen is enable, then reserve the adc channels */
	अगर (st->touchscreen_type == ATMEL_ADC_TOUCHSCREEN_4WIRE)
		rsvd_mask = CHAN_MASK_TOUCHSCREEN_4WIRE;
	अन्यथा अगर (st->touchscreen_type == ATMEL_ADC_TOUCHSCREEN_5WIRE)
		rsvd_mask = CHAN_MASK_TOUCHSCREEN_5WIRE;

	/* set up the channel mask to reserve touchscreen channels */
	st->channels_mask &= ~rsvd_mask;

	idev->num_channels = biपंचांगap_weight(&st->channels_mask,
					   st->num_channels) + 1;

	chan_array = devm_kzalloc(&idev->dev,
				  ((idev->num_channels + 1) *
					माप(काष्ठा iio_chan_spec)),
				  GFP_KERNEL);

	अगर (!chan_array)
		वापस -ENOMEM;

	क्रम_each_set_bit(bit, &st->channels_mask, st->num_channels) अणु
		काष्ठा iio_chan_spec *chan = chan_array + idx;

		chan->type = IIO_VOLTAGE;
		chan->indexed = 1;
		chan->channel = bit;
		chan->scan_index = idx;
		chan->scan_type.sign = 'u';
		chan->scan_type.realbits = st->res;
		chan->scan_type.storagebits = 16;
		chan->info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE);
		chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
		idx++;
	पूर्ण
	बारtamp = chan_array + idx;

	बारtamp->type = IIO_TIMESTAMP;
	बारtamp->channel = -1;
	बारtamp->scan_index = idx;
	बारtamp->scan_type.sign = 's';
	बारtamp->scan_type.realbits = 64;
	बारtamp->scan_type.storagebits = 64;

	idev->channels = chan_array;
	वापस idev->num_channels;
पूर्ण

अटल पूर्णांक at91_adc_get_trigger_value_by_name(काष्ठा iio_dev *idev,
					     स्थिर काष्ठा at91_adc_trigger *triggers,
					     स्थिर अक्षर *trigger_name)
अणु
	काष्ठा at91_adc_state *st = iio_priv(idev);
	पूर्णांक i;

	क्रम (i = 0; i < st->caps->trigger_number; i++) अणु
		अक्षर *name = kaप्र_लिखो(GFP_KERNEL,
				"%s-dev%d-%s",
				idev->name,
				idev->id,
				triggers[i].name);
		अगर (!name)
			वापस -ENOMEM;

		अगर (म_भेद(trigger_name, name) == 0) अणु
			kमुक्त(name);
			अगर (triggers[i].value == 0)
				वापस -EINVAL;
			वापस triggers[i].value;
		पूर्ण

		kमुक्त(name);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक at91_adc_configure_trigger(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *idev = iio_trigger_get_drvdata(trig);
	काष्ठा at91_adc_state *st = iio_priv(idev);
	स्थिर काष्ठा at91_adc_reg_desc *reg = st->रेजिस्टरs;
	u32 status = at91_adc_पढ़ोl(st, reg->trigger_रेजिस्टर);
	पूर्णांक value;
	u8 bit;

	value = at91_adc_get_trigger_value_by_name(idev,
						   st->caps->triggers,
						   idev->trig->name);
	अगर (value < 0)
		वापस value;

	अगर (state) अणु
		st->buffer = kदो_स्मृति(idev->scan_bytes, GFP_KERNEL);
		अगर (st->buffer == शून्य)
			वापस -ENOMEM;

		at91_adc_ग_लिखोl(st, reg->trigger_रेजिस्टर,
				status | value);

		क्रम_each_set_bit(bit, idev->active_scan_mask,
				 st->num_channels) अणु
			काष्ठा iio_chan_spec स्थिर *chan = idev->channels + bit;
			at91_adc_ग_लिखोl(st, AT91_ADC_CHER,
					AT91_ADC_CH(chan->channel));
		पूर्ण

		at91_adc_ग_लिखोl(st, AT91_ADC_IER, reg->drdy_mask);

	पूर्ण अन्यथा अणु
		at91_adc_ग_लिखोl(st, AT91_ADC_IDR, reg->drdy_mask);

		at91_adc_ग_लिखोl(st, reg->trigger_रेजिस्टर,
				status & ~value);

		क्रम_each_set_bit(bit, idev->active_scan_mask,
				 st->num_channels) अणु
			काष्ठा iio_chan_spec स्थिर *chan = idev->channels + bit;
			at91_adc_ग_लिखोl(st, AT91_ADC_CHDR,
					AT91_ADC_CH(chan->channel));
		पूर्ण
		kमुक्त(st->buffer);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops at91_adc_trigger_ops = अणु
	.set_trigger_state = &at91_adc_configure_trigger,
पूर्ण;

अटल काष्ठा iio_trigger *at91_adc_allocate_trigger(काष्ठा iio_dev *idev,
						     स्थिर काष्ठा at91_adc_trigger *trigger)
अणु
	काष्ठा iio_trigger *trig;
	पूर्णांक ret;

	trig = iio_trigger_alloc(idev->dev.parent, "%s-dev%d-%s", idev->name,
				 idev->id, trigger->name);
	अगर (trig == शून्य)
		वापस शून्य;

	iio_trigger_set_drvdata(trig, idev);
	trig->ops = &at91_adc_trigger_ops;

	ret = iio_trigger_रेजिस्टर(trig);
	अगर (ret)
		वापस शून्य;

	वापस trig;
पूर्ण

अटल पूर्णांक at91_adc_trigger_init(काष्ठा iio_dev *idev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(idev);
	पूर्णांक i, ret;

	st->trig = devm_kसुस्मृति(&idev->dev,
				st->caps->trigger_number, माप(*st->trig),
				GFP_KERNEL);

	अगर (st->trig == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_ret;
	पूर्ण

	क्रम (i = 0; i < st->caps->trigger_number; i++) अणु
		अगर (st->caps->triggers[i].is_बाह्यal && !(st->use_बाह्यal))
			जारी;

		st->trig[i] = at91_adc_allocate_trigger(idev,
							st->caps->triggers + i);
		अगर (st->trig[i] == शून्य) अणु
			dev_err(&idev->dev,
				"Could not allocate trigger %d\n", i);
			ret = -ENOMEM;
			जाओ error_trigger;
		पूर्ण
	पूर्ण

	वापस 0;

error_trigger:
	क्रम (i--; i >= 0; i--) अणु
		iio_trigger_unरेजिस्टर(st->trig[i]);
		iio_trigger_मुक्त(st->trig[i]);
	पूर्ण
error_ret:
	वापस ret;
पूर्ण

अटल व्योम at91_adc_trigger_हटाओ(काष्ठा iio_dev *idev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(idev);
	पूर्णांक i;

	क्रम (i = 0; i < st->caps->trigger_number; i++) अणु
		iio_trigger_unरेजिस्टर(st->trig[i]);
		iio_trigger_मुक्त(st->trig[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक at91_adc_buffer_init(काष्ठा iio_dev *idev)
अणु
	वापस iio_triggered_buffer_setup(idev, &iio_pollfunc_store_समय,
		&at91_adc_trigger_handler, शून्य);
पूर्ण

अटल व्योम at91_adc_buffer_हटाओ(काष्ठा iio_dev *idev)
अणु
	iio_triggered_buffer_cleanup(idev);
पूर्ण

अटल पूर्णांक at91_adc_पढ़ो_raw(काष्ठा iio_dev *idev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा at91_adc_state *st = iio_priv(idev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);

		st->chnb = chan->channel;
		at91_adc_ग_लिखोl(st, AT91_ADC_CHER,
				AT91_ADC_CH(chan->channel));
		at91_adc_ग_लिखोl(st, AT91_ADC_IER, BIT(chan->channel));
		at91_adc_ग_लिखोl(st, AT91_ADC_CR, AT91_ADC_START);

		ret = रुको_event_पूर्णांकerruptible_समयout(st->wq_data_avail,
						       st->करोne,
						       msecs_to_jअगरfies(1000));

		/* Disable पूर्णांकerrupts, regardless अगर adc conversion was
		 * successful or not
		 */
		at91_adc_ग_लिखोl(st, AT91_ADC_CHDR,
				AT91_ADC_CH(chan->channel));
		at91_adc_ग_लिखोl(st, AT91_ADC_IDR, BIT(chan->channel));

		अगर (ret > 0) अणु
			/* a valid conversion took place */
			*val = st->last_value;
			st->last_value = 0;
			st->करोne = false;
			ret = IIO_VAL_INT;
		पूर्ण अन्यथा अगर (ret == 0) अणु
			/* conversion समयout */
			dev_err(&idev->dev, "ADC Channel %d timeout.\n",
				chan->channel);
			ret = -ETIMEDOUT;
		पूर्ण

		mutex_unlock(&st->lock);
		वापस ret;

	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_mv;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण


अटल u32 calc_startup_ticks_9260(u32 startup_समय, u32 adc_clk_khz)
अणु
	/*
	 * Number of ticks needed to cover the startup समय of the ADC
	 * as defined in the electrical अक्षरacteristics of the board,
	 * भागided by 8. The क्रमmula thus is :
	 *   Startup Time = (ticks + 1) * 8 / ADC Clock
	 */
	वापस round_up((startup_समय * adc_clk_khz / 1000) - 1, 8) / 8;
पूर्ण

अटल u32 calc_startup_ticks_9x5(u32 startup_समय, u32 adc_clk_khz)
अणु
	/*
	 * For sama5d3x and at91sam9x5, the क्रमmula changes to:
	 * Startup Time = <lookup_table_value> / ADC Clock
	 */
	अटल स्थिर पूर्णांक startup_lookup[] = अणु
		0,   8,   16,  24,
		64,  80,  96,  112,
		512, 576, 640, 704,
		768, 832, 896, 960
		पूर्ण;
	पूर्णांक i, size = ARRAY_SIZE(startup_lookup);
	अचिन्हित पूर्णांक ticks;

	ticks = startup_समय * adc_clk_khz / 1000;
	क्रम (i = 0; i < size; i++)
		अगर (ticks < startup_lookup[i])
			अवरोध;

	ticks = i;
	अगर (ticks == size)
		/* Reach the end of lookup table */
		ticks = size - 1;

	वापस ticks;
पूर्ण

अटल पूर्णांक at91_adc_probe_dt_ts(काष्ठा device_node *node,
	काष्ठा at91_adc_state *st, काष्ठा device *dev)
अणु
	पूर्णांक ret;
	u32 prop;

	ret = of_property_पढ़ो_u32(node, "atmel,adc-ts-wires", &prop);
	अगर (ret) अणु
		dev_info(dev, "ADC Touch screen is disabled.\n");
		वापस 0;
	पूर्ण

	चयन (prop) अणु
	हाल 4:
	हाल 5:
		st->touchscreen_type = prop;
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported number of touchscreen wires (%d). Should be 4 or 5.\n", prop);
		वापस -EINVAL;
	पूर्ण

	अगर (!st->caps->has_tsmr)
		वापस 0;
	prop = 0;
	of_property_पढ़ो_u32(node, "atmel,adc-ts-pressure-threshold", &prop);
	st->ts_pressure_threshold = prop;
	अगर (st->ts_pressure_threshold) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Invalid pressure threshold for the touchscreen\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info at91_adc_info = अणु
	.पढ़ो_raw = &at91_adc_पढ़ो_raw,
पूर्ण;

/* Touchscreen related functions */
अटल पूर्णांक aपंचांगel_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा at91_adc_state *st = input_get_drvdata(dev);

	अगर (st->caps->has_tsmr)
		at91_adc_ग_लिखोl(st, AT91_ADC_IER, AT91_ADC_IER_PEN);
	अन्यथा
		at91_adc_ग_लिखोl(st, AT91_ADC_IER, AT91RL_ADC_IER_PEN);
	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा at91_adc_state *st = input_get_drvdata(dev);

	अगर (st->caps->has_tsmr)
		at91_adc_ग_लिखोl(st, AT91_ADC_IDR, AT91_ADC_IER_PEN);
	अन्यथा
		at91_adc_ग_लिखोl(st, AT91_ADC_IDR, AT91RL_ADC_IER_PEN);
पूर्ण

अटल पूर्णांक at91_ts_hw_init(काष्ठा iio_dev *idev, u32 adc_clk_khz)
अणु
	काष्ठा at91_adc_state *st = iio_priv(idev);
	u32 reg = 0;
	u32 tssctim = 0;
	पूर्णांक i = 0;

	/* a Pen Detect Debounce Time is necessary क्रम the ADC Touch to aव्योम
	 * pen detect noise.
	 * The क्रमmula is : Pen Detect Debounce Time = (2 ^ pendbc) / ADCClock
	 */
	st->ts_pendbc = round_up(TOUCH_PEN_DETECT_DEBOUNCE_US * adc_clk_khz /
				 1000, 1);

	जबतक (st->ts_pendbc >> ++i)
		;	/* Empty! Find the shअगरt offset */
	अगर (असल(st->ts_pendbc - (1 << i)) < असल(st->ts_pendbc - (1 << (i - 1))))
		st->ts_pendbc = i;
	अन्यथा
		st->ts_pendbc = i - 1;

	अगर (!st->caps->has_tsmr) अणु
		reg = at91_adc_पढ़ोl(st, AT91_ADC_MR);
		reg |= AT91_ADC_TSAMOD_TS_ONLY_MODE | AT91_ADC_PENDET;

		reg |= AT91_ADC_PENDBC_(st->ts_pendbc) & AT91_ADC_PENDBC;
		at91_adc_ग_लिखोl(st, AT91_ADC_MR, reg);

		reg = AT91_ADC_TSR_SHTIM_(TOUCH_SHTIM) & AT91_ADC_TSR_SHTIM;
		at91_adc_ग_लिखोl(st, AT91_ADC_TSR, reg);

		st->ts_sample_period_val = round_up((TOUCH_SAMPLE_PERIOD_US_RL *
						    adc_clk_khz / 1000) - 1, 1);

		वापस 0;
	पूर्ण

	/* Touchscreen Switches Closure समय needed क्रम allowing the value to
	 * stabilize.
	 * Switch Closure Time = (TSSCTIM * 4) ADCClock periods
	 */
	tssctim = DIV_ROUND_UP(TOUCH_SCTIM_US * adc_clk_khz / 1000, 4);
	dev_dbg(&idev->dev, "adc_clk at: %d KHz, tssctim at: %d\n",
		adc_clk_khz, tssctim);

	अगर (st->touchscreen_type == ATMEL_ADC_TOUCHSCREEN_4WIRE)
		reg = AT91_ADC_TSMR_TSMODE_4WIRE_PRESS;
	अन्यथा
		reg = AT91_ADC_TSMR_TSMODE_5WIRE;

	reg |= AT91_ADC_TSMR_SCTIM_(tssctim) & AT91_ADC_TSMR_SCTIM;
	reg |= AT91_ADC_TSMR_TSAV_(st->caps->ts_filter_average)
	       & AT91_ADC_TSMR_TSAV;
	reg |= AT91_ADC_TSMR_PENDBC_(st->ts_pendbc) & AT91_ADC_TSMR_PENDBC;
	reg |= AT91_ADC_TSMR_NOTSDMA;
	reg |= AT91_ADC_TSMR_PENDET_ENA;
	reg |= 0x03 << 8;	/* TSFREQ, needs to be bigger than TSAV */

	at91_adc_ग_लिखोl(st, AT91_ADC_TSMR, reg);

	/* Change adc पूर्णांकernal resistor value क्रम better pen detection,
	 * शेष value is 100 kOhm.
	 * 0 = 200 kOhm, 1 = 150 kOhm, 2 = 100 kOhm, 3 = 50 kOhm
	 * option only available on ES2 and higher
	 */
	at91_adc_ग_लिखोl(st, AT91_ADC_ACR, st->caps->ts_pen_detect_sensitivity
			& AT91_ADC_ACR_PENDETSENS);

	/* Sample Period Time = (TRGPER + 1) / ADCClock */
	st->ts_sample_period_val = round_up((TOUCH_SAMPLE_PERIOD_US *
			adc_clk_khz / 1000) - 1, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_ts_रेजिस्टर(काष्ठा iio_dev *idev,
		काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(idev);
	काष्ठा input_dev *input;
	पूर्णांक ret;

	input = input_allocate_device();
	अगर (!input) अणु
		dev_err(&idev->dev, "Failed to allocate TS device!\n");
		वापस -ENOMEM;
	पूर्ण

	input->name = DRIVER_NAME;
	input->id.bustype = BUS_HOST;
	input->dev.parent = &pdev->dev;
	input->खोलो = aपंचांगel_ts_खोलो;
	input->बंद = aपंचांगel_ts_बंद;

	__set_bit(EV_ABS, input->evbit);
	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_TOUCH, input->keybit);
	अगर (st->caps->has_tsmr) अणु
		input_set_असल_params(input, ABS_X, 0, (1 << MAX_POS_BITS) - 1,
				     0, 0);
		input_set_असल_params(input, ABS_Y, 0, (1 << MAX_POS_BITS) - 1,
				     0, 0);
		input_set_असल_params(input, ABS_PRESSURE, 0, 0xffffff, 0, 0);
	पूर्ण अन्यथा अणु
		अगर (st->touchscreen_type != ATMEL_ADC_TOUCHSCREEN_4WIRE) अणु
			dev_err(&pdev->dev,
				"This touchscreen controller only support 4 wires\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		input_set_असल_params(input, ABS_X, 0, (1 << MAX_RLPOS_BITS) - 1,
				     0, 0);
		input_set_असल_params(input, ABS_Y, 0, (1 << MAX_RLPOS_BITS) - 1,
				     0, 0);
	पूर्ण

	st->ts_input = input;
	input_set_drvdata(input, st);

	ret = input_रेजिस्टर_device(input);
	अगर (ret)
		जाओ err;

	वापस ret;

err:
	input_मुक्त_device(st->ts_input);
	वापस ret;
पूर्ण

अटल व्योम at91_ts_unरेजिस्टर(काष्ठा at91_adc_state *st)
अणु
	input_unरेजिस्टर_device(st->ts_input);
पूर्ण

अटल पूर्णांक at91_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक prsc, mstrclk, ticks, adc_clk, adc_clk_khz, shtim;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक ret;
	काष्ठा iio_dev *idev;
	काष्ठा at91_adc_state *st;
	u32 reg, prop;
	अक्षर *s;

	idev = devm_iio_device_alloc(&pdev->dev, माप(काष्ठा at91_adc_state));
	अगर (!idev)
		वापस -ENOMEM;

	st = iio_priv(idev);

	st->caps = of_device_get_match_data(&pdev->dev);

	st->use_बाह्यal = of_property_पढ़ो_bool(node, "atmel,adc-use-external-triggers");

	अगर (of_property_पढ़ो_u32(node, "atmel,adc-channels-used", &prop)) अणु
		dev_err(&idev->dev, "Missing adc-channels-used property in the DT.\n");
		वापस -EINVAL;
	पूर्ण
	st->channels_mask = prop;

	st->sleep_mode = of_property_पढ़ो_bool(node, "atmel,adc-sleep-mode");

	अगर (of_property_पढ़ो_u32(node, "atmel,adc-startup-time", &prop)) अणु
		dev_err(&idev->dev, "Missing adc-startup-time property in the DT.\n");
		वापस -EINVAL;
	पूर्ण
	st->startup_समय = prop;

	prop = 0;
	of_property_पढ़ो_u32(node, "atmel,adc-sample-hold-time", &prop);
	st->sample_hold_समय = prop;

	अगर (of_property_पढ़ो_u32(node, "atmel,adc-vref", &prop)) अणु
		dev_err(&idev->dev, "Missing adc-vref property in the DT.\n");
		वापस -EINVAL;
	पूर्ण
	st->vref_mv = prop;

	st->res = st->caps->high_res_bits;
	अगर (st->caps->low_res_bits &&
	    !of_property_पढ़ो_string(node, "atmel,adc-use-res", (स्थिर अक्षर **)&s)
	    && !म_भेद(s, "lowres"))
		st->res = st->caps->low_res_bits;

	dev_info(&idev->dev, "Resolution used: %u bits\n", st->res);

	st->रेजिस्टरs = &st->caps->रेजिस्टरs;
	st->num_channels = st->caps->num_channels;

	/* Check अगर touchscreen is supported. */
	अगर (st->caps->has_ts) अणु
		ret = at91_adc_probe_dt_ts(node, st, &idev->dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, idev);

	idev->name = dev_name(&pdev->dev);
	idev->modes = INDIO_सूचीECT_MODE;
	idev->info = &at91_adc_info;

	st->irq = platक्रमm_get_irq(pdev, 0);
	अगर (st->irq < 0)
		वापस -ENODEV;

	st->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(st->reg_base))
		वापस PTR_ERR(st->reg_base);


	/*
	 * Disable all IRQs beक्रमe setting up the handler
	 */
	at91_adc_ग_लिखोl(st, AT91_ADC_CR, AT91_ADC_SWRST);
	at91_adc_ग_लिखोl(st, AT91_ADC_IDR, 0xFFFFFFFF);

	अगर (st->caps->has_tsmr)
		ret = request_irq(st->irq, at91_adc_9x5_पूर्णांकerrupt, 0,
				  pdev->dev.driver->name, idev);
	अन्यथा
		ret = request_irq(st->irq, at91_adc_rl_पूर्णांकerrupt, 0,
				  pdev->dev.driver->name, idev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to allocate IRQ.\n");
		वापस ret;
	पूर्ण

	st->clk = devm_clk_get(&pdev->dev, "adc_clk");
	अगर (IS_ERR(st->clk)) अणु
		dev_err(&pdev->dev, "Failed to get the clock.\n");
		ret = PTR_ERR(st->clk);
		जाओ error_मुक्त_irq;
	पूर्ण

	ret = clk_prepare_enable(st->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Could not prepare or enable the clock.\n");
		जाओ error_मुक्त_irq;
	पूर्ण

	st->adc_clk = devm_clk_get(&pdev->dev, "adc_op_clk");
	अगर (IS_ERR(st->adc_clk)) अणु
		dev_err(&pdev->dev, "Failed to get the ADC clock.\n");
		ret = PTR_ERR(st->adc_clk);
		जाओ error_disable_clk;
	पूर्ण

	ret = clk_prepare_enable(st->adc_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Could not prepare or enable the ADC clock.\n");
		जाओ error_disable_clk;
	पूर्ण

	/*
	 * Prescaler rate computation using the क्रमmula from the Aपंचांगel's
	 * datasheet : ADC Clock = MCK / ((Prescaler + 1) * 2), ADC Clock being
	 * specअगरied by the electrical अक्षरacteristics of the board.
	 */
	mstrclk = clk_get_rate(st->clk);
	adc_clk = clk_get_rate(st->adc_clk);
	adc_clk_khz = adc_clk / 1000;

	dev_dbg(&pdev->dev, "Master clock is set as: %d Hz, adc_clk should set as: %d Hz\n",
		mstrclk, adc_clk);

	prsc = (mstrclk / (2 * adc_clk)) - 1;

	अगर (!st->startup_समय) अणु
		dev_err(&pdev->dev, "No startup time available.\n");
		ret = -EINVAL;
		जाओ error_disable_adc_clk;
	पूर्ण
	ticks = (*st->caps->calc_startup_ticks)(st->startup_समय, adc_clk_khz);

	/*
	 * a minimal Sample and Hold Time is necessary क्रम the ADC to guarantee
	 * the best converted final value between two channels selection
	 * The क्रमmula thus is : Sample and Hold Time = (shtim + 1) / ADCClock
	 */
	अगर (st->sample_hold_समय > 0)
		shtim = round_up((st->sample_hold_समय * adc_clk_khz / 1000)
				 - 1, 1);
	अन्यथा
		shtim = 0;

	reg = AT91_ADC_PRESCAL_(prsc) & st->रेजिस्टरs->mr_prescal_mask;
	reg |= AT91_ADC_STARTUP_(ticks) & st->रेजिस्टरs->mr_startup_mask;
	अगर (st->res == st->caps->low_res_bits)
		reg |= AT91_ADC_LOWRES;
	अगर (st->sleep_mode)
		reg |= AT91_ADC_SLEEP;
	reg |= AT91_ADC_SHTIM_(shtim) & AT91_ADC_SHTIM;
	at91_adc_ग_लिखोl(st, AT91_ADC_MR, reg);

	/* Setup the ADC channels available on the board */
	ret = at91_adc_channel_init(idev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Couldn't initialize the channels.\n");
		जाओ error_disable_adc_clk;
	पूर्ण

	init_रुकोqueue_head(&st->wq_data_avail);
	mutex_init(&st->lock);

	/*
	 * Since touch screen will set trigger रेजिस्टर as period trigger. So
	 * when touch screen is enabled, then we have to disable hardware
	 * trigger क्रम classic adc.
	 */
	अगर (!st->touchscreen_type) अणु
		ret = at91_adc_buffer_init(idev);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "Couldn't initialize the buffer.\n");
			जाओ error_disable_adc_clk;
		पूर्ण

		ret = at91_adc_trigger_init(idev);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "Couldn't setup the triggers.\n");
			at91_adc_buffer_हटाओ(idev);
			जाओ error_disable_adc_clk;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = at91_ts_रेजिस्टर(idev, pdev);
		अगर (ret)
			जाओ error_disable_adc_clk;

		at91_ts_hw_init(idev, adc_clk_khz);
	पूर्ण

	ret = iio_device_रेजिस्टर(idev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Couldn't register the device.\n");
		जाओ error_iio_device_रेजिस्टर;
	पूर्ण

	वापस 0;

error_iio_device_रेजिस्टर:
	अगर (!st->touchscreen_type) अणु
		at91_adc_trigger_हटाओ(idev);
		at91_adc_buffer_हटाओ(idev);
	पूर्ण अन्यथा अणु
		at91_ts_unरेजिस्टर(st);
	पूर्ण
error_disable_adc_clk:
	clk_disable_unprepare(st->adc_clk);
error_disable_clk:
	clk_disable_unprepare(st->clk);
error_मुक्त_irq:
	मुक्त_irq(st->irq, idev);
	वापस ret;
पूर्ण

अटल पूर्णांक at91_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *idev = platक्रमm_get_drvdata(pdev);
	काष्ठा at91_adc_state *st = iio_priv(idev);

	iio_device_unरेजिस्टर(idev);
	अगर (!st->touchscreen_type) अणु
		at91_adc_trigger_हटाओ(idev);
		at91_adc_buffer_हटाओ(idev);
	पूर्ण अन्यथा अणु
		at91_ts_unरेजिस्टर(st);
	पूर्ण
	clk_disable_unprepare(st->adc_clk);
	clk_disable_unprepare(st->clk);
	मुक्त_irq(st->irq, idev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक at91_adc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *idev = dev_get_drvdata(dev);
	काष्ठा at91_adc_state *st = iio_priv(idev);

	pinctrl_pm_select_sleep_state(dev);
	clk_disable_unprepare(st->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_adc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *idev = dev_get_drvdata(dev);
	काष्ठा at91_adc_state *st = iio_priv(idev);

	clk_prepare_enable(st->clk);
	pinctrl_pm_select_शेष_state(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(at91_adc_pm_ops, at91_adc_suspend, at91_adc_resume);

अटल स्थिर काष्ठा at91_adc_trigger at91sam9260_triggers[] = अणु
	अणु .name = "timer-counter-0", .value = 0x1 पूर्ण,
	अणु .name = "timer-counter-1", .value = 0x3 पूर्ण,
	अणु .name = "timer-counter-2", .value = 0x5 पूर्ण,
	अणु .name = "external", .value = 0xd, .is_बाह्यal = true पूर्ण,
पूर्ण;

अटल काष्ठा at91_adc_caps at91sam9260_caps = अणु
	.calc_startup_ticks = calc_startup_ticks_9260,
	.num_channels = 4,
	.low_res_bits = 8,
	.high_res_bits = 10,
	.रेजिस्टरs = अणु
		.channel_base = AT91_ADC_CHR(0),
		.drdy_mask = AT91_ADC_DRDY,
		.status_रेजिस्टर = AT91_ADC_SR,
		.trigger_रेजिस्टर = AT91_ADC_TRGR_9260,
		.mr_prescal_mask = AT91_ADC_PRESCAL_9260,
		.mr_startup_mask = AT91_ADC_STARTUP_9260,
	पूर्ण,
	.triggers = at91sam9260_triggers,
	.trigger_number = ARRAY_SIZE(at91sam9260_triggers),
पूर्ण;

अटल स्थिर काष्ठा at91_adc_trigger at91sam9x5_triggers[] = अणु
	अणु .name = "external-rising", .value = 0x1, .is_बाह्यal = true पूर्ण,
	अणु .name = "external-falling", .value = 0x2, .is_बाह्यal = true पूर्ण,
	अणु .name = "external-any", .value = 0x3, .is_बाह्यal = true पूर्ण,
	अणु .name = "continuous", .value = 0x6 पूर्ण,
पूर्ण;

अटल काष्ठा at91_adc_caps at91sam9rl_caps = अणु
	.has_ts = true,
	.calc_startup_ticks = calc_startup_ticks_9260,	/* same as 9260 */
	.num_channels = 6,
	.low_res_bits = 8,
	.high_res_bits = 10,
	.रेजिस्टरs = अणु
		.channel_base = AT91_ADC_CHR(0),
		.drdy_mask = AT91_ADC_DRDY,
		.status_रेजिस्टर = AT91_ADC_SR,
		.trigger_रेजिस्टर = AT91_ADC_TRGR_9G45,
		.mr_prescal_mask = AT91_ADC_PRESCAL_9260,
		.mr_startup_mask = AT91_ADC_STARTUP_9G45,
	पूर्ण,
	.triggers = at91sam9x5_triggers,
	.trigger_number = ARRAY_SIZE(at91sam9x5_triggers),
पूर्ण;

अटल काष्ठा at91_adc_caps at91sam9g45_caps = अणु
	.has_ts = true,
	.calc_startup_ticks = calc_startup_ticks_9260,	/* same as 9260 */
	.num_channels = 8,
	.low_res_bits = 8,
	.high_res_bits = 10,
	.रेजिस्टरs = अणु
		.channel_base = AT91_ADC_CHR(0),
		.drdy_mask = AT91_ADC_DRDY,
		.status_रेजिस्टर = AT91_ADC_SR,
		.trigger_रेजिस्टर = AT91_ADC_TRGR_9G45,
		.mr_prescal_mask = AT91_ADC_PRESCAL_9G45,
		.mr_startup_mask = AT91_ADC_STARTUP_9G45,
	पूर्ण,
	.triggers = at91sam9x5_triggers,
	.trigger_number = ARRAY_SIZE(at91sam9x5_triggers),
पूर्ण;

अटल काष्ठा at91_adc_caps at91sam9x5_caps = अणु
	.has_ts = true,
	.has_tsmr = true,
	.ts_filter_average = 3,
	.ts_pen_detect_sensitivity = 2,
	.calc_startup_ticks = calc_startup_ticks_9x5,
	.num_channels = 12,
	.low_res_bits = 8,
	.high_res_bits = 10,
	.रेजिस्टरs = अणु
		.channel_base = AT91_ADC_CDR0_9X5,
		.drdy_mask = AT91_ADC_SR_DRDY_9X5,
		.status_रेजिस्टर = AT91_ADC_SR_9X5,
		.trigger_रेजिस्टर = AT91_ADC_TRGR_9X5,
		/* prescal mask is same as 9G45 */
		.mr_prescal_mask = AT91_ADC_PRESCAL_9G45,
		.mr_startup_mask = AT91_ADC_STARTUP_9X5,
	पूर्ण,
	.triggers = at91sam9x5_triggers,
	.trigger_number = ARRAY_SIZE(at91sam9x5_triggers),
पूर्ण;

अटल काष्ठा at91_adc_caps sama5d3_caps = अणु
	.has_ts = true,
	.has_tsmr = true,
	.ts_filter_average = 3,
	.ts_pen_detect_sensitivity = 2,
	.calc_startup_ticks = calc_startup_ticks_9x5,
	.num_channels = 12,
	.low_res_bits = 0,
	.high_res_bits = 12,
	.रेजिस्टरs = अणु
		.channel_base = AT91_ADC_CDR0_9X5,
		.drdy_mask = AT91_ADC_SR_DRDY_9X5,
		.status_रेजिस्टर = AT91_ADC_SR_9X5,
		.trigger_रेजिस्टर = AT91_ADC_TRGR_9X5,
		.mr_prescal_mask = AT91_ADC_PRESCAL_9G45,
		.mr_startup_mask = AT91_ADC_STARTUP_9X5,
	पूर्ण,
	.triggers = at91sam9x5_triggers,
	.trigger_number = ARRAY_SIZE(at91sam9x5_triggers),
पूर्ण;

अटल स्थिर काष्ठा of_device_id at91_adc_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9260-adc", .data = &at91sam9260_caps पूर्ण,
	अणु .compatible = "atmel,at91sam9rl-adc", .data = &at91sam9rl_caps पूर्ण,
	अणु .compatible = "atmel,at91sam9g45-adc", .data = &at91sam9g45_caps पूर्ण,
	अणु .compatible = "atmel,at91sam9x5-adc", .data = &at91sam9x5_caps पूर्ण,
	अणु .compatible = "atmel,sama5d3-adc", .data = &sama5d3_caps पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_adc_dt_ids);

अटल काष्ठा platक्रमm_driver at91_adc_driver = अणु
	.probe = at91_adc_probe,
	.हटाओ = at91_adc_हटाओ,
	.driver = अणु
		   .name = DRIVER_NAME,
		   .of_match_table = at91_adc_dt_ids,
		   .pm = &at91_adc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(at91_adc_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Atmel AT91 ADC Driver");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
