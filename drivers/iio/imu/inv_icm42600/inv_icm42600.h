<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2020 Invensense, Inc.
 */

#अगर_अघोषित INV_ICM42600_H_
#घोषणा INV_ICM42600_H_

#समावेश <linux/bits.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm.h>
#समावेश <linux/iio/iपन.स>

#समावेश "inv_icm42600_buffer.h"

क्रमागत inv_icm42600_chip अणु
	INV_CHIP_ICM42600,
	INV_CHIP_ICM42602,
	INV_CHIP_ICM42605,
	INV_CHIP_ICM42622,
	INV_CHIP_NB,
पूर्ण;

/* serial bus slew rates */
क्रमागत inv_icm42600_slew_rate अणु
	INV_ICM42600_SLEW_RATE_20_60NS,
	INV_ICM42600_SLEW_RATE_12_36NS,
	INV_ICM42600_SLEW_RATE_6_18NS,
	INV_ICM42600_SLEW_RATE_4_12NS,
	INV_ICM42600_SLEW_RATE_2_6NS,
	INV_ICM42600_SLEW_RATE_INF_2NS,
पूर्ण;

क्रमागत inv_icm42600_sensor_mode अणु
	INV_ICM42600_SENSOR_MODE_OFF,
	INV_ICM42600_SENSOR_MODE_STANDBY,
	INV_ICM42600_SENSOR_MODE_LOW_POWER,
	INV_ICM42600_SENSOR_MODE_LOW_NOISE,
	INV_ICM42600_SENSOR_MODE_NB,
पूर्ण;

/* gyroscope fullscale values */
क्रमागत inv_icm42600_gyro_fs अणु
	INV_ICM42600_GYRO_FS_2000DPS,
	INV_ICM42600_GYRO_FS_1000DPS,
	INV_ICM42600_GYRO_FS_500DPS,
	INV_ICM42600_GYRO_FS_250DPS,
	INV_ICM42600_GYRO_FS_125DPS,
	INV_ICM42600_GYRO_FS_62_5DPS,
	INV_ICM42600_GYRO_FS_31_25DPS,
	INV_ICM42600_GYRO_FS_15_625DPS,
	INV_ICM42600_GYRO_FS_NB,
पूर्ण;

/* accelerometer fullscale values */
क्रमागत inv_icm42600_accel_fs अणु
	INV_ICM42600_ACCEL_FS_16G,
	INV_ICM42600_ACCEL_FS_8G,
	INV_ICM42600_ACCEL_FS_4G,
	INV_ICM42600_ACCEL_FS_2G,
	INV_ICM42600_ACCEL_FS_NB,
पूर्ण;

/* ODR suffixed by LN or LP are Low-Noise or Low-Power mode only */
क्रमागत inv_icm42600_odr अणु
	INV_ICM42600_ODR_8KHZ_LN = 3,
	INV_ICM42600_ODR_4KHZ_LN,
	INV_ICM42600_ODR_2KHZ_LN,
	INV_ICM42600_ODR_1KHZ_LN,
	INV_ICM42600_ODR_200HZ,
	INV_ICM42600_ODR_100HZ,
	INV_ICM42600_ODR_50HZ,
	INV_ICM42600_ODR_25HZ,
	INV_ICM42600_ODR_12_5HZ,
	INV_ICM42600_ODR_6_25HZ_LP,
	INV_ICM42600_ODR_3_125HZ_LP,
	INV_ICM42600_ODR_1_5625HZ_LP,
	INV_ICM42600_ODR_500HZ,
	INV_ICM42600_ODR_NB,
पूर्ण;

क्रमागत inv_icm42600_filter अणु
	/* Low-Noise mode sensor data filter (3rd order filter by शेष) */
	INV_ICM42600_FILTER_BW_ODR_DIV_2,

	/* Low-Power mode sensor data filter (averaging) */
	INV_ICM42600_FILTER_AVG_1X = 1,
	INV_ICM42600_FILTER_AVG_16X = 6,
पूर्ण;

काष्ठा inv_icm42600_sensor_conf अणु
	पूर्णांक mode;
	पूर्णांक fs;
	पूर्णांक odr;
	पूर्णांक filter;
