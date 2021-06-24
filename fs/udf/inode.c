<शैली गुरु>
/*
 * inode.c
 *
 * PURPOSE
 *  Inode handling routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *  This file is distributed under the terms of the GNU General Public
 *  License (GPL). Copies of the GPL can be obtained from:
 *    ftp://prep.ai.mit.edu/pub/gnu/GPL
 *  Each contributing author retains all rights to their own work.
 *
 *  (C) 1998 Dave Boynton
 *  (C) 1998-2004 Ben Fennema
 *  (C) 1999-2000 Stelias Computing Inc
 *
 * HISTORY
 *
 *  10/04/98 dgb  Added rudimentary directory functions
 *  10/07/98      Fully working udf_block_map! It works!
 *  11/25/98      bmap altered to better support extents
 *  12/06/98 blf  partition support in udf_iget, udf_block_map
 *                and udf_पढ़ो_inode
 *  12/12/98      rewrote udf_block_map to handle next extents and descs across
 *                block boundaries (which is not actually allowed)
 *  12/20/98      added support क्रम strategy 4096
 *  03/07/99      rewrote udf_block_map (again)
 *                New funcs, inode_bmap, udf_next_aext
 *  04/19/99      Support क्रम writing device EA's क्रम major/minor #
 */

#समावेश "udfdecl.h"
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc-itu-t.h>
#समावेश <linux/mpage.h>
#समावेश <linux/uपन.स>
#समावेश <linux/bपन.स>

#समावेश "udf_i.h"
#समावेश "udf_sb.h"

#घोषणा EXTENT_MERGE_SIZE 5

#घोषणा FE_MAPPED_PERMS	(FE_PERM_U_READ | FE_PERM_U_WRITE | FE_PERM_U_EXEC | \
			 FE_PERM_G_READ | FE_PERM_G_WRITE | FE_PERM_G_EXEC | \
			 FE_PERM_O_READ | FE_PERM_O_WRITE | FE_PERM_O_EXEC)

#घोषणा FE_DELETE_PERMS	(FE_PERM_U_DELETE | FE_PERM_G_DELETE | \
			 FE_PERM_O_DELETE)

अटल umode_t udf_convert_permissions(काष्ठा fileEntry *);
अटल पूर्णांक udf_update_inode(काष्ठा inode *, पूर्णांक);
अटल पूर्णांक udf_sync_inode(काष्ठा inode *inode);
अटल पूर्णांक udf_alloc_i_data(काष्ठा inode *inode, माप_प्रकार size);
अटल sector_t inode_getblk(काष्ठा inode *, sector_t, पूर्णांक *, पूर्णांक *);
अटल पूर्णांक8_t udf_insert_aext(काष्ठा inode *, काष्ठा extent_position,
			      काष्ठा kernel_lb_addr, uपूर्णांक32_t);
अटल व्योम udf_split_extents(काष्ठा inode *, पूर्णांक *, पूर्णांक, udf_pblk_t,
			      काष्ठा kernel_दीर्घ_ad *, पूर्णांक *);
अटल व्योम udf_pपुनः_स्मृति_extents(काष्ठा inode *, पूर्णांक, पूर्णांक,
				 काष्ठा kernel_दीर्घ_ad *, पूर्णांक *);
अटल व्योम udf_merge_extents(काष्ठा inode *, काष्ठा kernel_दीर्घ_ad *, पूर्णांक *);
अटल व्योम udf_update_extents(काष्ठा inode *, काष्ठा kernel_दीर्घ_ad *, पूर्णांक,
			       पूर्णांक, काष्ठा extent_position *);
अटल पूर्णांक udf_get_block(काष्ठा inode *, sector_t, काष्ठा buffer_head *, पूर्णांक);

अटल व्योम __udf_clear_extent_cache(काष्ठा inode *inode)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	अगर (iinfo->cached_extent.lstart != -1) अणु
		brअन्यथा(iinfo->cached_extent.epos.bh);
		iinfo->cached_extent.lstart = -1;
	पूर्ण
पूर्ण

/* Invalidate extent cache */
अटल व्योम udf_clear_extent_cache(काष्ठा inode *inode)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	spin_lock(&iinfo->i_extent_cache_lock);
	__udf_clear_extent_cache(inode);
	spin_unlock(&iinfo->i_extent_cache_lock);
पूर्ण

/* Return contents of extent cache */
अटल पूर्णांक udf_पढ़ो_extent_cache(काष्ठा inode *inode, loff_t bcount,
				 loff_t *lbcount, काष्ठा extent_position *pos)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	पूर्णांक ret = 0;

	spin_lock(&iinfo->i_extent_cache_lock);
	अगर ((iinfo->cached_extent.lstart <= bcount) &&
	    (iinfo->cached_extent.lstart != -1)) अणु
		/* Cache hit */
		*lbcount = iinfo->cached_extent.lstart;
		स_नकल(pos, &iinfo->cached_extent.epos,
		       माप(काष्ठा extent_position));
		अगर (pos->bh)
			get_bh(pos->bh);
		ret = 1;
	पूर्ण
	spin_unlock(&iinfo->i_extent_cache_lock);
	वापस ret;
पूर्ण

/* Add extent to extent cache */
अटल व्योम udf_update_extent_cache(काष्ठा inode *inode, loff_t estart,
				    काष्ठा extent_position *pos)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	spin_lock(&iinfo->i_extent_cache_lock);
	/* Invalidate previously cached extent */
	__udf_clear_extent_cache(inode);
	अगर (pos->bh)
		get_bh(pos->bh);
	स_नकल(&iinfo->cached_extent.epos, pos, माप(*pos));
	iinfo->cached_extent.lstart = estart;
	चयन (iinfo->i_alloc_type) अणु
	हाल ICBTAG_FLAG_AD_SHORT:
		iinfo->cached_extent.epos.offset -= माप(काष्ठा लघु_ad);
		अवरोध;
	हाल ICBTAG_FLAG_AD_LONG:
		iinfo->cached_extent.epos.offset -= माप(काष्ठा दीर्घ_ad);
		अवरोध;
	पूर्ण
	spin_unlock(&iinfo->i_extent_cache_lock);
पूर्ण

व्योम udf_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	पूर्णांक want_delete = 0;

	अगर (!is_bad_inode(inode)) अणु
		अगर (!inode->i_nlink) अणु
			want_delete = 1;
			udf_setsize(inode, 0);
			udf_update_inode(inode, IS_SYNC(inode));
		पूर्ण
		अगर (iinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB &&
		    inode->i_size != iinfo->i_lenExtents) अणु
			udf_warn(inode->i_sb,
				 "Inode %lu (mode %o) has inode size %llu different from extent length %llu. Filesystem need not be standards compliant.\n",
				 inode->i_ino, inode->i_mode,
				 (अचिन्हित दीर्घ दीर्घ)inode->i_size,
				 (अचिन्हित दीर्घ दीर्घ)iinfo->i_lenExtents);
		पूर्ण
	पूर्ण
	truncate_inode_pages_final(&inode->i_data);
	invalidate_inode_buffers(inode);
	clear_inode(inode);
	kमुक्त(iinfo->i_data);
	iinfo->i_data = शून्य;
	udf_clear_extent_cache(inode);
	अगर (want_delete) अणु
		udf_मुक्त_inode(inode);
	पूर्ण
पूर्ण

अटल व्योम udf_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	loff_t isize = inode->i_size;

	अगर (to > isize) अणु
		truncate_pagecache(inode, isize);
		अगर (iinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) अणु
			करोwn_ग_लिखो(&iinfo->i_data_sem);
			udf_clear_extent_cache(inode);
			udf_truncate_extents(inode);
			up_ग_लिखो(&iinfo->i_data_sem);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक udf_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, udf_get_block, wbc);
पूर्ण

अटल पूर्णांक udf_ग_लिखोpages(काष्ठा address_space *mapping,
			काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस mpage_ग_लिखोpages(mapping, wbc, udf_get_block);
पूर्ण

अटल पूर्णांक udf_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस mpage_पढ़ोpage(page, udf_get_block);
पूर्ण

अटल व्योम udf_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, udf_get_block);
पूर्ण

अटल पूर्णांक udf_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	ret = block_ग_लिखो_begin(mapping, pos, len, flags, pagep, udf_get_block);
	अगर (unlikely(ret))
		udf_ग_लिखो_failed(mapping, pos + len);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार udf_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	माप_प्रकार count = iov_iter_count(iter);
	sमाप_प्रकार ret;

	ret = blockdev_direct_IO(iocb, inode, iter, udf_get_block);
	अगर (unlikely(ret < 0 && iov_iter_rw(iter) == WRITE))
		udf_ग_लिखो_failed(mapping, iocb->ki_pos + count);
	वापस ret;
पूर्ण

अटल sector_t udf_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, udf_get_block);
पूर्ण

स्थिर काष्ठा address_space_operations udf_aops = अणु
	.पढ़ोpage	= udf_पढ़ोpage,
	.पढ़ोahead	= udf_पढ़ोahead,
	.ग_लिखोpage	= udf_ग_लिखोpage,
	.ग_लिखोpages	= udf_ग_लिखोpages,
	.ग_लिखो_begin	= udf_ग_लिखो_begin,
	.ग_लिखो_end	= generic_ग_लिखो_end,
	.direct_IO	= udf_direct_IO,
	.bmap		= udf_bmap,
पूर्ण;

/*
 * Expand file stored in ICB to a normal one-block-file
 *
 * This function requires i_data_sem क्रम writing and releases it.
 * This function requires i_mutex held
 */
पूर्णांक udf_expand_file_adinicb(काष्ठा inode *inode)
अणु
	काष्ठा page *page;
	अक्षर *kaddr;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	पूर्णांक err;
	काष्ठा ग_लिखोback_control udf_wbc = अणु
		.sync_mode = WB_SYNC_NONE,
		.nr_to_ग_लिखो = 1,
	पूर्ण;

	WARN_ON_ONCE(!inode_is_locked(inode));
	अगर (!iinfo->i_lenAlloc) अणु
		अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
			iinfo->i_alloc_type = ICBTAG_FLAG_AD_SHORT;
		अन्यथा
			iinfo->i_alloc_type = ICBTAG_FLAG_AD_LONG;
		/* from now on we have normal address_space methods */
		inode->i_data.a_ops = &udf_aops;
		up_ग_लिखो(&iinfo->i_data_sem);
		mark_inode_dirty(inode);
		वापस 0;
	पूर्ण
	/*
	 * Release i_data_sem so that we can lock a page - page lock ranks
	 * above i_data_sem. i_mutex still protects us against file changes.
	 */
	up_ग_लिखो(&iinfo->i_data_sem);

	page = find_or_create_page(inode->i_mapping, 0, GFP_NOFS);
	अगर (!page)
		वापस -ENOMEM;

	अगर (!PageUptodate(page)) अणु
		kaddr = kmap_atomic(page);
		स_रखो(kaddr + iinfo->i_lenAlloc, 0x00,
		       PAGE_SIZE - iinfo->i_lenAlloc);
		स_नकल(kaddr, iinfo->i_data + iinfo->i_lenEAttr,
			iinfo->i_lenAlloc);
		flush_dcache_page(page);
		SetPageUptodate(page);
		kunmap_atomic(kaddr);
	पूर्ण
	करोwn_ग_लिखो(&iinfo->i_data_sem);
	स_रखो(iinfo->i_data + iinfo->i_lenEAttr, 0x00,
	       iinfo->i_lenAlloc);
	iinfo->i_lenAlloc = 0;
	अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_SHORT;
	अन्यथा
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_LONG;
	/* from now on we have normal address_space methods */
	inode->i_data.a_ops = &udf_aops;
	up_ग_लिखो(&iinfo->i_data_sem);
	err = inode->i_data.a_ops->ग_लिखोpage(page, &udf_wbc);
	अगर (err) अणु
		/* Restore everything back so that we करोn't lose data... */
		lock_page(page);
		करोwn_ग_लिखो(&iinfo->i_data_sem);
		kaddr = kmap_atomic(page);
		स_नकल(iinfo->i_data + iinfo->i_lenEAttr, kaddr, inode->i_size);
		kunmap_atomic(kaddr);
		unlock_page(page);
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_IN_ICB;
		inode->i_data.a_ops = &udf_adinicb_aops;
		up_ग_लिखो(&iinfo->i_data_sem);
	पूर्ण
	put_page(page);
	mark_inode_dirty(inode);

	वापस err;
