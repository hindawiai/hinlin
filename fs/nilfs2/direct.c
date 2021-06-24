<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * direct.c - NILFS direct block poपूर्णांकer.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश "nilfs.h"
#समावेश "page.h"
#समावेश "direct.h"
#समावेश "alloc.h"
#समावेश "dat.h"

अटल अंतरभूत __le64 *nilfs_direct_dptrs(स्थिर काष्ठा nilfs_bmap *direct)
अणु
	वापस (__le64 *)
		((काष्ठा nilfs_direct_node *)direct->b_u.u_data + 1);
पूर्ण

अटल अंतरभूत __u64
nilfs_direct_get_ptr(स्थिर काष्ठा nilfs_bmap *direct, __u64 key)
अणु
	वापस le64_to_cpu(*(nilfs_direct_dptrs(direct) + key));
पूर्ण

अटल अंतरभूत व्योम nilfs_direct_set_ptr(काष्ठा nilfs_bmap *direct,
					__u64 key, __u64 ptr)
अणु
	*(nilfs_direct_dptrs(direct) + key) = cpu_to_le64(ptr);
पूर्ण

अटल पूर्णांक nilfs_direct_lookup(स्थिर काष्ठा nilfs_bmap *direct,
			       __u64 key, पूर्णांक level, __u64 *ptrp)
अणु
	__u64 ptr;

	अगर (key > NILFS_सूचीECT_KEY_MAX || level != 1)
		वापस -ENOENT;
	ptr = nilfs_direct_get_ptr(direct, key);
	अगर (ptr == NILFS_BMAP_INVALID_PTR)
		वापस -ENOENT;

	*ptrp = ptr;
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_direct_lookup_contig(स्थिर काष्ठा nilfs_bmap *direct,
				      __u64 key, __u64 *ptrp,
				      अचिन्हित पूर्णांक maxblocks)
अणु
	काष्ठा inode *dat = शून्य;
	__u64 ptr, ptr2;
	sector_t blocknr;
	पूर्णांक ret, cnt;

	अगर (key > NILFS_सूचीECT_KEY_MAX)
		वापस -ENOENT;
	ptr = nilfs_direct_get_ptr(direct, key);
	अगर (ptr == NILFS_BMAP_INVALID_PTR)
		वापस -ENOENT;

	अगर (NILFS_BMAP_USE_VBN(direct)) अणु
		dat = nilfs_bmap_get_dat(direct);
		ret = nilfs_dat_translate(dat, ptr, &blocknr);
		अगर (ret < 0)
			वापस ret;
		ptr = blocknr;
	पूर्ण

	maxblocks = min_t(अचिन्हित पूर्णांक, maxblocks,
			  NILFS_सूचीECT_KEY_MAX - key + 1);
	क्रम (cnt = 1; cnt < maxblocks &&
		     (ptr2 = nilfs_direct_get_ptr(direct, key + cnt)) !=
		     NILFS_BMAP_INVALID_PTR;
	     cnt++) अणु
		अगर (dat) अणु
			ret = nilfs_dat_translate(dat, ptr2, &blocknr);
			अगर (ret < 0)
				वापस ret;
			ptr2 = blocknr;
		पूर्ण
		अगर (ptr2 != ptr + cnt)
			अवरोध;
	पूर्ण
	*ptrp = ptr;
	वापस cnt;
पूर्ण

अटल __u64
nilfs_direct_find_target_v(स्थिर काष्ठा nilfs_bmap *direct, __u64 key)
अणु
	__u64 ptr;

	ptr = nilfs_bmap_find_target_seq(direct, key);
	अगर (ptr != NILFS_BMAP_INVALID_PTR)
		/* sequential access */
		वापस ptr;

	/* block group */
	वापस nilfs_bmap_find_target_in_group(direct);
पूर्ण

अटल पूर्णांक nilfs_direct_insert(काष्ठा nilfs_bmap *bmap, __u64 key, __u64 ptr)
अणु
	जोड़ nilfs_bmap_ptr_req req;
	काष्ठा inode *dat = शून्य;
	काष्ठा buffer_head *bh;
	पूर्णांक ret;

	अगर (key > NILFS_सूचीECT_KEY_MAX)
		वापस -ENOENT;
	अगर (nilfs_direct_get_ptr(bmap, key) != NILFS_BMAP_INVALID_PTR)
		वापस -EEXIST;

	अगर (NILFS_BMAP_USE_VBN(bmap)) अणु
		req.bpr_ptr = nilfs_direct_find_target_v(bmap, key);
		dat = nilfs_bmap_get_dat(bmap);
	पूर्ण
	ret = nilfs_bmap_prepare_alloc_ptr(bmap, &req, dat);
	अगर (!ret) अणु
		/* ptr must be a poपूर्णांकer to a buffer head. */
		bh = (काष्ठा buffer_head *)((अचिन्हित दीर्घ)ptr);
		set_buffer_nilfs_अस्थिर(bh);

		nilfs_bmap_commit_alloc_ptr(bmap, &req, dat);
		nilfs_direct_set_ptr(bmap, key, req.bpr_ptr);

		अगर (!nilfs_bmap_dirty(bmap))
			nilfs_bmap_set_dirty(bmap);

		अगर (NILFS_BMAP_USE_VBN(bmap))
			nilfs_bmap_set_target_v(bmap, key, req.bpr_ptr);

		nilfs_inode_add_blocks(bmap->b_inode, 1);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_direct_delete(काष्ठा nilfs_bmap *bmap, __u64 key)