पूर्ण;
#घोषणा INV_ICM42600_SENSOR_CONF_INIT		अणु-1, -1, -1, -1पूर्ण

काष्ठा inv_icm42600_conf अणु
	काष्ठा inv_icm42600_sensor_conf gyro;
	काष्ठा inv_icm42600_sensor_conf accel;
	bool temp_en;
पूर्ण;

काष्ठा inv_icm42600_suspended अणु
	क्रमागत inv_icm42600_sensor_mode gyro;
	क्रमागत inv_icm42600_sensor_mode accel;
	bool temp;
पूर्ण;

/**
 *  काष्ठा inv_icm42600_state - driver state variables
 *  @lock:		lock क्रम serializing multiple रेजिस्टरs access.
 *  @chip:		chip identअगरier.
 *  @name:		chip name.
 *  @map:		regmap poपूर्णांकer.
 *  @vdd_supply:	VDD voltage regulator क्रम the chip.
 *  @vddio_supply:	I/O voltage regulator क्रम the chip.
 *  @orientation:	sensor chip orientation relative to मुख्य hardware.
 *  @conf:		chip sensors configurations.
 *  @suspended:		suspended sensors configuration.
 *  @indio_gyro:	gyroscope IIO device.
 *  @indio_accel:	accelerometer IIO device.
 *  @buffer:		data transfer buffer aligned क्रम DMA.
 *  @fअगरo:		FIFO management काष्ठाure.
 *  @बारtamp:		पूर्णांकerrupt बारtamps.
 */
काष्ठा inv_icm42600_state अणु
	काष्ठा mutex lock;
	क्रमागत inv_icm42600_chip chip;
	स्थिर अक्षर *name;
	काष्ठा regmap *map;
	काष्ठा regulator *vdd_supply;
	काष्ठा regulator *vddio_supply;
	काष्ठा iio_mount_matrix orientation;
	काष्ठा inv_icm42600_conf conf;
	काष्ठा inv_icm42600_suspended suspended;
	काष्ठा iio_dev *indio_gyro;
	काष्ठा iio_dev *indio_accel;
	uपूर्णांक8_t buffer[2] ____cacheline_aligned;
	काष्ठा inv_icm42600_fअगरo fअगरo;
	काष्ठा अणु
		पूर्णांक64_t gyro;
		पूर्णांक64_t accel;
	पूर्ण बारtamp;
पूर्ण;

/* Virtual रेजिस्टर addresses: @bank on MSB (4 upper bits), @address on LSB */

/* Bank selection रेजिस्टर, available in all banks */
#घोषणा INV_ICM42600_REG_BANK_SEL			0x76
#घोषणा INV_ICM42600_BANK_SEL_MASK			GENMASK(2, 0)

/* User bank 0 (MSB 0x00) */
#घोषणा INV_ICM42600_REG_DEVICE_CONFIG			0x0011
#घोषणा INV_ICM42600_DEVICE_CONFIG_SOFT_RESET		BIT(0)

#घोषणा INV_ICM42600_REG_DRIVE_CONFIG			0x0013
#घोषणा INV_ICM42600_DRIVE_CONFIG_I2C_MASK		GENMASK(5, 3)
#घोषणा INV_ICM42600_DRIVE_CONFIG_I2C(_rate)		\
		FIELD_PREP(INV_ICM42600_DRIVE_CONFIG_I2C_MASK, (_rate))
#घोषणा INV_ICM42600_DRIVE_CONFIG_SPI_MASK		GENMASK(2, 0)
#घोषणा INV_ICM42600_DRIVE_CONFIG_SPI(_rate)		\
		FIELD_PREP(INV_ICM42600_DRIVE_CONFIG_SPI_MASK, (_rate))

#घोषणा INV_ICM42600_REG_INT_CONFIG			0x0014
#घोषणा INV_ICM42600_INT_CONFIG_INT2_LATCHED		BIT(5)
#घोषणा INV_ICM42600_INT_CONFIG_INT2_PUSH_PULL		BIT(4)
#घोषणा INV_ICM42600_INT_CONFIG_INT2_ACTIVE_HIGH	BIT(3)
#घोषणा INV_ICM42600_INT_CONFIG_INT2_ACTIVE_LOW		0x00
#घोषणा INV_ICM42600_INT_CONFIG_INT1_LATCHED		BIT(2)
#घोषणा INV_ICM42600_INT_CONFIG_INT1_PUSH_PULL		BIT(1)
#घोषणा INV_ICM42600_INT_CONFIG_INT1_ACTIVE_HIGH	BIT(0)
#घोषणा INV_ICM42600_INT_CONFIG_INT1_ACTIVE_LOW		0x00

