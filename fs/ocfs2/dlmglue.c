<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmglue.c
 *
 * Code which implements an OCFS2 specअगरic पूर्णांकerface to our DLM.
 *
 * Copyright (C) 2003, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/समय.स>
#समावेश <linux/quotaops.h>
#समावेश <linux/sched/संकेत.स>

#घोषणा MLOG_MASK_PREFIX ML_DLM_GLUE
#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"
#समावेश "ocfs2_lockingver.h"

#समावेश "alloc.h"
#समावेश "dcache.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "file.h"
#समावेश "heartbeat.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "stackglue.h"
#समावेश "slot_map.h"
#समावेश "super.h"
#समावेश "uptodate.h"
#समावेश "quota.h"
#समावेश "refcounttree.h"
#समावेश "acl.h"

#समावेश "buffer_head_io.h"

काष्ठा ocfs2_mask_रुकोer अणु
	काष्ठा list_head	mw_item;
	पूर्णांक			mw_status;
	काष्ठा completion	mw_complete;
	अचिन्हित दीर्घ		mw_mask;
	अचिन्हित दीर्घ		mw_goal;
#अगर_घोषित CONFIG_OCFS2_FS_STATS
	kसमय_प्रकार			mw_lock_start;
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा ocfs2_super *ocfs2_get_dentry_osb(काष्ठा ocfs2_lock_res *lockres);
अटल काष्ठा ocfs2_super *ocfs2_get_inode_osb(काष्ठा ocfs2_lock_res *lockres);
अटल काष्ठा ocfs2_super *ocfs2_get_file_osb(काष्ठा ocfs2_lock_res *lockres);
अटल काष्ठा ocfs2_super *ocfs2_get_qinfo_osb(काष्ठा ocfs2_lock_res *lockres);

/*
 * Return value from ->करोwnconvert_worker functions.
 *
 * These control the precise actions of ocfs2_unblock_lock()
 * and ocfs2_process_blocked_lock()
 *
 */
क्रमागत ocfs2_unblock_action अणु
	UNBLOCK_CONTINUE	= 0, /* Continue करोwnconvert */
	UNBLOCK_CONTINUE_POST	= 1, /* Continue करोwnconvert, fire
				      * ->post_unlock callback */
	UNBLOCK_STOP_POST	= 2, /* Do not करोwnconvert, fire
				      * ->post_unlock() callback. */
पूर्ण;

काष्ठा ocfs2_unblock_ctl अणु
	पूर्णांक requeue;
	क्रमागत ocfs2_unblock_action unblock_action;
पूर्ण;

/* Lockdep class keys */
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
अटल काष्ठा lock_class_key lockdep_keys[OCFS2_NUM_LOCK_TYPES];
#पूर्ण_अगर

अटल पूर्णांक ocfs2_check_meta_करोwnconvert(काष्ठा ocfs2_lock_res *lockres,
					पूर्णांक new_level);
अटल व्योम ocfs2_set_meta_lvb(काष्ठा ocfs2_lock_res *lockres);

अटल पूर्णांक ocfs2_data_convert_worker(काष्ठा ocfs2_lock_res *lockres,
				     पूर्णांक blocking);

अटल पूर्णांक ocfs2_dentry_convert_worker(काष्ठा ocfs2_lock_res *lockres,
				       पूर्णांक blocking);

अटल व्योम ocfs2_dentry_post_unlock(काष्ठा ocfs2_super *osb,
				     काष्ठा ocfs2_lock_res *lockres);

अटल व्योम ocfs2_set_qinfo_lvb(काष्ठा ocfs2_lock_res *lockres);

अटल पूर्णांक ocfs2_check_refcount_करोwnconvert(काष्ठा ocfs2_lock_res *lockres,
					    पूर्णांक new_level);
अटल पूर्णांक ocfs2_refcount_convert_worker(काष्ठा ocfs2_lock_res *lockres,
					 पूर्णांक blocking);

#घोषणा mlog_meta_lvb(__level, __lockres) ocfs2_dump_meta_lvb_info(__level, __PRETTY_FUNCTION__, __LINE__, __lockres)

/* This aids in debugging situations where a bad LVB might be involved. */
अटल व्योम ocfs2_dump_meta_lvb_info(u64 level,
				     स्थिर अक्षर *function,
				     अचिन्हित पूर्णांक line,
				     काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा ocfs2_meta_lvb *lvb = ocfs2_dlm_lvb(&lockres->l_lksb);

	mlog(level, "LVB information for %s (called from %s:%u):\n",
	     lockres->l_name, function, line);
	mlog(level, "version: %u, clusters: %u, generation: 0x%x\n",
	     lvb->lvb_version, be32_to_cpu(lvb->lvb_iclusters),
	     be32_to_cpu(lvb->lvb_igeneration));
	mlog(level, "size: %llu, uid %u, gid %u, mode 0x%x\n",
	     (अचिन्हित दीर्घ दीर्घ)be64_to_cpu(lvb->lvb_isize),
	     be32_to_cpu(lvb->lvb_iuid), be32_to_cpu(lvb->lvb_igid),
	     be16_to_cpu(lvb->lvb_imode));
	mlog(level, "nlink %u, atime_packed 0x%llx, ctime_packed 0x%llx, "
	     "mtime_packed 0x%llx iattr 0x%x\n", be16_to_cpu(lvb->lvb_inlink),
	     (दीर्घ दीर्घ)be64_to_cpu(lvb->lvb_iaसमय_packed),
	     (दीर्घ दीर्घ)be64_to_cpu(lvb->lvb_iस_समय_packed),
	     (दीर्घ दीर्घ)be64_to_cpu(lvb->lvb_imसमय_packed),
	     be32_to_cpu(lvb->lvb_iattr));
पूर्ण


/*
 * OCFS2 Lock Resource Operations
 *
 * These fine tune the behavior of the generic dlmglue locking infraकाष्ठाure.
 *
 * The most basic of lock types can poपूर्णांक ->l_priv to their respective
 * काष्ठा ocfs2_super and allow the शेष actions to manage things.
 *
 * Right now, each lock type also needs to implement an init function,
 * and trivial lock/unlock wrappers. ocfs2_simple_drop_lockres()
 * should be called when the lock is no दीर्घer needed (i.e., object
 * deकाष्ठाion समय).
 */
काष्ठा ocfs2_lock_res_ops अणु
	/*
	 * Translate an ocfs2_lock_res * पूर्णांकo an ocfs2_super *. Define
	 * this callback अगर ->l_priv is not an ocfs2_super poपूर्णांकer
	 */
	काष्ठा ocfs2_super * (*get_osb)(काष्ठा ocfs2_lock_res *);

	/*
	 * Optionally called in the करोwnconvert thपढ़ो after a
	 * successful करोwnconvert. The lockres will not be referenced
	 * after this callback is called, so it is safe to मुक्त
	 * memory, etc.
	 *
	 * The exact semantics of when this is called are controlled
	 * by ->करोwnconvert_worker()
	 */
	व्योम (*post_unlock)(काष्ठा ocfs2_super *, काष्ठा ocfs2_lock_res *);

	/*
	 * Allow a lock type to add checks to determine whether it is
	 * safe to करोwnconvert a lock. Return 0 to re-queue the
	 * करोwnconvert at a later समय, nonzero to जारी.
	 *
	 * For most locks, the शेष checks that there are no
	 * incompatible holders are sufficient.
	 *
	 * Called with the lockres spinlock held.
	 */
	पूर्णांक (*check_करोwnconvert)(काष्ठा ocfs2_lock_res *, पूर्णांक);

	/*
	 * Allows a lock type to populate the lock value block. This
	 * is called on करोwnconvert, and when we drop a lock.
	 *
	 * Locks that want to use this should set LOCK_TYPE_USES_LVB
	 * in the flags field.
	 *
	 * Called with the lockres spinlock held.
	 */
	व्योम (*set_lvb)(काष्ठा ocfs2_lock_res *);

	/*
	 * Called from the करोwnconvert thपढ़ो when it is determined
	 * that a lock will be करोwnconverted. This is called without
	 * any locks held so the function can करो work that might
	 * schedule (syncing out data, etc).
	 *
	 * This should वापस any one of the ocfs2_unblock_action
	 * values, depending on what it wants the thपढ़ो to करो.
	 */
	पूर्णांक (*करोwnconvert_worker)(काष्ठा ocfs2_lock_res *, पूर्णांक);

	/*
	 * LOCK_TYPE_* flags which describe the specअगरic requirements
	 * of a lock type. Descriptions of each inभागidual flag follow.
	 */
	पूर्णांक flags;
पूर्ण;

/*
 * Some locks want to "refresh" potentially stale data when a
 * meaningful (PRMODE or EXMODE) lock level is first obtained. If this
 * flag is set, the OCFS2_LOCK_NEEDS_REFRESH flag will be set on the
 * inभागidual lockres l_flags member from the ast function. It is
 * expected that the locking wrapper will clear the
 * OCFS2_LOCK_NEEDS_REFRESH flag when करोne.
 */
#घोषणा LOCK_TYPE_REQUIRES_REFRESH 0x1

/*
 * Indicate that a lock type makes use of the lock value block. The
 * ->set_lvb lock type callback must be defined.
 */
#घोषणा LOCK_TYPE_USES_LVB		0x2

अटल काष्ठा ocfs2_lock_res_ops ocfs2_inode_rw_lops = अणु
	.get_osb	= ocfs2_get_inode_osb,
	.flags		= 0,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_inode_inode_lops = अणु
	.get_osb	= ocfs2_get_inode_osb,
	.check_करोwnconvert = ocfs2_check_meta_करोwnconvert,
	.set_lvb	= ocfs2_set_meta_lvb,
	.करोwnconvert_worker = ocfs2_data_convert_worker,
	.flags		= LOCK_TYPE_REQUIRES_REFRESH|LOCK_TYPE_USES_LVB,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_super_lops = अणु
	.flags		= LOCK_TYPE_REQUIRES_REFRESH,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_नाम_lops = अणु
	.flags		= 0,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_nfs_sync_lops = अणु
	.flags		= 0,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_trim_fs_lops = अणु
	.flags		= LOCK_TYPE_REQUIRES_REFRESH|LOCK_TYPE_USES_LVB,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_orphan_scan_lops = अणु
	.flags		= LOCK_TYPE_REQUIRES_REFRESH|LOCK_TYPE_USES_LVB,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_dentry_lops = अणु
	.get_osb	= ocfs2_get_dentry_osb,
	.post_unlock	= ocfs2_dentry_post_unlock,
	.करोwnconvert_worker = ocfs2_dentry_convert_worker,
	.flags		= 0,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_inode_खोलो_lops = अणु
	.get_osb	= ocfs2_get_inode_osb,
	.flags		= 0,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_flock_lops = अणु
	.get_osb	= ocfs2_get_file_osb,
	.flags		= 0,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_qinfo_lops = अणु
	.set_lvb	= ocfs2_set_qinfo_lvb,
	.get_osb	= ocfs2_get_qinfo_osb,
	.flags		= LOCK_TYPE_REQUIRES_REFRESH | LOCK_TYPE_USES_LVB,
पूर्ण;

अटल काष्ठा ocfs2_lock_res_ops ocfs2_refcount_block_lops = अणु
	.check_करोwnconvert = ocfs2_check_refcount_करोwnconvert,
	.करोwnconvert_worker = ocfs2_refcount_convert_worker,
	.flags		= 0,
पूर्ण;

अटल अंतरभूत पूर्णांक ocfs2_is_inode_lock(काष्ठा ocfs2_lock_res *lockres)
अणु
	वापस lockres->l_type == OCFS2_LOCK_TYPE_META ||
		lockres->l_type == OCFS2_LOCK_TYPE_RW ||
		lockres->l_type == OCFS2_LOCK_TYPE_OPEN;
पूर्ण

अटल अंतरभूत काष्ठा ocfs2_lock_res *ocfs2_lksb_to_lock_res(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	वापस container_of(lksb, काष्ठा ocfs2_lock_res, l_lksb);
पूर्ण

अटल अंतरभूत काष्ठा inode *ocfs2_lock_res_inode(काष्ठा ocfs2_lock_res *lockres)
अणु
	BUG_ON(!ocfs2_is_inode_lock(lockres));

	वापस (काष्ठा inode *) lockres->l_priv;
पूर्ण

अटल अंतरभूत काष्ठा ocfs2_dentry_lock *ocfs2_lock_res_dl(काष्ठा ocfs2_lock_res *lockres)
अणु
	BUG_ON(lockres->l_type != OCFS2_LOCK_TYPE_DENTRY);

	वापस (काष्ठा ocfs2_dentry_lock *)lockres->l_priv;
पूर्ण

अटल अंतरभूत काष्ठा ocfs2_mem_dqinfo *ocfs2_lock_res_qinfo(काष्ठा ocfs2_lock_res *lockres)
अणु
	BUG_ON(lockres->l_type != OCFS2_LOCK_TYPE_QINFO);

	वापस (काष्ठा ocfs2_mem_dqinfo *)lockres->l_priv;
पूर्ण

अटल अंतरभूत काष्ठा ocfs2_refcount_tree *
ocfs2_lock_res_refcount_tree(काष्ठा ocfs2_lock_res *res)
अणु
	वापस container_of(res, काष्ठा ocfs2_refcount_tree, rf_lockres);
पूर्ण

अटल अंतरभूत काष्ठा ocfs2_super *ocfs2_get_lockres_osb(काष्ठा ocfs2_lock_res *lockres)
अणु
	अगर (lockres->l_ops->get_osb)
		वापस lockres->l_ops->get_osb(lockres);

	वापस (काष्ठा ocfs2_super *)lockres->l_priv;
पूर्ण

अटल पूर्णांक ocfs2_lock_create(काष्ठा ocfs2_super *osb,
			     काष्ठा ocfs2_lock_res *lockres,
			     पूर्णांक level,
			     u32 dlm_flags);
अटल अंतरभूत पूर्णांक ocfs2_may_जारी_on_blocked_lock(काष्ठा ocfs2_lock_res *lockres,
						     पूर्णांक wanted);
अटल व्योम __ocfs2_cluster_unlock(काष्ठा ocfs2_super *osb,
				   काष्ठा ocfs2_lock_res *lockres,
				   पूर्णांक level, अचिन्हित दीर्घ caller_ip);
अटल अंतरभूत व्योम ocfs2_cluster_unlock(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_lock_res *lockres,
					पूर्णांक level)
अणु
	__ocfs2_cluster_unlock(osb, lockres, level, _RET_IP_);
पूर्ण

अटल अंतरभूत व्योम ocfs2_generic_handle_करोwnconvert_action(काष्ठा ocfs2_lock_res *lockres);
अटल अंतरभूत व्योम ocfs2_generic_handle_convert_action(काष्ठा ocfs2_lock_res *lockres);
अटल अंतरभूत व्योम ocfs2_generic_handle_attach_action(काष्ठा ocfs2_lock_res *lockres);
अटल पूर्णांक ocfs2_generic_handle_bast(काष्ठा ocfs2_lock_res *lockres, पूर्णांक level);
अटल व्योम ocfs2_schedule_blocked_lock(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_lock_res *lockres);
अटल अंतरभूत व्योम ocfs2_recover_from_dlm_error(काष्ठा ocfs2_lock_res *lockres,
						पूर्णांक convert);
#घोषणा ocfs2_log_dlm_error(_func, _err, _lockres) करो अणु					\
	अगर ((_lockres)->l_type != OCFS2_LOCK_TYPE_DENTRY)				\
		mlog(ML_ERROR, "DLM error %d while calling %s on resource %s\n",	\
		     _err, _func, _lockres->l_name);					\
	अन्यथा										\
		mlog(ML_ERROR, "DLM error %d while calling %s on resource %.*s%08x\n",	\
		     _err, _func, OCFS2_DENTRY_LOCK_INO_START - 1, (_lockres)->l_name,	\
		     (अचिन्हित पूर्णांक)ocfs2_get_dentry_lock_ino(_lockres));		\
पूर्ण जबतक (0)
अटल पूर्णांक ocfs2_करोwnconvert_thपढ़ो(व्योम *arg);
अटल व्योम ocfs2_करोwnconvert_on_unlock(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_lock_res *lockres);
अटल पूर्णांक ocfs2_inode_lock_update(काष्ठा inode *inode,
				  काष्ठा buffer_head **bh);
अटल व्योम ocfs2_drop_osb_locks(काष्ठा ocfs2_super *osb);
अटल अंतरभूत पूर्णांक ocfs2_highest_compat_lock_level(पूर्णांक level);
अटल अचिन्हित पूर्णांक ocfs2_prepare_करोwnconvert(काष्ठा ocfs2_lock_res *lockres,
					      पूर्णांक new_level);
अटल पूर्णांक ocfs2_करोwnconvert_lock(काष्ठा ocfs2_super *osb,
				  काष्ठा ocfs2_lock_res *lockres,
				  पूर्णांक new_level,
				  पूर्णांक lvb,
				  अचिन्हित पूर्णांक generation);
अटल पूर्णांक ocfs2_prepare_cancel_convert(काष्ठा ocfs2_super *osb,
				        काष्ठा ocfs2_lock_res *lockres);
अटल पूर्णांक ocfs2_cancel_convert(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_lock_res *lockres);


अटल व्योम ocfs2_build_lock_name(क्रमागत ocfs2_lock_type type,
				  u64 blkno,
				  u32 generation,
				  अक्षर *name)
अणु
	पूर्णांक len;

	BUG_ON(type >= OCFS2_NUM_LOCK_TYPES);

	len = snम_लिखो(name, OCFS2_LOCK_ID_MAX_LEN, "%c%s%016llx%08x",
		       ocfs2_lock_type_अक्षर(type), OCFS2_LOCK_ID_PAD,
		       (दीर्घ दीर्घ)blkno, generation);

	BUG_ON(len != (OCFS2_LOCK_ID_MAX_LEN - 1));

	mlog(0, "built lock resource with name: %s\n", name);
पूर्ण

अटल DEFINE_SPINLOCK(ocfs2_dlm_tracking_lock);

अटल व्योम ocfs2_add_lockres_tracking(काष्ठा ocfs2_lock_res *res,
				       काष्ठा ocfs2_dlm_debug *dlm_debug)
अणु
	mlog(0, "Add tracking for lockres %s\n", res->l_name);

	spin_lock(&ocfs2_dlm_tracking_lock);
	list_add(&res->l_debug_list, &dlm_debug->d_lockres_tracking);
	spin_unlock(&ocfs2_dlm_tracking_lock);
पूर्ण

अटल व्योम ocfs2_हटाओ_lockres_tracking(काष्ठा ocfs2_lock_res *res)
अणु
	spin_lock(&ocfs2_dlm_tracking_lock);
	अगर (!list_empty(&res->l_debug_list))
		list_del_init(&res->l_debug_list);
	spin_unlock(&ocfs2_dlm_tracking_lock);
पूर्ण

#अगर_घोषित CONFIG_OCFS2_FS_STATS
अटल व्योम ocfs2_init_lock_stats(काष्ठा ocfs2_lock_res *res)
अणु
	res->l_lock_refresh = 0;
	res->l_lock_रुको = 0;
	स_रखो(&res->l_lock_prmode, 0, माप(काष्ठा ocfs2_lock_stats));
	स_रखो(&res->l_lock_exmode, 0, माप(काष्ठा ocfs2_lock_stats));
पूर्ण

अटल व्योम ocfs2_update_lock_stats(काष्ठा ocfs2_lock_res *res, पूर्णांक level,
				    काष्ठा ocfs2_mask_रुकोer *mw, पूर्णांक ret)
अणु
	u32 usec;
	kसमय_प्रकार kt;
	काष्ठा ocfs2_lock_stats *stats;

	अगर (level == LKM_PRMODE)
		stats = &res->l_lock_prmode;
	अन्यथा अगर (level == LKM_EXMODE)
		stats = &res->l_lock_exmode;
	अन्यथा
		वापस;

	kt = kसमय_sub(kसमय_get(), mw->mw_lock_start);
	usec = kसमय_प्रकारo_us(kt);

	stats->ls_माला_लो++;
	stats->ls_total += kसमय_प्रकारo_ns(kt);
	/* overflow */
	अगर (unlikely(stats->ls_माला_लो == 0)) अणु
		stats->ls_माला_लो++;
		stats->ls_total = kसमय_प्रकारo_ns(kt);
	पूर्ण

	अगर (stats->ls_max < usec)
		stats->ls_max = usec;

	अगर (ret)
		stats->ls_fail++;

	stats->ls_last = kसमय_प्रकारo_us(kसमय_get_real());
पूर्ण

अटल अंतरभूत व्योम ocfs2_track_lock_refresh(काष्ठा ocfs2_lock_res *lockres)
अणु
	lockres->l_lock_refresh++;
पूर्ण

अटल अंतरभूत व्योम ocfs2_track_lock_रुको(काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा ocfs2_mask_रुकोer *mw;

	अगर (list_empty(&lockres->l_mask_रुकोers)) अणु
		lockres->l_lock_रुको = 0;
		वापस;
	पूर्ण

	mw = list_first_entry(&lockres->l_mask_रुकोers,
				काष्ठा ocfs2_mask_रुकोer, mw_item);
	lockres->l_lock_रुको =
			kसमय_प्रकारo_us(kसमय_mono_to_real(mw->mw_lock_start));
पूर्ण

अटल अंतरभूत व्योम ocfs2_init_start_समय(काष्ठा ocfs2_mask_रुकोer *mw)
अणु
	mw->mw_lock_start = kसमय_get();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ocfs2_init_lock_stats(काष्ठा ocfs2_lock_res *res)
अणु
पूर्ण
अटल अंतरभूत व्योम ocfs2_update_lock_stats(काष्ठा ocfs2_lock_res *res,
			   पूर्णांक level, काष्ठा ocfs2_mask_रुकोer *mw, पूर्णांक ret)
अणु
पूर्ण
अटल अंतरभूत व्योम ocfs2_track_lock_refresh(काष्ठा ocfs2_lock_res *lockres)
अणु
पूर्ण
अटल अंतरभूत व्योम ocfs2_track_lock_रुको(काष्ठा ocfs2_lock_res *lockres)
अणु
पूर्ण
अटल अंतरभूत व्योम ocfs2_init_start_समय(काष्ठा ocfs2_mask_रुकोer *mw)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम ocfs2_lock_res_init_common(काष्ठा ocfs2_super *osb,
				       काष्ठा ocfs2_lock_res *res,
				       क्रमागत ocfs2_lock_type type,
				       काष्ठा ocfs2_lock_res_ops *ops,
				       व्योम *priv)
अणु
	res->l_type          = type;
	res->l_ops           = ops;
	res->l_priv          = priv;

	res->l_level         = DLM_LOCK_IV;
	res->l_requested     = DLM_LOCK_IV;
	res->l_blocking      = DLM_LOCK_IV;
	res->l_action        = OCFS2_AST_INVALID;
	res->l_unlock_action = OCFS2_UNLOCK_INVALID;

	res->l_flags         = OCFS2_LOCK_INITIALIZED;

	ocfs2_add_lockres_tracking(res, osb->osb_dlm_debug);

	ocfs2_init_lock_stats(res);
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	अगर (type != OCFS2_LOCK_TYPE_OPEN)
		lockdep_init_map(&res->l_lockdep_map, ocfs2_lock_type_strings[type],
				 &lockdep_keys[type], 0);
	अन्यथा
		res->l_lockdep_map.key = शून्य;
#पूर्ण_अगर
पूर्ण

व्योम ocfs2_lock_res_init_once(काष्ठा ocfs2_lock_res *res)
अणु
	/* This also clears out the lock status block */
	स_रखो(res, 0, माप(काष्ठा ocfs2_lock_res));
	spin_lock_init(&res->l_lock);
	init_रुकोqueue_head(&res->l_event);
	INIT_LIST_HEAD(&res->l_blocked_list);
	INIT_LIST_HEAD(&res->l_mask_रुकोers);
	INIT_LIST_HEAD(&res->l_holders);
पूर्ण

व्योम ocfs2_inode_lock_res_init(काष्ठा ocfs2_lock_res *res,
			       क्रमागत ocfs2_lock_type type,
			       अचिन्हित पूर्णांक generation,
			       काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_lock_res_ops *ops;

	चयन(type) अणु
		हाल OCFS2_LOCK_TYPE_RW:
			ops = &ocfs2_inode_rw_lops;
			अवरोध;
		हाल OCFS2_LOCK_TYPE_META:
			ops = &ocfs2_inode_inode_lops;
			अवरोध;
		हाल OCFS2_LOCK_TYPE_OPEN:
			ops = &ocfs2_inode_खोलो_lops;
			अवरोध;
		शेष:
			mlog_bug_on_msg(1, "type: %d\n", type);
			ops = शून्य; /* thanks, gcc */
			अवरोध;
	पूर्ण

	ocfs2_build_lock_name(type, OCFS2_I(inode)->ip_blkno,
			      generation, res->l_name);
	ocfs2_lock_res_init_common(OCFS2_SB(inode->i_sb), res, type, ops, inode);
पूर्ण

अटल काष्ठा ocfs2_super *ocfs2_get_inode_osb(काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा inode *inode = ocfs2_lock_res_inode(lockres);

	वापस OCFS2_SB(inode->i_sb);
पूर्ण

अटल काष्ठा ocfs2_super *ocfs2_get_qinfo_osb(काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा ocfs2_mem_dqinfo *info = lockres->l_priv;

	वापस OCFS2_SB(info->dqi_gi.dqi_sb);
पूर्ण

अटल काष्ठा ocfs2_super *ocfs2_get_file_osb(काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा ocfs2_file_निजी *fp = lockres->l_priv;

	वापस OCFS2_SB(fp->fp_file->f_mapping->host->i_sb);
पूर्ण

अटल __u64 ocfs2_get_dentry_lock_ino(काष्ठा ocfs2_lock_res *lockres)
अणु
	__be64 inode_blkno_be;

	स_नकल(&inode_blkno_be, &lockres->l_name[OCFS2_DENTRY_LOCK_INO_START],
	       माप(__be64));

	वापस be64_to_cpu(inode_blkno_be);
पूर्ण

अटल काष्ठा ocfs2_super *ocfs2_get_dentry_osb(काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा ocfs2_dentry_lock *dl = lockres->l_priv;

	वापस OCFS2_SB(dl->dl_inode->i_sb);
पूर्ण

व्योम ocfs2_dentry_lock_res_init(काष्ठा ocfs2_dentry_lock *dl,
				u64 parent, काष्ठा inode *inode)
अणु
	पूर्णांक len;
	u64 inode_blkno = OCFS2_I(inode)->ip_blkno;
	__be64 inode_blkno_be = cpu_to_be64(inode_blkno);
	काष्ठा ocfs2_lock_res *lockres = &dl->dl_lockres;

	ocfs2_lock_res_init_once(lockres);

	/*
	 * Unक्रमtunately, the standard lock naming scheme won't work
	 * here because we have two 16 byte values to use. Instead,
	 * we'll stuff the inode number as a binary value. We still
	 * want error prपूर्णांकs to show something without garbling the
	 * display, so drop a null byte in there beक्रमe the inode
	 * number. A future version of OCFS2 will likely use all
	 * binary lock names. The stringअगरied names have been a
	 * tremenकरोus aid in debugging, but now that the debugfs
	 * पूर्णांकerface exists, we can mangle things there अगर need be.
	 *
	 * NOTE: We also drop the standard "pad" value (the total lock
	 * name size stays the same though - the last part is all
	 * zeros due to the स_रखो in ocfs2_lock_res_init_once()
	 */
	len = snम_लिखो(lockres->l_name, OCFS2_DENTRY_LOCK_INO_START,
		       "%c%016llx",
		       ocfs2_lock_type_अक्षर(OCFS2_LOCK_TYPE_DENTRY),
		       (दीर्घ दीर्घ)parent);

	BUG_ON(len != (OCFS2_DENTRY_LOCK_INO_START - 1));

	स_नकल(&lockres->l_name[OCFS2_DENTRY_LOCK_INO_START], &inode_blkno_be,
	       माप(__be64));

	ocfs2_lock_res_init_common(OCFS2_SB(inode->i_sb), lockres,
				   OCFS2_LOCK_TYPE_DENTRY, &ocfs2_dentry_lops,
				   dl);
पूर्ण

अटल व्योम ocfs2_super_lock_res_init(काष्ठा ocfs2_lock_res *res,
				      काष्ठा ocfs2_super *osb)
अणु
	/* Superblock lockres करोesn't come from a slab so we call init
	 * once on it manually.  */
	ocfs2_lock_res_init_once(res);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_SUPER, OCFS2_SUPER_BLOCK_BLKNO,
			      0, res->l_name);
	ocfs2_lock_res_init_common(osb, res, OCFS2_LOCK_TYPE_SUPER,
				   &ocfs2_super_lops, osb);
पूर्ण

अटल व्योम ocfs2_नाम_lock_res_init(काष्ठा ocfs2_lock_res *res,
				       काष्ठा ocfs2_super *osb)
अणु
	/* Rename lockres करोesn't come from a slab so we call init
	 * once on it manually.  */
	ocfs2_lock_res_init_once(res);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_RENAME, 0, 0, res->l_name);
	ocfs2_lock_res_init_common(osb, res, OCFS2_LOCK_TYPE_RENAME,
				   &ocfs2_नाम_lops, osb);
पूर्ण

अटल व्योम ocfs2_nfs_sync_lock_res_init(काष्ठा ocfs2_lock_res *res,
					 काष्ठा ocfs2_super *osb)
अणु
	/* nfs_sync lockres करोesn't come from a slab so we call init
	 * once on it manually.  */
	ocfs2_lock_res_init_once(res);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_NFS_SYNC, 0, 0, res->l_name);
	ocfs2_lock_res_init_common(osb, res, OCFS2_LOCK_TYPE_NFS_SYNC,
				   &ocfs2_nfs_sync_lops, osb);
पूर्ण

अटल व्योम ocfs2_nfs_sync_lock_init(काष्ठा ocfs2_super *osb)
अणु
	ocfs2_nfs_sync_lock_res_init(&osb->osb_nfs_sync_lockres, osb);
	init_rwsem(&osb->nfs_sync_rwlock);
पूर्ण

व्योम ocfs2_trim_fs_lock_res_init(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_trim_fs_lockres;

	/* Only one trimfs thपढ़ो are allowed to work at the same समय. */
	mutex_lock(&osb->obs_trim_fs_mutex);

	ocfs2_lock_res_init_once(lockres);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_TRIM_FS, 0, 0, lockres->l_name);
	ocfs2_lock_res_init_common(osb, lockres, OCFS2_LOCK_TYPE_TRIM_FS,
				   &ocfs2_trim_fs_lops, osb);
पूर्ण

व्योम ocfs2_trim_fs_lock_res_uninit(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_trim_fs_lockres;

	ocfs2_simple_drop_lockres(osb, lockres);
	ocfs2_lock_res_मुक्त(lockres);

	mutex_unlock(&osb->obs_trim_fs_mutex);
पूर्ण

अटल व्योम ocfs2_orphan_scan_lock_res_init(काष्ठा ocfs2_lock_res *res,
					    काष्ठा ocfs2_super *osb)
अणु
	ocfs2_lock_res_init_once(res);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_ORPHAN_SCAN, 0, 0, res->l_name);
	ocfs2_lock_res_init_common(osb, res, OCFS2_LOCK_TYPE_ORPHAN_SCAN,
				   &ocfs2_orphan_scan_lops, osb);
पूर्ण

व्योम ocfs2_file_lock_res_init(काष्ठा ocfs2_lock_res *lockres,
			      काष्ठा ocfs2_file_निजी *fp)
अणु
	काष्ठा inode *inode = fp->fp_file->f_mapping->host;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	ocfs2_lock_res_init_once(lockres);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_FLOCK, oi->ip_blkno,
			      inode->i_generation, lockres->l_name);
	ocfs2_lock_res_init_common(OCFS2_SB(inode->i_sb), lockres,
				   OCFS2_LOCK_TYPE_FLOCK, &ocfs2_flock_lops,
				   fp);
	lockres->l_flags |= OCFS2_LOCK_NOCACHE;
पूर्ण

व्योम ocfs2_qinfo_lock_res_init(काष्ठा ocfs2_lock_res *lockres,
			       काष्ठा ocfs2_mem_dqinfo *info)
अणु
	ocfs2_lock_res_init_once(lockres);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_QINFO, info->dqi_gi.dqi_type,
			      0, lockres->l_name);
	ocfs2_lock_res_init_common(OCFS2_SB(info->dqi_gi.dqi_sb), lockres,
				   OCFS2_LOCK_TYPE_QINFO, &ocfs2_qinfo_lops,
				   info);
पूर्ण

व्योम ocfs2_refcount_lock_res_init(काष्ठा ocfs2_lock_res *lockres,
				  काष्ठा ocfs2_super *osb, u64 ref_blkno,
				  अचिन्हित पूर्णांक generation)
अणु
	ocfs2_lock_res_init_once(lockres);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_REFCOUNT, ref_blkno,
			      generation, lockres->l_name);
	ocfs2_lock_res_init_common(osb, lockres, OCFS2_LOCK_TYPE_REFCOUNT,
				   &ocfs2_refcount_block_lops, osb);
पूर्ण

व्योम ocfs2_lock_res_मुक्त(काष्ठा ocfs2_lock_res *res)
अणु
	अगर (!(res->l_flags & OCFS2_LOCK_INITIALIZED))
		वापस;

	ocfs2_हटाओ_lockres_tracking(res);

	mlog_bug_on_msg(!list_empty(&res->l_blocked_list),
			"Lockres %s is on the blocked list\n",
			res->l_name);
	mlog_bug_on_msg(!list_empty(&res->l_mask_रुकोers),
			"Lockres %s has mask waiters pending\n",
			res->l_name);
	mlog_bug_on_msg(spin_is_locked(&res->l_lock),
			"Lockres %s is locked\n",
			res->l_name);
	mlog_bug_on_msg(res->l_ro_holders,
			"Lockres %s has %u ro holders\n",
			res->l_name, res->l_ro_holders);
	mlog_bug_on_msg(res->l_ex_holders,
			"Lockres %s has %u ex holders\n",
			res->l_name, res->l_ex_holders);

	/* Need to clear out the lock status block क्रम the dlm */
	स_रखो(&res->l_lksb, 0, माप(res->l_lksb));

	res->l_flags = 0UL;
पूर्ण

/*
 * Keep a list of processes who have पूर्णांकerest in a lockres.
 * Note: this is now only uesed क्रम check recursive cluster locking.
 */
अटल अंतरभूत व्योम ocfs2_add_holder(काष्ठा ocfs2_lock_res *lockres,
				   काष्ठा ocfs2_lock_holder *oh)
अणु
	INIT_LIST_HEAD(&oh->oh_list);
	oh->oh_owner_pid = get_pid(task_pid(current));

	spin_lock(&lockres->l_lock);
	list_add_tail(&oh->oh_list, &lockres->l_holders);
	spin_unlock(&lockres->l_lock);
पूर्ण

अटल काष्ठा ocfs2_lock_holder *
ocfs2_pid_holder(काष्ठा ocfs2_lock_res *lockres,
		काष्ठा pid *pid)
अणु
	काष्ठा ocfs2_lock_holder *oh;

	spin_lock(&lockres->l_lock);
	list_क्रम_each_entry(oh, &lockres->l_holders, oh_list) अणु
		अगर (oh->oh_owner_pid == pid) अणु
			spin_unlock(&lockres->l_lock);
			वापस oh;
		पूर्ण
	पूर्ण
	spin_unlock(&lockres->l_lock);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम ocfs2_हटाओ_holder(काष्ठा ocfs2_lock_res *lockres,
				       काष्ठा ocfs2_lock_holder *oh)
अणु
	spin_lock(&lockres->l_lock);
	list_del(&oh->oh_list);
	spin_unlock(&lockres->l_lock);

	put_pid(oh->oh_owner_pid);
पूर्ण


अटल अंतरभूत व्योम ocfs2_inc_holders(काष्ठा ocfs2_lock_res *lockres,
				     पूर्णांक level)
अणु
	BUG_ON(!lockres);

	चयन(level) अणु
	हाल DLM_LOCK_EX:
		lockres->l_ex_holders++;
		अवरोध;
	हाल DLM_LOCK_PR:
		lockres->l_ro_holders++;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ocfs2_dec_holders(काष्ठा ocfs2_lock_res *lockres,
				     पूर्णांक level)
अणु
	BUG_ON(!lockres);

	चयन(level) अणु
	हाल DLM_LOCK_EX:
		BUG_ON(!lockres->l_ex_holders);
		lockres->l_ex_holders--;
		अवरोध;
	हाल DLM_LOCK_PR:
		BUG_ON(!lockres->l_ro_holders);
		lockres->l_ro_holders--;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/* WARNING: This function lives in a world where the only three lock
 * levels are EX, PR, and NL. It *will* have to be adjusted when more
 * lock types are added. */
अटल अंतरभूत पूर्णांक ocfs2_highest_compat_lock_level(पूर्णांक level)
अणु
	पूर्णांक new_level = DLM_LOCK_EX;

	अगर (level == DLM_LOCK_EX)
		new_level = DLM_LOCK_NL;
	अन्यथा अगर (level == DLM_LOCK_PR)
		new_level = DLM_LOCK_PR;
	वापस new_level;
पूर्ण

अटल व्योम lockres_set_flags(काष्ठा ocfs2_lock_res *lockres,
			      अचिन्हित दीर्घ newflags)
अणु
	काष्ठा ocfs2_mask_रुकोer *mw, *पंचांगp;

 	निश्चित_spin_locked(&lockres->l_lock);

	lockres->l_flags = newflags;

	list_क्रम_each_entry_safe(mw, पंचांगp, &lockres->l_mask_रुकोers, mw_item) अणु
		अगर ((lockres->l_flags & mw->mw_mask) != mw->mw_goal)
			जारी;

		list_del_init(&mw->mw_item);
		mw->mw_status = 0;
		complete(&mw->mw_complete);
		ocfs2_track_lock_रुको(lockres);
	पूर्ण
पूर्ण
अटल व्योम lockres_or_flags(काष्ठा ocfs2_lock_res *lockres, अचिन्हित दीर्घ or)
अणु
	lockres_set_flags(lockres, lockres->l_flags | or);
पूर्ण
अटल व्योम lockres_clear_flags(काष्ठा ocfs2_lock_res *lockres,
				अचिन्हित दीर्घ clear)
अणु
	lockres_set_flags(lockres, lockres->l_flags & ~clear);
पूर्ण

अटल अंतरभूत व्योम ocfs2_generic_handle_करोwnconvert_action(काष्ठा ocfs2_lock_res *lockres)
अणु
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_BUSY));
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_ATTACHED));
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_BLOCKED));
	BUG_ON(lockres->l_blocking <= DLM_LOCK_NL);

	lockres->l_level = lockres->l_requested;
	अगर (lockres->l_level <=
	    ocfs2_highest_compat_lock_level(lockres->l_blocking)) अणु
		lockres->l_blocking = DLM_LOCK_NL;
		lockres_clear_flags(lockres, OCFS2_LOCK_BLOCKED);
	पूर्ण
	lockres_clear_flags(lockres, OCFS2_LOCK_BUSY);
