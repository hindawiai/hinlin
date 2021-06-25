<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale MXS LRADC touchscreen driver
 *
 * Copyright (c) 2012 DENX Software Engineering, GmbH.
 * Copyright (c) 2017 Ksenija Stanojevic <ksenija.stanojevic@gmail.com>
 *
 * Authors:
 *  Marek Vasut <marex@denx.de>
 *  Ksenija Stanojevic <ksenija.stanojevic@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/mxs-lradc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

अटल स्थिर अक्षर * स्थिर mxs_lradc_ts_irq_names[] = अणु
	"mxs-lradc-touchscreen",
	"mxs-lradc-channel6",
	"mxs-lradc-channel7",
पूर्ण;

/*
 * Touchscreen handling
 */
क्रमागत mxs_lradc_ts_plate अणु
	LRADC_TOUCH = 0,
	LRADC_SAMPLE_X,
	LRADC_SAMPLE_Y,
	LRADC_SAMPLE_PRESSURE,
	LRADC_SAMPLE_VALID,
पूर्ण;

काष्ठा mxs_lradc_ts अणु
	काष्ठा mxs_lradc	*lradc;
	काष्ठा device		*dev;

	व्योम __iomem		*base;
	/*
	 * When the touchscreen is enabled, we give it two निजी भव
	 * channels: #6 and #7. This means that only 6 भव channels (instead
	 * of 8) will be available क्रम buffered capture.
	 */
#घोषणा TOUCHSCREEN_VCHANNEL1		7
#घोषणा TOUCHSCREEN_VCHANNEL2		6

	काष्ठा input_dev	*ts_input;

	क्रमागत mxs_lradc_ts_plate	cur_plate; /* state machine */
	bool			ts_valid;
	अचिन्हित पूर्णांक		ts_x_pos;
	अचिन्हित पूर्णांक		ts_y_pos;
	अचिन्हित पूर्णांक		ts_pressure;

	/* handle touchscreen's physical behaviour */
	/* samples per coordinate */
	अचिन्हित पूर्णांक		over_sample_cnt;
	/* समय घड़ीs between samples */
	अचिन्हित पूर्णांक		over_sample_delay;
	/* समय in घड़ीs to रुको after the plates where चयनed */
	अचिन्हित पूर्णांक		settling_delay;
	spinlock_t		lock;
पूर्ण;

काष्ठा state_info अणु
	u32		mask;
	u32		bit;
	u32		x_plate;
	u32		y_plate;
	u32		pressure;
पूर्ण;

अटल काष्ठा state_info info[] = अणु
	अणुLRADC_CTRL0_MX23_PLATE_MASK, LRADC_CTRL0_MX23_TOUCH_DETECT_ENABLE,
	 LRADC_CTRL0_MX23_XP | LRADC_CTRL0_MX23_XM,
	 LRADC_CTRL0_MX23_YP | LRADC_CTRL0_MX23_YM,
	 LRADC_CTRL0_MX23_YP | LRADC_CTRL0_MX23_XMपूर्ण,
	अणुLRADC_CTRL0_MX28_PLATE_MASK, LRADC_CTRL0_MX28_TOUCH_DETECT_ENABLE,
	 LRADC_CTRL0_MX28_XPPSW | LRADC_CTRL0_MX28_XNNSW,
	 LRADC_CTRL0_MX28_YPPSW | LRADC_CTRL0_MX28_YNNSW,
	 LRADC_CTRL0_MX28_YPPSW | LRADC_CTRL0_MX28_XNNSWपूर्ण
पूर्ण;

अटल bool mxs_lradc_check_touch_event(काष्ठा mxs_lradc_ts *ts)
अणु
	वापस !!(पढ़ोl(ts->base + LRADC_STATUS) &
					LRADC_STATUS_TOUCH_DETECT_RAW);
पूर्ण

अटल व्योम mxs_lradc_map_ts_channel(काष्ठा mxs_lradc_ts *ts, अचिन्हित पूर्णांक vch,
				     अचिन्हित पूर्णांक ch)