पूर्ण

काष्ठा buffer_head *udf_expand_dir_adinicb(काष्ठा inode *inode,
					    udf_pblk_t *block, पूर्णांक *err)
अणु
	udf_pblk_t newblock;
	काष्ठा buffer_head *dbh = शून्य;
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक8_t alloctype;
	काष्ठा extent_position epos;

	काष्ठा udf_fileident_bh sfibh, dfibh;
	loff_t f_pos = udf_ext0_offset(inode);
	पूर्णांक size = udf_ext0_offset(inode) + inode->i_size;
	काष्ठा fileIdentDesc cfi, *sfi, *dfi;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
		alloctype = ICBTAG_FLAG_AD_SHORT;
	अन्यथा
		alloctype = ICBTAG_FLAG_AD_LONG;

	अगर (!inode->i_size) अणु
		iinfo->i_alloc_type = alloctype;
		mark_inode_dirty(inode);
		वापस शून्य;
	पूर्ण

	/* alloc block, and copy data to it */
	*block = udf_new_block(inode->i_sb, inode,
			       iinfo->i_location.partitionReferenceNum,
			       iinfo->i_location.logicalBlockNum, err);
	अगर (!(*block))
		वापस शून्य;
	newblock = udf_get_pblock(inode->i_sb, *block,
				  iinfo->i_location.partitionReferenceNum,
				0);
	अगर (!newblock)
		वापस शून्य;
	dbh = udf_tgetblk(inode->i_sb, newblock);
	अगर (!dbh)
		वापस शून्य;
	lock_buffer(dbh);
	स_रखो(dbh->b_data, 0x00, inode->i_sb->s_blocksize);
	set_buffer_uptodate(dbh);
	unlock_buffer(dbh);
	mark_buffer_dirty_inode(dbh, inode);

	sfibh.soffset = sfibh.eoffset =
			f_pos & (inode->i_sb->s_blocksize - 1);
	sfibh.sbh = sfibh.ebh = शून्य;
	dfibh.soffset = dfibh.eoffset = 0;
	dfibh.sbh = dfibh.ebh = dbh;
	जबतक (f_pos < size) अणु
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_IN_ICB;
		sfi = udf_fileident_पढ़ो(inode, &f_pos, &sfibh, &cfi, शून्य,
					 शून्य, शून्य, शून्य);
		अगर (!sfi) अणु
			brअन्यथा(dbh);
			वापस शून्य;
		पूर्ण
		iinfo->i_alloc_type = alloctype;
		sfi->descTag.tagLocation = cpu_to_le32(*block);
		dfibh.soffset = dfibh.eoffset;
		dfibh.eoffset += (sfibh.eoffset - sfibh.soffset);
		dfi = (काष्ठा fileIdentDesc *)(dbh->b_data + dfibh.soffset);
		अगर (udf_ग_लिखो_fi(inode, sfi, dfi, &dfibh, sfi->impUse,
				 sfi->fileIdent +
					le16_to_cpu(sfi->lengthOfImpUse))) अणु
			iinfo->i_alloc_type = ICBTAG_FLAG_AD_IN_ICB;
			brअन्यथा(dbh);
			वापस शून्य;
		पूर्ण
	पूर्ण
	mark_buffer_dirty_inode(dbh, inode);

	स_रखो(iinfo->i_data + iinfo->i_lenEAttr, 0, iinfo->i_lenAlloc);
	iinfo->i_lenAlloc = 0;
	eloc.logicalBlockNum = *block;
	eloc.partitionReferenceNum =
				iinfo->i_location.partitionReferenceNum;
	iinfo->i_lenExtents = inode->i_size;
	epos.bh = शून्य;
	epos.block = iinfo->i_location;
	epos.offset = udf_file_entry_alloc_offset(inode);
	udf_add_aext(inode, &epos, &eloc, inode->i_size, 0);
	/* UniqueID stuff */

	brअन्यथा(epos.bh);
	mark_inode_dirty(inode);
	वापस dbh;
पूर्ण

