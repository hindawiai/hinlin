<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * configfs.h - definitions क्रम the device driver fileप्रणाली
 *
 * Based on sysfs:
 * 	sysfs is Copyright (C) 2001, 2002, 2003 Patrick Mochel
 *
 * Based on kobject.h:
 *      Copyright (c) 2002-2003	Patrick Mochel
 *      Copyright (c) 2002-2003	Open Source Development Lअसल
 *
 * configfs Copyright (C) 2005 Oracle.  All rights reserved.
 *
 * Please पढ़ो Documentation/fileप्रणालीs/configfs.rst beक्रमe using
 * the configfs पूर्णांकerface, ESPECIALLY the parts about reference counts and
 * item deकाष्ठाors.
 */

#अगर_अघोषित _CONFIGFS_H_
#घोषणा _CONFIGFS_H_

#समावेश <linux/स्थिति.स>   /* S_IRUGO */
#समावेश <linux/types.h>  /* sमाप_प्रकार */
#समावेश <linux/list.h>   /* काष्ठा list_head */
#समावेश <linux/kref.h>   /* काष्ठा kref */
#समावेश <linux/mutex.h>  /* काष्ठा mutex */

#घोषणा CONFIGFS_ITEM_NAME_LEN	20

काष्ठा module;

काष्ठा configfs_item_operations;
काष्ठा configfs_group_operations;
काष्ठा configfs_attribute;
काष्ठा configfs_bin_attribute;
काष्ठा configfs_subप्रणाली;

काष्ठा config_item अणु
	अक्षर			*ci_name;
	अक्षर			ci_namebuf[CONFIGFS_ITEM_NAME_LEN];
	काष्ठा kref		ci_kref;
	काष्ठा list_head	ci_entry;
	काष्ठा config_item	*ci_parent;
	काष्ठा config_group	*ci_group;
	स्थिर काष्ठा config_item_type	*ci_type;
	काष्ठा dentry		*ci_dentry;
पूर्ण;

बाह्य __म_लिखो(2, 3)
पूर्णांक config_item_set_name(काष्ठा config_item *, स्थिर अक्षर *, ...);

अटल अंतरभूत अक्षर *config_item_name(काष्ठा config_item * item)
अणु
	वापस item->ci_name;
पूर्ण

बाह्य व्योम config_item_init_type_name(काष्ठा config_item *item,
				       स्थिर अक्षर *name,
				       स्थिर काष्ठा config_item_type *type);

बाह्य काष्ठा config_item *config_item_get(काष्ठा config_item *);
बाह्य काष्ठा config_item *config_item_get_unless_zero(काष्ठा config_item *);
बाह्य व्योम config_item_put(काष्ठा config_item *);

काष्ठा config_item_type अणु
	काष्ठा module				*ct_owner;
	काष्ठा configfs_item_operations		*ct_item_ops;
	काष्ठा configfs_group_operations	*ct_group_ops;
	काष्ठा configfs_attribute		**ct_attrs;
	काष्ठा configfs_bin_attribute		**ct_bin_attrs;
पूर्ण;

/**
 *	group - a group of config_items of a specअगरic type, beदीर्घing
 *	to a specअगरic subप्रणाली.
 */
काष्ठा config_group अणु
	काष्ठा config_item		cg_item;
	काष्ठा list_head		cg_children;
	काष्ठा configfs_subप्रणाली 	*cg_subsys;
	काष्ठा list_head		शेष_groups;
	काष्ठा list_head		group_entry;
पूर्ण;

बाह्य व्योम config_group_init(काष्ठा config_group *group);
बाह्य व्योम config_group_init_type_name(काष्ठा config_group *group,
					स्थिर अक्षर *name,
					स्थिर काष्ठा config_item_type *type);

अटल अंतरभूत काष्ठा config_group *to_config_group(काष्ठा config_item *item)
अणु
	वापस item ? container_of(item,काष्ठा config_group,cg_item) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा config_group *config_group_get(काष्ठा config_group *group)
अणु
	वापस group ? to_config_group(config_item_get(&group->cg_item)) : शून्य;
पूर्ण

अटल अंतरभूत व्योम config_group_put(काष्ठा config_group *group)
अणु
	config_item_put(&group->cg_item);
