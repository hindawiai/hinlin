<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * configfs_example_macros.c - This file is a demonstration module
 *      containing a number of configfs subप्रणालीs.  It uses the helper
 *      macros defined by configfs.h
 *
 * Based on sysfs:
 *      sysfs is Copyright (C) 2001, 2002, 2003 Patrick Mochel
 *
 * configfs Copyright (C) 2005 Oracle.  All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/configfs.h>

/*
 * 01-childless
 *
 * This first example is a childless subप्रणाली.  It cannot create
 * any config_items.  It just has attributes.
 *
 * Note that we are enclosing the configfs_subप्रणाली inside a container.
 * This is not necessary अगर a subप्रणाली has no attributes directly
 * on the subप्रणाली.  See the next example, 02-simple-children, क्रम
 * such a subप्रणाली.
 */

काष्ठा childless अणु
	काष्ठा configfs_subप्रणाली subsys;
	पूर्णांक showme;
	पूर्णांक storeme;
पूर्ण;

अटल अंतरभूत काष्ठा childless *to_childless(काष्ठा config_item *item)
अणु
	वापस container_of(to_configfs_subप्रणाली(to_config_group(item)),
			    काष्ठा childless, subsys);
पूर्ण

अटल sमाप_प्रकार childless_showme_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा childless *childless = to_childless(item);
	sमाप_प्रकार pos;

	pos = प्र_लिखो(page, "%d\n", childless->showme);
	childless->showme++;

	वापस pos;
पूर्ण

अटल sमाप_प्रकार childless_storeme_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", to_childless(item)->storeme);
पूर्ण

अटल sमाप_प्रकार childless_storeme_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा childless *childless = to_childless(item);
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(page, 10, &childless->storeme);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार childless_description_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page,
"[01-childless]\n"
"\n"
"The childless subsystem is the simplest possible subsystem in\n"
"configfs.  It does not support the creation of child config_items.\n"
"It only has a few attributes.  In fact, it isn't much different\n"
"than a directory in /proc.\n");
पूर्ण

CONFIGFS_ATTR_RO(childless_, showme);
CONFIGFS_ATTR(childless_, storeme);
CONFIGFS_ATTR_RO(childless_, description);

अटल काष्ठा configfs_attribute *childless_attrs[] = अणु
	&childless_attr_showme,
	&childless_attr_storeme,
	&childless_attr_description,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type childless_type = अणु
	.ct_attrs	= childless_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा childless childless_subsys = अणु
	.subsys = अणु
		.su_group = अणु
			.cg_item = अणु
				.ci_namebuf = "01-childless",
				.ci_type = &childless_type,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* ----------------------------------------------------------------- */

/*
 * 02-simple-children
 *
 * This example merely has a simple one-attribute child.  Note that
 * there is no extra attribute काष्ठाure, as the child's attribute is
 * known from the get-go.  Also, there is no container क्रम the
 * subप्रणाली, as it has no attributes of its own.
 */

काष्ठा simple_child अणु
	काष्ठा config_item item;
	पूर्णांक storeme;
पूर्ण;

अटल अंतरभूत काष्ठा simple_child *to_simple_child(काष्ठा config_item *item)
अणु
	वापस container_of(item, काष्ठा simple_child, item);
पूर्ण

अटल sमाप_प्रकार simple_child_storeme_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", to_simple_child(item)->storeme);
पूर्ण

अटल sमाप_प्रकार simple_child_storeme_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा simple_child *simple_child = to_simple_child(item);
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(page, 10, &simple_child->storeme);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

CONFIGFS_ATTR(simple_child_, storeme);

अटल काष्ठा configfs_attribute *simple_child_attrs[] = अणु
	&simple_child_attr_storeme,
	शून्य,
पूर्ण;

अटल व्योम simple_child_release(काष्ठा config_item *item)
अणु
	kमुक्त(to_simple_child(item));
पूर्ण

अटल काष्ठा configfs_item_operations simple_child_item_ops = अणु
	.release	= simple_child_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type simple_child_type = अणु
	.ct_item_ops	= &simple_child_item_ops,
	.ct_attrs	= simple_child_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

काष्ठा simple_children अणु
	काष्ठा config_group group;
पूर्ण;

अटल अंतरभूत काष्ठा simple_children *to_simple_children(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item),
			    काष्ठा simple_children, group);
पूर्ण

अटल काष्ठा config_item *simple_children_make_item(काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा simple_child *simple_child;

	simple_child = kzalloc(माप(काष्ठा simple_child), GFP_KERNEL);
	अगर (!simple_child)
		वापस ERR_PTR(-ENOMEM);

	config_item_init_type_name(&simple_child->item, name,
				   &simple_child_type);

	वापस &simple_child->item;
पूर्ण

अटल sमाप_प्रकार simple_children_description_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page,
"[02-simple-children]\n"
"\n"
"This subsystem allows the creation of child config_items.  These\n"
"items have only one attribute that is readable and writeable.\n");
पूर्ण

