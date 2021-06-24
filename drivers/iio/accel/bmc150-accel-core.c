<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 3-axis accelerometer driver supporting following Bosch-Sensortec chips:
 *  - BMC150
 *  - BMI055
 *  - BMA255
 *  - BMA250E
 *  - BMA222
 *  - BMA222E
 *  - BMA280
 *
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "bmc150-accel.h"

#घोषणा BMC150_ACCEL_DRV_NAME			"bmc150_accel"
#घोषणा BMC150_ACCEL_IRQ_NAME			"bmc150_accel_event"

#घोषणा BMC150_ACCEL_REG_CHIP_ID		0x00

#घोषणा BMC150_ACCEL_REG_INT_STATUS_2		0x0B
#घोषणा BMC150_ACCEL_ANY_MOTION_MASK		0x07
#घोषणा BMC150_ACCEL_ANY_MOTION_BIT_X		BIT(0)
#घोषणा BMC150_ACCEL_ANY_MOTION_BIT_Y		BIT(1)
#घोषणा BMC150_ACCEL_ANY_MOTION_BIT_Z		BIT(2)
#घोषणा BMC150_ACCEL_ANY_MOTION_BIT_SIGN	BIT(3)

#घोषणा BMC150_ACCEL_REG_PMU_LPW		0x11
#घोषणा BMC150_ACCEL_PMU_MODE_MASK		0xE0
#घोषणा BMC150_ACCEL_PMU_MODE_SHIFT		5
#घोषणा BMC150_ACCEL_PMU_BIT_SLEEP_DUR_MASK	0x17
#घोषणा BMC150_ACCEL_PMU_BIT_SLEEP_DUR_SHIFT	1

#घोषणा BMC150_ACCEL_REG_PMU_RANGE		0x0F

#घोषणा BMC150_ACCEL_DEF_RANGE_2G		0x03
#घोषणा BMC150_ACCEL_DEF_RANGE_4G		0x05
#घोषणा BMC150_ACCEL_DEF_RANGE_8G		0x08
#घोषणा BMC150_ACCEL_DEF_RANGE_16G		0x0C

/* Default BW: 125Hz */
#घोषणा BMC150_ACCEL_REG_PMU_BW		0x10
#घोषणा BMC150_ACCEL_DEF_BW			125

#घोषणा BMC150_ACCEL_REG_RESET			0x14
#घोषणा BMC150_ACCEL_RESET_VAL			0xB6

#घोषणा BMC150_ACCEL_REG_INT_MAP_0		0x19
#घोषणा BMC150_ACCEL_INT_MAP_0_BIT_SLOPE	BIT(2)

#घोषणा BMC150_ACCEL_REG_INT_MAP_1		0x1A
#घोषणा BMC150_ACCEL_INT_MAP_1_BIT_DATA		BIT(0)
#घोषणा BMC150_ACCEL_INT_MAP_1_BIT_FWM		BIT(1)
#घोषणा BMC150_ACCEL_INT_MAP_1_BIT_FFULL	BIT(2)

#घोषणा BMC150_ACCEL_REG_INT_RST_LATCH		0x21
#घोषणा BMC150_ACCEL_INT_MODE_LATCH_RESET	0x80
#घोषणा BMC150_ACCEL_INT_MODE_LATCH_INT	0x0F
#घोषणा BMC150_ACCEL_INT_MODE_NON_LATCH_INT	0x00

#घोषणा BMC150_ACCEL_REG_INT_EN_0		0x16
#घोषणा BMC150_ACCEL_INT_EN_BIT_SLP_X		BIT(0)
#घोषणा BMC150_ACCEL_INT_EN_BIT_SLP_Y		BIT(1)
#घोषणा BMC150_ACCEL_INT_EN_BIT_SLP_Z		BIT(2)

#घोषणा BMC150_ACCEL_REG_INT_EN_1		0x17
#घोषणा BMC150_ACCEL_INT_EN_BIT_DATA_EN		BIT(4)
#घोषणा BMC150_ACCEL_INT_EN_BIT_FFULL_EN	BIT(5)
#घोषणा BMC150_ACCEL_INT_EN_BIT_FWM_EN		BIT(6)

#घोषणा BMC150_ACCEL_REG_INT_OUT_CTRL		0x20
#घोषणा BMC150_ACCEL_INT_OUT_CTRL_INT1_LVL	BIT(0)

#घोषणा BMC150_ACCEL_REG_INT_5			0x27
#घोषणा BMC150_ACCEL_SLOPE_DUR_MASK		0x03

#घोषणा BMC150_ACCEL_REG_INT_6			0x28
#घोषणा BMC150_ACCEL_SLOPE_THRES_MASK		0xFF

/* Slope duration in terms of number of samples */
#घोषणा BMC150_ACCEL_DEF_SLOPE_DURATION		1
/* in terms of multiples of g's/LSB, based on range */
#घोषणा BMC150_ACCEL_DEF_SLOPE_THRESHOLD	1

#घोषणा BMC150_ACCEL_REG_XOUT_L		0x02

#घोषणा BMC150_ACCEL_MAX_STARTUP_TIME_MS	100

/* Sleep Duration values */
#घोषणा BMC150_ACCEL_SLEEP_500_MICRO		0x05
#घोषणा BMC150_ACCEL_SLEEP_1_MS		0x06
#घोषणा BMC150_ACCEL_SLEEP_2_MS		0x07
#घोषणा BMC150_ACCEL_SLEEP_4_MS		0x08
#घोषणा BMC150_ACCEL_SLEEP_6_MS		0x09
#घोषणा BMC150_ACCEL_SLEEP_10_MS		0x0A
#घोषणा BMC150_ACCEL_SLEEP_25_MS		0x0B
#घोषणा BMC150_ACCEL_SLEEP_50_MS		0x0C
#घोषणा BMC150_ACCEL_SLEEP_100_MS		0x0D
#घोषणा BMC150_ACCEL_SLEEP_500_MS		0x0E
#घोषणा BMC150_ACCEL_SLEEP_1_SEC		0x0F

#घोषणा BMC150_ACCEL_REG_TEMP			0x08
#घोषणा BMC150_ACCEL_TEMP_CENTER_VAL		23

#घोषणा BMC150_ACCEL_AXIS_TO_REG(axis)	(BMC150_ACCEL_REG_XOUT_L + (axis * 2))
#घोषणा BMC150_AUTO_SUSPEND_DELAY_MS		2000

#घोषणा BMC150_ACCEL_REG_FIFO_STATUS		0x0E
#घोषणा BMC150_ACCEL_REG_FIFO_CONFIG0		0x30
#घोषणा BMC150_ACCEL_REG_FIFO_CONFIG1		0x3E
#घोषणा BMC150_ACCEL_REG_FIFO_DATA		0x3F
#घोषणा BMC150_ACCEL_FIFO_LENGTH		32

क्रमागत bmc150_accel_axis अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX,
पूर्ण;

क्रमागत bmc150_घातer_modes अणु
	BMC150_ACCEL_SLEEP_MODE_NORMAL,
	BMC150_ACCEL_SLEEP_MODE_DEEP_SUSPEND,
	BMC150_ACCEL_SLEEP_MODE_LPM,
	BMC150_ACCEL_SLEEP_MODE_SUSPEND = 0x04,
पूर्ण;

काष्ठा bmc150_scale_info अणु
	पूर्णांक scale;
	u8 reg_range;
पूर्ण;

काष्ठा bmc150_accel_chip_info अणु
	स्थिर अक्षर *name;
	u8 chip_id;
	स्थिर काष्ठा iio_chan_spec *channels;
	पूर्णांक num_channels;
	स्थिर काष्ठा bmc150_scale_info scale_table[4];
पूर्ण;

