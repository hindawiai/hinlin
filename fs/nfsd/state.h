<शैली गुरु>
/*
 *  Copyright (c) 2001 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
 *  Andy Adamson <andros@umich.edu>
 *  
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *  
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the University nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#अगर_अघोषित _NFSD4_STATE_H
#घोषणा _NFSD4_STATE_H

#समावेश <linux/idr.h>
#समावेश <linux/refcount.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश "nfsfh.h"
#समावेश "nfsd.h"

प्रकार काष्ठा अणु
	u32             cl_boot;
	u32             cl_id;
पूर्ण clientid_t;

प्रकार काष्ठा अणु
	clientid_t	so_clid;
	u32		so_id;
पूर्ण stateid_opaque_t;

प्रकार काष्ठा अणु
	u32                     si_generation;
	stateid_opaque_t        si_opaque;
पूर्ण stateid_t;

प्रकार काष्ठा अणु
	stateid_t		stid;
#घोषणा NFS4_COPY_STID 1
#घोषणा NFS4_COPYNOTIFY_STID 2
	अचिन्हित अक्षर		sc_type;
	refcount_t		sc_count;
पूर्ण copy_stateid_t;

काष्ठा nfsd4_callback अणु
	काष्ठा nfs4_client *cb_clp;
	काष्ठा rpc_message cb_msg;
	स्थिर काष्ठा nfsd4_callback_ops *cb_ops;
	काष्ठा work_काष्ठा cb_work;
	पूर्णांक cb_seq_status;
	पूर्णांक cb_status;
	bool cb_need_restart;
	bool cb_holds_slot;
पूर्ण;

काष्ठा nfsd4_callback_ops अणु
	व्योम (*prepare)(काष्ठा nfsd4_callback *);
	पूर्णांक (*करोne)(काष्ठा nfsd4_callback *, काष्ठा rpc_task *);
	व्योम (*release)(काष्ठा nfsd4_callback *);
पूर्ण;

/*
 * A core object that represents a "common" stateid. These are generally
 * embedded within the dअगरferent (more specअगरic) stateid objects and contain
 * fields that are of general use to any stateid.
 */
काष्ठा nfs4_stid अणु
	refcount_t		sc_count;
#घोषणा NFS4_OPEN_STID 1
#घोषणा NFS4_LOCK_STID 2
#घोषणा NFS4_DELEG_STID 4
/* For an खोलो stateid kept around *only* to process बंद replays: */
#घोषणा NFS4_CLOSED_STID 8
/* For a deleg stateid kept around only to process मुक्त_stateid's: */
#घोषणा NFS4_REVOKED_DELEG_STID 16
#घोषणा NFS4_CLOSED_DELEG_STID 32
#घोषणा NFS4_LAYOUT_STID 64
	काष्ठा list_head	sc_cp_list;
	अचिन्हित अक्षर		sc_type;
	stateid_t		sc_stateid;
	spinlock_t		sc_lock;
	काष्ठा nfs4_client	*sc_client;
	काष्ठा nfs4_file	*sc_file;
	व्योम			(*sc_मुक्त)(काष्ठा nfs4_stid *);
पूर्ण;

/* Keep a list of stateids issued by the COPY_NOTIFY, associate it with the
 * parent OPEN/LOCK/DELEG stateid.
 */
काष्ठा nfs4_cpntf_state अणु
	copy_stateid_t		cp_stateid;
	काष्ठा list_head	cp_list;	/* per parent nfs4_stid */
	stateid_t		cp_p_stateid;	/* copy of parent's stateid */
	clientid_t		cp_p_clid;	/* copy of parent's clid */
	समय64_t		cpntf_समय;	/* last समय stateid used */
पूर्ण;

/*
 * Represents a delegation stateid. The nfs4_client holds references to these
 * and they are put when it is being destroyed or when the delegation is
 * वापसed by the client:
 *
 * o 1 reference as दीर्घ as a delegation is still in क्रमce (taken when it's
 *   alloc'd, put when it's वापसed or revoked)
 *
 * o 1 reference as दीर्घ as a recall rpc is in progress (taken when the lease
 *   is broken, put when the rpc निकासs)
 *
 * o 1 more ephemeral reference क्रम each nfsd thपढ़ो currently करोing something
 *   with that delegation without holding the cl_lock
 *
 * If the server attempts to recall a delegation and the client करोesn't करो so
 * beक्रमe a समयout, the server may also revoke the delegation. In that हाल,
 * the object will either be destroyed (v4.0) or moved to a per-client list of
 * revoked delegations (v4.1+).
 *
 * This object is a superset of the nfs4_stid.
 */
