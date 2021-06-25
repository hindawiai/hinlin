<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/node.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/mpage.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/swap.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"
#समावेश "xattr.h"
#समावेश <trace/events/f2fs.h>

#घोषणा on_f2fs_build_मुक्त_nids(nmi) mutex_is_locked(&(nm_i)->build_lock)

अटल काष्ठा kmem_cache *nat_entry_slab;
अटल काष्ठा kmem_cache *मुक्त_nid_slab;
अटल काष्ठा kmem_cache *nat_entry_set_slab;
अटल काष्ठा kmem_cache *fsync_node_entry_slab;

/*
 * Check whether the given nid is within node id range.
 */
पूर्णांक f2fs_check_nid_range(काष्ठा f2fs_sb_info *sbi, nid_t nid)
अणु
	अगर (unlikely(nid < F2FS_ROOT_INO(sbi) || nid >= NM_I(sbi)->max_nid)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: out-of-range nid=%x, run fsck to fix.",
			  __func__, nid);
		वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

bool f2fs_available_मुक्त_memory(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	काष्ठा sysinfo val;
	अचिन्हित दीर्घ avail_ram;
	अचिन्हित दीर्घ mem_size = 0;
	bool res = false;

	अगर (!nm_i)
		वापस true;

	si_meminfo(&val);

	/* only uses low memory */
	avail_ram = val.totalram - val.totalhigh;

	/*
	 * give 25%, 25%, 50%, 50%, 50% memory क्रम each components respectively
	 */
	अगर (type == FREE_NIDS) अणु
		mem_size = (nm_i->nid_cnt[FREE_NID] *
				माप(काष्ठा मुक्त_nid)) >> PAGE_SHIFT;
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 2);
	पूर्ण अन्यथा अगर (type == NAT_ENTRIES) अणु
		mem_size = (nm_i->nat_cnt[TOTAL_NAT] *
				माप(काष्ठा nat_entry)) >> PAGE_SHIFT;
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 2);
		अगर (excess_cached_nats(sbi))
			res = false;
	पूर्ण अन्यथा अगर (type == सूचीTY_DENTS) अणु
		अगर (sbi->sb->s_bdi->wb.dirty_exceeded)
			वापस false;
		mem_size = get_pages(sbi, F2FS_सूचीTY_DENTS);
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 1);
	पूर्ण अन्यथा अगर (type == INO_ENTRIES) अणु
		पूर्णांक i;

		क्रम (i = 0; i < MAX_INO_ENTRY; i++)
			mem_size += sbi->im[i].ino_num *
						माप(काष्ठा ino_entry);
		mem_size >>= PAGE_SHIFT;
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 1);
	पूर्ण अन्यथा अगर (type == EXTENT_CACHE) अणु
		mem_size = (atomic_पढ़ो(&sbi->total_ext_tree) *
				माप(काष्ठा extent_tree) +
				atomic_पढ़ो(&sbi->total_ext_node) *
				माप(काष्ठा extent_node)) >> PAGE_SHIFT;
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 1);
	पूर्ण अन्यथा अगर (type == INMEM_PAGES) अणु
		/* it allows 20% / total_ram क्रम inmemory pages */
		mem_size = get_pages(sbi, F2FS_INMEM_PAGES);
		res = mem_size < (val.totalram / 5);
	पूर्ण अन्यथा अगर (type == DISCARD_CACHE) अणु
		mem_size = (atomic_पढ़ो(&dcc->discard_cmd_cnt) *
				माप(काष्ठा discard_cmd)) >> PAGE_SHIFT;
		res = mem_size < (avail_ram * nm_i->ram_thresh / 100);
	पूर्ण अन्यथा अणु
		अगर (!sbi->sb->s_bdi->wb.dirty_exceeded)
			वापस true;
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम clear_node_page_dirty(काष्ठा page *page)
अणु
	अगर (PageDirty(page)) अणु
		f2fs_clear_page_cache_dirty_tag(page);
		clear_page_dirty_क्रम_io(page);
		dec_page_count(F2FS_P_SB(page), F2FS_सूचीTY_NODES);
	पूर्ण
	ClearPageUptodate(page);
पूर्ण

अटल काष्ठा page *get_current_nat_page(काष्ठा f2fs_sb_info *sbi, nid_t nid)
अणु
	वापस f2fs_get_meta_page_retry(sbi, current_nat_addr(sbi, nid));
पूर्ण

अटल काष्ठा page *get_next_nat_page(काष्ठा f2fs_sb_info *sbi, nid_t nid)
अणु
	काष्ठा page *src_page;
	काष्ठा page *dst_page;
	pgoff_t dst_off;
	व्योम *src_addr;
	व्योम *dst_addr;
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);

	dst_off = next_nat_addr(sbi, current_nat_addr(sbi, nid));

	/* get current nat block page with lock */
	src_page = get_current_nat_page(sbi, nid);
	अगर (IS_ERR(src_page))
		वापस src_page;
	dst_page = f2fs_grab_meta_page(sbi, dst_off);
	f2fs_bug_on(sbi, PageDirty(src_page));

	src_addr = page_address(src_page);
	dst_addr = page_address(dst_page);
	स_नकल(dst_addr, src_addr, PAGE_SIZE);
	set_page_dirty(dst_page);
	f2fs_put_page(src_page, 1);

	set_to_next_nat(nm_i, nid);

	वापस dst_page;
पूर्ण

अटल काष्ठा nat_entry *__alloc_nat_entry(nid_t nid, bool no_fail)
अणु
	काष्ठा nat_entry *new;

	अगर (no_fail)
		new = f2fs_kmem_cache_alloc(nat_entry_slab, GFP_F2FS_ZERO);
	अन्यथा
		new = kmem_cache_alloc(nat_entry_slab, GFP_F2FS_ZERO);
	अगर (new) अणु
		nat_set_nid(new, nid);
		nat_reset_flag(new);
	पूर्ण
	वापस new;
पूर्ण

अटल व्योम __मुक्त_nat_entry(काष्ठा nat_entry *e)
अणु
	kmem_cache_मुक्त(nat_entry_slab, e);
पूर्ण

/* must be locked by nat_tree_lock */
अटल काष्ठा nat_entry *__init_nat_entry(काष्ठा f2fs_nm_info *nm_i,
	काष्ठा nat_entry *ne, काष्ठा f2fs_nat_entry *raw_ne, bool no_fail)
अणु
	अगर (no_fail)
		f2fs_radix_tree_insert(&nm_i->nat_root, nat_get_nid(ne), ne);
	अन्यथा अगर (radix_tree_insert(&nm_i->nat_root, nat_get_nid(ne), ne))
		वापस शून्य;

	अगर (raw_ne)
		node_info_from_raw_nat(&ne->ni, raw_ne);

	spin_lock(&nm_i->nat_list_lock);
	list_add_tail(&ne->list, &nm_i->nat_entries);
	spin_unlock(&nm_i->nat_list_lock);

	nm_i->nat_cnt[TOTAL_NAT]++;
	nm_i->nat_cnt[RECLAIMABLE_NAT]++;
	वापस ne;
पूर्ण

अटल काष्ठा nat_entry *__lookup_nat_cache(काष्ठा f2fs_nm_info *nm_i, nid_t n)
अणु
	काष्ठा nat_entry *ne;

	ne = radix_tree_lookup(&nm_i->nat_root, n);

	/* क्रम recent accessed nat entry, move it to tail of lru list */
	अगर (ne && !get_nat_flag(ne, IS_सूचीTY)) अणु
		spin_lock(&nm_i->nat_list_lock);
		अगर (!list_empty(&ne->list))
			list_move_tail(&ne->list, &nm_i->nat_entries);
		spin_unlock(&nm_i->nat_list_lock);
	पूर्ण

	वापस ne;
पूर्ण

अटल अचिन्हित पूर्णांक __gang_lookup_nat_cache(काष्ठा f2fs_nm_info *nm_i,
		nid_t start, अचिन्हित पूर्णांक nr, काष्ठा nat_entry **ep)
अणु
	वापस radix_tree_gang_lookup(&nm_i->nat_root, (व्योम **)ep, start, nr);
पूर्ण

अटल व्योम __del_from_nat_cache(काष्ठा f2fs_nm_info *nm_i, काष्ठा nat_entry *e)
अणु
	radix_tree_delete(&nm_i->nat_root, nat_get_nid(e));
	nm_i->nat_cnt[TOTAL_NAT]--;
	nm_i->nat_cnt[RECLAIMABLE_NAT]--;
	__मुक्त_nat_entry(e);
पूर्ण

अटल काष्ठा nat_entry_set *__grab_nat_entry_set(काष्ठा f2fs_nm_info *nm_i,
							काष्ठा nat_entry *ne)
अणु
	nid_t set = NAT_BLOCK_OFFSET(ne->ni.nid);
	काष्ठा nat_entry_set *head;

	head = radix_tree_lookup(&nm_i->nat_set_root, set);
	अगर (!head) अणु
		head = f2fs_kmem_cache_alloc(nat_entry_set_slab, GFP_NOFS);

		INIT_LIST_HEAD(&head->entry_list);
		INIT_LIST_HEAD(&head->set_list);
		head->set = set;
		head->entry_cnt = 0;
		f2fs_radix_tree_insert(&nm_i->nat_set_root, set, head);
	पूर्ण
	वापस head;
पूर्ण

अटल व्योम __set_nat_cache_dirty(काष्ठा f2fs_nm_info *nm_i,
						काष्ठा nat_entry *ne)
अणु
	काष्ठा nat_entry_set *head;
	bool new_ne = nat_get_blkaddr(ne) == NEW_ADDR;

	अगर (!new_ne)
		head = __grab_nat_entry_set(nm_i, ne);

	/*
	 * update entry_cnt in below condition:
	 * 1. update NEW_ADDR to valid block address;
	 * 2. update old block address to new one;
	 */
	अगर (!new_ne && (get_nat_flag(ne, IS_PREALLOC) ||
				!get_nat_flag(ne, IS_सूचीTY)))
		head->entry_cnt++;

	set_nat_flag(ne, IS_PREALLOC, new_ne);

	अगर (get_nat_flag(ne, IS_सूचीTY))
		जाओ refresh_list;

	nm_i->nat_cnt[सूचीTY_NAT]++;
	nm_i->nat_cnt[RECLAIMABLE_NAT]--;
	set_nat_flag(ne, IS_सूचीTY, true);
refresh_list:
	spin_lock(&nm_i->nat_list_lock);
	अगर (new_ne)
		list_del_init(&ne->list);
	अन्यथा
		list_move_tail(&ne->list, &head->entry_list);
	spin_unlock(&nm_i->nat_list_lock);
पूर्ण

अटल व्योम __clear_nat_cache_dirty(काष्ठा f2fs_nm_info *nm_i,
		काष्ठा nat_entry_set *set, काष्ठा nat_entry *ne)
अणु
	spin_lock(&nm_i->nat_list_lock);
	list_move_tail(&ne->list, &nm_i->nat_entries);
	spin_unlock(&nm_i->nat_list_lock);

	set_nat_flag(ne, IS_सूचीTY, false);
	set->entry_cnt--;
	nm_i->nat_cnt[सूचीTY_NAT]--;
	nm_i->nat_cnt[RECLAIMABLE_NAT]++;
पूर्ण

अटल अचिन्हित पूर्णांक __gang_lookup_nat_set(काष्ठा f2fs_nm_info *nm_i,
		nid_t start, अचिन्हित पूर्णांक nr, काष्ठा nat_entry_set **ep)
अणु
	वापस radix_tree_gang_lookup(&nm_i->nat_set_root, (व्योम **)ep,
							start, nr);
पूर्ण

bool f2fs_in_warm_node_list(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page)
अणु
	वापस NODE_MAPPING(sbi) == page->mapping &&
			IS_DNODE(page) && is_cold_node(page);
पूर्ण

व्योम f2fs_init_fsync_node_info(काष्ठा f2fs_sb_info *sbi)
अणु
	spin_lock_init(&sbi->fsync_node_lock);
	INIT_LIST_HEAD(&sbi->fsync_node_list);
	sbi->fsync_seg_id = 0;
	sbi->fsync_node_num = 0;
पूर्ण

अटल अचिन्हित पूर्णांक f2fs_add_fsync_node_entry(काष्ठा f2fs_sb_info *sbi,
							काष्ठा page *page)
अणु
	काष्ठा fsync_node_entry *fn;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक seq_id;

	fn = f2fs_kmem_cache_alloc(fsync_node_entry_slab, GFP_NOFS);

	get_page(page);
	fn->page = page;
	INIT_LIST_HEAD(&fn->list);

	spin_lock_irqsave(&sbi->fsync_node_lock, flags);
	list_add_tail(&fn->list, &sbi->fsync_node_list);
	fn->seq_id = sbi->fsync_seg_id++;
	seq_id = fn->seq_id;
	sbi->fsync_node_num++;
	spin_unlock_irqrestore(&sbi->fsync_node_lock, flags);

	वापस seq_id;
पूर्ण

व्योम f2fs_del_fsync_node_entry(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page)
अणु
	काष्ठा fsync_node_entry *fn;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sbi->fsync_node_lock, flags);
	list_क्रम_each_entry(fn, &sbi->fsync_node_list, list) अणु
		अगर (fn->page == page) अणु
			list_del(&fn->list);
			sbi->fsync_node_num--;
			spin_unlock_irqrestore(&sbi->fsync_node_lock, flags);
			kmem_cache_मुक्त(fsync_node_entry_slab, fn);
			put_page(page);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&sbi->fsync_node_lock, flags);
	f2fs_bug_on(sbi, 1);
पूर्ण

व्योम f2fs_reset_fsync_node_info(काष्ठा f2fs_sb_info *sbi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sbi->fsync_node_lock, flags);
	sbi->fsync_seg_id = 0;
	spin_unlock_irqrestore(&sbi->fsync_node_lock, flags);
पूर्ण

पूर्णांक f2fs_need_dentry_mark(काष्ठा f2fs_sb_info *sbi, nid_t nid)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा nat_entry *e;
	bool need = false;

	करोwn_पढ़ो(&nm_i->nat_tree_lock);
	e = __lookup_nat_cache(nm_i, nid);
	अगर (e) अणु
		अगर (!get_nat_flag(e, IS_CHECKPOINTED) &&
				!get_nat_flag(e, HAS_FSYNCED_INODE))
			need = true;
	पूर्ण
	up_पढ़ो(&nm_i->nat_tree_lock);
	वापस need;
पूर्ण

bool f2fs_is_checkpoपूर्णांकed_node(काष्ठा f2fs_sb_info *sbi, nid_t nid)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा nat_entry *e;
	bool is_cp = true;

	करोwn_पढ़ो(&nm_i->nat_tree_lock);
	e = __lookup_nat_cache(nm_i, nid);
	अगर (e && !get_nat_flag(e, IS_CHECKPOINTED))
		is_cp = false;
	up_पढ़ो(&nm_i->nat_tree_lock);
	वापस is_cp;
पूर्ण

