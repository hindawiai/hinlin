<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * hid-sensor-custom.c
 * Copyright (c) 2015, Intel Corporation.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hid-sensor-hub.h>

#घोषणा HID_CUSTOM_NAME_LENGTH		64
#घोषणा HID_CUSTOM_MAX_CORE_ATTRS	10
#घोषणा HID_CUSTOM_TOTAL_ATTRS		(HID_CUSTOM_MAX_CORE_ATTRS + 1)
#घोषणा HID_CUSTOM_FIFO_SIZE		4096
#घोषणा HID_CUSTOM_MAX_FEATURE_BYTES	64
#घोषणा HID_SENSOR_USAGE_LENGTH (4 + 1)

काष्ठा hid_sensor_custom_field अणु
	पूर्णांक report_id;
	अक्षर group_name[HID_CUSTOM_NAME_LENGTH];
	काष्ठा hid_sensor_hub_attribute_info attribute;
	काष्ठा device_attribute sd_attrs[HID_CUSTOM_MAX_CORE_ATTRS];
	अक्षर attr_name[HID_CUSTOM_TOTAL_ATTRS][HID_CUSTOM_NAME_LENGTH];
	काष्ठा attribute *attrs[HID_CUSTOM_TOTAL_ATTRS];
	काष्ठा attribute_group hid_custom_attribute_group;
पूर्ण;

काष्ठा hid_sensor_custom अणु
	काष्ठा mutex mutex;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा hid_sensor_hub_device *hsdev;
	काष्ठा hid_sensor_hub_callbacks callbacks;
	पूर्णांक sensor_field_count;
	काष्ठा hid_sensor_custom_field *fields;
	पूर्णांक input_field_count;
	पूर्णांक input_report_size;
	पूर्णांक input_report_recd_size;
	bool input_skip_sample;
	bool enable;
	काष्ठा hid_sensor_custom_field *घातer_state;
	काष्ठा hid_sensor_custom_field *report_state;
	काष्ठा miscdevice custom_dev;
	काष्ठा kfअगरo data_fअगरo;
	अचिन्हित दीर्घ misc_खोलोed;
	रुको_queue_head_t रुको;
	काष्ठा platक्रमm_device *custom_pdev;
पूर्ण;

/* Header क्रम each sample to user space via dev पूर्णांकerface */
काष्ठा hid_sensor_sample अणु
	u32 usage_id;
	u64 बारtamp;
	u32 raw_len;
पूर्ण __packed;

अटल काष्ठा attribute hid_custom_attrs[] = अणु
	अणु.name = "name", .mode = S_IRUGOपूर्ण,
	अणु.name = "units", .mode = S_IRUGOपूर्ण,
	अणु.name = "unit-expo", .mode = S_IRUGOपूर्ण,
	अणु.name = "minimum", .mode = S_IRUGOपूर्ण,
	अणु.name = "maximum", .mode = S_IRUGOपूर्ण,
	अणु.name = "size", .mode = S_IRUGOपूर्ण,
	अणु.name = "value", .mode = S_IWUSR | S_IRUGOपूर्ण,
	अणु.name = शून्यपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hid_custom_usage_desc अणु
	पूर्णांक usage_id;
	अक्षर *desc;
