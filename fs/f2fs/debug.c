<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * f2fs debugging statistics
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 * Copyright (c) 2012 Linux Foundation
 * Copyright (c) 2012 Greg Kroah-Harपंचांगan <gregkh@linuxfoundation.org>
 */

#समावेश <linux/fs.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"
#समावेश "gc.h"

अटल LIST_HEAD(f2fs_stat_list);
अटल DEFINE_MUTEX(f2fs_stat_mutex);
#अगर_घोषित CONFIG_DEBUG_FS
अटल काष्ठा dentry *f2fs_debugfs_root;
#पूर्ण_अगर

/*
 * This function calculates BDF of every segments
 */
व्योम f2fs_update_sit_info(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);
	अचिन्हित दीर्घ दीर्घ blks_per_sec, hblks_per_sec, total_vblocks;
	अचिन्हित दीर्घ दीर्घ bimodal, dist;
	अचिन्हित पूर्णांक segno, vblocks;
	पूर्णांक ndirty = 0;

	bimodal = 0;
	total_vblocks = 0;
	blks_per_sec = BLKS_PER_SEC(sbi);
	hblks_per_sec = blks_per_sec / 2;
	क्रम (segno = 0; segno < MAIN_SEGS(sbi); segno += sbi->segs_per_sec) अणु
		vblocks = get_valid_blocks(sbi, segno, true);
		dist = असल(vblocks - hblks_per_sec);
		bimodal += dist * dist;

		अगर (vblocks > 0 && vblocks < blks_per_sec) अणु
			total_vblocks += vblocks;
			ndirty++;
		पूर्ण
	पूर्ण
	dist = भाग_u64(MAIN_SECS(sbi) * hblks_per_sec * hblks_per_sec, 100);
	si->bimodal = भाग64_u64(bimodal, dist);
	अगर (si->dirty_count)
		si->avg_vblocks = भाग_u64(total_vblocks, ndirty);
	अन्यथा
		si->avg_vblocks = 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम update_general_status(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);
	काष्ठा f2fs_super_block *raw_super = F2FS_RAW_SUPER(sbi);
	पूर्णांक i;

	/* these will be changed अगर online resize is करोne */
	si->मुख्य_area_segs = le32_to_cpu(raw_super->segment_count_मुख्य);
	si->मुख्य_area_sections = le32_to_cpu(raw_super->section_count);
	si->मुख्य_area_zones = si->मुख्य_area_sections /
				le32_to_cpu(raw_super->secs_per_zone);

	/* validation check of the segment numbers */
	si->hit_largest = atomic64_पढ़ो(&sbi->पढ़ो_hit_largest);
	si->hit_cached = atomic64_पढ़ो(&sbi->पढ़ो_hit_cached);
	si->hit_rbtree = atomic64_पढ़ो(&sbi->पढ़ो_hit_rbtree);
	si->hit_total = si->hit_largest + si->hit_cached + si->hit_rbtree;
	si->total_ext = atomic64_पढ़ो(&sbi->total_hit_ext);
	si->ext_tree = atomic_पढ़ो(&sbi->total_ext_tree);
	si->zombie_tree = atomic_पढ़ो(&sbi->total_zombie_tree);
	si->ext_node = atomic_पढ़ो(&sbi->total_ext_node);
	si->ndirty_node = get_pages(sbi, F2FS_सूचीTY_NODES);
	si->ndirty_dent = get_pages(sbi, F2FS_सूचीTY_DENTS);
	si->ndirty_meta = get_pages(sbi, F2FS_सूचीTY_META);
	si->ndirty_data = get_pages(sbi, F2FS_सूचीTY_DATA);
	si->ndirty_qdata = get_pages(sbi, F2FS_सूचीTY_QDATA);
	si->ndirty_imeta = get_pages(sbi, F2FS_सूचीTY_IMETA);
	si->ndirty_dirs = sbi->ndirty_inode[सूची_INODE];
	si->ndirty_files = sbi->ndirty_inode[खाता_INODE];
	si->nquota_files = sbi->nquota_files;
	si->ndirty_all = sbi->ndirty_inode[सूचीTY_META];
	si->inmem_pages = get_pages(sbi, F2FS_INMEM_PAGES);
	si->aw_cnt = sbi->atomic_files;
	si->vw_cnt = atomic_पढ़ो(&sbi->vw_cnt);
	si->max_aw_cnt = atomic_पढ़ो(&sbi->max_aw_cnt);
	si->max_vw_cnt = atomic_पढ़ो(&sbi->max_vw_cnt);
	si->nr_dio_पढ़ो = get_pages(sbi, F2FS_DIO_READ);
	si->nr_dio_ग_लिखो = get_pages(sbi, F2FS_DIO_WRITE);
	si->nr_wb_cp_data = get_pages(sbi, F2FS_WB_CP_DATA);
	si->nr_wb_data = get_pages(sbi, F2FS_WB_DATA);
	si->nr_rd_data = get_pages(sbi, F2FS_RD_DATA);
	si->nr_rd_node = get_pages(sbi, F2FS_RD_NODE);
	si->nr_rd_meta = get_pages(sbi, F2FS_RD_META);
	अगर (SM_I(sbi)->fcc_info) अणु
		si->nr_flushed =
			atomic_पढ़ो(&SM_I(sbi)->fcc_info->issued_flush);
		si->nr_flushing =
			atomic_पढ़ो(&SM_I(sbi)->fcc_info->queued_flush);
		si->flush_list_empty =
			llist_empty(&SM_I(sbi)->fcc_info->issue_list);
	पूर्ण
	अगर (SM_I(sbi)->dcc_info) अणु
		si->nr_discarded =
			atomic_पढ़ो(&SM_I(sbi)->dcc_info->issued_discard);
		si->nr_discarding =
			atomic_पढ़ो(&SM_I(sbi)->dcc_info->queued_discard);
		si->nr_discard_cmd =
			atomic_पढ़ो(&SM_I(sbi)->dcc_info->discard_cmd_cnt);
		si->undiscard_blks = SM_I(sbi)->dcc_info->undiscard_blks;
	पूर्ण
	si->nr_issued_ckpt = atomic_पढ़ो(&sbi->cprc_info.issued_ckpt);
	si->nr_total_ckpt = atomic_पढ़ो(&sbi->cprc_info.total_ckpt);
	si->nr_queued_ckpt = atomic_पढ़ो(&sbi->cprc_info.queued_ckpt);
	spin_lock(&sbi->cprc_info.stat_lock);
	si->cur_ckpt_समय = sbi->cprc_info.cur_समय;
	si->peak_ckpt_समय = sbi->cprc_info.peak_समय;
	spin_unlock(&sbi->cprc_info.stat_lock);
	si->total_count = (पूर्णांक)sbi->user_block_count / sbi->blocks_per_seg;
	si->rsvd_segs = reserved_segments(sbi);
	si->overp_segs = overprovision_segments(sbi);
	si->valid_count = valid_user_blocks(sbi);
	si->discard_blks = discard_blocks(sbi);
	si->valid_node_count = valid_node_count(sbi);
	si->valid_inode_count = valid_inode_count(sbi);
	si->अंतरभूत_xattr = atomic_पढ़ो(&sbi->अंतरभूत_xattr);
	si->अंतरभूत_inode = atomic_पढ़ो(&sbi->अंतरभूत_inode);
	si->अंतरभूत_dir = atomic_पढ़ो(&sbi->अंतरभूत_dir);
	si->compr_inode = atomic_पढ़ो(&sbi->compr_inode);
	si->compr_blocks = atomic64_पढ़ो(&sbi->compr_blocks);
	si->append = sbi->im[APPEND_INO].ino_num;
	si->update = sbi->im[UPDATE_INO].ino_num;
	si->orphans = sbi->im[ORPHAN_INO].ino_num;
	si->utilization = utilization(sbi);

	si->मुक्त_segs = मुक्त_segments(sbi);
	si->मुक्त_secs = मुक्त_sections(sbi);
	si->preमुक्त_count = preमुक्त_segments(sbi);
	si->dirty_count = dirty_segments(sbi);
	अगर (sbi->node_inode)
		si->node_pages = NODE_MAPPING(sbi)->nrpages;
	अगर (sbi->meta_inode)
		si->meta_pages = META_MAPPING(sbi)->nrpages;
	si->nats = NM_I(sbi)->nat_cnt[TOTAL_NAT];
	si->dirty_nats = NM_I(sbi)->nat_cnt[सूचीTY_NAT];
	si->sits = MAIN_SEGS(sbi);
	si->dirty_sits = SIT_I(sbi)->dirty_sentries;
	si->मुक्त_nids = NM_I(sbi)->nid_cnt[FREE_NID];
	si->avail_nids = NM_I(sbi)->available_nids;
	si->alloc_nids = NM_I(sbi)->nid_cnt[PREALLOC_NID];
	si->io_skip_bggc = sbi->io_skip_bggc;
	si->other_skip_bggc = sbi->other_skip_bggc;
	si->skipped_atomic_files[BG_GC] = sbi->skipped_atomic_files[BG_GC];
	si->skipped_atomic_files[FG_GC] = sbi->skipped_atomic_files[FG_GC];
	si->util_मुक्त = (पूर्णांक)(मुक्त_user_blocks(sbi) >> sbi->log_blocks_per_seg)
		* 100 / (पूर्णांक)(sbi->user_block_count >> sbi->log_blocks_per_seg)
		/ 2;
	si->util_valid = (पूर्णांक)(written_block_count(sbi) >>
						sbi->log_blocks_per_seg)
		* 100 / (पूर्णांक)(sbi->user_block_count >> sbi->log_blocks_per_seg)
		/ 2;
	si->util_invalid = 50 - si->util_मुक्त - si->util_valid;
	क्रम (i = CURSEG_HOT_DATA; i < NO_CHECK_TYPE; i++) अणु
		काष्ठा curseg_info *curseg = CURSEG_I(sbi, i);

		si->curseg[i] = curseg->segno;
		si->cursec[i] = GET_SEC_FROM_SEG(sbi, curseg->segno);
		si->curzone[i] = GET_ZONE_FROM_SEC(sbi, si->cursec[i]);
	पूर्ण

	क्रम (i = META_CP; i < META_MAX; i++)
		si->meta_count[i] = atomic_पढ़ो(&sbi->meta_count[i]);

	क्रम (i = 0; i < NO_CHECK_TYPE; i++) अणु
		si->dirty_seg[i] = 0;
		si->full_seg[i] = 0;
		si->valid_blks[i] = 0;
	पूर्ण

	क्रम (i = 0; i < MAIN_SEGS(sbi); i++) अणु
		पूर्णांक blks = get_seg_entry(sbi, i)->valid_blocks;
		पूर्णांक type = get_seg_entry(sbi, i)->type;

		अगर (!blks)
			जारी;

		अगर (blks == sbi->blocks_per_seg)
			si->full_seg[type]++;
		अन्यथा
			si->dirty_seg[type]++;
		si->valid_blks[type] += blks;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		si->segment_count[i] = sbi->segment_count[i];
		si->block_count[i] = sbi->block_count[i];
	पूर्ण

	si->inplace_count = atomic_पढ़ो(&sbi->inplace_count);
