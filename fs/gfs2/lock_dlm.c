<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright 2004-2011 Red Hat, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/dlm.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "incore.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "recovery.h"
#समावेश "util.h"
#समावेश "sys.h"
#समावेश "trace_gfs2.h"

/**
 * gfs2_update_stats - Update समय based stats
 * @s: The stats to update (local or global)
 * @index: The index inside @s
 * @sample: New data to include
 */
अटल अंतरभूत व्योम gfs2_update_stats(काष्ठा gfs2_lkstats *s, अचिन्हित index,
				     s64 sample)
अणु
	/*
	 * @delta is the dअगरference between the current rtt sample and the
	 * running average srtt. We add 1/8 of that to the srtt in order to
	 * update the current srtt estimate. The variance estimate is a bit
	 * more complicated. We subtract the current variance estimate from
	 * the असल value of the @delta and add 1/4 of that to the running
	 * total.  That's equivalent to 3/4 of the current variance
	 * estimate plus 1/4 of the असल of @delta.
	 *
	 * Note that the index poपूर्णांकs at the array entry containing the
	 * smoothed mean value, and the variance is always in the following
	 * entry
	 *
	 * Reference: TCP/IP Illustrated, vol 2, p. 831,832
	 * All बार are in units of पूर्णांकeger nanoseconds. Unlike the TCP/IP
	 * हाल, they are not scaled fixed poपूर्णांक.
	 */

	s64 delta = sample - s->stats[index];
	s->stats[index] += (delta >> 3);
	index++;
	s->stats[index] += (s64)(असल(delta) - s->stats[index]) >> 2;
पूर्ण

/**
 * gfs2_update_reply_बार - Update locking statistics
 * @gl: The glock to update
 *
 * This assumes that gl->gl_dstamp has been set earlier.
 *
 * The rtt (lock round trip समय) is an estimate of the समय
 * taken to perक्रमm a dlm lock request. We update it on each
 * reply from the dlm.
 *
 * The blocking flag is set on the glock क्रम all dlm requests
 * which may potentially block due to lock requests from other nodes.
 * DLM requests where the current lock state is exclusive, the
 * requested state is null (or unlocked) or where the TRY or
 * TRY_1CB flags are set are classअगरied as non-blocking. All
 * other DLM requests are counted as (potentially) blocking.
 */
अटल अंतरभूत व्योम gfs2_update_reply_बार(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_pcpu_lkstats *lks;
	स्थिर अचिन्हित gltype = gl->gl_name.ln_type;
	अचिन्हित index = test_bit(GLF_BLOCKING, &gl->gl_flags) ?
			 GFS2_LKS_SRTTB : GFS2_LKS_SRTT;
	s64 rtt;

	preempt_disable();
	rtt = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get_real(), gl->gl_dstamp));
	lks = this_cpu_ptr(gl->gl_name.ln_sbd->sd_lkstats);
	gfs2_update_stats(&gl->gl_stats, index, rtt);		/* Local */
	gfs2_update_stats(&lks->lkstats[gltype], index, rtt);	/* Global */
	preempt_enable();

	trace_gfs2_glock_lock_समय(gl, rtt);
पूर्ण

/**
 * gfs2_update_request_बार - Update locking statistics
 * @gl: The glock to update
 *
 * The irt (lock पूर्णांकer-request बार) measures the average समय
 * between requests to the dlm. It is updated immediately beक्रमe
 * each dlm call.
 */