काष्ठा nfs4_delegation अणु
	काष्ठा nfs4_stid	dl_stid; /* must be first field */
	काष्ठा list_head	dl_perfile;
	काष्ठा list_head	dl_perclnt;
	काष्ठा list_head	dl_recall_lru;  /* delegation recalled */
	काष्ठा nfs4_clnt_odstate *dl_clnt_odstate;
	u32			dl_type;
	समय64_t		dl_समय;
/* For recall: */
	पूर्णांक			dl_retries;
	काष्ठा nfsd4_callback	dl_recall;
पूर्ण;

#घोषणा cb_to_delegation(cb) \
	container_of(cb, काष्ठा nfs4_delegation, dl_recall)

/* client delegation callback info */
काष्ठा nfs4_cb_conn अणु
	/* SETCLIENTID info */
	काष्ठा sockaddr_storage	cb_addr;
	काष्ठा sockaddr_storage	cb_saddr;
	माप_प्रकार			cb_addrlen;
	u32                     cb_prog; /* used only in 4.0 हाल;
					    per-session otherwise */
	u32                     cb_ident;	/* minorversion 0 only */
	काष्ठा svc_xprt		*cb_xprt;	/* minorversion 1 only */
पूर्ण;

अटल अंतरभूत काष्ठा nfs4_delegation *delegstateid(काष्ठा nfs4_stid *s)
अणु
	वापस container_of(s, काष्ठा nfs4_delegation, dl_stid);
पूर्ण

/* Maximum number of slots per session. 160 is useful क्रम दीर्घ haul TCP */
#घोषणा NFSD_MAX_SLOTS_PER_SESSION     160
/* Maximum number of operations per session compound */
#घोषणा NFSD_MAX_OPS_PER_COMPOUND	16
/* Maximum  session per slot cache size */
#घोषणा NFSD_SLOT_CACHE_SIZE		2048
/* Maximum number of NFSD_SLOT_CACHE_SIZE slots per session */
#घोषणा NFSD_CACHE_SIZE_SLOTS_PER_SESSION	32
#घोषणा NFSD_MAX_MEM_PER_SESSION  \
		(NFSD_CACHE_SIZE_SLOTS_PER_SESSION * NFSD_SLOT_CACHE_SIZE)

काष्ठा nfsd4_slot अणु
	u32	sl_seqid;
	__be32	sl_status;
	काष्ठा svc_cred sl_cred;
	u32	sl_datalen;
	u16	sl_opcnt;
#घोषणा NFSD4_SLOT_INUSE	(1 << 0)
#घोषणा NFSD4_SLOT_CACHETHIS	(1 << 1)
#घोषणा NFSD4_SLOT_INITIALIZED	(1 << 2)
#घोषणा NFSD4_SLOT_CACHED	(1 << 3)
	u8	sl_flags;
	अक्षर	sl_data[];
पूर्ण;

काष्ठा nfsd4_channel_attrs अणु
	u32		headerpadsz;
	u32		maxreq_sz;
	u32		maxresp_sz;
	u32		maxresp_cached;
	u32		maxops;
	u32		maxreqs;
	u32		nr_rdma_attrs;
	u32		rdma_attrs;
पूर्ण;

काष्ठा nfsd4_cb_sec अणु
	u32	flavor; /* (u32)(-1) used to mean "no valid flavor" */
	kuid_t	uid;
	kgid_t	gid;
पूर्ण;

काष्ठा nfsd4_create_session अणु
	clientid_t			clientid;
	काष्ठा nfs4_sessionid		sessionid;
	u32				seqid;
	u32				flags;
	काष्ठा nfsd4_channel_attrs	क्रमe_channel;
	काष्ठा nfsd4_channel_attrs	back_channel;
	u32				callback_prog;
	काष्ठा nfsd4_cb_sec		cb_sec;
