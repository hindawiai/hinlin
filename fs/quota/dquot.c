<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementation of the diskquota प्रणाली क्रम the LINUX operating प्रणाली. QUOTA
 * is implemented using the BSD प्रणाली call पूर्णांकerface as the means of
 * communication with the user level. This file contains the generic routines
 * called by the dअगरferent fileप्रणालीs on allocation of an inode or block.
 * These routines take care of the administration needed to have a consistent
 * diskquota tracking प्रणाली. The ideas of both user and group quotas are based
 * on the Melbourne quota प्रणाली as used on BSD derived प्रणालीs. The पूर्णांकernal
 * implementation is based on one of the several variants of the LINUX
 * inode-subप्रणाली with added complनिकासy of the diskquota प्रणाली.
 *
 * Author:	Marco van Wieringen <mvw@planets.elm.net>
 *
 * Fixes:   Dmitry Gorodchanin <pgmdsg@ibi.com>, 11 Feb 96
 *
 *		Revised list management to aव्योम races
 *		-- Bill Hawes, <whawes@star.net>, 9/98
 *
 *		Fixed races in dquot_transfer(), dqget() and dquot_alloc_...().
 *		As the consequence the locking was moved from dquot_decr_...(),
 *		dquot_incr_...() to calling functions.
 *		invalidate_dquots() now ग_लिखोs modअगरied dquots.
 *		Serialized quota_off() and quota_on() क्रम mount poपूर्णांक.
 *		Fixed a few bugs in grow_dquots().
 *		Fixed deadlock in ग_लिखो_dquot() - we no दीर्घer account quotas on
 *		quota files
 *		हटाओ_dquot_ref() moved to inode.c - it now traverses through inodes
 *		add_dquot_ref() restarts after blocking
 *		Added check क्रम bogus uid and fixed check क्रम group in quotactl.
 *		Jan Kara, <jack@suse.cz>, sponsored by SuSE CR, 10-11/99
 *
 *		Used काष्ठा list_head instead of own list काष्ठा
 *		Invalidation of referenced dquots is no दीर्घer possible
 *		Improved मुक्त_dquots list management
 *		Quota and i_blocks are now updated in one place to aव्योम races
 *		Warnings are now delayed so we won't block in critical section
 *		Write updated not to require dquot lock
 *		Jan Kara, <jack@suse.cz>, 9/2000
 *
 *		Added dynamic quota काष्ठाure allocation
 *		Jan Kara <jack@suse.cz> 12/2000
 *
 *		Rewritten quota पूर्णांकerface. Implemented new quota क्रमmat and
 *		क्रमmats रेजिस्टरing.
 *		Jan Kara, <jack@suse.cz>, 2001,2002
 *
 *		New SMP locking.
 *		Jan Kara, <jack@suse.cz>, 10/2002
 *
 *		Added journalled quota support, fix lock inversion problems
 *		Jan Kara, <jack@suse.cz>, 2003,2004
 *
 * (C) Copyright 1994 - 1997 Marco van Wieringen
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/mm.h>
#समावेश <linux/समय.स>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/tty.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/security.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/kmod.h>
#समावेश <linux/namei.h>
#समावेश <linux/capability.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/blkdev.h>
#समावेश "../internal.h" /* ugh */

#समावेश <linux/uaccess.h>

/*
 * There are five quota SMP locks:
 * * dq_list_lock protects all lists with quotas and quota क्रमmats.
 * * dquot->dq_dqb_lock protects data from dq_dqb
 * * inode->i_lock protects inode->i_blocks, i_bytes and also guards
 *   consistency of dquot->dq_dqb with inode->i_blocks, i_bytes so that
 *   dquot_transfer() can stabilize amount it transfers
 * * dq_data_lock protects mem_dqinfo काष्ठाures and modअगरications of dquot
 *   poपूर्णांकers in the inode
 * * dq_state_lock protects modअगरications of quota state (on quotaon and
 *   quotaoff) and पढ़ोers who care about latest values take it as well.
 *
 * The spinlock ordering is hence:
 *   dq_data_lock > dq_list_lock > i_lock > dquot->dq_dqb_lock,
 *   dq_list_lock > dq_state_lock
 *
 * Note that some things (eg. sb poपूर्णांकer, type, id) करोesn't change during
 * the lअगरe of the dquot काष्ठाure and so needn't to be रक्षित by a lock
 *
 * Operation accessing dquots via inode poपूर्णांकers are रक्षित by dquot_srcu.
 * Operation of पढ़ोing poपूर्णांकer needs srcu_पढ़ो_lock(&dquot_srcu), and
 * synchronize_srcu(&dquot_srcu) is called after clearing poपूर्णांकers from
 * inode and beक्रमe dropping dquot references to aव्योम use of dquots after
 * they are मुक्तd. dq_data_lock is used to serialize the poपूर्णांकer setting and
 * clearing operations.
 * Special care needs to be taken about S_NOQUOTA inode flag (marking that
 * inode is a quota file). Functions adding poपूर्णांकers from inode to dquots have
 * to check this flag under dq_data_lock and then (अगर S_NOQUOTA is not set) they
 * have to करो all poपूर्णांकer modअगरications beक्रमe dropping dq_data_lock. This makes
 * sure they cannot race with quotaon which first sets S_NOQUOTA flag and
 * then drops all poपूर्णांकers to dquots from an inode.
 *
 * Each dquot has its dq_lock mutex.  Dquot is locked when it is being पढ़ो to
 * memory (or space क्रम it is being allocated) on the first dqget(), when it is
 * being written out, and when it is being released on the last dqput(). The
 * allocation and release operations are serialized by the dq_lock and by
 * checking the use count in dquot_release().
 *
 * Lock ordering (including related VFS locks) is the following:
 *   s_umount > i_mutex > journal_lock > dquot->dq_lock > dqio_sem
 */

अटल __cacheline_aligned_in_smp DEFINE_SPINLOCK(dq_list_lock);
अटल __cacheline_aligned_in_smp DEFINE_SPINLOCK(dq_state_lock);
__cacheline_aligned_in_smp DEFINE_SPINLOCK(dq_data_lock);
EXPORT_SYMBOL(dq_data_lock);
DEFINE_STATIC_SRCU(dquot_srcu);

अटल DECLARE_WAIT_QUEUE_HEAD(dquot_ref_wq);

व्योम __quota_error(काष्ठा super_block *sb, स्थिर अक्षर *func,
		   स्थिर अक्षर *fmt, ...)
अणु
	अगर (prपूर्णांकk_ratelimit()) अणु
		बहु_सूची args;
		काष्ठा va_क्रमmat vaf;

		बहु_शुरू(args, fmt);

		vaf.fmt = fmt;
		vaf.va = &args;

		prपूर्णांकk(KERN_ERR "Quota error (device %s): %s: %pV\n",
		       sb->s_id, func, &vaf);

		बहु_पूर्ण(args);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__quota_error);

#अगर defined(CONFIG_QUOTA_DEBUG) || defined(CONFIG_PRINT_QUOTA_WARNING)
अटल अक्षर *quotatypes[] = INITQFNAMES;
#पूर्ण_अगर
अटल काष्ठा quota_क्रमmat_type *quota_क्रमmats;	/* List of रेजिस्टरed क्रमmats */
अटल काष्ठा quota_module_name module_names[] = INIT_QUOTA_MODULE_NAMES;

/* SLAB cache क्रम dquot काष्ठाures */
अटल काष्ठा kmem_cache *dquot_cachep;

पूर्णांक रेजिस्टर_quota_क्रमmat(काष्ठा quota_क्रमmat_type *fmt)
अणु
	spin_lock(&dq_list_lock);
	fmt->qf_next = quota_क्रमmats;
	quota_क्रमmats = fmt;
	spin_unlock(&dq_list_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_quota_क्रमmat);

व्योम unरेजिस्टर_quota_क्रमmat(काष्ठा quota_क्रमmat_type *fmt)
अणु
	काष्ठा quota_क्रमmat_type **actqf;

	spin_lock(&dq_list_lock);
	क्रम (actqf = &quota_क्रमmats; *actqf && *actqf != fmt;
	     actqf = &(*actqf)->qf_next)
		;
	अगर (*actqf)
		*actqf = (*actqf)->qf_next;
	spin_unlock(&dq_list_lock);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_quota_क्रमmat);

अटल काष्ठा quota_क्रमmat_type *find_quota_क्रमmat(पूर्णांक id)
अणु
	काष्ठा quota_क्रमmat_type *actqf;

	spin_lock(&dq_list_lock);
	क्रम (actqf = quota_क्रमmats; actqf && actqf->qf_fmt_id != id;
	     actqf = actqf->qf_next)
		;
	अगर (!actqf || !try_module_get(actqf->qf_owner)) अणु
		पूर्णांक qm;

		spin_unlock(&dq_list_lock);

		क्रम (qm = 0; module_names[qm].qm_fmt_id &&
			     module_names[qm].qm_fmt_id != id; qm++)
			;
		अगर (!module_names[qm].qm_fmt_id ||
		    request_module(module_names[qm].qm_mod_name))
			वापस शून्य;

		spin_lock(&dq_list_lock);
		क्रम (actqf = quota_क्रमmats; actqf && actqf->qf_fmt_id != id;
		     actqf = actqf->qf_next)
			;
		अगर (actqf && !try_module_get(actqf->qf_owner))
			actqf = शून्य;
	पूर्ण
	spin_unlock(&dq_list_lock);
	वापस actqf;
पूर्ण

अटल व्योम put_quota_क्रमmat(काष्ठा quota_क्रमmat_type *fmt)
अणु
	module_put(fmt->qf_owner);
पूर्ण

/*
 * Dquot List Management:
 * The quota code uses four lists क्रम dquot management: the inuse_list,
 * मुक्त_dquots, dqi_dirty_list, and dquot_hash[] array. A single dquot
 * काष्ठाure may be on some of those lists, depending on its current state.
 *
 * All dquots are placed to the end of inuse_list when first created, and this
 * list is used क्रम invalidate operation, which must look at every dquot.
 *
 * Unused dquots (dq_count == 0) are added to the मुक्त_dquots list when मुक्तd,
 * and this list is searched whenever we need an available dquot.  Dquots are
 * हटाओd from the list as soon as they are used again, and
 * dqstats.मुक्त_dquots gives the number of dquots on the list. When
 * dquot is invalidated it's completely released from memory.
 *
 * Dirty dquots are added to the dqi_dirty_list of quota_info when mark
 * dirtied, and this list is searched when writing dirty dquots back to
 * quota file. Note that some fileप्रणालीs करो dirty dquot tracking on their
 * own (e.g. in a journal) and thus करोn't use dqi_dirty_list.
 *
 * Dquots with a specअगरic identity (device, type and id) are placed on
 * one of the dquot_hash[] hash chains. The provides an efficient search
 * mechanism to locate a specअगरic dquot.
 */

अटल LIST_HEAD(inuse_list);
अटल LIST_HEAD(मुक्त_dquots);
अटल अचिन्हित पूर्णांक dq_hash_bits, dq_hash_mask;
अटल काष्ठा hlist_head *dquot_hash;

काष्ठा dqstats dqstats;
EXPORT_SYMBOL(dqstats);

अटल qमाप_प्रकार inode_get_rsv_space(काष्ठा inode *inode);
अटल qमाप_प्रकार __inode_get_rsv_space(काष्ठा inode *inode);
अटल पूर्णांक __dquot_initialize(काष्ठा inode *inode, पूर्णांक type);

अटल अंतरभूत अचिन्हित पूर्णांक
hashfn(स्थिर काष्ठा super_block *sb, काष्ठा kqid qid)
अणु
	अचिन्हित पूर्णांक id = from_kqid(&init_user_ns, qid);
	पूर्णांक type = qid.type;
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = (((अचिन्हित दीर्घ)sb>>L1_CACHE_SHIFT) ^ id) * (MAXQUOTAS - type);
	वापस (पंचांगp + (पंचांगp >> dq_hash_bits)) & dq_hash_mask;
पूर्ण

/*
 * Following list functions expect dq_list_lock to be held
 */
अटल अंतरभूत व्योम insert_dquot_hash(काष्ठा dquot *dquot)
अणु
	काष्ठा hlist_head *head;
	head = dquot_hash + hashfn(dquot->dq_sb, dquot->dq_id);
	hlist_add_head(&dquot->dq_hash, head);
पूर्ण

अटल अंतरभूत व्योम हटाओ_dquot_hash(काष्ठा dquot *dquot)
अणु
	hlist_del_init(&dquot->dq_hash);
पूर्ण

अटल काष्ठा dquot *find_dquot(अचिन्हित पूर्णांक hashent, काष्ठा super_block *sb,
				काष्ठा kqid qid)
अणु
	काष्ठा dquot *dquot;

	hlist_क्रम_each_entry(dquot, dquot_hash+hashent, dq_hash)
		अगर (dquot->dq_sb == sb && qid_eq(dquot->dq_id, qid))
			वापस dquot;

	वापस शून्य;
पूर्ण

/* Add a dquot to the tail of the मुक्त list */
अटल अंतरभूत व्योम put_dquot_last(काष्ठा dquot *dquot)
अणु
	list_add_tail(&dquot->dq_मुक्त, &मुक्त_dquots);
	dqstats_inc(DQST_FREE_DQUOTS);
पूर्ण

अटल अंतरभूत व्योम हटाओ_मुक्त_dquot(काष्ठा dquot *dquot)
अणु
	अगर (list_empty(&dquot->dq_मुक्त))
		वापस;
	list_del_init(&dquot->dq_मुक्त);
	dqstats_dec(DQST_FREE_DQUOTS);
पूर्ण

अटल अंतरभूत व्योम put_inuse(काष्ठा dquot *dquot)
अणु
	/* We add to the back of inuse list so we करोn't have to restart
	 * when traversing this list and we block */
	list_add_tail(&dquot->dq_inuse, &inuse_list);
	dqstats_inc(DQST_ALLOC_DQUOTS);
पूर्ण

अटल अंतरभूत व्योम हटाओ_inuse(काष्ठा dquot *dquot)
अणु
	dqstats_dec(DQST_ALLOC_DQUOTS);
	list_del(&dquot->dq_inuse);
पूर्ण
/*
 * End of list functions needing dq_list_lock
 */

अटल व्योम रुको_on_dquot(काष्ठा dquot *dquot)
अणु
	mutex_lock(&dquot->dq_lock);
	mutex_unlock(&dquot->dq_lock);
पूर्ण

