<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* पूर्णांकernal AFS stuff
 *
 * Copyright (C) 2002, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/rxrpc.h>
#समावेश <linux/key.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>
#घोषणा FSCACHE_USE_NEW_IO_API
#समावेश <linux/fscache.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/uuid.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/dns_resolver.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>

#समावेश "afs.h"
#समावेश "afs_vl.h"

#घोषणा AFS_CELL_MAX_ADDRS 15

काष्ठा pagevec;
काष्ठा afs_call;
काष्ठा afs_vnode;

/*
 * Partial file-locking emulation mode.  (The problem being that AFS3 only
 * allows whole-file locks and no upgrading/करोwngrading).
 */
क्रमागत afs_flock_mode अणु
	afs_flock_mode_unset,
	afs_flock_mode_local,	/* Local locking only */
	afs_flock_mode_खोलोafs,	/* Don't get server lock क्रम a partial lock */
	afs_flock_mode_strict,	/* Always get a server lock क्रम a partial lock */
	afs_flock_mode_ग_लिखो,	/* Get an exclusive server lock क्रम a partial lock */
पूर्ण;

काष्ठा afs_fs_context अणु
	bool			क्रमce;		/* T to क्रमce cell type */
	bool			स्वतःcell;	/* T अगर set स्वतः mount operation */
	bool			dyn_root;	/* T अगर dynamic root */
	bool			no_cell;	/* T अगर the source is "none" (क्रम dynroot) */
	क्रमागत afs_flock_mode	flock_mode;	/* Partial file-locking emulation mode */
	afs_voltype_t		type;		/* type of volume requested */
	अचिन्हित पूर्णांक		volnamesz;	/* size of volume name */
	स्थिर अक्षर		*volname;	/* name of volume to mount */
	काष्ठा afs_net		*net;		/* the AFS net namespace stuff */
	काष्ठा afs_cell		*cell;		/* cell in which to find volume */
	काष्ठा afs_volume	*volume;	/* volume record */
	काष्ठा key		*key;		/* key to use क्रम secure mounting */
पूर्ण;

क्रमागत afs_call_state अणु
	AFS_CALL_CL_REQUESTING,		/* Client: Request is being sent */
	AFS_CALL_CL_AWAIT_REPLY,	/* Client: Aरुकोing reply */
	AFS_CALL_CL_PROC_REPLY,		/* Client: rxrpc call complete; processing reply */
	AFS_CALL_SV_AWAIT_OP_ID,	/* Server: Aरुकोing op ID */
	AFS_CALL_SV_AWAIT_REQUEST,	/* Server: Aरुकोing request data */
	AFS_CALL_SV_REPLYING,		/* Server: Replying */
	AFS_CALL_SV_AWAIT_ACK,		/* Server: Aरुकोing final ACK */
	AFS_CALL_COMPLETE,		/* Completed or failed */
पूर्ण;

/*
 * List of server addresses.
 */
काष्ठा afs_addr_list अणु
	काष्ठा rcu_head		rcu;
	refcount_t		usage;
	u32			version;	/* Version */
	अचिन्हित अक्षर		max_addrs;
	अचिन्हित अक्षर		nr_addrs;
	अचिन्हित अक्षर		preferred;	/* Preferred address */
	अचिन्हित अक्षर		nr_ipv4;	/* Number of IPv4 addresses */
	क्रमागत dns_record_source	source:8;
	क्रमागत dns_lookup_status	status:8;
	अचिन्हित दीर्घ		failed;		/* Mask of addrs that failed locally/ICMP */
	अचिन्हित दीर्घ		responded;	/* Mask of addrs that responded */
	काष्ठा sockaddr_rxrpc	addrs[];
#घोषणा AFS_MAX_ADDRESSES ((अचिन्हित पूर्णांक)(माप(अचिन्हित दीर्घ) * 8))
पूर्ण;

/*
 * a record of an in-progress RxRPC call
 */
काष्ठा afs_call अणु
	स्थिर काष्ठा afs_call_type *type;	/* type of call */
	काष्ठा afs_addr_list	*alist;		/* Address is alist[addr_ix] */
	रुको_queue_head_t	रुकोq;		/* processes aरुकोing completion */
	काष्ठा work_काष्ठा	async_work;	/* async I/O processor */
	काष्ठा work_काष्ठा	work;		/* actual work processor */
	काष्ठा rxrpc_call	*rxcall;	/* RxRPC call handle */
	काष्ठा key		*key;		/* security क्रम this call */
	काष्ठा afs_net		*net;		/* The network namespace */
	काष्ठा afs_server	*server;	/* The fileserver record अगर fs op (pins ref) */
	काष्ठा afs_vlserver	*vlserver;	/* The vlserver record अगर vl op */
	व्योम			*request;	/* request data (first part) */
	माप_प्रकार			iov_len;	/* Size of *iter to be used */
	काष्ठा iov_iter		def_iter;	/* Default buffer/data iterator */
	काष्ठा iov_iter		*ग_लिखो_iter;	/* Iterator defining ग_लिखो to be made */
	काष्ठा iov_iter		*iter;		/* Iterator currently in use */
	जोड़ अणु	/* Convenience क्रम ->def_iter */
		काष्ठा kvec	kvec[1];
		काष्ठा bio_vec	bvec[1];
	पूर्ण;
	व्योम			*buffer;	/* reply receive buffer */
	जोड़ अणु
		दीर्घ			ret0;	/* Value to reply with instead of 0 */
		काष्ठा afs_addr_list	*ret_alist;
		काष्ठा afs_vldb_entry	*ret_vldb;
		अक्षर			*ret_str;
	पूर्ण;
	काष्ठा afs_operation	*op;
	अचिन्हित पूर्णांक		server_index;
	atomic_t		usage;
	क्रमागत afs_call_state	state;
	spinlock_t		state_lock;
	पूर्णांक			error;		/* error code */
	u32			पात_code;	/* Remote पात ID or 0 */
	अचिन्हित पूर्णांक		max_lअगरespan;	/* Maximum lअगरespan to set अगर not 0 */
	अचिन्हित		request_size;	/* size of request data */
	अचिन्हित		reply_max;	/* maximum size of reply */
	अचिन्हित		count2;		/* count used in unmarshalling */
	अचिन्हित अक्षर		unmarshall;	/* unmarshalling phase */
	अचिन्हित अक्षर		addr_ix;	/* Address in ->alist */
	bool			drop_ref;	/* T अगर need to drop ref क्रम incoming call */
	bool			need_attention;	/* T अगर RxRPC poked us */
	bool			async;		/* T अगर asynchronous */
	bool			upgrade;	/* T to request service upgrade */
	bool			have_reply_समय; /* T अगर have got reply_समय */
	bool			पूर्णांकr;		/* T अगर पूर्णांकerruptible */
	bool			unmarshalling_error; /* T अगर an unmarshalling error occurred */
	u16			service_id;	/* Actual service ID (after upgrade) */
	अचिन्हित पूर्णांक		debug_id;	/* Trace ID */
	u32			operation_ID;	/* operation ID क्रम an incoming call */
	u32			count;		/* count क्रम use in unmarshalling */
	जोड़ अणु					/* place to extract temporary data */
		काष्ठा अणु
			__be32	पंचांगp_u;
			__be32	पंचांगp;
		पूर्ण __attribute__((packed));
		__be64		पंचांगp64;
	पूर्ण;
	kसमय_प्रकार			reply_समय;	/* Time of first reply packet */
पूर्ण;

काष्ठा afs_call_type अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक op; /* Really क्रमागत afs_fs_operation */

	/* deliver request or reply data to an call
	 * - वापसing an error will cause the call to be पातed
	 */
	पूर्णांक (*deliver)(काष्ठा afs_call *call);

	/* clean up a call */
	व्योम (*deकाष्ठाor)(काष्ठा afs_call *call);

	/* Work function */
	व्योम (*work)(काष्ठा work_काष्ठा *work);

	/* Call करोne function (माला_लो called immediately on success or failure) */
	व्योम (*करोne)(काष्ठा afs_call *call);
पूर्ण;

/*
 * Key available क्रम ग_लिखोback on a file.
 */
काष्ठा afs_wb_key अणु
	refcount_t		usage;
	काष्ठा key		*key;
	काष्ठा list_head	vnode_link;	/* Link in vnode->wb_keys */
पूर्ण;

/*
 * AFS खोलो file inक्रमmation record.  Poपूर्णांकed to by file->निजी_data.
 */
काष्ठा afs_file अणु
	काष्ठा key		*key;		/* The key this file was खोलोed with */
	काष्ठा afs_wb_key	*wb;		/* Writeback key record क्रम this file */
पूर्ण;

अटल अंतरभूत काष्ठा key *afs_file_key(काष्ठा file *file)
अणु
	काष्ठा afs_file *af = file->निजी_data;

	वापस af->key;
पूर्ण

/*
 * Record of an outstanding पढ़ो operation on a vnode.
 */
काष्ठा afs_पढ़ो अणु
	loff_t			pos;		/* Where to start पढ़ोing */
	loff_t			len;		/* How much we're asking क्रम */
	loff_t			actual_len;	/* How much we're actually getting */
	loff_t			file_size;	/* File size वापसed by server */
	काष्ठा key		*key;		/* The key to use to reissue the पढ़ो */
	काष्ठा afs_vnode	*vnode;		/* The file being पढ़ो पूर्णांकo. */
	काष्ठा netfs_पढ़ो_subrequest *subreq;	/* Fscache helper पढ़ो request this beदीर्घs to */
	afs_dataversion_t	data_version;	/* Version number वापसed by server */
	refcount_t		usage;
	अचिन्हित पूर्णांक		call_debug_id;
	अचिन्हित पूर्णांक		nr_pages;
	पूर्णांक			error;
	व्योम (*करोne)(काष्ठा afs_पढ़ो *);
	व्योम (*cleanup)(काष्ठा afs_पढ़ो *);
	काष्ठा iov_iter		*iter;		/* Iterator representing the buffer */
	काष्ठा iov_iter		def_iter;	/* Default iterator */
पूर्ण;

/*
 * AFS superblock निजी data
 * - there's one superblock per volume
 */
काष्ठा afs_super_info अणु
	काष्ठा net		*net_ns;	/* Network namespace */
	काष्ठा afs_cell		*cell;		/* The cell in which the volume resides */
	काष्ठा afs_volume	*volume;	/* volume record */
	क्रमागत afs_flock_mode	flock_mode:8;	/* File locking emulation mode */
	bool			dyn_root;	/* True अगर dynamic root */
पूर्ण;