#घोषणा INV_ICM42600_REG_FIFO_CONFIG			0x0016
#घोषणा INV_ICM42600_FIFO_CONFIG_MASK			GENMASK(7, 6)
#घोषणा INV_ICM42600_FIFO_CONFIG_BYPASS			\
		FIELD_PREP(INV_ICM42600_FIFO_CONFIG_MASK, 0)
#घोषणा INV_ICM42600_FIFO_CONFIG_STREAM			\
		FIELD_PREP(INV_ICM42600_FIFO_CONFIG_MASK, 1)
#घोषणा INV_ICM42600_FIFO_CONFIG_STOP_ON_FULL		\
		FIELD_PREP(INV_ICM42600_FIFO_CONFIG_MASK, 2)

/* all sensor data are 16 bits (2 रेजिस्टरs wide) in big-endian */
#घोषणा INV_ICM42600_REG_TEMP_DATA			0x001D
#घोषणा INV_ICM42600_REG_ACCEL_DATA_X			0x001F
#घोषणा INV_ICM42600_REG_ACCEL_DATA_Y			0x0021
#घोषणा INV_ICM42600_REG_ACCEL_DATA_Z			0x0023
#घोषणा INV_ICM42600_REG_GYRO_DATA_X			0x0025
#घोषणा INV_ICM42600_REG_GYRO_DATA_Y			0x0027
#घोषणा INV_ICM42600_REG_GYRO_DATA_Z			0x0029
#घोषणा INV_ICM42600_DATA_INVALID			-32768

#घोषणा INV_ICM42600_REG_INT_STATUS			0x002D
#घोषणा INV_ICM42600_INT_STATUS_UI_FSYNC		BIT(6)
#घोषणा INV_ICM42600_INT_STATUS_PLL_RDY			BIT(5)
#घोषणा INV_ICM42600_INT_STATUS_RESET_DONE		BIT(4)
#घोषणा INV_ICM42600_INT_STATUS_DATA_RDY		BIT(3)
#घोषणा INV_ICM42600_INT_STATUS_FIFO_THS		BIT(2)
#घोषणा INV_ICM42600_INT_STATUS_FIFO_FULL		BIT(1)
#घोषणा INV_ICM42600_INT_STATUS_AGC_RDY			BIT(0)

/*
 * FIFO access रेजिस्टरs
 * FIFO count is 16 bits (2 रेजिस्टरs) big-endian
 * FIFO data is a continuous पढ़ो रेजिस्टर to पढ़ो FIFO content
 */
#घोषणा INV_ICM42600_REG_FIFO_COUNT			0x002E
#घोषणा INV_ICM42600_REG_FIFO_DATA			0x0030

#घोषणा INV_ICM42600_REG_SIGNAL_PATH_RESET		0x004B
#घोषणा INV_ICM42600_SIGNAL_PATH_RESET_DMP_INIT_EN	BIT(6)
#घोषणा INV_ICM42600_SIGNAL_PATH_RESET_DMP_MEM_RESET	BIT(5)
#घोषणा INV_ICM42600_SIGNAL_PATH_RESET_RESET		BIT(3)
#घोषणा INV_ICM42600_SIGNAL_PATH_RESET_TMST_STROBE	BIT(2)
#घोषणा INV_ICM42600_SIGNAL_PATH_RESET_FIFO_FLUSH	BIT(1)

/* शेष configuration: all data big-endian and fअगरo count in bytes */
#घोषणा INV_ICM42600_REG_INTF_CONFIG0			0x004C
#घोषणा INV_ICM42600_INTF_CONFIG0_FIFO_HOLD_LAST_DATA	BIT(7)
#घोषणा INV_ICM42600_INTF_CONFIG0_FIFO_COUNT_REC	BIT(6)
#घोषणा INV_ICM42600_INTF_CONFIG0_FIFO_COUNT_ENDIAN	BIT(5)
#घोषणा INV_ICM42600_INTF_CONFIG0_SENSOR_DATA_ENDIAN	BIT(4)
#घोषणा INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_MASK	GENMASK(1, 0)
#घोषणा INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_SPI_DIS	\
		FIELD_PREP(INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_MASK, 2)