काष्ठा bmc150_accel_पूर्णांकerrupt अणु
	स्थिर काष्ठा bmc150_accel_पूर्णांकerrupt_info *info;
	atomic_t users;
पूर्ण;

काष्ठा bmc150_accel_trigger अणु
	काष्ठा bmc150_accel_data *data;
	काष्ठा iio_trigger *indio_trig;
	पूर्णांक (*setup)(काष्ठा bmc150_accel_trigger *t, bool state);
	पूर्णांक पूर्णांकr;
	bool enabled;
पूर्ण;

क्रमागत bmc150_accel_पूर्णांकerrupt_id अणु
	BMC150_ACCEL_INT_DATA_READY,
	BMC150_ACCEL_INT_ANY_MOTION,
	BMC150_ACCEL_INT_WATERMARK,
	BMC150_ACCEL_INTERRUPTS,
पूर्ण;

क्रमागत bmc150_accel_trigger_id अणु
	BMC150_ACCEL_TRIGGER_DATA_READY,
	BMC150_ACCEL_TRIGGER_ANY_MOTION,
	BMC150_ACCEL_TRIGGERS,
पूर्ण;

काष्ठा bmc150_accel_data अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data regulators[2];
	काष्ठा bmc150_accel_पूर्णांकerrupt पूर्णांकerrupts[BMC150_ACCEL_INTERRUPTS];
	काष्ठा bmc150_accel_trigger triggers[BMC150_ACCEL_TRIGGERS];
	काष्ठा mutex mutex;
	u8 fअगरo_mode, watermark;
	s16 buffer[8];
	/*
	 * Ensure there is sufficient space and correct alignment क्रम
	 * the बारtamp अगर enabled
	 */
	काष्ठा अणु
		__le16 channels[3];
		s64 ts __aligned(8);
	पूर्ण scan;
	u8 bw_bits;
	u32 slope_dur;
	u32 slope_thres;
	u32 range;
	पूर्णांक ev_enable_state;
	पूर्णांक64_t बारtamp, old_बारtamp; /* Only used in hw fअगरo mode. */
	स्थिर काष्ठा bmc150_accel_chip_info *chip_info;
	काष्ठा i2c_client *second_device;
	काष्ठा iio_mount_matrix orientation;
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	पूर्णांक val2;
	u8 bw_bits;
पूर्ण bmc150_accel_samp_freq_table[] = अणु अणु15, 620000, 0x08पूर्ण,
				     अणु31, 260000, 0x09पूर्ण,
				     अणु62, 500000, 0x0Aपूर्ण,
				     अणु125, 0, 0x0Bपूर्ण,
				     अणु250, 0, 0x0Cपूर्ण,
				     अणु500, 0, 0x0Dपूर्ण,
				     अणु1000, 0, 0x0Eपूर्ण,
				     अणु2000, 0, 0x0Fपूर्ण पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक bw_bits;
	पूर्णांक msec;
पूर्ण bmc150_accel_sample_upd_समय[] = अणु अणु0x08, 64पूर्ण,
				     अणु0x09, 32पूर्ण,
				     अणु0x0A, 16पूर्ण,
				     अणु0x0B, 8पूर्ण,
				     अणु0x0C, 4पूर्ण,
				     अणु0x0D, 2पूर्ण,
				     अणु0x0E, 1पूर्ण,
				     अणु0x0F, 1पूर्ण पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक sleep_dur;
	u8 reg_value;
पूर्ण bmc150_accel_sleep_value_table[] = अणु अणु0, 0पूर्ण,
				       अणु500, BMC150_ACCEL_SLEEP_500_MICROपूर्ण,
				       अणु1000, BMC150_ACCEL_SLEEP_1_MSपूर्ण,
				       अणु2000, BMC150_ACCEL_SLEEP_2_MSपूर्ण,
				       अणु4000, BMC150_ACCEL_SLEEP_4_MSपूर्ण,
				       अणु6000, BMC150_ACCEL_SLEEP_6_MSपूर्ण,
				       अणु10000, BMC150_ACCEL_SLEEP_10_MSपूर्ण,
				       अणु25000, BMC150_ACCEL_SLEEP_25_MSपूर्ण,
				       अणु50000, BMC150_ACCEL_SLEEP_50_MSपूर्ण,
				       अणु100000, BMC150_ACCEL_SLEEP_100_MSपूर्ण,
				       अणु500000, BMC150_ACCEL_SLEEP_500_MSपूर्ण,
				       अणु1000000, BMC150_ACCEL_SLEEP_1_SECपूर्ण पूर्ण;

स्थिर काष्ठा regmap_config bmc150_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x3f,
पूर्ण;
EXPORT_SYMBOL_GPL(bmc150_regmap_conf);

अटल पूर्णांक bmc150_accel_set_mode(काष्ठा bmc150_accel_data *data,
				 क्रमागत bmc150_घातer_modes mode,
				 पूर्णांक dur_us)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक i;
	पूर्णांक ret;
	u8 lpw_bits;
	पूर्णांक dur_val = -1;

	अगर (dur_us > 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(bmc150_accel_sleep_value_table);
									 ++i) अणु
			अगर (bmc150_accel_sleep_value_table[i].sleep_dur ==
									dur_us)
				dur_val =
				bmc150_accel_sleep_value_table[i].reg_value;
		पूर्ण
	पूर्ण अन्यथा अणु
		dur_val = 0;
	पूर्ण

	अगर (dur_val < 0)
		वापस -EINVAL;

	lpw_bits = mode << BMC150_ACCEL_PMU_MODE_SHIFT;
	lpw_bits |= (dur_val << BMC150_ACCEL_PMU_BIT_SLEEP_DUR_SHIFT);

	dev_dbg(dev, "Set Mode bits %x\n", lpw_bits);

	ret = regmap_ग_लिखो(data->regmap, BMC150_ACCEL_REG_PMU_LPW, lpw_bits);
	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_pmu_lpw\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_accel_set_bw(काष्ठा bmc150_accel_data *data, पूर्णांक val,
			       पूर्णांक val2)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(bmc150_accel_samp_freq_table); ++i) अणु
		अगर (bmc150_accel_samp_freq_table[i].val == val &&
		    bmc150_accel_samp_freq_table[i].val2 == val2) अणु
			ret = regmap_ग_लिखो(data->regmap,
				BMC150_ACCEL_REG_PMU_BW,
				bmc150_accel_samp_freq_table[i].bw_bits);
			अगर (ret < 0)
				वापस ret;

			data->bw_bits =
				bmc150_accel_samp_freq_table[i].bw_bits;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmc150_accel_update_slope(काष्ठा bmc150_accel_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, BMC150_ACCEL_REG_INT_6,
					data->slope_thres);
	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_int_6\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(data->regmap, BMC150_ACCEL_REG_INT_5,
				 BMC150_ACCEL_SLOPE_DUR_MASK, data->slope_dur);
	अगर (ret < 0) अणु
		dev_err(dev, "Error updating reg_int_5\n");
		वापस ret;
	पूर्ण

	dev_dbg(dev, "%x %x\n", data->slope_thres, data->slope_dur);

	वापस ret;
पूर्ण

अटल पूर्णांक bmc150_accel_any_motion_setup(काष्ठा bmc150_accel_trigger *t,
					 bool state)
अणु
	अगर (state)
		वापस bmc150_accel_update_slope(t->data);

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_accel_get_bw(काष्ठा bmc150_accel_data *data, पूर्णांक *val,
			       पूर्णांक *val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bmc150_accel_samp_freq_table); ++i) अणु
		अगर (bmc150_accel_samp_freq_table[i].bw_bits == data->bw_bits) अणु
			*val = bmc150_accel_samp_freq_table[i].val;
			*val2 = bmc150_accel_samp_freq_table[i].val2;
			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bmc150_accel_get_startup_बार(काष्ठा bmc150_accel_data *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bmc150_accel_sample_upd_समय); ++i) अणु
		अगर (bmc150_accel_sample_upd_समय[i].bw_bits == data->bw_bits)
			वापस bmc150_accel_sample_upd_समय[i].msec;
	पूर्ण

	वापस BMC150_ACCEL_MAX_STARTUP_TIME_MS;
