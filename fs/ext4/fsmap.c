<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "ext4.h"
#समावेश <linux/fsmap.h>
#समावेश "fsmap.h"
#समावेश "mballoc.h"
#समावेश <linux/sort.h>
#समावेश <linux/list_sort.h>
#समावेश <trace/events/ext4.h>

/* Convert an ext4_fsmap to an fsmap. */
व्योम ext4_fsmap_from_पूर्णांकernal(काष्ठा super_block *sb, काष्ठा fsmap *dest,
			      काष्ठा ext4_fsmap *src)
अणु
	dest->fmr_device = src->fmr_device;
	dest->fmr_flags = src->fmr_flags;
	dest->fmr_physical = src->fmr_physical << sb->s_blocksize_bits;
	dest->fmr_owner = src->fmr_owner;
	dest->fmr_offset = 0;
	dest->fmr_length = src->fmr_length << sb->s_blocksize_bits;
	dest->fmr_reserved[0] = 0;
	dest->fmr_reserved[1] = 0;
	dest->fmr_reserved[2] = 0;
पूर्ण

/* Convert an fsmap to an ext4_fsmap. */
व्योम ext4_fsmap_to_पूर्णांकernal(काष्ठा super_block *sb, काष्ठा ext4_fsmap *dest,
			    काष्ठा fsmap *src)
अणु
	dest->fmr_device = src->fmr_device;
	dest->fmr_flags = src->fmr_flags;
	dest->fmr_physical = src->fmr_physical >> sb->s_blocksize_bits;
	dest->fmr_owner = src->fmr_owner;
	dest->fmr_length = src->fmr_length >> sb->s_blocksize_bits;
पूर्ण

/* getfsmap query state */
काष्ठा ext4_getfsmap_info अणु
	काष्ठा ext4_fsmap_head	*gfi_head;
	ext4_fsmap_क्रमmat_t	gfi_क्रमmatter;	/* क्रमmatting fn */
	व्योम			*gfi_क्रमmat_arg;/* क्रमmat buffer */
	ext4_fsblk_t		gfi_next_fsblk;	/* next fsblock we expect */
	u32			gfi_dev;	/* device id */
	ext4_group_t		gfi_agno;	/* bg number, अगर applicable */
	काष्ठा ext4_fsmap	gfi_low;	/* low rmap key */
	काष्ठा ext4_fsmap	gfi_high;	/* high rmap key */
	काष्ठा ext4_fsmap	gfi_lastमुक्त;	/* मुक्त ext at end of last bg */
	काष्ठा list_head	gfi_meta_list;	/* fixed metadata list */
	bool			gfi_last;	/* last extent? */
पूर्ण;

/* Associate a device with a getfsmap handler. */
काष्ठा ext4_getfsmap_dev अणु
	पूर्णांक			(*gfd_fn)(काष्ठा super_block *sb,
				      काष्ठा ext4_fsmap *keys,
				      काष्ठा ext4_getfsmap_info *info);
	u32			gfd_dev;
पूर्ण;

