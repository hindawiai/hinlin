<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A hwmon driver क्रम the Intel 5000 series chipset FB-DIMM AMB
 * temperature sensors
 * Copyright (C) 2007 IBM
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/log2.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा DRVNAME "i5k_amb"

#घोषणा I5K_REG_AMB_BASE_ADDR		0x48
#घोषणा I5K_REG_AMB_LEN_ADDR		0x50
#घोषणा I5K_REG_CHAN0_PRESENCE_ADDR	0x64
#घोषणा I5K_REG_CHAN1_PRESENCE_ADDR	0x66

#घोषणा AMB_REG_TEMP_MIN_ADDR		0x80
#घोषणा AMB_REG_TEMP_MID_ADDR		0x81
#घोषणा AMB_REG_TEMP_MAX_ADDR		0x82
#घोषणा AMB_REG_TEMP_STATUS_ADDR	0x84
#घोषणा AMB_REG_TEMP_ADDR		0x85

#घोषणा AMB_CONFIG_SIZE			2048
#घोषणा AMB_FUNC_3_OFFSET		768

अटल अचिन्हित दीर्घ amb_reg_temp_status(अचिन्हित पूर्णांक amb)
अणु
	वापस AMB_FUNC_3_OFFSET + AMB_REG_TEMP_STATUS_ADDR +
	       AMB_CONFIG_SIZE * amb;
पूर्ण

अटल अचिन्हित दीर्घ amb_reg_temp_min(अचिन्हित पूर्णांक amb)
अणु
	वापस AMB_FUNC_3_OFFSET + AMB_REG_TEMP_MIN_ADDR +
	       AMB_CONFIG_SIZE * amb;
पूर्ण

अटल अचिन्हित दीर्घ amb_reg_temp_mid(अचिन्हित पूर्णांक amb)
अणु
	वापस AMB_FUNC_3_OFFSET + AMB_REG_TEMP_MID_ADDR +
	       AMB_CONFIG_SIZE * amb;
पूर्ण

अटल अचिन्हित दीर्घ amb_reg_temp_max(अचिन्हित पूर्णांक amb)
अणु
	वापस AMB_FUNC_3_OFFSET + AMB_REG_TEMP_MAX_ADDR +
	       AMB_CONFIG_SIZE * amb;
पूर्ण

अटल अचिन्हित दीर्घ amb_reg_temp(अचिन्हित पूर्णांक amb)
अणु
	वापस AMB_FUNC_3_OFFSET + AMB_REG_TEMP_ADDR +
	       AMB_CONFIG_SIZE * amb;
पूर्ण

#घोषणा MAX_MEM_CHANNELS		4
#घोषणा MAX_AMBS_PER_CHANNEL		16
#घोषणा MAX_AMBS			(MAX_MEM_CHANNELS * \
					 MAX_AMBS_PER_CHANNEL)
#घोषणा CHANNEL_SHIFT			4
#घोषणा DIMM_MASK			0xF
/*
 * Ugly hack: For some reason the highest bit is set अगर there
 * are _any_ DIMMs in the channel.  Attempting to पढ़ो from
 * this "high-order" AMB results in a memory bus error, so
 * क्रम now we'll just ignore that top bit, even though that
 * might prevent us from seeing the 16th DIMM in the channel.
 */
#घोषणा REAL_MAX_AMBS_PER_CHANNEL	15
#घोषणा KNOBS_PER_AMB			6

अटल अचिन्हित दीर्घ amb_num_from_reg(अचिन्हित पूर्णांक byte_num, अचिन्हित पूर्णांक bit)
अणु
	वापस byte_num * MAX_AMBS_PER_CHANNEL + bit;
पूर्ण

#घोषणा AMB_SYSFS_NAME_LEN		16
काष्ठा i5k_device_attribute अणु
	काष्ठा sensor_device_attribute s_attr;
	अक्षर name[AMB_SYSFS_NAME_LEN];
पूर्ण;