पूर्ण

अटल पूर्णांक bmc150_accel_set_घातer_state(काष्ठा bmc150_accel_data *data, bool on)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(dev);
		ret = pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(dev,
			"Failed: %s for %d\n", __func__, on);
		अगर (on)
			pm_runसमय_put_noidle(dev);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक bmc150_accel_set_घातer_state(काष्ठा bmc150_accel_data *data, bool on)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
/*
 * Support क्रम getting accelerometer inक्रमmation from BOSC0200 ACPI nodes.
 *
 * There are 2 variants of the BOSC0200 ACPI node. Some 2-in-1s with 360 degree
 * hinges declare 2 I2C ACPI-resources क्रम 2 accelerometers, 1 in the display
 * and 1 in the base of the 2-in-1. On these 2-in-1s the ROMS ACPI object
 * contains the mount-matrix क्रम the sensor in the display and ROMK contains
 * the mount-matrix क्रम the sensor in the base. On devices using a single
 * sensor there is a ROTM ACPI object which contains the mount-matrix.
 *
 * Here is an incomplete list of devices known to use 1 of these setups:
 *
 * Yoga devices with 2 accelerometers using ROMS + ROMK क्रम the mount-matrices:
 * Lenovo Thinkpad Yoga 11e 3th gen
 * Lenovo Thinkpad Yoga 11e 4th gen
 *
 * Tablets using a single accelerometer using ROTM क्रम the mount-matrix:
 * Chuwi Hi8 Pro (CWI513)
 * Chuwi Vi8 Plus (CWI519)
 * Chuwi Hi13
 * Irbis TW90
 * Jumper EZpad mini 3
 * Onda V80 plus
 * Predia Basic Tablet
 */
