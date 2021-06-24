<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * kernfs.h - pseuकरो fileप्रणाली decoupled from vfs locking
 */

#अगर_अघोषित __LINUX_KERNFS_H
#घोषणा __LINUX_KERNFS_H

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/idr.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/रुको.h>

काष्ठा file;
काष्ठा dentry;
काष्ठा iattr;
काष्ठा seq_file;
काष्ठा vm_area_काष्ठा;
काष्ठा super_block;
काष्ठा file_प्रणाली_type;
काष्ठा poll_table_काष्ठा;
काष्ठा fs_context;

काष्ठा kernfs_fs_context;
काष्ठा kernfs_खोलो_node;
काष्ठा kernfs_iattrs;

क्रमागत kernfs_node_type अणु
	KERNFS_सूची		= 0x0001,
	KERNFS_खाता		= 0x0002,
	KERNFS_LINK		= 0x0004,
पूर्ण;

#घोषणा KERNFS_TYPE_MASK		0x000f
#घोषणा KERNFS_FLAG_MASK		~KERNFS_TYPE_MASK
#घोषणा KERNFS_MAX_USER_XATTRS		128
#घोषणा KERNFS_USER_XATTR_SIZE_LIMIT	(128 << 10)

क्रमागत kernfs_node_flag अणु
	KERNFS_ACTIVATED	= 0x0010,
	KERNFS_NS		= 0x0020,
	KERNFS_HAS_SEQ_SHOW	= 0x0040,
	KERNFS_HAS_MMAP		= 0x0080,
	KERNFS_LOCKDEP		= 0x0100,
	KERNFS_SUICIDAL		= 0x0400,
	KERNFS_SUICIDED		= 0x0800,
	KERNFS_EMPTY_सूची	= 0x1000,
	KERNFS_HAS_RELEASE	= 0x2000,
पूर्ण;

/* @flags क्रम kernfs_create_root() */
क्रमागत kernfs_root_flag अणु
	/*
	 * kernfs_nodes are created in the deactivated state and invisible.
	 * They require explicit kernfs_activate() to become visible.  This
	 * can be used to make related nodes become visible atomically
	 * after all nodes are created successfully.
	 */
	KERNFS_ROOT_CREATE_DEACTIVATED		= 0x0001,

	/*
	 * For regular files, अगर the खोलोer has CAP_DAC_OVERRIDE, खोलो(2)
	 * succeeds regardless of the RW permissions.  sysfs had an extra
	 * layer of enक्रमcement where खोलो(2) fails with -EACCES regardless
	 * of CAP_DAC_OVERRIDE अगर the permission करोesn't have the
	 * respective पढ़ो or ग_लिखो access at all (none of S_IRUGO or
	 * S_IWUGO) or the respective operation isn't implemented.  The
	 * following flag enables that behavior.
	 */
	KERNFS_ROOT_EXTRA_OPEN_PERM_CHECK	= 0x0002,

	/*
	 * The fileप्रणाली supports exportfs operation, so userspace can use
	 * fhandle to access nodes of the fs.
	 */
	KERNFS_ROOT_SUPPORT_EXPORTOP		= 0x0004,

	/*
	 * Support user xattrs to be written to nodes rooted at this root.
	 */
	KERNFS_ROOT_SUPPORT_USER_XATTR		= 0x0008,
पूर्ण;

/* type-specअगरic काष्ठाures क्रम kernfs_node जोड़ members */
काष्ठा kernfs_elem_dir अणु
	अचिन्हित दीर्घ		subdirs;
	/* children rbtree starts here and goes through kn->rb */
	काष्ठा rb_root		children;

	/*
	 * The kernfs hierarchy this directory beदीर्घs to.  This fits
	 * better directly in kernfs_node but is here to save space.
	 */
	काष्ठा kernfs_root	*root;
पूर्ण;

