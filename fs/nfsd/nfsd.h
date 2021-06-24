<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Hodge-podge collection of knfsd-related stuff.
 * I will sort this out later.
 *
 * Copyright (C) 1995-1997 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित LINUX_NFSD_NFSD_H
#घोषणा LINUX_NFSD_NFSD_H

#समावेश <linux/types.h>
#समावेश <linux/mount.h>

#समावेश <linux/nfs.h>
#समावेश <linux/nfs2.h>
#समावेश <linux/nfs3.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/sunrpc/addr.h>

#समावेश <uapi/linux/nfsd/debug.h>

#समावेश "netns.h"
#समावेश "export.h"
#समावेश "stats.h"

#अघोषित अगरdebug
#अगर_घोषित CONFIG_SUNRPC_DEBUG
# define अगरdebug(flag)		अगर (nfsd_debug & NFSDDBG_##flag)
#अन्यथा
# define अगरdebug(flag)		अगर (0)
#पूर्ण_अगर

/*
 * nfsd version
 */
#घोषणा NFSD_SUPPORTED_MINOR_VERSION	2
/*
 * Maximum blocksizes supported by daemon under various circumstances.
 */
#घोषणा NFSSVC_MAXBLKSIZE       RPCSVC_MAXPAYLOAD
/* NFSv2 is limited by the protocol specअगरication, see RFC 1094 */
#घोषणा NFSSVC_MAXBLKSIZE_V2    (8*1024)


/*
 * Largest number of bytes we need to allocate क्रम an NFS
 * call or reply.  Used to control buffer sizes.  We use
 * the length of v3 WRITE, READसूची and READसूची replies
 * which are an RPC header, up to 26 XDR units of reply
 * data, and some page data.
 *
 * Note that accuracy here करोesn't matter too much as the
 * size is rounded up to a page size when allocating space.
 */
#घोषणा NFSD_बफ_मानE            ((RPC_MAX_HEADER_WITH_AUTH+26)*XDR_UNIT + NFSSVC_MAXBLKSIZE)

काष्ठा सूची_पढ़ो_cd अणु
	__be32			err;	/* 0, nfserr, or nfserr_eof */
पूर्ण;


बाह्य काष्ठा svc_program	nfsd_program;
बाह्य स्थिर काष्ठा svc_version	nfsd_version2, nfsd_version3,
				nfsd_version4;
बाह्य काष्ठा mutex		nfsd_mutex;
बाह्य spinlock_t		nfsd_drc_lock;
बाह्य अचिन्हित दीर्घ		nfsd_drc_max_mem;
बाह्य अचिन्हित दीर्घ		nfsd_drc_mem_used;

बाह्य स्थिर काष्ठा seq_operations nfs_exports_op;

/*
 * Common व्योम argument and result helpers
 */
काष्ठा nfsd_व्योमargs अणु पूर्ण;
काष्ठा nfsd_व्योमres अणु पूर्ण;
पूर्णांक		nfssvc_decode_व्योमarg(काष्ठा svc_rqst *rqstp, __be32 *p);
पूर्णांक		nfssvc_encode_व्योमres(काष्ठा svc_rqst *rqstp, __be32 *p);

/*
 * Function prototypes.
 */
पूर्णांक		nfsd_svc(पूर्णांक nrservs, काष्ठा net *net, स्थिर काष्ठा cred *cred);
पूर्णांक		nfsd_dispatch(काष्ठा svc_rqst *rqstp, __be32 *statp);

पूर्णांक		nfsd_nrthपढ़ोs(काष्ठा net *);
पूर्णांक		nfsd_nrpools(काष्ठा net *);
पूर्णांक		nfsd_get_nrthपढ़ोs(पूर्णांक n, पूर्णांक *, काष्ठा net *);
पूर्णांक		nfsd_set_nrthपढ़ोs(पूर्णांक n, पूर्णांक *, काष्ठा net *);
पूर्णांक		nfsd_pool_stats_खोलो(काष्ठा inode *, काष्ठा file *);
पूर्णांक		nfsd_pool_stats_release(काष्ठा inode *, काष्ठा file *);
व्योम		nfsd_shutकरोwn_thपढ़ोs(काष्ठा net *net);

