<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Red Hat, Inc.
 * All Rights Reserved.
 */

#अगर_अघोषित __XFS_SYSFS_H__
#घोषणा __XFS_SYSFS_H__

बाह्य काष्ठा kobj_type xfs_mp_ktype;	/* xfs_mount */
बाह्य काष्ठा kobj_type xfs_dbg_ktype;	/* debug */
बाह्य काष्ठा kobj_type xfs_log_ktype;	/* xlog */
बाह्य काष्ठा kobj_type xfs_stats_ktype;	/* stats */

अटल अंतरभूत काष्ठा xfs_kobj *
to_kobj(काष्ठा kobject *kobject)
अणु
	वापस container_of(kobject, काष्ठा xfs_kobj, kobject);
पूर्ण

अटल अंतरभूत व्योम
xfs_sysfs_release(काष्ठा kobject *kobject)
अणु
	काष्ठा xfs_kobj *kobj = to_kobj(kobject);
	complete(&kobj->complete);
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_sysfs_init(
	काष्ठा xfs_kobj		*kobj,
	काष्ठा kobj_type	*ktype,
	काष्ठा xfs_kobj		*parent_kobj,
	स्थिर अक्षर		*name)
अणु
	काष्ठा kobject		*parent;

	parent = parent_kobj ? &parent_kobj->kobject : शून्य;
	init_completion(&kobj->complete);
	वापस kobject_init_and_add(&kobj->kobject, ktype, parent, "%s", name);
पूर्ण

अटल अंतरभूत व्योम
xfs_sysfs_del(
	काष्ठा xfs_kobj	*kobj)
अणु
	kobject_del(&kobj->kobject);
	kobject_put(&kobj->kobject);
	रुको_क्रम_completion(&kobj->complete);
पूर्ण

पूर्णांक	xfs_error_sysfs_init(काष्ठा xfs_mount *mp);
व्योम	xfs_error_sysfs_del(काष्ठा xfs_mount *mp);

#पूर्ण_अगर	/* __XFS_SYSFS_H__ */
