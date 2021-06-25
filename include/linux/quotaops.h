<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम diskquota-operations. When diskquota is configured these
 * macros expand to the right source-code.
 *
 * Author:  Marco van Wieringen <mvw@planets.elm.net>
 */
#अगर_अघोषित _LINUX_QUOTAOPS_
#घोषणा _LINUX_QUOTAOPS_

#समावेश <linux/fs.h>

#घोषणा DQUOT_SPACE_WARN	0x1
#घोषणा DQUOT_SPACE_RESERVE	0x2
#घोषणा DQUOT_SPACE_NOFAIL	0x4

अटल अंतरभूत काष्ठा quota_info *sb_dqopt(काष्ठा super_block *sb)
अणु
	वापस &sb->s_dquot;
पूर्ण

/* i_mutex must being held */
अटल अंतरभूत bool is_quota_modअगरication(काष्ठा inode *inode, काष्ठा iattr *ia)
अणु
	वापस (ia->ia_valid & ATTR_SIZE) ||
		(ia->ia_valid & ATTR_UID && !uid_eq(ia->ia_uid, inode->i_uid)) ||
		(ia->ia_valid & ATTR_GID && !gid_eq(ia->ia_gid, inode->i_gid));
पूर्ण

#अगर defined(CONFIG_QUOTA)