अटल पूर्णांक udf_get_block(काष्ठा inode *inode, sector_t block,
			 काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक err, new;
	sector_t phys = 0;
	काष्ठा udf_inode_info *iinfo;

	अगर (!create) अणु
		phys = udf_block_map(inode, block);
		अगर (phys)
			map_bh(bh_result, inode->i_sb, phys);
		वापस 0;
	पूर्ण

	err = -EIO;
	new = 0;
	iinfo = UDF_I(inode);

	करोwn_ग_लिखो(&iinfo->i_data_sem);
	अगर (block == iinfo->i_next_alloc_block + 1) अणु
		iinfo->i_next_alloc_block++;
		iinfo->i_next_alloc_goal++;
	पूर्ण

	udf_clear_extent_cache(inode);
	phys = inode_getblk(inode, block, &err, &new);
	अगर (!phys)
		जाओ पात;

	अगर (new)
		set_buffer_new(bh_result);
	map_bh(bh_result, inode->i_sb, phys);

पात:
	up_ग_लिखो(&iinfo->i_data_sem);
	वापस err;
पूर्ण

अटल काष्ठा buffer_head *udf_getblk(काष्ठा inode *inode, udf_pblk_t block,
				      पूर्णांक create, पूर्णांक *err)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा buffer_head dummy;

	dummy.b_state = 0;
	dummy.b_blocknr = -1000;
	*err = udf_get_block(inode, block, &dummy, create);
	अगर (!*err && buffer_mapped(&dummy)) अणु
		bh = sb_getblk(inode->i_sb, dummy.b_blocknr);
		अगर (buffer_new(&dummy)) अणु
			lock_buffer(bh);
			स_रखो(bh->b_data, 0x00, inode->i_sb->s_blocksize);
			set_buffer_uptodate(bh);
			unlock_buffer(bh);
			mark_buffer_dirty_inode(bh, inode);
		पूर्ण
		वापस bh;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Extend the file with new blocks totaling 'new_block_bytes',
 * वापस the number of extents added
 */
अटल पूर्णांक udf_करो_extend_file(काष्ठा inode *inode,
			      काष्ठा extent_position *last_pos,
			      काष्ठा kernel_दीर्घ_ad *last_ext,
			      loff_t new_block_bytes)
अणु
	uपूर्णांक32_t add;
	पूर्णांक count = 0, fake = !(last_ext->extLength & UDF_EXTENT_LENGTH_MASK);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा kernel_lb_addr pपुनः_स्मृति_loc = अणुपूर्ण;
	uपूर्णांक32_t pपुनः_स्मृति_len = 0;
	काष्ठा udf_inode_info *iinfo;
	पूर्णांक err;

	/* The previous extent is fake and we should not extend by anything
	 * - there's nothing to करो... */
	अगर (!new_block_bytes && fake)
		वापस 0;

	iinfo = UDF_I(inode);
	/* Round the last extent up to a multiple of block size */
	अगर (last_ext->extLength & (sb->s_blocksize - 1)) अणु
		last_ext->extLength =
			(last_ext->extLength & UDF_EXTENT_FLAG_MASK) |
			(((last_ext->extLength & UDF_EXTENT_LENGTH_MASK) +
			  sb->s_blocksize - 1) & ~(sb->s_blocksize - 1));
		iinfo->i_lenExtents =
			(iinfo->i_lenExtents + sb->s_blocksize - 1) &
			~(sb->s_blocksize - 1);
	पूर्ण

	/* Last extent are just pपुनः_स्मृतिated blocks? */
	अगर ((last_ext->extLength & UDF_EXTENT_FLAG_MASK) ==
						EXT_NOT_RECORDED_ALLOCATED) अणु
		/* Save the extent so that we can reattach it to the end */
		pपुनः_स्मृति_loc = last_ext->extLocation;
		pपुनः_स्मृति_len = last_ext->extLength;
		/* Mark the extent as a hole */
		last_ext->extLength = EXT_NOT_RECORDED_NOT_ALLOCATED |
			(last_ext->extLength & UDF_EXTENT_LENGTH_MASK);
		last_ext->extLocation.logicalBlockNum = 0;
		last_ext->extLocation.partitionReferenceNum = 0;
	पूर्ण

	/* Can we merge with the previous extent? */
	अगर ((last_ext->extLength & UDF_EXTENT_FLAG_MASK) ==
					EXT_NOT_RECORDED_NOT_ALLOCATED) अणु
		add = (1 << 30) - sb->s_blocksize -
			(last_ext->extLength & UDF_EXTENT_LENGTH_MASK);
		अगर (add > new_block_bytes)
			add = new_block_bytes;
		new_block_bytes -= add;
		last_ext->extLength += add;
	पूर्ण

	अगर (fake) अणु
		udf_add_aext(inode, last_pos, &last_ext->extLocation,
			     last_ext->extLength, 1);
		count++;
	पूर्ण अन्यथा अणु
		काष्ठा kernel_lb_addr पंचांगploc;
		uपूर्णांक32_t पंचांगplen;

		udf_ग_लिखो_aext(inode, last_pos, &last_ext->extLocation,
				last_ext->extLength, 1);

		/*
		 * We've rewritten the last extent. If we are going to add
		 * more extents, we may need to enter possible following
		 * empty indirect extent.
		 */
		अगर (new_block_bytes || pपुनः_स्मृति_len)
			udf_next_aext(inode, last_pos, &पंचांगploc, &पंचांगplen, 0);
	पूर्ण

	/* Managed to करो everything necessary? */
	अगर (!new_block_bytes)
		जाओ out;

	/* All further extents will be NOT_RECORDED_NOT_ALLOCATED */
	last_ext->extLocation.logicalBlockNum = 0;
	last_ext->extLocation.partitionReferenceNum = 0;
	add = (1 << 30) - sb->s_blocksize;
	last_ext->extLength = EXT_NOT_RECORDED_NOT_ALLOCATED | add;

	/* Create enough extents to cover the whole hole */
	जबतक (new_block_bytes > add) अणु
		new_block_bytes -= add;
		err = udf_add_aext(inode, last_pos, &last_ext->extLocation,
				   last_ext->extLength, 1);
		अगर (err)
			वापस err;
		count++;
	पूर्ण
	अगर (new_block_bytes) अणु
		last_ext->extLength = EXT_NOT_RECORDED_NOT_ALLOCATED |
			new_block_bytes;
		err = udf_add_aext(inode, last_pos, &last_ext->extLocation,
				   last_ext->extLength, 1);
		अगर (err)
			वापस err;
		count++;
	पूर्ण

out:
	/* Do we have some pपुनः_स्मृतिated blocks saved? */
	अगर (pपुनः_स्मृति_len) अणु
		err = udf_add_aext(inode, last_pos, &pपुनः_स्मृति_loc,
				   pपुनः_स्मृति_len, 1);
		अगर (err)
			वापस err;
		last_ext->extLocation = pपुनः_स्मृति_loc;
		last_ext->extLength = pपुनः_स्मृति_len;
		count++;
	पूर्ण

	/* last_pos should poपूर्णांक to the last written extent... */
	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		last_pos->offset -= माप(काष्ठा लघु_ad);
	अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		last_pos->offset -= माप(काष्ठा दीर्घ_ad);
	अन्यथा
		वापस -EIO;

	वापस count;
पूर्ण

/* Extend the final block of the file to final_block_len bytes */
अटल व्योम udf_करो_extend_final_block(काष्ठा inode *inode,
				      काष्ठा extent_position *last_pos,
				      काष्ठा kernel_दीर्घ_ad *last_ext,
				      uपूर्णांक32_t final_block_len)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	uपूर्णांक32_t added_bytes;

	added_bytes = final_block_len -
		      (last_ext->extLength & (sb->s_blocksize - 1));
	last_ext->extLength += added_bytes;
	UDF_I(inode)->i_lenExtents += added_bytes;

	udf_ग_लिखो_aext(inode, last_pos, &last_ext->extLocation,
			last_ext->extLength, 1);
पूर्ण

अटल पूर्णांक udf_extend_file(काष्ठा inode *inode, loff_t newsize)
अणु

	काष्ठा extent_position epos;
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen;
	पूर्णांक8_t etype;
	काष्ठा super_block *sb = inode->i_sb;
	sector_t first_block = newsize >> sb->s_blocksize_bits, offset;
	अचिन्हित दीर्घ partial_final_block;
	पूर्णांक adsize;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	काष्ठा kernel_दीर्घ_ad extent;
	पूर्णांक err = 0;
	पूर्णांक within_final_block;

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		BUG();

	etype = inode_bmap(inode, first_block, &epos, &eloc, &elen, &offset);
	within_final_block = (etype != -1);

	अगर ((!epos.bh && epos.offset == udf_file_entry_alloc_offset(inode)) ||
	    (epos.bh && epos.offset == माप(काष्ठा allocExtDesc))) अणु
		/* File has no extents at all or has empty last
		 * indirect extent! Create a fake extent... */
		extent.extLocation.logicalBlockNum = 0;
		extent.extLocation.partitionReferenceNum = 0;
		extent.extLength = EXT_NOT_RECORDED_NOT_ALLOCATED;
	पूर्ण अन्यथा अणु
		epos.offset -= adsize;
		etype = udf_next_aext(inode, &epos, &extent.extLocation,
				      &extent.extLength, 0);
		extent.extLength |= etype << 30;
	पूर्ण

	partial_final_block = newsize & (sb->s_blocksize - 1);

	/* File has extent covering the new size (could happen when extending
	 * inside a block)?
	 */
	अगर (within_final_block) अणु
		/* Extending file within the last file block */
		udf_करो_extend_final_block(inode, &epos, &extent,
					  partial_final_block);
	पूर्ण अन्यथा अणु
		loff_t add = ((loff_t)offset << sb->s_blocksize_bits) |
			     partial_final_block;
		err = udf_करो_extend_file(inode, &epos, &extent, add);
	पूर्ण

	अगर (err < 0)
		जाओ out;
	err = 0;
	iinfo->i_lenExtents = newsize;
out:
	brअन्यथा(epos.bh);
	वापस err;
पूर्ण

अटल sector_t inode_getblk(काष्ठा inode *inode, sector_t block,
			     पूर्णांक *err, पूर्णांक *new)
अणु
	काष्ठा kernel_दीर्घ_ad laarr[EXTENT_MERGE_SIZE];
	काष्ठा extent_position prev_epos, cur_epos, next_epos;
	पूर्णांक count = 0, startnum = 0, endnum = 0;
	uपूर्णांक32_t elen = 0, पंचांगpelen;
	काष्ठा kernel_lb_addr eloc, पंचांगpeloc;
	पूर्णांक c = 1;
	loff_t lbcount = 0, b_off = 0;
	udf_pblk_t newblocknum, newblock;
	sector_t offset = 0;
	पूर्णांक8_t etype;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	udf_pblk_t goal = 0, pgoal = iinfo->i_location.logicalBlockNum;
	पूर्णांक lastblock = 0;
	bool isBeyondखातापूर्ण;

	*err = 0;
	*new = 0;
	prev_epos.offset = udf_file_entry_alloc_offset(inode);
	prev_epos.block = iinfo->i_location;
	prev_epos.bh = शून्य;
	cur_epos = next_epos = prev_epos;
	b_off = (loff_t)block << inode->i_sb->s_blocksize_bits;

	/* find the extent which contains the block we are looking क्रम.
	   alternate between laarr[0] and laarr[1] क्रम locations of the
	   current extent, and the previous extent */
	करो अणु
		अगर (prev_epos.bh != cur_epos.bh) अणु
			brअन्यथा(prev_epos.bh);
			get_bh(cur_epos.bh);
			prev_epos.bh = cur_epos.bh;
		पूर्ण
		अगर (cur_epos.bh != next_epos.bh) अणु
			brअन्यथा(cur_epos.bh);
			get_bh(next_epos.bh);
			cur_epos.bh = next_epos.bh;
		पूर्ण

		lbcount += elen;

		prev_epos.block = cur_epos.block;
		cur_epos.block = next_epos.block;

		prev_epos.offset = cur_epos.offset;
		cur_epos.offset = next_epos.offset;

		etype = udf_next_aext(inode, &next_epos, &eloc, &elen, 1);
		अगर (etype == -1)
			अवरोध;

		c = !c;

		laarr[c].extLength = (etype << 30) | elen;
		laarr[c].extLocation = eloc;

		अगर (etype != (EXT_NOT_RECORDED_NOT_ALLOCATED >> 30))
			pgoal = eloc.logicalBlockNum +
				((elen + inode->i_sb->s_blocksize - 1) >>
				 inode->i_sb->s_blocksize_bits);

		count++;
	पूर्ण जबतक (lbcount + elen <= b_off);

	b_off -= lbcount;
	offset = b_off >> inode->i_sb->s_blocksize_bits;
	/*
	 * Move prev_epos and cur_epos पूर्णांकo indirect extent अगर we are at
	 * the poपूर्णांकer to it
	 */
	udf_next_aext(inode, &prev_epos, &पंचांगpeloc, &पंचांगpelen, 0);
	udf_next_aext(inode, &cur_epos, &पंचांगpeloc, &पंचांगpelen, 0);

	/* अगर the extent is allocated and recorded, वापस the block
	   अगर the extent is not a multiple of the blocksize, round up */

	अगर (etype == (EXT_RECORDED_ALLOCATED >> 30)) अणु
		अगर (elen & (inode->i_sb->s_blocksize - 1)) अणु
			elen = EXT_RECORDED_ALLOCATED |
				((elen + inode->i_sb->s_blocksize - 1) &
				 ~(inode->i_sb->s_blocksize - 1));
			udf_ग_लिखो_aext(inode, &cur_epos, &eloc, elen, 1);
		पूर्ण
		newblock = udf_get_lb_pblock(inode->i_sb, &eloc, offset);
		जाओ out_मुक्त;
	पूर्ण

	/* Are we beyond खातापूर्ण? */
	अगर (etype == -1) अणु
		पूर्णांक ret;
		loff_t hole_len;
		isBeyondखातापूर्ण = true;
		अगर (count) अणु
			अगर (c)
				laarr[0] = laarr[1];
			startnum = 1;
		पूर्ण अन्यथा अणु
			/* Create a fake extent when there's not one */
			स_रखो(&laarr[0].extLocation, 0x00,
				माप(काष्ठा kernel_lb_addr));
			laarr[0].extLength = EXT_NOT_RECORDED_NOT_ALLOCATED;
			/* Will udf_करो_extend_file() create real extent from
			   a fake one? */
			startnum = (offset > 0);
		पूर्ण
		/* Create extents क्रम the hole between खातापूर्ण and offset */
		hole_len = (loff_t)offset << inode->i_blkbits;
		ret = udf_करो_extend_file(inode, &prev_epos, laarr, hole_len);
		अगर (ret < 0) अणु
			*err = ret;
			newblock = 0;
			जाओ out_मुक्त;
		पूर्ण
		c = 0;
		offset = 0;
		count += ret;
		/* We are not covered by a pपुनः_स्मृतिated extent? */
		अगर ((laarr[0].extLength & UDF_EXTENT_FLAG_MASK) !=
						EXT_NOT_RECORDED_ALLOCATED) अणु
			/* Is there any real extent? - otherwise we overग_लिखो
			 * the fake one... */
			अगर (count)
				c = !c;
			laarr[c].extLength = EXT_NOT_RECORDED_NOT_ALLOCATED |
				inode->i_sb->s_blocksize;
			स_रखो(&laarr[c].extLocation, 0x00,
				माप(काष्ठा kernel_lb_addr));
			count++;
		पूर्ण
		endnum = c + 1;
		lastblock = 1;
	पूर्ण अन्यथा अणु
		isBeyondखातापूर्ण = false;
		endnum = startnum = ((count > 2) ? 2 : count);

		/* अगर the current extent is in position 0,
		   swap it with the previous */
		अगर (!c && count != 1) अणु
			laarr[2] = laarr[0];
			laarr[0] = laarr[1];
			laarr[1] = laarr[2];
			c = 1;
		पूर्ण

		/* अगर the current block is located in an extent,
		   पढ़ो the next extent */
		etype = udf_next_aext(inode, &next_epos, &eloc, &elen, 0);
		अगर (etype != -1) अणु
			laarr[c + 1].extLength = (etype << 30) | elen;
			laarr[c + 1].extLocation = eloc;
			count++;
			startnum++;
			endnum++;
		पूर्ण अन्यथा
			lastblock = 1;
	पूर्ण

	/* अगर the current extent is not recorded but allocated, get the
	 * block in the extent corresponding to the requested block */
	अगर ((laarr[c].extLength >> 30) == (EXT_NOT_RECORDED_ALLOCATED >> 30))
		newblocknum = laarr[c].extLocation.logicalBlockNum + offset;
	अन्यथा अणु /* otherwise, allocate a new block */
		अगर (iinfo->i_next_alloc_block == block)
			goal = iinfo->i_next_alloc_goal;

		अगर (!goal) अणु
			अगर (!(goal = pgoal)) /* XXX: what was पूर्णांकended here? */
				goal = iinfo->i_location.logicalBlockNum + 1;
		पूर्ण

		newblocknum = udf_new_block(inode->i_sb, inode,
				iinfo->i_location.partitionReferenceNum,
				goal, err);
		अगर (!newblocknum) अणु
			*err = -ENOSPC;
			newblock = 0;
			जाओ out_मुक्त;
		पूर्ण
		अगर (isBeyondखातापूर्ण)
			iinfo->i_lenExtents += inode->i_sb->s_blocksize;
	पूर्ण

	/* अगर the extent the requsted block is located in contains multiple
	 * blocks, split the extent पूर्णांकo at most three extents. blocks prior
	 * to requested block, requested block, and blocks after requested
	 * block */
	udf_split_extents(inode, &c, offset, newblocknum, laarr, &endnum);

	/* We pपुनः_स्मृतिate blocks only क्रम regular files. It also makes sense
	 * क्रम directories but there's a problem when to drop the
	 * pपुनः_स्मृतिation. We might use some delayed work क्रम that but I feel
	 * it's overengineering क्रम a fileप्रणाली like UDF. */
	अगर (S_ISREG(inode->i_mode))
		udf_pपुनः_स्मृति_extents(inode, c, lastblock, laarr, &endnum);

	/* merge any continuous blocks in laarr */
	udf_merge_extents(inode, laarr, &endnum);

	/* ग_लिखो back the new extents, inserting new extents अगर the new number
	 * of extents is greater than the old number, and deleting extents अगर
	 * the new number of extents is less than the old number */
	udf_update_extents(inode, laarr, startnum, endnum, &prev_epos);

	newblock = udf_get_pblock(inode->i_sb, newblocknum,
				iinfo->i_location.partitionReferenceNum, 0);
	अगर (!newblock) अणु
		*err = -EIO;
		जाओ out_मुक्त;
	पूर्ण
	*new = 1;
	iinfo->i_next_alloc_block = block;
	iinfo->i_next_alloc_goal = newblocknum;
	inode->i_स_समय = current_समय(inode);

	अगर (IS_SYNC(inode))
		udf_sync_inode(inode);
	अन्यथा
		mark_inode_dirty(inode);
out_मुक्त:
	brअन्यथा(prev_epos.bh);
	brअन्यथा(cur_epos.bh);
	brअन्यथा(next_epos.bh);
	वापस newblock;
पूर्ण

अटल व्योम udf_split_extents(काष्ठा inode *inode, पूर्णांक *c, पूर्णांक offset,
			       udf_pblk_t newblocknum,
			       काष्ठा kernel_दीर्घ_ad *laarr, पूर्णांक *endnum)
अणु
	अचिन्हित दीर्घ blocksize = inode->i_sb->s_blocksize;
	अचिन्हित अक्षर blocksize_bits = inode->i_sb->s_blocksize_bits;

	अगर ((laarr[*c].extLength >> 30) == (EXT_NOT_RECORDED_ALLOCATED >> 30) ||
	    (laarr[*c].extLength >> 30) ==
				(EXT_NOT_RECORDED_NOT_ALLOCATED >> 30)) अणु
		पूर्णांक curr = *c;
		पूर्णांक blen = ((laarr[curr].extLength & UDF_EXTENT_LENGTH_MASK) +
			    blocksize - 1) >> blocksize_bits;
		पूर्णांक8_t etype = (laarr[curr].extLength >> 30);

		अगर (blen == 1)
			;
		अन्यथा अगर (!offset || blen == offset + 1) अणु
			laarr[curr + 2] = laarr[curr + 1];
			laarr[curr + 1] = laarr[curr];
		पूर्ण अन्यथा अणु
			laarr[curr + 3] = laarr[curr + 1];
			laarr[curr + 2] = laarr[curr + 1] = laarr[curr];
		पूर्ण

		अगर (offset) अणु
			अगर (etype == (EXT_NOT_RECORDED_ALLOCATED >> 30)) अणु
				udf_मुक्त_blocks(inode->i_sb, inode,
						&laarr[curr].extLocation,
						0, offset);
				laarr[curr].extLength =
					EXT_NOT_RECORDED_NOT_ALLOCATED |
					(offset << blocksize_bits);
				laarr[curr].extLocation.logicalBlockNum = 0;
				laarr[curr].extLocation.
						partitionReferenceNum = 0;
			पूर्ण अन्यथा
				laarr[curr].extLength = (etype << 30) |
					(offset << blocksize_bits);
			curr++;
			(*c)++;
			(*endnum)++;
		पूर्ण

		laarr[curr].extLocation.logicalBlockNum = newblocknum;
		अगर (etype == (EXT_NOT_RECORDED_NOT_ALLOCATED >> 30))
			laarr[curr].extLocation.partitionReferenceNum =
				UDF_I(inode)->i_location.partitionReferenceNum;
		laarr[curr].extLength = EXT_RECORDED_ALLOCATED |
			blocksize;
		curr++;

		अगर (blen != offset + 1) अणु
			अगर (etype == (EXT_NOT_RECORDED_ALLOCATED >> 30))
				laarr[curr].extLocation.logicalBlockNum +=
								offset + 1;
			laarr[curr].extLength = (etype << 30) |
				((blen - (offset + 1)) << blocksize_bits);
			curr++;
			(*endnum)++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम udf_pपुनः_स्मृति_extents(काष्ठा inode *inode, पूर्णांक c, पूर्णांक lastblock,
				 काष्ठा kernel_दीर्घ_ad *laarr,
				 पूर्णांक *endnum)
अणु
	पूर्णांक start, length = 0, currlength = 0, i;

	अगर (*endnum >= (c + 1)) अणु
		अगर (!lastblock)
			वापस;
		अन्यथा
			start = c;
	पूर्ण अन्यथा अणु
		अगर ((laarr[c + 1].extLength >> 30) ==
					(EXT_NOT_RECORDED_ALLOCATED >> 30)) अणु
			start = c + 1;
			length = currlength =
				(((laarr[c + 1].extLength &
					UDF_EXTENT_LENGTH_MASK) +
				inode->i_sb->s_blocksize - 1) >>
				inode->i_sb->s_blocksize_bits);
		पूर्ण अन्यथा
			start = c;
	पूर्ण

	क्रम (i = start + 1; i <= *endnum; i++) अणु
		अगर (i == *endnum) अणु
			अगर (lastblock)
				length += UDF_DEFAULT_PREALLOC_BLOCKS;
		पूर्ण अन्यथा अगर ((laarr[i].extLength >> 30) ==
				(EXT_NOT_RECORDED_NOT_ALLOCATED >> 30)) अणु
			length += (((laarr[i].extLength &
						UDF_EXTENT_LENGTH_MASK) +
				    inode->i_sb->s_blocksize - 1) >>
				    inode->i_sb->s_blocksize_bits);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	अगर (length) अणु
		पूर्णांक next = laarr[start].extLocation.logicalBlockNum +
			(((laarr[start].extLength & UDF_EXTENT_LENGTH_MASK) +
			  inode->i_sb->s_blocksize - 1) >>
			  inode->i_sb->s_blocksize_bits);
		पूर्णांक nuदो_स्मृति = udf_pपुनः_स्मृति_blocks(inode->i_sb, inode,
				laarr[start].extLocation.partitionReferenceNum,
				next, (UDF_DEFAULT_PREALLOC_BLOCKS > length ?
				length : UDF_DEFAULT_PREALLOC_BLOCKS) -
				currlength);
		अगर (nuदो_स्मृति) 	अणु
			अगर (start == (c + 1))
				laarr[start].extLength +=
					(nuदो_स्मृति <<
					 inode->i_sb->s_blocksize_bits);
			अन्यथा अणु
				स_हटाओ(&laarr[c + 2], &laarr[c + 1],
					माप(काष्ठा दीर्घ_ad) * (*endnum - (c + 1)));
				(*endnum)++;
				laarr[c + 1].extLocation.logicalBlockNum = next;
				laarr[c + 1].extLocation.partitionReferenceNum =
					laarr[c].extLocation.
							partitionReferenceNum;
				laarr[c + 1].extLength =
					EXT_NOT_RECORDED_ALLOCATED |
					(nuदो_स्मृति <<
					 inode->i_sb->s_blocksize_bits);
				start = c + 1;
			पूर्ण

			क्रम (i = start + 1; nuदो_स्मृति && i < *endnum; i++) अणु
				पूर्णांक elen = ((laarr[i].extLength &
						UDF_EXTENT_LENGTH_MASK) +
					    inode->i_sb->s_blocksize - 1) >>
					    inode->i_sb->s_blocksize_bits;

				अगर (elen > nuदो_स्मृति) अणु
					laarr[i].extLength -=
						(nuदो_स्मृति <<
						 inode->i_sb->s_blocksize_bits);
					nuदो_स्मृति = 0;
				पूर्ण अन्यथा अणु
					nuदो_स्मृति -= elen;
					अगर (*endnum > (i + 1))
						स_हटाओ(&laarr[i],
							&laarr[i + 1],
							माप(काष्ठा दीर्घ_ad) *
							(*endnum - (i + 1)));
					i--;
					(*endnum)--;
				पूर्ण
			पूर्ण
			UDF_I(inode)->i_lenExtents +=
				nuदो_स्मृति << inode->i_sb->s_blocksize_bits;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम udf_merge_extents(काष्ठा inode *inode, काष्ठा kernel_दीर्घ_ad *laarr,
			      पूर्णांक *endnum)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ blocksize = inode->i_sb->s_blocksize;
	अचिन्हित अक्षर blocksize_bits = inode->i_sb->s_blocksize_bits;

	क्रम (i = 0; i < (*endnum - 1); i++) अणु
		काष्ठा kernel_दीर्घ_ad *li /*l[i]*/ = &laarr[i];
		काष्ठा kernel_दीर्घ_ad *lip1 /*l[i plus 1]*/ = &laarr[i + 1];

		अगर (((li->extLength >> 30) == (lip1->extLength >> 30)) &&
			(((li->extLength >> 30) ==
				(EXT_NOT_RECORDED_NOT_ALLOCATED >> 30)) ||
			((lip1->extLocation.logicalBlockNum -
			  li->extLocation.logicalBlockNum) ==
			(((li->extLength & UDF_EXTENT_LENGTH_MASK) +
			blocksize - 1) >> blocksize_bits)))) अणु

			अगर (((li->extLength & UDF_EXTENT_LENGTH_MASK) +
				(lip1->extLength & UDF_EXTENT_LENGTH_MASK) +
				blocksize - 1) & ~UDF_EXTENT_LENGTH_MASK) अणु
				lip1->extLength = (lip1->extLength -
						  (li->extLength &
						   UDF_EXTENT_LENGTH_MASK) +
						   UDF_EXTENT_LENGTH_MASK) &
							~(blocksize - 1);
				li->extLength = (li->extLength &
						 UDF_EXTENT_FLAG_MASK) +
						(UDF_EXTENT_LENGTH_MASK + 1) -
						blocksize;
				lip1->extLocation.logicalBlockNum =
					li->extLocation.logicalBlockNum +
					((li->extLength &
						UDF_EXTENT_LENGTH_MASK) >>
						blocksize_bits);
			पूर्ण अन्यथा अणु
				li->extLength = lip1->extLength +
					(((li->extLength &
						UDF_EXTENT_LENGTH_MASK) +
					 blocksize - 1) & ~(blocksize - 1));
				अगर (*endnum > (i + 2))
					स_हटाओ(&laarr[i + 1], &laarr[i + 2],
						माप(काष्ठा दीर्घ_ad) *
						(*endnum - (i + 2)));
				i--;
				(*endnum)--;
			पूर्ण
		पूर्ण अन्यथा अगर (((li->extLength >> 30) ==
				(EXT_NOT_RECORDED_ALLOCATED >> 30)) &&
			   ((lip1->extLength >> 30) ==
				(EXT_NOT_RECORDED_NOT_ALLOCATED >> 30))) अणु
			udf_मुक्त_blocks(inode->i_sb, inode, &li->extLocation, 0,
					((li->extLength &
					  UDF_EXTENT_LENGTH_MASK) +
					 blocksize - 1) >> blocksize_bits);
			li->extLocation.logicalBlockNum = 0;
			li->extLocation.partitionReferenceNum = 0;

			अगर (((li->extLength & UDF_EXTENT_LENGTH_MASK) +
			     (lip1->extLength & UDF_EXTENT_LENGTH_MASK) +
			     blocksize - 1) & ~UDF_EXTENT_LENGTH_MASK) अणु
				lip1->extLength = (lip1->extLength -
						   (li->extLength &
						   UDF_EXTENT_LENGTH_MASK) +
						   UDF_EXTENT_LENGTH_MASK) &
						   ~(blocksize - 1);
				li->extLength = (li->extLength &
						 UDF_EXTENT_FLAG_MASK) +
						(UDF_EXTENT_LENGTH_MASK + 1) -
						blocksize;
			पूर्ण अन्यथा अणु
				li->extLength = lip1->extLength +
					(((li->extLength &
						UDF_EXTENT_LENGTH_MASK) +
					  blocksize - 1) & ~(blocksize - 1));
				अगर (*endnum > (i + 2))
					स_हटाओ(&laarr[i + 1], &laarr[i + 2],
						माप(काष्ठा दीर्घ_ad) *
						(*endnum - (i + 2)));
				i--;
				(*endnum)--;
			पूर्ण
		पूर्ण अन्यथा अगर ((li->extLength >> 30) ==
					(EXT_NOT_RECORDED_ALLOCATED >> 30)) अणु
			udf_मुक्त_blocks(inode->i_sb, inode,
					&li->extLocation, 0,
					((li->extLength &
						UDF_EXTENT_LENGTH_MASK) +
					 blocksize - 1) >> blocksize_bits);
			li->extLocation.logicalBlockNum = 0;
			li->extLocation.partitionReferenceNum = 0;
			li->extLength = (li->extLength &
						UDF_EXTENT_LENGTH_MASK) |
						EXT_NOT_RECORDED_NOT_ALLOCATED;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम udf_update_extents(काष्ठा inode *inode, काष्ठा kernel_दीर्घ_ad *laarr,
			       पूर्णांक startnum, पूर्णांक endnum,
			       काष्ठा extent_position *epos)
अणु
	पूर्णांक start = 0, i;
	काष्ठा kernel_lb_addr पंचांगploc;
	uपूर्णांक32_t पंचांगplen;

	अगर (startnum > endnum) अणु
		क्रम (i = 0; i < (startnum - endnum); i++)
			udf_delete_aext(inode, *epos);
	पूर्ण अन्यथा अगर (startnum < endnum) अणु
		क्रम (i = 0; i < (endnum - startnum); i++) अणु
			udf_insert_aext(inode, *epos, laarr[i].extLocation,
					laarr[i].extLength);
			udf_next_aext(inode, epos, &laarr[i].extLocation,
				      &laarr[i].extLength, 1);
			start++;
		पूर्ण
	पूर्ण

	क्रम (i = start; i < endnum; i++) अणु
		udf_next_aext(inode, epos, &पंचांगploc, &पंचांगplen, 0);
		udf_ग_लिखो_aext(inode, epos, &laarr[i].extLocation,
			       laarr[i].extLength, 1);
	पूर्ण
पूर्ण

काष्ठा buffer_head *udf_bपढ़ो(काष्ठा inode *inode, udf_pblk_t block,
			      पूर्णांक create, पूर्णांक *err)
अणु
	काष्ठा buffer_head *bh = शून्य;

	bh = udf_getblk(inode, block, create, err);
	अगर (!bh)
		वापस शून्य;

	अगर (buffer_uptodate(bh))
		वापस bh;

	ll_rw_block(REQ_OP_READ, 0, 1, &bh);

	रुको_on_buffer(bh);
	अगर (buffer_uptodate(bh))
		वापस bh;

	brअन्यथा(bh);
	*err = -EIO;
	वापस शून्य;
पूर्ण

पूर्णांक udf_setsize(काष्ठा inode *inode, loff_t newsize)
अणु
	पूर्णांक err;
	काष्ठा udf_inode_info *iinfo;
	अचिन्हित पूर्णांक bsize = i_blocksize(inode);

	अगर (!(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
	      S_ISLNK(inode->i_mode)))
		वापस -EINVAL;
	अगर (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		वापस -EPERM;

	iinfo = UDF_I(inode);
	अगर (newsize > inode->i_size) अणु
		करोwn_ग_लिखो(&iinfo->i_data_sem);
		अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) अणु
			अगर (bsize <
			    (udf_file_entry_alloc_offset(inode) + newsize)) अणु
				err = udf_expand_file_adinicb(inode);
				अगर (err)
					वापस err;
				करोwn_ग_लिखो(&iinfo->i_data_sem);
			पूर्ण अन्यथा अणु
				iinfo->i_lenAlloc = newsize;
				जाओ set_size;
			पूर्ण
		पूर्ण
		err = udf_extend_file(inode, newsize);
		अगर (err) अणु
			up_ग_लिखो(&iinfo->i_data_sem);
			वापस err;
		पूर्ण
set_size:
		up_ग_लिखो(&iinfo->i_data_sem);
		truncate_setsize(inode, newsize);
	पूर्ण अन्यथा अणु
		अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) अणु
			करोwn_ग_लिखो(&iinfo->i_data_sem);
			udf_clear_extent_cache(inode);
			स_रखो(iinfo->i_data + iinfo->i_lenEAttr + newsize,
			       0x00, bsize - newsize -
			       udf_file_entry_alloc_offset(inode));
			iinfo->i_lenAlloc = newsize;
			truncate_setsize(inode, newsize);
			up_ग_लिखो(&iinfo->i_data_sem);
			जाओ update_समय;
		पूर्ण
		err = block_truncate_page(inode->i_mapping, newsize,
					  udf_get_block);
		अगर (err)
			वापस err;
		truncate_setsize(inode, newsize);
		करोwn_ग_लिखो(&iinfo->i_data_sem);
		udf_clear_extent_cache(inode);
		err = udf_truncate_extents(inode);
		up_ग_लिखो(&iinfo->i_data_sem);
		अगर (err)
			वापस err;
	पूर्ण
