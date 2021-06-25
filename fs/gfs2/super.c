<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2007 Red Hat, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bपन.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/statfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mount.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/kernel.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "bmap.h"
#समावेश "dir.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "inode.h"
#समावेश "log.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "recovery.h"
#समावेश "rgrp.h"
#समावेश "super.h"
#समावेश "trans.h"
#समावेश "util.h"
#समावेश "sys.h"
#समावेश "xattr.h"
#समावेश "lops.h"

क्रमागत dinode_demise अणु
	SHOULD_DELETE_DINODE,
	SHOULD_NOT_DELETE_DINODE,
	SHOULD_DEFER_EVICTION,
पूर्ण;

/**
 * gfs2_jindex_मुक्त - Clear all the journal index inक्रमmation
 * @sdp: The GFS2 superblock
 *
 */

व्योम gfs2_jindex_मुक्त(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा list_head list;
	काष्ठा gfs2_jdesc *jd;

	spin_lock(&sdp->sd_jindex_spin);
	list_add(&list, &sdp->sd_jindex_list);
	list_del_init(&sdp->sd_jindex_list);
	sdp->sd_journals = 0;
	spin_unlock(&sdp->sd_jindex_spin);

	sdp->sd_jdesc = शून्य;
	जबतक (!list_empty(&list)) अणु
		jd = list_first_entry(&list, काष्ठा gfs2_jdesc, jd_list);
		gfs2_मुक्त_journal_extents(jd);
		list_del(&jd->jd_list);
		iput(jd->jd_inode);
		jd->jd_inode = शून्य;
		kमुक्त(jd);
	पूर्ण
पूर्ण

अटल काष्ठा gfs2_jdesc *jdesc_find_i(काष्ठा list_head *head, अचिन्हित पूर्णांक jid)
अणु
	काष्ठा gfs2_jdesc *jd;

	list_क्रम_each_entry(jd, head, jd_list) अणु
		अगर (jd->jd_jid == jid)
			वापस jd;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा gfs2_jdesc *gfs2_jdesc_find(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक jid)
अणु
	काष्ठा gfs2_jdesc *jd;

	spin_lock(&sdp->sd_jindex_spin);
	jd = jdesc_find_i(&sdp->sd_jindex_list, jid);
	spin_unlock(&sdp->sd_jindex_spin);

	वापस jd;
पूर्ण

पूर्णांक gfs2_jdesc_check(काष्ठा gfs2_jdesc *jd)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(jd->jd_inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	u64 size = i_size_पढ़ो(jd->jd_inode);

	अगर (gfs2_check_पूर्णांकernal_file_size(jd->jd_inode, 8 << 20, BIT(30)))
		वापस -EIO;

	jd->jd_blocks = size >> sdp->sd_sb.sb_bsize_shअगरt;

	अगर (gfs2_ग_लिखो_alloc_required(ip, 0, size)) अणु
		gfs2_consist_inode(ip);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_thपढ़ोs(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा task_काष्ठा *p;
	पूर्णांक error = 0;

	p = kthपढ़ो_run(gfs2_logd, sdp, "gfs2_logd");
	अगर (IS_ERR(p)) अणु
		error = PTR_ERR(p);
		fs_err(sdp, "can't start logd thread: %d\n", error);
		वापस error;
	पूर्ण
	sdp->sd_logd_process = p;

	p = kthपढ़ो_run(gfs2_quotad, sdp, "gfs2_quotad");
	अगर (IS_ERR(p)) अणु
		error = PTR_ERR(p);
		fs_err(sdp, "can't start quotad thread: %d\n", error);
		जाओ fail;
	पूर्ण
	sdp->sd_quotad_process = p;
	वापस 0;

fail:
	kthपढ़ो_stop(sdp->sd_logd_process);
	sdp->sd_logd_process = शून्य;
	वापस error;
पूर्ण

/**
 * gfs2_make_fs_rw - Turn a Read-Only FS पूर्णांकo a Read-Write one
 * @sdp: the fileप्रणाली
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_make_fs_rw(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_jdesc->jd_inode);
	काष्ठा gfs2_glock *j_gl = ip->i_gl;
	काष्ठा gfs2_log_header_host head;
	पूर्णांक error;

	error = init_thपढ़ोs(sdp);
	अगर (error) अणु
		gfs2_withdraw_delayed(sdp);
		वापस error;
	पूर्ण

	j_gl->gl_ops->go_inval(j_gl, DIO_METADATA);
	अगर (gfs2_withdrawn(sdp)) अणु
		error = -EIO;
		जाओ fail;
	पूर्ण

	error = gfs2_find_jhead(sdp->sd_jdesc, &head, false);
	अगर (error || gfs2_withdrawn(sdp))
		जाओ fail;

	अगर (!(head.lh_flags & GFS2_LOG_HEAD_UNMOUNT)) अणु
		gfs2_consist(sdp);
		error = -EIO;
		जाओ fail;
	पूर्ण

	/*  Initialize some head of the log stuff  */
	sdp->sd_log_sequence = head.lh_sequence + 1;
	gfs2_log_poपूर्णांकers_init(sdp, head.lh_blkno);

	error = gfs2_quota_init(sdp);
	अगर (error || gfs2_withdrawn(sdp))
		जाओ fail;

	set_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags);

	वापस 0;

fail:
	अगर (sdp->sd_quotad_process)
		kthपढ़ो_stop(sdp->sd_quotad_process);
	sdp->sd_quotad_process = शून्य;
	अगर (sdp->sd_logd_process)
		kthपढ़ो_stop(sdp->sd_logd_process);
	sdp->sd_logd_process = शून्य;
	वापस error;
पूर्ण

व्योम gfs2_statfs_change_in(काष्ठा gfs2_statfs_change_host *sc, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा gfs2_statfs_change *str = buf;

	sc->sc_total = be64_to_cpu(str->sc_total);
	sc->sc_मुक्त = be64_to_cpu(str->sc_मुक्त);
	sc->sc_dinodes = be64_to_cpu(str->sc_dinodes);
पूर्ण

व्योम gfs2_statfs_change_out(स्थिर काष्ठा gfs2_statfs_change_host *sc, व्योम *buf)
अणु
	काष्ठा gfs2_statfs_change *str = buf;

	str->sc_total = cpu_to_be64(sc->sc_total);
	str->sc_मुक्त = cpu_to_be64(sc->sc_मुक्त);
	str->sc_dinodes = cpu_to_be64(sc->sc_dinodes);
पूर्ण

पूर्णांक gfs2_statfs_init(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	काष्ठा gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	काष्ठा gfs2_inode *l_ip = GFS2_I(sdp->sd_sc_inode);
	काष्ठा gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;
	काष्ठा buffer_head *m_bh, *l_bh;
	काष्ठा gfs2_holder gh;
	पूर्णांक error;

	error = gfs2_glock_nq_init(m_ip->i_gl, LM_ST_EXCLUSIVE, GL_NOCACHE,
				   &gh);
	अगर (error)
		वापस error;

	error = gfs2_meta_inode_buffer(m_ip, &m_bh);
	अगर (error)
		जाओ out;

	अगर (sdp->sd_args.ar_spectator) अणु
		spin_lock(&sdp->sd_statfs_spin);
		gfs2_statfs_change_in(m_sc, m_bh->b_data +
				      माप(काष्ठा gfs2_dinode));
		spin_unlock(&sdp->sd_statfs_spin);
	पूर्ण अन्यथा अणु
		error = gfs2_meta_inode_buffer(l_ip, &l_bh);
		अगर (error)
			जाओ out_m_bh;

		spin_lock(&sdp->sd_statfs_spin);
		gfs2_statfs_change_in(m_sc, m_bh->b_data +
				      माप(काष्ठा gfs2_dinode));
		gfs2_statfs_change_in(l_sc, l_bh->b_data +
				      माप(काष्ठा gfs2_dinode));
		spin_unlock(&sdp->sd_statfs_spin);

		brअन्यथा(l_bh);
	पूर्ण

out_m_bh:
	brअन्यथा(m_bh);
out:
	gfs2_glock_dq_uninit(&gh);
	वापस 0;
पूर्ण

व्योम gfs2_statfs_change(काष्ठा gfs2_sbd *sdp, s64 total, s64 मुक्त,
			s64 dinodes)
अणु
	काष्ठा gfs2_inode *l_ip = GFS2_I(sdp->sd_sc_inode);
	काष्ठा gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;
	काष्ठा gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	काष्ठा buffer_head *l_bh;
	s64 x, y;
	पूर्णांक need_sync = 0;
	पूर्णांक error;

	error = gfs2_meta_inode_buffer(l_ip, &l_bh);
	अगर (error)
		वापस;

	gfs2_trans_add_meta(l_ip->i_gl, l_bh);

	spin_lock(&sdp->sd_statfs_spin);
	l_sc->sc_total += total;
	l_sc->sc_मुक्त += मुक्त;
	l_sc->sc_dinodes += dinodes;
	gfs2_statfs_change_out(l_sc, l_bh->b_data + माप(काष्ठा gfs2_dinode));
	अगर (sdp->sd_args.ar_statfs_percent) अणु
		x = 100 * l_sc->sc_मुक्त;
		y = m_sc->sc_मुक्त * sdp->sd_args.ar_statfs_percent;
		अगर (x >= y || x <= -y)
			need_sync = 1;
	पूर्ण
	spin_unlock(&sdp->sd_statfs_spin);

	brअन्यथा(l_bh);
	अगर (need_sync)
		gfs2_wake_up_statfs(sdp);
पूर्ण

व्योम update_statfs(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *m_bh,
		   काष्ठा buffer_head *l_bh)
अणु
	काष्ठा gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	काष्ठा gfs2_inode *l_ip = GFS2_I(sdp->sd_sc_inode);
	काष्ठा gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	काष्ठा gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;

	gfs2_trans_add_meta(l_ip->i_gl, l_bh);
	gfs2_trans_add_meta(m_ip->i_gl, m_bh);

	spin_lock(&sdp->sd_statfs_spin);
	m_sc->sc_total += l_sc->sc_total;
	m_sc->sc_मुक्त += l_sc->sc_मुक्त;
	m_sc->sc_dinodes += l_sc->sc_dinodes;
	स_रखो(l_sc, 0, माप(काष्ठा gfs2_statfs_change));
	स_रखो(l_bh->b_data + माप(काष्ठा gfs2_dinode),
	       0, माप(काष्ठा gfs2_statfs_change));
	gfs2_statfs_change_out(m_sc, m_bh->b_data + माप(काष्ठा gfs2_dinode));
	spin_unlock(&sdp->sd_statfs_spin);
पूर्ण

पूर्णांक gfs2_statfs_sync(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	काष्ठा gfs2_inode *l_ip = GFS2_I(sdp->sd_sc_inode);
	काष्ठा gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	काष्ठा gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;
	काष्ठा gfs2_holder gh;
	काष्ठा buffer_head *m_bh, *l_bh;
	पूर्णांक error;

	error = gfs2_glock_nq_init(m_ip->i_gl, LM_ST_EXCLUSIVE, GL_NOCACHE,
				   &gh);
	अगर (error)
		जाओ out;

	error = gfs2_meta_inode_buffer(m_ip, &m_bh);
	अगर (error)
		जाओ out_unlock;

	spin_lock(&sdp->sd_statfs_spin);
	gfs2_statfs_change_in(m_sc, m_bh->b_data +
			      माप(काष्ठा gfs2_dinode));
	अगर (!l_sc->sc_total && !l_sc->sc_मुक्त && !l_sc->sc_dinodes) अणु
		spin_unlock(&sdp->sd_statfs_spin);
		जाओ out_bh;
	पूर्ण
	spin_unlock(&sdp->sd_statfs_spin);

	error = gfs2_meta_inode_buffer(l_ip, &l_bh);
	अगर (error)
		जाओ out_bh;

	error = gfs2_trans_begin(sdp, 2 * RES_DINODE, 0);
	अगर (error)
		जाओ out_bh2;

	update_statfs(sdp, m_bh, l_bh);
	sdp->sd_statfs_क्रमce_sync = 0;

	gfs2_trans_end(sdp);

out_bh2:
	brअन्यथा(l_bh);
out_bh:
	brअन्यथा(m_bh);
out_unlock:
	gfs2_glock_dq_uninit(&gh);
out:
	वापस error;
पूर्ण

काष्ठा lfcc अणु
	काष्ठा list_head list;
	काष्ठा gfs2_holder gh;
पूर्ण;

/**
 * gfs2_lock_fs_check_clean - Stop all ग_लिखोs to the FS and check that all
 *                            journals are clean
 * @sdp: the file प्रणाली
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_lock_fs_check_clean(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_inode *ip;
	काष्ठा gfs2_jdesc *jd;
	काष्ठा lfcc *lfcc;
	LIST_HEAD(list);
	काष्ठा gfs2_log_header_host lh;
	पूर्णांक error;

	list_क्रम_each_entry(jd, &sdp->sd_jindex_list, jd_list) अणु
		lfcc = kदो_स्मृति(माप(काष्ठा lfcc), GFP_KERNEL);
		अगर (!lfcc) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
		ip = GFS2_I(jd->jd_inode);
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &lfcc->gh);
		अगर (error) अणु
			kमुक्त(lfcc);
			जाओ out;
		पूर्ण
		list_add(&lfcc->list, &list);
	पूर्ण

	error = gfs2_glock_nq_init(sdp->sd_मुक्तze_gl, LM_ST_EXCLUSIVE,
				   LM_FLAG_NOEXP, &sdp->sd_मुक्तze_gh);
	अगर (error)
		जाओ out;

	list_क्रम_each_entry(jd, &sdp->sd_jindex_list, jd_list) अणु
		error = gfs2_jdesc_check(jd);
		अगर (error)
			अवरोध;
		error = gfs2_find_jhead(jd, &lh, false);
		अगर (error)
			अवरोध;
		अगर (!(lh.lh_flags & GFS2_LOG_HEAD_UNMOUNT)) अणु
			error = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (error)
		gfs2_मुक्तze_unlock(&sdp->sd_मुक्तze_gh);

out:
	जबतक (!list_empty(&list)) अणु
		lfcc = list_first_entry(&list, काष्ठा lfcc, list);
		list_del(&lfcc->list);
		gfs2_glock_dq_uninit(&lfcc->gh);
		kमुक्त(lfcc);
	पूर्ण
	वापस error;
पूर्ण

व्योम gfs2_dinode_out(स्थिर काष्ठा gfs2_inode *ip, व्योम *buf)
अणु
	काष्ठा gfs2_dinode *str = buf;

	str->di_header.mh_magic = cpu_to_be32(GFS2_MAGIC);
	str->di_header.mh_type = cpu_to_be32(GFS2_METATYPE_DI);
	str->di_header.mh_क्रमmat = cpu_to_be32(GFS2_FORMAT_DI);
	str->di_num.no_addr = cpu_to_be64(ip->i_no_addr);
	str->di_num.no_क्रमmal_ino = cpu_to_be64(ip->i_no_क्रमmal_ino);
	str->di_mode = cpu_to_be32(ip->i_inode.i_mode);
	str->di_uid = cpu_to_be32(i_uid_पढ़ो(&ip->i_inode));
	str->di_gid = cpu_to_be32(i_gid_पढ़ो(&ip->i_inode));
	str->di_nlink = cpu_to_be32(ip->i_inode.i_nlink);
	str->di_size = cpu_to_be64(i_size_पढ़ो(&ip->i_inode));
	str->di_blocks = cpu_to_be64(gfs2_get_inode_blocks(&ip->i_inode));
	str->di_aसमय = cpu_to_be64(ip->i_inode.i_aसमय.tv_sec);
	str->di_mसमय = cpu_to_be64(ip->i_inode.i_mसमय.tv_sec);
	str->di_स_समय = cpu_to_be64(ip->i_inode.i_स_समय.tv_sec);

	str->di_goal_meta = cpu_to_be64(ip->i_goal);
	str->di_goal_data = cpu_to_be64(ip->i_goal);
	str->di_generation = cpu_to_be64(ip->i_generation);

	str->di_flags = cpu_to_be32(ip->i_diskflags);
	str->di_height = cpu_to_be16(ip->i_height);
	str->di_payload_क्रमmat = cpu_to_be32(S_ISसूची(ip->i_inode.i_mode) &&
					     !(ip->i_diskflags & GFS2_DIF_EXHASH) ?
					     GFS2_FORMAT_DE : 0);
	str->di_depth = cpu_to_be16(ip->i_depth);
	str->di_entries = cpu_to_be32(ip->i_entries);

	str->di_eattr = cpu_to_be64(ip->i_eattr);
	str->di_aसमय_nsec = cpu_to_be32(ip->i_inode.i_aसमय.tv_nsec);
	str->di_mसमय_nsec = cpu_to_be32(ip->i_inode.i_mसमय.tv_nsec);
	str->di_स_समय_nsec = cpu_to_be32(ip->i_inode.i_स_समय.tv_nsec);
पूर्ण

/**
 * gfs2_ग_लिखो_inode - Make sure the inode is stable on the disk
 * @inode: The inode
 * @wbc: The ग_लिखोback control काष्ठाure
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा address_space *metamapping = gfs2_glock2aspace(ip->i_gl);
	काष्ठा backing_dev_info *bdi = inode_to_bdi(metamapping->host);
	पूर्णांक ret = 0;
	bool flush_all = (wbc->sync_mode == WB_SYNC_ALL || gfs2_is_jdata(ip));

	अगर (flush_all)
		gfs2_log_flush(GFS2_SB(inode), ip->i_gl,
			       GFS2_LOG_HEAD_FLUSH_NORMAL |
			       GFS2_LFC_WRITE_INODE);
	अगर (bdi->wb.dirty_exceeded)
		gfs2_ail1_flush(sdp, wbc);
	अन्यथा
		filemap_fdataग_लिखो(metamapping);
	अगर (flush_all)
		ret = filemap_fdataरुको(metamapping);
	अगर (ret)
		mark_inode_dirty_sync(inode);
	अन्यथा अणु
		spin_lock(&inode->i_lock);
		अगर (!(inode->i_flags & I_सूचीTY))
			gfs2_ordered_del_inode(ip);
		spin_unlock(&inode->i_lock);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * gfs2_dirty_inode - check क्रम aसमय updates
 * @inode: The inode in question
 * @flags: The type of dirty
 *
 * Unक्रमtunately it can be called under any combination of inode
 * glock and transaction lock, so we have to check carefully.
 *
 * At the moment this deals only with aसमय - it should be possible
 * to expand that role in future, once a review of the locking has
 * been carried out.
 */

अटल व्योम gfs2_dirty_inode(काष्ठा inode *inode, पूर्णांक flags)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_holder gh;
	पूर्णांक need_unlock = 0;
	पूर्णांक need_endtrans = 0;
	पूर्णांक ret;

	अगर (unlikely(gfs2_withdrawn(sdp)))
		वापस;
	अगर (!gfs2_glock_is_locked_by_me(ip->i_gl)) अणु
		ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
		अगर (ret) अणु
			fs_err(sdp, "dirty_inode: glock %d\n", ret);
			gfs2_dump_glock(शून्य, ip->i_gl, true);
			वापस;
		पूर्ण
		need_unlock = 1;
	पूर्ण अन्यथा अगर (WARN_ON_ONCE(ip->i_gl->gl_state != LM_ST_EXCLUSIVE))
		वापस;

	अगर (current->journal_info == शून्य) अणु
		ret = gfs2_trans_begin(sdp, RES_DINODE, 0);
		अगर (ret) अणु
			fs_err(sdp, "dirty_inode: gfs2_trans_begin %d\n", ret);
			जाओ out;
		पूर्ण
		need_endtrans = 1;
	पूर्ण

	ret = gfs2_meta_inode_buffer(ip, &bh);
	अगर (ret == 0) अणु
		gfs2_trans_add_meta(ip->i_gl, bh);
		gfs2_dinode_out(ip, bh->b_data);
		brअन्यथा(bh);
	पूर्ण

	अगर (need_endtrans)
		gfs2_trans_end(sdp);
out:
	अगर (need_unlock)
		gfs2_glock_dq_uninit(&gh);
पूर्ण

/**
 * gfs2_make_fs_ro - Turn a Read-Write FS पूर्णांकo a Read-Only one
 * @sdp: the fileप्रणाली
 *
 * Returns: त्रुटि_सं
 */

व्योम gfs2_make_fs_ro(काष्ठा gfs2_sbd *sdp)
अणु
	पूर्णांक log_ग_लिखो_allowed = test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags);

	gfs2_flush_delete_work(sdp);
	अगर (!log_ग_लिखो_allowed && current == sdp->sd_quotad_process)
		fs_warn(sdp, "The quotad daemon is withdrawing.\n");
	अन्यथा अगर (sdp->sd_quotad_process)
		kthपढ़ो_stop(sdp->sd_quotad_process);
	sdp->sd_quotad_process = शून्य;

	अगर (!log_ग_लिखो_allowed && current == sdp->sd_logd_process)
		fs_warn(sdp, "The logd daemon is withdrawing.\n");
	अन्यथा अगर (sdp->sd_logd_process)
		kthपढ़ो_stop(sdp->sd_logd_process);
	sdp->sd_logd_process = शून्य;

	अगर (log_ग_लिखो_allowed) अणु
		gfs2_quota_sync(sdp->sd_vfs, 0);
		gfs2_statfs_sync(sdp->sd_vfs, 0);

		gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_SHUTDOWN |
			       GFS2_LFC_MAKE_FS_RO);
		रुको_event_समयout(sdp->sd_log_रुकोq,
				   gfs2_log_is_empty(sdp),
				   HZ * 5);
		gfs2_निश्चित_warn(sdp, gfs2_log_is_empty(sdp));
	पूर्ण अन्यथा अणु
		रुको_event_समयout(sdp->sd_log_रुकोq,
				   gfs2_log_is_empty(sdp),
				   HZ * 5);
	पूर्ण
	gfs2_quota_cleanup(sdp);

	अगर (!log_ग_लिखो_allowed)
		sdp->sd_vfs->s_flags |= SB_RDONLY;
पूर्ण

/**
 * gfs2_put_super - Unmount the fileप्रणाली
 * @sb: The VFS superblock
 *
 */

अटल व्योम gfs2_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा gfs2_jdesc *jd;

	/* No more recovery requests */
	set_bit(SDF_NORECOVERY, &sdp->sd_flags);
	smp_mb();

	/* Wait on outstanding recovery */
restart:
	spin_lock(&sdp->sd_jindex_spin);
	list_क्रम_each_entry(jd, &sdp->sd_jindex_list, jd_list) अणु
		अगर (!test_bit(JDF_RECOVERY, &jd->jd_flags))
			जारी;
		spin_unlock(&sdp->sd_jindex_spin);
		रुको_on_bit(&jd->jd_flags, JDF_RECOVERY,
			    TASK_UNINTERRUPTIBLE);
		जाओ restart;
	पूर्ण
	spin_unlock(&sdp->sd_jindex_spin);

	अगर (!sb_rकरोnly(sb)) अणु
		gfs2_make_fs_ro(sdp);
	पूर्ण
	WARN_ON(gfs2_withdrawing(sdp));

	/*  At this poपूर्णांक, we're through modअगरying the disk  */

	/*  Release stuff  */

	iput(sdp->sd_jindex);
	iput(sdp->sd_statfs_inode);
	iput(sdp->sd_rindex);
	iput(sdp->sd_quota_inode);

	gfs2_glock_put(sdp->sd_नाम_gl);
	gfs2_glock_put(sdp->sd_मुक्तze_gl);

	अगर (!sdp->sd_args.ar_spectator) अणु
		अगर (gfs2_holder_initialized(&sdp->sd_journal_gh))
			gfs2_glock_dq_uninit(&sdp->sd_journal_gh);
		अगर (gfs2_holder_initialized(&sdp->sd_jinode_gh))
			gfs2_glock_dq_uninit(&sdp->sd_jinode_gh);
		gfs2_glock_dq_uninit(&sdp->sd_sc_gh);
		gfs2_glock_dq_uninit(&sdp->sd_qc_gh);
		मुक्त_local_statfs_inodes(sdp);
		iput(sdp->sd_qc_inode);
	पूर्ण

	gfs2_glock_dq_uninit(&sdp->sd_live_gh);
	gfs2_clear_rgrpd(sdp);
	gfs2_jindex_मुक्त(sdp);
	/*  Take apart glock काष्ठाures and buffer lists  */
	gfs2_gl_hash_clear(sdp);
	truncate_inode_pages_final(&sdp->sd_aspace);
	gfs2_delete_debugfs_file(sdp);
	/*  Unmount the locking protocol  */
	gfs2_lm_unmount(sdp);

	/*  At this poपूर्णांक, we're through participating in the lockspace  */
	gfs2_sys_fs_del(sdp);
	मुक्त_sbd(sdp);
पूर्ण

/**
 * gfs2_sync_fs - sync the fileप्रणाली
 * @sb: the superblock
 * @रुको: true to रुको क्रम completion
 *
 * Flushes the log to disk.
 */

अटल पूर्णांक gfs2_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;

	gfs2_quota_sync(sb, -1);
	अगर (रुको)
		gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_NORMAL |
			       GFS2_LFC_SYNC_FS);
	वापस sdp->sd_log_error;
पूर्ण

व्योम gfs2_मुक्तze_func(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक error;
	काष्ठा gfs2_holder मुक्तze_gh;
	काष्ठा gfs2_sbd *sdp = container_of(work, काष्ठा gfs2_sbd, sd_मुक्तze_work);
	काष्ठा super_block *sb = sdp->sd_vfs;

	atomic_inc(&sb->s_active);
	error = gfs2_मुक्तze_lock(sdp, &मुक्तze_gh, 0);
	अगर (error) अणु
		gfs2_निश्चित_withdraw(sdp, 0);
	पूर्ण अन्यथा अणु
		atomic_set(&sdp->sd_मुक्तze_state, SFS_UNFROZEN);
		error = thaw_super(sb);
		अगर (error) अणु
			fs_info(sdp, "GFS2: couldn't thaw filesystem: %d\n",
				error);
			gfs2_निश्चित_withdraw(sdp, 0);
		पूर्ण
		gfs2_मुक्तze_unlock(&मुक्तze_gh);
	पूर्ण
	deactivate_super(sb);
	clear_bit_unlock(SDF_FS_FROZEN, &sdp->sd_flags);
	wake_up_bit(&sdp->sd_flags, SDF_FS_FROZEN);
	वापस;
पूर्ण

/**
 * gfs2_मुक्तze - prevent further ग_लिखोs to the fileप्रणाली
 * @sb: the VFS काष्ठाure क्रम the fileप्रणाली
 *
 */

अटल पूर्णांक gfs2_मुक्तze(काष्ठा super_block *sb)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	पूर्णांक error;

	mutex_lock(&sdp->sd_मुक्तze_mutex);
	अगर (atomic_पढ़ो(&sdp->sd_मुक्तze_state) != SFS_UNFROZEN) अणु
		error = -EBUSY;
		जाओ out;
	पूर्ण

	क्रम (;;) अणु
		अगर (gfs2_withdrawn(sdp)) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण

		error = gfs2_lock_fs_check_clean(sdp);
		अगर (!error)
			अवरोध;

		अगर (error == -EBUSY)
			fs_err(sdp, "waiting for recovery before freeze\n");
		अन्यथा अगर (error == -EIO) अणु
			fs_err(sdp, "Fatal IO error: cannot freeze gfs2 due "
			       "to recovery error.\n");
			जाओ out;
		पूर्ण अन्यथा अणु
			fs_err(sdp, "error freezing FS: %d\n", error);
		पूर्ण
		fs_err(sdp, "retrying...\n");
		msleep(1000);
	पूर्ण
	set_bit(SDF_FS_FROZEN, &sdp->sd_flags);
out:
	mutex_unlock(&sdp->sd_मुक्तze_mutex);
	वापस error;
पूर्ण

/**
 * gfs2_unमुक्तze - reallow ग_लिखोs to the fileप्रणाली
 * @sb: the VFS काष्ठाure क्रम the fileप्रणाली
 *
 */

अटल पूर्णांक gfs2_unमुक्तze(काष्ठा super_block *sb)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;

	mutex_lock(&sdp->sd_मुक्तze_mutex);
	अगर (atomic_पढ़ो(&sdp->sd_मुक्तze_state) != SFS_FROZEN ||
	    !gfs2_holder_initialized(&sdp->sd_मुक्तze_gh)) अणु
		mutex_unlock(&sdp->sd_मुक्तze_mutex);
		वापस -EINVAL;
	पूर्ण

	gfs2_मुक्तze_unlock(&sdp->sd_मुक्तze_gh);
	mutex_unlock(&sdp->sd_मुक्तze_mutex);
	वापस रुको_on_bit(&sdp->sd_flags, SDF_FS_FROZEN, TASK_INTERRUPTIBLE);
पूर्ण

/**
 * statfs_slow_fill - fill in the sg क्रम a given RG
 * @rgd: the RG
 * @sc: the sc काष्ठाure
 *
 * Returns: 0 on success, -ESTALE अगर the LVB is invalid
 */

अटल पूर्णांक statfs_slow_fill(काष्ठा gfs2_rgrpd *rgd,
			    काष्ठा gfs2_statfs_change_host *sc)
अणु
	gfs2_rgrp_verअगरy(rgd);
	sc->sc_total += rgd->rd_data;
	sc->sc_मुक्त += rgd->rd_मुक्त;
	sc->sc_dinodes += rgd->rd_dinodes;
	वापस 0;
पूर्ण

/**
 * gfs2_statfs_slow - Stat a fileप्रणाली using asynchronous locking
 * @sdp: the fileप्रणाली
 * @sc: the sc info that will be वापसed
 *
 * Any error (other than a संकेत) will cause this routine to fall back
 * to the synchronous version.
 *
 * FIXME: This really shouldn't busy रुको like this.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_statfs_slow(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_statfs_change_host *sc)
अणु
	काष्ठा gfs2_rgrpd *rgd_next;
	काष्ठा gfs2_holder *gha, *gh;
	अचिन्हित पूर्णांक slots = 64;
	अचिन्हित पूर्णांक x;
	पूर्णांक करोne;
	पूर्णांक error = 0, err;

	स_रखो(sc, 0, माप(काष्ठा gfs2_statfs_change_host));
	gha = kदो_स्मृति_array(slots, माप(काष्ठा gfs2_holder), GFP_KERNEL);
	अगर (!gha)
		वापस -ENOMEM;
	क्रम (x = 0; x < slots; x++)
		gfs2_holder_mark_uninitialized(gha + x);

	rgd_next = gfs2_rgrpd_get_first(sdp);

	क्रम (;;) अणु
		करोne = 1;

		क्रम (x = 0; x < slots; x++) अणु
			gh = gha + x;

			अगर (gfs2_holder_initialized(gh) && gfs2_glock_poll(gh)) अणु
				err = gfs2_glock_रुको(gh);
				अगर (err) अणु
					gfs2_holder_uninit(gh);
					error = err;
				पूर्ण अन्यथा अणु
					अगर (!error) अणु
						काष्ठा gfs2_rgrpd *rgd =
							gfs2_glock2rgrp(gh->gh_gl);

						error = statfs_slow_fill(rgd, sc);
					पूर्ण
					gfs2_glock_dq_uninit(gh);
				पूर्ण
			पूर्ण

			अगर (gfs2_holder_initialized(gh))
				करोne = 0;
			अन्यथा अगर (rgd_next && !error) अणु
				error = gfs2_glock_nq_init(rgd_next->rd_gl,
							   LM_ST_SHARED,
							   GL_ASYNC,
							   gh);
				rgd_next = gfs2_rgrpd_get_next(rgd_next);
				करोne = 0;
			पूर्ण

			अगर (संकेत_pending(current))
				error = -ERESTARTSYS;
		पूर्ण

		अगर (करोne)
			अवरोध;

		yield();
	पूर्ण

	kमुक्त(gha);
	वापस error;
पूर्ण

/**
 * gfs2_statfs_i - Do a statfs
 * @sdp: the fileप्रणाली
 * @sc: the sc काष्ठाure
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_statfs_i(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_statfs_change_host *sc)
अणु
	काष्ठा gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	काष्ठा gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;

	spin_lock(&sdp->sd_statfs_spin);

	*sc = *m_sc;
	sc->sc_total += l_sc->sc_total;
	sc->sc_मुक्त += l_sc->sc_मुक्त;
	sc->sc_dinodes += l_sc->sc_dinodes;

	spin_unlock(&sdp->sd_statfs_spin);

	अगर (sc->sc_मुक्त < 0)
		sc->sc_मुक्त = 0;
	अगर (sc->sc_मुक्त > sc->sc_total)
		sc->sc_मुक्त = sc->sc_total;
	अगर (sc->sc_dinodes < 0)
		sc->sc_dinodes = 0;

	वापस 0;
पूर्ण

/**
 * gfs2_statfs - Gather and वापस stats about the fileप्रणाली
 * @dentry: The name of the link
 * @buf: The buffer
 *
 * Returns: 0 on success or error code
 */

अटल पूर्णांक gfs2_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा gfs2_statfs_change_host sc;
	पूर्णांक error;

	error = gfs2_rindex_update(sdp);
	अगर (error)
		वापस error;

	अगर (gfs2_tune_get(sdp, gt_statfs_slow))
		error = gfs2_statfs_slow(sdp, &sc);
	अन्यथा
		error = gfs2_statfs_i(sdp, &sc);

	अगर (error)
		वापस error;

	buf->f_type = GFS2_MAGIC;
	buf->f_bsize = sdp->sd_sb.sb_bsize;
	buf->f_blocks = sc.sc_total;
	buf->f_bमुक्त = sc.sc_मुक्त;
	buf->f_bavail = sc.sc_मुक्त;
	buf->f_files = sc.sc_dinodes + sc.sc_मुक्त;
	buf->f_fमुक्त = sc.sc_मुक्त;
	buf->f_namelen = GFS2_FNAMESIZE;

	वापस 0;
पूर्ण

/**
 * gfs2_drop_inode - Drop an inode (test क्रम remote unlink)
 * @inode: The inode to drop
 *
 * If we've received a callback on an iopen lock then it's because a
 * remote node tried to deallocate the inode but failed due to this node
 * still having the inode खोलो. Here we mark the link count zero
 * since we know that it must have reached zero अगर the GLF_DEMOTE flag
 * is set on the iखोलो glock. If we didn't करो a disk पढ़ो since the
 * remote node हटाओd the final link then we might otherwise miss
 * this event. This check ensures that this node will deallocate the
 * inode's blocks, or alternatively pass the baton on to another
 * node क्रम later deallocation.
 */

अटल पूर्णांक gfs2_drop_inode(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);

	अगर (!test_bit(GIF_FREE_VFS_INODE, &ip->i_flags) &&
	    inode->i_nlink &&
	    gfs2_holder_initialized(&ip->i_iखोलो_gh)) अणु
		काष्ठा gfs2_glock *gl = ip->i_iखोलो_gh.gh_gl;
		अगर (test_bit(GLF_DEMOTE, &gl->gl_flags))
			clear_nlink(inode);
	पूर्ण

	/*
	 * When under memory pressure when an inode's link count has dropped to
	 * zero, defer deleting the inode to the delete workqueue.  This aव्योमs
	 * calling पूर्णांकo DLM under memory pressure, which can deadlock.
	 */
	अगर (!inode->i_nlink &&
	    unlikely(current->flags & PF_MEMALLOC) &&
	    gfs2_holder_initialized(&ip->i_iखोलो_gh)) अणु
		काष्ठा gfs2_glock *gl = ip->i_iखोलो_gh.gh_gl;

		gfs2_glock_hold(gl);
		अगर (!gfs2_queue_delete_work(gl, 0))
			gfs2_glock_queue_put(gl);
		वापस false;
	पूर्ण

	वापस generic_drop_inode(inode);
पूर्ण

अटल पूर्णांक is_ancestor(स्थिर काष्ठा dentry *d1, स्थिर काष्ठा dentry *d2)
अणु
	करो अणु
		अगर (d1 == d2)
			वापस 1;
		d1 = d1->d_parent;
	पूर्ण जबतक (!IS_ROOT(d1));
	वापस 0;
पूर्ण

/**
 * gfs2_show_options - Show mount options क्रम /proc/mounts
 * @s: seq_file काष्ठाure
 * @root: root of this (sub)tree
 *
 * Returns: 0 on success or error code
 */

अटल पूर्णांक gfs2_show_options(काष्ठा seq_file *s, काष्ठा dentry *root)
अणु
	काष्ठा gfs2_sbd *sdp = root->d_sb->s_fs_info;
	काष्ठा gfs2_args *args = &sdp->sd_args;
	पूर्णांक val;

	अगर (is_ancestor(root, sdp->sd_master_dir))
		seq_माला_दो(s, ",meta");
	अगर (args->ar_lockproto[0])
		seq_show_option(s, "lockproto", args->ar_lockproto);
	अगर (args->ar_locktable[0])
		seq_show_option(s, "locktable", args->ar_locktable);
	अगर (args->ar_hostdata[0])
		seq_show_option(s, "hostdata", args->ar_hostdata);
	अगर (args->ar_spectator)
		seq_माला_दो(s, ",spectator");
	अगर (args->ar_localflocks)
		seq_माला_दो(s, ",localflocks");
	अगर (args->ar_debug)
		seq_माला_दो(s, ",debug");
	अगर (args->ar_posix_acl)
		seq_माला_दो(s, ",acl");
	अगर (args->ar_quota != GFS2_QUOTA_DEFAULT) अणु
		अक्षर *state;
		चयन (args->ar_quota) अणु
		हाल GFS2_QUOTA_OFF:
			state = "off";
			अवरोध;
		हाल GFS2_QUOTA_ACCOUNT:
			state = "account";
			अवरोध;
		हाल GFS2_QUOTA_ON:
			state = "on";
			अवरोध;
		शेष:
			state = "unknown";
			अवरोध;
		पूर्ण
		seq_म_लिखो(s, ",quota=%s", state);
	पूर्ण
	अगर (args->ar_suiddir)
		seq_माला_दो(s, ",suiddir");
	अगर (args->ar_data != GFS2_DATA_DEFAULT) अणु
		अक्षर *state;
		चयन (args->ar_data) अणु
		हाल GFS2_DATA_WRITEBACK:
			state = "writeback";
			अवरोध;
		हाल GFS2_DATA_ORDERED:
			state = "ordered";
			अवरोध;
		शेष:
			state = "unknown";
			अवरोध;
		पूर्ण
		seq_म_लिखो(s, ",data=%s", state);
	पूर्ण
	अगर (args->ar_discard)
		seq_माला_दो(s, ",discard");
	val = sdp->sd_tune.gt_logd_secs;
	अगर (val != 30)
		seq_म_लिखो(s, ",commit=%d", val);
	val = sdp->sd_tune.gt_statfs_quantum;
	अगर (val != 30)
		seq_म_लिखो(s, ",statfs_quantum=%d", val);
	अन्यथा अगर (sdp->sd_tune.gt_statfs_slow)
		seq_माला_दो(s, ",statfs_quantum=0");
	val = sdp->sd_tune.gt_quota_quantum;
	अगर (val != 60)
		seq_म_लिखो(s, ",quota_quantum=%d", val);
	अगर (args->ar_statfs_percent)
		seq_म_लिखो(s, ",statfs_percent=%d", args->ar_statfs_percent);
	अगर (args->ar_errors != GFS2_ERRORS_DEFAULT) अणु
		स्थिर अक्षर *state;

		चयन (args->ar_errors) अणु
		हाल GFS2_ERRORS_WITHDRAW:
			state = "withdraw";
			अवरोध;
		हाल GFS2_ERRORS_PANIC:
			state = "panic";
			अवरोध;
		शेष:
			state = "unknown";
			अवरोध;
		पूर्ण
		seq_म_लिखो(s, ",errors=%s", state);
	पूर्ण
	अगर (test_bit(SDF_NOBARRIERS, &sdp->sd_flags))
		seq_माला_दो(s, ",nobarrier");
	अगर (test_bit(SDF_DEMOTE, &sdp->sd_flags))
		seq_माला_दो(s, ",demote_interface_used");
	अगर (args->ar_rgrplvb)
		seq_माला_दो(s, ",rgrplvb");
	अगर (args->ar_loccookie)
		seq_माला_दो(s, ",loccookie");
	वापस 0;
पूर्ण

अटल व्योम gfs2_final_release_pages(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा inode *inode = &ip->i_inode;
	काष्ठा gfs2_glock *gl = ip->i_gl;

	truncate_inode_pages(gfs2_glock2aspace(ip->i_gl), 0);
	truncate_inode_pages(&inode->i_data, 0);

	अगर (atomic_पढ़ो(&gl->gl_revokes) == 0) अणु
		clear_bit(GLF_LFLUSH, &gl->gl_flags);
		clear_bit(GLF_सूचीTY, &gl->gl_flags);
	पूर्ण
पूर्ण

अटल पूर्णांक gfs2_dinode_dealloc(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_rgrpd *rgd;
	काष्ठा gfs2_holder gh;
	पूर्णांक error;

	अगर (gfs2_get_inode_blocks(&ip->i_inode) != 1) अणु
		gfs2_consist_inode(ip);
		वापस -EIO;
	पूर्ण

	error = gfs2_rindex_update(sdp);
	अगर (error)
		वापस error;

	error = gfs2_quota_hold(ip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	अगर (error)
		वापस error;

	rgd = gfs2_blk2rgrpd(sdp, ip->i_no_addr, 1);
	अगर (!rgd) अणु
		gfs2_consist_inode(ip);
		error = -EIO;
		जाओ out_qs;
	पूर्ण

	error = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_EXCLUSIVE,
				   LM_FLAG_NODE_SCOPE, &gh);
	अगर (error)
		जाओ out_qs;

	error = gfs2_trans_begin(sdp, RES_RG_BIT + RES_STATFS + RES_QUOTA,
				 sdp->sd_jdesc->jd_blocks);
	अगर (error)
		जाओ out_rg_gunlock;

	gfs2_मुक्त_di(rgd, ip);

	gfs2_final_release_pages(ip);

	gfs2_trans_end(sdp);

out_rg_gunlock:
	gfs2_glock_dq_uninit(&gh);
out_qs:
	gfs2_quota_unhold(ip);
	वापस error;
पूर्ण

/**
 * gfs2_glock_put_eventually
 * @gl:	The glock to put
 *
 * When under memory pressure, trigger a deferred glock put to make sure we
 * won't call पूर्णांकo DLM and deadlock.  Otherwise, put the glock directly.
 */

अटल व्योम gfs2_glock_put_eventually(काष्ठा gfs2_glock *gl)
अणु
	अगर (current->flags & PF_MEMALLOC)
		gfs2_glock_queue_put(gl);
	अन्यथा
		gfs2_glock_put(gl);
पूर्ण

अटल bool gfs2_upgrade_iखोलो_glock(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_holder *gh = &ip->i_iखोलो_gh;
	दीर्घ समयout = 5 * HZ;
	पूर्णांक error;

	gh->gh_flags |= GL_NOCACHE;
	gfs2_glock_dq_रुको(gh);

	/*
	 * If there are no other lock holders, we'll get the lock immediately.
	 * Otherwise, the other nodes holding the lock will be notअगरied about
	 * our locking request.  If they करोn't have the inode open, they'll
	 * evict the cached inode and release the lock.  Otherwise, अगर they
	 * poke the inode glock, we'll take this as an indication that they
	 * still need the iखोलो glock and that they'll take care of deleting
	 * the inode when they're करोne.  As a last resort, अगर another node
	 * keeps holding the iखोलो glock without showing any activity on the
	 * inode glock, we'll eventually समय out.
	 *
	 * Note that we're passing the LM_FLAG_TRY_1CB flag to the first
	 * locking request as an optimization to notअगरy lock holders as soon as
	 * possible.  Without that flag, they'd be notअगरied implicitly by the
	 * second locking request.
	 */

	gfs2_holder_reinit(LM_ST_EXCLUSIVE, LM_FLAG_TRY_1CB | GL_NOCACHE, gh);
	error = gfs2_glock_nq(gh);
	अगर (error != GLR_TRYFAILED)
		वापस !error;

	gfs2_holder_reinit(LM_ST_EXCLUSIVE, GL_ASYNC | GL_NOCACHE, gh);
	error = gfs2_glock_nq(gh);
	अगर (error)
		वापस false;

	समयout = रुको_event_पूर्णांकerruptible_समयout(sdp->sd_async_glock_रुको,
		!test_bit(HIF_WAIT, &gh->gh_अगरlags) ||
		test_bit(GLF_DEMOTE, &ip->i_gl->gl_flags),
		समयout);
	अगर (!test_bit(HIF_HOLDER, &gh->gh_अगरlags)) अणु
		gfs2_glock_dq(gh);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * evict_should_delete - determine whether the inode is eligible क्रम deletion
 * @inode: The inode to evict
 * @gh: The glock holder काष्ठाure
 *
 * This function determines whether the evicted inode is eligible to be deleted
 * and locks the inode glock.
 *
 * Returns: the fate of the dinode
 */
अटल क्रमागत dinode_demise evict_should_delete(काष्ठा inode *inode,
					      काष्ठा gfs2_holder *gh)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	पूर्णांक ret;

	अगर (test_bit(GIF_ALLOC_FAILED, &ip->i_flags)) अणु
		BUG_ON(!gfs2_glock_is_locked_by_me(ip->i_gl));
		जाओ should_delete;
	पूर्ण

	अगर (test_bit(GIF_DEFERRED_DELETE, &ip->i_flags))
		वापस SHOULD_DEFER_EVICTION;

	/* Deletes should never happen under memory pressure anymore.  */
	अगर (WARN_ON_ONCE(current->flags & PF_MEMALLOC))
		वापस SHOULD_DEFER_EVICTION;

	/* Must not पढ़ो inode block until block type has been verअगरied */
	ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, GL_SKIP, gh);
	अगर (unlikely(ret)) अणु
		glock_clear_object(ip->i_iखोलो_gh.gh_gl, ip);
		ip->i_iखोलो_gh.gh_flags |= GL_NOCACHE;
		gfs2_glock_dq_uninit(&ip->i_iखोलो_gh);
		वापस SHOULD_DEFER_EVICTION;
	पूर्ण

	अगर (gfs2_inode_alपढ़ोy_deleted(ip->i_gl, ip->i_no_क्रमmal_ino))
		वापस SHOULD_NOT_DELETE_DINODE;
	ret = gfs2_check_blk_type(sdp, ip->i_no_addr, GFS2_BLKST_UNLINKED);
	अगर (ret)
		वापस SHOULD_NOT_DELETE_DINODE;

	अगर (test_bit(GIF_INVALID, &ip->i_flags)) अणु
		ret = gfs2_inode_refresh(ip);
		अगर (ret)
			वापस SHOULD_NOT_DELETE_DINODE;
	पूर्ण

	/*
	 * The inode may have been recreated in the meanसमय.
	 */
	अगर (inode->i_nlink)
		वापस SHOULD_NOT_DELETE_DINODE;

should_delete:
	अगर (gfs2_holder_initialized(&ip->i_iखोलो_gh) &&
	    test_bit(HIF_HOLDER, &ip->i_iखोलो_gh.gh_अगरlags)) अणु
		अगर (!gfs2_upgrade_iखोलो_glock(inode)) अणु
			gfs2_holder_uninit(&ip->i_iखोलो_gh);
			वापस SHOULD_NOT_DELETE_DINODE;
		पूर्ण
	पूर्ण
	वापस SHOULD_DELETE_DINODE;
पूर्ण

/**
 * evict_unlinked_inode - delete the pieces of an unlinked evicted inode
 * @inode: The inode to evict
 */
अटल पूर्णांक evict_unlinked_inode(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	पूर्णांक ret;

	अगर (S_ISसूची(inode->i_mode) &&
	    (ip->i_diskflags & GFS2_DIF_EXHASH)) अणु
		ret = gfs2_dir_exhash_dealloc(ip);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (ip->i_eattr) अणु
		ret = gfs2_ea_dealloc(ip);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (!gfs2_is_stuffed(ip)) अणु
		ret = gfs2_file_dealloc(ip);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* We're about to clear the biपंचांगap क्रम the dinode, but as soon as we
	   करो, gfs2_create_inode can create another inode at the same block
	   location and try to set gl_object again. We clear gl_object here so
	   that subsequent inode creates करोn't see an old gl_object. */
	glock_clear_object(ip->i_gl, ip);
	ret = gfs2_dinode_dealloc(ip);
	gfs2_inode_remember_delete(ip->i_gl, ip->i_no_क्रमmal_ino);
out:
	वापस ret;
पूर्ण

/*
 * evict_linked_inode - evict an inode whose dinode has not been unlinked
 * @inode: The inode to evict
 */
अटल पूर्णांक evict_linked_inode(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा address_space *metamapping;
	पूर्णांक ret;

	gfs2_log_flush(sdp, ip->i_gl, GFS2_LOG_HEAD_FLUSH_NORMAL |
		       GFS2_LFC_EVICT_INODE);
	metamapping = gfs2_glock2aspace(ip->i_gl);
	अगर (test_bit(GLF_सूचीTY, &ip->i_gl->gl_flags)) अणु
		filemap_fdataग_लिखो(metamapping);
		filemap_fdataरुको(metamapping);
	पूर्ण
	ग_लिखो_inode_now(inode, 1);
	gfs2_ail_flush(ip->i_gl, 0);

	ret = gfs2_trans_begin(sdp, 0, sdp->sd_jdesc->jd_blocks);
	अगर (ret)
		वापस ret;

	/* Needs to be करोne beक्रमe glock release & also in a transaction */
	truncate_inode_pages(&inode->i_data, 0);
	truncate_inode_pages(metamapping, 0);
	gfs2_trans_end(sdp);
	वापस 0;
पूर्ण

/**
 * gfs2_evict_inode - Remove an inode from cache
 * @inode: The inode to evict
 *
 * There are three हालs to consider:
 * 1. i_nlink == 0, we are final खोलोer (and must deallocate)
 * 2. i_nlink == 0, we are not the final खोलोer (and cannot deallocate)
 * 3. i_nlink > 0
 *
 * If the fs is पढ़ो only, then we have to treat all हालs as per #3
 * since we are unable to करो any deallocation. The inode will be
 * deallocated by the next पढ़ो/ग_लिखो node to attempt an allocation
 * in the same resource group
 *
 * We have to (at the moment) hold the inodes मुख्य lock to cover
 * the gap between unlocking the shared lock on the iखोलो lock and
 * taking the exclusive lock. I'd rather करो a shared -> exclusive
 * conversion on the iखोलो lock, but we can change that later. This
 * is safe, just less efficient.
 */

अटल व्योम gfs2_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	पूर्णांक ret;

	अगर (test_bit(GIF_FREE_VFS_INODE, &ip->i_flags)) अणु
		clear_inode(inode);
		वापस;
	पूर्ण

	अगर (inode->i_nlink || sb_rकरोnly(sb))
		जाओ out;

	gfs2_holder_mark_uninitialized(&gh);
	ret = evict_should_delete(inode, &gh);
	अगर (ret == SHOULD_DEFER_EVICTION)
		जाओ out;
	अगर (ret == SHOULD_DELETE_DINODE)
		ret = evict_unlinked_inode(inode);
	अन्यथा
		ret = evict_linked_inode(inode);

	अगर (gfs2_rs_active(&ip->i_res))
		gfs2_rs_deltree(&ip->i_res);

	अगर (gfs2_holder_initialized(&gh)) अणु
		glock_clear_object(ip->i_gl, ip);
		gfs2_glock_dq_uninit(&gh);
	पूर्ण
	अगर (ret && ret != GLR_TRYFAILED && ret != -EROFS)
		fs_warn(sdp, "gfs2_evict_inode: %d\n", ret);
out:
	truncate_inode_pages_final(&inode->i_data);
	अगर (ip->i_qadata)
		gfs2_निश्चित_warn(sdp, ip->i_qadata->qa_ref == 0);
	gfs2_rs_delete(ip, शून्य);
	gfs2_ordered_del_inode(ip);
	clear_inode(inode);
	gfs2_dir_hash_inval(ip);
	अगर (ip->i_gl) अणु
		glock_clear_object(ip->i_gl, ip);
		रुको_on_bit_io(&ip->i_flags, GIF_GLOP_PENDING, TASK_UNINTERRUPTIBLE);
		gfs2_glock_add_to_lru(ip->i_gl);
		gfs2_glock_put_eventually(ip->i_gl);
		ip->i_gl = शून्य;
	पूर्ण
	अगर (gfs2_holder_initialized(&ip->i_iखोलो_gh)) अणु
		काष्ठा gfs2_glock *gl = ip->i_iखोलो_gh.gh_gl;

		glock_clear_object(gl, ip);
		अगर (test_bit(HIF_HOLDER, &ip->i_iखोलो_gh.gh_अगरlags)) अणु
			ip->i_iखोलो_gh.gh_flags |= GL_NOCACHE;
			gfs2_glock_dq(&ip->i_iखोलो_gh);
		पूर्ण
		gfs2_glock_hold(gl);
		gfs2_holder_uninit(&ip->i_iखोलो_gh);
		gfs2_glock_put_eventually(gl);
	पूर्ण
पूर्ण

अटल काष्ठा inode *gfs2_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा gfs2_inode *ip;

	ip = kmem_cache_alloc(gfs2_inode_cachep, GFP_KERNEL);
	अगर (!ip)
		वापस शून्य;
	ip->i_flags = 0;
	ip->i_gl = शून्य;
	gfs2_holder_mark_uninitialized(&ip->i_iखोलो_gh);
	स_रखो(&ip->i_res, 0, माप(ip->i_res));
	RB_CLEAR_NODE(&ip->i_res.rs_node);
	ip->i_rahead = 0;
	वापस &ip->i_inode;
पूर्ण

अटल व्योम gfs2_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(gfs2_inode_cachep, GFS2_I(inode));
पूर्ण

बाह्य व्योम मुक्त_local_statfs_inodes(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा local_statfs_inode *lsi, *safe;

	/* Run through the statfs inodes list to iput and मुक्त memory */
	list_क्रम_each_entry_safe(lsi, safe, &sdp->sd_sc_inodes_list, si_list) अणु
		अगर (lsi->si_jid == sdp->sd_jdesc->jd_jid)
			sdp->sd_sc_inode = शून्य; /* beदीर्घs to this node */
		अगर (lsi->si_sc_inode)
			iput(lsi->si_sc_inode);
		list_del(&lsi->si_list);
		kमुक्त(lsi);
	पूर्ण
पूर्ण

बाह्य काष्ठा inode *find_local_statfs_inode(काष्ठा gfs2_sbd *sdp,
					     अचिन्हित पूर्णांक index)
अणु
	काष्ठा local_statfs_inode *lsi;

	/* Return the local (per node) statfs inode in the
	 * sdp->sd_sc_inodes_list corresponding to the 'index'. */
	list_क्रम_each_entry(lsi, &sdp->sd_sc_inodes_list, si_list) अणु
		अगर (lsi->si_jid == index)
			वापस lsi->si_sc_inode;
	पूर्ण
	वापस शून्य;
पूर्ण

स्थिर काष्ठा super_operations gfs2_super_ops = अणु
	.alloc_inode		= gfs2_alloc_inode,
	.मुक्त_inode		= gfs2_मुक्त_inode,
	.ग_लिखो_inode		= gfs2_ग_लिखो_inode,
	.dirty_inode		= gfs2_dirty_inode,
	.evict_inode		= gfs2_evict_inode,
	.put_super		= gfs2_put_super,
	.sync_fs		= gfs2_sync_fs,
	.मुक्तze_super		= gfs2_मुक्तze,
	.thaw_super		= gfs2_unमुक्तze,
	.statfs			= gfs2_statfs,
	.drop_inode		= gfs2_drop_inode,
	.show_options		= gfs2_show_options,
पूर्ण;