bool f2fs_need_inode_block_update(काष्ठा f2fs_sb_info *sbi, nid_t ino)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा nat_entry *e;
	bool need_update = true;

	करोwn_पढ़ो(&nm_i->nat_tree_lock);
	e = __lookup_nat_cache(nm_i, ino);
	अगर (e && get_nat_flag(e, HAS_LAST_FSYNC) &&
			(get_nat_flag(e, IS_CHECKPOINTED) ||
			 get_nat_flag(e, HAS_FSYNCED_INODE)))
		need_update = false;
	up_पढ़ो(&nm_i->nat_tree_lock);
	वापस need_update;
पूर्ण

/* must be locked by nat_tree_lock */
अटल व्योम cache_nat_entry(काष्ठा f2fs_sb_info *sbi, nid_t nid,
						काष्ठा f2fs_nat_entry *ne)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा nat_entry *new, *e;

	new = __alloc_nat_entry(nid, false);
	अगर (!new)
		वापस;

	करोwn_ग_लिखो(&nm_i->nat_tree_lock);
	e = __lookup_nat_cache(nm_i, nid);
	अगर (!e)
		e = __init_nat_entry(nm_i, new, ne, false);
	अन्यथा
		f2fs_bug_on(sbi, nat_get_ino(e) != le32_to_cpu(ne->ino) ||
				nat_get_blkaddr(e) !=
					le32_to_cpu(ne->block_addr) ||
				nat_get_version(e) != ne->version);
	up_ग_लिखो(&nm_i->nat_tree_lock);
	अगर (e != new)
		__मुक्त_nat_entry(new);
पूर्ण

अटल व्योम set_node_addr(काष्ठा f2fs_sb_info *sbi, काष्ठा node_info *ni,
			block_t new_blkaddr, bool fsync_करोne)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा nat_entry *e;
	काष्ठा nat_entry *new = __alloc_nat_entry(ni->nid, true);

	करोwn_ग_लिखो(&nm_i->nat_tree_lock);
	e = __lookup_nat_cache(nm_i, ni->nid);
	अगर (!e) अणु
		e = __init_nat_entry(nm_i, new, शून्य, true);
		copy_node_info(&e->ni, ni);
		f2fs_bug_on(sbi, ni->blk_addr == NEW_ADDR);
	पूर्ण अन्यथा अगर (new_blkaddr == NEW_ADDR) अणु
		/*
		 * when nid is पुनः_स्मृतिated,
		 * previous nat entry can be reमुख्यed in nat cache.
		 * So, reinitialize it with new inक्रमmation.
		 */
		copy_node_info(&e->ni, ni);
		f2fs_bug_on(sbi, ni->blk_addr != शून्य_ADDR);
	पूर्ण
	/* let's मुक्त early to reduce memory consumption */
	अगर (e != new)
		__मुक्त_nat_entry(new);

	/* sanity check */
	f2fs_bug_on(sbi, nat_get_blkaddr(e) != ni->blk_addr);
	f2fs_bug_on(sbi, nat_get_blkaddr(e) == शून्य_ADDR &&
			new_blkaddr == शून्य_ADDR);
	f2fs_bug_on(sbi, nat_get_blkaddr(e) == NEW_ADDR &&
			new_blkaddr == NEW_ADDR);
	f2fs_bug_on(sbi, __is_valid_data_blkaddr(nat_get_blkaddr(e)) &&
			new_blkaddr == NEW_ADDR);

	/* increment version no as node is हटाओd */
	अगर (nat_get_blkaddr(e) != NEW_ADDR && new_blkaddr == शून्य_ADDR) अणु
		अचिन्हित अक्षर version = nat_get_version(e);

		nat_set_version(e, inc_node_version(version));
	पूर्ण

	/* change address */
	nat_set_blkaddr(e, new_blkaddr);
	अगर (!__is_valid_data_blkaddr(new_blkaddr))
		set_nat_flag(e, IS_CHECKPOINTED, false);
	__set_nat_cache_dirty(nm_i, e);

	/* update fsync_mark अगर its inode nat entry is still alive */
	अगर (ni->nid != ni->ino)
		e = __lookup_nat_cache(nm_i, ni->ino);
	अगर (e) अणु
		अगर (fsync_करोne && ni->nid == ni->ino)
			set_nat_flag(e, HAS_FSYNCED_INODE, true);
		set_nat_flag(e, HAS_LAST_FSYNC, fsync_करोne);
	पूर्ण
	up_ग_लिखो(&nm_i->nat_tree_lock);
पूर्ण

पूर्णांक f2fs_try_to_मुक्त_nats(काष्ठा f2fs_sb_info *sbi, पूर्णांक nr_shrink)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	पूर्णांक nr = nr_shrink;

	अगर (!करोwn_ग_लिखो_trylock(&nm_i->nat_tree_lock))
		वापस 0;

	spin_lock(&nm_i->nat_list_lock);
	जबतक (nr_shrink) अणु
		काष्ठा nat_entry *ne;

		अगर (list_empty(&nm_i->nat_entries))
			अवरोध;

		ne = list_first_entry(&nm_i->nat_entries,
					काष्ठा nat_entry, list);
		list_del(&ne->list);
		spin_unlock(&nm_i->nat_list_lock);

		__del_from_nat_cache(nm_i, ne);
		nr_shrink--;

		spin_lock(&nm_i->nat_list_lock);
	पूर्ण
	spin_unlock(&nm_i->nat_list_lock);

	up_ग_लिखो(&nm_i->nat_tree_lock);
	वापस nr - nr_shrink;
पूर्ण

पूर्णांक f2fs_get_node_info(काष्ठा f2fs_sb_info *sbi, nid_t nid,
						काष्ठा node_info *ni)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, CURSEG_HOT_DATA);
	काष्ठा f2fs_journal *journal = curseg->journal;
	nid_t start_nid = START_NID(nid);
	काष्ठा f2fs_nat_block *nat_blk;
	काष्ठा page *page = शून्य;
	काष्ठा f2fs_nat_entry ne;
	काष्ठा nat_entry *e;
	pgoff_t index;
	block_t blkaddr;
	पूर्णांक i;

	ni->nid = nid;

	/* Check nat cache */
	करोwn_पढ़ो(&nm_i->nat_tree_lock);
	e = __lookup_nat_cache(nm_i, nid);
	अगर (e) अणु
		ni->ino = nat_get_ino(e);
		ni->blk_addr = nat_get_blkaddr(e);
		ni->version = nat_get_version(e);
		up_पढ़ो(&nm_i->nat_tree_lock);
		वापस 0;
	पूर्ण

	स_रखो(&ne, 0, माप(काष्ठा f2fs_nat_entry));

	/* Check current segment summary */
	करोwn_पढ़ो(&curseg->journal_rwsem);
	i = f2fs_lookup_journal_in_cursum(journal, NAT_JOURNAL, nid, 0);
	अगर (i >= 0) अणु
		ne = nat_in_journal(journal, i);
		node_info_from_raw_nat(ni, &ne);
	पूर्ण
	up_पढ़ो(&curseg->journal_rwsem);
	अगर (i >= 0) अणु
		up_पढ़ो(&nm_i->nat_tree_lock);
		जाओ cache;
	पूर्ण

	/* Fill node_info from nat page */
	index = current_nat_addr(sbi, nid);
	up_पढ़ो(&nm_i->nat_tree_lock);

	page = f2fs_get_meta_page(sbi, index);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	nat_blk = (काष्ठा f2fs_nat_block *)page_address(page);
	ne = nat_blk->entries[nid - start_nid];
	node_info_from_raw_nat(ni, &ne);
	f2fs_put_page(page, 1);
cache:
	blkaddr = le32_to_cpu(ne.block_addr);
	अगर (__is_valid_data_blkaddr(blkaddr) &&
		!f2fs_is_valid_blkaddr(sbi, blkaddr, DATA_GENERIC_ENHANCE))
		वापस -EFAULT;

	/* cache nat entry */
	cache_nat_entry(sbi, nid, &ne);
	वापस 0;
पूर्ण

/*
 * पढ़ोahead MAX_RA_NODE number of node pages.
 */
अटल व्योम f2fs_ra_node_pages(काष्ठा page *parent, पूर्णांक start, पूर्णांक n)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_P_SB(parent);
	काष्ठा blk_plug plug;
	पूर्णांक i, end;
	nid_t nid;

	blk_start_plug(&plug);

	/* Then, try पढ़ोahead क्रम siblings of the desired node */
	end = start + n;
	end = min(end, NIDS_PER_BLOCK);
	क्रम (i = start; i < end; i++) अणु
		nid = get_nid(parent, i, false);
		f2fs_ra_node_page(sbi, nid);
	पूर्ण

	blk_finish_plug(&plug);
पूर्ण

pgoff_t f2fs_get_next_page_offset(काष्ठा dnode_of_data *dn, pgoff_t pgofs)
अणु
	स्थिर दीर्घ direct_index = ADDRS_PER_INODE(dn->inode);
	स्थिर दीर्घ direct_blks = ADDRS_PER_BLOCK(dn->inode);
	स्थिर दीर्घ indirect_blks = ADDRS_PER_BLOCK(dn->inode) * NIDS_PER_BLOCK;
	अचिन्हित पूर्णांक skipped_unit = ADDRS_PER_BLOCK(dn->inode);
	पूर्णांक cur_level = dn->cur_level;
	पूर्णांक max_level = dn->max_level;
	pgoff_t base = 0;

	अगर (!dn->max_level)
		वापस pgofs + 1;

	जबतक (max_level-- > cur_level)
		skipped_unit *= NIDS_PER_BLOCK;

	चयन (dn->max_level) अणु
	हाल 3:
		base += 2 * indirect_blks;
		fallthrough;
	हाल 2:
		base += 2 * direct_blks;
		fallthrough;
	हाल 1:
		base += direct_index;
		अवरोध;
	शेष:
		f2fs_bug_on(F2FS_I_SB(dn->inode), 1);
	पूर्ण

	वापस ((pgofs - base) / skipped_unit + 1) * skipped_unit + base;
पूर्ण

/*
 * The maximum depth is four.
 * Offset[0] will have raw inode offset.
 */
अटल पूर्णांक get_node_path(काष्ठा inode *inode, दीर्घ block,
				पूर्णांक offset[4], अचिन्हित पूर्णांक noffset[4])
अणु
	स्थिर दीर्घ direct_index = ADDRS_PER_INODE(inode);
	स्थिर दीर्घ direct_blks = ADDRS_PER_BLOCK(inode);
	स्थिर दीर्घ dptrs_per_blk = NIDS_PER_BLOCK;
	स्थिर दीर्घ indirect_blks = ADDRS_PER_BLOCK(inode) * NIDS_PER_BLOCK;
	स्थिर दीर्घ dindirect_blks = indirect_blks * NIDS_PER_BLOCK;
	पूर्णांक n = 0;
	पूर्णांक level = 0;

	noffset[0] = 0;

	अगर (block < direct_index) अणु
		offset[n] = block;
		जाओ got;
	पूर्ण
	block -= direct_index;
	अगर (block < direct_blks) अणु
		offset[n++] = NODE_सूची1_BLOCK;
		noffset[n] = 1;
		offset[n] = block;
		level = 1;
		जाओ got;
	पूर्ण
	block -= direct_blks;
	अगर (block < direct_blks) अणु
		offset[n++] = NODE_सूची2_BLOCK;
		noffset[n] = 2;
		offset[n] = block;
		level = 1;
		जाओ got;
	पूर्ण
	block -= direct_blks;
	अगर (block < indirect_blks) अणु
		offset[n++] = NODE_IND1_BLOCK;
		noffset[n] = 3;
		offset[n++] = block / direct_blks;
		noffset[n] = 4 + offset[n - 1];
		offset[n] = block % direct_blks;
		level = 2;
		जाओ got;
	पूर्ण
	block -= indirect_blks;
	अगर (block < indirect_blks) अणु
		offset[n++] = NODE_IND2_BLOCK;
		noffset[n] = 4 + dptrs_per_blk;
		offset[n++] = block / direct_blks;
		noffset[n] = 5 + dptrs_per_blk + offset[n - 1];
		offset[n] = block % direct_blks;
		level = 2;
		जाओ got;
	पूर्ण
	block -= indirect_blks;
	अगर (block < dindirect_blks) अणु
		offset[n++] = NODE_DIND_BLOCK;
		noffset[n] = 5 + (dptrs_per_blk * 2);
		offset[n++] = block / indirect_blks;
		noffset[n] = 6 + (dptrs_per_blk * 2) +
			      offset[n - 1] * (dptrs_per_blk + 1);
		offset[n++] = (block / direct_blks) % dptrs_per_blk;
		noffset[n] = 7 + (dptrs_per_blk * 2) +
			      offset[n - 2] * (dptrs_per_blk + 1) +
			      offset[n - 1];
		offset[n] = block % direct_blks;
		level = 3;
		जाओ got;
	पूर्ण अन्यथा अणु
		वापस -E2BIG;
	पूर्ण
got:
	वापस level;
पूर्ण

/*
 * Caller should call f2fs_put_dnode(dn).
 * Also, it should grab and release a rwsem by calling f2fs_lock_op() and
 * f2fs_unlock_op() only अगर mode is set with ALLOC_NODE.
 */
