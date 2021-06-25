<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sysfs.h - definitions क्रम the device driver fileप्रणाली
 *
 * Copyright (c) 2001,2002 Patrick Mochel
 * Copyright (c) 2004 Silicon Graphics, Inc.
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Please see Documentation/fileप्रणालीs/sysfs.rst क्रम more inक्रमmation.
 */

#अगर_अघोषित _SYSFS_H_
#घोषणा _SYSFS_H_

#समावेश <linux/kernfs.h>
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/kobject_ns.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/atomic.h>

काष्ठा kobject;
काष्ठा module;
काष्ठा bin_attribute;
क्रमागत kobj_ns_type;

काष्ठा attribute अणु
	स्थिर अक्षर		*name;
	umode_t			mode;
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	bool			ignore_lockdep:1;
	काष्ठा lock_class_key	*key;
	काष्ठा lock_class_key	skey;
#पूर्ण_अगर
पूर्ण;

/**
 *	sysfs_attr_init - initialize a dynamically allocated sysfs attribute
 *	@attr: काष्ठा attribute to initialize
 *
 *	Initialize a dynamically allocated काष्ठा attribute so we can
 *	make lockdep happy.  This is a new requirement क्रम attributes
 *	and initially this is only needed when lockdep is enabled.
 *	Lockdep gives a nice error when your attribute is added to
 *	sysfs अगर you करोn't have this.
 */
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
#घोषणा sysfs_attr_init(attr)				\
करो अणु							\
	अटल काष्ठा lock_class_key __key;		\
							\
	(attr)->key = &__key;				\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा sysfs_attr_init(attr) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * काष्ठा attribute_group - data काष्ठाure used to declare an attribute group.
 * @name:	Optional: Attribute group name
 *		If specअगरied, the attribute group will be created in
 *		a new subdirectory with this name.
 * @is_visible:	Optional: Function to वापस permissions associated with an
 *		attribute of the group. Will be called repeatedly क्रम each
 *		non-binary attribute in the group. Only पढ़ो/ग_लिखो
 *		permissions as well as SYSFS_PREALLOC are accepted. Must
 *		वापस 0 अगर an attribute is not visible. The वापसed value
 *		will replace अटल permissions defined in काष्ठा attribute.
 * @is_bin_visible:
 *		Optional: Function to वापस permissions associated with a
 *		binary attribute of the group. Will be called repeatedly
 *		क्रम each binary attribute in the group. Only पढ़ो/ग_लिखो
 *		permissions as well as SYSFS_PREALLOC are accepted. Must
 *		वापस 0 अगर a binary attribute is not visible. The वापसed
 *		value will replace अटल permissions defined in
 *		काष्ठा bin_attribute.
 * @attrs:	Poपूर्णांकer to शून्य terminated list of attributes.
 * @bin_attrs:	Poपूर्णांकer to शून्य terminated list of binary attributes.
 *		Either attrs or bin_attrs or both must be provided.
 */
काष्ठा attribute_group अणु
	स्थिर अक्षर		*name;
	umode_t			(*is_visible)(काष्ठा kobject *,
					      काष्ठा attribute *, पूर्णांक);
	umode_t			(*is_bin_visible)(काष्ठा kobject *,
						  काष्ठा bin_attribute *, पूर्णांक);
	काष्ठा attribute	**attrs;
	काष्ठा bin_attribute	**bin_attrs;
पूर्ण;

/*
 * Use these macros to make defining attributes easier.
 * See include/linux/device.h क्रम examples..
 */

#घोषणा SYSFS_PREALLOC 010000

#घोषणा __ATTR(_name, _mode, _show, _store) अणु				\
	.attr = अणु.name = __stringअगरy(_name),				\
		 .mode = VERIFY_OCTAL_PERMISSIONS(_mode) पूर्ण,		\
	.show	= _show,						\
	.store	= _store,						\
पूर्ण

#घोषणा __ATTR_PREALLOC(_name, _mode, _show, _store) अणु			\
	.attr = अणु.name = __stringअगरy(_name),				\
		 .mode = SYSFS_PREALLOC | VERIFY_OCTAL_PERMISSIONS(_mode) पूर्ण,\
	.show	= _show,						\
	.store	= _store,						\
