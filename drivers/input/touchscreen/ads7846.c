<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADS7846 based touchscreen and sensor driver
 *
 * Copyright (c) 2005 David Brownell
 * Copyright (c) 2006 Nokia Corporation
 * Various changes: Imre Deak <imre.deak@nokia.com>
 *
 * Using code from:
 *  - corgi_ts.c
 *	Copyright (C) 2004-2005 Riअक्षरd Purdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *	Copyright (C) 2002 MontaVista Software
 *	Copyright (C) 2004 Texas Instruments
 *	Copyright (C) 2005 Dirk Behme
 */
#समावेश <linux/types.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>

/*
 * This code has been heavily tested on a Nokia 770, and lightly
 * tested on other ads7846 devices (OSK/Mistral, Lubbock, Spitz).
 * TSC2046 is just newer ads7846 silicon.
 * Support क्रम ads7843 tested on Aपंचांगel at91sam926x-EK.
 * Support क्रम ads7845 has only been stubbed in.
 * Support क्रम Analog Devices AD7873 and AD7843 tested.
 *
 * IRQ handling needs a workaround because of a लघुcoming in handling
 * edge triggered IRQs on some platक्रमms like the OMAP1/2. These
 * platक्रमms करोn't handle the ARM lazy IRQ disabling properly, thus we
 * have to मुख्यtain our own SW IRQ disabled status. This should be
 * हटाओd as soon as the affected platक्रमm's IRQ handling is fixed.
 *
 * App note sbaa036 talks in more detail about accurate sampling...
 * that ought to help in situations like LCDs inducing noise (which
 * can also be helped by using synch संकेतs) and more generally.
 * This driver tries to utilize the measures described in the app
 * note. The strength of filtering can be set in the board-* specअगरic
 * files.
 */

#घोषणा TS_POLL_DELAY	1	/* ms delay beक्रमe the first sample */
#घोषणा TS_POLL_PERIOD	5	/* ms delay between samples */

/* this driver करोesn't aim at the peak continuous sample rate */
#घोषणा	SAMPLE_BITS	(8 /*cmd*/ + 16 /*sample*/ + 2 /* beक्रमe, after */)

काष्ठा ads7846_buf अणु
	u8 cmd;
	__be16 data;
पूर्ण __packed;

काष्ठा ads7846_buf_layout अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक skip;
पूर्ण;

/*
 * We allocate this separately to aव्योम cache line sharing issues when
 * driver is used with DMA-based SPI controllers (like aपंचांगel_spi) on
 * प्रणालीs where मुख्य memory is not DMA-coherent (most non-x86 boards).
 */
काष्ठा ads7846_packet अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक count_skip;
	अचिन्हित पूर्णांक cmds;
	अचिन्हित पूर्णांक last_cmd_idx;
	काष्ठा ads7846_buf_layout l[5];
	काष्ठा ads7846_buf *rx;
	काष्ठा ads7846_buf *tx;

	काष्ठा ads7846_buf pwrकरोwn_cmd;

	bool ignore;
	u16 x, y, z1, z2;
पूर्ण;

काष्ठा ads7846 अणु
	काष्ठा input_dev	*input;
	अक्षर			phys[32];
	अक्षर			name[32];

	काष्ठा spi_device	*spi;
	काष्ठा regulator	*reg;

#अगर IS_ENABLED(CONFIG_HWMON)
	काष्ठा device		*hwmon;
#पूर्ण_अगर

	u16			model;
	u16			vref_mv;
	u16			vref_delay_usecs;
	u16			x_plate_ohms;
	u16			pressure_max;

	bool			swap_xy;
	bool			use_पूर्णांकernal;

	काष्ठा ads7846_packet	*packet;

	काष्ठा spi_transfer	xfer[18];
	काष्ठा spi_message	msg[5];
	पूर्णांक			msg_count;
	रुको_queue_head_t	रुको;

	bool			penकरोwn;

	पूर्णांक			पढ़ो_cnt;
	पूर्णांक			पढ़ो_rep;
	पूर्णांक			last_पढ़ो;

	u16			debounce_max;
	u16			debounce_tol;
	u16			debounce_rep;

	u16			penirq_recheck_delay_usecs;

	काष्ठा touchscreen_properties core_prop;

	काष्ठा mutex		lock;
	bool			stopped;	/* P: lock */
	bool			disabled;	/* P: lock */
	bool			suspended;	/* P: lock */

	पूर्णांक			(*filter)(व्योम *data, पूर्णांक data_idx, पूर्णांक *val);
	व्योम			*filter_data;
	व्योम			(*filter_cleanup)(व्योम *data);
	पूर्णांक			(*get_penकरोwn_state)(व्योम);
	पूर्णांक			gpio_penकरोwn;

	व्योम			(*रुको_क्रम_sync)(व्योम);
पूर्ण;

/* leave chip selected when we're करोne, क्रम quicker re-select? */
#अगर	0
#घोषणा	CS_CHANGE(xfer)	((xfer).cs_change = 1)
#अन्यथा
#घोषणा	CS_CHANGE(xfer)	((xfer).cs_change = 0)
#पूर्ण_अगर

/*--------------------------------------------------------------------------*/

/* The ADS7846 has touchscreen and other sensors.
 * Earlier ads784x chips are somewhat compatible.
 */
#घोषणा	ADS_START		(1 << 7)
#घोषणा	ADS_A2A1A0_d_y		(1 << 4)	/* dअगरferential */
#घोषणा	ADS_A2A1A0_d_z1		(3 << 4)	/* dअगरferential */
#घोषणा	ADS_A2A1A0_d_z2		(4 << 4)	/* dअगरferential */
#घोषणा	ADS_A2A1A0_d_x		(5 << 4)	/* dअगरferential */
#घोषणा	ADS_A2A1A0_temp0	(0 << 4)	/* non-dअगरferential */
#घोषणा	ADS_A2A1A0_vbatt	(2 << 4)	/* non-dअगरferential */
#घोषणा	ADS_A2A1A0_vaux		(6 << 4)	/* non-dअगरferential */
#घोषणा	ADS_A2A1A0_temp1	(7 << 4)	/* non-dअगरferential */
#घोषणा	ADS_8_BIT		(1 << 3)
#घोषणा	ADS_12_BIT		(0 << 3)
#घोषणा	ADS_SER			(1 << 2)	/* non-dअगरferential */
#घोषणा	ADS_DFR			(0 << 2)	/* dअगरferential */
#घोषणा	ADS_PD10_PDOWN		(0 << 0)	/* low घातer mode + penirq */
#घोषणा	ADS_PD10_ADC_ON		(1 << 0)	/* ADC on */
#घोषणा	ADS_PD10_REF_ON		(2 << 0)	/* vREF on + penirq */
#घोषणा	ADS_PD10_ALL_ON		(3 << 0)	/* ADC + vREF on */

