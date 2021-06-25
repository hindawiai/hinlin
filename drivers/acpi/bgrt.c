<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BGRT boot graphic support
 * Authors: Matthew Garrett, Josh Triplett <josh@joshtriplett.org>
 * Copyright 2012 Red Hat, Inc <mjg@redhat.com>
 * Copyright 2012 Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/efi-bgrt.h>

अटल व्योम *bgrt_image;
अटल काष्ठा kobject *bgrt_kobj;

अटल sमाप_प्रकार version_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", bgrt_tab.version);
पूर्ण
अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार status_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", bgrt_tab.status);
पूर्ण
अटल DEVICE_ATTR_RO(status);

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", bgrt_tab.image_type);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार xoffset_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", bgrt_tab.image_offset_x);
पूर्ण
अटल DEVICE_ATTR_RO(xoffset);

अटल sमाप_प्रकार yoffset_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", bgrt_tab.image_offset_y);
पूर्ण
अटल DEVICE_ATTR_RO(yoffset);

अटल sमाप_प्रकार image_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
	       काष्ठा bin_attribute *attr, अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	स_नकल(buf, attr->निजी + off, count);
	वापस count;
पूर्ण

अटल BIN_ATTR_RO(image, 0);	/* size माला_लो filled in later */

अटल काष्ठा attribute *bgrt_attributes[] = अणु
	&dev_attr_version.attr,
	&dev_attr_status.attr,
	&dev_attr_type.attr,
	&dev_attr_xoffset.attr,
	&dev_attr_yoffset.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *bgrt_bin_attributes[] = अणु
	&bin_attr_image,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bgrt_attribute_group = अणु
	.attrs = bgrt_attributes,
	.bin_attrs = bgrt_bin_attributes,
पूर्ण;

पूर्णांक __init acpi_parse_bgrt(काष्ठा acpi_table_header *table)
अणु
	efi_bgrt_init(table);
	वापस 0;
पूर्ण

अटल पूर्णांक __init bgrt_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!bgrt_tab.image_address)
		वापस -ENODEV;

	bgrt_image = memremap(bgrt_tab.image_address, bgrt_image_size,
			      MEMREMAP_WB);
	अगर (!bgrt_image) अणु
		pr_notice("Ignoring BGRT: failed to map image memory\n");
		वापस -ENOMEM;
	पूर्ण

	bin_attr_image.निजी = bgrt_image;
	bin_attr_image.size = bgrt_image_size;

	bgrt_kobj = kobject_create_and_add("bgrt", acpi_kobj);
	अगर (!bgrt_kobj) अणु
		ret = -EINVAL;
		जाओ out_memmap;
	पूर्ण

	ret = sysfs_create_group(bgrt_kobj, &bgrt_attribute_group);
	अगर (ret)
		जाओ out_kobject;

	वापस 0;

out_kobject:
	kobject_put(bgrt_kobj);
out_memmap:
	memunmap(bgrt_image);
	वापस ret;
पूर्ण
device_initcall(bgrt_init);
