<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/iio/iपन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/i2c.h>

/**
 * क्रमागत mpu3050_fullscale - indicates the full range of the sensor in deg/sec
 */
क्रमागत mpu3050_fullscale अणु
	FS_250_DPS = 0,
	FS_500_DPS,
	FS_1000_DPS,
	FS_2000_DPS,
पूर्ण;

/**
 * क्रमागत mpu3050_lpf - indicates the low pass filter width
 */
क्रमागत mpu3050_lpf अणु
	/* This implicity sets sample frequency to 8 kHz */
	LPF_256_HZ_NOLPF = 0,
	/* All others sets the sample frequency to 1 kHz */
	LPF_188_HZ,
	LPF_98_HZ,
	LPF_42_HZ,
	LPF_20_HZ,
	LPF_10_HZ,
	LPF_5_HZ,
	LPF_2100_HZ_NOLPF,
पूर्ण;

क्रमागत mpu3050_axis अणु
	AXIS_X = 0,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX,
पूर्ण;

/**
 * काष्ठा mpu3050 - instance state container क्रम the device
 * @dev: parent device क्रम this instance
 * @orientation: mounting matrix, flipped axis etc
 * @map: regmap to reach the रेजिस्टरs
 * @lock: serialization lock to marshal all requests
 * @irq: the IRQ used क्रम this device
 * @regs: the regulators to घातer this device
 * @fullscale: the current fullscale setting क्रम the device
 * @lpf: digital low pass filter setting क्रम the device
 * @भागisor: base frequency भागider: भागides 8 or 1 kHz
 * @calibration: the three चिन्हित 16-bit calibration settings that
 * get written पूर्णांकo the offset रेजिस्टरs क्रम each axis to compensate
 * क्रम DC offsets
 * @trig: trigger क्रम the MPU-3050 पूर्णांकerrupt, अगर present
 * @hw_irq_trigger: hardware पूर्णांकerrupt trigger is in use
 * @irq_actl: पूर्णांकerrupt is active low
 * @irq_latch: latched IRQ, this means that it is a level IRQ
 * @irq_खोलोdrain: the पूर्णांकerrupt line shall be configured खोलो drain
 * @pending_fअगरo_footer: tells us अगर there is a pending footer in the FIFO
 * that we have to पढ़ो out first when handling the FIFO
 * @hw_बारtamp: latest hardware बारtamp from the trigger IRQ, when in
 * use
 * @i2cmux: an I2C mux reflecting the fact that this sensor is a hub with
 * a pass-through I2C पूर्णांकerface coming out of it: this device needs to be
 * घातered up in order to reach devices on the other side of this mux
 */
काष्ठा mpu3050 अणु
	काष्ठा device *dev;
	काष्ठा iio_mount_matrix orientation;
	काष्ठा regmap *map;
	काष्ठा mutex lock;
	पूर्णांक irq;
	काष्ठा regulator_bulk_data regs[2];
	क्रमागत mpu3050_fullscale fullscale;
	क्रमागत mpu3050_lpf lpf;
	u8 भागisor;
	s16 calibration[3];
	काष्ठा iio_trigger *trig;
	bool hw_irq_trigger;
	bool irq_actl;
	bool irq_latch;
	bool irq_खोलोdrain;
	bool pending_fअगरo_footer;
	s64 hw_बारtamp;
	काष्ठा i2c_mux_core *i2cmux;
पूर्ण;

/* Probe called from dअगरferent transports */
पूर्णांक mpu3050_common_probe(काष्ठा device *dev,
			 काष्ठा regmap *map,
			 पूर्णांक irq,
			 स्थिर अक्षर *name);
पूर्णांक mpu3050_common_हटाओ(काष्ठा device *dev);

/* PM ops */
बाह्य स्थिर काष्ठा dev_pm_ops mpu3050_dev_pm_ops;