काष्ठा kernfs_elem_symlink अणु
	काष्ठा kernfs_node	*target_kn;
पूर्ण;

काष्ठा kernfs_elem_attr अणु
	स्थिर काष्ठा kernfs_ops	*ops;
	काष्ठा kernfs_खोलो_node	*खोलो;
	loff_t			size;
	काष्ठा kernfs_node	*notअगरy_next;	/* क्रम kernfs_notअगरy() */
पूर्ण;

/*
 * kernfs_node - the building block of kernfs hierarchy.  Each and every
 * kernfs node is represented by single kernfs_node.  Most fields are
 * निजी to kernfs and shouldn't be accessed directly by kernfs users.
 *
 * As दीर्घ as count reference is held, the kernfs_node itself is
 * accessible.  Dereferencing elem or any other outer entity requires
 * active reference.
 */
काष्ठा kernfs_node अणु
	atomic_t		count;
	atomic_t		active;
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map	dep_map;
#पूर्ण_अगर
	/*
	 * Use kernfs_get_parent() and kernfs_name/path() instead of
	 * accessing the following two fields directly.  If the node is
	 * never moved to a dअगरferent parent, it is safe to access the
	 * parent directly.
	 */
	काष्ठा kernfs_node	*parent;
	स्थिर अक्षर		*name;

	काष्ठा rb_node		rb;

	स्थिर व्योम		*ns;	/* namespace tag */
	अचिन्हित पूर्णांक		hash;	/* ns + name hash */
	जोड़ अणु
		काष्ठा kernfs_elem_dir		dir;
		काष्ठा kernfs_elem_symlink	symlink;
		काष्ठा kernfs_elem_attr		attr;
	पूर्ण;

	व्योम			*priv;

	/*
	 * 64bit unique ID.  On 64bit ino setups, id is the ino.  On 32bit,
	 * the low 32bits are ino and upper generation.
	 */
	u64			id;

	अचिन्हित लघु		flags;
	umode_t			mode;
	काष्ठा kernfs_iattrs	*iattr;
पूर्ण;

/*
 * kernfs_syscall_ops may be specअगरied on kernfs_create_root() to support
 * syscalls.  These optional callbacks are invoked on the matching syscalls
 * and can perक्रमm any kernfs operations which करोn't necessarily have to be
 * the exact operation requested.  An active reference is held क्रम each
 * kernfs_node parameter.
 */
काष्ठा kernfs_syscall_ops अणु
	पूर्णांक (*show_options)(काष्ठा seq_file *sf, काष्ठा kernfs_root *root);

	पूर्णांक (*सूची_गढ़ो)(काष्ठा kernfs_node *parent, स्थिर अक्षर *name,
		     umode_t mode);
	पूर्णांक (*सूची_हटाओ)(काष्ठा kernfs_node *kn);
	पूर्णांक (*नाम)(काष्ठा kernfs_node *kn, काष्ठा kernfs_node *new_parent,
		      स्थिर अक्षर *new_name);
	पूर्णांक (*show_path)(काष्ठा seq_file *sf, काष्ठा kernfs_node *kn,
			 काष्ठा kernfs_root *root);
पूर्ण;

काष्ठा kernfs_root अणु
	/* published fields */
	काष्ठा kernfs_node	*kn;
	अचिन्हित पूर्णांक		flags;	/* KERNFS_ROOT_* flags */

	/* निजी fields, करो not use outside kernfs proper */
	काष्ठा idr		ino_idr;
	u32			last_id_lowbits;
	u32			id_highbits;
	काष्ठा kernfs_syscall_ops *syscall_ops;

	/* list of kernfs_super_info of this root, रक्षित by kernfs_mutex */
	काष्ठा list_head	supers;

	रुको_queue_head_t	deactivate_रुकोq;
पूर्ण;

