<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_LIBCEPH_H
#घोषणा _FS_CEPH_LIBCEPH_H

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/completion.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/bug.h>
#समावेश <linux/fs.h>
#समावेश <linux/mempool.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/रुको.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/slab.h>
#समावेश <linux/refcount.h>

#समावेश <linux/ceph/types.h>
#समावेश <linux/ceph/messenger.h>
#समावेश <linux/ceph/msgpool.h>
#समावेश <linux/ceph/mon_client.h>
#समावेश <linux/ceph/osd_client.h>
#समावेश <linux/ceph/ceph_fs.h>
#समावेश <linux/ceph/string_table.h>

/*
 * mount options
 */
#घोषणा CEPH_OPT_FSID             (1<<0)
#घोषणा CEPH_OPT_NOSHARE          (1<<1) /* करोn't share client with other sbs */
#घोषणा CEPH_OPT_MYIP             (1<<2) /* specअगरied my ip */
#घोषणा CEPH_OPT_NOCRC            (1<<3) /* no data crc on ग_लिखोs (msgr1) */
#घोषणा CEPH_OPT_TCP_NODELAY      (1<<4) /* TCP_NODELAY on TCP sockets */
#घोषणा CEPH_OPT_NOMSGSIGN        (1<<5) /* करोn't sign msgs (msgr1) */
#घोषणा CEPH_OPT_ABORT_ON_FULL    (1<<6) /* पात w/ ENOSPC when full */

#घोषणा CEPH_OPT_DEFAULT   (CEPH_OPT_TCP_NODELAY)

#घोषणा ceph_set_opt(client, opt) \
	(client)->options->flags |= CEPH_OPT_##opt;
