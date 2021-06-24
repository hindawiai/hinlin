<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/nfs_fs.h
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  OS-specअगरic nfs fileप्रणाली definitions and declarations
 */
#अगर_अघोषित _LINUX_NFS_FS_H
#घोषणा _LINUX_NFS_FS_H

#समावेश <uapi/linux/nfs_fs.h>


/*
 * Enable dprपूर्णांकk() debugging support क्रम nfs client.
 */
#अगर_घोषित CONFIG_NFS_DEBUG
# define NFS_DEBUG
#पूर्ण_अगर

#समावेश <linux/in.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/refcount.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/रुको.h>

#समावेश <linux/sunrpc/debug.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/sunrpc/clnt.h>

#समावेश <linux/nfs.h>
#समावेश <linux/nfs2.h>
#समावेश <linux/nfs3.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_xdr.h>
#समावेश <linux/nfs_fs_sb.h>

#समावेश <linux/mempool.h>

/*
 * These are the शेष flags क्रम swap requests
 */
#घोषणा NFS_RPC_SWAPFLAGS		(RPC_TASK_SWAPPER|RPC_TASK_ROOTCREDS)

/*
 * Size of the NFS directory verअगरier
 */
#घोषणा NFS_सूची_VERIFIER_SIZE		2

/*
 * NFSv3/v4 Access mode cache entry
 */
काष्ठा nfs_access_entry अणु
	काष्ठा rb_node		rb_node;
	काष्ठा list_head	lru;
	स्थिर काष्ठा cred *	cred;
	__u32			mask;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

काष्ठा nfs_lock_context अणु
	refcount_t count;
	काष्ठा list_head list;
	काष्ठा nfs_खोलो_context *खोलो_context;
	fl_owner_t lockowner;
	atomic_t io_count;
	काष्ठा rcu_head	rcu_head;
पूर्ण;

काष्ठा nfs4_state;
काष्ठा nfs_खोलो_context अणु
	काष्ठा nfs_lock_context lock_context;
	fl_owner_t flock_owner;
	काष्ठा dentry *dentry;
	स्थिर काष्ठा cred *cred;
	काष्ठा rpc_cred *ll_cred;	/* low-level cred - use to check क्रम expiry */
	काष्ठा nfs4_state *state;
	भ_शेषe_t mode;

	अचिन्हित दीर्घ flags;
#घोषणा NFS_CONTEXT_RESEND_WRITES	(1)
#घोषणा NFS_CONTEXT_BAD			(2)
#घोषणा NFS_CONTEXT_UNLOCK	(3)
	पूर्णांक error;

	काष्ठा list_head list;
	काष्ठा nfs4_threshold	*mdsthreshold;
	काष्ठा rcu_head	rcu_head;
पूर्ण;

काष्ठा nfs_खोलो_dir_context अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ attr_gencount;
	__be32	verf[NFS_सूची_VERIFIER_SIZE];
	__u64 dir_cookie;
	__u64 dup_cookie;
	चिन्हित अक्षर duped;
पूर्ण;

/*
 * NFSv4 delegation
 */
काष्ठा nfs_delegation;

काष्ठा posix_acl;

काष्ठा nfs4_xattr_cache;

/*
 * nfs fs inode data in memory
 */