पूर्ण;

काष्ठा nfsd4_backchannel_ctl अणु
	u32	bc_cb_program;
	काष्ठा nfsd4_cb_sec		bc_cb_sec;
पूर्ण;

काष्ठा nfsd4_bind_conn_to_session अणु
	काष्ठा nfs4_sessionid		sessionid;
	u32				dir;
पूर्ण;

/* The single slot clientid cache काष्ठाure */
काष्ठा nfsd4_clid_slot अणु
	u32				sl_seqid;
	__be32				sl_status;
	काष्ठा nfsd4_create_session	sl_cr_ses;
पूर्ण;

काष्ठा nfsd4_conn अणु
	काष्ठा list_head cn_persession;
	काष्ठा svc_xprt *cn_xprt;
	काष्ठा svc_xpt_user cn_xpt_user;
	काष्ठा nfsd4_session *cn_session;
/* CDFC4_FORE, CDFC4_BACK: */
	अचिन्हित अक्षर cn_flags;
पूर्ण;

/*
 * Representation of a v4.1+ session. These are refcounted in a similar fashion
 * to the nfs4_client. References are only taken when the server is actively
 * working on the object (primarily during the processing of compounds).
 */
काष्ठा nfsd4_session अणु
	atomic_t		se_ref;
	काष्ठा list_head	se_hash;	/* hash by sessionid */
	काष्ठा list_head	se_perclnt;
/* See SESSION4_PERSIST, etc. क्रम standard flags; this is पूर्णांकernal-only: */
#घोषणा NFS4_SESSION_DEAD	0x010
	u32			se_flags;
	काष्ठा nfs4_client	*se_client;
	काष्ठा nfs4_sessionid	se_sessionid;
	काष्ठा nfsd4_channel_attrs se_fchannel;
	काष्ठा nfsd4_channel_attrs se_bchannel;
	काष्ठा nfsd4_cb_sec	se_cb_sec;
	काष्ठा list_head	se_conns;
	u32			se_cb_prog;
	u32			se_cb_seq_nr;
	काष्ठा nfsd4_slot	*se_slots[];	/* क्रमward channel slots */
पूर्ण;

/* क्रमmatted contents of nfs4_sessionid */
काष्ठा nfsd4_sessionid अणु
	clientid_t	clientid;
	u32		sequence;
	u32		reserved;
पूर्ण;

#घोषणा HEXसूची_LEN     33 /* hex version of 16 byte md5 of cl_name plus '\0' */

/*
 * काष्ठा nfs4_client - one per client.  Clientids live here.
 *
 * The initial object created by an NFS client using SETCLIENTID (क्रम NFSv4.0)
 * or EXCHANGE_ID (क्रम NFSv4.1+). These objects are refcounted and बारtamped.
 * Each nfsd_net_ns object contains a set of these and they are tracked via
 * लघु and दीर्घ क्रमm clientid. They are hashed and searched क्रम under the
 * per-nfsd_net client_lock spinlock.
 *
 * References to it are only held during the processing of compounds, and in
 * certain other operations. In their "resting state" they have a refcount of
 * 0. If they are not renewed within a lease period, they become eligible क्रम
 * deकाष्ठाion by the laundromat.
 *
 * These objects can also be destroyed prematurely by the fault injection code,
 * or अगर the client sends certain क्रमms of SETCLIENTID or EXCHANGE_ID updates.
 * Care is taken *not* to करो this however when the objects have an elevated
 * refcount.
 *
 * o Each nfs4_client is hashed by clientid
 *
 * o Each nfs4_clients is also hashed by name (the opaque quantity initially
 *   sent by the client to identअगरy itself).
 * 	  
 * o cl_perclient list is used to ensure no dangling stateowner references
 *   when we expire the nfs4_client
 */
काष्ठा nfs4_client अणु
	काष्ठा list_head	cl_idhash; 	/* hash by cl_clientid.id */
	काष्ठा rb_node		cl_namenode;	/* link पूर्णांकo by-name trees */
	काष्ठा list_head	*cl_ownerstr_hashtbl;
	काष्ठा list_head	cl_खोलोowners;
	काष्ठा idr		cl_stateids;	/* stateid lookup */
	काष्ठा list_head	cl_delegations;
	काष्ठा list_head	cl_revoked;	/* unacknowledged, revoked 4.1 state */
	काष्ठा list_head        cl_lru;         /* tail queue */
