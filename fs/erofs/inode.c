<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश "xattr.h"

#समावेश <trace/events/erofs.h>

/*
 * अगर inode is successfully पढ़ो, वापस its inode page (or someबार
 * the inode payload page अगर it's an extended inode) in order to fill
 * अंतरभूत data अगर possible.
 */
अटल काष्ठा page *erofs_पढ़ो_inode(काष्ठा inode *inode,
				     अचिन्हित पूर्णांक *ofs)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा erofs_sb_info *sbi = EROFS_SB(sb);
	काष्ठा erofs_inode *vi = EROFS_I(inode);
	स्थिर erofs_off_t inode_loc = iloc(sbi, vi->nid);

	erofs_blk_t blkaddr, nblks = 0;
	काष्ठा page *page;
	काष्ठा erofs_inode_compact *dic;
	काष्ठा erofs_inode_extended *die, *copied = शून्य;
	अचिन्हित पूर्णांक अगरmt;
	पूर्णांक err;

	blkaddr = erofs_blknr(inode_loc);
	*ofs = erofs_blkoff(inode_loc);

	erofs_dbg("%s, reading inode nid %llu at %u of blkaddr %u",
		  __func__, vi->nid, *ofs, blkaddr);

	page = erofs_get_meta_page(sb, blkaddr);
	अगर (IS_ERR(page)) अणु
		erofs_err(sb, "failed to get inode (nid: %llu) page, err %ld",
			  vi->nid, PTR_ERR(page));
		वापस page;
	पूर्ण

	dic = page_address(page) + *ofs;
	अगरmt = le16_to_cpu(dic->i_क्रमmat);

	अगर (अगरmt & ~EROFS_I_ALL) अणु
		erofs_err(inode->i_sb, "unsupported i_format %u of nid %llu",
			  अगरmt, vi->nid);
		err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	vi->datalayout = erofs_inode_datalayout(अगरmt);
	अगर (vi->datalayout >= EROFS_INODE_DATALAYOUT_MAX) अणु
		erofs_err(inode->i_sb, "unsupported datalayout %u of nid %llu",
			  vi->datalayout, vi->nid);
		err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	चयन (erofs_inode_version(अगरmt)) अणु
	हाल EROFS_INODE_LAYOUT_EXTENDED:
		vi->inode_isize = माप(काष्ठा erofs_inode_extended);
		/* check अगर the inode acrosses page boundary */
		अगर (*ofs + vi->inode_isize <= PAGE_SIZE) अणु
			*ofs += vi->inode_isize;
			die = (काष्ठा erofs_inode_extended *)dic;
		पूर्ण अन्यथा अणु
			स्थिर अचिन्हित पूर्णांक gotten = PAGE_SIZE - *ofs;

			copied = kदो_स्मृति(vi->inode_isize, GFP_NOFS);
			अगर (!copied) अणु
				err = -ENOMEM;
				जाओ err_out;
			पूर्ण
			स_नकल(copied, dic, gotten);
			unlock_page(page);
			put_page(page);

			page = erofs_get_meta_page(sb, blkaddr + 1);
			अगर (IS_ERR(page)) अणु
				erofs_err(sb, "failed to get inode payload page (nid: %llu), err %ld",
					  vi->nid, PTR_ERR(page));
				kमुक्त(copied);
				वापस page;
			पूर्ण
			*ofs = vi->inode_isize - gotten;
			स_नकल((u8 *)copied + gotten, page_address(page), *ofs);
			die = copied;
		पूर्ण
		vi->xattr_isize = erofs_xattr_ibody_size(die->i_xattr_icount);

		inode->i_mode = le16_to_cpu(die->i_mode);
		चयन (inode->i_mode & S_IFMT) अणु
		हाल S_IFREG:
		हाल S_IFसूची:
		हाल S_IFLNK:
			vi->raw_blkaddr = le32_to_cpu(die->i_u.raw_blkaddr);
			अवरोध;
		हाल S_IFCHR:
		हाल S_IFBLK:
			inode->i_rdev =
				new_decode_dev(le32_to_cpu(die->i_u.rdev));
			अवरोध;
		हाल S_IFIFO:
		हाल S_IFSOCK:
			inode->i_rdev = 0;
			अवरोध;
		शेष:
			जाओ bogusimode;
		पूर्ण
		i_uid_ग_लिखो(inode, le32_to_cpu(die->i_uid));
		i_gid_ग_लिखो(inode, le32_to_cpu(die->i_gid));
		set_nlink(inode, le32_to_cpu(die->i_nlink));

		/* extended inode has its own बारtamp */
		inode->i_स_समय.tv_sec = le64_to_cpu(die->i_स_समय);
		inode->i_स_समय.tv_nsec = le32_to_cpu(die->i_स_समय_nsec);

		inode->i_size = le64_to_cpu(die->i_size);

		/* total blocks क्रम compressed files */
		अगर (erofs_inode_is_data_compressed(vi->datalayout))
			nblks = le32_to_cpu(die->i_u.compressed_blocks);

		kमुक्त(copied);
		अवरोध;
	हाल EROFS_INODE_LAYOUT_COMPACT:
		vi->inode_isize = माप(काष्ठा erofs_inode_compact);
		*ofs += vi->inode_isize;
		vi->xattr_isize = erofs_xattr_ibody_size(dic->i_xattr_icount);

		inode->i_mode = le16_to_cpu(dic->i_mode);
		चयन (inode->i_mode & S_IFMT) अणु
		हाल S_IFREG:
		हाल S_IFसूची:
		हाल S_IFLNK:
			vi->raw_blkaddr = le32_to_cpu(dic->i_u.raw_blkaddr);
			अवरोध;
		हाल S_IFCHR:
		हाल S_IFBLK:
			inode->i_rdev =
				new_decode_dev(le32_to_cpu(dic->i_u.rdev));
			अवरोध;
		हाल S_IFIFO:
		हाल S_IFSOCK:
			inode->i_rdev = 0;
			अवरोध;
		शेष:
			जाओ bogusimode;
		पूर्ण
		i_uid_ग_लिखो(inode, le16_to_cpu(dic->i_uid));
		i_gid_ग_लिखो(inode, le16_to_cpu(dic->i_gid));
		set_nlink(inode, le16_to_cpu(dic->i_nlink));

		/* use build समय क्रम compact inodes */
		inode->i_स_समय.tv_sec = sbi->build_समय;
		inode->i_स_समय.tv_nsec = sbi->build_समय_nsec;

		inode->i_size = le32_to_cpu(dic->i_size);
		अगर (erofs_inode_is_data_compressed(vi->datalayout))
			nblks = le32_to_cpu(dic->i_u.compressed_blocks);
		अवरोध;
	शेष:
		erofs_err(inode->i_sb,
			  "unsupported on-disk inode version %u of nid %llu",
			  erofs_inode_version(अगरmt), vi->nid);
		err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	inode->i_mसमय.tv_sec = inode->i_स_समय.tv_sec;
	inode->i_aसमय.tv_sec = inode->i_स_समय.tv_sec;
	inode->i_mसमय.tv_nsec = inode->i_स_समय.tv_nsec;
	inode->i_aसमय.tv_nsec = inode->i_स_समय.tv_nsec;

	अगर (!nblks)
		/* measure inode.i_blocks as generic fileप्रणालीs */
		inode->i_blocks = roundup(inode->i_size, EROFS_BLKSIZ) >> 9;
	अन्यथा
		inode->i_blocks = nblks << LOG_SECTORS_PER_BLOCK;
	वापस page;

