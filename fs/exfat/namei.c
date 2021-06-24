<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/iversion.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/nls.h>

#समावेश "exfat_raw.h"
#समावेश "exfat_fs.h"

अटल अंतरभूत अचिन्हित दीर्घ exfat_d_version(काष्ठा dentry *dentry)
अणु
	वापस (अचिन्हित दीर्घ) dentry->d_fsdata;
पूर्ण

अटल अंतरभूत व्योम exfat_d_version_set(काष्ठा dentry *dentry,
		अचिन्हित दीर्घ version)
अणु
	dentry->d_fsdata = (व्योम *) version;
पूर्ण

/*
 * If new entry was created in the parent, it could create the 8.3 alias (the
 * लघुname of logname).  So, the parent may have the negative-dentry which
 * matches the created 8.3 alias.
 *
 * If it happened, the negative dentry isn't actually negative anymore.  So,
 * drop it.
 */
अटल पूर्णांक exfat_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	/*
	 * This is not negative dentry. Always valid.
	 *
	 * Note, नाम() to existing directory entry will have ->d_inode, and
	 * will use existing name which isn't specअगरied name by user.
	 *
	 * We may be able to drop this positive dentry here. But dropping
	 * positive dentry isn't good idea. So it's unsupported like
	 * नाम("filename", "FILENAME") क्रम now.
	 */
	अगर (d_really_is_positive(dentry))
		वापस 1;

	/*
	 * Drop the negative dentry, in order to make sure to use the हाल
	 * sensitive name which is specअगरied by user अगर this is क्रम creation.
	 */
	अगर (flags & (LOOKUP_CREATE | LOOKUP_RENAME_TARGET))
		वापस 0;

	spin_lock(&dentry->d_lock);
	ret = inode_eq_iversion(d_inode(dentry->d_parent),
			exfat_d_version(dentry));
	spin_unlock(&dentry->d_lock);
	वापस ret;
पूर्ण

/* वापसs the length of a काष्ठा qstr, ignoring trailing करोts */
अटल अचिन्हित पूर्णांक exfat_striptail_len(अचिन्हित पूर्णांक len, स्थिर अक्षर *name)
अणु
	जबतक (len && name[len - 1] == '.')
		len--;
	वापस len;
पूर्ण

/*
 * Compute the hash क्रम the exfat name corresponding to the dentry.  If the name
 * is invalid, we leave the hash code unchanged so that the existing dentry can
 * be used. The exfat fs routines will वापस ENOENT or EINVAL as appropriate.
 */
