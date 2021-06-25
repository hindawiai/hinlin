<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/crc32.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "log.h"
#समावेश "lops.h"
#समावेश "recovery.h"
#समावेश "rgrp.h"
#समावेश "super.h"
#समावेश "util.h"

काष्ठा kmem_cache *gfs2_glock_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *gfs2_glock_aspace_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *gfs2_inode_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *gfs2_bufdata_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *gfs2_rgrpd_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *gfs2_quotad_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *gfs2_qadata_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *gfs2_trans_cachep __पढ़ो_mostly;
mempool_t *gfs2_page_pool __पढ़ो_mostly;

व्योम gfs2_निश्चित_i(काष्ठा gfs2_sbd *sdp)
अणु
	fs_emerg(sdp, "fatal assertion failed\n");
पूर्ण

/**
 * check_journal_clean - Make sure a journal is clean क्रम a spectator mount
 * @sdp: The GFS2 superblock
 * @jd: The journal descriptor
 * @verbose: Show more prपूर्णांकs in the log
 *
 * Returns: 0 अगर the journal is clean or locked, अन्यथा an error
 */
पूर्णांक check_journal_clean(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_jdesc *jd,
			bool verbose)
अणु
	पूर्णांक error;
	काष्ठा gfs2_holder j_gh;
	काष्ठा gfs2_log_header_host head;
	काष्ठा gfs2_inode *ip;

	ip = GFS2_I(jd->jd_inode);
	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_NOEXP |
				   GL_EXACT | GL_NOCACHE, &j_gh);
	अगर (error) अणु
		अगर (verbose)
			fs_err(sdp, "Error %d locking journal for spectator "
			       "mount.\n", error);
		वापस -EPERM;
	पूर्ण
	error = gfs2_jdesc_check(jd);
	अगर (error) अणु
		अगर (verbose)
			fs_err(sdp, "Error checking journal for spectator "
			       "mount.\n");
		जाओ out_unlock;
	पूर्ण
	error = gfs2_find_jhead(jd, &head, false);
	अगर (error) अणु
		अगर (verbose)
			fs_err(sdp, "Error parsing journal for spectator "
			       "mount.\n");
		जाओ out_unlock;
	पूर्ण
	अगर (!(head.lh_flags & GFS2_LOG_HEAD_UNMOUNT)) अणु
		error = -EPERM;
		अगर (verbose)
			fs_err(sdp, "jid=%u: Journal is dirty, so the first "
			       "mounter must not be a spectator.\n",
			       jd->jd_jid);
	पूर्ण

out_unlock:
	gfs2_glock_dq_uninit(&j_gh);
	वापस error;
पूर्ण

/**
 * gfs2_मुक्तze_lock - hold the मुक्तze glock
 * @sdp: the superblock
 * @मुक्तze_gh: poपूर्णांकer to the requested holder
 * @caller_flags: any additional flags needed by the caller
 */
पूर्णांक gfs2_मुक्तze_lock(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_holder *मुक्तze_gh,
		     पूर्णांक caller_flags)
अणु
	पूर्णांक flags = LM_FLAG_NOEXP | GL_EXACT | caller_flags;
	पूर्णांक error;

	error = gfs2_glock_nq_init(sdp->sd_मुक्तze_gl, LM_ST_SHARED, flags,
				   मुक्तze_gh);
	अगर (error && error != GLR_TRYFAILED)
		fs_err(sdp, "can't lock the freeze lock: %d\n", error);
	वापस error;
पूर्ण

व्योम gfs2_मुक्तze_unlock(काष्ठा gfs2_holder *मुक्तze_gh)
अणु
	अगर (gfs2_holder_initialized(मुक्तze_gh))
		gfs2_glock_dq_uninit(मुक्तze_gh);
पूर्ण

