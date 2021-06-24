<शैली गुरु>
/*
 * Copyright (C) 2014 Facebook. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/device-mapper.h>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/dax.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/uपन.स>

#घोषणा DM_MSG_PREFIX "log-writes"

/*
 * This target will sequentially log all ग_लिखोs to the target device onto the
 * log device.  This is helpful क्रम replaying ग_लिखोs to check क्रम fs consistency
 * at all बार.  This target provides a mechanism to mark specअगरic events to
 * check data at a later समय.  So क्रम example you would:
 *
 * ग_लिखो data
 * fsync
 * dmsetup message /dev/whatever mark mymark
 * unmount /mnt/test
 *
 * Then replay the log up to mymark and check the contents of the replay to
 * verअगरy it matches what was written.
 *
 * We log ग_लिखोs only after they have been flushed, this makes the log describe
 * बंद to the order in which the data hits the actual disk, not its cache.  So
 * क्रम example the following sequence (W means ग_लिखो, C means complete)
 *
 * Wa,Wb,Wc,Cc,Ca,FLUSH,FUAd,Cb,CFLUSH,CFUAd
 *
 * Would result in the log looking like this:
 *
 * c,a,b,flush,fuad,<other ग_लिखोs>,<next flush>
 *
 * This is meant to help expose problems where file प्रणालीs करो not properly रुको
 * on data being written beक्रमe invoking a FLUSH.  FUA bypasses cache so once it
 * completes it is added to the log as it should be on disk.
 *
 * We treat DISCARDs as अगर they करोn't bypass cache so that they are logged in
 * order of completion aदीर्घ with the normal ग_लिखोs.  If we didn't करो it this
 * way we would process all the discards first and then ग_लिखो all the data, when
 * in fact we want to करो the data and the discard in the order that they
 * completed.
 */
#घोषणा LOG_FLUSH_FLAG		(1 << 0)
#घोषणा LOG_FUA_FLAG		(1 << 1)
#घोषणा LOG_DISCARD_FLAG	(1 << 2)
#घोषणा LOG_MARK_FLAG		(1 << 3)
#घोषणा LOG_METADATA_FLAG	(1 << 4)

#घोषणा WRITE_LOG_VERSION 1ULL
#घोषणा WRITE_LOG_MAGIC 0x6a736677736872ULL
#घोषणा WRITE_LOG_SUPER_SECTOR 0

/*
 * The disk क्रमmat क्रम this is braindead simple.
 *
 * At byte 0 we have our super, followed by the following sequence क्रम
 * nr_entries:
 *
 * [   1 sector    ][  entry->nr_sectors ]
 * [log_ग_लिखो_entry][    data written    ]
 *
 * The log_ग_लिखो_entry takes up a full sector so we can have arbitrary length
 * marks and it leaves us room क्रम extra content in the future.
 */

/*
 * Basic info about the log क्रम userspace.
 */
काष्ठा log_ग_लिखो_super अणु
	__le64 magic;
	__le64 version;
	__le64 nr_entries;
	__le32 sectorsize;
पूर्ण;

/*
 * sector - the sector we wrote.
 * nr_sectors - the number of sectors we wrote.
 * flags - flags क्रम this log entry.
 * data_len - the size of the data in this log entry, this is क्रम निजी log
 * entry stuff, the MARK data provided by userspace क्रम example.
 */
काष्ठा log_ग_लिखो_entry अणु
	__le64 sector;
	__le64 nr_sectors;
	__le64 flags;
	__le64 data_len;
पूर्ण;

काष्ठा log_ग_लिखोs_c अणु
	काष्ठा dm_dev *dev;
	काष्ठा dm_dev *logdev;
	u64 logged_entries;
	u32 sectorsize;
	u32 sectorshअगरt;
	atomic_t io_blocks;
	atomic_t pending_blocks;
	sector_t next_sector;
	sector_t end_sector;
	bool logging_enabled;
	bool device_supports_discard;
	spinlock_t blocks_lock;
	काष्ठा list_head unflushed_blocks;
	काष्ठा list_head logging_blocks;
	रुको_queue_head_t रुको;
	काष्ठा task_काष्ठा *log_kthपढ़ो;
	काष्ठा completion super_करोne;
पूर्ण;

काष्ठा pending_block अणु
	पूर्णांक vec_cnt;
	u64 flags;
	sector_t sector;
	sector_t nr_sectors;
	अक्षर *data;
	u32 datalen;
	काष्ठा list_head list;
	काष्ठा bio_vec vecs[];
पूर्ण;

काष्ठा per_bio_data अणु
	काष्ठा pending_block *block;
पूर्ण;

अटल अंतरभूत sector_t bio_to_dev_sectors(काष्ठा log_ग_लिखोs_c *lc,
					  sector_t sectors)
अणु
	वापस sectors >> (lc->sectorshअगरt - SECTOR_SHIFT);
पूर्ण

