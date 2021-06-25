<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Analog Devices LTC2983 Multi-Sensor Digital Temperature Measurement System
 * driver
 *
 * Copyright 2019 Analog Devices Inc.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

/* रेजिस्टर map */
#घोषणा LTC2983_STATUS_REG			0x0000
#घोषणा LTC2983_TEMP_RES_START_REG		0x0010
#घोषणा LTC2983_TEMP_RES_END_REG		0x005F
#घोषणा LTC2983_GLOBAL_CONFIG_REG		0x00F0
#घोषणा LTC2983_MULT_CHANNEL_START_REG		0x00F4
#घोषणा LTC2983_MULT_CHANNEL_END_REG		0x00F7
#घोषणा LTC2983_MUX_CONFIG_REG			0x00FF
#घोषणा LTC2983_CHAN_ASSIGN_START_REG		0x0200
#घोषणा LTC2983_CHAN_ASSIGN_END_REG		0x024F
#घोषणा LTC2983_CUST_SENS_TBL_START_REG		0x0250
#घोषणा LTC2983_CUST_SENS_TBL_END_REG		0x03CF

#घोषणा LTC2983_DIFFERENTIAL_CHAN_MIN		2
#घोषणा LTC2983_MAX_CHANNELS_NR			20
#घोषणा LTC2983_MIN_CHANNELS_NR			1
#घोषणा LTC2983_SLEEP				0x97
#घोषणा LTC2983_CUSTOM_STEINHART_SIZE		24
#घोषणा LTC2983_CUSTOM_SENSOR_ENTRY_SZ		6
#घोषणा LTC2983_CUSTOM_STEINHART_ENTRY_SZ	4

#घोषणा LTC2983_CHAN_START_ADDR(chan) \
			(((chan - 1) * 4) + LTC2983_CHAN_ASSIGN_START_REG)
#घोषणा LTC2983_CHAN_RES_ADDR(chan) \
			(((chan - 1) * 4) + LTC2983_TEMP_RES_START_REG)
#घोषणा LTC2983_THERMOCOUPLE_DIFF_MASK		BIT(3)
#घोषणा LTC2983_THERMOCOUPLE_SGL(x) \
				FIELD_PREP(LTC2983_THERMOCOUPLE_DIFF_MASK, x)
#घोषणा LTC2983_THERMOCOUPLE_OC_CURR_MASK	GENMASK(1, 0)
#घोषणा LTC2983_THERMOCOUPLE_OC_CURR(x) \
				FIELD_PREP(LTC2983_THERMOCOUPLE_OC_CURR_MASK, x)
#घोषणा LTC2983_THERMOCOUPLE_OC_CHECK_MASK	BIT(2)
#घोषणा LTC2983_THERMOCOUPLE_OC_CHECK(x) \
			FIELD_PREP(LTC2983_THERMOCOUPLE_OC_CHECK_MASK, x)

#घोषणा LTC2983_THERMISTOR_DIFF_MASK		BIT(2)
#घोषणा LTC2983_THERMISTOR_SGL(x) \
				FIELD_PREP(LTC2983_THERMISTOR_DIFF_MASK, x)
#घोषणा LTC2983_THERMISTOR_R_SHARE_MASK		BIT(1)
#घोषणा LTC2983_THERMISTOR_R_SHARE(x) \
				FIELD_PREP(LTC2983_THERMISTOR_R_SHARE_MASK, x)
#घोषणा LTC2983_THERMISTOR_C_ROTATE_MASK	BIT(0)
#घोषणा LTC2983_THERMISTOR_C_ROTATE(x) \
				FIELD_PREP(LTC2983_THERMISTOR_C_ROTATE_MASK, x)

#घोषणा LTC2983_DIODE_DIFF_MASK			BIT(2)
#घोषणा LTC2983_DIODE_SGL(x) \
			FIELD_PREP(LTC2983_DIODE_DIFF_MASK, x)
#घोषणा LTC2983_DIODE_3_CONV_CYCLE_MASK		BIT(1)
#घोषणा LTC2983_DIODE_3_CONV_CYCLE(x) \
				FIELD_PREP(LTC2983_DIODE_3_CONV_CYCLE_MASK, x)
#घोषणा LTC2983_DIODE_AVERAGE_ON_MASK		BIT(0)
#घोषणा LTC2983_DIODE_AVERAGE_ON(x) \
				FIELD_PREP(LTC2983_DIODE_AVERAGE_ON_MASK, x)

#घोषणा LTC2983_RTD_4_WIRE_MASK			BIT(3)
#घोषणा LTC2983_RTD_ROTATION_MASK		BIT(1)
#घोषणा LTC2983_RTD_C_ROTATE(x) \
			FIELD_PREP(LTC2983_RTD_ROTATION_MASK, x)
#घोषणा LTC2983_RTD_KELVIN_R_SENSE_MASK		GENMASK(3, 2)
#घोषणा LTC2983_RTD_N_WIRES_MASK		GENMASK(3, 2)
#घोषणा LTC2983_RTD_N_WIRES(x) \
			FIELD_PREP(LTC2983_RTD_N_WIRES_MASK, x)
#घोषणा LTC2983_RTD_R_SHARE_MASK		BIT(0)
#घोषणा LTC2983_RTD_R_SHARE(x) \
			FIELD_PREP(LTC2983_RTD_R_SHARE_MASK, 1)

#घोषणा LTC2983_COMMON_HARD_FAULT_MASK	GENMASK(31, 30)
#घोषणा LTC2983_COMMON_SOFT_FAULT_MASK	GENMASK(27, 25)

#घोषणा	LTC2983_STATUS_START_MASK	BIT(7)
#घोषणा	LTC2983_STATUS_START(x)		FIELD_PREP(LTC2983_STATUS_START_MASK, x)

#घोषणा	LTC2983_STATUS_CHAN_SEL_MASK	GENMASK(4, 0)
#घोषणा	LTC2983_STATUS_CHAN_SEL(x) \
				FIELD_PREP(LTC2983_STATUS_CHAN_SEL_MASK, x)

#घोषणा LTC2983_TEMP_UNITS_MASK		BIT(2)
#घोषणा LTC2983_TEMP_UNITS(x)		FIELD_PREP(LTC2983_TEMP_UNITS_MASK, x)

#घोषणा LTC2983_NOTCH_FREQ_MASK		GENMASK(1, 0)
#घोषणा LTC2983_NOTCH_FREQ(x)		FIELD_PREP(LTC2983_NOTCH_FREQ_MASK, x)

#घोषणा LTC2983_RES_VALID_MASK		BIT(24)
#घोषणा LTC2983_DATA_MASK		GENMASK(23, 0)
#घोषणा LTC2983_DATA_SIGN_BIT		23

#घोषणा LTC2983_CHAN_TYPE_MASK		GENMASK(31, 27)
#घोषणा LTC2983_CHAN_TYPE(x)		FIELD_PREP(LTC2983_CHAN_TYPE_MASK, x)

/* cold junction क्रम thermocouples and rsense क्रम rtd's and thermistor's */
#घोषणा LTC2983_CHAN_ASSIGN_MASK	GENMASK(26, 22)
#घोषणा LTC2983_CHAN_ASSIGN(x)		FIELD_PREP(LTC2983_CHAN_ASSIGN_MASK, x)

#घोषणा LTC2983_CUSTOM_LEN_MASK		GENMASK(5, 0)
#घोषणा LTC2983_CUSTOM_LEN(x)		FIELD_PREP(LTC2983_CUSTOM_LEN_MASK, x)

#घोषणा LTC2983_CUSTOM_ADDR_MASK	GENMASK(11, 6)
#घोषणा LTC2983_CUSTOM_ADDR(x)		FIELD_PREP(LTC2983_CUSTOM_ADDR_MASK, x)