पूर्ण hid_custom_usage_desc_table[] = अणु
	अणु0x200201,	"event-sensor-state"पूर्ण,
	अणु0x200202,	"event-sensor-event"पूर्ण,
	अणु0x200301,	"property-friendly-name"पूर्ण,
	अणु0x200302,	"property-persistent-unique-id"पूर्ण,
	अणु0x200303,	"property-sensor-status"पूर्ण,
	अणु0x200304,	"property-min-report-interval"पूर्ण,
	अणु0x200305,	"property-sensor-manufacturer"पूर्ण,
	अणु0x200306,	"property-sensor-model"पूर्ण,
	अणु0x200307,	"property-sensor-serial-number"पूर्ण,
	अणु0x200308,	"property-sensor-description"पूर्ण,
	अणु0x200309,	"property-sensor-connection-type"पूर्ण,
	अणु0x20030A,	"property-sensor-device-path"पूर्ण,
	अणु0x20030B,	"property-hardware-revision"पूर्ण,
	अणु0x20030C,	"property-firmware-version"पूर्ण,
	अणु0x20030D,	"property-release-date"पूर्ण,
	अणु0x20030E,	"property-report-interval"पूर्ण,
	अणु0x20030F,	"property-change-sensitivity-absolute"पूर्ण,
	अणु0x200310,	"property-change-sensitivity-percent-range"पूर्ण,
	अणु0x200311,	"property-change-sensitivity-percent-relative"पूर्ण,
	अणु0x200312,	"property-accuracy"पूर्ण,
	अणु0x200313,	"property-resolution"पूर्ण,
	अणु0x200314,	"property-maximum"पूर्ण,
	अणु0x200315,	"property-minimum"पूर्ण,
	अणु0x200316,	"property-reporting-state"पूर्ण,
	अणु0x200317,	"property-sampling-rate"पूर्ण,
	अणु0x200318,	"property-response-curve"पूर्ण,
	अणु0x200319,	"property-power-state"पूर्ण,
	अणु0x200540,	"data-field-custom"पूर्ण,
	अणु0x200541,	"data-field-custom-usage"पूर्ण,
	अणु0x200542,	"data-field-custom-boolean-array"पूर्ण,
	अणु0x200543,	"data-field-custom-value"पूर्ण,
	अणु0x200544,	"data-field-custom-value_1"पूर्ण,
	अणु0x200545,	"data-field-custom-value_2"पूर्ण,
	अणु0x200546,	"data-field-custom-value_3"पूर्ण,
	अणु0x200547,	"data-field-custom-value_4"पूर्ण,
	अणु0x200548,	"data-field-custom-value_5"पूर्ण,
	अणु0x200549,	"data-field-custom-value_6"पूर्ण,
	अणु0x20054A,	"data-field-custom-value_7"पूर्ण,
	अणु0x20054B,	"data-field-custom-value_8"पूर्ण,
	अणु0x20054C,	"data-field-custom-value_9"पूर्ण,
	अणु0x20054D,	"data-field-custom-value_10"पूर्ण,
	अणु0x20054E,	"data-field-custom-value_11"पूर्ण,
	अणु0x20054F,	"data-field-custom-value_12"पूर्ण,
	अणु0x200550,	"data-field-custom-value_13"पूर्ण,
	अणु0x200551,	"data-field-custom-value_14"पूर्ण,
	अणु0x200552,	"data-field-custom-value_15"पूर्ण,
	अणु0x200553,	"data-field-custom-value_16"पूर्ण,
	अणु0x200554,	"data-field-custom-value_17"पूर्ण,
	अणु0x200555,	"data-field-custom-value_18"पूर्ण,
	अणु0x200556,	"data-field-custom-value_19"पूर्ण,
	अणु0x200557,	"data-field-custom-value_20"पूर्ण,
	अणु0x200558,	"data-field-custom-value_21"पूर्ण,
	अणु0x200559,	"data-field-custom-value_22"पूर्ण,
	अणु0x20055A,	"data-field-custom-value_23"पूर्ण,
	अणु0x20055B,	"data-field-custom-value_24"पूर्ण,
	अणु0x20055C,	"data-field-custom-value_25"पूर्ण,
	अणु0x20055D,	"data-field-custom-value_26"पूर्ण,
	अणु0x20055E,	"data-field-custom-value_27"पूर्ण,
	अणु0x20055F,	"data-field-custom-value_28"पूर्ण,
पूर्ण;

