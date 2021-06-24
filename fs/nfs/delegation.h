<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/fs/nfs/delegation.h
 *
 * Copyright (c) Trond Myklebust
 *
 * Definitions pertaining to NFS delegated files
 */
#अगर_अघोषित FS_NFS_DELEGATION_H
#घोषणा FS_NFS_DELEGATION_H

#अगर IS_ENABLED(CONFIG_NFS_V4)
/*
 * NFSv4 delegation
 */
काष्ठा nfs_delegation अणु
	काष्ठा list_head super_list;
	स्थिर काष्ठा cred *cred;
	काष्ठा inode *inode;
	nfs4_stateid stateid;
	भ_शेषe_t type;
	अचिन्हित दीर्घ pagemod_limit;
	__u64 change_attr;
	अचिन्हित दीर्घ flags;
	refcount_t refcount;
	spinlock_t lock;
	काष्ठा rcu_head rcu;
पूर्ण;

क्रमागत अणु
	NFS_DELEGATION_NEED_RECLAIM = 0,
	NFS_DELEGATION_RETURN,
	NFS_DELEGATION_RETURN_IF_CLOSED,
	NFS_DELEGATION_REFERENCED,
	NFS_DELEGATION_RETURNING,
	NFS_DELEGATION_REVOKED,
	NFS_DELEGATION_TEST_EXPIRED,
	NFS_DELEGATION_INODE_FREEING,
पूर्ण;

पूर्णांक nfs_inode_set_delegation(काष्ठा inode *inode, स्थिर काष्ठा cred *cred,
		भ_शेषe_t type, स्थिर nfs4_stateid *stateid, अचिन्हित दीर्घ pagemod_limit);
व्योम nfs_inode_reclaim_delegation(काष्ठा inode *inode, स्थिर काष्ठा cred *cred,
		भ_शेषe_t type, स्थिर nfs4_stateid *stateid, अचिन्हित दीर्घ pagemod_limit);
पूर्णांक nfs4_inode_वापस_delegation(काष्ठा inode *inode);
व्योम nfs4_inode_वापस_delegation_on_बंद(काष्ठा inode *inode);
पूर्णांक nfs_async_inode_वापस_delegation(काष्ठा inode *inode, स्थिर nfs4_stateid *stateid);
व्योम nfs_inode_evict_delegation(काष्ठा inode *inode);

काष्ठा inode *nfs_delegation_find_inode(काष्ठा nfs_client *clp, स्थिर काष्ठा nfs_fh *fhandle);
व्योम nfs_server_वापस_all_delegations(काष्ठा nfs_server *);
व्योम nfs_expire_all_delegations(काष्ठा nfs_client *clp);
व्योम nfs_expire_unused_delegation_types(काष्ठा nfs_client *clp, भ_शेषe_t flags);
व्योम nfs_expire_unreferenced_delegations(काष्ठा nfs_client *clp);
पूर्णांक nfs_client_वापस_marked_delegations(काष्ठा nfs_client *clp);
पूर्णांक nfs_delegations_present(काष्ठा nfs_client *clp);
व्योम nfs_हटाओ_bad_delegation(काष्ठा inode *inode, स्थिर nfs4_stateid *stateid);
व्योम nfs_delegation_mark_वापसed(काष्ठा inode *inode, स्थिर nfs4_stateid *stateid);

व्योम nfs_delegation_mark_reclaim(काष्ठा nfs_client *clp);
व्योम nfs_delegation_reap_unclaimed(काष्ठा nfs_client *clp);

व्योम nfs_mark_test_expired_all_delegations(काष्ठा nfs_client *clp);
व्योम nfs_test_expired_all_delegations(काष्ठा nfs_client *clp);
व्योम nfs_reap_expired_delegations(काष्ठा nfs_client *clp);

/* NFSv4 delegation-related procedures */
पूर्णांक nfs4_proc_delegवापस(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, स्थिर nfs4_stateid *stateid, पूर्णांक issync);
पूर्णांक nfs4_खोलो_delegation_recall(काष्ठा nfs_खोलो_context *ctx, काष्ठा nfs4_state *state, स्थिर nfs4_stateid *stateid);
पूर्णांक nfs4_lock_delegation_recall(काष्ठा file_lock *fl, काष्ठा nfs4_state *state, स्थिर nfs4_stateid *stateid);
bool nfs4_copy_delegation_stateid(काष्ठा inode *inode, भ_शेषe_t flags, nfs4_stateid *dst, स्थिर काष्ठा cred **cred);
bool nfs4_refresh_delegation_stateid(nfs4_stateid *dst, काष्ठा inode *inode);

काष्ठा nfs_delegation *nfs4_get_valid_delegation(स्थिर काष्ठा inode *inode);
व्योम nfs_mark_delegation_referenced(काष्ठा nfs_delegation *delegation);
पूर्णांक nfs4_have_delegation(काष्ठा inode *inode, भ_शेषe_t flags);
पूर्णांक nfs4_check_delegation(काष्ठा inode *inode, भ_शेषe_t flags);
bool nfs4_delegation_flush_on_बंद(स्थिर काष्ठा inode *inode);
व्योम nfs_inode_find_delegation_state_and_recover(काष्ठा inode *inode,
		स्थिर nfs4_stateid *stateid);
पूर्णांक nfs4_inode_make_ग_लिखोable(काष्ठा inode *inode);

#पूर्ण_अगर

अटल अंतरभूत पूर्णांक nfs_have_delegated_attributes(काष्ठा inode *inode)
अणु
	वापस NFS_PROTO(inode)->have_delegation(inode, FMODE_READ);
पूर्ण

#पूर्ण_अगर
