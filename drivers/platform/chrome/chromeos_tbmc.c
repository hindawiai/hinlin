<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Driver to detect Tablet Mode क्रम ChromeOS convertible.
//
// Copyright (C) 2017 Google, Inc.
// Author: Gwendal Grignou <gwendal@chromium.org>
//
// On Chromebook using ACPI, this device listens क्रम notअगरication
// from GOOG0006 and issue method TBMC to retrieve the status.
//
// GOOG0006 issues the notअगरication when it receives EC_HOST_EVENT_MODE_CHANGE
// from the EC.
// Method TBMC पढ़ोs EC_ACPI_MEM_DEVICE_ORIENTATION byte from the shared
// memory region.

#समावेश <linux/acpi.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>

#घोषणा DRV_NAME "chromeos_tbmc"
#घोषणा ACPI_DRV_NAME "GOOG0006"

अटल पूर्णांक chromeos_tbmc_query_चयन(काष्ठा acpi_device *adev,
				     काष्ठा input_dev *idev)
अणु
	अचिन्हित दीर्घ दीर्घ state;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(adev->handle, "TBMC", शून्य, &state);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	/* input layer checks अगर event is redundant */
	input_report_चयन(idev, SW_TABLET_MODE, state);
	input_sync(idev);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक chromeos_tbmc_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev = to_acpi_device(dev);

	वापस chromeos_tbmc_query_चयन(adev, adev->driver_data);
पूर्ण

अटल व्योम chromeos_tbmc_notअगरy(काष्ठा acpi_device *adev, u32 event)
अणु
	acpi_pm_wakeup_event(&adev->dev);
	चयन (event) अणु
	हाल 0x80:
		chromeos_tbmc_query_चयन(adev, adev->driver_data);
		अवरोध;
	शेष:
		dev_err(&adev->dev, "Unexpected event: 0x%08X\n", event);
	पूर्ण
पूर्ण

अटल पूर्णांक chromeos_tbmc_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा acpi_device *adev = input_get_drvdata(idev);

	वापस chromeos_tbmc_query_चयन(adev, idev);
पूर्ण

अटल पूर्णांक chromeos_tbmc_add(काष्ठा acpi_device *adev)
अणु
	काष्ठा input_dev *idev;
	काष्ठा device *dev = &adev->dev;
	पूर्णांक ret;

	idev = devm_input_allocate_device(dev);
	अगर (!idev)
		वापस -ENOMEM;

	idev->name = "Tablet Mode Switch";
	idev->phys = acpi_device_hid(adev);

	idev->id.bustype = BUS_HOST;
	idev->id.version = 1;
	idev->id.product = 0;
	idev->खोलो = chromeos_tbmc_खोलो;

	input_set_drvdata(idev, adev);
	adev->driver_data = idev;

	input_set_capability(idev, EV_SW, SW_TABLET_MODE);
	ret = input_रेजिस्टर_device(idev);
	अगर (ret) अणु
		dev_err(dev, "cannot register input device\n");
		वापस ret;
	पूर्ण
	device_init_wakeup(dev, true);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id chromeos_tbmc_acpi_device_ids[] = अणु
	अणु ACPI_DRV_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, chromeos_tbmc_acpi_device_ids);

अटल SIMPLE_DEV_PM_OPS(chromeos_tbmc_pm_ops, शून्य,
		chromeos_tbmc_resume);

अटल काष्ठा acpi_driver chromeos_tbmc_driver = अणु
	.name = DRV_NAME,
	.class = DRV_NAME,
	.ids = chromeos_tbmc_acpi_device_ids,
	.ops = अणु
		.add = chromeos_tbmc_add,
		.notअगरy = chromeos_tbmc_notअगरy,
	पूर्ण,
	.drv.pm = &chromeos_tbmc_pm_ops,
पूर्ण;

module_acpi_driver(chromeos_tbmc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChromeOS ACPI tablet switch driver");
