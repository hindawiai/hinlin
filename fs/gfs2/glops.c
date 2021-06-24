<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/bपन.स>
#समावेश <linux/posix_acl.h>
#समावेश <linux/security.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "bmap.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "inode.h"
#समावेश "log.h"
#समावेश "meta_io.h"
#समावेश "recovery.h"
#समावेश "rgrp.h"
#समावेश "util.h"
#समावेश "trans.h"
#समावेश "dir.h"
#समावेश "lops.h"

काष्ठा workqueue_काष्ठा *gfs2_मुक्तze_wq;

बाह्य काष्ठा workqueue_काष्ठा *gfs2_control_wq;

अटल व्योम gfs2_ail_error(काष्ठा gfs2_glock *gl, स्थिर काष्ठा buffer_head *bh)
अणु
	fs_err(gl->gl_name.ln_sbd,
	       "AIL buffer %p: blocknr %llu state 0x%08lx mapping %p page "
	       "state 0x%lx\n",
	       bh, (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, bh->b_state,
	       bh->b_page->mapping, bh->b_page->flags);
	fs_err(gl->gl_name.ln_sbd, "AIL glock %u:%llu mapping %p\n",
	       gl->gl_name.ln_type, gl->gl_name.ln_number,
	       gfs2_glock2aspace(gl));
	gfs2_lm(gl->gl_name.ln_sbd, "AIL error\n");
	gfs2_withdraw(gl->gl_name.ln_sbd);
पूर्ण

/**
 * __gfs2_ail_flush - हटाओ all buffers क्रम a given lock from the AIL
 * @gl: the glock
 * @fsync: set when called from fsync (not all buffers will be clean)
 * @nr_revokes: Number of buffers to revoke
 *
 * None of the buffers should be dirty, locked, or pinned.
 */

अटल व्योम __gfs2_ail_flush(काष्ठा gfs2_glock *gl, bool fsync,
			     अचिन्हित पूर्णांक nr_revokes)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा list_head *head = &gl->gl_ail_list;
	काष्ठा gfs2_bufdata *bd, *पंचांगp;
	काष्ठा buffer_head *bh;
	स्थिर अचिन्हित दीर्घ b_state = (1UL << BH_Dirty)|(1UL << BH_Pinned)|(1UL << BH_Lock);

	gfs2_log_lock(sdp);
	spin_lock(&sdp->sd_ail_lock);
	list_क्रम_each_entry_safe_reverse(bd, पंचांगp, head, bd_ail_gl_list) अणु
		अगर (nr_revokes == 0)
			अवरोध;
		bh = bd->bd_bh;
		अगर (bh->b_state & b_state) अणु
			अगर (fsync)
				जारी;
			gfs2_ail_error(gl, bh);
		पूर्ण
		gfs2_trans_add_revoke(sdp, bd);
		nr_revokes--;
	पूर्ण
	GLOCK_BUG_ON(gl, !fsync && atomic_पढ़ो(&gl->gl_ail_count));
	spin_unlock(&sdp->sd_ail_lock);
	gfs2_log_unlock(sdp);
पूर्ण


अटल पूर्णांक gfs2_ail_empty_gl(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा gfs2_trans tr;
	अचिन्हित पूर्णांक revokes;
	पूर्णांक ret;

	revokes = atomic_पढ़ो(&gl->gl_ail_count);

	अगर (!revokes) अणु
		bool have_revokes;
		bool log_in_flight;

		/*
		 * We have nothing on the ail, but there could be revokes on
		 * the sdp revoke queue, in which हाल, we still want to flush
		 * the log and रुको क्रम it to finish.
		 *
		 * If the sdp revoke list is empty too, we might still have an
		 * io outstanding क्रम writing revokes, so we should रुको क्रम
		 * it beक्रमe वापसing.
		 *
		 * If none of these conditions are true, our revokes are all
		 * flushed and we can वापस.
		 */
		gfs2_log_lock(sdp);
		have_revokes = !list_empty(&sdp->sd_log_revokes);
		log_in_flight = atomic_पढ़ो(&sdp->sd_log_in_flight);
		gfs2_log_unlock(sdp);
		अगर (have_revokes)
			जाओ flush;
		अगर (log_in_flight)
			log_flush_रुको(sdp);
		वापस 0;
	पूर्ण

	स_रखो(&tr, 0, माप(tr));
	set_bit(TR_ONSTACK, &tr.tr_flags);
	ret = __gfs2_trans_begin(&tr, sdp, 0, revokes, _RET_IP_);
	अगर (ret)
		जाओ flush;
	__gfs2_ail_flush(gl, 0, revokes);
	gfs2_trans_end(sdp);

flush:
	gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_NORMAL |
		       GFS2_LFC_AIL_EMPTY_GL);
	वापस 0;
पूर्ण

व्योम gfs2_ail_flush(काष्ठा gfs2_glock *gl, bool fsync)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	अचिन्हित पूर्णांक revokes = atomic_पढ़ो(&gl->gl_ail_count);
	पूर्णांक ret;

	अगर (!revokes)
		वापस;

	ret = gfs2_trans_begin(sdp, 0, revokes);
	अगर (ret)
		वापस;
	__gfs2_ail_flush(gl, fsync, revokes);
	gfs2_trans_end(sdp);
	gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_NORMAL |
		       GFS2_LFC_AIL_FLUSH);
