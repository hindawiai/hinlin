<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ufs/balloc.c
 *
 * Copyright (C) 1998
 * Daniel Pirkl <daniel.pirkl@email.cz>
 * Charles University, Faculty of Mathematics and Physics
 *
 * UFS2 ग_लिखो support Evgeniy Dushistov <dushistov@mail.ru>, 2007
 */

#समावेश <linux/fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/capability.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bपन.स>
#समावेश <यंत्र/byteorder.h>

#समावेश "ufs_fs.h"
#समावेश "ufs.h"
#समावेश "swab.h"
#समावेश "util.h"

#घोषणा INVBLOCK ((u64)-1L)

अटल u64 ufs_add_fragments(काष्ठा inode *, u64, अचिन्हित, अचिन्हित);
अटल u64 ufs_alloc_fragments(काष्ठा inode *, अचिन्हित, u64, अचिन्हित, पूर्णांक *);
अटल u64 ufs_alloccg_block(काष्ठा inode *, काष्ठा ufs_cg_निजी_info *, u64, पूर्णांक *);
अटल u64 ufs_biपंचांगap_search (काष्ठा super_block *, काष्ठा ufs_cg_निजी_info *, u64, अचिन्हित);
अटल अचिन्हित अक्षर ufs_fragtable_8fpb[], ufs_fragtable_other[];
अटल व्योम ufs_clusteracct(काष्ठा super_block *, काष्ठा ufs_cg_निजी_info *, अचिन्हित, पूर्णांक);

/*
 * Free 'count' fragments from fragment number 'fragment'
 */
व्योम ufs_मुक्त_fragments(काष्ठा inode *inode, u64 fragment, अचिन्हित count)
अणु
	काष्ठा super_block * sb;
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_cg_निजी_info * ucpi;
	काष्ठा ufs_cylinder_group * ucg;
	अचिन्हित cgno, bit, end_bit, bbase, blkmap, i;
	u64 blkno;
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	
	UFSD("ENTER, fragment %llu, count %u\n",
	     (अचिन्हित दीर्घ दीर्घ)fragment, count);
	
	अगर (ufs_fragnum(fragment) + count > uspi->s_fpg)
		ufs_error (sb, "ufs_free_fragments", "internal error");

	mutex_lock(&UFS_SB(sb)->s_lock);
	
	cgno = ufs_dtog(uspi, fragment);
	bit = ufs_dtogd(uspi, fragment);
	अगर (cgno >= uspi->s_ncg) अणु
		ufs_panic (sb, "ufs_free_fragments", "freeing blocks are outside device");
		जाओ failed;
	पूर्ण
		
	ucpi = ufs_load_cylinder (sb, cgno);
	अगर (!ucpi) 
		जाओ failed;
	ucg = ubh_get_ucg (UCPI_UBH(ucpi));
	अगर (!ufs_cg_chkmagic(sb, ucg)) अणु
		ufs_panic (sb, "ufs_free_fragments", "internal error, bad magic number on cg %u", cgno);
		जाओ failed;
	पूर्ण

	end_bit = bit + count;
	bbase = ufs_blknum (bit);
	blkmap = ubh_blkmap (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, bbase);
	ufs_fragacct (sb, blkmap, ucg->cg_frsum, -1);
	क्रम (i = bit; i < end_bit; i++) अणु
		अगर (ubh_isclr (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, i))
			ubh_setbit (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, i);
		अन्यथा 
			ufs_error (sb, "ufs_free_fragments",
				   "bit already cleared for fragment %u", i);
	पूर्ण

	inode_sub_bytes(inode, count << uspi->s_fshअगरt);
	fs32_add(sb, &ucg->cg_cs.cs_nfमुक्त, count);
	uspi->cs_total.cs_nfमुक्त += count;
	fs32_add(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nfमुक्त, count);
	blkmap = ubh_blkmap (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, bbase);
	ufs_fragacct(sb, blkmap, ucg->cg_frsum, 1);

	/*
	 * Trying to reassemble मुक्त fragments पूर्णांकo block
	 */
	blkno = ufs_fragstoblks (bbase);
	अगर (ubh_isblockset(UCPI_UBH(ucpi), ucpi->c_मुक्तoff, blkno)) अणु
		fs32_sub(sb, &ucg->cg_cs.cs_nfमुक्त, uspi->s_fpb);
		uspi->cs_total.cs_nfमुक्त -= uspi->s_fpb;
		fs32_sub(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nfमुक्त, uspi->s_fpb);
		अगर ((UFS_SB(sb)->s_flags & UFS_CG_MASK) == UFS_CG_44BSD)
			ufs_clusteracct (sb, ucpi, blkno, 1);
		fs32_add(sb, &ucg->cg_cs.cs_nbमुक्त, 1);
		uspi->cs_total.cs_nbमुक्त++;
		fs32_add(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nbमुक्त, 1);
		अगर (uspi->fs_magic != UFS2_MAGIC) अणु
			अचिन्हित cylno = ufs_cbtocylno (bbase);

			fs16_add(sb, &ubh_cg_blks(ucpi, cylno,
						  ufs_cbtorpos(bbase)), 1);
			fs32_add(sb, &ubh_cg_blktot(ucpi, cylno), 1);
		पूर्ण
	पूर्ण
	
	ubh_mark_buffer_dirty (USPI_UBH(uspi));
	ubh_mark_buffer_dirty (UCPI_UBH(ucpi));
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		ubh_sync_block(UCPI_UBH(ucpi));
	ufs_mark_sb_dirty(sb);

	mutex_unlock(&UFS_SB(sb)->s_lock);
	UFSD("EXIT\n");
	वापस;

