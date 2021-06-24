<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  WMI methods क्रम use with dell-smbios
 *
 *  Copyright (c) 2017 Dell Inc.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/dmi.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/wmi.h>
#समावेश "dell-smbios.h"
#समावेश "dell-wmi-descriptor.h"

अटल DEFINE_MUTEX(call_mutex);
अटल DEFINE_MUTEX(list_mutex);
अटल पूर्णांक wmi_supported;

काष्ठा misc_bios_flags_काष्ठाure अणु
	काष्ठा dmi_header header;
	u16 flags0;
पूर्ण __packed;
#घोषणा FLAG_HAS_ACPI_WMI 0x02

#घोषणा DELL_WMI_SMBIOS_GUID "A80593CE-A997-11DA-B012-B622A1EF5492"

काष्ठा wmi_smbios_priv अणु
	काष्ठा dell_wmi_smbios_buffer *buf;
	काष्ठा list_head list;
	काष्ठा wmi_device *wdev;
	काष्ठा device *child;
	u32 req_buf_size;
पूर्ण;
अटल LIST_HEAD(wmi_list);

अटल अंतरभूत काष्ठा wmi_smbios_priv *get_first_smbios_priv(व्योम)
अणु
	वापस list_first_entry_or_null(&wmi_list,
					काष्ठा wmi_smbios_priv,
					list);
पूर्ण

