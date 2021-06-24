<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MPU3050 gyroscope driver
 *
 * Copyright (C) 2016 Linaro Ltd.
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * Based on the input subप्रणाली driver, Copyright (C) 2011 Wistron Co.Ltd
 * Joseph Lai <joseph_lai@wistron.com> and trimmed करोwn by
 * Alan Cox <alan@linux.पूर्णांकel.com> in turn based on bma023.c.
 * Device behaviour based on a misc driver posted by Nathan Royer in 2011.
 *
 * TODO: add support क्रम setting up the low pass 3dB frequency.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>

#समावेश "mpu3050.h"

#घोषणा MPU3050_CHIP_ID		0x68
#घोषणा MPU3050_CHIP_ID_MASK	0x7E

/*
 * Register map: anything suffixed *_H is a big-endian high byte and always
 * followed by the corresponding low byte (*_L) even though these are not
 * explicitly included in the रेजिस्टर definitions.
 */
#घोषणा MPU3050_CHIP_ID_REG	0x00
#घोषणा MPU3050_PRODUCT_ID_REG	0x01
#घोषणा MPU3050_XG_OFFS_TC	0x05
#घोषणा MPU3050_YG_OFFS_TC	0x08
#घोषणा MPU3050_ZG_OFFS_TC	0x0B
#घोषणा MPU3050_X_OFFS_USR_H	0x0C
#घोषणा MPU3050_Y_OFFS_USR_H	0x0E
#घोषणा MPU3050_Z_OFFS_USR_H	0x10
#घोषणा MPU3050_FIFO_EN		0x12
#घोषणा MPU3050_AUX_VDDIO	0x13
#घोषणा MPU3050_SLV_ADDR	0x14
#घोषणा MPU3050_SMPLRT_DIV	0x15
#घोषणा MPU3050_DLPF_FS_SYNC	0x16
#घोषणा MPU3050_INT_CFG		0x17
#घोषणा MPU3050_AUX_ADDR	0x18
#घोषणा MPU3050_INT_STATUS	0x1A
#घोषणा MPU3050_TEMP_H		0x1B
#घोषणा MPU3050_XOUT_H		0x1D
#घोषणा MPU3050_YOUT_H		0x1F
#घोषणा MPU3050_ZOUT_H		0x21
#घोषणा MPU3050_DMP_CFG1	0x35
#घोषणा MPU3050_DMP_CFG2	0x36
#घोषणा MPU3050_BANK_SEL	0x37
#घोषणा MPU3050_MEM_START_ADDR	0x38
#घोषणा MPU3050_MEM_R_W		0x39
#घोषणा MPU3050_FIFO_COUNT_H	0x3A
#घोषणा MPU3050_FIFO_R		0x3C
#घोषणा MPU3050_USR_CTRL	0x3D
#घोषणा MPU3050_PWR_MGM		0x3E

/* MPU memory bank पढ़ो options */
#घोषणा MPU3050_MEM_PRFTCH	BIT(5)
#घोषणा MPU3050_MEM_USER_BANK	BIT(4)
/* Bits 8-11 select memory bank */
#घोषणा MPU3050_MEM_RAM_BANK_0	0
#घोषणा MPU3050_MEM_RAM_BANK_1	1
#घोषणा MPU3050_MEM_RAM_BANK_2	2
#घोषणा MPU3050_MEM_RAM_BANK_3	3
#घोषणा MPU3050_MEM_OTP_BANK_0	4

#घोषणा MPU3050_AXIS_REGS(axis) (MPU3050_XOUT_H + (axis * 2))

/* Register bits */

/* FIFO Enable */
#घोषणा MPU3050_FIFO_EN_FOOTER		BIT(0)
#घोषणा MPU3050_FIFO_EN_AUX_ZOUT	BIT(1)
#घोषणा MPU3050_FIFO_EN_AUX_YOUT	BIT(2)
#घोषणा MPU3050_FIFO_EN_AUX_XOUT	BIT(3)
#घोषणा MPU3050_FIFO_EN_GYRO_ZOUT	BIT(4)
#घोषणा MPU3050_FIFO_EN_GYRO_YOUT	BIT(5)
#घोषणा MPU3050_FIFO_EN_GYRO_XOUT	BIT(6)
#घोषणा MPU3050_FIFO_EN_TEMP_OUT	BIT(7)

/*
 * Digital Low Pass filter (DLPF)
 * Full Scale (FS)
 * and Synchronization
 */
#घोषणा MPU3050_EXT_SYNC_NONE		0x00
#घोषणा MPU3050_EXT_SYNC_TEMP		0x20
#घोषणा MPU3050_EXT_SYNC_GYROX		0x40
#घोषणा MPU3050_EXT_SYNC_GYROY		0x60
#घोषणा MPU3050_EXT_SYNC_GYROZ		0x80
#घोषणा MPU3050_EXT_SYNC_ACCELX	0xA0
#घोषणा MPU3050_EXT_SYNC_ACCELY	0xC0
#घोषणा MPU3050_EXT_SYNC_ACCELZ	0xE0
#घोषणा MPU3050_EXT_SYNC_MASK		0xE0
#घोषणा MPU3050_EXT_SYNC_SHIFT		5

#घोषणा MPU3050_FS_250DPS		0x00
#घोषणा MPU3050_FS_500DPS		0x08
#घोषणा MPU3050_FS_1000DPS		0x10
#घोषणा MPU3050_FS_2000DPS		0x18
#घोषणा MPU3050_FS_MASK			0x18
#घोषणा MPU3050_FS_SHIFT		3