#अगर_घोषित CONFIG_NFSD_PNFS
	काष्ठा list_head	cl_lo_states;	/* outstanding layout states */
#पूर्ण_अगर
	काष्ठा xdr_netobj	cl_name; 	/* id generated by client */
	nfs4_verअगरier		cl_verअगरier; 	/* generated by client */
	समय64_t		cl_समय;	/* समय of last lease renewal */
	काष्ठा sockaddr_storage	cl_addr; 	/* client ipaddress */
	bool			cl_mach_cred;	/* SP4_MACH_CRED in क्रमce */
	काष्ठा svc_cred		cl_cred; 	/* setclientid principal */
	clientid_t		cl_clientid;	/* generated by server */
	nfs4_verअगरier		cl_confirm;	/* generated by server */
	u32			cl_minorversion;
	/* NFSv4.1 client implementation id: */
	काष्ठा xdr_netobj	cl_nii_करोमुख्य;
	काष्ठा xdr_netobj	cl_nii_name;
	काष्ठा बारpec64	cl_nii_समय;

	/* क्रम v4.0 and v4.1 callbacks: */
	काष्ठा nfs4_cb_conn	cl_cb_conn;
#घोषणा NFSD4_CLIENT_CB_UPDATE		(0)
#घोषणा NFSD4_CLIENT_CB_KILL		(1)
#घोषणा NFSD4_CLIENT_STABLE		(2)	/* client on stable storage */
#घोषणा NFSD4_CLIENT_RECLAIM_COMPLETE	(3)	/* reclaim_complete करोne */
#घोषणा NFSD4_CLIENT_CONFIRMED		(4)	/* client is confirmed */
#घोषणा NFSD4_CLIENT_UPCALL_LOCK	(5)	/* upcall serialization */
#घोषणा NFSD4_CLIENT_CB_FLAG_MASK	(1 << NFSD4_CLIENT_CB_UPDATE | \
					 1 << NFSD4_CLIENT_CB_KILL)
	अचिन्हित दीर्घ		cl_flags;
	स्थिर काष्ठा cred	*cl_cb_cred;
	काष्ठा rpc_clnt		*cl_cb_client;
	u32			cl_cb_ident;
#घोषणा NFSD4_CB_UP		0
#घोषणा NFSD4_CB_UNKNOWN	1
#घोषणा NFSD4_CB_DOWN		2
#घोषणा NFSD4_CB_FAULT		3
	पूर्णांक			cl_cb_state;
	काष्ठा nfsd4_callback	cl_cb_null;
	काष्ठा nfsd4_session	*cl_cb_session;

	/* क्रम all client inक्रमmation that callback code might need: */
	spinlock_t		cl_lock;

	/* क्रम nfs41 */
	काष्ठा list_head	cl_sessions;
	काष्ठा nfsd4_clid_slot	cl_cs_slot;	/* create_session slot */
	u32			cl_exchange_flags;
	/* number of rpc's in progress over an associated session: */
	atomic_t		cl_rpc_users;
	काष्ठा nfsdfs_client	cl_nfsdfs;
	काष्ठा nfs4_op_map      cl_spo_must_allow;

	/* debugging info directory under nfsd/clients/ : */
	काष्ठा dentry		*cl_nfsd_dentry;
	/* 'info' file within that directory. Ref is not counted,
	 * but will reमुख्य valid अगरf cl_nfsd_dentry != शून्य
	 */
	काष्ठा dentry		*cl_nfsd_info_dentry;

	/* क्रम nfs41 callbacks */
	/* We currently support a single back channel with a single slot */
	अचिन्हित दीर्घ		cl_cb_slot_busy;
	काष्ठा rpc_रुको_queue	cl_cb_रुकोq;	/* backchannel callers may */
						/* रुको here क्रम slots */
	काष्ठा net		*net;
	काष्ठा list_head	async_copies;	/* list of async copies */
	spinlock_t		async_lock;	/* lock क्रम async copies */
	atomic_t		cl_cb_inflight;	/* Outstanding callbacks */
