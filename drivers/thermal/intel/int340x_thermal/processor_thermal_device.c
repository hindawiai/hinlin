<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * processor_thermal_device.c
 * Copyright (c) 2014, Intel Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/thermal.h>
#समावेश <linux/cpuhotplug.h>
#समावेश "int340x_thermal_zone.h"
#समावेश "processor_thermal_device.h"
#समावेश "../intel_soc_dts_iosf.h"

#घोषणा DRV_NAME "proc_thermal"

क्रमागत proc_thermal_emum_mode_type अणु
	PROC_THERMAL_NONE,
	PROC_THERMAL_PCI,
	PROC_THERMAL_PLATFORM_DEV
पूर्ण;

/*
 * We can have only one type of क्रमागतeration, PCI or Platक्रमm,
 * not both. So we करोn't need instance specअगरic data.
 */
अटल क्रमागत proc_thermal_emum_mode_type proc_thermal_emum_mode =
							PROC_THERMAL_NONE;

#घोषणा POWER_LIMIT_SHOW(index, suffix) \
अटल sमाप_प्रकार घातer_limit_##index##_##suffix##_show(काष्ठा device *dev, \
					काष्ठा device_attribute *attr, \
					अक्षर *buf) \
अणु \
	काष्ठा proc_thermal_device *proc_dev = dev_get_drvdata(dev); \
	\
	अगर (proc_thermal_emum_mode == PROC_THERMAL_NONE) अणु \
		dev_warn(dev, "Attempted to get power limit before device was initialized!\n"); \
		वापस 0; \
	पूर्ण \
	\
	वापस प्र_लिखो(buf, "%lu\n",\
	(अचिन्हित दीर्घ)proc_dev->घातer_limits[index].suffix * 1000); \
पूर्ण

POWER_LIMIT_SHOW(0, min_uw)
POWER_LIMIT_SHOW(0, max_uw)
POWER_LIMIT_SHOW(0, step_uw)
POWER_LIMIT_SHOW(0, पंचांगin_us)
POWER_LIMIT_SHOW(0, पंचांगax_us)

POWER_LIMIT_SHOW(1, min_uw)
POWER_LIMIT_SHOW(1, max_uw)
POWER_LIMIT_SHOW(1, step_uw)
POWER_LIMIT_SHOW(1, पंचांगin_us)
POWER_LIMIT_SHOW(1, पंचांगax_us)

अटल DEVICE_ATTR_RO(घातer_limit_0_min_uw);
अटल DEVICE_ATTR_RO(घातer_limit_0_max_uw);
अटल DEVICE_ATTR_RO(घातer_limit_0_step_uw);
अटल DEVICE_ATTR_RO(घातer_limit_0_पंचांगin_us);
अटल DEVICE_ATTR_RO(घातer_limit_0_पंचांगax_us);

अटल DEVICE_ATTR_RO(घातer_limit_1_min_uw);
अटल DEVICE_ATTR_RO(घातer_limit_1_max_uw);
अटल DEVICE_ATTR_RO(घातer_limit_1_step_uw);
अटल DEVICE_ATTR_RO(घातer_limit_1_पंचांगin_us);
अटल DEVICE_ATTR_RO(घातer_limit_1_पंचांगax_us);

अटल काष्ठा attribute *घातer_limit_attrs[] = अणु
	&dev_attr_घातer_limit_0_min_uw.attr,
	&dev_attr_घातer_limit_1_min_uw.attr,
	&dev_attr_घातer_limit_0_max_uw.attr,
	&dev_attr_घातer_limit_1_max_uw.attr,
	&dev_attr_घातer_limit_0_step_uw.attr,
	&dev_attr_घातer_limit_1_step_uw.attr,
	&dev_attr_घातer_limit_0_पंचांगin_us.attr,
	&dev_attr_घातer_limit_1_पंचांगin_us.attr,
	&dev_attr_घातer_limit_0_पंचांगax_us.attr,
	&dev_attr_घातer_limit_1_पंचांगax_us.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group घातer_limit_attribute_group = अणु
	.attrs = घातer_limit_attrs,
	.name = "power_limits"
पूर्ण;

अटल sमाप_प्रकार tcc_offset_degree_celsius_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u64 val;
	पूर्णांक err;

	err = rdmsrl_safe(MSR_IA32_TEMPERATURE_TARGET, &val);
	अगर (err)
		वापस err;

	val = (val >> 24) & 0xff;
	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)val);
पूर्ण

