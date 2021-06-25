<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
* Copyright (C) 2012 Invensense, Inc.
*/

#अगर_अघोषित INV_MPU_IIO_H_
#घोषणा INV_MPU_IIO_H_

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/mutex.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/platक्रमm_data/invensense_mpu6050.h>

/**
 *  काष्ठा inv_mpu6050_reg_map - Notable रेजिस्टरs.
 *  @sample_rate_भाग:	Divider applied to gyro output rate.
 *  @lpf:		Configures पूर्णांकernal low pass filter.
 *  @accel_lpf:		Configures accelerometer low pass filter.
 *  @user_ctrl:		Enables/resets the FIFO.
 *  @fअगरo_en:		Determines which data will appear in FIFO.
 *  @gyro_config:	gyro config रेजिस्टर.
 *  @accl_config:	accel config रेजिस्टर
 *  @fअगरo_count_h:	Upper byte of FIFO count.
 *  @fअगरo_r_w:		FIFO रेजिस्टर.
 *  @raw_gyro:		Address of first gyro रेजिस्टर.
 *  @raw_accl:		Address of first accel रेजिस्टर.
 *  @temperature:	temperature रेजिस्टर
 *  @पूर्णांक_enable:	Interrupt enable रेजिस्टर.
 *  @पूर्णांक_status:	Interrupt status रेजिस्टर.
 *  @pwr_mgmt_1:	Controls chip's घातer state and घड़ी source.
 *  @pwr_mgmt_2:	Controls घातer state of inभागidual sensors.
 *  @पूर्णांक_pin_cfg;	Controls पूर्णांकerrupt pin configuration.
 *  @accl_offset:	Controls the accelerometer calibration offset.
 *  @gyro_offset:	Controls the gyroscope calibration offset.
 *  @i2c_अगर:		Controls the i2c पूर्णांकerface
 */
काष्ठा inv_mpu6050_reg_map अणु
	u8 sample_rate_भाग;
	u8 lpf;
	u8 accel_lpf;
	u8 user_ctrl;
	u8 fअगरo_en;
	u8 gyro_config;
	u8 accl_config;
	u8 fअगरo_count_h;
	u8 fअगरo_r_w;
	u8 raw_gyro;
	u8 raw_accl;
	u8 temperature;
	u8 पूर्णांक_enable;
	u8 पूर्णांक_status;
	u8 pwr_mgmt_1;
	u8 pwr_mgmt_2;
	u8 पूर्णांक_pin_cfg;
	u8 accl_offset;
	u8 gyro_offset;
	u8 i2c_अगर;
पूर्ण;

/*device क्रमागत */
क्रमागत inv_devices अणु
	INV_MPU6050,
	INV_MPU6500,
	INV_MPU6515,
	INV_MPU6880,
	INV_MPU6000,
	INV_MPU9150,
	INV_MPU9250,
	INV_MPU9255,
	INV_ICM20608,
	INV_ICM20609,
	INV_ICM20689,
	INV_ICM20602,
	INV_ICM20690,
	INV_IAM20680,
	INV_NUM_PARTS
पूर्ण;

/* chip sensors mask: accelerometer, gyroscope, temperature, magnetometer */
#घोषणा INV_MPU6050_SENSOR_ACCL		BIT(0)
#घोषणा INV_MPU6050_SENSOR_GYRO		BIT(1)
#घोषणा INV_MPU6050_SENSOR_TEMP		BIT(2)
#घोषणा INV_MPU6050_SENSOR_MAGN		BIT(3)

/**
 *  काष्ठा inv_mpu6050_chip_config - Cached chip configuration data.
 *  @clk:		selected chip घड़ी
 *  @fsr:		Full scale range.
 *  @lpf:		Digital low pass filter frequency.
 *  @accl_fs:		accel full scale range.
 *  @accl_en:		accel engine enabled
 *  @gyro_en:		gyro engine enabled
 *  @temp_en:		temperature sensor enabled
 *  @magn_en:		magn engine (i2c master) enabled
 *  @accl_fअगरo_enable:	enable accel data output
 *  @gyro_fअगरo_enable:	enable gyro data output
 *  @temp_fअगरo_enable:	enable temp data output
 *  @magn_fअगरo_enable:	enable magn data output
 *  @भागider:		chip sample rate भागider (sample rate भागider - 1)
 */