काष्ठा nfs_inode अणु
	/*
	 * The 64bit 'inode number'
	 */
	__u64 fileid;

	/*
	 * NFS file handle
	 */
	काष्ठा nfs_fh		fh;

	/*
	 * Various flags
	 */
	अचिन्हित दीर्घ		flags;			/* atomic bit ops */
	अचिन्हित दीर्घ		cache_validity;		/* bit mask */

	/*
	 * पढ़ो_cache_jअगरfies is when we started पढ़ो-caching this inode.
	 * attrसमयo is क्रम how दीर्घ the cached inक्रमmation is assumed
	 * to be valid. A successful attribute revalidation द्विगुनs
	 * attrसमयo (up to acregmax/acdirmax), a failure resets it to
	 * acregmin/acdirmin.
	 *
	 * We need to revalidate the cached attrs क्रम this inode अगर
	 *
	 *	jअगरfies - पढ़ो_cache_jअगरfies >= attrसमयo
	 *
	 * Please note the comparison is greater than or equal
	 * so that zero समयout values can be specअगरied.
	 */
	अचिन्हित दीर्घ		पढ़ो_cache_jअगरfies;
	अचिन्हित दीर्घ		attrसमयo;
	अचिन्हित दीर्घ		attrसमयo_बारtamp;

	अचिन्हित दीर्घ		attr_gencount;
	/* "Generation counter" क्रम the attribute cache. This is
	 * bumped whenever we update the metadata on the
	 * server.
	 */
	अचिन्हित दीर्घ		cache_change_attribute;

	काष्ठा rb_root		access_cache;
	काष्ठा list_head	access_cache_entry_lru;
	काष्ठा list_head	access_cache_inode_lru;

	/*
	 * This is the cookie verअगरier used क्रम NFSv3 सूची_पढ़ो
	 * operations
	 */
	__be32			cookieverf[NFS_सूची_VERIFIER_SIZE];

	atomic_दीर्घ_t		nrequests;
	काष्ठा nfs_mds_commit_info commit_info;

	/* Open contexts क्रम shared mmap ग_लिखोs */
	काष्ठा list_head	खोलो_files;

	/* Readers: in-flight sillydelete RPC calls */
	/* Writers: सूची_हटाओ */
	काष्ठा rw_semaphore	सूची_हटाओ_sem;
	काष्ठा mutex		commit_mutex;

	/* track last access to cached pages */
	अचिन्हित दीर्घ		page_index;

#अगर IS_ENABLED(CONFIG_NFS_V4)
	काष्ठा nfs4_cached_acl	*nfs4_acl;
        /* NFSv4 state */
	काष्ठा list_head	खोलो_states;
	काष्ठा nfs_delegation __rcu *delegation;
	काष्ठा rw_semaphore	rwsem;

	/* pNFS layout inक्रमmation */
	काष्ठा pnfs_layout_hdr *layout;
#पूर्ण_अगर /* CONFIG_NFS_V4*/
	/* how many bytes have been written/पढ़ो and how many bytes queued up */
	__u64 ग_लिखो_io;
	__u64 पढ़ो_io;
#अगर_घोषित CONFIG_NFS_FSCACHE
	काष्ठा fscache_cookie	*fscache;
#पूर्ण_अगर
	काष्ठा inode		vfs_inode;

#अगर_घोषित CONFIG_NFS_V4_2
	काष्ठा nfs4_xattr_cache *xattr_cache;
#पूर्ण_अगर
पूर्ण;

काष्ठा nfs4_copy_state अणु
	काष्ठा list_head	copies;
	काष्ठा list_head	src_copies;
	nfs4_stateid		stateid;
	काष्ठा completion	completion;
	uपूर्णांक64_t		count;
	काष्ठा nfs_ग_लिखोverf	verf;
	पूर्णांक			error;
	पूर्णांक			flags;
	काष्ठा nfs4_state	*parent_src_state;
	काष्ठा nfs4_state	*parent_dst_state;
पूर्ण;

/*
 * Access bit flags
 */
#घोषणा NFS_ACCESS_READ        0x0001
#घोषणा NFS_ACCESS_LOOKUP      0x0002
#घोषणा NFS_ACCESS_MODIFY      0x0004
#घोषणा NFS_ACCESS_EXTEND      0x0008
#घोषणा NFS_ACCESS_DELETE      0x0010
#घोषणा NFS_ACCESS_EXECUTE     0x0020
#घोषणा NFS_ACCESS_XAREAD      0x0040
#घोषणा NFS_ACCESS_XAWRITE     0x0080
#घोषणा NFS_ACCESS_XALIST      0x0100

/*
 * Cache validity bit flags
 */