व्योम		nfsd_destroy(काष्ठा net *net);

bool		i_am_nfsd(व्योम);

काष्ठा nfsdfs_client अणु
	काष्ठा kref cl_ref;
	व्योम (*cl_release)(काष्ठा kref *kref);
पूर्ण;

काष्ठा nfsdfs_client *get_nfsdfs_client(काष्ठा inode *);
काष्ठा dentry *nfsd_client_सूची_गढ़ो(काष्ठा nfsd_net *nn,
				 काष्ठा nfsdfs_client *ncl, u32 id,
				 स्थिर काष्ठा tree_descr *,
				 काष्ठा dentry **fdentries);
व्योम nfsd_client_सूची_हटाओ(काष्ठा dentry *dentry);


#अगर defined(CONFIG_NFSD_V2_ACL) || defined(CONFIG_NFSD_V3_ACL)
#अगर_घोषित CONFIG_NFSD_V2_ACL
बाह्य स्थिर काष्ठा svc_version nfsd_acl_version2;
#अन्यथा
#घोषणा nfsd_acl_version2 शून्य
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFSD_V3_ACL
बाह्य स्थिर काष्ठा svc_version nfsd_acl_version3;
#अन्यथा
#घोषणा nfsd_acl_version3 शून्य
#पूर्ण_अगर
#पूर्ण_अगर

काष्ठा nfsd_net;

क्रमागत vers_op अणुNFSD_SET, NFSD_CLEAR, NFSD_TEST, NFSD_AVAIL पूर्ण;
पूर्णांक nfsd_vers(काष्ठा nfsd_net *nn, पूर्णांक vers, क्रमागत vers_op change);
पूर्णांक nfsd_minorversion(काष्ठा nfsd_net *nn, u32 minorversion, क्रमागत vers_op change);
व्योम nfsd_reset_versions(काष्ठा nfsd_net *nn);
पूर्णांक nfsd_create_serv(काष्ठा net *net);

बाह्य पूर्णांक nfsd_max_blksize;

अटल अंतरभूत पूर्णांक nfsd_v4client(काष्ठा svc_rqst *rq)
अणु
	वापस rq->rq_prog == NFS_PROGRAM && rq->rq_vers == 4;
पूर्ण
अटल अंतरभूत काष्ठा user_namespace *
nfsd_user_namespace(स्थिर काष्ठा svc_rqst *rqstp)
अणु
	स्थिर काष्ठा cred *cred = rqstp->rq_xprt->xpt_cred;
	वापस cred ? cred->user_ns : &init_user_ns;
पूर्ण

/* 
 * NFSv4 State
 */
