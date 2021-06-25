<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kobject.h - generic kernel object infraकाष्ठाure.
 *
 * Copyright (c) 2002-2003 Patrick Mochel
 * Copyright (c) 2002-2003 Open Source Development Lअसल
 * Copyright (c) 2006-2008 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (c) 2006-2008 Novell Inc.
 *
 * Please पढ़ो Documentation/core-api/kobject.rst beक्रमe using the kobject
 * पूर्णांकerface, ESPECIALLY the parts about reference counts and object
 * deकाष्ठाors.
 */

#अगर_अघोषित _KOBJECT_H_
#घोषणा _KOBJECT_H_

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/compiler.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kref.h>
#समावेश <linux/kobject_ns.h>
#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/atomic.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/uidgid.h>

#घोषणा UEVENT_HELPER_PATH_LEN		256
#घोषणा UEVENT_NUM_ENVP			64	/* number of env poपूर्णांकers */
#घोषणा UEVENT_BUFFER_SIZE		2048	/* buffer क्रम the variables */

#अगर_घोषित CONFIG_UEVENT_HELPER
/* path to the userspace helper executed on an event */
बाह्य अक्षर uevent_helper[];
#पूर्ण_अगर

/* counter to tag the uevent, पढ़ो only except क्रम the kobject core */
बाह्य u64 uevent_seqnum;

/*
 * The actions here must match the index to the string array
 * in lib/kobject_uevent.c
 *
 * Do not add new actions here without checking with the driver-core
 * मुख्यtainers. Action strings are not meant to express subप्रणाली
 * or device specअगरic properties. In most हालs you want to send a
 * kobject_uevent_env(kobj, KOBJ_CHANGE, env) with additional event
 * specअगरic variables added to the event environment.
 */
क्रमागत kobject_action अणु
	KOBJ_ADD,
	KOBJ_REMOVE,
	KOBJ_CHANGE,
	KOBJ_MOVE,
	KOBJ_ONLINE,
	KOBJ_OFFLINE,
	KOBJ_BIND,
	KOBJ_UNBIND,
पूर्ण;

काष्ठा kobject अणु
	स्थिर अक्षर		*name;
	काष्ठा list_head	entry;
	काष्ठा kobject		*parent;
	काष्ठा kset		*kset;
	काष्ठा kobj_type	*ktype;
	काष्ठा kernfs_node	*sd; /* sysfs directory entry */
	काष्ठा kref		kref;
#अगर_घोषित CONFIG_DEBUG_KOBJECT_RELEASE
	काष्ठा delayed_work	release;
#पूर्ण_अगर
	अचिन्हित पूर्णांक state_initialized:1;
	अचिन्हित पूर्णांक state_in_sysfs:1;
	अचिन्हित पूर्णांक state_add_uevent_sent:1;
	अचिन्हित पूर्णांक state_हटाओ_uevent_sent:1;
	अचिन्हित पूर्णांक uevent_suppress:1;
पूर्ण;

बाह्य __म_लिखो(2, 3)
पूर्णांक kobject_set_name(काष्ठा kobject *kobj, स्थिर अक्षर *name, ...);
बाह्य __म_लिखो(2, 0)
पूर्णांक kobject_set_name_vargs(काष्ठा kobject *kobj, स्थिर अक्षर *fmt,
			   बहु_सूची vargs);

अटल अंतरभूत स्थिर अक्षर *kobject_name(स्थिर काष्ठा kobject *kobj)
अणु
	वापस kobj->name;
पूर्ण

