<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright 2013 Matthew Garrett <mjg59@srcf.ucam.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

MODULE_LICENSE("GPL");

अटल sमाप_प्रकार irst_show_wakeup_events(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi;
	अचिन्हित दीर्घ दीर्घ value;
	acpi_status status;

	acpi = to_acpi_device(dev);

	status = acpi_evaluate_पूर्णांकeger(acpi->handle, "GFFS", शून्य, &value);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%lld\n", value);
पूर्ण

अटल sमाप_प्रकार irst_store_wakeup_events(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi;
	acpi_status status;
	अचिन्हित दीर्घ value;
	पूर्णांक error;

	acpi = to_acpi_device(dev);

	error = kम_से_अदीर्घ(buf, 0, &value);
	अगर (error)
		वापस error;

	status = acpi_execute_simple_method(acpi->handle, "SFFS", value);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute irst_wakeup_attr = अणु
	.attr = अणु .name = "wakeup_events", .mode = 0600 पूर्ण,
	.show = irst_show_wakeup_events,
	.store = irst_store_wakeup_events
पूर्ण;

अटल sमाप_प्रकार irst_show_wakeup_समय(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi;
	अचिन्हित दीर्घ दीर्घ value;
	acpi_status status;

	acpi = to_acpi_device(dev);

	status = acpi_evaluate_पूर्णांकeger(acpi->handle, "GFTV", शून्य, &value);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%lld\n", value);
पूर्ण

अटल sमाप_प्रकार irst_store_wakeup_समय(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi;
	acpi_status status;
	अचिन्हित दीर्घ value;
	पूर्णांक error;

	acpi = to_acpi_device(dev);

	error = kम_से_अदीर्घ(buf, 0, &value);
	अगर (error)
		वापस error;

	status = acpi_execute_simple_method(acpi->handle, "SFTV", value);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute irst_समयout_attr = अणु
	.attr = अणु .name = "wakeup_time", .mode = 0600 पूर्ण,
	.show = irst_show_wakeup_समय,
	.store = irst_store_wakeup_समय
पूर्ण;

अटल पूर्णांक irst_add(काष्ठा acpi_device *acpi)
अणु
	पूर्णांक error;

	error = device_create_file(&acpi->dev, &irst_समयout_attr);
	अगर (unlikely(error))
		वापस error;

	error = device_create_file(&acpi->dev, &irst_wakeup_attr);
	अगर (unlikely(error))
		device_हटाओ_file(&acpi->dev, &irst_समयout_attr);

	वापस error;
पूर्ण

अटल पूर्णांक irst_हटाओ(काष्ठा acpi_device *acpi)
अणु
	device_हटाओ_file(&acpi->dev, &irst_wakeup_attr);
	device_हटाओ_file(&acpi->dev, &irst_समयout_attr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id irst_ids[] = अणु
	अणु"INT3392", 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

अटल काष्ठा acpi_driver irst_driver = अणु
	.owner = THIS_MODULE,
	.name = "intel_rapid_start",
	.class = "intel_rapid_start",
	.ids = irst_ids,
	.ops = अणु
		.add = irst_add,
		.हटाओ = irst_हटाओ,
	पूर्ण,
पूर्ण;

module_acpi_driver(irst_driver);

MODULE_DEVICE_TABLE(acpi, irst_ids);