अटल अंतरभूत पूर्णांक dquot_dirty(काष्ठा dquot *dquot)
अणु
	वापस test_bit(DQ_MOD_B, &dquot->dq_flags);
पूर्ण

अटल अंतरभूत पूर्णांक mark_dquot_dirty(काष्ठा dquot *dquot)
अणु
	वापस dquot->dq_sb->dq_op->mark_dirty(dquot);
पूर्ण

/* Mark dquot dirty in atomic manner, and वापस it's old dirty flag state */
पूर्णांक dquot_mark_dquot_dirty(काष्ठा dquot *dquot)
अणु
	पूर्णांक ret = 1;

	अगर (!test_bit(DQ_ACTIVE_B, &dquot->dq_flags))
		वापस 0;

	अगर (sb_dqopt(dquot->dq_sb)->flags & DQUOT_NOLIST_सूचीTY)
		वापस test_and_set_bit(DQ_MOD_B, &dquot->dq_flags);

	/* If quota is dirty alपढ़ोy, we करोn't have to acquire dq_list_lock */
	अगर (test_bit(DQ_MOD_B, &dquot->dq_flags))
		वापस 1;

	spin_lock(&dq_list_lock);
	अगर (!test_and_set_bit(DQ_MOD_B, &dquot->dq_flags)) अणु
		list_add(&dquot->dq_dirty, &sb_dqopt(dquot->dq_sb)->
				info[dquot->dq_id.type].dqi_dirty_list);
		ret = 0;
	पूर्ण
	spin_unlock(&dq_list_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dquot_mark_dquot_dirty);

/* Dirtअगरy all the dquots - this can block when journalling */
अटल अंतरभूत पूर्णांक mark_all_dquot_dirty(काष्ठा dquot * स्थिर *dquot)
अणु
	पूर्णांक ret, err, cnt;

	ret = err = 0;
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (dquot[cnt])
			/* Even in हाल of error we have to जारी */
			ret = mark_dquot_dirty(dquot[cnt]);
		अगर (!err)
			err = ret;
	पूर्ण
	वापस err;
पूर्ण

अटल अंतरभूत व्योम dqput_all(काष्ठा dquot **dquot)
अणु
	अचिन्हित पूर्णांक cnt;

	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++)
		dqput(dquot[cnt]);
पूर्ण

अटल अंतरभूत पूर्णांक clear_dquot_dirty(काष्ठा dquot *dquot)
अणु
	अगर (sb_dqopt(dquot->dq_sb)->flags & DQUOT_NOLIST_सूचीTY)
		वापस test_and_clear_bit(DQ_MOD_B, &dquot->dq_flags);

	spin_lock(&dq_list_lock);
	अगर (!test_and_clear_bit(DQ_MOD_B, &dquot->dq_flags)) अणु
		spin_unlock(&dq_list_lock);
		वापस 0;
	पूर्ण
	list_del_init(&dquot->dq_dirty);
	spin_unlock(&dq_list_lock);
	वापस 1;
पूर्ण

व्योम mark_info_dirty(काष्ठा super_block *sb, पूर्णांक type)
अणु
	spin_lock(&dq_data_lock);
	sb_dqopt(sb)->info[type].dqi_flags |= DQF_INFO_सूचीTY;
	spin_unlock(&dq_data_lock);
पूर्ण
EXPORT_SYMBOL(mark_info_dirty);

/*
 *	Read dquot from disk and alloc space क्रम it
 */

पूर्णांक dquot_acquire(काष्ठा dquot *dquot)
अणु
	पूर्णांक ret = 0, ret2 = 0;
	काष्ठा quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	mutex_lock(&dquot->dq_lock);
	अगर (!test_bit(DQ_READ_B, &dquot->dq_flags)) अणु
		ret = dqopt->ops[dquot->dq_id.type]->पढ़ो_dqblk(dquot);
		अगर (ret < 0)
			जाओ out_iolock;
	पूर्ण
	/* Make sure flags update is visible after dquot has been filled */
	smp_mb__beक्रमe_atomic();
	set_bit(DQ_READ_B, &dquot->dq_flags);
	/* Instantiate dquot अगर needed */
	अगर (!test_bit(DQ_ACTIVE_B, &dquot->dq_flags) && !dquot->dq_off) अणु
		ret = dqopt->ops[dquot->dq_id.type]->commit_dqblk(dquot);
		/* Write the info अगर needed */
		अगर (info_dirty(&dqopt->info[dquot->dq_id.type])) अणु
			ret2 = dqopt->ops[dquot->dq_id.type]->ग_लिखो_file_info(
					dquot->dq_sb, dquot->dq_id.type);
		पूर्ण
		अगर (ret < 0)
			जाओ out_iolock;
		अगर (ret2 < 0) अणु
			ret = ret2;
			जाओ out_iolock;
		पूर्ण
	पूर्ण
	/*
	 * Make sure flags update is visible after on-disk काष्ठा has been
	 * allocated. Paired with smp_rmb() in dqget().
	 */
	smp_mb__beक्रमe_atomic();
	set_bit(DQ_ACTIVE_B, &dquot->dq_flags);
out_iolock:
	mutex_unlock(&dquot->dq_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dquot_acquire);

/*
 *	Write dquot to disk
 */
पूर्णांक dquot_commit(काष्ठा dquot *dquot)
अणु
	पूर्णांक ret = 0;
	काष्ठा quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	mutex_lock(&dquot->dq_lock);
	अगर (!clear_dquot_dirty(dquot))
		जाओ out_lock;
	/* Inactive dquot can be only अगर there was error during पढ़ो/init
	 * => we have better not writing it */
	अगर (test_bit(DQ_ACTIVE_B, &dquot->dq_flags))
		ret = dqopt->ops[dquot->dq_id.type]->commit_dqblk(dquot);
	अन्यथा
		ret = -EIO;
out_lock:
	mutex_unlock(&dquot->dq_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dquot_commit);

/*
 *	Release dquot
 */
पूर्णांक dquot_release(काष्ठा dquot *dquot)
अणु
	पूर्णांक ret = 0, ret2 = 0;
	काष्ठा quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	mutex_lock(&dquot->dq_lock);
	/* Check whether we are not racing with some other dqget() */
	अगर (dquot_is_busy(dquot))
		जाओ out_dqlock;
	अगर (dqopt->ops[dquot->dq_id.type]->release_dqblk) अणु
		ret = dqopt->ops[dquot->dq_id.type]->release_dqblk(dquot);
		/* Write the info */
		अगर (info_dirty(&dqopt->info[dquot->dq_id.type])) अणु
			ret2 = dqopt->ops[dquot->dq_id.type]->ग_लिखो_file_info(
						dquot->dq_sb, dquot->dq_id.type);
		पूर्ण
		अगर (ret >= 0)
			ret = ret2;
	पूर्ण
	clear_bit(DQ_ACTIVE_B, &dquot->dq_flags);
out_dqlock:
	mutex_unlock(&dquot->dq_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dquot_release);

व्योम dquot_destroy(काष्ठा dquot *dquot)
अणु
	kmem_cache_मुक्त(dquot_cachep, dquot);
पूर्ण
EXPORT_SYMBOL(dquot_destroy);

अटल अंतरभूत व्योम करो_destroy_dquot(काष्ठा dquot *dquot)
अणु
	dquot->dq_sb->dq_op->destroy_dquot(dquot);
पूर्ण

/* Invalidate all dquots on the list. Note that this function is called after
 * quota is disabled and poपूर्णांकers from inodes हटाओd so there cannot be new
 * quota users. There can still be some users of quotas due to inodes being
 * just deleted or pruned by prune_icache() (those are not attached to any
 * list) or parallel quotactl call. We have to रुको क्रम such users.
 */
अटल व्योम invalidate_dquots(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा dquot *dquot, *पंचांगp;

restart:
	spin_lock(&dq_list_lock);
	list_क्रम_each_entry_safe(dquot, पंचांगp, &inuse_list, dq_inuse) अणु
		अगर (dquot->dq_sb != sb)
			जारी;
		अगर (dquot->dq_id.type != type)
			जारी;
		/* Wait क्रम dquot users */
		अगर (atomic_पढ़ो(&dquot->dq_count)) अणु
			dqgrab(dquot);
			spin_unlock(&dq_list_lock);
			/*
			 * Once dqput() wakes us up, we know it's समय to मुक्त
			 * the dquot.
			 * IMPORTANT: we rely on the fact that there is always
			 * at most one process रुकोing क्रम dquot to मुक्त.
			 * Otherwise dq_count would be > 1 and we would never
			 * wake up.
			 */
			रुको_event(dquot_ref_wq,
				   atomic_पढ़ो(&dquot->dq_count) == 1);
			dqput(dquot);
			/* At this moment dquot() need not exist (it could be
			 * reclaimed by prune_dqcache(). Hence we must
			 * restart. */
			जाओ restart;
		पूर्ण
		/*
		 * Quota now has no users and it has been written on last
		 * dqput()
		 */
		हटाओ_dquot_hash(dquot);
		हटाओ_मुक्त_dquot(dquot);
		हटाओ_inuse(dquot);
		करो_destroy_dquot(dquot);
	पूर्ण
	spin_unlock(&dq_list_lock);
पूर्ण

/* Call callback क्रम every active dquot on given fileप्रणाली */
पूर्णांक dquot_scan_active(काष्ठा super_block *sb,
		      पूर्णांक (*fn)(काष्ठा dquot *dquot, अचिन्हित दीर्घ priv),
		      अचिन्हित दीर्घ priv)
अणु
	काष्ठा dquot *dquot, *old_dquot = शून्य;
	पूर्णांक ret = 0;

	WARN_ON_ONCE(!rwsem_is_locked(&sb->s_umount));

	spin_lock(&dq_list_lock);
	list_क्रम_each_entry(dquot, &inuse_list, dq_inuse) अणु
		अगर (!test_bit(DQ_ACTIVE_B, &dquot->dq_flags))
			जारी;
		अगर (dquot->dq_sb != sb)
			जारी;
		/* Now we have active dquot so we can just increase use count */
		atomic_inc(&dquot->dq_count);
		spin_unlock(&dq_list_lock);
		dqput(old_dquot);
		old_dquot = dquot;
		/*
		 * ->release_dquot() can be racing with us. Our reference
		 * protects us from new calls to it so just रुको क्रम any
		 * outstanding call and recheck the DQ_ACTIVE_B after that.
		 */
		रुको_on_dquot(dquot);
		अगर (test_bit(DQ_ACTIVE_B, &dquot->dq_flags)) अणु
			ret = fn(dquot, priv);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
		spin_lock(&dq_list_lock);
		/* We are safe to जारी now because our dquot could not
		 * be moved out of the inuse list जबतक we hold the reference */
	पूर्ण
	spin_unlock(&dq_list_lock);
out:
	dqput(old_dquot);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dquot_scan_active);

/* Write all dquot काष्ठाures to quota files */
पूर्णांक dquot_ग_लिखोback_dquots(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा list_head dirty;
	काष्ठा dquot *dquot;
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	पूर्णांक cnt;
	पूर्णांक err, ret = 0;

	WARN_ON_ONCE(!rwsem_is_locked(&sb->s_umount));

	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (type != -1 && cnt != type)
			जारी;
		अगर (!sb_has_quota_active(sb, cnt))
			जारी;
		spin_lock(&dq_list_lock);
		/* Move list away to aव्योम livelock. */
		list_replace_init(&dqopt->info[cnt].dqi_dirty_list, &dirty);
		जबतक (!list_empty(&dirty)) अणु
			dquot = list_first_entry(&dirty, काष्ठा dquot,
						 dq_dirty);

			WARN_ON(!test_bit(DQ_ACTIVE_B, &dquot->dq_flags));

			/* Now we have active dquot from which someone is
 			 * holding reference so we can safely just increase
			 * use count */
			dqgrab(dquot);
			spin_unlock(&dq_list_lock);
			err = sb->dq_op->ग_लिखो_dquot(dquot);
			अगर (err) अणु
				/*
				 * Clear dirty bit anyway to aव्योम infinite
				 * loop here.
				 */
				clear_dquot_dirty(dquot);
				अगर (!ret)
					ret = err;
			पूर्ण
			dqput(dquot);
			spin_lock(&dq_list_lock);
		पूर्ण
		spin_unlock(&dq_list_lock);
	पूर्ण

	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++)
		अगर ((cnt == type || type == -1) && sb_has_quota_active(sb, cnt)
		    && info_dirty(&dqopt->info[cnt]))
			sb->dq_op->ग_लिखो_info(sb, cnt);
	dqstats_inc(DQST_SYNCS);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dquot_ग_लिखोback_dquots);

