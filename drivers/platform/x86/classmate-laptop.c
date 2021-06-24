<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2009  Thadeu Lima de Souza Cascarकरो <cascarकरो@holoscopio.com>
 */


#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/acpi.h>
#समावेश <linux/backlight.h>
#समावेश <linux/input.h>
#समावेश <linux/rfसमाप्त.h>

MODULE_LICENSE("GPL");

काष्ठा cmpc_accel अणु
	पूर्णांक sensitivity;
	पूर्णांक g_select;
	पूर्णांक inputdev_state;
पूर्ण;

#घोषणा CMPC_ACCEL_DEV_STATE_CLOSED	0
#घोषणा CMPC_ACCEL_DEV_STATE_OPEN	1

#घोषणा CMPC_ACCEL_SENSITIVITY_DEFAULT		5
#घोषणा CMPC_ACCEL_G_SELECT_DEFAULT		0

#घोषणा CMPC_ACCEL_HID		"ACCE0000"
#घोषणा CMPC_ACCEL_HID_V4	"ACCE0001"
#घोषणा CMPC_TABLET_HID		"TBLT0000"
#घोषणा CMPC_IPML_HID	"IPML200"
#घोषणा CMPC_KEYS_HID		"FNBT0000"

/*
 * Generic input device code.
 */

प्रकार व्योम (*input_device_init)(काष्ठा input_dev *dev);

अटल पूर्णांक cmpc_add_acpi_notअगरy_device(काष्ठा acpi_device *acpi, अक्षर *name,
				       input_device_init idev_init)
अणु
	काष्ठा input_dev *inputdev;
	पूर्णांक error;

	inputdev = input_allocate_device();
	अगर (!inputdev)
		वापस -ENOMEM;
	inputdev->name = name;
	inputdev->dev.parent = &acpi->dev;
	idev_init(inputdev);
	error = input_रेजिस्टर_device(inputdev);
	अगर (error) अणु
		input_मुक्त_device(inputdev);
		वापस error;
	पूर्ण
	dev_set_drvdata(&acpi->dev, inputdev);
	वापस 0;
पूर्ण

अटल पूर्णांक cmpc_हटाओ_acpi_notअगरy_device(काष्ठा acpi_device *acpi)
अणु
	काष्ठा input_dev *inputdev = dev_get_drvdata(&acpi->dev);
	input_unरेजिस्टर_device(inputdev);
	वापस 0;
पूर्ण

/*
 * Accelerometer code क्रम Classmate V4
 */
अटल acpi_status cmpc_start_accel_v4(acpi_handle handle)
अणु
	जोड़ acpi_object param[4];
	काष्ठा acpi_object_list input;
	acpi_status status;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x3;
	param[1].type = ACPI_TYPE_INTEGER;
	param[1].पूर्णांकeger.value = 0;
	param[2].type = ACPI_TYPE_INTEGER;
	param[2].पूर्णांकeger.value = 0;
	param[3].type = ACPI_TYPE_INTEGER;
	param[3].पूर्णांकeger.value = 0;
	input.count = 4;
	input.poपूर्णांकer = param;
	status = acpi_evaluate_object(handle, "ACMD", &input, शून्य);
	वापस status;
पूर्ण

अटल acpi_status cmpc_stop_accel_v4(acpi_handle handle)
अणु
	जोड़ acpi_object param[4];
	काष्ठा acpi_object_list input;
	acpi_status status;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x4;
	param[1].type = ACPI_TYPE_INTEGER;
	param[1].पूर्णांकeger.value = 0;
	param[2].type = ACPI_TYPE_INTEGER;
	param[2].पूर्णांकeger.value = 0;
	param[3].type = ACPI_TYPE_INTEGER;
	param[3].पूर्णांकeger.value = 0;
	input.count = 4;
	input.poपूर्णांकer = param;
	status = acpi_evaluate_object(handle, "ACMD", &input, शून्य);
	वापस status;
पूर्ण

अटल acpi_status cmpc_accel_set_sensitivity_v4(acpi_handle handle, पूर्णांक val)
अणु
	जोड़ acpi_object param[4];
	काष्ठा acpi_object_list input;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x02;
	param[1].type = ACPI_TYPE_INTEGER;
	param[1].पूर्णांकeger.value = val;
	param[2].type = ACPI_TYPE_INTEGER;
	param[2].पूर्णांकeger.value = 0;
	param[3].type = ACPI_TYPE_INTEGER;
	param[3].पूर्णांकeger.value = 0;
	input.count = 4;
	input.poपूर्णांकer = param;
	वापस acpi_evaluate_object(handle, "ACMD", &input, शून्य);
पूर्ण