पूर्ण

अटल अंतरभूत व्योम ocfs2_generic_handle_convert_action(काष्ठा ocfs2_lock_res *lockres)
अणु
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_BUSY));
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_ATTACHED));

	/* Convert from RO to EX करोesn't really need anything as our
	 * inक्रमmation is alपढ़ोy up to data. Convert from NL to
	 * *anything* however should mark ourselves as needing an
	 * update */
	अगर (lockres->l_level == DLM_LOCK_NL &&
	    lockres->l_ops->flags & LOCK_TYPE_REQUIRES_REFRESH)
		lockres_or_flags(lockres, OCFS2_LOCK_NEEDS_REFRESH);

	lockres->l_level = lockres->l_requested;

	/*
	 * We set the OCFS2_LOCK_UPCONVERT_FINISHING flag beक्रमe clearing
	 * the OCFS2_LOCK_BUSY flag to prevent the dc thपढ़ो from
	 * करोwnconverting the lock beक्रमe the upconvert has fully completed.
	 * Do not prevent the dc thपढ़ो from करोwnconverting अगर NONBLOCK lock
	 * had alपढ़ोy वापसed.
	 */
	अगर (!(lockres->l_flags & OCFS2_LOCK_NONBLOCK_FINISHED))
		lockres_or_flags(lockres, OCFS2_LOCK_UPCONVERT_FINISHING);
	अन्यथा
		lockres_clear_flags(lockres, OCFS2_LOCK_NONBLOCK_FINISHED);

	lockres_clear_flags(lockres, OCFS2_LOCK_BUSY);
पूर्ण

अटल अंतरभूत व्योम ocfs2_generic_handle_attach_action(काष्ठा ocfs2_lock_res *lockres)
अणु
	BUG_ON((!(lockres->l_flags & OCFS2_LOCK_BUSY)));
	BUG_ON(lockres->l_flags & OCFS2_LOCK_ATTACHED);

	अगर (lockres->l_requested > DLM_LOCK_NL &&
	    !(lockres->l_flags & OCFS2_LOCK_LOCAL) &&
	    lockres->l_ops->flags & LOCK_TYPE_REQUIRES_REFRESH)
		lockres_or_flags(lockres, OCFS2_LOCK_NEEDS_REFRESH);

	lockres->l_level = lockres->l_requested;
	lockres_or_flags(lockres, OCFS2_LOCK_ATTACHED);
	lockres_clear_flags(lockres, OCFS2_LOCK_BUSY);
पूर्ण

अटल पूर्णांक ocfs2_generic_handle_bast(काष्ठा ocfs2_lock_res *lockres,
				     पूर्णांक level)
अणु
	पूर्णांक needs_करोwnconvert = 0;

	निश्चित_spin_locked(&lockres->l_lock);

	अगर (level > lockres->l_blocking) अणु
		/* only schedule a करोwnconvert अगर we haven't alपढ़ोy scheduled
		 * one that goes low enough to satisfy the level we're
		 * blocking.  this also catches the हाल where we get
		 * duplicate BASTs */
		अगर (ocfs2_highest_compat_lock_level(level) <
		    ocfs2_highest_compat_lock_level(lockres->l_blocking))
			needs_करोwnconvert = 1;

		lockres->l_blocking = level;
	पूर्ण

	mlog(ML_BASTS, "lockres %s, block %d, level %d, l_block %d, dwn %d\n",
	     lockres->l_name, level, lockres->l_level, lockres->l_blocking,
	     needs_करोwnconvert);

	अगर (needs_करोwnconvert)
		lockres_or_flags(lockres, OCFS2_LOCK_BLOCKED);
	mlog(0, "needs_downconvert = %d\n", needs_करोwnconvert);
	वापस needs_करोwnconvert;
पूर्ण