अटल पूर्णांक usage_id_cmp(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	अगर (*(पूर्णांक *)p1 < *(पूर्णांक *)p2)
		वापस -1;

	अगर (*(पूर्णांक *)p1 > *(पूर्णांक *)p2)
		वापस 1;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार enable_sensor_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hid_sensor_custom *sensor_inst = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", sensor_inst->enable);
पूर्ण

अटल पूर्णांक set_घातer_report_state(काष्ठा hid_sensor_custom *sensor_inst,
				  bool state)
अणु
	पूर्णांक घातer_val = -1;
	पूर्णांक report_val = -1;
	u32 घातer_state_usage_id;
	u32 report_state_usage_id;
	पूर्णांक ret;

	/*
	 * It is possible that the घातer/report state ids are not present.
	 * In this हाल this function will वापस success. But अगर the
	 * ids are present, then it will वापस error अगर set fails.
	 */
	अगर (state) अणु
		घातer_state_usage_id =
			HID_USAGE_SENSOR_PROP_POWER_STATE_D0_FULL_POWER_ENUM;
		report_state_usage_id =
			HID_USAGE_SENSOR_PROP_REPORTING_STATE_ALL_EVENTS_ENUM;
	पूर्ण अन्यथा अणु
		घातer_state_usage_id =
			HID_USAGE_SENSOR_PROP_POWER_STATE_D4_POWER_OFF_ENUM;
		report_state_usage_id =
			HID_USAGE_SENSOR_PROP_REPORTING_STATE_NO_EVENTS_ENUM;
	पूर्ण

	अगर (sensor_inst->घातer_state)
		घातer_val = hid_sensor_get_usage_index(sensor_inst->hsdev,
				sensor_inst->घातer_state->attribute.report_id,
				sensor_inst->घातer_state->attribute.index,
				घातer_state_usage_id);
	अगर (sensor_inst->report_state)
		report_val = hid_sensor_get_usage_index(sensor_inst->hsdev,
				sensor_inst->report_state->attribute.report_id,
				sensor_inst->report_state->attribute.index,
				report_state_usage_id);

	अगर (घातer_val >= 0) अणु
		घातer_val +=
			sensor_inst->घातer_state->attribute.logical_minimum;
		ret = sensor_hub_set_feature(sensor_inst->hsdev,
				sensor_inst->घातer_state->attribute.report_id,
				sensor_inst->घातer_state->attribute.index,
				माप(घातer_val),
				&घातer_val);
		अगर (ret) अणु
			hid_err(sensor_inst->hsdev->hdev,
				"Set power state failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (report_val >= 0) अणु
		report_val +=
			sensor_inst->report_state->attribute.logical_minimum;
		ret = sensor_hub_set_feature(sensor_inst->hsdev,
				sensor_inst->report_state->attribute.report_id,
				sensor_inst->report_state->attribute.index,
				माप(report_val),
				&report_val);
		अगर (ret) अणु
			hid_err(sensor_inst->hsdev->hdev,
				"Set report state failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार enable_sensor_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_sensor_custom *sensor_inst = dev_get_drvdata(dev);
	पूर्णांक value;
	पूर्णांक ret = -EINVAL;

	अगर (kstrtoपूर्णांक(buf, 0, &value) != 0)
		वापस -EINVAL;

	mutex_lock(&sensor_inst->mutex);
	अगर (value && !sensor_inst->enable) अणु
		ret = sensor_hub_device_खोलो(sensor_inst->hsdev);
		अगर (ret)
			जाओ unlock_state;

		ret = set_घातer_report_state(sensor_inst, true);
		अगर (ret) अणु
			sensor_hub_device_बंद(sensor_inst->hsdev);
			जाओ unlock_state;
		पूर्ण
		sensor_inst->enable = true;
	पूर्ण अन्यथा अगर (!value && sensor_inst->enable) अणु
		ret = set_घातer_report_state(sensor_inst, false);
		sensor_hub_device_बंद(sensor_inst->hsdev);
		sensor_inst->enable = false;
	पूर्ण
unlock_state:
	mutex_unlock(&sensor_inst->mutex);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(enable_sensor);

अटल काष्ठा attribute *enable_sensor_attrs[] = अणु
	&dev_attr_enable_sensor.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group enable_sensor_attr_group = अणु
	.attrs = enable_sensor_attrs,
पूर्ण;

अटल sमाप_प्रकार show_value(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा hid_sensor_custom *sensor_inst = dev_get_drvdata(dev);
	काष्ठा hid_sensor_hub_attribute_info *attribute;
	पूर्णांक index, usage, field_index;
	अक्षर name[HID_CUSTOM_NAME_LENGTH];
	bool feature = false;
	bool input = false;
	पूर्णांक value = 0;

	अगर (माला_पूछो(attr->attr.name, "feature-%x-%x-%s", &index, &usage,
		   name) == 3) अणु
		feature = true;
		field_index = index + sensor_inst->input_field_count;
	पूर्ण अन्यथा अगर (माला_पूछो(attr->attr.name, "input-%x-%x-%s", &index, &usage,
		   name) == 3) अणु
		input = true;
		field_index = index;
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (!म_भेदन(name, "value", म_माप("value"))) अणु
		u32 report_id;
		पूर्णांक ret;

		attribute = &sensor_inst->fields[field_index].attribute;
		report_id = attribute->report_id;
		अगर (feature) अणु
			u8 values[HID_CUSTOM_MAX_FEATURE_BYTES];
			पूर्णांक len = 0;
			u64 value = 0;
			पूर्णांक i = 0;

			ret = sensor_hub_get_feature(sensor_inst->hsdev,
						     report_id,
						     index,
						     माप(values), values);
			अगर (ret < 0)
				वापस ret;

			जबतक (i < ret) अणु
				अगर (i + attribute->size > ret) अणु
					len += scnम_लिखो(&buf[len],
							PAGE_SIZE - len,
							"%d ", values[i]);
					अवरोध;
				पूर्ण
				चयन (attribute->size) अणु
				हाल 2:
					value = (u64) *(u16 *)&values[i];
					i += attribute->size;
					अवरोध;
				हाल 4:
					value = (u64) *(u32 *)&values[i];
					i += attribute->size;
					अवरोध;
				हाल 8:
					value = *(u64 *)&values[i];
					i += attribute->size;
					अवरोध;
				शेष:
					value = (u64) values[i];
					++i;
					अवरोध;
				पूर्ण
				len += scnम_लिखो(&buf[len], PAGE_SIZE - len,
						"%lld ", value);
			पूर्ण
			len += scnम_लिखो(&buf[len], PAGE_SIZE - len, "\n");

			वापस len;
		पूर्ण अन्यथा अगर (input)
			value = sensor_hub_input_attr_get_raw_value(
						sensor_inst->hsdev,
						sensor_inst->hsdev->usage,
						usage, report_id,
						SENSOR_HUB_SYNC, false);
	पूर्ण अन्यथा अगर (!म_भेदन(name, "units", म_माप("units")))
		value = sensor_inst->fields[field_index].attribute.units;
	अन्यथा अगर (!म_भेदन(name, "unit-expo", म_माप("unit-expo")))
		value = sensor_inst->fields[field_index].attribute.unit_expo;
	अन्यथा अगर (!म_भेदन(name, "size", म_माप("size")))
		value = sensor_inst->fields[field_index].attribute.size;
	अन्यथा अगर (!म_भेदन(name, "minimum", म_माप("minimum")))
		value = sensor_inst->fields[field_index].attribute.
							logical_minimum;
	अन्यथा अगर (!म_भेदन(name, "maximum", म_माप("maximum")))
		value = sensor_inst->fields[field_index].attribute.
							logical_maximum;
	अन्यथा अगर (!म_भेदन(name, "name", म_माप("name"))) अणु
		काष्ठा hid_custom_usage_desc *usage_desc;

		usage_desc = द्वा_खोज(&usage, hid_custom_usage_desc_table,
				     ARRAY_SIZE(hid_custom_usage_desc_table),
				     माप(काष्ठा hid_custom_usage_desc),
				     usage_id_cmp);
		अगर (usage_desc)
			वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
					usage_desc->desc);
		अन्यथा
			वापस प्र_लिखो(buf, "not-specified\n");
	 पूर्ण अन्यथा
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार store_value(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_sensor_custom *sensor_inst = dev_get_drvdata(dev);
	पूर्णांक index, field_index, usage;
	अक्षर name[HID_CUSTOM_NAME_LENGTH];
	पूर्णांक value, ret;

	अगर (माला_पूछो(attr->attr.name, "feature-%x-%x-%s", &index, &usage,
		   name) == 3) अणु
		field_index = index + sensor_inst->input_field_count;
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (!म_भेदन(name, "value", म_माप("value"))) अणु
		u32 report_id;

		अगर (kstrtoपूर्णांक(buf, 0, &value) != 0)
			वापस -EINVAL;

		report_id = sensor_inst->fields[field_index].attribute.
								report_id;
		ret = sensor_hub_set_feature(sensor_inst->hsdev, report_id,
					     index, माप(value), &value);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल पूर्णांक hid_sensor_capture_sample(काष्ठा hid_sensor_hub_device *hsdev,
				  अचिन्हित usage_id, माप_प्रकार raw_len,
				  अक्षर *raw_data, व्योम *priv)
अणु
	काष्ठा hid_sensor_custom *sensor_inst = platक्रमm_get_drvdata(priv);
	काष्ठा hid_sensor_sample header;

	/* If any error occurs in a sample, rest of the fields are ignored */
	अगर (sensor_inst->input_skip_sample) अणु
		hid_err(sensor_inst->hsdev->hdev, "Skipped remaining data\n");
		वापस 0;
	पूर्ण

	hid_dbg(sensor_inst->hsdev->hdev, "%s received %d of %d\n", __func__,
		(पूर्णांक) (sensor_inst->input_report_recd_size + raw_len),
		sensor_inst->input_report_size);

	अगर (!test_bit(0, &sensor_inst->misc_खोलोed))
		वापस 0;

	अगर (!sensor_inst->input_report_recd_size) अणु
		पूर्णांक required_size = माप(काष्ठा hid_sensor_sample) +
						sensor_inst->input_report_size;
		header.usage_id = hsdev->usage;
		header.raw_len = sensor_inst->input_report_size;
		header.बारtamp = kसमय_get_real_ns();
		अगर (kfअगरo_avail(&sensor_inst->data_fअगरo) >= required_size) अणु
			kfअगरo_in(&sensor_inst->data_fअगरo,
				 (अचिन्हित अक्षर *)&header,
				 माप(header));
		पूर्ण अन्यथा
			sensor_inst->input_skip_sample = true;
	पूर्ण
	अगर (kfअगरo_avail(&sensor_inst->data_fअगरo) >= raw_len)
		kfअगरo_in(&sensor_inst->data_fअगरo, (अचिन्हित अक्षर *)raw_data,
			 raw_len);

	sensor_inst->input_report_recd_size += raw_len;

	वापस 0;
पूर्ण

अटल पूर्णांक hid_sensor_send_event(काष्ठा hid_sensor_hub_device *hsdev,
				 अचिन्हित usage_id, व्योम *priv)
अणु
	काष्ठा hid_sensor_custom *sensor_inst = platक्रमm_get_drvdata(priv);

	अगर (!test_bit(0, &sensor_inst->misc_खोलोed))
		वापस 0;

	sensor_inst->input_report_recd_size = 0;
	sensor_inst->input_skip_sample = false;

	wake_up(&sensor_inst->रुको);

	वापस 0;
पूर्ण

अटल पूर्णांक hid_sensor_custom_add_field(काष्ठा hid_sensor_custom *sensor_inst,
				       पूर्णांक index, पूर्णांक report_type,
				       काष्ठा hid_report *report,
				       काष्ठा hid_field *field)
अणु
	काष्ठा hid_sensor_custom_field *sensor_field;
	व्योम *fields;

	fields = kपुनः_स्मृति(sensor_inst->fields,
			  (sensor_inst->sensor_field_count + 1) *
			   माप(काष्ठा hid_sensor_custom_field), GFP_KERNEL);
	अगर (!fields) अणु
		kमुक्त(sensor_inst->fields);
		वापस -ENOMEM;
	पूर्ण
	sensor_inst->fields = fields;
	sensor_field = &sensor_inst->fields[sensor_inst->sensor_field_count];
	sensor_field->attribute.usage_id = sensor_inst->hsdev->usage;
	अगर (field->logical)
		sensor_field->attribute.attrib_id = field->logical;
	अन्यथा
		sensor_field->attribute.attrib_id = field->usage[0].hid;

	sensor_field->attribute.index = index;
	sensor_field->attribute.report_id = report->id;
	sensor_field->attribute.units = field->unit;
	sensor_field->attribute.unit_expo = field->unit_exponent;
	sensor_field->attribute.size = (field->report_size / 8);
	sensor_field->attribute.logical_minimum = field->logical_minimum;
	sensor_field->attribute.logical_maximum = field->logical_maximum;

	अगर (report_type == HID_FEATURE_REPORT)
		snम_लिखो(sensor_field->group_name,
			 माप(sensor_field->group_name), "feature-%x-%x",
			 sensor_field->attribute.index,
			 sensor_field->attribute.attrib_id);
	अन्यथा अगर (report_type == HID_INPUT_REPORT) अणु
		snम_लिखो(sensor_field->group_name,
			 माप(sensor_field->group_name),
			 "input-%x-%x", sensor_field->attribute.index,
			 sensor_field->attribute.attrib_id);
		sensor_inst->input_field_count++;
		sensor_inst->input_report_size += (field->report_size *
						   field->report_count) / 8;
	पूर्ण

	स_रखो(&sensor_field->hid_custom_attribute_group, 0,
	       माप(काष्ठा attribute_group));
	sensor_inst->sensor_field_count++;

	वापस 0;
पूर्ण

अटल पूर्णांक hid_sensor_custom_add_fields(काष्ठा hid_sensor_custom *sensor_inst,
					काष्ठा hid_report_क्रमागत *report_क्रमागत,
					पूर्णांक report_type)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा hid_report *report;
	काष्ठा hid_field *field;
	काष्ठा hid_sensor_hub_device *hsdev = sensor_inst->hsdev;

	list_क्रम_each_entry(report, &report_क्रमागत->report_list, list) अणु
		क्रम (i = 0; i < report->maxfield; ++i) अणु
			field = report->field[i];
			अगर (field->maxusage &&
			    ((field->usage[0].collection_index >=
			      hsdev->start_collection_index) &&
			      (field->usage[0].collection_index <
			       hsdev->end_collection_index))) अणु

				ret = hid_sensor_custom_add_field(sensor_inst,
								  i,
								  report_type,
								  report,
								  field);
				अगर (ret)
					वापस ret;

			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hid_sensor_custom_add_attributes(काष्ठा hid_sensor_custom
								*sensor_inst)
अणु
	काष्ठा hid_sensor_hub_device *hsdev = sensor_inst->hsdev;
	काष्ठा hid_device *hdev = hsdev->hdev;
	पूर्णांक ret = -1;
	पूर्णांक i, j;

	क्रम (j = 0; j < HID_REPORT_TYPES; ++j) अणु
		अगर (j == HID_OUTPUT_REPORT)
			जारी;

		ret = hid_sensor_custom_add_fields(sensor_inst,
						   &hdev->report_क्रमागत[j], j);
		अगर (ret)
			वापस ret;

	पूर्ण

	/* Create sysfs attributes */
	क्रम (i = 0; i < sensor_inst->sensor_field_count; ++i) अणु
		j = 0;
		जबतक (j < HID_CUSTOM_TOTAL_ATTRS &&
		       hid_custom_attrs[j].name) अणु
			काष्ठा device_attribute *device_attr;

			device_attr = &sensor_inst->fields[i].sd_attrs[j];

			snम_लिखो((अक्षर *)&sensor_inst->fields[i].attr_name[j],
				 HID_CUSTOM_NAME_LENGTH, "%s-%s",
				 sensor_inst->fields[i].group_name,
				 hid_custom_attrs[j].name);
			sysfs_attr_init(&device_attr->attr);
			device_attr->attr.name =
				(अक्षर *)&sensor_inst->fields[i].attr_name[j];
			device_attr->attr.mode = hid_custom_attrs[j].mode;
			device_attr->show = show_value;
			अगर (hid_custom_attrs[j].mode & S_IWUSR)
				device_attr->store = store_value;
			sensor_inst->fields[i].attrs[j] = &device_attr->attr;
			++j;
		पूर्ण
		sensor_inst->fields[i].attrs[j] = शून्य;
		sensor_inst->fields[i].hid_custom_attribute_group.attrs =
						sensor_inst->fields[i].attrs;
		sensor_inst->fields[i].hid_custom_attribute_group.name =
					sensor_inst->fields[i].group_name;
		ret = sysfs_create_group(&sensor_inst->pdev->dev.kobj,
					 &sensor_inst->fields[i].
					 hid_custom_attribute_group);
		अगर (ret)
			अवरोध;

		/* For घातer or report field store indexes */
		अगर (sensor_inst->fields[i].attribute.attrib_id ==
					HID_USAGE_SENSOR_PROY_POWER_STATE)
			sensor_inst->घातer_state = &sensor_inst->fields[i];
		अन्यथा अगर (sensor_inst->fields[i].attribute.attrib_id ==
					HID_USAGE_SENSOR_PROP_REPORT_STATE)
			sensor_inst->report_state = &sensor_inst->fields[i];
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hid_sensor_custom_हटाओ_attributes(काष्ठा hid_sensor_custom *
								sensor_inst)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sensor_inst->sensor_field_count; ++i)
		sysfs_हटाओ_group(&sensor_inst->pdev->dev.kobj,
				   &sensor_inst->fields[i].
				   hid_custom_attribute_group);

	kमुक्त(sensor_inst->fields);
पूर्ण

अटल sमाप_प्रकार hid_sensor_custom_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				      माप_प्रकार count, loff_t *f_ps)
अणु
	काष्ठा hid_sensor_custom *sensor_inst;
	अचिन्हित पूर्णांक copied;
	पूर्णांक ret;

	sensor_inst = container_of(file->निजी_data,
				   काष्ठा hid_sensor_custom, custom_dev);

	अगर (count < माप(काष्ठा hid_sensor_sample))
		वापस -EINVAL;

	करो अणु
		अगर (kfअगरo_is_empty(&sensor_inst->data_fअगरo)) अणु
			अगर (file->f_flags & O_NONBLOCK)
				वापस -EAGAIN;

			ret = रुको_event_पूर्णांकerruptible(sensor_inst->रुको,
				!kfअगरo_is_empty(&sensor_inst->data_fअगरo));
			अगर (ret)
				वापस ret;
		पूर्ण
		ret = kfअगरo_to_user(&sensor_inst->data_fअगरo, buf, count,
				    &copied);
		अगर (ret)
			वापस ret;

	पूर्ण जबतक (copied == 0);

	वापस copied;
पूर्ण

अटल पूर्णांक hid_sensor_custom_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hid_sensor_custom *sensor_inst;

	sensor_inst = container_of(file->निजी_data,
				   काष्ठा hid_sensor_custom, custom_dev);

	clear_bit(0, &sensor_inst->misc_खोलोed);

	वापस 0;
पूर्ण

अटल पूर्णांक hid_sensor_custom_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hid_sensor_custom *sensor_inst;

	sensor_inst = container_of(file->निजी_data,
				   काष्ठा hid_sensor_custom, custom_dev);
	/* We essentially have single पढ़ोer and ग_लिखोr */
	अगर (test_and_set_bit(0, &sensor_inst->misc_खोलोed))
		वापस -EBUSY;

	वापस stream_खोलो(inode, file);
पूर्ण

अटल __poll_t hid_sensor_custom_poll(काष्ठा file *file,
					   काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा hid_sensor_custom *sensor_inst;
	__poll_t mask = 0;

	sensor_inst = container_of(file->निजी_data,
				   काष्ठा hid_sensor_custom, custom_dev);

	poll_रुको(file, &sensor_inst->रुको, रुको);

	अगर (!kfअगरo_is_empty(&sensor_inst->data_fअगरo))
		mask = EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations hid_sensor_custom_fops = अणु
	.खोलो =  hid_sensor_custom_खोलो,
	.पढ़ो =  hid_sensor_custom_पढ़ो,
	.release = hid_sensor_custom_release,
	.poll = hid_sensor_custom_poll,
	.llseek = noop_llseek,
पूर्ण;

अटल पूर्णांक hid_sensor_custom_dev_अगर_add(काष्ठा hid_sensor_custom *sensor_inst)
अणु
	पूर्णांक ret;

	ret = kfअगरo_alloc(&sensor_inst->data_fअगरo, HID_CUSTOM_FIFO_SIZE,
			  GFP_KERNEL);
	अगर (ret)
		वापस ret;

	init_रुकोqueue_head(&sensor_inst->रुको);

	sensor_inst->custom_dev.minor = MISC_DYNAMIC_MINOR;
	sensor_inst->custom_dev.name = dev_name(&sensor_inst->pdev->dev);
	sensor_inst->custom_dev.fops = &hid_sensor_custom_fops,
	ret = misc_रेजिस्टर(&sensor_inst->custom_dev);
	अगर (ret) अणु
		kfअगरo_मुक्त(&sensor_inst->data_fअगरo);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hid_sensor_custom_dev_अगर_हटाओ(काष्ठा hid_sensor_custom
								*sensor_inst)
अणु
	wake_up(&sensor_inst->रुको);
	misc_deरेजिस्टर(&sensor_inst->custom_dev);
	kfअगरo_मुक्त(&sensor_inst->data_fअगरo);

पूर्ण

/* luid defined in FW (e.g. ISH).  Maybe used to identअगरy sensor. */
अटल स्थिर अक्षर *स्थिर known_sensor_luid[] = अणु "020B000000000000" पूर्ण;

अटल पूर्णांक get_luid_table_index(अचिन्हित अक्षर *usage_str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(known_sensor_luid); i++) अणु
		अगर (!म_भेदन(usage_str, known_sensor_luid[i],
			     म_माप(known_sensor_luid[i])))
			वापस i;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक get_known_custom_sensor_index(काष्ठा hid_sensor_hub_device *hsdev)
अणु
	काष्ठा hid_sensor_hub_attribute_info sensor_manufacturer = अणु 0 पूर्ण;
	काष्ठा hid_sensor_hub_attribute_info sensor_luid_info = अणु 0 पूर्ण;
	पूर्णांक report_size;
	पूर्णांक ret;
	अटल u16 w_buf[HID_CUSTOM_MAX_FEATURE_BYTES];
	अटल अक्षर buf[HID_CUSTOM_MAX_FEATURE_BYTES];
	पूर्णांक i;

	स_रखो(w_buf, 0, माप(w_buf));
	स_रखो(buf, 0, माप(buf));

	/* get manufacturer info */
	ret = sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, hsdev->usage,
			HID_USAGE_SENSOR_PROP_MANUFACTURER, &sensor_manufacturer);
	अगर (ret < 0)
		वापस ret;

	report_size =
		sensor_hub_get_feature(hsdev, sensor_manufacturer.report_id,
				       sensor_manufacturer.index, माप(w_buf),
				       w_buf);
	अगर (report_size <= 0) अणु
		hid_err(hsdev->hdev,
			"Failed to get sensor manufacturer info %d\n",
			report_size);
		वापस -ENODEV;
	पूर्ण

	/* convert from wide अक्षर to अक्षर */
	क्रम (i = 0; i < ARRAY_SIZE(buf) - 1 && w_buf[i]; i++)
		buf[i] = (अक्षर)w_buf[i];

	/* ensure it's ISH sensor */
	अगर (म_भेदन(buf, "INTEL", म_माप("INTEL")))
		वापस -ENODEV;

	स_रखो(w_buf, 0, माप(w_buf));
	स_रखो(buf, 0, माप(buf));

	/* get real usage id */
	ret = sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, hsdev->usage,
			HID_USAGE_SENSOR_PROP_SERIAL_NUM, &sensor_luid_info);
	अगर (ret < 0)
		वापस ret;

	report_size = sensor_hub_get_feature(hsdev, sensor_luid_info.report_id,
					     sensor_luid_info.index, माप(w_buf),
					     w_buf);
	अगर (report_size <= 0) अणु
		hid_err(hsdev->hdev, "Failed to get real usage info %d\n",
			report_size);
		वापस -ENODEV;
	पूर्ण

	/* convert from wide अक्षर to अक्षर */
	क्रम (i = 0; i < ARRAY_SIZE(buf) - 1 && w_buf[i]; i++)
		buf[i] = (अक्षर)w_buf[i];

	अगर (म_माप(buf) != म_माप(known_sensor_luid[0]) + 5) अणु
		hid_err(hsdev->hdev,
			"%s luid length not match %zu != (%zu + 5)\n", __func__,
			म_माप(buf), म_माप(known_sensor_luid[0]));
		वापस -ENODEV;
	पूर्ण

	/* get table index with luid (not matching 'LUID: ' in luid) */
	वापस get_luid_table_index(&buf[5]);
पूर्ण

अटल काष्ठा platक्रमm_device *
hid_sensor_रेजिस्टर_platक्रमm_device(काष्ठा platक्रमm_device *pdev,
				    काष्ठा hid_sensor_hub_device *hsdev,
				    पूर्णांक index)
अणु
	अक्षर real_usage[HID_SENSOR_USAGE_LENGTH] = अणु 0 पूर्ण;
	काष्ठा platक्रमm_device *custom_pdev;
	स्थिर अक्षर *dev_name;
	अक्षर *c;

	/* copy real usage id */
	स_नकल(real_usage, known_sensor_luid[index], 4);

	/* usage id are all lowहाल */
	क्रम (c = real_usage; *c != '\0'; c++)
		*c = छोटे(*c);

	/* HID-SENSOR-INT-REAL_USAGE_ID */
	dev_name = kaप्र_लिखो(GFP_KERNEL, "HID-SENSOR-INT-%s", real_usage);
	अगर (!dev_name)
		वापस ERR_PTR(-ENOMEM);

	custom_pdev = platक्रमm_device_रेजिस्टर_data(pdev->dev.parent, dev_name,
						    PLATFORM_DEVID_NONE, hsdev,
						    माप(*hsdev));
	kमुक्त(dev_name);
	वापस custom_pdev;
पूर्ण

अटल पूर्णांक hid_sensor_custom_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_custom *sensor_inst;
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;
	पूर्णांक ret;
	पूर्णांक index;

	sensor_inst = devm_kzalloc(&pdev->dev, माप(*sensor_inst),
				   GFP_KERNEL);
	अगर (!sensor_inst)
		वापस -ENOMEM;

	sensor_inst->callbacks.capture_sample = hid_sensor_capture_sample;
	sensor_inst->callbacks.send_event = hid_sensor_send_event;
	sensor_inst->callbacks.pdev = pdev;
	sensor_inst->hsdev = hsdev;
	sensor_inst->pdev = pdev;
	mutex_init(&sensor_inst->mutex);
	platक्रमm_set_drvdata(pdev, sensor_inst);

	index = get_known_custom_sensor_index(hsdev);
	अगर (index >= 0 && index < ARRAY_SIZE(known_sensor_luid)) अणु
		sensor_inst->custom_pdev =
			hid_sensor_रेजिस्टर_platक्रमm_device(pdev, hsdev, index);

		ret = PTR_ERR_OR_ZERO(sensor_inst->custom_pdev);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"register_platform_device failed\n");
			वापस ret;
		पूर्ण

		वापस 0;
	पूर्ण

	ret = sensor_hub_रेजिस्टर_callback(hsdev, hsdev->usage,
					   &sensor_inst->callbacks);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "callback reg failed\n");
		वापस ret;
	पूर्ण

	ret = sysfs_create_group(&sensor_inst->pdev->dev.kobj,
				 &enable_sensor_attr_group);
	अगर (ret)
		जाओ err_हटाओ_callback;

	ret = hid_sensor_custom_add_attributes(sensor_inst);
	अगर (ret)
		जाओ err_हटाओ_group;

	ret = hid_sensor_custom_dev_अगर_add(sensor_inst);
	अगर (ret)
		जाओ err_हटाओ_attributes;

	वापस 0;