पूर्णांक f2fs_get_dnode_of_data(काष्ठा dnode_of_data *dn, pgoff_t index, पूर्णांक mode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	काष्ठा page *npage[4];
	काष्ठा page *parent = शून्य;
	पूर्णांक offset[4];
	अचिन्हित पूर्णांक noffset[4];
	nid_t nids[4];
	पूर्णांक level, i = 0;
	पूर्णांक err = 0;

	level = get_node_path(dn->inode, index, offset, noffset);
	अगर (level < 0)
		वापस level;

	nids[0] = dn->inode->i_ino;
	npage[0] = dn->inode_page;

	अगर (!npage[0]) अणु
		npage[0] = f2fs_get_node_page(sbi, nids[0]);
		अगर (IS_ERR(npage[0]))
			वापस PTR_ERR(npage[0]);
	पूर्ण

	/* अगर अंतरभूत_data is set, should not report any block indices */
	अगर (f2fs_has_अंतरभूत_data(dn->inode) && index) अणु
		err = -ENOENT;
		f2fs_put_page(npage[0], 1);
		जाओ release_out;
	पूर्ण

	parent = npage[0];
	अगर (level != 0)
		nids[1] = get_nid(parent, offset[0], true);
	dn->inode_page = npage[0];
	dn->inode_page_locked = true;

	/* get indirect or direct nodes */
	क्रम (i = 1; i <= level; i++) अणु
		bool करोne = false;

		अगर (!nids[i] && mode == ALLOC_NODE) अणु
			/* alloc new node */
			अगर (!f2fs_alloc_nid(sbi, &(nids[i]))) अणु
				err = -ENOSPC;
				जाओ release_pages;
			पूर्ण

			dn->nid = nids[i];
			npage[i] = f2fs_new_node_page(dn, noffset[i]);
			अगर (IS_ERR(npage[i])) अणु
				f2fs_alloc_nid_failed(sbi, nids[i]);
				err = PTR_ERR(npage[i]);
				जाओ release_pages;
			पूर्ण

			set_nid(parent, offset[i - 1], nids[i], i == 1);
			f2fs_alloc_nid_करोne(sbi, nids[i]);
			करोne = true;
		पूर्ण अन्यथा अगर (mode == LOOKUP_NODE_RA && i == level && level > 1) अणु
			npage[i] = f2fs_get_node_page_ra(parent, offset[i - 1]);
			अगर (IS_ERR(npage[i])) अणु
				err = PTR_ERR(npage[i]);
				जाओ release_pages;
			पूर्ण
			करोne = true;
		पूर्ण
		अगर (i == 1) अणु
			dn->inode_page_locked = false;
			unlock_page(parent);
		पूर्ण अन्यथा अणु
			f2fs_put_page(parent, 1);
		पूर्ण

		अगर (!करोne) अणु
			npage[i] = f2fs_get_node_page(sbi, nids[i]);
			अगर (IS_ERR(npage[i])) अणु
				err = PTR_ERR(npage[i]);
				f2fs_put_page(npage[0], 0);
				जाओ release_out;
			पूर्ण
		पूर्ण
		अगर (i < level) अणु
			parent = npage[i];
			nids[i + 1] = get_nid(parent, offset[i], false);
		पूर्ण
	पूर्ण
	dn->nid = nids[level];
	dn->ofs_in_node = offset[level];
	dn->node_page = npage[level];
	dn->data_blkaddr = f2fs_data_blkaddr(dn);
	वापस 0;

release_pages:
	f2fs_put_page(parent, 1);
	अगर (i > 1)
		f2fs_put_page(npage[0], 0);
release_out:
	dn->inode_page = शून्य;
	dn->node_page = शून्य;
	अगर (err == -ENOENT) अणु
		dn->cur_level = i;
		dn->max_level = level;
		dn->ofs_in_node = offset[level];
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक truncate_node(काष्ठा dnode_of_data *dn)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	काष्ठा node_info ni;
	पूर्णांक err;
	pgoff_t index;

	err = f2fs_get_node_info(sbi, dn->nid, &ni);
	अगर (err)
		वापस err;

	/* Deallocate node address */
	f2fs_invalidate_blocks(sbi, ni.blk_addr);
	dec_valid_node_count(sbi, dn->inode, dn->nid == dn->inode->i_ino);
	set_node_addr(sbi, &ni, शून्य_ADDR, false);

	अगर (dn->nid == dn->inode->i_ino) अणु
		f2fs_हटाओ_orphan_inode(sbi, dn->nid);
		dec_valid_inode_count(sbi);
		f2fs_inode_synced(dn->inode);
	पूर्ण

	clear_node_page_dirty(dn->node_page);
	set_sbi_flag(sbi, SBI_IS_सूचीTY);

	index = dn->node_page->index;
	f2fs_put_page(dn->node_page, 1);

	invalidate_mapping_pages(NODE_MAPPING(sbi),
			index, index);

	dn->node_page = शून्य;
	trace_f2fs_truncate_node(dn->inode, dn->nid, ni.blk_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक truncate_dnode(काष्ठा dnode_of_data *dn)
अणु
	काष्ठा page *page;
	पूर्णांक err;

	अगर (dn->nid == 0)
		वापस 1;

	/* get direct node */
	page = f2fs_get_node_page(F2FS_I_SB(dn->inode), dn->nid);
	अगर (PTR_ERR(page) == -ENOENT)
		वापस 1;
	अन्यथा अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	/* Make dnode_of_data क्रम parameter */
	dn->node_page = page;
	dn->ofs_in_node = 0;
	f2fs_truncate_data_blocks(dn);
	err = truncate_node(dn);
	अगर (err)
		वापस err;

	वापस 1;
पूर्ण

अटल पूर्णांक truncate_nodes(काष्ठा dnode_of_data *dn, अचिन्हित पूर्णांक nofs,
						पूर्णांक ofs, पूर्णांक depth)
अणु
	काष्ठा dnode_of_data rdn = *dn;
	काष्ठा page *page;
	काष्ठा f2fs_node *rn;
	nid_t child_nid;
	अचिन्हित पूर्णांक child_nofs;
	पूर्णांक मुक्तd = 0;
	पूर्णांक i, ret;

	अगर (dn->nid == 0)
		वापस NIDS_PER_BLOCK + 1;

	trace_f2fs_truncate_nodes_enter(dn->inode, dn->nid, dn->data_blkaddr);

	page = f2fs_get_node_page(F2FS_I_SB(dn->inode), dn->nid);
	अगर (IS_ERR(page)) अणु
		trace_f2fs_truncate_nodes_निकास(dn->inode, PTR_ERR(page));
		वापस PTR_ERR(page);
	पूर्ण

	f2fs_ra_node_pages(page, ofs, NIDS_PER_BLOCK);

	rn = F2FS_NODE(page);
	अगर (depth < 3) अणु
		क्रम (i = ofs; i < NIDS_PER_BLOCK; i++, मुक्तd++) अणु
			child_nid = le32_to_cpu(rn->in.nid[i]);
			अगर (child_nid == 0)
				जारी;
			rdn.nid = child_nid;
			ret = truncate_dnode(&rdn);
			अगर (ret < 0)
				जाओ out_err;
			अगर (set_nid(page, i, 0, false))
				dn->node_changed = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		child_nofs = nofs + ofs * (NIDS_PER_BLOCK + 1) + 1;
		क्रम (i = ofs; i < NIDS_PER_BLOCK; i++) अणु
			child_nid = le32_to_cpu(rn->in.nid[i]);
			अगर (child_nid == 0) अणु
				child_nofs += NIDS_PER_BLOCK + 1;
				जारी;
			पूर्ण
			rdn.nid = child_nid;
			ret = truncate_nodes(&rdn, child_nofs, 0, depth - 1);
			अगर (ret == (NIDS_PER_BLOCK + 1)) अणु
				अगर (set_nid(page, i, 0, false))
					dn->node_changed = true;
				child_nofs += ret;
			पूर्ण अन्यथा अगर (ret < 0 && ret != -ENOENT) अणु
				जाओ out_err;
			पूर्ण
		पूर्ण
		मुक्तd = child_nofs;
	पूर्ण

	अगर (!ofs) अणु
		/* हटाओ current indirect node */
		dn->node_page = page;
		ret = truncate_node(dn);
		अगर (ret)
			जाओ out_err;
		मुक्तd++;
	पूर्ण अन्यथा अणु
		f2fs_put_page(page, 1);
	पूर्ण
	trace_f2fs_truncate_nodes_निकास(dn->inode, मुक्तd);
	वापस मुक्तd;

out_err:
	f2fs_put_page(page, 1);
	trace_f2fs_truncate_nodes_निकास(dn->inode, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक truncate_partial_nodes(काष्ठा dnode_of_data *dn,
			काष्ठा f2fs_inode *ri, पूर्णांक *offset, पूर्णांक depth)
अणु
	काष्ठा page *pages[2];
	nid_t nid[3];
	nid_t child_nid;
	पूर्णांक err = 0;
	पूर्णांक i;
	पूर्णांक idx = depth - 2;

	nid[0] = le32_to_cpu(ri->i_nid[offset[0] - NODE_सूची1_BLOCK]);
	अगर (!nid[0])
		वापस 0;

	/* get indirect nodes in the path */
	क्रम (i = 0; i < idx + 1; i++) अणु
		/* reference count'll be increased */
		pages[i] = f2fs_get_node_page(F2FS_I_SB(dn->inode), nid[i]);
		अगर (IS_ERR(pages[i])) अणु
			err = PTR_ERR(pages[i]);
			idx = i - 1;
			जाओ fail;
		पूर्ण
		nid[i + 1] = get_nid(pages[i], offset[i + 1], false);
	पूर्ण

	f2fs_ra_node_pages(pages[idx], offset[idx + 1], NIDS_PER_BLOCK);

	/* मुक्त direct nodes linked to a partial indirect node */
	क्रम (i = offset[idx + 1]; i < NIDS_PER_BLOCK; i++) अणु
		child_nid = get_nid(pages[idx], i, false);
		अगर (!child_nid)
			जारी;
		dn->nid = child_nid;
		err = truncate_dnode(dn);
		अगर (err < 0)
			जाओ fail;
		अगर (set_nid(pages[idx], i, 0, false))
			dn->node_changed = true;
	पूर्ण

	अगर (offset[idx + 1] == 0) अणु
		dn->node_page = pages[idx];
		dn->nid = nid[idx];
		err = truncate_node(dn);
		अगर (err)
			जाओ fail;
	पूर्ण अन्यथा अणु
		f2fs_put_page(pages[idx], 1);
	पूर्ण
	offset[idx]++;
	offset[idx + 1] = 0;
	idx--;
fail:
	क्रम (i = idx; i >= 0; i--)
		f2fs_put_page(pages[i], 1);

	trace_f2fs_truncate_partial_nodes(dn->inode, nid, depth, err);

	वापस err;
पूर्ण

/*
 * All the block addresses of data and nodes should be nullअगरied.
 */
पूर्णांक f2fs_truncate_inode_blocks(काष्ठा inode *inode, pgoff_t from)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक err = 0, cont = 1;
	पूर्णांक level, offset[4], noffset[4];
	अचिन्हित पूर्णांक nofs = 0;
	काष्ठा f2fs_inode *ri;
	काष्ठा dnode_of_data dn;
	काष्ठा page *page;

	trace_f2fs_truncate_inode_blocks_enter(inode, from);

	level = get_node_path(inode, from, offset, noffset);
	अगर (level < 0) अणु
		trace_f2fs_truncate_inode_blocks_निकास(inode, level);
		वापस level;
	पूर्ण

	page = f2fs_get_node_page(sbi, inode->i_ino);
	अगर (IS_ERR(page)) अणु
		trace_f2fs_truncate_inode_blocks_निकास(inode, PTR_ERR(page));
		वापस PTR_ERR(page);
	पूर्ण

	set_new_dnode(&dn, inode, page, शून्य, 0);
	unlock_page(page);

	ri = F2FS_INODE(page);
	चयन (level) अणु
	हाल 0:
	हाल 1:
		nofs = noffset[1];
		अवरोध;
	हाल 2:
		nofs = noffset[1];
		अगर (!offset[level - 1])
			जाओ skip_partial;
		err = truncate_partial_nodes(&dn, ri, offset, level);
		अगर (err < 0 && err != -ENOENT)
			जाओ fail;
		nofs += 1 + NIDS_PER_BLOCK;
		अवरोध;
	हाल 3:
		nofs = 5 + 2 * NIDS_PER_BLOCK;
		अगर (!offset[level - 1])
			जाओ skip_partial;
		err = truncate_partial_nodes(&dn, ri, offset, level);
		अगर (err < 0 && err != -ENOENT)
			जाओ fail;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

skip_partial:
	जबतक (cont) अणु
		dn.nid = le32_to_cpu(ri->i_nid[offset[0] - NODE_सूची1_BLOCK]);
		चयन (offset[0]) अणु
		हाल NODE_सूची1_BLOCK:
		हाल NODE_सूची2_BLOCK:
			err = truncate_dnode(&dn);
			अवरोध;

		हाल NODE_IND1_BLOCK:
		हाल NODE_IND2_BLOCK:
			err = truncate_nodes(&dn, nofs, offset[1], 2);
			अवरोध;

		हाल NODE_DIND_BLOCK:
			err = truncate_nodes(&dn, nofs, offset[1], 3);
			cont = 0;
			अवरोध;

		शेष:
			BUG();
		पूर्ण
		अगर (err < 0 && err != -ENOENT)
			जाओ fail;
		अगर (offset[1] == 0 &&
				ri->i_nid[offset[0] - NODE_सूची1_BLOCK]) अणु
			lock_page(page);
			BUG_ON(page->mapping != NODE_MAPPING(sbi));
			f2fs_रुको_on_page_ग_लिखोback(page, NODE, true, true);
			ri->i_nid[offset[0] - NODE_सूची1_BLOCK] = 0;
			set_page_dirty(page);
			unlock_page(page);
		पूर्ण
		offset[1] = 0;
		offset[0]++;
		nofs += err;
	पूर्ण
fail:
	f2fs_put_page(page, 0);
	trace_f2fs_truncate_inode_blocks_निकास(inode, err);
	वापस err > 0 ? 0 : err;
पूर्ण

/* caller must lock inode page */
पूर्णांक f2fs_truncate_xattr_node(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t nid = F2FS_I(inode)->i_xattr_nid;
	काष्ठा dnode_of_data dn;
	काष्ठा page *npage;
	पूर्णांक err;

	अगर (!nid)
		वापस 0;

	npage = f2fs_get_node_page(sbi, nid);
	अगर (IS_ERR(npage))
		वापस PTR_ERR(npage);

	set_new_dnode(&dn, inode, शून्य, npage, nid);
	err = truncate_node(&dn);
	अगर (err) अणु
		f2fs_put_page(npage, 1);
		वापस err;
	पूर्ण

	f2fs_i_xnid_ग_लिखो(inode, 0);

	वापस 0;
पूर्ण

/*
 * Caller should grab and release a rwsem by calling f2fs_lock_op() and
 * f2fs_unlock_op().
 */
पूर्णांक f2fs_हटाओ_inode_page(काष्ठा inode *inode)
अणु
	काष्ठा dnode_of_data dn;
	पूर्णांक err;

	set_new_dnode(&dn, inode, शून्य, शून्य, inode->i_ino);
	err = f2fs_get_dnode_of_data(&dn, 0, LOOKUP_NODE);
	अगर (err)
		वापस err;

	err = f2fs_truncate_xattr_node(inode);
	अगर (err) अणु
		f2fs_put_dnode(&dn);
		वापस err;
	पूर्ण

	/* हटाओ potential अंतरभूत_data blocks */
	अगर (S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
				S_ISLNK(inode->i_mode))
		f2fs_truncate_data_blocks_range(&dn, 1);

	/* 0 is possible, after f2fs_new_inode() has failed */
	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(inode)))) अणु
		f2fs_put_dnode(&dn);
		वापस -EIO;
	पूर्ण

	अगर (unlikely(inode->i_blocks != 0 && inode->i_blocks != 8)) अणु
		f2fs_warn(F2FS_I_SB(inode),
			"f2fs_remove_inode_page: inconsistent i_blocks, ino:%lu, iblocks:%llu",
			inode->i_ino, (अचिन्हित दीर्घ दीर्घ)inode->i_blocks);
		set_sbi_flag(F2FS_I_SB(inode), SBI_NEED_FSCK);
	पूर्ण

	/* will put inode & node pages */
	err = truncate_node(&dn);
	अगर (err) अणु
		f2fs_put_dnode(&dn);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा page *f2fs_new_inode_page(काष्ठा inode *inode)
अणु
	काष्ठा dnode_of_data dn;

	/* allocate inode page क्रम new inode */
	set_new_dnode(&dn, inode, शून्य, शून्य, inode->i_ino);

	/* caller should f2fs_put_page(page, 1); */
	वापस f2fs_new_node_page(&dn, 0);
पूर्ण

काष्ठा page *f2fs_new_node_page(काष्ठा dnode_of_data *dn, अचिन्हित पूर्णांक ofs)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	काष्ठा node_info new_ni;
	काष्ठा page *page;
	पूर्णांक err;

	अगर (unlikely(is_inode_flag_set(dn->inode, FI_NO_ALLOC)))
		वापस ERR_PTR(-EPERM);

	page = f2fs_grab_cache_page(NODE_MAPPING(sbi), dn->nid, false);
	अगर (!page)
		वापस ERR_PTR(-ENOMEM);

	अगर (unlikely((err = inc_valid_node_count(sbi, dn->inode, !ofs))))
		जाओ fail;

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	err = f2fs_get_node_info(sbi, dn->nid, &new_ni);
	अगर (err) अणु
		dec_valid_node_count(sbi, dn->inode, !ofs);
		जाओ fail;
	पूर्ण
	f2fs_bug_on(sbi, new_ni.blk_addr != शून्य_ADDR);
#पूर्ण_अगर
	new_ni.nid = dn->nid;
	new_ni.ino = dn->inode->i_ino;
	new_ni.blk_addr = शून्य_ADDR;
	new_ni.flag = 0;
	new_ni.version = 0;
	set_node_addr(sbi, &new_ni, NEW_ADDR, false);

	f2fs_रुको_on_page_ग_लिखोback(page, NODE, true, true);
	fill_node_footer(page, dn->nid, dn->inode->i_ino, ofs, true);
	set_cold_node(page, S_ISसूची(dn->inode->i_mode));
	अगर (!PageUptodate(page))
		SetPageUptodate(page);
	अगर (set_page_dirty(page))
		dn->node_changed = true;

	अगर (f2fs_has_xattr_block(ofs))
		f2fs_i_xnid_ग_लिखो(dn->inode, dn->nid);

	अगर (ofs == 0)
		inc_valid_inode_count(sbi);
	वापस page;

fail:
	clear_node_page_dirty(page);
	f2fs_put_page(page, 1);
	वापस ERR_PTR(err);
पूर्ण

/*
 * Caller should करो after getting the following values.
 * 0: f2fs_put_page(page, 0)
 * LOCKED_PAGE or error: f2fs_put_page(page, 1)
 */
अटल पूर्णांक पढ़ो_node_page(काष्ठा page *page, पूर्णांक op_flags)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_P_SB(page);
	काष्ठा node_info ni;
	काष्ठा f2fs_io_info fio = अणु
		.sbi = sbi,
		.type = NODE,
		.op = REQ_OP_READ,
		.op_flags = op_flags,
		.page = page,
		.encrypted_page = शून्य,
	पूर्ण;
	पूर्णांक err;

	अगर (PageUptodate(page)) अणु
		अगर (!f2fs_inode_chksum_verअगरy(sbi, page)) अणु
			ClearPageUptodate(page);
			वापस -EFSBADCRC;
		पूर्ण
		वापस LOCKED_PAGE;
	पूर्ण

	err = f2fs_get_node_info(sbi, page->index, &ni);
	अगर (err)
		वापस err;

	अगर (unlikely(ni.blk_addr == शून्य_ADDR) ||
			is_sbi_flag_set(sbi, SBI_IS_SHUTDOWN)) अणु
		ClearPageUptodate(page);
		वापस -ENOENT;
	पूर्ण

	fio.new_blkaddr = fio.old_blkaddr = ni.blk_addr;

	err = f2fs_submit_page_bio(&fio);

	अगर (!err)
		f2fs_update_iostat(sbi, FS_NODE_READ_IO, F2FS_BLKSIZE);

	वापस err;
पूर्ण

/*
 * Readahead a node page
 */
व्योम f2fs_ra_node_page(काष्ठा f2fs_sb_info *sbi, nid_t nid)
अणु
	काष्ठा page *apage;
	पूर्णांक err;

	अगर (!nid)
		वापस;
	अगर (f2fs_check_nid_range(sbi, nid))
		वापस;

	apage = xa_load(&NODE_MAPPING(sbi)->i_pages, nid);
	अगर (apage)
		वापस;

	apage = f2fs_grab_cache_page(NODE_MAPPING(sbi), nid, false);
	अगर (!apage)
		वापस;

	err = पढ़ो_node_page(apage, REQ_RAHEAD);
	f2fs_put_page(apage, err ? 1 : 0);
पूर्ण

अटल काष्ठा page *__get_node_page(काष्ठा f2fs_sb_info *sbi, pgoff_t nid,
					काष्ठा page *parent, पूर्णांक start)
अणु
	काष्ठा page *page;
	पूर्णांक err;

	अगर (!nid)
		वापस ERR_PTR(-ENOENT);
	अगर (f2fs_check_nid_range(sbi, nid))
		वापस ERR_PTR(-EINVAL);
repeat:
	page = f2fs_grab_cache_page(NODE_MAPPING(sbi), nid, false);
	अगर (!page)
		वापस ERR_PTR(-ENOMEM);

	err = पढ़ो_node_page(page, 0);
	अगर (err < 0) अणु
		f2fs_put_page(page, 1);
		वापस ERR_PTR(err);
	पूर्ण अन्यथा अगर (err == LOCKED_PAGE) अणु
		err = 0;
		जाओ page_hit;
	पूर्ण

	अगर (parent)
		f2fs_ra_node_pages(parent, start + 1, MAX_RA_NODE);

	lock_page(page);

	अगर (unlikely(page->mapping != NODE_MAPPING(sbi))) अणु
		f2fs_put_page(page, 1);
		जाओ repeat;
	पूर्ण

	अगर (unlikely(!PageUptodate(page))) अणु
		err = -EIO;
		जाओ out_err;
	पूर्ण

	अगर (!f2fs_inode_chksum_verअगरy(sbi, page)) अणु
		err = -EFSBADCRC;
		जाओ out_err;
	पूर्ण
page_hit:
	अगर (unlikely(nid != nid_of_node(page))) अणु
		f2fs_warn(sbi, "inconsistent node block, nid:%lu, node_footer[nid:%u,ino:%u,ofs:%u,cpver:%llu,blkaddr:%u]",
			  nid, nid_of_node(page), ino_of_node(page),
			  ofs_of_node(page), cpver_of_node(page),
			  next_blkaddr_of_node(page));
		err = -EINVAL;
out_err:
		ClearPageUptodate(page);
		f2fs_put_page(page, 1);
		वापस ERR_PTR(err);
	पूर्ण
	वापस page;
पूर्ण

काष्ठा page *f2fs_get_node_page(काष्ठा f2fs_sb_info *sbi, pgoff_t nid)
अणु
	वापस __get_node_page(sbi, nid, शून्य, 0);
पूर्ण

काष्ठा page *f2fs_get_node_page_ra(काष्ठा page *parent, पूर्णांक start)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_P_SB(parent);
	nid_t nid = get_nid(parent, start, false);

	वापस __get_node_page(sbi, nid, parent, start);
पूर्ण

अटल व्योम flush_अंतरभूत_data(काष्ठा f2fs_sb_info *sbi, nid_t ino)
अणु
	काष्ठा inode *inode;
	काष्ठा page *page;
	पूर्णांक ret;

	/* should flush अंतरभूत_data beक्रमe evict_inode */
	inode = ilookup(sbi->sb, ino);
	अगर (!inode)
		वापस;

	page = f2fs_pagecache_get_page(inode->i_mapping, 0,
					FGP_LOCK|FGP_NOWAIT, 0);
	अगर (!page)
		जाओ iput_out;

	अगर (!PageUptodate(page))
		जाओ page_out;

	अगर (!PageDirty(page))
		जाओ page_out;

	अगर (!clear_page_dirty_क्रम_io(page))
		जाओ page_out;

	ret = f2fs_ग_लिखो_अंतरभूत_data(inode, page);
	inode_dec_dirty_pages(inode);
	f2fs_हटाओ_dirty_inode(inode);
	अगर (ret)
		set_page_dirty(page);
page_out:
	f2fs_put_page(page, 1);
iput_out:
	iput(inode);
पूर्ण

अटल काष्ठा page *last_fsync_dnode(काष्ठा f2fs_sb_info *sbi, nid_t ino)
अणु
	pgoff_t index;
	काष्ठा pagevec pvec;
	काष्ठा page *last_page = शून्य;
	पूर्णांक nr_pages;

	pagevec_init(&pvec);
	index = 0;

	जबतक ((nr_pages = pagevec_lookup_tag(&pvec, NODE_MAPPING(sbi), &index,
				PAGECACHE_TAG_सूचीTY))) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			अगर (unlikely(f2fs_cp_error(sbi))) अणु
				f2fs_put_page(last_page, 0);
				pagevec_release(&pvec);
				वापस ERR_PTR(-EIO);
			पूर्ण

			अगर (!IS_DNODE(page) || !is_cold_node(page))
				जारी;
			अगर (ino_of_node(page) != ino)
				जारी;

			lock_page(page);

			अगर (unlikely(page->mapping != NODE_MAPPING(sbi))) अणु
जारी_unlock:
				unlock_page(page);
				जारी;
			पूर्ण
			अगर (ino_of_node(page) != ino)
				जाओ जारी_unlock;

			अगर (!PageDirty(page)) अणु
				/* someone wrote it क्रम us */
				जाओ जारी_unlock;
			पूर्ण

			अगर (last_page)
				f2fs_put_page(last_page, 0);

			get_page(page);
			last_page = page;
			unlock_page(page);
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
	वापस last_page;
पूर्ण

अटल पूर्णांक __ग_लिखो_node_page(काष्ठा page *page, bool atomic, bool *submitted,
				काष्ठा ग_लिखोback_control *wbc, bool करो_balance,
				क्रमागत iostat_type io_type, अचिन्हित पूर्णांक *seq_id)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_P_SB(page);
	nid_t nid;
	काष्ठा node_info ni;
	काष्ठा f2fs_io_info fio = अणु
		.sbi = sbi,
		.ino = ino_of_node(page),
		.type = NODE,
		.op = REQ_OP_WRITE,
		.op_flags = wbc_to_ग_लिखो_flags(wbc),
		.page = page,
		.encrypted_page = शून्य,
		.submitted = false,
		.io_type = io_type,
		.io_wbc = wbc,
	पूर्ण;
	अचिन्हित पूर्णांक seq;

	trace_f2fs_ग_लिखोpage(page, NODE);

	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		अगर (is_sbi_flag_set(sbi, SBI_IS_CLOSE)) अणु
			ClearPageUptodate(page);
			dec_page_count(sbi, F2FS_सूचीTY_NODES);
			unlock_page(page);
			वापस 0;
		पूर्ण
		जाओ redirty_out;
	पूर्ण

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		जाओ redirty_out;

	अगर (!is_sbi_flag_set(sbi, SBI_CP_DISABLED) &&
			wbc->sync_mode == WB_SYNC_NONE &&
			IS_DNODE(page) && is_cold_node(page))
		जाओ redirty_out;

	/* get old block addr of this node page */
	nid = nid_of_node(page);
	f2fs_bug_on(sbi, page->index != nid);

	अगर (f2fs_get_node_info(sbi, nid, &ni))
		जाओ redirty_out;

	अगर (wbc->क्रम_reclaim) अणु
		अगर (!करोwn_पढ़ो_trylock(&sbi->node_ग_लिखो))
			जाओ redirty_out;
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&sbi->node_ग_लिखो);
	पूर्ण

	/* This page is alपढ़ोy truncated */
	अगर (unlikely(ni.blk_addr == शून्य_ADDR)) अणु
		ClearPageUptodate(page);
		dec_page_count(sbi, F2FS_सूचीTY_NODES);
		up_पढ़ो(&sbi->node_ग_लिखो);
		unlock_page(page);
		वापस 0;
	पूर्ण

	अगर (__is_valid_data_blkaddr(ni.blk_addr) &&
		!f2fs_is_valid_blkaddr(sbi, ni.blk_addr,
					DATA_GENERIC_ENHANCE)) अणु
		up_पढ़ो(&sbi->node_ग_लिखो);
		जाओ redirty_out;
	पूर्ण

	अगर (atomic && !test_opt(sbi, NOBARRIER))
		fio.op_flags |= REQ_PREFLUSH | REQ_FUA;

	/* should add to global list beक्रमe clearing PAGECACHE status */
	अगर (f2fs_in_warm_node_list(sbi, page)) अणु
		seq = f2fs_add_fsync_node_entry(sbi, page);
		अगर (seq_id)
			*seq_id = seq;
	पूर्ण

	set_page_ग_लिखोback(page);
	ClearPageError(page);

	fio.old_blkaddr = ni.blk_addr;
	f2fs_करो_ग_लिखो_node_page(nid, &fio);
	set_node_addr(sbi, &ni, fio.new_blkaddr, is_fsync_dnode(page));
	dec_page_count(sbi, F2FS_सूचीTY_NODES);
	up_पढ़ो(&sbi->node_ग_लिखो);

	अगर (wbc->क्रम_reclaim) अणु
		f2fs_submit_merged_ग_लिखो_cond(sbi, शून्य, page, 0, NODE);
		submitted = शून्य;
	पूर्ण

	unlock_page(page);

	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		f2fs_submit_merged_ग_लिखो(sbi, NODE);
		submitted = शून्य;
	पूर्ण
	अगर (submitted)
		*submitted = fio.submitted;

	अगर (करो_balance)
		f2fs_balance_fs(sbi, false);
	वापस 0;