काष्ठा kernfs_खोलो_file अणु
	/* published fields */
	काष्ठा kernfs_node	*kn;
	काष्ठा file		*file;
	काष्ठा seq_file		*seq_file;
	व्योम			*priv;

	/* निजी fields, करो not use outside kernfs proper */
	काष्ठा mutex		mutex;
	काष्ठा mutex		pपुनः_स्मृति_mutex;
	पूर्णांक			event;
	काष्ठा list_head	list;
	अक्षर			*pपुनः_स्मृति_buf;

	माप_प्रकार			atomic_ग_लिखो_len;
	bool			mmapped:1;
	bool			released:1;
	स्थिर काष्ठा vm_operations_काष्ठा *vm_ops;
पूर्ण;

काष्ठा kernfs_ops अणु
	/*
	 * Optional खोलो/release methods.  Both are called with
	 * @of->seq_file populated.
	 */
	पूर्णांक (*खोलो)(काष्ठा kernfs_खोलो_file *of);
	व्योम (*release)(काष्ठा kernfs_खोलो_file *of);

	/*
	 * Read is handled by either seq_file or raw_पढ़ो().
	 *
	 * If seq_show() is present, seq_file path is active.  Other seq
	 * operations are optional and अगर not implemented, the behavior is
	 * equivalent to single_खोलो().  @sf->निजी poपूर्णांकs to the
	 * associated kernfs_खोलो_file.
	 *
	 * पढ़ो() is bounced through kernel buffer and a पढ़ो larger than
	 * PAGE_SIZE results in partial operation of PAGE_SIZE.
	 */
	पूर्णांक (*seq_show)(काष्ठा seq_file *sf, व्योम *v);

	व्योम *(*seq_start)(काष्ठा seq_file *sf, loff_t *ppos);
	व्योम *(*seq_next)(काष्ठा seq_file *sf, व्योम *v, loff_t *ppos);
	व्योम (*seq_stop)(काष्ठा seq_file *sf, व्योम *v);

	sमाप_प्रकार (*पढ़ो)(काष्ठा kernfs_खोलो_file *of, अक्षर *buf, माप_प्रकार bytes,
			loff_t off);

	/*
	 * ग_लिखो() is bounced through kernel buffer.  If atomic_ग_लिखो_len
	 * is not set, a ग_लिखो larger than PAGE_SIZE results in partial
	 * operations of PAGE_SIZE chunks.  If atomic_ग_लिखो_len is set,
	 * ग_लिखोs upto the specअगरied size are executed atomically but
	 * larger ones are rejected with -E2BIG.
	 */
	माप_प्रकार atomic_ग_लिखो_len;
	/*
	 * "prealloc" causes a buffer to be allocated at खोलो क्रम
	 * all पढ़ो/ग_लिखो requests.  As ->seq_show uses seq_पढ़ो()
	 * which करोes its own allocation, it is incompatible with
	 * ->pपुनः_स्मृति.  Provide ->पढ़ो and ->ग_लिखो with ->pपुनः_स्मृति.
	 */
	bool pपुनः_स्मृति;
	sमाप_प्रकार (*ग_लिखो)(काष्ठा kernfs_खोलो_file *of, अक्षर *buf, माप_प्रकार bytes,
			 loff_t off);

	__poll_t (*poll)(काष्ठा kernfs_खोलो_file *of,
			 काष्ठा poll_table_काष्ठा *pt);

	पूर्णांक (*mmap)(काष्ठा kernfs_खोलो_file *of, काष्ठा vm_area_काष्ठा *vma);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lock_class_key	lockdep_key;
#पूर्ण_अगर
पूर्ण;

/*
 * The kernfs superblock creation/mount parameter context.
 */
काष्ठा kernfs_fs_context अणु
	काष्ठा kernfs_root	*root;		/* Root of the hierarchy being mounted */
	व्योम			*ns_tag;	/* Namespace tag of the mount (or शून्य) */
	अचिन्हित दीर्घ		magic;		/* File प्रणाली specअगरic magic number */

	/* The following are set/used by kernfs_mount() */
	bool			new_sb_created;	/* Set to T अगर we allocated a new sb */