#घोषणा MPU3050_DLPF_CFG_256HZ_NOLPF2	0x00
#घोषणा MPU3050_DLPF_CFG_188HZ		0x01
#घोषणा MPU3050_DLPF_CFG_98HZ		0x02
#घोषणा MPU3050_DLPF_CFG_42HZ		0x03
#घोषणा MPU3050_DLPF_CFG_20HZ		0x04
#घोषणा MPU3050_DLPF_CFG_10HZ		0x05
#घोषणा MPU3050_DLPF_CFG_5HZ		0x06
#घोषणा MPU3050_DLPF_CFG_2100HZ_NOLPF	0x07
#घोषणा MPU3050_DLPF_CFG_MASK		0x07
#घोषणा MPU3050_DLPF_CFG_SHIFT		0

/* Interrupt config */
#घोषणा MPU3050_INT_RAW_RDY_EN		BIT(0)
#घोषणा MPU3050_INT_DMP_DONE_EN		BIT(1)
#घोषणा MPU3050_INT_MPU_RDY_EN		BIT(2)
#घोषणा MPU3050_INT_ANYRD_2CLEAR	BIT(4)
#घोषणा MPU3050_INT_LATCH_EN		BIT(5)
#घोषणा MPU3050_INT_OPEN		BIT(6)
#घोषणा MPU3050_INT_ACTL		BIT(7)
/* Interrupt status */
#घोषणा MPU3050_INT_STATUS_RAW_RDY	BIT(0)
#घोषणा MPU3050_INT_STATUS_DMP_DONE	BIT(1)
#घोषणा MPU3050_INT_STATUS_MPU_RDY	BIT(2)
#घोषणा MPU3050_INT_STATUS_FIFO_OVFLW	BIT(7)
/* USR_CTRL */
#घोषणा MPU3050_USR_CTRL_FIFO_EN	BIT(6)
#घोषणा MPU3050_USR_CTRL_AUX_IF_EN	BIT(5)
#घोषणा MPU3050_USR_CTRL_AUX_IF_RST	BIT(3)
#घोषणा MPU3050_USR_CTRL_FIFO_RST	BIT(1)
#घोषणा MPU3050_USR_CTRL_GYRO_RST	BIT(0)
/* PWR_MGM */
#घोषणा MPU3050_PWR_MGM_PLL_X		0x01
#घोषणा MPU3050_PWR_MGM_PLL_Y		0x02
#घोषणा MPU3050_PWR_MGM_PLL_Z		0x03
#घोषणा MPU3050_PWR_MGM_CLKSEL_MASK	0x07
#घोषणा MPU3050_PWR_MGM_STBY_ZG		BIT(3)
#घोषणा MPU3050_PWR_MGM_STBY_YG		BIT(4)
#घोषणा MPU3050_PWR_MGM_STBY_XG		BIT(5)
#घोषणा MPU3050_PWR_MGM_SLEEP		BIT(6)
#घोषणा MPU3050_PWR_MGM_RESET		BIT(7)
#घोषणा MPU3050_PWR_MGM_MASK		0xff

/*
 * Fullscale precision is (क्रम finest precision) +/- 250 deg/s, so the full
 * scale is actually 500 deg/s. All 16 bits are then used to cover this scale,
 * in two's complement.
 */
अटल अचिन्हित पूर्णांक mpu3050_fs_precision[] = अणु
	IIO_DEGREE_TO_RAD(250),
	IIO_DEGREE_TO_RAD(500),
	IIO_DEGREE_TO_RAD(1000),
	IIO_DEGREE_TO_RAD(2000)
पूर्ण;

/*
 * Regulator names
 */
अटल स्थिर अक्षर mpu3050_reg_vdd[] = "vdd";
अटल स्थिर अक्षर mpu3050_reg_vlogic[] = "vlogic";

अटल अचिन्हित पूर्णांक mpu3050_get_freq(काष्ठा mpu3050 *mpu3050)
अणु
	अचिन्हित पूर्णांक freq;

	अगर (mpu3050->lpf == MPU3050_DLPF_CFG_256HZ_NOLPF2)
		freq = 8000;
	अन्यथा
		freq = 1000;
	freq /= (mpu3050->भागisor + 1);

	वापस freq;
पूर्ण

अटल पूर्णांक mpu3050_start_sampling(काष्ठा mpu3050 *mpu3050)
अणु
	__be16 raw_val[3];
	पूर्णांक ret;
	पूर्णांक i;

	/* Reset */
	ret = regmap_update_bits(mpu3050->map, MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_RESET, MPU3050_PWR_MGM_RESET);
	अगर (ret)
		वापस ret;

	/* Turn on the Z-axis PLL */
	ret = regmap_update_bits(mpu3050->map, MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_CLKSEL_MASK,
				 MPU3050_PWR_MGM_PLL_Z);
	अगर (ret)
		वापस ret;

	/* Write calibration offset रेजिस्टरs */
	क्रम (i = 0; i < 3; i++)
		raw_val[i] = cpu_to_be16(mpu3050->calibration[i]);

	ret = regmap_bulk_ग_लिखो(mpu3050->map, MPU3050_X_OFFS_USR_H, raw_val,
				माप(raw_val));
	अगर (ret)
		वापस ret;

	/* Set low pass filter (sample rate), sync and full scale */
	ret = regmap_ग_लिखो(mpu3050->map, MPU3050_DLPF_FS_SYNC,
			   MPU3050_EXT_SYNC_NONE << MPU3050_EXT_SYNC_SHIFT |
			   mpu3050->fullscale << MPU3050_FS_SHIFT |
			   mpu3050->lpf << MPU3050_DLPF_CFG_SHIFT);
	अगर (ret)
		वापस ret;

	/* Set up sampling frequency */
	ret = regmap_ग_लिखो(mpu3050->map, MPU3050_SMPLRT_DIV, mpu3050->भागisor);
	अगर (ret)
		वापस ret;

	/*
	 * Max 50 ms start-up समय after setting DLPF_FS_SYNC
	 * according to the data sheet, then रुको क्रम the next sample
	 * at this frequency T = 1000/f ms.
	 */
	msleep(50 + 1000 / mpu3050_get_freq(mpu3050));

	वापस 0;
