<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Fileप्रणाली access notअगरication क्रम Linux
 *
 *  Copyright (C) 2008 Red Hat, Inc., Eric Paris <eparis@redhat.com>
 */

#अगर_अघोषित __LINUX_FSNOTIFY_BACKEND_H
#घोषणा __LINUX_FSNOTIFY_BACKEND_H

#अगर_घोषित __KERNEL__

#समावेश <linux/idr.h> /* inotअगरy uses this */
#समावेश <linux/fs.h> /* काष्ठा inode */
#समावेश <linux/list.h>
#समावेश <linux/path.h> /* काष्ठा path */
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/refcount.h>

/*
 * IN_* from inotfy.h lines up EXACTLY with FS_*, this is so we can easily
 * convert between them.  dnotअगरy only needs conversion at watch creation
 * so no perf loss there.  fanotअगरy isn't defined yet, so it can use the
 * wholes अगर it needs more events.
 */
#घोषणा FS_ACCESS		0x00000001	/* File was accessed */
#घोषणा FS_MODIFY		0x00000002	/* File was modअगरied */
#घोषणा FS_ATTRIB		0x00000004	/* Metadata changed */
#घोषणा FS_CLOSE_WRITE		0x00000008	/* Writtable file was बंदd */
#घोषणा FS_CLOSE_NOWRITE	0x00000010	/* Unwrittable file बंदd */
#घोषणा FS_OPEN			0x00000020	/* File was खोलोed */
#घोषणा FS_MOVED_FROM		0x00000040	/* File was moved from X */
#घोषणा FS_MOVED_TO		0x00000080	/* File was moved to Y */
#घोषणा FS_CREATE		0x00000100	/* Subfile was created */
#घोषणा FS_DELETE		0x00000200	/* Subfile was deleted */
#घोषणा FS_DELETE_SELF		0x00000400	/* Self was deleted */
#घोषणा FS_MOVE_SELF		0x00000800	/* Self was moved */
#घोषणा FS_OPEN_EXEC		0x00001000	/* File was खोलोed क्रम exec */

#घोषणा FS_UNMOUNT		0x00002000	/* inode on umount fs */
#घोषणा FS_Q_OVERFLOW		0x00004000	/* Event queued overflowed */
#घोषणा FS_IN_IGNORED		0x00008000	/* last inotअगरy event here */

#घोषणा FS_OPEN_PERM		0x00010000	/* खोलो event in an permission hook */
#घोषणा FS_ACCESS_PERM		0x00020000	/* access event in a permissions hook */
#घोषणा FS_OPEN_EXEC_PERM	0x00040000	/* खोलो/exec event in a permission hook */

#घोषणा FS_EXCL_UNLINK		0x04000000	/* करो not send events अगर object is unlinked */
/*
 * Set on inode mark that cares about things that happen to its children.
 * Always set क्रम dnotअगरy and inotअगरy.
 * Set on inode/sb/mount marks that care about parent/name info.
 */
#घोषणा FS_EVENT_ON_CHILD	0x08000000

#घोषणा FS_DN_RENAME		0x10000000	/* file नामd */
#घोषणा FS_DN_MULTISHOT		0x20000000	/* dnotअगरy multishot */
#घोषणा FS_ISसूची		0x40000000	/* event occurred against dir */
#घोषणा FS_IN_ONESHOT		0x80000000	/* only send event once */

#घोषणा FS_MOVE			(FS_MOVED_FROM | FS_MOVED_TO)

/*
 * Directory entry modअगरication events - reported only to directory
 * where entry is modअगरied and not to a watching parent.
 * The watching parent may get an FS_ATTRIB|FS_EVENT_ON_CHILD event
 * when a directory entry inside a child subdir changes.
 */
#घोषणा ALL_FSNOTIFY_सूचीENT_EVENTS	(FS_CREATE | FS_DELETE | FS_MOVE)

#घोषणा ALL_FSNOTIFY_PERM_EVENTS (FS_OPEN_PERM | FS_ACCESS_PERM | \
				  FS_OPEN_EXEC_PERM)

/*
 * This is a list of all events that may get sent to a parent that is watching
 * with flag FS_EVENT_ON_CHILD based on fs event on a child of that directory.
 */