/*
 * OCFS2_LOCK_PENDING and l_pending_gen.
 *
 * Why करोes OCFS2_LOCK_PENDING exist?  To बंद a race between setting
 * OCFS2_LOCK_BUSY and calling ocfs2_dlm_lock().  See ocfs2_unblock_lock()
 * क्रम more details on the race.
 *
 * OCFS2_LOCK_PENDING बंदs the race quite nicely.  However, it पूर्णांकroduces
 * a race on itself.  In o2dlm, we can get the ast beक्रमe ocfs2_dlm_lock()
 * वापसs.  The ast clears OCFS2_LOCK_BUSY, and must thereक्रमe clear
 * OCFS2_LOCK_PENDING at the same समय.  When ocfs2_dlm_lock() वापसs,
 * the caller is going to try to clear PENDING again.  If nothing अन्यथा is
 * happening, __lockres_clear_pending() sees PENDING is unset and करोes
 * nothing.
 *
 * But what अगर another path (eg करोwnconvert thपढ़ो) has just started a
 * new locking action?  The other path has re-set PENDING.  Our path
 * cannot clear PENDING, because that will re-खोलो the original race
 * winकरोw.
 *
 * [Example]
 *
 * ocfs2_meta_lock()
 *  ocfs2_cluster_lock()
 *   set BUSY
 *   set PENDING
 *   drop l_lock
 *   ocfs2_dlm_lock()
 *    ocfs2_locking_ast()		ocfs2_करोwnconvert_thपढ़ो()
 *     clear PENDING			 ocfs2_unblock_lock()
 *					  take_l_lock
 *					  !BUSY
 *					  ocfs2_prepare_करोwnconvert()
 *					   set BUSY
 *					   set PENDING
 *					  drop l_lock
 *   take l_lock
 *   clear PENDING
 *   drop l_lock
 *			<winकरोw>
 *					  ocfs2_dlm_lock()
 *
 * So as you can see, we now have a winकरोw where l_lock is not held,
 * PENDING is not set, and ocfs2_dlm_lock() has not been called.
 *
 * The core problem is that ocfs2_cluster_lock() has cleared the PENDING
 * set by ocfs2_prepare_करोwnconvert().  That wasn't nice.
 *
 * To solve this we पूर्णांकroduce l_pending_gen.  A call to
 * lockres_clear_pending() will only करो so when it is passed a generation
 * number that matches the lockres.  lockres_set_pending() will वापस the
 * current generation number.  When ocfs2_cluster_lock() goes to clear
 * PENDING, it passes the generation it got from set_pending().  In our
 * example above, the generation numbers will *not* match.  Thus,
 * ocfs2_cluster_lock() will not clear the PENDING set by
 * ocfs2_prepare_करोwnconvert().
 */

/* Unlocked version क्रम ocfs2_locking_ast() */
अटल व्योम __lockres_clear_pending(काष्ठा ocfs2_lock_res *lockres,
				    अचिन्हित पूर्णांक generation,
				    काष्ठा ocfs2_super *osb)
अणु
	निश्चित_spin_locked(&lockres->l_lock);

	/*
	 * The ast and locking functions can race us here.  The winner
	 * will clear pending, the loser will not.
	 */
	अगर (!(lockres->l_flags & OCFS2_LOCK_PENDING) ||
	    (lockres->l_pending_gen != generation))
		वापस;

	lockres_clear_flags(lockres, OCFS2_LOCK_PENDING);
	lockres->l_pending_gen++;

	/*
	 * The करोwnconvert thपढ़ो may have skipped us because we
	 * were PENDING.  Wake it up.
	 */
	अगर (lockres->l_flags & OCFS2_LOCK_BLOCKED)
		ocfs2_wake_करोwnconvert_thपढ़ो(osb);
पूर्ण

/* Locked version क्रम callers of ocfs2_dlm_lock() */
अटल व्योम lockres_clear_pending(काष्ठा ocfs2_lock_res *lockres,
				  अचिन्हित पूर्णांक generation,
				  काष्ठा ocfs2_super *osb)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lockres->l_lock, flags);
	__lockres_clear_pending(lockres, generation, osb);
	spin_unlock_irqrestore(&lockres->l_lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक lockres_set_pending(काष्ठा ocfs2_lock_res *lockres)
अणु
	निश्चित_spin_locked(&lockres->l_lock);
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_BUSY));

	lockres_or_flags(lockres, OCFS2_LOCK_PENDING);

	वापस lockres->l_pending_gen;
पूर्ण

अटल व्योम ocfs2_blocking_ast(काष्ठा ocfs2_dlm_lksb *lksb, पूर्णांक level)
अणु
	काष्ठा ocfs2_lock_res *lockres = ocfs2_lksb_to_lock_res(lksb);
	काष्ठा ocfs2_super *osb = ocfs2_get_lockres_osb(lockres);
	पूर्णांक needs_करोwnconvert;
	अचिन्हित दीर्घ flags;

	BUG_ON(level <= DLM_LOCK_NL);

	mlog(ML_BASTS, "BAST fired for lockres %s, blocking %d, level %d, "
	     "type %s\n", lockres->l_name, level, lockres->l_level,
	     ocfs2_lock_type_string(lockres->l_type));

	/*
	 * We can skip the bast क्रम locks which करोn't enable caching -
	 * they'll be dropped at the earliest possible समय anyway.
	 */
	अगर (lockres->l_flags & OCFS2_LOCK_NOCACHE)
		वापस;

	spin_lock_irqsave(&lockres->l_lock, flags);
	needs_करोwnconvert = ocfs2_generic_handle_bast(lockres, level);
	अगर (needs_करोwnconvert)
		ocfs2_schedule_blocked_lock(osb, lockres);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	wake_up(&lockres->l_event);

	ocfs2_wake_करोwnconvert_thपढ़ो(osb);
पूर्ण

अटल व्योम ocfs2_locking_ast(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	काष्ठा ocfs2_lock_res *lockres = ocfs2_lksb_to_lock_res(lksb);
	काष्ठा ocfs2_super *osb = ocfs2_get_lockres_osb(lockres);
	अचिन्हित दीर्घ flags;
	पूर्णांक status;

	spin_lock_irqsave(&lockres->l_lock, flags);

	status = ocfs2_dlm_lock_status(&lockres->l_lksb);

	अगर (status == -EAGAIN) अणु
		lockres_clear_flags(lockres, OCFS2_LOCK_BUSY);
		जाओ out;
	पूर्ण

	अगर (status) अणु
		mlog(ML_ERROR, "lockres %s: lksb status value of %d!\n",
		     lockres->l_name, status);
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		वापस;
	पूर्ण

	mlog(ML_BASTS, "AST fired for lockres %s, action %d, unlock %d, "
	     "level %d => %d\n", lockres->l_name, lockres->l_action,
	     lockres->l_unlock_action, lockres->l_level, lockres->l_requested);

	चयन(lockres->l_action) अणु
	हाल OCFS2_AST_ATTACH:
		ocfs2_generic_handle_attach_action(lockres);
		lockres_clear_flags(lockres, OCFS2_LOCK_LOCAL);
		अवरोध;
	हाल OCFS2_AST_CONVERT:
		ocfs2_generic_handle_convert_action(lockres);
		अवरोध;
	हाल OCFS2_AST_DOWNCONVERT:
		ocfs2_generic_handle_करोwnconvert_action(lockres);
		अवरोध;
	शेष:
		mlog(ML_ERROR, "lockres %s: AST fired with invalid action: %u, "
		     "flags 0x%lx, unlock: %u\n",
		     lockres->l_name, lockres->l_action, lockres->l_flags,
		     lockres->l_unlock_action);
		BUG();
	पूर्ण
out:
	/* set it to something invalid so अगर we get called again we
	 * can catch it. */
	lockres->l_action = OCFS2_AST_INVALID;

	/* Did we try to cancel this lock?  Clear that state */
	अगर (lockres->l_unlock_action == OCFS2_UNLOCK_CANCEL_CONVERT)
		lockres->l_unlock_action = OCFS2_UNLOCK_INVALID;

	/*
	 * We may have beaten the locking functions here.  We certainly
	 * know that dlm_lock() has been called :-)
	 * Because we can't have two lock calls in flight at once, we
	 * can use lockres->l_pending_gen.
	 */
	__lockres_clear_pending(lockres, lockres->l_pending_gen,  osb);

	wake_up(&lockres->l_event);
	spin_unlock_irqrestore(&lockres->l_lock, flags);
पूर्ण

अटल व्योम ocfs2_unlock_ast(काष्ठा ocfs2_dlm_lksb *lksb, पूर्णांक error)
अणु
	काष्ठा ocfs2_lock_res *lockres = ocfs2_lksb_to_lock_res(lksb);
	अचिन्हित दीर्घ flags;

	mlog(ML_BASTS, "UNLOCK AST fired for lockres %s, action = %d\n",
	     lockres->l_name, lockres->l_unlock_action);

	spin_lock_irqsave(&lockres->l_lock, flags);
	अगर (error) अणु
		mlog(ML_ERROR, "Dlm passes error %d for lock %s, "
		     "unlock_action %d\n", error, lockres->l_name,
		     lockres->l_unlock_action);
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		वापस;
	पूर्ण

	चयन(lockres->l_unlock_action) अणु
	हाल OCFS2_UNLOCK_CANCEL_CONVERT:
		mlog(0, "Cancel convert success for %s\n", lockres->l_name);
		lockres->l_action = OCFS2_AST_INVALID;
		/* Downconvert thपढ़ो may have requeued this lock, we
		 * need to wake it. */
		अगर (lockres->l_flags & OCFS2_LOCK_BLOCKED)
			ocfs2_wake_करोwnconvert_thपढ़ो(ocfs2_get_lockres_osb(lockres));
		अवरोध;
	हाल OCFS2_UNLOCK_DROP_LOCK:
		lockres->l_level = DLM_LOCK_IV;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	lockres_clear_flags(lockres, OCFS2_LOCK_BUSY);
	lockres->l_unlock_action = OCFS2_UNLOCK_INVALID;
	wake_up(&lockres->l_event);
	spin_unlock_irqrestore(&lockres->l_lock, flags);
पूर्ण

/*
 * This is the fileप्रणाली locking protocol.  It provides the lock handling
 * hooks क्रम the underlying DLM.  It has a maximum version number.
 * The version number allows पूर्णांकeroperability with प्रणालीs running at
 * the same major number and an equal or smaller minor number.
 *
 * Whenever the fileप्रणाली करोes new things with locks (adds or हटाओs a
 * lock, orders them dअगरferently, करोes dअगरferent things underneath a lock),
 * the version must be changed.  The protocol is negotiated when joining
 * the dlm करोमुख्य.  A node may join the करोमुख्य अगर its major version is
 * identical to all other nodes and its minor version is greater than
 * or equal to all other nodes.  When its minor version is greater than
 * the other nodes, it will run at the minor version specअगरied by the
 * other nodes.
 *
 * If a locking change is made that will not be compatible with older
 * versions, the major number must be increased and the minor version set
 * to zero.  If a change merely adds a behavior that can be disabled when
 * speaking to older versions, the minor version must be increased.  If a
 * change adds a fully backwards compatible change (eg, LVB changes that
 * are just ignored by older versions), the version करोes not need to be
 * updated.
 */
अटल काष्ठा ocfs2_locking_protocol lproto = अणु
	.lp_max_version = अणु
		.pv_major = OCFS2_LOCKING_PROTOCOL_MAJOR,
		.pv_minor = OCFS2_LOCKING_PROTOCOL_MINOR,
	पूर्ण,
	.lp_lock_ast		= ocfs2_locking_ast,
	.lp_blocking_ast	= ocfs2_blocking_ast,
	.lp_unlock_ast		= ocfs2_unlock_ast,
पूर्ण;

व्योम ocfs2_set_locking_protocol(व्योम)
अणु
	ocfs2_stack_glue_set_max_proto_version(&lproto.lp_max_version);
पूर्ण

अटल अंतरभूत व्योम ocfs2_recover_from_dlm_error(काष्ठा ocfs2_lock_res *lockres,
						पूर्णांक convert)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lockres->l_lock, flags);
	lockres_clear_flags(lockres, OCFS2_LOCK_BUSY);
	lockres_clear_flags(lockres, OCFS2_LOCK_UPCONVERT_FINISHING);
	अगर (convert)
		lockres->l_action = OCFS2_AST_INVALID;
	अन्यथा
		lockres->l_unlock_action = OCFS2_UNLOCK_INVALID;
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	wake_up(&lockres->l_event);
पूर्ण

/* Note: If we detect another process working on the lock (i.e.,
 * OCFS2_LOCK_BUSY), we'll bail out returning 0. It's up to the caller
 * to करो the right thing in that हाल.
 */
अटल पूर्णांक ocfs2_lock_create(काष्ठा ocfs2_super *osb,
			     काष्ठा ocfs2_lock_res *lockres,
			     पूर्णांक level,
			     u32 dlm_flags)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक gen;

	mlog(0, "lock %s, level = %d, flags = %u\n", lockres->l_name, level,
	     dlm_flags);

	spin_lock_irqsave(&lockres->l_lock, flags);
	अगर ((lockres->l_flags & OCFS2_LOCK_ATTACHED) ||
	    (lockres->l_flags & OCFS2_LOCK_BUSY)) अणु
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		जाओ bail;
	पूर्ण

	lockres->l_action = OCFS2_AST_ATTACH;
	lockres->l_requested = level;
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);
	gen = lockres_set_pending(lockres);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	ret = ocfs2_dlm_lock(osb->cconn,
			     level,
			     &lockres->l_lksb,
			     dlm_flags,
			     lockres->l_name,
			     OCFS2_LOCK_ID_MAX_LEN - 1);
	lockres_clear_pending(lockres, gen, osb);
	अगर (ret) अणु
		ocfs2_log_dlm_error("ocfs2_dlm_lock", ret, lockres);
		ocfs2_recover_from_dlm_error(lockres, 1);
	पूर्ण

	mlog(0, "lock %s, return from ocfs2_dlm_lock\n", lockres->l_name);

bail:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_check_रुको_flag(काष्ठा ocfs2_lock_res *lockres,
					पूर्णांक flag)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&lockres->l_lock, flags);
	ret = lockres->l_flags & flag;
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ocfs2_रुको_on_busy_lock(काष्ठा ocfs2_lock_res *lockres)

अणु
	रुको_event(lockres->l_event,
		   !ocfs2_check_रुको_flag(lockres, OCFS2_LOCK_BUSY));
पूर्ण

अटल अंतरभूत व्योम ocfs2_रुको_on_refreshing_lock(काष्ठा ocfs2_lock_res *lockres)

अणु
	रुको_event(lockres->l_event,
		   !ocfs2_check_रुको_flag(lockres, OCFS2_LOCK_REFRESHING));
पूर्ण

/* predict what lock level we'll be dropping करोwn to on behalf
 * of another node, and वापस true अगर the currently wanted
 * level will be compatible with it. */
अटल अंतरभूत पूर्णांक ocfs2_may_जारी_on_blocked_lock(काष्ठा ocfs2_lock_res *lockres,
						     पूर्णांक wanted)
अणु
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_BLOCKED));

	वापस wanted <= ocfs2_highest_compat_lock_level(lockres->l_blocking);
पूर्ण

अटल व्योम ocfs2_init_mask_रुकोer(काष्ठा ocfs2_mask_रुकोer *mw)
अणु
	INIT_LIST_HEAD(&mw->mw_item);
	init_completion(&mw->mw_complete);
	ocfs2_init_start_समय(mw);
पूर्ण

अटल पूर्णांक ocfs2_रुको_क्रम_mask(काष्ठा ocfs2_mask_रुकोer *mw)
अणु
	रुको_क्रम_completion(&mw->mw_complete);
	/* Re-arm the completion in हाल we want to रुको on it again */
	reinit_completion(&mw->mw_complete);
	वापस mw->mw_status;
पूर्ण

अटल व्योम lockres_add_mask_रुकोer(काष्ठा ocfs2_lock_res *lockres,
				    काष्ठा ocfs2_mask_रुकोer *mw,
				    अचिन्हित दीर्घ mask,
				    अचिन्हित दीर्घ goal)
अणु
	BUG_ON(!list_empty(&mw->mw_item));

	निश्चित_spin_locked(&lockres->l_lock);

	list_add_tail(&mw->mw_item, &lockres->l_mask_रुकोers);
	mw->mw_mask = mask;
	mw->mw_goal = goal;
	ocfs2_track_lock_रुको(lockres);
पूर्ण

/* वापसs 0 अगर the mw that was हटाओd was alपढ़ोy satisfied, -EBUSY
 * अगर the mask still hadn't reached its goal */
अटल पूर्णांक __lockres_हटाओ_mask_रुकोer(काष्ठा ocfs2_lock_res *lockres,
				      काष्ठा ocfs2_mask_रुकोer *mw)
अणु
	पूर्णांक ret = 0;

	निश्चित_spin_locked(&lockres->l_lock);
	अगर (!list_empty(&mw->mw_item)) अणु
		अगर ((lockres->l_flags & mw->mw_mask) != mw->mw_goal)
			ret = -EBUSY;

		list_del_init(&mw->mw_item);
		init_completion(&mw->mw_complete);
		ocfs2_track_lock_रुको(lockres);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lockres_हटाओ_mask_रुकोer(काष्ठा ocfs2_lock_res *lockres,
				      काष्ठा ocfs2_mask_रुकोer *mw)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&lockres->l_lock, flags);
	ret = __lockres_हटाओ_mask_रुकोer(lockres, mw);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	वापस ret;

पूर्ण

अटल पूर्णांक ocfs2_रुको_क्रम_mask_पूर्णांकerruptible(काष्ठा ocfs2_mask_रुकोer *mw,
					     काष्ठा ocfs2_lock_res *lockres)
अणु
	पूर्णांक ret;

	ret = रुको_क्रम_completion_पूर्णांकerruptible(&mw->mw_complete);
	अगर (ret)
		lockres_हटाओ_mask_रुकोer(lockres, mw);
	अन्यथा
		ret = mw->mw_status;
	/* Re-arm the completion in हाल we want to रुको on it again */
	reinit_completion(&mw->mw_complete);
	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_cluster_lock(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_lock_res *lockres,
				पूर्णांक level,
				u32 lkm_flags,
				पूर्णांक arg_flags,
				पूर्णांक l_subclass,
				अचिन्हित दीर्घ caller_ip)
