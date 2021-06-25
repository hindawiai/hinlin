<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* WMI driver क्रम Xiaomi Laptops */

#समावेश <linux/acpi.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/wmi.h>

#समावेश <uapi/linux/input-event-codes.h>

#घोषणा XIAOMI_KEY_FN_ESC_0	"A2095CCE-0491-44E7-BA27-F8ED8F88AA86"
#घोषणा XIAOMI_KEY_FN_ESC_1	"7BBE8E39-B486-473D-BA13-66F75C5805CD"
#घोषणा XIAOMI_KEY_FN_FN	"409B028D-F06B-4C7C-8BBB-EE133A6BD87E"
#घोषणा XIAOMI_KEY_CAPSLOCK	"83FE7607-053A-4644-822A-21532C621FC7"
#घोषणा XIAOMI_KEY_FN_F7	"76E9027C-95D0-4180-8692-DA6747DD1C2D"

#घोषणा XIAOMI_DEVICE(guid, key)		\
	.guid_string = (guid),			\
	.context = &(स्थिर अचिन्हित पूर्णांक)अणुkeyपूर्ण

काष्ठा xiaomi_wmi अणु
	काष्ठा input_dev *input_dev;
	अचिन्हित पूर्णांक key_code;
पूर्ण;

अटल पूर्णांक xiaomi_wmi_probe(काष्ठा wmi_device *wdev, स्थिर व्योम *context)
अणु
	काष्ठा xiaomi_wmi *data;

	अगर (wdev == शून्य || context == शून्य)
		वापस -EINVAL;

	data = devm_kzalloc(&wdev->dev, माप(काष्ठा xiaomi_wmi), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;
	dev_set_drvdata(&wdev->dev, data);

	data->input_dev = devm_input_allocate_device(&wdev->dev);
	अगर (data->input_dev == शून्य)
		वापस -ENOMEM;
	data->input_dev->name = "Xiaomi WMI keys";
	data->input_dev->phys = "wmi/input0";

	data->key_code = *((स्थिर अचिन्हित पूर्णांक *)context);
	set_bit(EV_KEY, data->input_dev->evbit);
	set_bit(data->key_code, data->input_dev->keybit);

	वापस input_रेजिस्टर_device(data->input_dev);
पूर्ण

अटल व्योम xiaomi_wmi_notअगरy(काष्ठा wmi_device *wdev, जोड़ acpi_object *dummy)
अणु
	काष्ठा xiaomi_wmi *data;

	अगर (wdev == शून्य)
		वापस;

	data = dev_get_drvdata(&wdev->dev);
	अगर (data == शून्य)
		वापस;

	input_report_key(data->input_dev, data->key_code, 1);
	input_sync(data->input_dev);
	input_report_key(data->input_dev, data->key_code, 0);
	input_sync(data->input_dev);
पूर्ण

अटल स्थिर काष्ठा wmi_device_id xiaomi_wmi_id_table[] = अणु
	// अणु XIAOMI_DEVICE(XIAOMI_KEY_FN_ESC_0, KEY_FN_ESC) पूर्ण,
	// अणु XIAOMI_DEVICE(XIAOMI_KEY_FN_ESC_1, KEY_FN_ESC) पूर्ण,
	अणु XIAOMI_DEVICE(XIAOMI_KEY_FN_FN, KEY_PROG1) पूर्ण,
	// अणु XIAOMI_DEVICE(XIAOMI_KEY_CAPSLOCK, KEY_CAPSLOCK) पूर्ण,
	अणु XIAOMI_DEVICE(XIAOMI_KEY_FN_F7, KEY_CUT) पूर्ण,

	/* Terminating entry */
	अणु पूर्ण
पूर्ण;

अटल काष्ठा wmi_driver xiaomi_wmi_driver = अणु
	.driver = अणु
		.name = "xiaomi-wmi",
	पूर्ण,
	.id_table = xiaomi_wmi_id_table,
	.probe = xiaomi_wmi_probe,
	.notअगरy = xiaomi_wmi_notअगरy,
पूर्ण;
module_wmi_driver(xiaomi_wmi_driver);

MODULE_DEVICE_TABLE(wmi, xiaomi_wmi_id_table);
MODULE_AUTHOR("Mattias Jacobsson");
MODULE_DESCRIPTION("Xiaomi WMI driver");
MODULE_LICENSE("GPL v2");