पूर्ण

/*
 * This function calculates memory footprपूर्णांक.
 */
अटल व्योम update_mem_info(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);
	पूर्णांक i;

	अगर (si->base_mem)
		जाओ get_cache;

	/* build stat */
	si->base_mem = माप(काष्ठा f2fs_stat_info);

	/* build superblock */
	si->base_mem += माप(काष्ठा f2fs_sb_info) + sbi->sb->s_blocksize;
	si->base_mem += 2 * माप(काष्ठा f2fs_inode_info);
	si->base_mem += माप(*sbi->ckpt);

	/* build sm */
	si->base_mem += माप(काष्ठा f2fs_sm_info);

	/* build sit */
	si->base_mem += माप(काष्ठा sit_info);
	si->base_mem += MAIN_SEGS(sbi) * माप(काष्ठा seg_entry);
	si->base_mem += f2fs_biपंचांगap_size(MAIN_SEGS(sbi));
	si->base_mem += 2 * SIT_VBLOCK_MAP_SIZE * MAIN_SEGS(sbi);
	si->base_mem += SIT_VBLOCK_MAP_SIZE * MAIN_SEGS(sbi);
	si->base_mem += SIT_VBLOCK_MAP_SIZE;
	अगर (__is_large_section(sbi))
		si->base_mem += MAIN_SECS(sbi) * माप(काष्ठा sec_entry);
	si->base_mem += __biपंचांगap_size(sbi, SIT_BITMAP);

	/* build मुक्त segmap */
	si->base_mem += माप(काष्ठा मुक्त_segmap_info);
	si->base_mem += f2fs_biपंचांगap_size(MAIN_SEGS(sbi));
	si->base_mem += f2fs_biपंचांगap_size(MAIN_SECS(sbi));

	/* build curseg */
	si->base_mem += माप(काष्ठा curseg_info) * NR_CURSEG_TYPE;
	si->base_mem += PAGE_SIZE * NR_CURSEG_TYPE;

	/* build dirty segmap */
	si->base_mem += माप(काष्ठा dirty_seglist_info);
	si->base_mem += NR_सूचीTY_TYPE * f2fs_biपंचांगap_size(MAIN_SEGS(sbi));
	si->base_mem += f2fs_biपंचांगap_size(MAIN_SECS(sbi));

	/* build nm */
	si->base_mem += माप(काष्ठा f2fs_nm_info);
	si->base_mem += __biपंचांगap_size(sbi, NAT_BITMAP);
	si->base_mem += (NM_I(sbi)->nat_bits_blocks << F2FS_BLKSIZE_BITS);
	si->base_mem += NM_I(sbi)->nat_blocks *
				f2fs_biपंचांगap_size(NAT_ENTRY_PER_BLOCK);
	si->base_mem += NM_I(sbi)->nat_blocks / 8;
	si->base_mem += NM_I(sbi)->nat_blocks * माप(अचिन्हित लघु);

