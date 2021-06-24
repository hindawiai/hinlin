<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD5758 Digital to analog converters driver
 *
 * Copyright 2018 Analog Devices Inc.
 *
 * TODO: Currently CRC is not supported in this driver
 */
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

/* AD5758 रेजिस्टरs definition */
#घोषणा AD5758_NOP				0x00
#घोषणा AD5758_DAC_INPUT			0x01
#घोषणा AD5758_DAC_OUTPUT			0x02
#घोषणा AD5758_CLEAR_CODE			0x03
#घोषणा AD5758_USER_GAIN			0x04
#घोषणा AD5758_USER_OFFSET			0x05
#घोषणा AD5758_DAC_CONFIG			0x06
#घोषणा AD5758_SW_LDAC				0x07
#घोषणा AD5758_KEY				0x08
#घोषणा AD5758_GP_CONFIG1			0x09
#घोषणा AD5758_GP_CONFIG2			0x0A
#घोषणा AD5758_DCDC_CONFIG1			0x0B
#घोषणा AD5758_DCDC_CONFIG2			0x0C
#घोषणा AD5758_WDT_CONFIG			0x0F
#घोषणा AD5758_DIGITAL_DIAG_CONFIG		0x10
#घोषणा AD5758_ADC_CONFIG			0x11
#घोषणा AD5758_FAULT_PIN_CONFIG			0x12
#घोषणा AD5758_TWO_STAGE_READBACK_SELECT	0x13
#घोषणा AD5758_DIGITAL_DIAG_RESULTS		0x14
#घोषणा AD5758_ANALOG_DIAG_RESULTS		0x15
#घोषणा AD5758_STATUS				0x16
#घोषणा AD5758_CHIP_ID				0x17
#घोषणा AD5758_FREQ_MONITOR			0x18
#घोषणा AD5758_DEVICE_ID_0			0x19
#घोषणा AD5758_DEVICE_ID_1			0x1A
#घोषणा AD5758_DEVICE_ID_2			0x1B
#घोषणा AD5758_DEVICE_ID_3			0x1C

/* AD5758_DAC_CONFIG */
#घोषणा AD5758_DAC_CONFIG_RANGE_MSK		GENMASK(3, 0)
#घोषणा AD5758_DAC_CONFIG_RANGE_MODE(x)		(((x) & 0xF) << 0)
#घोषणा AD5758_DAC_CONFIG_INT_EN_MSK		BIT(5)
#घोषणा AD5758_DAC_CONFIG_INT_EN_MODE(x)	(((x) & 0x1) << 5)
#घोषणा AD5758_DAC_CONFIG_OUT_EN_MSK		BIT(6)
#घोषणा AD5758_DAC_CONFIG_OUT_EN_MODE(x)	(((x) & 0x1) << 6)
#घोषणा AD5758_DAC_CONFIG_SR_EN_MSK		BIT(8)
#घोषणा AD5758_DAC_CONFIG_SR_EN_MODE(x)		(((x) & 0x1) << 8)
#घोषणा AD5758_DAC_CONFIG_SR_CLOCK_MSK		GENMASK(12, 9)
#घोषणा AD5758_DAC_CONFIG_SR_CLOCK_MODE(x)	(((x) & 0xF) << 9)
#घोषणा AD5758_DAC_CONFIG_SR_STEP_MSK		GENMASK(15, 13)
#घोषणा AD5758_DAC_CONFIG_SR_STEP_MODE(x)	(((x) & 0x7) << 13)

/* AD5758_KEY */
#घोषणा AD5758_KEY_CODE_RESET_1			0x15FA
#घोषणा AD5758_KEY_CODE_RESET_2			0xAF51
#घोषणा AD5758_KEY_CODE_SINGLE_ADC_CONV		0x1ADC
#घोषणा AD5758_KEY_CODE_RESET_WDT		0x0D06
#घोषणा AD5758_KEY_CODE_CALIB_MEM_REFRESH	0xFCBA

/* AD5758_DCDC_CONFIG1 */
#घोषणा AD5758_DCDC_CONFIG1_DCDC_VPROG_MSK	GENMASK(4, 0)
#घोषणा AD5758_DCDC_CONFIG1_DCDC_VPROG_MODE(x)	(((x) & 0x1F) << 0)
#घोषणा AD5758_DCDC_CONFIG1_DCDC_MODE_MSK	GENMASK(6, 5)
#घोषणा AD5758_DCDC_CONFIG1_DCDC_MODE_MODE(x)	(((x) & 0x3) << 5)