failed:
	mutex_unlock(&UFS_SB(sb)->s_lock);
	UFSD("EXIT (FAILED)\n");
	वापस;
पूर्ण

/*
 * Free 'count' fragments from fragment number 'fragment' (मुक्त whole blocks)
 */
व्योम ufs_मुक्त_blocks(काष्ठा inode *inode, u64 fragment, अचिन्हित count)
अणु
	काष्ठा super_block * sb;
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_cg_निजी_info * ucpi;
	काष्ठा ufs_cylinder_group * ucg;
	अचिन्हित overflow, cgno, bit, end_bit, i;
	u64 blkno;
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;

	UFSD("ENTER, fragment %llu, count %u\n",
	     (अचिन्हित दीर्घ दीर्घ)fragment, count);
	
	अगर ((fragment & uspi->s_fpbmask) || (count & uspi->s_fpbmask)) अणु
		ufs_error (sb, "ufs_free_blocks", "internal error, "
			   "fragment %llu, count %u\n",
			   (अचिन्हित दीर्घ दीर्घ)fragment, count);
		जाओ failed;
	पूर्ण

	mutex_lock(&UFS_SB(sb)->s_lock);
	
करो_more:
	overflow = 0;
	cgno = ufs_dtog(uspi, fragment);
	bit = ufs_dtogd(uspi, fragment);
	अगर (cgno >= uspi->s_ncg) अणु
		ufs_panic (sb, "ufs_free_blocks", "freeing blocks are outside device");
		जाओ failed_unlock;
	पूर्ण
	end_bit = bit + count;
	अगर (end_bit > uspi->s_fpg) अणु
		overflow = bit + count - uspi->s_fpg;
		count -= overflow;
		end_bit -= overflow;
	पूर्ण

	ucpi = ufs_load_cylinder (sb, cgno);
	अगर (!ucpi) 
		जाओ failed_unlock;
	ucg = ubh_get_ucg (UCPI_UBH(ucpi));
	अगर (!ufs_cg_chkmagic(sb, ucg)) अणु
		ufs_panic (sb, "ufs_free_blocks", "internal error, bad magic number on cg %u", cgno);
		जाओ failed_unlock;
	पूर्ण

	क्रम (i = bit; i < end_bit; i += uspi->s_fpb) अणु
		blkno = ufs_fragstoblks(i);
		अगर (ubh_isblockset(UCPI_UBH(ucpi), ucpi->c_मुक्तoff, blkno)) अणु
			ufs_error(sb, "ufs_free_blocks", "freeing free fragment");
		पूर्ण
		ubh_setblock(UCPI_UBH(ucpi), ucpi->c_मुक्तoff, blkno);
		inode_sub_bytes(inode, uspi->s_fpb << uspi->s_fshअगरt);
		अगर ((UFS_SB(sb)->s_flags & UFS_CG_MASK) == UFS_CG_44BSD)
			ufs_clusteracct (sb, ucpi, blkno, 1);

		fs32_add(sb, &ucg->cg_cs.cs_nbमुक्त, 1);
		uspi->cs_total.cs_nbमुक्त++;
		fs32_add(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nbमुक्त, 1);

		अगर (uspi->fs_magic != UFS2_MAGIC) अणु
			अचिन्हित cylno = ufs_cbtocylno(i);

			fs16_add(sb, &ubh_cg_blks(ucpi, cylno,
						  ufs_cbtorpos(i)), 1);
			fs32_add(sb, &ubh_cg_blktot(ucpi, cylno), 1);
		पूर्ण
	पूर्ण

	ubh_mark_buffer_dirty (USPI_UBH(uspi));
	ubh_mark_buffer_dirty (UCPI_UBH(ucpi));
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		ubh_sync_block(UCPI_UBH(ucpi));

	अगर (overflow) अणु
		fragment += count;
		count = overflow;
		जाओ करो_more;
	पूर्ण

	ufs_mark_sb_dirty(sb);
	mutex_unlock(&UFS_SB(sb)->s_lock);
	UFSD("EXIT\n");
	वापस;

failed_unlock:
	mutex_unlock(&UFS_SB(sb)->s_lock);
failed:
	UFSD("EXIT (FAILED)\n");
	वापस;
पूर्ण

/*
 * Modअगरy inode page cache in such way:
 * have - blocks with b_blocknr equal to oldb...oldb+count-1
 * get - blocks with b_blocknr equal to newb...newb+count-1
 * also we suppose that oldb...oldb+count-1 blocks
 * situated at the end of file.
 *
 * We can come here from ufs_ग_लिखोpage or ufs_prepare_ग_लिखो,
 * locked_page is argument of these functions, so we alपढ़ोy lock it.
 */
अटल व्योम ufs_change_blocknr(काष्ठा inode *inode, sector_t beg,
			       अचिन्हित पूर्णांक count, sector_t oldb,
			       sector_t newb, काष्ठा page *locked_page)
