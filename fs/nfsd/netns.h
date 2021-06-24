<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * per net namespace data काष्ठाures क्रम nfsd
 *
 * Copyright (C) 2012, Jeff Layton <jlayton@redhat.com>
 */

#अगर_अघोषित __NFSD_NETNS_H__
#घोषणा __NFSD_NETNS_H__

#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/percpu_counter.h>

/* Hash tables क्रम nfs4_clientid state */
#घोषणा CLIENT_HASH_BITS                 4
#घोषणा CLIENT_HASH_SIZE                (1 << CLIENT_HASH_BITS)
#घोषणा CLIENT_HASH_MASK                (CLIENT_HASH_SIZE - 1)

#घोषणा SESSION_HASH_SIZE	512

काष्ठा cld_net;
काष्ठा nfsd4_client_tracking_ops;

क्रमागत अणु
	/* cache misses due only to checksum comparison failures */
	NFSD_NET_PAYLOAD_MISSES,
	/* amount of memory (in bytes) currently consumed by the DRC */
	NFSD_NET_DRC_MEM_USAGE,
	NFSD_NET_COUNTERS_NUM
पूर्ण;

/*
 * Represents a nfsd "container". With respect to nfsv4 state tracking, the
 * fields of पूर्णांकerest are the *_id_hashtbls and the *_name_tree. These track
 * the nfs4_client objects by either लघु or दीर्घ क्रमm clientid.
 *
 * Each nfsd_net runs a nfs4_laundromat workqueue job when necessary to clean
 * up expired clients and delegations within the container.
 */
काष्ठा nfsd_net अणु
	काष्ठा cld_net *cld_net;

	काष्ठा cache_detail *svc_expkey_cache;
	काष्ठा cache_detail *svc_export_cache;

	काष्ठा cache_detail *idtoname_cache;
	काष्ठा cache_detail *nametoid_cache;

	काष्ठा lock_manager nfsd4_manager;
	bool grace_ended;
	समय64_t boot_समय;

	काष्ठा dentry *nfsd_client_dir;

	/*
	 * reclaim_str_hashtbl[] holds known client info from previous reset/reboot
	 * used in reboot/reset lease grace period processing
	 *
	 * conf_id_hashtbl[], and conf_name_tree hold confirmed
	 * setclientid_confirmed info.
	 *
	 * unconf_str_hastbl[] and unconf_name_tree hold unconfirmed
	 * setclientid info.
	 */
	काष्ठा list_head *reclaim_str_hashtbl;
	पूर्णांक reclaim_str_hashtbl_size;
	काष्ठा list_head *conf_id_hashtbl;
	काष्ठा rb_root conf_name_tree;
	काष्ठा list_head *unconf_id_hashtbl;
	काष्ठा rb_root unconf_name_tree;
	काष्ठा list_head *sessionid_hashtbl;
	/*
	 * client_lru holds client queue ordered by nfs4_client.cl_समय
	 * क्रम lease renewal.
	 *
	 * बंद_lru holds (खोलो) stateowner queue ordered by nfs4_stateowner.so_समय
	 * क्रम last बंद replay.
	 *
	 * All of the above fields are रक्षित by the client_mutex.
	 */
	काष्ठा list_head client_lru;
	काष्ठा list_head बंद_lru;
	काष्ठा list_head del_recall_lru;

	/* रक्षित by blocked_locks_lock */
	काष्ठा list_head blocked_locks_lru;

	काष्ठा delayed_work laundromat_work;

	/* client_lock protects the client lru list and session hash table */
	spinlock_t client_lock;

	/* protects blocked_locks_lru */
	spinlock_t blocked_locks_lock;

	काष्ठा file *rec_file;
	bool in_grace;
	स्थिर काष्ठा nfsd4_client_tracking_ops *client_tracking_ops;

	समय64_t nfsd4_lease;
	समय64_t nfsd4_grace;
	bool somebody_reclaimed;

	bool track_reclaim_completes;
	atomic_t nr_reclaim_complete;

	bool nfsd_net_up;
	bool lockd_up;

	/* Time of server startup */
	काष्ठा बारpec64 nfssvc_boot;
	seqlock_t boot_lock;

	/*
	 * Max number of connections this nfsd container will allow. Defaults
	 * to '0' which is means that it bases this on the number of thपढ़ोs.
	 */
	अचिन्हित पूर्णांक max_connections;

	u32 clientid_base;
	u32 clientid_counter;
	u32 clverअगरier_counter;

	काष्ठा svc_serv *nfsd_serv;

	रुको_queue_head_t ntf_wq;
	atomic_t ntf_refcnt;

	/* Allow umount to रुको क्रम nfsd state cleanup */
	काष्ठा completion nfsd_shutकरोwn_complete;

	/*
	 * clientid and stateid data क्रम स्थिरruction of net unique COPY
	 * stateids.
	 */
	u32		s2s_cp_cl_id;
	काष्ठा idr	s2s_cp_stateids;
	spinlock_t	s2s_cp_lock;

	/*
	 * Version inक्रमmation
	 */
	bool *nfsd_versions;
	bool *nfsd4_minorversions;

	/*
	 * Duplicate reply cache
	 */
	काष्ठा nfsd_drc_bucket   *drc_hashtbl;

	/* max number of entries allowed in the cache */
	अचिन्हित पूर्णांक             max_drc_entries;

	/* number of signअगरicant bits in the hash value */
	अचिन्हित पूर्णांक             maskbits;
	अचिन्हित पूर्णांक             drc_hashsize;

	/*
	 * Stats and other tracking of on the duplicate reply cache.
	 * The दीर्घest_chain* fields are modअगरied with only the per-bucket
	 * cache lock, which isn't really safe and should be fixed अगर we want
	 * these statistics to be completely accurate.
	 */

	/* total number of entries */
	atomic_t                 num_drc_entries;

	/* Per-netns stats counters */
	काष्ठा percpu_counter    counter[NFSD_NET_COUNTERS_NUM];

	/* दीर्घest hash chain seen */
	अचिन्हित पूर्णांक             दीर्घest_chain;

	/* size of cache when we saw the दीर्घest hash chain */
	अचिन्हित पूर्णांक             दीर्घest_chain_cachesize;

	काष्ठा shrinker		nfsd_reply_cache_shrinker;
	/* utsname taken from the process that starts the server */
	अक्षर			nfsd_name[UNX_MAXNODENAME+1];
पूर्ण;

/* Simple check to find out अगर a given net was properly initialized */
#घोषणा nfsd_netns_पढ़ोy(nn) ((nn)->sessionid_hashtbl)

बाह्य व्योम nfsd_netns_मुक्त_versions(काष्ठा nfsd_net *nn);

बाह्य अचिन्हित पूर्णांक nfsd_net_id;

व्योम nfsd_copy_boot_verअगरier(__be32 verf[2], काष्ठा nfsd_net *nn);
व्योम nfsd_reset_boot_verअगरier(काष्ठा nfsd_net *nn);
#पूर्ण_अगर /* __NFSD_NETNS_H__ */