पूर्ण;

/* काष्ठा nfs4_client_reset
 * one per old client. Populates reset_str_hashtbl. Filled from conf_id_hashtbl
 * upon lease reset, or from upcall to state_daemon (to पढ़ो in state
 * from non-volitile storage) upon reboot.
 */
काष्ठा nfs4_client_reclaim अणु
	काष्ठा list_head	cr_strhash;	/* hash by cr_name */
	काष्ठा nfs4_client	*cr_clp;	/* poपूर्णांकer to associated clp */
	काष्ठा xdr_netobj	cr_name;	/* recovery dir name */
	काष्ठा xdr_netobj	cr_princhash;
पूर्ण;

/* A reasonable value क्रम REPLAY_ISIZE was estimated as follows:  
 * The OPEN response, typically the largest, requires 
 *   4(status) + 8(stateid) + 20(changeinfo) + 4(rflags) +  8(verअगरier) + 
 *   4(deleg. type) + 8(deleg. stateid) + 4(deleg. recall flag) + 
 *   20(deleg. space limit) + ~32(deleg. ace) = 112 bytes 
 */

#घोषणा NFSD4_REPLAY_ISIZE       112 

/*
 * Replay buffer, where the result of the last seqid-mutating operation 
 * is cached. 
 */
काष्ठा nfs4_replay अणु
	__be32			rp_status;
	अचिन्हित पूर्णांक		rp_buflen;
	अक्षर			*rp_buf;
	काष्ठा knfsd_fh		rp_खोलोfh;
	काष्ठा mutex		rp_mutex;
	अक्षर			rp_ibuf[NFSD4_REPLAY_ISIZE];
पूर्ण;

काष्ठा nfs4_stateowner;

काष्ठा nfs4_stateowner_operations अणु
	व्योम (*so_unhash)(काष्ठा nfs4_stateowner *);
	व्योम (*so_मुक्त)(काष्ठा nfs4_stateowner *);
पूर्ण;

/*
 * A core object that represents either an खोलो or lock owner. The object and
 * lock owner objects have one of these embedded within them. Refcounts and
 * other fields common to both owner types are contained within these
 * काष्ठाures.
 */
काष्ठा nfs4_stateowner अणु
	काष्ठा list_head			so_strhash;
	काष्ठा list_head			so_stateids;
	काष्ठा nfs4_client			*so_client;
	स्थिर काष्ठा nfs4_stateowner_operations	*so_ops;
	/* after increment in nfsd4_bump_seqid, represents the next
	 * sequence id expected from the client: */
	atomic_t				so_count;
	u32					so_seqid;
	काष्ठा xdr_netobj			so_owner; /* खोलो owner name */
	काष्ठा nfs4_replay			so_replay;
	bool					so_is_खोलो_owner;
पूर्ण;

/*
 * When a file is खोलोed, the client provides an खोलो state owner opaque string
 * that indicates the "owner" of that खोलो. These objects are refcounted.
 * References to it are held by each खोलो state associated with it. This object
 * is a superset of the nfs4_stateowner काष्ठा.
 */
काष्ठा nfs4_खोलोowner अणु
	काष्ठा nfs4_stateowner	oo_owner; /* must be first field */
	काष्ठा list_head        oo_perclient;
	/*
	 * We keep around खोलोowners a little जबतक after last बंद,
	 * which saves clients from having to confirm, and allows us to
	 * handle बंद replays अगर they come soon enough.  The बंद_lru
	 * is a list of such खोलोowners, to be reaped by the laundromat
	 * thपढ़ो eventually अगर they reमुख्य unused:
	 */
	काष्ठा list_head	oo_बंद_lru;
	काष्ठा nfs4_ol_stateid *oo_last_बंदd_stid;
	समय64_t		oo_समय; /* समय of placement on so_बंद_lru */
#घोषणा NFS4_OO_CONFIRMED   1
	अचिन्हित अक्षर		oo_flags;
पूर्ण;

/*
 * Represents a generic "lockowner". Similar to an खोलोowner. References to it
 * are held by the lock stateids that are created on its behalf. This object is
 * a superset of the nfs4_stateowner काष्ठा.
 */
