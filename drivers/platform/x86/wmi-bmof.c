<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * WMI embedded Binary MOF driver
 *
 * Copyright (c) 2015 Andrew Lutomirski
 * Copyright (C) 2017 VMware, Inc. All Rights Reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <linux/wmi.h>

#घोषणा WMI_BMOF_GUID "05901221-D566-11D1-B2F0-00A0C9062910"

काष्ठा bmof_priv अणु
	जोड़ acpi_object *bmofdata;
	काष्ठा bin_attribute bmof_bin_attr;
पूर्ण;

अटल sमाप_प्रकार
पढ़ो_bmof(काष्ठा file *filp, काष्ठा kobject *kobj,
	 काष्ठा bin_attribute *attr,
	 अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा bmof_priv *priv =
		container_of(attr, काष्ठा bmof_priv, bmof_bin_attr);

	अगर (off < 0)
		वापस -EINVAL;

	अगर (off >= priv->bmofdata->buffer.length)
		वापस 0;

	अगर (count > priv->bmofdata->buffer.length - off)
		count = priv->bmofdata->buffer.length - off;

	स_नकल(buf, priv->bmofdata->buffer.poपूर्णांकer + off, count);
	वापस count;
पूर्ण

अटल पूर्णांक wmi_bmof_probe(काष्ठा wmi_device *wdev, स्थिर व्योम *context)
अणु
	काष्ठा bmof_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&wdev->dev, माप(काष्ठा bmof_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(&wdev->dev, priv);

	priv->bmofdata = wmidev_block_query(wdev, 0);
	अगर (!priv->bmofdata) अणु
		dev_err(&wdev->dev, "failed to read Binary MOF\n");
		वापस -EIO;
	पूर्ण

	अगर (priv->bmofdata->type != ACPI_TYPE_BUFFER) अणु
		dev_err(&wdev->dev, "Binary MOF is not a buffer\n");
		ret = -EIO;
		जाओ err_मुक्त;
	पूर्ण

	sysfs_bin_attr_init(&priv->bmof_bin_attr);
	priv->bmof_bin_attr.attr.name = "bmof";
	priv->bmof_bin_attr.attr.mode = 0400;
	priv->bmof_bin_attr.पढ़ो = पढ़ो_bmof;
	priv->bmof_bin_attr.size = priv->bmofdata->buffer.length;

	ret = sysfs_create_bin_file(&wdev->dev.kobj, &priv->bmof_bin_attr);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

 err_मुक्त:
	kमुक्त(priv->bmofdata);
	वापस ret;
पूर्ण

अटल व्योम wmi_bmof_हटाओ(काष्ठा wmi_device *wdev)
अणु
	काष्ठा bmof_priv *priv = dev_get_drvdata(&wdev->dev);

	sysfs_हटाओ_bin_file(&wdev->dev.kobj, &priv->bmof_bin_attr);
	kमुक्त(priv->bmofdata);
पूर्ण

अटल स्थिर काष्ठा wmi_device_id wmi_bmof_id_table[] = अणु
	अणु .guid_string = WMI_BMOF_GUID पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा wmi_driver wmi_bmof_driver = अणु
	.driver = अणु
		.name = "wmi-bmof",
	पूर्ण,
	.probe = wmi_bmof_probe,
	.हटाओ = wmi_bmof_हटाओ,
	.id_table = wmi_bmof_id_table,
पूर्ण;

module_wmi_driver(wmi_bmof_driver);

MODULE_DEVICE_TABLE(wmi, wmi_bmof_id_table);
MODULE_AUTHOR("Andrew Lutomirski <luto@kernel.org>");
MODULE_DESCRIPTION("WMI embedded Binary MOF driver");
MODULE_LICENSE("GPL");