अटल acpi_status cmpc_accel_set_g_select_v4(acpi_handle handle, पूर्णांक val)
अणु
	जोड़ acpi_object param[4];
	काष्ठा acpi_object_list input;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x05;
	param[1].type = ACPI_TYPE_INTEGER;
	param[1].पूर्णांकeger.value = val;
	param[2].type = ACPI_TYPE_INTEGER;
	param[2].पूर्णांकeger.value = 0;
	param[3].type = ACPI_TYPE_INTEGER;
	param[3].पूर्णांकeger.value = 0;
	input.count = 4;
	input.poपूर्णांकer = param;
	वापस acpi_evaluate_object(handle, "ACMD", &input, शून्य);
पूर्ण

अटल acpi_status cmpc_get_accel_v4(acpi_handle handle,
				     पूर्णांक16_t *x,
				     पूर्णांक16_t *y,
				     पूर्णांक16_t *z)
अणु
	जोड़ acpi_object param[4];
	काष्ठा acpi_object_list input;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	पूर्णांक16_t *locs;
	acpi_status status;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x01;
	param[1].type = ACPI_TYPE_INTEGER;
	param[1].पूर्णांकeger.value = 0;
	param[2].type = ACPI_TYPE_INTEGER;
	param[2].पूर्णांकeger.value = 0;
	param[3].type = ACPI_TYPE_INTEGER;
	param[3].पूर्णांकeger.value = 0;
	input.count = 4;
	input.poपूर्णांकer = param;
	status = acpi_evaluate_object(handle, "ACMD", &input, &output);
	अगर (ACPI_SUCCESS(status)) अणु
		जोड़ acpi_object *obj;
		obj = output.poपूर्णांकer;
		locs = (पूर्णांक16_t *) obj->buffer.poपूर्णांकer;
		*x = locs[0];
		*y = locs[1];
		*z = locs[2];
		kमुक्त(output.poपूर्णांकer);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम cmpc_accel_handler_v4(काष्ठा acpi_device *dev, u32 event)