#घोषणा ceph_test_opt(client, opt) \
	(!!((client)->options->flags & CEPH_OPT_##opt))

काष्ठा ceph_options अणु
	पूर्णांक flags;
	काष्ठा ceph_fsid fsid;
	काष्ठा ceph_entity_addr my_addr;
	अचिन्हित दीर्घ mount_समयout;		/* jअगरfies */
	अचिन्हित दीर्घ osd_idle_ttl;		/* jअगरfies */
	अचिन्हित दीर्घ osd_keepalive_समयout;	/* jअगरfies */
	अचिन्हित दीर्घ osd_request_समयout;	/* jअगरfies */
	u32 पढ़ो_from_replica;  /* CEPH_OSD_FLAG_BALANCE/LOCALIZE_READS */
	पूर्णांक con_modes[2];  /* CEPH_CON_MODE_* */

	/*
	 * any type that can't be simply compared or doesn't need
	 * to be compared should go beyond this poपूर्णांक,
	 * ceph_compare_options() should be updated accordingly
	 */

	काष्ठा ceph_entity_addr *mon_addr; /* should be the first
					      poपूर्णांकer type of args */
	पूर्णांक num_mon;
	अक्षर *name;
	काष्ठा ceph_crypto_key *key;
	काष्ठा rb_root crush_locs;
पूर्ण;

/*
 * शेषs
 */
#घोषणा CEPH_MOUNT_TIMEOUT_DEFAULT	msecs_to_jअगरfies(60 * 1000)
#घोषणा CEPH_OSD_KEEPALIVE_DEFAULT	msecs_to_jअगरfies(5 * 1000)
#घोषणा CEPH_OSD_IDLE_TTL_DEFAULT	msecs_to_jअगरfies(60 * 1000)
#घोषणा CEPH_OSD_REQUEST_TIMEOUT_DEFAULT 0  /* no समयout */
#घोषणा CEPH_READ_FROM_REPLICA_DEFAULT	0  /* पढ़ो from primary */

#घोषणा CEPH_MONC_HUNT_INTERVAL		msecs_to_jअगरfies(3 * 1000)
#घोषणा CEPH_MONC_PING_INTERVAL		msecs_to_jअगरfies(10 * 1000)
#घोषणा CEPH_MONC_PING_TIMEOUT		msecs_to_jअगरfies(30 * 1000)
#घोषणा CEPH_MONC_HUNT_BACKOFF		2
#घोषणा CEPH_MONC_HUNT_MAX_MULT		10

#घोषणा CEPH_MSG_MAX_CONTROL_LEN (16*1024*1024)
#घोषणा CEPH_MSG_MAX_FRONT_LEN	(16*1024*1024)
#घोषणा CEPH_MSG_MAX_MIDDLE_LEN	(16*1024*1024)

/*
 * The largest possible rbd data object is 32M.
 * The largest possible rbd object map object is 64M.
 *
 * There is no limit on the size of cephfs objects, but it has to obey
 * rsize and wsize mount options anyway.
 */
#घोषणा CEPH_MSG_MAX_DATA_LEN	(64*1024*1024)

#घोषणा CEPH_AUTH_NAME_DEFAULT   "guest"

/* mount state */
क्रमागत अणु
	CEPH_MOUNT_MOUNTING,
	CEPH_MOUNT_MOUNTED,
	CEPH_MOUNT_UNMOUNTING,
	CEPH_MOUNT_UNMOUNTED,
	CEPH_MOUNT_SHUTDOWN,
	CEPH_MOUNT_RECOVER,
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ ceph_समयout_jअगरfies(अचिन्हित दीर्घ समयout)
अणु
	वापस समयout ?: MAX_SCHEDULE_TIMEOUT;
पूर्ण

काष्ठा ceph_mds_client;

/*
 * per client state
 *
 * possibly shared by multiple mount poपूर्णांकs, अगर they are
 * mounting the same ceph fileप्रणाली/cluster.
 */
काष्ठा ceph_client अणु
	काष्ठा ceph_fsid fsid;
	bool have_fsid;

	व्योम *निजी;

	काष्ठा ceph_options *options;

	काष्ठा mutex mount_mutex;      /* serialize mount attempts */
	रुको_queue_head_t auth_wq;
	पूर्णांक auth_err;

	पूर्णांक (*extra_mon_dispatch)(काष्ठा ceph_client *, काष्ठा ceph_msg *);

	u64 supported_features;
	u64 required_features;

	काष्ठा ceph_messenger msgr;   /* messenger instance */
	काष्ठा ceph_mon_client monc;
	काष्ठा ceph_osd_client osdc;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_dir;
	काष्ठा dentry *debugfs_monmap;
	काष्ठा dentry *debugfs_osdmap;
	काष्ठा dentry *debugfs_options;
#पूर्ण_अगर
पूर्ण;

#घोषणा from_msgr(ms)	container_of(ms, काष्ठा ceph_client, msgr)

अटल अंतरभूत bool ceph_msgr2(काष्ठा ceph_client *client)
अणु
	वापस client->options->con_modes[0] != CEPH_CON_MODE_UNKNOWN;
पूर्ण

/*
 * snapshots
 */

/*
 * A "snap context" is the set of existing snapshots when we
 * ग_लिखो data.  It is used by the OSD to guide its COW behavior.
 *
 * The ceph_snap_context is refcounted, and attached to each dirty
 * page, indicating which context the dirty data beदीर्घed when it was
 * dirtied.
 */
काष्ठा ceph_snap_context अणु
	refcount_t nref;
	u64 seq;
	u32 num_snaps;
	u64 snaps[];
पूर्ण;

बाह्य काष्ठा ceph_snap_context *ceph_create_snap_context(u32 snap_count,
					gfp_t gfp_flags);
बाह्य काष्ठा ceph_snap_context *ceph_get_snap_context(
					काष्ठा ceph_snap_context *sc);
बाह्य व्योम ceph_put_snap_context(काष्ठा ceph_snap_context *sc);

/*
 * calculate the number of pages a given length and offset map onto,
 * अगर we align the data.
 */
अटल अंतरभूत पूर्णांक calc_pages_क्रम(u64 off, u64 len)
अणु
	वापस ((off+len+PAGE_SIZE-1) >> PAGE_SHIFT) -
		(off >> PAGE_SHIFT);
पूर्ण

#घोषणा RB_BYVAL(a)      (a)
#घोषणा RB_BYPTR(a)      (&(a))
#घोषणा RB_CMP3WAY(a, b) ((a) < (b) ? -1 : (a) > (b))

#घोषणा DEFINE_RB_INSDEL_FUNCS2(name, type, keyfld, cmpexp, keyexp, nodefld) \
अटल bool __insert_##name(काष्ठा rb_root *root, type *t)		\
अणु									\
	काष्ठा rb_node **n = &root->rb_node;				\
	काष्ठा rb_node *parent = शून्य;					\
									\
	BUG_ON(!RB_EMPTY_NODE(&t->nodefld));				\
									\
	जबतक (*n) अणु							\
		type *cur = rb_entry(*n, type, nodefld);		\
		पूर्णांक cmp;						\
									\
		parent = *n;						\
		cmp = cmpexp(keyexp(t->keyfld), keyexp(cur->keyfld));	\
		अगर (cmp < 0)						\
			n = &(*n)->rb_left;				\
		अन्यथा अगर (cmp > 0)					\
			n = &(*n)->rb_right;				\
		अन्यथा							\
			वापस false;					\
	पूर्ण								\
									\
	rb_link_node(&t->nodefld, parent, n);				\
	rb_insert_color(&t->nodefld, root);				\
	वापस true;							\
पूर्ण									\
अटल व्योम __maybe_unused insert_##name(काष्ठा rb_root *root, type *t)	\
अणु									\
	अगर (!__insert_##name(root, t))					\
		BUG();							\
पूर्ण									\
अटल व्योम erase_##name(काष्ठा rb_root *root, type *t)			\
अणु									\
	BUG_ON(RB_EMPTY_NODE(&t->nodefld));				\
	rb_erase(&t->nodefld, root);					\
	RB_CLEAR_NODE(&t->nodefld);					\
पूर्ण

/*
 * @lookup_param_type is a parameter and not स्थिरructed from (@type,
 * @keyfld) with typeof() because adding स्थिर is too unwieldy.
 */
#घोषणा DEFINE_RB_LOOKUP_FUNC2(name, type, keyfld, cmpexp, keyexp,	\
			       lookup_param_type, nodefld)		\
अटल type *lookup_##name(काष्ठा rb_root *root, lookup_param_type key)	\
अणु									\
	काष्ठा rb_node *n = root->rb_node;				\
									\
	जबतक (n) अणु							\
		type *cur = rb_entry(n, type, nodefld);			\
		पूर्णांक cmp;						\
									\
		cmp = cmpexp(key, keyexp(cur->keyfld));			\
		अगर (cmp < 0)						\
			n = n->rb_left;					\
		अन्यथा अगर (cmp > 0)					\
			n = n->rb_right;				\
		अन्यथा							\
			वापस cur;					\
	पूर्ण								\
									\
	वापस शून्य;							\
पूर्ण

#घोषणा DEFINE_RB_FUNCS2(name, type, keyfld, cmpexp, keyexp,		\
			 lookup_param_type, nodefld)			\
DEFINE_RB_INSDEL_FUNCS2(name, type, keyfld, cmpexp, keyexp, nodefld)	\
DEFINE_RB_LOOKUP_FUNC2(name, type, keyfld, cmpexp, keyexp,		\
		       lookup_param_type, nodefld)

/*
 * Shorthands क्रम पूर्णांकeger keys.
 */
#घोषणा DEFINE_RB_INSDEL_FUNCS(name, type, keyfld, nodefld)		\
DEFINE_RB_INSDEL_FUNCS2(name, type, keyfld, RB_CMP3WAY, RB_BYVAL, nodefld)

#घोषणा DEFINE_RB_LOOKUP_FUNC(name, type, keyfld, nodefld)		\
बाह्य type __lookup_##name##_key;					\
DEFINE_RB_LOOKUP_FUNC2(name, type, keyfld, RB_CMP3WAY, RB_BYVAL,	\
		       typeof(__lookup_##name##_key.keyfld), nodefld)

#घोषणा DEFINE_RB_FUNCS(name, type, keyfld, nodefld)			\
DEFINE_RB_INSDEL_FUNCS(name, type, keyfld, nodefld)			\
DEFINE_RB_LOOKUP_FUNC(name, type, keyfld, nodefld)

बाह्य काष्ठा kmem_cache *ceph_inode_cachep;
बाह्य काष्ठा kmem_cache *ceph_cap_cachep;
बाह्य काष्ठा kmem_cache *ceph_cap_flush_cachep;
बाह्य काष्ठा kmem_cache *ceph_dentry_cachep;
बाह्य काष्ठा kmem_cache *ceph_file_cachep;
बाह्य काष्ठा kmem_cache *ceph_dir_file_cachep;
बाह्य काष्ठा kmem_cache *ceph_mds_request_cachep;
बाह्य mempool_t *ceph_wb_pagevec_pool;

/* ceph_common.c */
बाह्य bool libceph_compatible(व्योम *data);

बाह्य स्थिर अक्षर *ceph_msg_type_name(पूर्णांक type);
बाह्य पूर्णांक ceph_check_fsid(काष्ठा ceph_client *client, काष्ठा ceph_fsid *fsid);
बाह्य व्योम *ceph_kvदो_स्मृति(माप_प्रकार size, gfp_t flags);

काष्ठा fs_parameter;
काष्ठा fc_log;
काष्ठा ceph_options *ceph_alloc_options(व्योम);
पूर्णांक ceph_parse_mon_ips(स्थिर अक्षर *buf, माप_प्रकार len, काष्ठा ceph_options *opt,
		       काष्ठा fc_log *l);
पूर्णांक ceph_parse_param(काष्ठा fs_parameter *param, काष्ठा ceph_options *opt,
		     काष्ठा fc_log *l);
पूर्णांक ceph_prपूर्णांक_client_options(काष्ठा seq_file *m, काष्ठा ceph_client *client,
			      bool show_all);
बाह्य व्योम ceph_destroy_options(काष्ठा ceph_options *opt);
बाह्य पूर्णांक ceph_compare_options(काष्ठा ceph_options *new_opt,
				काष्ठा ceph_client *client);
काष्ठा ceph_client *ceph_create_client(काष्ठा ceph_options *opt, व्योम *निजी);
काष्ठा ceph_entity_addr *ceph_client_addr(काष्ठा ceph_client *client);
u64 ceph_client_gid(काष्ठा ceph_client *client);
बाह्य व्योम ceph_destroy_client(काष्ठा ceph_client *client);
बाह्य व्योम ceph_reset_client_addr(काष्ठा ceph_client *client);
बाह्य पूर्णांक __ceph_खोलो_session(काष्ठा ceph_client *client,
			       अचिन्हित दीर्घ started);
बाह्य पूर्णांक ceph_खोलो_session(काष्ठा ceph_client *client);
पूर्णांक ceph_रुको_क्रम_latest_osdmap(काष्ठा ceph_client *client,
				अचिन्हित दीर्घ समयout);

/* pagevec.c */
बाह्य व्योम ceph_release_page_vector(काष्ठा page **pages, पूर्णांक num_pages);
बाह्य व्योम ceph_put_page_vector(काष्ठा page **pages, पूर्णांक num_pages,
				 bool dirty);
बाह्य काष्ठा page **ceph_alloc_page_vector(पूर्णांक num_pages, gfp_t flags);
बाह्य पूर्णांक ceph_copy_user_to_page_vector(काष्ठा page **pages,
					 स्थिर व्योम __user *data,
					 loff_t off, माप_प्रकार len);
बाह्य व्योम ceph_copy_to_page_vector(काष्ठा page **pages,
				    स्थिर व्योम *data,
				    loff_t off, माप_प्रकार len);
बाह्य व्योम ceph_copy_from_page_vector(काष्ठा page **pages,
				    व्योम *data,
				    loff_t off, माप_प्रकार len);
बाह्य व्योम ceph_zero_page_vector_range(पूर्णांक off, पूर्णांक len, काष्ठा page **pages);


#पूर्ण_अगर /* _FS_CEPH_SUPER_H */
