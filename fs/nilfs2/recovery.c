<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * recovery.c - NILFS recovery logic
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc32.h>
#समावेश "nilfs.h"
#समावेश "segment.h"
#समावेश "sufile.h"
#समावेश "page.h"
#समावेश "segbuf.h"

/*
 * Segment check result
 */
क्रमागत अणु
	NILFS_SEG_VALID,
	NILFS_SEG_NO_SUPER_ROOT,
	NILFS_SEG_FAIL_IO,
	NILFS_SEG_FAIL_MAGIC,
	NILFS_SEG_FAIL_SEQ,
	NILFS_SEG_FAIL_CHECKSUM_SUPER_ROOT,
	NILFS_SEG_FAIL_CHECKSUM_FULL,
	NILFS_SEG_FAIL_CONSISTENCY,
पूर्ण;

/* work काष्ठाure क्रम recovery */
काष्ठा nilfs_recovery_block अणु
	ino_t ino;		/*
				 * Inode number of the file that this block
				 * beदीर्घs to
				 */
	sector_t blocknr;	/* block number */
	__u64 vblocknr;		/* भव block number */
	अचिन्हित दीर्घ blkoff;	/* File offset of the data block (per block) */
	काष्ठा list_head list;
पूर्ण;


अटल पूर्णांक nilfs_warn_segment_error(काष्ठा super_block *sb, पूर्णांक err)
अणु
	स्थिर अक्षर *msg = शून्य;

	चयन (err) अणु
	हाल NILFS_SEG_FAIL_IO:
		nilfs_err(sb, "I/O error reading segment");
		वापस -EIO;
	हाल NILFS_SEG_FAIL_MAGIC:
		msg = "Magic number mismatch";
		अवरोध;
	हाल NILFS_SEG_FAIL_SEQ:
		msg = "Sequence number mismatch";
		अवरोध;
	हाल NILFS_SEG_FAIL_CHECKSUM_SUPER_ROOT:
		msg = "Checksum error in super root";
		अवरोध;
	हाल NILFS_SEG_FAIL_CHECKSUM_FULL:
		msg = "Checksum error in segment payload";
		अवरोध;
	हाल NILFS_SEG_FAIL_CONSISTENCY:
		msg = "Inconsistency found";
		अवरोध;
	हाल NILFS_SEG_NO_SUPER_ROOT:
		msg = "No super root in the last segment";
		अवरोध;
	शेष:
		nilfs_err(sb, "unrecognized segment error %d", err);
		वापस -EINVAL;
	पूर्ण
	nilfs_warn(sb, "invalid segment: %s", msg);
	वापस -EINVAL;
पूर्ण

/**
 * nilfs_compute_checksum - compute checksum of blocks continuously
 * @nilfs: nilfs object
 * @bhs: buffer head of start block
 * @sum: place to store result
 * @offset: offset bytes in the first block
 * @check_bytes: number of bytes to be checked
 * @start: DBN of start block
 * @nblock: number of blocks to be checked
 */
अटल पूर्णांक nilfs_compute_checksum(काष्ठा the_nilfs *nilfs,
				  काष्ठा buffer_head *bhs, u32 *sum,
				  अचिन्हित दीर्घ offset, u64 check_bytes,
				  sector_t start, अचिन्हित दीर्घ nblock)
अणु
	अचिन्हित पूर्णांक blocksize = nilfs->ns_blocksize;
	अचिन्हित दीर्घ size;
	u32 crc;

	BUG_ON(offset >= blocksize);
	check_bytes -= offset;
	size = min_t(u64, check_bytes, blocksize - offset);
	crc = crc32_le(nilfs->ns_crc_seed,
		       (अचिन्हित अक्षर *)bhs->b_data + offset, size);
	अगर (--nblock > 0) अणु
		करो अणु
			काष्ठा buffer_head *bh;

			bh = __bपढ़ो(nilfs->ns_bdev, ++start, blocksize);
			अगर (!bh)
				वापस -EIO;
			check_bytes -= size;
			size = min_t(u64, check_bytes, blocksize);
			crc = crc32_le(crc, bh->b_data, size);
			brअन्यथा(bh);
		पूर्ण जबतक (--nblock > 0);
	पूर्ण
	*sum = crc;
	वापस 0;
पूर्ण

/**
 * nilfs_पढ़ो_super_root_block - पढ़ो super root block
 * @nilfs: nilfs object
 * @sr_block: disk block number of the super root block
 * @pbh: address of a buffer_head poपूर्णांकer to वापस super root buffer
 * @check: CRC check flag
 */
