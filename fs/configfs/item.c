<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * item.c - library routines क्रम handling generic config items
 *
 * Based on kobject:
 *	kobject is Copyright (c) 2002-2003 Patrick Mochel
 *
 * configfs Copyright (C) 2005 Oracle.  All rights reserved.
 *
 * Please see the file Documentation/fileप्रणालीs/configfs.rst क्रम
 * critical inक्रमmation about using the config_item पूर्णांकerface.
 */

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>

#समावेश <linux/configfs.h>


अटल अंतरभूत काष्ठा config_item *to_item(काष्ठा list_head *entry)
अणु
	वापस container_of(entry, काष्ठा config_item, ci_entry);
पूर्ण

/* Evil kernel */
अटल व्योम config_item_release(काष्ठा kref *kref);

/**
 *	config_item_init - initialize item.
 *	@item:	item in question.
 */
अटल व्योम config_item_init(काष्ठा config_item *item)
अणु
	kref_init(&item->ci_kref);
	INIT_LIST_HEAD(&item->ci_entry);
पूर्ण

/**
 *	config_item_set_name - Set the name of an item
 *	@item:	item.
 *	@fmt:  The vsnम_लिखो()'s क्रमmat string.
 *
 *	If म_माप(name) >= CONFIGFS_ITEM_NAME_LEN, then use a
 *	dynamically allocated string that @item->ci_name poपूर्णांकs to.
 *	Otherwise, use the अटल @item->ci_namebuf array.
 */
पूर्णांक config_item_set_name(काष्ठा config_item *item, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक limit = CONFIGFS_ITEM_NAME_LEN;
	पूर्णांक need;
	बहु_सूची args;
	अक्षर *name;

	/*
	 * First, try the अटल array
	 */
	बहु_शुरू(args, fmt);
	need = vsnम_लिखो(item->ci_namebuf, limit, fmt, args);
	बहु_पूर्ण(args);
	अगर (need < limit)
		name = item->ci_namebuf;
	अन्यथा अणु
		बहु_शुरू(args, fmt);
		name = kvaप्र_लिखो(GFP_KERNEL, fmt, args);
		बहु_पूर्ण(args);
		अगर (!name)
			वापस -EFAULT;
	पूर्ण

	/* Free the old name, अगर necessary. */
	अगर (item->ci_name && item->ci_name != item->ci_namebuf)
		kमुक्त(item->ci_name);

	/* Now, set the new name */
	item->ci_name = name;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(config_item_set_name);

व्योम config_item_init_type_name(काष्ठा config_item *item,
				स्थिर अक्षर *name,
				स्थिर काष्ठा config_item_type *type)
अणु
	config_item_set_name(item, "%s", name);
	item->ci_type = type;
	config_item_init(item);
पूर्ण
EXPORT_SYMBOL(config_item_init_type_name);

व्योम config_group_init_type_name(काष्ठा config_group *group, स्थिर अक्षर *name,
			 स्थिर काष्ठा config_item_type *type)
अणु
	config_item_set_name(&group->cg_item, "%s", name);
	group->cg_item.ci_type = type;
	config_group_init(group);
पूर्ण
EXPORT_SYMBOL(config_group_init_type_name);

काष्ठा config_item *config_item_get(काष्ठा config_item *item)
अणु
	अगर (item)
		kref_get(&item->ci_kref);
	वापस item;
पूर्ण
EXPORT_SYMBOL(config_item_get);

काष्ठा config_item *config_item_get_unless_zero(काष्ठा config_item *item)
अणु
	अगर (item && kref_get_unless_zero(&item->ci_kref))
		वापस item;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(config_item_get_unless_zero);

अटल व्योम config_item_cleanup(काष्ठा config_item *item)
अणु
	स्थिर काष्ठा config_item_type *t = item->ci_type;
	काष्ठा config_group *s = item->ci_group;
	काष्ठा config_item *parent = item->ci_parent;

	pr_debug("config_item %s: cleaning up\n", config_item_name(item));
	अगर (item->ci_name != item->ci_namebuf)
		kमुक्त(item->ci_name);
	item->ci_name = शून्य;
	अगर (t && t->ct_item_ops && t->ct_item_ops->release)
		t->ct_item_ops->release(item);
	अगर (s)
		config_group_put(s);
	अगर (parent)
		config_item_put(parent);
पूर्ण

अटल व्योम config_item_release(काष्ठा kref *kref)
अणु
	config_item_cleanup(container_of(kref, काष्ठा config_item, ci_kref));
पूर्ण

/**
 *	config_item_put - decrement refcount क्रम item.
 *	@item:	item.
 *
 *	Decrement the refcount, and अगर 0, call config_item_cleanup().
 */
व्योम config_item_put(काष्ठा config_item *item)
अणु
	अगर (item)
		kref_put(&item->ci_kref, config_item_release);
पूर्ण
EXPORT_SYMBOL(config_item_put);

/**
 *	config_group_init - initialize a group क्रम use
 *	@group:	config_group
 */
व्योम config_group_init(काष्ठा config_group *group)
अणु
	config_item_init(&group->cg_item);
	INIT_LIST_HEAD(&group->cg_children);
	INIT_LIST_HEAD(&group->शेष_groups);
पूर्ण
EXPORT_SYMBOL(config_group_init);

/**
 *	config_group_find_item - search क्रम item in group.
 *	@group:	group we're looking in.
 *	@name:	item's name.
 *
 *	Iterate over @group->cg_list, looking क्रम a matching config_item.
 *	If matching item is found take a reference and वापस the item.
 *	Caller must have locked group via @group->cg_subsys->su_mtx.
 */
काष्ठा config_item *config_group_find_item(काष्ठा config_group *group,
					   स्थिर अक्षर *name)
अणु
	काष्ठा list_head *entry;
	काष्ठा config_item *ret = शून्य;

	list_क्रम_each(entry, &group->cg_children) अणु
		काष्ठा config_item *item = to_item(entry);
		अगर (config_item_name(item) &&
		    !म_भेद(config_item_name(item), name)) अणु
			ret = config_item_get(item);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(config_group_find_item);
