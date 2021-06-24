<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ufs/inode.c
 *
 * Copyright (C) 1998
 * Daniel Pirkl <daniel.pirkl@email.cz>
 * Charles University, Faculty of Mathematics and Physics
 *
 *  from
 *
 *  linux/fs/ext2/inode.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/inode.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Goal-directed block allocation by Stephen Tweedie (sct@dcs.ed.ac.uk), 1993
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#समावेश <linux/uaccess.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/iversion.h>

#समावेश "ufs_fs.h"
#समावेश "ufs.h"
#समावेश "swab.h"
#समावेश "util.h"

अटल पूर्णांक ufs_block_to_path(काष्ठा inode *inode, sector_t i_block, अचिन्हित offsets[4])
अणु
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(inode->i_sb)->s_uspi;
	पूर्णांक ptrs = uspi->s_apb;
	पूर्णांक ptrs_bits = uspi->s_apbshअगरt;
	स्थिर दीर्घ direct_blocks = UFS_NDADDR,
		indirect_blocks = ptrs,
		द्विगुन_blocks = (1 << (ptrs_bits * 2));
	पूर्णांक n = 0;


	UFSD("ptrs=uspi->s_apb = %d,double_blocks=%ld \n",ptrs,द्विगुन_blocks);
	अगर (i_block < direct_blocks) अणु
		offsets[n++] = i_block;
	पूर्ण अन्यथा अगर ((i_block -= direct_blocks) < indirect_blocks) अणु
		offsets[n++] = UFS_IND_BLOCK;
		offsets[n++] = i_block;
	पूर्ण अन्यथा अगर ((i_block -= indirect_blocks) < द्विगुन_blocks) अणु
		offsets[n++] = UFS_DIND_BLOCK;
		offsets[n++] = i_block >> ptrs_bits;
		offsets[n++] = i_block & (ptrs - 1);
	पूर्ण अन्यथा अगर (((i_block -= द्विगुन_blocks) >> (ptrs_bits * 2)) < ptrs) अणु
		offsets[n++] = UFS_TIND_BLOCK;
		offsets[n++] = i_block >> (ptrs_bits * 2);
		offsets[n++] = (i_block >> ptrs_bits) & (ptrs - 1);
		offsets[n++] = i_block & (ptrs - 1);
	पूर्ण अन्यथा अणु
		ufs_warning(inode->i_sb, "ufs_block_to_path", "block > big");
	पूर्ण
	वापस n;
पूर्ण

प्रकार काष्ठा अणु
	व्योम	*p;
	जोड़ अणु
		__fs32	key32;
		__fs64	key64;
	पूर्ण;
	काष्ठा buffer_head *bh;
पूर्ण Indirect;

अटल अंतरभूत पूर्णांक grow_chain32(काष्ठा ufs_inode_info *ufsi,
			       काष्ठा buffer_head *bh, __fs32 *v,
			       Indirect *from, Indirect *to)
अणु
	Indirect *p;
	अचिन्हित seq;
	to->bh = bh;
	करो अणु
		seq = पढ़ो_seqbegin(&ufsi->meta_lock);
		to->key32 = *(__fs32 *)(to->p = v);
		क्रम (p = from; p <= to && p->key32 == *(__fs32 *)p->p; p++)
			;
	पूर्ण जबतक (पढ़ो_seqretry(&ufsi->meta_lock, seq));
	वापस (p > to);
पूर्ण

अटल अंतरभूत पूर्णांक grow_chain64(काष्ठा ufs_inode_info *ufsi,
			       काष्ठा buffer_head *bh, __fs64 *v,
			       Indirect *from, Indirect *to)
अणु
	Indirect *p;
	अचिन्हित seq;
	to->bh = bh;
	करो अणु
		seq = पढ़ो_seqbegin(&ufsi->meta_lock);
		to->key64 = *(__fs64 *)(to->p = v);
		क्रम (p = from; p <= to && p->key64 == *(__fs64 *)p->p; p++)
			;
	पूर्ण जबतक (पढ़ो_seqretry(&ufsi->meta_lock, seq));
	वापस (p > to);
पूर्ण

/*
 * Returns the location of the fragment from
 * the beginning of the fileप्रणाली.
 */

अटल u64 ufs_frag_map(काष्ठा inode *inode, अचिन्हित offsets[4], पूर्णांक depth)
अणु
	काष्ठा ufs_inode_info *ufsi = UFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	u64 mask = (u64) uspi->s_apbmask>>uspi->s_fpbshअगरt;
	पूर्णांक shअगरt = uspi->s_apbshअगरt-uspi->s_fpbshअगरt;
	Indirect chain[4], *q = chain;
	अचिन्हित *p;
	अचिन्हित flags = UFS_SB(sb)->s_flags;
	u64 res = 0;

	UFSD(": uspi->s_fpbshift = %d ,uspi->s_apbmask = %x, mask=%llx\n",
		uspi->s_fpbshअगरt, uspi->s_apbmask,
		(अचिन्हित दीर्घ दीर्घ)mask);

	अगर (depth == 0)
		जाओ no_block;

again:
	p = offsets;

	अगर ((flags & UFS_TYPE_MASK) == UFS_TYPE_UFS2)
		जाओ ufs2;

	अगर (!grow_chain32(ufsi, शून्य, &ufsi->i_u1.i_data[*p++], chain, q))
		जाओ changed;
	अगर (!q->key32)
		जाओ no_block;
	जबतक (--depth) अणु
		__fs32 *ptr;
		काष्ठा buffer_head *bh;
		अचिन्हित n = *p++;

		bh = sb_bपढ़ो(sb, uspi->s_sbbase +
				  fs32_to_cpu(sb, q->key32) + (n>>shअगरt));
		अगर (!bh)
			जाओ no_block;
		ptr = (__fs32 *)bh->b_data + (n & mask);
		अगर (!grow_chain32(ufsi, bh, ptr, chain, ++q))
			जाओ changed;
		अगर (!q->key32)
			जाओ no_block;
	पूर्ण
	res = fs32_to_cpu(sb, q->key32);
	जाओ found;