/* Compare two getfsmap device handlers. */
अटल पूर्णांक ext4_getfsmap_dev_compare(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा ext4_getfsmap_dev *d1 = p1;
	स्थिर काष्ठा ext4_getfsmap_dev *d2 = p2;

	वापस d1->gfd_dev - d2->gfd_dev;
पूर्ण

/* Compare a record against our starting poपूर्णांक */
अटल bool ext4_getfsmap_rec_beक्रमe_low_key(काष्ठा ext4_getfsmap_info *info,
					     काष्ठा ext4_fsmap *rec)
अणु
	वापस rec->fmr_physical < info->gfi_low.fmr_physical;
पूर्ण

/*
 * Format a reverse mapping क्रम getfsmap, having translated rm_startblock
 * पूर्णांकo the appropriate daddr units.
 */
अटल पूर्णांक ext4_getfsmap_helper(काष्ठा super_block *sb,
				काष्ठा ext4_getfsmap_info *info,
				काष्ठा ext4_fsmap *rec)
अणु
	काष्ठा ext4_fsmap fmr;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t rec_fsblk = rec->fmr_physical;
	ext4_group_t agno;
	ext4_grpblk_t cno;
	पूर्णांक error;

	अगर (fatal_संकेत_pending(current))
		वापस -EINTR;

	/*
	 * Filter out records that start beक्रमe our startpoपूर्णांक, अगर the
	 * caller requested that.
	 */
	अगर (ext4_getfsmap_rec_beक्रमe_low_key(info, rec)) अणु
		rec_fsblk += rec->fmr_length;
		अगर (info->gfi_next_fsblk < rec_fsblk)
			info->gfi_next_fsblk = rec_fsblk;
		वापस EXT4_QUERY_RANGE_CONTINUE;
	पूर्ण

	/* Are we just counting mappings? */
	अगर (info->gfi_head->fmh_count == 0) अणु
		अगर (info->gfi_head->fmh_entries == अच_पूर्णांक_उच्च)
			वापस EXT4_QUERY_RANGE_ABORT;

		अगर (rec_fsblk > info->gfi_next_fsblk)
			info->gfi_head->fmh_entries++;

		अगर (info->gfi_last)
			वापस EXT4_QUERY_RANGE_CONTINUE;

		info->gfi_head->fmh_entries++;

		rec_fsblk += rec->fmr_length;
		अगर (info->gfi_next_fsblk < rec_fsblk)
			info->gfi_next_fsblk = rec_fsblk;
		वापस EXT4_QUERY_RANGE_CONTINUE;
	पूर्ण

	/*
	 * If the record starts past the last physical block we saw,
	 * then we've found a gap.  Report the gap as being owned by
	 * whatever the caller specअगरied is the missing owner.
	 */
	अगर (rec_fsblk > info->gfi_next_fsblk) अणु
		अगर (info->gfi_head->fmh_entries >= info->gfi_head->fmh_count)
			वापस EXT4_QUERY_RANGE_ABORT;

		ext4_get_group_no_and_offset(sb, info->gfi_next_fsblk,
				&agno, &cno);
		trace_ext4_fsmap_mapping(sb, info->gfi_dev, agno,
				EXT4_C2B(sbi, cno),
				rec_fsblk - info->gfi_next_fsblk,
				EXT4_FMR_OWN_UNKNOWN);

		fmr.fmr_device = info->gfi_dev;
		fmr.fmr_physical = info->gfi_next_fsblk;
		fmr.fmr_owner = EXT4_FMR_OWN_UNKNOWN;
		fmr.fmr_length = rec_fsblk - info->gfi_next_fsblk;
		fmr.fmr_flags = FMR_OF_SPECIAL_OWNER;
		error = info->gfi_क्रमmatter(&fmr, info->gfi_क्रमmat_arg);
		अगर (error)
			वापस error;
		info->gfi_head->fmh_entries++;
	पूर्ण

	अगर (info->gfi_last)
		जाओ out;

	/* Fill out the extent we found */
	अगर (info->gfi_head->fmh_entries >= info->gfi_head->fmh_count)
		वापस EXT4_QUERY_RANGE_ABORT;

	ext4_get_group_no_and_offset(sb, rec_fsblk, &agno, &cno);
	trace_ext4_fsmap_mapping(sb, info->gfi_dev, agno, EXT4_C2B(sbi, cno),
			rec->fmr_length, rec->fmr_owner);

	fmr.fmr_device = info->gfi_dev;
	fmr.fmr_physical = rec_fsblk;
	fmr.fmr_owner = rec->fmr_owner;
	fmr.fmr_flags = FMR_OF_SPECIAL_OWNER;
	fmr.fmr_length = rec->fmr_length;
	error = info->gfi_क्रमmatter(&fmr, info->gfi_क्रमmat_arg);
	अगर (error)
		वापस error;
	info->gfi_head->fmh_entries++;

out:
	rec_fsblk += rec->fmr_length;
	अगर (info->gfi_next_fsblk < rec_fsblk)
		info->gfi_next_fsblk = rec_fsblk;
	वापस EXT4_QUERY_RANGE_CONTINUE;
पूर्ण

अटल अंतरभूत ext4_fsblk_t ext4_fsmap_next_pblk(काष्ठा ext4_fsmap *fmr)
अणु
	वापस fmr->fmr_physical + fmr->fmr_length;
पूर्ण

/* Transक्रमm a blockgroup's मुक्त record पूर्णांकo a fsmap */
अटल पूर्णांक ext4_getfsmap_datadev_helper(काष्ठा super_block *sb,
					ext4_group_t agno, ext4_grpblk_t start,
					ext4_grpblk_t len, व्योम *priv)
अणु
	काष्ठा ext4_fsmap irec;
	काष्ठा ext4_getfsmap_info *info = priv;
	काष्ठा ext4_fsmap *p;
	काष्ठा ext4_fsmap *पंचांगp;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t fsb;
	ext4_fsblk_t fslen;
	पूर्णांक error;

	fsb = (EXT4_C2B(sbi, start) + ext4_group_first_block_no(sb, agno));
	fslen = EXT4_C2B(sbi, len);

	/* If the retained मुक्त extent record is set... */
	अगर (info->gfi_lastमुक्त.fmr_owner) अणु
		/* ...and abuts this one, lengthen it and वापस. */
		अगर (ext4_fsmap_next_pblk(&info->gfi_lastमुक्त) == fsb) अणु
			info->gfi_lastमुक्त.fmr_length += fslen;
			वापस 0;
		पूर्ण

		/*
		 * There's a gap between the two मुक्त extents; emit the
		 * retained extent prior to merging the meta_list.
		 */
		error = ext4_getfsmap_helper(sb, info, &info->gfi_lastमुक्त);
		अगर (error)
			वापस error;
		info->gfi_lastमुक्त.fmr_owner = 0;
	पूर्ण

	/* Merge in any relevant extents from the meta_list */
	list_क्रम_each_entry_safe(p, पंचांगp, &info->gfi_meta_list, fmr_list) अणु
		अगर (p->fmr_physical + p->fmr_length <= info->gfi_next_fsblk) अणु
			list_del(&p->fmr_list);
			kमुक्त(p);
		पूर्ण अन्यथा अगर (p->fmr_physical < fsb) अणु
			error = ext4_getfsmap_helper(sb, info, p);
			अगर (error)
				वापस error;

			list_del(&p->fmr_list);
			kमुक्त(p);
		पूर्ण
	पूर्ण

	irec.fmr_device = 0;
	irec.fmr_physical = fsb;
	irec.fmr_length = fslen;
	irec.fmr_owner = EXT4_FMR_OWN_FREE;
	irec.fmr_flags = 0;

	/* If this is a मुक्त extent at the end of a bg, buffer it. */
	अगर (ext4_fsmap_next_pblk(&irec) ==
			ext4_group_first_block_no(sb, agno + 1)) अणु
		info->gfi_lastमुक्त = irec;
		वापस 0;
	पूर्ण

	/* Otherwise, emit it */
	वापस ext4_getfsmap_helper(sb, info, &irec);
पूर्ण

/* Execute a getfsmap query against the log device. */
अटल पूर्णांक ext4_getfsmap_logdev(काष्ठा super_block *sb, काष्ठा ext4_fsmap *keys,
				काष्ठा ext4_getfsmap_info *info)
अणु
	journal_t *journal = EXT4_SB(sb)->s_journal;
	काष्ठा ext4_fsmap irec;

	/* Set up search keys */
	info->gfi_low = keys[0];
	info->gfi_low.fmr_length = 0;

	स_रखो(&info->gfi_high, 0xFF, माप(info->gfi_high));

	trace_ext4_fsmap_low_key(sb, info->gfi_dev, 0,
			info->gfi_low.fmr_physical,
			info->gfi_low.fmr_length,
			info->gfi_low.fmr_owner);

	trace_ext4_fsmap_high_key(sb, info->gfi_dev, 0,
			info->gfi_high.fmr_physical,
			info->gfi_high.fmr_length,
			info->gfi_high.fmr_owner);

	अगर (keys[0].fmr_physical > 0)
		वापस 0;

	/* Fabricate an rmap entry क्रम the बाह्यal log device. */
	irec.fmr_physical = journal->j_blk_offset;
	irec.fmr_length = journal->j_total_len;
	irec.fmr_owner = EXT4_FMR_OWN_LOG;
	irec.fmr_flags = 0;

	वापस ext4_getfsmap_helper(sb, info, &irec);
पूर्ण

/* Helper to fill out an ext4_fsmap. */
अटल अंतरभूत पूर्णांक ext4_getfsmap_fill(काष्ठा list_head *meta_list,
				     ext4_fsblk_t fsb, ext4_fsblk_t len,
				     uपूर्णांक64_t owner)
अणु
	काष्ठा ext4_fsmap *fsm;

	fsm = kदो_स्मृति(माप(*fsm), GFP_NOFS);
	अगर (!fsm)
		वापस -ENOMEM;
	fsm->fmr_device = 0;
	fsm->fmr_flags = 0;
	fsm->fmr_physical = fsb;
	fsm->fmr_owner = owner;
	fsm->fmr_length = len;
	list_add_tail(&fsm->fmr_list, meta_list);

	वापस 0;
पूर्ण

/*
 * This function वापसs the number of file प्रणाली metadata blocks at
 * the beginning of a block group, including the reserved gdt blocks.
 */
अटल अचिन्हित पूर्णांक ext4_getfsmap_find_sb(काष्ठा super_block *sb,
					  ext4_group_t agno,
					  काष्ठा list_head *meta_list)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t fsb = ext4_group_first_block_no(sb, agno);
	ext4_fsblk_t len;
	अचिन्हित दीर्घ first_meta_bg = le32_to_cpu(sbi->s_es->s_first_meta_bg);
	अचिन्हित दीर्घ metagroup = agno / EXT4_DESC_PER_BLOCK(sb);
	पूर्णांक error;

	/* Record the superblock. */
	अगर (ext4_bg_has_super(sb, agno)) अणु
		error = ext4_getfsmap_fill(meta_list, fsb, 1, EXT4_FMR_OWN_FS);
		अगर (error)
			वापस error;
		fsb++;
	पूर्ण

	/* Record the group descriptors. */
	len = ext4_bg_num_gdb(sb, agno);
	अगर (!len)
		वापस 0;
	error = ext4_getfsmap_fill(meta_list, fsb, len,
				   EXT4_FMR_OWN_GDT);
	अगर (error)
		वापस error;
	fsb += len;

	/* Reserved GDT blocks */
	अगर (!ext4_has_feature_meta_bg(sb) || metagroup < first_meta_bg) अणु
		len = le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks);
		error = ext4_getfsmap_fill(meta_list, fsb, len,
					   EXT4_FMR_OWN_RESV_GDT);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/* Compare two fsmap items. */
