<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFS_FS_SB
#घोषणा _NFS_FS_SB

#समावेश <linux/list.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/idr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/nfs_xdr.h>
#समावेश <linux/sunrpc/xprt.h>

#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>

काष्ठा nfs4_session;
काष्ठा nfs_iostats;
काष्ठा nlm_host;
काष्ठा nfs4_sequence_args;
काष्ठा nfs4_sequence_res;
काष्ठा nfs_server;
काष्ठा nfs4_minor_version_ops;
काष्ठा nfs41_server_scope;
काष्ठा nfs41_impl_id;

/*
 * The nfs_client identअगरies our client state to the server.
 */
काष्ठा nfs_client अणु
	refcount_t		cl_count;
	atomic_t		cl_mds_count;
	पूर्णांक			cl_cons_state;	/* current स्थिरruction state (-ve: init error) */
#घोषणा NFS_CS_READY		0		/* पढ़ोy to be used */
#घोषणा NFS_CS_INITING		1		/* busy initialising */
#घोषणा NFS_CS_SESSION_INITING	2		/* busy initialising  session */
	अचिन्हित दीर्घ		cl_res_state;	/* NFS resources state */
#घोषणा NFS_CS_CALLBACK		1		/* - callback started */
#घोषणा NFS_CS_IDMAP		2		/* - idmap started */
#घोषणा NFS_CS_RENEWD		3		/* - renewd started */
#घोषणा NFS_CS_STOP_RENEW	4		/* no more state to renew */
#घोषणा NFS_CS_CHECK_LEASE_TIME	5		/* need to check lease समय */
	अचिन्हित दीर्घ		cl_flags;	/* behavior चयनes */
#घोषणा NFS_CS_NORESVPORT	0		/* - use ephemeral src port */
#घोषणा NFS_CS_DISCRTRY		1		/* - disconnect on RPC retry */
#घोषणा NFS_CS_MIGRATION	2		/* - transparent state migr */
#घोषणा NFS_CS_INFINITE_SLOTS	3		/* - करोn't limit TCP slots */
#घोषणा NFS_CS_NO_RETRANS_TIMEOUT	4	/* - Disable retransmit समयouts */
#घोषणा NFS_CS_TSM_POSSIBLE	5		/* - Maybe state migration */
#घोषणा NFS_CS_NOPING		6		/* - करोn't ping on connect */
#घोषणा NFS_CS_DS		7		/* - Server is a DS */
#घोषणा NFS_CS_REUSEPORT	8		/* - reuse src port on reconnect */
	काष्ठा sockaddr_storage	cl_addr;	/* server identअगरier */
	माप_प्रकार			cl_addrlen;
	अक्षर *			cl_hostname;	/* hostname of server */
	अक्षर *			cl_acceptor;	/* GSSAPI acceptor name */
	काष्ठा list_head	cl_share_link;	/* link in global client list */
	काष्ठा list_head	cl_superblocks;	/* List of nfs_server काष्ठाs */

	काष्ठा rpc_clnt *	cl_rpcclient;
	स्थिर काष्ठा nfs_rpc_ops *rpc_ops;	/* NFS protocol vector */
	पूर्णांक			cl_proto;	/* Network transport protocol */
	काष्ठा nfs_subversion *	cl_nfs_mod;	/* poपूर्णांकer to nfs version module */

	u32			cl_minorversion;/* NFSv4 minorversion */
	अचिन्हित पूर्णांक		cl_nconnect;	/* Number of connections */
	स्थिर अक्षर *		cl_principal;  /* used क्रम machine cred */

