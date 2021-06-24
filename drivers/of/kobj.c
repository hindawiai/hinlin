<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश "of_private.h"

/* true when node is initialized */
अटल पूर्णांक of_node_is_initialized(काष्ठा device_node *node)
अणु
	वापस node && node->kobj.state_initialized;
पूर्ण

/* true when node is attached (i.e. present on sysfs) */
पूर्णांक of_node_is_attached(काष्ठा device_node *node)
अणु
	वापस node && node->kobj.state_in_sysfs;
पूर्ण


#अगर_अघोषित CONFIG_OF_DYNAMIC
अटल व्योम of_node_release(काष्ठा kobject *kobj)
अणु
	/* Without CONFIG_OF_DYNAMIC, no nodes माला_लो मुक्तd */
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_DYNAMIC */

काष्ठा kobj_type of_node_ktype = अणु
	.release = of_node_release,
पूर्ण;

अटल sमाप_प्रकार of_node_property_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				loff_t offset, माप_प्रकार count)
अणु
	काष्ठा property *pp = container_of(bin_attr, काष्ठा property, attr);
	वापस memory_पढ़ो_from_buffer(buf, count, &offset, pp->value, pp->length);
पूर्ण

/* always वापस newly allocated name, caller must मुक्त after use */
अटल स्थिर अक्षर *safe_name(काष्ठा kobject *kobj, स्थिर अक्षर *orig_name)
अणु
	स्थिर अक्षर *name = orig_name;
	काष्ठा kernfs_node *kn;
	पूर्णांक i = 0;

	/* करोn't be a hero. After 16 tries give up */
	जबतक (i < 16 && (kn = sysfs_get_dirent(kobj->sd, name))) अणु
		sysfs_put(kn);
		अगर (name != orig_name)
			kमुक्त(name);
		name = kaप्र_लिखो(GFP_KERNEL, "%s#%i", orig_name, ++i);
	पूर्ण

	अगर (name == orig_name) अणु
		name = kstrdup(orig_name, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		pr_warn("Duplicate name in %s, renamed to \"%s\"\n",
			kobject_name(kobj), name);
	पूर्ण
	वापस name;
पूर्ण

पूर्णांक __of_add_property_sysfs(काष्ठा device_node *np, काष्ठा property *pp)
अणु
	पूर्णांक rc;

	/* Important: Don't leak passwords */
	bool secure = म_भेदन(pp->name, "security-", 9) == 0;

	अगर (!IS_ENABLED(CONFIG_SYSFS))
		वापस 0;

	अगर (!of_kset || !of_node_is_attached(np))
		वापस 0;

	sysfs_bin_attr_init(&pp->attr);
	pp->attr.attr.name = safe_name(&np->kobj, pp->name);
	pp->attr.attr.mode = secure ? 0400 : 0444;
	pp->attr.size = secure ? 0 : pp->length;
	pp->attr.पढ़ो = of_node_property_पढ़ो;

	rc = sysfs_create_bin_file(&np->kobj, &pp->attr);
	WARN(rc, "error adding attribute %s to node %pOF\n", pp->name, np);
	वापस rc;
पूर्ण

व्योम __of_sysfs_हटाओ_bin_file(काष्ठा device_node *np, काष्ठा property *prop)
अणु
	अगर (!IS_ENABLED(CONFIG_SYSFS))
		वापस;

	sysfs_हटाओ_bin_file(&np->kobj, &prop->attr);
	kमुक्त(prop->attr.attr.name);
पूर्ण

व्योम __of_हटाओ_property_sysfs(काष्ठा device_node *np, काष्ठा property *prop)
अणु
	/* at early boot, bail here and defer setup to of_init() */
	अगर (of_kset && of_node_is_attached(np))
		__of_sysfs_हटाओ_bin_file(np, prop);
पूर्ण

व्योम __of_update_property_sysfs(काष्ठा device_node *np, काष्ठा property *newprop,
		काष्ठा property *oldprop)
अणु
	/* At early boot, bail out and defer setup to of_init() */
	अगर (!of_kset)
		वापस;

	अगर (oldprop)
		__of_sysfs_हटाओ_bin_file(np, oldprop);
	__of_add_property_sysfs(np, newprop);
पूर्ण

पूर्णांक __of_attach_node_sysfs(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *name;
	काष्ठा kobject *parent;
	काष्ठा property *pp;
	पूर्णांक rc;

	अगर (!of_kset)
		वापस 0;

	np->kobj.kset = of_kset;
	अगर (!np->parent) अणु
		/* Nodes without parents are new top level trees */
		name = safe_name(&of_kset->kobj, "base");
		parent = शून्य;
	पूर्ण अन्यथा अणु
		name = safe_name(&np->parent->kobj, kbasename(np->full_name));
		parent = &np->parent->kobj;
	पूर्ण
	अगर (!name)
		वापस -ENOMEM;

	rc = kobject_add(&np->kobj, parent, "%s", name);
	kमुक्त(name);
	अगर (rc)
		वापस rc;

	क्रम_each_property_of_node(np, pp)
		__of_add_property_sysfs(np, pp);

	of_node_get(np);
	वापस 0;
पूर्ण

व्योम __of_detach_node_sysfs(काष्ठा device_node *np)
अणु
	काष्ठा property *pp;

	BUG_ON(!of_node_is_initialized(np));
	अगर (!of_kset)
		वापस;

	/* only हटाओ properties अगर on sysfs */
	अगर (of_node_is_attached(np)) अणु
		क्रम_each_property_of_node(np, pp)
			__of_sysfs_हटाओ_bin_file(np, pp);
		kobject_del(&np->kobj);
	पूर्ण

	of_node_put(np);
पूर्ण
