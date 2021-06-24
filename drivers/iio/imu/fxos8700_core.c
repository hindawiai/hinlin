<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FXOS8700 - NXP IMU (accelerometer plus magnetometer)
 *
 * IIO core driver क्रम FXOS8700, with support क्रम I2C/SPI busses
 *
 * TODO: Buffer, trigger, and IRQ support
 */
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश "fxos8700.h"

/* Register Definitions */
#घोषणा FXOS8700_STATUS             0x00
#घोषणा FXOS8700_OUT_X_MSB          0x01
#घोषणा FXOS8700_OUT_X_LSB          0x02
#घोषणा FXOS8700_OUT_Y_MSB          0x03
#घोषणा FXOS8700_OUT_Y_LSB          0x04
#घोषणा FXOS8700_OUT_Z_MSB          0x05
#घोषणा FXOS8700_OUT_Z_LSB          0x06
#घोषणा FXOS8700_F_SETUP            0x09
#घोषणा FXOS8700_TRIG_CFG           0x0a
#घोषणा FXOS8700_SYSMOD             0x0b
#घोषणा FXOS8700_INT_SOURCE         0x0c
#घोषणा FXOS8700_WHO_AM_I           0x0d
#घोषणा FXOS8700_XYZ_DATA_CFG       0x0e
#घोषणा FXOS8700_HP_FILTER_CUTOFF   0x0f
#घोषणा FXOS8700_PL_STATUS          0x10
#घोषणा FXOS8700_PL_CFG             0x11
#घोषणा FXOS8700_PL_COUNT           0x12
#घोषणा FXOS8700_PL_BF_ZCOMP        0x13
#घोषणा FXOS8700_PL_THS_REG         0x14
#घोषणा FXOS8700_A_FFMT_CFG         0x15
#घोषणा FXOS8700_A_FFMT_SRC         0x16
#घोषणा FXOS8700_A_FFMT_THS         0x17
#घोषणा FXOS8700_A_FFMT_COUNT       0x18
#घोषणा FXOS8700_TRANSIENT_CFG      0x1d
#घोषणा FXOS8700_TRANSIENT_SRC      0x1e
#घोषणा FXOS8700_TRANSIENT_THS      0x1f
#घोषणा FXOS8700_TRANSIENT_COUNT    0x20
#घोषणा FXOS8700_PULSE_CFG          0x21
#घोषणा FXOS8700_PULSE_SRC          0x22
#घोषणा FXOS8700_PULSE_THSX         0x23
#घोषणा FXOS8700_PULSE_THSY         0x24
#घोषणा FXOS8700_PULSE_THSZ         0x25
#घोषणा FXOS8700_PULSE_TMLT         0x26
#घोषणा FXOS8700_PULSE_LTCY         0x27
#घोषणा FXOS8700_PULSE_WIND         0x28
#घोषणा FXOS8700_ASLP_COUNT         0x29
#घोषणा FXOS8700_CTRL_REG1          0x2a
#घोषणा FXOS8700_CTRL_REG2          0x2b
#घोषणा FXOS8700_CTRL_REG3          0x2c
#घोषणा FXOS8700_CTRL_REG4          0x2d
#घोषणा FXOS8700_CTRL_REG5          0x2e
#घोषणा FXOS8700_OFF_X              0x2f
#घोषणा FXOS8700_OFF_Y              0x30
#घोषणा FXOS8700_OFF_Z              0x31
#घोषणा FXOS8700_M_DR_STATUS        0x32
#घोषणा FXOS8700_M_OUT_X_MSB        0x33
#घोषणा FXOS8700_M_OUT_X_LSB        0x34
#घोषणा FXOS8700_M_OUT_Y_MSB        0x35
#घोषणा FXOS8700_M_OUT_Y_LSB        0x36
#घोषणा FXOS8700_M_OUT_Z_MSB        0x37
#घोषणा FXOS8700_M_OUT_Z_LSB        0x38
#घोषणा FXOS8700_CMP_X_MSB          0x39
#घोषणा FXOS8700_CMP_X_LSB          0x3a
#घोषणा FXOS8700_CMP_Y_MSB          0x3b
#घोषणा FXOS8700_CMP_Y_LSB          0x3c
#घोषणा FXOS8700_CMP_Z_MSB          0x3d
#घोषणा FXOS8700_CMP_Z_LSB          0x3e
#घोषणा FXOS8700_M_OFF_X_MSB        0x3f
#घोषणा FXOS8700_M_OFF_X_LSB        0x40
#घोषणा FXOS8700_M_OFF_Y_MSB        0x41
#घोषणा FXOS8700_M_OFF_Y_LSB        0x42
#घोषणा FXOS8700_M_OFF_Z_MSB        0x43
#घोषणा FXOS8700_M_OFF_Z_LSB        0x44
#घोषणा FXOS8700_MAX_X_MSB          0x45
#घोषणा FXOS8700_MAX_X_LSB          0x46
#घोषणा FXOS8700_MAX_Y_MSB          0x47
#घोषणा FXOS8700_MAX_Y_LSB          0x48
#घोषणा FXOS8700_MAX_Z_MSB          0x49
#घोषणा FXOS8700_MAX_Z_LSB          0x4a
#घोषणा FXOS8700_MIN_X_MSB          0x4b
#घोषणा FXOS8700_MIN_X_LSB          0x4c
#घोषणा FXOS8700_MIN_Y_MSB          0x4d
#घोषणा FXOS8700_MIN_Y_LSB          0x4e
#घोषणा FXOS8700_MIN_Z_MSB          0x4f
#घोषणा FXOS8700_MIN_Z_LSB          0x50
#घोषणा FXOS8700_TEMP               0x51
#घोषणा FXOS8700_M_THS_CFG          0x52
#घोषणा FXOS8700_M_THS_SRC          0x53
#घोषणा FXOS8700_M_THS_X_MSB        0x54
#घोषणा FXOS8700_M_THS_X_LSB        0x55
#घोषणा FXOS8700_M_THS_Y_MSB        0x56
#घोषणा FXOS8700_M_THS_Y_LSB        0x57
#घोषणा FXOS8700_M_THS_Z_MSB        0x58
#घोषणा FXOS8700_M_THS_Z_LSB        0x59
#घोषणा FXOS8700_M_THS_COUNT        0x5a
#घोषणा FXOS8700_M_CTRL_REG1        0x5b
#घोषणा FXOS8700_M_CTRL_REG2        0x5c
#घोषणा FXOS8700_M_CTRL_REG3        0x5d
#घोषणा FXOS8700_M_INT_SRC          0x5e
#घोषणा FXOS8700_A_VECM_CFG         0x5f
#घोषणा FXOS8700_A_VECM_THS_MSB     0x60
#घोषणा FXOS8700_A_VECM_THS_LSB     0x61
#घोषणा FXOS8700_A_VECM_CNT         0x62
#घोषणा FXOS8700_A_VECM_INITX_MSB   0x63
#घोषणा FXOS8700_A_VECM_INITX_LSB   0x64
#घोषणा FXOS8700_A_VECM_INITY_MSB   0x65
#घोषणा FXOS8700_A_VECM_INITY_LSB   0x66
#घोषणा FXOS8700_A_VECM_INITZ_MSB   0x67
#घोषणा FXOS8700_A_VECM_INITZ_LSB   0x68
#घोषणा FXOS8700_M_VECM_CFG         0x69
#घोषणा FXOS8700_M_VECM_THS_MSB     0x6a
#घोषणा FXOS8700_M_VECM_THS_LSB     0x6b
#घोषणा FXOS8700_M_VECM_CNT         0x6c
#घोषणा FXOS8700_M_VECM_INITX_MSB   0x6d
#घोषणा FXOS8700_M_VECM_INITX_LSB   0x6e
#घोषणा FXOS8700_M_VECM_INITY_MSB   0x6f
#घोषणा FXOS8700_M_VECM_INITY_LSB   0x70
#घोषणा FXOS8700_M_VECM_INITZ_MSB   0x71
#घोषणा FXOS8700_M_VECM_INITZ_LSB   0x72
#घोषणा FXOS8700_A_FFMT_THS_X_MSB   0x73
#घोषणा FXOS8700_A_FFMT_THS_X_LSB   0x74
#घोषणा FXOS8700_A_FFMT_THS_Y_MSB   0x75
#घोषणा FXOS8700_A_FFMT_THS_Y_LSB   0x76
#घोषणा FXOS8700_A_FFMT_THS_Z_MSB   0x77
#घोषणा FXOS8700_A_FFMT_THS_Z_LSB   0x78
#घोषणा FXOS8700_A_TRAN_INIT_MSB    0x79
#घोषणा FXOS8700_A_TRAN_INIT_LSB_X  0x7a
#घोषणा FXOS8700_A_TRAN_INIT_LSB_Y  0x7b
#घोषणा FXOS8700_A_TRAN_INIT_LSB_Z  0x7d
#घोषणा FXOS8700_TM_NVM_LOCK        0x7e
#घोषणा FXOS8700_NVM_DATA0_35       0x80
#घोषणा FXOS8700_NVM_DATA_BNK3      0xa4
#घोषणा FXOS8700_NVM_DATA_BNK2      0xa5
#घोषणा FXOS8700_NVM_DATA_BNK1      0xa6
#घोषणा FXOS8700_NVM_DATA_BNK0      0xa7

