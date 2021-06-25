<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dptf_घातer:  DPTF platक्रमm घातer driver
 * Copyright (c) 2016, Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * Presentation of attributes which are defined क्रम INT3407 and INT3532.
 * They are:
 * PMAX : Maximum platक्रमm घातe
 * PSRC : Platक्रमm घातer source
 * ARTG : Adapter rating
 * CTYP : Charger type
 * PBSS : Battery steady घातer
 * PROP : Rest of worst हाल platक्रमm Power
 * PBSS : Power Battery Steady State
 * PBSS : Power Battery Steady State
 * RBHF : High Frequency Impedance
 * VBNL : Instantaneous No-Load Voltage
 * CMPP : Current Disअक्षरge Capability
 */
#घोषणा DPTF_POWER_SHOW(name, object) \
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,\
			   काष्ठा device_attribute *attr,\
			   अक्षर *buf)\
अणु\
	काष्ठा acpi_device *acpi_dev = dev_get_drvdata(dev);\
	अचिन्हित दीर्घ दीर्घ val;\
	acpi_status status;\
\
	status = acpi_evaluate_पूर्णांकeger(acpi_dev->handle, #object,\
				       शून्य, &val);\
	अगर (ACPI_SUCCESS(status))\
		वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)val);\
	अन्यथा \
		वापस -EINVAL;\
पूर्ण

DPTF_POWER_SHOW(max_platक्रमm_घातer_mw, PMAX)
DPTF_POWER_SHOW(platक्रमm_घातer_source, PSRC)
DPTF_POWER_SHOW(adapter_rating_mw, ARTG)
DPTF_POWER_SHOW(battery_steady_घातer_mw, PBSS)
DPTF_POWER_SHOW(अक्षरger_type, CTYP)
DPTF_POWER_SHOW(rest_of_platक्रमm_घातer_mw, PROP)
DPTF_POWER_SHOW(max_steady_state_घातer_mw, PBSS)
DPTF_POWER_SHOW(high_freq_impedance_mohm, RBHF)
DPTF_POWER_SHOW(no_load_voltage_mv, VBNL)
DPTF_POWER_SHOW(current_disअक्षरge_capbility_ma, CMPP);

अटल DEVICE_ATTR_RO(max_platक्रमm_घातer_mw);
अटल DEVICE_ATTR_RO(platक्रमm_घातer_source);
अटल DEVICE_ATTR_RO(adapter_rating_mw);
अटल DEVICE_ATTR_RO(battery_steady_घातer_mw);
अटल DEVICE_ATTR_RO(अक्षरger_type);
अटल DEVICE_ATTR_RO(rest_of_platक्रमm_घातer_mw);
अटल DEVICE_ATTR_RO(max_steady_state_घातer_mw);
अटल DEVICE_ATTR_RO(high_freq_impedance_mohm);
अटल DEVICE_ATTR_RO(no_load_voltage_mv);
अटल DEVICE_ATTR_RO(current_disअक्षरge_capbility_ma);

अटल sमाप_प्रकार prochot_confirm_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi_dev = dev_get_drvdata(dev);
	acpi_status status;
	पूर्णांक seq_no;

	अगर (kstrtouपूर्णांक(buf, 0, &seq_no) < 0)
		वापस -EINVAL;

	status = acpi_execute_simple_method(acpi_dev->handle, "PBOK", seq_no);
	अगर (ACPI_SUCCESS(status))
		वापस count;

	वापस -EINVAL;
पूर्ण

अटल DEVICE_ATTR_WO(prochot_confirm);

अटल काष्ठा attribute *dptf_घातer_attrs[] = अणु
	&dev_attr_max_platक्रमm_घातer_mw.attr,
	&dev_attr_platक्रमm_घातer_source.attr,
	&dev_attr_adapter_rating_mw.attr,
	&dev_attr_battery_steady_घातer_mw.attr,
	&dev_attr_अक्षरger_type.attr,
	&dev_attr_rest_of_platक्रमm_घातer_mw.attr,
	&dev_attr_prochot_confirm.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dptf_घातer_attribute_group = अणु
	.attrs = dptf_घातer_attrs,
	.name = "dptf_power"
पूर्ण;

अटल काष्ठा attribute *dptf_battery_attrs[] = अणु
	&dev_attr_max_platक्रमm_घातer_mw.attr,
	&dev_attr_max_steady_state_घातer_mw.attr,
	&dev_attr_high_freq_impedance_mohm.attr,
	&dev_attr_no_load_voltage_mv.attr,
	&dev_attr_current_disअक्षरge_capbility_ma.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dptf_battery_attribute_group = अणु
	.attrs = dptf_battery_attrs,
	.name = "dptf_battery"