अणु
	स्थिर अचिन्हित blks_per_page =
		1 << (PAGE_SHIFT - inode->i_blkbits);
	स्थिर अचिन्हित mask = blks_per_page - 1;
	काष्ठा address_space * स्थिर mapping = inode->i_mapping;
	pgoff_t index, cur_index, last_index;
	अचिन्हित pos, j, lblock;
	sector_t end, i;
	काष्ठा page *page;
	काष्ठा buffer_head *head, *bh;

	UFSD("ENTER, ino %lu, count %u, oldb %llu, newb %llu\n",
	      inode->i_ino, count,
	     (अचिन्हित दीर्घ दीर्घ)oldb, (अचिन्हित दीर्घ दीर्घ)newb);

	BUG_ON(!locked_page);
	BUG_ON(!PageLocked(locked_page));

	cur_index = locked_page->index;
	end = count + beg;
	last_index = end >> (PAGE_SHIFT - inode->i_blkbits);
	क्रम (i = beg; i < end; i = (i | mask) + 1) अणु
		index = i >> (PAGE_SHIFT - inode->i_blkbits);

		अगर (likely(cur_index != index)) अणु
			page = ufs_get_locked_page(mapping, index);
			अगर (!page)/* it was truncated */
				जारी;
			अगर (IS_ERR(page)) अणु/* or EIO */
				ufs_error(inode->i_sb, __func__,
					  "read of page %llu failed\n",
					  (अचिन्हित दीर्घ दीर्घ)index);
				जारी;
			पूर्ण
		पूर्ण अन्यथा
			page = locked_page;

		head = page_buffers(page);
		bh = head;
		pos = i & mask;
		क्रम (j = 0; j < pos; ++j)
			bh = bh->b_this_page;


		अगर (unlikely(index == last_index))
			lblock = end & mask;
		अन्यथा
			lblock = blks_per_page;

		करो अणु
			अगर (j >= lblock)
				अवरोध;
			pos = (i - beg) + j;

			अगर (!buffer_mapped(bh))
					map_bh(bh, inode->i_sb, oldb + pos);
			अगर (!buffer_uptodate(bh)) अणु
				ll_rw_block(REQ_OP_READ, 0, 1, &bh);
				रुको_on_buffer(bh);
				अगर (!buffer_uptodate(bh)) अणु
					ufs_error(inode->i_sb, __func__,
						  "read of block failed\n");
					अवरोध;
				पूर्ण
			पूर्ण

			UFSD(" change from %llu to %llu, pos %u\n",
			     (अचिन्हित दीर्घ दीर्घ)(pos + oldb),
			     (अचिन्हित दीर्घ दीर्घ)(pos + newb), pos);

			bh->b_blocknr = newb + pos;
			clean_bdev_bh_alias(bh);
			mark_buffer_dirty(bh);
			++j;
			bh = bh->b_this_page;
		पूर्ण जबतक (bh != head);

		अगर (likely(cur_index != index))
			ufs_put_locked_page(page);
 	पूर्ण
	UFSD("EXIT\n");
पूर्ण

अटल व्योम ufs_clear_frags(काष्ठा inode *inode, sector_t beg, अचिन्हित पूर्णांक n,
			    पूर्णांक sync)
अणु
	काष्ठा buffer_head *bh;
	sector_t end = beg + n;

	क्रम (; beg < end; ++beg) अणु
		bh = sb_getblk(inode->i_sb, beg);
		lock_buffer(bh);
		स_रखो(bh->b_data, 0, inode->i_sb->s_blocksize);
		set_buffer_uptodate(bh);
		mark_buffer_dirty(bh);
		unlock_buffer(bh);
		अगर (IS_SYNC(inode) || sync)
			sync_dirty_buffer(bh);
		brअन्यथा(bh);
	पूर्ण
पूर्ण

u64 ufs_new_fragments(काष्ठा inode *inode, व्योम *p, u64 fragment,
			   u64 goal, अचिन्हित count, पूर्णांक *err,
			   काष्ठा page *locked_page)