#घोषणा	MAX_12BIT	((1<<12)-1)

/* leave ADC घातered up (disables penirq) between dअगरferential samples */
#घोषणा	READ_12BIT_DFR(x, adc, vref) (ADS_START | ADS_A2A1A0_d_ ## x \
	| ADS_12_BIT | ADS_DFR | \
	(adc ? ADS_PD10_ADC_ON : 0) | (vref ? ADS_PD10_REF_ON : 0))

#घोषणा	READ_Y(vref)	(READ_12BIT_DFR(y,  1, vref))
#घोषणा	READ_Z1(vref)	(READ_12BIT_DFR(z1, 1, vref))
#घोषणा	READ_Z2(vref)	(READ_12BIT_DFR(z2, 1, vref))
#घोषणा	READ_X(vref)	(READ_12BIT_DFR(x,  1, vref))
#घोषणा	PWRDOWN		(READ_12BIT_DFR(y,  0, 0))	/* LAST */

/* single-ended samples need to first घातer up reference voltage;
 * we leave both ADC and VREF घातered
 */
#घोषणा	READ_12BIT_SER(x) (ADS_START | ADS_A2A1A0_ ## x \
	| ADS_12_BIT | ADS_SER)

#घोषणा	REF_ON	(READ_12BIT_DFR(x, 1, 1))
#घोषणा	REF_OFF	(READ_12BIT_DFR(y, 0, 0))

/* Order commands in the most optimal way to reduce Vref चयनing and
 * settling समय:
 * Measure:  X; Vref: X+, X-; IN: Y+
 * Measure:  Y; Vref: Y+, Y-; IN: X+
 * Measure: Z1; Vref: Y+, X-; IN: X+
 * Measure: Z2; Vref: Y+, X-; IN: Y-
 */
क्रमागत ads7846_cmds अणु
	ADS7846_X,
	ADS7846_Y,
	ADS7846_Z1,
	ADS7846_Z2,
	ADS7846_PWDOWN,
पूर्ण;

अटल पूर्णांक get_penकरोwn_state(काष्ठा ads7846 *ts)
अणु
	अगर (ts->get_penकरोwn_state)
		वापस ts->get_penकरोwn_state();

	वापस !gpio_get_value(ts->gpio_penकरोwn);
पूर्ण

अटल व्योम ads7846_report_pen_up(काष्ठा ads7846 *ts)
अणु
	काष्ठा input_dev *input = ts->input;

	input_report_key(input, BTN_TOUCH, 0);
	input_report_असल(input, ABS_PRESSURE, 0);
	input_sync(input);

	ts->penकरोwn = false;
	dev_vdbg(&ts->spi->dev, "UP\n");
पूर्ण

/* Must be called with ts->lock held */
अटल व्योम ads7846_stop(काष्ठा ads7846 *ts)
अणु
	अगर (!ts->disabled && !ts->suspended) अणु
		/* Signal IRQ thपढ़ो to stop polling and disable the handler. */
		ts->stopped = true;
		mb();
		wake_up(&ts->रुको);
		disable_irq(ts->spi->irq);
	पूर्ण
पूर्ण

/* Must be called with ts->lock held */
अटल व्योम ads7846_restart(काष्ठा ads7846 *ts)
अणु
	अगर (!ts->disabled && !ts->suspended) अणु
		/* Check अगर pen was released since last stop */
		अगर (ts->penकरोwn && !get_penकरोwn_state(ts))
			ads7846_report_pen_up(ts);

		/* Tell IRQ thपढ़ो that it may poll the device. */
		ts->stopped = false;
		mb();
		enable_irq(ts->spi->irq);
	पूर्ण
पूर्ण

/* Must be called with ts->lock held */
अटल व्योम __ads7846_disable(काष्ठा ads7846 *ts)
अणु
	ads7846_stop(ts);
	regulator_disable(ts->reg);

	/*
	 * We know the chip's in low घातer mode since we always
	 * leave it that way after every request
	 */
पूर्ण

/* Must be called with ts->lock held */
अटल व्योम __ads7846_enable(काष्ठा ads7846 *ts)
अणु
	पूर्णांक error;

	error = regulator_enable(ts->reg);
	अगर (error != 0)
		dev_err(&ts->spi->dev, "Failed to enable supply: %d\n", error);

	ads7846_restart(ts);
पूर्ण

अटल व्योम ads7846_disable(काष्ठा ads7846 *ts)
अणु
	mutex_lock(&ts->lock);

	अगर (!ts->disabled) अणु

		अगर  (!ts->suspended)
			__ads7846_disable(ts);

		ts->disabled = true;
	पूर्ण

	mutex_unlock(&ts->lock);
पूर्ण

अटल व्योम ads7846_enable(काष्ठा ads7846 *ts)
अणु
	mutex_lock(&ts->lock);

	अगर (ts->disabled) अणु

		ts->disabled = false;

		अगर (!ts->suspended)
			__ads7846_enable(ts);
	पूर्ण

	mutex_unlock(&ts->lock);
पूर्ण

/*--------------------------------------------------------------------------*/

/*
 * Non-touchscreen sensors only use single-ended conversions.
 * The range is GND..vREF. The ads7843 and ads7835 must use बाह्यal vREF;
 * ads7846 lets that pin be unconnected, to use पूर्णांकernal vREF.
 */

काष्ठा ser_req अणु
	u8			ref_on;
	u8			command;
	u8			ref_off;
	u16			scratch;
	काष्ठा spi_message	msg;
	काष्ठा spi_transfer	xfer[6];
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	__be16 sample ____cacheline_aligned;
पूर्ण;