ufs2:
	अगर (!grow_chain64(ufsi, शून्य, &ufsi->i_u1.u2_i_data[*p++], chain, q))
		जाओ changed;
	अगर (!q->key64)
		जाओ no_block;

	जबतक (--depth) अणु
		__fs64 *ptr;
		काष्ठा buffer_head *bh;
		अचिन्हित n = *p++;

		bh = sb_bपढ़ो(sb, uspi->s_sbbase +
				  fs64_to_cpu(sb, q->key64) + (n>>shअगरt));
		अगर (!bh)
			जाओ no_block;
		ptr = (__fs64 *)bh->b_data + (n & mask);
		अगर (!grow_chain64(ufsi, bh, ptr, chain, ++q))
			जाओ changed;
		अगर (!q->key64)
			जाओ no_block;
	पूर्ण
	res = fs64_to_cpu(sb, q->key64);
found:
	res += uspi->s_sbbase;
no_block:
	जबतक (q > chain) अणु
		brअन्यथा(q->bh);
		q--;
	पूर्ण
	वापस res;

changed:
	जबतक (q > chain) अणु
		brअन्यथा(q->bh);
		q--;
	पूर्ण
	जाओ again;
पूर्ण

/*
 * Unpacking tails: we have a file with partial final block and
 * we had been asked to extend it.  If the fragment being written
 * is within the same block, we need to extend the tail just to cover
 * that fragment.  Otherwise the tail is extended to full block.
 *
 * Note that we might need to create a _new_ tail, but that will
 * be handled अन्यथाwhere; this is strictly क्रम resizing old
 * ones.
 */
अटल bool
ufs_extend_tail(काष्ठा inode *inode, u64 ग_लिखोs_to,
		  पूर्णांक *err, काष्ठा page *locked_page)
अणु
	काष्ठा ufs_inode_info *ufsi = UFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	अचिन्हित lastfrag = ufsi->i_lastfrag;	/* it's a लघु file, so अचिन्हित is enough */
	अचिन्हित block = ufs_fragstoblks(lastfrag);
	अचिन्हित new_size;
	व्योम *p;
	u64 पंचांगp;

	अगर (ग_लिखोs_to < (lastfrag | uspi->s_fpbmask))
		new_size = (ग_लिखोs_to & uspi->s_fpbmask) + 1;
	अन्यथा
		new_size = uspi->s_fpb;

	p = ufs_get_direct_data_ptr(uspi, ufsi, block);
	पंचांगp = ufs_new_fragments(inode, p, lastfrag, ufs_data_ptr_to_cpu(sb, p),
				new_size - (lastfrag & uspi->s_fpbmask), err,
				locked_page);
	वापस पंचांगp != 0;
पूर्ण

/**
 * ufs_inode_getfrag() - allocate new fragment(s)
 * @inode: poपूर्णांकer to inode
 * @index: number of block poपूर्णांकer within the inode's array.
 * @new_fragment: number of new allocated fragment(s)
 * @err: we set it अगर something wrong
 * @new: we set it अगर we allocate new block
 * @locked_page: क्रम ufs_new_fragments()
 */
अटल u64
ufs_inode_getfrag(काष्ठा inode *inode, अचिन्हित index,
		  sector_t new_fragment, पूर्णांक *err,
		  पूर्णांक *new, काष्ठा page *locked_page)
अणु
	काष्ठा ufs_inode_info *ufsi = UFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	u64 पंचांगp, goal, lastfrag;
	अचिन्हित nfrags = uspi->s_fpb;
	व्योम *p;

        /* TODO : to be करोne क्रम ग_लिखो support
        अगर ( (flags & UFS_TYPE_MASK) == UFS_TYPE_UFS2)
             जाओ ufs2;
         */

	p = ufs_get_direct_data_ptr(uspi, ufsi, index);
	पंचांगp = ufs_data_ptr_to_cpu(sb, p);
	अगर (पंचांगp)
		जाओ out;

	lastfrag = ufsi->i_lastfrag;

	/* will that be a new tail? */
	अगर (new_fragment < UFS_Nसूची_FRAGMENT && new_fragment >= lastfrag)
		nfrags = (new_fragment & uspi->s_fpbmask) + 1;

	goal = 0;
	अगर (index) अणु
		goal = ufs_data_ptr_to_cpu(sb,
				 ufs_get_direct_data_ptr(uspi, ufsi, index - 1));
		अगर (goal)
			goal += uspi->s_fpb;
	पूर्ण
	पंचांगp = ufs_new_fragments(inode, p, ufs_blknum(new_fragment),
				goal, nfrags, err, locked_page);

	अगर (!पंचांगp) अणु
		*err = -ENOSPC;
		वापस 0;
	पूर्ण

	अगर (new)
		*new = 1;
	inode->i_स_समय = current_समय(inode);
	अगर (IS_SYNC(inode))
		ufs_sync_inode (inode);
	mark_inode_dirty(inode);
out:
	वापस पंचांगp + uspi->s_sbbase;

     /* This part : To be implemented ....
        Required only क्रम writing, not required क्रम READ-ONLY.
ufs2:

	u2_block = ufs_fragstoblks(fragment);
	u2_blockoff = ufs_fragnum(fragment);
	p = ufsi->i_u1.u2_i_data + block;
	goal = 0;

repeat2:
	पंचांगp = fs32_to_cpu(sb, *p);
	lastfrag = ufsi->i_lastfrag;

     */
पूर्ण

/**
 * ufs_inode_getblock() - allocate new block
 * @inode: poपूर्णांकer to inode
 * @ind_block: block number of the indirect block
 * @index: number of poपूर्णांकer within the indirect block
 * @new_fragment: number of new allocated fragment
 *  (block will hold this fragment and also uspi->s_fpb-1)
 * @err: see ufs_inode_getfrag()
 * @new: see ufs_inode_getfrag()
 * @locked_page: see ufs_inode_getfrag()
 */
