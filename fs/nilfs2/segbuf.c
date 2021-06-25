<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * segbuf.c - NILFS segment buffer
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 *
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/crc32.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/slab.h>
#समावेश "page.h"
#समावेश "segbuf.h"


काष्ठा nilfs_ग_लिखो_info अणु
	काष्ठा the_nilfs       *nilfs;
	काष्ठा bio	       *bio;
	पूर्णांक			start, end; /* The region to be submitted */
	पूर्णांक			rest_blocks;
	पूर्णांक			max_pages;
	पूर्णांक			nr_vecs;
	sector_t		blocknr;
पूर्ण;

अटल पूर्णांक nilfs_segbuf_ग_लिखो(काष्ठा nilfs_segment_buffer *segbuf,
			      काष्ठा the_nilfs *nilfs);
अटल पूर्णांक nilfs_segbuf_रुको(काष्ठा nilfs_segment_buffer *segbuf);

काष्ठा nilfs_segment_buffer *nilfs_segbuf_new(काष्ठा super_block *sb)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;

	segbuf = kmem_cache_alloc(nilfs_segbuf_cachep, GFP_NOFS);
	अगर (unlikely(!segbuf))
		वापस शून्य;

	segbuf->sb_super = sb;
	INIT_LIST_HEAD(&segbuf->sb_list);
	INIT_LIST_HEAD(&segbuf->sb_segsum_buffers);
	INIT_LIST_HEAD(&segbuf->sb_payload_buffers);
	segbuf->sb_super_root = शून्य;

	init_completion(&segbuf->sb_bio_event);
	atomic_set(&segbuf->sb_err, 0);
	segbuf->sb_nbio = 0;

	वापस segbuf;
पूर्ण

व्योम nilfs_segbuf_मुक्त(काष्ठा nilfs_segment_buffer *segbuf)
अणु
	kmem_cache_मुक्त(nilfs_segbuf_cachep, segbuf);
पूर्ण

व्योम nilfs_segbuf_map(काष्ठा nilfs_segment_buffer *segbuf, __u64 segnum,
		     अचिन्हित दीर्घ offset, काष्ठा the_nilfs *nilfs)
अणु
	segbuf->sb_segnum = segnum;
	nilfs_get_segment_range(nilfs, segnum, &segbuf->sb_fseg_start,
				&segbuf->sb_fseg_end);

	segbuf->sb_pseg_start = segbuf->sb_fseg_start + offset;
	segbuf->sb_rest_blocks =
		segbuf->sb_fseg_end - segbuf->sb_pseg_start + 1;
पूर्ण

/**
 * nilfs_segbuf_map_cont - map a new log behind a given log
 * @segbuf: new segment buffer
 * @prev: segment buffer containing a log to be जारीd
 */
व्योम nilfs_segbuf_map_cont(काष्ठा nilfs_segment_buffer *segbuf,
			   काष्ठा nilfs_segment_buffer *prev)
अणु
	segbuf->sb_segnum = prev->sb_segnum;
	segbuf->sb_fseg_start = prev->sb_fseg_start;
	segbuf->sb_fseg_end = prev->sb_fseg_end;
	segbuf->sb_pseg_start = prev->sb_pseg_start + prev->sb_sum.nblocks;
	segbuf->sb_rest_blocks =
		segbuf->sb_fseg_end - segbuf->sb_pseg_start + 1;
पूर्ण

व्योम nilfs_segbuf_set_next_segnum(काष्ठा nilfs_segment_buffer *segbuf,
				  __u64 nextnum, काष्ठा the_nilfs *nilfs)
अणु
	segbuf->sb_nextnum = nextnum;
	segbuf->sb_sum.next = nilfs_get_segment_start_blocknr(nilfs, nextnum);
पूर्ण

पूर्णांक nilfs_segbuf_extend_segsum(काष्ठा nilfs_segment_buffer *segbuf)
अणु
	काष्ठा buffer_head *bh;

	bh = sb_getblk(segbuf->sb_super,
		       segbuf->sb_pseg_start + segbuf->sb_sum.nsumblk);
	अगर (unlikely(!bh))
		वापस -ENOMEM;

	nilfs_segbuf_add_segsum_buffer(segbuf, bh);
	वापस 0;