पूर्ण

अटल पूर्णांक mpu3050_set_8khz_samplerate(काष्ठा mpu3050 *mpu3050)
अणु
	पूर्णांक ret;
	u8 भागisor;
	क्रमागत mpu3050_lpf lpf;

	lpf = mpu3050->lpf;
	भागisor = mpu3050->भागisor;

	mpu3050->lpf = LPF_256_HZ_NOLPF; /* 8 kHz base frequency */
	mpu3050->भागisor = 0; /* Divide by 1 */
	ret = mpu3050_start_sampling(mpu3050);

	mpu3050->lpf = lpf;
	mpu3050->भागisor = भागisor;

	वापस ret;
पूर्ण

अटल पूर्णांक mpu3050_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2,
			    दीर्घ mask)
अणु
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);
	पूर्णांक ret;
	__be16 raw_val;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			/*
			 * The temperature scaling is (x+23000)/280 Celsius
			 * क्रम the "best fit straight line" temperature range
			 * of -30C..85C.  The 23000 includes room temperature
			 * offset of +35C, 280 is the precision scale and x is
			 * the 16-bit चिन्हित पूर्णांकeger reported by hardware.
			 *
			 * Temperature value itself represents temperature of
			 * the sensor die.
			 */
			*val = 23000;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_CALIBBIAS:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val = mpu3050->calibration[chan->scan_index-1];
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = mpu3050_get_freq(mpu3050);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			/* Millidegrees, see about temperature scaling above */
			*val = 1000;
			*val2 = 280;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_ANGL_VEL:
			/*
			 * Convert to the corresponding full scale in
			 * radians. All 16 bits are used with sign to
			 * span the available scale: to account क्रम the one
			 * missing value अगर we multiply by 1/S16_MAX, instead
			 * multiply with 2/U16_MAX.
			 */
			*val = mpu3050_fs_precision[mpu3050->fullscale] * 2;
			*val2 = U16_MAX;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_RAW:
		/* Resume device */
		pm_runसमय_get_sync(mpu3050->dev);
		mutex_lock(&mpu3050->lock);

		ret = mpu3050_set_8khz_samplerate(mpu3050);
		अगर (ret)
			जाओ out_पढ़ो_raw_unlock;

		चयन (chan->type) अणु
		हाल IIO_TEMP:
			ret = regmap_bulk_पढ़ो(mpu3050->map, MPU3050_TEMP_H,
					       &raw_val, माप(raw_val));
			अगर (ret) अणु
				dev_err(mpu3050->dev,
					"error reading temperature\n");
				जाओ out_पढ़ो_raw_unlock;
			पूर्ण

			*val = (s16)be16_to_cpu(raw_val);
			ret = IIO_VAL_INT;

			जाओ out_पढ़ो_raw_unlock;
		हाल IIO_ANGL_VEL:
			ret = regmap_bulk_पढ़ो(mpu3050->map,
				       MPU3050_AXIS_REGS(chan->scan_index-1),
				       &raw_val,
				       माप(raw_val));
			अगर (ret) अणु
				dev_err(mpu3050->dev,
					"error reading axis data\n");
				जाओ out_पढ़ो_raw_unlock;
			पूर्ण

			*val = be16_to_cpu(raw_val);
			ret = IIO_VAL_INT;

			जाओ out_पढ़ो_raw_unlock;
		शेष:
			ret = -EINVAL;
			जाओ out_पढ़ो_raw_unlock;
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;

