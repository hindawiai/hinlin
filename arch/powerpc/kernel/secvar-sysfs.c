<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 IBM Corporation <nayna@linux.ibm.com>
 *
 * This code exposes secure variables to user via sysfs
 */

#घोषणा pr_fmt(fmt) "secvar-sysfs: "fmt

#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/माला.स>
#समावेश <linux/of.h>
#समावेश <यंत्र/secvar.h>

#घोषणा NAME_MAX_SIZE	   1024

अटल काष्ठा kobject *secvar_kobj;
अटल काष्ठा kset *secvar_kset;

अटल sमाप_प्रकार क्रमmat_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			   अक्षर *buf)
अणु
	sमाप_प्रकार rc = 0;
	काष्ठा device_node *node;
	स्थिर अक्षर *क्रमmat;

	node = of_find_compatible_node(शून्य, शून्य, "ibm,secvar-backend");
	अगर (!of_device_is_available(node))
		वापस -ENODEV;

	rc = of_property_पढ़ो_string(node, "format", &क्रमmat);
	अगर (rc)
		वापस rc;

	rc = प्र_लिखो(buf, "%s\n", क्रमmat);

	of_node_put(node);

	वापस rc;
पूर्ण


अटल sमाप_प्रकार size_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	uपूर्णांक64_t dsize;
	पूर्णांक rc;

	rc = secvar_ops->get(kobj->name, म_माप(kobj->name) + 1, शून्य, &dsize);
	अगर (rc) अणु
		pr_err("Error retrieving %s variable size %d\n", kobj->name,
		       rc);
		वापस rc;
	पूर्ण

	वापस प्र_लिखो(buf, "%llu\n", dsize);
पूर्ण

अटल sमाप_प्रकार data_पढ़ो(काष्ठा file *filep, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *attr, अक्षर *buf, loff_t off,
			 माप_प्रकार count)
अणु
	uपूर्णांक64_t dsize;
	अक्षर *data;
	पूर्णांक rc;

	rc = secvar_ops->get(kobj->name, म_माप(kobj->name) + 1, शून्य, &dsize);
	अगर (rc) अणु
		pr_err("Error getting %s variable size %d\n", kobj->name, rc);
		वापस rc;
	पूर्ण
	pr_debug("dsize is %llu\n", dsize);

	data = kzalloc(dsize, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	rc = secvar_ops->get(kobj->name, म_माप(kobj->name) + 1, data, &dsize);
	अगर (rc) अणु
		pr_err("Error getting %s variable %d\n", kobj->name, rc);
		जाओ data_fail;
	पूर्ण

	rc = memory_पढ़ो_from_buffer(buf, count, &off, data, dsize);

data_fail:
	kमुक्त(data);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार update_ग_लिखो(काष्ठा file *filep, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *attr, अक्षर *buf, loff_t off,
			    माप_प्रकार count)
अणु
	पूर्णांक rc;

	pr_debug("count is %ld\n", count);
	rc = secvar_ops->set(kobj->name, म_माप(kobj->name) + 1, buf, count);
	अगर (rc) अणु
		pr_err("Error setting the %s variable %d\n", kobj->name, rc);
		वापस rc;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute क्रमmat_attr = __ATTR_RO(क्रमmat);

अटल काष्ठा kobj_attribute size_attr = __ATTR_RO(size);

अटल काष्ठा bin_attribute data_attr = __BIN_ATTR_RO(data, 0);

अटल काष्ठा bin_attribute update_attr = __BIN_ATTR_WO(update, 0);

अटल काष्ठा bin_attribute *secvar_bin_attrs[] = अणु
	&data_attr,
	&update_attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *secvar_attrs[] = अणु
	&size_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group secvar_attr_group = अणु
	.attrs = secvar_attrs,
	.bin_attrs = secvar_bin_attrs,
पूर्ण;
__ATTRIBUTE_GROUPS(secvar_attr);

अटल काष्ठा kobj_type secvar_ktype = अणु
	.sysfs_ops	= &kobj_sysfs_ops,
	.शेष_groups = secvar_attr_groups,
पूर्ण;

अटल पूर्णांक update_kobj_size(व्योम)
अणु

	काष्ठा device_node *node;
	u64 varsize;
	पूर्णांक rc = 0;

	node = of_find_compatible_node(शून्य, शून्य, "ibm,secvar-backend");
	अगर (!of_device_is_available(node)) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	rc = of_property_पढ़ो_u64(node, "max-var-size", &varsize);
	अगर (rc)
		जाओ out;

	data_attr.size = varsize;
	update_attr.size = varsize;

out:
	of_node_put(node);

	वापस rc;
पूर्ण

अटल पूर्णांक secvar_sysfs_load(व्योम)
अणु
	अक्षर *name;
	uपूर्णांक64_t namesize = 0;
	काष्ठा kobject *kobj;
	पूर्णांक rc;

	name = kzalloc(NAME_MAX_SIZE, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	करो अणु
		rc = secvar_ops->get_next(name, &namesize, NAME_MAX_SIZE);
		अगर (rc) अणु
			अगर (rc != -ENOENT)
				pr_err("error getting secvar from firmware %d\n",
				       rc);
			अवरोध;
		पूर्ण

		kobj = kzalloc(माप(*kobj), GFP_KERNEL);
		अगर (!kobj) अणु
			rc = -ENOMEM;
			अवरोध;
		पूर्ण

		kobject_init(kobj, &secvar_ktype);

		rc = kobject_add(kobj, &secvar_kset->kobj, "%s", name);
		अगर (rc) अणु
			pr_warn("kobject_add error %d for attribute: %s\n", rc,
				name);
			kobject_put(kobj);
			kobj = शून्य;
		पूर्ण

		अगर (kobj)
			kobject_uevent(kobj, KOBJ_ADD);

	पूर्ण जबतक (!rc);

	kमुक्त(name);
	वापस rc;
पूर्ण

अटल पूर्णांक secvar_sysfs_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!secvar_ops) अणु
		pr_warn("secvar: failed to retrieve secvar operations.\n");
		वापस -ENODEV;
	पूर्ण

	secvar_kobj = kobject_create_and_add("secvar", firmware_kobj);
	अगर (!secvar_kobj) अणु
		pr_err("secvar: Failed to create firmware kobj\n");
		वापस -ENOMEM;
	पूर्ण

	rc = sysfs_create_file(secvar_kobj, &क्रमmat_attr.attr);
	अगर (rc) अणु
		kobject_put(secvar_kobj);
		वापस -ENOMEM;
	पूर्ण

	secvar_kset = kset_create_and_add("vars", शून्य, secvar_kobj);
	अगर (!secvar_kset) अणु
		pr_err("secvar: sysfs kobject registration failed.\n");
		kobject_put(secvar_kobj);
		वापस -ENOMEM;
	पूर्ण

	rc = update_kobj_size();
	अगर (rc) अणु
		pr_err("Cannot read the size of the attribute\n");
		वापस rc;
	पूर्ण

	secvar_sysfs_load();

	वापस 0;
पूर्ण

late_initcall(secvar_sysfs_init);