पूर्ण

पूर्णांक nilfs_segbuf_extend_payload(काष्ठा nilfs_segment_buffer *segbuf,
				काष्ठा buffer_head **bhp)
अणु
	काष्ठा buffer_head *bh;

	bh = sb_getblk(segbuf->sb_super,
		       segbuf->sb_pseg_start + segbuf->sb_sum.nblocks);
	अगर (unlikely(!bh))
		वापस -ENOMEM;

	nilfs_segbuf_add_payload_buffer(segbuf, bh);
	*bhp = bh;
	वापस 0;
पूर्ण

पूर्णांक nilfs_segbuf_reset(काष्ठा nilfs_segment_buffer *segbuf, अचिन्हित पूर्णांक flags,
		       समय64_t स_समय, __u64 cno)
अणु
	पूर्णांक err;

	segbuf->sb_sum.nblocks = segbuf->sb_sum.nsumblk = 0;
	err = nilfs_segbuf_extend_segsum(segbuf);
	अगर (unlikely(err))
		वापस err;

	segbuf->sb_sum.flags = flags;
	segbuf->sb_sum.sumbytes = माप(काष्ठा nilfs_segment_summary);
	segbuf->sb_sum.nfinfo = segbuf->sb_sum.nfileblk = 0;
	segbuf->sb_sum.स_समय = स_समय;
	segbuf->sb_sum.cno = cno;
	वापस 0;
पूर्ण

/*
 * Setup segment summary
 */
व्योम nilfs_segbuf_fill_in_segsum(काष्ठा nilfs_segment_buffer *segbuf)
अणु
	काष्ठा nilfs_segment_summary *raw_sum;
	काष्ठा buffer_head *bh_sum;

	bh_sum = list_entry(segbuf->sb_segsum_buffers.next,
			    काष्ठा buffer_head, b_assoc_buffers);
	raw_sum = (काष्ठा nilfs_segment_summary *)bh_sum->b_data;

	raw_sum->ss_magic    = cpu_to_le32(NILFS_SEGSUM_MAGIC);
	raw_sum->ss_bytes    = cpu_to_le16(माप(*raw_sum));
	raw_sum->ss_flags    = cpu_to_le16(segbuf->sb_sum.flags);
	raw_sum->ss_seq      = cpu_to_le64(segbuf->sb_sum.seg_seq);
	raw_sum->ss_create   = cpu_to_le64(segbuf->sb_sum.स_समय);
	raw_sum->ss_next     = cpu_to_le64(segbuf->sb_sum.next);
	raw_sum->ss_nblocks  = cpu_to_le32(segbuf->sb_sum.nblocks);
	raw_sum->ss_nfinfo   = cpu_to_le32(segbuf->sb_sum.nfinfo);
	raw_sum->ss_sumbytes = cpu_to_le32(segbuf->sb_sum.sumbytes);
	raw_sum->ss_pad      = 0;
	raw_sum->ss_cno      = cpu_to_le64(segbuf->sb_sum.cno);
पूर्ण

/*
 * CRC calculation routines
 */
अटल व्योम
nilfs_segbuf_fill_in_segsum_crc(काष्ठा nilfs_segment_buffer *segbuf, u32 seed)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_segment_summary *raw_sum;
	अचिन्हित दीर्घ size, bytes = segbuf->sb_sum.sumbytes;
	u32 crc;

	bh = list_entry(segbuf->sb_segsum_buffers.next, काष्ठा buffer_head,
			b_assoc_buffers);

	raw_sum = (काष्ठा nilfs_segment_summary *)bh->b_data;
	size = min_t(अचिन्हित दीर्घ, bytes, bh->b_size);
	crc = crc32_le(seed,
		       (अचिन्हित अक्षर *)raw_sum +
		       माप(raw_sum->ss_datasum) + माप(raw_sum->ss_sumsum),
		       size - (माप(raw_sum->ss_datasum) +
			       माप(raw_sum->ss_sumsum)));

	list_क्रम_each_entry_जारी(bh, &segbuf->sb_segsum_buffers,
				     b_assoc_buffers) अणु
		bytes -= size;
		size = min_t(अचिन्हित दीर्घ, bytes, bh->b_size);
		crc = crc32_le(crc, bh->b_data, size);
	पूर्ण
	raw_sum->ss_sumsum = cpu_to_le32(crc);