अटल पूर्णांक exfat_d_hash(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा nls_table *t = EXFAT_SB(sb)->nls_io;
	स्थिर अचिन्हित अक्षर *name = qstr->name;
	अचिन्हित पूर्णांक len = exfat_striptail_len(qstr->len, qstr->name);
	अचिन्हित दीर्घ hash = init_name_hash(dentry);
	पूर्णांक i, अक्षरlen;
	ब_अक्षर_प्रकार c;

	क्रम (i = 0; i < len; i += अक्षरlen) अणु
		अक्षरlen = t->अक्षर2uni(&name[i], len - i, &c);
		अगर (अक्षरlen < 0)
			वापस अक्षरlen;
		hash = partial_name_hash(exfat_बड़े(sb, c), hash);
	पूर्ण

	qstr->hash = end_name_hash(hash);
	वापस 0;
पूर्ण

अटल पूर्णांक exfat_d_cmp(स्थिर काष्ठा dentry *dentry, अचिन्हित पूर्णांक len,
		स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा nls_table *t = EXFAT_SB(sb)->nls_io;
	अचिन्हित पूर्णांक alen = exfat_striptail_len(name->len, name->name);
	अचिन्हित पूर्णांक blen = exfat_striptail_len(len, str);
	ब_अक्षर_प्रकार c1, c2;
	पूर्णांक अक्षरlen, i;

	अगर (alen != blen)
		वापस 1;

	क्रम (i = 0; i < len; i += अक्षरlen) अणु
		अक्षरlen = t->अक्षर2uni(&name->name[i], alen - i, &c1);
		अगर (अक्षरlen < 0)
			वापस 1;
		अगर (अक्षरlen != t->अक्षर2uni(&str[i], blen - i, &c2))
			वापस 1;

		अगर (exfat_बड़े(sb, c1) != exfat_बड़े(sb, c2))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा dentry_operations exfat_dentry_ops = अणु
	.d_revalidate	= exfat_d_revalidate,
	.d_hash		= exfat_d_hash,
	.d_compare	= exfat_d_cmp,
पूर्ण;

अटल पूर्णांक exfat_utf8_d_hash(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	स्थिर अचिन्हित अक्षर *name = qstr->name;
	अचिन्हित पूर्णांक len = exfat_striptail_len(qstr->len, qstr->name);
	अचिन्हित दीर्घ hash = init_name_hash(dentry);
	पूर्णांक i, अक्षरlen;
	unicode_t u;

	क्रम (i = 0; i < len; i += अक्षरlen) अणु
		अक्षरlen = utf8_to_utf32(&name[i], len - i, &u);
		अगर (अक्षरlen < 0)
			वापस अक्षरlen;

		/*
		 * exfat_बड़े() works only क्रम code poपूर्णांकs up to the U+FFFF.
		 */
		hash = partial_name_hash(u <= 0xFFFF ? exfat_बड़े(sb, u) : u,
					 hash);
	पूर्ण

	qstr->hash = end_name_hash(hash);
	वापस 0;
पूर्ण

अटल पूर्णांक exfat_utf8_d_cmp(स्थिर काष्ठा dentry *dentry, अचिन्हित पूर्णांक len,
		स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	अचिन्हित पूर्णांक alen = exfat_striptail_len(name->len, name->name);
	अचिन्हित पूर्णांक blen = exfat_striptail_len(len, str);
	unicode_t u_a, u_b;
	पूर्णांक अक्षरlen, i;

	अगर (alen != blen)
		वापस 1;

	क्रम (i = 0; i < alen; i += अक्षरlen) अणु
		अक्षरlen = utf8_to_utf32(&name->name[i], alen - i, &u_a);
		अगर (अक्षरlen < 0)
			वापस 1;
		अगर (अक्षरlen != utf8_to_utf32(&str[i], blen - i, &u_b))
			वापस 1;

		अगर (u_a <= 0xFFFF && u_b <= 0xFFFF) अणु
			अगर (exfat_बड़े(sb, u_a) != exfat_बड़े(sb, u_b))
				वापस 1;
		पूर्ण अन्यथा अणु
			अगर (u_a != u_b)
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा dentry_operations exfat_utf8_dentry_ops = अणु
	.d_revalidate	= exfat_d_revalidate,
	.d_hash		= exfat_utf8_d_hash,
	.d_compare	= exfat_utf8_d_cmp,
पूर्ण;

/* used only in search empty_slot() */
#घोषणा CNT_UNUSED_NOHIT        (-1)
#घोषणा CNT_UNUSED_HIT          (-2)
/* search EMPTY CONTINUOUS "num_entries" entries */
अटल पूर्णांक exfat_search_empty_slot(काष्ठा super_block *sb,
		काष्ठा exfat_hपूर्णांक_femp *hपूर्णांक_femp, काष्ठा exfat_chain *p_dir,
		पूर्णांक num_entries)
अणु
	पूर्णांक i, dentry, num_empty = 0;
	पूर्णांक dentries_per_clu;
	अचिन्हित पूर्णांक type;
	काष्ठा exfat_chain clu;
	काष्ठा exfat_dentry *ep;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा buffer_head *bh;

	dentries_per_clu = sbi->dentries_per_clu;

	अगर (hपूर्णांक_femp->eidx != EXFAT_HINT_NONE) अणु
		dentry = hपूर्णांक_femp->eidx;
		अगर (num_entries <= hपूर्णांक_femp->count) अणु
			hपूर्णांक_femp->eidx = EXFAT_HINT_NONE;
			वापस dentry;
		पूर्ण

		exfat_chain_dup(&clu, &hपूर्णांक_femp->cur);
	पूर्ण अन्यथा अणु
		exfat_chain_dup(&clu, p_dir);
		dentry = 0;
	पूर्ण

	जबतक (clu.dir != EXFAT_खातापूर्ण_CLUSTER) अणु
		i = dentry & (dentries_per_clu - 1);

		क्रम (; i < dentries_per_clu; i++, dentry++) अणु
			ep = exfat_get_dentry(sb, &clu, i, &bh, शून्य);
			अगर (!ep)
				वापस -EIO;
			type = exfat_get_entry_type(ep);
			brअन्यथा(bh);

			अगर (type == TYPE_UNUSED || type == TYPE_DELETED) अणु
				num_empty++;
				अगर (hपूर्णांक_femp->eidx == EXFAT_HINT_NONE) अणु
					hपूर्णांक_femp->eidx = dentry;
					hपूर्णांक_femp->count = CNT_UNUSED_NOHIT;
					exfat_chain_set(&hपूर्णांक_femp->cur,
						clu.dir, clu.size, clu.flags);
				पूर्ण

				अगर (type == TYPE_UNUSED &&
				    hपूर्णांक_femp->count != CNT_UNUSED_HIT)
					hपूर्णांक_femp->count = CNT_UNUSED_HIT;
			पूर्ण अन्यथा अणु
				अगर (hपूर्णांक_femp->eidx != EXFAT_HINT_NONE &&
				    hपूर्णांक_femp->count == CNT_UNUSED_HIT) अणु
					/* unused empty group means
					 * an empty group which includes
					 * unused dentry
					 */
					exfat_fs_error(sb,
						"found bogus dentry(%d) beyond unused empty group(%d) (start_clu : %u, cur_clu : %u)",
						dentry, hपूर्णांक_femp->eidx,
						p_dir->dir, clu.dir);
					वापस -EIO;
				पूर्ण

				num_empty = 0;
				hपूर्णांक_femp->eidx = EXFAT_HINT_NONE;
			पूर्ण

			अगर (num_empty >= num_entries) अणु
				/* found and invalidate hपूर्णांक_femp */
				hपूर्णांक_femp->eidx = EXFAT_HINT_NONE;
				वापस (dentry - (num_entries - 1));
			पूर्ण
		पूर्ण

		अगर (clu.flags == ALLOC_NO_FAT_CHAIN) अणु
			अगर (--clu.size > 0)
				clu.dir++;
			अन्यथा
				clu.dir = EXFAT_खातापूर्ण_CLUSTER;
		पूर्ण अन्यथा अणु
			अगर (exfat_get_next_cluster(sb, &clu.dir))
				वापस -EIO;
		पूर्ण
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक exfat_check_max_dentries(काष्ठा inode *inode)
अणु
	अगर (EXFAT_B_TO_DEN(i_size_पढ़ो(inode)) >= MAX_EXFAT_DENTRIES) अणु
		/*
		 * exFAT spec allows a dir to grow up to 8388608(256MB)
		 * dentries
		 */
		वापस -ENOSPC;
	पूर्ण
	वापस 0;
पूर्ण

/* find empty directory entry.
 * अगर there isn't any empty slot, expand cluster chain.
 */
अटल पूर्णांक exfat_find_empty_entry(काष्ठा inode *inode,
		काष्ठा exfat_chain *p_dir, पूर्णांक num_entries)
अणु
	पूर्णांक dentry;
	अचिन्हित पूर्णांक ret, last_clu;
	sector_t sector;
	loff_t size = 0;
	काष्ठा exfat_chain clu;
	काष्ठा exfat_dentry *ep = शून्य;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	काष्ठा exfat_hपूर्णांक_femp hपूर्णांक_femp;

	hपूर्णांक_femp.eidx = EXFAT_HINT_NONE;

	अगर (ei->hपूर्णांक_femp.eidx != EXFAT_HINT_NONE) अणु
		hपूर्णांक_femp = ei->hपूर्णांक_femp;
		ei->hपूर्णांक_femp.eidx = EXFAT_HINT_NONE;
	पूर्ण

	जबतक ((dentry = exfat_search_empty_slot(sb, &hपूर्णांक_femp, p_dir,
					num_entries)) < 0) अणु
		अगर (dentry == -EIO)
			अवरोध;

		अगर (exfat_check_max_dentries(inode))
			वापस -ENOSPC;

		/* we trust p_dir->size regardless of FAT type */
		अगर (exfat_find_last_cluster(sb, p_dir, &last_clu))
			वापस -EIO;

		/*
		 * Allocate new cluster to this directory
		 */
		exfat_chain_set(&clu, last_clu + 1, 0, p_dir->flags);

		/* allocate a cluster */
		ret = exfat_alloc_cluster(inode, 1, &clu, IS_सूचीSYNC(inode));
		अगर (ret)
			वापस ret;

		अगर (exfat_zeroed_cluster(inode, clu.dir))
			वापस -EIO;

		/* append to the FAT chain */
		अगर (clu.flags != p_dir->flags) अणु
			/* no-fat-chain bit is disabled,
			 * so fat-chain should be synced with alloc-biपंचांगap
			 */
			exfat_chain_cont_cluster(sb, p_dir->dir, p_dir->size);
			p_dir->flags = ALLOC_FAT_CHAIN;
			hपूर्णांक_femp.cur.flags = ALLOC_FAT_CHAIN;
		पूर्ण

		अगर (clu.flags == ALLOC_FAT_CHAIN)
			अगर (exfat_ent_set(sb, last_clu, clu.dir))
				वापस -EIO;

		अगर (hपूर्णांक_femp.eidx == EXFAT_HINT_NONE) अणु
			/* the special हाल that new dentry
			 * should be allocated from the start of new cluster
			 */
			hपूर्णांक_femp.eidx = EXFAT_B_TO_DEN_IDX(p_dir->size, sbi);
			hपूर्णांक_femp.count = sbi->dentries_per_clu;

			exfat_chain_set(&hपूर्णांक_femp.cur, clu.dir, 0, clu.flags);
		पूर्ण
		hपूर्णांक_femp.cur.size++;
		p_dir->size++;
		size = EXFAT_CLU_TO_B(p_dir->size, sbi);

		/* update the directory entry */
		अगर (p_dir->dir != sbi->root_dir) अणु
			काष्ठा buffer_head *bh;

			ep = exfat_get_dentry(sb,
				&(ei->dir), ei->entry + 1, &bh, &sector);
			अगर (!ep)
				वापस -EIO;

			ep->dentry.stream.valid_size = cpu_to_le64(size);
			ep->dentry.stream.size = ep->dentry.stream.valid_size;
			ep->dentry.stream.flags = p_dir->flags;
			exfat_update_bh(bh, IS_सूचीSYNC(inode));
			brअन्यथा(bh);
			अगर (exfat_update_dir_chksum(inode, &(ei->dir),
			    ei->entry))
				वापस -EIO;
		पूर्ण

		/* directory inode should be updated in here */
		i_size_ग_लिखो(inode, size);
		EXFAT_I(inode)->i_size_ondisk += sbi->cluster_size;
		EXFAT_I(inode)->i_size_aligned += sbi->cluster_size;
		EXFAT_I(inode)->flags = p_dir->flags;
		inode->i_blocks += 1 << sbi->sect_per_clus_bits;
	पूर्ण

	वापस dentry;
पूर्ण

/*
 * Name Resolution Functions :
 * Zero अगर it was successful; otherwise nonzero.
 */
अटल पूर्णांक __exfat_resolve_path(काष्ठा inode *inode, स्थिर अचिन्हित अक्षर *path,
		काष्ठा exfat_chain *p_dir, काष्ठा exfat_uni_name *p_uniname,
		पूर्णांक lookup)
अणु
	पूर्णांक namelen;
	पूर्णांक lossy = NLS_NAME_NO_LOSSY;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);

	/* strip all trailing periods */
	namelen = exfat_striptail_len(म_माप(path), path);
	अगर (!namelen)
		वापस -ENOENT;

	अगर (म_माप(path) > (MAX_NAME_LENGTH * MAX_CHARSET_SIZE))
		वापस -ENAMETOOLONG;

	/*
	 * strip all leading spaces :
	 * "MS windows 7" supports leading spaces.
	 * So we should skip this preprocessing क्रम compatibility.
	 */

	/* file name conversion :
	 * If lookup हाल, we allow bad-name क्रम compatibility.
	 */
	namelen = exfat_nls_to_utf16(sb, path, namelen, p_uniname,
			&lossy);
	अगर (namelen < 0)
		वापस namelen; /* वापस error value */

	अगर ((lossy && !lookup) || !namelen)
		वापस -EINVAL;

	exfat_chain_set(p_dir, ei->start_clu,
		EXFAT_B_TO_CLU(i_size_पढ़ो(inode), sbi), ei->flags);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक exfat_resolve_path(काष्ठा inode *inode,
		स्थिर अचिन्हित अक्षर *path, काष्ठा exfat_chain *dir,
		काष्ठा exfat_uni_name *uni)
अणु
	वापस __exfat_resolve_path(inode, path, dir, uni, 0);
पूर्ण

अटल अंतरभूत पूर्णांक exfat_resolve_path_क्रम_lookup(काष्ठा inode *inode,
		स्थिर अचिन्हित अक्षर *path, काष्ठा exfat_chain *dir,
		काष्ठा exfat_uni_name *uni)
अणु
	वापस __exfat_resolve_path(inode, path, dir, uni, 1);
पूर्ण

अटल अंतरभूत loff_t exfat_make_i_pos(काष्ठा exfat_dir_entry *info)
अणु
	वापस ((loff_t) info->dir.dir << 32) | (info->entry & 0xffffffff);
पूर्ण

अटल पूर्णांक exfat_add_entry(काष्ठा inode *inode, स्थिर अक्षर *path,
		काष्ठा exfat_chain *p_dir, अचिन्हित पूर्णांक type,
		काष्ठा exfat_dir_entry *info)
अणु
	पूर्णांक ret, dentry, num_entries;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_uni_name uniname;
	काष्ठा exfat_chain clu;
	पूर्णांक clu_size = 0;
	अचिन्हित पूर्णांक start_clu = EXFAT_FREE_CLUSTER;

	ret = exfat_resolve_path(inode, path, p_dir, &uniname);
	अगर (ret)
		जाओ out;

	num_entries = exfat_calc_num_entries(&uniname);
	अगर (num_entries < 0) अणु
		ret = num_entries;
		जाओ out;
	पूर्ण

	/* exfat_find_empty_entry must be called beक्रमe alloc_cluster() */
	dentry = exfat_find_empty_entry(inode, p_dir, num_entries);
	अगर (dentry < 0) अणु
		ret = dentry; /* -EIO or -ENOSPC */
		जाओ out;
	पूर्ण

	अगर (type == TYPE_सूची) अणु
		ret = exfat_alloc_new_dir(inode, &clu);
		अगर (ret)
			जाओ out;
		start_clu = clu.dir;
		clu_size = sbi->cluster_size;
	पूर्ण

	/* update the directory entry */
	/* fill the करोs name directory entry inक्रमmation of the created file.
	 * the first cluster is not determined yet. (0)
	 */
	ret = exfat_init_dir_entry(inode, p_dir, dentry, type,
		start_clu, clu_size);
	अगर (ret)
		जाओ out;

	ret = exfat_init_ext_entry(inode, p_dir, dentry, num_entries, &uniname);
	अगर (ret)
		जाओ out;

	info->dir = *p_dir;
	info->entry = dentry;
	info->flags = ALLOC_NO_FAT_CHAIN;
	info->type = type;

	अगर (type == TYPE_खाता) अणु
		info->attr = ATTR_ARCHIVE;
		info->start_clu = EXFAT_खातापूर्ण_CLUSTER;
		info->size = 0;
		info->num_subdirs = 0;
	पूर्ण अन्यथा अणु
		info->attr = ATTR_SUBसूची;
		info->start_clu = start_clu;
		info->size = clu_size;
		info->num_subdirs = EXFAT_MIN_SUBसूची;
	पूर्ण
	स_रखो(&info->crसमय, 0, माप(info->crसमय));
	स_रखो(&info->mसमय, 0, माप(info->mसमय));
	स_रखो(&info->aसमय, 0, माप(info->aसमय));
out:
	वापस ret;
पूर्ण

अटल पूर्णांक exfat_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *inode;
	काष्ठा exfat_chain cdir;
	काष्ठा exfat_dir_entry info;
	loff_t i_pos;
	पूर्णांक err;

	mutex_lock(&EXFAT_SB(sb)->s_lock);
	exfat_set_volume_dirty(sb);
	err = exfat_add_entry(dir, dentry->d_name.name, &cdir, TYPE_खाता,
		&info);
	exfat_clear_volume_dirty(sb);
	अगर (err)
		जाओ unlock;

	inode_inc_iversion(dir);
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	अगर (IS_सूचीSYNC(dir))
		exfat_sync_inode(dir);
	अन्यथा
		mark_inode_dirty(dir);

	i_pos = exfat_make_i_pos(&info);
	inode = exfat_build_inode(sb, &info, i_pos);
	err = PTR_ERR_OR_ZERO(inode);
	अगर (err)
		जाओ unlock;

	inode_inc_iversion(inode);
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय =
		EXFAT_I(inode)->i_crसमय = current_समय(inode);
	exfat_truncate_aसमय(&inode->i_aसमय);
	/* बारtamp is alपढ़ोy written, so mark_inode_dirty() is unneeded. */

	d_instantiate(dentry, inode);
unlock:
	mutex_unlock(&EXFAT_SB(sb)->s_lock);
	वापस err;
पूर्ण

/* lookup a file */
अटल पूर्णांक exfat_find(काष्ठा inode *dir, काष्ठा qstr *qname,
		काष्ठा exfat_dir_entry *info)
अणु
	पूर्णांक ret, dentry, num_entries, count;
	काष्ठा exfat_chain cdir;
	काष्ठा exfat_uni_name uni_name;
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(dir);
	काष्ठा exfat_dentry *ep, *ep2;
	काष्ठा exfat_entry_set_cache *es;
	/* क्रम optimized dir & entry to prevent दीर्घ traverse of cluster chain */
	काष्ठा exfat_hपूर्णांक hपूर्णांक_opt;

	अगर (qname->len == 0)
		वापस -ENOENT;

	/* check the validity of directory name in the given pathname */
	ret = exfat_resolve_path_क्रम_lookup(dir, qname->name, &cdir, &uni_name);
	अगर (ret)
		वापस ret;

	num_entries = exfat_calc_num_entries(&uni_name);
	अगर (num_entries < 0)
		वापस num_entries;

	/* check the validation of hपूर्णांक_stat and initialize it अगर required */
	अगर (ei->version != (inode_peek_iversion_raw(dir) & 0xffffffff)) अणु
		ei->hपूर्णांक_stat.clu = cdir.dir;
		ei->hपूर्णांक_stat.eidx = 0;
		ei->version = (inode_peek_iversion_raw(dir) & 0xffffffff);
		ei->hपूर्णांक_femp.eidx = EXFAT_HINT_NONE;
	पूर्ण

	/* search the file name क्रम directories */
	dentry = exfat_find_dir_entry(sb, ei, &cdir, &uni_name,
			num_entries, TYPE_ALL, &hपूर्णांक_opt);

	अगर (dentry < 0)
		वापस dentry; /* -error value */

	info->dir = cdir;
	info->entry = dentry;
	info->num_subdirs = 0;

	/* adjust cdir to the optimized value */
	cdir.dir = hपूर्णांक_opt.clu;
	अगर (cdir.flags & ALLOC_NO_FAT_CHAIN)
		cdir.size -= dentry / sbi->dentries_per_clu;
	dentry = hपूर्णांक_opt.eidx;
	es = exfat_get_dentry_set(sb, &cdir, dentry, ES_2_ENTRIES);
	अगर (!es)
		वापस -EIO;
	ep = exfat_get_dentry_cached(es, 0);
	ep2 = exfat_get_dentry_cached(es, 1);

	info->type = exfat_get_entry_type(ep);
	info->attr = le16_to_cpu(ep->dentry.file.attr);
	info->size = le64_to_cpu(ep2->dentry.stream.valid_size);
	अगर ((info->type == TYPE_खाता) && (info->size == 0)) अणु
		info->flags = ALLOC_NO_FAT_CHAIN;
		info->start_clu = EXFAT_खातापूर्ण_CLUSTER;
	पूर्ण अन्यथा अणु
		info->flags = ep2->dentry.stream.flags;
		info->start_clu =
			le32_to_cpu(ep2->dentry.stream.start_clu);
	पूर्ण

	exfat_get_entry_समय(sbi, &info->crसमय,
			     ep->dentry.file.create_tz,
			     ep->dentry.file.create_समय,
			     ep->dentry.file.create_date,
			     ep->dentry.file.create_समय_cs);
	exfat_get_entry_समय(sbi, &info->mसमय,
			     ep->dentry.file.modअगरy_tz,
			     ep->dentry.file.modअगरy_समय,
			     ep->dentry.file.modअगरy_date,
			     ep->dentry.file.modअगरy_समय_cs);
	exfat_get_entry_समय(sbi, &info->aसमय,
			     ep->dentry.file.access_tz,
			     ep->dentry.file.access_समय,
			     ep->dentry.file.access_date,
			     0);
	exfat_मुक्त_dentry_set(es, false);

	अगर (ei->start_clu == EXFAT_FREE_CLUSTER) अणु
		exfat_fs_error(sb,
			       "non-zero size file starts with zero cluster (size : %llu, p_dir : %u, entry : 0x%08x)",
			       i_size_पढ़ो(dir), ei->dir.dir, ei->entry);
		वापस -EIO;
	पूर्ण

	अगर (info->type == TYPE_सूची) अणु
		exfat_chain_set(&cdir, info->start_clu,
				EXFAT_B_TO_CLU(info->size, sbi), info->flags);
		count = exfat_count_dir_entries(sb, &cdir);
		अगर (count < 0)
			वापस -EIO;

		info->num_subdirs = count + EXFAT_MIN_SUBसूची;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक exfat_d_anon_disconn(काष्ठा dentry *dentry)
अणु
	वापस IS_ROOT(dentry) && (dentry->d_flags & DCACHE_DISCONNECTED);
पूर्ण

अटल काष्ठा dentry *exfat_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक flags)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *inode;
	काष्ठा dentry *alias;
	काष्ठा exfat_dir_entry info;
	पूर्णांक err;
	loff_t i_pos;
	mode_t i_mode;

	mutex_lock(&EXFAT_SB(sb)->s_lock);
	err = exfat_find(dir, &dentry->d_name, &info);
	अगर (err) अणु
		अगर (err == -ENOENT) अणु
			inode = शून्य;
			जाओ out;
		पूर्ण
		जाओ unlock;
	पूर्ण

	i_pos = exfat_make_i_pos(&info);
	inode = exfat_build_inode(sb, &info, i_pos);
	err = PTR_ERR_OR_ZERO(inode);
	अगर (err)
		जाओ unlock;

	i_mode = inode->i_mode;
	alias = d_find_alias(inode);

	/*
	 * Checking "alias->d_parent == dentry->d_parent" to make sure
	 * FS is not corrupted (especially द्विगुन linked dir).
	 */
	अगर (alias && alias->d_parent == dentry->d_parent &&
			!exfat_d_anon_disconn(alias)) अणु

		/*
		 * Unhashed alias is able to exist because of revalidate()
		 * called by lookup_fast. You can easily make this status
		 * by calling create and lookup concurrently
		 * In such हाल, we reuse an alias instead of new dentry
		 */
		अगर (d_unhashed(alias)) अणु
			WARN_ON(alias->d_name.hash_len !=
				dentry->d_name.hash_len);
			exfat_info(sb, "rehashed a dentry(%p) in read lookup",
				   alias);
			d_drop(dentry);
			d_rehash(alias);
		पूर्ण अन्यथा अगर (!S_ISसूची(i_mode)) अणु
			/*
			 * This inode has non anonymous-DCACHE_DISCONNECTED
			 * dentry. This means, the user did ->lookup() by an
			 * another name (दीर्घname vs 8.3 alias of it) in past.
			 *
			 * Switch to new one क्रम reason of locality अगर possible.
			 */
			d_move(alias, dentry);
		पूर्ण
		iput(inode);
		mutex_unlock(&EXFAT_SB(sb)->s_lock);
		वापस alias;
	पूर्ण
	dput(alias);
out:
	mutex_unlock(&EXFAT_SB(sb)->s_lock);
	अगर (!inode)
		exfat_d_version_set(dentry, inode_query_iversion(dir));

	वापस d_splice_alias(inode, dentry);
unlock:
	mutex_unlock(&EXFAT_SB(sb)->s_lock);
	वापस ERR_PTR(err);
पूर्ण

/* हटाओ an entry, BUT करोn't truncate */
अटल पूर्णांक exfat_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा exfat_chain cdir;
	काष्ठा exfat_dentry *ep;
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *inode = dentry->d_inode;
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	काष्ठा buffer_head *bh;
	sector_t sector;
	पूर्णांक num_entries, entry, err = 0;

	mutex_lock(&EXFAT_SB(sb)->s_lock);
	exfat_chain_dup(&cdir, &ei->dir);
	entry = ei->entry;
	अगर (ei->dir.dir == सूची_DELETED) अणु
		exfat_err(sb, "abnormal access to deleted dentry");
		err = -ENOENT;
		जाओ unlock;
	पूर्ण

	ep = exfat_get_dentry(sb, &cdir, entry, &bh, &sector);
	अगर (!ep) अणु
		err = -EIO;
		जाओ unlock;
	पूर्ण
	num_entries = exfat_count_ext_entries(sb, &cdir, entry, ep);
	अगर (num_entries < 0) अणु
		err = -EIO;
		brअन्यथा(bh);
		जाओ unlock;
	पूर्ण
	num_entries++;
	brअन्यथा(bh);

	exfat_set_volume_dirty(sb);
	/* update the directory entry */
	अगर (exfat_हटाओ_entries(dir, &cdir, entry, 0, num_entries)) अणु
		err = -EIO;
		जाओ unlock;
	पूर्ण

	/* This करोesn't modअगरy ei */
	ei->dir.dir = सूची_DELETED;
	exfat_clear_volume_dirty(sb);

	inode_inc_iversion(dir);
	dir->i_mसमय = dir->i_aसमय = current_समय(dir);
	exfat_truncate_aसमय(&dir->i_aसमय);
	अगर (IS_सूचीSYNC(dir))
		exfat_sync_inode(dir);
	अन्यथा
		mark_inode_dirty(dir);

	clear_nlink(inode);
	inode->i_mसमय = inode->i_aसमय = current_समय(inode);
	exfat_truncate_aसमय(&inode->i_aसमय);
	exfat_unhash_inode(inode);
	exfat_d_version_set(dentry, inode_query_iversion(dir));
unlock:
	mutex_unlock(&EXFAT_SB(sb)->s_lock);
	वापस err;
पूर्ण

अटल पूर्णांक exfat_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *inode;
	काष्ठा exfat_dir_entry info;
	काष्ठा exfat_chain cdir;
	loff_t i_pos;
	पूर्णांक err;

	mutex_lock(&EXFAT_SB(sb)->s_lock);
	exfat_set_volume_dirty(sb);
	err = exfat_add_entry(dir, dentry->d_name.name, &cdir, TYPE_सूची,
		&info);
	exfat_clear_volume_dirty(sb);
	अगर (err)
		जाओ unlock;

	inode_inc_iversion(dir);
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	अगर (IS_सूचीSYNC(dir))
		exfat_sync_inode(dir);
	अन्यथा
		mark_inode_dirty(dir);
	inc_nlink(dir);

	i_pos = exfat_make_i_pos(&info);
	inode = exfat_build_inode(sb, &info, i_pos);
	err = PTR_ERR_OR_ZERO(inode);
	अगर (err)
		जाओ unlock;

	inode_inc_iversion(inode);
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय =
		EXFAT_I(inode)->i_crसमय = current_समय(inode);
	exfat_truncate_aसमय(&inode->i_aसमय);
	/* बारtamp is alपढ़ोy written, so mark_inode_dirty() is unneeded. */

	d_instantiate(dentry, inode);

unlock:
	mutex_unlock(&EXFAT_SB(sb)->s_lock);
	वापस err;
पूर्ण

अटल पूर्णांक exfat_check_dir_empty(काष्ठा super_block *sb,
		काष्ठा exfat_chain *p_dir)
अणु
	पूर्णांक i, dentries_per_clu;
	अचिन्हित पूर्णांक type;
	काष्ठा exfat_chain clu;
	काष्ठा exfat_dentry *ep;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा buffer_head *bh;

	dentries_per_clu = sbi->dentries_per_clu;

	exfat_chain_dup(&clu, p_dir);

	जबतक (clu.dir != EXFAT_खातापूर्ण_CLUSTER) अणु
		क्रम (i = 0; i < dentries_per_clu; i++) अणु
			ep = exfat_get_dentry(sb, &clu, i, &bh, शून्य);
			अगर (!ep)
				वापस -EIO;
			type = exfat_get_entry_type(ep);
			brअन्यथा(bh);
			अगर (type == TYPE_UNUSED)
				वापस 0;

			अगर (type != TYPE_खाता && type != TYPE_सूची)
				जारी;

			वापस -ENOTEMPTY;
		पूर्ण

		अगर (clu.flags == ALLOC_NO_FAT_CHAIN) अणु
			अगर (--clu.size > 0)
				clu.dir++;
			अन्यथा
				clu.dir = EXFAT_खातापूर्ण_CLUSTER;
		पूर्ण अन्यथा अणु
			अगर (exfat_get_next_cluster(sb, &(clu.dir)))
				वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exfat_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	काष्ठा exfat_dentry *ep;
	काष्ठा exfat_chain cdir, clu_to_मुक्त;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	काष्ठा buffer_head *bh;
	sector_t sector;
	पूर्णांक num_entries, entry, err;

	mutex_lock(&EXFAT_SB(inode->i_sb)->s_lock);

	exfat_chain_dup(&cdir, &ei->dir);
	entry = ei->entry;

	अगर (ei->dir.dir == सूची_DELETED) अणु
		exfat_err(sb, "abnormal access to deleted dentry");
		err = -ENOENT;
		जाओ unlock;
	पूर्ण

	exfat_chain_set(&clu_to_मुक्त, ei->start_clu,
		EXFAT_B_TO_CLU_ROUND_UP(i_size_पढ़ो(inode), sbi), ei->flags);

	err = exfat_check_dir_empty(sb, &clu_to_मुक्त);
	अगर (err) अणु
		अगर (err == -EIO)
			exfat_err(sb, "failed to exfat_check_dir_empty : err(%d)",
				  err);
		जाओ unlock;
	पूर्ण

	ep = exfat_get_dentry(sb, &cdir, entry, &bh, &sector);
	अगर (!ep) अणु
		err = -EIO;
		जाओ unlock;
	पूर्ण

	num_entries = exfat_count_ext_entries(sb, &cdir, entry, ep);
	अगर (num_entries < 0) अणु
		err = -EIO;
		brअन्यथा(bh);
		जाओ unlock;
	पूर्ण
	num_entries++;
	brअन्यथा(bh);

	exfat_set_volume_dirty(sb);
	err = exfat_हटाओ_entries(dir, &cdir, entry, 0, num_entries);
	अगर (err) अणु
		exfat_err(sb, "failed to exfat_remove_entries : err(%d)", err);
		जाओ unlock;
	पूर्ण
	ei->dir.dir = सूची_DELETED;
	exfat_clear_volume_dirty(sb);

	inode_inc_iversion(dir);
	dir->i_mसमय = dir->i_aसमय = current_समय(dir);
	exfat_truncate_aसमय(&dir->i_aसमय);
	अगर (IS_सूचीSYNC(dir))
		exfat_sync_inode(dir);
	अन्यथा
		mark_inode_dirty(dir);
	drop_nlink(dir);

	clear_nlink(inode);
	inode->i_mसमय = inode->i_aसमय = current_समय(inode);
	exfat_truncate_aसमय(&inode->i_aसमय);
	exfat_unhash_inode(inode);
	exfat_d_version_set(dentry, inode_query_iversion(dir));
unlock:
	mutex_unlock(&EXFAT_SB(inode->i_sb)->s_lock);
	वापस err;
पूर्ण

अटल पूर्णांक exfat_नाम_file(काष्ठा inode *inode, काष्ठा exfat_chain *p_dir,
		पूर्णांक oldentry, काष्ठा exfat_uni_name *p_uniname,
		काष्ठा exfat_inode_info *ei)
अणु
	पूर्णांक ret, num_old_entries, num_new_entries;
	sector_t sector_old, sector_new;
	काष्ठा exfat_dentry *epold, *epnew;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *new_bh, *old_bh;
	पूर्णांक sync = IS_सूचीSYNC(inode);

	epold = exfat_get_dentry(sb, p_dir, oldentry, &old_bh, &sector_old);
	अगर (!epold)
		वापस -EIO;

	num_old_entries = exfat_count_ext_entries(sb, p_dir, oldentry, epold);
	अगर (num_old_entries < 0)
		वापस -EIO;
	num_old_entries++;

	num_new_entries = exfat_calc_num_entries(p_uniname);
	अगर (num_new_entries < 0)
		वापस num_new_entries;

	अगर (num_old_entries < num_new_entries) अणु
		पूर्णांक newentry;

		newentry =
			exfat_find_empty_entry(inode, p_dir, num_new_entries);
		अगर (newentry < 0)
			वापस newentry; /* -EIO or -ENOSPC */

		epnew = exfat_get_dentry(sb, p_dir, newentry, &new_bh,
			&sector_new);
		अगर (!epnew)
			वापस -EIO;

		*epnew = *epold;
		अगर (exfat_get_entry_type(epnew) == TYPE_खाता) अणु
			epnew->dentry.file.attr |= cpu_to_le16(ATTR_ARCHIVE);
			ei->attr |= ATTR_ARCHIVE;
		पूर्ण
		exfat_update_bh(new_bh, sync);
		brअन्यथा(old_bh);
		brअन्यथा(new_bh);

		epold = exfat_get_dentry(sb, p_dir, oldentry + 1, &old_bh,
			&sector_old);
		अगर (!epold)
			वापस -EIO;
		epnew = exfat_get_dentry(sb, p_dir, newentry + 1, &new_bh,
			&sector_new);
		अगर (!epnew) अणु
			brअन्यथा(old_bh);
			वापस -EIO;
		पूर्ण

		*epnew = *epold;
		exfat_update_bh(new_bh, sync);
		brअन्यथा(old_bh);
		brअन्यथा(new_bh);

		ret = exfat_init_ext_entry(inode, p_dir, newentry,
			num_new_entries, p_uniname);
		अगर (ret)
			वापस ret;

		exfat_हटाओ_entries(inode, p_dir, oldentry, 0,
			num_old_entries);
		ei->entry = newentry;
	पूर्ण अन्यथा अणु
		अगर (exfat_get_entry_type(epold) == TYPE_खाता) अणु
			epold->dentry.file.attr |= cpu_to_le16(ATTR_ARCHIVE);
			ei->attr |= ATTR_ARCHIVE;
		पूर्ण
		exfat_update_bh(old_bh, sync);
		brअन्यथा(old_bh);
		ret = exfat_init_ext_entry(inode, p_dir, oldentry,
			num_new_entries, p_uniname);
		अगर (ret)
			वापस ret;

		exfat_हटाओ_entries(inode, p_dir, oldentry, num_new_entries,
			num_old_entries);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक exfat_move_file(काष्ठा inode *inode, काष्ठा exfat_chain *p_olddir,
		पूर्णांक oldentry, काष्ठा exfat_chain *p_newdir,
		काष्ठा exfat_uni_name *p_uniname, काष्ठा exfat_inode_info *ei)
अणु
	पूर्णांक ret, newentry, num_new_entries, num_old_entries;
	sector_t sector_mov, sector_new;
	काष्ठा exfat_dentry *epmov, *epnew;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *mov_bh, *new_bh;

	epmov = exfat_get_dentry(sb, p_olddir, oldentry, &mov_bh, &sector_mov);
	अगर (!epmov)
		वापस -EIO;

	num_old_entries = exfat_count_ext_entries(sb, p_olddir, oldentry,
		epmov);
	अगर (num_old_entries < 0)
		वापस -EIO;
	num_old_entries++;

	num_new_entries = exfat_calc_num_entries(p_uniname);
	अगर (num_new_entries < 0)
		वापस num_new_entries;

	newentry = exfat_find_empty_entry(inode, p_newdir, num_new_entries);
	अगर (newentry < 0)
		वापस newentry; /* -EIO or -ENOSPC */

	epnew = exfat_get_dentry(sb, p_newdir, newentry, &new_bh, &sector_new);
	अगर (!epnew)
		वापस -EIO;

	*epnew = *epmov;
	अगर (exfat_get_entry_type(epnew) == TYPE_खाता) अणु
		epnew->dentry.file.attr |= cpu_to_le16(ATTR_ARCHIVE);
		ei->attr |= ATTR_ARCHIVE;
	पूर्ण
	exfat_update_bh(new_bh, IS_सूचीSYNC(inode));
	brअन्यथा(mov_bh);
	brअन्यथा(new_bh);

	epmov = exfat_get_dentry(sb, p_olddir, oldentry + 1, &mov_bh,
		&sector_mov);
	अगर (!epmov)
		वापस -EIO;
	epnew = exfat_get_dentry(sb, p_newdir, newentry + 1, &new_bh,
		&sector_new);
	अगर (!epnew) अणु
		brअन्यथा(mov_bh);
		वापस -EIO;
	पूर्ण

	*epnew = *epmov;
	exfat_update_bh(new_bh, IS_सूचीSYNC(inode));
	brअन्यथा(mov_bh);
	brअन्यथा(new_bh);

	ret = exfat_init_ext_entry(inode, p_newdir, newentry, num_new_entries,
		p_uniname);
	अगर (ret)
		वापस ret;

	exfat_हटाओ_entries(inode, p_olddir, oldentry, 0, num_old_entries);

	exfat_chain_set(&ei->dir, p_newdir->dir, p_newdir->size,
		p_newdir->flags);

	ei->entry = newentry;
	वापस 0;
पूर्ण

अटल व्योम exfat_update_parent_info(काष्ठा exfat_inode_info *ei,
		काष्ठा inode *parent_inode)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(parent_inode->i_sb);
	काष्ठा exfat_inode_info *parent_ei = EXFAT_I(parent_inode);
	loff_t parent_isize = i_size_पढ़ो(parent_inode);

	/*
	 * the problem that काष्ठा exfat_inode_info caches wrong parent info.
	 *
	 * because of flag-mismatch of ei->dir,
	 * there is abnormal traversing cluster chain.
	 */
	अगर (unlikely(parent_ei->flags != ei->dir.flags ||
		     parent_isize != EXFAT_CLU_TO_B(ei->dir.size, sbi) ||
		     parent_ei->start_clu != ei->dir.dir)) अणु
		exfat_chain_set(&ei->dir, parent_ei->start_clu,
			EXFAT_B_TO_CLU_ROUND_UP(parent_isize, sbi),
			parent_ei->flags);
	पूर्ण
पूर्ण

/* नाम or move a old file पूर्णांकo a new file */
अटल पूर्णांक __exfat_नाम(काष्ठा inode *old_parent_inode,
		काष्ठा exfat_inode_info *ei, काष्ठा inode *new_parent_inode,
		काष्ठा dentry *new_dentry)
अणु
	पूर्णांक ret;
	पूर्णांक dentry;
	काष्ठा exfat_chain olddir, newdir;
	काष्ठा exfat_chain *p_dir = शून्य;
	काष्ठा exfat_uni_name uni_name;
	काष्ठा exfat_dentry *ep;
	काष्ठा super_block *sb = old_parent_inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	स्थिर अचिन्हित अक्षर *new_path = new_dentry->d_name.name;
	काष्ठा inode *new_inode = new_dentry->d_inode;
	पूर्णांक num_entries;
	काष्ठा exfat_inode_info *new_ei = शून्य;
	अचिन्हित पूर्णांक new_entry_type = TYPE_UNUSED;
	पूर्णांक new_entry = 0;
	काष्ठा buffer_head *old_bh, *new_bh = शून्य;

	/* check the validity of poपूर्णांकer parameters */
	अगर (new_path == शून्य || म_माप(new_path) == 0)
		वापस -EINVAL;

	अगर (ei->dir.dir == सूची_DELETED) अणु
		exfat_err(sb, "abnormal access to deleted source dentry");
		वापस -ENOENT;
	पूर्ण

	exfat_update_parent_info(ei, old_parent_inode);

	exfat_chain_dup(&olddir, &ei->dir);
	dentry = ei->entry;

	ep = exfat_get_dentry(sb, &olddir, dentry, &old_bh, शून्य);
	अगर (!ep) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण
	brअन्यथा(old_bh);

	/* check whether new dir is existing directory and empty */
	अगर (new_inode) अणु
		ret = -EIO;
		new_ei = EXFAT_I(new_inode);

		अगर (new_ei->dir.dir == सूची_DELETED) अणु
			exfat_err(sb, "abnormal access to deleted target dentry");
			जाओ out;
		पूर्ण

		exfat_update_parent_info(new_ei, new_parent_inode);

		p_dir = &(new_ei->dir);
		new_entry = new_ei->entry;
		ep = exfat_get_dentry(sb, p_dir, new_entry, &new_bh, शून्य);
		अगर (!ep)
			जाओ out;

		new_entry_type = exfat_get_entry_type(ep);
		brअन्यथा(new_bh);

		/* अगर new_inode exists, update ei */
		अगर (new_entry_type == TYPE_सूची) अणु
			काष्ठा exfat_chain new_clu;

			new_clu.dir = new_ei->start_clu;
			new_clu.size =
				EXFAT_B_TO_CLU_ROUND_UP(i_size_पढ़ो(new_inode),
				sbi);
			new_clu.flags = new_ei->flags;

			ret = exfat_check_dir_empty(sb, &new_clu);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

	/* check the validity of directory name in the given new pathname */
	ret = exfat_resolve_path(new_parent_inode, new_path, &newdir,
			&uni_name);
	अगर (ret)
		जाओ out;

	exfat_set_volume_dirty(sb);

	अगर (olddir.dir == newdir.dir)
		ret = exfat_नाम_file(new_parent_inode, &olddir, dentry,
				&uni_name, ei);
	अन्यथा
		ret = exfat_move_file(new_parent_inode, &olddir, dentry,
				&newdir, &uni_name, ei);

	अगर (!ret && new_inode) अणु
		/* delete entries of new_dir */
		ep = exfat_get_dentry(sb, p_dir, new_entry, &new_bh, शून्य);
		अगर (!ep) अणु
			ret = -EIO;
			जाओ del_out;
		पूर्ण

		num_entries = exfat_count_ext_entries(sb, p_dir, new_entry, ep);
		अगर (num_entries < 0) अणु
			ret = -EIO;
			जाओ del_out;
		पूर्ण
		brअन्यथा(new_bh);

		अगर (exfat_हटाओ_entries(new_inode, p_dir, new_entry, 0,
				num_entries + 1)) अणु
			ret = -EIO;
			जाओ del_out;
		पूर्ण

		/* Free the clusters अगर new_inode is a dir(as अगर exfat_सूची_हटाओ) */
		अगर (new_entry_type == TYPE_सूची) अणु
			/* new_ei, new_clu_to_मुक्त */
			काष्ठा exfat_chain new_clu_to_मुक्त;

			exfat_chain_set(&new_clu_to_मुक्त, new_ei->start_clu,
				EXFAT_B_TO_CLU_ROUND_UP(i_size_पढ़ो(new_inode),
				sbi), new_ei->flags);

			अगर (exfat_मुक्त_cluster(new_inode, &new_clu_to_मुक्त)) अणु
				/* just set I/O error only */
				ret = -EIO;
			पूर्ण

			i_size_ग_लिखो(new_inode, 0);
			new_ei->start_clu = EXFAT_खातापूर्ण_CLUSTER;
			new_ei->flags = ALLOC_NO_FAT_CHAIN;
		पूर्ण
del_out:
		/* Update new_inode ei
		 * Prevent syncing हटाओd new_inode
		 * (new_ei is alपढ़ोy initialized above code ("if (new_inode)")
		 */
		new_ei->dir.dir = सूची_DELETED;
	पूर्ण
	exfat_clear_volume_dirty(sb);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक exfat_नाम(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *old_inode, *new_inode;
	काष्ठा super_block *sb = old_dir->i_sb;
	loff_t i_pos;
	पूर्णांक err;

	/*
	 * The VFS alपढ़ोy checks क्रम existence, so क्रम local fileप्रणालीs
	 * the RENAME_NOREPLACE implementation is equivalent to plain नाम.
	 * Don't support any other flags
	 */
	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	mutex_lock(&EXFAT_SB(sb)->s_lock);
	old_inode = old_dentry->d_inode;
	new_inode = new_dentry->d_inode;

	err = __exfat_नाम(old_dir, EXFAT_I(old_inode), new_dir, new_dentry);
	अगर (err)
		जाओ unlock;

	inode_inc_iversion(new_dir);
	new_dir->i_स_समय = new_dir->i_mसमय = new_dir->i_aसमय =
		EXFAT_I(new_dir)->i_crसमय = current_समय(new_dir);
	exfat_truncate_aसमय(&new_dir->i_aसमय);
	अगर (IS_सूचीSYNC(new_dir))
		exfat_sync_inode(new_dir);
	अन्यथा
		mark_inode_dirty(new_dir);

	i_pos = ((loff_t)EXFAT_I(old_inode)->dir.dir << 32) |
		(EXFAT_I(old_inode)->entry & 0xffffffff);
	exfat_unhash_inode(old_inode);
	exfat_hash_inode(old_inode, i_pos);
	अगर (IS_सूचीSYNC(new_dir))
		exfat_sync_inode(old_inode);
	अन्यथा
		mark_inode_dirty(old_inode);

	अगर (S_ISसूची(old_inode->i_mode) && old_dir != new_dir) अणु
		drop_nlink(old_dir);
		अगर (!new_inode)
			inc_nlink(new_dir);
	पूर्ण

	inode_inc_iversion(old_dir);
	old_dir->i_स_समय = old_dir->i_mसमय = current_समय(old_dir);
	अगर (IS_सूचीSYNC(old_dir))
		exfat_sync_inode(old_dir);
	अन्यथा
		mark_inode_dirty(old_dir);

	अगर (new_inode) अणु
		exfat_unhash_inode(new_inode);

		/* skip drop_nlink अगर new_inode alपढ़ोy has been dropped */
		अगर (new_inode->i_nlink) अणु
			drop_nlink(new_inode);
			अगर (S_ISसूची(new_inode->i_mode))
				drop_nlink(new_inode);
		पूर्ण अन्यथा अणु
			exfat_warn(sb, "abnormal access to an inode dropped");
			WARN_ON(new_inode->i_nlink == 0);
		पूर्ण
		new_inode->i_स_समय = EXFAT_I(new_inode)->i_crसमय =
			current_समय(new_inode);
	पूर्ण

unlock:
	mutex_unlock(&EXFAT_SB(sb)->s_lock);
	वापस err;
पूर्ण

स्थिर काष्ठा inode_operations exfat_dir_inode_operations = अणु
	.create		= exfat_create,
	.lookup		= exfat_lookup,
	.unlink		= exfat_unlink,
	.सूची_गढ़ो		= exfat_सूची_गढ़ो,
	.सूची_हटाओ		= exfat_सूची_हटाओ,
	.नाम		= exfat_नाम,
	.setattr	= exfat_setattr,
	.getattr	= exfat_getattr,
पूर्ण;
