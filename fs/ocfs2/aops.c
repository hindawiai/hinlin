<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/swap.h>
#समावेश <linux/mpage.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/uपन.स>
#समावेश <linux/mm.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "aops.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "file.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "suballoc.h"
#समावेश "super.h"
#समावेश "symlink.h"
#समावेश "refcounttree.h"
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"
#समावेश "dir.h"
#समावेश "namei.h"
#समावेश "sysfile.h"

अटल पूर्णांक ocfs2_symlink_get_block(काष्ठा inode *inode, sector_t iblock,
				   काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक err = -EIO;
	पूर्णांक status;
	काष्ठा ocfs2_dinode *fe = शून्य;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा buffer_head *buffer_cache_bh = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	व्योम *kaddr;

	trace_ocfs2_symlink_get_block(
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			(अचिन्हित दीर्घ दीर्घ)iblock, bh_result, create);

	BUG_ON(ocfs2_inode_is_fast_symlink(inode));

	अगर ((iblock << inode->i_sb->s_blocksize_bits) > PATH_MAX + 1) अणु
		mlog(ML_ERROR, "block offset > PATH_MAX: %llu",
		     (अचिन्हित दीर्घ दीर्घ)iblock);
		जाओ bail;
	पूर्ण

	status = ocfs2_पढ़ो_inode_block(inode, &bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	fe = (काष्ठा ocfs2_dinode *) bh->b_data;

	अगर ((u64)iblock >= ocfs2_clusters_to_blocks(inode->i_sb,
						    le32_to_cpu(fe->i_clusters))) अणु
		err = -ENOMEM;
		mlog(ML_ERROR, "block offset is outside the allocated size: "
		     "%llu\n", (अचिन्हित दीर्घ दीर्घ)iblock);
		जाओ bail;
	पूर्ण

	/* We करोn't use the page cache to create symlink data, so अगर
	 * need be, copy it over from the buffer cache. */
	अगर (!buffer_uptodate(bh_result) && ocfs2_inode_is_new(inode)) अणु
		u64 blkno = le64_to_cpu(fe->id2.i_list.l_recs[0].e_blkno) +
			    iblock;
		buffer_cache_bh = sb_getblk(osb->sb, blkno);
		अगर (!buffer_cache_bh) अणु
			err = -ENOMEM;
			mlog(ML_ERROR, "couldn't getblock for symlink!\n");
			जाओ bail;
		पूर्ण

		/* we haven't locked out transactions, so a commit
		 * could've happened. Since we've got a reference on
		 * the bh, even अगर it commits जबतक we're करोing the
		 * copy, the data is still good. */
		अगर (buffer_jbd(buffer_cache_bh)
		    && ocfs2_inode_is_new(inode)) अणु
			kaddr = kmap_atomic(bh_result->b_page);
			अगर (!kaddr) अणु
				mlog(ML_ERROR, "couldn't kmap!\n");
				जाओ bail;
			पूर्ण
			स_नकल(kaddr + (bh_result->b_size * iblock),
			       buffer_cache_bh->b_data,
			       bh_result->b_size);
			kunmap_atomic(kaddr);
			set_buffer_uptodate(bh_result);
		पूर्ण
		brअन्यथा(buffer_cache_bh);
	पूर्ण

	map_bh(bh_result, inode->i_sb,
	       le64_to_cpu(fe->id2.i_list.l_recs[0].e_blkno) + iblock);

	err = 0;

bail:
	brअन्यथा(bh);

	वापस err;
पूर्ण

अटल पूर्णांक ocfs2_lock_get_block(काष्ठा inode *inode, sector_t iblock,
		    काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	करोwn_पढ़ो(&oi->ip_alloc_sem);
	ret = ocfs2_get_block(inode, iblock, bh_result, create);
	up_पढ़ो(&oi->ip_alloc_sem);

	वापस ret;
पूर्ण

पूर्णांक ocfs2_get_block(काष्ठा inode *inode, sector_t iblock,
		    काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक ext_flags;
	u64 max_blocks = bh_result->b_size >> inode->i_blkbits;
	u64 p_blkno, count, past_eof;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	trace_ocfs2_get_block((अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			      (अचिन्हित दीर्घ दीर्घ)iblock, bh_result, create);

	अगर (OCFS2_I(inode)->ip_flags & OCFS2_INODE_SYSTEM_खाता)
		mlog(ML_NOTICE, "get_block on system inode 0x%p (%lu)\n",
		     inode, inode->i_ino);

	अगर (S_ISLNK(inode->i_mode)) अणु
		/* this always करोes I/O क्रम some reason. */
		err = ocfs2_symlink_get_block(inode, iblock, bh_result, create);
		जाओ bail;
	पूर्ण

	err = ocfs2_extent_map_get_blocks(inode, iblock, &p_blkno, &count,
					  &ext_flags);
	अगर (err) अणु
		mlog(ML_ERROR, "Error %d from get_blocks(0x%p, %llu, 1, "
		     "%llu, NULL)\n", err, inode, (अचिन्हित दीर्घ दीर्घ)iblock,
		     (अचिन्हित दीर्घ दीर्घ)p_blkno);
		जाओ bail;
	पूर्ण

	अगर (max_blocks < count)
		count = max_blocks;

	/*
	 * ocfs2 never allocates in this function - the only समय we
	 * need to use BH_New is when we're extending i_size on a file
	 * प्रणाली which करोesn't support holes, in which हाल BH_New
	 * allows __block_ग_लिखो_begin() to zero.
	 *
	 * If we see this on a sparse file प्रणाली, then a truncate has
	 * raced us and हटाओd the cluster. In this हाल, we clear
	 * the buffers dirty and uptodate bits and let the buffer code
	 * ignore it as a hole.
	 */
	अगर (create && p_blkno == 0 && ocfs2_sparse_alloc(osb)) अणु
		clear_buffer_dirty(bh_result);
		clear_buffer_uptodate(bh_result);
		जाओ bail;
	पूर्ण

	/* Treat the unwritten extent as a hole क्रम zeroing purposes. */
	अगर (p_blkno && !(ext_flags & OCFS2_EXT_UNWRITTEN))
		map_bh(bh_result, inode->i_sb, p_blkno);

	bh_result->b_size = count << inode->i_blkbits;

	अगर (!ocfs2_sparse_alloc(osb)) अणु
		अगर (p_blkno == 0) अणु
			err = -EIO;
			mlog(ML_ERROR,
			     "iblock = %llu p_blkno = %llu blkno=(%llu)\n",
			     (अचिन्हित दीर्घ दीर्घ)iblock,
			     (अचिन्हित दीर्घ दीर्घ)p_blkno,
			     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
			mlog(ML_ERROR, "Size %llu, clusters %u\n", (अचिन्हित दीर्घ दीर्घ)i_size_पढ़ो(inode), OCFS2_I(inode)->ip_clusters);
			dump_stack();
			जाओ bail;
		पूर्ण
	पूर्ण

	past_eof = ocfs2_blocks_क्रम_bytes(inode->i_sb, i_size_पढ़ो(inode));

	trace_ocfs2_get_block_end((अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
				  (अचिन्हित दीर्घ दीर्घ)past_eof);
	अगर (create && (iblock >= past_eof))
		set_buffer_new(bh_result);

bail:
	अगर (err < 0)
		err = -EIO;

	वापस err;
पूर्ण

पूर्णांक ocfs2_पढ़ो_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *page,
			   काष्ठा buffer_head *di_bh)
अणु
	व्योम *kaddr;
	loff_t size;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	अगर (!(le16_to_cpu(di->i_dyn_features) & OCFS2_INLINE_DATA_FL)) अणु
		ocfs2_error(inode->i_sb, "Inode %llu lost inline data flag\n",
			    (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
		वापस -EROFS;
	पूर्ण

	size = i_size_पढ़ो(inode);

	अगर (size > PAGE_SIZE ||
	    size > ocfs2_max_अंतरभूत_data_with_xattr(inode->i_sb, di)) अणु
		ocfs2_error(inode->i_sb,
			    "Inode %llu has with inline data has bad size: %Lu\n",
			    (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			    (अचिन्हित दीर्घ दीर्घ)size);
		वापस -EROFS;
	पूर्ण

	kaddr = kmap_atomic(page);
	अगर (size)
		स_नकल(kaddr, di->id2.i_data.id_data, size);
	/* Clear the reमुख्यing part of the page */
	स_रखो(kaddr + size, 0, PAGE_SIZE - size);
	flush_dcache_page(page);
	kunmap_atomic(kaddr);

	SetPageUptodate(page);

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_पढ़ोpage_अंतरभूत(काष्ठा inode *inode, काष्ठा page *page)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *di_bh = शून्य;

	BUG_ON(!PageLocked(page));
	BUG_ON(!(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL));

	ret = ocfs2_पढ़ो_inode_block(inode, &di_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_अंतरभूत_data(inode, page, di_bh);
out:
	unlock_page(page);

	brअन्यथा(di_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	loff_t start = (loff_t)page->index << PAGE_SHIFT;
	पूर्णांक ret, unlock = 1;

	trace_ocfs2_पढ़ोpage((अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
			     (page ? page->index : 0));

	ret = ocfs2_inode_lock_with_page(inode, शून्य, 0, page);
	अगर (ret != 0) अणु
		अगर (ret == AOP_TRUNCATED_PAGE)
			unlock = 0;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (करोwn_पढ़ो_trylock(&oi->ip_alloc_sem) == 0) अणु
		/*
		 * Unlock the page and cycle ip_alloc_sem so that we करोn't
		 * busyloop रुकोing क्रम ip_alloc_sem to unlock
		 */
		ret = AOP_TRUNCATED_PAGE;
		unlock_page(page);
		unlock = 0;
		करोwn_पढ़ो(&oi->ip_alloc_sem);
		up_पढ़ो(&oi->ip_alloc_sem);
		जाओ out_inode_unlock;
	पूर्ण

	/*
	 * i_size might have just been updated as we grabed the meta lock.  We
	 * might now be discovering a truncate that hit on another node.
	 * block_पढ़ो_full_page->get_block freaks out अगर it is asked to पढ़ो
	 * beyond the end of a file, so we check here.  Callers
	 * (generic_file_पढ़ो, vm_ops->fault) are clever enough to check i_size
	 * and notice that the page they just पढ़ो isn't needed.
	 *
	 * XXX sys_पढ़ोahead() seems to get that wrong?
	 */
	अगर (start >= i_size_पढ़ो(inode)) अणु
		zero_user(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
		ret = 0;
		जाओ out_alloc;
	पूर्ण

	अगर (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		ret = ocfs2_पढ़ोpage_अंतरभूत(inode, page);
	अन्यथा
		ret = block_पढ़ो_full_page(page, ocfs2_get_block);
	unlock = 0;

out_alloc:
	up_पढ़ो(&oi->ip_alloc_sem);
out_inode_unlock:
	ocfs2_inode_unlock(inode, 0);
out:
	अगर (unlock)
		unlock_page(page);
	वापस ret;
पूर्ण

/*
 * This is used only क्रम पढ़ो-ahead. Failures or dअगरficult to handle
 * situations are safe to ignore.
 *
 * Right now, we करोn't bother with BH_Boundary - in-inode extent lists
 * are quite large (243 extents on 4k blocks), so most inodes करोn't
 * grow out to a tree. If need be, detecting boundary extents could
 * trivially be added in a future version of ocfs2_get_block().
 */
अटल व्योम ocfs2_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode = rac->mapping->host;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	/*
	 * Use the nonblocking flag क्रम the dlm code to aव्योम page
	 * lock inversion, but करोn't bother with retrying.
	 */
	ret = ocfs2_inode_lock_full(inode, शून्य, 0, OCFS2_LOCK_NONBLOCK);
	अगर (ret)
		वापस;

	अगर (करोwn_पढ़ो_trylock(&oi->ip_alloc_sem) == 0)
		जाओ out_unlock;

	/*
	 * Don't bother with inline-data. There isn't anything
	 * to पढ़ो-ahead in that हाल anyway...
	 */
	अगर (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		जाओ out_up;

	/*
	 * Check whether a remote node truncated this file - we just
	 * drop out in that हाल as it's not worth handling here.
	 */
	अगर (पढ़ोahead_pos(rac) >= i_size_पढ़ो(inode))
		जाओ out_up;

	mpage_पढ़ोahead(rac, ocfs2_get_block);

out_up:
	up_पढ़ो(&oi->ip_alloc_sem);
out_unlock:
	ocfs2_inode_unlock(inode, 0);
पूर्ण

/* Note: Because we करोn't support holes, our allocation has
 * alपढ़ोy happened (allocation ग_लिखोs zeros to the file data)
 * so we करोn't have to worry about ordered ग_लिखोs in
 * ocfs2_ग_लिखोpage.
 *
 * ->ग_लिखोpage is called during the process of invalidating the page cache
 * during blocked lock processing.  It can't block on any cluster locks
 * to during block mapping.  It's relying on the fact that the block
 * mapping can't have disappeared under the dirty pages that it is
 * being asked to ग_लिखो back.
 */
अटल पूर्णांक ocfs2_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	trace_ocfs2_ग_लिखोpage(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(page->mapping->host)->ip_blkno,
		page->index);

	वापस block_ग_लिखो_full_page(page, ocfs2_get_block, wbc);
पूर्ण

/* Taken from ext3. We करोn't necessarily need the full blown
 * functionality yet, but IMHO it's better to cut and paste the whole
 * thing so we can aव्योम पूर्णांकroducing our own bugs (and easily pick up
 * their fixes when they happen) --Mark */
पूर्णांक walk_page_buffers(	handle_t *handle,
			काष्ठा buffer_head *head,
			अचिन्हित from,
			अचिन्हित to,
			पूर्णांक *partial,
			पूर्णांक (*fn)(	handle_t *handle,
					काष्ठा buffer_head *bh))
अणु
	काष्ठा buffer_head *bh;
	अचिन्हित block_start, block_end;
	अचिन्हित blocksize = head->b_size;
	पूर्णांक err, ret = 0;
	काष्ठा buffer_head *next;

	क्रम (	bh = head, block_start = 0;
		ret == 0 && (bh != head || !block_start);
	    	block_start = block_end, bh = next)
	अणु
		next = bh->b_this_page;
		block_end = block_start + blocksize;
		अगर (block_end <= from || block_start >= to) अणु
			अगर (partial && !buffer_uptodate(bh))
				*partial = 1;
			जारी;
		पूर्ण
		err = (*fn)(handle, bh);
		अगर (!ret)
			ret = err;
	पूर्ण
	वापस ret;
पूर्ण

अटल sector_t ocfs2_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	sector_t status;
	u64 p_blkno = 0;
	पूर्णांक err = 0;
	काष्ठा inode *inode = mapping->host;

	trace_ocfs2_bmap((अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			 (अचिन्हित दीर्घ दीर्घ)block);

	/*
	 * The swap code (ab-)uses ->bmap to get a block mapping and then
	 * bypasseल the file प्रणाली क्रम actual I/O.  We really can't allow
	 * that on refcounted inodes, so we have to skip out here.  And yes,
	 * 0 is the magic code क्रम a bmap error..
	 */
	अगर (ocfs2_is_refcount_inode(inode))
		वापस 0;

	/* We करोn't need to lock journal system files, since they aren't
	 * accessed concurrently from multiple nodes.
	 */
	अगर (!INODE_JOURNAL(inode)) अणु
		err = ocfs2_inode_lock(inode, शून्य, 0);
		अगर (err) अणु
			अगर (err != -ENOENT)
				mlog_त्रुटि_सं(err);
			जाओ bail;
		पूर्ण
		करोwn_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);
	पूर्ण

	अगर (!(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL))
		err = ocfs2_extent_map_get_blocks(inode, block, &p_blkno, शून्य,
						  शून्य);

	अगर (!INODE_JOURNAL(inode)) अणु
		up_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);
		ocfs2_inode_unlock(inode, 0);
	पूर्ण

	अगर (err) अणु
		mlog(ML_ERROR, "get_blocks() failed, block = %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)block);
		mlog_त्रुटि_सं(err);
		जाओ bail;
	पूर्ण

bail:
	status = err ? 0 : p_blkno;

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_releasepage(काष्ठा page *page, gfp_t रुको)
अणु
	अगर (!page_has_buffers(page))
		वापस 0;
	वापस try_to_मुक्त_buffers(page);
पूर्ण

अटल व्योम ocfs2_figure_cluster_boundaries(काष्ठा ocfs2_super *osb,
					    u32 cpos,
					    अचिन्हित पूर्णांक *start,
					    अचिन्हित पूर्णांक *end)
अणु
	अचिन्हित पूर्णांक cluster_start = 0, cluster_end = PAGE_SIZE;

	अगर (unlikely(PAGE_SHIFT > osb->s_clustersize_bits)) अणु
		अचिन्हित पूर्णांक cpp;

		cpp = 1 << (PAGE_SHIFT - osb->s_clustersize_bits);

		cluster_start = cpos % cpp;
		cluster_start = cluster_start << osb->s_clustersize_bits;

		cluster_end = cluster_start + osb->s_clustersize;
	पूर्ण

	BUG_ON(cluster_start > PAGE_SIZE);
	BUG_ON(cluster_end > PAGE_SIZE);

	अगर (start)
		*start = cluster_start;
	अगर (end)
		*end = cluster_end;
पूर्ण

/*
 * 'from' and 'to' are the region in the page to aव्योम zeroing.
 *
 * If pagesize > clustersize, this function will aव्योम zeroing outside
 * of the cluster boundary.
 *
 * from == to == 0 is code क्रम "zero the entire cluster region"
 */
अटल व्योम ocfs2_clear_page_regions(काष्ठा page *page,
				     काष्ठा ocfs2_super *osb, u32 cpos,
				     अचिन्हित from, अचिन्हित to)
अणु
	व्योम *kaddr;
	अचिन्हित पूर्णांक cluster_start, cluster_end;

	ocfs2_figure_cluster_boundaries(osb, cpos, &cluster_start, &cluster_end);

	kaddr = kmap_atomic(page);

	अगर (from || to) अणु
		अगर (from > cluster_start)
			स_रखो(kaddr + cluster_start, 0, from - cluster_start);
		अगर (to < cluster_end)
			स_रखो(kaddr + to, 0, cluster_end - to);
	पूर्ण अन्यथा अणु
		स_रखो(kaddr + cluster_start, 0, cluster_end - cluster_start);
	पूर्ण

	kunmap_atomic(kaddr);
पूर्ण

/*
 * Nonsparse file प्रणालीs fully allocate beक्रमe we get to the ग_लिखो
 * code. This prevents ocfs2_ग_लिखो() from tagging the ग_लिखो as an
 * allocating one, which means ocfs2_map_page_blocks() might try to
 * पढ़ो-in the blocks at the tail of our file. Aव्योम पढ़ोing them by
 * testing i_size against each block offset.
 */
अटल पूर्णांक ocfs2_should_पढ़ो_blk(काष्ठा inode *inode, काष्ठा page *page,
				 अचिन्हित पूर्णांक block_start)
अणु
	u64 offset = page_offset(page) + block_start;

	अगर (ocfs2_sparse_alloc(OCFS2_SB(inode->i_sb)))
		वापस 1;

	अगर (i_size_पढ़ो(inode) > offset)
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Some of this taken from __block_ग_लिखो_begin(). We alपढ़ोy have our
 * mapping by now though, and the entire ग_लिखो will be allocating or
 * it won't, so not much need to use BH_New.
 *
 * This will also skip zeroing, which is handled बाह्यally.
 */
पूर्णांक ocfs2_map_page_blocks(काष्ठा page *page, u64 *p_blkno,
			  काष्ठा inode *inode, अचिन्हित पूर्णांक from,
			  अचिन्हित पूर्णांक to, पूर्णांक new)
अणु
	पूर्णांक ret = 0;
	काष्ठा buffer_head *head, *bh, *रुको[2], **रुको_bh = रुको;
	अचिन्हित पूर्णांक block_end, block_start;
	अचिन्हित पूर्णांक bsize = i_blocksize(inode);

	अगर (!page_has_buffers(page))
		create_empty_buffers(page, bsize, 0);

	head = page_buffers(page);
	क्रम (bh = head, block_start = 0; bh != head || !block_start;
	     bh = bh->b_this_page, block_start += bsize) अणु
		block_end = block_start + bsize;

		clear_buffer_new(bh);

		/*
		 * Ignore blocks outside of our i/o range -
		 * they may beदीर्घ to unallocated clusters.
		 */
		अगर (block_start >= to || block_end <= from) अणु
			अगर (PageUptodate(page))
				set_buffer_uptodate(bh);
			जारी;
		पूर्ण

		/*
		 * For an allocating ग_लिखो with cluster size >= page
		 * size, we always ग_लिखो the entire page.
		 */
		अगर (new)
			set_buffer_new(bh);

		अगर (!buffer_mapped(bh)) अणु
			map_bh(bh, inode->i_sb, *p_blkno);
			clean_bdev_bh_alias(bh);
		पूर्ण

		अगर (PageUptodate(page)) अणु
			अगर (!buffer_uptodate(bh))
				set_buffer_uptodate(bh);
		पूर्ण अन्यथा अगर (!buffer_uptodate(bh) && !buffer_delay(bh) &&
			   !buffer_new(bh) &&
			   ocfs2_should_पढ़ो_blk(inode, page, block_start) &&
			   (block_start < from || block_end > to)) अणु
			ll_rw_block(REQ_OP_READ, 0, 1, &bh);
			*रुको_bh++=bh;
		पूर्ण

		*p_blkno = *p_blkno + 1;
	पूर्ण

	/*
	 * If we issued पढ़ो requests - let them complete.
	 */
	जबतक(रुको_bh > रुको) अणु
		रुको_on_buffer(*--रुको_bh);
		अगर (!buffer_uptodate(*रुको_bh))
			ret = -EIO;
	पूर्ण

	अगर (ret == 0 || !new)
		वापस ret;

	/*
	 * If we get -EIO above, zero out any newly allocated blocks
	 * to aव्योम exposing stale data.
	 */
	bh = head;
	block_start = 0;
	करो अणु
		block_end = block_start + bsize;
		अगर (block_end <= from)
			जाओ next_bh;
		अगर (block_start >= to)
			अवरोध;

		zero_user(page, block_start, bh->b_size);
		set_buffer_uptodate(bh);
		mark_buffer_dirty(bh);

next_bh:
		block_start = block_end;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);

	वापस ret;
पूर्ण

#अगर (PAGE_SIZE >= OCFS2_MAX_CLUSTERSIZE)
#घोषणा OCFS2_MAX_CTXT_PAGES	1
#अन्यथा
#घोषणा OCFS2_MAX_CTXT_PAGES	(OCFS2_MAX_CLUSTERSIZE / PAGE_SIZE)
#पूर्ण_अगर

#घोषणा OCFS2_MAX_CLUSTERS_PER_PAGE	(PAGE_SIZE / OCFS2_MIN_CLUSTERSIZE)

काष्ठा ocfs2_unwritten_extent अणु
	काष्ठा list_head	ue_node;
	काष्ठा list_head	ue_ip_node;
	u32			ue_cpos;
	u32			ue_phys;
पूर्ण;

/*
 * Describe the state of a single cluster to be written to.
 */
काष्ठा ocfs2_ग_लिखो_cluster_desc अणु
	u32		c_cpos;
	u32		c_phys;
	/*
	 * Give this a unique field because c_phys eventually माला_लो
	 * filled.
	 */
	अचिन्हित	c_new;
	अचिन्हित	c_clear_unwritten;
	अचिन्हित	c_needs_zero;
पूर्ण;

काष्ठा ocfs2_ग_लिखो_ctxt अणु
	/* Logical cluster position / len of ग_लिखो */
	u32				w_cpos;
	u32				w_clen;

	/* First cluster allocated in a nonsparse extend */
	u32				w_first_new_cpos;

	/* Type of caller. Must be one of buffer, mmap, direct.  */
	ocfs2_ग_लिखो_type_t		w_type;

	काष्ठा ocfs2_ग_लिखो_cluster_desc	w_desc[OCFS2_MAX_CLUSTERS_PER_PAGE];

	/*
	 * This is true अगर page_size > cluster_size.
	 *
	 * It triggers a set of special हालs during ग_लिखो which might
	 * have to deal with allocating ग_लिखोs to partial pages.
	 */
	अचिन्हित पूर्णांक			w_large_pages;

	/*
	 * Pages involved in this ग_लिखो.
	 *
	 * w_target_page is the page being written to by the user.
	 *
	 * w_pages is an array of pages which always contains
	 * w_target_page, and in the हाल of an allocating ग_लिखो with
	 * page_size < cluster size, it will contain zero'd and mapped
	 * pages adjacent to w_target_page which need to be written
	 * out in so that future पढ़ोs from that region will get
	 * zero's.
	 */
	अचिन्हित पूर्णांक			w_num_pages;
	काष्ठा page			*w_pages[OCFS2_MAX_CTXT_PAGES];
	काष्ठा page			*w_target_page;

	/*
	 * w_target_locked is used क्रम page_mkग_लिखो path indicating no unlocking
	 * against w_target_page in ocfs2_ग_लिखो_end_nolock.
	 */
	अचिन्हित पूर्णांक			w_target_locked:1;

	/*
	 * ocfs2_ग_लिखो_end() uses this to know what the real range to
	 * ग_लिखो in the target should be.
	 */
	अचिन्हित पूर्णांक			w_target_from;
	अचिन्हित पूर्णांक			w_target_to;

	/*
	 * We could use journal_current_handle() but this is cleaner,
	 * IMHO -Mark
	 */
	handle_t			*w_handle;

	काष्ठा buffer_head		*w_di_bh;

	काष्ठा ocfs2_cached_dealloc_ctxt w_dealloc;

	काष्ठा list_head		w_unwritten_list;
	अचिन्हित पूर्णांक			w_unwritten_count;
पूर्ण;

व्योम ocfs2_unlock_and_मुक्त_pages(काष्ठा page **pages, पूर्णांक num_pages)
अणु
	पूर्णांक i;

	क्रम(i = 0; i < num_pages; i++) अणु
		अगर (pages[i]) अणु
			unlock_page(pages[i]);
			mark_page_accessed(pages[i]);
			put_page(pages[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ocfs2_unlock_pages(काष्ठा ocfs2_ग_लिखो_ctxt *wc)
अणु
	पूर्णांक i;

	/*
	 * w_target_locked is only set to true in the page_mkग_लिखो() हाल.
	 * The पूर्णांकent is to allow us to lock the target page from ग_लिखो_begin()
	 * to ग_लिखो_end(). The caller must hold a ref on w_target_page.
	 */
	अगर (wc->w_target_locked) अणु
		BUG_ON(!wc->w_target_page);
		क्रम (i = 0; i < wc->w_num_pages; i++) अणु
			अगर (wc->w_target_page == wc->w_pages[i]) अणु
				wc->w_pages[i] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		mark_page_accessed(wc->w_target_page);
		put_page(wc->w_target_page);
	पूर्ण
	ocfs2_unlock_and_मुक्त_pages(wc->w_pages, wc->w_num_pages);
पूर्ण

अटल व्योम ocfs2_मुक्त_unwritten_list(काष्ठा inode *inode,
				 काष्ठा list_head *head)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_unwritten_extent *ue = शून्य, *पंचांगp = शून्य;

	list_क्रम_each_entry_safe(ue, पंचांगp, head, ue_node) अणु
		list_del(&ue->ue_node);
		spin_lock(&oi->ip_lock);
		list_del(&ue->ue_ip_node);
		spin_unlock(&oi->ip_lock);
		kमुक्त(ue);
	पूर्ण
पूर्ण

अटल व्योम ocfs2_मुक्त_ग_लिखो_ctxt(काष्ठा inode *inode,
				  काष्ठा ocfs2_ग_लिखो_ctxt *wc)
अणु
	ocfs2_मुक्त_unwritten_list(inode, &wc->w_unwritten_list);
	ocfs2_unlock_pages(wc);
	brअन्यथा(wc->w_di_bh);
	kमुक्त(wc);
पूर्ण

अटल पूर्णांक ocfs2_alloc_ग_लिखो_ctxt(काष्ठा ocfs2_ग_लिखो_ctxt **wcp,
				  काष्ठा ocfs2_super *osb, loff_t pos,
				  अचिन्हित len, ocfs2_ग_लिखो_type_t type,
				  काष्ठा buffer_head *di_bh)
अणु
	u32 cend;
	काष्ठा ocfs2_ग_लिखो_ctxt *wc;

	wc = kzalloc(माप(काष्ठा ocfs2_ग_लिखो_ctxt), GFP_NOFS);
	अगर (!wc)
		वापस -ENOMEM;

	wc->w_cpos = pos >> osb->s_clustersize_bits;
	wc->w_first_new_cpos = अच_पूर्णांक_उच्च;
	cend = (pos + len - 1) >> osb->s_clustersize_bits;
	wc->w_clen = cend - wc->w_cpos + 1;
	get_bh(di_bh);
	wc->w_di_bh = di_bh;
	wc->w_type = type;

	अगर (unlikely(PAGE_SHIFT > osb->s_clustersize_bits))
		wc->w_large_pages = 1;
	अन्यथा
		wc->w_large_pages = 0;

	ocfs2_init_dealloc_ctxt(&wc->w_dealloc);
	INIT_LIST_HEAD(&wc->w_unwritten_list);

	*wcp = wc;

	वापस 0;
पूर्ण

/*
 * If a page has any new buffers, zero them out here, and mark them uptodate
 * and dirty so they'll be written out (in order to prevent uninitialised
 * block data from leaking). And clear the new bit.
 */
अटल व्योम ocfs2_zero_new_buffers(काष्ठा page *page, अचिन्हित from, अचिन्हित to)
अणु
	अचिन्हित पूर्णांक block_start, block_end;
	काष्ठा buffer_head *head, *bh;

	BUG_ON(!PageLocked(page));
	अगर (!page_has_buffers(page))
		वापस;

	bh = head = page_buffers(page);
	block_start = 0;
	करो अणु
		block_end = block_start + bh->b_size;

		अगर (buffer_new(bh)) अणु
			अगर (block_end > from && block_start < to) अणु
				अगर (!PageUptodate(page)) अणु
					अचिन्हित start, end;

					start = max(from, block_start);
					end = min(to, block_end);

					zero_user_segment(page, start, end);
					set_buffer_uptodate(bh);
				पूर्ण

				clear_buffer_new(bh);
				mark_buffer_dirty(bh);
			पूर्ण
		पूर्ण

		block_start = block_end;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
पूर्ण

/*
 * Only called when we have a failure during allocating ग_लिखो to ग_लिखो
 * zero's to the newly allocated region.
 */
अटल व्योम ocfs2_ग_लिखो_failure(काष्ठा inode *inode,
				काष्ठा ocfs2_ग_लिखो_ctxt *wc,
				loff_t user_pos, अचिन्हित user_len)
अणु
	पूर्णांक i;
	अचिन्हित from = user_pos & (PAGE_SIZE - 1),
		to = user_pos + user_len;
	काष्ठा page *पंचांगppage;

	अगर (wc->w_target_page)
		ocfs2_zero_new_buffers(wc->w_target_page, from, to);

	क्रम(i = 0; i < wc->w_num_pages; i++) अणु
		पंचांगppage = wc->w_pages[i];

		अगर (पंचांगppage && page_has_buffers(पंचांगppage)) अणु
			अगर (ocfs2_should_order_data(inode))
				ocfs2_jbd2_inode_add_ग_लिखो(wc->w_handle, inode,
							   user_pos, user_len);

			block_commit_ग_लिखो(पंचांगppage, from, to);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_prepare_page_क्रम_ग_लिखो(काष्ठा inode *inode, u64 *p_blkno,
					काष्ठा ocfs2_ग_लिखो_ctxt *wc,
					काष्ठा page *page, u32 cpos,
					loff_t user_pos, अचिन्हित user_len,
					पूर्णांक new)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक map_from = 0, map_to = 0;
	अचिन्हित पूर्णांक cluster_start, cluster_end;
	अचिन्हित पूर्णांक user_data_from = 0, user_data_to = 0;

	ocfs2_figure_cluster_boundaries(OCFS2_SB(inode->i_sb), cpos,
					&cluster_start, &cluster_end);

	/* treat the ग_लिखो as new अगर the a hole/lseek spanned across
	 * the page boundary.
	 */
	new = new | ((i_size_पढ़ो(inode) <= page_offset(page)) &&
			(page_offset(page) <= user_pos));

	अगर (page == wc->w_target_page) अणु
		map_from = user_pos & (PAGE_SIZE - 1);
		map_to = map_from + user_len;

		अगर (new)
			ret = ocfs2_map_page_blocks(page, p_blkno, inode,
						    cluster_start, cluster_end,
						    new);
		अन्यथा
			ret = ocfs2_map_page_blocks(page, p_blkno, inode,
						    map_from, map_to, new);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		user_data_from = map_from;
		user_data_to = map_to;
		अगर (new) अणु
			map_from = cluster_start;
			map_to = cluster_end;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If we haven't allocated the new page yet, we
		 * shouldn't be writing it out without copying user
		 * data. This is likely a math error from the caller.
		 */
		BUG_ON(!new);

		map_from = cluster_start;
		map_to = cluster_end;

		ret = ocfs2_map_page_blocks(page, p_blkno, inode,
					    cluster_start, cluster_end, new);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Parts of newly allocated pages need to be zero'd.
	 *
	 * Above, we have also rewritten 'to' and 'from' - as far as
	 * the rest of the function is concerned, the entire cluster
	 * range inside of a page needs to be written.
	 *
	 * We can skip this अगर the page is up to date - it's alपढ़ोy
	 * been zero'd from being पढ़ो in as a hole.
	 */
	अगर (new && !PageUptodate(page))
		ocfs2_clear_page_regions(page, OCFS2_SB(inode->i_sb),
					 cpos, user_data_from, user_data_to);

	flush_dcache_page(page);

out:
	वापस ret;
पूर्ण

/*
 * This function will only grab one clusters worth of pages.
 */
अटल पूर्णांक ocfs2_grab_pages_क्रम_ग_लिखो(काष्ठा address_space *mapping,
				      काष्ठा ocfs2_ग_लिखो_ctxt *wc,
				      u32 cpos, loff_t user_pos,
				      अचिन्हित user_len, पूर्णांक new,
				      काष्ठा page *mmap_page)
अणु
	पूर्णांक ret = 0, i;
	अचिन्हित दीर्घ start, target_index, end_index, index;
	काष्ठा inode *inode = mapping->host;
	loff_t last_byte;

	target_index = user_pos >> PAGE_SHIFT;

	/*
	 * Figure out how many pages we'll be manipulating here. For
	 * non allocating ग_लिखो, we just change the one
	 * page. Otherwise, we'll need a whole clusters worth.  If we're
	 * writing past i_size, we only need enough pages to cover the
	 * last page of the ग_लिखो.
	 */
	अगर (new) अणु
		wc->w_num_pages = ocfs2_pages_per_cluster(inode->i_sb);
		start = ocfs2_align_clusters_to_page_index(inode->i_sb, cpos);
		/*
		 * We need the index *past* the last page we could possibly
		 * touch.  This is the page past the end of the ग_लिखो or
		 * i_size, whichever is greater.
		 */
		last_byte = max(user_pos + user_len, i_size_पढ़ो(inode));
		BUG_ON(last_byte < 1);
		end_index = ((last_byte - 1) >> PAGE_SHIFT) + 1;
		अगर ((start + wc->w_num_pages) > end_index)
			wc->w_num_pages = end_index - start;
	पूर्ण अन्यथा अणु
		wc->w_num_pages = 1;
		start = target_index;
	पूर्ण
	end_index = (user_pos + user_len - 1) >> PAGE_SHIFT;

	क्रम(i = 0; i < wc->w_num_pages; i++) अणु
		index = start + i;

		अगर (index >= target_index && index <= end_index &&
		    wc->w_type == OCFS2_WRITE_MMAP) अणु
			/*
			 * ocfs2_pagemkग_लिखो() is a little dअगरferent
			 * and wants us to directly use the page
			 * passed in.
			 */
			lock_page(mmap_page);

			/* Exit and let the caller retry */
			अगर (mmap_page->mapping != mapping) अणु
				WARN_ON(mmap_page->mapping);
				unlock_page(mmap_page);
				ret = -EAGAIN;
				जाओ out;
			पूर्ण

			get_page(mmap_page);
			wc->w_pages[i] = mmap_page;
			wc->w_target_locked = true;
		पूर्ण अन्यथा अगर (index >= target_index && index <= end_index &&
			   wc->w_type == OCFS2_WRITE_सूचीECT) अणु
			/* Direct ग_लिखो has no mapping page. */
			wc->w_pages[i] = शून्य;
			जारी;
		पूर्ण अन्यथा अणु
			wc->w_pages[i] = find_or_create_page(mapping, index,
							     GFP_NOFS);
			अगर (!wc->w_pages[i]) अणु
				ret = -ENOMEM;
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण
		रुको_क्रम_stable_page(wc->w_pages[i]);

		अगर (index == target_index)
			wc->w_target_page = wc->w_pages[i];
	पूर्ण
out:
	अगर (ret)
		wc->w_target_locked = false;
	वापस ret;
पूर्ण

/*
 * Prepare a single cluster क्रम ग_लिखो one cluster पूर्णांकo the file.
 */
अटल पूर्णांक ocfs2_ग_लिखो_cluster(काष्ठा address_space *mapping,
			       u32 *phys, अचिन्हित पूर्णांक new,
			       अचिन्हित पूर्णांक clear_unwritten,
			       अचिन्हित पूर्णांक should_zero,
			       काष्ठा ocfs2_alloc_context *data_ac,
			       काष्ठा ocfs2_alloc_context *meta_ac,
			       काष्ठा ocfs2_ग_लिखो_ctxt *wc, u32 cpos,
			       loff_t user_pos, अचिन्हित user_len)
अणु
	पूर्णांक ret, i;
	u64 p_blkno;
	काष्ठा inode *inode = mapping->host;
	काष्ठा ocfs2_extent_tree et;
	पूर्णांक bpc = ocfs2_clusters_to_blocks(inode->i_sb, 1);

	अगर (new) अणु
		u32 पंचांगp_pos;

		/*
		 * This is safe to call with the page locks - it won't take
		 * any additional semaphores or cluster locks.
		 */
		पंचांगp_pos = cpos;
		ret = ocfs2_add_inode_data(OCFS2_SB(inode->i_sb), inode,
					   &पंचांगp_pos, 1, !clear_unwritten,
					   wc->w_di_bh, wc->w_handle,
					   data_ac, meta_ac, शून्य);
		/*
		 * This shouldn't happen because we must have alपढ़ोy
		 * calculated the correct meta data allocation required. The
		 * पूर्णांकernal tree allocation code should know how to increase
		 * transaction credits itself.
		 *
		 * If need be, we could handle -EAGAIN क्रम a
		 * RESTART_TRANS here.
		 */
		mlog_bug_on_msg(ret == -EAGAIN,
				"Inode %llu: EAGAIN return during allocation.\n",
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (clear_unwritten) अणु
		ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode),
					      wc->w_di_bh);
		ret = ocfs2_mark_extent_written(inode, &et,
						wc->w_handle, cpos, 1, *phys,
						meta_ac, &wc->w_dealloc);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * The only reason this should fail is due to an inability to
	 * find the extent added.
	 */
	ret = ocfs2_get_clusters(inode, cpos, phys, शून्य, शून्य);
	अगर (ret < 0) अणु
		mlog(ML_ERROR, "Get physical blkno failed for inode %llu, "
			    "at logical cluster %u",
			    (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno, cpos);
		जाओ out;
	पूर्ण

	BUG_ON(*phys == 0);

	p_blkno = ocfs2_clusters_to_blocks(inode->i_sb, *phys);
	अगर (!should_zero)
		p_blkno += (user_pos >> inode->i_sb->s_blocksize_bits) & (u64)(bpc - 1);

	क्रम(i = 0; i < wc->w_num_pages; i++) अणु
		पूर्णांक पंचांगpret;

		/* This is the direct io target page. */
		अगर (wc->w_pages[i] == शून्य) अणु
			p_blkno++;
			जारी;
		पूर्ण

		पंचांगpret = ocfs2_prepare_page_क्रम_ग_लिखो(inode, &p_blkno, wc,
						      wc->w_pages[i], cpos,
						      user_pos, user_len,
						      should_zero);
		अगर (पंचांगpret) अणु
			mlog_त्रुटि_सं(पंचांगpret);
			अगर (ret == 0)
				ret = पंचांगpret;
		पूर्ण
	पूर्ण

	/*
	 * We only have cleanup to करो in हाल of allocating ग_लिखो.
	 */
	अगर (ret && new)
		ocfs2_ग_लिखो_failure(inode, wc, user_pos, user_len);

out:

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_ग_लिखो_cluster_by_desc(काष्ठा address_space *mapping,
				       काष्ठा ocfs2_alloc_context *data_ac,
				       काष्ठा ocfs2_alloc_context *meta_ac,
				       काष्ठा ocfs2_ग_लिखो_ctxt *wc,
				       loff_t pos, अचिन्हित len)
अणु
	पूर्णांक ret, i;
	loff_t cluster_off;
	अचिन्हित पूर्णांक local_len = len;
	काष्ठा ocfs2_ग_लिखो_cluster_desc *desc;
	काष्ठा ocfs2_super *osb = OCFS2_SB(mapping->host->i_sb);

	क्रम (i = 0; i < wc->w_clen; i++) अणु
		desc = &wc->w_desc[i];

		/*
		 * We have to make sure that the total ग_लिखो passed in
		 * करोesn't extend past a single cluster.
		 */
		local_len = len;
		cluster_off = pos & (osb->s_clustersize - 1);
		अगर ((cluster_off + local_len) > osb->s_clustersize)
			local_len = osb->s_clustersize - cluster_off;

		ret = ocfs2_ग_लिखो_cluster(mapping, &desc->c_phys,
					  desc->c_new,
					  desc->c_clear_unwritten,
					  desc->c_needs_zero,
					  data_ac, meta_ac,
					  wc, desc->c_cpos, pos, local_len);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		len -= local_len;
		pos += local_len;
	पूर्ण

	ret = 0;
out:
	वापस ret;
पूर्ण

/*
 * ocfs2_ग_लिखो_end() wants to know which parts of the target page it
 * should complete the ग_लिखो on. It's easiest to compute them ahead of
 * समय when a more complete view of the ग_लिखो is available.
 */
अटल व्योम ocfs2_set_target_boundaries(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_ग_लिखो_ctxt *wc,
					loff_t pos, अचिन्हित len, पूर्णांक alloc)
अणु
	काष्ठा ocfs2_ग_लिखो_cluster_desc *desc;

	wc->w_target_from = pos & (PAGE_SIZE - 1);
	wc->w_target_to = wc->w_target_from + len;

	अगर (alloc == 0)
		वापस;

	/*
	 * Allocating ग_लिखो - we may have dअगरferent boundaries based
	 * on page size and cluster size.
	 *
	 * NOTE: We can no दीर्घer compute one value from the other as
	 * the actual ग_लिखो length and user provided length may be
	 * dअगरferent.
	 */

	अगर (wc->w_large_pages) अणु
		/*
		 * We only care about the 1st and last cluster within
		 * our range and whether they should be zero'd or not. Either
		 * value may be extended out to the start/end of a
		 * newly allocated cluster.
		 */
		desc = &wc->w_desc[0];
		अगर (desc->c_needs_zero)
			ocfs2_figure_cluster_boundaries(osb,
							desc->c_cpos,
							&wc->w_target_from,
							शून्य);

		desc = &wc->w_desc[wc->w_clen - 1];
		अगर (desc->c_needs_zero)
			ocfs2_figure_cluster_boundaries(osb,
							desc->c_cpos,
							शून्य,
							&wc->w_target_to);
	पूर्ण अन्यथा अणु
		wc->w_target_from = 0;
		wc->w_target_to = PAGE_SIZE;
	पूर्ण
पूर्ण

/*
 * Check अगर this extent is marked UNWRITTEN by direct io. If so, we need not to
 * करो the zero work. And should not to clear UNWRITTEN since it will be cleared
 * by the direct io procedure.
 * If this is a new extent that allocated by direct io, we should mark it in
 * the ip_unwritten_list.
 */
अटल पूर्णांक ocfs2_unwritten_check(काष्ठा inode *inode,
				 काष्ठा ocfs2_ग_लिखो_ctxt *wc,
				 काष्ठा ocfs2_ग_लिखो_cluster_desc *desc)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_unwritten_extent *ue = शून्य, *new = शून्य;
	पूर्णांक ret = 0;

	अगर (!desc->c_needs_zero)
		वापस 0;

retry:
	spin_lock(&oi->ip_lock);
	/* Needs not to zero no metter buffer or direct. The one who is zero
	 * the cluster is करोing zero. And he will clear unwritten after all
	 * cluster io finished. */
	list_क्रम_each_entry(ue, &oi->ip_unwritten_list, ue_ip_node) अणु
		अगर (desc->c_cpos == ue->ue_cpos) अणु
			BUG_ON(desc->c_new);
			desc->c_needs_zero = 0;
			desc->c_clear_unwritten = 0;
			जाओ unlock;
		पूर्ण
	पूर्ण

	अगर (wc->w_type != OCFS2_WRITE_सूचीECT)
		जाओ unlock;

	अगर (new == शून्य) अणु
		spin_unlock(&oi->ip_lock);
		new = kदो_स्मृति(माप(काष्ठा ocfs2_unwritten_extent),
			     GFP_NOFS);
		अगर (new == शून्य) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		जाओ retry;
	पूर्ण
	/* This direct ग_लिखो will करोing zero. */
	new->ue_cpos = desc->c_cpos;
	new->ue_phys = desc->c_phys;
	desc->c_clear_unwritten = 0;
	list_add_tail(&new->ue_ip_node, &oi->ip_unwritten_list);
	list_add_tail(&new->ue_node, &wc->w_unwritten_list);
	wc->w_unwritten_count++;
	new = शून्य;
unlock:
	spin_unlock(&oi->ip_lock);
out:
	kमुक्त(new);
	वापस ret;
पूर्ण

/*
 * Populate each single-cluster ग_लिखो descriptor in the ग_लिखो context
 * with inक्रमmation about the i/o to be करोne.
 *
 * Returns the number of clusters that will have to be allocated, as
 * well as a worst हाल estimate of the number of extent records that
 * would have to be created during a ग_लिखो to an unwritten region.
 */
अटल पूर्णांक ocfs2_populate_ग_लिखो_desc(काष्ठा inode *inode,
				     काष्ठा ocfs2_ग_लिखो_ctxt *wc,
				     अचिन्हित पूर्णांक *clusters_to_alloc,
				     अचिन्हित पूर्णांक *extents_to_split)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_ग_लिखो_cluster_desc *desc;
	अचिन्हित पूर्णांक num_clusters = 0;
	अचिन्हित पूर्णांक ext_flags = 0;
	u32 phys = 0;
	पूर्णांक i;

	*clusters_to_alloc = 0;
	*extents_to_split = 0;

	क्रम (i = 0; i < wc->w_clen; i++) अणु
		desc = &wc->w_desc[i];
		desc->c_cpos = wc->w_cpos + i;

		अगर (num_clusters == 0) अणु
			/*
			 * Need to look up the next extent record.
			 */
			ret = ocfs2_get_clusters(inode, desc->c_cpos, &phys,
						 &num_clusters, &ext_flags);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			/* We should alपढ़ोy CoW the refcountd extent. */
			BUG_ON(ext_flags & OCFS2_EXT_REFCOUNTED);

			/*
			 * Assume worst हाल - that we're writing in
			 * the middle of the extent.
			 *
			 * We can assume that the ग_लिखो proceeds from
			 * left to right, in which हाल the extent
			 * insert code is smart enough to coalesce the
			 * next splits पूर्णांकo the previous records created.
			 */
			अगर (ext_flags & OCFS2_EXT_UNWRITTEN)
				*extents_to_split = *extents_to_split + 2;
		पूर्ण अन्यथा अगर (phys) अणु
			/*
			 * Only increment phys अगर it करोesn't describe
			 * a hole.
			 */
			phys++;
		पूर्ण

		/*
		 * If w_first_new_cpos is < अच_पूर्णांक_उच्च, we have a non-sparse
		 * file that got extended.  w_first_new_cpos tells us
		 * where the newly allocated clusters are so we can
		 * zero them.
		 */
		अगर (desc->c_cpos >= wc->w_first_new_cpos) अणु
			BUG_ON(phys == 0);
			desc->c_needs_zero = 1;
		पूर्ण

		desc->c_phys = phys;
		अगर (phys == 0) अणु
			desc->c_new = 1;
			desc->c_needs_zero = 1;
			desc->c_clear_unwritten = 1;
			*clusters_to_alloc = *clusters_to_alloc + 1;
		पूर्ण

		अगर (ext_flags & OCFS2_EXT_UNWRITTEN) अणु
			desc->c_clear_unwritten = 1;
			desc->c_needs_zero = 1;
		पूर्ण

		ret = ocfs2_unwritten_check(inode, wc, desc);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		num_clusters--;
	पूर्ण

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_ग_लिखो_begin_अंतरभूत(काष्ठा address_space *mapping,
				    काष्ठा inode *inode,
				    काष्ठा ocfs2_ग_लिखो_ctxt *wc)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा page *page;
	handle_t *handle;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)wc->w_di_bh->b_data;

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	page = find_or_create_page(mapping, 0, GFP_NOFS);
	अगर (!page) अणु
		ocfs2_commit_trans(osb, handle);
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	/*
	 * If we करोn't set w_num_pages then this page won't get unlocked
	 * and मुक्तd on cleanup of the ग_लिखो context.
	 */
	wc->w_pages[0] = wc->w_target_page = page;
	wc->w_num_pages = 1;

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), wc->w_di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		ocfs2_commit_trans(osb, handle);

		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (!(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL))
		ocfs2_set_inode_data_अंतरभूत(inode, di);

	अगर (!PageUptodate(page)) अणु
		ret = ocfs2_पढ़ो_अंतरभूत_data(inode, page, wc->w_di_bh);
		अगर (ret) अणु
			ocfs2_commit_trans(osb, handle);

			जाओ out;
		पूर्ण
	पूर्ण

	wc->w_handle = handle;
out:
	वापस ret;
पूर्ण

पूर्णांक ocfs2_size_fits_अंतरभूत_data(काष्ठा buffer_head *di_bh, u64 new_size)
अणु
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	अगर (new_size <= le16_to_cpu(di->id2.i_data.id_count))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_try_to_ग_लिखो_अंतरभूत_data(काष्ठा address_space *mapping,
					  काष्ठा inode *inode, loff_t pos,
					  अचिन्हित len, काष्ठा page *mmap_page,
					  काष्ठा ocfs2_ग_लिखो_ctxt *wc)
अणु
	पूर्णांक ret, written = 0;
	loff_t end = pos + len;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_dinode *di = शून्य;

	trace_ocfs2_try_to_ग_लिखो_अंतरभूत_data((अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
					     len, (अचिन्हित दीर्घ दीर्घ)pos,
					     oi->ip_dyn_features);

	/*
	 * Handle inodes which alपढ़ोy have अंतरभूत data 1st.
	 */
	अगर (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		अगर (mmap_page == शून्य &&
		    ocfs2_size_fits_अंतरभूत_data(wc->w_di_bh, end))
			जाओ करो_अंतरभूत_ग_लिखो;

		/*
		 * The ग_लिखो won't fit - we have to give this inode an
		 * अंतरभूत extent list now.
		 */
		ret = ocfs2_convert_अंतरभूत_data_to_extents(inode, wc->w_di_bh);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Check whether the inode can accept अंतरभूत data.
	 */
	अगर (oi->ip_clusters != 0 || i_size_पढ़ो(inode) != 0)
		वापस 0;

	/*
	 * Check whether the ग_लिखो can fit.
	 */
	di = (काष्ठा ocfs2_dinode *)wc->w_di_bh->b_data;
	अगर (mmap_page ||
	    end > ocfs2_max_अंतरभूत_data_with_xattr(inode->i_sb, di))
		वापस 0;

करो_अंतरभूत_ग_लिखो:
	ret = ocfs2_ग_लिखो_begin_अंतरभूत(mapping, inode, wc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * This संकेतs to the caller that the data can be written
	 * अंतरभूत.
	 */
	written = 1;
out:
	वापस written ? written : ret;
पूर्ण

/*
 * This function only करोes anything क्रम file प्रणालीs which can't
 * handle sparse files.
 *
 * What we want to करो here is fill in any hole between the current end
 * of allocation and the end of our ग_लिखो. That way the rest of the
 * ग_लिखो path can treat it as an non-allocating ग_लिखो, which has no
 * special हाल code क्रम sparse/nonsparse files.
 */
अटल पूर्णांक ocfs2_expand_nonsparse_inode(काष्ठा inode *inode,
					काष्ठा buffer_head *di_bh,
					loff_t pos, अचिन्हित len,
					काष्ठा ocfs2_ग_लिखो_ctxt *wc)
अणु
	पूर्णांक ret;
	loff_t newsize = pos + len;

	BUG_ON(ocfs2_sparse_alloc(OCFS2_SB(inode->i_sb)));

	अगर (newsize <= i_size_पढ़ो(inode))
		वापस 0;

	ret = ocfs2_extend_no_holes(inode, di_bh, newsize, pos);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	/* There is no wc अगर this is call from direct. */
	अगर (wc)
		wc->w_first_new_cpos =
			ocfs2_clusters_क्रम_bytes(inode->i_sb, i_size_पढ़ो(inode));

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_zero_tail(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
			   loff_t pos)
अणु
	पूर्णांक ret = 0;

	BUG_ON(!ocfs2_sparse_alloc(OCFS2_SB(inode->i_sb)));
	अगर (pos > i_size_पढ़ो(inode))
		ret = ocfs2_zero_extend(inode, di_bh, pos);

	वापस ret;
पूर्ण

पूर्णांक ocfs2_ग_लिखो_begin_nolock(काष्ठा address_space *mapping,
			     loff_t pos, अचिन्हित len, ocfs2_ग_लिखो_type_t type,
			     काष्ठा page **pagep, व्योम **fsdata,
			     काष्ठा buffer_head *di_bh, काष्ठा page *mmap_page)
अणु
	पूर्णांक ret, cluster_of_pages, credits = OCFS2_INODE_UPDATE_CREDITS;
	अचिन्हित पूर्णांक clusters_to_alloc, extents_to_split, clusters_need = 0;
	काष्ठा ocfs2_ग_लिखो_ctxt *wc;
	काष्ठा inode *inode = mapping->host;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	handle_t *handle;
	काष्ठा ocfs2_extent_tree et;
	पूर्णांक try_मुक्त = 1, ret1;

try_again:
	ret = ocfs2_alloc_ग_लिखो_ctxt(&wc, osb, pos, len, type, di_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	अगर (ocfs2_supports_अंतरभूत_data(osb)) अणु
		ret = ocfs2_try_to_ग_लिखो_अंतरभूत_data(mapping, inode, pos, len,
						     mmap_page, wc);
		अगर (ret == 1) अणु
			ret = 0;
			जाओ success;
		पूर्ण
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Direct io change i_size late, should not zero tail here. */
	अगर (type != OCFS2_WRITE_सूचीECT) अणु
		अगर (ocfs2_sparse_alloc(osb))
			ret = ocfs2_zero_tail(inode, di_bh, pos);
		अन्यथा
			ret = ocfs2_expand_nonsparse_inode(inode, di_bh, pos,
							   len, wc);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ocfs2_check_range_क्रम_refcount(inode, pos, len);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण अन्यथा अगर (ret == 1) अणु
		clusters_need = wc->w_clen;
		ret = ocfs2_refcount_cow(inode, di_bh,
					 wc->w_cpos, wc->w_clen, अच_पूर्णांक_उच्च);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ocfs2_populate_ग_लिखो_desc(inode, wc, &clusters_to_alloc,
					&extents_to_split);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	clusters_need += clusters_to_alloc;

	di = (काष्ठा ocfs2_dinode *)wc->w_di_bh->b_data;

	trace_ocfs2_ग_लिखो_begin_nolock(
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			(दीर्घ दीर्घ)i_size_पढ़ो(inode),
			le32_to_cpu(di->i_clusters),
			pos, len, type, mmap_page,
			clusters_to_alloc, extents_to_split);

	/*
	 * We set w_target_from, w_target_to here so that
	 * ocfs2_ग_लिखो_end() knows which range in the target page to
	 * ग_लिखो out. An allocation requires that we ग_लिखो the entire
	 * cluster range.
	 */
	अगर (clusters_to_alloc || extents_to_split) अणु
		/*
		 * XXX: We are stretching the limits of
		 * ocfs2_lock_allocators(). It greatly over-estimates
		 * the work to be करोne.
		 */
		ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode),
					      wc->w_di_bh);
		ret = ocfs2_lock_allocators(inode, &et,
					    clusters_to_alloc, extents_to_split,
					    &data_ac, &meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (data_ac)
			data_ac->ac_resv = &OCFS2_I(inode)->ip_la_data_resv;

		credits = ocfs2_calc_extend_credits(inode->i_sb,
						    &di->id2.i_list);
	पूर्ण अन्यथा अगर (type == OCFS2_WRITE_सूचीECT)
		/* direct ग_लिखो needs not to start trans अगर no extents alloc. */
		जाओ success;

	/*
	 * We have to zero sparse allocated clusters, unwritten extent clusters,
	 * and non-sparse clusters we just extended.  For non-sparse ग_लिखोs,
	 * we know zeros will only be needed in the first and/or last cluster.
	 */
	अगर (wc->w_clen && (wc->w_desc[0].c_needs_zero ||
			   wc->w_desc[wc->w_clen - 1].c_needs_zero))
		cluster_of_pages = 1;
	अन्यथा
		cluster_of_pages = 0;

	ocfs2_set_target_boundaries(osb, wc, pos, len, cluster_of_pages);

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	wc->w_handle = handle;

	अगर (clusters_to_alloc) अणु
		ret = dquot_alloc_space_nodirty(inode,
			ocfs2_clusters_to_bytes(osb->sb, clusters_to_alloc));
		अगर (ret)
			जाओ out_commit;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), wc->w_di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_quota;
	पूर्ण

	/*
	 * Fill our page array first. That way we've grabbed enough so
	 * that we can zero and flush अगर we error after adding the
	 * extent.
	 */
	ret = ocfs2_grab_pages_क्रम_ग_लिखो(mapping, wc, wc->w_cpos, pos, len,
					 cluster_of_pages, mmap_page);
	अगर (ret && ret != -EAGAIN) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_quota;
	पूर्ण

	/*
	 * ocfs2_grab_pages_क्रम_ग_लिखो() वापसs -EAGAIN अगर it could not lock
	 * the target page. In this हाल, we निकास with no error and no target
	 * page. This will trigger the caller, page_mkग_लिखो(), to re-try
	 * the operation.
	 */
	अगर (ret == -EAGAIN) अणु
		BUG_ON(wc->w_target_page);
		ret = 0;
		जाओ out_quota;
	पूर्ण

	ret = ocfs2_ग_लिखो_cluster_by_desc(mapping, data_ac, meta_ac, wc, pos,
					  len);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_quota;
	पूर्ण

	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);

success:
	अगर (pagep)
		*pagep = wc->w_target_page;
	*fsdata = wc;
	वापस 0;
out_quota:
	अगर (clusters_to_alloc)
		dquot_मुक्त_space(inode,
			  ocfs2_clusters_to_bytes(osb->sb, clusters_to_alloc));
out_commit:
	ocfs2_commit_trans(osb, handle);

out:
	/*
	 * The mmapped page won't be unlocked in ocfs2_मुक्त_ग_लिखो_ctxt(),
	 * even in हाल of error here like ENOSPC and ENOMEM. So, we need
	 * to unlock the target page manually to prevent deadlocks when
	 * retrying again on ENOSPC, or when वापसing non-VM_FAULT_LOCKED
	 * to VM code.
	 */
	अगर (wc->w_target_locked)
		unlock_page(mmap_page);

	ocfs2_मुक्त_ग_लिखो_ctxt(inode, wc);

	अगर (data_ac) अणु
		ocfs2_मुक्त_alloc_context(data_ac);
		data_ac = शून्य;
	पूर्ण
	अगर (meta_ac) अणु
		ocfs2_मुक्त_alloc_context(meta_ac);
		meta_ac = शून्य;
	पूर्ण

	अगर (ret == -ENOSPC && try_मुक्त) अणु
		/*
		 * Try to मुक्त some truncate log so that we can have enough
		 * clusters to allocate.
		 */
		try_मुक्त = 0;

		ret1 = ocfs2_try_to_मुक्त_truncate_log(osb, clusters_need);
		अगर (ret1 == 1)
			जाओ try_again;

		अगर (ret1 < 0)
			mlog_त्रुटि_सं(ret1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			     loff_t pos, अचिन्हित len, अचिन्हित flags,
			     काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा inode *inode = mapping->host;

	ret = ocfs2_inode_lock(inode, &di_bh, 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	/*
	 * Take alloc sem here to prevent concurrent lookups. That way
	 * the mapping, zeroing and tree manipulation within
	 * ocfs2_ग_लिखो() will be safe against ->पढ़ोpage(). This
	 * should also serve to lock out allocation from a shared
	 * ग_लिखोable region.
	 */
	करोwn_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);

	ret = ocfs2_ग_लिखो_begin_nolock(mapping, pos, len, OCFS2_WRITE_BUFFER,
				       pagep, fsdata, di_bh, शून्य);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_fail;
	पूर्ण

	brअन्यथा(di_bh);

	वापस 0;

out_fail:
	up_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);

	brअन्यथा(di_bh);
	ocfs2_inode_unlock(inode, 1);

	वापस ret;
पूर्ण

अटल व्योम ocfs2_ग_लिखो_end_अंतरभूत(काष्ठा inode *inode, loff_t pos,
				   अचिन्हित len, अचिन्हित *copied,
				   काष्ठा ocfs2_dinode *di,
				   काष्ठा ocfs2_ग_लिखो_ctxt *wc)
अणु
	व्योम *kaddr;

	अगर (unlikely(*copied < len)) अणु
		अगर (!PageUptodate(wc->w_target_page)) अणु
			*copied = 0;
			वापस;
		पूर्ण
	पूर्ण

	kaddr = kmap_atomic(wc->w_target_page);
	स_नकल(di->id2.i_data.id_data + pos, kaddr + pos, *copied);
	kunmap_atomic(kaddr);

	trace_ocfs2_ग_लिखो_end_अंतरभूत(
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
	     (अचिन्हित दीर्घ दीर्घ)pos, *copied,
	     le16_to_cpu(di->id2.i_data.id_count),
	     le16_to_cpu(di->i_dyn_features));
पूर्ण

पूर्णांक ocfs2_ग_लिखो_end_nolock(काष्ठा address_space *mapping,
			   loff_t pos, अचिन्हित len, अचिन्हित copied, व्योम *fsdata)
अणु
	पूर्णांक i, ret;
	अचिन्हित from, to, start = pos & (PAGE_SIZE - 1);
	काष्ठा inode *inode = mapping->host;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_ग_लिखो_ctxt *wc = fsdata;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)wc->w_di_bh->b_data;
	handle_t *handle = wc->w_handle;
	काष्ठा page *पंचांगppage;

	BUG_ON(!list_empty(&wc->w_unwritten_list));

	अगर (handle) अणु
		ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode),
				wc->w_di_bh, OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (ret) अणु
			copied = ret;
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		ocfs2_ग_लिखो_end_अंतरभूत(inode, pos, len, &copied, di, wc);
		जाओ out_ग_लिखो_size;
	पूर्ण

	अगर (unlikely(copied < len) && wc->w_target_page) अणु
		अगर (!PageUptodate(wc->w_target_page))
			copied = 0;

		ocfs2_zero_new_buffers(wc->w_target_page, start+copied,
				       start+len);
	पूर्ण
	अगर (wc->w_target_page)
		flush_dcache_page(wc->w_target_page);

	क्रम(i = 0; i < wc->w_num_pages; i++) अणु
		पंचांगppage = wc->w_pages[i];

		/* This is the direct io target page. */
		अगर (पंचांगppage == शून्य)
			जारी;

		अगर (पंचांगppage == wc->w_target_page) अणु
			from = wc->w_target_from;
			to = wc->w_target_to;

			BUG_ON(from > PAGE_SIZE ||
			       to > PAGE_SIZE ||
			       to < from);
		पूर्ण अन्यथा अणु
			/*
			 * Pages adjacent to the target (अगर any) imply
			 * a hole-filling ग_लिखो in which हाल we want
			 * to flush their entire range.
			 */
			from = 0;
			to = PAGE_SIZE;
		पूर्ण

		अगर (page_has_buffers(पंचांगppage)) अणु
			अगर (handle && ocfs2_should_order_data(inode)) अणु
				loff_t start_byte =
					((loff_t)पंचांगppage->index << PAGE_SHIFT) +
					from;
				loff_t length = to - from;
				ocfs2_jbd2_inode_add_ग_लिखो(handle, inode,
							   start_byte, length);
			पूर्ण
			block_commit_ग_लिखो(पंचांगppage, from, to);
		पूर्ण
	पूर्ण

out_ग_लिखो_size:
	/* Direct io करो not update i_size here. */
	अगर (wc->w_type != OCFS2_WRITE_सूचीECT) अणु
		pos += copied;
		अगर (pos > i_size_पढ़ो(inode)) अणु
			i_size_ग_लिखो(inode, pos);
			mark_inode_dirty(inode);
		पूर्ण
		inode->i_blocks = ocfs2_inode_sector_count(inode);
		di->i_size = cpu_to_le64((u64)i_size_पढ़ो(inode));
		inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		di->i_mसमय = di->i_स_समय = cpu_to_le64(inode->i_mसमय.tv_sec);
		di->i_mसमय_nsec = di->i_स_समय_nsec = cpu_to_le32(inode->i_mसमय.tv_nsec);
		अगर (handle)
			ocfs2_update_inode_fsync_trans(handle, inode, 1);
	पूर्ण
	अगर (handle)
		ocfs2_journal_dirty(handle, wc->w_di_bh);

out:
	/* unlock pages beक्रमe dealloc since it needs acquiring j_trans_barrier
	 * lock, or it will cause a deadlock since journal commit thपढ़ोs holds
	 * this lock and will ask क्रम the page lock when flushing the data.
	 * put it here to preserve the unlock order.
	 */
	ocfs2_unlock_pages(wc);

	अगर (handle)
		ocfs2_commit_trans(osb, handle);

	ocfs2_run_deallocs(osb, &wc->w_dealloc);

	brअन्यथा(wc->w_di_bh);
	kमुक्त(wc);

	वापस copied;
पूर्ण

अटल पूर्णांक ocfs2_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			   loff_t pos, अचिन्हित len, अचिन्हित copied,
			   काष्ठा page *page, व्योम *fsdata)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode = mapping->host;

	ret = ocfs2_ग_लिखो_end_nolock(mapping, pos, len, copied, fsdata);

	up_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
	ocfs2_inode_unlock(inode, 1);

	वापस ret;
पूर्ण

काष्ठा ocfs2_dio_ग_लिखो_ctxt अणु
	काष्ठा list_head	dw_zero_list;
	अचिन्हित		dw_zero_count;
	पूर्णांक			dw_orphaned;
	pid_t			dw_ग_लिखोr_pid;
पूर्ण;

अटल काष्ठा ocfs2_dio_ग_लिखो_ctxt *
ocfs2_dio_alloc_ग_लिखो_ctx(काष्ठा buffer_head *bh, पूर्णांक *alloc)
अणु
	काष्ठा ocfs2_dio_ग_लिखो_ctxt *dwc = शून्य;

	अगर (bh->b_निजी)
		वापस bh->b_निजी;

	dwc = kदो_स्मृति(माप(काष्ठा ocfs2_dio_ग_लिखो_ctxt), GFP_NOFS);
	अगर (dwc == शून्य)
		वापस शून्य;
	INIT_LIST_HEAD(&dwc->dw_zero_list);
	dwc->dw_zero_count = 0;
	dwc->dw_orphaned = 0;
	dwc->dw_ग_लिखोr_pid = task_pid_nr(current);
	bh->b_निजी = dwc;
	*alloc = 1;

	वापस dwc;
पूर्ण

अटल व्योम ocfs2_dio_मुक्त_ग_लिखो_ctx(काष्ठा inode *inode,
				     काष्ठा ocfs2_dio_ग_लिखो_ctxt *dwc)
अणु
	ocfs2_मुक्त_unwritten_list(inode, &dwc->dw_zero_list);
	kमुक्त(dwc);
पूर्ण

/*
 * TODO: Make this पूर्णांकo a generic get_blocks function.
 *
 * From करो_direct_io in direct-io.c:
 *  "So what we करो is to permit the ->get_blocks function to populate
 *   bh.b_size with the size of IO which is permitted at this offset and
 *   this i_blkbits."
 *
 * This function is called directly from get_more_blocks in direct-io.c.
 *
 * called like this: dio->get_blocks(dio->inode, fs_startblk,
 * 					fs_count, map_bh, dio->rw == WRITE);
 */
अटल पूर्णांक ocfs2_dio_wr_get_block(काष्ठा inode *inode, sector_t iblock,
			       काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_ग_लिखो_ctxt *wc;
	काष्ठा ocfs2_ग_लिखो_cluster_desc *desc = शून्य;
	काष्ठा ocfs2_dio_ग_लिखो_ctxt *dwc = शून्य;
	काष्ठा buffer_head *di_bh = शून्य;
	u64 p_blkno;
	अचिन्हित पूर्णांक i_blkbits = inode->i_sb->s_blocksize_bits;
	loff_t pos = iblock << i_blkbits;
	sector_t endblk = (i_size_पढ़ो(inode) - 1) >> i_blkbits;
	अचिन्हित len, total_len = bh_result->b_size;
	पूर्णांक ret = 0, first_get_block = 0;

	len = osb->s_clustersize - (pos & (osb->s_clustersize - 1));
	len = min(total_len, len);

	/*
	 * bh_result->b_size is count in get_more_blocks according to ग_लिखो
	 * "pos" and "end", we need map twice to वापस dअगरferent buffer state:
	 * 1. area in file size, not set NEW;
	 * 2. area out file size, set  NEW.
	 *
	 *		   iblock    endblk
	 * |--------|---------|---------|---------
	 * |<-------area in file------->|
	 */

	अगर ((iblock <= endblk) &&
	    ((iblock + ((len - 1) >> i_blkbits)) > endblk))
		len = (endblk - iblock + 1) << i_blkbits;

	mlog(0, "get block of %lu at %llu:%u req %u\n",
			inode->i_ino, pos, len, total_len);

	/*
	 * Because we need to change file size in ocfs2_dio_end_io_ग_लिखो(), or
	 * we may need to add it to orphan dir. So can not fall to fast path
	 * जबतक file size will be changed.
	 */
	अगर (pos + total_len <= i_size_पढ़ो(inode)) अणु

		/* This is the fast path क्रम re-ग_लिखो. */
		ret = ocfs2_lock_get_block(inode, iblock, bh_result, create);
		अगर (buffer_mapped(bh_result) &&
		    !buffer_new(bh_result) &&
		    ret == 0)
			जाओ out;

		/* Clear state set by ocfs2_get_block. */
		bh_result->b_state = 0;
	पूर्ण

	dwc = ocfs2_dio_alloc_ग_लिखो_ctx(bh_result, &first_get_block);
	अगर (unlikely(dwc == शून्य)) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (ocfs2_clusters_क्रम_bytes(inode->i_sb, pos + total_len) >
	    ocfs2_clusters_क्रम_bytes(inode->i_sb, i_size_पढ़ो(inode)) &&
	    !dwc->dw_orphaned) अणु
		/*
		 * when we are going to alloc extents beyond file size, add the
		 * inode to orphan dir, so we can recall those spaces when
		 * प्रणाली crashed during ग_लिखो.
		 */
		ret = ocfs2_add_inode_to_orphan(osb, inode);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		dwc->dw_orphaned = 1;
	पूर्ण

	ret = ocfs2_inode_lock(inode, &di_bh, 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	करोwn_ग_लिखो(&oi->ip_alloc_sem);

	अगर (first_get_block) अणु
		अगर (ocfs2_sparse_alloc(osb))
			ret = ocfs2_zero_tail(inode, di_bh, pos);
		अन्यथा
			ret = ocfs2_expand_nonsparse_inode(inode, di_bh, pos,
							   total_len, शून्य);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ unlock;
		पूर्ण
	पूर्ण

	ret = ocfs2_ग_लिखो_begin_nolock(inode->i_mapping, pos, len,
				       OCFS2_WRITE_सूचीECT, शून्य,
				       (व्योम **)&wc, di_bh, शून्य);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ unlock;
	पूर्ण

	desc = &wc->w_desc[0];

	p_blkno = ocfs2_clusters_to_blocks(inode->i_sb, desc->c_phys);
	BUG_ON(p_blkno == 0);
	p_blkno += iblock & (u64)(ocfs2_clusters_to_blocks(inode->i_sb, 1) - 1);

	map_bh(bh_result, inode->i_sb, p_blkno);
	bh_result->b_size = len;
	अगर (desc->c_needs_zero)
		set_buffer_new(bh_result);

	अगर (iblock > endblk)
		set_buffer_new(bh_result);

	/* May sleep in end_io. It should not happen in a irq context. So defer
	 * it to dio work queue. */
	set_buffer_defer_completion(bh_result);

	अगर (!list_empty(&wc->w_unwritten_list)) अणु
		काष्ठा ocfs2_unwritten_extent *ue = शून्य;

		ue = list_first_entry(&wc->w_unwritten_list,
				      काष्ठा ocfs2_unwritten_extent,
				      ue_node);
		BUG_ON(ue->ue_cpos != desc->c_cpos);
		/* The physical address may be 0, fill it. */
		ue->ue_phys = desc->c_phys;

		list_splice_tail_init(&wc->w_unwritten_list, &dwc->dw_zero_list);
		dwc->dw_zero_count += wc->w_unwritten_count;
	पूर्ण

	ret = ocfs2_ग_लिखो_end_nolock(inode->i_mapping, pos, len, len, wc);
	BUG_ON(ret != len);
	ret = 0;
unlock:
	up_ग_लिखो(&oi->ip_alloc_sem);
	ocfs2_inode_unlock(inode, 1);
	brअन्यथा(di_bh);
out:
	अगर (ret < 0)
		ret = -EIO;
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_dio_end_io_ग_लिखो(काष्ठा inode *inode,
				  काष्ठा ocfs2_dio_ग_लिखो_ctxt *dwc,
				  loff_t offset,
				  sमाप_प्रकार bytes)
अणु
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	काष्ठा ocfs2_extent_tree et;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_unwritten_extent *ue = शून्य;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	handle_t *handle = शून्य;
	loff_t end = offset + bytes;
	पूर्णांक ret = 0, credits = 0;

	ocfs2_init_dealloc_ctxt(&dealloc);

	/* We करो clear unwritten, delete orphan, change i_size here. If neither
	 * of these happen, we can skip all this. */
	अगर (list_empty(&dwc->dw_zero_list) &&
	    end <= i_size_पढ़ो(inode) &&
	    !dwc->dw_orphaned)
		जाओ out;

	ret = ocfs2_inode_lock(inode, &di_bh, 1);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	करोwn_ग_लिखो(&oi->ip_alloc_sem);

	/* Delete orphan beक्रमe acquire i_mutex. */
	अगर (dwc->dw_orphaned) अणु
		BUG_ON(dwc->dw_ग_लिखोr_pid != task_pid_nr(current));

		end = end > i_size_पढ़ो(inode) ? end : 0;

		ret = ocfs2_del_inode_from_orphan(osb, inode, di_bh,
				!!end, end);
		अगर (ret < 0)
			mlog_त्रुटि_सं(ret);
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), di_bh);

	/* Attach dealloc with extent tree in हाल that we may reuse extents
	 * which are alपढ़ोy unlinked from current extent tree due to extent
	 * rotation and merging.
	 */
	et.et_dealloc = &dealloc;

	ret = ocfs2_lock_allocators(inode, &et, 0, dwc->dw_zero_count*2,
				    &data_ac, &meta_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ unlock;
	पूर्ण

	credits = ocfs2_calc_extend_credits(inode->i_sb, &di->id2.i_list);

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ unlock;
	पूर्ण
	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ commit;
	पूर्ण

	list_क्रम_each_entry(ue, &dwc->dw_zero_list, ue_node) अणु
		ret = ocfs2_mark_extent_written(inode, &et, handle,
						ue->ue_cpos, 1,
						ue->ue_phys,
						meta_ac, &dealloc);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (end > i_size_पढ़ो(inode)) अणु
		ret = ocfs2_set_inode_size(handle, inode, di_bh, end);
		अगर (ret < 0)
			mlog_त्रुटि_सं(ret);
	पूर्ण
commit:
	ocfs2_commit_trans(osb, handle);
unlock:
	up_ग_लिखो(&oi->ip_alloc_sem);
	ocfs2_inode_unlock(inode, 1);
	brअन्यथा(di_bh);
out:
	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);
	ocfs2_run_deallocs(osb, &dealloc);
	ocfs2_dio_मुक्त_ग_लिखो_ctx(inode, dwc);

	वापस ret;
पूर्ण

/*
 * ocfs2_dio_end_io is called by the dio core when a dio is finished.  We're
 * particularly पूर्णांकerested in the aio/dio हाल.  We use the rw_lock DLM lock
 * to protect io on one node from truncation on another.
 */
अटल पूर्णांक ocfs2_dio_end_io(काष्ठा kiocb *iocb,
			    loff_t offset,
			    sमाप_प्रकार bytes,
			    व्योम *निजी)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	पूर्णांक level;
	पूर्णांक ret = 0;

	/* this io's submitter should not have unlocked this beक्रमe we could */
	BUG_ON(!ocfs2_iocb_is_rw_locked(iocb));

	अगर (bytes <= 0)
		mlog_ratelimited(ML_ERROR, "Direct IO failed, bytes = %lld",
				 (दीर्घ दीर्घ)bytes);
	अगर (निजी) अणु
		अगर (bytes > 0)
			ret = ocfs2_dio_end_io_ग_लिखो(inode, निजी, offset,
						     bytes);
		अन्यथा
			ocfs2_dio_मुक्त_ग_लिखो_ctx(inode, निजी);
	पूर्ण

	ocfs2_iocb_clear_rw_locked(iocb);

	level = ocfs2_iocb_rw_locked_level(iocb);
	ocfs2_rw_unlock(inode, level);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ocfs2_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	get_block_t *get_block;

	/*
	 * Fallback to buffered I/O अगर we see an inode without
	 * extents.
	 */
	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		वापस 0;

	/* Fallback to buffered I/O अगर we करो not support append dio. */
	अगर (iocb->ki_pos + iter->count > i_size_पढ़ो(inode) &&
	    !ocfs2_supports_append_dio(osb))
		वापस 0;

	अगर (iov_iter_rw(iter) == READ)
		get_block = ocfs2_lock_get_block;
	अन्यथा
		get_block = ocfs2_dio_wr_get_block;

	वापस __blockdev_direct_IO(iocb, inode, inode->i_sb->s_bdev,
				    iter, get_block,
				    ocfs2_dio_end_io, शून्य, 0);
पूर्ण

स्थिर काष्ठा address_space_operations ocfs2_aops = अणु
	.पढ़ोpage		= ocfs2_पढ़ोpage,
	.पढ़ोahead		= ocfs2_पढ़ोahead,
	.ग_लिखोpage		= ocfs2_ग_लिखोpage,
	.ग_लिखो_begin		= ocfs2_ग_लिखो_begin,
	.ग_लिखो_end		= ocfs2_ग_लिखो_end,
	.bmap			= ocfs2_bmap,
	.direct_IO		= ocfs2_direct_IO,
	.invalidatepage		= block_invalidatepage,
	.releasepage		= ocfs2_releasepage,
	.migratepage		= buffer_migrate_page,
	.is_partially_uptodate	= block_is_partially_uptodate,
	.error_हटाओ_page	= generic_error_हटाओ_page,
पूर्ण;
