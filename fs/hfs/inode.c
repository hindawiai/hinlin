<शैली गुरु>
/*
 *  linux/fs/hfs/inode.c
 *
 * Copyright (C) 1995-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * This file contains inode-related functions which करो not depend on
 * which scheme is being used to represent विभाजनs.
 *
 * Based on the minix file प्रणाली code, (C) 1991, 1992 by Linus Torvalds
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/mpage.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/uपन.स>
#समावेश <linux/xattr.h>
#समावेश <linux/blkdev.h>

#समावेश "hfs_fs.h"
#समावेश "btree.h"

अटल स्थिर काष्ठा file_operations hfs_file_operations;
अटल स्थिर काष्ठा inode_operations hfs_file_inode_operations;

/*================ Variable-like macros ================*/

#घोषणा HFS_VALID_MODE_BITS  (S_IFREG | S_IFसूची | S_IRWXUGO)

अटल पूर्णांक hfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, hfs_get_block, wbc);
पूर्ण

अटल पूर्णांक hfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page, hfs_get_block);
पूर्ण

अटल व्योम hfs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		hfs_file_truncate(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक hfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	*pagep = शून्य;
	ret = cont_ग_लिखो_begin(file, mapping, pos, len, flags, pagep, fsdata,
				hfs_get_block,
				&HFS_I(mapping->host)->phys_size);
	अगर (unlikely(ret))
		hfs_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल sector_t hfs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, hfs_get_block);
पूर्ण

अटल पूर्णांक hfs_releasepage(काष्ठा page *page, gfp_t mask)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *node;
	u32 nidx;
	पूर्णांक i, res = 1;

	चयन (inode->i_ino) अणु
	हाल HFS_EXT_CNID:
		tree = HFS_SB(sb)->ext_tree;
		अवरोध;
	हाल HFS_CAT_CNID:
		tree = HFS_SB(sb)->cat_tree;
		अवरोध;
	शेष:
		BUG();
		वापस 0;
	पूर्ण

	अगर (!tree)
		वापस 0;

	अगर (tree->node_size >= PAGE_SIZE) अणु
		nidx = page->index >> (tree->node_size_shअगरt - PAGE_SHIFT);
		spin_lock(&tree->hash_lock);
		node = hfs_bnode_findhash(tree, nidx);
		अगर (!node)
			;
		अन्यथा अगर (atomic_पढ़ो(&node->refcnt))
			res = 0;
		अगर (res && node) अणु
			hfs_bnode_unhash(node);
			hfs_bnode_मुक्त(node);
		पूर्ण
		spin_unlock(&tree->hash_lock);
	पूर्ण अन्यथा अणु
		nidx = page->index << (PAGE_SHIFT - tree->node_size_shअगरt);
		i = 1 << (PAGE_SHIFT - tree->node_size_shअगरt);
		spin_lock(&tree->hash_lock);
		करो अणु
			node = hfs_bnode_findhash(tree, nidx++);
			अगर (!node)
				जारी;
			अगर (atomic_पढ़ो(&node->refcnt)) अणु
				res = 0;
				अवरोध;
			पूर्ण
			hfs_bnode_unhash(node);
			hfs_bnode_मुक्त(node);
		पूर्ण जबतक (--i && nidx < tree->node_count);
		spin_unlock(&tree->hash_lock);
	पूर्ण
	वापस res ? try_to_मुक्त_buffers(page) : 0;
पूर्ण