bogusimode:
	erofs_err(inode->i_sb, "bogus i_mode (%o) @ nid %llu",
		  inode->i_mode, vi->nid);
	err = -EFSCORRUPTED;
err_out:
	DBG_BUGON(1);
	kमुक्त(copied);
	unlock_page(page);
	put_page(page);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक erofs_fill_symlink(काष्ठा inode *inode, व्योम *data,
			      अचिन्हित पूर्णांक m_pofs)
अणु
	काष्ठा erofs_inode *vi = EROFS_I(inode);
	अक्षर *lnk;

	/* अगर it cannot be handled with fast symlink scheme */
	अगर (vi->datalayout != EROFS_INODE_FLAT_INLINE ||
	    inode->i_size >= PAGE_SIZE) अणु
		inode->i_op = &erofs_symlink_iops;
		वापस 0;
	पूर्ण

	lnk = kदो_स्मृति(inode->i_size + 1, GFP_KERNEL);
	अगर (!lnk)
		वापस -ENOMEM;

	m_pofs += vi->xattr_isize;
	/* अंतरभूत symlink data shouldn't cross page boundary as well */
	अगर (m_pofs + inode->i_size > PAGE_SIZE) अणु
		kमुक्त(lnk);
		erofs_err(inode->i_sb,
			  "inline data cross block boundary @ nid %llu",
			  vi->nid);
		DBG_BUGON(1);
		वापस -EFSCORRUPTED;
	पूर्ण

	स_नकल(lnk, data + m_pofs, inode->i_size);
	lnk[inode->i_size] = '\0';

	inode->i_link = lnk;
	inode->i_op = &erofs_fast_symlink_iops;
	वापस 0;
पूर्ण