अटल व्योम संकेत_our_withdraw(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_glock *live_gl = sdp->sd_live_gh.gh_gl;
	काष्ठा inode *inode;
	काष्ठा gfs2_inode *ip;
	काष्ठा gfs2_glock *i_gl;
	u64 no_क्रमmal_ino;
	पूर्णांक log_ग_लिखो_allowed = test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags);
	पूर्णांक ret = 0;
	पूर्णांक tries;

	अगर (test_bit(SDF_NORECOVERY, &sdp->sd_flags) || !sdp->sd_jdesc)
		वापस;

	gfs2_ail_drain(sdp); /* मुक्तs all transactions */
	inode = sdp->sd_jdesc->jd_inode;
	ip = GFS2_I(inode);
	i_gl = ip->i_gl;
	no_क्रमmal_ino = ip->i_no_क्रमmal_ino;

	/* Prevent any glock dq until withdraw recovery is complete */
	set_bit(SDF_WITHDRAW_RECOVERY, &sdp->sd_flags);
	/*
	 * Don't tell dlm we're bailing until we have no more buffers in the
	 * wind. If journal had an IO error, the log code should just purge
	 * the outstanding buffers rather than submitting new IO. Making the
	 * file प्रणाली पढ़ो-only will flush the journal, etc.
	 *
	 * During a normal unmount, gfs2_make_fs_ro calls gfs2_log_shutकरोwn
	 * which clears SDF_JOURNAL_LIVE. In a withdraw, we must not ग_लिखो
	 * any UNMOUNT log header, so we can't call gfs2_log_shutकरोwn, and
	 * thereक्रमe we need to clear SDF_JOURNAL_LIVE manually.
	 */
	clear_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags);
	अगर (!sb_rकरोnly(sdp->sd_vfs)) अणु
		काष्ठा gfs2_holder मुक्तze_gh;

		gfs2_holder_mark_uninitialized(&मुक्तze_gh);
		अगर (sdp->sd_मुक्तze_gl &&
		    !gfs2_glock_is_locked_by_me(sdp->sd_मुक्तze_gl)) अणु
			ret = gfs2_मुक्तze_lock(sdp, &मुक्तze_gh,
				       log_ग_लिखो_allowed ? 0 : LM_FLAG_TRY);
			अगर (ret == GLR_TRYFAILED)
				ret = 0;
		पूर्ण
		अगर (!ret)
			gfs2_make_fs_ro(sdp);
		gfs2_मुक्तze_unlock(&मुक्तze_gh);
	पूर्ण

	अगर (sdp->sd_lockकाष्ठा.ls_ops->lm_lock == शून्य) अणु /* lock_nolock */
		अगर (!ret)
			ret = -EIO;
		clear_bit(SDF_WITHDRAW_RECOVERY, &sdp->sd_flags);
		जाओ skip_recovery;
	पूर्ण
	/*
	 * Drop the glock क्रम our journal so another node can recover it.
	 */
	अगर (gfs2_holder_initialized(&sdp->sd_journal_gh)) अणु
		gfs2_glock_dq_रुको(&sdp->sd_journal_gh);
		gfs2_holder_uninit(&sdp->sd_journal_gh);
	पूर्ण
	sdp->sd_jinode_gh.gh_flags |= GL_NOCACHE;
	gfs2_glock_dq(&sdp->sd_jinode_gh);
	अगर (test_bit(SDF_FS_FROZEN, &sdp->sd_flags)) अणु
		/* Make sure gfs2_unमुक्तze works अगर partially-frozen */
		flush_work(&sdp->sd_मुक्तze_work);
		atomic_set(&sdp->sd_मुक्तze_state, SFS_FROZEN);
		thaw_super(sdp->sd_vfs);
	पूर्ण अन्यथा अणु
		रुको_on_bit(&i_gl->gl_flags, GLF_DEMOTE,
			    TASK_UNINTERRUPTIBLE);
	पूर्ण

	/*
	 * holder_uninit to क्रमce glock_put, to क्रमce dlm to let go
	 */
	gfs2_holder_uninit(&sdp->sd_jinode_gh);

	/*
	 * Note: We need to be careful here:
	 * Our iput of jd_inode will evict it. The evict will dequeue its
	 * glock, but the glock dq will रुको क्रम the withdraw unless we have
	 * exception code in glock_dq.
	 */
	iput(inode);
	/*
	 * Wait until the journal inode's glock is मुक्तd. This allows try locks
	 * on other nodes to be successful, otherwise we reमुख्य the owner of
	 * the glock as far as dlm is concerned.
	 */
	अगर (i_gl->gl_ops->go_मुक्त) अणु
		set_bit(GLF_FREEING, &i_gl->gl_flags);
		रुको_on_bit(&i_gl->gl_flags, GLF_FREEING, TASK_UNINTERRUPTIBLE);
	पूर्ण

	/*
	 * Dequeue the "live" glock, but keep a reference so it's never मुक्तd.
	 */
	gfs2_glock_hold(live_gl);
	gfs2_glock_dq_रुको(&sdp->sd_live_gh);
	/*
	 * We enqueue the "live" glock in EX so that all other nodes
	 * get a demote request and act on it. We करोn't really want the
	 * lock in EX, so we send a "try" lock with 1CB to produce a callback.
	 */
	fs_warn(sdp, "Requesting recovery of jid %d.\n",
		sdp->sd_lockकाष्ठा.ls_jid);
	gfs2_holder_reinit(LM_ST_EXCLUSIVE, LM_FLAG_TRY_1CB | LM_FLAG_NOEXP,
			   &sdp->sd_live_gh);
	msleep(GL_GLOCK_MAX_HOLD);
	/*
	 * This will likely fail in a cluster, but succeed standalone:
	 */
	ret = gfs2_glock_nq(&sdp->sd_live_gh);

	/*
	 * If we actually got the "live" lock in EX mode, there are no other
	 * nodes available to replay our journal. So we try to replay it
	 * ourselves. We hold the "live" glock to prevent other mounters
	 * during recovery, then just dequeue it and reacquire it in our
	 * normal SH mode. Just in हाल the problem that caused us to
	 * withdraw prevents us from recovering our journal (e.g. io errors
	 * and such) we still check अगर the journal is clean beक्रमe proceeding
	 * but we may रुको क्रमever until another mounter करोes the recovery.
	 */
	अगर (ret == 0) अणु
		fs_warn(sdp, "No other mounters found. Trying to recover our "
			"own journal jid %d.\n", sdp->sd_lockकाष्ठा.ls_jid);
		अगर (gfs2_recover_journal(sdp->sd_jdesc, 1))
			fs_warn(sdp, "Unable to recover our journal jid %d.\n",
				sdp->sd_lockकाष्ठा.ls_jid);
		gfs2_glock_dq_रुको(&sdp->sd_live_gh);
		gfs2_holder_reinit(LM_ST_SHARED, LM_FLAG_NOEXP | GL_EXACT,
				   &sdp->sd_live_gh);
		gfs2_glock_nq(&sdp->sd_live_gh);
	पूर्ण

	gfs2_glock_queue_put(live_gl); /* drop extra reference we acquired */
	clear_bit(SDF_WITHDRAW_RECOVERY, &sdp->sd_flags);

	/*
	 * At this poपूर्णांक our journal is evicted, so we need to get a new inode
	 * क्रम it. Once करोne, we need to call gfs2_find_jhead which
	 * calls gfs2_map_journal_extents to map it क्रम us again.
	 *
	 * Note that we करोn't really want it to look up a FREE block. The
	 * GFS2_BLKST_FREE simply overrides a block check in gfs2_inode_lookup
	 * which would otherwise fail because it requires grabbing an rgrp
	 * glock, which would fail with -EIO because we're withdrawing.
	 */
	inode = gfs2_inode_lookup(sdp->sd_vfs, DT_UNKNOWN,
				  sdp->sd_jdesc->jd_no_addr, no_क्रमmal_ino,
				  GFS2_BLKST_FREE);
	अगर (IS_ERR(inode)) अणु
		fs_warn(sdp, "Reprocessing of jid %d failed with %ld.\n",
			sdp->sd_lockकाष्ठा.ls_jid, PTR_ERR(inode));
		जाओ skip_recovery;
	पूर्ण
	sdp->sd_jdesc->jd_inode = inode;

	/*
	 * Now रुको until recovery is complete.
	 */
	क्रम (tries = 0; tries < 10; tries++) अणु
		ret = check_journal_clean(sdp, sdp->sd_jdesc, false);
		अगर (!ret)
			अवरोध;
		msleep(HZ);
		fs_warn(sdp, "Waiting for journal recovery jid %d.\n",
			sdp->sd_lockकाष्ठा.ls_jid);
	पूर्ण
