<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>

#समावेश <loongson.h>
#समावेश <boot_param.h>
#समावेश <loongson_hwmon.h>
#समावेश <loongson_regs.h>

अटल पूर्णांक csr_temp_enable;

/*
 * Loongson-3 series cpu has two sensors inside,
 * each of them from 0 to 255,
 * अगर more than 127, that is dangerous.
 * here only provide sensor1 data, because it always hot than sensor0
 */
पूर्णांक loongson3_cpu_temp(पूर्णांक cpu)
अणु
	u32 reg, prid_rev;

	अगर (csr_temp_enable) अणु
		reg = (csr_पढ़ोl(LOONGSON_CSR_CPUTEMP) & 0xff);
		जाओ out;
	पूर्ण

	reg = LOONGSON_CHIPTEMP(cpu);
	prid_rev = पढ़ो_c0_prid() & PRID_REV_MASK;

	चयन (prid_rev) अणु
	हाल PRID_REV_LOONGSON3A_R1:
		reg = (reg >> 8) & 0xff;
		अवरोध;
	हाल PRID_REV_LOONGSON3B_R1:
	हाल PRID_REV_LOONGSON3B_R2:
	हाल PRID_REV_LOONGSON3A_R2_0:
	हाल PRID_REV_LOONGSON3A_R2_1:
		reg = ((reg >> 8) & 0xff) - 100;
		अवरोध;
	हाल PRID_REV_LOONGSON3A_R3_0:
	हाल PRID_REV_LOONGSON3A_R3_1:
	शेष:
		reg = (reg & 0xffff) * 731 / 0x4000 - 273;
		अवरोध;
	पूर्ण

out:
	वापस (पूर्णांक)reg * 1000;
पूर्ण

अटल पूर्णांक nr_packages;
अटल काष्ठा device *cpu_hwmon_dev;

अटल SENSOR_DEVICE_ATTR(name, 0444, शून्य, शून्य, 0);

अटल काष्ठा attribute *cpu_hwmon_attributes[] = अणु
	&sensor_dev_attr_name.dev_attr.attr,
	शून्य
पूर्ण;

/* Hwmon device attribute group */
अटल काष्ठा attribute_group cpu_hwmon_attribute_group = अणु
	.attrs = cpu_hwmon_attributes,
पूर्ण;

अटल sमाप_प्रकार get_cpu_temp(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf);
अटल sमाप_प्रकार cpu_temp_label(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf);

अटल SENSOR_DEVICE_ATTR(temp1_input, 0444, get_cpu_temp, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp1_label, 0444, cpu_temp_label, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp2_input, 0444, get_cpu_temp, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(temp2_label, 0444, cpu_temp_label, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(temp3_input, 0444, get_cpu_temp, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(temp3_label, 0444, cpu_temp_label, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(temp4_input, 0444, get_cpu_temp, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(temp4_label, 0444, cpu_temp_label, शून्य, 4);

अटल स्थिर काष्ठा attribute *hwmon_cputemp[4][3] = अणु
	अणु
		&sensor_dev_attr_temp1_input.dev_attr.attr,
		&sensor_dev_attr_temp1_label.dev_attr.attr,
		शून्य
	पूर्ण,
	अणु
		&sensor_dev_attr_temp2_input.dev_attr.attr,
		&sensor_dev_attr_temp2_label.dev_attr.attr,
		शून्य
	पूर्ण,
	अणु
		&sensor_dev_attr_temp3_input.dev_attr.attr,
		&sensor_dev_attr_temp3_label.dev_attr.attr,
		शून्य
	पूर्ण,
	अणु
		&sensor_dev_attr_temp4_input.dev_attr.attr,
		&sensor_dev_attr_temp4_label.dev_attr.attr,
		शून्य
	पूर्ण
पूर्ण;

अटल sमाप_प्रकार cpu_temp_label(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक id = (to_sensor_dev_attr(attr))->index - 1;

	वापस प्र_लिखो(buf, "CPU %d Temperature\n", id);
पूर्ण

अटल sमाप_प्रकार get_cpu_temp(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक id = (to_sensor_dev_attr(attr))->index - 1;
	पूर्णांक value = loongson3_cpu_temp(id);

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल पूर्णांक create_sysfs_cputemp_files(काष्ठा kobject *kobj)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < nr_packages; i++)
		ret = sysfs_create_files(kobj, hwmon_cputemp[i]);

	वापस ret;
पूर्ण

अटल व्योम हटाओ_sysfs_cputemp_files(काष्ठा kobject *kobj)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_packages; i++)
		sysfs_हटाओ_files(kobj, hwmon_cputemp[i]);
पूर्ण

#घोषणा CPU_THERMAL_THRESHOLD 90000
अटल काष्ठा delayed_work thermal_work;

अटल व्योम करो_thermal_समयr(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i, value;

	क्रम (i = 0; i < nr_packages; i++) अणु
		value = loongson3_cpu_temp(i);
		अगर (value > CPU_THERMAL_THRESHOLD) अणु
			pr_emerg("Power off due to high temp: %d\n", value);
			orderly_घातeroff(true);
		पूर्ण
	पूर्ण

	schedule_delayed_work(&thermal_work, msecs_to_jअगरfies(5000));
पूर्ण

अटल पूर्णांक __init loongson_hwmon_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("Loongson Hwmon Enter...\n");

	अगर (cpu_has_csr())
		csr_temp_enable = csr_पढ़ोl(LOONGSON_CSR_FEATURES) &
				  LOONGSON_CSRF_TEMP;

	cpu_hwmon_dev = hwmon_device_रेजिस्टर_with_info(शून्य, "cpu_hwmon", शून्य, शून्य, शून्य);
	अगर (IS_ERR(cpu_hwmon_dev)) अणु
		ret = PTR_ERR(cpu_hwmon_dev);
		pr_err("hwmon_device_register fail!\n");
		जाओ fail_hwmon_device_रेजिस्टर;
	पूर्ण

	nr_packages = loongson_sysconf.nr_cpus /
		loongson_sysconf.cores_per_package;

	ret = create_sysfs_cputemp_files(&cpu_hwmon_dev->kobj);
	अगर (ret) अणु
		pr_err("fail to create cpu temperature interface!\n");
		जाओ fail_create_sysfs_cputemp_files;
	पूर्ण

	INIT_DEFERRABLE_WORK(&thermal_work, करो_thermal_समयr);
	schedule_delayed_work(&thermal_work, msecs_to_jअगरfies(20000));

	वापस ret;

fail_create_sysfs_cputemp_files:
	sysfs_हटाओ_group(&cpu_hwmon_dev->kobj,
				&cpu_hwmon_attribute_group);
	hwmon_device_unरेजिस्टर(cpu_hwmon_dev);

fail_hwmon_device_रेजिस्टर:
	वापस ret;
पूर्ण

अटल व्योम __निकास loongson_hwmon_निकास(व्योम)
अणु
	cancel_delayed_work_sync(&thermal_work);
	हटाओ_sysfs_cputemp_files(&cpu_hwmon_dev->kobj);
	sysfs_हटाओ_group(&cpu_hwmon_dev->kobj,
				&cpu_hwmon_attribute_group);
	hwmon_device_unरेजिस्टर(cpu_hwmon_dev);
पूर्ण

module_init(loongson_hwmon_init);
module_निकास(loongson_hwmon_निकास);

MODULE_AUTHOR("Yu Xiang <xiangy@lemote.com>");
MODULE_AUTHOR("Huacai Chen <chenhc@lemote.com>");
MODULE_DESCRIPTION("Loongson CPU Hwmon driver");
MODULE_LICENSE("GPL");
