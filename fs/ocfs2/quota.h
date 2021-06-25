<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * quota.h क्रम OCFS2
 *
 * On disk quota काष्ठाures क्रम local and global quota file, in-memory
 * काष्ठाures.
 *
 */

#अगर_अघोषित _OCFS2_QUOTA_H
#घोषणा _OCFS2_QUOTA_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/quota.h>
#समावेश <linux/list.h>
#समावेश <linux/dqblk_qtree.h>

#समावेश "ocfs2.h"

/* Number of quota types we support */
#घोषणा OCFS2_MAXQUOTAS 2

/*
 * In-memory काष्ठाures
 */
काष्ठा ocfs2_dquot अणु
	काष्ठा dquot dq_dquot;	/* Generic VFS dquot */
	loff_t dq_local_off;	/* Offset in the local quota file */
	u64 dq_local_phys_blk;	/* Physical block carrying quota काष्ठाure */
	काष्ठा ocfs2_quota_chunk *dq_chunk;	/* Chunk dquot is in */
	अचिन्हित पूर्णांक dq_use_count;	/* Number of nodes having reference to this entry in global quota file */
	s64 dq_origspace;	/* Last globally synced space usage */
	s64 dq_originodes;	/* Last globally synced inode usage */
	काष्ठा llist_node list;	/* Member of list of dquots to drop */
पूर्ण;

/* Description of one chunk to recover in memory */
काष्ठा ocfs2_recovery_chunk अणु
	काष्ठा list_head rc_list;	/* List of chunks */
	पूर्णांक rc_chunk;			/* Chunk number */
	अचिन्हित दीर्घ *rc_biपंचांगap;	/* Biपंचांगap of entries to recover */
पूर्ण;

काष्ठा ocfs2_quota_recovery अणु
	काष्ठा list_head r_list[OCFS2_MAXQUOTAS];	/* List of chunks to recover */
पूर्ण;

/* In-memory काष्ठाure with quota header inक्रमmation */
काष्ठा ocfs2_mem_dqinfo अणु
	अचिन्हित पूर्णांक dqi_type;		/* Quota type this काष्ठाure describes */
	अचिन्हित पूर्णांक dqi_flags;		/* Flags OLQF_* */
	अचिन्हित पूर्णांक dqi_chunks;	/* Number of chunks in local quota file */
	अचिन्हित पूर्णांक dqi_blocks;	/* Number of blocks allocated क्रम local quota file */
	अचिन्हित पूर्णांक dqi_syncms;	/* How often should we sync with other nodes */
	काष्ठा list_head dqi_chunk;	/* List of chunks */
	काष्ठा inode *dqi_gqinode;	/* Global quota file inode */
	काष्ठा ocfs2_lock_res dqi_gqlock;	/* Lock protecting quota inक्रमmation काष्ठाure */
	काष्ठा buffer_head *dqi_gqi_bh;	/* Buffer head with global quota file inode - set only अगर inode lock is obtained */
	पूर्णांक dqi_gqi_count;		/* Number of holders of dqi_gqi_bh */
	u64 dqi_giblk;			/* Number of block with global inक्रमmation header */
	काष्ठा buffer_head *dqi_lqi_bh;	/* Buffer head with local quota file inode */
	काष्ठा buffer_head *dqi_libh;	/* Buffer with local inक्रमmation header */
	काष्ठा qtree_mem_dqinfo dqi_gi;	/* Info about global file */
	काष्ठा delayed_work dqi_sync_work;	/* Work क्रम syncing dquots */
	काष्ठा ocfs2_quota_recovery *dqi_rec;	/* Poपूर्णांकer to recovery
						 * inक्रमmation, in हाल we
						 * enable quotas on file
						 * needing it */
पूर्ण;

अटल अंतरभूत काष्ठा ocfs2_dquot *OCFS2_DQUOT(काष्ठा dquot *dquot)
अणु
	वापस container_of(dquot, काष्ठा ocfs2_dquot, dq_dquot);
पूर्ण

काष्ठा ocfs2_quota_chunk अणु
	काष्ठा list_head qc_chunk;	/* List of quotafile chunks */
	पूर्णांक qc_num;			/* Number of quota chunk */
	काष्ठा buffer_head *qc_headerbh;	/* Buffer head with chunk header */
पूर्ण;

बाह्य काष्ठा kmem_cache *ocfs2_dquot_cachep;
बाह्य काष्ठा kmem_cache *ocfs2_qf_chunk_cachep;

बाह्य स्थिर काष्ठा qtree_fmt_operations ocfs2_global_ops;

काष्ठा ocfs2_quota_recovery *ocfs2_begin_quota_recovery(
				काष्ठा ocfs2_super *osb, पूर्णांक slot_num);
पूर्णांक ocfs2_finish_quota_recovery(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_quota_recovery *rec,
				पूर्णांक slot_num);
व्योम ocfs2_मुक्त_quota_recovery(काष्ठा ocfs2_quota_recovery *rec);
sमाप_प्रकार ocfs2_quota_पढ़ो(काष्ठा super_block *sb, पूर्णांक type, अक्षर *data,
			 माप_प्रकार len, loff_t off);
sमाप_प्रकार ocfs2_quota_ग_लिखो(काष्ठा super_block *sb, पूर्णांक type,
			  स्थिर अक्षर *data, माप_प्रकार len, loff_t off);
पूर्णांक ocfs2_global_पढ़ो_info(काष्ठा super_block *sb, पूर्णांक type);
पूर्णांक ocfs2_global_ग_लिखो_info(काष्ठा super_block *sb, पूर्णांक type);
पूर्णांक ocfs2_global_पढ़ो_dquot(काष्ठा dquot *dquot);
पूर्णांक __ocfs2_sync_dquot(काष्ठा dquot *dquot, पूर्णांक मुक्तing);
अटल अंतरभूत पूर्णांक ocfs2_sync_dquot(काष्ठा dquot *dquot)
अणु
	वापस __ocfs2_sync_dquot(dquot, 0);
पूर्ण
अटल अंतरभूत पूर्णांक ocfs2_global_release_dquot(काष्ठा dquot *dquot)
अणु
	वापस __ocfs2_sync_dquot(dquot, 1);
पूर्ण

पूर्णांक ocfs2_lock_global_qf(काष्ठा ocfs2_mem_dqinfo *oinfo, पूर्णांक ex);
व्योम ocfs2_unlock_global_qf(काष्ठा ocfs2_mem_dqinfo *oinfo, पूर्णांक ex);
पूर्णांक ocfs2_validate_quota_block(काष्ठा super_block *sb, काष्ठा buffer_head *bh);
पूर्णांक ocfs2_पढ़ो_quota_phys_block(काष्ठा inode *inode, u64 p_block,
				काष्ठा buffer_head **bh);
पूर्णांक ocfs2_create_local_dquot(काष्ठा dquot *dquot);
पूर्णांक ocfs2_local_release_dquot(handle_t *handle, काष्ठा dquot *dquot);
पूर्णांक ocfs2_local_ग_लिखो_dquot(काष्ठा dquot *dquot);
व्योम ocfs2_drop_dquot_refs(काष्ठा work_काष्ठा *work);

बाह्य स्थिर काष्ठा dquot_operations ocfs2_quota_operations;
बाह्य काष्ठा quota_क्रमmat_type ocfs2_quota_क्रमmat;

#पूर्ण_अगर /* _OCFS2_QUOTA_H */
