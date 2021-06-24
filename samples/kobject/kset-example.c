<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sample kset and ktype implementation
 *
 * Copyright (C) 2004-2007 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2007 Novell Inc.
 */
#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

/*
 * This module shows how to create a kset in sysfs called
 * /sys/kernel/kset-example
 * Then tree kobjects are created and asचिन्हित to this kset, "foo", "baz",
 * and "bar".  In those kobjects, attributes of the same name are also
 * created and अगर an पूर्णांकeger is written to these files, it can be later
 * पढ़ो out of it.
 */


/*
 * This is our "object" that we will create a few of and रेजिस्टर them with
 * sysfs.
 */
काष्ठा foo_obj अणु
	काष्ठा kobject kobj;
	पूर्णांक foo;
	पूर्णांक baz;
	पूर्णांक bar;
पूर्ण;
#घोषणा to_foo_obj(x) container_of(x, काष्ठा foo_obj, kobj)

/* a custom attribute that works just क्रम a काष्ठा foo_obj. */
काष्ठा foo_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा foo_obj *foo, काष्ठा foo_attribute *attr, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा foo_obj *foo, काष्ठा foo_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;
#घोषणा to_foo_attr(x) container_of(x, काष्ठा foo_attribute, attr)

/*
 * The शेष show function that must be passed to sysfs.  This will be
 * called by sysfs क्रम whenever a show function is called by the user on a
 * sysfs file associated with the kobjects we have रेजिस्टरed.  We need to
 * transpose back from a "default" kobject to our custom काष्ठा foo_obj and
 * then call the show function क्रम that specअगरic object.
 */