#अगर_घोषित CONFIG_NFSD_V4
बाह्य अचिन्हित दीर्घ max_delegations;
पूर्णांक nfsd4_init_sद_असल(व्योम);
व्योम nfsd4_मुक्त_sद_असल(व्योम);
पूर्णांक nfs4_state_start(व्योम);
पूर्णांक nfs4_state_start_net(काष्ठा net *net);
व्योम nfs4_state_shutकरोwn(व्योम);
व्योम nfs4_state_shutकरोwn_net(काष्ठा net *net);
पूर्णांक nfs4_reset_recoverydir(अक्षर *recdir);
अक्षर * nfs4_recoverydir(व्योम);
bool nfsd4_spo_must_allow(काष्ठा svc_rqst *rqstp);
#अन्यथा
अटल अंतरभूत पूर्णांक nfsd4_init_sद_असल(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nfsd4_मुक्त_sद_असल(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक nfs4_state_start(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक nfs4_state_start_net(काष्ठा net *net) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nfs4_state_shutकरोwn(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम nfs4_state_shutकरोwn_net(काष्ठा net *net) अणु पूर्ण
अटल अंतरभूत पूर्णांक nfs4_reset_recoverydir(अक्षर *recdir) अणु वापस 0; पूर्ण
अटल अंतरभूत अक्षर * nfs4_recoverydir(व्योम) अणुवापस शून्य; पूर्ण
अटल अंतरभूत bool nfsd4_spo_must_allow(काष्ठा svc_rqst *rqstp)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * lockd binding
 */
व्योम		nfsd_lockd_init(व्योम);
व्योम		nfsd_lockd_shutकरोwn(व्योम);


/*
 * These macros provide pre-xdr'ed values क्रम faster operation.
 */
#घोषणा	nfs_ok			cpu_to_be32(NFS_OK)
#घोषणा	nfserr_perm		cpu_to_be32(NFSERR_PERM)
#घोषणा	nfserr_noent		cpu_to_be32(NFSERR_NOENT)
#घोषणा	nfserr_io		cpu_to_be32(NFSERR_IO)
#घोषणा	nfserr_nxio		cpu_to_be32(NFSERR_NXIO)
#घोषणा	nfserr_eagain		cpu_to_be32(NFSERR_EAGAIN)
#घोषणा	nfserr_acces		cpu_to_be32(NFSERR_ACCES)
#घोषणा	nfserr_exist		cpu_to_be32(NFSERR_EXIST)
#घोषणा	nfserr_xdev		cpu_to_be32(NFSERR_XDEV)
#घोषणा	nfserr_nodev		cpu_to_be32(NFSERR_NODEV)
#घोषणा	nfserr_notdir		cpu_to_be32(NFSERR_NOTसूची)
#घोषणा	nfserr_isdir		cpu_to_be32(NFSERR_ISसूची)
#घोषणा	nfserr_inval		cpu_to_be32(NFSERR_INVAL)
#घोषणा	nfserr_fbig		cpu_to_be32(NFSERR_FBIG)
#घोषणा	nfserr_nospc		cpu_to_be32(NFSERR_NOSPC)
#घोषणा	nfserr_rofs		cpu_to_be32(NFSERR_ROFS)
#घोषणा	nfserr_mlink		cpu_to_be32(NFSERR_MLINK)
#घोषणा	nfserr_opnotsupp	cpu_to_be32(NFSERR_OPNOTSUPP)
#घोषणा	nfserr_nametooदीर्घ	cpu_to_be32(NFSERR_NAMETOOLONG)
#घोषणा	nfserr_notempty		cpu_to_be32(NFSERR_NOTEMPTY)
#घोषणा	nfserr_dquot		cpu_to_be32(NFSERR_DQUOT)
#घोषणा	nfserr_stale		cpu_to_be32(NFSERR_STALE)
#घोषणा	nfserr_remote		cpu_to_be32(NFSERR_REMOTE)
#घोषणा	nfserr_wflush		cpu_to_be32(NFSERR_WFLUSH)
#घोषणा	nfserr_badhandle	cpu_to_be32(NFSERR_BADHANDLE)
#घोषणा	nfserr_notsync		cpu_to_be32(NFSERR_NOT_SYNC)
#घोषणा	nfserr_badcookie	cpu_to_be32(NFSERR_BAD_COOKIE)
#घोषणा	nfserr_notsupp		cpu_to_be32(NFSERR_NOTSUPP)
#घोषणा	nfserr_toosmall		cpu_to_be32(NFSERR_TOOSMALL)
#घोषणा	nfserr_serverfault	cpu_to_be32(NFSERR_SERVERFAULT)
#घोषणा	nfserr_badtype		cpu_to_be32(NFSERR_BADTYPE)
#घोषणा	nfserr_jukebox		cpu_to_be32(NFSERR_JUKEBOX)
#घोषणा	nfserr_denied		cpu_to_be32(NFSERR_DENIED)
#घोषणा	nfserr_deadlock		cpu_to_be32(NFSERR_DEADLOCK)
#घोषणा nfserr_expired          cpu_to_be32(NFSERR_EXPIRED)
#घोषणा	nfserr_bad_cookie	cpu_to_be32(NFSERR_BAD_COOKIE)
#घोषणा	nfserr_same		cpu_to_be32(NFSERR_SAME)
#घोषणा	nfserr_clid_inuse	cpu_to_be32(NFSERR_CLID_INUSE)
#घोषणा	nfserr_stale_clientid	cpu_to_be32(NFSERR_STALE_CLIENTID)
#घोषणा	nfserr_resource		cpu_to_be32(NFSERR_RESOURCE)
#घोषणा	nfserr_moved		cpu_to_be32(NFSERR_MOVED)
#घोषणा	nfserr_nofilehandle	cpu_to_be32(NFSERR_NOखाताHANDLE)
#घोषणा	nfserr_minor_vers_mismatch	cpu_to_be32(NFSERR_MINOR_VERS_MISMATCH)
#घोषणा nfserr_share_denied	cpu_to_be32(NFSERR_SHARE_DENIED)
#घोषणा nfserr_stale_stateid	cpu_to_be32(NFSERR_STALE_STATEID)
#घोषणा nfserr_old_stateid	cpu_to_be32(NFSERR_OLD_STATEID)
#घोषणा nfserr_bad_stateid	cpu_to_be32(NFSERR_BAD_STATEID)
#घोषणा nfserr_bad_seqid	cpu_to_be32(NFSERR_BAD_SEQID)
#घोषणा	nfserr_symlink		cpu_to_be32(NFSERR_SYMLINK)
#घोषणा	nfserr_not_same		cpu_to_be32(NFSERR_NOT_SAME)
#घोषणा nfserr_lock_range	cpu_to_be32(NFSERR_LOCK_RANGE)
#घोषणा	nfserr_restorefh	cpu_to_be32(NFSERR_RESTOREFH)
#घोषणा	nfserr_attrnotsupp	cpu_to_be32(NFSERR_ATTRNOTSUPP)
#घोषणा	nfserr_bad_xdr		cpu_to_be32(NFSERR_BAD_XDR)
#घोषणा	nfserr_खोलोmode		cpu_to_be32(NFSERR_OPENMODE)
#घोषणा	nfserr_baकरोwner		cpu_to_be32(NFSERR_BADOWNER)
#घोषणा	nfserr_locks_held	cpu_to_be32(NFSERR_LOCKS_HELD)
#घोषणा	nfserr_op_illegal	cpu_to_be32(NFSERR_OP_ILLEGAL)
#घोषणा	nfserr_grace		cpu_to_be32(NFSERR_GRACE)
#घोषणा	nfserr_no_grace		cpu_to_be32(NFSERR_NO_GRACE)
#घोषणा	nfserr_reclaim_bad	cpu_to_be32(NFSERR_RECLAIM_BAD)
#घोषणा	nfserr_badname		cpu_to_be32(NFSERR_BADNAME)
#घोषणा	nfserr_cb_path_करोwn	cpu_to_be32(NFSERR_CB_PATH_DOWN)
#घोषणा	nfserr_locked		cpu_to_be32(NFSERR_LOCKED)
#घोषणा	nfserr_wrongsec		cpu_to_be32(NFSERR_WRONGSEC)
#घोषणा nfserr_badiomode		cpu_to_be32(NFS4ERR_BADIOMODE)
#घोषणा nfserr_badlayout		cpu_to_be32(NFS4ERR_BADLAYOUT)
#घोषणा nfserr_bad_session_digest	cpu_to_be32(NFS4ERR_BAD_SESSION_DIGEST)
#घोषणा nfserr_badsession		cpu_to_be32(NFS4ERR_BADSESSION)
#घोषणा nfserr_badslot			cpu_to_be32(NFS4ERR_BADSLOT)
#घोषणा nfserr_complete_alपढ़ोy		cpu_to_be32(NFS4ERR_COMPLETE_ALREADY)
#घोषणा nfserr_conn_not_bound_to_session cpu_to_be32(NFS4ERR_CONN_NOT_BOUND_TO_SESSION)
#घोषणा nfserr_deleg_alपढ़ोy_wanted	cpu_to_be32(NFS4ERR_DELEG_ALREADY_WANTED)
#घोषणा nfserr_back_chan_busy		cpu_to_be32(NFS4ERR_BACK_CHAN_BUSY)
#घोषणा nfserr_layouttrylater		cpu_to_be32(NFS4ERR_LAYOUTTRYLATER)
#घोषणा nfserr_layoutunavailable	cpu_to_be32(NFS4ERR_LAYOUTUNAVAILABLE)
#घोषणा nfserr_nomatching_layout	cpu_to_be32(NFS4ERR_NOMATCHING_LAYOUT)
#घोषणा nfserr_recallconflict		cpu_to_be32(NFS4ERR_RECALLCONFLICT)
#घोषणा nfserr_unknown_layouttype	cpu_to_be32(NFS4ERR_UNKNOWN_LAYOUTTYPE)
#घोषणा nfserr_seq_misordered		cpu_to_be32(NFS4ERR_SEQ_MISORDERED)
#घोषणा nfserr_sequence_pos		cpu_to_be32(NFS4ERR_SEQUENCE_POS)
#घोषणा nfserr_req_too_big		cpu_to_be32(NFS4ERR_REQ_TOO_BIG)
#घोषणा nfserr_rep_too_big		cpu_to_be32(NFS4ERR_REP_TOO_BIG)
#घोषणा nfserr_rep_too_big_to_cache	cpu_to_be32(NFS4ERR_REP_TOO_BIG_TO_CACHE)
#घोषणा nfserr_retry_uncached_rep	cpu_to_be32(NFS4ERR_RETRY_UNCACHED_REP)
#घोषणा nfserr_unsafe_compound		cpu_to_be32(NFS4ERR_UNSAFE_COMPOUND)
#घोषणा nfserr_too_many_ops		cpu_to_be32(NFS4ERR_TOO_MANY_OPS)
#घोषणा nfserr_op_not_in_session	cpu_to_be32(NFS4ERR_OP_NOT_IN_SESSION)
#घोषणा nfserr_hash_alg_unsupp		cpu_to_be32(NFS4ERR_HASH_ALG_UNSUPP)
#घोषणा nfserr_clientid_busy		cpu_to_be32(NFS4ERR_CLIENTID_BUSY)
#घोषणा nfserr_pnfs_io_hole		cpu_to_be32(NFS4ERR_PNFS_IO_HOLE)
#घोषणा nfserr_seq_false_retry		cpu_to_be32(NFS4ERR_SEQ_FALSE_RETRY)
#घोषणा nfserr_bad_high_slot		cpu_to_be32(NFS4ERR_BAD_HIGH_SLOT)
#घोषणा nfserr_deadsession		cpu_to_be32(NFS4ERR_DEADSESSION)
#घोषणा nfserr_encr_alg_unsupp		cpu_to_be32(NFS4ERR_ENCR_ALG_UNSUPP)
#घोषणा nfserr_pnfs_no_layout		cpu_to_be32(NFS4ERR_PNFS_NO_LAYOUT)
#घोषणा nfserr_not_only_op		cpu_to_be32(NFS4ERR_NOT_ONLY_OP)
#घोषणा nfserr_wrong_cred		cpu_to_be32(NFS4ERR_WRONG_CRED)
#घोषणा nfserr_wrong_type		cpu_to_be32(NFS4ERR_WRONG_TYPE)
#घोषणा nfserr_dirdeleg_unavail		cpu_to_be32(NFS4ERR_सूचीDELEG_UNAVAIL)
#घोषणा nfserr_reject_deleg		cpu_to_be32(NFS4ERR_REJECT_DELEG)
#घोषणा nfserr_वापसconflict		cpu_to_be32(NFS4ERR_RETURNCONFLICT)
#घोषणा nfserr_deleg_revoked		cpu_to_be32(NFS4ERR_DELEG_REVOKED)
#घोषणा nfserr_partner_notsupp		cpu_to_be32(NFS4ERR_PARTNER_NOTSUPP)
#घोषणा nfserr_partner_no_auth		cpu_to_be32(NFS4ERR_PARTNER_NO_AUTH)
#घोषणा nfserr_जोड़_notsupp		cpu_to_be32(NFS4ERR_UNION_NOTSUPP)
#घोषणा nfserr_offload_denied		cpu_to_be32(NFS4ERR_OFFLOAD_DENIED)
#घोषणा nfserr_wrong_lfs		cpu_to_be32(NFS4ERR_WRONG_LFS)
#घोषणा nfserr_badlabel			cpu_to_be32(NFS4ERR_BADLABEL)
#घोषणा nfserr_file_खोलो		cpu_to_be32(NFS4ERR_खाता_OPEN)
#घोषणा nfserr_xattr2big		cpu_to_be32(NFS4ERR_XATTR2BIG)
#घोषणा nfserr_noxattr			cpu_to_be32(NFS4ERR_NOXATTR)

/* error codes क्रम पूर्णांकernal use */
/* अगर a request fails due to kदो_स्मृति failure, it माला_लो dropped.
 *  Client should resend eventually
 */
#घोषणा	nfserr_dropit		cpu_to_be32(30000)
/* end-of-file indicator in सूची_पढ़ो */
#घोषणा	nfserr_eof		cpu_to_be32(30001)
/* replay detected */
#घोषणा	nfserr_replay_me	cpu_to_be32(11001)
/* nfs41 replay detected */
#घोषणा	nfserr_replay_cache	cpu_to_be32(11002)

/* Check क्रम dir entries '.' and '..' */
#घोषणा isकरोtent(n, l)	(l < 3 && n[0] == '.' && (l == 1 || n[1] == '.'))

#अगर_घोषित CONFIG_NFSD_V4

/* beक्रमe processing a COMPOUND operation, we have to check that there
 * is enough space in the buffer क्रम XDR encode to succeed.  otherwise,
 * we might process an operation with side effects, and be unable to
 * tell the client that the operation succeeded.
 *
 * COMPOUND_SLACK_SPACE - this is the minimum bytes of buffer space
 * needed to encode an "ordinary" _successful_ operation.  (GETATTR,
 * READ, READसूची, and READLINK have their own buffer checks.)  अगर we
 * fall below this level, we fail the next operation with NFS4ERR_RESOURCE.
 *
 * COMPOUND_ERR_SLACK_SPACE - this is the minimum bytes of buffer space
 * needed to encode an operation which has failed with NFS4ERR_RESOURCE.
 * care is taken to ensure that we never fall below this level क्रम any
 * reason.
 */
#घोषणा	COMPOUND_SLACK_SPACE		140    /* OP_GETFH */
#घोषणा COMPOUND_ERR_SLACK_SPACE	16     /* OP_SETATTR */

#घोषणा NFSD_LAUNDROMAT_MINTIMEOUT      1   /* seconds */

/*
 * The following attributes are currently not supported by the NFSv4 server:
 *    ARCHIVE       (deprecated anyway)
 *    HIDDEN        (unlikely to be supported any समय soon)
 *    MIMETYPE      (unlikely to be supported any समय soon)
 *    QUOTA_*       (will be supported in a क्रमthcoming patch)
 *    SYSTEM        (unlikely to be supported any समय soon)
 *    TIME_BACKUP   (unlikely to be supported any समय soon)
 *    TIME_CREATE   (unlikely to be supported any समय soon)
 */
#घोषणा NFSD4_SUPPORTED_ATTRS_WORD0                                                         \
(FATTR4_WORD0_SUPPORTED_ATTRS   | FATTR4_WORD0_TYPE         | FATTR4_WORD0_FH_EXPIRE_TYPE   \
 | FATTR4_WORD0_CHANGE          | FATTR4_WORD0_SIZE         | FATTR4_WORD0_LINK_SUPPORT     \
 | FATTR4_WORD0_SYMLINK_SUPPORT | FATTR4_WORD0_NAMED_ATTR   | FATTR4_WORD0_FSID             \
 | FATTR4_WORD0_UNIQUE_HANDLES  | FATTR4_WORD0_LEASE_TIME   | FATTR4_WORD0_RDATTR_ERROR     \
 | FATTR4_WORD0_ACLSUPPORT      | FATTR4_WORD0_CANSETTIME   | FATTR4_WORD0_CASE_INSENSITIVE \
 | FATTR4_WORD0_CASE_PRESERVING | FATTR4_WORD0_CHOWN_RESTRICTED                             \
 | FATTR4_WORD0_खाताHANDLE      | FATTR4_WORD0_खाताID       | FATTR4_WORD0_खाताS_AVAIL      \
 | FATTR4_WORD0_खाताS_FREE      | FATTR4_WORD0_खाताS_TOTAL  | FATTR4_WORD0_FS_LOCATIONS | FATTR4_WORD0_HOMOGENEOUS      \
 | FATTR4_WORD0_MAXखाताSIZE     | FATTR4_WORD0_MAXLINK      | FATTR4_WORD0_MAXNAME          \
 | FATTR4_WORD0_MAXREAD         | FATTR4_WORD0_MAXWRITE     | FATTR4_WORD0_ACL)

#घोषणा NFSD4_SUPPORTED_ATTRS_WORD1                                                         \
(FATTR4_WORD1_MODE              | FATTR4_WORD1_NO_TRUNC     | FATTR4_WORD1_NUMLINKS         \
 | FATTR4_WORD1_OWNER	        | FATTR4_WORD1_OWNER_GROUP  | FATTR4_WORD1_RAWDEV           \
 | FATTR4_WORD1_SPACE_AVAIL     | FATTR4_WORD1_SPACE_FREE   | FATTR4_WORD1_SPACE_TOTAL      \
 | FATTR4_WORD1_SPACE_USED      | FATTR4_WORD1_TIME_ACCESS  | FATTR4_WORD1_TIME_ACCESS_SET  \
 | FATTR4_WORD1_TIME_DELTA   | FATTR4_WORD1_TIME_METADATA    \
 | FATTR4_WORD1_TIME_MODIFY     | FATTR4_WORD1_TIME_MODIFY_SET | FATTR4_WORD1_MOUNTED_ON_खाताID)

#घोषणा NFSD4_SUPPORTED_ATTRS_WORD2 0

/* 4.1 */
#अगर_घोषित CONFIG_NFSD_PNFS
#घोषणा PNFSD_SUPPORTED_ATTRS_WORD1	FATTR4_WORD1_FS_LAYOUT_TYPES
#घोषणा PNFSD_SUPPORTED_ATTRS_WORD2 \
(FATTR4_WORD2_LAYOUT_BLKSIZE	| FATTR4_WORD2_LAYOUT_TYPES)
#अन्यथा
#घोषणा PNFSD_SUPPORTED_ATTRS_WORD1	0
#घोषणा PNFSD_SUPPORTED_ATTRS_WORD2	0
#पूर्ण_अगर /* CONFIG_NFSD_PNFS */

#घोषणा NFSD4_1_SUPPORTED_ATTRS_WORD0 \
	NFSD4_SUPPORTED_ATTRS_WORD0

#घोषणा NFSD4_1_SUPPORTED_ATTRS_WORD1 \
	(NFSD4_SUPPORTED_ATTRS_WORD1	| PNFSD_SUPPORTED_ATTRS_WORD1)

#घोषणा NFSD4_1_SUPPORTED_ATTRS_WORD2 \
	(NFSD4_SUPPORTED_ATTRS_WORD2	| PNFSD_SUPPORTED_ATTRS_WORD2 | \
	 FATTR4_WORD2_SUPPATTR_EXCLCREAT)

/* 4.2 */
#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
#घोषणा NFSD4_2_SECURITY_ATTRS		FATTR4_WORD2_SECURITY_LABEL
#अन्यथा
#घोषणा NFSD4_2_SECURITY_ATTRS		0
#पूर्ण_अगर

#घोषणा NFSD4_2_SUPPORTED_ATTRS_WORD2 \
	(NFSD4_1_SUPPORTED_ATTRS_WORD2 | \
	FATTR4_WORD2_MODE_UMASK | \
	NFSD4_2_SECURITY_ATTRS | \
	FATTR4_WORD2_XATTR_SUPPORT)

बाह्य स्थिर u32 nfsd_suppattrs[3][3];

अटल अंतरभूत __be32 nfsd4_set_netaddr(काष्ठा sockaddr *addr,
				    काष्ठा nfs42_netaddr *netaddr)
अणु
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)addr;
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)addr;
	अचिन्हित पूर्णांक port;
	माप_प्रकार ret_addr, ret_port;

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		port = ntohs(sin->sin_port);
		प्र_लिखो(netaddr->netid, "tcp");
		netaddr->netid_len = 3;
		अवरोध;
	हाल AF_INET6:
		port = ntohs(sin6->sin6_port);
		प्र_लिखो(netaddr->netid, "tcp6");
		netaddr->netid_len = 4;
		अवरोध;
	शेष:
		वापस nfserr_inval;
	पूर्ण
	ret_addr = rpc_ntop(addr, netaddr->addr, माप(netaddr->addr));
	ret_port = snम_लिखो(netaddr->addr + ret_addr,
			    RPCBIND_MAXUADDRLEN + 1 - ret_addr,
			    ".%u.%u", port >> 8, port & 0xff);
	WARN_ON(ret_port >= RPCBIND_MAXUADDRLEN + 1 - ret_addr);
	netaddr->addr_len = ret_addr + ret_port;
	वापस 0;
पूर्ण

अटल अंतरभूत bool bmval_is_subset(स्थिर u32 *bm1, स्थिर u32 *bm2)
अणु
	वापस !((bm1[0] & ~bm2[0]) ||
	         (bm1[1] & ~bm2[1]) ||
		 (bm1[2] & ~bm2[2]));
पूर्ण

अटल अंतरभूत bool nfsd_attrs_supported(u32 minorversion, स्थिर u32 *bmval)
अणु
	वापस bmval_is_subset(bmval, nfsd_suppattrs[minorversion]);
पूर्ण

/* These will वापस ERR_INVAL अगर specअगरied in GETATTR or READसूची. */
#घोषणा NFSD_WRITEONLY_ATTRS_WORD1 \
	(FATTR4_WORD1_TIME_ACCESS_SET   | FATTR4_WORD1_TIME_MODIFY_SET)

/*
 * These are the only attrs allowed in CREATE/OPEN/SETATTR. Don't add
 * a ग_लिखोable attribute here without also adding code to parse it to
 * nfsd4_decode_fattr().
 */
#घोषणा NFSD_WRITEABLE_ATTRS_WORD0 \
	(FATTR4_WORD0_SIZE | FATTR4_WORD0_ACL)
#घोषणा NFSD_WRITEABLE_ATTRS_WORD1 \
	(FATTR4_WORD1_MODE | FATTR4_WORD1_OWNER | FATTR4_WORD1_OWNER_GROUP \
	| FATTR4_WORD1_TIME_ACCESS_SET | FATTR4_WORD1_TIME_MODIFY_SET)
#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
#घोषणा MAYBE_FATTR4_WORD2_SECURITY_LABEL \
	FATTR4_WORD2_SECURITY_LABEL
#अन्यथा
#घोषणा MAYBE_FATTR4_WORD2_SECURITY_LABEL 0
#पूर्ण_अगर
#घोषणा NFSD_WRITEABLE_ATTRS_WORD2 \
	(FATTR4_WORD2_MODE_UMASK \
	| MAYBE_FATTR4_WORD2_SECURITY_LABEL)

#घोषणा NFSD_SUPPATTR_EXCLCREAT_WORD0 \
	NFSD_WRITEABLE_ATTRS_WORD0
/*
 * we currently store the exclusive create verअगरier in the v_अणुa,mपूर्णसमय
 * attributes so the client can't set these at create समय using EXCLUSIVE4_1
 */
#घोषणा NFSD_SUPPATTR_EXCLCREAT_WORD1 \
	(NFSD_WRITEABLE_ATTRS_WORD1 & \
	 ~(FATTR4_WORD1_TIME_ACCESS_SET | FATTR4_WORD1_TIME_MODIFY_SET))
#घोषणा NFSD_SUPPATTR_EXCLCREAT_WORD2 \
	NFSD_WRITEABLE_ATTRS_WORD2

बाह्य पूर्णांक nfsd4_is_junction(काष्ठा dentry *dentry);
बाह्य पूर्णांक रेजिस्टर_cld_notअगरier(व्योम);
बाह्य व्योम unरेजिस्टर_cld_notअगरier(व्योम);
#अन्यथा /* CONFIG_NFSD_V4 */
अटल अंतरभूत पूर्णांक nfsd4_is_junction(काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

#घोषणा रेजिस्टर_cld_notअगरier() 0
#घोषणा unरेजिस्टर_cld_notअगरier() करो अणु पूर्ण जबतक(0)

#पूर्ण_अगर /* CONFIG_NFSD_V4 */

#पूर्ण_अगर /* LINUX_NFSD_NFSD_H */