redirty_out:
	redirty_page_क्रम_ग_लिखोpage(wbc, page);
	वापस AOP_WRITEPAGE_ACTIVATE;
पूर्ण

पूर्णांक f2fs_move_node_page(काष्ठा page *node_page, पूर्णांक gc_type)
अणु
	पूर्णांक err = 0;

	अगर (gc_type == FG_GC) अणु
		काष्ठा ग_लिखोback_control wbc = अणु
			.sync_mode = WB_SYNC_ALL,
			.nr_to_ग_लिखो = 1,
			.क्रम_reclaim = 0,
		पूर्ण;

		f2fs_रुको_on_page_ग_लिखोback(node_page, NODE, true, true);

		set_page_dirty(node_page);

		अगर (!clear_page_dirty_क्रम_io(node_page)) अणु
			err = -EAGAIN;
			जाओ out_page;
		पूर्ण

		अगर (__ग_लिखो_node_page(node_page, false, शून्य,
					&wbc, false, FS_GC_NODE_IO, शून्य)) अणु
			err = -EAGAIN;
			unlock_page(node_page);
		पूर्ण
		जाओ release_page;
	पूर्ण अन्यथा अणु
		/* set page dirty and ग_लिखो it */
		अगर (!PageWriteback(node_page))
			set_page_dirty(node_page);
	पूर्ण
out_page:
	unlock_page(node_page);
release_page:
	f2fs_put_page(node_page, 0);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_node_page(काष्ठा page *page,
				काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस __ग_लिखो_node_page(page, false, शून्य, wbc, false,
						FS_NODE_IO, शून्य);
पूर्ण

पूर्णांक f2fs_fsync_node_pages(काष्ठा f2fs_sb_info *sbi, काष्ठा inode *inode,
			काष्ठा ग_लिखोback_control *wbc, bool atomic,
			अचिन्हित पूर्णांक *seq_id)
अणु
	pgoff_t index;
	काष्ठा pagevec pvec;
	पूर्णांक ret = 0;
	काष्ठा page *last_page = शून्य;
	bool marked = false;
	nid_t ino = inode->i_ino;
	पूर्णांक nr_pages;
	पूर्णांक nwritten = 0;

	अगर (atomic) अणु
		last_page = last_fsync_dnode(sbi, ino);
		अगर (IS_ERR_OR_शून्य(last_page))
			वापस PTR_ERR_OR_ZERO(last_page);
	पूर्ण
retry:
	pagevec_init(&pvec);
	index = 0;

	जबतक ((nr_pages = pagevec_lookup_tag(&pvec, NODE_MAPPING(sbi), &index,
				PAGECACHE_TAG_सूचीTY))) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];
			bool submitted = false;

			अगर (unlikely(f2fs_cp_error(sbi))) अणु
				f2fs_put_page(last_page, 0);
				pagevec_release(&pvec);
				ret = -EIO;
				जाओ out;
			पूर्ण

			अगर (!IS_DNODE(page) || !is_cold_node(page))
				जारी;
			अगर (ino_of_node(page) != ino)
				जारी;

			lock_page(page);

			अगर (unlikely(page->mapping != NODE_MAPPING(sbi))) अणु
