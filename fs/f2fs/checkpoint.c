<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/checkpoपूर्णांक.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/fs.h>
#समावेश <linux/bपन.स>
#समावेश <linux/mpage.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/swap.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"
#समावेश <trace/events/f2fs.h>

#घोषणा DEFAULT_CHECKPOINT_IOPRIO (IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, 3))

अटल काष्ठा kmem_cache *ino_entry_slab;
काष्ठा kmem_cache *f2fs_inode_entry_slab;

व्योम f2fs_stop_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi, bool end_io)
अणु
	f2fs_build_fault_attr(sbi, 0, 0);
	set_ckpt_flags(sbi, CP_ERROR_FLAG);
	अगर (!end_io)
		f2fs_flush_merged_ग_लिखोs(sbi);
पूर्ण

/*
 * We guarantee no failure on the वापसed page.
 */
काष्ठा page *f2fs_grab_meta_page(काष्ठा f2fs_sb_info *sbi, pgoff_t index)
अणु
	काष्ठा address_space *mapping = META_MAPPING(sbi);
	काष्ठा page *page;
repeat:
	page = f2fs_grab_cache_page(mapping, index, false);
	अगर (!page) अणु
		cond_resched();
		जाओ repeat;
	पूर्ण
	f2fs_रुको_on_page_ग_लिखोback(page, META, true, true);
	अगर (!PageUptodate(page))
		SetPageUptodate(page);
	वापस page;
पूर्ण

अटल काष्ठा page *__get_meta_page(काष्ठा f2fs_sb_info *sbi, pgoff_t index,
							bool is_meta)
अणु
	काष्ठा address_space *mapping = META_MAPPING(sbi);
	काष्ठा page *page;
	काष्ठा f2fs_io_info fio = अणु
		.sbi = sbi,
		.type = META,
		.op = REQ_OP_READ,
		.op_flags = REQ_META | REQ_PRIO,
		.old_blkaddr = index,
		.new_blkaddr = index,
		.encrypted_page = शून्य,
		.is_por = !is_meta,
	पूर्ण;
	पूर्णांक err;

	अगर (unlikely(!is_meta))
		fio.op_flags &= ~REQ_META;
repeat:
	page = f2fs_grab_cache_page(mapping, index, false);
	अगर (!page) अणु
		cond_resched();
		जाओ repeat;
	पूर्ण
	अगर (PageUptodate(page))
		जाओ out;

	fio.page = page;

	err = f2fs_submit_page_bio(&fio);
	अगर (err) अणु
		f2fs_put_page(page, 1);
		वापस ERR_PTR(err);
	पूर्ण

	f2fs_update_iostat(sbi, FS_META_READ_IO, F2FS_BLKSIZE);

	lock_page(page);
	अगर (unlikely(page->mapping != mapping)) अणु
		f2fs_put_page(page, 1);
		जाओ repeat;
	पूर्ण

	अगर (unlikely(!PageUptodate(page))) अणु
		f2fs_put_page(page, 1);
		वापस ERR_PTR(-EIO);
	पूर्ण
out:
	वापस page;
पूर्ण

काष्ठा page *f2fs_get_meta_page(काष्ठा f2fs_sb_info *sbi, pgoff_t index)
अणु
	वापस __get_meta_page(sbi, index, true);
पूर्ण

काष्ठा page *f2fs_get_meta_page_retry(काष्ठा f2fs_sb_info *sbi, pgoff_t index)
अणु
	काष्ठा page *page;
	पूर्णांक count = 0;

retry:
	page = __get_meta_page(sbi, index, true);
	अगर (IS_ERR(page)) अणु
		अगर (PTR_ERR(page) == -EIO &&
				++count <= DEFAULT_RETRY_IO_COUNT)
			जाओ retry;
		f2fs_stop_checkpoपूर्णांक(sbi, false);
	पूर्ण
	वापस page;
पूर्ण

/* क्रम POR only */
काष्ठा page *f2fs_get_पंचांगp_page(काष्ठा f2fs_sb_info *sbi, pgoff_t index)
अणु
	वापस __get_meta_page(sbi, index, false);
पूर्ण

अटल bool __is_biपंचांगap_valid(काष्ठा f2fs_sb_info *sbi, block_t blkaddr,
							पूर्णांक type)
अणु
	काष्ठा seg_entry *se;
	अचिन्हित पूर्णांक segno, offset;
	bool exist;

	अगर (type != DATA_GENERIC_ENHANCE && type != DATA_GENERIC_ENHANCE_READ)
		वापस true;

	segno = GET_SEGNO(sbi, blkaddr);
	offset = GET_BLKOFF_FROM_SEG0(sbi, blkaddr);
	se = get_seg_entry(sbi, segno);

	exist = f2fs_test_bit(offset, se->cur_valid_map);
	अगर (!exist && type == DATA_GENERIC_ENHANCE) अणु
		f2fs_err(sbi, "Inconsistent error blkaddr:%u, sit bitmap:%d",
			 blkaddr, exist);
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		WARN_ON(1);
	पूर्ण
	वापस exist;
पूर्ण

bool f2fs_is_valid_blkaddr(काष्ठा f2fs_sb_info *sbi,
					block_t blkaddr, पूर्णांक type)
अणु
	चयन (type) अणु
	हाल META_NAT:
		अवरोध;
	हाल META_SIT:
		अगर (unlikely(blkaddr >= SIT_BLK_CNT(sbi)))
			वापस false;
		अवरोध;
	हाल META_SSA:
		अगर (unlikely(blkaddr >= MAIN_BLKADDR(sbi) ||
			blkaddr < SM_I(sbi)->ssa_blkaddr))
			वापस false;
		अवरोध;
	हाल META_CP:
		अगर (unlikely(blkaddr >= SIT_I(sbi)->sit_base_addr ||
			blkaddr < __start_cp_addr(sbi)))
			वापस false;
		अवरोध;
	हाल META_POR:
		अगर (unlikely(blkaddr >= MAX_BLKADDR(sbi) ||
			blkaddr < MAIN_BLKADDR(sbi)))
			वापस false;
		अवरोध;
	हाल DATA_GENERIC:
	हाल DATA_GENERIC_ENHANCE:
	हाल DATA_GENERIC_ENHANCE_READ:
		अगर (unlikely(blkaddr >= MAX_BLKADDR(sbi) ||
				blkaddr < MAIN_BLKADDR(sbi))) अणु
			f2fs_warn(sbi, "access invalid blkaddr:%u",
				  blkaddr);
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			WARN_ON(1);
			वापस false;
		पूर्ण अन्यथा अणु
			वापस __is_biपंचांगap_valid(sbi, blkaddr, type);
		पूर्ण
		अवरोध;
	हाल META_GENERIC:
		अगर (unlikely(blkaddr < SEG0_BLKADDR(sbi) ||
			blkaddr >= MAIN_BLKADDR(sbi)))
			वापस false;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस true;
पूर्ण

/*
 * Readahead CP/NAT/SIT/SSA/POR pages
 */
पूर्णांक f2fs_ra_meta_pages(काष्ठा f2fs_sb_info *sbi, block_t start, पूर्णांक nrpages,
							पूर्णांक type, bool sync)
अणु
	काष्ठा page *page;
	block_t blkno = start;
	काष्ठा f2fs_io_info fio = अणु
		.sbi = sbi,
		.type = META,
		.op = REQ_OP_READ,
		.op_flags = sync ? (REQ_META | REQ_PRIO) : REQ_RAHEAD,
		.encrypted_page = शून्य,
		.in_list = false,
		.is_por = (type == META_POR),
	पूर्ण;
	काष्ठा blk_plug plug;
	पूर्णांक err;

	अगर (unlikely(type == META_POR))
		fio.op_flags &= ~REQ_META;

	blk_start_plug(&plug);
	क्रम (; nrpages-- > 0; blkno++) अणु

		अगर (!f2fs_is_valid_blkaddr(sbi, blkno, type))
			जाओ out;

		चयन (type) अणु
		हाल META_NAT:
			अगर (unlikely(blkno >=
					NAT_BLOCK_OFFSET(NM_I(sbi)->max_nid)))
				blkno = 0;
			/* get nat block addr */
			fio.new_blkaddr = current_nat_addr(sbi,
					blkno * NAT_ENTRY_PER_BLOCK);
			अवरोध;
		हाल META_SIT:
			अगर (unlikely(blkno >= TOTAL_SEGS(sbi)))
				जाओ out;
			/* get sit block addr */
			fio.new_blkaddr = current_sit_addr(sbi,
					blkno * SIT_ENTRY_PER_BLOCK);
			अवरोध;
		हाल META_SSA:
		हाल META_CP:
		हाल META_POR:
			fio.new_blkaddr = blkno;
			अवरोध;
		शेष:
			BUG();
		पूर्ण

		page = f2fs_grab_cache_page(META_MAPPING(sbi),
						fio.new_blkaddr, false);
		अगर (!page)
			जारी;
		अगर (PageUptodate(page)) अणु
			f2fs_put_page(page, 1);
			जारी;
		पूर्ण

		fio.page = page;
		err = f2fs_submit_page_bio(&fio);
		f2fs_put_page(page, err ? 1 : 0);

		अगर (!err)
			f2fs_update_iostat(sbi, FS_META_READ_IO, F2FS_BLKSIZE);
	पूर्ण