अटल u64
ufs_inode_getblock(काष्ठा inode *inode, u64 ind_block,
		  अचिन्हित index, sector_t new_fragment, पूर्णांक *err,
		  पूर्णांक *new, काष्ठा page *locked_page)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	पूर्णांक shअगरt = uspi->s_apbshअगरt - uspi->s_fpbshअगरt;
	u64 पंचांगp = 0, goal;
	काष्ठा buffer_head *bh;
	व्योम *p;

	अगर (!ind_block)
		वापस 0;

	bh = sb_bपढ़ो(sb, ind_block + (index >> shअगरt));
	अगर (unlikely(!bh)) अणु
		*err = -EIO;
		वापस 0;
	पूर्ण

	index &= uspi->s_apbmask >> uspi->s_fpbshअगरt;
	अगर (uspi->fs_magic == UFS2_MAGIC)
		p = (__fs64 *)bh->b_data + index;
	अन्यथा
		p = (__fs32 *)bh->b_data + index;

	पंचांगp = ufs_data_ptr_to_cpu(sb, p);
	अगर (पंचांगp)
		जाओ out;

	अगर (index && (uspi->fs_magic == UFS2_MAGIC ?
		      (पंचांगp = fs64_to_cpu(sb, ((__fs64 *)bh->b_data)[index-1])) :
		      (पंचांगp = fs32_to_cpu(sb, ((__fs32 *)bh->b_data)[index-1]))))
		goal = पंचांगp + uspi->s_fpb;
	अन्यथा
		goal = bh->b_blocknr + uspi->s_fpb;
	पंचांगp = ufs_new_fragments(inode, p, ufs_blknum(new_fragment), goal,
				uspi->s_fpb, err, locked_page);
	अगर (!पंचांगp)
		जाओ out;

	अगर (new)
		*new = 1;

	mark_buffer_dirty(bh);
	अगर (IS_SYNC(inode))
		sync_dirty_buffer(bh);
	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
out:
	brअन्यथा (bh);
	UFSD("EXIT\n");
	अगर (पंचांगp)
		पंचांगp += uspi->s_sbbase;
	वापस पंचांगp;
पूर्ण

/**
 * ufs_getfrag_block() - `get_block_t' function, पूर्णांकerface between UFS and
 * पढ़ोpage, ग_लिखोpage and so on
 */

अटल पूर्णांक ufs_getfrag_block(काष्ठा inode *inode, sector_t fragment, काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	पूर्णांक err = 0, new = 0;
	अचिन्हित offsets[4];
	पूर्णांक depth = ufs_block_to_path(inode, fragment >> uspi->s_fpbshअगरt, offsets);
	u64 phys64 = 0;
	अचिन्हित frag = fragment & uspi->s_fpbmask;

	phys64 = ufs_frag_map(inode, offsets, depth);
	अगर (!create)
		जाओ करोne;

	अगर (phys64) अणु
		अगर (fragment >= UFS_Nसूची_FRAGMENT)
			जाओ करोne;
		पढ़ो_seqlock_excl(&UFS_I(inode)->meta_lock);
		अगर (fragment < UFS_I(inode)->i_lastfrag) अणु
			पढ़ो_sequnlock_excl(&UFS_I(inode)->meta_lock);
			जाओ करोne;
		पूर्ण
		पढ़ो_sequnlock_excl(&UFS_I(inode)->meta_lock);
	पूर्ण
        /* This code entered only जबतक writing ....? */

	mutex_lock(&UFS_I(inode)->truncate_mutex);

	UFSD("ENTER, ino %lu, fragment %llu\n", inode->i_ino, (अचिन्हित दीर्घ दीर्घ)fragment);
	अगर (unlikely(!depth)) अणु
		ufs_warning(sb, "ufs_get_block", "block > big");
		err = -EIO;
		जाओ out;
	पूर्ण

	अगर (UFS_I(inode)->i_lastfrag < UFS_Nसूची_FRAGMENT) अणु
		अचिन्हित lastfrag = UFS_I(inode)->i_lastfrag;
		अचिन्हित tailfrags = lastfrag & uspi->s_fpbmask;
		अगर (tailfrags && fragment >= lastfrag) अणु
			अगर (!ufs_extend_tail(inode, fragment,
					     &err, bh_result->b_page))
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (depth == 1) अणु
		phys64 = ufs_inode_getfrag(inode, offsets[0], fragment,
					   &err, &new, bh_result->b_page);
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		phys64 = ufs_inode_getfrag(inode, offsets[0], fragment,
					   &err, शून्य, शून्य);
		क्रम (i = 1; i < depth - 1; i++)
			phys64 = ufs_inode_getblock(inode, phys64, offsets[i],
						fragment, &err, शून्य, शून्य);
		phys64 = ufs_inode_getblock(inode, phys64, offsets[depth - 1],
					fragment, &err, &new, bh_result->b_page);
	पूर्ण
out:
	अगर (phys64) अणु
		phys64 += frag;
		map_bh(bh_result, sb, phys64);
		अगर (new)
			set_buffer_new(bh_result);
	पूर्ण
	mutex_unlock(&UFS_I(inode)->truncate_mutex);
	वापस err;

करोne:
	अगर (phys64)
		map_bh(bh_result, sb, phys64 + frag);
	वापस 0;
पूर्ण

अटल पूर्णांक ufs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page,ufs_getfrag_block,wbc);
पूर्ण

अटल पूर्णांक ufs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page,ufs_getfrag_block);
पूर्ण

पूर्णांक ufs_prepare_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len)
अणु
	वापस __block_ग_लिखो_begin(page, pos, len, ufs_getfrag_block);
पूर्ण

अटल व्योम ufs_truncate_blocks(काष्ठा inode *);

अटल व्योम ufs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		ufs_truncate_blocks(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक ufs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	ret = block_ग_लिखो_begin(mapping, pos, len, flags, pagep,
				ufs_getfrag_block);
	अगर (unlikely(ret))
		ufs_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल पूर्णांक ufs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	पूर्णांक ret;

	ret = generic_ग_लिखो_end(file, mapping, pos, len, copied, page, fsdata);
	अगर (ret < len)
		ufs_ग_लिखो_failed(mapping, pos + len);
	वापस ret;
पूर्ण

अटल sector_t ufs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping,block,ufs_getfrag_block);
पूर्ण

स्थिर काष्ठा address_space_operations ufs_aops = अणु
	.पढ़ोpage = ufs_पढ़ोpage,
	.ग_लिखोpage = ufs_ग_लिखोpage,
	.ग_लिखो_begin = ufs_ग_लिखो_begin,
	.ग_लिखो_end = ufs_ग_लिखो_end,
	.bmap = ufs_bmap
