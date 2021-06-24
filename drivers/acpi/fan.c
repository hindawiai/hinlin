<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi_fan.c - ACPI Fan Driver ($Revision: 29 $)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/thermal.h>
#समावेश <linux/acpi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sort.h>

MODULE_AUTHOR("Paul Diefenbaugh");
MODULE_DESCRIPTION("ACPI Fan Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक acpi_fan_probe(काष्ठा platक्रमm_device *pdev);
अटल पूर्णांक acpi_fan_हटाओ(काष्ठा platक्रमm_device *pdev);

अटल स्थिर काष्ठा acpi_device_id fan_device_ids[] = अणु
	अणु"PNP0C0B", 0पूर्ण,
	अणु"INT3404", 0पूर्ण,
	अणु"INTC1044", 0पूर्ण,
	अणु"INTC1048", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, fan_device_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_fan_suspend(काष्ठा device *dev);
अटल पूर्णांक acpi_fan_resume(काष्ठा device *dev);
अटल स्थिर काष्ठा dev_pm_ops acpi_fan_pm = अणु
	.resume = acpi_fan_resume,
	.मुक्तze = acpi_fan_suspend,
	.thaw = acpi_fan_resume,
	.restore = acpi_fan_resume,
पूर्ण;
#घोषणा FAN_PM_OPS_PTR (&acpi_fan_pm)
#अन्यथा
#घोषणा FAN_PM_OPS_PTR शून्य
#पूर्ण_अगर

#घोषणा ACPI_FPS_NAME_LEN	20

काष्ठा acpi_fan_fps अणु
	u64 control;
	u64 trip_poपूर्णांक;
	u64 speed;
	u64 noise_level;
	u64 घातer;
	अक्षर name[ACPI_FPS_NAME_LEN];
	काष्ठा device_attribute dev_attr;
पूर्ण;

काष्ठा acpi_fan_fअगर अणु
	u64 revision;
	u64 fine_grain_ctrl;
	u64 step_size;
	u64 low_speed_notअगरication;
पूर्ण;

काष्ठा acpi_fan अणु
	bool acpi4;
	काष्ठा acpi_fan_fअगर fअगर;
	काष्ठा acpi_fan_fps *fps;
	पूर्णांक fps_count;
	काष्ठा thermal_cooling_device *cdev;
पूर्ण;

अटल काष्ठा platक्रमm_driver acpi_fan_driver = अणु
	.probe = acpi_fan_probe,
	.हटाओ = acpi_fan_हटाओ,
	.driver = अणु
		.name = "acpi-fan",
		.acpi_match_table = fan_device_ids,
		.pm = FAN_PM_OPS_PTR,
	पूर्ण,
पूर्ण;

/* thermal cooling device callbacks */
अटल पूर्णांक fan_get_max_state(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ
			     *state)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	काष्ठा acpi_fan *fan = acpi_driver_data(device);

	अगर (fan->acpi4)
		*state = fan->fps_count - 1;
	अन्यथा
		*state = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक fan_get_state_acpi4(काष्ठा acpi_device *device, अचिन्हित दीर्घ *state)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_fan *fan = acpi_driver_data(device);
	जोड़ acpi_object *obj;
	acpi_status status;
	पूर्णांक control, i;

	status = acpi_evaluate_object(device->handle, "_FST", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&device->dev, "Get fan state failed\n");
		वापस status;
	पूर्ण

	obj = buffer.poपूर्णांकer;
	अगर (!obj || obj->type != ACPI_TYPE_PACKAGE ||
	    obj->package.count != 3 ||
	    obj->package.elements[1].type != ACPI_TYPE_INTEGER) अणु
		dev_err(&device->dev, "Invalid _FST data\n");
		status = -EINVAL;
		जाओ err;
	पूर्ण

	control = obj->package.elements[1].पूर्णांकeger.value;
	क्रम (i = 0; i < fan->fps_count; i++) अणु
		/*
		 * When Fine Grain Control is set, वापस the state
		 * corresponding to maximum fan->fps[i].control
		 * value compared to the current speed. Here the
		 * fan->fps[] is sorted array with increasing speed.
		 */
		अगर (fan->fअगर.fine_grain_ctrl && control < fan->fps[i].control) अणु
			i = (i > 0) ? i - 1 : 0;
			अवरोध;
		पूर्ण अन्यथा अगर (control == fan->fps[i].control) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == fan->fps_count) अणु
		dev_dbg(&device->dev, "Invalid control value returned\n");
		status = -EINVAL;
		जाओ err;
	पूर्ण

	*state = i;

