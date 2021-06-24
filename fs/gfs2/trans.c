<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/gfs2_ondisk.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "glock.h"
#समावेश "inode.h"
#समावेश "log.h"
#समावेश "lops.h"
#समावेश "meta_io.h"
#समावेश "trans.h"
#समावेश "util.h"
#समावेश "trace_gfs2.h"

अटल व्योम gfs2_prपूर्णांक_trans(काष्ठा gfs2_sbd *sdp, स्थिर काष्ठा gfs2_trans *tr)
अणु
	fs_warn(sdp, "Transaction created at: %pSR\n", (व्योम *)tr->tr_ip);
	fs_warn(sdp, "blocks=%u revokes=%u reserved=%u touched=%u\n",
		tr->tr_blocks, tr->tr_revokes, tr->tr_reserved,
		test_bit(TR_TOUCHED, &tr->tr_flags));
	fs_warn(sdp, "Buf %u/%u Databuf %u/%u Revoke %u\n",
		tr->tr_num_buf_new, tr->tr_num_buf_rm,
		tr->tr_num_databuf_new, tr->tr_num_databuf_rm,
		tr->tr_num_revoke);
पूर्ण

पूर्णांक __gfs2_trans_begin(काष्ठा gfs2_trans *tr, काष्ठा gfs2_sbd *sdp,
		       अचिन्हित पूर्णांक blocks, अचिन्हित पूर्णांक revokes,
		       अचिन्हित दीर्घ ip)
अणु
	अचिन्हित पूर्णांक extra_revokes;

	अगर (current->journal_info) अणु
		gfs2_prपूर्णांक_trans(sdp, current->journal_info);
		BUG();
	पूर्ण
	BUG_ON(blocks == 0 && revokes == 0);

	अगर (!test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags))
		वापस -EROFS;

	tr->tr_ip = ip;
	tr->tr_blocks = blocks;
	tr->tr_revokes = revokes;
	tr->tr_reserved = GFS2_LOG_FLUSH_MIN_BLOCKS;
	अगर (blocks) अणु
		/*
		 * The reserved blocks are either used क्रम data or metadata.
		 * We can have mixed data and metadata, each with its own log
		 * descriptor block; see calc_reserved().
		 */
		tr->tr_reserved += blocks + 1 + DIV_ROUND_UP(blocks - 1, databuf_limit(sdp));
	पूर्ण
	INIT_LIST_HEAD(&tr->tr_databuf);
	INIT_LIST_HEAD(&tr->tr_buf);
	INIT_LIST_HEAD(&tr->tr_list);
	INIT_LIST_HEAD(&tr->tr_ail1_list);
	INIT_LIST_HEAD(&tr->tr_ail2_list);

	अगर (gfs2_निश्चित_warn(sdp, tr->tr_reserved <= sdp->sd_jdesc->jd_blocks))
		वापस -EINVAL;

	sb_start_पूर्णांकग_लिखो(sdp->sd_vfs);

	/*
	 * Try the reservations under sd_log_flush_lock to prevent log flushes
	 * from creating inconsistencies between the number of allocated and
	 * reserved revokes.  If that fails, करो a full-block allocation outside
	 * of the lock to aव्योम stalling log flushes.  Then, allot the
	 * appropriate number of blocks to revokes, use as many revokes locally
	 * as needed, and "release" the surplus पूर्णांकo the revokes pool.
	 */

	करोwn_पढ़ो(&sdp->sd_log_flush_lock);
	अगर (gfs2_log_try_reserve(sdp, tr, &extra_revokes))
		जाओ reserved;
	up_पढ़ो(&sdp->sd_log_flush_lock);
	gfs2_log_reserve(sdp, tr, &extra_revokes);
	करोwn_पढ़ो(&sdp->sd_log_flush_lock);

reserved:
	gfs2_log_release_revokes(sdp, extra_revokes);
	अगर (unlikely(!test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags))) अणु
		gfs2_log_release_revokes(sdp, tr->tr_revokes);
		up_पढ़ो(&sdp->sd_log_flush_lock);
		gfs2_log_release(sdp, tr->tr_reserved);
		sb_end_पूर्णांकग_लिखो(sdp->sd_vfs);
		वापस -EROFS;
	पूर्ण

	current->journal_info = tr;

	वापस 0;
पूर्ण

पूर्णांक gfs2_trans_begin(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक blocks,
		     अचिन्हित पूर्णांक revokes)
अणु
	काष्ठा gfs2_trans *tr;
	पूर्णांक error;

	tr = kmem_cache_zalloc(gfs2_trans_cachep, GFP_NOFS);
	अगर (!tr)
		वापस -ENOMEM;
	error = __gfs2_trans_begin(tr, sdp, blocks, revokes, _RET_IP_);
	अगर (error)
		kmem_cache_मुक्त(gfs2_trans_cachep, tr);
	वापस error;