CONFIGFS_ATTR_RO(simple_children_, description);

अटल काष्ठा configfs_attribute *simple_children_attrs[] = अणु
	&simple_children_attr_description,
	शून्य,
पूर्ण;

अटल व्योम simple_children_release(काष्ठा config_item *item)
अणु
	kमुक्त(to_simple_children(item));
पूर्ण

अटल काष्ठा configfs_item_operations simple_children_item_ops = अणु
	.release	= simple_children_release,
पूर्ण;

/*
 * Note that, since no extra work is required on ->drop_item(),
 * no ->drop_item() is provided.
 */
अटल काष्ठा configfs_group_operations simple_children_group_ops = अणु
	.make_item	= simple_children_make_item,
पूर्ण;

अटल स्थिर काष्ठा config_item_type simple_children_type = अणु
	.ct_item_ops	= &simple_children_item_ops,
	.ct_group_ops	= &simple_children_group_ops,
	.ct_attrs	= simple_children_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली simple_children_subsys = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf = "02-simple-children",
			.ci_type = &simple_children_type,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* ----------------------------------------------------------------- */

/*
 * 03-group-children
 *
 * This example reuses the simple_children group from above.  However,
 * the simple_children group is not the subप्रणाली itself, it is a
 * child of the subप्रणाली.  Creation of a group in the subप्रणाली creates
 * a new simple_children group.  That group can then have simple_child
 * children of its own.
 */

अटल काष्ठा config_group *group_children_make_group(
		काष्ठा config_group *group, स्थिर अक्षर *name)
अणु
	काष्ठा simple_children *simple_children;

	simple_children = kzalloc(माप(काष्ठा simple_children),
				  GFP_KERNEL);
	अगर (!simple_children)
		वापस ERR_PTR(-ENOMEM);

	config_group_init_type_name(&simple_children->group, name,
				    &simple_children_type);

	वापस &simple_children->group;
पूर्ण

अटल sमाप_प्रकार group_children_description_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page,
"[03-group-children]\n"
"\n"
"This subsystem allows the creation of child config_groups.  These\n"
"groups are like the subsystem simple-children.\n");
पूर्ण

CONFIGFS_ATTR_RO(group_children_, description);

अटल काष्ठा configfs_attribute *group_children_attrs[] = अणु
	&group_children_attr_description,
	शून्य,
पूर्ण;

/*
 * Note that, since no extra work is required on ->drop_item(),
 * no ->drop_item() is provided.
 */
अटल काष्ठा configfs_group_operations group_children_group_ops = अणु
	.make_group	= group_children_make_group,
पूर्ण;

अटल स्थिर काष्ठा config_item_type group_children_type = अणु
	.ct_group_ops	= &group_children_group_ops,
	.ct_attrs	= group_children_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली group_children_subsys = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf = "03-group-children",
			.ci_type = &group_children_type,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* ----------------------------------------------------------------- */

/*
 * We're now करोne with our subप्रणाली definitions.
 * For convenience in this module, here's a list of them all.  It
 * allows the init function to easily रेजिस्टर them.  Most modules
 * will only have one subप्रणाली, and will only call रेजिस्टर_subप्रणाली
 * on it directly.
 */
अटल काष्ठा configfs_subप्रणाली *example_subsys[] = अणु
	&childless_subsys.subsys,
	&simple_children_subsys,
	&group_children_subsys,
	शून्य,
पूर्ण;

अटल पूर्णांक __init configfs_example_init(व्योम)
अणु
	काष्ठा configfs_subप्रणाली *subsys;
	पूर्णांक ret, i;

	क्रम (i = 0; example_subsys[i]; i++) अणु
		subsys = example_subsys[i];

		config_group_init(&subsys->su_group);
		mutex_init(&subsys->su_mutex);
		ret = configfs_रेजिस्टर_subप्रणाली(subsys);
		अगर (ret) अणु
			pr_err("Error %d while registering subsystem %s\n",
			       ret, subsys->su_group.cg_item.ci_namebuf);
			जाओ out_unरेजिस्टर;
		पूर्ण
	पूर्ण

	वापस 0;

out_unरेजिस्टर:
	क्रम (i--; i >= 0; i--)
		configfs_unरेजिस्टर_subप्रणाली(example_subsys[i]);

	वापस ret;
पूर्ण

अटल व्योम __निकास configfs_example_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; example_subsys[i]; i++)
		configfs_unरेजिस्टर_subप्रणाली(example_subsys[i]);
पूर्ण

module_init(configfs_example_init);
module_निकास(configfs_example_निकास);
MODULE_LICENSE("GPL");
