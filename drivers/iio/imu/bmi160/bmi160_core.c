<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BMI160 - Bosch IMU (accel, gyro plus बाह्यal magnetometer)
 *
 * Copyright (c) 2016, Intel Corporation.
 * Copyright (c) 2019, Martin Kelly.
 *
 * IIO core driver क्रम BMI160, with support क्रम I2C/SPI busses
 *
 * TODO: magnetometer, hardware FIFO
 */
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>

#समावेश "bmi160.h"

#घोषणा BMI160_REG_CHIP_ID	0x00
#घोषणा BMI160_CHIP_ID_VAL	0xD1

#घोषणा BMI160_REG_PMU_STATUS	0x03

/* X axis data low byte address, the rest can be obtained using axis offset */
#घोषणा BMI160_REG_DATA_MAGN_XOUT_L	0x04
#घोषणा BMI160_REG_DATA_GYRO_XOUT_L	0x0C
#घोषणा BMI160_REG_DATA_ACCEL_XOUT_L	0x12

#घोषणा BMI160_REG_ACCEL_CONFIG		0x40
#घोषणा BMI160_ACCEL_CONFIG_ODR_MASK	GENMASK(3, 0)
#घोषणा BMI160_ACCEL_CONFIG_BWP_MASK	GENMASK(6, 4)

#घोषणा BMI160_REG_ACCEL_RANGE		0x41
#घोषणा BMI160_ACCEL_RANGE_2G		0x03
#घोषणा BMI160_ACCEL_RANGE_4G		0x05
#घोषणा BMI160_ACCEL_RANGE_8G		0x08
#घोषणा BMI160_ACCEL_RANGE_16G		0x0C

#घोषणा BMI160_REG_GYRO_CONFIG		0x42
#घोषणा BMI160_GYRO_CONFIG_ODR_MASK	GENMASK(3, 0)
#घोषणा BMI160_GYRO_CONFIG_BWP_MASK	GENMASK(5, 4)

#घोषणा BMI160_REG_GYRO_RANGE		0x43
#घोषणा BMI160_GYRO_RANGE_2000DPS	0x00
#घोषणा BMI160_GYRO_RANGE_1000DPS	0x01
#घोषणा BMI160_GYRO_RANGE_500DPS	0x02
#घोषणा BMI160_GYRO_RANGE_250DPS	0x03
#घोषणा BMI160_GYRO_RANGE_125DPS	0x04

#घोषणा BMI160_REG_CMD			0x7E
#घोषणा BMI160_CMD_ACCEL_PM_SUSPEND	0x10
#घोषणा BMI160_CMD_ACCEL_PM_NORMAL	0x11
#घोषणा BMI160_CMD_ACCEL_PM_LOW_POWER	0x12
#घोषणा BMI160_CMD_GYRO_PM_SUSPEND	0x14
#घोषणा BMI160_CMD_GYRO_PM_NORMAL	0x15
#घोषणा BMI160_CMD_GYRO_PM_FAST_STARTUP	0x17
#घोषणा BMI160_CMD_SOFTRESET		0xB6

#घोषणा BMI160_REG_INT_EN		0x51
#घोषणा BMI160_DRDY_INT_EN		BIT(4)

#घोषणा BMI160_REG_INT_OUT_CTRL		0x53
#घोषणा BMI160_INT_OUT_CTRL_MASK	0x0f
#घोषणा BMI160_INT1_OUT_CTRL_SHIFT	0
#घोषणा BMI160_INT2_OUT_CTRL_SHIFT	4
#घोषणा BMI160_EDGE_TRIGGERED		BIT(0)
#घोषणा BMI160_ACTIVE_HIGH		BIT(1)
#घोषणा BMI160_OPEN_DRAIN		BIT(2)
#घोषणा BMI160_OUTPUT_EN		BIT(3)

#घोषणा BMI160_REG_INT_LATCH		0x54
#घोषणा BMI160_INT1_LATCH_MASK		BIT(4)
#घोषणा BMI160_INT2_LATCH_MASK		BIT(5)

