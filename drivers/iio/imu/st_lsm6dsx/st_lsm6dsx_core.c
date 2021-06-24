<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics st_lsm6dsx sensor driver
 *
 * The ST LSM6DSx IMU MEMS series consists of 3D digital accelerometer
 * and 3D digital gyroscope प्रणाली-in-package with a digital I2C/SPI serial
 * पूर्णांकerface standard output.
 * LSM6DSx IMU MEMS series has a dynamic user-selectable full-scale
 * acceleration range of +-2/+-4/+-8/+-16 g and an angular rate range of
 * +-125/+-245/+-500/+-1000/+-2000 dps
 * LSM6DSx series has an पूर्णांकegrated First-In-First-Out (FIFO) buffer
 * allowing dynamic batching of sensor data.
 * LSM9DSx series is similar but includes an additional magnetometer, handled
 * by a dअगरferent driver.
 *
 * Supported sensors:
 * - LSM6DS3:
 *   - Accelerometer/Gyroscope supported ODR [Hz]: 13, 26, 52, 104, 208, 416
 *   - Accelerometer supported full-scale [g]: +-2/+-4/+-8/+-16
 *   - Gyroscope supported full-scale [dps]: +-125/+-245/+-500/+-1000/+-2000
 *   - FIFO size: 8KB
 *
 * - LSM6DS3H/LSM6DSL/LSM6DSM/ISM330DLC/LSM6DS3TR-C:
 *   - Accelerometer/Gyroscope supported ODR [Hz]: 13, 26, 52, 104, 208, 416
 *   - Accelerometer supported full-scale [g]: +-2/+-4/+-8/+-16
 *   - Gyroscope supported full-scale [dps]: +-125/+-245/+-500/+-1000/+-2000
 *   - FIFO size: 4KB
 *
 * - LSM6DSO/LSM6DSOX/ASM330LHH/LSM6DSR/ISM330DHCX/LSM6DST/LSM6DSOP:
 *   - Accelerometer/Gyroscope supported ODR [Hz]: 13, 26, 52, 104, 208, 416,
 *     833
 *   - Accelerometer supported full-scale [g]: +-2/+-4/+-8/+-16
 *   - Gyroscope supported full-scale [dps]: +-125/+-245/+-500/+-1000/+-2000
 *   - FIFO size: 3KB
 *
 * - LSM9DS1/LSM6DS0:
 *   - Accelerometer supported ODR [Hz]: 10, 50, 119, 238, 476, 952
 *   - Accelerometer supported full-scale [g]: +-2/+-4/+-8/+-16
 *   - Gyroscope supported ODR [Hz]: 15, 60, 119, 238, 476, 952
 *   - Gyroscope supported full-scale [dps]: +-245/+-500/+-2000
 *   - FIFO size: 32
 *
 * Copyright 2016 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi@st.com>
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/pm.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitfield.h>

#समावेश <linux/platक्रमm_data/st_sensors_pdata.h>

#समावेश "st_lsm6dsx.h"

#घोषणा ST_LSM6DSX_REG_WHOAMI_ADDR		0x0f

#घोषणा ST_LSM6DSX_TS_SENSITIVITY		25000UL /* 25us */