err:
	kमुक्त(obj);
	वापस status;
पूर्ण

अटल पूर्णांक fan_get_state(काष्ठा acpi_device *device, अचिन्हित दीर्घ *state)
अणु
	पूर्णांक result;
	पूर्णांक acpi_state = ACPI_STATE_D0;

	result = acpi_device_update_घातer(device, &acpi_state);
	अगर (result)
		वापस result;

	*state = acpi_state == ACPI_STATE_D3_COLD
			|| acpi_state == ACPI_STATE_D3_HOT ?
		0 : (acpi_state == ACPI_STATE_D0 ? 1 : -1);
	वापस 0;
पूर्ण

अटल पूर्णांक fan_get_cur_state(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ
			     *state)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	काष्ठा acpi_fan *fan = acpi_driver_data(device);

	अगर (fan->acpi4)
		वापस fan_get_state_acpi4(device, state);
	अन्यथा
		वापस fan_get_state(device, state);
पूर्ण

अटल पूर्णांक fan_set_state(काष्ठा acpi_device *device, अचिन्हित दीर्घ state)
अणु
	अगर (state != 0 && state != 1)
		वापस -EINVAL;

	वापस acpi_device_set_घातer(device,
				     state ? ACPI_STATE_D0 : ACPI_STATE_D3_COLD);
पूर्ण

अटल पूर्णांक fan_set_state_acpi4(काष्ठा acpi_device *device, अचिन्हित दीर्घ state)
अणु
	काष्ठा acpi_fan *fan = acpi_driver_data(device);
	acpi_status status;

	अगर (state >= fan->fps_count)
		वापस -EINVAL;

	status = acpi_execute_simple_method(device->handle, "_FSL",
					    fan->fps[state].control);
	अगर (ACPI_FAILURE(status)) अणु
		dev_dbg(&device->dev, "Failed to set state by _FSL\n");
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fan_set_cur_state(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ state)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	काष्ठा acpi_fan *fan = acpi_driver_data(device);

	अगर (fan->acpi4)
		वापस fan_set_state_acpi4(device, state);
	अन्यथा
		वापस fan_set_state(device, state);
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops fan_cooling_ops = अणु
	.get_max_state = fan_get_max_state,
	.get_cur_state = fan_get_cur_state,
	.set_cur_state = fan_set_cur_state,
पूर्ण;

/* --------------------------------------------------------------------------
 *                               Driver Interface
 * --------------------------------------------------------------------------
*/

अटल bool acpi_fan_is_acpi4(काष्ठा acpi_device *device)
अणु
	वापस acpi_has_method(device->handle, "_FIF") &&
	       acpi_has_method(device->handle, "_FPS") &&
	       acpi_has_method(device->handle, "_FSL") &&
	       acpi_has_method(device->handle, "_FST");
पूर्ण