#घोषणा FS_EVENTS_POSS_ON_CHILD   (ALL_FSNOTIFY_PERM_EVENTS | \
				   FS_ACCESS | FS_MODIFY | FS_ATTRIB | \
				   FS_CLOSE_WRITE | FS_CLOSE_NOWRITE | \
				   FS_OPEN | FS_OPEN_EXEC)

/*
 * This is a list of all events that may get sent with the parent inode as the
 * @to_tell argument of fsnotअगरy().
 * It may include events that can be sent to an inode/sb/mount mark, but cannot
 * be sent to a parent watching children.
 */
#घोषणा FS_EVENTS_POSS_TO_PARENT (FS_EVENTS_POSS_ON_CHILD)

/* Events that can be reported to backends */
#घोषणा ALL_FSNOTIFY_EVENTS (ALL_FSNOTIFY_सूचीENT_EVENTS | \
			     FS_EVENTS_POSS_ON_CHILD | \
			     FS_DELETE_SELF | FS_MOVE_SELF | FS_DN_RENAME | \
			     FS_UNMOUNT | FS_Q_OVERFLOW | FS_IN_IGNORED)

/* Extra flags that may be reported with event or control handling of events */
#घोषणा ALL_FSNOTIFY_FLAGS  (FS_EXCL_UNLINK | FS_ISसूची | FS_IN_ONESHOT | \
			     FS_DN_MULTISHOT | FS_EVENT_ON_CHILD)

#घोषणा ALL_FSNOTIFY_BITS   (ALL_FSNOTIFY_EVENTS | ALL_FSNOTIFY_FLAGS)

काष्ठा fsnotअगरy_group;
काष्ठा fsnotअगरy_event;
काष्ठा fsnotअगरy_mark;
काष्ठा fsnotअगरy_event_निजी_data;
काष्ठा fsnotअगरy_fname;
काष्ठा fsnotअगरy_iter_info;

काष्ठा mem_cgroup;

/*
 * Each group much define these ops.  The fsnotअगरy infraकाष्ठाure will call
 * these operations क्रम each relevant group.
 *
 * handle_event - मुख्य call क्रम a group to handle an fs event
 * @group:	group to notअगरy
 * @mask:	event type and flags
 * @data:	object that event happened on
 * @data_type:	type of object क्रम fanotअगरy_data_XXX() accessors
 * @dir:	optional directory associated with event -
 *		अगर @file_name is not शून्य, this is the directory that
 *		@file_name is relative to
 * @file_name:	optional file name associated with event
 * @cookie:	inotअगरy नाम cookie
 * @iter_info:	array of marks from this group that are पूर्णांकerested in the event
 *
 * handle_inode_event - simple variant of handle_event() क्रम groups that only
 *		have inode marks and करोn't have ignore mask
 * @mark:	mark to notअगरy
 * @mask:	event type and flags
 * @inode:	inode that event happened on
 * @dir:	optional directory associated with event -
 *		अगर @file_name is not शून्य, this is the directory that
 *		@file_name is relative to.
 * @file_name:	optional file name associated with event
 * @cookie:	inotअगरy नाम cookie
 *
 * मुक्त_group_priv - called when a group refcnt hits 0 to clean up the निजी जोड़
 * मुक्तing_mark - called when a mark is being destroyed क्रम some reason.  The group
 *		MUST be holding a reference on each mark and that reference must be
 *		dropped in this function.  inotअगरy uses this function to send
 *		userspace messages that marks have been हटाओd.
 */
काष्ठा fsnotअगरy_ops अणु
	पूर्णांक (*handle_event)(काष्ठा fsnotअगरy_group *group, u32 mask,
			    स्थिर व्योम *data, पूर्णांक data_type, काष्ठा inode *dir,
			    स्थिर काष्ठा qstr *file_name, u32 cookie,
			    काष्ठा fsnotअगरy_iter_info *iter_info);
	पूर्णांक (*handle_inode_event)(काष्ठा fsnotअगरy_mark *mark, u32 mask,
			    काष्ठा inode *inode, काष्ठा inode *dir,
			    स्थिर काष्ठा qstr *file_name, u32 cookie);
	व्योम (*मुक्त_group_priv)(काष्ठा fsnotअगरy_group *group);
	व्योम (*मुक्तing_mark)(काष्ठा fsnotअगरy_mark *mark, काष्ठा fsnotअगरy_group *group);
	व्योम (*मुक्त_event)(काष्ठा fsnotअगरy_event *event);
	/* called on final put+मुक्त to मुक्त memory */
	व्योम (*मुक्त_mark)(काष्ठा fsnotअगरy_mark *mark);