अणु
	काष्ठा ocfs2_mask_रुकोer mw;
	पूर्णांक रुको, catch_संकेतs = !(osb->s_mount_opt & OCFS2_MOUNT_NOINTR);
	पूर्णांक ret = 0; /* gcc करोesn't realize रुको = 1 guarantees ret is set */
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक gen;
	पूर्णांक noqueue_attempted = 0;
	पूर्णांक dlm_locked = 0;
	पूर्णांक kick_dc = 0;

	अगर (!(lockres->l_flags & OCFS2_LOCK_INITIALIZED)) अणु
		mlog_त्रुटि_सं(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	ocfs2_init_mask_रुकोer(&mw);

	अगर (lockres->l_ops->flags & LOCK_TYPE_USES_LVB)
		lkm_flags |= DLM_LKF_VALBLK;

again:
	रुको = 0;

	spin_lock_irqsave(&lockres->l_lock, flags);

	अगर (catch_संकेतs && संकेत_pending(current)) अणु
		ret = -ERESTARTSYS;
		जाओ unlock;
	पूर्ण

	mlog_bug_on_msg(lockres->l_flags & OCFS2_LOCK_FREEING,
			"Cluster lock called on freeing lockres %s! flags "
			"0x%lx\n", lockres->l_name, lockres->l_flags);

	/* We only compare against the currently granted level
	 * here. If the lock is blocked रुकोing on a करोwnconvert,
	 * we'll get caught below. */
	अगर (lockres->l_flags & OCFS2_LOCK_BUSY &&
	    level > lockres->l_level) अणु
		/* is someone sitting in dlm_lock? If so, रुको on
		 * them. */
		lockres_add_mask_रुकोer(lockres, &mw, OCFS2_LOCK_BUSY, 0);
		रुको = 1;
		जाओ unlock;
	पूर्ण

	अगर (lockres->l_flags & OCFS2_LOCK_UPCONVERT_FINISHING) अणु
		/*
		 * We've upconverted. If the lock now has a level we can
		 * work with, we take it. If, however, the lock is not at the
		 * required level, we go thru the full cycle. One way this could
		 * happen is अगर a process requesting an upconvert to PR is
		 * बंदly followed by another requesting upconvert to an EX.
		 * If the process requesting EX lands here, we want it to
		 * जारी attempting to upconvert and let the process
		 * requesting PR take the lock.
		 * If multiple processes request upconvert to PR, the first one
		 * here will take the lock. The others will have to go thru the
		 * OCFS2_LOCK_BLOCKED check to ensure that there is no pending
		 * करोwnconvert request.
		 */
		अगर (level <= lockres->l_level)
			जाओ update_holders;
	पूर्ण

	अगर (lockres->l_flags & OCFS2_LOCK_BLOCKED &&
	    !ocfs2_may_जारी_on_blocked_lock(lockres, level)) अणु
		/* is the lock is currently blocked on behalf of
		 * another node */
		lockres_add_mask_रुकोer(lockres, &mw, OCFS2_LOCK_BLOCKED, 0);
		रुको = 1;
		जाओ unlock;
	पूर्ण

	अगर (level > lockres->l_level) अणु
		अगर (noqueue_attempted > 0) अणु
			ret = -EAGAIN;
			जाओ unlock;
		पूर्ण
		अगर (lkm_flags & DLM_LKF_NOQUEUE)
			noqueue_attempted = 1;

		अगर (lockres->l_action != OCFS2_AST_INVALID)
			mlog(ML_ERROR, "lockres %s has action %u pending\n",
			     lockres->l_name, lockres->l_action);

		अगर (!(lockres->l_flags & OCFS2_LOCK_ATTACHED)) अणु
			lockres->l_action = OCFS2_AST_ATTACH;
			lkm_flags &= ~DLM_LKF_CONVERT;
		पूर्ण अन्यथा अणु
			lockres->l_action = OCFS2_AST_CONVERT;
			lkm_flags |= DLM_LKF_CONVERT;
		पूर्ण

		lockres->l_requested = level;
		lockres_or_flags(lockres, OCFS2_LOCK_BUSY);
		gen = lockres_set_pending(lockres);
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		BUG_ON(level == DLM_LOCK_IV);
		BUG_ON(level == DLM_LOCK_NL);

		mlog(ML_BASTS, "lockres %s, convert from %d to %d\n",
		     lockres->l_name, lockres->l_level, level);

		/* call dlm_lock to upgrade lock now */
		ret = ocfs2_dlm_lock(osb->cconn,
				     level,
				     &lockres->l_lksb,
				     lkm_flags,
				     lockres->l_name,
				     OCFS2_LOCK_ID_MAX_LEN - 1);
		lockres_clear_pending(lockres, gen, osb);
		अगर (ret) अणु
			अगर (!(lkm_flags & DLM_LKF_NOQUEUE) ||
			    (ret != -EAGAIN)) अणु
				ocfs2_log_dlm_error("ocfs2_dlm_lock",
						    ret, lockres);
			पूर्ण
			ocfs2_recover_from_dlm_error(lockres, 1);
			जाओ out;
		पूर्ण
		dlm_locked = 1;

		mlog(0, "lock %s, successful return from ocfs2_dlm_lock\n",
		     lockres->l_name);

		/* At this poपूर्णांक we've gone inside the dlm and need to
		 * complete our work regardless. */
		catch_संकेतs = 0;

		/* रुको क्रम busy to clear and carry on */
		जाओ again;
	पूर्ण

update_holders:
	/* Ok, अगर we get here then we're good to go. */
	ocfs2_inc_holders(lockres, level);

	ret = 0;
unlock:
	lockres_clear_flags(lockres, OCFS2_LOCK_UPCONVERT_FINISHING);

	/* ocfs2_unblock_lock reques on seeing OCFS2_LOCK_UPCONVERT_FINISHING */
	kick_dc = (lockres->l_flags & OCFS2_LOCK_BLOCKED);

	spin_unlock_irqrestore(&lockres->l_lock, flags);
	अगर (kick_dc)
		ocfs2_wake_करोwnconvert_thपढ़ो(osb);
out:
	/*
	 * This is helping work around a lock inversion between the page lock
	 * and dlm locks.  One path holds the page lock जबतक calling aops
	 * which block acquiring dlm locks.  The voting thपढ़ो holds dlm
	 * locks जबतक acquiring page locks जबतक करोwn converting data locks.
	 * This block is helping an aop path notice the inversion and back
	 * off to unlock its page lock beक्रमe trying the dlm lock again.
	 */
	अगर (रुको && arg_flags & OCFS2_LOCK_NONBLOCK &&
	    mw.mw_mask & (OCFS2_LOCK_BUSY|OCFS2_LOCK_BLOCKED)) अणु
		रुको = 0;
		spin_lock_irqsave(&lockres->l_lock, flags);
		अगर (__lockres_हटाओ_mask_रुकोer(lockres, &mw)) अणु
			अगर (dlm_locked)
				lockres_or_flags(lockres,
					OCFS2_LOCK_NONBLOCK_FINISHED);
			spin_unlock_irqrestore(&lockres->l_lock, flags);
			ret = -EAGAIN;
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&lockres->l_lock, flags);
			जाओ again;
		पूर्ण
	पूर्ण
	अगर (रुको) अणु
		ret = ocfs2_रुको_क्रम_mask(&mw);
		अगर (ret == 0)
			जाओ again;
		mlog_त्रुटि_सं(ret);
	पूर्ण
	ocfs2_update_lock_stats(lockres, level, &mw, ret);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	अगर (!ret && lockres->l_lockdep_map.key != शून्य) अणु
		अगर (level == DLM_LOCK_PR)
			rwsem_acquire_पढ़ो(&lockres->l_lockdep_map, l_subclass,
				!!(arg_flags & OCFS2_META_LOCK_NOQUEUE),
				caller_ip);
		अन्यथा
			rwsem_acquire(&lockres->l_lockdep_map, l_subclass,
				!!(arg_flags & OCFS2_META_LOCK_NOQUEUE),
				caller_ip);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_cluster_lock(काष्ठा ocfs2_super *osb,
				     काष्ठा ocfs2_lock_res *lockres,
				     पूर्णांक level,
				     u32 lkm_flags,
				     पूर्णांक arg_flags)
अणु
	वापस __ocfs2_cluster_lock(osb, lockres, level, lkm_flags, arg_flags,
				    0, _RET_IP_);
पूर्ण


अटल व्योम __ocfs2_cluster_unlock(काष्ठा ocfs2_super *osb,
				   काष्ठा ocfs2_lock_res *lockres,
				   पूर्णांक level,
				   अचिन्हित दीर्घ caller_ip)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lockres->l_lock, flags);
	ocfs2_dec_holders(lockres, level);
	ocfs2_करोwnconvert_on_unlock(osb, lockres);
	spin_unlock_irqrestore(&lockres->l_lock, flags);
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	अगर (lockres->l_lockdep_map.key != शून्य)
		rwsem_release(&lockres->l_lockdep_map, caller_ip);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ocfs2_create_new_lock(काष्ठा ocfs2_super *osb,
				 काष्ठा ocfs2_lock_res *lockres,
				 पूर्णांक ex,
				 पूर्णांक local)
अणु
	पूर्णांक level =  ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	अचिन्हित दीर्घ flags;
	u32 lkm_flags = local ? DLM_LKF_LOCAL : 0;

	spin_lock_irqsave(&lockres->l_lock, flags);
	BUG_ON(lockres->l_flags & OCFS2_LOCK_ATTACHED);
	lockres_or_flags(lockres, OCFS2_LOCK_LOCAL);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	वापस ocfs2_lock_create(osb, lockres, level, lkm_flags);
पूर्ण

/* Grants us an EX lock on the data and metadata resources, skipping
 * the normal cluster directory lookup. Use this ONLY on newly created
 * inodes which other nodes can't possibly see, and which haven't been
 * hashed in the inode hash yet. This can give us a good perक्रमmance
 * increase as it'll skip the network broadcast normally associated
 * with creating a new lock resource. */