पूर्ण;

अटल व्योम ufs_set_inode_ops(काष्ठा inode *inode)
अणु
	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op = &ufs_file_inode_operations;
		inode->i_fop = &ufs_file_operations;
		inode->i_mapping->a_ops = &ufs_aops;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &ufs_dir_inode_operations;
		inode->i_fop = &ufs_dir_operations;
		inode->i_mapping->a_ops = &ufs_aops;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		अगर (!inode->i_blocks) अणु
			inode->i_link = (अक्षर *)UFS_I(inode)->i_u1.i_symlink;
			inode->i_op = &simple_symlink_inode_operations;
		पूर्ण अन्यथा अणु
			inode->i_mapping->a_ops = &ufs_aops;
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
		पूर्ण
	पूर्ण अन्यथा
		init_special_inode(inode, inode->i_mode,
				   ufs_get_inode_dev(inode->i_sb, UFS_I(inode)));
पूर्ण

अटल पूर्णांक ufs1_पढ़ो_inode(काष्ठा inode *inode, काष्ठा ufs_inode *ufs_inode)
अणु
	काष्ठा ufs_inode_info *ufsi = UFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	umode_t mode;

	/*
	 * Copy data to the in-core inode.
	 */
	inode->i_mode = mode = fs16_to_cpu(sb, ufs_inode->ui_mode);
	set_nlink(inode, fs16_to_cpu(sb, ufs_inode->ui_nlink));
	अगर (inode->i_nlink == 0)
		वापस -ESTALE;

	/*
	 * Linux now has 32-bit uid and gid, so we can support EFT.
	 */
	i_uid_ग_लिखो(inode, ufs_get_inode_uid(sb, ufs_inode));
	i_gid_ग_लिखो(inode, ufs_get_inode_gid(sb, ufs_inode));

	inode->i_size = fs64_to_cpu(sb, ufs_inode->ui_size);
	inode->i_aसमय.tv_sec = (चिन्हित)fs32_to_cpu(sb, ufs_inode->ui_aसमय.tv_sec);
	inode->i_स_समय.tv_sec = (चिन्हित)fs32_to_cpu(sb, ufs_inode->ui_स_समय.tv_sec);
	inode->i_mसमय.tv_sec = (चिन्हित)fs32_to_cpu(sb, ufs_inode->ui_mसमय.tv_sec);
	inode->i_mसमय.tv_nsec = 0;
	inode->i_aसमय.tv_nsec = 0;
	inode->i_स_समय.tv_nsec = 0;
	inode->i_blocks = fs32_to_cpu(sb, ufs_inode->ui_blocks);
	inode->i_generation = fs32_to_cpu(sb, ufs_inode->ui_gen);
	ufsi->i_flags = fs32_to_cpu(sb, ufs_inode->ui_flags);
	ufsi->i_shaकरोw = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_shaकरोw);
	ufsi->i_oeftflag = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_oeftflag);


	अगर (S_ISCHR(mode) || S_ISBLK(mode) || inode->i_blocks) अणु
		स_नकल(ufsi->i_u1.i_data, &ufs_inode->ui_u2.ui_addr,
		       माप(ufs_inode->ui_u2.ui_addr));
	पूर्ण अन्यथा अणु
		स_नकल(ufsi->i_u1.i_symlink, ufs_inode->ui_u2.ui_symlink,
		       माप(ufs_inode->ui_u2.ui_symlink) - 1);
		ufsi->i_u1.i_symlink[माप(ufs_inode->ui_u2.ui_symlink) - 1] = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ufs2_पढ़ो_inode(काष्ठा inode *inode, काष्ठा ufs2_inode *ufs2_inode)