पूर्ण

/**
 * gfs2_rgrp_metasync - sync out the metadata of a resource group
 * @gl: the glock protecting the resource group
 *
 */

अटल पूर्णांक gfs2_rgrp_metasync(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा address_space *metamapping = &sdp->sd_aspace;
	काष्ठा gfs2_rgrpd *rgd = gfs2_glock2rgrp(gl);
	स्थिर अचिन्हित bsize = sdp->sd_sb.sb_bsize;
	loff_t start = (rgd->rd_addr * bsize) & PAGE_MASK;
	loff_t end = PAGE_ALIGN((rgd->rd_addr + rgd->rd_length) * bsize) - 1;
	पूर्णांक error;

	filemap_fdataग_लिखो_range(metamapping, start, end);
	error = filemap_fdataरुको_range(metamapping, start, end);
	WARN_ON_ONCE(error && !gfs2_withdrawn(sdp));
	mapping_set_error(metamapping, error);
	अगर (error)
		gfs2_io_error(sdp);
	वापस error;
पूर्ण

/**
 * rgrp_go_sync - sync out the metadata क्रम this glock
 * @gl: the glock
 *
 * Called when demoting or unlocking an EX glock.  We must flush
 * to disk all dirty buffers/pages relating to this glock, and must not
 * वापस to caller to demote/unlock the glock until I/O is complete.
 */

अटल पूर्णांक rgrp_go_sync(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा gfs2_rgrpd *rgd = gfs2_glock2rgrp(gl);
	पूर्णांक error;

	अगर (!test_and_clear_bit(GLF_सूचीTY, &gl->gl_flags))
		वापस 0;
	GLOCK_BUG_ON(gl, gl->gl_state != LM_ST_EXCLUSIVE);

	gfs2_log_flush(sdp, gl, GFS2_LOG_HEAD_FLUSH_NORMAL |
		       GFS2_LFC_RGRP_GO_SYNC);
	error = gfs2_rgrp_metasync(gl);
	अगर (!error)
		error = gfs2_ail_empty_gl(gl);
	gfs2_मुक्त_clones(rgd);
	वापस error;
पूर्ण

/**
 * rgrp_go_inval - invalidate the metadata क्रम this glock
 * @gl: the glock
 * @flags:
 *
 * We never used LM_ST_DEFERRED with resource groups, so that we
 * should always see the metadata flag set here.
 *
 */

अटल व्योम rgrp_go_inval(काष्ठा gfs2_glock *gl, पूर्णांक flags)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा address_space *mapping = &sdp->sd_aspace;
	काष्ठा gfs2_rgrpd *rgd = gfs2_glock2rgrp(gl);
	स्थिर अचिन्हित bsize = sdp->sd_sb.sb_bsize;
	loff_t start = (rgd->rd_addr * bsize) & PAGE_MASK;
	loff_t end = PAGE_ALIGN((rgd->rd_addr + rgd->rd_length) * bsize) - 1;

	gfs2_rgrp_brअन्यथा(rgd);
	WARN_ON_ONCE(!(flags & DIO_METADATA));
	truncate_inode_pages_range(mapping, start, end);
	rgd->rd_flags &= ~GFS2_RDF_UPTODATE;
पूर्ण

अटल व्योम gfs2_rgrp_go_dump(काष्ठा seq_file *seq, काष्ठा gfs2_glock *gl,
			      स्थिर अक्षर *fs_id_buf)
अणु
	काष्ठा gfs2_rgrpd *rgd = gl->gl_object;

	अगर (rgd)
		gfs2_rgrp_dump(seq, rgd, fs_id_buf);
पूर्ण

अटल काष्ठा gfs2_inode *gfs2_glock2inode(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_inode *ip;

	spin_lock(&gl->gl_lockref.lock);
	ip = gl->gl_object;
	अगर (ip)
		set_bit(GIF_GLOP_PENDING, &ip->i_flags);
	spin_unlock(&gl->gl_lockref.lock);
	वापस ip;
पूर्ण

काष्ठा gfs2_rgrpd *gfs2_glock2rgrp(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_rgrpd *rgd;

	spin_lock(&gl->gl_lockref.lock);
	rgd = gl->gl_object;
	spin_unlock(&gl->gl_lockref.lock);

	वापस rgd;
पूर्ण

अटल व्योम gfs2_clear_glop_pending(काष्ठा gfs2_inode *ip)
अणु
	अगर (!ip)
		वापस;

	clear_bit_unlock(GIF_GLOP_PENDING, &ip->i_flags);
	wake_up_bit(&ip->i_flags, GIF_GLOP_PENDING);
पूर्ण

/**
 * gfs2_inode_metasync - sync out the metadata of an inode
 * @gl: the glock protecting the inode
 *
 */
पूर्णांक gfs2_inode_metasync(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा address_space *metamapping = gfs2_glock2aspace(gl);
	पूर्णांक error;

	filemap_fdataग_लिखो(metamapping);
	error = filemap_fdataरुको(metamapping);
	अगर (error)
		gfs2_io_error(gl->gl_name.ln_sbd);
	वापस error;
पूर्ण

/**
 * inode_go_sync - Sync the dirty metadata of an inode
 * @gl: the glock protecting the inode
 *
 */

अटल पूर्णांक inode_go_sync(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_inode *ip = gfs2_glock2inode(gl);
	पूर्णांक isreg = ip && S_ISREG(ip->i_inode.i_mode);
	काष्ठा address_space *metamapping = gfs2_glock2aspace(gl);
	पूर्णांक error = 0, ret;

	अगर (isreg) अणु
		अगर (test_and_clear_bit(GIF_SW_PAGED, &ip->i_flags))
			unmap_shared_mapping_range(ip->i_inode.i_mapping, 0, 0);
		inode_dio_रुको(&ip->i_inode);
	पूर्ण
	अगर (!test_and_clear_bit(GLF_सूचीTY, &gl->gl_flags))
		जाओ out;

	GLOCK_BUG_ON(gl, gl->gl_state != LM_ST_EXCLUSIVE);

	gfs2_log_flush(gl->gl_name.ln_sbd, gl, GFS2_LOG_HEAD_FLUSH_NORMAL |
		       GFS2_LFC_INODE_GO_SYNC);
	filemap_fdataग_लिखो(metamapping);
	अगर (isreg) अणु
		काष्ठा address_space *mapping = ip->i_inode.i_mapping;
		filemap_fdataग_लिखो(mapping);
		error = filemap_fdataरुको(mapping);
		mapping_set_error(mapping, error);
	पूर्ण
	ret = gfs2_inode_metasync(gl);
	अगर (!error)
		error = ret;
	gfs2_ail_empty_gl(gl);
	/*
	 * Writeback of the data mapping may cause the dirty flag to be set
	 * so we have to clear it again here.
	 */
	smp_mb__beक्रमe_atomic();
	clear_bit(GLF_सूचीTY, &gl->gl_flags);

out:
	gfs2_clear_glop_pending(ip);
	वापस error;
पूर्ण

/**
 * inode_go_inval - prepare a inode glock to be released
 * @gl: the glock
 * @flags:
 *
 * Normally we invalidate everything, but अगर we are moving पूर्णांकo
 * LM_ST_DEFERRED from LM_ST_SHARED or LM_ST_EXCLUSIVE then we
 * can keep hold of the metadata, since it won't have changed.
 *
 */

अटल व्योम inode_go_inval(काष्ठा gfs2_glock *gl, पूर्णांक flags)
अणु
	काष्ठा gfs2_inode *ip = gfs2_glock2inode(gl);

	अगर (flags & DIO_METADATA) अणु
		काष्ठा address_space *mapping = gfs2_glock2aspace(gl);
		truncate_inode_pages(mapping, 0);
		अगर (ip) अणु
			set_bit(GIF_INVALID, &ip->i_flags);
			क्रमget_all_cached_acls(&ip->i_inode);
			security_inode_invalidate_secctx(&ip->i_inode);
			gfs2_dir_hash_inval(ip);
		पूर्ण
	पूर्ण

	अगर (ip == GFS2_I(gl->gl_name.ln_sbd->sd_rindex)) अणु
		gfs2_log_flush(gl->gl_name.ln_sbd, शून्य,
			       GFS2_LOG_HEAD_FLUSH_NORMAL |
			       GFS2_LFC_INODE_GO_INVAL);
		gl->gl_name.ln_sbd->sd_rindex_uptodate = 0;
	पूर्ण
	अगर (ip && S_ISREG(ip->i_inode.i_mode))
		truncate_inode_pages(ip->i_inode.i_mapping, 0);

	gfs2_clear_glop_pending(ip);
पूर्ण

/**
 * inode_go_demote_ok - Check to see अगर it's ok to unlock an inode glock
 * @gl: the glock
 *
 * Returns: 1 अगर it's ok
 */

अटल पूर्णांक inode_go_demote_ok(स्थिर काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;

	अगर (sdp->sd_jindex == gl->gl_object || sdp->sd_rindex == gl->gl_object)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक gfs2_dinode_in(काष्ठा gfs2_inode *ip, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा gfs2_dinode *str = buf;
	काष्ठा बारpec64 aसमय;
	u16 height, depth;
	umode_t mode = be32_to_cpu(str->di_mode);
	bool is_new = ip->i_inode.i_state & I_NEW;

	अगर (unlikely(ip->i_no_addr != be64_to_cpu(str->di_num.no_addr)))
		जाओ corrupt;
	अगर (unlikely(!is_new && inode_wrong_type(&ip->i_inode, mode)))
		जाओ corrupt;
	ip->i_no_क्रमmal_ino = be64_to_cpu(str->di_num.no_क्रमmal_ino);
	ip->i_inode.i_mode = mode;
	अगर (is_new) अणु
		ip->i_inode.i_rdev = 0;
		चयन (mode & S_IFMT) अणु
		हाल S_IFBLK:
		हाल S_IFCHR:
			ip->i_inode.i_rdev = MKDEV(be32_to_cpu(str->di_major),
						   be32_to_cpu(str->di_minor));
			अवरोध;
		पूर्ण
	पूर्ण

	i_uid_ग_लिखो(&ip->i_inode, be32_to_cpu(str->di_uid));
	i_gid_ग_लिखो(&ip->i_inode, be32_to_cpu(str->di_gid));
	set_nlink(&ip->i_inode, be32_to_cpu(str->di_nlink));
	i_size_ग_लिखो(&ip->i_inode, be64_to_cpu(str->di_size));
	gfs2_set_inode_blocks(&ip->i_inode, be64_to_cpu(str->di_blocks));
	aसमय.tv_sec = be64_to_cpu(str->di_aसमय);
	aसमय.tv_nsec = be32_to_cpu(str->di_aसमय_nsec);
	अगर (बारpec64_compare(&ip->i_inode.i_aसमय, &aसमय) < 0)
		ip->i_inode.i_aसमय = aसमय;
	ip->i_inode.i_mसमय.tv_sec = be64_to_cpu(str->di_mसमय);
	ip->i_inode.i_mसमय.tv_nsec = be32_to_cpu(str->di_mसमय_nsec);
	ip->i_inode.i_स_समय.tv_sec = be64_to_cpu(str->di_स_समय);
	ip->i_inode.i_स_समय.tv_nsec = be32_to_cpu(str->di_स_समय_nsec);

	ip->i_goal = be64_to_cpu(str->di_goal_meta);
	ip->i_generation = be64_to_cpu(str->di_generation);

	ip->i_diskflags = be32_to_cpu(str->di_flags);
	ip->i_eattr = be64_to_cpu(str->di_eattr);
	/* i_diskflags and i_eattr must be set beक्रमe gfs2_set_inode_flags() */
	gfs2_set_inode_flags(&ip->i_inode);
	height = be16_to_cpu(str->di_height);
	अगर (unlikely(height > GFS2_MAX_META_HEIGHT))
		जाओ corrupt;
	ip->i_height = (u8)height;

	depth = be16_to_cpu(str->di_depth);
	अगर (unlikely(depth > GFS2_सूची_MAX_DEPTH))
		जाओ corrupt;
	ip->i_depth = (u8)depth;
	ip->i_entries = be32_to_cpu(str->di_entries);

	अगर (S_ISREG(ip->i_inode.i_mode))
		gfs2_set_aops(&ip->i_inode);

	वापस 0;
corrupt:
	gfs2_consist_inode(ip);
	वापस -EIO;
पूर्ण

/**
 * gfs2_inode_refresh - Refresh the incore copy of the dinode
 * @ip: The GFS2 inode
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_inode_refresh(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा buffer_head *dibh;
	पूर्णांक error;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		वापस error;

	error = gfs2_dinode_in(ip, dibh->b_data);
	brअन्यथा(dibh);
	clear_bit(GIF_INVALID, &ip->i_flags);

	वापस error;
पूर्ण

/**
 * inode_go_lock - operation करोne after an inode lock is locked by a process
 * @gh: The glock holder
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक inode_go_lock(काष्ठा gfs2_holder *gh)
अणु
	काष्ठा gfs2_glock *gl = gh->gh_gl;
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा gfs2_inode *ip = gl->gl_object;
	पूर्णांक error = 0;

	अगर (!ip || (gh->gh_flags & GL_SKIP))
		वापस 0;

	अगर (test_bit(GIF_INVALID, &ip->i_flags)) अणु
		error = gfs2_inode_refresh(ip);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (gh->gh_state != LM_ST_DEFERRED)
		inode_dio_रुको(&ip->i_inode);

	अगर ((ip->i_diskflags & GFS2_DIF_TRUNC_IN_PROG) &&
	    (gl->gl_state == LM_ST_EXCLUSIVE) &&
	    (gh->gh_state == LM_ST_EXCLUSIVE)) अणु
		spin_lock(&sdp->sd_trunc_lock);
		अगर (list_empty(&ip->i_trunc_list))
			list_add(&ip->i_trunc_list, &sdp->sd_trunc_list);
		spin_unlock(&sdp->sd_trunc_lock);
		wake_up(&sdp->sd_quota_रुको);
		वापस 1;
	पूर्ण

	वापस error;
पूर्ण

/**
 * inode_go_dump - prपूर्णांक inक्रमmation about an inode
 * @seq: The iterator
 * @gl: The glock
 * @fs_id_buf: file प्रणाली id (may be empty)
 *
 */

अटल व्योम inode_go_dump(काष्ठा seq_file *seq, काष्ठा gfs2_glock *gl,
			  स्थिर अक्षर *fs_id_buf)
अणु
	काष्ठा gfs2_inode *ip = gl->gl_object;
	काष्ठा inode *inode = &ip->i_inode;
	अचिन्हित दीर्घ nrpages;

	अगर (ip == शून्य)
		वापस;

	xa_lock_irq(&inode->i_data.i_pages);
	nrpages = inode->i_data.nrpages;
	xa_unlock_irq(&inode->i_data.i_pages);

	gfs2_prपूर्णांक_dbg(seq, "%s I: n:%llu/%llu t:%u f:0x%02lx d:0x%08x s:%llu "
		       "p:%lu\n", fs_id_buf,
		  (अचिन्हित दीर्घ दीर्घ)ip->i_no_क्रमmal_ino,
		  (अचिन्हित दीर्घ दीर्घ)ip->i_no_addr,
		  IF2DT(ip->i_inode.i_mode), ip->i_flags,
		  (अचिन्हित पूर्णांक)ip->i_diskflags,
		  (अचिन्हित दीर्घ दीर्घ)i_size_पढ़ो(inode), nrpages);
पूर्ण

/**
 * मुक्तze_go_sync - promote/demote the मुक्तze glock
 * @gl: the glock
 */

अटल पूर्णांक मुक्तze_go_sync(काष्ठा gfs2_glock *gl)
अणु
	पूर्णांक error = 0;
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;

	/*
	 * We need to check gl_state == LM_ST_SHARED here and not gl_req ==
	 * LM_ST_EXCLUSIVE. That's because when any node करोes a मुक्तze,
	 * all the nodes should have the मुक्तze glock in SH mode and they all
	 * call करो_xmote: One क्रम EX and the others क्रम UN. They ALL must
	 * मुक्तze locally, and they ALL must queue मुक्तze work. The मुक्तze_work
	 * calls मुक्तze_func, which tries to reacquire the मुक्तze glock in SH,
	 * effectively रुकोing क्रम the thaw on the node who holds it in EX.
	 * Once thawed, the work func acquires the मुक्तze glock in
	 * SH and everybody goes back to thawed.
	 */
	अगर (gl->gl_state == LM_ST_SHARED && !gfs2_withdrawn(sdp) &&
	    !test_bit(SDF_NORECOVERY, &sdp->sd_flags)) अणु
		atomic_set(&sdp->sd_मुक्तze_state, SFS_STARTING_FREEZE);
		error = मुक्तze_super(sdp->sd_vfs);
		अगर (error) अणु
			fs_info(sdp, "GFS2: couldn't freeze filesystem: %d\n",
				error);
			अगर (gfs2_withdrawn(sdp)) अणु
				atomic_set(&sdp->sd_मुक्तze_state, SFS_UNFROZEN);
				वापस 0;
			पूर्ण
			gfs2_निश्चित_withdraw(sdp, 0);
		पूर्ण
		queue_work(gfs2_मुक्तze_wq, &sdp->sd_मुक्तze_work);
		अगर (test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags))
			gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_FREEZE |
				       GFS2_LFC_FREEZE_GO_SYNC);
		अन्यथा /* पढ़ो-only mounts */
			atomic_set(&sdp->sd_मुक्तze_state, SFS_FROZEN);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * मुक्तze_go_xmote_bh - After promoting/demoting the मुक्तze glock
 * @gl: the glock
 */
अटल पूर्णांक मुक्तze_go_xmote_bh(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_jdesc->jd_inode);
	काष्ठा gfs2_glock *j_gl = ip->i_gl;
	काष्ठा gfs2_log_header_host head;
	पूर्णांक error;

	अगर (test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags)) अणु
		j_gl->gl_ops->go_inval(j_gl, DIO_METADATA);

		error = gfs2_find_jhead(sdp->sd_jdesc, &head, false);
		अगर (error)
			gfs2_consist(sdp);
		अगर (!(head.lh_flags & GFS2_LOG_HEAD_UNMOUNT))
			gfs2_consist(sdp);

		/*  Initialize some head of the log stuff  */
		अगर (!gfs2_withdrawn(sdp)) अणु
			sdp->sd_log_sequence = head.lh_sequence + 1;
			gfs2_log_poपूर्णांकers_init(sdp, head.lh_blkno);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * मुक्तze_go_demote_ok
 * @gl: the glock
 *
 * Always वापसs 0
 */

अटल पूर्णांक मुक्तze_go_demote_ok(स्थिर काष्ठा gfs2_glock *gl)
अणु
	वापस 0;
पूर्ण

/**
 * iखोलो_go_callback - schedule the dcache entry क्रम the inode to be deleted
 * @gl: the glock
 * @remote: true अगर this came from a dअगरferent cluster node
 *
 * gl_lockref.lock lock is held जबतक calling this
 */
अटल व्योम iखोलो_go_callback(काष्ठा gfs2_glock *gl, bool remote)
अणु
	काष्ठा gfs2_inode *ip = gl->gl_object;
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;

	अगर (!remote || sb_rकरोnly(sdp->sd_vfs))
		वापस;

	अगर (gl->gl_demote_state == LM_ST_UNLOCKED &&
	    gl->gl_state == LM_ST_SHARED && ip) अणु
		gl->gl_lockref.count++;
		अगर (!queue_delayed_work(gfs2_delete_workqueue,
					&gl->gl_delete, 0))
			gl->gl_lockref.count--;
	पूर्ण
पूर्ण

अटल पूर्णांक iखोलो_go_demote_ok(स्थिर काष्ठा gfs2_glock *gl)
अणु
       वापस !gfs2_delete_work_queued(gl);
पूर्ण

/**
 * inode_go_मुक्त - wake up anyone रुकोing क्रम dlm's unlock ast to मुक्त it
 * @gl: glock being मुक्तd
 *
 * For now, this is only used क्रम the journal inode glock. In withdraw
 * situations, we need to रुको क्रम the glock to be मुक्तd so that we know
 * other nodes may proceed with recovery / journal replay.
 */
अटल व्योम inode_go_मुक्त(काष्ठा gfs2_glock *gl)
अणु
	/* Note that we cannot reference gl_object because it's alपढ़ोy set
	 * to शून्य by this poपूर्णांक in its lअगरecycle. */
	अगर (!test_bit(GLF_FREEING, &gl->gl_flags))
		वापस;
	clear_bit_unlock(GLF_FREEING, &gl->gl_flags);
	wake_up_bit(&gl->gl_flags, GLF_FREEING);
पूर्ण

/**
 * nondisk_go_callback - used to संकेत when a node did a withdraw
 * @gl: the nondisk glock
 * @remote: true अगर this came from a dअगरferent cluster node
 *
 */
अटल व्योम nondisk_go_callback(काष्ठा gfs2_glock *gl, bool remote)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;

	/* Ignore the callback unless it's from another node, and it's the
	   live lock. */
	अगर (!remote || gl->gl_name.ln_number != GFS2_LIVE_LOCK)
		वापस;

	/* First order of business is to cancel the demote request. We करोn't
	 * really want to demote a nondisk glock. At best it's just to inक्रमm
	 * us of another node's withdraw. We'll keep it in SH mode. */
	clear_bit(GLF_DEMOTE, &gl->gl_flags);
	clear_bit(GLF_PENDING_DEMOTE, &gl->gl_flags);

	/* Ignore the unlock अगर we're withdrawn, unmounting, or in recovery. */
	अगर (test_bit(SDF_NORECOVERY, &sdp->sd_flags) ||
	    test_bit(SDF_WITHDRAWN, &sdp->sd_flags) ||
	    test_bit(SDF_REMOTE_WITHDRAW, &sdp->sd_flags))
		वापस;

	/* We only care when a node wants us to unlock, because that means
	 * they want a journal recovered. */
	अगर (gl->gl_demote_state != LM_ST_UNLOCKED)
		वापस;

	अगर (sdp->sd_args.ar_spectator) अणु
		fs_warn(sdp, "Spectator node cannot recover journals.\n");
		वापस;
	पूर्ण

	fs_warn(sdp, "Some node has withdrawn; checking for recovery.\n");
	set_bit(SDF_REMOTE_WITHDRAW, &sdp->sd_flags);
	/*
	 * We can't call remote_withdraw directly here or gfs2_recover_journal
	 * because this is called from the glock unlock function and the
	 * remote_withdraw needs to enqueue and dequeue the same "live" glock
	 * we were called from. So we queue it to the control work queue in
	 * lock_dlm.
	 */
	queue_delayed_work(gfs2_control_wq, &sdp->sd_control_work, 0);
पूर्ण

स्थिर काष्ठा gfs2_glock_operations gfs2_meta_glops = अणु
	.go_type = LM_TYPE_META,
	.go_flags = GLOF_NONDISK,
पूर्ण;

स्थिर काष्ठा gfs2_glock_operations gfs2_inode_glops = अणु
	.go_sync = inode_go_sync,
	.go_inval = inode_go_inval,
	.go_demote_ok = inode_go_demote_ok,
	.go_lock = inode_go_lock,
	.go_dump = inode_go_dump,
	.go_type = LM_TYPE_INODE,
	.go_flags = GLOF_ASPACE | GLOF_LRU | GLOF_LVB,
	.go_मुक्त = inode_go_मुक्त,
पूर्ण;

स्थिर काष्ठा gfs2_glock_operations gfs2_rgrp_glops = अणु
	.go_sync = rgrp_go_sync,
	.go_inval = rgrp_go_inval,
	.go_lock = gfs2_rgrp_go_lock,
	.go_dump = gfs2_rgrp_go_dump,
	.go_type = LM_TYPE_RGRP,
	.go_flags = GLOF_LVB,
पूर्ण;

स्थिर काष्ठा gfs2_glock_operations gfs2_मुक्तze_glops = अणु
	.go_sync = मुक्तze_go_sync,
	.go_xmote_bh = मुक्तze_go_xmote_bh,
	.go_demote_ok = मुक्तze_go_demote_ok,
	.go_type = LM_TYPE_NONDISK,
	.go_flags = GLOF_NONDISK,
पूर्ण;

स्थिर काष्ठा gfs2_glock_operations gfs2_iखोलो_glops = अणु
	.go_type = LM_TYPE_IOPEN,
	.go_callback = iखोलो_go_callback,
	.go_demote_ok = iखोलो_go_demote_ok,
	.go_flags = GLOF_LRU | GLOF_NONDISK,
	.go_subclass = 1,
पूर्ण;

स्थिर काष्ठा gfs2_glock_operations gfs2_flock_glops = अणु
	.go_type = LM_TYPE_FLOCK,
	.go_flags = GLOF_LRU | GLOF_NONDISK,
पूर्ण;

स्थिर काष्ठा gfs2_glock_operations gfs2_nondisk_glops = अणु
	.go_type = LM_TYPE_NONDISK,
	.go_flags = GLOF_NONDISK,
	.go_callback = nondisk_go_callback,
पूर्ण;

स्थिर काष्ठा gfs2_glock_operations gfs2_quota_glops = अणु
	.go_type = LM_TYPE_QUOTA,
	.go_flags = GLOF_LVB | GLOF_LRU | GLOF_NONDISK,
पूर्ण;

स्थिर काष्ठा gfs2_glock_operations gfs2_journal_glops = अणु
	.go_type = LM_TYPE_JOURNAL,
	.go_flags = GLOF_NONDISK,
पूर्ण;

स्थिर काष्ठा gfs2_glock_operations *gfs2_glops_list[] = अणु
	[LM_TYPE_META] = &gfs2_meta_glops,
	[LM_TYPE_INODE] = &gfs2_inode_glops,
	[LM_TYPE_RGRP] = &gfs2_rgrp_glops,
	[LM_TYPE_IOPEN] = &gfs2_iखोलो_glops,
	[LM_TYPE_FLOCK] = &gfs2_flock_glops,
	[LM_TYPE_NONDISK] = &gfs2_nondisk_glops,
	[LM_TYPE_QUOTA] = &gfs2_quota_glops,
	[LM_TYPE_JOURNAL] = &gfs2_journal_glops,
पूर्ण;