अणु
	जोड़ nilfs_bmap_ptr_req req;
	काष्ठा inode *dat;
	पूर्णांक ret;

	अगर (key > NILFS_सूचीECT_KEY_MAX ||
	    nilfs_direct_get_ptr(bmap, key) == NILFS_BMAP_INVALID_PTR)
		वापस -ENOENT;

	dat = NILFS_BMAP_USE_VBN(bmap) ? nilfs_bmap_get_dat(bmap) : शून्य;
	req.bpr_ptr = nilfs_direct_get_ptr(bmap, key);

	ret = nilfs_bmap_prepare_end_ptr(bmap, &req, dat);
	अगर (!ret) अणु
		nilfs_bmap_commit_end_ptr(bmap, &req, dat);
		nilfs_direct_set_ptr(bmap, key, NILFS_BMAP_INVALID_PTR);
		nilfs_inode_sub_blocks(bmap->b_inode, 1);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_direct_seek_key(स्थिर काष्ठा nilfs_bmap *direct, __u64 start,
				 __u64 *keyp)
अणु
	__u64 key;

	क्रम (key = start; key <= NILFS_सूचीECT_KEY_MAX; key++) अणु
		अगर (nilfs_direct_get_ptr(direct, key) !=
		    NILFS_BMAP_INVALID_PTR) अणु
			*keyp = key;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक nilfs_direct_last_key(स्थिर काष्ठा nilfs_bmap *direct, __u64 *keyp)
अणु
	__u64 key, lastkey;

	lastkey = NILFS_सूचीECT_KEY_MAX + 1;
	क्रम (key = NILFS_सूचीECT_KEY_MIN; key <= NILFS_सूचीECT_KEY_MAX; key++)
		अगर (nilfs_direct_get_ptr(direct, key) !=
		    NILFS_BMAP_INVALID_PTR)
			lastkey = key;

	अगर (lastkey == NILFS_सूचीECT_KEY_MAX + 1)
		वापस -ENOENT;

	*keyp = lastkey;

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_direct_check_insert(स्थिर काष्ठा nilfs_bmap *bmap, __u64 key)
अणु
	वापस key > NILFS_सूचीECT_KEY_MAX;
पूर्ण

अटल पूर्णांक nilfs_direct_gather_data(काष्ठा nilfs_bmap *direct,
				    __u64 *keys, __u64 *ptrs, पूर्णांक nitems)
अणु
	__u64 key;
	__u64 ptr;
	पूर्णांक n;

	अगर (nitems > NILFS_सूचीECT_NBLOCKS)
		nitems = NILFS_सूचीECT_NBLOCKS;
	n = 0;
	क्रम (key = 0; key < nitems; key++) अणु
		ptr = nilfs_direct_get_ptr(direct, key);
		अगर (ptr != NILFS_BMAP_INVALID_PTR) अणु
			keys[n] = key;
			ptrs[n] = ptr;
			n++;
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण

पूर्णांक nilfs_direct_delete_and_convert(काष्ठा nilfs_bmap *bmap,
				    __u64 key, __u64 *keys, __u64 *ptrs, पूर्णांक n)
अणु
	__le64 *dptrs;
	पूर्णांक ret, i, j;

	/* no need to allocate any resource क्रम conversion */

	/* delete */
	ret = bmap->b_ops->bop_delete(bmap, key);
	अगर (ret < 0)
		वापस ret;

	/* मुक्त resources */
	अगर (bmap->b_ops->bop_clear != शून्य)
		bmap->b_ops->bop_clear(bmap);

	/* convert */
	dptrs = nilfs_direct_dptrs(bmap);
	क्रम (i = 0, j = 0; i < NILFS_सूचीECT_NBLOCKS; i++) अणु
		अगर ((j < n) && (i == keys[j])) अणु
			dptrs[i] = (i != key) ?
				cpu_to_le64(ptrs[j]) :
				NILFS_BMAP_INVALID_PTR;
			j++;
		पूर्ण अन्यथा
			dptrs[i] = NILFS_BMAP_INVALID_PTR;
	पूर्ण

	nilfs_direct_init(bmap);
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_direct_propagate(काष्ठा nilfs_bmap *bmap,
				  काष्ठा buffer_head *bh)