#अगर IS_ENABLED(CONFIG_NFS_V4)
	काष्ठा list_head	cl_ds_clients; /* auth flavor data servers */
	u64			cl_clientid;	/* स्थिरant */
	nfs4_verअगरier		cl_confirm;	/* Clientid verअगरier */
	अचिन्हित दीर्घ		cl_state;

	spinlock_t		cl_lock;

	अचिन्हित दीर्घ		cl_lease_समय;
	अचिन्हित दीर्घ		cl_last_renewal;
	काष्ठा delayed_work	cl_renewd;

	काष्ठा rpc_रुको_queue	cl_rpcरुकोq;

	/* idmapper */
	काष्ठा idmap *		cl_idmap;

	/* Client owner identअगरier */
	स्थिर अक्षर *		cl_owner_id;

	u32			cl_cb_ident;	/* v4.0 callback identअगरier */
	स्थिर काष्ठा nfs4_minor_version_ops *cl_mvops;
	अचिन्हित दीर्घ		cl_mig_gen;

	/* NFSv4.0 transport blocking */
	काष्ठा nfs4_slot_table	*cl_slot_tbl;

	/* The sequence id to use क्रम the next CREATE_SESSION */
	u32			cl_seqid;
	/* The flags used क्रम obtaining the clientid during EXCHANGE_ID */
	u32			cl_exchange_flags;
	काष्ठा nfs4_session	*cl_session;	/* shared session */
	bool			cl_preserve_clid;
	काष्ठा nfs41_server_owner *cl_serverowner;
	काष्ठा nfs41_server_scope *cl_serverscope;
	काष्ठा nfs41_impl_id	*cl_implid;
	/* nfs 4.1+ state protection modes: */
	अचिन्हित दीर्घ		cl_sp4_flags;
#घोषणा NFS_SP4_MACH_CRED_MINIMAL  1	/* Minimal sp4_mach_cred - state ops
					 * must use machine cred */
#घोषणा NFS_SP4_MACH_CRED_CLEANUP  2	/* CLOSE and LOCKU */
#घोषणा NFS_SP4_MACH_CRED_SECINFO  3	/* SECINFO and SECINFO_NO_NAME */
#घोषणा NFS_SP4_MACH_CRED_STATEID  4	/* TEST_STATEID and FREE_STATEID */
#घोषणा NFS_SP4_MACH_CRED_WRITE    5	/* WRITE */
#घोषणा NFS_SP4_MACH_CRED_COMMIT   6	/* COMMIT */
#घोषणा NFS_SP4_MACH_CRED_PNFS_CLEANUP  7 /* LAYOUTRETURN */
#अगर IS_ENABLED(CONFIG_NFS_V4_1)
	रुको_queue_head_t	cl_lock_रुकोq;
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
#पूर्ण_अगर /* CONFIG_NFS_V4 */

	/* Our own IP address, as a null-terminated string.
	 * This is used to generate the mv0 callback address.
	 */
	अक्षर			cl_ipaddr[48];

#अगर_घोषित CONFIG_NFS_FSCACHE
	काष्ठा fscache_cookie	*fscache;	/* client index cache cookie */
#पूर्ण_अगर

	काष्ठा net		*cl_net;
	काष्ठा list_head	pending_cb_stateids;
पूर्ण;

/*
 * NFS client parameters stored in the superblock.
 */
काष्ठा nfs_server अणु
	काष्ठा nfs_client *	nfs_client;	/* shared client and NFS4 state */
	काष्ठा list_head	client_link;	/* List of other nfs_server काष्ठाs
						 * that share the same client
						 */
	काष्ठा list_head	master_link;	/* link in master servers list */
	काष्ठा rpc_clnt *	client;		/* RPC client handle */
	काष्ठा rpc_clnt *	client_acl;	/* ACL RPC client handle */
	काष्ठा nlm_host		*nlm_host;	/* NLM client handle */
	काष्ठा nfs_iostats __percpu *io_stats;	/* I/O statistics */
	atomic_दीर्घ_t		ग_लिखोback;	/* number of ग_लिखोback pages */
	अचिन्हित पूर्णांक		flags;		/* various flags */