#घोषणा NFS_INO_INVALID_DATA	BIT(1)		/* cached data is invalid */
#घोषणा NFS_INO_INVALID_ATIME	BIT(2)		/* cached aसमय is invalid */
#घोषणा NFS_INO_INVALID_ACCESS	BIT(3)		/* cached access cred invalid */
#घोषणा NFS_INO_INVALID_ACL	BIT(4)		/* cached acls are invalid */
#घोषणा NFS_INO_REVAL_PAGECACHE	BIT(5)		/* must revalidate pagecache */
#घोषणा NFS_INO_REVAL_FORCED	BIT(6)		/* क्रमce revalidation ignoring a delegation */
#घोषणा NFS_INO_INVALID_LABEL	BIT(7)		/* cached label is invalid */
#घोषणा NFS_INO_INVALID_CHANGE	BIT(8)		/* cached change is invalid */
#घोषणा NFS_INO_INVALID_CTIME	BIT(9)		/* cached स_समय is invalid */
#घोषणा NFS_INO_INVALID_MTIME	BIT(10)		/* cached mसमय is invalid */
#घोषणा NFS_INO_INVALID_SIZE	BIT(11)		/* cached size is invalid */
#घोषणा NFS_INO_INVALID_OTHER	BIT(12)		/* other attrs are invalid */
#घोषणा NFS_INO_DATA_INVAL_DEFER	\
				BIT(13)		/* Deferred cache invalidation */
#घोषणा NFS_INO_INVALID_BLOCKS	BIT(14)         /* cached blocks are invalid */
#घोषणा NFS_INO_INVALID_XATTR	BIT(15)		/* xattrs are invalid */
#घोषणा NFS_INO_INVALID_NLINK	BIT(16)		/* cached nlinks is invalid */
#घोषणा NFS_INO_INVALID_MODE	BIT(17)		/* cached mode is invalid */

#घोषणा NFS_INO_INVALID_ATTR	(NFS_INO_INVALID_CHANGE \
		| NFS_INO_INVALID_CTIME \
		| NFS_INO_INVALID_MTIME \
		| NFS_INO_INVALID_SIZE \
		| NFS_INO_INVALID_NLINK \
		| NFS_INO_INVALID_MODE \
		| NFS_INO_INVALID_OTHER)	/* inode metadata is invalid */

/*
 * Bit offsets in flags field
 */
#घोषणा NFS_INO_ADVISE_RDPLUS	(0)		/* advise सूची_पढ़ोplus */
#घोषणा NFS_INO_STALE		(1)		/* possible stale inode */
#घोषणा NFS_INO_ACL_LRU_SET	(2)		/* Inode is on the LRU list */
#घोषणा NFS_INO_INVALIDATING	(3)		/* inode is being invalidated */
#घोषणा NFS_INO_FSCACHE		(5)		/* inode can be cached by FS-Cache */
#घोषणा NFS_INO_FSCACHE_LOCK	(6)		/* FS-Cache cookie management lock */
#घोषणा NFS_INO_LAYOUTCOMMIT	(9)		/* layoutcommit required */
#घोषणा NFS_INO_LAYOUTCOMMITTING (10)		/* layoutcommit inflight */
#घोषणा NFS_INO_LAYOUTSTATS	(11)		/* layoutstats inflight */
#घोषणा NFS_INO_OसूचीECT		(12)		/* I/O setting is O_सूचीECT */