अटल अंतरभूत व्योम gfs2_update_request_बार(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_pcpu_lkstats *lks;
	स्थिर अचिन्हित gltype = gl->gl_name.ln_type;
	kसमय_प्रकार dstamp;
	s64 irt;

	preempt_disable();
	dstamp = gl->gl_dstamp;
	gl->gl_dstamp = kसमय_get_real();
	irt = kसमय_प्रकारo_ns(kसमय_sub(gl->gl_dstamp, dstamp));
	lks = this_cpu_ptr(gl->gl_name.ln_sbd->sd_lkstats);
	gfs2_update_stats(&gl->gl_stats, GFS2_LKS_SIRT, irt);		/* Local */
	gfs2_update_stats(&lks->lkstats[gltype], GFS2_LKS_SIRT, irt);	/* Global */
	preempt_enable();
पूर्ण
 
अटल व्योम gdlm_ast(व्योम *arg)
अणु
	काष्ठा gfs2_glock *gl = arg;
	अचिन्हित ret = gl->gl_state;

	gfs2_update_reply_बार(gl);
	BUG_ON(gl->gl_lksb.sb_flags & DLM_SBF_DEMOTED);

	अगर ((gl->gl_lksb.sb_flags & DLM_SBF_VALNOTVALID) && gl->gl_lksb.sb_lvbptr)
		स_रखो(gl->gl_lksb.sb_lvbptr, 0, GDLM_LVB_SIZE);

	चयन (gl->gl_lksb.sb_status) अणु
	हाल -DLM_EUNLOCK: /* Unlocked, so glock can be मुक्तd */
		अगर (gl->gl_ops->go_मुक्त)
			gl->gl_ops->go_मुक्त(gl);
		gfs2_glock_मुक्त(gl);
		वापस;
	हाल -DLM_ECANCEL: /* Cancel जबतक getting lock */
		ret |= LM_OUT_CANCELED;
		जाओ out;
	हाल -EAGAIN: /* Try lock fails */
	हाल -EDEADLK: /* Deadlock detected */
		जाओ out;
	हाल -ETIMEDOUT: /* Canceled due to समयout */
		ret |= LM_OUT_ERROR;
		जाओ out;
	हाल 0: /* Success */
		अवरोध;
	शेष: /* Something unexpected */
		BUG();
	पूर्ण

	ret = gl->gl_req;
	अगर (gl->gl_lksb.sb_flags & DLM_SBF_ALTMODE) अणु
		अगर (gl->gl_req == LM_ST_SHARED)
			ret = LM_ST_DEFERRED;
		अन्यथा अगर (gl->gl_req == LM_ST_DEFERRED)
			ret = LM_ST_SHARED;
		अन्यथा
			BUG();
	पूर्ण

	set_bit(GLF_INITIAL, &gl->gl_flags);
	gfs2_glock_complete(gl, ret);
	वापस;
out:
	अगर (!test_bit(GLF_INITIAL, &gl->gl_flags))
		gl->gl_lksb.sb_lkid = 0;
	gfs2_glock_complete(gl, ret);
पूर्ण

अटल व्योम gdlm_bast(व्योम *arg, पूर्णांक mode)
अणु
	काष्ठा gfs2_glock *gl = arg;

	चयन (mode) अणु
	हाल DLM_LOCK_EX:
		gfs2_glock_cb(gl, LM_ST_UNLOCKED);
		अवरोध;
	हाल DLM_LOCK_CW:
		gfs2_glock_cb(gl, LM_ST_DEFERRED);
		अवरोध;
	हाल DLM_LOCK_PR:
		gfs2_glock_cb(gl, LM_ST_SHARED);
		अवरोध;
	शेष:
		fs_err(gl->gl_name.ln_sbd, "unknown bast mode %d\n", mode);
		BUG();
	पूर्ण
पूर्ण

/* convert gfs lock-state to dlm lock-mode */

अटल पूर्णांक make_mode(काष्ठा gfs2_sbd *sdp, स्थिर अचिन्हित पूर्णांक lmstate)
अणु
	चयन (lmstate) अणु
	हाल LM_ST_UNLOCKED:
		वापस DLM_LOCK_NL;
	हाल LM_ST_EXCLUSIVE:
		वापस DLM_LOCK_EX;
	हाल LM_ST_DEFERRED:
		वापस DLM_LOCK_CW;
	हाल LM_ST_SHARED:
		वापस DLM_LOCK_PR;
	पूर्ण
	fs_err(sdp, "unknown LM state %d\n", lmstate);
	BUG();
	वापस -1;
पूर्ण

अटल u32 make_flags(काष्ठा gfs2_glock *gl, स्थिर अचिन्हित पूर्णांक gfs_flags,
		      स्थिर पूर्णांक req)
अणु
	u32 lkf = 0;

	अगर (gl->gl_lksb.sb_lvbptr)
		lkf |= DLM_LKF_VALBLK;

	अगर (gfs_flags & LM_FLAG_TRY)
		lkf |= DLM_LKF_NOQUEUE;

	अगर (gfs_flags & LM_FLAG_TRY_1CB) अणु
		lkf |= DLM_LKF_NOQUEUE;
		lkf |= DLM_LKF_NOQUEUEBAST;
	पूर्ण

	अगर (gfs_flags & LM_FLAG_PRIORITY) अणु
		lkf |= DLM_LKF_NOORDER;
		lkf |= DLM_LKF_HEADQUE;
	पूर्ण

	अगर (gfs_flags & LM_FLAG_ANY) अणु
		अगर (req == DLM_LOCK_PR)
			lkf |= DLM_LKF_ALTCW;
		अन्यथा अगर (req == DLM_LOCK_CW)
			lkf |= DLM_LKF_ALTPR;
		अन्यथा
			BUG();
	पूर्ण

	अगर (gl->gl_lksb.sb_lkid != 0) अणु
		lkf |= DLM_LKF_CONVERT;
		अगर (test_bit(GLF_BLOCKING, &gl->gl_flags))
			lkf |= DLM_LKF_QUECVT;
	पूर्ण

	वापस lkf;
पूर्ण

अटल व्योम gfs2_reverse_hex(अक्षर *c, u64 value)
अणु
	*c = '0';
	जबतक (value) अणु
		*c-- = hex_asc[value & 0x0f];
		value >>= 4;
	पूर्ण
पूर्ण

अटल पूर्णांक gdlm_lock(काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक req_state,
		     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &gl->gl_name.ln_sbd->sd_lockकाष्ठा;
	पूर्णांक req;
	u32 lkf;
	अक्षर strname[GDLM_STRNAME_BYTES] = "";

	req = make_mode(gl->gl_name.ln_sbd, req_state);
	lkf = make_flags(gl, flags, req);
	gfs2_glstats_inc(gl, GFS2_LKS_DCOUNT);
	gfs2_sbstats_inc(gl, GFS2_LKS_DCOUNT);
	अगर (gl->gl_lksb.sb_lkid) अणु
		gfs2_update_request_बार(gl);
	पूर्ण अन्यथा अणु
		स_रखो(strname, ' ', GDLM_STRNAME_BYTES - 1);
		strname[GDLM_STRNAME_BYTES - 1] = '\0';
		gfs2_reverse_hex(strname + 7, gl->gl_name.ln_type);
		gfs2_reverse_hex(strname + 23, gl->gl_name.ln_number);
		gl->gl_dstamp = kसमय_get_real();
	पूर्ण
	/*
	 * Submit the actual lock request.
	 */

	वापस dlm_lock(ls->ls_dlm, req, &gl->gl_lksb, lkf, strname,
			GDLM_STRNAME_BYTES - 1, 0, gdlm_ast, gl, gdlm_bast);
पूर्ण

अटल व्योम gdlm_put_lock(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	पूर्णांक error;

	अगर (gl->gl_lksb.sb_lkid == 0) अणु
		gfs2_glock_मुक्त(gl);
		वापस;
	पूर्ण

	clear_bit(GLF_BLOCKING, &gl->gl_flags);
	gfs2_glstats_inc(gl, GFS2_LKS_DCOUNT);
	gfs2_sbstats_inc(gl, GFS2_LKS_DCOUNT);
	gfs2_update_request_बार(gl);

	/* करोn't want to skip dlm_unlock writing the lvb when lock has one */

	अगर (test_bit(SDF_SKIP_DLM_UNLOCK, &sdp->sd_flags) &&
	    !gl->gl_lksb.sb_lvbptr) अणु
		gfs2_glock_मुक्त(gl);
		वापस;
	पूर्ण

	error = dlm_unlock(ls->ls_dlm, gl->gl_lksb.sb_lkid, DLM_LKF_VALBLK,
			   शून्य, gl);
	अगर (error) अणु
		fs_err(sdp, "gdlm_unlock %x,%llx err=%d\n",
		       gl->gl_name.ln_type,
		       (अचिन्हित दीर्घ दीर्घ)gl->gl_name.ln_number, error);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम gdlm_cancel(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &gl->gl_name.ln_sbd->sd_lockकाष्ठा;
	dlm_unlock(ls->ls_dlm, gl->gl_lksb.sb_lkid, DLM_LKF_CANCEL, शून्य, gl);
पूर्ण

/*
 * dlm/gfs2 recovery coordination using dlm_recover callbacks
 *
 *  0. gfs2 checks क्रम another cluster node withdraw, needing journal replay
 *  1. dlm_controld sees lockspace members change
 *  2. dlm_controld blocks dlm-kernel locking activity
 *  3. dlm_controld within dlm-kernel notअगरies gfs2 (recover_prep)
 *  4. dlm_controld starts and finishes its own user level recovery
 *  5. dlm_controld starts dlm-kernel dlm_recoverd to करो kernel recovery
 *  6. dlm_recoverd notअगरies gfs2 of failed nodes (recover_slot)
 *  7. dlm_recoverd करोes its own lock recovery
 *  8. dlm_recoverd unblocks dlm-kernel locking activity
 *  9. dlm_recoverd notअगरies gfs2 when करोne (recover_करोne with new generation)
 * 10. gfs2_control updates control_lock lvb with new generation and jid bits
 * 11. gfs2_control enqueues journals क्रम gfs2_recover to recover (maybe none)
 * 12. gfs2_recover dequeues and recovers journals of failed nodes
 * 13. gfs2_recover provides recovery results to gfs2_control (recovery_result)
 * 14. gfs2_control updates control_lock lvb jid bits क्रम recovered journals
 * 15. gfs2_control unblocks normal locking when all journals are recovered
 *
 * - failures during recovery
 *
 * recover_prep() may set BLOCK_LOCKS (step 3) again beक्रमe gfs2_control
 * clears BLOCK_LOCKS (step 15), e.g. another node fails जबतक still
 * recovering क्रम a prior failure.  gfs2_control needs a way to detect
 * this so it can leave BLOCK_LOCKS set in step 15.  This is managed using
 * the recover_block and recover_start values.
 *
 * recover_करोne() provides a new lockspace generation number each समय it
 * is called (step 9).  This generation number is saved as recover_start.
 * When recover_prep() is called, it sets BLOCK_LOCKS and sets
 * recover_block = recover_start.  So, जबतक recover_block is equal to
 * recover_start, BLOCK_LOCKS should reमुख्य set.  (recover_spin must
 * be held around the BLOCK_LOCKS/recover_block/recover_start logic.)
 *
 * - more specअगरic gfs2 steps in sequence above
 *
 *  3. recover_prep sets BLOCK_LOCKS and sets recover_block = recover_start
 *  6. recover_slot records any failed jids (maybe none)
 *  9. recover_करोne sets recover_start = new generation number
 * 10. gfs2_control sets control_lock lvb = new gen + bits क्रम failed jids
 * 12. gfs2_recover करोes journal recoveries क्रम failed jids identअगरied above
 * 14. gfs2_control clears control_lock lvb bits क्रम recovered jids
 * 15. gfs2_control checks अगर recover_block == recover_start (step 3 occured
 *     again) then करो nothing, otherwise अगर recover_start > recover_block
 *     then clear BLOCK_LOCKS.
 *
 * - parallel recovery steps across all nodes
 *
 * All nodes attempt to update the control_lock lvb with the new generation
 * number and jid bits, but only the first to get the control_lock EX will
 * करो so; others will see that it's alपढ़ोy करोne (lvb alपढ़ोy contains new
 * generation number.)
 *
 * . All nodes get the same recover_prep/recover_slot/recover_करोne callbacks
 * . All nodes attempt to set control_lock lvb gen + bits क्रम the new gen
 * . One node माला_लो control_lock first and ग_लिखोs the lvb, others see it's करोne
 * . All nodes attempt to recover jids क्रम which they see control_lock bits set
 * . One node succeeds क्रम a jid, and that one clears the jid bit in the lvb
 * . All nodes will eventually see all lvb bits clear and unblock locks
 *
 * - is there a problem with clearing an lvb bit that should be set
 *   and missing a journal recovery?
 *
 * 1. jid fails
 * 2. lvb bit set क्रम step 1
 * 3. jid recovered क्रम step 1
 * 4. jid taken again (new mount)
 * 5. jid fails (क्रम step 4)
 * 6. lvb bit set क्रम step 5 (will alपढ़ोy be set)
 * 7. lvb bit cleared क्रम step 3
 *
 * This is not a problem because the failure in step 5 करोes not
 * require recovery, because the mount in step 4 could not have
 * progressed far enough to unblock locks and access the fs.  The
 * control_mount() function रुकोs क्रम all recoveries to be complete
 * क्रम the latest lockspace generation beक्रमe ever unblocking locks
 * and वापसing.  The mount in step 4 रुकोs until the recovery in
 * step 1 is करोne.
 *
 * - special हाल of first mounter: first node to mount the fs
 *
 * The first node to mount a gfs2 fs needs to check all the journals
 * and recover any that need recovery beक्रमe other nodes are allowed
 * to mount the fs.  (Others may begin mounting, but they must रुको
 * क्रम the first mounter to be करोne beक्रमe taking locks on the fs
 * or accessing the fs.)  This has two parts:
 *
 * 1. The mounted_lock tells a node it's the first to mount the fs.
 * Each node holds the mounted_lock in PR जबतक it's mounted.
 * Each node tries to acquire the mounted_lock in EX when it mounts.
 * If a node is granted the mounted_lock EX it means there are no
 * other mounted nodes (no PR locks exist), and it is the first mounter.
 * The mounted_lock is demoted to PR when first recovery is करोne, so
 * others will fail to get an EX lock, but will get a PR lock.
 *
 * 2. The control_lock blocks others in control_mount() जबतक the first
 * mounter is करोing first mount recovery of all journals.
 * A mounting node needs to acquire control_lock in EX mode beक्रमe
 * it can proceed.  The first mounter holds control_lock in EX जबतक करोing
 * the first mount recovery, blocking mounts from other nodes, then demotes
 * control_lock to NL when it's करोne (others_may_mount/first_करोne),
 * allowing other nodes to जारी mounting.
 *
 * first mounter:
 * control_lock EX/NOQUEUE success
 * mounted_lock EX/NOQUEUE success (no other PR, so no other mounters)
 * set first=1
 * करो first mounter recovery
 * mounted_lock EX->PR
 * control_lock EX->NL, ग_लिखो lvb generation
 *
 * other mounter:
 * control_lock EX/NOQUEUE success (अगर fail -EAGAIN, retry)
 * mounted_lock EX/NOQUEUE fail -EAGAIN (expected due to other mounters PR)
 * mounted_lock PR/NOQUEUE success
 * पढ़ो lvb generation
 * control_lock EX->NL
 * set first=0
 *
 * - mount during recovery
 *
 * If a node mounts जबतक others are करोing recovery (not first mounter),
 * the mounting node will get its initial recover_करोne() callback without
 * having seen any previous failures/callbacks.
 *
 * It must रुको क्रम all recoveries preceding its mount to be finished
 * beक्रमe it unblocks locks.  It करोes this by repeating the "other mounter"
 * steps above until the lvb generation number is >= its mount generation
 * number (from initial recover_करोne) and all lvb bits are clear.
 *
 * - control_lock lvb क्रमmat
 *
 * 4 bytes generation number: the latest dlm lockspace generation number
 * from recover_करोne callback.  Indicates the jid biपंचांगap has been updated
 * to reflect all slot failures through that generation.
 * 4 bytes unused.
 * GDLM_LVB_SIZE-8 bytes of jid bit map. If bit N is set, it indicates
 * that jid N needs recovery.
 */

#घोषणा JID_BITMAP_OFFSET 8 /* 4 byte generation number + 4 byte unused */

अटल व्योम control_lvb_पढ़ो(काष्ठा lm_lockकाष्ठा *ls, uपूर्णांक32_t *lvb_gen,
			     अक्षर *lvb_bits)
अणु
	__le32 gen;
	स_नकल(lvb_bits, ls->ls_control_lvb, GDLM_LVB_SIZE);
	स_नकल(&gen, lvb_bits, माप(__le32));
	*lvb_gen = le32_to_cpu(gen);
पूर्ण

अटल व्योम control_lvb_ग_लिखो(काष्ठा lm_lockकाष्ठा *ls, uपूर्णांक32_t lvb_gen,
			      अक्षर *lvb_bits)
अणु
	__le32 gen;
	स_नकल(ls->ls_control_lvb, lvb_bits, GDLM_LVB_SIZE);
	gen = cpu_to_le32(lvb_gen);
	स_नकल(ls->ls_control_lvb, &gen, माप(__le32));
पूर्ण

अटल पूर्णांक all_jid_bits_clear(अक्षर *lvb)
अणु
	वापस !स_प्रथम_inv(lvb + JID_BITMAP_OFFSET, 0,
			GDLM_LVB_SIZE - JID_BITMAP_OFFSET);
पूर्ण

अटल व्योम sync_रुको_cb(व्योम *arg)
अणु
	काष्ठा lm_lockकाष्ठा *ls = arg;
	complete(&ls->ls_sync_रुको);
पूर्ण

अटल पूर्णांक sync_unlock(काष्ठा gfs2_sbd *sdp, काष्ठा dlm_lksb *lksb, अक्षर *name)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	पूर्णांक error;

	error = dlm_unlock(ls->ls_dlm, lksb->sb_lkid, 0, lksb, ls);
	अगर (error) अणु
		fs_err(sdp, "%s lkid %x error %d\n",
		       name, lksb->sb_lkid, error);
		वापस error;
	पूर्ण

	रुको_क्रम_completion(&ls->ls_sync_रुको);

	अगर (lksb->sb_status != -DLM_EUNLOCK) अणु
		fs_err(sdp, "%s lkid %x status %d\n",
		       name, lksb->sb_lkid, lksb->sb_status);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sync_lock(काष्ठा gfs2_sbd *sdp, पूर्णांक mode, uपूर्णांक32_t flags,
		     अचिन्हित पूर्णांक num, काष्ठा dlm_lksb *lksb, अक्षर *name)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	अक्षर strname[GDLM_STRNAME_BYTES];
	पूर्णांक error, status;

	स_रखो(strname, 0, GDLM_STRNAME_BYTES);
	snम_लिखो(strname, GDLM_STRNAME_BYTES, "%8x%16x", LM_TYPE_NONDISK, num);

	error = dlm_lock(ls->ls_dlm, mode, lksb, flags,
			 strname, GDLM_STRNAME_BYTES - 1,
			 0, sync_रुको_cb, ls, शून्य);
	अगर (error) अणु
		fs_err(sdp, "%s lkid %x flags %x mode %d error %d\n",
		       name, lksb->sb_lkid, flags, mode, error);
		वापस error;
	पूर्ण

	रुको_क्रम_completion(&ls->ls_sync_रुको);

	status = lksb->sb_status;

	अगर (status && status != -EAGAIN) अणु
		fs_err(sdp, "%s lkid %x flags %x mode %d status %d\n",
		       name, lksb->sb_lkid, flags, mode, status);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक mounted_unlock(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	वापस sync_unlock(sdp, &ls->ls_mounted_lksb, "mounted_lock");
पूर्ण

अटल पूर्णांक mounted_lock(काष्ठा gfs2_sbd *sdp, पूर्णांक mode, uपूर्णांक32_t flags)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	वापस sync_lock(sdp, mode, flags, GFS2_MOUNTED_LOCK,
			 &ls->ls_mounted_lksb, "mounted_lock");
पूर्ण

अटल पूर्णांक control_unlock(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	वापस sync_unlock(sdp, &ls->ls_control_lksb, "control_lock");
पूर्ण

अटल पूर्णांक control_lock(काष्ठा gfs2_sbd *sdp, पूर्णांक mode, uपूर्णांक32_t flags)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	वापस sync_lock(sdp, mode, flags, GFS2_CONTROL_LOCK,
			 &ls->ls_control_lksb, "control_lock");
पूर्ण

/**
 * remote_withdraw - react to a node withdrawing from the file प्रणाली
 * @sdp: The superblock
 */
अटल व्योम remote_withdraw(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_jdesc *jd;
	पूर्णांक ret = 0, count = 0;

	list_क्रम_each_entry(jd, &sdp->sd_jindex_list, jd_list) अणु
		अगर (jd->jd_jid == sdp->sd_lockकाष्ठा.ls_jid)
			जारी;
		ret = gfs2_recover_journal(jd, true);
		अगर (ret)
			अवरोध;
		count++;
	पूर्ण

	/* Now drop the additional reference we acquired */
	fs_err(sdp, "Journals checked: %d, ret = %d.\n", count, ret);
पूर्ण

अटल व्योम gfs2_control_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gfs2_sbd *sdp = container_of(work, काष्ठा gfs2_sbd, sd_control_work.work);
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	uपूर्णांक32_t block_gen, start_gen, lvb_gen, flags;
	पूर्णांक recover_set = 0;
	पूर्णांक ग_लिखो_lvb = 0;
	पूर्णांक recover_size;
	पूर्णांक i, error;

	/* First check क्रम other nodes that may have करोne a withdraw. */
	अगर (test_bit(SDF_REMOTE_WITHDRAW, &sdp->sd_flags)) अणु
		remote_withdraw(sdp);
		clear_bit(SDF_REMOTE_WITHDRAW, &sdp->sd_flags);
		वापस;
	पूर्ण

	spin_lock(&ls->ls_recover_spin);
	/*
	 * No MOUNT_DONE means we're still mounting; control_mount()
	 * will set this flag, after which this thपढ़ो will take over
	 * all further clearing of BLOCK_LOCKS.
	 *
	 * FIRST_MOUNT means this node is करोing first mounter recovery,
	 * क्रम which recovery control is handled by
	 * control_mount()/control_first_करोne(), not this thपढ़ो.
	 */
	अगर (!test_bit(DFL_MOUNT_DONE, &ls->ls_recover_flags) ||
	     test_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags)) अणु
		spin_unlock(&ls->ls_recover_spin);
		वापस;
	पूर्ण
	block_gen = ls->ls_recover_block;
	start_gen = ls->ls_recover_start;
	spin_unlock(&ls->ls_recover_spin);

	/*
	 * Equal block_gen and start_gen implies we are between
	 * recover_prep and recover_करोne callbacks, which means
	 * dlm recovery is in progress and dlm locking is blocked.
	 * There's no poपूर्णांक trying to करो any work until recover_करोne.
	 */

	अगर (block_gen == start_gen)
		वापस;

	/*
	 * Propagate recover_submit[] and recover_result[] to lvb:
	 * dlm_recoverd adds to recover_submit[] jids needing recovery
	 * gfs2_recover adds to recover_result[] journal recovery results
	 *
	 * set lvb bit क्रम jids in recover_submit[] अगर the lvb has not
	 * yet been updated क्रम the generation of the failure
	 *
	 * clear lvb bit क्रम jids in recover_result[] अगर the result of
	 * the journal recovery is SUCCESS
	 */

	error = control_lock(sdp, DLM_LOCK_EX, DLM_LKF_CONVERT|DLM_LKF_VALBLK);
	अगर (error) अणु
		fs_err(sdp, "control lock EX error %d\n", error);
		वापस;
	पूर्ण

	control_lvb_पढ़ो(ls, &lvb_gen, ls->ls_lvb_bits);

	spin_lock(&ls->ls_recover_spin);
	अगर (block_gen != ls->ls_recover_block ||
	    start_gen != ls->ls_recover_start) अणु
		fs_info(sdp, "recover generation %u block1 %u %u\n",
			start_gen, block_gen, ls->ls_recover_block);
		spin_unlock(&ls->ls_recover_spin);
		control_lock(sdp, DLM_LOCK_NL, DLM_LKF_CONVERT);
		वापस;
	पूर्ण

	recover_size = ls->ls_recover_size;

	अगर (lvb_gen <= start_gen) अणु
		/*
		 * Clear lvb bits क्रम jids we've successfully recovered.
		 * Because all nodes attempt to recover failed journals,
		 * a journal can be recovered multiple बार successfully
		 * in succession.  Only the first will really करो recovery,
		 * the others find it clean, but still report a successful
		 * recovery.  So, another node may have alपढ़ोy recovered
		 * the jid and cleared the lvb bit क्रम it.
		 */
		क्रम (i = 0; i < recover_size; i++) अणु
			अगर (ls->ls_recover_result[i] != LM_RD_SUCCESS)
				जारी;

			ls->ls_recover_result[i] = 0;

			अगर (!test_bit_le(i, ls->ls_lvb_bits + JID_BITMAP_OFFSET))
				जारी;

			__clear_bit_le(i, ls->ls_lvb_bits + JID_BITMAP_OFFSET);
			ग_लिखो_lvb = 1;
		पूर्ण
	पूर्ण

	अगर (lvb_gen == start_gen) अणु
		/*
		 * Failed slots beक्रमe start_gen are alपढ़ोy set in lvb.
		 */
		क्रम (i = 0; i < recover_size; i++) अणु
			अगर (!ls->ls_recover_submit[i])
				जारी;
			अगर (ls->ls_recover_submit[i] < lvb_gen)
				ls->ls_recover_submit[i] = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (lvb_gen < start_gen) अणु
		/*
		 * Failed slots beक्रमe start_gen are not yet set in lvb.
		 */
		क्रम (i = 0; i < recover_size; i++) अणु
			अगर (!ls->ls_recover_submit[i])
				जारी;
			अगर (ls->ls_recover_submit[i] < start_gen) अणु
				ls->ls_recover_submit[i] = 0;
				__set_bit_le(i, ls->ls_lvb_bits + JID_BITMAP_OFFSET);
			पूर्ण
		पूर्ण
		/* even अगर there are no bits to set, we need to ग_लिखो the
		   latest generation to the lvb */
		ग_लिखो_lvb = 1;
	पूर्ण अन्यथा अणु
		/*
		 * we should be getting a recover_करोne() क्रम lvb_gen soon
		 */
	पूर्ण
	spin_unlock(&ls->ls_recover_spin);

	अगर (ग_लिखो_lvb) अणु
		control_lvb_ग_लिखो(ls, start_gen, ls->ls_lvb_bits);
		flags = DLM_LKF_CONVERT | DLM_LKF_VALBLK;
	पूर्ण अन्यथा अणु
		flags = DLM_LKF_CONVERT;
	पूर्ण

	error = control_lock(sdp, DLM_LOCK_NL, flags);
	अगर (error) अणु
		fs_err(sdp, "control lock NL error %d\n", error);
		वापस;
	पूर्ण

	/*
	 * Everyone will see jid bits set in the lvb, run gfs2_recover_set(),
	 * and clear a jid bit in the lvb अगर the recovery is a success.
	 * Eventually all journals will be recovered, all jid bits will
	 * be cleared in the lvb, and everyone will clear BLOCK_LOCKS.
	 */

	क्रम (i = 0; i < recover_size; i++) अणु
		अगर (test_bit_le(i, ls->ls_lvb_bits + JID_BITMAP_OFFSET)) अणु
			fs_info(sdp, "recover generation %u jid %d\n",
				start_gen, i);
			gfs2_recover_set(sdp, i);
			recover_set++;
		पूर्ण
	पूर्ण
	अगर (recover_set)
		वापस;

	/*
	 * No more jid bits set in lvb, all recovery is करोne, unblock locks
	 * (unless a new recover_prep callback has occured blocking locks
	 * again जबतक working above)
	 */

	spin_lock(&ls->ls_recover_spin);
	अगर (ls->ls_recover_block == block_gen &&
	    ls->ls_recover_start == start_gen) अणु
		clear_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags);
		spin_unlock(&ls->ls_recover_spin);
		fs_info(sdp, "recover generation %u done\n", start_gen);
		gfs2_glock_thaw(sdp);
	पूर्ण अन्यथा अणु
		fs_info(sdp, "recover generation %u block2 %u %u\n",
			start_gen, block_gen, ls->ls_recover_block);
		spin_unlock(&ls->ls_recover_spin);
	पूर्ण
पूर्ण

अटल पूर्णांक control_mount(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	uपूर्णांक32_t start_gen, block_gen, mount_gen, lvb_gen;
	पूर्णांक mounted_mode;
	पूर्णांक retries = 0;
	पूर्णांक error;

	स_रखो(&ls->ls_mounted_lksb, 0, माप(काष्ठा dlm_lksb));
	स_रखो(&ls->ls_control_lksb, 0, माप(काष्ठा dlm_lksb));
	स_रखो(&ls->ls_control_lvb, 0, GDLM_LVB_SIZE);
	ls->ls_control_lksb.sb_lvbptr = ls->ls_control_lvb;
	init_completion(&ls->ls_sync_रुको);

	set_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags);

	error = control_lock(sdp, DLM_LOCK_NL, DLM_LKF_VALBLK);
	अगर (error) अणु
		fs_err(sdp, "control_mount control_lock NL error %d\n", error);
		वापस error;
	पूर्ण

	error = mounted_lock(sdp, DLM_LOCK_NL, 0);
	अगर (error) अणु
		fs_err(sdp, "control_mount mounted_lock NL error %d\n", error);
		control_unlock(sdp);
		वापस error;
	पूर्ण
	mounted_mode = DLM_LOCK_NL;

restart:
	अगर (retries++ && संकेत_pending(current)) अणु
		error = -EINTR;
		जाओ fail;
	पूर्ण

	/*
	 * We always start with both locks in NL. control_lock is
	 * demoted to NL below so we करोn't need to करो it here.
	 */

	अगर (mounted_mode != DLM_LOCK_NL) अणु
		error = mounted_lock(sdp, DLM_LOCK_NL, DLM_LKF_CONVERT);
		अगर (error)
			जाओ fail;
		mounted_mode = DLM_LOCK_NL;
	पूर्ण

	/*
	 * Other nodes need to करो some work in dlm recovery and gfs2_control
	 * beक्रमe the recover_करोne and control_lock will be पढ़ोy क्रम us below.
	 * A delay here is not required but often aव्योमs having to retry.
	 */

	msleep_पूर्णांकerruptible(500);

	/*
	 * Acquire control_lock in EX and mounted_lock in either EX or PR.
	 * control_lock lvb keeps track of any pending journal recoveries.
	 * mounted_lock indicates अगर any other nodes have the fs mounted.
	 */

	error = control_lock(sdp, DLM_LOCK_EX, DLM_LKF_CONVERT|DLM_LKF_NOQUEUE|DLM_LKF_VALBLK);
	अगर (error == -EAGAIN) अणु
		जाओ restart;
	पूर्ण अन्यथा अगर (error) अणु
		fs_err(sdp, "control_mount control_lock EX error %d\n", error);
		जाओ fail;
	पूर्ण

	/**
	 * If we're a spectator, we don't want to take the lock in EX because
	 * we cannot करो the first-mount responsibility it implies: recovery.
	 */
	अगर (sdp->sd_args.ar_spectator)
		जाओ locks_करोne;

	error = mounted_lock(sdp, DLM_LOCK_EX, DLM_LKF_CONVERT|DLM_LKF_NOQUEUE);
	अगर (!error) अणु
		mounted_mode = DLM_LOCK_EX;
		जाओ locks_करोne;
	पूर्ण अन्यथा अगर (error != -EAGAIN) अणु
		fs_err(sdp, "control_mount mounted_lock EX error %d\n", error);
		जाओ fail;
	पूर्ण

	error = mounted_lock(sdp, DLM_LOCK_PR, DLM_LKF_CONVERT|DLM_LKF_NOQUEUE);
	अगर (!error) अणु
		mounted_mode = DLM_LOCK_PR;
		जाओ locks_करोne;
	पूर्ण अन्यथा अणु
		/* not even -EAGAIN should happen here */
		fs_err(sdp, "control_mount mounted_lock PR error %d\n", error);
		जाओ fail;
	पूर्ण

locks_करोne:
	/*
	 * If we got both locks above in EX, then we're the first mounter.
	 * If not, then we need to रुको क्रम the control_lock lvb to be
	 * updated by other mounted nodes to reflect our mount generation.
	 *
	 * In simple first mounter हालs, first mounter will see zero lvb_gen,
	 * but in हालs where all existing nodes leave/fail beक्रमe mounting
	 * nodes finish control_mount, then all nodes will be mounting and
	 * lvb_gen will be non-zero.
	 */

	control_lvb_पढ़ो(ls, &lvb_gen, ls->ls_lvb_bits);

	अगर (lvb_gen == 0xFFFFFFFF) अणु
		/* special value to क्रमce mount attempts to fail */
		fs_err(sdp, "control_mount control_lock disabled\n");
		error = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (mounted_mode == DLM_LOCK_EX) अणु
		/* first mounter, keep both EX जबतक करोing first recovery */
		spin_lock(&ls->ls_recover_spin);
		clear_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags);
		set_bit(DFL_MOUNT_DONE, &ls->ls_recover_flags);
		set_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags);
		spin_unlock(&ls->ls_recover_spin);
		fs_info(sdp, "first mounter control generation %u\n", lvb_gen);
		वापस 0;
	पूर्ण

	error = control_lock(sdp, DLM_LOCK_NL, DLM_LKF_CONVERT);
	अगर (error)
		जाओ fail;

	/*
	 * We are not first mounter, now we need to रुको क्रम the control_lock
	 * lvb generation to be >= the generation from our first recover_करोne
	 * and all lvb bits to be clear (no pending journal recoveries.)
	 */

	अगर (!all_jid_bits_clear(ls->ls_lvb_bits)) अणु
		/* journals need recovery, रुको until all are clear */
		fs_info(sdp, "control_mount wait for journal recovery\n");
		जाओ restart;
	पूर्ण

	spin_lock(&ls->ls_recover_spin);
	block_gen = ls->ls_recover_block;
	start_gen = ls->ls_recover_start;
	mount_gen = ls->ls_recover_mount;

	अगर (lvb_gen < mount_gen) अणु
		/* रुको क्रम mounted nodes to update control_lock lvb to our
		   generation, which might include new recovery bits set */
		अगर (sdp->sd_args.ar_spectator) अणु
			fs_info(sdp, "Recovery is required. Waiting for a "
				"non-spectator to mount.\n");
			msleep_पूर्णांकerruptible(1000);
		पूर्ण अन्यथा अणु
			fs_info(sdp, "control_mount wait1 block %u start %u "
				"mount %u lvb %u flags %lx\n", block_gen,
				start_gen, mount_gen, lvb_gen,
				ls->ls_recover_flags);
		पूर्ण
		spin_unlock(&ls->ls_recover_spin);
		जाओ restart;
	पूर्ण

	अगर (lvb_gen != start_gen) अणु
		/* रुको क्रम mounted nodes to update control_lock lvb to the
		   latest recovery generation */
		fs_info(sdp, "control_mount wait2 block %u start %u mount %u "
			"lvb %u flags %lx\n", block_gen, start_gen, mount_gen,
			lvb_gen, ls->ls_recover_flags);
		spin_unlock(&ls->ls_recover_spin);
		जाओ restart;
	पूर्ण

	अगर (block_gen == start_gen) अणु
		/* dlm recovery in progress, रुको क्रम it to finish */
		fs_info(sdp, "control_mount wait3 block %u start %u mount %u "
			"lvb %u flags %lx\n", block_gen, start_gen, mount_gen,
			lvb_gen, ls->ls_recover_flags);
		spin_unlock(&ls->ls_recover_spin);
		जाओ restart;
	पूर्ण

	clear_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags);
	set_bit(DFL_MOUNT_DONE, &ls->ls_recover_flags);
	स_रखो(ls->ls_recover_submit, 0, ls->ls_recover_size*माप(uपूर्णांक32_t));
	स_रखो(ls->ls_recover_result, 0, ls->ls_recover_size*माप(uपूर्णांक32_t));
	spin_unlock(&ls->ls_recover_spin);
	वापस 0;

fail:
	mounted_unlock(sdp);
	control_unlock(sdp);
	वापस error;
पूर्ण

अटल पूर्णांक control_first_करोne(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	uपूर्णांक32_t start_gen, block_gen;
	पूर्णांक error;

restart:
	spin_lock(&ls->ls_recover_spin);
	start_gen = ls->ls_recover_start;
	block_gen = ls->ls_recover_block;

	अगर (test_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags) ||
	    !test_bit(DFL_MOUNT_DONE, &ls->ls_recover_flags) ||
	    !test_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags)) अणु
		/* sanity check, should not happen */
		fs_err(sdp, "control_first_done start %u block %u flags %lx\n",
		       start_gen, block_gen, ls->ls_recover_flags);
		spin_unlock(&ls->ls_recover_spin);
		control_unlock(sdp);
		वापस -1;
	पूर्ण

	अगर (start_gen == block_gen) अणु
		/*
		 * Wait क्रम the end of a dlm recovery cycle to चयन from
		 * first mounter recovery.  We can ignore any recover_slot
		 * callbacks between the recover_prep and next recover_करोne
		 * because we are still the first mounter and any failed nodes
		 * have not fully mounted, so they करोn't need recovery.
		 */
		spin_unlock(&ls->ls_recover_spin);
		fs_info(sdp, "control_first_done wait gen %u\n", start_gen);

		रुको_on_bit(&ls->ls_recover_flags, DFL_DLM_RECOVERY,
			    TASK_UNINTERRUPTIBLE);
		जाओ restart;
	पूर्ण

	clear_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags);
	set_bit(DFL_FIRST_MOUNT_DONE, &ls->ls_recover_flags);
	स_रखो(ls->ls_recover_submit, 0, ls->ls_recover_size*माप(uपूर्णांक32_t));
	स_रखो(ls->ls_recover_result, 0, ls->ls_recover_size*माप(uपूर्णांक32_t));
	spin_unlock(&ls->ls_recover_spin);

	स_रखो(ls->ls_lvb_bits, 0, GDLM_LVB_SIZE);
	control_lvb_ग_लिखो(ls, start_gen, ls->ls_lvb_bits);

	error = mounted_lock(sdp, DLM_LOCK_PR, DLM_LKF_CONVERT);
	अगर (error)
		fs_err(sdp, "control_first_done mounted PR error %d\n", error);

	error = control_lock(sdp, DLM_LOCK_NL, DLM_LKF_CONVERT|DLM_LKF_VALBLK);
	अगर (error)
		fs_err(sdp, "control_first_done control NL error %d\n", error);

	वापस error;