पूर्ण;

#अगर_घोषित CONFIG_KERNFS

अटल अंतरभूत क्रमागत kernfs_node_type kernfs_type(काष्ठा kernfs_node *kn)
अणु
	वापस kn->flags & KERNFS_TYPE_MASK;
पूर्ण

अटल अंतरभूत ino_t kernfs_id_ino(u64 id)
अणु
	/* id is ino अगर ino_t is 64bit; otherwise, low 32bits */
	अगर (माप(ino_t) >= माप(u64))
		वापस id;
	अन्यथा
		वापस (u32)id;
पूर्ण

अटल अंतरभूत u32 kernfs_id_gen(u64 id)
अणु
	/* gen is fixed at 1 अगर ino_t is 64bit; otherwise, high 32bits */
	अगर (माप(ino_t) >= माप(u64))
		वापस 1;
	अन्यथा
		वापस id >> 32;
पूर्ण

अटल अंतरभूत ino_t kernfs_ino(काष्ठा kernfs_node *kn)
अणु
	वापस kernfs_id_ino(kn->id);
पूर्ण

अटल अंतरभूत ino_t kernfs_gen(काष्ठा kernfs_node *kn)
अणु
	वापस kernfs_id_gen(kn->id);
पूर्ण

/**
 * kernfs_enable_ns - enable namespace under a directory
 * @kn: directory of पूर्णांकerest, should be empty
 *
 * This is to be called right after @kn is created to enable namespace
 * under it.  All children of @kn must have non-शून्य namespace tags and
 * only the ones which match the super_block's tag will be visible.
 */
अटल अंतरभूत व्योम kernfs_enable_ns(काष्ठा kernfs_node *kn)
अणु
	WARN_ON_ONCE(kernfs_type(kn) != KERNFS_सूची);
	WARN_ON_ONCE(!RB_EMPTY_ROOT(&kn->dir.children));
	kn->flags |= KERNFS_NS;
पूर्ण

/**
 * kernfs_ns_enabled - test whether namespace is enabled
 * @kn: the node to test
 *
 * Test whether namespace filtering is enabled क्रम the children of @ns.
 */
अटल अंतरभूत bool kernfs_ns_enabled(काष्ठा kernfs_node *kn)
अणु
	वापस kn->flags & KERNFS_NS;
पूर्ण

पूर्णांक kernfs_name(काष्ठा kernfs_node *kn, अक्षर *buf, माप_प्रकार buflen);
पूर्णांक kernfs_path_from_node(काष्ठा kernfs_node *root_kn, काष्ठा kernfs_node *kn,
			  अक्षर *buf, माप_प्रकार buflen);
व्योम pr_cont_kernfs_name(काष्ठा kernfs_node *kn);
व्योम pr_cont_kernfs_path(काष्ठा kernfs_node *kn);
काष्ठा kernfs_node *kernfs_get_parent(काष्ठा kernfs_node *kn);
काष्ठा kernfs_node *kernfs_find_and_get_ns(काष्ठा kernfs_node *parent,
					   स्थिर अक्षर *name, स्थिर व्योम *ns);
काष्ठा kernfs_node *kernfs_walk_and_get_ns(काष्ठा kernfs_node *parent,
					   स्थिर अक्षर *path, स्थिर व्योम *ns);
व्योम kernfs_get(काष्ठा kernfs_node *kn);
व्योम kernfs_put(काष्ठा kernfs_node *kn);

काष्ठा kernfs_node *kernfs_node_from_dentry(काष्ठा dentry *dentry);
काष्ठा kernfs_root *kernfs_root_from_sb(काष्ठा super_block *sb);
काष्ठा inode *kernfs_get_inode(काष्ठा super_block *sb, काष्ठा kernfs_node *kn);

