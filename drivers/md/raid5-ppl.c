<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Partial Parity Log क्रम closing the RAID5 ग_लिखो hole
 * Copyright (c) 2017, Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/async_tx.h>
#समावेश <linux/raid/md_p.h>
#समावेश "md.h"
#समावेश "raid5.h"
#समावेश "raid5-log.h"

/*
 * PPL consists of a 4KB header (काष्ठा ppl_header) and at least 128KB क्रम
 * partial parity data. The header contains an array of entries
 * (काष्ठा ppl_header_entry) which describe the logged ग_लिखो requests.
 * Partial parity क्रम the entries comes after the header, written in the same
 * sequence as the entries:
 *
 * Header
 *   entry0
 *   ...
 *   entryN
 * PP data
 *   PP क्रम entry0
 *   ...
 *   PP क्रम entryN
 *
 * An entry describes one or more consecutive stripe_heads, up to a full
 * stripe. The modअगरed raid data chunks क्रमm an m-by-n matrix, where m is the
 * number of stripe_heads in the entry and n is the number of modअगरied data
 * disks. Every stripe_head in the entry must ग_लिखो to the same data disks.
 * An example of a valid हाल described by a single entry (ग_लिखोs to the first
 * stripe of a 4 disk array, 16k chunk size):
 *
 * sh->sector   dd0   dd1   dd2    ppl
 *            +-----+-----+-----+
 * 0          | --- | --- | --- | +----+
 * 8          | -W- | -W- | --- | | pp |   data_sector = 8
 * 16         | -W- | -W- | --- | | pp |   data_size = 3 * 2 * 4k
 * 24         | -W- | -W- | --- | | pp |   pp_size = 3 * 4k
 *            +-----+-----+-----+ +----+
 *
 * data_sector is the first raid sector of the modअगरied data, data_size is the
 * total size of modअगरied data and pp_size is the size of partial parity क्रम
 * this entry. Entries क्रम full stripe ग_लिखोs contain no partial parity
 * (pp_size = 0), they only mark the stripes क्रम which parity should be
 * recalculated after an unclean shutकरोwn. Every entry holds a checksum of its
 * partial parity, the header also has a checksum of the header itself.
 *
 * A ग_लिखो request is always logged to the PPL instance stored on the parity
 * disk of the corresponding stripe. For each member disk there is one ppl_log
 * used to handle logging क्रम this disk, independently from others. They are
 * grouped in child_logs array in काष्ठा ppl_conf, which is asचिन्हित to
 * r5conf->log_निजी.
 *
 * ppl_io_unit represents a full PPL ग_लिखो, header_page contains the ppl_header.
 * PPL entries क्रम logged stripes are added in ppl_log_stripe(). A stripe_head
 * can be appended to the last entry अगर it meets the conditions क्रम a valid
 * entry described above, otherwise a new entry is added. Checksums of entries
 * are calculated incrementally as stripes containing partial parity are being
 * added. ppl_submit_iounit() calculates the checksum of the header and submits
 * a bio containing the header page and partial parity pages (sh->ppl_page) क्रम
 * all stripes of the io_unit. When the PPL ग_लिखो completes, the stripes
 * associated with the io_unit are released and raid5d starts writing their data
 * and parity. When all stripes are written, the io_unit is मुक्तd and the next
 * can be submitted.
 *
 * An io_unit is used to gather stripes until it is submitted or becomes full
 * (अगर the maximum number of entries or size of PPL is reached). Another io_unit
 * can't be submitted until the previous has completed (PPL and stripe
 * data+parity is written). The log->io_list tracks all io_units of a log
 * (क्रम a single member disk). New io_units are added to the end of the list
 * and the first io_unit is submitted, अगर it is not submitted alपढ़ोy.
 * The current io_unit accepting new stripes is always at the end of the list.
 *
 * If ग_लिखो-back cache is enabled क्रम any of the disks in the array, its data
 * must be flushed beक्रमe next io_unit is submitted.
 */

#घोषणा PPL_SPACE_SIZE (128 * 1024)

काष्ठा ppl_conf अणु
	काष्ठा mddev *mddev;

	/* array of child logs, one क्रम each raid disk */
	काष्ठा ppl_log *child_logs;
	पूर्णांक count;

	पूर्णांक block_size;		/* the logical block size used क्रम data_sector
				 * in ppl_header_entry */
	u32 signature;		/* raid array identअगरier */
	atomic64_t seq;		/* current log ग_लिखो sequence number */

	काष्ठा kmem_cache *io_kc;
	mempool_t io_pool;
	काष्ठा bio_set bs;
	काष्ठा bio_set flush_bs;

	/* used only क्रम recovery */
	पूर्णांक recovered_entries;
	पूर्णांक mismatch_count;

	/* stripes to retry अगर failed to allocate io_unit */
	काष्ठा list_head no_mem_stripes;
	spinlock_t no_mem_stripes_lock;

	अचिन्हित लघु ग_लिखो_hपूर्णांक;
पूर्ण;

काष्ठा ppl_log अणु
	काष्ठा ppl_conf *ppl_conf;	/* shared between all log instances */

	काष्ठा md_rdev *rdev;		/* array member disk associated with
					 * this log instance */
	काष्ठा mutex io_mutex;
	काष्ठा ppl_io_unit *current_io;	/* current io_unit accepting new data
					 * always at the end of io_list */
	spinlock_t io_list_lock;
	काष्ठा list_head io_list;	/* all io_units of this log */

	sector_t next_io_sector;
	अचिन्हित पूर्णांक entry_space;
	bool use_multippl;
	bool wb_cache_on;
	अचिन्हित दीर्घ disk_flush_biपंचांगap;
पूर्ण;

#घोषणा PPL_IO_INLINE_BVECS 32

काष्ठा ppl_io_unit अणु
	काष्ठा ppl_log *log;

	काष्ठा page *header_page;	/* क्रम ppl_header */

	अचिन्हित पूर्णांक entries_count;	/* number of entries in ppl_header */
	अचिन्हित पूर्णांक pp_size;		/* total size current of partial parity */

	u64 seq;			/* sequence number of this log ग_लिखो */
	काष्ठा list_head log_sibling;	/* log->io_list */

	काष्ठा list_head stripe_list;	/* stripes added to the io_unit */
	atomic_t pending_stripes;	/* how many stripes not written to raid */
	atomic_t pending_flushes;	/* how many disk flushes are in progress */

	bool submitted;			/* true अगर ग_लिखो to log started */

	/* अंतरभूत bio and its biovec क्रम submitting the iounit */
	काष्ठा bio bio;
	काष्ठा bio_vec biovec[PPL_IO_INLINE_BVECS];
पूर्ण;

काष्ठा dma_async_tx_descriptor *
ops_run_partial_parity(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu,
		       काष्ठा dma_async_tx_descriptor *tx)
अणु
	पूर्णांक disks = sh->disks;
	काष्ठा page **srcs = percpu->scribble;
	पूर्णांक count = 0, pd_idx = sh->pd_idx, i;
	काष्ठा async_submit_ctl submit;

	pr_debug("%s: stripe %llu\n", __func__, (अचिन्हित दीर्घ दीर्घ)sh->sector);

	/*
	 * Partial parity is the XOR of stripe data chunks that are not changed
	 * during the ग_लिखो request. Depending on available data
	 * (पढ़ो-modअगरy-ग_लिखो vs. reस्थिरruct-ग_लिखो हाल) we calculate it
	 * dअगरferently.
	 */
	अगर (sh->reस्थिरruct_state == reस्थिरruct_state_prexor_drain_run) अणु
		/*
		 * rmw: xor old data and parity from updated disks
		 * This is calculated earlier by ops_run_prexor5() so just copy
		 * the parity dev page.
		 */
		srcs[count++] = sh->dev[pd_idx].page;
	पूर्ण अन्यथा अगर (sh->reस्थिरruct_state == reस्थिरruct_state_drain_run) अणु
		/* rcw: xor data from all not updated disks */
		क्रम (i = disks; i--;) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (test_bit(R5_UPTODATE, &dev->flags))
				srcs[count++] = dev->page;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस tx;
	पूर्ण

	init_async_submit(&submit, ASYNC_TX_FENCE|ASYNC_TX_XOR_ZERO_DST, tx,
			  शून्य, sh, (व्योम *) (srcs + sh->disks + 2));

	अगर (count == 1)
		tx = async_स_नकल(sh->ppl_page, srcs[0], 0, 0, PAGE_SIZE,
				  &submit);
	अन्यथा
		tx = async_xor(sh->ppl_page, srcs, 0, count, PAGE_SIZE,
			       &submit);

	वापस tx;