अणु
	अगर (event == 0x81) अणु
		पूर्णांक16_t x, y, z;
		acpi_status status;

		status = cmpc_get_accel_v4(dev->handle, &x, &y, &z);
		अगर (ACPI_SUCCESS(status)) अणु
			काष्ठा input_dev *inputdev = dev_get_drvdata(&dev->dev);

			input_report_असल(inputdev, ABS_X, x);
			input_report_असल(inputdev, ABS_Y, y);
			input_report_असल(inputdev, ABS_Z, z);
			input_sync(inputdev);
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार cmpc_accel_sensitivity_show_v4(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi;
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_drvdata(&acpi->dev);
	accel = dev_get_drvdata(&inputdev->dev);

	वापस प्र_लिखो(buf, "%d\n", accel->sensitivity);
पूर्ण

अटल sमाप_प्रकार cmpc_accel_sensitivity_store_v4(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi;
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;
	अचिन्हित दीर्घ sensitivity;
	पूर्णांक r;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_drvdata(&acpi->dev);
	accel = dev_get_drvdata(&inputdev->dev);

	r = kम_से_अदीर्घ(buf, 0, &sensitivity);
	अगर (r)
		वापस r;

	/* sensitivity must be between 1 and 127 */
	अगर (sensitivity < 1 || sensitivity > 127)
		वापस -EINVAL;

	accel->sensitivity = sensitivity;
	cmpc_accel_set_sensitivity_v4(acpi->handle, sensitivity);

	वापस strnlen(buf, count);
पूर्ण

अटल काष्ठा device_attribute cmpc_accel_sensitivity_attr_v4 = अणु
	.attr = अणु .name = "sensitivity", .mode = 0660 पूर्ण,
	.show = cmpc_accel_sensitivity_show_v4,
	.store = cmpc_accel_sensitivity_store_v4
पूर्ण;

अटल sमाप_प्रकार cmpc_accel_g_select_show_v4(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi;
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_drvdata(&acpi->dev);
	accel = dev_get_drvdata(&inputdev->dev);

	वापस प्र_लिखो(buf, "%d\n", accel->g_select);
पूर्ण

अटल sमाप_प्रकार cmpc_accel_g_select_store_v4(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi;
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;
	अचिन्हित दीर्घ g_select;
	पूर्णांक r;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_drvdata(&acpi->dev);
	accel = dev_get_drvdata(&inputdev->dev);

	r = kम_से_अदीर्घ(buf, 0, &g_select);
	अगर (r)
		वापस r;

	/* 0 means 1.5g, 1 means 6g, everything अन्यथा is wrong */
	अगर (g_select != 0 && g_select != 1)
		वापस -EINVAL;

	accel->g_select = g_select;
	cmpc_accel_set_g_select_v4(acpi->handle, g_select);

	वापस strnlen(buf, count);
पूर्ण

अटल काष्ठा device_attribute cmpc_accel_g_select_attr_v4 = अणु
	.attr = अणु .name = "g_select", .mode = 0660 पूर्ण,
	.show = cmpc_accel_g_select_show_v4,
	.store = cmpc_accel_g_select_store_v4
पूर्ण;

अटल पूर्णांक cmpc_accel_खोलो_v4(काष्ठा input_dev *input)
अणु
	काष्ठा acpi_device *acpi;
	काष्ठा cmpc_accel *accel;

	acpi = to_acpi_device(input->dev.parent);
	accel = dev_get_drvdata(&input->dev);

	cmpc_accel_set_sensitivity_v4(acpi->handle, accel->sensitivity);
	cmpc_accel_set_g_select_v4(acpi->handle, accel->g_select);

	अगर (ACPI_SUCCESS(cmpc_start_accel_v4(acpi->handle))) अणु
		accel->inputdev_state = CMPC_ACCEL_DEV_STATE_OPEN;
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल व्योम cmpc_accel_बंद_v4(काष्ठा input_dev *input)
अणु
	काष्ठा acpi_device *acpi;
	काष्ठा cmpc_accel *accel;

	acpi = to_acpi_device(input->dev.parent);
	accel = dev_get_drvdata(&input->dev);

	cmpc_stop_accel_v4(acpi->handle);
	accel->inputdev_state = CMPC_ACCEL_DEV_STATE_CLOSED;
पूर्ण

अटल व्योम cmpc_accel_idev_init_v4(काष्ठा input_dev *inputdev)
अणु
	set_bit(EV_ABS, inputdev->evbit);
	input_set_असल_params(inputdev, ABS_X, -255, 255, 16, 0);
	input_set_असल_params(inputdev, ABS_Y, -255, 255, 16, 0);
	input_set_असल_params(inputdev, ABS_Z, -255, 255, 16, 0);
	inputdev->खोलो = cmpc_accel_खोलो_v4;
	inputdev->बंद = cmpc_accel_बंद_v4;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cmpc_accel_suspend_v4(काष्ठा device *dev)
अणु
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;

	inputdev = dev_get_drvdata(dev);
	accel = dev_get_drvdata(&inputdev->dev);

	अगर (accel->inputdev_state == CMPC_ACCEL_DEV_STATE_OPEN)
		वापस cmpc_stop_accel_v4(to_acpi_device(dev)->handle);

	वापस 0;
पूर्ण

अटल पूर्णांक cmpc_accel_resume_v4(काष्ठा device *dev)
अणु
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;

	inputdev = dev_get_drvdata(dev);
	accel = dev_get_drvdata(&inputdev->dev);

	अगर (accel->inputdev_state == CMPC_ACCEL_DEV_STATE_OPEN) अणु
		cmpc_accel_set_sensitivity_v4(to_acpi_device(dev)->handle,
					      accel->sensitivity);
		cmpc_accel_set_g_select_v4(to_acpi_device(dev)->handle,
					   accel->g_select);

		अगर (ACPI_FAILURE(cmpc_start_accel_v4(to_acpi_device(dev)->handle)))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cmpc_accel_add_v4(काष्ठा acpi_device *acpi)
अणु
	पूर्णांक error;
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;

	accel = kदो_स्मृति(माप(*accel), GFP_KERNEL);
	अगर (!accel)
		वापस -ENOMEM;

	accel->inputdev_state = CMPC_ACCEL_DEV_STATE_CLOSED;

	accel->sensitivity = CMPC_ACCEL_SENSITIVITY_DEFAULT;
	cmpc_accel_set_sensitivity_v4(acpi->handle, accel->sensitivity);

	error = device_create_file(&acpi->dev, &cmpc_accel_sensitivity_attr_v4);
	अगर (error)
		जाओ failed_sensitivity;

	accel->g_select = CMPC_ACCEL_G_SELECT_DEFAULT;
	cmpc_accel_set_g_select_v4(acpi->handle, accel->g_select);

	error = device_create_file(&acpi->dev, &cmpc_accel_g_select_attr_v4);
	अगर (error)
		जाओ failed_g_select;

	error = cmpc_add_acpi_notअगरy_device(acpi, "cmpc_accel_v4",
					    cmpc_accel_idev_init_v4);
	अगर (error)
		जाओ failed_input;

	inputdev = dev_get_drvdata(&acpi->dev);
	dev_set_drvdata(&inputdev->dev, accel);

	वापस 0;

failed_input:
	device_हटाओ_file(&acpi->dev, &cmpc_accel_g_select_attr_v4);
failed_g_select:
	device_हटाओ_file(&acpi->dev, &cmpc_accel_sensitivity_attr_v4);
failed_sensitivity:
	kमुक्त(accel);
	वापस error;
पूर्ण

अटल पूर्णांक cmpc_accel_हटाओ_v4(काष्ठा acpi_device *acpi)
अणु
	device_हटाओ_file(&acpi->dev, &cmpc_accel_sensitivity_attr_v4);
	device_हटाओ_file(&acpi->dev, &cmpc_accel_g_select_attr_v4);
	वापस cmpc_हटाओ_acpi_notअगरy_device(acpi);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cmpc_accel_pm, cmpc_accel_suspend_v4,
			 cmpc_accel_resume_v4);

अटल स्थिर काष्ठा acpi_device_id cmpc_accel_device_ids_v4[] = अणु
	अणुCMPC_ACCEL_HID_V4, 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

अटल काष्ठा acpi_driver cmpc_accel_acpi_driver_v4 = अणु
	.owner = THIS_MODULE,
	.name = "cmpc_accel_v4",
	.class = "cmpc_accel_v4",
	.ids = cmpc_accel_device_ids_v4,
	.ops = अणु
		.add = cmpc_accel_add_v4,
		.हटाओ = cmpc_accel_हटाओ_v4,
		.notअगरy = cmpc_accel_handler_v4,
	पूर्ण,
	.drv.pm = &cmpc_accel_pm,
पूर्ण;


/*
 * Accelerometer code क्रम Classmate versions prior to V4
 */
अटल acpi_status cmpc_start_accel(acpi_handle handle)
अणु
	जोड़ acpi_object param[2];
	काष्ठा acpi_object_list input;
	acpi_status status;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x3;
	param[1].type = ACPI_TYPE_INTEGER;
	input.count = 2;
	input.poपूर्णांकer = param;
	status = acpi_evaluate_object(handle, "ACMD", &input, शून्य);
	वापस status;
पूर्ण

अटल acpi_status cmpc_stop_accel(acpi_handle handle)
अणु
	जोड़ acpi_object param[2];
	काष्ठा acpi_object_list input;
	acpi_status status;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x4;
	param[1].type = ACPI_TYPE_INTEGER;
	input.count = 2;
	input.poपूर्णांकer = param;
	status = acpi_evaluate_object(handle, "ACMD", &input, शून्य);
	वापस status;
पूर्ण

अटल acpi_status cmpc_accel_set_sensitivity(acpi_handle handle, पूर्णांक val)
अणु
	जोड़ acpi_object param[2];
	काष्ठा acpi_object_list input;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x02;
	param[1].type = ACPI_TYPE_INTEGER;
	param[1].पूर्णांकeger.value = val;
	input.count = 2;
	input.poपूर्णांकer = param;
	वापस acpi_evaluate_object(handle, "ACMD", &input, शून्य);
पूर्ण

अटल acpi_status cmpc_get_accel(acpi_handle handle,
				  अचिन्हित अक्षर *x,
				  अचिन्हित अक्षर *y,
				  अचिन्हित अक्षर *z)
अणु
	जोड़ acpi_object param[2];
	काष्ठा acpi_object_list input;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	अचिन्हित अक्षर *locs;
	acpi_status status;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x01;
	param[1].type = ACPI_TYPE_INTEGER;
	input.count = 2;
	input.poपूर्णांकer = param;
	status = acpi_evaluate_object(handle, "ACMD", &input, &output);
	अगर (ACPI_SUCCESS(status)) अणु
		जोड़ acpi_object *obj;
		obj = output.poपूर्णांकer;
		locs = obj->buffer.poपूर्णांकer;
		*x = locs[0];
		*y = locs[1];
		*z = locs[2];
		kमुक्त(output.poपूर्णांकer);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम cmpc_accel_handler(काष्ठा acpi_device *dev, u32 event)
अणु
	अगर (event == 0x81) अणु
		अचिन्हित अक्षर x, y, z;
		acpi_status status;

		status = cmpc_get_accel(dev->handle, &x, &y, &z);
		अगर (ACPI_SUCCESS(status)) अणु
			काष्ठा input_dev *inputdev = dev_get_drvdata(&dev->dev);

			input_report_असल(inputdev, ABS_X, x);
			input_report_असल(inputdev, ABS_Y, y);
			input_report_असल(inputdev, ABS_Z, z);
			input_sync(inputdev);
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार cmpc_accel_sensitivity_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi;
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_drvdata(&acpi->dev);
	accel = dev_get_drvdata(&inputdev->dev);

	वापस प्र_लिखो(buf, "%d\n", accel->sensitivity);
पूर्ण

अटल sमाप_प्रकार cmpc_accel_sensitivity_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi;
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;
	अचिन्हित दीर्घ sensitivity;
	पूर्णांक r;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_drvdata(&acpi->dev);
	accel = dev_get_drvdata(&inputdev->dev);

	r = kम_से_अदीर्घ(buf, 0, &sensitivity);
	अगर (r)
		वापस r;

	accel->sensitivity = sensitivity;
	cmpc_accel_set_sensitivity(acpi->handle, sensitivity);

	वापस strnlen(buf, count);
पूर्ण

अटल काष्ठा device_attribute cmpc_accel_sensitivity_attr = अणु
	.attr = अणु .name = "sensitivity", .mode = 0660 पूर्ण,
	.show = cmpc_accel_sensitivity_show,
	.store = cmpc_accel_sensitivity_store
पूर्ण;

अटल पूर्णांक cmpc_accel_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा acpi_device *acpi;

	acpi = to_acpi_device(input->dev.parent);
	अगर (ACPI_SUCCESS(cmpc_start_accel(acpi->handle)))
		वापस 0;
	वापस -EIO;
पूर्ण

अटल व्योम cmpc_accel_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा acpi_device *acpi;

	acpi = to_acpi_device(input->dev.parent);
	cmpc_stop_accel(acpi->handle);
पूर्ण

अटल व्योम cmpc_accel_idev_init(काष्ठा input_dev *inputdev)
अणु
	set_bit(EV_ABS, inputdev->evbit);
	input_set_असल_params(inputdev, ABS_X, 0, 255, 8, 0);
	input_set_असल_params(inputdev, ABS_Y, 0, 255, 8, 0);
	input_set_असल_params(inputdev, ABS_Z, 0, 255, 8, 0);
	inputdev->खोलो = cmpc_accel_खोलो;
	inputdev->बंद = cmpc_accel_बंद;
पूर्ण

अटल पूर्णांक cmpc_accel_add(काष्ठा acpi_device *acpi)
अणु
	पूर्णांक error;
	काष्ठा input_dev *inputdev;
	काष्ठा cmpc_accel *accel;

	accel = kदो_स्मृति(माप(*accel), GFP_KERNEL);
	अगर (!accel)
		वापस -ENOMEM;

	accel->sensitivity = CMPC_ACCEL_SENSITIVITY_DEFAULT;
	cmpc_accel_set_sensitivity(acpi->handle, accel->sensitivity);

	error = device_create_file(&acpi->dev, &cmpc_accel_sensitivity_attr);
	अगर (error)
		जाओ failed_file;

	error = cmpc_add_acpi_notअगरy_device(acpi, "cmpc_accel",
					    cmpc_accel_idev_init);
	अगर (error)
		जाओ failed_input;

	inputdev = dev_get_drvdata(&acpi->dev);
	dev_set_drvdata(&inputdev->dev, accel);

	वापस 0;

failed_input:
	device_हटाओ_file(&acpi->dev, &cmpc_accel_sensitivity_attr);
failed_file:
	kमुक्त(accel);
	वापस error;
पूर्ण

अटल पूर्णांक cmpc_accel_हटाओ(काष्ठा acpi_device *acpi)
अणु
	device_हटाओ_file(&acpi->dev, &cmpc_accel_sensitivity_attr);
	वापस cmpc_हटाओ_acpi_notअगरy_device(acpi);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id cmpc_accel_device_ids[] = अणु
	अणुCMPC_ACCEL_HID, 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

अटल काष्ठा acpi_driver cmpc_accel_acpi_driver = अणु
	.owner = THIS_MODULE,
	.name = "cmpc_accel",
	.class = "cmpc_accel",
	.ids = cmpc_accel_device_ids,
	.ops = अणु
		.add = cmpc_accel_add,
		.हटाओ = cmpc_accel_हटाओ,
		.notअगरy = cmpc_accel_handler,
	पूर्ण
पूर्ण;


/*
 * Tablet mode code.
 */
अटल acpi_status cmpc_get_tablet(acpi_handle handle,
				   अचिन्हित दीर्घ दीर्घ *value)
अणु
	जोड़ acpi_object param;
	काष्ठा acpi_object_list input;
	अचिन्हित दीर्घ दीर्घ output;
	acpi_status status;

	param.type = ACPI_TYPE_INTEGER;
	param.पूर्णांकeger.value = 0x01;
	input.count = 1;
	input.poपूर्णांकer = &param;
	status = acpi_evaluate_पूर्णांकeger(handle, "TCMD", &input, &output);
	अगर (ACPI_SUCCESS(status))
		*value = output;
	वापस status;
पूर्ण

अटल व्योम cmpc_tablet_handler(काष्ठा acpi_device *dev, u32 event)
अणु
	अचिन्हित दीर्घ दीर्घ val = 0;
	काष्ठा input_dev *inputdev = dev_get_drvdata(&dev->dev);

	अगर (event == 0x81) अणु
		अगर (ACPI_SUCCESS(cmpc_get_tablet(dev->handle, &val))) अणु
			input_report_चयन(inputdev, SW_TABLET_MODE, !val);
			input_sync(inputdev);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cmpc_tablet_idev_init(काष्ठा input_dev *inputdev)
अणु
	अचिन्हित दीर्घ दीर्घ val = 0;
	काष्ठा acpi_device *acpi;

	set_bit(EV_SW, inputdev->evbit);
	set_bit(SW_TABLET_MODE, inputdev->swbit);

	acpi = to_acpi_device(inputdev->dev.parent);
	अगर (ACPI_SUCCESS(cmpc_get_tablet(acpi->handle, &val))) अणु
		input_report_चयन(inputdev, SW_TABLET_MODE, !val);
		input_sync(inputdev);
	पूर्ण
पूर्ण

अटल पूर्णांक cmpc_tablet_add(काष्ठा acpi_device *acpi)
अणु
	वापस cmpc_add_acpi_notअगरy_device(acpi, "cmpc_tablet",
					   cmpc_tablet_idev_init);
पूर्ण

अटल पूर्णांक cmpc_tablet_हटाओ(काष्ठा acpi_device *acpi)
अणु
	वापस cmpc_हटाओ_acpi_notअगरy_device(acpi);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cmpc_tablet_resume(काष्ठा device *dev)
अणु
	काष्ठा input_dev *inputdev = dev_get_drvdata(dev);

	अचिन्हित दीर्घ दीर्घ val = 0;
	अगर (ACPI_SUCCESS(cmpc_get_tablet(to_acpi_device(dev)->handle, &val))) अणु
		input_report_चयन(inputdev, SW_TABLET_MODE, !val);
		input_sync(inputdev);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cmpc_tablet_pm, शून्य, cmpc_tablet_resume);

अटल स्थिर काष्ठा acpi_device_id cmpc_tablet_device_ids[] = अणु
	अणुCMPC_TABLET_HID, 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

अटल काष्ठा acpi_driver cmpc_tablet_acpi_driver = अणु
	.owner = THIS_MODULE,
	.name = "cmpc_tablet",
	.class = "cmpc_tablet",
	.ids = cmpc_tablet_device_ids,
	.ops = अणु
		.add = cmpc_tablet_add,
		.हटाओ = cmpc_tablet_हटाओ,
		.notअगरy = cmpc_tablet_handler,
	पूर्ण,
	.drv.pm = &cmpc_tablet_pm,
पूर्ण;


/*
 * Backlight code.
 */

अटल acpi_status cmpc_get_brightness(acpi_handle handle,
				       अचिन्हित दीर्घ दीर्घ *value)
अणु
	जोड़ acpi_object param;
	काष्ठा acpi_object_list input;
	अचिन्हित दीर्घ दीर्घ output;
	acpi_status status;

	param.type = ACPI_TYPE_INTEGER;
	param.पूर्णांकeger.value = 0xC0;
	input.count = 1;
	input.poपूर्णांकer = &param;
	status = acpi_evaluate_पूर्णांकeger(handle, "GRDI", &input, &output);
	अगर (ACPI_SUCCESS(status))
		*value = output;
	वापस status;
पूर्ण

अटल acpi_status cmpc_set_brightness(acpi_handle handle,
				       अचिन्हित दीर्घ दीर्घ value)
अणु
	जोड़ acpi_object param[2];
	काष्ठा acpi_object_list input;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ output;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0xC0;
	param[1].type = ACPI_TYPE_INTEGER;
	param[1].पूर्णांकeger.value = value;
	input.count = 2;
	input.poपूर्णांकer = param;
	status = acpi_evaluate_पूर्णांकeger(handle, "GWRI", &input, &output);
	वापस status;
पूर्ण

अटल पूर्णांक cmpc_bl_get_brightness(काष्ठा backlight_device *bd)
अणु
	acpi_status status;
	acpi_handle handle;
	अचिन्हित दीर्घ दीर्घ brightness;

	handle = bl_get_data(bd);
	status = cmpc_get_brightness(handle, &brightness);
	अगर (ACPI_SUCCESS(status))
		वापस brightness;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक cmpc_bl_update_status(काष्ठा backlight_device *bd)
अणु
	acpi_status status;
	acpi_handle handle;

	handle = bl_get_data(bd);
	status = cmpc_set_brightness(handle, bd->props.brightness);
	अगर (ACPI_SUCCESS(status))
		वापस 0;
	अन्यथा
		वापस -1;
पूर्ण

अटल स्थिर काष्ठा backlight_ops cmpc_bl_ops = अणु
	.get_brightness = cmpc_bl_get_brightness,
	.update_status = cmpc_bl_update_status
पूर्ण;

/*
 * RFKILL code.
 */

अटल acpi_status cmpc_get_rfसमाप्त_wlan(acpi_handle handle,
					अचिन्हित दीर्घ दीर्घ *value)
अणु
	जोड़ acpi_object param;
	काष्ठा acpi_object_list input;
	अचिन्हित दीर्घ दीर्घ output;
	acpi_status status;

	param.type = ACPI_TYPE_INTEGER;
	param.पूर्णांकeger.value = 0xC1;
	input.count = 1;
	input.poपूर्णांकer = &param;
	status = acpi_evaluate_पूर्णांकeger(handle, "GRDI", &input, &output);
	अगर (ACPI_SUCCESS(status))
		*value = output;
	वापस status;
पूर्ण

अटल acpi_status cmpc_set_rfसमाप्त_wlan(acpi_handle handle,
					अचिन्हित दीर्घ दीर्घ value)
अणु
	जोड़ acpi_object param[2];
	काष्ठा acpi_object_list input;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ output;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0xC1;
	param[1].type = ACPI_TYPE_INTEGER;
	param[1].पूर्णांकeger.value = value;
	input.count = 2;
	input.poपूर्णांकer = param;
	status = acpi_evaluate_पूर्णांकeger(handle, "GWRI", &input, &output);
	वापस status;
पूर्ण

अटल व्योम cmpc_rfसमाप्त_query(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data)
अणु
	acpi_status status;
	acpi_handle handle;
	अचिन्हित दीर्घ दीर्घ state;
	bool blocked;

	handle = data;
	status = cmpc_get_rfसमाप्त_wlan(handle, &state);
	अगर (ACPI_SUCCESS(status)) अणु
		blocked = state & 1 ? false : true;
		rfसमाप्त_set_sw_state(rfसमाप्त, blocked);
	पूर्ण
पूर्ण

अटल पूर्णांक cmpc_rfसमाप्त_block(व्योम *data, bool blocked)
अणु
	acpi_status status;
	acpi_handle handle;
	अचिन्हित दीर्घ दीर्घ state;
	bool is_blocked;

	handle = data;
	status = cmpc_get_rfसमाप्त_wlan(handle, &state);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;
	/* Check अगर we really need to call cmpc_set_rfसमाप्त_wlan */
	is_blocked = state & 1 ? false : true;
	अगर (is_blocked != blocked) अणु
		state = blocked ? 0 : 1;
		status = cmpc_set_rfसमाप्त_wlan(handle, state);
		अगर (ACPI_FAILURE(status))
			वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops cmpc_rfसमाप्त_ops = अणु
	.query = cmpc_rfसमाप्त_query,
	.set_block = cmpc_rfसमाप्त_block,
पूर्ण;

/*
 * Common backlight and rfसमाप्त code.
 */

काष्ठा ipml200_dev अणु
	काष्ठा backlight_device *bd;
	काष्ठा rfसमाप्त *rf;
पूर्ण;

अटल पूर्णांक cmpc_ipml_add(काष्ठा acpi_device *acpi)
अणु
	पूर्णांक retval;
	काष्ठा ipml200_dev *ipml;
	काष्ठा backlight_properties props;

	ipml = kदो_स्मृति(माप(*ipml), GFP_KERNEL);
	अगर (ipml == शून्य)
		वापस -ENOMEM;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = 7;
	ipml->bd = backlight_device_रेजिस्टर("cmpc_bl", &acpi->dev,
					     acpi->handle, &cmpc_bl_ops,
					     &props);
	अगर (IS_ERR(ipml->bd)) अणु
		retval = PTR_ERR(ipml->bd);
		जाओ out_bd;
	पूर्ण

	ipml->rf = rfसमाप्त_alloc("cmpc_rfkill", &acpi->dev, RFKILL_TYPE_WLAN,
				&cmpc_rfसमाप्त_ops, acpi->handle);
	/*
	 * If RFKILL is disabled, rfसमाप्त_alloc will वापस ERR_PTR(-ENODEV).
	 * This is OK, however, since all other uses of the device will not
	 * dereference it.
	 */
	अगर (ipml->rf) अणु
		retval = rfसमाप्त_रेजिस्टर(ipml->rf);
		अगर (retval) अणु
			rfसमाप्त_destroy(ipml->rf);
			ipml->rf = शून्य;
		पूर्ण
	पूर्ण

	dev_set_drvdata(&acpi->dev, ipml);
	वापस 0;

out_bd:
	kमुक्त(ipml);
	वापस retval;
पूर्ण

अटल पूर्णांक cmpc_ipml_हटाओ(काष्ठा acpi_device *acpi)
अणु
	काष्ठा ipml200_dev *ipml;

	ipml = dev_get_drvdata(&acpi->dev);

	backlight_device_unरेजिस्टर(ipml->bd);

	अगर (ipml->rf) अणु
		rfसमाप्त_unरेजिस्टर(ipml->rf);
		rfसमाप्त_destroy(ipml->rf);
	पूर्ण

	kमुक्त(ipml);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id cmpc_ipml_device_ids[] = अणु
	अणुCMPC_IPML_HID, 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

अटल काष्ठा acpi_driver cmpc_ipml_acpi_driver = अणु
	.owner = THIS_MODULE,
	.name = "cmpc",
	.class = "cmpc",
	.ids = cmpc_ipml_device_ids,
	.ops = अणु
		.add = cmpc_ipml_add,
		.हटाओ = cmpc_ipml_हटाओ
	पूर्ण
पूर्ण;


/*
 * Extra keys code.
 */
अटल पूर्णांक cmpc_keys_codes[] = अणु
	KEY_UNKNOWN,
	KEY_WLAN,
	KEY_SWITCHVIDEOMODE,
	KEY_BRIGHTNESSDOWN,
	KEY_BRIGHTNESSUP,
	KEY_VENDOR,
	KEY_UNKNOWN,
	KEY_CAMERA,
	KEY_BACK,
	KEY_FORWARD,
	KEY_UNKNOWN,
	KEY_WLAN, /* NL3: 0x8b (press), 0x9b (release) */
	KEY_MAX
पूर्ण;

अटल व्योम cmpc_keys_handler(काष्ठा acpi_device *dev, u32 event)
अणु
	काष्ठा input_dev *inputdev;
	पूर्णांक code = KEY_MAX;

	अगर ((event & 0x0F) < ARRAY_SIZE(cmpc_keys_codes))
		code = cmpc_keys_codes[event & 0x0F];
	inputdev = dev_get_drvdata(&dev->dev);
	input_report_key(inputdev, code, !(event & 0x10));
	input_sync(inputdev);
पूर्ण

अटल व्योम cmpc_keys_idev_init(काष्ठा input_dev *inputdev)
अणु
	पूर्णांक i;

	set_bit(EV_KEY, inputdev->evbit);
	क्रम (i = 0; cmpc_keys_codes[i] != KEY_MAX; i++)
		set_bit(cmpc_keys_codes[i], inputdev->keybit);
पूर्ण

अटल पूर्णांक cmpc_keys_add(काष्ठा acpi_device *acpi)
अणु
	वापस cmpc_add_acpi_notअगरy_device(acpi, "cmpc_keys",
					   cmpc_keys_idev_init);
पूर्ण

अटल पूर्णांक cmpc_keys_हटाओ(काष्ठा acpi_device *acpi)
अणु
	वापस cmpc_हटाओ_acpi_notअगरy_device(acpi);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id cmpc_keys_device_ids[] = अणु
	अणुCMPC_KEYS_HID, 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

अटल काष्ठा acpi_driver cmpc_keys_acpi_driver = अणु
	.owner = THIS_MODULE,
	.name = "cmpc_keys",
	.class = "cmpc_keys",
	.ids = cmpc_keys_device_ids,
	.ops = अणु
		.add = cmpc_keys_add,
		.हटाओ = cmpc_keys_हटाओ,
		.notअगरy = cmpc_keys_handler,
	पूर्ण
पूर्ण;


/*
 * General init/निकास code.
 */

अटल पूर्णांक cmpc_init(व्योम)
अणु
	पूर्णांक r;

	r = acpi_bus_रेजिस्टर_driver(&cmpc_keys_acpi_driver);
	अगर (r)
		जाओ failed_keys;

	r = acpi_bus_रेजिस्टर_driver(&cmpc_ipml_acpi_driver);
	अगर (r)
		जाओ failed_bl;

	r = acpi_bus_रेजिस्टर_driver(&cmpc_tablet_acpi_driver);
	अगर (r)
		जाओ failed_tablet;

	r = acpi_bus_रेजिस्टर_driver(&cmpc_accel_acpi_driver);
	अगर (r)
		जाओ failed_accel;

	r = acpi_bus_रेजिस्टर_driver(&cmpc_accel_acpi_driver_v4);
	अगर (r)
		जाओ failed_accel_v4;

	वापस r;

failed_accel_v4:
	acpi_bus_unरेजिस्टर_driver(&cmpc_accel_acpi_driver);

failed_accel:
	acpi_bus_unरेजिस्टर_driver(&cmpc_tablet_acpi_driver);

failed_tablet:
	acpi_bus_unरेजिस्टर_driver(&cmpc_ipml_acpi_driver);

failed_bl:
	acpi_bus_unरेजिस्टर_driver(&cmpc_keys_acpi_driver);

failed_keys:
	वापस r;
पूर्ण

अटल व्योम cmpc_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&cmpc_accel_acpi_driver_v4);
	acpi_bus_unरेजिस्टर_driver(&cmpc_accel_acpi_driver);
	acpi_bus_unरेजिस्टर_driver(&cmpc_tablet_acpi_driver);
	acpi_bus_unरेजिस्टर_driver(&cmpc_ipml_acpi_driver);
	acpi_bus_unरेजिस्टर_driver(&cmpc_keys_acpi_driver);
पूर्ण

module_init(cmpc_init);
module_निकास(cmpc_निकास);

अटल स्थिर काष्ठा acpi_device_id cmpc_device_ids[] = अणु
	अणुCMPC_ACCEL_HID, 0पूर्ण,
	अणुCMPC_ACCEL_HID_V4, 0पूर्ण,
	अणुCMPC_TABLET_HID, 0पूर्ण,
	अणुCMPC_IPML_HID, 0पूर्ण,
	अणुCMPC_KEYS_HID, 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, cmpc_device_ids);