काष्ठा dentry *kernfs_node_dentry(काष्ठा kernfs_node *kn,
				  काष्ठा super_block *sb);
काष्ठा kernfs_root *kernfs_create_root(काष्ठा kernfs_syscall_ops *scops,
				       अचिन्हित पूर्णांक flags, व्योम *priv);
व्योम kernfs_destroy_root(काष्ठा kernfs_root *root);

काष्ठा kernfs_node *kernfs_create_dir_ns(काष्ठा kernfs_node *parent,
					 स्थिर अक्षर *name, umode_t mode,
					 kuid_t uid, kgid_t gid,
					 व्योम *priv, स्थिर व्योम *ns);
काष्ठा kernfs_node *kernfs_create_empty_dir(काष्ठा kernfs_node *parent,
					    स्थिर अक्षर *name);
काष्ठा kernfs_node *__kernfs_create_file(काष्ठा kernfs_node *parent,
					 स्थिर अक्षर *name, umode_t mode,
					 kuid_t uid, kgid_t gid,
					 loff_t size,
					 स्थिर काष्ठा kernfs_ops *ops,
					 व्योम *priv, स्थिर व्योम *ns,
					 काष्ठा lock_class_key *key);
काष्ठा kernfs_node *kernfs_create_link(काष्ठा kernfs_node *parent,
				       स्थिर अक्षर *name,
				       काष्ठा kernfs_node *target);
व्योम kernfs_activate(काष्ठा kernfs_node *kn);
व्योम kernfs_हटाओ(काष्ठा kernfs_node *kn);
व्योम kernfs_अवरोध_active_protection(काष्ठा kernfs_node *kn);
व्योम kernfs_unअवरोध_active_protection(काष्ठा kernfs_node *kn);
bool kernfs_हटाओ_self(काष्ठा kernfs_node *kn);
पूर्णांक kernfs_हटाओ_by_name_ns(काष्ठा kernfs_node *parent, स्थिर अक्षर *name,
			     स्थिर व्योम *ns);
पूर्णांक kernfs_नाम_ns(काष्ठा kernfs_node *kn, काष्ठा kernfs_node *new_parent,
		     स्थिर अक्षर *new_name, स्थिर व्योम *new_ns);
पूर्णांक kernfs_setattr(काष्ठा kernfs_node *kn, स्थिर काष्ठा iattr *iattr);
__poll_t kernfs_generic_poll(काष्ठा kernfs_खोलो_file *of,
			     काष्ठा poll_table_काष्ठा *pt);
व्योम kernfs_notअगरy(काष्ठा kernfs_node *kn);

पूर्णांक kernfs_xattr_get(काष्ठा kernfs_node *kn, स्थिर अक्षर *name,
		     व्योम *value, माप_प्रकार size);
पूर्णांक kernfs_xattr_set(काष्ठा kernfs_node *kn, स्थिर अक्षर *name,
		     स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);

स्थिर व्योम *kernfs_super_ns(काष्ठा super_block *sb);
पूर्णांक kernfs_get_tree(काष्ठा fs_context *fc);
व्योम kernfs_मुक्त_fs_context(काष्ठा fs_context *fc);
व्योम kernfs_समाप्त_sb(काष्ठा super_block *sb);

व्योम kernfs_init(व्योम);

काष्ठा kernfs_node *kernfs_find_and_get_node_by_id(काष्ठा kernfs_root *root,
						   u64 id);
#अन्यथा	/* CONFIG_KERNFS */

अटल अंतरभूत क्रमागत kernfs_node_type kernfs_type(काष्ठा kernfs_node *kn)
अणु वापस 0; पूर्ण	/* whatever */

अटल अंतरभूत व्योम kernfs_enable_ns(काष्ठा kernfs_node *kn) अणु पूर्ण