अटल अंतरभूत sector_t dev_to_bio_sectors(काष्ठा log_ग_लिखोs_c *lc,
					  sector_t sectors)
अणु
	वापस sectors << (lc->sectorshअगरt - SECTOR_SHIFT);
पूर्ण

अटल व्योम put_pending_block(काष्ठा log_ग_लिखोs_c *lc)
अणु
	अगर (atomic_dec_and_test(&lc->pending_blocks)) अणु
		smp_mb__after_atomic();
		अगर (रुकोqueue_active(&lc->रुको))
			wake_up(&lc->रुको);
	पूर्ण
पूर्ण

अटल व्योम put_io_block(काष्ठा log_ग_लिखोs_c *lc)
अणु
	अगर (atomic_dec_and_test(&lc->io_blocks)) अणु
		smp_mb__after_atomic();
		अगर (रुकोqueue_active(&lc->रुको))
			wake_up(&lc->रुको);
	पूर्ण
पूर्ण

अटल व्योम log_end_io(काष्ठा bio *bio)
अणु
	काष्ठा log_ग_लिखोs_c *lc = bio->bi_निजी;

	अगर (bio->bi_status) अणु
		अचिन्हित दीर्घ flags;

		DMERR("Error writing log block, error=%d", bio->bi_status);
		spin_lock_irqsave(&lc->blocks_lock, flags);
		lc->logging_enabled = false;
		spin_unlock_irqrestore(&lc->blocks_lock, flags);
	पूर्ण

	bio_मुक्त_pages(bio);
	put_io_block(lc);
	bio_put(bio);
पूर्ण

अटल व्योम log_end_super(काष्ठा bio *bio)
अणु
	काष्ठा log_ग_लिखोs_c *lc = bio->bi_निजी;

	complete(&lc->super_करोne);
	log_end_io(bio);
पूर्ण

/*
 * Meant to be called अगर there is an error, it will मुक्त all the pages
 * associated with the block.
 */
अटल व्योम मुक्त_pending_block(काष्ठा log_ग_लिखोs_c *lc,
			       काष्ठा pending_block *block)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < block->vec_cnt; i++) अणु
		अगर (block->vecs[i].bv_page)
			__मुक्त_page(block->vecs[i].bv_page);
	पूर्ण
	kमुक्त(block->data);
	kमुक्त(block);
	put_pending_block(lc);
पूर्ण

अटल पूर्णांक ग_लिखो_metadata(काष्ठा log_ग_लिखोs_c *lc, व्योम *entry,
			  माप_प्रकार entrylen, व्योम *data, माप_प्रकार datalen,
			  sector_t sector)
अणु
	काष्ठा bio *bio;
	काष्ठा page *page;
	व्योम *ptr;
	माप_प्रकार ret;

	bio = bio_alloc(GFP_KERNEL, 1);
	अगर (!bio) अणु
		DMERR("Couldn't alloc log bio");
		जाओ error;
	पूर्ण
	bio->bi_iter.bi_size = 0;
	bio->bi_iter.bi_sector = sector;
	bio_set_dev(bio, lc->logdev->bdev);
	bio->bi_end_io = (sector == WRITE_LOG_SUPER_SECTOR) ?
			  log_end_super : log_end_io;
	bio->bi_निजी = lc;
	bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

	page = alloc_page(GFP_KERNEL);
	अगर (!page) अणु
		DMERR("Couldn't alloc log page");
		bio_put(bio);
		जाओ error;
	पूर्ण

	ptr = kmap_atomic(page);
	स_नकल(ptr, entry, entrylen);
	अगर (datalen)
		स_नकल(ptr + entrylen, data, datalen);
	स_रखो(ptr + entrylen + datalen, 0,
	       lc->sectorsize - entrylen - datalen);
	kunmap_atomic(ptr);

	ret = bio_add_page(bio, page, lc->sectorsize, 0);
	अगर (ret != lc->sectorsize) अणु
		DMERR("Couldn't add page to the log block");
		जाओ error_bio;
	पूर्ण
	submit_bio(bio);
	वापस 0;
error_bio:
	bio_put(bio);
	__मुक्त_page(page);
error:
	put_io_block(lc);
	वापस -1;
पूर्ण

अटल पूर्णांक ग_लिखो_अंतरभूत_data(काष्ठा log_ग_लिखोs_c *lc, व्योम *entry,
			     माप_प्रकार entrylen, व्योम *data, माप_प्रकार datalen,
			     sector_t sector)
