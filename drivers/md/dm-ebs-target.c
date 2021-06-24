<शैली गुरु>
/*
 * Copyright (C) 2020 Red Hat GmbH
 *
 * This file is released under the GPL.
 *
 * Device-mapper target to emulate smaller logical block
 * size on backing devices exposing (natively) larger ones.
 *
 * E.g. 512 byte sector emulation on 4K native disks.
 */

#समावेश "dm.h"
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/dm-bufपन.स>

#घोषणा DM_MSG_PREFIX "ebs"

अटल व्योम ebs_dtr(काष्ठा dm_target *ti);

/* Emulated block size context. */
काष्ठा ebs_c अणु
	काष्ठा dm_dev *dev;		/* Underlying device to emulate block size on. */
	काष्ठा dm_bufio_client *bufio;	/* Use dm-bufio क्रम पढ़ो and पढ़ो-modअगरy-ग_लिखो processing. */
	काष्ठा workqueue_काष्ठा *wq;	/* Workqueue क्रम ^ processing of bios. */
	काष्ठा work_काष्ठा ws;		/* Work item used क्रम ^. */
	काष्ठा bio_list bios_in;	/* Worker bios input list. */
	spinlock_t lock;		/* Guard bios input list above. */
	sector_t start;			/* <start> table line argument, see ebs_ctr below. */
	अचिन्हित पूर्णांक e_bs;		/* Emulated block size in sectors exposed to upper layer. */
	अचिन्हित पूर्णांक u_bs;		/* Underlying block size in sectors retrieved from/set on lower layer device. */
	अचिन्हित अक्षर block_shअगरt;	/* bitshअगरt sectors -> blocks used in dm-bufio API. */
	bool u_bs_set:1;		/* Flag to indicate underlying block size is set on table line. */
पूर्ण;

अटल अंतरभूत sector_t __sector_to_block(काष्ठा ebs_c *ec, sector_t sector)
अणु
	वापस sector >> ec->block_shअगरt;
पूर्ण

अटल अंतरभूत sector_t __block_mod(sector_t sector, अचिन्हित पूर्णांक bs)
अणु
	वापस sector & (bs - 1);
पूर्ण

/* Return number of blocks क्रम a bio, accounting क्रम misalignment of start and end sectors. */
अटल अंतरभूत अचिन्हित पूर्णांक __nr_blocks(काष्ठा ebs_c *ec, काष्ठा bio *bio)
अणु
	sector_t end_sector = __block_mod(bio->bi_iter.bi_sector, ec->u_bs) + bio_sectors(bio);

	वापस __sector_to_block(ec, end_sector) + (__block_mod(end_sector, ec->u_bs) ? 1 : 0);
पूर्ण

अटल अंतरभूत bool __ebs_check_bs(अचिन्हित पूर्णांक bs)
अणु
	वापस bs && is_घातer_of_2(bs);
पूर्ण

/*
 * READ/WRITE:
 *
 * copy blocks between bufio blocks and bio vector's (partial/overlapping) pages.
 */
अटल पूर्णांक __ebs_rw_bvec(काष्ठा ebs_c *ec, पूर्णांक rw, काष्ठा bio_vec *bv, काष्ठा bvec_iter *iter)
अणु
	पूर्णांक r = 0;
	अचिन्हित अक्षर *ba, *pa;
	अचिन्हित पूर्णांक cur_len;
	अचिन्हित पूर्णांक bv_len = bv->bv_len;
	अचिन्हित पूर्णांक buf_off = to_bytes(__block_mod(iter->bi_sector, ec->u_bs));
	sector_t block = __sector_to_block(ec, iter->bi_sector);
	काष्ठा dm_buffer *b;

	अगर (unlikely(!bv->bv_page || !bv_len))
		वापस -EIO;

	pa = page_address(bv->bv_page) + bv->bv_offset;

	/* Handle overlapping page <-> blocks */
	जबतक (bv_len) अणु
		cur_len = min(dm_bufio_get_block_size(ec->bufio) - buf_off, bv_len);

		/* Aव्योम पढ़ोing क्रम ग_लिखोs in हाल bio vector's page overग_लिखोs block completely. */
		अगर (rw == READ || buf_off || bv_len < dm_bufio_get_block_size(ec->bufio))
			ba = dm_bufio_पढ़ो(ec->bufio, block, &b);
		अन्यथा
			ba = dm_bufio_new(ec->bufio, block, &b);

		अगर (IS_ERR(ba)) अणु
			/*
			 * Carry on with next buffer, अगर any, to issue all possible
			 * data but वापस error.
			 */
			r = PTR_ERR(ba);
		पूर्ण अन्यथा अणु
			/* Copy data to/from bio to buffer अगर पढ़ो/new was successful above. */
			ba += buf_off;
			अगर (rw == READ) अणु
				स_नकल(pa, ba, cur_len);
				flush_dcache_page(bv->bv_page);
			पूर्ण अन्यथा अणु
				flush_dcache_page(bv->bv_page);
				स_नकल(ba, pa, cur_len);
				dm_bufio_mark_partial_buffer_dirty(b, buf_off, buf_off + cur_len);
			पूर्ण

			dm_bufio_release(b);
		पूर्ण

		pa += cur_len;
		bv_len -= cur_len;
		buf_off = 0;
		block++;
	पूर्ण

	वापस r;