अणु
	काष्ठा ufs_inode_info *ufsi = UFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	umode_t mode;

	UFSD("Reading ufs2 inode, ino %lu\n", inode->i_ino);
	/*
	 * Copy data to the in-core inode.
	 */
	inode->i_mode = mode = fs16_to_cpu(sb, ufs2_inode->ui_mode);
	set_nlink(inode, fs16_to_cpu(sb, ufs2_inode->ui_nlink));
	अगर (inode->i_nlink == 0)
		वापस -ESTALE;

        /*
         * Linux now has 32-bit uid and gid, so we can support EFT.
         */
	i_uid_ग_लिखो(inode, fs32_to_cpu(sb, ufs2_inode->ui_uid));
	i_gid_ग_लिखो(inode, fs32_to_cpu(sb, ufs2_inode->ui_gid));

	inode->i_size = fs64_to_cpu(sb, ufs2_inode->ui_size);
	inode->i_aसमय.tv_sec = fs64_to_cpu(sb, ufs2_inode->ui_aसमय);
	inode->i_स_समय.tv_sec = fs64_to_cpu(sb, ufs2_inode->ui_स_समय);
	inode->i_mसमय.tv_sec = fs64_to_cpu(sb, ufs2_inode->ui_mसमय);
	inode->i_aसमय.tv_nsec = fs32_to_cpu(sb, ufs2_inode->ui_aसमयnsec);
	inode->i_स_समय.tv_nsec = fs32_to_cpu(sb, ufs2_inode->ui_स_समयnsec);
	inode->i_mसमय.tv_nsec = fs32_to_cpu(sb, ufs2_inode->ui_mसमयnsec);
	inode->i_blocks = fs64_to_cpu(sb, ufs2_inode->ui_blocks);
	inode->i_generation = fs32_to_cpu(sb, ufs2_inode->ui_gen);
	ufsi->i_flags = fs32_to_cpu(sb, ufs2_inode->ui_flags);
	/*
	ufsi->i_shaकरोw = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_shaकरोw);
	ufsi->i_oeftflag = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_oeftflag);
	*/

	अगर (S_ISCHR(mode) || S_ISBLK(mode) || inode->i_blocks) अणु
		स_नकल(ufsi->i_u1.u2_i_data, &ufs2_inode->ui_u2.ui_addr,
		       माप(ufs2_inode->ui_u2.ui_addr));
	पूर्ण अन्यथा अणु
		स_नकल(ufsi->i_u1.i_symlink, ufs2_inode->ui_u2.ui_symlink,
		       माप(ufs2_inode->ui_u2.ui_symlink) - 1);
		ufsi->i_u1.i_symlink[माप(ufs2_inode->ui_u2.ui_symlink) - 1] = 0;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा inode *ufs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा ufs_inode_info *ufsi;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	काष्ठा buffer_head * bh;
	काष्ठा inode *inode;
	पूर्णांक err = -EIO;

	UFSD("ENTER, ino %lu\n", ino);

	अगर (ino < UFS_ROOTINO || ino > (uspi->s_ncg * uspi->s_ipg)) अणु
		ufs_warning(sb, "ufs_read_inode", "bad inode number (%lu)\n",
			    ino);
		वापस ERR_PTR(-EIO);
	पूर्ण

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	ufsi = UFS_I(inode);

	bh = sb_bपढ़ो(sb, uspi->s_sbbase + ufs_inotofsba(inode->i_ino));
	अगर (!bh) अणु
		ufs_warning(sb, "ufs_read_inode", "unable to read inode %lu\n",
			    inode->i_ino);
		जाओ bad_inode;
	पूर्ण
	अगर ((UFS_SB(sb)->s_flags & UFS_TYPE_MASK) == UFS_TYPE_UFS2) अणु
		काष्ठा ufs2_inode *ufs2_inode = (काष्ठा ufs2_inode *)bh->b_data;

		err = ufs2_पढ़ो_inode(inode,
				      ufs2_inode + ufs_inotofsbo(inode->i_ino));
	पूर्ण अन्यथा अणु
		काष्ठा ufs_inode *ufs_inode = (काष्ठा ufs_inode *)bh->b_data;

		err = ufs1_पढ़ो_inode(inode,
				      ufs_inode + ufs_inotofsbo(inode->i_ino));
	पूर्ण
	brअन्यथा(bh);
	अगर (err)
		जाओ bad_inode;

	inode_inc_iversion(inode);
	ufsi->i_lastfrag =
		(inode->i_size + uspi->s_fsize - 1) >> uspi->s_fshअगरt;
	ufsi->i_dir_start_lookup = 0;
	ufsi->i_osync = 0;

	ufs_set_inode_ops(inode);

	UFSD("EXIT\n");
	unlock_new_inode(inode);
	वापस inode;

bad_inode:
	iget_failed(inode);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम ufs1_update_inode(काष्ठा inode *inode, काष्ठा ufs_inode *ufs_inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
 	काष्ठा ufs_inode_info *ufsi = UFS_I(inode);

	ufs_inode->ui_mode = cpu_to_fs16(sb, inode->i_mode);
	ufs_inode->ui_nlink = cpu_to_fs16(sb, inode->i_nlink);

	ufs_set_inode_uid(sb, ufs_inode, i_uid_पढ़ो(inode));
	ufs_set_inode_gid(sb, ufs_inode, i_gid_पढ़ो(inode));

	ufs_inode->ui_size = cpu_to_fs64(sb, inode->i_size);
	ufs_inode->ui_aसमय.tv_sec = cpu_to_fs32(sb, inode->i_aसमय.tv_sec);
	ufs_inode->ui_aसमय.tv_usec = 0;
	ufs_inode->ui_स_समय.tv_sec = cpu_to_fs32(sb, inode->i_स_समय.tv_sec);
	ufs_inode->ui_स_समय.tv_usec = 0;
	ufs_inode->ui_mसमय.tv_sec = cpu_to_fs32(sb, inode->i_mसमय.tv_sec);
	ufs_inode->ui_mसमय.tv_usec = 0;
	ufs_inode->ui_blocks = cpu_to_fs32(sb, inode->i_blocks);
	ufs_inode->ui_flags = cpu_to_fs32(sb, ufsi->i_flags);
	ufs_inode->ui_gen = cpu_to_fs32(sb, inode->i_generation);

	अगर ((UFS_SB(sb)->s_flags & UFS_UID_MASK) == UFS_UID_EFT) अणु
		ufs_inode->ui_u3.ui_sun.ui_shaकरोw = cpu_to_fs32(sb, ufsi->i_shaकरोw);
		ufs_inode->ui_u3.ui_sun.ui_oeftflag = cpu_to_fs32(sb, ufsi->i_oeftflag);
	पूर्ण

	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) अणु
		/* ufs_inode->ui_u2.ui_addr.ui_db[0] = cpu_to_fs32(sb, inode->i_rdev); */
		ufs_inode->ui_u2.ui_addr.ui_db[0] = ufsi->i_u1.i_data[0];
	पूर्ण अन्यथा अगर (inode->i_blocks) अणु
		स_नकल(&ufs_inode->ui_u2.ui_addr, ufsi->i_u1.i_data,
		       माप(ufs_inode->ui_u2.ui_addr));
	पूर्ण
	अन्यथा अणु
		स_नकल(&ufs_inode->ui_u2.ui_symlink, ufsi->i_u1.i_symlink,
		       माप(ufs_inode->ui_u2.ui_symlink));
	पूर्ण

	अगर (!inode->i_nlink)
		स_रखो (ufs_inode, 0, माप(काष्ठा ufs_inode));
पूर्ण