पूर्णांक nilfs_पढ़ो_super_root_block(काष्ठा the_nilfs *nilfs, sector_t sr_block,
				काष्ठा buffer_head **pbh, पूर्णांक check)
अणु
	काष्ठा buffer_head *bh_sr;
	काष्ठा nilfs_super_root *sr;
	u32 crc;
	पूर्णांक ret;

	*pbh = शून्य;
	bh_sr = __bपढ़ो(nilfs->ns_bdev, sr_block, nilfs->ns_blocksize);
	अगर (unlikely(!bh_sr)) अणु
		ret = NILFS_SEG_FAIL_IO;
		जाओ failed;
	पूर्ण

	sr = (काष्ठा nilfs_super_root *)bh_sr->b_data;
	अगर (check) अणु
		अचिन्हित पूर्णांक bytes = le16_to_cpu(sr->sr_bytes);

		अगर (bytes == 0 || bytes > nilfs->ns_blocksize) अणु
			ret = NILFS_SEG_FAIL_CHECKSUM_SUPER_ROOT;
			जाओ failed_bh;
		पूर्ण
		अगर (nilfs_compute_checksum(
			    nilfs, bh_sr, &crc, माप(sr->sr_sum), bytes,
			    sr_block, 1)) अणु
			ret = NILFS_SEG_FAIL_IO;
			जाओ failed_bh;
		पूर्ण
		अगर (crc != le32_to_cpu(sr->sr_sum)) अणु
			ret = NILFS_SEG_FAIL_CHECKSUM_SUPER_ROOT;
			जाओ failed_bh;
		पूर्ण
	पूर्ण
	*pbh = bh_sr;
	वापस 0;

 failed_bh:
	brअन्यथा(bh_sr);

 failed:
	वापस nilfs_warn_segment_error(nilfs->ns_sb, ret);
पूर्ण

/**
 * nilfs_पढ़ो_log_header - पढ़ो summary header of the specअगरied log
 * @nilfs: nilfs object
 * @start_blocknr: start block number of the log
 * @sum: poपूर्णांकer to वापस segment summary काष्ठाure
 */
अटल काष्ठा buffer_head *
nilfs_पढ़ो_log_header(काष्ठा the_nilfs *nilfs, sector_t start_blocknr,
		      काष्ठा nilfs_segment_summary **sum)
अणु
	काष्ठा buffer_head *bh_sum;

	bh_sum = __bपढ़ो(nilfs->ns_bdev, start_blocknr, nilfs->ns_blocksize);
	अगर (bh_sum)
		*sum = (काष्ठा nilfs_segment_summary *)bh_sum->b_data;
	वापस bh_sum;
पूर्ण

/**
 * nilfs_validate_log - verअगरy consistency of log
 * @nilfs: nilfs object
 * @seg_seq: sequence number of segment
 * @bh_sum: buffer head of summary block
 * @sum: segment summary काष्ठा
 */
अटल पूर्णांक nilfs_validate_log(काष्ठा the_nilfs *nilfs, u64 seg_seq,
			      काष्ठा buffer_head *bh_sum,
			      काष्ठा nilfs_segment_summary *sum)
अणु
	अचिन्हित दीर्घ nblock;
	u32 crc;
	पूर्णांक ret;

	ret = NILFS_SEG_FAIL_MAGIC;
	अगर (le32_to_cpu(sum->ss_magic) != NILFS_SEGSUM_MAGIC)
		जाओ out;

	ret = NILFS_SEG_FAIL_SEQ;
	अगर (le64_to_cpu(sum->ss_seq) != seg_seq)
		जाओ out;

	nblock = le32_to_cpu(sum->ss_nblocks);
	ret = NILFS_SEG_FAIL_CONSISTENCY;
	अगर (unlikely(nblock == 0 || nblock > nilfs->ns_blocks_per_segment))
		/* This limits the number of blocks पढ़ो in the CRC check */
		जाओ out;

	ret = NILFS_SEG_FAIL_IO;
	अगर (nilfs_compute_checksum(nilfs, bh_sum, &crc, माप(sum->ss_datasum),
				   ((u64)nblock << nilfs->ns_blocksize_bits),
				   bh_sum->b_blocknr, nblock))
		जाओ out;

	ret = NILFS_SEG_FAIL_CHECKSUM_FULL;
	अगर (crc != le32_to_cpu(sum->ss_datasum))
		जाओ out;
	ret = 0;
out:
	वापस ret;
पूर्ण

/**
 * nilfs_पढ़ो_summary_info - पढ़ो an item on summary blocks of a log
 * @nilfs: nilfs object
 * @pbh: the current buffer head on summary blocks [in, out]
 * @offset: the current byte offset on summary blocks [in, out]
 * @bytes: byte size of the item to be पढ़ो
 */
