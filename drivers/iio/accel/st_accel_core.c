<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics accelerometers driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/buffer.h>

#समावेश <linux/iio/common/st_sensors.h>
#समावेश "st_accel.h"

#घोषणा ST_ACCEL_NUMBER_DATA_CHANNELS		3

/* DEFAULT VALUE FOR SENSORS */
#घोषणा ST_ACCEL_DEFAULT_OUT_X_L_ADDR		0x28
#घोषणा ST_ACCEL_DEFAULT_OUT_Y_L_ADDR		0x2a
#घोषणा ST_ACCEL_DEFAULT_OUT_Z_L_ADDR		0x2c

/* FULLSCALE */
#घोषणा ST_ACCEL_FS_AVL_2G			2
#घोषणा ST_ACCEL_FS_AVL_4G			4
#घोषणा ST_ACCEL_FS_AVL_6G			6
#घोषणा ST_ACCEL_FS_AVL_8G			8
#घोषणा ST_ACCEL_FS_AVL_16G			16
#घोषणा ST_ACCEL_FS_AVL_100G			100
#घोषणा ST_ACCEL_FS_AVL_200G			200
#घोषणा ST_ACCEL_FS_AVL_400G			400

अटल स्थिर काष्ठा iio_chan_spec st_accel_8bit_channels[] = अणु
	ST_SENSORS_LSM_CHANNELS(IIO_ACCEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_X, 1, IIO_MOD_X, 's', IIO_LE, 8, 8,
			ST_ACCEL_DEFAULT_OUT_X_L_ADDR+1),
	ST_SENSORS_LSM_CHANNELS(IIO_ACCEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_LE, 8, 8,
			ST_ACCEL_DEFAULT_OUT_Y_L_ADDR+1),
	ST_SENSORS_LSM_CHANNELS(IIO_ACCEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_LE, 8, 8,
			ST_ACCEL_DEFAULT_OUT_Z_L_ADDR+1),
	IIO_CHAN_SOFT_TIMESTAMP(3)
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec st_accel_12bit_channels[] = अणु
	ST_SENSORS_LSM_CHANNELS(IIO_ACCEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_X, 1, IIO_MOD_X, 's', IIO_LE, 12, 16,
			ST_ACCEL_DEFAULT_OUT_X_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_ACCEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_LE, 12, 16,
			ST_ACCEL_DEFAULT_OUT_Y_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_ACCEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_LE, 12, 16,
			ST_ACCEL_DEFAULT_OUT_Z_L_ADDR),
	IIO_CHAN_SOFT_TIMESTAMP(3)
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec st_accel_16bit_channels[] = अणु
	ST_SENSORS_LSM_CHANNELS(IIO_ACCEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_X, 1, IIO_MOD_X, 's', IIO_LE, 16, 16,
			ST_ACCEL_DEFAULT_OUT_X_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_ACCEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_LE, 16, 16,
			ST_ACCEL_DEFAULT_OUT_Y_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_ACCEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_LE, 16, 16,
			ST_ACCEL_DEFAULT_OUT_Z_L_ADDR),
	IIO_CHAN_SOFT_TIMESTAMP(3)
पूर्ण;