अटल पूर्णांक tcc_offset_update(पूर्णांक tcc)
अणु
	u64 val;
	पूर्णांक err;

	अगर (!tcc)
		वापस -EINVAL;

	err = rdmsrl_safe(MSR_IA32_TEMPERATURE_TARGET, &val);
	अगर (err)
		वापस err;

	val &= ~GENMASK_ULL(31, 24);
	val |= (tcc & 0xff) << 24;

	err = wrmsrl_safe(MSR_IA32_TEMPERATURE_TARGET, val);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tcc_offset_save;

अटल sमाप_प्रकार tcc_offset_degree_celsius_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	u64 val;
	पूर्णांक tcc, err;

	err = rdmsrl_safe(MSR_PLATFORM_INFO, &val);
	अगर (err)
		वापस err;

	अगर (!(val & BIT(30)))
		वापस -EACCES;

	अगर (kstrtoपूर्णांक(buf, 0, &tcc))
		वापस -EINVAL;

	err = tcc_offset_update(tcc);
	अगर (err)
		वापस err;

	tcc_offset_save = tcc;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(tcc_offset_degree_celsius);

अटल पूर्णांक stored_tjmax; /* since it is fixed, we can have local storage */

अटल पूर्णांक get_tjmax(व्योम)
अणु
	u32 eax, edx;
	u32 val;
	पूर्णांक err;

	err = rdmsr_safe(MSR_IA32_TEMPERATURE_TARGET, &eax, &edx);
	अगर (err)
		वापस err;

	val = (eax >> 16) & 0xff;
	अगर (val)
		वापस val;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पढ़ो_temp_msr(पूर्णांक *temp)
अणु
	पूर्णांक cpu;
	u32 eax, edx;
	पूर्णांक err;
	अचिन्हित दीर्घ curr_temp_off = 0;

	*temp = 0;

	क्रम_each_online_cpu(cpu) अणु
		err = rdmsr_safe_on_cpu(cpu, MSR_IA32_THERM_STATUS, &eax,
					&edx);
		अगर (err)
			जाओ err_ret;
		अन्यथा अणु
			अगर (eax & 0x80000000) अणु
				curr_temp_off = (eax >> 16) & 0x7f;
				अगर (!*temp || curr_temp_off < *temp)
					*temp = curr_temp_off;
			पूर्ण अन्यथा अणु
				err = -EINVAL;
				जाओ err_ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
err_ret:
	वापस err;
पूर्ण

अटल पूर्णांक proc_thermal_get_zone_temp(काष्ठा thermal_zone_device *zone,
					 पूर्णांक *temp)
अणु
	पूर्णांक ret;

	ret = पढ़ो_temp_msr(temp);
	अगर (!ret)
		*temp = (stored_tjmax - *temp) * 1000;

	वापस ret;
पूर्ण

अटल काष्ठा thermal_zone_device_ops proc_thermal_local_ops = अणु
	.get_temp       = proc_thermal_get_zone_temp,
पूर्ण;

अटल पूर्णांक proc_thermal_पढ़ो_ppcc(काष्ठा proc_thermal_device *proc_priv)
अणु
	पूर्णांक i;
	acpi_status status;
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *elements, *ppcc;
	जोड़ acpi_object *p;
	पूर्णांक ret = 0;

	status = acpi_evaluate_object(proc_priv->adev->handle, "PPCC",
				      शून्य, &buf);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	p = buf.poपूर्णांकer;
	अगर (!p || (p->type != ACPI_TYPE_PACKAGE)) अणु
		dev_err(proc_priv->dev, "Invalid PPCC data\n");
		ret = -EFAULT;
		जाओ मुक्त_buffer;
	पूर्ण

	अगर (!p->package.count) अणु
		dev_err(proc_priv->dev, "Invalid PPCC package size\n");
		ret = -EFAULT;
		जाओ मुक्त_buffer;
	पूर्ण

	क्रम (i = 0; i < min((पूर्णांक)p->package.count - 1, 2); ++i) अणु
		elements = &(p->package.elements[i+1]);
		अगर (elements->type != ACPI_TYPE_PACKAGE ||
		    elements->package.count != 6) अणु
			ret = -EFAULT;
			जाओ मुक्त_buffer;
		पूर्ण
		ppcc = elements->package.elements;
		proc_priv->घातer_limits[i].index = ppcc[0].पूर्णांकeger.value;
		proc_priv->घातer_limits[i].min_uw = ppcc[1].पूर्णांकeger.value;
		proc_priv->घातer_limits[i].max_uw = ppcc[2].पूर्णांकeger.value;
		proc_priv->घातer_limits[i].पंचांगin_us = ppcc[3].पूर्णांकeger.value;
		proc_priv->घातer_limits[i].पंचांगax_us = ppcc[4].पूर्णांकeger.value;
		proc_priv->घातer_limits[i].step_uw = ppcc[5].पूर्णांकeger.value;
	पूर्ण