#घोषणा INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_I2C_DIS	\
		FIELD_PREP(INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_MASK, 3)

#घोषणा INV_ICM42600_REG_INTF_CONFIG1			0x004D
#घोषणा INV_ICM42600_INTF_CONFIG1_ACCEL_LP_CLK_RC	BIT(3)

#घोषणा INV_ICM42600_REG_PWR_MGMT0			0x004E
#घोषणा INV_ICM42600_PWR_MGMT0_TEMP_DIS			BIT(5)
#घोषणा INV_ICM42600_PWR_MGMT0_IDLE			BIT(4)
#घोषणा INV_ICM42600_PWR_MGMT0_GYRO(_mode)		\
		FIELD_PREP(GENMASK(3, 2), (_mode))
#घोषणा INV_ICM42600_PWR_MGMT0_ACCEL(_mode)		\
		FIELD_PREP(GENMASK(1, 0), (_mode))

#घोषणा INV_ICM42600_REG_GYRO_CONFIG0			0x004F
#घोषणा INV_ICM42600_GYRO_CONFIG0_FS(_fs)		\
		FIELD_PREP(GENMASK(7, 5), (_fs))
#घोषणा INV_ICM42600_GYRO_CONFIG0_ODR(_odr)		\
		FIELD_PREP(GENMASK(3, 0), (_odr))

#घोषणा INV_ICM42600_REG_ACCEL_CONFIG0			0x0050
#घोषणा INV_ICM42600_ACCEL_CONFIG0_FS(_fs)		\
		FIELD_PREP(GENMASK(7, 5), (_fs))
#घोषणा INV_ICM42600_ACCEL_CONFIG0_ODR(_odr)		\
		FIELD_PREP(GENMASK(3, 0), (_odr))

#घोषणा INV_ICM42600_REG_GYRO_ACCEL_CONFIG0		0x0052
#घोषणा INV_ICM42600_GYRO_ACCEL_CONFIG0_ACCEL_FILT(_f)	\
		FIELD_PREP(GENMASK(7, 4), (_f))
#घोषणा INV_ICM42600_GYRO_ACCEL_CONFIG0_GYRO_FILT(_f)	\
		FIELD_PREP(GENMASK(3, 0), (_f))

#घोषणा INV_ICM42600_REG_TMST_CONFIG			0x0054
#घोषणा INV_ICM42600_TMST_CONFIG_MASK			GENMASK(4, 0)
#घोषणा INV_ICM42600_TMST_CONFIG_TMST_TO_REGS_EN	BIT(4)
#घोषणा INV_ICM42600_TMST_CONFIG_TMST_RES_16US		BIT(3)
#घोषणा INV_ICM42600_TMST_CONFIG_TMST_DELTA_EN		BIT(2)
#घोषणा INV_ICM42600_TMST_CONFIG_TMST_FSYNC_EN		BIT(1)
#घोषणा INV_ICM42600_TMST_CONFIG_TMST_EN		BIT(0)

#घोषणा INV_ICM42600_REG_FIFO_CONFIG1			0x005F
#घोषणा INV_ICM42600_FIFO_CONFIG1_RESUME_PARTIAL_RD	BIT(6)
#घोषणा INV_ICM42600_FIFO_CONFIG1_WM_GT_TH		BIT(5)
#घोषणा INV_ICM42600_FIFO_CONFIG1_TMST_FSYNC_EN		BIT(3)
#घोषणा INV_ICM42600_FIFO_CONFIG1_TEMP_EN		BIT(2)
#घोषणा INV_ICM42600_FIFO_CONFIG1_GYRO_EN		BIT(1)
#घोषणा INV_ICM42600_FIFO_CONFIG1_ACCEL_EN		BIT(0)