अटल पूर्णांक ext4_getfsmap_compare(व्योम *priv,
				 स्थिर काष्ठा list_head *a,
				 स्थिर काष्ठा list_head *b)
अणु
	काष्ठा ext4_fsmap *fa;
	काष्ठा ext4_fsmap *fb;

	fa = container_of(a, काष्ठा ext4_fsmap, fmr_list);
	fb = container_of(b, काष्ठा ext4_fsmap, fmr_list);
	अगर (fa->fmr_physical < fb->fmr_physical)
		वापस -1;
	अन्यथा अगर (fa->fmr_physical > fb->fmr_physical)
		वापस 1;
	वापस 0;
पूर्ण

/* Merge adjacent extents of fixed metadata. */
अटल व्योम ext4_getfsmap_merge_fixed_metadata(काष्ठा list_head *meta_list)
अणु
	काष्ठा ext4_fsmap *p;
	काष्ठा ext4_fsmap *prev = शून्य;
	काष्ठा ext4_fsmap *पंचांगp;

	list_क्रम_each_entry_safe(p, पंचांगp, meta_list, fmr_list) अणु
		अगर (!prev) अणु
			prev = p;
			जारी;
		पूर्ण

		अगर (prev->fmr_owner == p->fmr_owner &&
		    prev->fmr_physical + prev->fmr_length == p->fmr_physical) अणु
			prev->fmr_length += p->fmr_length;
			list_del(&p->fmr_list);
			kमुक्त(p);
		पूर्ण अन्यथा
			prev = p;
	पूर्ण