पूर्ण

/*
 * Expand अटल jid arrays अगर necessary (by increments of RECOVER_SIZE_INC)
 * to accomodate the largest slot number.  (NB dlm slot numbers start at 1,
 * gfs2 jids start at 0, so jid = slot - 1)
 */

#घोषणा RECOVER_SIZE_INC 16

अटल पूर्णांक set_recover_size(काष्ठा gfs2_sbd *sdp, काष्ठा dlm_slot *slots,
			    पूर्णांक num_slots)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	uपूर्णांक32_t *submit = शून्य;
	uपूर्णांक32_t *result = शून्य;
	uपूर्णांक32_t old_size, new_size;
	पूर्णांक i, max_jid;

	अगर (!ls->ls_lvb_bits) अणु
		ls->ls_lvb_bits = kzalloc(GDLM_LVB_SIZE, GFP_NOFS);
		अगर (!ls->ls_lvb_bits)
			वापस -ENOMEM;
	पूर्ण

	max_jid = 0;
	क्रम (i = 0; i < num_slots; i++) अणु
		अगर (max_jid < slots[i].slot - 1)
			max_jid = slots[i].slot - 1;
	पूर्ण

	old_size = ls->ls_recover_size;
	new_size = old_size;
	जबतक (new_size < max_jid + 1)
		new_size += RECOVER_SIZE_INC;
	अगर (new_size == old_size)
		वापस 0;

	submit = kसुस्मृति(new_size, माप(uपूर्णांक32_t), GFP_NOFS);
	result = kसुस्मृति(new_size, माप(uपूर्णांक32_t), GFP_NOFS);
	अगर (!submit || !result) अणु
		kमुक्त(submit);
		kमुक्त(result);
		वापस -ENOMEM;
	पूर्ण

	spin_lock(&ls->ls_recover_spin);
	स_नकल(submit, ls->ls_recover_submit, old_size * माप(uपूर्णांक32_t));
	स_नकल(result, ls->ls_recover_result, old_size * माप(uपूर्णांक32_t));
	kमुक्त(ls->ls_recover_submit);
	kमुक्त(ls->ls_recover_result);
	ls->ls_recover_submit = submit;
	ls->ls_recover_result = result;
	ls->ls_recover_size = new_size;
	spin_unlock(&ls->ls_recover_spin);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_recover_size(काष्ठा lm_lockकाष्ठा *ls)
