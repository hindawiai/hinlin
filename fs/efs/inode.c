<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * inode.c
 *
 * Copyright (c) 1999 Al Smith
 *
 * Portions derived from work (c) 1995,1996 Christian Vogelgsang,
 *              and from work (c) 1998 Mike Shaver.
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश "efs.h"
#समावेश <linux/efs_fs_sb.h>

अटल पूर्णांक efs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page,efs_get_block);
पूर्ण
अटल sector_t _efs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping,block,efs_get_block);
पूर्ण
अटल स्थिर काष्ठा address_space_operations efs_aops = अणु
	.पढ़ोpage = efs_पढ़ोpage,
	.bmap = _efs_bmap
पूर्ण;

अटल अंतरभूत व्योम extent_copy(efs_extent *src, efs_extent *dst) अणु
	/*
	 * this is slightly evil. it करोesn't just copy
	 * efs_extent from src to dst, it also mangles
	 * the bits so that dst ends up in cpu byte-order.
	 */

	dst->cooked.ex_magic  =  (अचिन्हित पूर्णांक) src->raw[0];
	dst->cooked.ex_bn     = ((अचिन्हित पूर्णांक) src->raw[1] << 16) |
				((अचिन्हित पूर्णांक) src->raw[2] <<  8) |
				((अचिन्हित पूर्णांक) src->raw[3] <<  0);
	dst->cooked.ex_length =  (अचिन्हित पूर्णांक) src->raw[4];
	dst->cooked.ex_offset = ((अचिन्हित पूर्णांक) src->raw[5] << 16) |
				((अचिन्हित पूर्णांक) src->raw[6] <<  8) |
				((अचिन्हित पूर्णांक) src->raw[7] <<  0);
	वापस;
पूर्ण