skip_recovery:
	अगर (!ret)
		fs_warn(sdp, "Journal recovery complete for jid %d.\n",
			sdp->sd_lockकाष्ठा.ls_jid);
	अन्यथा
		fs_warn(sdp, "Journal recovery skipped for %d until next "
			"mount.\n", sdp->sd_lockकाष्ठा.ls_jid);
	fs_warn(sdp, "Glock dequeues delayed: %lu\n", sdp->sd_glock_dqs_held);
	sdp->sd_glock_dqs_held = 0;
	wake_up_bit(&sdp->sd_flags, SDF_WITHDRAW_RECOVERY);
पूर्ण

व्योम gfs2_lm(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (sdp->sd_args.ar_errors == GFS2_ERRORS_WITHDRAW &&
	    test_bit(SDF_WITHDRAWN, &sdp->sd_flags))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	fs_err(sdp, "%pV", &vaf);
	बहु_पूर्ण(args);
पूर्ण

पूर्णांक gfs2_withdraw(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	स्थिर काष्ठा lm_lockops *lm = ls->ls_ops;

	अगर (sdp->sd_args.ar_errors == GFS2_ERRORS_WITHDRAW &&
	    test_and_set_bit(SDF_WITHDRAWN, &sdp->sd_flags)) अणु
		अगर (!test_bit(SDF_WITHDRAW_IN_PROG, &sdp->sd_flags))
			वापस -1;

		रुको_on_bit(&sdp->sd_flags, SDF_WITHDRAW_IN_PROG,
			    TASK_UNINTERRUPTIBLE);
		वापस -1;
	पूर्ण

	set_bit(SDF_WITHDRAW_IN_PROG, &sdp->sd_flags);

	अगर (sdp->sd_args.ar_errors == GFS2_ERRORS_WITHDRAW) अणु
		fs_err(sdp, "about to withdraw this file system\n");
		BUG_ON(sdp->sd_args.ar_debug);

		संकेत_our_withdraw(sdp);

		kobject_uevent(&sdp->sd_kobj, KOBJ_OFFLINE);

		अगर (!म_भेद(sdp->sd_lockकाष्ठा.ls_ops->lm_proto_name, "lock_dlm"))
			रुको_क्रम_completion(&sdp->sd_wdack);

		अगर (lm->lm_unmount) अणु
			fs_err(sdp, "telling LM to unmount\n");
			lm->lm_unmount(sdp);
		पूर्ण
		set_bit(SDF_SKIP_DLM_UNLOCK, &sdp->sd_flags);
		fs_err(sdp, "File system withdrawn\n");
		dump_stack();
		clear_bit(SDF_WITHDRAW_IN_PROG, &sdp->sd_flags);
		smp_mb__after_atomic();
		wake_up_bit(&sdp->sd_flags, SDF_WITHDRAW_IN_PROG);
	पूर्ण

	अगर (sdp->sd_args.ar_errors == GFS2_ERRORS_PANIC)
		panic("GFS2: fsid=%s: panic requested\n", sdp->sd_fsname);

	वापस -1;
पूर्ण

/*
 * gfs2_निश्चित_withdraw_i - Cause the machine to withdraw अगर @निश्चितion is false
 */

व्योम gfs2_निश्चित_withdraw_i(काष्ठा gfs2_sbd *sdp, अक्षर *निश्चितion,
			    स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line,
			    bool delayed)
अणु
	अगर (gfs2_withdrawn(sdp))
		वापस;

	fs_err(sdp,
	       "fatal: assertion \"%s\" failed\n"
	       "   function = %s, file = %s, line = %u\n",
	       निश्चितion, function, file, line);

	/*
	 * If errors=panic was specअगरied on mount, it won't help to delay the
	 * withdraw.
	 */
	अगर (sdp->sd_args.ar_errors == GFS2_ERRORS_PANIC)
		delayed = false;

	अगर (delayed)
		gfs2_withdraw_delayed(sdp);
	अन्यथा
		gfs2_withdraw(sdp);
	dump_stack();
पूर्ण

/*
 * gfs2_निश्चित_warn_i - Prपूर्णांक a message to the console अगर @निश्चितion is false
 */

व्योम gfs2_निश्चित_warn_i(काष्ठा gfs2_sbd *sdp, अक्षर *निश्चितion,
			स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line)
अणु
	अगर (समय_beक्रमe(jअगरfies,
			sdp->sd_last_warning +
			gfs2_tune_get(sdp, gt_complain_secs) * HZ))
		वापस;

	अगर (sdp->sd_args.ar_errors == GFS2_ERRORS_WITHDRAW)
		fs_warn(sdp, "warning: assertion \"%s\" failed at function = %s, file = %s, line = %u\n",
			निश्चितion, function, file, line);

	अगर (sdp->sd_args.ar_debug)
		BUG();
	अन्यथा
		dump_stack();

	अगर (sdp->sd_args.ar_errors == GFS2_ERRORS_PANIC)
		panic("GFS2: fsid=%s: warning: assertion \"%s\" failed\n"
		      "GFS2: fsid=%s:   function = %s, file = %s, line = %u\n",
		      sdp->sd_fsname, निश्चितion,
		      sdp->sd_fsname, function, file, line);

	sdp->sd_last_warning = jअगरfies;
पूर्ण

/*
 * gfs2_consist_i - Flag a fileप्रणाली consistency error and withdraw
 */

व्योम gfs2_consist_i(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *function,
		    अक्षर *file, अचिन्हित पूर्णांक line)
अणु
	gfs2_lm(sdp,
		"fatal: filesystem consistency error - function = %s, file = %s, line = %u\n",
		function, file, line);
	gfs2_withdraw(sdp);
पूर्ण

/*
 * gfs2_consist_inode_i - Flag an inode consistency error and withdraw
 */

व्योम gfs2_consist_inode_i(काष्ठा gfs2_inode *ip,
			  स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	gfs2_lm(sdp,
		"fatal: filesystem consistency error\n"
		"  inode = %llu %llu\n"
		"  function = %s, file = %s, line = %u\n",
		(अचिन्हित दीर्घ दीर्घ)ip->i_no_क्रमmal_ino,
		(अचिन्हित दीर्घ दीर्घ)ip->i_no_addr,
		function, file, line);
	gfs2_withdraw(sdp);
पूर्ण

/*
 * gfs2_consist_rgrpd_i - Flag a RG consistency error and withdraw
 */

व्योम gfs2_consist_rgrpd_i(काष्ठा gfs2_rgrpd *rgd,
			  स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line)
अणु
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;
	अक्षर fs_id_buf[माप(sdp->sd_fsname) + 7];

	प्र_लिखो(fs_id_buf, "fsid=%s: ", sdp->sd_fsname);
	gfs2_rgrp_dump(शून्य, rgd, fs_id_buf);
	gfs2_lm(sdp,
		"fatal: filesystem consistency error\n"
		"  RG = %llu\n"
		"  function = %s, file = %s, line = %u\n",
		(अचिन्हित दीर्घ दीर्घ)rgd->rd_addr,
		function, file, line);
	gfs2_withdraw(sdp);
पूर्ण

/*
 * gfs2_meta_check_ii - Flag a magic number consistency error and withdraw
 * Returns: -1 अगर this call withdrew the machine,
 *          -2 अगर it was alपढ़ोy withdrawn
 */

पूर्णांक gfs2_meta_check_ii(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh,
		       स्थिर अक्षर *type, स्थिर अक्षर *function, अक्षर *file,
		       अचिन्हित पूर्णांक line)
अणु
	पूर्णांक me;

	gfs2_lm(sdp,
		"fatal: invalid metadata block\n"
		"  bh = %llu (%s)\n"
		"  function = %s, file = %s, line = %u\n",
		(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, type,
		function, file, line);
	me = gfs2_withdraw(sdp);
	वापस (me) ? -1 : -2;
पूर्ण

/*
 * gfs2_metatype_check_ii - Flag a metadata type consistency error and withdraw
 * Returns: -1 अगर this call withdrew the machine,
 *          -2 अगर it was alपढ़ोy withdrawn
 */

पूर्णांक gfs2_metatype_check_ii(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh,
			   u16 type, u16 t, स्थिर अक्षर *function,
			   अक्षर *file, अचिन्हित पूर्णांक line)
अणु
	पूर्णांक me;

	gfs2_lm(sdp,
		"fatal: invalid metadata block\n"
		"  bh = %llu (type: exp=%u, found=%u)\n"
		"  function = %s, file = %s, line = %u\n",
		(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, type, t,
		function, file, line);
	me = gfs2_withdraw(sdp);
	वापस (me) ? -1 : -2;
पूर्ण

/*
 * gfs2_io_error_i - Flag an I/O error and withdraw
 * Returns: -1 अगर this call withdrew the machine,
 *          0 अगर it was alपढ़ोy withdrawn
 */

पूर्णांक gfs2_io_error_i(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *function, अक्षर *file,
		    अचिन्हित पूर्णांक line)
अणु
	gfs2_lm(sdp,
		"fatal: I/O error\n"
		"  function = %s, file = %s, line = %u\n",
		function, file, line);
	वापस gfs2_withdraw(sdp);
पूर्ण

/*
 * gfs2_io_error_bh_i - Flag a buffer I/O error
 * @withdraw: withdraw the fileप्रणाली
 */

व्योम gfs2_io_error_bh_i(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh,
			स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line,
			bool withdraw)
अणु
	अगर (gfs2_withdrawn(sdp))
		वापस;

	fs_err(sdp, "fatal: I/O error\n"
	       "  block = %llu\n"
	       "  function = %s, file = %s, line = %u\n",
	       (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, function, file, line);
	अगर (withdraw)
		gfs2_withdraw(sdp);
पूर्ण