/* INT1 and INT2 are in the opposite order as in INT_OUT_CTRL! */
#घोषणा BMI160_REG_INT_MAP		0x56
#घोषणा BMI160_INT1_MAP_DRDY_EN		0x80
#घोषणा BMI160_INT2_MAP_DRDY_EN		0x08

#घोषणा BMI160_REG_DUMMY		0x7F

#घोषणा BMI160_NORMAL_WRITE_USLEEP	2
#घोषणा BMI160_SUSPENDED_WRITE_USLEEP	450

#घोषणा BMI160_ACCEL_PMU_MIN_USLEEP	3800
#घोषणा BMI160_GYRO_PMU_MIN_USLEEP	80000
#घोषणा BMI160_SOFTRESET_USLEEP		1000

#घोषणा BMI160_CHANNEL(_type, _axis, _index) अणु			\
	.type = _type,						\
	.modअगरied = 1,						\
	.channel2 = IIO_MOD_##_axis,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |  \
		BIT(IIO_CHAN_INFO_SAMP_FREQ),			\
	.scan_index = _index,					\
	.scan_type = अणु						\
		.sign = 's',					\
		.realbits = 16,					\
		.storagebits = 16,				\
		.endianness = IIO_LE,				\
	पूर्ण,							\
	.ext_info = bmi160_ext_info,				\
पूर्ण

/* scan indexes follow DATA रेजिस्टर order */
क्रमागत bmi160_scan_axis अणु
	BMI160_SCAN_EXT_MAGN_X = 0,
	BMI160_SCAN_EXT_MAGN_Y,
	BMI160_SCAN_EXT_MAGN_Z,
	BMI160_SCAN_RHALL,
	BMI160_SCAN_GYRO_X,
	BMI160_SCAN_GYRO_Y,
	BMI160_SCAN_GYRO_Z,
	BMI160_SCAN_ACCEL_X,
	BMI160_SCAN_ACCEL_Y,
	BMI160_SCAN_ACCEL_Z,
	BMI160_SCAN_TIMESTAMP,
पूर्ण;

क्रमागत bmi160_sensor_type अणु
	BMI160_ACCEL	= 0,
	BMI160_GYRO,
	BMI160_EXT_MAGN,
	BMI160_NUM_SENSORS /* must be last */
पूर्ण;

क्रमागत bmi160_पूर्णांक_pin अणु
	BMI160_PIN_INT1,
	BMI160_PIN_INT2
पूर्ण;

स्थिर काष्ठा regmap_config bmi160_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;
EXPORT_SYMBOL(bmi160_regmap_config);

काष्ठा bmi160_regs अणु
	u8 data; /* LSB byte रेजिस्टर क्रम X-axis */
	u8 config;
	u8 config_odr_mask;
	u8 config_bwp_mask;
	u8 range;
	u8 pmu_cmd_normal;
	u8 pmu_cmd_suspend;
पूर्ण;

अटल काष्ठा bmi160_regs bmi160_regs[] = अणु
	[BMI160_ACCEL] = अणु
		.data	= BMI160_REG_DATA_ACCEL_XOUT_L,
		.config	= BMI160_REG_ACCEL_CONFIG,
		.config_odr_mask = BMI160_ACCEL_CONFIG_ODR_MASK,
		.config_bwp_mask = BMI160_ACCEL_CONFIG_BWP_MASK,
		.range	= BMI160_REG_ACCEL_RANGE,
		.pmu_cmd_normal = BMI160_CMD_ACCEL_PM_NORMAL,
		.pmu_cmd_suspend = BMI160_CMD_ACCEL_PM_SUSPEND,
	पूर्ण,
	[BMI160_GYRO] = अणु
		.data	= BMI160_REG_DATA_GYRO_XOUT_L,
		.config	= BMI160_REG_GYRO_CONFIG,
		.config_odr_mask = BMI160_GYRO_CONFIG_ODR_MASK,
		.config_bwp_mask = BMI160_GYRO_CONFIG_BWP_MASK,
		.range	= BMI160_REG_GYRO_RANGE,
		.pmu_cmd_normal = BMI160_CMD_GYRO_PM_NORMAL,
		.pmu_cmd_suspend = BMI160_CMD_GYRO_PM_SUSPEND,
	पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ bmi160_pmu_समय[] = अणु
	[BMI160_ACCEL] = BMI160_ACCEL_PMU_MIN_USLEEP,
	[BMI160_GYRO] = BMI160_GYRO_PMU_MIN_USLEEP,
