<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * fam15h_घातer.c - AMD Family 15h processor घातer monitoring
 *
 * Copyright (c) 2011-2016 Advanced Micro Devices, Inc.
 * Author: Andreas Herrmann <herrmann.der.user@googlemail.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/समय.स>
#समावेश <linux/sched.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/msr.h>

MODULE_DESCRIPTION("AMD Family 15h CPU processor power monitor");
MODULE_AUTHOR("Andreas Herrmann <herrmann.der.user@googlemail.com>");
MODULE_LICENSE("GPL");

/* D18F3 */
#घोषणा REG_NORTHBRIDGE_CAP		0xe8

/* D18F4 */
#घोषणा REG_PROCESSOR_TDP		0x1b8

/* D18F5 */
#घोषणा REG_TDP_RUNNING_AVERAGE		0xe0
#घोषणा REG_TDP_LIMIT3			0xe8

#घोषणा FAM15H_MIN_NUM_ATTRS		2
#घोषणा FAM15H_NUM_GROUPS		2
#घोषणा MAX_CUS				8

/* set maximum पूर्णांकerval as 1 second */
#घोषणा MAX_INTERVAL			1000

#घोषणा PCI_DEVICE_ID_AMD_15H_M70H_NB_F4 0x15b4

काष्ठा fam15h_घातer_data अणु
	काष्ठा pci_dev *pdev;
	अचिन्हित पूर्णांक tdp_to_watts;
	अचिन्हित पूर्णांक base_tdp;
	अचिन्हित पूर्णांक processor_pwr_watts;
	अचिन्हित पूर्णांक cpu_pwr_sample_ratio;
	स्थिर काष्ठा attribute_group *groups[FAM15H_NUM_GROUPS];
	काष्ठा attribute_group group;
	/* maximum accumulated घातer of a compute unit */
	u64 max_cu_acc_घातer;
	/* accumulated घातer of the compute units */
	u64 cu_acc_घातer[MAX_CUS];
	/* perक्रमmance बारtamp counter */
	u64 cpu_sw_pwr_ptsc[MAX_CUS];
	/* online/offline status of current compute unit */
	पूर्णांक cu_on[MAX_CUS];
	अचिन्हित दीर्घ घातer_period;
पूर्ण;

अटल bool is_carrizo_or_later(व्योम)
अणु
	वापस boot_cpu_data.x86 == 0x15 && boot_cpu_data.x86_model >= 0x60;
पूर्ण

अटल sमाप_प्रकार घातer1_input_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 val, tdp_limit, running_avg_range;
	s32 running_avg_capture;
	u64 curr_pwr_watts;
	काष्ठा fam15h_घातer_data *data = dev_get_drvdata(dev);
	काष्ठा pci_dev *f4 = data->pdev;

	pci_bus_पढ़ो_config_dword(f4->bus, PCI_DEVFN(PCI_SLOT(f4->devfn), 5),
				  REG_TDP_RUNNING_AVERAGE, &val);

	/*
	 * On Carrizo and later platक्रमms, TdpRunAvgAccCap bit field
	 * is extended to 4:31 from 4:25.
	 */
	अगर (is_carrizo_or_later()) अणु
		running_avg_capture = val >> 4;
		running_avg_capture = sign_extend32(running_avg_capture, 27);
	पूर्ण अन्यथा अणु
		running_avg_capture = (val >> 4) & 0x3fffff;
		running_avg_capture = sign_extend32(running_avg_capture, 21);
	पूर्ण

	running_avg_range = (val & 0xf) + 1;

	pci_bus_पढ़ो_config_dword(f4->bus, PCI_DEVFN(PCI_SLOT(f4->devfn), 5),
				  REG_TDP_LIMIT3, &val);

	/*
	 * On Carrizo and later platक्रमms, ApmTdpLimit bit field
	 * is extended to 16:31 from 16:28.
	 */
	अगर (is_carrizo_or_later())
		tdp_limit = val >> 16;
	अन्यथा
		tdp_limit = (val >> 16) & 0x1fff;

	curr_pwr_watts = ((u64)(tdp_limit +
				data->base_tdp)) << running_avg_range;
	curr_pwr_watts -= running_avg_capture;
	curr_pwr_watts *= data->tdp_to_watts;

	/*
	 * Convert to microWatt
	 *
	 * घातer is in Watt provided as fixed poपूर्णांक पूर्णांकeger with
	 * scaling factor 1/(2^16).  For conversion we use
	 * (10^6)/(2^16) = 15625/(2^10)
	 */
	curr_pwr_watts = (curr_pwr_watts * 15625) >> (10 + running_avg_range);
	वापस प्र_लिखो(buf, "%u\n", (अचिन्हित पूर्णांक) curr_pwr_watts);
