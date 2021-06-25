<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dell WMI descriptor driver
 *
 * Copyright (C) 2017 Dell Inc. All Rights Reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/wmi.h>
#समावेश "dell-wmi-descriptor.h"

#घोषणा DELL_WMI_DESCRIPTOR_GUID "8D9DDCBC-A997-11DA-B012-B622A1EF5492"

काष्ठा descriptor_priv अणु
	काष्ठा list_head list;
	u32 पूर्णांकerface_version;
	u32 size;
	u32 hotfix;
पूर्ण;
अटल पूर्णांक descriptor_valid = -EPROBE_DEFER;
अटल LIST_HEAD(wmi_list);
अटल DEFINE_MUTEX(list_mutex);

पूर्णांक dell_wmi_get_descriptor_valid(व्योम)
अणु
	अगर (!wmi_has_guid(DELL_WMI_DESCRIPTOR_GUID))
		वापस -ENODEV;

	वापस descriptor_valid;
पूर्ण
EXPORT_SYMBOL_GPL(dell_wmi_get_descriptor_valid);

bool dell_wmi_get_पूर्णांकerface_version(u32 *version)
अणु
	काष्ठा descriptor_priv *priv;
	bool ret = false;

	mutex_lock(&list_mutex);
	priv = list_first_entry_or_null(&wmi_list,
					काष्ठा descriptor_priv,
					list);
	अगर (priv) अणु
		*version = priv->पूर्णांकerface_version;
		ret = true;
	पूर्ण
	mutex_unlock(&list_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dell_wmi_get_पूर्णांकerface_version);

bool dell_wmi_get_size(u32 *size)
अणु
	काष्ठा descriptor_priv *priv;
	bool ret = false;

	mutex_lock(&list_mutex);
	priv = list_first_entry_or_null(&wmi_list,
					काष्ठा descriptor_priv,
					list);
	अगर (priv) अणु
		*size = priv->size;
		ret = true;
	पूर्ण
	mutex_unlock(&list_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dell_wmi_get_size);

bool dell_wmi_get_hotfix(u32 *hotfix)
अणु
	काष्ठा descriptor_priv *priv;
	bool ret = false;

	mutex_lock(&list_mutex);
	priv = list_first_entry_or_null(&wmi_list,
					काष्ठा descriptor_priv,
					list);
	अगर (priv) अणु
		*hotfix = priv->hotfix;
		ret = true;
	पूर्ण
	mutex_unlock(&list_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dell_wmi_get_hotfix);

/*
 * Descriptor buffer is 128 byte दीर्घ and contains:
 *
 *       Name             Offset  Length  Value
 * Venकरोr Signature          0       4    "DELL"
 * Object Signature          4       4    " WMI"
 * WMI Interface Version     8       4    <version>
 * WMI buffer length        12       4    <length>
 * WMI hotfix number        16       4    <hotfix>
 */
अटल पूर्णांक dell_wmi_descriptor_probe(काष्ठा wmi_device *wdev,
				     स्थिर व्योम *context)
अणु
	जोड़ acpi_object *obj = शून्य;
	काष्ठा descriptor_priv *priv;
	u32 *buffer;
	पूर्णांक ret;

	obj = wmidev_block_query(wdev, 0);
	अगर (!obj) अणु
		dev_err(&wdev->dev, "failed to read Dell WMI descriptor\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		dev_err(&wdev->dev, "Dell descriptor has wrong type\n");
		ret = -EINVAL;
		descriptor_valid = ret;
		जाओ out;
	पूर्ण

	/* Although it's not technically a failure, this would lead to
	 * unexpected behavior
	 */
	अगर (obj->buffer.length != 128) अणु
		dev_err(&wdev->dev,
			"Dell descriptor buffer has unexpected length (%d)\n",
			obj->buffer.length);
		ret = -EINVAL;
		descriptor_valid = ret;
		जाओ out;
	पूर्ण

	buffer = (u32 *)obj->buffer.poपूर्णांकer;

	अगर (म_भेदन(obj->string.poपूर्णांकer, "DELL WMI", 8) != 0) अणु
		dev_err(&wdev->dev, "Dell descriptor buffer has invalid signature (%8ph)\n",
			buffer);
		ret = -EINVAL;
		descriptor_valid = ret;
		जाओ out;
	पूर्ण
	descriptor_valid = 0;

	अगर (buffer[2] != 0 && buffer[2] != 1)
		dev_warn(&wdev->dev, "Dell descriptor buffer has unknown version (%lu)\n",
			(अचिन्हित दीर्घ) buffer[2]);

	priv = devm_kzalloc(&wdev->dev, माप(काष्ठा descriptor_priv),
	GFP_KERNEL);

	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	priv->पूर्णांकerface_version = buffer[2];
	priv->size = buffer[3];
	priv->hotfix = buffer[4];
	ret = 0;
	dev_set_drvdata(&wdev->dev, priv);
	mutex_lock(&list_mutex);
	list_add_tail(&priv->list, &wmi_list);
	mutex_unlock(&list_mutex);

	dev_dbg(&wdev->dev, "Detected Dell WMI interface version %lu, buffer size %lu, hotfix %lu\n",
		(अचिन्हित दीर्घ) priv->पूर्णांकerface_version,
		(अचिन्हित दीर्घ) priv->size,
		(अचिन्हित दीर्घ) priv->hotfix);

out:
	kमुक्त(obj);
	वापस ret;
पूर्ण

अटल व्योम dell_wmi_descriptor_हटाओ(काष्ठा wmi_device *wdev)
अणु
	काष्ठा descriptor_priv *priv = dev_get_drvdata(&wdev->dev);

	mutex_lock(&list_mutex);
	list_del(&priv->list);
	mutex_unlock(&list_mutex);
पूर्ण

अटल स्थिर काष्ठा wmi_device_id dell_wmi_descriptor_id_table[] = अणु
	अणु .guid_string = DELL_WMI_DESCRIPTOR_GUID पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा wmi_driver dell_wmi_descriptor_driver = अणु
	.driver = अणु
		.name = "dell-wmi-descriptor",
	पूर्ण,
	.probe = dell_wmi_descriptor_probe,
	.हटाओ = dell_wmi_descriptor_हटाओ,
	.id_table = dell_wmi_descriptor_id_table,
पूर्ण;

module_wmi_driver(dell_wmi_descriptor_driver);

MODULE_DEVICE_TABLE(wmi, dell_wmi_descriptor_id_table);
MODULE_AUTHOR("Mario Limonciello <mario.limonciello@outlook.com>");
MODULE_DESCRIPTION("Dell WMI descriptor driver");
MODULE_LICENSE("GPL");