update_समय:
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	अगर (IS_SYNC(inode))
		udf_sync_inode(inode);
	अन्यथा
		mark_inode_dirty(inode);
	वापस 0;
पूर्ण

/*
 * Maximum length of linked list क्रमmed by ICB hierarchy. The chosen number is
 * arbitrary - just that we hopefully करोn't limit any real use of rewritten
 * inode on ग_लिखो-once media but aव्योम looping क्रम too दीर्घ on corrupted media.
 */
#घोषणा UDF_MAX_ICB_NESTING 1024

अटल पूर्णांक udf_पढ़ो_inode(काष्ठा inode *inode, bool hidden_inode)
अणु
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा fileEntry *fe;
	काष्ठा extendedFileEntry *efe;
	uपूर्णांक16_t ident;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	काष्ठा udf_sb_info *sbi = UDF_SB(inode->i_sb);
	काष्ठा kernel_lb_addr *iloc = &iinfo->i_location;
	अचिन्हित पूर्णांक link_count;
	अचिन्हित पूर्णांक indirections = 0;
	पूर्णांक bs = inode->i_sb->s_blocksize;
	पूर्णांक ret = -EIO;
	uपूर्णांक32_t uid, gid;

reपढ़ो:
	अगर (iloc->partitionReferenceNum >= sbi->s_partitions) अणु
		udf_debug("partition reference: %u > logical volume partitions: %u\n",
			  iloc->partitionReferenceNum, sbi->s_partitions);
		वापस -EIO;
	पूर्ण

	अगर (iloc->logicalBlockNum >=
	    sbi->s_parपंचांगaps[iloc->partitionReferenceNum].s_partition_len) अणु
		udf_debug("block=%u, partition=%u out of range\n",
			  iloc->logicalBlockNum, iloc->partitionReferenceNum);
		वापस -EIO;
	पूर्ण

	/*
	 * Set शेषs, but the inode is still incomplete!
	 * Note: get_new_inode() sets the following on a new inode:
	 *      i_sb = sb
	 *      i_no = ino
	 *      i_flags = sb->s_flags
	 *      i_state = 0
	 * clean_inode(): zero fills and sets
	 *      i_count = 1
	 *      i_nlink = 1
	 *      i_op = शून्य;
	 */
	bh = udf_पढ़ो_ptagged(inode->i_sb, iloc, 0, &ident);
	अगर (!bh) अणु
		udf_err(inode->i_sb, "(ino %lu) failed !bh\n", inode->i_ino);
		वापस -EIO;
	पूर्ण

	अगर (ident != TAG_IDENT_FE && ident != TAG_IDENT_EFE &&
	    ident != TAG_IDENT_USE) अणु
		udf_err(inode->i_sb, "(ino %lu) failed ident=%u\n",
			inode->i_ino, ident);
		जाओ out;
	पूर्ण

	fe = (काष्ठा fileEntry *)bh->b_data;
	efe = (काष्ठा extendedFileEntry *)bh->b_data;

	अगर (fe->icbTag.strategyType == cpu_to_le16(4096)) अणु
		काष्ठा buffer_head *ibh;

		ibh = udf_पढ़ो_ptagged(inode->i_sb, iloc, 1, &ident);
		अगर (ident == TAG_IDENT_IE && ibh) अणु
			काष्ठा kernel_lb_addr loc;
			काष्ठा indirectEntry *ie;

			ie = (काष्ठा indirectEntry *)ibh->b_data;
			loc = lelb_to_cpu(ie->indirectICB.extLocation);

			अगर (ie->indirectICB.extLength) अणु
				brअन्यथा(ibh);
				स_नकल(&iinfo->i_location, &loc,
				       माप(काष्ठा kernel_lb_addr));
				अगर (++indirections > UDF_MAX_ICB_NESTING) अणु
					udf_err(inode->i_sb,
						"too many ICBs in ICB hierarchy"
						" (max %d supported)\n",
						UDF_MAX_ICB_NESTING);
					जाओ out;
				पूर्ण
				brअन्यथा(bh);
				जाओ reपढ़ो;
			पूर्ण
		पूर्ण
		brअन्यथा(ibh);
	पूर्ण अन्यथा अगर (fe->icbTag.strategyType != cpu_to_le16(4)) अणु
		udf_err(inode->i_sb, "unsupported strategy type: %u\n",
			le16_to_cpu(fe->icbTag.strategyType));
		जाओ out;
	पूर्ण
	अगर (fe->icbTag.strategyType == cpu_to_le16(4))
		iinfo->i_strat4096 = 0;
	अन्यथा /* अगर (fe->icbTag.strategyType == cpu_to_le16(4096)) */
		iinfo->i_strat4096 = 1;

	iinfo->i_alloc_type = le16_to_cpu(fe->icbTag.flags) &
							ICBTAG_FLAG_AD_MASK;
	अगर (iinfo->i_alloc_type != ICBTAG_FLAG_AD_SHORT &&
	    iinfo->i_alloc_type != ICBTAG_FLAG_AD_LONG &&
	    iinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण
	iinfo->i_unique = 0;
	iinfo->i_lenEAttr = 0;
	iinfo->i_lenExtents = 0;
	iinfo->i_lenAlloc = 0;
	iinfo->i_next_alloc_block = 0;
	iinfo->i_next_alloc_goal = 0;
	अगर (fe->descTag.tagIdent == cpu_to_le16(TAG_IDENT_EFE)) अणु
		iinfo->i_efe = 1;
		iinfo->i_use = 0;
		ret = udf_alloc_i_data(inode, bs -
					माप(काष्ठा extendedFileEntry));
		अगर (ret)
			जाओ out;
		स_नकल(iinfo->i_data,
		       bh->b_data + माप(काष्ठा extendedFileEntry),
		       bs - माप(काष्ठा extendedFileEntry));
	पूर्ण अन्यथा अगर (fe->descTag.tagIdent == cpu_to_le16(TAG_IDENT_FE)) अणु
		iinfo->i_efe = 0;
		iinfo->i_use = 0;
		ret = udf_alloc_i_data(inode, bs - माप(काष्ठा fileEntry));
		अगर (ret)
			जाओ out;
		स_नकल(iinfo->i_data,
		       bh->b_data + माप(काष्ठा fileEntry),
		       bs - माप(काष्ठा fileEntry));
	पूर्ण अन्यथा अगर (fe->descTag.tagIdent == cpu_to_le16(TAG_IDENT_USE)) अणु
		iinfo->i_efe = 0;
		iinfo->i_use = 1;
		iinfo->i_lenAlloc = le32_to_cpu(
				((काष्ठा unallocSpaceEntry *)bh->b_data)->
				 lengthAllocDescs);
		ret = udf_alloc_i_data(inode, bs -
					माप(काष्ठा unallocSpaceEntry));
		अगर (ret)
			जाओ out;
		स_नकल(iinfo->i_data,
		       bh->b_data + माप(काष्ठा unallocSpaceEntry),
		       bs - माप(काष्ठा unallocSpaceEntry));
		वापस 0;
	पूर्ण

	ret = -EIO;
	पढ़ो_lock(&sbi->s_cred_lock);
	uid = le32_to_cpu(fe->uid);
	अगर (uid == UDF_INVALID_ID ||
	    UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_UID_SET))
		inode->i_uid = sbi->s_uid;
	अन्यथा
		i_uid_ग_लिखो(inode, uid);

	gid = le32_to_cpu(fe->gid);
	अगर (gid == UDF_INVALID_ID ||
	    UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_GID_SET))
		inode->i_gid = sbi->s_gid;
	अन्यथा
		i_gid_ग_लिखो(inode, gid);

	अगर (fe->icbTag.fileType != ICBTAG_खाता_TYPE_सूचीECTORY &&
			sbi->s_भ_शेषe != UDF_INVALID_MODE)
		inode->i_mode = sbi->s_भ_शेषe;
	अन्यथा अगर (fe->icbTag.fileType == ICBTAG_खाता_TYPE_सूचीECTORY &&
			sbi->s_dmode != UDF_INVALID_MODE)
		inode->i_mode = sbi->s_dmode;
	अन्यथा
		inode->i_mode = udf_convert_permissions(fe);
	inode->i_mode &= ~sbi->s_umask;
	iinfo->i_extraPerms = le32_to_cpu(fe->permissions) & ~FE_MAPPED_PERMS;

	पढ़ो_unlock(&sbi->s_cred_lock);

	link_count = le16_to_cpu(fe->fileLinkCount);
	अगर (!link_count) अणु
		अगर (!hidden_inode) अणु
			ret = -ESTALE;
			जाओ out;
		पूर्ण
		link_count = 1;
	पूर्ण
	set_nlink(inode, link_count);

	inode->i_size = le64_to_cpu(fe->inक्रमmationLength);
	iinfo->i_lenExtents = inode->i_size;

	अगर (iinfo->i_efe == 0) अणु
		inode->i_blocks = le64_to_cpu(fe->logicalBlocksRecorded) <<
			(inode->i_sb->s_blocksize_bits - 9);

		udf_disk_stamp_to_समय(&inode->i_aसमय, fe->accessTime);
		udf_disk_stamp_to_समय(&inode->i_mसमय, fe->modअगरicationTime);
		udf_disk_stamp_to_समय(&inode->i_स_समय, fe->attrTime);

		iinfo->i_unique = le64_to_cpu(fe->uniqueID);
		iinfo->i_lenEAttr = le32_to_cpu(fe->lengthExtendedAttr);
		iinfo->i_lenAlloc = le32_to_cpu(fe->lengthAllocDescs);
		iinfo->i_checkpoपूर्णांक = le32_to_cpu(fe->checkpoपूर्णांक);
		iinfo->i_streamdir = 0;
		iinfo->i_lenStreams = 0;
	पूर्ण अन्यथा अणु
		inode->i_blocks = le64_to_cpu(efe->logicalBlocksRecorded) <<
		    (inode->i_sb->s_blocksize_bits - 9);

		udf_disk_stamp_to_समय(&inode->i_aसमय, efe->accessTime);
		udf_disk_stamp_to_समय(&inode->i_mसमय, efe->modअगरicationTime);
		udf_disk_stamp_to_समय(&iinfo->i_crसमय, efe->createTime);
		udf_disk_stamp_to_समय(&inode->i_स_समय, efe->attrTime);

		iinfo->i_unique = le64_to_cpu(efe->uniqueID);
		iinfo->i_lenEAttr = le32_to_cpu(efe->lengthExtendedAttr);
		iinfo->i_lenAlloc = le32_to_cpu(efe->lengthAllocDescs);
		iinfo->i_checkpoपूर्णांक = le32_to_cpu(efe->checkpoपूर्णांक);

		/* Named streams */
		iinfo->i_streamdir = (efe->streamDirectoryICB.extLength != 0);
		iinfo->i_locStreamdir =
			lelb_to_cpu(efe->streamDirectoryICB.extLocation);
		iinfo->i_lenStreams = le64_to_cpu(efe->objectSize);
		अगर (iinfo->i_lenStreams >= inode->i_size)
			iinfo->i_lenStreams -= inode->i_size;
		अन्यथा
			iinfo->i_lenStreams = 0;
	पूर्ण
	inode->i_generation = iinfo->i_unique;

	/*
	 * Sanity check length of allocation descriptors and extended attrs to
	 * aव्योम पूर्णांकeger overflows
	 */
	अगर (iinfo->i_lenEAttr > bs || iinfo->i_lenAlloc > bs)
		जाओ out;
	/* Now करो exact checks */
	अगर (udf_file_entry_alloc_offset(inode) + iinfo->i_lenAlloc > bs)
		जाओ out;
	/* Sanity checks क्रम files in ICB so that we करोn't get confused later */
	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) अणु
		/*
		 * For file in ICB data is stored in allocation descriptor
		 * so sizes should match
		 */
		अगर (iinfo->i_lenAlloc != inode->i_size)
			जाओ out;
		/* File in ICB has to fit in there... */
		अगर (inode->i_size > bs - udf_file_entry_alloc_offset(inode))
			जाओ out;
	पूर्ण

	चयन (fe->icbTag.fileType) अणु
	हाल ICBTAG_खाता_TYPE_सूचीECTORY:
		inode->i_op = &udf_dir_inode_operations;
		inode->i_fop = &udf_dir_operations;
		inode->i_mode |= S_IFसूची;
		inc_nlink(inode);
		अवरोध;
	हाल ICBTAG_खाता_TYPE_REALTIME:
	हाल ICBTAG_खाता_TYPE_REGULAR:
	हाल ICBTAG_खाता_TYPE_UNDEF:
	हाल ICBTAG_खाता_TYPE_VAT20:
		अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
			inode->i_data.a_ops = &udf_adinicb_aops;
		अन्यथा
			inode->i_data.a_ops = &udf_aops;
		inode->i_op = &udf_file_inode_operations;
		inode->i_fop = &udf_file_operations;
		inode->i_mode |= S_IFREG;
		अवरोध;
	हाल ICBTAG_खाता_TYPE_BLOCK:
		inode->i_mode |= S_IFBLK;
		अवरोध;
	हाल ICBTAG_खाता_TYPE_CHAR:
		inode->i_mode |= S_IFCHR;
		अवरोध;
	हाल ICBTAG_खाता_TYPE_FIFO:
		init_special_inode(inode, inode->i_mode | S_IFIFO, 0);
		अवरोध;
	हाल ICBTAG_खाता_TYPE_SOCKET:
		init_special_inode(inode, inode->i_mode | S_IFSOCK, 0);
		अवरोध;
	हाल ICBTAG_खाता_TYPE_SYMLINK:
		inode->i_data.a_ops = &udf_symlink_aops;
		inode->i_op = &udf_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mode = S_IFLNK | 0777;
		अवरोध;
	हाल ICBTAG_खाता_TYPE_MAIN:
		udf_debug("METADATA FILE-----\n");
		अवरोध;
	हाल ICBTAG_खाता_TYPE_MIRROR:
		udf_debug("METADATA MIRROR FILE-----\n");
		अवरोध;
	हाल ICBTAG_खाता_TYPE_BITMAP:
		udf_debug("METADATA BITMAP FILE-----\n");
		अवरोध;
	शेष:
		udf_err(inode->i_sb, "(ino %lu) failed unknown file type=%u\n",
			inode->i_ino, fe->icbTag.fileType);
		जाओ out;
	पूर्ण
	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) अणु
		काष्ठा deviceSpec *dsea =
			(काष्ठा deviceSpec *)udf_get_extendedattr(inode, 12, 1);
		अगर (dsea) अणु
			init_special_inode(inode, inode->i_mode,
				MKDEV(le32_to_cpu(dsea->majorDeviceIdent),
				      le32_to_cpu(dsea->minorDeviceIdent)));
			/* Developer ID ??? */
		पूर्ण अन्यथा
			जाओ out;
	पूर्ण
	ret = 0;