पूर्ण

/* Free a list of fixed metadata. */
अटल व्योम ext4_getfsmap_मुक्त_fixed_metadata(काष्ठा list_head *meta_list)
अणु
	काष्ठा ext4_fsmap *p;
	काष्ठा ext4_fsmap *पंचांगp;

	list_क्रम_each_entry_safe(p, पंचांगp, meta_list, fmr_list) अणु
		list_del(&p->fmr_list);
		kमुक्त(p);
	पूर्ण
पूर्ण

/* Find all the fixed metadata in the fileप्रणाली. */
अटल पूर्णांक ext4_getfsmap_find_fixed_metadata(काष्ठा super_block *sb,
					     काष्ठा list_head *meta_list)
अणु
	काष्ठा ext4_group_desc *gdp;
	ext4_group_t agno;
	पूर्णांक error;

	INIT_LIST_HEAD(meta_list);

	/* Collect everything. */
	क्रम (agno = 0; agno < EXT4_SB(sb)->s_groups_count; agno++) अणु
		gdp = ext4_get_group_desc(sb, agno, शून्य);
		अगर (!gdp) अणु
			error = -EFSCORRUPTED;
			जाओ err;
		पूर्ण

		/* Superblock & GDT */
		error = ext4_getfsmap_find_sb(sb, agno, meta_list);
		अगर (error)
			जाओ err;

		/* Block biपंचांगap */
		error = ext4_getfsmap_fill(meta_list,
					   ext4_block_biपंचांगap(sb, gdp), 1,
					   EXT4_FMR_OWN_BLKBM);
		अगर (error)
			जाओ err;

		/* Inode biपंचांगap */
		error = ext4_getfsmap_fill(meta_list,
					   ext4_inode_biपंचांगap(sb, gdp), 1,
					   EXT4_FMR_OWN_INOBM);
		अगर (error)
			जाओ err;

		/* Inodes */
		error = ext4_getfsmap_fill(meta_list,
					   ext4_inode_table(sb, gdp),
					   EXT4_SB(sb)->s_itb_per_group,
					   EXT4_FMR_OWN_INODES);
		अगर (error)
			जाओ err;
	पूर्ण

	/* Sort the list */
	list_sort(शून्य, meta_list, ext4_getfsmap_compare);

	/* Merge adjacent extents */
	ext4_getfsmap_merge_fixed_metadata(meta_list);

	वापस 0;