पूर्ण

/* READ/WRITE: iterate bio vector's copying between (partial) pages and bufio blocks. */
अटल पूर्णांक __ebs_rw_bio(काष्ठा ebs_c *ec, पूर्णांक rw, काष्ठा bio *bio)
अणु
	पूर्णांक r = 0, rr;
	काष्ठा bio_vec bv;
	काष्ठा bvec_iter iter;

	bio_क्रम_each_bvec(bv, bio, iter) अणु
		rr = __ebs_rw_bvec(ec, rw, &bv, &iter);
		अगर (rr)
			r = rr;
	पूर्ण

	वापस r;
पूर्ण

/*
 * Discard bio's blocks, i.e. pass discards करोwn.
 *
 * Aव्योम discarding partial blocks at beginning and end;
 * वापस 0 in हाल no blocks can be discarded as a result.
 */
अटल पूर्णांक __ebs_discard_bio(काष्ठा ebs_c *ec, काष्ठा bio *bio)
अणु
	sector_t block, blocks, sector = bio->bi_iter.bi_sector;

	block = __sector_to_block(ec, sector);
	blocks = __nr_blocks(ec, bio);

	/*
	 * Partial first underlying block (__nr_blocks() may have
	 * resulted in one block).
	 */
	अगर (__block_mod(sector, ec->u_bs)) अणु
		block++;
		blocks--;
	पूर्ण

	/* Partial last underlying block अगर any. */
	अगर (blocks && __block_mod(bio_end_sector(bio), ec->u_bs))
		blocks--;

	वापस blocks ? dm_bufio_issue_discard(ec->bufio, block, blocks) : 0;
पूर्ण

/* Release blocks them from the bufio cache. */
अटल व्योम __ebs_क्रमget_bio(काष्ठा ebs_c *ec, काष्ठा bio *bio)
अणु
	sector_t blocks, sector = bio->bi_iter.bi_sector;

	blocks = __nr_blocks(ec, bio);

	dm_bufio_क्रमget_buffers(ec->bufio, __sector_to_block(ec, sector), blocks);
पूर्ण

/* Worker function to process incoming bios. */
अटल व्योम __ebs_process_bios(काष्ठा work_काष्ठा *ws)
अणु
	पूर्णांक r;
	bool ग_लिखो = false;
	sector_t block1, block2;
	काष्ठा ebs_c *ec = container_of(ws, काष्ठा ebs_c, ws);
	काष्ठा bio *bio;
	काष्ठा bio_list bios;

	bio_list_init(&bios);

	spin_lock_irq(&ec->lock);
	bios = ec->bios_in;
	bio_list_init(&ec->bios_in);
	spin_unlock_irq(&ec->lock);

	/* Prefetch all पढ़ो and any mis-aligned ग_लिखो buffers */
	bio_list_क्रम_each(bio, &bios) अणु
		block1 = __sector_to_block(ec, bio->bi_iter.bi_sector);
		अगर (bio_op(bio) == REQ_OP_READ)
			dm_bufio_prefetch(ec->bufio, block1, __nr_blocks(ec, bio));
		अन्यथा अगर (bio_op(bio) == REQ_OP_WRITE && !(bio->bi_opf & REQ_PREFLUSH)) अणु
			block2 = __sector_to_block(ec, bio_end_sector(bio));
			अगर (__block_mod(bio->bi_iter.bi_sector, ec->u_bs))
				dm_bufio_prefetch(ec->bufio, block1, 1);
			अगर (__block_mod(bio_end_sector(bio), ec->u_bs) && block2 != block1)
				dm_bufio_prefetch(ec->bufio, block2, 1);
		पूर्ण
	पूर्ण

	bio_list_क्रम_each(bio, &bios) अणु
		r = -EIO;
		अगर (bio_op(bio) == REQ_OP_READ)
			r = __ebs_rw_bio(ec, READ, bio);
		अन्यथा अगर (bio_op(bio) == REQ_OP_WRITE) अणु
			ग_लिखो = true;
			r = __ebs_rw_bio(ec, WRITE, bio);
		पूर्ण अन्यथा अगर (bio_op(bio) == REQ_OP_DISCARD) अणु
			__ebs_क्रमget_bio(ec, bio);
			r = __ebs_discard_bio(ec, bio);
		पूर्ण

		अगर (r < 0)
			bio->bi_status = त्रुटि_सं_to_blk_status(r);
	पूर्ण

	/*
	 * We ग_लिखो dirty buffers after processing I/O on them
	 * but beक्रमe we endio thus addressing REQ_FUA/REQ_SYNC.
	 */
	r = ग_लिखो ? dm_bufio_ग_लिखो_dirty_buffers(ec->bufio) : 0;

	जबतक ((bio = bio_list_pop(&bios))) अणु
		/* Any other request is endioed. */
		अगर (unlikely(r && bio_op(bio) == REQ_OP_WRITE))
			bio_io_error(bio);
		अन्यथा
			bio_endio(bio);
	पूर्ण
