<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/quota.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/dqblk_v1.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "quotaio_v1.h"

MODULE_AUTHOR("Jan Kara");
MODULE_DESCRIPTION("Old quota format support");
MODULE_LICENSE("GPL");

#घोषणा QUOTABLOCK_BITS 10
#घोषणा QUOTABLOCK_SIZE (1 << QUOTABLOCK_BITS)

अटल अंतरभूत qमाप_प्रकार v1_stoqb(qमाप_प्रकार space)
अणु
	वापस (space + QUOTABLOCK_SIZE - 1) >> QUOTABLOCK_BITS;
पूर्ण

अटल अंतरभूत qमाप_प्रकार v1_qbtos(qमाप_प्रकार blocks)
अणु
	वापस blocks << QUOTABLOCK_BITS;
पूर्ण

अटल व्योम v1_disk2mem_dqblk(काष्ठा mem_dqblk *m, काष्ठा v1_disk_dqblk *d)
अणु
	m->dqb_ihardlimit = d->dqb_ihardlimit;
	m->dqb_isoftlimit = d->dqb_isoftlimit;
	m->dqb_curinodes = d->dqb_curinodes;
	m->dqb_bhardlimit = v1_qbtos(d->dqb_bhardlimit);
	m->dqb_bsoftlimit = v1_qbtos(d->dqb_bsoftlimit);
	m->dqb_curspace = v1_qbtos(d->dqb_curblocks);
	m->dqb_iसमय = d->dqb_iसमय;
	m->dqb_bसमय = d->dqb_bसमय;
पूर्ण

अटल व्योम v1_mem2disk_dqblk(काष्ठा v1_disk_dqblk *d, काष्ठा mem_dqblk *m)
अणु
	d->dqb_ihardlimit = m->dqb_ihardlimit;
	d->dqb_isoftlimit = m->dqb_isoftlimit;
	d->dqb_curinodes = m->dqb_curinodes;
	d->dqb_bhardlimit = v1_stoqb(m->dqb_bhardlimit);
	d->dqb_bsoftlimit = v1_stoqb(m->dqb_bsoftlimit);
	d->dqb_curblocks = v1_stoqb(m->dqb_curspace);
	d->dqb_iसमय = m->dqb_iसमय;
	d->dqb_bसमय = m->dqb_bसमय;
पूर्ण

अटल पूर्णांक v1_पढ़ो_dqblk(काष्ठा dquot *dquot)
अणु
	पूर्णांक type = dquot->dq_id.type;
	काष्ठा v1_disk_dqblk dqblk;
	काष्ठा quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	अगर (!dqopt->files[type])
		वापस -EINVAL;

	/* Set काष्ठाure to 0s in हाल पढ़ो fails/is after end of file */
	स_रखो(&dqblk, 0, माप(काष्ठा v1_disk_dqblk));
	dquot->dq_sb->s_op->quota_पढ़ो(dquot->dq_sb, type, (अक्षर *)&dqblk,
			माप(काष्ठा v1_disk_dqblk),
			v1_dqoff(from_kqid(&init_user_ns, dquot->dq_id)));

	v1_disk2mem_dqblk(&dquot->dq_dqb, &dqblk);
	अगर (dquot->dq_dqb.dqb_bhardlimit == 0 &&
	    dquot->dq_dqb.dqb_bsoftlimit == 0 &&
	    dquot->dq_dqb.dqb_ihardlimit == 0 &&
	    dquot->dq_dqb.dqb_isoftlimit == 0)
		set_bit(DQ_FAKE_B, &dquot->dq_flags);
	dqstats_inc(DQST_READS);

	वापस 0;
पूर्ण

अटल पूर्णांक v1_commit_dqblk(काष्ठा dquot *dquot)
अणु
	लघु type = dquot->dq_id.type;
	sमाप_प्रकार ret;
	काष्ठा v1_disk_dqblk dqblk;

	v1_mem2disk_dqblk(&dqblk, &dquot->dq_dqb);
	अगर (((type == USRQUOTA) && uid_eq(dquot->dq_id.uid, GLOBAL_ROOT_UID)) ||
	    ((type == GRPQUOTA) && gid_eq(dquot->dq_id.gid, GLOBAL_ROOT_GID))) अणु
		dqblk.dqb_bसमय =
			sb_dqopt(dquot->dq_sb)->info[type].dqi_bgrace;
		dqblk.dqb_iसमय =
			sb_dqopt(dquot->dq_sb)->info[type].dqi_igrace;
	पूर्ण
	ret = 0;
	अगर (sb_dqopt(dquot->dq_sb)->files[type])
		ret = dquot->dq_sb->s_op->quota_ग_लिखो(dquot->dq_sb, type,
			(अक्षर *)&dqblk, माप(काष्ठा v1_disk_dqblk),
			v1_dqoff(from_kqid(&init_user_ns, dquot->dq_id)));
	अगर (ret != माप(काष्ठा v1_disk_dqblk)) अणु
		quota_error(dquot->dq_sb, "dquota write failed");
		अगर (ret >= 0)
			ret = -EIO;
		जाओ out;
	पूर्ण
	ret = 0;

out:
	dqstats_inc(DQST_WRITES);

	वापस ret;
पूर्ण

/* Magics of new quota क्रमmat */
#घोषणा V2_INITQMAGICS अणु\
	0xd9c01f11,     /* USRQUOTA */\
	0xd9c01927      /* GRPQUOTA */\
पूर्ण