out_पढ़ो_raw_unlock:
	mutex_unlock(&mpu3050->lock);
	pm_runसमय_mark_last_busy(mpu3050->dev);
	pm_runसमय_put_स्वतःsuspend(mpu3050->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mpu3050_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);
	/*
	 * Couldn't figure out a way to precalculate these at compile समय.
	 */
	अचिन्हित पूर्णांक fs250 =
		DIV_ROUND_CLOSEST(mpu3050_fs_precision[0] * 1000000 * 2,
				  U16_MAX);
	अचिन्हित पूर्णांक fs500 =
		DIV_ROUND_CLOSEST(mpu3050_fs_precision[1] * 1000000 * 2,
				  U16_MAX);
	अचिन्हित पूर्णांक fs1000 =
		DIV_ROUND_CLOSEST(mpu3050_fs_precision[2] * 1000000 * 2,
				  U16_MAX);
	अचिन्हित पूर्णांक fs2000 =
		DIV_ROUND_CLOSEST(mpu3050_fs_precision[3] * 1000000 * 2,
				  U16_MAX);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (chan->type != IIO_ANGL_VEL)
			वापस -EINVAL;
		mpu3050->calibration[chan->scan_index-1] = val;
		वापस 0;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		/*
		 * The max samplerate is 8000 Hz, the minimum
		 * 1000 / 256 ~= 4 Hz
		 */
		अगर (val < 4 || val > 8000)
			वापस -EINVAL;

		/*
		 * Above 1000 Hz we must turn off the digital low pass filter
		 * so we get a base frequency of 8kHz to the भागider
		 */
		अगर (val > 1000) अणु
			mpu3050->lpf = LPF_256_HZ_NOLPF;
			mpu3050->भागisor = DIV_ROUND_CLOSEST(8000, val) - 1;
			वापस 0;
		पूर्ण

		mpu3050->lpf = LPF_188_HZ;
		mpu3050->भागisor = DIV_ROUND_CLOSEST(1000, val) - 1;
		वापस 0;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type != IIO_ANGL_VEL)
			वापस -EINVAL;
		/*
		 * We support +/-250, +/-500, +/-1000 and +/2000 deg/s
		 * which means we need to round to the बंदst radians
		 * which will be roughly +/-4.3, +/-8.7, +/-17.5, +/-35
		 * rad/s. The scale is then क्रम the 16 bits used to cover
		 * it 2/(2^16) of that.
		 */

		/* Just too large, set the max range */
		अगर (val != 0) अणु
			mpu3050->fullscale = FS_2000_DPS;
			वापस 0;
		पूर्ण

		/*
		 * Now we're dealing with fractions below zero in millirad/s
		 * करो some पूर्णांकeger पूर्णांकerpolation and match with the बंदst
		 * fullscale in the table.
		 */
		अगर (val2 <= fs250 ||
		    val2 < ((fs500 + fs250) / 2))
			mpu3050->fullscale = FS_250_DPS;
		अन्यथा अगर (val2 <= fs500 ||
			 val2 < ((fs1000 + fs500) / 2))
			mpu3050->fullscale = FS_500_DPS;
		अन्यथा अगर (val2 <= fs1000 ||
			 val2 < ((fs2000 + fs1000) / 2))
			mpu3050->fullscale = FS_1000_DPS;
		अन्यथा
			/* Catch-all */
			mpu3050->fullscale = FS_2000_DPS;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t mpu3050_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	स्थिर काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);
	पूर्णांक ret;
	/*
	 * Temperature 1*16 bits
	 * Three axes 3*16 bits
	 * Timestamp 64 bits (4*16 bits)
	 * Sum total 8*16 bits
	 */
	__be16 hw_values[8];
	s64 बारtamp;
	अचिन्हित पूर्णांक datums_from_fअगरo = 0;

	/*
	 * If we're using the hardware trigger, get the precise बारtamp from
	 * the top half of the thपढ़ोed IRQ handler. Otherwise get the
	 * बारtamp here so it will be बंद in समय to the actual values
	 * पढ़ो from the रेजिस्टरs.
	 */
	अगर (iio_trigger_using_own(indio_dev))
		बारtamp = mpu3050->hw_बारtamp;
	अन्यथा
		बारtamp = iio_get_समय_ns(indio_dev);

	mutex_lock(&mpu3050->lock);

	/* Using the hardware IRQ trigger? Check the buffer then. */
	अगर (mpu3050->hw_irq_trigger) अणु
		__be16 raw_fअगरocnt;
		u16 fअगरocnt;
		/* X, Y, Z + temperature */
		अचिन्हित पूर्णांक bytes_per_datum = 8;
		bool fअगरo_overflow = false;

		ret = regmap_bulk_पढ़ो(mpu3050->map,
				       MPU3050_FIFO_COUNT_H,
				       &raw_fअगरocnt,
				       माप(raw_fअगरocnt));
		अगर (ret)
			जाओ out_trigger_unlock;
		fअगरocnt = be16_to_cpu(raw_fअगरocnt);

		अगर (fअगरocnt == 512) अणु
			dev_info(mpu3050->dev,
				 "FIFO overflow! Emptying and resetting FIFO\n");
			fअगरo_overflow = true;
			/* Reset and enable the FIFO */
			ret = regmap_update_bits(mpu3050->map,
						 MPU3050_USR_CTRL,
						 MPU3050_USR_CTRL_FIFO_EN |
						 MPU3050_USR_CTRL_FIFO_RST,
						 MPU3050_USR_CTRL_FIFO_EN |
						 MPU3050_USR_CTRL_FIFO_RST);
			अगर (ret) अणु
				dev_info(mpu3050->dev, "error resetting FIFO\n");
				जाओ out_trigger_unlock;
			पूर्ण
			mpu3050->pending_fअगरo_footer = false;
		पूर्ण

		अगर (fअगरocnt)
			dev_dbg(mpu3050->dev,
				"%d bytes in the FIFO\n",
				fअगरocnt);

		जबतक (!fअगरo_overflow && fअगरocnt > bytes_per_datum) अणु
			अचिन्हित पूर्णांक toपढ़ो;
			अचिन्हित पूर्णांक offset;
			__be16 fअगरo_values[5];

			/*
			 * If there is a FIFO footer in the pipe, first clear
			 * that out. This follows the complex algorithm in the
			 * datasheet that states that you may never leave the
			 * FIFO empty after the first पढ़ोing: you have to
			 * always leave two footer bytes in it. The footer is
			 * in practice just two zero bytes.
			 */
			अगर (mpu3050->pending_fअगरo_footer) अणु
				toपढ़ो = bytes_per_datum + 2;
				offset = 0;
			पूर्ण अन्यथा अणु
				toपढ़ो = bytes_per_datum;
				offset = 1;
				/* Put in some dummy value */
				fअगरo_values[0] = cpu_to_be16(0xAAAA);
			पूर्ण

			ret = regmap_bulk_पढ़ो(mpu3050->map,
					       MPU3050_FIFO_R,
					       &fअगरo_values[offset],
					       toपढ़ो);
			अगर (ret)
				जाओ out_trigger_unlock;

			dev_dbg(mpu3050->dev,
				"%04x %04x %04x %04x %04x\n",
				fअगरo_values[0],
				fअगरo_values[1],
				fअगरo_values[2],
				fअगरo_values[3],
				fअगरo_values[4]);

			/* Index past the footer (fअगरo_values[0]) and push */
			iio_push_to_buffers_with_बारtamp(indio_dev,
							   &fअगरo_values[1],
							   बारtamp);

			fअगरocnt -= toपढ़ो;
			datums_from_fअगरo++;
			mpu3050->pending_fअगरo_footer = true;

			/*
			 * If we're emptying the FIFO, just make sure to
			 * check अगर something new appeared.
			 */
			अगर (fअगरocnt < bytes_per_datum) अणु
				ret = regmap_bulk_पढ़ो(mpu3050->map,
						       MPU3050_FIFO_COUNT_H,
						       &raw_fअगरocnt,
						       माप(raw_fअगरocnt));
				अगर (ret)
					जाओ out_trigger_unlock;
				fअगरocnt = be16_to_cpu(raw_fअगरocnt);
			पूर्ण

			अगर (fअगरocnt < bytes_per_datum)
				dev_dbg(mpu3050->dev,
					"%d bytes left in the FIFO\n",
					fअगरocnt);

			/*
			 * At this poपूर्णांक, the बारtamp that triggered the
			 * hardware पूर्णांकerrupt is no दीर्घer valid क्रम what
			 * we are पढ़ोing (the पूर्णांकerrupt likely fired क्रम
			 * the value on the top of the FIFO), so set the
			 * बारtamp to zero and let userspace deal with it.
			 */
			बारtamp = 0;
		पूर्ण
	पूर्ण

	/*
	 * If we picked some datums from the FIFO that's enough, अन्यथा
	 * fall through and just पढ़ो from the current value रेजिस्टरs.
	 * This happens in two हालs:
	 *
	 * - We are using some other trigger (बाह्यal, like an HRTimer)
	 *   than the sensor's own sample generator. In this हाल the
	 *   sensor is just set to the max sampling frequency and we give
	 *   the trigger a copy of the latest value every समय we get here.
	 *
	 * - The hardware trigger is active but unused and we actually use
	 *   another trigger which calls here with a frequency higher
	 *   than what the device provides data. We will then just पढ़ो
	 *   duplicate values directly from the hardware रेजिस्टरs.
	 */
	अगर (datums_from_fअगरo) अणु
		dev_dbg(mpu3050->dev,
			"read %d datums from the FIFO\n",
			datums_from_fअगरo);
		जाओ out_trigger_unlock;
	पूर्ण

	ret = regmap_bulk_पढ़ो(mpu3050->map, MPU3050_TEMP_H, &hw_values,
			       माप(hw_values));
	अगर (ret) अणु
		dev_err(mpu3050->dev,
			"error reading axis data\n");
		जाओ out_trigger_unlock;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, hw_values, बारtamp);