काष्ठा inv_mpu6050_chip_config अणु
	अचिन्हित पूर्णांक clk:3;
	अचिन्हित पूर्णांक fsr:2;
	अचिन्हित पूर्णांक lpf:3;
	अचिन्हित पूर्णांक accl_fs:2;
	अचिन्हित पूर्णांक accl_en:1;
	अचिन्हित पूर्णांक gyro_en:1;
	अचिन्हित पूर्णांक temp_en:1;
	अचिन्हित पूर्णांक magn_en:1;
	अचिन्हित पूर्णांक accl_fअगरo_enable:1;
	अचिन्हित पूर्णांक gyro_fअगरo_enable:1;
	अचिन्हित पूर्णांक temp_fअगरo_enable:1;
	अचिन्हित पूर्णांक magn_fअगरo_enable:1;
	u8 भागider;
	u8 user_ctrl;
पूर्ण;

/*
 * Maximum of 6 + 6 + 2 + 7 (क्रम MPU9x50) = 21 round up to 24 and plus 8.
 * May be less अगर fewer channels are enabled, as दीर्घ as the बारtamp
 * reमुख्यs 8 byte aligned
 */
#घोषणा INV_MPU6050_OUTPUT_DATA_SIZE         32

/**
 *  काष्ठा inv_mpu6050_hw - Other important hardware inक्रमmation.
 *  @whoami:	Self identअगरication byte from WHO_AM_I रेजिस्टर
 *  @name:      name of the chip.
 *  @reg:   रेजिस्टर map of the chip.
 *  @config:    configuration of the chip.
 *  @fअगरo_size:	size of the FIFO in bytes.
 *  @temp:	offset and scale to apply to raw temperature.
 */
काष्ठा inv_mpu6050_hw अणु
	u8 whoami;
	u8 *name;
	स्थिर काष्ठा inv_mpu6050_reg_map *reg;
	स्थिर काष्ठा inv_mpu6050_chip_config *config;
	माप_प्रकार fअगरo_size;
	काष्ठा अणु
		पूर्णांक offset;
		पूर्णांक scale;
	पूर्ण temp;
पूर्ण;

/*
 *  काष्ठा inv_mpu6050_state - Driver state variables.
 *  @lock:              Chip access lock.
 *  @trig:              IIO trigger.
 *  @chip_config:	Cached attribute inक्रमmation.
 *  @reg:		Map of important रेजिस्टरs.
 *  @hw:		Other hardware-specअगरic inक्रमmation.
 *  @chip_type:		chip type.
 *  @plat_data:		platक्रमm data (deprecated in favor of @orientation).
 *  @orientation:	sensor chip orientation relative to मुख्य hardware.
 *  @map		regmap poपूर्णांकer.
 *  @irq		पूर्णांकerrupt number.
 *  @irq_mask		the पूर्णांक_pin_cfg mask to configure पूर्णांकerrupt type.
 *  @chip_period:	chip पूर्णांकernal period estimation (~1kHz).
 *  @it_बारtamp:	बारtamp from previous पूर्णांकerrupt.
 *  @data_बारtamp:	बारtamp क्रम next data sample.
 *  @vdd_supply:	VDD voltage regulator क्रम the chip.
 *  @vddio_supply	I/O voltage regulator क्रम the chip.
 *  @magn_disabled:     magnetometer disabled क्रम backward compatibility reason.
 *  @magn_raw_to_gauss:	coefficient to convert mag raw value to Gauss.
 *  @magn_orient:       magnetometer sensor chip orientation अगर available.
 *  @suspended_sensors:	sensors mask of sensors turned off क्रम suspend
 *  @data:		dma safe buffer used क्रम bulk पढ़ोs.
 */
