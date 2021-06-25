<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * via-cputemp.c - Driver क्रम VIA CPU core temperature monitoring
 * Copyright (C) 2009 VIA Technologies, Inc.
 *
 * based on existing coretemp.c, which is
 *
 * Copyright (C) 2007 Ruकरोlf Marek <r.marek@assembler.cz>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpu_device_id.h>

#घोषणा DRVNAME	"via_cputemp"

क्रमागत अणु SHOW_TEMP, SHOW_LABEL, SHOW_NAME पूर्ण;

/*
 * Functions declaration
 */

काष्ठा via_cputemp_data अणु
	काष्ठा device *hwmon_dev;
	स्थिर अक्षर *name;
	u8 vrm;
	u32 id;
	u32 msr_temp;
	u32 msr_vid;
पूर्ण;

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा via_cputemp_data *data = dev_get_drvdata(dev);

	अगर (attr->index == SHOW_NAME)
		ret = प्र_लिखो(buf, "%s\n", data->name);
	अन्यथा	/* show label */
		ret = प्र_लिखो(buf, "Core %d\n", data->id);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा via_cputemp_data *data = dev_get_drvdata(dev);
	u32 eax, edx;
	पूर्णांक err;

	err = rdmsr_safe_on_cpu(data->id, data->msr_temp, &eax, &edx);
	अगर (err)
		वापस -EAGAIN;

	वापस प्र_लिखो(buf, "%lu\n", ((अचिन्हित दीर्घ)eax & 0xffffff) * 1000);
पूर्ण

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा via_cputemp_data *data = dev_get_drvdata(dev);
	u32 eax, edx;
	पूर्णांक err;

	err = rdmsr_safe_on_cpu(data->id, data->msr_vid, &eax, &edx);
	अगर (err)
		वापस -EAGAIN;

	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(~edx & 0x7f, data->vrm));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, SHOW_TEMP);
अटल SENSOR_DEVICE_ATTR_RO(temp1_label, name, SHOW_LABEL);
अटल SENSOR_DEVICE_ATTR_RO(name, name, SHOW_NAME);

अटल काष्ठा attribute *via_cputemp_attributes[] = अणु
	&sensor_dev_attr_name.dev_attr.attr,
	&sensor_dev_attr_temp1_label.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group via_cputemp_group = अणु
	.attrs = via_cputemp_attributes,
पूर्ण;

/* Optional attributes */
अटल DEVICE_ATTR_RO(cpu0_vid);

अटल पूर्णांक via_cputemp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा via_cputemp_data *data;
	काष्ठा cpuinfo_x86 *c = &cpu_data(pdev->id);
	पूर्णांक err;
	u32 eax, edx;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा via_cputemp_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->id = pdev->id;
	data->name = "via_cputemp";

	अगर (c->x86 == 7) अणु
		data->msr_temp = 0x1423;
	पूर्ण अन्यथा अणु
		चयन (c->x86_model) अणु
		हाल 0xA:
			/* C7 A */
		हाल 0xD:
			/* C7 D */
			data->msr_temp = 0x1169;
			data->msr_vid = 0x198;
			अवरोध;
		हाल 0xF:
			/* Nano */
			data->msr_temp = 0x1423;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* test अगर we can access the TEMPERATURE MSR */
	err = rdmsr_safe_on_cpu(data->id, data->msr_temp, &eax, &edx);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Unable to access TEMPERATURE MSR, giving up\n");
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	err = sysfs_create_group(&pdev->dev.kobj, &via_cputemp_group);
	अगर (err)
		वापस err;

	अगर (data->msr_vid)
		data->vrm = vid_which_vrm();

	अगर (data->vrm) अणु
		err = device_create_file(&pdev->dev, &dev_attr_cpu0_vid);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		dev_err(&pdev->dev, "Class registration failed (%d)\n",
			err);
		जाओ निकास_हटाओ;
	पूर्ण

	वापस 0;

निकास_हटाओ:
	अगर (data->vrm)
		device_हटाओ_file(&pdev->dev, &dev_attr_cpu0_vid);
	sysfs_हटाओ_group(&pdev->dev.kobj, &via_cputemp_group);
	वापस err;
पूर्ण