पूर्ण

अटल व्योम *ppl_io_pool_alloc(gfp_t gfp_mask, व्योम *pool_data)
अणु
	काष्ठा kmem_cache *kc = pool_data;
	काष्ठा ppl_io_unit *io;

	io = kmem_cache_alloc(kc, gfp_mask);
	अगर (!io)
		वापस शून्य;

	io->header_page = alloc_page(gfp_mask);
	अगर (!io->header_page) अणु
		kmem_cache_मुक्त(kc, io);
		वापस शून्य;
	पूर्ण

	वापस io;
पूर्ण

अटल व्योम ppl_io_pool_मुक्त(व्योम *element, व्योम *pool_data)
अणु
	काष्ठा kmem_cache *kc = pool_data;
	काष्ठा ppl_io_unit *io = element;

	__मुक्त_page(io->header_page);
	kmem_cache_मुक्त(kc, io);
पूर्ण

अटल काष्ठा ppl_io_unit *ppl_new_iounit(काष्ठा ppl_log *log,
					  काष्ठा stripe_head *sh)
अणु
	काष्ठा ppl_conf *ppl_conf = log->ppl_conf;
	काष्ठा ppl_io_unit *io;
	काष्ठा ppl_header *pplhdr;
	काष्ठा page *header_page;

	io = mempool_alloc(&ppl_conf->io_pool, GFP_NOWAIT);
	अगर (!io)
		वापस शून्य;

	header_page = io->header_page;
	स_रखो(io, 0, माप(*io));
	io->header_page = header_page;

	io->log = log;
	INIT_LIST_HEAD(&io->log_sibling);
	INIT_LIST_HEAD(&io->stripe_list);
	atomic_set(&io->pending_stripes, 0);
	atomic_set(&io->pending_flushes, 0);
	bio_init(&io->bio, io->biovec, PPL_IO_INLINE_BVECS);

	pplhdr = page_address(io->header_page);
	clear_page(pplhdr);
	स_रखो(pplhdr->reserved, 0xff, PPL_HDR_RESERVED);
	pplhdr->signature = cpu_to_le32(ppl_conf->signature);

	io->seq = atomic64_add_वापस(1, &ppl_conf->seq);
	pplhdr->generation = cpu_to_le64(io->seq);

	वापस io;
पूर्ण

अटल पूर्णांक ppl_log_stripe(काष्ठा ppl_log *log, काष्ठा stripe_head *sh)
अणु
	काष्ठा ppl_io_unit *io = log->current_io;
	काष्ठा ppl_header_entry *e = शून्य;
	काष्ठा ppl_header *pplhdr;
	पूर्णांक i;
	sector_t data_sector = 0;
	पूर्णांक data_disks = 0;
	काष्ठा r5conf *conf = sh->raid_conf;

	pr_debug("%s: stripe: %llu\n", __func__, (अचिन्हित दीर्घ दीर्घ)sh->sector);

	/* check अगर current io_unit is full */
	अगर (io && (io->pp_size == log->entry_space ||
		   io->entries_count == PPL_HDR_MAX_ENTRIES)) अणु
		pr_debug("%s: add io_unit blocked by seq: %llu\n",
			 __func__, io->seq);
		io = शून्य;
	पूर्ण

	/* add a new unit अगर there is none or the current is full */
	अगर (!io) अणु
		io = ppl_new_iounit(log, sh);
		अगर (!io)
			वापस -ENOMEM;
		spin_lock_irq(&log->io_list_lock);
		list_add_tail(&io->log_sibling, &log->io_list);
		spin_unlock_irq(&log->io_list_lock);

		log->current_io = io;
	पूर्ण

	क्रम (i = 0; i < sh->disks; i++) अणु
		काष्ठा r5dev *dev = &sh->dev[i];

		अगर (i != sh->pd_idx && test_bit(R5_Wantग_लिखो, &dev->flags)) अणु
			अगर (!data_disks || dev->sector < data_sector)
				data_sector = dev->sector;
			data_disks++;
		पूर्ण
	पूर्ण
	BUG_ON(!data_disks);

	pr_debug("%s: seq: %llu data_sector: %llu data_disks: %d\n", __func__,
		 io->seq, (अचिन्हित दीर्घ दीर्घ)data_sector, data_disks);

	pplhdr = page_address(io->header_page);

	अगर (io->entries_count > 0) अणु
		काष्ठा ppl_header_entry *last =
				&pplhdr->entries[io->entries_count - 1];
		काष्ठा stripe_head *sh_last = list_last_entry(
				&io->stripe_list, काष्ठा stripe_head, log_list);
		u64 data_sector_last = le64_to_cpu(last->data_sector);
		u32 data_size_last = le32_to_cpu(last->data_size);

		/*
		 * Check अगर we can append the stripe to the last entry. It must
		 * be just after the last logged stripe and ग_लिखो to the same
		 * disks. Use bit shअगरt and logarithm to aव्योम 64-bit भागision.
		 */
		अगर ((sh->sector == sh_last->sector + RAID5_STRIPE_SECTORS(conf)) &&
		    (data_sector >> ilog2(conf->chunk_sectors) ==
		     data_sector_last >> ilog2(conf->chunk_sectors)) &&
		    ((data_sector - data_sector_last) * data_disks ==
		     data_size_last >> 9))
			e = last;
	पूर्ण

	अगर (!e) अणु
		e = &pplhdr->entries[io->entries_count++];
		e->data_sector = cpu_to_le64(data_sector);
		e->parity_disk = cpu_to_le32(sh->pd_idx);
		e->checksum = cpu_to_le32(~0);
	पूर्ण

	le32_add_cpu(&e->data_size, data_disks << PAGE_SHIFT);

	/* करोn't ग_लिखो any PP अगर full stripe ग_लिखो */
	अगर (!test_bit(STRIPE_FULL_WRITE, &sh->state)) अणु
		le32_add_cpu(&e->pp_size, PAGE_SIZE);
		io->pp_size += PAGE_SIZE;
		e->checksum = cpu_to_le32(crc32c_le(le32_to_cpu(e->checksum),
						    page_address(sh->ppl_page),
						    PAGE_SIZE));
	पूर्ण

	list_add_tail(&sh->log_list, &io->stripe_list);
	atomic_inc(&io->pending_stripes);
	sh->ppl_io = io;

	वापस 0;
पूर्ण