/* AD5758_DCDC_CONFIG2 */
#घोषणा AD5758_DCDC_CONFIG2_ILIMIT_MSK		GENMASK(3, 1)
#घोषणा AD5758_DCDC_CONFIG2_ILIMIT_MODE(x)	(((x) & 0x7) << 1)
#घोषणा AD5758_DCDC_CONFIG2_INTR_SAT_3WI_MSK	BIT(11)
#घोषणा AD5758_DCDC_CONFIG2_BUSY_3WI_MSK	BIT(12)

/* AD5758_DIGITAL_DIAG_RESULTS */
#घोषणा AD5758_CAL_MEM_UNREFRESHED_MSK		BIT(15)

/* AD5758_ADC_CONFIG */
#घोषणा AD5758_ADC_CONFIG_PPC_BUF_EN(x)		(((x) & 0x1) << 11)
#घोषणा AD5758_ADC_CONFIG_PPC_BUF_MSK		BIT(11)

#घोषणा AD5758_WR_FLAG_MSK(x)		(0x80 | ((x) & 0x1F))

#घोषणा AD5758_FULL_SCALE_MICRO	65535000000ULL

काष्ठा ad5758_range अणु
	पूर्णांक reg;
	पूर्णांक min;
	पूर्णांक max;
पूर्ण;

/**
 * काष्ठा ad5758_state - driver instance specअगरic data
 * @spi:	spi_device
 * @lock:	mutex lock
 * @gpio_reset:	gpio descriptor क्रम the reset line
 * @out_range:	काष्ठा which stores the output range
 * @dc_dc_mode:	variable which stores the mode of operation
 * @dc_dc_ilim:	variable which stores the dc-to-dc converter current limit
 * @slew_समय:	variable which stores the target slew समय
 * @pwr_करोwn:	variable which contains whether a channel is घातered करोwn or not
 * @d32:	spi transfer buffers
 */
काष्ठा ad5758_state अणु
	काष्ठा spi_device *spi;
	काष्ठा mutex lock;
	काष्ठा gpio_desc *gpio_reset;
	काष्ठा ad5758_range out_range;
	अचिन्हित पूर्णांक dc_dc_mode;
	अचिन्हित पूर्णांक dc_dc_ilim;
	अचिन्हित पूर्णांक slew_समय;
	bool pwr_करोwn;
	__be32 d32[3];
पूर्ण;

/*
 * Output ranges corresponding to bits [3:0] from DAC_CONFIG रेजिस्टर
 * 0000: 0 V to 5 V voltage range
 * 0001: 0 V to 10 V voltage range
 * 0010: तऔ5 V voltage range
 * 0011: तऔ10 V voltage range
 * 1000: 0 mA to 20 mA current range
 * 1001: 0 mA to 24 mA current range
 * 1010: 4 mA to 20 mA current range
 * 1011: तऔ20 mA current range
 * 1100: तऔ24 mA current range
 * 1101: -1 mA to +22 mA current range
 */
क्रमागत ad5758_output_range अणु
	AD5758_RANGE_0V_5V,
	AD5758_RANGE_0V_10V,
	AD5758_RANGE_PLUSMINUS_5V,
	AD5758_RANGE_PLUSMINUS_10V,
	AD5758_RANGE_0mA_20mA = 8,
	AD5758_RANGE_0mA_24mA,
	AD5758_RANGE_4mA_24mA,
	AD5758_RANGE_PLUSMINUS_20mA,
	AD5758_RANGE_PLUSMINUS_24mA,
	AD5758_RANGE_MINUS_1mA_PLUS_22mA,
पूर्ण;

क्रमागत ad5758_dc_dc_mode अणु
	AD5758_DCDC_MODE_POWER_OFF,
	AD5758_DCDC_MODE_DPC_CURRENT,
	AD5758_DCDC_MODE_DPC_VOLTAGE,
	AD5758_DCDC_MODE_PPC_CURRENT,
पूर्ण;