अणु
	पूर्णांक bio_pages, pg_datalen, pg_sectorlen, i;
	काष्ठा page *page;
	काष्ठा bio *bio;
	माप_प्रकार ret;
	व्योम *ptr;

	जबतक (datalen) अणु
		bio_pages = bio_max_segs(DIV_ROUND_UP(datalen, PAGE_SIZE));

		atomic_inc(&lc->io_blocks);

		bio = bio_alloc(GFP_KERNEL, bio_pages);
		अगर (!bio) अणु
			DMERR("Couldn't alloc inline data bio");
			जाओ error;
		पूर्ण

		bio->bi_iter.bi_size = 0;
		bio->bi_iter.bi_sector = sector;
		bio_set_dev(bio, lc->logdev->bdev);
		bio->bi_end_io = log_end_io;
		bio->bi_निजी = lc;
		bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

		क्रम (i = 0; i < bio_pages; i++) अणु
			pg_datalen = min_t(पूर्णांक, datalen, PAGE_SIZE);
			pg_sectorlen = ALIGN(pg_datalen, lc->sectorsize);

			page = alloc_page(GFP_KERNEL);
			अगर (!page) अणु
				DMERR("Couldn't alloc inline data page");
				जाओ error_bio;
			पूर्ण

			ptr = kmap_atomic(page);
			स_नकल(ptr, data, pg_datalen);
			अगर (pg_sectorlen > pg_datalen)
				स_रखो(ptr + pg_datalen, 0, pg_sectorlen - pg_datalen);
			kunmap_atomic(ptr);

			ret = bio_add_page(bio, page, pg_sectorlen, 0);
			अगर (ret != pg_sectorlen) अणु
				DMERR("Couldn't add page of inline data");
				__मुक्त_page(page);
				जाओ error_bio;
			पूर्ण

			datalen -= pg_datalen;
			data	+= pg_datalen;
		पूर्ण
		submit_bio(bio);

		sector += bio_pages * PAGE_SECTORS;
	पूर्ण
	वापस 0;
error_bio:
	bio_मुक्त_pages(bio);
	bio_put(bio);
error:
	put_io_block(lc);
	वापस -1;
पूर्ण

अटल पूर्णांक log_one_block(काष्ठा log_ग_लिखोs_c *lc,
			 काष्ठा pending_block *block, sector_t sector)
अणु
	काष्ठा bio *bio;
	काष्ठा log_ग_लिखो_entry entry;
	माप_प्रकार metadatalen, ret;
	पूर्णांक i;

	entry.sector = cpu_to_le64(block->sector);
	entry.nr_sectors = cpu_to_le64(block->nr_sectors);
	entry.flags = cpu_to_le64(block->flags);
	entry.data_len = cpu_to_le64(block->datalen);

	metadatalen = (block->flags & LOG_MARK_FLAG) ? block->datalen : 0;
	अगर (ग_लिखो_metadata(lc, &entry, माप(entry), block->data,
			   metadatalen, sector)) अणु
		मुक्त_pending_block(lc, block);
		वापस -1;
	पूर्ण

	sector += dev_to_bio_sectors(lc, 1);

	अगर (block->datalen && metadatalen == 0) अणु
		अगर (ग_लिखो_अंतरभूत_data(lc, &entry, माप(entry), block->data,
				      block->datalen, sector)) अणु
			मुक्त_pending_block(lc, block);
			वापस -1;
		पूर्ण
		/* we करोn't support both अंतरभूत data & bio data */
		जाओ out;
	पूर्ण

	अगर (!block->vec_cnt)
		जाओ out;

	atomic_inc(&lc->io_blocks);
	bio = bio_alloc(GFP_KERNEL, bio_max_segs(block->vec_cnt));
	अगर (!bio) अणु
		DMERR("Couldn't alloc log bio");
		जाओ error;
	पूर्ण
	bio->bi_iter.bi_size = 0;
	bio->bi_iter.bi_sector = sector;
	bio_set_dev(bio, lc->logdev->bdev);
	bio->bi_end_io = log_end_io;
	bio->bi_निजी = lc;
	bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

	क्रम (i = 0; i < block->vec_cnt; i++) अणु
		/*
		 * The page offset is always 0 because we allocate a new page
		 * क्रम every bvec in the original bio क्रम simplicity sake.
		 */
		ret = bio_add_page(bio, block->vecs[i].bv_page,
				   block->vecs[i].bv_len, 0);
		अगर (ret != block->vecs[i].bv_len) अणु
			atomic_inc(&lc->io_blocks);
			submit_bio(bio);
			bio = bio_alloc(GFP_KERNEL,
					bio_max_segs(block->vec_cnt - i));
			अगर (!bio) अणु
				DMERR("Couldn't alloc log bio");
				जाओ error;
			पूर्ण
			bio->bi_iter.bi_size = 0;
			bio->bi_iter.bi_sector = sector;
			bio_set_dev(bio, lc->logdev->bdev);
			bio->bi_end_io = log_end_io;
			bio->bi_निजी = lc;
			bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

			ret = bio_add_page(bio, block->vecs[i].bv_page,
					   block->vecs[i].bv_len, 0);
			अगर (ret != block->vecs[i].bv_len) अणु
				DMERR("Couldn't add page on new bio?");
				bio_put(bio);
				जाओ error;
			पूर्ण
		पूर्ण
		sector += block->vecs[i].bv_len >> SECTOR_SHIFT;
	पूर्ण
	submit_bio(bio);