पूर्ण
अटल DEVICE_ATTR_RO(घातer1_input);

अटल sमाप_प्रकार घातer1_crit_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fam15h_घातer_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", data->processor_pwr_watts);
पूर्ण
अटल DEVICE_ATTR_RO(घातer1_crit);

अटल व्योम करो_पढ़ो_रेजिस्टरs_on_cu(व्योम *_data)
अणु
	काष्ठा fam15h_घातer_data *data = _data;
	पूर्णांक cpu, cu;

	cpu = smp_processor_id();

	/*
	 * With the new x86 topology modelling, cpu core id actually
	 * is compute unit id.
	 */
	cu = cpu_data(cpu).cpu_core_id;

	rdmsrl_safe(MSR_F15H_CU_PWR_ACCUMULATOR, &data->cu_acc_घातer[cu]);
	rdmsrl_safe(MSR_F15H_PTSC, &data->cpu_sw_pwr_ptsc[cu]);

	data->cu_on[cu] = 1;
पूर्ण

/*
 * This function is only able to be called when CPUID
 * Fn8000_0007:EDX[12] is set.
 */
अटल पूर्णांक पढ़ो_रेजिस्टरs(काष्ठा fam15h_घातer_data *data)
अणु
	पूर्णांक core, this_core;
	cpumask_var_t mask;
	पूर्णांक ret, cpu;

	ret = zalloc_cpumask_var(&mask, GFP_KERNEL);
	अगर (!ret)
		वापस -ENOMEM;

	स_रखो(data->cu_on, 0, माप(पूर्णांक) * MAX_CUS);

	get_online_cpus();

	/*
	 * Choose the first online core of each compute unit, and then
	 * पढ़ो their MSR value of घातer and ptsc in a single IPI,
	 * because the MSR value of CPU core represent the compute
	 * unit's.
	 */
	core = -1;

	क्रम_each_online_cpu(cpu) अणु
		this_core = topology_core_id(cpu);

		अगर (this_core == core)
			जारी;

		core = this_core;

		/* get any CPU on this compute unit */
		cpumask_set_cpu(cpumask_any(topology_sibling_cpumask(cpu)), mask);
	पूर्ण

	on_each_cpu_mask(mask, करो_पढ़ो_रेजिस्टरs_on_cu, data, true);

	put_online_cpus();
	मुक्त_cpumask_var(mask);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार घातer1_average_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fam15h_घातer_data *data = dev_get_drvdata(dev);
	u64 prev_cu_acc_घातer[MAX_CUS], prev_ptsc[MAX_CUS],
	    jdelta[MAX_CUS];
	u64 tdelta, avg_acc;
	पूर्णांक cu, cu_num, ret;
	चिन्हित दीर्घ leftover;

	/*
	 * With the new x86 topology modelling, x86_max_cores is the
	 * compute unit number.
	 */
	cu_num = boot_cpu_data.x86_max_cores;

	ret = पढ़ो_रेजिस्टरs(data);
	अगर (ret)
		वापस 0;

	क्रम (cu = 0; cu < cu_num; cu++) अणु
		prev_cu_acc_घातer[cu] = data->cu_acc_घातer[cu];
		prev_ptsc[cu] = data->cpu_sw_pwr_ptsc[cu];
	पूर्ण

	leftover = schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(data->घातer_period));
	अगर (leftover)
		वापस 0;

	ret = पढ़ो_रेजिस्टरs(data);
	अगर (ret)
		वापस 0;

	क्रम (cu = 0, avg_acc = 0; cu < cu_num; cu++) अणु
		/* check अगर current compute unit is online */
		अगर (data->cu_on[cu] == 0)
			जारी;

		अगर (data->cu_acc_घातer[cu] < prev_cu_acc_घातer[cu]) अणु
			jdelta[cu] = data->max_cu_acc_घातer + data->cu_acc_घातer[cu];
			jdelta[cu] -= prev_cu_acc_घातer[cu];
		पूर्ण अन्यथा अणु
			jdelta[cu] = data->cu_acc_घातer[cu] - prev_cu_acc_घातer[cu];
		पूर्ण
		tdelta = data->cpu_sw_pwr_ptsc[cu] - prev_ptsc[cu];
		jdelta[cu] *= data->cpu_pwr_sample_ratio * 1000;
		करो_भाग(jdelta[cu], tdelta);

		/* the unit is microWatt */
		avg_acc += jdelta[cu];
	पूर्ण

	वापस प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)avg_acc);