अटल स्थिर काष्ठा ad5758_range ad5758_voltage_range[] = अणु
	अणु AD5758_RANGE_0V_5V, 0, 5000000 पूर्ण,
	अणु AD5758_RANGE_0V_10V, 0, 10000000 पूर्ण,
	अणु AD5758_RANGE_PLUSMINUS_5V, -5000000, 5000000 पूर्ण,
	अणु AD5758_RANGE_PLUSMINUS_10V, -10000000, 10000000 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ad5758_range ad5758_current_range[] = अणु
	अणु AD5758_RANGE_0mA_20mA, 0, 20000पूर्ण,
	अणु AD5758_RANGE_0mA_24mA, 0, 24000 पूर्ण,
	अणु AD5758_RANGE_4mA_24mA, 4, 24000 पूर्ण,
	अणु AD5758_RANGE_PLUSMINUS_20mA, -20000, 20000 पूर्ण,
	अणु AD5758_RANGE_PLUSMINUS_24mA, -24000, 24000 पूर्ण,
	अणु AD5758_RANGE_MINUS_1mA_PLUS_22mA, -1000, 22000 पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक ad5758_sr_clk[16] = अणु
	240000, 200000, 150000, 128000, 64000, 32000, 16000, 8000, 4000, 2000,
	1000, 512, 256, 128, 64, 16
पूर्ण;

अटल स्थिर पूर्णांक ad5758_sr_step[8] = अणु
	4, 12, 64, 120, 256, 500, 1820, 2048
पूर्ण;

अटल स्थिर पूर्णांक ad5758_dc_dc_ilim[6] = अणु
	150000, 200000, 250000, 300000, 350000, 400000
पूर्ण;