अटल पूर्णांक acpi_fan_get_fअगर(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_fan *fan = acpi_driver_data(device);
	काष्ठा acpi_buffer क्रमmat = अणु माप("NNNN"), "NNNN" पूर्ण;
	काष्ठा acpi_buffer fअगर = अणु माप(fan->fअगर), &fan->fअगर पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	status = acpi_evaluate_object(device->handle, "_FIF", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = buffer.poपूर्णांकer;
	अगर (!obj || obj->type != ACPI_TYPE_PACKAGE) अणु
		dev_err(&device->dev, "Invalid _FIF data\n");
		status = -EINVAL;
		जाओ err;
	पूर्ण

	status = acpi_extract_package(obj, &क्रमmat, &fअगर);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&device->dev, "Invalid _FIF element\n");
		status = -EINVAL;
	पूर्ण

err:
	kमुक्त(obj);
	वापस status;
पूर्ण

अटल पूर्णांक acpi_fan_speed_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा acpi_fan_fps *fps1 = a;
	स्थिर काष्ठा acpi_fan_fps *fps2 = b;
	वापस fps1->speed - fps2->speed;
पूर्ण

अटल sमाप_प्रकार show_state(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_fan_fps *fps = container_of(attr, काष्ठा acpi_fan_fps, dev_attr);
	पूर्णांक count;

	अगर (fps->control == 0xFFFFFFFF || fps->control > 100)
		count = scnम_लिखो(buf, PAGE_SIZE, "not-defined:");
	अन्यथा
		count = scnम_लिखो(buf, PAGE_SIZE, "%lld:", fps->control);

	अगर (fps->trip_poपूर्णांक == 0xFFFFFFFF || fps->trip_poपूर्णांक > 9)
		count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "not-defined:");
	अन्यथा
		count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "%lld:", fps->trip_poपूर्णांक);

	अगर (fps->speed == 0xFFFFFFFF)
		count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "not-defined:");
	अन्यथा
		count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "%lld:", fps->speed);

	अगर (fps->noise_level == 0xFFFFFFFF)
		count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "not-defined:");
	अन्यथा
		count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "%lld:", fps->noise_level * 100);

	अगर (fps->घातer == 0xFFFFFFFF)
		count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "not-defined\n");
	अन्यथा
		count += scnम_लिखो(&buf[count], PAGE_SIZE - count, "%lld\n", fps->घातer);

	वापस count;
पूर्ण

