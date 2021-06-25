<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sysctl.h: General linux प्रणाली control पूर्णांकerface
 *
 * Begun 24 March 1995, Stephen Tweedie
 *
 ****************************************************************
 ****************************************************************
 **
 **  WARNING:
 **  The values in this file are exported to user space via 
 **  the sysctl() binary पूर्णांकerface.  Do *NOT* change the
 **  numbering of any existing values here, and करो not change
 **  any numbers within any one set of values.  If you have to
 **  redefine an existing पूर्णांकerface, use a new number क्रम it.
 **  The kernel will then वापस -ENOTसूची to any application using
 **  the old binary पूर्णांकerface.
 **
 ****************************************************************
 ****************************************************************
 */
#अगर_अघोषित _LINUX_SYSCTL_H
#घोषणा _LINUX_SYSCTL_H

#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/रुको.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/uidgid.h>
#समावेश <uapi/linux/sysctl.h>

/* For the /proc/sys support */
काष्ठा completion;
काष्ठा ctl_table;
काष्ठा nsproxy;
काष्ठा ctl_table_root;
काष्ठा ctl_table_header;
काष्ठा ctl_dir;

/* Keep the same order as in fs/proc/proc_sysctl.c */
#घोषणा SYSCTL_ZERO	((व्योम *)&sysctl_vals[0])
#घोषणा SYSCTL_ONE	((व्योम *)&sysctl_vals[1])
#घोषणा SYSCTL_पूर्णांक_उच्च	((व्योम *)&sysctl_vals[2])

बाह्य स्थिर पूर्णांक sysctl_vals[];

प्रकार पूर्णांक proc_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos);