अटल स्थिर काष्ठा st_sensor_settings st_accel_sensors_settings[] = अणु
	अणु
		.wai = 0x33,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LIS3DH_ACCEL_DEV_NAME,
			[1] = LSM303DLHC_ACCEL_DEV_NAME,
			[2] = LSM330D_ACCEL_DEV_NAME,
			[3] = LSM330DL_ACCEL_DEV_NAME,
			[4] = LSM330DLC_ACCEL_DEV_NAME,
			[5] = LSM303AGR_ACCEL_DEV_NAME,
			[6] = LIS2DH12_ACCEL_DEV_NAME,
			[7] = LIS3DE_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_12bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x01, पूर्ण,
				अणु .hz = 10, .value = 0x02, पूर्ण,
				अणु .hz = 25, .value = 0x03, पूर्ण,
				अणु .hz = 50, .value = 0x04, पूर्ण,
				अणु .hz = 100, .value = 0x05, पूर्ण,
				अणु .hz = 200, .value = 0x06, पूर्ण,
				अणु .hz = 400, .value = 0x07, पूर्ण,
				अणु .hz = 1600, .value = 0x08, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(1000),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_4G,
					.value = 0x01,
					.gain = IIO_G_TO_M_S_2(2000),
				पूर्ण,
				[2] = अणु
					.num = ST_ACCEL_FS_AVL_8G,
					.value = 0x02,
					.gain = IIO_G_TO_M_S_2(4000),
				पूर्ण,
				[3] = अणु
					.num = ST_ACCEL_FS_AVL_16G,
					.value = 0x03,
					.gain = IIO_G_TO_M_S_2(12000),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x23,
			.mask = 0x80,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x22,
				.mask = 0x10,
			पूर्ण,
			.addr_ihl = 0x25,
			.mask_ihl = 0x02,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x32,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LIS331DLH_ACCEL_DEV_NAME,
			[1] = LSM303DL_ACCEL_DEV_NAME,
			[2] = LSM303DLH_ACCEL_DEV_NAME,
			[3] = LSM303DLM_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_12bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0x18,
			.odr_avl = अणु
				अणु .hz = 50, .value = 0x00, पूर्ण,
				अणु .hz = 100, .value = 0x01, पूर्ण,
				अणु .hz = 400, .value = 0x02, पूर्ण,
				अणु .hz = 1000, .value = 0x03, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0xe0,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(1000),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_4G,
					.value = 0x01,
					.gain = IIO_G_TO_M_S_2(2000),
				पूर्ण,
				[2] = अणु
					.num = ST_ACCEL_FS_AVL_8G,
					.value = 0x03,
					.gain = IIO_G_TO_M_S_2(3900),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x23,
			.mask = 0x80,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x22,
				.mask = 0x02,
				.addr_od = 0x22,
				.mask_od = 0x40,
			पूर्ण,
			.पूर्णांक2 = अणु
				.addr = 0x22,
				.mask = 0x10,
				.addr_od = 0x22,
				.mask_od = 0x40,
			पूर्ण,
			.addr_ihl = 0x22,
			.mask_ihl = 0x80,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x40,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LSM330_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_16bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.odr_avl = अणु
				अणु .hz = 3, .value = 0x01, पूर्ण,
				अणु .hz = 6, .value = 0x02, पूर्ण,
				अणु .hz = 12, .value = 0x03, पूर्ण,
				अणु .hz = 25, .value = 0x04, पूर्ण,
				अणु .hz = 50, .value = 0x05, पूर्ण,
				अणु .hz = 100, .value = 0x06, पूर्ण,
				अणु .hz = 200, .value = 0x07, पूर्ण,
				अणु .hz = 400, .value = 0x08, पूर्ण,
				अणु .hz = 800, .value = 0x09, पूर्ण,
				अणु .hz = 1600, .value = 0x0a, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x24,
			.mask = 0x38,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(61),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_4G,
					.value = 0x01,
					.gain = IIO_G_TO_M_S_2(122),
				पूर्ण,
				[2] = अणु
					.num = ST_ACCEL_FS_AVL_6G,
					.value = 0x02,
					.gain = IIO_G_TO_M_S_2(183),
				पूर्ण,
				[3] = अणु
					.num = ST_ACCEL_FS_AVL_8G,
					.value = 0x03,
					.gain = IIO_G_TO_M_S_2(244),
				पूर्ण,
				[4] = अणु
					.num = ST_ACCEL_FS_AVL_16G,
					.value = 0x04,
					.gain = IIO_G_TO_M_S_2(732),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x20,
			.mask = 0x08,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x23,
				.mask = 0x80,
			पूर्ण,
			.addr_ihl = 0x23,
			.mask_ihl = 0x40,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
			.ig1 = अणु
				.en_addr = 0x23,
				.en_mask = 0x08,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x24,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x3a,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LIS3LV02DL_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_12bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0x30, /* DF1 and DF0 */
			.odr_avl = अणु
				अणु .hz = 40, .value = 0x00, पूर्ण,
				अणु .hz = 160, .value = 0x01, पूर्ण,
				अणु .hz = 640, .value = 0x02, पूर्ण,
				अणु .hz = 2560, .value = 0x03, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0xc0,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x21,
			.mask = 0x80,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(1000),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_6G,
					.value = 0x01,
					.gain = IIO_G_TO_M_S_2(3000),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x21,
			.mask = 0x40,
		पूर्ण,
		/*
		 * Data Alignment Setting - needs to be set to get
		 * left-justअगरied data like all other sensors.
		 */
		.das = अणु
			.addr = 0x21,
			.mask = 0x01,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x21,
				.mask = 0x04,
			पूर्ण,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x21,
			.value = BIT(1),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2, /* guess */
	पूर्ण,
	अणु
		.wai = 0x3b,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LIS331DL_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_8bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0x80,
			.odr_avl = अणु
				अणु .hz = 100, .value = 0x00, पूर्ण,
				अणु .hz = 400, .value = 0x01, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x40,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x20,
			.mask = 0x20,
			/*
			 * TODO: check these resulting gain settings, these are
			 * not in the datsheet
			 */
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(18000),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_8G,
					.value = 0x01,
					.gain = IIO_G_TO_M_S_2(72000),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x22,
				.mask = 0x04,
				.addr_od = 0x22,
				.mask_od = 0x40,
			पूर्ण,
			.पूर्णांक2 = अणु
				.addr = 0x22,
				.mask = 0x20,
				.addr_od = 0x22,
				.mask_od = 0x40,
			पूर्ण,
			.addr_ihl = 0x22,
			.mask_ihl = 0x80,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x21,
			.value = BIT(7),
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2, /* guess */
	पूर्ण,
	अणु
		.wai = 0x32,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = H3LIS331DL_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_12bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0x18,
			.odr_avl = अणु
				अणु .hz = 50, .value = 0x00, पूर्ण,
				अणु .hz = 100, .value = 0x01, पूर्ण,
				अणु .hz = 400, .value = 0x02, पूर्ण,
				अणु .hz = 1000, .value = 0x03, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x20,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_100G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(49000),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_200G,
					.value = 0x01,
					.gain = IIO_G_TO_M_S_2(98000),
				पूर्ण,
				[2] = अणु
					.num = ST_ACCEL_FS_AVL_400G,
					.value = 0x03,
					.gain = IIO_G_TO_M_S_2(195000),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x23,
			.mask = 0x80,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x22,
				.mask = 0x02,
			पूर्ण,
			.पूर्णांक2 = अणु
				.addr = 0x22,
				.mask = 0x10,
			पूर्ण,
			.addr_ihl = 0x22,
			.mask_ihl = 0x80,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		/* No WAI रेजिस्टर present */
		.sensors_supported = अणु
			[0] = LIS3L02DQ_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_12bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0x30,
			.odr_avl = अणु
				अणु .hz = 280, .value = 0x00, पूर्ण,
				अणु .hz = 560, .value = 0x01, पूर्ण,
				अणु .hz = 1120, .value = 0x02, पूर्ण,
				अणु .hz = 4480, .value = 0x03, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0xc0,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.gain = IIO_G_TO_M_S_2(488),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		/*
		 * The part has a BDU bit but अगर set the data is never
		 * updated so करोn't set it.
		 */
		.bdu = अणु
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x21,
				.mask = 0x04,
			पूर्ण,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x21,
			.value = BIT(1),
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x33,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LNG2DM_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_8bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x01, पूर्ण,
				अणु .hz = 10, .value = 0x02, पूर्ण,
				अणु .hz = 25, .value = 0x03, पूर्ण,
				अणु .hz = 50, .value = 0x04, पूर्ण,
				अणु .hz = 100, .value = 0x05, पूर्ण,
				अणु .hz = 200, .value = 0x06, पूर्ण,
				अणु .hz = 400, .value = 0x07, पूर्ण,
				अणु .hz = 1600, .value = 0x08, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(15600),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_4G,
					.value = 0x01,
					.gain = IIO_G_TO_M_S_2(31200),
				पूर्ण,
				[2] = अणु
					.num = ST_ACCEL_FS_AVL_8G,
					.value = 0x02,
					.gain = IIO_G_TO_M_S_2(62500),
				पूर्ण,
				[3] = अणु
					.num = ST_ACCEL_FS_AVL_16G,
					.value = 0x03,
					.gain = IIO_G_TO_M_S_2(187500),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x22,
				.mask = 0x10,
			पूर्ण,
			.addr_ihl = 0x25,
			.mask_ihl = 0x02,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x44,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LIS2DW12_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_12bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x01, पूर्ण,
				अणु .hz = 12, .value = 0x02, पूर्ण,
				अणु .hz = 25, .value = 0x03, पूर्ण,
				अणु .hz = 50, .value = 0x04, पूर्ण,
				अणु .hz = 100, .value = 0x05, पूर्ण,
				अणु .hz = 200, .value = 0x06, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.fs = अणु
			.addr = 0x25,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(976),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_4G,
					.value = 0x01,
					.gain = IIO_G_TO_M_S_2(1952),
				पूर्ण,
				[2] = अणु
					.num = ST_ACCEL_FS_AVL_8G,
					.value = 0x02,
					.gain = IIO_G_TO_M_S_2(3904),
				पूर्ण,
				[3] = अणु
					.num = ST_ACCEL_FS_AVL_16G,
					.value = 0x03,
					.gain = IIO_G_TO_M_S_2(7808),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x21,
			.mask = 0x08,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x23,
				.mask = 0x01,
				.addr_od = 0x22,
				.mask_od = 0x20,
			पूर्ण,
			.पूर्णांक2 = अणु
				.addr = 0x24,
				.mask = 0x01,
				.addr_od = 0x22,
				.mask_od = 0x20,
			पूर्ण,
			.addr_ihl = 0x22,
			.mask_ihl = 0x08,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x01,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x21,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x11,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LIS3DHH_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_16bit_channels,
		.odr = अणु
			/* just ODR = 1100Hz available */
			.odr_avl = अणु
				अणु .hz = 1100, .value = 0x00, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x80,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.fs = अणु
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.gain = IIO_G_TO_M_S_2(76),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x20,
			.mask = 0x01,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x21,
				.mask = 0x80,
				.addr_od = 0x23,
				.mask_od = 0x04,
			पूर्ण,
			.पूर्णांक2 = अणु
				.addr = 0x22,
				.mask = 0x80,
				.addr_od = 0x23,
				.mask_od = 0x08,
			पूर्ण,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x33,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LIS2DE12_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_8bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x01, पूर्ण,
				अणु .hz = 10, .value = 0x02, पूर्ण,
				अणु .hz = 25, .value = 0x03, पूर्ण,
				अणु .hz = 50, .value = 0x04, पूर्ण,
				अणु .hz = 100, .value = 0x05, पूर्ण,
				अणु .hz = 200, .value = 0x06, पूर्ण,
				अणु .hz = 400, .value = 0x07, पूर्ण,
				अणु .hz = 1620, .value = 0x08, पूर्ण,
				अणु .hz = 5376, .value = 0x09, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0xf0,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(15600),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_4G,
					.value = 0x01,
					.gain = IIO_G_TO_M_S_2(31200),
				पूर्ण,
				[2] = अणु
					.num = ST_ACCEL_FS_AVL_8G,
					.value = 0x02,
					.gain = IIO_G_TO_M_S_2(62500),
				पूर्ण,
				[3] = अणु
					.num = ST_ACCEL_FS_AVL_16G,
					.value = 0x03,
					.gain = IIO_G_TO_M_S_2(187500),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x22,
				.mask = 0x10,
			पूर्ण,
			.addr_ihl = 0x25,
			.mask_ihl = 0x02,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x41,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LIS2HH12_ACCEL_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_accel_16bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0x70,
			.odr_avl = अणु
				अणु .hz = 10, .value = 0x01, पूर्ण,
				अणु .hz = 50, .value = 0x02, पूर्ण,
				अणु .hz = 100, .value = 0x03, पूर्ण,
				अणु .hz = 200, .value = 0x04, पूर्ण,
				अणु .hz = 400, .value = 0x05, पूर्ण,
				अणु .hz = 800, .value = 0x06, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x70,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_ACCEL_FS_AVL_2G,
					.value = 0x00,
					.gain = IIO_G_TO_M_S_2(61),
				पूर्ण,
				[1] = अणु
					.num = ST_ACCEL_FS_AVL_4G,
					.value = 0x02,
					.gain = IIO_G_TO_M_S_2(122),
				पूर्ण,
				[2] = अणु
					.num = ST_ACCEL_FS_AVL_8G,
					.value = 0x03,
					.gain = IIO_G_TO_M_S_2(244),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x20,
			.mask = 0x08,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x22,
				.mask = 0x01,
			पूर्ण,
			.पूर्णांक2 = अणु
				.addr = 0x25,
				.mask = 0x01,
			पूर्ण,
			.addr_ihl = 0x24,
			.mask_ihl = 0x02,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,

