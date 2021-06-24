<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Murata ZPA2326 pressure and temperature sensor IIO driver
 *
 * Copyright (c) 2016 Parrot S.A.
 *
 * Author: Gregor Boirie <gregor.boirie@parrot.com>
 */

/**
 * DOC: ZPA2326 theory of operations
 *
 * This driver supports %INDIO_सूचीECT_MODE and %INDIO_BUFFER_TRIGGERED IIO
 * modes.
 * A पूर्णांकernal hardware trigger is also implemented to dispatch रेजिस्टरed IIO
 * trigger consumers upon "sample ready" पूर्णांकerrupts.
 *
 * ZPA2326 hardware supports 2 sampling mode: one shot and continuous.
 *
 * A complete one shot sampling cycle माला_लो device out of low घातer mode,
 * perक्रमms pressure and temperature measurements, then स्वतःmatically चयनes
 * back to low घातer mode. It is meant क्रम on demand sampling with optimal घातer
 * saving at the cost of lower sampling rate and higher software overhead.
 * This is a natural candidate क्रम IIO पढ़ो_raw hook implementation
 * (%INDIO_सूचीECT_MODE). It is also used क्रम triggered buffering support to
 * ensure explicit synchronization with बाह्यal trigger events
 * (%INDIO_BUFFER_TRIGGERED).
 *
 * The continuous mode works according to a periodic hardware measurement
 * process continuously pushing samples पूर्णांकo an पूर्णांकernal hardware FIFO (क्रम
 * pressure samples only). Measurement cycle completion may be संकेतed by a
 * "sample ready" पूर्णांकerrupt.
 * Typical software sequence of operations :
 * - get device out of low घातer mode,
 * - setup hardware sampling period,
 * - at end of period, upon data पढ़ोy पूर्णांकerrupt: pop pressure samples out of
 *   hardware FIFO and fetch temperature sample
 * - when no दीर्घer needed, stop sampling process by putting device पूर्णांकo
 *   low घातer mode.
 * This mode is used to implement %INDIO_BUFFER_TRIGGERED mode अगर device tree
 * declares a valid पूर्णांकerrupt line. In this हाल, the पूर्णांकernal hardware trigger
 * drives acquisition.
 *
 * Note that hardware sampling frequency is taken पूर्णांकo account only when
 * पूर्णांकernal hardware trigger is attached as the highest sampling rate seems to
 * be the most energy efficient.
 *
 * TODO:
 *   preset pressure threshold crossing / IIO events ;
 *   dअगरferential pressure sampling ;
 *   hardware samples averaging.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "zpa2326.h"

/* 200 ms should be enough क्रम the दीर्घest conversion समय in one-shot mode. */
#घोषणा ZPA2326_CONVERSION_JIFFIES (HZ / 5)

/* There should be a 1 ms delay (Tpup) after getting out of reset. */
#घोषणा ZPA2326_TPUP_USEC_MIN      (1000)
#घोषणा ZPA2326_TPUP_USEC_MAX      (2000)

/**
 * काष्ठा zpa2326_frequency - Hardware sampling frequency descriptor
 * @hz : Frequency in Hertz.
 * @odr: Output Data Rate word as expected by %ZPA2326_CTRL_REG3_REG.
 */
काष्ठा zpa2326_frequency अणु
	पूर्णांक hz;
	u16 odr;
पूर्ण;

/*
 * Keep these in strict ascending order: last array entry is expected to
 * correspond to the highest sampling frequency.
 */
अटल स्थिर काष्ठा zpa2326_frequency zpa2326_sampling_frequencies[] = अणु
	अणु .hz = 1,  .odr = 1 << ZPA2326_CTRL_REG3_ODR_SHIFT पूर्ण,
	अणु .hz = 5,  .odr = 5 << ZPA2326_CTRL_REG3_ODR_SHIFT पूर्ण,
	अणु .hz = 11, .odr = 6 << ZPA2326_CTRL_REG3_ODR_SHIFT पूर्ण,
	अणु .hz = 23, .odr = 7 << ZPA2326_CTRL_REG3_ODR_SHIFT पूर्ण,
पूर्ण;

/* Return the highest hardware sampling frequency available. */
अटल स्थिर काष्ठा zpa2326_frequency *zpa2326_highest_frequency(व्योम)
अणु
	वापस &zpa2326_sampling_frequencies[
		ARRAY_SIZE(zpa2326_sampling_frequencies) - 1];
पूर्ण

/**
 * काष्ठा zpa2326_निजी - Per-device पूर्णांकernal निजी state
 * @बारtamp:  Buffered samples पढ़ोy datum.
 * @regmap:     Underlying I2C / SPI bus adapter used to असलtract slave रेजिस्टर
 *              accesses.
 * @result:     Allows sampling logic to get completion status of operations
 *              that पूर्णांकerrupt handlers perक्रमm asynchronously.
 * @data_पढ़ोy: Interrupt handler uses this to wake user context up at sampling
 *              operation completion.
 * @trigger:    Optional hardware / पूर्णांकerrupt driven trigger used to notअगरy
 *              बाह्यal devices a new sample is पढ़ोy.
 * @waken:      Flag indicating whether or not device has just been घातered on.
 * @irq:        Optional पूर्णांकerrupt line: negative or zero अगर not declared पूर्णांकo
 *              DT, in which हाल sampling logic keeps polling status रेजिस्टर
 *              to detect completion.
 * @frequency:  Current hardware sampling frequency.
 * @vref:       Power / voltage reference.
 * @vdd:        Power supply.
 */
काष्ठा zpa2326_निजी अणु
	s64                             बारtamp;
	काष्ठा regmap                  *regmap;
	पूर्णांक                             result;
	काष्ठा completion               data_पढ़ोy;
	काष्ठा iio_trigger             *trigger;
	bool                            waken;
	पूर्णांक                             irq;
	स्थिर काष्ठा zpa2326_frequency *frequency;
	काष्ठा regulator               *vref;
	काष्ठा regulator               *vdd;
पूर्ण;