काष्ठा nfs4_lockowner अणु
	काष्ठा nfs4_stateowner	lo_owner;	/* must be first element */
	काष्ठा list_head	lo_blocked;	/* blocked file_locks */
पूर्ण;

अटल अंतरभूत काष्ठा nfs4_खोलोowner * खोलोowner(काष्ठा nfs4_stateowner *so)
अणु
	वापस container_of(so, काष्ठा nfs4_खोलोowner, oo_owner);
पूर्ण

अटल अंतरभूत काष्ठा nfs4_lockowner * lockowner(काष्ठा nfs4_stateowner *so)
अणु
	वापस container_of(so, काष्ठा nfs4_lockowner, lo_owner);
पूर्ण

/*
 * Per-client state indicating no. of खोलोs and outstanding delegations
 * on a file from a particular client.'od' stands for 'open & delegation'
 */
काष्ठा nfs4_clnt_odstate अणु
	काष्ठा nfs4_client	*co_client;
	काष्ठा nfs4_file	*co_file;
	काष्ठा list_head	co_perfile;
	refcount_t		co_odcount;
पूर्ण;

/*
 * nfs4_file: a file खोलोed by some number of (खोलो) nfs4_stateowners.
 *
 * These objects are global. nfsd keeps one instance of a nfs4_file per
 * filehandle (though it may keep multiple file descriptors क्रम each). Each
 * inode can have multiple filehandles associated with it, so there is
 * (potentially) a many to one relationship between this काष्ठा and काष्ठा
 * inode.
 *
 * These are hashed by filehandle in the file_hashtbl, which is रक्षित by
 * the global state_lock spinlock.
 */
काष्ठा nfs4_file अणु
	refcount_t		fi_ref;
	काष्ठा inode *		fi_inode;
	bool			fi_aliased;
	spinlock_t		fi_lock;
	काष्ठा hlist_node       fi_hash;	/* hash on fi_fhandle */
	काष्ठा list_head        fi_stateids;
	जोड़ अणु
		काष्ठा list_head	fi_delegations;
		काष्ठा rcu_head		fi_rcu;
	पूर्ण;
	काष्ठा list_head	fi_clnt_odstate;
	/* One each क्रम O_RDONLY, O_WRONLY, O_RDWR: */
	काष्ठा nfsd_file	*fi_fds[3];
	/*
	 * Each खोलो or lock stateid contributes 0-4 to the counts
	 * below depending on which bits are set in st_access_biपंचांगap:
	 *     1 to fi_access[O_RDONLY] अगर NFS4_SHARE_ACCES_READ is set
	 *   + 1 to fi_access[O_WRONLY] अगर NFS4_SHARE_ACCESS_WRITE is set
	 *   + 1 to both of the above अगर NFS4_SHARE_ACCESS_BOTH is set.
	 */
	atomic_t		fi_access[2];
	u32			fi_share_deny;
	काष्ठा nfsd_file	*fi_deleg_file;
	पूर्णांक			fi_delegees;
	काष्ठा knfsd_fh		fi_fhandle;
	bool			fi_had_conflict;
#अगर_घोषित CONFIG_NFSD_PNFS
	काष्ठा list_head	fi_lo_states;
	atomic_t		fi_lo_recalls;
#पूर्ण_अगर
पूर्ण;

/*
 * A generic काष्ठा representing either a खोलो or lock stateid. The nfs4_client
 * holds a reference to each of these objects, and they in turn hold a
 * reference to their respective stateowners. The client's reference is
 * released in response to a बंद or unlock (depending on whether it's an खोलो
 * or lock stateid) or when the client is being destroyed.
 *
 * In the हाल of v4.0 खोलो stateids, these objects are preserved क्रम a little
 * जबतक after बंद in order to handle CLOSE replays. Those are eventually
 * reclaimed via a LRU scheme by the laundromat.
 *
 * This object is a superset of the nfs4_stid. "ol" stands क्रम "Open or Lock".
 * Better suggestions welcome.
 */