अटल पूर्णांक ad5758_spi_reg_पढ़ो(काष्ठा ad5758_state *st, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->d32[0],
			.len = 4,
			.cs_change = 1,
		पूर्ण, अणु
			.tx_buf = &st->d32[1],
			.rx_buf = &st->d32[2],
			.len = 4,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	st->d32[0] = cpu_to_be32(
		(AD5758_WR_FLAG_MSK(AD5758_TWO_STAGE_READBACK_SELECT) << 24) |
		(addr << 8));
	st->d32[1] = cpu_to_be32(AD5758_WR_FLAG_MSK(AD5758_NOP) << 24);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	अगर (ret < 0)
		वापस ret;

	वापस (be32_to_cpu(st->d32[2]) >> 8) & 0xFFFF;
पूर्ण

अटल पूर्णांक ad5758_spi_reg_ग_लिखो(काष्ठा ad5758_state *st,
				अचिन्हित पूर्णांक addr,
				अचिन्हित पूर्णांक val)
अणु
	st->d32[0] = cpu_to_be32((AD5758_WR_FLAG_MSK(addr) << 24) |
				 ((val & 0xFFFF) << 8));

	वापस spi_ग_लिखो(st->spi, &st->d32[0], माप(st->d32[0]));
पूर्ण

अटल पूर्णांक ad5758_spi_ग_लिखो_mask(काष्ठा ad5758_state *st,
				 अचिन्हित पूर्णांक addr,
				 अचिन्हित दीर्घ पूर्णांक mask,
				 अचिन्हित पूर्णांक val)
अणु
	पूर्णांक regval;

	regval = ad5758_spi_reg_पढ़ो(st, addr);
	अगर (regval < 0)
		वापस regval;

	regval &= ~mask;
	regval |= val;

	वापस ad5758_spi_reg_ग_लिखो(st, addr, regval);
पूर्ण

अटल पूर्णांक cmpfunc(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस *(पूर्णांक *)a - *(पूर्णांक *)b;
पूर्ण

अटल पूर्णांक ad5758_find_बंदst_match(स्थिर पूर्णांक *array,
				     अचिन्हित पूर्णांक size, पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (val <= array[i])
			वापस i;
	पूर्ण

	वापस size - 1;
पूर्ण

अटल पूर्णांक ad5758_रुको_क्रम_task_complete(काष्ठा ad5758_state *st,
					 अचिन्हित पूर्णांक reg,
					 अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक समयout;
	पूर्णांक ret;

	समयout = 10;
	करो अणु
		ret = ad5758_spi_reg_पढ़ो(st, reg);
		अगर (ret < 0)
			वापस ret;

		अगर (!(ret & mask))
			वापस 0;

		usleep_range(100, 1000);
	पूर्ण जबतक (--समयout);

	dev_err(&st->spi->dev,
		"Error reading bit 0x%x in 0x%x register\n", mask, reg);

	वापस -EIO;
पूर्ण

अटल पूर्णांक ad5758_calib_mem_refresh(काष्ठा ad5758_state *st)
अणु
	पूर्णांक ret;

	ret = ad5758_spi_reg_ग_लिखो(st, AD5758_KEY,
				   AD5758_KEY_CODE_CALIB_MEM_REFRESH);
	अगर (ret < 0) अणु
		dev_err(&st->spi->dev,
			"Failed to initiate a calibration memory refresh\n");
		वापस ret;
	पूर्ण

	/* Wait to allow समय क्रम the पूर्णांकernal calibrations to complete */
	वापस ad5758_रुको_क्रम_task_complete(st, AD5758_DIGITAL_DIAG_RESULTS,
					     AD5758_CAL_MEM_UNREFRESHED_MSK);
पूर्ण

अटल पूर्णांक ad5758_soft_reset(काष्ठा ad5758_state *st)
अणु
	पूर्णांक ret;

	ret = ad5758_spi_reg_ग_लिखो(st, AD5758_KEY, AD5758_KEY_CODE_RESET_1);
	अगर (ret < 0)
		वापस ret;

	ret = ad5758_spi_reg_ग_लिखो(st, AD5758_KEY, AD5758_KEY_CODE_RESET_2);

	/* Perक्रमm a software reset and रुको at least 100us */
	usleep_range(100, 1000);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5758_set_dc_dc_conv_mode(काष्ठा ad5758_state *st,
				      क्रमागत ad5758_dc_dc_mode mode)
अणु
	पूर्णांक ret;

	/*
	 * The ENABLE_PPC_BUFFERS bit must be set prior to enabling PPC current
	 * mode.
	 */
	अगर (mode == AD5758_DCDC_MODE_PPC_CURRENT) अणु
		ret  = ad5758_spi_ग_लिखो_mask(st, AD5758_ADC_CONFIG,
				    AD5758_ADC_CONFIG_PPC_BUF_MSK,
				    AD5758_ADC_CONFIG_PPC_BUF_EN(1));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = ad5758_spi_ग_लिखो_mask(st, AD5758_DCDC_CONFIG1,
				    AD5758_DCDC_CONFIG1_DCDC_MODE_MSK,
				    AD5758_DCDC_CONFIG1_DCDC_MODE_MODE(mode));
	अगर (ret < 0)
		वापस ret;

	/*
	 * Poll the BUSY_3WI bit in the DCDC_CONFIG2 रेजिस्टर until it is 0.
	 * This allows the 3-wire पूर्णांकerface communication to complete.
	 */
	ret = ad5758_रुको_क्रम_task_complete(st, AD5758_DCDC_CONFIG2,
					    AD5758_DCDC_CONFIG2_BUSY_3WI_MSK);
	अगर (ret < 0)
		वापस ret;

	st->dc_dc_mode = mode;

	वापस ret;
पूर्ण

अटल पूर्णांक ad5758_set_dc_dc_ilim(काष्ठा ad5758_state *st, अचिन्हित पूर्णांक ilim)
अणु
	पूर्णांक ret;

	ret = ad5758_spi_ग_लिखो_mask(st, AD5758_DCDC_CONFIG2,
				    AD5758_DCDC_CONFIG2_ILIMIT_MSK,
				    AD5758_DCDC_CONFIG2_ILIMIT_MODE(ilim));
	अगर (ret < 0)
		वापस ret;
	/*
	 * Poll the BUSY_3WI bit in the DCDC_CONFIG2 रेजिस्टर until it is 0.
	 * This allows the 3-wire पूर्णांकerface communication to complete.
	 */
	वापस ad5758_रुको_क्रम_task_complete(st, AD5758_DCDC_CONFIG2,
					     AD5758_DCDC_CONFIG2_BUSY_3WI_MSK);
पूर्ण

अटल पूर्णांक ad5758_slew_rate_set(काष्ठा ad5758_state *st,
				अचिन्हित पूर्णांक sr_clk_idx,
				अचिन्हित पूर्णांक sr_step_idx)
अणु
	अचिन्हित पूर्णांक mode;
	अचिन्हित दीर्घ पूर्णांक mask;
	पूर्णांक ret;

	mask = AD5758_DAC_CONFIG_SR_EN_MSK |
	       AD5758_DAC_CONFIG_SR_CLOCK_MSK |
	       AD5758_DAC_CONFIG_SR_STEP_MSK;
	mode = AD5758_DAC_CONFIG_SR_EN_MODE(1) |
	       AD5758_DAC_CONFIG_SR_STEP_MODE(sr_step_idx) |
	       AD5758_DAC_CONFIG_SR_CLOCK_MODE(sr_clk_idx);

	ret = ad5758_spi_ग_लिखो_mask(st, AD5758_DAC_CONFIG, mask, mode);
	अगर (ret < 0)
		वापस ret;

	/* Wait to allow समय क्रम the पूर्णांकernal calibrations to complete */
	वापस ad5758_रुको_क्रम_task_complete(st, AD5758_DIGITAL_DIAG_RESULTS,
					     AD5758_CAL_MEM_UNREFRESHED_MSK);
पूर्ण

अटल पूर्णांक ad5758_slew_rate_config(काष्ठा ad5758_state *st)
अणु
	अचिन्हित पूर्णांक sr_clk_idx, sr_step_idx;
	पूर्णांक i, res;
	s64 dअगरf_new, dअगरf_old;
	u64 sr_step, calc_slew_समय;

	sr_clk_idx = 0;
	sr_step_idx = 0;
	dअगरf_old = S64_MAX;
	/*
	 * The slew समय can be determined by using the क्रमmula:
	 * Slew Time = (Full Scale Out / (Step Size x Update Clk Freq))
	 * where Slew समय is expressed in microseconds
	 * Given the desired slew समय, the following algorithm determines the
	 * best match क्रम the step size and the update घड़ी frequency.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(ad5758_sr_clk); i++) अणु
		/*
		 * Go through each valid update घड़ी freq and determine a raw
		 * value क्रम the step size by using the क्रमmula:
		 * Step Size = Full Scale Out / (Update Clk Freq * Slew Time)
		 */
		sr_step = AD5758_FULL_SCALE_MICRO;
		करो_भाग(sr_step, ad5758_sr_clk[i]);
		करो_भाग(sr_step, st->slew_समय);
		/*
		 * After a raw value क्रम step size was determined, find the
		 * बंदst valid match
		 */
		res = ad5758_find_बंदst_match(ad5758_sr_step,
						ARRAY_SIZE(ad5758_sr_step),
						sr_step);
		/* Calculate the slew समय */
		calc_slew_समय = AD5758_FULL_SCALE_MICRO;
		करो_भाग(calc_slew_समय, ad5758_sr_step[res]);
		करो_भाग(calc_slew_समय, ad5758_sr_clk[i]);
		/*
		 * Determine with how many microseconds the calculated slew समय
		 * is dअगरferent from the desired slew समय and store the dअगरf
		 * क्रम the next iteration
		 */
		dअगरf_new = असल(st->slew_समय - calc_slew_समय);
		अगर (dअगरf_new < dअगरf_old) अणु
			dअगरf_old = dअगरf_new;
			sr_clk_idx = i;
			sr_step_idx = res;
		पूर्ण
	पूर्ण

	वापस ad5758_slew_rate_set(st, sr_clk_idx, sr_step_idx);
पूर्ण

अटल पूर्णांक ad5758_set_out_range(काष्ठा ad5758_state *st, पूर्णांक range)
अणु
	पूर्णांक ret;

	ret = ad5758_spi_ग_लिखो_mask(st, AD5758_DAC_CONFIG,
				    AD5758_DAC_CONFIG_RANGE_MSK,
				    AD5758_DAC_CONFIG_RANGE_MODE(range));
	अगर (ret < 0)
		वापस ret;

	/* Wait to allow समय क्रम the पूर्णांकernal calibrations to complete */
	वापस ad5758_रुको_क्रम_task_complete(st, AD5758_DIGITAL_DIAG_RESULTS,
					     AD5758_CAL_MEM_UNREFRESHED_MSK);
पूर्ण

अटल पूर्णांक ad5758_पूर्णांकernal_buffers_en(काष्ठा ad5758_state *st, bool enable)
अणु
	पूर्णांक ret;

	ret = ad5758_spi_ग_लिखो_mask(st, AD5758_DAC_CONFIG,
				    AD5758_DAC_CONFIG_INT_EN_MSK,
				    AD5758_DAC_CONFIG_INT_EN_MODE(enable));
	अगर (ret < 0)
		वापस ret;

	/* Wait to allow समय क्रम the पूर्णांकernal calibrations to complete */
	वापस ad5758_रुको_क्रम_task_complete(st, AD5758_DIGITAL_DIAG_RESULTS,
					     AD5758_CAL_MEM_UNREFRESHED_MSK);
पूर्ण

अटल पूर्णांक ad5758_reset(काष्ठा ad5758_state *st)
अणु
	अगर (st->gpio_reset) अणु
		gpiod_set_value(st->gpio_reset, 0);
		usleep_range(100, 1000);
		gpiod_set_value(st->gpio_reset, 1);
		usleep_range(100, 1000);

		वापस 0;
	पूर्ण अन्यथा अणु
		/* Perक्रमm a software reset */
		वापस ad5758_soft_reset(st);
	पूर्ण
पूर्ण

अटल पूर्णांक ad5758_reg_access(काष्ठा iio_dev *indio_dev,
			     अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक ग_लिखोval,
			     अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ad5758_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	अगर (पढ़ोval) अणु
		ret = ad5758_spi_reg_पढ़ो(st, reg);
		अगर (ret < 0) अणु
			mutex_unlock(&st->lock);
			वापस ret;
		पूर्ण

		*पढ़ोval = ret;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = ad5758_spi_reg_ग_लिखो(st, reg, ग_लिखोval);
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5758_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad5758_state *st = iio_priv(indio_dev);
	पूर्णांक max, min, ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		ret = ad5758_spi_reg_पढ़ो(st, AD5758_DAC_INPUT);
		mutex_unlock(&st->lock);
		अगर (ret < 0)
			वापस ret;

		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		min = st->out_range.min;
		max = st->out_range.max;
		*val = (max - min) / 1000;
		*val2 = 16;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		min = st->out_range.min;
		max = st->out_range.max;
		*val = ((min * (1 << 16)) / (max - min)) / 1000;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5758_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा ad5758_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		ret = ad5758_spi_reg_ग_लिखो(st, AD5758_DAC_INPUT, val);
		mutex_unlock(&st->lock);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ad5758_पढ़ो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
				     uपूर्णांकptr_t priv,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     अक्षर *buf)
अणु
	काष्ठा ad5758_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", st->pwr_करोwn);
पूर्ण

अटल sमाप_प्रकार ad5758_ग_लिखो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
				      uपूर्णांकptr_t priv,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ad5758_state *st = iio_priv(indio_dev);
	bool pwr_करोwn;
	अचिन्हित पूर्णांक dac_config_mode, val;
	अचिन्हित दीर्घ पूर्णांक dac_config_msk;
	पूर्णांक ret;

	ret = kstrtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	mutex_lock(&st->lock);
	अगर (pwr_करोwn)
		val = 0;
	अन्यथा
		val = 1;

	dac_config_mode = AD5758_DAC_CONFIG_OUT_EN_MODE(val) |
			  AD5758_DAC_CONFIG_INT_EN_MODE(val);
	dac_config_msk = AD5758_DAC_CONFIG_OUT_EN_MSK |
			 AD5758_DAC_CONFIG_INT_EN_MSK;

	ret = ad5758_spi_ग_लिखो_mask(st, AD5758_DAC_CONFIG,
				    dac_config_msk,
				    dac_config_mode);
	अगर (ret < 0)
		जाओ err_unlock;

	st->pwr_करोwn = pwr_करोwn;

err_unlock:
	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5758_info = अणु
	.पढ़ो_raw = ad5758_पढ़ो_raw,
	.ग_लिखो_raw = ad5758_ग_लिखो_raw,
	.debugfs_reg_access = &ad5758_reg_access,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5758_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5758_पढ़ो_घातerकरोwn,
		.ग_लिखो = ad5758_ग_लिखो_घातerकरोwn,
		.shared = IIO_SHARED_BY_TYPE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

#घोषणा AD5758_DAC_CHAN(_chan_type) अणु				\
	.type = (_chan_type),					\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_RAW) |	\
		BIT(IIO_CHAN_INFO_SCALE) |			\
		BIT(IIO_CHAN_INFO_OFFSET),			\
	.indexed = 1,						\
	.output = 1,						\
	.ext_info = ad5758_ext_info,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad5758_voltage_ch[] = अणु
	AD5758_DAC_CHAN(IIO_VOLTAGE)
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad5758_current_ch[] = अणु
	AD5758_DAC_CHAN(IIO_CURRENT)
पूर्ण;

अटल bool ad5758_is_valid_mode(क्रमागत ad5758_dc_dc_mode mode)
अणु
	चयन (mode) अणु
	हाल AD5758_DCDC_MODE_DPC_CURRENT:
	हाल AD5758_DCDC_MODE_DPC_VOLTAGE:
	हाल AD5758_DCDC_MODE_PPC_CURRENT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5758_crc_disable(काष्ठा ad5758_state *st)
अणु
	अचिन्हित पूर्णांक mask;

	mask = (AD5758_WR_FLAG_MSK(AD5758_DIGITAL_DIAG_CONFIG) << 24) | 0x5C3A;
	st->d32[0] = cpu_to_be32(mask);

	वापस spi_ग_लिखो(st->spi, &st->d32[0], 4);
पूर्ण

अटल पूर्णांक ad5758_find_out_range(काष्ठा ad5758_state *st,
				 स्थिर काष्ठा ad5758_range *range,
				 अचिन्हित पूर्णांक size,
				 पूर्णांक min, पूर्णांक max)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर ((min == range[i].min) && (max == range[i].max)) अणु
			st->out_range.reg = range[i].reg;
			st->out_range.min = range[i].min;
			st->out_range.max = range[i].max;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5758_parse_dt(काष्ठा ad5758_state *st)
अणु
	अचिन्हित पूर्णांक पंचांगp, पंचांगparray[2], size;
	स्थिर काष्ठा ad5758_range *range;
	पूर्णांक *index, ret;

	st->dc_dc_ilim = 0;
	ret = device_property_पढ़ो_u32(&st->spi->dev,
				       "adi,dc-dc-ilim-microamp", &पंचांगp);
	अगर (ret) अणु
		dev_dbg(&st->spi->dev,
			"Missing \"dc-dc-ilim-microamp\" property\n");
	पूर्ण अन्यथा अणु
		index = द्वा_खोज(&पंचांगp, ad5758_dc_dc_ilim,
				ARRAY_SIZE(ad5758_dc_dc_ilim),
				माप(पूर्णांक), cmpfunc);
		अगर (!index)
			dev_dbg(&st->spi->dev, "dc-dc-ilim out of range\n");
		अन्यथा
			st->dc_dc_ilim = index - ad5758_dc_dc_ilim;
	पूर्ण

	ret = device_property_पढ़ो_u32(&st->spi->dev, "adi,dc-dc-mode",
				       &st->dc_dc_mode);
	अगर (ret) अणु
		dev_err(&st->spi->dev, "Missing \"dc-dc-mode\" property\n");
		वापस ret;
	पूर्ण

	अगर (!ad5758_is_valid_mode(st->dc_dc_mode))
		वापस -EINVAL;

	अगर (st->dc_dc_mode == AD5758_DCDC_MODE_DPC_VOLTAGE) अणु
		ret = device_property_पढ़ो_u32_array(&st->spi->dev,
						     "adi,range-microvolt",
						     पंचांगparray, 2);
		अगर (ret) अणु
			dev_err(&st->spi->dev,
				"Missing \"range-microvolt\" property\n");
			वापस ret;
		पूर्ण
		range = ad5758_voltage_range;
		size = ARRAY_SIZE(ad5758_voltage_range);
	पूर्ण अन्यथा अणु
		ret = device_property_पढ़ो_u32_array(&st->spi->dev,
						     "adi,range-microamp",
						     पंचांगparray, 2);
		अगर (ret) अणु
			dev_err(&st->spi->dev,
				"Missing \"range-microamp\" property\n");
			वापस ret;
		पूर्ण
		range = ad5758_current_range;
		size = ARRAY_SIZE(ad5758_current_range);
	पूर्ण

	ret = ad5758_find_out_range(st, range, size, पंचांगparray[0], पंचांगparray[1]);
	अगर (ret) अणु
		dev_err(&st->spi->dev, "range invalid\n");
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(&st->spi->dev, "adi,slew-time-us", &पंचांगp);
	अगर (ret) अणु
		dev_dbg(&st->spi->dev, "Missing \"slew-time-us\" property\n");
		st->slew_समय = 0;
	पूर्ण अन्यथा अणु
		st->slew_समय = पंचांगp;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad5758_init(काष्ठा ad5758_state *st)
अणु
	पूर्णांक regval, ret;

	st->gpio_reset = devm_gpiod_get_optional(&st->spi->dev, "reset",
						 GPIOD_OUT_HIGH);
	अगर (IS_ERR(st->gpio_reset))
		वापस PTR_ERR(st->gpio_reset);

	/* Disable CRC checks */
	ret = ad5758_crc_disable(st);
	अगर (ret < 0)
		वापस ret;

	/* Perक्रमm a reset */
	ret = ad5758_reset(st);
	अगर (ret < 0)
		वापस ret;

	/* Disable CRC checks */
	ret = ad5758_crc_disable(st);
	अगर (ret < 0)
		वापस ret;

	/* Perक्रमm a calibration memory refresh */
	ret = ad5758_calib_mem_refresh(st);
	अगर (ret < 0)
		वापस ret;

	regval = ad5758_spi_reg_पढ़ो(st, AD5758_DIGITAL_DIAG_RESULTS);
	अगर (regval < 0)
		वापस regval;

	/* Clear all the error flags */
	ret = ad5758_spi_reg_ग_लिखो(st, AD5758_DIGITAL_DIAG_RESULTS, regval);
	अगर (ret < 0)
		वापस ret;

	/* Set the dc-to-dc current limit */
	ret = ad5758_set_dc_dc_ilim(st, st->dc_dc_ilim);
	अगर (ret < 0)
		वापस ret;

	/* Configure the dc-to-dc controller mode */
	ret = ad5758_set_dc_dc_conv_mode(st, st->dc_dc_mode);
	अगर (ret < 0)
		वापस ret;

	/* Configure the output range */
	ret = ad5758_set_out_range(st, st->out_range.reg);
	अगर (ret < 0)
		वापस ret;

	/* Enable Slew Rate Control, set the slew rate घड़ी and step */
	अगर (st->slew_समय) अणु
		ret = ad5758_slew_rate_config(st);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Power up the DAC and पूर्णांकernal (INT) amplअगरiers */
	ret = ad5758_पूर्णांकernal_buffers_en(st, 1);
	अगर (ret < 0)
		वापस ret;

	/* Enable VIOUT */
	वापस ad5758_spi_ग_लिखो_mask(st, AD5758_DAC_CONFIG,
				     AD5758_DAC_CONFIG_OUT_EN_MSK,
				     AD5758_DAC_CONFIG_OUT_EN_MODE(1));
पूर्ण

अटल पूर्णांक ad5758_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad5758_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	mutex_init(&st->lock);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5758_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->num_channels = 1;

	ret = ad5758_parse_dt(st);
	अगर (ret < 0)
		वापस ret;

	अगर (st->dc_dc_mode == AD5758_DCDC_MODE_DPC_VOLTAGE)
		indio_dev->channels = ad5758_voltage_ch;
	अन्यथा
		indio_dev->channels = ad5758_current_ch;

	ret = ad5758_init(st);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "AD5758 init failed\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&st->spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5758_id[] = अणु
	अणु "ad5758", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5758_id);

अटल स्थिर काष्ठा of_device_id ad5758_of_match[] = अणु
        अणु .compatible = "adi,ad5758" पूर्ण,
        अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5758_of_match);

अटल काष्ठा spi_driver ad5758_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = ad5758_of_match,
	पूर्ण,
	.probe = ad5758_probe,
	.id_table = ad5758_id,
पूर्ण;

module_spi_driver(ad5758_driver);

MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5758 DAC");
MODULE_LICENSE("GPL v2");