पूर्ण;

#घोषणा MAX_POWER_CHANGED		0x80
#घोषणा POWER_STATE_CHANGED		0x81
#घोषणा STEADY_STATE_POWER_CHANGED	0x83
#घोषणा POWER_PROP_CHANGE_EVENT	0x84
#घोषणा IMPEDANCED_CHNGED		0x85
#घोषणा VOLTAGE_CURRENT_CHANGED	0x86

अटल दीर्घ दीर्घ dptf_participant_type(acpi_handle handle)
अणु
	अचिन्हित दीर्घ दीर्घ ptype;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(handle, "PTYP", शून्य, &ptype);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	वापस ptype;
पूर्ण

अटल व्योम dptf_घातer_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = data;
	अक्षर *attr;

	चयन (event) अणु
	हाल POWER_STATE_CHANGED:
		attr = "platform_power_source";
		अवरोध;
	हाल POWER_PROP_CHANGE_EVENT:
		attr = "rest_of_platform_power_mw";
		अवरोध;
	हाल MAX_POWER_CHANGED:
		attr = "max_platform_power_mw";
		अवरोध;
	हाल STEADY_STATE_POWER_CHANGED:
		attr = "max_steady_state_power_mw";
		अवरोध;
	हाल VOLTAGE_CURRENT_CHANGED:
		attr = "no_load_voltage_mv";
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported event [0x%x]\n", event);
		वापस;
	पूर्ण

	/*
	 * Notअगरy that an attribute is changed, so that user space can पढ़ो
	 * again.
	 */
	अगर (dptf_participant_type(handle) == 0x0CULL)
		sysfs_notअगरy(&pdev->dev.kobj, "dptf_battery", attr);
	अन्यथा
		sysfs_notअगरy(&pdev->dev.kobj, "dptf_power", attr);
पूर्ण

अटल पूर्णांक dptf_घातer_add(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा attribute_group *attr_group;
	काष्ठा acpi_device *acpi_dev;
	अचिन्हित दीर्घ दीर्घ ptype;
	पूर्णांक result;

	acpi_dev = ACPI_COMPANION(&(pdev->dev));
	अगर (!acpi_dev)
		वापस -ENODEV;

	ptype = dptf_participant_type(acpi_dev->handle);
	अगर (ptype == 0x11)
		attr_group = &dptf_घातer_attribute_group;
	अन्यथा अगर (ptype == 0x0C)
		attr_group = &dptf_battery_attribute_group;
	अन्यथा
		वापस -ENODEV;

	result = acpi_install_notअगरy_handler(acpi_dev->handle,
					     ACPI_DEVICE_NOTIFY,
					     dptf_घातer_notअगरy,
					     (व्योम *)pdev);
	अगर (result)
		वापस result;

	result = sysfs_create_group(&pdev->dev.kobj,
				    attr_group);
	अगर (result) अणु
		acpi_हटाओ_notअगरy_handler(acpi_dev->handle,
					   ACPI_DEVICE_NOTIFY,
					   dptf_घातer_notअगरy);
		वापस result;
	पूर्ण

	platक्रमm_set_drvdata(pdev, acpi_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dptf_घातer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_device *acpi_dev = platक्रमm_get_drvdata(pdev);

	acpi_हटाओ_notअगरy_handler(acpi_dev->handle,
				   ACPI_DEVICE_NOTIFY,
				   dptf_घातer_notअगरy);

	अगर (dptf_participant_type(acpi_dev->handle) == 0x0CULL)
		sysfs_हटाओ_group(&pdev->dev.kobj, &dptf_battery_attribute_group);
	अन्यथा
		sysfs_हटाओ_group(&pdev->dev.kobj, &dptf_घातer_attribute_group);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id पूर्णांक3407_device_ids[] = अणु
	अणु"INT3407", 0पूर्ण,
	अणु"INT3532", 0पूर्ण,
	अणु"INTC1047", 0पूर्ण,
	अणु"INTC1050", 0पूर्ण,
	अणु"INTC1060", 0पूर्ण,
	अणु"INTC1061", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांक3407_device_ids);

अटल काष्ठा platक्रमm_driver dptf_घातer_driver = अणु
	.probe = dptf_घातer_add,
	.हटाओ = dptf_घातer_हटाओ,
	.driver = अणु
		.name = "dptf_power",
		.acpi_match_table = पूर्णांक3407_device_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dptf_घातer_driver);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ACPI DPTF platform power driver");