अटल sमाप_प्रकार hfs_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	माप_प्रकार count = iov_iter_count(iter);
	sमाप_प्रकार ret;

	ret = blockdev_direct_IO(iocb, inode, iter, hfs_get_block);

	/*
	 * In हाल of error extending ग_लिखो may have instantiated a few
	 * blocks outside i_size. Trim these off again.
	 */
	अगर (unlikely(iov_iter_rw(iter) == WRITE && ret < 0)) अणु
		loff_t isize = i_size_पढ़ो(inode);
		loff_t end = iocb->ki_pos + count;

		अगर (end > isize)
			hfs_ग_लिखो_failed(mapping, end);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hfs_ग_लिखोpages(काष्ठा address_space *mapping,
			  काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस mpage_ग_लिखोpages(mapping, wbc, hfs_get_block);
पूर्ण

स्थिर काष्ठा address_space_operations hfs_btree_aops = अणु
	.पढ़ोpage	= hfs_पढ़ोpage,
	.ग_लिखोpage	= hfs_ग_लिखोpage,
	.ग_लिखो_begin	= hfs_ग_लिखो_begin,
	.ग_लिखो_end	= generic_ग_लिखो_end,
	.bmap		= hfs_bmap,
	.releasepage	= hfs_releasepage,
पूर्ण;

स्थिर काष्ठा address_space_operations hfs_aops = अणु
	.पढ़ोpage	= hfs_पढ़ोpage,
	.ग_लिखोpage	= hfs_ग_लिखोpage,
	.ग_लिखो_begin	= hfs_ग_लिखो_begin,
	.ग_लिखो_end	= generic_ग_लिखो_end,
	.bmap		= hfs_bmap,
	.direct_IO	= hfs_direct_IO,
	.ग_लिखोpages	= hfs_ग_लिखोpages,
पूर्ण;

/*
 * hfs_new_inode
 */
काष्ठा inode *hfs_new_inode(काष्ठा inode *dir, स्थिर काष्ठा qstr *name, umode_t mode)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *inode = new_inode(sb);
	अगर (!inode)
		वापस शून्य;

	mutex_init(&HFS_I(inode)->extents_lock);
	INIT_LIST_HEAD(&HFS_I(inode)->खोलो_dir_list);
	spin_lock_init(&HFS_I(inode)->खोलो_dir_lock);
	hfs_cat_build_key(sb, (btree_key *)&HFS_I(inode)->cat_key, dir->i_ino, name);
	inode->i_ino = HFS_SB(sb)->next_id++;
	inode->i_mode = mode;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	set_nlink(inode, 1);
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	HFS_I(inode)->flags = 0;
	HFS_I(inode)->rsrc_inode = शून्य;
	HFS_I(inode)->fs_blocks = 0;
	अगर (S_ISसूची(mode)) अणु
		inode->i_size = 2;
		HFS_SB(sb)->folder_count++;
		अगर (dir->i_ino == HFS_ROOT_CNID)
			HFS_SB(sb)->root_dirs++;
		inode->i_op = &hfs_dir_inode_operations;
		inode->i_fop = &hfs_dir_operations;
		inode->i_mode |= S_IRWXUGO;
		inode->i_mode &= ~HFS_SB(inode->i_sb)->s_dir_umask;
	पूर्ण अन्यथा अगर (S_ISREG(mode)) अणु
		HFS_I(inode)->clump_blocks = HFS_SB(sb)->clumpablks;
		HFS_SB(sb)->file_count++;
		अगर (dir->i_ino == HFS_ROOT_CNID)
			HFS_SB(sb)->root_files++;
		inode->i_op = &hfs_file_inode_operations;
		inode->i_fop = &hfs_file_operations;
		inode->i_mapping->a_ops = &hfs_aops;
		inode->i_mode |= S_IRUGO|S_IXUGO;
		अगर (mode & S_IWUSR)
			inode->i_mode |= S_IWUGO;
		inode->i_mode &= ~HFS_SB(inode->i_sb)->s_file_umask;
		HFS_I(inode)->phys_size = 0;
		HFS_I(inode)->alloc_blocks = 0;
		HFS_I(inode)->first_blocks = 0;
		HFS_I(inode)->cached_start = 0;
		HFS_I(inode)->cached_blocks = 0;
		स_रखो(HFS_I(inode)->first_extents, 0, माप(hfs_extent_rec));
		स_रखो(HFS_I(inode)->cached_extents, 0, माप(hfs_extent_rec));
	पूर्ण
	insert_inode_hash(inode);
	mark_inode_dirty(inode);
	set_bit(HFS_FLG_MDB_सूचीTY, &HFS_SB(sb)->flags);
	hfs_mark_mdb_dirty(sb);

	वापस inode;
पूर्ण

व्योम hfs_delete_inode(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;

	hfs_dbg(INODE, "delete_inode: %lu\n", inode->i_ino);
	अगर (S_ISसूची(inode->i_mode)) अणु
		HFS_SB(sb)->folder_count--;
		अगर (HFS_I(inode)->cat_key.ParID == cpu_to_be32(HFS_ROOT_CNID))
			HFS_SB(sb)->root_dirs--;
		set_bit(HFS_FLG_MDB_सूचीTY, &HFS_SB(sb)->flags);
		hfs_mark_mdb_dirty(sb);
		वापस;
	पूर्ण
	HFS_SB(sb)->file_count--;
	अगर (HFS_I(inode)->cat_key.ParID == cpu_to_be32(HFS_ROOT_CNID))
		HFS_SB(sb)->root_files--;
	अगर (S_ISREG(inode->i_mode)) अणु
		अगर (!inode->i_nlink) अणु
			inode->i_size = 0;
			hfs_file_truncate(inode);
		पूर्ण
	पूर्ण
	set_bit(HFS_FLG_MDB_सूचीTY, &HFS_SB(sb)->flags);
	hfs_mark_mdb_dirty(sb);
पूर्ण

व्योम hfs_inode_पढ़ो_विभाजन(काष्ठा inode *inode, काष्ठा hfs_extent *ext,
			 __be32 __log_size, __be32 phys_size, u32 clump_size)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	u32 log_size = be32_to_cpu(__log_size);
	u16 count;
	पूर्णांक i;

	स_नकल(HFS_I(inode)->first_extents, ext, माप(hfs_extent_rec));
	क्रम (count = 0, i = 0; i < 3; i++)
		count += be16_to_cpu(ext[i].count);
	HFS_I(inode)->first_blocks = count;

	inode->i_size = HFS_I(inode)->phys_size = log_size;
	HFS_I(inode)->fs_blocks = (log_size + sb->s_blocksize - 1) >> sb->s_blocksize_bits;
	inode_set_bytes(inode, HFS_I(inode)->fs_blocks << sb->s_blocksize_bits);
	HFS_I(inode)->alloc_blocks = be32_to_cpu(phys_size) /
				     HFS_SB(sb)->alloc_blksz;
	HFS_I(inode)->clump_blocks = clump_size / HFS_SB(sb)->alloc_blksz;
	अगर (!HFS_I(inode)->clump_blocks)
		HFS_I(inode)->clump_blocks = HFS_SB(sb)->clumpablks;
पूर्ण

काष्ठा hfs_iget_data अणु
	काष्ठा hfs_cat_key *key;
	hfs_cat_rec *rec;
पूर्ण;

अटल पूर्णांक hfs_test_inode(काष्ठा inode *inode, व्योम *data)
अणु
	काष्ठा hfs_iget_data *idata = data;
	hfs_cat_rec *rec;

	rec = idata->rec;
	चयन (rec->type) अणु
	हाल HFS_CDR_सूची:
		वापस inode->i_ino == be32_to_cpu(rec->dir.DirID);
	हाल HFS_CDR_FIL:
		वापस inode->i_ino == be32_to_cpu(rec->file.FlNum);
	शेष:
		BUG();
		वापस 1;
	पूर्ण
पूर्ण

/*
 * hfs_पढ़ो_inode
 */
अटल पूर्णांक hfs_पढ़ो_inode(काष्ठा inode *inode, व्योम *data)
अणु
	काष्ठा hfs_iget_data *idata = data;
	काष्ठा hfs_sb_info *hsb = HFS_SB(inode->i_sb);
	hfs_cat_rec *rec;

	HFS_I(inode)->flags = 0;
	HFS_I(inode)->rsrc_inode = शून्य;
	mutex_init(&HFS_I(inode)->extents_lock);
	INIT_LIST_HEAD(&HFS_I(inode)->खोलो_dir_list);
	spin_lock_init(&HFS_I(inode)->खोलो_dir_lock);

	/* Initialize the inode */
	inode->i_uid = hsb->s_uid;
	inode->i_gid = hsb->s_gid;
	set_nlink(inode, 1);

	अगर (idata->key)
		HFS_I(inode)->cat_key = *idata->key;
	अन्यथा
		HFS_I(inode)->flags |= HFS_FLG_RSRC;
	HFS_I(inode)->tz_secondswest = sys_tz.tz_minuteswest * 60;

	rec = idata->rec;
	चयन (rec->type) अणु
	हाल HFS_CDR_FIL:
		अगर (!HFS_IS_RSRC(inode)) अणु
			hfs_inode_पढ़ो_विभाजन(inode, rec->file.ExtRec, rec->file.LgLen,
					    rec->file.PyLen, be16_to_cpu(rec->file.ClpSize));
		पूर्ण अन्यथा अणु
			hfs_inode_पढ़ो_विभाजन(inode, rec->file.RExtRec, rec->file.RLgLen,
					    rec->file.RPyLen, be16_to_cpu(rec->file.ClpSize));
		पूर्ण

		inode->i_ino = be32_to_cpu(rec->file.FlNum);
		inode->i_mode = S_IRUGO | S_IXUGO;
		अगर (!(rec->file.Flags & HFS_FIL_LOCK))
			inode->i_mode |= S_IWUGO;
		inode->i_mode &= ~hsb->s_file_umask;
		inode->i_mode |= S_IFREG;
		inode->i_स_समय = inode->i_aसमय = inode->i_mसमय =
				hfs_m_to_uसमय(rec->file.MdDat);
		inode->i_op = &hfs_file_inode_operations;
		inode->i_fop = &hfs_file_operations;
		inode->i_mapping->a_ops = &hfs_aops;
		अवरोध;
	हाल HFS_CDR_सूची:
		inode->i_ino = be32_to_cpu(rec->dir.DirID);
		inode->i_size = be16_to_cpu(rec->dir.Val) + 2;
		HFS_I(inode)->fs_blocks = 0;
		inode->i_mode = S_IFसूची | (S_IRWXUGO & ~hsb->s_dir_umask);
		inode->i_स_समय = inode->i_aसमय = inode->i_mसमय =
				hfs_m_to_uसमय(rec->dir.MdDat);
		inode->i_op = &hfs_dir_inode_operations;
		inode->i_fop = &hfs_dir_operations;
		अवरोध;
	शेष:
		make_bad_inode(inode);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * __hfs_iget()
 *
 * Given the MDB क्रम a HFS fileप्रणाली, a 'key' and an 'entry' in
 * the catalog B-tree and the 'type' of the desired file वापस the
 * inode क्रम that file/directory or शून्य.  Note that 'type' indicates
 * whether we want the actual file or directory, or the corresponding
 * metadata (AppleDouble header file or CAP metadata file).
 */
काष्ठा inode *hfs_iget(काष्ठा super_block *sb, काष्ठा hfs_cat_key *key, hfs_cat_rec *rec)
अणु
	काष्ठा hfs_iget_data data = अणु key, rec पूर्ण;
	काष्ठा inode *inode;
	u32 cnid;

	चयन (rec->type) अणु
	हाल HFS_CDR_सूची:
		cnid = be32_to_cpu(rec->dir.DirID);
		अवरोध;
	हाल HFS_CDR_FIL:
		cnid = be32_to_cpu(rec->file.FlNum);
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण
	inode = iget5_locked(sb, cnid, hfs_test_inode, hfs_पढ़ो_inode, &data);
	अगर (inode && (inode->i_state & I_NEW))
		unlock_new_inode(inode);
	वापस inode;
पूर्ण

व्योम hfs_inode_ग_लिखो_विभाजन(काष्ठा inode *inode, काष्ठा hfs_extent *ext,
			  __be32 *log_size, __be32 *phys_size)
अणु
	स_नकल(ext, HFS_I(inode)->first_extents, माप(hfs_extent_rec));

	अगर (log_size)
		*log_size = cpu_to_be32(inode->i_size);
	अगर (phys_size)
		*phys_size = cpu_to_be32(HFS_I(inode)->alloc_blocks *
					 HFS_SB(inode->i_sb)->alloc_blksz);
पूर्ण

पूर्णांक hfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *मुख्य_inode = inode;
	काष्ठा hfs_find_data fd;
	hfs_cat_rec rec;
	पूर्णांक res;

	hfs_dbg(INODE, "hfs_write_inode: %lu\n", inode->i_ino);
	res = hfs_ext_ग_लिखो_extent(inode);
	अगर (res)
		वापस res;

	अगर (inode->i_ino < HFS_FIRSTUSER_CNID) अणु
		चयन (inode->i_ino) अणु
		हाल HFS_ROOT_CNID:
			अवरोध;
		हाल HFS_EXT_CNID:
			hfs_btree_ग_लिखो(HFS_SB(inode->i_sb)->ext_tree);
			वापस 0;
		हाल HFS_CAT_CNID:
			hfs_btree_ग_लिखो(HFS_SB(inode->i_sb)->cat_tree);
			वापस 0;
		शेष:
			BUG();
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (HFS_IS_RSRC(inode))
		मुख्य_inode = HFS_I(inode)->rsrc_inode;

	अगर (!मुख्य_inode->i_nlink)
		वापस 0;

	अगर (hfs_find_init(HFS_SB(मुख्य_inode->i_sb)->cat_tree, &fd))
		/* panic? */
		वापस -EIO;

	fd.search_key->cat = HFS_I(मुख्य_inode)->cat_key;
	अगर (hfs_brec_find(&fd))
		/* panic? */
		जाओ out;

	अगर (S_ISसूची(मुख्य_inode->i_mode)) अणु
		अगर (fd.entrylength < माप(काष्ठा hfs_cat_dir))
			/* panic? */;
		hfs_bnode_पढ़ो(fd.bnode, &rec, fd.entryoffset,
			   माप(काष्ठा hfs_cat_dir));
		अगर (rec.type != HFS_CDR_सूची ||
		    be32_to_cpu(rec.dir.DirID) != inode->i_ino) अणु
		पूर्ण

		rec.dir.MdDat = hfs_u_to_mसमय(inode->i_mसमय);
		rec.dir.Val = cpu_to_be16(inode->i_size - 2);

		hfs_bnode_ग_लिखो(fd.bnode, &rec, fd.entryoffset,
			    माप(काष्ठा hfs_cat_dir));
	पूर्ण अन्यथा अगर (HFS_IS_RSRC(inode)) अणु
		hfs_bnode_पढ़ो(fd.bnode, &rec, fd.entryoffset,
			       माप(काष्ठा hfs_cat_file));
		hfs_inode_ग_लिखो_विभाजन(inode, rec.file.RExtRec,
				     &rec.file.RLgLen, &rec.file.RPyLen);
		hfs_bnode_ग_लिखो(fd.bnode, &rec, fd.entryoffset,
				माप(काष्ठा hfs_cat_file));
	पूर्ण अन्यथा अणु
		अगर (fd.entrylength < माप(काष्ठा hfs_cat_file))
			/* panic? */;
		hfs_bnode_पढ़ो(fd.bnode, &rec, fd.entryoffset,
			   माप(काष्ठा hfs_cat_file));
		अगर (rec.type != HFS_CDR_FIL ||
		    be32_to_cpu(rec.file.FlNum) != inode->i_ino) अणु
		पूर्ण

		अगर (inode->i_mode & S_IWUSR)
			rec.file.Flags &= ~HFS_FIL_LOCK;
		अन्यथा
			rec.file.Flags |= HFS_FIL_LOCK;
		hfs_inode_ग_लिखो_विभाजन(inode, rec.file.ExtRec, &rec.file.LgLen, &rec.file.PyLen);
		rec.file.MdDat = hfs_u_to_mसमय(inode->i_mसमय);

		hfs_bnode_ग_लिखो(fd.bnode, &rec, fd.entryoffset,
			    माप(काष्ठा hfs_cat_file));
	पूर्ण
out:
	hfs_find_निकास(&fd);
	वापस 0;
पूर्ण

अटल काष्ठा dentry *hfs_file_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				      अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = शून्य;
	hfs_cat_rec rec;
	काष्ठा hfs_find_data fd;
	पूर्णांक res;

	अगर (HFS_IS_RSRC(dir) || म_भेद(dentry->d_name.name, "rsrc"))
		जाओ out;

	inode = HFS_I(dir)->rsrc_inode;
	अगर (inode)
		जाओ out;

	inode = new_inode(dir->i_sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	res = hfs_find_init(HFS_SB(dir->i_sb)->cat_tree, &fd);
	अगर (res) अणु
		iput(inode);
		वापस ERR_PTR(res);
	पूर्ण
	fd.search_key->cat = HFS_I(dir)->cat_key;
	res = hfs_brec_पढ़ो(&fd, &rec, माप(rec));
	अगर (!res) अणु
		काष्ठा hfs_iget_data idata = अणु शून्य, &rec पूर्ण;
		hfs_पढ़ो_inode(inode, &idata);
	पूर्ण
	hfs_find_निकास(&fd);
	अगर (res) अणु
		iput(inode);
		वापस ERR_PTR(res);
	पूर्ण
	HFS_I(inode)->rsrc_inode = dir;
	HFS_I(dir)->rsrc_inode = inode;
	igrab(dir);
	inode_fake_hash(inode);
	mark_inode_dirty(inode);
	करोnt_mount(dentry);
out:
	वापस d_splice_alias(inode, dentry);
पूर्ण

व्योम hfs_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	अगर (HFS_IS_RSRC(inode) && HFS_I(inode)->rsrc_inode) अणु
		HFS_I(HFS_I(inode)->rsrc_inode)->rsrc_inode = शून्य;
		iput(HFS_I(inode)->rsrc_inode);
	पूर्ण
पूर्ण

अटल पूर्णांक hfs_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (HFS_IS_RSRC(inode))
		inode = HFS_I(inode)->rsrc_inode;
	atomic_inc(&HFS_I(inode)->खोलोcnt);
	वापस 0;
पूर्ण

अटल पूर्णांक hfs_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	//काष्ठा super_block *sb = inode->i_sb;

	अगर (HFS_IS_RSRC(inode))
		inode = HFS_I(inode)->rsrc_inode;
	अगर (atomic_dec_and_test(&HFS_I(inode)->खोलोcnt)) अणु
		inode_lock(inode);
		hfs_file_truncate(inode);
		//अगर (inode->i_flags & S_DEAD) अणु
		//	hfs_delete_cat(inode->i_ino, HFSPLUS_SB(sb).hidden_dir, शून्य);
		//	hfs_delete_inode(inode);
		//पूर्ण
		inode_unlock(inode);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * hfs_notअगरy_change()
 *
 * Based very बंदly on fs/msकरोs/inode.c by Werner Almesberger
 *
 * This is the notअगरy_change() field in the super_operations काष्ठाure
 * क्रम HFS file प्रणालीs.  The purpose is to take that changes made to
 * an inode and apply then in a fileप्रणाली-dependent manner.  In this
 * हाल the process has a few of tasks to करो:
 *  1) prevent changes to the i_uid and i_gid fields.
 *  2) map file permissions to the बंदst allowable permissions
 *  3) Since multiple Linux files can share the same on-disk inode under
 *     HFS (क्रम instance the data and resource विभाजनs of a file) a change
 *     to permissions must be applied to all other in-core inodes which
 *     correspond to the same HFS file.
 */