पूर्ण

व्योम gfs2_trans_end(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_trans *tr = current->journal_info;
	s64 nbuf;

	current->journal_info = शून्य;

	अगर (!test_bit(TR_TOUCHED, &tr->tr_flags)) अणु
		gfs2_log_release_revokes(sdp, tr->tr_revokes);
		up_पढ़ो(&sdp->sd_log_flush_lock);
		gfs2_log_release(sdp, tr->tr_reserved);
		अगर (!test_bit(TR_ONSTACK, &tr->tr_flags))
			gfs2_trans_मुक्त(sdp, tr);
		sb_end_पूर्णांकग_लिखो(sdp->sd_vfs);
		वापस;
	पूर्ण

	gfs2_log_release_revokes(sdp, tr->tr_revokes - tr->tr_num_revoke);

	nbuf = tr->tr_num_buf_new + tr->tr_num_databuf_new;
	nbuf -= tr->tr_num_buf_rm;
	nbuf -= tr->tr_num_databuf_rm;

	अगर (gfs2_निश्चित_withdraw(sdp, nbuf <= tr->tr_blocks) ||
	    gfs2_निश्चित_withdraw(sdp, tr->tr_num_revoke <= tr->tr_revokes))
		gfs2_prपूर्णांक_trans(sdp, tr);

	gfs2_log_commit(sdp, tr);
	अगर (!test_bit(TR_ONSTACK, &tr->tr_flags) &&
	    !test_bit(TR_ATTACHED, &tr->tr_flags))
		gfs2_trans_मुक्त(sdp, tr);
	up_पढ़ो(&sdp->sd_log_flush_lock);

	अगर (sdp->sd_vfs->s_flags & SB_SYNCHRONOUS)
		gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_NORMAL |
			       GFS2_LFC_TRANS_END);
	sb_end_पूर्णांकग_लिखो(sdp->sd_vfs);
पूर्ण

अटल काष्ठा gfs2_bufdata *gfs2_alloc_bufdata(काष्ठा gfs2_glock *gl,
					       काष्ठा buffer_head *bh)
अणु
	काष्ठा gfs2_bufdata *bd;

	bd = kmem_cache_zalloc(gfs2_bufdata_cachep, GFP_NOFS | __GFP_NOFAIL);
	bd->bd_bh = bh;
	bd->bd_gl = gl;
	INIT_LIST_HEAD(&bd->bd_list);
	INIT_LIST_HEAD(&bd->bd_ail_st_list);
	INIT_LIST_HEAD(&bd->bd_ail_gl_list);
	bh->b_निजी = bd;
	वापस bd;
पूर्ण

/**
 * gfs2_trans_add_data - Add a databuf to the transaction.
 * @gl: The inode glock associated with the buffer
 * @bh: The buffer to add
 *
 * This is used in journaled data mode.
 * We need to journal the data block in the same way as metadata in
 * the functions above. The dअगरference is that here we have a tag
 * which is two __be64's being the block number (as per meta data)
 * and a flag which says whether the data block needs escaping or
 * not. This means we need a new log entry क्रम each 251 or so data
 * blocks, which isn't an enormous overhead but twice as much as
 * क्रम normal metadata blocks.
 */
व्योम gfs2_trans_add_data(काष्ठा gfs2_glock *gl, काष्ठा buffer_head *bh)
अणु
	काष्ठा gfs2_trans *tr = current->journal_info;
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा gfs2_bufdata *bd;

	lock_buffer(bh);
	अगर (buffer_pinned(bh)) अणु
		set_bit(TR_TOUCHED, &tr->tr_flags);
		जाओ out;
	पूर्ण
	gfs2_log_lock(sdp);
	bd = bh->b_निजी;
	अगर (bd == शून्य) अणु
		gfs2_log_unlock(sdp);
		unlock_buffer(bh);
		अगर (bh->b_निजी == शून्य)
			bd = gfs2_alloc_bufdata(gl, bh);
		अन्यथा
			bd = bh->b_निजी;
		lock_buffer(bh);
		gfs2_log_lock(sdp);
	पूर्ण
	gfs2_निश्चित(sdp, bd->bd_gl == gl);
	set_bit(TR_TOUCHED, &tr->tr_flags);
	अगर (list_empty(&bd->bd_list)) अणु
		set_bit(GLF_LFLUSH, &bd->bd_gl->gl_flags);
		set_bit(GLF_सूचीTY, &bd->bd_gl->gl_flags);
		gfs2_pin(sdp, bd->bd_bh);
		tr->tr_num_databuf_new++;
		list_add_tail(&bd->bd_list, &tr->tr_databuf);
	पूर्ण
	gfs2_log_unlock(sdp);
out:
	unlock_buffer(bh);
पूर्ण