err:
	ext4_getfsmap_मुक्त_fixed_metadata(meta_list);
	वापस error;
पूर्ण

/* Execute a getfsmap query against the buddy biपंचांगaps */
अटल पूर्णांक ext4_getfsmap_datadev(काष्ठा super_block *sb,
				 काष्ठा ext4_fsmap *keys,
				 काष्ठा ext4_getfsmap_info *info)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t start_fsb;
	ext4_fsblk_t end_fsb;
	ext4_fsblk_t bofs;
	ext4_fsblk_t eofs;
	ext4_group_t start_ag;
	ext4_group_t end_ag;
	ext4_grpblk_t first_cluster;
	ext4_grpblk_t last_cluster;
	पूर्णांक error = 0;

	bofs = le32_to_cpu(sbi->s_es->s_first_data_block);
	eofs = ext4_blocks_count(sbi->s_es);
	अगर (keys[0].fmr_physical >= eofs)
		वापस 0;
	अन्यथा अगर (keys[0].fmr_physical < bofs)
		keys[0].fmr_physical = bofs;
	अगर (keys[1].fmr_physical >= eofs)
		keys[1].fmr_physical = eofs - 1;
	start_fsb = keys[0].fmr_physical;
	end_fsb = keys[1].fmr_physical;

	/* Determine first and last group to examine based on start and end */
	ext4_get_group_no_and_offset(sb, start_fsb, &start_ag, &first_cluster);
	ext4_get_group_no_and_offset(sb, end_fsb, &end_ag, &last_cluster);

	/*
	 * Convert the fsmap low/high keys to bg based keys.  Initialize
	 * low to the fsmap low key and max out the high key to the end
	 * of the bg.
	 */
	info->gfi_low = keys[0];
	info->gfi_low.fmr_physical = EXT4_C2B(sbi, first_cluster);
	info->gfi_low.fmr_length = 0;

	स_रखो(&info->gfi_high, 0xFF, माप(info->gfi_high));

	/* Assemble a list of all the fixed-location metadata. */
	error = ext4_getfsmap_find_fixed_metadata(sb, &info->gfi_meta_list);
	अगर (error)
		जाओ err;

	/* Query each bg */
	क्रम (info->gfi_agno = start_ag;
	     info->gfi_agno <= end_ag;
	     info->gfi_agno++) अणु
		/*
		 * Set the bg high key from the fsmap high key अगर this
		 * is the last bg that we're querying.
		 */
		अगर (info->gfi_agno == end_ag) अणु
			info->gfi_high = keys[1];
			info->gfi_high.fmr_physical = EXT4_C2B(sbi,
					last_cluster);
			info->gfi_high.fmr_length = 0;
		पूर्ण

		trace_ext4_fsmap_low_key(sb, info->gfi_dev, info->gfi_agno,
				info->gfi_low.fmr_physical,
				info->gfi_low.fmr_length,
				info->gfi_low.fmr_owner);

		trace_ext4_fsmap_high_key(sb, info->gfi_dev, info->gfi_agno,
				info->gfi_high.fmr_physical,
				info->gfi_high.fmr_length,
				info->gfi_high.fmr_owner);

		error = ext4_mballoc_query_range(sb, info->gfi_agno,
				EXT4_B2C(sbi, info->gfi_low.fmr_physical),
				EXT4_B2C(sbi, info->gfi_high.fmr_physical),
				ext4_getfsmap_datadev_helper, info);
		अगर (error)
			जाओ err;

		/*
		 * Set the bg low key to the start of the bg prior to
		 * moving on to the next bg.
		 */
		अगर (info->gfi_agno == start_ag)
			स_रखो(&info->gfi_low, 0, माप(info->gfi_low));
	पूर्ण

	/* Do we have a retained मुक्त extent? */
	अगर (info->gfi_lastमुक्त.fmr_owner) अणु
		error = ext4_getfsmap_helper(sb, info, &info->gfi_lastमुक्त);
		अगर (error)
			जाओ err;
	पूर्ण

	/* Report any gaps at the end of the bg */
	info->gfi_last = true;
	error = ext4_getfsmap_datadev_helper(sb, end_ag, last_cluster, 0, info);
	अगर (error)
		जाओ err;

