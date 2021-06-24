<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
* Filename: dev.c
*
* Authors: Joshua Morris <josh.h.morris@us.ibm.com>
*	Philip Kelleher <pjk1939@linux.vnet.ibm.com>
*
* (C) Copyright 2013 IBM Corporation
*/

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <linux/hdreg.h>
#समावेश <linux/genhd.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>

#समावेश <linux/fs.h>

#समावेश "rsxx_priv.h"

अटल अचिन्हित पूर्णांक blkdev_minors = 64;
module_param(blkdev_minors, uपूर्णांक, 0444);
MODULE_PARM_DESC(blkdev_minors, "Number of minors(partitions)");

/*
 * For now I'm making this tweakable in हाल any applications hit this limit.
 * If you see a "bio too big" error in the log you will need to उठाओ this
 * value.
 */
अटल अचिन्हित पूर्णांक blkdev_max_hw_sectors = 1024;
module_param(blkdev_max_hw_sectors, uपूर्णांक, 0444);
MODULE_PARM_DESC(blkdev_max_hw_sectors, "Max hw sectors for a single BIO");

अटल अचिन्हित पूर्णांक enable_blkdev = 1;
module_param(enable_blkdev , uपूर्णांक, 0444);
MODULE_PARM_DESC(enable_blkdev, "Enable block device interfaces");


काष्ठा rsxx_bio_meta अणु
	काष्ठा bio	*bio;
	atomic_t	pending_dmas;
	atomic_t	error;
	अचिन्हित दीर्घ	start_समय;
पूर्ण;

अटल काष्ठा kmem_cache *bio_meta_pool;

अटल blk_qc_t rsxx_submit_bio(काष्ठा bio *bio);

