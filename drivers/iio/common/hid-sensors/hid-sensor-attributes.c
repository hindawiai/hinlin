<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID Sensors Driver
 * Copyright (c) 2012, Intel Corporation.
 */
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>

#समावेश <linux/hid-sensor-hub.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा HZ_PER_MHZ	1000000L

अटल काष्ठा अणु
	u32 usage_id;
	पूर्णांक unit; /* 0 क्रम शेष others from HID sensor spec */
	पूर्णांक scale_val0; /* scale, whole number */
	पूर्णांक scale_val1; /* scale, fraction in nanos */
पूर्ण unit_conversion[] = अणु
	अणुHID_USAGE_SENSOR_ACCEL_3D, 0, 9, 806650000पूर्ण,
	अणुHID_USAGE_SENSOR_ACCEL_3D,
		HID_USAGE_SENSOR_UNITS_METERS_PER_SEC_SQRD, 1, 0पूर्ण,
	अणुHID_USAGE_SENSOR_ACCEL_3D,
		HID_USAGE_SENSOR_UNITS_G, 9, 806650000पूर्ण,

	अणुHID_USAGE_SENSOR_GRAVITY_VECTOR, 0, 9, 806650000पूर्ण,
	अणुHID_USAGE_SENSOR_GRAVITY_VECTOR,
		HID_USAGE_SENSOR_UNITS_METERS_PER_SEC_SQRD, 1, 0पूर्ण,
	अणुHID_USAGE_SENSOR_GRAVITY_VECTOR,
		HID_USAGE_SENSOR_UNITS_G, 9, 806650000पूर्ण,

	अणुHID_USAGE_SENSOR_GYRO_3D, 0, 0, 17453293पूर्ण,
	अणुHID_USAGE_SENSOR_GYRO_3D,
		HID_USAGE_SENSOR_UNITS_RADIANS_PER_SECOND, 1, 0पूर्ण,
	अणुHID_USAGE_SENSOR_GYRO_3D,
		HID_USAGE_SENSOR_UNITS_DEGREES_PER_SECOND, 0, 17453293पूर्ण,

	अणुHID_USAGE_SENSOR_COMPASS_3D, 0, 0, 1000000पूर्ण,
	अणुHID_USAGE_SENSOR_COMPASS_3D, HID_USAGE_SENSOR_UNITS_GAUSS, 1, 0पूर्ण,

	अणुHID_USAGE_SENSOR_INCLINOMETER_3D, 0, 0, 17453293पूर्ण,
	अणुHID_USAGE_SENSOR_INCLINOMETER_3D,
		HID_USAGE_SENSOR_UNITS_DEGREES, 0, 17453293पूर्ण,
	अणुHID_USAGE_SENSOR_INCLINOMETER_3D,
		HID_USAGE_SENSOR_UNITS_RADIANS, 1, 0पूर्ण,

	अणुHID_USAGE_SENSOR_ALS, 0, 1, 0पूर्ण,
	अणुHID_USAGE_SENSOR_ALS, HID_USAGE_SENSOR_UNITS_LUX, 1, 0पूर्ण,

	अणुHID_USAGE_SENSOR_PRESSURE, 0, 100, 0पूर्ण,
	अणुHID_USAGE_SENSOR_PRESSURE, HID_USAGE_SENSOR_UNITS_PASCAL, 0, 1000000पूर्ण,

	अणुHID_USAGE_SENSOR_TIME_TIMESTAMP, 0, 1000000000, 0पूर्ण,
	अणुHID_USAGE_SENSOR_TIME_TIMESTAMP, HID_USAGE_SENSOR_UNITS_MILLISECOND,
		1000000, 0पूर्ण,

	अणुHID_USAGE_SENSOR_DEVICE_ORIENTATION, 0, 1, 0पूर्ण,

	अणुHID_USAGE_SENSOR_RELATIVE_ORIENTATION, 0, 1, 0पूर्ण,

	अणुHID_USAGE_SENSOR_GEOMAGNETIC_ORIENTATION, 0, 1, 0पूर्ण,

	अणुHID_USAGE_SENSOR_TEMPERATURE, 0, 1000, 0पूर्ण,
	अणुHID_USAGE_SENSOR_TEMPERATURE, HID_USAGE_SENSOR_UNITS_DEGREES, 1000, 0पूर्ण,

	अणुHID_USAGE_SENSOR_HUMIDITY, 0, 1000, 0पूर्ण,
	अणुHID_USAGE_SENSOR_HINGE, 0, 0, 17453293पूर्ण,
	अणुHID_USAGE_SENSOR_HINGE, HID_USAGE_SENSOR_UNITS_DEGREES, 0, 17453293पूर्ण,