पूर्ण

#घोषणा __ATTR_RO(_name) अणु						\
	.attr	= अणु .name = __stringअगरy(_name), .mode = 0444 पूर्ण,		\
	.show	= _name##_show,						\
पूर्ण

#घोषणा __ATTR_RO_MODE(_name, _mode) अणु					\
	.attr	= अणु .name = __stringअगरy(_name),				\
		    .mode = VERIFY_OCTAL_PERMISSIONS(_mode) पूर्ण,		\
	.show	= _name##_show,						\
पूर्ण

#घोषणा __ATTR_RW_MODE(_name, _mode) अणु					\
	.attr	= अणु .name = __stringअगरy(_name),				\
		    .mode = VERIFY_OCTAL_PERMISSIONS(_mode) पूर्ण,		\
	.show	= _name##_show,						\
	.store	= _name##_store,					\
पूर्ण

#घोषणा __ATTR_WO(_name) अणु						\
	.attr	= अणु .name = __stringअगरy(_name), .mode = 0200 पूर्ण,		\
	.store	= _name##_store,					\
पूर्ण

#घोषणा __ATTR_RW(_name) __ATTR(_name, 0644, _name##_show, _name##_store)

#घोषणा __ATTR_शून्य अणु .attr = अणु .name = शून्य पूर्ण पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
#घोषणा __ATTR_IGNORE_LOCKDEP(_name, _mode, _show, _store) अणु	\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode,	\
			.ignore_lockdep = true पूर्ण,		\
	.show		= _show,				\
	.store		= _store,				\
पूर्ण
#अन्यथा
#घोषणा __ATTR_IGNORE_LOCKDEP	__ATTR
#पूर्ण_अगर

#घोषणा __ATTRIBUTE_GROUPS(_name)				\
अटल स्थिर काष्ठा attribute_group *_name##_groups[] = अणु	\
	&_name##_group,						\
	शून्य,							\
पूर्ण

#घोषणा ATTRIBUTE_GROUPS(_name)					\
अटल स्थिर काष्ठा attribute_group _name##_group = अणु		\
	.attrs = _name##_attrs,					\
पूर्ण;								\
__ATTRIBUTE_GROUPS(_name)

काष्ठा file;
काष्ठा vm_area_काष्ठा;
काष्ठा address_space;

काष्ठा bin_attribute अणु
	काष्ठा attribute	attr;
	माप_प्रकार			size;
	व्योम			*निजी;
	काष्ठा address_space	*mapping;
	sमाप_प्रकार (*पढ़ो)(काष्ठा file *, काष्ठा kobject *, काष्ठा bin_attribute *,
			अक्षर *, loff_t, माप_प्रकार);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा file *, काष्ठा kobject *, काष्ठा bin_attribute *,
			 अक्षर *, loff_t, माप_प्रकार);
	पूर्णांक (*mmap)(काष्ठा file *, काष्ठा kobject *, काष्ठा bin_attribute *attr,
		    काष्ठा vm_area_काष्ठा *vma);
पूर्ण;

/**
 *	sysfs_bin_attr_init - initialize a dynamically allocated bin_attribute
 *	@attr: काष्ठा bin_attribute to initialize
 *
 *	Initialize a dynamically allocated काष्ठा bin_attribute so we
 *	can make lockdep happy.  This is a new requirement क्रम
 *	attributes and initially this is only needed when lockdep is
 *	enabled.  Lockdep gives a nice error when your attribute is
 *	added to sysfs अगर you करोn't have this.
 */
#घोषणा sysfs_bin_attr_init(bin_attr) sysfs_attr_init(&(bin_attr)->attr)

/* macros to create अटल binary attributes easier */
#घोषणा __BIN_ATTR(_name, _mode, _पढ़ो, _ग_लिखो, _size) अणु		\
	.attr = अणु .name = __stringअगरy(_name), .mode = _mode पूर्ण,		\
	.पढ़ो	= _पढ़ो,						\
	.ग_लिखो	= _ग_लिखो,						\
	.size	= _size,						\