पूर्ण

/*
 * Conकाष्ठा an emulated block size mapping: <dev_path> <offset> <ebs> [<ubs>]
 *
 * <dev_path>: path of the underlying device
 * <offset>: offset in 512 bytes sectors पूर्णांकo <dev_path>
 * <ebs>: emulated block size in units of 512 bytes exposed to the upper layer
 * [<ubs>]: underlying block size in units of 512 bytes imposed on the lower layer;
 * 	    optional, अगर not supplied, retrieve logical block size from underlying device
 */
अटल पूर्णांक ebs_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक r;
	अचिन्हित लघु पंचांगp1;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	अक्षर dummy;
	काष्ठा ebs_c *ec;

	अगर (argc < 3 || argc > 4) अणु
		ti->error = "Invalid argument count";
		वापस -EINVAL;
	पूर्ण

	ec = ti->निजी = kzalloc(माप(*ec), GFP_KERNEL);
	अगर (!ec) अणु
		ti->error = "Cannot allocate ebs context";
		वापस -ENOMEM;
	पूर्ण

	r = -EINVAL;
	अगर (माला_पूछो(argv[1], "%llu%c", &पंचांगp, &dummy) != 1 ||
	    पंचांगp != (sector_t)पंचांगp ||
	    (sector_t)पंचांगp >= ti->len) अणु
		ti->error = "Invalid device offset sector";
		जाओ bad;
	पूर्ण
	ec->start = पंचांगp;

	अगर (माला_पूछो(argv[2], "%hu%c", &पंचांगp1, &dummy) != 1 ||
	    !__ebs_check_bs(पंचांगp1) ||
	    to_bytes(पंचांगp1) > PAGE_SIZE) अणु
		ti->error = "Invalid emulated block size";
		जाओ bad;
	पूर्ण
	ec->e_bs = पंचांगp1;

	अगर (argc > 3) अणु
		अगर (माला_पूछो(argv[3], "%hu%c", &पंचांगp1, &dummy) != 1 || !__ebs_check_bs(पंचांगp1)) अणु
			ti->error = "Invalid underlying block size";
			जाओ bad;
		पूर्ण
		ec->u_bs = पंचांगp1;
		ec->u_bs_set = true;
	पूर्ण अन्यथा
		ec->u_bs_set = false;

	r = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &ec->dev);
	अगर (r) अणु
		ti->error = "Device lookup failed";
		ec->dev = शून्य;
		जाओ bad;
	पूर्ण

	r = -EINVAL;
	अगर (!ec->u_bs_set) अणु
		ec->u_bs = to_sector(bdev_logical_block_size(ec->dev->bdev));
		अगर (!__ebs_check_bs(ec->u_bs)) अणु
			ti->error = "Invalid retrieved underlying block size";
			जाओ bad;
		पूर्ण
	पूर्ण

	अगर (!ec->u_bs_set && ec->e_bs == ec->u_bs)
		DMINFO("Emulation superfluous: emulated equal to underlying block size");

	अगर (__block_mod(ec->start, ec->u_bs)) अणु
		ti->error = "Device offset must be multiple of underlying block size";
		जाओ bad;
	पूर्ण

	ec->bufio = dm_bufio_client_create(ec->dev->bdev, to_bytes(ec->u_bs), 1, 0, शून्य, शून्य);
	अगर (IS_ERR(ec->bufio)) अणु
		ti->error = "Cannot create dm bufio client";
		r = PTR_ERR(ec->bufio);
		ec->bufio = शून्य;
		जाओ bad;
	पूर्ण

	ec->wq = alloc_ordered_workqueue("dm-" DM_MSG_PREFIX, WQ_MEM_RECLAIM);
	अगर (!ec->wq) अणु
		ti->error = "Cannot create dm-" DM_MSG_PREFIX " workqueue";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण

	ec->block_shअगरt = __ffs(ec->u_bs);
	INIT_WORK(&ec->ws, &__ebs_process_bios);
	bio_list_init(&ec->bios_in);
	spin_lock_init(&ec->lock);

	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->num_secure_erase_bios = 0;
	ti->num_ग_लिखो_same_bios = 0;
	ti->num_ग_लिखो_zeroes_bios = 0;
	वापस 0;