पूर्ण;

अटल व्योम simple_भाग(पूर्णांक भागidend, पूर्णांक भागisor, पूर्णांक *whole,
				पूर्णांक *micro_frac)
अणु
	पूर्णांक rem;
	पूर्णांक exp = 0;

	*micro_frac = 0;
	अगर (भागisor == 0) अणु
		*whole = 0;
		वापस;
	पूर्ण
	*whole = भागidend/भागisor;
	rem = भागidend % भागisor;
	अगर (rem) अणु
		जबतक (rem <= भागisor) अणु
			rem *= 10;
			exp++;
		पूर्ण
		*micro_frac = (rem / भागisor) * पूर्णांक_घात(10, 6 - exp);
	पूर्ण
पूर्ण

अटल व्योम split_micro_fraction(अचिन्हित पूर्णांक no, पूर्णांक exp, पूर्णांक *val1, पूर्णांक *val2)
अणु
	पूर्णांक भागisor = पूर्णांक_घात(10, exp);

	*val1 = no / भागisor;
	*val2 = no % भागisor * पूर्णांक_घात(10, 6 - exp);
पूर्ण

/*
VTF क्रमmat uses exponent and variable size क्रमmat.
For example अगर the size is 2 bytes
0x0067 with VTF16E14 क्रमmat -> +1.03
To convert just change to 0x67 to decimal and use two decimal as E14 stands
क्रम 10^-2.
Negative numbers are 2's complement
*/
अटल व्योम convert_from_vtf_क्रमmat(u32 value, पूर्णांक size, पूर्णांक exp,
					पूर्णांक *val1, पूर्णांक *val2)
अणु
	पूर्णांक sign = 1;

	अगर (value & BIT(size*8 - 1)) अणु
		value =  ((1LL << (size * 8)) - value);
		sign = -1;
	पूर्ण
	exp = hid_sensor_convert_exponent(exp);
	अगर (exp >= 0) अणु
		*val1 = sign * value * पूर्णांक_घात(10, exp);
		*val2 = 0;
	पूर्ण अन्यथा अणु
		split_micro_fraction(value, -exp, val1, val2);
		अगर (*val1)
			*val1 = sign * (*val1);
		अन्यथा
			*val2 = sign * (*val2);
	पूर्ण
पूर्ण

अटल u32 convert_to_vtf_क्रमmat(पूर्णांक size, पूर्णांक exp, पूर्णांक val1, पूर्णांक val2)
अणु
	पूर्णांक भागisor;
	u32 value;
	पूर्णांक sign = 1;

	अगर (val1 < 0 || val2 < 0)
		sign = -1;
	exp = hid_sensor_convert_exponent(exp);
	अगर (exp < 0) अणु
		भागisor = पूर्णांक_घात(10, 6 + exp);
		value = असल(val1) * पूर्णांक_घात(10, -exp);
		value += असल(val2) / भागisor;
	पूर्ण अन्यथा अणु
		भागisor = पूर्णांक_घात(10, exp);
		value = असल(val1) / भागisor;
	पूर्ण
	अगर (sign < 0)
		value =  ((1LL << (size * 8)) - value);

	वापस value;
पूर्ण