अणु
	kमुक्त(ls->ls_lvb_bits);
	kमुक्त(ls->ls_recover_submit);
	kमुक्त(ls->ls_recover_result);
	ls->ls_recover_submit = शून्य;
	ls->ls_recover_result = शून्य;
	ls->ls_recover_size = 0;
	ls->ls_lvb_bits = शून्य;
पूर्ण

/* dlm calls beक्रमe it करोes lock recovery */

अटल व्योम gdlm_recover_prep(व्योम *arg)
अणु
	काष्ठा gfs2_sbd *sdp = arg;
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;

	अगर (gfs2_withdrawn(sdp)) अणु
		fs_err(sdp, "recover_prep ignored due to withdraw.\n");
		वापस;
	पूर्ण
	spin_lock(&ls->ls_recover_spin);
	ls->ls_recover_block = ls->ls_recover_start;
	set_bit(DFL_DLM_RECOVERY, &ls->ls_recover_flags);

	अगर (!test_bit(DFL_MOUNT_DONE, &ls->ls_recover_flags) ||
	     test_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags)) अणु
		spin_unlock(&ls->ls_recover_spin);
		वापस;
	पूर्ण
	set_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags);
	spin_unlock(&ls->ls_recover_spin);
पूर्ण

/* dlm calls after recover_prep has been completed on all lockspace members;
   identअगरies slot/jid of failed member */