काष्ठा inv_mpu6050_state अणु
	काष्ठा mutex lock;
	काष्ठा iio_trigger  *trig;
	काष्ठा inv_mpu6050_chip_config chip_config;
	स्थिर काष्ठा inv_mpu6050_reg_map *reg;
	स्थिर काष्ठा inv_mpu6050_hw *hw;
	क्रमागत   inv_devices chip_type;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा i2c_client *mux_client;
	काष्ठा inv_mpu6050_platक्रमm_data plat_data;
	काष्ठा iio_mount_matrix orientation;
	काष्ठा regmap *map;
	पूर्णांक irq;
	u8 irq_mask;
	अचिन्हित skip_samples;
	s64 chip_period;
	s64 it_बारtamp;
	s64 data_बारtamp;
	काष्ठा regulator *vdd_supply;
	काष्ठा regulator *vddio_supply;
	bool magn_disabled;
	s32 magn_raw_to_gauss[3];
	काष्ठा iio_mount_matrix magn_orient;
	अचिन्हित पूर्णांक suspended_sensors;
	u8 data[INV_MPU6050_OUTPUT_DATA_SIZE] ____cacheline_aligned;
पूर्ण;

/*रेजिस्टर and associated bit definition*/
#घोषणा INV_MPU6050_REG_ACCEL_OFFSET        0x06
#घोषणा INV_MPU6050_REG_GYRO_OFFSET         0x13

#घोषणा INV_MPU6050_REG_SAMPLE_RATE_DIV     0x19
#घोषणा INV_MPU6050_REG_CONFIG              0x1A
#घोषणा INV_MPU6050_REG_GYRO_CONFIG         0x1B
#घोषणा INV_MPU6050_REG_ACCEL_CONFIG        0x1C

#घोषणा INV_MPU6050_REG_FIFO_EN             0x23
#घोषणा INV_MPU6050_BIT_SLAVE_0             0x01
#घोषणा INV_MPU6050_BIT_SLAVE_1             0x02
#घोषणा INV_MPU6050_BIT_SLAVE_2             0x04
#घोषणा INV_MPU6050_BIT_ACCEL_OUT           0x08
#घोषणा INV_MPU6050_BITS_GYRO_OUT           0x70
#घोषणा INV_MPU6050_BIT_TEMP_OUT            0x80

#घोषणा INV_MPU6050_REG_I2C_MST_CTRL        0x24
#घोषणा INV_MPU6050_BITS_I2C_MST_CLK_400KHZ 0x0D
#घोषणा INV_MPU6050_BIT_I2C_MST_P_NSR       0x10
#घोषणा INV_MPU6050_BIT_SLV3_FIFO_EN        0x20
#घोषणा INV_MPU6050_BIT_WAIT_FOR_ES         0x40
#घोषणा INV_MPU6050_BIT_MULT_MST_EN         0x80

/* control I2C slaves from 0 to 3 */
#घोषणा INV_MPU6050_REG_I2C_SLV_ADDR(_x)    (0x25 + 3 * (_x))
#घोषणा INV_MPU6050_BIT_I2C_SLV_RNW         0x80

#घोषणा INV_MPU6050_REG_I2C_SLV_REG(_x)     (0x26 + 3 * (_x))

#घोषणा INV_MPU6050_REG_I2C_SLV_CTRL(_x)    (0x27 + 3 * (_x))
#घोषणा INV_MPU6050_BIT_SLV_GRP             0x10
#घोषणा INV_MPU6050_BIT_SLV_REG_DIS         0x20
#घोषणा INV_MPU6050_BIT_SLV_BYTE_SW         0x40
#घोषणा INV_MPU6050_BIT_SLV_EN              0x80

/* I2C master delay रेजिस्टर */
#घोषणा INV_MPU6050_REG_I2C_SLV4_CTRL       0x34
#घोषणा INV_MPU6050_BITS_I2C_MST_DLY(_x)    ((_x) & 0x1F)

#घोषणा INV_MPU6050_REG_I2C_MST_STATUS      0x36
#घोषणा INV_MPU6050_BIT_I2C_SLV0_NACK       0x01
#घोषणा INV_MPU6050_BIT_I2C_SLV1_NACK       0x02
#घोषणा INV_MPU6050_BIT_I2C_SLV2_NACK       0x04
#घोषणा INV_MPU6050_BIT_I2C_SLV3_NACK       0x08