err:
	ext4_getfsmap_मुक्त_fixed_metadata(&info->gfi_meta_list);
	वापस error;
पूर्ण

/* Do we recognize the device? */
अटल bool ext4_getfsmap_is_valid_device(काष्ठा super_block *sb,
					  काष्ठा ext4_fsmap *fm)
अणु
	अगर (fm->fmr_device == 0 || fm->fmr_device == अच_पूर्णांक_उच्च ||
	    fm->fmr_device == new_encode_dev(sb->s_bdev->bd_dev))
		वापस true;
	अगर (EXT4_SB(sb)->s_journal_bdev &&
	    fm->fmr_device == new_encode_dev(EXT4_SB(sb)->s_journal_bdev->bd_dev))
		वापस true;
	वापस false;
पूर्ण

/* Ensure that the low key is less than the high key. */
अटल bool ext4_getfsmap_check_keys(काष्ठा ext4_fsmap *low_key,
				     काष्ठा ext4_fsmap *high_key)
अणु
	अगर (low_key->fmr_device > high_key->fmr_device)
		वापस false;
	अगर (low_key->fmr_device < high_key->fmr_device)
		वापस true;

	अगर (low_key->fmr_physical > high_key->fmr_physical)
		वापस false;
	अगर (low_key->fmr_physical < high_key->fmr_physical)
		वापस true;

	अगर (low_key->fmr_owner > high_key->fmr_owner)
		वापस false;
	अगर (low_key->fmr_owner < high_key->fmr_owner)
		वापस true;

	वापस false;
पूर्ण

#घोषणा EXT4_GETFSMAP_DEVS	2
/*
 * Get fileप्रणाली's extents as described in head, and क्रमmat क्रम
 * output.  Calls क्रमmatter to fill the user's buffer until all
 * extents are mapped, until the passed-in head->fmh_count slots have
 * been filled, or until the क्रमmatter लघु-circuits the loop, अगर it
 * is tracking filled-in extents on its own.
 *
 * Key to Confusion
 * ----------------
 * There are multiple levels of keys and counters at work here:
 * _fsmap_head.fmh_keys		-- low and high fsmap keys passed in;
 * 				   these reflect fs-wide block addrs.
 * dkeys			-- fmh_keys used to query each device;
 * 				   these are fmh_keys but w/ the low key
 * 				   bumped up by fmr_length.
 * _getfsmap_info.gfi_next_fsblk-- next fs block we expect to see; this
 *				   is how we detect gaps in the fsmap
 *				   records and report them.
 * _getfsmap_info.gfi_low/high	-- per-bg low/high keys computed from
 * 				   dkeys; used to query the मुक्त space.
 */