s32 hid_sensor_पढ़ो_poll_value(काष्ठा hid_sensor_common *st)
अणु
	s32 value = 0;
	पूर्णांक ret;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->poll.report_id,
				     st->poll.index, माप(value), &value);

	अगर (ret < 0 || value < 0) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (st->poll.units == HID_USAGE_SENSOR_UNITS_SECOND)
			value = value * 1000;
	पूर्ण

	वापस value;
पूर्ण
EXPORT_SYMBOL(hid_sensor_पढ़ो_poll_value);

पूर्णांक hid_sensor_पढ़ो_samp_freq_value(काष्ठा hid_sensor_common *st,
				पूर्णांक *val1, पूर्णांक *val2)
अणु
	s32 value;
	पूर्णांक ret;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->poll.report_id,
				     st->poll.index, माप(value), &value);
	अगर (ret < 0 || value < 0) अणु
		*val1 = *val2 = 0;
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (st->poll.units == HID_USAGE_SENSOR_UNITS_MILLISECOND)
			simple_भाग(1000, value, val1, val2);
		अन्यथा अगर (st->poll.units == HID_USAGE_SENSOR_UNITS_SECOND)
			simple_भाग(1, value, val1, val2);
		अन्यथा अणु
			*val1 = *val2 = 0;
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण
EXPORT_SYMBOL(hid_sensor_पढ़ो_samp_freq_value);

पूर्णांक hid_sensor_ग_लिखो_samp_freq_value(काष्ठा hid_sensor_common *st,
				पूर्णांक val1, पूर्णांक val2)
अणु
	s32 value;
	पूर्णांक ret;

	अगर (val1 < 0 || val2 < 0)
		वापस -EINVAL;

	value = val1 * HZ_PER_MHZ + val2;
	अगर (value) अणु
		अगर (st->poll.units == HID_USAGE_SENSOR_UNITS_MILLISECOND)
			value = NSEC_PER_SEC / value;
		अन्यथा अगर (st->poll.units == HID_USAGE_SENSOR_UNITS_SECOND)
			value = USEC_PER_SEC / value;
		अन्यथा
			value = 0;
	पूर्ण
	ret = sensor_hub_set_feature(st->hsdev, st->poll.report_id,
				     st->poll.index, माप(value), &value);
	अगर (ret < 0 || value < 0)
		वापस -EINVAL;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->poll.report_id,
				     st->poll.index, माप(value), &value);
	अगर (ret < 0 || value < 0)
		वापस -EINVAL;

	st->poll_पूर्णांकerval = value;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hid_sensor_ग_लिखो_samp_freq_value);

पूर्णांक hid_sensor_पढ़ो_raw_hyst_value(काष्ठा hid_sensor_common *st,
				पूर्णांक *val1, पूर्णांक *val2)
अणु
	s32 value;
	पूर्णांक ret;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->sensitivity.report_id,
				     st->sensitivity.index, माप(value),
				     &value);
	अगर (ret < 0 || value < 0) अणु
		*val1 = *val2 = 0;
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		convert_from_vtf_क्रमmat(value, st->sensitivity.size,
					st->sensitivity.unit_expo,
					val1, val2);
	पूर्ण

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण
EXPORT_SYMBOL(hid_sensor_पढ़ो_raw_hyst_value);

पूर्णांक hid_sensor_पढ़ो_raw_hyst_rel_value(काष्ठा hid_sensor_common *st, पूर्णांक *val1,
				       पूर्णांक *val2)
अणु
	s32 value;
	पूर्णांक ret;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->sensitivity_rel.report_id,
				     st->sensitivity_rel.index, माप(value),
				     &value);
	अगर (ret < 0 || value < 0) अणु
		*val1 = *val2 = 0;
		वापस -EINVAL;
	पूर्ण

	convert_from_vtf_क्रमmat(value, st->sensitivity_rel.size,
				st->sensitivity_rel.unit_expo, val1, val2);

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण
EXPORT_SYMBOL(hid_sensor_पढ़ो_raw_hyst_rel_value);