अटल अंतरभूत काष्ठा nfs_inode *NFS_I(स्थिर काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा nfs_inode, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा nfs_server *NFS_SB(स्थिर काष्ठा super_block *s)
अणु
	वापस (काष्ठा nfs_server *)(s->s_fs_info);
पूर्ण

अटल अंतरभूत काष्ठा nfs_fh *NFS_FH(स्थिर काष्ठा inode *inode)
अणु
	वापस &NFS_I(inode)->fh;
पूर्ण

अटल अंतरभूत काष्ठा nfs_server *NFS_SERVER(स्थिर काष्ठा inode *inode)
अणु
	वापस NFS_SB(inode->i_sb);
पूर्ण

अटल अंतरभूत काष्ठा rpc_clnt *NFS_CLIENT(स्थिर काष्ठा inode *inode)
अणु
	वापस NFS_SERVER(inode)->client;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा nfs_rpc_ops *NFS_PROTO(स्थिर काष्ठा inode *inode)
अणु
	वापस NFS_SERVER(inode)->nfs_client->rpc_ops;
पूर्ण

अटल अंतरभूत अचिन्हित NFS_MINATTRTIMEO(स्थिर काष्ठा inode *inode)
अणु
	काष्ठा nfs_server *nfss = NFS_SERVER(inode);
	वापस S_ISसूची(inode->i_mode) ? nfss->acdirmin : nfss->acregmin;
पूर्ण

अटल अंतरभूत अचिन्हित NFS_MAXATTRTIMEO(स्थिर काष्ठा inode *inode)
अणु
	काष्ठा nfs_server *nfss = NFS_SERVER(inode);
	वापस S_ISसूची(inode->i_mode) ? nfss->acdirmax : nfss->acregmax;
पूर्ण

अटल अंतरभूत पूर्णांक NFS_STALE(स्थिर काष्ठा inode *inode)
अणु
	वापस test_bit(NFS_INO_STALE, &NFS_I(inode)->flags);
पूर्ण

अटल अंतरभूत काष्ठा fscache_cookie *nfs_i_fscache(काष्ठा inode *inode)
अणु
#अगर_घोषित CONFIG_NFS_FSCACHE
	वापस NFS_I(inode)->fscache;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __u64 NFS_खाताID(स्थिर काष्ठा inode *inode)
अणु
	वापस NFS_I(inode)->fileid;
पूर्ण

अटल अंतरभूत व्योम set_nfs_fileid(काष्ठा inode *inode, __u64 fileid)
अणु
	NFS_I(inode)->fileid = fileid;
पूर्ण

अटल अंतरभूत व्योम nfs_mark_क्रम_revalidate(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	spin_lock(&inode->i_lock);
	nfsi->cache_validity |= NFS_INO_REVAL_PAGECACHE
		| NFS_INO_INVALID_ACCESS
		| NFS_INO_INVALID_ACL
		| NFS_INO_INVALID_CHANGE
		| NFS_INO_INVALID_CTIME;
	अगर (S_ISसूची(inode->i_mode))
		nfsi->cache_validity |= NFS_INO_INVALID_DATA;
	spin_unlock(&inode->i_lock);
पूर्ण

अटल अंतरभूत पूर्णांक nfs_server_capable(काष्ठा inode *inode, पूर्णांक cap)
अणु
	वापस NFS_SERVER(inode)->caps & cap;
पूर्ण

/**
 * nfs_save_change_attribute - Returns the inode attribute change cookie
 * @dir - poपूर्णांकer to parent directory inode
 * The "cache change attribute" is updated when we need to revalidate
 * our dentry cache after a directory was seen to change on the server.
 */
अटल अंतरभूत अचिन्हित दीर्घ nfs_save_change_attribute(काष्ठा inode *dir)
अणु
	वापस NFS_I(dir)->cache_change_attribute;
पूर्ण

/*
 * linux/fs/nfs/inode.c
 */
बाह्य पूर्णांक nfs_sync_mapping(काष्ठा address_space *mapping);
बाह्य व्योम nfs_zap_mapping(काष्ठा inode *inode, काष्ठा address_space *mapping);
बाह्य व्योम nfs_zap_caches(काष्ठा inode *);
बाह्य व्योम nfs_set_inode_stale(काष्ठा inode *inode);
बाह्य व्योम nfs_invalidate_aसमय(काष्ठा inode *);
बाह्य काष्ठा inode *nfs_fhget(काष्ठा super_block *, काष्ठा nfs_fh *,
				काष्ठा nfs_fattr *, काष्ठा nfs4_label *);
काष्ठा inode *nfs_ilookup(काष्ठा super_block *sb, काष्ठा nfs_fattr *, काष्ठा nfs_fh *);
बाह्य पूर्णांक nfs_refresh_inode(काष्ठा inode *, काष्ठा nfs_fattr *);
बाह्य पूर्णांक nfs_post_op_update_inode(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr);
बाह्य पूर्णांक nfs_post_op_update_inode_क्रमce_wcc(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr);
बाह्य पूर्णांक nfs_post_op_update_inode_क्रमce_wcc_locked(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr);
बाह्य पूर्णांक nfs_getattr(काष्ठा user_namespace *, स्थिर काष्ठा path *,
		       काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य व्योम nfs_access_add_cache(काष्ठा inode *, काष्ठा nfs_access_entry *);
बाह्य व्योम nfs_access_set_mask(काष्ठा nfs_access_entry *, u32);
बाह्य पूर्णांक nfs_permission(काष्ठा user_namespace *, काष्ठा inode *, पूर्णांक);
बाह्य पूर्णांक nfs_खोलो(काष्ठा inode *, काष्ठा file *);
बाह्य पूर्णांक nfs_attribute_cache_expired(काष्ठा inode *inode);
बाह्य पूर्णांक nfs_revalidate_inode(काष्ठा inode *inode, अचिन्हित दीर्घ flags);
बाह्य पूर्णांक __nfs_revalidate_inode(काष्ठा nfs_server *, काष्ठा inode *);
बाह्य पूर्णांक nfs_clear_invalid_mapping(काष्ठा address_space *mapping);
बाह्य bool nfs_mapping_need_revalidate_inode(काष्ठा inode *inode);
बाह्य पूर्णांक nfs_revalidate_mapping(काष्ठा inode *inode, काष्ठा address_space *mapping);
बाह्य पूर्णांक nfs_revalidate_mapping_rcu(काष्ठा inode *inode);
बाह्य पूर्णांक nfs_setattr(काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा iattr *);
बाह्य व्योम nfs_setattr_update_inode(काष्ठा inode *inode, काष्ठा iattr *attr, काष्ठा nfs_fattr *);
बाह्य व्योम nfs_setsecurity(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr,
				काष्ठा nfs4_label *label);
बाह्य काष्ठा nfs_खोलो_context *get_nfs_खोलो_context(काष्ठा nfs_खोलो_context *ctx);
बाह्य व्योम put_nfs_खोलो_context(काष्ठा nfs_खोलो_context *ctx);
बाह्य काष्ठा nfs_खोलो_context *nfs_find_खोलो_context(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, भ_शेषe_t mode);
बाह्य काष्ठा nfs_खोलो_context *alloc_nfs_खोलो_context(काष्ठा dentry *dentry, भ_शेषe_t f_mode, काष्ठा file *filp);
बाह्य व्योम nfs_inode_attach_खोलो_context(काष्ठा nfs_खोलो_context *ctx);
बाह्य व्योम nfs_file_set_खोलो_context(काष्ठा file *filp, काष्ठा nfs_खोलो_context *ctx);
बाह्य व्योम nfs_file_clear_खोलो_context(काष्ठा file *flip);
बाह्य काष्ठा nfs_lock_context *nfs_get_lock_context(काष्ठा nfs_खोलो_context *ctx);
बाह्य व्योम nfs_put_lock_context(काष्ठा nfs_lock_context *l_ctx);
बाह्य u64 nfs_compat_user_ino64(u64 fileid);
बाह्य व्योम nfs_fattr_init(काष्ठा nfs_fattr *fattr);
बाह्य व्योम nfs_fattr_set_barrier(काष्ठा nfs_fattr *fattr);
बाह्य अचिन्हित दीर्घ nfs_inc_attr_generation_counter(व्योम);

बाह्य काष्ठा nfs_fattr *nfs_alloc_fattr(व्योम);

अटल अंतरभूत व्योम nfs_मुक्त_fattr(स्थिर काष्ठा nfs_fattr *fattr)
अणु
	kमुक्त(fattr);
पूर्ण

बाह्य काष्ठा nfs_fh *nfs_alloc_fhandle(व्योम);

अटल अंतरभूत व्योम nfs_मुक्त_fhandle(स्थिर काष्ठा nfs_fh *fh)
अणु
	kमुक्त(fh);
पूर्ण

#अगर_घोषित NFS_DEBUG
बाह्य u32 _nfs_display_fhandle_hash(स्थिर काष्ठा nfs_fh *fh);
अटल अंतरभूत u32 nfs_display_fhandle_hash(स्थिर काष्ठा nfs_fh *fh)
अणु
	वापस _nfs_display_fhandle_hash(fh);
पूर्ण
बाह्य व्योम _nfs_display_fhandle(स्थिर काष्ठा nfs_fh *fh, स्थिर अक्षर *caption);
#घोषणा nfs_display_fhandle(fh, caption)			\
	करो अणु							\
		अगर (unlikely(nfs_debug & NFSDBG_FACILITY))	\
			_nfs_display_fhandle(fh, caption);	\
	पूर्ण जबतक (0)
#अन्यथा
अटल अंतरभूत u32 nfs_display_fhandle_hash(स्थिर काष्ठा nfs_fh *fh)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम nfs_display_fhandle(स्थिर काष्ठा nfs_fh *fh,
				       स्थिर अक्षर *caption)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * linux/fs/nfs/nfsroot.c
 */
बाह्य पूर्णांक  nfs_root_data(अक्षर **root_device, अक्षर **root_data); /*__init*/
/* linux/net/ipv4/ipconfig.c: trims ip addr off front of name, too. */
बाह्य __be32 root_nfs_parse_addr(अक्षर *name); /*__init*/

/*
 * linux/fs/nfs/file.c
 */
बाह्य स्थिर काष्ठा file_operations nfs_file_operations;
#अगर IS_ENABLED(CONFIG_NFS_V4)
बाह्य स्थिर काष्ठा file_operations nfs4_file_operations;
#पूर्ण_अगर /* CONFIG_NFS_V4 */
बाह्य स्थिर काष्ठा address_space_operations nfs_file_aops;
बाह्य स्थिर काष्ठा address_space_operations nfs_dir_aops;

अटल अंतरभूत काष्ठा nfs_खोलो_context *nfs_file_खोलो_context(काष्ठा file *filp)
अणु
	वापस filp->निजी_data;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cred *nfs_file_cred(काष्ठा file *file)
अणु
	अगर (file != शून्य) अणु
		काष्ठा nfs_खोलो_context *ctx =
			nfs_file_खोलो_context(file);
		अगर (ctx)
			वापस ctx->cred;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * linux/fs/nfs/direct.c
 */
बाह्य sमाप_प्रकार nfs_direct_IO(काष्ठा kiocb *, काष्ठा iov_iter *);
बाह्य sमाप_प्रकार nfs_file_direct_पढ़ो(काष्ठा kiocb *iocb,
			काष्ठा iov_iter *iter);
बाह्य sमाप_प्रकार nfs_file_direct_ग_लिखो(काष्ठा kiocb *iocb,
			काष्ठा iov_iter *iter);

/*
 * linux/fs/nfs/dir.c
 */
बाह्य स्थिर काष्ठा file_operations nfs_dir_operations;
बाह्य स्थिर काष्ठा dentry_operations nfs_dentry_operations;

बाह्य व्योम nfs_क्रमce_lookup_revalidate(काष्ठा inode *dir);
बाह्य व्योम nfs_set_verअगरier(काष्ठा dentry * dentry, अचिन्हित दीर्घ verf);
#अगर IS_ENABLED(CONFIG_NFS_V4)
बाह्य व्योम nfs_clear_verअगरier_delegated(काष्ठा inode *inode);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_NFS_V4) */
बाह्य काष्ठा dentry *nfs_add_or_obtain(काष्ठा dentry *dentry,
			काष्ठा nfs_fh *fh, काष्ठा nfs_fattr *fattr,
			काष्ठा nfs4_label *label);
बाह्य पूर्णांक nfs_instantiate(काष्ठा dentry *dentry, काष्ठा nfs_fh *fh,
			काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label);
बाह्य पूर्णांक nfs_may_खोलो(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, पूर्णांक खोलोflags);
बाह्य व्योम nfs_access_zap_cache(काष्ठा inode *inode);
बाह्य पूर्णांक nfs_access_get_cached(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, काष्ठा nfs_access_entry *res,
				 bool may_block);

/*
 * linux/fs/nfs/symlink.c
 */
बाह्य स्थिर काष्ठा inode_operations nfs_symlink_inode_operations;

/*
 * linux/fs/nfs/sysctl.c
 */
#अगर_घोषित CONFIG_SYSCTL
बाह्य पूर्णांक nfs_रेजिस्टर_sysctl(व्योम);
बाह्य व्योम nfs_unरेजिस्टर_sysctl(व्योम);
#अन्यथा
#घोषणा nfs_रेजिस्टर_sysctl() 0
#घोषणा nfs_unरेजिस्टर_sysctl() करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/*
 * linux/fs/nfs/namespace.c
 */
बाह्य स्थिर काष्ठा inode_operations nfs_mountpoपूर्णांक_inode_operations;
बाह्य स्थिर काष्ठा inode_operations nfs_referral_inode_operations;
बाह्य पूर्णांक nfs_mountpoपूर्णांक_expiry_समयout;
बाह्य व्योम nfs_release_स्वतःmount_समयr(व्योम);

/*
 * linux/fs/nfs/unlink.c
 */
बाह्य व्योम nfs_complete_unlink(काष्ठा dentry *dentry, काष्ठा inode *);

/*
 * linux/fs/nfs/ग_लिखो.c
 */
बाह्य पूर्णांक  nfs_congestion_kb;
बाह्य पूर्णांक  nfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc);
बाह्य पूर्णांक  nfs_ग_लिखोpages(काष्ठा address_space *, काष्ठा ग_लिखोback_control *);
बाह्य पूर्णांक  nfs_flush_incompatible(काष्ठा file *file, काष्ठा page *page);
बाह्य पूर्णांक  nfs_updatepage(काष्ठा file *, काष्ठा page *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

/*
 * Try to ग_लिखो back everything synchronously (but check the
 * वापस value!)
 */
बाह्य पूर्णांक nfs_sync_inode(काष्ठा inode *inode);
बाह्य पूर्णांक nfs_wb_all(काष्ठा inode *inode);
बाह्य पूर्णांक nfs_wb_page(काष्ठा inode *inode, काष्ठा page *page);
बाह्य पूर्णांक nfs_wb_page_cancel(काष्ठा inode *inode, काष्ठा page* page);
बाह्य पूर्णांक  nfs_commit_inode(काष्ठा inode *, पूर्णांक);
बाह्य काष्ठा nfs_commit_data *nfs_commitdata_alloc(bool never_fail);
बाह्य व्योम nfs_commit_मुक्त(काष्ठा nfs_commit_data *data);

अटल अंतरभूत पूर्णांक
nfs_have_ग_लिखोbacks(काष्ठा inode *inode)
अणु
	वापस atomic_दीर्घ_पढ़ो(&NFS_I(inode)->nrequests) != 0;
पूर्ण

/*
 * linux/fs/nfs/पढ़ो.c
 */
बाह्य पूर्णांक  nfs_पढ़ोpage(काष्ठा file *, काष्ठा page *);
बाह्य पूर्णांक  nfs_पढ़ोpages(काष्ठा file *, काष्ठा address_space *,
		काष्ठा list_head *, अचिन्हित);

/*
 * अंतरभूत functions
 */

अटल अंतरभूत loff_t nfs_माप_प्रकारo_loff_t(__u64 size)
अणु
	वापस min_t(u64, size, OFFSET_MAX);
पूर्ण

अटल अंतरभूत ino_t
nfs_fileid_to_ino_t(u64 fileid)
अणु
	ino_t ino = (ino_t) fileid;
	अगर (माप(ino_t) < माप(u64))
		ino ^= fileid >> (माप(u64)-माप(ino_t)) * 8;
	वापस ino;
पूर्ण

#घोषणा NFS_JUKEBOX_RETRY_TIME (5 * HZ)


# undef अगरdebug
# अगरdef NFS_DEBUG
#  define अगरdebug(fac)		अगर (unlikely(nfs_debug & NFSDBG_##fac))
#  define NFS_IFDEBUG(x)	x
# अन्यथा
#  define अगरdebug(fac)		अगर (0)
#  define NFS_IFDEBUG(x)
# endअगर
#पूर्ण_अगर