#घोषणा INV_MPU6050_REG_INT_ENABLE          0x38
#घोषणा INV_MPU6050_BIT_DATA_RDY_EN         0x01
#घोषणा INV_MPU6050_BIT_DMP_INT_EN          0x02

#घोषणा INV_MPU6050_REG_RAW_ACCEL           0x3B
#घोषणा INV_MPU6050_REG_TEMPERATURE         0x41
#घोषणा INV_MPU6050_REG_RAW_GYRO            0x43

#घोषणा INV_MPU6050_REG_INT_STATUS          0x3A
#घोषणा INV_MPU6050_BIT_FIFO_OVERFLOW_INT   0x10
#घोषणा INV_MPU6050_BIT_RAW_DATA_RDY_INT    0x01

#घोषणा INV_MPU6050_REG_EXT_SENS_DATA       0x49

/* I2C slaves data output from 0 to 3 */
#घोषणा INV_MPU6050_REG_I2C_SLV_DO(_x)      (0x63 + (_x))

#घोषणा INV_MPU6050_REG_I2C_MST_DELAY_CTRL  0x67
#घोषणा INV_MPU6050_BIT_I2C_SLV0_DLY_EN     0x01
#घोषणा INV_MPU6050_BIT_I2C_SLV1_DLY_EN     0x02
#घोषणा INV_MPU6050_BIT_I2C_SLV2_DLY_EN     0x04
#घोषणा INV_MPU6050_BIT_I2C_SLV3_DLY_EN     0x08
#घोषणा INV_MPU6050_BIT_DELAY_ES_SHADOW     0x80

#घोषणा INV_MPU6050_REG_SIGNAL_PATH_RESET   0x68
#घोषणा INV_MPU6050_BIT_TEMP_RST            BIT(0)
#घोषणा INV_MPU6050_BIT_ACCEL_RST           BIT(1)
#घोषणा INV_MPU6050_BIT_GYRO_RST            BIT(2)

#घोषणा INV_MPU6050_REG_USER_CTRL           0x6A
#घोषणा INV_MPU6050_BIT_SIG_COND_RST        0x01
#घोषणा INV_MPU6050_BIT_FIFO_RST            0x04
#घोषणा INV_MPU6050_BIT_DMP_RST             0x08
#घोषणा INV_MPU6050_BIT_I2C_MST_EN          0x20
#घोषणा INV_MPU6050_BIT_FIFO_EN             0x40
#घोषणा INV_MPU6050_BIT_DMP_EN              0x80
#घोषणा INV_MPU6050_BIT_I2C_IF_DIS          0x10

#घोषणा INV_MPU6050_REG_PWR_MGMT_1          0x6B
#घोषणा INV_MPU6050_BIT_H_RESET             0x80
#घोषणा INV_MPU6050_BIT_SLEEP               0x40
#घोषणा INV_MPU6050_BIT_TEMP_DIS            0x08
#घोषणा INV_MPU6050_BIT_CLK_MASK            0x7

#घोषणा INV_MPU6050_REG_PWR_MGMT_2          0x6C
#घोषणा INV_MPU6050_BIT_PWR_ACCL_STBY       0x38
#घोषणा INV_MPU6050_BIT_PWR_GYRO_STBY       0x07

/* ICM20602 रेजिस्टर */
#घोषणा INV_ICM20602_REG_I2C_IF             0x70
#घोषणा INV_ICM20602_BIT_I2C_IF_DIS         0x40

#घोषणा INV_MPU6050_REG_FIFO_COUNT_H        0x72
#घोषणा INV_MPU6050_REG_FIFO_R_W            0x74

#घोषणा INV_MPU6050_BYTES_PER_3AXIS_SENSOR   6
#घोषणा INV_MPU6050_FIFO_COUNT_BYTE          2

/* MPU9X50 9-axis magnetometer */
#घोषणा INV_MPU9X50_BYTES_MAGN               7

/* FIFO temperature sample size */
#घोषणा INV_MPU6050_BYTES_PER_TEMP_SENSOR   2

/* mpu6500 रेजिस्टरs */
#घोषणा INV_MPU6500_REG_ACCEL_CONFIG_2      0x1D
#घोषणा INV_ICM20689_BITS_FIFO_SIZE_MAX     0xC0
#घोषणा INV_MPU6500_REG_ACCEL_OFFSET        0x77