पूर्ण

अटल व्योम nilfs_segbuf_fill_in_data_crc(काष्ठा nilfs_segment_buffer *segbuf,
					  u32 seed)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_segment_summary *raw_sum;
	व्योम *kaddr;
	u32 crc;

	bh = list_entry(segbuf->sb_segsum_buffers.next, काष्ठा buffer_head,
			b_assoc_buffers);
	raw_sum = (काष्ठा nilfs_segment_summary *)bh->b_data;
	crc = crc32_le(seed,
		       (अचिन्हित अक्षर *)raw_sum + माप(raw_sum->ss_datasum),
		       bh->b_size - माप(raw_sum->ss_datasum));

	list_क्रम_each_entry_जारी(bh, &segbuf->sb_segsum_buffers,
				     b_assoc_buffers) अणु
		crc = crc32_le(crc, bh->b_data, bh->b_size);
	पूर्ण
	list_क्रम_each_entry(bh, &segbuf->sb_payload_buffers, b_assoc_buffers) अणु
		kaddr = kmap_atomic(bh->b_page);
		crc = crc32_le(crc, kaddr + bh_offset(bh), bh->b_size);
		kunmap_atomic(kaddr);
	पूर्ण
	raw_sum->ss_datasum = cpu_to_le32(crc);
पूर्ण

अटल व्योम
nilfs_segbuf_fill_in_super_root_crc(काष्ठा nilfs_segment_buffer *segbuf,
				    u32 seed)
अणु
	काष्ठा nilfs_super_root *raw_sr;
	काष्ठा the_nilfs *nilfs = segbuf->sb_super->s_fs_info;
	अचिन्हित पूर्णांक srsize;
	u32 crc;

	raw_sr = (काष्ठा nilfs_super_root *)segbuf->sb_super_root->b_data;
	srsize = NILFS_SR_BYTES(nilfs->ns_inode_size);
	crc = crc32_le(seed,
		       (अचिन्हित अक्षर *)raw_sr + माप(raw_sr->sr_sum),
		       srsize - माप(raw_sr->sr_sum));
	raw_sr->sr_sum = cpu_to_le32(crc);
पूर्ण

अटल व्योम nilfs_release_buffers(काष्ठा list_head *list)
अणु
	काष्ठा buffer_head *bh, *n;

	list_क्रम_each_entry_safe(bh, n, list, b_assoc_buffers) अणु
		list_del_init(&bh->b_assoc_buffers);
		brअन्यथा(bh);
	पूर्ण
पूर्ण

अटल व्योम nilfs_segbuf_clear(काष्ठा nilfs_segment_buffer *segbuf)
अणु
	nilfs_release_buffers(&segbuf->sb_segsum_buffers);
	nilfs_release_buffers(&segbuf->sb_payload_buffers);
	segbuf->sb_super_root = शून्य;
पूर्ण

/*
 * Iterators क्रम segment buffers
 */
व्योम nilfs_clear_logs(काष्ठा list_head *logs)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;

	list_क्रम_each_entry(segbuf, logs, sb_list)
		nilfs_segbuf_clear(segbuf);
पूर्ण

व्योम nilfs_truncate_logs(काष्ठा list_head *logs,
			 काष्ठा nilfs_segment_buffer *last)
अणु
	काष्ठा nilfs_segment_buffer *n, *segbuf;

	segbuf = list_prepare_entry(last, logs, sb_list);
	list_क्रम_each_entry_safe_जारी(segbuf, n, logs, sb_list) अणु
		list_del_init(&segbuf->sb_list);
		nilfs_segbuf_clear(segbuf);
		nilfs_segbuf_मुक्त(segbuf);
	पूर्ण
पूर्ण