अणु
	काष्ठा super_block * sb;
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_super_block_first * usb1;
	अचिन्हित cgno, oldcount, newcount;
	u64 पंचांगp, request, result;
	
	UFSD("ENTER, ino %lu, fragment %llu, goal %llu, count %u\n",
	     inode->i_ino, (अचिन्हित दीर्घ दीर्घ)fragment,
	     (अचिन्हित दीर्घ दीर्घ)goal, count);
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	usb1 = ubh_get_usb_first(uspi);
	*err = -ENOSPC;

	mutex_lock(&UFS_SB(sb)->s_lock);
	पंचांगp = ufs_data_ptr_to_cpu(sb, p);

	अगर (count + ufs_fragnum(fragment) > uspi->s_fpb) अणु
		ufs_warning(sb, "ufs_new_fragments", "internal warning"
			    " fragment %llu, count %u",
			    (अचिन्हित दीर्घ दीर्घ)fragment, count);
		count = uspi->s_fpb - ufs_fragnum(fragment); 
	पूर्ण
	oldcount = ufs_fragnum (fragment);
	newcount = oldcount + count;

	/*
	 * Somebody अन्यथा has just allocated our fragments
	 */
	अगर (oldcount) अणु
		अगर (!पंचांगp) अणु
			ufs_error(sb, "ufs_new_fragments", "internal error, "
				  "fragment %llu, tmp %llu\n",
				  (अचिन्हित दीर्घ दीर्घ)fragment,
				  (अचिन्हित दीर्घ दीर्घ)पंचांगp);
			mutex_unlock(&UFS_SB(sb)->s_lock);
			वापस INVBLOCK;
		पूर्ण
		अगर (fragment < UFS_I(inode)->i_lastfrag) अणु
			UFSD("EXIT (ALREADY ALLOCATED)\n");
			mutex_unlock(&UFS_SB(sb)->s_lock);
			वापस 0;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		अगर (पंचांगp) अणु
			UFSD("EXIT (ALREADY ALLOCATED)\n");
			mutex_unlock(&UFS_SB(sb)->s_lock);
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * There is not enough space क्रम user on the device
	 */
	अगर (unlikely(ufs_मुक्तfrags(uspi) <= uspi->s_root_blocks)) अणु
		अगर (!capable(CAP_SYS_RESOURCE)) अणु
			mutex_unlock(&UFS_SB(sb)->s_lock);
			UFSD("EXIT (FAILED)\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (goal >= uspi->s_size) 
		goal = 0;
	अगर (goal == 0) 
		cgno = ufs_inotocg (inode->i_ino);
	अन्यथा
		cgno = ufs_dtog(uspi, goal);
	 
	/*
	 * allocate new fragment
	 */
	अगर (oldcount == 0) अणु
		result = ufs_alloc_fragments (inode, cgno, goal, count, err);
		अगर (result) अणु
			ufs_clear_frags(inode, result + oldcount,
					newcount - oldcount, locked_page != शून्य);
			*err = 0;
			ग_लिखो_seqlock(&UFS_I(inode)->meta_lock);
			ufs_cpu_to_data_ptr(sb, p, result);
			UFS_I(inode)->i_lastfrag =
				max(UFS_I(inode)->i_lastfrag, fragment + count);
			ग_लिखो_sequnlock(&UFS_I(inode)->meta_lock);
		पूर्ण
		mutex_unlock(&UFS_SB(sb)->s_lock);
		UFSD("EXIT, result %llu\n", (अचिन्हित दीर्घ दीर्घ)result);
		वापस result;
	पूर्ण

	/*
	 * resize block
	 */
	result = ufs_add_fragments(inode, पंचांगp, oldcount, newcount);
	अगर (result) अणु
		*err = 0;
		पढ़ो_seqlock_excl(&UFS_I(inode)->meta_lock);
		UFS_I(inode)->i_lastfrag = max(UFS_I(inode)->i_lastfrag,
						fragment + count);
		पढ़ो_sequnlock_excl(&UFS_I(inode)->meta_lock);
		ufs_clear_frags(inode, result + oldcount, newcount - oldcount,
				locked_page != शून्य);
		mutex_unlock(&UFS_SB(sb)->s_lock);
		UFSD("EXIT, result %llu\n", (अचिन्हित दीर्घ दीर्घ)result);
		वापस result;
	पूर्ण

	/*
	 * allocate new block and move data
	 */
	अगर (fs32_to_cpu(sb, usb1->fs_optim) == UFS_OPTSPACE) अणु
		request = newcount;
		अगर (uspi->cs_total.cs_nfमुक्त < uspi->s_space_to_समय)
			usb1->fs_optim = cpu_to_fs32(sb, UFS_OPTTIME);
	पूर्ण अन्यथा अणु
		request = uspi->s_fpb;
		अगर (uspi->cs_total.cs_nfमुक्त > uspi->s_समय_प्रकारo_space)
			usb1->fs_optim = cpu_to_fs32(sb, UFS_OPTSPACE);
	पूर्ण
	result = ufs_alloc_fragments (inode, cgno, goal, request, err);
	अगर (result) अणु
		ufs_clear_frags(inode, result + oldcount, newcount - oldcount,
				locked_page != शून्य);
		mutex_unlock(&UFS_SB(sb)->s_lock);
		ufs_change_blocknr(inode, fragment - oldcount, oldcount,
				   uspi->s_sbbase + पंचांगp,
				   uspi->s_sbbase + result, locked_page);
		*err = 0;
		ग_लिखो_seqlock(&UFS_I(inode)->meta_lock);
		ufs_cpu_to_data_ptr(sb, p, result);
		UFS_I(inode)->i_lastfrag = max(UFS_I(inode)->i_lastfrag,
						fragment + count);
		ग_लिखो_sequnlock(&UFS_I(inode)->meta_lock);
		अगर (newcount < request)
			ufs_मुक्त_fragments (inode, result + newcount, request - newcount);
		ufs_मुक्त_fragments (inode, पंचांगp, oldcount);
		UFSD("EXIT, result %llu\n", (अचिन्हित दीर्घ दीर्घ)result);
		वापस result;
	पूर्ण

	mutex_unlock(&UFS_SB(sb)->s_lock);
	UFSD("EXIT (FAILED)\n");
	वापस 0;
पूर्ण		

अटल bool try_add_frags(काष्ठा inode *inode, अचिन्हित frags)
अणु
	अचिन्हित size = frags * i_blocksize(inode);
	spin_lock(&inode->i_lock);
	__inode_add_bytes(inode, size);
	अगर (unlikely((u32)inode->i_blocks != inode->i_blocks)) अणु
		__inode_sub_bytes(inode, size);
		spin_unlock(&inode->i_lock);
		वापस false;
	पूर्ण
	spin_unlock(&inode->i_lock);
	वापस true;
पूर्ण

अटल u64 ufs_add_fragments(काष्ठा inode *inode, u64 fragment,
			     अचिन्हित oldcount, अचिन्हित newcount)
अणु
	काष्ठा super_block * sb;
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_cg_निजी_info * ucpi;
	काष्ठा ufs_cylinder_group * ucg;
	अचिन्हित cgno, fragno, fragoff, count, fragsize, i;
	
	UFSD("ENTER, fragment %llu, oldcount %u, newcount %u\n",
	     (अचिन्हित दीर्घ दीर्घ)fragment, oldcount, newcount);
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	count = newcount - oldcount;
	
	cgno = ufs_dtog(uspi, fragment);
	अगर (fs32_to_cpu(sb, UFS_SB(sb)->fs_cs(cgno).cs_nfमुक्त) < count)
		वापस 0;
	अगर ((ufs_fragnum (fragment) + newcount) > uspi->s_fpb)
		वापस 0;
	ucpi = ufs_load_cylinder (sb, cgno);
	अगर (!ucpi)
		वापस 0;
	ucg = ubh_get_ucg (UCPI_UBH(ucpi));
	अगर (!ufs_cg_chkmagic(sb, ucg)) अणु
		ufs_panic (sb, "ufs_add_fragments",
			"internal error, bad magic number on cg %u", cgno);
		वापस 0;
	पूर्ण

	fragno = ufs_dtogd(uspi, fragment);
	fragoff = ufs_fragnum (fragno);
	क्रम (i = oldcount; i < newcount; i++)
		अगर (ubh_isclr (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, fragno + i))
			वापस 0;

	अगर (!try_add_frags(inode, count))
		वापस 0;
	/*
	 * Block can be extended
	 */
	ucg->cg_समय = ufs_get_seconds(sb);
	क्रम (i = newcount; i < (uspi->s_fpb - fragoff); i++)
		अगर (ubh_isclr (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, fragno + i))
			अवरोध;
	fragsize = i - oldcount;
	अगर (!fs32_to_cpu(sb, ucg->cg_frsum[fragsize]))
		ufs_panic (sb, "ufs_add_fragments",
			"internal error or corrupted bitmap on cg %u", cgno);
	fs32_sub(sb, &ucg->cg_frsum[fragsize], 1);
	अगर (fragsize != count)
		fs32_add(sb, &ucg->cg_frsum[fragsize - count], 1);
	क्रम (i = oldcount; i < newcount; i++)
		ubh_clrbit (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, fragno + i);

	fs32_sub(sb, &ucg->cg_cs.cs_nfमुक्त, count);
	fs32_sub(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nfमुक्त, count);
	uspi->cs_total.cs_nfमुक्त -= count;
	
	ubh_mark_buffer_dirty (USPI_UBH(uspi));
	ubh_mark_buffer_dirty (UCPI_UBH(ucpi));
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		ubh_sync_block(UCPI_UBH(ucpi));
	ufs_mark_sb_dirty(sb);

	UFSD("EXIT, fragment %llu\n", (अचिन्हित दीर्घ दीर्घ)fragment);
	
	वापस fragment;
पूर्ण

#घोषणा UFS_TEST_FREE_SPACE_CG \
	ucg = (काष्ठा ufs_cylinder_group *) UFS_SB(sb)->s_ucg[cgno]->b_data; \
	अगर (fs32_to_cpu(sb, ucg->cg_cs.cs_nbमुक्त)) \
		जाओ cg_found; \
	क्रम (k = count; k < uspi->s_fpb; k++) \
		अगर (fs32_to_cpu(sb, ucg->cg_frsum[k])) \
			जाओ cg_found; 

अटल u64 ufs_alloc_fragments(काष्ठा inode *inode, अचिन्हित cgno,
			       u64 goal, अचिन्हित count, पूर्णांक *err)
अणु
	काष्ठा super_block * sb;
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_cg_निजी_info * ucpi;
	काष्ठा ufs_cylinder_group * ucg;
	अचिन्हित oldcg, i, j, k, allocsize;
	u64 result;
	
	UFSD("ENTER, ino %lu, cgno %u, goal %llu, count %u\n",
	     inode->i_ino, cgno, (अचिन्हित दीर्घ दीर्घ)goal, count);

	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	oldcg = cgno;
	
	/*
	 * 1. searching on preferred cylinder group
	 */
	UFS_TEST_FREE_SPACE_CG

	/*
	 * 2. quadratic rehash
	 */
	क्रम (j = 1; j < uspi->s_ncg; j *= 2) अणु
		cgno += j;
		अगर (cgno >= uspi->s_ncg) 
			cgno -= uspi->s_ncg;
		UFS_TEST_FREE_SPACE_CG
	पूर्ण

	/*
	 * 3. brute क्रमce search
	 * We start at i = 2 ( 0 is checked at 1.step, 1 at 2.step )
	 */
	cgno = (oldcg + 1) % uspi->s_ncg;
	क्रम (j = 2; j < uspi->s_ncg; j++) अणु
		cgno++;
		अगर (cgno >= uspi->s_ncg)
			cgno = 0;
		UFS_TEST_FREE_SPACE_CG
	पूर्ण
	
	UFSD("EXIT (FAILED)\n");
	वापस 0;

cg_found:
	ucpi = ufs_load_cylinder (sb, cgno);
	अगर (!ucpi)
		वापस 0;
	ucg = ubh_get_ucg (UCPI_UBH(ucpi));
	अगर (!ufs_cg_chkmagic(sb, ucg)) 
		ufs_panic (sb, "ufs_alloc_fragments",
			"internal error, bad magic number on cg %u", cgno);
	ucg->cg_समय = ufs_get_seconds(sb);

	अगर (count == uspi->s_fpb) अणु
		result = ufs_alloccg_block (inode, ucpi, goal, err);
		अगर (result == INVBLOCK)
			वापस 0;
		जाओ succed;
	पूर्ण

	क्रम (allocsize = count; allocsize < uspi->s_fpb; allocsize++)
		अगर (fs32_to_cpu(sb, ucg->cg_frsum[allocsize]) != 0)
			अवरोध;
	
	अगर (allocsize == uspi->s_fpb) अणु
		result = ufs_alloccg_block (inode, ucpi, goal, err);
		अगर (result == INVBLOCK)
			वापस 0;
		goal = ufs_dtogd(uspi, result);
		क्रम (i = count; i < uspi->s_fpb; i++)
			ubh_setbit (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, goal + i);
		i = uspi->s_fpb - count;

		inode_sub_bytes(inode, i << uspi->s_fshअगरt);
		fs32_add(sb, &ucg->cg_cs.cs_nfमुक्त, i);
		uspi->cs_total.cs_nfमुक्त += i;
		fs32_add(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nfमुक्त, i);
		fs32_add(sb, &ucg->cg_frsum[i], 1);
		जाओ succed;
	पूर्ण

	result = ufs_biपंचांगap_search (sb, ucpi, goal, allocsize);
	अगर (result == INVBLOCK)
		वापस 0;
	अगर (!try_add_frags(inode, count))
		वापस 0;
	क्रम (i = 0; i < count; i++)
		ubh_clrbit (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, result + i);
	
	fs32_sub(sb, &ucg->cg_cs.cs_nfमुक्त, count);
	uspi->cs_total.cs_nfमुक्त -= count;
	fs32_sub(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nfमुक्त, count);
	fs32_sub(sb, &ucg->cg_frsum[allocsize], 1);

	अगर (count != allocsize)
		fs32_add(sb, &ucg->cg_frsum[allocsize - count], 1);

succed:
	ubh_mark_buffer_dirty (USPI_UBH(uspi));
	ubh_mark_buffer_dirty (UCPI_UBH(ucpi));
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		ubh_sync_block(UCPI_UBH(ucpi));
	ufs_mark_sb_dirty(sb);

	result += cgno * uspi->s_fpg;
	UFSD("EXIT3, result %llu\n", (अचिन्हित दीर्घ दीर्घ)result);
	वापस result;
पूर्ण

अटल u64 ufs_alloccg_block(काष्ठा inode *inode,
			     काष्ठा ufs_cg_निजी_info *ucpi,
			     u64 goal, पूर्णांक *err)
अणु
	काष्ठा super_block * sb;
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_cylinder_group * ucg;
	u64 result, blkno;

	UFSD("ENTER, goal %llu\n", (अचिन्हित दीर्घ दीर्घ)goal);

	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	ucg = ubh_get_ucg(UCPI_UBH(ucpi));

	अगर (goal == 0) अणु
		goal = ucpi->c_rotor;
		जाओ norot;
	पूर्ण
	goal = ufs_blknum (goal);
	goal = ufs_dtogd(uspi, goal);
	
	/*
	 * If the requested block is available, use it.
	 */
	अगर (ubh_isblockset(UCPI_UBH(ucpi), ucpi->c_मुक्तoff, ufs_fragstoblks(goal))) अणु
		result = goal;
		जाओ gotit;
	पूर्ण
	
norot:	
	result = ufs_biपंचांगap_search (sb, ucpi, goal, uspi->s_fpb);
	अगर (result == INVBLOCK)
		वापस INVBLOCK;
	ucpi->c_rotor = result;
gotit:
	अगर (!try_add_frags(inode, uspi->s_fpb))
		वापस 0;
	blkno = ufs_fragstoblks(result);
	ubh_clrblock (UCPI_UBH(ucpi), ucpi->c_मुक्तoff, blkno);
	अगर ((UFS_SB(sb)->s_flags & UFS_CG_MASK) == UFS_CG_44BSD)
		ufs_clusteracct (sb, ucpi, blkno, -1);

	fs32_sub(sb, &ucg->cg_cs.cs_nbमुक्त, 1);
	uspi->cs_total.cs_nbमुक्त--;
	fs32_sub(sb, &UFS_SB(sb)->fs_cs(ucpi->c_cgx).cs_nbमुक्त, 1);

	अगर (uspi->fs_magic != UFS2_MAGIC) अणु
		अचिन्हित cylno = ufs_cbtocylno((अचिन्हित)result);

		fs16_sub(sb, &ubh_cg_blks(ucpi, cylno,
					  ufs_cbtorpos((अचिन्हित)result)), 1);
		fs32_sub(sb, &ubh_cg_blktot(ucpi, cylno), 1);
	पूर्ण
	
	UFSD("EXIT, result %llu\n", (अचिन्हित दीर्घ दीर्घ)result);

	वापस result;
पूर्ण

अटल अचिन्हित ubh_scanc(काष्ठा ufs_sb_निजी_info *uspi,
			  काष्ठा ufs_buffer_head *ubh,
			  अचिन्हित begin, अचिन्हित size,
			  अचिन्हित अक्षर *table, अचिन्हित अक्षर mask)
अणु
	अचिन्हित rest, offset;
	अचिन्हित अक्षर *cp;
	

	offset = begin & ~uspi->s_fmask;
	begin >>= uspi->s_fshअगरt;
	क्रम (;;) अणु
		अगर ((offset + size) < uspi->s_fsize)
			rest = size;
		अन्यथा
			rest = uspi->s_fsize - offset;
		size -= rest;
		cp = ubh->bh[begin]->b_data + offset;
		जबतक ((table[*cp++] & mask) == 0 && --rest)
			;
		अगर (rest || !size)
			अवरोध;
		begin++;
		offset = 0;
	पूर्ण
	वापस (size + rest);
पूर्ण

/*
 * Find a block of the specअगरied size in the specअगरied cylinder group.
 * @sp: poपूर्णांकer to super block
 * @ucpi: poपूर्णांकer to cylinder group info
 * @goal: near which block we want find new one
 * @count: specअगरied size
 */
अटल u64 ufs_biपंचांगap_search(काष्ठा super_block *sb,
			     काष्ठा ufs_cg_निजी_info *ucpi,
			     u64 goal, अचिन्हित count)
अणु
	/*
	 * Bit patterns क्रम identअगरying fragments in the block map
	 * used as ((map & mask_arr) == want_arr)
	 */
	अटल स्थिर पूर्णांक mask_arr[9] = अणु
		0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x1ff, 0x3ff
	पूर्ण;
	अटल स्थिर पूर्णांक want_arr[9] = अणु
		0x0, 0x2, 0x6, 0xe, 0x1e, 0x3e, 0x7e, 0xfe, 0x1fe
	पूर्ण;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	अचिन्हित start, length, loc;
	अचिन्हित pos, want, blockmap, mask, end;
	u64 result;

	UFSD("ENTER, cg %u, goal %llu, count %u\n", ucpi->c_cgx,
	     (अचिन्हित दीर्घ दीर्घ)goal, count);

	अगर (goal)
		start = ufs_dtogd(uspi, goal) >> 3;
	अन्यथा
		start = ucpi->c_frotor >> 3;
		
	length = ((uspi->s_fpg + 7) >> 3) - start;
	loc = ubh_scanc(uspi, UCPI_UBH(ucpi), ucpi->c_मुक्तoff + start, length,
		(uspi->s_fpb == 8) ? ufs_fragtable_8fpb : ufs_fragtable_other,
		1 << (count - 1 + (uspi->s_fpb & 7))); 
	अगर (loc == 0) अणु
		length = start + 1;
		loc = ubh_scanc(uspi, UCPI_UBH(ucpi), ucpi->c_मुक्तoff, length,
				(uspi->s_fpb == 8) ? ufs_fragtable_8fpb :
				ufs_fragtable_other,
				1 << (count - 1 + (uspi->s_fpb & 7)));
		अगर (loc == 0) अणु
			ufs_error(sb, "ufs_bitmap_search",
				  "bitmap corrupted on cg %u, start %u,"
				  " length %u, count %u, freeoff %u\n",
				  ucpi->c_cgx, start, length, count,
				  ucpi->c_मुक्तoff);
			वापस INVBLOCK;
		पूर्ण
		start = 0;
	पूर्ण
	result = (start + length - loc) << 3;
	ucpi->c_frotor = result;

	/*
	 * found the byte in the map
	 */

	क्रम (end = result + 8; result < end; result += uspi->s_fpb) अणु
		blockmap = ubh_blkmap(UCPI_UBH(ucpi), ucpi->c_मुक्तoff, result);
		blockmap <<= 1;
		mask = mask_arr[count];
		want = want_arr[count];
		क्रम (pos = 0; pos <= uspi->s_fpb - count; pos++) अणु
			अगर ((blockmap & mask) == want) अणु
				UFSD("EXIT, result %llu\n",
				     (अचिन्हित दीर्घ दीर्घ)result);
				वापस result + pos;
 			पूर्ण
			mask <<= 1;
			want <<= 1;
 		पूर्ण
 	पूर्ण

	ufs_error(sb, "ufs_bitmap_search", "block not in map on cg %u\n",
		  ucpi->c_cgx);
	UFSD("EXIT (FAILED)\n");
	वापस INVBLOCK;
पूर्ण

अटल व्योम ufs_clusteracct(काष्ठा super_block * sb,
	काष्ठा ufs_cg_निजी_info * ucpi, अचिन्हित blkno, पूर्णांक cnt)
अणु
	काष्ठा ufs_sb_निजी_info * uspi;
	पूर्णांक i, start, end, क्रमw, back;
	
	uspi = UFS_SB(sb)->s_uspi;
	अगर (uspi->s_contigsumsize <= 0)
		वापस;

	अगर (cnt > 0)
		ubh_setbit(UCPI_UBH(ucpi), ucpi->c_clusteroff, blkno);
	अन्यथा
		ubh_clrbit(UCPI_UBH(ucpi), ucpi->c_clusteroff, blkno);

	/*
	 * Find the size of the cluster going क्रमward.
	 */
	start = blkno + 1;
	end = start + uspi->s_contigsumsize;
	अगर ( end >= ucpi->c_nclusterblks)
		end = ucpi->c_nclusterblks;
	i = ubh_find_next_zero_bit (UCPI_UBH(ucpi), ucpi->c_clusteroff, end, start);
	अगर (i > end)
		i = end;
	क्रमw = i - start;
	
	/*
	 * Find the size of the cluster going backward.
	 */
	start = blkno - 1;
	end = start - uspi->s_contigsumsize;
	अगर (end < 0 ) 
		end = -1;
	i = ubh_find_last_zero_bit (UCPI_UBH(ucpi), ucpi->c_clusteroff, start, end);
	अगर ( i < end) 
		i = end;
	back = start - i;
	
	/*
	 * Account क्रम old cluster and the possibly new क्रमward and
	 * back clusters.
	 */
	i = back + क्रमw + 1;
	अगर (i > uspi->s_contigsumsize)
		i = uspi->s_contigsumsize;
	fs32_add(sb, (__fs32*)ubh_get_addr(UCPI_UBH(ucpi), ucpi->c_clustersumoff + (i << 2)), cnt);
	अगर (back > 0)
		fs32_sub(sb, (__fs32*)ubh_get_addr(UCPI_UBH(ucpi), ucpi->c_clustersumoff + (back << 2)), cnt);
	अगर (क्रमw > 0)
		fs32_sub(sb, (__fs32*)ubh_get_addr(UCPI_UBH(ucpi), ucpi->c_clustersumoff + (क्रमw << 2)), cnt);
पूर्ण


अटल अचिन्हित अक्षर ufs_fragtable_8fpb[] = अणु
	0x00, 0x01, 0x01, 0x02, 0x01, 0x01, 0x02, 0x04, 0x01, 0x01, 0x01, 0x03, 0x02, 0x03, 0x04, 0x08,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x02, 0x03, 0x03, 0x02, 0x04, 0x05, 0x08, 0x10,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x05, 0x09,
	0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x06, 0x04, 0x05, 0x05, 0x06, 0x08, 0x09, 0x10, 0x20,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x05, 0x09,	
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x03, 0x03, 0x03, 0x03, 0x05, 0x05, 0x09, 0x11,
	0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x06, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x06, 0x0A,
	0x04, 0x05, 0x05, 0x06, 0x05, 0x05, 0x06, 0x04, 0x08, 0x09, 0x09, 0x0A, 0x10, 0x11, 0x20, 0x40,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x05, 0x09,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x03, 0x03, 0x03, 0x03, 0x05, 0x05, 0x09, 0x11,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x05, 0x09,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x05, 0x05, 0x05, 0x07, 0x09, 0x09, 0x11, 0x21,
	0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x06, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x06, 0x0A,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x02, 0x03, 0x03, 0x02, 0x06, 0x07, 0x0A, 0x12,
	0x04, 0x05, 0x05, 0x06, 0x05, 0x05, 0x06, 0x04, 0x05, 0x05, 0x05, 0x07, 0x06, 0x07, 0x04, 0x0C,
	0x08, 0x09, 0x09, 0x0A, 0x09, 0x09, 0x0A, 0x0C, 0x10, 0x11, 0x11, 0x12, 0x20, 0x21, 0x40, 0x80,
पूर्ण;

अटल अचिन्हित अक्षर ufs_fragtable_other[] = अणु
	0x00, 0x16, 0x16, 0x2A, 0x16, 0x16, 0x26, 0x4E, 0x16, 0x16, 0x16, 0x3E, 0x2A, 0x3E, 0x4E, 0x8A,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x2A, 0x3E, 0x3E, 0x2A, 0x3E, 0x3E, 0x2E, 0x6E, 0x3E, 0x3E, 0x3E, 0x3E, 0x2A, 0x3E, 0x6E, 0xAA,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x26, 0x36, 0x36, 0x2E, 0x36, 0x36, 0x26, 0x6E, 0x36, 0x36, 0x36, 0x3E, 0x2E, 0x3E, 0x6E, 0xAE,
	0x4E, 0x5E, 0x5E, 0x6E, 0x5E, 0x5E, 0x6E, 0x4E, 0x5E, 0x5E, 0x5E, 0x7E, 0x6E, 0x7E, 0x4E, 0xCE,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7E, 0xBE,
	0x2A, 0x3E, 0x3E, 0x2A, 0x3E, 0x3E, 0x2E, 0x6E, 0x3E, 0x3E, 0x3E, 0x3E, 0x2A, 0x3E, 0x6E, 0xAA,
	0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7E,	0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7E, 0xBE,
	0x4E, 0x5E, 0x5E, 0x6E, 0x5E, 0x5E, 0x6E, 0x4E, 0x5E, 0x5E, 0x5E, 0x7E, 0x6E, 0x7E, 0x4E, 0xCE,
	0x8A, 0x9E, 0x9E, 0xAA, 0x9E, 0x9E, 0xAE, 0xCE, 0x9E, 0x9E, 0x9E, 0xBE, 0xAA, 0xBE, 0xCE, 0x8A,
पूर्ण;
