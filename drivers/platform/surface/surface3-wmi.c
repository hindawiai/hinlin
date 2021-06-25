<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम the LID cover चयन of the Surface 3
 *
 *  Copyright (c) 2016 Red Hat Inc.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/input.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>

MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@redhat.com>");
MODULE_DESCRIPTION("Surface 3 platform driver");
MODULE_LICENSE("GPL");

#घोषणा ACPI_BUTTON_HID_LID		"PNP0C0D"
#घोषणा SPI_CTL_OBJ_NAME		"SPI"
#घोषणा SPI_TS_OBJ_NAME			"NTRG"

#घोषणा SURFACE3_LID_GUID "F7CC25EC-D20B-404C-8903-0ED4359C18AE"

MODULE_ALIAS("wmi:" SURFACE3_LID_GUID);

अटल स्थिर काष्ठा dmi_प्रणाली_id surface3_dmi_table[] = अणु
#अगर defined(CONFIG_X86)
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Surface 3"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

काष्ठा surface3_wmi अणु
	काष्ठा acpi_device *touchscreen_adev;
	काष्ठा acpi_device *pnp0c0d_adev;
	काष्ठा acpi_hotplug_context hp;
	काष्ठा input_dev *input;
पूर्ण;

अटल काष्ठा platक्रमm_device *s3_wmi_pdev;

अटल काष्ठा surface3_wmi s3_wmi;

अटल DEFINE_MUTEX(s3_wmi_lock);

अटल पूर्णांक s3_wmi_query_block(स्थिर अक्षर *guid, पूर्णांक instance, पूर्णांक *ret)
अणु
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj = शून्य;
	acpi_status status;
	पूर्णांक error = 0;

	mutex_lock(&s3_wmi_lock);
	status = wmi_query_block(guid, instance, &output);
	अगर (ACPI_FAILURE(status)) अणु
		error = -EIO;
		जाओ out_मुक्त_unlock;
	पूर्ण

	obj = output.poपूर्णांकer;

	अगर (!obj || obj->type != ACPI_TYPE_INTEGER) अणु
		अगर (obj) अणु
			pr_err("query block returned object type: %d - buffer length:%d\n",
			       obj->type,
			       obj->type == ACPI_TYPE_BUFFER ?
						obj->buffer.length : 0);
		पूर्ण
		error = -EINVAL;
		जाओ out_मुक्त_unlock;
	पूर्ण
	*ret = obj->पूर्णांकeger.value;
 out_मुक्त_unlock:
	kमुक्त(obj);
	mutex_unlock(&s3_wmi_lock);
	वापस error;
पूर्ण

अटल अंतरभूत पूर्णांक s3_wmi_query_lid(पूर्णांक *ret)
अणु
	वापस s3_wmi_query_block(SURFACE3_LID_GUID, 0, ret);
पूर्ण

अटल पूर्णांक s3_wmi_send_lid_state(व्योम)
अणु
	पूर्णांक ret, lid_sw;

	ret = s3_wmi_query_lid(&lid_sw);
	अगर (ret)
		वापस ret;

	input_report_चयन(s3_wmi.input, SW_LID, lid_sw);
	input_sync(s3_wmi.input);

	वापस 0;
पूर्ण

अटल पूर्णांक s3_wmi_hp_notअगरy(काष्ठा acpi_device *adev, u32 value)
अणु
	वापस s3_wmi_send_lid_state();
पूर्ण

अटल acpi_status s3_wmi_attach_spi_device(acpi_handle handle,
					    u32 level,
					    व्योम *data,
					    व्योम **वापस_value)
अणु
	काष्ठा acpi_device *adev, **ts_adev;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	ts_adev = data;

	अगर (म_भेदन(acpi_device_bid(adev), SPI_TS_OBJ_NAME,
	    म_माप(SPI_TS_OBJ_NAME)))
		वापस AE_OK;

	अगर (*ts_adev) अणु
		pr_err("duplicate entry %s\n", SPI_TS_OBJ_NAME);
		वापस AE_OK;
	पूर्ण

	*ts_adev = adev;

	वापस AE_OK;
पूर्ण

