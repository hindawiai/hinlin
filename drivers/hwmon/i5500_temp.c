<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * i5500_temp - Driver क्रम Intel 5500/5520/X58 chipset thermal sensor
 *
 * Copyright (C) 2012, 2014 Jean Delvare <jdelvare@suse.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>

/* Register definitions from datasheet */
#घोषणा REG_TSTHRCATA	0xE2
#घोषणा REG_TSCTRL	0xE8
#घोषणा REG_TSTHRRPEX	0xEB
#घोषणा REG_TSTHRLO	0xEC
#घोषणा REG_TSTHRHI	0xEE
#घोषणा REG_CTHINT	0xF0
#घोषणा REG_TSFSC	0xF3
#घोषणा REG_CTSTS	0xF4
#घोषणा REG_TSTHRRQPI	0xF5
#घोषणा REG_CTCTRL	0xF7
#घोषणा REG_TSTIMER	0xF8

/*
 * Sysfs stuff
 */

/* Sensor resolution : 0.5 degree C */
अटल sमाप_प्रकार temp1_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->parent);
	दीर्घ temp;
	u16 tsthrhi;
	s8 tsfsc;

	pci_पढ़ो_config_word(pdev, REG_TSTHRHI, &tsthrhi);
	pci_पढ़ो_config_byte(pdev, REG_TSFSC, &tsfsc);
	temp = ((दीर्घ)tsthrhi - tsfsc) * 500;

	वापस प्र_लिखो(buf, "%ld\n", temp);
पूर्ण

अटल sमाप_प्रकार thresh_show(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->parent);
	पूर्णांक reg = to_sensor_dev_attr(devattr)->index;
	दीर्घ temp;
	u16 tsthr;

	pci_पढ़ो_config_word(pdev, reg, &tsthr);
	temp = tsthr * 500;

	वापस प्र_लिखो(buf, "%ld\n", temp);
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->parent);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	u8 ctsts;

	pci_पढ़ो_config_byte(pdev, REG_CTSTS, &ctsts);
	वापस प्र_लिखो(buf, "%u\n", (अचिन्हित पूर्णांक)ctsts & (1 << nr));
पूर्ण

अटल DEVICE_ATTR_RO(temp1_input);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit, thresh, 0xE2);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_hyst, thresh, 0xEC);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max, thresh, 0xEE);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 1);

अटल काष्ठा attribute *i5500_temp_attrs[] = अणु
	&dev_attr_temp1_input.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(i5500_temp);

अटल स्थिर काष्ठा pci_device_id i5500_temp_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x3438) पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, i5500_temp_ids);

अटल पूर्णांक i5500_temp_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा device *hwmon_dev;
	u32 tsसमयr;
	s8 tsfsc;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to enable device\n");
		वापस err;
	पूर्ण

	pci_पढ़ो_config_byte(pdev, REG_TSFSC, &tsfsc);
	pci_पढ़ो_config_dword(pdev, REG_TSTIMER, &tsसमयr);
	अगर (tsfsc == 0x7F && tsसमयr == 0x07D30D40) अणु
		dev_notice(&pdev->dev, "Sensor seems to be disabled\n");
		वापस -ENODEV;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev,
							   "intel5500", शून्य,
							   i5500_temp_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा pci_driver i5500_temp_driver = अणु
	.name = "i5500_temp",
	.id_table = i5500_temp_ids,
	.probe = i5500_temp_probe,
पूर्ण;

module_pci_driver(i5500_temp_driver);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("Intel 5500/5520/X58 chipset thermal sensor driver");
MODULE_LICENSE("GPL");