अटल व्योम gdlm_recover_slot(व्योम *arg, काष्ठा dlm_slot *slot)
अणु
	काष्ठा gfs2_sbd *sdp = arg;
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	पूर्णांक jid = slot->slot - 1;

	अगर (gfs2_withdrawn(sdp)) अणु
		fs_err(sdp, "recover_slot jid %d ignored due to withdraw.\n",
		       jid);
		वापस;
	पूर्ण
	spin_lock(&ls->ls_recover_spin);
	अगर (ls->ls_recover_size < jid + 1) अणु
		fs_err(sdp, "recover_slot jid %d gen %u short size %d\n",
		       jid, ls->ls_recover_block, ls->ls_recover_size);
		spin_unlock(&ls->ls_recover_spin);
		वापस;
	पूर्ण

	अगर (ls->ls_recover_submit[jid]) अणु
		fs_info(sdp, "recover_slot jid %d gen %u prev %u\n",
			jid, ls->ls_recover_block, ls->ls_recover_submit[jid]);
	पूर्ण
	ls->ls_recover_submit[jid] = ls->ls_recover_block;
	spin_unlock(&ls->ls_recover_spin);
पूर्ण

/* dlm calls after recover_slot and after it completes lock recovery */

अटल व्योम gdlm_recover_करोne(व्योम *arg, काष्ठा dlm_slot *slots, पूर्णांक num_slots,
			      पूर्णांक our_slot, uपूर्णांक32_t generation)