अटल bool bmc150_apply_acpi_orientation(काष्ठा device *dev,
					  काष्ठा iio_mount_matrix *orientation)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	अक्षर *name, *alt_name, *label, *str;
	जोड़ acpi_object *obj, *elements;
	acpi_status status;
	पूर्णांक i, j, val[3];

	अगर (!adev || !acpi_dev_hid_uid_match(adev, "BOSC0200", शून्य))
		वापस false;

	अगर (म_भेद(dev_name(dev), "i2c-BOSC0200:base") == 0) अणु
		alt_name = "ROMK";
		label = "accel-base";
	पूर्ण अन्यथा अणु
		alt_name = "ROMS";
		label = "accel-display";
	पूर्ण

	अगर (acpi_has_method(adev->handle, "ROTM")) अणु
		name = "ROTM";
	पूर्ण अन्यथा अगर (acpi_has_method(adev->handle, alt_name)) अणु
		name = alt_name;
		indio_dev->label = label;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	status = acpi_evaluate_object(adev->handle, name, शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		dev_warn(dev, "Failed to get ACPI mount matrix: %d\n", status);
		वापस false;
	पूर्ण

	obj = buffer.poपूर्णांकer;
	अगर (obj->type != ACPI_TYPE_PACKAGE || obj->package.count != 3)
		जाओ unknown_क्रमmat;

	elements = obj->package.elements;
	क्रम (i = 0; i < 3; i++) अणु
		अगर (elements[i].type != ACPI_TYPE_STRING)
			जाओ unknown_क्रमmat;

		str = elements[i].string.poपूर्णांकer;
		अगर (माला_पूछो(str, "%d %d %d", &val[0], &val[1], &val[2]) != 3)
			जाओ unknown_क्रमmat;

		क्रम (j = 0; j < 3; j++) अणु
			चयन (val[j]) अणु
			हाल -1: str = "-1"; अवरोध;
			हाल 0:  str = "0";  अवरोध;
			हाल 1:  str = "1";  अवरोध;
			शेष: जाओ unknown_क्रमmat;
			पूर्ण
			orientation->rotation[i * 3 + j] = str;
		पूर्ण
	पूर्ण

	kमुक्त(buffer.poपूर्णांकer);
	वापस true;

unknown_क्रमmat:
	dev_warn(dev, "Unknown ACPI mount matrix format, ignoring\n");
	kमुक्त(buffer.poपूर्णांकer);
	वापस false;
पूर्ण
#अन्यथा
अटल bool bmc150_apply_acpi_orientation(काष्ठा device *dev,
					  काष्ठा iio_mount_matrix *orientation)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा bmc150_accel_पूर्णांकerrupt_info अणु
	u8 map_reg;
	u8 map_biपंचांगask;
	u8 en_reg;
	u8 en_biपंचांगask;
पूर्ण bmc150_accel_पूर्णांकerrupts[BMC150_ACCEL_INTERRUPTS] = अणु
	अणु /* data पढ़ोy पूर्णांकerrupt */
		.map_reg = BMC150_ACCEL_REG_INT_MAP_1,
		.map_biपंचांगask = BMC150_ACCEL_INT_MAP_1_BIT_DATA,
		.en_reg = BMC150_ACCEL_REG_INT_EN_1,
		.en_biपंचांगask = BMC150_ACCEL_INT_EN_BIT_DATA_EN,
	पूर्ण,
	अणु  /* motion पूर्णांकerrupt */
		.map_reg = BMC150_ACCEL_REG_INT_MAP_0,
		.map_biपंचांगask = BMC150_ACCEL_INT_MAP_0_BIT_SLOPE,
		.en_reg = BMC150_ACCEL_REG_INT_EN_0,
		.en_biपंचांगask =  BMC150_ACCEL_INT_EN_BIT_SLP_X |
			BMC150_ACCEL_INT_EN_BIT_SLP_Y |
			BMC150_ACCEL_INT_EN_BIT_SLP_Z
	पूर्ण,
	अणु /* fअगरo watermark पूर्णांकerrupt */
		.map_reg = BMC150_ACCEL_REG_INT_MAP_1,
		.map_biपंचांगask = BMC150_ACCEL_INT_MAP_1_BIT_FWM,
		.en_reg = BMC150_ACCEL_REG_INT_EN_1,
		.en_biपंचांगask = BMC150_ACCEL_INT_EN_BIT_FWM_EN,
	पूर्ण,
पूर्ण;

अटल व्योम bmc150_accel_पूर्णांकerrupts_setup(काष्ठा iio_dev *indio_dev,
					  काष्ठा bmc150_accel_data *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BMC150_ACCEL_INTERRUPTS; i++)
		data->पूर्णांकerrupts[i].info = &bmc150_accel_पूर्णांकerrupts[i];
पूर्ण

अटल पूर्णांक bmc150_accel_set_पूर्णांकerrupt(काष्ठा bmc150_accel_data *data, पूर्णांक i,
				      bool state)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	काष्ठा bmc150_accel_पूर्णांकerrupt *पूर्णांकr = &data->पूर्णांकerrupts[i];
	स्थिर काष्ठा bmc150_accel_पूर्णांकerrupt_info *info = पूर्णांकr->info;
	पूर्णांक ret;

	अगर (state) अणु
		अगर (atomic_inc_वापस(&पूर्णांकr->users) > 1)
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (atomic_dec_वापस(&पूर्णांकr->users) > 0)
			वापस 0;
	पूर्ण

	/*
	 * We will expect the enable and disable to करो operation in reverse
	 * order. This will happen here anyway, as our resume operation uses
	 * sync mode runसमय pm calls. The suspend operation will be delayed
	 * by स्वतःsuspend delay.
	 * So the disable operation will still happen in reverse order of
	 * enable operation. When runसमय pm is disabled the mode is always on,
	 * so sequence करोesn't matter.
	 */
	ret = bmc150_accel_set_घातer_state(data, state);
	अगर (ret < 0)
		वापस ret;

	/* map the पूर्णांकerrupt to the appropriate pins */
	ret = regmap_update_bits(data->regmap, info->map_reg, info->map_biपंचांगask,
				 (state ? info->map_biपंचांगask : 0));
	अगर (ret < 0) अणु
		dev_err(dev, "Error updating reg_int_map\n");
		जाओ out_fix_घातer_state;
	पूर्ण

	/* enable/disable the पूर्णांकerrupt */
	ret = regmap_update_bits(data->regmap, info->en_reg, info->en_biपंचांगask,
				 (state ? info->en_biपंचांगask : 0));
	अगर (ret < 0) अणु
		dev_err(dev, "Error updating reg_int_en\n");
		जाओ out_fix_घातer_state;
	पूर्ण

	वापस 0;

out_fix_घातer_state:
	bmc150_accel_set_घातer_state(data, false);
	वापस ret;
पूर्ण

अटल पूर्णांक bmc150_accel_set_scale(काष्ठा bmc150_accel_data *data, पूर्णांक val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(data->chip_info->scale_table); ++i) अणु
		अगर (data->chip_info->scale_table[i].scale == val) अणु
			ret = regmap_ग_लिखो(data->regmap,
				     BMC150_ACCEL_REG_PMU_RANGE,
				     data->chip_info->scale_table[i].reg_range);
			अगर (ret < 0) अणु
				dev_err(dev, "Error writing pmu_range\n");
				वापस ret;
			पूर्ण

			data->range = data->chip_info->scale_table[i].reg_range;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmc150_accel_get_temp(काष्ठा bmc150_accel_data *data, पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	अचिन्हित पूर्णांक value;

	mutex_lock(&data->mutex);

	ret = regmap_पढ़ो(data->regmap, BMC150_ACCEL_REG_TEMP, &value);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading reg_temp\n");
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण
	*val = sign_extend32(value, 7);

	mutex_unlock(&data->mutex);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bmc150_accel_get_axis(काष्ठा bmc150_accel_data *data,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	पूर्णांक axis = chan->scan_index;
	__le16 raw_val;

	mutex_lock(&data->mutex);
	ret = bmc150_accel_set_घातer_state(data, true);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	ret = regmap_bulk_पढ़ो(data->regmap, BMC150_ACCEL_AXIS_TO_REG(axis),
			       &raw_val, माप(raw_val));
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading axis %d\n", axis);
		bmc150_accel_set_घातer_state(data, false);
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण
	*val = sign_extend32(le16_to_cpu(raw_val) >> chan->scan_type.shअगरt,
			     chan->scan_type.realbits - 1);
	ret = bmc150_accel_set_घातer_state(data, false);
	mutex_unlock(&data->mutex);
	अगर (ret < 0)
		वापस ret;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bmc150_accel_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			वापस bmc150_accel_get_temp(data, val);
		हाल IIO_ACCEL:
			अगर (iio_buffer_enabled(indio_dev))
				वापस -EBUSY;
			अन्यथा
				वापस bmc150_accel_get_axis(data, chan, val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		अगर (chan->type == IIO_TEMP) अणु
			*val = BMC150_ACCEL_TEMP_CENTER_VAL;
			वापस IIO_VAL_INT;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val2 = 500000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_ACCEL:
		अणु
			पूर्णांक i;
			स्थिर काष्ठा bmc150_scale_info *si;
			पूर्णांक st_size = ARRAY_SIZE(data->chip_info->scale_table);

			क्रम (i = 0; i < st_size; ++i) अणु
				si = &data->chip_info->scale_table[i];
				अगर (si->reg_range == data->range) अणु
					*val2 = si->scale;
					वापस IIO_VAL_INT_PLUS_MICRO;
				पूर्ण
			पूर्ण
			वापस -EINVAL;
		पूर्ण
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		ret = bmc150_accel_get_bw(data, val, val2);
		mutex_unlock(&data->mutex);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bmc150_accel_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				  काष्ठा iio_chan_spec स्थिर *chan,
				  पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		ret = bmc150_accel_set_bw(data, val, val2);
		mutex_unlock(&data->mutex);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val)
			वापस -EINVAL;

		mutex_lock(&data->mutex);
		ret = bmc150_accel_set_scale(data, val2);
		mutex_unlock(&data->mutex);
		वापस ret;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bmc150_accel_पढ़ो_event(काष्ठा iio_dev *indio_dev,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   क्रमागत iio_event_type type,
				   क्रमागत iio_event_direction dir,
				   क्रमागत iio_event_info info,
				   पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	*val2 = 0;
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		*val = data->slope_thres;
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		*val = data->slope_dur;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bmc150_accel_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	अगर (data->ev_enable_state)
		वापस -EBUSY;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		data->slope_thres = val & BMC150_ACCEL_SLOPE_THRES_MASK;
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		data->slope_dur = val & BMC150_ACCEL_SLOPE_DUR_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_accel_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  क्रमागत iio_event_type type,
					  क्रमागत iio_event_direction dir)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	वापस data->ev_enable_state;
पूर्ण

अटल पूर्णांक bmc150_accel_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   क्रमागत iio_event_type type,
					   क्रमागत iio_event_direction dir,
					   पूर्णांक state)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (state == data->ev_enable_state)
		वापस 0;

	mutex_lock(&data->mutex);

	ret = bmc150_accel_set_पूर्णांकerrupt(data, BMC150_ACCEL_INT_ANY_MOTION,
					 state);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	data->ev_enable_state = state;
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_accel_validate_trigger(काष्ठा iio_dev *indio_dev,
					 काष्ठा iio_trigger *trig)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक i;

	क्रम (i = 0; i < BMC150_ACCEL_TRIGGERS; i++) अणु
		अगर (data->triggers[i].indio_trig == trig)
			वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार bmc150_accel_get_fअगरo_watermark(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक wm;

	mutex_lock(&data->mutex);
	wm = data->watermark;
	mutex_unlock(&data->mutex);

	वापस प्र_लिखो(buf, "%d\n", wm);
पूर्ण

अटल sमाप_प्रकार bmc150_accel_get_fअगरo_state(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	bool state;

	mutex_lock(&data->mutex);
	state = data->fअगरo_mode;
	mutex_unlock(&data->mutex);

	वापस प्र_लिखो(buf, "%d\n", state);
पूर्ण

अटल स्थिर काष्ठा iio_mount_matrix *
bmc150_accel_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info bmc150_accel_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, bmc150_accel_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

अटल IIO_CONST_ATTR(hwfअगरo_watermark_min, "1");
अटल IIO_CONST_ATTR(hwfअगरo_watermark_max,
		      __stringअगरy(BMC150_ACCEL_FIFO_LENGTH));
अटल IIO_DEVICE_ATTR(hwfअगरo_enabled, S_IRUGO,
		       bmc150_accel_get_fअगरo_state, शून्य, 0);
अटल IIO_DEVICE_ATTR(hwfअगरo_watermark, S_IRUGO,
		       bmc150_accel_get_fअगरo_watermark, शून्य, 0);

अटल स्थिर काष्ठा attribute *bmc150_accel_fअगरo_attributes[] = अणु
	&iio_स्थिर_attr_hwfअगरo_watermark_min.dev_attr.attr,
	&iio_स्थिर_attr_hwfअगरo_watermark_max.dev_attr.attr,
	&iio_dev_attr_hwfअगरo_watermark.dev_attr.attr,
	&iio_dev_attr_hwfअगरo_enabled.dev_attr.attr,
	शून्य,
पूर्ण;

अटल पूर्णांक bmc150_accel_set_watermark(काष्ठा iio_dev *indio_dev, अचिन्हित val)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	अगर (val > BMC150_ACCEL_FIFO_LENGTH)
		val = BMC150_ACCEL_FIFO_LENGTH;

	mutex_lock(&data->mutex);
	data->watermark = val;
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

/*
 * We must पढ़ो at least one full frame in one burst, otherwise the rest of the
 * frame data is discarded.
 */
अटल पूर्णांक bmc150_accel_fअगरo_transfer(काष्ठा bmc150_accel_data *data,
				      अक्षर *buffer, पूर्णांक samples)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक sample_length = 3 * 2;
	पूर्णांक ret;
	पूर्णांक total_length = samples * sample_length;

	ret = regmap_raw_पढ़ो(data->regmap, BMC150_ACCEL_REG_FIFO_DATA,
			      buffer, total_length);
	अगर (ret)
		dev_err(dev,
			"Error transferring data from fifo: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __bmc150_accel_fअगरo_flush(काष्ठा iio_dev *indio_dev,
				     अचिन्हित samples, bool irq)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret, i;
	u8 count;
	u16 buffer[BMC150_ACCEL_FIFO_LENGTH * 3];
	पूर्णांक64_t tstamp;
	uपूर्णांक64_t sample_period;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(data->regmap, BMC150_ACCEL_REG_FIFO_STATUS, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading reg_fifo_status\n");
		वापस ret;
	पूर्ण

	count = val & 0x7F;

	अगर (!count)
		वापस 0;

	/*
	 * If we getting called from IRQ handler we know the stored बारtamp is
	 * fairly accurate क्रम the last stored sample. Otherwise, अगर we are
	 * called as a result of a पढ़ो operation from userspace and hence
	 * beक्रमe the watermark पूर्णांकerrupt was triggered, take a बारtamp
	 * now. We can fall anywhere in between two samples so the error in this
	 * हाल is at most one sample period.
	 */
	अगर (!irq) अणु
		data->old_बारtamp = data->बारtamp;
		data->बारtamp = iio_get_समय_ns(indio_dev);
	पूर्ण

	/*
	 * Approximate बारtamps क्रम each of the sample based on the sampling
	 * frequency, बारtamp क्रम last sample and number of samples.
	 *
	 * Note that we can't use the current bandwidth settings to compute the
	 * sample period because the sample rate varies with the device
	 * (e.g. between 31.70ms to 32.20ms क्रम a bandwidth of 15.63HZ). That
	 * small variation adds when we store a large number of samples and
	 * creates signअगरicant jitter between the last and first samples in
	 * dअगरferent batches (e.g. 32ms vs 21ms).
	 *
	 * To aव्योम this issue we compute the actual sample period ourselves
	 * based on the बारtamp delta between the last two flush operations.
	 */
	sample_period = (data->बारtamp - data->old_बारtamp);
	करो_भाग(sample_period, count);
	tstamp = data->बारtamp - (count - 1) * sample_period;

	अगर (samples && count > samples)
		count = samples;

	ret = bmc150_accel_fअगरo_transfer(data, (u8 *)buffer, count);
	अगर (ret)
		वापस ret;

	/*
	 * Ideally we want the IIO core to handle the demux when running in fअगरo
	 * mode but not when running in triggered buffer mode. Unक्रमtunately
	 * this करोes not seem to be possible, so stick with driver demux क्रम
	 * now.
	 */
	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक j, bit;

		j = 0;
		क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
				 indio_dev->masklength)
			स_नकल(&data->scan.channels[j++], &buffer[i * 3 + bit],
			       माप(data->scan.channels[0]));

		iio_push_to_buffers_with_बारtamp(indio_dev, &data->scan,
						   tstamp);

		tstamp += sample_period;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक bmc150_accel_fअगरo_flush(काष्ठा iio_dev *indio_dev, अचिन्हित samples)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = __bmc150_accel_fअगरo_flush(indio_dev, samples, false);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(
		"15.620000 31.260000 62.50000 125 250 500 1000 2000");

अटल काष्ठा attribute *bmc150_accel_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bmc150_accel_attrs_group = अणु
	.attrs = bmc150_accel_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec bmc150_accel_event = अणु
		.type = IIO_EV_TYPE_ROC,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_ENABLE) |
				 BIT(IIO_EV_INFO_PERIOD)
पूर्ण;

#घोषणा BMC150_ACCEL_CHANNEL(_axis, bits) अणु				\
	.type = IIO_ACCEL,						\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##_axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),		\
	.scan_index = AXIS_##_axis,					\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = (bits),					\
		.storagebits = 16,					\
		.shअगरt = 16 - (bits),					\
		.endianness = IIO_LE,					\
	पूर्ण,								\
	.ext_info = bmc150_accel_ext_info,				\
	.event_spec = &bmc150_accel_event,				\
	.num_event_specs = 1						\
पूर्ण

#घोषणा BMC150_ACCEL_CHANNELS(bits) अणु					\
	अणु								\
		.type = IIO_TEMP,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
				      BIT(IIO_CHAN_INFO_SCALE) |	\
				      BIT(IIO_CHAN_INFO_OFFSET),	\
		.scan_index = -1,					\
	पूर्ण,								\
	BMC150_ACCEL_CHANNEL(X, bits),					\
	BMC150_ACCEL_CHANNEL(Y, bits),					\
	BMC150_ACCEL_CHANNEL(Z, bits),					\
	IIO_CHAN_SOFT_TIMESTAMP(3),					\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec bma222e_accel_channels[] =
	BMC150_ACCEL_CHANNELS(8);
अटल स्थिर काष्ठा iio_chan_spec bma250e_accel_channels[] =
	BMC150_ACCEL_CHANNELS(10);
अटल स्थिर काष्ठा iio_chan_spec bmc150_accel_channels[] =
	BMC150_ACCEL_CHANNELS(12);
अटल स्थिर काष्ठा iio_chan_spec bma280_accel_channels[] =
	BMC150_ACCEL_CHANNELS(14);

अटल स्थिर काष्ठा bmc150_accel_chip_info bmc150_accel_chip_info_tbl[] = अणु
	[bmc150] = अणु
		.name = "BMC150A",
		.chip_id = 0xFA,
		.channels = bmc150_accel_channels,
		.num_channels = ARRAY_SIZE(bmc150_accel_channels),
		.scale_table = अणु अणु9610, BMC150_ACCEL_DEF_RANGE_2Gपूर्ण,
				 अणु19122, BMC150_ACCEL_DEF_RANGE_4Gपूर्ण,
				 अणु38344, BMC150_ACCEL_DEF_RANGE_8Gपूर्ण,
				 अणु76590, BMC150_ACCEL_DEF_RANGE_16Gपूर्ण पूर्ण,
	पूर्ण,
	[bmi055] = अणु
		.name = "BMI055A",
		.chip_id = 0xFA,
		.channels = bmc150_accel_channels,
		.num_channels = ARRAY_SIZE(bmc150_accel_channels),
		.scale_table = अणु अणु9610, BMC150_ACCEL_DEF_RANGE_2Gपूर्ण,
				 अणु19122, BMC150_ACCEL_DEF_RANGE_4Gपूर्ण,
				 अणु38344, BMC150_ACCEL_DEF_RANGE_8Gपूर्ण,
				 अणु76590, BMC150_ACCEL_DEF_RANGE_16Gपूर्ण पूर्ण,
	पूर्ण,
	[bma255] = अणु
		.name = "BMA0255",
		.chip_id = 0xFA,
		.channels = bmc150_accel_channels,
		.num_channels = ARRAY_SIZE(bmc150_accel_channels),
		.scale_table = अणु अणु9610, BMC150_ACCEL_DEF_RANGE_2Gपूर्ण,
				 अणु19122, BMC150_ACCEL_DEF_RANGE_4Gपूर्ण,
				 अणु38344, BMC150_ACCEL_DEF_RANGE_8Gपूर्ण,
				 अणु76590, BMC150_ACCEL_DEF_RANGE_16Gपूर्ण पूर्ण,
	पूर्ण,
	[bma250e] = अणु
		.name = "BMA250E",
		.chip_id = 0xF9,
		.channels = bma250e_accel_channels,
		.num_channels = ARRAY_SIZE(bma250e_accel_channels),
		.scale_table = अणु अणु38344, BMC150_ACCEL_DEF_RANGE_2Gपूर्ण,
				 अणु76590, BMC150_ACCEL_DEF_RANGE_4Gपूर्ण,
				 अणु153277, BMC150_ACCEL_DEF_RANGE_8Gपूर्ण,
				 अणु306457, BMC150_ACCEL_DEF_RANGE_16Gपूर्ण पूर्ण,
	पूर्ण,
	[bma222] = अणु
		.name = "BMA222",
		.chip_id = 0x03,
		.channels = bma222e_accel_channels,
		.num_channels = ARRAY_SIZE(bma222e_accel_channels),
		/*
		 * The datasheet page 17 says:
		 * 15.6, 31.3, 62.5 and 125 mg per LSB.
		 */
		.scale_table = अणु अणु156000, BMC150_ACCEL_DEF_RANGE_2Gपूर्ण,
				 अणु313000, BMC150_ACCEL_DEF_RANGE_4Gपूर्ण,
				 अणु625000, BMC150_ACCEL_DEF_RANGE_8Gपूर्ण,
				 अणु1250000, BMC150_ACCEL_DEF_RANGE_16Gपूर्ण पूर्ण,
	पूर्ण,
	[bma222e] = अणु
		.name = "BMA222E",
		.chip_id = 0xF8,
		.channels = bma222e_accel_channels,
		.num_channels = ARRAY_SIZE(bma222e_accel_channels),
		.scale_table = अणु अणु153277, BMC150_ACCEL_DEF_RANGE_2Gपूर्ण,
				 अणु306457, BMC150_ACCEL_DEF_RANGE_4Gपूर्ण,
				 अणु612915, BMC150_ACCEL_DEF_RANGE_8Gपूर्ण,
				 अणु1225831, BMC150_ACCEL_DEF_RANGE_16Gपूर्ण पूर्ण,
	पूर्ण,
	[bma280] = अणु
		.name = "BMA0280",
		.chip_id = 0xFB,
		.channels = bma280_accel_channels,
		.num_channels = ARRAY_SIZE(bma280_accel_channels),
		.scale_table = अणु अणु2392, BMC150_ACCEL_DEF_RANGE_2Gपूर्ण,
				 अणु4785, BMC150_ACCEL_DEF_RANGE_4Gपूर्ण,
				 अणु9581, BMC150_ACCEL_DEF_RANGE_8Gपूर्ण,
				 अणु19152, BMC150_ACCEL_DEF_RANGE_16Gपूर्ण पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info bmc150_accel_info = अणु
	.attrs			= &bmc150_accel_attrs_group,
	.पढ़ो_raw		= bmc150_accel_पढ़ो_raw,
	.ग_लिखो_raw		= bmc150_accel_ग_लिखो_raw,
	.पढ़ो_event_value	= bmc150_accel_पढ़ो_event,
	.ग_लिखो_event_value	= bmc150_accel_ग_लिखो_event,
	.ग_लिखो_event_config	= bmc150_accel_ग_लिखो_event_config,
	.पढ़ो_event_config	= bmc150_accel_पढ़ो_event_config,
पूर्ण;

अटल स्थिर काष्ठा iio_info bmc150_accel_info_fअगरo = अणु
	.attrs			= &bmc150_accel_attrs_group,
	.पढ़ो_raw		= bmc150_accel_पढ़ो_raw,
	.ग_लिखो_raw		= bmc150_accel_ग_लिखो_raw,
	.पढ़ो_event_value	= bmc150_accel_पढ़ो_event,
	.ग_लिखो_event_value	= bmc150_accel_ग_लिखो_event,
	.ग_लिखो_event_config	= bmc150_accel_ग_लिखो_event_config,
	.पढ़ो_event_config	= bmc150_accel_पढ़ो_event_config,
	.validate_trigger	= bmc150_accel_validate_trigger,
	.hwfअगरo_set_watermark	= bmc150_accel_set_watermark,
	.hwfअगरo_flush_to_buffer	= bmc150_accel_fअगरo_flush,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bmc150_accel_scan_masks[] = अणु
					BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
					0पूर्ण;

अटल irqवापस_t bmc150_accel_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = regmap_bulk_पढ़ो(data->regmap, BMC150_ACCEL_REG_XOUT_L,
			       data->buffer, AXIS_MAX * 2);
	mutex_unlock(&data->mutex);
	अगर (ret < 0)
		जाओ err_पढ़ो;

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   pf->बारtamp);
err_पढ़ो:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bmc150_accel_trig_reen(काष्ठा iio_trigger *trig)
अणु
	काष्ठा bmc150_accel_trigger *t = iio_trigger_get_drvdata(trig);
	काष्ठा bmc150_accel_data *data = t->data;
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	/* new data पूर्णांकerrupts करोn't need ack */
	अगर (t == &t->data->triggers[BMC150_ACCEL_TRIGGER_DATA_READY])
		वापस;

	mutex_lock(&data->mutex);
	/* clear any latched पूर्णांकerrupt */
	ret = regmap_ग_लिखो(data->regmap, BMC150_ACCEL_REG_INT_RST_LATCH,
			   BMC150_ACCEL_INT_MODE_LATCH_INT |
			   BMC150_ACCEL_INT_MODE_LATCH_RESET);
	mutex_unlock(&data->mutex);
	अगर (ret < 0)
		dev_err(dev, "Error writing reg_int_rst_latch\n");
पूर्ण

अटल पूर्णांक bmc150_accel_trigger_set_state(काष्ठा iio_trigger *trig,
					  bool state)
अणु
	काष्ठा bmc150_accel_trigger *t = iio_trigger_get_drvdata(trig);
	काष्ठा bmc150_accel_data *data = t->data;
	पूर्णांक ret;

	mutex_lock(&data->mutex);

	अगर (t->enabled == state) अणु
		mutex_unlock(&data->mutex);
		वापस 0;
	पूर्ण

	अगर (t->setup) अणु
		ret = t->setup(t, state);
		अगर (ret < 0) अणु
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = bmc150_accel_set_पूर्णांकerrupt(data, t->पूर्णांकr, state);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	t->enabled = state;

	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops bmc150_accel_trigger_ops = अणु
	.set_trigger_state = bmc150_accel_trigger_set_state,
	.reenable = bmc150_accel_trig_reen,
पूर्ण;

अटल पूर्णांक bmc150_accel_handle_roc_event(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक dir;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(data->regmap, BMC150_ACCEL_REG_INT_STATUS_2, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading reg_int_status_2\n");
		वापस ret;
	पूर्ण

	अगर (val & BMC150_ACCEL_ANY_MOTION_BIT_SIGN)
		dir = IIO_EV_सूची_FALLING;
	अन्यथा
		dir = IIO_EV_सूची_RISING;

	अगर (val & BMC150_ACCEL_ANY_MOTION_BIT_X)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_X,
						  IIO_EV_TYPE_ROC,
						  dir),
			       data->बारtamp);

	अगर (val & BMC150_ACCEL_ANY_MOTION_BIT_Y)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Y,
						  IIO_EV_TYPE_ROC,
						  dir),
			       data->बारtamp);

	अगर (val & BMC150_ACCEL_ANY_MOTION_BIT_Z)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Z,
						  IIO_EV_TYPE_ROC,
						  dir),
			       data->बारtamp);

	वापस ret;