पूर्ण
अटल DEVICE_ATTR_RO(घातer1_average);

अटल sमाप_प्रकार घातer1_average_पूर्णांकerval_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा fam15h_घातer_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lu\n", data->घातer_period);
पूर्ण

अटल sमाप_प्रकार घातer1_average_पूर्णांकerval_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fam15h_घातer_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ temp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &temp);
	अगर (ret)
		वापस ret;

	अगर (temp > MAX_INTERVAL)
		वापस -EINVAL;

	/* the पूर्णांकerval value should be greater than 0 */
	अगर (temp <= 0)
		वापस -EINVAL;

	data->घातer_period = temp;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(घातer1_average_पूर्णांकerval);

अटल पूर्णांक fam15h_घातer_init_attrs(काष्ठा pci_dev *pdev,
				   काष्ठा fam15h_घातer_data *data)
अणु
	पूर्णांक n = FAM15H_MIN_NUM_ATTRS;
	काष्ठा attribute **fam15h_घातer_attrs;
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	अगर (c->x86 == 0x15 &&
	    (c->x86_model <= 0xf ||
	     (c->x86_model >= 0x60 && c->x86_model <= 0x7f)))
		n += 1;

	/* check अगर processor supports accumulated घातer */
	अगर (boot_cpu_has(X86_FEATURE_ACC_POWER))
		n += 2;

	fam15h_घातer_attrs = devm_kसुस्मृति(&pdev->dev, n,
					  माप(*fam15h_घातer_attrs),
					  GFP_KERNEL);

	अगर (!fam15h_घातer_attrs)
		वापस -ENOMEM;

	n = 0;
	fam15h_घातer_attrs[n++] = &dev_attr_घातer1_crit.attr;
	अगर (c->x86 == 0x15 &&
	    (c->x86_model <= 0xf ||
	     (c->x86_model >= 0x60 && c->x86_model <= 0x7f)))
		fam15h_घातer_attrs[n++] = &dev_attr_घातer1_input.attr;

	अगर (boot_cpu_has(X86_FEATURE_ACC_POWER)) अणु
		fam15h_घातer_attrs[n++] = &dev_attr_घातer1_average.attr;
		fam15h_घातer_attrs[n++] = &dev_attr_घातer1_average_पूर्णांकerval.attr;
	पूर्ण

	data->group.attrs = fam15h_घातer_attrs;

	वापस 0;
पूर्ण

अटल bool should_load_on_this_node(काष्ठा pci_dev *f4)
अणु
	u32 val;

	pci_bus_पढ़ो_config_dword(f4->bus, PCI_DEVFN(PCI_SLOT(f4->devfn), 3),
				  REG_NORTHBRIDGE_CAP, &val);
	अगर ((val & BIT(29)) && ((val >> 30) & 3))
		वापस false;

	वापस true;
पूर्ण

/*
 * Newer BKDG versions have an updated recommendation on how to properly
 * initialize the running average range (was: 0xE, now: 0x9). This aव्योमs
 * counter saturations resulting in bogus घातer पढ़ोings.
 * We correct this value ourselves to cope with older BIOSes.
 */