पूर्णांक proc_करोstring(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_करोपूर्णांकvec(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_करोuपूर्णांकvec(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_करोपूर्णांकvec_minmax(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_करोuपूर्णांकvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक proc_करोu8vec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
			माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक proc_करोपूर्णांकvec_jअगरfies(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_करोपूर्णांकvec_userhz_jअगरfies(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
पूर्णांक proc_करोपूर्णांकvec_ms_jअगरfies(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
पूर्णांक proc_करोuदीर्घvec_minmax(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_करोuदीर्घvec_ms_jअगरfies_minmax(काष्ठा ctl_table *table, पूर्णांक, व्योम *,
		माप_प्रकार *, loff_t *);
पूर्णांक proc_करो_large_biपंचांगap(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_करो_अटल_key(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos);

/*
 * Register a set of sysctl names by calling रेजिस्टर_sysctl_table
 * with an initialised array of काष्ठा ctl_table's.  An entry with 
 * शून्य procname terminates the table.  table->de will be
 * set up by the registration and need not be initialised in advance.
 *
 * sysctl names can be mirrored स्वतःmatically under /proc/sys.  The
 * procname supplied controls /proc naming.
 *
 * The table's mode will be honoured क्रम proc-fs access.
 *
 * Leaf nodes in the sysctl tree will be represented by a single file
 * under /proc; non-leaf nodes will be represented by directories.  A
 * null procname disables /proc mirroring at this node.
 *
 * The data and maxlen fields of the ctl_table
 * काष्ठा enable minimal validation of the values being written to be
 * perक्रमmed, and the mode field allows minimal authentication.
 * 
 * There must be a proc_handler routine क्रम any terminal nodes
 * mirrored under /proc/sys (non-terminals are handled by a built-in
 * directory handler).  Several शेष handlers are available to
 * cover common हालs.
 */

/* Support क्रम userspace poll() to watch क्रम changes */
काष्ठा ctl_table_poll अणु
	atomic_t event;
	रुको_queue_head_t रुको;
पूर्ण;

अटल अंतरभूत व्योम *proc_sys_poll_event(काष्ठा ctl_table_poll *poll)
अणु
	वापस (व्योम *)(अचिन्हित दीर्घ)atomic_पढ़ो(&poll->event);
पूर्ण

#घोषणा __CTL_TABLE_POLL_INITIALIZER(name) अणु				\
	.event = ATOMIC_INIT(0),					\
	.रुको = __WAIT_QUEUE_HEAD_INITIALIZER(name.रुको) पूर्ण

#घोषणा DEFINE_CTL_TABLE_POLL(name)					\
	काष्ठा ctl_table_poll name = __CTL_TABLE_POLL_INITIALIZER(name)

/* A sysctl table is an array of काष्ठा ctl_table: */
काष्ठा ctl_table अणु
	स्थिर अक्षर *procname;		/* Text ID क्रम /proc/sys, or zero */
	व्योम *data;
	पूर्णांक maxlen;
	umode_t mode;
	काष्ठा ctl_table *child;	/* Deprecated */
	proc_handler *proc_handler;	/* Callback क्रम text क्रमmatting */
	काष्ठा ctl_table_poll *poll;
	व्योम *extra1;
	व्योम *extra2;
पूर्ण __अक्रमomize_layout;

काष्ठा ctl_node अणु
	काष्ठा rb_node node;
	काष्ठा ctl_table_header *header;
पूर्ण;

/* काष्ठा ctl_table_header is used to मुख्यtain dynamic lists of
   काष्ठा ctl_table trees. */
काष्ठा ctl_table_header अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा ctl_table *ctl_table;
			पूर्णांक used;
			पूर्णांक count;
			पूर्णांक nreg;
		पूर्ण;
		काष्ठा rcu_head rcu;
	पूर्ण;
	काष्ठा completion *unरेजिस्टरing;
	काष्ठा ctl_table *ctl_table_arg;
	काष्ठा ctl_table_root *root;
	काष्ठा ctl_table_set *set;
	काष्ठा ctl_dir *parent;
	काष्ठा ctl_node *node;
	काष्ठा hlist_head inodes; /* head क्रम proc_inode->sysctl_inodes */
पूर्ण;

काष्ठा ctl_dir अणु
	/* Header must be at the start of ctl_dir */
	काष्ठा ctl_table_header header;
	काष्ठा rb_root root;
पूर्ण;

काष्ठा ctl_table_set अणु
	पूर्णांक (*is_seen)(काष्ठा ctl_table_set *);
	काष्ठा ctl_dir dir;
पूर्ण;

काष्ठा ctl_table_root अणु
	काष्ठा ctl_table_set शेष_set;
	काष्ठा ctl_table_set *(*lookup)(काष्ठा ctl_table_root *root);
	व्योम (*set_ownership)(काष्ठा ctl_table_header *head,
			      काष्ठा ctl_table *table,
			      kuid_t *uid, kgid_t *gid);
	पूर्णांक (*permissions)(काष्ठा ctl_table_header *head, काष्ठा ctl_table *table);
पूर्ण;

/* काष्ठा ctl_path describes where in the hierarchy a table is added */
काष्ठा ctl_path अणु
	स्थिर अक्षर *procname;
पूर्ण;

#अगर_घोषित CONFIG_SYSCTL

व्योम proc_sys_poll_notअगरy(काष्ठा ctl_table_poll *poll);

बाह्य व्योम setup_sysctl_set(काष्ठा ctl_table_set *p,
	काष्ठा ctl_table_root *root,
	पूर्णांक (*is_seen)(काष्ठा ctl_table_set *));
बाह्य व्योम retire_sysctl_set(काष्ठा ctl_table_set *set);

काष्ठा ctl_table_header *__रेजिस्टर_sysctl_table(
	काष्ठा ctl_table_set *set,
	स्थिर अक्षर *path, काष्ठा ctl_table *table);
काष्ठा ctl_table_header *__रेजिस्टर_sysctl_paths(
	काष्ठा ctl_table_set *set,
	स्थिर काष्ठा ctl_path *path, काष्ठा ctl_table *table);
काष्ठा ctl_table_header *रेजिस्टर_sysctl(स्थिर अक्षर *path, काष्ठा ctl_table *table);
काष्ठा ctl_table_header *रेजिस्टर_sysctl_table(काष्ठा ctl_table * table);
काष्ठा ctl_table_header *रेजिस्टर_sysctl_paths(स्थिर काष्ठा ctl_path *path,
						काष्ठा ctl_table *table);

व्योम unरेजिस्टर_sysctl_table(काष्ठा ctl_table_header * table);

बाह्य पूर्णांक sysctl_init(व्योम);
व्योम करो_sysctl_args(व्योम);

बाह्य पूर्णांक pwrsw_enabled;
बाह्य पूर्णांक unaligned_enabled;
बाह्य पूर्णांक unaligned_dump_stack;
बाह्य पूर्णांक no_unaligned_warning;

बाह्य काष्ठा ctl_table sysctl_mount_poपूर्णांक[];
बाह्य काष्ठा ctl_table अक्रमom_table[];
बाह्य काष्ठा ctl_table firmware_config_table[];
बाह्य काष्ठा ctl_table epoll_table[];

#अन्यथा /* CONFIG_SYSCTL */
अटल अंतरभूत काष्ठा ctl_table_header *रेजिस्टर_sysctl_table(काष्ठा ctl_table * table)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा ctl_table_header *रेजिस्टर_sysctl_paths(
			स्थिर काष्ठा ctl_path *path, काष्ठा ctl_table *table)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा ctl_table_header *रेजिस्टर_sysctl(स्थिर अक्षर *path, काष्ठा ctl_table *table)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_sysctl_table(काष्ठा ctl_table_header * table)
अणु
पूर्ण

अटल अंतरभूत व्योम setup_sysctl_set(काष्ठा ctl_table_set *p,
	काष्ठा ctl_table_root *root,
	पूर्णांक (*is_seen)(काष्ठा ctl_table_set *))
अणु
पूर्ण

अटल अंतरभूत व्योम करो_sysctl_args(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

पूर्णांक sysctl_max_thपढ़ोs(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos);

#पूर्ण_अगर /* _LINUX_SYSCTL_H */