out:
	kमुक्त(block->data);
	kमुक्त(block);
	put_pending_block(lc);
	वापस 0;
error:
	मुक्त_pending_block(lc, block);
	put_io_block(lc);
	वापस -1;
पूर्ण

अटल पूर्णांक log_super(काष्ठा log_ग_लिखोs_c *lc)
अणु
	काष्ठा log_ग_लिखो_super super;

	super.magic = cpu_to_le64(WRITE_LOG_MAGIC);
	super.version = cpu_to_le64(WRITE_LOG_VERSION);
	super.nr_entries = cpu_to_le64(lc->logged_entries);
	super.sectorsize = cpu_to_le32(lc->sectorsize);

	अगर (ग_लिखो_metadata(lc, &super, माप(super), शून्य, 0,
			   WRITE_LOG_SUPER_SECTOR)) अणु
		DMERR("Couldn't write super");
		वापस -1;
	पूर्ण

	/*
	 * Super sector should be ग_लिखोn in-order, otherwise the
	 * nr_entries could be rewritten incorrectly by an old bio.
	 */
	रुको_क्रम_completion_io(&lc->super_करोne);

	वापस 0;
पूर्ण

अटल अंतरभूत sector_t logdev_last_sector(काष्ठा log_ग_लिखोs_c *lc)
अणु
	वापस i_size_पढ़ो(lc->logdev->bdev->bd_inode) >> SECTOR_SHIFT;
पूर्ण

अटल पूर्णांक log_ग_लिखोs_kthपढ़ो(व्योम *arg)
अणु
	काष्ठा log_ग_लिखोs_c *lc = (काष्ठा log_ग_लिखोs_c *)arg;
	sector_t sector = 0;

	जबतक (!kthपढ़ो_should_stop()) अणु
		bool super = false;
		bool logging_enabled;
		काष्ठा pending_block *block = शून्य;
		पूर्णांक ret;

		spin_lock_irq(&lc->blocks_lock);
		अगर (!list_empty(&lc->logging_blocks)) अणु
			block = list_first_entry(&lc->logging_blocks,
						 काष्ठा pending_block, list);
			list_del_init(&block->list);
			अगर (!lc->logging_enabled)
				जाओ next;

			sector = lc->next_sector;
			अगर (!(block->flags & LOG_DISCARD_FLAG))
				lc->next_sector += dev_to_bio_sectors(lc, block->nr_sectors);
			lc->next_sector += dev_to_bio_sectors(lc, 1);

			/*
			 * Apparently the size of the device may not be known
			 * right away, so handle this properly.
			 */
			अगर (!lc->end_sector)
				lc->end_sector = logdev_last_sector(lc);
			अगर (lc->end_sector &&
			    lc->next_sector >= lc->end_sector) अणु
				DMERR("Ran out of space on the logdev");
				lc->logging_enabled = false;
				जाओ next;
			पूर्ण
			lc->logged_entries++;
			atomic_inc(&lc->io_blocks);

			super = (block->flags & (LOG_FUA_FLAG | LOG_MARK_FLAG));
			अगर (super)
				atomic_inc(&lc->io_blocks);
		पूर्ण
next:
		logging_enabled = lc->logging_enabled;
		spin_unlock_irq(&lc->blocks_lock);
		अगर (block) अणु
			अगर (logging_enabled) अणु
				ret = log_one_block(lc, block, sector);
				अगर (!ret && super)
					ret = log_super(lc);
				अगर (ret) अणु
					spin_lock_irq(&lc->blocks_lock);
					lc->logging_enabled = false;
					spin_unlock_irq(&lc->blocks_lock);
				पूर्ण
			पूर्ण अन्यथा
				मुक्त_pending_block(lc, block);
			जारी;
		पूर्ण

		अगर (!try_to_मुक्तze()) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			अगर (!kthपढ़ो_should_stop() &&
			    list_empty(&lc->logging_blocks))
				schedule();
			__set_current_state(TASK_RUNNING);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Conकाष्ठा a log-ग_लिखोs mapping:
 * log-ग_लिखोs <dev_path> <log_dev_path>
 */
