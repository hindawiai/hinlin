<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFS_FS_I
#घोषणा _NFS_FS_I

काष्ठा nlm_lockowner;

/*
 * NFS lock info
 */
काष्ठा nfs_lock_info अणु
	u32		state;
	काष्ठा nlm_lockowner *owner;
	काष्ठा list_head list;
पूर्ण;

काष्ठा nfs4_lock_state;
काष्ठा nfs4_lock_info अणु
	काष्ठा nfs4_lock_state *owner;
पूर्ण;

#पूर्ण_अगर