अणु
	ग_लिखोl(LRADC_CTRL4_LRADCSELECT_MASK(vch),
	       ts->base + LRADC_CTRL4 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(LRADC_CTRL4_LRADCSELECT(vch, ch),
	       ts->base + LRADC_CTRL4 + STMP_OFFSET_REG_SET);
पूर्ण

अटल व्योम mxs_lradc_setup_ts_channel(काष्ठा mxs_lradc_ts *ts, अचिन्हित पूर्णांक ch)
अणु
	/*
	 * prepare क्रम oversampling conversion
	 *
	 * from the datasheet:
	 * "The ACCUMULATE bit in the appropriate channel रेजिस्टर
	 * HW_LRADC_CHn must be set to 1 अगर NUM_SAMPLES is greater then 0;
	 * otherwise, the IRQs will not fire."
	 */
	ग_लिखोl(LRADC_CH_ACCUMULATE |
	       LRADC_CH_NUM_SAMPLES(ts->over_sample_cnt - 1),
	       ts->base + LRADC_CH(ch));

	/* from the datasheet:
	 * "Software must clear this रेजिस्टर in preparation क्रम a
	 * multi-cycle accumulation.
	 */
	ग_लिखोl(LRADC_CH_VALUE_MASK,
	       ts->base + LRADC_CH(ch) + STMP_OFFSET_REG_CLR);

	/*
	 * prepare the delay/loop unit according to the oversampling count
	 *
	 * from the datasheet:
	 * "The DELAY fields in HW_LRADC_DELAY0, HW_LRADC_DELAY1,
	 * HW_LRADC_DELAY2, and HW_LRADC_DELAY3 must be non-zero; otherwise,
	 * the LRADC will not trigger the delay group."
	 */
	ग_लिखोl(LRADC_DELAY_TRIGGER(1 << ch) | LRADC_DELAY_TRIGGER_DELAYS(0) |
	       LRADC_DELAY_LOOP(ts->over_sample_cnt - 1) |
	       LRADC_DELAY_DELAY(ts->over_sample_delay - 1),
	       ts->base + LRADC_DELAY(3));

	ग_लिखोl(LRADC_CTRL1_LRADC_IRQ(ch),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);

	/*
	 * after changing the touchscreen plates setting
	 * the संकेतs need some initial समय to settle. Start the
	 * SoC's delay unit and start the conversion later
	 * and स्वतःmatically.
	 */
	ग_लिखोl(LRADC_DELAY_TRIGGER(0) | LRADC_DELAY_TRIGGER_DELAYS(BIT(3)) |
	       LRADC_DELAY_KICK | LRADC_DELAY_DELAY(ts->settling_delay),
	       ts->base + LRADC_DELAY(2));
पूर्ण

/*
 * Pressure detection is special:
 * We want to करो both required measurements क्रम the pressure detection in
 * one turn. Use the hardware features to chain both conversions and let the
 * hardware report one पूर्णांकerrupt अगर both conversions are करोne
 */
अटल व्योम mxs_lradc_setup_ts_pressure(काष्ठा mxs_lradc_ts *ts,
					अचिन्हित पूर्णांक ch1, अचिन्हित पूर्णांक ch2)
अणु
	u32 reg;

	/*
	 * prepare क्रम oversampling conversion
	 *
	 * from the datasheet:
	 * "The ACCUMULATE bit in the appropriate channel रेजिस्टर
	 * HW_LRADC_CHn must be set to 1 अगर NUM_SAMPLES is greater then 0;
	 * otherwise, the IRQs will not fire."
	 */
	reg = LRADC_CH_ACCUMULATE |
		LRADC_CH_NUM_SAMPLES(ts->over_sample_cnt - 1);
	ग_लिखोl(reg, ts->base + LRADC_CH(ch1));
	ग_लिखोl(reg, ts->base + LRADC_CH(ch2));

	/* from the datasheet:
	 * "Software must clear this रेजिस्टर in preparation क्रम a
	 * multi-cycle accumulation.
	 */
	ग_लिखोl(LRADC_CH_VALUE_MASK,
	       ts->base + LRADC_CH(ch1) + STMP_OFFSET_REG_CLR);
	ग_लिखोl(LRADC_CH_VALUE_MASK,
	       ts->base + LRADC_CH(ch2) + STMP_OFFSET_REG_CLR);

	/* prepare the delay/loop unit according to the oversampling count */
	ग_लिखोl(LRADC_DELAY_TRIGGER(1 << ch1) | LRADC_DELAY_TRIGGER(1 << ch2) |
	       LRADC_DELAY_TRIGGER_DELAYS(0) |
	       LRADC_DELAY_LOOP(ts->over_sample_cnt - 1) |
	       LRADC_DELAY_DELAY(ts->over_sample_delay - 1),
	       ts->base + LRADC_DELAY(3));

	ग_लिखोl(LRADC_CTRL1_LRADC_IRQ(ch2),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);

	/*
	 * after changing the touchscreen plates setting
	 * the संकेतs need some initial समय to settle. Start the
	 * SoC's delay unit and start the conversion later
	 * and स्वतःmatically.
	 */
	ग_लिखोl(LRADC_DELAY_TRIGGER(0) | LRADC_DELAY_TRIGGER_DELAYS(BIT(3)) |
	       LRADC_DELAY_KICK | LRADC_DELAY_DELAY(ts->settling_delay),
	       ts->base + LRADC_DELAY(2));
पूर्ण

अटल अचिन्हित पूर्णांक mxs_lradc_ts_पढ़ो_raw_channel(काष्ठा mxs_lradc_ts *ts,
						  अचिन्हित पूर्णांक channel)
अणु
	u32 reg;
	अचिन्हित पूर्णांक num_samples, val;

	reg = पढ़ोl(ts->base + LRADC_CH(channel));
	अगर (reg & LRADC_CH_ACCUMULATE)
		num_samples = ts->over_sample_cnt;
	अन्यथा
		num_samples = 1;

	val = (reg & LRADC_CH_VALUE_MASK) >> LRADC_CH_VALUE_OFFSET;
	वापस val / num_samples;
पूर्ण

अटल अचिन्हित पूर्णांक mxs_lradc_पढ़ो_ts_pressure(काष्ठा mxs_lradc_ts *ts,
					अचिन्हित पूर्णांक ch1, अचिन्हित पूर्णांक ch2)
अणु
	u32 reg, mask;
	अचिन्हित पूर्णांक pressure, m1, m2;

	mask = LRADC_CTRL1_LRADC_IRQ(ch1) | LRADC_CTRL1_LRADC_IRQ(ch2);
	reg = पढ़ोl(ts->base + LRADC_CTRL1) & mask;

	जबतक (reg != mask) अणु
		reg = पढ़ोl(ts->base + LRADC_CTRL1) & mask;
		dev_dbg(ts->dev, "One channel is still busy: %X\n", reg);
	पूर्ण

	m1 = mxs_lradc_ts_पढ़ो_raw_channel(ts, ch1);
	m2 = mxs_lradc_ts_पढ़ो_raw_channel(ts, ch2);

	अगर (m2 == 0) अणु
		dev_warn(ts->dev, "Cannot calculate pressure\n");
		वापस 1 << (LRADC_RESOLUTION - 1);
	पूर्ण

	/* simply scale the value from 0 ... max ADC resolution */
	pressure = m1;
	pressure *= (1 << LRADC_RESOLUTION);
	pressure /= m2;

	dev_dbg(ts->dev, "Pressure = %u\n", pressure);
	वापस pressure;
पूर्ण

#घोषणा TS_CH_XP 2
#घोषणा TS_CH_YP 3
#घोषणा TS_CH_XM 4
#घोषणा TS_CH_YM 5

/*
 * YP(खोलो)--+-------------+
 *	     |		   |--+
 *	     |		   |  |
 *    YM(-)--+-------------+  |
 *	       +--------------+
 *	       |	      |
 *	   XP(weak+)	    XM(खोलो)
 *
 * "weak+" means 200k Ohm VDDIO
 * (-) means GND
 */
अटल व्योम mxs_lradc_setup_touch_detection(काष्ठा mxs_lradc_ts *ts)
अणु
	काष्ठा mxs_lradc *lradc = ts->lradc;

	/*
	 * In order to detect a touch event the 'touch detect enable' bit
	 * enables:
	 *  - a weak pullup to the X+ connector
	 *  - a strong ground at the Y- connector
	 */
	ग_लिखोl(info[lradc->soc].mask,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(info[lradc->soc].bit,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);
पूर्ण

/*
 * YP(meas)--+-------------+
 *	     |		   |--+
 *	     |		   |  |
 * YM(खोलो)--+-------------+  |
 *	       +--------------+
 *	       |	      |
 *	     XP(+)	    XM(-)
 *
 * (+) means here 1.85 V
 * (-) means here GND
 */
अटल व्योम mxs_lradc_prepare_x_pos(काष्ठा mxs_lradc_ts *ts)
अणु
	काष्ठा mxs_lradc *lradc = ts->lradc;

	ग_लिखोl(info[lradc->soc].mask,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(info[lradc->soc].x_plate,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);

	ts->cur_plate = LRADC_SAMPLE_X;
	mxs_lradc_map_ts_channel(ts, TOUCHSCREEN_VCHANNEL1, TS_CH_YP);
	mxs_lradc_setup_ts_channel(ts, TOUCHSCREEN_VCHANNEL1);
पूर्ण

/*
 *   YP(+)--+-------------+
 *	    |		  |--+
 *	    |		  |  |
 *   YM(-)--+-------------+  |
 *	      +--------------+
 *	      |		     |
 *	   XP(खोलो)	   XM(meas)
 *
 * (+) means here 1.85 V
 * (-) means here GND
 */
अटल व्योम mxs_lradc_prepare_y_pos(काष्ठा mxs_lradc_ts *ts)
अणु
	काष्ठा mxs_lradc *lradc = ts->lradc;

	ग_लिखोl(info[lradc->soc].mask,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(info[lradc->soc].y_plate,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);

	ts->cur_plate = LRADC_SAMPLE_Y;
	mxs_lradc_map_ts_channel(ts, TOUCHSCREEN_VCHANNEL1, TS_CH_XM);
	mxs_lradc_setup_ts_channel(ts, TOUCHSCREEN_VCHANNEL1);
पूर्ण

/*
 *    YP(+)--+-------------+
 *	     |		   |--+
 *	     |		   |  |
 * YM(meas)--+-------------+  |
 *	       +--------------+
 *	       |	      |
 *	    XP(meas)	    XM(-)
 *
 * (+) means here 1.85 V
 * (-) means here GND
 */
अटल व्योम mxs_lradc_prepare_pressure(काष्ठा mxs_lradc_ts *ts)
अणु
	काष्ठा mxs_lradc *lradc = ts->lradc;

	ग_लिखोl(info[lradc->soc].mask,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(info[lradc->soc].pressure,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);

	ts->cur_plate = LRADC_SAMPLE_PRESSURE;
	mxs_lradc_map_ts_channel(ts, TOUCHSCREEN_VCHANNEL1, TS_CH_YM);
	mxs_lradc_map_ts_channel(ts, TOUCHSCREEN_VCHANNEL2, TS_CH_XP);
	mxs_lradc_setup_ts_pressure(ts, TOUCHSCREEN_VCHANNEL2,
				    TOUCHSCREEN_VCHANNEL1);
पूर्ण

अटल व्योम mxs_lradc_enable_touch_detection(काष्ठा mxs_lradc_ts *ts)
अणु
	mxs_lradc_setup_touch_detection(ts);

	ts->cur_plate = LRADC_TOUCH;
	ग_लिखोl(LRADC_CTRL1_TOUCH_DETECT_IRQ | LRADC_CTRL1_TOUCH_DETECT_IRQ_EN,
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(LRADC_CTRL1_TOUCH_DETECT_IRQ_EN,
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_SET);
पूर्ण

अटल व्योम mxs_lradc_start_touch_event(काष्ठा mxs_lradc_ts *ts)
अणु
	ग_लिखोl(LRADC_CTRL1_TOUCH_DETECT_IRQ_EN,
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(LRADC_CTRL1_LRADC_IRQ_EN(TOUCHSCREEN_VCHANNEL1),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_SET);
	/*
	 * start with the Y-pos, because it uses nearly the same plate
	 * settings like the touch detection
	 */
	mxs_lradc_prepare_y_pos(ts);
पूर्ण

अटल व्योम mxs_lradc_report_ts_event(काष्ठा mxs_lradc_ts *ts)
अणु
	input_report_असल(ts->ts_input, ABS_X, ts->ts_x_pos);
	input_report_असल(ts->ts_input, ABS_Y, ts->ts_y_pos);
	input_report_असल(ts->ts_input, ABS_PRESSURE, ts->ts_pressure);
	input_report_key(ts->ts_input, BTN_TOUCH, 1);
	input_sync(ts->ts_input);
पूर्ण

अटल व्योम mxs_lradc_complete_touch_event(काष्ठा mxs_lradc_ts *ts)
अणु
	mxs_lradc_setup_touch_detection(ts);
	ts->cur_plate = LRADC_SAMPLE_VALID;
	/*
	 * start a dummy conversion to burn समय to settle the संकेतs
	 * note: we are not पूर्णांकerested in the conversion's value
	 */
	ग_लिखोl(0, ts->base + LRADC_CH(TOUCHSCREEN_VCHANNEL1));
	ग_लिखोl(LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1) |
	       LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL2),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(LRADC_DELAY_TRIGGER(1 << TOUCHSCREEN_VCHANNEL1) |
	       LRADC_DELAY_KICK | LRADC_DELAY_DELAY(10),
	       ts->base + LRADC_DELAY(2));
पूर्ण

/*
 * in order to aव्योम false measurements, report only samples where
 * the surface is still touched after the position measurement
 */
अटल व्योम mxs_lradc_finish_touch_event(काष्ठा mxs_lradc_ts *ts, bool valid)
अणु
	/* अगर it is still touched, report the sample */
	अगर (valid && mxs_lradc_check_touch_event(ts)) अणु
		ts->ts_valid = true;
		mxs_lradc_report_ts_event(ts);
	पूर्ण

	/* अगर it is even still touched, जारी with the next measurement */
	अगर (mxs_lradc_check_touch_event(ts)) अणु
		mxs_lradc_prepare_y_pos(ts);
		वापस;
	पूर्ण

	अगर (ts->ts_valid) अणु
		/* संकेत the release */
		ts->ts_valid = false;
		input_report_key(ts->ts_input, BTN_TOUCH, 0);
		input_sync(ts->ts_input);
	पूर्ण

	/* अगर it is released, रुको क्रम the next touch via IRQ */
	ts->cur_plate = LRADC_TOUCH;
	ग_लिखोl(0, ts->base + LRADC_DELAY(2));
	ग_लिखोl(0, ts->base + LRADC_DELAY(3));
	ग_लिखोl(LRADC_CTRL1_TOUCH_DETECT_IRQ |
	       LRADC_CTRL1_LRADC_IRQ_EN(TOUCHSCREEN_VCHANNEL1) |
	       LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(LRADC_CTRL1_TOUCH_DETECT_IRQ_EN,
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_SET);
पूर्ण

/* touchscreen's state machine */
अटल व्योम mxs_lradc_handle_touch(काष्ठा mxs_lradc_ts *ts)
अणु
	चयन (ts->cur_plate) अणु
	हाल LRADC_TOUCH:
		अगर (mxs_lradc_check_touch_event(ts))
			mxs_lradc_start_touch_event(ts);
		ग_लिखोl(LRADC_CTRL1_TOUCH_DETECT_IRQ,
		       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
		वापस;

	हाल LRADC_SAMPLE_Y:
		ts->ts_y_pos =
		    mxs_lradc_ts_पढ़ो_raw_channel(ts, TOUCHSCREEN_VCHANNEL1);
		mxs_lradc_prepare_x_pos(ts);
		वापस;

	हाल LRADC_SAMPLE_X:
		ts->ts_x_pos =
		    mxs_lradc_ts_पढ़ो_raw_channel(ts, TOUCHSCREEN_VCHANNEL1);
		mxs_lradc_prepare_pressure(ts);
		वापस;

	हाल LRADC_SAMPLE_PRESSURE:
		ts->ts_pressure =
		    mxs_lradc_पढ़ो_ts_pressure(ts,
					       TOUCHSCREEN_VCHANNEL2,
					       TOUCHSCREEN_VCHANNEL1);
		mxs_lradc_complete_touch_event(ts);
		वापस;

	हाल LRADC_SAMPLE_VALID:
		mxs_lradc_finish_touch_event(ts, 1);
		अवरोध;
	पूर्ण
पूर्ण

/* IRQ Handling */
अटल irqवापस_t mxs_lradc_ts_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mxs_lradc_ts *ts = data;
	काष्ठा mxs_lradc *lradc = ts->lradc;
	अचिन्हित दीर्घ reg = पढ़ोl(ts->base + LRADC_CTRL1);
	u32 clr_irq = mxs_lradc_irq_mask(lradc);
	स्थिर u32 ts_irq_mask =
		LRADC_CTRL1_TOUCH_DETECT_IRQ |
		LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1) |
		LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL2);
	अचिन्हित दीर्घ flags;

	अगर (!(reg & mxs_lradc_irq_mask(lradc)))
		वापस IRQ_NONE;

	अगर (reg & ts_irq_mask) अणु
		spin_lock_irqsave(&ts->lock, flags);
		mxs_lradc_handle_touch(ts);
		spin_unlock_irqrestore(&ts->lock, flags);
		/* Make sure we करोn't clear the next conversion's पूर्णांकerrupt. */
		clr_irq &= ~(LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1) |
				LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL2));
		ग_लिखोl(reg & clr_irq,
		       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxs_lradc_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा mxs_lradc_ts *ts = input_get_drvdata(dev);

	/* Enable the touch-detect circuitry. */
	mxs_lradc_enable_touch_detection(ts);

	वापस 0;
पूर्ण

अटल व्योम mxs_lradc_ts_stop(काष्ठा mxs_lradc_ts *ts)
अणु
	पूर्णांक i;
	काष्ठा mxs_lradc *lradc = ts->lradc;

	/* stop all पूर्णांकerrupts from firing */
	ग_लिखोl(LRADC_CTRL1_TOUCH_DETECT_IRQ_EN |
	       LRADC_CTRL1_LRADC_IRQ_EN(TOUCHSCREEN_VCHANNEL1) |
	       LRADC_CTRL1_LRADC_IRQ_EN(TOUCHSCREEN_VCHANNEL2),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);

	/* Power-करोwn touchscreen touch-detect circuitry. */
	ग_लिखोl(info[lradc->soc].mask,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);

	ग_लिखोl(lradc->buffer_vchans << LRADC_CTRL1_LRADC_IRQ_EN_OFFSET,
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);

	क्रम (i = 1; i < LRADC_MAX_DELAY_CHANS; i++)
		ग_लिखोl(0, ts->base + LRADC_DELAY(i));
पूर्ण

अटल व्योम mxs_lradc_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा mxs_lradc_ts *ts = input_get_drvdata(dev);

	mxs_lradc_ts_stop(ts);
पूर्ण

अटल व्योम mxs_lradc_ts_hw_init(काष्ठा mxs_lradc_ts *ts)
अणु
	काष्ठा mxs_lradc *lradc = ts->lradc;

	/* Configure the touchscreen type */
	अगर (lradc->soc == IMX28_LRADC) अणु
		ग_लिखोl(LRADC_CTRL0_MX28_TOUCH_SCREEN_TYPE,
		       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);

		अगर (lradc->touchscreen_wire == MXS_LRADC_TOUCHSCREEN_5WIRE)
			ग_लिखोl(LRADC_CTRL0_MX28_TOUCH_SCREEN_TYPE,
			       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);
	पूर्ण
पूर्ण

अटल पूर्णांक mxs_lradc_ts_रेजिस्टर(काष्ठा mxs_lradc_ts *ts)
अणु
	काष्ठा input_dev *input;
	काष्ठा device *dev = ts->dev;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "mxs-lradc-ts";
	input->id.bustype = BUS_HOST;
	input->खोलो = mxs_lradc_ts_खोलो;
	input->बंद = mxs_lradc_ts_बंद;

	__set_bit(INPUT_PROP_सूचीECT, input->propbit);
	input_set_capability(input, EV_KEY, BTN_TOUCH);
	input_set_असल_params(input, ABS_X, 0, LRADC_SINGLE_SAMPLE_MASK, 0, 0);
	input_set_असल_params(input, ABS_Y, 0, LRADC_SINGLE_SAMPLE_MASK, 0, 0);
	input_set_असल_params(input, ABS_PRESSURE, 0, LRADC_SINGLE_SAMPLE_MASK,
			     0, 0);

	ts->ts_input = input;
	input_set_drvdata(input, ts);

	वापस input_रेजिस्टर_device(input);
पूर्ण

अटल पूर्णांक mxs_lradc_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->parent->of_node;
	काष्ठा mxs_lradc *lradc = dev_get_drvdata(dev->parent);
	काष्ठा mxs_lradc_ts *ts;
	पूर्णांक ret, irq, virq, i;
	u32 ts_wires = 0, adapt;

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ts);

	ts->lradc = lradc;
	ts->dev = dev;
	spin_lock_init(&ts->lock);

	ts->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ts->base))
		वापस PTR_ERR(ts->base);

	ret = of_property_पढ़ो_u32(node, "fsl,lradc-touchscreen-wires",
				   &ts_wires);
	अगर (ret)
		वापस ret;

	अगर (of_property_पढ़ो_u32(node, "fsl,ave-ctrl", &adapt)) अणु
		ts->over_sample_cnt = 4;
	पूर्ण अन्यथा अणु
		अगर (adapt >= 1 && adapt <= 32) अणु
			ts->over_sample_cnt = adapt;
		पूर्ण अन्यथा अणु
			dev_err(ts->dev, "Invalid sample count (%u)\n",
				adapt);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "fsl,ave-delay", &adapt)) अणु
		ts->over_sample_delay = 2;
	पूर्ण अन्यथा अणु
		अगर (adapt >= 2 && adapt <= LRADC_DELAY_DELAY_MASK + 1) अणु
			ts->over_sample_delay = adapt;
		पूर्ण अन्यथा अणु
			dev_err(ts->dev, "Invalid sample delay (%u)\n",
				adapt);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "fsl,settling", &adapt)) अणु
		ts->settling_delay = 10;
	पूर्ण अन्यथा अणु
		अगर (adapt >= 1 && adapt <= LRADC_DELAY_DELAY_MASK) अणु
			ts->settling_delay = adapt;
		पूर्ण अन्यथा अणु
			dev_err(ts->dev, "Invalid settling delay (%u)\n",
				adapt);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = sपंचांगp_reset_block(ts->base);
	अगर (ret)
		वापस ret;

	mxs_lradc_ts_hw_init(ts);

	क्रम (i = 0; i < 3; i++) अणु
		irq = platक्रमm_get_irq_byname(pdev, mxs_lradc_ts_irq_names[i]);
		अगर (irq < 0)
			वापस irq;

		virq = irq_of_parse_and_map(node, irq);

		mxs_lradc_ts_stop(ts);

		ret = devm_request_irq(dev, virq,
				       mxs_lradc_ts_handle_irq,
				       0, mxs_lradc_ts_irq_names[i], ts);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस mxs_lradc_ts_रेजिस्टर(ts);
पूर्ण

अटल काष्ठा platक्रमm_driver mxs_lradc_ts_driver = अणु
	.driver	= अणु
		.name = "mxs-lradc-ts",
	पूर्ण,
	.probe	= mxs_lradc_ts_probe,
पूर्ण;
module_platक्रमm_driver(mxs_lradc_ts_driver);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("Freescale MXS LRADC touchscreen driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mxs-lradc-ts");
