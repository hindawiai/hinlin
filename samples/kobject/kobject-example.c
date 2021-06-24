<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sample kobject implementation
 *
 * Copyright (C) 2004-2007 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2007 Novell Inc.
 */
#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

/*
 * This module shows how to create a simple subdirectory in sysfs called
 * /sys/kernel/kobject-example  In that directory, 3 files are created:
 * "foo", "baz", and "bar".  If an पूर्णांकeger is written to these files, it can be
 * later पढ़ो out of it.
 */

अटल पूर्णांक foo;
अटल पूर्णांक baz;
अटल पूर्णांक bar;

/*
 * The "foo" file where a अटल variable is पढ़ो from and written to.
 */
अटल sमाप_प्रकार foo_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", foo);
पूर्ण

अटल sमाप_प्रकार foo_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 10, &foo);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

/* Sysfs attributes cannot be world-writable. */
अटल काष्ठा kobj_attribute foo_attribute =
	__ATTR(foo, 0664, foo_show, foo_store);

/*
 * More complex function where we determine which variable is being accessed by
 * looking at the attribute क्रम the "baz" and "bar" files.
 */
अटल sमाप_प्रकार b_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		      अक्षर *buf)
अणु
	पूर्णांक var;

	अगर (म_भेद(attr->attr.name, "baz") == 0)
		var = baz;
	अन्यथा
		var = bar;
	वापस प्र_लिखो(buf, "%d\n", var);
पूर्ण

अटल sमाप_प्रकार b_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक var, ret;

	ret = kstrtoपूर्णांक(buf, 10, &var);
	अगर (ret < 0)
		वापस ret;

	अगर (म_भेद(attr->attr.name, "baz") == 0)
		baz = var;
	अन्यथा
		bar = var;
	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute baz_attribute =
	__ATTR(baz, 0664, b_show, b_store);
अटल काष्ठा kobj_attribute bar_attribute =
	__ATTR(bar, 0664, b_show, b_store);


/*
 * Create a group of attributes so that we can create and destroy them all
 * at once.
 */
अटल काष्ठा attribute *attrs[] = अणु
	&foo_attribute.attr,
	&baz_attribute.attr,
	&bar_attribute.attr,
	शून्य,	/* need to शून्य terminate the list of attributes */
पूर्ण;

/*
 * An unnamed attribute group will put all of the attributes directly in
 * the kobject directory.  If we specअगरy a name, a subdirectory will be
 * created क्रम the attributes with the directory being the name of the
 * attribute group.
 */
अटल काष्ठा attribute_group attr_group = अणु
	.attrs = attrs,
पूर्ण;

अटल काष्ठा kobject *example_kobj;

अटल पूर्णांक __init example_init(व्योम)
अणु
	पूर्णांक retval;

	/*
	 * Create a simple kobject with the name of "kobject_example",
	 * located under /sys/kernel/
	 *
	 * As this is a simple directory, no uevent will be sent to
	 * userspace.  That is why this function should not be used क्रम
	 * any type of dynamic kobjects, where the name and number are
	 * not known ahead of समय.
	 */
	example_kobj = kobject_create_and_add("kobject_example", kernel_kobj);
	अगर (!example_kobj)
		वापस -ENOMEM;

	/* Create the files associated with this kobject */
	retval = sysfs_create_group(example_kobj, &attr_group);
	अगर (retval)
		kobject_put(example_kobj);

	वापस retval;
पूर्ण

अटल व्योम __निकास example_निकास(व्योम)
अणु
	kobject_put(example_kobj);
पूर्ण

module_init(example_init);
module_निकास(example_निकास);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Greg Kroah-Hartman <greg@kroah.com>");