पूर्ण

बाह्य काष्ठा config_item *config_group_find_item(काष्ठा config_group *,
						  स्थिर अक्षर *);


अटल अंतरभूत व्योम configfs_add_शेष_group(काष्ठा config_group *new_group,
		काष्ठा config_group *group)
अणु
	list_add_tail(&new_group->group_entry, &group->शेष_groups);
पूर्ण

काष्ठा configfs_attribute अणु
	स्थिर अक्षर		*ca_name;
	काष्ठा module 		*ca_owner;
	umode_t			ca_mode;
	sमाप_प्रकार (*show)(काष्ठा config_item *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा config_item *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

#घोषणा CONFIGFS_ATTR(_pfx, _name)			\
अटल काष्ठा configfs_attribute _pfx##attr_##_name = अणु	\
	.ca_name	= __stringअगरy(_name),		\
	.ca_mode	= S_IRUGO | S_IWUSR,		\
	.ca_owner	= THIS_MODULE,			\
	.show		= _pfx##_name##_show,		\
	.store		= _pfx##_name##_store,		\
पूर्ण

#घोषणा CONFIGFS_ATTR_RO(_pfx, _name)			\
अटल काष्ठा configfs_attribute _pfx##attr_##_name = अणु	\
	.ca_name	= __stringअगरy(_name),		\
	.ca_mode	= S_IRUGO,			\
	.ca_owner	= THIS_MODULE,			\
	.show		= _pfx##_name##_show,		\
पूर्ण

#घोषणा CONFIGFS_ATTR_WO(_pfx, _name)			\
अटल काष्ठा configfs_attribute _pfx##attr_##_name = अणु	\
	.ca_name	= __stringअगरy(_name),		\
	.ca_mode	= S_IWUSR,			\
	.ca_owner	= THIS_MODULE,			\
	.store		= _pfx##_name##_store,		\
पूर्ण

काष्ठा file;
काष्ठा vm_area_काष्ठा;

काष्ठा configfs_bin_attribute अणु
	काष्ठा configfs_attribute cb_attr;	/* std. attribute */
	व्योम *cb_निजी;			/* क्रम user       */
	माप_प्रकार cb_max_size;			/* max core size  */
	sमाप_प्रकार (*पढ़ो)(काष्ठा config_item *, व्योम *, माप_प्रकार);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा config_item *, स्थिर व्योम *, माप_प्रकार);
पूर्ण;

#घोषणा CONFIGFS_BIN_ATTR(_pfx, _name, _priv, _maxsz)		\
अटल काष्ठा configfs_bin_attribute _pfx##attr_##_name = अणु	\
	.cb_attr = अणु						\
		.ca_name	= __stringअगरy(_name),		\
		.ca_mode	= S_IRUGO | S_IWUSR,		\
		.ca_owner	= THIS_MODULE,			\
	पूर्ण,							\
	.cb_निजी	= _priv,				\
	.cb_max_size	= _maxsz,				\
	.पढ़ो		= _pfx##_name##_पढ़ो,			\
	.ग_लिखो		= _pfx##_name##_ग_लिखो,			\
पूर्ण

#घोषणा CONFIGFS_BIN_ATTR_RO(_pfx, _name, _priv, _maxsz)	\
अटल काष्ठा configfs_bin_attribute _pfx##attr_##_name = अणु	\
	.cb_attr = अणु						\
		.ca_name	= __stringअगरy(_name),		\
		.ca_mode	= S_IRUGO,			\
		.ca_owner	= THIS_MODULE,			\
	पूर्ण,							\
	.cb_निजी	= _priv,				\
	.cb_max_size	= _maxsz,				\
	.पढ़ो		= _pfx##_name##_पढ़ो,			\
पूर्ण

#घोषणा CONFIGFS_BIN_ATTR_WO(_pfx, _name, _priv, _maxsz)	\
अटल काष्ठा configfs_bin_attribute _pfx##attr_##_name = अणु	\
	.cb_attr = अणु						\
		.ca_name	= __stringअगरy(_name),		\
		.ca_mode	= S_IWUSR,			\
		.ca_owner	= THIS_MODULE,			\
	पूर्ण,							\
	.cb_निजी	= _priv,				\
	.cb_max_size	= _maxsz,				\
	.ग_लिखो		= _pfx##_name##_ग_लिखो,			\