#घोषणा LTC2983_THERMOCOUPLE_CFG_MASK	GENMASK(21, 18)
#घोषणा LTC2983_THERMOCOUPLE_CFG(x) \
				FIELD_PREP(LTC2983_THERMOCOUPLE_CFG_MASK, x)
#घोषणा LTC2983_THERMOCOUPLE_HARD_FAULT_MASK	GENMASK(31, 29)
#घोषणा LTC2983_THERMOCOUPLE_SOFT_FAULT_MASK	GENMASK(28, 25)

#घोषणा LTC2983_RTD_CFG_MASK		GENMASK(21, 18)
#घोषणा LTC2983_RTD_CFG(x)		FIELD_PREP(LTC2983_RTD_CFG_MASK, x)
#घोषणा LTC2983_RTD_EXC_CURRENT_MASK	GENMASK(17, 14)
#घोषणा LTC2983_RTD_EXC_CURRENT(x) \
				FIELD_PREP(LTC2983_RTD_EXC_CURRENT_MASK, x)
#घोषणा LTC2983_RTD_CURVE_MASK		GENMASK(13, 12)
#घोषणा LTC2983_RTD_CURVE(x)		FIELD_PREP(LTC2983_RTD_CURVE_MASK, x)

#घोषणा LTC2983_THERMISTOR_CFG_MASK	GENMASK(21, 19)
#घोषणा LTC2983_THERMISTOR_CFG(x) \
				FIELD_PREP(LTC2983_THERMISTOR_CFG_MASK, x)
#घोषणा LTC2983_THERMISTOR_EXC_CURRENT_MASK	GENMASK(18, 15)
#घोषणा LTC2983_THERMISTOR_EXC_CURRENT(x) \
			FIELD_PREP(LTC2983_THERMISTOR_EXC_CURRENT_MASK, x)

#घोषणा LTC2983_DIODE_CFG_MASK		GENMASK(26, 24)
#घोषणा LTC2983_DIODE_CFG(x)		FIELD_PREP(LTC2983_DIODE_CFG_MASK, x)
#घोषणा LTC2983_DIODE_EXC_CURRENT_MASK	GENMASK(23, 22)
#घोषणा LTC2983_DIODE_EXC_CURRENT(x) \
				FIELD_PREP(LTC2983_DIODE_EXC_CURRENT_MASK, x)
#घोषणा LTC2983_DIODE_IDEAL_FACTOR_MASK	GENMASK(21, 0)
#घोषणा LTC2983_DIODE_IDEAL_FACTOR(x) \
				FIELD_PREP(LTC2983_DIODE_IDEAL_FACTOR_MASK, x)

#घोषणा LTC2983_R_SENSE_VAL_MASK	GENMASK(26, 0)
#घोषणा LTC2983_R_SENSE_VAL(x)		FIELD_PREP(LTC2983_R_SENSE_VAL_MASK, x)

#घोषणा LTC2983_ADC_SINGLE_ENDED_MASK	BIT(26)
#घोषणा LTC2983_ADC_SINGLE_ENDED(x) \
				FIELD_PREP(LTC2983_ADC_SINGLE_ENDED_MASK, x)

क्रमागत अणु
	LTC2983_SENSOR_THERMOCOUPLE = 1,
	LTC2983_SENSOR_THERMOCOUPLE_CUSTOM = 9,
	LTC2983_SENSOR_RTD = 10,
	LTC2983_SENSOR_RTD_CUSTOM = 18,
	LTC2983_SENSOR_THERMISTOR = 19,
	LTC2983_SENSOR_THERMISTOR_STEINHART = 26,
	LTC2983_SENSOR_THERMISTOR_CUSTOM = 27,
	LTC2983_SENSOR_DIODE = 28,
	LTC2983_SENSOR_SENSE_RESISTOR = 29,
	LTC2983_SENSOR_सूचीECT_ADC = 30,
पूर्ण;

#घोषणा to_thermocouple(_sensor) \
		container_of(_sensor, काष्ठा ltc2983_thermocouple, sensor)

#घोषणा to_rtd(_sensor) \
		container_of(_sensor, काष्ठा ltc2983_rtd, sensor)

#घोषणा to_thermistor(_sensor) \
		container_of(_sensor, काष्ठा ltc2983_thermistor, sensor)

#घोषणा to_diode(_sensor) \
		container_of(_sensor, काष्ठा ltc2983_diode, sensor)

#घोषणा to_rsense(_sensor) \
		container_of(_sensor, काष्ठा ltc2983_rsense, sensor)

#घोषणा to_adc(_sensor) \
		container_of(_sensor, काष्ठा ltc2983_adc, sensor)

काष्ठा ltc2983_data अणु
	काष्ठा regmap *regmap;
	काष्ठा spi_device *spi;
	काष्ठा mutex lock;
	काष्ठा completion completion;
	काष्ठा iio_chan_spec *iio_chan;
	काष्ठा ltc2983_sensor **sensors;
	u32 mux_delay_config;
	u32 filter_notch_freq;
	u16 custom_table_size;
	u8 num_channels;
	u8 iio_channels;
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 * Holds the converted temperature
	 */
	__be32 temp ____cacheline_aligned;
पूर्ण;

काष्ठा ltc2983_sensor अणु
	पूर्णांक (*fault_handler)(स्थिर काष्ठा ltc2983_data *st, स्थिर u32 result);
	पूर्णांक (*assign_chan)(काष्ठा ltc2983_data *st,
			   स्थिर काष्ठा ltc2983_sensor *sensor);
	/* specअगरies the sensor channel */
	u32 chan;
	/* sensor type */
	u32 type;
पूर्ण;

काष्ठा ltc2983_custom_sensor अणु
	/* raw table sensor data */
	u8 *table;
	माप_प्रकार size;
	/* address offset */
	s8 offset;
	bool is_steinhart;
पूर्ण;

काष्ठा ltc2983_thermocouple अणु
	काष्ठा ltc2983_sensor sensor;
	काष्ठा ltc2983_custom_sensor *custom;
	u32 sensor_config;
	u32 cold_junction_chan;
पूर्ण;

काष्ठा ltc2983_rtd अणु
	काष्ठा ltc2983_sensor sensor;
	काष्ठा ltc2983_custom_sensor *custom;
	u32 sensor_config;
	u32 r_sense_chan;
	u32 excitation_current;
	u32 rtd_curve;
पूर्ण;

काष्ठा ltc2983_thermistor अणु
	काष्ठा ltc2983_sensor sensor;
	काष्ठा ltc2983_custom_sensor *custom;
	u32 sensor_config;
	u32 r_sense_chan;
	u32 excitation_current;
पूर्ण;

काष्ठा ltc2983_diode अणु
	काष्ठा ltc2983_sensor sensor;
	u32 sensor_config;
	u32 excitation_current;
	u32 ideal_factor_value;
पूर्ण;

काष्ठा ltc2983_rsense अणु
	काष्ठा ltc2983_sensor sensor;
	u32 r_sense_val;
पूर्ण;

काष्ठा ltc2983_adc अणु
	काष्ठा ltc2983_sensor sensor;
	bool single_ended;
पूर्ण;

/*
 * Convert to Q क्रमmat numbers. These number's are पूर्णांकegers where
 * the number of पूर्णांकeger and fractional bits are specअगरied. The resolution
 * is given by 1/@resolution and tell us the number of fractional bits. For
 * instance a resolution of 2^-10 means we have 10 fractional bits.
 */
अटल u32 __convert_to_raw(स्थिर u64 val, स्थिर u32 resolution)
अणु
	u64 __res = val * resolution;

	/* all values are multiplied by 1000000 to हटाओ the fraction */
	करो_भाग(__res, 1000000);

	वापस __res;
पूर्ण