मुक्त_buffer:
	kमुक्त(buf.poपूर्णांकer);

	वापस ret;
पूर्ण

#घोषणा PROC_POWER_CAPABILITY_CHANGED	0x83
अटल व्योम proc_thermal_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा proc_thermal_device *proc_priv = data;

	अगर (!proc_priv)
		वापस;

	चयन (event) अणु
	हाल PROC_POWER_CAPABILITY_CHANGED:
		proc_thermal_पढ़ो_ppcc(proc_priv);
		पूर्णांक340x_thermal_zone_device_update(proc_priv->पूर्णांक340x_zone,
				THERMAL_DEVICE_POWER_CAPABILITY_CHANGED);
		अवरोध;
	शेष:
		dev_dbg(proc_priv->dev, "Unsupported event [0x%x]\n", event);
		अवरोध;
	पूर्ण
पूर्ण


अटल पूर्णांक proc_thermal_add(काष्ठा device *dev,
			    काष्ठा proc_thermal_device **priv)
अणु
	काष्ठा proc_thermal_device *proc_priv;
	काष्ठा acpi_device *adev;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	काष्ठा thermal_zone_device_ops *ops = शून्य;
	पूर्णांक ret;

	adev = ACPI_COMPANION(dev);
	अगर (!adev)
		वापस -ENODEV;

	proc_priv = devm_kzalloc(dev, माप(*proc_priv), GFP_KERNEL);
	अगर (!proc_priv)
		वापस -ENOMEM;

	proc_priv->dev = dev;
	proc_priv->adev = adev;
	*priv = proc_priv;

	ret = proc_thermal_पढ़ो_ppcc(proc_priv);
	अगर (ret)
		वापस ret;

	status = acpi_evaluate_पूर्णांकeger(adev->handle, "_TMP", शून्य, &पंचांगp);
	अगर (ACPI_FAILURE(status)) अणु
		/* there is no _TMP method, add local method */
		stored_tjmax = get_tjmax();
		अगर (stored_tjmax > 0)
			ops = &proc_thermal_local_ops;
	पूर्ण

	proc_priv->पूर्णांक340x_zone = पूर्णांक340x_thermal_zone_add(adev, ops);
	अगर (IS_ERR(proc_priv->पूर्णांक340x_zone)) अणु
		वापस PTR_ERR(proc_priv->पूर्णांक340x_zone);
	पूर्ण अन्यथा
		ret = 0;

	ret = acpi_install_notअगरy_handler(adev->handle, ACPI_DEVICE_NOTIFY,
					  proc_thermal_notअगरy,
					  (व्योम *)proc_priv);
	अगर (ret)
		जाओ हटाओ_zone;

	वापस 0;

हटाओ_zone:
	पूर्णांक340x_thermal_zone_हटाओ(proc_priv->पूर्णांक340x_zone);

	वापस ret;
पूर्ण

अटल व्योम proc_thermal_हटाओ(काष्ठा proc_thermal_device *proc_priv)
अणु
	acpi_हटाओ_notअगरy_handler(proc_priv->adev->handle,
				   ACPI_DEVICE_NOTIFY, proc_thermal_notअगरy);
	पूर्णांक340x_thermal_zone_हटाओ(proc_priv->पूर्णांक340x_zone);
	sysfs_हटाओ_file(&proc_priv->dev->kobj, &dev_attr_tcc_offset_degree_celsius.attr);
	sysfs_हटाओ_group(&proc_priv->dev->kobj,
			   &घातer_limit_attribute_group);
पूर्ण

अटल पूर्णांक पूर्णांक3401_add(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा proc_thermal_device *proc_priv;
	पूर्णांक ret;

	अगर (proc_thermal_emum_mode == PROC_THERMAL_PCI) अणु
		dev_err(&pdev->dev, "error: enumerated as PCI dev\n");
		वापस -ENODEV;
	पूर्ण

	ret = proc_thermal_add(&pdev->dev, &proc_priv);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, proc_priv);
	proc_thermal_emum_mode = PROC_THERMAL_PLATFORM_DEV;

	dev_info(&pdev->dev, "Creating sysfs group for PROC_THERMAL_PLATFORM_DEV\n");

	ret = sysfs_create_file(&pdev->dev.kobj, &dev_attr_tcc_offset_degree_celsius.attr);
	अगर (ret)
		वापस ret;

	ret = sysfs_create_group(&pdev->dev.kobj, &घातer_limit_attribute_group);
	अगर (ret)
		sysfs_हटाओ_file(&pdev->dev.kobj, &dev_attr_tcc_offset_degree_celsius.attr);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांक3401_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	proc_thermal_हटाओ(platक्रमm_get_drvdata(pdev));

	वापस 0;
