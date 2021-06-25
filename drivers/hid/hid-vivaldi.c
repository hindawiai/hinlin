<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * HID support क्रम Vivaldi Keyboard
 *
 * Copyright 2020 Google LLC.
 * Author: Sean O'Brien <seobrien@chromium.org>
 */

#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#घोषणा MIN_FN_ROW_KEY	1
#घोषणा MAX_FN_ROW_KEY	24
#घोषणा HID_VD_FN_ROW_PHYSMAP 0x00000001
#घोषणा HID_USAGE_FN_ROW_PHYSMAP (HID_UP_GOOGLEVENDOR | HID_VD_FN_ROW_PHYSMAP)

अटल काष्ठा hid_driver hid_vivaldi;

काष्ठा vivaldi_data अणु
	u32 function_row_physmap[MAX_FN_ROW_KEY - MIN_FN_ROW_KEY + 1];
	पूर्णांक max_function_row_key;
पूर्ण;

अटल sमाप_प्रकार function_row_physmap_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा vivaldi_data *drvdata = hid_get_drvdata(hdev);
	sमाप_प्रकार size = 0;
	पूर्णांक i;

	अगर (!drvdata->max_function_row_key)
		वापस 0;

	क्रम (i = 0; i < drvdata->max_function_row_key; i++)
		size += प्र_लिखो(buf + size, "%02X ",
				drvdata->function_row_physmap[i]);
	size += प्र_लिखो(buf + size, "\n");
	वापस size;
पूर्ण

DEVICE_ATTR_RO(function_row_physmap);
अटल काष्ठा attribute *sysfs_attrs[] = अणु
	&dev_attr_function_row_physmap.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group input_attribute_group = अणु
	.attrs = sysfs_attrs
पूर्ण;

अटल पूर्णांक vivaldi_probe(काष्ठा hid_device *hdev,
			 स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा vivaldi_data *drvdata;
	पूर्णांक ret;

	drvdata = devm_kzalloc(&hdev->dev, माप(*drvdata), GFP_KERNEL);
	hid_set_drvdata(hdev, drvdata);

	ret = hid_parse(hdev);
	अगर (ret)
		वापस ret;

	वापस hid_hw_start(hdev, HID_CONNECT_DEFAULT);
पूर्ण

अटल व्योम vivaldi_feature_mapping(काष्ठा hid_device *hdev,
				    काष्ठा hid_field *field,
				    काष्ठा hid_usage *usage)
अणु
	काष्ठा vivaldi_data *drvdata = hid_get_drvdata(hdev);
	पूर्णांक fn_key;
	पूर्णांक ret;
	u32 report_len;
	u8 *buf;

	अगर (field->logical != HID_USAGE_FN_ROW_PHYSMAP ||
	    (usage->hid & HID_USAGE_PAGE) != HID_UP_ORDINAL)
		वापस;

	fn_key = (usage->hid & HID_USAGE);
	अगर (fn_key < MIN_FN_ROW_KEY || fn_key > MAX_FN_ROW_KEY)
		वापस;
	अगर (fn_key > drvdata->max_function_row_key)
		drvdata->max_function_row_key = fn_key;

	buf = hid_alloc_report_buf(field->report, GFP_KERNEL);
	अगर (!buf)
		वापस;

	report_len = hid_report_len(field->report);
	ret = hid_hw_raw_request(hdev, field->report->id, buf,
				 report_len, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	अगर (ret < 0) अणु
		dev_warn(&hdev->dev, "failed to fetch feature %d\n",
			 field->report->id);
		जाओ out;
	पूर्ण

	ret = hid_report_raw_event(hdev, HID_FEATURE_REPORT, buf,
				   report_len, 0);
	अगर (ret) अणु
		dev_warn(&hdev->dev, "failed to report feature %d\n",
			 field->report->id);
		जाओ out;
	पूर्ण

	drvdata->function_row_physmap[fn_key - MIN_FN_ROW_KEY] =
	    field->value[usage->usage_index];

out:
	kमुक्त(buf);
पूर्ण

अटल पूर्णांक vivaldi_input_configured(काष्ठा hid_device *hdev,
				    काष्ठा hid_input *hidinput)
अणु
	वापस sysfs_create_group(&hdev->dev.kobj, &input_attribute_group);
पूर्ण

अटल स्थिर काष्ठा hid_device_id vivaldi_table[] = अणु
	अणु HID_DEVICE(HID_BUS_ANY, HID_GROUP_VIVALDI, HID_ANY_ID,
		     HID_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, vivaldi_table);

अटल काष्ठा hid_driver hid_vivaldi = अणु
	.name = "hid-vivaldi",
	.id_table = vivaldi_table,
	.probe = vivaldi_probe,
	.feature_mapping = vivaldi_feature_mapping,
	.input_configured = vivaldi_input_configured,
पूर्ण;

module_hid_driver(hid_vivaldi);

MODULE_AUTHOR("Sean O'Brien");
MODULE_DESCRIPTION("HID vivaldi driver");
MODULE_LICENSE("GPL");