व्योम gfs2_trans_add_meta(काष्ठा gfs2_glock *gl, काष्ठा buffer_head *bh)
अणु

	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा gfs2_bufdata *bd;
	काष्ठा gfs2_meta_header *mh;
	काष्ठा gfs2_trans *tr = current->journal_info;
	क्रमागत gfs2_मुक्तze_state state = atomic_पढ़ो(&sdp->sd_मुक्तze_state);

	lock_buffer(bh);
	अगर (buffer_pinned(bh)) अणु
		set_bit(TR_TOUCHED, &tr->tr_flags);
		जाओ out;
	पूर्ण
	gfs2_log_lock(sdp);
	bd = bh->b_निजी;
	अगर (bd == शून्य) अणु
		gfs2_log_unlock(sdp);
		unlock_buffer(bh);
		lock_page(bh->b_page);
		अगर (bh->b_निजी == शून्य)
			bd = gfs2_alloc_bufdata(gl, bh);
		अन्यथा
			bd = bh->b_निजी;
		unlock_page(bh->b_page);
		lock_buffer(bh);
		gfs2_log_lock(sdp);
	पूर्ण
	gfs2_निश्चित(sdp, bd->bd_gl == gl);
	set_bit(TR_TOUCHED, &tr->tr_flags);
	अगर (!list_empty(&bd->bd_list))
		जाओ out_unlock;
	set_bit(GLF_LFLUSH, &bd->bd_gl->gl_flags);
	set_bit(GLF_सूचीTY, &bd->bd_gl->gl_flags);
	mh = (काष्ठा gfs2_meta_header *)bd->bd_bh->b_data;
	अगर (unlikely(mh->mh_magic != cpu_to_be32(GFS2_MAGIC))) अणु
		fs_err(sdp, "Attempting to add uninitialised block to "
		       "journal (inplace block=%lld)\n",
		       (अचिन्हित दीर्घ दीर्घ)bd->bd_bh->b_blocknr);
		BUG();
	पूर्ण
	अगर (unlikely(state == SFS_FROZEN)) अणु
		fs_info(sdp, "GFS2:adding buf while frozen\n");
		gfs2_निश्चित_withdraw(sdp, 0);
	पूर्ण
	अगर (unlikely(gfs2_withdrawn(sdp))) अणु
		fs_info(sdp, "GFS2:adding buf while withdrawn! 0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)bd->bd_bh->b_blocknr);
	पूर्ण
	gfs2_pin(sdp, bd->bd_bh);
	mh->__pad0 = cpu_to_be64(0);
	mh->mh_jid = cpu_to_be32(sdp->sd_jdesc->jd_jid);
	list_add(&bd->bd_list, &tr->tr_buf);
	tr->tr_num_buf_new++;
out_unlock:
	gfs2_log_unlock(sdp);
out:
	unlock_buffer(bh);
पूर्ण

व्योम gfs2_trans_add_revoke(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_bufdata *bd)
अणु
	काष्ठा gfs2_trans *tr = current->journal_info;

	BUG_ON(!list_empty(&bd->bd_list));
	gfs2_add_revoke(sdp, bd);
	set_bit(TR_TOUCHED, &tr->tr_flags);
	tr->tr_num_revoke++;
पूर्ण

व्योम gfs2_trans_हटाओ_revoke(काष्ठा gfs2_sbd *sdp, u64 blkno, अचिन्हित पूर्णांक len)
अणु
	काष्ठा gfs2_bufdata *bd, *पंचांगp;
	अचिन्हित पूर्णांक n = len;

	gfs2_log_lock(sdp);
	list_क्रम_each_entry_safe(bd, पंचांगp, &sdp->sd_log_revokes, bd_list) अणु
		अगर ((bd->bd_blkno >= blkno) && (bd->bd_blkno < (blkno + len))) अणु
			list_del_init(&bd->bd_list);
			gfs2_निश्चित_withdraw(sdp, sdp->sd_log_num_revoke);
			sdp->sd_log_num_revoke--;
			अगर (bd->bd_gl)
				gfs2_glock_हटाओ_revoke(bd->bd_gl);
			kmem_cache_मुक्त(gfs2_bufdata_cachep, bd);
			gfs2_log_release_revokes(sdp, 1);
			अगर (--n == 0)
				अवरोध;
		पूर्ण
	पूर्ण
	gfs2_log_unlock(sdp);
पूर्ण

व्योम gfs2_trans_मुक्त(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	अगर (tr == शून्य)
		वापस;

	gfs2_निश्चित_warn(sdp, list_empty(&tr->tr_ail1_list));
	gfs2_निश्चित_warn(sdp, list_empty(&tr->tr_ail2_list));
	gfs2_निश्चित_warn(sdp, list_empty(&tr->tr_databuf));
	gfs2_निश्चित_warn(sdp, list_empty(&tr->tr_buf));
	kmem_cache_मुक्त(gfs2_trans_cachep, tr);
पूर्ण