#घोषणा zpa2326_err(idev, fmt, ...)					\
	dev_err(idev->dev.parent, fmt "\n", ##__VA_ARGS__)

#घोषणा zpa2326_warn(idev, fmt, ...)					\
	dev_warn(idev->dev.parent, fmt "\n", ##__VA_ARGS__)

#घोषणा zpa2326_dbg(idev, fmt, ...)					\
	dev_dbg(idev->dev.parent, fmt "\n", ##__VA_ARGS__)

bool zpa2326_isreg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ZPA2326_REF_P_XL_REG:
	हाल ZPA2326_REF_P_L_REG:
	हाल ZPA2326_REF_P_H_REG:
	हाल ZPA2326_RES_CONF_REG:
	हाल ZPA2326_CTRL_REG0_REG:
	हाल ZPA2326_CTRL_REG1_REG:
	हाल ZPA2326_CTRL_REG2_REG:
	हाल ZPA2326_CTRL_REG3_REG:
	हाल ZPA2326_THS_P_LOW_REG:
	हाल ZPA2326_THS_P_HIGH_REG:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(zpa2326_isreg_ग_लिखोable);

bool zpa2326_isreg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ZPA2326_REF_P_XL_REG:
	हाल ZPA2326_REF_P_L_REG:
	हाल ZPA2326_REF_P_H_REG:
	हाल ZPA2326_DEVICE_ID_REG:
	हाल ZPA2326_RES_CONF_REG:
	हाल ZPA2326_CTRL_REG0_REG:
	हाल ZPA2326_CTRL_REG1_REG:
	हाल ZPA2326_CTRL_REG2_REG:
	हाल ZPA2326_CTRL_REG3_REG:
	हाल ZPA2326_INT_SOURCE_REG:
	हाल ZPA2326_THS_P_LOW_REG:
	हाल ZPA2326_THS_P_HIGH_REG:
	हाल ZPA2326_STATUS_REG:
	हाल ZPA2326_PRESS_OUT_XL_REG:
	हाल ZPA2326_PRESS_OUT_L_REG:
	हाल ZPA2326_PRESS_OUT_H_REG:
	हाल ZPA2326_TEMP_OUT_L_REG:
	हाल ZPA2326_TEMP_OUT_H_REG:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(zpa2326_isreg_पढ़ोable);

bool zpa2326_isreg_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ZPA2326_INT_SOURCE_REG:
	हाल ZPA2326_PRESS_OUT_H_REG:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(zpa2326_isreg_precious);

/**
 * zpa2326_enable_device() - Enable device, i.e. get out of low घातer mode.
 * @indio_dev: The IIO device associated with the hardware to enable.
 *
 * Required to access complete रेजिस्टर space and to perक्रमm any sampling
 * or control operations.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_enable_device(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक err;

	err = regmap_ग_लिखो(((काष्ठा zpa2326_निजी *)
			    iio_priv(indio_dev))->regmap,
			    ZPA2326_CTRL_REG0_REG, ZPA2326_CTRL_REG0_ENABLE);
	अगर (err) अणु
		zpa2326_err(indio_dev, "failed to enable device (%d)", err);
		वापस err;
	पूर्ण

	zpa2326_dbg(indio_dev, "enabled");

	वापस 0;
पूर्ण

/**
 * zpa2326_sleep() - Disable device, i.e. चयन to low घातer mode.
 * @indio_dev: The IIO device associated with the hardware to disable.
 *
 * Only %ZPA2326_DEVICE_ID_REG and %ZPA2326_CTRL_REG0_REG रेजिस्टरs may be
 * accessed once device is in the disabled state.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_sleep(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक err;

	err = regmap_ग_लिखो(((काष्ठा zpa2326_निजी *)
			    iio_priv(indio_dev))->regmap,
			    ZPA2326_CTRL_REG0_REG, 0);
	अगर (err) अणु
		zpa2326_err(indio_dev, "failed to sleep (%d)", err);
		वापस err;
	पूर्ण

	zpa2326_dbg(indio_dev, "sleeping");

	वापस 0;
पूर्ण

/**
 * zpa2326_reset_device() - Reset device to शेष hardware state.
 * @indio_dev: The IIO device associated with the hardware to reset.
 *
 * Disable sampling and empty hardware FIFO.
 * Device must be enabled beक्रमe reset, i.e. not in low घातer mode.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_reset_device(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक err;

	err = regmap_ग_लिखो(((काष्ठा zpa2326_निजी *)
			    iio_priv(indio_dev))->regmap,
			    ZPA2326_CTRL_REG2_REG, ZPA2326_CTRL_REG2_SWRESET);
	अगर (err) अणु
		zpa2326_err(indio_dev, "failed to reset device (%d)", err);
		वापस err;
	पूर्ण

	usleep_range(ZPA2326_TPUP_USEC_MIN, ZPA2326_TPUP_USEC_MAX);

	zpa2326_dbg(indio_dev, "reset");

	वापस 0;
पूर्ण

/**
 * zpa2326_start_oneshot() - Start a single sampling cycle, i.e. in one shot
 *                           mode.
 * @indio_dev: The IIO device associated with the sampling hardware.
 *
 * Device must have been previously enabled and configured क्रम one shot mode.
 * Device will be चयनed back to low घातer mode at end of cycle.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_start_oneshot(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक err;

	err = regmap_ग_लिखो(((काष्ठा zpa2326_निजी *)
			    iio_priv(indio_dev))->regmap,
			    ZPA2326_CTRL_REG0_REG,
			    ZPA2326_CTRL_REG0_ENABLE |
			    ZPA2326_CTRL_REG0_ONE_SHOT);
	अगर (err) अणु
		zpa2326_err(indio_dev, "failed to start one shot cycle (%d)",
			    err);
		वापस err;
	पूर्ण

	zpa2326_dbg(indio_dev, "one shot cycle started");

	वापस 0;
पूर्ण

/**
 * zpa2326_घातer_on() - Power on device to allow subsequent configuration.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @निजी:   Internal निजी state related to @indio_dev.
 *
 * Sampling will be disabled, preventing strange things from happening in our
 * back. Hardware FIFO content will be cleared.
 * When successful, device will be left in the enabled state to allow further
 * configuration.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_घातer_on(स्थिर काष्ठा iio_dev         *indio_dev,
			    स्थिर काष्ठा zpa2326_निजी *निजी)
अणु
	पूर्णांक err;

	err = regulator_enable(निजी->vref);
	अगर (err)
		वापस err;

	err = regulator_enable(निजी->vdd);
	अगर (err)
		जाओ vref;

	zpa2326_dbg(indio_dev, "powered on");

	err = zpa2326_enable_device(indio_dev);
	अगर (err)
		जाओ vdd;

	err = zpa2326_reset_device(indio_dev);
	अगर (err)
		जाओ sleep;

	वापस 0;

sleep:
	zpa2326_sleep(indio_dev);
vdd:
	regulator_disable(निजी->vdd);
vref:
	regulator_disable(निजी->vref);

	zpa2326_dbg(indio_dev, "powered off");

	वापस err;
पूर्ण

/**
 * zpa2326_घातer_off() - Power off device, i.e. disable attached घातer
 *                       regulators.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @निजी:   Internal निजी state related to @indio_dev.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल व्योम zpa2326_घातer_off(स्थिर काष्ठा iio_dev         *indio_dev,
			      स्थिर काष्ठा zpa2326_निजी *निजी)
अणु
	regulator_disable(निजी->vdd);
	regulator_disable(निजी->vref);

	zpa2326_dbg(indio_dev, "powered off");
पूर्ण

/**
 * zpa2326_config_oneshot() - Setup device क्रम one shot / on demand mode.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @irq:       Optional पूर्णांकerrupt line the hardware uses to notअगरy new data
 *             samples are पढ़ोy. Negative or zero values indicate no पूर्णांकerrupts
 *             are available, meaning polling is required.
 *
 * Output Data Rate is configured क्रम the highest possible rate so that
 * conversion समय and घातer consumption are reduced to a minimum.
 * Note that hardware पूर्णांकernal averaging machinery (not implemented in this
 * driver) is not applicable in this mode.
 *
 * Device must have been previously enabled beक्रमe calling
 * zpa2326_config_oneshot().
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_config_oneshot(स्थिर काष्ठा iio_dev *indio_dev,
				  पूर्णांक                   irq)
अणु
	काष्ठा regmap                  *regs = ((काष्ठा zpa2326_निजी *)
						iio_priv(indio_dev))->regmap;
	स्थिर काष्ठा zpa2326_frequency *freq = zpa2326_highest_frequency();
	पूर्णांक                             err;

	/* Setup highest available Output Data Rate क्रम one shot mode. */
	err = regmap_ग_लिखो(regs, ZPA2326_CTRL_REG3_REG, freq->odr);
	अगर (err)
		वापस err;

	अगर (irq > 0) अणु
		/* Request पूर्णांकerrupt when new sample is available. */
		err = regmap_ग_लिखो(regs, ZPA2326_CTRL_REG1_REG,
				   (u8)~ZPA2326_CTRL_REG1_MASK_DATA_READY);

		अगर (err) अणु
			dev_err(indio_dev->dev.parent,
				"failed to setup one shot mode (%d)", err);
			वापस err;
		पूर्ण
	पूर्ण

	zpa2326_dbg(indio_dev, "one shot mode setup @%dHz", freq->hz);

	वापस 0;
पूर्ण

/**
 * zpa2326_clear_fअगरo() - Clear reमुख्यing entries in hardware FIFO.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @min_count: Number of samples present within hardware FIFO.
 *
 * @min_count argument is a hपूर्णांक corresponding to the known minimum number of
 * samples currently living in the FIFO. This allows to reduce the number of bus
 * accesses by skipping status रेजिस्टर पढ़ो operation as दीर्घ as we know क्रम
 * sure there are still entries left.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_clear_fअगरo(स्थिर काष्ठा iio_dev *indio_dev,
			      अचिन्हित पूर्णांक          min_count)
अणु
	काष्ठा regmap *regs = ((काष्ठा zpa2326_निजी *)
			       iio_priv(indio_dev))->regmap;
	पूर्णांक            err;
	अचिन्हित पूर्णांक   val;

	अगर (!min_count) अणु
		/*
		 * No hपूर्णांक: पढ़ो status रेजिस्टर to determine whether FIFO is
		 * empty or not.
		 */
		err = regmap_पढ़ो(regs, ZPA2326_STATUS_REG, &val);

		अगर (err < 0)
			जाओ err;

		अगर (val & ZPA2326_STATUS_FIFO_E)
			/* Fअगरo is empty: nothing to trash. */
			वापस 0;
	पूर्ण

	/* Clear FIFO. */
	करो अणु
		/*
		 * A single fetch from pressure MSB रेजिस्टर is enough to pop
		 * values out of FIFO.
		 */
		err = regmap_पढ़ो(regs, ZPA2326_PRESS_OUT_H_REG, &val);
		अगर (err < 0)
			जाओ err;

		अगर (min_count) अणु
			/*
			 * We know क्रम sure there are at least min_count entries
			 * left in FIFO. Skip status रेजिस्टर पढ़ो.
			 */
			min_count--;
			जारी;
		पूर्ण

		err = regmap_पढ़ो(regs, ZPA2326_STATUS_REG, &val);
		अगर (err < 0)
			जाओ err;

	पूर्ण जबतक (!(val & ZPA2326_STATUS_FIFO_E));

	zpa2326_dbg(indio_dev, "FIFO cleared");

	वापस 0;

err:
	zpa2326_err(indio_dev, "failed to clear FIFO (%d)", err);

	वापस err;
पूर्ण

/**
 * zpa2326_dequeue_pressure() - Retrieve the most recent pressure sample from
 *                              hardware FIFO.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @pressure:  Sampled pressure output.
 *
 * Note that ZPA2326 hardware FIFO stores pressure samples only.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_dequeue_pressure(स्थिर काष्ठा iio_dev *indio_dev,
				    u32                  *pressure)
अणु
	काष्ठा regmap *regs = ((काष्ठा zpa2326_निजी *)
			       iio_priv(indio_dev))->regmap;
	अचिन्हित पूर्णांक   val;
	पूर्णांक            err;
	पूर्णांक            cleared = -1;

	err = regmap_पढ़ो(regs, ZPA2326_STATUS_REG, &val);
	अगर (err < 0)
		वापस err;

	*pressure = 0;

	अगर (val & ZPA2326_STATUS_P_OR) अणु
		/*
		 * Fअगरo overrun : first sample dequeued from FIFO is the
		 * newest.
		 */
		zpa2326_warn(indio_dev, "FIFO overflow");

		err = regmap_bulk_पढ़ो(regs, ZPA2326_PRESS_OUT_XL_REG, pressure,
				       3);
		अगर (err)
			वापस err;

#घोषणा ZPA2326_FIFO_DEPTH (16U)
		/* Hardware FIFO may hold no more than 16 pressure samples. */
		वापस zpa2326_clear_fअगरo(indio_dev, ZPA2326_FIFO_DEPTH - 1);
	पूर्ण

	/*
	 * Fअगरo has not overflown : retrieve newest sample. We need to pop
	 * values out until FIFO is empty : last fetched pressure is the newest.
	 * In nominal हालs, we should find a single queued sample only.
	 */
	करो अणु
		err = regmap_bulk_पढ़ो(regs, ZPA2326_PRESS_OUT_XL_REG, pressure,
				       3);
		अगर (err)
			वापस err;

		err = regmap_पढ़ो(regs, ZPA2326_STATUS_REG, &val);
		अगर (err < 0)
			वापस err;

		cleared++;
	पूर्ण जबतक (!(val & ZPA2326_STATUS_FIFO_E));

	अगर (cleared)
		/*
		 * Samples were pushed by hardware during previous rounds but we
		 * didn't consume them fast enough: inक्रमm user.
		 */
		zpa2326_dbg(indio_dev, "cleared %d FIFO entries", cleared);

	वापस 0;
पूर्ण

/**
 * zpa2326_fill_sample_buffer() - Enqueue new channel samples to IIO buffer.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @निजी:   Internal निजी state related to @indio_dev.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_fill_sample_buffer(काष्ठा iio_dev               *indio_dev,
				      स्थिर काष्ठा zpa2326_निजी *निजी)
अणु
	काष्ठा अणु
		u32 pressure;
		u16 temperature;
		u64 बारtamp;
	पूर्ण   sample;
	पूर्णांक err;

	अगर (test_bit(0, indio_dev->active_scan_mask)) अणु
		/* Get current pressure from hardware FIFO. */
		err = zpa2326_dequeue_pressure(indio_dev, &sample.pressure);
		अगर (err) अणु
			zpa2326_warn(indio_dev, "failed to fetch pressure (%d)",
				     err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (test_bit(1, indio_dev->active_scan_mask)) अणु
		/* Get current temperature. */
		err = regmap_bulk_पढ़ो(निजी->regmap, ZPA2326_TEMP_OUT_L_REG,
				       &sample.temperature, 2);
		अगर (err) अणु
			zpa2326_warn(indio_dev,
				     "failed to fetch temperature (%d)", err);
			वापस err;
		पूर्ण
	पूर्ण

	/*
	 * Now push samples using बारtamp stored either :
	 *   - by hardware पूर्णांकerrupt handler अगर पूर्णांकerrupt is available: see
	 *     zpa2326_handle_irq(),
	 *   - or oneshot completion polling machinery : see
	 *     zpa2326_trigger_handler().
	 */
	zpa2326_dbg(indio_dev, "filling raw samples buffer");

	iio_push_to_buffers_with_बारtamp(indio_dev, &sample,
					   निजी->बारtamp);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक zpa2326_runसमय_suspend(काष्ठा device *parent)
अणु
	स्थिर काष्ठा iio_dev *indio_dev = dev_get_drvdata(parent);

	अगर (pm_runसमय_स्वतःsuspend_expiration(parent))
		/* Userspace changed स्वतःsuspend delay. */
		वापस -EAGAIN;

	zpa2326_घातer_off(indio_dev, iio_priv(indio_dev));

	वापस 0;
पूर्ण

अटल पूर्णांक zpa2326_runसमय_resume(काष्ठा device *parent)
अणु
	स्थिर काष्ठा iio_dev *indio_dev = dev_get_drvdata(parent);

	वापस zpa2326_घातer_on(indio_dev, iio_priv(indio_dev));
पूर्ण

स्थिर काष्ठा dev_pm_ops zpa2326_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(zpa2326_runसमय_suspend, zpa2326_runसमय_resume,
			   शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(zpa2326_pm_ops);

/**
 * zpa2326_resume() - Request the PM layer to घातer supply the device.
 * @indio_dev: The IIO device associated with the sampling hardware.
 *
 * Return:
 *  < 0 - a negative error code meaning failure ;
 *    0 - success, device has just been घातered up ;
 *    1 - success, device was alपढ़ोy घातered.
 */
अटल पूर्णांक zpa2326_resume(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक err;

	err = pm_runसमय_get_sync(indio_dev->dev.parent);
	अगर (err < 0) अणु
		pm_runसमय_put(indio_dev->dev.parent);
		वापस err;
	पूर्ण

	अगर (err > 0) अणु
		/*
		 * Device was alपढ़ोy घातer supplied: get it out of low घातer
		 * mode and inक्रमm caller.
		 */
		zpa2326_enable_device(indio_dev);
		वापस 1;
	पूर्ण

	/* Inक्रमm caller device has just been brought back to lअगरe. */
	वापस 0;
पूर्ण

/**
 * zpa2326_suspend() - Schedule a घातer करोwn using स्वतःsuspend feature of PM
 *                     layer.
 * @indio_dev: The IIO device associated with the sampling hardware.
 *
 * Device is चयनed to low घातer mode at first to save घातer even when
 * attached regulator is a "dummy" one.
 */
अटल व्योम zpa2326_suspend(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा device *parent = indio_dev->dev.parent;

	zpa2326_sleep(indio_dev);

	pm_runसमय_mark_last_busy(parent);
	pm_runसमय_put_स्वतःsuspend(parent);
पूर्ण

अटल व्योम zpa2326_init_runसमय(काष्ठा device *parent)
अणु
	pm_runसमय_get_noresume(parent);
	pm_runसमय_set_active(parent);
	pm_runसमय_enable(parent);
	pm_runसमय_set_स्वतःsuspend_delay(parent, 1000);
	pm_runसमय_use_स्वतःsuspend(parent);
	pm_runसमय_mark_last_busy(parent);
	pm_runसमय_put_स्वतःsuspend(parent);
पूर्ण

अटल व्योम zpa2326_fini_runसमय(काष्ठा device *parent)
अणु
	pm_runसमय_disable(parent);
	pm_runसमय_set_suspended(parent);
पूर्ण
#अन्यथा /* !CONFIG_PM */
अटल पूर्णांक zpa2326_resume(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	zpa2326_enable_device(indio_dev);

	वापस 0;
पूर्ण

अटल व्योम zpa2326_suspend(काष्ठा iio_dev *indio_dev)
अणु
	zpa2326_sleep(indio_dev);
पूर्ण

#घोषणा zpa2326_init_runसमय(_parent)
#घोषणा zpa2326_fini_runसमय(_parent)
#पूर्ण_अगर /* !CONFIG_PM */

/**
 * zpa2326_handle_irq() - Process hardware पूर्णांकerrupts.
 * @irq:  Interrupt line the hardware uses to notअगरy new data has arrived.
 * @data: The IIO device associated with the sampling hardware.
 *
 * Timestamp buffered samples as soon as possible then schedule thपढ़ोed bottom
 * half.
 *
 * Return: Always successful.
 */
अटल irqवापस_t zpa2326_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;

	अगर (iio_buffer_enabled(indio_dev)) अणु
		/* Timestamping needed क्रम buffered sampling only. */
		((काष्ठा zpa2326_निजी *)
		 iio_priv(indio_dev))->बारtamp = iio_get_समय_ns(indio_dev);
	पूर्ण

	वापस IRQ_WAKE_THREAD;
पूर्ण

/**
 * zpa2326_handle_thपढ़ोed_irq() - Interrupt bottom-half handler.
 * @irq:  Interrupt line the hardware uses to notअगरy new data has arrived.
 * @data: The IIO device associated with the sampling hardware.
 *
 * Mainly ensures पूर्णांकerrupt is caused by a real "new sample available"
 * condition. This relies upon the ability to perक्रमm blocking / sleeping bus
 * accesses to slave's रेजिस्टरs. This is why zpa2326_handle_thपढ़ोed_irq() is
 * called from within a thपढ़ो, i.e. not called from hard पूर्णांकerrupt context.
 *
 * When device is using its own पूर्णांकernal hardware trigger in continuous sampling
 * mode, data are available पूर्णांकo hardware FIFO once पूर्णांकerrupt has occurred. All
 * we have to करो is to dispatch the trigger, which in turn will fetch data and
 * fill IIO buffer.
 *
 * When not using its own पूर्णांकernal hardware trigger, the device has been
 * configured in one-shot mode either by an बाह्यal trigger or the IIO पढ़ो_raw
 * hook. This means one of the latter is currently रुकोing क्रम sampling
 * completion, in which हाल we must simply wake it up.
 *
 * See zpa2326_trigger_handler().
 *
 * Return:
 *   %IRQ_NONE - no consistent पूर्णांकerrupt happened ;
 *   %IRQ_HANDLED - there was new samples available.
 */
अटल irqवापस_t zpa2326_handle_thपढ़ोed_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev         *indio_dev = data;
	काष्ठा zpa2326_निजी *priv = iio_priv(indio_dev);
	अचिन्हित पूर्णांक            val;
	bool                    cont;
	irqवापस_t             ret = IRQ_NONE;

	/*
	 * Are we using our own पूर्णांकernal trigger in triggered buffer mode, i.e.,
	 * currently working in continuous sampling mode ?
	 */
	cont = (iio_buffer_enabled(indio_dev) &&
		iio_trigger_using_own(indio_dev));

	/*
	 * Device works according to a level पूर्णांकerrupt scheme: पढ़ोing पूर्णांकerrupt
	 * status de-निश्चितs पूर्णांकerrupt line.
	 */
	priv->result = regmap_पढ़ो(priv->regmap, ZPA2326_INT_SOURCE_REG, &val);
	अगर (priv->result < 0) अणु
		अगर (cont)
			वापस IRQ_NONE;

		जाओ complete;
	पूर्ण

	/* Data पढ़ोy is the only पूर्णांकerrupt source we requested. */
	अगर (!(val & ZPA2326_INT_SOURCE_DATA_READY)) अणु
		/*
		 * Interrupt happened but no new sample available: likely caused
		 * by spurious पूर्णांकerrupts, in which हाल, वापसing IRQ_NONE
		 * allows to benefit from the generic spurious पूर्णांकerrupts
		 * handling.
		 */
		zpa2326_warn(indio_dev, "unexpected interrupt status %02x",
			     val);

		अगर (cont)
			वापस IRQ_NONE;

		priv->result = -ENODATA;
		जाओ complete;
	पूर्ण

	/* New sample available: dispatch पूर्णांकernal trigger consumers. */
	iio_trigger_poll_chained(priv->trigger);

	अगर (cont)
		/*
		 * Internal hardware trigger has been scheduled above : it will
		 * fetch data on its own.
		 */
		वापस IRQ_HANDLED;

	ret = IRQ_HANDLED;

complete:
	/*
	 * Wake up direct or बाह्यaly triggered buffer mode रुकोers: see
	 * zpa2326_sample_oneshot() and zpa2326_trigger_handler().
	 */
	complete(&priv->data_पढ़ोy);

	वापस ret;
पूर्ण

/**
 * zpa2326_रुको_oneshot_completion() - Wait क्रम oneshot data पढ़ोy पूर्णांकerrupt.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @निजी:   Internal निजी state related to @indio_dev.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_रुको_oneshot_completion(स्थिर काष्ठा iio_dev   *indio_dev,
					   काष्ठा zpa2326_निजी *निजी)
अणु
	अचिन्हित पूर्णांक val;
	दीर्घ     समयout;

	zpa2326_dbg(indio_dev, "waiting for one shot completion interrupt");

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&निजी->data_पढ़ोy, ZPA2326_CONVERSION_JIFFIES);
	अगर (समयout > 0)
		/*
		 * Interrupt handler completed beक्रमe समयout: वापस operation
		 * status.
		 */
		वापस निजी->result;

	/* Clear all पूर्णांकerrupts just to be sure. */
	regmap_पढ़ो(निजी->regmap, ZPA2326_INT_SOURCE_REG, &val);

	अगर (!समयout) अणु
		/* Timed out. */
		zpa2326_warn(indio_dev, "no one shot interrupt occurred (%ld)",
			     समयout);
		वापस -ETIME;
	पूर्ण

	zpa2326_warn(indio_dev, "wait for one shot interrupt cancelled");
	वापस -ERESTARTSYS;
पूर्ण

अटल पूर्णांक zpa2326_init_managed_irq(काष्ठा device          *parent,
				    काष्ठा iio_dev         *indio_dev,
				    काष्ठा zpa2326_निजी *निजी,
				    पूर्णांक                     irq)
अणु
	पूर्णांक err;

	निजी->irq = irq;

	अगर (irq <= 0) अणु
		/*
		 * Platक्रमm declared no पूर्णांकerrupt line: device will be polled
		 * क्रम data availability.
		 */
		dev_info(parent, "no interrupt found, running in polling mode");
		वापस 0;
	पूर्ण

	init_completion(&निजी->data_पढ़ोy);

	/* Request handler to be scheduled पूर्णांकo thपढ़ोed पूर्णांकerrupt context. */
	err = devm_request_thपढ़ोed_irq(parent, irq, zpa2326_handle_irq,
					zpa2326_handle_thपढ़ोed_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(parent), indio_dev);
	अगर (err) अणु
		dev_err(parent, "failed to request interrupt %d (%d)", irq,
			err);
		वापस err;
	पूर्ण

	dev_info(parent, "using interrupt %d", irq);

	वापस 0;
पूर्ण

/**
 * zpa2326_poll_oneshot_completion() - Actively poll क्रम one shot data पढ़ोy.
 * @indio_dev: The IIO device associated with the sampling hardware.
 *
 * Loop over रेजिस्टरs content to detect end of sampling cycle. Used when DT
 * declared no valid पूर्णांकerrupt lines.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_poll_oneshot_completion(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	अचिन्हित दीर्घ  पंचांगout = jअगरfies + ZPA2326_CONVERSION_JIFFIES;
	काष्ठा regmap *regs = ((काष्ठा zpa2326_निजी *)
			       iio_priv(indio_dev))->regmap;
	अचिन्हित पूर्णांक   val;
	पूर्णांक            err;

	zpa2326_dbg(indio_dev, "polling for one shot completion");

	/*
	 * At least, 100 ms is needed क्रम the device to complete its one-shot
	 * cycle.
	 */
	अगर (msleep_पूर्णांकerruptible(100))
		वापस -ERESTARTSYS;

	/* Poll क्रम conversion completion in hardware. */
	जबतक (true) अणु
		err = regmap_पढ़ो(regs, ZPA2326_CTRL_REG0_REG, &val);
		अगर (err < 0)
			जाओ err;

		अगर (!(val & ZPA2326_CTRL_REG0_ONE_SHOT))
			/* One-shot bit self clears at conversion end. */
			अवरोध;

		अगर (समय_after(jअगरfies, पंचांगout)) अणु
			/* Prevent from रुकोing क्रमever : let's समय out. */
			err = -ETIME;
			जाओ err;
		पूर्ण

		usleep_range(10000, 20000);
	पूर्ण

	/*
	 * In oneshot mode, pressure sample availability guarantees that
	 * temperature conversion has also completed : just check pressure
	 * status bit to keep things simple.
	 */
	err = regmap_पढ़ो(regs, ZPA2326_STATUS_REG, &val);
	अगर (err < 0)
		जाओ err;

	अगर (!(val & ZPA2326_STATUS_P_DA)) अणु
		/* No sample available. */
		err = -ENODATA;
		जाओ err;
	पूर्ण

	वापस 0;

err:
	zpa2326_warn(indio_dev, "failed to poll one shot completion (%d)", err);

	वापस err;
पूर्ण

/**
 * zpa2326_fetch_raw_sample() - Retrieve a raw sample and convert it to CPU
 *                              endianness.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @type:      Type of measurement / channel to fetch from.
 * @value:     Sample output.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_fetch_raw_sample(स्थिर काष्ठा iio_dev *indio_dev,
				    क्रमागत iio_chan_type    type,
				    पूर्णांक                  *value)
अणु
	काष्ठा regmap *regs = ((काष्ठा zpa2326_निजी *)
			       iio_priv(indio_dev))->regmap;
	पूर्णांक            err;
	u8             v[3];

	चयन (type) अणु
	हाल IIO_PRESSURE:
		zpa2326_dbg(indio_dev, "fetching raw pressure sample");

		err = regmap_bulk_पढ़ो(regs, ZPA2326_PRESS_OUT_XL_REG, v, माप(v));
		अगर (err) अणु
			zpa2326_warn(indio_dev, "failed to fetch pressure (%d)",
				     err);
			वापस err;
		पूर्ण

		*value = get_unaligned_le24(&v[0]);

		वापस IIO_VAL_INT;

	हाल IIO_TEMP:
		zpa2326_dbg(indio_dev, "fetching raw temperature sample");

		err = regmap_bulk_पढ़ो(regs, ZPA2326_TEMP_OUT_L_REG, value, 2);
		अगर (err) अणु
			zpa2326_warn(indio_dev,
				     "failed to fetch temperature (%d)", err);
			वापस err;
		पूर्ण

		/* Temperature is a 16 bits wide little-endian चिन्हित पूर्णांक. */
		*value = (पूर्णांक)le16_to_cpup((__le16 *)value);

		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * zpa2326_sample_oneshot() - Perक्रमm a complete one shot sampling cycle.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @type:      Type of measurement / channel to fetch from.
 * @value:     Sample output.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_sample_oneshot(काष्ठा iio_dev     *indio_dev,
				  क्रमागत iio_chan_type  type,
				  पूर्णांक                *value)
अणु
	पूर्णांक                     ret;
	काष्ठा zpa2326_निजी *priv;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	ret = zpa2326_resume(indio_dev);
	अगर (ret < 0)
		जाओ release;

	priv = iio_priv(indio_dev);

	अगर (ret > 0) अणु
		/*
		 * We were alपढ़ोy घातer supplied. Just clear hardware FIFO to
		 * get rid of samples acquired during previous rounds (अगर any).
		 * Sampling operation always generates both temperature and
		 * pressure samples. The latter are always enqueued पूर्णांकo
		 * hardware FIFO. This may lead to situations were pressure
		 * samples still sit पूर्णांकo FIFO when previous cycle(s) fetched
		 * temperature data only.
		 * Hence, we need to clear hardware FIFO content to prevent from
		 * getting outdated values at the end of current cycle.
		 */
		अगर (type == IIO_PRESSURE) अणु
			ret = zpa2326_clear_fअगरo(indio_dev, 0);
			अगर (ret)
				जाओ suspend;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We have just been घातer supplied, i.e. device is in शेष
		 * "out of reset" state, meaning we need to reconfigure it
		 * entirely.
		 */
		ret = zpa2326_config_oneshot(indio_dev, priv->irq);
		अगर (ret)
			जाओ suspend;
	पूर्ण

	/* Start a sampling cycle in oneshot mode. */
	ret = zpa2326_start_oneshot(indio_dev);
	अगर (ret)
		जाओ suspend;

	/* Wait क्रम sampling cycle to complete. */
	अगर (priv->irq > 0)
		ret = zpa2326_रुको_oneshot_completion(indio_dev, priv);
	अन्यथा
		ret = zpa2326_poll_oneshot_completion(indio_dev);

	अगर (ret)
		जाओ suspend;

	/* Retrieve raw sample value and convert it to CPU endianness. */
	ret = zpa2326_fetch_raw_sample(indio_dev, type, value);

suspend:
	zpa2326_suspend(indio_dev);
release:
	iio_device_release_direct_mode(indio_dev);

	वापस ret;
पूर्ण

/**
 * zpa2326_trigger_handler() - Perक्रमm an IIO buffered sampling round in one
 *                             shot mode.
 * @irq:  The software पूर्णांकerrupt asचिन्हित to @data
 * @data: The IIO poll function dispatched by बाह्यal trigger our device is
 *        attached to.
 *
 * Bottom-half handler called by the IIO trigger to which our device is
 * currently attached. Allows us to synchronize this device buffered sampling
 * either with बाह्यal events (such as समयr expiration, बाह्यal device sample
 * पढ़ोy, etc...) or with its own पूर्णांकerrupt (पूर्णांकernal hardware trigger).
 *
 * When using an बाह्यal trigger, basically run the same sequence of operations
 * as क्रम zpa2326_sample_oneshot() with the following hereafter. Hardware FIFO
 * is not cleared since alपढ़ोy करोne at buffering enable समय and samples
 * dequeueing always retrieves the most recent value.
 *
 * Otherwise, when पूर्णांकernal hardware trigger has dispatched us, just fetch data
 * from hardware FIFO.
 *
 * Fetched data will pushed unprocessed to IIO buffer since samples conversion
 * is delegated to userspace in buffered mode (endianness, etc...).
 *
 * Return:
 *   %IRQ_NONE - no consistent पूर्णांकerrupt happened ;
 *   %IRQ_HANDLED - there was new samples available.
 */
अटल irqवापस_t zpa2326_trigger_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev         *indio_dev = ((काष्ठा iio_poll_func *)
					     data)->indio_dev;
	काष्ठा zpa2326_निजी *priv = iio_priv(indio_dev);
	bool                    cont;

	/*
	 * We have been dispatched, meaning we are in triggered buffer mode.
	 * Using our own पूर्णांकernal trigger implies we are currently in continuous
	 * hardware sampling mode.
	 */
	cont = iio_trigger_using_own(indio_dev);

	अगर (!cont) अणु
		/* On demand sampling : start a one shot cycle. */
		अगर (zpa2326_start_oneshot(indio_dev))
			जाओ out;

		/* Wait क्रम sampling cycle to complete. */
		अगर (priv->irq <= 0) अणु
			/* No पूर्णांकerrupt available: poll क्रम completion. */
			अगर (zpa2326_poll_oneshot_completion(indio_dev))
				जाओ out;

			/* Only बारtamp sample once it is पढ़ोy. */
			priv->बारtamp = iio_get_समय_ns(indio_dev);
		पूर्ण अन्यथा अणु
			/* Interrupt handlers will बारtamp क्रम us. */
			अगर (zpa2326_रुको_oneshot_completion(indio_dev, priv))
				जाओ out;
		पूर्ण
	पूर्ण

	/* Enqueue to IIO buffer / userspace. */
	zpa2326_fill_sample_buffer(indio_dev, priv);

out:
	अगर (!cont)
		/* Don't चयन to low घातer अगर sampling continuously. */
		zpa2326_sleep(indio_dev);

	/* Inक्रमm attached trigger we are करोne. */
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * zpa2326_preenable_buffer() - Prepare device क्रम configuring triggered
 *                              sampling
 * modes.
 * @indio_dev: The IIO device associated with the sampling hardware.
 *
 * Basically घातer up device.
 * Called with IIO device's lock held.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_preenable_buffer(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret = zpa2326_resume(indio_dev);

	अगर (ret < 0)
		वापस ret;

	/* Tell zpa2326_postenable_buffer() अगर we have just been घातered on. */
	((काष्ठा zpa2326_निजी *)
	 iio_priv(indio_dev))->waken = iio_priv(indio_dev);

	वापस 0;
पूर्ण

/**
 * zpa2326_postenable_buffer() - Configure device क्रम triggered sampling.
 * @indio_dev: The IIO device associated with the sampling hardware.
 *
 * Basically setup one-shot mode अगर plugging बाह्यal trigger.
 * Otherwise, let पूर्णांकernal trigger configure continuous sampling :
 * see zpa2326_set_trigger_state().
 *
 * If an error is वापसed, IIO layer will call our postdisable hook क्रम us,
 * i.e. no need to explicitly घातer device off here.
 * Called with IIO device's lock held.
 *
 * Called with IIO device's lock held.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_postenable_buffer(काष्ठा iio_dev *indio_dev)
अणु
	स्थिर काष्ठा zpa2326_निजी *priv = iio_priv(indio_dev);
	पूर्णांक                           err;

	अगर (!priv->waken) अणु
		/*
		 * We were alपढ़ोy घातer supplied. Just clear hardware FIFO to
		 * get rid of samples acquired during previous rounds (अगर any).
		 */
		err = zpa2326_clear_fअगरo(indio_dev, 0);
		अगर (err) अणु
			zpa2326_err(indio_dev,
				    "failed to enable buffering (%d)", err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (!iio_trigger_using_own(indio_dev) && priv->waken) अणु
		/*
		 * We are using an बाह्यal trigger and we have just been
		 * घातered up: reconfigure one-shot mode.
		 */
		err = zpa2326_config_oneshot(indio_dev, priv->irq);
		अगर (err) अणु
			zpa2326_err(indio_dev,
				    "failed to enable buffering (%d)", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zpa2326_postdisable_buffer(काष्ठा iio_dev *indio_dev)
अणु
	zpa2326_suspend(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops zpa2326_buffer_setup_ops = अणु
	.preenable   = zpa2326_preenable_buffer,
	.postenable  = zpa2326_postenable_buffer,
	.postdisable = zpa2326_postdisable_buffer
पूर्ण;

/**
 * zpa2326_set_trigger_state() - Start / stop continuous sampling.
 * @trig:  The trigger being attached to IIO device associated with the sampling
 *         hardware.
 * @state: Tell whether to start (true) or stop (false)
 *
 * Basically enable / disable hardware continuous sampling mode.
 *
 * Called with IIO device's lock held at postenable() or predisable() समय.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_set_trigger_state(काष्ठा iio_trigger *trig, bool state)
अणु
	स्थिर काष्ठा iio_dev         *indio_dev = dev_get_drvdata(
							trig->dev.parent);
	स्थिर काष्ठा zpa2326_निजी *priv = iio_priv(indio_dev);
	पूर्णांक                           err;

	अगर (!state) अणु
		/*
		 * Switch trigger off : in हाल of failure, पूर्णांकerrupt is left
		 * disabled in order to prevent handler from accessing released
		 * resources.
		 */
		अचिन्हित पूर्णांक val;

		/*
		 * As device is working in continuous mode, handlers may be
		 * accessing resources we are currently मुक्तing...
		 * Prevent this by disabling पूर्णांकerrupt handlers and ensure
		 * the device will generate no more पूर्णांकerrupts unless explicitly
		 * required to, i.e. by restoring back to शेष one shot mode.
		 */
		disable_irq(priv->irq);

		/*
		 * Disable continuous sampling mode to restore settings क्रम
		 * one shot / direct sampling operations.
		 */
		err = regmap_ग_लिखो(priv->regmap, ZPA2326_CTRL_REG3_REG,
				   zpa2326_highest_frequency()->odr);
		अगर (err)
			वापस err;

		/*
		 * Now that device won't generate पूर्णांकerrupts on its own,
		 * acknowledge any currently active पूर्णांकerrupts (may happen on
		 * rare occasions जबतक stopping continuous mode).
		 */
		err = regmap_पढ़ो(priv->regmap, ZPA2326_INT_SOURCE_REG, &val);
		अगर (err < 0)
			वापस err;

		/*
		 * Re-enable पूर्णांकerrupts only अगर we can guarantee the device will
		 * generate no more पूर्णांकerrupts to prevent handlers from
		 * accessing released resources.
		 */
		enable_irq(priv->irq);

		zpa2326_dbg(indio_dev, "continuous mode stopped");
	पूर्ण अन्यथा अणु
		/*
		 * Switch trigger on : start continuous sampling at required
		 * frequency.
		 */

		अगर (priv->waken) अणु
			/* Enable पूर्णांकerrupt अगर getting out of reset. */
			err = regmap_ग_लिखो(priv->regmap, ZPA2326_CTRL_REG1_REG,
					   (u8)
					   ~ZPA2326_CTRL_REG1_MASK_DATA_READY);
			अगर (err)
				वापस err;
		पूर्ण

		/* Enable continuous sampling at specअगरied frequency. */
		err = regmap_ग_लिखो(priv->regmap, ZPA2326_CTRL_REG3_REG,
				   ZPA2326_CTRL_REG3_ENABLE_MEAS |
				   priv->frequency->odr);
		अगर (err)
			वापस err;

		zpa2326_dbg(indio_dev, "continuous mode setup @%dHz",
			    priv->frequency->hz);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops zpa2326_trigger_ops = अणु
	.set_trigger_state = zpa2326_set_trigger_state,
पूर्ण;

/**
 * zpa2326_init_managed_trigger() - Create पूर्णांकerrupt driven / hardware trigger
 *                          allowing to notअगरy बाह्यal devices a new sample is
 *                          पढ़ोy.
 * @parent:    Hardware sampling device @indio_dev is a child of.
 * @indio_dev: The IIO device associated with the sampling hardware.
 * @निजी:   Internal निजी state related to @indio_dev.
 * @irq:       Optional पूर्णांकerrupt line the hardware uses to notअगरy new data
 *             samples are पढ़ोy. Negative or zero values indicate no पूर्णांकerrupts
 *             are available, meaning polling is required.
 *
 * Only relevant when DT declares a valid पूर्णांकerrupt line.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
अटल पूर्णांक zpa2326_init_managed_trigger(काष्ठा device          *parent,
					काष्ठा iio_dev         *indio_dev,
					काष्ठा zpa2326_निजी *निजी,
					पूर्णांक                     irq)
अणु
	काष्ठा iio_trigger *trigger;
	पूर्णांक                 ret;

	अगर (irq <= 0)
		वापस 0;

	trigger = devm_iio_trigger_alloc(parent, "%s-dev%d",
					 indio_dev->name, indio_dev->id);
	अगर (!trigger)
		वापस -ENOMEM;

	/* Basic setup. */
	trigger->ops = &zpa2326_trigger_ops;

	निजी->trigger = trigger;

	/* Register to triggers space. */
	ret = devm_iio_trigger_रेजिस्टर(parent, trigger);
	अगर (ret)
		dev_err(parent, "failed to register hardware trigger (%d)",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक zpa2326_get_frequency(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	वापस ((काष्ठा zpa2326_निजी *)iio_priv(indio_dev))->frequency->hz;
पूर्ण

अटल पूर्णांक zpa2326_set_frequency(काष्ठा iio_dev *indio_dev, पूर्णांक hz)
अणु
	काष्ठा zpa2326_निजी *priv = iio_priv(indio_dev);
	पूर्णांक                     freq;
	पूर्णांक                     err;

	/* Check अगर requested frequency is supported. */
	क्रम (freq = 0; freq < ARRAY_SIZE(zpa2326_sampling_frequencies); freq++)
		अगर (zpa2326_sampling_frequencies[freq].hz == hz)
			अवरोध;
	अगर (freq == ARRAY_SIZE(zpa2326_sampling_frequencies))
		वापस -EINVAL;

	/* Don't allow changing frequency अगर buffered sampling is ongoing. */
	err = iio_device_claim_direct_mode(indio_dev);
	अगर (err)
		वापस err;

	priv->frequency = &zpa2326_sampling_frequencies[freq];

	iio_device_release_direct_mode(indio_dev);

	वापस 0;
पूर्ण

/* Expose supported hardware sampling frequencies (Hz) through sysfs. */
अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("1 5 11 23");

अटल काष्ठा attribute *zpa2326_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group zpa2326_attribute_group = अणु
	.attrs = zpa2326_attributes,
पूर्ण;

अटल पूर्णांक zpa2326_पढ़ो_raw(काष्ठा iio_dev             *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक                        *val,
			    पूर्णांक                        *val2,
			    दीर्घ                        mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस zpa2326_sample_oneshot(indio_dev, chan->type, val);

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_PRESSURE:
			/*
			 * Pressure resolution is 1/64 Pascal. Scale to kPascal
			 * as required by IIO ABI.
			 */
			*val = 1;
			*val2 = 64000;
			वापस IIO_VAL_FRACTIONAL;

		हाल IIO_TEMP:
			/*
			 * Temperature follows the equation:
			 *     Temp[degC] = Tempcode * 0.00649 - 176.83
			 * where:
			 *     Tempcode is composed the raw sampled 16 bits.
			 *
			 * Hence, to produce a temperature in milli-degrees
			 * Celsius according to IIO ABI, we need to apply the
			 * following equation to raw samples:
			 *     Temp[milli degC] = (Tempcode + Offset) * Scale
			 * where:
			 *     Offset = -176.83 / 0.00649
			 *     Scale = 0.00649 * 1000
			 */
			*val = 6;
			*val2 = 490000;
			वापस IIO_VAL_INT_PLUS_MICRO;

		शेष:
			वापस -EINVAL;
		पूर्ण

	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = -17683000;
			*val2 = 649;
			वापस IIO_VAL_FRACTIONAL;

		शेष:
			वापस -EINVAL;
		पूर्ण

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = zpa2326_get_frequency(indio_dev);
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक zpa2326_ग_लिखो_raw(काष्ठा iio_dev             *indio_dev,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     पूर्णांक                         val,
			     पूर्णांक                         val2,
			     दीर्घ                        mask)
अणु
	अगर ((mask != IIO_CHAN_INFO_SAMP_FREQ) || val2)
		वापस -EINVAL;

	वापस zpa2326_set_frequency(indio_dev, val);
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec zpa2326_channels[] = अणु
	[0] = अणु
		.type                    = IIO_PRESSURE,
		.scan_index              = 0,
		.scan_type               = अणु
			.sign                   = 'u',
			.realbits               = 24,
			.storagebits            = 32,
			.endianness             = IIO_LE,
		पूर्ण,
		.info_mask_separate      = BIT(IIO_CHAN_INFO_RAW) |
					   BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
	[1] = अणु
		.type                    = IIO_TEMP,
		.scan_index              = 1,
		.scan_type               = अणु
			.sign                   = 's',
			.realbits               = 16,
			.storagebits            = 16,
			.endianness             = IIO_LE,
		पूर्ण,
		.info_mask_separate      = BIT(IIO_CHAN_INFO_RAW) |
					   BIT(IIO_CHAN_INFO_SCALE) |
					   BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
	[2] = IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल स्थिर काष्ठा iio_info zpa2326_info = अणु
	.attrs         = &zpa2326_attribute_group,
	.पढ़ो_raw      = zpa2326_पढ़ो_raw,
	.ग_लिखो_raw     = zpa2326_ग_लिखो_raw,
पूर्ण;

अटल काष्ठा iio_dev *zpa2326_create_managed_iiodev(काष्ठा device *device,
						     स्थिर अक्षर    *name,
						     काष्ठा regmap *regmap)
अणु
	काष्ठा iio_dev *indio_dev;

	/* Allocate space to hold IIO device पूर्णांकernal state. */
	indio_dev = devm_iio_device_alloc(device,
					  माप(काष्ठा zpa2326_निजी));
	अगर (!indio_dev)
		वापस शून्य;

	/* Setup क्रम userspace synchronous on demand sampling. */
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = zpa2326_channels;
	indio_dev->num_channels = ARRAY_SIZE(zpa2326_channels);
	indio_dev->name = name;
	indio_dev->info = &zpa2326_info;

	वापस indio_dev;
पूर्ण

पूर्णांक zpa2326_probe(काष्ठा device *parent,
		  स्थिर अक्षर    *name,
		  पूर्णांक            irq,
		  अचिन्हित पूर्णांक   hwid,
		  काष्ठा regmap *regmap)
अणु
	काष्ठा iio_dev         *indio_dev;
	काष्ठा zpa2326_निजी *priv;
	पूर्णांक                     err;
	अचिन्हित पूर्णांक            id;

	indio_dev = zpa2326_create_managed_iiodev(parent, name, regmap);
	अगर (!indio_dev)
		वापस -ENOMEM;

	priv = iio_priv(indio_dev);

	priv->vref = devm_regulator_get(parent, "vref");
	अगर (IS_ERR(priv->vref))
		वापस PTR_ERR(priv->vref);

	priv->vdd = devm_regulator_get(parent, "vdd");
	अगर (IS_ERR(priv->vdd))
		वापस PTR_ERR(priv->vdd);

	/* Set शेष hardware sampling frequency to highest rate supported. */
	priv->frequency = zpa2326_highest_frequency();

	/*
	 * Plug device's underlying bus असलtraction : this MUST be set beक्रमe
	 * रेजिस्टरing पूर्णांकerrupt handlers since an पूर्णांकerrupt might happen अगर
	 * घातer up sequence is not properly applied.
	 */
	priv->regmap = regmap;

	err = devm_iio_triggered_buffer_setup(parent, indio_dev, शून्य,
					      zpa2326_trigger_handler,
					      &zpa2326_buffer_setup_ops);
	अगर (err)
		वापस err;

	err = zpa2326_init_managed_trigger(parent, indio_dev, priv, irq);
	अगर (err)
		वापस err;

	err = zpa2326_init_managed_irq(parent, indio_dev, priv, irq);
	अगर (err)
		वापस err;

	/* Power up to check device ID and perक्रमm initial hardware setup. */
	err = zpa2326_घातer_on(indio_dev, priv);
	अगर (err)
		वापस err;

	/* Read id रेजिस्टर to check we are talking to the right slave. */
	err = regmap_पढ़ो(regmap, ZPA2326_DEVICE_ID_REG, &id);
	अगर (err)
		जाओ sleep;

	अगर (id != hwid) अणु
		dev_err(parent, "found device with unexpected id %02x", id);
		err = -ENODEV;
		जाओ sleep;
	पूर्ण

	err = zpa2326_config_oneshot(indio_dev, irq);
	अगर (err)
		जाओ sleep;

	/* Setup करोne : go sleeping. Device will be awaken upon user request. */
	err = zpa2326_sleep(indio_dev);
	अगर (err)
		जाओ घातeroff;

	dev_set_drvdata(parent, indio_dev);

	zpa2326_init_runसमय(parent);

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err) अणु
		zpa2326_fini_runसमय(parent);
		जाओ घातeroff;
	पूर्ण

	वापस 0;

sleep:
	/* Put to sleep just in हाल घातer regulators are "dummy" ones. */
	zpa2326_sleep(indio_dev);
घातeroff:
	zpa2326_घातer_off(indio_dev, priv);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(zpa2326_probe);

व्योम zpa2326_हटाओ(स्थिर काष्ठा device *parent)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(parent);

	iio_device_unरेजिस्टर(indio_dev);
	zpa2326_fini_runसमय(indio_dev->dev.parent);
	zpa2326_sleep(indio_dev);
	zpa2326_घातer_off(indio_dev, iio_priv(indio_dev));
पूर्ण
EXPORT_SYMBOL_GPL(zpa2326_हटाओ);

MODULE_AUTHOR("Gregor Boirie <gregor.boirie@parrot.com>");
MODULE_DESCRIPTION("Core driver for Murata ZPA2326 pressure sensor");
MODULE_LICENSE("GPL v2");