पूर्ण;

काष्ठा bmi160_scale अणु
	u8 bits;
	पूर्णांक uscale;
पूर्ण;

काष्ठा bmi160_odr अणु
	u8 bits;
	पूर्णांक odr;
	पूर्णांक uodr;
पूर्ण;

अटल स्थिर काष्ठा bmi160_scale bmi160_accel_scale[] = अणु
	अणु BMI160_ACCEL_RANGE_2G, 598पूर्ण,
	अणु BMI160_ACCEL_RANGE_4G, 1197पूर्ण,
	अणु BMI160_ACCEL_RANGE_8G, 2394पूर्ण,
	अणु BMI160_ACCEL_RANGE_16G, 4788पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bmi160_scale bmi160_gyro_scale[] = अणु
	अणु BMI160_GYRO_RANGE_2000DPS, 1065पूर्ण,
	अणु BMI160_GYRO_RANGE_1000DPS, 532पूर्ण,
	अणु BMI160_GYRO_RANGE_500DPS, 266पूर्ण,
	अणु BMI160_GYRO_RANGE_250DPS, 133पूर्ण,
	अणु BMI160_GYRO_RANGE_125DPS, 66पूर्ण,
पूर्ण;

काष्ठा bmi160_scale_item अणु
	स्थिर काष्ठा bmi160_scale *tbl;
	पूर्णांक num;
पूर्ण;

अटल स्थिर काष्ठा  bmi160_scale_item bmi160_scale_table[] = अणु
	[BMI160_ACCEL] = अणु
		.tbl	= bmi160_accel_scale,
		.num	= ARRAY_SIZE(bmi160_accel_scale),
	पूर्ण,
	[BMI160_GYRO] = अणु
		.tbl	= bmi160_gyro_scale,
		.num	= ARRAY_SIZE(bmi160_gyro_scale),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bmi160_odr bmi160_accel_odr[] = अणु
	अणु0x01, 0, 781250पूर्ण,
	अणु0x02, 1, 562500पूर्ण,
	अणु0x03, 3, 125000पूर्ण,
	अणु0x04, 6, 250000पूर्ण,
	अणु0x05, 12, 500000पूर्ण,
	अणु0x06, 25, 0पूर्ण,
	अणु0x07, 50, 0पूर्ण,
	अणु0x08, 100, 0पूर्ण,
	अणु0x09, 200, 0पूर्ण,
	अणु0x0A, 400, 0पूर्ण,
	अणु0x0B, 800, 0पूर्ण,
	अणु0x0C, 1600, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bmi160_odr bmi160_gyro_odr[] = अणु
	अणु0x06, 25, 0पूर्ण,
	अणु0x07, 50, 0पूर्ण,
	अणु0x08, 100, 0पूर्ण,
	अणु0x09, 200, 0पूर्ण,
	अणु0x0A, 400, 0पूर्ण,
	अणु0x0B, 800, 0पूर्ण,
	अणु0x0C, 1600, 0पूर्ण,
	अणु0x0D, 3200, 0पूर्ण,
पूर्ण;

काष्ठा bmi160_odr_item अणु
	स्थिर काष्ठा bmi160_odr *tbl;
	पूर्णांक num;
पूर्ण;

अटल स्थिर काष्ठा  bmi160_odr_item bmi160_odr_table[] = अणु
	[BMI160_ACCEL] = अणु
		.tbl	= bmi160_accel_odr,
		.num	= ARRAY_SIZE(bmi160_accel_odr),
	पूर्ण,
	[BMI160_GYRO] = अणु
		.tbl	= bmi160_gyro_odr,
		.num	= ARRAY_SIZE(bmi160_gyro_odr),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_mount_matrix *