पूर्ण

अटल irqवापस_t proc_thermal_pci_msi_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा proc_thermal_device *proc_priv;
	काष्ठा pci_dev *pdev = devid;

	proc_priv = pci_get_drvdata(pdev);

	पूर्णांकel_soc_dts_iosf_पूर्णांकerrupt_handler(proc_priv->soc_dts);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा MCHBAR 0

अटल पूर्णांक proc_thermal_set_mmio_base(काष्ठा pci_dev *pdev,
				      काष्ठा proc_thermal_device *proc_priv)
अणु
	पूर्णांक ret;

	ret = pcim_iomap_regions(pdev, 1 << MCHBAR, DRV_NAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot reserve PCI memory region\n");
		वापस -ENOMEM;
	पूर्ण

	proc_priv->mmio_base = pcim_iomap_table(pdev)[MCHBAR];

	वापस 0;
पूर्ण

अटल पूर्णांक proc_thermal_mmio_add(काष्ठा pci_dev *pdev,
				 काष्ठा proc_thermal_device *proc_priv,
				 kernel_uदीर्घ_t feature_mask)
अणु
	पूर्णांक ret;

	proc_priv->mmio_feature_mask = feature_mask;

	अगर (feature_mask) अणु
		ret = proc_thermal_set_mmio_base(pdev, proc_priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (feature_mask & PROC_THERMAL_FEATURE_RAPL) अणु
		ret = proc_thermal_rapl_add(pdev, proc_priv);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to add RAPL MMIO interface\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (feature_mask & PROC_THERMAL_FEATURE_FIVR ||
	    feature_mask & PROC_THERMAL_FEATURE_DVFS) अणु
		ret = proc_thermal_rfim_add(pdev, proc_priv);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to add RFIM interface\n");
			जाओ err_rem_rapl;
		पूर्ण
	पूर्ण

	अगर (feature_mask & PROC_THERMAL_FEATURE_MBOX) अणु
		ret = proc_thermal_mbox_add(pdev, proc_priv);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to add MBOX interface\n");
			जाओ err_rem_rfim;
		पूर्ण
	पूर्ण

	वापस 0;

err_rem_rfim:
	proc_thermal_rfim_हटाओ(pdev);
err_rem_rapl:
	proc_thermal_rapl_हटाओ();

	वापस ret;
पूर्ण

अटल व्योम proc_thermal_mmio_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा proc_thermal_device *proc_priv = pci_get_drvdata(pdev);

	अगर (proc_priv->mmio_feature_mask & PROC_THERMAL_FEATURE_RAPL)
		proc_thermal_rapl_हटाओ();

	अगर (proc_priv->mmio_feature_mask & PROC_THERMAL_FEATURE_FIVR ||
	    proc_priv->mmio_feature_mask & PROC_THERMAL_FEATURE_DVFS)
		proc_thermal_rfim_हटाओ(pdev);

	अगर (proc_priv->mmio_feature_mask & PROC_THERMAL_FEATURE_MBOX)
		proc_thermal_mbox_हटाओ(pdev);
पूर्ण

अटल पूर्णांक  proc_thermal_pci_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा proc_thermal_device *proc_priv;
	पूर्णांक ret;

	अगर (proc_thermal_emum_mode == PROC_THERMAL_PLATFORM_DEV) अणु
		dev_err(&pdev->dev, "error: enumerated as platform dev\n");
		वापस -ENODEV;
	पूर्ण

	ret = pcim_enable_device(pdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "error: could not enable device\n");
		वापस ret;
	पूर्ण

	ret = proc_thermal_add(&pdev->dev, &proc_priv);
	अगर (ret)
		वापस ret;

	pci_set_drvdata(pdev, proc_priv);
	proc_thermal_emum_mode = PROC_THERMAL_PCI;

	अगर (pdev->device == PCI_DEVICE_ID_INTEL_BSW_THERMAL) अणु
		/*
		 * Enumerate additional DTS sensors available via IOSF.
		 * But we are not treating as a failure condition, अगर
		 * there are no aux DTSs enabled or fails. This driver
		 * alपढ़ोy exposes sensors, which can be accessed via
		 * ACPI/MSR. So we करोn't want to fail क्रम auxiliary DTSs.
		 */
		proc_priv->soc_dts = पूर्णांकel_soc_dts_iosf_init(
					INTEL_SOC_DTS_INTERRUPT_MSI, 2, 0);

		अगर (!IS_ERR(proc_priv->soc_dts) && pdev->irq) अणु
			ret = pci_enable_msi(pdev);
			अगर (!ret) अणु
				ret = request_thपढ़ोed_irq(pdev->irq, शून्य,
						proc_thermal_pci_msi_irq,
						IRQF_ONESHOT, "proc_thermal",
						pdev);
				अगर (ret) अणु
					पूर्णांकel_soc_dts_iosf_निकास(
							proc_priv->soc_dts);
					pci_disable_msi(pdev);
					proc_priv->soc_dts = शून्य;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			dev_err(&pdev->dev, "No auxiliary DTSs enabled\n");
	पूर्ण

	dev_info(&pdev->dev, "Creating sysfs group for PROC_THERMAL_PCI\n");

	ret = sysfs_create_file(&pdev->dev.kobj, &dev_attr_tcc_offset_degree_celsius.attr);
	अगर (ret)
		वापस ret;

	ret = sysfs_create_group(&pdev->dev.kobj, &घातer_limit_attribute_group);
	अगर (ret) अणु
		sysfs_हटाओ_file(&pdev->dev.kobj, &dev_attr_tcc_offset_degree_celsius.attr);
		वापस ret;
	पूर्ण

	ret = proc_thermal_mmio_add(pdev, proc_priv, id->driver_data);
	अगर (ret) अणु
		proc_thermal_हटाओ(proc_priv);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम  proc_thermal_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा proc_thermal_device *proc_priv = pci_get_drvdata(pdev);

	अगर (proc_priv->soc_dts) अणु
		पूर्णांकel_soc_dts_iosf_निकास(proc_priv->soc_dts);
		अगर (pdev->irq) अणु
			मुक्त_irq(pdev->irq, pdev);
			pci_disable_msi(pdev);
		पूर्ण
	पूर्ण

	proc_thermal_mmio_हटाओ(pdev);
	proc_thermal_हटाओ(proc_priv);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक proc_thermal_resume(काष्ठा device *dev)
अणु
	काष्ठा proc_thermal_device *proc_dev;

	proc_dev = dev_get_drvdata(dev);
	proc_thermal_पढ़ो_ppcc(proc_dev);

	tcc_offset_update(tcc_offset_save);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा proc_thermal_resume शून्य
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(proc_thermal_pm, शून्य, proc_thermal_resume);

अटल स्थिर काष्ठा pci_device_id proc_thermal_pci_ids[] = अणु
	अणु PCI_DEVICE_DATA(INTEL, ADL_THERMAL, PROC_THERMAL_FEATURE_RAPL | PROC_THERMAL_FEATURE_FIVR | PROC_THERMAL_FEATURE_DVFS | PROC_THERMAL_FEATURE_MBOX) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BDW_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BSW_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BXT0_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BXT1_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BXTX_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BXTP_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, CNL_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, CFL_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, GLK_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, HSB_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, ICL_THERMAL, PROC_THERMAL_FEATURE_RAPL) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, JSL_THERMAL, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, SKL_THERMAL, PROC_THERMAL_FEATURE_RAPL) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, TGL_THERMAL, PROC_THERMAL_FEATURE_RAPL | PROC_THERMAL_FEATURE_FIVR | PROC_THERMAL_FEATURE_MBOX) पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, proc_thermal_pci_ids);