अटल पूर्णांक log_ग_लिखोs_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा log_ग_लिखोs_c *lc;
	काष्ठा dm_arg_set as;
	स्थिर अक्षर *devname, *logdevname;
	पूर्णांक ret;

	as.argc = argc;
	as.argv = argv;

	अगर (argc < 2) अणु
		ti->error = "Invalid argument count";
		वापस -EINVAL;
	पूर्ण

	lc = kzalloc(माप(काष्ठा log_ग_लिखोs_c), GFP_KERNEL);
	अगर (!lc) अणु
		ti->error = "Cannot allocate context";
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&lc->blocks_lock);
	INIT_LIST_HEAD(&lc->unflushed_blocks);
	INIT_LIST_HEAD(&lc->logging_blocks);
	init_रुकोqueue_head(&lc->रुको);
	init_completion(&lc->super_करोne);
	atomic_set(&lc->io_blocks, 0);
	atomic_set(&lc->pending_blocks, 0);

	devname = dm_shअगरt_arg(&as);
	ret = dm_get_device(ti, devname, dm_table_get_mode(ti->table), &lc->dev);
	अगर (ret) अणु
		ti->error = "Device lookup failed";
		जाओ bad;
	पूर्ण

	logdevname = dm_shअगरt_arg(&as);
	ret = dm_get_device(ti, logdevname, dm_table_get_mode(ti->table),
			    &lc->logdev);
	अगर (ret) अणु
		ti->error = "Log device lookup failed";
		dm_put_device(ti, lc->dev);
		जाओ bad;
	पूर्ण

	lc->sectorsize = bdev_logical_block_size(lc->dev->bdev);
	lc->sectorshअगरt = ilog2(lc->sectorsize);
	lc->log_kthपढ़ो = kthपढ़ो_run(log_ग_लिखोs_kthपढ़ो, lc, "log-write");
	अगर (IS_ERR(lc->log_kthपढ़ो)) अणु
		ret = PTR_ERR(lc->log_kthपढ़ो);
		ti->error = "Couldn't alloc kthread";
		dm_put_device(ti, lc->dev);
		dm_put_device(ti, lc->logdev);
		जाओ bad;
	पूर्ण

	/*
	 * next_sector is in 512b sectors to correspond to what bi_sector expects.
	 * The super starts at sector 0, and the next_sector is the next logical
	 * one based on the sectorsize of the device.
	 */
	lc->next_sector = lc->sectorsize >> SECTOR_SHIFT;
	lc->logging_enabled = true;
	lc->end_sector = logdev_last_sector(lc);
	lc->device_supports_discard = true;

	ti->num_flush_bios = 1;
	ti->flush_supported = true;
	ti->num_discard_bios = 1;
	ti->discards_supported = true;
	ti->per_io_data_size = माप(काष्ठा per_bio_data);
	ti->निजी = lc;
	वापस 0;

bad:
	kमुक्त(lc);
	वापस ret;
पूर्ण

अटल पूर्णांक log_mark(काष्ठा log_ग_लिखोs_c *lc, अक्षर *data)
अणु
	काष्ठा pending_block *block;
	माप_प्रकार maxsize = lc->sectorsize - माप(काष्ठा log_ग_लिखो_entry);

	block = kzalloc(माप(काष्ठा pending_block), GFP_KERNEL);
	अगर (!block) अणु
		DMERR("Error allocating pending block");
		वापस -ENOMEM;
	पूर्ण

	block->data = kstrndup(data, maxsize - 1, GFP_KERNEL);
	अगर (!block->data) अणु
		DMERR("Error copying mark data");
		kमुक्त(block);
		वापस -ENOMEM;
	पूर्ण
	atomic_inc(&lc->pending_blocks);
	block->datalen = म_माप(block->data);
	block->flags |= LOG_MARK_FLAG;
	spin_lock_irq(&lc->blocks_lock);
	list_add_tail(&block->list, &lc->logging_blocks);
	spin_unlock_irq(&lc->blocks_lock);
	wake_up_process(lc->log_kthपढ़ो);
	वापस 0;
पूर्ण

अटल व्योम log_ग_लिखोs_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;

	spin_lock_irq(&lc->blocks_lock);
	list_splice_init(&lc->unflushed_blocks, &lc->logging_blocks);
	spin_unlock_irq(&lc->blocks_lock);

	/*
	 * This is just nice to have since it'll update the super to include the
	 * unflushed blocks, अगर it fails we करोn't really care.
	 */
	log_mark(lc, "dm-log-writes-end");
	wake_up_process(lc->log_kthपढ़ो);
	रुको_event(lc->रुको, !atomic_पढ़ो(&lc->io_blocks) &&
		   !atomic_पढ़ो(&lc->pending_blocks));
	kthपढ़ो_stop(lc->log_kthपढ़ो);

	WARN_ON(!list_empty(&lc->logging_blocks));
	WARN_ON(!list_empty(&lc->unflushed_blocks));
	dm_put_device(ti, lc->dev);
	dm_put_device(ti, lc->logdev);
	kमुक्त(lc);
पूर्ण

