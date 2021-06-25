<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/mount.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/poll.h>
#समावेश <linux/ns_common.h>
#समावेश <linux/fs_pin.h>

काष्ठा mnt_namespace अणु
	काष्ठा ns_common	ns;
	काष्ठा mount *	root;
	/*
	 * Traversal and modअगरication of .list is रक्षित by either
	 * - taking namespace_sem क्रम ग_लिखो, OR
	 * - taking namespace_sem क्रम पढ़ो AND taking .ns_lock.
	 */
	काष्ठा list_head	list;
	spinlock_t		ns_lock;
	काष्ठा user_namespace	*user_ns;
	काष्ठा ucounts		*ucounts;
	u64			seq;	/* Sequence number to prevent loops */
	रुको_queue_head_t poll;
	u64 event;
	अचिन्हित पूर्णांक		mounts; /* # of mounts in the namespace */
	अचिन्हित पूर्णांक		pending_mounts;
पूर्ण __अक्रमomize_layout;

काष्ठा mnt_pcp अणु
	पूर्णांक mnt_count;
	पूर्णांक mnt_ग_लिखोrs;
पूर्ण;

काष्ठा mountpoपूर्णांक अणु
	काष्ठा hlist_node m_hash;
	काष्ठा dentry *m_dentry;
	काष्ठा hlist_head m_list;
	पूर्णांक m_count;
पूर्ण;

काष्ठा mount अणु
	काष्ठा hlist_node mnt_hash;
	काष्ठा mount *mnt_parent;
	काष्ठा dentry *mnt_mountpoपूर्णांक;
	काष्ठा vfsmount mnt;
	जोड़ अणु
		काष्ठा rcu_head mnt_rcu;
		काष्ठा llist_node mnt_llist;
	पूर्ण;
#अगर_घोषित CONFIG_SMP
	काष्ठा mnt_pcp __percpu *mnt_pcp;
#अन्यथा
	पूर्णांक mnt_count;
	पूर्णांक mnt_ग_लिखोrs;
#पूर्ण_अगर
	काष्ठा list_head mnt_mounts;	/* list of children, anchored here */
	काष्ठा list_head mnt_child;	/* and going through their mnt_child */
	काष्ठा list_head mnt_instance;	/* mount instance on sb->s_mounts */
	स्थिर अक्षर *mnt_devname;	/* Name of device e.g. /dev/dsk/hda1 */
	काष्ठा list_head mnt_list;
	काष्ठा list_head mnt_expire;	/* link in fs-specअगरic expiry list */
	काष्ठा list_head mnt_share;	/* circular list of shared mounts */
	काष्ठा list_head mnt_slave_list;/* list of slave mounts */
	काष्ठा list_head mnt_slave;	/* slave list entry */
	काष्ठा mount *mnt_master;	/* slave is on master->mnt_slave_list */
	काष्ठा mnt_namespace *mnt_ns;	/* containing namespace */
	काष्ठा mountpoपूर्णांक *mnt_mp;	/* where is it mounted */
	जोड़ अणु
		काष्ठा hlist_node mnt_mp_list;	/* list mounts with the same mountpoपूर्णांक */
		काष्ठा hlist_node mnt_umount;
	पूर्ण;
	काष्ठा list_head mnt_umounting; /* list entry क्रम umount propagation */
#अगर_घोषित CONFIG_FSNOTIFY
	काष्ठा fsnotअगरy_mark_connector __rcu *mnt_fsnotअगरy_marks;
	__u32 mnt_fsnotअगरy_mask;
#पूर्ण_अगर
	पूर्णांक mnt_id;			/* mount identअगरier */
	पूर्णांक mnt_group_id;		/* peer group identअगरier */
	पूर्णांक mnt_expiry_mark;		/* true अगर marked क्रम expiry */
	काष्ठा hlist_head mnt_pins;
	काष्ठा hlist_head mnt_stuck_children;
पूर्ण __अक्रमomize_layout;

#घोषणा MNT_NS_INTERNAL ERR_PTR(-EINVAL) /* distinct from any mnt_namespace */

अटल अंतरभूत काष्ठा mount *real_mount(काष्ठा vfsmount *mnt)
अणु
	वापस container_of(mnt, काष्ठा mount, mnt);
पूर्ण

अटल अंतरभूत पूर्णांक mnt_has_parent(काष्ठा mount *mnt)
अणु
	वापस mnt != mnt->mnt_parent;
पूर्ण

अटल अंतरभूत पूर्णांक is_mounted(काष्ठा vfsmount *mnt)
अणु
	/* neither detached nor पूर्णांकernal? */
	वापस !IS_ERR_OR_शून्य(real_mount(mnt)->mnt_ns);
पूर्ण

बाह्य काष्ठा mount *__lookup_mnt(काष्ठा vfsmount *, काष्ठा dentry *);

बाह्य पूर्णांक __legitimize_mnt(काष्ठा vfsmount *, अचिन्हित);
बाह्य bool legitimize_mnt(काष्ठा vfsmount *, अचिन्हित);

अटल अंतरभूत bool __path_is_mountpoपूर्णांक(स्थिर काष्ठा path *path)
अणु
	काष्ठा mount *m = __lookup_mnt(path->mnt, path->dentry);
	वापस m && likely(!(m->mnt.mnt_flags & MNT_SYNC_UMOUNT));
पूर्ण

बाह्य व्योम __detach_mounts(काष्ठा dentry *dentry);

अटल अंतरभूत व्योम detach_mounts(काष्ठा dentry *dentry)
अणु
	अगर (!d_mountpoपूर्णांक(dentry))
		वापस;
	__detach_mounts(dentry);
पूर्ण

अटल अंतरभूत व्योम get_mnt_ns(काष्ठा mnt_namespace *ns)
अणु
	refcount_inc(&ns->ns.count);
पूर्ण

बाह्य seqlock_t mount_lock;

काष्ठा proc_mounts अणु
	काष्ठा mnt_namespace *ns;
	काष्ठा path root;
	पूर्णांक (*show)(काष्ठा seq_file *, काष्ठा vfsmount *);
	काष्ठा mount cursor;
पूर्ण;

बाह्य स्थिर काष्ठा seq_operations mounts_op;

बाह्य bool __is_local_mountpoपूर्णांक(काष्ठा dentry *dentry);
अटल अंतरभूत bool is_local_mountpoपूर्णांक(काष्ठा dentry *dentry)
अणु
	अगर (!d_mountpoपूर्णांक(dentry))
		वापस false;

	वापस __is_local_mountpoपूर्णांक(dentry);
पूर्ण

अटल अंतरभूत bool is_anon_ns(काष्ठा mnt_namespace *ns)
अणु
	वापस ns->seq == 0;
पूर्ण

बाह्य व्योम mnt_cursor_del(काष्ठा mnt_namespace *ns, काष्ठा mount *cursor);