पूर्ण

/*
 * If allow_link() exists, the item can symlink(2) out to other
 * items.  If the item is a group, it may support सूची_गढ़ो(2).
 * Groups supply one of make_group() and make_item().  If the
 * group supports make_group(), one can create group children.  If it
 * supports make_item(), one can create config_item children.  make_group()
 * and make_item() वापस ERR_PTR() on errors.  If it has
 * शेष_groups on group->शेष_groups, it has स्वतःmatically created
 * group children.  शेष_groups may coexist aदीर्घsize make_group() or
 * make_item(), but अगर the group wishes to have only शेष_groups
 * children (disallowing सूची_गढ़ो(2)), it need not provide either function.
 * If the group has commit(), it supports pending and committed (active)
 * items.
 */
काष्ठा configfs_item_operations अणु
	व्योम (*release)(काष्ठा config_item *);
	पूर्णांक (*allow_link)(काष्ठा config_item *src, काष्ठा config_item *target);
	व्योम (*drop_link)(काष्ठा config_item *src, काष्ठा config_item *target);
पूर्ण;

काष्ठा configfs_group_operations अणु
	काष्ठा config_item *(*make_item)(काष्ठा config_group *group, स्थिर अक्षर *name);
	काष्ठा config_group *(*make_group)(काष्ठा config_group *group, स्थिर अक्षर *name);
	पूर्णांक (*commit_item)(काष्ठा config_item *item);
	व्योम (*disconnect_notअगरy)(काष्ठा config_group *group, काष्ठा config_item *item);
	व्योम (*drop_item)(काष्ठा config_group *group, काष्ठा config_item *item);
पूर्ण;

काष्ठा configfs_subप्रणाली अणु
	काष्ठा config_group	su_group;
	काष्ठा mutex		su_mutex;
पूर्ण;

अटल अंतरभूत काष्ठा configfs_subप्रणाली *to_configfs_subप्रणाली(काष्ठा config_group *group)
अणु
	वापस group ?
		container_of(group, काष्ठा configfs_subप्रणाली, su_group) :
		शून्य;
पूर्ण

पूर्णांक configfs_रेजिस्टर_subप्रणाली(काष्ठा configfs_subप्रणाली *subsys);
व्योम configfs_unरेजिस्टर_subप्रणाली(काष्ठा configfs_subप्रणाली *subsys);

पूर्णांक configfs_रेजिस्टर_group(काष्ठा config_group *parent_group,
			    काष्ठा config_group *group);
व्योम configfs_unरेजिस्टर_group(काष्ठा config_group *group);

व्योम configfs_हटाओ_शेष_groups(काष्ठा config_group *group);

काष्ठा config_group *
configfs_रेजिस्टर_शेष_group(काष्ठा config_group *parent_group,
				स्थिर अक्षर *name,
				स्थिर काष्ठा config_item_type *item_type);
व्योम configfs_unरेजिस्टर_शेष_group(काष्ठा config_group *group);

/* These functions can sleep and can alloc with GFP_KERNEL */
/* WARNING: These cannot be called underneath configfs callbacks!! */
पूर्णांक configfs_depend_item(काष्ठा configfs_subप्रणाली *subsys,
			 काष्ठा config_item *target);
व्योम configfs_undepend_item(काष्ठा config_item *target);

/*
 * These functions can sleep and can alloc with GFP_KERNEL
 * NOTE: These should be called only underneath configfs callbacks.
 * NOTE: First parameter is a caller's subsystem, not target's.
 * WARNING: These cannot be called on newly created item
 *        (in make_group()/make_item() callback)
 */
पूर्णांक configfs_depend_item_unlocked(काष्ठा configfs_subप्रणाली *caller_subsys,
				  काष्ठा config_item *target);


अटल अंतरभूत व्योम configfs_undepend_item_unlocked(काष्ठा config_item *target)
अणु
	configfs_undepend_item(target);
पूर्ण

#पूर्ण_अगर /* _CONFIGFS_H_ */