अटल पूर्णांक erofs_fill_inode(काष्ठा inode *inode, पूर्णांक isdir)
अणु
	काष्ठा erofs_inode *vi = EROFS_I(inode);
	काष्ठा page *page;
	अचिन्हित पूर्णांक ofs;
	पूर्णांक err = 0;

	trace_erofs_fill_inode(inode, isdir);

	/* पढ़ो inode base data from disk */
	page = erofs_पढ़ो_inode(inode, &ofs);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	/* setup the new inode */
	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFREG:
		inode->i_op = &erofs_generic_iops;
		inode->i_fop = &generic_ro_fops;
		अवरोध;
	हाल S_IFसूची:
		inode->i_op = &erofs_dir_iops;
		inode->i_fop = &erofs_dir_fops;
		अवरोध;
	हाल S_IFLNK:
		err = erofs_fill_symlink(inode, page_address(page), ofs);
		अगर (err)
			जाओ out_unlock;
		inode_nohighmem(inode);
		अवरोध;
	हाल S_IFCHR:
	हाल S_IFBLK:
	हाल S_IFIFO:
	हाल S_IFSOCK:
		inode->i_op = &erofs_generic_iops;
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
		जाओ out_unlock;
	शेष:
		err = -EFSCORRUPTED;
		जाओ out_unlock;
	पूर्ण

	अगर (erofs_inode_is_data_compressed(vi->datalayout)) अणु
		err = z_erofs_fill_inode(inode);
		जाओ out_unlock;
	पूर्ण
	inode->i_mapping->a_ops = &erofs_raw_access_aops;

out_unlock:
	unlock_page(page);
	put_page(page);
	वापस err;
पूर्ण

/*
 * erofs nid is 64bits, but i_ino is 'unsigned long', thereक्रमe
 * we should करो more क्रम 32-bit platक्रमm to find the right inode.
 */
अटल पूर्णांक erofs_ilookup_test_actor(काष्ठा inode *inode, व्योम *opaque)
अणु
	स्थिर erofs_nid_t nid = *(erofs_nid_t *)opaque;

	वापस EROFS_I(inode)->nid == nid;
पूर्ण

अटल पूर्णांक erofs_iget_set_actor(काष्ठा inode *inode, व्योम *opaque)
अणु
	स्थिर erofs_nid_t nid = *(erofs_nid_t *)opaque;

	inode->i_ino = erofs_inode_hash(nid);
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा inode *erofs_iget_locked(काष्ठा super_block *sb,
					      erofs_nid_t nid)
अणु
	स्थिर अचिन्हित दीर्घ hashval = erofs_inode_hash(nid);

	वापस iget5_locked(sb, hashval, erofs_ilookup_test_actor,
		erofs_iget_set_actor, &nid);
पूर्ण

काष्ठा inode *erofs_iget(काष्ठा super_block *sb,
			 erofs_nid_t nid,
			 bool isdir)
अणु
	काष्ठा inode *inode = erofs_iget_locked(sb, nid);

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	अगर (inode->i_state & I_NEW) अणु
		पूर्णांक err;
		काष्ठा erofs_inode *vi = EROFS_I(inode);

		vi->nid = nid;

		err = erofs_fill_inode(inode, isdir);
		अगर (!err)
			unlock_new_inode(inode);
		अन्यथा अणु
			iget_failed(inode);
			inode = ERR_PTR(err);
		पूर्ण
	पूर्ण
	वापस inode;
पूर्ण

पूर्णांक erofs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		  काष्ठा kstat *stat, u32 request_mask,
		  अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *स्थिर inode = d_inode(path->dentry);

	अगर (erofs_inode_is_data_compressed(EROFS_I(inode)->datalayout))
		stat->attributes |= STATX_ATTR_COMPRESSED;

	stat->attributes |= STATX_ATTR_IMMUTABLE;
	stat->attributes_mask |= (STATX_ATTR_COMPRESSED |
				  STATX_ATTR_IMMUTABLE);

	generic_fillattr(&init_user_ns, inode, stat);
	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations erofs_generic_iops = अणु
	.getattr = erofs_getattr,
	.listxattr = erofs_listxattr,
	.get_acl = erofs_get_acl,
पूर्ण;

स्थिर काष्ठा inode_operations erofs_symlink_iops = अणु
	.get_link = page_get_link,
	.getattr = erofs_getattr,
	.listxattr = erofs_listxattr,
	.get_acl = erofs_get_acl,
पूर्ण;

स्थिर काष्ठा inode_operations erofs_fast_symlink_iops = अणु
	.get_link = simple_get_link,
	.getattr = erofs_getattr,
	.listxattr = erofs_listxattr,
	.get_acl = erofs_get_acl,
पूर्ण;

