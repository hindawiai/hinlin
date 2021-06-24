<शैली गुरु>
/*
 *  File Attributes क्रम DIO Devices
 *
 *  Copyright (C) 2004 Jochen Friedrich
 *
 *  Loosely based on drivers/pci/pci-sysfs.c and drivers/zorro/zorro-sysfs.c
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/dपन.स>
#समावेश <linux/स्थिति.स>

/* show configuration fields */

अटल sमाप_प्रकार dio_show_id(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dio_dev *d;

	d = to_dio_dev(dev);
	वापस प्र_लिखो(buf, "0x%02x\n", (d->id & 0xff));
पूर्ण
अटल DEVICE_ATTR(id, S_IRUGO, dio_show_id, शून्य);

अटल sमाप_प्रकार dio_show_ipl(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dio_dev *d;

	d = to_dio_dev(dev);
	वापस प्र_लिखो(buf, "0x%02x\n", d->ipl);
पूर्ण
अटल DEVICE_ATTR(ipl, S_IRUGO, dio_show_ipl, शून्य);

अटल sमाप_प्रकार dio_show_secid(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dio_dev *d;

	d = to_dio_dev(dev);
	वापस प्र_लिखो(buf, "0x%02x\n", ((d->id >> 8)& 0xff));
पूर्ण
अटल DEVICE_ATTR(secid, S_IRUGO, dio_show_secid, शून्य);

अटल sमाप_प्रकार dio_show_name(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dio_dev *d;

	d = to_dio_dev(dev);
	वापस प्र_लिखो(buf, "%s\n", d->name);
पूर्ण
अटल DEVICE_ATTR(name, S_IRUGO, dio_show_name, शून्य);

अटल sमाप_प्रकार dio_show_resource(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dio_dev *d = to_dio_dev(dev);

	वापस प्र_लिखो(buf, "0x%08lx 0x%08lx 0x%08lx\n",
		       (अचिन्हित दीर्घ)dio_resource_start(d),
		       (अचिन्हित दीर्घ)dio_resource_end(d),
		       dio_resource_flags(d));
पूर्ण
अटल DEVICE_ATTR(resource, S_IRUGO, dio_show_resource, शून्य);

पूर्णांक dio_create_sysfs_dev_files(काष्ठा dio_dev *d)
अणु
	काष्ठा device *dev = &d->dev;
	पूर्णांक error;

	/* current configuration's attributes */
	अगर ((error = device_create_file(dev, &dev_attr_id)) ||
	    (error = device_create_file(dev, &dev_attr_ipl)) ||
	    (error = device_create_file(dev, &dev_attr_secid)) ||
	    (error = device_create_file(dev, &dev_attr_name)) ||
	    (error = device_create_file(dev, &dev_attr_resource)))
		वापस error;

	वापस 0;
पूर्ण