err_हटाओ_attributes:
	hid_sensor_custom_हटाओ_attributes(sensor_inst);
err_हटाओ_group:
	sysfs_हटाओ_group(&sensor_inst->pdev->dev.kobj,
			   &enable_sensor_attr_group);
err_हटाओ_callback:
	sensor_hub_हटाओ_callback(hsdev, hsdev->usage);

	वापस ret;
पूर्ण

अटल पूर्णांक hid_sensor_custom_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_custom *sensor_inst = platक्रमm_get_drvdata(pdev);
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;

	अगर (sensor_inst->custom_pdev) अणु
		platक्रमm_device_unरेजिस्टर(sensor_inst->custom_pdev);
		वापस 0;
	पूर्ण

	hid_sensor_custom_dev_अगर_हटाओ(sensor_inst);
	hid_sensor_custom_हटाओ_attributes(sensor_inst);
	sysfs_हटाओ_group(&sensor_inst->pdev->dev.kobj,
			   &enable_sensor_attr_group);
	sensor_hub_हटाओ_callback(hsdev, hsdev->usage);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hid_sensor_custom_ids[] = अणु
	अणु
		.name = "HID-SENSOR-2000e1",
	पूर्ण,
	अणु
		.name = "HID-SENSOR-2000e2",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hid_sensor_custom_ids);

अटल काष्ठा platक्रमm_driver hid_sensor_custom_platक्रमm_driver = अणु
	.id_table = hid_sensor_custom_ids,
	.driver = अणु
		.name	= KBUILD_MODNAME,
	पूर्ण,
	.probe		= hid_sensor_custom_probe,
	.हटाओ		= hid_sensor_custom_हटाओ,
पूर्ण;
module_platक्रमm_driver(hid_sensor_custom_platक्रमm_driver);

MODULE_DESCRIPTION("HID Sensor Custom and Generic sensor Driver");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL");