पूर्ण;

अटल पूर्णांक st_accel_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *ch, पूर्णांक *val,
							पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक err;
	काष्ठा st_sensor_data *adata = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		err = st_sensors_पढ़ो_info_raw(indio_dev, ch, val);
		अगर (err < 0)
			जाओ पढ़ो_error;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = adata->current_fullscale->gain / 1000000;
		*val2 = adata->current_fullscale->gain % 1000000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = adata->odr;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण

पढ़ो_error:
	वापस err;
पूर्ण

अटल पूर्णांक st_accel_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक err;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE: अणु
		पूर्णांक gain;

		gain = val * 1000000 + val2;
		err = st_sensors_set_fullscale_by_gain(indio_dev, gain);
		अवरोध;
	पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val2)
			वापस -EINVAL;
		mutex_lock(&indio_dev->mlock);
		err = st_sensors_set_odr(indio_dev, val);
		mutex_unlock(&indio_dev->mlock);
		वापस err;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल ST_SENSORS_DEV_ATTR_SAMP_FREQ_AVAIL();
अटल ST_SENSORS_DEV_ATTR_SCALE_AVAIL(in_accel_scale_available);

अटल काष्ठा attribute *st_accel_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_accel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group st_accel_attribute_group = अणु
	.attrs = st_accel_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info accel_info = अणु
	.attrs = &st_accel_attribute_group,
	.पढ़ो_raw = &st_accel_पढ़ो_raw,
	.ग_लिखो_raw = &st_accel_ग_लिखो_raw,
	.debugfs_reg_access = &st_sensors_debugfs_reg_access,