/* FIFO watermark is 16 bits (2 रेजिस्टरs wide) in little-endian */
#घोषणा INV_ICM42600_REG_FIFO_WATERMARK			0x0060
#घोषणा INV_ICM42600_FIFO_WATERMARK_VAL(_wm)		\
		cpu_to_le16((_wm) & GENMASK(11, 0))
/* FIFO is 2048 bytes, let 12 samples क्रम पढ़ोing latency */
#घोषणा INV_ICM42600_FIFO_WATERMARK_MAX			(2048 - 12 * 16)

#घोषणा INV_ICM42600_REG_INT_CONFIG1			0x0064
#घोषणा INV_ICM42600_INT_CONFIG1_TPULSE_DURATION	BIT(6)
#घोषणा INV_ICM42600_INT_CONFIG1_TDEASSERT_DISABLE	BIT(5)
#घोषणा INV_ICM42600_INT_CONFIG1_ASYNC_RESET		BIT(4)

#घोषणा INV_ICM42600_REG_INT_SOURCE0			0x0065
#घोषणा INV_ICM42600_INT_SOURCE0_UI_FSYNC_INT1_EN	BIT(6)
#घोषणा INV_ICM42600_INT_SOURCE0_PLL_RDY_INT1_EN	BIT(5)
#घोषणा INV_ICM42600_INT_SOURCE0_RESET_DONE_INT1_EN	BIT(4)
#घोषणा INV_ICM42600_INT_SOURCE0_UI_DRDY_INT1_EN	BIT(3)
#घोषणा INV_ICM42600_INT_SOURCE0_FIFO_THS_INT1_EN	BIT(2)
#घोषणा INV_ICM42600_INT_SOURCE0_FIFO_FULL_INT1_EN	BIT(1)
#घोषणा INV_ICM42600_INT_SOURCE0_UI_AGC_RDY_INT1_EN	BIT(0)

#घोषणा INV_ICM42600_REG_WHOAMI				0x0075
#घोषणा INV_ICM42600_WHOAMI_ICM42600			0x40
#घोषणा INV_ICM42600_WHOAMI_ICM42602			0x41
#घोषणा INV_ICM42600_WHOAMI_ICM42605			0x42
#घोषणा INV_ICM42600_WHOAMI_ICM42622			0x46

/* User bank 1 (MSB 0x10) */
#घोषणा INV_ICM42600_REG_SENSOR_CONFIG0			0x1003
#घोषणा INV_ICM42600_SENSOR_CONFIG0_ZG_DISABLE		BIT(5)
#घोषणा INV_ICM42600_SENSOR_CONFIG0_YG_DISABLE		BIT(4)
#घोषणा INV_ICM42600_SENSOR_CONFIG0_XG_DISABLE		BIT(3)
#घोषणा INV_ICM42600_SENSOR_CONFIG0_ZA_DISABLE		BIT(2)
#घोषणा INV_ICM42600_SENSOR_CONFIG0_YA_DISABLE		BIT(1)
#घोषणा INV_ICM42600_SENSOR_CONFIG0_XA_DISABLE		BIT(0)

/* Timestamp value is 20 bits (3 रेजिस्टरs) in little-endian */
#घोषणा INV_ICM42600_REG_TMSTVAL			0x1062
#घोषणा INV_ICM42600_TMSTVAL_MASK			GENMASK(19, 0)

#घोषणा INV_ICM42600_REG_INTF_CONFIG4			0x107A
#घोषणा INV_ICM42600_INTF_CONFIG4_I3C_BUS_ONLY		BIT(6)
#घोषणा INV_ICM42600_INTF_CONFIG4_SPI_AP_4WIRE		BIT(1)

#घोषणा INV_ICM42600_REG_INTF_CONFIG6			0x107C
#घोषणा INV_ICM42600_INTF_CONFIG6_MASK			GENMASK(4, 0)
#घोषणा INV_ICM42600_INTF_CONFIG6_I3C_EN		BIT(4)
#घोषणा INV_ICM42600_INTF_CONFIG6_I3C_IBI_BYTE_EN	BIT(3)
#घोषणा INV_ICM42600_INTF_CONFIG6_I3C_IBI_EN		BIT(2)
#घोषणा INV_ICM42600_INTF_CONFIG6_I3C_DDR_EN		BIT(1)
#घोषणा INV_ICM42600_INTF_CONFIG6_I3C_SDR_EN		BIT(0)