पूर्णांक hid_sensor_ग_लिखो_raw_hyst_value(काष्ठा hid_sensor_common *st,
					पूर्णांक val1, पूर्णांक val2)
अणु
	s32 value;
	पूर्णांक ret;

	अगर (val1 < 0 || val2 < 0)
		वापस -EINVAL;

	value = convert_to_vtf_क्रमmat(st->sensitivity.size,
				st->sensitivity.unit_expo,
				val1, val2);
	ret = sensor_hub_set_feature(st->hsdev, st->sensitivity.report_id,
				     st->sensitivity.index, माप(value),
				     &value);
	अगर (ret < 0 || value < 0)
		वापस -EINVAL;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->sensitivity.report_id,
				     st->sensitivity.index, माप(value),
				     &value);
	अगर (ret < 0 || value < 0)
		वापस -EINVAL;

	st->raw_hystersis = value;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hid_sensor_ग_लिखो_raw_hyst_value);

पूर्णांक hid_sensor_ग_लिखो_raw_hyst_rel_value(काष्ठा hid_sensor_common *st,
					पूर्णांक val1, पूर्णांक val2)
अणु
	s32 value;
	पूर्णांक ret;

	अगर (val1 < 0 || val2 < 0)
		वापस -EINVAL;

	value = convert_to_vtf_क्रमmat(st->sensitivity_rel.size,
				st->sensitivity_rel.unit_expo,
				val1, val2);
	ret = sensor_hub_set_feature(st->hsdev, st->sensitivity_rel.report_id,
				     st->sensitivity_rel.index, माप(value),
				     &value);
	अगर (ret < 0 || value < 0)
		वापस -EINVAL;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->sensitivity_rel.report_id,
				     st->sensitivity_rel.index, माप(value),
				     &value);
	अगर (ret < 0 || value < 0)
		वापस -EINVAL;

	st->raw_hystersis = value;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hid_sensor_ग_लिखो_raw_hyst_rel_value);

/*
 * This fuction applies the unit exponent to the scale.
 * For example:
 * 9.806650000 ->exp:2-> val0[980]val1[665000000]
 * 9.000806000 ->exp:2-> val0[900]val1[80600000]
 * 0.174535293 ->exp:2-> val0[17]val1[453529300]
 * 1.001745329 ->exp:0-> val0[1]val1[1745329]
 * 1.001745329 ->exp:2-> val0[100]val1[174532900]
 * 1.001745329 ->exp:4-> val0[10017]val1[453290000]
 * 9.806650000 ->exp:-2-> val0[0]val1[98066500]
 */
अटल व्योम adjust_exponent_nano(पूर्णांक *val0, पूर्णांक *val1, पूर्णांक scale0,
				  पूर्णांक scale1, पूर्णांक exp)
अणु
	पूर्णांक भागisor;
	पूर्णांक i;
	पूर्णांक x;
	पूर्णांक res;
	पूर्णांक rem;

	अगर (exp > 0) अणु
		*val0 = scale0 * पूर्णांक_घात(10, exp);
		res = 0;
		अगर (exp > 9) अणु
			*val1 = 0;
			वापस;
		पूर्ण
		क्रम (i = 0; i < exp; ++i) अणु
			भागisor = पूर्णांक_घात(10, 8 - i);
			x = scale1 / भागisor;
			res += पूर्णांक_घात(10, exp - 1 - i) * x;
			scale1 = scale1 % भागisor;
		पूर्ण
		*val0 += res;
		*val1 = scale1 * पूर्णांक_घात(10, exp);
	पूर्ण अन्यथा अगर (exp < 0) अणु
		exp = असल(exp);
		अगर (exp > 9) अणु
			*val0 = *val1 = 0;
			वापस;
		पूर्ण
		भागisor = पूर्णांक_घात(10, exp);
		*val0 = scale0 / भागisor;
		rem = scale0 % भागisor;
		res = 0;
		क्रम (i = 0; i < (9 - exp); ++i) अणु
			भागisor = पूर्णांक_घात(10, 8 - i);
			x = scale1 / भागisor;
			res += पूर्णांक_घात(10, 8 - exp - i) * x;
			scale1 = scale1 % भागisor;
		पूर्ण
		*val1 = rem * पूर्णांक_घात(10, 9 - exp) + res;
	पूर्ण अन्यथा अणु
		*val0 = scale0;
		*val1 = scale1;
	पूर्ण