पूर्णांक hfs_inode_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		      काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा hfs_sb_info *hsb = HFS_SB(inode->i_sb);
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry,
				attr); /* basic permission checks */
	अगर (error)
		वापस error;

	/* no uig/gid changes and limit which mode bits can be set */
	अगर (((attr->ia_valid & ATTR_UID) &&
	     (!uid_eq(attr->ia_uid, hsb->s_uid))) ||
	    ((attr->ia_valid & ATTR_GID) &&
	     (!gid_eq(attr->ia_gid, hsb->s_gid))) ||
	    ((attr->ia_valid & ATTR_MODE) &&
	     ((S_ISसूची(inode->i_mode) &&
	       (attr->ia_mode != inode->i_mode)) ||
	      (attr->ia_mode & ~HFS_VALID_MODE_BITS)))) अणु
		वापस hsb->s_quiet ? 0 : error;
	पूर्ण

	अगर (attr->ia_valid & ATTR_MODE) अणु
		/* Only the 'w' bits can ever change and only all together. */
		अगर (attr->ia_mode & S_IWUSR)
			attr->ia_mode = inode->i_mode | S_IWUGO;
		अन्यथा
			attr->ia_mode = inode->i_mode & ~S_IWUGO;
		attr->ia_mode &= S_ISसूची(inode->i_mode) ? ~hsb->s_dir_umask: ~hsb->s_file_umask;
	पूर्ण

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_पढ़ो(inode)) अणु
		inode_dio_रुको(inode);

		error = inode_newsize_ok(inode, attr->ia_size);
		अगर (error)
			वापस error;

		truncate_setsize(inode, attr->ia_size);
		hfs_file_truncate(inode);
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय =
						  current_समय(inode);
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

अटल पूर्णांक hfs_file_fsync(काष्ठा file *filp, loff_t start, loff_t end,
			  पूर्णांक datasync)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	काष्ठा super_block * sb;
	पूर्णांक ret, err;

	ret = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (ret)
		वापस ret;
	inode_lock(inode);

	/* sync the inode to buffers */
	ret = ग_लिखो_inode_now(inode, 0);

	/* sync the superblock to buffers */
	sb = inode->i_sb;
	flush_delayed_work(&HFS_SB(sb)->mdb_work);
	/* .. finally sync the buffers to disk */
	err = sync_blockdev(sb->s_bdev);
	अगर (!ret)
		ret = err;
	inode_unlock(inode);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations hfs_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.fsync		= hfs_file_fsync,
	.खोलो		= hfs_file_खोलो,
	.release	= hfs_file_release,
पूर्ण;

अटल स्थिर काष्ठा inode_operations hfs_file_inode_operations = अणु
	.lookup		= hfs_file_lookup,
	.setattr	= hfs_inode_setattr,
	.listxattr	= generic_listxattr,
पूर्ण;