अटल स्थिर काष्ठा pci_device_id affected_device[] = अणु
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_NB_F4) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल व्योम tweak_runavg_range(काष्ठा pci_dev *pdev)
अणु
	u32 val;

	/*
	 * let this quirk apply only to the current version of the
	 * northbridge, since future versions may change the behavior
	 */
	अगर (!pci_match_id(affected_device, pdev))
		वापस;

	pci_bus_पढ़ो_config_dword(pdev->bus,
		PCI_DEVFN(PCI_SLOT(pdev->devfn), 5),
		REG_TDP_RUNNING_AVERAGE, &val);
	अगर ((val & 0xf) != 0xe)
		वापस;

	val &= ~0xf;
	val |=  0x9;
	pci_bus_ग_लिखो_config_dword(pdev->bus,
		PCI_DEVFN(PCI_SLOT(pdev->devfn), 5),
		REG_TDP_RUNNING_AVERAGE, val);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fam15h_घातer_resume(काष्ठा pci_dev *pdev)
अणु
	tweak_runavg_range(pdev);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा fam15h_घातer_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक fam15h_घातer_init_data(काष्ठा pci_dev *f4,
				  काष्ठा fam15h_घातer_data *data)
अणु
	u32 val;
	u64 पंचांगp;
	पूर्णांक ret;

	pci_पढ़ो_config_dword(f4, REG_PROCESSOR_TDP, &val);
	data->base_tdp = val >> 16;
	पंचांगp = val & 0xffff;

	pci_bus_पढ़ो_config_dword(f4->bus, PCI_DEVFN(PCI_SLOT(f4->devfn), 5),
				  REG_TDP_LIMIT3, &val);

	data->tdp_to_watts = ((val & 0x3ff) << 6) | ((val >> 10) & 0x3f);
	पंचांगp *= data->tdp_to_watts;

	/* result not allowed to be >= 256W */
	अगर ((पंचांगp >> 16) >= 256)
		dev_warn(&f4->dev,
			 "Bogus value for ProcessorPwrWatts (processor_pwr_watts>=%u)\n",
			 (अचिन्हित पूर्णांक) (पंचांगp >> 16));

	/* convert to microWatt */
	data->processor_pwr_watts = (पंचांगp * 15625) >> 10;

	ret = fam15h_घातer_init_attrs(f4, data);
	अगर (ret)
		वापस ret;


	/* CPUID Fn8000_0007:EDX[12] indicates to support accumulated घातer */
	अगर (!boot_cpu_has(X86_FEATURE_ACC_POWER))
		वापस 0;

	/*
	 * determine the ratio of the compute unit घातer accumulator
	 * sample period to the PTSC counter period by executing CPUID
	 * Fn8000_0007:ECX
	 */
	data->cpu_pwr_sample_ratio = cpuid_ecx(0x80000007);

	अगर (rdmsrl_safe(MSR_F15H_CU_MAX_PWR_ACCUMULATOR, &पंचांगp)) अणु
		pr_err("Failed to read max compute unit power accumulator MSR\n");
		वापस -ENODEV;
	पूर्ण

	data->max_cu_acc_घातer = पंचांगp;

	/*
	 * Milliseconds are a reasonable पूर्णांकerval क्रम the measurement.
	 * But it shouldn't set too दीर्घ here, because several seconds
	 * would cause the पढ़ो function to hang. So set शेष
	 * पूर्णांकerval as 10 ms.
	 */
	data->घातer_period = 10;

	वापस पढ़ो_रेजिस्टरs(data);
पूर्ण

अटल पूर्णांक fam15h_घातer_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा fam15h_घातer_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret;

	/*
	 * though we ignore every other northbridge, we still have to
	 * करो the tweaking on _each_ node in MCM processors as the counters
	 * are working hand-in-hand
	 */
	tweak_runavg_range(pdev);

	अगर (!should_load_on_this_node(pdev))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(काष्ठा fam15h_घातer_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = fam15h_घातer_init_data(pdev, data);
	अगर (ret)
		वापस ret;

	data->pdev = pdev;

	data->groups[0] = &data->group;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, "fam15h_power",
							   data,
							   &data->groups[0]);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id fam15h_घातer_id_table[] = अणु
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_NB_F4) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M30H_NB_F4) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M60H_NB_F4) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M70H_NB_F4) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_16H_NB_F4) पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_16H_M30H_NB_F4) पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, fam15h_घातer_id_table);

अटल काष्ठा pci_driver fam15h_घातer_driver = अणु
	.name = "fam15h_power",
	.id_table = fam15h_घातer_id_table,
	.probe = fam15h_घातer_probe,
	.resume = fam15h_घातer_resume,
पूर्ण;

module_pci_driver(fam15h_घातer_driver);