अटल व्योम *nilfs_पढ़ो_summary_info(काष्ठा the_nilfs *nilfs,
				     काष्ठा buffer_head **pbh,
				     अचिन्हित पूर्णांक *offset, अचिन्हित पूर्णांक bytes)
अणु
	व्योम *ptr;
	sector_t blocknr;

	BUG_ON((*pbh)->b_size < *offset);
	अगर (bytes > (*pbh)->b_size - *offset) अणु
		blocknr = (*pbh)->b_blocknr;
		brअन्यथा(*pbh);
		*pbh = __bपढ़ो(nilfs->ns_bdev, blocknr + 1,
			       nilfs->ns_blocksize);
		अगर (unlikely(!*pbh))
			वापस शून्य;
		*offset = 0;
	पूर्ण
	ptr = (*pbh)->b_data + *offset;
	*offset += bytes;
	वापस ptr;
पूर्ण

/**
 * nilfs_skip_summary_info - skip items on summary blocks of a log
 * @nilfs: nilfs object
 * @pbh: the current buffer head on summary blocks [in, out]
 * @offset: the current byte offset on summary blocks [in, out]
 * @bytes: byte size of the item to be skipped
 * @count: number of items to be skipped
 */
अटल व्योम nilfs_skip_summary_info(काष्ठा the_nilfs *nilfs,
				    काष्ठा buffer_head **pbh,
				    अचिन्हित पूर्णांक *offset, अचिन्हित पूर्णांक bytes,
				    अचिन्हित दीर्घ count)
अणु
	अचिन्हित पूर्णांक rest_item_in_current_block
		= ((*pbh)->b_size - *offset) / bytes;

	अगर (count <= rest_item_in_current_block) अणु
		*offset += bytes * count;
	पूर्ण अन्यथा अणु
		sector_t blocknr = (*pbh)->b_blocknr;
		अचिन्हित पूर्णांक nitem_per_block = (*pbh)->b_size / bytes;
		अचिन्हित पूर्णांक bcnt;

		count -= rest_item_in_current_block;
		bcnt = DIV_ROUND_UP(count, nitem_per_block);
		*offset = bytes * (count - (bcnt - 1) * nitem_per_block);

		brअन्यथा(*pbh);
		*pbh = __bपढ़ो(nilfs->ns_bdev, blocknr + bcnt,
			       nilfs->ns_blocksize);
	पूर्ण
पूर्ण

/**
 * nilfs_scan_dsync_log - get block inक्रमmation of a log written क्रम data sync
 * @nilfs: nilfs object
 * @start_blocknr: start block number of the log
 * @sum: log summary inक्रमmation
 * @head: list head to add nilfs_recovery_block काष्ठा
 */
अटल पूर्णांक nilfs_scan_dsync_log(काष्ठा the_nilfs *nilfs, sector_t start_blocknr,
				काष्ठा nilfs_segment_summary *sum,
				काष्ठा list_head *head)
अणु
	काष्ठा buffer_head *bh;
	अचिन्हित पूर्णांक offset;
	u32 nfinfo, sumbytes;
	sector_t blocknr;
	ino_t ino;
	पूर्णांक err = -EIO;

	nfinfo = le32_to_cpu(sum->ss_nfinfo);
	अगर (!nfinfo)
		वापस 0;

	sumbytes = le32_to_cpu(sum->ss_sumbytes);
	blocknr = start_blocknr + DIV_ROUND_UP(sumbytes, nilfs->ns_blocksize);
	bh = __bपढ़ो(nilfs->ns_bdev, start_blocknr, nilfs->ns_blocksize);
	अगर (unlikely(!bh))
		जाओ out;

	offset = le16_to_cpu(sum->ss_bytes);
	क्रम (;;) अणु
		अचिन्हित दीर्घ nblocks, ndatablk, nnodeblk;
		काष्ठा nilfs_finfo *finfo;

		finfo = nilfs_पढ़ो_summary_info(nilfs, &bh, &offset,
						माप(*finfo));
		अगर (unlikely(!finfo))
			जाओ out;

		ino = le64_to_cpu(finfo->fi_ino);
		nblocks = le32_to_cpu(finfo->fi_nblocks);
		ndatablk = le32_to_cpu(finfo->fi_ndatablk);
		nnodeblk = nblocks - ndatablk;

		जबतक (ndatablk-- > 0) अणु
			काष्ठा nilfs_recovery_block *rb;
			काष्ठा nilfs_binfo_v *binfo;

			binfo = nilfs_पढ़ो_summary_info(nilfs, &bh, &offset,
							माप(*binfo));
			अगर (unlikely(!binfo))
				जाओ out;

			rb = kदो_स्मृति(माप(*rb), GFP_NOFS);
			अगर (unlikely(!rb)) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण
			rb->ino = ino;
			rb->blocknr = blocknr++;
			rb->vblocknr = le64_to_cpu(binfo->bi_vblocknr);
			rb->blkoff = le64_to_cpu(binfo->bi_blkoff);
			/* INIT_LIST_HEAD(&rb->list); */
			list_add_tail(&rb->list, head);
		पूर्ण
		अगर (--nfinfo == 0)
			अवरोध;
		blocknr += nnodeblk; /* always 0 क्रम data sync logs */
		nilfs_skip_summary_info(nilfs, &bh, &offset, माप(__le64),
					nnodeblk);
		अगर (unlikely(!bh))
			जाओ out;
	पूर्ण
	err = 0;
 out:
	brअन्यथा(bh);   /* brअन्यथा(शून्य) is just ignored */
	वापस err;