जारी_unlock:
				unlock_page(page);
				जारी;
			पूर्ण
			अगर (ino_of_node(page) != ino)
				जाओ जारी_unlock;

			अगर (!PageDirty(page) && page != last_page) अणु
				/* someone wrote it क्रम us */
				जाओ जारी_unlock;
			पूर्ण

			f2fs_रुको_on_page_ग_लिखोback(page, NODE, true, true);

			set_fsync_mark(page, 0);
			set_dentry_mark(page, 0);

			अगर (!atomic || page == last_page) अणु
				set_fsync_mark(page, 1);
				अगर (IS_INODE(page)) अणु
					अगर (is_inode_flag_set(inode,
								FI_सूचीTY_INODE))
						f2fs_update_inode(inode, page);
					set_dentry_mark(page,
						f2fs_need_dentry_mark(sbi, ino));
				पूर्ण
				/* may be written by other thपढ़ो */
				अगर (!PageDirty(page))
					set_page_dirty(page);
			पूर्ण

			अगर (!clear_page_dirty_क्रम_io(page))
				जाओ जारी_unlock;

			ret = __ग_लिखो_node_page(page, atomic &&
						page == last_page,
						&submitted, wbc, true,
						FS_NODE_IO, seq_id);
			अगर (ret) अणु
				unlock_page(page);
				f2fs_put_page(last_page, 0);
				अवरोध;
			पूर्ण अन्यथा अगर (submitted) अणु
				nwritten++;
			पूर्ण

			अगर (page == last_page) अणु
				f2fs_put_page(page, 0);
				marked = true;
				अवरोध;
			पूर्ण
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();

		अगर (ret || marked)
			अवरोध;
	पूर्ण
	अगर (!ret && atomic && !marked) अणु
		f2fs_debug(sbi, "Retry to write fsync mark: ino=%u, idx=%lx",
			   ino, last_page->index);
		lock_page(last_page);
		f2fs_रुको_on_page_ग_लिखोback(last_page, NODE, true, true);
		set_page_dirty(last_page);
		unlock_page(last_page);
		जाओ retry;
	पूर्ण
out:
	अगर (nwritten)
		f2fs_submit_merged_ग_लिखो_cond(sbi, शून्य, शून्य, ino, NODE);
	वापस ret ? -EIO : 0;
पूर्ण

अटल पूर्णांक f2fs_match_ino(काष्ठा inode *inode, अचिन्हित दीर्घ ino, व्योम *data)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	bool clean;

	अगर (inode->i_ino != ino)
		वापस 0;

	अगर (!is_inode_flag_set(inode, FI_सूचीTY_INODE))
		वापस 0;

	spin_lock(&sbi->inode_lock[सूचीTY_META]);
	clean = list_empty(&F2FS_I(inode)->gdirty_list);
	spin_unlock(&sbi->inode_lock[सूचीTY_META]);

	अगर (clean)
		वापस 0;

	inode = igrab(inode);
	अगर (!inode)
		वापस 0;
	वापस 1;
पूर्ण

अटल bool flush_dirty_inode(काष्ठा page *page)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_P_SB(page);
	काष्ठा inode *inode;
	nid_t ino = ino_of_node(page);

	inode = find_inode_noरुको(sbi->sb, ino, f2fs_match_ino, शून्य);
	अगर (!inode)
		वापस false;

	f2fs_update_inode(inode, page);
	unlock_page(page);

	iput(inode);
	वापस true;
पूर्ण

व्योम f2fs_flush_अंतरभूत_data(काष्ठा f2fs_sb_info *sbi)
अणु
	pgoff_t index = 0;
	काष्ठा pagevec pvec;
	पूर्णांक nr_pages;

	pagevec_init(&pvec);

	जबतक ((nr_pages = pagevec_lookup_tag(&pvec,
			NODE_MAPPING(sbi), &index, PAGECACHE_TAG_सूचीTY))) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			अगर (!IS_DNODE(page))
				जारी;

			lock_page(page);

			अगर (unlikely(page->mapping != NODE_MAPPING(sbi))) अणु
जारी_unlock:
				unlock_page(page);
				जारी;
			पूर्ण

			अगर (!PageDirty(page)) अणु
				/* someone wrote it क्रम us */
				जाओ जारी_unlock;
			पूर्ण

			/* flush अंतरभूत_data, अगर it's async context. */
			अगर (is_अंतरभूत_node(page)) अणु
				clear_अंतरभूत_node(page);
				unlock_page(page);
				flush_अंतरभूत_data(sbi, ino_of_node(page));
				जारी;
			पूर्ण
			unlock_page(page);
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
पूर्ण

पूर्णांक f2fs_sync_node_pages(काष्ठा f2fs_sb_info *sbi,
				काष्ठा ग_लिखोback_control *wbc,
				bool करो_balance, क्रमागत iostat_type io_type)
अणु
	pgoff_t index;
	काष्ठा pagevec pvec;
	पूर्णांक step = 0;
	पूर्णांक nwritten = 0;
	पूर्णांक ret = 0;
	पूर्णांक nr_pages, करोne = 0;

	pagevec_init(&pvec);

next_step:
	index = 0;

	जबतक (!करोne && (nr_pages = pagevec_lookup_tag(&pvec,
			NODE_MAPPING(sbi), &index, PAGECACHE_TAG_सूचीTY))) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];
			bool submitted = false;
			bool may_dirty = true;

			/* give a priority to WB_SYNC thपढ़ोs */
			अगर (atomic_पढ़ो(&sbi->wb_sync_req[NODE]) &&
					wbc->sync_mode == WB_SYNC_NONE) अणु
				करोne = 1;
				अवरोध;
			पूर्ण

			/*
			 * flushing sequence with step:
			 * 0. indirect nodes
			 * 1. dentry dnodes
			 * 2. file dnodes
			 */
			अगर (step == 0 && IS_DNODE(page))
				जारी;
			अगर (step == 1 && (!IS_DNODE(page) ||
						is_cold_node(page)))
				जारी;
			अगर (step == 2 && (!IS_DNODE(page) ||
						!is_cold_node(page)))
				जारी;
lock_node:
			अगर (wbc->sync_mode == WB_SYNC_ALL)
				lock_page(page);
			अन्यथा अगर (!trylock_page(page))
				जारी;

			अगर (unlikely(page->mapping != NODE_MAPPING(sbi))) अणु
जारी_unlock:
				unlock_page(page);
				जारी;
			पूर्ण

			अगर (!PageDirty(page)) अणु
				/* someone wrote it क्रम us */
				जाओ जारी_unlock;
			पूर्ण

			/* flush अंतरभूत_data/inode, अगर it's async context. */
			अगर (!करो_balance)
				जाओ ग_लिखो_node;

			/* flush अंतरभूत_data */
			अगर (is_अंतरभूत_node(page)) अणु
				clear_अंतरभूत_node(page);
				unlock_page(page);
				flush_अंतरभूत_data(sbi, ino_of_node(page));
				जाओ lock_node;
			पूर्ण

			/* flush dirty inode */
			अगर (IS_INODE(page) && may_dirty) अणु
				may_dirty = false;
				अगर (flush_dirty_inode(page))
					जाओ lock_node;
			पूर्ण
ग_लिखो_node:
			f2fs_रुको_on_page_ग_लिखोback(page, NODE, true, true);

			अगर (!clear_page_dirty_क्रम_io(page))
				जाओ जारी_unlock;

			set_fsync_mark(page, 0);
			set_dentry_mark(page, 0);

			ret = __ग_लिखो_node_page(page, false, &submitted,
						wbc, करो_balance, io_type, शून्य);
			अगर (ret)
				unlock_page(page);
			अन्यथा अगर (submitted)
				nwritten++;

			अगर (--wbc->nr_to_ग_लिखो == 0)
				अवरोध;
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();

		अगर (wbc->nr_to_ग_लिखो == 0) अणु
			step = 2;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (step < 2) अणु
		अगर (!is_sbi_flag_set(sbi, SBI_CP_DISABLED) &&
				wbc->sync_mode == WB_SYNC_NONE && step == 1)
			जाओ out;
		step++;
		जाओ next_step;
	पूर्ण
out:
	अगर (nwritten)
		f2fs_submit_merged_ग_लिखो(sbi, NODE);

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;
	वापस ret;
पूर्ण

पूर्णांक f2fs_रुको_on_node_pages_ग_लिखोback(काष्ठा f2fs_sb_info *sbi,
						अचिन्हित पूर्णांक seq_id)
अणु
	काष्ठा fsync_node_entry *fn;
	काष्ठा page *page;
	काष्ठा list_head *head = &sbi->fsync_node_list;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cur_seq_id = 0;
	पूर्णांक ret2, ret = 0;

	जबतक (seq_id && cur_seq_id < seq_id) अणु
		spin_lock_irqsave(&sbi->fsync_node_lock, flags);
		अगर (list_empty(head)) अणु
			spin_unlock_irqrestore(&sbi->fsync_node_lock, flags);
			अवरोध;
		पूर्ण
		fn = list_first_entry(head, काष्ठा fsync_node_entry, list);
		अगर (fn->seq_id > seq_id) अणु
			spin_unlock_irqrestore(&sbi->fsync_node_lock, flags);
			अवरोध;
		पूर्ण
		cur_seq_id = fn->seq_id;
		page = fn->page;
		get_page(page);
		spin_unlock_irqrestore(&sbi->fsync_node_lock, flags);

		f2fs_रुको_on_page_ग_लिखोback(page, NODE, true, false);
		अगर (TestClearPageError(page))
			ret = -EIO;

		put_page(page);

		अगर (ret)
			अवरोध;
	पूर्ण

	ret2 = filemap_check_errors(NODE_MAPPING(sbi));
	अगर (!ret)
		ret = ret2;

	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_node_pages(काष्ठा address_space *mapping,
			    काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_M_SB(mapping);
	काष्ठा blk_plug plug;
	दीर्घ dअगरf;

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		जाओ skip_ग_लिखो;

	/* balancing f2fs's metadata in background */
	f2fs_balance_fs_bg(sbi, true);

	/* collect a number of dirty node pages and ग_लिखो together */
	अगर (wbc->sync_mode != WB_SYNC_ALL &&
			get_pages(sbi, F2FS_सूचीTY_NODES) <
					nr_pages_to_skip(sbi, NODE))
		जाओ skip_ग_लिखो;

	अगर (wbc->sync_mode == WB_SYNC_ALL)
		atomic_inc(&sbi->wb_sync_req[NODE]);
	अन्यथा अगर (atomic_पढ़ो(&sbi->wb_sync_req[NODE]))
		जाओ skip_ग_लिखो;

	trace_f2fs_ग_लिखोpages(mapping->host, wbc, NODE);

	dअगरf = nr_pages_to_ग_लिखो(sbi, NODE, wbc);
	blk_start_plug(&plug);
	f2fs_sync_node_pages(sbi, wbc, true, FS_NODE_IO);
	blk_finish_plug(&plug);
	wbc->nr_to_ग_लिखो = max((दीर्घ)0, wbc->nr_to_ग_लिखो - dअगरf);

	अगर (wbc->sync_mode == WB_SYNC_ALL)
		atomic_dec(&sbi->wb_sync_req[NODE]);
	वापस 0;

skip_ग_लिखो:
	wbc->pages_skipped += get_pages(sbi, F2FS_सूचीTY_NODES);
	trace_f2fs_ग_लिखोpages(mapping->host, wbc, NODE);
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_set_node_page_dirty(काष्ठा page *page)
अणु
	trace_f2fs_set_page_dirty(page, NODE);

	अगर (!PageUptodate(page))
		SetPageUptodate(page);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	अगर (IS_INODE(page))
		f2fs_inode_chksum_set(F2FS_P_SB(page), page);
#पूर्ण_अगर
	अगर (!PageDirty(page)) अणु
		__set_page_dirty_nobuffers(page);
		inc_page_count(F2FS_P_SB(page), F2FS_सूचीTY_NODES);
		f2fs_set_page_निजी(page, 0);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Structure of the f2fs node operations
 */
स्थिर काष्ठा address_space_operations f2fs_node_aops = अणु
	.ग_लिखोpage	= f2fs_ग_लिखो_node_page,
	.ग_लिखोpages	= f2fs_ग_लिखो_node_pages,
	.set_page_dirty	= f2fs_set_node_page_dirty,
	.invalidatepage	= f2fs_invalidate_page,
	.releasepage	= f2fs_release_page,
#अगर_घोषित CONFIG_MIGRATION
	.migratepage	= f2fs_migrate_page,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा मुक्त_nid *__lookup_मुक्त_nid_list(काष्ठा f2fs_nm_info *nm_i,
						nid_t n)
अणु
	वापस radix_tree_lookup(&nm_i->मुक्त_nid_root, n);
पूर्ण

अटल पूर्णांक __insert_मुक्त_nid(काष्ठा f2fs_sb_info *sbi,
				काष्ठा मुक्त_nid *i)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	पूर्णांक err = radix_tree_insert(&nm_i->मुक्त_nid_root, i->nid, i);

	अगर (err)
		वापस err;

	nm_i->nid_cnt[FREE_NID]++;
	list_add_tail(&i->list, &nm_i->मुक्त_nid_list);
	वापस 0;
पूर्ण

अटल व्योम __हटाओ_मुक्त_nid(काष्ठा f2fs_sb_info *sbi,
			काष्ठा मुक्त_nid *i, क्रमागत nid_state state)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);

	f2fs_bug_on(sbi, state != i->state);
	nm_i->nid_cnt[state]--;
	अगर (state == FREE_NID)
		list_del(&i->list);
	radix_tree_delete(&nm_i->मुक्त_nid_root, i->nid);
पूर्ण

अटल व्योम __move_मुक्त_nid(काष्ठा f2fs_sb_info *sbi, काष्ठा मुक्त_nid *i,
			क्रमागत nid_state org_state, क्रमागत nid_state dst_state)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);

	f2fs_bug_on(sbi, org_state != i->state);
	i->state = dst_state;
	nm_i->nid_cnt[org_state]--;
	nm_i->nid_cnt[dst_state]++;

	चयन (dst_state) अणु
	हाल PREALLOC_NID:
		list_del(&i->list);
		अवरोध;
	हाल FREE_NID:
		list_add_tail(&i->list, &nm_i->मुक्त_nid_list);
		अवरोध;
	शेष:
		BUG_ON(1);
	पूर्ण
पूर्ण