bmi160_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा bmi160_data *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info bmi160_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, bmi160_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec bmi160_channels[] = अणु
	BMI160_CHANNEL(IIO_ACCEL, X, BMI160_SCAN_ACCEL_X),
	BMI160_CHANNEL(IIO_ACCEL, Y, BMI160_SCAN_ACCEL_Y),
	BMI160_CHANNEL(IIO_ACCEL, Z, BMI160_SCAN_ACCEL_Z),
	BMI160_CHANNEL(IIO_ANGL_VEL, X, BMI160_SCAN_GYRO_X),
	BMI160_CHANNEL(IIO_ANGL_VEL, Y, BMI160_SCAN_GYRO_Y),
	BMI160_CHANNEL(IIO_ANGL_VEL, Z, BMI160_SCAN_GYRO_Z),
	IIO_CHAN_SOFT_TIMESTAMP(BMI160_SCAN_TIMESTAMP),
पूर्ण;

अटल क्रमागत bmi160_sensor_type bmi160_to_sensor(क्रमागत iio_chan_type iio_type)
अणु
	चयन (iio_type) अणु
	हाल IIO_ACCEL:
		वापस BMI160_ACCEL;
	हाल IIO_ANGL_VEL:
		वापस BMI160_GYRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल
पूर्णांक bmi160_set_mode(काष्ठा bmi160_data *data, क्रमागत bmi160_sensor_type t,
		    bool mode)
अणु
	पूर्णांक ret;
	u8 cmd;

	अगर (mode)
		cmd = bmi160_regs[t].pmu_cmd_normal;
	अन्यथा
		cmd = bmi160_regs[t].pmu_cmd_suspend;

	ret = regmap_ग_लिखो(data->regmap, BMI160_REG_CMD, cmd);
	अगर (ret)
		वापस ret;

	usleep_range(bmi160_pmu_समय[t], bmi160_pmu_समय[t] + 1000);

	वापस 0;
पूर्ण

अटल
पूर्णांक bmi160_set_scale(काष्ठा bmi160_data *data, क्रमागत bmi160_sensor_type t,
		     पूर्णांक uscale)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bmi160_scale_table[t].num; i++)
		अगर (bmi160_scale_table[t].tbl[i].uscale == uscale)
			अवरोध;

	अगर (i == bmi160_scale_table[t].num)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(data->regmap, bmi160_regs[t].range,
			    bmi160_scale_table[t].tbl[i].bits);
पूर्ण

अटल
पूर्णांक bmi160_get_scale(काष्ठा bmi160_data *data, क्रमागत bmi160_sensor_type t,
		     पूर्णांक *uscale)
अणु
	पूर्णांक i, ret, val;

	ret = regmap_पढ़ो(data->regmap, bmi160_regs[t].range, &val);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < bmi160_scale_table[t].num; i++)
		अगर (bmi160_scale_table[t].tbl[i].bits == val) अणु
			*uscale = bmi160_scale_table[t].tbl[i].uscale;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmi160_get_data(काष्ठा bmi160_data *data, पूर्णांक chan_type,
			   पूर्णांक axis, पूर्णांक *val)
अणु
	u8 reg;
	पूर्णांक ret;
	__le16 sample;
	क्रमागत bmi160_sensor_type t = bmi160_to_sensor(chan_type);

	reg = bmi160_regs[t].data + (axis - IIO_MOD_X) * माप(sample);

	ret = regmap_bulk_पढ़ो(data->regmap, reg, &sample, माप(sample));
	अगर (ret)
		वापस ret;

	*val = sign_extend32(le16_to_cpu(sample), 15);

	वापस 0;
पूर्ण