अटल स्थिर काष्ठा iio_chan_spec st_lsm6dsx_acc_channels[] = अणु
	ST_LSM6DSX_CHANNEL_ACC(IIO_ACCEL, 0x28, IIO_MOD_X, 0),
	ST_LSM6DSX_CHANNEL_ACC(IIO_ACCEL, 0x2a, IIO_MOD_Y, 1),
	ST_LSM6DSX_CHANNEL_ACC(IIO_ACCEL, 0x2c, IIO_MOD_Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec st_lsm6dsx_gyro_channels[] = अणु
	ST_LSM6DSX_CHANNEL(IIO_ANGL_VEL, 0x22, IIO_MOD_X, 0),
	ST_LSM6DSX_CHANNEL(IIO_ANGL_VEL, 0x24, IIO_MOD_Y, 1),
	ST_LSM6DSX_CHANNEL(IIO_ANGL_VEL, 0x26, IIO_MOD_Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec st_lsm6ds0_gyro_channels[] = अणु
	ST_LSM6DSX_CHANNEL(IIO_ANGL_VEL, 0x18, IIO_MOD_X, 0),
	ST_LSM6DSX_CHANNEL(IIO_ANGL_VEL, 0x1a, IIO_MOD_Y, 1),
	ST_LSM6DSX_CHANNEL(IIO_ANGL_VEL, 0x1c, IIO_MOD_Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा st_lsm6dsx_settings st_lsm6dsx_sensor_settings[] = अणु
	अणु
		.reset = अणु
			.addr = 0x22,
			.mask = BIT(0),
		पूर्ण,
		.boot = अणु
			.addr = 0x22,
			.mask = BIT(7),
		पूर्ण,
		.bdu = अणु
			.addr = 0x22,
			.mask = BIT(6),
		पूर्ण,
		.max_fअगरo_size = 32,
		.id = अणु
			अणु
				.hw_id = ST_LSM9DS1_ID,
				.name = ST_LSM9DS1_DEV_NAME,
				.wai = 0x68,
			पूर्ण, अणु
				.hw_id = ST_LSM6DS0_ID,
				.name = ST_LSM6DS0_DEV_NAME,
				.wai = 0x68,
			पूर्ण,
		पूर्ण,
		.channels = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.chan = st_lsm6dsx_acc_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_acc_channels),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.chan = st_lsm6ds0_gyro_channels,
				.len = ARRAY_SIZE(st_lsm6ds0_gyro_channels),
			पूर्ण,
		पूर्ण,
		.odr_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x20,
					.mask = GENMASK(7, 5),
				पूर्ण,
				.odr_avl[0] = अणु  10000, 0x01 पूर्ण,
				.odr_avl[1] = अणु  50000, 0x02 पूर्ण,
				.odr_avl[2] = अणु 119000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 238000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 476000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 952000, 0x06 पूर्ण,
				.odr_len = 6,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(7, 5),
				पूर्ण,
				.odr_avl[0] = अणु  14900, 0x01 पूर्ण,
				.odr_avl[1] = अणु  59500, 0x02 पूर्ण,
				.odr_avl[2] = अणु 119000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 238000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 476000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 952000, 0x06 पूर्ण,
				.odr_len = 6,
			पूर्ण,
		पूर्ण,
		.fs_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x20,
					.mask = GENMASK(4, 3),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_G_TO_M_S_2(61000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_G_TO_M_S_2(122000), 0x2 पूर्ण,
				.fs_avl[2] = अणु IIO_G_TO_M_S_2(244000), 0x3 पूर्ण,
				.fs_avl[3] = अणु IIO_G_TO_M_S_2(732000), 0x1 पूर्ण,
				.fs_len = 4,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(4, 3),
				पूर्ण,

				.fs_avl[0] = अणु  IIO_DEGREE_TO_RAD(8750000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_DEGREE_TO_RAD(17500000), 0x1 पूर्ण,
				.fs_avl[2] = अणु IIO_DEGREE_TO_RAD(70000000), 0x3 पूर्ण,
				.fs_len = 3,
			पूर्ण,
		पूर्ण,
		.irq_config = अणु
			.irq1 = अणु
				.addr = 0x0c,
				.mask = BIT(3),
			पूर्ण,
			.irq2 = अणु
				.addr = 0x0d,
				.mask = BIT(3),
			पूर्ण,
			.hla = अणु
				.addr = 0x22,
				.mask = BIT(5),
			पूर्ण,
			.od = अणु
				.addr = 0x22,
				.mask = BIT(4),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.reset = अणु
			.addr = 0x12,
			.mask = BIT(0),
		पूर्ण,
		.boot = अणु
			.addr = 0x12,
			.mask = BIT(7),
		पूर्ण,
		.bdu = अणु
			.addr = 0x12,
			.mask = BIT(6),
		पूर्ण,
		.max_fअगरo_size = 1365,
		.id = अणु
			अणु
				.hw_id = ST_LSM6DS3_ID,
				.name = ST_LSM6DS3_DEV_NAME,
				.wai = 0x69,
			पूर्ण,
		पूर्ण,
		.channels = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.chan = st_lsm6dsx_acc_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_acc_channels),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.chan = st_lsm6dsx_gyro_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_gyro_channels),
			पूर्ण,
		पूर्ण,
		.odr_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_len = 6,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_len = 6,
			पूर्ण,
		पूर्ण,
		.fs_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_G_TO_M_S_2(61000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_G_TO_M_S_2(122000), 0x2 पूर्ण,
				.fs_avl[2] = अणु IIO_G_TO_M_S_2(244000), 0x3 पूर्ण,
				.fs_avl[3] = अणु IIO_G_TO_M_S_2(488000), 0x1 पूर्ण,
				.fs_len = 4,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_DEGREE_TO_RAD(8750000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_DEGREE_TO_RAD(17500000), 0x1 पूर्ण,
				.fs_avl[2] = अणु IIO_DEGREE_TO_RAD(35000000), 0x2 पूर्ण,
				.fs_avl[3] = अणु IIO_DEGREE_TO_RAD(70000000), 0x3 पूर्ण,
				.fs_len = 4,
			पूर्ण,
		पूर्ण,
		.irq_config = अणु
			.irq1 = अणु
				.addr = 0x0d,
				.mask = BIT(3),
			पूर्ण,
			.irq2 = अणु
				.addr = 0x0e,
				.mask = BIT(3),
			पूर्ण,
			.lir = अणु
				.addr = 0x58,
				.mask = BIT(0),
			पूर्ण,
			.irq1_func = अणु
				.addr = 0x5e,
				.mask = BIT(5),
			पूर्ण,
			.irq2_func = अणु
				.addr = 0x5f,
				.mask = BIT(5),
			पूर्ण,
			.hla = अणु
				.addr = 0x12,
				.mask = BIT(5),
			पूर्ण,
			.od = अणु
				.addr = 0x12,
				.mask = BIT(4),
			पूर्ण,
		पूर्ण,
		.decimator = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.addr = 0x08,
				.mask = GENMASK(2, 0),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.addr = 0x08,
				.mask = GENMASK(5, 3),
			पूर्ण,
		पूर्ण,
		.fअगरo_ops = अणु
			.update_fअगरo = st_lsm6dsx_update_fअगरo,
			.पढ़ो_fअगरo = st_lsm6dsx_पढ़ो_fअगरo,
			.fअगरo_th = अणु
				.addr = 0x06,
				.mask = GENMASK(11, 0),
			पूर्ण,
			.fअगरo_dअगरf = अणु
				.addr = 0x3a,
				.mask = GENMASK(11, 0),
			पूर्ण,
			.th_wl = 3, /* 1LSB = 2B */
		पूर्ण,
		.ts_settings = अणु
			.समयr_en = अणु
				.addr = 0x58,
				.mask = BIT(7),
			पूर्ण,
			.hr_समयr = अणु
				.addr = 0x5c,
				.mask = BIT(4),
			पूर्ण,
			.fअगरo_en = अणु
				.addr = 0x07,
				.mask = BIT(7),
			पूर्ण,
			.decimator = अणु
				.addr = 0x09,
				.mask = GENMASK(5, 3),
			पूर्ण,
		पूर्ण,
		.event_settings = अणु
			.wakeup_reg = अणु
				.addr = 0x5B,
				.mask = GENMASK(5, 0),
			पूर्ण,
			.wakeup_src_reg = 0x1b,
			.wakeup_src_status_mask = BIT(3),
			.wakeup_src_z_mask = BIT(0),
			.wakeup_src_y_mask = BIT(1),
			.wakeup_src_x_mask = BIT(2),
		पूर्ण,
	पूर्ण,
	अणु
		.reset = अणु
			.addr = 0x12,
			.mask = BIT(0),
		पूर्ण,
		.boot = अणु
			.addr = 0x12,
			.mask = BIT(7),
		पूर्ण,
		.bdu = अणु
			.addr = 0x12,
			.mask = BIT(6),
		पूर्ण,
		.max_fअगरo_size = 682,
		.id = अणु
			अणु
				.hw_id = ST_LSM6DS3H_ID,
				.name = ST_LSM6DS3H_DEV_NAME,
				.wai = 0x69,
			पूर्ण,
		पूर्ण,
		.channels = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.chan = st_lsm6dsx_acc_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_acc_channels),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.chan = st_lsm6dsx_gyro_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_gyro_channels),
			पूर्ण,
		पूर्ण,
		.odr_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_len = 6,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_len = 6,
			पूर्ण,
		पूर्ण,
		.fs_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_G_TO_M_S_2(61000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_G_TO_M_S_2(122000), 0x2 पूर्ण,
				.fs_avl[2] = अणु IIO_G_TO_M_S_2(244000), 0x3 पूर्ण,
				.fs_avl[3] = अणु IIO_G_TO_M_S_2(488000), 0x1 पूर्ण,
				.fs_len = 4,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_DEGREE_TO_RAD(8750000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_DEGREE_TO_RAD(17500000), 0x1 पूर्ण,
				.fs_avl[2] = अणु IIO_DEGREE_TO_RAD(35000000), 0x2 पूर्ण,
				.fs_avl[3] = अणु IIO_DEGREE_TO_RAD(70000000), 0x3 पूर्ण,
				.fs_len = 4,
			पूर्ण,
		पूर्ण,
		.irq_config = अणु
			.irq1 = अणु
				.addr = 0x0d,
				.mask = BIT(3),
			पूर्ण,
			.irq2 = अणु
				.addr = 0x0e,
				.mask = BIT(3),
			पूर्ण,
			.lir = अणु
				.addr = 0x58,
				.mask = BIT(0),
			पूर्ण,
			.irq1_func = अणु
				.addr = 0x5e,
				.mask = BIT(5),
			पूर्ण,
			.irq2_func = अणु
				.addr = 0x5f,
				.mask = BIT(5),
			पूर्ण,
			.hla = अणु
				.addr = 0x12,
				.mask = BIT(5),
			पूर्ण,
			.od = अणु
				.addr = 0x12,
				.mask = BIT(4),
			पूर्ण,
		पूर्ण,
		.decimator = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.addr = 0x08,
				.mask = GENMASK(2, 0),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.addr = 0x08,
				.mask = GENMASK(5, 3),
			पूर्ण,
		पूर्ण,
		.fअगरo_ops = अणु
			.update_fअगरo = st_lsm6dsx_update_fअगरo,
			.पढ़ो_fअगरo = st_lsm6dsx_पढ़ो_fअगरo,
			.fअगरo_th = अणु
				.addr = 0x06,
				.mask = GENMASK(11, 0),
			पूर्ण,
			.fअगरo_dअगरf = अणु
				.addr = 0x3a,
				.mask = GENMASK(11, 0),
			पूर्ण,
			.th_wl = 3, /* 1LSB = 2B */
		पूर्ण,
		.ts_settings = अणु
			.समयr_en = अणु
				.addr = 0x58,
				.mask = BIT(7),
			पूर्ण,
			.hr_समयr = अणु
				.addr = 0x5c,
				.mask = BIT(4),
			पूर्ण,
			.fअगरo_en = अणु
				.addr = 0x07,
				.mask = BIT(7),
			पूर्ण,
			.decimator = अणु
				.addr = 0x09,
				.mask = GENMASK(5, 3),
			पूर्ण,
		पूर्ण,
		.event_settings = अणु
			.wakeup_reg = अणु
				.addr = 0x5B,
				.mask = GENMASK(5, 0),
			पूर्ण,
			.wakeup_src_reg = 0x1b,
			.wakeup_src_status_mask = BIT(3),
			.wakeup_src_z_mask = BIT(0),
			.wakeup_src_y_mask = BIT(1),
			.wakeup_src_x_mask = BIT(2),
		पूर्ण,
	पूर्ण,
	अणु
		.reset = अणु
			.addr = 0x12,
			.mask = BIT(0),
		पूर्ण,
		.boot = अणु
			.addr = 0x12,
			.mask = BIT(7),
		पूर्ण,
		.bdu = अणु
			.addr = 0x12,
			.mask = BIT(6),
		पूर्ण,
		.max_fअगरo_size = 682,
		.id = अणु
			अणु
				.hw_id = ST_LSM6DSL_ID,
				.name = ST_LSM6DSL_DEV_NAME,
				.wai = 0x6a,
			पूर्ण, अणु
				.hw_id = ST_LSM6DSM_ID,
				.name = ST_LSM6DSM_DEV_NAME,
				.wai = 0x6a,
			पूर्ण, अणु
				.hw_id = ST_ISM330DLC_ID,
				.name = ST_ISM330DLC_DEV_NAME,
				.wai = 0x6a,
			पूर्ण, अणु
				.hw_id = ST_LSM6DS3TRC_ID,
				.name = ST_LSM6DS3TRC_DEV_NAME,
				.wai = 0x6a,
			पूर्ण,
		पूर्ण,
		.channels = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.chan = st_lsm6dsx_acc_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_acc_channels),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.chan = st_lsm6dsx_gyro_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_gyro_channels),
			पूर्ण,
		पूर्ण,
		.odr_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_len = 6,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_len = 6,
			पूर्ण,
		पूर्ण,
		.fs_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_G_TO_M_S_2(61000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_G_TO_M_S_2(122000), 0x2 पूर्ण,
				.fs_avl[2] = अणु IIO_G_TO_M_S_2(244000), 0x3 पूर्ण,
				.fs_avl[3] = अणु IIO_G_TO_M_S_2(488000), 0x1 पूर्ण,
				.fs_len = 4,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_DEGREE_TO_RAD(8750000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_DEGREE_TO_RAD(17500000), 0x1 पूर्ण,
				.fs_avl[2] = अणु IIO_DEGREE_TO_RAD(35000000), 0x2 पूर्ण,
				.fs_avl[3] = अणु IIO_DEGREE_TO_RAD(70000000), 0x3 पूर्ण,
				.fs_len = 4,
			पूर्ण,
		पूर्ण,
		.irq_config = अणु
			.irq1 = अणु
				.addr = 0x0d,
				.mask = BIT(3),
			पूर्ण,
			.irq2 = अणु
				.addr = 0x0e,
				.mask = BIT(3),
			पूर्ण,
			.lir = अणु
				.addr = 0x58,
				.mask = BIT(0),
			पूर्ण,
			.irq1_func = अणु
				.addr = 0x5e,
				.mask = BIT(5),
			पूर्ण,
			.irq2_func = अणु
				.addr = 0x5f,
				.mask = BIT(5),
			पूर्ण,
			.hla = अणु
				.addr = 0x12,
				.mask = BIT(5),
			पूर्ण,
			.od = अणु
				.addr = 0x12,
				.mask = BIT(4),
			पूर्ण,
		पूर्ण,
		.decimator = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.addr = 0x08,
				.mask = GENMASK(2, 0),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.addr = 0x08,
				.mask = GENMASK(5, 3),
			पूर्ण,
			[ST_LSM6DSX_ID_EXT0] = अणु
				.addr = 0x09,
				.mask = GENMASK(2, 0),
			पूर्ण,
		पूर्ण,
		.fअगरo_ops = अणु
			.update_fअगरo = st_lsm6dsx_update_fअगरo,
			.पढ़ो_fअगरo = st_lsm6dsx_पढ़ो_fअगरo,
			.fअगरo_th = अणु
				.addr = 0x06,
				.mask = GENMASK(10, 0),
			पूर्ण,
			.fअगरo_dअगरf = अणु
				.addr = 0x3a,
				.mask = GENMASK(10, 0),
			पूर्ण,
			.th_wl = 3, /* 1LSB = 2B */
		पूर्ण,
		.ts_settings = अणु
			.समयr_en = अणु
				.addr = 0x19,
				.mask = BIT(5),
			पूर्ण,
			.hr_समयr = अणु
				.addr = 0x5c,
				.mask = BIT(4),
			पूर्ण,
			.fअगरo_en = अणु
				.addr = 0x07,
				.mask = BIT(7),
			पूर्ण,
			.decimator = अणु
				.addr = 0x09,
				.mask = GENMASK(5, 3),
			पूर्ण,
		पूर्ण,
		.shub_settings = अणु
			.page_mux = अणु
				.addr = 0x01,
				.mask = BIT(7),
			पूर्ण,
			.master_en = अणु
				.addr = 0x1a,
				.mask = BIT(0),
			पूर्ण,
			.pullup_en = अणु
				.addr = 0x1a,
				.mask = BIT(3),
			पूर्ण,
			.aux_sens = अणु
				.addr = 0x04,
				.mask = GENMASK(5, 4),
			पूर्ण,
			.wr_once = अणु
				.addr = 0x07,
				.mask = BIT(5),
			पूर्ण,
			.emb_func = अणु
				.addr = 0x19,
				.mask = BIT(2),
			पूर्ण,
			.num_ext_dev = 1,
			.shub_out = अणु
				.addr = 0x2e,
			पूर्ण,
			.slv0_addr = 0x02,
			.dw_slv0_addr = 0x0e,
			.छोड़ो = 0x7,
		पूर्ण,
		.event_settings = अणु
			.enable_reg = अणु
				.addr = 0x58,
				.mask = BIT(7),
			पूर्ण,
			.wakeup_reg = अणु
				.addr = 0x5B,
				.mask = GENMASK(5, 0),
			पूर्ण,
			.wakeup_src_reg = 0x1b,
			.wakeup_src_status_mask = BIT(3),
			.wakeup_src_z_mask = BIT(0),
			.wakeup_src_y_mask = BIT(1),
			.wakeup_src_x_mask = BIT(2),
		पूर्ण,
	पूर्ण,
	अणु
		.reset = अणु
			.addr = 0x12,
			.mask = BIT(0),
		पूर्ण,
		.boot = अणु
			.addr = 0x12,
			.mask = BIT(7),
		पूर्ण,
		.bdu = अणु
			.addr = 0x12,
			.mask = BIT(6),
		पूर्ण,
		.max_fअगरo_size = 512,
		.id = अणु
			अणु
				.hw_id = ST_LSM6DSR_ID,
				.name = ST_LSM6DSR_DEV_NAME,
				.wai = 0x6b,
			पूर्ण, अणु
				.hw_id = ST_ISM330DHCX_ID,
				.name = ST_ISM330DHCX_DEV_NAME,
				.wai = 0x6b,
			पूर्ण, अणु
				.hw_id = ST_LSM6DSRX_ID,
				.name = ST_LSM6DSRX_DEV_NAME,
				.wai = 0x6b,
			पूर्ण, अणु
				.hw_id = ST_LSM6DSO_ID,
				.name = ST_LSM6DSO_DEV_NAME,
				.wai = 0x6c,
			पूर्ण, अणु
				.hw_id = ST_LSM6DSOX_ID,
				.name = ST_LSM6DSOX_DEV_NAME,
				.wai = 0x6c,
			पूर्ण, अणु
				.hw_id = ST_LSM6DST_ID,
				.name = ST_LSM6DST_DEV_NAME,
				.wai = 0x6d,
			पूर्ण,
		पूर्ण,
		.channels = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.chan = st_lsm6dsx_acc_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_acc_channels),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.chan = st_lsm6dsx_gyro_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_gyro_channels),
			पूर्ण,
		पूर्ण,
		.drdy_mask = अणु
			.addr = 0x13,
			.mask = BIT(3),
		पूर्ण,
		.odr_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_avl[6] = अणु 833000, 0x07 पूर्ण,
				.odr_len = 7,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_avl[6] = अणु 833000, 0x07 पूर्ण,
				.odr_len = 7,
			पूर्ण,
		पूर्ण,
		.fs_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_G_TO_M_S_2(61000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_G_TO_M_S_2(122000), 0x2 पूर्ण,
				.fs_avl[2] = अणु IIO_G_TO_M_S_2(244000), 0x3 पूर्ण,
				.fs_avl[3] = अणु IIO_G_TO_M_S_2(488000), 0x1 पूर्ण,
				.fs_len = 4,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_DEGREE_TO_RAD(8750000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_DEGREE_TO_RAD(17500000), 0x1 पूर्ण,
				.fs_avl[2] = अणु IIO_DEGREE_TO_RAD(35000000), 0x2 पूर्ण,
				.fs_avl[3] = अणु IIO_DEGREE_TO_RAD(70000000), 0x3 पूर्ण,
				.fs_len = 4,
			पूर्ण,
		पूर्ण,
		.irq_config = अणु
			.irq1 = अणु
				.addr = 0x0d,
				.mask = BIT(3),
			पूर्ण,
			.irq2 = अणु
				.addr = 0x0e,
				.mask = BIT(3),
			पूर्ण,
			.lir = अणु
				.addr = 0x56,
				.mask = BIT(0),
			पूर्ण,
			.clear_on_पढ़ो = अणु
				.addr = 0x56,
				.mask = BIT(6),
			पूर्ण,
			.irq1_func = अणु
				.addr = 0x5e,
				.mask = BIT(5),
			पूर्ण,
			.irq2_func = अणु
				.addr = 0x5f,
				.mask = BIT(5),
			पूर्ण,
			.hla = अणु
				.addr = 0x12,
				.mask = BIT(5),
			पूर्ण,
			.od = अणु
				.addr = 0x12,
				.mask = BIT(4),
			पूर्ण,
		पूर्ण,
		.batch = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.addr = 0x09,
				.mask = GENMASK(3, 0),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.addr = 0x09,
				.mask = GENMASK(7, 4),
			पूर्ण,
		पूर्ण,
		.fअगरo_ops = अणु
			.update_fअगरo = st_lsm6dsx_update_fअगरo,
			.पढ़ो_fअगरo = st_lsm6dsx_पढ़ो_tagged_fअगरo,
			.fअगरo_th = अणु
				.addr = 0x07,
				.mask = GENMASK(8, 0),
			पूर्ण,
			.fअगरo_dअगरf = अणु
				.addr = 0x3a,
				.mask = GENMASK(9, 0),
			पूर्ण,
			.th_wl = 1,
		पूर्ण,
		.ts_settings = अणु
			.समयr_en = अणु
				.addr = 0x19,
				.mask = BIT(5),
			पूर्ण,
			.decimator = अणु
				.addr = 0x0a,
				.mask = GENMASK(7, 6),
			पूर्ण,
			.freq_fine = 0x63,
		पूर्ण,
		.shub_settings = अणु
			.page_mux = अणु
				.addr = 0x01,
				.mask = BIT(6),
			पूर्ण,
			.master_en = अणु
				.sec_page = true,
				.addr = 0x14,
				.mask = BIT(2),
			पूर्ण,
			.pullup_en = अणु
				.sec_page = true,
				.addr = 0x14,
				.mask = BIT(3),
			पूर्ण,
			.aux_sens = अणु
				.addr = 0x14,
				.mask = GENMASK(1, 0),
			पूर्ण,
			.wr_once = अणु
				.addr = 0x14,
				.mask = BIT(6),
			पूर्ण,
			.num_ext_dev = 3,
			.shub_out = अणु
				.sec_page = true,
				.addr = 0x02,
			पूर्ण,
			.slv0_addr = 0x15,
			.dw_slv0_addr = 0x21,
			.batch_en = BIT(3),
		पूर्ण,
		.event_settings = अणु
			.enable_reg = अणु
				.addr = 0x58,
				.mask = BIT(7),
			पूर्ण,
			.wakeup_reg = अणु
				.addr = 0x5b,
				.mask = GENMASK(5, 0),
			पूर्ण,
			.wakeup_src_reg = 0x1b,
			.wakeup_src_status_mask = BIT(3),
			.wakeup_src_z_mask = BIT(0),
			.wakeup_src_y_mask = BIT(1),
			.wakeup_src_x_mask = BIT(2),
		पूर्ण,
	पूर्ण,
	अणु
		.reset = अणु
			.addr = 0x12,
			.mask = BIT(0),
		पूर्ण,
		.boot = अणु
			.addr = 0x12,
			.mask = BIT(7),
		पूर्ण,
		.bdu = अणु
			.addr = 0x12,
			.mask = BIT(6),
		पूर्ण,
		.max_fअगरo_size = 512,
		.id = अणु
			अणु
				.hw_id = ST_ASM330LHH_ID,
				.name = ST_ASM330LHH_DEV_NAME,
				.wai = 0x6b,
			पूर्ण, अणु
				.hw_id = ST_LSM6DSOP_ID,
				.name = ST_LSM6DSOP_DEV_NAME,
				.wai = 0x6c,
			पूर्ण,
		पूर्ण,
		.channels = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.chan = st_lsm6dsx_acc_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_acc_channels),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.chan = st_lsm6dsx_gyro_channels,
				.len = ARRAY_SIZE(st_lsm6dsx_gyro_channels),
			पूर्ण,
		पूर्ण,
		.drdy_mask = अणु
			.addr = 0x13,
			.mask = BIT(3),
		पूर्ण,
		.odr_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_avl[6] = अणु 833000, 0x07 पूर्ण,
				.odr_len = 7,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(7, 4),
				पूर्ण,
				.odr_avl[0] = अणु  12500, 0x01 पूर्ण,
				.odr_avl[1] = अणु  26000, 0x02 पूर्ण,
				.odr_avl[2] = अणु  52000, 0x03 पूर्ण,
				.odr_avl[3] = अणु 104000, 0x04 पूर्ण,
				.odr_avl[4] = अणु 208000, 0x05 पूर्ण,
				.odr_avl[5] = अणु 416000, 0x06 पूर्ण,
				.odr_avl[6] = अणु 833000, 0x07 पूर्ण,
				.odr_len = 7,
			पूर्ण,
		पूर्ण,
		.fs_table = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.reg = अणु
					.addr = 0x10,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_G_TO_M_S_2(61000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_G_TO_M_S_2(122000), 0x2 पूर्ण,
				.fs_avl[2] = अणु IIO_G_TO_M_S_2(244000), 0x3 पूर्ण,
				.fs_avl[3] = अणु IIO_G_TO_M_S_2(488000), 0x1 पूर्ण,
				.fs_len = 4,
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.reg = अणु
					.addr = 0x11,
					.mask = GENMASK(3, 2),
				पूर्ण,
				.fs_avl[0] = अणु  IIO_DEGREE_TO_RAD(8750000), 0x0 पूर्ण,
				.fs_avl[1] = अणु IIO_DEGREE_TO_RAD(17500000), 0x1 पूर्ण,
				.fs_avl[2] = अणु IIO_DEGREE_TO_RAD(35000000), 0x2 पूर्ण,
				.fs_avl[3] = अणु IIO_DEGREE_TO_RAD(70000000), 0x3 पूर्ण,
				.fs_len = 4,
			पूर्ण,
		पूर्ण,
		.irq_config = अणु
			.irq1 = अणु
				.addr = 0x0d,
				.mask = BIT(3),
			पूर्ण,
			.irq2 = अणु
				.addr = 0x0e,
				.mask = BIT(3),
			पूर्ण,
			.lir = अणु
				.addr = 0x56,
				.mask = BIT(0),
			पूर्ण,
			.clear_on_पढ़ो = अणु
				.addr = 0x56,
				.mask = BIT(6),
			पूर्ण,
			.irq1_func = अणु
				.addr = 0x5e,
				.mask = BIT(5),
			पूर्ण,
			.irq2_func = अणु
				.addr = 0x5f,
				.mask = BIT(5),
			पूर्ण,
			.hla = अणु
				.addr = 0x12,
				.mask = BIT(5),
			पूर्ण,
			.od = अणु
				.addr = 0x12,
				.mask = BIT(4),
			पूर्ण,
		पूर्ण,
		.batch = अणु
			[ST_LSM6DSX_ID_ACC] = अणु
				.addr = 0x09,
				.mask = GENMASK(3, 0),
			पूर्ण,
			[ST_LSM6DSX_ID_GYRO] = अणु
				.addr = 0x09,
				.mask = GENMASK(7, 4),
			पूर्ण,
		पूर्ण,
		.fअगरo_ops = अणु
			.update_fअगरo = st_lsm6dsx_update_fअगरo,
			.पढ़ो_fअगरo = st_lsm6dsx_पढ़ो_tagged_fअगरo,
			.fअगरo_th = अणु
				.addr = 0x07,
				.mask = GENMASK(8, 0),
			पूर्ण,
			.fअगरo_dअगरf = अणु
				.addr = 0x3a,
				.mask = GENMASK(9, 0),
			पूर्ण,
			.th_wl = 1,
		पूर्ण,
		.ts_settings = अणु
			.समयr_en = अणु
				.addr = 0x19,
				.mask = BIT(5),
			पूर्ण,
			.decimator = अणु
				.addr = 0x0a,
				.mask = GENMASK(7, 6),
			पूर्ण,
			.freq_fine = 0x63,
		पूर्ण,
		.event_settings = अणु
			.enable_reg = अणु
				.addr = 0x58,
				.mask = BIT(7),
			पूर्ण,
			.wakeup_reg = अणु
				.addr = 0x5B,
				.mask = GENMASK(5, 0),
			पूर्ण,
			.wakeup_src_reg = 0x1b,
			.wakeup_src_status_mask = BIT(3),
			.wakeup_src_z_mask = BIT(0),
			.wakeup_src_y_mask = BIT(1),
			.wakeup_src_x_mask = BIT(2),
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक st_lsm6dsx_set_page(काष्ठा st_lsm6dsx_hw *hw, bool enable)
अणु
	स्थिर काष्ठा st_lsm6dsx_shub_settings *hub_settings;
	अचिन्हित पूर्णांक data;
	पूर्णांक err;

	hub_settings = &hw->settings->shub_settings;
	data = ST_LSM6DSX_SHIFT_VAL(enable, hub_settings->page_mux.mask);
	err = regmap_update_bits(hw->regmap, hub_settings->page_mux.addr,
				 hub_settings->page_mux.mask, data);
	usleep_range(100, 150);

	वापस err;
पूर्ण

अटल पूर्णांक st_lsm6dsx_check_whoami(काष्ठा st_lsm6dsx_hw *hw, पूर्णांक id,
				   स्थिर अक्षर **name)
अणु
	पूर्णांक err, i, j, data;

	क्रम (i = 0; i < ARRAY_SIZE(st_lsm6dsx_sensor_settings); i++) अणु
		क्रम (j = 0; j < ST_LSM6DSX_MAX_ID; j++) अणु
			अगर (st_lsm6dsx_sensor_settings[i].id[j].name &&
			    id == st_lsm6dsx_sensor_settings[i].id[j].hw_id)
				अवरोध;
		पूर्ण
		अगर (j < ST_LSM6DSX_MAX_ID)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(st_lsm6dsx_sensor_settings)) अणु
		dev_err(hw->dev, "unsupported hw id [%02x]\n", id);
		वापस -ENODEV;
	पूर्ण

	err = regmap_पढ़ो(hw->regmap, ST_LSM6DSX_REG_WHOAMI_ADDR, &data);
	अगर (err < 0) अणु
		dev_err(hw->dev, "failed to read whoami register\n");
		वापस err;
	पूर्ण

	अगर (data != st_lsm6dsx_sensor_settings[i].id[j].wai) अणु
		dev_err(hw->dev, "unsupported whoami [%02x]\n", data);
		वापस -ENODEV;
	पूर्ण

	*name = st_lsm6dsx_sensor_settings[i].id[j].name;
	hw->settings = &st_lsm6dsx_sensor_settings[i];

	वापस 0;
पूर्ण

अटल पूर्णांक st_lsm6dsx_set_full_scale(काष्ठा st_lsm6dsx_sensor *sensor,
				     u32 gain)
अणु
	स्थिर काष्ठा st_lsm6dsx_fs_table_entry *fs_table;
	अचिन्हित पूर्णांक data;
	पूर्णांक i, err;

	fs_table = &sensor->hw->settings->fs_table[sensor->id];
	क्रम (i = 0; i < fs_table->fs_len; i++) अणु
		अगर (fs_table->fs_avl[i].gain == gain)
			अवरोध;
	पूर्ण

	अगर (i == fs_table->fs_len)
		वापस -EINVAL;

	data = ST_LSM6DSX_SHIFT_VAL(fs_table->fs_avl[i].val,
				    fs_table->reg.mask);
	err = st_lsm6dsx_update_bits_locked(sensor->hw, fs_table->reg.addr,
					    fs_table->reg.mask, data);
	अगर (err < 0)
		वापस err;

	sensor->gain = gain;

	वापस 0;
पूर्ण

पूर्णांक st_lsm6dsx_check_odr(काष्ठा st_lsm6dsx_sensor *sensor, u32 odr, u8 *val)
अणु
	स्थिर काष्ठा st_lsm6dsx_odr_table_entry *odr_table;
	पूर्णांक i;

	odr_table = &sensor->hw->settings->odr_table[sensor->id];
	क्रम (i = 0; i < odr_table->odr_len; i++) अणु
		/*
		 * ext devices can run at dअगरferent odr respect to
		 * accel sensor
		 */
		अगर (odr_table->odr_avl[i].milli_hz >= odr)
			अवरोध;
	पूर्ण

	अगर (i == odr_table->odr_len)
		वापस -EINVAL;

	*val = odr_table->odr_avl[i].val;
	वापस odr_table->odr_avl[i].milli_hz;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_check_odr_dependency(काष्ठा st_lsm6dsx_hw *hw, u32 odr,
				क्रमागत st_lsm6dsx_sensor_id id)
अणु
	काष्ठा st_lsm6dsx_sensor *ref = iio_priv(hw->iio_devs[id]);

	अगर (odr > 0) अणु
		अगर (hw->enable_mask & BIT(id))
			वापस max_t(u32, ref->odr, odr);
		अन्यथा
			वापस odr;
	पूर्ण अन्यथा अणु
		वापस (hw->enable_mask & BIT(id)) ? ref->odr : 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
st_lsm6dsx_set_odr(काष्ठा st_lsm6dsx_sensor *sensor, u32 req_odr)
अणु
	काष्ठा st_lsm6dsx_sensor *ref_sensor = sensor;
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	स्थिर काष्ठा st_lsm6dsx_reg *reg;
	अचिन्हित पूर्णांक data;
	u8 val = 0;
	पूर्णांक err;

	चयन (sensor->id) अणु
	हाल ST_LSM6DSX_ID_EXT0:
	हाल ST_LSM6DSX_ID_EXT1:
	हाल ST_LSM6DSX_ID_EXT2:
	हाल ST_LSM6DSX_ID_ACC: अणु
		u32 odr;
		पूर्णांक i;

		/*
		 * i2c embedded controller relies on the accelerometer sensor as
		 * bus पढ़ो/ग_लिखो trigger so we need to enable accel device
		 * at odr = max(accel_odr, ext_odr) in order to properly
		 * communicate with i2c slave devices
		 */
		ref_sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_ACC]);
		क्रम (i = ST_LSM6DSX_ID_ACC; i < ST_LSM6DSX_ID_MAX; i++) अणु
			अगर (!hw->iio_devs[i] || i == sensor->id)
				जारी;

			odr = st_lsm6dsx_check_odr_dependency(hw, req_odr, i);
			अगर (odr != req_odr)
				/* device alपढ़ोy configured */
				वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	अगर (req_odr > 0) अणु
		err = st_lsm6dsx_check_odr(ref_sensor, req_odr, &val);
		अगर (err < 0)
			वापस err;
	पूर्ण

	reg = &hw->settings->odr_table[ref_sensor->id].reg;
	data = ST_LSM6DSX_SHIFT_VAL(val, reg->mask);
	वापस st_lsm6dsx_update_bits_locked(hw, reg->addr, reg->mask, data);
पूर्ण

अटल पूर्णांक
__st_lsm6dsx_sensor_set_enable(काष्ठा st_lsm6dsx_sensor *sensor,
			       bool enable)
अणु
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	u32 odr = enable ? sensor->odr : 0;
	पूर्णांक err;

	err = st_lsm6dsx_set_odr(sensor, odr);
	अगर (err < 0)
		वापस err;

	अगर (enable)
		hw->enable_mask |= BIT(sensor->id);
	अन्यथा
		hw->enable_mask &= ~BIT(sensor->id);

	वापस 0;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_check_events(काष्ठा st_lsm6dsx_sensor *sensor, bool enable)
अणु
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;

	अगर (sensor->id == ST_LSM6DSX_ID_GYRO || enable)
		वापस 0;

	वापस hw->enable_event;
पूर्ण

पूर्णांक st_lsm6dsx_sensor_set_enable(काष्ठा st_lsm6dsx_sensor *sensor,
				 bool enable)
अणु
	अगर (st_lsm6dsx_check_events(sensor, enable))
		वापस 0;

	वापस __st_lsm6dsx_sensor_set_enable(sensor, enable);
पूर्ण

अटल पूर्णांक st_lsm6dsx_पढ़ो_oneshot(काष्ठा st_lsm6dsx_sensor *sensor,
				   u8 addr, पूर्णांक *val)
अणु
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	पूर्णांक err, delay;
	__le16 data;

	err = st_lsm6dsx_sensor_set_enable(sensor, true);
	अगर (err < 0)
		वापस err;

	delay = 1000000000 / sensor->odr;
	usleep_range(delay, 2 * delay);

	err = st_lsm6dsx_पढ़ो_locked(hw, addr, &data, माप(data));
	अगर (err < 0)
		वापस err;

	अगर (!hw->enable_event) अणु
		err = st_lsm6dsx_sensor_set_enable(sensor, false);
		अगर (err < 0)
			वापस err;
	पूर्ण

	*val = (s16)le16_to_cpu(data);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक st_lsm6dsx_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			       काष्ठा iio_chan_spec स्थिर *ch,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(iio_dev);
		अगर (ret)
			अवरोध;

		ret = st_lsm6dsx_पढ़ो_oneshot(sensor, ch->address, val);
		iio_device_release_direct_mode(iio_dev);
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = sensor->odr / 1000;
		*val2 = (sensor->odr % 1000) * 1000;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = sensor->gain;
		ret = IIO_VAL_INT_PLUS_न_अंकO;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक st_lsm6dsx_ग_लिखो_raw(काष्ठा iio_dev *iio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	पूर्णांक err;

	err = iio_device_claim_direct_mode(iio_dev);
	अगर (err)
		वापस err;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		err = st_lsm6dsx_set_full_scale(sensor, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ: अणु
		u8 data;

		val = val * 1000 + val2 / 1000;
		val = st_lsm6dsx_check_odr(sensor, val, &data);
		अगर (val < 0)
			err = val;
		अन्यथा
			sensor->odr = val;
		अवरोध;
	पूर्ण
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	iio_device_release_direct_mode(iio_dev);

	वापस err;
पूर्ण

अटल पूर्णांक st_lsm6dsx_event_setup(काष्ठा st_lsm6dsx_hw *hw, पूर्णांक state)
अणु
	स्थिर काष्ठा st_lsm6dsx_reg *reg;
	अचिन्हित पूर्णांक data;
	पूर्णांक err;

	अगर (!hw->settings->irq_config.irq1_func.addr)
		वापस -ENOTSUPP;

	reg = &hw->settings->event_settings.enable_reg;
	अगर (reg->addr) अणु
		data = ST_LSM6DSX_SHIFT_VAL(state, reg->mask);
		err = st_lsm6dsx_update_bits_locked(hw, reg->addr,
						    reg->mask, data);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Enable wakeup पूर्णांकerrupt */
	data = ST_LSM6DSX_SHIFT_VAL(state, hw->irq_routing->mask);
	वापस st_lsm6dsx_update_bits_locked(hw, hw->irq_routing->addr,
					     hw->irq_routing->mask, data);
पूर्ण

अटल पूर्णांक st_lsm6dsx_पढ़ो_event(काष्ठा iio_dev *iio_dev,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 क्रमागत iio_event_type type,
				 क्रमागत iio_event_direction dir,
				 क्रमागत iio_event_info info,
				 पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;

	अगर (type != IIO_EV_TYPE_THRESH)
		वापस -EINVAL;

	*val2 = 0;
	*val = hw->event_threshold;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_ग_लिखो_event(काष्ठा iio_dev *iio_dev,
		       स्थिर काष्ठा iio_chan_spec *chan,
		       क्रमागत iio_event_type type,
		       क्रमागत iio_event_direction dir,
		       क्रमागत iio_event_info info,
		       पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	स्थिर काष्ठा st_lsm6dsx_reg *reg;
	अचिन्हित पूर्णांक data;
	पूर्णांक err;

	अगर (type != IIO_EV_TYPE_THRESH)
		वापस -EINVAL;

	अगर (val < 0 || val > 31)
		वापस -EINVAL;

	reg = &hw->settings->event_settings.wakeup_reg;
	data = ST_LSM6DSX_SHIFT_VAL(val, reg->mask);
	err = st_lsm6dsx_update_bits_locked(hw, reg->addr,
					    reg->mask, data);
	अगर (err < 0)
		वापस -EINVAL;

	hw->event_threshold = val;

	वापस 0;
पूर्ण

अटल पूर्णांक
st_lsm6dsx_पढ़ो_event_config(काष्ठा iio_dev *iio_dev,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     क्रमागत iio_event_type type,
			     क्रमागत iio_event_direction dir)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;

	अगर (type != IIO_EV_TYPE_THRESH)
		वापस -EINVAL;

	वापस !!(hw->enable_event & BIT(chan->channel2));
पूर्ण

अटल पूर्णांक
st_lsm6dsx_ग_लिखो_event_config(काष्ठा iio_dev *iio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan,
			      क्रमागत iio_event_type type,
			      क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	u8 enable_event;
	पूर्णांक err;

	अगर (type != IIO_EV_TYPE_THRESH)
		वापस -EINVAL;

	अगर (state) अणु
		enable_event = hw->enable_event | BIT(chan->channel2);

		/* करो not enable events अगर they are alपढ़ोy enabled */
		अगर (hw->enable_event)
			जाओ out;
	पूर्ण अन्यथा अणु
		enable_event = hw->enable_event & ~BIT(chan->channel2);

		/* only turn off sensor अगर no events is enabled */
		अगर (enable_event)
			जाओ out;
	पूर्ण

	/* stop here अगर no changes have been made */
	अगर (hw->enable_event == enable_event)
		वापस 0;

	err = st_lsm6dsx_event_setup(hw, state);
	अगर (err < 0)
		वापस err;

	mutex_lock(&hw->conf_lock);
	अगर (enable_event || !(hw->fअगरo_mask & BIT(sensor->id)))
		err = __st_lsm6dsx_sensor_set_enable(sensor, state);
	mutex_unlock(&hw->conf_lock);
	अगर (err < 0)
		वापस err;

out:
	hw->enable_event = enable_event;

	वापस 0;
पूर्ण

पूर्णांक st_lsm6dsx_set_watermark(काष्ठा iio_dev *iio_dev, अचिन्हित पूर्णांक val)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	पूर्णांक err;

	अगर (val < 1 || val > hw->settings->max_fअगरo_size)
		वापस -EINVAL;

	mutex_lock(&hw->conf_lock);

	err = st_lsm6dsx_update_watermark(sensor, val);

	mutex_unlock(&hw->conf_lock);

	अगर (err < 0)
		वापस err;

	sensor->watermark = val;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
st_lsm6dsx_sysfs_sampling_frequency_avail(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(dev_get_drvdata(dev));
	स्थिर काष्ठा st_lsm6dsx_odr_table_entry *odr_table;
	पूर्णांक i, len = 0;

	odr_table = &sensor->hw->settings->odr_table[sensor->id];
	क्रम (i = 0; i < odr_table->odr_len; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%03d ",
				 odr_table->odr_avl[i].milli_hz / 1000,
				 odr_table->odr_avl[i].milli_hz % 1000);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार st_lsm6dsx_sysfs_scale_avail(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(dev_get_drvdata(dev));
	स्थिर काष्ठा st_lsm6dsx_fs_table_entry *fs_table;
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	पूर्णांक i, len = 0;

	fs_table = &hw->settings->fs_table[sensor->id];
	क्रम (i = 0; i < fs_table->fs_len; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "0.%09u ",
				 fs_table->fs_avl[i].gain);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल पूर्णांक st_lsm6dsx_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
					काष्ठा iio_chan_spec स्थिर *chan,
					दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
		हाल IIO_ACCEL:
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		शेष:
			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
	शेष:
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(st_lsm6dsx_sysfs_sampling_frequency_avail);
अटल IIO_DEVICE_ATTR(in_accel_scale_available, 0444,
		       st_lsm6dsx_sysfs_scale_avail, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_anglvel_scale_available, 0444,
		       st_lsm6dsx_sysfs_scale_avail, शून्य, 0);

अटल काष्ठा attribute *st_lsm6dsx_acc_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_accel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group st_lsm6dsx_acc_attribute_group = अणु
	.attrs = st_lsm6dsx_acc_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info st_lsm6dsx_acc_info = अणु
	.attrs = &st_lsm6dsx_acc_attribute_group,
	.पढ़ो_raw = st_lsm6dsx_पढ़ो_raw,
	.ग_लिखो_raw = st_lsm6dsx_ग_लिखो_raw,
	.पढ़ो_event_value = st_lsm6dsx_पढ़ो_event,
	.ग_लिखो_event_value = st_lsm6dsx_ग_लिखो_event,
	.पढ़ो_event_config = st_lsm6dsx_पढ़ो_event_config,
	.ग_लिखो_event_config = st_lsm6dsx_ग_लिखो_event_config,
	.hwfअगरo_set_watermark = st_lsm6dsx_set_watermark,
	.ग_लिखो_raw_get_fmt = st_lsm6dsx_ग_लिखो_raw_get_fmt,
पूर्ण;

अटल काष्ठा attribute *st_lsm6dsx_gyro_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_anglvel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group st_lsm6dsx_gyro_attribute_group = अणु
	.attrs = st_lsm6dsx_gyro_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info st_lsm6dsx_gyro_info = अणु
	.attrs = &st_lsm6dsx_gyro_attribute_group,
	.पढ़ो_raw = st_lsm6dsx_पढ़ो_raw,
	.ग_लिखो_raw = st_lsm6dsx_ग_लिखो_raw,
	.hwfअगरo_set_watermark = st_lsm6dsx_set_watermark,
	.ग_लिखो_raw_get_fmt = st_lsm6dsx_ग_लिखो_raw_get_fmt,
पूर्ण;

अटल पूर्णांक st_lsm6dsx_get_drdy_pin(काष्ठा st_lsm6dsx_hw *hw, पूर्णांक *drdy_pin)
अणु
	काष्ठा device *dev = hw->dev;

	अगर (!dev_fwnode(dev))
		वापस -EINVAL;

	वापस device_property_पढ़ो_u32(dev, "st,drdy-int-pin", drdy_pin);
पूर्ण

अटल पूर्णांक
st_lsm6dsx_get_drdy_reg(काष्ठा st_lsm6dsx_hw *hw,
			स्थिर काष्ठा st_lsm6dsx_reg **drdy_reg)
अणु
	पूर्णांक err = 0, drdy_pin;

	अगर (st_lsm6dsx_get_drdy_pin(hw, &drdy_pin) < 0) अणु
		काष्ठा st_sensors_platक्रमm_data *pdata;
		काष्ठा device *dev = hw->dev;

		pdata = (काष्ठा st_sensors_platक्रमm_data *)dev->platक्रमm_data;
		drdy_pin = pdata ? pdata->drdy_पूर्णांक_pin : 1;
	पूर्ण

	चयन (drdy_pin) अणु
	हाल 1:
		hw->irq_routing = &hw->settings->irq_config.irq1_func;
		*drdy_reg = &hw->settings->irq_config.irq1;
		अवरोध;
	हाल 2:
		hw->irq_routing = &hw->settings->irq_config.irq2_func;
		*drdy_reg = &hw->settings->irq_config.irq2;
		अवरोध;
	शेष:
		dev_err(hw->dev, "unsupported data ready pin\n");
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक st_lsm6dsx_init_shub(काष्ठा st_lsm6dsx_hw *hw)
अणु
	स्थिर काष्ठा st_lsm6dsx_shub_settings *hub_settings;
	काष्ठा st_sensors_platक्रमm_data *pdata;
	काष्ठा device *dev = hw->dev;
	अचिन्हित पूर्णांक data;
	पूर्णांक err = 0;

	hub_settings = &hw->settings->shub_settings;

	pdata = (काष्ठा st_sensors_platक्रमm_data *)dev->platक्रमm_data;
	अगर ((dev_fwnode(dev) && device_property_पढ़ो_bool(dev, "st,pullups")) ||
	    (pdata && pdata->pullups)) अणु
		अगर (hub_settings->pullup_en.sec_page) अणु
			err = st_lsm6dsx_set_page(hw, true);
			अगर (err < 0)
				वापस err;
		पूर्ण

		data = ST_LSM6DSX_SHIFT_VAL(1, hub_settings->pullup_en.mask);
		err = regmap_update_bits(hw->regmap,
					 hub_settings->pullup_en.addr,
					 hub_settings->pullup_en.mask, data);

		अगर (hub_settings->pullup_en.sec_page)
			st_lsm6dsx_set_page(hw, false);

		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (hub_settings->aux_sens.addr) अणु
		/* configure aux sensors */
		err = st_lsm6dsx_set_page(hw, true);
		अगर (err < 0)
			वापस err;

		data = ST_LSM6DSX_SHIFT_VAL(3, hub_settings->aux_sens.mask);
		err = regmap_update_bits(hw->regmap,
					 hub_settings->aux_sens.addr,
					 hub_settings->aux_sens.mask, data);

		st_lsm6dsx_set_page(hw, false);

		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (hub_settings->emb_func.addr) अणु
		data = ST_LSM6DSX_SHIFT_VAL(1, hub_settings->emb_func.mask);
		err = regmap_update_bits(hw->regmap,
					 hub_settings->emb_func.addr,
					 hub_settings->emb_func.mask, data);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक st_lsm6dsx_init_hw_समयr(काष्ठा st_lsm6dsx_hw *hw)
अणु
	स्थिर काष्ठा st_lsm6dsx_hw_ts_settings *ts_settings;
	पूर्णांक err, val;

	ts_settings = &hw->settings->ts_settings;
	/* enable hw बारtamp generation अगर necessary */
	अगर (ts_settings->समयr_en.addr) अणु
		val = ST_LSM6DSX_SHIFT_VAL(1, ts_settings->समयr_en.mask);
		err = regmap_update_bits(hw->regmap,
					 ts_settings->समयr_en.addr,
					 ts_settings->समयr_en.mask, val);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* enable high resolution क्रम hw ts समयr अगर necessary */
	अगर (ts_settings->hr_समयr.addr) अणु
		val = ST_LSM6DSX_SHIFT_VAL(1, ts_settings->hr_समयr.mask);
		err = regmap_update_bits(hw->regmap,
					 ts_settings->hr_समयr.addr,
					 ts_settings->hr_समयr.mask, val);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* enable ts queueing in FIFO अगर necessary */
	अगर (ts_settings->fअगरo_en.addr) अणु
		val = ST_LSM6DSX_SHIFT_VAL(1, ts_settings->fअगरo_en.mask);
		err = regmap_update_bits(hw->regmap,
					 ts_settings->fअगरo_en.addr,
					 ts_settings->fअगरo_en.mask, val);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* calibrate बारtamp sensitivity */
	hw->ts_gain = ST_LSM6DSX_TS_SENSITIVITY;
	अगर (ts_settings->freq_fine) अणु
		err = regmap_पढ़ो(hw->regmap, ts_settings->freq_fine, &val);
		अगर (err < 0)
			वापस err;

		/*
		 * linearize the AN5192 क्रमmula:
		 * 1 / (1 + x) ~= 1 - x (Taylorै s Series)
		 * ttrim[s] = 1 / (40000 * (1 + 0.0015 * val))
		 * ttrim[ns] ~= 25000 - 37.5 * val
		 * ttrim[ns] ~= 25000 - (37500 * val) / 1000
		 */
		hw->ts_gain -= ((s8)val * 37500) / 1000;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_lsm6dsx_reset_device(काष्ठा st_lsm6dsx_hw *hw)
अणु
	स्थिर काष्ठा st_lsm6dsx_reg *reg;
	पूर्णांक err;

	/*
	 * flush hw FIFO beक्रमe device reset in order to aव्योम
	 * possible races on पूर्णांकerrupt line 1. If the first पूर्णांकerrupt
	 * line is निश्चितed during hw reset the device will work in
	 * I3C-only mode (अगर it is supported)
	 */
	err = st_lsm6dsx_flush_fअगरo(hw);
	अगर (err < 0 && err != -ENOTSUPP)
		वापस err;

	/* device sw reset */
	reg = &hw->settings->reset;
	err = regmap_update_bits(hw->regmap, reg->addr, reg->mask,
				 ST_LSM6DSX_SHIFT_VAL(1, reg->mask));
	अगर (err < 0)
		वापस err;

	msleep(50);

	/* reload trimming parameter */
	reg = &hw->settings->boot;
	err = regmap_update_bits(hw->regmap, reg->addr, reg->mask,
				 ST_LSM6DSX_SHIFT_VAL(1, reg->mask));
	अगर (err < 0)
		वापस err;

	msleep(50);

	वापस 0;
पूर्ण

अटल पूर्णांक st_lsm6dsx_init_device(काष्ठा st_lsm6dsx_hw *hw)
अणु
	स्थिर काष्ठा st_lsm6dsx_reg *reg;
	पूर्णांक err;

	err = st_lsm6dsx_reset_device(hw);
	अगर (err < 0)
		वापस err;

	/* enable Block Data Update */
	reg = &hw->settings->bdu;
	err = regmap_update_bits(hw->regmap, reg->addr, reg->mask,
				 ST_LSM6DSX_SHIFT_VAL(1, reg->mask));
	अगर (err < 0)
		वापस err;

	/* enable FIFO watermak पूर्णांकerrupt */
	err = st_lsm6dsx_get_drdy_reg(hw, &reg);
	अगर (err < 0)
		वापस err;

	err = regmap_update_bits(hw->regmap, reg->addr, reg->mask,
				 ST_LSM6DSX_SHIFT_VAL(1, reg->mask));
	अगर (err < 0)
		वापस err;

	/* enable Latched पूर्णांकerrupts क्रम device events */
	अगर (hw->settings->irq_config.lir.addr) अणु
		reg = &hw->settings->irq_config.lir;
		err = regmap_update_bits(hw->regmap, reg->addr, reg->mask,
					 ST_LSM6DSX_SHIFT_VAL(1, reg->mask));
		अगर (err < 0)
			वापस err;

		/* enable clear on पढ़ो क्रम latched पूर्णांकerrupts */
		अगर (hw->settings->irq_config.clear_on_पढ़ो.addr) अणु
			reg = &hw->settings->irq_config.clear_on_पढ़ो;
			err = regmap_update_bits(hw->regmap,
					reg->addr, reg->mask,
					ST_LSM6DSX_SHIFT_VAL(1, reg->mask));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* enable drdy-mas अगर available */
	अगर (hw->settings->drdy_mask.addr) अणु
		reg = &hw->settings->drdy_mask;
		err = regmap_update_bits(hw->regmap, reg->addr, reg->mask,
					 ST_LSM6DSX_SHIFT_VAL(1, reg->mask));
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = st_lsm6dsx_init_shub(hw);
	अगर (err < 0)
		वापस err;

	वापस st_lsm6dsx_init_hw_समयr(hw);
पूर्ण

अटल काष्ठा iio_dev *st_lsm6dsx_alloc_iiodev(काष्ठा st_lsm6dsx_hw *hw,
					       क्रमागत st_lsm6dsx_sensor_id id,
					       स्थिर अक्षर *name)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor;
	काष्ठा iio_dev *iio_dev;

	iio_dev = devm_iio_device_alloc(hw->dev, माप(*sensor));
	अगर (!iio_dev)
		वापस शून्य;

	iio_dev->modes = INDIO_सूचीECT_MODE;
	iio_dev->available_scan_masks = st_lsm6dsx_available_scan_masks;
	iio_dev->channels = hw->settings->channels[id].chan;
	iio_dev->num_channels = hw->settings->channels[id].len;

	sensor = iio_priv(iio_dev);
	sensor->id = id;
	sensor->hw = hw;
	sensor->odr = hw->settings->odr_table[id].odr_avl[0].milli_hz;
	sensor->gain = hw->settings->fs_table[id].fs_avl[0].gain;
	sensor->watermark = 1;

	चयन (id) अणु
	हाल ST_LSM6DSX_ID_ACC:
		iio_dev->info = &st_lsm6dsx_acc_info;
		scnम_लिखो(sensor->name, माप(sensor->name), "%s_accel",
			  name);
		अवरोध;
	हाल ST_LSM6DSX_ID_GYRO:
		iio_dev->info = &st_lsm6dsx_gyro_info;
		scnम_लिखो(sensor->name, माप(sensor->name), "%s_gyro",
			  name);
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण
	iio_dev->name = sensor->name;

	वापस iio_dev;
पूर्ण

अटल bool
st_lsm6dsx_report_motion_event(काष्ठा st_lsm6dsx_hw *hw)
अणु
	स्थिर काष्ठा st_lsm6dsx_event_settings *event_settings;
	पूर्णांक err, data;
	s64 बारtamp;

	अगर (!hw->enable_event)
		वापस false;

	event_settings = &hw->settings->event_settings;
	err = st_lsm6dsx_पढ़ो_locked(hw, event_settings->wakeup_src_reg,
				     &data, माप(data));
	अगर (err < 0)
		वापस false;

	बारtamp = iio_get_समय_ns(hw->iio_devs[ST_LSM6DSX_ID_ACC]);
	अगर ((data & hw->settings->event_settings.wakeup_src_z_mask) &&
	    (hw->enable_event & BIT(IIO_MOD_Z)))
		iio_push_event(hw->iio_devs[ST_LSM6DSX_ID_ACC],
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Z,
						  IIO_EV_TYPE_THRESH,
						  IIO_EV_सूची_EITHER),
						  बारtamp);

	अगर ((data & hw->settings->event_settings.wakeup_src_y_mask) &&
	    (hw->enable_event & BIT(IIO_MOD_Y)))
		iio_push_event(hw->iio_devs[ST_LSM6DSX_ID_ACC],
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Y,
						  IIO_EV_TYPE_THRESH,
						  IIO_EV_सूची_EITHER),
						  बारtamp);

	अगर ((data & hw->settings->event_settings.wakeup_src_x_mask) &&
	    (hw->enable_event & BIT(IIO_MOD_X)))
		iio_push_event(hw->iio_devs[ST_LSM6DSX_ID_ACC],
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_X,
						  IIO_EV_TYPE_THRESH,
						  IIO_EV_सूची_EITHER),
						  बारtamp);

	वापस data & event_settings->wakeup_src_status_mask;
पूर्ण

अटल irqवापस_t st_lsm6dsx_handler_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा st_lsm6dsx_hw *hw = निजी;
	पूर्णांक fअगरo_len = 0, len;
	bool event;

	event = st_lsm6dsx_report_motion_event(hw);

	अगर (!hw->settings->fअगरo_ops.पढ़ो_fअगरo)
		वापस event ? IRQ_HANDLED : IRQ_NONE;

	/*
	 * If we are using edge IRQs, new samples can arrive जबतक
	 * processing current पूर्णांकerrupt since there are no hw
	 * guarantees the irq line stays "low" दीर्घ enough to properly
	 * detect the new पूर्णांकerrupt. In this हाल the new sample will
	 * be missed.
	 * Polling FIFO status रेजिस्टर allow us to पढ़ो new
	 * samples even अगर the पूर्णांकerrupt arrives जबतक processing
	 * previous data and the बारlot where the line is "low" is
	 * too लघु to be properly detected.
	 */
	करो अणु
		mutex_lock(&hw->fअगरo_lock);
		len = hw->settings->fअगरo_ops.पढ़ो_fअगरo(hw);
		mutex_unlock(&hw->fअगरo_lock);

		अगर (len > 0)
			fअगरo_len += len;
	पूर्ण जबतक (len > 0);

	वापस fअगरo_len || event ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक st_lsm6dsx_irq_setup(काष्ठा st_lsm6dsx_hw *hw)
अणु
	काष्ठा st_sensors_platक्रमm_data *pdata;
	स्थिर काष्ठा st_lsm6dsx_reg *reg;
	काष्ठा device *dev = hw->dev;
	अचिन्हित दीर्घ irq_type;
	bool irq_active_low;
	पूर्णांक err;

	irq_type = irqd_get_trigger_type(irq_get_irq_data(hw->irq));

	चयन (irq_type) अणु
	हाल IRQF_TRIGGER_HIGH:
	हाल IRQF_TRIGGER_RISING:
		irq_active_low = false;
		अवरोध;
	हाल IRQF_TRIGGER_LOW:
	हाल IRQF_TRIGGER_FALLING:
		irq_active_low = true;
		अवरोध;
	शेष:
		dev_info(hw->dev, "mode %lx unsupported\n", irq_type);
		वापस -EINVAL;
	पूर्ण

	reg = &hw->settings->irq_config.hla;
	err = regmap_update_bits(hw->regmap, reg->addr, reg->mask,
				 ST_LSM6DSX_SHIFT_VAL(irq_active_low,
						      reg->mask));
	अगर (err < 0)
		वापस err;

	pdata = (काष्ठा st_sensors_platक्रमm_data *)dev->platक्रमm_data;
	अगर ((dev_fwnode(dev) && device_property_पढ़ो_bool(dev, "drive-open-drain")) ||
	    (pdata && pdata->खोलो_drain)) अणु
		reg = &hw->settings->irq_config.od;
		err = regmap_update_bits(hw->regmap, reg->addr, reg->mask,
					 ST_LSM6DSX_SHIFT_VAL(1, reg->mask));
		अगर (err < 0)
			वापस err;

		irq_type |= IRQF_SHARED;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(hw->dev, hw->irq,
					शून्य,
					st_lsm6dsx_handler_thपढ़ो,
					irq_type | IRQF_ONESHOT,
					"lsm6dsx", hw);
	अगर (err) अणु
		dev_err(hw->dev, "failed to request trigger irq %d\n",
			hw->irq);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_lsm6dsx_init_regulators(काष्ठा device *dev)
अणु
	काष्ठा st_lsm6dsx_hw *hw = dev_get_drvdata(dev);
	पूर्णांक err;

	/* vdd-vddio घातer regulators */
	hw->regulators[0].supply = "vdd";
	hw->regulators[1].supply = "vddio";
	err = devm_regulator_bulk_get(dev, ARRAY_SIZE(hw->regulators),
				      hw->regulators);
	अगर (err)
		वापस dev_err_probe(dev, err, "failed to get regulators\n");

	err = regulator_bulk_enable(ARRAY_SIZE(hw->regulators),
				    hw->regulators);
	अगर (err) अणु
		dev_err(dev, "failed to enable regulators: %d\n", err);
		वापस err;
	पूर्ण

	msleep(50);

	वापस 0;
पूर्ण

अटल व्योम st_lsm6dsx_chip_uninit(व्योम *data)
अणु
	काष्ठा st_lsm6dsx_hw *hw = data;

	regulator_bulk_disable(ARRAY_SIZE(hw->regulators), hw->regulators);
पूर्ण

पूर्णांक st_lsm6dsx_probe(काष्ठा device *dev, पूर्णांक irq, पूर्णांक hw_id,
		     काष्ठा regmap *regmap)
अणु
	काष्ठा st_sensors_platक्रमm_data *pdata = dev->platक्रमm_data;
	स्थिर काष्ठा st_lsm6dsx_shub_settings *hub_settings;
	काष्ठा st_lsm6dsx_hw *hw;
	स्थिर अक्षर *name = शून्य;
	पूर्णांक i, err;

	hw = devm_kzalloc(dev, माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;

	dev_set_drvdata(dev, (व्योम *)hw);

	mutex_init(&hw->fअगरo_lock);
	mutex_init(&hw->conf_lock);
	mutex_init(&hw->page_lock);

	err = st_lsm6dsx_init_regulators(dev);
	अगर (err)
		वापस err;

	err = devm_add_action_or_reset(dev, st_lsm6dsx_chip_uninit, hw);
	अगर (err)
		वापस err;

	hw->buff = devm_kzalloc(dev, ST_LSM6DSX_BUFF_SIZE, GFP_KERNEL);
	अगर (!hw->buff)
		वापस -ENOMEM;

	hw->dev = dev;
	hw->irq = irq;
	hw->regmap = regmap;

	err = st_lsm6dsx_check_whoami(hw, hw_id, &name);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < ST_LSM6DSX_ID_EXT0; i++) अणु
		hw->iio_devs[i] = st_lsm6dsx_alloc_iiodev(hw, i, name);
		अगर (!hw->iio_devs[i])
			वापस -ENOMEM;
	पूर्ण

	err = st_lsm6dsx_init_device(hw);
	अगर (err < 0)
		वापस err;

	hub_settings = &hw->settings->shub_settings;
	अगर (hub_settings->master_en.addr) अणु
		err = st_lsm6dsx_shub_probe(hw, name);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (hw->irq > 0) अणु
		err = st_lsm6dsx_irq_setup(hw);
		अगर (err < 0)
			वापस err;

		err = st_lsm6dsx_fअगरo_setup(hw);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = iio_पढ़ो_mount_matrix(hw->dev, "mount-matrix", &hw->orientation);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ST_LSM6DSX_ID_MAX; i++) अणु
		अगर (!hw->iio_devs[i])
			जारी;

		err = devm_iio_device_रेजिस्टर(hw->dev, hw->iio_devs[i]);
		अगर (err)
			वापस err;
	पूर्ण

	अगर ((dev_fwnode(dev) && device_property_पढ़ो_bool(dev, "wakeup-source")) ||
	    (pdata && pdata->wakeup_source))
		device_init_wakeup(dev, true);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(st_lsm6dsx_probe);

अटल पूर्णांक __maybe_unused st_lsm6dsx_suspend(काष्ठा device *dev)
अणु
	काष्ठा st_lsm6dsx_hw *hw = dev_get_drvdata(dev);
	काष्ठा st_lsm6dsx_sensor *sensor;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < ST_LSM6DSX_ID_MAX; i++) अणु
		अगर (!hw->iio_devs[i])
			जारी;

		sensor = iio_priv(hw->iio_devs[i]);
		अगर (!(hw->enable_mask & BIT(sensor->id)))
			जारी;

		अगर (device_may_wakeup(dev) &&
		    sensor->id == ST_LSM6DSX_ID_ACC && hw->enable_event) अणु
			/* Enable wake from IRQ */
			enable_irq_wake(hw->irq);
			जारी;
		पूर्ण

		अगर (sensor->id == ST_LSM6DSX_ID_EXT0 ||
		    sensor->id == ST_LSM6DSX_ID_EXT1 ||
		    sensor->id == ST_LSM6DSX_ID_EXT2)
			err = st_lsm6dsx_shub_set_enable(sensor, false);
		अन्यथा
			err = st_lsm6dsx_sensor_set_enable(sensor, false);
		अगर (err < 0)
			वापस err;

		hw->suspend_mask |= BIT(sensor->id);
	पूर्ण

	अगर (hw->fअगरo_mask)
		err = st_lsm6dsx_flush_fअगरo(hw);

	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused st_lsm6dsx_resume(काष्ठा device *dev)
अणु
	काष्ठा st_lsm6dsx_hw *hw = dev_get_drvdata(dev);
	काष्ठा st_lsm6dsx_sensor *sensor;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < ST_LSM6DSX_ID_MAX; i++) अणु
		अगर (!hw->iio_devs[i])
			जारी;

		sensor = iio_priv(hw->iio_devs[i]);
		अगर (device_may_wakeup(dev) &&
		    sensor->id == ST_LSM6DSX_ID_ACC && hw->enable_event)
			disable_irq_wake(hw->irq);

		अगर (!(hw->suspend_mask & BIT(sensor->id)))
			जारी;

		अगर (sensor->id == ST_LSM6DSX_ID_EXT0 ||
		    sensor->id == ST_LSM6DSX_ID_EXT1 ||
		    sensor->id == ST_LSM6DSX_ID_EXT2)
			err = st_lsm6dsx_shub_set_enable(sensor, true);
		अन्यथा
			err = st_lsm6dsx_sensor_set_enable(sensor, true);
		अगर (err < 0)
			वापस err;

		hw->suspend_mask &= ~BIT(sensor->id);
	पूर्ण

	अगर (hw->fअगरo_mask)
		err = st_lsm6dsx_resume_fअगरo(hw);

	वापस err;
पूर्ण

स्थिर काष्ठा dev_pm_ops st_lsm6dsx_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(st_lsm6dsx_suspend, st_lsm6dsx_resume)
पूर्ण;
EXPORT_SYMBOL(st_lsm6dsx_pm_ops);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi@st.com>");
MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics st_lsm6dsx driver");
MODULE_LICENSE("GPL v2");