/* delay समय in milliseconds */
#घोषणा INV_MPU6050_POWER_UP_TIME            100
#घोषणा INV_MPU6050_TEMP_UP_TIME             100
#घोषणा INV_MPU6050_ACCEL_UP_TIME            20
#घोषणा INV_MPU6050_GYRO_UP_TIME             35
#घोषणा INV_MPU6050_GYRO_DOWN_TIME           150
#घोषणा INV_MPU6050_SUSPEND_DELAY_MS         2000

/* delay समय in microseconds */
#घोषणा INV_MPU6050_REG_UP_TIME_MIN          5000
#घोषणा INV_MPU6050_REG_UP_TIME_MAX          10000

#घोषणा INV_MPU6050_TEMP_OFFSET	             12420
#घोषणा INV_MPU6050_TEMP_SCALE               2941176
#घोषणा INV_MPU6050_MAX_GYRO_FS_PARAM        3
#घोषणा INV_MPU6050_MAX_ACCL_FS_PARAM        3
#घोषणा INV_MPU6050_THREE_AXIS               3
#घोषणा INV_MPU6050_GYRO_CONFIG_FSR_SHIFT    3
#घोषणा INV_ICM20690_GYRO_CONFIG_FSR_SHIFT   2
#घोषणा INV_MPU6050_ACCL_CONFIG_FSR_SHIFT    3

#घोषणा INV_MPU6500_TEMP_OFFSET              7011
#घोषणा INV_MPU6500_TEMP_SCALE               2995178

#घोषणा INV_ICM20608_TEMP_OFFSET	     8170
#घोषणा INV_ICM20608_TEMP_SCALE		     3059976

#घोषणा INV_MPU6050_REG_INT_PIN_CFG	0x37
#घोषणा INV_MPU6050_ACTIVE_HIGH		0x00
#घोषणा INV_MPU6050_ACTIVE_LOW		0x80
/* enable level triggering */
#घोषणा INV_MPU6050_LATCH_INT_EN	0x20
#घोषणा INV_MPU6050_BIT_BYPASS_EN	0x2

/* Allowed बारtamp period jitter in percent */
#घोषणा INV_MPU6050_TS_PERIOD_JITTER	4

/* init parameters */
#घोषणा INV_MPU6050_MAX_FIFO_RATE            1000
#घोषणा INV_MPU6050_MIN_FIFO_RATE            4

/* chip पूर्णांकernal frequency: 1KHz */
#घोषणा INV_MPU6050_INTERNAL_FREQ_HZ		1000
/* वापस the frequency भागider (chip sample rate भागider + 1) */
#घोषणा INV_MPU6050_FREQ_DIVIDER(st)					\
	((st)->chip_config.भागider + 1)
/* chip sample rate भागider to fअगरo rate */
#घोषणा INV_MPU6050_FIFO_RATE_TO_DIVIDER(fअगरo_rate)			\
	((INV_MPU6050_INTERNAL_FREQ_HZ / (fअगरo_rate)) - 1)
#घोषणा INV_MPU6050_DIVIDER_TO_FIFO_RATE(भागider)			\
	(INV_MPU6050_INTERNAL_FREQ_HZ / ((भागider) + 1))

#घोषणा INV_MPU6050_REG_WHOAMI			117

#घोषणा INV_MPU6000_WHOAMI_VALUE		0x68
#घोषणा INV_MPU6050_WHOAMI_VALUE		0x68
#घोषणा INV_MPU6500_WHOAMI_VALUE		0x70
#घोषणा INV_MPU6880_WHOAMI_VALUE		0x78
#घोषणा INV_MPU9150_WHOAMI_VALUE		0x68
#घोषणा INV_MPU9250_WHOAMI_VALUE		0x71
#घोषणा INV_MPU9255_WHOAMI_VALUE		0x73
#घोषणा INV_MPU6515_WHOAMI_VALUE		0x74
#घोषणा INV_ICM20608_WHOAMI_VALUE		0xAF
#घोषणा INV_ICM20609_WHOAMI_VALUE		0xA6
#घोषणा INV_ICM20689_WHOAMI_VALUE		0x98
#घोषणा INV_ICM20602_WHOAMI_VALUE		0x12
#घोषणा INV_ICM20690_WHOAMI_VALUE		0x20
#घोषणा INV_IAM20680_WHOAMI_VALUE		0xA9