काष्ठा inode *efs_iget(काष्ठा super_block *super, अचिन्हित दीर्घ ino)
अणु
	पूर्णांक i, inode_index;
	dev_t device;
	u32 rdev;
	काष्ठा buffer_head *bh;
	काष्ठा efs_sb_info    *sb = SUPER_INFO(super);
	काष्ठा efs_inode_info *in;
	efs_block_t block, offset;
	काष्ठा efs_dinode *efs_inode;
	काष्ठा inode *inode;

	inode = iget_locked(super, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	in = INODE_INFO(inode);

	/*
	** EFS layout:
	**
	** |   cylinder group    |   cylinder group    |   cylinder group ..etc
	** |inodes|data          |inodes|data          |inodes|data       ..etc
	**
	** work out the inode block index, (considering initially that the
	** inodes are stored as consecutive blocks). then work out the block
	** number of that inode given the above layout, and finally the
	** offset of the inode within that block.
	*/

	inode_index = inode->i_ino /
		(EFS_BLOCKSIZE / माप(काष्ठा efs_dinode));

	block = sb->fs_start + sb->first_block + 
		(sb->group_size * (inode_index / sb->inode_blocks)) +
		(inode_index % sb->inode_blocks);

	offset = (inode->i_ino %
			(EFS_BLOCKSIZE / माप(काष्ठा efs_dinode))) *
		माप(काष्ठा efs_dinode);

	bh = sb_bपढ़ो(inode->i_sb, block);
	अगर (!bh) अणु
		pr_warn("%s() failed at block %d\n", __func__, block);
		जाओ पढ़ो_inode_error;
	पूर्ण

	efs_inode = (काष्ठा efs_dinode *) (bh->b_data + offset);
    
	inode->i_mode  = be16_to_cpu(efs_inode->di_mode);
	set_nlink(inode, be16_to_cpu(efs_inode->di_nlink));
	i_uid_ग_लिखो(inode, (uid_t)be16_to_cpu(efs_inode->di_uid));
	i_gid_ग_लिखो(inode, (gid_t)be16_to_cpu(efs_inode->di_gid));
	inode->i_size  = be32_to_cpu(efs_inode->di_size);
	inode->i_aसमय.tv_sec = be32_to_cpu(efs_inode->di_aसमय);
	inode->i_mसमय.tv_sec = be32_to_cpu(efs_inode->di_mसमय);
	inode->i_स_समय.tv_sec = be32_to_cpu(efs_inode->di_स_समय);
	inode->i_aसमय.tv_nsec = inode->i_mसमय.tv_nsec = inode->i_स_समय.tv_nsec = 0;

	/* this is the number of blocks in the file */
	अगर (inode->i_size == 0) अणु
		inode->i_blocks = 0;
	पूर्ण अन्यथा अणु
		inode->i_blocks = ((inode->i_size - 1) >> EFS_BLOCKSIZE_BITS) + 1;
	पूर्ण

	rdev = be16_to_cpu(efs_inode->di_u.di_dev.odev);
	अगर (rdev == 0xffff) अणु
		rdev = be32_to_cpu(efs_inode->di_u.di_dev.ndev);
		अगर (sysv_major(rdev) > 0xfff)
			device = 0;
		अन्यथा
			device = MKDEV(sysv_major(rdev), sysv_minor(rdev));
	पूर्ण अन्यथा
		device = old_decode_dev(rdev);

	/* get the number of extents क्रम this object */
	in->numextents = be16_to_cpu(efs_inode->di_numextents);
	in->lastextent = 0;

	/* copy the extents contained within the inode to memory */
	क्रम(i = 0; i < EFS_सूचीECTEXTENTS; i++) अणु
		extent_copy(&(efs_inode->di_u.di_extents[i]), &(in->extents[i]));
		अगर (i < in->numextents && in->extents[i].cooked.ex_magic != 0) अणु
			pr_warn("extent %d has bad magic number in inode %lu\n",
				i, inode->i_ino);
			brअन्यथा(bh);
			जाओ पढ़ो_inode_error;
		पूर्ण
	पूर्ण

	brअन्यथा(bh);
	pr_debug("efs_iget(): inode %lu, extents %d, mode %o\n",
		 inode->i_ino, in->numextents, inode->i_mode);
	चयन (inode->i_mode & S_IFMT) अणु
		हाल S_IFसूची: 
			inode->i_op = &efs_dir_inode_operations; 
			inode->i_fop = &efs_dir_operations; 
			अवरोध;
		हाल S_IFREG:
			inode->i_fop = &generic_ro_fops;
			inode->i_data.a_ops = &efs_aops;
			अवरोध;
		हाल S_IFLNK:
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
			inode->i_data.a_ops = &efs_symlink_aops;
			अवरोध;
		हाल S_IFCHR:
		हाल S_IFBLK:
		हाल S_IFIFO:
			init_special_inode(inode, inode->i_mode, device);
			अवरोध;
		शेष:
			pr_warn("unsupported inode mode %o\n", inode->i_mode);
			जाओ पढ़ो_inode_error;
			अवरोध;
	पूर्ण

	unlock_new_inode(inode);
	वापस inode;
        
पढ़ो_inode_error:
	pr_warn("failed to read inode %lu\n", inode->i_ino);
	iget_failed(inode);
	वापस ERR_PTR(-EIO);
पूर्ण

अटल अंतरभूत efs_block_t
efs_extent_check(efs_extent *ptr, efs_block_t block, काष्ठा efs_sb_info *sb) अणु
	efs_block_t start;
	efs_block_t length;
	efs_block_t offset;

	/*
	 * given an extent and a logical block within a file,
	 * can this block be found within this extent ?
	 */
	start  = ptr->cooked.ex_bn;
	length = ptr->cooked.ex_length;
	offset = ptr->cooked.ex_offset;

	अगर ((block >= offset) && (block < offset+length)) अणु
		वापस(sb->fs_start + start + block - offset);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

efs_block_t efs_map_block(काष्ठा inode *inode, efs_block_t block) अणु
	काष्ठा efs_sb_info    *sb = SUPER_INFO(inode->i_sb);
	काष्ठा efs_inode_info *in = INODE_INFO(inode);
	काष्ठा buffer_head    *bh = शून्य;

	पूर्णांक cur, last, first = 1;
	पूर्णांक ibase, ioffset, dirext, direxts, indext, indexts;
	efs_block_t iblock, result = 0, lastblock = 0;
	efs_extent ext, *exts;

	last = in->lastextent;

	अगर (in->numextents <= EFS_सूचीECTEXTENTS) अणु
		/* first check the last extent we वापसed */
		अगर ((result = efs_extent_check(&in->extents[last], block, sb)))
			वापस result;
    
		/* अगर we only have one extent then nothing can be found */
		अगर (in->numextents == 1) अणु
			pr_err("%s() failed to map (1 extent)\n", __func__);
			वापस 0;
		पूर्ण

		direxts = in->numextents;

		/*
		 * check the stored extents in the inode
		 * start with next extent and check क्रमwards
		 */
		क्रम(dirext = 1; dirext < direxts; dirext++) अणु
			cur = (last + dirext) % in->numextents;
			अगर ((result = efs_extent_check(&in->extents[cur], block, sb))) अणु
				in->lastextent = cur;
				वापस result;
			पूर्ण
		पूर्ण

		pr_err("%s() failed to map block %u (dir)\n", __func__, block);
		वापस 0;
	पूर्ण

	pr_debug("%s(): indirect search for logical block %u\n",
		 __func__, block);
	direxts = in->extents[0].cooked.ex_offset;
	indexts = in->numextents;

	क्रम(indext = 0; indext < indexts; indext++) अणु
		cur = (last + indext) % indexts;

		/*
		 * work out which direct extent contains `cur'.
		 *
		 * also compute ibase: i.e. the number of the first
		 * indirect extent contained within direct extent `cur'.
		 *
		 */
		ibase = 0;
		क्रम(dirext = 0; cur < ibase && dirext < direxts; dirext++) अणु
			ibase += in->extents[dirext].cooked.ex_length *
				(EFS_BLOCKSIZE / माप(efs_extent));
		पूर्ण

		अगर (dirext == direxts) अणु
			/* should never happen */
			pr_err("couldn't find direct extent for indirect extent %d (block %u)\n",
			       cur, block);
			अगर (bh) brअन्यथा(bh);
			वापस 0;
		पूर्ण
		
		/* work out block number and offset of this indirect extent */
		iblock = sb->fs_start + in->extents[dirext].cooked.ex_bn +
			(cur - ibase) /
			(EFS_BLOCKSIZE / माप(efs_extent));
		ioffset = (cur - ibase) %
			(EFS_BLOCKSIZE / माप(efs_extent));

		अगर (first || lastblock != iblock) अणु
			अगर (bh) brअन्यथा(bh);

			bh = sb_bपढ़ो(inode->i_sb, iblock);
			अगर (!bh) अणु
				pr_err("%s() failed at block %d\n",
				       __func__, iblock);
				वापस 0;
			पूर्ण
			pr_debug("%s(): read indirect extent block %d\n",
				 __func__, iblock);
			first = 0;
			lastblock = iblock;
		पूर्ण

		exts = (efs_extent *) bh->b_data;

		extent_copy(&(exts[ioffset]), &ext);

		अगर (ext.cooked.ex_magic != 0) अणु
			pr_err("extent %d has bad magic number in block %d\n",
			       cur, iblock);
			अगर (bh) brअन्यथा(bh);
			वापस 0;
		पूर्ण

		अगर ((result = efs_extent_check(&ext, block, sb))) अणु
			अगर (bh) brअन्यथा(bh);
			in->lastextent = cur;
			वापस result;
		पूर्ण
	पूर्ण
	अगर (bh) brअन्यथा(bh);
	pr_err("%s() failed to map block %u (indir)\n", __func__, block);
	वापस 0;
पूर्ण  

MODULE_LICENSE("GPL");