अणु
	काष्ठा gfs2_sbd *sdp = arg;
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;

	अगर (gfs2_withdrawn(sdp)) अणु
		fs_err(sdp, "recover_done ignored due to withdraw.\n");
		वापस;
	पूर्ण
	/* ensure the ls jid arrays are large enough */
	set_recover_size(sdp, slots, num_slots);

	spin_lock(&ls->ls_recover_spin);
	ls->ls_recover_start = generation;

	अगर (!ls->ls_recover_mount) अणु
		ls->ls_recover_mount = generation;
		ls->ls_jid = our_slot - 1;
	पूर्ण

	अगर (!test_bit(DFL_UNMOUNT, &ls->ls_recover_flags))
		queue_delayed_work(gfs2_control_wq, &sdp->sd_control_work, 0);

	clear_bit(DFL_DLM_RECOVERY, &ls->ls_recover_flags);
	smp_mb__after_atomic();
	wake_up_bit(&ls->ls_recover_flags, DFL_DLM_RECOVERY);
	spin_unlock(&ls->ls_recover_spin);
पूर्ण

/* gfs2_recover thपढ़ो has a journal recovery result */

अटल व्योम gdlm_recovery_result(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक jid,
				 अचिन्हित पूर्णांक result)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;

	अगर (gfs2_withdrawn(sdp)) अणु
		fs_err(sdp, "recovery_result jid %d ignored due to withdraw.\n",
		       jid);
		वापस;
	पूर्ण
	अगर (test_bit(DFL_NO_DLM_OPS, &ls->ls_recover_flags))
		वापस;

	/* करोn't care about the recovery of own journal during mount */
	अगर (jid == ls->ls_jid)
		वापस;

	spin_lock(&ls->ls_recover_spin);
	अगर (test_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags)) अणु
		spin_unlock(&ls->ls_recover_spin);
		वापस;
	पूर्ण
	अगर (ls->ls_recover_size < jid + 1) अणु
		fs_err(sdp, "recovery_result jid %d short size %d\n",
		       jid, ls->ls_recover_size);
		spin_unlock(&ls->ls_recover_spin);
		वापस;
	पूर्ण

	fs_info(sdp, "recover jid %d result %s\n", jid,
		result == LM_RD_GAVEUP ? "busy" : "success");

	ls->ls_recover_result[jid] = result;

	/* GAVEUP means another node is recovering the journal; delay our
	   next attempt to recover it, to give the other node a chance to
	   finish beक्रमe trying again */

	अगर (!test_bit(DFL_UNMOUNT, &ls->ls_recover_flags))
		queue_delayed_work(gfs2_control_wq, &sdp->sd_control_work,
				   result == LM_RD_GAVEUP ? HZ : 0);
	spin_unlock(&ls->ls_recover_spin);