अटल u32 __convert_to_raw_sign(स्थिर u64 val, स्थिर u32 resolution)
अणु
	s64 __res = -(s32)val;

	__res = __convert_to_raw(__res, resolution);

	वापस (u32)-__res;
पूर्ण

अटल पूर्णांक __ltc2983_fault_handler(स्थिर काष्ठा ltc2983_data *st,
				   स्थिर u32 result, स्थिर u32 hard_mask,
				   स्थिर u32 soft_mask)
अणु
	स्थिर काष्ठा device *dev = &st->spi->dev;

	अगर (result & hard_mask) अणु
		dev_err(dev, "Invalid conversion: Sensor HARD fault\n");
		वापस -EIO;
	पूर्ण अन्यथा अगर (result & soft_mask) अणु
		/* just prपूर्णांक a warning */
		dev_warn(dev, "Suspicious conversion: Sensor SOFT fault\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __ltc2983_chan_assign_common(स्थिर काष्ठा ltc2983_data *st,
					स्थिर काष्ठा ltc2983_sensor *sensor,
					u32 chan_val)
अणु
	u32 reg = LTC2983_CHAN_START_ADDR(sensor->chan);
	__be32 __chan_val;

	chan_val |= LTC2983_CHAN_TYPE(sensor->type);
	dev_dbg(&st->spi->dev, "Assign reg:0x%04X, val:0x%08X\n", reg,
		chan_val);
	__chan_val = cpu_to_be32(chan_val);
	वापस regmap_bulk_ग_लिखो(st->regmap, reg, &__chan_val,
				 माप(__chan_val));
पूर्ण

अटल पूर्णांक __ltc2983_chan_custom_sensor_assign(काष्ठा ltc2983_data *st,
					  काष्ठा ltc2983_custom_sensor *custom,
					  u32 *chan_val)
अणु
	u32 reg;
	u8 mult = custom->is_steinhart ? LTC2983_CUSTOM_STEINHART_ENTRY_SZ :
		LTC2983_CUSTOM_SENSOR_ENTRY_SZ;
	स्थिर काष्ठा device *dev = &st->spi->dev;
	/*
	 * custom->size holds the raw size of the table. However, when
	 * configuring the sensor channel, we must ग_लिखो the number of
	 * entries of the table minus 1. For steinhart sensors 0 is written
	 * since the size is स्थिरant!
	 */
	स्थिर u8 len = custom->is_steinhart ? 0 :
		(custom->size / LTC2983_CUSTOM_SENSOR_ENTRY_SZ) - 1;
	/*
	 * Check अगर the offset was asचिन्हित alपढ़ोy. It should be क्रम steinhart
	 * sensors. When coming from sleep, it should be asचिन्हित क्रम all.
	 */
	अगर (custom->offset < 0) अणु
		/*
		 * This needs to be करोne again here because, from the moment
		 * when this test was करोne (successfully) क्रम this custom
		 * sensor, a steinhart sensor might have been added changing
		 * custom_table_size...
		 */
		अगर (st->custom_table_size + custom->size >
		    (LTC2983_CUST_SENS_TBL_END_REG -
		     LTC2983_CUST_SENS_TBL_START_REG) + 1) अणु
			dev_err(dev,
				"Not space left(%d) for new custom sensor(%zu)",
				st->custom_table_size,
				custom->size);
			वापस -EINVAL;
		पूर्ण

		custom->offset = st->custom_table_size /
					LTC2983_CUSTOM_SENSOR_ENTRY_SZ;
		st->custom_table_size += custom->size;
	पूर्ण

	reg = (custom->offset * mult) + LTC2983_CUST_SENS_TBL_START_REG;

	*chan_val |= LTC2983_CUSTOM_LEN(len);
	*chan_val |= LTC2983_CUSTOM_ADDR(custom->offset);
	dev_dbg(dev, "Assign custom sensor, reg:0x%04X, off:%d, sz:%zu",
		reg, custom->offset,
		custom->size);
	/* ग_लिखो custom sensor table */
	वापस regmap_bulk_ग_लिखो(st->regmap, reg, custom->table, custom->size);
पूर्ण

अटल काष्ठा ltc2983_custom_sensor *__ltc2983_custom_sensor_new(
						काष्ठा ltc2983_data *st,
						स्थिर काष्ठा device_node *np,
						स्थिर अक्षर *propname,
						स्थिर bool is_steinhart,
						स्थिर u32 resolution,
						स्थिर bool has_चिन्हित)