get_cache:
	si->cache_mem = 0;

	/* build gc */
	अगर (sbi->gc_thपढ़ो)
		si->cache_mem += माप(काष्ठा f2fs_gc_kthपढ़ो);

	/* build merge flush thपढ़ो */
	अगर (SM_I(sbi)->fcc_info)
		si->cache_mem += माप(काष्ठा flush_cmd_control);
	अगर (SM_I(sbi)->dcc_info) अणु
		si->cache_mem += माप(काष्ठा discard_cmd_control);
		si->cache_mem += माप(काष्ठा discard_cmd) *
			atomic_पढ़ो(&SM_I(sbi)->dcc_info->discard_cmd_cnt);
	पूर्ण

	/* मुक्त nids */
	si->cache_mem += (NM_I(sbi)->nid_cnt[FREE_NID] +
				NM_I(sbi)->nid_cnt[PREALLOC_NID]) *
				माप(काष्ठा मुक्त_nid);
	si->cache_mem += NM_I(sbi)->nat_cnt[TOTAL_NAT] *
				माप(काष्ठा nat_entry);
	si->cache_mem += NM_I(sbi)->nat_cnt[सूचीTY_NAT] *
				माप(काष्ठा nat_entry_set);
	si->cache_mem += si->inmem_pages * माप(काष्ठा inmem_pages);
	क्रम (i = 0; i < MAX_INO_ENTRY; i++)
		si->cache_mem += sbi->im[i].ino_num * माप(काष्ठा ino_entry);
	si->cache_mem += atomic_पढ़ो(&sbi->total_ext_tree) *
						माप(काष्ठा extent_tree);
	si->cache_mem += atomic_पढ़ो(&sbi->total_ext_node) *
						माप(काष्ठा extent_node);

	si->page_mem = 0;
	अगर (sbi->node_inode) अणु
		अचिन्हित npages = NODE_MAPPING(sbi)->nrpages;

		si->page_mem += (अचिन्हित दीर्घ दीर्घ)npages << PAGE_SHIFT;
	पूर्ण
	अगर (sbi->meta_inode) अणु
		अचिन्हित npages = META_MAPPING(sbi)->nrpages;

		si->page_mem += (अचिन्हित दीर्घ दीर्घ)npages << PAGE_SHIFT;
	पूर्ण
