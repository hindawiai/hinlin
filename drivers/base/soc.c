<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) ST-Ericsson SA 2011
 *
 * Author: Lee Jones <lee.jones@linaro.org> क्रम ST-Ericsson.
 */

#समावेश <linux/sysfs.h>
#समावेश <linux/init.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/err.h>
#समावेश <linux/glob.h>

अटल DEFINE_IDA(soc_ida);

/* Prototype to allow declarations of DEVICE_ATTR(<foo>) beक्रमe soc_info_show */
अटल sमाप_प्रकार soc_info_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf);

काष्ठा soc_device अणु
	काष्ठा device dev;
	काष्ठा soc_device_attribute *attr;
	पूर्णांक soc_dev_num;
पूर्ण;

अटल काष्ठा bus_type soc_bus_type = अणु
	.name  = "soc",
पूर्ण;

अटल DEVICE_ATTR(machine,		0444, soc_info_show,  शून्य);
अटल DEVICE_ATTR(family,		0444, soc_info_show,  शून्य);
अटल DEVICE_ATTR(serial_number,	0444, soc_info_show,  शून्य);
अटल DEVICE_ATTR(soc_id,		0444, soc_info_show,  शून्य);
अटल DEVICE_ATTR(revision,		0444, soc_info_show,  शून्य);

काष्ठा device *soc_device_to_device(काष्ठा soc_device *soc_dev)
अणु
	वापस &soc_dev->dev;
पूर्ण