पूर्णांक ext4_getfsmap(काष्ठा super_block *sb, काष्ठा ext4_fsmap_head *head,
		  ext4_fsmap_क्रमmat_t क्रमmatter, व्योम *arg)
अणु
	काष्ठा ext4_fsmap dkeys[2];	/* per-dev keys */
	काष्ठा ext4_getfsmap_dev handlers[EXT4_GETFSMAP_DEVS];
	काष्ठा ext4_getfsmap_info info = अणु शून्य पूर्ण;
	पूर्णांक i;
	पूर्णांक error = 0;

	अगर (head->fmh_अगरlags & ~FMH_IF_VALID)
		वापस -EINVAL;
	अगर (!ext4_getfsmap_is_valid_device(sb, &head->fmh_keys[0]) ||
	    !ext4_getfsmap_is_valid_device(sb, &head->fmh_keys[1]))
		वापस -EINVAL;

	head->fmh_entries = 0;

	/* Set up our device handlers. */
	स_रखो(handlers, 0, माप(handlers));
	handlers[0].gfd_dev = new_encode_dev(sb->s_bdev->bd_dev);
	handlers[0].gfd_fn = ext4_getfsmap_datadev;
	अगर (EXT4_SB(sb)->s_journal_bdev) अणु
		handlers[1].gfd_dev = new_encode_dev(
				EXT4_SB(sb)->s_journal_bdev->bd_dev);
		handlers[1].gfd_fn = ext4_getfsmap_logdev;
	पूर्ण

	sort(handlers, EXT4_GETFSMAP_DEVS, माप(काष्ठा ext4_getfsmap_dev),
			ext4_getfsmap_dev_compare, शून्य);

	/*
	 * To जारी where we left off, we allow userspace to use the
	 * last mapping from a previous call as the low key of the next.
	 * This is identअगरied by a non-zero length in the low key. We
	 * have to increment the low key in this scenario to ensure we
	 * करोn't वापस the same mapping again, and instead वापस the
	 * very next mapping.
	 *
	 * Bump the physical offset as there can be no other mapping क्रम
	 * the same physical block range.
	 */
	dkeys[0] = head->fmh_keys[0];
	dkeys[0].fmr_physical += dkeys[0].fmr_length;
	dkeys[0].fmr_owner = 0;
	dkeys[0].fmr_length = 0;
	स_रखो(&dkeys[1], 0xFF, माप(काष्ठा ext4_fsmap));

	अगर (!ext4_getfsmap_check_keys(dkeys, &head->fmh_keys[1]))
		वापस -EINVAL;

	info.gfi_next_fsblk = head->fmh_keys[0].fmr_physical +
			  head->fmh_keys[0].fmr_length;
	info.gfi_क्रमmatter = क्रमmatter;
	info.gfi_क्रमmat_arg = arg;
	info.gfi_head = head;

	/* For each device we support... */
	क्रम (i = 0; i < EXT4_GETFSMAP_DEVS; i++) अणु
		/* Is this device within the range the user asked क्रम? */
		अगर (!handlers[i].gfd_fn)
			जारी;
		अगर (head->fmh_keys[0].fmr_device > handlers[i].gfd_dev)
			जारी;
		अगर (head->fmh_keys[1].fmr_device < handlers[i].gfd_dev)
			अवरोध;

		/*
		 * If this device number matches the high key, we have
		 * to pass the high key to the handler to limit the
		 * query results.  If the device number exceeds the
		 * low key, zero out the low key so that we get
		 * everything from the beginning.
		 */
		अगर (handlers[i].gfd_dev == head->fmh_keys[1].fmr_device)
			dkeys[1] = head->fmh_keys[1];
		अगर (handlers[i].gfd_dev > head->fmh_keys[0].fmr_device)
			स_रखो(&dkeys[0], 0, माप(काष्ठा ext4_fsmap));

		info.gfi_dev = handlers[i].gfd_dev;
		info.gfi_last = false;
		info.gfi_agno = -1;
		error = handlers[i].gfd_fn(sb, dkeys, &info);
		अगर (error)
			अवरोध;
		info.gfi_next_fsblk = 0;
	पूर्ण

	head->fmh_oflags = FMH_OF_DEV_T;
	वापस error;
पूर्ण
