<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	vfsv0 quota IO operations on file
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/dqblk_v2.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/quotaops.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "quota_tree.h"
#समावेश "quotaio_v2.h"

MODULE_AUTHOR("Jan Kara");
MODULE_DESCRIPTION("Quota format v2 support");
MODULE_LICENSE("GPL");

अटल व्योम v2r0_mem2diskdqb(व्योम *dp, काष्ठा dquot *dquot);
अटल व्योम v2r0_disk2memdqb(काष्ठा dquot *dquot, व्योम *dp);
अटल पूर्णांक v2r0_is_id(व्योम *dp, काष्ठा dquot *dquot);
अटल व्योम v2r1_mem2diskdqb(व्योम *dp, काष्ठा dquot *dquot);
अटल व्योम v2r1_disk2memdqb(काष्ठा dquot *dquot, व्योम *dp);
अटल पूर्णांक v2r1_is_id(व्योम *dp, काष्ठा dquot *dquot);

अटल स्थिर काष्ठा qtree_fmt_operations v2r0_qtree_ops = अणु
	.mem2disk_dqblk = v2r0_mem2diskdqb,
	.disk2mem_dqblk = v2r0_disk2memdqb,
	.is_id = v2r0_is_id,
पूर्ण;

अटल स्थिर काष्ठा qtree_fmt_operations v2r1_qtree_ops = अणु
	.mem2disk_dqblk = v2r1_mem2diskdqb,
	.disk2mem_dqblk = v2r1_disk2memdqb,
	.is_id = v2r1_is_id,
पूर्ण;

#घोषणा QUOTABLOCK_BITS 10
#घोषणा QUOTABLOCK_SIZE (1 << QUOTABLOCK_BITS)

अटल अंतरभूत qमाप_प्रकार v2_stoqb(qमाप_प्रकार space)
अणु
	वापस (space + QUOTABLOCK_SIZE - 1) >> QUOTABLOCK_BITS;
पूर्ण

अटल अंतरभूत qमाप_प्रकार v2_qbtos(qमाप_प्रकार blocks)
अणु
	वापस blocks << QUOTABLOCK_BITS;
पूर्ण

अटल पूर्णांक v2_पढ़ो_header(काष्ठा super_block *sb, पूर्णांक type,
			  काष्ठा v2_disk_dqheader *dqhead)