काष्ठा ads7845_ser_req अणु
	u8			command[3];
	काष्ठा spi_message	msg;
	काष्ठा spi_transfer	xfer[2];
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	u8 sample[3] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ads7846_पढ़ो12_ser(काष्ठा device *dev, अचिन्हित command)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा ads7846 *ts = dev_get_drvdata(dev);
	काष्ठा ser_req *req;
	पूर्णांक status;

	req = kzalloc(माप *req, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	spi_message_init(&req->msg);

	/* maybe turn on पूर्णांकernal vREF, and let it settle */
	अगर (ts->use_पूर्णांकernal) अणु
		req->ref_on = REF_ON;
		req->xfer[0].tx_buf = &req->ref_on;
		req->xfer[0].len = 1;
		spi_message_add_tail(&req->xfer[0], &req->msg);

		req->xfer[1].rx_buf = &req->scratch;
		req->xfer[1].len = 2;

		/* क्रम 1uF, settle क्रम 800 usec; no cap, 100 usec.  */
		req->xfer[1].delay.value = ts->vref_delay_usecs;
		req->xfer[1].delay.unit = SPI_DELAY_UNIT_USECS;
		spi_message_add_tail(&req->xfer[1], &req->msg);

		/* Enable reference voltage */
		command |= ADS_PD10_REF_ON;
	पूर्ण

	/* Enable ADC in every हाल */
	command |= ADS_PD10_ADC_ON;

	/* take sample */
	req->command = (u8) command;
	req->xfer[2].tx_buf = &req->command;
	req->xfer[2].len = 1;
	spi_message_add_tail(&req->xfer[2], &req->msg);

	req->xfer[3].rx_buf = &req->sample;
	req->xfer[3].len = 2;
	spi_message_add_tail(&req->xfer[3], &req->msg);

	/* REVISIT:  take a few more samples, and compare ... */

	/* converter in low घातer mode & enable PENIRQ */
	req->ref_off = PWRDOWN;
	req->xfer[4].tx_buf = &req->ref_off;
	req->xfer[4].len = 1;
	spi_message_add_tail(&req->xfer[4], &req->msg);

	req->xfer[5].rx_buf = &req->scratch;
	req->xfer[5].len = 2;
	CS_CHANGE(req->xfer[5]);
	spi_message_add_tail(&req->xfer[5], &req->msg);

	mutex_lock(&ts->lock);
	ads7846_stop(ts);
	status = spi_sync(spi, &req->msg);
	ads7846_restart(ts);
	mutex_unlock(&ts->lock);

	अगर (status == 0) अणु
		/* on-wire is a must-ignore bit, a BE12 value, then padding */
		status = be16_to_cpu(req->sample);
		status = status >> 3;
		status &= 0x0fff;
	पूर्ण

	kमुक्त(req);
	वापस status;
पूर्ण

अटल पूर्णांक ads7845_पढ़ो12_ser(काष्ठा device *dev, अचिन्हित command)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा ads7846 *ts = dev_get_drvdata(dev);
	काष्ठा ads7845_ser_req *req;
	पूर्णांक status;

	req = kzalloc(माप *req, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	spi_message_init(&req->msg);

	req->command[0] = (u8) command;
	req->xfer[0].tx_buf = req->command;
	req->xfer[0].rx_buf = req->sample;
	req->xfer[0].len = 3;
	spi_message_add_tail(&req->xfer[0], &req->msg);

	mutex_lock(&ts->lock);
	ads7846_stop(ts);
	status = spi_sync(spi, &req->msg);
	ads7846_restart(ts);
	mutex_unlock(&ts->lock);

	अगर (status == 0) अणु
		/* BE12 value, then padding */
		status = get_unaligned_be16(&req->sample[1]);
		status = status >> 3;
		status &= 0x0fff;
	पूर्ण

	kमुक्त(req);
	वापस status;
पूर्ण

#अगर IS_ENABLED(CONFIG_HWMON)

#घोषणा SHOW(name, var, adjust) अटल sमाप_प्रकार \
name ## _show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा ads7846 *ts = dev_get_drvdata(dev); \
	sमाप_प्रकार v = ads7846_पढ़ो12_ser(&ts->spi->dev, \
			READ_12BIT_SER(var)); \
	अगर (v < 0) \
		वापस v; \
	वापस प्र_लिखो(buf, "%u\n", adjust(ts, v)); \
पूर्ण \
अटल DEVICE_ATTR(name, S_IRUGO, name ## _show, शून्य);


/* Sysfs conventions report temperatures in millidegrees Celsius.
 * ADS7846 could use the low-accuracy two-sample scheme, but can't करो the high
 * accuracy scheme without calibration data.  For now we won't try either;
 * userspace sees raw sensor values, and must scale/calibrate appropriately.
 */
अटल अंतरभूत अचिन्हित null_adjust(काष्ठा ads7846 *ts, sमाप_प्रकार v)
अणु
	वापस v;
पूर्ण

SHOW(temp0, temp0, null_adjust)		/* temp1_input */
SHOW(temp1, temp1, null_adjust)		/* temp2_input */


/* sysfs conventions report voltages in millivolts.  We can convert voltages
 * अगर we know vREF.  userspace may need to scale vAUX to match the board's
 * बाह्यal resistors; we assume that vBATT only uses the पूर्णांकernal ones.
 */
अटल अंतरभूत अचिन्हित vaux_adjust(काष्ठा ads7846 *ts, sमाप_प्रकार v)
अणु
	अचिन्हित retval = v;

	/* बाह्यal resistors may scale vAUX पूर्णांकo 0..vREF */
	retval *= ts->vref_mv;
	retval = retval >> 12;

	वापस retval;
पूर्ण

अटल अंतरभूत अचिन्हित vbatt_adjust(काष्ठा ads7846 *ts, sमाप_प्रकार v)
अणु
	अचिन्हित retval = vaux_adjust(ts, v);

	/* ads7846 has a resistor ladder to scale this संकेत करोwn */
	अगर (ts->model == 7846)
		retval *= 4;

	वापस retval;
पूर्ण

SHOW(in0_input, vaux, vaux_adjust)
SHOW(in1_input, vbatt, vbatt_adjust)

अटल umode_t ads7846_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				  पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा ads7846 *ts = dev_get_drvdata(dev);

	अगर (ts->model == 7843 && index < 2)	/* in0, in1 */
		वापस 0;
	अगर (ts->model == 7845 && index != 2)	/* in0 */
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute *ads7846_attributes[] = अणु
	&dev_attr_temp0.attr,		/* 0 */
	&dev_attr_temp1.attr,		/* 1 */
	&dev_attr_in0_input.attr,	/* 2 */
	&dev_attr_in1_input.attr,	/* 3 */
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ads7846_attr_group = अणु
	.attrs = ads7846_attributes,
	.is_visible = ads7846_is_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(ads7846_attr);

अटल पूर्णांक ads784x_hwmon_रेजिस्टर(काष्ठा spi_device *spi, काष्ठा ads7846 *ts)
अणु
	/* hwmon sensors need a reference voltage */
	चयन (ts->model) अणु
	हाल 7846:
		अगर (!ts->vref_mv) अणु
			dev_dbg(&spi->dev, "assuming 2.5V internal vREF\n");
			ts->vref_mv = 2500;
			ts->use_पूर्णांकernal = true;
		पूर्ण
		अवरोध;
	हाल 7845:
	हाल 7843:
		अगर (!ts->vref_mv) अणु
			dev_warn(&spi->dev,
				"external vREF for ADS%d not specified\n",
				ts->model);
			वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण

	ts->hwmon = hwmon_device_रेजिस्टर_with_groups(&spi->dev, spi->modalias,
						      ts, ads7846_attr_groups);

	वापस PTR_ERR_OR_ZERO(ts->hwmon);
पूर्ण

अटल व्योम ads784x_hwmon_unरेजिस्टर(काष्ठा spi_device *spi,
				     काष्ठा ads7846 *ts)
अणु
	अगर (ts->hwmon)
		hwmon_device_unरेजिस्टर(ts->hwmon);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक ads784x_hwmon_रेजिस्टर(काष्ठा spi_device *spi,
					 काष्ठा ads7846 *ts)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ads784x_hwmon_unरेजिस्टर(काष्ठा spi_device *spi,
					    काष्ठा ads7846 *ts)
अणु
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार ads7846_pen_करोwn_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ads7846 *ts = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", ts->penकरोwn);
पूर्ण

अटल DEVICE_ATTR(pen_करोwn, S_IRUGO, ads7846_pen_करोwn_show, शून्य);

अटल sमाप_प्रकार ads7846_disable_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ads7846 *ts = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", ts->disabled);
पूर्ण

अटल sमाप_प्रकार ads7846_disable_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ads7846 *ts = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &i);
	अगर (err)
		वापस err;

	अगर (i)
		ads7846_disable(ts);
	अन्यथा
		ads7846_enable(ts);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(disable, 0664, ads7846_disable_show, ads7846_disable_store);

अटल काष्ठा attribute *ads784x_attributes[] = अणु
	&dev_attr_pen_करोwn.attr,
	&dev_attr_disable.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ads784x_attr_group = अणु
	.attrs = ads784x_attributes,
पूर्ण;

/*--------------------------------------------------------------------------*/

अटल व्योम null_रुको_क्रम_sync(व्योम)
अणु
पूर्ण

अटल पूर्णांक ads7846_debounce_filter(व्योम *ads, पूर्णांक data_idx, पूर्णांक *val)
अणु
	काष्ठा ads7846 *ts = ads;

	अगर (!ts->पढ़ो_cnt || (असल(ts->last_पढ़ो - *val) > ts->debounce_tol)) अणु
		/* Start over collecting consistent पढ़ोings. */
		ts->पढ़ो_rep = 0;
		/*
		 * Repeat it, अगर this was the first पढ़ो or the पढ़ो
		 * wasn't consistent enough.
		 */
		अगर (ts->पढ़ो_cnt < ts->debounce_max) अणु
			ts->last_पढ़ो = *val;
			ts->पढ़ो_cnt++;
			वापस ADS7846_FILTER_REPEAT;
		पूर्ण अन्यथा अणु
			/*
			 * Maximum number of debouncing reached and still
			 * not enough number of consistent पढ़ोings. Abort
			 * the whole sample, repeat it in the next sampling
			 * period.
			 */
			ts->पढ़ो_cnt = 0;
			वापस ADS7846_FILTER_IGNORE;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (++ts->पढ़ो_rep > ts->debounce_rep) अणु
			/*
			 * Got a good पढ़ोing क्रम this coordinate,
			 * go क्रम the next one.
			 */
			ts->पढ़ो_cnt = 0;
			ts->पढ़ो_rep = 0;
			वापस ADS7846_FILTER_OK;
		पूर्ण अन्यथा अणु
			/* Read more values that are consistent. */
			ts->पढ़ो_cnt++;
			वापस ADS7846_FILTER_REPEAT;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ads7846_no_filter(व्योम *ads, पूर्णांक data_idx, पूर्णांक *val)
अणु
	वापस ADS7846_FILTER_OK;
पूर्ण

अटल पूर्णांक ads7846_get_value(काष्ठा ads7846_buf *buf)
अणु
	पूर्णांक value;

	value = be16_to_cpup(&buf->data);

	/* enक्रमce ADC output is 12 bits width */
	वापस (value >> 3) & 0xfff;
पूर्ण

अटल व्योम ads7846_set_cmd_val(काष्ठा ads7846 *ts, क्रमागत ads7846_cmds cmd_idx,
				u16 val)
अणु
	काष्ठा ads7846_packet *packet = ts->packet;

	चयन (cmd_idx) अणु
	हाल ADS7846_Y:
		packet->y = val;
		अवरोध;
	हाल ADS7846_X:
		packet->x = val;
		अवरोध;
	हाल ADS7846_Z1:
		packet->z1 = val;
		अवरोध;
	हाल ADS7846_Z2:
		packet->z2 = val;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल u8 ads7846_get_cmd(क्रमागत ads7846_cmds cmd_idx, पूर्णांक vref)
अणु
	चयन (cmd_idx) अणु
	हाल ADS7846_Y:
		वापस READ_Y(vref);
	हाल ADS7846_X:
		वापस READ_X(vref);

	/* 7846 specअगरic commands  */
	हाल ADS7846_Z1:
		वापस READ_Z1(vref);
	हाल ADS7846_Z2:
		वापस READ_Z2(vref);
	हाल ADS7846_PWDOWN:
		वापस PWRDOWN;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ads7846_cmd_need_settle(क्रमागत ads7846_cmds cmd_idx)
अणु
	चयन (cmd_idx) अणु
	हाल ADS7846_X:
	हाल ADS7846_Y:
	हाल ADS7846_Z1:
	हाल ADS7846_Z2:
		वापस true;
	हाल ADS7846_PWDOWN:
		वापस false;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ads7846_filter(काष्ठा ads7846 *ts)
अणु
	काष्ठा ads7846_packet *packet = ts->packet;
	पूर्णांक action;
	पूर्णांक val;
	अचिन्हित पूर्णांक cmd_idx, b;

	packet->ignore = false;
	क्रम (cmd_idx = packet->last_cmd_idx; cmd_idx < packet->cmds - 1; cmd_idx++) अणु
		काष्ठा ads7846_buf_layout *l = &packet->l[cmd_idx];

		packet->last_cmd_idx = cmd_idx;

		क्रम (b = l->skip; b < l->count; b++) अणु
			val = ads7846_get_value(&packet->rx[l->offset + b]);

			action = ts->filter(ts->filter_data, cmd_idx, &val);
			अगर (action == ADS7846_FILTER_REPEAT) अणु
				अगर (b == l->count - 1)
					वापस -EAGAIN;
			पूर्ण अन्यथा अगर (action == ADS7846_FILTER_OK) अणु
				ads7846_set_cmd_val(ts, cmd_idx, val);
				अवरोध;
			पूर्ण अन्यथा अणु
				packet->ignore = true;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ads7846_पढ़ो_state(काष्ठा ads7846 *ts)
अणु
	काष्ठा ads7846_packet *packet = ts->packet;
	काष्ठा spi_message *m;
	पूर्णांक msg_idx = 0;
	पूर्णांक error;

	packet->last_cmd_idx = 0;

	जबतक (true) अणु
		ts->रुको_क्रम_sync();

		m = &ts->msg[msg_idx];
		error = spi_sync(ts->spi, m);
		अगर (error) अणु
			dev_err(&ts->spi->dev, "spi_sync --> %d\n", error);
			packet->ignore = true;
			वापस;
		पूर्ण

		error = ads7846_filter(ts);
		अगर (error)
			जारी;

		वापस;
	पूर्ण
पूर्ण

अटल व्योम ads7846_report_state(काष्ठा ads7846 *ts)
अणु
	काष्ठा ads7846_packet *packet = ts->packet;
	अचिन्हित पूर्णांक Rt;
	u16 x, y, z1, z2;

	x = packet->x;
	y = packet->y;
	अगर (ts->model == 7845) अणु
		z1 = 0;
		z2 = 0;
	पूर्ण अन्यथा अणु
		z1 = packet->z1;
		z2 = packet->z2;
	पूर्ण

	/* range filtering */
	अगर (x == MAX_12BIT)
		x = 0;

	अगर (ts->model == 7843) अणु
		Rt = ts->pressure_max / 2;
	पूर्ण अन्यथा अगर (ts->model == 7845) अणु
		अगर (get_penकरोwn_state(ts))
			Rt = ts->pressure_max / 2;
		अन्यथा
			Rt = 0;
		dev_vdbg(&ts->spi->dev, "x/y: %d/%d, PD %d\n", x, y, Rt);
	पूर्ण अन्यथा अगर (likely(x && z1)) अणु
		/* compute touch pressure resistance using equation #2 */
		Rt = z2;
		Rt -= z1;
		Rt *= ts->x_plate_ohms;
		Rt = DIV_ROUND_CLOSEST(Rt, 16);
		Rt *= x;
		Rt /= z1;
		Rt = DIV_ROUND_CLOSEST(Rt, 256);
	पूर्ण अन्यथा अणु
		Rt = 0;
	पूर्ण

	/*
	 * Sample found inconsistent by debouncing or pressure is beyond
	 * the maximum. Don't report it to user space, repeat at least
	 * once more the measurement
	 */
	अगर (packet->ignore || Rt > ts->pressure_max) अणु
		dev_vdbg(&ts->spi->dev, "ignored %d pressure %d\n",
			 packet->ignore, Rt);
		वापस;
	पूर्ण

	/*
	 * Maybe check the penकरोwn state beक्रमe reporting. This discards
	 * false पढ़ोings when the pen is lअगरted.
	 */
	अगर (ts->penirq_recheck_delay_usecs) अणु
		udelay(ts->penirq_recheck_delay_usecs);
		अगर (!get_penकरोwn_state(ts))
			Rt = 0;
	पूर्ण

	/*
	 * NOTE: We can't rely on the pressure to determine the pen करोwn
	 * state, even this controller has a pressure sensor. The pressure
	 * value can fluctuate क्रम quite a जबतक after lअगरting the pen and
	 * in some हालs may not even settle at the expected value.
	 *
	 * The only safe way to check क्रम the pen up condition is in the
	 * समयr by पढ़ोing the pen संकेत state (it's a GPIO _and_ IRQ).
	 */
	अगर (Rt) अणु
		काष्ठा input_dev *input = ts->input;

		अगर (!ts->penकरोwn) अणु
			input_report_key(input, BTN_TOUCH, 1);
			ts->penकरोwn = true;
			dev_vdbg(&ts->spi->dev, "DOWN\n");
		पूर्ण

		touchscreen_report_pos(input, &ts->core_prop, x, y, false);
		input_report_असल(input, ABS_PRESSURE, ts->pressure_max - Rt);

		input_sync(input);
		dev_vdbg(&ts->spi->dev, "%4d/%4d/%4d\n", x, y, Rt);
	पूर्ण
पूर्ण

अटल irqवापस_t ads7846_hard_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा ads7846 *ts = handle;

	वापस get_penकरोwn_state(ts) ? IRQ_WAKE_THREAD : IRQ_HANDLED;
पूर्ण


अटल irqवापस_t ads7846_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा ads7846 *ts = handle;

	/* Start with a small delay beक्रमe checking penकरोwn state */
	msleep(TS_POLL_DELAY);

	जबतक (!ts->stopped && get_penकरोwn_state(ts)) अणु

		/* pen is करोwn, जारी with the measurement */
		ads7846_पढ़ो_state(ts);

		अगर (!ts->stopped)
			ads7846_report_state(ts);

		रुको_event_समयout(ts->रुको, ts->stopped,
				   msecs_to_jअगरfies(TS_POLL_PERIOD));
	पूर्ण

	अगर (ts->penकरोwn && !ts->stopped)
		ads7846_report_pen_up(ts);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __maybe_unused ads7846_suspend(काष्ठा device *dev)
अणु
	काष्ठा ads7846 *ts = dev_get_drvdata(dev);

	mutex_lock(&ts->lock);

	अगर (!ts->suspended) अणु

		अगर (!ts->disabled)
			__ads7846_disable(ts);

		अगर (device_may_wakeup(&ts->spi->dev))
			enable_irq_wake(ts->spi->irq);

		ts->suspended = true;
	पूर्ण

	mutex_unlock(&ts->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ads7846_resume(काष्ठा device *dev)
अणु
	काष्ठा ads7846 *ts = dev_get_drvdata(dev);

	mutex_lock(&ts->lock);

	अगर (ts->suspended) अणु

		ts->suspended = false;

		अगर (device_may_wakeup(&ts->spi->dev))
			disable_irq_wake(ts->spi->irq);

		अगर (!ts->disabled)
			__ads7846_enable(ts);
	पूर्ण

	mutex_unlock(&ts->lock);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ads7846_pm, ads7846_suspend, ads7846_resume);

अटल पूर्णांक ads7846_setup_penकरोwn(काष्ठा spi_device *spi,
				 काष्ठा ads7846 *ts,
				 स्थिर काष्ठा ads7846_platक्रमm_data *pdata)
अणु
	पूर्णांक err;

	/*
	 * REVISIT when the irq can be triggered active-low, or अगर क्रम some
	 * reason the touchscreen isn't hooked up, we don't need to access
	 * the penकरोwn state.
	 */

	अगर (pdata->get_penकरोwn_state) अणु
		ts->get_penकरोwn_state = pdata->get_penकरोwn_state;
	पूर्ण अन्यथा अगर (gpio_is_valid(pdata->gpio_penकरोwn)) अणु

		err = gpio_request_one(pdata->gpio_penकरोwn, GPIOF_IN,
				       "ads7846_pendown");
		अगर (err) अणु
			dev_err(&spi->dev,
				"failed to request/setup pendown GPIO%d: %d\n",
				pdata->gpio_penकरोwn, err);
			वापस err;
		पूर्ण

		ts->gpio_penकरोwn = pdata->gpio_penकरोwn;

		अगर (pdata->gpio_penकरोwn_debounce)
			gpio_set_debounce(pdata->gpio_penकरोwn,
					  pdata->gpio_penकरोwn_debounce);
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "no get_pendown_state nor gpio_pendown?\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set up the transfers to पढ़ो touchscreen state; this assumes we
 * use क्रमmula #2 क्रम pressure, not #3.
 */
अटल पूर्णांक ads7846_setup_spi_msg(काष्ठा ads7846 *ts,
				  स्थिर काष्ठा ads7846_platक्रमm_data *pdata)
अणु
	काष्ठा spi_message *m = &ts->msg[0];
	काष्ठा spi_transfer *x = ts->xfer;
	काष्ठा ads7846_packet *packet = ts->packet;
	पूर्णांक vref = pdata->keep_vref_on;
	अचिन्हित पूर्णांक count, offset = 0;
	अचिन्हित पूर्णांक cmd_idx, b;
	अचिन्हित दीर्घ समय;
	माप_प्रकार size = 0;

	/* समय per bit */
	समय = NSEC_PER_SEC / ts->spi->max_speed_hz;

	count = pdata->settle_delay_usecs * NSEC_PER_USEC / समय;
	packet->count_skip = DIV_ROUND_UP(count, 24);

	अगर (ts->debounce_max && ts->debounce_rep)
		/* ads7846_debounce_filter() is making ts->debounce_rep + 2
		 * पढ़ोs. So we need to get all samples क्रम normal हाल. */
		packet->count = ts->debounce_rep + 2;
	अन्यथा
		packet->count = 1;

	अगर (ts->model == 7846)
		packet->cmds = 5; /* x, y, z1, z2, pwकरोwn */
	अन्यथा
		packet->cmds = 3; /* x, y, pwकरोwn */

	क्रम (cmd_idx = 0; cmd_idx < packet->cmds; cmd_idx++) अणु
		काष्ठा ads7846_buf_layout *l = &packet->l[cmd_idx];
		अचिन्हित पूर्णांक max_count;

		अगर (ads7846_cmd_need_settle(cmd_idx))
			max_count = packet->count + packet->count_skip;
		अन्यथा
			max_count = packet->count;

		l->offset = offset;
		offset += max_count;
		l->count = max_count;
		l->skip = packet->count_skip;
		size += माप(*packet->tx) * max_count;
	पूर्ण

	packet->tx = devm_kzalloc(&ts->spi->dev, size, GFP_KERNEL);
	अगर (!packet->tx)
		वापस -ENOMEM;

	packet->rx = devm_kzalloc(&ts->spi->dev, size, GFP_KERNEL);
	अगर (!packet->rx)
		वापस -ENOMEM;

	अगर (ts->model == 7873) अणु
		/*
		 * The AD7873 is almost identical to the ADS7846
		 * keep VREF off during dअगरferential/ratiometric
		 * conversion modes.
		 */
		ts->model = 7846;
		vref = 0;
	पूर्ण

	ts->msg_count = 1;
	spi_message_init(m);
	m->context = ts;

	क्रम (cmd_idx = 0; cmd_idx < packet->cmds; cmd_idx++) अणु
		काष्ठा ads7846_buf_layout *l = &packet->l[cmd_idx];
		u8 cmd = ads7846_get_cmd(cmd_idx, vref);

		क्रम (b = 0; b < l->count; b++)
			packet->tx[l->offset + b].cmd = cmd;
	पूर्ण

	x->tx_buf = packet->tx;
	x->rx_buf = packet->rx;
	x->len = size;
	spi_message_add_tail(x, m);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ads7846_dt_ids[] = अणु
	अणु .compatible = "ti,tsc2046",	.data = (व्योम *) 7846 पूर्ण,
	अणु .compatible = "ti,ads7843",	.data = (व्योम *) 7843 पूर्ण,
	अणु .compatible = "ti,ads7845",	.data = (व्योम *) 7845 पूर्ण,
	अणु .compatible = "ti,ads7846",	.data = (व्योम *) 7846 पूर्ण,
	अणु .compatible = "ti,ads7873",	.data = (व्योम *) 7873 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ads7846_dt_ids);

अटल स्थिर काष्ठा ads7846_platक्रमm_data *ads7846_probe_dt(काष्ठा device *dev)
अणु
	काष्ठा ads7846_platक्रमm_data *pdata;
	काष्ठा device_node *node = dev->of_node;
	स्थिर काष्ठा of_device_id *match;
	u32 value;

	अगर (!node) अणु
		dev_err(dev, "Device does not have associated DT data\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	match = of_match_device(ads7846_dt_ids, dev);
	अगर (!match) अणु
		dev_err(dev, "Unknown device model\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->model = (अचिन्हित दीर्घ)match->data;

	of_property_पढ़ो_u16(node, "ti,vref-delay-usecs",
			     &pdata->vref_delay_usecs);
	of_property_पढ़ो_u16(node, "ti,vref-mv", &pdata->vref_mv);
	pdata->keep_vref_on = of_property_पढ़ो_bool(node, "ti,keep-vref-on");

	pdata->swap_xy = of_property_पढ़ो_bool(node, "ti,swap-xy");

	of_property_पढ़ो_u16(node, "ti,settle-delay-usec",
			     &pdata->settle_delay_usecs);
	of_property_पढ़ो_u16(node, "ti,penirq-recheck-delay-usecs",
			     &pdata->penirq_recheck_delay_usecs);

	of_property_पढ़ो_u16(node, "ti,x-plate-ohms", &pdata->x_plate_ohms);
	of_property_पढ़ो_u16(node, "ti,y-plate-ohms", &pdata->y_plate_ohms);

	of_property_पढ़ो_u16(node, "ti,x-min", &pdata->x_min);
	of_property_पढ़ो_u16(node, "ti,y-min", &pdata->y_min);
	of_property_पढ़ो_u16(node, "ti,x-max", &pdata->x_max);
	of_property_पढ़ो_u16(node, "ti,y-max", &pdata->y_max);

	/*
	 * touchscreen-max-pressure माला_लो parsed during
	 * touchscreen_parse_properties()
	 */
	of_property_पढ़ो_u16(node, "ti,pressure-min", &pdata->pressure_min);
	अगर (!of_property_पढ़ो_u32(node, "touchscreen-min-pressure", &value))
		pdata->pressure_min = (u16) value;
	of_property_पढ़ो_u16(node, "ti,pressure-max", &pdata->pressure_max);

	of_property_पढ़ो_u16(node, "ti,debounce-max", &pdata->debounce_max);
	अगर (!of_property_पढ़ो_u32(node, "touchscreen-average-samples", &value))
		pdata->debounce_max = (u16) value;
	of_property_पढ़ो_u16(node, "ti,debounce-tol", &pdata->debounce_tol);
	of_property_पढ़ो_u16(node, "ti,debounce-rep", &pdata->debounce_rep);

	of_property_पढ़ो_u32(node, "ti,pendown-gpio-debounce",
			     &pdata->gpio_penकरोwn_debounce);

	pdata->wakeup = of_property_पढ़ो_bool(node, "wakeup-source") ||
			of_property_पढ़ो_bool(node, "linux,wakeup");

	pdata->gpio_penकरोwn = of_get_named_gpio(dev->of_node, "pendown-gpio", 0);

	वापस pdata;
पूर्ण
#अन्यथा
अटल स्थिर काष्ठा ads7846_platक्रमm_data *ads7846_probe_dt(काष्ठा device *dev)
अणु
	dev_err(dev, "no platform data defined\n");
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ads7846_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा ads7846_platक्रमm_data *pdata;
	काष्ठा ads7846 *ts;
	काष्ठा ads7846_packet *packet;
	काष्ठा input_dev *input_dev;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक err;

	अगर (!spi->irq) अणु
		dev_dbg(&spi->dev, "no IRQ?\n");
		वापस -EINVAL;
	पूर्ण

	/* करोn't exceed max specअगरied sample rate */
	अगर (spi->max_speed_hz > (125000 * SAMPLE_BITS)) अणु
		dev_err(&spi->dev, "f(sample) %d KHz?\n",
				(spi->max_speed_hz/SAMPLE_BITS)/1000);
		वापस -EINVAL;
	पूर्ण

	/*
	 * We'd set TX word size 8 bits and RX word size to 13 bits ... except
	 * that even अगर the hardware can करो that, the SPI controller driver
	 * may not.  So we stick to very-portable 8 bit words, both RX and TX.
	 */
	spi->bits_per_word = 8;
	spi->mode &= ~SPI_MODE_X_MASK;
	spi->mode |= SPI_MODE_0;
	err = spi_setup(spi);
	अगर (err < 0)
		वापस err;

	ts = kzalloc(माप(काष्ठा ads7846), GFP_KERNEL);
	packet = kzalloc(माप(काष्ठा ads7846_packet), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!ts || !packet || !input_dev) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	spi_set_drvdata(spi, ts);

	ts->packet = packet;
	ts->spi = spi;
	ts->input = input_dev;

	mutex_init(&ts->lock);
	init_रुकोqueue_head(&ts->रुको);

	pdata = dev_get_platdata(&spi->dev);
	अगर (!pdata) अणु
		pdata = ads7846_probe_dt(&spi->dev);
		अगर (IS_ERR(pdata)) अणु
			err = PTR_ERR(pdata);
			जाओ err_मुक्त_mem;
		पूर्ण
	पूर्ण

	ts->model = pdata->model ? : 7846;
	ts->vref_delay_usecs = pdata->vref_delay_usecs ? : 100;
	ts->x_plate_ohms = pdata->x_plate_ohms ? : 400;
	ts->vref_mv = pdata->vref_mv;

	अगर (pdata->filter != शून्य) अणु
		अगर (pdata->filter_init != शून्य) अणु
			err = pdata->filter_init(pdata, &ts->filter_data);
			अगर (err < 0)
				जाओ err_मुक्त_mem;
		पूर्ण
		ts->filter = pdata->filter;
		ts->filter_cleanup = pdata->filter_cleanup;
	पूर्ण अन्यथा अगर (pdata->debounce_max) अणु
		ts->debounce_max = pdata->debounce_max;
		अगर (ts->debounce_max < 2)
			ts->debounce_max = 2;
		ts->debounce_tol = pdata->debounce_tol;
		ts->debounce_rep = pdata->debounce_rep;
		ts->filter = ads7846_debounce_filter;
		ts->filter_data = ts;
	पूर्ण अन्यथा अणु
		ts->filter = ads7846_no_filter;
	पूर्ण

	err = ads7846_setup_penकरोwn(spi, ts, pdata);
	अगर (err)
		जाओ err_cleanup_filter;

	अगर (pdata->penirq_recheck_delay_usecs)
		ts->penirq_recheck_delay_usecs =
				pdata->penirq_recheck_delay_usecs;

	ts->रुको_क्रम_sync = pdata->रुको_क्रम_sync ? : null_रुको_क्रम_sync;

	snम_लिखो(ts->phys, माप(ts->phys), "%s/input0", dev_name(&spi->dev));
	snम_लिखो(ts->name, माप(ts->name), "ADS%d Touchscreen", ts->model);

	input_dev->name = ts->name;
	input_dev->phys = ts->phys;
	input_dev->dev.parent = &spi->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X,
			pdata->x_min ? : 0,
			pdata->x_max ? : MAX_12BIT,
			0, 0);
	input_set_असल_params(input_dev, ABS_Y,
			pdata->y_min ? : 0,
			pdata->y_max ? : MAX_12BIT,
			0, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE,
			pdata->pressure_min, pdata->pressure_max, 0, 0);

	/*
	 * Parse common framework properties. Must be करोne here to ensure the
	 * correct behaviour in हाल of using the legacy venकरोr bindings. The
	 * general binding value overrides the venकरोr specअगरic one.
	 */
	touchscreen_parse_properties(ts->input, false, &ts->core_prop);
	ts->pressure_max = input_असल_get_max(input_dev, ABS_PRESSURE) ? : ~0;

	/*
	 * Check अगर legacy ti,swap-xy binding is used instead of
	 * touchscreen-swapped-x-y
	 */
	अगर (!ts->core_prop.swap_x_y && pdata->swap_xy) अणु
		swap(input_dev->असलinfo[ABS_X], input_dev->असलinfo[ABS_Y]);
		ts->core_prop.swap_x_y = true;
	पूर्ण

	ads7846_setup_spi_msg(ts, pdata);

	ts->reg = regulator_get(&spi->dev, "vcc");
	अगर (IS_ERR(ts->reg)) अणु
		err = PTR_ERR(ts->reg);
		dev_err(&spi->dev, "unable to get regulator: %d\n", err);
		जाओ err_मुक्त_gpio;
	पूर्ण

	err = regulator_enable(ts->reg);
	अगर (err) अणु
		dev_err(&spi->dev, "unable to enable regulator: %d\n", err);
		जाओ err_put_regulator;
	पूर्ण

	irq_flags = pdata->irq_flags ? : IRQF_TRIGGER_FALLING;
	irq_flags |= IRQF_ONESHOT;

	err = request_thपढ़ोed_irq(spi->irq, ads7846_hard_irq, ads7846_irq,
				   irq_flags, spi->dev.driver->name, ts);
	अगर (err && !pdata->irq_flags) अणु
		dev_info(&spi->dev,
			"trying pin change workaround on irq %d\n", spi->irq);
		irq_flags |= IRQF_TRIGGER_RISING;
		err = request_thपढ़ोed_irq(spi->irq,
				  ads7846_hard_irq, ads7846_irq,
				  irq_flags, spi->dev.driver->name, ts);
	पूर्ण

	अगर (err) अणु
		dev_dbg(&spi->dev, "irq %d busy?\n", spi->irq);
		जाओ err_disable_regulator;
	पूर्ण

	err = ads784x_hwmon_रेजिस्टर(spi, ts);
	अगर (err)
		जाओ err_मुक्त_irq;

	dev_info(&spi->dev, "touchscreen, irq %d\n", spi->irq);

	/*
	 * Take a first sample, leaving nPENIRQ active and vREF off; aव्योम
	 * the touchscreen, in हाल it's not connected.
	 */
	अगर (ts->model == 7845)
		ads7845_पढ़ो12_ser(&spi->dev, PWRDOWN);
	अन्यथा
		(व्योम) ads7846_पढ़ो12_ser(&spi->dev, READ_12BIT_SER(vaux));

	err = sysfs_create_group(&spi->dev.kobj, &ads784x_attr_group);
	अगर (err)
		जाओ err_हटाओ_hwmon;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		जाओ err_हटाओ_attr_group;

	device_init_wakeup(&spi->dev, pdata->wakeup);

	/*
	 * If device करोes not carry platक्रमm data we must have allocated it
	 * when parsing DT data.
	 */
	अगर (!dev_get_platdata(&spi->dev))
		devm_kमुक्त(&spi->dev, (व्योम *)pdata);

	वापस 0;

 err_हटाओ_attr_group:
	sysfs_हटाओ_group(&spi->dev.kobj, &ads784x_attr_group);
 err_हटाओ_hwmon:
	ads784x_hwmon_unरेजिस्टर(spi, ts);
 err_मुक्त_irq:
	मुक्त_irq(spi->irq, ts);
 err_disable_regulator:
	regulator_disable(ts->reg);
 err_put_regulator:
	regulator_put(ts->reg);
 err_मुक्त_gpio:
	अगर (!ts->get_penकरोwn_state)
		gpio_मुक्त(ts->gpio_penकरोwn);
 err_cleanup_filter:
	अगर (ts->filter_cleanup)
		ts->filter_cleanup(ts->filter_data);
 err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(packet);
	kमुक्त(ts);
	वापस err;
पूर्ण

अटल पूर्णांक ads7846_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ads7846 *ts = spi_get_drvdata(spi);

	sysfs_हटाओ_group(&spi->dev.kobj, &ads784x_attr_group);

	ads7846_disable(ts);
	मुक्त_irq(ts->spi->irq, ts);

	input_unरेजिस्टर_device(ts->input);

	ads784x_hwmon_unरेजिस्टर(spi, ts);

	regulator_put(ts->reg);

	अगर (!ts->get_penकरोwn_state) अणु
		/*
		 * If we are not using specialized penकरोwn method we must
		 * have been relying on gpio we set up ourselves.
		 */
		gpio_मुक्त(ts->gpio_penकरोwn);
	पूर्ण

	अगर (ts->filter_cleanup)
		ts->filter_cleanup(ts->filter_data);

	kमुक्त(ts->packet);
	kमुक्त(ts);

	dev_dbg(&spi->dev, "unregistered touchscreen\n");

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver ads7846_driver = अणु
	.driver = अणु
		.name	= "ads7846",
		.pm	= &ads7846_pm,
		.of_match_table = of_match_ptr(ads7846_dt_ids),
	पूर्ण,
	.probe		= ads7846_probe,
	.हटाओ		= ads7846_हटाओ,
पूर्ण;

module_spi_driver(ads7846_driver);

MODULE_DESCRIPTION("ADS7846 TouchScreen Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:ads7846");