/* Bit definitions क्रम FXOS8700_CTRL_REG1 */
#घोषणा FXOS8700_CTRL_ODR_MSK       0x38
#घोषणा FXOS8700_CTRL_ODR_MAX       0x00
#घोषणा FXOS8700_CTRL_ODR_MIN       GENMASK(4, 3)

/* Bit definitions क्रम FXOS8700_M_CTRL_REG1 */
#घोषणा FXOS8700_HMS_MASK           GENMASK(1, 0)
#घोषणा FXOS8700_OS_MASK            GENMASK(4, 2)

/* Bit definitions क्रम FXOS8700_M_CTRL_REG2 */
#घोषणा FXOS8700_MAXMIN_RST         BIT(2)
#घोषणा FXOS8700_MAXMIN_DIS_THS     BIT(3)
#घोषणा FXOS8700_MAXMIN_DIS         BIT(4)

#घोषणा FXOS8700_ACTIVE             0x01
#घोषणा FXOS8700_ACTIVE_MIN_USLEEP  4000 /* from table 6 in datasheet */

#घोषणा FXOS8700_DEVICE_ID          0xC7
#घोषणा FXOS8700_PRE_DEVICE_ID      0xC4
#घोषणा FXOS8700_DATA_BUF_SIZE      3

काष्ठा fxos8700_data अणु
	काष्ठा regmap *regmap;
	काष्ठा iio_trigger *trig;
	__be16 buf[FXOS8700_DATA_BUF_SIZE] ____cacheline_aligned;