out:
	brअन्यथा(bh);
	वापस ret;
पूर्ण

अटल पूर्णांक udf_alloc_i_data(काष्ठा inode *inode, माप_प्रकार size)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	iinfo->i_data = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!iinfo->i_data)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल umode_t udf_convert_permissions(काष्ठा fileEntry *fe)
अणु
	umode_t mode;
	uपूर्णांक32_t permissions;
	uपूर्णांक32_t flags;

	permissions = le32_to_cpu(fe->permissions);
	flags = le16_to_cpu(fe->icbTag.flags);

	mode =	((permissions) & 0007) |
		((permissions >> 2) & 0070) |
		((permissions >> 4) & 0700) |
		((flags & ICBTAG_FLAG_SETUID) ? S_ISUID : 0) |
		((flags & ICBTAG_FLAG_SETGID) ? S_ISGID : 0) |
		((flags & ICBTAG_FLAG_STICKY) ? S_ISVTX : 0);

	वापस mode;
पूर्ण

व्योम udf_update_extra_perms(काष्ठा inode *inode, umode_t mode)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	/*
	 * UDF 2.01 sec. 3.3.3.3 Note 2:
	 * In Unix, delete permission tracks ग_लिखो
	 */
	iinfo->i_extraPerms &= ~FE_DELETE_PERMS;
	अगर (mode & 0200)
		iinfo->i_extraPerms |= FE_PERM_U_DELETE;
	अगर (mode & 0020)
		iinfo->i_extraPerms |= FE_PERM_G_DELETE;
	अगर (mode & 0002)
		iinfo->i_extraPerms |= FE_PERM_O_DELETE;