पूर्ण;

/*
 * all of the inक्रमmation about the original object we want to now send to
 * a group.  If you want to carry more info from the accessing task to the
 * listener this काष्ठाure is where you need to be adding fields.
 */
काष्ठा fsnotअगरy_event अणु
	काष्ठा list_head list;
पूर्ण;

/*
 * A group is a "thing" that wants to receive notअगरication about fileप्रणाली
 * events.  The mask holds the subset of event types this group cares about.
 * refcnt on a group is up to the implementor and at any moment अगर it goes 0
 * everything will be cleaned up.
 */
काष्ठा fsnotअगरy_group अणु
	स्थिर काष्ठा fsnotअगरy_ops *ops;	/* how this group handles things */

	/*
	 * How the refcnt is used is up to each group.  When the refcnt hits 0
	 * fsnotअगरy will clean up all of the resources associated with this group.
	 * As an example, the dnotअगरy group will always have a refcnt=1 and that
	 * will never change.  Inotअगरy, on the other hand, has a group per
	 * inotअगरy_init() and the refcnt will hit 0 only when that fd has been
	 * बंदd.
	 */
	refcount_t refcnt;		/* things with पूर्णांकerest in this group */

	/* needed to send notअगरication to userspace */
	spinlock_t notअगरication_lock;		/* protect the notअगरication_list */
	काष्ठा list_head notअगरication_list;	/* list of event_holder this group needs to send to userspace */
	रुको_queue_head_t notअगरication_रुकोq;	/* पढ़ो() on the notअगरication file blocks on this रुकोq */
	अचिन्हित पूर्णांक q_len;			/* events on the queue */
	अचिन्हित पूर्णांक max_events;		/* maximum events allowed on the list */
	/*
	 * Valid fsnotअगरy group priorities.  Events are send in order from highest
	 * priority to lowest priority.  We शेष to the lowest priority.
	 */
	#घोषणा FS_PRIO_0	0 /* normal notअगरiers, no permissions */
	#घोषणा FS_PRIO_1	1 /* fanotअगरy content based access control */
	#घोषणा FS_PRIO_2	2 /* fanotअगरy pre-content access */
	अचिन्हित पूर्णांक priority;
	bool shutकरोwn;		/* group is being shut करोwn, करोn't queue more events */

	/* stores all fastpath marks assoc with this group so they can be cleaned on unरेजिस्टर */
	काष्ठा mutex mark_mutex;	/* protect marks_list */
	atomic_t user_रुकोs;		/* Number of tasks रुकोing क्रम user
					 * response */
	काष्ठा list_head marks_list;	/* all inode marks क्रम this group */

	काष्ठा fasync_काष्ठा *fsn_fa;    /* async notअगरication */

	काष्ठा fsnotअगरy_event *overflow_event;	/* Event we queue when the
						 * notअगरication list is too
						 * full */

	काष्ठा mem_cgroup *memcg;	/* memcg to अक्षरge allocations */

	/* groups can define निजी fields here or use the व्योम *निजी */
	जोड़ अणु
		व्योम *निजी;
#अगर_घोषित CONFIG_INOTIFY_USER
		काष्ठा inotअगरy_group_निजी_data अणु
			spinlock_t	idr_lock;
			काष्ठा idr      idr;
			काष्ठा ucounts *ucounts;
		पूर्ण inotअगरy_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FANOTIFY
		काष्ठा fanotअगरy_group_निजी_data अणु
			/* Hash table of events क्रम merge */
			काष्ठा hlist_head *merge_hash;
			/* allows a group to block रुकोing क्रम a userspace response */
			काष्ठा list_head access_list;
			रुको_queue_head_t access_रुकोq;
			पूर्णांक flags;           /* flags from fanotअगरy_init() */
			पूर्णांक f_flags; /* event_f_flags from fanotअगरy_init() */
			काष्ठा ucounts *ucounts;
		पूर्ण fanotअगरy_data;