पूर्णांक ppl_ग_लिखो_stripe(काष्ठा r5conf *conf, काष्ठा stripe_head *sh)
अणु
	काष्ठा ppl_conf *ppl_conf = conf->log_निजी;
	काष्ठा ppl_io_unit *io = sh->ppl_io;
	काष्ठा ppl_log *log;

	अगर (io || test_bit(STRIPE_SYNCING, &sh->state) || !sh->ppl_page ||
	    !test_bit(R5_Wantग_लिखो, &sh->dev[sh->pd_idx].flags) ||
	    !test_bit(R5_Insync, &sh->dev[sh->pd_idx].flags)) अणु
		clear_bit(STRIPE_LOG_TRAPPED, &sh->state);
		वापस -EAGAIN;
	पूर्ण

	log = &ppl_conf->child_logs[sh->pd_idx];

	mutex_lock(&log->io_mutex);

	अगर (!log->rdev || test_bit(Faulty, &log->rdev->flags)) अणु
		mutex_unlock(&log->io_mutex);
		वापस -EAGAIN;
	पूर्ण

	set_bit(STRIPE_LOG_TRAPPED, &sh->state);
	clear_bit(STRIPE_DELAYED, &sh->state);
	atomic_inc(&sh->count);

	अगर (ppl_log_stripe(log, sh)) अणु
		spin_lock_irq(&ppl_conf->no_mem_stripes_lock);
		list_add_tail(&sh->log_list, &ppl_conf->no_mem_stripes);
		spin_unlock_irq(&ppl_conf->no_mem_stripes_lock);
	पूर्ण

	mutex_unlock(&log->io_mutex);

	वापस 0;
पूर्ण

अटल व्योम ppl_log_endio(काष्ठा bio *bio)
अणु
	काष्ठा ppl_io_unit *io = bio->bi_निजी;
	काष्ठा ppl_log *log = io->log;
	काष्ठा ppl_conf *ppl_conf = log->ppl_conf;
	काष्ठा stripe_head *sh, *next;

	pr_debug("%s: seq: %llu\n", __func__, io->seq);

	अगर (bio->bi_status)
		md_error(ppl_conf->mddev, log->rdev);

	list_क्रम_each_entry_safe(sh, next, &io->stripe_list, log_list) अणु
		list_del_init(&sh->log_list);

		set_bit(STRIPE_HANDLE, &sh->state);
		raid5_release_stripe(sh);
	पूर्ण
पूर्ण

