<शैली गुरु>
/*
 *  File Attributes क्रम Zorro Devices
 *
 *  Copyright (C) 2003 Geert Uytterhoeven
 *
 *  Loosely based on drivers/pci/pci-sysfs.c
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/zorro.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>

#समावेश <यंत्र/byteorder.h>

#समावेश "zorro.h"


/* show configuration fields */
#घोषणा zorro_config_attr(name, field, क्रमmat_string)			\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा zorro_dev *z;						\
									\
	z = to_zorro_dev(dev);						\
	वापस प्र_लिखो(buf, क्रमmat_string, z->field);			\
पूर्ण									\
अटल DEVICE_ATTR_RO(name);

zorro_config_attr(id, id, "0x%08x\n");
zorro_config_attr(type, rom.er_Type, "0x%02x\n");
zorro_config_attr(slotaddr, slotaddr, "0x%04x\n");
zorro_config_attr(slotsize, slotsize, "0x%04x\n");

अटल sमाप_प्रकार serial_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा zorro_dev *z;

	z = to_zorro_dev(dev);
	वापस प्र_लिखो(buf, "0x%08x\n", be32_to_cpu(z->rom.er_SerialNumber));
पूर्ण
अटल DEVICE_ATTR_RO(serial);

अटल sमाप_प्रकार resource_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा zorro_dev *z = to_zorro_dev(dev);

	वापस प्र_लिखो(buf, "0x%08lx 0x%08lx 0x%08lx\n",
		       (अचिन्हित दीर्घ)zorro_resource_start(z),
		       (अचिन्हित दीर्घ)zorro_resource_end(z),
		       zorro_resource_flags(z));
पूर्ण
अटल DEVICE_ATTR_RO(resource);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा zorro_dev *z = to_zorro_dev(dev);

	वापस प्र_लिखो(buf, ZORRO_DEVICE_MODALIAS_FMT "\n", z->id);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *zorro_device_attrs[] = अणु
	&dev_attr_id.attr,
	&dev_attr_type.attr,
	&dev_attr_serial.attr,
	&dev_attr_slotaddr.attr,
	&dev_attr_slotsize.attr,
	&dev_attr_resource.attr,
	&dev_attr_modalias.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार zorro_पढ़ो_config(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *bin_attr,
				 अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा zorro_dev *z = to_zorro_dev(kobj_to_dev(kobj));
	काष्ठा ConfigDev cd;

	/* Conकाष्ठा a ConfigDev */
	स_रखो(&cd, 0, माप(cd));
	cd.cd_Rom = z->rom;
	cd.cd_SlotAddr = cpu_to_be16(z->slotaddr);
	cd.cd_SlotSize = cpu_to_be16(z->slotsize);
	cd.cd_BoardAddr = cpu_to_be32(zorro_resource_start(z));
	cd.cd_BoardSize = cpu_to_be32(zorro_resource_len(z));

	वापस memory_पढ़ो_from_buffer(buf, count, &off, &cd, माप(cd));
पूर्ण

अटल काष्ठा bin_attribute zorro_config_attr = अणु
	.attr =	अणु
		.name = "config",
		.mode = S_IRUGO,
	पूर्ण,
	.size = माप(काष्ठा ConfigDev),
	.पढ़ो = zorro_पढ़ो_config,
पूर्ण;

अटल काष्ठा bin_attribute *zorro_device_bin_attrs[] = अणु
	&zorro_config_attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group zorro_device_attr_group = अणु
	.attrs		= zorro_device_attrs,
	.bin_attrs	= zorro_device_bin_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *zorro_device_attribute_groups[] = अणु
	&zorro_device_attr_group,
	शून्य
पूर्ण;