पूर्णांक ocfs2_create_new_inode_locks(काष्ठा inode *inode)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	BUG_ON(!ocfs2_inode_is_new(inode));

	mlog(0, "Inode %llu\n", (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

	/* NOTE: That we करोn't increment any of the holder counts, nor
	 * करो we add anything to a journal handle. Since this is
	 * supposed to be a new inode which the cluster करोesn't know
	 * about yet, there is no need to.  As far as the LVB handling
	 * is concerned, this is basically like acquiring an EX lock
	 * on a resource which has an invalid one -- we'll set it
	 * valid when we release the EX. */

	ret = ocfs2_create_new_lock(osb, &OCFS2_I(inode)->ip_rw_lockres, 1, 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण

	/*
	 * We करोn't want to use DLM_LKF_LOCAL on a meta data lock as they
	 * करोn't use a generation in their lock names.
	 */
	ret = ocfs2_create_new_lock(osb, &OCFS2_I(inode)->ip_inode_lockres, 1, 0);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण

	ret = ocfs2_create_new_lock(osb, &OCFS2_I(inode)->ip_खोलो_lockres, 0, 0);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

bail:
	वापस ret;
पूर्ण

पूर्णांक ocfs2_rw_lock(काष्ठा inode *inode, पूर्णांक ग_लिखो)
अणु
	पूर्णांक status, level;
	काष्ठा ocfs2_lock_res *lockres;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog(0, "inode %llu take %s RW lock\n",
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
	     ग_लिखो ? "EXMODE" : "PRMODE");

	अगर (ocfs2_mount_local(osb))
		वापस 0;

	lockres = &OCFS2_I(inode)->ip_rw_lockres;

	level = ग_लिखो ? DLM_LOCK_EX : DLM_LOCK_PR;

	status = ocfs2_cluster_lock(osb, lockres, level, 0, 0);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

पूर्णांक ocfs2_try_rw_lock(काष्ठा inode *inode, पूर्णांक ग_लिखो)
अणु
	पूर्णांक status, level;
	काष्ठा ocfs2_lock_res *lockres;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog(0, "inode %llu try to take %s RW lock\n",
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
	     ग_लिखो ? "EXMODE" : "PRMODE");

	अगर (ocfs2_mount_local(osb))
		वापस 0;

	lockres = &OCFS2_I(inode)->ip_rw_lockres;

	level = ग_लिखो ? DLM_LOCK_EX : DLM_LOCK_PR;

	status = ocfs2_cluster_lock(osb, lockres, level, DLM_LKF_NOQUEUE, 0);
	वापस status;
पूर्ण

व्योम ocfs2_rw_unlock(काष्ठा inode *inode, पूर्णांक ग_लिखो)
अणु
	पूर्णांक level = ग_लिखो ? DLM_LOCK_EX : DLM_LOCK_PR;
	काष्ठा ocfs2_lock_res *lockres = &OCFS2_I(inode)->ip_rw_lockres;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog(0, "inode %llu drop %s RW lock\n",
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
	     ग_लिखो ? "EXMODE" : "PRMODE");

	अगर (!ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres, level);
पूर्ण

/*
 * ocfs2_खोलो_lock always get PR mode lock.
 */
पूर्णांक ocfs2_खोलो_lock(काष्ठा inode *inode)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_lock_res *lockres;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog(0, "inode %llu take PRMODE open lock\n",
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_mount_local(osb))
		जाओ out;

	lockres = &OCFS2_I(inode)->ip_खोलो_lockres;

	status = ocfs2_cluster_lock(osb, lockres, DLM_LOCK_PR, 0, 0);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

out:
	वापस status;
पूर्ण

पूर्णांक ocfs2_try_खोलो_lock(काष्ठा inode *inode, पूर्णांक ग_लिखो)
अणु
	पूर्णांक status = 0, level;
	काष्ठा ocfs2_lock_res *lockres;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog(0, "inode %llu try to take %s open lock\n",
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
	     ग_लिखो ? "EXMODE" : "PRMODE");

	अगर (ocfs2_is_hard_पढ़ोonly(osb)) अणु
		अगर (ग_लिखो)
			status = -EROFS;
		जाओ out;
	पूर्ण

	अगर (ocfs2_mount_local(osb))
		जाओ out;

	lockres = &OCFS2_I(inode)->ip_खोलो_lockres;

	level = ग_लिखो ? DLM_LOCK_EX : DLM_LOCK_PR;

	/*
	 * The file प्रणाली may alपढ़ोy holding a PRMODE/EXMODE खोलो lock.
	 * Since we pass DLM_LKF_NOQUEUE, the request won't block रुकोing on
	 * other nodes and the -EAGAIN will indicate to the caller that
	 * this inode is still in use.
	 */
	status = ocfs2_cluster_lock(osb, lockres, level, DLM_LKF_NOQUEUE, 0);

out:
	वापस status;
पूर्ण

/*
 * ocfs2_खोलो_unlock unlock PR and EX mode खोलो locks.
 */
व्योम ocfs2_खोलो_unlock(काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_lock_res *lockres = &OCFS2_I(inode)->ip_खोलो_lockres;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog(0, "inode %llu drop open lock\n",
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

	अगर (ocfs2_mount_local(osb))
		जाओ out;

	अगर(lockres->l_ro_holders)
		ocfs2_cluster_unlock(osb, lockres, DLM_LOCK_PR);
	अगर(lockres->l_ex_holders)
		ocfs2_cluster_unlock(osb, lockres, DLM_LOCK_EX);

out:
	वापस;
पूर्ण

अटल पूर्णांक ocfs2_flock_handle_संकेत(काष्ठा ocfs2_lock_res *lockres,
				     पूर्णांक level)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = ocfs2_get_lockres_osb(lockres);
	अचिन्हित दीर्घ flags;
	काष्ठा ocfs2_mask_रुकोer mw;

	ocfs2_init_mask_रुकोer(&mw);

retry_cancel:
	spin_lock_irqsave(&lockres->l_lock, flags);
	अगर (lockres->l_flags & OCFS2_LOCK_BUSY) अणु
		ret = ocfs2_prepare_cancel_convert(osb, lockres);
		अगर (ret) अणु
			spin_unlock_irqrestore(&lockres->l_lock, flags);
			ret = ocfs2_cancel_convert(osb, lockres);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
			जाओ retry_cancel;
		पूर्ण
		lockres_add_mask_रुकोer(lockres, &mw, OCFS2_LOCK_BUSY, 0);
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		ocfs2_रुको_क्रम_mask(&mw);
		जाओ retry_cancel;
	पूर्ण

	ret = -ERESTARTSYS;
	/*
	 * We may still have gotten the lock, in which हाल there's no
	 * poपूर्णांक to restarting the syscall.
	 */
	अगर (lockres->l_level == level)
		ret = 0;

	mlog(0, "Cancel returning %d. flags: 0x%lx, level: %d, act: %d\n", ret,
	     lockres->l_flags, lockres->l_level, lockres->l_action);

	spin_unlock_irqrestore(&lockres->l_lock, flags);

out:
	वापस ret;
पूर्ण

/*
 * ocfs2_file_lock() and ocfs2_file_unlock() map to a single pair of
 * flock() calls. The locking approach this requires is sufficiently
 * dअगरferent from all other cluster lock types that we implement a
 * separate path to the "low-level" dlm calls. In particular:
 *
 * - No optimization of lock levels is करोne - we take at exactly
 *   what's been requested.
 *
 * - No lock caching is employed. We immediately करोwnconvert to
 *   no-lock at unlock समय. This also means flock locks never go on
 *   the blocking list).
 *
 * - Since userspace can trivially deadlock itself with flock, we make
 *   sure to allow cancellation of a misbehaving applications flock()
 *   request.
 *
 * - Access to any flock lockres करोesn't require concurrency, so we
 *   can simplअगरy the code by requiring the caller to guarantee
 *   serialization of dlmglue flock calls.
 */
पूर्णांक ocfs2_file_lock(काष्ठा file *file, पूर्णांक ex, पूर्णांक trylock)
अणु
	पूर्णांक ret, level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	अचिन्हित पूर्णांक lkm_flags = trylock ? DLM_LKF_NOQUEUE : 0;
	अचिन्हित दीर्घ flags;
	काष्ठा ocfs2_file_निजी *fp = file->निजी_data;
	काष्ठा ocfs2_lock_res *lockres = &fp->fp_flock;
	काष्ठा ocfs2_super *osb = OCFS2_SB(file->f_mapping->host->i_sb);
	काष्ठा ocfs2_mask_रुकोer mw;

	ocfs2_init_mask_रुकोer(&mw);

	अगर ((lockres->l_flags & OCFS2_LOCK_BUSY) ||
	    (lockres->l_level > DLM_LOCK_NL)) अणु
		mlog(ML_ERROR,
		     "File lock \"%s\" has busy or locked state: flags: 0x%lx, "
		     "level: %u\n", lockres->l_name, lockres->l_flags,
		     lockres->l_level);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&lockres->l_lock, flags);
	अगर (!(lockres->l_flags & OCFS2_LOCK_ATTACHED)) अणु
		lockres_add_mask_रुकोer(lockres, &mw, OCFS2_LOCK_BUSY, 0);
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		/*
		 * Get the lock at NLMODE to start - that way we
		 * can cancel the upconvert request अगर need be.
		 */
		ret = ocfs2_lock_create(osb, lockres, DLM_LOCK_NL, 0);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_रुको_क्रम_mask(&mw);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		spin_lock_irqsave(&lockres->l_lock, flags);
	पूर्ण

	lockres->l_action = OCFS2_AST_CONVERT;
	lkm_flags |= DLM_LKF_CONVERT;
	lockres->l_requested = level;
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);

	lockres_add_mask_रुकोer(lockres, &mw, OCFS2_LOCK_BUSY, 0);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	ret = ocfs2_dlm_lock(osb->cconn, level, &lockres->l_lksb, lkm_flags,
			     lockres->l_name, OCFS2_LOCK_ID_MAX_LEN - 1);
	अगर (ret) अणु
		अगर (!trylock || (ret != -EAGAIN)) अणु
			ocfs2_log_dlm_error("ocfs2_dlm_lock", ret, lockres);
			ret = -EINVAL;
		पूर्ण

		ocfs2_recover_from_dlm_error(lockres, 1);
		lockres_हटाओ_mask_रुकोer(lockres, &mw);
		जाओ out;
	पूर्ण

	ret = ocfs2_रुको_क्रम_mask_पूर्णांकerruptible(&mw, lockres);
	अगर (ret == -ERESTARTSYS) अणु
		/*
		 * Userspace can cause deadlock itself with
		 * flock(). Current behavior locally is to allow the
		 * deadlock, but पात the प्रणाली call अगर a संकेत is
		 * received. We follow this example, otherwise a
		 * poorly written program could sit in kernel until
		 * reboot.
		 *
		 * Handling this is a bit more complicated क्रम Ocfs2
		 * though. We can't निकास this function with an
		 * outstanding lock request, so a cancel convert is
		 * required. We पूर्णांकentionally overग_लिखो 'ret' - अगर the
		 * cancel fails and the lock was granted, it's easier
		 * to just bubble success back up to the user.
		 */
		ret = ocfs2_flock_handle_संकेत(lockres, level);
	पूर्ण अन्यथा अगर (!ret && (level > lockres->l_level)) अणु
		/* Trylock failed asynchronously */
		BUG_ON(!trylock);
		ret = -EAGAIN;
	पूर्ण

out:

	mlog(0, "Lock: \"%s\" ex: %d, trylock: %d, returns: %d\n",
	     lockres->l_name, ex, trylock, ret);
	वापस ret;
पूर्ण

व्योम ocfs2_file_unlock(काष्ठा file *file)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक gen;
	अचिन्हित दीर्घ flags;
	काष्ठा ocfs2_file_निजी *fp = file->निजी_data;
	काष्ठा ocfs2_lock_res *lockres = &fp->fp_flock;
	काष्ठा ocfs2_super *osb = OCFS2_SB(file->f_mapping->host->i_sb);
	काष्ठा ocfs2_mask_रुकोer mw;

	ocfs2_init_mask_रुकोer(&mw);

	अगर (!(lockres->l_flags & OCFS2_LOCK_ATTACHED))
		वापस;

	अगर (lockres->l_level == DLM_LOCK_NL)
		वापस;

	mlog(0, "Unlock: \"%s\" flags: 0x%lx, level: %d, act: %d\n",
	     lockres->l_name, lockres->l_flags, lockres->l_level,
	     lockres->l_action);

	spin_lock_irqsave(&lockres->l_lock, flags);
	/*
	 * Fake a blocking ast क्रम the करोwnconvert code.
	 */
	lockres_or_flags(lockres, OCFS2_LOCK_BLOCKED);
	lockres->l_blocking = DLM_LOCK_EX;

	gen = ocfs2_prepare_करोwnconvert(lockres, DLM_LOCK_NL);
	lockres_add_mask_रुकोer(lockres, &mw, OCFS2_LOCK_BUSY, 0);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	ret = ocfs2_करोwnconvert_lock(osb, lockres, DLM_LOCK_NL, 0, gen);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस;
	पूर्ण

	ret = ocfs2_रुको_क्रम_mask(&mw);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
पूर्ण

अटल व्योम ocfs2_करोwnconvert_on_unlock(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_lock_res *lockres)
अणु
	पूर्णांक kick = 0;

	/* If we know that another node is रुकोing on our lock, kick
	 * the करोwnconvert thपढ़ो * pre-emptively when we reach a release
	 * condition. */
	अगर (lockres->l_flags & OCFS2_LOCK_BLOCKED) अणु
		चयन(lockres->l_blocking) अणु
		हाल DLM_LOCK_EX:
			अगर (!lockres->l_ex_holders && !lockres->l_ro_holders)
				kick = 1;
			अवरोध;
		हाल DLM_LOCK_PR:
			अगर (!lockres->l_ex_holders)
				kick = 1;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण

	अगर (kick)
		ocfs2_wake_करोwnconvert_thपढ़ो(osb);
पूर्ण

#घोषणा OCFS2_SEC_BITS   34
#घोषणा OCFS2_SEC_SHIFT  (64 - OCFS2_SEC_BITS)
#घोषणा OCFS2_NSEC_MASK  ((1ULL << OCFS2_SEC_SHIFT) - 1)

/* LVB only has room क्रम 64 bits of समय here so we pack it क्रम
 * now. */
अटल u64 ocfs2_pack_बारpec(काष्ठा बारpec64 *spec)
अणु
	u64 res;
	u64 sec = clamp_t(समय64_t, spec->tv_sec, 0, 0x3ffffffffull);
	u32 nsec = spec->tv_nsec;

	res = (sec << OCFS2_SEC_SHIFT) | (nsec & OCFS2_NSEC_MASK);

	वापस res;
पूर्ण

/* Call this with the lockres locked. I am reasonably sure we करोn't
 * need ip_lock in this function as anyone who would be changing those
 * values is supposed to be blocked in ocfs2_inode_lock right now. */
अटल व्योम __ocfs2_stuff_meta_lvb(काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_lock_res *lockres = &oi->ip_inode_lockres;
	काष्ठा ocfs2_meta_lvb *lvb;

	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);

	/*
	 * Invalidate the LVB of a deleted inode - this way other
	 * nodes are क्रमced to go to disk and discover the new inode
	 * status.
	 */
	अगर (oi->ip_flags & OCFS2_INODE_DELETED) अणु
		lvb->lvb_version = 0;
		जाओ out;
	पूर्ण

	lvb->lvb_version   = OCFS2_LVB_VERSION;
	lvb->lvb_isize	   = cpu_to_be64(i_size_पढ़ो(inode));
	lvb->lvb_iclusters = cpu_to_be32(oi->ip_clusters);
	lvb->lvb_iuid      = cpu_to_be32(i_uid_पढ़ो(inode));
	lvb->lvb_igid      = cpu_to_be32(i_gid_पढ़ो(inode));
	lvb->lvb_imode     = cpu_to_be16(inode->i_mode);
	lvb->lvb_inlink    = cpu_to_be16(inode->i_nlink);
	lvb->lvb_iaसमय_packed  =
		cpu_to_be64(ocfs2_pack_बारpec(&inode->i_aसमय));
	lvb->lvb_iस_समय_packed =
		cpu_to_be64(ocfs2_pack_बारpec(&inode->i_स_समय));
	lvb->lvb_imसमय_packed =
		cpu_to_be64(ocfs2_pack_बारpec(&inode->i_mसमय));
	lvb->lvb_iattr    = cpu_to_be32(oi->ip_attr);
	lvb->lvb_idynfeatures = cpu_to_be16(oi->ip_dyn_features);
	lvb->lvb_igeneration = cpu_to_be32(inode->i_generation);

out:
	mlog_meta_lvb(0, lockres);
पूर्ण

अटल व्योम ocfs2_unpack_बारpec(काष्ठा बारpec64 *spec,
				  u64 packed_समय)
अणु
	spec->tv_sec = packed_समय >> OCFS2_SEC_SHIFT;
	spec->tv_nsec = packed_समय & OCFS2_NSEC_MASK;
पूर्ण

अटल पूर्णांक ocfs2_refresh_inode_from_lvb(काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_lock_res *lockres = &oi->ip_inode_lockres;
	काष्ठा ocfs2_meta_lvb *lvb;

	mlog_meta_lvb(0, lockres);

	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
	अगर (inode_wrong_type(inode, be16_to_cpu(lvb->lvb_imode)))
		वापस -ESTALE;

	/* We're safe here without the lockres lock... */
	spin_lock(&oi->ip_lock);
	oi->ip_clusters = be32_to_cpu(lvb->lvb_iclusters);
	i_size_ग_लिखो(inode, be64_to_cpu(lvb->lvb_isize));

	oi->ip_attr = be32_to_cpu(lvb->lvb_iattr);
	oi->ip_dyn_features = be16_to_cpu(lvb->lvb_idynfeatures);
	ocfs2_set_inode_flags(inode);

	/* fast-symlinks are a special हाल */
	अगर (S_ISLNK(inode->i_mode) && !oi->ip_clusters)
		inode->i_blocks = 0;
	अन्यथा
		inode->i_blocks = ocfs2_inode_sector_count(inode);

	i_uid_ग_लिखो(inode, be32_to_cpu(lvb->lvb_iuid));
	i_gid_ग_लिखो(inode, be32_to_cpu(lvb->lvb_igid));
	inode->i_mode    = be16_to_cpu(lvb->lvb_imode);
	set_nlink(inode, be16_to_cpu(lvb->lvb_inlink));
	ocfs2_unpack_बारpec(&inode->i_aसमय,
			      be64_to_cpu(lvb->lvb_iaसमय_packed));
	ocfs2_unpack_बारpec(&inode->i_mसमय,
			      be64_to_cpu(lvb->lvb_imसमय_packed));
	ocfs2_unpack_बारpec(&inode->i_स_समय,
			      be64_to_cpu(lvb->lvb_iस_समय_packed));
	spin_unlock(&oi->ip_lock);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_meta_lvb_is_trustable(काष्ठा inode *inode,
					      काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा ocfs2_meta_lvb *lvb = ocfs2_dlm_lvb(&lockres->l_lksb);

	अगर (ocfs2_dlm_lvb_valid(&lockres->l_lksb)
	    && lvb->lvb_version == OCFS2_LVB_VERSION
	    && be32_to_cpu(lvb->lvb_igeneration) == inode->i_generation)
		वापस 1;
	वापस 0;
पूर्ण

/* Determine whether a lock resource needs to be refreshed, and
 * arbitrate who माला_लो to refresh it.
 *
 *   0 means no refresh needed.
 *
 *   > 0 means you need to refresh this and you MUST call
 *   ocfs2_complete_lock_res_refresh afterwards. */
अटल पूर्णांक ocfs2_should_refresh_lock_res(काष्ठा ocfs2_lock_res *lockres)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक status = 0;

refresh_check:
	spin_lock_irqsave(&lockres->l_lock, flags);
	अगर (!(lockres->l_flags & OCFS2_LOCK_NEEDS_REFRESH)) अणु
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		जाओ bail;
	पूर्ण

	अगर (lockres->l_flags & OCFS2_LOCK_REFRESHING) अणु
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		ocfs2_रुको_on_refreshing_lock(lockres);
		जाओ refresh_check;
	पूर्ण

	/* Ok, I'll be the one to refresh this lock. */
	lockres_or_flags(lockres, OCFS2_LOCK_REFRESHING);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	status = 1;
bail:
	mlog(0, "status %d\n", status);
	वापस status;
पूर्ण

/* If status is non zero, I'll mark it as not being in refresh
 * anymroe, but i won't clear the needs refresh flag. */
अटल अंतरभूत व्योम ocfs2_complete_lock_res_refresh(काष्ठा ocfs2_lock_res *lockres,
						   पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lockres->l_lock, flags);
	lockres_clear_flags(lockres, OCFS2_LOCK_REFRESHING);
	अगर (!status)
		lockres_clear_flags(lockres, OCFS2_LOCK_NEEDS_REFRESH);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	wake_up(&lockres->l_event);
पूर्ण

/* may or may not वापस a bh अगर it went to disk. */
अटल पूर्णांक ocfs2_inode_lock_update(काष्ठा inode *inode,
				  काष्ठा buffer_head **bh)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_lock_res *lockres = &oi->ip_inode_lockres;
	काष्ठा ocfs2_dinode *fe;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (ocfs2_mount_local(osb))
		जाओ bail;

	spin_lock(&oi->ip_lock);
	अगर (oi->ip_flags & OCFS2_INODE_DELETED) अणु
		mlog(0, "Orphaned inode %llu was deleted while we "
		     "were waiting on a lock. ip_flags = 0x%x\n",
		     (अचिन्हित दीर्घ दीर्घ)oi->ip_blkno, oi->ip_flags);
		spin_unlock(&oi->ip_lock);
		status = -ENOENT;
		जाओ bail;
	पूर्ण
	spin_unlock(&oi->ip_lock);

	अगर (!ocfs2_should_refresh_lock_res(lockres))
		जाओ bail;

	/* This will discard any caching inक्रमmation we might have had
	 * क्रम the inode metadata. */
	ocfs2_metadata_cache_purge(INODE_CACHE(inode));

	ocfs2_extent_map_trunc(inode, 0);

	अगर (ocfs2_meta_lvb_is_trustable(inode, lockres)) अणु
		mlog(0, "Trusting LVB on inode %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);
		status = ocfs2_refresh_inode_from_lvb(inode);
		जाओ bail_refresh;
	पूर्ण अन्यथा अणु
		/* Boo, we have to go to disk. */
		/* पढ़ो bh, cast, ocfs2_refresh_inode */
		status = ocfs2_पढ़ो_inode_block(inode, bh);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail_refresh;
		पूर्ण
		fe = (काष्ठा ocfs2_dinode *) (*bh)->b_data;
		अगर (inode_wrong_type(inode, le16_to_cpu(fe->i_mode))) अणु
			status = -ESTALE;
			जाओ bail_refresh;
		पूर्ण

		/* This is a good chance to make sure we're not
		 * locking an invalid object.  ocfs2_पढ़ो_inode_block()
		 * alपढ़ोy checked that the inode block is sane.
		 *
		 * We bug on a stale inode here because we checked
		 * above whether it was wiped from disk. The wiping
		 * node provides a guarantee that we receive that
		 * message and can mark the inode beक्रमe dropping any
		 * locks associated with it. */
		mlog_bug_on_msg(inode->i_generation !=
				le32_to_cpu(fe->i_generation),
				"Invalid dinode %llu disk generation: %u "
				"inode->i_generation: %u\n",
				(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
				le32_to_cpu(fe->i_generation),
				inode->i_generation);
		mlog_bug_on_msg(le64_to_cpu(fe->i_dसमय) ||
				!(fe->i_flags & cpu_to_le32(OCFS2_VALID_FL)),
				"Stale dinode %llu dtime: %llu flags: 0x%x\n",
				(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
				(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_dसमय),
				le32_to_cpu(fe->i_flags));

		ocfs2_refresh_inode(inode, fe);
		ocfs2_track_lock_refresh(lockres);
	पूर्ण

	status = 0;
bail_refresh:
	ocfs2_complete_lock_res_refresh(lockres, status);
bail:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_assign_bh(काष्ठा inode *inode,
			   काष्ठा buffer_head **ret_bh,
			   काष्ठा buffer_head *passed_bh)
अणु
	पूर्णांक status;

	अगर (passed_bh) अणु
		/* Ok, the update went to disk क्रम us, use the
		 * वापसed bh. */
		*ret_bh = passed_bh;
		get_bh(*ret_bh);

		वापस 0;
	पूर्ण

	status = ocfs2_पढ़ो_inode_block(inode, ret_bh);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

/*
 * वापसs < 0 error अगर the callback will never be called, otherwise
 * the result of the lock will be communicated via the callback.
 */
पूर्णांक ocfs2_inode_lock_full_nested(काष्ठा inode *inode,
				 काष्ठा buffer_head **ret_bh,
				 पूर्णांक ex,
				 पूर्णांक arg_flags,
				 पूर्णांक subclass)
अणु
	पूर्णांक status, level, acquired;
	u32 dlm_flags;
	काष्ठा ocfs2_lock_res *lockres = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा buffer_head *local_bh = शून्य;

	mlog(0, "inode %llu, take %s META lock\n",
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
	     ex ? "EXMODE" : "PRMODE");

	status = 0;
	acquired = 0;
	/* We'll allow faking a पढ़ोonly metadata lock क्रम
	 * rodevices. */
	अगर (ocfs2_is_hard_पढ़ोonly(osb)) अणु
		अगर (ex)
			status = -EROFS;
		जाओ getbh;
	पूर्ण

	अगर ((arg_flags & OCFS2_META_LOCK_GETBH) ||
	    ocfs2_mount_local(osb))
		जाओ update;

	अगर (!(arg_flags & OCFS2_META_LOCK_RECOVERY))
		ocfs2_रुको_क्रम_recovery(osb);

	lockres = &OCFS2_I(inode)->ip_inode_lockres;
	level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	dlm_flags = 0;
	अगर (arg_flags & OCFS2_META_LOCK_NOQUEUE)
		dlm_flags |= DLM_LKF_NOQUEUE;

	status = __ocfs2_cluster_lock(osb, lockres, level, dlm_flags,
				      arg_flags, subclass, _RET_IP_);
	अगर (status < 0) अणु
		अगर (status != -EAGAIN)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* Notअगरy the error cleanup path to drop the cluster lock. */
	acquired = 1;

	/* We रुको twice because a node may have died जबतक we were in
	 * the lower dlm layers. The second समय though, we've
	 * committed to owning this lock so we करोn't allow संकेतs to
	 * पात the operation. */
	अगर (!(arg_flags & OCFS2_META_LOCK_RECOVERY))
		ocfs2_रुको_क्रम_recovery(osb);

update:
	/*
	 * We only see this flag अगर we're being called from
	 * ocfs2_पढ़ो_locked_inode(). It means we're locking an inode
	 * which hasn't been populated yet, so clear the refresh flag
	 * and let the caller handle it.
	 */
	अगर (inode->i_state & I_NEW) अणु
		status = 0;
		अगर (lockres)
			ocfs2_complete_lock_res_refresh(lockres, 0);
		जाओ bail;
	पूर्ण

	/* This is fun. The caller may want a bh back, or it may
	 * not. ocfs2_inode_lock_update definitely wants one in, but
	 * may or may not पढ़ो one, depending on what's in the
	 * LVB. The result of all of this is that we've *only* gone to
	 * disk अगर we have to, so the complनिकासy is worthजबतक. */
	status = ocfs2_inode_lock_update(inode, &local_bh);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
getbh:
	अगर (ret_bh) अणु
		status = ocfs2_assign_bh(inode, ret_bh, local_bh);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

bail:
	अगर (status < 0) अणु
		अगर (ret_bh && (*ret_bh)) अणु
			brअन्यथा(*ret_bh);
			*ret_bh = शून्य;
		पूर्ण
		अगर (acquired)
			ocfs2_inode_unlock(inode, ex);
	पूर्ण

	brअन्यथा(local_bh);
	वापस status;
पूर्ण

/*
 * This is working around a lock inversion between tasks acquiring DLM
 * locks जबतक holding a page lock and the करोwnconvert thपढ़ो which
 * blocks dlm lock acquiry जबतक acquiring page locks.
 *
 * ** These _with_page variantes are only पूर्णांकended to be called from aop
 * methods that hold page locks and वापस a very specअगरic *positive* error
 * code that aop methods pass up to the VFS -- test क्रम errors with != 0. **
 *
 * The DLM is called such that it वापसs -EAGAIN अगर it would have
 * blocked रुकोing क्रम the करोwnconvert thपढ़ो.  In that हाल we unlock
 * our page so the करोwnconvert thपढ़ो can make progress.  Once we've
 * करोne this we have to वापस AOP_TRUNCATED_PAGE so the aop method
 * that called us can bubble that back up पूर्णांकo the VFS who will then
 * immediately retry the aop call.
 */
पूर्णांक ocfs2_inode_lock_with_page(काष्ठा inode *inode,
			      काष्ठा buffer_head **ret_bh,
			      पूर्णांक ex,
			      काष्ठा page *page)
अणु
	पूर्णांक ret;

	ret = ocfs2_inode_lock_full(inode, ret_bh, ex, OCFS2_LOCK_NONBLOCK);
	अगर (ret == -EAGAIN) अणु
		unlock_page(page);
		/*
		 * If we can't get inode lock immediately, we should not वापस
		 * directly here, since this will lead to a softlockup problem.
		 * The method is to get a blocking lock and immediately unlock
		 * beक्रमe वापसing, this can aव्योम CPU resource waste due to
		 * lots of retries, and benefits fairness in getting lock.
		 */
		अगर (ocfs2_inode_lock(inode, ret_bh, ex) == 0)
			ocfs2_inode_unlock(inode, ex);
		ret = AOP_TRUNCATED_PAGE;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ocfs2_inode_lock_aसमय(काष्ठा inode *inode,
			  काष्ठा vfsmount *vfsmnt,
			  पूर्णांक *level, पूर्णांक रुको)
अणु
	पूर्णांक ret;

	अगर (रुको)
		ret = ocfs2_inode_lock(inode, शून्य, 0);
	अन्यथा
		ret = ocfs2_try_inode_lock(inode, शून्य, 0);

	अगर (ret < 0) अणु
		अगर (ret != -EAGAIN)
			mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	/*
	 * If we should update aसमय, we will get EX lock,
	 * otherwise we just get PR lock.
	 */
	अगर (ocfs2_should_update_aसमय(inode, vfsmnt)) अणु
		काष्ठा buffer_head *bh = शून्य;

		ocfs2_inode_unlock(inode, 0);
		अगर (रुको)
			ret = ocfs2_inode_lock(inode, &bh, 1);
		अन्यथा
			ret = ocfs2_try_inode_lock(inode, &bh, 1);

		अगर (ret < 0) अणु
			अगर (ret != -EAGAIN)
				mlog_त्रुटि_सं(ret);
			वापस ret;
		पूर्ण
		*level = 1;
		अगर (ocfs2_should_update_aसमय(inode, vfsmnt))
			ocfs2_update_inode_aसमय(inode, bh);
		brअन्यथा(bh);
	पूर्ण अन्यथा
		*level = 0;

	वापस ret;
पूर्ण

व्योम ocfs2_inode_unlock(काष्ठा inode *inode,
		       पूर्णांक ex)
अणु
	पूर्णांक level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	काष्ठा ocfs2_lock_res *lockres = &OCFS2_I(inode)->ip_inode_lockres;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog(0, "inode %llu drop %s META lock\n",
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
	     ex ? "EXMODE" : "PRMODE");

	अगर (!ocfs2_is_hard_पढ़ोonly(osb) &&
	    !ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres, level);
पूर्ण

/*
 * This _tracker variantes are पूर्णांकroduced to deal with the recursive cluster
 * locking issue. The idea is to keep track of a lock holder on the stack of
 * the current process. If there's a lock holder on the stack, we know the
 * task context is alपढ़ोy रक्षित by cluster locking. Currently, they're
 * used in some VFS entry routines.
 *
 * वापस < 0 on error, वापस == 0 अगर there's no lock holder on the stack
 * beक्रमe this call, वापस == 1 अगर this call would be a recursive locking.
 * वापस == -1 अगर this lock attempt will cause an upgrade which is क्रमbidden.
 *
 * When taking lock levels पूर्णांकo account,we face some dअगरferent situations.
 *
 * 1. no lock is held
 *    In this हाल, just lock the inode as requested and वापस 0
 *
 * 2. We are holding a lock
 *    For this situation, things भागerges पूर्णांकo several हालs
 *
 *    wanted     holding	     what to करो
 *    ex		ex	    see 2.1 below
 *    ex		pr	    see 2.2 below
 *    pr		ex	    see 2.1 below
 *    pr		pr	    see 2.1 below
 *
 *    2.1 lock level that is been held is compatible
 *    with the wanted level, so no lock action will be tacken.
 *
 *    2.2 Otherwise, an upgrade is needed, but it is क्रमbidden.
 *
 * Reason why upgrade within a process is क्रमbidden is that
 * lock upgrade may cause dead lock. The following illustrates
 * how it happens.
 *
 *         thपढ़ो on node1                             thपढ़ो on node2
 * ocfs2_inode_lock_tracker(ex=0)
 *
 *                                <======   ocfs2_inode_lock_tracker(ex=1)
 *
 * ocfs2_inode_lock_tracker(ex=1)
 */
पूर्णांक ocfs2_inode_lock_tracker(काष्ठा inode *inode,
			     काष्ठा buffer_head **ret_bh,
			     पूर्णांक ex,
			     काष्ठा ocfs2_lock_holder *oh)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_lock_res *lockres;
	काष्ठा ocfs2_lock_holder *पंचांगp_oh;
	काष्ठा pid *pid = task_pid(current);


	lockres = &OCFS2_I(inode)->ip_inode_lockres;
	पंचांगp_oh = ocfs2_pid_holder(lockres, pid);

	अगर (!पंचांगp_oh) अणु
		/*
		 * This corresponds to the हाल 1.
		 * We haven't got any lock beक्रमe.
		 */
		status = ocfs2_inode_lock_full(inode, ret_bh, ex, 0);
		अगर (status < 0) अणु
			अगर (status != -ENOENT)
				mlog_त्रुटि_सं(status);
			वापस status;
		पूर्ण

		oh->oh_ex = ex;
		ocfs2_add_holder(lockres, oh);
		वापस 0;
	पूर्ण

	अगर (unlikely(ex && !पंचांगp_oh->oh_ex)) अणु
		/*
		 * हाल 2.2 upgrade may cause dead lock, क्रमbid it.
		 */
		mlog(ML_ERROR, "Recursive locking is not permitted to "
		     "upgrade to EX level from PR level.\n");
		dump_stack();
		वापस -EINVAL;
	पूर्ण

	/*
	 *  हाल 2.1 OCFS2_META_LOCK_GETBH flag make ocfs2_inode_lock_full.
	 *  ignore the lock level and just update it.
	 */
	अगर (ret_bh) अणु
		status = ocfs2_inode_lock_full(inode, ret_bh, ex,
					       OCFS2_META_LOCK_GETBH);
		अगर (status < 0) अणु
			अगर (status != -ENOENT)
				mlog_त्रुटि_सं(status);
			वापस status;
		पूर्ण
	पूर्ण
	वापस पंचांगp_oh ? 1 : 0;
पूर्ण

व्योम ocfs2_inode_unlock_tracker(काष्ठा inode *inode,
				पूर्णांक ex,
				काष्ठा ocfs2_lock_holder *oh,
				पूर्णांक had_lock)
अणु
	काष्ठा ocfs2_lock_res *lockres;

	lockres = &OCFS2_I(inode)->ip_inode_lockres;
	/* had_lock means that the currect process alपढ़ोy takes the cluster
	 * lock previously.
	 * If had_lock is 1, we have nothing to करो here.
	 * If had_lock is 0, we will release the lock.
	 */
	अगर (!had_lock) अणु
		ocfs2_inode_unlock(inode, oh->oh_ex);
		ocfs2_हटाओ_holder(lockres, oh);
	पूर्ण
पूर्ण

पूर्णांक ocfs2_orphan_scan_lock(काष्ठा ocfs2_super *osb, u32 *seqno)
अणु
	काष्ठा ocfs2_lock_res *lockres;
	काष्ठा ocfs2_orphan_scan_lvb *lvb;
	पूर्णांक status = 0;

	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		वापस -EROFS;

	अगर (ocfs2_mount_local(osb))
		वापस 0;

	lockres = &osb->osb_orphan_scan.os_lockres;
	status = ocfs2_cluster_lock(osb, lockres, DLM_LOCK_EX, 0, 0);
	अगर (status < 0)
		वापस status;

	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
	अगर (ocfs2_dlm_lvb_valid(&lockres->l_lksb) &&
	    lvb->lvb_version == OCFS2_ORPHAN_LVB_VERSION)
		*seqno = be32_to_cpu(lvb->lvb_os_seqno);
	अन्यथा
		*seqno = osb->osb_orphan_scan.os_seqno + 1;

	वापस status;
पूर्ण

व्योम ocfs2_orphan_scan_unlock(काष्ठा ocfs2_super *osb, u32 seqno)
अणु
	काष्ठा ocfs2_lock_res *lockres;
	काष्ठा ocfs2_orphan_scan_lvb *lvb;

	अगर (!ocfs2_is_hard_पढ़ोonly(osb) && !ocfs2_mount_local(osb)) अणु
		lockres = &osb->osb_orphan_scan.os_lockres;
		lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
		lvb->lvb_version = OCFS2_ORPHAN_LVB_VERSION;
		lvb->lvb_os_seqno = cpu_to_be32(seqno);
		ocfs2_cluster_unlock(osb, lockres, DLM_LOCK_EX);
	पूर्ण
पूर्ण

पूर्णांक ocfs2_super_lock(काष्ठा ocfs2_super *osb,
		     पूर्णांक ex)
अणु
	पूर्णांक status = 0;
	पूर्णांक level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_super_lockres;

	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		वापस -EROFS;

	अगर (ocfs2_mount_local(osb))
		जाओ bail;

	status = ocfs2_cluster_lock(osb, lockres, level, 0, 0);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* The super block lock path is really in the best position to
	 * know when resources covered by the lock need to be
	 * refreshed, so we करो it here. Of course, making sense of
	 * everything is up to the caller :) */
	status = ocfs2_should_refresh_lock_res(lockres);
	अगर (status) अणु
		status = ocfs2_refresh_slot_info(osb);

		ocfs2_complete_lock_res_refresh(lockres, status);

		अगर (status < 0) अणु
			ocfs2_cluster_unlock(osb, lockres, level);
			mlog_त्रुटि_सं(status);
		पूर्ण
		ocfs2_track_lock_refresh(lockres);
	पूर्ण
bail:
	वापस status;
पूर्ण

व्योम ocfs2_super_unlock(काष्ठा ocfs2_super *osb,
			पूर्णांक ex)
अणु
	पूर्णांक level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_super_lockres;

	अगर (!ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres, level);
पूर्ण

पूर्णांक ocfs2_नाम_lock(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_नाम_lockres;

	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		वापस -EROFS;

	अगर (ocfs2_mount_local(osb))
		वापस 0;

	status = ocfs2_cluster_lock(osb, lockres, DLM_LOCK_EX, 0, 0);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

व्योम ocfs2_नाम_unlock(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_नाम_lockres;

	अगर (!ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres, DLM_LOCK_EX);
पूर्ण

पूर्णांक ocfs2_nfs_sync_lock(काष्ठा ocfs2_super *osb, पूर्णांक ex)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_nfs_sync_lockres;

	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		वापस -EROFS;

	अगर (ex)
		करोwn_ग_लिखो(&osb->nfs_sync_rwlock);
	अन्यथा
		करोwn_पढ़ो(&osb->nfs_sync_rwlock);

	अगर (ocfs2_mount_local(osb))
		वापस 0;

	status = ocfs2_cluster_lock(osb, lockres, ex ? LKM_EXMODE : LKM_PRMODE,
				    0, 0);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "lock on nfs sync lock failed %d\n", status);

		अगर (ex)
			up_ग_लिखो(&osb->nfs_sync_rwlock);
		अन्यथा
			up_पढ़ो(&osb->nfs_sync_rwlock);
	पूर्ण

	वापस status;
पूर्ण

व्योम ocfs2_nfs_sync_unlock(काष्ठा ocfs2_super *osb, पूर्णांक ex)
अणु
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_nfs_sync_lockres;

	अगर (!ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres,
				     ex ? LKM_EXMODE : LKM_PRMODE);
	अगर (ex)
		up_ग_लिखो(&osb->nfs_sync_rwlock);
	अन्यथा
		up_पढ़ो(&osb->nfs_sync_rwlock);
पूर्ण

पूर्णांक ocfs2_trim_fs_lock(काष्ठा ocfs2_super *osb,
		       काष्ठा ocfs2_trim_fs_info *info, पूर्णांक trylock)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_trim_fs_lvb *lvb;
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_trim_fs_lockres;

	अगर (info)
		info->tf_valid = 0;

	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		वापस -EROFS;

	अगर (ocfs2_mount_local(osb))
		वापस 0;

	status = ocfs2_cluster_lock(osb, lockres, DLM_LOCK_EX,
				    trylock ? DLM_LKF_NOQUEUE : 0, 0);
	अगर (status < 0) अणु
		अगर (status != -EAGAIN)
			mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	अगर (info) अणु
		lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
		अगर (ocfs2_dlm_lvb_valid(&lockres->l_lksb) &&
		    lvb->lvb_version == OCFS2_TRIMFS_LVB_VERSION) अणु
			info->tf_valid = 1;
			info->tf_success = lvb->lvb_success;
			info->tf_nodक्रमागत = be32_to_cpu(lvb->lvb_nodक्रमागत);
			info->tf_start = be64_to_cpu(lvb->lvb_start);
			info->tf_len = be64_to_cpu(lvb->lvb_len);
			info->tf_minlen = be64_to_cpu(lvb->lvb_minlen);
			info->tf_trimlen = be64_to_cpu(lvb->lvb_trimlen);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

व्योम ocfs2_trim_fs_unlock(काष्ठा ocfs2_super *osb,
			  काष्ठा ocfs2_trim_fs_info *info)
अणु
	काष्ठा ocfs2_trim_fs_lvb *lvb;
	काष्ठा ocfs2_lock_res *lockres = &osb->osb_trim_fs_lockres;

	अगर (ocfs2_mount_local(osb))
		वापस;

	अगर (info) अणु
		lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
		lvb->lvb_version = OCFS2_TRIMFS_LVB_VERSION;
		lvb->lvb_success = info->tf_success;
		lvb->lvb_nodक्रमागत = cpu_to_be32(info->tf_nodक्रमागत);
		lvb->lvb_start = cpu_to_be64(info->tf_start);
		lvb->lvb_len = cpu_to_be64(info->tf_len);
		lvb->lvb_minlen = cpu_to_be64(info->tf_minlen);
		lvb->lvb_trimlen = cpu_to_be64(info->tf_trimlen);
	पूर्ण

	ocfs2_cluster_unlock(osb, lockres, DLM_LOCK_EX);
पूर्ण

पूर्णांक ocfs2_dentry_lock(काष्ठा dentry *dentry, पूर्णांक ex)
अणु
	पूर्णांक ret;
	पूर्णांक level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	काष्ठा ocfs2_dentry_lock *dl = dentry->d_fsdata;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dentry->d_sb);

	BUG_ON(!dl);

	अगर (ocfs2_is_hard_पढ़ोonly(osb)) अणु
		अगर (ex)
			वापस -EROFS;
		वापस 0;
	पूर्ण

	अगर (ocfs2_mount_local(osb))
		वापस 0;

	ret = ocfs2_cluster_lock(osb, &dl->dl_lockres, level, 0, 0);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

	वापस ret;
पूर्ण

व्योम ocfs2_dentry_unlock(काष्ठा dentry *dentry, पूर्णांक ex)
अणु
	पूर्णांक level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	काष्ठा ocfs2_dentry_lock *dl = dentry->d_fsdata;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dentry->d_sb);

	अगर (!ocfs2_is_hard_पढ़ोonly(osb) && !ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, &dl->dl_lockres, level);
पूर्ण

/* Reference counting of the dlm debug काष्ठाure. We want this because
 * खोलो references on the debug inodes can live on after a mount, so
 * we can't rely on the ocfs2_super to always exist. */
अटल व्योम ocfs2_dlm_debug_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा ocfs2_dlm_debug *dlm_debug;

	dlm_debug = container_of(kref, काष्ठा ocfs2_dlm_debug, d_refcnt);

	kमुक्त(dlm_debug);
पूर्ण

व्योम ocfs2_put_dlm_debug(काष्ठा ocfs2_dlm_debug *dlm_debug)
अणु
	अगर (dlm_debug)
		kref_put(&dlm_debug->d_refcnt, ocfs2_dlm_debug_मुक्त);
पूर्ण

अटल व्योम ocfs2_get_dlm_debug(काष्ठा ocfs2_dlm_debug *debug)
अणु
	kref_get(&debug->d_refcnt);
पूर्ण

काष्ठा ocfs2_dlm_debug *ocfs2_new_dlm_debug(व्योम)
अणु
	काष्ठा ocfs2_dlm_debug *dlm_debug;

	dlm_debug = kदो_स्मृति(माप(काष्ठा ocfs2_dlm_debug), GFP_KERNEL);
	अगर (!dlm_debug) अणु
		mlog_त्रुटि_सं(-ENOMEM);
		जाओ out;
	पूर्ण

	kref_init(&dlm_debug->d_refcnt);
	INIT_LIST_HEAD(&dlm_debug->d_lockres_tracking);
	dlm_debug->d_filter_secs = 0;
out:
	वापस dlm_debug;
पूर्ण

/* Access to this is arbitrated क्रम us via seq_file->sem. */
काष्ठा ocfs2_dlm_seq_priv अणु
	काष्ठा ocfs2_dlm_debug *p_dlm_debug;
	काष्ठा ocfs2_lock_res p_iter_res;
	काष्ठा ocfs2_lock_res p_पंचांगp_res;
पूर्ण;

अटल काष्ठा ocfs2_lock_res *ocfs2_dlm_next_res(काष्ठा ocfs2_lock_res *start,
						 काष्ठा ocfs2_dlm_seq_priv *priv)
अणु
	काष्ठा ocfs2_lock_res *iter, *ret = शून्य;
	काष्ठा ocfs2_dlm_debug *dlm_debug = priv->p_dlm_debug;

	निश्चित_spin_locked(&ocfs2_dlm_tracking_lock);

	list_क्रम_each_entry(iter, &start->l_debug_list, l_debug_list) अणु
		/* discover the head of the list */
		अगर (&iter->l_debug_list == &dlm_debug->d_lockres_tracking) अणु
			mlog(0, "End of list found, %p\n", ret);
			अवरोध;
		पूर्ण

		/* We track our "dummy" iteration lockres' by a शून्य
		 * l_ops field. */
		अगर (iter->l_ops != शून्य) अणु
			ret = iter;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम *ocfs2_dlm_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ocfs2_dlm_seq_priv *priv = m->निजी;
	काष्ठा ocfs2_lock_res *iter;

	spin_lock(&ocfs2_dlm_tracking_lock);
	iter = ocfs2_dlm_next_res(&priv->p_iter_res, priv);
	अगर (iter) अणु
		/* Since lockres' have the lअगरeसमय of their container
		 * (which can be inodes, ocfs2_supers, etc) we want to
		 * copy this out to a temporary lockres जबतक still
		 * under the spinlock. Obviously after this we can't
		 * trust any poपूर्णांकers on the copy वापसed, but that's
		 * ok as the inक्रमmation we want isn't typically held
		 * in them. */
		priv->p_पंचांगp_res = *iter;
		iter = &priv->p_पंचांगp_res;
	पूर्ण
	spin_unlock(&ocfs2_dlm_tracking_lock);

	वापस iter;
पूर्ण

अटल व्योम ocfs2_dlm_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल व्योम *ocfs2_dlm_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा ocfs2_dlm_seq_priv *priv = m->निजी;
	काष्ठा ocfs2_lock_res *iter = v;
	काष्ठा ocfs2_lock_res *dummy = &priv->p_iter_res;

	spin_lock(&ocfs2_dlm_tracking_lock);
	iter = ocfs2_dlm_next_res(iter, priv);
	list_del_init(&dummy->l_debug_list);
	अगर (iter) अणु
		list_add(&dummy->l_debug_list, &iter->l_debug_list);
		priv->p_पंचांगp_res = *iter;
		iter = &priv->p_पंचांगp_res;
	पूर्ण
	spin_unlock(&ocfs2_dlm_tracking_lock);

	वापस iter;
पूर्ण

/*
 * Version is used by debugfs.ocfs2 to determine the क्रमmat being used
 *
 * New in version 2
 *	- Lock stats prपूर्णांकed
 * New in version 3
 *	- Max समय in lock stats is in usecs (instead of nsecs)
 * New in version 4
 *	- Add last pr/ex unlock बार and first lock रुको समय in usecs
 */
#घोषणा OCFS2_DLM_DEBUG_STR_VERSION 4
अटल पूर्णांक ocfs2_dlm_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;
	अक्षर *lvb;
	काष्ठा ocfs2_lock_res *lockres = v;
#अगर_घोषित CONFIG_OCFS2_FS_STATS
	u64 now, last;
	काष्ठा ocfs2_dlm_debug *dlm_debug =
			((काष्ठा ocfs2_dlm_seq_priv *)m->निजी)->p_dlm_debug;
#पूर्ण_अगर

	अगर (!lockres)
		वापस -EINVAL;

#अगर_घोषित CONFIG_OCFS2_FS_STATS
	अगर (!lockres->l_lock_रुको && dlm_debug->d_filter_secs) अणु
		now = kसमय_प्रकारo_us(kसमय_get_real());
		अगर (lockres->l_lock_prmode.ls_last >
		    lockres->l_lock_exmode.ls_last)
			last = lockres->l_lock_prmode.ls_last;
		अन्यथा
			last = lockres->l_lock_exmode.ls_last;
		/*
		 * Use d_filter_secs field to filter lock resources dump,
		 * the शेष d_filter_secs(0) value filters nothing,
		 * otherwise, only dump the last N seconds active lock
		 * resources.
		 */
		अगर (भाग_u64(now - last, 1000000) > dlm_debug->d_filter_secs)
			वापस 0;
	पूर्ण
#पूर्ण_अगर

	seq_म_लिखो(m, "0x%x\t", OCFS2_DLM_DEBUG_STR_VERSION);

	अगर (lockres->l_type == OCFS2_LOCK_TYPE_DENTRY)
		seq_म_लिखो(m, "%.*s%08x\t", OCFS2_DENTRY_LOCK_INO_START - 1,
			   lockres->l_name,
			   (अचिन्हित पूर्णांक)ocfs2_get_dentry_lock_ino(lockres));
	अन्यथा
		seq_म_लिखो(m, "%.*s\t", OCFS2_LOCK_ID_MAX_LEN, lockres->l_name);

	seq_म_लिखो(m, "%d\t"
		   "0x%lx\t"
		   "0x%x\t"
		   "0x%x\t"
		   "%u\t"
		   "%u\t"
		   "%d\t"
		   "%d\t",
		   lockres->l_level,
		   lockres->l_flags,
		   lockres->l_action,
		   lockres->l_unlock_action,
		   lockres->l_ro_holders,
		   lockres->l_ex_holders,
		   lockres->l_requested,
		   lockres->l_blocking);

	/* Dump the raw LVB */
	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
	क्रम(i = 0; i < DLM_LVB_LEN; i++)
		seq_म_लिखो(m, "0x%x\t", lvb[i]);

#अगर_घोषित CONFIG_OCFS2_FS_STATS
# define lock_num_prmode(_l)		((_l)->l_lock_prmode.ls_माला_लो)
# define lock_num_exmode(_l)		((_l)->l_lock_exmode.ls_माला_लो)
# define lock_num_prmode_failed(_l)	((_l)->l_lock_prmode.ls_fail)
# define lock_num_exmode_failed(_l)	((_l)->l_lock_exmode.ls_fail)
# define lock_total_prmode(_l)		((_l)->l_lock_prmode.ls_total)
# define lock_total_exmode(_l)		((_l)->l_lock_exmode.ls_total)
# define lock_max_prmode(_l)		((_l)->l_lock_prmode.ls_max)
# define lock_max_exmode(_l)		((_l)->l_lock_exmode.ls_max)
# define lock_refresh(_l)		((_l)->l_lock_refresh)
# define lock_last_prmode(_l)		((_l)->l_lock_prmode.ls_last)
# define lock_last_exmode(_l)		((_l)->l_lock_exmode.ls_last)
# define lock_रुको(_l)			((_l)->l_lock_रुको)
#अन्यथा
# define lock_num_prmode(_l)		(0)
# define lock_num_exmode(_l)		(0)
# define lock_num_prmode_failed(_l)	(0)
# define lock_num_exmode_failed(_l)	(0)
# define lock_total_prmode(_l)		(0ULL)
# define lock_total_exmode(_l)		(0ULL)
# define lock_max_prmode(_l)		(0)
# define lock_max_exmode(_l)		(0)
# define lock_refresh(_l)		(0)
# define lock_last_prmode(_l)		(0ULL)
# define lock_last_exmode(_l)		(0ULL)
# define lock_रुको(_l)			(0ULL)
#पूर्ण_अगर
	/* The following seq_prपूर्णांक was added in version 2 of this output */
	seq_म_लिखो(m, "%u\t"
		   "%u\t"
		   "%u\t"
		   "%u\t"
		   "%llu\t"
		   "%llu\t"
		   "%u\t"
		   "%u\t"
		   "%u\t"
		   "%llu\t"
		   "%llu\t"
		   "%llu\t",
		   lock_num_prmode(lockres),
		   lock_num_exmode(lockres),
		   lock_num_prmode_failed(lockres),
		   lock_num_exmode_failed(lockres),
		   lock_total_prmode(lockres),
		   lock_total_exmode(lockres),
		   lock_max_prmode(lockres),
		   lock_max_exmode(lockres),
		   lock_refresh(lockres),
		   lock_last_prmode(lockres),
		   lock_last_exmode(lockres),
		   lock_रुको(lockres));

	/* End the line */
	seq_म_लिखो(m, "\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ocfs2_dlm_seq_ops = अणु
	.start =	ocfs2_dlm_seq_start,
	.stop =		ocfs2_dlm_seq_stop,
	.next =		ocfs2_dlm_seq_next,
	.show =		ocfs2_dlm_seq_show,
पूर्ण;

अटल पूर्णांक ocfs2_dlm_debug_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा ocfs2_dlm_seq_priv *priv = seq->निजी;
	काष्ठा ocfs2_lock_res *res = &priv->p_iter_res;

	ocfs2_हटाओ_lockres_tracking(res);
	ocfs2_put_dlm_debug(priv->p_dlm_debug);
	वापस seq_release_निजी(inode, file);
पूर्ण

अटल पूर्णांक ocfs2_dlm_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocfs2_dlm_seq_priv *priv;
	काष्ठा ocfs2_super *osb;

	priv = __seq_खोलो_निजी(file, &ocfs2_dlm_seq_ops, माप(*priv));
	अगर (!priv) अणु
		mlog_त्रुटि_सं(-ENOMEM);
		वापस -ENOMEM;
	पूर्ण

	osb = inode->i_निजी;
	ocfs2_get_dlm_debug(osb->osb_dlm_debug);
	priv->p_dlm_debug = osb->osb_dlm_debug;
	INIT_LIST_HEAD(&priv->p_iter_res.l_debug_list);

	ocfs2_add_lockres_tracking(&priv->p_iter_res,
				   priv->p_dlm_debug);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations ocfs2_dlm_debug_fops = अणु
	.खोलो =		ocfs2_dlm_debug_खोलो,
	.release =	ocfs2_dlm_debug_release,
	.पढ़ो =		seq_पढ़ो,
	.llseek =	seq_lseek,
पूर्ण;

अटल व्योम ocfs2_dlm_init_debug(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_dlm_debug *dlm_debug = osb->osb_dlm_debug;

	debugfs_create_file("locking_state", S_IFREG|S_IRUSR,
			    osb->osb_debug_root, osb, &ocfs2_dlm_debug_fops);

	debugfs_create_u32("locking_filter", 0600, osb->osb_debug_root,
			   &dlm_debug->d_filter_secs);
	ocfs2_get_dlm_debug(dlm_debug);
पूर्ण

अटल व्योम ocfs2_dlm_shutकरोwn_debug(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_dlm_debug *dlm_debug = osb->osb_dlm_debug;

	अगर (dlm_debug)
		ocfs2_put_dlm_debug(dlm_debug);
पूर्ण

पूर्णांक ocfs2_dlm_init(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_cluster_connection *conn = शून्य;

	अगर (ocfs2_mount_local(osb)) अणु
		osb->node_num = 0;
		जाओ local;
	पूर्ण

	ocfs2_dlm_init_debug(osb);

	/* launch करोwnconvert thपढ़ो */
	osb->dc_task = kthपढ़ो_run(ocfs2_करोwnconvert_thपढ़ो, osb, "ocfs2dc-%s",
			osb->uuid_str);
	अगर (IS_ERR(osb->dc_task)) अणु
		status = PTR_ERR(osb->dc_task);
		osb->dc_task = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* क्रम now, uuid == करोमुख्य */
	status = ocfs2_cluster_connect(osb->osb_cluster_stack,
				       osb->osb_cluster_name,
				       म_माप(osb->osb_cluster_name),
				       osb->uuid_str,
				       म_माप(osb->uuid_str),
				       &lproto, ocfs2_करो_node_करोwn, osb,
				       &conn);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_cluster_this_node(conn, &osb->node_num);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		mlog(ML_ERROR,
		     "could not find this host's node number\n");
		ocfs2_cluster_disconnect(conn, 0);
		जाओ bail;
	पूर्ण

local:
	ocfs2_super_lock_res_init(&osb->osb_super_lockres, osb);
	ocfs2_नाम_lock_res_init(&osb->osb_नाम_lockres, osb);
	ocfs2_nfs_sync_lock_init(osb);
	ocfs2_orphan_scan_lock_res_init(&osb->osb_orphan_scan.os_lockres, osb);

	osb->cconn = conn;
bail:
	अगर (status < 0) अणु
		ocfs2_dlm_shutकरोwn_debug(osb);
		अगर (osb->dc_task)
			kthपढ़ो_stop(osb->dc_task);
	पूर्ण

	वापस status;
पूर्ण

व्योम ocfs2_dlm_shutकरोwn(काष्ठा ocfs2_super *osb,
			पूर्णांक hangup_pending)
अणु
	ocfs2_drop_osb_locks(osb);

	/*
	 * Now that we have dropped all locks and ocfs2_dismount_volume()
	 * has disabled recovery, the DLM won't be talking to us.  It's
	 * safe to tear things करोwn beक्रमe disconnecting the cluster.
	 */

	अगर (osb->dc_task) अणु
		kthपढ़ो_stop(osb->dc_task);
		osb->dc_task = शून्य;
	पूर्ण

	ocfs2_lock_res_मुक्त(&osb->osb_super_lockres);
	ocfs2_lock_res_मुक्त(&osb->osb_नाम_lockres);
	ocfs2_lock_res_मुक्त(&osb->osb_nfs_sync_lockres);
	ocfs2_lock_res_मुक्त(&osb->osb_orphan_scan.os_lockres);

	ocfs2_cluster_disconnect(osb->cconn, hangup_pending);
	osb->cconn = शून्य;

	ocfs2_dlm_shutकरोwn_debug(osb);
पूर्ण

अटल पूर्णांक ocfs2_drop_lock(काष्ठा ocfs2_super *osb,
			   काष्ठा ocfs2_lock_res *lockres)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	u32 lkm_flags = 0;

	/* We didn't get anywhere near actually using this lockres. */
	अगर (!(lockres->l_flags & OCFS2_LOCK_INITIALIZED))
		जाओ out;

	अगर (lockres->l_ops->flags & LOCK_TYPE_USES_LVB)
		lkm_flags |= DLM_LKF_VALBLK;

	spin_lock_irqsave(&lockres->l_lock, flags);

	mlog_bug_on_msg(!(lockres->l_flags & OCFS2_LOCK_FREEING),
			"lockres %s, flags 0x%lx\n",
			lockres->l_name, lockres->l_flags);

	जबतक (lockres->l_flags & OCFS2_LOCK_BUSY) अणु
		mlog(0, "waiting on busy lock \"%s\": flags = %lx, action = "
		     "%u, unlock_action = %u\n",
		     lockres->l_name, lockres->l_flags, lockres->l_action,
		     lockres->l_unlock_action);

		spin_unlock_irqrestore(&lockres->l_lock, flags);

		/* XXX: Today we just रुको on any busy
		 * locks... Perhaps we need to cancel converts in the
		 * future? */
		ocfs2_रुको_on_busy_lock(lockres);

		spin_lock_irqsave(&lockres->l_lock, flags);
	पूर्ण

	अगर (lockres->l_ops->flags & LOCK_TYPE_USES_LVB) अणु
		अगर (lockres->l_flags & OCFS2_LOCK_ATTACHED &&
		    lockres->l_level == DLM_LOCK_EX &&
		    !(lockres->l_flags & OCFS2_LOCK_NEEDS_REFRESH))
			lockres->l_ops->set_lvb(lockres);
	पूर्ण

	अगर (lockres->l_flags & OCFS2_LOCK_BUSY)
		mlog(ML_ERROR, "destroying busy lock: \"%s\"\n",
		     lockres->l_name);
	अगर (lockres->l_flags & OCFS2_LOCK_BLOCKED)
		mlog(0, "destroying blocked lock: \"%s\"\n", lockres->l_name);

	अगर (!(lockres->l_flags & OCFS2_LOCK_ATTACHED)) अणु
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		जाओ out;
	पूर्ण

	lockres_clear_flags(lockres, OCFS2_LOCK_ATTACHED);

	/* make sure we never get here जबतक रुकोing क्रम an ast to
	 * fire. */
	BUG_ON(lockres->l_action != OCFS2_AST_INVALID);

	/* is this necessary? */
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);
	lockres->l_unlock_action = OCFS2_UNLOCK_DROP_LOCK;
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	mlog(0, "lock %s\n", lockres->l_name);

	ret = ocfs2_dlm_unlock(osb->cconn, &lockres->l_lksb, lkm_flags);
	अगर (ret) अणु
		ocfs2_log_dlm_error("ocfs2_dlm_unlock", ret, lockres);
		mlog(ML_ERROR, "lockres flags: %lu\n", lockres->l_flags);
		ocfs2_dlm_dump_lksb(&lockres->l_lksb);
		BUG();
	पूर्ण
	mlog(0, "lock %s, successful return from ocfs2_dlm_unlock\n",
	     lockres->l_name);

	ocfs2_रुको_on_busy_lock(lockres);
out:
	वापस 0;
पूर्ण

अटल व्योम ocfs2_process_blocked_lock(काष्ठा ocfs2_super *osb,
				       काष्ठा ocfs2_lock_res *lockres);

/* Mark the lockres as being dropped. It will no दीर्घer be
 * queued अगर blocking, but we still may have to रुको on it
 * being dequeued from the करोwnconvert thपढ़ो beक्रमe we can consider
 * it safe to drop.
 *
 * You can *not* attempt to call cluster_lock on this lockres anymore. */
व्योम ocfs2_mark_lockres_मुक्तing(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_lock_res *lockres)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_mask_रुकोer mw;
	अचिन्हित दीर्घ flags, flags2;

	ocfs2_init_mask_रुकोer(&mw);

	spin_lock_irqsave(&lockres->l_lock, flags);
	lockres->l_flags |= OCFS2_LOCK_FREEING;
	अगर (lockres->l_flags & OCFS2_LOCK_QUEUED && current == osb->dc_task) अणु
		/*
		 * We know the करोwnconvert is queued but not in progress
		 * because we are the करोwnconvert thपढ़ो and processing
		 * dअगरferent lock. So we can just हटाओ the lock from the
		 * queue. This is not only an optimization but also a way
		 * to aव्योम the following deadlock:
		 *   ocfs2_dentry_post_unlock()
		 *     ocfs2_dentry_lock_put()
		 *       ocfs2_drop_dentry_lock()
		 *         iput()
		 *           ocfs2_evict_inode()
		 *             ocfs2_clear_inode()
		 *               ocfs2_mark_lockres_मुक्तing()
		 *                 ... blocks रुकोing क्रम OCFS2_LOCK_QUEUED
		 *                 since we are the करोwnconvert thपढ़ो which
		 *                 should clear the flag.
		 */
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		spin_lock_irqsave(&osb->dc_task_lock, flags2);
		list_del_init(&lockres->l_blocked_list);
		osb->blocked_lock_count--;
		spin_unlock_irqrestore(&osb->dc_task_lock, flags2);
		/*
		 * Warn अगर we recurse पूर्णांकo another post_unlock call.  Strictly
		 * speaking it isn't a problem but we need to be careful अगर
		 * that happens (stack overflow, deadlocks, ...) so warn अगर
		 * ocfs2 grows a path क्रम which this can happen.
		 */
		WARN_ON_ONCE(lockres->l_ops->post_unlock);
		/* Since the lock is मुक्तing we करोn't करो much in the fn below */
		ocfs2_process_blocked_lock(osb, lockres);
		वापस;
	पूर्ण
	जबतक (lockres->l_flags & OCFS2_LOCK_QUEUED) अणु
		lockres_add_mask_रुकोer(lockres, &mw, OCFS2_LOCK_QUEUED, 0);
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		mlog(0, "Waiting on lockres %s\n", lockres->l_name);

		status = ocfs2_रुको_क्रम_mask(&mw);
		अगर (status)
			mlog_त्रुटि_सं(status);

		spin_lock_irqsave(&lockres->l_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&lockres->l_lock, flags);
पूर्ण

व्योम ocfs2_simple_drop_lockres(काष्ठा ocfs2_super *osb,
			       काष्ठा ocfs2_lock_res *lockres)
अणु
	पूर्णांक ret;

	ocfs2_mark_lockres_मुक्तing(osb, lockres);
	ret = ocfs2_drop_lock(osb, lockres);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
पूर्ण

अटल व्योम ocfs2_drop_osb_locks(काष्ठा ocfs2_super *osb)
अणु
	ocfs2_simple_drop_lockres(osb, &osb->osb_super_lockres);
	ocfs2_simple_drop_lockres(osb, &osb->osb_नाम_lockres);
	ocfs2_simple_drop_lockres(osb, &osb->osb_nfs_sync_lockres);
	ocfs2_simple_drop_lockres(osb, &osb->osb_orphan_scan.os_lockres);
पूर्ण

पूर्णांक ocfs2_drop_inode_locks(काष्ठा inode *inode)
अणु
	पूर्णांक status, err;

	/* No need to call ocfs2_mark_lockres_मुक्तing here -
	 * ocfs2_clear_inode has करोne it क्रम us. */

	err = ocfs2_drop_lock(OCFS2_SB(inode->i_sb),
			      &OCFS2_I(inode)->ip_खोलो_lockres);
	अगर (err < 0)
		mlog_त्रुटि_सं(err);

	status = err;

	err = ocfs2_drop_lock(OCFS2_SB(inode->i_sb),
			      &OCFS2_I(inode)->ip_inode_lockres);
	अगर (err < 0)
		mlog_त्रुटि_सं(err);
	अगर (err < 0 && !status)
		status = err;

	err = ocfs2_drop_lock(OCFS2_SB(inode->i_sb),
			      &OCFS2_I(inode)->ip_rw_lockres);
	अगर (err < 0)
		mlog_त्रुटि_सं(err);
	अगर (err < 0 && !status)
		status = err;

	वापस status;
पूर्ण

अटल अचिन्हित पूर्णांक ocfs2_prepare_करोwnconvert(काष्ठा ocfs2_lock_res *lockres,
					      पूर्णांक new_level)
अणु
	निश्चित_spin_locked(&lockres->l_lock);

	BUG_ON(lockres->l_blocking <= DLM_LOCK_NL);

	अगर (lockres->l_level <= new_level) अणु
		mlog(ML_ERROR, "lockres %s, lvl %d <= %d, blcklst %d, mask %d, "
		     "type %d, flags 0x%lx, hold %d %d, act %d %d, req %d, "
		     "block %d, pgen %d\n", lockres->l_name, lockres->l_level,
		     new_level, list_empty(&lockres->l_blocked_list),
		     list_empty(&lockres->l_mask_रुकोers), lockres->l_type,
		     lockres->l_flags, lockres->l_ro_holders,
		     lockres->l_ex_holders, lockres->l_action,
		     lockres->l_unlock_action, lockres->l_requested,
		     lockres->l_blocking, lockres->l_pending_gen);
		BUG();
	पूर्ण

	mlog(ML_BASTS, "lockres %s, level %d => %d, blocking %d\n",
	     lockres->l_name, lockres->l_level, new_level, lockres->l_blocking);

	lockres->l_action = OCFS2_AST_DOWNCONVERT;
	lockres->l_requested = new_level;
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);
	वापस lockres_set_pending(lockres);
पूर्ण

अटल पूर्णांक ocfs2_करोwnconvert_lock(काष्ठा ocfs2_super *osb,
				  काष्ठा ocfs2_lock_res *lockres,
				  पूर्णांक new_level,
				  पूर्णांक lvb,
				  अचिन्हित पूर्णांक generation)
अणु
	पूर्णांक ret;
	u32 dlm_flags = DLM_LKF_CONVERT;

	mlog(ML_BASTS, "lockres %s, level %d => %d\n", lockres->l_name,
	     lockres->l_level, new_level);

	/*
	 * On DLM_LKF_VALBLK, fsdlm behaves dअगरferently with o2cb. It always
	 * expects DLM_LKF_VALBLK being set अगर the LKB has LVB, so that
	 * we can recover correctly from node failure. Otherwise, we may get
	 * invalid LVB in LKB, but without DLM_SBF_VALNOTVALID being set.
	 */
	अगर (ocfs2_userspace_stack(osb) &&
	    lockres->l_ops->flags & LOCK_TYPE_USES_LVB)
		lvb = 1;

	अगर (lvb)
		dlm_flags |= DLM_LKF_VALBLK;

	ret = ocfs2_dlm_lock(osb->cconn,
			     new_level,
			     &lockres->l_lksb,
			     dlm_flags,
			     lockres->l_name,
			     OCFS2_LOCK_ID_MAX_LEN - 1);
	lockres_clear_pending(lockres, generation, osb);
	अगर (ret) अणु
		ocfs2_log_dlm_error("ocfs2_dlm_lock", ret, lockres);
		ocfs2_recover_from_dlm_error(lockres, 1);
		जाओ bail;
	पूर्ण

	ret = 0;
bail:
	वापस ret;
पूर्ण

/* वापसs 1 when the caller should unlock and call ocfs2_dlm_unlock */
अटल पूर्णांक ocfs2_prepare_cancel_convert(काष्ठा ocfs2_super *osb,
				        काष्ठा ocfs2_lock_res *lockres)
अणु
	निश्चित_spin_locked(&lockres->l_lock);

	अगर (lockres->l_unlock_action == OCFS2_UNLOCK_CANCEL_CONVERT) अणु
		/* If we're alपढ़ोy trying to cancel a lock conversion
		 * then just drop the spinlock and allow the caller to
		 * requeue this lock. */
		mlog(ML_BASTS, "lockres %s, skip convert\n", lockres->l_name);
		वापस 0;
	पूर्ण

	/* were we in a convert when we got the bast fire? */
	BUG_ON(lockres->l_action != OCFS2_AST_CONVERT &&
	       lockres->l_action != OCFS2_AST_DOWNCONVERT);
	/* set things up क्रम the unlockast to know to just
	 * clear out the ast_action and unset busy, etc. */
	lockres->l_unlock_action = OCFS2_UNLOCK_CANCEL_CONVERT;

	mlog_bug_on_msg(!(lockres->l_flags & OCFS2_LOCK_BUSY),
			"lock %s, invalid flags: 0x%lx\n",
			lockres->l_name, lockres->l_flags);

	mlog(ML_BASTS, "lockres %s\n", lockres->l_name);

	वापस 1;
पूर्ण

अटल पूर्णांक ocfs2_cancel_convert(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_lock_res *lockres)
अणु
	पूर्णांक ret;

	ret = ocfs2_dlm_unlock(osb->cconn, &lockres->l_lksb,
			       DLM_LKF_CANCEL);
	अगर (ret) अणु
		ocfs2_log_dlm_error("ocfs2_dlm_unlock", ret, lockres);
		ocfs2_recover_from_dlm_error(lockres, 0);
	पूर्ण

	mlog(ML_BASTS, "lockres %s\n", lockres->l_name);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_unblock_lock(काष्ठा ocfs2_super *osb,
			      काष्ठा ocfs2_lock_res *lockres,
			      काष्ठा ocfs2_unblock_ctl *ctl)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक blocking;
	पूर्णांक new_level;
	पूर्णांक level;
	पूर्णांक ret = 0;
	पूर्णांक set_lvb = 0;
	अचिन्हित पूर्णांक gen;

	spin_lock_irqsave(&lockres->l_lock, flags);

recheck:
	/*
	 * Is it still blocking? If not, we have no more work to करो.
	 */
	अगर (!(lockres->l_flags & OCFS2_LOCK_BLOCKED)) अणु
		BUG_ON(lockres->l_blocking != DLM_LOCK_NL);
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		ret = 0;
		जाओ leave;
	पूर्ण

	अगर (lockres->l_flags & OCFS2_LOCK_BUSY) अणु
		/* XXX
		 * This is a *big* race.  The OCFS2_LOCK_PENDING flag
		 * exists entirely क्रम one reason - another thपढ़ो has set
		 * OCFS2_LOCK_BUSY, but has *NOT* yet called dlm_lock().
		 *
		 * If we करो ocfs2_cancel_convert() beक्रमe the other thपढ़ो
		 * calls dlm_lock(), our cancel will करो nothing.  We will
		 * get no ast, and we will have no way of knowing the
		 * cancel failed.  Meanजबतक, the other thपढ़ो will call
		 * पूर्णांकo dlm_lock() and रुको...क्रमever.
		 *
		 * Why क्रमever?  Because another node has asked क्रम the
		 * lock first; that's why we're here in unblock_lock().
		 *
		 * The solution is OCFS2_LOCK_PENDING.  When PENDING is
		 * set, we just requeue the unblock.  Only when the other
		 * thपढ़ो has called dlm_lock() and cleared PENDING will
		 * we then cancel their request.
		 *
		 * All callers of dlm_lock() must set OCFS2_DLM_PENDING
		 * at the same समय they set OCFS2_DLM_BUSY.  They must
		 * clear OCFS2_DLM_PENDING after dlm_lock() वापसs.
		 */
		अगर (lockres->l_flags & OCFS2_LOCK_PENDING) अणु
			mlog(ML_BASTS, "lockres %s, ReQ: Pending\n",
			     lockres->l_name);
			जाओ leave_requeue;
		पूर्ण

		ctl->requeue = 1;
		ret = ocfs2_prepare_cancel_convert(osb, lockres);
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		अगर (ret) अणु
			ret = ocfs2_cancel_convert(osb, lockres);
			अगर (ret < 0)
				mlog_त्रुटि_सं(ret);
		पूर्ण
		जाओ leave;
	पूर्ण

	/*
	 * This prevents livelocks. OCFS2_LOCK_UPCONVERT_FINISHING flag is
	 * set when the ast is received क्रम an upconvert just beक्रमe the
	 * OCFS2_LOCK_BUSY flag is cleared. Now अगर the fs received a bast
	 * on the heels of the ast, we want to delay the करोwnconvert just
	 * enough to allow the up requestor to करो its task. Because this
	 * lock is in the blocked queue, the lock will be करोwnconverted
	 * as soon as the requestor is करोne with the lock.
	 */
	अगर (lockres->l_flags & OCFS2_LOCK_UPCONVERT_FINISHING)
		जाओ leave_requeue;

	/*
	 * How can we block and yet be at NL?  We were trying to upconvert
	 * from NL and got canceled.  The code comes back here, and now
	 * we notice and clear BLOCKING.
	 */
	अगर (lockres->l_level == DLM_LOCK_NL) अणु
		BUG_ON(lockres->l_ex_holders || lockres->l_ro_holders);
		mlog(ML_BASTS, "lockres %s, Aborting dc\n", lockres->l_name);
		lockres->l_blocking = DLM_LOCK_NL;
		lockres_clear_flags(lockres, OCFS2_LOCK_BLOCKED);
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		जाओ leave;
	पूर्ण

	/* अगर we're blocking an exclusive and we have *any* holders,
	 * then requeue. */
	अगर ((lockres->l_blocking == DLM_LOCK_EX)
	    && (lockres->l_ex_holders || lockres->l_ro_holders)) अणु
		mlog(ML_BASTS, "lockres %s, ReQ: EX/PR Holders %u,%u\n",
		     lockres->l_name, lockres->l_ex_holders,
		     lockres->l_ro_holders);
		जाओ leave_requeue;
	पूर्ण

	/* If it's a PR we're blocking, then only
	 * requeue अगर we've got any EX holders */
	अगर (lockres->l_blocking == DLM_LOCK_PR &&
	    lockres->l_ex_holders) अणु
		mlog(ML_BASTS, "lockres %s, ReQ: EX Holders %u\n",
		     lockres->l_name, lockres->l_ex_holders);
		जाओ leave_requeue;
	पूर्ण

	/*
	 * Can we get a lock in this state अगर the holder counts are
	 * zero? The meta data unblock code used to check this.
	 */
	अगर ((lockres->l_ops->flags & LOCK_TYPE_REQUIRES_REFRESH)
	    && (lockres->l_flags & OCFS2_LOCK_REFRESHING)) अणु
		mlog(ML_BASTS, "lockres %s, ReQ: Lock Refreshing\n",
		     lockres->l_name);
		जाओ leave_requeue;
	पूर्ण

	new_level = ocfs2_highest_compat_lock_level(lockres->l_blocking);

	अगर (lockres->l_ops->check_करोwnconvert
	    && !lockres->l_ops->check_करोwnconvert(lockres, new_level)) अणु
		mlog(ML_BASTS, "lockres %s, ReQ: Checkpointing\n",
		     lockres->l_name);
		जाओ leave_requeue;
	पूर्ण

	/* If we get here, then we know that there are no more
	 * incompatible holders (and anyone asking क्रम an incompatible
	 * lock is blocked). We can now करोwnconvert the lock */
	अगर (!lockres->l_ops->करोwnconvert_worker)
		जाओ करोwnconvert;

	/* Some lockres types want to करो a bit of work beक्रमe
	 * करोwnconverting a lock. Allow that here. The worker function
	 * may sleep, so we save off a copy of what we're blocking as
	 * it may change जबतक we're not holding the spin lock. */
	blocking = lockres->l_blocking;
	level = lockres->l_level;
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	ctl->unblock_action = lockres->l_ops->करोwnconvert_worker(lockres, blocking);

	अगर (ctl->unblock_action == UNBLOCK_STOP_POST) अणु
		mlog(ML_BASTS, "lockres %s, UNBLOCK_STOP_POST\n",
		     lockres->l_name);
		जाओ leave;
	पूर्ण

	spin_lock_irqsave(&lockres->l_lock, flags);
	अगर ((blocking != lockres->l_blocking) || (level != lockres->l_level)) अणु
		/* If this changed underneath us, then we can't drop
		 * it just yet. */
		mlog(ML_BASTS, "lockres %s, block=%d:%d, level=%d:%d, "
		     "Recheck\n", lockres->l_name, blocking,
		     lockres->l_blocking, level, lockres->l_level);
		जाओ recheck;
	पूर्ण

करोwnconvert:
	ctl->requeue = 0;

	अगर (lockres->l_ops->flags & LOCK_TYPE_USES_LVB) अणु
		अगर (lockres->l_level == DLM_LOCK_EX)
			set_lvb = 1;

		/*
		 * We only set the lvb अगर the lock has been fully
		 * refreshed - otherwise we risk setting stale
		 * data. Otherwise, there's no need to actually clear
		 * out the lvb here as it's value is still valid.
		 */
		अगर (set_lvb && !(lockres->l_flags & OCFS2_LOCK_NEEDS_REFRESH))
			lockres->l_ops->set_lvb(lockres);
	पूर्ण

	gen = ocfs2_prepare_करोwnconvert(lockres, new_level);
	spin_unlock_irqrestore(&lockres->l_lock, flags);
	ret = ocfs2_करोwnconvert_lock(osb, lockres, new_level, set_lvb,
				     gen);

leave:
	अगर (ret)
		mlog_त्रुटि_सं(ret);
	वापस ret;

leave_requeue:
	spin_unlock_irqrestore(&lockres->l_lock, flags);
	ctl->requeue = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_data_convert_worker(काष्ठा ocfs2_lock_res *lockres,
				     पूर्णांक blocking)
अणु
	काष्ठा inode *inode;
	काष्ठा address_space *mapping;
	काष्ठा ocfs2_inode_info *oi;

       	inode = ocfs2_lock_res_inode(lockres);
	mapping = inode->i_mapping;

	अगर (S_ISसूची(inode->i_mode)) अणु
		oi = OCFS2_I(inode);
		oi->ip_dir_lock_gen++;
		mlog(0, "generation: %u\n", oi->ip_dir_lock_gen);
		जाओ out;
	पूर्ण

	अगर (!S_ISREG(inode->i_mode))
		जाओ out;

	/*
	 * We need this beक्रमe the filemap_fdataग_लिखो() so that it can
	 * transfer the dirty bit from the PTE to the
	 * page. Unक्रमtunately this means that even क्रम EX->PR
	 * करोwnconverts, we'll lose our mappings and have to build
	 * them up again.
	 */
	unmap_mapping_range(mapping, 0, 0, 0);

	अगर (filemap_fdataग_लिखो(mapping)) अणु
		mlog(ML_ERROR, "Could not sync inode %llu for downconvert!",
		     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
	पूर्ण
	sync_mapping_buffers(mapping);
	अगर (blocking == DLM_LOCK_EX) अणु
		truncate_inode_pages(mapping, 0);
	पूर्ण अन्यथा अणु
		/* We only need to रुको on the I/O अगर we're not also
		 * truncating pages because truncate_inode_pages रुकोs
		 * क्रम us above. We करोn't truncate pages if we're
		 * blocking anything < EXMODE because we want to keep
		 * them around in that हाल. */
		filemap_fdataरुको(mapping);
	पूर्ण

	क्रमget_all_cached_acls(inode);

out:
	वापस UNBLOCK_CONTINUE;
पूर्ण

अटल पूर्णांक ocfs2_ci_checkpoपूर्णांकed(काष्ठा ocfs2_caching_info *ci,
				 काष्ठा ocfs2_lock_res *lockres,
				 पूर्णांक new_level)
अणु
	पूर्णांक checkpoपूर्णांकed = ocfs2_ci_fully_checkpoपूर्णांकed(ci);

	BUG_ON(new_level != DLM_LOCK_NL && new_level != DLM_LOCK_PR);
	BUG_ON(lockres->l_level != DLM_LOCK_EX && !checkpoपूर्णांकed);

	अगर (checkpoपूर्णांकed)
		वापस 1;

	ocfs2_start_checkpoपूर्णांक(OCFS2_SB(ocfs2_metadata_cache_get_super(ci)));
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_check_meta_करोwnconvert(काष्ठा ocfs2_lock_res *lockres,
					पूर्णांक new_level)
अणु
	काष्ठा inode *inode = ocfs2_lock_res_inode(lockres);

	वापस ocfs2_ci_checkpoपूर्णांकed(INODE_CACHE(inode), lockres, new_level);
पूर्ण

अटल व्योम ocfs2_set_meta_lvb(काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा inode *inode = ocfs2_lock_res_inode(lockres);

	__ocfs2_stuff_meta_lvb(inode);
पूर्ण

/*
 * Does the final reference drop on our dentry lock. Right now this
 * happens in the करोwnconvert thपढ़ो, but we could choose to simplअगरy the
 * dlmglue API and push these off to the ocfs2_wq in the future.
 */
अटल व्योम ocfs2_dentry_post_unlock(काष्ठा ocfs2_super *osb,
				     काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा ocfs2_dentry_lock *dl = ocfs2_lock_res_dl(lockres);
	ocfs2_dentry_lock_put(osb, dl);
पूर्ण

/*
 * d_delete() matching dentries beक्रमe the lock करोwnconvert.
 *
 * At this poपूर्णांक, any process रुकोing to destroy the
 * dentry_lock due to last ref count is stopped by the
 * OCFS2_LOCK_QUEUED flag.
 *
 * We have two potential problems
 *
 * 1) If we करो the last reference drop on our dentry_lock (via dput)
 *    we'll wind up in ocfs2_release_dentry_lock(), रुकोing on
 *    the करोwnconvert to finish. Instead we take an elevated
 *    reference and push the drop until after we've completed our
 *    unblock processing.
 *
 * 2) There might be another process with a final reference,
 *    रुकोing on us to finish processing. If this is the हाल, we
 *    detect it and निकास out - there's no more dentries anyway.
 */
अटल पूर्णांक ocfs2_dentry_convert_worker(काष्ठा ocfs2_lock_res *lockres,
				       पूर्णांक blocking)
अणु
	काष्ठा ocfs2_dentry_lock *dl = ocfs2_lock_res_dl(lockres);
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(dl->dl_inode);
	काष्ठा dentry *dentry;
	अचिन्हित दीर्घ flags;
	पूर्णांक extra_ref = 0;

	/*
	 * This node is blocking another node from getting a पढ़ो
	 * lock. This happens when we've नामd within a
	 * directory. We've क्रमced the other nodes to d_delete(), but
	 * we never actually dropped our lock because it's still
	 * valid. The करोwnconvert code will retain a PR क्रम this node,
	 * so there's no further work to करो.
	 */
	अगर (blocking == DLM_LOCK_PR)
		वापस UNBLOCK_CONTINUE;

	/*
	 * Mark this inode as potentially orphaned. The code in
	 * ocfs2_delete_inode() will figure out whether it actually
	 * needs to be मुक्तd or not.
	 */
	spin_lock(&oi->ip_lock);
	oi->ip_flags |= OCFS2_INODE_MAYBE_ORPHANED;
	spin_unlock(&oi->ip_lock);

	/*
	 * Yuck. We need to make sure however that the check of
	 * OCFS2_LOCK_FREEING and the extra reference are atomic with
	 * respect to a reference decrement or the setting of that
	 * flag.
	 */
	spin_lock_irqsave(&lockres->l_lock, flags);
	spin_lock(&dentry_attach_lock);
	अगर (!(lockres->l_flags & OCFS2_LOCK_FREEING)
	    && dl->dl_count) अणु
		dl->dl_count++;
		extra_ref = 1;
	पूर्ण
	spin_unlock(&dentry_attach_lock);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	mlog(0, "extra_ref = %d\n", extra_ref);

	/*
	 * We have a process रुकोing on us in ocfs2_dentry_iput(),
	 * which means we can't have any more outstanding
	 * aliases. There's no need to करो any more work.
	 */
	अगर (!extra_ref)
		वापस UNBLOCK_CONTINUE;

	spin_lock(&dentry_attach_lock);
	जबतक (1) अणु
		dentry = ocfs2_find_local_alias(dl->dl_inode,
						dl->dl_parent_blkno, 1);
		अगर (!dentry)
			अवरोध;
		spin_unlock(&dentry_attach_lock);

		अगर (S_ISसूची(dl->dl_inode->i_mode))
			shrink_dcache_parent(dentry);

		mlog(0, "d_delete(%pd);\n", dentry);

		/*
		 * The following dcache calls may करो an
		 * iput(). Normally we करोn't want that from the
		 * करोwnconverting thपढ़ो, but in this हाल it's ok
		 * because the requesting node alपढ़ोy has an
		 * exclusive lock on the inode, so it can't be queued
		 * क्रम a करोwnconvert.
		 */
		d_delete(dentry);
		dput(dentry);

		spin_lock(&dentry_attach_lock);
	पूर्ण
	spin_unlock(&dentry_attach_lock);

	/*
	 * If we are the last holder of this dentry lock, there is no
	 * reason to करोwnconvert so skip straight to the unlock.
	 */
	अगर (dl->dl_count == 1)
		वापस UNBLOCK_STOP_POST;

	वापस UNBLOCK_CONTINUE_POST;
पूर्ण

अटल पूर्णांक ocfs2_check_refcount_करोwnconvert(काष्ठा ocfs2_lock_res *lockres,
					    पूर्णांक new_level)
अणु
	काष्ठा ocfs2_refcount_tree *tree =
				ocfs2_lock_res_refcount_tree(lockres);

	वापस ocfs2_ci_checkpoपूर्णांकed(&tree->rf_ci, lockres, new_level);
पूर्ण

अटल पूर्णांक ocfs2_refcount_convert_worker(काष्ठा ocfs2_lock_res *lockres,
					 पूर्णांक blocking)
अणु
	काष्ठा ocfs2_refcount_tree *tree =
				ocfs2_lock_res_refcount_tree(lockres);

	ocfs2_metadata_cache_purge(&tree->rf_ci);

	वापस UNBLOCK_CONTINUE;
पूर्ण

अटल व्योम ocfs2_set_qinfo_lvb(काष्ठा ocfs2_lock_res *lockres)
अणु
	काष्ठा ocfs2_qinfo_lvb *lvb;
	काष्ठा ocfs2_mem_dqinfo *oinfo = ocfs2_lock_res_qinfo(lockres);
	काष्ठा mem_dqinfo *info = sb_dqinfo(oinfo->dqi_gi.dqi_sb,
					    oinfo->dqi_gi.dqi_type);

	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
	lvb->lvb_version = OCFS2_QINFO_LVB_VERSION;
	lvb->lvb_bgrace = cpu_to_be32(info->dqi_bgrace);
	lvb->lvb_igrace = cpu_to_be32(info->dqi_igrace);
	lvb->lvb_syncms = cpu_to_be32(oinfo->dqi_syncms);
	lvb->lvb_blocks = cpu_to_be32(oinfo->dqi_gi.dqi_blocks);
	lvb->lvb_मुक्त_blk = cpu_to_be32(oinfo->dqi_gi.dqi_मुक्त_blk);
	lvb->lvb_मुक्त_entry = cpu_to_be32(oinfo->dqi_gi.dqi_मुक्त_entry);
पूर्ण

व्योम ocfs2_qinfo_unlock(काष्ठा ocfs2_mem_dqinfo *oinfo, पूर्णांक ex)
अणु
	काष्ठा ocfs2_lock_res *lockres = &oinfo->dqi_gqlock;
	काष्ठा ocfs2_super *osb = OCFS2_SB(oinfo->dqi_gi.dqi_sb);
	पूर्णांक level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;

	अगर (!ocfs2_is_hard_पढ़ोonly(osb) && !ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres, level);
पूर्ण

अटल पूर्णांक ocfs2_refresh_qinfo(काष्ठा ocfs2_mem_dqinfo *oinfo)
अणु
	काष्ठा mem_dqinfo *info = sb_dqinfo(oinfo->dqi_gi.dqi_sb,
					    oinfo->dqi_gi.dqi_type);
	काष्ठा ocfs2_lock_res *lockres = &oinfo->dqi_gqlock;
	काष्ठा ocfs2_qinfo_lvb *lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_global_disk_dqinfo *gdinfo;
	पूर्णांक status = 0;

	अगर (ocfs2_dlm_lvb_valid(&lockres->l_lksb) &&
	    lvb->lvb_version == OCFS2_QINFO_LVB_VERSION) अणु
		info->dqi_bgrace = be32_to_cpu(lvb->lvb_bgrace);
		info->dqi_igrace = be32_to_cpu(lvb->lvb_igrace);
		oinfo->dqi_syncms = be32_to_cpu(lvb->lvb_syncms);
		oinfo->dqi_gi.dqi_blocks = be32_to_cpu(lvb->lvb_blocks);
		oinfo->dqi_gi.dqi_मुक्त_blk = be32_to_cpu(lvb->lvb_मुक्त_blk);
		oinfo->dqi_gi.dqi_मुक्त_entry =
					be32_to_cpu(lvb->lvb_मुक्त_entry);
	पूर्ण अन्यथा अणु
		status = ocfs2_पढ़ो_quota_phys_block(oinfo->dqi_gqinode,
						     oinfo->dqi_giblk, &bh);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		gdinfo = (काष्ठा ocfs2_global_disk_dqinfo *)
					(bh->b_data + OCFS2_GLOBAL_INFO_OFF);
		info->dqi_bgrace = le32_to_cpu(gdinfo->dqi_bgrace);
		info->dqi_igrace = le32_to_cpu(gdinfo->dqi_igrace);
		oinfo->dqi_syncms = le32_to_cpu(gdinfo->dqi_syncms);
		oinfo->dqi_gi.dqi_blocks = le32_to_cpu(gdinfo->dqi_blocks);
		oinfo->dqi_gi.dqi_मुक्त_blk = le32_to_cpu(gdinfo->dqi_मुक्त_blk);
		oinfo->dqi_gi.dqi_मुक्त_entry =
					le32_to_cpu(gdinfo->dqi_मुक्त_entry);
		brअन्यथा(bh);
		ocfs2_track_lock_refresh(lockres);
	पूर्ण

bail:
	वापस status;
पूर्ण

/* Lock quota info, this function expects at least shared lock on the quota file
 * so that we can safely refresh quota info from disk. */
पूर्णांक ocfs2_qinfo_lock(काष्ठा ocfs2_mem_dqinfo *oinfo, पूर्णांक ex)
अणु
	काष्ठा ocfs2_lock_res *lockres = &oinfo->dqi_gqlock;
	काष्ठा ocfs2_super *osb = OCFS2_SB(oinfo->dqi_gi.dqi_sb);
	पूर्णांक level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	पूर्णांक status = 0;

	/* On RO devices, locking really isn't needed... */
	अगर (ocfs2_is_hard_पढ़ोonly(osb)) अणु
		अगर (ex)
			status = -EROFS;
		जाओ bail;
	पूर्ण
	अगर (ocfs2_mount_local(osb))
		जाओ bail;

	status = ocfs2_cluster_lock(osb, lockres, level, 0, 0);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	अगर (!ocfs2_should_refresh_lock_res(lockres))
		जाओ bail;
	/* OK, we have the lock but we need to refresh the quota info */
	status = ocfs2_refresh_qinfo(oinfo);
	अगर (status)
		ocfs2_qinfo_unlock(oinfo, ex);
	ocfs2_complete_lock_res_refresh(lockres, status);
bail:
	वापस status;
पूर्ण

पूर्णांक ocfs2_refcount_lock(काष्ठा ocfs2_refcount_tree *ref_tree, पूर्णांक ex)
अणु
	पूर्णांक status;
	पूर्णांक level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	काष्ठा ocfs2_lock_res *lockres = &ref_tree->rf_lockres;
	काष्ठा ocfs2_super *osb = lockres->l_priv;


	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		वापस -EROFS;

	अगर (ocfs2_mount_local(osb))
		वापस 0;

	status = ocfs2_cluster_lock(osb, lockres, level, 0, 0);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

व्योम ocfs2_refcount_unlock(काष्ठा ocfs2_refcount_tree *ref_tree, पूर्णांक ex)
अणु
	पूर्णांक level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	काष्ठा ocfs2_lock_res *lockres = &ref_tree->rf_lockres;
	काष्ठा ocfs2_super *osb = lockres->l_priv;

	अगर (!ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres, level);
पूर्ण

अटल व्योम ocfs2_process_blocked_lock(काष्ठा ocfs2_super *osb,
				       काष्ठा ocfs2_lock_res *lockres)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_unblock_ctl ctl = अणु0, 0,पूर्ण;
	अचिन्हित दीर्घ flags;

	/* Our reference to the lockres in this function can be
	 * considered valid until we हटाओ the OCFS2_LOCK_QUEUED
	 * flag. */

	BUG_ON(!lockres);
	BUG_ON(!lockres->l_ops);

	mlog(ML_BASTS, "lockres %s blocked\n", lockres->l_name);

	/* Detect whether a lock has been marked as going away जबतक
	 * the करोwnconvert thपढ़ो was processing other things. A lock can
	 * still be marked with OCFS2_LOCK_FREEING after this check,
	 * but लघु circuiting here will still save us some
	 * perक्रमmance. */
	spin_lock_irqsave(&lockres->l_lock, flags);
	अगर (lockres->l_flags & OCFS2_LOCK_FREEING)
		जाओ unqueue;
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	status = ocfs2_unblock_lock(osb, lockres, &ctl);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	spin_lock_irqsave(&lockres->l_lock, flags);
unqueue:
	अगर (lockres->l_flags & OCFS2_LOCK_FREEING || !ctl.requeue) अणु
		lockres_clear_flags(lockres, OCFS2_LOCK_QUEUED);
	पूर्ण अन्यथा
		ocfs2_schedule_blocked_lock(osb, lockres);

	mlog(ML_BASTS, "lockres %s, requeue = %s.\n", lockres->l_name,
	     ctl.requeue ? "yes" : "no");
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	अगर (ctl.unblock_action != UNBLOCK_CONTINUE
	    && lockres->l_ops->post_unlock)
		lockres->l_ops->post_unlock(osb, lockres);
पूर्ण

अटल व्योम ocfs2_schedule_blocked_lock(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_lock_res *lockres)
अणु
	अचिन्हित दीर्घ flags;

	निश्चित_spin_locked(&lockres->l_lock);

	अगर (lockres->l_flags & OCFS2_LOCK_FREEING) अणु
		/* Do not schedule a lock क्रम करोwnconvert when it's on
		 * the way to deकाष्ठाion - any nodes wanting access
		 * to the resource will get it soon. */
		mlog(ML_BASTS, "lockres %s won't be scheduled: flags 0x%lx\n",
		     lockres->l_name, lockres->l_flags);
		वापस;
	पूर्ण

	lockres_or_flags(lockres, OCFS2_LOCK_QUEUED);

	spin_lock_irqsave(&osb->dc_task_lock, flags);
	अगर (list_empty(&lockres->l_blocked_list)) अणु
		list_add_tail(&lockres->l_blocked_list,
			      &osb->blocked_lock_list);
		osb->blocked_lock_count++;
	पूर्ण
	spin_unlock_irqrestore(&osb->dc_task_lock, flags);
पूर्ण

अटल व्योम ocfs2_करोwnconvert_thपढ़ो_करो_work(काष्ठा ocfs2_super *osb)
अणु
	अचिन्हित दीर्घ processed;
	अचिन्हित दीर्घ flags;
	काष्ठा ocfs2_lock_res *lockres;

	spin_lock_irqsave(&osb->dc_task_lock, flags);
	/* grab this early so we know to try again अगर a state change and
	 * wake happens part-way through our work  */
	osb->dc_work_sequence = osb->dc_wake_sequence;

	processed = osb->blocked_lock_count;
	/*
	 * blocked lock processing in this loop might call iput which can
	 * हटाओ items off osb->blocked_lock_list. Downconvert up to
	 * 'processed' number of locks, but stop लघु अगर we had some
	 * हटाओd in ocfs2_mark_lockres_मुक्तing when करोwnconverting.
	 */
	जबतक (processed && !list_empty(&osb->blocked_lock_list)) अणु
		lockres = list_entry(osb->blocked_lock_list.next,
				     काष्ठा ocfs2_lock_res, l_blocked_list);
		list_del_init(&lockres->l_blocked_list);
		osb->blocked_lock_count--;
		spin_unlock_irqrestore(&osb->dc_task_lock, flags);

		BUG_ON(!processed);
		processed--;

		ocfs2_process_blocked_lock(osb, lockres);

		spin_lock_irqsave(&osb->dc_task_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&osb->dc_task_lock, flags);
पूर्ण

अटल पूर्णांक ocfs2_करोwnconvert_thपढ़ो_lists_empty(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक empty = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osb->dc_task_lock, flags);
	अगर (list_empty(&osb->blocked_lock_list))
		empty = 1;

	spin_unlock_irqrestore(&osb->dc_task_lock, flags);
	वापस empty;
पूर्ण

अटल पूर्णांक ocfs2_करोwnconvert_thपढ़ो_should_wake(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक should_wake = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osb->dc_task_lock, flags);
	अगर (osb->dc_work_sequence != osb->dc_wake_sequence)
		should_wake = 1;
	spin_unlock_irqrestore(&osb->dc_task_lock, flags);

	वापस should_wake;
पूर्ण

अटल पूर्णांक ocfs2_करोwnconvert_thपढ़ो(व्योम *arg)
अणु
	काष्ठा ocfs2_super *osb = arg;

	/* only quit once we've been asked to stop and there is no more
	 * work available */
	जबतक (!(kthपढ़ो_should_stop() &&
		ocfs2_करोwnconvert_thपढ़ो_lists_empty(osb))) अणु

		रुको_event_पूर्णांकerruptible(osb->dc_event,
					 ocfs2_करोwnconvert_thपढ़ो_should_wake(osb) ||
					 kthपढ़ो_should_stop());

		mlog(0, "downconvert_thread: awoken\n");

		ocfs2_करोwnconvert_thपढ़ो_करो_work(osb);
	पूर्ण

	osb->dc_task = शून्य;
	वापस 0;
पूर्ण

व्योम ocfs2_wake_करोwnconvert_thपढ़ो(काष्ठा ocfs2_super *osb)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osb->dc_task_lock, flags);
	/* make sure the voting thपढ़ो माला_लो a swipe at whatever changes
	 * the caller may have made to the voting state */
	osb->dc_wake_sequence++;
	spin_unlock_irqrestore(&osb->dc_task_lock, flags);
	wake_up(&osb->dc_event);
पूर्ण