पूर्ण

अटल irqवापस_t bmc150_accel_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(data->regmap);
	bool ack = false;
	पूर्णांक ret;

	mutex_lock(&data->mutex);

	अगर (data->fअगरo_mode) अणु
		ret = __bmc150_accel_fअगरo_flush(indio_dev,
						BMC150_ACCEL_FIFO_LENGTH, true);
		अगर (ret > 0)
			ack = true;
	पूर्ण

	अगर (data->ev_enable_state) अणु
		ret = bmc150_accel_handle_roc_event(indio_dev);
		अगर (ret > 0)
			ack = true;
	पूर्ण

	अगर (ack) अणु
		ret = regmap_ग_लिखो(data->regmap, BMC150_ACCEL_REG_INT_RST_LATCH,
				   BMC150_ACCEL_INT_MODE_LATCH_INT |
				   BMC150_ACCEL_INT_MODE_LATCH_RESET);
		अगर (ret)
			dev_err(dev, "Error writing reg_int_rst_latch\n");

		ret = IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		ret = IRQ_NONE;
	पूर्ण

	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल irqवापस_t bmc150_accel_irq_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	bool ack = false;
	पूर्णांक i;

	data->old_बारtamp = data->बारtamp;
	data->बारtamp = iio_get_समय_ns(indio_dev);

	क्रम (i = 0; i < BMC150_ACCEL_TRIGGERS; i++) अणु
		अगर (data->triggers[i].enabled) अणु
			iio_trigger_poll(data->triggers[i].indio_trig);
			ack = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (data->ev_enable_state || data->fअगरo_mode)
		वापस IRQ_WAKE_THREAD;

	अगर (ack)
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक पूर्णांकr;
	स्थिर अक्षर *name;
	पूर्णांक (*setup)(काष्ठा bmc150_accel_trigger *t, bool state);