पूर्ण

अटल व्योम dispose_recovery_list(काष्ठा list_head *head)
अणु
	जबतक (!list_empty(head)) अणु
		काष्ठा nilfs_recovery_block *rb;

		rb = list_first_entry(head, काष्ठा nilfs_recovery_block, list);
		list_del(&rb->list);
		kमुक्त(rb);
	पूर्ण
पूर्ण

काष्ठा nilfs_segment_entry अणु
	काष्ठा list_head	list;
	__u64			segnum;
पूर्ण;

अटल पूर्णांक nilfs_segment_list_add(काष्ठा list_head *head, __u64 segnum)
अणु
	काष्ठा nilfs_segment_entry *ent = kदो_स्मृति(माप(*ent), GFP_NOFS);

	अगर (unlikely(!ent))
		वापस -ENOMEM;

	ent->segnum = segnum;
	INIT_LIST_HEAD(&ent->list);
	list_add_tail(&ent->list, head);
	वापस 0;
पूर्ण

व्योम nilfs_dispose_segment_list(काष्ठा list_head *head)
अणु
	जबतक (!list_empty(head)) अणु
		काष्ठा nilfs_segment_entry *ent;

		ent = list_first_entry(head, काष्ठा nilfs_segment_entry, list);
		list_del(&ent->list);
		kमुक्त(ent);
	पूर्ण
पूर्ण

अटल पूर्णांक nilfs_prepare_segment_क्रम_recovery(काष्ठा the_nilfs *nilfs,
					      काष्ठा super_block *sb,
					      काष्ठा nilfs_recovery_info *ri)
अणु
	काष्ठा list_head *head = &ri->ri_used_segments;
	काष्ठा nilfs_segment_entry *ent, *n;
	काष्ठा inode *sufile = nilfs->ns_sufile;
	__u64 segnum[4];
	पूर्णांक err;
	पूर्णांक i;

	segnum[0] = nilfs->ns_segnum;
	segnum[1] = nilfs->ns_nextnum;
	segnum[2] = ri->ri_segnum;
	segnum[3] = ri->ri_nextnum;

	/*
	 * Releasing the next segment of the latest super root.
	 * The next segment is invalidated by this recovery.
	 */
	err = nilfs_sufile_मुक्त(sufile, segnum[1]);
	अगर (unlikely(err))
		जाओ failed;

	क्रम (i = 1; i < 4; i++) अणु
		err = nilfs_segment_list_add(head, segnum[i]);
		अगर (unlikely(err))
			जाओ failed;
	पूर्ण

	/*
	 * Collecting segments written after the latest super root.
	 * These are marked dirty to aव्योम being पुनः_स्मृतिated in the next ग_लिखो.
	 */
	list_क्रम_each_entry_safe(ent, n, head, list) अणु
		अगर (ent->segnum != segnum[0]) अणु
			err = nilfs_sufile_scrap(sufile, ent->segnum);
			अगर (unlikely(err))
				जाओ failed;
		पूर्ण
		list_del(&ent->list);
		kमुक्त(ent);
	पूर्ण

	/* Allocate new segments क्रम recovery */
	err = nilfs_sufile_alloc(sufile, &segnum[0]);
	अगर (unlikely(err))
		जाओ failed;

	nilfs->ns_pseg_offset = 0;
	nilfs->ns_seg_seq = ri->ri_seq + 2;
	nilfs->ns_nextnum = nilfs->ns_segnum = segnum[0];

 failed:
	/* No need to recover sufile because it will be destroyed on error */
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_recovery_copy_block(काष्ठा the_nilfs *nilfs,
				     काष्ठा nilfs_recovery_block *rb,
				     काष्ठा page *page)