अटल अंतरभूत काष्ठा afs_super_info *AFS_FS_S(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

बाह्य काष्ठा file_प्रणाली_type afs_fs_type;

/*
 * Set of substitutes क्रम @sys.
 */
काष्ठा afs_sysnames अणु
#घोषणा AFS_NR_SYSNAME 16
	अक्षर			*subs[AFS_NR_SYSNAME];
	refcount_t		usage;
	अचिन्हित लघु		nr;
	अक्षर			blank[1];
पूर्ण;

/*
 * AFS network namespace record.
 */
काष्ठा afs_net अणु
	काष्ठा net		*net;		/* Backpoपूर्णांकer to the owning net namespace */
	काष्ठा afs_uuid		uuid;
	bool			live;		/* F अगर this namespace is being हटाओd */

	/* AF_RXRPC I/O stuff */
	काष्ठा socket		*socket;
	काष्ठा afs_call		*spare_incoming_call;
	काष्ठा work_काष्ठा	अक्षरge_pपुनः_स्मृतिation_work;
	काष्ठा mutex		socket_mutex;
	atomic_t		nr_outstanding_calls;
	atomic_t		nr_superblocks;

	/* Cell database */
	काष्ठा rb_root		cells;
	काष्ठा afs_cell		*ws_cell;
	काष्ठा work_काष्ठा	cells_manager;
	काष्ठा समयr_list	cells_समयr;
	atomic_t		cells_outstanding;
	काष्ठा rw_semaphore	cells_lock;
	काष्ठा mutex		cells_alias_lock;

	काष्ठा mutex		proc_cells_lock;
	काष्ठा hlist_head	proc_cells;

	/* Known servers.  Theoretically each fileserver can only be in one
	 * cell, but in practice, people create aliases and subsets and there's
	 * no easy way to distinguish them.
	 */
	seqlock_t		fs_lock;	/* For fs_servers, fs_probe_*, fs_proc */
	काष्ठा rb_root		fs_servers;	/* afs_server (by server UUID or address) */
	काष्ठा list_head	fs_probe_fast;	/* List of afs_server to probe at 30s पूर्णांकervals */
	काष्ठा list_head	fs_probe_slow;	/* List of afs_server to probe at 5m पूर्णांकervals */
	काष्ठा hlist_head	fs_proc;	/* procfs servers list */

	काष्ठा hlist_head	fs_addresses4;	/* afs_server (by lowest IPv4 addr) */
	काष्ठा hlist_head	fs_addresses6;	/* afs_server (by lowest IPv6 addr) */
	seqlock_t		fs_addr_lock;	/* For fs_addresses[46] */

	काष्ठा work_काष्ठा	fs_manager;
	काष्ठा समयr_list	fs_समयr;

	काष्ठा work_काष्ठा	fs_prober;
	काष्ठा समयr_list	fs_probe_समयr;
	atomic_t		servers_outstanding;

	/* File locking renewal management */
	काष्ठा mutex		lock_manager_mutex;

	/* Misc */
	काष्ठा super_block	*dynroot_sb;	/* Dynamic root mount superblock */
	काष्ठा proc_dir_entry	*proc_afs;	/* /proc/net/afs directory */
	काष्ठा afs_sysnames	*sysnames;
	rwlock_t		sysnames_lock;

	/* Statistics counters */
	atomic_t		n_lookup;	/* Number of lookups करोne */
	atomic_t		n_reval;	/* Number of dentries needing revalidation */
	atomic_t		n_inval;	/* Number of invalidations by the server */
	atomic_t		n_relpg;	/* Number of invalidations by releasepage */
	atomic_t		n_पढ़ो_dir;	/* Number of directory pages पढ़ो */
	atomic_t		n_dir_cr;	/* Number of directory entry creation edits */
	atomic_t		n_dir_rm;	/* Number of directory entry removal edits */
	atomic_t		n_stores;	/* Number of store ops */
	atomic_दीर्घ_t		n_store_bytes;	/* Number of bytes stored */
	atomic_दीर्घ_t		n_fetch_bytes;	/* Number of bytes fetched */
	atomic_t		n_fetches;	/* Number of data fetch ops */
पूर्ण;

बाह्य स्थिर अक्षर afs_init_sysname[];

क्रमागत afs_cell_state अणु
	AFS_CELL_UNSET,
	AFS_CELL_ACTIVATING,
	AFS_CELL_ACTIVE,
	AFS_CELL_DEACTIVATING,
	AFS_CELL_INACTIVE,
	AFS_CELL_FAILED,
	AFS_CELL_REMOVED,
पूर्ण;

/*
 * AFS cell record.
 *
 * This is a tricky concept to get right as it is possible to create aliases
 * simply by poपूर्णांकing AFSDB/SRV records क्रम two names at the same set of VL
 * servers; it is also possible to करो things like setting up two sets of VL
 * servers, one of which provides a superset of the volumes provided by the
 * other (क्रम पूर्णांकernal/बाह्यal भागision, क्रम example).
 *
 * Cells only exist in the sense that (a) a cell's name maps to a set of VL
 * servers and (b) a cell's name is used by the client to select the key to use
 * क्रम authentication and encryption.  The cell name is not typically used in
 * the protocol.
 *
 * Two cells are determined to be aliases अगर they have an explicit alias (YFS
 * only), share any VL servers in common or have at least one volume in common.
 * "In common" means that the address list of the VL servers or the fileservers
 * share at least one endpoपूर्णांक.
 */
काष्ठा afs_cell अणु
	जोड़ अणु
		काष्ठा rcu_head	rcu;
		काष्ठा rb_node	net_node;	/* Node in net->cells */
	पूर्ण;
	काष्ठा afs_net		*net;
	काष्ठा afs_cell		*alias_of;	/* The cell this is an alias of */
	काष्ठा afs_volume	*root_volume;	/* The root.cell volume अगर there is one */
	काष्ठा key		*anonymous_key;	/* anonymous user key क्रम this cell */
	काष्ठा work_काष्ठा	manager;	/* Manager क्रम init/deinit/dns */
	काष्ठा hlist_node	proc_link;	/* /proc cell list link */
#अगर_घोषित CONFIG_AFS_FSCACHE
	काष्ठा fscache_cookie	*cache;		/* caching cookie */
#पूर्ण_अगर
	समय64_t		dns_expiry;	/* Time AFSDB/SRV record expires */
	समय64_t		last_inactive;	/* Time of last drop of usage count */
	atomic_t		ref;		/* Struct refcount */
	atomic_t		active;		/* Active usage counter */
	अचिन्हित दीर्घ		flags;
#घोषणा AFS_CELL_FL_NO_GC	0		/* The cell was added manually, करोn't स्वतः-gc */
#घोषणा AFS_CELL_FL_DO_LOOKUP	1		/* DNS lookup requested */
#घोषणा AFS_CELL_FL_CHECK_ALIAS	2		/* Need to check क्रम aliases */
	क्रमागत afs_cell_state	state;
	लघु			error;
	क्रमागत dns_record_source	dns_source:8;	/* Latest source of data from lookup */
	क्रमागत dns_lookup_status	dns_status:8;	/* Latest status of data from lookup */
	अचिन्हित पूर्णांक		dns_lookup_count; /* Counter of DNS lookups */
	अचिन्हित पूर्णांक		debug_id;

	/* The volumes beदीर्घing to this cell */
	काष्ठा rb_root		volumes;	/* Tree of volumes on this server */
	काष्ठा hlist_head	proc_volumes;	/* procfs volume list */
	seqlock_t		volume_lock;	/* For volumes */

	/* Active fileserver पूर्णांकeraction state. */
	काष्ठा rb_root		fs_servers;	/* afs_server (by server UUID) */
	seqlock_t		fs_lock;	/* For fs_servers  */

	/* VL server list. */
	rwlock_t		vl_servers_lock; /* Lock on vl_servers */
	काष्ठा afs_vlserver_list __rcu *vl_servers;

	u8			name_len;	/* Length of name */
	अक्षर			*name;		/* Cell name, हाल-flattened and NUL-padded */
पूर्ण;

/*
 * Volume Location server record.
 */
काष्ठा afs_vlserver अणु
	काष्ठा rcu_head		rcu;
	काष्ठा afs_addr_list	__rcu *addresses; /* List of addresses क्रम this VL server */
	अचिन्हित दीर्घ		flags;
#घोषणा AFS_VLSERVER_FL_PROBED	0		/* The VL server has been probed */
#घोषणा AFS_VLSERVER_FL_PROBING	1		/* VL server is being probed */
#घोषणा AFS_VLSERVER_FL_IS_YFS	2		/* Server is YFS not AFS */
#घोषणा AFS_VLSERVER_FL_RESPONDING 3		/* VL server is responding */
	rwlock_t		lock;		/* Lock on addresses */
	atomic_t		usage;
	अचिन्हित पूर्णांक		rtt;		/* Server's current RTT in uS */

	/* Probe state */
	रुको_queue_head_t	probe_wq;
	atomic_t		probe_outstanding;
	spinlock_t		probe_lock;
	काष्ठा अणु
		अचिन्हित पूर्णांक	rtt;		/* RTT in uS */
		u32		पात_code;
		लघु		error;
		अचिन्हित लघु	flags;
#घोषणा AFS_VLSERVER_PROBE_RESPONDED		0x01 /* At least once response (may be पात) */
#घोषणा AFS_VLSERVER_PROBE_IS_YFS		0x02 /* The peer appears to be YFS */
#घोषणा AFS_VLSERVER_PROBE_NOT_YFS		0x04 /* The peer appears not to be YFS */
#घोषणा AFS_VLSERVER_PROBE_LOCAL_FAILURE	0x08 /* A local failure prevented a probe */
	पूर्ण probe;

	u16			port;
	u16			name_len;	/* Length of name */
	अक्षर			name[];		/* Server name, हाल-flattened */
पूर्ण;

/*
 * Weighted list of Volume Location servers.
 */
काष्ठा afs_vlserver_entry अणु
	u16			priority;	/* Preference (as SRV) */
	u16			weight;		/* Weight (as SRV) */
	क्रमागत dns_record_source	source:8;
	क्रमागत dns_lookup_status	status:8;
	काष्ठा afs_vlserver	*server;
पूर्ण;

काष्ठा afs_vlserver_list अणु
	काष्ठा rcu_head		rcu;
	atomic_t		usage;
	u8			nr_servers;
	u8			index;		/* Server currently in use */
	u8			preferred;	/* Preferred server */
	क्रमागत dns_record_source	source:8;
	क्रमागत dns_lookup_status	status:8;
	rwlock_t		lock;
	काष्ठा afs_vlserver_entry servers[];
पूर्ण;

/*
 * Cached VLDB entry.
 *
 * This is poपूर्णांकed to by cell->vldb_entries, indexed by name.
 */
काष्ठा afs_vldb_entry अणु
	afs_volid_t		vid[3];		/* Volume IDs क्रम R/W, R/O and Bak volumes */

	अचिन्हित दीर्घ		flags;
#घोषणा AFS_VLDB_HAS_RW		0		/* - R/W volume exists */
#घोषणा AFS_VLDB_HAS_RO		1		/* - R/O volume exists */
#घोषणा AFS_VLDB_HAS_BAK	2		/* - Backup volume exists */
#घोषणा AFS_VLDB_QUERY_VALID	3		/* - Record is valid */
#घोषणा AFS_VLDB_QUERY_ERROR	4		/* - VL server वापसed error */

	uuid_t			fs_server[AFS_NMAXNSERVERS];
	u32			addr_version[AFS_NMAXNSERVERS]; /* Registration change counters */
	u8			fs_mask[AFS_NMAXNSERVERS];
#घोषणा AFS_VOL_VTM_RW	0x01 /* R/W version of the volume is available (on this server) */
#घोषणा AFS_VOL_VTM_RO	0x02 /* R/O version of the volume is available (on this server) */
#घोषणा AFS_VOL_VTM_BAK	0x04 /* backup version of the volume is available (on this server) */
	लघु			error;
	u8			nr_servers;	/* Number of server records */
	u8			name_len;
	u8			name[AFS_MAXVOLNAME + 1]; /* NUL-padded volume name */
पूर्ण;

/*
 * Record of fileserver with which we're actively communicating.
 */
काष्ठा afs_server अणु
	काष्ठा rcu_head		rcu;
	जोड़ अणु
		uuid_t		uuid;		/* Server ID */
		काष्ठा afs_uuid	_uuid;
	पूर्ण;

	काष्ठा afs_addr_list	__rcu *addresses;
	काष्ठा afs_cell		*cell;		/* Cell to which beदीर्घs (pins ref) */
	काष्ठा rb_node		uuid_rb;	/* Link in net->fs_servers */
	काष्ठा afs_server __rcu	*uuid_next;	/* Next server with same UUID */
	काष्ठा afs_server	*uuid_prev;	/* Previous server with same UUID */
	काष्ठा list_head	probe_link;	/* Link in net->fs_probe_list */
	काष्ठा hlist_node	addr4_link;	/* Link in net->fs_addresses4 */
	काष्ठा hlist_node	addr6_link;	/* Link in net->fs_addresses6 */
	काष्ठा hlist_node	proc_link;	/* Link in net->fs_proc */
	काष्ठा afs_server	*gc_next;	/* Next server in manager's list */
	समय64_t		unuse_समय;	/* Time at which last unused */
	अचिन्हित दीर्घ		flags;
#घोषणा AFS_SERVER_FL_RESPONDING 0		/* The server is responding */
#घोषणा AFS_SERVER_FL_UPDATING	1
#घोषणा AFS_SERVER_FL_NEEDS_UPDATE 2		/* Fileserver address list is out of date */
#घोषणा AFS_SERVER_FL_NOT_READY	4		/* The record is not पढ़ोy क्रम use */
#घोषणा AFS_SERVER_FL_NOT_FOUND	5		/* VL server says no such server */
#घोषणा AFS_SERVER_FL_VL_FAIL	6		/* Failed to access VL server */
#घोषणा AFS_SERVER_FL_MAY_HAVE_CB 8		/* May have callbacks on this fileserver */
#घोषणा AFS_SERVER_FL_IS_YFS	16		/* Server is YFS not AFS */
#घोषणा AFS_SERVER_FL_NO_IBULK	17		/* Fileserver करोesn't support FS.InlineBulkStatus */
#घोषणा AFS_SERVER_FL_NO_RM2	18		/* Fileserver करोesn't support YFS.RemoveFile2 */
	atomic_t		ref;		/* Object refcount */
	atomic_t		active;		/* Active user count */
	u32			addr_version;	/* Address list version */
	अचिन्हित पूर्णांक		rtt;		/* Server's current RTT in uS */
	अचिन्हित पूर्णांक		debug_id;	/* Debugging ID क्रम traces */

	/* file service access */
	rwlock_t		fs_lock;	/* access lock */

	/* callback promise management */
	अचिन्हित		cb_s_अवरोध;	/* Break-everything counter. */

	/* Probe state */
	अचिन्हित दीर्घ		probed_at;	/* Time last probe was dispatched (jअगरfies) */
	रुको_queue_head_t	probe_wq;
	atomic_t		probe_outstanding;
	spinlock_t		probe_lock;
	काष्ठा अणु
		अचिन्हित पूर्णांक	rtt;		/* RTT in uS */
		u32		पात_code;
		लघु		error;
		bool		responded:1;
		bool		is_yfs:1;
		bool		not_yfs:1;
		bool		local_failure:1;
	पूर्ण probe;
पूर्ण;

/*
 * Replaceable volume server list.
 */
काष्ठा afs_server_entry अणु
	काष्ठा afs_server	*server;
पूर्ण;

काष्ठा afs_server_list अणु
	afs_volid_t		vids[AFS_MAXTYPES]; /* Volume IDs */
	refcount_t		usage;
	अचिन्हित अक्षर		nr_servers;
	अचिन्हित अक्षर		preferred;	/* Preferred server */
	अचिन्हित लघु		vnovol_mask;	/* Servers to be skipped due to VNOVOL */
	अचिन्हित पूर्णांक		seq;		/* Set to ->servers_seq when installed */
	rwlock_t		lock;
	काष्ठा afs_server_entry	servers[];
पूर्ण;

/*
 * Live AFS volume management.
 */
काष्ठा afs_volume अणु
	जोड़ अणु
		काष्ठा rcu_head	rcu;
		afs_volid_t	vid;		/* volume ID */
	पूर्ण;
	atomic_t		usage;
	समय64_t		update_at;	/* Time at which to next update */
	काष्ठा afs_cell		*cell;		/* Cell to which beदीर्घs (pins ref) */
	काष्ठा rb_node		cell_node;	/* Link in cell->volumes */
	काष्ठा hlist_node	proc_link;	/* Link in cell->proc_volumes */
	काष्ठा super_block __rcu *sb;		/* Superblock on which inodes reside */
	अचिन्हित दीर्घ		flags;
#घोषणा AFS_VOLUME_NEEDS_UPDATE	0	/* - T अगर an update needs perक्रमming */
#घोषणा AFS_VOLUME_UPDATING	1	/* - T अगर an update is in progress */
#घोषणा AFS_VOLUME_WAIT		2	/* - T अगर users must रुको क्रम update */
#घोषणा AFS_VOLUME_DELETED	3	/* - T अगर volume appears deleted */
#घोषणा AFS_VOLUME_OFFLINE	4	/* - T अगर volume offline notice given */
#घोषणा AFS_VOLUME_BUSY		5	/* - T अगर volume busy notice given */
#घोषणा AFS_VOLUME_MAYBE_NO_IBULK 6	/* - T अगर some servers करोn't have InlineBulkStatus */
#अगर_घोषित CONFIG_AFS_FSCACHE
	काष्ठा fscache_cookie	*cache;		/* caching cookie */
#पूर्ण_अगर
	काष्ठा afs_server_list __rcu *servers;	/* List of servers on which volume resides */
	rwlock_t		servers_lock;	/* Lock क्रम ->servers */
	अचिन्हित पूर्णांक		servers_seq;	/* Incremented each समय ->servers changes */

	अचिन्हित		cb_v_अवरोध;	/* Break-everything counter. */
	rwlock_t		cb_v_अवरोध_lock;

	afs_voltype_t		type;		/* type of volume */
	अक्षर			type_क्रमce;	/* क्रमce volume type (suppress R/O -> R/W) */
	u8			name_len;
	u8			name[AFS_MAXVOLNAME + 1]; /* NUL-padded volume name */
पूर्ण;

क्रमागत afs_lock_state अणु
	AFS_VNODE_LOCK_NONE,		/* The vnode has no lock on the server */
	AFS_VNODE_LOCK_WAITING_FOR_CB,	/* We're रुकोing क्रम the server to अवरोध the callback */
	AFS_VNODE_LOCK_SETTING,		/* We're asking the server क्रम a lock */
	AFS_VNODE_LOCK_GRANTED,		/* We have a lock on the server */
	AFS_VNODE_LOCK_EXTENDING,	/* We're extending a lock on the server */
	AFS_VNODE_LOCK_NEED_UNLOCK,	/* We need to unlock on the server */
	AFS_VNODE_LOCK_UNLOCKING,	/* We're telling the server to unlock */
	AFS_VNODE_LOCK_DELETED,		/* The vnode has been deleted whilst we have a lock */
पूर्ण;

/*
 * AFS inode निजी data.
 *
 * Note that afs_alloc_inode() *must* reset anything that could incorrectly
 * leak from one inode to another.
 */
काष्ठा afs_vnode अणु
	काष्ठा inode		vfs_inode;	/* the VFS's inode record */

	काष्ठा afs_volume	*volume;	/* volume on which vnode resides */
	काष्ठा afs_fid		fid;		/* the file identअगरier क्रम this inode */
	काष्ठा afs_file_status	status;		/* AFS status info क्रम this file */
	afs_dataversion_t	invalid_beक्रमe;	/* Child dentries are invalid beक्रमe this */
#अगर_घोषित CONFIG_AFS_FSCACHE
	काष्ठा fscache_cookie	*cache;		/* caching cookie */
#पूर्ण_अगर
	काष्ठा afs_permits __rcu *permit_cache;	/* cache of permits so far obtained */
	काष्ठा mutex		io_lock;	/* Lock क्रम serialising I/O on this mutex */
	काष्ठा rw_semaphore	validate_lock;	/* lock क्रम validating this vnode */
	काष्ठा rw_semaphore	सूची_हटाओ_lock;	/* Lock क्रम सूची_हटाओ vs sillyनाम */
	काष्ठा key		*silly_key;	/* Silly नाम key */
	spinlock_t		wb_lock;	/* lock क्रम wb_keys */
	spinlock_t		lock;		/* रुकोqueue/flags lock */
	अचिन्हित दीर्घ		flags;
#घोषणा AFS_VNODE_CB_PROMISED	0		/* Set अगर vnode has a callback promise */
#घोषणा AFS_VNODE_UNSET		1		/* set अगर vnode attributes not yet set */
#घोषणा AFS_VNODE_सूची_VALID	2		/* Set अगर dir contents are valid */
#घोषणा AFS_VNODE_ZAP_DATA	3		/* set अगर vnode's data should be invalidated */
#घोषणा AFS_VNODE_DELETED	4		/* set अगर vnode deleted on server */
#घोषणा AFS_VNODE_MOUNTPOINT	5		/* set अगर vnode is a mountpoपूर्णांक symlink */
#घोषणा AFS_VNODE_AUTOCELL	6		/* set अगर Vnode is an स्वतः mount poपूर्णांक */
#घोषणा AFS_VNODE_PSEUDOसूची	7 		/* set अगर Vnode is a pseuकरो directory */
#घोषणा AFS_VNODE_NEW_CONTENT	8		/* Set अगर file has new content (create/trunc-0) */
#घोषणा AFS_VNODE_SILLY_DELETED	9		/* Set अगर file has been silly-deleted */
#घोषणा AFS_VNODE_MODIFYING	10		/* Set अगर we're perक्रमming a modअगरication op */

	काष्ठा list_head	wb_keys;	/* List of keys available क्रम ग_लिखोback */
	काष्ठा list_head	pending_locks;	/* locks रुकोing to be granted */
	काष्ठा list_head	granted_locks;	/* locks granted on this file */
	काष्ठा delayed_work	lock_work;	/* work to be करोne in locking */
	काष्ठा key		*lock_key;	/* Key to be used in lock ops */
	kसमय_प्रकार			locked_at;	/* Time at which lock obtained */
	क्रमागत afs_lock_state	lock_state : 8;
	afs_lock_type_t		lock_type : 8;

	/* outstanding callback notअगरication on this file */
	व्योम			*cb_server;	/* Server with callback/filelock */
	अचिन्हित पूर्णांक		cb_s_अवरोध;	/* Mass अवरोध counter on ->server */
	अचिन्हित पूर्णांक		cb_v_अवरोध;	/* Mass अवरोध counter on ->volume */
	अचिन्हित पूर्णांक		cb_अवरोध;	/* Break counter on vnode */
	seqlock_t		cb_lock;	/* Lock क्रम ->cb_server, ->status, ->cb_*अवरोध */

	समय64_t		cb_expires_at;	/* समय at which callback expires */
पूर्ण;

अटल अंतरभूत काष्ठा fscache_cookie *afs_vnode_cache(काष्ठा afs_vnode *vnode)
अणु
#अगर_घोषित CONFIG_AFS_FSCACHE
	वापस vnode->cache;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

/*
 * cached security record क्रम one user's attempt to access a vnode
 */
काष्ठा afs_permit अणु
	काष्ठा key		*key;		/* RxRPC ticket holding a security context */
	afs_access_t		access;		/* CallerAccess value क्रम this key */
पूर्ण;

/*
 * Immutable cache of CallerAccess records from attempts to access vnodes.
 * These may be shared between multiple vnodes.
 */
काष्ठा afs_permits अणु
	काष्ठा rcu_head		rcu;
	काष्ठा hlist_node	hash_node;	/* Link in hash */
	अचिन्हित दीर्घ		h;		/* Hash value क्रम this permit list */
	refcount_t		usage;
	अचिन्हित लघु		nr_permits;	/* Number of records */
	bool			invalidated;	/* Invalidated due to key change */
	काष्ठा afs_permit	permits[];	/* List of permits sorted by key poपूर्णांकer */
पूर्ण;

/*
 * Error prioritisation and accumulation.
 */
काष्ठा afs_error अणु
	लघु	error;			/* Accumulated error */
	bool	responded;		/* T अगर server responded */
पूर्ण;

/*
 * Cursor क्रम iterating over a server's address list.
 */
काष्ठा afs_addr_cursor अणु
	काष्ठा afs_addr_list	*alist;		/* Current address list (pins ref) */
	अचिन्हित दीर्घ		tried;		/* Tried addresses */
	चिन्हित अक्षर		index;		/* Current address */
	bool			responded;	/* T अगर the current address responded */
	अचिन्हित लघु		nr_iterations;	/* Number of address iterations */
	लघु			error;
	u32			पात_code;
पूर्ण;

/*
 * Cursor क्रम iterating over a set of volume location servers.
 */
काष्ठा afs_vl_cursor अणु
	काष्ठा afs_addr_cursor	ac;
	काष्ठा afs_cell		*cell;		/* The cell we're querying */
	काष्ठा afs_vlserver_list *server_list;	/* Current server list (pins ref) */
	काष्ठा afs_vlserver	*server;	/* Server on which this resides */
	काष्ठा key		*key;		/* Key क्रम the server */
	अचिन्हित दीर्घ		untried;	/* Biपंचांगask of untried servers */
	लघु			index;		/* Current server */
	लघु			error;
	अचिन्हित लघु		flags;
#घोषणा AFS_VL_CURSOR_STOP	0x0001		/* Set to cease iteration */
#घोषणा AFS_VL_CURSOR_RETRY	0x0002		/* Set to करो a retry */
#घोषणा AFS_VL_CURSOR_RETRIED	0x0004		/* Set अगर started a retry */
	अचिन्हित लघु		nr_iterations;	/* Number of server iterations */
पूर्ण;

/*
 * Fileserver operation methods.
 */
काष्ठा afs_operation_ops अणु
	व्योम (*issue_afs_rpc)(काष्ठा afs_operation *op);
	व्योम (*issue_yfs_rpc)(काष्ठा afs_operation *op);
	व्योम (*success)(काष्ठा afs_operation *op);
	व्योम (*पातed)(काष्ठा afs_operation *op);
	व्योम (*failed)(काष्ठा afs_operation *op);
	व्योम (*edit_dir)(काष्ठा afs_operation *op);
	व्योम (*put)(काष्ठा afs_operation *op);
पूर्ण;

काष्ठा afs_vnode_param अणु
	काष्ठा afs_vnode	*vnode;
	काष्ठा afs_fid		fid;		/* Fid to access */
	काष्ठा afs_status_cb	scb;		/* Returned status and callback promise */
	afs_dataversion_t	dv_beक्रमe;	/* Data version beक्रमe the call */
	अचिन्हित पूर्णांक		cb_अवरोध_beक्रमe; /* cb_अवरोध + cb_s_अवरोध beक्रमe the call */
	u8			dv_delta;	/* Expected change in data version */
	bool			put_vnode:1;	/* T अगर we have a ref on the vnode */
	bool			need_io_lock:1;	/* T अगर we need the I/O lock on this */
	bool			update_स_समय:1;	/* Need to update the स_समय */
	bool			set_size:1;	/* Must update i_size */
	bool			op_unlinked:1;	/* True अगर file was unlinked by op */
	bool			speculative:1;	/* T अगर speculative status fetch (no vnode lock) */
	bool			modअगरication:1;	/* Set अगर the content माला_लो modअगरied */
पूर्ण;

/*
 * Fileserver operation wrapper, handling server and address rotation
 * asynchronously.  May make simultaneous calls to multiple servers.
 */
काष्ठा afs_operation अणु
	काष्ठा afs_net		*net;		/* Network namespace */
	काष्ठा key		*key;		/* Key क्रम the cell */
	स्थिर काष्ठा afs_call_type *type;	/* Type of call करोne */
	स्थिर काष्ठा afs_operation_ops *ops;

	/* Parameters/results क्रम the operation */
	काष्ठा afs_volume	*volume;	/* Volume being accessed */
	काष्ठा afs_vnode_param	file[2];
	काष्ठा afs_vnode_param	*more_files;
	काष्ठा afs_volsync	volsync;
	काष्ठा dentry		*dentry;	/* Dentry to be altered */
	काष्ठा dentry		*dentry_2;	/* Second dentry to be altered */
	काष्ठा बारpec64	mसमय;		/* Modअगरication समय to record */
	काष्ठा बारpec64	स_समय;		/* Change समय to set */
	लघु			nr_files;	/* Number of entries in file[], more_files */
	लघु			error;
	अचिन्हित पूर्णांक		debug_id;

	अचिन्हित पूर्णांक		cb_v_अवरोध;	/* Volume अवरोध counter beक्रमe op */
	अचिन्हित पूर्णांक		cb_s_अवरोध;	/* Server अवरोध counter beक्रमe op */

	जोड़ अणु
		काष्ठा अणु
			पूर्णांक	which;		/* Which ->file[] to fetch क्रम */
		पूर्ण fetch_status;
		काष्ठा अणु
			पूर्णांक	reason;		/* क्रमागत afs_edit_dir_reason */
			mode_t	mode;
			स्थिर अक्षर *symlink;
		पूर्ण create;
		काष्ठा अणु
			bool	need_rehash;
		पूर्ण unlink;
		काष्ठा अणु
			काष्ठा dentry *rehash;
			काष्ठा dentry *पंचांगp;
			bool	new_negative;
		पूर्ण नाम;
		काष्ठा अणु
			काष्ठा afs_पढ़ो *req;
		पूर्ण fetch;
		काष्ठा अणु
			afs_lock_type_t type;
		पूर्ण lock;
		काष्ठा अणु
			काष्ठा iov_iter	*ग_लिखो_iter;
			loff_t	pos;
			loff_t	size;
			loff_t	i_size;
			bool	laundering;	/* Laundering page, PG_ग_लिखोback not set */
		पूर्ण store;
		काष्ठा अणु
			काष्ठा iattr	*attr;
			loff_t		old_i_size;
		पूर्ण setattr;
		काष्ठा afs_acl	*acl;
		काष्ठा yfs_acl	*yacl;
		काष्ठा अणु
			काष्ठा afs_volume_status vs;
			काष्ठा kstatfs		*buf;
		पूर्ण volstatus;
	पूर्ण;

	/* Fileserver iteration state */
	काष्ठा afs_addr_cursor	ac;
	काष्ठा afs_server_list	*server_list;	/* Current server list (pins ref) */
	काष्ठा afs_server	*server;	/* Server we're using (ref pinned by server_list) */
	काष्ठा afs_call		*call;
	अचिन्हित दीर्घ		untried;	/* Biपंचांगask of untried servers */
	लघु			index;		/* Current server */
	अचिन्हित लघु		nr_iterations;	/* Number of server iterations */

	अचिन्हित पूर्णांक		flags;
#घोषणा AFS_OPERATION_STOP		0x0001	/* Set to cease iteration */
#घोषणा AFS_OPERATION_VBUSY		0x0002	/* Set अगर seen VBUSY */
#घोषणा AFS_OPERATION_VMOVED		0x0004	/* Set अगर seen VMOVED */
#घोषणा AFS_OPERATION_VNOVOL		0x0008	/* Set अगर seen VNOVOL */
#घोषणा AFS_OPERATION_CUR_ONLY		0x0010	/* Set अगर current server only (file lock held) */
#घोषणा AFS_OPERATION_NO_VSLEEP		0x0020	/* Set to prevent sleep on VBUSY, VOFFLINE, ... */
#घोषणा AFS_OPERATION_UNINTR		0x0040	/* Set अगर op is unपूर्णांकerruptible */
#घोषणा AFS_OPERATION_DOWNGRADE		0x0080	/* Set to retry with करोwngraded opcode */
#घोषणा AFS_OPERATION_LOCK_0		0x0100	/* Set अगर have io_lock on file[0] */
#घोषणा AFS_OPERATION_LOCK_1		0x0200	/* Set अगर have io_lock on file[1] */
#घोषणा AFS_OPERATION_TRIED_ALL		0x0400	/* Set अगर we've tried all the fileservers */
#घोषणा AFS_OPERATION_RETRY_SERVER	0x0800	/* Set अगर we should retry the current server */
#घोषणा AFS_OPERATION_सूची_CONFLICT	0x1000	/* Set अगर we detected a 3rd-party dir change */
पूर्ण;

/*
 * Cache auxiliary data.
 */
काष्ठा afs_vnode_cache_aux अणु
	u64			data_version;
पूर्ण __packed;

/*
 * We use page->निजी to hold the amount of the page that we've written to,
 * splitting the field पूर्णांकo two parts.  However, we need to represent a range
 * 0...PAGE_SIZE, so we reduce the resolution अगर the size of the page
 * exceeds what we can encode.
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा __AFS_PAGE_PRIV_MASK	0x7fffffffUL
#घोषणा __AFS_PAGE_PRIV_SHIFT	32
#घोषणा __AFS_PAGE_PRIV_MMAPPED	0x80000000UL
#अन्यथा
#घोषणा __AFS_PAGE_PRIV_MASK	0x7fffUL
#घोषणा __AFS_PAGE_PRIV_SHIFT	16
#घोषणा __AFS_PAGE_PRIV_MMAPPED	0x8000UL
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक afs_page_dirty_resolution(काष्ठा page *page)
अणु
	पूर्णांक shअगरt = thp_order(page) + PAGE_SHIFT - (__AFS_PAGE_PRIV_SHIFT - 1);
	वापस (shअगरt > 0) ? shअगरt : 0;
पूर्ण

अटल अंतरभूत माप_प्रकार afs_page_dirty_from(काष्ठा page *page, अचिन्हित दीर्घ priv)
अणु
	अचिन्हित दीर्घ x = priv & __AFS_PAGE_PRIV_MASK;

	/* The lower bound is inclusive */
	वापस x << afs_page_dirty_resolution(page);
पूर्ण

अटल अंतरभूत माप_प्रकार afs_page_dirty_to(काष्ठा page *page, अचिन्हित दीर्घ priv)
अणु
	अचिन्हित दीर्घ x = (priv >> __AFS_PAGE_PRIV_SHIFT) & __AFS_PAGE_PRIV_MASK;

	/* The upper bound is immediately beyond the region */
	वापस (x + 1) << afs_page_dirty_resolution(page);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ afs_page_dirty(काष्ठा page *page, माप_प्रकार from, माप_प्रकार to)
अणु
	अचिन्हित पूर्णांक res = afs_page_dirty_resolution(page);
	from >>= res;
	to = (to - 1) >> res;
	वापस (to << __AFS_PAGE_PRIV_SHIFT) | from;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ afs_page_dirty_mmapped(अचिन्हित दीर्घ priv)
अणु
	वापस priv | __AFS_PAGE_PRIV_MMAPPED;
पूर्ण

अटल अंतरभूत bool afs_is_page_dirty_mmapped(अचिन्हित दीर्घ priv)
अणु
	वापस priv & __AFS_PAGE_PRIV_MMAPPED;
पूर्ण

#समावेश <trace/events/afs.h>

/*****************************************************************************/
/*
 * addr_list.c
 */
अटल अंतरभूत काष्ठा afs_addr_list *afs_get_addrlist(काष्ठा afs_addr_list *alist)
अणु
	अगर (alist)
		refcount_inc(&alist->usage);
	वापस alist;
पूर्ण
बाह्य काष्ठा afs_addr_list *afs_alloc_addrlist(अचिन्हित पूर्णांक,
						अचिन्हित लघु,
						अचिन्हित लघु);
बाह्य व्योम afs_put_addrlist(काष्ठा afs_addr_list *);
बाह्य काष्ठा afs_vlserver_list *afs_parse_text_addrs(काष्ठा afs_net *,
						      स्थिर अक्षर *, माप_प्रकार, अक्षर,
						      अचिन्हित लघु, अचिन्हित लघु);
बाह्य काष्ठा afs_vlserver_list *afs_dns_query(काष्ठा afs_cell *, समय64_t *);
बाह्य bool afs_iterate_addresses(काष्ठा afs_addr_cursor *);
बाह्य पूर्णांक afs_end_cursor(काष्ठा afs_addr_cursor *);

बाह्य व्योम afs_merge_fs_addr4(काष्ठा afs_addr_list *, __be32, u16);
बाह्य व्योम afs_merge_fs_addr6(काष्ठा afs_addr_list *, __be32 *, u16);

/*
 * cache.c
 */
#अगर_घोषित CONFIG_AFS_FSCACHE
बाह्य काष्ठा fscache_netfs afs_cache_netfs;
बाह्य काष्ठा fscache_cookie_def afs_cell_cache_index_def;
बाह्य काष्ठा fscache_cookie_def afs_volume_cache_index_def;
बाह्य काष्ठा fscache_cookie_def afs_vnode_cache_index_def;
#अन्यथा
#घोषणा afs_cell_cache_index_def	(*(काष्ठा fscache_cookie_def *) शून्य)
#घोषणा afs_volume_cache_index_def	(*(काष्ठा fscache_cookie_def *) शून्य)
#घोषणा afs_vnode_cache_index_def	(*(काष्ठा fscache_cookie_def *) शून्य)
#पूर्ण_अगर

/*
 * callback.c
 */
बाह्य व्योम afs_init_callback_state(काष्ठा afs_server *);
बाह्य व्योम __afs_अवरोध_callback(काष्ठा afs_vnode *, क्रमागत afs_cb_अवरोध_reason);
बाह्य व्योम afs_अवरोध_callback(काष्ठा afs_vnode *, क्रमागत afs_cb_अवरोध_reason);
बाह्य व्योम afs_अवरोध_callbacks(काष्ठा afs_server *, माप_प्रकार, काष्ठा afs_callback_अवरोध *);

अटल अंतरभूत अचिन्हित पूर्णांक afs_calc_vnode_cb_अवरोध(काष्ठा afs_vnode *vnode)
अणु
	वापस vnode->cb_अवरोध + vnode->cb_v_अवरोध;
पूर्ण

अटल अंतरभूत bool afs_cb_is_broken(अचिन्हित पूर्णांक cb_अवरोध,
				    स्थिर काष्ठा afs_vnode *vnode)
अणु
	वापस cb_अवरोध != (vnode->cb_अवरोध + vnode->volume->cb_v_अवरोध);
पूर्ण

/*
 * cell.c
 */
बाह्य पूर्णांक afs_cell_init(काष्ठा afs_net *, स्थिर अक्षर *);
बाह्य काष्ठा afs_cell *afs_find_cell(काष्ठा afs_net *, स्थिर अक्षर *, अचिन्हित,
				      क्रमागत afs_cell_trace);
बाह्य काष्ठा afs_cell *afs_lookup_cell(काष्ठा afs_net *, स्थिर अक्षर *, अचिन्हित,
					स्थिर अक्षर *, bool);
बाह्य काष्ठा afs_cell *afs_use_cell(काष्ठा afs_cell *, क्रमागत afs_cell_trace);
बाह्य व्योम afs_unuse_cell(काष्ठा afs_net *, काष्ठा afs_cell *, क्रमागत afs_cell_trace);
बाह्य काष्ठा afs_cell *afs_get_cell(काष्ठा afs_cell *, क्रमागत afs_cell_trace);
बाह्य व्योम afs_see_cell(काष्ठा afs_cell *, क्रमागत afs_cell_trace);
बाह्य व्योम afs_put_cell(काष्ठा afs_cell *, क्रमागत afs_cell_trace);
बाह्य व्योम afs_queue_cell(काष्ठा afs_cell *, क्रमागत afs_cell_trace);
बाह्य व्योम afs_manage_cells(काष्ठा work_काष्ठा *);
बाह्य व्योम afs_cells_समयr(काष्ठा समयr_list *);
बाह्य व्योम __net_निकास afs_cell_purge(काष्ठा afs_net *);

/*
 * cmservice.c
 */
बाह्य bool afs_cm_incoming_call(काष्ठा afs_call *);

/*
 * dir.c
 */
बाह्य स्थिर काष्ठा file_operations afs_dir_file_operations;
बाह्य स्थिर काष्ठा inode_operations afs_dir_inode_operations;
बाह्य स्थिर काष्ठा address_space_operations afs_dir_aops;
बाह्य स्थिर काष्ठा dentry_operations afs_fs_dentry_operations;

बाह्य व्योम afs_d_release(काष्ठा dentry *);
बाह्य व्योम afs_check_क्रम_remote_deletion(काष्ठा afs_operation *);

/*
 * dir_edit.c
 */
बाह्य व्योम afs_edit_dir_add(काष्ठा afs_vnode *, काष्ठा qstr *, काष्ठा afs_fid *,
			     क्रमागत afs_edit_dir_reason);
बाह्य व्योम afs_edit_dir_हटाओ(काष्ठा afs_vnode *, काष्ठा qstr *, क्रमागत afs_edit_dir_reason);

/*
 * dir_silly.c
 */
बाह्य पूर्णांक afs_sillyनाम(काष्ठा afs_vnode *, काष्ठा afs_vnode *,
			   काष्ठा dentry *, काष्ठा key *);
बाह्य पूर्णांक afs_silly_iput(काष्ठा dentry *, काष्ठा inode *);

/*
 * dynroot.c
 */
बाह्य स्थिर काष्ठा inode_operations afs_dynroot_inode_operations;
बाह्य स्थिर काष्ठा dentry_operations afs_dynroot_dentry_operations;

बाह्य काष्ठा inode *afs_try_स्वतः_mntpt(काष्ठा dentry *, काष्ठा inode *);
बाह्य पूर्णांक afs_dynroot_सूची_गढ़ो(काष्ठा afs_net *, काष्ठा afs_cell *);
बाह्य व्योम afs_dynroot_सूची_हटाओ(काष्ठा afs_net *, काष्ठा afs_cell *);
बाह्य पूर्णांक afs_dynroot_populate(काष्ठा super_block *);
बाह्य व्योम afs_dynroot_depopulate(काष्ठा super_block *);

/*
 * file.c
 */
बाह्य स्थिर काष्ठा address_space_operations afs_fs_aops;
बाह्य स्थिर काष्ठा inode_operations afs_file_inode_operations;
बाह्य स्थिर काष्ठा file_operations afs_file_operations;
बाह्य स्थिर काष्ठा netfs_पढ़ो_request_ops afs_req_ops;

बाह्य पूर्णांक afs_cache_wb_key(काष्ठा afs_vnode *, काष्ठा afs_file *);
बाह्य व्योम afs_put_wb_key(काष्ठा afs_wb_key *);
बाह्य पूर्णांक afs_खोलो(काष्ठा inode *, काष्ठा file *);
बाह्य पूर्णांक afs_release(काष्ठा inode *, काष्ठा file *);
बाह्य पूर्णांक afs_fetch_data(काष्ठा afs_vnode *, काष्ठा afs_पढ़ो *);
बाह्य काष्ठा afs_पढ़ो *afs_alloc_पढ़ो(gfp_t);
बाह्य व्योम afs_put_पढ़ो(काष्ठा afs_पढ़ो *);

अटल अंतरभूत काष्ठा afs_पढ़ो *afs_get_पढ़ो(काष्ठा afs_पढ़ो *req)
अणु
	refcount_inc(&req->usage);
	वापस req;
पूर्ण

/*
 * flock.c
 */
बाह्य काष्ठा workqueue_काष्ठा *afs_lock_manager;

बाह्य व्योम afs_lock_op_करोne(काष्ठा afs_call *);
बाह्य व्योम afs_lock_work(काष्ठा work_काष्ठा *);
बाह्य व्योम afs_lock_may_be_available(काष्ठा afs_vnode *);
बाह्य पूर्णांक afs_lock(काष्ठा file *, पूर्णांक, काष्ठा file_lock *);
बाह्य पूर्णांक afs_flock(काष्ठा file *, पूर्णांक, काष्ठा file_lock *);

/*
 * fsclient.c
 */
बाह्य व्योम afs_fs_fetch_status(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_fetch_data(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_create_file(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_make_dir(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_हटाओ_file(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_हटाओ_dir(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_link(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_symlink(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_नाम(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_store_data(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_setattr(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_get_volume_status(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_set_lock(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_extend_lock(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_release_lock(काष्ठा afs_operation *);
बाह्य पूर्णांक afs_fs_give_up_all_callbacks(काष्ठा afs_net *, काष्ठा afs_server *,
					काष्ठा afs_addr_cursor *, काष्ठा key *);
बाह्य bool afs_fs_get_capabilities(काष्ठा afs_net *, काष्ठा afs_server *,
				    काष्ठा afs_addr_cursor *, काष्ठा key *);
बाह्य व्योम afs_fs_अंतरभूत_bulk_status(काष्ठा afs_operation *);

काष्ठा afs_acl अणु
	u32	size;
	u8	data[];
पूर्ण;

बाह्य व्योम afs_fs_fetch_acl(काष्ठा afs_operation *);
बाह्य व्योम afs_fs_store_acl(काष्ठा afs_operation *);

/*
 * fs_operation.c
 */
बाह्य काष्ठा afs_operation *afs_alloc_operation(काष्ठा key *, काष्ठा afs_volume *);
बाह्य पूर्णांक afs_put_operation(काष्ठा afs_operation *);
बाह्य bool afs_begin_vnode_operation(काष्ठा afs_operation *);
बाह्य व्योम afs_रुको_क्रम_operation(काष्ठा afs_operation *);
बाह्य पूर्णांक afs_करो_sync_operation(काष्ठा afs_operation *);

अटल अंतरभूत व्योम afs_op_nomem(काष्ठा afs_operation *op)
अणु
	op->error = -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम afs_op_set_vnode(काष्ठा afs_operation *op, अचिन्हित पूर्णांक n,
				    काष्ठा afs_vnode *vnode)
अणु
	op->file[n].vnode = vnode;
	op->file[n].need_io_lock = true;
पूर्ण

अटल अंतरभूत व्योम afs_op_set_fid(काष्ठा afs_operation *op, अचिन्हित पूर्णांक n,
				  स्थिर काष्ठा afs_fid *fid)
अणु
	op->file[n].fid = *fid;
पूर्ण

/*
 * fs_probe.c
 */
बाह्य व्योम afs_fileserver_probe_result(काष्ठा afs_call *);
बाह्य व्योम afs_fs_probe_fileserver(काष्ठा afs_net *, काष्ठा afs_server *, काष्ठा key *, bool);
बाह्य पूर्णांक afs_रुको_क्रम_fs_probes(काष्ठा afs_server_list *, अचिन्हित दीर्घ);
बाह्य व्योम afs_probe_fileserver(काष्ठा afs_net *, काष्ठा afs_server *);
बाह्य व्योम afs_fs_probe_dispatcher(काष्ठा work_काष्ठा *);
बाह्य पूर्णांक afs_रुको_क्रम_one_fs_probe(काष्ठा afs_server *, bool);
बाह्य व्योम afs_fs_probe_cleanup(काष्ठा afs_net *);

/*
 * inode.c
 */
बाह्य स्थिर काष्ठा afs_operation_ops afs_fetch_status_operation;

बाह्य व्योम afs_vnode_commit_status(काष्ठा afs_operation *, काष्ठा afs_vnode_param *);
बाह्य पूर्णांक afs_fetch_status(काष्ठा afs_vnode *, काष्ठा key *, bool, afs_access_t *);
बाह्य पूर्णांक afs_ilookup5_test_by_fid(काष्ठा inode *, व्योम *);
बाह्य काष्ठा inode *afs_iget_pseuकरो_dir(काष्ठा super_block *, bool);
बाह्य काष्ठा inode *afs_iget(काष्ठा afs_operation *, काष्ठा afs_vnode_param *);
बाह्य काष्ठा inode *afs_root_iget(काष्ठा super_block *, काष्ठा key *);
बाह्य bool afs_check_validity(काष्ठा afs_vnode *);
बाह्य पूर्णांक afs_validate(काष्ठा afs_vnode *, काष्ठा key *);
बाह्य पूर्णांक afs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *,
		       काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य पूर्णांक afs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *, काष्ठा iattr *);
बाह्य व्योम afs_evict_inode(काष्ठा inode *);
बाह्य पूर्णांक afs_drop_inode(काष्ठा inode *);

/*
 * मुख्य.c
 */
बाह्य काष्ठा workqueue_काष्ठा *afs_wq;
बाह्य पूर्णांक afs_net_id;

अटल अंतरभूत काष्ठा afs_net *afs_net(काष्ठा net *net)
अणु
	वापस net_generic(net, afs_net_id);
पूर्ण

अटल अंतरभूत काष्ठा afs_net *afs_sb2net(काष्ठा super_block *sb)
अणु
	वापस afs_net(AFS_FS_S(sb)->net_ns);
पूर्ण

अटल अंतरभूत काष्ठा afs_net *afs_d2net(काष्ठा dentry *dentry)
अणु
	वापस afs_sb2net(dentry->d_sb);
पूर्ण

अटल अंतरभूत काष्ठा afs_net *afs_i2net(काष्ठा inode *inode)
अणु
	वापस afs_sb2net(inode->i_sb);
पूर्ण

अटल अंतरभूत काष्ठा afs_net *afs_v2net(काष्ठा afs_vnode *vnode)
अणु
	वापस afs_i2net(&vnode->vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा afs_net *afs_sock2net(काष्ठा sock *sk)
अणु
	वापस net_generic(sock_net(sk), afs_net_id);
पूर्ण

अटल अंतरभूत व्योम __afs_stat(atomic_t *s)
अणु
	atomic_inc(s);
पूर्ण

#घोषणा afs_stat_v(vnode, n) __afs_stat(&afs_v2net(vnode)->n)

/*
 * misc.c
 */
बाह्य पूर्णांक afs_पात_to_error(u32);
बाह्य व्योम afs_prioritise_error(काष्ठा afs_error *, पूर्णांक, u32);

/*
 * mntpt.c
 */
बाह्य स्थिर काष्ठा inode_operations afs_mntpt_inode_operations;
बाह्य स्थिर काष्ठा inode_operations afs_स्वतःcell_inode_operations;
बाह्य स्थिर काष्ठा file_operations afs_mntpt_file_operations;

बाह्य काष्ठा vfsmount *afs_d_स्वतःmount(काष्ठा path *);
बाह्य व्योम afs_mntpt_समाप्त_समयr(व्योम);

/*
 * proc.c
 */
#अगर_घोषित CONFIG_PROC_FS
बाह्य पूर्णांक __net_init afs_proc_init(काष्ठा afs_net *);
बाह्य व्योम __net_निकास afs_proc_cleanup(काष्ठा afs_net *);
बाह्य पूर्णांक afs_proc_cell_setup(काष्ठा afs_cell *);
बाह्य व्योम afs_proc_cell_हटाओ(काष्ठा afs_cell *);
बाह्य व्योम afs_put_sysnames(काष्ठा afs_sysnames *);
#अन्यथा
अटल अंतरभूत पूर्णांक afs_proc_init(काष्ठा afs_net *net) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम afs_proc_cleanup(काष्ठा afs_net *net) अणुपूर्ण
अटल अंतरभूत पूर्णांक afs_proc_cell_setup(काष्ठा afs_cell *cell) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम afs_proc_cell_हटाओ(काष्ठा afs_cell *cell) अणुपूर्ण
अटल अंतरभूत व्योम afs_put_sysnames(काष्ठा afs_sysnames *sysnames) अणुपूर्ण
#पूर्ण_अगर

/*
 * rotate.c
 */
बाह्य bool afs_select_fileserver(काष्ठा afs_operation *);
बाह्य व्योम afs_dump_edestaddrreq(स्थिर काष्ठा afs_operation *);

/*
 * rxrpc.c
 */
बाह्य काष्ठा workqueue_काष्ठा *afs_async_calls;

बाह्य पूर्णांक __net_init afs_खोलो_socket(काष्ठा afs_net *);
बाह्य व्योम __net_निकास afs_बंद_socket(काष्ठा afs_net *);
बाह्य व्योम afs_अक्षरge_pपुनः_स्मृतिation(काष्ठा work_काष्ठा *);
बाह्य व्योम afs_put_call(काष्ठा afs_call *);
बाह्य व्योम afs_make_call(काष्ठा afs_addr_cursor *, काष्ठा afs_call *, gfp_t);
बाह्य दीर्घ afs_रुको_क्रम_call_to_complete(काष्ठा afs_call *, काष्ठा afs_addr_cursor *);
बाह्य काष्ठा afs_call *afs_alloc_flat_call(काष्ठा afs_net *,
					    स्थिर काष्ठा afs_call_type *,
					    माप_प्रकार, माप_प्रकार);
बाह्य व्योम afs_flat_call_deकाष्ठाor(काष्ठा afs_call *);
बाह्य व्योम afs_send_empty_reply(काष्ठा afs_call *);
बाह्य व्योम afs_send_simple_reply(काष्ठा afs_call *, स्थिर व्योम *, माप_प्रकार);
बाह्य पूर्णांक afs_extract_data(काष्ठा afs_call *, bool);
बाह्य पूर्णांक afs_protocol_error(काष्ठा afs_call *, क्रमागत afs_eproto_cause);

अटल अंतरभूत व्योम afs_make_op_call(काष्ठा afs_operation *op, काष्ठा afs_call *call,
				    gfp_t gfp)
अणु
	op->call = call;
	op->type = call->type;
	call->op = op;
	call->key = op->key;
	call->पूर्णांकr = !(op->flags & AFS_OPERATION_UNINTR);
	afs_make_call(&op->ac, call, gfp);
पूर्ण

अटल अंतरभूत व्योम afs_extract_begin(काष्ठा afs_call *call, व्योम *buf, माप_प्रकार size)
अणु
	call->iov_len = size;
	call->kvec[0].iov_base = buf;
	call->kvec[0].iov_len = size;
	iov_iter_kvec(&call->def_iter, READ, call->kvec, 1, size);
पूर्ण

अटल अंतरभूत व्योम afs_extract_to_पंचांगp(काष्ठा afs_call *call)
अणु
	call->iov_len = माप(call->पंचांगp);
	afs_extract_begin(call, &call->पंचांगp, माप(call->पंचांगp));
पूर्ण

अटल अंतरभूत व्योम afs_extract_to_पंचांगp64(काष्ठा afs_call *call)
अणु
	call->iov_len = माप(call->पंचांगp64);
	afs_extract_begin(call, &call->पंचांगp64, माप(call->पंचांगp64));
पूर्ण

अटल अंतरभूत व्योम afs_extract_discard(काष्ठा afs_call *call, माप_प्रकार size)
अणु
	call->iov_len = size;
	iov_iter_discard(&call->def_iter, READ, size);
पूर्ण

अटल अंतरभूत व्योम afs_extract_to_buf(काष्ठा afs_call *call, माप_प्रकार size)
अणु
	call->iov_len = size;
	afs_extract_begin(call, call->buffer, size);
पूर्ण

अटल अंतरभूत पूर्णांक afs_transfer_reply(काष्ठा afs_call *call)
अणु
	वापस afs_extract_data(call, false);
पूर्ण

अटल अंतरभूत bool afs_check_call_state(काष्ठा afs_call *call,
					क्रमागत afs_call_state state)
अणु
	वापस READ_ONCE(call->state) == state;
पूर्ण

अटल अंतरभूत bool afs_set_call_state(काष्ठा afs_call *call,
				      क्रमागत afs_call_state from,
				      क्रमागत afs_call_state to)
अणु
	bool ok = false;

	spin_lock_bh(&call->state_lock);
	अगर (call->state == from) अणु
		call->state = to;
		trace_afs_call_state(call, from, to, 0, 0);
		ok = true;
	पूर्ण
	spin_unlock_bh(&call->state_lock);
	वापस ok;
पूर्ण

अटल अंतरभूत व्योम afs_set_call_complete(काष्ठा afs_call *call,
					 पूर्णांक error, u32 remote_पात)
अणु
	क्रमागत afs_call_state state;
	bool ok = false;

	spin_lock_bh(&call->state_lock);
	state = call->state;
	अगर (state != AFS_CALL_COMPLETE) अणु
		call->पात_code = remote_पात;
		call->error = error;
		call->state = AFS_CALL_COMPLETE;
		trace_afs_call_state(call, state, AFS_CALL_COMPLETE,
				     error, remote_पात);
		ok = true;
	पूर्ण
	spin_unlock_bh(&call->state_lock);
	अगर (ok) अणु
		trace_afs_call_करोne(call);

		/* Asynchronous calls have two refs to release - one from the alloc and
		 * one queued with the work item - and we can't just deallocate the
		 * call because the work item may be queued again.
		 */
		अगर (call->drop_ref)
			afs_put_call(call);
	पूर्ण
पूर्ण

/*
 * security.c
 */
बाह्य व्योम afs_put_permits(काष्ठा afs_permits *);
बाह्य व्योम afs_clear_permits(काष्ठा afs_vnode *);
बाह्य व्योम afs_cache_permit(काष्ठा afs_vnode *, काष्ठा key *, अचिन्हित पूर्णांक,
			     काष्ठा afs_status_cb *);
बाह्य व्योम afs_zap_permits(काष्ठा rcu_head *);
बाह्य काष्ठा key *afs_request_key(काष्ठा afs_cell *);
बाह्य काष्ठा key *afs_request_key_rcu(काष्ठा afs_cell *);
बाह्य पूर्णांक afs_check_permit(काष्ठा afs_vnode *, काष्ठा key *, afs_access_t *);
बाह्य पूर्णांक afs_permission(काष्ठा user_namespace *, काष्ठा inode *, पूर्णांक);
बाह्य व्योम __निकास afs_clean_up_permit_cache(व्योम);

/*
 * server.c
 */
बाह्य spinlock_t afs_server_peer_lock;

बाह्य काष्ठा afs_server *afs_find_server(काष्ठा afs_net *,
					  स्थिर काष्ठा sockaddr_rxrpc *);
बाह्य काष्ठा afs_server *afs_find_server_by_uuid(काष्ठा afs_net *, स्थिर uuid_t *);
बाह्य काष्ठा afs_server *afs_lookup_server(काष्ठा afs_cell *, काष्ठा key *, स्थिर uuid_t *, u32);
बाह्य काष्ठा afs_server *afs_get_server(काष्ठा afs_server *, क्रमागत afs_server_trace);
बाह्य काष्ठा afs_server *afs_use_server(काष्ठा afs_server *, क्रमागत afs_server_trace);
बाह्य व्योम afs_unuse_server(काष्ठा afs_net *, काष्ठा afs_server *, क्रमागत afs_server_trace);
बाह्य व्योम afs_unuse_server_noसमय(काष्ठा afs_net *, काष्ठा afs_server *, क्रमागत afs_server_trace);
बाह्य व्योम afs_put_server(काष्ठा afs_net *, काष्ठा afs_server *, क्रमागत afs_server_trace);
बाह्य व्योम afs_manage_servers(काष्ठा work_काष्ठा *);
बाह्य व्योम afs_servers_समयr(काष्ठा समयr_list *);
बाह्य व्योम afs_fs_probe_समयr(काष्ठा समयr_list *);
बाह्य व्योम __net_निकास afs_purge_servers(काष्ठा afs_net *);
बाह्य bool afs_check_server_record(काष्ठा afs_operation *, काष्ठा afs_server *);

अटल अंतरभूत व्योम afs_inc_servers_outstanding(काष्ठा afs_net *net)
अणु
	atomic_inc(&net->servers_outstanding);
पूर्ण

अटल अंतरभूत व्योम afs_dec_servers_outstanding(काष्ठा afs_net *net)
अणु
	अगर (atomic_dec_and_test(&net->servers_outstanding))
		wake_up_var(&net->servers_outstanding);
पूर्ण

अटल अंतरभूत bool afs_is_probing_server(काष्ठा afs_server *server)
अणु
	वापस list_empty(&server->probe_link);
पूर्ण

/*
 * server_list.c
 */
अटल अंतरभूत काष्ठा afs_server_list *afs_get_serverlist(काष्ठा afs_server_list *slist)
अणु
	refcount_inc(&slist->usage);
	वापस slist;
पूर्ण

बाह्य व्योम afs_put_serverlist(काष्ठा afs_net *, काष्ठा afs_server_list *);
बाह्य काष्ठा afs_server_list *afs_alloc_server_list(काष्ठा afs_cell *, काष्ठा key *,
						     काष्ठा afs_vldb_entry *,
						     u8);
बाह्य bool afs_annotate_server_list(काष्ठा afs_server_list *, काष्ठा afs_server_list *);

/*
 * super.c
 */
बाह्य पूर्णांक __init afs_fs_init(व्योम);
बाह्य व्योम afs_fs_निकास(व्योम);

/*
 * vlclient.c
 */
बाह्य काष्ठा afs_vldb_entry *afs_vl_get_entry_by_name_u(काष्ठा afs_vl_cursor *,
							 स्थिर अक्षर *, पूर्णांक);
बाह्य काष्ठा afs_addr_list *afs_vl_get_addrs_u(काष्ठा afs_vl_cursor *, स्थिर uuid_t *);
बाह्य काष्ठा afs_call *afs_vl_get_capabilities(काष्ठा afs_net *, काष्ठा afs_addr_cursor *,
						काष्ठा key *, काष्ठा afs_vlserver *, अचिन्हित पूर्णांक);
बाह्य काष्ठा afs_addr_list *afs_yfsvl_get_endpoपूर्णांकs(काष्ठा afs_vl_cursor *, स्थिर uuid_t *);
बाह्य अक्षर *afs_yfsvl_get_cell_name(काष्ठा afs_vl_cursor *);

/*
 * vl_alias.c
 */
बाह्य पूर्णांक afs_cell_detect_alias(काष्ठा afs_cell *, काष्ठा key *);

/*
 * vl_probe.c
 */
बाह्य व्योम afs_vlserver_probe_result(काष्ठा afs_call *);
बाह्य पूर्णांक afs_send_vl_probes(काष्ठा afs_net *, काष्ठा key *, काष्ठा afs_vlserver_list *);
बाह्य पूर्णांक afs_रुको_क्रम_vl_probes(काष्ठा afs_vlserver_list *, अचिन्हित दीर्घ);

/*
 * vl_rotate.c
 */
बाह्य bool afs_begin_vlserver_operation(काष्ठा afs_vl_cursor *,
					 काष्ठा afs_cell *, काष्ठा key *);
बाह्य bool afs_select_vlserver(काष्ठा afs_vl_cursor *);
बाह्य bool afs_select_current_vlserver(काष्ठा afs_vl_cursor *);
बाह्य पूर्णांक afs_end_vlserver_operation(काष्ठा afs_vl_cursor *);

/*
 * vlserver_list.c
 */
अटल अंतरभूत काष्ठा afs_vlserver *afs_get_vlserver(काष्ठा afs_vlserver *vlserver)
अणु
	atomic_inc(&vlserver->usage);
	वापस vlserver;
पूर्ण

अटल अंतरभूत काष्ठा afs_vlserver_list *afs_get_vlserverlist(काष्ठा afs_vlserver_list *vllist)
अणु
	अगर (vllist)
		atomic_inc(&vllist->usage);
	वापस vllist;
पूर्ण

बाह्य काष्ठा afs_vlserver *afs_alloc_vlserver(स्थिर अक्षर *, माप_प्रकार, अचिन्हित लघु);
बाह्य व्योम afs_put_vlserver(काष्ठा afs_net *, काष्ठा afs_vlserver *);
बाह्य काष्ठा afs_vlserver_list *afs_alloc_vlserver_list(अचिन्हित पूर्णांक);
बाह्य व्योम afs_put_vlserverlist(काष्ठा afs_net *, काष्ठा afs_vlserver_list *);
बाह्य काष्ठा afs_vlserver_list *afs_extract_vlserver_list(काष्ठा afs_cell *,
							   स्थिर व्योम *, माप_प्रकार);

/*
 * volume.c
 */
बाह्य काष्ठा afs_volume *afs_create_volume(काष्ठा afs_fs_context *);
बाह्य व्योम afs_activate_volume(काष्ठा afs_volume *);
बाह्य व्योम afs_deactivate_volume(काष्ठा afs_volume *);
बाह्य काष्ठा afs_volume *afs_get_volume(काष्ठा afs_volume *, क्रमागत afs_volume_trace);
बाह्य व्योम afs_put_volume(काष्ठा afs_net *, काष्ठा afs_volume *, क्रमागत afs_volume_trace);
बाह्य पूर्णांक afs_check_volume_status(काष्ठा afs_volume *, काष्ठा afs_operation *);

/*
 * ग_लिखो.c
 */
बाह्य पूर्णांक afs_set_page_dirty(काष्ठा page *);
बाह्य पूर्णांक afs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata);
बाह्य पूर्णांक afs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata);
बाह्य पूर्णांक afs_ग_लिखोpage(काष्ठा page *, काष्ठा ग_लिखोback_control *);
बाह्य पूर्णांक afs_ग_लिखोpages(काष्ठा address_space *, काष्ठा ग_लिखोback_control *);
बाह्य sमाप_प्रकार afs_file_ग_लिखो(काष्ठा kiocb *, काष्ठा iov_iter *);
बाह्य पूर्णांक afs_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);
बाह्य vm_fault_t afs_page_mkग_लिखो(काष्ठा vm_fault *vmf);
बाह्य व्योम afs_prune_wb_keys(काष्ठा afs_vnode *);
बाह्य पूर्णांक afs_launder_page(काष्ठा page *);

/*
 * xattr.c
 */
बाह्य स्थिर काष्ठा xattr_handler *afs_xattr_handlers[];

/*
 * yfsclient.c
 */
बाह्य व्योम yfs_fs_fetch_data(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_create_file(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_make_dir(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_हटाओ_file2(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_हटाओ_file(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_हटाओ_dir(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_link(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_symlink(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_नाम(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_store_data(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_setattr(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_get_volume_status(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_set_lock(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_extend_lock(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_release_lock(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_fetch_status(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_अंतरभूत_bulk_status(काष्ठा afs_operation *);

काष्ठा yfs_acl अणु
	काष्ठा afs_acl	*acl;		/* Dir/file/symlink ACL */
	काष्ठा afs_acl	*vol_acl;	/* Whole volume ACL */
	u32		inherit_flag;	/* True अगर ACL is inherited from parent dir */
	u32		num_cleaned;	/* Number of ACEs हटाओd due to subject removal */
	अचिन्हित पूर्णांक	flags;
#घोषणा YFS_ACL_WANT_ACL	0x01	/* Set अगर caller wants ->acl */
#घोषणा YFS_ACL_WANT_VOL_ACL	0x02	/* Set अगर caller wants ->vol_acl */
पूर्ण;

बाह्य व्योम yfs_मुक्त_opaque_acl(काष्ठा yfs_acl *);
बाह्य व्योम yfs_fs_fetch_opaque_acl(काष्ठा afs_operation *);
बाह्य व्योम yfs_fs_store_opaque_acl2(काष्ठा afs_operation *);

/*
 * Miscellaneous अंतरभूत functions.
 */
अटल अंतरभूत काष्ठा afs_vnode *AFS_FS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा afs_vnode, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा inode *AFS_VNODE_TO_I(काष्ठा afs_vnode *vnode)
अणु
	वापस &vnode->vfs_inode;
पूर्ण

/*
 * Note that a dentry got changed.  We need to set d_fsdata to the data version
 * number derived from the result of the operation.  It करोesn't matter अगर
 * d_fsdata goes backwards as we'll just revalidate.
 */
अटल अंतरभूत व्योम afs_update_dentry_version(काष्ठा afs_operation *op,
					     काष्ठा afs_vnode_param *dir_vp,
					     काष्ठा dentry *dentry)
अणु
	अगर (!op->error)
		dentry->d_fsdata =
			(व्योम *)(अचिन्हित दीर्घ)dir_vp->scb.status.data_version;
पूर्ण

/*
 * Check क्रम a conflicting operation on a directory that we just unlinked from.
 * If someone managed to sneak a link or an unlink in on the file we just
 * unlinked, we won't be able to trust nlink on an AFS file (but not YFS).
 */
अटल अंतरभूत व्योम afs_check_dir_conflict(काष्ठा afs_operation *op,
					  काष्ठा afs_vnode_param *dvp)
अणु
	अगर (dvp->dv_beक्रमe + dvp->dv_delta != dvp->scb.status.data_version)
		op->flags |= AFS_OPERATION_सूची_CONFLICT;
पूर्ण

अटल अंतरभूत पूर्णांक afs_io_error(काष्ठा afs_call *call, क्रमागत afs_io_error where)
अणु
	trace_afs_io_error(call->debug_id, -EIO, where);
	वापस -EIO;
पूर्ण

अटल अंतरभूत पूर्णांक afs_bad(काष्ठा afs_vnode *vnode, क्रमागत afs_file_error where)
अणु
	trace_afs_file_error(vnode, -EIO, where);
	वापस -EIO;
पूर्ण

/*****************************************************************************/
/*
 * debug tracing
 */
बाह्य अचिन्हित afs_debug;

#घोषणा dbgprपूर्णांकk(FMT,...) \
	prपूर्णांकk("[%-6.6s] "FMT"\n", current->comm ,##__VA_ARGS__)

#घोषणा kenter(FMT,...)	dbgprपूर्णांकk("==> %s("FMT")",__func__ ,##__VA_ARGS__)
#घोषणा kleave(FMT,...)	dbgprपूर्णांकk("<== %s()"FMT"",__func__ ,##__VA_ARGS__)
#घोषणा kdebug(FMT,...)	dbgprपूर्णांकk("    "FMT ,##__VA_ARGS__)


#अगर defined(__KDEBUG)
#घोषणा _enter(FMT,...)	kenter(FMT,##__VA_ARGS__)
#घोषणा _leave(FMT,...)	kleave(FMT,##__VA_ARGS__)
#घोषणा _debug(FMT,...)	kdebug(FMT,##__VA_ARGS__)

#या_अगर defined(CONFIG_AFS_DEBUG)
#घोषणा AFS_DEBUG_KENTER	0x01
#घोषणा AFS_DEBUG_KLEAVE	0x02
#घोषणा AFS_DEBUG_KDEBUG	0x04

#घोषणा _enter(FMT,...)					\
करो अणु							\
	अगर (unlikely(afs_debug & AFS_DEBUG_KENTER))	\
		kenter(FMT,##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा _leave(FMT,...)					\
करो अणु							\
	अगर (unlikely(afs_debug & AFS_DEBUG_KLEAVE))	\
		kleave(FMT,##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा _debug(FMT,...)					\
करो अणु							\
	अगर (unlikely(afs_debug & AFS_DEBUG_KDEBUG))	\
		kdebug(FMT,##__VA_ARGS__);		\
पूर्ण जबतक (0)

#अन्यथा
#घोषणा _enter(FMT,...)	no_prपूर्णांकk("==> %s("FMT")",__func__ ,##__VA_ARGS__)
#घोषणा _leave(FMT,...)	no_prपूर्णांकk("<== %s()"FMT"",__func__ ,##__VA_ARGS__)
#घोषणा _debug(FMT,...)	no_prपूर्णांकk("    "FMT ,##__VA_ARGS__)
#पूर्ण_अगर

/*
 * debug निश्चितion checking
 */
#अगर 1 // defined(__KDEBUGALL)

#घोषणा ASSERT(X)						\
करो अणु								\
	अगर (unlikely(!(X))) अणु					\
		prपूर्णांकk(KERN_ERR "\n");				\
		prपूर्णांकk(KERN_ERR "AFS: Assertion failed\n");	\
		BUG();						\
	पूर्ण							\
पूर्ण जबतक(0)

#घोषणा ASSERTCMP(X, OP, Y)						\
करो अणु									\
	अगर (unlikely(!((X) OP (Y)))) अणु					\
		prपूर्णांकk(KERN_ERR "\n");					\
		prपूर्णांकk(KERN_ERR "AFS: Assertion failed\n");		\
		prपूर्णांकk(KERN_ERR "%lu " #OP " %lu is false\n",		\
		       (अचिन्हित दीर्घ)(X), (अचिन्हित दीर्घ)(Y));		\
		prपूर्णांकk(KERN_ERR "0x%lx " #OP " 0x%lx is false\n",	\
		       (अचिन्हित दीर्घ)(X), (अचिन्हित दीर्घ)(Y));		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक(0)

#घोषणा ASSERTRANGE(L, OP1, N, OP2, H)					\
करो अणु									\
	अगर (unlikely(!((L) OP1 (N)) || !((N) OP2 (H)))) अणु		\
		prपूर्णांकk(KERN_ERR "\n");					\
		prपूर्णांकk(KERN_ERR "AFS: Assertion failed\n");		\
		prपूर्णांकk(KERN_ERR "%lu "#OP1" %lu "#OP2" %lu is false\n",	\
		       (अचिन्हित दीर्घ)(L), (अचिन्हित दीर्घ)(N),		\
		       (अचिन्हित दीर्घ)(H));				\
		prपूर्णांकk(KERN_ERR "0x%lx "#OP1" 0x%lx "#OP2" 0x%lx is false\n", \
		       (अचिन्हित दीर्घ)(L), (अचिन्हित दीर्घ)(N),		\
		       (अचिन्हित दीर्घ)(H));				\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक(0)

#घोषणा ASSERTIF(C, X)						\
करो अणु								\
	अगर (unlikely((C) && !(X))) अणु				\
		prपूर्णांकk(KERN_ERR "\n");				\
		prपूर्णांकk(KERN_ERR "AFS: Assertion failed\n");	\
		BUG();						\
	पूर्ण							\
पूर्ण जबतक(0)

#घोषणा ASSERTIFCMP(C, X, OP, Y)					\
करो अणु									\
	अगर (unlikely((C) && !((X) OP (Y)))) अणु				\
		prपूर्णांकk(KERN_ERR "\n");					\
		prपूर्णांकk(KERN_ERR "AFS: Assertion failed\n");		\
		prपूर्णांकk(KERN_ERR "%lu " #OP " %lu is false\n",		\
		       (अचिन्हित दीर्घ)(X), (अचिन्हित दीर्घ)(Y));		\
		prपूर्णांकk(KERN_ERR "0x%lx " #OP " 0x%lx is false\n",	\
		       (अचिन्हित दीर्घ)(X), (अचिन्हित दीर्घ)(Y));		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक(0)

#अन्यथा

#घोषणा ASSERT(X)				\
करो अणु						\
पूर्ण जबतक(0)

#घोषणा ASSERTCMP(X, OP, Y)			\
करो अणु						\
पूर्ण जबतक(0)

#घोषणा ASSERTRANGE(L, OP1, N, OP2, H)		\
करो अणु						\
पूर्ण जबतक(0)

#घोषणा ASSERTIF(C, X)				\
करो अणु						\
पूर्ण जबतक(0)

#घोषणा ASSERTIFCMP(C, X, OP, Y)		\
करो अणु						\
पूर्ण जबतक(0)

#पूर्ण_अगर /* __KDEBUGALL */