अटल व्योम ufs2_update_inode(काष्ठा inode *inode, काष्ठा ufs2_inode *ufs_inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
 	काष्ठा ufs_inode_info *ufsi = UFS_I(inode);

	UFSD("ENTER\n");
	ufs_inode->ui_mode = cpu_to_fs16(sb, inode->i_mode);
	ufs_inode->ui_nlink = cpu_to_fs16(sb, inode->i_nlink);

	ufs_inode->ui_uid = cpu_to_fs32(sb, i_uid_पढ़ो(inode));
	ufs_inode->ui_gid = cpu_to_fs32(sb, i_gid_पढ़ो(inode));

	ufs_inode->ui_size = cpu_to_fs64(sb, inode->i_size);
	ufs_inode->ui_aसमय = cpu_to_fs64(sb, inode->i_aसमय.tv_sec);
	ufs_inode->ui_aसमयnsec = cpu_to_fs32(sb, inode->i_aसमय.tv_nsec);
	ufs_inode->ui_स_समय = cpu_to_fs64(sb, inode->i_स_समय.tv_sec);
	ufs_inode->ui_स_समयnsec = cpu_to_fs32(sb, inode->i_स_समय.tv_nsec);
	ufs_inode->ui_mसमय = cpu_to_fs64(sb, inode->i_mसमय.tv_sec);
	ufs_inode->ui_mसमयnsec = cpu_to_fs32(sb, inode->i_mसमय.tv_nsec);

	ufs_inode->ui_blocks = cpu_to_fs64(sb, inode->i_blocks);
	ufs_inode->ui_flags = cpu_to_fs32(sb, ufsi->i_flags);
	ufs_inode->ui_gen = cpu_to_fs32(sb, inode->i_generation);

	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) अणु
		/* ufs_inode->ui_u2.ui_addr.ui_db[0] = cpu_to_fs32(sb, inode->i_rdev); */
		ufs_inode->ui_u2.ui_addr.ui_db[0] = ufsi->i_u1.u2_i_data[0];
	पूर्ण अन्यथा अगर (inode->i_blocks) अणु
		स_नकल(&ufs_inode->ui_u2.ui_addr, ufsi->i_u1.u2_i_data,
		       माप(ufs_inode->ui_u2.ui_addr));
	पूर्ण अन्यथा अणु
		स_नकल(&ufs_inode->ui_u2.ui_symlink, ufsi->i_u1.i_symlink,
		       माप(ufs_inode->ui_u2.ui_symlink));
 	पूर्ण

	अगर (!inode->i_nlink)
		स_रखो (ufs_inode, 0, माप(काष्ठा ufs2_inode));
	UFSD("EXIT\n");
पूर्ण

अटल पूर्णांक ufs_update_inode(काष्ठा inode * inode, पूर्णांक करो_sync)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	काष्ठा buffer_head * bh;

	UFSD("ENTER, ino %lu\n", inode->i_ino);

	अगर (inode->i_ino < UFS_ROOTINO ||
	    inode->i_ino > (uspi->s_ncg * uspi->s_ipg)) अणु
		ufs_warning (sb, "ufs_read_inode", "bad inode number (%lu)\n", inode->i_ino);
		वापस -1;
	पूर्ण

	bh = sb_bपढ़ो(sb, ufs_inotofsba(inode->i_ino));
	अगर (!bh) अणु
		ufs_warning (sb, "ufs_read_inode", "unable to read inode %lu\n", inode->i_ino);
		वापस -1;
	पूर्ण
	अगर (uspi->fs_magic == UFS2_MAGIC) अणु
		काष्ठा ufs2_inode *ufs2_inode = (काष्ठा ufs2_inode *)bh->b_data;

		ufs2_update_inode(inode,
				  ufs2_inode + ufs_inotofsbo(inode->i_ino));
	पूर्ण अन्यथा अणु
		काष्ठा ufs_inode *ufs_inode = (काष्ठा ufs_inode *) bh->b_data;

		ufs1_update_inode(inode, ufs_inode + ufs_inotofsbo(inode->i_ino));
	पूर्ण

	mark_buffer_dirty(bh);
	अगर (करो_sync)
		sync_dirty_buffer(bh);
	brअन्यथा (bh);

	UFSD("EXIT\n");
	वापस 0;
पूर्ण

पूर्णांक ufs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस ufs_update_inode(inode, wbc->sync_mode == WB_SYNC_ALL);
पूर्ण

पूर्णांक ufs_sync_inode (काष्ठा inode *inode)
अणु
	वापस ufs_update_inode (inode, 1);
पूर्ण

व्योम ufs_evict_inode(काष्ठा inode * inode)
अणु
	पूर्णांक want_delete = 0;

	अगर (!inode->i_nlink && !is_bad_inode(inode))
		want_delete = 1;

	truncate_inode_pages_final(&inode->i_data);
	अगर (want_delete) अणु
		inode->i_size = 0;
		अगर (inode->i_blocks &&
		    (S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
		     S_ISLNK(inode->i_mode)))
			ufs_truncate_blocks(inode);
		ufs_update_inode(inode, inode_needs_sync(inode));
	पूर्ण

	invalidate_inode_buffers(inode);
	clear_inode(inode);

	अगर (want_delete)
		ufs_मुक्त_inode(inode);
पूर्ण

काष्ठा to_मुक्त अणु
	काष्ठा inode *inode;
	u64 to;
	अचिन्हित count;
पूर्ण;

अटल अंतरभूत व्योम मुक्त_data(काष्ठा to_मुक्त *ctx, u64 from, अचिन्हित count)
अणु
	अगर (ctx->count && ctx->to != from) अणु
		ufs_मुक्त_blocks(ctx->inode, ctx->to - ctx->count, ctx->count);
		ctx->count = 0;
	पूर्ण
	ctx->count += count;
	ctx->to = from + count;
पूर्ण

#घोषणा सूचीECT_FRAGMENT ((inode->i_size + uspi->s_fsize - 1) >> uspi->s_fshअगरt)

