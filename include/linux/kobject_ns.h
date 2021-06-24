<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Kernel object name space definitions
 *
 * Copyright (c) 2002-2003 Patrick Mochel
 * Copyright (c) 2002-2003 Open Source Development Lअसल
 * Copyright (c) 2006-2008 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (c) 2006-2008 Novell Inc.
 *
 * Split from kobject.h by David Howells (dhowells@redhat.com)
 *
 * Please पढ़ो Documentation/core-api/kobject.rst beक्रमe using the kobject
 * पूर्णांकerface, ESPECIALLY the parts about reference counts and object
 * deकाष्ठाors.
 */

#अगर_अघोषित _LINUX_KOBJECT_NS_H
#घोषणा _LINUX_KOBJECT_NS_H

काष्ठा sock;
काष्ठा kobject;

/*
 * Namespace types which are used to tag kobjects and sysfs entries.
 * Network namespace will likely be the first.
 */
क्रमागत kobj_ns_type अणु
	KOBJ_NS_TYPE_NONE = 0,
	KOBJ_NS_TYPE_NET,
	KOBJ_NS_TYPES
पूर्ण;

/*
 * Callbacks so sysfs can determine namespaces
 *   @grab_current_ns: वापस a new reference to calling task's namespace
 *   @netlink_ns: वापस namespace to which a sock beदीर्घs (right?)
 *   @initial_ns: वापस the initial namespace (i.e. init_net_ns)
 *   @drop_ns: drops a reference to namespace
 */
काष्ठा kobj_ns_type_operations अणु
	क्रमागत kobj_ns_type type;
	bool (*current_may_mount)(व्योम);
	व्योम *(*grab_current_ns)(व्योम);
	स्थिर व्योम *(*netlink_ns)(काष्ठा sock *sk);
	स्थिर व्योम *(*initial_ns)(व्योम);
	व्योम (*drop_ns)(व्योम *);
पूर्ण;

पूर्णांक kobj_ns_type_रेजिस्टर(स्थिर काष्ठा kobj_ns_type_operations *ops);
पूर्णांक kobj_ns_type_रेजिस्टरed(क्रमागत kobj_ns_type type);
स्थिर काष्ठा kobj_ns_type_operations *kobj_child_ns_ops(काष्ठा kobject *parent);
स्थिर काष्ठा kobj_ns_type_operations *kobj_ns_ops(काष्ठा kobject *kobj);

bool kobj_ns_current_may_mount(क्रमागत kobj_ns_type type);
व्योम *kobj_ns_grab_current(क्रमागत kobj_ns_type type);
स्थिर व्योम *kobj_ns_netlink(क्रमागत kobj_ns_type type, काष्ठा sock *sk);
स्थिर व्योम *kobj_ns_initial(क्रमागत kobj_ns_type type);
व्योम kobj_ns_drop(क्रमागत kobj_ns_type type, व्योम *ns);

#पूर्ण_अगर /* _LINUX_KOBJECT_NS_H */