काष्ठा nfs4_ol_stateid अणु
	काष्ठा nfs4_stid		st_stid;
	काष्ठा list_head		st_perfile;
	काष्ठा list_head		st_perstateowner;
	काष्ठा list_head		st_locks;
	काष्ठा nfs4_stateowner		*st_stateowner;
	काष्ठा nfs4_clnt_odstate	*st_clnt_odstate;
	अचिन्हित अक्षर			st_access_bmap;
	अचिन्हित अक्षर			st_deny_bmap;
	काष्ठा nfs4_ol_stateid		*st_खोलोstp;
	काष्ठा mutex			st_mutex;
पूर्ण;

अटल अंतरभूत काष्ठा nfs4_ol_stateid *खोलोlockstateid(काष्ठा nfs4_stid *s)
अणु
	वापस container_of(s, काष्ठा nfs4_ol_stateid, st_stid);
पूर्ण

काष्ठा nfs4_layout_stateid अणु
	काष्ठा nfs4_stid		ls_stid;
	काष्ठा list_head		ls_perclnt;
	काष्ठा list_head		ls_perfile;
	spinlock_t			ls_lock;
	काष्ठा list_head		ls_layouts;
	u32				ls_layout_type;
	काष्ठा nfsd_file		*ls_file;
	काष्ठा nfsd4_callback		ls_recall;
	stateid_t			ls_recall_sid;
	bool				ls_recalled;
	काष्ठा mutex			ls_mutex;
पूर्ण;

अटल अंतरभूत काष्ठा nfs4_layout_stateid *layoutstateid(काष्ठा nfs4_stid *s)
अणु
	वापस container_of(s, काष्ठा nfs4_layout_stateid, ls_stid);
पूर्ण

/* flags क्रम preprocess_seqid_op() */
#घोषणा RD_STATE	        0x00000010
#घोषणा WR_STATE	        0x00000020

क्रमागत nfsd4_cb_op अणु
	NFSPROC4_CLNT_CB_शून्य = 0,
	NFSPROC4_CLNT_CB_RECALL,
	NFSPROC4_CLNT_CB_LAYOUT,
	NFSPROC4_CLNT_CB_OFFLOAD,
	NFSPROC4_CLNT_CB_SEQUENCE,
	NFSPROC4_CLNT_CB_NOTIFY_LOCK,
पूर्ण;

/* Returns true अगरf a is later than b: */
अटल अंतरभूत bool nfsd4_stateid_generation_after(stateid_t *a, stateid_t *b)
अणु
	वापस (s32)(a->si_generation - b->si_generation) > 0;
पूर्ण

/*
 * When a client tries to get a lock on a file, we set one of these objects
 * on the blocking lock. When the lock becomes मुक्त, we can then issue a
 * CB_NOTIFY_LOCK to the server.
 */
काष्ठा nfsd4_blocked_lock अणु
	काष्ठा list_head	nbl_list;
	काष्ठा list_head	nbl_lru;
	समय64_t		nbl_समय;
	काष्ठा file_lock	nbl_lock;
	काष्ठा knfsd_fh		nbl_fh;
	काष्ठा nfsd4_callback	nbl_cb;
पूर्ण;

काष्ठा nfsd4_compound_state;
काष्ठा nfsd_net;
काष्ठा nfsd4_copy;

बाह्य __be32 nfs4_preprocess_stateid_op(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, काष्ठा svc_fh *fhp,
		stateid_t *stateid, पूर्णांक flags, काष्ठा nfsd_file **filp,
		काष्ठा nfs4_stid **cstid);
__be32 nfsd4_lookup_stateid(काष्ठा nfsd4_compound_state *cstate,
		     stateid_t *stateid, अचिन्हित अक्षर typemask,
		     काष्ठा nfs4_stid **s, काष्ठा nfsd_net *nn);
काष्ठा nfs4_stid *nfs4_alloc_stid(काष्ठा nfs4_client *cl, काष्ठा kmem_cache *slab,
				  व्योम (*sc_मुक्त)(काष्ठा nfs4_stid *));
पूर्णांक nfs4_init_copy_state(काष्ठा nfsd_net *nn, काष्ठा nfsd4_copy *copy);
व्योम nfs4_मुक्त_copy_state(काष्ठा nfsd4_copy *copy);
काष्ठा nfs4_cpntf_state *nfs4_alloc_init_cpntf_state(काष्ठा nfsd_net *nn,
			काष्ठा nfs4_stid *p_stid);