out_trigger_unlock:
	mutex_unlock(&mpu3050->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mpu3050_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);

	pm_runसमय_get_sync(mpu3050->dev);

	/* Unless we have OUR trigger active, run at full speed */
	अगर (!mpu3050->hw_irq_trigger)
		वापस mpu3050_set_8khz_samplerate(mpu3050);

	वापस 0;
पूर्ण

अटल पूर्णांक mpu3050_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);

	pm_runसमय_mark_last_busy(mpu3050->dev);
	pm_runसमय_put_स्वतःsuspend(mpu3050->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops mpu3050_buffer_setup_ops = अणु
	.preenable = mpu3050_buffer_preenable,
	.postdisable = mpu3050_buffer_postdisable,
पूर्ण;

अटल स्थिर काष्ठा iio_mount_matrix *
mpu3050_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			 स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);

	वापस &mpu3050->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info mpu3050_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_TYPE, mpu3050_get_mount_matrix),
	अणु पूर्ण,
पूर्ण;

#घोषणा MPU3050_AXIS_CHANNEL(axis, index)				\
	अणु								\
		.type = IIO_ANGL_VEL,					\
		.modअगरied = 1,						\
		.channel2 = IIO_MOD_##axis,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
			BIT(IIO_CHAN_INFO_CALIBBIAS),			\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),\
		.ext_info = mpu3050_ext_info,				\
		.scan_index = index,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 16,					\
			.storagebits = 16,				\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mpu3050_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	MPU3050_AXIS_CHANNEL(X, 1),
	MPU3050_AXIS_CHANNEL(Y, 2),
	MPU3050_AXIS_CHANNEL(Z, 3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

/* Four channels apart from बारtamp, scan mask = 0x0f */
अटल स्थिर अचिन्हित दीर्घ mpu3050_scan_masks[] = अणु 0xf, 0 पूर्ण;

/*
 * These are just the hardcoded factors resulting from the more elaborate
 * calculations करोne with fractions in the scale raw get/set functions.
 */
अटल IIO_CONST_ATTR(anglevel_scale_available,
		      "0.000122070 "
		      "0.000274658 "
		      "0.000518798 "
		      "0.001068115");

अटल काष्ठा attribute *mpu3050_attributes[] = अणु
	&iio_स्थिर_attr_anglevel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mpu3050_attribute_group = अणु
	.attrs = mpu3050_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info mpu3050_info = अणु
	.पढ़ो_raw = mpu3050_पढ़ो_raw,
	.ग_लिखो_raw = mpu3050_ग_लिखो_raw,
	.attrs = &mpu3050_attribute_group,
पूर्ण;

/**
 * mpu3050_पढ़ो_mem() - पढ़ो MPU-3050 पूर्णांकernal memory
 * @mpu3050: device to पढ़ो from
 * @bank: target bank
 * @addr: target address
 * @len: number of bytes
 * @buf: the buffer to store the पढ़ो bytes in
 */
अटल पूर्णांक mpu3050_पढ़ो_mem(काष्ठा mpu3050 *mpu3050,
			    u8 bank,
			    u8 addr,
			    u8 len,
			    u8 *buf)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(mpu3050->map,
			   MPU3050_BANK_SEL,
			   bank);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(mpu3050->map,
			   MPU3050_MEM_START_ADDR,
			   addr);
	अगर (ret)
		वापस ret;

	वापस regmap_bulk_पढ़ो(mpu3050->map,
				MPU3050_MEM_R_W,
				buf,
				len);
पूर्ण

अटल पूर्णांक mpu3050_hw_init(काष्ठा mpu3050 *mpu3050)
अणु
	पूर्णांक ret;
	__le64 otp_le;
	u64 otp;

	/* Reset */
	ret = regmap_update_bits(mpu3050->map,
				 MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_RESET,
				 MPU3050_PWR_MGM_RESET);
	अगर (ret)
		वापस ret;

	/* Turn on the PLL */
	ret = regmap_update_bits(mpu3050->map,
				 MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_CLKSEL_MASK,
				 MPU3050_PWR_MGM_PLL_Z);
	अगर (ret)
		वापस ret;

	/* Disable IRQs */
	ret = regmap_ग_लिखो(mpu3050->map,
			   MPU3050_INT_CFG,
			   0);
	अगर (ret)
		वापस ret;

	/* Read out the 8 bytes of OTP (one-समय-programmable) memory */
	ret = mpu3050_पढ़ो_mem(mpu3050,
			       (MPU3050_MEM_PRFTCH |
				MPU3050_MEM_USER_BANK |
				MPU3050_MEM_OTP_BANK_0),
			       0,
			       माप(otp_le),
			       (u8 *)&otp_le);
	अगर (ret)
		वापस ret;

	/* This is device-unique data so it goes पूर्णांकo the entropy pool */
	add_device_अक्रमomness(&otp_le, माप(otp_le));

	otp = le64_to_cpu(otp_le);

	dev_info(mpu3050->dev,
		 "die ID: %04llX, wafer ID: %02llX, A lot ID: %04llX, "
		 "W lot ID: %03llX, WP ID: %01llX, rev ID: %02llX\n",
		 /* Die ID, bits 0-12 */
		 FIELD_GET(GENMASK_ULL(12, 0), otp),
		 /* Wafer ID, bits 13-17 */
		 FIELD_GET(GENMASK_ULL(17, 13), otp),
		 /* A lot ID, bits 18-33 */
		 FIELD_GET(GENMASK_ULL(33, 18), otp),
		 /* W lot ID, bits 34-45 */
		 FIELD_GET(GENMASK_ULL(45, 34), otp),
		 /* WP ID, bits 47-49 */
		 FIELD_GET(GENMASK_ULL(49, 47), otp),
		 /* rev ID, bits 50-55 */
		 FIELD_GET(GENMASK_ULL(55, 50), otp));

	वापस 0;
पूर्ण

अटल पूर्णांक mpu3050_घातer_up(काष्ठा mpu3050 *mpu3050)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(mpu3050->regs), mpu3050->regs);
	अगर (ret) अणु
		dev_err(mpu3050->dev, "cannot enable regulators\n");
		वापस ret;
	पूर्ण
	/*
	 * 20-100 ms start-up समय क्रम रेजिस्टर पढ़ो/ग_लिखो according to
	 * the datasheet, be on the safe side and रुको 200 ms.
	 */
	msleep(200);

	/* Take device out of sleep mode */
	ret = regmap_update_bits(mpu3050->map, MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_SLEEP, 0);
	अगर (ret) अणु
		dev_err(mpu3050->dev, "error setting power mode\n");
		वापस ret;
	पूर्ण
	usleep_range(10000, 20000);

	वापस 0;