अटल अंतरभूत bool kernfs_ns_enabled(काष्ठा kernfs_node *kn)
अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक kernfs_name(काष्ठा kernfs_node *kn, अक्षर *buf, माप_प्रकार buflen)
अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत पूर्णांक kernfs_path_from_node(काष्ठा kernfs_node *root_kn,
					काष्ठा kernfs_node *kn,
					अक्षर *buf, माप_प्रकार buflen)
अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत व्योम pr_cont_kernfs_name(काष्ठा kernfs_node *kn) अणु पूर्ण
अटल अंतरभूत व्योम pr_cont_kernfs_path(काष्ठा kernfs_node *kn) अणु पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *kernfs_get_parent(काष्ठा kernfs_node *kn)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
kernfs_find_and_get_ns(काष्ठा kernfs_node *parent, स्थिर अक्षर *name,
		       स्थिर व्योम *ns)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा kernfs_node *
kernfs_walk_and_get_ns(काष्ठा kernfs_node *parent, स्थिर अक्षर *path,
		       स्थिर व्योम *ns)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत व्योम kernfs_get(काष्ठा kernfs_node *kn) अणु पूर्ण
अटल अंतरभूत व्योम kernfs_put(काष्ठा kernfs_node *kn) अणु पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *kernfs_node_from_dentry(काष्ठा dentry *dentry)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत काष्ठा kernfs_root *kernfs_root_from_sb(काष्ठा super_block *sb)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत काष्ठा inode *
kernfs_get_inode(काष्ठा super_block *sb, काष्ठा kernfs_node *kn)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत काष्ठा kernfs_root *
kernfs_create_root(काष्ठा kernfs_syscall_ops *scops, अचिन्हित पूर्णांक flags,
		   व्योम *priv)
अणु वापस ERR_PTR(-ENOSYS); पूर्ण

अटल अंतरभूत व्योम kernfs_destroy_root(काष्ठा kernfs_root *root) अणु पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
kernfs_create_dir_ns(काष्ठा kernfs_node *parent, स्थिर अक्षर *name,
		     umode_t mode, kuid_t uid, kgid_t gid,
		     व्योम *priv, स्थिर व्योम *ns)
अणु वापस ERR_PTR(-ENOSYS); पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
__kernfs_create_file(काष्ठा kernfs_node *parent, स्थिर अक्षर *name,
		     umode_t mode, kuid_t uid, kgid_t gid,
		     loff_t size, स्थिर काष्ठा kernfs_ops *ops,
		     व्योम *priv, स्थिर व्योम *ns, काष्ठा lock_class_key *key)
अणु वापस ERR_PTR(-ENOSYS); पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
kernfs_create_link(काष्ठा kernfs_node *parent, स्थिर अक्षर *name,
		   काष्ठा kernfs_node *target)
अणु वापस ERR_PTR(-ENOSYS); पूर्ण

अटल अंतरभूत व्योम kernfs_activate(काष्ठा kernfs_node *kn) अणु पूर्ण

अटल अंतरभूत व्योम kernfs_हटाओ(काष्ठा kernfs_node *kn) अणु पूर्ण

अटल अंतरभूत bool kernfs_हटाओ_self(काष्ठा kernfs_node *kn)
अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक kernfs_हटाओ_by_name_ns(काष्ठा kernfs_node *kn,
					   स्थिर अक्षर *name, स्थिर व्योम *ns)
अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत पूर्णांक kernfs_नाम_ns(काष्ठा kernfs_node *kn,
				   काष्ठा kernfs_node *new_parent,
				   स्थिर अक्षर *new_name, स्थिर व्योम *new_ns)
अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत पूर्णांक kernfs_setattr(काष्ठा kernfs_node *kn,
				 स्थिर काष्ठा iattr *iattr)
अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत व्योम kernfs_notअगरy(काष्ठा kernfs_node *kn) अणु पूर्ण