पूर्ण

पूर्णांक udf_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस udf_update_inode(inode, wbc->sync_mode == WB_SYNC_ALL);
पूर्ण

अटल पूर्णांक udf_sync_inode(काष्ठा inode *inode)
अणु
	वापस udf_update_inode(inode, 1);
पूर्ण

अटल व्योम udf_adjust_समय(काष्ठा udf_inode_info *iinfo, काष्ठा बारpec64 समय)
अणु
	अगर (iinfo->i_crसमय.tv_sec > समय.tv_sec ||
	    (iinfo->i_crसमय.tv_sec == समय.tv_sec &&
	     iinfo->i_crसमय.tv_nsec > समय.tv_nsec))
		iinfo->i_crसमय = समय;
पूर्ण

अटल पूर्णांक udf_update_inode(काष्ठा inode *inode, पूर्णांक करो_sync)
अणु
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा fileEntry *fe;
	काष्ठा extendedFileEntry *efe;
	uपूर्णांक64_t lb_recorded;
	uपूर्णांक32_t udfperms;
	uपूर्णांक16_t icbflags;
	uपूर्णांक16_t crclen;
	पूर्णांक err = 0;
	काष्ठा udf_sb_info *sbi = UDF_SB(inode->i_sb);
	अचिन्हित अक्षर blocksize_bits = inode->i_sb->s_blocksize_bits;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	bh = udf_tgetblk(inode->i_sb,
			udf_get_lb_pblock(inode->i_sb, &iinfo->i_location, 0));
	अगर (!bh) अणु
		udf_debug("getblk failure\n");
		वापस -EIO;
	पूर्ण

	lock_buffer(bh);
	स_रखो(bh->b_data, 0, inode->i_sb->s_blocksize);
	fe = (काष्ठा fileEntry *)bh->b_data;
	efe = (काष्ठा extendedFileEntry *)bh->b_data;

	अगर (iinfo->i_use) अणु
		काष्ठा unallocSpaceEntry *use =
			(काष्ठा unallocSpaceEntry *)bh->b_data;

		use->lengthAllocDescs = cpu_to_le32(iinfo->i_lenAlloc);
		स_नकल(bh->b_data + माप(काष्ठा unallocSpaceEntry),
		       iinfo->i_data, inode->i_sb->s_blocksize -
					माप(काष्ठा unallocSpaceEntry));
		use->descTag.tagIdent = cpu_to_le16(TAG_IDENT_USE);
		crclen = माप(काष्ठा unallocSpaceEntry);

		जाओ finish;
	पूर्ण

	अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_UID_FORGET))
		fe->uid = cpu_to_le32(UDF_INVALID_ID);
	अन्यथा
		fe->uid = cpu_to_le32(i_uid_पढ़ो(inode));

	अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_GID_FORGET))
		fe->gid = cpu_to_le32(UDF_INVALID_ID);
	अन्यथा
		fe->gid = cpu_to_le32(i_gid_पढ़ो(inode));

	udfperms = ((inode->i_mode & 0007)) |
		   ((inode->i_mode & 0070) << 2) |
		   ((inode->i_mode & 0700) << 4);

	udfperms |= iinfo->i_extraPerms;
	fe->permissions = cpu_to_le32(udfperms);

	अगर (S_ISसूची(inode->i_mode) && inode->i_nlink > 0)
		fe->fileLinkCount = cpu_to_le16(inode->i_nlink - 1);
	अन्यथा
		fe->fileLinkCount = cpu_to_le16(inode->i_nlink);

	fe->inक्रमmationLength = cpu_to_le64(inode->i_size);

	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) अणु
		काष्ठा regid *eid;
		काष्ठा deviceSpec *dsea =
			(काष्ठा deviceSpec *)udf_get_extendedattr(inode, 12, 1);
		अगर (!dsea) अणु
			dsea = (काष्ठा deviceSpec *)
				udf_add_extendedattr(inode,
						     माप(काष्ठा deviceSpec) +
						     माप(काष्ठा regid), 12, 0x3);
			dsea->attrType = cpu_to_le32(12);
			dsea->attrSubtype = 1;
			dsea->attrLength = cpu_to_le32(
						माप(काष्ठा deviceSpec) +
						माप(काष्ठा regid));
			dsea->impUseLength = cpu_to_le32(माप(काष्ठा regid));
		पूर्ण
		eid = (काष्ठा regid *)dsea->impUse;
		स_रखो(eid, 0, माप(*eid));
		म_नकल(eid->ident, UDF_ID_DEVELOPER);
		eid->identSuffix[0] = UDF_OS_CLASS_UNIX;
		eid->identSuffix[1] = UDF_OS_ID_LINUX;
		dsea->majorDeviceIdent = cpu_to_le32(imajor(inode));
		dsea->minorDeviceIdent = cpu_to_le32(iminor(inode));
	पूर्ण

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		lb_recorded = 0; /* No extents => no blocks! */
	अन्यथा
		lb_recorded =
			(inode->i_blocks + (1 << (blocksize_bits - 9)) - 1) >>
			(blocksize_bits - 9);

	अगर (iinfo->i_efe == 0) अणु
		स_नकल(bh->b_data + माप(काष्ठा fileEntry),
		       iinfo->i_data,
		       inode->i_sb->s_blocksize - माप(काष्ठा fileEntry));
		fe->logicalBlocksRecorded = cpu_to_le64(lb_recorded);

		udf_समय_प्रकारo_disk_stamp(&fe->accessTime, inode->i_aसमय);
		udf_समय_प्रकारo_disk_stamp(&fe->modअगरicationTime, inode->i_mसमय);
		udf_समय_प्रकारo_disk_stamp(&fe->attrTime, inode->i_स_समय);
		स_रखो(&(fe->impIdent), 0, माप(काष्ठा regid));
		म_नकल(fe->impIdent.ident, UDF_ID_DEVELOPER);
		fe->impIdent.identSuffix[0] = UDF_OS_CLASS_UNIX;
		fe->impIdent.identSuffix[1] = UDF_OS_ID_LINUX;
		fe->uniqueID = cpu_to_le64(iinfo->i_unique);
		fe->lengthExtendedAttr = cpu_to_le32(iinfo->i_lenEAttr);
		fe->lengthAllocDescs = cpu_to_le32(iinfo->i_lenAlloc);
		fe->checkpoपूर्णांक = cpu_to_le32(iinfo->i_checkpoपूर्णांक);
		fe->descTag.tagIdent = cpu_to_le16(TAG_IDENT_FE);
		crclen = माप(काष्ठा fileEntry);
	पूर्ण अन्यथा अणु
		स_नकल(bh->b_data + माप(काष्ठा extendedFileEntry),
		       iinfo->i_data,
		       inode->i_sb->s_blocksize -
					माप(काष्ठा extendedFileEntry));
		efe->objectSize =
			cpu_to_le64(inode->i_size + iinfo->i_lenStreams);
		efe->logicalBlocksRecorded = cpu_to_le64(lb_recorded);

		अगर (iinfo->i_streamdir) अणु
			काष्ठा दीर्घ_ad *icb_lad = &efe->streamDirectoryICB;

			icb_lad->extLocation =
				cpu_to_lelb(iinfo->i_locStreamdir);
			icb_lad->extLength =
				cpu_to_le32(inode->i_sb->s_blocksize);
		पूर्ण

		udf_adjust_समय(iinfo, inode->i_aसमय);
		udf_adjust_समय(iinfo, inode->i_mसमय);
		udf_adjust_समय(iinfo, inode->i_स_समय);

		udf_समय_प्रकारo_disk_stamp(&efe->accessTime, inode->i_aसमय);
		udf_समय_प्रकारo_disk_stamp(&efe->modअगरicationTime, inode->i_mसमय);
		udf_समय_प्रकारo_disk_stamp(&efe->createTime, iinfo->i_crसमय);
		udf_समय_प्रकारo_disk_stamp(&efe->attrTime, inode->i_स_समय);

		स_रखो(&(efe->impIdent), 0, माप(efe->impIdent));
		म_नकल(efe->impIdent.ident, UDF_ID_DEVELOPER);
		efe->impIdent.identSuffix[0] = UDF_OS_CLASS_UNIX;
		efe->impIdent.identSuffix[1] = UDF_OS_ID_LINUX;
		efe->uniqueID = cpu_to_le64(iinfo->i_unique);
		efe->lengthExtendedAttr = cpu_to_le32(iinfo->i_lenEAttr);
		efe->lengthAllocDescs = cpu_to_le32(iinfo->i_lenAlloc);
		efe->checkpoपूर्णांक = cpu_to_le32(iinfo->i_checkpoपूर्णांक);
		efe->descTag.tagIdent = cpu_to_le16(TAG_IDENT_EFE);
		crclen = माप(काष्ठा extendedFileEntry);
	पूर्ण