अटल umode_t soc_attribute_mode(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा soc_device *soc_dev = container_of(dev, काष्ठा soc_device, dev);

	अगर ((attr == &dev_attr_machine.attr) && soc_dev->attr->machine)
		वापस attr->mode;
	अगर ((attr == &dev_attr_family.attr) && soc_dev->attr->family)
		वापस attr->mode;
	अगर ((attr == &dev_attr_revision.attr) && soc_dev->attr->revision)
		वापस attr->mode;
	अगर ((attr == &dev_attr_serial_number.attr) && soc_dev->attr->serial_number)
		वापस attr->mode;
	अगर ((attr == &dev_attr_soc_id.attr) && soc_dev->attr->soc_id)
		वापस attr->mode;

	/* Unknown or unfilled attribute */
	वापस 0;
पूर्ण

अटल sमाप_प्रकार soc_info_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा soc_device *soc_dev = container_of(dev, काष्ठा soc_device, dev);
	स्थिर अक्षर *output;

	अगर (attr == &dev_attr_machine)
		output = soc_dev->attr->machine;
	अन्यथा अगर (attr == &dev_attr_family)
		output = soc_dev->attr->family;
	अन्यथा अगर (attr == &dev_attr_revision)
		output = soc_dev->attr->revision;
	अन्यथा अगर (attr == &dev_attr_serial_number)
		output = soc_dev->attr->serial_number;
	अन्यथा अगर (attr == &dev_attr_soc_id)
		output = soc_dev->attr->soc_id;
	अन्यथा
		वापस -EINVAL;

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण

अटल काष्ठा attribute *soc_attr[] = अणु
	&dev_attr_machine.attr,
	&dev_attr_family.attr,
	&dev_attr_serial_number.attr,
	&dev_attr_soc_id.attr,
	&dev_attr_revision.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group soc_attr_group = अणु
	.attrs = soc_attr,
	.is_visible = soc_attribute_mode,
पूर्ण;

अटल व्योम soc_release(काष्ठा device *dev)
अणु
	काष्ठा soc_device *soc_dev = container_of(dev, काष्ठा soc_device, dev);

	ida_simple_हटाओ(&soc_ida, soc_dev->soc_dev_num);
	kमुक्त(soc_dev->dev.groups);
	kमुक्त(soc_dev);
पूर्ण

अटल काष्ठा soc_device_attribute *early_soc_dev_attr;

काष्ठा soc_device *soc_device_रेजिस्टर(काष्ठा soc_device_attribute *soc_dev_attr)
अणु
	काष्ठा soc_device *soc_dev;
	स्थिर काष्ठा attribute_group **soc_attr_groups;
	पूर्णांक ret;

	अगर (!soc_bus_type.p) अणु
		अगर (early_soc_dev_attr)
			वापस ERR_PTR(-EBUSY);
		early_soc_dev_attr = soc_dev_attr;
		वापस शून्य;
	पूर्ण

	soc_dev = kzalloc(माप(*soc_dev), GFP_KERNEL);
	अगर (!soc_dev) अणु
		ret = -ENOMEM;
		जाओ out1;
	पूर्ण

	soc_attr_groups = kसुस्मृति(3, माप(*soc_attr_groups), GFP_KERNEL);
	अगर (!soc_attr_groups) अणु
		ret = -ENOMEM;
		जाओ out2;
	पूर्ण
	soc_attr_groups[0] = &soc_attr_group;
	soc_attr_groups[1] = soc_dev_attr->custom_attr_group;

	/* Fetch a unique (reclaimable) SOC ID. */
	ret = ida_simple_get(&soc_ida, 0, 0, GFP_KERNEL);
	अगर (ret < 0)
		जाओ out3;
	soc_dev->soc_dev_num = ret;

	soc_dev->attr = soc_dev_attr;
	soc_dev->dev.bus = &soc_bus_type;
	soc_dev->dev.groups = soc_attr_groups;
	soc_dev->dev.release = soc_release;

	dev_set_name(&soc_dev->dev, "soc%d", soc_dev->soc_dev_num);

	ret = device_रेजिस्टर(&soc_dev->dev);
	अगर (ret) अणु
		put_device(&soc_dev->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस soc_dev;

out3:
	kमुक्त(soc_attr_groups);
out2:
	kमुक्त(soc_dev);
out1:
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(soc_device_रेजिस्टर);

/* Ensure soc_dev->attr is मुक्तd after calling soc_device_unरेजिस्टर. */
व्योम soc_device_unरेजिस्टर(काष्ठा soc_device *soc_dev)
अणु
	device_unरेजिस्टर(&soc_dev->dev);
	early_soc_dev_attr = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(soc_device_unरेजिस्टर);

अटल पूर्णांक __init soc_bus_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&soc_bus_type);
	अगर (ret)
		वापस ret;

	अगर (early_soc_dev_attr)
		वापस PTR_ERR(soc_device_रेजिस्टर(early_soc_dev_attr));

	वापस 0;
पूर्ण
core_initcall(soc_bus_रेजिस्टर);

अटल पूर्णांक soc_device_match_attr(स्थिर काष्ठा soc_device_attribute *attr,
				 स्थिर काष्ठा soc_device_attribute *match)
अणु
	अगर (match->machine &&
	    (!attr->machine || !glob_match(match->machine, attr->machine)))
		वापस 0;

	अगर (match->family &&
	    (!attr->family || !glob_match(match->family, attr->family)))
		वापस 0;

	अगर (match->revision &&
	    (!attr->revision || !glob_match(match->revision, attr->revision)))
		वापस 0;

	अगर (match->soc_id &&
	    (!attr->soc_id || !glob_match(match->soc_id, attr->soc_id)))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक soc_device_match_one(काष्ठा device *dev, व्योम *arg)
अणु
	काष्ठा soc_device *soc_dev = container_of(dev, काष्ठा soc_device, dev);

	वापस soc_device_match_attr(soc_dev->attr, arg);
पूर्ण

/*
 * soc_device_match - identअगरy the SoC in the machine
 * @matches: zero-terminated array of possible matches
 *
 * वापसs the first matching entry of the argument array, or शून्य
 * अगर none of them match.
 *
 * This function is meant as a helper in place of of_match_node()
 * in हालs where either no device tree is available or the inक्रमmation
 * in a device node is insufficient to identअगरy a particular variant
 * by its compatible strings or other properties. For new devices,
 * the DT binding should always provide unique compatible strings
 * that allow the use of of_match_node() instead.
 *
 * The calling function can use the .data entry of the
 * soc_device_attribute to pass a काष्ठाure or function poपूर्णांकer क्रम
 * each entry.
 */
स्थिर काष्ठा soc_device_attribute *soc_device_match(
	स्थिर काष्ठा soc_device_attribute *matches)
अणु
	पूर्णांक ret = 0;

	अगर (!matches)
		वापस शून्य;

	जबतक (!ret) अणु
		अगर (!(matches->machine || matches->family ||
		      matches->revision || matches->soc_id))
			अवरोध;
		ret = bus_क्रम_each_dev(&soc_bus_type, शून्य, (व्योम *)matches,
				       soc_device_match_one);
		अगर (ret < 0 && early_soc_dev_attr)
			ret = soc_device_match_attr(early_soc_dev_attr,
						    matches);
		अगर (ret < 0)
			वापस शून्य;
		अगर (!ret)
			matches++;
		अन्यथा
			वापस matches;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(soc_device_match);