पूर्ण bmc150_accel_triggers[BMC150_ACCEL_TRIGGERS] = अणु
	अणु
		.पूर्णांकr = 0,
		.name = "%s-dev%d",
	पूर्ण,
	अणु
		.पूर्णांकr = 1,
		.name = "%s-any-motion-dev%d",
		.setup = bmc150_accel_any_motion_setup,
	पूर्ण,
पूर्ण;

अटल व्योम bmc150_accel_unरेजिस्टर_triggers(काष्ठा bmc150_accel_data *data,
					     पूर्णांक from)
अणु
	पूर्णांक i;

	क्रम (i = from; i >= 0; i--) अणु
		अगर (data->triggers[i].indio_trig) अणु
			iio_trigger_unरेजिस्टर(data->triggers[i].indio_trig);
			data->triggers[i].indio_trig = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bmc150_accel_triggers_setup(काष्ठा iio_dev *indio_dev,
				       काष्ठा bmc150_accel_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक i, ret;

	क्रम (i = 0; i < BMC150_ACCEL_TRIGGERS; i++) अणु
		काष्ठा bmc150_accel_trigger *t = &data->triggers[i];

		t->indio_trig = devm_iio_trigger_alloc(dev,
					bmc150_accel_triggers[i].name,
						       indio_dev->name,
						       indio_dev->id);
		अगर (!t->indio_trig) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		t->indio_trig->ops = &bmc150_accel_trigger_ops;
		t->पूर्णांकr = bmc150_accel_triggers[i].पूर्णांकr;
		t->data = data;
		t->setup = bmc150_accel_triggers[i].setup;
		iio_trigger_set_drvdata(t->indio_trig, t);

		ret = iio_trigger_रेजिस्टर(t->indio_trig);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (ret)
		bmc150_accel_unरेजिस्टर_triggers(data, i - 1);

	वापस ret;
पूर्ण

#घोषणा BMC150_ACCEL_FIFO_MODE_STREAM          0x80
#घोषणा BMC150_ACCEL_FIFO_MODE_FIFO            0x40
#घोषणा BMC150_ACCEL_FIFO_MODE_BYPASS          0x00

अटल पूर्णांक bmc150_accel_fअगरo_set_mode(काष्ठा bmc150_accel_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	u8 reg = BMC150_ACCEL_REG_FIFO_CONFIG1;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, reg, data->fअगरo_mode);
	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_fifo_config1\n");
		वापस ret;
	पूर्ण

	अगर (!data->fअगरo_mode)
		वापस 0;

	ret = regmap_ग_लिखो(data->regmap, BMC150_ACCEL_REG_FIFO_CONFIG0,
			   data->watermark);
	अगर (ret < 0)
		dev_err(dev, "Error writing reg_fifo_config0\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bmc150_accel_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	वापस bmc150_accel_set_घातer_state(data, true);
पूर्ण

अटल पूर्णांक bmc150_accel_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	अगर (indio_dev->currenपंचांगode == INDIO_BUFFER_TRIGGERED)
		वापस 0;

	mutex_lock(&data->mutex);

	अगर (!data->watermark)
		जाओ out;

	ret = bmc150_accel_set_पूर्णांकerrupt(data, BMC150_ACCEL_INT_WATERMARK,
					 true);
	अगर (ret)
		जाओ out;

	data->fअगरo_mode = BMC150_ACCEL_FIFO_MODE_FIFO;

	ret = bmc150_accel_fअगरo_set_mode(data);
	अगर (ret) अणु
		data->fअगरo_mode = 0;
		bmc150_accel_set_पूर्णांकerrupt(data, BMC150_ACCEL_INT_WATERMARK,
					   false);
	पूर्ण

out:
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक bmc150_accel_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	अगर (indio_dev->currenपंचांगode == INDIO_BUFFER_TRIGGERED)
		वापस 0;

	mutex_lock(&data->mutex);

	अगर (!data->fअगरo_mode)
		जाओ out;

	bmc150_accel_set_पूर्णांकerrupt(data, BMC150_ACCEL_INT_WATERMARK, false);
	__bmc150_accel_fअगरo_flush(indio_dev, BMC150_ACCEL_FIFO_LENGTH, false);
	data->fअगरo_mode = 0;
	bmc150_accel_fअगरo_set_mode(data);

out:
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_accel_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	वापस bmc150_accel_set_घातer_state(data, false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops bmc150_accel_buffer_ops = अणु
	.preenable = bmc150_accel_buffer_preenable,
	.postenable = bmc150_accel_buffer_postenable,
	.predisable = bmc150_accel_buffer_predisable,
	.postdisable = bmc150_accel_buffer_postdisable,
पूर्ण;

अटल पूर्णांक bmc150_accel_chip_init(काष्ठा bmc150_accel_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक val;

	/*
	 * Reset chip to get it in a known good state. A delay of 1.8ms after
	 * reset is required according to the data sheets of supported chips.
	 */
	regmap_ग_लिखो(data->regmap, BMC150_ACCEL_REG_RESET,
		     BMC150_ACCEL_RESET_VAL);
	usleep_range(1800, 2500);

	ret = regmap_पढ़ो(data->regmap, BMC150_ACCEL_REG_CHIP_ID, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error: Reading chip id\n");
		वापस ret;
	पूर्ण

	dev_dbg(dev, "Chip Id %x\n", val);
	क्रम (i = 0; i < ARRAY_SIZE(bmc150_accel_chip_info_tbl); i++) अणु
		अगर (bmc150_accel_chip_info_tbl[i].chip_id == val) अणु
			data->chip_info = &bmc150_accel_chip_info_tbl[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!data->chip_info) अणु
		dev_err(dev, "Invalid chip %x\n", val);
		वापस -ENODEV;
	पूर्ण

	ret = bmc150_accel_set_mode(data, BMC150_ACCEL_SLEEP_MODE_NORMAL, 0);
	अगर (ret < 0)
		वापस ret;

	/* Set Bandwidth */
	ret = bmc150_accel_set_bw(data, BMC150_ACCEL_DEF_BW, 0);
	अगर (ret < 0)
		वापस ret;

	/* Set Default Range */
	ret = regmap_ग_लिखो(data->regmap, BMC150_ACCEL_REG_PMU_RANGE,
			   BMC150_ACCEL_DEF_RANGE_4G);
	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_pmu_range\n");
		वापस ret;
	पूर्ण

	data->range = BMC150_ACCEL_DEF_RANGE_4G;

	/* Set शेष slope duration and thresholds */
	data->slope_thres = BMC150_ACCEL_DEF_SLOPE_THRESHOLD;
	data->slope_dur = BMC150_ACCEL_DEF_SLOPE_DURATION;
	ret = bmc150_accel_update_slope(data);
	अगर (ret < 0)
		वापस ret;

	/* Set शेष as latched पूर्णांकerrupts */
	ret = regmap_ग_लिखो(data->regmap, BMC150_ACCEL_REG_INT_RST_LATCH,
			   BMC150_ACCEL_INT_MODE_LATCH_INT |
			   BMC150_ACCEL_INT_MODE_LATCH_RESET);
	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_int_rst_latch\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bmc150_accel_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap, पूर्णांक irq,
			    स्थिर अक्षर *name, bool block_supported)
अणु
	स्थिर काष्ठा attribute **fअगरo_attrs;
	काष्ठा bmc150_accel_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);

	data->regmap = regmap;

	अगर (!bmc150_apply_acpi_orientation(dev, &data->orientation)) अणु
		ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix",
					     &data->orientation);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * VDD   is the analog and digital करोमुख्य voltage supply
	 * VDDIO is the digital I/O voltage supply
	 */
	data->regulators[0].supply = "vdd";
	data->regulators[1].supply = "vddio";
	ret = devm_regulator_bulk_get(dev,
				      ARRAY_SIZE(data->regulators),
				      data->regulators);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "failed to get regulators\n");

	ret = regulator_bulk_enable(ARRAY_SIZE(data->regulators),
				    data->regulators);
	अगर (ret) अणु
		dev_err(dev, "failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण
	/*
	 * 2ms or 3ms घातer-on समय according to datasheets, let's better
	 * be safe than sorry and set this delay to 5ms.
	 */
	msleep(5);

	ret = bmc150_accel_chip_init(data);
	अगर (ret < 0)
		जाओ err_disable_regulators;

	mutex_init(&data->mutex);

	indio_dev->channels = data->chip_info->channels;
	indio_dev->num_channels = data->chip_info->num_channels;
	indio_dev->name = name ? name : data->chip_info->name;
	indio_dev->available_scan_masks = bmc150_accel_scan_masks;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &bmc150_accel_info;

	अगर (block_supported) अणु
		indio_dev->modes |= INDIO_BUFFER_SOFTWARE;
		indio_dev->info = &bmc150_accel_info_fअगरo;
		fअगरo_attrs = bmc150_accel_fअगरo_attributes;
	पूर्ण अन्यथा अणु
		fअगरo_attrs = शून्य;
	पूर्ण

	ret = iio_triggered_buffer_setup_ext(indio_dev,
					     &iio_pollfunc_store_समय,
					     bmc150_accel_trigger_handler,
					     &bmc150_accel_buffer_ops,
					     fअगरo_attrs);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed: iio triggered buffer setup\n");
		जाओ err_disable_regulators;
	पूर्ण

	अगर (irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev, irq,
						bmc150_accel_irq_handler,
						bmc150_accel_irq_thपढ़ो_handler,
						IRQF_TRIGGER_RISING,
						BMC150_ACCEL_IRQ_NAME,
						indio_dev);
		अगर (ret)
			जाओ err_buffer_cleanup;

		/*
		 * Set latched mode पूर्णांकerrupt. While certain पूर्णांकerrupts are
		 * non-latched regardless of this settings (e.g. new data) we
		 * want to use latch mode when we can to prevent पूर्णांकerrupt
		 * flooding.
		 */
		ret = regmap_ग_लिखो(data->regmap, BMC150_ACCEL_REG_INT_RST_LATCH,
				   BMC150_ACCEL_INT_MODE_LATCH_RESET);
		अगर (ret < 0) अणु
			dev_err(dev, "Error writing reg_int_rst_latch\n");
			जाओ err_buffer_cleanup;
		पूर्ण

		bmc150_accel_पूर्णांकerrupts_setup(indio_dev, data);

		ret = bmc150_accel_triggers_setup(indio_dev, data);
		अगर (ret)
			जाओ err_buffer_cleanup;
	पूर्ण

	ret = pm_runसमय_set_active(dev);
	अगर (ret)
		जाओ err_trigger_unरेजिस्टर;

	pm_runसमय_enable(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, BMC150_AUTO_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Unable to register iio device\n");
		जाओ err_trigger_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_trigger_unरेजिस्टर:
	bmc150_accel_unरेजिस्टर_triggers(data, BMC150_ACCEL_TRIGGERS - 1);
err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_disable_regulators:
	regulator_bulk_disable(ARRAY_SIZE(data->regulators),
			       data->regulators);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bmc150_accel_core_probe);

काष्ठा i2c_client *bmc150_get_second_device(काष्ठा i2c_client *client)
अणु
	काष्ठा bmc150_accel_data *data = i2c_get_clientdata(client);

	अगर (!data)
		वापस शून्य;

	वापस data->second_device;
पूर्ण
EXPORT_SYMBOL_GPL(bmc150_get_second_device);

व्योम bmc150_set_second_device(काष्ठा i2c_client *client)
अणु
	काष्ठा bmc150_accel_data *data = i2c_get_clientdata(client);

	अगर (data)
		data->second_device = client;
पूर्ण
EXPORT_SYMBOL_GPL(bmc150_set_second_device);

पूर्णांक bmc150_accel_core_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);

	bmc150_accel_unरेजिस्टर_triggers(data, BMC150_ACCEL_TRIGGERS - 1);

	iio_triggered_buffer_cleanup(indio_dev);

	mutex_lock(&data->mutex);
	bmc150_accel_set_mode(data, BMC150_ACCEL_SLEEP_MODE_DEEP_SUSPEND, 0);
	mutex_unlock(&data->mutex);

	regulator_bulk_disable(ARRAY_SIZE(data->regulators),
			       data->regulators);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bmc150_accel_core_हटाओ);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bmc150_accel_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	mutex_lock(&data->mutex);
	bmc150_accel_set_mode(data, BMC150_ACCEL_SLEEP_MODE_SUSPEND, 0);
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_accel_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);

	mutex_lock(&data->mutex);
	bmc150_accel_set_mode(data, BMC150_ACCEL_SLEEP_MODE_NORMAL, 0);
	bmc150_accel_fअगरo_set_mode(data);
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bmc150_accel_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = bmc150_accel_set_mode(data, BMC150_ACCEL_SLEEP_MODE_SUSPEND, 0);
	अगर (ret < 0)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_accel_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_accel_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक sleep_val;

	ret = bmc150_accel_set_mode(data, BMC150_ACCEL_SLEEP_MODE_NORMAL, 0);
	अगर (ret < 0)
		वापस ret;
	ret = bmc150_accel_fअगरo_set_mode(data);
	अगर (ret < 0)
		वापस ret;

	sleep_val = bmc150_accel_get_startup_बार(data);
	अगर (sleep_val < 20)
		usleep_range(sleep_val * 1000, 20000);
	अन्यथा
		msleep_पूर्णांकerruptible(sleep_val);

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops bmc150_accel_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bmc150_accel_suspend, bmc150_accel_resume)
	SET_RUNTIME_PM_OPS(bmc150_accel_runसमय_suspend,
			   bmc150_accel_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(bmc150_accel_pm_ops);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMC150 accelerometer driver");