/* User bank 4 (MSB 0x40) */
#घोषणा INV_ICM42600_REG_INT_SOURCE8			0x404F
#घोषणा INV_ICM42600_INT_SOURCE8_FSYNC_IBI_EN		BIT(5)
#घोषणा INV_ICM42600_INT_SOURCE8_PLL_RDY_IBI_EN		BIT(4)
#घोषणा INV_ICM42600_INT_SOURCE8_UI_DRDY_IBI_EN		BIT(3)
#घोषणा INV_ICM42600_INT_SOURCE8_FIFO_THS_IBI_EN	BIT(2)
#घोषणा INV_ICM42600_INT_SOURCE8_FIFO_FULL_IBI_EN	BIT(1)
#घोषणा INV_ICM42600_INT_SOURCE8_AGC_RDY_IBI_EN		BIT(0)

#घोषणा INV_ICM42600_REG_OFFSET_USER0			0x4077
#घोषणा INV_ICM42600_REG_OFFSET_USER1			0x4078
#घोषणा INV_ICM42600_REG_OFFSET_USER2			0x4079
#घोषणा INV_ICM42600_REG_OFFSET_USER3			0x407A
#घोषणा INV_ICM42600_REG_OFFSET_USER4			0x407B
#घोषणा INV_ICM42600_REG_OFFSET_USER5			0x407C
#घोषणा INV_ICM42600_REG_OFFSET_USER6			0x407D
#घोषणा INV_ICM42600_REG_OFFSET_USER7			0x407E
#घोषणा INV_ICM42600_REG_OFFSET_USER8			0x407F

/* Sleep बार required by the driver */
#घोषणा INV_ICM42600_POWER_UP_TIME_MS		100
#घोषणा INV_ICM42600_RESET_TIME_MS		1
#घोषणा INV_ICM42600_ACCEL_STARTUP_TIME_MS	20
#घोषणा INV_ICM42600_GYRO_STARTUP_TIME_MS	60
#घोषणा INV_ICM42600_GYRO_STOP_TIME_MS		150
#घोषणा INV_ICM42600_TEMP_STARTUP_TIME_MS	14
#घोषणा INV_ICM42600_SUSPEND_DELAY_MS		2000

प्रकार पूर्णांक (*inv_icm42600_bus_setup)(काष्ठा inv_icm42600_state *);

बाह्य स्थिर काष्ठा regmap_config inv_icm42600_regmap_config;
बाह्य स्थिर काष्ठा dev_pm_ops inv_icm42600_pm_ops;

स्थिर काष्ठा iio_mount_matrix *
inv_icm42600_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan);

uपूर्णांक32_t inv_icm42600_odr_to_period(क्रमागत inv_icm42600_odr odr);

पूर्णांक inv_icm42600_set_accel_conf(काष्ठा inv_icm42600_state *st,
				काष्ठा inv_icm42600_sensor_conf *conf,
				अचिन्हित पूर्णांक *sleep_ms);

पूर्णांक inv_icm42600_set_gyro_conf(काष्ठा inv_icm42600_state *st,
			       काष्ठा inv_icm42600_sensor_conf *conf,
			       अचिन्हित पूर्णांक *sleep_ms);

पूर्णांक inv_icm42600_set_temp_conf(काष्ठा inv_icm42600_state *st, bool enable,
			       अचिन्हित पूर्णांक *sleep_ms);

पूर्णांक inv_icm42600_debugfs_reg(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक ग_लिखोval, अचिन्हित पूर्णांक *पढ़ोval);

पूर्णांक inv_icm42600_core_probe(काष्ठा regmap *regmap, पूर्णांक chip, पूर्णांक irq,
			    inv_icm42600_bus_setup bus_setup);

काष्ठा iio_dev *inv_icm42600_gyro_init(काष्ठा inv_icm42600_state *st);

पूर्णांक inv_icm42600_gyro_parse_fअगरo(काष्ठा iio_dev *indio_dev);

काष्ठा iio_dev *inv_icm42600_accel_init(काष्ठा inv_icm42600_state *st);

पूर्णांक inv_icm42600_accel_parse_fअगरo(काष्ठा iio_dev *indio_dev);

#पूर्ण_अगर