पूर्णांक nilfs_ग_लिखो_logs(काष्ठा list_head *logs, काष्ठा the_nilfs *nilfs)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(segbuf, logs, sb_list) अणु
		ret = nilfs_segbuf_ग_लिखो(segbuf, nilfs);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक nilfs_रुको_on_logs(काष्ठा list_head *logs)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;
	पूर्णांक err, ret = 0;

	list_क्रम_each_entry(segbuf, logs, sb_list) अणु
		err = nilfs_segbuf_रुको(segbuf);
		अगर (err && !ret)
			ret = err;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nilfs_add_checksums_on_logs - add checksums on the logs
 * @logs: list of segment buffers storing target logs
 * @seed: checksum seed value
 */
व्योम nilfs_add_checksums_on_logs(काष्ठा list_head *logs, u32 seed)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;

	list_क्रम_each_entry(segbuf, logs, sb_list) अणु
		अगर (segbuf->sb_super_root)
			nilfs_segbuf_fill_in_super_root_crc(segbuf, seed);
		nilfs_segbuf_fill_in_segsum_crc(segbuf, seed);
		nilfs_segbuf_fill_in_data_crc(segbuf, seed);
	पूर्ण
पूर्ण

/*
 * BIO operations
 */
अटल व्योम nilfs_end_bio_ग_लिखो(काष्ठा bio *bio)
अणु
	काष्ठा nilfs_segment_buffer *segbuf = bio->bi_निजी;

	अगर (bio->bi_status)
		atomic_inc(&segbuf->sb_err);

	bio_put(bio);
	complete(&segbuf->sb_bio_event);
पूर्ण

अटल पूर्णांक nilfs_segbuf_submit_bio(काष्ठा nilfs_segment_buffer *segbuf,
				   काष्ठा nilfs_ग_लिखो_info *wi, पूर्णांक mode,
				   पूर्णांक mode_flags)
अणु
	काष्ठा bio *bio = wi->bio;
	पूर्णांक err;

	अगर (segbuf->sb_nbio > 0 &&
	    bdi_ग_लिखो_congested(segbuf->sb_super->s_bdi)) अणु
		रुको_क्रम_completion(&segbuf->sb_bio_event);
		segbuf->sb_nbio--;
		अगर (unlikely(atomic_पढ़ो(&segbuf->sb_err))) अणु
			bio_put(bio);
			err = -EIO;
			जाओ failed;
		पूर्ण
	पूर्ण

	bio->bi_end_io = nilfs_end_bio_ग_लिखो;
	bio->bi_निजी = segbuf;
	bio_set_op_attrs(bio, mode, mode_flags);
	submit_bio(bio);
	segbuf->sb_nbio++;

	wi->bio = शून्य;
	wi->rest_blocks -= wi->end - wi->start;
	wi->nr_vecs = min(wi->max_pages, wi->rest_blocks);
	wi->start = wi->end;
	वापस 0;

 failed:
	wi->bio = शून्य;
	वापस err;
पूर्ण

/**
 * nilfs_alloc_seg_bio - allocate a new bio क्रम writing log
 * @nilfs: nilfs object
 * @start: start block number of the bio
 * @nr_vecs: request size of page vector.
 *
 * Return Value: On success, poपूर्णांकer to the काष्ठा bio is वापसed.
 * On error, शून्य is वापसed.
 */
अटल काष्ठा bio *nilfs_alloc_seg_bio(काष्ठा the_nilfs *nilfs, sector_t start,
				       पूर्णांक nr_vecs)
अणु
	काष्ठा bio *bio;

	bio = bio_alloc(GFP_NOIO, nr_vecs);
	अगर (likely(bio)) अणु
		bio_set_dev(bio, nilfs->ns_bdev);
		bio->bi_iter.bi_sector =
			start << (nilfs->ns_blocksize_bits - 9);
	पूर्ण
	वापस bio;
पूर्ण

अटल व्योम nilfs_segbuf_prepare_ग_लिखो(काष्ठा nilfs_segment_buffer *segbuf,
				       काष्ठा nilfs_ग_लिखो_info *wi)
अणु
	wi->bio = शून्य;
	wi->rest_blocks = segbuf->sb_sum.nblocks;
	wi->max_pages = BIO_MAX_VECS;
	wi->nr_vecs = min(wi->max_pages, wi->rest_blocks);
	wi->start = wi->end = 0;
	wi->blocknr = segbuf->sb_pseg_start;