पूर्ण

#घोषणा __BIN_ATTR_RO(_name, _size) अणु					\
	.attr	= अणु .name = __stringअगरy(_name), .mode = 0444 पूर्ण,		\
	.पढ़ो	= _name##_पढ़ो,						\
	.size	= _size,						\
पूर्ण

#घोषणा __BIN_ATTR_WO(_name, _size) अणु					\
	.attr	= अणु .name = __stringअगरy(_name), .mode = 0200 पूर्ण,		\
	.ग_लिखो	= _name##_ग_लिखो,					\
	.size	= _size,						\
पूर्ण

#घोषणा __BIN_ATTR_RW(_name, _size)					\
	__BIN_ATTR(_name, 0644, _name##_पढ़ो, _name##_ग_लिखो, _size)

#घोषणा __BIN_ATTR_शून्य __ATTR_शून्य

#घोषणा BIN_ATTR(_name, _mode, _पढ़ो, _ग_लिखो, _size)			\
काष्ठा bin_attribute bin_attr_##_name = __BIN_ATTR(_name, _mode, _पढ़ो,	\
					_ग_लिखो, _size)

#घोषणा BIN_ATTR_RO(_name, _size)					\
काष्ठा bin_attribute bin_attr_##_name = __BIN_ATTR_RO(_name, _size)

#घोषणा BIN_ATTR_WO(_name, _size)					\
काष्ठा bin_attribute bin_attr_##_name = __BIN_ATTR_WO(_name, _size)

#घोषणा BIN_ATTR_RW(_name, _size)					\
काष्ठा bin_attribute bin_attr_##_name = __BIN_ATTR_RW(_name, _size)