अटल अंतरभूत पूर्णांक kernfs_xattr_get(काष्ठा kernfs_node *kn, स्थिर अक्षर *name,
				   व्योम *value, माप_प्रकार size)
अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत पूर्णांक kernfs_xattr_set(काष्ठा kernfs_node *kn, स्थिर अक्षर *name,
				   स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत स्थिर व्योम *kernfs_super_ns(काष्ठा super_block *sb)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत पूर्णांक kernfs_get_tree(काष्ठा fs_context *fc)
अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत व्योम kernfs_मुक्त_fs_context(काष्ठा fs_context *fc) अणु पूर्ण

अटल अंतरभूत व्योम kernfs_समाप्त_sb(काष्ठा super_block *sb) अणु पूर्ण

अटल अंतरभूत व्योम kernfs_init(व्योम) अणु पूर्ण

#पूर्ण_अगर	/* CONFIG_KERNFS */

/**
 * kernfs_path - build full path of a given node
 * @kn: kernfs_node of पूर्णांकerest
 * @buf: buffer to copy @kn's name पूर्णांकo
 * @buflen: size of @buf
 *
 * If @kn is शून्य result will be "(null)".
 *
 * Returns the length of the full path.  If the full length is equal to or
 * greater than @buflen, @buf contains the truncated path with the trailing
 * '\0'.  On error, -त्रुटि_सं is वापसed.
 */
अटल अंतरभूत पूर्णांक kernfs_path(काष्ठा kernfs_node *kn, अक्षर *buf, माप_प्रकार buflen)
अणु
	वापस kernfs_path_from_node(kn, शून्य, buf, buflen);
पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
kernfs_find_and_get(काष्ठा kernfs_node *kn, स्थिर अक्षर *name)
अणु
	वापस kernfs_find_and_get_ns(kn, name, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
kernfs_walk_and_get(काष्ठा kernfs_node *kn, स्थिर अक्षर *path)
अणु
	वापस kernfs_walk_and_get_ns(kn, path, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
kernfs_create_dir(काष्ठा kernfs_node *parent, स्थिर अक्षर *name, umode_t mode,
		  व्योम *priv)
अणु
	वापस kernfs_create_dir_ns(parent, name, mode,
				    GLOBAL_ROOT_UID, GLOBAL_ROOT_GID,
				    priv, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
kernfs_create_file_ns(काष्ठा kernfs_node *parent, स्थिर अक्षर *name,
		      umode_t mode, kuid_t uid, kgid_t gid,
		      loff_t size, स्थिर काष्ठा kernfs_ops *ops,
		      व्योम *priv, स्थिर व्योम *ns)
अणु
	काष्ठा lock_class_key *key = शून्य;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	key = (काष्ठा lock_class_key *)&ops->lockdep_key;
#पूर्ण_अगर
	वापस __kernfs_create_file(parent, name, mode, uid, gid,
				    size, ops, priv, ns, key);
पूर्ण

अटल अंतरभूत काष्ठा kernfs_node *
kernfs_create_file(काष्ठा kernfs_node *parent, स्थिर अक्षर *name, umode_t mode,
		   loff_t size, स्थिर काष्ठा kernfs_ops *ops, व्योम *priv)
अणु
	वापस kernfs_create_file_ns(parent, name, mode,
				     GLOBAL_ROOT_UID, GLOBAL_ROOT_GID,
				     size, ops, priv, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक kernfs_हटाओ_by_name(काष्ठा kernfs_node *parent,
					स्थिर अक्षर *name)
अणु
	वापस kernfs_हटाओ_by_name_ns(parent, name, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक kernfs_नाम(काष्ठा kernfs_node *kn,
				काष्ठा kernfs_node *new_parent,
				स्थिर अक्षर *new_name)
अणु
	वापस kernfs_नाम_ns(kn, new_parent, new_name, शून्य);
पूर्ण

#पूर्ण_अगर	/* __LINUX_KERNFS_H */