अटल पूर्णांक s3_wmi_check_platक्रमm_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा acpi_device *adev, *ts_adev = शून्य;
	acpi_handle handle;
	acpi_status status;

	/* ignore non ACPI devices */
	handle = ACPI_HANDLE(dev);
	अगर (!handle || acpi_bus_get_device(handle, &adev))
		वापस 0;

	/* check क्रम LID ACPI चयन */
	अगर (!म_भेद(ACPI_BUTTON_HID_LID, acpi_device_hid(adev))) अणु
		s3_wmi.pnp0c0d_adev = adev;
		वापस 0;
	पूर्ण

	/* ignore non SPI controllers */
	अगर (म_भेदन(acpi_device_bid(adev), SPI_CTL_OBJ_NAME,
	    म_माप(SPI_CTL_OBJ_NAME)))
		वापस 0;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
				     s3_wmi_attach_spi_device, शून्य,
				     &ts_adev, शून्य);
	अगर (ACPI_FAILURE(status))
		dev_warn(dev, "failed to enumerate SPI slaves\n");

	अगर (!ts_adev)
		वापस 0;

	s3_wmi.touchscreen_adev = ts_adev;

	वापस 0;
पूर्ण

अटल पूर्णांक s3_wmi_create_and_रेजिस्टर_input(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *input;
	पूर्णांक error;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "Lid Switch";
	input->phys = "button/input0";
	input->id.bustype = BUS_HOST;
	input->id.product = 0x0005;

	input_set_capability(input, EV_SW, SW_LID);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		जाओ out_err;

	s3_wmi.input = input;

	वापस 0;
 out_err:
	input_मुक्त_device(s3_wmi.input);
	वापस error;
पूर्ण

अटल पूर्णांक __init s3_wmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक error;

	अगर (!dmi_check_प्रणाली(surface3_dmi_table))
		वापस -ENODEV;

	स_रखो(&s3_wmi, 0, माप(s3_wmi));

	bus_क्रम_each_dev(&platक्रमm_bus_type, शून्य, शून्य,
			 s3_wmi_check_platक्रमm_device);

	अगर (!s3_wmi.touchscreen_adev)
		वापस -ENODEV;

	acpi_bus_trim(s3_wmi.pnp0c0d_adev);

	error = s3_wmi_create_and_रेजिस्टर_input(pdev);
	अगर (error)
		जाओ restore_acpi_lid;

	acpi_initialize_hp_context(s3_wmi.touchscreen_adev, &s3_wmi.hp,
				   s3_wmi_hp_notअगरy, शून्य);

	s3_wmi_send_lid_state();

	वापस 0;

 restore_acpi_lid:
	acpi_bus_scan(s3_wmi.pnp0c0d_adev->handle);
	वापस error;
पूर्ण

अटल पूर्णांक s3_wmi_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	/* हटाओ the hotplug context from the acpi device */
	s3_wmi.touchscreen_adev->hp = शून्य;

	/* reinstall the actual PNPC0C0D LID शेष handle */
	acpi_bus_scan(s3_wmi.pnp0c0d_adev->handle);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused s3_wmi_resume(काष्ठा device *dev)
अणु
	s3_wmi_send_lid_state();
	वापस 0;
पूर्ण
अटल SIMPLE_DEV_PM_OPS(s3_wmi_pm, शून्य, s3_wmi_resume);

अटल काष्ठा platक्रमm_driver s3_wmi_driver = अणु
	.driver = अणु
		.name = "surface3-wmi",
		.pm = &s3_wmi_pm,
	पूर्ण,
	.हटाओ = s3_wmi_हटाओ,
पूर्ण;

अटल पूर्णांक __init s3_wmi_init(व्योम)
अणु
	पूर्णांक error;

	s3_wmi_pdev = platक्रमm_device_alloc("surface3-wmi", -1);
	अगर (!s3_wmi_pdev)
		वापस -ENOMEM;

	error = platक्रमm_device_add(s3_wmi_pdev);
	अगर (error)
		जाओ err_device_put;

	error = platक्रमm_driver_probe(&s3_wmi_driver, s3_wmi_probe);
	अगर (error)
		जाओ err_device_del;

	pr_info("Surface 3 WMI Extras loaded\n");
	वापस 0;

 err_device_del:
	platक्रमm_device_del(s3_wmi_pdev);
 err_device_put:
	platक्रमm_device_put(s3_wmi_pdev);
	वापस error;
पूर्ण

अटल व्योम __निकास s3_wmi_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(s3_wmi_pdev);
	platक्रमm_driver_unरेजिस्टर(&s3_wmi_driver);
पूर्ण

module_init(s3_wmi_init);
module_निकास(s3_wmi_निकास);