पूर्ण

अटल पूर्णांक mpu3050_घातer_करोwn(काष्ठा mpu3050 *mpu3050)
अणु
	पूर्णांक ret;

	/*
	 * Put MPU-3050 पूर्णांकo sleep mode beक्रमe cutting regulators.
	 * This is important, because we may not be the sole user
	 * of the regulator so the घातer may stay on after this, and
	 * then we would be wasting घातer unless we go to sleep mode
	 * first.
	 */
	ret = regmap_update_bits(mpu3050->map, MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_SLEEP, MPU3050_PWR_MGM_SLEEP);
	अगर (ret)
		dev_err(mpu3050->dev, "error putting to sleep\n");

	ret = regulator_bulk_disable(ARRAY_SIZE(mpu3050->regs), mpu3050->regs);
	अगर (ret)
		dev_err(mpu3050->dev, "error disabling regulators\n");

	वापस 0;
पूर्ण

अटल irqवापस_t mpu3050_irq_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_trigger *trig = p;
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);

	अगर (!mpu3050->hw_irq_trigger)
		वापस IRQ_NONE;

	/* Get the समय stamp as बंद in समय as possible */
	mpu3050->hw_बारtamp = iio_get_समय_ns(indio_dev);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t mpu3050_irq_thपढ़ो(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_trigger *trig = p;
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* ACK IRQ and check अगर it was from us */
	ret = regmap_पढ़ो(mpu3050->map, MPU3050_INT_STATUS, &val);
	अगर (ret) अणु
		dev_err(mpu3050->dev, "error reading IRQ status\n");
		वापस IRQ_HANDLED;
	पूर्ण
	अगर (!(val & MPU3050_INT_STATUS_RAW_RDY))
		वापस IRQ_NONE;

	iio_trigger_poll_chained(p);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * mpu3050_drdy_trigger_set_state() - set data पढ़ोy पूर्णांकerrupt state
 * @trig: trigger instance
 * @enable: true अगर trigger should be enabled, false to disable
 */
अटल पूर्णांक mpu3050_drdy_trigger_set_state(काष्ठा iio_trigger *trig,
					  bool enable)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Disabling trigger: disable पूर्णांकerrupt and वापस */
	अगर (!enable) अणु
		/* Disable all पूर्णांकerrupts */
		ret = regmap_ग_लिखो(mpu3050->map,
				   MPU3050_INT_CFG,
				   0);
		अगर (ret)
			dev_err(mpu3050->dev, "error disabling IRQ\n");

		/* Clear IRQ flag */
		ret = regmap_पढ़ो(mpu3050->map, MPU3050_INT_STATUS, &val);
		अगर (ret)
			dev_err(mpu3050->dev, "error clearing IRQ status\n");

		/* Disable all things in the FIFO and reset it */
		ret = regmap_ग_लिखो(mpu3050->map, MPU3050_FIFO_EN, 0);
		अगर (ret)
			dev_err(mpu3050->dev, "error disabling FIFO\n");

		ret = regmap_ग_लिखो(mpu3050->map, MPU3050_USR_CTRL,
				   MPU3050_USR_CTRL_FIFO_RST);
		अगर (ret)
			dev_err(mpu3050->dev, "error resetting FIFO\n");

		pm_runसमय_mark_last_busy(mpu3050->dev);
		pm_runसमय_put_स्वतःsuspend(mpu3050->dev);
		mpu3050->hw_irq_trigger = false;

		वापस 0;
	पूर्ण अन्यथा अणु
		/* Else we're enabling the trigger from this poपूर्णांक */
		pm_runसमय_get_sync(mpu3050->dev);
		mpu3050->hw_irq_trigger = true;

		/* Disable all things in the FIFO */
		ret = regmap_ग_लिखो(mpu3050->map, MPU3050_FIFO_EN, 0);
		अगर (ret)
			वापस ret;

		/* Reset and enable the FIFO */
		ret = regmap_update_bits(mpu3050->map, MPU3050_USR_CTRL,
					 MPU3050_USR_CTRL_FIFO_EN |
					 MPU3050_USR_CTRL_FIFO_RST,
					 MPU3050_USR_CTRL_FIFO_EN |
					 MPU3050_USR_CTRL_FIFO_RST);
		अगर (ret)
			वापस ret;

		mpu3050->pending_fअगरo_footer = false;

		/* Turn on the FIFO क्रम temp+X+Y+Z */
		ret = regmap_ग_लिखो(mpu3050->map, MPU3050_FIFO_EN,
				   MPU3050_FIFO_EN_TEMP_OUT |
				   MPU3050_FIFO_EN_GYRO_XOUT |
				   MPU3050_FIFO_EN_GYRO_YOUT |
				   MPU3050_FIFO_EN_GYRO_ZOUT |
				   MPU3050_FIFO_EN_FOOTER);
		अगर (ret)
			वापस ret;

		/* Configure the sample engine */
		ret = mpu3050_start_sampling(mpu3050);
		अगर (ret)
			वापस ret;

		/* Clear IRQ flag */
		ret = regmap_पढ़ो(mpu3050->map, MPU3050_INT_STATUS, &val);
		अगर (ret)
			dev_err(mpu3050->dev, "error clearing IRQ status\n");

		/* Give us पूर्णांकerrupts whenever there is new data पढ़ोy */
		val = MPU3050_INT_RAW_RDY_EN;

		अगर (mpu3050->irq_actl)
			val |= MPU3050_INT_ACTL;
		अगर (mpu3050->irq_latch)
			val |= MPU3050_INT_LATCH_EN;
		अगर (mpu3050->irq_खोलोdrain)
			val |= MPU3050_INT_OPEN;

		ret = regmap_ग_लिखो(mpu3050->map, MPU3050_INT_CFG, val);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops mpu3050_trigger_ops = अणु
	.set_trigger_state = mpu3050_drdy_trigger_set_state,
पूर्ण;

अटल पूर्णांक mpu3050_trigger_probe(काष्ठा iio_dev *indio_dev, पूर्णांक irq)
अणु
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);
	अचिन्हित दीर्घ irq_trig;
	पूर्णांक ret;

	mpu3050->trig = devm_iio_trigger_alloc(&indio_dev->dev,
					       "%s-dev%d",
					       indio_dev->name,
					       indio_dev->id);
	अगर (!mpu3050->trig)
		वापस -ENOMEM;

	/* Check अगर IRQ is खोलो drain */
	अगर (of_property_पढ़ो_bool(mpu3050->dev->of_node, "drive-open-drain"))
		mpu3050->irq_खोलोdrain = true;

	irq_trig = irqd_get_trigger_type(irq_get_irq_data(irq));
	/*
	 * Configure the पूर्णांकerrupt generator hardware to supply whatever
	 * the पूर्णांकerrupt is configured क्रम, edges low/high level low/high,
	 * we can provide it all.
	 */
	चयन (irq_trig) अणु
	हाल IRQF_TRIGGER_RISING:
		dev_info(&indio_dev->dev,
			 "pulse interrupts on the rising edge\n");
		अवरोध;
	हाल IRQF_TRIGGER_FALLING:
		mpu3050->irq_actl = true;
		dev_info(&indio_dev->dev,
			 "pulse interrupts on the falling edge\n");
		अवरोध;
	हाल IRQF_TRIGGER_HIGH:
		mpu3050->irq_latch = true;
		dev_info(&indio_dev->dev,
			 "interrupts active high level\n");
		/*
		 * With level IRQs, we mask the IRQ until it is processed,
		 * but with edge IRQs (pulses) we can queue several पूर्णांकerrupts
		 * in the top half.
		 */
		irq_trig |= IRQF_ONESHOT;
		अवरोध;
	हाल IRQF_TRIGGER_LOW:
		mpu3050->irq_latch = true;
		mpu3050->irq_actl = true;
		irq_trig |= IRQF_ONESHOT;
		dev_info(&indio_dev->dev,
			 "interrupts active low level\n");
		अवरोध;
	शेष:
		/* This is the most preferred mode, अगर possible */
		dev_err(&indio_dev->dev,
			"unsupported IRQ trigger specified (%lx), enforce "
			"rising edge\n", irq_trig);
		irq_trig = IRQF_TRIGGER_RISING;
		अवरोध;
	पूर्ण

	/* An खोलो drain line can be shared with several devices */
	अगर (mpu3050->irq_खोलोdrain)
		irq_trig |= IRQF_SHARED;

	ret = request_thपढ़ोed_irq(irq,
				   mpu3050_irq_handler,
				   mpu3050_irq_thपढ़ो,
				   irq_trig,
				   mpu3050->trig->name,
				   mpu3050->trig);
	अगर (ret) अणु
		dev_err(mpu3050->dev,
			"can't get IRQ %d, error %d\n", irq, ret);
		वापस ret;
	पूर्ण

	mpu3050->irq = irq;
	mpu3050->trig->dev.parent = mpu3050->dev;
	mpu3050->trig->ops = &mpu3050_trigger_ops;
	iio_trigger_set_drvdata(mpu3050->trig, indio_dev);

	ret = iio_trigger_रेजिस्टर(mpu3050->trig);
	अगर (ret)
		वापस ret;

	indio_dev->trig = iio_trigger_get(mpu3050->trig);

	वापस 0;