अणु
	काष्ठा buffer_head *bh_org;
	व्योम *kaddr;

	bh_org = __bपढ़ो(nilfs->ns_bdev, rb->blocknr, nilfs->ns_blocksize);
	अगर (unlikely(!bh_org))
		वापस -EIO;

	kaddr = kmap_atomic(page);
	स_नकल(kaddr + bh_offset(bh_org), bh_org->b_data, bh_org->b_size);
	kunmap_atomic(kaddr);
	brअन्यथा(bh_org);
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_recover_dsync_blocks(काष्ठा the_nilfs *nilfs,
				      काष्ठा super_block *sb,
				      काष्ठा nilfs_root *root,
				      काष्ठा list_head *head,
				      अचिन्हित दीर्घ *nr_salvaged_blocks)
अणु
	काष्ठा inode *inode;
	काष्ठा nilfs_recovery_block *rb, *n;
	अचिन्हित पूर्णांक blocksize = nilfs->ns_blocksize;
	काष्ठा page *page;
	loff_t pos;
	पूर्णांक err = 0, err2 = 0;

	list_क्रम_each_entry_safe(rb, n, head, list) अणु
		inode = nilfs_iget(sb, root, rb->ino);
		अगर (IS_ERR(inode)) अणु
			err = PTR_ERR(inode);
			inode = शून्य;
			जाओ failed_inode;
		पूर्ण

		pos = rb->blkoff << inode->i_blkbits;
		err = block_ग_लिखो_begin(inode->i_mapping, pos, blocksize,
					0, &page, nilfs_get_block);
		अगर (unlikely(err)) अणु
			loff_t isize = inode->i_size;

			अगर (pos + blocksize > isize)
				nilfs_ग_लिखो_failed(inode->i_mapping,
							pos + blocksize);
			जाओ failed_inode;
		पूर्ण

		err = nilfs_recovery_copy_block(nilfs, rb, page);
		अगर (unlikely(err))
			जाओ failed_page;

		err = nilfs_set_file_dirty(inode, 1);
		अगर (unlikely(err))
			जाओ failed_page;

		block_ग_लिखो_end(शून्य, inode->i_mapping, pos, blocksize,
				blocksize, page, शून्य);

		unlock_page(page);
		put_page(page);

		(*nr_salvaged_blocks)++;
		जाओ next;

 failed_page:
		unlock_page(page);
		put_page(page);

 failed_inode:
		nilfs_warn(sb,
			   "error %d recovering data block (ino=%lu, block-offset=%llu)",
			   err, (अचिन्हित दीर्घ)rb->ino,
			   (अचिन्हित दीर्घ दीर्घ)rb->blkoff);
		अगर (!err2)
			err2 = err;
 next:
		iput(inode); /* iput(शून्य) is just ignored */
		list_del_init(&rb->list);
		kमुक्त(rb);
	पूर्ण
	वापस err2;
पूर्ण

/**
 * nilfs_करो_roll_क्रमward - salvage logical segments newer than the latest
 * checkpoपूर्णांक
 * @nilfs: nilfs object
 * @sb: super block instance
 * @ri: poपूर्णांकer to a nilfs_recovery_info
 */
अटल पूर्णांक nilfs_करो_roll_क्रमward(काष्ठा the_nilfs *nilfs,
				 काष्ठा super_block *sb,
				 काष्ठा nilfs_root *root,
				 काष्ठा nilfs_recovery_info *ri)
