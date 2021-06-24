<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/segment.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/swap.h>
#समावेश <linux/समयr.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "f2fs.h"
#समावेश "segment.h"
#समावेश "node.h"
#समावेश "gc.h"
#समावेश <trace/events/f2fs.h>

#घोषणा __reverse_ffz(x) __reverse_ffs(~(x))

अटल काष्ठा kmem_cache *discard_entry_slab;
अटल काष्ठा kmem_cache *discard_cmd_slab;
अटल काष्ठा kmem_cache *sit_entry_set_slab;
अटल काष्ठा kmem_cache *inmem_entry_slab;

अटल अचिन्हित दीर्घ __reverse_uदीर्घ(अचिन्हित अक्षर *str)
अणु
	अचिन्हित दीर्घ पंचांगp = 0;
	पूर्णांक shअगरt = 24, idx = 0;

#अगर BITS_PER_LONG == 64
	shअगरt = 56;
#पूर्ण_अगर
	जबतक (shअगरt >= 0) अणु
		पंचांगp |= (अचिन्हित दीर्घ)str[idx++] << shअगरt;
		shअगरt -= BITS_PER_BYTE;
	पूर्ण
	वापस पंचांगp;
पूर्ण

/*
 * __reverse_ffs is copied from include/यंत्र-generic/bitops/__ffs.h since
 * MSB and LSB are reversed in a byte by f2fs_set_bit.
 */
अटल अंतरभूत अचिन्हित दीर्घ __reverse_ffs(अचिन्हित दीर्घ word)
अणु
	पूर्णांक num = 0;

#अगर BITS_PER_LONG == 64
	अगर ((word & 0xffffffff00000000UL) == 0)
		num += 32;
	अन्यथा
		word >>= 32;
#पूर्ण_अगर
	अगर ((word & 0xffff0000) == 0)
		num += 16;
	अन्यथा
		word >>= 16;

	अगर ((word & 0xff00) == 0)
		num += 8;
	अन्यथा
		word >>= 8;

	अगर ((word & 0xf0) == 0)
		num += 4;
	अन्यथा
		word >>= 4;

	अगर ((word & 0xc) == 0)
		num += 2;
	अन्यथा
		word >>= 2;

	अगर ((word & 0x2) == 0)
		num += 1;
	वापस num;
पूर्ण

/*
 * __find_rev_next(_zero)_bit is copied from lib/find_next_bit.c because
 * f2fs_set_bit makes MSB and LSB reversed in a byte.
 * @size must be पूर्णांकegral बार of अचिन्हित दीर्घ.
 * Example:
 *                             MSB <--> LSB
 *   f2fs_set_bit(0, biपंचांगap) => 1000 0000
 *   f2fs_set_bit(7, biपंचांगap) => 0000 0001
 */
अटल अचिन्हित दीर्घ __find_rev_next_bit(स्थिर अचिन्हित दीर्घ *addr,
			अचिन्हित दीर्घ size, अचिन्हित दीर्घ offset)
अणु
	स्थिर अचिन्हित दीर्घ *p = addr + BIT_WORD(offset);
	अचिन्हित दीर्घ result = size;
	अचिन्हित दीर्घ पंचांगp;

	अगर (offset >= size)
		वापस size;

	size -= (offset & ~(BITS_PER_LONG - 1));
	offset %= BITS_PER_LONG;

	जबतक (1) अणु
		अगर (*p == 0)
			जाओ pass;

		पंचांगp = __reverse_uदीर्घ((अचिन्हित अक्षर *)p);

		पंचांगp &= ~0UL >> offset;
		अगर (size < BITS_PER_LONG)
			पंचांगp &= (~0UL << (BITS_PER_LONG - size));
		अगर (पंचांगp)
			जाओ found;
pass:
		अगर (size <= BITS_PER_LONG)
			अवरोध;
		size -= BITS_PER_LONG;
		offset = 0;
		p++;
	पूर्ण
	वापस result;
found:
	वापस result - size + __reverse_ffs(पंचांगp);
पूर्ण

अटल अचिन्हित दीर्घ __find_rev_next_zero_bit(स्थिर अचिन्हित दीर्घ *addr,
			अचिन्हित दीर्घ size, अचिन्हित दीर्घ offset)
अणु
	स्थिर अचिन्हित दीर्घ *p = addr + BIT_WORD(offset);
	अचिन्हित दीर्घ result = size;
	अचिन्हित दीर्घ पंचांगp;

	अगर (offset >= size)
		वापस size;

	size -= (offset & ~(BITS_PER_LONG - 1));
	offset %= BITS_PER_LONG;

	जबतक (1) अणु
		अगर (*p == ~0UL)
			जाओ pass;

		पंचांगp = __reverse_uदीर्घ((अचिन्हित अक्षर *)p);

		अगर (offset)
			पंचांगp |= ~0UL << (BITS_PER_LONG - offset);
		अगर (size < BITS_PER_LONG)
			पंचांगp |= ~0UL >> size;
		अगर (पंचांगp != ~0UL)
			जाओ found;
pass:
		अगर (size <= BITS_PER_LONG)
			अवरोध;
		size -= BITS_PER_LONG;
		offset = 0;
		p++;
	पूर्ण
	वापस result;
found:
	वापस result - size + __reverse_ffz(पंचांगp);
पूर्ण