काष्ठा i5k_amb_data अणु
	काष्ठा device *hwmon_dev;

	अचिन्हित दीर्घ amb_base;
	अचिन्हित दीर्घ amb_len;
	u16 amb_present[MAX_MEM_CHANNELS];
	व्योम __iomem *amb_mmio;
	काष्ठा i5k_device_attribute *attrs;
	अचिन्हित पूर्णांक num_attrs;
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", DRVNAME);
पूर्ण


अटल DEVICE_ATTR_RO(name);

अटल काष्ठा platक्रमm_device *amb_pdev;

अटल u8 amb_पढ़ो_byte(काष्ठा i5k_amb_data *data, अचिन्हित दीर्घ offset)
अणु
	वापस ioपढ़ो8(data->amb_mmio + offset);
पूर्ण

अटल व्योम amb_ग_लिखो_byte(काष्ठा i5k_amb_data *data, अचिन्हित दीर्घ offset,
			   u8 val)
अणु
	ioग_लिखो8(val, data->amb_mmio + offset);
पूर्ण

अटल sमाप_प्रकार show_amb_alarm(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा i5k_amb_data *data = dev_get_drvdata(dev);

	अगर (!(amb_पढ़ो_byte(data, amb_reg_temp_status(attr->index)) & 0x20) &&
	     (amb_पढ़ो_byte(data, amb_reg_temp_status(attr->index)) & 0x8))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार store_amb_min(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा i5k_amb_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ temp;
	पूर्णांक ret = kम_से_अदीर्घ(buf, 10, &temp);
	अगर (ret < 0)
		वापस ret;

	temp = temp / 500;
	अगर (temp > 255)
		temp = 255;

	amb_ग_लिखो_byte(data, amb_reg_temp_min(attr->index), temp);
	वापस count;
पूर्ण

अटल sमाप_प्रकार store_amb_mid(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा i5k_amb_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ temp;
	पूर्णांक ret = kम_से_अदीर्घ(buf, 10, &temp);
	अगर (ret < 0)
		वापस ret;

	temp = temp / 500;
	अगर (temp > 255)
		temp = 255;

	amb_ग_लिखो_byte(data, amb_reg_temp_mid(attr->index), temp);
	वापस count;
पूर्ण

अटल sमाप_प्रकार store_amb_max(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा i5k_amb_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ temp;
	पूर्णांक ret = kम_से_अदीर्घ(buf, 10, &temp);
	अगर (ret < 0)
		वापस ret;

	temp = temp / 500;
	अगर (temp > 255)
		temp = 255;

	amb_ग_लिखो_byte(data, amb_reg_temp_max(attr->index), temp);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_amb_min(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा i5k_amb_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n",
		500 * amb_पढ़ो_byte(data, amb_reg_temp_min(attr->index)));
पूर्ण

अटल sमाप_प्रकार show_amb_mid(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा i5k_amb_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n",
		500 * amb_पढ़ो_byte(data, amb_reg_temp_mid(attr->index)));
पूर्ण

अटल sमाप_प्रकार show_amb_max(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा i5k_amb_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n",
		500 * amb_पढ़ो_byte(data, amb_reg_temp_max(attr->index)));
पूर्ण

अटल sमाप_प्रकार show_amb_temp(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा i5k_amb_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n",
		500 * amb_पढ़ो_byte(data, amb_reg_temp(attr->index)));
पूर्ण

अटल sमाप_प्रकार show_label(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr,
			  अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	वापस प्र_लिखो(buf, "Ch. %d DIMM %d\n", attr->index >> CHANNEL_SHIFT,
		       attr->index & DIMM_MASK);
पूर्ण

अटल पूर्णांक i5k_amb_hwmon_init(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, j, k, d = 0;
	u16 c;
	पूर्णांक res = 0;
	पूर्णांक num_ambs = 0;
	काष्ठा i5k_amb_data *data = platक्रमm_get_drvdata(pdev);

	/* Count the number of AMBs found */
	/* ignore the high-order bit, see "Ugly hack" comment above */
	क्रम (i = 0; i < MAX_MEM_CHANNELS; i++)
		num_ambs += hweight16(data->amb_present[i] & 0x7fff);

	/* Set up sysfs stuff */
	data->attrs = kzalloc(array3_size(num_ambs, KNOBS_PER_AMB,
					  माप(*data->attrs)),
			      GFP_KERNEL);
	अगर (!data->attrs)
		वापस -ENOMEM;
	data->num_attrs = 0;

	क्रम (i = 0; i < MAX_MEM_CHANNELS; i++) अणु
		c = data->amb_present[i];
		क्रम (j = 0; j < REAL_MAX_AMBS_PER_CHANNEL; j++, c >>= 1) अणु
			काष्ठा i5k_device_attribute *iattr;

			k = amb_num_from_reg(i, j);
			अगर (!(c & 0x1))
				जारी;
			d++;

			/* sysfs label */
			iattr = data->attrs + data->num_attrs;
			snम_लिखो(iattr->name, AMB_SYSFS_NAME_LEN,
				 "temp%d_label", d);
			iattr->s_attr.dev_attr.attr.name = iattr->name;
			iattr->s_attr.dev_attr.attr.mode = 0444;
			iattr->s_attr.dev_attr.show = show_label;
			iattr->s_attr.index = k;
			sysfs_attr_init(&iattr->s_attr.dev_attr.attr);
			res = device_create_file(&pdev->dev,
						 &iattr->s_attr.dev_attr);
			अगर (res)
				जाओ निकास_हटाओ;
			data->num_attrs++;

			/* Temperature sysfs knob */
			iattr = data->attrs + data->num_attrs;
			snम_लिखो(iattr->name, AMB_SYSFS_NAME_LEN,
				 "temp%d_input", d);
			iattr->s_attr.dev_attr.attr.name = iattr->name;
			iattr->s_attr.dev_attr.attr.mode = 0444;
			iattr->s_attr.dev_attr.show = show_amb_temp;
			iattr->s_attr.index = k;
			sysfs_attr_init(&iattr->s_attr.dev_attr.attr);
			res = device_create_file(&pdev->dev,
						 &iattr->s_attr.dev_attr);
			अगर (res)
				जाओ निकास_हटाओ;
			data->num_attrs++;

			/* Temperature min sysfs knob */
			iattr = data->attrs + data->num_attrs;
			snम_लिखो(iattr->name, AMB_SYSFS_NAME_LEN,
				 "temp%d_min", d);
			iattr->s_attr.dev_attr.attr.name = iattr->name;
			iattr->s_attr.dev_attr.attr.mode = 0644;
			iattr->s_attr.dev_attr.show = show_amb_min;
			iattr->s_attr.dev_attr.store = store_amb_min;
			iattr->s_attr.index = k;
			sysfs_attr_init(&iattr->s_attr.dev_attr.attr);
			res = device_create_file(&pdev->dev,
						 &iattr->s_attr.dev_attr);
			अगर (res)
				जाओ निकास_हटाओ;
			data->num_attrs++;

			/* Temperature mid sysfs knob */
			iattr = data->attrs + data->num_attrs;
			snम_लिखो(iattr->name, AMB_SYSFS_NAME_LEN,
				 "temp%d_mid", d);
			iattr->s_attr.dev_attr.attr.name = iattr->name;
			iattr->s_attr.dev_attr.attr.mode = 0644;
			iattr->s_attr.dev_attr.show = show_amb_mid;
			iattr->s_attr.dev_attr.store = store_amb_mid;
			iattr->s_attr.index = k;
			sysfs_attr_init(&iattr->s_attr.dev_attr.attr);
			res = device_create_file(&pdev->dev,
						 &iattr->s_attr.dev_attr);
			अगर (res)
				जाओ निकास_हटाओ;
			data->num_attrs++;

			/* Temperature max sysfs knob */
			iattr = data->attrs + data->num_attrs;
			snम_लिखो(iattr->name, AMB_SYSFS_NAME_LEN,
				 "temp%d_max", d);
			iattr->s_attr.dev_attr.attr.name = iattr->name;
			iattr->s_attr.dev_attr.attr.mode = 0644;
			iattr->s_attr.dev_attr.show = show_amb_max;
			iattr->s_attr.dev_attr.store = store_amb_max;
			iattr->s_attr.index = k;
			sysfs_attr_init(&iattr->s_attr.dev_attr.attr);
			res = device_create_file(&pdev->dev,
						 &iattr->s_attr.dev_attr);
			अगर (res)
				जाओ निकास_हटाओ;
			data->num_attrs++;

			/* Temperature alarm sysfs knob */
			iattr = data->attrs + data->num_attrs;
			snम_लिखो(iattr->name, AMB_SYSFS_NAME_LEN,
				 "temp%d_alarm", d);
			iattr->s_attr.dev_attr.attr.name = iattr->name;
			iattr->s_attr.dev_attr.attr.mode = 0444;
			iattr->s_attr.dev_attr.show = show_amb_alarm;
			iattr->s_attr.index = k;
			sysfs_attr_init(&iattr->s_attr.dev_attr.attr);
			res = device_create_file(&pdev->dev,
						 &iattr->s_attr.dev_attr);
			अगर (res)
				जाओ निकास_हटाओ;
			data->num_attrs++;
		पूर्ण
	पूर्ण

	res = device_create_file(&pdev->dev, &dev_attr_name);
	अगर (res)
		जाओ निकास_हटाओ;

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		res = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ;
	पूर्ण

	वापस res;

निकास_हटाओ:
	device_हटाओ_file(&pdev->dev, &dev_attr_name);
	क्रम (i = 0; i < data->num_attrs; i++)
		device_हटाओ_file(&pdev->dev, &data->attrs[i].s_attr.dev_attr);
	kमुक्त(data->attrs);

	वापस res;
पूर्ण

अटल पूर्णांक i5k_amb_add(व्योम)
अणु
	पूर्णांक res;

	/* only ever going to be one of these */
	amb_pdev = platक्रमm_device_alloc(DRVNAME, 0);
	अगर (!amb_pdev)
		वापस -ENOMEM;

	res = platक्रमm_device_add(amb_pdev);
	अगर (res)
		जाओ err;
	वापस 0;

err:
	platक्रमm_device_put(amb_pdev);
	वापस res;
पूर्ण

अटल पूर्णांक i5k_find_amb_रेजिस्टरs(काष्ठा i5k_amb_data *data,
					    अचिन्हित दीर्घ devid)
अणु
	काष्ठा pci_dev *pcidev;
	u32 val32;
	पूर्णांक res = -ENODEV;

	/* Find AMB रेजिस्टर memory space */
	pcidev = pci_get_device(PCI_VENDOR_ID_INTEL,
				devid,
				शून्य);
	अगर (!pcidev)
		वापस -ENODEV;

	pci_पढ़ो_config_dword(pcidev, I5K_REG_AMB_BASE_ADDR, &val32);
	अगर (val32 == (u32)~0)
		जाओ out;
	data->amb_base = val32;

	pci_पढ़ो_config_dword(pcidev, I5K_REG_AMB_LEN_ADDR, &val32);
	अगर (val32 == (u32)~0)
		जाओ out;
	data->amb_len = val32;

	/* Is it big enough? */
	अगर (data->amb_len < AMB_CONFIG_SIZE * MAX_AMBS) अणु
		dev_err(&pcidev->dev, "AMB region too small!\n");
		जाओ out;
	पूर्ण

	res = 0;
out:
	pci_dev_put(pcidev);
	वापस res;
पूर्ण

अटल पूर्णांक i5k_channel_probe(u16 *amb_present, अचिन्हित दीर्घ dev_id)
अणु
	काष्ठा pci_dev *pcidev;
	u16 val16;
	पूर्णांक res = -ENODEV;

	/* Copy the DIMM presence map क्रम these two channels */
	pcidev = pci_get_device(PCI_VENDOR_ID_INTEL, dev_id, शून्य);
	अगर (!pcidev)
		वापस -ENODEV;

	pci_पढ़ो_config_word(pcidev, I5K_REG_CHAN0_PRESENCE_ADDR, &val16);
	अगर (val16 == (u16)~0)
		जाओ out;
	amb_present[0] = val16;

	pci_पढ़ो_config_word(pcidev, I5K_REG_CHAN1_PRESENCE_ADDR, &val16);
	अगर (val16 == (u16)~0)
		जाओ out;
	amb_present[1] = val16;

	res = 0;

out:
	pci_dev_put(pcidev);
	वापस res;
पूर्ण

अटल काष्ठा अणु
	अचिन्हित दीर्घ err;
	अचिन्हित दीर्घ fbd0;
पूर्ण chipset_ids[]  = अणु
	अणु PCI_DEVICE_ID_INTEL_5000_ERR, PCI_DEVICE_ID_INTEL_5000_FBD0 पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_5400_ERR, PCI_DEVICE_ID_INTEL_5400_FBD0 पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

#अगर_घोषित MODULE
अटल स्थिर काष्ठा pci_device_id i5k_amb_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_5000_ERR) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_5400_ERR) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, i5k_amb_ids);
#पूर्ण_अगर

अटल पूर्णांक i5k_amb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i5k_amb_data *data;
	काष्ठा resource *reso;
	पूर्णांक i, res;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* Figure out where the AMB रेजिस्टरs live */
	i = 0;
	करो अणु
		res = i5k_find_amb_रेजिस्टरs(data, chipset_ids[i].err);
		अगर (res == 0)
			अवरोध;
		i++;
	पूर्ण जबतक (chipset_ids[i].err);

	अगर (res)
		जाओ err;

	/* Copy the DIMM presence map क्रम the first two channels */
	res = i5k_channel_probe(&data->amb_present[0], chipset_ids[i].fbd0);
	अगर (res)
		जाओ err;

	/* Copy the DIMM presence map क्रम the optional second two channels */
	i5k_channel_probe(&data->amb_present[2], chipset_ids[i].fbd0 + 1);

	/* Set up resource regions */
	reso = request_mem_region(data->amb_base, data->amb_len, DRVNAME);
	अगर (!reso) अणु
		res = -EBUSY;
		जाओ err;
	पूर्ण

	data->amb_mmio = ioremap(data->amb_base, data->amb_len);
	अगर (!data->amb_mmio) अणु
		res = -EBUSY;
		जाओ err_map_failed;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	res = i5k_amb_hwmon_init(pdev);
	अगर (res)
		जाओ err_init_failed;

	वापस res;

err_init_failed:
	iounmap(data->amb_mmio);
err_map_failed:
	release_mem_region(data->amb_base, data->amb_len);
err:
	kमुक्त(data);
	वापस res;
पूर्ण

अटल पूर्णांक i5k_amb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा i5k_amb_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	device_हटाओ_file(&pdev->dev, &dev_attr_name);
	क्रम (i = 0; i < data->num_attrs; i++)
		device_हटाओ_file(&pdev->dev, &data->attrs[i].s_attr.dev_attr);
	kमुक्त(data->attrs);
	iounmap(data->amb_mmio);
	release_mem_region(data->amb_base, data->amb_len);
	kमुक्त(data);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver i5k_amb_driver = अणु
	.driver = अणु
		.name = DRVNAME,
	पूर्ण,
	.probe = i5k_amb_probe,
	.हटाओ = i5k_amb_हटाओ,
पूर्ण;

अटल पूर्णांक __init i5k_amb_init(व्योम)
अणु
	पूर्णांक res;

	res = platक्रमm_driver_रेजिस्टर(&i5k_amb_driver);
	अगर (res)
		वापस res;

	res = i5k_amb_add();
	अगर (res)
		platक्रमm_driver_unरेजिस्टर(&i5k_amb_driver);

	वापस res;
पूर्ण

अटल व्योम __निकास i5k_amb_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(amb_pdev);
	platक्रमm_driver_unरेजिस्टर(&i5k_amb_driver);
पूर्ण

MODULE_AUTHOR("Darrick J. Wong <darrick.wong@oracle.com>");
MODULE_DESCRIPTION("Intel 5000 chipset FB-DIMM AMB temperature sensor");
MODULE_LICENSE("GPL");

module_init(i5k_amb_init);
module_निकास(i5k_amb_निकास);