/* scan element definition क्रम generic MPU6xxx devices */
क्रमागत inv_mpu6050_scan अणु
	INV_MPU6050_SCAN_ACCL_X,
	INV_MPU6050_SCAN_ACCL_Y,
	INV_MPU6050_SCAN_ACCL_Z,
	INV_MPU6050_SCAN_TEMP,
	INV_MPU6050_SCAN_GYRO_X,
	INV_MPU6050_SCAN_GYRO_Y,
	INV_MPU6050_SCAN_GYRO_Z,
	INV_MPU6050_SCAN_TIMESTAMP,

	INV_MPU9X50_SCAN_MAGN_X = INV_MPU6050_SCAN_GYRO_Z + 1,
	INV_MPU9X50_SCAN_MAGN_Y,
	INV_MPU9X50_SCAN_MAGN_Z,
	INV_MPU9X50_SCAN_TIMESTAMP,
पूर्ण;

क्रमागत inv_mpu6050_filter_e अणु
	INV_MPU6050_FILTER_NOLPF2 = 0,
	INV_MPU6050_FILTER_200HZ,
	INV_MPU6050_FILTER_100HZ,
	INV_MPU6050_FILTER_45HZ,
	INV_MPU6050_FILTER_20HZ,
	INV_MPU6050_FILTER_10HZ,
	INV_MPU6050_FILTER_5HZ,
	INV_MPU6050_FILTER_NOLPF,
	NUM_MPU6050_FILTER
पूर्ण;

/* IIO attribute address */
क्रमागत INV_MPU6050_IIO_ATTR_ADDR अणु
	ATTR_GYRO_MATRIX,
	ATTR_ACCL_MATRIX,
पूर्ण;

क्रमागत inv_mpu6050_accl_fs_e अणु
	INV_MPU6050_FS_02G = 0,
	INV_MPU6050_FS_04G,
	INV_MPU6050_FS_08G,
	INV_MPU6050_FS_16G,
	NUM_ACCL_FSR
पूर्ण;

क्रमागत inv_mpu6050_fsr_e अणु
	INV_MPU6050_FSR_250DPS = 0,
	INV_MPU6050_FSR_500DPS,
	INV_MPU6050_FSR_1000DPS,
	INV_MPU6050_FSR_2000DPS,
	NUM_MPU6050_FSR
पूर्ण;

क्रमागत inv_mpu6050_घड़ी_sel_e अणु
	INV_CLK_INTERNAL = 0,
	INV_CLK_PLL,
	NUM_CLK
पूर्ण;

irqवापस_t inv_mpu6050_पढ़ो_fअगरo(पूर्णांक irq, व्योम *p);
पूर्णांक inv_mpu6050_probe_trigger(काष्ठा iio_dev *indio_dev, पूर्णांक irq_type);
पूर्णांक inv_mpu6050_prepare_fअगरo(काष्ठा inv_mpu6050_state *st, bool enable);
पूर्णांक inv_mpu6050_चयन_engine(काष्ठा inv_mpu6050_state *st, bool en,
			      अचिन्हित पूर्णांक mask);
पूर्णांक inv_mpu6050_ग_लिखो_reg(काष्ठा inv_mpu6050_state *st, पूर्णांक reg, u8 val);
पूर्णांक inv_mpu_acpi_create_mux_client(काष्ठा i2c_client *client);
व्योम inv_mpu_acpi_delete_mux_client(काष्ठा i2c_client *client);
पूर्णांक inv_mpu_core_probe(काष्ठा regmap *regmap, पूर्णांक irq, स्थिर अक्षर *name,
		पूर्णांक (*inv_mpu_bus_setup)(काष्ठा iio_dev *), पूर्णांक chip_type);
बाह्य स्थिर काष्ठा dev_pm_ops inv_mpu_pmops;

#पूर्ण_अगर
