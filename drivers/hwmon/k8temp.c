<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * k8temp.c - Linux kernel module क्रम hardware monitoring
 *
 * Copyright (C) 2006 Ruकरोlf Marek <r.marek@assembler.cz>
 *
 * Inspired from the w83785 and amd756 drivers.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/processor.h>

#घोषणा TEMP_FROM_REG(val)	(((((val) >> 16) & 0xff) - 49) * 1000)
#घोषणा REG_TEMP	0xe4
#घोषणा SEL_PLACE	0x40
#घोषणा SEL_CORE	0x04

काष्ठा k8temp_data अणु
	काष्ठा mutex update_lock;

	/* रेजिस्टरs values */
	u8 sensorsp;		/* sensor presence bits - SEL_CORE, SEL_PLACE */
	u8 swap_core_select;    /* meaning of SEL_CORE is inverted */
	u32 temp_offset;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id k8temp_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_MISC) पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, k8temp_ids);

अटल पूर्णांक is_rev_g_desktop(u8 model)
अणु
	u32 bअक्रमidx;

	अगर (model < 0x69)
		वापस 0;

	अगर (model == 0xc1 || model == 0x6c || model == 0x7c)
		वापस 0;

	/*
	 * Dअगरferentiate between AM2 and ASB1.
	 * See "Constructing the processor Name String" in "Revision
	 * Guide क्रम AMD NPT Family 0Fh Processors" (33610).
	 */
	bअक्रमidx = cpuid_ebx(0x80000001);
	bअक्रमidx = (bअक्रमidx >> 9) & 0x1f;

	/* Single core */
	अगर ((model == 0x6f || model == 0x7f) &&
	    (bअक्रमidx == 0x7 || bअक्रमidx == 0x9 || bअक्रमidx == 0xc))
		वापस 0;

	/* Dual core */
	अगर (model == 0x6b &&
	    (bअक्रमidx == 0xb || bअक्रमidx == 0xc))
		वापस 0;

	वापस 1;
पूर्ण

अटल umode_t
k8temp_is_visible(स्थिर व्योम *drvdata, क्रमागत hwmon_sensor_types type,
		  u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा k8temp_data *data = drvdata;

	अगर ((channel & 1) && !(data->sensorsp & SEL_PLACE))
		वापस 0;

	अगर ((channel & 2) && !(data->sensorsp & SEL_CORE))
		वापस 0;

	वापस 0444;
पूर्ण

अटल पूर्णांक
k8temp_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
	    u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा k8temp_data *data = dev_get_drvdata(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->parent);
	पूर्णांक core, place;
	u32 temp;
	u8 पंचांगp;

	core = (channel >> 1) & 1;
	place = channel & 1;

	core ^= data->swap_core_select;

	mutex_lock(&data->update_lock);
	pci_पढ़ो_config_byte(pdev, REG_TEMP, &पंचांगp);
	पंचांगp &= ~(SEL_PLACE | SEL_CORE);
	अगर (core)
		पंचांगp |= SEL_CORE;
	अगर (place)
		पंचांगp |= SEL_PLACE;
	pci_ग_लिखो_config_byte(pdev, REG_TEMP, पंचांगp);
	pci_पढ़ो_config_dword(pdev, REG_TEMP, &temp);
	mutex_unlock(&data->update_lock);

	*val = TEMP_FROM_REG(temp) + data->temp_offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops k8temp_ops = अणु
	.is_visible = k8temp_is_visible,
	.पढ़ो = k8temp_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *k8temp_info[] = अणु
	HWMON_CHANNEL_INFO(temp,
		HWMON_T_INPUT, HWMON_T_INPUT, HWMON_T_INPUT, HWMON_T_INPUT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info k8temp_chip_info = अणु
	.ops = &k8temp_ops,
	.info = k8temp_info,
पूर्ण;

अटल पूर्णांक k8temp_probe(काष्ठा pci_dev *pdev,
				  स्थिर काष्ठा pci_device_id *id)
अणु
	u8 scfg;
	u32 temp;
	u8 model, stepping;
	काष्ठा k8temp_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा k8temp_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	model = boot_cpu_data.x86_model;
	stepping = boot_cpu_data.x86_stepping;

	/* feature available since SH-C0, exclude older revisions */
	अगर ((model == 4 && stepping == 0) ||
	    (model == 5 && stepping <= 1))
		वापस -ENODEV;

	/*
	 * AMD NPT family 0fh, i.e. RevF and RevG:
	 * meaning of SEL_CORE bit is inverted
	 */
	अगर (model >= 0x40) अणु
		data->swap_core_select = 1;
		dev_warn(&pdev->dev,
			 "Temperature readouts might be wrong - check erratum #141\n");
	पूर्ण

	/*
	 * RevG desktop CPUs (i.e. no socket S1G1 or ASB1 parts) need
	 * additional offset, otherwise reported temperature is below
	 * ambient temperature
	 */
	अगर (is_rev_g_desktop(model))
		data->temp_offset = 21000;

	pci_पढ़ो_config_byte(pdev, REG_TEMP, &scfg);
	scfg &= ~(SEL_PLACE | SEL_CORE);	/* Select sensor 0, core0 */
	pci_ग_लिखो_config_byte(pdev, REG_TEMP, scfg);
	pci_पढ़ो_config_byte(pdev, REG_TEMP, &scfg);

	अगर (scfg & (SEL_PLACE | SEL_CORE)) अणु
		dev_err(&pdev->dev, "Configuration bit(s) stuck at 1!\n");
		वापस -ENODEV;
	पूर्ण

	scfg |= (SEL_PLACE | SEL_CORE);
	pci_ग_लिखो_config_byte(pdev, REG_TEMP, scfg);

	/* now we know अगर we can change core and/or sensor */
	pci_पढ़ो_config_byte(pdev, REG_TEMP, &data->sensorsp);

	अगर (data->sensorsp & SEL_PLACE) अणु
		scfg &= ~SEL_CORE;	/* Select sensor 1, core0 */
		pci_ग_लिखो_config_byte(pdev, REG_TEMP, scfg);
		pci_पढ़ो_config_dword(pdev, REG_TEMP, &temp);
		scfg |= SEL_CORE;	/* prepare क्रम next selection */
		अगर (!((temp >> 16) & 0xff)) /* अगर temp is 0 -49C is unlikely */
			data->sensorsp &= ~SEL_PLACE;
	पूर्ण

	अगर (data->sensorsp & SEL_CORE) अणु
		scfg &= ~SEL_PLACE;	/* Select sensor 0, core1 */
		pci_ग_लिखो_config_byte(pdev, REG_TEMP, scfg);
		pci_पढ़ो_config_dword(pdev, REG_TEMP, &temp);
		अगर (!((temp >> 16) & 0xff)) /* अगर temp is 0 -49C is unlikely */
			data->sensorsp &= ~SEL_CORE;
	पूर्ण

	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(&pdev->dev,
							 "k8temp",
							 data,
							 &k8temp_chip_info,
							 शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा pci_driver k8temp_driver = अणु
	.name = "k8temp",
	.id_table = k8temp_ids,
	.probe = k8temp_probe,
पूर्ण;

module_pci_driver(k8temp_driver);

MODULE_AUTHOR("Rudolf Marek <r.marek@assembler.cz>");
MODULE_DESCRIPTION("AMD K8 core temperature monitor");
MODULE_LICENSE("GPL");