अटल व्योम ufs_trunc_direct(काष्ठा inode *inode)
अणु
	काष्ठा ufs_inode_info *ufsi = UFS_I(inode);
	काष्ठा super_block * sb;
	काष्ठा ufs_sb_निजी_info * uspi;
	व्योम *p;
	u64 frag1, frag2, frag3, frag4, block1, block2;
	काष्ठा to_मुक्त ctx = अणु.inode = inodeपूर्ण;
	अचिन्हित i, पंचांगp;

	UFSD("ENTER: ino %lu\n", inode->i_ino);

	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;

	frag1 = सूचीECT_FRAGMENT;
	frag4 = min_t(u64, UFS_Nसूची_FRAGMENT, ufsi->i_lastfrag);
	frag2 = ((frag1 & uspi->s_fpbmask) ? ((frag1 | uspi->s_fpbmask) + 1) : frag1);
	frag3 = frag4 & ~uspi->s_fpbmask;
	block1 = block2 = 0;
	अगर (frag2 > frag3) अणु
		frag2 = frag4;
		frag3 = frag4 = 0;
	पूर्ण अन्यथा अगर (frag2 < frag3) अणु
		block1 = ufs_fragstoblks (frag2);
		block2 = ufs_fragstoblks (frag3);
	पूर्ण

	UFSD("ino %lu, frag1 %llu, frag2 %llu, block1 %llu, block2 %llu,"
	     " frag3 %llu, frag4 %llu\n", inode->i_ino,
	     (अचिन्हित दीर्घ दीर्घ)frag1, (अचिन्हित दीर्घ दीर्घ)frag2,
	     (अचिन्हित दीर्घ दीर्घ)block1, (अचिन्हित दीर्घ दीर्घ)block2,
	     (अचिन्हित दीर्घ दीर्घ)frag3, (अचिन्हित दीर्घ दीर्घ)frag4);

	अगर (frag1 >= frag2)
		जाओ next1;

	/*
	 * Free first मुक्त fragments
	 */
	p = ufs_get_direct_data_ptr(uspi, ufsi, ufs_fragstoblks(frag1));
	पंचांगp = ufs_data_ptr_to_cpu(sb, p);
	अगर (!पंचांगp )
		ufs_panic (sb, "ufs_trunc_direct", "internal error");
	frag2 -= frag1;
	frag1 = ufs_fragnum (frag1);

	ufs_मुक्त_fragments(inode, पंचांगp + frag1, frag2);

next1:
	/*
	 * Free whole blocks
	 */
	क्रम (i = block1 ; i < block2; i++) अणु
		p = ufs_get_direct_data_ptr(uspi, ufsi, i);
		पंचांगp = ufs_data_ptr_to_cpu(sb, p);
		अगर (!पंचांगp)
			जारी;
		ग_लिखो_seqlock(&ufsi->meta_lock);
		ufs_data_ptr_clear(uspi, p);
		ग_लिखो_sequnlock(&ufsi->meta_lock);

		मुक्त_data(&ctx, पंचांगp, uspi->s_fpb);
	पूर्ण

	मुक्त_data(&ctx, 0, 0);

	अगर (frag3 >= frag4)
		जाओ next3;

	/*
	 * Free last मुक्त fragments
	 */
	p = ufs_get_direct_data_ptr(uspi, ufsi, ufs_fragstoblks(frag3));
	पंचांगp = ufs_data_ptr_to_cpu(sb, p);
	अगर (!पंचांगp )
		ufs_panic(sb, "ufs_truncate_direct", "internal error");
	frag4 = ufs_fragnum (frag4);
	ग_लिखो_seqlock(&ufsi->meta_lock);
	ufs_data_ptr_clear(uspi, p);
	ग_लिखो_sequnlock(&ufsi->meta_lock);

	ufs_मुक्त_fragments (inode, पंचांगp, frag4);
 next3:

	UFSD("EXIT: ino %lu\n", inode->i_ino);
पूर्ण

अटल व्योम मुक्त_full_branch(काष्ठा inode *inode, u64 ind_block, पूर्णांक depth)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	काष्ठा ufs_buffer_head *ubh = ubh_bपढ़ो(sb, ind_block, uspi->s_bsize);
	अचिन्हित i;

	अगर (!ubh)
		वापस;

	अगर (--depth) अणु
		क्रम (i = 0; i < uspi->s_apb; i++) अणु
			व्योम *p = ubh_get_data_ptr(uspi, ubh, i);
			u64 block = ufs_data_ptr_to_cpu(sb, p);
			अगर (block)
				मुक्त_full_branch(inode, block, depth);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा to_मुक्त ctx = अणु.inode = inodeपूर्ण;

		क्रम (i = 0; i < uspi->s_apb; i++) अणु
			व्योम *p = ubh_get_data_ptr(uspi, ubh, i);
			u64 block = ufs_data_ptr_to_cpu(sb, p);
			अगर (block)
				मुक्त_data(&ctx, block, uspi->s_fpb);
		पूर्ण
		मुक्त_data(&ctx, 0, 0);
	पूर्ण

	ubh_bक्रमget(ubh);
	ufs_मुक्त_blocks(inode, ind_block, uspi->s_fpb);
पूर्ण

अटल व्योम मुक्त_branch_tail(काष्ठा inode *inode, अचिन्हित from, काष्ठा ufs_buffer_head *ubh, पूर्णांक depth)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	अचिन्हित i;

	अगर (--depth) अणु
		क्रम (i = from; i < uspi->s_apb ; i++) अणु
			व्योम *p = ubh_get_data_ptr(uspi, ubh, i);
			u64 block = ufs_data_ptr_to_cpu(sb, p);
			अगर (block) अणु
				ग_लिखो_seqlock(&UFS_I(inode)->meta_lock);
				ufs_data_ptr_clear(uspi, p);
				ग_लिखो_sequnlock(&UFS_I(inode)->meta_lock);
				ubh_mark_buffer_dirty(ubh);
				मुक्त_full_branch(inode, block, depth);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा to_मुक्त ctx = अणु.inode = inodeपूर्ण;

		क्रम (i = from; i < uspi->s_apb; i++) अणु
			व्योम *p = ubh_get_data_ptr(uspi, ubh, i);
			u64 block = ufs_data_ptr_to_cpu(sb, p);
			अगर (block) अणु
				ग_लिखो_seqlock(&UFS_I(inode)->meta_lock);
				ufs_data_ptr_clear(uspi, p);
				ग_लिखो_sequnlock(&UFS_I(inode)->meta_lock);
				ubh_mark_buffer_dirty(ubh);
				मुक्त_data(&ctx, block, uspi->s_fpb);
			पूर्ण
		पूर्ण
		मुक्त_data(&ctx, 0, 0);
	पूर्ण
	अगर (IS_SYNC(inode) && ubh_buffer_dirty(ubh))
		ubh_sync_block(ubh);
	ubh_brअन्यथा(ubh);
पूर्ण