अटल व्योम normal_map_bio(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;

	bio_set_dev(bio, lc->dev->bdev);
पूर्ण

अटल पूर्णांक log_ग_लिखोs_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;
	काष्ठा per_bio_data *pb = dm_per_bio_data(bio, माप(काष्ठा per_bio_data));
	काष्ठा pending_block *block;
	काष्ठा bvec_iter iter;
	काष्ठा bio_vec bv;
	माप_प्रकार alloc_size;
	पूर्णांक i = 0;
	bool flush_bio = (bio->bi_opf & REQ_PREFLUSH);
	bool fua_bio = (bio->bi_opf & REQ_FUA);
	bool discard_bio = (bio_op(bio) == REQ_OP_DISCARD);
	bool meta_bio = (bio->bi_opf & REQ_META);

	pb->block = शून्य;

	/* Don't bother करोing anything अगर logging has been disabled */
	अगर (!lc->logging_enabled)
		जाओ map_bio;

	/*
	 * Map पढ़ोs as normal.
	 */
	अगर (bio_data_dir(bio) == READ)
		जाओ map_bio;

	/* No sectors and not a flush?  Don't care */
	अगर (!bio_sectors(bio) && !flush_bio)
		जाओ map_bio;

	/*
	 * Discards will have bi_size set but there's no actual data, so just
	 * allocate the size of the pending block.
	 */
	अगर (discard_bio)
		alloc_size = माप(काष्ठा pending_block);
	अन्यथा
		alloc_size = काष्ठा_size(block, vecs, bio_segments(bio));

	block = kzalloc(alloc_size, GFP_NOIO);
	अगर (!block) अणु
		DMERR("Error allocating pending block");
		spin_lock_irq(&lc->blocks_lock);
		lc->logging_enabled = false;
		spin_unlock_irq(&lc->blocks_lock);
		वापस DM_MAPIO_KILL;
	पूर्ण
	INIT_LIST_HEAD(&block->list);
	pb->block = block;
	atomic_inc(&lc->pending_blocks);

	अगर (flush_bio)
		block->flags |= LOG_FLUSH_FLAG;
	अगर (fua_bio)
		block->flags |= LOG_FUA_FLAG;
	अगर (discard_bio)
		block->flags |= LOG_DISCARD_FLAG;
	अगर (meta_bio)
		block->flags |= LOG_METADATA_FLAG;

	block->sector = bio_to_dev_sectors(lc, bio->bi_iter.bi_sector);
	block->nr_sectors = bio_to_dev_sectors(lc, bio_sectors(bio));

	/* We करोn't need the data, just submit */
	अगर (discard_bio) अणु
		WARN_ON(flush_bio || fua_bio);
		अगर (lc->device_supports_discard)
			जाओ map_bio;
		bio_endio(bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	/* Flush bio, splice the unflushed blocks onto this list and submit */
	अगर (flush_bio && !bio_sectors(bio)) अणु
		spin_lock_irq(&lc->blocks_lock);
		list_splice_init(&lc->unflushed_blocks, &block->list);
		spin_unlock_irq(&lc->blocks_lock);
		जाओ map_bio;
	पूर्ण

	/*
	 * We will ग_लिखो this bio somewhere अन्यथा way later so we need to copy
	 * the actual contents पूर्णांकo new pages so we know the data will always be
	 * there.
	 *
	 * We करो this because this could be a bio from O_सूचीECT in which हाल we
	 * can't just hold onto the page until some later poपूर्णांक, we have to
	 * manually copy the contents.
	 */
	bio_क्रम_each_segment(bv, bio, iter) अणु
		काष्ठा page *page;
		व्योम *src, *dst;

		page = alloc_page(GFP_NOIO);
		अगर (!page) अणु
			DMERR("Error allocing page");
			मुक्त_pending_block(lc, block);
			spin_lock_irq(&lc->blocks_lock);
			lc->logging_enabled = false;
			spin_unlock_irq(&lc->blocks_lock);
			वापस DM_MAPIO_KILL;
		पूर्ण

		src = kmap_atomic(bv.bv_page);
		dst = kmap_atomic(page);
		स_नकल(dst, src + bv.bv_offset, bv.bv_len);
		kunmap_atomic(dst);
		kunmap_atomic(src);
		block->vecs[i].bv_page = page;
		block->vecs[i].bv_len = bv.bv_len;
		block->vec_cnt++;
		i++;
	पूर्ण

	/* Had a flush with data in it, weird */
	अगर (flush_bio) अणु
		spin_lock_irq(&lc->blocks_lock);
		list_splice_init(&lc->unflushed_blocks, &block->list);
		spin_unlock_irq(&lc->blocks_lock);
	पूर्ण
map_bio:
	normal_map_bio(ti, bio);
	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल पूर्णांक normal_end_io(काष्ठा dm_target *ti, काष्ठा bio *bio,
		blk_status_t *error)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;
	काष्ठा per_bio_data *pb = dm_per_bio_data(bio, माप(काष्ठा per_bio_data));

	अगर (bio_data_dir(bio) == WRITE && pb->block) अणु
		काष्ठा pending_block *block = pb->block;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&lc->blocks_lock, flags);
		अगर (block->flags & LOG_FLUSH_FLAG) अणु
			list_splice_tail_init(&block->list, &lc->logging_blocks);
			list_add_tail(&block->list, &lc->logging_blocks);
			wake_up_process(lc->log_kthपढ़ो);
		पूर्ण अन्यथा अगर (block->flags & LOG_FUA_FLAG) अणु
			list_add_tail(&block->list, &lc->logging_blocks);
			wake_up_process(lc->log_kthपढ़ो);
		पूर्ण अन्यथा
			list_add_tail(&block->list, &lc->unflushed_blocks);
		spin_unlock_irqrestore(&lc->blocks_lock, flags);
	पूर्ण

	वापस DM_ENDIO_DONE;
पूर्ण

/*
 * INFO क्रमmat: <logged entries> <highest allocated sector>
 */
अटल व्योम log_ग_लिखोs_status(काष्ठा dm_target *ti, status_type_t type,
			      अचिन्हित status_flags, अक्षर *result,
			      अचिन्हित maxlen)
अणु
	अचिन्हित sz = 0;
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%llu %llu", lc->logged_entries,
		       (अचिन्हित दीर्घ दीर्घ)lc->next_sector - 1);
		अगर (!lc->logging_enabled)
			DMEMIT(" logging_disabled");
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%s %s", lc->dev->name, lc->logdev->name);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक log_ग_लिखोs_prepare_ioctl(काष्ठा dm_target *ti,
				    काष्ठा block_device **bdev)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;
	काष्ठा dm_dev *dev = lc->dev;

	*bdev = dev->bdev;
	/*
	 * Only pass ioctls through अगर the device sizes match exactly.
	 */
	अगर (ti->len != i_size_पढ़ो(dev->bdev->bd_inode) >> SECTOR_SHIFT)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक log_ग_लिखोs_iterate_devices(काष्ठा dm_target *ti,
				      iterate_devices_callout_fn fn,
				      व्योम *data)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;

	वापस fn(ti, lc->dev, 0, ti->len, data);