/* Write all dquot काष्ठाures to disk and make them visible from userspace */
पूर्णांक dquot_quota_sync(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	पूर्णांक cnt;
	पूर्णांक ret;

	ret = dquot_ग_लिखोback_dquots(sb, type);
	अगर (ret)
		वापस ret;
	अगर (dqopt->flags & DQUOT_QUOTA_SYS_खाता)
		वापस 0;

	/* This is not very clever (and fast) but currently I करोn't know about
	 * any other simple way of getting quota data to disk and we must get
	 * them there क्रम userspace to be visible... */
	अगर (sb->s_op->sync_fs)
		sb->s_op->sync_fs(sb, 1);
	sync_blockdev(sb->s_bdev);

	/*
	 * Now when everything is written we can discard the pagecache so
	 * that userspace sees the changes.
	 */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (type != -1 && cnt != type)
			जारी;
		अगर (!sb_has_quota_active(sb, cnt))
			जारी;
		inode_lock(dqopt->files[cnt]);
		truncate_inode_pages(&dqopt->files[cnt]->i_data, 0);
		inode_unlock(dqopt->files[cnt]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dquot_quota_sync);

अटल अचिन्हित दीर्घ
dqcache_shrink_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	काष्ठा dquot *dquot;
	अचिन्हित दीर्घ मुक्तd = 0;

	spin_lock(&dq_list_lock);
	जबतक (!list_empty(&मुक्त_dquots) && sc->nr_to_scan) अणु
		dquot = list_first_entry(&मुक्त_dquots, काष्ठा dquot, dq_मुक्त);
		हटाओ_dquot_hash(dquot);
		हटाओ_मुक्त_dquot(dquot);
		हटाओ_inuse(dquot);
		करो_destroy_dquot(dquot);
		sc->nr_to_scan--;
		मुक्तd++;
	पूर्ण
	spin_unlock(&dq_list_lock);
	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ
dqcache_shrink_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	वापस vfs_pressure_ratio(
	percpu_counter_पढ़ो_positive(&dqstats.counter[DQST_FREE_DQUOTS]));
पूर्ण

अटल काष्ठा shrinker dqcache_shrinker = अणु
	.count_objects = dqcache_shrink_count,
	.scan_objects = dqcache_shrink_scan,
	.seeks = DEFAULT_SEEKS,
पूर्ण;

/*
 * Put reference to dquot
 */
व्योम dqput(काष्ठा dquot *dquot)
अणु
	पूर्णांक ret;

	अगर (!dquot)
		वापस;
#अगर_घोषित CONFIG_QUOTA_DEBUG
	अगर (!atomic_पढ़ो(&dquot->dq_count)) अणु
		quota_error(dquot->dq_sb, "trying to free free dquot of %s %d",
			    quotatypes[dquot->dq_id.type],
			    from_kqid(&init_user_ns, dquot->dq_id));
		BUG();
	पूर्ण
#पूर्ण_अगर
	dqstats_inc(DQST_DROPS);
we_slept:
	spin_lock(&dq_list_lock);
	अगर (atomic_पढ़ो(&dquot->dq_count) > 1) अणु
		/* We have more than one user... nothing to करो */
		atomic_dec(&dquot->dq_count);
		/* Releasing dquot during quotaoff phase? */
		अगर (!sb_has_quota_active(dquot->dq_sb, dquot->dq_id.type) &&
		    atomic_पढ़ो(&dquot->dq_count) == 1)
			wake_up(&dquot_ref_wq);
		spin_unlock(&dq_list_lock);
		वापस;
	पूर्ण
	/* Need to release dquot? */
	अगर (dquot_dirty(dquot)) अणु
		spin_unlock(&dq_list_lock);
		/* Commit dquot beक्रमe releasing */
		ret = dquot->dq_sb->dq_op->ग_लिखो_dquot(dquot);
		अगर (ret < 0) अणु
			quota_error(dquot->dq_sb, "Can't write quota structure"
				    " (error %d). Quota may get out of sync!",
				    ret);
			/*
			 * We clear dirty bit anyway, so that we aव्योम
			 * infinite loop here
			 */
			clear_dquot_dirty(dquot);
		पूर्ण
		जाओ we_slept;
	पूर्ण
	अगर (test_bit(DQ_ACTIVE_B, &dquot->dq_flags)) अणु
		spin_unlock(&dq_list_lock);
		dquot->dq_sb->dq_op->release_dquot(dquot);
		जाओ we_slept;
	पूर्ण
	atomic_dec(&dquot->dq_count);
#अगर_घोषित CONFIG_QUOTA_DEBUG
	/* sanity check */
	BUG_ON(!list_empty(&dquot->dq_मुक्त));
#पूर्ण_अगर
	put_dquot_last(dquot);
	spin_unlock(&dq_list_lock);
पूर्ण
EXPORT_SYMBOL(dqput);

काष्ठा dquot *dquot_alloc(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस kmem_cache_zalloc(dquot_cachep, GFP_NOFS);
पूर्ण
EXPORT_SYMBOL(dquot_alloc);

अटल काष्ठा dquot *get_empty_dquot(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा dquot *dquot;

	dquot = sb->dq_op->alloc_dquot(sb, type);
	अगर(!dquot)
		वापस शून्य;

	mutex_init(&dquot->dq_lock);
	INIT_LIST_HEAD(&dquot->dq_मुक्त);
	INIT_LIST_HEAD(&dquot->dq_inuse);
	INIT_HLIST_NODE(&dquot->dq_hash);
	INIT_LIST_HEAD(&dquot->dq_dirty);
	dquot->dq_sb = sb;
	dquot->dq_id = make_kqid_invalid(type);
	atomic_set(&dquot->dq_count, 1);
	spin_lock_init(&dquot->dq_dqb_lock);

	वापस dquot;
पूर्ण

/*
 * Get reference to dquot
 *
 * Locking is slightly tricky here. We are guarded from parallel quotaoff()
 * destroying our dquot by:
 *   a) checking क्रम quota flags under dq_list_lock and
 *   b) getting a reference to dquot beक्रमe we release dq_list_lock
 */
काष्ठा dquot *dqget(काष्ठा super_block *sb, काष्ठा kqid qid)
अणु
	अचिन्हित पूर्णांक hashent = hashfn(sb, qid);
	काष्ठा dquot *dquot, *empty = शून्य;

	अगर (!qid_has_mapping(sb->s_user_ns, qid))
		वापस ERR_PTR(-EINVAL);

        अगर (!sb_has_quota_active(sb, qid.type))
		वापस ERR_PTR(-ESRCH);
we_slept:
	spin_lock(&dq_list_lock);
	spin_lock(&dq_state_lock);
	अगर (!sb_has_quota_active(sb, qid.type)) अणु
		spin_unlock(&dq_state_lock);
		spin_unlock(&dq_list_lock);
		dquot = ERR_PTR(-ESRCH);
		जाओ out;
	पूर्ण
	spin_unlock(&dq_state_lock);

	dquot = find_dquot(hashent, sb, qid);
	अगर (!dquot) अणु
		अगर (!empty) अणु
			spin_unlock(&dq_list_lock);
			empty = get_empty_dquot(sb, qid.type);
			अगर (!empty)
				schedule();	/* Try to रुको क्रम a moment... */
			जाओ we_slept;
		पूर्ण
		dquot = empty;
		empty = शून्य;
		dquot->dq_id = qid;
		/* all dquots go on the inuse_list */
		put_inuse(dquot);
		/* hash it first so it can be found */
		insert_dquot_hash(dquot);
		spin_unlock(&dq_list_lock);
		dqstats_inc(DQST_LOOKUPS);
	पूर्ण अन्यथा अणु
		अगर (!atomic_पढ़ो(&dquot->dq_count))
			हटाओ_मुक्त_dquot(dquot);
		atomic_inc(&dquot->dq_count);
		spin_unlock(&dq_list_lock);
		dqstats_inc(DQST_CACHE_HITS);
		dqstats_inc(DQST_LOOKUPS);
	पूर्ण
	/* Wait क्रम dq_lock - after this we know that either dquot_release() is
	 * alपढ़ोy finished or it will be canceled due to dq_count > 1 test */
	रुको_on_dquot(dquot);
	/* Read the dquot / allocate space in quota file */
	अगर (!test_bit(DQ_ACTIVE_B, &dquot->dq_flags)) अणु
		पूर्णांक err;

		err = sb->dq_op->acquire_dquot(dquot);
		अगर (err < 0) अणु
			dqput(dquot);
			dquot = ERR_PTR(err);
			जाओ out;
		पूर्ण
	पूर्ण
	/*
	 * Make sure following पढ़ोs see filled काष्ठाure - paired with
	 * smp_mb__beक्रमe_atomic() in dquot_acquire().
	 */
	smp_rmb();
#अगर_घोषित CONFIG_QUOTA_DEBUG
	BUG_ON(!dquot->dq_sb);	/* Has somebody invalidated entry under us? */
#पूर्ण_अगर
out:
	अगर (empty)
		करो_destroy_dquot(empty);

	वापस dquot;
पूर्ण
EXPORT_SYMBOL(dqget);

अटल अंतरभूत काष्ठा dquot **i_dquot(काष्ठा inode *inode)
अणु
	वापस inode->i_sb->s_op->get_dquots(inode);
पूर्ण

अटल पूर्णांक dqinit_needed(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा dquot * स्थिर *dquots;
	पूर्णांक cnt;

	अगर (IS_NOQUOTA(inode))
		वापस 0;

	dquots = i_dquot(inode);
	अगर (type != -1)
		वापस !dquots[type];
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++)
		अगर (!dquots[cnt])
			वापस 1;
	वापस 0;
पूर्ण

/* This routine is guarded by s_umount semaphore */
अटल पूर्णांक add_dquot_ref(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा inode *inode, *old_inode = शून्य;
#अगर_घोषित CONFIG_QUOTA_DEBUG
	पूर्णांक reserved = 0;
#पूर्ण_अगर
	पूर्णांक err = 0;

	spin_lock(&sb->s_inode_list_lock);
	list_क्रम_each_entry(inode, &sb->s_inodes, i_sb_list) अणु
		spin_lock(&inode->i_lock);
		अगर ((inode->i_state & (I_FREEING|I_WILL_FREE|I_NEW)) ||
		    !atomic_पढ़ो(&inode->i_ग_लिखोcount) ||
		    !dqinit_needed(inode, type)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		__iget(inode);
		spin_unlock(&inode->i_lock);
		spin_unlock(&sb->s_inode_list_lock);

#अगर_घोषित CONFIG_QUOTA_DEBUG
		अगर (unlikely(inode_get_rsv_space(inode) > 0))
			reserved = 1;
#पूर्ण_अगर
		iput(old_inode);
		err = __dquot_initialize(inode, type);
		अगर (err) अणु
			iput(inode);
			जाओ out;
		पूर्ण

		/*
		 * We hold a reference to 'inode' so it couldn't have been
		 * हटाओd from s_inodes list जबतक we dropped the
		 * s_inode_list_lock. We cannot iput the inode now as we can be
		 * holding the last reference and we cannot iput it under
		 * s_inode_list_lock. So we keep the reference and iput it
		 * later.
		 */
		old_inode = inode;
		cond_resched();
		spin_lock(&sb->s_inode_list_lock);
	पूर्ण
	spin_unlock(&sb->s_inode_list_lock);
	iput(old_inode);
out:
#अगर_घोषित CONFIG_QUOTA_DEBUG
	अगर (reserved) अणु
		quota_error(sb, "Writes happened before quota was turned on "
			"thus quota information is probably inconsistent. "
			"Please run quotacheck(8)");
	पूर्ण
#पूर्ण_अगर
	वापस err;
पूर्ण

/*
 * Remove references to dquots from inode and add dquot to list क्रम मुक्तing
 * अगर we have the last reference to dquot
 */
अटल व्योम हटाओ_inode_dquot_ref(काष्ठा inode *inode, पूर्णांक type,
				   काष्ठा list_head *toमुक्त_head)
अणु
	काष्ठा dquot **dquots = i_dquot(inode);
	काष्ठा dquot *dquot = dquots[type];

	अगर (!dquot)
		वापस;

	dquots[type] = शून्य;
	अगर (list_empty(&dquot->dq_मुक्त)) अणु
		/*
		 * The inode still has reference to dquot so it can't be in the
		 * मुक्त list
		 */
		spin_lock(&dq_list_lock);
		list_add(&dquot->dq_मुक्त, toमुक्त_head);
		spin_unlock(&dq_list_lock);
	पूर्ण अन्यथा अणु
		/*
		 * Dquot is alपढ़ोy in a list to put so we won't drop the last
		 * reference here.
		 */
		dqput(dquot);
	पूर्ण
पूर्ण

/*
 * Free list of dquots
 * Dquots are हटाओd from inodes and no new references can be got so we are
 * the only ones holding reference
 */
अटल व्योम put_dquot_list(काष्ठा list_head *toमुक्त_head)
अणु
	काष्ठा list_head *act_head;
	काष्ठा dquot *dquot;

	act_head = toमुक्त_head->next;
	जबतक (act_head != toमुक्त_head) अणु
		dquot = list_entry(act_head, काष्ठा dquot, dq_मुक्त);
		act_head = act_head->next;
		/* Remove dquot from the list so we won't have problems... */
		list_del_init(&dquot->dq_मुक्त);
		dqput(dquot);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_dquot_ref(काष्ठा super_block *sb, पूर्णांक type,
		काष्ठा list_head *toमुक्त_head)
अणु
	काष्ठा inode *inode;
#अगर_घोषित CONFIG_QUOTA_DEBUG
	पूर्णांक reserved = 0;
#पूर्ण_अगर

	spin_lock(&sb->s_inode_list_lock);
	list_क्रम_each_entry(inode, &sb->s_inodes, i_sb_list) अणु
		/*
		 *  We have to scan also I_NEW inodes because they can alपढ़ोy
		 *  have quota poपूर्णांकer initialized. Luckily, we need to touch
		 *  only quota poपूर्णांकers and these have separate locking
		 *  (dq_data_lock).
		 */
		spin_lock(&dq_data_lock);
		अगर (!IS_NOQUOTA(inode)) अणु
#अगर_घोषित CONFIG_QUOTA_DEBUG
			अगर (unlikely(inode_get_rsv_space(inode) > 0))
				reserved = 1;
#पूर्ण_अगर
			हटाओ_inode_dquot_ref(inode, type, toमुक्त_head);
		पूर्ण
		spin_unlock(&dq_data_lock);
	पूर्ण
	spin_unlock(&sb->s_inode_list_lock);
#अगर_घोषित CONFIG_QUOTA_DEBUG
	अगर (reserved) अणु
		prपूर्णांकk(KERN_WARNING "VFS (%s): Writes happened after quota"
			" was disabled thus quota information is probably "
			"inconsistent. Please run quotacheck(8).\n", sb->s_id);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* Gather all references from inodes and drop them */
अटल व्योम drop_dquot_ref(काष्ठा super_block *sb, पूर्णांक type)
अणु
	LIST_HEAD(toमुक्त_head);

	अगर (sb->dq_op) अणु
		हटाओ_dquot_ref(sb, type, &toमुक्त_head);
		synchronize_srcu(&dquot_srcu);
		put_dquot_list(&toमुक्त_head);
	पूर्ण
पूर्ण

अटल अंतरभूत
व्योम dquot_मुक्त_reserved_space(काष्ठा dquot *dquot, qमाप_प्रकार number)
अणु
	अगर (dquot->dq_dqb.dqb_rsvspace >= number)
		dquot->dq_dqb.dqb_rsvspace -= number;
	अन्यथा अणु
		WARN_ON_ONCE(1);
		dquot->dq_dqb.dqb_rsvspace = 0;
	पूर्ण
	अगर (dquot->dq_dqb.dqb_curspace + dquot->dq_dqb.dqb_rsvspace <=
	    dquot->dq_dqb.dqb_bsoftlimit)
		dquot->dq_dqb.dqb_bसमय = (समय64_t) 0;
	clear_bit(DQ_BLKS_B, &dquot->dq_flags);
पूर्ण

अटल व्योम dquot_decr_inodes(काष्ठा dquot *dquot, qमाप_प्रकार number)
अणु
	अगर (sb_dqopt(dquot->dq_sb)->flags & DQUOT_NEGATIVE_USAGE ||
	    dquot->dq_dqb.dqb_curinodes >= number)
		dquot->dq_dqb.dqb_curinodes -= number;
	अन्यथा
		dquot->dq_dqb.dqb_curinodes = 0;
	अगर (dquot->dq_dqb.dqb_curinodes <= dquot->dq_dqb.dqb_isoftlimit)
		dquot->dq_dqb.dqb_iसमय = (समय64_t) 0;
	clear_bit(DQ_INODES_B, &dquot->dq_flags);
पूर्ण

अटल व्योम dquot_decr_space(काष्ठा dquot *dquot, qमाप_प्रकार number)
अणु
	अगर (sb_dqopt(dquot->dq_sb)->flags & DQUOT_NEGATIVE_USAGE ||
	    dquot->dq_dqb.dqb_curspace >= number)
		dquot->dq_dqb.dqb_curspace -= number;
	अन्यथा
		dquot->dq_dqb.dqb_curspace = 0;
	अगर (dquot->dq_dqb.dqb_curspace + dquot->dq_dqb.dqb_rsvspace <=
	    dquot->dq_dqb.dqb_bsoftlimit)
		dquot->dq_dqb.dqb_bसमय = (समय64_t) 0;
	clear_bit(DQ_BLKS_B, &dquot->dq_flags);
पूर्ण

काष्ठा dquot_warn अणु
	काष्ठा super_block *w_sb;
	काष्ठा kqid w_dq_id;
	लघु w_type;
पूर्ण;

अटल पूर्णांक warning_issued(काष्ठा dquot *dquot, स्थिर पूर्णांक warntype)
अणु
	पूर्णांक flag = (warntype == QUOTA_NL_BHARDWARN ||
		warntype == QUOTA_NL_BSOFTLONGWARN) ? DQ_BLKS_B :
		((warntype == QUOTA_NL_IHARDWARN ||
		warntype == QUOTA_NL_ISOFTLONGWARN) ? DQ_INODES_B : 0);

	अगर (!flag)
		वापस 0;
	वापस test_and_set_bit(flag, &dquot->dq_flags);
पूर्ण

#अगर_घोषित CONFIG_PRINT_QUOTA_WARNING
अटल पूर्णांक flag_prपूर्णांक_warnings = 1;

अटल पूर्णांक need_prपूर्णांक_warning(काष्ठा dquot_warn *warn)
अणु
	अगर (!flag_prपूर्णांक_warnings)
		वापस 0;

	चयन (warn->w_dq_id.type) अणु
		हाल USRQUOTA:
			वापस uid_eq(current_fsuid(), warn->w_dq_id.uid);
		हाल GRPQUOTA:
			वापस in_group_p(warn->w_dq_id.gid);
		हाल PRJQUOTA:
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Prपूर्णांक warning to user which exceeded quota */
अटल व्योम prपूर्णांक_warning(काष्ठा dquot_warn *warn)
अणु
	अक्षर *msg = शून्य;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक warntype = warn->w_type;

	अगर (warntype == QUOTA_NL_IHARDBELOW ||
	    warntype == QUOTA_NL_ISOFTBELOW ||
	    warntype == QUOTA_NL_BHARDBELOW ||
	    warntype == QUOTA_NL_BSOFTBELOW || !need_prपूर्णांक_warning(warn))
		वापस;

	tty = get_current_tty();
	अगर (!tty)
		वापस;
	tty_ग_लिखो_message(tty, warn->w_sb->s_id);
	अगर (warntype == QUOTA_NL_ISOFTWARN || warntype == QUOTA_NL_BSOFTWARN)
		tty_ग_लिखो_message(tty, ": warning, ");
	अन्यथा
		tty_ग_लिखो_message(tty, ": write failed, ");
	tty_ग_लिखो_message(tty, quotatypes[warn->w_dq_id.type]);
	चयन (warntype) अणु
		हाल QUOTA_NL_IHARDWARN:
			msg = " file limit reached.\r\n";
			अवरोध;
		हाल QUOTA_NL_ISOFTLONGWARN:
			msg = " file quota exceeded too long.\r\n";
			अवरोध;
		हाल QUOTA_NL_ISOFTWARN:
			msg = " file quota exceeded.\r\n";
			अवरोध;
		हाल QUOTA_NL_BHARDWARN:
			msg = " block limit reached.\r\n";
			अवरोध;
		हाल QUOTA_NL_BSOFTLONGWARN:
			msg = " block quota exceeded too long.\r\n";
			अवरोध;
		हाल QUOTA_NL_BSOFTWARN:
			msg = " block quota exceeded.\r\n";
			अवरोध;
	पूर्ण
	tty_ग_लिखो_message(tty, msg);
	tty_kref_put(tty);
पूर्ण
#पूर्ण_अगर

अटल व्योम prepare_warning(काष्ठा dquot_warn *warn, काष्ठा dquot *dquot,
			    पूर्णांक warntype)
अणु
	अगर (warning_issued(dquot, warntype))
		वापस;
	warn->w_type = warntype;
	warn->w_sb = dquot->dq_sb;
	warn->w_dq_id = dquot->dq_id;
पूर्ण

/*
 * Write warnings to the console and send warning messages over netlink.
 *
 * Note that this function can call पूर्णांकo tty and networking code.
 */
अटल व्योम flush_warnings(काष्ठा dquot_warn *warn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAXQUOTAS; i++) अणु
		अगर (warn[i].w_type == QUOTA_NL_NOWARN)
			जारी;
#अगर_घोषित CONFIG_PRINT_QUOTA_WARNING
		prपूर्णांक_warning(&warn[i]);
#पूर्ण_अगर
		quota_send_warning(warn[i].w_dq_id,
				   warn[i].w_sb->s_dev, warn[i].w_type);
	पूर्ण
पूर्ण

अटल पूर्णांक ignore_hardlimit(काष्ठा dquot *dquot)
अणु
	काष्ठा mem_dqinfo *info = &sb_dqopt(dquot->dq_sb)->info[dquot->dq_id.type];

	वापस capable(CAP_SYS_RESOURCE) &&
	       (info->dqi_क्रमmat->qf_fmt_id != QFMT_VFS_OLD ||
		!(info->dqi_flags & DQF_ROOT_SQUASH));
पूर्ण

अटल पूर्णांक dquot_add_inodes(काष्ठा dquot *dquot, qमाप_प्रकार inodes,
			    काष्ठा dquot_warn *warn)
अणु
	qमाप_प्रकार newinodes;
	पूर्णांक ret = 0;

	spin_lock(&dquot->dq_dqb_lock);
	newinodes = dquot->dq_dqb.dqb_curinodes + inodes;
	अगर (!sb_has_quota_limits_enabled(dquot->dq_sb, dquot->dq_id.type) ||
	    test_bit(DQ_FAKE_B, &dquot->dq_flags))
		जाओ add;

	अगर (dquot->dq_dqb.dqb_ihardlimit &&
	    newinodes > dquot->dq_dqb.dqb_ihardlimit &&
            !ignore_hardlimit(dquot)) अणु
		prepare_warning(warn, dquot, QUOTA_NL_IHARDWARN);
		ret = -EDQUOT;
		जाओ out;
	पूर्ण

	अगर (dquot->dq_dqb.dqb_isoftlimit &&
	    newinodes > dquot->dq_dqb.dqb_isoftlimit &&
	    dquot->dq_dqb.dqb_iसमय &&
	    kसमय_get_real_seconds() >= dquot->dq_dqb.dqb_iसमय &&
            !ignore_hardlimit(dquot)) अणु
		prepare_warning(warn, dquot, QUOTA_NL_ISOFTLONGWARN);
		ret = -EDQUOT;
		जाओ out;
	पूर्ण

	अगर (dquot->dq_dqb.dqb_isoftlimit &&
	    newinodes > dquot->dq_dqb.dqb_isoftlimit &&
	    dquot->dq_dqb.dqb_iसमय == 0) अणु
		prepare_warning(warn, dquot, QUOTA_NL_ISOFTWARN);
		dquot->dq_dqb.dqb_iसमय = kसमय_get_real_seconds() +
		    sb_dqopt(dquot->dq_sb)->info[dquot->dq_id.type].dqi_igrace;
	पूर्ण
add:
	dquot->dq_dqb.dqb_curinodes = newinodes;

out:
	spin_unlock(&dquot->dq_dqb_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dquot_add_space(काष्ठा dquot *dquot, qमाप_प्रकार space,
			   qमाप_प्रकार rsv_space, अचिन्हित पूर्णांक flags,
			   काष्ठा dquot_warn *warn)
अणु
	qमाप_प्रकार tspace;
	काष्ठा super_block *sb = dquot->dq_sb;
	पूर्णांक ret = 0;

	spin_lock(&dquot->dq_dqb_lock);
	अगर (!sb_has_quota_limits_enabled(sb, dquot->dq_id.type) ||
	    test_bit(DQ_FAKE_B, &dquot->dq_flags))
		जाओ finish;

	tspace = dquot->dq_dqb.dqb_curspace + dquot->dq_dqb.dqb_rsvspace
		+ space + rsv_space;

	अगर (dquot->dq_dqb.dqb_bhardlimit &&
	    tspace > dquot->dq_dqb.dqb_bhardlimit &&
            !ignore_hardlimit(dquot)) अणु
		अगर (flags & DQUOT_SPACE_WARN)
			prepare_warning(warn, dquot, QUOTA_NL_BHARDWARN);
		ret = -EDQUOT;
		जाओ finish;
	पूर्ण

	अगर (dquot->dq_dqb.dqb_bsoftlimit &&
	    tspace > dquot->dq_dqb.dqb_bsoftlimit &&
	    dquot->dq_dqb.dqb_bसमय &&
	    kसमय_get_real_seconds() >= dquot->dq_dqb.dqb_bसमय &&
            !ignore_hardlimit(dquot)) अणु
		अगर (flags & DQUOT_SPACE_WARN)
			prepare_warning(warn, dquot, QUOTA_NL_BSOFTLONGWARN);
		ret = -EDQUOT;
		जाओ finish;
	पूर्ण

	अगर (dquot->dq_dqb.dqb_bsoftlimit &&
	    tspace > dquot->dq_dqb.dqb_bsoftlimit &&
	    dquot->dq_dqb.dqb_bसमय == 0) अणु
		अगर (flags & DQUOT_SPACE_WARN) अणु
			prepare_warning(warn, dquot, QUOTA_NL_BSOFTWARN);
			dquot->dq_dqb.dqb_bसमय = kसमय_get_real_seconds() +
			    sb_dqopt(sb)->info[dquot->dq_id.type].dqi_bgrace;
		पूर्ण अन्यथा अणु
			/*
			 * We करोn't allow pपुनः_स्मृतिation to exceed softlimit so exceeding will
			 * be always prपूर्णांकed
			 */
			ret = -EDQUOT;
			जाओ finish;
		पूर्ण
	पूर्ण
finish:
	/*
	 * We have to be careful and go through warning generation & grace समय
	 * setting even अगर DQUOT_SPACE_NOFAIL is set. That's why we check it
	 * only here...
	 */
	अगर (flags & DQUOT_SPACE_NOFAIL)
		ret = 0;
	अगर (!ret) अणु
		dquot->dq_dqb.dqb_rsvspace += rsv_space;
		dquot->dq_dqb.dqb_curspace += space;
	पूर्ण
	spin_unlock(&dquot->dq_dqb_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक info_idq_मुक्त(काष्ठा dquot *dquot, qमाप_प्रकार inodes)
अणु
	qमाप_प्रकार newinodes;

	अगर (test_bit(DQ_FAKE_B, &dquot->dq_flags) ||
	    dquot->dq_dqb.dqb_curinodes <= dquot->dq_dqb.dqb_isoftlimit ||
	    !sb_has_quota_limits_enabled(dquot->dq_sb, dquot->dq_id.type))
		वापस QUOTA_NL_NOWARN;

	newinodes = dquot->dq_dqb.dqb_curinodes - inodes;
	अगर (newinodes <= dquot->dq_dqb.dqb_isoftlimit)
		वापस QUOTA_NL_ISOFTBELOW;
	अगर (dquot->dq_dqb.dqb_curinodes >= dquot->dq_dqb.dqb_ihardlimit &&
	    newinodes < dquot->dq_dqb.dqb_ihardlimit)
		वापस QUOTA_NL_IHARDBELOW;
	वापस QUOTA_NL_NOWARN;
पूर्ण

अटल पूर्णांक info_bdq_मुक्त(काष्ठा dquot *dquot, qमाप_प्रकार space)
अणु
	qमाप_प्रकार tspace;

	tspace = dquot->dq_dqb.dqb_curspace + dquot->dq_dqb.dqb_rsvspace;

	अगर (test_bit(DQ_FAKE_B, &dquot->dq_flags) ||
	    tspace <= dquot->dq_dqb.dqb_bsoftlimit)
		वापस QUOTA_NL_NOWARN;

	अगर (tspace - space <= dquot->dq_dqb.dqb_bsoftlimit)
		वापस QUOTA_NL_BSOFTBELOW;
	अगर (tspace >= dquot->dq_dqb.dqb_bhardlimit &&
	    tspace - space < dquot->dq_dqb.dqb_bhardlimit)
		वापस QUOTA_NL_BHARDBELOW;
	वापस QUOTA_NL_NOWARN;
पूर्ण

अटल पूर्णांक dquot_active(स्थिर काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;

	अगर (IS_NOQUOTA(inode))
		वापस 0;
	वापस sb_any_quota_loaded(sb) & ~sb_any_quota_suspended(sb);
पूर्ण

/*
 * Initialize quota poपूर्णांकers in inode
 *
 * It is better to call this function outside of any transaction as it
 * might need a lot of space in journal क्रम dquot काष्ठाure allocation.
 */
अटल पूर्णांक __dquot_initialize(काष्ठा inode *inode, पूर्णांक type)
अणु
	पूर्णांक cnt, init_needed = 0;
	काष्ठा dquot **dquots, *got[MAXQUOTAS] = अणुपूर्ण;
	काष्ठा super_block *sb = inode->i_sb;
	qमाप_प्रकार rsv;
	पूर्णांक ret = 0;

	अगर (!dquot_active(inode))
		वापस 0;

	dquots = i_dquot(inode);

	/* First get references to काष्ठाures we might need. */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		काष्ठा kqid qid;
		kprojid_t projid;
		पूर्णांक rc;
		काष्ठा dquot *dquot;

		अगर (type != -1 && cnt != type)
			जारी;
		/*
		 * The i_dquot should have been initialized in most हालs,
		 * we check it without locking here to aव्योम unnecessary
		 * dqget()/dqput() calls.
		 */
		अगर (dquots[cnt])
			जारी;

		अगर (!sb_has_quota_active(sb, cnt))
			जारी;

		init_needed = 1;

		चयन (cnt) अणु
		हाल USRQUOTA:
			qid = make_kqid_uid(inode->i_uid);
			अवरोध;
		हाल GRPQUOTA:
			qid = make_kqid_gid(inode->i_gid);
			अवरोध;
		हाल PRJQUOTA:
			rc = inode->i_sb->dq_op->get_projid(inode, &projid);
			अगर (rc)
				जारी;
			qid = make_kqid_projid(projid);
			अवरोध;
		पूर्ण
		dquot = dqget(sb, qid);
		अगर (IS_ERR(dquot)) अणु
			/* We raced with somebody turning quotas off... */
			अगर (PTR_ERR(dquot) != -ESRCH) अणु
				ret = PTR_ERR(dquot);
				जाओ out_put;
			पूर्ण
			dquot = शून्य;
		पूर्ण
		got[cnt] = dquot;
	पूर्ण

	/* All required i_dquot has been initialized */
	अगर (!init_needed)
		वापस 0;

	spin_lock(&dq_data_lock);
	अगर (IS_NOQUOTA(inode))
		जाओ out_lock;
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (type != -1 && cnt != type)
			जारी;
		/* Aव्योम races with quotaoff() */
		अगर (!sb_has_quota_active(sb, cnt))
			जारी;
		/* We could race with quotaon or dqget() could have failed */
		अगर (!got[cnt])
			जारी;
		अगर (!dquots[cnt]) अणु
			dquots[cnt] = got[cnt];
			got[cnt] = शून्य;
			/*
			 * Make quota reservation प्रणाली happy अगर someone
			 * did a ग_लिखो beक्रमe quota was turned on
			 */
			rsv = inode_get_rsv_space(inode);
			अगर (unlikely(rsv)) अणु
				spin_lock(&inode->i_lock);
				/* Get reservation again under proper lock */
				rsv = __inode_get_rsv_space(inode);
				spin_lock(&dquots[cnt]->dq_dqb_lock);
				dquots[cnt]->dq_dqb.dqb_rsvspace += rsv;
				spin_unlock(&dquots[cnt]->dq_dqb_lock);
				spin_unlock(&inode->i_lock);
			पूर्ण
		पूर्ण
	पूर्ण
out_lock:
	spin_unlock(&dq_data_lock);
out_put:
	/* Drop unused references */
	dqput_all(got);

	वापस ret;
पूर्ण

पूर्णांक dquot_initialize(काष्ठा inode *inode)
अणु
	वापस __dquot_initialize(inode, -1);
पूर्ण
EXPORT_SYMBOL(dquot_initialize);

bool dquot_initialize_needed(काष्ठा inode *inode)
अणु
	काष्ठा dquot **dquots;
	पूर्णांक i;

	अगर (!dquot_active(inode))
		वापस false;

	dquots = i_dquot(inode);
	क्रम (i = 0; i < MAXQUOTAS; i++)
		अगर (!dquots[i] && sb_has_quota_active(inode->i_sb, i))
			वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL(dquot_initialize_needed);

/*
 * Release all quotas referenced by inode.
 *
 * This function only be called on inode मुक्त or converting
 * a file to quota file, no other users क्रम the i_dquot in
 * both हालs, so we needn't call synchronize_srcu() after
 * clearing i_dquot.
 */
अटल व्योम __dquot_drop(काष्ठा inode *inode)
अणु
	पूर्णांक cnt;
	काष्ठा dquot **dquots = i_dquot(inode);
	काष्ठा dquot *put[MAXQUOTAS];

	spin_lock(&dq_data_lock);
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		put[cnt] = dquots[cnt];
		dquots[cnt] = शून्य;
	पूर्ण
	spin_unlock(&dq_data_lock);
	dqput_all(put);
पूर्ण

व्योम dquot_drop(काष्ठा inode *inode)
अणु
	काष्ठा dquot * स्थिर *dquots;
	पूर्णांक cnt;

	अगर (IS_NOQUOTA(inode))
		वापस;

	/*
	 * Test beक्रमe calling to rule out calls from proc and such
	 * where we are not allowed to block. Note that this is
	 * actually reliable test even without the lock - the caller
	 * must assure that nobody can come after the DQUOT_DROP and
	 * add quota poपूर्णांकers back anyway.
	 */
	dquots = i_dquot(inode);
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (dquots[cnt])
			अवरोध;
	पूर्ण

	अगर (cnt < MAXQUOTAS)
		__dquot_drop(inode);
पूर्ण
EXPORT_SYMBOL(dquot_drop);

/*
 * inode_reserved_space is managed पूर्णांकernally by quota, and रक्षित by
 * i_lock similar to i_blocks+i_bytes.
 */
अटल qमाप_प्रकार *inode_reserved_space(काष्ठा inode * inode)
अणु
	/* Fileप्रणाली must explicitly define it's own method in order to use
	 * quota reservation पूर्णांकerface */
	BUG_ON(!inode->i_sb->dq_op->get_reserved_space);
	वापस inode->i_sb->dq_op->get_reserved_space(inode);
पूर्ण

अटल qमाप_प्रकार __inode_get_rsv_space(काष्ठा inode *inode)
अणु
	अगर (!inode->i_sb->dq_op->get_reserved_space)
		वापस 0;
	वापस *inode_reserved_space(inode);
पूर्ण

अटल qमाप_प्रकार inode_get_rsv_space(काष्ठा inode *inode)
अणु
	qमाप_प्रकार ret;

	अगर (!inode->i_sb->dq_op->get_reserved_space)
		वापस 0;
	spin_lock(&inode->i_lock);
	ret = __inode_get_rsv_space(inode);
	spin_unlock(&inode->i_lock);
	वापस ret;
पूर्ण

/*
 * This functions updates i_blocks+i_bytes fields and quota inक्रमmation
 * (together with appropriate checks).
 *
 * NOTE: We असलolutely rely on the fact that caller dirties the inode
 * (usually helpers in quotaops.h care about this) and holds a handle क्रम
 * the current transaction so that dquot ग_लिखो and inode ग_लिखो go पूर्णांकo the
 * same transaction.
 */

/*
 * This operation can block, but only after everything is updated
 */
पूर्णांक __dquot_alloc_space(काष्ठा inode *inode, qमाप_प्रकार number, पूर्णांक flags)
अणु
	पूर्णांक cnt, ret = 0, index;
	काष्ठा dquot_warn warn[MAXQUOTAS];
	पूर्णांक reserve = flags & DQUOT_SPACE_RESERVE;
	काष्ठा dquot **dquots;

	अगर (!dquot_active(inode)) अणु
		अगर (reserve) अणु
			spin_lock(&inode->i_lock);
			*inode_reserved_space(inode) += number;
			spin_unlock(&inode->i_lock);
		पूर्ण अन्यथा अणु
			inode_add_bytes(inode, number);
		पूर्ण
		जाओ out;
	पूर्ण

	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++)
		warn[cnt].w_type = QUOTA_NL_NOWARN;

	dquots = i_dquot(inode);
	index = srcu_पढ़ो_lock(&dquot_srcu);
	spin_lock(&inode->i_lock);
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (!dquots[cnt])
			जारी;
		अगर (reserve) अणु
			ret = dquot_add_space(dquots[cnt], 0, number, flags,
					      &warn[cnt]);
		पूर्ण अन्यथा अणु
			ret = dquot_add_space(dquots[cnt], number, 0, flags,
					      &warn[cnt]);
		पूर्ण
		अगर (ret) अणु
			/* Back out changes we alपढ़ोy did */
			क्रम (cnt--; cnt >= 0; cnt--) अणु
				अगर (!dquots[cnt])
					जारी;
				spin_lock(&dquots[cnt]->dq_dqb_lock);
				अगर (reserve)
					dquot_मुक्त_reserved_space(dquots[cnt],
								  number);
				अन्यथा
					dquot_decr_space(dquots[cnt], number);
				spin_unlock(&dquots[cnt]->dq_dqb_lock);
			पूर्ण
			spin_unlock(&inode->i_lock);
			जाओ out_flush_warn;
		पूर्ण
	पूर्ण
	अगर (reserve)
		*inode_reserved_space(inode) += number;
	अन्यथा
		__inode_add_bytes(inode, number);
	spin_unlock(&inode->i_lock);

	अगर (reserve)
		जाओ out_flush_warn;
	mark_all_dquot_dirty(dquots);
out_flush_warn:
	srcu_पढ़ो_unlock(&dquot_srcu, index);
	flush_warnings(warn);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__dquot_alloc_space);

/*
 * This operation can block, but only after everything is updated
 */
पूर्णांक dquot_alloc_inode(काष्ठा inode *inode)
अणु
	पूर्णांक cnt, ret = 0, index;
	काष्ठा dquot_warn warn[MAXQUOTAS];
	काष्ठा dquot * स्थिर *dquots;

	अगर (!dquot_active(inode))
		वापस 0;
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++)
		warn[cnt].w_type = QUOTA_NL_NOWARN;

	dquots = i_dquot(inode);
	index = srcu_पढ़ो_lock(&dquot_srcu);
	spin_lock(&inode->i_lock);
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (!dquots[cnt])
			जारी;
		ret = dquot_add_inodes(dquots[cnt], 1, &warn[cnt]);
		अगर (ret) अणु
			क्रम (cnt--; cnt >= 0; cnt--) अणु
				अगर (!dquots[cnt])
					जारी;
				/* Back out changes we alपढ़ोy did */
				spin_lock(&dquots[cnt]->dq_dqb_lock);
				dquot_decr_inodes(dquots[cnt], 1);
				spin_unlock(&dquots[cnt]->dq_dqb_lock);
			पूर्ण
			जाओ warn_put_all;
		पूर्ण
	पूर्ण

warn_put_all:
	spin_unlock(&inode->i_lock);
	अगर (ret == 0)
		mark_all_dquot_dirty(dquots);
	srcu_पढ़ो_unlock(&dquot_srcu, index);
	flush_warnings(warn);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dquot_alloc_inode);

/*
 * Convert in-memory reserved quotas to real consumed quotas
 */
पूर्णांक dquot_claim_space_nodirty(काष्ठा inode *inode, qमाप_प्रकार number)
अणु
	काष्ठा dquot **dquots;
	पूर्णांक cnt, index;

	अगर (!dquot_active(inode)) अणु
		spin_lock(&inode->i_lock);
		*inode_reserved_space(inode) -= number;
		__inode_add_bytes(inode, number);
		spin_unlock(&inode->i_lock);
		वापस 0;
	पूर्ण

	dquots = i_dquot(inode);
	index = srcu_पढ़ो_lock(&dquot_srcu);
	spin_lock(&inode->i_lock);
	/* Claim reserved quotas to allocated quotas */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (dquots[cnt]) अणु
			काष्ठा dquot *dquot = dquots[cnt];

			spin_lock(&dquot->dq_dqb_lock);
			अगर (WARN_ON_ONCE(dquot->dq_dqb.dqb_rsvspace < number))
				number = dquot->dq_dqb.dqb_rsvspace;
			dquot->dq_dqb.dqb_curspace += number;
			dquot->dq_dqb.dqb_rsvspace -= number;
			spin_unlock(&dquot->dq_dqb_lock);
		पूर्ण
	पूर्ण
	/* Update inode bytes */
	*inode_reserved_space(inode) -= number;
	__inode_add_bytes(inode, number);
	spin_unlock(&inode->i_lock);
	mark_all_dquot_dirty(dquots);
	srcu_पढ़ो_unlock(&dquot_srcu, index);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dquot_claim_space_nodirty);

/*
 * Convert allocated space back to in-memory reserved quotas
 */
व्योम dquot_reclaim_space_nodirty(काष्ठा inode *inode, qमाप_प्रकार number)
अणु
	काष्ठा dquot **dquots;
	पूर्णांक cnt, index;

	अगर (!dquot_active(inode)) अणु
		spin_lock(&inode->i_lock);
		*inode_reserved_space(inode) += number;
		__inode_sub_bytes(inode, number);
		spin_unlock(&inode->i_lock);
		वापस;
	पूर्ण

	dquots = i_dquot(inode);
	index = srcu_पढ़ो_lock(&dquot_srcu);
	spin_lock(&inode->i_lock);
	/* Claim reserved quotas to allocated quotas */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (dquots[cnt]) अणु
			काष्ठा dquot *dquot = dquots[cnt];

			spin_lock(&dquot->dq_dqb_lock);
			अगर (WARN_ON_ONCE(dquot->dq_dqb.dqb_curspace < number))
				number = dquot->dq_dqb.dqb_curspace;
			dquot->dq_dqb.dqb_rsvspace += number;
			dquot->dq_dqb.dqb_curspace -= number;
			spin_unlock(&dquot->dq_dqb_lock);
		पूर्ण
	पूर्ण
	/* Update inode bytes */
	*inode_reserved_space(inode) += number;
	__inode_sub_bytes(inode, number);
	spin_unlock(&inode->i_lock);
	mark_all_dquot_dirty(dquots);
	srcu_पढ़ो_unlock(&dquot_srcu, index);
	वापस;
पूर्ण
EXPORT_SYMBOL(dquot_reclaim_space_nodirty);

/*
 * This operation can block, but only after everything is updated
 */
व्योम __dquot_मुक्त_space(काष्ठा inode *inode, qमाप_प्रकार number, पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक cnt;
	काष्ठा dquot_warn warn[MAXQUOTAS];
	काष्ठा dquot **dquots;
	पूर्णांक reserve = flags & DQUOT_SPACE_RESERVE, index;

	अगर (!dquot_active(inode)) अणु
		अगर (reserve) अणु
			spin_lock(&inode->i_lock);
			*inode_reserved_space(inode) -= number;
			spin_unlock(&inode->i_lock);
		पूर्ण अन्यथा अणु
			inode_sub_bytes(inode, number);
		पूर्ण
		वापस;
	पूर्ण

	dquots = i_dquot(inode);
	index = srcu_पढ़ो_lock(&dquot_srcu);
	spin_lock(&inode->i_lock);
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		पूर्णांक wtype;

		warn[cnt].w_type = QUOTA_NL_NOWARN;
		अगर (!dquots[cnt])
			जारी;
		spin_lock(&dquots[cnt]->dq_dqb_lock);
		wtype = info_bdq_मुक्त(dquots[cnt], number);
		अगर (wtype != QUOTA_NL_NOWARN)
			prepare_warning(&warn[cnt], dquots[cnt], wtype);
		अगर (reserve)
			dquot_मुक्त_reserved_space(dquots[cnt], number);
		अन्यथा
			dquot_decr_space(dquots[cnt], number);
		spin_unlock(&dquots[cnt]->dq_dqb_lock);
	पूर्ण
	अगर (reserve)
		*inode_reserved_space(inode) -= number;
	अन्यथा
		__inode_sub_bytes(inode, number);
	spin_unlock(&inode->i_lock);

	अगर (reserve)
		जाओ out_unlock;
	mark_all_dquot_dirty(dquots);
out_unlock:
	srcu_पढ़ो_unlock(&dquot_srcu, index);
	flush_warnings(warn);
पूर्ण
EXPORT_SYMBOL(__dquot_मुक्त_space);

/*
 * This operation can block, but only after everything is updated
 */
व्योम dquot_मुक्त_inode(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक cnt;
	काष्ठा dquot_warn warn[MAXQUOTAS];
	काष्ठा dquot * स्थिर *dquots;
	पूर्णांक index;

	अगर (!dquot_active(inode))
		वापस;

	dquots = i_dquot(inode);
	index = srcu_पढ़ो_lock(&dquot_srcu);
	spin_lock(&inode->i_lock);
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		पूर्णांक wtype;

		warn[cnt].w_type = QUOTA_NL_NOWARN;
		अगर (!dquots[cnt])
			जारी;
		spin_lock(&dquots[cnt]->dq_dqb_lock);
		wtype = info_idq_मुक्त(dquots[cnt], 1);
		अगर (wtype != QUOTA_NL_NOWARN)
			prepare_warning(&warn[cnt], dquots[cnt], wtype);
		dquot_decr_inodes(dquots[cnt], 1);
		spin_unlock(&dquots[cnt]->dq_dqb_lock);
	पूर्ण
	spin_unlock(&inode->i_lock);
	mark_all_dquot_dirty(dquots);
	srcu_पढ़ो_unlock(&dquot_srcu, index);
	flush_warnings(warn);
पूर्ण
EXPORT_SYMBOL(dquot_मुक्त_inode);

/*
 * Transfer the number of inode and blocks from one diskquota to an other.
 * On success, dquot references in transfer_to are consumed and references
 * to original dquots that need to be released are placed there. On failure,
 * references are kept untouched.
 *
 * This operation can block, but only after everything is updated
 * A transaction must be started when entering this function.
 *
 * We are holding reference on transfer_from & transfer_to, no need to
 * protect them by srcu_पढ़ो_lock().
 */
पूर्णांक __dquot_transfer(काष्ठा inode *inode, काष्ठा dquot **transfer_to)
अणु
	qमाप_प्रकार cur_space;
	qमाप_प्रकार rsv_space = 0;
	qमाप_प्रकार inode_usage = 1;
	काष्ठा dquot *transfer_from[MAXQUOTAS] = अणुपूर्ण;
	पूर्णांक cnt, ret = 0;
	अक्षर is_valid[MAXQUOTAS] = अणुपूर्ण;
	काष्ठा dquot_warn warn_to[MAXQUOTAS];
	काष्ठा dquot_warn warn_from_inodes[MAXQUOTAS];
	काष्ठा dquot_warn warn_from_space[MAXQUOTAS];

	अगर (IS_NOQUOTA(inode))
		वापस 0;

	अगर (inode->i_sb->dq_op->get_inode_usage) अणु
		ret = inode->i_sb->dq_op->get_inode_usage(inode, &inode_usage);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Initialize the arrays */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		warn_to[cnt].w_type = QUOTA_NL_NOWARN;
		warn_from_inodes[cnt].w_type = QUOTA_NL_NOWARN;
		warn_from_space[cnt].w_type = QUOTA_NL_NOWARN;
	पूर्ण

	spin_lock(&dq_data_lock);
	spin_lock(&inode->i_lock);
	अगर (IS_NOQUOTA(inode)) अणु	/* File without quota accounting? */
		spin_unlock(&inode->i_lock);
		spin_unlock(&dq_data_lock);
		वापस 0;
	पूर्ण
	cur_space = __inode_get_bytes(inode);
	rsv_space = __inode_get_rsv_space(inode);
	/*
	 * Build the transfer_from list, check limits, and update usage in
	 * the target काष्ठाures.
	 */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		/*
		 * Skip changes क्रम same uid or gid or क्रम turned off quota-type.
		 */
		अगर (!transfer_to[cnt])
			जारी;
		/* Aव्योम races with quotaoff() */
		अगर (!sb_has_quota_active(inode->i_sb, cnt))
			जारी;
		is_valid[cnt] = 1;
		transfer_from[cnt] = i_dquot(inode)[cnt];
		ret = dquot_add_inodes(transfer_to[cnt], inode_usage,
				       &warn_to[cnt]);
		अगर (ret)
			जाओ over_quota;
		ret = dquot_add_space(transfer_to[cnt], cur_space, rsv_space,
				      DQUOT_SPACE_WARN, &warn_to[cnt]);
		अगर (ret) अणु
			spin_lock(&transfer_to[cnt]->dq_dqb_lock);
			dquot_decr_inodes(transfer_to[cnt], inode_usage);
			spin_unlock(&transfer_to[cnt]->dq_dqb_lock);
			जाओ over_quota;
		पूर्ण
	पूर्ण

	/* Decrease usage क्रम source काष्ठाures and update quota poपूर्णांकers */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (!is_valid[cnt])
			जारी;
		/* Due to IO error we might not have transfer_from[] काष्ठाure */
		अगर (transfer_from[cnt]) अणु
			पूर्णांक wtype;

			spin_lock(&transfer_from[cnt]->dq_dqb_lock);
			wtype = info_idq_मुक्त(transfer_from[cnt], inode_usage);
			अगर (wtype != QUOTA_NL_NOWARN)
				prepare_warning(&warn_from_inodes[cnt],
						transfer_from[cnt], wtype);
			wtype = info_bdq_मुक्त(transfer_from[cnt],
					      cur_space + rsv_space);
			अगर (wtype != QUOTA_NL_NOWARN)
				prepare_warning(&warn_from_space[cnt],
						transfer_from[cnt], wtype);
			dquot_decr_inodes(transfer_from[cnt], inode_usage);
			dquot_decr_space(transfer_from[cnt], cur_space);
			dquot_मुक्त_reserved_space(transfer_from[cnt],
						  rsv_space);
			spin_unlock(&transfer_from[cnt]->dq_dqb_lock);
		पूर्ण
		i_dquot(inode)[cnt] = transfer_to[cnt];
	पूर्ण
	spin_unlock(&inode->i_lock);
	spin_unlock(&dq_data_lock);

	mark_all_dquot_dirty(transfer_from);
	mark_all_dquot_dirty(transfer_to);
	flush_warnings(warn_to);
	flush_warnings(warn_from_inodes);
	flush_warnings(warn_from_space);
	/* Pass back references to put */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++)
		अगर (is_valid[cnt])
			transfer_to[cnt] = transfer_from[cnt];
	वापस 0;
over_quota:
	/* Back out changes we alपढ़ोy did */
	क्रम (cnt--; cnt >= 0; cnt--) अणु
		अगर (!is_valid[cnt])
			जारी;
		spin_lock(&transfer_to[cnt]->dq_dqb_lock);
		dquot_decr_inodes(transfer_to[cnt], inode_usage);
		dquot_decr_space(transfer_to[cnt], cur_space);
		dquot_मुक्त_reserved_space(transfer_to[cnt], rsv_space);
		spin_unlock(&transfer_to[cnt]->dq_dqb_lock);
	पूर्ण
	spin_unlock(&inode->i_lock);
	spin_unlock(&dq_data_lock);
	flush_warnings(warn_to);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__dquot_transfer);

/* Wrapper क्रम transferring ownership of an inode क्रम uid/gid only
 * Called from FSXXX_setattr()
 */
पूर्णांक dquot_transfer(काष्ठा inode *inode, काष्ठा iattr *iattr)
अणु
	काष्ठा dquot *transfer_to[MAXQUOTAS] = अणुपूर्ण;
	काष्ठा dquot *dquot;
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक ret;

	अगर (!dquot_active(inode))
		वापस 0;

	अगर (iattr->ia_valid & ATTR_UID && !uid_eq(iattr->ia_uid, inode->i_uid))अणु
		dquot = dqget(sb, make_kqid_uid(iattr->ia_uid));
		अगर (IS_ERR(dquot)) अणु
			अगर (PTR_ERR(dquot) != -ESRCH) अणु
				ret = PTR_ERR(dquot);
				जाओ out_put;
			पूर्ण
			dquot = शून्य;
		पूर्ण
		transfer_to[USRQUOTA] = dquot;
	पूर्ण
	अगर (iattr->ia_valid & ATTR_GID && !gid_eq(iattr->ia_gid, inode->i_gid))अणु
		dquot = dqget(sb, make_kqid_gid(iattr->ia_gid));
		अगर (IS_ERR(dquot)) अणु
			अगर (PTR_ERR(dquot) != -ESRCH) अणु
				ret = PTR_ERR(dquot);
				जाओ out_put;
			पूर्ण
			dquot = शून्य;
		पूर्ण
		transfer_to[GRPQUOTA] = dquot;
	पूर्ण
	ret = __dquot_transfer(inode, transfer_to);
out_put:
	dqput_all(transfer_to);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dquot_transfer);

/*
 * Write info of quota file to disk
 */
पूर्णांक dquot_commit_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(sb);

	वापस dqopt->ops[type]->ग_लिखो_file_info(sb, type);
पूर्ण
EXPORT_SYMBOL(dquot_commit_info);

पूर्णांक dquot_get_next_id(काष्ठा super_block *sb, काष्ठा kqid *qid)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(sb);

	अगर (!sb_has_quota_active(sb, qid->type))
		वापस -ESRCH;
	अगर (!dqopt->ops[qid->type]->get_next_id)
		वापस -ENOSYS;
	वापस dqopt->ops[qid->type]->get_next_id(sb, qid);
पूर्ण
EXPORT_SYMBOL(dquot_get_next_id);

/*
 * Definitions of diskquota operations.
 */
स्थिर काष्ठा dquot_operations dquot_operations = अणु
	.ग_लिखो_dquot	= dquot_commit,
	.acquire_dquot	= dquot_acquire,
	.release_dquot	= dquot_release,
	.mark_dirty	= dquot_mark_dquot_dirty,
	.ग_लिखो_info	= dquot_commit_info,
	.alloc_dquot	= dquot_alloc,
	.destroy_dquot	= dquot_destroy,
	.get_next_id	= dquot_get_next_id,
पूर्ण;
EXPORT_SYMBOL(dquot_operations);

/*
 * Generic helper क्रम ->खोलो on fileप्रणालीs supporting disk quotas.
 */
पूर्णांक dquot_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक error;

	error = generic_file_खोलो(inode, file);
	अगर (!error && (file->f_mode & FMODE_WRITE))
		error = dquot_initialize(inode);
	वापस error;
पूर्ण
EXPORT_SYMBOL(dquot_file_खोलो);

अटल व्योम vfs_cleanup_quota_inode(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	काष्ठा inode *inode = dqopt->files[type];

	अगर (!inode)
		वापस;
	अगर (!(dqopt->flags & DQUOT_QUOTA_SYS_खाता)) अणु
		inode_lock(inode);
		inode->i_flags &= ~S_NOQUOTA;
		inode_unlock(inode);
	पूर्ण
	dqopt->files[type] = शून्य;
	iput(inode);
पूर्ण

/*
 * Turn quota off on a device. type == -1 ==> quotaoff क्रम all types (umount)
 */
पूर्णांक dquot_disable(काष्ठा super_block *sb, पूर्णांक type, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक cnt;
	काष्ठा quota_info *dqopt = sb_dqopt(sb);

	/* s_umount should be held in exclusive mode */
	अगर (WARN_ON_ONCE(करोwn_पढ़ो_trylock(&sb->s_umount)))
		up_पढ़ो(&sb->s_umount);

	/* Cannot turn off usage accounting without turning off limits, or
	 * suspend quotas and simultaneously turn quotas off. */
	अगर ((flags & DQUOT_USAGE_ENABLED && !(flags & DQUOT_LIMITS_ENABLED))
	    || (flags & DQUOT_SUSPENDED && flags & (DQUOT_LIMITS_ENABLED |
	    DQUOT_USAGE_ENABLED)))
		वापस -EINVAL;

	/*
	 * Skip everything अगर there's nothing to करो. We have to करो this because
	 * someबार we are called when fill_super() failed and calling
	 * sync_fs() in such हालs करोes no good.
	 */
	अगर (!sb_any_quota_loaded(sb))
		वापस 0;

	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (type != -1 && cnt != type)
			जारी;
		अगर (!sb_has_quota_loaded(sb, cnt))
			जारी;

		अगर (flags & DQUOT_SUSPENDED) अणु
			spin_lock(&dq_state_lock);
			dqopt->flags |=
				dquot_state_flag(DQUOT_SUSPENDED, cnt);
			spin_unlock(&dq_state_lock);
		पूर्ण अन्यथा अणु
			spin_lock(&dq_state_lock);
			dqopt->flags &= ~dquot_state_flag(flags, cnt);
			/* Turning off suspended quotas? */
			अगर (!sb_has_quota_loaded(sb, cnt) &&
			    sb_has_quota_suspended(sb, cnt)) अणु
				dqopt->flags &=	~dquot_state_flag(
							DQUOT_SUSPENDED, cnt);
				spin_unlock(&dq_state_lock);
				vfs_cleanup_quota_inode(sb, cnt);
				जारी;
			पूर्ण
			spin_unlock(&dq_state_lock);
		पूर्ण

		/* We still have to keep quota loaded? */
		अगर (sb_has_quota_loaded(sb, cnt) && !(flags & DQUOT_SUSPENDED))
			जारी;

		/* Note: these are blocking operations */
		drop_dquot_ref(sb, cnt);
		invalidate_dquots(sb, cnt);
		/*
		 * Now all dquots should be invalidated, all ग_लिखोs करोne so we
		 * should be only users of the info. No locks needed.
		 */
		अगर (info_dirty(&dqopt->info[cnt]))
			sb->dq_op->ग_लिखो_info(sb, cnt);
		अगर (dqopt->ops[cnt]->मुक्त_file_info)
			dqopt->ops[cnt]->मुक्त_file_info(sb, cnt);
		put_quota_क्रमmat(dqopt->info[cnt].dqi_क्रमmat);
		dqopt->info[cnt].dqi_flags = 0;
		dqopt->info[cnt].dqi_igrace = 0;
		dqopt->info[cnt].dqi_bgrace = 0;
		dqopt->ops[cnt] = शून्य;
	पूर्ण

	/* Skip syncing and setting flags अगर quota files are hidden */
	अगर (dqopt->flags & DQUOT_QUOTA_SYS_खाता)
		जाओ put_inodes;

	/* Sync the superblock so that buffers with quota data are written to
	 * disk (and so userspace sees correct data afterwards). */
	अगर (sb->s_op->sync_fs)
		sb->s_op->sync_fs(sb, 1);
	sync_blockdev(sb->s_bdev);
	/* Now the quota files are just ordinary files and we can set the
	 * inode flags back. Moreover we discard the pagecache so that
	 * userspace sees the ग_लिखोs we did bypassing the pagecache. We
	 * must also discard the blockdev buffers so that we see the
	 * changes करोne by userspace on the next quotaon() */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++)
		अगर (!sb_has_quota_loaded(sb, cnt) && dqopt->files[cnt]) अणु
			inode_lock(dqopt->files[cnt]);
			truncate_inode_pages(&dqopt->files[cnt]->i_data, 0);
			inode_unlock(dqopt->files[cnt]);
		पूर्ण
	अगर (sb->s_bdev)
		invalidate_bdev(sb->s_bdev);
put_inodes:
	/* We are करोne when suspending quotas */
	अगर (flags & DQUOT_SUSPENDED)
		वापस 0;

	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++)
		अगर (!sb_has_quota_loaded(sb, cnt))
			vfs_cleanup_quota_inode(sb, cnt);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dquot_disable);

पूर्णांक dquot_quota_off(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस dquot_disable(sb, type,
			     DQUOT_USAGE_ENABLED | DQUOT_LIMITS_ENABLED);
पूर्ण
EXPORT_SYMBOL(dquot_quota_off);

/*
 *	Turn quotas on on a device
 */

अटल पूर्णांक vfs_setup_quota_inode(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा quota_info *dqopt = sb_dqopt(sb);

	अगर (!S_ISREG(inode->i_mode))
		वापस -EACCES;
	अगर (IS_RDONLY(inode))
		वापस -EROFS;
	अगर (sb_has_quota_loaded(sb, type))
		वापस -EBUSY;

	dqopt->files[type] = igrab(inode);
	अगर (!dqopt->files[type])
		वापस -EIO;
	अगर (!(dqopt->flags & DQUOT_QUOTA_SYS_खाता)) अणु
		/* We करोn't want quota and aसमय on quota files (deadlocks
		 * possible) Also nobody should ग_लिखो to the file - we use
		 * special IO operations which ignore the immutable bit. */
		inode_lock(inode);
		inode->i_flags |= S_NOQUOTA;
		inode_unlock(inode);
		/*
		 * When S_NOQUOTA is set, हटाओ dquot references as no more
		 * references can be added
		 */
		__dquot_drop(inode);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक dquot_load_quota_sb(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
	अचिन्हित पूर्णांक flags)
अणु
	काष्ठा quota_क्रमmat_type *fmt = find_quota_क्रमmat(क्रमmat_id);
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	पूर्णांक error;

	/* Just unsuspend quotas? */
	BUG_ON(flags & DQUOT_SUSPENDED);
	/* s_umount should be held in exclusive mode */
	अगर (WARN_ON_ONCE(करोwn_पढ़ो_trylock(&sb->s_umount)))
		up_पढ़ो(&sb->s_umount);

	अगर (!fmt)
		वापस -ESRCH;
	अगर (!sb->s_op->quota_ग_लिखो || !sb->s_op->quota_पढ़ो ||
	    (type == PRJQUOTA && sb->dq_op->get_projid == शून्य)) अणु
		error = -EINVAL;
		जाओ out_fmt;
	पूर्ण
	/* Fileप्रणालीs outside of init_user_ns not yet supported */
	अगर (sb->s_user_ns != &init_user_ns) अणु
		error = -EINVAL;
		जाओ out_fmt;
	पूर्ण
	/* Usage always has to be set... */
	अगर (!(flags & DQUOT_USAGE_ENABLED)) अणु
		error = -EINVAL;
		जाओ out_fmt;
	पूर्ण
	अगर (sb_has_quota_loaded(sb, type)) अणु
		error = -EBUSY;
		जाओ out_fmt;
	पूर्ण

	अगर (!(dqopt->flags & DQUOT_QUOTA_SYS_खाता)) अणु
		/* As we bypass the pagecache we must now flush all the
		 * dirty data and invalidate caches so that kernel sees
		 * changes from userspace. It is not enough to just flush
		 * the quota file since अगर blocksize < pagesize, invalidation
		 * of the cache could fail because of other unrelated dirty
		 * data */
		sync_fileप्रणाली(sb);
		invalidate_bdev(sb->s_bdev);
	पूर्ण

	error = -EINVAL;
	अगर (!fmt->qf_ops->check_quota_file(sb, type))
		जाओ out_fmt;

	dqopt->ops[type] = fmt->qf_ops;
	dqopt->info[type].dqi_क्रमmat = fmt;
	dqopt->info[type].dqi_fmt_id = क्रमmat_id;
	INIT_LIST_HEAD(&dqopt->info[type].dqi_dirty_list);
	error = dqopt->ops[type]->पढ़ो_file_info(sb, type);
	अगर (error < 0)
		जाओ out_fmt;
	अगर (dqopt->flags & DQUOT_QUOTA_SYS_खाता) अणु
		spin_lock(&dq_data_lock);
		dqopt->info[type].dqi_flags |= DQF_SYS_खाता;
		spin_unlock(&dq_data_lock);
	पूर्ण
	spin_lock(&dq_state_lock);
	dqopt->flags |= dquot_state_flag(flags, type);
	spin_unlock(&dq_state_lock);

	error = add_dquot_ref(sb, type);
	अगर (error)
		dquot_disable(sb, type, flags);

	वापस error;
out_fmt:
	put_quota_क्रमmat(fmt);

	वापस error;
पूर्ण
EXPORT_SYMBOL(dquot_load_quota_sb);

/*
 * More घातerful function क्रम turning on quotas on given quota inode allowing
 * setting of inभागidual quota flags
 */
पूर्णांक dquot_load_quota_inode(काष्ठा inode *inode, पूर्णांक type, पूर्णांक क्रमmat_id,
	अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;

	err = vfs_setup_quota_inode(inode, type);
	अगर (err < 0)
		वापस err;
	err = dquot_load_quota_sb(inode->i_sb, type, क्रमmat_id, flags);
	अगर (err < 0)
		vfs_cleanup_quota_inode(inode->i_sb, type);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dquot_load_quota_inode);

/* Reenable quotas on remount RW */
पूर्णांक dquot_resume(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	पूर्णांक ret = 0, cnt;
	अचिन्हित पूर्णांक flags;

	/* s_umount should be held in exclusive mode */
	अगर (WARN_ON_ONCE(करोwn_पढ़ो_trylock(&sb->s_umount)))
		up_पढ़ो(&sb->s_umount);

	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		अगर (type != -1 && cnt != type)
			जारी;
		अगर (!sb_has_quota_suspended(sb, cnt))
			जारी;

		spin_lock(&dq_state_lock);
		flags = dqopt->flags & dquot_state_flag(DQUOT_USAGE_ENABLED |
							DQUOT_LIMITS_ENABLED,
							cnt);
		dqopt->flags &= ~dquot_state_flag(DQUOT_STATE_FLAGS, cnt);
		spin_unlock(&dq_state_lock);

		flags = dquot_generic_flag(flags, cnt);
		ret = dquot_load_quota_sb(sb, cnt, dqopt->info[cnt].dqi_fmt_id,
					  flags);
		अगर (ret < 0)
			vfs_cleanup_quota_inode(sb, cnt);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dquot_resume);

पूर्णांक dquot_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
		   स्थिर काष्ठा path *path)
अणु
	पूर्णांक error = security_quota_on(path->dentry);
	अगर (error)
		वापस error;
	/* Quota file not on the same fileप्रणाली? */
	अगर (path->dentry->d_sb != sb)
		error = -EXDEV;
	अन्यथा
		error = dquot_load_quota_inode(d_inode(path->dentry), type,
					     क्रमmat_id, DQUOT_USAGE_ENABLED |
					     DQUOT_LIMITS_ENABLED);
	वापस error;
पूर्ण
EXPORT_SYMBOL(dquot_quota_on);

/*
 * This function is used when fileप्रणाली needs to initialize quotas
 * during mount समय.
 */
पूर्णांक dquot_quota_on_mount(काष्ठा super_block *sb, अक्षर *qf_name,
		पूर्णांक क्रमmat_id, पूर्णांक type)
अणु
	काष्ठा dentry *dentry;
	पूर्णांक error;

	dentry = lookup_positive_unlocked(qf_name, sb->s_root, म_माप(qf_name));
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	error = security_quota_on(dentry);
	अगर (!error)
		error = dquot_load_quota_inode(d_inode(dentry), type, क्रमmat_id,
				DQUOT_USAGE_ENABLED | DQUOT_LIMITS_ENABLED);

	dput(dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL(dquot_quota_on_mount);

अटल पूर्णांक dquot_quota_enable(काष्ठा super_block *sb, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;
	पूर्णांक type;
	काष्ठा quota_info *dqopt = sb_dqopt(sb);

	अगर (!(dqopt->flags & DQUOT_QUOTA_SYS_खाता))
		वापस -ENOSYS;
	/* Accounting cannot be turned on जबतक fs is mounted */
	flags &= ~(FS_QUOTA_UDQ_ACCT | FS_QUOTA_GDQ_ACCT | FS_QUOTA_PDQ_ACCT);
	अगर (!flags)
		वापस -EINVAL;
	क्रम (type = 0; type < MAXQUOTAS; type++) अणु
		अगर (!(flags & qtype_enक्रमce_flag(type)))
			जारी;
		/* Can't enक्रमce without accounting */
		अगर (!sb_has_quota_usage_enabled(sb, type)) अणु
			ret = -EINVAL;
			जाओ out_err;
		पूर्ण
		अगर (sb_has_quota_limits_enabled(sb, type)) अणु
			ret = -EBUSY;
			जाओ out_err;
		पूर्ण
		spin_lock(&dq_state_lock);
		dqopt->flags |= dquot_state_flag(DQUOT_LIMITS_ENABLED, type);
		spin_unlock(&dq_state_lock);
	पूर्ण
	वापस 0;
out_err:
	/* Backout enक्रमcement enablement we alपढ़ोy did */
	क्रम (type--; type >= 0; type--)  अणु
		अगर (flags & qtype_enक्रमce_flag(type))
			dquot_disable(sb, type, DQUOT_LIMITS_ENABLED);
	पूर्ण
	/* Error code translation क्रम better compatibility with XFS */
	अगर (ret == -EBUSY)
		ret = -EEXIST;
	वापस ret;
पूर्ण

अटल पूर्णांक dquot_quota_disable(काष्ठा super_block *sb, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;
	पूर्णांक type;
	काष्ठा quota_info *dqopt = sb_dqopt(sb);

	अगर (!(dqopt->flags & DQUOT_QUOTA_SYS_खाता))
		वापस -ENOSYS;
	/*
	 * We करोn't support turning off accounting via quotactl. In principle
	 * quota infraकाष्ठाure can करो this but fileप्रणालीs करोn't expect
	 * userspace to be able to करो it.
	 */
	अगर (flags &
		  (FS_QUOTA_UDQ_ACCT | FS_QUOTA_GDQ_ACCT | FS_QUOTA_PDQ_ACCT))
		वापस -EOPNOTSUPP;

	/* Filter out limits not enabled */
	क्रम (type = 0; type < MAXQUOTAS; type++)
		अगर (!sb_has_quota_limits_enabled(sb, type))
			flags &= ~qtype_enक्रमce_flag(type);
	/* Nothing left? */
	अगर (!flags)
		वापस -EEXIST;
	क्रम (type = 0; type < MAXQUOTAS; type++) अणु
		अगर (flags & qtype_enक्रमce_flag(type)) अणु
			ret = dquot_disable(sb, type, DQUOT_LIMITS_ENABLED);
			अगर (ret < 0)
				जाओ out_err;
		पूर्ण
	पूर्ण
	वापस 0;
out_err:
	/* Backout enक्रमcement disabling we alपढ़ोy did */
	क्रम (type--; type >= 0; type--)  अणु
		अगर (flags & qtype_enक्रमce_flag(type)) अणु
			spin_lock(&dq_state_lock);
			dqopt->flags |=
				dquot_state_flag(DQUOT_LIMITS_ENABLED, type);
			spin_unlock(&dq_state_lock);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* Generic routine क्रम getting common part of quota काष्ठाure */
अटल व्योम करो_get_dqblk(काष्ठा dquot *dquot, काष्ठा qc_dqblk *di)
अणु
	काष्ठा mem_dqblk *dm = &dquot->dq_dqb;

	स_रखो(di, 0, माप(*di));
	spin_lock(&dquot->dq_dqb_lock);
	di->d_spc_hardlimit = dm->dqb_bhardlimit;
	di->d_spc_softlimit = dm->dqb_bsoftlimit;
	di->d_ino_hardlimit = dm->dqb_ihardlimit;
	di->d_ino_softlimit = dm->dqb_isoftlimit;
	di->d_space = dm->dqb_curspace + dm->dqb_rsvspace;
	di->d_ino_count = dm->dqb_curinodes;
	di->d_spc_समयr = dm->dqb_bसमय;
	di->d_ino_समयr = dm->dqb_iसमय;
	spin_unlock(&dquot->dq_dqb_lock);
पूर्ण

पूर्णांक dquot_get_dqblk(काष्ठा super_block *sb, काष्ठा kqid qid,
		    काष्ठा qc_dqblk *di)
अणु
	काष्ठा dquot *dquot;

	dquot = dqget(sb, qid);
	अगर (IS_ERR(dquot))
		वापस PTR_ERR(dquot);
	करो_get_dqblk(dquot, di);
	dqput(dquot);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dquot_get_dqblk);

पूर्णांक dquot_get_next_dqblk(काष्ठा super_block *sb, काष्ठा kqid *qid,
			 काष्ठा qc_dqblk *di)
अणु
	काष्ठा dquot *dquot;
	पूर्णांक err;

	अगर (!sb->dq_op->get_next_id)
		वापस -ENOSYS;
	err = sb->dq_op->get_next_id(sb, qid);
	अगर (err < 0)
		वापस err;
	dquot = dqget(sb, *qid);
	अगर (IS_ERR(dquot))
		वापस PTR_ERR(dquot);
	करो_get_dqblk(dquot, di);
	dqput(dquot);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dquot_get_next_dqblk);

#घोषणा VFS_QC_MASK \
	(QC_SPACE | QC_SPC_SOFT | QC_SPC_HARD | \
	 QC_INO_COUNT | QC_INO_SOFT | QC_INO_HARD | \
	 QC_SPC_TIMER | QC_INO_TIMER)

/* Generic routine क्रम setting common part of quota काष्ठाure */
अटल पूर्णांक करो_set_dqblk(काष्ठा dquot *dquot, काष्ठा qc_dqblk *di)
अणु
	काष्ठा mem_dqblk *dm = &dquot->dq_dqb;
	पूर्णांक check_blim = 0, check_ilim = 0;
	काष्ठा mem_dqinfo *dqi = &sb_dqopt(dquot->dq_sb)->info[dquot->dq_id.type];

	अगर (di->d_fieldmask & ~VFS_QC_MASK)
		वापस -EINVAL;

	अगर (((di->d_fieldmask & QC_SPC_SOFT) &&
	     di->d_spc_softlimit > dqi->dqi_max_spc_limit) ||
	    ((di->d_fieldmask & QC_SPC_HARD) &&
	     di->d_spc_hardlimit > dqi->dqi_max_spc_limit) ||
	    ((di->d_fieldmask & QC_INO_SOFT) &&
	     (di->d_ino_softlimit > dqi->dqi_max_ino_limit)) ||
	    ((di->d_fieldmask & QC_INO_HARD) &&
	     (di->d_ino_hardlimit > dqi->dqi_max_ino_limit)))
		वापस -दुस्फल;

	spin_lock(&dquot->dq_dqb_lock);
	अगर (di->d_fieldmask & QC_SPACE) अणु
		dm->dqb_curspace = di->d_space - dm->dqb_rsvspace;
		check_blim = 1;
		set_bit(DQ_LASTSET_B + QIF_SPACE_B, &dquot->dq_flags);
	पूर्ण

	अगर (di->d_fieldmask & QC_SPC_SOFT)
		dm->dqb_bsoftlimit = di->d_spc_softlimit;
	अगर (di->d_fieldmask & QC_SPC_HARD)
		dm->dqb_bhardlimit = di->d_spc_hardlimit;
	अगर (di->d_fieldmask & (QC_SPC_SOFT | QC_SPC_HARD)) अणु
		check_blim = 1;
		set_bit(DQ_LASTSET_B + QIF_BLIMITS_B, &dquot->dq_flags);
	पूर्ण

	अगर (di->d_fieldmask & QC_INO_COUNT) अणु
		dm->dqb_curinodes = di->d_ino_count;
		check_ilim = 1;
		set_bit(DQ_LASTSET_B + QIF_INODES_B, &dquot->dq_flags);
	पूर्ण

	अगर (di->d_fieldmask & QC_INO_SOFT)
		dm->dqb_isoftlimit = di->d_ino_softlimit;
	अगर (di->d_fieldmask & QC_INO_HARD)
		dm->dqb_ihardlimit = di->d_ino_hardlimit;
	अगर (di->d_fieldmask & (QC_INO_SOFT | QC_INO_HARD)) अणु
		check_ilim = 1;
		set_bit(DQ_LASTSET_B + QIF_ILIMITS_B, &dquot->dq_flags);
	पूर्ण

	अगर (di->d_fieldmask & QC_SPC_TIMER) अणु
		dm->dqb_bसमय = di->d_spc_समयr;
		check_blim = 1;
		set_bit(DQ_LASTSET_B + QIF_BTIME_B, &dquot->dq_flags);
	पूर्ण

	अगर (di->d_fieldmask & QC_INO_TIMER) अणु
		dm->dqb_iसमय = di->d_ino_समयr;
		check_ilim = 1;
		set_bit(DQ_LASTSET_B + QIF_ITIME_B, &dquot->dq_flags);
	पूर्ण

	अगर (check_blim) अणु
		अगर (!dm->dqb_bsoftlimit ||
		    dm->dqb_curspace + dm->dqb_rsvspace <= dm->dqb_bsoftlimit) अणु
			dm->dqb_bसमय = 0;
			clear_bit(DQ_BLKS_B, &dquot->dq_flags);
		पूर्ण अन्यथा अगर (!(di->d_fieldmask & QC_SPC_TIMER))
			/* Set grace only अगर user hasn't provided his own... */
			dm->dqb_bसमय = kसमय_get_real_seconds() + dqi->dqi_bgrace;
	पूर्ण
	अगर (check_ilim) अणु
		अगर (!dm->dqb_isoftlimit ||
		    dm->dqb_curinodes <= dm->dqb_isoftlimit) अणु
			dm->dqb_iसमय = 0;
			clear_bit(DQ_INODES_B, &dquot->dq_flags);
		पूर्ण अन्यथा अगर (!(di->d_fieldmask & QC_INO_TIMER))
			/* Set grace only अगर user hasn't provided his own... */
			dm->dqb_iसमय = kसमय_get_real_seconds() + dqi->dqi_igrace;
	पूर्ण
	अगर (dm->dqb_bhardlimit || dm->dqb_bsoftlimit || dm->dqb_ihardlimit ||
	    dm->dqb_isoftlimit)
		clear_bit(DQ_FAKE_B, &dquot->dq_flags);
	अन्यथा
		set_bit(DQ_FAKE_B, &dquot->dq_flags);
	spin_unlock(&dquot->dq_dqb_lock);
	mark_dquot_dirty(dquot);

	वापस 0;
पूर्ण

पूर्णांक dquot_set_dqblk(काष्ठा super_block *sb, काष्ठा kqid qid,
		  काष्ठा qc_dqblk *di)
अणु
	काष्ठा dquot *dquot;
	पूर्णांक rc;

	dquot = dqget(sb, qid);
	अगर (IS_ERR(dquot)) अणु
		rc = PTR_ERR(dquot);
		जाओ out;
	पूर्ण
	rc = करो_set_dqblk(dquot, di);
	dqput(dquot);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(dquot_set_dqblk);

/* Generic routine क्रम getting common part of quota file inक्रमmation */
पूर्णांक dquot_get_state(काष्ठा super_block *sb, काष्ठा qc_state *state)
अणु
	काष्ठा mem_dqinfo *mi;
	काष्ठा qc_type_state *tstate;
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	पूर्णांक type;

	स_रखो(state, 0, माप(*state));
	क्रम (type = 0; type < MAXQUOTAS; type++) अणु
		अगर (!sb_has_quota_active(sb, type))
			जारी;
		tstate = state->s_state + type;
		mi = sb_dqopt(sb)->info + type;
		tstate->flags = QCI_ACCT_ENABLED;
		spin_lock(&dq_data_lock);
		अगर (mi->dqi_flags & DQF_SYS_खाता)
			tstate->flags |= QCI_SYSखाता;
		अगर (mi->dqi_flags & DQF_ROOT_SQUASH)
			tstate->flags |= QCI_ROOT_SQUASH;
		अगर (sb_has_quota_limits_enabled(sb, type))
			tstate->flags |= QCI_LIMITS_ENFORCED;
		tstate->spc_समयlimit = mi->dqi_bgrace;
		tstate->ino_समयlimit = mi->dqi_igrace;
		अगर (dqopt->files[type]) अणु
			tstate->ino = dqopt->files[type]->i_ino;
			tstate->blocks = dqopt->files[type]->i_blocks;
		पूर्ण
		tstate->nextents = 1;	/* We करोn't know... */
		spin_unlock(&dq_data_lock);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dquot_get_state);

/* Generic routine क्रम setting common part of quota file inक्रमmation */
पूर्णांक dquot_set_dqinfo(काष्ठा super_block *sb, पूर्णांक type, काष्ठा qc_info *ii)
अणु
	काष्ठा mem_dqinfo *mi;
	पूर्णांक err = 0;

	अगर ((ii->i_fieldmask & QC_WARNS_MASK) ||
	    (ii->i_fieldmask & QC_RT_SPC_TIMER))
		वापस -EINVAL;
	अगर (!sb_has_quota_active(sb, type))
		वापस -ESRCH;
	mi = sb_dqopt(sb)->info + type;
	अगर (ii->i_fieldmask & QC_FLAGS) अणु
		अगर ((ii->i_flags & QCI_ROOT_SQUASH &&
		     mi->dqi_क्रमmat->qf_fmt_id != QFMT_VFS_OLD))
			वापस -EINVAL;
	पूर्ण
	spin_lock(&dq_data_lock);
	अगर (ii->i_fieldmask & QC_SPC_TIMER)
		mi->dqi_bgrace = ii->i_spc_समयlimit;
	अगर (ii->i_fieldmask & QC_INO_TIMER)
		mi->dqi_igrace = ii->i_ino_समयlimit;
	अगर (ii->i_fieldmask & QC_FLAGS) अणु
		अगर (ii->i_flags & QCI_ROOT_SQUASH)
			mi->dqi_flags |= DQF_ROOT_SQUASH;
		अन्यथा
			mi->dqi_flags &= ~DQF_ROOT_SQUASH;
	पूर्ण
	spin_unlock(&dq_data_lock);
	mark_info_dirty(sb, type);
	/* Force ग_लिखो to disk */
	sb->dq_op->ग_लिखो_info(sb, type);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dquot_set_dqinfo);

स्थिर काष्ठा quotactl_ops dquot_quotactl_sysfile_ops = अणु
	.quota_enable	= dquot_quota_enable,
	.quota_disable	= dquot_quota_disable,
	.quota_sync	= dquot_quota_sync,
	.get_state	= dquot_get_state,
	.set_info	= dquot_set_dqinfo,
	.get_dqblk	= dquot_get_dqblk,
	.get_nextdqblk	= dquot_get_next_dqblk,
	.set_dqblk	= dquot_set_dqblk
पूर्ण;
EXPORT_SYMBOL(dquot_quotactl_sysfile_ops);

अटल पूर्णांक करो_proc_dqstats(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक type = (अचिन्हित दीर्घ *)table->data - dqstats.stat;
	s64 value = percpu_counter_sum(&dqstats.counter[type]);

	/* Filter negative values क्रम non-monotonic counters */
	अगर (value < 0 && (type == DQST_ALLOC_DQUOTS ||
			  type == DQST_FREE_DQUOTS))
		value = 0;

	/* Update global table */
	dqstats.stat[type] = value;
	वापस proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल काष्ठा ctl_table fs_dqstats_table[] = अणु
	अणु
		.procname	= "lookups",
		.data		= &dqstats.stat[DQST_LOOKUPS],
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0444,
		.proc_handler	= करो_proc_dqstats,
	पूर्ण,
	अणु
		.procname	= "drops",
		.data		= &dqstats.stat[DQST_DROPS],
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0444,
		.proc_handler	= करो_proc_dqstats,
	पूर्ण,
	अणु
		.procname	= "reads",
		.data		= &dqstats.stat[DQST_READS],
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0444,
		.proc_handler	= करो_proc_dqstats,
	पूर्ण,
	अणु
		.procname	= "writes",
		.data		= &dqstats.stat[DQST_WRITES],
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0444,
		.proc_handler	= करो_proc_dqstats,
	पूर्ण,
	अणु
		.procname	= "cache_hits",
		.data		= &dqstats.stat[DQST_CACHE_HITS],
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0444,
		.proc_handler	= करो_proc_dqstats,
	पूर्ण,
	अणु
		.procname	= "allocated_dquots",
		.data		= &dqstats.stat[DQST_ALLOC_DQUOTS],
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0444,
		.proc_handler	= करो_proc_dqstats,
	पूर्ण,
	अणु
		.procname	= "free_dquots",
		.data		= &dqstats.stat[DQST_FREE_DQUOTS],
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0444,
		.proc_handler	= करो_proc_dqstats,
	पूर्ण,
	अणु
		.procname	= "syncs",
		.data		= &dqstats.stat[DQST_SYNCS],
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0444,
		.proc_handler	= करो_proc_dqstats,
	पूर्ण,
#अगर_घोषित CONFIG_PRINT_QUOTA_WARNING
	अणु
		.procname	= "warnings",
		.data		= &flag_prपूर्णांक_warnings,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table fs_table[] = अणु
	अणु
		.procname	= "quota",
		.mode		= 0555,
		.child		= fs_dqstats_table,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table sys_table[] = अणु
	अणु
		.procname	= "fs",
		.mode		= 0555,
		.child		= fs_table,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __init dquot_init(व्योम)
अणु
	पूर्णांक i, ret;
	अचिन्हित दीर्घ nr_hash, order;

	prपूर्णांकk(KERN_NOTICE "VFS: Disk quotas %s\n", __DQUOT_VERSION__);

	रेजिस्टर_sysctl_table(sys_table);

	dquot_cachep = kmem_cache_create("dquot",
			माप(काष्ठा dquot), माप(अचिन्हित दीर्घ) * 4,
			(SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|
				SLAB_MEM_SPREAD|SLAB_PANIC),
			शून्य);

	order = 0;
	dquot_hash = (काष्ठा hlist_head *)__get_मुक्त_pages(GFP_KERNEL, order);
	अगर (!dquot_hash)
		panic("Cannot create dquot hash table");

	क्रम (i = 0; i < _DQST_DQSTAT_LAST; i++) अणु
		ret = percpu_counter_init(&dqstats.counter[i], 0, GFP_KERNEL);
		अगर (ret)
			panic("Cannot create dquot stat counters");
	पूर्ण

	/* Find घातer-of-two hlist_heads which can fit पूर्णांकo allocation */
	nr_hash = (1UL << order) * PAGE_SIZE / माप(काष्ठा hlist_head);
	dq_hash_bits = ilog2(nr_hash);

	nr_hash = 1UL << dq_hash_bits;
	dq_hash_mask = nr_hash - 1;
	क्रम (i = 0; i < nr_hash; i++)
		INIT_HLIST_HEAD(dquot_hash + i);

	pr_info("VFS: Dquot-cache hash table entries: %ld (order %ld,"
		" %ld bytes)\n", nr_hash, order, (PAGE_SIZE << order));

	अगर (रेजिस्टर_shrinker(&dqcache_shrinker))
		panic("Cannot register dquot shrinker");

	वापस 0;
पूर्ण
fs_initcall(dquot_init);