पूर्ण;

#अगर_घोषित CONFIG_IIO_TRIGGER
अटल स्थिर काष्ठा iio_trigger_ops st_accel_trigger_ops = अणु
	.set_trigger_state = ST_ACCEL_TRIGGER_SET_STATE,
	.validate_device = st_sensors_validate_device,
पूर्ण;
#घोषणा ST_ACCEL_TRIGGER_OPS (&st_accel_trigger_ops)
#अन्यथा
#घोषणा ST_ACCEL_TRIGGER_OPS शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा iio_mount_matrix *
get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
		 स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा st_sensor_data *adata = iio_priv(indio_dev);

	वापस adata->mount_matrix;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info mount_matrix_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_ALL, get_mount_matrix),
	अणु पूर्ण,
पूर्ण;

/* Read ST-specअगरic _ONT orientation data from ACPI and generate an
 * appropriate mount matrix.
 */
अटल पूर्णांक apply_acpi_orientation(काष्ठा iio_dev *indio_dev,
				  काष्ठा iio_chan_spec *channels)
अणु
	काष्ठा st_sensor_data *adata = iio_priv(indio_dev);
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	काष्ठा acpi_device *adev;
	जोड़ acpi_object *ont;
	जोड़ acpi_object *elements;
	acpi_status status;
	पूर्णांक ret = -EINVAL;
	अचिन्हित पूर्णांक val;
	पूर्णांक i, j;
	पूर्णांक final_ont[3][3] = अणु अणु 0 पूर्ण, पूर्ण;

	/* For some reason, ST's _ONT translation करोes not apply directly
	 * to the data पढ़ो from the sensor. Another translation must be
	 * perक्रमmed first, as described by the matrix below. Perhaps
	 * ST required this specअगरic translation क्रम the first product
	 * where the device was mounted?
	 */
	स्थिर पूर्णांक शेष_ont[3][3] = अणु
		अणु  0,  1,  0 पूर्ण,
		अणु -1,  0,  0 पूर्ण,
		अणु  0,  0, -1 पूर्ण,
	पूर्ण;


	adev = ACPI_COMPANION(adata->dev);
	अगर (!adev)
		वापस 0;

	/* Read _ONT data, which should be a package of 6 पूर्णांकegers. */
	status = acpi_evaluate_object(adev->handle, "_ONT", शून्य, &buffer);
	अगर (status == AE_NOT_FOUND) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (ACPI_FAILURE(status)) अणु
		dev_warn(&indio_dev->dev, "failed to execute _ONT: %d\n",
			 status);
		वापस status;
	पूर्ण

	ont = buffer.poपूर्णांकer;
	अगर (ont->type != ACPI_TYPE_PACKAGE || ont->package.count != 6)
		जाओ out;

	/* The first 3 पूर्णांकegers provide axis order inक्रमmation.
	 * e.g. 0 1 2 would indicate normal X,Y,Z ordering.
	 * e.g. 1 0 2 indicates that data arrives in order Y,X,Z.
	 */
	elements = ont->package.elements;
	क्रम (i = 0; i < 3; i++) अणु
		अगर (elements[i].type != ACPI_TYPE_INTEGER)
			जाओ out;

		val = elements[i].पूर्णांकeger.value;
		अगर (val > 2)
			जाओ out;

		/* Aव्योमing full matrix multiplication, we simply reorder the
		 * columns in the शेष_ont matrix according to the
		 * ordering provided by _ONT.
		 */
		final_ont[0][i] = शेष_ont[0][val];
		final_ont[1][i] = शेष_ont[1][val];
		final_ont[2][i] = शेष_ont[2][val];
	पूर्ण

	/* The final 3 पूर्णांकegers provide sign flip inक्रमmation.
	 * 0 means no change, 1 means flip.
	 * e.g. 0 0 1 means that Z data should be sign-flipped.
	 * This is applied after the axis reordering from above.
	 */
	elements += 3;
	क्रम (i = 0; i < 3; i++) अणु
		अगर (elements[i].type != ACPI_TYPE_INTEGER)
			जाओ out;

		val = elements[i].पूर्णांकeger.value;
		अगर (val != 0 && val != 1)
			जाओ out;
		अगर (!val)
			जारी;

		/* Flip the values in the indicated column */
		final_ont[0][i] *= -1;
		final_ont[1][i] *= -1;
		final_ont[2][i] *= -1;
	पूर्ण

	/* Convert our पूर्णांकeger matrix to a string-based iio_mount_matrix */
	adata->mount_matrix = devm_kदो_स्मृति(&indio_dev->dev,
					   माप(*adata->mount_matrix),
					   GFP_KERNEL);
	अगर (!adata->mount_matrix) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		क्रम (j = 0; j < 3; j++) अणु
			पूर्णांक matrix_val = final_ont[i][j];
			अक्षर *str_value;

			चयन (matrix_val) अणु
			हाल -1:
				str_value = "-1";
				अवरोध;
			हाल 0:
				str_value = "0";
				अवरोध;
			हाल 1:
				str_value = "1";
				अवरोध;
			शेष:
				जाओ out;
			पूर्ण
			adata->mount_matrix->rotation[i * 3 + j] = str_value;
		पूर्ण
	पूर्ण

	/* Expose the mount matrix via ext_info */
	क्रम (i = 0; i < indio_dev->num_channels; i++)
		channels[i].ext_info = mount_matrix_ext_info;

	ret = 0;
	dev_info(&indio_dev->dev, "computed mount matrix from ACPI\n");