पूर्ण;

/* Regmap info */
अटल स्थिर काष्ठा regmap_range पढ़ो_range[] = अणु
	अणु
		.range_min = FXOS8700_STATUS,
		.range_max = FXOS8700_A_FFMT_COUNT,
	पूर्ण, अणु
		.range_min = FXOS8700_TRANSIENT_CFG,
		.range_max = FXOS8700_A_FFMT_THS_Z_LSB,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range ग_लिखो_range[] = अणु
	अणु
		.range_min = FXOS8700_F_SETUP,
		.range_max = FXOS8700_TRIG_CFG,
	पूर्ण, अणु
		.range_min = FXOS8700_XYZ_DATA_CFG,
		.range_max = FXOS8700_HP_FILTER_CUTOFF,
	पूर्ण, अणु
		.range_min = FXOS8700_PL_CFG,
		.range_max = FXOS8700_A_FFMT_CFG,
	पूर्ण, अणु
		.range_min = FXOS8700_A_FFMT_THS,
		.range_max = FXOS8700_TRANSIENT_CFG,
	पूर्ण, अणु
		.range_min = FXOS8700_TRANSIENT_THS,
		.range_max = FXOS8700_PULSE_CFG,
	पूर्ण, अणु
		.range_min = FXOS8700_PULSE_THSX,
		.range_max = FXOS8700_OFF_Z,
	पूर्ण, अणु
		.range_min = FXOS8700_M_OFF_X_MSB,
		.range_max = FXOS8700_M_OFF_Z_LSB,
	पूर्ण, अणु
		.range_min = FXOS8700_M_THS_CFG,
		.range_max = FXOS8700_M_THS_CFG,
	पूर्ण, अणु
		.range_min = FXOS8700_M_THS_X_MSB,
		.range_max = FXOS8700_M_CTRL_REG3,
	पूर्ण, अणु
		.range_min = FXOS8700_A_VECM_CFG,
		.range_max = FXOS8700_A_FFMT_THS_Z_LSB,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table driver_पढ़ो_table = अणु
	.yes_ranges =   पढ़ो_range,
	.n_yes_ranges = ARRAY_SIZE(पढ़ो_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table driver_ग_लिखो_table = अणु
	.yes_ranges =   ग_लिखो_range,
	.n_yes_ranges = ARRAY_SIZE(ग_लिखो_range),
पूर्ण;

स्थिर काष्ठा regmap_config fxos8700_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = FXOS8700_NVM_DATA_BNK0,
	.rd_table = &driver_पढ़ो_table,
	.wr_table = &driver_ग_लिखो_table,
पूर्ण;
EXPORT_SYMBOL(fxos8700_regmap_config);

#घोषणा FXOS8700_CHANNEL(_type, _axis) अणु			\
	.type = _type,						\
	.modअगरied = 1,						\
	.channel2 = IIO_MOD_##_axis,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |  \
		BIT(IIO_CHAN_INFO_SAMP_FREQ),			\
पूर्ण

क्रमागत fxos8700_accel_scale_bits अणु
	MODE_2G = 0,
	MODE_4G,
	MODE_8G,
पूर्ण;

/* scan indexes follow DATA रेजिस्टर order */
क्रमागत fxos8700_scan_axis अणु
	FXOS8700_SCAN_ACCEL_X = 0,
	FXOS8700_SCAN_ACCEL_Y,
	FXOS8700_SCAN_ACCEL_Z,
	FXOS8700_SCAN_MAGN_X,
	FXOS8700_SCAN_MAGN_Y,
	FXOS8700_SCAN_MAGN_Z,
	FXOS8700_SCAN_RHALL,
	FXOS8700_SCAN_TIMESTAMP,
पूर्ण;

क्रमागत fxos8700_sensor अणु
	FXOS8700_ACCEL	= 0,
	FXOS8700_MAGN,
	FXOS8700_NUM_SENSORS /* must be last */
पूर्ण;

क्रमागत fxos8700_पूर्णांक_pin अणु
	FXOS8700_PIN_INT1,
	FXOS8700_PIN_INT2
पूर्ण;

काष्ठा fxos8700_scale अणु
	u8 bits;
	पूर्णांक uscale;
पूर्ण;

काष्ठा fxos8700_odr अणु
	u8 bits;
	पूर्णांक odr;
	पूर्णांक uodr;
पूर्ण;

अटल स्थिर काष्ठा fxos8700_scale fxos8700_accel_scale[] = अणु
	अणु MODE_2G, 244पूर्ण,
	अणु MODE_4G, 488पूर्ण,
	अणु MODE_8G, 976पूर्ण,
पूर्ण;

/*
 * Accellerometer and magnetometer have the same ODR options, set in the
 * CTRL_REG1 रेजिस्टर. ODR is halved when using both sensors at once in
 * hybrid mode.
 */
अटल स्थिर काष्ठा fxos8700_odr fxos8700_odr[] = अणु
	अणु0x00, 800, 0पूर्ण,
	अणु0x01, 400, 0पूर्ण,
	अणु0x02, 200, 0पूर्ण,
	अणु0x03, 100, 0पूर्ण,
	अणु0x04, 50, 0पूर्ण,
	अणु0x05, 12, 500000पूर्ण,
	अणु0x06, 6, 250000पूर्ण,
	अणु0x07, 1, 562500पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec fxos8700_channels[] = अणु
	FXOS8700_CHANNEL(IIO_ACCEL, X),
	FXOS8700_CHANNEL(IIO_ACCEL, Y),
	FXOS8700_CHANNEL(IIO_ACCEL, Z),
	FXOS8700_CHANNEL(IIO_MAGN, X),
	FXOS8700_CHANNEL(IIO_MAGN, Y),
	FXOS8700_CHANNEL(IIO_MAGN, Z),
	IIO_CHAN_SOFT_TIMESTAMP(FXOS8700_SCAN_TIMESTAMP),
पूर्ण;

अटल क्रमागत fxos8700_sensor fxos8700_to_sensor(क्रमागत iio_chan_type iio_type)
अणु
	चयन (iio_type) अणु
	हाल IIO_ACCEL:
		वापस FXOS8700_ACCEL;
	हाल IIO_ANGL_VEL:
		वापस FXOS8700_MAGN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक fxos8700_set_active_mode(काष्ठा fxos8700_data *data,
				    क्रमागत fxos8700_sensor t, bool mode)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, FXOS8700_CTRL_REG1, mode);
	अगर (ret)
		वापस ret;

	usleep_range(FXOS8700_ACTIVE_MIN_USLEEP,
		     FXOS8700_ACTIVE_MIN_USLEEP + 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक fxos8700_set_scale(काष्ठा fxos8700_data *data,
			      क्रमागत fxos8700_sensor t, पूर्णांक uscale)
अणु
	पूर्णांक i;
	अटल स्थिर पूर्णांक scale_num = ARRAY_SIZE(fxos8700_accel_scale);
	काष्ठा device *dev = regmap_get_device(data->regmap);

	अगर (t == FXOS8700_MAGN) अणु
		dev_err(dev, "Magnetometer scale is locked at 1200uT\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < scale_num; i++)
		अगर (fxos8700_accel_scale[i].uscale == uscale)
			अवरोध;

	अगर (i == scale_num)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(data->regmap, FXOS8700_XYZ_DATA_CFG,
			    fxos8700_accel_scale[i].bits);
पूर्ण

अटल पूर्णांक fxos8700_get_scale(काष्ठा fxos8700_data *data,
			      क्रमागत fxos8700_sensor t, पूर्णांक *uscale)
अणु
	पूर्णांक i, ret, val;
	अटल स्थिर पूर्णांक scale_num = ARRAY_SIZE(fxos8700_accel_scale);

	अगर (t == FXOS8700_MAGN) अणु
		*uscale = 1200; /* Magnetometer is locked at 1200uT */
		वापस 0;
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, FXOS8700_XYZ_DATA_CFG, &val);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < scale_num; i++) अणु
		अगर (fxos8700_accel_scale[i].bits == (val & 0x3)) अणु
			*uscale = fxos8700_accel_scale[i].uscale;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fxos8700_get_data(काष्ठा fxos8700_data *data, पूर्णांक chan_type,
			     पूर्णांक axis, पूर्णांक *val)