अणु
	काष्ठा buffer_head *bh_sum = शून्य;
	काष्ठा nilfs_segment_summary *sum = शून्य;
	sector_t pseg_start;
	sector_t seg_start, seg_end;  /* Starting/ending DBN of full segment */
	अचिन्हित दीर्घ nsalvaged_blocks = 0;
	अचिन्हित पूर्णांक flags;
	u64 seg_seq;
	__u64 segnum, nextnum = 0;
	पूर्णांक empty_seg = 0;
	पूर्णांक err = 0, ret;
	LIST_HEAD(dsync_blocks);  /* list of data blocks to be recovered */
	क्रमागत अणु
		RF_INIT_ST,
		RF_DSYNC_ST,   /* scanning data-sync segments */
	पूर्ण;
	पूर्णांक state = RF_INIT_ST;

	pseg_start = ri->ri_lsegs_start;
	seg_seq = ri->ri_lsegs_start_seq;
	segnum = nilfs_get_segnum_of_block(nilfs, pseg_start);
	nilfs_get_segment_range(nilfs, segnum, &seg_start, &seg_end);

	जबतक (segnum != ri->ri_segnum || pseg_start <= ri->ri_pseg_start) अणु
		brअन्यथा(bh_sum);
		bh_sum = nilfs_पढ़ो_log_header(nilfs, pseg_start, &sum);
		अगर (!bh_sum) अणु
			err = -EIO;
			जाओ failed;
		पूर्ण

		ret = nilfs_validate_log(nilfs, seg_seq, bh_sum, sum);
		अगर (ret) अणु
			अगर (ret == NILFS_SEG_FAIL_IO) अणु
				err = -EIO;
				जाओ failed;
			पूर्ण
			जाओ strayed;
		पूर्ण

		flags = le16_to_cpu(sum->ss_flags);
		अगर (flags & NILFS_SS_SR)
			जाओ confused;

		/* Found a valid partial segment; करो recovery actions */
		nextnum = nilfs_get_segnum_of_block(nilfs,
						    le64_to_cpu(sum->ss_next));
		empty_seg = 0;
		nilfs->ns_स_समय = le64_to_cpu(sum->ss_create);
		अगर (!(flags & NILFS_SS_GC))
			nilfs->ns_nongc_स_समय = nilfs->ns_स_समय;

		चयन (state) अणु
		हाल RF_INIT_ST:
			अगर (!(flags & NILFS_SS_LOGBGN) ||
			    !(flags & NILFS_SS_SYNDT))
				जाओ try_next_pseg;
			state = RF_DSYNC_ST;
			fallthrough;
		हाल RF_DSYNC_ST:
			अगर (!(flags & NILFS_SS_SYNDT))
				जाओ confused;

			err = nilfs_scan_dsync_log(nilfs, pseg_start, sum,
						   &dsync_blocks);
			अगर (unlikely(err))
				जाओ failed;
			अगर (flags & NILFS_SS_LOGEND) अणु
				err = nilfs_recover_dsync_blocks(
					nilfs, sb, root, &dsync_blocks,
					&nsalvaged_blocks);
				अगर (unlikely(err))
					जाओ failed;
				state = RF_INIT_ST;
			पूर्ण
			अवरोध; /* Fall through to try_next_pseg */
		पूर्ण

 try_next_pseg:
		अगर (pseg_start == ri->ri_lsegs_end)
			अवरोध;
		pseg_start += le32_to_cpu(sum->ss_nblocks);
		अगर (pseg_start < seg_end)
			जारी;
		जाओ feed_segment;

 strayed:
		अगर (pseg_start == ri->ri_lsegs_end)
			अवरोध;

 feed_segment:
		/* Looking to the next full segment */
		अगर (empty_seg++)
			अवरोध;
		seg_seq++;
		segnum = nextnum;
		nilfs_get_segment_range(nilfs, segnum, &seg_start, &seg_end);
		pseg_start = seg_start;
	पूर्ण

	अगर (nsalvaged_blocks) अणु
		nilfs_info(sb, "salvaged %lu blocks", nsalvaged_blocks);
		ri->ri_need_recovery = NILFS_RECOVERY_ROLLFORWARD_DONE;
	पूर्ण
 out:
	brअन्यथा(bh_sum);
	dispose_recovery_list(&dsync_blocks);
	वापस err;

 confused:
	err = -EINVAL;
 failed:
	nilfs_err(sb,
		  "error %d roll-forwarding partial segment at blocknr = %llu",
		  err, (अचिन्हित दीर्घ दीर्घ)pseg_start);
	जाओ out;
पूर्ण

अटल व्योम nilfs_finish_roll_क्रमward(काष्ठा the_nilfs *nilfs,
				      काष्ठा nilfs_recovery_info *ri)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक err;

	अगर (nilfs_get_segnum_of_block(nilfs, ri->ri_lsegs_start) !=
	    nilfs_get_segnum_of_block(nilfs, ri->ri_super_root))
		वापस;

	bh = __getblk(nilfs->ns_bdev, ri->ri_lsegs_start, nilfs->ns_blocksize);
	BUG_ON(!bh);
	स_रखो(bh->b_data, 0, bh->b_size);
	set_buffer_dirty(bh);
	err = sync_dirty_buffer(bh);
	अगर (unlikely(err))
		nilfs_warn(nilfs->ns_sb,
			   "buffer sync write failed during post-cleaning of recovery.");
	brअन्यथा(bh);
पूर्ण