पूर्ण

अटल स्थिर काष्ठा dlm_lockspace_ops gdlm_lockspace_ops = अणु
	.recover_prep = gdlm_recover_prep,
	.recover_slot = gdlm_recover_slot,
	.recover_करोne = gdlm_recover_करोne,
पूर्ण;

अटल पूर्णांक gdlm_mount(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *table)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	अक्षर cluster[GFS2_LOCKNAME_LEN];
	स्थिर अक्षर *fsname;
	uपूर्णांक32_t flags;
	पूर्णांक error, ops_result;

	/*
	 * initialize everything
	 */

	INIT_DELAYED_WORK(&sdp->sd_control_work, gfs2_control_func);
	spin_lock_init(&ls->ls_recover_spin);
	ls->ls_recover_flags = 0;
	ls->ls_recover_mount = 0;
	ls->ls_recover_start = 0;
	ls->ls_recover_block = 0;
	ls->ls_recover_size = 0;
	ls->ls_recover_submit = शून्य;
	ls->ls_recover_result = शून्य;
	ls->ls_lvb_bits = शून्य;

	error = set_recover_size(sdp, शून्य, 0);
	अगर (error)
		जाओ fail;

	/*
	 * prepare dlm_new_lockspace args
	 */

	fsname = म_अक्षर(table, ':');
	अगर (!fsname) अणु
		fs_info(sdp, "no fsname found\n");
		error = -EINVAL;
		जाओ fail_मुक्त;
	पूर्ण
	स_रखो(cluster, 0, माप(cluster));
	स_नकल(cluster, table, म_माप(table) - म_माप(fsname));
	fsname++;

	flags = DLM_LSFL_FS | DLM_LSFL_NEWEXCL;

	/*
	 * create/join lockspace
	 */

	error = dlm_new_lockspace(fsname, cluster, flags, GDLM_LVB_SIZE,
				  &gdlm_lockspace_ops, sdp, &ops_result,
				  &ls->ls_dlm);
	अगर (error) अणु
		fs_err(sdp, "dlm_new_lockspace error %d\n", error);
		जाओ fail_मुक्त;
	पूर्ण

	अगर (ops_result < 0) अणु
		/*
		 * dlm करोes not support ops callbacks,
		 * old dlm_controld/gfs_controld are used, try without ops.
		 */
		fs_info(sdp, "dlm lockspace ops not used\n");
		मुक्त_recover_size(ls);
		set_bit(DFL_NO_DLM_OPS, &ls->ls_recover_flags);
		वापस 0;
	पूर्ण

	अगर (!test_bit(SDF_NOJOURNALID, &sdp->sd_flags)) अणु
		fs_err(sdp, "dlm lockspace ops disallow jid preset\n");
		error = -EINVAL;
		जाओ fail_release;
	पूर्ण

	/*
	 * control_mount() uses control_lock to determine first mounter,
	 * and क्रम later mounts, रुकोs क्रम any recoveries to be cleared.
	 */

	error = control_mount(sdp);
	अगर (error) अणु
		fs_err(sdp, "mount control error %d\n", error);
		जाओ fail_release;
	पूर्ण

	ls->ls_first = !!test_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags);
	clear_bit(SDF_NOJOURNALID, &sdp->sd_flags);
	smp_mb__after_atomic();
	wake_up_bit(&sdp->sd_flags, SDF_NOJOURNALID);
	वापस 0;