अटल व्योम ppl_submit_iounit_bio(काष्ठा ppl_io_unit *io, काष्ठा bio *bio)
अणु
	अक्षर b[BDEVNAME_SIZE];

	pr_debug("%s: seq: %llu size: %u sector: %llu dev: %s\n",
		 __func__, io->seq, bio->bi_iter.bi_size,
		 (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector,
		 bio_devname(bio, b));

	submit_bio(bio);
पूर्ण

अटल व्योम ppl_submit_iounit(काष्ठा ppl_io_unit *io)
अणु
	काष्ठा ppl_log *log = io->log;
	काष्ठा ppl_conf *ppl_conf = log->ppl_conf;
	काष्ठा ppl_header *pplhdr = page_address(io->header_page);
	काष्ठा bio *bio = &io->bio;
	काष्ठा stripe_head *sh;
	पूर्णांक i;

	bio->bi_निजी = io;

	अगर (!log->rdev || test_bit(Faulty, &log->rdev->flags)) अणु
		ppl_log_endio(bio);
		वापस;
	पूर्ण

	क्रम (i = 0; i < io->entries_count; i++) अणु
		काष्ठा ppl_header_entry *e = &pplhdr->entries[i];

		pr_debug("%s: seq: %llu entry: %d data_sector: %llu pp_size: %u data_size: %u\n",
			 __func__, io->seq, i, le64_to_cpu(e->data_sector),
			 le32_to_cpu(e->pp_size), le32_to_cpu(e->data_size));

		e->data_sector = cpu_to_le64(le64_to_cpu(e->data_sector) >>
					     ilog2(ppl_conf->block_size >> 9));
		e->checksum = cpu_to_le32(~le32_to_cpu(e->checksum));
	पूर्ण

	pplhdr->entries_count = cpu_to_le32(io->entries_count);
	pplhdr->checksum = cpu_to_le32(~crc32c_le(~0, pplhdr, PPL_HEADER_SIZE));

	/* Rewind the buffer अगर current PPL is larger then reमुख्यing space */
	अगर (log->use_multippl &&
	    log->rdev->ppl.sector + log->rdev->ppl.size - log->next_io_sector <
	    (PPL_HEADER_SIZE + io->pp_size) >> 9)
		log->next_io_sector = log->rdev->ppl.sector;


	bio->bi_end_io = ppl_log_endio;
	bio->bi_opf = REQ_OP_WRITE | REQ_FUA;
	bio_set_dev(bio, log->rdev->bdev);
	bio->bi_iter.bi_sector = log->next_io_sector;
	bio_add_page(bio, io->header_page, PAGE_SIZE, 0);
	bio->bi_ग_लिखो_hपूर्णांक = ppl_conf->ग_लिखो_hपूर्णांक;

	pr_debug("%s: log->current_io_sector: %llu\n", __func__,
	    (अचिन्हित दीर्घ दीर्घ)log->next_io_sector);

	अगर (log->use_multippl)
		log->next_io_sector += (PPL_HEADER_SIZE + io->pp_size) >> 9;

	WARN_ON(log->disk_flush_biपंचांगap != 0);

	list_क्रम_each_entry(sh, &io->stripe_list, log_list) अणु
		क्रम (i = 0; i < sh->disks; i++) अणु
			काष्ठा r5dev *dev = &sh->dev[i];

			अगर ((ppl_conf->child_logs[i].wb_cache_on) &&
			    (test_bit(R5_Wantग_लिखो, &dev->flags))) अणु
				set_bit(i, &log->disk_flush_biपंचांगap);
			पूर्ण
		पूर्ण

		/* entries क्रम full stripe ग_लिखोs have no partial parity */
		अगर (test_bit(STRIPE_FULL_WRITE, &sh->state))
			जारी;

		अगर (!bio_add_page(bio, sh->ppl_page, PAGE_SIZE, 0)) अणु
			काष्ठा bio *prev = bio;

			bio = bio_alloc_bioset(GFP_NOIO, BIO_MAX_VECS,
					       &ppl_conf->bs);
			bio->bi_opf = prev->bi_opf;
			bio->bi_ग_लिखो_hपूर्णांक = prev->bi_ग_लिखो_hपूर्णांक;
			bio_copy_dev(bio, prev);
			bio->bi_iter.bi_sector = bio_end_sector(prev);
			bio_add_page(bio, sh->ppl_page, PAGE_SIZE, 0);

			bio_chain(bio, prev);
			ppl_submit_iounit_bio(io, prev);
		पूर्ण
	पूर्ण

	ppl_submit_iounit_bio(io, bio);
पूर्ण

अटल व्योम ppl_submit_current_io(काष्ठा ppl_log *log)
अणु
	काष्ठा ppl_io_unit *io;

	spin_lock_irq(&log->io_list_lock);

	io = list_first_entry_or_null(&log->io_list, काष्ठा ppl_io_unit,
				      log_sibling);
	अगर (io && io->submitted)
		io = शून्य;

	spin_unlock_irq(&log->io_list_lock);

	अगर (io) अणु
		io->submitted = true;

		अगर (io == log->current_io)
			log->current_io = शून्य;

		ppl_submit_iounit(io);
	पूर्ण
पूर्ण

व्योम ppl_ग_लिखो_stripe_run(काष्ठा r5conf *conf)
अणु
	काष्ठा ppl_conf *ppl_conf = conf->log_निजी;
	काष्ठा ppl_log *log;
	पूर्णांक i;

	क्रम (i = 0; i < ppl_conf->count; i++) अणु
		log = &ppl_conf->child_logs[i];

		mutex_lock(&log->io_mutex);
		ppl_submit_current_io(log);
		mutex_unlock(&log->io_mutex);
	पूर्ण
पूर्ण

अटल व्योम ppl_io_unit_finished(काष्ठा ppl_io_unit *io)
अणु
	काष्ठा ppl_log *log = io->log;
	काष्ठा ppl_conf *ppl_conf = log->ppl_conf;
	काष्ठा r5conf *conf = ppl_conf->mddev->निजी;
	अचिन्हित दीर्घ flags;

	pr_debug("%s: seq: %llu\n", __func__, io->seq);

	local_irq_save(flags);

	spin_lock(&log->io_list_lock);
	list_del(&io->log_sibling);
	spin_unlock(&log->io_list_lock);

	mempool_मुक्त(io, &ppl_conf->io_pool);

	spin_lock(&ppl_conf->no_mem_stripes_lock);
	अगर (!list_empty(&ppl_conf->no_mem_stripes)) अणु
		काष्ठा stripe_head *sh;

		sh = list_first_entry(&ppl_conf->no_mem_stripes,
				      काष्ठा stripe_head, log_list);
		list_del_init(&sh->log_list);
		set_bit(STRIPE_HANDLE, &sh->state);
		raid5_release_stripe(sh);
	पूर्ण
	spin_unlock(&ppl_conf->no_mem_stripes_lock);

	local_irq_restore(flags);

	wake_up(&conf->रुको_क्रम_quiescent);
पूर्ण

अटल व्योम ppl_flush_endio(काष्ठा bio *bio)
अणु
	काष्ठा ppl_io_unit *io = bio->bi_निजी;
	काष्ठा ppl_log *log = io->log;
	काष्ठा ppl_conf *ppl_conf = log->ppl_conf;
	काष्ठा r5conf *conf = ppl_conf->mddev->निजी;
	अक्षर b[BDEVNAME_SIZE];

	pr_debug("%s: dev: %s\n", __func__, bio_devname(bio, b));

	अगर (bio->bi_status) अणु
		काष्ठा md_rdev *rdev;

		rcu_पढ़ो_lock();
		rdev = md_find_rdev_rcu(conf->mddev, bio_dev(bio));
		अगर (rdev)
			md_error(rdev->mddev, rdev);
		rcu_पढ़ो_unlock();
	पूर्ण

	bio_put(bio);

	अगर (atomic_dec_and_test(&io->pending_flushes)) अणु
		ppl_io_unit_finished(io);
		md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
	पूर्ण
पूर्ण

अटल व्योम ppl_करो_flush(काष्ठा ppl_io_unit *io)
अणु
	काष्ठा ppl_log *log = io->log;
	काष्ठा ppl_conf *ppl_conf = log->ppl_conf;
	काष्ठा r5conf *conf = ppl_conf->mddev->निजी;
	पूर्णांक raid_disks = conf->raid_disks;
	पूर्णांक flushed_disks = 0;
	पूर्णांक i;

	atomic_set(&io->pending_flushes, raid_disks);

	क्रम_each_set_bit(i, &log->disk_flush_biपंचांगap, raid_disks) अणु
		काष्ठा md_rdev *rdev;
		काष्ठा block_device *bdev = शून्य;

		rcu_पढ़ो_lock();
		rdev = rcu_dereference(conf->disks[i].rdev);
		अगर (rdev && !test_bit(Faulty, &rdev->flags))
			bdev = rdev->bdev;
		rcu_पढ़ो_unlock();

		अगर (bdev) अणु
			काष्ठा bio *bio;
			अक्षर b[BDEVNAME_SIZE];

			bio = bio_alloc_bioset(GFP_NOIO, 0, &ppl_conf->flush_bs);
			bio_set_dev(bio, bdev);
			bio->bi_निजी = io;
			bio->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;
			bio->bi_end_io = ppl_flush_endio;

			pr_debug("%s: dev: %s\n", __func__,
				 bio_devname(bio, b));

			submit_bio(bio);
			flushed_disks++;
		पूर्ण
	पूर्ण

	log->disk_flush_biपंचांगap = 0;

	क्रम (i = flushed_disks ; i < raid_disks; i++) अणु
		अगर (atomic_dec_and_test(&io->pending_flushes))
			ppl_io_unit_finished(io);
	पूर्ण
पूर्ण

अटल अंतरभूत bool ppl_no_io_unit_submitted(काष्ठा r5conf *conf,
					    काष्ठा ppl_log *log)
अणु
	काष्ठा ppl_io_unit *io;

	io = list_first_entry_or_null(&log->io_list, काष्ठा ppl_io_unit,
				      log_sibling);

	वापस !io || !io->submitted;
पूर्ण

व्योम ppl_quiesce(काष्ठा r5conf *conf, पूर्णांक quiesce)
अणु
	काष्ठा ppl_conf *ppl_conf = conf->log_निजी;
	पूर्णांक i;

	अगर (quiesce) अणु
		क्रम (i = 0; i < ppl_conf->count; i++) अणु
			काष्ठा ppl_log *log = &ppl_conf->child_logs[i];

			spin_lock_irq(&log->io_list_lock);
			रुको_event_lock_irq(conf->रुको_क्रम_quiescent,
					    ppl_no_io_unit_submitted(conf, log),
					    log->io_list_lock);
			spin_unlock_irq(&log->io_list_lock);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ppl_handle_flush_request(काष्ठा r5l_log *log, काष्ठा bio *bio)
अणु
	अगर (bio->bi_iter.bi_size == 0) अणु
		bio_endio(bio);
		वापस 0;
	पूर्ण
	bio->bi_opf &= ~REQ_PREFLUSH;
	वापस -EAGAIN;
पूर्ण

व्योम ppl_stripe_ग_लिखो_finished(काष्ठा stripe_head *sh)
अणु
	काष्ठा ppl_io_unit *io;

	io = sh->ppl_io;
	sh->ppl_io = शून्य;

	अगर (io && atomic_dec_and_test(&io->pending_stripes)) अणु
		अगर (io->log->disk_flush_biपंचांगap)
			ppl_करो_flush(io);
		अन्यथा
			ppl_io_unit_finished(io);
	पूर्ण
पूर्ण

अटल व्योम ppl_xor(पूर्णांक size, काष्ठा page *page1, काष्ठा page *page2)
अणु
	काष्ठा async_submit_ctl submit;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा page *xor_srcs[] = अणु page1, page2 पूर्ण;

	init_async_submit(&submit, ASYNC_TX_ACK|ASYNC_TX_XOR_DROP_DST,
			  शून्य, शून्य, शून्य, शून्य);
	tx = async_xor(page1, xor_srcs, 0, 2, size, &submit);

	async_tx_quiesce(&tx);
पूर्ण

/*
 * PPL recovery strategy: xor partial parity and data from all modअगरied data
 * disks within a stripe and ग_लिखो the result as the new stripe parity. If all
 * stripe data disks are modअगरied (full stripe ग_लिखो), no partial parity is
 * available, so just xor the data disks.
 *
 * Recovery of a PPL entry shall occur only अगर all modअगरied data disks are
 * available and पढ़ो from all of them succeeds.
 *
 * A PPL entry applies to a stripe, partial parity size क्रम an entry is at most
 * the size of the chunk. Examples of possible हालs क्रम a single entry:
 *
 * हाल 0: single data disk ग_लिखो:
 *   data0    data1    data2     ppl        parity
 * +--------+--------+--------+           +--------------------+
 * | ------ | ------ | ------ | +----+    | (no change)        |
 * | ------ | -data- | ------ | | pp | -> | data1 ^ pp         |
 * | ------ | -data- | ------ | | pp | -> | data1 ^ pp         |
 * | ------ | ------ | ------ | +----+    | (no change)        |
 * +--------+--------+--------+           +--------------------+
 * pp_size = data_size
 *
 * हाल 1: more than one data disk ग_लिखो:
 *   data0    data1    data2     ppl        parity
 * +--------+--------+--------+           +--------------------+
 * | ------ | ------ | ------ | +----+    | (no change)        |
 * | -data- | -data- | ------ | | pp | -> | data0 ^ data1 ^ pp |
 * | -data- | -data- | ------ | | pp | -> | data0 ^ data1 ^ pp |
 * | ------ | ------ | ------ | +----+    | (no change)        |
 * +--------+--------+--------+           +--------------------+
 * pp_size = data_size / modअगरied_data_disks
 *
 * हाल 2: ग_लिखो to all data disks (also full stripe ग_लिखो):
 *   data0    data1    data2                parity
 * +--------+--------+--------+           +--------------------+
 * | ------ | ------ | ------ |           | (no change)        |
 * | -data- | -data- | -data- | --------> | xor all data       |
 * | ------ | ------ | ------ | --------> | (no change)        |
 * | ------ | ------ | ------ |           | (no change)        |
 * +--------+--------+--------+           +--------------------+
 * pp_size = 0
 *
 * The following हालs are possible only in other implementations. The recovery
 * code can handle them, but they are not generated at runसमय because they can
 * be reduced to हालs 0, 1 and 2:
 *
 * हाल 3:
 *   data0    data1    data2     ppl        parity
 * +--------+--------+--------+ +----+    +--------------------+
 * | ------ | -data- | -data- | | pp |    | data1 ^ data2 ^ pp |
 * | ------ | -data- | -data- | | pp | -> | data1 ^ data2 ^ pp |
 * | -data- | -data- | -data- | | -- | -> | xor all data       |
 * | -data- | -data- | ------ | | pp |    | data0 ^ data1 ^ pp |
 * +--------+--------+--------+ +----+    +--------------------+
 * pp_size = chunk_size
 *
 * हाल 4:
 *   data0    data1    data2     ppl        parity
 * +--------+--------+--------+ +----+    +--------------------+
 * | ------ | -data- | ------ | | pp |    | data1 ^ pp         |
 * | ------ | ------ | ------ | | -- | -> | (no change)        |
 * | ------ | ------ | ------ | | -- | -> | (no change)        |
 * | -data- | ------ | ------ | | pp |    | data0 ^ pp         |
 * +--------+--------+--------+ +----+    +--------------------+
 * pp_size = chunk_size
 */
अटल पूर्णांक ppl_recover_entry(काष्ठा ppl_log *log, काष्ठा ppl_header_entry *e,
			     sector_t ppl_sector)
अणु
	काष्ठा ppl_conf *ppl_conf = log->ppl_conf;
	काष्ठा mddev *mddev = ppl_conf->mddev;
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक block_size = ppl_conf->block_size;
	काष्ठा page *page1;
	काष्ठा page *page2;
	sector_t r_sector_first;
	sector_t r_sector_last;
	पूर्णांक strip_sectors;
	पूर्णांक data_disks;
	पूर्णांक i;
	पूर्णांक ret = 0;
	अक्षर b[BDEVNAME_SIZE];
	अचिन्हित पूर्णांक pp_size = le32_to_cpu(e->pp_size);
	अचिन्हित पूर्णांक data_size = le32_to_cpu(e->data_size);

	page1 = alloc_page(GFP_KERNEL);
	page2 = alloc_page(GFP_KERNEL);

	अगर (!page1 || !page2) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	r_sector_first = le64_to_cpu(e->data_sector) * (block_size >> 9);

	अगर ((pp_size >> 9) < conf->chunk_sectors) अणु
		अगर (pp_size > 0) अणु
			data_disks = data_size / pp_size;
			strip_sectors = pp_size >> 9;
		पूर्ण अन्यथा अणु
			data_disks = conf->raid_disks - conf->max_degraded;
			strip_sectors = (data_size >> 9) / data_disks;
		पूर्ण
		r_sector_last = r_sector_first +
				(data_disks - 1) * conf->chunk_sectors +
				strip_sectors;
	पूर्ण अन्यथा अणु
		data_disks = conf->raid_disks - conf->max_degraded;
		strip_sectors = conf->chunk_sectors;
		r_sector_last = r_sector_first + (data_size >> 9);
	पूर्ण

	pr_debug("%s: array sector first: %llu last: %llu\n", __func__,
		 (अचिन्हित दीर्घ दीर्घ)r_sector_first,
		 (अचिन्हित दीर्घ दीर्घ)r_sector_last);

	/* अगर start and end is 4k aligned, use a 4k block */
	अगर (block_size == 512 &&
	    (r_sector_first & (RAID5_STRIPE_SECTORS(conf) - 1)) == 0 &&
	    (r_sector_last & (RAID5_STRIPE_SECTORS(conf) - 1)) == 0)
		block_size = RAID5_STRIPE_SIZE(conf);

	/* iterate through blocks in strip */
	क्रम (i = 0; i < strip_sectors; i += (block_size >> 9)) अणु
		bool update_parity = false;
		sector_t parity_sector;
		काष्ठा md_rdev *parity_rdev;
		काष्ठा stripe_head sh;
		पूर्णांक disk;
		पूर्णांक indent = 0;

		pr_debug("%s:%*s iter %d start\n", __func__, indent, "", i);
		indent += 2;

		स_रखो(page_address(page1), 0, PAGE_SIZE);

		/* iterate through data member disks */
		क्रम (disk = 0; disk < data_disks; disk++) अणु
			पूर्णांक dd_idx;
			काष्ठा md_rdev *rdev;
			sector_t sector;
			sector_t r_sector = r_sector_first + i +
					    (disk * conf->chunk_sectors);

			pr_debug("%s:%*s data member disk %d start\n",
				 __func__, indent, "", disk);
			indent += 2;

			अगर (r_sector >= r_sector_last) अणु
				pr_debug("%s:%*s array sector %llu doesn't need parity update\n",
					 __func__, indent, "",
					 (अचिन्हित दीर्घ दीर्घ)r_sector);
				indent -= 2;
				जारी;
			पूर्ण

			update_parity = true;

			/* map raid sector to member disk */
			sector = raid5_compute_sector(conf, r_sector, 0,
						      &dd_idx, शून्य);
			pr_debug("%s:%*s processing array sector %llu => data member disk %d, sector %llu\n",
				 __func__, indent, "",
				 (अचिन्हित दीर्घ दीर्घ)r_sector, dd_idx,
				 (अचिन्हित दीर्घ दीर्घ)sector);

			rdev = conf->disks[dd_idx].rdev;
			अगर (!rdev || (!test_bit(In_sync, &rdev->flags) &&
				      sector >= rdev->recovery_offset)) अणु
				pr_debug("%s:%*s data member disk %d missing\n",
					 __func__, indent, "", dd_idx);
				update_parity = false;
				अवरोध;
			पूर्ण

			pr_debug("%s:%*s reading data member disk %s sector %llu\n",
				 __func__, indent, "", bdevname(rdev->bdev, b),
				 (अचिन्हित दीर्घ दीर्घ)sector);
			अगर (!sync_page_io(rdev, sector, block_size, page2,
					REQ_OP_READ, 0, false)) अणु
				md_error(mddev, rdev);
				pr_debug("%s:%*s read failed!\n", __func__,
					 indent, "");
				ret = -EIO;
				जाओ out;
			पूर्ण

			ppl_xor(block_size, page1, page2);

			indent -= 2;
		पूर्ण

		अगर (!update_parity)
			जारी;

		अगर (pp_size > 0) अणु
			pr_debug("%s:%*s reading pp disk sector %llu\n",
				 __func__, indent, "",
				 (अचिन्हित दीर्घ दीर्घ)(ppl_sector + i));
			अगर (!sync_page_io(log->rdev,
					ppl_sector - log->rdev->data_offset + i,
					block_size, page2, REQ_OP_READ, 0,
					false)) अणु
				pr_debug("%s:%*s read failed!\n", __func__,
					 indent, "");
				md_error(mddev, log->rdev);
				ret = -EIO;
				जाओ out;
			पूर्ण

			ppl_xor(block_size, page1, page2);
		पूर्ण

		/* map raid sector to parity disk */
		parity_sector = raid5_compute_sector(conf, r_sector_first + i,
				0, &disk, &sh);
		BUG_ON(sh.pd_idx != le32_to_cpu(e->parity_disk));
		parity_rdev = conf->disks[sh.pd_idx].rdev;

		BUG_ON(parity_rdev->bdev->bd_dev != log->rdev->bdev->bd_dev);
		pr_debug("%s:%*s write parity at sector %llu, disk %s\n",
			 __func__, indent, "",
			 (अचिन्हित दीर्घ दीर्घ)parity_sector,
			 bdevname(parity_rdev->bdev, b));
		अगर (!sync_page_io(parity_rdev, parity_sector, block_size,
				page1, REQ_OP_WRITE, 0, false)) अणु
			pr_debug("%s:%*s parity write error!\n", __func__,
				 indent, "");
			md_error(mddev, parity_rdev);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (page1)
		__मुक्त_page(page1);
	अगर (page2)
		__मुक्त_page(page2);
	वापस ret;
पूर्ण

अटल पूर्णांक ppl_recover(काष्ठा ppl_log *log, काष्ठा ppl_header *pplhdr,
		       sector_t offset)
अणु
	काष्ठा ppl_conf *ppl_conf = log->ppl_conf;
	काष्ठा md_rdev *rdev = log->rdev;
	काष्ठा mddev *mddev = rdev->mddev;
	sector_t ppl_sector = rdev->ppl.sector + offset +
			      (PPL_HEADER_SIZE >> 9);
	काष्ठा page *page;
	पूर्णांक i;
	पूर्णांक ret = 0;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	/* iterate through all PPL entries saved */
	क्रम (i = 0; i < le32_to_cpu(pplhdr->entries_count); i++) अणु
		काष्ठा ppl_header_entry *e = &pplhdr->entries[i];
		u32 pp_size = le32_to_cpu(e->pp_size);
		sector_t sector = ppl_sector;
		पूर्णांक ppl_entry_sectors = pp_size >> 9;
		u32 crc, crc_stored;

		pr_debug("%s: disk: %d entry: %d ppl_sector: %llu pp_size: %u\n",
			 __func__, rdev->raid_disk, i,
			 (अचिन्हित दीर्घ दीर्घ)ppl_sector, pp_size);

		crc = ~0;
		crc_stored = le32_to_cpu(e->checksum);

		/* पढ़ो parial parity क्रम this entry and calculate its checksum */
		जबतक (pp_size) अणु
			पूर्णांक s = pp_size > PAGE_SIZE ? PAGE_SIZE : pp_size;

			अगर (!sync_page_io(rdev, sector - rdev->data_offset,
					s, page, REQ_OP_READ, 0, false)) अणु
				md_error(mddev, rdev);
				ret = -EIO;
				जाओ out;
			पूर्ण

			crc = crc32c_le(crc, page_address(page), s);

			pp_size -= s;
			sector += s >> 9;
		पूर्ण

		crc = ~crc;

		अगर (crc != crc_stored) अणु
			/*
			 * Don't recover this entry अगर the checksum करोes not
			 * match, but keep going and try to recover other
			 * entries.
			 */
			pr_debug("%s: ppl entry crc does not match: stored: 0x%x calculated: 0x%x\n",
				 __func__, crc_stored, crc);
			ppl_conf->mismatch_count++;
		पूर्ण अन्यथा अणु
			ret = ppl_recover_entry(log, e, ppl_sector);
			अगर (ret)
				जाओ out;
			ppl_conf->recovered_entries++;
		पूर्ण

		ppl_sector += ppl_entry_sectors;
	पूर्ण

	/* flush the disk cache after recovery अगर necessary */
	ret = blkdev_issue_flush(rdev->bdev);
out:
	__मुक्त_page(page);
	वापस ret;
पूर्ण

अटल पूर्णांक ppl_ग_लिखो_empty_header(काष्ठा ppl_log *log)
अणु
	काष्ठा page *page;
	काष्ठा ppl_header *pplhdr;
	काष्ठा md_rdev *rdev = log->rdev;
	पूर्णांक ret = 0;

	pr_debug("%s: disk: %d ppl_sector: %llu\n", __func__,
		 rdev->raid_disk, (अचिन्हित दीर्घ दीर्घ)rdev->ppl.sector);

	page = alloc_page(GFP_NOIO | __GFP_ZERO);
	अगर (!page)
		वापस -ENOMEM;

	pplhdr = page_address(page);
	/* zero out PPL space to aव्योम collision with old PPLs */
	blkdev_issue_zeroout(rdev->bdev, rdev->ppl.sector,
			    log->rdev->ppl.size, GFP_NOIO, 0);
	स_रखो(pplhdr->reserved, 0xff, PPL_HDR_RESERVED);
	pplhdr->signature = cpu_to_le32(log->ppl_conf->signature);
	pplhdr->checksum = cpu_to_le32(~crc32c_le(~0, pplhdr, PAGE_SIZE));

	अगर (!sync_page_io(rdev, rdev->ppl.sector - rdev->data_offset,
			  PPL_HEADER_SIZE, page, REQ_OP_WRITE | REQ_SYNC |
			  REQ_FUA, 0, false)) अणु
		md_error(rdev->mddev, rdev);
		ret = -EIO;
	पूर्ण

	__मुक्त_page(page);
	वापस ret;
पूर्ण

अटल पूर्णांक ppl_load_distributed(काष्ठा ppl_log *log)
अणु
	काष्ठा ppl_conf *ppl_conf = log->ppl_conf;
	काष्ठा md_rdev *rdev = log->rdev;
	काष्ठा mddev *mddev = rdev->mddev;
	काष्ठा page *page, *page2, *पंचांगp;
	काष्ठा ppl_header *pplhdr = शून्य, *prev_pplhdr = शून्य;
	u32 crc, crc_stored;
	u32 signature;
	पूर्णांक ret = 0, i;
	sector_t pplhdr_offset = 0, prev_pplhdr_offset = 0;

	pr_debug("%s: disk: %d\n", __func__, rdev->raid_disk);
	/* पढ़ो PPL headers, find the recent one */
	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	page2 = alloc_page(GFP_KERNEL);
	अगर (!page2) अणु
		__मुक्त_page(page);
		वापस -ENOMEM;
	पूर्ण

	/* searching ppl area क्रम latest ppl */
	जबतक (pplhdr_offset < rdev->ppl.size - (PPL_HEADER_SIZE >> 9)) अणु
		अगर (!sync_page_io(rdev,
				  rdev->ppl.sector - rdev->data_offset +
				  pplhdr_offset, PAGE_SIZE, page, REQ_OP_READ,
				  0, false)) अणु
			md_error(mddev, rdev);
			ret = -EIO;
			/* अगर not able to पढ़ो - करोn't recover any PPL */
			pplhdr = शून्य;
			अवरोध;
		पूर्ण
		pplhdr = page_address(page);

		/* check header validity */
		crc_stored = le32_to_cpu(pplhdr->checksum);
		pplhdr->checksum = 0;
		crc = ~crc32c_le(~0, pplhdr, PAGE_SIZE);

		अगर (crc_stored != crc) अणु
			pr_debug("%s: ppl header crc does not match: stored: 0x%x calculated: 0x%x (offset: %llu)\n",
				 __func__, crc_stored, crc,
				 (अचिन्हित दीर्घ दीर्घ)pplhdr_offset);
			pplhdr = prev_pplhdr;
			pplhdr_offset = prev_pplhdr_offset;
			अवरोध;
		पूर्ण

		signature = le32_to_cpu(pplhdr->signature);

		अगर (mddev->बाह्यal) अणु
			/*
			 * For बाह्यal metadata the header signature is set and
			 * validated in userspace.
			 */
			ppl_conf->signature = signature;
		पूर्ण अन्यथा अगर (ppl_conf->signature != signature) अणु
			pr_debug("%s: ppl header signature does not match: stored: 0x%x configured: 0x%x (offset: %llu)\n",
				 __func__, signature, ppl_conf->signature,
				 (अचिन्हित दीर्घ दीर्घ)pplhdr_offset);
			pplhdr = prev_pplhdr;
			pplhdr_offset = prev_pplhdr_offset;
			अवरोध;
		पूर्ण

		अगर (prev_pplhdr && le64_to_cpu(prev_pplhdr->generation) >
		    le64_to_cpu(pplhdr->generation)) अणु
			/* previous was newest */
			pplhdr = prev_pplhdr;
			pplhdr_offset = prev_pplhdr_offset;
			अवरोध;
		पूर्ण

		prev_pplhdr_offset = pplhdr_offset;
		prev_pplhdr = pplhdr;

		पंचांगp = page;
		page = page2;
		page2 = पंचांगp;

		/* calculate next potential ppl offset */
		क्रम (i = 0; i < le32_to_cpu(pplhdr->entries_count); i++)
			pplhdr_offset +=
			    le32_to_cpu(pplhdr->entries[i].pp_size) >> 9;
		pplhdr_offset += PPL_HEADER_SIZE >> 9;
	पूर्ण

	/* no valid ppl found */
	अगर (!pplhdr)
		ppl_conf->mismatch_count++;
	अन्यथा
		pr_debug("%s: latest PPL found at offset: %llu, with generation: %llu\n",
		    __func__, (अचिन्हित दीर्घ दीर्घ)pplhdr_offset,
		    le64_to_cpu(pplhdr->generation));

	/* attempt to recover from log अगर we are starting a dirty array */
	अगर (pplhdr && !mddev->pers && mddev->recovery_cp != MaxSector)
		ret = ppl_recover(log, pplhdr, pplhdr_offset);

	/* ग_लिखो empty header अगर we are starting the array */
	अगर (!ret && !mddev->pers)
		ret = ppl_ग_लिखो_empty_header(log);

	__मुक्त_page(page);
	__मुक्त_page(page2);

	pr_debug("%s: return: %d mismatch_count: %d recovered_entries: %d\n",
		 __func__, ret, ppl_conf->mismatch_count,
		 ppl_conf->recovered_entries);
	वापस ret;
पूर्ण

अटल पूर्णांक ppl_load(काष्ठा ppl_conf *ppl_conf)
अणु
	पूर्णांक ret = 0;
	u32 signature = 0;
	bool signature_set = false;
	पूर्णांक i;

	क्रम (i = 0; i < ppl_conf->count; i++) अणु
		काष्ठा ppl_log *log = &ppl_conf->child_logs[i];

		/* skip missing drive */
		अगर (!log->rdev)
			जारी;

		ret = ppl_load_distributed(log);
		अगर (ret)
			अवरोध;

		/*
		 * For बाह्यal metadata we can't check अगर the signature is
		 * correct on a single drive, but we can check अगर it is the same
		 * on all drives.
		 */
		अगर (ppl_conf->mddev->बाह्यal) अणु
			अगर (!signature_set) अणु
				signature = ppl_conf->signature;
				signature_set = true;
			पूर्ण अन्यथा अगर (signature != ppl_conf->signature) अणु
				pr_warn("md/raid:%s: PPL header signature does not match on all member drives\n",
					mdname(ppl_conf->mddev));
				ret = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	pr_debug("%s: return: %d mismatch_count: %d recovered_entries: %d\n",
		 __func__, ret, ppl_conf->mismatch_count,
		 ppl_conf->recovered_entries);
	वापस ret;
पूर्ण

अटल व्योम __ppl_निकास_log(काष्ठा ppl_conf *ppl_conf)
अणु
	clear_bit(MD_HAS_PPL, &ppl_conf->mddev->flags);
	clear_bit(MD_HAS_MULTIPLE_PPLS, &ppl_conf->mddev->flags);

	kमुक्त(ppl_conf->child_logs);

	bioset_निकास(&ppl_conf->bs);
	bioset_निकास(&ppl_conf->flush_bs);
	mempool_निकास(&ppl_conf->io_pool);
	kmem_cache_destroy(ppl_conf->io_kc);

	kमुक्त(ppl_conf);
पूर्ण

व्योम ppl_निकास_log(काष्ठा r5conf *conf)
अणु
	काष्ठा ppl_conf *ppl_conf = conf->log_निजी;

	अगर (ppl_conf) अणु
		__ppl_निकास_log(ppl_conf);
		conf->log_निजी = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ppl_validate_rdev(काष्ठा md_rdev *rdev)
अणु
	अक्षर b[BDEVNAME_SIZE];
	पूर्णांक ppl_data_sectors;
	पूर्णांक ppl_size_new;

	/*
	 * The configured PPL size must be enough to store
	 * the header and (at the very least) partial parity
	 * क्रम one stripe. Round it करोwn to ensure the data
	 * space is cleanly भागisible by stripe size.
	 */
	ppl_data_sectors = rdev->ppl.size - (PPL_HEADER_SIZE >> 9);

	अगर (ppl_data_sectors > 0)
		ppl_data_sectors = roundकरोwn(ppl_data_sectors,
				RAID5_STRIPE_SECTORS((काष्ठा r5conf *)rdev->mddev->निजी));

	अगर (ppl_data_sectors <= 0) अणु
		pr_warn("md/raid:%s: PPL space too small on %s\n",
			mdname(rdev->mddev), bdevname(rdev->bdev, b));
		वापस -ENOSPC;
	पूर्ण

	ppl_size_new = ppl_data_sectors + (PPL_HEADER_SIZE >> 9);

	अगर ((rdev->ppl.sector < rdev->data_offset &&
	     rdev->ppl.sector + ppl_size_new > rdev->data_offset) ||
	    (rdev->ppl.sector >= rdev->data_offset &&
	     rdev->data_offset + rdev->sectors > rdev->ppl.sector)) अणु
		pr_warn("md/raid:%s: PPL space overlaps with data on %s\n",
			mdname(rdev->mddev), bdevname(rdev->bdev, b));
		वापस -EINVAL;
	पूर्ण

	अगर (!rdev->mddev->बाह्यal &&
	    ((rdev->ppl.offset > 0 && rdev->ppl.offset < (rdev->sb_size >> 9)) ||
	     (rdev->ppl.offset <= 0 && rdev->ppl.offset + ppl_size_new > 0))) अणु
		pr_warn("md/raid:%s: PPL space overlaps with superblock on %s\n",
			mdname(rdev->mddev), bdevname(rdev->bdev, b));
		वापस -EINVAL;
	पूर्ण

	rdev->ppl.size = ppl_size_new;

	वापस 0;
पूर्ण

अटल व्योम ppl_init_child_log(काष्ठा ppl_log *log, काष्ठा md_rdev *rdev)
अणु
	काष्ठा request_queue *q;

	अगर ((rdev->ppl.size << 9) >= (PPL_SPACE_SIZE +
				      PPL_HEADER_SIZE) * 2) अणु
		log->use_multippl = true;
		set_bit(MD_HAS_MULTIPLE_PPLS,
			&log->ppl_conf->mddev->flags);
		log->entry_space = PPL_SPACE_SIZE;
	पूर्ण अन्यथा अणु
		log->use_multippl = false;
		log->entry_space = (log->rdev->ppl.size << 9) -
				   PPL_HEADER_SIZE;
	पूर्ण
	log->next_io_sector = rdev->ppl.sector;

	q = bdev_get_queue(rdev->bdev);
	अगर (test_bit(QUEUE_FLAG_WC, &q->queue_flags))
		log->wb_cache_on = true;
पूर्ण

पूर्णांक ppl_init_log(काष्ठा r5conf *conf)
अणु
	काष्ठा ppl_conf *ppl_conf;
	काष्ठा mddev *mddev = conf->mddev;
	पूर्णांक ret = 0;
	पूर्णांक max_disks;
	पूर्णांक i;

	pr_debug("md/raid:%s: enabling distributed Partial Parity Log\n",
		 mdname(conf->mddev));

	अगर (PAGE_SIZE != 4096)
		वापस -EINVAL;

	अगर (mddev->level != 5) अणु
		pr_warn("md/raid:%s PPL is not compatible with raid level %d\n",
			mdname(mddev), mddev->level);
		वापस -EINVAL;
	पूर्ण

	अगर (mddev->biपंचांगap_info.file || mddev->biपंचांगap_info.offset) अणु
		pr_warn("md/raid:%s PPL is not compatible with bitmap\n",
			mdname(mddev));
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(MD_HAS_JOURNAL, &mddev->flags)) अणु
		pr_warn("md/raid:%s PPL is not compatible with journal\n",
			mdname(mddev));
		वापस -EINVAL;
	पूर्ण

	max_disks = माप_field(काष्ठा ppl_log, disk_flush_biपंचांगap) *
		BITS_PER_BYTE;
	अगर (conf->raid_disks > max_disks) अणु
		pr_warn("md/raid:%s PPL doesn't support over %d disks in the array\n",
			mdname(mddev), max_disks);
		वापस -EINVAL;
	पूर्ण

	ppl_conf = kzalloc(माप(काष्ठा ppl_conf), GFP_KERNEL);
	अगर (!ppl_conf)
		वापस -ENOMEM;

	ppl_conf->mddev = mddev;

	ppl_conf->io_kc = KMEM_CACHE(ppl_io_unit, 0);
	अगर (!ppl_conf->io_kc) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = mempool_init(&ppl_conf->io_pool, conf->raid_disks, ppl_io_pool_alloc,
			   ppl_io_pool_मुक्त, ppl_conf->io_kc);
	अगर (ret)
		जाओ err;

	ret = bioset_init(&ppl_conf->bs, conf->raid_disks, 0, BIOSET_NEED_BVECS);
	अगर (ret)
		जाओ err;

	ret = bioset_init(&ppl_conf->flush_bs, conf->raid_disks, 0, 0);
	अगर (ret)
		जाओ err;

	ppl_conf->count = conf->raid_disks;
	ppl_conf->child_logs = kसुस्मृति(ppl_conf->count, माप(काष्ठा ppl_log),
				       GFP_KERNEL);
	अगर (!ppl_conf->child_logs) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	atomic64_set(&ppl_conf->seq, 0);
	INIT_LIST_HEAD(&ppl_conf->no_mem_stripes);
	spin_lock_init(&ppl_conf->no_mem_stripes_lock);
	ppl_conf->ग_लिखो_hपूर्णांक = RWH_WRITE_LIFE_NOT_SET;

	अगर (!mddev->बाह्यal) अणु
		ppl_conf->signature = ~crc32c_le(~0, mddev->uuid, माप(mddev->uuid));
		ppl_conf->block_size = 512;
	पूर्ण अन्यथा अणु
		ppl_conf->block_size = queue_logical_block_size(mddev->queue);
	पूर्ण

	क्रम (i = 0; i < ppl_conf->count; i++) अणु
		काष्ठा ppl_log *log = &ppl_conf->child_logs[i];
		काष्ठा md_rdev *rdev = conf->disks[i].rdev;

		mutex_init(&log->io_mutex);
		spin_lock_init(&log->io_list_lock);
		INIT_LIST_HEAD(&log->io_list);

		log->ppl_conf = ppl_conf;
		log->rdev = rdev;

		अगर (rdev) अणु
			ret = ppl_validate_rdev(rdev);
			अगर (ret)
				जाओ err;

			ppl_init_child_log(log, rdev);
		पूर्ण
	पूर्ण

	/* load and possibly recover the logs from the member disks */
	ret = ppl_load(ppl_conf);

	अगर (ret) अणु
		जाओ err;
	पूर्ण अन्यथा अगर (!mddev->pers && mddev->recovery_cp == 0 &&
		   ppl_conf->recovered_entries > 0 &&
		   ppl_conf->mismatch_count == 0) अणु
		/*
		 * If we are starting a dirty array and the recovery succeeds
		 * without any issues, set the array as clean.
		 */
		mddev->recovery_cp = MaxSector;
		set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
	पूर्ण अन्यथा अगर (mddev->pers && ppl_conf->mismatch_count > 0) अणु
		/* no mismatch allowed when enabling PPL क्रम a running array */
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	conf->log_निजी = ppl_conf;
	set_bit(MD_HAS_PPL, &ppl_conf->mddev->flags);

	वापस 0;