पूर्ण

अटल पूर्णांक nilfs_segbuf_submit_bh(काष्ठा nilfs_segment_buffer *segbuf,
				  काष्ठा nilfs_ग_लिखो_info *wi,
				  काष्ठा buffer_head *bh, पूर्णांक mode)
अणु
	पूर्णांक len, err;

	BUG_ON(wi->nr_vecs <= 0);
 repeat:
	अगर (!wi->bio) अणु
		wi->bio = nilfs_alloc_seg_bio(wi->nilfs, wi->blocknr + wi->end,
					      wi->nr_vecs);
		अगर (unlikely(!wi->bio))
			वापस -ENOMEM;
	पूर्ण

	len = bio_add_page(wi->bio, bh->b_page, bh->b_size, bh_offset(bh));
	अगर (len == bh->b_size) अणु
		wi->end++;
		वापस 0;
	पूर्ण
	/* bio is FULL */
	err = nilfs_segbuf_submit_bio(segbuf, wi, mode, 0);
	/* never submit current bh */
	अगर (likely(!err))
		जाओ repeat;
	वापस err;
पूर्ण

/**
 * nilfs_segbuf_ग_लिखो - submit ग_लिखो requests of a log
 * @segbuf: buffer storing a log to be written
 * @nilfs: nilfs object
 *
 * Return Value: On Success, 0 is वापसed. On Error, one of the following
 * negative error code is वापसed.
 *
 * %-EIO - I/O error
 *
 * %-ENOMEM - Insufficient memory available.
 */
अटल पूर्णांक nilfs_segbuf_ग_लिखो(काष्ठा nilfs_segment_buffer *segbuf,
			      काष्ठा the_nilfs *nilfs)
अणु
	काष्ठा nilfs_ग_लिखो_info wi;
	काष्ठा buffer_head *bh;
	पूर्णांक res = 0;

	wi.nilfs = nilfs;
	nilfs_segbuf_prepare_ग_लिखो(segbuf, &wi);

	list_क्रम_each_entry(bh, &segbuf->sb_segsum_buffers, b_assoc_buffers) अणु
		res = nilfs_segbuf_submit_bh(segbuf, &wi, bh, REQ_OP_WRITE);
		अगर (unlikely(res))
			जाओ failed_bio;
	पूर्ण

	list_क्रम_each_entry(bh, &segbuf->sb_payload_buffers, b_assoc_buffers) अणु
		res = nilfs_segbuf_submit_bh(segbuf, &wi, bh, REQ_OP_WRITE);
		अगर (unlikely(res))
			जाओ failed_bio;
	पूर्ण

	अगर (wi.bio) अणु
		/*
		 * Last BIO is always sent through the following
		 * submission.
		 */
		res = nilfs_segbuf_submit_bio(segbuf, &wi, REQ_OP_WRITE,
					      REQ_SYNC);
	पूर्ण

 failed_bio:
	वापस res;
पूर्ण

/**
 * nilfs_segbuf_रुको - रुको क्रम completion of requested BIOs
 * @segbuf: segment buffer
 *
 * Return Value: On Success, 0 is वापसed. On Error, one of the following
 * negative error code is वापसed.
 *
 * %-EIO - I/O error
 */
अटल पूर्णांक nilfs_segbuf_रुको(काष्ठा nilfs_segment_buffer *segbuf)
अणु
	पूर्णांक err = 0;

	अगर (!segbuf->sb_nbio)
		वापस 0;

	करो अणु
		रुको_क्रम_completion(&segbuf->sb_bio_event);
	पूर्ण जबतक (--segbuf->sb_nbio > 0);

	अगर (unlikely(atomic_पढ़ो(&segbuf->sb_err) > 0)) अणु
		nilfs_err(segbuf->sb_super,
			  "I/O error writing log (start-blocknr=%llu, block-count=%lu) in segment %llu",
			  (अचिन्हित दीर्घ दीर्घ)segbuf->sb_pseg_start,
			  segbuf->sb_sum.nblocks,
			  (अचिन्हित दीर्घ दीर्घ)segbuf->sb_segnum);
		err = -EIO;
	पूर्ण
	वापस err;
पूर्ण