अणु
	काष्ठा ltc2983_custom_sensor *new_custom;
	u8 index, n_entries, tbl = 0;
	काष्ठा device *dev = &st->spi->dev;
	/*
	 * For custom steinhart, the full u32 is taken. For all the others
	 * the MSB is discarded.
	 */
	स्थिर u8 n_size = is_steinhart ? 4 : 3;
	स्थिर u8 e_size = is_steinhart ? माप(u32) : माप(u64);

	n_entries = of_property_count_elems_of_size(np, propname, e_size);
	/* n_entries must be an even number */
	अगर (!n_entries || (n_entries % 2) != 0) अणु
		dev_err(dev, "Number of entries either 0 or not even\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	new_custom = devm_kzalloc(dev, माप(*new_custom), GFP_KERNEL);
	अगर (!new_custom)
		वापस ERR_PTR(-ENOMEM);

	new_custom->size = n_entries * n_size;
	/* check Steinhart size */
	अगर (is_steinhart && new_custom->size != LTC2983_CUSTOM_STEINHART_SIZE) अणु
		dev_err(dev, "Steinhart sensors size(%zu) must be 24",
							new_custom->size);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	/* Check space on the table. */
	अगर (st->custom_table_size + new_custom->size >
	    (LTC2983_CUST_SENS_TBL_END_REG -
	     LTC2983_CUST_SENS_TBL_START_REG) + 1) अणु
		dev_err(dev, "No space left(%d) for new custom sensor(%zu)",
				st->custom_table_size, new_custom->size);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* allocate the table */
	new_custom->table = devm_kzalloc(dev, new_custom->size, GFP_KERNEL);
	अगर (!new_custom->table)
		वापस ERR_PTR(-ENOMEM);

	क्रम (index = 0; index < n_entries; index++) अणु
		u64 temp = 0, j;
		/*
		 * Steinhart sensors are configured with raw values in the
		 * devicetree. For the other sensors we must convert the
		 * value to raw. The odd index's correspond to temperarures
		 * and always have 1/1024 of resolution. Temperatures also
		 * come in kelvin, so चिन्हित values is not possible
		 */
		अगर (!is_steinhart) अणु
			of_property_पढ़ो_u64_index(np, propname, index, &temp);

			अगर ((index % 2) != 0)
				temp = __convert_to_raw(temp, 1024);
			अन्यथा अगर (has_चिन्हित && (s64)temp < 0)
				temp = __convert_to_raw_sign(temp, resolution);
			अन्यथा
				temp = __convert_to_raw(temp, resolution);
		पूर्ण अन्यथा अणु
			u32 t32;

			of_property_पढ़ो_u32_index(np, propname, index, &t32);
			temp = t32;
		पूर्ण

		क्रम (j = 0; j < n_size; j++)
			new_custom->table[tbl++] =
				temp >> (8 * (n_size - j - 1));
	पूर्ण

	new_custom->is_steinhart = is_steinhart;
	/*
	 * This is करोne to first add all the steinhart sensors to the table,
	 * in order to maximize the table usage. If we mix adding steinhart
	 * with the other sensors, we might have to करो some roundup to make
	 * sure that sensor_addr - 0x250(start address) is a multiple of 4
	 * (क्रम steinhart), and a multiple of 6 क्रम all the other sensors.
	 * Since we have स्थिर 24 bytes क्रम steinhart sensors and 24 is
	 * also a multiple of 6, we guarantee that the first non-steinhart
	 * sensor will sit in a correct address without the need of filling
	 * addresses.
	 */
	अगर (is_steinhart) अणु
		new_custom->offset = st->custom_table_size /
					LTC2983_CUSTOM_STEINHART_ENTRY_SZ;
		st->custom_table_size += new_custom->size;
	पूर्ण अन्यथा अणु
		/* mark as unset. This is checked later on the assign phase */
		new_custom->offset = -1;
	पूर्ण

	वापस new_custom;
पूर्ण

अटल पूर्णांक ltc2983_thermocouple_fault_handler(स्थिर काष्ठा ltc2983_data *st,
					      स्थिर u32 result)
अणु
	वापस __ltc2983_fault_handler(st, result,
				       LTC2983_THERMOCOUPLE_HARD_FAULT_MASK,
				       LTC2983_THERMOCOUPLE_SOFT_FAULT_MASK);
पूर्ण

अटल पूर्णांक ltc2983_common_fault_handler(स्थिर काष्ठा ltc2983_data *st,
					स्थिर u32 result)
अणु
	वापस __ltc2983_fault_handler(st, result,
				       LTC2983_COMMON_HARD_FAULT_MASK,
				       LTC2983_COMMON_SOFT_FAULT_MASK);
पूर्ण

अटल पूर्णांक ltc2983_thermocouple_assign_chan(काष्ठा ltc2983_data *st,
				स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_thermocouple *thermo = to_thermocouple(sensor);
	u32 chan_val;

	chan_val = LTC2983_CHAN_ASSIGN(thermo->cold_junction_chan);
	chan_val |= LTC2983_THERMOCOUPLE_CFG(thermo->sensor_config);

	अगर (thermo->custom) अणु
		पूर्णांक ret;

		ret = __ltc2983_chan_custom_sensor_assign(st, thermo->custom,
							  &chan_val);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस __ltc2983_chan_assign_common(st, sensor, chan_val);
पूर्ण

अटल पूर्णांक ltc2983_rtd_assign_chan(काष्ठा ltc2983_data *st,
				   स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_rtd *rtd = to_rtd(sensor);
	u32 chan_val;

	chan_val = LTC2983_CHAN_ASSIGN(rtd->r_sense_chan);
	chan_val |= LTC2983_RTD_CFG(rtd->sensor_config);
	chan_val |= LTC2983_RTD_EXC_CURRENT(rtd->excitation_current);
	chan_val |= LTC2983_RTD_CURVE(rtd->rtd_curve);

	अगर (rtd->custom) अणु
		पूर्णांक ret;

		ret = __ltc2983_chan_custom_sensor_assign(st, rtd->custom,
							  &chan_val);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस __ltc2983_chan_assign_common(st, sensor, chan_val);
पूर्ण

अटल पूर्णांक ltc2983_thermistor_assign_chan(काष्ठा ltc2983_data *st,
					  स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_thermistor *thermistor = to_thermistor(sensor);
	u32 chan_val;

	chan_val = LTC2983_CHAN_ASSIGN(thermistor->r_sense_chan);
	chan_val |= LTC2983_THERMISTOR_CFG(thermistor->sensor_config);
	chan_val |=
		LTC2983_THERMISTOR_EXC_CURRENT(thermistor->excitation_current);

	अगर (thermistor->custom) अणु
		पूर्णांक ret;

		ret = __ltc2983_chan_custom_sensor_assign(st,
							  thermistor->custom,
							  &chan_val);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस __ltc2983_chan_assign_common(st, sensor, chan_val);
पूर्ण

अटल पूर्णांक ltc2983_diode_assign_chan(काष्ठा ltc2983_data *st,
				     स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_diode *diode = to_diode(sensor);
	u32 chan_val;

	chan_val = LTC2983_DIODE_CFG(diode->sensor_config);
	chan_val |= LTC2983_DIODE_EXC_CURRENT(diode->excitation_current);
	chan_val |= LTC2983_DIODE_IDEAL_FACTOR(diode->ideal_factor_value);

	वापस __ltc2983_chan_assign_common(st, sensor, chan_val);
पूर्ण

अटल पूर्णांक ltc2983_r_sense_assign_chan(काष्ठा ltc2983_data *st,
				       स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_rsense *rsense = to_rsense(sensor);
	u32 chan_val;

	chan_val = LTC2983_R_SENSE_VAL(rsense->r_sense_val);

	वापस __ltc2983_chan_assign_common(st, sensor, chan_val);
पूर्ण

अटल पूर्णांक ltc2983_adc_assign_chan(काष्ठा ltc2983_data *st,
				   स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_adc *adc = to_adc(sensor);
	u32 chan_val;

	chan_val = LTC2983_ADC_SINGLE_ENDED(adc->single_ended);

	वापस __ltc2983_chan_assign_common(st, sensor, chan_val);
पूर्ण

अटल काष्ठा ltc2983_sensor *ltc2983_thermocouple_new(
					स्थिर काष्ठा device_node *child,
					काष्ठा ltc2983_data *st,
					स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_thermocouple *thermo;
	काष्ठा device_node *phandle;
	u32 oc_current;
	पूर्णांक ret;

	thermo = devm_kzalloc(&st->spi->dev, माप(*thermo), GFP_KERNEL);
	अगर (!thermo)
		वापस ERR_PTR(-ENOMEM);

	अगर (of_property_पढ़ो_bool(child, "adi,single-ended"))
		thermo->sensor_config = LTC2983_THERMOCOUPLE_SGL(1);

	ret = of_property_पढ़ो_u32(child, "adi,sensor-oc-current-microamp",
				   &oc_current);
	अगर (!ret) अणु
		चयन (oc_current) अणु
		हाल 10:
			thermo->sensor_config |=
					LTC2983_THERMOCOUPLE_OC_CURR(0);
			अवरोध;
		हाल 100:
			thermo->sensor_config |=
					LTC2983_THERMOCOUPLE_OC_CURR(1);
			अवरोध;
		हाल 500:
			thermo->sensor_config |=
					LTC2983_THERMOCOUPLE_OC_CURR(2);
			अवरोध;
		हाल 1000:
			thermo->sensor_config |=
					LTC2983_THERMOCOUPLE_OC_CURR(3);
			अवरोध;
		शेष:
			dev_err(&st->spi->dev,
				"Invalid open circuit current:%u", oc_current);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		thermo->sensor_config |= LTC2983_THERMOCOUPLE_OC_CHECK(1);
	पूर्ण
	/* validate channel index */
	अगर (!(thermo->sensor_config & LTC2983_THERMOCOUPLE_DIFF_MASK) &&
	    sensor->chan < LTC2983_DIFFERENTIAL_CHAN_MIN) अणु
		dev_err(&st->spi->dev,
			"Invalid chann:%d for differential thermocouple",
			sensor->chan);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	phandle = of_parse_phandle(child, "adi,cold-junction-handle", 0);
	अगर (phandle) अणु
		पूर्णांक ret;

		ret = of_property_पढ़ो_u32(phandle, "reg",
					   &thermo->cold_junction_chan);
		अगर (ret) अणु
			/*
			 * This would be catched later but we can just वापस
			 * the error right away.
			 */
			dev_err(&st->spi->dev, "Property reg must be given\n");
			of_node_put(phandle);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	/* check custom sensor */
	अगर (sensor->type == LTC2983_SENSOR_THERMOCOUPLE_CUSTOM) अणु
		स्थिर अक्षर *propname = "adi,custom-thermocouple";

		thermo->custom = __ltc2983_custom_sensor_new(st, child,
							     propname, false,
							     16384, true);
		अगर (IS_ERR(thermo->custom)) अणु
			of_node_put(phandle);
			वापस ERR_CAST(thermo->custom);
		पूर्ण
	पूर्ण

	/* set common parameters */
	thermo->sensor.fault_handler = ltc2983_thermocouple_fault_handler;
	thermo->sensor.assign_chan = ltc2983_thermocouple_assign_chan;

	of_node_put(phandle);
	वापस &thermo->sensor;
पूर्ण

अटल काष्ठा ltc2983_sensor *ltc2983_rtd_new(स्थिर काष्ठा device_node *child,
					  काष्ठा ltc2983_data *st,
					  स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_rtd *rtd;
	पूर्णांक ret = 0;
	काष्ठा device *dev = &st->spi->dev;
	काष्ठा device_node *phandle;
	u32 excitation_current = 0, n_wires = 0;

	rtd = devm_kzalloc(dev, माप(*rtd), GFP_KERNEL);
	अगर (!rtd)
		वापस ERR_PTR(-ENOMEM);

	phandle = of_parse_phandle(child, "adi,rsense-handle", 0);
	अगर (!phandle) अणु
		dev_err(dev, "Property adi,rsense-handle missing or invalid");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ret = of_property_पढ़ो_u32(phandle, "reg", &rtd->r_sense_chan);
	अगर (ret) अणु
		dev_err(dev, "Property reg must be given\n");
		जाओ fail;
	पूर्ण

	ret = of_property_पढ़ो_u32(child, "adi,number-of-wires", &n_wires);
	अगर (!ret) अणु
		चयन (n_wires) अणु
		हाल 2:
			rtd->sensor_config = LTC2983_RTD_N_WIRES(0);
			अवरोध;
		हाल 3:
			rtd->sensor_config = LTC2983_RTD_N_WIRES(1);
			अवरोध;
		हाल 4:
			rtd->sensor_config = LTC2983_RTD_N_WIRES(2);
			अवरोध;
		हाल 5:
			/* 4 wires, Kelvin Rsense */
			rtd->sensor_config = LTC2983_RTD_N_WIRES(3);
			अवरोध;
		शेष:
			dev_err(dev, "Invalid number of wires:%u\n", n_wires);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_bool(child, "adi,rsense-share")) अणु
		/* Current rotation is only available with rsense sharing */
		अगर (of_property_पढ़ो_bool(child, "adi,current-rotate")) अणु
			अगर (n_wires == 2 || n_wires == 3) अणु
				dev_err(dev,
					"Rotation not allowed for 2/3 Wire RTDs");
				ret = -EINVAL;
				जाओ fail;
			पूर्ण
			rtd->sensor_config |= LTC2983_RTD_C_ROTATE(1);
		पूर्ण अन्यथा अणु
			rtd->sensor_config |= LTC2983_RTD_R_SHARE(1);
		पूर्ण
	पूर्ण
	/*
	 * rtd channel indexes are a bit more complicated to validate.
	 * For 4wire RTD with rotation, the channel selection cannot be
	 * >=19 since the chann + 1 is used in this configuration.
	 * For 4wire RTDs with kelvin rsense, the rsense channel cannot be
	 * <=1 since chanel - 1 and channel - 2 are used.
	 */
	अगर (rtd->sensor_config & LTC2983_RTD_4_WIRE_MASK) अणु
		/* 4-wire */
		u8 min = LTC2983_DIFFERENTIAL_CHAN_MIN,
			max = LTC2983_MAX_CHANNELS_NR;

		अगर (rtd->sensor_config & LTC2983_RTD_ROTATION_MASK)
			max = LTC2983_MAX_CHANNELS_NR - 1;

		अगर (((rtd->sensor_config & LTC2983_RTD_KELVIN_R_SENSE_MASK)
		     == LTC2983_RTD_KELVIN_R_SENSE_MASK) &&
		    (rtd->r_sense_chan <=  min)) अणु
			/* kelvin rsense*/
			dev_err(dev,
				"Invalid rsense chann:%d to use in kelvin rsense",
				rtd->r_sense_chan);

			ret = -EINVAL;
			जाओ fail;
		पूर्ण

		अगर (sensor->chan < min || sensor->chan > max) अणु
			dev_err(dev, "Invalid chann:%d for the rtd config",
				sensor->chan);

			ret = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* same as dअगरferential हाल */
		अगर (sensor->chan < LTC2983_DIFFERENTIAL_CHAN_MIN) अणु
			dev_err(&st->spi->dev,
				"Invalid chann:%d for RTD", sensor->chan);

			ret = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	/* check custom sensor */
	अगर (sensor->type == LTC2983_SENSOR_RTD_CUSTOM) अणु
		rtd->custom = __ltc2983_custom_sensor_new(st, child,
							  "adi,custom-rtd",
							  false, 2048, false);
		अगर (IS_ERR(rtd->custom)) अणु
			of_node_put(phandle);
			वापस ERR_CAST(rtd->custom);
		पूर्ण
	पूर्ण

	/* set common parameters */
	rtd->sensor.fault_handler = ltc2983_common_fault_handler;
	rtd->sensor.assign_chan = ltc2983_rtd_assign_chan;

	ret = of_property_पढ़ो_u32(child, "adi,excitation-current-microamp",
				   &excitation_current);
	अगर (ret) अणु
		/* शेष to 5uA */
		rtd->excitation_current = 1;
	पूर्ण अन्यथा अणु
		चयन (excitation_current) अणु
		हाल 5:
			rtd->excitation_current = 0x01;
			अवरोध;
		हाल 10:
			rtd->excitation_current = 0x02;
			अवरोध;
		हाल 25:
			rtd->excitation_current = 0x03;
			अवरोध;
		हाल 50:
			rtd->excitation_current = 0x04;
			अवरोध;
		हाल 100:
			rtd->excitation_current = 0x05;
			अवरोध;
		हाल 250:
			rtd->excitation_current = 0x06;
			अवरोध;
		हाल 500:
			rtd->excitation_current = 0x07;
			अवरोध;
		हाल 1000:
			rtd->excitation_current = 0x08;
			अवरोध;
		शेष:
			dev_err(&st->spi->dev,
				"Invalid value for excitation current(%u)",
				excitation_current);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	of_property_पढ़ो_u32(child, "adi,rtd-curve", &rtd->rtd_curve);

	of_node_put(phandle);
	वापस &rtd->sensor;
fail:
	of_node_put(phandle);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा ltc2983_sensor *ltc2983_thermistor_new(
					स्थिर काष्ठा device_node *child,
					काष्ठा ltc2983_data *st,
					स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_thermistor *thermistor;
	काष्ठा device *dev = &st->spi->dev;
	काष्ठा device_node *phandle;
	u32 excitation_current = 0;
	पूर्णांक ret = 0;

	thermistor = devm_kzalloc(dev, माप(*thermistor), GFP_KERNEL);
	अगर (!thermistor)
		वापस ERR_PTR(-ENOMEM);

	phandle = of_parse_phandle(child, "adi,rsense-handle", 0);
	अगर (!phandle) अणु
		dev_err(dev, "Property adi,rsense-handle missing or invalid");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ret = of_property_पढ़ो_u32(phandle, "reg", &thermistor->r_sense_chan);
	अगर (ret) अणु
		dev_err(dev, "rsense channel must be configured...\n");
		जाओ fail;
	पूर्ण

	अगर (of_property_पढ़ो_bool(child, "adi,single-ended")) अणु
		thermistor->sensor_config = LTC2983_THERMISTOR_SGL(1);
	पूर्ण अन्यथा अगर (of_property_पढ़ो_bool(child, "adi,rsense-share")) अणु
		/* rotation is only possible अगर sharing rsense */
		अगर (of_property_पढ़ो_bool(child, "adi,current-rotate"))
			thermistor->sensor_config =
						LTC2983_THERMISTOR_C_ROTATE(1);
		अन्यथा
			thermistor->sensor_config =
						LTC2983_THERMISTOR_R_SHARE(1);
	पूर्ण
	/* validate channel index */
	अगर (!(thermistor->sensor_config & LTC2983_THERMISTOR_DIFF_MASK) &&
	    sensor->chan < LTC2983_DIFFERENTIAL_CHAN_MIN) अणु
		dev_err(&st->spi->dev,
			"Invalid chann:%d for differential thermistor",
			sensor->chan);
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	/* check custom sensor */
	अगर (sensor->type >= LTC2983_SENSOR_THERMISTOR_STEINHART) अणु
		bool steinhart = false;
		स्थिर अक्षर *propname;

		अगर (sensor->type == LTC2983_SENSOR_THERMISTOR_STEINHART) अणु
			steinhart = true;
			propname = "adi,custom-steinhart";
		पूर्ण अन्यथा अणु
			propname = "adi,custom-thermistor";
		पूर्ण

		thermistor->custom = __ltc2983_custom_sensor_new(st, child,
								 propname,
								 steinhart,
								 64, false);
		अगर (IS_ERR(thermistor->custom)) अणु
			of_node_put(phandle);
			वापस ERR_CAST(thermistor->custom);
		पूर्ण
	पूर्ण
	/* set common parameters */
	thermistor->sensor.fault_handler = ltc2983_common_fault_handler;
	thermistor->sensor.assign_chan = ltc2983_thermistor_assign_chan;

	ret = of_property_पढ़ो_u32(child, "adi,excitation-current-nanoamp",
				   &excitation_current);
	अगर (ret) अणु
		/* Auto range is not allowed क्रम custom sensors */
		अगर (sensor->type >= LTC2983_SENSOR_THERMISTOR_STEINHART)
			/* शेष to 1uA */
			thermistor->excitation_current = 0x03;
		अन्यथा
			/* शेष to स्वतः-range */
			thermistor->excitation_current = 0x0c;
	पूर्ण अन्यथा अणु
		चयन (excitation_current) अणु
		हाल 0:
			/* स्वतः range */
			अगर (sensor->type >=
			    LTC2983_SENSOR_THERMISTOR_STEINHART) अणु
				dev_err(&st->spi->dev,
					"Auto Range not allowed for custom sensors\n");
				ret = -EINVAL;
				जाओ fail;
			पूर्ण
			thermistor->excitation_current = 0x0c;
			अवरोध;
		हाल 250:
			thermistor->excitation_current = 0x01;
			अवरोध;
		हाल 500:
			thermistor->excitation_current = 0x02;
			अवरोध;
		हाल 1000:
			thermistor->excitation_current = 0x03;
			अवरोध;
		हाल 5000:
			thermistor->excitation_current = 0x04;
			अवरोध;
		हाल 10000:
			thermistor->excitation_current = 0x05;
			अवरोध;
		हाल 25000:
			thermistor->excitation_current = 0x06;
			अवरोध;
		हाल 50000:
			thermistor->excitation_current = 0x07;
			अवरोध;
		हाल 100000:
			thermistor->excitation_current = 0x08;
			अवरोध;
		हाल 250000:
			thermistor->excitation_current = 0x09;
			अवरोध;
		हाल 500000:
			thermistor->excitation_current = 0x0a;
			अवरोध;
		हाल 1000000:
			thermistor->excitation_current = 0x0b;
			अवरोध;
		शेष:
			dev_err(&st->spi->dev,
				"Invalid value for excitation current(%u)",
				excitation_current);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	of_node_put(phandle);
	वापस &thermistor->sensor;
fail:
	of_node_put(phandle);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा ltc2983_sensor *ltc2983_diode_new(
					स्थिर काष्ठा device_node *child,
					स्थिर काष्ठा ltc2983_data *st,
					स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_diode *diode;
	u32 temp = 0, excitation_current = 0;
	पूर्णांक ret;

	diode = devm_kzalloc(&st->spi->dev, माप(*diode), GFP_KERNEL);
	अगर (!diode)
		वापस ERR_PTR(-ENOMEM);

	अगर (of_property_पढ़ो_bool(child, "adi,single-ended"))
		diode->sensor_config = LTC2983_DIODE_SGL(1);

	अगर (of_property_पढ़ो_bool(child, "adi,three-conversion-cycles"))
		diode->sensor_config |= LTC2983_DIODE_3_CONV_CYCLE(1);

	अगर (of_property_पढ़ो_bool(child, "adi,average-on"))
		diode->sensor_config |= LTC2983_DIODE_AVERAGE_ON(1);

	/* validate channel index */
	अगर (!(diode->sensor_config & LTC2983_DIODE_DIFF_MASK) &&
	    sensor->chan < LTC2983_DIFFERENTIAL_CHAN_MIN) अणु
		dev_err(&st->spi->dev,
			"Invalid chann:%d for differential thermistor",
			sensor->chan);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	/* set common parameters */
	diode->sensor.fault_handler = ltc2983_common_fault_handler;
	diode->sensor.assign_chan = ltc2983_diode_assign_chan;

	ret = of_property_पढ़ो_u32(child, "adi,excitation-current-microamp",
				   &excitation_current);
	अगर (!ret) अणु
		चयन (excitation_current) अणु
		हाल 10:
			diode->excitation_current = 0x00;
			अवरोध;
		हाल 20:
			diode->excitation_current = 0x01;
			अवरोध;
		हाल 40:
			diode->excitation_current = 0x02;
			अवरोध;
		हाल 80:
			diode->excitation_current = 0x03;
			अवरोध;
		शेष:
			dev_err(&st->spi->dev,
				"Invalid value for excitation current(%u)",
				excitation_current);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	of_property_पढ़ो_u32(child, "adi,ideal-factor-value", &temp);

	/* 2^20 resolution */
	diode->ideal_factor_value = __convert_to_raw(temp, 1048576);

	वापस &diode->sensor;
पूर्ण

अटल काष्ठा ltc2983_sensor *ltc2983_r_sense_new(काष्ठा device_node *child,
					काष्ठा ltc2983_data *st,
					स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_rsense *rsense;
	पूर्णांक ret;
	u32 temp;

	rsense = devm_kzalloc(&st->spi->dev, माप(*rsense), GFP_KERNEL);
	अगर (!rsense)
		वापस ERR_PTR(-ENOMEM);

	/* validate channel index */
	अगर (sensor->chan < LTC2983_DIFFERENTIAL_CHAN_MIN) अणु
		dev_err(&st->spi->dev, "Invalid chann:%d for r_sense",
			sensor->chan);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ret = of_property_पढ़ो_u32(child, "adi,rsense-val-milli-ohms", &temp);
	अगर (ret) अणु
		dev_err(&st->spi->dev, "Property adi,rsense-val-milli-ohms missing\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	/*
	 * Times 1000 because we have milli-ohms and __convert_to_raw
	 * expects scales of 1000000 which are used क्रम all other
	 * properties.
	 * 2^10 resolution
	 */
	rsense->r_sense_val = __convert_to_raw((u64)temp * 1000, 1024);

	/* set common parameters */
	rsense->sensor.assign_chan = ltc2983_r_sense_assign_chan;

	वापस &rsense->sensor;
पूर्ण

अटल काष्ठा ltc2983_sensor *ltc2983_adc_new(काष्ठा device_node *child,
					 काष्ठा ltc2983_data *st,
					 स्थिर काष्ठा ltc2983_sensor *sensor)
अणु
	काष्ठा ltc2983_adc *adc;

	adc = devm_kzalloc(&st->spi->dev, माप(*adc), GFP_KERNEL);
	अगर (!adc)
		वापस ERR_PTR(-ENOMEM);

	अगर (of_property_पढ़ो_bool(child, "adi,single-ended"))
		adc->single_ended = true;

	अगर (!adc->single_ended &&
	    sensor->chan < LTC2983_DIFFERENTIAL_CHAN_MIN) अणु
		dev_err(&st->spi->dev, "Invalid chan:%d for differential adc\n",
			sensor->chan);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	/* set common parameters */
	adc->sensor.assign_chan = ltc2983_adc_assign_chan;
	adc->sensor.fault_handler = ltc2983_common_fault_handler;

	वापस &adc->sensor;
पूर्ण

अटल पूर्णांक ltc2983_chan_पढ़ो(काष्ठा ltc2983_data *st,
			स्थिर काष्ठा ltc2983_sensor *sensor, पूर्णांक *val)
अणु
	u32 start_conversion = 0;
	पूर्णांक ret;
	अचिन्हित दीर्घ समय;

	start_conversion = LTC2983_STATUS_START(true);
	start_conversion |= LTC2983_STATUS_CHAN_SEL(sensor->chan);
	dev_dbg(&st->spi->dev, "Start conversion on chan:%d, status:%02X\n",
		sensor->chan, start_conversion);
	/* start conversion */
	ret = regmap_ग_लिखो(st->regmap, LTC2983_STATUS_REG, start_conversion);
	अगर (ret)
		वापस ret;

	reinit_completion(&st->completion);
	/*
	 * रुको क्रम conversion to complete.
	 * 300 ms should be more than enough to complete the conversion.
	 * Depending on the sensor configuration, there are 2/3 conversions
	 * cycles of 82ms.
	 */
	समय = रुको_क्रम_completion_समयout(&st->completion,
					   msecs_to_jअगरfies(300));
	अगर (!समय) अणु
		dev_warn(&st->spi->dev, "Conversion timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* पढ़ो the converted data */
	ret = regmap_bulk_पढ़ो(st->regmap, LTC2983_CHAN_RES_ADDR(sensor->chan),
			       &st->temp, माप(st->temp));
	अगर (ret)
		वापस ret;

	*val = __be32_to_cpu(st->temp);

	अगर (!(LTC2983_RES_VALID_MASK & *val)) अणु
		dev_err(&st->spi->dev, "Invalid conversion detected\n");
		वापस -EIO;
	पूर्ण

	ret = sensor->fault_handler(st, *val);
	अगर (ret)
		वापस ret;

	*val = sign_extend32((*val) & LTC2983_DATA_MASK, LTC2983_DATA_SIGN_BIT);
	वापस 0;
पूर्ण

अटल पूर्णांक ltc2983_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ltc2983_data *st = iio_priv(indio_dev);
	पूर्णांक ret;

	/* sanity check */
	अगर (chan->address >= st->num_channels) अणु
		dev_err(&st->spi->dev, "Invalid chan address:%ld",
			chan->address);
		वापस -EINVAL;
	पूर्ण

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		ret = ltc2983_chan_पढ़ो(st, st->sensors[chan->address], val);
		mutex_unlock(&st->lock);
		वापस ret ?: IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			/* value in milli degrees */
			*val = 1000;
			/* 2^10 */
			*val2 = 1024;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_VOLTAGE:
			/* value in millivolt */
			*val = 1000;
			/* 2^21 */
			*val2 = 2097152;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltc2983_reg_access(काष्ठा iio_dev *indio_dev,
			      अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक ग_लिखोval,
			      अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ltc2983_data *st = iio_priv(indio_dev);

	अगर (पढ़ोval)
		वापस regmap_पढ़ो(st->regmap, reg, पढ़ोval);
	अन्यथा
		वापस regmap_ग_लिखो(st->regmap, reg, ग_लिखोval);
पूर्ण

अटल irqवापस_t ltc2983_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ltc2983_data *st = data;

	complete(&st->completion);
	वापस IRQ_HANDLED;
पूर्ण

#घोषणा LTC2983_CHAN(__type, index, __address) (अणु \
	काष्ठा iio_chan_spec __chan = अणु \
		.type = __type, \
		.indexed = 1, \
		.channel = index, \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.address = __address, \
	पूर्ण; \
	__chan; \
पूर्ण)

अटल पूर्णांक ltc2983_parse_dt(काष्ठा ltc2983_data *st)
अणु
	काष्ठा device_node *child;
	काष्ठा device *dev = &st->spi->dev;
	पूर्णांक ret = 0, chan = 0, channel_avail_mask = 0;

	of_property_पढ़ो_u32(dev->of_node, "adi,mux-delay-config-us",
			     &st->mux_delay_config);

	of_property_पढ़ो_u32(dev->of_node, "adi,filter-notch-freq",
			     &st->filter_notch_freq);

	st->num_channels = of_get_available_child_count(dev->of_node);
	st->sensors = devm_kसुस्मृति(dev, st->num_channels, माप(*st->sensors),
				   GFP_KERNEL);
	अगर (!st->sensors)
		वापस -ENOMEM;

	st->iio_channels = st->num_channels;
	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		काष्ठा ltc2983_sensor sensor;

		ret = of_property_पढ़ो_u32(child, "reg", &sensor.chan);
		अगर (ret) अणु
			dev_err(dev, "reg property must given for child nodes\n");
			जाओ put_child;
		पूर्ण

		/* check अगर we have a valid channel */
		अगर (sensor.chan < LTC2983_MIN_CHANNELS_NR ||
		    sensor.chan > LTC2983_MAX_CHANNELS_NR) अणु
			ret = -EINVAL;
			dev_err(dev,
				"chan:%d must be from 1 to 20\n", sensor.chan);
			जाओ put_child;
		पूर्ण अन्यथा अगर (channel_avail_mask & BIT(sensor.chan)) अणु
			ret = -EINVAL;
			dev_err(dev, "chan:%d already in use\n", sensor.chan);
			जाओ put_child;
		पूर्ण

		ret = of_property_पढ़ो_u32(child, "adi,sensor-type",
					       &sensor.type);
		अगर (ret) अणु
			dev_err(dev,
				"adi,sensor-type property must given for child nodes\n");
			जाओ put_child;
		पूर्ण

		dev_dbg(dev, "Create new sensor, type %u, chann %u",
								sensor.type,
								sensor.chan);

		अगर (sensor.type >= LTC2983_SENSOR_THERMOCOUPLE &&
		    sensor.type <= LTC2983_SENSOR_THERMOCOUPLE_CUSTOM) अणु
			st->sensors[chan] = ltc2983_thermocouple_new(child, st,
								     &sensor);
		पूर्ण अन्यथा अगर (sensor.type >= LTC2983_SENSOR_RTD &&
			   sensor.type <= LTC2983_SENSOR_RTD_CUSTOM) अणु
			st->sensors[chan] = ltc2983_rtd_new(child, st, &sensor);
		पूर्ण अन्यथा अगर (sensor.type >= LTC2983_SENSOR_THERMISTOR &&
			   sensor.type <= LTC2983_SENSOR_THERMISTOR_CUSTOM) अणु
			st->sensors[chan] = ltc2983_thermistor_new(child, st,
								   &sensor);
		पूर्ण अन्यथा अगर (sensor.type == LTC2983_SENSOR_DIODE) अणु
			st->sensors[chan] = ltc2983_diode_new(child, st,
							      &sensor);
		पूर्ण अन्यथा अगर (sensor.type == LTC2983_SENSOR_SENSE_RESISTOR) अणु
			st->sensors[chan] = ltc2983_r_sense_new(child, st,
								&sensor);
			/* करोn't add rsense to iio */
			st->iio_channels--;
		पूर्ण अन्यथा अगर (sensor.type == LTC2983_SENSOR_सूचीECT_ADC) अणु
			st->sensors[chan] = ltc2983_adc_new(child, st, &sensor);
		पूर्ण अन्यथा अणु
			dev_err(dev, "Unknown sensor type %d\n", sensor.type);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		अगर (IS_ERR(st->sensors[chan])) अणु
			dev_err(dev, "Failed to create sensor %ld",
				PTR_ERR(st->sensors[chan]));
			ret = PTR_ERR(st->sensors[chan]);
			जाओ put_child;
		पूर्ण
		/* set generic sensor parameters */
		st->sensors[chan]->chan = sensor.chan;
		st->sensors[chan]->type = sensor.type;

		channel_avail_mask |= BIT(sensor.chan);
		chan++;
	पूर्ण

	वापस 0;
put_child:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल पूर्णांक ltc2983_setup(काष्ठा ltc2983_data *st, bool assign_iio)
अणु
	u32 iio_chan_t = 0, iio_chan_v = 0, chan, iio_idx = 0;
	पूर्णांक ret;
	अचिन्हित दीर्घ समय;

	/* make sure the device is up */
	समय = रुको_क्रम_completion_समयout(&st->completion,
					    msecs_to_jअगरfies(250));

	अगर (!समय) अणु
		dev_err(&st->spi->dev, "Device startup timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	st->iio_chan = devm_kzalloc(&st->spi->dev,
				    st->iio_channels * माप(*st->iio_chan),
				    GFP_KERNEL);

	अगर (!st->iio_chan)
		वापस -ENOMEM;

	ret = regmap_update_bits(st->regmap, LTC2983_GLOBAL_CONFIG_REG,
				 LTC2983_NOTCH_FREQ_MASK,
				 LTC2983_NOTCH_FREQ(st->filter_notch_freq));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(st->regmap, LTC2983_MUX_CONFIG_REG,
			   st->mux_delay_config);
	अगर (ret)
		वापस ret;

	क्रम (chan = 0; chan < st->num_channels; chan++) अणु
		u32 chan_type = 0, *iio_chan;

		ret = st->sensors[chan]->assign_chan(st, st->sensors[chan]);
		अगर (ret)
			वापस ret;
		/*
		 * The assign_iio flag is necessary क्रम when the device is
		 * coming out of sleep. In that हाल, we just need to
		 * re-configure the device channels.
		 * We also करोn't assign iio channels क्रम rsense.
		 */
		अगर (st->sensors[chan]->type == LTC2983_SENSOR_SENSE_RESISTOR ||
		    !assign_iio)
			जारी;

		/* assign iio channel */
		अगर (st->sensors[chan]->type != LTC2983_SENSOR_सूचीECT_ADC) अणु
			chan_type = IIO_TEMP;
			iio_chan = &iio_chan_t;
		पूर्ण अन्यथा अणु
			chan_type = IIO_VOLTAGE;
			iio_chan = &iio_chan_v;
		पूर्ण

		/*
		 * add chan as the iio .address so that, we can directly
		 * reference the sensor given the iio_chan_spec
		 */
		st->iio_chan[iio_idx++] = LTC2983_CHAN(chan_type, (*iio_chan)++,
						       chan);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_range ltc2983_reg_ranges[] = अणु
	regmap_reg_range(LTC2983_STATUS_REG, LTC2983_STATUS_REG),
	regmap_reg_range(LTC2983_TEMP_RES_START_REG, LTC2983_TEMP_RES_END_REG),
	regmap_reg_range(LTC2983_GLOBAL_CONFIG_REG, LTC2983_GLOBAL_CONFIG_REG),
	regmap_reg_range(LTC2983_MULT_CHANNEL_START_REG,
			 LTC2983_MULT_CHANNEL_END_REG),
	regmap_reg_range(LTC2983_MUX_CONFIG_REG, LTC2983_MUX_CONFIG_REG),
	regmap_reg_range(LTC2983_CHAN_ASSIGN_START_REG,
			 LTC2983_CHAN_ASSIGN_END_REG),
	regmap_reg_range(LTC2983_CUST_SENS_TBL_START_REG,
			 LTC2983_CUST_SENS_TBL_END_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table ltc2983_reg_table = अणु
	.yes_ranges = ltc2983_reg_ranges,
	.n_yes_ranges = ARRAY_SIZE(ltc2983_reg_ranges),
पूर्ण;

/*
 *  The reg_bits are actually 12 but the device needs the first *complete*
 *  byte क्रम the command (R/W).
 */
अटल स्थिर काष्ठा regmap_config ltc2983_regmap_config = अणु
	.reg_bits = 24,
	.val_bits = 8,
	.wr_table = &ltc2983_reg_table,
	.rd_table = &ltc2983_reg_table,
	.पढ़ो_flag_mask = GENMASK(1, 0),
	.ग_लिखो_flag_mask = BIT(1),
पूर्ण;

अटल स्थिर काष्ठा  iio_info ltc2983_iio_info = अणु
	.पढ़ो_raw = ltc2983_पढ़ो_raw,
	.debugfs_reg_access = ltc2983_reg_access,
पूर्ण;

अटल पूर्णांक ltc2983_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ltc2983_data *st;
	काष्ठा iio_dev *indio_dev;
	स्थिर अक्षर *name = spi_get_device_id(spi)->name;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	st->regmap = devm_regmap_init_spi(spi, &ltc2983_regmap_config);
	अगर (IS_ERR(st->regmap)) अणु
		dev_err(&spi->dev, "Failed to initialize regmap\n");
		वापस PTR_ERR(st->regmap);
	पूर्ण

	mutex_init(&st->lock);
	init_completion(&st->completion);
	st->spi = spi;
	spi_set_drvdata(spi, st);

	ret = ltc2983_parse_dt(st);
	अगर (ret)
		वापस ret;
	/*
	 * let's request the irq now so it is used to sync the device
	 * startup in ltc2983_setup()
	 */
	ret = devm_request_irq(&spi->dev, spi->irq, ltc2983_irq_handler,
			       IRQF_TRIGGER_RISING, name, st);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to request an irq, %d", ret);
		वापस ret;
	पूर्ण

	ret = ltc2983_setup(st, true);
	अगर (ret)
		वापस ret;

	indio_dev->name = name;
	indio_dev->num_channels = st->iio_channels;
	indio_dev->channels = st->iio_chan;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &ltc2983_iio_info;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused ltc2983_resume(काष्ठा device *dev)
अणु
	काष्ठा ltc2983_data *st = spi_get_drvdata(to_spi_device(dev));
	पूर्णांक dummy;

	/* dummy पढ़ो to bring the device out of sleep */
	regmap_पढ़ो(st->regmap, LTC2983_STATUS_REG, &dummy);
	/* we need to re-assign the channels */
	वापस ltc2983_setup(st, false);
पूर्ण

अटल पूर्णांक __maybe_unused ltc2983_suspend(काष्ठा device *dev)
अणु
	काष्ठा ltc2983_data *st = spi_get_drvdata(to_spi_device(dev));

	वापस regmap_ग_लिखो(st->regmap, LTC2983_STATUS_REG, LTC2983_SLEEP);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ltc2983_pm_ops, ltc2983_suspend, ltc2983_resume);

अटल स्थिर काष्ठा spi_device_id ltc2983_id_table[] = अणु
	अणु "ltc2983" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, ltc2983_id_table);

अटल स्थिर काष्ठा of_device_id ltc2983_of_match[] = अणु
	अणु .compatible = "adi,ltc2983" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc2983_of_match);

अटल काष्ठा spi_driver ltc2983_driver = अणु
	.driver = अणु
		.name = "ltc2983",
		.of_match_table = ltc2983_of_match,
		.pm = &ltc2983_pm_ops,
	पूर्ण,
	.probe = ltc2983_probe,
	.id_table = ltc2983_id_table,
पूर्ण;

module_spi_driver(ltc2983_driver);

MODULE_AUTHOR("Nuno Sa <nuno.sa@analog.com>");
MODULE_DESCRIPTION("Analog Devices LTC2983 SPI Temperature sensors");
MODULE_LICENSE("GPL");