finish:
	अगर (iinfo->i_strat4096) अणु
		fe->icbTag.strategyType = cpu_to_le16(4096);
		fe->icbTag.strategyParameter = cpu_to_le16(1);
		fe->icbTag.numEntries = cpu_to_le16(2);
	पूर्ण अन्यथा अणु
		fe->icbTag.strategyType = cpu_to_le16(4);
		fe->icbTag.numEntries = cpu_to_le16(1);
	पूर्ण

	अगर (iinfo->i_use)
		fe->icbTag.fileType = ICBTAG_खाता_TYPE_USE;
	अन्यथा अगर (S_ISसूची(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_खाता_TYPE_सूचीECTORY;
	अन्यथा अगर (S_ISREG(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_खाता_TYPE_REGULAR;
	अन्यथा अगर (S_ISLNK(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_खाता_TYPE_SYMLINK;
	अन्यथा अगर (S_ISBLK(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_खाता_TYPE_BLOCK;
	अन्यथा अगर (S_ISCHR(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_खाता_TYPE_CHAR;
	अन्यथा अगर (S_ISFIFO(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_खाता_TYPE_FIFO;
	अन्यथा अगर (S_ISSOCK(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_खाता_TYPE_SOCKET;

	icbflags =	iinfo->i_alloc_type |
			((inode->i_mode & S_ISUID) ? ICBTAG_FLAG_SETUID : 0) |
			((inode->i_mode & S_ISGID) ? ICBTAG_FLAG_SETGID : 0) |
			((inode->i_mode & S_ISVTX) ? ICBTAG_FLAG_STICKY : 0) |
			(le16_to_cpu(fe->icbTag.flags) &
				~(ICBTAG_FLAG_AD_MASK | ICBTAG_FLAG_SETUID |
				ICBTAG_FLAG_SETGID | ICBTAG_FLAG_STICKY));

	fe->icbTag.flags = cpu_to_le16(icbflags);
	अगर (sbi->s_udfrev >= 0x0200)
		fe->descTag.descVersion = cpu_to_le16(3);
	अन्यथा
		fe->descTag.descVersion = cpu_to_le16(2);
	fe->descTag.tagSerialNum = cpu_to_le16(sbi->s_serial_number);
	fe->descTag.tagLocation = cpu_to_le32(
					iinfo->i_location.logicalBlockNum);
	crclen += iinfo->i_lenEAttr + iinfo->i_lenAlloc - माप(काष्ठा tag);
	fe->descTag.descCRCLength = cpu_to_le16(crclen);
	fe->descTag.descCRC = cpu_to_le16(crc_itu_t(0, (अक्षर *)fe + माप(काष्ठा tag),
						  crclen));
	fe->descTag.tagChecksum = udf_tag_checksum(&fe->descTag);

	set_buffer_uptodate(bh);
	unlock_buffer(bh);

	/* ग_लिखो the data blocks */
	mark_buffer_dirty(bh);
	अगर (करो_sync) अणु
		sync_dirty_buffer(bh);
		अगर (buffer_ग_लिखो_io_error(bh)) अणु
			udf_warn(inode->i_sb, "IO error syncing udf inode [%08lx]\n",
				 inode->i_ino);
			err = -EIO;
		पूर्ण
	पूर्ण
	brअन्यथा(bh);

	वापस err;
पूर्ण

काष्ठा inode *__udf_iget(काष्ठा super_block *sb, काष्ठा kernel_lb_addr *ino,
			 bool hidden_inode)
अणु
	अचिन्हित दीर्घ block = udf_get_lb_pblock(sb, ino, 0);
	काष्ठा inode *inode = iget_locked(sb, block);
	पूर्णांक err;

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	स_नकल(&UDF_I(inode)->i_location, ino, माप(काष्ठा kernel_lb_addr));
	err = udf_पढ़ो_inode(inode, hidden_inode);
	अगर (err < 0) अणु
		iget_failed(inode);
		वापस ERR_PTR(err);
	पूर्ण
	unlock_new_inode(inode);

	वापस inode;
पूर्ण

पूर्णांक udf_setup_indirect_aext(काष्ठा inode *inode, udf_pblk_t block,
			    काष्ठा extent_position *epos)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *bh;
	काष्ठा allocExtDesc *aed;
	काष्ठा extent_position nepos;
	काष्ठा kernel_lb_addr neloc;
	पूर्णांक ver, adsize;

	अगर (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		वापस -EIO;

	neloc.logicalBlockNum = block;
	neloc.partitionReferenceNum = epos->block.partitionReferenceNum;

	bh = udf_tgetblk(sb, udf_get_lb_pblock(sb, &neloc, 0));
	अगर (!bh)
		वापस -EIO;
	lock_buffer(bh);
	स_रखो(bh->b_data, 0x00, sb->s_blocksize);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);
	mark_buffer_dirty_inode(bh, inode);

	aed = (काष्ठा allocExtDesc *)(bh->b_data);
	अगर (!UDF_QUERY_FLAG(sb, UDF_FLAG_STRICT)) अणु
		aed->previousAllocExtLocation =
				cpu_to_le32(epos->block.logicalBlockNum);
	पूर्ण
	aed->lengthAllocDescs = cpu_to_le32(0);
	अगर (UDF_SB(sb)->s_udfrev >= 0x0200)
		ver = 3;
	अन्यथा
		ver = 2;
	udf_new_tag(bh->b_data, TAG_IDENT_AED, ver, 1, block,
		    माप(काष्ठा tag));

	nepos.block = neloc;
	nepos.offset = माप(काष्ठा allocExtDesc);
	nepos.bh = bh;

	/*
	 * Do we have to copy current last extent to make space क्रम indirect
	 * one?
	 */
	अगर (epos->offset + adsize > sb->s_blocksize) अणु
		काष्ठा kernel_lb_addr cp_loc;
		uपूर्णांक32_t cp_len;
		पूर्णांक cp_type;

		epos->offset -= adsize;
		cp_type = udf_current_aext(inode, epos, &cp_loc, &cp_len, 0);
		cp_len |= ((uपूर्णांक32_t)cp_type) << 30;

		__udf_add_aext(inode, &nepos, &cp_loc, cp_len, 1);
		udf_ग_लिखो_aext(inode, epos, &nepos.block,
			       sb->s_blocksize | EXT_NEXT_EXTENT_ALLOCDESCS, 0);
	पूर्ण अन्यथा अणु
		__udf_add_aext(inode, epos, &nepos.block,
			       sb->s_blocksize | EXT_NEXT_EXTENT_ALLOCDESCS, 0);
	पूर्ण

	brअन्यथा(epos->bh);
	*epos = nepos;

	वापस 0;
पूर्ण

/*
 * Append extent at the given position - should be the first मुक्त one in inode
 * / indirect extent. This function assumes there is enough space in the inode
 * or indirect extent. Use udf_add_aext() अगर you didn't check क्रम this beक्रमe.
 */
पूर्णांक __udf_add_aext(काष्ठा inode *inode, काष्ठा extent_position *epos,
		   काष्ठा kernel_lb_addr *eloc, uपूर्णांक32_t elen, पूर्णांक inc)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	काष्ठा allocExtDesc *aed;
	पूर्णांक adsize;

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		वापस -EIO;

	अगर (!epos->bh) अणु
		WARN_ON(iinfo->i_lenAlloc !=
			epos->offset - udf_file_entry_alloc_offset(inode));
	पूर्ण अन्यथा अणु
		aed = (काष्ठा allocExtDesc *)epos->bh->b_data;
		WARN_ON(le32_to_cpu(aed->lengthAllocDescs) !=
			epos->offset - माप(काष्ठा allocExtDesc));
		WARN_ON(epos->offset + adsize > inode->i_sb->s_blocksize);
	पूर्ण

	udf_ग_लिखो_aext(inode, epos, eloc, elen, inc);

	अगर (!epos->bh) अणु
		iinfo->i_lenAlloc += adsize;
		mark_inode_dirty(inode);
	पूर्ण अन्यथा अणु
		aed = (काष्ठा allocExtDesc *)epos->bh->b_data;
		le32_add_cpu(&aed->lengthAllocDescs, adsize);
		अगर (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
				UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
			udf_update_tag(epos->bh->b_data,
					epos->offset + (inc ? 0 : adsize));
		अन्यथा
			udf_update_tag(epos->bh->b_data,
					माप(काष्ठा allocExtDesc));
		mark_buffer_dirty_inode(epos->bh, inode);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Append extent at given position - should be the first मुक्त one in inode
 * / indirect extent. Takes care of allocating and linking indirect blocks.
 */
पूर्णांक udf_add_aext(काष्ठा inode *inode, काष्ठा extent_position *epos,
		 काष्ठा kernel_lb_addr *eloc, uपूर्णांक32_t elen, पूर्णांक inc)
अणु
	पूर्णांक adsize;
	काष्ठा super_block *sb = inode->i_sb;

	अगर (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		वापस -EIO;

	अगर (epos->offset + (2 * adsize) > sb->s_blocksize) अणु
		पूर्णांक err;
		udf_pblk_t new_block;

		new_block = udf_new_block(sb, शून्य,
					  epos->block.partitionReferenceNum,
					  epos->block.logicalBlockNum, &err);
		अगर (!new_block)
			वापस -ENOSPC;

		err = udf_setup_indirect_aext(inode, new_block, epos);
		अगर (err)
			वापस err;
	पूर्ण

	वापस __udf_add_aext(inode, epos, eloc, elen, inc);
पूर्ण

व्योम udf_ग_लिखो_aext(काष्ठा inode *inode, काष्ठा extent_position *epos,
		    काष्ठा kernel_lb_addr *eloc, uपूर्णांक32_t elen, पूर्णांक inc)
अणु
	पूर्णांक adsize;
	uपूर्णांक8_t *ptr;
	काष्ठा लघु_ad *sad;
	काष्ठा दीर्घ_ad *lad;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	अगर (!epos->bh)
		ptr = iinfo->i_data + epos->offset -
			udf_file_entry_alloc_offset(inode) +
			iinfo->i_lenEAttr;
	अन्यथा
		ptr = epos->bh->b_data + epos->offset;

	चयन (iinfo->i_alloc_type) अणु
	हाल ICBTAG_FLAG_AD_SHORT:
		sad = (काष्ठा लघु_ad *)ptr;
		sad->extLength = cpu_to_le32(elen);
		sad->extPosition = cpu_to_le32(eloc->logicalBlockNum);
		adsize = माप(काष्ठा लघु_ad);
		अवरोध;
	हाल ICBTAG_FLAG_AD_LONG:
		lad = (काष्ठा दीर्घ_ad *)ptr;
		lad->extLength = cpu_to_le32(elen);
		lad->extLocation = cpu_to_lelb(*eloc);
		स_रखो(lad->impUse, 0x00, माप(lad->impUse));
		adsize = माप(काष्ठा दीर्घ_ad);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (epos->bh) अणु
		अगर (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
		    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201) अणु
			काष्ठा allocExtDesc *aed =
				(काष्ठा allocExtDesc *)epos->bh->b_data;
			udf_update_tag(epos->bh->b_data,
				       le32_to_cpu(aed->lengthAllocDescs) +
				       माप(काष्ठा allocExtDesc));
		पूर्ण
		mark_buffer_dirty_inode(epos->bh, inode);
	पूर्ण अन्यथा अणु
		mark_inode_dirty(inode);
	पूर्ण

	अगर (inc)
		epos->offset += adsize;
पूर्ण

/*
 * Only 1 indirect extent in a row really makes sense but allow upto 16 in हाल
 * someone करोes some weird stuff.
 */
#घोषणा UDF_MAX_INसूची_EXTS 16

पूर्णांक8_t udf_next_aext(काष्ठा inode *inode, काष्ठा extent_position *epos,
		     काष्ठा kernel_lb_addr *eloc, uपूर्णांक32_t *elen, पूर्णांक inc)
अणु
	पूर्णांक8_t etype;
	अचिन्हित पूर्णांक indirections = 0;

	जबतक ((etype = udf_current_aext(inode, epos, eloc, elen, inc)) ==
	       (EXT_NEXT_EXTENT_ALLOCDESCS >> 30)) अणु
		udf_pblk_t block;

		अगर (++indirections > UDF_MAX_INसूची_EXTS) अणु
			udf_err(inode->i_sb,
				"too many indirect extents in inode %lu\n",
				inode->i_ino);
			वापस -1;
		पूर्ण

		epos->block = *eloc;
		epos->offset = माप(काष्ठा allocExtDesc);
		brअन्यथा(epos->bh);
		block = udf_get_lb_pblock(inode->i_sb, &epos->block, 0);
		epos->bh = udf_tपढ़ो(inode->i_sb, block);
		अगर (!epos->bh) अणु
			udf_debug("reading block %u failed!\n", block);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस etype;
पूर्ण

पूर्णांक8_t udf_current_aext(काष्ठा inode *inode, काष्ठा extent_position *epos,
			काष्ठा kernel_lb_addr *eloc, uपूर्णांक32_t *elen, पूर्णांक inc)
अणु
	पूर्णांक alen;
	पूर्णांक8_t etype;
	uपूर्णांक8_t *ptr;
	काष्ठा लघु_ad *sad;
	काष्ठा दीर्घ_ad *lad;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	अगर (!epos->bh) अणु
		अगर (!epos->offset)
			epos->offset = udf_file_entry_alloc_offset(inode);
		ptr = iinfo->i_data + epos->offset -
			udf_file_entry_alloc_offset(inode) +
			iinfo->i_lenEAttr;
		alen = udf_file_entry_alloc_offset(inode) +
							iinfo->i_lenAlloc;
	पूर्ण अन्यथा अणु
		अगर (!epos->offset)
			epos->offset = माप(काष्ठा allocExtDesc);
		ptr = epos->bh->b_data + epos->offset;
		alen = माप(काष्ठा allocExtDesc) +
			le32_to_cpu(((काष्ठा allocExtDesc *)epos->bh->b_data)->
							lengthAllocDescs);
	पूर्ण

	चयन (iinfo->i_alloc_type) अणु
	हाल ICBTAG_FLAG_AD_SHORT:
		sad = udf_get_fileलघुad(ptr, alen, &epos->offset, inc);
		अगर (!sad)
			वापस -1;
		etype = le32_to_cpu(sad->extLength) >> 30;
		eloc->logicalBlockNum = le32_to_cpu(sad->extPosition);
		eloc->partitionReferenceNum =
				iinfo->i_location.partitionReferenceNum;
		*elen = le32_to_cpu(sad->extLength) & UDF_EXTENT_LENGTH_MASK;
		अवरोध;
	हाल ICBTAG_FLAG_AD_LONG:
		lad = udf_get_fileदीर्घad(ptr, alen, &epos->offset, inc);
		अगर (!lad)
			वापस -1;
		etype = le32_to_cpu(lad->extLength) >> 30;
		*eloc = lelb_to_cpu(lad->extLocation);
		*elen = le32_to_cpu(lad->extLength) & UDF_EXTENT_LENGTH_MASK;
		अवरोध;
	शेष:
		udf_debug("alloc_type = %u unsupported\n", iinfo->i_alloc_type);
		वापस -1;
	पूर्ण

	वापस etype;
पूर्ण

अटल पूर्णांक8_t udf_insert_aext(काष्ठा inode *inode, काष्ठा extent_position epos,
			      काष्ठा kernel_lb_addr neloc, uपूर्णांक32_t nelen)
अणु
	काष्ठा kernel_lb_addr oeloc;
	uपूर्णांक32_t oelen;
	पूर्णांक8_t etype;

	अगर (epos.bh)
		get_bh(epos.bh);

	जबतक ((etype = udf_next_aext(inode, &epos, &oeloc, &oelen, 0)) != -1) अणु
		udf_ग_लिखो_aext(inode, &epos, &neloc, nelen, 1);
		neloc = oeloc;
		nelen = (etype << 30) | oelen;
	पूर्ण
	udf_add_aext(inode, &epos, &neloc, nelen, 1);
	brअन्यथा(epos.bh);

	वापस (nelen >> 30);
पूर्ण

पूर्णांक8_t udf_delete_aext(काष्ठा inode *inode, काष्ठा extent_position epos)
अणु
	काष्ठा extent_position oepos;
	पूर्णांक adsize;
	पूर्णांक8_t etype;
	काष्ठा allocExtDesc *aed;
	काष्ठा udf_inode_info *iinfo;
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen;

	अगर (epos.bh) अणु
		get_bh(epos.bh);
		get_bh(epos.bh);
	पूर्ण

	iinfo = UDF_I(inode);
	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		adsize = 0;

	oepos = epos;
	अगर (udf_next_aext(inode, &epos, &eloc, &elen, 1) == -1)
		वापस -1;

	जबतक ((etype = udf_next_aext(inode, &epos, &eloc, &elen, 1)) != -1) अणु
		udf_ग_लिखो_aext(inode, &oepos, &eloc, (etype << 30) | elen, 1);
		अगर (oepos.bh != epos.bh) अणु
			oepos.block = epos.block;
			brअन्यथा(oepos.bh);
			get_bh(epos.bh);
			oepos.bh = epos.bh;
			oepos.offset = epos.offset - adsize;
		पूर्ण
	पूर्ण
	स_रखो(&eloc, 0x00, माप(काष्ठा kernel_lb_addr));
	elen = 0;

	अगर (epos.bh != oepos.bh) अणु
		udf_मुक्त_blocks(inode->i_sb, inode, &epos.block, 0, 1);
		udf_ग_लिखो_aext(inode, &oepos, &eloc, elen, 1);
		udf_ग_लिखो_aext(inode, &oepos, &eloc, elen, 1);
		अगर (!oepos.bh) अणु
			iinfo->i_lenAlloc -= (adsize * 2);
			mark_inode_dirty(inode);
		पूर्ण अन्यथा अणु
			aed = (काष्ठा allocExtDesc *)oepos.bh->b_data;
			le32_add_cpu(&aed->lengthAllocDescs, -(2 * adsize));
			अगर (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
			    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
				udf_update_tag(oepos.bh->b_data,
						oepos.offset - (2 * adsize));
			अन्यथा
				udf_update_tag(oepos.bh->b_data,
						माप(काष्ठा allocExtDesc));
			mark_buffer_dirty_inode(oepos.bh, inode);
		पूर्ण
	पूर्ण अन्यथा अणु
		udf_ग_लिखो_aext(inode, &oepos, &eloc, elen, 1);
		अगर (!oepos.bh) अणु
			iinfo->i_lenAlloc -= adsize;
			mark_inode_dirty(inode);
		पूर्ण अन्यथा अणु
			aed = (काष्ठा allocExtDesc *)oepos.bh->b_data;
			le32_add_cpu(&aed->lengthAllocDescs, -adsize);
			अगर (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
			    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
				udf_update_tag(oepos.bh->b_data,
						epos.offset - adsize);
			अन्यथा
				udf_update_tag(oepos.bh->b_data,
						माप(काष्ठा allocExtDesc));
			mark_buffer_dirty_inode(oepos.bh, inode);
		पूर्ण
	पूर्ण

	brअन्यथा(epos.bh);
	brअन्यथा(oepos.bh);

	वापस (elen >> 30);
पूर्ण

पूर्णांक8_t inode_bmap(काष्ठा inode *inode, sector_t block,
		  काष्ठा extent_position *pos, काष्ठा kernel_lb_addr *eloc,
		  uपूर्णांक32_t *elen, sector_t *offset)
अणु
	अचिन्हित अक्षर blocksize_bits = inode->i_sb->s_blocksize_bits;
	loff_t lbcount = 0, bcount = (loff_t) block << blocksize_bits;
	पूर्णांक8_t etype;
	काष्ठा udf_inode_info *iinfo;

	iinfo = UDF_I(inode);
	अगर (!udf_पढ़ो_extent_cache(inode, bcount, &lbcount, pos)) अणु
		pos->offset = 0;
		pos->block = iinfo->i_location;
		pos->bh = शून्य;
	पूर्ण
	*elen = 0;
	करो अणु
		etype = udf_next_aext(inode, pos, eloc, elen, 1);
		अगर (etype == -1) अणु
			*offset = (bcount - lbcount) >> blocksize_bits;
			iinfo->i_lenExtents = lbcount;
			वापस -1;
		पूर्ण
		lbcount += *elen;
	पूर्ण जबतक (lbcount <= bcount);
	/* update extent cache */
	udf_update_extent_cache(inode, lbcount - *elen, pos);
	*offset = (bcount + *elen - lbcount) >> blocksize_bits;

	वापस etype;
पूर्ण

udf_pblk_t udf_block_map(काष्ठा inode *inode, sector_t block)
अणु
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen;
	sector_t offset;
	काष्ठा extent_position epos = अणुपूर्ण;
	udf_pblk_t ret;

	करोwn_पढ़ो(&UDF_I(inode)->i_data_sem);

	अगर (inode_bmap(inode, block, &epos, &eloc, &elen, &offset) ==
						(EXT_RECORDED_ALLOCATED >> 30))
		ret = udf_get_lb_pblock(inode->i_sb, &eloc, offset);
	अन्यथा
		ret = 0;

	up_पढ़ो(&UDF_I(inode)->i_data_sem);
	brअन्यथा(epos.bh);

	अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_VARCONV))
		वापस udf_fixed_to_variable(ret);
	अन्यथा
		वापस ret;
पूर्ण