अटल
पूर्णांक bmi160_set_odr(काष्ठा bmi160_data *data, क्रमागत bmi160_sensor_type t,
		   पूर्णांक odr, पूर्णांक uodr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bmi160_odr_table[t].num; i++)
		अगर (bmi160_odr_table[t].tbl[i].odr == odr &&
		    bmi160_odr_table[t].tbl[i].uodr == uodr)
			अवरोध;

	अगर (i >= bmi160_odr_table[t].num)
		वापस -EINVAL;

	वापस regmap_update_bits(data->regmap,
				  bmi160_regs[t].config,
				  bmi160_regs[t].config_odr_mask,
				  bmi160_odr_table[t].tbl[i].bits);
पूर्ण

अटल पूर्णांक bmi160_get_odr(काष्ठा bmi160_data *data, क्रमागत bmi160_sensor_type t,
			  पूर्णांक *odr, पूर्णांक *uodr)
अणु
	पूर्णांक i, val, ret;

	ret = regmap_पढ़ो(data->regmap, bmi160_regs[t].config, &val);
	अगर (ret)
		वापस ret;

	val &= bmi160_regs[t].config_odr_mask;

	क्रम (i = 0; i < bmi160_odr_table[t].num; i++)
		अगर (val == bmi160_odr_table[t].tbl[i].bits)
			अवरोध;

	अगर (i >= bmi160_odr_table[t].num)
		वापस -EINVAL;

	*odr = bmi160_odr_table[t].tbl[i].odr;
	*uodr = bmi160_odr_table[t].tbl[i].uodr;

	वापस 0;
पूर्ण

अटल irqवापस_t bmi160_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा bmi160_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret, j = 0, base = BMI160_REG_DATA_MAGN_XOUT_L;
	__le16 sample;

	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		ret = regmap_bulk_पढ़ो(data->regmap, base + i * माप(sample),
				       &sample, माप(sample));
		अगर (ret)
			जाओ करोne;
		data->buf[j++] = sample;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buf, pf->बारtamp);
करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bmi160_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा bmi160_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = bmi160_get_data(data, chan->type, chan->channel2, val);
		अगर (ret)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		ret = bmi160_get_scale(data,
				       bmi160_to_sensor(chan->type), val2);
		वापस ret ? ret : IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = bmi160_get_odr(data, bmi160_to_sensor(chan->type),
				     val, val2);
		वापस ret ? ret : IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmi160_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा bmi160_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		वापस bmi160_set_scale(data,
					bmi160_to_sensor(chan->type), val2);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस bmi160_set_odr(data, bmi160_to_sensor(chan->type),
				      val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल
IIO_CONST_ATTR(in_accel_sampling_frequency_available,
	       "0.78125 1.5625 3.125 6.25 12.5 25 50 100 200 400 800 1600");
अटल
IIO_CONST_ATTR(in_anglvel_sampling_frequency_available,
	       "25 50 100 200 400 800 1600 3200");
अटल
IIO_CONST_ATTR(in_accel_scale_available,
	       "0.000598 0.001197 0.002394 0.004788");
अटल
IIO_CONST_ATTR(in_anglvel_scale_available,
	       "0.001065 0.000532 0.000266 0.000133 0.000066");

अटल काष्ठा attribute *bmi160_attrs[] = अणु
	&iio_स्थिर_attr_in_accel_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_anglvel_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_accel_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_anglvel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bmi160_attrs_group = अणु
	.attrs = bmi160_attrs,
पूर्ण;

अटल स्थिर काष्ठा iio_info bmi160_info = अणु
	.पढ़ो_raw = bmi160_पढ़ो_raw,
	.ग_लिखो_raw = bmi160_ग_लिखो_raw,
	.attrs = &bmi160_attrs_group,
पूर्ण;

अटल स्थिर अक्षर *bmi160_match_acpi_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस शून्य;

	वापस dev_name(dev);
पूर्ण

अटल पूर्णांक bmi160_ग_लिखो_conf_reg(काष्ठा regmap *regmap, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक bits,
				 अचिन्हित पूर्णांक ग_लिखो_usleep)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(regmap, reg, &val);
	अगर (ret)
		वापस ret;

	val = (val & ~mask) | bits;

	ret = regmap_ग_लिखो(regmap, reg, val);
	अगर (ret)
		वापस ret;

	/*
	 * We need to रुको after writing beक्रमe we can ग_लिखो again. See the
	 * datasheet, page 93.
	 */
	usleep_range(ग_लिखो_usleep, ग_लिखो_usleep + 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक bmi160_config_pin(काष्ठा regmap *regmap, क्रमागत bmi160_पूर्णांक_pin pin,
			     bool खोलो_drain, u8 irq_mask,
			     अचिन्हित दीर्घ ग_लिखो_usleep)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = regmap_get_device(regmap);
	u8 पूर्णांक_out_ctrl_shअगरt;
	u8 पूर्णांक_latch_mask;
	u8 पूर्णांक_map_mask;
	u8 पूर्णांक_out_ctrl_mask;
	u8 पूर्णांक_out_ctrl_bits;
	स्थिर अक्षर *pin_name;

	चयन (pin) अणु
	हाल BMI160_PIN_INT1:
		पूर्णांक_out_ctrl_shअगरt = BMI160_INT1_OUT_CTRL_SHIFT;
		पूर्णांक_latch_mask = BMI160_INT1_LATCH_MASK;
		पूर्णांक_map_mask = BMI160_INT1_MAP_DRDY_EN;
		अवरोध;
	हाल BMI160_PIN_INT2:
		पूर्णांक_out_ctrl_shअगरt = BMI160_INT2_OUT_CTRL_SHIFT;
		पूर्णांक_latch_mask = BMI160_INT2_LATCH_MASK;
		पूर्णांक_map_mask = BMI160_INT2_MAP_DRDY_EN;
		अवरोध;
	पूर्ण
	पूर्णांक_out_ctrl_mask = BMI160_INT_OUT_CTRL_MASK << पूर्णांक_out_ctrl_shअगरt;

	/*
	 * Enable the requested pin with the right settings:
	 * - Push-pull/खोलो-drain
	 * - Active low/high
	 * - Edge/level triggered
	 */
	पूर्णांक_out_ctrl_bits = BMI160_OUTPUT_EN;
	अगर (खोलो_drain)
		/* Default is push-pull. */
		पूर्णांक_out_ctrl_bits |= BMI160_OPEN_DRAIN;
	पूर्णांक_out_ctrl_bits |= irq_mask;
	पूर्णांक_out_ctrl_bits <<= पूर्णांक_out_ctrl_shअगरt;

	ret = bmi160_ग_लिखो_conf_reg(regmap, BMI160_REG_INT_OUT_CTRL,
				    पूर्णांक_out_ctrl_mask, पूर्णांक_out_ctrl_bits,
				    ग_लिखो_usleep);
	अगर (ret)
		वापस ret;

	/* Set the pin to input mode with no latching. */
	ret = bmi160_ग_लिखो_conf_reg(regmap, BMI160_REG_INT_LATCH,
				    पूर्णांक_latch_mask, पूर्णांक_latch_mask,
				    ग_लिखो_usleep);
	अगर (ret)
		वापस ret;

	/* Map पूर्णांकerrupts to the requested pin. */
	ret = bmi160_ग_लिखो_conf_reg(regmap, BMI160_REG_INT_MAP,
				    पूर्णांक_map_mask, पूर्णांक_map_mask,
				    ग_लिखो_usleep);
	अगर (ret) अणु
		चयन (pin) अणु
		हाल BMI160_PIN_INT1:
			pin_name = "INT1";
			अवरोध;
		हाल BMI160_PIN_INT2:
			pin_name = "INT2";
			अवरोध;
		पूर्ण
		dev_err(dev, "Failed to configure %s IRQ pin", pin_name);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक bmi160_enable_irq(काष्ठा regmap *regmap, bool enable)
अणु
	अचिन्हित पूर्णांक enable_bit = 0;

	अगर (enable)
		enable_bit = BMI160_DRDY_INT_EN;

	वापस bmi160_ग_लिखो_conf_reg(regmap, BMI160_REG_INT_EN,
				     BMI160_DRDY_INT_EN, enable_bit,
				     BMI160_NORMAL_WRITE_USLEEP);
पूर्ण
EXPORT_SYMBOL(bmi160_enable_irq);

अटल पूर्णांक bmi160_get_irq(काष्ठा device_node *of_node, क्रमागत bmi160_पूर्णांक_pin *pin)
अणु
	पूर्णांक irq;

	/* Use INT1 अगर possible, otherwise fall back to INT2. */
	irq = of_irq_get_byname(of_node, "INT1");
	अगर (irq > 0) अणु
		*pin = BMI160_PIN_INT1;
		वापस irq;
	पूर्ण

	irq = of_irq_get_byname(of_node, "INT2");
	अगर (irq > 0)
		*pin = BMI160_PIN_INT2;

	वापस irq;
पूर्ण

अटल पूर्णांक bmi160_config_device_irq(काष्ठा iio_dev *indio_dev, पूर्णांक irq_type,
				    क्रमागत bmi160_पूर्णांक_pin pin)
अणु
	bool खोलो_drain;
	u8 irq_mask;
	काष्ठा bmi160_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(data->regmap);

	/* Level-triggered, active-low is the शेष अगर we set all zeroes. */
	अगर (irq_type == IRQF_TRIGGER_RISING)
		irq_mask = BMI160_ACTIVE_HIGH | BMI160_EDGE_TRIGGERED;
	अन्यथा अगर (irq_type == IRQF_TRIGGER_FALLING)
		irq_mask = BMI160_EDGE_TRIGGERED;
	अन्यथा अगर (irq_type == IRQF_TRIGGER_HIGH)
		irq_mask = BMI160_ACTIVE_HIGH;
	अन्यथा अगर (irq_type == IRQF_TRIGGER_LOW)
		irq_mask = 0;
	अन्यथा अणु
		dev_err(&indio_dev->dev,
			"Invalid interrupt type 0x%x specified\n", irq_type);
		वापस -EINVAL;
	पूर्ण

	खोलो_drain = of_property_पढ़ो_bool(dev->of_node, "drive-open-drain");

	वापस bmi160_config_pin(data->regmap, pin, खोलो_drain, irq_mask,
				 BMI160_NORMAL_WRITE_USLEEP);
पूर्ण

अटल पूर्णांक bmi160_setup_irq(काष्ठा iio_dev *indio_dev, पूर्णांक irq,
			    क्रमागत bmi160_पूर्णांक_pin pin)
अणु
	काष्ठा irq_data *desc;
	u32 irq_type;
	पूर्णांक ret;

	desc = irq_get_irq_data(irq);
	अगर (!desc) अणु
		dev_err(&indio_dev->dev, "Could not find IRQ %d\n", irq);
		वापस -EINVAL;
	पूर्ण

	irq_type = irqd_get_trigger_type(desc);

	ret = bmi160_config_device_irq(indio_dev, irq_type, pin);
	अगर (ret)
		वापस ret;

	वापस bmi160_probe_trigger(indio_dev, irq, irq_type);
पूर्ण

अटल पूर्णांक bmi160_chip_init(काष्ठा bmi160_data *data, bool use_spi)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा device *dev = regmap_get_device(data->regmap);

	ret = regulator_bulk_enable(ARRAY_SIZE(data->supplies), data->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, BMI160_REG_CMD, BMI160_CMD_SOFTRESET);
	अगर (ret)
		वापस ret;

	usleep_range(BMI160_SOFTRESET_USLEEP, BMI160_SOFTRESET_USLEEP + 1);

	/*
	 * CS rising edge is needed beक्रमe starting SPI, so करो a dummy पढ़ो
	 * See Section 3.2.1, page 86 of the datasheet
	 */
	अगर (use_spi) अणु
		ret = regmap_पढ़ो(data->regmap, BMI160_REG_DUMMY, &val);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, BMI160_REG_CHIP_ID, &val);
	अगर (ret) अणु
		dev_err(dev, "Error reading chip id\n");
		वापस ret;
	पूर्ण
	अगर (val != BMI160_CHIP_ID_VAL) अणु
		dev_err(dev, "Wrong chip id, got %x expected %x\n",
			val, BMI160_CHIP_ID_VAL);
		वापस -ENODEV;
	पूर्ण

	ret = bmi160_set_mode(data, BMI160_ACCEL, true);
	अगर (ret)
		वापस ret;

	ret = bmi160_set_mode(data, BMI160_GYRO, true);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक bmi160_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
					     bool enable)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा bmi160_data *data = iio_priv(indio_dev);

	वापस bmi160_enable_irq(data->regmap, enable);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops bmi160_trigger_ops = अणु
	.set_trigger_state = &bmi160_data_rdy_trigger_set_state,