पूर्ण

पूर्णांक hid_sensor_क्रमmat_scale(u32 usage_id,
			काष्ठा hid_sensor_hub_attribute_info *attr_info,
			पूर्णांक *val0, पूर्णांक *val1)
अणु
	पूर्णांक i;
	पूर्णांक exp;

	*val0 = 1;
	*val1 = 0;

	क्रम (i = 0; i < ARRAY_SIZE(unit_conversion); ++i) अणु
		अगर (unit_conversion[i].usage_id == usage_id &&
			unit_conversion[i].unit == attr_info->units) अणु
			exp  = hid_sensor_convert_exponent(
						attr_info->unit_expo);
			adjust_exponent_nano(val0, val1,
					unit_conversion[i].scale_val0,
					unit_conversion[i].scale_val1, exp);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस IIO_VAL_INT_PLUS_न_अंकO;
पूर्ण
EXPORT_SYMBOL(hid_sensor_क्रमmat_scale);

पूर्णांक64_t hid_sensor_convert_बारtamp(काष्ठा hid_sensor_common *st,
				     पूर्णांक64_t raw_value)
अणु
	वापस st->बारtamp_ns_scale * raw_value;
पूर्ण
EXPORT_SYMBOL(hid_sensor_convert_बारtamp);

अटल
पूर्णांक hid_sensor_get_reporting_पूर्णांकerval(काष्ठा hid_sensor_hub_device *hsdev,
					u32 usage_id,
					काष्ठा hid_sensor_common *st)
अणु
	sensor_hub_input_get_attribute_info(hsdev,
					HID_FEATURE_REPORT, usage_id,
					HID_USAGE_SENSOR_PROP_REPORT_INTERVAL,
					&st->poll);
	/* Default unit of measure is milliseconds */
	अगर (st->poll.units == 0)
		st->poll.units = HID_USAGE_SENSOR_UNITS_MILLISECOND;

	st->poll_पूर्णांकerval = -1;

	वापस 0;

पूर्ण

अटल व्योम hid_sensor_get_report_latency_info(काष्ठा hid_sensor_hub_device *hsdev,
					       u32 usage_id,
					       काष्ठा hid_sensor_common *st)
अणु
	sensor_hub_input_get_attribute_info(hsdev, HID_FEATURE_REPORT,
					    usage_id,
					    HID_USAGE_SENSOR_PROP_REPORT_LATENCY,
					    &st->report_latency);

	hid_dbg(hsdev->hdev, "Report latency attributes: %x:%x\n",
		st->report_latency.index, st->report_latency.report_id);
पूर्ण

पूर्णांक hid_sensor_get_report_latency(काष्ठा hid_sensor_common *st)
अणु
	पूर्णांक ret;
	पूर्णांक value;

	ret = sensor_hub_get_feature(st->hsdev, st->report_latency.report_id,
				     st->report_latency.index, माप(value),
				     &value);
	अगर (ret < 0)
		वापस ret;

	वापस value;
पूर्ण
EXPORT_SYMBOL(hid_sensor_get_report_latency);

पूर्णांक hid_sensor_set_report_latency(काष्ठा hid_sensor_common *st, पूर्णांक latency_ms)
अणु
	वापस sensor_hub_set_feature(st->hsdev, st->report_latency.report_id,
				      st->report_latency.index,
				      माप(latency_ms), &latency_ms);
पूर्ण
EXPORT_SYMBOL(hid_sensor_set_report_latency);