अटल काष्ठा pci_driver proc_thermal_pci_driver = अणु
	.name		= DRV_NAME,
	.probe		= proc_thermal_pci_probe,
	.हटाओ		= proc_thermal_pci_हटाओ,
	.id_table	= proc_thermal_pci_ids,
	.driver.pm	= &proc_thermal_pm,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id पूर्णांक3401_device_ids[] = अणु
	अणु"INT3401", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांक3401_device_ids);

अटल काष्ठा platक्रमm_driver पूर्णांक3401_driver = अणु
	.probe = पूर्णांक3401_add,
	.हटाओ = पूर्णांक3401_हटाओ,
	.driver = अणु
		.name = "int3401 thermal",
		.acpi_match_table = पूर्णांक3401_device_ids,
		.pm = &proc_thermal_pm,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init proc_thermal_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&पूर्णांक3401_driver);
	अगर (ret)
		वापस ret;

	ret = pci_रेजिस्टर_driver(&proc_thermal_pci_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास proc_thermal_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&पूर्णांक3401_driver);
	pci_unरेजिस्टर_driver(&proc_thermal_pci_driver);
पूर्ण

module_init(proc_thermal_init);
module_निकास(proc_thermal_निकास);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_DESCRIPTION("Processor Thermal Reporting Device Driver");
MODULE_LICENSE("GPL v2");