/**
 * nilfs_salvage_orphan_logs - salvage logs written after the latest checkpoपूर्णांक
 * @nilfs: nilfs object
 * @sb: super block instance
 * @ri: poपूर्णांकer to a nilfs_recovery_info काष्ठा to store search results.
 *
 * Return Value: On success, 0 is वापसed.  On error, one of the following
 * negative error code is वापसed.
 *
 * %-EINVAL - Inconsistent fileप्रणाली state.
 *
 * %-EIO - I/O error
 *
 * %-ENOSPC - No space left on device (only in a panic state).
 *
 * %-ERESTARTSYS - Interrupted.
 *
 * %-ENOMEM - Insufficient memory available.
 */
पूर्णांक nilfs_salvage_orphan_logs(काष्ठा the_nilfs *nilfs,
			      काष्ठा super_block *sb,
			      काष्ठा nilfs_recovery_info *ri)
अणु
	काष्ठा nilfs_root *root;
	पूर्णांक err;

	अगर (ri->ri_lsegs_start == 0 || ri->ri_lsegs_end == 0)
		वापस 0;

	err = nilfs_attach_checkpoपूर्णांक(sb, ri->ri_cno, true, &root);
	अगर (unlikely(err)) अणु
		nilfs_err(sb, "error %d loading the latest checkpoint", err);
		वापस err;
	पूर्ण

	err = nilfs_करो_roll_क्रमward(nilfs, sb, root, ri);
	अगर (unlikely(err))
		जाओ failed;

	अगर (ri->ri_need_recovery == NILFS_RECOVERY_ROLLFORWARD_DONE) अणु
		err = nilfs_prepare_segment_क्रम_recovery(nilfs, sb, ri);
		अगर (unlikely(err)) अणु
			nilfs_err(sb, "error %d preparing segment for recovery",
				  err);
			जाओ failed;
		पूर्ण

		err = nilfs_attach_log_ग_लिखोr(sb, root);
		अगर (unlikely(err))
			जाओ failed;

		set_nilfs_disजारीd(nilfs);
		err = nilfs_स्थिरruct_segment(sb);
		nilfs_detach_log_ग_लिखोr(sb);

		अगर (unlikely(err)) अणु
			nilfs_err(sb, "error %d writing segment for recovery",
				  err);
			जाओ failed;
		पूर्ण

		nilfs_finish_roll_क्रमward(nilfs, ri);
	पूर्ण

 failed:
	nilfs_put_root(root);
	वापस err;
पूर्ण

/**
 * nilfs_search_super_root - search the latest valid super root
 * @nilfs: the_nilfs
 * @ri: poपूर्णांकer to a nilfs_recovery_info काष्ठा to store search results.
 *
 * nilfs_search_super_root() looks क्रम the latest super-root from a partial
 * segment poपूर्णांकed by the superblock.  It sets up काष्ठा the_nilfs through
 * this search. It fills nilfs_recovery_info (ri) required क्रम recovery.
 *
 * Return Value: On success, 0 is वापसed.  On error, one of the following
 * negative error code is वापसed.
 *
 * %-EINVAL - No valid segment found
 *
 * %-EIO - I/O error
 *
 * %-ENOMEM - Insufficient memory available.
 */
पूर्णांक nilfs_search_super_root(काष्ठा the_nilfs *nilfs,
			    काष्ठा nilfs_recovery_info *ri)