पूर्ण;

पूर्णांक bmi160_probe_trigger(काष्ठा iio_dev *indio_dev, पूर्णांक irq, u32 irq_type)
अणु
	काष्ठा bmi160_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	data->trig = devm_iio_trigger_alloc(&indio_dev->dev, "%s-dev%d",
					    indio_dev->name, indio_dev->id);

	अगर (data->trig == शून्य)
		वापस -ENOMEM;

	ret = devm_request_irq(&indio_dev->dev, irq,
			       &iio_trigger_generic_data_rdy_poll,
			       irq_type, "bmi160", data->trig);
	अगर (ret)
		वापस ret;

	data->trig->dev.parent = regmap_get_device(data->regmap);
	data->trig->ops = &bmi160_trigger_ops;
	iio_trigger_set_drvdata(data->trig, indio_dev);

	ret = devm_iio_trigger_रेजिस्टर(&indio_dev->dev, data->trig);
	अगर (ret)
		वापस ret;

	indio_dev->trig = iio_trigger_get(data->trig);

	वापस 0;
पूर्ण

अटल व्योम bmi160_chip_uninit(व्योम *data)
अणु
	काष्ठा bmi160_data *bmi_data = data;
	काष्ठा device *dev = regmap_get_device(bmi_data->regmap);
	पूर्णांक ret;

	bmi160_set_mode(bmi_data, BMI160_GYRO, false);
	bmi160_set_mode(bmi_data, BMI160_ACCEL, false);

	ret = regulator_bulk_disable(ARRAY_SIZE(bmi_data->supplies),
				     bmi_data->supplies);
	अगर (ret)
		dev_err(dev, "Failed to disable regulators: %d\n", ret);