/*----------------- Block Device Operations -----------------*/
अटल पूर्णांक rsxx_blkdev_ioctl(काष्ठा block_device *bdev,
				 भ_शेषe_t mode,
				 अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा rsxx_cardinfo *card = bdev->bd_disk->निजी_data;

	चयन (cmd) अणु
	हाल RSXX_GETREG:
		वापस rsxx_reg_access(card, (व्योम __user *)arg, 1);
	हाल RSXX_SETREG:
		वापस rsxx_reg_access(card, (व्योम __user *)arg, 0);
	पूर्ण

	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक rsxx_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा rsxx_cardinfo *card = bdev->bd_disk->निजी_data;
	u64 blocks = card->size8 >> 9;

	/*
	 * get geometry: Fake it. I haven't found any drivers that set
	 * geo->start, so we won't either.
	 */
	अगर (card->size8) अणु
		geo->heads = 64;
		geo->sectors = 16;
		करो_भाग(blocks, (geo->heads * geo->sectors));
		geo->cylinders = blocks;
	पूर्ण अन्यथा अणु
		geo->heads = 0;
		geo->sectors = 0;
		geo->cylinders = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations rsxx_fops = अणु
	.owner		= THIS_MODULE,
	.submit_bio	= rsxx_submit_bio,
	.getgeo		= rsxx_getgeo,
	.ioctl		= rsxx_blkdev_ioctl,
पूर्ण;

अटल व्योम bio_dma_करोne_cb(काष्ठा rsxx_cardinfo *card,
			    व्योम *cb_data,
			    अचिन्हित पूर्णांक error)
अणु
	काष्ठा rsxx_bio_meta *meta = cb_data;

	अगर (error)
		atomic_set(&meta->error, 1);

	अगर (atomic_dec_and_test(&meta->pending_dmas)) अणु
		अगर (!card->eeh_state && card->gendisk)
			bio_end_io_acct(meta->bio, meta->start_समय);

		अगर (atomic_पढ़ो(&meta->error))
			bio_io_error(meta->bio);
		अन्यथा
			bio_endio(meta->bio);
		kmem_cache_मुक्त(bio_meta_pool, meta);
	पूर्ण
पूर्ण

अटल blk_qc_t rsxx_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा rsxx_cardinfo *card = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा rsxx_bio_meta *bio_meta;
	blk_status_t st = BLK_STS_IOERR;

	blk_queue_split(&bio);

	might_sleep();

	अगर (!card)
		जाओ req_err;

	अगर (bio_end_sector(bio) > get_capacity(card->gendisk))
		जाओ req_err;

	अगर (unlikely(card->halt))
		जाओ req_err;

	अगर (unlikely(card->dma_fault))
		जाओ req_err;

	अगर (bio->bi_iter.bi_size == 0) अणु
		dev_err(CARD_TO_DEV(card), "size zero BIO!\n");
		जाओ req_err;
	पूर्ण

	bio_meta = kmem_cache_alloc(bio_meta_pool, GFP_KERNEL);
	अगर (!bio_meta) अणु
		st = BLK_STS_RESOURCE;
		जाओ req_err;
	पूर्ण

	bio_meta->bio = bio;
	atomic_set(&bio_meta->error, 0);
	atomic_set(&bio_meta->pending_dmas, 0);

	अगर (!unlikely(card->halt))
		bio_meta->start_समय = bio_start_io_acct(bio);

	dev_dbg(CARD_TO_DEV(card), "BIO[%c]: meta: %p addr8: x%llx size: %d\n",
		 bio_data_dir(bio) ? 'W' : 'R', bio_meta,
		 (u64)bio->bi_iter.bi_sector << 9, bio->bi_iter.bi_size);

	st = rsxx_dma_queue_bio(card, bio, &bio_meta->pending_dmas,
				    bio_dma_करोne_cb, bio_meta);
	अगर (st)
		जाओ queue_err;

	वापस BLK_QC_T_NONE;

queue_err:
	kmem_cache_मुक्त(bio_meta_pool, bio_meta);
req_err:
	अगर (st)
		bio->bi_status = st;
	bio_endio(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

/*----------------- Device Setup -------------------*/
अटल bool rsxx_discard_supported(काष्ठा rsxx_cardinfo *card)
अणु
	अचिन्हित अक्षर pci_rev;

	pci_पढ़ो_config_byte(card->dev, PCI_REVISION_ID, &pci_rev);

	वापस (pci_rev >= RSXX_DISCARD_SUPPORT);
पूर्ण

पूर्णांक rsxx_attach_dev(काष्ठा rsxx_cardinfo *card)
अणु
	mutex_lock(&card->dev_lock);

	/* The block device requires the stripe size from the config. */
	अगर (enable_blkdev) अणु
		अगर (card->config_valid)
			set_capacity(card->gendisk, card->size8 >> 9);
		अन्यथा
			set_capacity(card->gendisk, 0);
		device_add_disk(CARD_TO_DEV(card), card->gendisk, शून्य);
		card->bdev_attached = 1;
	पूर्ण

	mutex_unlock(&card->dev_lock);

	वापस 0;
पूर्ण

व्योम rsxx_detach_dev(काष्ठा rsxx_cardinfo *card)
अणु
	mutex_lock(&card->dev_lock);

	अगर (card->bdev_attached) अणु
		del_gendisk(card->gendisk);
		card->bdev_attached = 0;
	पूर्ण

	mutex_unlock(&card->dev_lock);
पूर्ण

पूर्णांक rsxx_setup_dev(काष्ठा rsxx_cardinfo *card)
अणु
	अचिन्हित लघु blk_size;

	mutex_init(&card->dev_lock);

	अगर (!enable_blkdev)
		वापस 0;

	card->major = रेजिस्टर_blkdev(0, DRIVER_NAME);
	अगर (card->major < 0) अणु
		dev_err(CARD_TO_DEV(card), "Failed to get major number\n");
		वापस -ENOMEM;
	पूर्ण

	card->queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!card->queue) अणु
		dev_err(CARD_TO_DEV(card), "Failed queue alloc\n");
		unरेजिस्टर_blkdev(card->major, DRIVER_NAME);
		वापस -ENOMEM;
	पूर्ण

	card->gendisk = alloc_disk(blkdev_minors);
	अगर (!card->gendisk) अणु
		dev_err(CARD_TO_DEV(card), "Failed disk alloc\n");
		blk_cleanup_queue(card->queue);
		unरेजिस्टर_blkdev(card->major, DRIVER_NAME);
		वापस -ENOMEM;
	पूर्ण

	अगर (card->config_valid) अणु
		blk_size = card->config.data.block_size;
		blk_queue_dma_alignment(card->queue, blk_size - 1);
		blk_queue_logical_block_size(card->queue, blk_size);
	पूर्ण

	blk_queue_max_hw_sectors(card->queue, blkdev_max_hw_sectors);
	blk_queue_physical_block_size(card->queue, RSXX_HW_BLK_SIZE);

	blk_queue_flag_set(QUEUE_FLAG_NONROT, card->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, card->queue);
	अगर (rsxx_discard_supported(card)) अणु
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, card->queue);
		blk_queue_max_discard_sectors(card->queue,
						RSXX_HW_BLK_SIZE >> 9);
		card->queue->limits.discard_granularity = RSXX_HW_BLK_SIZE;
		card->queue->limits.discard_alignment   = RSXX_HW_BLK_SIZE;
	पूर्ण

	snम_लिखो(card->gendisk->disk_name, माप(card->gendisk->disk_name),
		 "rsxx%d", card->disk_id);
	card->gendisk->major = card->major;
	card->gendisk->first_minor = 0;
	card->gendisk->fops = &rsxx_fops;
	card->gendisk->निजी_data = card;
	card->gendisk->queue = card->queue;

	वापस 0;
पूर्ण

व्योम rsxx_destroy_dev(काष्ठा rsxx_cardinfo *card)
अणु
	अगर (!enable_blkdev)
		वापस;

	put_disk(card->gendisk);
	card->gendisk = शून्य;

	blk_cleanup_queue(card->queue);
	unरेजिस्टर_blkdev(card->major, DRIVER_NAME);
पूर्ण

पूर्णांक rsxx_dev_init(व्योम)
अणु
	bio_meta_pool = KMEM_CACHE(rsxx_bio_meta, SLAB_HWCACHE_ALIGN);
	अगर (!bio_meta_pool)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम rsxx_dev_cleanup(व्योम)
अणु
	kmem_cache_destroy(bio_meta_pool);
पूर्ण


