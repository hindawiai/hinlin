<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs/nfs/nfs4session.h
 *
 * Copyright (c) 2012 Trond Myklebust <Trond.Myklebust@netapp.com>
 *
 */
#अगर_अघोषित __LINUX_FS_NFS_NFS4SESSION_H
#घोषणा __LINUX_FS_NFS_NFS4SESSION_H

/* maximum number of slots to use */
#घोषणा NFS4_DEF_SLOT_TABLE_SIZE (64U)
#घोषणा NFS4_DEF_CB_SLOT_TABLE_SIZE (16U)
#घोषणा NFS4_MAX_SLOT_TABLE (1024U)
#घोषणा NFS4_NO_SLOT ((u32)-1)

#अगर IS_ENABLED(CONFIG_NFS_V4)

/* Sessions slot seqid */
काष्ठा nfs4_slot अणु
	काष्ठा nfs4_slot_table	*table;
	काष्ठा nfs4_slot	*next;
	अचिन्हित दीर्घ		generation;
	u32			slot_nr;
	u32		 	seq_nr;
	u32		 	seq_nr_last_acked;
	u32		 	seq_nr_highest_sent;
	अचिन्हित पूर्णांक		privileged : 1,
				seq_करोne : 1;
पूर्ण;

/* Sessions */
क्रमागत nfs4_slot_tbl_state अणु
	NFS4_SLOT_TBL_DRAINING,
पूर्ण;

#घोषणा SLOT_TABLE_SZ DIV_ROUND_UP(NFS4_MAX_SLOT_TABLE, BITS_PER_LONG)
काष्ठा nfs4_slot_table अणु
	काष्ठा nfs4_session *session;		/* Parent session */
	काष्ठा nfs4_slot *slots;		/* seqid per slot */
	अचिन्हित दीर्घ   used_slots[SLOT_TABLE_SZ]; /* used/unused biपंचांगap */
	spinlock_t	slot_tbl_lock;
	काष्ठा rpc_रुको_queue	slot_tbl_रुकोq;	/* allocators may रुको here */
	रुको_queue_head_t	slot_रुकोq;	/* Completion रुको on slot */
	u32		max_slots;		/* # slots in table */
	u32		max_slotid;		/* Max allowed slotid value */
	u32		highest_used_slotid;	/* sent to server on each SEQ.
						 * op क्रम dynamic resizing */
	u32		target_highest_slotid;	/* Server max_slot target */
	u32		server_highest_slotid;	/* Server highest slotid */
	s32		d_target_highest_slotid; /* Derivative */
	s32		d2_target_highest_slotid; /* 2nd derivative */
	अचिन्हित दीर्घ	generation;		/* Generation counter क्रम
						   target_highest_slotid */
	काष्ठा completion complete;
	अचिन्हित दीर्घ	slot_tbl_state;
पूर्ण;

/*
 * Session related parameters
 */
काष्ठा nfs4_session अणु
	काष्ठा nfs4_sessionid		sess_id;
	u32				flags;
	अचिन्हित दीर्घ			session_state;
	u32				hash_alg;
	u32				ssv_len;

	/* The क्रमe and back channel */
	काष्ठा nfs4_channel_attrs	fc_attrs;
	काष्ठा nfs4_slot_table		fc_slot_table;
	काष्ठा nfs4_channel_attrs	bc_attrs;
	काष्ठा nfs4_slot_table		bc_slot_table;
	काष्ठा nfs_client		*clp;
पूर्ण;

क्रमागत nfs4_session_state अणु
	NFS4_SESSION_INITING,
	NFS4_SESSION_ESTABLISHED,
पूर्ण;

बाह्य पूर्णांक nfs4_setup_slot_table(काष्ठा nfs4_slot_table *tbl,
		अचिन्हित पूर्णांक max_reqs, स्थिर अक्षर *queue);
बाह्य व्योम nfs4_shutकरोwn_slot_table(काष्ठा nfs4_slot_table *tbl);
बाह्य काष्ठा nfs4_slot *nfs4_alloc_slot(काष्ठा nfs4_slot_table *tbl);
बाह्य काष्ठा nfs4_slot *nfs4_lookup_slot(काष्ठा nfs4_slot_table *tbl, u32 slotid);
बाह्य पूर्णांक nfs4_slot_रुको_on_seqid(काष्ठा nfs4_slot_table *tbl,
		u32 slotid, u32 seq_nr,
		अचिन्हित दीर्घ समयout);