#पूर्ण_अगर /* CONFIG_FANOTIFY */
	पूर्ण;
पूर्ण;

/* When calling fsnotअगरy tell it अगर the data is a path or inode */
क्रमागत fsnotअगरy_data_type अणु
	FSNOTIFY_EVENT_NONE,
	FSNOTIFY_EVENT_PATH,
	FSNOTIFY_EVENT_INODE,
पूर्ण;

अटल अंतरभूत काष्ठा inode *fsnotअगरy_data_inode(स्थिर व्योम *data, पूर्णांक data_type)
अणु
	चयन (data_type) अणु
	हाल FSNOTIFY_EVENT_INODE:
		वापस (काष्ठा inode *)data;
	हाल FSNOTIFY_EVENT_PATH:
		वापस d_inode(((स्थिर काष्ठा path *)data)->dentry);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर काष्ठा path *fsnotअगरy_data_path(स्थिर व्योम *data,
						    पूर्णांक data_type)
अणु
	चयन (data_type) अणु
	हाल FSNOTIFY_EVENT_PATH:
		वापस data;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

क्रमागत fsnotअगरy_obj_type अणु
	FSNOTIFY_OBJ_TYPE_INODE,
	FSNOTIFY_OBJ_TYPE_PARENT,
	FSNOTIFY_OBJ_TYPE_VFSMOUNT,
	FSNOTIFY_OBJ_TYPE_SB,
	FSNOTIFY_OBJ_TYPE_COUNT,
	FSNOTIFY_OBJ_TYPE_DETACHED = FSNOTIFY_OBJ_TYPE_COUNT
पूर्ण;

#घोषणा FSNOTIFY_OBJ_TYPE_INODE_FL	(1U << FSNOTIFY_OBJ_TYPE_INODE)
#घोषणा FSNOTIFY_OBJ_TYPE_PARENT_FL	(1U << FSNOTIFY_OBJ_TYPE_PARENT)
#घोषणा FSNOTIFY_OBJ_TYPE_VFSMOUNT_FL	(1U << FSNOTIFY_OBJ_TYPE_VFSMOUNT)
#घोषणा FSNOTIFY_OBJ_TYPE_SB_FL		(1U << FSNOTIFY_OBJ_TYPE_SB)
#घोषणा FSNOTIFY_OBJ_ALL_TYPES_MASK	((1U << FSNOTIFY_OBJ_TYPE_COUNT) - 1)

अटल अंतरभूत bool fsnotअगरy_valid_obj_type(अचिन्हित पूर्णांक type)
अणु
	वापस (type < FSNOTIFY_OBJ_TYPE_COUNT);
पूर्ण

काष्ठा fsnotअगरy_iter_info अणु
	काष्ठा fsnotअगरy_mark *marks[FSNOTIFY_OBJ_TYPE_COUNT];
	अचिन्हित पूर्णांक report_mask;
	पूर्णांक srcu_idx;
पूर्ण;

अटल अंतरभूत bool fsnotअगरy_iter_should_report_type(
		काष्ठा fsnotअगरy_iter_info *iter_info, पूर्णांक type)
अणु
	वापस (iter_info->report_mask & (1U << type));
पूर्ण

अटल अंतरभूत व्योम fsnotअगरy_iter_set_report_type(
		काष्ठा fsnotअगरy_iter_info *iter_info, पूर्णांक type)
अणु
	iter_info->report_mask |= (1U << type);
पूर्ण

अटल अंतरभूत व्योम fsnotअगरy_iter_set_report_type_mark(
		काष्ठा fsnotअगरy_iter_info *iter_info, पूर्णांक type,
		काष्ठा fsnotअगरy_mark *mark)
अणु
	iter_info->marks[type] = mark;
	iter_info->report_mask |= (1U << type);
पूर्ण

#घोषणा FSNOTIFY_ITER_FUNCS(name, NAME) \
अटल अंतरभूत काष्ठा fsnotअगरy_mark *fsnotअगरy_iter_##name##_mark( \
		काष्ठा fsnotअगरy_iter_info *iter_info) \