/* Header of new quota क्रमmat */
काष्ठा v2_disk_dqheader अणु
	__le32 dqh_magic;        /* Magic number identअगरying file */
	__le32 dqh_version;      /* File version */
पूर्ण;

अटल पूर्णांक v1_check_quota_file(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	uदीर्घ blocks;
	माप_प्रकार off;
	काष्ठा v2_disk_dqheader dqhead;
	sमाप_प्रकार size;
	loff_t isize;
	अटल स्थिर uपूर्णांक quota_magics[] = V2_INITQMAGICS;

	isize = i_size_पढ़ो(inode);
	अगर (!isize)
		वापस 0;
	blocks = isize >> BLOCK_SIZE_BITS;
	off = isize & (BLOCK_SIZE - 1);
	अगर ((blocks % माप(काष्ठा v1_disk_dqblk) * BLOCK_SIZE + off) %
	    माप(काष्ठा v1_disk_dqblk))
		वापस 0;
	/* Doublecheck whether we didn't get file with new क्रमmat - with old
	 * quotactl() this could happen */
	size = sb->s_op->quota_पढ़ो(sb, type, (अक्षर *)&dqhead,
				    माप(काष्ठा v2_disk_dqheader), 0);
	अगर (size != माप(काष्ठा v2_disk_dqheader))
		वापस 1;	/* Probably not new क्रमmat */
	अगर (le32_to_cpu(dqhead.dqh_magic) != quota_magics[type])
		वापस 1;	/* Definitely not new क्रमmat */
	prपूर्णांकk(KERN_INFO
	       "VFS: %s: Refusing to turn on old quota format on given file."
	       " It probably contains newer quota format.\n", sb->s_id);
        वापस 0;		/* Seems like a new क्रमmat file -> refuse it */
पूर्ण

अटल पूर्णांक v1_पढ़ो_file_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	काष्ठा v1_disk_dqblk dqblk;
	पूर्णांक ret;

	करोwn_पढ़ो(&dqopt->dqio_sem);
	ret = sb->s_op->quota_पढ़ो(sb, type, (अक्षर *)&dqblk,
				माप(काष्ठा v1_disk_dqblk), v1_dqoff(0));
	अगर (ret != माप(काष्ठा v1_disk_dqblk)) अणु
		अगर (ret >= 0)
			ret = -EIO;
		जाओ out;
	पूर्ण
	ret = 0;
	/* limits are stored as अचिन्हित 32-bit data */
	dqopt->info[type].dqi_max_spc_limit = 0xffffffffULL << QUOTABLOCK_BITS;
	dqopt->info[type].dqi_max_ino_limit = 0xffffffff;
	dqopt->info[type].dqi_igrace =
			dqblk.dqb_iसमय ? dqblk.dqb_iसमय : MAX_IQ_TIME;
	dqopt->info[type].dqi_bgrace =
			dqblk.dqb_bसमय ? dqblk.dqb_bसमय : MAX_DQ_TIME;
out:
	up_पढ़ो(&dqopt->dqio_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक v1_ग_लिखो_file_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	काष्ठा v1_disk_dqblk dqblk;
	पूर्णांक ret;

	करोwn_ग_लिखो(&dqopt->dqio_sem);
	ret = sb->s_op->quota_पढ़ो(sb, type, (अक्षर *)&dqblk,
				माप(काष्ठा v1_disk_dqblk), v1_dqoff(0));
	अगर (ret != माप(काष्ठा v1_disk_dqblk)) अणु
		अगर (ret >= 0)
			ret = -EIO;
		जाओ out;
	पूर्ण
	spin_lock(&dq_data_lock);
	dqopt->info[type].dqi_flags &= ~DQF_INFO_सूचीTY;
	dqblk.dqb_iसमय = dqopt->info[type].dqi_igrace;
	dqblk.dqb_bसमय = dqopt->info[type].dqi_bgrace;
	spin_unlock(&dq_data_lock);
	ret = sb->s_op->quota_ग_लिखो(sb, type, (अक्षर *)&dqblk,
	      माप(काष्ठा v1_disk_dqblk), v1_dqoff(0));
	अगर (ret == माप(काष्ठा v1_disk_dqblk))
		ret = 0;
	अन्यथा अगर (ret > 0)
		ret = -EIO;
out:
	up_ग_लिखो(&dqopt->dqio_sem);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा quota_क्रमmat_ops v1_क्रमmat_ops = अणु
	.check_quota_file	= v1_check_quota_file,
	.पढ़ो_file_info		= v1_पढ़ो_file_info,
	.ग_लिखो_file_info	= v1_ग_लिखो_file_info,
	.पढ़ो_dqblk		= v1_पढ़ो_dqblk,
	.commit_dqblk		= v1_commit_dqblk,
पूर्ण;

अटल काष्ठा quota_क्रमmat_type v1_quota_क्रमmat = अणु
	.qf_fmt_id	= QFMT_VFS_OLD,
	.qf_ops		= &v1_क्रमmat_ops,
	.qf_owner	= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init init_v1_quota_क्रमmat(व्योम)
अणु
        वापस रेजिस्टर_quota_क्रमmat(&v1_quota_क्रमmat);
पूर्ण

अटल व्योम __निकास निकास_v1_quota_क्रमmat(व्योम)
अणु
        unरेजिस्टर_quota_क्रमmat(&v1_quota_क्रमmat);
पूर्ण

module_init(init_v1_quota_क्रमmat);
module_निकास(निकास_v1_quota_क्रमmat);