बाह्य bool nfs4_try_to_lock_slot(काष्ठा nfs4_slot_table *tbl, काष्ठा nfs4_slot *slot);
बाह्य व्योम nfs4_मुक्त_slot(काष्ठा nfs4_slot_table *tbl, काष्ठा nfs4_slot *slot);
बाह्य व्योम nfs4_slot_tbl_drain_complete(काष्ठा nfs4_slot_table *tbl);
bool nfs41_wake_and_assign_slot(काष्ठा nfs4_slot_table *tbl,
		काष्ठा nfs4_slot *slot);
व्योम nfs41_wake_slot_table(काष्ठा nfs4_slot_table *tbl);

अटल अंतरभूत bool nfs4_slot_tbl_draining(काष्ठा nfs4_slot_table *tbl)
अणु
	वापस !!test_bit(NFS4_SLOT_TBL_DRAINING, &tbl->slot_tbl_state);
पूर्ण

अटल अंतरभूत bool nfs4_test_locked_slot(स्थिर काष्ठा nfs4_slot_table *tbl,
		u32 slotid)
अणु
	वापस !!test_bit(slotid, tbl->used_slots);
पूर्ण

अटल अंतरभूत काष्ठा nfs4_session *nfs4_get_session(स्थिर काष्ठा nfs_client *clp)
अणु
	वापस clp->cl_session;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
बाह्य व्योम nfs41_set_target_slotid(काष्ठा nfs4_slot_table *tbl,
		u32 target_highest_slotid);
बाह्य व्योम nfs41_update_target_slotid(काष्ठा nfs4_slot_table *tbl,
		काष्ठा nfs4_slot *slot,
		काष्ठा nfs4_sequence_res *res);

बाह्य पूर्णांक nfs4_setup_session_slot_tables(काष्ठा nfs4_session *ses);

बाह्य काष्ठा nfs4_session *nfs4_alloc_session(काष्ठा nfs_client *clp);
बाह्य व्योम nfs4_destroy_session(काष्ठा nfs4_session *session);
बाह्य पूर्णांक nfs4_init_session(काष्ठा nfs_client *clp);
बाह्य पूर्णांक nfs4_init_ds_session(काष्ठा nfs_client *, अचिन्हित दीर्घ);

/*
 * Determine अगर sessions are in use.
 */
अटल अंतरभूत पूर्णांक nfs4_has_session(स्थिर काष्ठा nfs_client *clp)
अणु
	अगर (clp->cl_session)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nfs4_has_persistent_session(स्थिर काष्ठा nfs_client *clp)
अणु
	अगर (nfs4_has_session(clp))
		वापस (clp->cl_session->flags & SESSION4_PERSIST);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nfs4_copy_sessionid(काष्ठा nfs4_sessionid *dst,
		स्थिर काष्ठा nfs4_sessionid *src)
अणु
	स_नकल(dst->data, src->data, NFS4_MAX_SESSIONID_LEN);
पूर्ण

#अगर_घोषित CONFIG_CRC32
/*
 * nfs_session_id_hash - calculate the crc32 hash क्रम the session id
 * @session - poपूर्णांकer to session
 */
#घोषणा nfs_session_id_hash(sess_id) \
	(~crc32_le(0xFFFFFFFF, &(sess_id)->data[0], माप((sess_id)->data)))
#अन्यथा
#घोषणा nfs_session_id_hash(session) (0)
#पूर्ण_अगर
#अन्यथा /* defined(CONFIG_NFS_V4_1) */

अटल अंतरभूत पूर्णांक nfs4_init_session(काष्ठा nfs_client *clp)
अणु
	वापस 0;
पूर्ण

/*
 * Determine अगर sessions are in use.
 */
अटल अंतरभूत पूर्णांक nfs4_has_session(स्थिर काष्ठा nfs_client *clp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nfs4_has_persistent_session(स्थिर काष्ठा nfs_client *clp)
अणु
	वापस 0;
पूर्ण

#घोषणा nfs_session_id_hash(session) (0)

#पूर्ण_अगर /* defined(CONFIG_NFS_V4_1) */
#पूर्ण_अगर /* IS_ENABLED(CONFIG_NFS_V4) */
#पूर्ण_अगर /* __LINUX_FS_NFS_NFS4SESSION_H */