अणु
	sमाप_प्रकार size;

	size = sb->s_op->quota_पढ़ो(sb, type, (अक्षर *)dqhead,
				    माप(काष्ठा v2_disk_dqheader), 0);
	अगर (size != माप(काष्ठा v2_disk_dqheader)) अणु
		quota_error(sb, "Failed header read: expected=%zd got=%zd",
			    माप(काष्ठा v2_disk_dqheader), size);
		अगर (size < 0)
			वापस size;
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Check whether given file is really vfsv0 quotafile */
अटल पूर्णांक v2_check_quota_file(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा v2_disk_dqheader dqhead;
	अटल स्थिर uपूर्णांक quota_magics[] = V2_INITQMAGICS;
	अटल स्थिर uपूर्णांक quota_versions[] = V2_INITQVERSIONS;

	अगर (v2_पढ़ो_header(sb, type, &dqhead))
		वापस 0;
	अगर (le32_to_cpu(dqhead.dqh_magic) != quota_magics[type] ||
	    le32_to_cpu(dqhead.dqh_version) > quota_versions[type])
		वापस 0;
	वापस 1;
पूर्ण

/* Read inक्रमmation header from quota file */
अटल पूर्णांक v2_पढ़ो_file_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा v2_disk_dqinfo dinfo;
	काष्ठा v2_disk_dqheader dqhead;
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	काष्ठा mem_dqinfo *info = &dqopt->info[type];
	काष्ठा qtree_mem_dqinfo *qinfo;
	sमाप_प्रकार size;
	अचिन्हित पूर्णांक version;
	पूर्णांक ret;

	करोwn_पढ़ो(&dqopt->dqio_sem);
	ret = v2_पढ़ो_header(sb, type, &dqhead);
	अगर (ret < 0)
		जाओ out;
	version = le32_to_cpu(dqhead.dqh_version);
	अगर ((info->dqi_fmt_id == QFMT_VFS_V0 && version != 0) ||
	    (info->dqi_fmt_id == QFMT_VFS_V1 && version != 1)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	size = sb->s_op->quota_पढ़ो(sb, type, (अक्षर *)&dinfo,
	       माप(काष्ठा v2_disk_dqinfo), V2_DQINFOOFF);
	अगर (size != माप(काष्ठा v2_disk_dqinfo)) अणु
		quota_error(sb, "Can't read info structure");
		अगर (size < 0)
			ret = size;
		अन्यथा
			ret = -EIO;
		जाओ out;
	पूर्ण
	info->dqi_priv = kदो_स्मृति(माप(काष्ठा qtree_mem_dqinfo), GFP_NOFS);
	अगर (!info->dqi_priv) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	qinfo = info->dqi_priv;
	अगर (version == 0) अणु
		/* limits are stored as अचिन्हित 32-bit data */
		info->dqi_max_spc_limit = 0xffffffffLL << QUOTABLOCK_BITS;
		info->dqi_max_ino_limit = 0xffffffff;
	पूर्ण अन्यथा अणु
		/*
		 * Used space is stored as अचिन्हित 64-bit value in bytes but
		 * quota core supports only चिन्हित 64-bit values so use that
		 * as a limit
		 */
		info->dqi_max_spc_limit = 0x7fffffffffffffffLL; /* 2^63-1 */
		info->dqi_max_ino_limit = 0x7fffffffffffffffLL;
	पूर्ण
	info->dqi_bgrace = le32_to_cpu(dinfo.dqi_bgrace);
	info->dqi_igrace = le32_to_cpu(dinfo.dqi_igrace);
	/* No flags currently supported */
	info->dqi_flags = 0;
	qinfo->dqi_sb = sb;
	qinfo->dqi_type = type;
	qinfo->dqi_blocks = le32_to_cpu(dinfo.dqi_blocks);
	qinfo->dqi_मुक्त_blk = le32_to_cpu(dinfo.dqi_मुक्त_blk);
	qinfo->dqi_मुक्त_entry = le32_to_cpu(dinfo.dqi_मुक्त_entry);
	qinfo->dqi_blocksize_bits = V2_DQBLKSIZE_BITS;
	qinfo->dqi_usable_bs = 1 << V2_DQBLKSIZE_BITS;
	qinfo->dqi_qtree_depth = qtree_depth(qinfo);
	अगर (version == 0) अणु
		qinfo->dqi_entry_size = माप(काष्ठा v2r0_disk_dqblk);
		qinfo->dqi_ops = &v2r0_qtree_ops;
	पूर्ण अन्यथा अणु
		qinfo->dqi_entry_size = माप(काष्ठा v2r1_disk_dqblk);
		qinfo->dqi_ops = &v2r1_qtree_ops;
	पूर्ण
	ret = -EUCLEAN;
	/* Some sanity checks of the पढ़ो headers... */
	अगर ((loff_t)qinfo->dqi_blocks << qinfo->dqi_blocksize_bits >
	    i_size_पढ़ो(sb_dqopt(sb)->files[type])) अणु
		quota_error(sb, "Number of blocks too big for quota file size (%llu > %llu).",
		    (loff_t)qinfo->dqi_blocks << qinfo->dqi_blocksize_bits,
		    i_size_पढ़ो(sb_dqopt(sb)->files[type]));
		जाओ out_मुक्त;
	पूर्ण
	अगर (qinfo->dqi_मुक्त_blk >= qinfo->dqi_blocks) अणु
		quota_error(sb, "Free block number too big (%u >= %u).",
			    qinfo->dqi_मुक्त_blk, qinfo->dqi_blocks);
		जाओ out_मुक्त;
	पूर्ण
	अगर (qinfo->dqi_मुक्त_entry >= qinfo->dqi_blocks) अणु
		quota_error(sb, "Block with free entry too big (%u >= %u).",
			    qinfo->dqi_मुक्त_entry, qinfo->dqi_blocks);
		जाओ out_मुक्त;
	पूर्ण
	ret = 0;
out_मुक्त:
	अगर (ret) अणु
		kमुक्त(info->dqi_priv);
		info->dqi_priv = शून्य;
	पूर्ण
out:
	up_पढ़ो(&dqopt->dqio_sem);
	वापस ret;
पूर्ण

/* Write inक्रमmation header to quota file */
अटल पूर्णांक v2_ग_लिखो_file_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा v2_disk_dqinfo dinfo;
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	काष्ठा mem_dqinfo *info = &dqopt->info[type];
	काष्ठा qtree_mem_dqinfo *qinfo = info->dqi_priv;
	sमाप_प्रकार size;

	करोwn_ग_लिखो(&dqopt->dqio_sem);
	spin_lock(&dq_data_lock);
	info->dqi_flags &= ~DQF_INFO_सूचीTY;
	dinfo.dqi_bgrace = cpu_to_le32(info->dqi_bgrace);
	dinfo.dqi_igrace = cpu_to_le32(info->dqi_igrace);
	/* No flags currently supported */
	dinfo.dqi_flags = cpu_to_le32(0);
	spin_unlock(&dq_data_lock);
	dinfo.dqi_blocks = cpu_to_le32(qinfo->dqi_blocks);
	dinfo.dqi_मुक्त_blk = cpu_to_le32(qinfo->dqi_मुक्त_blk);
	dinfo.dqi_मुक्त_entry = cpu_to_le32(qinfo->dqi_मुक्त_entry);
	size = sb->s_op->quota_ग_लिखो(sb, type, (अक्षर *)&dinfo,
	       माप(काष्ठा v2_disk_dqinfo), V2_DQINFOOFF);
	up_ग_लिखो(&dqopt->dqio_sem);
	अगर (size != माप(काष्ठा v2_disk_dqinfo)) अणु
		quota_error(sb, "Can't write info structure");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम v2r0_disk2memdqb(काष्ठा dquot *dquot, व्योम *dp)
अणु
	काष्ठा v2r0_disk_dqblk *d = dp, empty;
	काष्ठा mem_dqblk *m = &dquot->dq_dqb;

	m->dqb_ihardlimit = le32_to_cpu(d->dqb_ihardlimit);
	m->dqb_isoftlimit = le32_to_cpu(d->dqb_isoftlimit);
	m->dqb_curinodes = le32_to_cpu(d->dqb_curinodes);
	m->dqb_iसमय = le64_to_cpu(d->dqb_iसमय);
	m->dqb_bhardlimit = v2_qbtos(le32_to_cpu(d->dqb_bhardlimit));
	m->dqb_bsoftlimit = v2_qbtos(le32_to_cpu(d->dqb_bsoftlimit));
	m->dqb_curspace = le64_to_cpu(d->dqb_curspace);
	m->dqb_bसमय = le64_to_cpu(d->dqb_bसमय);
	/* We need to escape back all-zero काष्ठाure */
	स_रखो(&empty, 0, माप(काष्ठा v2r0_disk_dqblk));
	empty.dqb_iसमय = cpu_to_le64(1);
	अगर (!स_भेद(&empty, dp, माप(काष्ठा v2r0_disk_dqblk)))
		m->dqb_iसमय = 0;
पूर्ण

अटल व्योम v2r0_mem2diskdqb(व्योम *dp, काष्ठा dquot *dquot)
अणु
	काष्ठा v2r0_disk_dqblk *d = dp;
	काष्ठा mem_dqblk *m = &dquot->dq_dqb;
	काष्ठा qtree_mem_dqinfo *info =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv;

	d->dqb_ihardlimit = cpu_to_le32(m->dqb_ihardlimit);
	d->dqb_isoftlimit = cpu_to_le32(m->dqb_isoftlimit);
	d->dqb_curinodes = cpu_to_le32(m->dqb_curinodes);
	d->dqb_iसमय = cpu_to_le64(m->dqb_iसमय);
	d->dqb_bhardlimit = cpu_to_le32(v2_stoqb(m->dqb_bhardlimit));
	d->dqb_bsoftlimit = cpu_to_le32(v2_stoqb(m->dqb_bsoftlimit));
	d->dqb_curspace = cpu_to_le64(m->dqb_curspace);
	d->dqb_bसमय = cpu_to_le64(m->dqb_bसमय);
	d->dqb_id = cpu_to_le32(from_kqid(&init_user_ns, dquot->dq_id));
	अगर (qtree_entry_unused(info, dp))
		d->dqb_iसमय = cpu_to_le64(1);
पूर्ण

अटल पूर्णांक v2r0_is_id(व्योम *dp, काष्ठा dquot *dquot)
अणु
	काष्ठा v2r0_disk_dqblk *d = dp;
	काष्ठा qtree_mem_dqinfo *info =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv;

	अगर (qtree_entry_unused(info, dp))
		वापस 0;
	वापस qid_eq(make_kqid(&init_user_ns, dquot->dq_id.type,
				le32_to_cpu(d->dqb_id)),
		      dquot->dq_id);
पूर्ण

अटल व्योम v2r1_disk2memdqb(काष्ठा dquot *dquot, व्योम *dp)
अणु
	काष्ठा v2r1_disk_dqblk *d = dp, empty;
	काष्ठा mem_dqblk *m = &dquot->dq_dqb;

	m->dqb_ihardlimit = le64_to_cpu(d->dqb_ihardlimit);
	m->dqb_isoftlimit = le64_to_cpu(d->dqb_isoftlimit);
	m->dqb_curinodes = le64_to_cpu(d->dqb_curinodes);
	m->dqb_iसमय = le64_to_cpu(d->dqb_iसमय);
	m->dqb_bhardlimit = v2_qbtos(le64_to_cpu(d->dqb_bhardlimit));
	m->dqb_bsoftlimit = v2_qbtos(le64_to_cpu(d->dqb_bsoftlimit));
	m->dqb_curspace = le64_to_cpu(d->dqb_curspace);
	m->dqb_bसमय = le64_to_cpu(d->dqb_bसमय);
	/* We need to escape back all-zero काष्ठाure */
	स_रखो(&empty, 0, माप(काष्ठा v2r1_disk_dqblk));
	empty.dqb_iसमय = cpu_to_le64(1);
	अगर (!स_भेद(&empty, dp, माप(काष्ठा v2r1_disk_dqblk)))
		m->dqb_iसमय = 0;
पूर्ण

अटल व्योम v2r1_mem2diskdqb(व्योम *dp, काष्ठा dquot *dquot)
अणु
	काष्ठा v2r1_disk_dqblk *d = dp;
	काष्ठा mem_dqblk *m = &dquot->dq_dqb;
	काष्ठा qtree_mem_dqinfo *info =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv;

	d->dqb_ihardlimit = cpu_to_le64(m->dqb_ihardlimit);
	d->dqb_isoftlimit = cpu_to_le64(m->dqb_isoftlimit);
	d->dqb_curinodes = cpu_to_le64(m->dqb_curinodes);
	d->dqb_iसमय = cpu_to_le64(m->dqb_iसमय);
	d->dqb_bhardlimit = cpu_to_le64(v2_stoqb(m->dqb_bhardlimit));
	d->dqb_bsoftlimit = cpu_to_le64(v2_stoqb(m->dqb_bsoftlimit));
	d->dqb_curspace = cpu_to_le64(m->dqb_curspace);
	d->dqb_bसमय = cpu_to_le64(m->dqb_bसमय);
	d->dqb_id = cpu_to_le32(from_kqid(&init_user_ns, dquot->dq_id));
	d->dqb_pad = 0;
	अगर (qtree_entry_unused(info, dp))
		d->dqb_iसमय = cpu_to_le64(1);
पूर्ण

अटल पूर्णांक v2r1_is_id(व्योम *dp, काष्ठा dquot *dquot)
अणु
	काष्ठा v2r1_disk_dqblk *d = dp;
	काष्ठा qtree_mem_dqinfo *info =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv;

	अगर (qtree_entry_unused(info, dp))
		वापस 0;
	वापस qid_eq(make_kqid(&init_user_ns, dquot->dq_id.type,
				le32_to_cpu(d->dqb_id)),
		      dquot->dq_id);
पूर्ण

अटल पूर्णांक v2_पढ़ो_dquot(काष्ठा dquot *dquot)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(dquot->dq_sb);
	पूर्णांक ret;

	करोwn_पढ़ो(&dqopt->dqio_sem);
	ret = qtree_पढ़ो_dquot(
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv,
			dquot);
	up_पढ़ो(&dqopt->dqio_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक v2_ग_लिखो_dquot(काष्ठा dquot *dquot)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(dquot->dq_sb);
	पूर्णांक ret;
	bool alloc = false;

	/*
	 * If space क्रम dquot is alपढ़ोy allocated, we करोn't need any
	 * protection as we'll only overग_लिखो the place of dquot. We are
	 * still रक्षित by concurrent ग_लिखोs of the same dquot by
	 * dquot->dq_lock.
	 */
	अगर (!dquot->dq_off) अणु
		alloc = true;
		करोwn_ग_लिखो(&dqopt->dqio_sem);
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&dqopt->dqio_sem);
	पूर्ण
	ret = qtree_ग_लिखो_dquot(
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv,
			dquot);
	अगर (alloc)
		up_ग_लिखो(&dqopt->dqio_sem);
	अन्यथा
		up_पढ़ो(&dqopt->dqio_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक v2_release_dquot(काष्ठा dquot *dquot)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(dquot->dq_sb);
	पूर्णांक ret;

	करोwn_ग_लिखो(&dqopt->dqio_sem);
	ret = qtree_release_dquot(sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv, dquot);
	up_ग_लिखो(&dqopt->dqio_sem);

	वापस ret;
पूर्ण

अटल पूर्णांक v2_मुक्त_file_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	kमुक्त(sb_dqinfo(sb, type)->dqi_priv);
	वापस 0;
पूर्ण

अटल पूर्णांक v2_get_next_id(काष्ठा super_block *sb, काष्ठा kqid *qid)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	पूर्णांक ret;

	करोwn_पढ़ो(&dqopt->dqio_sem);
	ret = qtree_get_next_id(sb_dqinfo(sb, qid->type)->dqi_priv, qid);
	up_पढ़ो(&dqopt->dqio_sem);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा quota_क्रमmat_ops v2_क्रमmat_ops = अणु
	.check_quota_file	= v2_check_quota_file,
	.पढ़ो_file_info		= v2_पढ़ो_file_info,
	.ग_लिखो_file_info	= v2_ग_लिखो_file_info,
	.मुक्त_file_info		= v2_मुक्त_file_info,
	.पढ़ो_dqblk		= v2_पढ़ो_dquot,
	.commit_dqblk		= v2_ग_लिखो_dquot,
	.release_dqblk		= v2_release_dquot,
	.get_next_id		= v2_get_next_id,
पूर्ण;

अटल काष्ठा quota_क्रमmat_type v2r0_quota_क्रमmat = अणु
	.qf_fmt_id	= QFMT_VFS_V0,
	.qf_ops		= &v2_क्रमmat_ops,
	.qf_owner	= THIS_MODULE
पूर्ण;

अटल काष्ठा quota_क्रमmat_type v2r1_quota_क्रमmat = अणु
	.qf_fmt_id	= QFMT_VFS_V1,
	.qf_ops		= &v2_क्रमmat_ops,
	.qf_owner	= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init init_v2_quota_क्रमmat(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_quota_क्रमmat(&v2r0_quota_क्रमmat);
	अगर (ret)
		वापस ret;
	वापस रेजिस्टर_quota_क्रमmat(&v2r1_quota_क्रमmat);
पूर्ण

अटल व्योम __निकास निकास_v2_quota_क्रमmat(व्योम)
अणु
	unरेजिस्टर_quota_क्रमmat(&v2r0_quota_क्रमmat);
	unरेजिस्टर_quota_क्रमmat(&v2r1_quota_क्रमmat);
पूर्ण

module_init(init_v2_quota_क्रमmat);
module_निकास(निकास_v2_quota_क्रमmat);
