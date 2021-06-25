<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dptf_pch_fivr:  DPTF PCH FIVR Participant driver
 * Copyright (c) 2020, Intel Corporation.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * Presentation of attributes which are defined क्रम INT1045
 * They are:
 * freq_mhz_low_घड़ी : Set PCH FIVR चयनing freq क्रम
 *			FIVR घड़ी 19.2MHz and 24MHz
 * freq_mhz_high_घड़ी : Set PCH FIVR चयनing freq क्रम
 *			FIVR घड़ी 38.4MHz
 */
#घोषणा PCH_FIVR_SHOW(name, method) \
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,\
			   काष्ठा device_attribute *attr,\
			   अक्षर *buf)\
अणु\
	काष्ठा acpi_device *acpi_dev = dev_get_drvdata(dev);\
	अचिन्हित दीर्घ दीर्घ val;\
	acpi_status status;\
\
	status = acpi_evaluate_पूर्णांकeger(acpi_dev->handle, #method,\
				       शून्य, &val);\
	अगर (ACPI_SUCCESS(status))\
		वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)val);\
	अन्यथा\
		वापस -EINVAL;\
पूर्ण

#घोषणा PCH_FIVR_STORE(name, method) \
अटल sमाप_प्रकार name##_store(काष्ठा device *dev,\
			    काष्ठा device_attribute *attr,\
			    स्थिर अक्षर *buf, माप_प्रकार count)\
अणु\
	काष्ठा acpi_device *acpi_dev = dev_get_drvdata(dev);\
	acpi_status status;\
	u32 val;\
\
	अगर (kstrtouपूर्णांक(buf, 0, &val) < 0)\
		वापस -EINVAL;\
\
	status = acpi_execute_simple_method(acpi_dev->handle, #method, val);\
	अगर (ACPI_SUCCESS(status))\
		वापस count;\
\
	वापस -EINVAL;\
पूर्ण

PCH_FIVR_SHOW(freq_mhz_low_घड़ी, GFC0)
PCH_FIVR_SHOW(freq_mhz_high_घड़ी, GFC1)
PCH_FIVR_STORE(freq_mhz_low_घड़ी, RFC0)
PCH_FIVR_STORE(freq_mhz_high_घड़ी, RFC1)

अटल DEVICE_ATTR_RW(freq_mhz_low_घड़ी);
अटल DEVICE_ATTR_RW(freq_mhz_high_घड़ी);

अटल काष्ठा attribute *fivr_attrs[] = अणु
	&dev_attr_freq_mhz_low_घड़ी.attr,
	&dev_attr_freq_mhz_high_घड़ी.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pch_fivr_attribute_group = अणु
	.attrs = fivr_attrs,
	.name = "pch_fivr_switch_frequency"
पूर्ण;

अटल पूर्णांक pch_fivr_add(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_device *acpi_dev;
	अचिन्हित दीर्घ दीर्घ ptype;
	acpi_status status;
	पूर्णांक result;

	acpi_dev = ACPI_COMPANION(&(pdev->dev));
	अगर (!acpi_dev)
		वापस -ENODEV;

	status = acpi_evaluate_पूर्णांकeger(acpi_dev->handle, "PTYP", शून्य, &ptype);
	अगर (ACPI_FAILURE(status) || ptype != 0x05)
		वापस -ENODEV;

	result = sysfs_create_group(&pdev->dev.kobj,
				    &pch_fivr_attribute_group);
	अगर (result)
		वापस result;

	platक्रमm_set_drvdata(pdev, acpi_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pch_fivr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	sysfs_हटाओ_group(&pdev->dev.kobj, &pch_fivr_attribute_group);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id pch_fivr_device_ids[] = अणु
	अणु"INTC1045", 0पूर्ण,
	अणु"INTC1049", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pch_fivr_device_ids);

अटल काष्ठा platक्रमm_driver pch_fivr_driver = अणु
	.probe = pch_fivr_add,
	.हटाओ = pch_fivr_हटाओ,
	.driver = अणु
		.name = "dptf_pch_fivr",
		.acpi_match_table = pch_fivr_device_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pch_fivr_driver);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ACPI DPTF PCH FIVR driver");