अटल व्योम update_मुक्त_nid_biपंचांगap(काष्ठा f2fs_sb_info *sbi, nid_t nid,
							bool set, bool build)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	अचिन्हित पूर्णांक nat_ofs = NAT_BLOCK_OFFSET(nid);
	अचिन्हित पूर्णांक nid_ofs = nid - START_NID(nid);

	अगर (!test_bit_le(nat_ofs, nm_i->nat_block_biपंचांगap))
		वापस;

	अगर (set) अणु
		अगर (test_bit_le(nid_ofs, nm_i->मुक्त_nid_biपंचांगap[nat_ofs]))
			वापस;
		__set_bit_le(nid_ofs, nm_i->मुक्त_nid_biपंचांगap[nat_ofs]);
		nm_i->मुक्त_nid_count[nat_ofs]++;
	पूर्ण अन्यथा अणु
		अगर (!test_bit_le(nid_ofs, nm_i->मुक्त_nid_biपंचांगap[nat_ofs]))
			वापस;
		__clear_bit_le(nid_ofs, nm_i->मुक्त_nid_biपंचांगap[nat_ofs]);
		अगर (!build)
			nm_i->मुक्त_nid_count[nat_ofs]--;
	पूर्ण
पूर्ण

/* वापस अगर the nid is recognized as मुक्त */
अटल bool add_मुक्त_nid(काष्ठा f2fs_sb_info *sbi,
				nid_t nid, bool build, bool update)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा मुक्त_nid *i, *e;
	काष्ठा nat_entry *ne;
	पूर्णांक err = -EINVAL;
	bool ret = false;

	/* 0 nid should not be used */
	अगर (unlikely(nid == 0))
		वापस false;

	अगर (unlikely(f2fs_check_nid_range(sbi, nid)))
		वापस false;

	i = f2fs_kmem_cache_alloc(मुक्त_nid_slab, GFP_NOFS);
	i->nid = nid;
	i->state = FREE_NID;

	radix_tree_preload(GFP_NOFS | __GFP_NOFAIL);

	spin_lock(&nm_i->nid_list_lock);

	अगर (build) अणु
		/*
		 *   Thपढ़ो A             Thपढ़ो B
		 *  - f2fs_create
		 *   - f2fs_new_inode
		 *    - f2fs_alloc_nid
		 *     - __insert_nid_to_list(PREALLOC_NID)
		 *                     - f2fs_balance_fs_bg
		 *                      - f2fs_build_मुक्त_nids
		 *                       - __f2fs_build_मुक्त_nids
		 *                        - scan_nat_page
		 *                         - add_मुक्त_nid
		 *                          - __lookup_nat_cache
		 *  - f2fs_add_link
		 *   - f2fs_init_inode_metadata
		 *    - f2fs_new_inode_page
		 *     - f2fs_new_node_page
		 *      - set_node_addr
		 *  - f2fs_alloc_nid_करोne
		 *   - __हटाओ_nid_from_list(PREALLOC_NID)
		 *                         - __insert_nid_to_list(FREE_NID)
		 */
		ne = __lookup_nat_cache(nm_i, nid);
		अगर (ne && (!get_nat_flag(ne, IS_CHECKPOINTED) ||
				nat_get_blkaddr(ne) != शून्य_ADDR))
			जाओ err_out;

		e = __lookup_मुक्त_nid_list(nm_i, nid);
		अगर (e) अणु
			अगर (e->state == FREE_NID)
				ret = true;
			जाओ err_out;
		पूर्ण
	पूर्ण
	ret = true;
	err = __insert_मुक्त_nid(sbi, i);
err_out:
	अगर (update) अणु
		update_मुक्त_nid_biपंचांगap(sbi, nid, ret, build);
		अगर (!build)
			nm_i->available_nids++;
	पूर्ण
	spin_unlock(&nm_i->nid_list_lock);
	radix_tree_preload_end();

	अगर (err)
		kmem_cache_मुक्त(मुक्त_nid_slab, i);
	वापस ret;
पूर्ण

अटल व्योम हटाओ_मुक्त_nid(काष्ठा f2fs_sb_info *sbi, nid_t nid)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा मुक्त_nid *i;
	bool need_मुक्त = false;

	spin_lock(&nm_i->nid_list_lock);
	i = __lookup_मुक्त_nid_list(nm_i, nid);
	अगर (i && i->state == FREE_NID) अणु
		__हटाओ_मुक्त_nid(sbi, i, FREE_NID);
		need_मुक्त = true;
	पूर्ण
	spin_unlock(&nm_i->nid_list_lock);

	अगर (need_मुक्त)
		kmem_cache_मुक्त(मुक्त_nid_slab, i);
पूर्ण

अटल पूर्णांक scan_nat_page(काष्ठा f2fs_sb_info *sbi,
			काष्ठा page *nat_page, nid_t start_nid)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा f2fs_nat_block *nat_blk = page_address(nat_page);
	block_t blk_addr;
	अचिन्हित पूर्णांक nat_ofs = NAT_BLOCK_OFFSET(start_nid);
	पूर्णांक i;

	__set_bit_le(nat_ofs, nm_i->nat_block_biपंचांगap);

	i = start_nid % NAT_ENTRY_PER_BLOCK;

	क्रम (; i < NAT_ENTRY_PER_BLOCK; i++, start_nid++) अणु
		अगर (unlikely(start_nid >= nm_i->max_nid))
			अवरोध;

		blk_addr = le32_to_cpu(nat_blk->entries[i].block_addr);

		अगर (blk_addr == NEW_ADDR)
			वापस -EINVAL;

		अगर (blk_addr == शून्य_ADDR) अणु
			add_मुक्त_nid(sbi, start_nid, true, true);
		पूर्ण अन्यथा अणु
			spin_lock(&NM_I(sbi)->nid_list_lock);
			update_मुक्त_nid_biपंचांगap(sbi, start_nid, false, true);
			spin_unlock(&NM_I(sbi)->nid_list_lock);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम scan_curseg_cache(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, CURSEG_HOT_DATA);
	काष्ठा f2fs_journal *journal = curseg->journal;
	पूर्णांक i;

	करोwn_पढ़ो(&curseg->journal_rwsem);
	क्रम (i = 0; i < nats_in_cursum(journal); i++) अणु
		block_t addr;
		nid_t nid;

		addr = le32_to_cpu(nat_in_journal(journal, i).block_addr);
		nid = le32_to_cpu(nid_in_journal(journal, i));
		अगर (addr == शून्य_ADDR)
			add_मुक्त_nid(sbi, nid, true, false);
		अन्यथा
			हटाओ_मुक्त_nid(sbi, nid);
	पूर्ण
	up_पढ़ो(&curseg->journal_rwsem);
पूर्ण