पूर्ण

पूर्णांक mpu3050_common_probe(काष्ठा device *dev,
			 काष्ठा regmap *map,
			 पूर्णांक irq,
			 स्थिर अक्षर *name)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा mpu3050 *mpu3050;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*mpu3050));
	अगर (!indio_dev)
		वापस -ENOMEM;
	mpu3050 = iio_priv(indio_dev);

	mpu3050->dev = dev;
	mpu3050->map = map;
	mutex_init(&mpu3050->lock);
	/* Default fullscale: 2000 degrees per second */
	mpu3050->fullscale = FS_2000_DPS;
	/* 1 kHz, भागide by 100, शेष frequency = 10 Hz */
	mpu3050->lpf = MPU3050_DLPF_CFG_188HZ;
	mpu3050->भागisor = 99;

	/* Read the mounting matrix, अगर present */
	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix", &mpu3050->orientation);
	अगर (ret)
		वापस ret;

	/* Fetch and turn on regulators */
	mpu3050->regs[0].supply = mpu3050_reg_vdd;
	mpu3050->regs[1].supply = mpu3050_reg_vlogic;
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(mpu3050->regs),
				      mpu3050->regs);
	अगर (ret) अणु
		dev_err(dev, "Cannot get regulators\n");
		वापस ret;
	पूर्ण

	ret = mpu3050_घातer_up(mpu3050);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(map, MPU3050_CHIP_ID_REG, &val);
	अगर (ret) अणु
		dev_err(dev, "could not read device ID\n");
		ret = -ENODEV;

		जाओ err_घातer_करोwn;
	पूर्ण

	अगर ((val & MPU3050_CHIP_ID_MASK) != MPU3050_CHIP_ID) अणु
		dev_err(dev, "unsupported chip id %02x\n",
				(u8)(val & MPU3050_CHIP_ID_MASK));
		ret = -ENODEV;
		जाओ err_घातer_करोwn;
	पूर्ण

	ret = regmap_पढ़ो(map, MPU3050_PRODUCT_ID_REG, &val);
	अगर (ret) अणु
		dev_err(dev, "could not read device ID\n");
		ret = -ENODEV;

		जाओ err_घातer_करोwn;
	पूर्ण
	dev_info(dev, "found MPU-3050 part no: %d, version: %d\n",
		 ((val >> 4) & 0xf), (val & 0xf));

	ret = mpu3050_hw_init(mpu3050);
	अगर (ret)
		जाओ err_घातer_करोwn;

	indio_dev->channels = mpu3050_channels;
	indio_dev->num_channels = ARRAY_SIZE(mpu3050_channels);
	indio_dev->info = &mpu3050_info;
	indio_dev->available_scan_masks = mpu3050_scan_masks;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->name = name;

	ret = iio_triggered_buffer_setup(indio_dev, iio_pollfunc_store_समय,
					 mpu3050_trigger_handler,
					 &mpu3050_buffer_setup_ops);
	अगर (ret) अणु
		dev_err(dev, "triggered buffer setup failed\n");
		जाओ err_घातer_करोwn;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "device register failed\n");
		जाओ err_cleanup_buffer;
	पूर्ण

	dev_set_drvdata(dev, indio_dev);

	/* Check अगर we have an asचिन्हित IRQ to use as trigger */
	अगर (irq) अणु
		ret = mpu3050_trigger_probe(indio_dev, irq);
		अगर (ret)
			dev_err(dev, "failed to register trigger\n");
	पूर्ण

	/* Enable runसमय PM */
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	/*
	 * Set स्वतःsuspend to two orders of magnitude larger than the
	 * start-up समय. 100ms start-up समय means 10000ms स्वतःsuspend,
	 * i.e. 10 seconds.
	 */
	pm_runसमय_set_स्वतःsuspend_delay(dev, 10000);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_put(dev);

	वापस 0;

err_cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
err_घातer_करोwn:
	mpu3050_घातer_करोwn(mpu3050);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mpu3050_common_probe);

पूर्णांक mpu3050_common_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा mpu3050 *mpu3050 = iio_priv(indio_dev);

	pm_runसमय_get_sync(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	iio_triggered_buffer_cleanup(indio_dev);
	अगर (mpu3050->irq)
		मुक्त_irq(mpu3050->irq, mpu3050);
	iio_device_unरेजिस्टर(indio_dev);
	mpu3050_घातer_करोwn(mpu3050);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mpu3050_common_हटाओ);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mpu3050_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस mpu3050_घातer_करोwn(iio_priv(dev_get_drvdata(dev)));
पूर्ण

अटल पूर्णांक mpu3050_runसमय_resume(काष्ठा device *dev)
अणु
	वापस mpu3050_घातer_up(iio_priv(dev_get_drvdata(dev)));
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

स्थिर काष्ठा dev_pm_ops mpu3050_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(mpu3050_runसमय_suspend,
			   mpu3050_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL(mpu3050_dev_pm_ops);

MODULE_AUTHOR("Linus Walleij");
MODULE_DESCRIPTION("MPU3050 gyroscope driver");
MODULE_LICENSE("GPL");