#घोषणा quota_error(sb, fmt, args...) \
	__quota_error((sb), __func__, fmt , ## args)

बाह्य __म_लिखो(3, 4)
व्योम __quota_error(काष्ठा super_block *sb, स्थिर अक्षर *func,
		   स्थिर अक्षर *fmt, ...);

/*
 * declaration of quota_function calls in kernel.
 */
पूर्णांक dquot_initialize(काष्ठा inode *inode);
bool dquot_initialize_needed(काष्ठा inode *inode);
व्योम dquot_drop(काष्ठा inode *inode);
काष्ठा dquot *dqget(काष्ठा super_block *sb, काष्ठा kqid qid);
अटल अंतरभूत काष्ठा dquot *dqgrab(काष्ठा dquot *dquot)
अणु
	/* Make sure someone अन्यथा has active reference to dquot */
	WARN_ON_ONCE(!atomic_पढ़ो(&dquot->dq_count));
	WARN_ON_ONCE(!test_bit(DQ_ACTIVE_B, &dquot->dq_flags));
	atomic_inc(&dquot->dq_count);
	वापस dquot;
पूर्ण

अटल अंतरभूत bool dquot_is_busy(काष्ठा dquot *dquot)
अणु
	अगर (test_bit(DQ_MOD_B, &dquot->dq_flags))
		वापस true;
	अगर (atomic_पढ़ो(&dquot->dq_count) > 1)
		वापस true;
	वापस false;
पूर्ण

व्योम dqput(काष्ठा dquot *dquot);
पूर्णांक dquot_scan_active(काष्ठा super_block *sb,
		      पूर्णांक (*fn)(काष्ठा dquot *dquot, अचिन्हित दीर्घ priv),
		      अचिन्हित दीर्घ priv);
काष्ठा dquot *dquot_alloc(काष्ठा super_block *sb, पूर्णांक type);
व्योम dquot_destroy(काष्ठा dquot *dquot);

पूर्णांक __dquot_alloc_space(काष्ठा inode *inode, qमाप_प्रकार number, पूर्णांक flags);
व्योम __dquot_मुक्त_space(काष्ठा inode *inode, qमाप_प्रकार number, पूर्णांक flags);

पूर्णांक dquot_alloc_inode(काष्ठा inode *inode);

पूर्णांक dquot_claim_space_nodirty(काष्ठा inode *inode, qमाप_प्रकार number);
व्योम dquot_मुक्त_inode(काष्ठा inode *inode);
व्योम dquot_reclaim_space_nodirty(काष्ठा inode *inode, qमाप_प्रकार number);

पूर्णांक dquot_disable(काष्ठा super_block *sb, पूर्णांक type, अचिन्हित पूर्णांक flags);
/* Suspend quotas on remount RO */
अटल अंतरभूत पूर्णांक dquot_suspend(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस dquot_disable(sb, type, DQUOT_SUSPENDED);
पूर्ण
पूर्णांक dquot_resume(काष्ठा super_block *sb, पूर्णांक type);

पूर्णांक dquot_commit(काष्ठा dquot *dquot);
पूर्णांक dquot_acquire(काष्ठा dquot *dquot);
पूर्णांक dquot_release(काष्ठा dquot *dquot);
पूर्णांक dquot_commit_info(काष्ठा super_block *sb, पूर्णांक type);
पूर्णांक dquot_get_next_id(काष्ठा super_block *sb, काष्ठा kqid *qid);
पूर्णांक dquot_mark_dquot_dirty(काष्ठा dquot *dquot);

पूर्णांक dquot_file_खोलो(काष्ठा inode *inode, काष्ठा file *file);

पूर्णांक dquot_load_quota_sb(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
	अचिन्हित पूर्णांक flags);
पूर्णांक dquot_load_quota_inode(काष्ठा inode *inode, पूर्णांक type, पूर्णांक क्रमmat_id,
	अचिन्हित पूर्णांक flags);
पूर्णांक dquot_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
	स्थिर काष्ठा path *path);
पूर्णांक dquot_quota_on_mount(काष्ठा super_block *sb, अक्षर *qf_name,
 	पूर्णांक क्रमmat_id, पूर्णांक type);
पूर्णांक dquot_quota_off(काष्ठा super_block *sb, पूर्णांक type);
पूर्णांक dquot_ग_लिखोback_dquots(काष्ठा super_block *sb, पूर्णांक type);
पूर्णांक dquot_quota_sync(काष्ठा super_block *sb, पूर्णांक type);
पूर्णांक dquot_get_state(काष्ठा super_block *sb, काष्ठा qc_state *state);
पूर्णांक dquot_set_dqinfo(काष्ठा super_block *sb, पूर्णांक type, काष्ठा qc_info *ii);
पूर्णांक dquot_get_dqblk(काष्ठा super_block *sb, काष्ठा kqid id,
		काष्ठा qc_dqblk *di);
पूर्णांक dquot_get_next_dqblk(काष्ठा super_block *sb, काष्ठा kqid *id,
		काष्ठा qc_dqblk *di);
पूर्णांक dquot_set_dqblk(काष्ठा super_block *sb, काष्ठा kqid id,
		काष्ठा qc_dqblk *di);

पूर्णांक __dquot_transfer(काष्ठा inode *inode, काष्ठा dquot **transfer_to);
पूर्णांक dquot_transfer(काष्ठा inode *inode, काष्ठा iattr *iattr);

अटल अंतरभूत काष्ठा mem_dqinfo *sb_dqinfo(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस sb_dqopt(sb)->info + type;
पूर्ण

/*
 * Functions क्रम checking status of quota
 */

अटल अंतरभूत bool sb_has_quota_usage_enabled(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस sb_dqopt(sb)->flags &
				dquot_state_flag(DQUOT_USAGE_ENABLED, type);
पूर्ण

अटल अंतरभूत bool sb_has_quota_limits_enabled(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस sb_dqopt(sb)->flags &
				dquot_state_flag(DQUOT_LIMITS_ENABLED, type);
पूर्ण

अटल अंतरभूत bool sb_has_quota_suspended(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस sb_dqopt(sb)->flags &
				dquot_state_flag(DQUOT_SUSPENDED, type);
पूर्ण

अटल अंतरभूत अचिन्हित sb_any_quota_suspended(काष्ठा super_block *sb)
अणु
	वापस dquot_state_types(sb_dqopt(sb)->flags, DQUOT_SUSPENDED);
पूर्ण

/* Does kernel know about any quota inक्रमmation क्रम given sb + type? */
अटल अंतरभूत bool sb_has_quota_loaded(काष्ठा super_block *sb, पूर्णांक type)
अणु
	/* Currently अगर anything is on, then quota usage is on as well */
	वापस sb_has_quota_usage_enabled(sb, type);
पूर्ण

अटल अंतरभूत अचिन्हित sb_any_quota_loaded(काष्ठा super_block *sb)
अणु
	वापस dquot_state_types(sb_dqopt(sb)->flags, DQUOT_USAGE_ENABLED);
पूर्ण

अटल अंतरभूत bool sb_has_quota_active(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस sb_has_quota_loaded(sb, type) &&
	       !sb_has_quota_suspended(sb, type);
पूर्ण

/*
 * Operations supported क्रम diskquotas.
 */
बाह्य स्थिर काष्ठा dquot_operations dquot_operations;
बाह्य स्थिर काष्ठा quotactl_ops dquot_quotactl_sysfile_ops;

#अन्यथा

अटल अंतरभूत पूर्णांक sb_has_quota_usage_enabled(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sb_has_quota_limits_enabled(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sb_has_quota_suspended(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sb_any_quota_suspended(काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण

/* Does kernel know about any quota inक्रमmation क्रम given sb + type? */
अटल अंतरभूत पूर्णांक sb_has_quota_loaded(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sb_any_quota_loaded(काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sb_has_quota_active(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dquot_initialize(काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool dquot_initialize_needed(काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम dquot_drop(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक dquot_alloc_inode(काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dquot_मुक्त_inode(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक dquot_transfer(काष्ठा inode *inode, काष्ठा iattr *iattr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __dquot_alloc_space(काष्ठा inode *inode, qमाप_प्रकार number,
		पूर्णांक flags)
अणु
	अगर (!(flags & DQUOT_SPACE_RESERVE))
		inode_add_bytes(inode, number);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __dquot_मुक्त_space(काष्ठा inode *inode, qमाप_प्रकार number,
		पूर्णांक flags)
अणु
	अगर (!(flags & DQUOT_SPACE_RESERVE))
		inode_sub_bytes(inode, number);
पूर्ण

अटल अंतरभूत पूर्णांक dquot_claim_space_nodirty(काष्ठा inode *inode, qमाप_प्रकार number)
अणु
	inode_add_bytes(inode, number);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dquot_reclaim_space_nodirty(काष्ठा inode *inode,
					      qमाप_प्रकार number)
अणु
	inode_sub_bytes(inode, number);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dquot_disable(काष्ठा super_block *sb, पूर्णांक type,
		अचिन्हित पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dquot_suspend(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dquot_resume(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस 0;
पूर्ण

#घोषणा dquot_file_खोलो		generic_file_खोलो

अटल अंतरभूत पूर्णांक dquot_ग_लिखोback_dquots(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_QUOTA */

अटल अंतरभूत पूर्णांक dquot_alloc_space_nodirty(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	वापस __dquot_alloc_space(inode, nr, DQUOT_SPACE_WARN);
पूर्ण

अटल अंतरभूत व्योम dquot_alloc_space_nofail(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	__dquot_alloc_space(inode, nr, DQUOT_SPACE_WARN|DQUOT_SPACE_NOFAIL);
	mark_inode_dirty_sync(inode);
पूर्ण

अटल अंतरभूत पूर्णांक dquot_alloc_space(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	पूर्णांक ret;

	ret = dquot_alloc_space_nodirty(inode, nr);
	अगर (!ret) अणु
		/*
		 * Mark inode fully dirty. Since we are allocating blocks, inode
		 * would become fully dirty soon anyway and it reportedly
		 * reduces lock contention.
		 */
		mark_inode_dirty(inode);
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक dquot_alloc_block_nodirty(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	वापस dquot_alloc_space_nodirty(inode, nr << inode->i_blkbits);
पूर्ण

अटल अंतरभूत व्योम dquot_alloc_block_nofail(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	dquot_alloc_space_nofail(inode, nr << inode->i_blkbits);
पूर्ण

अटल अंतरभूत पूर्णांक dquot_alloc_block(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	वापस dquot_alloc_space(inode, nr << inode->i_blkbits);
पूर्ण

अटल अंतरभूत पूर्णांक dquot_pपुनः_स्मृति_block_nodirty(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	वापस __dquot_alloc_space(inode, nr << inode->i_blkbits, 0);
पूर्ण

अटल अंतरभूत पूर्णांक dquot_pपुनः_स्मृति_block(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	पूर्णांक ret;

	ret = dquot_pपुनः_स्मृति_block_nodirty(inode, nr);
	अगर (!ret)
		mark_inode_dirty_sync(inode);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक dquot_reserve_block(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	वापस __dquot_alloc_space(inode, nr << inode->i_blkbits,
				DQUOT_SPACE_WARN|DQUOT_SPACE_RESERVE);
पूर्ण

अटल अंतरभूत पूर्णांक dquot_claim_block(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	पूर्णांक ret;

	ret = dquot_claim_space_nodirty(inode, nr << inode->i_blkbits);
	अगर (!ret)
		mark_inode_dirty_sync(inode);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम dquot_reclaim_block(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	dquot_reclaim_space_nodirty(inode, nr << inode->i_blkbits);
	mark_inode_dirty_sync(inode);
पूर्ण

अटल अंतरभूत व्योम dquot_मुक्त_space_nodirty(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	__dquot_मुक्त_space(inode, nr, 0);
पूर्ण

अटल अंतरभूत व्योम dquot_मुक्त_space(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	dquot_मुक्त_space_nodirty(inode, nr);
	mark_inode_dirty_sync(inode);
पूर्ण

अटल अंतरभूत व्योम dquot_मुक्त_block_nodirty(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	dquot_मुक्त_space_nodirty(inode, nr << inode->i_blkbits);
पूर्ण

अटल अंतरभूत व्योम dquot_मुक्त_block(काष्ठा inode *inode, qमाप_प्रकार nr)
अणु
	dquot_मुक्त_space(inode, nr << inode->i_blkbits);
पूर्ण

अटल अंतरभूत व्योम dquot_release_reservation_block(काष्ठा inode *inode,
		qमाप_प्रकार nr)
अणु
	__dquot_मुक्त_space(inode, nr << inode->i_blkbits, DQUOT_SPACE_RESERVE);
पूर्ण

अचिन्हित पूर्णांक qtype_enक्रमce_flag(पूर्णांक type);

#पूर्ण_अगर /* _LINUX_QUOTAOPS_ */