bool hid_sensor_batch_mode_supported(काष्ठा hid_sensor_common *st)
अणु
	वापस st->report_latency.index > 0 && st->report_latency.report_id > 0;
पूर्ण
EXPORT_SYMBOL(hid_sensor_batch_mode_supported);

पूर्णांक hid_sensor_parse_common_attributes(काष्ठा hid_sensor_hub_device *hsdev,
					u32 usage_id,
					काष्ठा hid_sensor_common *st,
					स्थिर u32 *sensitivity_addresses,
					u32 sensitivity_addresses_len)
अणु

	काष्ठा hid_sensor_hub_attribute_info बारtamp;
	s32 value;
	पूर्णांक ret;
	पूर्णांक i;

	hid_sensor_get_reporting_पूर्णांकerval(hsdev, usage_id, st);

	sensor_hub_input_get_attribute_info(hsdev,
					HID_FEATURE_REPORT, usage_id,
					HID_USAGE_SENSOR_PROP_REPORT_STATE,
					&st->report_state);

	sensor_hub_input_get_attribute_info(hsdev,
					HID_FEATURE_REPORT, usage_id,
					HID_USAGE_SENSOR_PROY_POWER_STATE,
					&st->घातer_state);

	st->घातer_state.logical_minimum = 1;
	st->report_state.logical_minimum = 1;

	sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, usage_id,
			HID_USAGE_SENSOR_PROP_SENSITIVITY_ABS,
			 &st->sensitivity);

	sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, usage_id,
			HID_USAGE_SENSOR_PROP_SENSITIVITY_REL_PCT,
			&st->sensitivity_rel);
	/*
	 * Set Sensitivity field ids, when there is no inभागidual modअगरier, will
	 * check असलolute sensitivity and relative sensitivity of data field
	 */
	क्रम (i = 0; i < sensitivity_addresses_len; i++) अणु
		अगर (st->sensitivity.index < 0)
			sensor_hub_input_get_attribute_info(
				hsdev, HID_FEATURE_REPORT, usage_id,
				HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS |
					sensitivity_addresses[i],
				&st->sensitivity);

		अगर (st->sensitivity_rel.index < 0)
			sensor_hub_input_get_attribute_info(
				hsdev, HID_FEATURE_REPORT, usage_id,
				HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_REL_PCT |
					sensitivity_addresses[i],
				&st->sensitivity_rel);
	पूर्ण

	st->raw_hystersis = -1;

	sensor_hub_input_get_attribute_info(hsdev,
					    HID_INPUT_REPORT, usage_id,
					    HID_USAGE_SENSOR_TIME_TIMESTAMP,
					    &बारtamp);
	अगर (बारtamp.index >= 0 && बारtamp.report_id) अणु
		पूर्णांक val0, val1;

		hid_sensor_क्रमmat_scale(HID_USAGE_SENSOR_TIME_TIMESTAMP,
					&बारtamp, &val0, &val1);
		st->बारtamp_ns_scale = val0;
	पूर्ण अन्यथा
		st->बारtamp_ns_scale = 1000000000;

	hid_sensor_get_report_latency_info(hsdev, usage_id, st);

	hid_dbg(hsdev->hdev, "common attributes: %x:%x, %x:%x, %x:%x %x:%x %x:%x\n",
		st->poll.index, st->poll.report_id,
		st->report_state.index, st->report_state.report_id,
		st->घातer_state.index, st->घातer_state.report_id,
		st->sensitivity.index, st->sensitivity.report_id,
		बारtamp.index, बारtamp.report_id);

	ret = sensor_hub_get_feature(hsdev,
				st->घातer_state.report_id,
				st->घातer_state.index, माप(value), &value);
	अगर (ret < 0)
		वापस ret;
	अगर (value < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hid_sensor_parse_common_attributes);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@intel.com>");
MODULE_DESCRIPTION("HID Sensor common attribute processing");
MODULE_LICENSE("GPL");