/* The following are क्रम पूर्णांकernal use only. Also see uapi/linux/nfs_mount.h */
#घोषणा NFS_MOUNT_LOOKUP_CACHE_NONEG	0x10000
#घोषणा NFS_MOUNT_LOOKUP_CACHE_NONE	0x20000
#घोषणा NFS_MOUNT_NORESVPORT		0x40000
#घोषणा NFS_MOUNT_LEGACY_INTERFACE	0x80000
#घोषणा NFS_MOUNT_LOCAL_FLOCK		0x100000
#घोषणा NFS_MOUNT_LOCAL_FCNTL		0x200000
#घोषणा NFS_MOUNT_SOFTERR		0x400000
#घोषणा NFS_MOUNT_SOFTREVAL		0x800000
#घोषणा NFS_MOUNT_WRITE_EAGER		0x01000000
#घोषणा NFS_MOUNT_WRITE_WAIT		0x02000000

	अचिन्हित पूर्णांक		fattr_valid;	/* Valid attributes */
	अचिन्हित पूर्णांक		caps;		/* server capabilities */
	अचिन्हित पूर्णांक		rsize;		/* पढ़ो size */
	अचिन्हित पूर्णांक		rpages;		/* पढ़ो size (in pages) */
	अचिन्हित पूर्णांक		wsize;		/* ग_लिखो size */
	अचिन्हित पूर्णांक		wpages;		/* ग_लिखो size (in pages) */
	अचिन्हित पूर्णांक		wपंचांगult;		/* server disk block size */
	अचिन्हित पूर्णांक		dtsize;		/* सूची_पढ़ो size */
	अचिन्हित लघु		port;		/* "port=" setting */
	अचिन्हित पूर्णांक		bsize;		/* server block size */
#अगर_घोषित CONFIG_NFS_V4_2
	अचिन्हित पूर्णांक		gxasize;	/* getxattr size */
	अचिन्हित पूर्णांक		sxasize;	/* setxattr size */
	अचिन्हित पूर्णांक		lxasize;	/* listxattr size */
#पूर्ण_अगर
	अचिन्हित पूर्णांक		acregmin;	/* attr cache समयouts */
	अचिन्हित पूर्णांक		acregmax;
	अचिन्हित पूर्णांक		acdirmin;
	अचिन्हित पूर्णांक		acdirmax;
	अचिन्हित पूर्णांक		namelen;
	अचिन्हित पूर्णांक		options;	/* extra options enabled by mount */
	अचिन्हित पूर्णांक		clone_blksize;	/* granularity of a CLONE operation */
#घोषणा NFS_OPTION_FSCACHE	0x00000001	/* - local caching enabled */
#घोषणा NFS_OPTION_MIGRATION	0x00000002	/* - NFSv4 migration enabled */

	क्रमागत nfs4_change_attr_type
				change_attr_type;/* Description of change attribute */

	काष्ठा nfs_fsid		fsid;
	__u64			maxfilesize;	/* maximum file size */
	काष्ठा बारpec64	समय_delta;	/* smallest समय granularity */
	अचिन्हित दीर्घ		mount_समय;	/* when this fs was mounted */
	काष्ठा super_block	*super;		/* VFS super block */
	dev_t			s_dev;		/* superblock dev numbers */
	काष्ठा nfs_auth_info	auth_info;	/* parsed auth flavors */

#अगर_घोषित CONFIG_NFS_FSCACHE
	काष्ठा nfs_fscache_key	*fscache_key;	/* unique key क्रम superblock */
	काष्ठा fscache_cookie	*fscache;	/* superblock cookie */
#पूर्ण_अगर

	u32			pnfs_blksize;	/* layout_blksize attr */