अणु \
	वापस (iter_info->report_mask & FSNOTIFY_OBJ_TYPE_##NAME##_FL) ? \
		iter_info->marks[FSNOTIFY_OBJ_TYPE_##NAME] : शून्य; \
पूर्ण

FSNOTIFY_ITER_FUNCS(inode, INODE)
FSNOTIFY_ITER_FUNCS(parent, PARENT)
FSNOTIFY_ITER_FUNCS(vfsmount, VFSMOUNT)
FSNOTIFY_ITER_FUNCS(sb, SB)

#घोषणा fsnotअगरy_क्रमeach_obj_type(type) \
	क्रम (type = 0; type < FSNOTIFY_OBJ_TYPE_COUNT; type++)

/*
 * fsnotअगरy_connp_t is what we embed in objects which connector can be attached
 * to. fsnotअगरy_connp_t * is how we refer from connector back to object.
 */
काष्ठा fsnotअगरy_mark_connector;
प्रकार काष्ठा fsnotअगरy_mark_connector __rcu *fsnotअगरy_connp_t;

/*
 * Inode/vfsmount/sb poपूर्णांक to this काष्ठाure which tracks all marks attached to
 * the inode/vfsmount/sb. The reference to inode/vfsmount/sb is held by this
 * काष्ठाure. We destroy this काष्ठाure when there are no more marks attached
 * to it. The काष्ठाure is रक्षित by fsnotअगरy_mark_srcu.
 */
काष्ठा fsnotअगरy_mark_connector अणु
	spinlock_t lock;
	अचिन्हित लघु type;	/* Type of object [lock] */
#घोषणा FSNOTIFY_CONN_FLAG_HAS_FSID	0x01
	अचिन्हित लघु flags;	/* flags [lock] */
	__kernel_fsid_t fsid;	/* fsid of fileप्रणाली containing object */
	जोड़ अणु
		/* Object poपूर्णांकer [lock] */
		fsnotअगरy_connp_t *obj;
		/* Used listing heads to मुक्त after srcu period expires */
		काष्ठा fsnotअगरy_mark_connector *destroy_next;
	पूर्ण;
	काष्ठा hlist_head list;
पूर्ण;

/*
 * A mark is simply an object attached to an in core inode which allows an
 * fsnotअगरy listener to indicate they are either no दीर्घer पूर्णांकerested in events
 * of a type matching mask or only पूर्णांकerested in those events.
 *
 * These are flushed when an inode is evicted from core and may be flushed
 * when the inode is modअगरied (as seen by fsnotअगरy_access).  Some fsnotअगरy
 * users (such as dnotअगरy) will flush these when the खोलो fd is बंदd and not
 * at inode eviction or modअगरication.
 *
 * Text in brackets is showing the lock(s) protecting modअगरications of a
 * particular entry. obj_lock means either inode->i_lock or
 * mnt->mnt_root->d_lock depending on the mark type.
 */
काष्ठा fsnotअगरy_mark अणु
	/* Mask this mark is क्रम [mark->lock, group->mark_mutex] */
	__u32 mask;
	/* We hold one क्रम presence in g_list. Also one ref क्रम each 'thing'
	 * in kernel that found and may be using this mark. */
	refcount_t refcnt;
	/* Group this mark is क्रम. Set on mark creation, stable until last ref
	 * is dropped */
	काष्ठा fsnotअगरy_group *group;
	/* List of marks by group->marks_list. Also reused क्रम queueing
	 * mark पूर्णांकo destroy_list when it's रुकोing क्रम the end of SRCU period
	 * beक्रमe it can be मुक्तd. [group->mark_mutex] */
	काष्ठा list_head g_list;
	/* Protects inode / mnt poपूर्णांकers, flags, masks */
	spinlock_t lock;
	/* List of marks क्रम inode / vfsmount [connector->lock, mark ref] */
	काष्ठा hlist_node obj_list;
	/* Head of list of marks क्रम an object [mark ref] */
	काष्ठा fsnotअगरy_mark_connector *connector;
	/* Events types to ignore [mark->lock, group->mark_mutex] */
	__u32 ignored_mask;
#घोषणा FSNOTIFY_MARK_FLAG_IGNORED_SURV_MODIFY	0x01
#घोषणा FSNOTIFY_MARK_FLAG_ALIVE		0x02
#घोषणा FSNOTIFY_MARK_FLAG_ATTACHED		0x04
	अचिन्हित पूर्णांक flags;		/* flags [mark->lock] */
पूर्ण;

#अगर_घोषित CONFIG_FSNOTIFY

/* called from the vfs helpers */

/* मुख्य fsnotअगरy call to send events */
बाह्य पूर्णांक fsnotअगरy(__u32 mask, स्थिर व्योम *data, पूर्णांक data_type,
		    काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
		    काष्ठा inode *inode, u32 cookie);
बाह्य पूर्णांक __fsnotअगरy_parent(काष्ठा dentry *dentry, __u32 mask, स्थिर व्योम *data,
			   पूर्णांक data_type);
बाह्य व्योम __fsnotअगरy_inode_delete(काष्ठा inode *inode);
बाह्य व्योम __fsnotअगरy_vfsmount_delete(काष्ठा vfsmount *mnt);
बाह्य व्योम fsnotअगरy_sb_delete(काष्ठा super_block *sb);
बाह्य u32 fsnotअगरy_get_cookie(व्योम);

अटल अंतरभूत __u32 fsnotअगरy_parent_needed_mask(__u32 mask)
अणु
	/* FS_EVENT_ON_CHILD is set on marks that want parent/name info */
	अगर (!(mask & FS_EVENT_ON_CHILD))
		वापस 0;
	/*
	 * This object might be watched by a mark that cares about parent/name
	 * info, करोes it care about the specअगरic set of events that can be
	 * reported with parent/name info?
	 */
	वापस mask & FS_EVENTS_POSS_TO_PARENT;
पूर्ण

अटल अंतरभूत पूर्णांक fsnotअगरy_inode_watches_children(काष्ठा inode *inode)
अणु
	/* FS_EVENT_ON_CHILD is set अगर the inode may care */
	अगर (!(inode->i_fsnotअगरy_mask & FS_EVENT_ON_CHILD))
		वापस 0;
	/* this inode might care about child events, करोes it care about the
	 * specअगरic set of events that can happen on a child? */
	वापस inode->i_fsnotअगरy_mask & FS_EVENTS_POSS_ON_CHILD;
पूर्ण

/*
 * Update the dentry with a flag indicating the पूर्णांकerest of its parent to receive
 * fileप्रणाली events when those events happens to this dentry->d_inode.
 */
अटल अंतरभूत व्योम fsnotअगरy_update_flags(काष्ठा dentry *dentry)
अणु
	निश्चित_spin_locked(&dentry->d_lock);

	/*
	 * Serialisation of setting PARENT_WATCHED on the dentries is provided
	 * by d_lock. If inotअगरy_inode_watched changes after we have taken
	 * d_lock, the following __fsnotअगरy_update_child_dentry_flags call will
	 * find our entry, so it will spin until we complete here, and update
	 * us with the new state.
	 */
	अगर (fsnotअगरy_inode_watches_children(dentry->d_parent->d_inode))
		dentry->d_flags |= DCACHE_FSNOTIFY_PARENT_WATCHED;
	अन्यथा
		dentry->d_flags &= ~DCACHE_FSNOTIFY_PARENT_WATCHED;
पूर्ण

/* called from fsnotअगरy listeners, such as fanotअगरy or dnotअगरy */

/* create a new group */
बाह्य काष्ठा fsnotअगरy_group *fsnotअगरy_alloc_group(स्थिर काष्ठा fsnotअगरy_ops *ops);
बाह्य काष्ठा fsnotअगरy_group *fsnotअगरy_alloc_user_group(स्थिर काष्ठा fsnotअगरy_ops *ops);
/* get reference to a group */
बाह्य व्योम fsnotअगरy_get_group(काष्ठा fsnotअगरy_group *group);
/* drop reference on a group from fsnotअगरy_alloc_group */
बाह्य व्योम fsnotअगरy_put_group(काष्ठा fsnotअगरy_group *group);
/* group deकाष्ठाion begins, stop queuing new events */
बाह्य व्योम fsnotअगरy_group_stop_queueing(काष्ठा fsnotअगरy_group *group);
/* destroy group */
बाह्य व्योम fsnotअगरy_destroy_group(काष्ठा fsnotअगरy_group *group);
/* fasync handler function */
बाह्य पूर्णांक fsnotअगरy_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on);
/* Free event from memory */
बाह्य व्योम fsnotअगरy_destroy_event(काष्ठा fsnotअगरy_group *group,
				   काष्ठा fsnotअगरy_event *event);
/* attach the event to the group notअगरication queue */
बाह्य पूर्णांक fsnotअगरy_add_event(काष्ठा fsnotअगरy_group *group,
			      काष्ठा fsnotअगरy_event *event,
			      पूर्णांक (*merge)(काष्ठा fsnotअगरy_group *,
					   काष्ठा fsnotअगरy_event *),
			      व्योम (*insert)(काष्ठा fsnotअगरy_group *,
					     काष्ठा fsnotअगरy_event *));
/* Queue overflow event to a notअगरication group */
अटल अंतरभूत व्योम fsnotअगरy_queue_overflow(काष्ठा fsnotअगरy_group *group)
अणु
	fsnotअगरy_add_event(group, group->overflow_event, शून्य, शून्य);
पूर्ण

अटल अंतरभूत bool fsnotअगरy_notअगरy_queue_is_empty(काष्ठा fsnotअगरy_group *group)
अणु
	निश्चित_spin_locked(&group->notअगरication_lock);

	वापस list_empty(&group->notअगरication_list);
पूर्ण

बाह्य bool fsnotअगरy_notअगरy_queue_is_empty(काष्ठा fsnotअगरy_group *group);
/* वापस, but करो not dequeue the first event on the notअगरication queue */
बाह्य काष्ठा fsnotअगरy_event *fsnotअगरy_peek_first_event(काष्ठा fsnotअगरy_group *group);
/* वापस AND dequeue the first event on the notअगरication queue */
बाह्य काष्ठा fsnotअगरy_event *fsnotअगरy_हटाओ_first_event(काष्ठा fsnotअगरy_group *group);
/* Remove event queued in the notअगरication list */
बाह्य व्योम fsnotअगरy_हटाओ_queued_event(काष्ठा fsnotअगरy_group *group,
					 काष्ठा fsnotअगरy_event *event);

/* functions used to manipulate the marks attached to inodes */

/* Get mask of events क्रम a list of marks */
बाह्य __u32 fsnotअगरy_conn_mask(काष्ठा fsnotअगरy_mark_connector *conn);
/* Calculate mask of events क्रम a list of marks */
बाह्य व्योम fsnotअगरy_recalc_mask(काष्ठा fsnotअगरy_mark_connector *conn);
बाह्य व्योम fsnotअगरy_init_mark(काष्ठा fsnotअगरy_mark *mark,
			       काष्ठा fsnotअगरy_group *group);
/* Find mark beदीर्घing to given group in the list of marks */
बाह्य काष्ठा fsnotअगरy_mark *fsnotअगरy_find_mark(fsnotअगरy_connp_t *connp,
						काष्ठा fsnotअगरy_group *group);
/* Get cached fsid of fileप्रणाली containing object */
बाह्य पूर्णांक fsnotअगरy_get_conn_fsid(स्थिर काष्ठा fsnotअगरy_mark_connector *conn,
				  __kernel_fsid_t *fsid);
/* attach the mark to the object */
बाह्य पूर्णांक fsnotअगरy_add_mark(काष्ठा fsnotअगरy_mark *mark,
			     fsnotअगरy_connp_t *connp, अचिन्हित पूर्णांक type,
			     पूर्णांक allow_dups, __kernel_fsid_t *fsid);
बाह्य पूर्णांक fsnotअगरy_add_mark_locked(काष्ठा fsnotअगरy_mark *mark,
				    fsnotअगरy_connp_t *connp,
				    अचिन्हित पूर्णांक type, पूर्णांक allow_dups,
				    __kernel_fsid_t *fsid);

/* attach the mark to the inode */
अटल अंतरभूत पूर्णांक fsnotअगरy_add_inode_mark(काष्ठा fsnotअगरy_mark *mark,
					  काष्ठा inode *inode,
					  पूर्णांक allow_dups)
अणु
	वापस fsnotअगरy_add_mark(mark, &inode->i_fsnotअगरy_marks,
				 FSNOTIFY_OBJ_TYPE_INODE, allow_dups, शून्य);
पूर्ण
अटल अंतरभूत पूर्णांक fsnotअगरy_add_inode_mark_locked(काष्ठा fsnotअगरy_mark *mark,
						 काष्ठा inode *inode,
						 पूर्णांक allow_dups)
अणु
	वापस fsnotअगरy_add_mark_locked(mark, &inode->i_fsnotअगरy_marks,
					FSNOTIFY_OBJ_TYPE_INODE, allow_dups,
					शून्य);
पूर्ण

/* given a group and a mark, flag mark to be मुक्तd when all references are dropped */
बाह्य व्योम fsnotअगरy_destroy_mark(काष्ठा fsnotअगरy_mark *mark,
				  काष्ठा fsnotअगरy_group *group);
/* detach mark from inode / mount list, group list, drop inode reference */
बाह्य व्योम fsnotअगरy_detach_mark(काष्ठा fsnotअगरy_mark *mark);
/* मुक्त mark */
बाह्य व्योम fsnotअगरy_मुक्त_mark(काष्ठा fsnotअगरy_mark *mark);
/* Wait until all marks queued क्रम deकाष्ठाion are destroyed */
बाह्य व्योम fsnotअगरy_रुको_marks_destroyed(व्योम);
/* run all the marks in a group, and clear all of the marks attached to given object type */
बाह्य व्योम fsnotअगरy_clear_marks_by_group(काष्ठा fsnotअगरy_group *group, अचिन्हित पूर्णांक type);
/* run all the marks in a group, and clear all of the vfsmount marks */
अटल अंतरभूत व्योम fsnotअगरy_clear_vfsmount_marks_by_group(काष्ठा fsnotअगरy_group *group)
अणु
	fsnotअगरy_clear_marks_by_group(group, FSNOTIFY_OBJ_TYPE_VFSMOUNT_FL);
पूर्ण
/* run all the marks in a group, and clear all of the inode marks */
अटल अंतरभूत व्योम fsnotअगरy_clear_inode_marks_by_group(काष्ठा fsnotअगरy_group *group)
अणु
	fsnotअगरy_clear_marks_by_group(group, FSNOTIFY_OBJ_TYPE_INODE_FL);
पूर्ण
/* run all the marks in a group, and clear all of the sn marks */
अटल अंतरभूत व्योम fsnotअगरy_clear_sb_marks_by_group(काष्ठा fsnotअगरy_group *group)
अणु
	fsnotअगरy_clear_marks_by_group(group, FSNOTIFY_OBJ_TYPE_SB_FL);
पूर्ण
बाह्य व्योम fsnotअगरy_get_mark(काष्ठा fsnotअगरy_mark *mark);
बाह्य व्योम fsnotअगरy_put_mark(काष्ठा fsnotअगरy_mark *mark);
बाह्य व्योम fsnotअगरy_finish_user_रुको(काष्ठा fsnotअगरy_iter_info *iter_info);
बाह्य bool fsnotअगरy_prepare_user_रुको(काष्ठा fsnotअगरy_iter_info *iter_info);

अटल अंतरभूत व्योम fsnotअगरy_init_event(काष्ठा fsnotअगरy_event *event)
अणु
	INIT_LIST_HEAD(&event->list);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक fsnotअगरy(__u32 mask, स्थिर व्योम *data, पूर्णांक data_type,
			   काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
			   काष्ठा inode *inode, u32 cookie)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __fsnotअगरy_parent(काष्ठा dentry *dentry, __u32 mask,
				  स्थिर व्योम *data, पूर्णांक data_type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __fsnotअगरy_inode_delete(काष्ठा inode *inode)
अणुपूर्ण

अटल अंतरभूत व्योम __fsnotअगरy_vfsmount_delete(काष्ठा vfsmount *mnt)
अणुपूर्ण

अटल अंतरभूत व्योम fsnotअगरy_sb_delete(काष्ठा super_block *sb)
अणुपूर्ण

अटल अंतरभूत व्योम fsnotअगरy_update_flags(काष्ठा dentry *dentry)
अणुपूर्ण

अटल अंतरभूत u32 fsnotअगरy_get_cookie(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fsnotअगरy_unmount_inodes(काष्ठा super_block *sb)
अणुपूर्ण

#पूर्ण_अगर	/* CONFIG_FSNOTIFY */

#पूर्ण_अगर	/* __KERNEL __ */

#पूर्ण_अगर	/* __LINUX_FSNOTIFY_BACKEND_H */