व्योम nfs4_unhash_stid(काष्ठा nfs4_stid *s);
व्योम nfs4_put_stid(काष्ठा nfs4_stid *s);
व्योम nfs4_inc_and_copy_stateid(stateid_t *dst, काष्ठा nfs4_stid *stid);
व्योम nfs4_हटाओ_reclaim_record(काष्ठा nfs4_client_reclaim *, काष्ठा nfsd_net *);
बाह्य व्योम nfs4_release_reclaim(काष्ठा nfsd_net *);
बाह्य काष्ठा nfs4_client_reclaim *nfsd4_find_reclaim_client(काष्ठा xdr_netobj name,
							काष्ठा nfsd_net *nn);
बाह्य __be32 nfs4_check_खोलो_reclaim(काष्ठा nfs4_client *);
बाह्य व्योम nfsd4_probe_callback(काष्ठा nfs4_client *clp);
बाह्य व्योम nfsd4_probe_callback_sync(काष्ठा nfs4_client *clp);
बाह्य व्योम nfsd4_change_callback(काष्ठा nfs4_client *clp, काष्ठा nfs4_cb_conn *);
बाह्य व्योम nfsd4_init_cb(काष्ठा nfsd4_callback *cb, काष्ठा nfs4_client *clp,
		स्थिर काष्ठा nfsd4_callback_ops *ops, क्रमागत nfsd4_cb_op op);
बाह्य व्योम nfsd4_run_cb(काष्ठा nfsd4_callback *cb);
बाह्य पूर्णांक nfsd4_create_callback_queue(व्योम);
बाह्य व्योम nfsd4_destroy_callback_queue(व्योम);
बाह्य व्योम nfsd4_shutकरोwn_callback(काष्ठा nfs4_client *);
बाह्य व्योम nfsd4_shutकरोwn_copy(काष्ठा nfs4_client *clp);
बाह्य व्योम nfsd4_prepare_cb_recall(काष्ठा nfs4_delegation *dp);
बाह्य काष्ठा nfs4_client_reclaim *nfs4_client_to_reclaim(काष्ठा xdr_netobj name,
				काष्ठा xdr_netobj princhash, काष्ठा nfsd_net *nn);
बाह्य bool nfs4_has_reclaimed_state(काष्ठा xdr_netobj name, काष्ठा nfsd_net *nn);

व्योम put_nfs4_file(काष्ठा nfs4_file *fi);
बाह्य व्योम nfs4_put_copy(काष्ठा nfsd4_copy *copy);
बाह्य काष्ठा nfsd4_copy *
find_async_copy(काष्ठा nfs4_client *clp, stateid_t *staetid);
बाह्य व्योम nfs4_put_cpntf_state(काष्ठा nfsd_net *nn,
				 काष्ठा nfs4_cpntf_state *cps);
बाह्य __be32 manage_cpntf_state(काष्ठा nfsd_net *nn, stateid_t *st,
				 काष्ठा nfs4_client *clp,
				 काष्ठा nfs4_cpntf_state **cps);
अटल अंतरभूत व्योम get_nfs4_file(काष्ठा nfs4_file *fi)
अणु
	refcount_inc(&fi->fi_ref);
पूर्ण
काष्ठा nfsd_file *find_any_file(काष्ठा nfs4_file *f);

/* grace period management */
व्योम nfsd4_end_grace(काष्ठा nfsd_net *nn);

/* nfs4recover operations */
बाह्य पूर्णांक nfsd4_client_tracking_init(काष्ठा net *net);
बाह्य व्योम nfsd4_client_tracking_निकास(काष्ठा net *net);
बाह्य व्योम nfsd4_client_record_create(काष्ठा nfs4_client *clp);
बाह्य व्योम nfsd4_client_record_हटाओ(काष्ठा nfs4_client *clp);
बाह्य पूर्णांक nfsd4_client_record_check(काष्ठा nfs4_client *clp);
बाह्य व्योम nfsd4_record_grace_करोne(काष्ठा nfsd_net *nn);

#पूर्ण_अगर   /* NFSD4_STATE_H */