अणु
	u8 base, reg;
	पूर्णांक ret;
	क्रमागत fxos8700_sensor type = fxos8700_to_sensor(chan_type);

	base = type ? FXOS8700_OUT_X_MSB : FXOS8700_M_OUT_X_MSB;

	/* Block पढ़ो 6 bytes of device output रेजिस्टरs to aव्योम data loss */
	ret = regmap_bulk_पढ़ो(data->regmap, base, data->buf,
			       FXOS8700_DATA_BUF_SIZE);
	अगर (ret)
		वापस ret;

	/* Convert axis to buffer index */
	reg = axis - IIO_MOD_X;

	/* Convert to native endianness */
	*val = sign_extend32(be16_to_cpu(data->buf[reg]), 15);

	वापस 0;
पूर्ण

अटल पूर्णांक fxos8700_set_odr(काष्ठा fxos8700_data *data, क्रमागत fxos8700_sensor t,
			    पूर्णांक odr, पूर्णांक uodr)
अणु
	पूर्णांक i, ret, val;
	bool active_mode;
	अटल स्थिर पूर्णांक odr_num = ARRAY_SIZE(fxos8700_odr);

	ret = regmap_पढ़ो(data->regmap, FXOS8700_CTRL_REG1, &val);
	अगर (ret)
		वापस ret;

	active_mode = val & FXOS8700_ACTIVE;

	अगर (active_mode) अणु
		/*
		 * The device must be in standby mode to change any of the
		 * other fields within CTRL_REG1
		 */
		ret = regmap_ग_लिखो(data->regmap, FXOS8700_CTRL_REG1,
				   val & ~FXOS8700_ACTIVE);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < odr_num; i++)
		अगर (fxos8700_odr[i].odr == odr && fxos8700_odr[i].uodr == uodr)
			अवरोध;

	अगर (i >= odr_num)
		वापस -EINVAL;

	वापस regmap_update_bits(data->regmap,
				  FXOS8700_CTRL_REG1,
				  FXOS8700_CTRL_ODR_MSK + FXOS8700_ACTIVE,
				  fxos8700_odr[i].bits << 3 | active_mode);