पूर्ण

पूर्णांक bmi160_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		      स्थिर अक्षर *name, bool use_spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा bmi160_data *data;
	पूर्णांक irq;
	क्रमागत bmi160_पूर्णांक_pin पूर्णांक_pin;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->regmap = regmap;

	data->supplies[0].supply = "vdd";
	data->supplies[1].supply = "vddio";
	ret = devm_regulator_bulk_get(dev,
				      ARRAY_SIZE(data->supplies),
				      data->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to get regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix",
				    &data->orientation);
	अगर (ret)
		वापस ret;

	ret = bmi160_chip_init(data, use_spi);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, bmi160_chip_uninit, data);
	अगर (ret)
		वापस ret;

	अगर (!name && ACPI_HANDLE(dev))
		name = bmi160_match_acpi_device(dev);

	indio_dev->channels = bmi160_channels;
	indio_dev->num_channels = ARRAY_SIZE(bmi160_channels);
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &bmi160_info;

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
					      iio_pollfunc_store_समय,
					      bmi160_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	irq = bmi160_get_irq(dev->of_node, &पूर्णांक_pin);
	अगर (irq > 0) अणु
		ret = bmi160_setup_irq(indio_dev, irq, पूर्णांक_pin);
		अगर (ret)
			dev_err(&indio_dev->dev, "Failed to setup IRQ %d\n",
				irq);
	पूर्ण अन्यथा अणु
		dev_info(&indio_dev->dev, "Not setting up IRQ trigger\n");
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण
EXPORT_SYMBOL_GPL(bmi160_core_probe);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("Bosch BMI160 driver");
MODULE_LICENSE("GPL v2");