अटल पूर्णांक acpi_fan_get_fps(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_fan *fan = acpi_driver_data(device);
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;
	पूर्णांक i;

	status = acpi_evaluate_object(device->handle, "_FPS", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = buffer.poपूर्णांकer;
	अगर (!obj || obj->type != ACPI_TYPE_PACKAGE || obj->package.count < 2) अणु
		dev_err(&device->dev, "Invalid _FPS data\n");
		status = -EINVAL;
		जाओ err;
	पूर्ण

	fan->fps_count = obj->package.count - 1; /* minus revision field */
	fan->fps = devm_kसुस्मृति(&device->dev,
				fan->fps_count, माप(काष्ठा acpi_fan_fps),
				GFP_KERNEL);
	अगर (!fan->fps) अणु
		dev_err(&device->dev, "Not enough memory\n");
		status = -ENOMEM;
		जाओ err;
	पूर्ण
	क्रम (i = 0; i < fan->fps_count; i++) अणु
		काष्ठा acpi_buffer क्रमmat = अणु माप("NNNNN"), "NNNNN" पूर्ण;
		काष्ठा acpi_buffer fps = अणु दुरत्व(काष्ठा acpi_fan_fps, name),
						&fan->fps[i] पूर्ण;
		status = acpi_extract_package(&obj->package.elements[i + 1],
					      &क्रमmat, &fps);
		अगर (ACPI_FAILURE(status)) अणु
			dev_err(&device->dev, "Invalid _FPS element\n");
			जाओ err;
		पूर्ण
	पूर्ण

	/* sort the state array according to fan speed in increase order */
	sort(fan->fps, fan->fps_count, माप(*fan->fps),
	     acpi_fan_speed_cmp, शून्य);

	क्रम (i = 0; i < fan->fps_count; ++i) अणु
		काष्ठा acpi_fan_fps *fps = &fan->fps[i];

		snम_लिखो(fps->name, ACPI_FPS_NAME_LEN, "state%d", i);
		sysfs_attr_init(&fps->dev_attr.attr);
		fps->dev_attr.show = show_state;
		fps->dev_attr.store = शून्य;
		fps->dev_attr.attr.name = fps->name;
		fps->dev_attr.attr.mode = 0444;
		status = sysfs_create_file(&device->dev.kobj, &fps->dev_attr.attr);
		अगर (status) अणु
			पूर्णांक j;

			क्रम (j = 0; j < i; ++j)
				sysfs_हटाओ_file(&device->dev.kobj, &fan->fps[j].dev_attr.attr);
			अवरोध;
		पूर्ण
	पूर्ण

err:
	kमुक्त(obj);
	वापस status;
पूर्ण

अटल पूर्णांक acpi_fan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक result = 0;
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा acpi_fan *fan;
	काष्ठा acpi_device *device = ACPI_COMPANION(&pdev->dev);
	अक्षर *name;

	fan = devm_kzalloc(&pdev->dev, माप(*fan), GFP_KERNEL);
	अगर (!fan) अणु
		dev_err(&device->dev, "No memory for fan\n");
		वापस -ENOMEM;
	पूर्ण
	device->driver_data = fan;
	platक्रमm_set_drvdata(pdev, fan);

	अगर (acpi_fan_is_acpi4(device)) अणु
		result = acpi_fan_get_fअगर(device);
		अगर (result)
			वापस result;

		result = acpi_fan_get_fps(device);
		अगर (result)
			वापस result;

		fan->acpi4 = true;
	पूर्ण अन्यथा अणु
		result = acpi_device_update_घातer(device, शून्य);
		अगर (result) अणु
			dev_err(&device->dev, "Failed to set initial power state\n");
			जाओ err_end;
		पूर्ण
	पूर्ण

	अगर (!म_भेदन(pdev->name, "PNP0C0B", म_माप("PNP0C0B")))
		name = "Fan";
	अन्यथा
		name = acpi_device_bid(device);

	cdev = thermal_cooling_device_रेजिस्टर(name, device,
						&fan_cooling_ops);
	अगर (IS_ERR(cdev)) अणु
		result = PTR_ERR(cdev);
		जाओ err_end;
	पूर्ण

	dev_dbg(&pdev->dev, "registered as cooling_device%d\n", cdev->id);

	fan->cdev = cdev;
	result = sysfs_create_link(&pdev->dev.kobj,
				   &cdev->device.kobj,
				   "thermal_cooling");
	अगर (result)
		dev_err(&pdev->dev, "Failed to create sysfs link 'thermal_cooling'\n");

	result = sysfs_create_link(&cdev->device.kobj,
				   &pdev->dev.kobj,
				   "device");
	अगर (result) अणु
		dev_err(&pdev->dev, "Failed to create sysfs link 'device'\n");
		जाओ err_end;
	पूर्ण

	वापस 0;

err_end:
	अगर (fan->acpi4) अणु
		पूर्णांक i;

		क्रम (i = 0; i < fan->fps_count; ++i)
			sysfs_हटाओ_file(&device->dev.kobj, &fan->fps[i].dev_attr.attr);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक acpi_fan_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_fan *fan = platक्रमm_get_drvdata(pdev);

	अगर (fan->acpi4) अणु
		काष्ठा acpi_device *device = ACPI_COMPANION(&pdev->dev);
		पूर्णांक i;

		क्रम (i = 0; i < fan->fps_count; ++i)
			sysfs_हटाओ_file(&device->dev.kobj, &fan->fps[i].dev_attr.attr);
	पूर्ण
	sysfs_हटाओ_link(&pdev->dev.kobj, "thermal_cooling");
	sysfs_हटाओ_link(&fan->cdev->device.kobj, "device");
	thermal_cooling_device_unरेजिस्टर(fan->cdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_fan_suspend(काष्ठा device *dev)
अणु
	काष्ठा acpi_fan *fan = dev_get_drvdata(dev);
	अगर (fan->acpi4)
		वापस 0;

	acpi_device_set_घातer(ACPI_COMPANION(dev), ACPI_STATE_D0);

	वापस AE_OK;
पूर्ण

अटल पूर्णांक acpi_fan_resume(काष्ठा device *dev)
अणु
	पूर्णांक result;
	काष्ठा acpi_fan *fan = dev_get_drvdata(dev);

	अगर (fan->acpi4)
		वापस 0;

	result = acpi_device_update_घातer(ACPI_COMPANION(dev), शून्य);
	अगर (result)
		dev_err(dev, "Error updating fan power state\n");

	वापस result;
पूर्ण
#पूर्ण_अगर

module_platक्रमm_driver(acpi_fan_driver);
