<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_USER_NAMESPACE_H
#घोषणा _LINUX_USER_NAMESPACE_H

#समावेश <linux/kref.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/ns_common.h>
#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/err.h>

#घोषणा UID_GID_MAP_MAX_BASE_EXTENTS 5
#घोषणा UID_GID_MAP_MAX_EXTENTS 340

काष्ठा uid_gid_extent अणु
	u32 first;
	u32 lower_first;
	u32 count;
पूर्ण;

काष्ठा uid_gid_map अणु /* 64 bytes -- 1 cache line */
	u32 nr_extents;
	जोड़ अणु
		काष्ठा uid_gid_extent extent[UID_GID_MAP_MAX_BASE_EXTENTS];
		काष्ठा अणु
			काष्ठा uid_gid_extent *क्रमward;
			काष्ठा uid_gid_extent *reverse;
		पूर्ण;
	पूर्ण;
पूर्ण;

#घोषणा USERNS_SETGROUPS_ALLOWED 1UL

#घोषणा USERNS_INIT_FLAGS USERNS_SETGROUPS_ALLOWED

काष्ठा ucounts;

क्रमागत ucount_type अणु
	UCOUNT_USER_NAMESPACES,
	UCOUNT_PID_NAMESPACES,
	UCOUNT_UTS_NAMESPACES,
	UCOUNT_IPC_NAMESPACES,
	UCOUNT_NET_NAMESPACES,
	UCOUNT_MNT_NAMESPACES,
	UCOUNT_CGROUP_NAMESPACES,
	UCOUNT_TIME_NAMESPACES,
#अगर_घोषित CONFIG_INOTIFY_USER
	UCOUNT_INOTIFY_INSTANCES,
	UCOUNT_INOTIFY_WATCHES,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FANOTIFY
	UCOUNT_FANOTIFY_GROUPS,
	UCOUNT_FANOTIFY_MARKS,
#पूर्ण_अगर
	UCOUNT_COUNTS,
पूर्ण;

काष्ठा user_namespace अणु
	काष्ठा uid_gid_map	uid_map;
	काष्ठा uid_gid_map	gid_map;
	काष्ठा uid_gid_map	projid_map;
	काष्ठा user_namespace	*parent;
	पूर्णांक			level;
	kuid_t			owner;
	kgid_t			group;
	काष्ठा ns_common	ns;
	अचिन्हित दीर्घ		flags;
	/* parent_could_setfcap: true अगर the creator अगर this ns had CAP_SETFCAP
	 * in its effective capability set at the child ns creation समय. */
	bool			parent_could_setfcap;

#अगर_घोषित CONFIG_KEYS
	/* List of joinable keyrings in this namespace.  Modअगरication access of
	 * these poपूर्णांकers is controlled by keyring_sem.  Once
	 * user_keyring_रेजिस्टर is set, it won't be changed, so it can be
	 * accessed directly with READ_ONCE().
	 */
	काष्ठा list_head	keyring_name_list;
	काष्ठा key		*user_keyring_रेजिस्टर;
	काष्ठा rw_semaphore	keyring_sem;
#पूर्ण_अगर

	/* Register of per-UID persistent keyrings क्रम this namespace */
#अगर_घोषित CONFIG_PERSISTENT_KEYRINGS
	काष्ठा key		*persistent_keyring_रेजिस्टर;
#पूर्ण_अगर
	काष्ठा work_काष्ठा	work;
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_set	set;
	काष्ठा ctl_table_header *sysctls;
#पूर्ण_अगर
	काष्ठा ucounts		*ucounts;
	पूर्णांक ucount_max[UCOUNT_COUNTS];
पूर्ण __अक्रमomize_layout;

काष्ठा ucounts अणु
	काष्ठा hlist_node node;
	काष्ठा user_namespace *ns;
	kuid_t uid;
	पूर्णांक count;
	atomic_t ucount[UCOUNT_COUNTS];
पूर्ण;

बाह्य काष्ठा user_namespace init_user_ns;

bool setup_userns_sysctls(काष्ठा user_namespace *ns);
व्योम retire_userns_sysctls(काष्ठा user_namespace *ns);
काष्ठा ucounts *inc_ucount(काष्ठा user_namespace *ns, kuid_t uid, क्रमागत ucount_type type);
व्योम dec_ucount(काष्ठा ucounts *ucounts, क्रमागत ucount_type type);

#अगर_घोषित CONFIG_USER_NS

अटल अंतरभूत काष्ठा user_namespace *get_user_ns(काष्ठा user_namespace *ns)
अणु
	अगर (ns)
		refcount_inc(&ns->ns.count);
	वापस ns;
पूर्ण

बाह्य पूर्णांक create_user_ns(काष्ठा cred *new);
बाह्य पूर्णांक unshare_userns(अचिन्हित दीर्घ unshare_flags, काष्ठा cred **new_cred);
बाह्य व्योम __put_user_ns(काष्ठा user_namespace *ns);

अटल अंतरभूत व्योम put_user_ns(काष्ठा user_namespace *ns)
अणु
	अगर (ns && refcount_dec_and_test(&ns->ns.count))
		__put_user_ns(ns);
पूर्ण

काष्ठा seq_operations;
बाह्य स्थिर काष्ठा seq_operations proc_uid_seq_operations;
बाह्य स्थिर काष्ठा seq_operations proc_gid_seq_operations;
बाह्य स्थिर काष्ठा seq_operations proc_projid_seq_operations;
बाह्य sमाप_प्रकार proc_uid_map_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
बाह्य sमाप_प्रकार proc_gid_map_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
बाह्य sमाप_प्रकार proc_projid_map_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
बाह्य sमाप_प्रकार proc_setgroups_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
बाह्य पूर्णांक proc_setgroups_show(काष्ठा seq_file *m, व्योम *v);
बाह्य bool userns_may_setgroups(स्थिर काष्ठा user_namespace *ns);
बाह्य bool in_userns(स्थिर काष्ठा user_namespace *ancestor,
		       स्थिर काष्ठा user_namespace *child);
बाह्य bool current_in_userns(स्थिर काष्ठा user_namespace *target_ns);
काष्ठा ns_common *ns_get_owner(काष्ठा ns_common *ns);
#अन्यथा

अटल अंतरभूत काष्ठा user_namespace *get_user_ns(काष्ठा user_namespace *ns)
अणु
	वापस &init_user_ns;
पूर्ण

अटल अंतरभूत पूर्णांक create_user_ns(काष्ठा cred *new)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक unshare_userns(अचिन्हित दीर्घ unshare_flags,
				 काष्ठा cred **new_cred)
अणु
	अगर (unshare_flags & CLONE_NEWUSER)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम put_user_ns(काष्ठा user_namespace *ns)
अणु
पूर्ण

अटल अंतरभूत bool userns_may_setgroups(स्थिर काष्ठा user_namespace *ns)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool in_userns(स्थिर काष्ठा user_namespace *ancestor,
			     स्थिर काष्ठा user_namespace *child)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool current_in_userns(स्थिर काष्ठा user_namespace *target_ns)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत काष्ठा ns_common *ns_get_owner(काष्ठा ns_common *ns)
अणु
	वापस ERR_PTR(-EPERM);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_USER_H */