out:
	blk_finish_plug(&plug);
	वापस blkno - start;
पूर्ण

व्योम f2fs_ra_meta_pages_cond(काष्ठा f2fs_sb_info *sbi, pgoff_t index)
अणु
	काष्ठा page *page;
	bool पढ़ोahead = false;

	page = find_get_page(META_MAPPING(sbi), index);
	अगर (!page || !PageUptodate(page))
		पढ़ोahead = true;
	f2fs_put_page(page, 0);

	अगर (पढ़ोahead)
		f2fs_ra_meta_pages(sbi, index, BIO_MAX_VECS, META_POR, true);
पूर्ण

अटल पूर्णांक __f2fs_ग_लिखो_meta_page(काष्ठा page *page,
				काष्ठा ग_लिखोback_control *wbc,
				क्रमागत iostat_type io_type)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_P_SB(page);

	trace_f2fs_ग_लिखोpage(page, META);

	अगर (unlikely(f2fs_cp_error(sbi)))
		जाओ redirty_out;
	अगर (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		जाओ redirty_out;
	अगर (wbc->क्रम_reclaim && page->index < GET_SUM_BLOCK(sbi, 0))
		जाओ redirty_out;

	f2fs_करो_ग_लिखो_meta_page(sbi, page, io_type);
	dec_page_count(sbi, F2FS_सूचीTY_META);

	अगर (wbc->क्रम_reclaim)
		f2fs_submit_merged_ग_लिखो_cond(sbi, शून्य, page, 0, META);

	unlock_page(page);

	अगर (unlikely(f2fs_cp_error(sbi)))
		f2fs_submit_merged_ग_लिखो(sbi, META);

	वापस 0;

redirty_out:
	redirty_page_क्रम_ग_लिखोpage(wbc, page);
	वापस AOP_WRITEPAGE_ACTIVATE;
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_meta_page(काष्ठा page *page,
				काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस __f2fs_ग_लिखो_meta_page(page, wbc, FS_META_IO);
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_meta_pages(काष्ठा address_space *mapping,
				काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_M_SB(mapping);
	दीर्घ dअगरf, written;

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		जाओ skip_ग_लिखो;

	/* collect a number of dirty meta pages and ग_लिखो together */
	अगर (wbc->sync_mode != WB_SYNC_ALL &&
			get_pages(sbi, F2FS_सूचीTY_META) <
					nr_pages_to_skip(sbi, META))
		जाओ skip_ग_लिखो;

	/* अगर locked failed, cp will flush dirty pages instead */
	अगर (!करोwn_ग_लिखो_trylock(&sbi->cp_global_sem))
		जाओ skip_ग_लिखो;

	trace_f2fs_ग_लिखोpages(mapping->host, wbc, META);
	dअगरf = nr_pages_to_ग_लिखो(sbi, META, wbc);
	written = f2fs_sync_meta_pages(sbi, META, wbc->nr_to_ग_लिखो, FS_META_IO);
	up_ग_लिखो(&sbi->cp_global_sem);
	wbc->nr_to_ग_लिखो = max((दीर्घ)0, wbc->nr_to_ग_लिखो - written - dअगरf);
	वापस 0;

skip_ग_लिखो:
	wbc->pages_skipped += get_pages(sbi, F2FS_सूचीTY_META);
	trace_f2fs_ग_लिखोpages(mapping->host, wbc, META);
	वापस 0;
पूर्ण

दीर्घ f2fs_sync_meta_pages(काष्ठा f2fs_sb_info *sbi, क्रमागत page_type type,
				दीर्घ nr_to_ग_लिखो, क्रमागत iostat_type io_type)
अणु
	काष्ठा address_space *mapping = META_MAPPING(sbi);
	pgoff_t index = 0, prev = अच_दीर्घ_उच्च;
	काष्ठा pagevec pvec;
	दीर्घ nwritten = 0;
	पूर्णांक nr_pages;
	काष्ठा ग_लिखोback_control wbc = अणु
		.क्रम_reclaim = 0,
	पूर्ण;
	काष्ठा blk_plug plug;

	pagevec_init(&pvec);

	blk_start_plug(&plug);

	जबतक ((nr_pages = pagevec_lookup_tag(&pvec, mapping, &index,
				PAGECACHE_TAG_सूचीTY))) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			अगर (prev == अच_दीर्घ_उच्च)
				prev = page->index - 1;
			अगर (nr_to_ग_लिखो != दीर्घ_उच्च && page->index != prev + 1) अणु
				pagevec_release(&pvec);
				जाओ stop;
			पूर्ण

			lock_page(page);

			अगर (unlikely(page->mapping != mapping)) अणु
जारी_unlock:
				unlock_page(page);
				जारी;
			पूर्ण
			अगर (!PageDirty(page)) अणु
				/* someone wrote it क्रम us */
				जाओ जारी_unlock;
			पूर्ण

			f2fs_रुको_on_page_ग_लिखोback(page, META, true, true);

			अगर (!clear_page_dirty_क्रम_io(page))
				जाओ जारी_unlock;

			अगर (__f2fs_ग_लिखो_meta_page(page, &wbc, io_type)) अणु
				unlock_page(page);
				अवरोध;
			पूर्ण
			nwritten++;
			prev = page->index;
			अगर (unlikely(nwritten >= nr_to_ग_लिखो))
				अवरोध;
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
stop:
	अगर (nwritten)
		f2fs_submit_merged_ग_लिखो(sbi, type);

	blk_finish_plug(&plug);

	वापस nwritten;
पूर्ण

अटल पूर्णांक f2fs_set_meta_page_dirty(काष्ठा page *page)
अणु
	trace_f2fs_set_page_dirty(page, META);

	अगर (!PageUptodate(page))
		SetPageUptodate(page);
	अगर (!PageDirty(page)) अणु
		__set_page_dirty_nobuffers(page);
		inc_page_count(F2FS_P_SB(page), F2FS_सूचीTY_META);
		f2fs_set_page_निजी(page, 0);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा address_space_operations f2fs_meta_aops = अणु
	.ग_लिखोpage	= f2fs_ग_लिखो_meta_page,
	.ग_लिखोpages	= f2fs_ग_लिखो_meta_pages,
	.set_page_dirty	= f2fs_set_meta_page_dirty,
	.invalidatepage = f2fs_invalidate_page,
	.releasepage	= f2fs_release_page,
#अगर_घोषित CONFIG_MIGRATION
	.migratepage    = f2fs_migrate_page,
#पूर्ण_अगर
पूर्ण;

अटल व्योम __add_ino_entry(काष्ठा f2fs_sb_info *sbi, nid_t ino,
						अचिन्हित पूर्णांक devidx, पूर्णांक type)
अणु
	काष्ठा inode_management *im = &sbi->im[type];
	काष्ठा ino_entry *e, *पंचांगp;

	पंचांगp = f2fs_kmem_cache_alloc(ino_entry_slab, GFP_NOFS);

	radix_tree_preload(GFP_NOFS | __GFP_NOFAIL);

	spin_lock(&im->ino_lock);
	e = radix_tree_lookup(&im->ino_root, ino);
	अगर (!e) अणु
		e = पंचांगp;
		अगर (unlikely(radix_tree_insert(&im->ino_root, ino, e)))
			f2fs_bug_on(sbi, 1);

		स_रखो(e, 0, माप(काष्ठा ino_entry));
		e->ino = ino;

		list_add_tail(&e->list, &im->ino_list);
		अगर (type != ORPHAN_INO)
			im->ino_num++;
	पूर्ण

	अगर (type == FLUSH_INO)
		f2fs_set_bit(devidx, (अक्षर *)&e->dirty_device);

	spin_unlock(&im->ino_lock);
	radix_tree_preload_end();

	अगर (e != पंचांगp)
		kmem_cache_मुक्त(ino_entry_slab, पंचांगp);
पूर्ण

अटल व्योम __हटाओ_ino_entry(काष्ठा f2fs_sb_info *sbi, nid_t ino, पूर्णांक type)
अणु
	काष्ठा inode_management *im = &sbi->im[type];
	काष्ठा ino_entry *e;

	spin_lock(&im->ino_lock);
	e = radix_tree_lookup(&im->ino_root, ino);
	अगर (e) अणु
		list_del(&e->list);
		radix_tree_delete(&im->ino_root, ino);
		im->ino_num--;
		spin_unlock(&im->ino_lock);
		kmem_cache_मुक्त(ino_entry_slab, e);
		वापस;
	पूर्ण
	spin_unlock(&im->ino_lock);
पूर्ण

व्योम f2fs_add_ino_entry(काष्ठा f2fs_sb_info *sbi, nid_t ino, पूर्णांक type)
अणु
	/* add new dirty ino entry पूर्णांकo list */
	__add_ino_entry(sbi, ino, 0, type);
पूर्ण

व्योम f2fs_हटाओ_ino_entry(काष्ठा f2fs_sb_info *sbi, nid_t ino, पूर्णांक type)
अणु
	/* हटाओ dirty ino entry from list */
	__हटाओ_ino_entry(sbi, ino, type);
पूर्ण

/* mode should be APPEND_INO, UPDATE_INO or TRANS_सूची_INO */
bool f2fs_exist_written_data(काष्ठा f2fs_sb_info *sbi, nid_t ino, पूर्णांक mode)
अणु
	काष्ठा inode_management *im = &sbi->im[mode];
	काष्ठा ino_entry *e;

	spin_lock(&im->ino_lock);
	e = radix_tree_lookup(&im->ino_root, ino);
	spin_unlock(&im->ino_lock);
	वापस e ? true : false;
पूर्ण

व्योम f2fs_release_ino_entry(काष्ठा f2fs_sb_info *sbi, bool all)
अणु
	काष्ठा ino_entry *e, *पंचांगp;
	पूर्णांक i;

	क्रम (i = all ? ORPHAN_INO : APPEND_INO; i < MAX_INO_ENTRY; i++) अणु
		काष्ठा inode_management *im = &sbi->im[i];

		spin_lock(&im->ino_lock);
		list_क्रम_each_entry_safe(e, पंचांगp, &im->ino_list, list) अणु
			list_del(&e->list);
			radix_tree_delete(&im->ino_root, e->ino);
			kmem_cache_मुक्त(ino_entry_slab, e);
			im->ino_num--;
		पूर्ण
		spin_unlock(&im->ino_lock);
	पूर्ण
पूर्ण

व्योम f2fs_set_dirty_device(काष्ठा f2fs_sb_info *sbi, nid_t ino,
					अचिन्हित पूर्णांक devidx, पूर्णांक type)
अणु
	__add_ino_entry(sbi, ino, devidx, type);
पूर्ण

bool f2fs_is_dirty_device(काष्ठा f2fs_sb_info *sbi, nid_t ino,
					अचिन्हित पूर्णांक devidx, पूर्णांक type)
अणु
	काष्ठा inode_management *im = &sbi->im[type];
	काष्ठा ino_entry *e;
	bool is_dirty = false;

	spin_lock(&im->ino_lock);
	e = radix_tree_lookup(&im->ino_root, ino);
	अगर (e && f2fs_test_bit(devidx, (अक्षर *)&e->dirty_device))
		is_dirty = true;
	spin_unlock(&im->ino_lock);
	वापस is_dirty;
पूर्ण

पूर्णांक f2fs_acquire_orphan_inode(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा inode_management *im = &sbi->im[ORPHAN_INO];
	पूर्णांक err = 0;

	spin_lock(&im->ino_lock);

	अगर (समय_प्रकारo_inject(sbi, FAULT_ORPHAN)) अणु
		spin_unlock(&im->ino_lock);
		f2fs_show_injection_info(sbi, FAULT_ORPHAN);
		वापस -ENOSPC;
	पूर्ण

	अगर (unlikely(im->ino_num >= sbi->max_orphans))
		err = -ENOSPC;
	अन्यथा
		im->ino_num++;
	spin_unlock(&im->ino_lock);

	वापस err;
पूर्ण

व्योम f2fs_release_orphan_inode(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा inode_management *im = &sbi->im[ORPHAN_INO];

	spin_lock(&im->ino_lock);
	f2fs_bug_on(sbi, im->ino_num == 0);
	im->ino_num--;
	spin_unlock(&im->ino_lock);
पूर्ण

व्योम f2fs_add_orphan_inode(काष्ठा inode *inode)
अणु
	/* add new orphan ino entry पूर्णांकo list */
	__add_ino_entry(F2FS_I_SB(inode), inode->i_ino, 0, ORPHAN_INO);
	f2fs_update_inode_page(inode);
पूर्ण

व्योम f2fs_हटाओ_orphan_inode(काष्ठा f2fs_sb_info *sbi, nid_t ino)
अणु
	/* हटाओ orphan entry from orphan list */
	__हटाओ_ino_entry(sbi, ino, ORPHAN_INO);
पूर्ण

अटल पूर्णांक recover_orphan_inode(काष्ठा f2fs_sb_info *sbi, nid_t ino)
अणु
	काष्ठा inode *inode;
	काष्ठा node_info ni;
	पूर्णांक err;

	inode = f2fs_iget_retry(sbi->sb, ino);
	अगर (IS_ERR(inode)) अणु
		/*
		 * there should be a bug that we can't find the entry
		 * to orphan inode.
		 */
		f2fs_bug_on(sbi, PTR_ERR(inode) == -ENOENT);
		वापस PTR_ERR(inode);
	पूर्ण

	err = dquot_initialize(inode);
	अगर (err) अणु
		iput(inode);
		जाओ err_out;
	पूर्ण

	clear_nlink(inode);

	/* truncate all the data during iput */
	iput(inode);

	err = f2fs_get_node_info(sbi, ino, &ni);
	अगर (err)
		जाओ err_out;

	/* ENOMEM was fully retried in f2fs_evict_inode. */
	अगर (ni.blk_addr != शून्य_ADDR) अणु
		err = -EIO;
		जाओ err_out;
	पूर्ण
	वापस 0;

err_out:
	set_sbi_flag(sbi, SBI_NEED_FSCK);
	f2fs_warn(sbi, "%s: orphan failed (ino=%x), run fsck to fix.",
		  __func__, ino);
	वापस err;
पूर्ण

पूर्णांक f2fs_recover_orphan_inodes(काष्ठा f2fs_sb_info *sbi)
अणु
	block_t start_blk, orphan_blocks, i, j;
	अचिन्हित पूर्णांक s_flags = sbi->sb->s_flags;
	पूर्णांक err = 0;
#अगर_घोषित CONFIG_QUOTA
	पूर्णांक quota_enabled;
#पूर्ण_अगर

	अगर (!is_set_ckpt_flags(sbi, CP_ORPHAN_PRESENT_FLAG))
		वापस 0;

	अगर (bdev_पढ़ो_only(sbi->sb->s_bdev)) अणु
		f2fs_info(sbi, "write access unavailable, skipping orphan cleanup");
		वापस 0;
	पूर्ण

	अगर (s_flags & SB_RDONLY) अणु
		f2fs_info(sbi, "orphan cleanup on readonly fs");
		sbi->sb->s_flags &= ~SB_RDONLY;
	पूर्ण

#अगर_घोषित CONFIG_QUOTA
	/* Needed क्रम iput() to work correctly and not trash data */
	sbi->sb->s_flags |= SB_ACTIVE;

	/*
	 * Turn on quotas which were not enabled क्रम पढ़ो-only mounts अगर
	 * fileप्रणाली has quota feature, so that they are updated correctly.
	 */
	quota_enabled = f2fs_enable_quota_files(sbi, s_flags & SB_RDONLY);
#पूर्ण_अगर

	start_blk = __start_cp_addr(sbi) + 1 + __cp_payload(sbi);
	orphan_blocks = __start_sum_addr(sbi) - 1 - __cp_payload(sbi);

	f2fs_ra_meta_pages(sbi, start_blk, orphan_blocks, META_CP, true);

	क्रम (i = 0; i < orphan_blocks; i++) अणु
		काष्ठा page *page;
		काष्ठा f2fs_orphan_block *orphan_blk;

		page = f2fs_get_meta_page(sbi, start_blk + i);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			जाओ out;
		पूर्ण

		orphan_blk = (काष्ठा f2fs_orphan_block *)page_address(page);
		क्रम (j = 0; j < le32_to_cpu(orphan_blk->entry_count); j++) अणु
			nid_t ino = le32_to_cpu(orphan_blk->ino[j]);

			err = recover_orphan_inode(sbi, ino);
			अगर (err) अणु
				f2fs_put_page(page, 1);
				जाओ out;
			पूर्ण
		पूर्ण
		f2fs_put_page(page, 1);
	पूर्ण
	/* clear Orphan Flag */
	clear_ckpt_flags(sbi, CP_ORPHAN_PRESENT_FLAG);
out:
	set_sbi_flag(sbi, SBI_IS_RECOVERED);

#अगर_घोषित CONFIG_QUOTA
	/* Turn quotas off */
	अगर (quota_enabled)
		f2fs_quota_off_umount(sbi->sb);
#पूर्ण_अगर
	sbi->sb->s_flags = s_flags; /* Restore SB_RDONLY status */

	वापस err;
पूर्ण

अटल व्योम ग_लिखो_orphan_inodes(काष्ठा f2fs_sb_info *sbi, block_t start_blk)
अणु
	काष्ठा list_head *head;
	काष्ठा f2fs_orphan_block *orphan_blk = शून्य;
	अचिन्हित पूर्णांक nentries = 0;
	अचिन्हित लघु index = 1;
	अचिन्हित लघु orphan_blocks;
	काष्ठा page *page = शून्य;
	काष्ठा ino_entry *orphan = शून्य;
	काष्ठा inode_management *im = &sbi->im[ORPHAN_INO];

	orphan_blocks = GET_ORPHAN_BLOCKS(im->ino_num);

	/*
	 * we करोn't need to करो spin_lock(&im->ino_lock) here, since all the
	 * orphan inode operations are covered under f2fs_lock_op().
	 * And, spin_lock should be aव्योमed due to page operations below.
	 */
	head = &im->ino_list;

	/* loop क्रम each orphan inode entry and ग_लिखो them in Jornal block */
	list_क्रम_each_entry(orphan, head, list) अणु
		अगर (!page) अणु
			page = f2fs_grab_meta_page(sbi, start_blk++);
			orphan_blk =
				(काष्ठा f2fs_orphan_block *)page_address(page);
			स_रखो(orphan_blk, 0, माप(*orphan_blk));
		पूर्ण

		orphan_blk->ino[nentries++] = cpu_to_le32(orphan->ino);

		अगर (nentries == F2FS_ORPHANS_PER_BLOCK) अणु
			/*
			 * an orphan block is full of 1020 entries,
			 * then we need to flush current orphan blocks
			 * and bring another one in memory
			 */
			orphan_blk->blk_addr = cpu_to_le16(index);
			orphan_blk->blk_count = cpu_to_le16(orphan_blocks);
			orphan_blk->entry_count = cpu_to_le32(nentries);
			set_page_dirty(page);
			f2fs_put_page(page, 1);
			index++;
			nentries = 0;
			page = शून्य;
		पूर्ण
	पूर्ण

	अगर (page) अणु
		orphan_blk->blk_addr = cpu_to_le16(index);
		orphan_blk->blk_count = cpu_to_le16(orphan_blocks);
		orphan_blk->entry_count = cpu_to_le32(nentries);
		set_page_dirty(page);
		f2fs_put_page(page, 1);
	पूर्ण
पूर्ण

अटल __u32 f2fs_checkpoपूर्णांक_chksum(काष्ठा f2fs_sb_info *sbi,
						काष्ठा f2fs_checkpoपूर्णांक *ckpt)
अणु
	अचिन्हित पूर्णांक chksum_ofs = le32_to_cpu(ckpt->checksum_offset);
	__u32 chksum;

	chksum = f2fs_crc32(sbi, ckpt, chksum_ofs);
	अगर (chksum_ofs < CP_CHKSUM_OFFSET) अणु
		chksum_ofs += माप(chksum);
		chksum = f2fs_chksum(sbi, chksum, (__u8 *)ckpt + chksum_ofs,
						F2FS_BLKSIZE - chksum_ofs);
	पूर्ण
	वापस chksum;
पूर्ण

अटल पूर्णांक get_checkpoपूर्णांक_version(काष्ठा f2fs_sb_info *sbi, block_t cp_addr,
		काष्ठा f2fs_checkpoपूर्णांक **cp_block, काष्ठा page **cp_page,
		अचिन्हित दीर्घ दीर्घ *version)
अणु
	माप_प्रकार crc_offset = 0;
	__u32 crc;

	*cp_page = f2fs_get_meta_page(sbi, cp_addr);
	अगर (IS_ERR(*cp_page))
		वापस PTR_ERR(*cp_page);

	*cp_block = (काष्ठा f2fs_checkpoपूर्णांक *)page_address(*cp_page);

	crc_offset = le32_to_cpu((*cp_block)->checksum_offset);
	अगर (crc_offset < CP_MIN_CHKSUM_OFFSET ||
			crc_offset > CP_CHKSUM_OFFSET) अणु
		f2fs_put_page(*cp_page, 1);
		f2fs_warn(sbi, "invalid crc_offset: %zu", crc_offset);
		वापस -EINVAL;
	पूर्ण

	crc = f2fs_checkpoपूर्णांक_chksum(sbi, *cp_block);
	अगर (crc != cur_cp_crc(*cp_block)) अणु
		f2fs_put_page(*cp_page, 1);
		f2fs_warn(sbi, "invalid crc value");
		वापस -EINVAL;
	पूर्ण

	*version = cur_cp_version(*cp_block);
	वापस 0;
पूर्ण

अटल काष्ठा page *validate_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi,
				block_t cp_addr, अचिन्हित दीर्घ दीर्घ *version)
अणु
	काष्ठा page *cp_page_1 = शून्य, *cp_page_2 = शून्य;
	काष्ठा f2fs_checkpoपूर्णांक *cp_block = शून्य;
	अचिन्हित दीर्घ दीर्घ cur_version = 0, pre_version = 0;
	पूर्णांक err;

	err = get_checkpoपूर्णांक_version(sbi, cp_addr, &cp_block,
					&cp_page_1, version);
	अगर (err)
		वापस शून्य;

	अगर (le32_to_cpu(cp_block->cp_pack_total_block_count) >
					sbi->blocks_per_seg) अणु
		f2fs_warn(sbi, "invalid cp_pack_total_block_count:%u",
			  le32_to_cpu(cp_block->cp_pack_total_block_count));
		जाओ invalid_cp;
	पूर्ण
	pre_version = *version;

	cp_addr += le32_to_cpu(cp_block->cp_pack_total_block_count) - 1;
	err = get_checkpoपूर्णांक_version(sbi, cp_addr, &cp_block,
					&cp_page_2, version);
	अगर (err)
		जाओ invalid_cp;
	cur_version = *version;

	अगर (cur_version == pre_version) अणु
		*version = cur_version;
		f2fs_put_page(cp_page_2, 1);
		वापस cp_page_1;
	पूर्ण
	f2fs_put_page(cp_page_2, 1);
invalid_cp:
	f2fs_put_page(cp_page_1, 1);
	वापस शून्य;
पूर्ण

पूर्णांक f2fs_get_valid_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *cp_block;
	काष्ठा f2fs_super_block *fsb = sbi->raw_super;
	काष्ठा page *cp1, *cp2, *cur_page;
	अचिन्हित दीर्घ blk_size = sbi->blocksize;
	अचिन्हित दीर्घ दीर्घ cp1_version = 0, cp2_version = 0;
	अचिन्हित दीर्घ दीर्घ cp_start_blk_no;
	अचिन्हित पूर्णांक cp_blks = 1 + __cp_payload(sbi);
	block_t cp_blk_no;
	पूर्णांक i;
	पूर्णांक err;

	sbi->ckpt = f2fs_kvzalloc(sbi, array_size(blk_size, cp_blks),
				  GFP_KERNEL);
	अगर (!sbi->ckpt)
		वापस -ENOMEM;
	/*
	 * Finding out valid cp block involves पढ़ो both
	 * sets( cp pack 1 and cp pack 2)
	 */
	cp_start_blk_no = le32_to_cpu(fsb->cp_blkaddr);
	cp1 = validate_checkpoपूर्णांक(sbi, cp_start_blk_no, &cp1_version);

	/* The second checkpoपूर्णांक pack should start at the next segment */
	cp_start_blk_no += ((अचिन्हित दीर्घ दीर्घ)1) <<
				le32_to_cpu(fsb->log_blocks_per_seg);
	cp2 = validate_checkpoपूर्णांक(sbi, cp_start_blk_no, &cp2_version);

	अगर (cp1 && cp2) अणु
		अगर (ver_after(cp2_version, cp1_version))
			cur_page = cp2;
		अन्यथा
			cur_page = cp1;
	पूर्ण अन्यथा अगर (cp1) अणु
		cur_page = cp1;
	पूर्ण अन्यथा अगर (cp2) अणु
		cur_page = cp2;
	पूर्ण अन्यथा अणु
		err = -EFSCORRUPTED;
		जाओ fail_no_cp;
	पूर्ण

	cp_block = (काष्ठा f2fs_checkpoपूर्णांक *)page_address(cur_page);
	स_नकल(sbi->ckpt, cp_block, blk_size);

	अगर (cur_page == cp1)
		sbi->cur_cp_pack = 1;
	अन्यथा
		sbi->cur_cp_pack = 2;

	/* Sanity checking of checkpoपूर्णांक */
	अगर (f2fs_sanity_check_ckpt(sbi)) अणु
		err = -EFSCORRUPTED;
		जाओ मुक्त_fail_no_cp;
	पूर्ण

	अगर (cp_blks <= 1)
		जाओ करोne;

	cp_blk_no = le32_to_cpu(fsb->cp_blkaddr);
	अगर (cur_page == cp2)
		cp_blk_no += 1 << le32_to_cpu(fsb->log_blocks_per_seg);

	क्रम (i = 1; i < cp_blks; i++) अणु
		व्योम *sit_biपंचांगap_ptr;
		अचिन्हित अक्षर *ckpt = (अचिन्हित अक्षर *)sbi->ckpt;

		cur_page = f2fs_get_meta_page(sbi, cp_blk_no + i);
		अगर (IS_ERR(cur_page)) अणु
			err = PTR_ERR(cur_page);
			जाओ मुक्त_fail_no_cp;
		पूर्ण
		sit_biपंचांगap_ptr = page_address(cur_page);
		स_नकल(ckpt + i * blk_size, sit_biपंचांगap_ptr, blk_size);
		f2fs_put_page(cur_page, 1);
	पूर्ण
करोne:
	f2fs_put_page(cp1, 1);
	f2fs_put_page(cp2, 1);
	वापस 0;

मुक्त_fail_no_cp:
	f2fs_put_page(cp1, 1);
	f2fs_put_page(cp2, 1);
fail_no_cp:
	kvमुक्त(sbi->ckpt);
	वापस err;
पूर्ण

अटल व्योम __add_dirty_inode(काष्ठा inode *inode, क्रमागत inode_type type)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक flag = (type == सूची_INODE) ? FI_सूचीTY_सूची : FI_सूचीTY_खाता;

	अगर (is_inode_flag_set(inode, flag))
		वापस;

	set_inode_flag(inode, flag);
	अगर (!f2fs_is_अस्थिर_file(inode))
		list_add_tail(&F2FS_I(inode)->dirty_list,
						&sbi->inode_list[type]);
	stat_inc_dirty_inode(sbi, type);
पूर्ण

अटल व्योम __हटाओ_dirty_inode(काष्ठा inode *inode, क्रमागत inode_type type)
अणु
	पूर्णांक flag = (type == सूची_INODE) ? FI_सूचीTY_सूची : FI_सूचीTY_खाता;

	अगर (get_dirty_pages(inode) || !is_inode_flag_set(inode, flag))
		वापस;

	list_del_init(&F2FS_I(inode)->dirty_list);
	clear_inode_flag(inode, flag);
	stat_dec_dirty_inode(F2FS_I_SB(inode), type);
पूर्ण

व्योम f2fs_update_dirty_page(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	क्रमागत inode_type type = S_ISसूची(inode->i_mode) ? सूची_INODE : खाता_INODE;

	अगर (!S_ISसूची(inode->i_mode) && !S_ISREG(inode->i_mode) &&
			!S_ISLNK(inode->i_mode))
		वापस;

	spin_lock(&sbi->inode_lock[type]);
	अगर (type != खाता_INODE || test_opt(sbi, DATA_FLUSH))
		__add_dirty_inode(inode, type);
	inode_inc_dirty_pages(inode);
	spin_unlock(&sbi->inode_lock[type]);

	f2fs_set_page_निजी(page, 0);
पूर्ण

व्योम f2fs_हटाओ_dirty_inode(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	क्रमागत inode_type type = S_ISसूची(inode->i_mode) ? सूची_INODE : खाता_INODE;

	अगर (!S_ISसूची(inode->i_mode) && !S_ISREG(inode->i_mode) &&
			!S_ISLNK(inode->i_mode))
		वापस;

	अगर (type == खाता_INODE && !test_opt(sbi, DATA_FLUSH))
		वापस;

	spin_lock(&sbi->inode_lock[type]);
	__हटाओ_dirty_inode(inode, type);
	spin_unlock(&sbi->inode_lock[type]);
पूर्ण

पूर्णांक f2fs_sync_dirty_inodes(काष्ठा f2fs_sb_info *sbi, क्रमागत inode_type type)
अणु
	काष्ठा list_head *head;
	काष्ठा inode *inode;
	काष्ठा f2fs_inode_info *fi;
	bool is_dir = (type == सूची_INODE);
	अचिन्हित दीर्घ ino = 0;

	trace_f2fs_sync_dirty_inodes_enter(sbi->sb, is_dir,
				get_pages(sbi, is_dir ?
				F2FS_सूचीTY_DENTS : F2FS_सूचीTY_DATA));
retry:
	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		trace_f2fs_sync_dirty_inodes_निकास(sbi->sb, is_dir,
				get_pages(sbi, is_dir ?
				F2FS_सूचीTY_DENTS : F2FS_सूचीTY_DATA));
		वापस -EIO;
	पूर्ण

	spin_lock(&sbi->inode_lock[type]);

	head = &sbi->inode_list[type];
	अगर (list_empty(head)) अणु
		spin_unlock(&sbi->inode_lock[type]);
		trace_f2fs_sync_dirty_inodes_निकास(sbi->sb, is_dir,
				get_pages(sbi, is_dir ?
				F2FS_सूचीTY_DENTS : F2FS_सूचीTY_DATA));
		वापस 0;
	पूर्ण
	fi = list_first_entry(head, काष्ठा f2fs_inode_info, dirty_list);
	inode = igrab(&fi->vfs_inode);
	spin_unlock(&sbi->inode_lock[type]);
	अगर (inode) अणु
		अचिन्हित दीर्घ cur_ino = inode->i_ino;

		F2FS_I(inode)->cp_task = current;

		filemap_fdataग_लिखो(inode->i_mapping);

		F2FS_I(inode)->cp_task = शून्य;

		iput(inode);
		/* We need to give cpu to another ग_लिखोrs. */
		अगर (ino == cur_ino)
			cond_resched();
		अन्यथा
			ino = cur_ino;
	पूर्ण अन्यथा अणु
		/*
		 * We should submit bio, since it exists several
		 * wribacking dentry pages in the मुक्तing inode.
		 */
		f2fs_submit_merged_ग_लिखो(sbi, DATA);
		cond_resched();
	पूर्ण
	जाओ retry;
पूर्ण

पूर्णांक f2fs_sync_inode_meta(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा list_head *head = &sbi->inode_list[सूचीTY_META];
	काष्ठा inode *inode;
	काष्ठा f2fs_inode_info *fi;
	s64 total = get_pages(sbi, F2FS_सूचीTY_IMETA);

	जबतक (total--) अणु
		अगर (unlikely(f2fs_cp_error(sbi)))
			वापस -EIO;

		spin_lock(&sbi->inode_lock[सूचीTY_META]);
		अगर (list_empty(head)) अणु
			spin_unlock(&sbi->inode_lock[सूचीTY_META]);
			वापस 0;
		पूर्ण
		fi = list_first_entry(head, काष्ठा f2fs_inode_info,
							gdirty_list);
		inode = igrab(&fi->vfs_inode);
		spin_unlock(&sbi->inode_lock[सूचीTY_META]);
		अगर (inode) अणु
			sync_inode_metadata(inode, 0);

			/* it's on eviction */
			अगर (is_inode_flag_set(inode, FI_सूचीTY_INODE))
				f2fs_update_inode_page(inode);
			iput(inode);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __prepare_cp_block(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	nid_t last_nid = nm_i->next_scan_nid;

	next_मुक्त_nid(sbi, &last_nid);
	ckpt->valid_block_count = cpu_to_le64(valid_user_blocks(sbi));
	ckpt->valid_node_count = cpu_to_le32(valid_node_count(sbi));
	ckpt->valid_inode_count = cpu_to_le32(valid_inode_count(sbi));
	ckpt->next_मुक्त_nid = cpu_to_le32(last_nid);
पूर्ण

अटल bool __need_flush_quota(काष्ठा f2fs_sb_info *sbi)
अणु
	bool ret = false;

	अगर (!is_journalled_quota(sbi))
		वापस false;

	करोwn_ग_लिखो(&sbi->quota_sem);
	अगर (is_sbi_flag_set(sbi, SBI_QUOTA_SKIP_FLUSH)) अणु
		ret = false;
	पूर्ण अन्यथा अगर (is_sbi_flag_set(sbi, SBI_QUOTA_NEED_REPAIR)) अणु
		ret = false;
	पूर्ण अन्यथा अगर (is_sbi_flag_set(sbi, SBI_QUOTA_NEED_FLUSH)) अणु
		clear_sbi_flag(sbi, SBI_QUOTA_NEED_FLUSH);
		ret = true;
	पूर्ण अन्यथा अगर (get_pages(sbi, F2FS_सूचीTY_QDATA)) अणु
		ret = true;
	पूर्ण
	up_ग_लिखो(&sbi->quota_sem);
	वापस ret;
पूर्ण

/*
 * Freeze all the FS-operations क्रम checkpoपूर्णांक.
 */
अटल पूर्णांक block_operations(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_ALL,
		.nr_to_ग_लिखो = दीर्घ_उच्च,
		.क्रम_reclaim = 0,
	पूर्ण;
	पूर्णांक err = 0, cnt = 0;

	/*
	 * Let's flush अंतरभूत_data in dirty node pages.
	 */
	f2fs_flush_अंतरभूत_data(sbi);

retry_flush_quotas:
	f2fs_lock_all(sbi);
	अगर (__need_flush_quota(sbi)) अणु
		पूर्णांक locked;

		अगर (++cnt > DEFAULT_RETRY_QUOTA_FLUSH_COUNT) अणु
			set_sbi_flag(sbi, SBI_QUOTA_SKIP_FLUSH);
			set_sbi_flag(sbi, SBI_QUOTA_NEED_FLUSH);
			जाओ retry_flush_dents;
		पूर्ण
		f2fs_unlock_all(sbi);

		/* only failed during mount/umount/मुक्तze/quotactl */
		locked = करोwn_पढ़ो_trylock(&sbi->sb->s_umount);
		f2fs_quota_sync(sbi->sb, -1);
		अगर (locked)
			up_पढ़ो(&sbi->sb->s_umount);
		cond_resched();
		जाओ retry_flush_quotas;
	पूर्ण

retry_flush_dents:
	/* ग_लिखो all the dirty dentry pages */
	अगर (get_pages(sbi, F2FS_सूचीTY_DENTS)) अणु
		f2fs_unlock_all(sbi);
		err = f2fs_sync_dirty_inodes(sbi, सूची_INODE);
		अगर (err)
			वापस err;
		cond_resched();
		जाओ retry_flush_quotas;
	पूर्ण

	/*
	 * POR: we should ensure that there are no dirty node pages
	 * until finishing nat/sit flush. inode->i_blocks can be updated.
	 */
	करोwn_ग_लिखो(&sbi->node_change);

	अगर (get_pages(sbi, F2FS_सूचीTY_IMETA)) अणु
		up_ग_लिखो(&sbi->node_change);
		f2fs_unlock_all(sbi);
		err = f2fs_sync_inode_meta(sbi);
		अगर (err)
			वापस err;
		cond_resched();
		जाओ retry_flush_quotas;
	पूर्ण

retry_flush_nodes:
	करोwn_ग_लिखो(&sbi->node_ग_लिखो);

	अगर (get_pages(sbi, F2FS_सूचीTY_NODES)) अणु
		up_ग_लिखो(&sbi->node_ग_लिखो);
		atomic_inc(&sbi->wb_sync_req[NODE]);
		err = f2fs_sync_node_pages(sbi, &wbc, false, FS_CP_NODE_IO);
		atomic_dec(&sbi->wb_sync_req[NODE]);
		अगर (err) अणु
			up_ग_लिखो(&sbi->node_change);
			f2fs_unlock_all(sbi);
			वापस err;
		पूर्ण
		cond_resched();
		जाओ retry_flush_nodes;
	पूर्ण

	/*
	 * sbi->node_change is used only क्रम AIO ग_लिखो_begin path which produces
	 * dirty node blocks and some checkpoपूर्णांक values by block allocation.
	 */
	__prepare_cp_block(sbi);
	up_ग_लिखो(&sbi->node_change);
	वापस err;
पूर्ण

अटल व्योम unblock_operations(काष्ठा f2fs_sb_info *sbi)
अणु
	up_ग_लिखो(&sbi->node_ग_लिखो);
	f2fs_unlock_all(sbi);
पूर्ण

व्योम f2fs_रुको_on_all_pages(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	DEFINE_WAIT(रुको);

	क्रम (;;) अणु
		अगर (!get_pages(sbi, type))
			अवरोध;

		अगर (unlikely(f2fs_cp_error(sbi)))
			अवरोध;

		अगर (type == F2FS_सूचीTY_META)
			f2fs_sync_meta_pages(sbi, META, दीर्घ_उच्च,
							FS_CP_META_IO);
		अन्यथा अगर (type == F2FS_WB_CP_DATA)
			f2fs_submit_merged_ग_लिखो(sbi, DATA);

		prepare_to_रुको(&sbi->cp_रुको, &रुको, TASK_UNINTERRUPTIBLE);
		io_schedule_समयout(DEFAULT_IO_TIMEOUT);
	पूर्ण
	finish_रुको(&sbi->cp_रुको, &रुको);
पूर्ण

अटल व्योम update_ckpt_flags(काष्ठा f2fs_sb_info *sbi, काष्ठा cp_control *cpc)
अणु
	अचिन्हित दीर्घ orphan_num = sbi->im[ORPHAN_INO].ino_num;
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sbi->cp_lock, flags);

	अगर ((cpc->reason & CP_UMOUNT) &&
			le32_to_cpu(ckpt->cp_pack_total_block_count) >
			sbi->blocks_per_seg - NM_I(sbi)->nat_bits_blocks)
		disable_nat_bits(sbi, false);

	अगर (cpc->reason & CP_TRIMMED)
		__set_ckpt_flags(ckpt, CP_TRIMMED_FLAG);
	अन्यथा
		__clear_ckpt_flags(ckpt, CP_TRIMMED_FLAG);

	अगर (cpc->reason & CP_UMOUNT)
		__set_ckpt_flags(ckpt, CP_UMOUNT_FLAG);
	अन्यथा
		__clear_ckpt_flags(ckpt, CP_UMOUNT_FLAG);

	अगर (cpc->reason & CP_FASTBOOT)
		__set_ckpt_flags(ckpt, CP_FASTBOOT_FLAG);
	अन्यथा
		__clear_ckpt_flags(ckpt, CP_FASTBOOT_FLAG);

	अगर (orphan_num)
		__set_ckpt_flags(ckpt, CP_ORPHAN_PRESENT_FLAG);
	अन्यथा
		__clear_ckpt_flags(ckpt, CP_ORPHAN_PRESENT_FLAG);

	अगर (is_sbi_flag_set(sbi, SBI_NEED_FSCK))
		__set_ckpt_flags(ckpt, CP_FSCK_FLAG);

	अगर (is_sbi_flag_set(sbi, SBI_IS_RESIZEFS))
		__set_ckpt_flags(ckpt, CP_RESIZEFS_FLAG);
	अन्यथा
		__clear_ckpt_flags(ckpt, CP_RESIZEFS_FLAG);

	अगर (is_sbi_flag_set(sbi, SBI_CP_DISABLED))
		__set_ckpt_flags(ckpt, CP_DISABLED_FLAG);
	अन्यथा
		__clear_ckpt_flags(ckpt, CP_DISABLED_FLAG);

	अगर (is_sbi_flag_set(sbi, SBI_CP_DISABLED_QUICK))
		__set_ckpt_flags(ckpt, CP_DISABLED_QUICK_FLAG);
	अन्यथा
		__clear_ckpt_flags(ckpt, CP_DISABLED_QUICK_FLAG);

	अगर (is_sbi_flag_set(sbi, SBI_QUOTA_SKIP_FLUSH))
		__set_ckpt_flags(ckpt, CP_QUOTA_NEED_FSCK_FLAG);
	अन्यथा
		__clear_ckpt_flags(ckpt, CP_QUOTA_NEED_FSCK_FLAG);

	अगर (is_sbi_flag_set(sbi, SBI_QUOTA_NEED_REPAIR))
		__set_ckpt_flags(ckpt, CP_QUOTA_NEED_FSCK_FLAG);

	/* set this flag to activate crc|cp_ver क्रम recovery */
	__set_ckpt_flags(ckpt, CP_CRC_RECOVERY_FLAG);
	__clear_ckpt_flags(ckpt, CP_NOCRC_RECOVERY_FLAG);

	spin_unlock_irqrestore(&sbi->cp_lock, flags);
पूर्ण

अटल व्योम commit_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi,
	व्योम *src, block_t blk_addr)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.क्रम_reclaim = 0,
	पूर्ण;

	/*
	 * pagevec_lookup_tag and lock_page again will take
	 * some extra समय. Thereक्रमe, f2fs_update_meta_pages and
	 * f2fs_sync_meta_pages are combined in this function.
	 */
	काष्ठा page *page = f2fs_grab_meta_page(sbi, blk_addr);
	पूर्णांक err;

	f2fs_रुको_on_page_ग_लिखोback(page, META, true, true);

	स_नकल(page_address(page), src, PAGE_SIZE);

	set_page_dirty(page);
	अगर (unlikely(!clear_page_dirty_क्रम_io(page)))
		f2fs_bug_on(sbi, 1);

	/* ग_लिखोout cp pack 2 page */
	err = __f2fs_ग_लिखो_meta_page(page, &wbc, FS_CP_META_IO);
	अगर (unlikely(err && f2fs_cp_error(sbi))) अणु
		f2fs_put_page(page, 1);
		वापस;
	पूर्ण

	f2fs_bug_on(sbi, err);
	f2fs_put_page(page, 0);

	/* submit checkpoपूर्णांक (with barrier अगर NOBARRIER is not set) */
	f2fs_submit_merged_ग_लिखो(sbi, META_FLUSH);
पूर्ण

अटल अंतरभूत u64 get_sectors_written(काष्ठा block_device *bdev)
अणु
	वापस (u64)part_stat_पढ़ो(bdev, sectors[STAT_WRITE]);
पूर्ण

u64 f2fs_get_sectors_written(काष्ठा f2fs_sb_info *sbi)
अणु
	अगर (f2fs_is_multi_device(sbi)) अणु
		u64 sectors = 0;
		पूर्णांक i;

		क्रम (i = 0; i < sbi->s_ndevs; i++)
			sectors += get_sectors_written(FDEV(i).bdev);

		वापस sectors;
	पूर्ण

	वापस get_sectors_written(sbi->sb->s_bdev);
पूर्ण

अटल पूर्णांक करो_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi, काष्ठा cp_control *cpc)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	अचिन्हित दीर्घ orphan_num = sbi->im[ORPHAN_INO].ino_num, flags;
	block_t start_blk;
	अचिन्हित पूर्णांक data_sum_blocks, orphan_blocks;
	__u32 crc32 = 0;
	पूर्णांक i;
	पूर्णांक cp_payload_blks = __cp_payload(sbi);
	काष्ठा curseg_info *seg_i = CURSEG_I(sbi, CURSEG_HOT_NODE);
	u64 kbytes_written;
	पूर्णांक err;

	/* Flush all the NAT/SIT pages */
	f2fs_sync_meta_pages(sbi, META, दीर्घ_उच्च, FS_CP_META_IO);

	/* start to update checkpoपूर्णांक, cp ver is alपढ़ोy updated previously */
	ckpt->elapsed_समय = cpu_to_le64(get_mसमय(sbi, true));
	ckpt->मुक्त_segment_count = cpu_to_le32(मुक्त_segments(sbi));
	क्रम (i = 0; i < NR_CURSEG_NODE_TYPE; i++) अणु
		ckpt->cur_node_segno[i] =
			cpu_to_le32(curseg_segno(sbi, i + CURSEG_HOT_NODE));
		ckpt->cur_node_blkoff[i] =
			cpu_to_le16(curseg_blkoff(sbi, i + CURSEG_HOT_NODE));
		ckpt->alloc_type[i + CURSEG_HOT_NODE] =
				curseg_alloc_type(sbi, i + CURSEG_HOT_NODE);
	पूर्ण
	क्रम (i = 0; i < NR_CURSEG_DATA_TYPE; i++) अणु
		ckpt->cur_data_segno[i] =
			cpu_to_le32(curseg_segno(sbi, i + CURSEG_HOT_DATA));
		ckpt->cur_data_blkoff[i] =
			cpu_to_le16(curseg_blkoff(sbi, i + CURSEG_HOT_DATA));
		ckpt->alloc_type[i + CURSEG_HOT_DATA] =
				curseg_alloc_type(sbi, i + CURSEG_HOT_DATA);
	पूर्ण

	/* 2 cp + n data seg summary + orphan inode blocks */
	data_sum_blocks = f2fs_npages_क्रम_summary_flush(sbi, false);
	spin_lock_irqsave(&sbi->cp_lock, flags);
	अगर (data_sum_blocks < NR_CURSEG_DATA_TYPE)
		__set_ckpt_flags(ckpt, CP_COMPACT_SUM_FLAG);
	अन्यथा
		__clear_ckpt_flags(ckpt, CP_COMPACT_SUM_FLAG);
	spin_unlock_irqrestore(&sbi->cp_lock, flags);

	orphan_blocks = GET_ORPHAN_BLOCKS(orphan_num);
	ckpt->cp_pack_start_sum = cpu_to_le32(1 + cp_payload_blks +
			orphan_blocks);

	अगर (__reमुख्य_node_summaries(cpc->reason))
		ckpt->cp_pack_total_block_count = cpu_to_le32(F2FS_CP_PACKS +
				cp_payload_blks + data_sum_blocks +
				orphan_blocks + NR_CURSEG_NODE_TYPE);
	अन्यथा
		ckpt->cp_pack_total_block_count = cpu_to_le32(F2FS_CP_PACKS +
				cp_payload_blks + data_sum_blocks +
				orphan_blocks);

	/* update ckpt flag क्रम checkpoपूर्णांक */
	update_ckpt_flags(sbi, cpc);

	/* update SIT/NAT biपंचांगap */
	get_sit_biपंचांगap(sbi, __biपंचांगap_ptr(sbi, SIT_BITMAP));
	get_nat_biपंचांगap(sbi, __biपंचांगap_ptr(sbi, NAT_BITMAP));

	crc32 = f2fs_checkpoपूर्णांक_chksum(sbi, ckpt);
	*((__le32 *)((अचिन्हित अक्षर *)ckpt +
				le32_to_cpu(ckpt->checksum_offset)))
				= cpu_to_le32(crc32);

	start_blk = __start_cp_next_addr(sbi);

	/* ग_लिखो nat bits */
	अगर (enabled_nat_bits(sbi, cpc)) अणु
		__u64 cp_ver = cur_cp_version(ckpt);
		block_t blk;

		cp_ver |= ((__u64)crc32 << 32);
		*(__le64 *)nm_i->nat_bits = cpu_to_le64(cp_ver);

		blk = start_blk + sbi->blocks_per_seg - nm_i->nat_bits_blocks;
		क्रम (i = 0; i < nm_i->nat_bits_blocks; i++)
			f2fs_update_meta_page(sbi, nm_i->nat_bits +
					(i << F2FS_BLKSIZE_BITS), blk + i);
	पूर्ण

	/* ग_लिखो out checkpoपूर्णांक buffer at block 0 */
	f2fs_update_meta_page(sbi, ckpt, start_blk++);

	क्रम (i = 1; i < 1 + cp_payload_blks; i++)
		f2fs_update_meta_page(sbi, (अक्षर *)ckpt + i * F2FS_BLKSIZE,
							start_blk++);

	अगर (orphan_num) अणु
		ग_लिखो_orphan_inodes(sbi, start_blk);
		start_blk += orphan_blocks;
	पूर्ण

	f2fs_ग_लिखो_data_summaries(sbi, start_blk);
	start_blk += data_sum_blocks;

	/* Record ग_लिखो statistics in the hot node summary */
	kbytes_written = sbi->kbytes_written;
	kbytes_written += (f2fs_get_sectors_written(sbi) -
				sbi->sectors_written_start) >> 1;
	seg_i->journal->info.kbytes_written = cpu_to_le64(kbytes_written);

	अगर (__reमुख्य_node_summaries(cpc->reason)) अणु
		f2fs_ग_लिखो_node_summaries(sbi, start_blk);
		start_blk += NR_CURSEG_NODE_TYPE;
	पूर्ण

	/* update user_block_counts */
	sbi->last_valid_block_count = sbi->total_valid_block_count;
	percpu_counter_set(&sbi->alloc_valid_block_count, 0);

	/* Here, we have one bio having CP pack except cp pack 2 page */
	f2fs_sync_meta_pages(sbi, META, दीर्घ_उच्च, FS_CP_META_IO);
	/* Wait क्रम all dirty meta pages to be submitted क्रम IO */
	f2fs_रुको_on_all_pages(sbi, F2FS_सूचीTY_META);

	/* रुको क्रम previous submitted meta pages ग_लिखोback */
	f2fs_रुको_on_all_pages(sbi, F2FS_WB_CP_DATA);

	/* flush all device cache */
	err = f2fs_flush_device_cache(sbi);
	अगर (err)
		वापस err;

	/* barrier and flush checkpoपूर्णांक cp pack 2 page अगर it can */
	commit_checkpoपूर्णांक(sbi, ckpt, start_blk);
	f2fs_रुको_on_all_pages(sbi, F2FS_WB_CP_DATA);

	/*
	 * invalidate पूर्णांकermediate page cache borrowed from meta inode which are
	 * used क्रम migration of encrypted, verity or compressed inode's blocks.
	 */
	अगर (f2fs_sb_has_encrypt(sbi) || f2fs_sb_has_verity(sbi) ||
		f2fs_sb_has_compression(sbi))
		invalidate_mapping_pages(META_MAPPING(sbi),
				MAIN_BLKADDR(sbi), MAX_BLKADDR(sbi) - 1);

	f2fs_release_ino_entry(sbi, false);

	f2fs_reset_fsync_node_info(sbi);

	clear_sbi_flag(sbi, SBI_IS_सूचीTY);
	clear_sbi_flag(sbi, SBI_NEED_CP);
	clear_sbi_flag(sbi, SBI_QUOTA_SKIP_FLUSH);

	spin_lock(&sbi->stat_lock);
	sbi->unusable_block_count = 0;
	spin_unlock(&sbi->stat_lock);

	__set_cp_next_pack(sbi);

	/*
	 * redirty superblock अगर metadata like node page or inode cache is
	 * updated during writing checkpoपूर्णांक.
	 */
	अगर (get_pages(sbi, F2FS_सूचीTY_NODES) ||
			get_pages(sbi, F2FS_सूचीTY_IMETA))
		set_sbi_flag(sbi, SBI_IS_सूचीTY);

	f2fs_bug_on(sbi, get_pages(sbi, F2FS_सूचीTY_DENTS));

	वापस unlikely(f2fs_cp_error(sbi)) ? -EIO : 0;
पूर्ण

पूर्णांक f2fs_ग_लिखो_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi, काष्ठा cp_control *cpc)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	अचिन्हित दीर्घ दीर्घ ckpt_ver;
	पूर्णांक err = 0;

	अगर (f2fs_पढ़ोonly(sbi->sb) || f2fs_hw_is_पढ़ोonly(sbi))
		वापस -EROFS;

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) अणु
		अगर (cpc->reason != CP_PAUSE)
			वापस 0;
		f2fs_warn(sbi, "Start checkpoint disabled!");
	पूर्ण
	अगर (cpc->reason != CP_RESIZE)
		करोwn_ग_लिखो(&sbi->cp_global_sem);

	अगर (!is_sbi_flag_set(sbi, SBI_IS_सूचीTY) &&
		((cpc->reason & CP_FASTBOOT) || (cpc->reason & CP_SYNC) ||
		((cpc->reason & CP_DISCARD) && !sbi->discard_blks)))
		जाओ out;
	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	trace_f2fs_ग_लिखो_checkpoपूर्णांक(sbi->sb, cpc->reason, "start block_ops");

	err = block_operations(sbi);
	अगर (err)
		जाओ out;

	trace_f2fs_ग_लिखो_checkpoपूर्णांक(sbi->sb, cpc->reason, "finish block_ops");

	f2fs_flush_merged_ग_लिखोs(sbi);

	/* this is the हाल of multiple fstrims without any changes */
	अगर (cpc->reason & CP_DISCARD) अणु
		अगर (!f2fs_exist_trim_candidates(sbi, cpc)) अणु
			unblock_operations(sbi);
			जाओ out;
		पूर्ण

		अगर (NM_I(sbi)->nat_cnt[सूचीTY_NAT] == 0 &&
				SIT_I(sbi)->dirty_sentries == 0 &&
				preमुक्त_segments(sbi) == 0) अणु
			f2fs_flush_sit_entries(sbi, cpc);
			f2fs_clear_preमुक्त_segments(sbi, cpc);
			unblock_operations(sbi);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * update checkpoपूर्णांक pack index
	 * Increase the version number so that
	 * SIT entries and seg summaries are written at correct place
	 */
	ckpt_ver = cur_cp_version(ckpt);
	ckpt->checkpoपूर्णांक_ver = cpu_to_le64(++ckpt_ver);

	/* ग_लिखो cached NAT/SIT entries to NAT/SIT area */
	err = f2fs_flush_nat_entries(sbi, cpc);
	अगर (err)
		जाओ stop;

	f2fs_flush_sit_entries(sbi, cpc);

	/* save inmem log status */
	f2fs_save_inmem_curseg(sbi);

	err = करो_checkpoपूर्णांक(sbi, cpc);
	अगर (err)
		f2fs_release_discard_addrs(sbi);
	अन्यथा
		f2fs_clear_preमुक्त_segments(sbi, cpc);

	f2fs_restore_inmem_curseg(sbi);
stop:
	unblock_operations(sbi);
	stat_inc_cp_count(sbi->stat_info);

	अगर (cpc->reason & CP_RECOVERY)
		f2fs_notice(sbi, "checkpoint: version = %llx", ckpt_ver);

	/* update CP_TIME to trigger checkpoपूर्णांक periodically */
	f2fs_update_समय(sbi, CP_TIME);
	trace_f2fs_ग_लिखो_checkpoपूर्णांक(sbi->sb, cpc->reason, "finish checkpoint");
out:
	अगर (cpc->reason != CP_RESIZE)
		up_ग_लिखो(&sbi->cp_global_sem);
	वापस err;
पूर्ण

व्योम f2fs_init_ino_entry_info(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_INO_ENTRY; i++) अणु
		काष्ठा inode_management *im = &sbi->im[i];

		INIT_RADIX_TREE(&im->ino_root, GFP_ATOMIC);
		spin_lock_init(&im->ino_lock);
		INIT_LIST_HEAD(&im->ino_list);
		im->ino_num = 0;
	पूर्ण

	sbi->max_orphans = (sbi->blocks_per_seg - F2FS_CP_PACKS -
			NR_CURSEG_PERSIST_TYPE - __cp_payload(sbi)) *
				F2FS_ORPHANS_PER_BLOCK;
पूर्ण

पूर्णांक __init f2fs_create_checkpoपूर्णांक_caches(व्योम)
अणु
	ino_entry_slab = f2fs_kmem_cache_create("f2fs_ino_entry",
			माप(काष्ठा ino_entry));
	अगर (!ino_entry_slab)
		वापस -ENOMEM;
	f2fs_inode_entry_slab = f2fs_kmem_cache_create("f2fs_inode_entry",
			माप(काष्ठा inode_entry));
	अगर (!f2fs_inode_entry_slab) अणु
		kmem_cache_destroy(ino_entry_slab);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम f2fs_destroy_checkpoपूर्णांक_caches(व्योम)
अणु
	kmem_cache_destroy(ino_entry_slab);
	kmem_cache_destroy(f2fs_inode_entry_slab);
पूर्ण

अटल पूर्णांक __ग_लिखो_checkpoपूर्णांक_sync(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा cp_control cpc = अणु .reason = CP_SYNC, पूर्ण;
	पूर्णांक err;

	करोwn_ग_लिखो(&sbi->gc_lock);
	err = f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
	up_ग_लिखो(&sbi->gc_lock);

	वापस err;
पूर्ण

अटल व्योम __checkpoपूर्णांक_and_complete_reqs(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा ckpt_req_control *cprc = &sbi->cprc_info;
	काष्ठा ckpt_req *req, *next;
	काष्ठा llist_node *dispatch_list;
	u64 sum_dअगरf = 0, dअगरf, count = 0;
	पूर्णांक ret;

	dispatch_list = llist_del_all(&cprc->issue_list);
	अगर (!dispatch_list)
		वापस;
	dispatch_list = llist_reverse_order(dispatch_list);

	ret = __ग_लिखो_checkpoपूर्णांक_sync(sbi);
	atomic_inc(&cprc->issued_ckpt);

	llist_क्रम_each_entry_safe(req, next, dispatch_list, llnode) अणु
		dअगरf = (u64)kसमय_ms_delta(kसमय_get(), req->queue_समय);
		req->ret = ret;
		complete(&req->रुको);

		sum_dअगरf += dअगरf;
		count++;
	पूर्ण
	atomic_sub(count, &cprc->queued_ckpt);
	atomic_add(count, &cprc->total_ckpt);

	spin_lock(&cprc->stat_lock);
	cprc->cur_समय = (अचिन्हित पूर्णांक)भाग64_u64(sum_dअगरf, count);
	अगर (cprc->peak_समय < cprc->cur_समय)
		cprc->peak_समय = cprc->cur_समय;
	spin_unlock(&cprc->stat_lock);
पूर्ण

अटल पूर्णांक issue_checkpoपूर्णांक_thपढ़ो(व्योम *data)
अणु
	काष्ठा f2fs_sb_info *sbi = data;
	काष्ठा ckpt_req_control *cprc = &sbi->cprc_info;
	रुको_queue_head_t *q = &cprc->ckpt_रुको_queue;
repeat:
	अगर (kthपढ़ो_should_stop())
		वापस 0;

	अगर (!llist_empty(&cprc->issue_list))
		__checkpoपूर्णांक_and_complete_reqs(sbi);

	रुको_event_पूर्णांकerruptible(*q,
		kthपढ़ो_should_stop() || !llist_empty(&cprc->issue_list));
	जाओ repeat;
पूर्ण

अटल व्योम flush_reमुख्यed_ckpt_reqs(काष्ठा f2fs_sb_info *sbi,
		काष्ठा ckpt_req *रुको_req)
अणु
	काष्ठा ckpt_req_control *cprc = &sbi->cprc_info;

	अगर (!llist_empty(&cprc->issue_list)) अणु
		__checkpoपूर्णांक_and_complete_reqs(sbi);
	पूर्ण अन्यथा अणु
		/* alपढ़ोy dispatched by issue_checkpoपूर्णांक_thपढ़ो */
		अगर (रुको_req)
			रुको_क्रम_completion(&रुको_req->रुको);
	पूर्ण
पूर्ण

अटल व्योम init_ckpt_req(काष्ठा ckpt_req *req)
अणु
	स_रखो(req, 0, माप(काष्ठा ckpt_req));

	init_completion(&req->रुको);
	req->queue_समय = kसमय_get();
पूर्ण

पूर्णांक f2fs_issue_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा ckpt_req_control *cprc = &sbi->cprc_info;
	काष्ठा ckpt_req req;
	काष्ठा cp_control cpc;

	cpc.reason = __get_cp_reason(sbi);
	अगर (!test_opt(sbi, MERGE_CHECKPOINT) || cpc.reason != CP_SYNC) अणु
		पूर्णांक ret;

		करोwn_ग_लिखो(&sbi->gc_lock);
		ret = f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
		up_ग_लिखो(&sbi->gc_lock);

		वापस ret;
	पूर्ण

	अगर (!cprc->f2fs_issue_ckpt)
		वापस __ग_लिखो_checkpoपूर्णांक_sync(sbi);

	init_ckpt_req(&req);

	llist_add(&req.llnode, &cprc->issue_list);
	atomic_inc(&cprc->queued_ckpt);

	/*
	 * update issue_list beक्रमe we wake up issue_checkpoपूर्णांक thपढ़ो,
	 * this smp_mb() pairs with another barrier in ___रुको_event(),
	 * see more details in comments of रुकोqueue_active().
	 */
	smp_mb();

	अगर (रुकोqueue_active(&cprc->ckpt_रुको_queue))
		wake_up(&cprc->ckpt_रुको_queue);

	अगर (cprc->f2fs_issue_ckpt)
		रुको_क्रम_completion(&req.रुको);
	अन्यथा
		flush_reमुख्यed_ckpt_reqs(sbi, &req);

	वापस req.ret;
पूर्ण

पूर्णांक f2fs_start_ckpt_thपढ़ो(काष्ठा f2fs_sb_info *sbi)
अणु
	dev_t dev = sbi->sb->s_bdev->bd_dev;
	काष्ठा ckpt_req_control *cprc = &sbi->cprc_info;

	अगर (cprc->f2fs_issue_ckpt)
		वापस 0;

	cprc->f2fs_issue_ckpt = kthपढ़ो_run(issue_checkpoपूर्णांक_thपढ़ो, sbi,
			"f2fs_ckpt-%u:%u", MAJOR(dev), MINOR(dev));
	अगर (IS_ERR(cprc->f2fs_issue_ckpt)) अणु
		cprc->f2fs_issue_ckpt = शून्य;
		वापस -ENOMEM;
	पूर्ण

	set_task_ioprio(cprc->f2fs_issue_ckpt, cprc->ckpt_thपढ़ो_ioprio);

	वापस 0;
पूर्ण

व्योम f2fs_stop_ckpt_thपढ़ो(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा ckpt_req_control *cprc = &sbi->cprc_info;

	अगर (cprc->f2fs_issue_ckpt) अणु
		काष्ठा task_काष्ठा *ckpt_task = cprc->f2fs_issue_ckpt;

		cprc->f2fs_issue_ckpt = शून्य;
		kthपढ़ो_stop(ckpt_task);

		flush_reमुख्यed_ckpt_reqs(sbi, शून्य);
	पूर्ण
पूर्ण

व्योम f2fs_init_ckpt_req_control(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा ckpt_req_control *cprc = &sbi->cprc_info;

	atomic_set(&cprc->issued_ckpt, 0);
	atomic_set(&cprc->total_ckpt, 0);
	atomic_set(&cprc->queued_ckpt, 0);
	cprc->ckpt_thपढ़ो_ioprio = DEFAULT_CHECKPOINT_IOPRIO;
	init_रुकोqueue_head(&cprc->ckpt_रुको_queue);
	init_llist_head(&cprc->issue_list);
	spin_lock_init(&cprc->stat_lock);
पूर्ण