अटल पूर्णांक run_smbios_call(काष्ठा wmi_device *wdev)
अणु
	काष्ठा acpi_buffer output = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	काष्ठा wmi_smbios_priv *priv;
	काष्ठा acpi_buffer input;
	जोड़ acpi_object *obj;
	acpi_status status;

	priv = dev_get_drvdata(&wdev->dev);
	input.length = priv->req_buf_size - माप(u64);
	input.poपूर्णांकer = &priv->buf->std;

	dev_dbg(&wdev->dev, "evaluating: %u/%u [%x,%x,%x,%x]\n",
		priv->buf->std.cmd_class, priv->buf->std.cmd_select,
		priv->buf->std.input[0], priv->buf->std.input[1],
		priv->buf->std.input[2], priv->buf->std.input[3]);

	status = wmidev_evaluate_method(wdev, 0, 1, &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;
	obj = (जोड़ acpi_object *)output.poपूर्णांकer;
	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		dev_dbg(&wdev->dev, "received type: %d\n", obj->type);
		अगर (obj->type == ACPI_TYPE_INTEGER)
			dev_dbg(&wdev->dev, "SMBIOS call failed: %llu\n",
				obj->पूर्णांकeger.value);
		वापस -EIO;
	पूर्ण
	स_नकल(&priv->buf->std, obj->buffer.poपूर्णांकer, obj->buffer.length);
	dev_dbg(&wdev->dev, "result: [%08x,%08x,%08x,%08x]\n",
		priv->buf->std.output[0], priv->buf->std.output[1],
		priv->buf->std.output[2], priv->buf->std.output[3]);
	kमुक्त(output.poपूर्णांकer);

	वापस 0;
पूर्ण

अटल पूर्णांक dell_smbios_wmi_call(काष्ठा calling_पूर्णांकerface_buffer *buffer)
अणु
	काष्ठा wmi_smbios_priv *priv;
	माप_प्रकार dअगरference;
	माप_प्रकार size;
	पूर्णांक ret;

	mutex_lock(&call_mutex);
	priv = get_first_smbios_priv();
	अगर (!priv) अणु
		ret = -ENODEV;
		जाओ out_wmi_call;
	पूर्ण

	size = माप(काष्ठा calling_पूर्णांकerface_buffer);
	dअगरference = priv->req_buf_size - माप(u64) - size;

	स_रखो(&priv->buf->ext, 0, dअगरference);
	स_नकल(&priv->buf->std, buffer, size);
	ret = run_smbios_call(priv->wdev);
	स_नकल(buffer, &priv->buf->std, size);
out_wmi_call:
	mutex_unlock(&call_mutex);

	वापस ret;
पूर्ण

अटल दीर्घ dell_smbios_wmi_filter(काष्ठा wmi_device *wdev, अचिन्हित पूर्णांक cmd,
				   काष्ठा wmi_ioctl_buffer *arg)
अणु
	काष्ठा wmi_smbios_priv *priv;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल DELL_WMI_SMBIOS_CMD:
		mutex_lock(&call_mutex);
		priv = dev_get_drvdata(&wdev->dev);
		अगर (!priv) अणु
			ret = -ENODEV;
			जाओ fail_smbios_cmd;
		पूर्ण
		स_नकल(priv->buf, arg, priv->req_buf_size);
		अगर (dell_smbios_call_filter(&wdev->dev, &priv->buf->std)) अणु
			dev_err(&wdev->dev, "Invalid call %d/%d:%8x\n",
				priv->buf->std.cmd_class,
				priv->buf->std.cmd_select,
				priv->buf->std.input[0]);
			ret = -EFAULT;
			जाओ fail_smbios_cmd;
		पूर्ण
		ret = run_smbios_call(priv->wdev);
		अगर (ret)
			जाओ fail_smbios_cmd;
		स_नकल(arg, priv->buf, priv->req_buf_size);
fail_smbios_cmd:
		mutex_unlock(&call_mutex);
		अवरोध;
	शेष:
		ret = -ENOIOCTLCMD;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक dell_smbios_wmi_probe(काष्ठा wmi_device *wdev, स्थिर व्योम *context)
अणु
	काष्ठा wmi_driver *wdriver =
		container_of(wdev->dev.driver, काष्ठा wmi_driver, driver);
	काष्ठा wmi_smbios_priv *priv;
	u32 hotfix;
	पूर्णांक count;
	पूर्णांक ret;

	ret = dell_wmi_get_descriptor_valid();
	अगर (ret)
		वापस ret;

	priv = devm_kzalloc(&wdev->dev, माप(काष्ठा wmi_smbios_priv),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* WMI buffer size will be either 4k or 32k depending on machine */
	अगर (!dell_wmi_get_size(&priv->req_buf_size))
		वापस -EPROBE_DEFER;

	/* some SMBIOS calls fail unless BIOS contains hotfix */
	अगर (!dell_wmi_get_hotfix(&hotfix))
		वापस -EPROBE_DEFER;
	अगर (!hotfix) अणु
		dev_warn(&wdev->dev,
			"WMI SMBIOS userspace interface not supported(%u), try upgrading to a newer BIOS\n",
			hotfix);
		wdriver->filter_callback = शून्य;
	पूर्ण

	/* add in the length object we will use पूर्णांकernally with ioctl */
	priv->req_buf_size += माप(u64);
	ret = set_required_buffer_size(wdev, priv->req_buf_size);
	अगर (ret)
		वापस ret;

	count = get_order(priv->req_buf_size);
	priv->buf = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, count);
	अगर (!priv->buf)
		वापस -ENOMEM;

	/* ID is used by dell-smbios to set priority of drivers */
	wdev->dev.id = 1;
	ret = dell_smbios_रेजिस्टर_device(&wdev->dev, &dell_smbios_wmi_call);
	अगर (ret)
		जाओ fail_रेजिस्टर;

	priv->wdev = wdev;
	dev_set_drvdata(&wdev->dev, priv);
	mutex_lock(&list_mutex);
	list_add_tail(&priv->list, &wmi_list);
	mutex_unlock(&list_mutex);

	वापस 0;

fail_रेजिस्टर:
	मुक्त_pages((अचिन्हित दीर्घ)priv->buf, count);
	वापस ret;
पूर्ण

अटल व्योम dell_smbios_wmi_हटाओ(काष्ठा wmi_device *wdev)
अणु
	काष्ठा wmi_smbios_priv *priv = dev_get_drvdata(&wdev->dev);
	पूर्णांक count;

	mutex_lock(&call_mutex);
	mutex_lock(&list_mutex);
	list_del(&priv->list);
	mutex_unlock(&list_mutex);
	dell_smbios_unरेजिस्टर_device(&wdev->dev);
	count = get_order(priv->req_buf_size);
	मुक्त_pages((अचिन्हित दीर्घ)priv->buf, count);
	mutex_unlock(&call_mutex);
पूर्ण

अटल स्थिर काष्ठा wmi_device_id dell_smbios_wmi_id_table[] = अणु
	अणु .guid_string = DELL_WMI_SMBIOS_GUID पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम parse_b1_table(स्थिर काष्ठा dmi_header *dm)
अणु
	काष्ठा misc_bios_flags_काष्ठाure *flags =
	container_of(dm, काष्ठा misc_bios_flags_काष्ठाure, header);

	/* 4 bytes header, 8 bytes flags */
	अगर (dm->length < 12)
		वापस;
	अगर (dm->handle != 0xb100)
		वापस;
	अगर ((flags->flags0 & FLAG_HAS_ACPI_WMI))
		wmi_supported = 1;
पूर्ण

अटल व्योम find_b1(स्थिर काष्ठा dmi_header *dm, व्योम *dummy)
अणु
	चयन (dm->type) अणु
	हाल 0xb1: /* misc bios flags */
		parse_b1_table(dm);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा wmi_driver dell_smbios_wmi_driver = अणु
	.driver = अणु
		.name = "dell-smbios",
	पूर्ण,
	.probe = dell_smbios_wmi_probe,
	.हटाओ = dell_smbios_wmi_हटाओ,
	.id_table = dell_smbios_wmi_id_table,
	.filter_callback = dell_smbios_wmi_filter,
पूर्ण;

पूर्णांक init_dell_smbios_wmi(व्योम)
अणु
	dmi_walk(find_b1, शून्य);

	अगर (!wmi_supported)
		वापस -ENODEV;

	वापस wmi_driver_रेजिस्टर(&dell_smbios_wmi_driver);
पूर्ण

व्योम निकास_dell_smbios_wmi(व्योम)
अणु
	अगर (wmi_supported)
		wmi_driver_unरेजिस्टर(&dell_smbios_wmi_driver);
पूर्ण

MODULE_DEVICE_TABLE(wmi, dell_smbios_wmi_id_table);