पूर्ण

अटल पूर्णांक fxos8700_get_odr(काष्ठा fxos8700_data *data, क्रमागत fxos8700_sensor t,
			    पूर्णांक *odr, पूर्णांक *uodr)
अणु
	पूर्णांक i, val, ret;
	अटल स्थिर पूर्णांक odr_num = ARRAY_SIZE(fxos8700_odr);

	ret = regmap_पढ़ो(data->regmap, FXOS8700_CTRL_REG1, &val);
	अगर (ret)
		वापस ret;

	val &= FXOS8700_CTRL_ODR_MSK;

	क्रम (i = 0; i < odr_num; i++)
		अगर (val == fxos8700_odr[i].bits)
			अवरोध;

	अगर (i >= odr_num)
		वापस -EINVAL;

	*odr = fxos8700_odr[i].odr;
	*uodr = fxos8700_odr[i].uodr;

	वापस 0;
पूर्ण

अटल पूर्णांक fxos8700_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा fxos8700_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = fxos8700_get_data(data, chan->type, chan->channel2, val);
		अगर (ret)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		ret = fxos8700_get_scale(data, fxos8700_to_sensor(chan->type),
					 val2);
		वापस ret ? ret : IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = fxos8700_get_odr(data, fxos8700_to_sensor(chan->type),
				       val, val2);
		वापस ret ? ret : IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक fxos8700_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा fxos8700_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		वापस fxos8700_set_scale(data, fxos8700_to_sensor(chan->type),
					  val2);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस fxos8700_set_odr(data, fxos8700_to_sensor(chan->type),
					val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल IIO_CONST_ATTR(in_accel_sampling_frequency_available,
		      "1.5625 6.25 12.5 50 100 200 400 800");
अटल IIO_CONST_ATTR(in_magn_sampling_frequency_available,
		      "1.5625 6.25 12.5 50 100 200 400 800");
अटल IIO_CONST_ATTR(in_accel_scale_available, "0.000244 0.000488 0.000976");
अटल IIO_CONST_ATTR(in_magn_scale_available, "0.000001200");

अटल काष्ठा attribute *fxos8700_attrs[] = अणु
	&iio_स्थिर_attr_in_accel_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_magn_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_accel_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_magn_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group fxos8700_attrs_group = अणु
	.attrs = fxos8700_attrs,
पूर्ण;

अटल स्थिर काष्ठा iio_info fxos8700_info = अणु
	.पढ़ो_raw = fxos8700_पढ़ो_raw,
	.ग_लिखो_raw = fxos8700_ग_लिखो_raw,
	.attrs = &fxos8700_attrs_group,
पूर्ण;

अटल पूर्णांक fxos8700_chip_init(काष्ठा fxos8700_data *data, bool use_spi)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा device *dev = regmap_get_device(data->regmap);

	ret = regmap_पढ़ो(data->regmap, FXOS8700_WHO_AM_I, &val);
	अगर (ret) अणु
		dev_err(dev, "Error reading chip id\n");
		वापस ret;
	पूर्ण
	अगर (val != FXOS8700_DEVICE_ID && val != FXOS8700_PRE_DEVICE_ID) अणु
		dev_err(dev, "Wrong chip id, got %x expected %x or %x\n",
			val, FXOS8700_DEVICE_ID, FXOS8700_PRE_DEVICE_ID);
		वापस -ENODEV;
	पूर्ण

	ret = fxos8700_set_active_mode(data, FXOS8700_ACCEL, true);
	अगर (ret)
		वापस ret;

	ret = fxos8700_set_active_mode(data, FXOS8700_MAGN, true);
	अगर (ret)
		वापस ret;

	/*
	 * The device must be in standby mode to change any of the other fields
	 * within CTRL_REG1
	 */
	ret = regmap_ग_लिखो(data->regmap, FXOS8700_CTRL_REG1, 0x00);
	अगर (ret)
		वापस ret;

	/* Set max oversample ratio (OSR) and both devices active */
	ret = regmap_ग_लिखो(data->regmap, FXOS8700_M_CTRL_REG1,
			   FXOS8700_HMS_MASK | FXOS8700_OS_MASK);
	अगर (ret)
		वापस ret;

	/* Disable and rst min/max measurements & threshold */
	ret = regmap_ग_लिखो(data->regmap, FXOS8700_M_CTRL_REG2,
			   FXOS8700_MAXMIN_RST | FXOS8700_MAXMIN_DIS_THS |
			   FXOS8700_MAXMIN_DIS);
	अगर (ret)
		वापस ret;

	/* Max ODR (800Hz inभागidual or 400Hz hybrid), active mode */
	ret = regmap_ग_लिखो(data->regmap, FXOS8700_CTRL_REG1,
			   FXOS8700_CTRL_ODR_MAX | FXOS8700_ACTIVE);
	अगर (ret)
		वापस ret;

	/* Set क्रम max full-scale range (+/-8G) */
	वापस regmap_ग_लिखो(data->regmap, FXOS8700_XYZ_DATA_CFG, MODE_8G);
पूर्ण

अटल व्योम fxos8700_chip_uninit(व्योम *data)
अणु
	काष्ठा fxos8700_data *fxos8700_data = data;

	fxos8700_set_active_mode(fxos8700_data, FXOS8700_ACCEL, false);
	fxos8700_set_active_mode(fxos8700_data, FXOS8700_MAGN, false);
पूर्ण

पूर्णांक fxos8700_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
			स्थिर अक्षर *name, bool use_spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा fxos8700_data *data;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->regmap = regmap;

	ret = fxos8700_chip_init(data, use_spi);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, fxos8700_chip_uninit, data);
	अगर (ret)
		वापस ret;

	indio_dev->channels = fxos8700_channels;
	indio_dev->num_channels = ARRAY_SIZE(fxos8700_channels);
	indio_dev->name = name ? name : "fxos8700";
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &fxos8700_info;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण
EXPORT_SYMBOL_GPL(fxos8700_core_probe);

MODULE_AUTHOR("Robert Jones <rjones@gateworks.com>");
MODULE_DESCRIPTION("FXOS8700 6-Axis Acc and Mag Combo Sensor driver");
MODULE_LICENSE("GPL v2");