काष्ठा sysfs_ops अणु
	sमाप_प्रकार	(*show)(काष्ठा kobject *, काष्ठा attribute *, अक्षर *);
	sमाप_प्रकार	(*store)(काष्ठा kobject *, काष्ठा attribute *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

#अगर_घोषित CONFIG_SYSFS

पूर्णांक __must_check sysfs_create_dir_ns(काष्ठा kobject *kobj, स्थिर व्योम *ns);
व्योम sysfs_हटाओ_dir(काष्ठा kobject *kobj);
पूर्णांक __must_check sysfs_नाम_dir_ns(काष्ठा kobject *kobj, स्थिर अक्षर *new_name,
				     स्थिर व्योम *new_ns);
पूर्णांक __must_check sysfs_move_dir_ns(काष्ठा kobject *kobj,
				   काष्ठा kobject *new_parent_kobj,
				   स्थिर व्योम *new_ns);
पूर्णांक __must_check sysfs_create_mount_poपूर्णांक(काष्ठा kobject *parent_kobj,
					  स्थिर अक्षर *name);
व्योम sysfs_हटाओ_mount_poपूर्णांक(काष्ठा kobject *parent_kobj,
			      स्थिर अक्षर *name);

पूर्णांक __must_check sysfs_create_file_ns(काष्ठा kobject *kobj,
				      स्थिर काष्ठा attribute *attr,
				      स्थिर व्योम *ns);
पूर्णांक __must_check sysfs_create_files(काष्ठा kobject *kobj,
				   स्थिर काष्ठा attribute * स्थिर *attr);
पूर्णांक __must_check sysfs_chmod_file(काष्ठा kobject *kobj,
				  स्थिर काष्ठा attribute *attr, umode_t mode);
काष्ठा kernfs_node *sysfs_अवरोध_active_protection(काष्ठा kobject *kobj,
						  स्थिर काष्ठा attribute *attr);
व्योम sysfs_unअवरोध_active_protection(काष्ठा kernfs_node *kn);
व्योम sysfs_हटाओ_file_ns(काष्ठा kobject *kobj, स्थिर काष्ठा attribute *attr,
			  स्थिर व्योम *ns);
bool sysfs_हटाओ_file_self(काष्ठा kobject *kobj, स्थिर काष्ठा attribute *attr);
व्योम sysfs_हटाओ_files(काष्ठा kobject *kobj, स्थिर काष्ठा attribute * स्थिर *attr);

पूर्णांक __must_check sysfs_create_bin_file(काष्ठा kobject *kobj,
				       स्थिर काष्ठा bin_attribute *attr);
व्योम sysfs_हटाओ_bin_file(काष्ठा kobject *kobj,
			   स्थिर काष्ठा bin_attribute *attr);

पूर्णांक __must_check sysfs_create_link(काष्ठा kobject *kobj, काष्ठा kobject *target,
				   स्थिर अक्षर *name);
पूर्णांक __must_check sysfs_create_link_nowarn(काष्ठा kobject *kobj,
					  काष्ठा kobject *target,
					  स्थिर अक्षर *name);
व्योम sysfs_हटाओ_link(काष्ठा kobject *kobj, स्थिर अक्षर *name);

पूर्णांक sysfs_नाम_link_ns(काष्ठा kobject *kobj, काष्ठा kobject *target,
			 स्थिर अक्षर *old_name, स्थिर अक्षर *new_name,
			 स्थिर व्योम *new_ns);

व्योम sysfs_delete_link(काष्ठा kobject *dir, काष्ठा kobject *targ,
			स्थिर अक्षर *name);

पूर्णांक __must_check sysfs_create_group(काष्ठा kobject *kobj,
				    स्थिर काष्ठा attribute_group *grp);
पूर्णांक __must_check sysfs_create_groups(काष्ठा kobject *kobj,
				     स्थिर काष्ठा attribute_group **groups);
पूर्णांक __must_check sysfs_update_groups(काष्ठा kobject *kobj,
				     स्थिर काष्ठा attribute_group **groups);
पूर्णांक sysfs_update_group(काष्ठा kobject *kobj,
		       स्थिर काष्ठा attribute_group *grp);
व्योम sysfs_हटाओ_group(काष्ठा kobject *kobj,
			स्थिर काष्ठा attribute_group *grp);
व्योम sysfs_हटाओ_groups(काष्ठा kobject *kobj,
			 स्थिर काष्ठा attribute_group **groups);
पूर्णांक sysfs_add_file_to_group(काष्ठा kobject *kobj,
			स्थिर काष्ठा attribute *attr, स्थिर अक्षर *group);
व्योम sysfs_हटाओ_file_from_group(काष्ठा kobject *kobj,
			स्थिर काष्ठा attribute *attr, स्थिर अक्षर *group);
पूर्णांक sysfs_merge_group(काष्ठा kobject *kobj,
		       स्थिर काष्ठा attribute_group *grp);
व्योम sysfs_unmerge_group(काष्ठा kobject *kobj,
		       स्थिर काष्ठा attribute_group *grp);
पूर्णांक sysfs_add_link_to_group(काष्ठा kobject *kobj, स्थिर अक्षर *group_name,
			    काष्ठा kobject *target, स्थिर अक्षर *link_name);
व्योम sysfs_हटाओ_link_from_group(काष्ठा kobject *kobj, स्थिर अक्षर *group_name,
				  स्थिर अक्षर *link_name);
पूर्णांक compat_only_sysfs_link_entry_to_kobj(काष्ठा kobject *kobj,
					 काष्ठा kobject *target_kobj,
					 स्थिर अक्षर *target_name,
					 स्थिर अक्षर *symlink_name);

व्योम sysfs_notअगरy(काष्ठा kobject *kobj, स्थिर अक्षर *dir, स्थिर अक्षर *attr);

पूर्णांक __must_check sysfs_init(व्योम);

अटल अंतरभूत व्योम sysfs_enable_ns(काष्ठा kernfs_node *kn)
अणु
	वापस kernfs_enable_ns(kn);
पूर्ण

पूर्णांक sysfs_file_change_owner(काष्ठा kobject *kobj, स्थिर अक्षर *name, kuid_t kuid,
			    kgid_t kgid);
पूर्णांक sysfs_change_owner(काष्ठा kobject *kobj, kuid_t kuid, kgid_t kgid);
पूर्णांक sysfs_link_change_owner(काष्ठा kobject *kobj, काष्ठा kobject *targ,
			    स्थिर अक्षर *name, kuid_t kuid, kgid_t kgid);
पूर्णांक sysfs_groups_change_owner(काष्ठा kobject *kobj,
			      स्थिर काष्ठा attribute_group **groups,
			      kuid_t kuid, kgid_t kgid);
पूर्णांक sysfs_group_change_owner(काष्ठा kobject *kobj,
			     स्थिर काष्ठा attribute_group *groups, kuid_t kuid,
			     kgid_t kgid);
__म_लिखो(2, 3)
पूर्णांक sysfs_emit(अक्षर *buf, स्थिर अक्षर *fmt, ...);
__म_लिखो(3, 4)
पूर्णांक sysfs_emit_at(अक्षर *buf, पूर्णांक at, स्थिर अक्षर *fmt, ...);

#अन्यथा /* CONFIG_SYSFS */

अटल अंतरभूत पूर्णांक sysfs_create_dir_ns(काष्ठा kobject *kobj, स्थिर व्योम *ns)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_dir(काष्ठा kobject *kobj)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_नाम_dir_ns(काष्ठा kobject *kobj,
				      स्थिर अक्षर *new_name, स्थिर व्योम *new_ns)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_move_dir_ns(काष्ठा kobject *kobj,
				    काष्ठा kobject *new_parent_kobj,
				    स्थिर व्योम *new_ns)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_create_mount_poपूर्णांक(काष्ठा kobject *parent_kobj,
					   स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_mount_poपूर्णांक(काष्ठा kobject *parent_kobj,
					    स्थिर अक्षर *name)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_create_file_ns(काष्ठा kobject *kobj,
				       स्थिर काष्ठा attribute *attr,
				       स्थिर व्योम *ns)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_create_files(काष्ठा kobject *kobj,
				    स्थिर काष्ठा attribute * स्थिर *attr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_chmod_file(काष्ठा kobject *kobj,
				   स्थिर काष्ठा attribute *attr, umode_t mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
sysfs_अवरोध_active_protection(काष्ठा kobject *kobj,
			      स्थिर काष्ठा attribute *attr)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम sysfs_unअवरोध_active_protection(काष्ठा kernfs_node *kn)
अणु
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_file_ns(काष्ठा kobject *kobj,
					स्थिर काष्ठा attribute *attr,
					स्थिर व्योम *ns)
अणु
पूर्ण

अटल अंतरभूत bool sysfs_हटाओ_file_self(काष्ठा kobject *kobj,
					  स्थिर काष्ठा attribute *attr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_files(काष्ठा kobject *kobj,
				     स्थिर काष्ठा attribute * स्थिर *attr)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_create_bin_file(काष्ठा kobject *kobj,
					स्थिर काष्ठा bin_attribute *attr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_bin_file(काष्ठा kobject *kobj,
					 स्थिर काष्ठा bin_attribute *attr)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_create_link(काष्ठा kobject *kobj,
				    काष्ठा kobject *target, स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_create_link_nowarn(काष्ठा kobject *kobj,
					   काष्ठा kobject *target,
					   स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_link(काष्ठा kobject *kobj, स्थिर अक्षर *name)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_नाम_link_ns(काष्ठा kobject *k, काष्ठा kobject *t,
				       स्थिर अक्षर *old_name,
				       स्थिर अक्षर *new_name, स्थिर व्योम *ns)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_delete_link(काष्ठा kobject *k, काष्ठा kobject *t,
				     स्थिर अक्षर *name)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_create_group(काष्ठा kobject *kobj,
				     स्थिर काष्ठा attribute_group *grp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_create_groups(काष्ठा kobject *kobj,
				      स्थिर काष्ठा attribute_group **groups)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_update_groups(काष्ठा kobject *kobj,
				      स्थिर काष्ठा attribute_group **groups)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_update_group(काष्ठा kobject *kobj,
				स्थिर काष्ठा attribute_group *grp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_group(काष्ठा kobject *kobj,
				      स्थिर काष्ठा attribute_group *grp)
अणु
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_groups(काष्ठा kobject *kobj,
				       स्थिर काष्ठा attribute_group **groups)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_add_file_to_group(काष्ठा kobject *kobj,
		स्थिर काष्ठा attribute *attr, स्थिर अक्षर *group)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_file_from_group(काष्ठा kobject *kobj,
		स्थिर काष्ठा attribute *attr, स्थिर अक्षर *group)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_merge_group(काष्ठा kobject *kobj,
		       स्थिर काष्ठा attribute_group *grp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_unmerge_group(काष्ठा kobject *kobj,
		       स्थिर काष्ठा attribute_group *grp)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_add_link_to_group(काष्ठा kobject *kobj,
		स्थिर अक्षर *group_name, काष्ठा kobject *target,
		स्थिर अक्षर *link_name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_link_from_group(काष्ठा kobject *kobj,
		स्थिर अक्षर *group_name, स्थिर अक्षर *link_name)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक compat_only_sysfs_link_entry_to_kobj(काष्ठा kobject *kobj,
						       काष्ठा kobject *target_kobj,
						       स्थिर अक्षर *target_name,
						       स्थिर अक्षर *symlink_name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_notअगरy(काष्ठा kobject *kobj, स्थिर अक्षर *dir,
				स्थिर अक्षर *attr)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक __must_check sysfs_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_enable_ns(काष्ठा kernfs_node *kn)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_file_change_owner(काष्ठा kobject *kobj,
					  स्थिर अक्षर *name, kuid_t kuid,
					  kgid_t kgid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_link_change_owner(काष्ठा kobject *kobj,
					  काष्ठा kobject *targ,
					  स्थिर अक्षर *name, kuid_t kuid,
					  kgid_t kgid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_change_owner(काष्ठा kobject *kobj, kuid_t kuid, kgid_t kgid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_groups_change_owner(काष्ठा kobject *kobj,
			  स्थिर काष्ठा attribute_group **groups,
			  kuid_t kuid, kgid_t kgid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_group_change_owner(काष्ठा kobject *kobj,
					   स्थिर काष्ठा attribute_group *groups,
					   kuid_t kuid, kgid_t kgid)
अणु
	वापस 0;
पूर्ण

__म_लिखो(2, 3)
अटल अंतरभूत पूर्णांक sysfs_emit(अक्षर *buf, स्थिर अक्षर *fmt, ...)
अणु
	वापस 0;
पूर्ण

__म_लिखो(3, 4)
अटल अंतरभूत पूर्णांक sysfs_emit_at(अक्षर *buf, पूर्णांक at, स्थिर अक्षर *fmt, ...)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSFS */

अटल अंतरभूत पूर्णांक __must_check sysfs_create_file(काष्ठा kobject *kobj,
						 स्थिर काष्ठा attribute *attr)
अणु
	वापस sysfs_create_file_ns(kobj, attr, शून्य);
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_file(काष्ठा kobject *kobj,
				     स्थिर काष्ठा attribute *attr)
अणु
	sysfs_हटाओ_file_ns(kobj, attr, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_नाम_link(काष्ठा kobject *kobj, काष्ठा kobject *target,
				    स्थिर अक्षर *old_name, स्थिर अक्षर *new_name)
अणु
	वापस sysfs_नाम_link_ns(kobj, target, old_name, new_name, शून्य);
पूर्ण

अटल अंतरभूत व्योम sysfs_notअगरy_dirent(काष्ठा kernfs_node *kn)
अणु
	kernfs_notअगरy(kn);
पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *sysfs_get_dirent(काष्ठा kernfs_node *parent,
						   स्थिर अक्षर *name)
अणु
	वापस kernfs_find_and_get(parent, name);
पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *sysfs_get(काष्ठा kernfs_node *kn)
अणु
	kernfs_get(kn);
	वापस kn;
पूर्ण

अटल अंतरभूत व्योम sysfs_put(काष्ठा kernfs_node *kn)
अणु
	kernfs_put(kn);
पूर्ण

#पूर्ण_अगर /* _SYSFS_H_ */