अटल पूर्णांक ufs_alloc_lastblock(काष्ठा inode *inode, loff_t size)
अणु
	पूर्णांक err = 0;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	अचिन्हित i, end;
	sector_t lastfrag;
	काष्ठा page *lastpage;
	काष्ठा buffer_head *bh;
	u64 phys64;

	lastfrag = (size + uspi->s_fsize - 1) >> uspi->s_fshअगरt;

	अगर (!lastfrag)
		जाओ out;

	lastfrag--;

	lastpage = ufs_get_locked_page(mapping, lastfrag >>
				       (PAGE_SHIFT - inode->i_blkbits));
       अगर (IS_ERR(lastpage)) अणु
               err = -EIO;
               जाओ out;
       पूर्ण

       end = lastfrag & ((1 << (PAGE_SHIFT - inode->i_blkbits)) - 1);
       bh = page_buffers(lastpage);
       क्रम (i = 0; i < end; ++i)
               bh = bh->b_this_page;


       err = ufs_getfrag_block(inode, lastfrag, bh, 1);

       अगर (unlikely(err))
	       जाओ out_unlock;

       अगर (buffer_new(bh)) अणु
	       clear_buffer_new(bh);
	       clean_bdev_bh_alias(bh);
	       /*
		* we करो not zeroize fragment, because of
		* अगर it maped to hole, it alपढ़ोy contains zeroes
		*/
	       set_buffer_uptodate(bh);
	       mark_buffer_dirty(bh);
	       set_page_dirty(lastpage);
       पूर्ण

       अगर (lastfrag >= UFS_IND_FRAGMENT) अणु
	       end = uspi->s_fpb - ufs_fragnum(lastfrag) - 1;
	       phys64 = bh->b_blocknr + 1;
	       क्रम (i = 0; i < end; ++i) अणु
		       bh = sb_getblk(sb, i + phys64);
		       lock_buffer(bh);
		       स_रखो(bh->b_data, 0, sb->s_blocksize);
		       set_buffer_uptodate(bh);
		       mark_buffer_dirty(bh);
		       unlock_buffer(bh);
		       sync_dirty_buffer(bh);
		       brअन्यथा(bh);
	       पूर्ण
       पूर्ण
out_unlock:
       ufs_put_locked_page(lastpage);
out:
       वापस err;
पूर्ण

अटल व्योम ufs_truncate_blocks(काष्ठा inode *inode)
अणु
	काष्ठा ufs_inode_info *ufsi = UFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	अचिन्हित offsets[4];
	पूर्णांक depth;
	पूर्णांक depth2;
	अचिन्हित i;
	काष्ठा ufs_buffer_head *ubh[3];
	व्योम *p;
	u64 block;

	अगर (inode->i_size) अणु
		sector_t last = (inode->i_size - 1) >> uspi->s_bshअगरt;
		depth = ufs_block_to_path(inode, last, offsets);
		अगर (!depth)
			वापस;
	पूर्ण अन्यथा अणु
		depth = 1;
	पूर्ण

	क्रम (depth2 = depth - 1; depth2; depth2--)
		अगर (offsets[depth2] != uspi->s_apb - 1)
			अवरोध;

	mutex_lock(&ufsi->truncate_mutex);
	अगर (depth == 1) अणु
		ufs_trunc_direct(inode);
		offsets[0] = UFS_IND_BLOCK;
	पूर्ण अन्यथा अणु
		/* get the blocks that should be partially emptied */
		p = ufs_get_direct_data_ptr(uspi, ufsi, offsets[0]++);
		क्रम (i = 0; i < depth2; i++) अणु
			block = ufs_data_ptr_to_cpu(sb, p);
			अगर (!block)
				अवरोध;
			ubh[i] = ubh_bपढ़ो(sb, block, uspi->s_bsize);
			अगर (!ubh[i]) अणु
				ग_लिखो_seqlock(&ufsi->meta_lock);
				ufs_data_ptr_clear(uspi, p);
				ग_लिखो_sequnlock(&ufsi->meta_lock);
				अवरोध;
			पूर्ण
			p = ubh_get_data_ptr(uspi, ubh[i], offsets[i + 1]++);
		पूर्ण
		जबतक (i--)
			मुक्त_branch_tail(inode, offsets[i + 1], ubh[i], depth - i - 1);
	पूर्ण
	क्रम (i = offsets[0]; i <= UFS_TIND_BLOCK; i++) अणु
		p = ufs_get_direct_data_ptr(uspi, ufsi, i);
		block = ufs_data_ptr_to_cpu(sb, p);
		अगर (block) अणु
			ग_लिखो_seqlock(&ufsi->meta_lock);
			ufs_data_ptr_clear(uspi, p);
			ग_लिखो_sequnlock(&ufsi->meta_lock);
			मुक्त_full_branch(inode, block, i - UFS_IND_BLOCK + 1);
		पूर्ण
	पूर्ण
	पढ़ो_seqlock_excl(&ufsi->meta_lock);
	ufsi->i_lastfrag = सूचीECT_FRAGMENT;
	पढ़ो_sequnlock_excl(&ufsi->meta_lock);
	mark_inode_dirty(inode);
	mutex_unlock(&ufsi->truncate_mutex);
पूर्ण

अटल पूर्णांक ufs_truncate(काष्ठा inode *inode, loff_t size)
अणु
	पूर्णांक err = 0;

	UFSD("ENTER: ino %lu, i_size: %llu, old_i_size: %llu\n",
	     inode->i_ino, (अचिन्हित दीर्घ दीर्घ)size,
	     (अचिन्हित दीर्घ दीर्घ)i_size_पढ़ो(inode));

	अगर (!(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
	      S_ISLNK(inode->i_mode)))
		वापस -EINVAL;
	अगर (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		वापस -EPERM;

	err = ufs_alloc_lastblock(inode, size);

	अगर (err)
		जाओ out;

	block_truncate_page(inode->i_mapping, size, ufs_getfrag_block);

	truncate_setsize(inode, size);

	ufs_truncate_blocks(inode);
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
out:
	UFSD("EXIT: err %d\n", err);
	वापस err;
पूर्ण

पूर्णांक ufs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	अगर (ia_valid & ATTR_SIZE && attr->ia_size != inode->i_size) अणु
		error = ufs_truncate(inode, attr->ia_size);
		अगर (error)
			वापस error;
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations ufs_file_inode_operations = अणु
	.setattr = ufs_setattr,
पूर्ण;