पूर्ण

अटल पूर्णांक stat_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा f2fs_stat_info *si;
	पूर्णांक i = 0;
	पूर्णांक j;

	mutex_lock(&f2fs_stat_mutex);
	list_क्रम_each_entry(si, &f2fs_stat_list, stat_list) अणु
		update_general_status(si->sbi);

		seq_म_लिखो(s, "\n=====[ partition info(%pg). #%d, %s, CP: %s]=====\n",
			si->sbi->sb->s_bdev, i++,
			f2fs_पढ़ोonly(si->sbi->sb) ? "RO": "RW",
			is_set_ckpt_flags(si->sbi, CP_DISABLED_FLAG) ?
			"Disabled": (f2fs_cp_error(si->sbi) ? "Error": "Good"));
		seq_म_लिखो(s, "[SB: 1] [CP: 2] [SIT: %d] [NAT: %d] ",
			   si->sit_area_segs, si->nat_area_segs);
		seq_म_लिखो(s, "[SSA: %d] [MAIN: %d",
			   si->ssa_area_segs, si->मुख्य_area_segs);
		seq_म_लिखो(s, "(OverProv:%d Resv:%d)]\n\n",
			   si->overp_segs, si->rsvd_segs);
		seq_म_लिखो(s, "Current Time Sec: %llu / Mounted Time Sec: %llu\n\n",
					kसमय_get_bootसमय_seconds(),
					SIT_I(si->sbi)->mounted_समय);
		अगर (test_opt(si->sbi, DISCARD))
			seq_म_लिखो(s, "Utilization: %u%% (%u valid blocks, %u discard blocks)\n",
				si->utilization, si->valid_count, si->discard_blks);
		अन्यथा
			seq_म_लिखो(s, "Utilization: %u%% (%u valid blocks)\n",
				si->utilization, si->valid_count);

		seq_म_लिखो(s, "  - Node: %u (Inode: %u, ",
			   si->valid_node_count, si->valid_inode_count);
		seq_म_लिखो(s, "Other: %u)\n  - Data: %u\n",
			   si->valid_node_count - si->valid_inode_count,
			   si->valid_count - si->valid_node_count);
		seq_म_लिखो(s, "  - Inline_xattr Inode: %u\n",
			   si->अंतरभूत_xattr);
		seq_म_लिखो(s, "  - Inline_data Inode: %u\n",
			   si->अंतरभूत_inode);
		seq_म_लिखो(s, "  - Inline_dentry Inode: %u\n",
			   si->अंतरभूत_dir);
		seq_म_लिखो(s, "  - Compressed Inode: %u, Blocks: %llu\n",
			   si->compr_inode, si->compr_blocks);
		seq_म_लिखो(s, "  - Orphan/Append/Update Inode: %u, %u, %u\n",
			   si->orphans, si->append, si->update);
		seq_म_लिखो(s, "\nMain area: %d segs, %d secs %d zones\n",
			   si->मुख्य_area_segs, si->मुख्य_area_sections,
			   si->मुख्य_area_zones);
		seq_म_लिखो(s, "    TYPE         %8s %8s %8s %10s %10s %10s\n",
			   "segno", "secno", "zoneno", "dirty_seg", "full_seg", "valid_blk");
		seq_म_लिखो(s, "  - COLD   data: %8d %8d %8d %10u %10u %10u\n",
			   si->curseg[CURSEG_COLD_DATA],
			   si->cursec[CURSEG_COLD_DATA],
			   si->curzone[CURSEG_COLD_DATA],
			   si->dirty_seg[CURSEG_COLD_DATA],
			   si->full_seg[CURSEG_COLD_DATA],
			   si->valid_blks[CURSEG_COLD_DATA]);
		seq_म_लिखो(s, "  - WARM   data: %8d %8d %8d %10u %10u %10u\n",
			   si->curseg[CURSEG_WARM_DATA],
			   si->cursec[CURSEG_WARM_DATA],
			   si->curzone[CURSEG_WARM_DATA],
			   si->dirty_seg[CURSEG_WARM_DATA],
			   si->full_seg[CURSEG_WARM_DATA],
			   si->valid_blks[CURSEG_WARM_DATA]);
		seq_म_लिखो(s, "  - HOT    data: %8d %8d %8d %10u %10u %10u\n",
			   si->curseg[CURSEG_HOT_DATA],
			   si->cursec[CURSEG_HOT_DATA],
			   si->curzone[CURSEG_HOT_DATA],
			   si->dirty_seg[CURSEG_HOT_DATA],
			   si->full_seg[CURSEG_HOT_DATA],
			   si->valid_blks[CURSEG_HOT_DATA]);
		seq_म_लिखो(s, "  - Dir   dnode: %8d %8d %8d %10u %10u %10u\n",
			   si->curseg[CURSEG_HOT_NODE],
			   si->cursec[CURSEG_HOT_NODE],
			   si->curzone[CURSEG_HOT_NODE],
			   si->dirty_seg[CURSEG_HOT_NODE],
			   si->full_seg[CURSEG_HOT_NODE],
			   si->valid_blks[CURSEG_HOT_NODE]);
		seq_म_लिखो(s, "  - File  dnode: %8d %8d %8d %10u %10u %10u\n",
			   si->curseg[CURSEG_WARM_NODE],
			   si->cursec[CURSEG_WARM_NODE],
			   si->curzone[CURSEG_WARM_NODE],
			   si->dirty_seg[CURSEG_WARM_NODE],
			   si->full_seg[CURSEG_WARM_NODE],
			   si->valid_blks[CURSEG_WARM_NODE]);
		seq_म_लिखो(s, "  - Indir nodes: %8d %8d %8d %10u %10u %10u\n",
			   si->curseg[CURSEG_COLD_NODE],
			   si->cursec[CURSEG_COLD_NODE],
			   si->curzone[CURSEG_COLD_NODE],
			   si->dirty_seg[CURSEG_COLD_NODE],
			   si->full_seg[CURSEG_COLD_NODE],
			   si->valid_blks[CURSEG_COLD_NODE]);
		seq_म_लिखो(s, "  - Pinned file: %8d %8d %8d\n",
			   si->curseg[CURSEG_COLD_DATA_PINNED],
			   si->cursec[CURSEG_COLD_DATA_PINNED],
			   si->curzone[CURSEG_COLD_DATA_PINNED]);
		seq_म_लिखो(s, "  - ATGC   data: %8d %8d %8d\n",
			   si->curseg[CURSEG_ALL_DATA_ATGC],
			   si->cursec[CURSEG_ALL_DATA_ATGC],
			   si->curzone[CURSEG_ALL_DATA_ATGC]);
		seq_म_लिखो(s, "\n  - Valid: %d\n  - Dirty: %d\n",
			   si->मुख्य_area_segs - si->dirty_count -
			   si->preमुक्त_count - si->मुक्त_segs,
			   si->dirty_count);
		seq_म_लिखो(s, "  - Prefree: %d\n  - Free: %d (%d)\n\n",
			   si->preमुक्त_count, si->मुक्त_segs, si->मुक्त_secs);
		seq_म_लिखो(s, "CP calls: %d (BG: %d)\n",
				si->cp_count, si->bg_cp_count);
		seq_म_लिखो(s, "  - cp blocks : %u\n", si->meta_count[META_CP]);
		seq_म_लिखो(s, "  - sit blocks : %u\n",
				si->meta_count[META_SIT]);
		seq_म_लिखो(s, "  - nat blocks : %u\n",
				si->meta_count[META_NAT]);
		seq_म_लिखो(s, "  - ssa blocks : %u\n",
				si->meta_count[META_SSA]);
		seq_म_लिखो(s, "CP merge (Queued: %4d, Issued: %4d, Total: %4d, "
				"Cur time: %4d(ms), Peak time: %4d(ms))\n",
				si->nr_queued_ckpt, si->nr_issued_ckpt,
				si->nr_total_ckpt, si->cur_ckpt_समय,
				si->peak_ckpt_समय);
		seq_म_लिखो(s, "GC calls: %d (BG: %d)\n",
			   si->call_count, si->bg_gc);
		seq_म_लिखो(s, "  - data segments : %d (%d)\n",
				si->data_segs, si->bg_data_segs);
		seq_म_लिखो(s, "  - node segments : %d (%d)\n",
				si->node_segs, si->bg_node_segs);
		seq_म_लिखो(s, "Try to move %d blocks (BG: %d)\n", si->tot_blks,
				si->bg_data_blks + si->bg_node_blks);
		seq_म_लिखो(s, "  - data blocks : %d (%d)\n", si->data_blks,
				si->bg_data_blks);
		seq_म_लिखो(s, "  - node blocks : %d (%d)\n", si->node_blks,
				si->bg_node_blks);
		seq_म_लिखो(s, "Skipped : atomic write %llu (%llu)\n",
				si->skipped_atomic_files[BG_GC] +
				si->skipped_atomic_files[FG_GC],
				si->skipped_atomic_files[BG_GC]);
		seq_म_लिखो(s, "BG skip : IO: %u, Other: %u\n",
				si->io_skip_bggc, si->other_skip_bggc);
		seq_माला_दो(s, "\nExtent Cache:\n");
		seq_म_लिखो(s, "  - Hit Count: L1-1:%llu L1-2:%llu L2:%llu\n",
				si->hit_largest, si->hit_cached,
				si->hit_rbtree);
		seq_म_लिखो(s, "  - Hit Ratio: %llu%% (%llu / %llu)\n",
				!si->total_ext ? 0 :
				भाग64_u64(si->hit_total * 100, si->total_ext),
				si->hit_total, si->total_ext);
		seq_म_लिखो(s, "  - Inner Struct Count: tree: %d(%d), node: %d\n",
				si->ext_tree, si->zombie_tree, si->ext_node);
		seq_माला_दो(s, "\nBalancing F2FS Async:\n");
		seq_म_लिखो(s, "  - DIO (R: %4d, W: %4d)\n",
			   si->nr_dio_पढ़ो, si->nr_dio_ग_लिखो);
		seq_म_लिखो(s, "  - IO_R (Data: %4d, Node: %4d, Meta: %4d\n",
			   si->nr_rd_data, si->nr_rd_node, si->nr_rd_meta);
		seq_म_लिखो(s, "  - IO_W (CP: %4d, Data: %4d, Flush: (%4d %4d %4d), "
			"Discard: (%4d %4d)) cmd: %4d undiscard:%4u\n",
			   si->nr_wb_cp_data, si->nr_wb_data,
			   si->nr_flushing, si->nr_flushed,
			   si->flush_list_empty,
			   si->nr_discarding, si->nr_discarded,
			   si->nr_discard_cmd, si->undiscard_blks);
		seq_म_लिखो(s, "  - inmem: %4d, atomic IO: %4d (Max. %4d), "
			"volatile IO: %4d (Max. %4d)\n",
			   si->inmem_pages, si->aw_cnt, si->max_aw_cnt,
			   si->vw_cnt, si->max_vw_cnt);
		seq_म_लिखो(s, "  - nodes: %4d in %4d\n",
			   si->ndirty_node, si->node_pages);
		seq_म_लिखो(s, "  - dents: %4d in dirs:%4d (%4d)\n",
			   si->ndirty_dent, si->ndirty_dirs, si->ndirty_all);
		seq_म_लिखो(s, "  - datas: %4d in files:%4d\n",
			   si->ndirty_data, si->ndirty_files);
		seq_म_लिखो(s, "  - quota datas: %4d in quota files:%4d\n",
			   si->ndirty_qdata, si->nquota_files);
		seq_म_लिखो(s, "  - meta: %4d in %4d\n",
			   si->ndirty_meta, si->meta_pages);
		seq_म_लिखो(s, "  - imeta: %4d\n",
			   si->ndirty_imeta);
		seq_म_लिखो(s, "  - NATs: %9d/%9d\n  - SITs: %9d/%9d\n",
			   si->dirty_nats, si->nats, si->dirty_sits, si->sits);
		seq_म_लिखो(s, "  - free_nids: %9d/%9d\n  - alloc_nids: %9d\n",
			   si->मुक्त_nids, si->avail_nids, si->alloc_nids);
		seq_माला_दो(s, "\nDistribution of User Blocks:");
		seq_माला_दो(s, " [ valid | invalid | free ]\n");
		seq_माला_दो(s, "  [");

		क्रम (j = 0; j < si->util_valid; j++)
			seq_अ_दो(s, '-');
		seq_अ_दो(s, '|');

		क्रम (j = 0; j < si->util_invalid; j++)
			seq_अ_दो(s, '-');
		seq_अ_दो(s, '|');

		क्रम (j = 0; j < si->util_मुक्त; j++)
			seq_अ_दो(s, '-');
		seq_माला_दो(s, "]\n\n");
		seq_म_लिखो(s, "IPU: %u blocks\n", si->inplace_count);
		seq_म_लिखो(s, "SSR: %u blocks in %u segments\n",
			   si->block_count[SSR], si->segment_count[SSR]);
		seq_म_लिखो(s, "LFS: %u blocks in %u segments\n",
			   si->block_count[LFS], si->segment_count[LFS]);

		/* segment usage info */
		f2fs_update_sit_info(si->sbi);
		seq_म_लिखो(s, "\nBDF: %u, avg. vblocks: %u\n",
			   si->bimodal, si->avg_vblocks);

		/* memory footprपूर्णांक */
		update_mem_info(si->sbi);
		seq_म_लिखो(s, "\nMemory: %llu KB\n",
			(si->base_mem + si->cache_mem + si->page_mem) >> 10);
		seq_म_लिखो(s, "  - static: %llu KB\n",
				si->base_mem >> 10);
		seq_म_लिखो(s, "  - cached: %llu KB\n",
				si->cache_mem >> 10);
		seq_म_लिखो(s, "  - paged : %llu KB\n",
				si->page_mem >> 10);
	पूर्ण
	mutex_unlock(&f2fs_stat_mutex);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(stat);