अणु
	काष्ठा nilfs_palloc_req oldreq, newreq;
	काष्ठा inode *dat;
	__u64 key;
	__u64 ptr;
	पूर्णांक ret;

	अगर (!NILFS_BMAP_USE_VBN(bmap))
		वापस 0;

	dat = nilfs_bmap_get_dat(bmap);
	key = nilfs_bmap_data_get_key(bmap, bh);
	ptr = nilfs_direct_get_ptr(bmap, key);
	अगर (!buffer_nilfs_अस्थिर(bh)) अणु
		oldreq.pr_entry_nr = ptr;
		newreq.pr_entry_nr = ptr;
		ret = nilfs_dat_prepare_update(dat, &oldreq, &newreq);
		अगर (ret < 0)
			वापस ret;
		nilfs_dat_commit_update(dat, &oldreq, &newreq,
					bmap->b_ptr_type == NILFS_BMAP_PTR_VS);
		set_buffer_nilfs_अस्थिर(bh);
		nilfs_direct_set_ptr(bmap, key, newreq.pr_entry_nr);
	पूर्ण अन्यथा
		ret = nilfs_dat_mark_dirty(dat, ptr);

	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_direct_assign_v(काष्ठा nilfs_bmap *direct,
				 __u64 key, __u64 ptr,
				 काष्ठा buffer_head **bh,
				 sector_t blocknr,
				 जोड़ nilfs_binfo *binfo)
अणु
	काष्ठा inode *dat = nilfs_bmap_get_dat(direct);
	जोड़ nilfs_bmap_ptr_req req;
	पूर्णांक ret;

	req.bpr_ptr = ptr;
	ret = nilfs_dat_prepare_start(dat, &req.bpr_req);
	अगर (!ret) अणु
		nilfs_dat_commit_start(dat, &req.bpr_req, blocknr);
		binfo->bi_v.bi_vblocknr = cpu_to_le64(ptr);
		binfo->bi_v.bi_blkoff = cpu_to_le64(key);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_direct_assign_p(काष्ठा nilfs_bmap *direct,
				 __u64 key, __u64 ptr,
				 काष्ठा buffer_head **bh,
				 sector_t blocknr,
				 जोड़ nilfs_binfo *binfo)
अणु
	nilfs_direct_set_ptr(direct, key, blocknr);

	binfo->bi_dat.bi_blkoff = cpu_to_le64(key);
	binfo->bi_dat.bi_level = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_direct_assign(काष्ठा nilfs_bmap *bmap,
			       काष्ठा buffer_head **bh,
			       sector_t blocknr,
			       जोड़ nilfs_binfo *binfo)
अणु
	__u64 key;
	__u64 ptr;

	key = nilfs_bmap_data_get_key(bmap, *bh);
	अगर (unlikely(key > NILFS_सूचीECT_KEY_MAX)) अणु
		nilfs_crit(bmap->b_inode->i_sb,
			   "%s (ino=%lu): invalid key: %llu",
			   __func__,
			   bmap->b_inode->i_ino, (अचिन्हित दीर्घ दीर्घ)key);
		वापस -EINVAL;
	पूर्ण
	ptr = nilfs_direct_get_ptr(bmap, key);
	अगर (unlikely(ptr == NILFS_BMAP_INVALID_PTR)) अणु
		nilfs_crit(bmap->b_inode->i_sb,
			   "%s (ino=%lu): invalid pointer: %llu",
			   __func__,
			   bmap->b_inode->i_ino, (अचिन्हित दीर्घ दीर्घ)ptr);
		वापस -EINVAL;
	पूर्ण

	वापस NILFS_BMAP_USE_VBN(bmap) ?
		nilfs_direct_assign_v(bmap, key, ptr, bh, blocknr, binfo) :
		nilfs_direct_assign_p(bmap, key, ptr, bh, blocknr, binfo);
पूर्ण

अटल स्थिर काष्ठा nilfs_bmap_operations nilfs_direct_ops = अणु
	.bop_lookup		=	nilfs_direct_lookup,
	.bop_lookup_contig	=	nilfs_direct_lookup_contig,
	.bop_insert		=	nilfs_direct_insert,
	.bop_delete		=	nilfs_direct_delete,
	.bop_clear		=	शून्य,

	.bop_propagate		=	nilfs_direct_propagate,

	.bop_lookup_dirty_buffers	=	शून्य,

	.bop_assign		=	nilfs_direct_assign,
	.bop_mark		=	शून्य,

	.bop_seek_key		=	nilfs_direct_seek_key,
	.bop_last_key		=	nilfs_direct_last_key,

	.bop_check_insert	=	nilfs_direct_check_insert,
	.bop_check_delete	=	शून्य,
	.bop_gather_data	=	nilfs_direct_gather_data,
पूर्ण;


पूर्णांक nilfs_direct_init(काष्ठा nilfs_bmap *bmap)
अणु
	bmap->b_ops = &nilfs_direct_ops;
	वापस 0;
पूर्ण