बाह्य व्योम kobject_init(काष्ठा kobject *kobj, काष्ठा kobj_type *ktype);
बाह्य __म_लिखो(3, 4) __must_check
पूर्णांक kobject_add(काष्ठा kobject *kobj, काष्ठा kobject *parent,
		स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(4, 5) __must_check
पूर्णांक kobject_init_and_add(काष्ठा kobject *kobj,
			 काष्ठा kobj_type *ktype, काष्ठा kobject *parent,
			 स्थिर अक्षर *fmt, ...);

बाह्य व्योम kobject_del(काष्ठा kobject *kobj);

बाह्य काष्ठा kobject * __must_check kobject_create(व्योम);
बाह्य काष्ठा kobject * __must_check kobject_create_and_add(स्थिर अक्षर *name,
						काष्ठा kobject *parent);

बाह्य पूर्णांक __must_check kobject_नाम(काष्ठा kobject *, स्थिर अक्षर *new_name);
बाह्य पूर्णांक __must_check kobject_move(काष्ठा kobject *, काष्ठा kobject *);

बाह्य काष्ठा kobject *kobject_get(काष्ठा kobject *kobj);
बाह्य काष्ठा kobject * __must_check kobject_get_unless_zero(
						काष्ठा kobject *kobj);
बाह्य व्योम kobject_put(काष्ठा kobject *kobj);

बाह्य स्थिर व्योम *kobject_namespace(काष्ठा kobject *kobj);
बाह्य व्योम kobject_get_ownership(काष्ठा kobject *kobj,
				  kuid_t *uid, kgid_t *gid);
बाह्य अक्षर *kobject_get_path(काष्ठा kobject *kobj, gfp_t flag);

/**
 * kobject_has_children - Returns whether a kobject has children.
 * @kobj: the object to test
 *
 * This will वापस whether a kobject has other kobjects as children.
 *
 * It करोes NOT account क्रम the presence of attribute files, only sub
 * directories. It also assumes there is no concurrent addition or
 * removal of such children, and thus relies on बाह्यal locking.
 */
अटल अंतरभूत bool kobject_has_children(काष्ठा kobject *kobj)
अणु
	WARN_ON_ONCE(kref_पढ़ो(&kobj->kref) == 0);

	वापस kobj->sd && kobj->sd->dir.subdirs;
पूर्ण

काष्ठा kobj_type अणु
	व्योम (*release)(काष्ठा kobject *kobj);
	स्थिर काष्ठा sysfs_ops *sysfs_ops;
	काष्ठा attribute **शेष_attrs;	/* use शेष_groups instead */
	स्थिर काष्ठा attribute_group **शेष_groups;
	स्थिर काष्ठा kobj_ns_type_operations *(*child_ns_type)(काष्ठा kobject *kobj);
	स्थिर व्योम *(*namespace)(काष्ठा kobject *kobj);
	व्योम (*get_ownership)(काष्ठा kobject *kobj, kuid_t *uid, kgid_t *gid);
पूर्ण;

काष्ठा kobj_uevent_env अणु
	अक्षर *argv[3];
	अक्षर *envp[UEVENT_NUM_ENVP];
	पूर्णांक envp_idx;
	अक्षर buf[UEVENT_BUFFER_SIZE];
	पूर्णांक buflen;
पूर्ण;

काष्ठा kset_uevent_ops अणु
	पूर्णांक (* स्थिर filter)(काष्ठा kset *kset, काष्ठा kobject *kobj);
	स्थिर अक्षर *(* स्थिर name)(काष्ठा kset *kset, काष्ठा kobject *kobj);
	पूर्णांक (* स्थिर uevent)(काष्ठा kset *kset, काष्ठा kobject *kobj,
		      काष्ठा kobj_uevent_env *env);
पूर्ण;

काष्ठा kobj_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

बाह्य स्थिर काष्ठा sysfs_ops kobj_sysfs_ops;

काष्ठा sock;

/**
 * काष्ठा kset - a set of kobjects of a specअगरic type, beदीर्घing to a specअगरic subप्रणाली.
 *
 * A kset defines a group of kobjects.  They can be inभागidually
 * dअगरferent "types" but overall these kobjects all want to be grouped
 * together and operated on in the same manner.  ksets are used to
 * define the attribute callbacks and other common events that happen to
 * a kobject.
 *
 * @list: the list of all kobjects क्रम this kset
 * @list_lock: a lock क्रम iterating over the kobjects
 * @kobj: the embedded kobject क्रम this kset (recursion, isn't it fun...)
 * @uevent_ops: the set of uevent operations क्रम this kset.  These are
 * called whenever a kobject has something happen to it so that the kset
 * can add new environment variables, or filter out the uevents अगर so
 * desired.
 */
काष्ठा kset अणु
	काष्ठा list_head list;
	spinlock_t list_lock;
	काष्ठा kobject kobj;
	स्थिर काष्ठा kset_uevent_ops *uevent_ops;
पूर्ण __अक्रमomize_layout;

बाह्य व्योम kset_init(काष्ठा kset *kset);
बाह्य पूर्णांक __must_check kset_रेजिस्टर(काष्ठा kset *kset);
बाह्य व्योम kset_unरेजिस्टर(काष्ठा kset *kset);
बाह्य काष्ठा kset * __must_check kset_create_and_add(स्थिर अक्षर *name,
						स्थिर काष्ठा kset_uevent_ops *u,
						काष्ठा kobject *parent_kobj);

अटल अंतरभूत काष्ठा kset *to_kset(काष्ठा kobject *kobj)
अणु
	वापस kobj ? container_of(kobj, काष्ठा kset, kobj) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा kset *kset_get(काष्ठा kset *k)
अणु
	वापस k ? to_kset(kobject_get(&k->kobj)) : शून्य;
पूर्ण

अटल अंतरभूत व्योम kset_put(काष्ठा kset *k)
अणु
	kobject_put(&k->kobj);
पूर्ण

अटल अंतरभूत काष्ठा kobj_type *get_ktype(काष्ठा kobject *kobj)
अणु
	वापस kobj->ktype;
पूर्ण

बाह्य काष्ठा kobject *kset_find_obj(काष्ठा kset *, स्थिर अक्षर *);

/* The global /sys/kernel/ kobject क्रम people to chain off of */
बाह्य काष्ठा kobject *kernel_kobj;
/* The global /sys/kernel/mm/ kobject क्रम people to chain off of */
बाह्य काष्ठा kobject *mm_kobj;
/* The global /sys/hypervisor/ kobject क्रम people to chain off of */
बाह्य काष्ठा kobject *hypervisor_kobj;
/* The global /sys/घातer/ kobject क्रम people to chain off of */
बाह्य काष्ठा kobject *घातer_kobj;
/* The global /sys/firmware/ kobject क्रम people to chain off of */
बाह्य काष्ठा kobject *firmware_kobj;

पूर्णांक kobject_uevent(काष्ठा kobject *kobj, क्रमागत kobject_action action);
पूर्णांक kobject_uevent_env(काष्ठा kobject *kobj, क्रमागत kobject_action action,
			अक्षर *envp[]);
पूर्णांक kobject_synth_uevent(काष्ठा kobject *kobj, स्थिर अक्षर *buf, माप_प्रकार count);

__म_लिखो(2, 3)
पूर्णांक add_uevent_var(काष्ठा kobj_uevent_env *env, स्थिर अक्षर *क्रमmat, ...);

#पूर्ण_अगर /* _KOBJECT_H_ */