fail_release:
	dlm_release_lockspace(ls->ls_dlm, 2);
fail_मुक्त:
	मुक्त_recover_size(ls);
fail:
	वापस error;
पूर्ण

अटल व्योम gdlm_first_करोne(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	पूर्णांक error;

	अगर (test_bit(DFL_NO_DLM_OPS, &ls->ls_recover_flags))
		वापस;

	error = control_first_करोne(sdp);
	अगर (error)
		fs_err(sdp, "mount first_done error %d\n", error);
पूर्ण

अटल व्योम gdlm_unmount(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;

	अगर (test_bit(DFL_NO_DLM_OPS, &ls->ls_recover_flags))
		जाओ release;

	/* रुको क्रम gfs2_control_wq to be करोne with this mount */

	spin_lock(&ls->ls_recover_spin);
	set_bit(DFL_UNMOUNT, &ls->ls_recover_flags);
	spin_unlock(&ls->ls_recover_spin);
	flush_delayed_work(&sdp->sd_control_work);

	/* mounted_lock and control_lock will be purged in dlm recovery */
release:
	अगर (ls->ls_dlm) अणु
		dlm_release_lockspace(ls->ls_dlm, 2);
		ls->ls_dlm = शून्य;
	पूर्ण

	मुक्त_recover_size(ls);
पूर्ण

अटल स्थिर match_table_t dlm_tokens = अणु
	अणु Opt_jid, "jid=%d"पूर्ण,
	अणु Opt_id, "id=%d"पूर्ण,
	अणु Opt_first, "first=%d"पूर्ण,
	अणु Opt_nodir, "nodir=%d"पूर्ण,
	अणु Opt_err, शून्य पूर्ण,
पूर्ण;

स्थिर काष्ठा lm_lockops gfs2_dlm_ops = अणु
	.lm_proto_name = "lock_dlm",
	.lm_mount = gdlm_mount,
	.lm_first_करोne = gdlm_first_करोne,
	.lm_recovery_result = gdlm_recovery_result,
	.lm_unmount = gdlm_unmount,
	.lm_put_lock = gdlm_put_lock,
	.lm_lock = gdlm_lock,
	.lm_cancel = gdlm_cancel,
	.lm_tokens = &dlm_tokens,
पूर्ण;