out:
	kमुक्त(buffer.poपूर्णांकer);
	वापस ret;
पूर्ण
#अन्यथा /* !CONFIG_ACPI */
अटल पूर्णांक apply_acpi_orientation(काष्ठा iio_dev *indio_dev,
				  काष्ठा iio_chan_spec *channels)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * st_accel_get_settings() - get sensor settings from device name
 * @name: device name buffer reference.
 *
 * Return: valid reference on success, शून्य otherwise.
 */
स्थिर काष्ठा st_sensor_settings *st_accel_get_settings(स्थिर अक्षर *name)
अणु
	पूर्णांक index = st_sensors_get_settings_index(name,
					st_accel_sensors_settings,
					ARRAY_SIZE(st_accel_sensors_settings));
	अगर (index < 0)
		वापस शून्य;

	वापस &st_accel_sensors_settings[index];
पूर्ण
EXPORT_SYMBOL(st_accel_get_settings);

पूर्णांक st_accel_common_probe(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *adata = iio_priv(indio_dev);
	काष्ठा st_sensors_platक्रमm_data *pdata = dev_get_platdata(adata->dev);
	काष्ठा iio_chan_spec *channels;
	माप_प्रकार channels_size;
	पूर्णांक err;

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &accel_info;

	err = st_sensors_घातer_enable(indio_dev);
	अगर (err)
		वापस err;

	err = st_sensors_verअगरy_id(indio_dev);
	अगर (err < 0)
		जाओ st_accel_घातer_off;

	adata->num_data_channels = ST_ACCEL_NUMBER_DATA_CHANNELS;
	indio_dev->num_channels = ST_SENSORS_NUMBER_ALL_CHANNELS;

	channels_size = indio_dev->num_channels * माप(काष्ठा iio_chan_spec);
	channels = devm_kmemdup(&indio_dev->dev,
				adata->sensor_settings->ch,
				channels_size, GFP_KERNEL);
	अगर (!channels) अणु
		err = -ENOMEM;
		जाओ st_accel_घातer_off;
	पूर्ण

	अगर (apply_acpi_orientation(indio_dev, channels))
		dev_warn(&indio_dev->dev,
			 "failed to apply ACPI orientation data: %d\n", err);

	indio_dev->channels = channels;
	adata->current_fullscale = &adata->sensor_settings->fs.fs_avl[0];
	adata->odr = adata->sensor_settings->odr.odr_avl[0].hz;

	अगर (!pdata)
		pdata = (काष्ठा st_sensors_platक्रमm_data *)&शेष_accel_pdata;

	err = st_sensors_init_sensor(indio_dev, pdata);
	अगर (err < 0)
		जाओ st_accel_घातer_off;

	err = st_accel_allocate_ring(indio_dev);
	अगर (err < 0)
		जाओ st_accel_घातer_off;

	अगर (adata->irq > 0) अणु
		err = st_sensors_allocate_trigger(indio_dev,
						 ST_ACCEL_TRIGGER_OPS);
		अगर (err < 0)
			जाओ st_accel_probe_trigger_error;
	पूर्ण

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err)
		जाओ st_accel_device_रेजिस्टर_error;

	dev_info(&indio_dev->dev, "registered accelerometer %s\n",
		 indio_dev->name);

	वापस 0;

st_accel_device_रेजिस्टर_error:
	अगर (adata->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);
st_accel_probe_trigger_error:
	st_accel_deallocate_ring(indio_dev);
st_accel_घातer_off:
	st_sensors_घातer_disable(indio_dev);

	वापस err;
पूर्ण
EXPORT_SYMBOL(st_accel_common_probe);

व्योम st_accel_common_हटाओ(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *adata = iio_priv(indio_dev);

	st_sensors_घातer_disable(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (adata->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);

	st_accel_deallocate_ring(indio_dev);
पूर्ण
EXPORT_SYMBOL(st_accel_common_हटाओ);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics accelerometers driver");
MODULE_LICENSE("GPL v2");