bad:
	ebs_dtr(ti);
	वापस r;
पूर्ण

अटल व्योम ebs_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा ebs_c *ec = ti->निजी;

	अगर (ec->wq)
		destroy_workqueue(ec->wq);
	अगर (ec->bufio)
		dm_bufio_client_destroy(ec->bufio);
	अगर (ec->dev)
		dm_put_device(ti, ec->dev);
	kमुक्त(ec);
पूर्ण

अटल पूर्णांक ebs_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा ebs_c *ec = ti->निजी;

	bio_set_dev(bio, ec->dev->bdev);
	bio->bi_iter.bi_sector = ec->start + dm_target_offset(ti, bio->bi_iter.bi_sector);

	अगर (unlikely(bio_op(bio) == REQ_OP_FLUSH))
		वापस DM_MAPIO_REMAPPED;
	/*
	 * Only queue क्रम bufio processing in हाल of partial or overlapping buffers
	 * -or-
	 * emulation with ebs == ubs aiming क्रम tests of dm-bufio overhead.
	 */
	अगर (likely(__block_mod(bio->bi_iter.bi_sector, ec->u_bs) ||
		   __block_mod(bio_end_sector(bio), ec->u_bs) ||
		   ec->e_bs == ec->u_bs)) अणु
		spin_lock_irq(&ec->lock);
		bio_list_add(&ec->bios_in, bio);
		spin_unlock_irq(&ec->lock);

		queue_work(ec->wq, &ec->ws);

		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	/* Forget any buffer content relative to this direct backing device I/O. */
	__ebs_क्रमget_bio(ec, bio);

	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल व्योम ebs_status(काष्ठा dm_target *ti, status_type_t type,
		       अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा ebs_c *ec = ti->निजी;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		*result = '\0';
		अवरोध;
	हाल STATUSTYPE_TABLE:
		snम_लिखो(result, maxlen, ec->u_bs_set ? "%s %llu %u %u" : "%s %llu %u",
			 ec->dev->name, (अचिन्हित दीर्घ दीर्घ) ec->start, ec->e_bs, ec->u_bs);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ebs_prepare_ioctl(काष्ठा dm_target *ti, काष्ठा block_device **bdev)
अणु
	काष्ठा ebs_c *ec = ti->निजी;
	काष्ठा dm_dev *dev = ec->dev;

	/*
	 * Only pass ioctls through अगर the device sizes match exactly.
	 */
	*bdev = dev->bdev;
	वापस !!(ec->start || ti->len != i_size_पढ़ो(dev->bdev->bd_inode) >> SECTOR_SHIFT);
पूर्ण

अटल व्योम ebs_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा ebs_c *ec = ti->निजी;

	limits->logical_block_size = to_bytes(ec->e_bs);
	limits->physical_block_size = to_bytes(ec->u_bs);
	limits->alignment_offset = limits->physical_block_size;
	blk_limits_io_min(limits, limits->logical_block_size);
पूर्ण

अटल पूर्णांक ebs_iterate_devices(काष्ठा dm_target *ti,
				  iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा ebs_c *ec = ti->निजी;

	वापस fn(ti, ec->dev, ec->start, ti->len, data);
पूर्ण

अटल काष्ठा target_type ebs_target = अणु
	.name		 = "ebs",
	.version	 = अणु1, 0, 1पूर्ण,
	.features	 = DM_TARGET_PASSES_INTEGRITY,
	.module		 = THIS_MODULE,
	.ctr		 = ebs_ctr,
	.dtr		 = ebs_dtr,
	.map		 = ebs_map,
	.status		 = ebs_status,
	.io_hपूर्णांकs	 = ebs_io_hपूर्णांकs,
	.prepare_ioctl	 = ebs_prepare_ioctl,
	.iterate_devices = ebs_iterate_devices,
पूर्ण;

अटल पूर्णांक __init dm_ebs_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_target(&ebs_target);

	अगर (r < 0)
		DMERR("register failed %d", r);

	वापस r;
पूर्ण

अटल व्योम dm_ebs_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&ebs_target);
पूर्ण

module_init(dm_ebs_init);
module_निकास(dm_ebs_निकास);

MODULE_AUTHOR("Heinz Mauelshagen <dm-devel@redhat.com>");
MODULE_DESCRIPTION(DM_NAME " emulated block size target");
MODULE_LICENSE("GPL");