अटल sमाप_प्रकार foo_attr_show(काष्ठा kobject *kobj,
			     काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा foo_attribute *attribute;
	काष्ठा foo_obj *foo;

	attribute = to_foo_attr(attr);
	foo = to_foo_obj(kobj);

	अगर (!attribute->show)
		वापस -EIO;

	वापस attribute->show(foo, attribute, buf);
पूर्ण

/*
 * Just like the शेष show function above, but this one is क्रम when the
 * sysfs "store" is requested (when a value is written to a file.)
 */
अटल sमाप_प्रकार foo_attr_store(काष्ठा kobject *kobj,
			      काष्ठा attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा foo_attribute *attribute;
	काष्ठा foo_obj *foo;

	attribute = to_foo_attr(attr);
	foo = to_foo_obj(kobj);

	अगर (!attribute->store)
		वापस -EIO;

	वापस attribute->store(foo, attribute, buf, len);
पूर्ण

/* Our custom sysfs_ops that we will associate with our ktype later on */
अटल स्थिर काष्ठा sysfs_ops foo_sysfs_ops = अणु
	.show = foo_attr_show,
	.store = foo_attr_store,
पूर्ण;

/*
 * The release function क्रम our object.  This is REQUIRED by the kernel to
 * have.  We मुक्त the memory held in our object here.
 *
 * NEVER try to get away with just a "blank" release function to try to be
 * smarter than the kernel.  Turns out, no one ever is...
 */
अटल व्योम foo_release(काष्ठा kobject *kobj)
अणु
	काष्ठा foo_obj *foo;

	foo = to_foo_obj(kobj);
	kमुक्त(foo);
पूर्ण

/*
 * The "foo" file where the .foo variable is पढ़ो from and written to.
 */
अटल sमाप_प्रकार foo_show(काष्ठा foo_obj *foo_obj, काष्ठा foo_attribute *attr,
			अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", foo_obj->foo);
पूर्ण

अटल sमाप_प्रकार foo_store(काष्ठा foo_obj *foo_obj, काष्ठा foo_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 10, &foo_obj->foo);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

/* Sysfs attributes cannot be world-writable. */
अटल काष्ठा foo_attribute foo_attribute =
	__ATTR(foo, 0664, foo_show, foo_store);

/*
 * More complex function where we determine which variable is being accessed by
 * looking at the attribute क्रम the "baz" and "bar" files.
 */
अटल sमाप_प्रकार b_show(काष्ठा foo_obj *foo_obj, काष्ठा foo_attribute *attr,
		      अक्षर *buf)
अणु
	पूर्णांक var;

	अगर (म_भेद(attr->attr.name, "baz") == 0)
		var = foo_obj->baz;
	अन्यथा
		var = foo_obj->bar;
	वापस प्र_लिखो(buf, "%d\n", var);
पूर्ण

अटल sमाप_प्रकार b_store(काष्ठा foo_obj *foo_obj, काष्ठा foo_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक var, ret;

	ret = kstrtoपूर्णांक(buf, 10, &var);
	अगर (ret < 0)
		वापस ret;

	अगर (म_भेद(attr->attr.name, "baz") == 0)
		foo_obj->baz = var;
	अन्यथा
		foo_obj->bar = var;
	वापस count;
पूर्ण

अटल काष्ठा foo_attribute baz_attribute =
	__ATTR(baz, 0664, b_show, b_store);
अटल काष्ठा foo_attribute bar_attribute =
	__ATTR(bar, 0664, b_show, b_store);

/*
 * Create a group of attributes so that we can create and destroy them all
 * at once.
 */
अटल काष्ठा attribute *foo_शेष_attrs[] = अणु
	&foo_attribute.attr,
	&baz_attribute.attr,
	&bar_attribute.attr,
	शून्य,	/* need to शून्य terminate the list of attributes */
पूर्ण;
ATTRIBUTE_GROUPS(foo_शेष);

/*
 * Our own ktype क्रम our kobjects.  Here we specअगरy our sysfs ops, the
 * release function, and the set of शेष attributes we want created
 * whenever a kobject of this type is रेजिस्टरed with the kernel.
 */
अटल काष्ठा kobj_type foo_ktype = अणु
	.sysfs_ops = &foo_sysfs_ops,
	.release = foo_release,
	.शेष_groups = foo_शेष_groups,
पूर्ण;

अटल काष्ठा kset *example_kset;
अटल काष्ठा foo_obj *foo_obj;
अटल काष्ठा foo_obj *bar_obj;
अटल काष्ठा foo_obj *baz_obj;

अटल काष्ठा foo_obj *create_foo_obj(स्थिर अक्षर *name)
अणु
	काष्ठा foo_obj *foo;
	पूर्णांक retval;

	/* allocate the memory क्रम the whole object */
	foo = kzalloc(माप(*foo), GFP_KERNEL);
	अगर (!foo)
		वापस शून्य;

	/*
	 * As we have a kset क्रम this kobject, we need to set it beक्रमe calling
	 * the kobject core.
	 */
	foo->kobj.kset = example_kset;

	/*
	 * Initialize and add the kobject to the kernel.  All the शेष files
	 * will be created here.  As we have alपढ़ोy specअगरied a kset क्रम this
	 * kobject, we करोn't have to set a parent क्रम the kobject, the kobject
	 * will be placed beneath that kset स्वतःmatically.
	 */
	retval = kobject_init_and_add(&foo->kobj, &foo_ktype, शून्य, "%s", name);
	अगर (retval) अणु
		kobject_put(&foo->kobj);
		वापस शून्य;
	पूर्ण

	/*
	 * We are always responsible क्रम sending the uevent that the kobject
	 * was added to the प्रणाली.
	 */
	kobject_uevent(&foo->kobj, KOBJ_ADD);

	वापस foo;
पूर्ण

अटल व्योम destroy_foo_obj(काष्ठा foo_obj *foo)
अणु
	kobject_put(&foo->kobj);
पूर्ण

अटल पूर्णांक __init example_init(व्योम)
अणु
	/*
	 * Create a kset with the name of "kset_example",
	 * located under /sys/kernel/
	 */
	example_kset = kset_create_and_add("kset_example", शून्य, kernel_kobj);
	अगर (!example_kset)
		वापस -ENOMEM;

	/*
	 * Create three objects and रेजिस्टर them with our kset
	 */
	foo_obj = create_foo_obj("foo");
	अगर (!foo_obj)
		जाओ foo_error;

	bar_obj = create_foo_obj("bar");
	अगर (!bar_obj)
		जाओ bar_error;

	baz_obj = create_foo_obj("baz");
	अगर (!baz_obj)
		जाओ baz_error;

	वापस 0;

baz_error:
	destroy_foo_obj(bar_obj);
bar_error:
	destroy_foo_obj(foo_obj);
foo_error:
	kset_unरेजिस्टर(example_kset);
	वापस -EINVAL;
पूर्ण

अटल व्योम __निकास example_निकास(व्योम)
अणु
	destroy_foo_obj(baz_obj);
	destroy_foo_obj(bar_obj);
	destroy_foo_obj(foo_obj);
	kset_unरेजिस्टर(example_kset);
पूर्ण

module_init(example_init);
module_निकास(example_निकास);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Greg Kroah-Hartman <greg@kroah.com>");