अटल व्योम scan_मुक्त_nid_bits(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	अचिन्हित पूर्णांक i, idx;
	nid_t nid;

	करोwn_पढ़ो(&nm_i->nat_tree_lock);

	क्रम (i = 0; i < nm_i->nat_blocks; i++) अणु
		अगर (!test_bit_le(i, nm_i->nat_block_biपंचांगap))
			जारी;
		अगर (!nm_i->मुक्त_nid_count[i])
			जारी;
		क्रम (idx = 0; idx < NAT_ENTRY_PER_BLOCK; idx++) अणु
			idx = find_next_bit_le(nm_i->मुक्त_nid_biपंचांगap[i],
						NAT_ENTRY_PER_BLOCK, idx);
			अगर (idx >= NAT_ENTRY_PER_BLOCK)
				अवरोध;

			nid = i * NAT_ENTRY_PER_BLOCK + idx;
			add_मुक्त_nid(sbi, nid, true, false);

			अगर (nm_i->nid_cnt[FREE_NID] >= MAX_FREE_NIDS)
				जाओ out;
		पूर्ण
	पूर्ण
out:
	scan_curseg_cache(sbi);

	up_पढ़ो(&nm_i->nat_tree_lock);
पूर्ण

अटल पूर्णांक __f2fs_build_मुक्त_nids(काष्ठा f2fs_sb_info *sbi,
						bool sync, bool mount)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	पूर्णांक i = 0, ret;
	nid_t nid = nm_i->next_scan_nid;

	अगर (unlikely(nid >= nm_i->max_nid))
		nid = 0;

	अगर (unlikely(nid % NAT_ENTRY_PER_BLOCK))
		nid = NAT_BLOCK_OFFSET(nid) * NAT_ENTRY_PER_BLOCK;

	/* Enough entries */
	अगर (nm_i->nid_cnt[FREE_NID] >= NAT_ENTRY_PER_BLOCK)
		वापस 0;

	अगर (!sync && !f2fs_available_मुक्त_memory(sbi, FREE_NIDS))
		वापस 0;

	अगर (!mount) अणु
		/* try to find मुक्त nids in मुक्त_nid_biपंचांगap */
		scan_मुक्त_nid_bits(sbi);

		अगर (nm_i->nid_cnt[FREE_NID] >= NAT_ENTRY_PER_BLOCK)
			वापस 0;
	पूर्ण

	/* पढ़ोahead nat pages to be scanned */
	f2fs_ra_meta_pages(sbi, NAT_BLOCK_OFFSET(nid), FREE_NID_PAGES,
							META_NAT, true);

	करोwn_पढ़ो(&nm_i->nat_tree_lock);

	जबतक (1) अणु
		अगर (!test_bit_le(NAT_BLOCK_OFFSET(nid),
						nm_i->nat_block_biपंचांगap)) अणु
			काष्ठा page *page = get_current_nat_page(sbi, nid);

			अगर (IS_ERR(page)) अणु
				ret = PTR_ERR(page);
			पूर्ण अन्यथा अणु
				ret = scan_nat_page(sbi, page, nid);
				f2fs_put_page(page, 1);
			पूर्ण

			अगर (ret) अणु
				up_पढ़ो(&nm_i->nat_tree_lock);
				f2fs_err(sbi, "NAT is corrupt, run fsck to fix it");
				वापस ret;
			पूर्ण
		पूर्ण

		nid += (NAT_ENTRY_PER_BLOCK - (nid % NAT_ENTRY_PER_BLOCK));
		अगर (unlikely(nid >= nm_i->max_nid))
			nid = 0;

		अगर (++i >= FREE_NID_PAGES)
			अवरोध;
	पूर्ण

	/* go to the next मुक्त nat pages to find मुक्त nids abundantly */
	nm_i->next_scan_nid = nid;

	/* find मुक्त nids from current sum_pages */
	scan_curseg_cache(sbi);

	up_पढ़ो(&nm_i->nat_tree_lock);

	f2fs_ra_meta_pages(sbi, NAT_BLOCK_OFFSET(nm_i->next_scan_nid),
					nm_i->ra_nid_pages, META_NAT, false);

	वापस 0;
पूर्ण

पूर्णांक f2fs_build_मुक्त_nids(काष्ठा f2fs_sb_info *sbi, bool sync, bool mount)
अणु
	पूर्णांक ret;

	mutex_lock(&NM_I(sbi)->build_lock);
	ret = __f2fs_build_मुक्त_nids(sbi, sync, mount);
	mutex_unlock(&NM_I(sbi)->build_lock);

	वापस ret;
पूर्ण

/*
 * If this function वापसs success, caller can obtain a new nid
 * from second parameter of this function.
 * The वापसed nid could be used ino as well as nid when inode is created.
 */
bool f2fs_alloc_nid(काष्ठा f2fs_sb_info *sbi, nid_t *nid)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा मुक्त_nid *i = शून्य;
retry:
	अगर (समय_प्रकारo_inject(sbi, FAULT_ALLOC_NID)) अणु
		f2fs_show_injection_info(sbi, FAULT_ALLOC_NID);
		वापस false;
	पूर्ण

	spin_lock(&nm_i->nid_list_lock);

	अगर (unlikely(nm_i->available_nids == 0)) अणु
		spin_unlock(&nm_i->nid_list_lock);
		वापस false;
	पूर्ण

	/* We should not use stale मुक्त nids created by f2fs_build_मुक्त_nids */
	अगर (nm_i->nid_cnt[FREE_NID] && !on_f2fs_build_मुक्त_nids(nm_i)) अणु
		f2fs_bug_on(sbi, list_empty(&nm_i->मुक्त_nid_list));
		i = list_first_entry(&nm_i->मुक्त_nid_list,
					काष्ठा मुक्त_nid, list);
		*nid = i->nid;

		__move_मुक्त_nid(sbi, i, FREE_NID, PREALLOC_NID);
		nm_i->available_nids--;

		update_मुक्त_nid_biपंचांगap(sbi, *nid, false, false);

		spin_unlock(&nm_i->nid_list_lock);
		वापस true;
	पूर्ण
	spin_unlock(&nm_i->nid_list_lock);

	/* Let's scan nat pages and its caches to get मुक्त nids */
	अगर (!f2fs_build_मुक्त_nids(sbi, true, false))
		जाओ retry;
	वापस false;
पूर्ण

/*
 * f2fs_alloc_nid() should be called prior to this function.
 */
व्योम f2fs_alloc_nid_करोne(काष्ठा f2fs_sb_info *sbi, nid_t nid)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा मुक्त_nid *i;

	spin_lock(&nm_i->nid_list_lock);
	i = __lookup_मुक्त_nid_list(nm_i, nid);
	f2fs_bug_on(sbi, !i);
	__हटाओ_मुक्त_nid(sbi, i, PREALLOC_NID);
	spin_unlock(&nm_i->nid_list_lock);

	kmem_cache_मुक्त(मुक्त_nid_slab, i);
पूर्ण

/*
 * f2fs_alloc_nid() should be called prior to this function.
 */
व्योम f2fs_alloc_nid_failed(काष्ठा f2fs_sb_info *sbi, nid_t nid)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा मुक्त_nid *i;
	bool need_मुक्त = false;

	अगर (!nid)
		वापस;

	spin_lock(&nm_i->nid_list_lock);
	i = __lookup_मुक्त_nid_list(nm_i, nid);
	f2fs_bug_on(sbi, !i);

	अगर (!f2fs_available_मुक्त_memory(sbi, FREE_NIDS)) अणु
		__हटाओ_मुक्त_nid(sbi, i, PREALLOC_NID);
		need_मुक्त = true;
	पूर्ण अन्यथा अणु
		__move_मुक्त_nid(sbi, i, PREALLOC_NID, FREE_NID);
	पूर्ण

	nm_i->available_nids++;

	update_मुक्त_nid_biपंचांगap(sbi, nid, true, false);

	spin_unlock(&nm_i->nid_list_lock);

	अगर (need_मुक्त)
		kmem_cache_मुक्त(मुक्त_nid_slab, i);
पूर्ण

पूर्णांक f2fs_try_to_मुक्त_nids(काष्ठा f2fs_sb_info *sbi, पूर्णांक nr_shrink)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	पूर्णांक nr = nr_shrink;

	अगर (nm_i->nid_cnt[FREE_NID] <= MAX_FREE_NIDS)
		वापस 0;

	अगर (!mutex_trylock(&nm_i->build_lock))
		वापस 0;

	जबतक (nr_shrink && nm_i->nid_cnt[FREE_NID] > MAX_FREE_NIDS) अणु
		काष्ठा मुक्त_nid *i, *next;
		अचिन्हित पूर्णांक batch = SHRINK_NID_BATCH_SIZE;

		spin_lock(&nm_i->nid_list_lock);
		list_क्रम_each_entry_safe(i, next, &nm_i->मुक्त_nid_list, list) अणु
			अगर (!nr_shrink || !batch ||
				nm_i->nid_cnt[FREE_NID] <= MAX_FREE_NIDS)
				अवरोध;
			__हटाओ_मुक्त_nid(sbi, i, FREE_NID);
			kmem_cache_मुक्त(मुक्त_nid_slab, i);
			nr_shrink--;
			batch--;
		पूर्ण
		spin_unlock(&nm_i->nid_list_lock);
	पूर्ण

	mutex_unlock(&nm_i->build_lock);

	वापस nr - nr_shrink;
पूर्ण

पूर्णांक f2fs_recover_अंतरभूत_xattr(काष्ठा inode *inode, काष्ठा page *page)
अणु
	व्योम *src_addr, *dst_addr;
	माप_प्रकार अंतरभूत_size;
	काष्ठा page *ipage;
	काष्ठा f2fs_inode *ri;

	ipage = f2fs_get_node_page(F2FS_I_SB(inode), inode->i_ino);
	अगर (IS_ERR(ipage))
		वापस PTR_ERR(ipage);

	ri = F2FS_INODE(page);
	अगर (ri->i_अंतरभूत & F2FS_INLINE_XATTR) अणु
		अगर (!f2fs_has_अंतरभूत_xattr(inode)) अणु
			set_inode_flag(inode, FI_INLINE_XATTR);
			stat_inc_अंतरभूत_xattr(inode);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (f2fs_has_अंतरभूत_xattr(inode)) अणु
			stat_dec_अंतरभूत_xattr(inode);
			clear_inode_flag(inode, FI_INLINE_XATTR);
		पूर्ण
		जाओ update_inode;
	पूर्ण

	dst_addr = अंतरभूत_xattr_addr(inode, ipage);
	src_addr = अंतरभूत_xattr_addr(inode, page);
	अंतरभूत_size = अंतरभूत_xattr_size(inode);

	f2fs_रुको_on_page_ग_लिखोback(ipage, NODE, true, true);
	स_नकल(dst_addr, src_addr, अंतरभूत_size);
update_inode:
	f2fs_update_inode(inode, ipage);
	f2fs_put_page(ipage, 1);
	वापस 0;
पूर्ण

पूर्णांक f2fs_recover_xattr_data(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t prev_xnid = F2FS_I(inode)->i_xattr_nid;
	nid_t new_xnid;
	काष्ठा dnode_of_data dn;
	काष्ठा node_info ni;
	काष्ठा page *xpage;
	पूर्णांक err;

	अगर (!prev_xnid)
		जाओ recover_xnid;

	/* 1: invalidate the previous xattr nid */
	err = f2fs_get_node_info(sbi, prev_xnid, &ni);
	अगर (err)
		वापस err;

	f2fs_invalidate_blocks(sbi, ni.blk_addr);
	dec_valid_node_count(sbi, inode, false);
	set_node_addr(sbi, &ni, शून्य_ADDR, false);

recover_xnid:
	/* 2: update xattr nid in inode */
	अगर (!f2fs_alloc_nid(sbi, &new_xnid))
		वापस -ENOSPC;

	set_new_dnode(&dn, inode, शून्य, शून्य, new_xnid);
	xpage = f2fs_new_node_page(&dn, XATTR_NODE_OFFSET);
	अगर (IS_ERR(xpage)) अणु
		f2fs_alloc_nid_failed(sbi, new_xnid);
		वापस PTR_ERR(xpage);
	पूर्ण

	f2fs_alloc_nid_करोne(sbi, new_xnid);
	f2fs_update_inode_page(inode);

	/* 3: update and set xattr node page dirty */
	स_नकल(F2FS_NODE(xpage), F2FS_NODE(page), VALID_XATTR_BLOCK_SIZE);

	set_page_dirty(xpage);
	f2fs_put_page(xpage, 1);

	वापस 0;
पूर्ण

पूर्णांक f2fs_recover_inode_page(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page)
अणु
	काष्ठा f2fs_inode *src, *dst;
	nid_t ino = ino_of_node(page);
	काष्ठा node_info old_ni, new_ni;
	काष्ठा page *ipage;
	पूर्णांक err;

	err = f2fs_get_node_info(sbi, ino, &old_ni);
	अगर (err)
		वापस err;

	अगर (unlikely(old_ni.blk_addr != शून्य_ADDR))
		वापस -EINVAL;
retry:
	ipage = f2fs_grab_cache_page(NODE_MAPPING(sbi), ino, false);
	अगर (!ipage) अणु
		congestion_रुको(BLK_RW_ASYNC, DEFAULT_IO_TIMEOUT);
		जाओ retry;
	पूर्ण

	/* Should not use this inode from मुक्त nid list */
	हटाओ_मुक्त_nid(sbi, ino);

	अगर (!PageUptodate(ipage))
		SetPageUptodate(ipage);
	fill_node_footer(ipage, ino, ino, 0, true);
	set_cold_node(ipage, false);

	src = F2FS_INODE(page);
	dst = F2FS_INODE(ipage);

	स_नकल(dst, src, दुरत्व(काष्ठा f2fs_inode, i_ext));
	dst->i_size = 0;
	dst->i_blocks = cpu_to_le64(1);
	dst->i_links = cpu_to_le32(1);
	dst->i_xattr_nid = 0;
	dst->i_अंतरभूत = src->i_अंतरभूत & (F2FS_INLINE_XATTR | F2FS_EXTRA_ATTR);
	अगर (dst->i_अंतरभूत & F2FS_EXTRA_ATTR) अणु
		dst->i_extra_isize = src->i_extra_isize;

		अगर (f2fs_sb_has_flexible_अंतरभूत_xattr(sbi) &&
			F2FS_FITS_IN_INODE(src, le16_to_cpu(src->i_extra_isize),
							i_अंतरभूत_xattr_size))
			dst->i_अंतरभूत_xattr_size = src->i_अंतरभूत_xattr_size;

		अगर (f2fs_sb_has_project_quota(sbi) &&
			F2FS_FITS_IN_INODE(src, le16_to_cpu(src->i_extra_isize),
								i_projid))
			dst->i_projid = src->i_projid;

		अगर (f2fs_sb_has_inode_crसमय(sbi) &&
			F2FS_FITS_IN_INODE(src, le16_to_cpu(src->i_extra_isize),
							i_crसमय_nsec)) अणु
			dst->i_crसमय = src->i_crसमय;
			dst->i_crसमय_nsec = src->i_crसमय_nsec;
		पूर्ण
	पूर्ण

	new_ni = old_ni;
	new_ni.ino = ino;

	अगर (unlikely(inc_valid_node_count(sbi, शून्य, true)))
		WARN_ON(1);
	set_node_addr(sbi, &new_ni, NEW_ADDR, false);
	inc_valid_inode_count(sbi);
	set_page_dirty(ipage);
	f2fs_put_page(ipage, 1);
	वापस 0;
पूर्ण

पूर्णांक f2fs_restore_node_summary(काष्ठा f2fs_sb_info *sbi,
			अचिन्हित पूर्णांक segno, काष्ठा f2fs_summary_block *sum)
अणु
	काष्ठा f2fs_node *rn;
	काष्ठा f2fs_summary *sum_entry;
	block_t addr;
	पूर्णांक i, idx, last_offset, nrpages;

	/* scan the node segment */
	last_offset = sbi->blocks_per_seg;
	addr = START_BLOCK(sbi, segno);
	sum_entry = &sum->entries[0];

	क्रम (i = 0; i < last_offset; i += nrpages, addr += nrpages) अणु
		nrpages = bio_max_segs(last_offset - i);

		/* पढ़ोahead node pages */
		f2fs_ra_meta_pages(sbi, addr, nrpages, META_POR, true);

		क्रम (idx = addr; idx < addr + nrpages; idx++) अणु
			काष्ठा page *page = f2fs_get_पंचांगp_page(sbi, idx);

			अगर (IS_ERR(page))
				वापस PTR_ERR(page);

			rn = F2FS_NODE(page);
			sum_entry->nid = rn->footer.nid;
			sum_entry->version = 0;
			sum_entry->ofs_in_node = 0;
			sum_entry++;
			f2fs_put_page(page, 1);
		पूर्ण

		invalidate_mapping_pages(META_MAPPING(sbi), addr,
							addr + nrpages);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम हटाओ_nats_in_journal(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, CURSEG_HOT_DATA);
	काष्ठा f2fs_journal *journal = curseg->journal;
	पूर्णांक i;

	करोwn_ग_लिखो(&curseg->journal_rwsem);
	क्रम (i = 0; i < nats_in_cursum(journal); i++) अणु
		काष्ठा nat_entry *ne;
		काष्ठा f2fs_nat_entry raw_ne;
		nid_t nid = le32_to_cpu(nid_in_journal(journal, i));

		अगर (f2fs_check_nid_range(sbi, nid))
			जारी;

		raw_ne = nat_in_journal(journal, i);

		ne = __lookup_nat_cache(nm_i, nid);
		अगर (!ne) अणु
			ne = __alloc_nat_entry(nid, true);
			__init_nat_entry(nm_i, ne, &raw_ne, true);
		पूर्ण

		/*
		 * अगर a मुक्त nat in journal has not been used after last
		 * checkpoपूर्णांक, we should हटाओ it from available nids,
		 * since later we will add it again.
		 */
		अगर (!get_nat_flag(ne, IS_सूचीTY) &&
				le32_to_cpu(raw_ne.block_addr) == शून्य_ADDR) अणु
			spin_lock(&nm_i->nid_list_lock);
			nm_i->available_nids--;
			spin_unlock(&nm_i->nid_list_lock);
		पूर्ण

		__set_nat_cache_dirty(nm_i, ne);
	पूर्ण
	update_nats_in_cursum(journal, -i);
	up_ग_लिखो(&curseg->journal_rwsem);
पूर्ण

अटल व्योम __adjust_nat_entry_set(काष्ठा nat_entry_set *nes,
						काष्ठा list_head *head, पूर्णांक max)
अणु
	काष्ठा nat_entry_set *cur;

	अगर (nes->entry_cnt >= max)
		जाओ add_out;

	list_क्रम_each_entry(cur, head, set_list) अणु
		अगर (cur->entry_cnt >= nes->entry_cnt) अणु
			list_add(&nes->set_list, cur->set_list.prev);
			वापस;
		पूर्ण
	पूर्ण
add_out:
	list_add_tail(&nes->set_list, head);
पूर्ण

अटल व्योम __update_nat_bits(काष्ठा f2fs_sb_info *sbi, nid_t start_nid,
						काष्ठा page *page)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	अचिन्हित पूर्णांक nat_index = start_nid / NAT_ENTRY_PER_BLOCK;
	काष्ठा f2fs_nat_block *nat_blk = page_address(page);
	पूर्णांक valid = 0;
	पूर्णांक i = 0;

	अगर (!enabled_nat_bits(sbi, शून्य))
		वापस;

	अगर (nat_index == 0) अणु
		valid = 1;
		i = 1;
	पूर्ण
	क्रम (; i < NAT_ENTRY_PER_BLOCK; i++) अणु
		अगर (le32_to_cpu(nat_blk->entries[i].block_addr) != शून्य_ADDR)
			valid++;
	पूर्ण
	अगर (valid == 0) अणु
		__set_bit_le(nat_index, nm_i->empty_nat_bits);
		__clear_bit_le(nat_index, nm_i->full_nat_bits);
		वापस;
	पूर्ण

	__clear_bit_le(nat_index, nm_i->empty_nat_bits);
	अगर (valid == NAT_ENTRY_PER_BLOCK)
		__set_bit_le(nat_index, nm_i->full_nat_bits);
	अन्यथा
		__clear_bit_le(nat_index, nm_i->full_nat_bits);
पूर्ण

अटल पूर्णांक __flush_nat_entry_set(काष्ठा f2fs_sb_info *sbi,
		काष्ठा nat_entry_set *set, काष्ठा cp_control *cpc)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, CURSEG_HOT_DATA);
	काष्ठा f2fs_journal *journal = curseg->journal;
	nid_t start_nid = set->set * NAT_ENTRY_PER_BLOCK;
	bool to_journal = true;
	काष्ठा f2fs_nat_block *nat_blk;
	काष्ठा nat_entry *ne, *cur;
	काष्ठा page *page = शून्य;

	/*
	 * there are two steps to flush nat entries:
	 * #1, flush nat entries to journal in current hot data summary block.
	 * #2, flush nat entries to nat page.
	 */
	अगर (enabled_nat_bits(sbi, cpc) ||
		!__has_cursum_space(journal, set->entry_cnt, NAT_JOURNAL))
		to_journal = false;

	अगर (to_journal) अणु
		करोwn_ग_लिखो(&curseg->journal_rwsem);
	पूर्ण अन्यथा अणु
		page = get_next_nat_page(sbi, start_nid);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		nat_blk = page_address(page);
		f2fs_bug_on(sbi, !nat_blk);
	पूर्ण

	/* flush dirty nats in nat entry set */
	list_क्रम_each_entry_safe(ne, cur, &set->entry_list, list) अणु
		काष्ठा f2fs_nat_entry *raw_ne;
		nid_t nid = nat_get_nid(ne);
		पूर्णांक offset;

		f2fs_bug_on(sbi, nat_get_blkaddr(ne) == NEW_ADDR);

		अगर (to_journal) अणु
			offset = f2fs_lookup_journal_in_cursum(journal,
							NAT_JOURNAL, nid, 1);
			f2fs_bug_on(sbi, offset < 0);
			raw_ne = &nat_in_journal(journal, offset);
			nid_in_journal(journal, offset) = cpu_to_le32(nid);
		पूर्ण अन्यथा अणु
			raw_ne = &nat_blk->entries[nid - start_nid];
		पूर्ण
		raw_nat_from_node_info(raw_ne, &ne->ni);
		nat_reset_flag(ne);
		__clear_nat_cache_dirty(NM_I(sbi), set, ne);
		अगर (nat_get_blkaddr(ne) == शून्य_ADDR) अणु
			add_मुक्त_nid(sbi, nid, false, true);
		पूर्ण अन्यथा अणु
			spin_lock(&NM_I(sbi)->nid_list_lock);
			update_मुक्त_nid_biपंचांगap(sbi, nid, false, false);
			spin_unlock(&NM_I(sbi)->nid_list_lock);
		पूर्ण
	पूर्ण

	अगर (to_journal) अणु
		up_ग_लिखो(&curseg->journal_rwsem);
	पूर्ण अन्यथा अणु
		__update_nat_bits(sbi, start_nid, page);
		f2fs_put_page(page, 1);
	पूर्ण

	/* Allow dirty nats by node block allocation in ग_लिखो_begin */
	अगर (!set->entry_cnt) अणु
		radix_tree_delete(&NM_I(sbi)->nat_set_root, set->set);
		kmem_cache_मुक्त(nat_entry_set_slab, set);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function is called during the checkpoपूर्णांकing process.
 */
पूर्णांक f2fs_flush_nat_entries(काष्ठा f2fs_sb_info *sbi, काष्ठा cp_control *cpc)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, CURSEG_HOT_DATA);
	काष्ठा f2fs_journal *journal = curseg->journal;
	काष्ठा nat_entry_set *setvec[SETVEC_SIZE];
	काष्ठा nat_entry_set *set, *पंचांगp;
	अचिन्हित पूर्णांक found;
	nid_t set_idx = 0;
	LIST_HEAD(sets);
	पूर्णांक err = 0;

	/*
	 * during unmount, let's flush nat_bits beक्रमe checking
	 * nat_cnt[सूचीTY_NAT].
	 */
	अगर (enabled_nat_bits(sbi, cpc)) अणु
		करोwn_ग_लिखो(&nm_i->nat_tree_lock);
		हटाओ_nats_in_journal(sbi);
		up_ग_लिखो(&nm_i->nat_tree_lock);
	पूर्ण

	अगर (!nm_i->nat_cnt[सूचीTY_NAT])
		वापस 0;

	करोwn_ग_लिखो(&nm_i->nat_tree_lock);

	/*
	 * अगर there are no enough space in journal to store dirty nat
	 * entries, हटाओ all entries from journal and merge them
	 * पूर्णांकo nat entry set.
	 */
	अगर (enabled_nat_bits(sbi, cpc) ||
		!__has_cursum_space(journal,
			nm_i->nat_cnt[सूचीTY_NAT], NAT_JOURNAL))
		हटाओ_nats_in_journal(sbi);

	जबतक ((found = __gang_lookup_nat_set(nm_i,
					set_idx, SETVEC_SIZE, setvec))) अणु
		अचिन्हित idx;

		set_idx = setvec[found - 1]->set + 1;
		क्रम (idx = 0; idx < found; idx++)
			__adjust_nat_entry_set(setvec[idx], &sets,
						MAX_NAT_JENTRIES(journal));
	पूर्ण

	/* flush dirty nats in nat entry set */
	list_क्रम_each_entry_safe(set, पंचांगp, &sets, set_list) अणु
		err = __flush_nat_entry_set(sbi, set, cpc);
		अगर (err)
			अवरोध;
	पूर्ण

	up_ग_लिखो(&nm_i->nat_tree_lock);
	/* Allow dirty nats by node block allocation in ग_लिखो_begin */

	वापस err;