#अगर IS_ENABLED(CONFIG_NFS_V4)
	u32			attr_biपंचांगask[3];/* V4 biपंचांगask representing the set
						   of attributes supported on this
						   fileप्रणाली */
	u32			attr_biपंचांगask_nl[3];
						/* V4 biपंचांगask representing the
						   set of attributes supported
						   on this fileप्रणाली excluding
						   the label support bit. */
	u32			exclcreat_biपंचांगask[3];
						/* V4 biपंचांगask representing the
						   set of attributes supported
						   on this fileप्रणाली क्रम the
						   exclusive create. */
	u32			cache_consistency_biपंचांगask[3];
						/* V4 biपंचांगask representing the subset
						   of change attribute, size, स_समय
						   and mसमय attributes supported by
						   the server */
	u32			acl_biपंचांगask;	/* V4 biपंचांगask representing the ACEs
						   that are supported on this
						   fileप्रणाली */
	u32			fh_expire_type;	/* V4 biपंचांगask representing file
						   handle volatility type क्रम
						   this fileप्रणाली */
	काष्ठा pnfs_layoutdriver_type  *pnfs_curr_ld; /* Active layout driver */
	काष्ठा rpc_रुको_queue	roc_rpcरुकोq;
	व्योम			*pnfs_ld_data;	/* per mount poपूर्णांक data */

	/* the following fields are रक्षित by nfs_client->cl_lock */
	काष्ठा rb_root		state_owners;
#पूर्ण_अगर
	काष्ठा ida		खोलोowner_id;
	काष्ठा ida		lockowner_id;
	काष्ठा list_head	state_owners_lru;
	काष्ठा list_head	layouts;
	काष्ठा list_head	delegations;
	काष्ठा list_head	ss_copies;

	अचिन्हित दीर्घ		mig_gen;
	अचिन्हित दीर्घ		mig_status;
#घोषणा NFS_MIG_IN_TRANSITION		(1)
#घोषणा NFS_MIG_FAILED			(2)
#घोषणा NFS_MIG_TSM_POSSIBLE		(3)

	व्योम (*destroy)(काष्ठा nfs_server *);

	atomic_t active; /* Keep trace of any activity to this server */

	/* mountd-related mount options */
	काष्ठा sockaddr_storage	mountd_address;
	माप_प्रकार			mountd_addrlen;
	u32			mountd_version;
	अचिन्हित लघु		mountd_port;
	अचिन्हित लघु		mountd_protocol;
	काष्ठा rpc_रुको_queue	uoc_rpcरुकोq;

	/* XDR related inक्रमmation */
	अचिन्हित पूर्णांक		पढ़ो_hdrsize;

	/* User namespace info */
	स्थिर काष्ठा cred	*cred;
	bool			has_sec_mnt_opts;
पूर्ण;

/* Server capabilities */
#घोषणा NFS_CAP_READसूचीPLUS	(1U << 0)
#घोषणा NFS_CAP_HARDLINKS	(1U << 1)
#घोषणा NFS_CAP_SYMLINKS	(1U << 2)
#घोषणा NFS_CAP_ACLS		(1U << 3)
#घोषणा NFS_CAP_ATOMIC_OPEN	(1U << 4)
#घोषणा NFS_CAP_LGOPEN		(1U << 5)
#घोषणा NFS_CAP_POSIX_LOCK	(1U << 14)
#घोषणा NFS_CAP_UIDGID_NOMAP	(1U << 15)
#घोषणा NFS_CAP_STATEID_NFSV41	(1U << 16)
#घोषणा NFS_CAP_ATOMIC_OPEN_V1	(1U << 17)
#घोषणा NFS_CAP_SECURITY_LABEL	(1U << 18)
#घोषणा NFS_CAP_SEEK		(1U << 19)
#घोषणा NFS_CAP_ALLOCATE	(1U << 20)
#घोषणा NFS_CAP_DEALLOCATE	(1U << 21)
#घोषणा NFS_CAP_LAYOUTSTATS	(1U << 22)
#घोषणा NFS_CAP_CLONE		(1U << 23)
#घोषणा NFS_CAP_COPY		(1U << 24)
#घोषणा NFS_CAP_OFFLOAD_CANCEL	(1U << 25)
#घोषणा NFS_CAP_LAYOUTERROR	(1U << 26)
#घोषणा NFS_CAP_COPY_NOTIFY	(1U << 27)
#घोषणा NFS_CAP_XATTR		(1U << 28)
#घोषणा NFS_CAP_READ_PLUS	(1U << 29)

#पूर्ण_अगर