अणु
	काष्ठा buffer_head *bh_sum = शून्य;
	काष्ठा nilfs_segment_summary *sum = शून्य;
	sector_t pseg_start, pseg_end, sr_pseg_start = 0;
	sector_t seg_start, seg_end; /* range of full segment (block number) */
	sector_t b, end;
	अचिन्हित दीर्घ nblocks;
	अचिन्हित पूर्णांक flags;
	u64 seg_seq;
	__u64 segnum, nextnum = 0;
	__u64 cno;
	LIST_HEAD(segments);
	पूर्णांक empty_seg = 0, scan_newer = 0;
	पूर्णांक ret;

	pseg_start = nilfs->ns_last_pseg;
	seg_seq = nilfs->ns_last_seq;
	cno = nilfs->ns_last_cno;
	segnum = nilfs_get_segnum_of_block(nilfs, pseg_start);

	/* Calculate range of segment */
	nilfs_get_segment_range(nilfs, segnum, &seg_start, &seg_end);

	/* Read ahead segment */
	b = seg_start;
	जबतक (b <= seg_end)
		__bपढ़ोahead(nilfs->ns_bdev, b++, nilfs->ns_blocksize);

	क्रम (;;) अणु
		brअन्यथा(bh_sum);
		ret = NILFS_SEG_FAIL_IO;
		bh_sum = nilfs_पढ़ो_log_header(nilfs, pseg_start, &sum);
		अगर (!bh_sum)
			जाओ failed;

		ret = nilfs_validate_log(nilfs, seg_seq, bh_sum, sum);
		अगर (ret) अणु
			अगर (ret == NILFS_SEG_FAIL_IO)
				जाओ failed;
			जाओ strayed;
		पूर्ण

		nblocks = le32_to_cpu(sum->ss_nblocks);
		pseg_end = pseg_start + nblocks - 1;
		अगर (unlikely(pseg_end > seg_end)) अणु
			ret = NILFS_SEG_FAIL_CONSISTENCY;
			जाओ strayed;
		पूर्ण

		/* A valid partial segment */
		ri->ri_pseg_start = pseg_start;
		ri->ri_seq = seg_seq;
		ri->ri_segnum = segnum;
		nextnum = nilfs_get_segnum_of_block(nilfs,
						    le64_to_cpu(sum->ss_next));
		ri->ri_nextnum = nextnum;
		empty_seg = 0;

		flags = le16_to_cpu(sum->ss_flags);
		अगर (!(flags & NILFS_SS_SR) && !scan_newer) अणु
			/*
			 * This will never happen because a superblock
			 * (last_segment) always poपूर्णांकs to a pseg with
			 * a super root.
			 */
			ret = NILFS_SEG_FAIL_CONSISTENCY;
			जाओ failed;
		पूर्ण

		अगर (pseg_start == seg_start) अणु
			nilfs_get_segment_range(nilfs, nextnum, &b, &end);
			जबतक (b <= end)
				__bपढ़ोahead(nilfs->ns_bdev, b++,
					     nilfs->ns_blocksize);
		पूर्ण
		अगर (!(flags & NILFS_SS_SR)) अणु
			अगर (!ri->ri_lsegs_start && (flags & NILFS_SS_LOGBGN)) अणु
				ri->ri_lsegs_start = pseg_start;
				ri->ri_lsegs_start_seq = seg_seq;
			पूर्ण
			अगर (flags & NILFS_SS_LOGEND)
				ri->ri_lsegs_end = pseg_start;
			जाओ try_next_pseg;
		पूर्ण

		/* A valid super root was found. */
		ri->ri_cno = cno++;
		ri->ri_super_root = pseg_end;
		ri->ri_lsegs_start = ri->ri_lsegs_end = 0;

		nilfs_dispose_segment_list(&segments);
		sr_pseg_start = pseg_start;
		nilfs->ns_pseg_offset = pseg_start + nblocks - seg_start;
		nilfs->ns_seg_seq = seg_seq;
		nilfs->ns_segnum = segnum;
		nilfs->ns_cno = cno;  /* nilfs->ns_cno = ri->ri_cno + 1 */
		nilfs->ns_स_समय = le64_to_cpu(sum->ss_create);
		nilfs->ns_nextnum = nextnum;

		अगर (scan_newer)
			ri->ri_need_recovery = NILFS_RECOVERY_SR_UPDATED;
		अन्यथा अणु
			अगर (nilfs->ns_mount_state & NILFS_VALID_FS)
				जाओ super_root_found;
			scan_newer = 1;
		पूर्ण

 try_next_pseg:
		/* Standing on a course, or met an inconsistent state */
		pseg_start += nblocks;
		अगर (pseg_start < seg_end)
			जारी;
		जाओ feed_segment;

 strayed:
		/* Off the trail */
		अगर (!scan_newer)
			/*
			 * This can happen अगर a checkpoपूर्णांक was written without
			 * barriers, or as a result of an I/O failure.
			 */
			जाओ failed;

 feed_segment:
		/* Looking to the next full segment */
		अगर (empty_seg++)
			जाओ super_root_found; /* found a valid super root */

		ret = nilfs_segment_list_add(&segments, segnum);
		अगर (unlikely(ret))
			जाओ failed;

		seg_seq++;
		segnum = nextnum;
		nilfs_get_segment_range(nilfs, segnum, &seg_start, &seg_end);
		pseg_start = seg_start;
	पूर्ण

 super_root_found:
	/* Updating poपूर्णांकers relating to the latest checkpoपूर्णांक */
	brअन्यथा(bh_sum);
	list_splice_tail(&segments, &ri->ri_used_segments);
	nilfs->ns_last_pseg = sr_pseg_start;
	nilfs->ns_last_seq = nilfs->ns_seg_seq;
	nilfs->ns_last_cno = ri->ri_cno;
	वापस 0;

 failed:
	brअन्यथा(bh_sum);
	nilfs_dispose_segment_list(&segments);
	वापस ret < 0 ? ret : nilfs_warn_segment_error(nilfs->ns_sb, ret);
पूर्ण