पूर्ण

अटल पूर्णांक __get_nat_biपंचांगaps(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	अचिन्हित पूर्णांक nat_bits_bytes = nm_i->nat_blocks / BITS_PER_BYTE;
	अचिन्हित पूर्णांक i;
	__u64 cp_ver = cur_cp_version(ckpt);
	block_t nat_bits_addr;

	अगर (!enabled_nat_bits(sbi, शून्य))
		वापस 0;

	nm_i->nat_bits_blocks = F2FS_BLK_ALIGN((nat_bits_bytes << 1) + 8);
	nm_i->nat_bits = f2fs_kvzalloc(sbi,
			nm_i->nat_bits_blocks << F2FS_BLKSIZE_BITS, GFP_KERNEL);
	अगर (!nm_i->nat_bits)
		वापस -ENOMEM;

	nat_bits_addr = __start_cp_addr(sbi) + sbi->blocks_per_seg -
						nm_i->nat_bits_blocks;
	क्रम (i = 0; i < nm_i->nat_bits_blocks; i++) अणु
		काष्ठा page *page;

		page = f2fs_get_meta_page(sbi, nat_bits_addr++);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		स_नकल(nm_i->nat_bits + (i << F2FS_BLKSIZE_BITS),
					page_address(page), F2FS_BLKSIZE);
		f2fs_put_page(page, 1);
	पूर्ण

	cp_ver |= (cur_cp_crc(ckpt) << 32);
	अगर (cpu_to_le64(cp_ver) != *(__le64 *)nm_i->nat_bits) अणु
		disable_nat_bits(sbi, true);
		वापस 0;
	पूर्ण

	nm_i->full_nat_bits = nm_i->nat_bits + 8;
	nm_i->empty_nat_bits = nm_i->full_nat_bits + nat_bits_bytes;

	f2fs_notice(sbi, "Found nat_bits in checkpoint");
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम load_मुक्त_nid_biपंचांगap(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	अचिन्हित पूर्णांक i = 0;
	nid_t nid, last_nid;

	अगर (!enabled_nat_bits(sbi, शून्य))
		वापस;

	क्रम (i = 0; i < nm_i->nat_blocks; i++) अणु
		i = find_next_bit_le(nm_i->empty_nat_bits, nm_i->nat_blocks, i);
		अगर (i >= nm_i->nat_blocks)
			अवरोध;

		__set_bit_le(i, nm_i->nat_block_biपंचांगap);

		nid = i * NAT_ENTRY_PER_BLOCK;
		last_nid = nid + NAT_ENTRY_PER_BLOCK;

		spin_lock(&NM_I(sbi)->nid_list_lock);
		क्रम (; nid < last_nid; nid++)
			update_मुक्त_nid_biपंचांगap(sbi, nid, true, true);
		spin_unlock(&NM_I(sbi)->nid_list_lock);
	पूर्ण

	क्रम (i = 0; i < nm_i->nat_blocks; i++) अणु
		i = find_next_bit_le(nm_i->full_nat_bits, nm_i->nat_blocks, i);
		अगर (i >= nm_i->nat_blocks)
			अवरोध;

		__set_bit_le(i, nm_i->nat_block_biपंचांगap);
	पूर्ण
पूर्ण

अटल पूर्णांक init_node_manager(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_super_block *sb_raw = F2FS_RAW_SUPER(sbi);
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	अचिन्हित अक्षर *version_biपंचांगap;
	अचिन्हित पूर्णांक nat_segs;
	पूर्णांक err;

	nm_i->nat_blkaddr = le32_to_cpu(sb_raw->nat_blkaddr);

	/* segment_count_nat includes pair segment so भागide to 2. */
	nat_segs = le32_to_cpu(sb_raw->segment_count_nat) >> 1;
	nm_i->nat_blocks = nat_segs << le32_to_cpu(sb_raw->log_blocks_per_seg);
	nm_i->max_nid = NAT_ENTRY_PER_BLOCK * nm_i->nat_blocks;

	/* not used nids: 0, node, meta, (and root counted as valid node) */
	nm_i->available_nids = nm_i->max_nid - sbi->total_valid_node_count -
						F2FS_RESERVED_NODE_NUM;
	nm_i->nid_cnt[FREE_NID] = 0;
	nm_i->nid_cnt[PREALLOC_NID] = 0;
	nm_i->ram_thresh = DEF_RAM_THRESHOLD;
	nm_i->ra_nid_pages = DEF_RA_NID_PAGES;
	nm_i->dirty_nats_ratio = DEF_सूचीTY_NAT_RATIO_THRESHOLD;

	INIT_RADIX_TREE(&nm_i->मुक्त_nid_root, GFP_ATOMIC);
	INIT_LIST_HEAD(&nm_i->मुक्त_nid_list);
	INIT_RADIX_TREE(&nm_i->nat_root, GFP_NOIO);
	INIT_RADIX_TREE(&nm_i->nat_set_root, GFP_NOIO);
	INIT_LIST_HEAD(&nm_i->nat_entries);
	spin_lock_init(&nm_i->nat_list_lock);

	mutex_init(&nm_i->build_lock);
	spin_lock_init(&nm_i->nid_list_lock);
	init_rwsem(&nm_i->nat_tree_lock);

	nm_i->next_scan_nid = le32_to_cpu(sbi->ckpt->next_मुक्त_nid);
	nm_i->biपंचांगap_size = __biपंचांगap_size(sbi, NAT_BITMAP);
	version_biपंचांगap = __biपंचांगap_ptr(sbi, NAT_BITMAP);
	nm_i->nat_biपंचांगap = kmemdup(version_biपंचांगap, nm_i->biपंचांगap_size,
					GFP_KERNEL);
	अगर (!nm_i->nat_biपंचांगap)
		वापस -ENOMEM;

	err = __get_nat_biपंचांगaps(sbi);
	अगर (err)
		वापस err;

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	nm_i->nat_biपंचांगap_mir = kmemdup(version_biपंचांगap, nm_i->biपंचांगap_size,
					GFP_KERNEL);
	अगर (!nm_i->nat_biपंचांगap_mir)
		वापस -ENOMEM;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक init_मुक्त_nid_cache(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	पूर्णांक i;

	nm_i->मुक्त_nid_biपंचांगap =
		f2fs_kvzalloc(sbi, array_size(माप(अचिन्हित अक्षर *),
					      nm_i->nat_blocks),
			      GFP_KERNEL);
	अगर (!nm_i->मुक्त_nid_biपंचांगap)
		वापस -ENOMEM;

	क्रम (i = 0; i < nm_i->nat_blocks; i++) अणु
		nm_i->मुक्त_nid_biपंचांगap[i] = f2fs_kvzalloc(sbi,
			f2fs_biपंचांगap_size(NAT_ENTRY_PER_BLOCK), GFP_KERNEL);
		अगर (!nm_i->मुक्त_nid_biपंचांगap[i])
			वापस -ENOMEM;
	पूर्ण

	nm_i->nat_block_biपंचांगap = f2fs_kvzalloc(sbi, nm_i->nat_blocks / 8,
								GFP_KERNEL);
	अगर (!nm_i->nat_block_biपंचांगap)
		वापस -ENOMEM;

	nm_i->मुक्त_nid_count =
		f2fs_kvzalloc(sbi, array_size(माप(अचिन्हित लघु),
					      nm_i->nat_blocks),
			      GFP_KERNEL);
	अगर (!nm_i->मुक्त_nid_count)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

पूर्णांक f2fs_build_node_manager(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक err;

	sbi->nm_info = f2fs_kzalloc(sbi, माप(काष्ठा f2fs_nm_info),
							GFP_KERNEL);
	अगर (!sbi->nm_info)
		वापस -ENOMEM;

	err = init_node_manager(sbi);
	अगर (err)
		वापस err;

	err = init_मुक्त_nid_cache(sbi);
	अगर (err)
		वापस err;

	/* load मुक्त nid status from nat_bits table */
	load_मुक्त_nid_biपंचांगap(sbi);

	वापस f2fs_build_मुक्त_nids(sbi, true, true);
पूर्ण

व्योम f2fs_destroy_node_manager(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा मुक्त_nid *i, *next_i;
	काष्ठा nat_entry *natvec[NATVEC_SIZE];
	काष्ठा nat_entry_set *setvec[SETVEC_SIZE];
	nid_t nid = 0;
	अचिन्हित पूर्णांक found;

	अगर (!nm_i)
		वापस;

	/* destroy मुक्त nid list */
	spin_lock(&nm_i->nid_list_lock);
	list_क्रम_each_entry_safe(i, next_i, &nm_i->मुक्त_nid_list, list) अणु
		__हटाओ_मुक्त_nid(sbi, i, FREE_NID);
		spin_unlock(&nm_i->nid_list_lock);
		kmem_cache_मुक्त(मुक्त_nid_slab, i);
		spin_lock(&nm_i->nid_list_lock);
	पूर्ण
	f2fs_bug_on(sbi, nm_i->nid_cnt[FREE_NID]);
	f2fs_bug_on(sbi, nm_i->nid_cnt[PREALLOC_NID]);
	f2fs_bug_on(sbi, !list_empty(&nm_i->मुक्त_nid_list));
	spin_unlock(&nm_i->nid_list_lock);

	/* destroy nat cache */
	करोwn_ग_लिखो(&nm_i->nat_tree_lock);
	जबतक ((found = __gang_lookup_nat_cache(nm_i,
					nid, NATVEC_SIZE, natvec))) अणु
		अचिन्हित idx;

		nid = nat_get_nid(natvec[found - 1]) + 1;
		क्रम (idx = 0; idx < found; idx++) अणु
			spin_lock(&nm_i->nat_list_lock);
			list_del(&natvec[idx]->list);
			spin_unlock(&nm_i->nat_list_lock);

			__del_from_nat_cache(nm_i, natvec[idx]);
		पूर्ण
	पूर्ण
	f2fs_bug_on(sbi, nm_i->nat_cnt[TOTAL_NAT]);

	/* destroy nat set cache */
	nid = 0;
	जबतक ((found = __gang_lookup_nat_set(nm_i,
					nid, SETVEC_SIZE, setvec))) अणु
		अचिन्हित idx;

		nid = setvec[found - 1]->set + 1;
		क्रम (idx = 0; idx < found; idx++) अणु
			/* entry_cnt is not zero, when cp_error was occurred */
			f2fs_bug_on(sbi, !list_empty(&setvec[idx]->entry_list));
			radix_tree_delete(&nm_i->nat_set_root, setvec[idx]->set);
			kmem_cache_मुक्त(nat_entry_set_slab, setvec[idx]);
		पूर्ण
	पूर्ण
	up_ग_लिखो(&nm_i->nat_tree_lock);

	kvमुक्त(nm_i->nat_block_biपंचांगap);
	अगर (nm_i->मुक्त_nid_biपंचांगap) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nm_i->nat_blocks; i++)
			kvमुक्त(nm_i->मुक्त_nid_biपंचांगap[i]);
		kvमुक्त(nm_i->मुक्त_nid_biपंचांगap);
	पूर्ण
	kvमुक्त(nm_i->मुक्त_nid_count);

	kvमुक्त(nm_i->nat_biपंचांगap);
	kvमुक्त(nm_i->nat_bits);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	kvमुक्त(nm_i->nat_biपंचांगap_mir);
#पूर्ण_अगर
	sbi->nm_info = शून्य;
	kमुक्त(nm_i);
पूर्ण

पूर्णांक __init f2fs_create_node_manager_caches(व्योम)
अणु
	nat_entry_slab = f2fs_kmem_cache_create("f2fs_nat_entry",
			माप(काष्ठा nat_entry));
	अगर (!nat_entry_slab)
		जाओ fail;

	मुक्त_nid_slab = f2fs_kmem_cache_create("f2fs_free_nid",
			माप(काष्ठा मुक्त_nid));
	अगर (!मुक्त_nid_slab)
		जाओ destroy_nat_entry;

	nat_entry_set_slab = f2fs_kmem_cache_create("f2fs_nat_entry_set",
			माप(काष्ठा nat_entry_set));
	अगर (!nat_entry_set_slab)
		जाओ destroy_मुक्त_nid;

	fsync_node_entry_slab = f2fs_kmem_cache_create("f2fs_fsync_node_entry",
			माप(काष्ठा fsync_node_entry));
	अगर (!fsync_node_entry_slab)
		जाओ destroy_nat_entry_set;
	वापस 0;

destroy_nat_entry_set:
	kmem_cache_destroy(nat_entry_set_slab);
destroy_मुक्त_nid:
	kmem_cache_destroy(मुक्त_nid_slab);
destroy_nat_entry:
	kmem_cache_destroy(nat_entry_slab);
fail:
	वापस -ENOMEM;
पूर्ण

व्योम f2fs_destroy_node_manager_caches(व्योम)
अणु
	kmem_cache_destroy(fsync_node_entry_slab);
	kmem_cache_destroy(nat_entry_set_slab);
	kmem_cache_destroy(मुक्त_nid_slab);
	kmem_cache_destroy(nat_entry_slab);
पूर्ण