पूर्ण

/*
 * Messages supported:
 *   mark <mark data> - specअगरy the marked data.
 */
अटल पूर्णांक log_ग_लिखोs_message(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv,
			      अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;

	अगर (argc != 2) अणु
		DMWARN("Invalid log-writes message arguments, expect 2 arguments, got %d", argc);
		वापस r;
	पूर्ण

	अगर (!strहालcmp(argv[0], "mark"))
		r = log_mark(lc, argv[1]);
	अन्यथा
		DMWARN("Unrecognised log writes target message received: %s", argv[0]);

	वापस r;
पूर्ण

अटल व्योम log_ग_लिखोs_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;
	काष्ठा request_queue *q = bdev_get_queue(lc->dev->bdev);

	अगर (!q || !blk_queue_discard(q)) अणु
		lc->device_supports_discard = false;
		limits->discard_granularity = lc->sectorsize;
		limits->max_discard_sectors = (अच_पूर्णांक_उच्च >> SECTOR_SHIFT);
	पूर्ण
	limits->logical_block_size = bdev_logical_block_size(lc->dev->bdev);
	limits->physical_block_size = bdev_physical_block_size(lc->dev->bdev);
	limits->io_min = limits->physical_block_size;
पूर्ण

#अगर IS_ENABLED(CONFIG_DAX_DRIVER)
अटल पूर्णांक log_dax(काष्ठा log_ग_लिखोs_c *lc, sector_t sector, माप_प्रकार bytes,
		   काष्ठा iov_iter *i)
अणु
	काष्ठा pending_block *block;

	अगर (!bytes)
		वापस 0;

	block = kzalloc(माप(काष्ठा pending_block), GFP_KERNEL);
	अगर (!block) अणु
		DMERR("Error allocating dax pending block");
		वापस -ENOMEM;
	पूर्ण

	block->data = kzalloc(bytes, GFP_KERNEL);
	अगर (!block->data) अणु
		DMERR("Error allocating dax data space");
		kमुक्त(block);
		वापस -ENOMEM;
	पूर्ण

	/* ग_लिखो data provided via the iterator */
	अगर (!copy_from_iter(block->data, bytes, i)) अणु
		DMERR("Error copying dax data");
		kमुक्त(block->data);
		kमुक्त(block);
		वापस -EIO;
	पूर्ण

	/* शुरुआत the iterator so that the block driver can use it */
	iov_iter_revert(i, bytes);

	block->datalen = bytes;
	block->sector = bio_to_dev_sectors(lc, sector);
	block->nr_sectors = ALIGN(bytes, lc->sectorsize) >> lc->sectorshअगरt;

	atomic_inc(&lc->pending_blocks);
	spin_lock_irq(&lc->blocks_lock);
	list_add_tail(&block->list, &lc->unflushed_blocks);
	spin_unlock_irq(&lc->blocks_lock);
	wake_up_process(lc->log_kthपढ़ो);

	वापस 0;
पूर्ण

अटल दीर्घ log_ग_लिखोs_dax_direct_access(काष्ठा dm_target *ti, pgoff_t pgoff,
					 दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;
	sector_t sector = pgoff * PAGE_SECTORS;
	पूर्णांक ret;

	ret = bdev_dax_pgoff(lc->dev->bdev, sector, nr_pages * PAGE_SIZE, &pgoff);
	अगर (ret)
		वापस ret;
	वापस dax_direct_access(lc->dev->dax_dev, pgoff, nr_pages, kaddr, pfn);
पूर्ण

अटल माप_प्रकार log_ग_लिखोs_dax_copy_from_iter(काष्ठा dm_target *ti,
					    pgoff_t pgoff, व्योम *addr, माप_प्रकार bytes,
					    काष्ठा iov_iter *i)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;
	sector_t sector = pgoff * PAGE_SECTORS;
	पूर्णांक err;

	अगर (bdev_dax_pgoff(lc->dev->bdev, sector, ALIGN(bytes, PAGE_SIZE), &pgoff))
		वापस 0;

	/* Don't bother करोing anything अगर logging has been disabled */
	अगर (!lc->logging_enabled)
		जाओ dax_copy;

	err = log_dax(lc, sector, bytes, i);
	अगर (err) अणु
		DMWARN("Error %d logging DAX write", err);
		वापस 0;
	पूर्ण
dax_copy:
	वापस dax_copy_from_iter(lc->dev->dax_dev, pgoff, addr, bytes, i);
पूर्ण

अटल माप_प्रकार log_ग_लिखोs_dax_copy_to_iter(काष्ठा dm_target *ti,
					  pgoff_t pgoff, व्योम *addr, माप_प्रकार bytes,
					  काष्ठा iov_iter *i)
अणु
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;
	sector_t sector = pgoff * PAGE_SECTORS;

	अगर (bdev_dax_pgoff(lc->dev->bdev, sector, ALIGN(bytes, PAGE_SIZE), &pgoff))
		वापस 0;
	वापस dax_copy_to_iter(lc->dev->dax_dev, pgoff, addr, bytes, i);
पूर्ण

अटल पूर्णांक log_ग_लिखोs_dax_zero_page_range(काष्ठा dm_target *ti, pgoff_t pgoff,
					  माप_प्रकार nr_pages)
अणु
	पूर्णांक ret;
	काष्ठा log_ग_लिखोs_c *lc = ti->निजी;
	sector_t sector = pgoff * PAGE_SECTORS;

	ret = bdev_dax_pgoff(lc->dev->bdev, sector, nr_pages << PAGE_SHIFT,
			     &pgoff);
	अगर (ret)
		वापस ret;
	वापस dax_zero_page_range(lc->dev->dax_dev, pgoff,
				   nr_pages << PAGE_SHIFT);
पूर्ण

#अन्यथा
#घोषणा log_ग_लिखोs_dax_direct_access शून्य
#घोषणा log_ग_लिखोs_dax_copy_from_iter शून्य
#घोषणा log_ग_लिखोs_dax_copy_to_iter शून्य
#घोषणा log_ग_लिखोs_dax_zero_page_range शून्य
#पूर्ण_अगर

अटल काष्ठा target_type log_ग_लिखोs_target = अणु
	.name   = "log-writes",
	.version = अणु1, 1, 0पूर्ण,
	.module = THIS_MODULE,
	.ctr    = log_ग_लिखोs_ctr,
	.dtr    = log_ग_लिखोs_dtr,
	.map    = log_ग_लिखोs_map,
	.end_io = normal_end_io,
	.status = log_ग_लिखोs_status,
	.prepare_ioctl = log_ग_लिखोs_prepare_ioctl,
	.message = log_ग_लिखोs_message,
	.iterate_devices = log_ग_लिखोs_iterate_devices,
	.io_hपूर्णांकs = log_ग_लिखोs_io_hपूर्णांकs,
	.direct_access = log_ग_लिखोs_dax_direct_access,
	.dax_copy_from_iter = log_ग_लिखोs_dax_copy_from_iter,
	.dax_copy_to_iter = log_ग_लिखोs_dax_copy_to_iter,
	.dax_zero_page_range = log_ग_लिखोs_dax_zero_page_range,
पूर्ण;

अटल पूर्णांक __init dm_log_ग_लिखोs_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_target(&log_ग_लिखोs_target);

	अगर (r < 0)
		DMERR("register failed %d", r);

	वापस r;
पूर्ण

अटल व्योम __निकास dm_log_ग_लिखोs_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&log_ग_लिखोs_target);
पूर्ण

module_init(dm_log_ग_लिखोs_init);
module_निकास(dm_log_ग_लिखोs_निकास);

MODULE_DESCRIPTION(DM_NAME " log writes target");
MODULE_AUTHOR("Josef Bacik <jbacik@fb.com>");
MODULE_LICENSE("GPL");