err:
	__ppl_निकास_log(ppl_conf);
	वापस ret;
पूर्ण

पूर्णांक ppl_modअगरy_log(काष्ठा r5conf *conf, काष्ठा md_rdev *rdev, bool add)
अणु
	काष्ठा ppl_conf *ppl_conf = conf->log_निजी;
	काष्ठा ppl_log *log;
	पूर्णांक ret = 0;
	अक्षर b[BDEVNAME_SIZE];

	अगर (!rdev)
		वापस -EINVAL;

	pr_debug("%s: disk: %d operation: %s dev: %s\n",
		 __func__, rdev->raid_disk, add ? "add" : "remove",
		 bdevname(rdev->bdev, b));

	अगर (rdev->raid_disk < 0)
		वापस 0;

	अगर (rdev->raid_disk >= ppl_conf->count)
		वापस -ENODEV;

	log = &ppl_conf->child_logs[rdev->raid_disk];

	mutex_lock(&log->io_mutex);
	अगर (add) अणु
		ret = ppl_validate_rdev(rdev);
		अगर (!ret) अणु
			log->rdev = rdev;
			ret = ppl_ग_लिखो_empty_header(log);
			ppl_init_child_log(log, rdev);
		पूर्ण
	पूर्ण अन्यथा अणु
		log->rdev = शून्य;
	पूर्ण
	mutex_unlock(&log->io_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
ppl_ग_लिखो_hपूर्णांक_show(काष्ठा mddev *mddev, अक्षर *buf)
अणु
	माप_प्रकार ret = 0;
	काष्ठा r5conf *conf;
	काष्ठा ppl_conf *ppl_conf = शून्य;

	spin_lock(&mddev->lock);
	conf = mddev->निजी;
	अगर (conf && raid5_has_ppl(conf))
		ppl_conf = conf->log_निजी;
	ret = प्र_लिखो(buf, "%d\n", ppl_conf ? ppl_conf->ग_लिखो_hपूर्णांक : 0);
	spin_unlock(&mddev->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
ppl_ग_लिखो_hपूर्णांक_store(काष्ठा mddev *mddev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा r5conf *conf;
	काष्ठा ppl_conf *ppl_conf;
	पूर्णांक err = 0;
	अचिन्हित लघु new;

	अगर (len >= PAGE_SIZE)
		वापस -EINVAL;
	अगर (kstrtou16(page, 10, &new))
		वापस -EINVAL;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;

	conf = mddev->निजी;
	अगर (!conf) अणु
		err = -ENODEV;
	पूर्ण अन्यथा अगर (raid5_has_ppl(conf)) अणु
		ppl_conf = conf->log_निजी;
		अगर (!ppl_conf)
			err = -EINVAL;
		अन्यथा
			ppl_conf->ग_लिखो_hपूर्णांक = new;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण

	mddev_unlock(mddev);

	वापस err ?: len;
पूर्ण

काष्ठा md_sysfs_entry
ppl_ग_लिखो_hपूर्णांक = __ATTR(ppl_ग_लिखो_hपूर्णांक, S_IRUGO | S_IWUSR,
			ppl_ग_लिखो_hपूर्णांक_show,
			ppl_ग_लिखो_hपूर्णांक_store);