अटल पूर्णांक via_cputemp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा via_cputemp_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	अगर (data->vrm)
		device_हटाओ_file(&pdev->dev, &dev_attr_cpu0_vid);
	sysfs_हटाओ_group(&pdev->dev.kobj, &via_cputemp_group);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver via_cputemp_driver = अणु
	.driver = अणु
		.name = DRVNAME,
	पूर्ण,
	.probe = via_cputemp_probe,
	.हटाओ = via_cputemp_हटाओ,
पूर्ण;

काष्ठा pdev_entry अणु
	काष्ठा list_head list;
	काष्ठा platक्रमm_device *pdev;
	अचिन्हित पूर्णांक cpu;
पूर्ण;

अटल LIST_HEAD(pdev_list);
अटल DEFINE_MUTEX(pdev_list_mutex);

अटल पूर्णांक via_cputemp_online(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक err;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा pdev_entry *pdev_entry;

	pdev = platक्रमm_device_alloc(DRVNAME, cpu);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास;
	पूर्ण

	pdev_entry = kzalloc(माप(काष्ठा pdev_entry), GFP_KERNEL);
	अगर (!pdev_entry) अणु
		err = -ENOMEM;
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_मुक्त;
	पूर्ण

	pdev_entry->pdev = pdev;
	pdev_entry->cpu = cpu;
	mutex_lock(&pdev_list_mutex);
	list_add_tail(&pdev_entry->list, &pdev_list);
	mutex_unlock(&pdev_list_mutex);

	वापस 0;

निकास_device_मुक्त:
	kमुक्त(pdev_entry);
निकास_device_put:
	platक्रमm_device_put(pdev);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक via_cputemp_करोwn_prep(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा pdev_entry *p;

	mutex_lock(&pdev_list_mutex);
	list_क्रम_each_entry(p, &pdev_list, list) अणु
		अगर (p->cpu == cpu) अणु
			platक्रमm_device_unरेजिस्टर(p->pdev);
			list_del(&p->list);
			mutex_unlock(&pdev_list_mutex);
			kमुक्त(p);
			वापस 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&pdev_list_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id __initस्थिर cputemp_ids[] = अणु
	X86_MATCH_VENDOR_FAM_MODEL(CENTAUR, 6, X86_CENTAUR_FAM6_C7_A,	शून्य),
	X86_MATCH_VENDOR_FAM_MODEL(CENTAUR, 6, X86_CENTAUR_FAM6_C7_D,	शून्य),
	X86_MATCH_VENDOR_FAM_MODEL(CENTAUR, 6, X86_CENTAUR_FAM6_न_अंकO,	शून्य),
	X86_MATCH_VENDOR_FAM_MODEL(CENTAUR, 7, X86_MODEL_ANY,		शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, cputemp_ids);

अटल क्रमागत cpuhp_state via_temp_online;

अटल पूर्णांक __init via_cputemp_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!x86_match_cpu(cputemp_ids))
		वापस -ENODEV;

	err = platक्रमm_driver_रेजिस्टर(&via_cputemp_driver);
	अगर (err)
		जाओ निकास;

	err = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "hwmon/via:online",
				via_cputemp_online, via_cputemp_करोwn_prep);
	अगर (err < 0)
		जाओ निकास_driver_unreg;
	via_temp_online = err;

#अगर_अघोषित CONFIG_HOTPLUG_CPU
	अगर (list_empty(&pdev_list)) अणु
		err = -ENODEV;
		जाओ निकास_hp_unreg;
	पूर्ण
#पूर्ण_अगर
	वापस 0;

#अगर_अघोषित CONFIG_HOTPLUG_CPU
निकास_hp_unreg:
	cpuhp_हटाओ_state_nocalls(via_temp_online);
#पूर्ण_अगर
निकास_driver_unreg:
	platक्रमm_driver_unरेजिस्टर(&via_cputemp_driver);
निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास via_cputemp_निकास(व्योम)
अणु
	cpuhp_हटाओ_state(via_temp_online);
	platक्रमm_driver_unरेजिस्टर(&via_cputemp_driver);
पूर्ण

MODULE_AUTHOR("Harald Welte <HaraldWelte@viatech.com>");
MODULE_DESCRIPTION("VIA CPU temperature monitor");
MODULE_LICENSE("GPL");

module_init(via_cputemp_init)
module_निकास(via_cputemp_निकास)