#पूर्ण_अगर

पूर्णांक f2fs_build_stats(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_super_block *raw_super = F2FS_RAW_SUPER(sbi);
	काष्ठा f2fs_stat_info *si;
	पूर्णांक i;

	si = f2fs_kzalloc(sbi, माप(काष्ठा f2fs_stat_info), GFP_KERNEL);
	अगर (!si)
		वापस -ENOMEM;

	si->all_area_segs = le32_to_cpu(raw_super->segment_count);
	si->sit_area_segs = le32_to_cpu(raw_super->segment_count_sit);
	si->nat_area_segs = le32_to_cpu(raw_super->segment_count_nat);
	si->ssa_area_segs = le32_to_cpu(raw_super->segment_count_ssa);
	si->मुख्य_area_segs = le32_to_cpu(raw_super->segment_count_मुख्य);
	si->मुख्य_area_sections = le32_to_cpu(raw_super->section_count);
	si->मुख्य_area_zones = si->मुख्य_area_sections /
				le32_to_cpu(raw_super->secs_per_zone);
	si->sbi = sbi;
	sbi->stat_info = si;

	atomic64_set(&sbi->total_hit_ext, 0);
	atomic64_set(&sbi->पढ़ो_hit_rbtree, 0);
	atomic64_set(&sbi->पढ़ो_hit_largest, 0);
	atomic64_set(&sbi->पढ़ो_hit_cached, 0);

	atomic_set(&sbi->अंतरभूत_xattr, 0);
	atomic_set(&sbi->अंतरभूत_inode, 0);
	atomic_set(&sbi->अंतरभूत_dir, 0);
	atomic_set(&sbi->compr_inode, 0);
	atomic64_set(&sbi->compr_blocks, 0);
	atomic_set(&sbi->inplace_count, 0);
	क्रम (i = META_CP; i < META_MAX; i++)
		atomic_set(&sbi->meta_count[i], 0);

	atomic_set(&sbi->vw_cnt, 0);
	atomic_set(&sbi->max_aw_cnt, 0);
	atomic_set(&sbi->max_vw_cnt, 0);

	mutex_lock(&f2fs_stat_mutex);
	list_add_tail(&si->stat_list, &f2fs_stat_list);
	mutex_unlock(&f2fs_stat_mutex);

	वापस 0;
पूर्ण

व्योम f2fs_destroy_stats(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);

	mutex_lock(&f2fs_stat_mutex);
	list_del(&si->stat_list);
	mutex_unlock(&f2fs_stat_mutex);

	kमुक्त(si);
पूर्ण

व्योम __init f2fs_create_root_stats(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	f2fs_debugfs_root = debugfs_create_dir("f2fs", शून्य);

	debugfs_create_file("status", S_IRUGO, f2fs_debugfs_root, शून्य,
			    &stat_fops);
#पूर्ण_अगर
पूर्ण

व्योम f2fs_destroy_root_stats(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	debugfs_हटाओ_recursive(f2fs_debugfs_root);
	f2fs_debugfs_root = शून्य;
#पूर्ण_अगर
पूर्ण