bool f2fs_need_SSR(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक node_secs = get_blocktype_secs(sbi, F2FS_सूचीTY_NODES);
	पूर्णांक dent_secs = get_blocktype_secs(sbi, F2FS_सूचीTY_DENTS);
	पूर्णांक imeta_secs = get_blocktype_secs(sbi, F2FS_सूचीTY_IMETA);

	अगर (f2fs_lfs_mode(sbi))
		वापस false;
	अगर (sbi->gc_mode == GC_URGENT_HIGH)
		वापस true;
	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		वापस true;

	वापस मुक्त_sections(sbi) <= (node_secs + 2 * dent_secs + imeta_secs +
			SM_I(sbi)->min_ssr_sections + reserved_sections(sbi));
पूर्ण

व्योम f2fs_रेजिस्टर_inmem_page(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा inmem_pages *new;

	अगर (PagePrivate(page))
		set_page_निजी(page, (अचिन्हित दीर्घ)ATOMIC_WRITTEN_PAGE);
	अन्यथा
		f2fs_set_page_निजी(page, ATOMIC_WRITTEN_PAGE);

	new = f2fs_kmem_cache_alloc(inmem_entry_slab, GFP_NOFS);

	/* add atomic page indices to the list */
	new->page = page;
	INIT_LIST_HEAD(&new->list);

	/* increase reference count with clean state */
	get_page(page);
	mutex_lock(&F2FS_I(inode)->inmem_lock);
	list_add_tail(&new->list, &F2FS_I(inode)->inmem_pages);
	inc_page_count(F2FS_I_SB(inode), F2FS_INMEM_PAGES);
	mutex_unlock(&F2FS_I(inode)->inmem_lock);

	trace_f2fs_रेजिस्टर_inmem_page(page, INMEM);
पूर्ण

अटल पूर्णांक __revoke_inmem_pages(काष्ठा inode *inode,
				काष्ठा list_head *head, bool drop, bool recover,
				bool trylock)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा inmem_pages *cur, *पंचांगp;
	पूर्णांक err = 0;

	list_क्रम_each_entry_safe(cur, पंचांगp, head, list) अणु
		काष्ठा page *page = cur->page;

		अगर (drop)
			trace_f2fs_commit_inmem_page(page, INMEM_DROP);

		अगर (trylock) अणु
			/*
			 * to aव्योम deadlock in between page lock and
			 * inmem_lock.
			 */
			अगर (!trylock_page(page))
				जारी;
		पूर्ण अन्यथा अणु
			lock_page(page);
		पूर्ण

		f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);

		अगर (recover) अणु
			काष्ठा dnode_of_data dn;
			काष्ठा node_info ni;

			trace_f2fs_commit_inmem_page(page, INMEM_REVOKE);
retry:
			set_new_dnode(&dn, inode, शून्य, शून्य, 0);
			err = f2fs_get_dnode_of_data(&dn, page->index,
								LOOKUP_NODE);
			अगर (err) अणु
				अगर (err == -ENOMEM) अणु
					congestion_रुको(BLK_RW_ASYNC,
							DEFAULT_IO_TIMEOUT);
					cond_resched();
					जाओ retry;
				पूर्ण
				err = -EAGAIN;
				जाओ next;
			पूर्ण

			err = f2fs_get_node_info(sbi, dn.nid, &ni);
			अगर (err) अणु
				f2fs_put_dnode(&dn);
				वापस err;
			पूर्ण

			अगर (cur->old_addr == NEW_ADDR) अणु
				f2fs_invalidate_blocks(sbi, dn.data_blkaddr);
				f2fs_update_data_blkaddr(&dn, NEW_ADDR);
			पूर्ण अन्यथा
				f2fs_replace_block(sbi, &dn, dn.data_blkaddr,
					cur->old_addr, ni.version, true, true);
			f2fs_put_dnode(&dn);
		पूर्ण
next:
		/* we करोn't need to invalidate this in the sccessful status */
		अगर (drop || recover) अणु
			ClearPageUptodate(page);
			clear_cold_data(page);
		पूर्ण
		f2fs_clear_page_निजी(page);
		f2fs_put_page(page, 1);

		list_del(&cur->list);
		kmem_cache_मुक्त(inmem_entry_slab, cur);
		dec_page_count(F2FS_I_SB(inode), F2FS_INMEM_PAGES);
	पूर्ण
	वापस err;
पूर्ण

व्योम f2fs_drop_inmem_pages_all(काष्ठा f2fs_sb_info *sbi, bool gc_failure)
अणु
	काष्ठा list_head *head = &sbi->inode_list[ATOMIC_खाता];
	काष्ठा inode *inode;
	काष्ठा f2fs_inode_info *fi;
	अचिन्हित पूर्णांक count = sbi->atomic_files;
	अचिन्हित पूर्णांक looped = 0;
next:
	spin_lock(&sbi->inode_lock[ATOMIC_खाता]);
	अगर (list_empty(head)) अणु
		spin_unlock(&sbi->inode_lock[ATOMIC_खाता]);
		वापस;
	पूर्ण
	fi = list_first_entry(head, काष्ठा f2fs_inode_info, inmem_ilist);
	inode = igrab(&fi->vfs_inode);
	अगर (inode)
		list_move_tail(&fi->inmem_ilist, head);
	spin_unlock(&sbi->inode_lock[ATOMIC_खाता]);

	अगर (inode) अणु
		अगर (gc_failure) अणु
			अगर (!fi->i_gc_failures[GC_FAILURE_ATOMIC])
				जाओ skip;
		पूर्ण
		set_inode_flag(inode, FI_ATOMIC_REVOKE_REQUEST);
		f2fs_drop_inmem_pages(inode);
skip:
		iput(inode);
	पूर्ण
	congestion_रुको(BLK_RW_ASYNC, DEFAULT_IO_TIMEOUT);
	cond_resched();
	अगर (gc_failure) अणु
		अगर (++looped >= count)
			वापस;
	पूर्ण
	जाओ next;
पूर्ण

व्योम f2fs_drop_inmem_pages(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);

	करो अणु
		mutex_lock(&fi->inmem_lock);
		अगर (list_empty(&fi->inmem_pages)) अणु
			fi->i_gc_failures[GC_FAILURE_ATOMIC] = 0;

			spin_lock(&sbi->inode_lock[ATOMIC_खाता]);
			अगर (!list_empty(&fi->inmem_ilist))
				list_del_init(&fi->inmem_ilist);
			अगर (f2fs_is_atomic_file(inode)) अणु
				clear_inode_flag(inode, FI_ATOMIC_खाता);
				sbi->atomic_files--;
			पूर्ण
			spin_unlock(&sbi->inode_lock[ATOMIC_खाता]);

			mutex_unlock(&fi->inmem_lock);
			अवरोध;
		पूर्ण
		__revoke_inmem_pages(inode, &fi->inmem_pages,
						true, false, true);
		mutex_unlock(&fi->inmem_lock);
	पूर्ण जबतक (1);
पूर्ण

व्योम f2fs_drop_inmem_page(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा list_head *head = &fi->inmem_pages;
	काष्ठा inmem_pages *cur = शून्य;

	f2fs_bug_on(sbi, !IS_ATOMIC_WRITTEN_PAGE(page));

	mutex_lock(&fi->inmem_lock);
	list_क्रम_each_entry(cur, head, list) अणु
		अगर (cur->page == page)
			अवरोध;
	पूर्ण

	f2fs_bug_on(sbi, list_empty(head) || cur->page != page);
	list_del(&cur->list);
	mutex_unlock(&fi->inmem_lock);

	dec_page_count(sbi, F2FS_INMEM_PAGES);
	kmem_cache_मुक्त(inmem_entry_slab, cur);

	ClearPageUptodate(page);
	f2fs_clear_page_निजी(page);
	f2fs_put_page(page, 0);

	trace_f2fs_commit_inmem_page(page, INMEM_INVALIDATE);
पूर्ण

अटल पूर्णांक __f2fs_commit_inmem_pages(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा inmem_pages *cur, *पंचांगp;
	काष्ठा f2fs_io_info fio = अणु
		.sbi = sbi,
		.ino = inode->i_ino,
		.type = DATA,
		.op = REQ_OP_WRITE,
		.op_flags = REQ_SYNC | REQ_PRIO,
		.io_type = FS_DATA_IO,
	पूर्ण;
	काष्ठा list_head revoke_list;
	bool submit_bio = false;
	पूर्णांक err = 0;

	INIT_LIST_HEAD(&revoke_list);

	list_क्रम_each_entry_safe(cur, पंचांगp, &fi->inmem_pages, list) अणु
		काष्ठा page *page = cur->page;

		lock_page(page);
		अगर (page->mapping == inode->i_mapping) अणु
			trace_f2fs_commit_inmem_page(page, INMEM);

			f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);

			set_page_dirty(page);
			अगर (clear_page_dirty_क्रम_io(page)) अणु
				inode_dec_dirty_pages(inode);
				f2fs_हटाओ_dirty_inode(inode);
			पूर्ण
retry:
			fio.page = page;
			fio.old_blkaddr = शून्य_ADDR;
			fio.encrypted_page = शून्य;
			fio.need_lock = LOCK_DONE;
			err = f2fs_करो_ग_लिखो_data_page(&fio);
			अगर (err) अणु
				अगर (err == -ENOMEM) अणु
					congestion_रुको(BLK_RW_ASYNC,
							DEFAULT_IO_TIMEOUT);
					cond_resched();
					जाओ retry;
				पूर्ण
				unlock_page(page);
				अवरोध;
			पूर्ण
			/* record old blkaddr क्रम revoking */
			cur->old_addr = fio.old_blkaddr;
			submit_bio = true;
		पूर्ण
		unlock_page(page);
		list_move_tail(&cur->list, &revoke_list);
	पूर्ण

	अगर (submit_bio)
		f2fs_submit_merged_ग_लिखो_cond(sbi, inode, शून्य, 0, DATA);

	अगर (err) अणु
		/*
		 * try to revoke all committed pages, but still we could fail
		 * due to no memory or other reason, अगर that happened, EAGAIN
		 * will be वापसed, which means in such हाल, transaction is
		 * alपढ़ोy not पूर्णांकegrity, caller should use journal to करो the
		 * recovery or reग_लिखो & commit last transaction. For other
		 * error number, revoking was करोne by fileप्रणाली itself.
		 */
		err = __revoke_inmem_pages(inode, &revoke_list,
						false, true, false);

		/* drop all uncommitted pages */
		__revoke_inmem_pages(inode, &fi->inmem_pages,
						true, false, false);
	पूर्ण अन्यथा अणु
		__revoke_inmem_pages(inode, &revoke_list,
						false, false, false);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक f2fs_commit_inmem_pages(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	पूर्णांक err;

	f2fs_balance_fs(sbi, true);

	करोwn_ग_लिखो(&fi->i_gc_rwsem[WRITE]);

	f2fs_lock_op(sbi);
	set_inode_flag(inode, FI_ATOMIC_COMMIT);

	mutex_lock(&fi->inmem_lock);
	err = __f2fs_commit_inmem_pages(inode);
	mutex_unlock(&fi->inmem_lock);

	clear_inode_flag(inode, FI_ATOMIC_COMMIT);

	f2fs_unlock_op(sbi);
	up_ग_लिखो(&fi->i_gc_rwsem[WRITE]);

	वापस err;
पूर्ण

/*
 * This function balances dirty node and dentry pages.
 * In addition, it controls garbage collection.
 */
व्योम f2fs_balance_fs(काष्ठा f2fs_sb_info *sbi, bool need)
अणु
	अगर (समय_प्रकारo_inject(sbi, FAULT_CHECKPOINT)) अणु
		f2fs_show_injection_info(sbi, FAULT_CHECKPOINT);
		f2fs_stop_checkpoपूर्णांक(sbi, false);
	पूर्ण

	/* balance_fs_bg is able to be pending */
	अगर (need && excess_cached_nats(sbi))
		f2fs_balance_fs_bg(sbi, false);

	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस;

	/*
	 * We should करो GC or end up with checkpoपूर्णांक, अगर there are so many dirty
	 * dir/node pages without enough मुक्त segments.
	 */
	अगर (has_not_enough_मुक्त_secs(sbi, 0, 0)) अणु
		अगर (test_opt(sbi, GC_MERGE) && sbi->gc_thपढ़ो &&
					sbi->gc_thपढ़ो->f2fs_gc_task) अणु
			DEFINE_WAIT(रुको);

			prepare_to_रुको(&sbi->gc_thपढ़ो->fggc_wq, &रुको,
						TASK_UNINTERRUPTIBLE);
			wake_up(&sbi->gc_thपढ़ो->gc_रुको_queue_head);
			io_schedule();
			finish_रुको(&sbi->gc_thपढ़ो->fggc_wq, &रुको);
		पूर्ण अन्यथा अणु
			करोwn_ग_लिखो(&sbi->gc_lock);
			f2fs_gc(sbi, false, false, false, शून्य_SEGNO);
		पूर्ण
	पूर्ण
पूर्ण

व्योम f2fs_balance_fs_bg(काष्ठा f2fs_sb_info *sbi, bool from_bg)
अणु
	अगर (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		वापस;

	/* try to shrink extent cache when there is no enough memory */
	अगर (!f2fs_available_मुक्त_memory(sbi, EXTENT_CACHE))
		f2fs_shrink_extent_tree(sbi, EXTENT_CACHE_SHRINK_NUMBER);

	/* check the # of cached NAT entries */
	अगर (!f2fs_available_मुक्त_memory(sbi, NAT_ENTRIES))
		f2fs_try_to_मुक्त_nats(sbi, NAT_ENTRY_PER_BLOCK);

	अगर (!f2fs_available_मुक्त_memory(sbi, FREE_NIDS))
		f2fs_try_to_मुक्त_nids(sbi, MAX_FREE_NIDS);
	अन्यथा
		f2fs_build_मुक्त_nids(sbi, false, false);

	अगर (excess_dirty_nats(sbi) || excess_dirty_nodes(sbi) ||
		excess_preमुक्त_segs(sbi))
		जाओ करो_sync;

	/* there is background inflight IO or क्रमeground operation recently */
	अगर (is_inflight_io(sbi, REQ_TIME) ||
		(!f2fs_समय_over(sbi, REQ_TIME) && rwsem_is_locked(&sbi->cp_rwsem)))
		वापस;

	/* exceed periodical checkpoपूर्णांक समयout threshold */
	अगर (f2fs_समय_over(sbi, CP_TIME))
		जाओ करो_sync;

	/* checkpoपूर्णांक is the only way to shrink partial cached entries */
	अगर (f2fs_available_मुक्त_memory(sbi, NAT_ENTRIES) ||
		f2fs_available_मुक्त_memory(sbi, INO_ENTRIES))
		वापस;

करो_sync:
	अगर (test_opt(sbi, DATA_FLUSH) && from_bg) अणु
		काष्ठा blk_plug plug;

		mutex_lock(&sbi->flush_lock);

		blk_start_plug(&plug);
		f2fs_sync_dirty_inodes(sbi, खाता_INODE);
		blk_finish_plug(&plug);

		mutex_unlock(&sbi->flush_lock);
	पूर्ण
	f2fs_sync_fs(sbi->sb, true);
	stat_inc_bg_cp_count(sbi->stat_info);
पूर्ण

अटल पूर्णांक __submit_flush_रुको(काष्ठा f2fs_sb_info *sbi,
				काष्ठा block_device *bdev)
अणु
	पूर्णांक ret = blkdev_issue_flush(bdev);

	trace_f2fs_issue_flush(bdev, test_opt(sbi, NOBARRIER),
				test_opt(sbi, FLUSH_MERGE), ret);
	वापस ret;
पूर्ण

अटल पूर्णांक submit_flush_रुको(काष्ठा f2fs_sb_info *sbi, nid_t ino)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!f2fs_is_multi_device(sbi))
		वापस __submit_flush_रुको(sbi, sbi->sb->s_bdev);

	क्रम (i = 0; i < sbi->s_ndevs; i++) अणु
		अगर (!f2fs_is_dirty_device(sbi, ino, i, FLUSH_INO))
			जारी;
		ret = __submit_flush_रुको(sbi, FDEV(i).bdev);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक issue_flush_thपढ़ो(व्योम *data)
अणु
	काष्ठा f2fs_sb_info *sbi = data;
	काष्ठा flush_cmd_control *fcc = SM_I(sbi)->fcc_info;
	रुको_queue_head_t *q = &fcc->flush_रुको_queue;
repeat:
	अगर (kthपढ़ो_should_stop())
		वापस 0;

	अगर (!llist_empty(&fcc->issue_list)) अणु
		काष्ठा flush_cmd *cmd, *next;
		पूर्णांक ret;

		fcc->dispatch_list = llist_del_all(&fcc->issue_list);
		fcc->dispatch_list = llist_reverse_order(fcc->dispatch_list);

		cmd = llist_entry(fcc->dispatch_list, काष्ठा flush_cmd, llnode);

		ret = submit_flush_रुको(sbi, cmd->ino);
		atomic_inc(&fcc->issued_flush);

		llist_क्रम_each_entry_safe(cmd, next,
					  fcc->dispatch_list, llnode) अणु
			cmd->ret = ret;
			complete(&cmd->रुको);
		पूर्ण
		fcc->dispatch_list = शून्य;
	पूर्ण

	रुको_event_पूर्णांकerruptible(*q,
		kthपढ़ो_should_stop() || !llist_empty(&fcc->issue_list));
	जाओ repeat;
पूर्ण

पूर्णांक f2fs_issue_flush(काष्ठा f2fs_sb_info *sbi, nid_t ino)
अणु
	काष्ठा flush_cmd_control *fcc = SM_I(sbi)->fcc_info;
	काष्ठा flush_cmd cmd;
	पूर्णांक ret;

	अगर (test_opt(sbi, NOBARRIER))
		वापस 0;

	अगर (!test_opt(sbi, FLUSH_MERGE)) अणु
		atomic_inc(&fcc->queued_flush);
		ret = submit_flush_रुको(sbi, ino);
		atomic_dec(&fcc->queued_flush);
		atomic_inc(&fcc->issued_flush);
		वापस ret;
	पूर्ण

	अगर (atomic_inc_वापस(&fcc->queued_flush) == 1 ||
	    f2fs_is_multi_device(sbi)) अणु
		ret = submit_flush_रुको(sbi, ino);
		atomic_dec(&fcc->queued_flush);

		atomic_inc(&fcc->issued_flush);
		वापस ret;
	पूर्ण

	cmd.ino = ino;
	init_completion(&cmd.रुको);

	llist_add(&cmd.llnode, &fcc->issue_list);

	/*
	 * update issue_list beक्रमe we wake up issue_flush thपढ़ो, this
	 * smp_mb() pairs with another barrier in ___रुको_event(), see
	 * more details in comments of रुकोqueue_active().
	 */
	smp_mb();

	अगर (रुकोqueue_active(&fcc->flush_रुको_queue))
		wake_up(&fcc->flush_रुको_queue);

	अगर (fcc->f2fs_issue_flush) अणु
		रुको_क्रम_completion(&cmd.रुको);
		atomic_dec(&fcc->queued_flush);
	पूर्ण अन्यथा अणु
		काष्ठा llist_node *list;

		list = llist_del_all(&fcc->issue_list);
		अगर (!list) अणु
			रुको_क्रम_completion(&cmd.रुको);
			atomic_dec(&fcc->queued_flush);
		पूर्ण अन्यथा अणु
			काष्ठा flush_cmd *पंचांगp, *next;

			ret = submit_flush_रुको(sbi, ino);

			llist_क्रम_each_entry_safe(पंचांगp, next, list, llnode) अणु
				अगर (पंचांगp == &cmd) अणु
					cmd.ret = ret;
					atomic_dec(&fcc->queued_flush);
					जारी;
				पूर्ण
				पंचांगp->ret = ret;
				complete(&पंचांगp->रुको);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस cmd.ret;
पूर्ण

पूर्णांक f2fs_create_flush_cmd_control(काष्ठा f2fs_sb_info *sbi)
अणु
	dev_t dev = sbi->sb->s_bdev->bd_dev;
	काष्ठा flush_cmd_control *fcc;
	पूर्णांक err = 0;

	अगर (SM_I(sbi)->fcc_info) अणु
		fcc = SM_I(sbi)->fcc_info;
		अगर (fcc->f2fs_issue_flush)
			वापस err;
		जाओ init_thपढ़ो;
	पूर्ण

	fcc = f2fs_kzalloc(sbi, माप(काष्ठा flush_cmd_control), GFP_KERNEL);
	अगर (!fcc)
		वापस -ENOMEM;
	atomic_set(&fcc->issued_flush, 0);
	atomic_set(&fcc->queued_flush, 0);
	init_रुकोqueue_head(&fcc->flush_रुको_queue);
	init_llist_head(&fcc->issue_list);
	SM_I(sbi)->fcc_info = fcc;
	अगर (!test_opt(sbi, FLUSH_MERGE))
		वापस err;

init_thपढ़ो:
	fcc->f2fs_issue_flush = kthपढ़ो_run(issue_flush_thपढ़ो, sbi,
				"f2fs_flush-%u:%u", MAJOR(dev), MINOR(dev));
	अगर (IS_ERR(fcc->f2fs_issue_flush)) अणु
		err = PTR_ERR(fcc->f2fs_issue_flush);
		kमुक्त(fcc);
		SM_I(sbi)->fcc_info = शून्य;
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

व्योम f2fs_destroy_flush_cmd_control(काष्ठा f2fs_sb_info *sbi, bool मुक्त)
अणु
	काष्ठा flush_cmd_control *fcc = SM_I(sbi)->fcc_info;

	अगर (fcc && fcc->f2fs_issue_flush) अणु
		काष्ठा task_काष्ठा *flush_thपढ़ो = fcc->f2fs_issue_flush;

		fcc->f2fs_issue_flush = शून्य;
		kthपढ़ो_stop(flush_thपढ़ो);
	पूर्ण
	अगर (मुक्त) अणु
		kमुक्त(fcc);
		SM_I(sbi)->fcc_info = शून्य;
	पूर्ण
पूर्ण

पूर्णांक f2fs_flush_device_cache(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक ret = 0, i;

	अगर (!f2fs_is_multi_device(sbi))
		वापस 0;

	अगर (test_opt(sbi, NOBARRIER))
		वापस 0;

	क्रम (i = 1; i < sbi->s_ndevs; i++) अणु
		अगर (!f2fs_test_bit(i, (अक्षर *)&sbi->dirty_device))
			जारी;
		ret = __submit_flush_रुको(sbi, FDEV(i).bdev);
		अगर (ret)
			अवरोध;

		spin_lock(&sbi->dev_lock);
		f2fs_clear_bit(i, (अक्षर *)&sbi->dirty_device);
		spin_unlock(&sbi->dev_lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __locate_dirty_segment(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno,
		क्रमागत dirty_type dirty_type)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);

	/* need not be added */
	अगर (IS_CURSEG(sbi, segno))
		वापस;

	अगर (!test_and_set_bit(segno, dirty_i->dirty_segmap[dirty_type]))
		dirty_i->nr_dirty[dirty_type]++;

	अगर (dirty_type == सूचीTY) अणु
		काष्ठा seg_entry *sentry = get_seg_entry(sbi, segno);
		क्रमागत dirty_type t = sentry->type;

		अगर (unlikely(t >= सूचीTY)) अणु
			f2fs_bug_on(sbi, 1);
			वापस;
		पूर्ण
		अगर (!test_and_set_bit(segno, dirty_i->dirty_segmap[t]))
			dirty_i->nr_dirty[t]++;

		अगर (__is_large_section(sbi)) अणु
			अचिन्हित पूर्णांक secno = GET_SEC_FROM_SEG(sbi, segno);
			block_t valid_blocks =
				get_valid_blocks(sbi, segno, true);

			f2fs_bug_on(sbi, unlikely(!valid_blocks ||
					valid_blocks == BLKS_PER_SEC(sbi)));

			अगर (!IS_CURSEC(sbi, secno))
				set_bit(secno, dirty_i->dirty_secmap);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __हटाओ_dirty_segment(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno,
		क्रमागत dirty_type dirty_type)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	block_t valid_blocks;

	अगर (test_and_clear_bit(segno, dirty_i->dirty_segmap[dirty_type]))
		dirty_i->nr_dirty[dirty_type]--;

	अगर (dirty_type == सूचीTY) अणु
		काष्ठा seg_entry *sentry = get_seg_entry(sbi, segno);
		क्रमागत dirty_type t = sentry->type;

		अगर (test_and_clear_bit(segno, dirty_i->dirty_segmap[t]))
			dirty_i->nr_dirty[t]--;

		valid_blocks = get_valid_blocks(sbi, segno, true);
		अगर (valid_blocks == 0) अणु
			clear_bit(GET_SEC_FROM_SEG(sbi, segno),
						dirty_i->victim_secmap);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
			clear_bit(segno, SIT_I(sbi)->invalid_segmap);
#पूर्ण_अगर
		पूर्ण
		अगर (__is_large_section(sbi)) अणु
			अचिन्हित पूर्णांक secno = GET_SEC_FROM_SEG(sbi, segno);

			अगर (!valid_blocks ||
					valid_blocks == BLKS_PER_SEC(sbi)) अणु
				clear_bit(secno, dirty_i->dirty_secmap);
				वापस;
			पूर्ण

			अगर (!IS_CURSEC(sbi, secno))
				set_bit(secno, dirty_i->dirty_secmap);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Should not occur error such as -ENOMEM.
 * Adding dirty entry पूर्णांकo seglist is not critical operation.
 * If a given segment is one of current working segments, it won't be added.
 */
अटल व्योम locate_dirty_segment(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	अचिन्हित लघु valid_blocks, ckpt_valid_blocks;
	अचिन्हित पूर्णांक usable_blocks;

	अगर (segno == शून्य_SEGNO || IS_CURSEG(sbi, segno))
		वापस;

	usable_blocks = f2fs_usable_blks_in_seg(sbi, segno);
	mutex_lock(&dirty_i->seglist_lock);

	valid_blocks = get_valid_blocks(sbi, segno, false);
	ckpt_valid_blocks = get_ckpt_valid_blocks(sbi, segno, false);

	अगर (valid_blocks == 0 && (!is_sbi_flag_set(sbi, SBI_CP_DISABLED) ||
		ckpt_valid_blocks == usable_blocks)) अणु
		__locate_dirty_segment(sbi, segno, PRE);
		__हटाओ_dirty_segment(sbi, segno, सूचीTY);
	पूर्ण अन्यथा अगर (valid_blocks < usable_blocks) अणु
		__locate_dirty_segment(sbi, segno, सूचीTY);
	पूर्ण अन्यथा अणु
		/* Recovery routine with SSR needs this */
		__हटाओ_dirty_segment(sbi, segno, सूचीTY);
	पूर्ण

	mutex_unlock(&dirty_i->seglist_lock);
पूर्ण

/* This moves currently empty dirty blocks to preमुक्त. Must hold seglist_lock */
व्योम f2fs_dirty_to_preमुक्त(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	अचिन्हित पूर्णांक segno;

	mutex_lock(&dirty_i->seglist_lock);
	क्रम_each_set_bit(segno, dirty_i->dirty_segmap[सूचीTY], MAIN_SEGS(sbi)) अणु
		अगर (get_valid_blocks(sbi, segno, false))
			जारी;
		अगर (IS_CURSEG(sbi, segno))
			जारी;
		__locate_dirty_segment(sbi, segno, PRE);
		__हटाओ_dirty_segment(sbi, segno, सूचीTY);
	पूर्ण
	mutex_unlock(&dirty_i->seglist_lock);
पूर्ण

block_t f2fs_get_unusable_blocks(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक ovp_hole_segs =
		(overprovision_segments(sbi) - reserved_segments(sbi));
	block_t ovp_holes = ovp_hole_segs << sbi->log_blocks_per_seg;
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	block_t holes[2] = अणु0, 0पूर्ण;	/* DATA and NODE */
	block_t unusable;
	काष्ठा seg_entry *se;
	अचिन्हित पूर्णांक segno;

	mutex_lock(&dirty_i->seglist_lock);
	क्रम_each_set_bit(segno, dirty_i->dirty_segmap[सूचीTY], MAIN_SEGS(sbi)) अणु
		se = get_seg_entry(sbi, segno);
		अगर (IS_NODESEG(se->type))
			holes[NODE] += f2fs_usable_blks_in_seg(sbi, segno) -
							se->valid_blocks;
		अन्यथा
			holes[DATA] += f2fs_usable_blks_in_seg(sbi, segno) -
							se->valid_blocks;
	पूर्ण
	mutex_unlock(&dirty_i->seglist_lock);

	unusable = holes[DATA] > holes[NODE] ? holes[DATA] : holes[NODE];
	अगर (unusable > ovp_holes)
		वापस unusable - ovp_holes;
	वापस 0;
पूर्ण

पूर्णांक f2fs_disable_cp_again(काष्ठा f2fs_sb_info *sbi, block_t unusable)
अणु
	पूर्णांक ovp_hole_segs =
		(overprovision_segments(sbi) - reserved_segments(sbi));
	अगर (unusable > F2FS_OPTION(sbi).unusable_cap)
		वापस -EAGAIN;
	अगर (is_sbi_flag_set(sbi, SBI_CP_DISABLED_QUICK) &&
		dirty_segments(sbi) > ovp_hole_segs)
		वापस -EAGAIN;
	वापस 0;
पूर्ण

/* This is only used by SBI_CP_DISABLED */
अटल अचिन्हित पूर्णांक get_मुक्त_segment(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	अचिन्हित पूर्णांक segno = 0;

	mutex_lock(&dirty_i->seglist_lock);
	क्रम_each_set_bit(segno, dirty_i->dirty_segmap[सूचीTY], MAIN_SEGS(sbi)) अणु
		अगर (get_valid_blocks(sbi, segno, false))
			जारी;
		अगर (get_ckpt_valid_blocks(sbi, segno, false))
			जारी;
		mutex_unlock(&dirty_i->seglist_lock);
		वापस segno;
	पूर्ण
	mutex_unlock(&dirty_i->seglist_lock);
	वापस शून्य_SEGNO;
पूर्ण

अटल काष्ठा discard_cmd *__create_discard_cmd(काष्ठा f2fs_sb_info *sbi,
		काष्ठा block_device *bdev, block_t lstart,
		block_t start, block_t len)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा list_head *pend_list;
	काष्ठा discard_cmd *dc;

	f2fs_bug_on(sbi, !len);

	pend_list = &dcc->pend_list[plist_idx(len)];

	dc = f2fs_kmem_cache_alloc(discard_cmd_slab, GFP_NOFS);
	INIT_LIST_HEAD(&dc->list);
	dc->bdev = bdev;
	dc->lstart = lstart;
	dc->start = start;
	dc->len = len;
	dc->ref = 0;
	dc->state = D_PREP;
	dc->queued = 0;
	dc->error = 0;
	init_completion(&dc->रुको);
	list_add_tail(&dc->list, pend_list);
	spin_lock_init(&dc->lock);
	dc->bio_ref = 0;
	atomic_inc(&dcc->discard_cmd_cnt);
	dcc->undiscard_blks += len;

	वापस dc;
पूर्ण

अटल काष्ठा discard_cmd *__attach_discard_cmd(काष्ठा f2fs_sb_info *sbi,
				काष्ठा block_device *bdev, block_t lstart,
				block_t start, block_t len,
				काष्ठा rb_node *parent, काष्ठा rb_node **p,
				bool lefपंचांगost)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा discard_cmd *dc;

	dc = __create_discard_cmd(sbi, bdev, lstart, start, len);

	rb_link_node(&dc->rb_node, parent, p);
	rb_insert_color_cached(&dc->rb_node, &dcc->root, lefपंचांगost);

	वापस dc;
पूर्ण

अटल व्योम __detach_discard_cmd(काष्ठा discard_cmd_control *dcc,
							काष्ठा discard_cmd *dc)
अणु
	अगर (dc->state == D_DONE)
		atomic_sub(dc->queued, &dcc->queued_discard);

	list_del(&dc->list);
	rb_erase_cached(&dc->rb_node, &dcc->root);
	dcc->undiscard_blks -= dc->len;

	kmem_cache_मुक्त(discard_cmd_slab, dc);

	atomic_dec(&dcc->discard_cmd_cnt);
पूर्ण

अटल व्योम __हटाओ_discard_cmd(काष्ठा f2fs_sb_info *sbi,
							काष्ठा discard_cmd *dc)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	अचिन्हित दीर्घ flags;

	trace_f2fs_हटाओ_discard(dc->bdev, dc->start, dc->len);

	spin_lock_irqsave(&dc->lock, flags);
	अगर (dc->bio_ref) अणु
		spin_unlock_irqrestore(&dc->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&dc->lock, flags);

	f2fs_bug_on(sbi, dc->ref);

	अगर (dc->error == -EOPNOTSUPP)
		dc->error = 0;

	अगर (dc->error)
		prपूर्णांकk_ratelimited(
			"%sF2FS-fs (%s): Issue discard(%u, %u, %u) failed, ret: %d",
			KERN_INFO, sbi->sb->s_id,
			dc->lstart, dc->start, dc->len, dc->error);
	__detach_discard_cmd(dcc, dc);
पूर्ण

अटल व्योम f2fs_submit_discard_endio(काष्ठा bio *bio)
अणु
	काष्ठा discard_cmd *dc = (काष्ठा discard_cmd *)bio->bi_निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dc->lock, flags);
	अगर (!dc->error)
		dc->error = blk_status_to_त्रुटि_सं(bio->bi_status);
	dc->bio_ref--;
	अगर (!dc->bio_ref && dc->state == D_SUBMIT) अणु
		dc->state = D_DONE;
		complete_all(&dc->रुको);
	पूर्ण
	spin_unlock_irqrestore(&dc->lock, flags);
	bio_put(bio);
पूर्ण

अटल व्योम __check_sit_biपंचांगap(काष्ठा f2fs_sb_info *sbi,
				block_t start, block_t end)
अणु
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	काष्ठा seg_entry *sentry;
	अचिन्हित पूर्णांक segno;
	block_t blk = start;
	अचिन्हित दीर्घ offset, size, max_blocks = sbi->blocks_per_seg;
	अचिन्हित दीर्घ *map;

	जबतक (blk < end) अणु
		segno = GET_SEGNO(sbi, blk);
		sentry = get_seg_entry(sbi, segno);
		offset = GET_BLKOFF_FROM_SEG0(sbi, blk);

		अगर (end < START_BLOCK(sbi, segno + 1))
			size = GET_BLKOFF_FROM_SEG0(sbi, end);
		अन्यथा
			size = max_blocks;
		map = (अचिन्हित दीर्घ *)(sentry->cur_valid_map);
		offset = __find_rev_next_bit(map, size, offset);
		f2fs_bug_on(sbi, offset != size);
		blk = START_BLOCK(sbi, segno + 1);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init_discard_policy(काष्ठा f2fs_sb_info *sbi,
				काष्ठा discard_policy *dpolicy,
				पूर्णांक discard_type, अचिन्हित पूर्णांक granularity)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;

	/* common policy */
	dpolicy->type = discard_type;
	dpolicy->sync = true;
	dpolicy->ordered = false;
	dpolicy->granularity = granularity;

	dpolicy->max_requests = DEF_MAX_DISCARD_REQUEST;
	dpolicy->io_aware_gran = MAX_PLIST_NUM;
	dpolicy->समयout = false;

	अगर (discard_type == DPOLICY_BG) अणु
		dpolicy->min_पूर्णांकerval = DEF_MIN_DISCARD_ISSUE_TIME;
		dpolicy->mid_पूर्णांकerval = DEF_MID_DISCARD_ISSUE_TIME;
		dpolicy->max_पूर्णांकerval = DEF_MAX_DISCARD_ISSUE_TIME;
		dpolicy->io_aware = true;
		dpolicy->sync = false;
		dpolicy->ordered = true;
		अगर (utilization(sbi) > DEF_DISCARD_URGENT_UTIL) अणु
			dpolicy->granularity = 1;
			अगर (atomic_पढ़ो(&dcc->discard_cmd_cnt))
				dpolicy->max_पूर्णांकerval =
					DEF_MIN_DISCARD_ISSUE_TIME;
		पूर्ण
	पूर्ण अन्यथा अगर (discard_type == DPOLICY_FORCE) अणु
		dpolicy->min_पूर्णांकerval = DEF_MIN_DISCARD_ISSUE_TIME;
		dpolicy->mid_पूर्णांकerval = DEF_MID_DISCARD_ISSUE_TIME;
		dpolicy->max_पूर्णांकerval = DEF_MAX_DISCARD_ISSUE_TIME;
		dpolicy->io_aware = false;
	पूर्ण अन्यथा अगर (discard_type == DPOLICY_FSTRIM) अणु
		dpolicy->io_aware = false;
	पूर्ण अन्यथा अगर (discard_type == DPOLICY_UMOUNT) अणु
		dpolicy->io_aware = false;
		/* we need to issue all to keep CP_TRIMMED_FLAG */
		dpolicy->granularity = 1;
		dpolicy->समयout = true;
	पूर्ण
पूर्ण

अटल व्योम __update_discard_tree_range(काष्ठा f2fs_sb_info *sbi,
				काष्ठा block_device *bdev, block_t lstart,
				block_t start, block_t len);
/* this function is copied from blkdev_issue_discard from block/blk-lib.c */
अटल पूर्णांक __submit_discard_cmd(काष्ठा f2fs_sb_info *sbi,
						काष्ठा discard_policy *dpolicy,
						काष्ठा discard_cmd *dc,
						अचिन्हित पूर्णांक *issued)
अणु
	काष्ठा block_device *bdev = dc->bdev;
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	अचिन्हित पूर्णांक max_discard_blocks =
			SECTOR_TO_BLOCK(q->limits.max_discard_sectors);
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा list_head *रुको_list = (dpolicy->type == DPOLICY_FSTRIM) ?
					&(dcc->fstrim_list) : &(dcc->रुको_list);
	पूर्णांक flag = dpolicy->sync ? REQ_SYNC : 0;
	block_t lstart, start, len, total_len;
	पूर्णांक err = 0;

	अगर (dc->state != D_PREP)
		वापस 0;

	अगर (is_sbi_flag_set(sbi, SBI_NEED_FSCK))
		वापस 0;

	trace_f2fs_issue_discard(bdev, dc->start, dc->len);

	lstart = dc->lstart;
	start = dc->start;
	len = dc->len;
	total_len = len;

	dc->len = 0;

	जबतक (total_len && *issued < dpolicy->max_requests && !err) अणु
		काष्ठा bio *bio = शून्य;
		अचिन्हित दीर्घ flags;
		bool last = true;

		अगर (len > max_discard_blocks) अणु
			len = max_discard_blocks;
			last = false;
		पूर्ण

		(*issued)++;
		अगर (*issued == dpolicy->max_requests)
			last = true;

		dc->len += len;

		अगर (समय_प्रकारo_inject(sbi, FAULT_DISCARD)) अणु
			f2fs_show_injection_info(sbi, FAULT_DISCARD);
			err = -EIO;
			जाओ submit;
		पूर्ण
		err = __blkdev_issue_discard(bdev,
					SECTOR_FROM_BLOCK(start),
					SECTOR_FROM_BLOCK(len),
					GFP_NOFS, 0, &bio);
submit:
		अगर (err) अणु
			spin_lock_irqsave(&dc->lock, flags);
			अगर (dc->state == D_PARTIAL)
				dc->state = D_SUBMIT;
			spin_unlock_irqrestore(&dc->lock, flags);

			अवरोध;
		पूर्ण

		f2fs_bug_on(sbi, !bio);

		/*
		 * should keep beक्रमe submission to aव्योम D_DONE
		 * right away
		 */
		spin_lock_irqsave(&dc->lock, flags);
		अगर (last)
			dc->state = D_SUBMIT;
		अन्यथा
			dc->state = D_PARTIAL;
		dc->bio_ref++;
		spin_unlock_irqrestore(&dc->lock, flags);

		atomic_inc(&dcc->queued_discard);
		dc->queued++;
		list_move_tail(&dc->list, रुको_list);

		/* sanity check on discard range */
		__check_sit_biपंचांगap(sbi, lstart, lstart + len);

		bio->bi_निजी = dc;
		bio->bi_end_io = f2fs_submit_discard_endio;
		bio->bi_opf |= flag;
		submit_bio(bio);

		atomic_inc(&dcc->issued_discard);

		f2fs_update_iostat(sbi, FS_DISCARD, 1);

		lstart += len;
		start += len;
		total_len -= len;
		len = total_len;
	पूर्ण

	अगर (!err && len) अणु
		dcc->undiscard_blks -= len;
		__update_discard_tree_range(sbi, bdev, lstart, start, len);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम __insert_discard_tree(काष्ठा f2fs_sb_info *sbi,
				काष्ठा block_device *bdev, block_t lstart,
				block_t start, block_t len,
				काष्ठा rb_node **insert_p,
				काष्ठा rb_node *insert_parent)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	bool lefपंचांगost = true;

	अगर (insert_p && insert_parent) अणु
		parent = insert_parent;
		p = insert_p;
		जाओ करो_insert;
	पूर्ण

	p = f2fs_lookup_rb_tree_क्रम_insert(sbi, &dcc->root, &parent,
							lstart, &lefपंचांगost);
करो_insert:
	__attach_discard_cmd(sbi, bdev, lstart, start, len, parent,
								p, lefपंचांगost);
पूर्ण

अटल व्योम __relocate_discard_cmd(काष्ठा discard_cmd_control *dcc,
						काष्ठा discard_cmd *dc)
अणु
	list_move_tail(&dc->list, &dcc->pend_list[plist_idx(dc->len)]);
पूर्ण

अटल व्योम __punch_discard_cmd(काष्ठा f2fs_sb_info *sbi,
				काष्ठा discard_cmd *dc, block_t blkaddr)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा discard_info di = dc->di;
	bool modअगरied = false;

	अगर (dc->state == D_DONE || dc->len == 1) अणु
		__हटाओ_discard_cmd(sbi, dc);
		वापस;
	पूर्ण

	dcc->undiscard_blks -= di.len;

	अगर (blkaddr > di.lstart) अणु
		dc->len = blkaddr - dc->lstart;
		dcc->undiscard_blks += dc->len;
		__relocate_discard_cmd(dcc, dc);
		modअगरied = true;
	पूर्ण

	अगर (blkaddr < di.lstart + di.len - 1) अणु
		अगर (modअगरied) अणु
			__insert_discard_tree(sbi, dc->bdev, blkaddr + 1,
					di.start + blkaddr + 1 - di.lstart,
					di.lstart + di.len - 1 - blkaddr,
					शून्य, शून्य);
		पूर्ण अन्यथा अणु
			dc->lstart++;
			dc->len--;
			dc->start++;
			dcc->undiscard_blks += dc->len;
			__relocate_discard_cmd(dcc, dc);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __update_discard_tree_range(काष्ठा f2fs_sb_info *sbi,
				काष्ठा block_device *bdev, block_t lstart,
				block_t start, block_t len)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा discard_cmd *prev_dc = शून्य, *next_dc = शून्य;
	काष्ठा discard_cmd *dc;
	काष्ठा discard_info di = अणु0पूर्ण;
	काष्ठा rb_node **insert_p = शून्य, *insert_parent = शून्य;
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	अचिन्हित पूर्णांक max_discard_blocks =
			SECTOR_TO_BLOCK(q->limits.max_discard_sectors);
	block_t end = lstart + len;

	dc = (काष्ठा discard_cmd *)f2fs_lookup_rb_tree_ret(&dcc->root,
					शून्य, lstart,
					(काष्ठा rb_entry **)&prev_dc,
					(काष्ठा rb_entry **)&next_dc,
					&insert_p, &insert_parent, true, शून्य);
	अगर (dc)
		prev_dc = dc;

	अगर (!prev_dc) अणु
		di.lstart = lstart;
		di.len = next_dc ? next_dc->lstart - lstart : len;
		di.len = min(di.len, len);
		di.start = start;
	पूर्ण

	जबतक (1) अणु
		काष्ठा rb_node *node;
		bool merged = false;
		काष्ठा discard_cmd *tdc = शून्य;

		अगर (prev_dc) अणु
			di.lstart = prev_dc->lstart + prev_dc->len;
			अगर (di.lstart < lstart)
				di.lstart = lstart;
			अगर (di.lstart >= end)
				अवरोध;

			अगर (!next_dc || next_dc->lstart > end)
				di.len = end - di.lstart;
			अन्यथा
				di.len = next_dc->lstart - di.lstart;
			di.start = start + di.lstart - lstart;
		पूर्ण

		अगर (!di.len)
			जाओ next;

		अगर (prev_dc && prev_dc->state == D_PREP &&
			prev_dc->bdev == bdev &&
			__is_discard_back_mergeable(&di, &prev_dc->di,
							max_discard_blocks)) अणु
			prev_dc->di.len += di.len;
			dcc->undiscard_blks += di.len;
			__relocate_discard_cmd(dcc, prev_dc);
			di = prev_dc->di;
			tdc = prev_dc;
			merged = true;
		पूर्ण

		अगर (next_dc && next_dc->state == D_PREP &&
			next_dc->bdev == bdev &&
			__is_discard_front_mergeable(&di, &next_dc->di,
							max_discard_blocks)) अणु
			next_dc->di.lstart = di.lstart;
			next_dc->di.len += di.len;
			next_dc->di.start = di.start;
			dcc->undiscard_blks += di.len;
			__relocate_discard_cmd(dcc, next_dc);
			अगर (tdc)
				__हटाओ_discard_cmd(sbi, tdc);
			merged = true;
		पूर्ण

		अगर (!merged) अणु
			__insert_discard_tree(sbi, bdev, di.lstart, di.start,
							di.len, शून्य, शून्य);
		पूर्ण
 next:
		prev_dc = next_dc;
		अगर (!prev_dc)
			अवरोध;

		node = rb_next(&prev_dc->rb_node);
		next_dc = rb_entry_safe(node, काष्ठा discard_cmd, rb_node);
	पूर्ण
पूर्ण

अटल पूर्णांक __queue_discard_cmd(काष्ठा f2fs_sb_info *sbi,
		काष्ठा block_device *bdev, block_t blkstart, block_t blklen)
अणु
	block_t lblkstart = blkstart;

	अगर (!f2fs_bdev_support_discard(bdev))
		वापस 0;

	trace_f2fs_queue_discard(bdev, blkstart, blklen);

	अगर (f2fs_is_multi_device(sbi)) अणु
		पूर्णांक devi = f2fs_target_device_index(sbi, blkstart);

		blkstart -= FDEV(devi).start_blk;
	पूर्ण
	mutex_lock(&SM_I(sbi)->dcc_info->cmd_lock);
	__update_discard_tree_range(sbi, bdev, lblkstart, blkstart, blklen);
	mutex_unlock(&SM_I(sbi)->dcc_info->cmd_lock);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक __issue_discard_cmd_orderly(काष्ठा f2fs_sb_info *sbi,
					काष्ठा discard_policy *dpolicy)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा discard_cmd *prev_dc = शून्य, *next_dc = शून्य;
	काष्ठा rb_node **insert_p = शून्य, *insert_parent = शून्य;
	काष्ठा discard_cmd *dc;
	काष्ठा blk_plug plug;
	अचिन्हित पूर्णांक pos = dcc->next_pos;
	अचिन्हित पूर्णांक issued = 0;
	bool io_पूर्णांकerrupted = false;

	mutex_lock(&dcc->cmd_lock);
	dc = (काष्ठा discard_cmd *)f2fs_lookup_rb_tree_ret(&dcc->root,
					शून्य, pos,
					(काष्ठा rb_entry **)&prev_dc,
					(काष्ठा rb_entry **)&next_dc,
					&insert_p, &insert_parent, true, शून्य);
	अगर (!dc)
		dc = next_dc;

	blk_start_plug(&plug);

	जबतक (dc) अणु
		काष्ठा rb_node *node;
		पूर्णांक err = 0;

		अगर (dc->state != D_PREP)
			जाओ next;

		अगर (dpolicy->io_aware && !is_idle(sbi, DISCARD_TIME)) अणु
			io_पूर्णांकerrupted = true;
			अवरोध;
		पूर्ण

		dcc->next_pos = dc->lstart + dc->len;
		err = __submit_discard_cmd(sbi, dpolicy, dc, &issued);

		अगर (issued >= dpolicy->max_requests)
			अवरोध;
next:
		node = rb_next(&dc->rb_node);
		अगर (err)
			__हटाओ_discard_cmd(sbi, dc);
		dc = rb_entry_safe(node, काष्ठा discard_cmd, rb_node);
	पूर्ण

	blk_finish_plug(&plug);

	अगर (!dc)
		dcc->next_pos = 0;

	mutex_unlock(&dcc->cmd_lock);

	अगर (!issued && io_पूर्णांकerrupted)
		issued = -1;

	वापस issued;
पूर्ण
अटल अचिन्हित पूर्णांक __रुको_all_discard_cmd(काष्ठा f2fs_sb_info *sbi,
					काष्ठा discard_policy *dpolicy);

अटल पूर्णांक __issue_discard_cmd(काष्ठा f2fs_sb_info *sbi,
					काष्ठा discard_policy *dpolicy)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा list_head *pend_list;
	काष्ठा discard_cmd *dc, *पंचांगp;
	काष्ठा blk_plug plug;
	पूर्णांक i, issued;
	bool io_पूर्णांकerrupted = false;

	अगर (dpolicy->समयout)
		f2fs_update_समय(sbi, UMOUNT_DISCARD_TIMEOUT);

retry:
	issued = 0;
	क्रम (i = MAX_PLIST_NUM - 1; i >= 0; i--) अणु
		अगर (dpolicy->समयout &&
				f2fs_समय_over(sbi, UMOUNT_DISCARD_TIMEOUT))
			अवरोध;

		अगर (i + 1 < dpolicy->granularity)
			अवरोध;

		अगर (i < DEFAULT_DISCARD_GRANULARITY && dpolicy->ordered)
			वापस __issue_discard_cmd_orderly(sbi, dpolicy);

		pend_list = &dcc->pend_list[i];

		mutex_lock(&dcc->cmd_lock);
		अगर (list_empty(pend_list))
			जाओ next;
		अगर (unlikely(dcc->rbtree_check))
			f2fs_bug_on(sbi, !f2fs_check_rb_tree_consistence(sbi,
							&dcc->root, false));
		blk_start_plug(&plug);
		list_क्रम_each_entry_safe(dc, पंचांगp, pend_list, list) अणु
			f2fs_bug_on(sbi, dc->state != D_PREP);

			अगर (dpolicy->समयout &&
				f2fs_समय_over(sbi, UMOUNT_DISCARD_TIMEOUT))
				अवरोध;

			अगर (dpolicy->io_aware && i < dpolicy->io_aware_gran &&
						!is_idle(sbi, DISCARD_TIME)) अणु
				io_पूर्णांकerrupted = true;
				अवरोध;
			पूर्ण

			__submit_discard_cmd(sbi, dpolicy, dc, &issued);

			अगर (issued >= dpolicy->max_requests)
				अवरोध;
		पूर्ण
		blk_finish_plug(&plug);
next:
		mutex_unlock(&dcc->cmd_lock);

		अगर (issued >= dpolicy->max_requests || io_पूर्णांकerrupted)
			अवरोध;
	पूर्ण

	अगर (dpolicy->type == DPOLICY_UMOUNT && issued) अणु
		__रुको_all_discard_cmd(sbi, dpolicy);
		जाओ retry;
	पूर्ण

	अगर (!issued && io_पूर्णांकerrupted)
		issued = -1;

	वापस issued;
पूर्ण

अटल bool __drop_discard_cmd(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा list_head *pend_list;
	काष्ठा discard_cmd *dc, *पंचांगp;
	पूर्णांक i;
	bool dropped = false;

	mutex_lock(&dcc->cmd_lock);
	क्रम (i = MAX_PLIST_NUM - 1; i >= 0; i--) अणु
		pend_list = &dcc->pend_list[i];
		list_क्रम_each_entry_safe(dc, पंचांगp, pend_list, list) अणु
			f2fs_bug_on(sbi, dc->state != D_PREP);
			__हटाओ_discard_cmd(sbi, dc);
			dropped = true;
		पूर्ण
	पूर्ण
	mutex_unlock(&dcc->cmd_lock);

	वापस dropped;
पूर्ण

व्योम f2fs_drop_discard_cmd(काष्ठा f2fs_sb_info *sbi)
अणु
	__drop_discard_cmd(sbi);
पूर्ण

अटल अचिन्हित पूर्णांक __रुको_one_discard_bio(काष्ठा f2fs_sb_info *sbi,
							काष्ठा discard_cmd *dc)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	अचिन्हित पूर्णांक len = 0;

	रुको_क्रम_completion_io(&dc->रुको);
	mutex_lock(&dcc->cmd_lock);
	f2fs_bug_on(sbi, dc->state != D_DONE);
	dc->ref--;
	अगर (!dc->ref) अणु
		अगर (!dc->error)
			len = dc->len;
		__हटाओ_discard_cmd(sbi, dc);
	पूर्ण
	mutex_unlock(&dcc->cmd_lock);

	वापस len;
पूर्ण

अटल अचिन्हित पूर्णांक __रुको_discard_cmd_range(काष्ठा f2fs_sb_info *sbi,
						काष्ठा discard_policy *dpolicy,
						block_t start, block_t end)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा list_head *रुको_list = (dpolicy->type == DPOLICY_FSTRIM) ?
					&(dcc->fstrim_list) : &(dcc->रुको_list);
	काष्ठा discard_cmd *dc, *पंचांगp;
	bool need_रुको;
	अचिन्हित पूर्णांक trimmed = 0;

next:
	need_रुको = false;

	mutex_lock(&dcc->cmd_lock);
	list_क्रम_each_entry_safe(dc, पंचांगp, रुको_list, list) अणु
		अगर (dc->lstart + dc->len <= start || end <= dc->lstart)
			जारी;
		अगर (dc->len < dpolicy->granularity)
			जारी;
		अगर (dc->state == D_DONE && !dc->ref) अणु
			रुको_क्रम_completion_io(&dc->रुको);
			अगर (!dc->error)
				trimmed += dc->len;
			__हटाओ_discard_cmd(sbi, dc);
		पूर्ण अन्यथा अणु
			dc->ref++;
			need_रुको = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&dcc->cmd_lock);

	अगर (need_रुको) अणु
		trimmed += __रुको_one_discard_bio(sbi, dc);
		जाओ next;
	पूर्ण

	वापस trimmed;
पूर्ण

अटल अचिन्हित पूर्णांक __रुको_all_discard_cmd(काष्ठा f2fs_sb_info *sbi,
						काष्ठा discard_policy *dpolicy)
अणु
	काष्ठा discard_policy dp;
	अचिन्हित पूर्णांक discard_blks;

	अगर (dpolicy)
		वापस __रुको_discard_cmd_range(sbi, dpolicy, 0, अच_पूर्णांक_उच्च);

	/* रुको all */
	__init_discard_policy(sbi, &dp, DPOLICY_FSTRIM, 1);
	discard_blks = __रुको_discard_cmd_range(sbi, &dp, 0, अच_पूर्णांक_उच्च);
	__init_discard_policy(sbi, &dp, DPOLICY_UMOUNT, 1);
	discard_blks += __रुको_discard_cmd_range(sbi, &dp, 0, अच_पूर्णांक_उच्च);

	वापस discard_blks;
पूर्ण

/* This should be covered by global mutex, &sit_i->sentry_lock */
अटल व्योम f2fs_रुको_discard_bio(काष्ठा f2fs_sb_info *sbi, block_t blkaddr)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा discard_cmd *dc;
	bool need_रुको = false;

	mutex_lock(&dcc->cmd_lock);
	dc = (काष्ठा discard_cmd *)f2fs_lookup_rb_tree(&dcc->root,
							शून्य, blkaddr);
	अगर (dc) अणु
		अगर (dc->state == D_PREP) अणु
			__punch_discard_cmd(sbi, dc, blkaddr);
		पूर्ण अन्यथा अणु
			dc->ref++;
			need_रुको = true;
		पूर्ण
	पूर्ण
	mutex_unlock(&dcc->cmd_lock);

	अगर (need_रुको)
		__रुको_one_discard_bio(sbi, dc);
पूर्ण

व्योम f2fs_stop_discard_thपढ़ो(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;

	अगर (dcc && dcc->f2fs_issue_discard) अणु
		काष्ठा task_काष्ठा *discard_thपढ़ो = dcc->f2fs_issue_discard;

		dcc->f2fs_issue_discard = शून्य;
		kthपढ़ो_stop(discard_thपढ़ो);
	पूर्ण
पूर्ण

/* This comes from f2fs_put_super */
bool f2fs_issue_discard_समयout(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा discard_policy dpolicy;
	bool dropped;

	__init_discard_policy(sbi, &dpolicy, DPOLICY_UMOUNT,
					dcc->discard_granularity);
	__issue_discard_cmd(sbi, &dpolicy);
	dropped = __drop_discard_cmd(sbi);

	/* just to make sure there is no pending discard commands */
	__रुको_all_discard_cmd(sbi, शून्य);

	f2fs_bug_on(sbi, atomic_पढ़ो(&dcc->discard_cmd_cnt));
	वापस dropped;
पूर्ण

अटल पूर्णांक issue_discard_thपढ़ो(व्योम *data)
अणु
	काष्ठा f2fs_sb_info *sbi = data;
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	रुको_queue_head_t *q = &dcc->discard_रुको_queue;
	काष्ठा discard_policy dpolicy;
	अचिन्हित पूर्णांक रुको_ms = DEF_MIN_DISCARD_ISSUE_TIME;
	पूर्णांक issued;

	set_मुक्तzable();

	करो अणु
		अगर (sbi->gc_mode == GC_URGENT_HIGH ||
			!f2fs_available_मुक्त_memory(sbi, DISCARD_CACHE))
			__init_discard_policy(sbi, &dpolicy, DPOLICY_FORCE, 1);
		अन्यथा
			__init_discard_policy(sbi, &dpolicy, DPOLICY_BG,
						dcc->discard_granularity);

		अगर (!atomic_पढ़ो(&dcc->discard_cmd_cnt))
		       रुको_ms = dpolicy.max_पूर्णांकerval;

		रुको_event_पूर्णांकerruptible_समयout(*q,
				kthपढ़ो_should_stop() || मुक्तzing(current) ||
				dcc->discard_wake,
				msecs_to_jअगरfies(रुको_ms));

		अगर (dcc->discard_wake)
			dcc->discard_wake = 0;

		/* clean up pending candidates beक्रमe going to sleep */
		अगर (atomic_पढ़ो(&dcc->queued_discard))
			__रुको_all_discard_cmd(sbi, शून्य);

		अगर (try_to_मुक्तze())
			जारी;
		अगर (f2fs_पढ़ोonly(sbi->sb))
			जारी;
		अगर (kthपढ़ो_should_stop())
			वापस 0;
		अगर (is_sbi_flag_set(sbi, SBI_NEED_FSCK)) अणु
			रुको_ms = dpolicy.max_पूर्णांकerval;
			जारी;
		पूर्ण
		अगर (!atomic_पढ़ो(&dcc->discard_cmd_cnt))
			जारी;

		sb_start_पूर्णांकग_लिखो(sbi->sb);

		issued = __issue_discard_cmd(sbi, &dpolicy);
		अगर (issued > 0) अणु
			__रुको_all_discard_cmd(sbi, &dpolicy);
			रुको_ms = dpolicy.min_पूर्णांकerval;
		पूर्ण अन्यथा अगर (issued == -1) अणु
			रुको_ms = f2fs_समय_प्रकारo_रुको(sbi, DISCARD_TIME);
			अगर (!रुको_ms)
				रुको_ms = dpolicy.mid_पूर्णांकerval;
		पूर्ण अन्यथा अणु
			रुको_ms = dpolicy.max_पूर्णांकerval;
		पूर्ण

		sb_end_पूर्णांकग_लिखो(sbi->sb);

	पूर्ण जबतक (!kthपढ़ो_should_stop());
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED
अटल पूर्णांक __f2fs_issue_discard_zone(काष्ठा f2fs_sb_info *sbi,
		काष्ठा block_device *bdev, block_t blkstart, block_t blklen)
अणु
	sector_t sector, nr_sects;
	block_t lblkstart = blkstart;
	पूर्णांक devi = 0;

	अगर (f2fs_is_multi_device(sbi)) अणु
		devi = f2fs_target_device_index(sbi, blkstart);
		अगर (blkstart < FDEV(devi).start_blk ||
		    blkstart > FDEV(devi).end_blk) अणु
			f2fs_err(sbi, "Invalid block %x", blkstart);
			वापस -EIO;
		पूर्ण
		blkstart -= FDEV(devi).start_blk;
	पूर्ण

	/* For sequential zones, reset the zone ग_लिखो poपूर्णांकer */
	अगर (f2fs_blkz_is_seq(sbi, devi, blkstart)) अणु
		sector = SECTOR_FROM_BLOCK(blkstart);
		nr_sects = SECTOR_FROM_BLOCK(blklen);

		अगर (sector & (bdev_zone_sectors(bdev) - 1) ||
				nr_sects != bdev_zone_sectors(bdev)) अणु
			f2fs_err(sbi, "(%d) %s: Unaligned zone reset attempted (block %x + %x)",
				 devi, sbi->s_ndevs ? FDEV(devi).path : "",
				 blkstart, blklen);
			वापस -EIO;
		पूर्ण
		trace_f2fs_issue_reset_zone(bdev, blkstart);
		वापस blkdev_zone_mgmt(bdev, REQ_OP_ZONE_RESET,
					sector, nr_sects, GFP_NOFS);
	पूर्ण

	/* For conventional zones, use regular discard अगर supported */
	वापस __queue_discard_cmd(sbi, bdev, lblkstart, blklen);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __issue_discard_async(काष्ठा f2fs_sb_info *sbi,
		काष्ठा block_device *bdev, block_t blkstart, block_t blklen)
अणु
#अगर_घोषित CONFIG_BLK_DEV_ZONED
	अगर (f2fs_sb_has_blkzoned(sbi) && bdev_is_zoned(bdev))
		वापस __f2fs_issue_discard_zone(sbi, bdev, blkstart, blklen);
#पूर्ण_अगर
	वापस __queue_discard_cmd(sbi, bdev, blkstart, blklen);
पूर्ण

अटल पूर्णांक f2fs_issue_discard(काष्ठा f2fs_sb_info *sbi,
				block_t blkstart, block_t blklen)
अणु
	sector_t start = blkstart, len = 0;
	काष्ठा block_device *bdev;
	काष्ठा seg_entry *se;
	अचिन्हित पूर्णांक offset;
	block_t i;
	पूर्णांक err = 0;

	bdev = f2fs_target_device(sbi, blkstart, शून्य);

	क्रम (i = blkstart; i < blkstart + blklen; i++, len++) अणु
		अगर (i != start) अणु
			काष्ठा block_device *bdev2 =
				f2fs_target_device(sbi, i, शून्य);

			अगर (bdev2 != bdev) अणु
				err = __issue_discard_async(sbi, bdev,
						start, len);
				अगर (err)
					वापस err;
				bdev = bdev2;
				start = i;
				len = 0;
			पूर्ण
		पूर्ण

		se = get_seg_entry(sbi, GET_SEGNO(sbi, i));
		offset = GET_BLKOFF_FROM_SEG0(sbi, i);

		अगर (!f2fs_test_and_set_bit(offset, se->discard_map))
			sbi->discard_blks--;
	पूर्ण

	अगर (len)
		err = __issue_discard_async(sbi, bdev, start, len);
	वापस err;
पूर्ण

अटल bool add_discard_addrs(काष्ठा f2fs_sb_info *sbi, काष्ठा cp_control *cpc,
							bool check_only)
अणु
	पूर्णांक entries = SIT_VBLOCK_MAP_SIZE / माप(अचिन्हित दीर्घ);
	पूर्णांक max_blocks = sbi->blocks_per_seg;
	काष्ठा seg_entry *se = get_seg_entry(sbi, cpc->trim_start);
	अचिन्हित दीर्घ *cur_map = (अचिन्हित दीर्घ *)se->cur_valid_map;
	अचिन्हित दीर्घ *ckpt_map = (अचिन्हित दीर्घ *)se->ckpt_valid_map;
	अचिन्हित दीर्घ *discard_map = (अचिन्हित दीर्घ *)se->discard_map;
	अचिन्हित दीर्घ *dmap = SIT_I(sbi)->पंचांगp_map;
	अचिन्हित पूर्णांक start = 0, end = -1;
	bool क्रमce = (cpc->reason & CP_DISCARD);
	काष्ठा discard_entry *de = शून्य;
	काष्ठा list_head *head = &SM_I(sbi)->dcc_info->entry_list;
	पूर्णांक i;

	अगर (se->valid_blocks == max_blocks || !f2fs_hw_support_discard(sbi))
		वापस false;

	अगर (!क्रमce) अणु
		अगर (!f2fs_realसमय_discard_enable(sbi) || !se->valid_blocks ||
			SM_I(sbi)->dcc_info->nr_discards >=
				SM_I(sbi)->dcc_info->max_discards)
			वापस false;
	पूर्ण

	/* SIT_VBLOCK_MAP_SIZE should be multiple of माप(अचिन्हित दीर्घ) */
	क्रम (i = 0; i < entries; i++)
		dmap[i] = क्रमce ? ~ckpt_map[i] & ~discard_map[i] :
				(cur_map[i] ^ ckpt_map[i]) & ckpt_map[i];

	जबतक (क्रमce || SM_I(sbi)->dcc_info->nr_discards <=
				SM_I(sbi)->dcc_info->max_discards) अणु
		start = __find_rev_next_bit(dmap, max_blocks, end + 1);
		अगर (start >= max_blocks)
			अवरोध;

		end = __find_rev_next_zero_bit(dmap, max_blocks, start + 1);
		अगर (क्रमce && start && end != max_blocks
					&& (end - start) < cpc->trim_minlen)
			जारी;

		अगर (check_only)
			वापस true;

		अगर (!de) अणु
			de = f2fs_kmem_cache_alloc(discard_entry_slab,
								GFP_F2FS_ZERO);
			de->start_blkaddr = START_BLOCK(sbi, cpc->trim_start);
			list_add_tail(&de->list, head);
		पूर्ण

		क्रम (i = start; i < end; i++)
			__set_bit_le(i, (व्योम *)de->discard_map);

		SM_I(sbi)->dcc_info->nr_discards += end - start;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम release_discard_addr(काष्ठा discard_entry *entry)
अणु
	list_del(&entry->list);
	kmem_cache_मुक्त(discard_entry_slab, entry);
पूर्ण

व्योम f2fs_release_discard_addrs(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा list_head *head = &(SM_I(sbi)->dcc_info->entry_list);
	काष्ठा discard_entry *entry, *this;

	/* drop caches */
	list_क्रम_each_entry_safe(entry, this, head, list)
		release_discard_addr(entry);
पूर्ण

/*
 * Should call f2fs_clear_preमुक्त_segments after checkpoपूर्णांक is करोne.
 */
अटल व्योम set_preमुक्त_as_मुक्त_segments(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	अचिन्हित पूर्णांक segno;

	mutex_lock(&dirty_i->seglist_lock);
	क्रम_each_set_bit(segno, dirty_i->dirty_segmap[PRE], MAIN_SEGS(sbi))
		__set_test_and_मुक्त(sbi, segno, false);
	mutex_unlock(&dirty_i->seglist_lock);
पूर्ण

व्योम f2fs_clear_preमुक्त_segments(काष्ठा f2fs_sb_info *sbi,
						काष्ठा cp_control *cpc)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा list_head *head = &dcc->entry_list;
	काष्ठा discard_entry *entry, *this;
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	अचिन्हित दीर्घ *preमुक्त_map = dirty_i->dirty_segmap[PRE];
	अचिन्हित पूर्णांक start = 0, end = -1;
	अचिन्हित पूर्णांक secno, start_segno;
	bool क्रमce = (cpc->reason & CP_DISCARD);
	bool need_align = f2fs_lfs_mode(sbi) && __is_large_section(sbi);

	mutex_lock(&dirty_i->seglist_lock);

	जबतक (1) अणु
		पूर्णांक i;

		अगर (need_align && end != -1)
			end--;
		start = find_next_bit(preमुक्त_map, MAIN_SEGS(sbi), end + 1);
		अगर (start >= MAIN_SEGS(sbi))
			अवरोध;
		end = find_next_zero_bit(preमुक्त_map, MAIN_SEGS(sbi),
								start + 1);

		अगर (need_align) अणु
			start = roundकरोwn(start, sbi->segs_per_sec);
			end = roundup(end, sbi->segs_per_sec);
		पूर्ण

		क्रम (i = start; i < end; i++) अणु
			अगर (test_and_clear_bit(i, preमुक्त_map))
				dirty_i->nr_dirty[PRE]--;
		पूर्ण

		अगर (!f2fs_realसमय_discard_enable(sbi))
			जारी;

		अगर (क्रमce && start >= cpc->trim_start &&
					(end - 1) <= cpc->trim_end)
				जारी;

		अगर (!f2fs_lfs_mode(sbi) || !__is_large_section(sbi)) अणु
			f2fs_issue_discard(sbi, START_BLOCK(sbi, start),
				(end - start) << sbi->log_blocks_per_seg);
			जारी;
		पूर्ण
next:
		secno = GET_SEC_FROM_SEG(sbi, start);
		start_segno = GET_SEG_FROM_SEC(sbi, secno);
		अगर (!IS_CURSEC(sbi, secno) &&
			!get_valid_blocks(sbi, start, true))
			f2fs_issue_discard(sbi, START_BLOCK(sbi, start_segno),
				sbi->segs_per_sec << sbi->log_blocks_per_seg);

		start = start_segno + sbi->segs_per_sec;
		अगर (start < end)
			जाओ next;
		अन्यथा
			end = start - 1;
	पूर्ण
	mutex_unlock(&dirty_i->seglist_lock);

	/* send small discards */
	list_क्रम_each_entry_safe(entry, this, head, list) अणु
		अचिन्हित पूर्णांक cur_pos = 0, next_pos, len, total_len = 0;
		bool is_valid = test_bit_le(0, entry->discard_map);

find_next:
		अगर (is_valid) अणु
			next_pos = find_next_zero_bit_le(entry->discard_map,
					sbi->blocks_per_seg, cur_pos);
			len = next_pos - cur_pos;

			अगर (f2fs_sb_has_blkzoned(sbi) ||
			    (क्रमce && len < cpc->trim_minlen))
				जाओ skip;

			f2fs_issue_discard(sbi, entry->start_blkaddr + cur_pos,
									len);
			total_len += len;
		पूर्ण अन्यथा अणु
			next_pos = find_next_bit_le(entry->discard_map,
					sbi->blocks_per_seg, cur_pos);
		पूर्ण
skip:
		cur_pos = next_pos;
		is_valid = !is_valid;

		अगर (cur_pos < sbi->blocks_per_seg)
			जाओ find_next;

		release_discard_addr(entry);
		dcc->nr_discards -= total_len;
	पूर्ण

	wake_up_discard_thपढ़ो(sbi, false);
पूर्ण

अटल पूर्णांक create_discard_cmd_control(काष्ठा f2fs_sb_info *sbi)
अणु
	dev_t dev = sbi->sb->s_bdev->bd_dev;
	काष्ठा discard_cmd_control *dcc;
	पूर्णांक err = 0, i;

	अगर (SM_I(sbi)->dcc_info) अणु
		dcc = SM_I(sbi)->dcc_info;
		जाओ init_thपढ़ो;
	पूर्ण

	dcc = f2fs_kzalloc(sbi, माप(काष्ठा discard_cmd_control), GFP_KERNEL);
	अगर (!dcc)
		वापस -ENOMEM;

	dcc->discard_granularity = DEFAULT_DISCARD_GRANULARITY;
	INIT_LIST_HEAD(&dcc->entry_list);
	क्रम (i = 0; i < MAX_PLIST_NUM; i++)
		INIT_LIST_HEAD(&dcc->pend_list[i]);
	INIT_LIST_HEAD(&dcc->रुको_list);
	INIT_LIST_HEAD(&dcc->fstrim_list);
	mutex_init(&dcc->cmd_lock);
	atomic_set(&dcc->issued_discard, 0);
	atomic_set(&dcc->queued_discard, 0);
	atomic_set(&dcc->discard_cmd_cnt, 0);
	dcc->nr_discards = 0;
	dcc->max_discards = MAIN_SEGS(sbi) << sbi->log_blocks_per_seg;
	dcc->undiscard_blks = 0;
	dcc->next_pos = 0;
	dcc->root = RB_ROOT_CACHED;
	dcc->rbtree_check = false;

	init_रुकोqueue_head(&dcc->discard_रुको_queue);
	SM_I(sbi)->dcc_info = dcc;
init_thपढ़ो:
	dcc->f2fs_issue_discard = kthपढ़ो_run(issue_discard_thपढ़ो, sbi,
				"f2fs_discard-%u:%u", MAJOR(dev), MINOR(dev));
	अगर (IS_ERR(dcc->f2fs_issue_discard)) अणु
		err = PTR_ERR(dcc->f2fs_issue_discard);
		kमुक्त(dcc);
		SM_I(sbi)->dcc_info = शून्य;
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम destroy_discard_cmd_control(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;

	अगर (!dcc)
		वापस;

	f2fs_stop_discard_thपढ़ो(sbi);

	/*
	 * Recovery can cache discard commands, so in error path of
	 * fill_super(), it needs to give a chance to handle them.
	 */
	अगर (unlikely(atomic_पढ़ो(&dcc->discard_cmd_cnt)))
		f2fs_issue_discard_समयout(sbi);

	kमुक्त(dcc);
	SM_I(sbi)->dcc_info = शून्य;
पूर्ण

अटल bool __mark_sit_entry_dirty(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);

	अगर (!__test_and_set_bit(segno, sit_i->dirty_sentries_biपंचांगap)) अणु
		sit_i->dirty_sentries++;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम __set_sit_entry_type(काष्ठा f2fs_sb_info *sbi, पूर्णांक type,
					अचिन्हित पूर्णांक segno, पूर्णांक modअगरied)
अणु
	काष्ठा seg_entry *se = get_seg_entry(sbi, segno);

	se->type = type;
	अगर (modअगरied)
		__mark_sit_entry_dirty(sbi, segno);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ get_segment_mसमय(काष्ठा f2fs_sb_info *sbi,
								block_t blkaddr)
अणु
	अचिन्हित पूर्णांक segno = GET_SEGNO(sbi, blkaddr);

	अगर (segno == शून्य_SEGNO)
		वापस 0;
	वापस get_seg_entry(sbi, segno)->mसमय;
पूर्ण

अटल व्योम update_segment_mसमय(काष्ठा f2fs_sb_info *sbi, block_t blkaddr,
						अचिन्हित दीर्घ दीर्घ old_mसमय)
अणु
	काष्ठा seg_entry *se;
	अचिन्हित पूर्णांक segno = GET_SEGNO(sbi, blkaddr);
	अचिन्हित दीर्घ दीर्घ स_समय = get_mसमय(sbi, false);
	अचिन्हित दीर्घ दीर्घ mसमय = old_mसमय ? old_mसमय : स_समय;

	अगर (segno == शून्य_SEGNO)
		वापस;

	se = get_seg_entry(sbi, segno);

	अगर (!se->mसमय)
		se->mसमय = mसमय;
	अन्यथा
		se->mसमय = भाग_u64(se->mसमय * se->valid_blocks + mसमय,
						se->valid_blocks + 1);

	अगर (स_समय > SIT_I(sbi)->max_mसमय)
		SIT_I(sbi)->max_mसमय = स_समय;
पूर्ण

अटल व्योम update_sit_entry(काष्ठा f2fs_sb_info *sbi, block_t blkaddr, पूर्णांक del)
अणु
	काष्ठा seg_entry *se;
	अचिन्हित पूर्णांक segno, offset;
	दीर्घ पूर्णांक new_vblocks;
	bool exist;
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	bool mir_exist;
#पूर्ण_अगर

	segno = GET_SEGNO(sbi, blkaddr);

	se = get_seg_entry(sbi, segno);
	new_vblocks = se->valid_blocks + del;
	offset = GET_BLKOFF_FROM_SEG0(sbi, blkaddr);

	f2fs_bug_on(sbi, (new_vblocks < 0 ||
			(new_vblocks > f2fs_usable_blks_in_seg(sbi, segno))));

	se->valid_blocks = new_vblocks;

	/* Update valid block biपंचांगap */
	अगर (del > 0) अणु
		exist = f2fs_test_and_set_bit(offset, se->cur_valid_map);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
		mir_exist = f2fs_test_and_set_bit(offset,
						se->cur_valid_map_mir);
		अगर (unlikely(exist != mir_exist)) अणु
			f2fs_err(sbi, "Inconsistent error when setting bitmap, blk:%u, old bit:%d",
				 blkaddr, exist);
			f2fs_bug_on(sbi, 1);
		पूर्ण
#पूर्ण_अगर
		अगर (unlikely(exist)) अणु
			f2fs_err(sbi, "Bitmap was wrongly set, blk:%u",
				 blkaddr);
			f2fs_bug_on(sbi, 1);
			se->valid_blocks--;
			del = 0;
		पूर्ण

		अगर (!f2fs_test_and_set_bit(offset, se->discard_map))
			sbi->discard_blks--;

		/*
		 * SSR should never reuse block which is checkpoपूर्णांकed
		 * or newly invalidated.
		 */
		अगर (!is_sbi_flag_set(sbi, SBI_CP_DISABLED)) अणु
			अगर (!f2fs_test_and_set_bit(offset, se->ckpt_valid_map))
				se->ckpt_valid_blocks++;
		पूर्ण
	पूर्ण अन्यथा अणु
		exist = f2fs_test_and_clear_bit(offset, se->cur_valid_map);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
		mir_exist = f2fs_test_and_clear_bit(offset,
						se->cur_valid_map_mir);
		अगर (unlikely(exist != mir_exist)) अणु
			f2fs_err(sbi, "Inconsistent error when clearing bitmap, blk:%u, old bit:%d",
				 blkaddr, exist);
			f2fs_bug_on(sbi, 1);
		पूर्ण
#पूर्ण_अगर
		अगर (unlikely(!exist)) अणु
			f2fs_err(sbi, "Bitmap was wrongly cleared, blk:%u",
				 blkaddr);
			f2fs_bug_on(sbi, 1);
			se->valid_blocks++;
			del = 0;
		पूर्ण अन्यथा अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) अणु
			/*
			 * If checkpoपूर्णांकs are off, we must not reuse data that
			 * was used in the previous checkpoपूर्णांक. If it was used
			 * beक्रमe, we must track that to know how much space we
			 * really have.
			 */
			अगर (f2fs_test_bit(offset, se->ckpt_valid_map)) अणु
				spin_lock(&sbi->stat_lock);
				sbi->unusable_block_count++;
				spin_unlock(&sbi->stat_lock);
			पूर्ण
		पूर्ण

		अगर (f2fs_test_and_clear_bit(offset, se->discard_map))
			sbi->discard_blks++;
	पूर्ण
	अगर (!f2fs_test_bit(offset, se->ckpt_valid_map))
		se->ckpt_valid_blocks += del;

	__mark_sit_entry_dirty(sbi, segno);

	/* update total number of valid blocks to be written in ckpt area */
	SIT_I(sbi)->written_valid_blocks += del;

	अगर (__is_large_section(sbi))
		get_sec_entry(sbi, segno)->valid_blocks += del;
पूर्ण

व्योम f2fs_invalidate_blocks(काष्ठा f2fs_sb_info *sbi, block_t addr)
अणु
	अचिन्हित पूर्णांक segno = GET_SEGNO(sbi, addr);
	काष्ठा sit_info *sit_i = SIT_I(sbi);

	f2fs_bug_on(sbi, addr == शून्य_ADDR);
	अगर (addr == NEW_ADDR || addr == COMPRESS_ADDR)
		वापस;

	invalidate_mapping_pages(META_MAPPING(sbi), addr, addr);

	/* add it पूर्णांकo sit मुख्य buffer */
	करोwn_ग_लिखो(&sit_i->sentry_lock);

	update_segment_mसमय(sbi, addr, 0);
	update_sit_entry(sbi, addr, -1);

	/* add it पूर्णांकo dirty seglist */
	locate_dirty_segment(sbi, segno);

	up_ग_लिखो(&sit_i->sentry_lock);
पूर्ण

bool f2fs_is_checkpoपूर्णांकed_data(काष्ठा f2fs_sb_info *sbi, block_t blkaddr)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	अचिन्हित पूर्णांक segno, offset;
	काष्ठा seg_entry *se;
	bool is_cp = false;

	अगर (!__is_valid_data_blkaddr(blkaddr))
		वापस true;

	करोwn_पढ़ो(&sit_i->sentry_lock);

	segno = GET_SEGNO(sbi, blkaddr);
	se = get_seg_entry(sbi, segno);
	offset = GET_BLKOFF_FROM_SEG0(sbi, blkaddr);

	अगर (f2fs_test_bit(offset, se->ckpt_valid_map))
		is_cp = true;

	up_पढ़ो(&sit_i->sentry_lock);

	वापस is_cp;
पूर्ण

/*
 * This function should be resided under the curseg_mutex lock
 */
अटल व्योम __add_sum_entry(काष्ठा f2fs_sb_info *sbi, पूर्णांक type,
					काष्ठा f2fs_summary *sum)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	व्योम *addr = curseg->sum_blk;

	addr += curseg->next_blkoff * माप(काष्ठा f2fs_summary);
	स_नकल(addr, sum, माप(काष्ठा f2fs_summary));
पूर्ण

/*
 * Calculate the number of current summary pages क्रम writing
 */
पूर्णांक f2fs_npages_क्रम_summary_flush(काष्ठा f2fs_sb_info *sbi, bool क्रम_ra)
अणु
	पूर्णांक valid_sum_count = 0;
	पूर्णांक i, sum_in_page;

	क्रम (i = CURSEG_HOT_DATA; i <= CURSEG_COLD_DATA; i++) अणु
		अगर (sbi->ckpt->alloc_type[i] == SSR)
			valid_sum_count += sbi->blocks_per_seg;
		अन्यथा अणु
			अगर (क्रम_ra)
				valid_sum_count += le16_to_cpu(
					F2FS_CKPT(sbi)->cur_data_blkoff[i]);
			अन्यथा
				valid_sum_count += curseg_blkoff(sbi, i);
		पूर्ण
	पूर्ण

	sum_in_page = (PAGE_SIZE - 2 * SUM_JOURNAL_SIZE -
			SUM_FOOTER_SIZE) / SUMMARY_SIZE;
	अगर (valid_sum_count <= sum_in_page)
		वापस 1;
	अन्यथा अगर ((valid_sum_count - sum_in_page) <=
		(PAGE_SIZE - SUM_FOOTER_SIZE) / SUMMARY_SIZE)
		वापस 2;
	वापस 3;
पूर्ण

/*
 * Caller should put this summary page
 */
काष्ठा page *f2fs_get_sum_page(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno)
अणु
	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस ERR_PTR(-EIO);
	वापस f2fs_get_meta_page_retry(sbi, GET_SUM_BLOCK(sbi, segno));
पूर्ण

व्योम f2fs_update_meta_page(काष्ठा f2fs_sb_info *sbi,
					व्योम *src, block_t blk_addr)
अणु
	काष्ठा page *page = f2fs_grab_meta_page(sbi, blk_addr);

	स_नकल(page_address(page), src, PAGE_SIZE);
	set_page_dirty(page);
	f2fs_put_page(page, 1);
पूर्ण

अटल व्योम ग_लिखो_sum_page(काष्ठा f2fs_sb_info *sbi,
			काष्ठा f2fs_summary_block *sum_blk, block_t blk_addr)
अणु
	f2fs_update_meta_page(sbi, (व्योम *)sum_blk, blk_addr);
पूर्ण

अटल व्योम ग_लिखो_current_sum_page(काष्ठा f2fs_sb_info *sbi,
						पूर्णांक type, block_t blk_addr)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	काष्ठा page *page = f2fs_grab_meta_page(sbi, blk_addr);
	काष्ठा f2fs_summary_block *src = curseg->sum_blk;
	काष्ठा f2fs_summary_block *dst;

	dst = (काष्ठा f2fs_summary_block *)page_address(page);
	स_रखो(dst, 0, PAGE_SIZE);

	mutex_lock(&curseg->curseg_mutex);

	करोwn_पढ़ो(&curseg->journal_rwsem);
	स_नकल(&dst->journal, curseg->journal, SUM_JOURNAL_SIZE);
	up_पढ़ो(&curseg->journal_rwsem);

	स_नकल(dst->entries, src->entries, SUM_ENTRY_SIZE);
	स_नकल(&dst->footer, &src->footer, SUM_FOOTER_SIZE);

	mutex_unlock(&curseg->curseg_mutex);

	set_page_dirty(page);
	f2fs_put_page(page, 1);
पूर्ण

अटल पूर्णांक is_next_segment_मुक्त(काष्ठा f2fs_sb_info *sbi,
				काष्ठा curseg_info *curseg, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक segno = curseg->segno + 1;
	काष्ठा मुक्त_segmap_info *मुक्त_i = FREE_I(sbi);

	अगर (segno < MAIN_SEGS(sbi) && segno % sbi->segs_per_sec)
		वापस !test_bit(segno, मुक्त_i->मुक्त_segmap);
	वापस 0;
पूर्ण

/*
 * Find a new segment from the मुक्त segments biपंचांगap to right order
 * This function should be वापसed with success, otherwise BUG
 */
अटल व्योम get_new_segment(काष्ठा f2fs_sb_info *sbi,
			अचिन्हित पूर्णांक *newseg, bool new_sec, पूर्णांक dir)
अणु
	काष्ठा मुक्त_segmap_info *मुक्त_i = FREE_I(sbi);
	अचिन्हित पूर्णांक segno, secno, zoneno;
	अचिन्हित पूर्णांक total_zones = MAIN_SECS(sbi) / sbi->secs_per_zone;
	अचिन्हित पूर्णांक hपूर्णांक = GET_SEC_FROM_SEG(sbi, *newseg);
	अचिन्हित पूर्णांक old_zoneno = GET_ZONE_FROM_SEG(sbi, *newseg);
	अचिन्हित पूर्णांक left_start = hपूर्णांक;
	bool init = true;
	पूर्णांक go_left = 0;
	पूर्णांक i;

	spin_lock(&मुक्त_i->segmap_lock);

	अगर (!new_sec && ((*newseg + 1) % sbi->segs_per_sec)) अणु
		segno = find_next_zero_bit(मुक्त_i->मुक्त_segmap,
			GET_SEG_FROM_SEC(sbi, hपूर्णांक + 1), *newseg + 1);
		अगर (segno < GET_SEG_FROM_SEC(sbi, hपूर्णांक + 1))
			जाओ got_it;
	पूर्ण
find_other_zone:
	secno = find_next_zero_bit(मुक्त_i->मुक्त_secmap, MAIN_SECS(sbi), hपूर्णांक);
	अगर (secno >= MAIN_SECS(sbi)) अणु
		अगर (dir == ALLOC_RIGHT) अणु
			secno = find_next_zero_bit(मुक्त_i->मुक्त_secmap,
							MAIN_SECS(sbi), 0);
			f2fs_bug_on(sbi, secno >= MAIN_SECS(sbi));
		पूर्ण अन्यथा अणु
			go_left = 1;
			left_start = hपूर्णांक - 1;
		पूर्ण
	पूर्ण
	अगर (go_left == 0)
		जाओ skip_left;

	जबतक (test_bit(left_start, मुक्त_i->मुक्त_secmap)) अणु
		अगर (left_start > 0) अणु
			left_start--;
			जारी;
		पूर्ण
		left_start = find_next_zero_bit(मुक्त_i->मुक्त_secmap,
							MAIN_SECS(sbi), 0);
		f2fs_bug_on(sbi, left_start >= MAIN_SECS(sbi));
		अवरोध;
	पूर्ण
	secno = left_start;
skip_left:
	segno = GET_SEG_FROM_SEC(sbi, secno);
	zoneno = GET_ZONE_FROM_SEC(sbi, secno);

	/* give up on finding another zone */
	अगर (!init)
		जाओ got_it;
	अगर (sbi->secs_per_zone == 1)
		जाओ got_it;
	अगर (zoneno == old_zoneno)
		जाओ got_it;
	अगर (dir == ALLOC_LEFT) अणु
		अगर (!go_left && zoneno + 1 >= total_zones)
			जाओ got_it;
		अगर (go_left && zoneno == 0)
			जाओ got_it;
	पूर्ण
	क्रम (i = 0; i < NR_CURSEG_TYPE; i++)
		अगर (CURSEG_I(sbi, i)->zone == zoneno)
			अवरोध;

	अगर (i < NR_CURSEG_TYPE) अणु
		/* zone is in user, try another */
		अगर (go_left)
			hपूर्णांक = zoneno * sbi->secs_per_zone - 1;
		अन्यथा अगर (zoneno + 1 >= total_zones)
			hपूर्णांक = 0;
		अन्यथा
			hपूर्णांक = (zoneno + 1) * sbi->secs_per_zone;
		init = false;
		जाओ find_other_zone;
	पूर्ण
got_it:
	/* set it as dirty segment in मुक्त segmap */
	f2fs_bug_on(sbi, test_bit(segno, मुक्त_i->मुक्त_segmap));
	__set_inuse(sbi, segno);
	*newseg = segno;
	spin_unlock(&मुक्त_i->segmap_lock);
पूर्ण

अटल व्योम reset_curseg(काष्ठा f2fs_sb_info *sbi, पूर्णांक type, पूर्णांक modअगरied)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	काष्ठा summary_footer *sum_footer;
	अचिन्हित लघु seg_type = curseg->seg_type;

	curseg->inited = true;
	curseg->segno = curseg->next_segno;
	curseg->zone = GET_ZONE_FROM_SEG(sbi, curseg->segno);
	curseg->next_blkoff = 0;
	curseg->next_segno = शून्य_SEGNO;

	sum_footer = &(curseg->sum_blk->footer);
	स_रखो(sum_footer, 0, माप(काष्ठा summary_footer));

	sanity_check_seg_type(sbi, seg_type);

	अगर (IS_DATASEG(seg_type))
		SET_SUM_TYPE(sum_footer, SUM_TYPE_DATA);
	अगर (IS_NODESEG(seg_type))
		SET_SUM_TYPE(sum_footer, SUM_TYPE_NODE);
	__set_sit_entry_type(sbi, seg_type, curseg->segno, modअगरied);
पूर्ण

अटल अचिन्हित पूर्णांक __get_next_segno(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	अचिन्हित लघु seg_type = curseg->seg_type;

	sanity_check_seg_type(sbi, seg_type);

	/* अगर segs_per_sec is large than 1, we need to keep original policy. */
	अगर (__is_large_section(sbi))
		वापस curseg->segno;

	/* inmem log may not locate on any segment after mount */
	अगर (!curseg->inited)
		वापस 0;

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		वापस 0;

	अगर (test_opt(sbi, NOHEAP) &&
		(seg_type == CURSEG_HOT_DATA || IS_NODESEG(seg_type)))
		वापस 0;

	अगर (SIT_I(sbi)->last_victim[ALLOC_NEXT])
		वापस SIT_I(sbi)->last_victim[ALLOC_NEXT];

	/* find segments from 0 to reuse मुक्तd segments */
	अगर (F2FS_OPTION(sbi).alloc_mode == ALLOC_MODE_REUSE)
		वापस 0;

	वापस curseg->segno;
पूर्ण

/*
 * Allocate a current working segment.
 * This function always allocates a मुक्त segment in LFS manner.
 */
अटल व्योम new_curseg(काष्ठा f2fs_sb_info *sbi, पूर्णांक type, bool new_sec)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	अचिन्हित लघु seg_type = curseg->seg_type;
	अचिन्हित पूर्णांक segno = curseg->segno;
	पूर्णांक dir = ALLOC_LEFT;

	अगर (curseg->inited)
		ग_लिखो_sum_page(sbi, curseg->sum_blk,
				GET_SUM_BLOCK(sbi, segno));
	अगर (seg_type == CURSEG_WARM_DATA || seg_type == CURSEG_COLD_DATA)
		dir = ALLOC_RIGHT;

	अगर (test_opt(sbi, NOHEAP))
		dir = ALLOC_RIGHT;

	segno = __get_next_segno(sbi, type);
	get_new_segment(sbi, &segno, new_sec, dir);
	curseg->next_segno = segno;
	reset_curseg(sbi, type, 1);
	curseg->alloc_type = LFS;
पूर्ण

अटल पूर्णांक __next_मुक्त_blkoff(काष्ठा f2fs_sb_info *sbi,
					पूर्णांक segno, block_t start)
अणु
	काष्ठा seg_entry *se = get_seg_entry(sbi, segno);
	पूर्णांक entries = SIT_VBLOCK_MAP_SIZE / माप(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ *target_map = SIT_I(sbi)->पंचांगp_map;
	अचिन्हित दीर्घ *ckpt_map = (अचिन्हित दीर्घ *)se->ckpt_valid_map;
	अचिन्हित दीर्घ *cur_map = (अचिन्हित दीर्घ *)se->cur_valid_map;
	पूर्णांक i;

	क्रम (i = 0; i < entries; i++)
		target_map[i] = ckpt_map[i] | cur_map[i];

	वापस __find_rev_next_zero_bit(target_map, sbi->blocks_per_seg, start);
पूर्ण

/*
 * If a segment is written by LFS manner, next block offset is just obtained
 * by increasing the current block offset. However, अगर a segment is written by
 * SSR manner, next block offset obtained by calling __next_मुक्त_blkoff
 */
अटल व्योम __refresh_next_blkoff(काष्ठा f2fs_sb_info *sbi,
				काष्ठा curseg_info *seg)
अणु
	अगर (seg->alloc_type == SSR)
		seg->next_blkoff =
			__next_मुक्त_blkoff(sbi, seg->segno,
						seg->next_blkoff + 1);
	अन्यथा
		seg->next_blkoff++;
पूर्ण

bool f2fs_segment_has_मुक्त_slot(काष्ठा f2fs_sb_info *sbi, पूर्णांक segno)
अणु
	वापस __next_मुक्त_blkoff(sbi, segno, 0) < sbi->blocks_per_seg;
पूर्ण

/*
 * This function always allocates a used segment(from dirty seglist) by SSR
 * manner, so it should recover the existing segment inक्रमmation of valid blocks
 */
अटल व्योम change_curseg(काष्ठा f2fs_sb_info *sbi, पूर्णांक type, bool flush)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	अचिन्हित पूर्णांक new_segno = curseg->next_segno;
	काष्ठा f2fs_summary_block *sum_node;
	काष्ठा page *sum_page;

	अगर (flush)
		ग_लिखो_sum_page(sbi, curseg->sum_blk,
					GET_SUM_BLOCK(sbi, curseg->segno));

	__set_test_and_inuse(sbi, new_segno);

	mutex_lock(&dirty_i->seglist_lock);
	__हटाओ_dirty_segment(sbi, new_segno, PRE);
	__हटाओ_dirty_segment(sbi, new_segno, सूचीTY);
	mutex_unlock(&dirty_i->seglist_lock);

	reset_curseg(sbi, type, 1);
	curseg->alloc_type = SSR;
	curseg->next_blkoff = __next_मुक्त_blkoff(sbi, curseg->segno, 0);

	sum_page = f2fs_get_sum_page(sbi, new_segno);
	अगर (IS_ERR(sum_page)) अणु
		/* GC won't be able to use stale summary pages by cp_error */
		स_रखो(curseg->sum_blk, 0, SUM_ENTRY_SIZE);
		वापस;
	पूर्ण
	sum_node = (काष्ठा f2fs_summary_block *)page_address(sum_page);
	स_नकल(curseg->sum_blk, sum_node, SUM_ENTRY_SIZE);
	f2fs_put_page(sum_page, 1);
पूर्ण

अटल पूर्णांक get_ssr_segment(काष्ठा f2fs_sb_info *sbi, पूर्णांक type,
				पूर्णांक alloc_mode, अचिन्हित दीर्घ दीर्घ age);

अटल व्योम get_atssr_segment(काष्ठा f2fs_sb_info *sbi, पूर्णांक type,
					पूर्णांक target_type, पूर्णांक alloc_mode,
					अचिन्हित दीर्घ दीर्घ age)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);

	curseg->seg_type = target_type;

	अगर (get_ssr_segment(sbi, type, alloc_mode, age)) अणु
		काष्ठा seg_entry *se = get_seg_entry(sbi, curseg->next_segno);

		curseg->seg_type = se->type;
		change_curseg(sbi, type, true);
	पूर्ण अन्यथा अणु
		/* allocate cold segment by शेष */
		curseg->seg_type = CURSEG_COLD_DATA;
		new_curseg(sbi, type, true);
	पूर्ण
	stat_inc_seg_type(sbi, curseg);
पूर्ण

अटल व्योम __f2fs_init_atgc_curseg(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, CURSEG_ALL_DATA_ATGC);

	अगर (!sbi->am.atgc_enabled)
		वापस;

	करोwn_पढ़ो(&SM_I(sbi)->curseg_lock);

	mutex_lock(&curseg->curseg_mutex);
	करोwn_ग_लिखो(&SIT_I(sbi)->sentry_lock);

	get_atssr_segment(sbi, CURSEG_ALL_DATA_ATGC, CURSEG_COLD_DATA, SSR, 0);

	up_ग_लिखो(&SIT_I(sbi)->sentry_lock);
	mutex_unlock(&curseg->curseg_mutex);

	up_पढ़ो(&SM_I(sbi)->curseg_lock);

पूर्ण
व्योम f2fs_init_inmem_curseg(काष्ठा f2fs_sb_info *sbi)
अणु
	__f2fs_init_atgc_curseg(sbi);
पूर्ण

अटल व्योम __f2fs_save_inmem_curseg(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);

	mutex_lock(&curseg->curseg_mutex);
	अगर (!curseg->inited)
		जाओ out;

	अगर (get_valid_blocks(sbi, curseg->segno, false)) अणु
		ग_लिखो_sum_page(sbi, curseg->sum_blk,
				GET_SUM_BLOCK(sbi, curseg->segno));
	पूर्ण अन्यथा अणु
		mutex_lock(&सूचीTY_I(sbi)->seglist_lock);
		__set_test_and_मुक्त(sbi, curseg->segno, true);
		mutex_unlock(&सूचीTY_I(sbi)->seglist_lock);
	पूर्ण
out:
	mutex_unlock(&curseg->curseg_mutex);
पूर्ण

व्योम f2fs_save_inmem_curseg(काष्ठा f2fs_sb_info *sbi)
अणु
	__f2fs_save_inmem_curseg(sbi, CURSEG_COLD_DATA_PINNED);

	अगर (sbi->am.atgc_enabled)
		__f2fs_save_inmem_curseg(sbi, CURSEG_ALL_DATA_ATGC);
पूर्ण

अटल व्योम __f2fs_restore_inmem_curseg(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);

	mutex_lock(&curseg->curseg_mutex);
	अगर (!curseg->inited)
		जाओ out;
	अगर (get_valid_blocks(sbi, curseg->segno, false))
		जाओ out;

	mutex_lock(&सूचीTY_I(sbi)->seglist_lock);
	__set_test_and_inuse(sbi, curseg->segno);
	mutex_unlock(&सूचीTY_I(sbi)->seglist_lock);
out:
	mutex_unlock(&curseg->curseg_mutex);
पूर्ण

व्योम f2fs_restore_inmem_curseg(काष्ठा f2fs_sb_info *sbi)
अणु
	__f2fs_restore_inmem_curseg(sbi, CURSEG_COLD_DATA_PINNED);

	अगर (sbi->am.atgc_enabled)
		__f2fs_restore_inmem_curseg(sbi, CURSEG_ALL_DATA_ATGC);
पूर्ण

अटल पूर्णांक get_ssr_segment(काष्ठा f2fs_sb_info *sbi, पूर्णांक type,
				पूर्णांक alloc_mode, अचिन्हित दीर्घ दीर्घ age)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	स्थिर काष्ठा victim_selection *v_ops = सूचीTY_I(sbi)->v_ops;
	अचिन्हित segno = शून्य_SEGNO;
	अचिन्हित लघु seg_type = curseg->seg_type;
	पूर्णांक i, cnt;
	bool reversed = false;

	sanity_check_seg_type(sbi, seg_type);

	/* f2fs_need_SSR() alपढ़ोy क्रमces to करो this */
	अगर (!v_ops->get_victim(sbi, &segno, BG_GC, seg_type, alloc_mode, age)) अणु
		curseg->next_segno = segno;
		वापस 1;
	पूर्ण

	/* For node segments, let's करो SSR more पूर्णांकensively */
	अगर (IS_NODESEG(seg_type)) अणु
		अगर (seg_type >= CURSEG_WARM_NODE) अणु
			reversed = true;
			i = CURSEG_COLD_NODE;
		पूर्ण अन्यथा अणु
			i = CURSEG_HOT_NODE;
		पूर्ण
		cnt = NR_CURSEG_NODE_TYPE;
	पूर्ण अन्यथा अणु
		अगर (seg_type >= CURSEG_WARM_DATA) अणु
			reversed = true;
			i = CURSEG_COLD_DATA;
		पूर्ण अन्यथा अणु
			i = CURSEG_HOT_DATA;
		पूर्ण
		cnt = NR_CURSEG_DATA_TYPE;
	पूर्ण

	क्रम (; cnt-- > 0; reversed ? i-- : i++) अणु
		अगर (i == seg_type)
			जारी;
		अगर (!v_ops->get_victim(sbi, &segno, BG_GC, i, alloc_mode, age)) अणु
			curseg->next_segno = segno;
			वापस 1;
		पूर्ण
	पूर्ण

	/* find valid_blocks=0 in dirty list */
	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) अणु
		segno = get_मुक्त_segment(sbi);
		अगर (segno != शून्य_SEGNO) अणु
			curseg->next_segno = segno;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * flush out current segment and replace it with new segment
 * This function should be वापसed with success, otherwise BUG
 */
अटल व्योम allocate_segment_by_शेष(काष्ठा f2fs_sb_info *sbi,
						पूर्णांक type, bool क्रमce)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);

	अगर (क्रमce)
		new_curseg(sbi, type, true);
	अन्यथा अगर (!is_set_ckpt_flags(sbi, CP_CRC_RECOVERY_FLAG) &&
					curseg->seg_type == CURSEG_WARM_NODE)
		new_curseg(sbi, type, false);
	अन्यथा अगर (curseg->alloc_type == LFS &&
			is_next_segment_मुक्त(sbi, curseg, type) &&
			likely(!is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		new_curseg(sbi, type, false);
	अन्यथा अगर (f2fs_need_SSR(sbi) &&
			get_ssr_segment(sbi, type, SSR, 0))
		change_curseg(sbi, type, true);
	अन्यथा
		new_curseg(sbi, type, false);

	stat_inc_seg_type(sbi, curseg);
पूर्ण

व्योम f2fs_allocate_segment_क्रम_resize(काष्ठा f2fs_sb_info *sbi, पूर्णांक type,
					अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	अचिन्हित पूर्णांक segno;

	करोwn_पढ़ो(&SM_I(sbi)->curseg_lock);
	mutex_lock(&curseg->curseg_mutex);
	करोwn_ग_लिखो(&SIT_I(sbi)->sentry_lock);

	segno = CURSEG_I(sbi, type)->segno;
	अगर (segno < start || segno > end)
		जाओ unlock;

	अगर (f2fs_need_SSR(sbi) && get_ssr_segment(sbi, type, SSR, 0))
		change_curseg(sbi, type, true);
	अन्यथा
		new_curseg(sbi, type, true);

	stat_inc_seg_type(sbi, curseg);

	locate_dirty_segment(sbi, segno);
unlock:
	up_ग_लिखो(&SIT_I(sbi)->sentry_lock);

	अगर (segno != curseg->segno)
		f2fs_notice(sbi, "For resize: curseg of type %d: %u ==> %u",
			    type, segno, curseg->segno);

	mutex_unlock(&curseg->curseg_mutex);
	up_पढ़ो(&SM_I(sbi)->curseg_lock);
पूर्ण

अटल व्योम __allocate_new_segment(काष्ठा f2fs_sb_info *sbi, पूर्णांक type,
						bool new_sec, bool क्रमce)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	अचिन्हित पूर्णांक old_segno;

	अगर (!curseg->inited)
		जाओ alloc;

	अगर (क्रमce || curseg->next_blkoff ||
		get_valid_blocks(sbi, curseg->segno, new_sec))
		जाओ alloc;

	अगर (!get_ckpt_valid_blocks(sbi, curseg->segno, new_sec))
		वापस;
alloc:
	old_segno = curseg->segno;
	SIT_I(sbi)->s_ops->allocate_segment(sbi, type, true);
	locate_dirty_segment(sbi, old_segno);
पूर्ण

अटल व्योम __allocate_new_section(काष्ठा f2fs_sb_info *sbi,
						पूर्णांक type, bool क्रमce)
अणु
	__allocate_new_segment(sbi, type, true, क्रमce);
पूर्ण

व्योम f2fs_allocate_new_section(काष्ठा f2fs_sb_info *sbi, पूर्णांक type, bool क्रमce)
अणु
	करोwn_पढ़ो(&SM_I(sbi)->curseg_lock);
	करोwn_ग_लिखो(&SIT_I(sbi)->sentry_lock);
	__allocate_new_section(sbi, type, क्रमce);
	up_ग_लिखो(&SIT_I(sbi)->sentry_lock);
	up_पढ़ो(&SM_I(sbi)->curseg_lock);
पूर्ण

व्योम f2fs_allocate_new_segments(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक i;

	करोwn_पढ़ो(&SM_I(sbi)->curseg_lock);
	करोwn_ग_लिखो(&SIT_I(sbi)->sentry_lock);
	क्रम (i = CURSEG_HOT_DATA; i <= CURSEG_COLD_DATA; i++)
		__allocate_new_segment(sbi, i, false, false);
	up_ग_लिखो(&SIT_I(sbi)->sentry_lock);
	up_पढ़ो(&SM_I(sbi)->curseg_lock);
पूर्ण

अटल स्थिर काष्ठा segment_allocation शेष_salloc_ops = अणु
	.allocate_segment = allocate_segment_by_शेष,
पूर्ण;

bool f2fs_exist_trim_candidates(काष्ठा f2fs_sb_info *sbi,
						काष्ठा cp_control *cpc)
अणु
	__u64 trim_start = cpc->trim_start;
	bool has_candidate = false;

	करोwn_ग_लिखो(&SIT_I(sbi)->sentry_lock);
	क्रम (; cpc->trim_start <= cpc->trim_end; cpc->trim_start++) अणु
		अगर (add_discard_addrs(sbi, cpc, true)) अणु
			has_candidate = true;
			अवरोध;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&SIT_I(sbi)->sentry_lock);

	cpc->trim_start = trim_start;
	वापस has_candidate;
पूर्ण

अटल अचिन्हित पूर्णांक __issue_discard_cmd_range(काष्ठा f2fs_sb_info *sbi,
					काष्ठा discard_policy *dpolicy,
					अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा discard_cmd *prev_dc = शून्य, *next_dc = शून्य;
	काष्ठा rb_node **insert_p = शून्य, *insert_parent = शून्य;
	काष्ठा discard_cmd *dc;
	काष्ठा blk_plug plug;
	पूर्णांक issued;
	अचिन्हित पूर्णांक trimmed = 0;

next:
	issued = 0;

	mutex_lock(&dcc->cmd_lock);
	अगर (unlikely(dcc->rbtree_check))
		f2fs_bug_on(sbi, !f2fs_check_rb_tree_consistence(sbi,
							&dcc->root, false));

	dc = (काष्ठा discard_cmd *)f2fs_lookup_rb_tree_ret(&dcc->root,
					शून्य, start,
					(काष्ठा rb_entry **)&prev_dc,
					(काष्ठा rb_entry **)&next_dc,
					&insert_p, &insert_parent, true, शून्य);
	अगर (!dc)
		dc = next_dc;

	blk_start_plug(&plug);

	जबतक (dc && dc->lstart <= end) अणु
		काष्ठा rb_node *node;
		पूर्णांक err = 0;

		अगर (dc->len < dpolicy->granularity)
			जाओ skip;

		अगर (dc->state != D_PREP) अणु
			list_move_tail(&dc->list, &dcc->fstrim_list);
			जाओ skip;
		पूर्ण

		err = __submit_discard_cmd(sbi, dpolicy, dc, &issued);

		अगर (issued >= dpolicy->max_requests) अणु
			start = dc->lstart + dc->len;

			अगर (err)
				__हटाओ_discard_cmd(sbi, dc);

			blk_finish_plug(&plug);
			mutex_unlock(&dcc->cmd_lock);
			trimmed += __रुको_all_discard_cmd(sbi, शून्य);
			congestion_रुको(BLK_RW_ASYNC, DEFAULT_IO_TIMEOUT);
			जाओ next;
		पूर्ण
skip:
		node = rb_next(&dc->rb_node);
		अगर (err)
			__हटाओ_discard_cmd(sbi, dc);
		dc = rb_entry_safe(node, काष्ठा discard_cmd, rb_node);

		अगर (fatal_संकेत_pending(current))
			अवरोध;
	पूर्ण

	blk_finish_plug(&plug);
	mutex_unlock(&dcc->cmd_lock);

	वापस trimmed;
पूर्ण

पूर्णांक f2fs_trim_fs(काष्ठा f2fs_sb_info *sbi, काष्ठा fstrim_range *range)
अणु
	__u64 start = F2FS_BYTES_TO_BLK(range->start);
	__u64 end = start + F2FS_BYTES_TO_BLK(range->len) - 1;
	अचिन्हित पूर्णांक start_segno, end_segno;
	block_t start_block, end_block;
	काष्ठा cp_control cpc;
	काष्ठा discard_policy dpolicy;
	अचिन्हित दीर्घ दीर्घ trimmed = 0;
	पूर्णांक err = 0;
	bool need_align = f2fs_lfs_mode(sbi) && __is_large_section(sbi);

	अगर (start >= MAX_BLKADDR(sbi) || range->len < sbi->blocksize)
		वापस -EINVAL;

	अगर (end < MAIN_BLKADDR(sbi))
		जाओ out;

	अगर (is_sbi_flag_set(sbi, SBI_NEED_FSCK)) अणु
		f2fs_warn(sbi, "Found FS corruption, run fsck to fix.");
		वापस -EFSCORRUPTED;
	पूर्ण

	/* start/end segment number in मुख्य_area */
	start_segno = (start <= MAIN_BLKADDR(sbi)) ? 0 : GET_SEGNO(sbi, start);
	end_segno = (end >= MAX_BLKADDR(sbi)) ? MAIN_SEGS(sbi) - 1 :
						GET_SEGNO(sbi, end);
	अगर (need_align) अणु
		start_segno = roundकरोwn(start_segno, sbi->segs_per_sec);
		end_segno = roundup(end_segno + 1, sbi->segs_per_sec) - 1;
	पूर्ण

	cpc.reason = CP_DISCARD;
	cpc.trim_minlen = max_t(__u64, 1, F2FS_BYTES_TO_BLK(range->minlen));
	cpc.trim_start = start_segno;
	cpc.trim_end = end_segno;

	अगर (sbi->discard_blks == 0)
		जाओ out;

	करोwn_ग_लिखो(&sbi->gc_lock);
	err = f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
	up_ग_लिखो(&sbi->gc_lock);
	अगर (err)
		जाओ out;

	/*
	 * We filed discard candidates, but actually we करोn't need to रुको क्रम
	 * all of them, since they'll be issued in idle समय aदीर्घ with runसमय
	 * discard option. User configuration looks like using runसमय discard
	 * or periodic fstrim instead of it.
	 */
	अगर (f2fs_realसमय_discard_enable(sbi))
		जाओ out;

	start_block = START_BLOCK(sbi, start_segno);
	end_block = START_BLOCK(sbi, end_segno + 1);

	__init_discard_policy(sbi, &dpolicy, DPOLICY_FSTRIM, cpc.trim_minlen);
	trimmed = __issue_discard_cmd_range(sbi, &dpolicy,
					start_block, end_block);

	trimmed += __रुको_discard_cmd_range(sbi, &dpolicy,
					start_block, end_block);
out:
	अगर (!err)
		range->len = F2FS_BLK_TO_BYTES(trimmed);
	वापस err;
पूर्ण

अटल bool __has_curseg_space(काष्ठा f2fs_sb_info *sbi,
					काष्ठा curseg_info *curseg)
अणु
	वापस curseg->next_blkoff < f2fs_usable_blks_in_seg(sbi,
							curseg->segno);
पूर्ण

पूर्णांक f2fs_rw_hपूर्णांक_to_seg_type(क्रमागत rw_hपूर्णांक hपूर्णांक)
अणु
	चयन (hपूर्णांक) अणु
	हाल WRITE_LIFE_SHORT:
		वापस CURSEG_HOT_DATA;
	हाल WRITE_LIFE_EXTREME:
		वापस CURSEG_COLD_DATA;
	शेष:
		वापस CURSEG_WARM_DATA;
	पूर्ण
पूर्ण

/* This वापसs ग_लिखो hपूर्णांकs क्रम each segment type. This hपूर्णांकs will be
 * passed करोwn to block layer. There are mapping tables which depend on
 * the mount option 'whint_mode'.
 *
 * 1) whपूर्णांक_mode=off. F2FS only passes करोwn WRITE_LIFE_NOT_SET.
 *
 * 2) whपूर्णांक_mode=user-based. F2FS tries to pass करोwn hपूर्णांकs given by users.
 *
 * User                  F2FS                     Block
 * ----                  ----                     -----
 *                       META                     WRITE_LIFE_NOT_SET
 *                       HOT_NODE                 "
 *                       WARM_NODE                "
 *                       COLD_NODE                "
 * ioctl(COLD)           COLD_DATA                WRITE_LIFE_EXTREME
 * extension list        "                        "
 *
 * -- buffered io
 * WRITE_LIFE_EXTREME    COLD_DATA                WRITE_LIFE_EXTREME
 * WRITE_LIFE_SHORT      HOT_DATA                 WRITE_LIFE_SHORT
 * WRITE_LIFE_NOT_SET    WARM_DATA                WRITE_LIFE_NOT_SET
 * WRITE_LIFE_NONE       "                        "
 * WRITE_LIFE_MEDIUM     "                        "
 * WRITE_LIFE_LONG       "                        "
 *
 * -- direct io
 * WRITE_LIFE_EXTREME    COLD_DATA                WRITE_LIFE_EXTREME
 * WRITE_LIFE_SHORT      HOT_DATA                 WRITE_LIFE_SHORT
 * WRITE_LIFE_NOT_SET    WARM_DATA                WRITE_LIFE_NOT_SET
 * WRITE_LIFE_NONE       "                        WRITE_LIFE_NONE
 * WRITE_LIFE_MEDIUM     "                        WRITE_LIFE_MEDIUM
 * WRITE_LIFE_LONG       "                        WRITE_LIFE_LONG
 *
 * 3) whपूर्णांक_mode=fs-based. F2FS passes करोwn hपूर्णांकs with its policy.
 *
 * User                  F2FS                     Block
 * ----                  ----                     -----
 *                       META                     WRITE_LIFE_MEDIUM;
 *                       HOT_NODE                 WRITE_LIFE_NOT_SET
 *                       WARM_NODE                "
 *                       COLD_NODE                WRITE_LIFE_NONE
 * ioctl(COLD)           COLD_DATA                WRITE_LIFE_EXTREME
 * extension list        "                        "
 *
 * -- buffered io
 * WRITE_LIFE_EXTREME    COLD_DATA                WRITE_LIFE_EXTREME
 * WRITE_LIFE_SHORT      HOT_DATA                 WRITE_LIFE_SHORT
 * WRITE_LIFE_NOT_SET    WARM_DATA                WRITE_LIFE_LONG
 * WRITE_LIFE_NONE       "                        "
 * WRITE_LIFE_MEDIUM     "                        "
 * WRITE_LIFE_LONG       "                        "
 *
 * -- direct io
 * WRITE_LIFE_EXTREME    COLD_DATA                WRITE_LIFE_EXTREME
 * WRITE_LIFE_SHORT      HOT_DATA                 WRITE_LIFE_SHORT
 * WRITE_LIFE_NOT_SET    WARM_DATA                WRITE_LIFE_NOT_SET
 * WRITE_LIFE_NONE       "                        WRITE_LIFE_NONE
 * WRITE_LIFE_MEDIUM     "                        WRITE_LIFE_MEDIUM
 * WRITE_LIFE_LONG       "                        WRITE_LIFE_LONG
 */

क्रमागत rw_hपूर्णांक f2fs_io_type_to_rw_hपूर्णांक(काष्ठा f2fs_sb_info *sbi,
				क्रमागत page_type type, क्रमागत temp_type temp)
अणु
	अगर (F2FS_OPTION(sbi).whपूर्णांक_mode == WHINT_MODE_USER) अणु
		अगर (type == DATA) अणु
			अगर (temp == WARM)
				वापस WRITE_LIFE_NOT_SET;
			अन्यथा अगर (temp == HOT)
				वापस WRITE_LIFE_SHORT;
			अन्यथा अगर (temp == COLD)
				वापस WRITE_LIFE_EXTREME;
		पूर्ण अन्यथा अणु
			वापस WRITE_LIFE_NOT_SET;
		पूर्ण
	पूर्ण अन्यथा अगर (F2FS_OPTION(sbi).whपूर्णांक_mode == WHINT_MODE_FS) अणु
		अगर (type == DATA) अणु
			अगर (temp == WARM)
				वापस WRITE_LIFE_LONG;
			अन्यथा अगर (temp == HOT)
				वापस WRITE_LIFE_SHORT;
			अन्यथा अगर (temp == COLD)
				वापस WRITE_LIFE_EXTREME;
		पूर्ण अन्यथा अगर (type == NODE) अणु
			अगर (temp == WARM || temp == HOT)
				वापस WRITE_LIFE_NOT_SET;
			अन्यथा अगर (temp == COLD)
				वापस WRITE_LIFE_NONE;
		पूर्ण अन्यथा अगर (type == META) अणु
			वापस WRITE_LIFE_MEDIUM;
		पूर्ण
	पूर्ण
	वापस WRITE_LIFE_NOT_SET;
पूर्ण

अटल पूर्णांक __get_segment_type_2(काष्ठा f2fs_io_info *fio)
अणु
	अगर (fio->type == DATA)
		वापस CURSEG_HOT_DATA;
	अन्यथा
		वापस CURSEG_HOT_NODE;
पूर्ण

अटल पूर्णांक __get_segment_type_4(काष्ठा f2fs_io_info *fio)
अणु
	अगर (fio->type == DATA) अणु
		काष्ठा inode *inode = fio->page->mapping->host;

		अगर (S_ISसूची(inode->i_mode))
			वापस CURSEG_HOT_DATA;
		अन्यथा
			वापस CURSEG_COLD_DATA;
	पूर्ण अन्यथा अणु
		अगर (IS_DNODE(fio->page) && is_cold_node(fio->page))
			वापस CURSEG_WARM_NODE;
		अन्यथा
			वापस CURSEG_COLD_NODE;
	पूर्ण
पूर्ण

अटल पूर्णांक __get_segment_type_6(काष्ठा f2fs_io_info *fio)
अणु
	अगर (fio->type == DATA) अणु
		काष्ठा inode *inode = fio->page->mapping->host;

		अगर (is_cold_data(fio->page)) अणु
			अगर (fio->sbi->am.atgc_enabled &&
				(fio->io_type == FS_DATA_IO) &&
				(fio->sbi->gc_mode != GC_URGENT_HIGH))
				वापस CURSEG_ALL_DATA_ATGC;
			अन्यथा
				वापस CURSEG_COLD_DATA;
		पूर्ण
		अगर (file_is_cold(inode) || f2fs_need_compress_data(inode))
			वापस CURSEG_COLD_DATA;
		अगर (file_is_hot(inode) ||
				is_inode_flag_set(inode, FI_HOT_DATA) ||
				f2fs_is_atomic_file(inode) ||
				f2fs_is_अस्थिर_file(inode))
			वापस CURSEG_HOT_DATA;
		वापस f2fs_rw_hपूर्णांक_to_seg_type(inode->i_ग_लिखो_hपूर्णांक);
	पूर्ण अन्यथा अणु
		अगर (IS_DNODE(fio->page))
			वापस is_cold_node(fio->page) ? CURSEG_WARM_NODE :
						CURSEG_HOT_NODE;
		वापस CURSEG_COLD_NODE;
	पूर्ण
पूर्ण

अटल पूर्णांक __get_segment_type(काष्ठा f2fs_io_info *fio)
अणु
	पूर्णांक type = 0;

	चयन (F2FS_OPTION(fio->sbi).active_logs) अणु
	हाल 2:
		type = __get_segment_type_2(fio);
		अवरोध;
	हाल 4:
		type = __get_segment_type_4(fio);
		अवरोध;
	हाल 6:
		type = __get_segment_type_6(fio);
		अवरोध;
	शेष:
		f2fs_bug_on(fio->sbi, true);
	पूर्ण

	अगर (IS_HOT(type))
		fio->temp = HOT;
	अन्यथा अगर (IS_WARM(type))
		fio->temp = WARM;
	अन्यथा
		fio->temp = COLD;
	वापस type;
पूर्ण

व्योम f2fs_allocate_data_block(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page,
		block_t old_blkaddr, block_t *new_blkaddr,
		काष्ठा f2fs_summary *sum, पूर्णांक type,
		काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	अचिन्हित दीर्घ दीर्घ old_mसमय;
	bool from_gc = (type == CURSEG_ALL_DATA_ATGC);
	काष्ठा seg_entry *se = शून्य;

	करोwn_पढ़ो(&SM_I(sbi)->curseg_lock);

	mutex_lock(&curseg->curseg_mutex);
	करोwn_ग_लिखो(&sit_i->sentry_lock);

	अगर (from_gc) अणु
		f2fs_bug_on(sbi, GET_SEGNO(sbi, old_blkaddr) == शून्य_SEGNO);
		se = get_seg_entry(sbi, GET_SEGNO(sbi, old_blkaddr));
		sanity_check_seg_type(sbi, se->type);
		f2fs_bug_on(sbi, IS_NODESEG(se->type));
	पूर्ण
	*new_blkaddr = NEXT_FREE_BLKADDR(sbi, curseg);

	f2fs_bug_on(sbi, curseg->next_blkoff >= sbi->blocks_per_seg);

	f2fs_रुको_discard_bio(sbi, *new_blkaddr);

	/*
	 * __add_sum_entry should be resided under the curseg_mutex
	 * because, this function updates a summary entry in the
	 * current summary block.
	 */
	__add_sum_entry(sbi, type, sum);

	__refresh_next_blkoff(sbi, curseg);

	stat_inc_block_count(sbi, curseg);

	अगर (from_gc) अणु
		old_mसमय = get_segment_mसमय(sbi, old_blkaddr);
	पूर्ण अन्यथा अणु
		update_segment_mसमय(sbi, old_blkaddr, 0);
		old_mसमय = 0;
	पूर्ण
	update_segment_mसमय(sbi, *new_blkaddr, old_mसमय);

	/*
	 * SIT inक्रमmation should be updated beक्रमe segment allocation,
	 * since SSR needs latest valid block inक्रमmation.
	 */
	update_sit_entry(sbi, *new_blkaddr, 1);
	अगर (GET_SEGNO(sbi, old_blkaddr) != शून्य_SEGNO)
		update_sit_entry(sbi, old_blkaddr, -1);

	अगर (!__has_curseg_space(sbi, curseg)) अणु
		अगर (from_gc)
			get_atssr_segment(sbi, type, se->type,
						AT_SSR, se->mसमय);
		अन्यथा
			sit_i->s_ops->allocate_segment(sbi, type, false);
	पूर्ण
	/*
	 * segment dirty status should be updated after segment allocation,
	 * so we just need to update status only one समय after previous
	 * segment being बंदd.
	 */
	locate_dirty_segment(sbi, GET_SEGNO(sbi, old_blkaddr));
	locate_dirty_segment(sbi, GET_SEGNO(sbi, *new_blkaddr));

	up_ग_लिखो(&sit_i->sentry_lock);

	अगर (page && IS_NODESEG(type)) अणु
		fill_node_footer_blkaddr(page, NEXT_FREE_BLKADDR(sbi, curseg));

		f2fs_inode_chksum_set(sbi, page);
	पूर्ण

	अगर (fio) अणु
		काष्ठा f2fs_bio_info *io;

		अगर (F2FS_IO_ALIGNED(sbi))
			fio->retry = false;

		INIT_LIST_HEAD(&fio->list);
		fio->in_list = true;
		io = sbi->ग_लिखो_io[fio->type] + fio->temp;
		spin_lock(&io->io_lock);
		list_add_tail(&fio->list, &io->io_list);
		spin_unlock(&io->io_lock);
	पूर्ण

	mutex_unlock(&curseg->curseg_mutex);

	up_पढ़ो(&SM_I(sbi)->curseg_lock);
पूर्ण

अटल व्योम update_device_state(काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा f2fs_sb_info *sbi = fio->sbi;
	अचिन्हित पूर्णांक devidx;

	अगर (!f2fs_is_multi_device(sbi))
		वापस;

	devidx = f2fs_target_device_index(sbi, fio->new_blkaddr);

	/* update device state क्रम fsync */
	f2fs_set_dirty_device(sbi, fio->ino, devidx, FLUSH_INO);

	/* update device state क्रम checkpoपूर्णांक */
	अगर (!f2fs_test_bit(devidx, (अक्षर *)&sbi->dirty_device)) अणु
		spin_lock(&sbi->dev_lock);
		f2fs_set_bit(devidx, (अक्षर *)&sbi->dirty_device);
		spin_unlock(&sbi->dev_lock);
	पूर्ण
पूर्ण

अटल व्योम करो_ग_लिखो_page(काष्ठा f2fs_summary *sum, काष्ठा f2fs_io_info *fio)
अणु
	पूर्णांक type = __get_segment_type(fio);
	bool keep_order = (f2fs_lfs_mode(fio->sbi) && type == CURSEG_COLD_DATA);

	अगर (keep_order)
		करोwn_पढ़ो(&fio->sbi->io_order_lock);
पुनः_स्मृतिate:
	f2fs_allocate_data_block(fio->sbi, fio->page, fio->old_blkaddr,
			&fio->new_blkaddr, sum, type, fio);
	अगर (GET_SEGNO(fio->sbi, fio->old_blkaddr) != शून्य_SEGNO)
		invalidate_mapping_pages(META_MAPPING(fio->sbi),
					fio->old_blkaddr, fio->old_blkaddr);

	/* ग_लिखोout dirty page पूर्णांकo bdev */
	f2fs_submit_page_ग_लिखो(fio);
	अगर (fio->retry) अणु
		fio->old_blkaddr = fio->new_blkaddr;
		जाओ पुनः_स्मृतिate;
	पूर्ण

	update_device_state(fio);

	अगर (keep_order)
		up_पढ़ो(&fio->sbi->io_order_lock);
पूर्ण

व्योम f2fs_करो_ग_लिखो_meta_page(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page,
					क्रमागत iostat_type io_type)
अणु
	काष्ठा f2fs_io_info fio = अणु
		.sbi = sbi,
		.type = META,
		.temp = HOT,
		.op = REQ_OP_WRITE,
		.op_flags = REQ_SYNC | REQ_META | REQ_PRIO,
		.old_blkaddr = page->index,
		.new_blkaddr = page->index,
		.page = page,
		.encrypted_page = शून्य,
		.in_list = false,
	पूर्ण;

	अगर (unlikely(page->index >= MAIN_BLKADDR(sbi)))
		fio.op_flags &= ~REQ_META;

	set_page_ग_लिखोback(page);
	ClearPageError(page);
	f2fs_submit_page_ग_लिखो(&fio);

	stat_inc_meta_count(sbi, page->index);
	f2fs_update_iostat(sbi, io_type, F2FS_BLKSIZE);
पूर्ण

व्योम f2fs_करो_ग_लिखो_node_page(अचिन्हित पूर्णांक nid, काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा f2fs_summary sum;

	set_summary(&sum, nid, 0, 0);
	करो_ग_लिखो_page(&sum, fio);

	f2fs_update_iostat(fio->sbi, fio->io_type, F2FS_BLKSIZE);
पूर्ण

व्योम f2fs_outplace_ग_लिखो_data(काष्ठा dnode_of_data *dn,
					काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा f2fs_sb_info *sbi = fio->sbi;
	काष्ठा f2fs_summary sum;

	f2fs_bug_on(sbi, dn->data_blkaddr == शून्य_ADDR);
	set_summary(&sum, dn->nid, dn->ofs_in_node, fio->version);
	करो_ग_लिखो_page(&sum, fio);
	f2fs_update_data_blkaddr(dn, fio->new_blkaddr);

	f2fs_update_iostat(sbi, fio->io_type, F2FS_BLKSIZE);
पूर्ण

पूर्णांक f2fs_inplace_ग_लिखो_data(काष्ठा f2fs_io_info *fio)
अणु
	पूर्णांक err;
	काष्ठा f2fs_sb_info *sbi = fio->sbi;
	अचिन्हित पूर्णांक segno;

	fio->new_blkaddr = fio->old_blkaddr;
	/* i/o temperature is needed क्रम passing करोwn ग_लिखो hपूर्णांकs */
	__get_segment_type(fio);

	segno = GET_SEGNO(sbi, fio->new_blkaddr);

	अगर (!IS_DATASEG(get_seg_entry(sbi, segno)->type)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: incorrect segment(%u) type, run fsck to fix.",
			  __func__, segno);
		err = -EFSCORRUPTED;
		जाओ drop_bio;
	पूर्ण

	अगर (is_sbi_flag_set(sbi, SBI_NEED_FSCK) || f2fs_cp_error(sbi)) अणु
		err = -EIO;
		जाओ drop_bio;
	पूर्ण

	stat_inc_inplace_blocks(fio->sbi);

	अगर (fio->bio && !(SM_I(sbi)->ipu_policy & (1 << F2FS_IPU_NOCACHE)))
		err = f2fs_merge_page_bio(fio);
	अन्यथा
		err = f2fs_submit_page_bio(fio);
	अगर (!err) अणु
		update_device_state(fio);
		f2fs_update_iostat(fio->sbi, fio->io_type, F2FS_BLKSIZE);
	पूर्ण

	वापस err;
drop_bio:
	अगर (fio->bio && *(fio->bio)) अणु
		काष्ठा bio *bio = *(fio->bio);

		bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
		*(fio->bio) = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक __f2fs_get_curseg(काष्ठा f2fs_sb_info *sbi,
						अचिन्हित पूर्णांक segno)
अणु
	पूर्णांक i;

	क्रम (i = CURSEG_HOT_DATA; i < NO_CHECK_TYPE; i++) अणु
		अगर (CURSEG_I(sbi, i)->segno == segno)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

व्योम f2fs_करो_replace_block(काष्ठा f2fs_sb_info *sbi, काष्ठा f2fs_summary *sum,
				block_t old_blkaddr, block_t new_blkaddr,
				bool recover_curseg, bool recover_newaddr,
				bool from_gc)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	काष्ठा curseg_info *curseg;
	अचिन्हित पूर्णांक segno, old_cursegno;
	काष्ठा seg_entry *se;
	पूर्णांक type;
	अचिन्हित लघु old_blkoff;
	अचिन्हित अक्षर old_alloc_type;

	segno = GET_SEGNO(sbi, new_blkaddr);
	se = get_seg_entry(sbi, segno);
	type = se->type;

	करोwn_ग_लिखो(&SM_I(sbi)->curseg_lock);

	अगर (!recover_curseg) अणु
		/* क्रम recovery flow */
		अगर (se->valid_blocks == 0 && !IS_CURSEG(sbi, segno)) अणु
			अगर (old_blkaddr == शून्य_ADDR)
				type = CURSEG_COLD_DATA;
			अन्यथा
				type = CURSEG_WARM_DATA;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (IS_CURSEG(sbi, segno)) अणु
			/* se->type is अस्थिर as SSR allocation */
			type = __f2fs_get_curseg(sbi, segno);
			f2fs_bug_on(sbi, type == NO_CHECK_TYPE);
		पूर्ण अन्यथा अणु
			type = CURSEG_WARM_DATA;
		पूर्ण
	पूर्ण

	f2fs_bug_on(sbi, !IS_DATASEG(type));
	curseg = CURSEG_I(sbi, type);

	mutex_lock(&curseg->curseg_mutex);
	करोwn_ग_लिखो(&sit_i->sentry_lock);

	old_cursegno = curseg->segno;
	old_blkoff = curseg->next_blkoff;
	old_alloc_type = curseg->alloc_type;

	/* change the current segment */
	अगर (segno != curseg->segno) अणु
		curseg->next_segno = segno;
		change_curseg(sbi, type, true);
	पूर्ण

	curseg->next_blkoff = GET_BLKOFF_FROM_SEG0(sbi, new_blkaddr);
	__add_sum_entry(sbi, type, sum);

	अगर (!recover_curseg || recover_newaddr) अणु
		अगर (!from_gc)
			update_segment_mसमय(sbi, new_blkaddr, 0);
		update_sit_entry(sbi, new_blkaddr, 1);
	पूर्ण
	अगर (GET_SEGNO(sbi, old_blkaddr) != शून्य_SEGNO) अणु
		invalidate_mapping_pages(META_MAPPING(sbi),
					old_blkaddr, old_blkaddr);
		अगर (!from_gc)
			update_segment_mसमय(sbi, old_blkaddr, 0);
		update_sit_entry(sbi, old_blkaddr, -1);
	पूर्ण

	locate_dirty_segment(sbi, GET_SEGNO(sbi, old_blkaddr));
	locate_dirty_segment(sbi, GET_SEGNO(sbi, new_blkaddr));

	locate_dirty_segment(sbi, old_cursegno);

	अगर (recover_curseg) अणु
		अगर (old_cursegno != curseg->segno) अणु
			curseg->next_segno = old_cursegno;
			change_curseg(sbi, type, true);
		पूर्ण
		curseg->next_blkoff = old_blkoff;
		curseg->alloc_type = old_alloc_type;
	पूर्ण

	up_ग_लिखो(&sit_i->sentry_lock);
	mutex_unlock(&curseg->curseg_mutex);
	up_ग_लिखो(&SM_I(sbi)->curseg_lock);
पूर्ण

व्योम f2fs_replace_block(काष्ठा f2fs_sb_info *sbi, काष्ठा dnode_of_data *dn,
				block_t old_addr, block_t new_addr,
				अचिन्हित अक्षर version, bool recover_curseg,
				bool recover_newaddr)
अणु
	काष्ठा f2fs_summary sum;

	set_summary(&sum, dn->nid, dn->ofs_in_node, version);

	f2fs_करो_replace_block(sbi, &sum, old_addr, new_addr,
					recover_curseg, recover_newaddr, false);

	f2fs_update_data_blkaddr(dn, new_addr);
पूर्ण

व्योम f2fs_रुको_on_page_ग_लिखोback(काष्ठा page *page,
				क्रमागत page_type type, bool ordered, bool locked)
अणु
	अगर (PageWriteback(page)) अणु
		काष्ठा f2fs_sb_info *sbi = F2FS_P_SB(page);

		/* submit cached LFS IO */
		f2fs_submit_merged_ग_लिखो_cond(sbi, शून्य, page, 0, type);
		/* sbumit cached IPU IO */
		f2fs_submit_merged_ipu_ग_लिखो(sbi, शून्य, page);
		अगर (ordered) अणु
			रुको_on_page_ग_लिखोback(page);
			f2fs_bug_on(sbi, locked && PageWriteback(page));
		पूर्ण अन्यथा अणु
			रुको_क्रम_stable_page(page);
		पूर्ण
	पूर्ण
पूर्ण

व्योम f2fs_रुको_on_block_ग_लिखोback(काष्ठा inode *inode, block_t blkaddr)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा page *cpage;

	अगर (!f2fs_post_पढ़ो_required(inode))
		वापस;

	अगर (!__is_valid_data_blkaddr(blkaddr))
		वापस;

	cpage = find_lock_page(META_MAPPING(sbi), blkaddr);
	अगर (cpage) अणु
		f2fs_रुको_on_page_ग_लिखोback(cpage, DATA, true, true);
		f2fs_put_page(cpage, 1);
	पूर्ण
पूर्ण

व्योम f2fs_रुको_on_block_ग_लिखोback_range(काष्ठा inode *inode, block_t blkaddr,
								block_t len)
अणु
	block_t i;

	क्रम (i = 0; i < len; i++)
		f2fs_रुको_on_block_ग_लिखोback(inode, blkaddr + i);
पूर्ण

अटल पूर्णांक पढ़ो_compacted_summaries(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	काष्ठा curseg_info *seg_i;
	अचिन्हित अक्षर *kaddr;
	काष्ठा page *page;
	block_t start;
	पूर्णांक i, j, offset;

	start = start_sum_block(sbi);

	page = f2fs_get_meta_page(sbi, start++);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);
	kaddr = (अचिन्हित अक्षर *)page_address(page);

	/* Step 1: restore nat cache */
	seg_i = CURSEG_I(sbi, CURSEG_HOT_DATA);
	स_नकल(seg_i->journal, kaddr, SUM_JOURNAL_SIZE);

	/* Step 2: restore sit cache */
	seg_i = CURSEG_I(sbi, CURSEG_COLD_DATA);
	स_नकल(seg_i->journal, kaddr + SUM_JOURNAL_SIZE, SUM_JOURNAL_SIZE);
	offset = 2 * SUM_JOURNAL_SIZE;

	/* Step 3: restore summary entries */
	क्रम (i = CURSEG_HOT_DATA; i <= CURSEG_COLD_DATA; i++) अणु
		अचिन्हित लघु blk_off;
		अचिन्हित पूर्णांक segno;

		seg_i = CURSEG_I(sbi, i);
		segno = le32_to_cpu(ckpt->cur_data_segno[i]);
		blk_off = le16_to_cpu(ckpt->cur_data_blkoff[i]);
		seg_i->next_segno = segno;
		reset_curseg(sbi, i, 0);
		seg_i->alloc_type = ckpt->alloc_type[i];
		seg_i->next_blkoff = blk_off;

		अगर (seg_i->alloc_type == SSR)
			blk_off = sbi->blocks_per_seg;

		क्रम (j = 0; j < blk_off; j++) अणु
			काष्ठा f2fs_summary *s;

			s = (काष्ठा f2fs_summary *)(kaddr + offset);
			seg_i->sum_blk->entries[j] = *s;
			offset += SUMMARY_SIZE;
			अगर (offset + SUMMARY_SIZE <= PAGE_SIZE -
						SUM_FOOTER_SIZE)
				जारी;

			f2fs_put_page(page, 1);
			page = शून्य;

			page = f2fs_get_meta_page(sbi, start++);
			अगर (IS_ERR(page))
				वापस PTR_ERR(page);
			kaddr = (अचिन्हित अक्षर *)page_address(page);
			offset = 0;
		पूर्ण
	पूर्ण
	f2fs_put_page(page, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_normal_summaries(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	काष्ठा f2fs_summary_block *sum;
	काष्ठा curseg_info *curseg;
	काष्ठा page *new;
	अचिन्हित लघु blk_off;
	अचिन्हित पूर्णांक segno = 0;
	block_t blk_addr = 0;
	पूर्णांक err = 0;

	/* get segment number and block addr */
	अगर (IS_DATASEG(type)) अणु
		segno = le32_to_cpu(ckpt->cur_data_segno[type]);
		blk_off = le16_to_cpu(ckpt->cur_data_blkoff[type -
							CURSEG_HOT_DATA]);
		अगर (__exist_node_summaries(sbi))
			blk_addr = sum_blk_addr(sbi, NR_CURSEG_PERSIST_TYPE, type);
		अन्यथा
			blk_addr = sum_blk_addr(sbi, NR_CURSEG_DATA_TYPE, type);
	पूर्ण अन्यथा अणु
		segno = le32_to_cpu(ckpt->cur_node_segno[type -
							CURSEG_HOT_NODE]);
		blk_off = le16_to_cpu(ckpt->cur_node_blkoff[type -
							CURSEG_HOT_NODE]);
		अगर (__exist_node_summaries(sbi))
			blk_addr = sum_blk_addr(sbi, NR_CURSEG_NODE_TYPE,
							type - CURSEG_HOT_NODE);
		अन्यथा
			blk_addr = GET_SUM_BLOCK(sbi, segno);
	पूर्ण

	new = f2fs_get_meta_page(sbi, blk_addr);
	अगर (IS_ERR(new))
		वापस PTR_ERR(new);
	sum = (काष्ठा f2fs_summary_block *)page_address(new);

	अगर (IS_NODESEG(type)) अणु
		अगर (__exist_node_summaries(sbi)) अणु
			काष्ठा f2fs_summary *ns = &sum->entries[0];
			पूर्णांक i;

			क्रम (i = 0; i < sbi->blocks_per_seg; i++, ns++) अणु
				ns->version = 0;
				ns->ofs_in_node = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = f2fs_restore_node_summary(sbi, segno, sum);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

	/* set uncompleted segment to curseg */
	curseg = CURSEG_I(sbi, type);
	mutex_lock(&curseg->curseg_mutex);

	/* update journal info */
	करोwn_ग_लिखो(&curseg->journal_rwsem);
	स_नकल(curseg->journal, &sum->journal, SUM_JOURNAL_SIZE);
	up_ग_लिखो(&curseg->journal_rwsem);

	स_नकल(curseg->sum_blk->entries, sum->entries, SUM_ENTRY_SIZE);
	स_नकल(&curseg->sum_blk->footer, &sum->footer, SUM_FOOTER_SIZE);
	curseg->next_segno = segno;
	reset_curseg(sbi, type, 0);
	curseg->alloc_type = ckpt->alloc_type[type];
	curseg->next_blkoff = blk_off;
	mutex_unlock(&curseg->curseg_mutex);
out:
	f2fs_put_page(new, 1);
	वापस err;
पूर्ण

अटल पूर्णांक restore_curseg_summaries(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_journal *sit_j = CURSEG_I(sbi, CURSEG_COLD_DATA)->journal;
	काष्ठा f2fs_journal *nat_j = CURSEG_I(sbi, CURSEG_HOT_DATA)->journal;
	पूर्णांक type = CURSEG_HOT_DATA;
	पूर्णांक err;

	अगर (is_set_ckpt_flags(sbi, CP_COMPACT_SUM_FLAG)) अणु
		पूर्णांक npages = f2fs_npages_क्रम_summary_flush(sbi, true);

		अगर (npages >= 2)
			f2fs_ra_meta_pages(sbi, start_sum_block(sbi), npages,
							META_CP, true);

		/* restore क्रम compacted data summary */
		err = पढ़ो_compacted_summaries(sbi);
		अगर (err)
			वापस err;
		type = CURSEG_HOT_NODE;
	पूर्ण

	अगर (__exist_node_summaries(sbi))
		f2fs_ra_meta_pages(sbi,
				sum_blk_addr(sbi, NR_CURSEG_PERSIST_TYPE, type),
				NR_CURSEG_PERSIST_TYPE - type, META_CP, true);

	क्रम (; type <= CURSEG_COLD_NODE; type++) अणु
		err = पढ़ो_normal_summaries(sbi, type);
		अगर (err)
			वापस err;
	पूर्ण

	/* sanity check क्रम summary blocks */
	अगर (nats_in_cursum(nat_j) > NAT_JOURNAL_ENTRIES ||
			sits_in_cursum(sit_j) > SIT_JOURNAL_ENTRIES) अणु
		f2fs_err(sbi, "invalid journal entries nats %u sits %u\n",
			 nats_in_cursum(nat_j), sits_in_cursum(sit_j));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ग_लिखो_compacted_summaries(काष्ठा f2fs_sb_info *sbi, block_t blkaddr)
अणु
	काष्ठा page *page;
	अचिन्हित अक्षर *kaddr;
	काष्ठा f2fs_summary *summary;
	काष्ठा curseg_info *seg_i;
	पूर्णांक written_size = 0;
	पूर्णांक i, j;

	page = f2fs_grab_meta_page(sbi, blkaddr++);
	kaddr = (अचिन्हित अक्षर *)page_address(page);
	स_रखो(kaddr, 0, PAGE_SIZE);

	/* Step 1: ग_लिखो nat cache */
	seg_i = CURSEG_I(sbi, CURSEG_HOT_DATA);
	स_नकल(kaddr, seg_i->journal, SUM_JOURNAL_SIZE);
	written_size += SUM_JOURNAL_SIZE;

	/* Step 2: ग_लिखो sit cache */
	seg_i = CURSEG_I(sbi, CURSEG_COLD_DATA);
	स_नकल(kaddr + written_size, seg_i->journal, SUM_JOURNAL_SIZE);
	written_size += SUM_JOURNAL_SIZE;

	/* Step 3: ग_लिखो summary entries */
	क्रम (i = CURSEG_HOT_DATA; i <= CURSEG_COLD_DATA; i++) अणु
		अचिन्हित लघु blkoff;

		seg_i = CURSEG_I(sbi, i);
		अगर (sbi->ckpt->alloc_type[i] == SSR)
			blkoff = sbi->blocks_per_seg;
		अन्यथा
			blkoff = curseg_blkoff(sbi, i);

		क्रम (j = 0; j < blkoff; j++) अणु
			अगर (!page) अणु
				page = f2fs_grab_meta_page(sbi, blkaddr++);
				kaddr = (अचिन्हित अक्षर *)page_address(page);
				स_रखो(kaddr, 0, PAGE_SIZE);
				written_size = 0;
			पूर्ण
			summary = (काष्ठा f2fs_summary *)(kaddr + written_size);
			*summary = seg_i->sum_blk->entries[j];
			written_size += SUMMARY_SIZE;

			अगर (written_size + SUMMARY_SIZE <= PAGE_SIZE -
							SUM_FOOTER_SIZE)
				जारी;

			set_page_dirty(page);
			f2fs_put_page(page, 1);
			page = शून्य;
		पूर्ण
	पूर्ण
	अगर (page) अणु
		set_page_dirty(page);
		f2fs_put_page(page, 1);
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_normal_summaries(काष्ठा f2fs_sb_info *sbi,
					block_t blkaddr, पूर्णांक type)
अणु
	पूर्णांक i, end;

	अगर (IS_DATASEG(type))
		end = type + NR_CURSEG_DATA_TYPE;
	अन्यथा
		end = type + NR_CURSEG_NODE_TYPE;

	क्रम (i = type; i < end; i++)
		ग_लिखो_current_sum_page(sbi, i, blkaddr + (i - type));
पूर्ण

व्योम f2fs_ग_लिखो_data_summaries(काष्ठा f2fs_sb_info *sbi, block_t start_blk)
अणु
	अगर (is_set_ckpt_flags(sbi, CP_COMPACT_SUM_FLAG))
		ग_लिखो_compacted_summaries(sbi, start_blk);
	अन्यथा
		ग_लिखो_normal_summaries(sbi, start_blk, CURSEG_HOT_DATA);
पूर्ण

व्योम f2fs_ग_लिखो_node_summaries(काष्ठा f2fs_sb_info *sbi, block_t start_blk)
अणु
	ग_लिखो_normal_summaries(sbi, start_blk, CURSEG_HOT_NODE);
पूर्ण

पूर्णांक f2fs_lookup_journal_in_cursum(काष्ठा f2fs_journal *journal, पूर्णांक type,
					अचिन्हित पूर्णांक val, पूर्णांक alloc)
अणु
	पूर्णांक i;

	अगर (type == NAT_JOURNAL) अणु
		क्रम (i = 0; i < nats_in_cursum(journal); i++) अणु
			अगर (le32_to_cpu(nid_in_journal(journal, i)) == val)
				वापस i;
		पूर्ण
		अगर (alloc && __has_cursum_space(journal, 1, NAT_JOURNAL))
			वापस update_nats_in_cursum(journal, 1);
	पूर्ण अन्यथा अगर (type == SIT_JOURNAL) अणु
		क्रम (i = 0; i < sits_in_cursum(journal); i++)
			अगर (le32_to_cpu(segno_in_journal(journal, i)) == val)
				वापस i;
		अगर (alloc && __has_cursum_space(journal, 1, SIT_JOURNAL))
			वापस update_sits_in_cursum(journal, 1);
	पूर्ण
	वापस -1;
पूर्ण

अटल काष्ठा page *get_current_sit_page(काष्ठा f2fs_sb_info *sbi,
					अचिन्हित पूर्णांक segno)
अणु
	वापस f2fs_get_meta_page(sbi, current_sit_addr(sbi, segno));
पूर्ण

अटल काष्ठा page *get_next_sit_page(काष्ठा f2fs_sb_info *sbi,
					अचिन्हित पूर्णांक start)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	काष्ठा page *page;
	pgoff_t src_off, dst_off;

	src_off = current_sit_addr(sbi, start);
	dst_off = next_sit_addr(sbi, src_off);

	page = f2fs_grab_meta_page(sbi, dst_off);
	seg_info_to_sit_page(sbi, page, start);

	set_page_dirty(page);
	set_to_next_sit(sit_i, start);

	वापस page;
पूर्ण

अटल काष्ठा sit_entry_set *grab_sit_entry_set(व्योम)
अणु
	काष्ठा sit_entry_set *ses =
			f2fs_kmem_cache_alloc(sit_entry_set_slab, GFP_NOFS);

	ses->entry_cnt = 0;
	INIT_LIST_HEAD(&ses->set_list);
	वापस ses;
पूर्ण

अटल व्योम release_sit_entry_set(काष्ठा sit_entry_set *ses)
अणु
	list_del(&ses->set_list);
	kmem_cache_मुक्त(sit_entry_set_slab, ses);
पूर्ण

अटल व्योम adjust_sit_entry_set(काष्ठा sit_entry_set *ses,
						काष्ठा list_head *head)
अणु
	काष्ठा sit_entry_set *next = ses;

	अगर (list_is_last(&ses->set_list, head))
		वापस;

	list_क्रम_each_entry_जारी(next, head, set_list)
		अगर (ses->entry_cnt <= next->entry_cnt)
			अवरोध;

	list_move_tail(&ses->set_list, &next->set_list);
पूर्ण

अटल व्योम add_sit_entry(अचिन्हित पूर्णांक segno, काष्ठा list_head *head)
अणु
	काष्ठा sit_entry_set *ses;
	अचिन्हित पूर्णांक start_segno = START_SEGNO(segno);

	list_क्रम_each_entry(ses, head, set_list) अणु
		अगर (ses->start_segno == start_segno) अणु
			ses->entry_cnt++;
			adjust_sit_entry_set(ses, head);
			वापस;
		पूर्ण
	पूर्ण

	ses = grab_sit_entry_set();

	ses->start_segno = start_segno;
	ses->entry_cnt++;
	list_add(&ses->set_list, head);
पूर्ण

अटल व्योम add_sits_in_set(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_sm_info *sm_info = SM_I(sbi);
	काष्ठा list_head *set_list = &sm_info->sit_entry_set;
	अचिन्हित दीर्घ *biपंचांगap = SIT_I(sbi)->dirty_sentries_biपंचांगap;
	अचिन्हित पूर्णांक segno;

	क्रम_each_set_bit(segno, biपंचांगap, MAIN_SEGS(sbi))
		add_sit_entry(segno, set_list);
पूर्ण

अटल व्योम हटाओ_sits_in_journal(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, CURSEG_COLD_DATA);
	काष्ठा f2fs_journal *journal = curseg->journal;
	पूर्णांक i;

	करोwn_ग_लिखो(&curseg->journal_rwsem);
	क्रम (i = 0; i < sits_in_cursum(journal); i++) अणु
		अचिन्हित पूर्णांक segno;
		bool dirtied;

		segno = le32_to_cpu(segno_in_journal(journal, i));
		dirtied = __mark_sit_entry_dirty(sbi, segno);

		अगर (!dirtied)
			add_sit_entry(segno, &SM_I(sbi)->sit_entry_set);
	पूर्ण
	update_sits_in_cursum(journal, -i);
	up_ग_लिखो(&curseg->journal_rwsem);
पूर्ण

/*
 * CP calls this function, which flushes SIT entries including sit_journal,
 * and moves preमुक्त segs to मुक्त segs.
 */
व्योम f2fs_flush_sit_entries(काष्ठा f2fs_sb_info *sbi, काष्ठा cp_control *cpc)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	अचिन्हित दीर्घ *biपंचांगap = sit_i->dirty_sentries_biपंचांगap;
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, CURSEG_COLD_DATA);
	काष्ठा f2fs_journal *journal = curseg->journal;
	काष्ठा sit_entry_set *ses, *पंचांगp;
	काष्ठा list_head *head = &SM_I(sbi)->sit_entry_set;
	bool to_journal = !is_sbi_flag_set(sbi, SBI_IS_RESIZEFS);
	काष्ठा seg_entry *se;

	करोwn_ग_लिखो(&sit_i->sentry_lock);

	अगर (!sit_i->dirty_sentries)
		जाओ out;

	/*
	 * add and account sit entries of dirty biपंचांगap in sit entry
	 * set temporarily
	 */
	add_sits_in_set(sbi);

	/*
	 * अगर there are no enough space in journal to store dirty sit
	 * entries, हटाओ all entries from journal and add and account
	 * them in sit entry set.
	 */
	अगर (!__has_cursum_space(journal, sit_i->dirty_sentries, SIT_JOURNAL) ||
								!to_journal)
		हटाओ_sits_in_journal(sbi);

	/*
	 * there are two steps to flush sit entries:
	 * #1, flush sit entries to journal in current cold data summary block.
	 * #2, flush sit entries to sit page.
	 */
	list_क्रम_each_entry_safe(ses, पंचांगp, head, set_list) अणु
		काष्ठा page *page = शून्य;
		काष्ठा f2fs_sit_block *raw_sit = शून्य;
		अचिन्हित पूर्णांक start_segno = ses->start_segno;
		अचिन्हित पूर्णांक end = min(start_segno + SIT_ENTRY_PER_BLOCK,
						(अचिन्हित दीर्घ)MAIN_SEGS(sbi));
		अचिन्हित पूर्णांक segno = start_segno;

		अगर (to_journal &&
			!__has_cursum_space(journal, ses->entry_cnt, SIT_JOURNAL))
			to_journal = false;

		अगर (to_journal) अणु
			करोwn_ग_लिखो(&curseg->journal_rwsem);
		पूर्ण अन्यथा अणु
			page = get_next_sit_page(sbi, start_segno);
			raw_sit = page_address(page);
		पूर्ण

		/* flush dirty sit entries in region of current sit set */
		क्रम_each_set_bit_from(segno, biपंचांगap, end) अणु
			पूर्णांक offset, sit_offset;

			se = get_seg_entry(sbi, segno);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
			अगर (स_भेद(se->cur_valid_map, se->cur_valid_map_mir,
						SIT_VBLOCK_MAP_SIZE))
				f2fs_bug_on(sbi, 1);
#पूर्ण_अगर

			/* add discard candidates */
			अगर (!(cpc->reason & CP_DISCARD)) अणु
				cpc->trim_start = segno;
				add_discard_addrs(sbi, cpc, false);
			पूर्ण

			अगर (to_journal) अणु
				offset = f2fs_lookup_journal_in_cursum(journal,
							SIT_JOURNAL, segno, 1);
				f2fs_bug_on(sbi, offset < 0);
				segno_in_journal(journal, offset) =
							cpu_to_le32(segno);
				seg_info_to_raw_sit(se,
					&sit_in_journal(journal, offset));
				check_block_count(sbi, segno,
					&sit_in_journal(journal, offset));
			पूर्ण अन्यथा अणु
				sit_offset = SIT_ENTRY_OFFSET(sit_i, segno);
				seg_info_to_raw_sit(se,
						&raw_sit->entries[sit_offset]);
				check_block_count(sbi, segno,
						&raw_sit->entries[sit_offset]);
			पूर्ण

			__clear_bit(segno, biपंचांगap);
			sit_i->dirty_sentries--;
			ses->entry_cnt--;
		पूर्ण

		अगर (to_journal)
			up_ग_लिखो(&curseg->journal_rwsem);
		अन्यथा
			f2fs_put_page(page, 1);

		f2fs_bug_on(sbi, ses->entry_cnt);
		release_sit_entry_set(ses);
	पूर्ण

	f2fs_bug_on(sbi, !list_empty(head));
	f2fs_bug_on(sbi, sit_i->dirty_sentries);
out:
	अगर (cpc->reason & CP_DISCARD) अणु
		__u64 trim_start = cpc->trim_start;

		क्रम (; cpc->trim_start <= cpc->trim_end; cpc->trim_start++)
			add_discard_addrs(sbi, cpc, false);

		cpc->trim_start = trim_start;
	पूर्ण
	up_ग_लिखो(&sit_i->sentry_lock);

	set_preमुक्त_as_मुक्त_segments(sbi);
पूर्ण

अटल पूर्णांक build_sit_info(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_super_block *raw_super = F2FS_RAW_SUPER(sbi);
	काष्ठा sit_info *sit_i;
	अचिन्हित पूर्णांक sit_segs, start;
	अक्षर *src_biपंचांगap, *biपंचांगap;
	अचिन्हित पूर्णांक biपंचांगap_size, मुख्य_biपंचांगap_size, sit_biपंचांगap_size;

	/* allocate memory क्रम SIT inक्रमmation */
	sit_i = f2fs_kzalloc(sbi, माप(काष्ठा sit_info), GFP_KERNEL);
	अगर (!sit_i)
		वापस -ENOMEM;

	SM_I(sbi)->sit_info = sit_i;

	sit_i->sentries =
		f2fs_kvzalloc(sbi, array_size(माप(काष्ठा seg_entry),
					      MAIN_SEGS(sbi)),
			      GFP_KERNEL);
	अगर (!sit_i->sentries)
		वापस -ENOMEM;

	मुख्य_biपंचांगap_size = f2fs_biपंचांगap_size(MAIN_SEGS(sbi));
	sit_i->dirty_sentries_biपंचांगap = f2fs_kvzalloc(sbi, मुख्य_biपंचांगap_size,
								GFP_KERNEL);
	अगर (!sit_i->dirty_sentries_biपंचांगap)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	biपंचांगap_size = MAIN_SEGS(sbi) * SIT_VBLOCK_MAP_SIZE * 4;
#अन्यथा
	biपंचांगap_size = MAIN_SEGS(sbi) * SIT_VBLOCK_MAP_SIZE * 3;
#पूर्ण_अगर
	sit_i->biपंचांगap = f2fs_kvzalloc(sbi, biपंचांगap_size, GFP_KERNEL);
	अगर (!sit_i->biपंचांगap)
		वापस -ENOMEM;

	biपंचांगap = sit_i->biपंचांगap;

	क्रम (start = 0; start < MAIN_SEGS(sbi); start++) अणु
		sit_i->sentries[start].cur_valid_map = biपंचांगap;
		biपंचांगap += SIT_VBLOCK_MAP_SIZE;

		sit_i->sentries[start].ckpt_valid_map = biपंचांगap;
		biपंचांगap += SIT_VBLOCK_MAP_SIZE;

#अगर_घोषित CONFIG_F2FS_CHECK_FS
		sit_i->sentries[start].cur_valid_map_mir = biपंचांगap;
		biपंचांगap += SIT_VBLOCK_MAP_SIZE;
#पूर्ण_अगर

		sit_i->sentries[start].discard_map = biपंचांगap;
		biपंचांगap += SIT_VBLOCK_MAP_SIZE;
	पूर्ण

	sit_i->पंचांगp_map = f2fs_kzalloc(sbi, SIT_VBLOCK_MAP_SIZE, GFP_KERNEL);
	अगर (!sit_i->पंचांगp_map)
		वापस -ENOMEM;

	अगर (__is_large_section(sbi)) अणु
		sit_i->sec_entries =
			f2fs_kvzalloc(sbi, array_size(माप(काष्ठा sec_entry),
						      MAIN_SECS(sbi)),
				      GFP_KERNEL);
		अगर (!sit_i->sec_entries)
			वापस -ENOMEM;
	पूर्ण

	/* get inक्रमmation related with SIT */
	sit_segs = le32_to_cpu(raw_super->segment_count_sit) >> 1;

	/* setup SIT biपंचांगap from ckeckpoपूर्णांक pack */
	sit_biपंचांगap_size = __biपंचांगap_size(sbi, SIT_BITMAP);
	src_biपंचांगap = __biपंचांगap_ptr(sbi, SIT_BITMAP);

	sit_i->sit_biपंचांगap = kmemdup(src_biपंचांगap, sit_biपंचांगap_size, GFP_KERNEL);
	अगर (!sit_i->sit_biपंचांगap)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	sit_i->sit_biपंचांगap_mir = kmemdup(src_biपंचांगap,
					sit_biपंचांगap_size, GFP_KERNEL);
	अगर (!sit_i->sit_biपंचांगap_mir)
		वापस -ENOMEM;

	sit_i->invalid_segmap = f2fs_kvzalloc(sbi,
					मुख्य_biपंचांगap_size, GFP_KERNEL);
	अगर (!sit_i->invalid_segmap)
		वापस -ENOMEM;
#पूर्ण_अगर

	/* init SIT inक्रमmation */
	sit_i->s_ops = &शेष_salloc_ops;

	sit_i->sit_base_addr = le32_to_cpu(raw_super->sit_blkaddr);
	sit_i->sit_blocks = sit_segs << sbi->log_blocks_per_seg;
	sit_i->written_valid_blocks = 0;
	sit_i->biपंचांगap_size = sit_biपंचांगap_size;
	sit_i->dirty_sentries = 0;
	sit_i->sents_per_block = SIT_ENTRY_PER_BLOCK;
	sit_i->elapsed_समय = le64_to_cpu(sbi->ckpt->elapsed_समय);
	sit_i->mounted_समय = kसमय_get_bootसमय_seconds();
	init_rwsem(&sit_i->sentry_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक build_मुक्त_segmap(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा मुक्त_segmap_info *मुक्त_i;
	अचिन्हित पूर्णांक biपंचांगap_size, sec_biपंचांगap_size;

	/* allocate memory क्रम मुक्त segmap inक्रमmation */
	मुक्त_i = f2fs_kzalloc(sbi, माप(काष्ठा मुक्त_segmap_info), GFP_KERNEL);
	अगर (!मुक्त_i)
		वापस -ENOMEM;

	SM_I(sbi)->मुक्त_info = मुक्त_i;

	biपंचांगap_size = f2fs_biपंचांगap_size(MAIN_SEGS(sbi));
	मुक्त_i->मुक्त_segmap = f2fs_kvदो_स्मृति(sbi, biपंचांगap_size, GFP_KERNEL);
	अगर (!मुक्त_i->मुक्त_segmap)
		वापस -ENOMEM;

	sec_biपंचांगap_size = f2fs_biपंचांगap_size(MAIN_SECS(sbi));
	मुक्त_i->मुक्त_secmap = f2fs_kvदो_स्मृति(sbi, sec_biपंचांगap_size, GFP_KERNEL);
	अगर (!मुक्त_i->मुक्त_secmap)
		वापस -ENOMEM;

	/* set all segments as dirty temporarily */
	स_रखो(मुक्त_i->मुक्त_segmap, 0xff, biपंचांगap_size);
	स_रखो(मुक्त_i->मुक्त_secmap, 0xff, sec_biपंचांगap_size);

	/* init मुक्त segmap inक्रमmation */
	मुक्त_i->start_segno = GET_SEGNO_FROM_SEG0(sbi, MAIN_BLKADDR(sbi));
	मुक्त_i->मुक्त_segments = 0;
	मुक्त_i->मुक्त_sections = 0;
	spin_lock_init(&मुक्त_i->segmap_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक build_curseg(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा curseg_info *array;
	पूर्णांक i;

	array = f2fs_kzalloc(sbi, array_size(NR_CURSEG_TYPE,
					माप(*array)), GFP_KERNEL);
	अगर (!array)
		वापस -ENOMEM;

	SM_I(sbi)->curseg_array = array;

	क्रम (i = 0; i < NO_CHECK_TYPE; i++) अणु
		mutex_init(&array[i].curseg_mutex);
		array[i].sum_blk = f2fs_kzalloc(sbi, PAGE_SIZE, GFP_KERNEL);
		अगर (!array[i].sum_blk)
			वापस -ENOMEM;
		init_rwsem(&array[i].journal_rwsem);
		array[i].journal = f2fs_kzalloc(sbi,
				माप(काष्ठा f2fs_journal), GFP_KERNEL);
		अगर (!array[i].journal)
			वापस -ENOMEM;
		अगर (i < NR_PERSISTENT_LOG)
			array[i].seg_type = CURSEG_HOT_DATA + i;
		अन्यथा अगर (i == CURSEG_COLD_DATA_PINNED)
			array[i].seg_type = CURSEG_COLD_DATA;
		अन्यथा अगर (i == CURSEG_ALL_DATA_ATGC)
			array[i].seg_type = CURSEG_COLD_DATA;
		array[i].segno = शून्य_SEGNO;
		array[i].next_blkoff = 0;
		array[i].inited = false;
	पूर्ण
	वापस restore_curseg_summaries(sbi);
पूर्ण

अटल पूर्णांक build_sit_entries(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, CURSEG_COLD_DATA);
	काष्ठा f2fs_journal *journal = curseg->journal;
	काष्ठा seg_entry *se;
	काष्ठा f2fs_sit_entry sit;
	पूर्णांक sit_blk_cnt = SIT_BLK_CNT(sbi);
	अचिन्हित पूर्णांक i, start, end;
	अचिन्हित पूर्णांक पढ़ोed, start_blk = 0;
	पूर्णांक err = 0;
	block_t total_node_blocks = 0;

	करो अणु
		पढ़ोed = f2fs_ra_meta_pages(sbi, start_blk, BIO_MAX_VECS,
							META_SIT, true);

		start = start_blk * sit_i->sents_per_block;
		end = (start_blk + पढ़ोed) * sit_i->sents_per_block;

		क्रम (; start < end && start < MAIN_SEGS(sbi); start++) अणु
			काष्ठा f2fs_sit_block *sit_blk;
			काष्ठा page *page;

			se = &sit_i->sentries[start];
			page = get_current_sit_page(sbi, start);
			अगर (IS_ERR(page))
				वापस PTR_ERR(page);
			sit_blk = (काष्ठा f2fs_sit_block *)page_address(page);
			sit = sit_blk->entries[SIT_ENTRY_OFFSET(sit_i, start)];
			f2fs_put_page(page, 1);

			err = check_block_count(sbi, start, &sit);
			अगर (err)
				वापस err;
			seg_info_from_raw_sit(se, &sit);
			अगर (IS_NODESEG(se->type))
				total_node_blocks += se->valid_blocks;

			/* build discard map only one समय */
			अगर (is_set_ckpt_flags(sbi, CP_TRIMMED_FLAG)) अणु
				स_रखो(se->discard_map, 0xff,
					SIT_VBLOCK_MAP_SIZE);
			पूर्ण अन्यथा अणु
				स_नकल(se->discard_map,
					se->cur_valid_map,
					SIT_VBLOCK_MAP_SIZE);
				sbi->discard_blks +=
					sbi->blocks_per_seg -
					se->valid_blocks;
			पूर्ण

			अगर (__is_large_section(sbi))
				get_sec_entry(sbi, start)->valid_blocks +=
							se->valid_blocks;
		पूर्ण
		start_blk += पढ़ोed;
	पूर्ण जबतक (start_blk < sit_blk_cnt);

	करोwn_पढ़ो(&curseg->journal_rwsem);
	क्रम (i = 0; i < sits_in_cursum(journal); i++) अणु
		अचिन्हित पूर्णांक old_valid_blocks;

		start = le32_to_cpu(segno_in_journal(journal, i));
		अगर (start >= MAIN_SEGS(sbi)) अणु
			f2fs_err(sbi, "Wrong journal entry on segno %u",
				 start);
			err = -EFSCORRUPTED;
			अवरोध;
		पूर्ण

		se = &sit_i->sentries[start];
		sit = sit_in_journal(journal, i);

		old_valid_blocks = se->valid_blocks;
		अगर (IS_NODESEG(se->type))
			total_node_blocks -= old_valid_blocks;

		err = check_block_count(sbi, start, &sit);
		अगर (err)
			अवरोध;
		seg_info_from_raw_sit(se, &sit);
		अगर (IS_NODESEG(se->type))
			total_node_blocks += se->valid_blocks;

		अगर (is_set_ckpt_flags(sbi, CP_TRIMMED_FLAG)) अणु
			स_रखो(se->discard_map, 0xff, SIT_VBLOCK_MAP_SIZE);
		पूर्ण अन्यथा अणु
			स_नकल(se->discard_map, se->cur_valid_map,
						SIT_VBLOCK_MAP_SIZE);
			sbi->discard_blks += old_valid_blocks;
			sbi->discard_blks -= se->valid_blocks;
		पूर्ण

		अगर (__is_large_section(sbi)) अणु
			get_sec_entry(sbi, start)->valid_blocks +=
							se->valid_blocks;
			get_sec_entry(sbi, start)->valid_blocks -=
							old_valid_blocks;
		पूर्ण
	पूर्ण
	up_पढ़ो(&curseg->journal_rwsem);

	अगर (!err && total_node_blocks != valid_node_count(sbi)) अणु
		f2fs_err(sbi, "SIT is corrupted node# %u vs %u",
			 total_node_blocks, valid_node_count(sbi));
		err = -EFSCORRUPTED;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम init_मुक्त_segmap(काष्ठा f2fs_sb_info *sbi)
अणु
	अचिन्हित पूर्णांक start;
	पूर्णांक type;
	काष्ठा seg_entry *sentry;

	क्रम (start = 0; start < MAIN_SEGS(sbi); start++) अणु
		अगर (f2fs_usable_blks_in_seg(sbi, start) == 0)
			जारी;
		sentry = get_seg_entry(sbi, start);
		अगर (!sentry->valid_blocks)
			__set_मुक्त(sbi, start);
		अन्यथा
			SIT_I(sbi)->written_valid_blocks +=
						sentry->valid_blocks;
	पूर्ण

	/* set use the current segments */
	क्रम (type = CURSEG_HOT_DATA; type <= CURSEG_COLD_NODE; type++) अणु
		काष्ठा curseg_info *curseg_t = CURSEG_I(sbi, type);

		__set_test_and_inuse(sbi, curseg_t->segno);
	पूर्ण
पूर्ण

अटल व्योम init_dirty_segmap(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	काष्ठा मुक्त_segmap_info *मुक्त_i = FREE_I(sbi);
	अचिन्हित पूर्णांक segno = 0, offset = 0, secno;
	block_t valid_blocks, usable_blks_in_seg;
	block_t blks_per_sec = BLKS_PER_SEC(sbi);

	जबतक (1) अणु
		/* find dirty segment based on मुक्त segmap */
		segno = find_next_inuse(मुक्त_i, MAIN_SEGS(sbi), offset);
		अगर (segno >= MAIN_SEGS(sbi))
			अवरोध;
		offset = segno + 1;
		valid_blocks = get_valid_blocks(sbi, segno, false);
		usable_blks_in_seg = f2fs_usable_blks_in_seg(sbi, segno);
		अगर (valid_blocks == usable_blks_in_seg || !valid_blocks)
			जारी;
		अगर (valid_blocks > usable_blks_in_seg) अणु
			f2fs_bug_on(sbi, 1);
			जारी;
		पूर्ण
		mutex_lock(&dirty_i->seglist_lock);
		__locate_dirty_segment(sbi, segno, सूचीTY);
		mutex_unlock(&dirty_i->seglist_lock);
	पूर्ण

	अगर (!__is_large_section(sbi))
		वापस;

	mutex_lock(&dirty_i->seglist_lock);
	क्रम (segno = 0; segno < MAIN_SEGS(sbi); segno += sbi->segs_per_sec) अणु
		valid_blocks = get_valid_blocks(sbi, segno, true);
		secno = GET_SEC_FROM_SEG(sbi, segno);

		अगर (!valid_blocks || valid_blocks == blks_per_sec)
			जारी;
		अगर (IS_CURSEC(sbi, secno))
			जारी;
		set_bit(secno, dirty_i->dirty_secmap);
	पूर्ण
	mutex_unlock(&dirty_i->seglist_lock);
पूर्ण

अटल पूर्णांक init_victim_secmap(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	अचिन्हित पूर्णांक biपंचांगap_size = f2fs_biपंचांगap_size(MAIN_SECS(sbi));

	dirty_i->victim_secmap = f2fs_kvzalloc(sbi, biपंचांगap_size, GFP_KERNEL);
	अगर (!dirty_i->victim_secmap)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक build_dirty_segmap(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा dirty_seglist_info *dirty_i;
	अचिन्हित पूर्णांक biपंचांगap_size, i;

	/* allocate memory क्रम dirty segments list inक्रमmation */
	dirty_i = f2fs_kzalloc(sbi, माप(काष्ठा dirty_seglist_info),
								GFP_KERNEL);
	अगर (!dirty_i)
		वापस -ENOMEM;

	SM_I(sbi)->dirty_info = dirty_i;
	mutex_init(&dirty_i->seglist_lock);

	biपंचांगap_size = f2fs_biपंचांगap_size(MAIN_SEGS(sbi));

	क्रम (i = 0; i < NR_सूचीTY_TYPE; i++) अणु
		dirty_i->dirty_segmap[i] = f2fs_kvzalloc(sbi, biपंचांगap_size,
								GFP_KERNEL);
		अगर (!dirty_i->dirty_segmap[i])
			वापस -ENOMEM;
	पूर्ण

	अगर (__is_large_section(sbi)) अणु
		biपंचांगap_size = f2fs_biपंचांगap_size(MAIN_SECS(sbi));
		dirty_i->dirty_secmap = f2fs_kvzalloc(sbi,
						biपंचांगap_size, GFP_KERNEL);
		अगर (!dirty_i->dirty_secmap)
			वापस -ENOMEM;
	पूर्ण

	init_dirty_segmap(sbi);
	वापस init_victim_secmap(sbi);
पूर्ण

अटल पूर्णांक sanity_check_curseg(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक i;

	/*
	 * In LFS/SSR curseg, .next_blkoff should poपूर्णांक to an unused blkaddr;
	 * In LFS curseg, all blkaddr after .next_blkoff should be unused.
	 */
	क्रम (i = 0; i < NR_PERSISTENT_LOG; i++) अणु
		काष्ठा curseg_info *curseg = CURSEG_I(sbi, i);
		काष्ठा seg_entry *se = get_seg_entry(sbi, curseg->segno);
		अचिन्हित पूर्णांक blkofs = curseg->next_blkoff;

		sanity_check_seg_type(sbi, curseg->seg_type);

		अगर (f2fs_test_bit(blkofs, se->cur_valid_map))
			जाओ out;

		अगर (curseg->alloc_type == SSR)
			जारी;

		क्रम (blkofs += 1; blkofs < sbi->blocks_per_seg; blkofs++) अणु
			अगर (!f2fs_test_bit(blkofs, se->cur_valid_map))
				जारी;
out:
			f2fs_err(sbi,
				 "Current segment's next free block offset is inconsistent with bitmap, logtype:%u, segno:%u, type:%u, next_blkoff:%u, blkofs:%u",
				 i, curseg->segno, curseg->alloc_type,
				 curseg->next_blkoff, blkofs);
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED

अटल पूर्णांक check_zone_ग_लिखो_poपूर्णांकer(काष्ठा f2fs_sb_info *sbi,
				    काष्ठा f2fs_dev_info *fdev,
				    काष्ठा blk_zone *zone)
अणु
	अचिन्हित पूर्णांक wp_segno, wp_blkoff, zone_secno, zone_segno, segno;
	block_t zone_block, wp_block, last_valid_block;
	अचिन्हित पूर्णांक log_sectors_per_block = sbi->log_blocksize - SECTOR_SHIFT;
	पूर्णांक i, s, b, ret;
	काष्ठा seg_entry *se;

	अगर (zone->type != BLK_ZONE_TYPE_SEQWRITE_REQ)
		वापस 0;

	wp_block = fdev->start_blk + (zone->wp >> log_sectors_per_block);
	wp_segno = GET_SEGNO(sbi, wp_block);
	wp_blkoff = wp_block - START_BLOCK(sbi, wp_segno);
	zone_block = fdev->start_blk + (zone->start >> log_sectors_per_block);
	zone_segno = GET_SEGNO(sbi, zone_block);
	zone_secno = GET_SEC_FROM_SEG(sbi, zone_segno);

	अगर (zone_segno >= MAIN_SEGS(sbi))
		वापस 0;

	/*
	 * Skip check of zones cursegs poपूर्णांक to, since
	 * fix_curseg_ग_लिखो_poपूर्णांकer() checks them.
	 */
	क्रम (i = 0; i < NO_CHECK_TYPE; i++)
		अगर (zone_secno == GET_SEC_FROM_SEG(sbi,
						   CURSEG_I(sbi, i)->segno))
			वापस 0;

	/*
	 * Get last valid block of the zone.
	 */
	last_valid_block = zone_block - 1;
	क्रम (s = sbi->segs_per_sec - 1; s >= 0; s--) अणु
		segno = zone_segno + s;
		se = get_seg_entry(sbi, segno);
		क्रम (b = sbi->blocks_per_seg - 1; b >= 0; b--)
			अगर (f2fs_test_bit(b, se->cur_valid_map)) अणु
				last_valid_block = START_BLOCK(sbi, segno) + b;
				अवरोध;
			पूर्ण
		अगर (last_valid_block >= zone_block)
			अवरोध;
	पूर्ण

	/*
	 * If last valid block is beyond the ग_लिखो poपूर्णांकer, report the
	 * inconsistency. This inconsistency करोes not cause ग_लिखो error
	 * because the zone will not be selected क्रम ग_लिखो operation until
	 * it get discarded. Just report it.
	 */
	अगर (last_valid_block >= wp_block) अणु
		f2fs_notice(sbi, "Valid block beyond write pointer: "
			    "valid block[0x%x,0x%x] wp[0x%x,0x%x]",
			    GET_SEGNO(sbi, last_valid_block),
			    GET_BLKOFF_FROM_SEG0(sbi, last_valid_block),
			    wp_segno, wp_blkoff);
		वापस 0;
	पूर्ण

	/*
	 * If there is no valid block in the zone and अगर ग_लिखो poपूर्णांकer is
	 * not at zone start, reset the ग_लिखो poपूर्णांकer.
	 */
	अगर (last_valid_block + 1 == zone_block && zone->wp != zone->start) अणु
		f2fs_notice(sbi,
			    "Zone without valid block has non-zero write "
			    "pointer. Reset the write pointer: wp[0x%x,0x%x]",
			    wp_segno, wp_blkoff);
		ret = __f2fs_issue_discard_zone(sbi, fdev->bdev, zone_block,
					zone->len >> log_sectors_per_block);
		अगर (ret) अणु
			f2fs_err(sbi, "Discard zone failed: %s (errno=%d)",
				 fdev->path, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा f2fs_dev_info *get_target_zoned_dev(काष्ठा f2fs_sb_info *sbi,
						  block_t zone_blkaddr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sbi->s_ndevs; i++) अणु
		अगर (!bdev_is_zoned(FDEV(i).bdev))
			जारी;
		अगर (sbi->s_ndevs == 1 || (FDEV(i).start_blk <= zone_blkaddr &&
				zone_blkaddr <= FDEV(i).end_blk))
			वापस &FDEV(i);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक report_one_zone_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx,
			      व्योम *data)
अणु
	स_नकल(data, zone, माप(काष्ठा blk_zone));
	वापस 0;
पूर्ण

अटल पूर्णांक fix_curseg_ग_लिखो_poपूर्णांकer(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	काष्ठा curseg_info *cs = CURSEG_I(sbi, type);
	काष्ठा f2fs_dev_info *zbd;
	काष्ठा blk_zone zone;
	अचिन्हित पूर्णांक cs_section, wp_segno, wp_blkoff, wp_sector_off;
	block_t cs_zone_block, wp_block;
	अचिन्हित पूर्णांक log_sectors_per_block = sbi->log_blocksize - SECTOR_SHIFT;
	sector_t zone_sector;
	पूर्णांक err;

	cs_section = GET_SEC_FROM_SEG(sbi, cs->segno);
	cs_zone_block = START_BLOCK(sbi, GET_SEG_FROM_SEC(sbi, cs_section));

	zbd = get_target_zoned_dev(sbi, cs_zone_block);
	अगर (!zbd)
		वापस 0;

	/* report zone क्रम the sector the curseg poपूर्णांकs to */
	zone_sector = (sector_t)(cs_zone_block - zbd->start_blk)
		<< log_sectors_per_block;
	err = blkdev_report_zones(zbd->bdev, zone_sector, 1,
				  report_one_zone_cb, &zone);
	अगर (err != 1) अणु
		f2fs_err(sbi, "Report zone failed: %s errno=(%d)",
			 zbd->path, err);
		वापस err;
	पूर्ण

	अगर (zone.type != BLK_ZONE_TYPE_SEQWRITE_REQ)
		वापस 0;

	wp_block = zbd->start_blk + (zone.wp >> log_sectors_per_block);
	wp_segno = GET_SEGNO(sbi, wp_block);
	wp_blkoff = wp_block - START_BLOCK(sbi, wp_segno);
	wp_sector_off = zone.wp & GENMASK(log_sectors_per_block - 1, 0);

	अगर (cs->segno == wp_segno && cs->next_blkoff == wp_blkoff &&
		wp_sector_off == 0)
		वापस 0;

	f2fs_notice(sbi, "Unaligned curseg[%d] with write pointer: "
		    "curseg[0x%x,0x%x] wp[0x%x,0x%x]",
		    type, cs->segno, cs->next_blkoff, wp_segno, wp_blkoff);

	f2fs_notice(sbi, "Assign new section to curseg[%d]: "
		    "curseg[0x%x,0x%x]", type, cs->segno, cs->next_blkoff);

	f2fs_allocate_new_section(sbi, type, true);

	/* check consistency of the zone curseg poपूर्णांकed to */
	अगर (check_zone_ग_लिखो_poपूर्णांकer(sbi, zbd, &zone))
		वापस -EIO;

	/* check newly asचिन्हित zone */
	cs_section = GET_SEC_FROM_SEG(sbi, cs->segno);
	cs_zone_block = START_BLOCK(sbi, GET_SEG_FROM_SEC(sbi, cs_section));

	zbd = get_target_zoned_dev(sbi, cs_zone_block);
	अगर (!zbd)
		वापस 0;

	zone_sector = (sector_t)(cs_zone_block - zbd->start_blk)
		<< log_sectors_per_block;
	err = blkdev_report_zones(zbd->bdev, zone_sector, 1,
				  report_one_zone_cb, &zone);
	अगर (err != 1) अणु
		f2fs_err(sbi, "Report zone failed: %s errno=(%d)",
			 zbd->path, err);
		वापस err;
	पूर्ण

	अगर (zone.type != BLK_ZONE_TYPE_SEQWRITE_REQ)
		वापस 0;

	अगर (zone.wp != zone.start) अणु
		f2fs_notice(sbi,
			    "New zone for curseg[%d] is not yet discarded. "
			    "Reset the zone: curseg[0x%x,0x%x]",
			    type, cs->segno, cs->next_blkoff);
		err = __f2fs_issue_discard_zone(sbi, zbd->bdev,
				zone_sector >> log_sectors_per_block,
				zone.len >> log_sectors_per_block);
		अगर (err) अणु
			f2fs_err(sbi, "Discard zone failed: %s (errno=%d)",
				 zbd->path, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक f2fs_fix_curseg_ग_लिखो_poपूर्णांकer(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < NR_PERSISTENT_LOG; i++) अणु
		ret = fix_curseg_ग_लिखो_poपूर्णांकer(sbi, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा check_zone_ग_लिखो_poपूर्णांकer_args अणु
	काष्ठा f2fs_sb_info *sbi;
	काष्ठा f2fs_dev_info *fdev;
पूर्ण;

अटल पूर्णांक check_zone_ग_लिखो_poपूर्णांकer_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx,
				      व्योम *data)
अणु
	काष्ठा check_zone_ग_लिखो_poपूर्णांकer_args *args;

	args = (काष्ठा check_zone_ग_लिखो_poपूर्णांकer_args *)data;

	वापस check_zone_ग_लिखो_poपूर्णांकer(args->sbi, args->fdev, zone);
पूर्ण

पूर्णांक f2fs_check_ग_लिखो_poपूर्णांकer(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक i, ret;
	काष्ठा check_zone_ग_लिखो_poपूर्णांकer_args args;

	क्रम (i = 0; i < sbi->s_ndevs; i++) अणु
		अगर (!bdev_is_zoned(FDEV(i).bdev))
			जारी;

		args.sbi = sbi;
		args.fdev = &FDEV(i);
		ret = blkdev_report_zones(FDEV(i).bdev, 0, BLK_ALL_ZONES,
					  check_zone_ग_लिखो_poपूर्णांकer_cb, &args);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool is_conv_zone(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक zone_idx,
						अचिन्हित पूर्णांक dev_idx)
अणु
	अगर (!bdev_is_zoned(FDEV(dev_idx).bdev))
		वापस true;
	वापस !test_bit(zone_idx, FDEV(dev_idx).blkz_seq);
पूर्ण

/* Return the zone index in the given device */
अटल अचिन्हित पूर्णांक get_zone_idx(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक secno,
					पूर्णांक dev_idx)
अणु
	block_t sec_start_blkaddr = START_BLOCK(sbi, GET_SEG_FROM_SEC(sbi, secno));

	वापस (sec_start_blkaddr - FDEV(dev_idx).start_blk) >>
						sbi->log_blocks_per_blkz;
पूर्ण

/*
 * Return the usable segments in a section based on the zone's
 * corresponding zone capacity. Zone is equal to a section.
 */
अटल अंतरभूत अचिन्हित पूर्णांक f2fs_usable_zone_segs_in_sec(
		काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno)
अणु
	अचिन्हित पूर्णांक dev_idx, zone_idx, unusable_segs_in_sec;

	dev_idx = f2fs_target_device_index(sbi, START_BLOCK(sbi, segno));
	zone_idx = get_zone_idx(sbi, GET_SEC_FROM_SEG(sbi, segno), dev_idx);

	/* Conventional zone's capacity is always equal to zone size */
	अगर (is_conv_zone(sbi, zone_idx, dev_idx))
		वापस sbi->segs_per_sec;

	/*
	 * If the zone_capacity_blocks array is शून्य, then zone capacity
	 * is equal to the zone size क्रम all zones
	 */
	अगर (!FDEV(dev_idx).zone_capacity_blocks)
		वापस sbi->segs_per_sec;

	/* Get the segment count beyond zone capacity block */
	unusable_segs_in_sec = (sbi->blocks_per_blkz -
				FDEV(dev_idx).zone_capacity_blocks[zone_idx]) >>
				sbi->log_blocks_per_seg;
	वापस sbi->segs_per_sec - unusable_segs_in_sec;
पूर्ण

/*
 * Return the number of usable blocks in a segment. The number of blocks
 * वापसed is always equal to the number of blocks in a segment क्रम
 * segments fully contained within a sequential zone capacity or a
 * conventional zone. For segments partially contained in a sequential
 * zone capacity, the number of usable blocks up to the zone capacity
 * is वापसed. 0 is वापसed in all other हालs.
 */
अटल अंतरभूत अचिन्हित पूर्णांक f2fs_usable_zone_blks_in_seg(
			काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno)
अणु
	block_t seg_start, sec_start_blkaddr, sec_cap_blkaddr;
	अचिन्हित पूर्णांक zone_idx, dev_idx, secno;

	secno = GET_SEC_FROM_SEG(sbi, segno);
	seg_start = START_BLOCK(sbi, segno);
	dev_idx = f2fs_target_device_index(sbi, seg_start);
	zone_idx = get_zone_idx(sbi, secno, dev_idx);

	/*
	 * Conventional zone's capacity is always equal to zone size,
	 * so, blocks per segment is unchanged.
	 */
	अगर (is_conv_zone(sbi, zone_idx, dev_idx))
		वापस sbi->blocks_per_seg;

	अगर (!FDEV(dev_idx).zone_capacity_blocks)
		वापस sbi->blocks_per_seg;

	sec_start_blkaddr = START_BLOCK(sbi, GET_SEG_FROM_SEC(sbi, secno));
	sec_cap_blkaddr = sec_start_blkaddr +
				FDEV(dev_idx).zone_capacity_blocks[zone_idx];

	/*
	 * If segment starts beक्रमe zone capacity and spans beyond
	 * zone capacity, then usable blocks are from seg start to
	 * zone capacity. If the segment starts after the zone capacity,
	 * then there are no usable blocks.
	 */
	अगर (seg_start >= sec_cap_blkaddr)
		वापस 0;
	अगर (seg_start + sbi->blocks_per_seg > sec_cap_blkaddr)
		वापस sec_cap_blkaddr - seg_start;

	वापस sbi->blocks_per_seg;
पूर्ण
#अन्यथा
पूर्णांक f2fs_fix_curseg_ग_लिखो_poपूर्णांकer(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस 0;
पूर्ण

पूर्णांक f2fs_check_ग_लिखो_poपूर्णांकer(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक f2fs_usable_zone_blks_in_seg(काष्ठा f2fs_sb_info *sbi,
							अचिन्हित पूर्णांक segno)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक f2fs_usable_zone_segs_in_sec(काष्ठा f2fs_sb_info *sbi,
							अचिन्हित पूर्णांक segno)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
अचिन्हित पूर्णांक f2fs_usable_blks_in_seg(काष्ठा f2fs_sb_info *sbi,
					अचिन्हित पूर्णांक segno)
अणु
	अगर (f2fs_sb_has_blkzoned(sbi))
		वापस f2fs_usable_zone_blks_in_seg(sbi, segno);

	वापस sbi->blocks_per_seg;
पूर्ण

अचिन्हित पूर्णांक f2fs_usable_segs_in_sec(काष्ठा f2fs_sb_info *sbi,
					अचिन्हित पूर्णांक segno)
अणु
	अगर (f2fs_sb_has_blkzoned(sbi))
		वापस f2fs_usable_zone_segs_in_sec(sbi, segno);

	वापस sbi->segs_per_sec;
पूर्ण

/*
 * Update min, max modअगरied समय क्रम cost-benefit GC algorithm
 */
अटल व्योम init_min_max_mसमय(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	अचिन्हित पूर्णांक segno;

	करोwn_ग_लिखो(&sit_i->sentry_lock);

	sit_i->min_mसमय = ULदीर्घ_उच्च;

	क्रम (segno = 0; segno < MAIN_SEGS(sbi); segno += sbi->segs_per_sec) अणु
		अचिन्हित पूर्णांक i;
		अचिन्हित दीर्घ दीर्घ mसमय = 0;

		क्रम (i = 0; i < sbi->segs_per_sec; i++)
			mसमय += get_seg_entry(sbi, segno + i)->mसमय;

		mसमय = भाग_u64(mसमय, sbi->segs_per_sec);

		अगर (sit_i->min_mसमय > mसमय)
			sit_i->min_mसमय = mसमय;
	पूर्ण
	sit_i->max_mसमय = get_mसमय(sbi, false);
	sit_i->dirty_max_mसमय = 0;
	up_ग_लिखो(&sit_i->sentry_lock);
पूर्ण

पूर्णांक f2fs_build_segment_manager(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_super_block *raw_super = F2FS_RAW_SUPER(sbi);
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	काष्ठा f2fs_sm_info *sm_info;
	पूर्णांक err;

	sm_info = f2fs_kzalloc(sbi, माप(काष्ठा f2fs_sm_info), GFP_KERNEL);
	अगर (!sm_info)
		वापस -ENOMEM;

	/* init sm info */
	sbi->sm_info = sm_info;
	sm_info->seg0_blkaddr = le32_to_cpu(raw_super->segment0_blkaddr);
	sm_info->मुख्य_blkaddr = le32_to_cpu(raw_super->मुख्य_blkaddr);
	sm_info->segment_count = le32_to_cpu(raw_super->segment_count);
	sm_info->reserved_segments = le32_to_cpu(ckpt->rsvd_segment_count);
	sm_info->ovp_segments = le32_to_cpu(ckpt->overprov_segment_count);
	sm_info->मुख्य_segments = le32_to_cpu(raw_super->segment_count_मुख्य);
	sm_info->ssa_blkaddr = le32_to_cpu(raw_super->ssa_blkaddr);
	sm_info->rec_preमुक्त_segments = sm_info->मुख्य_segments *
					DEF_RECLAIM_PREFREE_SEGMENTS / 100;
	अगर (sm_info->rec_preमुक्त_segments > DEF_MAX_RECLAIM_PREFREE_SEGMENTS)
		sm_info->rec_preमुक्त_segments = DEF_MAX_RECLAIM_PREFREE_SEGMENTS;

	अगर (!f2fs_lfs_mode(sbi))
		sm_info->ipu_policy = 1 << F2FS_IPU_FSYNC;
	sm_info->min_ipu_util = DEF_MIN_IPU_UTIL;
	sm_info->min_fsync_blocks = DEF_MIN_FSYNC_BLOCKS;
	sm_info->min_seq_blocks = sbi->blocks_per_seg * sbi->segs_per_sec;
	sm_info->min_hot_blocks = DEF_MIN_HOT_BLOCKS;
	sm_info->min_ssr_sections = reserved_sections(sbi);

	INIT_LIST_HEAD(&sm_info->sit_entry_set);

	init_rwsem(&sm_info->curseg_lock);

	अगर (!f2fs_पढ़ोonly(sbi->sb)) अणु
		err = f2fs_create_flush_cmd_control(sbi);
		अगर (err)
			वापस err;
	पूर्ण

	err = create_discard_cmd_control(sbi);
	अगर (err)
		वापस err;

	err = build_sit_info(sbi);
	अगर (err)
		वापस err;
	err = build_मुक्त_segmap(sbi);
	अगर (err)
		वापस err;
	err = build_curseg(sbi);
	अगर (err)
		वापस err;

	/* reinit मुक्त segmap based on SIT */
	err = build_sit_entries(sbi);
	अगर (err)
		वापस err;

	init_मुक्त_segmap(sbi);
	err = build_dirty_segmap(sbi);
	अगर (err)
		वापस err;

	err = sanity_check_curseg(sbi);
	अगर (err)
		वापस err;

	init_min_max_mसमय(sbi);
	वापस 0;
पूर्ण

अटल व्योम discard_dirty_segmap(काष्ठा f2fs_sb_info *sbi,
		क्रमागत dirty_type dirty_type)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);

	mutex_lock(&dirty_i->seglist_lock);
	kvमुक्त(dirty_i->dirty_segmap[dirty_type]);
	dirty_i->nr_dirty[dirty_type] = 0;
	mutex_unlock(&dirty_i->seglist_lock);
पूर्ण

अटल व्योम destroy_victim_secmap(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);

	kvमुक्त(dirty_i->victim_secmap);
पूर्ण

अटल व्योम destroy_dirty_segmap(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	पूर्णांक i;

	अगर (!dirty_i)
		वापस;

	/* discard pre-मुक्त/dirty segments list */
	क्रम (i = 0; i < NR_सूचीTY_TYPE; i++)
		discard_dirty_segmap(sbi, i);

	अगर (__is_large_section(sbi)) अणु
		mutex_lock(&dirty_i->seglist_lock);
		kvमुक्त(dirty_i->dirty_secmap);
		mutex_unlock(&dirty_i->seglist_lock);
	पूर्ण

	destroy_victim_secmap(sbi);
	SM_I(sbi)->dirty_info = शून्य;
	kमुक्त(dirty_i);
पूर्ण

अटल व्योम destroy_curseg(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा curseg_info *array = SM_I(sbi)->curseg_array;
	पूर्णांक i;

	अगर (!array)
		वापस;
	SM_I(sbi)->curseg_array = शून्य;
	क्रम (i = 0; i < NR_CURSEG_TYPE; i++) अणु
		kमुक्त(array[i].sum_blk);
		kमुक्त(array[i].journal);
	पूर्ण
	kमुक्त(array);
पूर्ण

अटल व्योम destroy_मुक्त_segmap(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा मुक्त_segmap_info *मुक्त_i = SM_I(sbi)->मुक्त_info;

	अगर (!मुक्त_i)
		वापस;
	SM_I(sbi)->मुक्त_info = शून्य;
	kvमुक्त(मुक्त_i->मुक्त_segmap);
	kvमुक्त(मुक्त_i->मुक्त_secmap);
	kमुक्त(मुक्त_i);
पूर्ण

अटल व्योम destroy_sit_info(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);

	अगर (!sit_i)
		वापस;

	अगर (sit_i->sentries)
		kvमुक्त(sit_i->biपंचांगap);
	kमुक्त(sit_i->पंचांगp_map);

	kvमुक्त(sit_i->sentries);
	kvमुक्त(sit_i->sec_entries);
	kvमुक्त(sit_i->dirty_sentries_biपंचांगap);

	SM_I(sbi)->sit_info = शून्य;
	kvमुक्त(sit_i->sit_biपंचांगap);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	kvमुक्त(sit_i->sit_biपंचांगap_mir);
	kvमुक्त(sit_i->invalid_segmap);
#पूर्ण_अगर
	kमुक्त(sit_i);
पूर्ण

व्योम f2fs_destroy_segment_manager(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_sm_info *sm_info = SM_I(sbi);

	अगर (!sm_info)
		वापस;
	f2fs_destroy_flush_cmd_control(sbi, true);
	destroy_discard_cmd_control(sbi);
	destroy_dirty_segmap(sbi);
	destroy_curseg(sbi);
	destroy_मुक्त_segmap(sbi);
	destroy_sit_info(sbi);
	sbi->sm_info = शून्य;
	kमुक्त(sm_info);
पूर्ण

पूर्णांक __init f2fs_create_segment_manager_caches(व्योम)
अणु
	discard_entry_slab = f2fs_kmem_cache_create("f2fs_discard_entry",
			माप(काष्ठा discard_entry));
	अगर (!discard_entry_slab)
		जाओ fail;

	discard_cmd_slab = f2fs_kmem_cache_create("f2fs_discard_cmd",
			माप(काष्ठा discard_cmd));
	अगर (!discard_cmd_slab)
		जाओ destroy_discard_entry;

	sit_entry_set_slab = f2fs_kmem_cache_create("f2fs_sit_entry_set",
			माप(काष्ठा sit_entry_set));
	अगर (!sit_entry_set_slab)
		जाओ destroy_discard_cmd;

	inmem_entry_slab = f2fs_kmem_cache_create("f2fs_inmem_page_entry",
			माप(काष्ठा inmem_pages));
	अगर (!inmem_entry_slab)
		जाओ destroy_sit_entry_set;
	वापस 0;

destroy_sit_entry_set:
	kmem_cache_destroy(sit_entry_set_slab);
destroy_discard_cmd:
	kmem_cache_destroy(discard_cmd_slab);
destroy_discard_entry:
	kmem_cache_destroy(discard_entry_slab);
fail:
	वापस -ENOMEM;
पूर्ण

व्योम f2fs_destroy_segment_manager_caches(व्योम)
अणु
	kmem_cache_destroy(sit_entry_set_slab);
	kmem_cache_destroy(discard_cmd_slab);
	kmem_cache_destroy(discard_entry_slab);
	kmem_cache_destroy(inmem_entry_slab);
पूर्ण
