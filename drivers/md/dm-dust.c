<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Red Hat, Inc.
 *
 * This is a test "dust" device, which fails पढ़ोs on specअगरied
 * sectors, emulating the behavior of a hard disk drive sending
 * a "Read Medium Error" sense.
 *
 */

#समावेश <linux/device-mapper.h>
#समावेश <linux/module.h>
#समावेश <linux/rbtree.h>

#घोषणा DM_MSG_PREFIX "dust"

काष्ठा badblock अणु
	काष्ठा rb_node node;
	sector_t bb;
	अचिन्हित अक्षर wr_fail_cnt;
पूर्ण;

काष्ठा dust_device अणु
	काष्ठा dm_dev *dev;
	काष्ठा rb_root badblocklist;
	अचिन्हित दीर्घ दीर्घ badblock_count;
	spinlock_t dust_lock;
	अचिन्हित पूर्णांक blksz;
	पूर्णांक sect_per_block_shअगरt;
	अचिन्हित पूर्णांक sect_per_block;
	sector_t start;
	bool fail_पढ़ो_on_bb:1;
	bool quiet_mode:1;
पूर्ण;

अटल काष्ठा badblock *dust_rb_search(काष्ठा rb_root *root, sector_t blk)
अणु
	काष्ठा rb_node *node = root->rb_node;

	जबतक (node) अणु
		काष्ठा badblock *bblk = rb_entry(node, काष्ठा badblock, node);

		अगर (bblk->bb > blk)
			node = node->rb_left;
		अन्यथा अगर (bblk->bb < blk)
			node = node->rb_right;
		अन्यथा
			वापस bblk;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool dust_rb_insert(काष्ठा rb_root *root, काष्ठा badblock *new)
अणु
	काष्ठा badblock *bblk;
	काष्ठा rb_node **link = &root->rb_node, *parent = शून्य;
	sector_t value = new->bb;

	जबतक (*link) अणु
		parent = *link;
		bblk = rb_entry(parent, काष्ठा badblock, node);

		अगर (bblk->bb > value)
			link = &(*link)->rb_left;
		अन्यथा अगर (bblk->bb < value)
			link = &(*link)->rb_right;
		अन्यथा
			वापस false;
	पूर्ण

	rb_link_node(&new->node, parent, link);
	rb_insert_color(&new->node, root);

	वापस true;
पूर्ण

अटल पूर्णांक dust_हटाओ_block(काष्ठा dust_device *dd, अचिन्हित दीर्घ दीर्घ block)
अणु
	काष्ठा badblock *bblock;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->dust_lock, flags);
	bblock = dust_rb_search(&dd->badblocklist, block);

	अगर (bblock == शून्य) अणु
		अगर (!dd->quiet_mode) अणु
			DMERR("%s: block %llu not found in badblocklist",
			      __func__, block);
		पूर्ण
		spin_unlock_irqrestore(&dd->dust_lock, flags);
		वापस -EINVAL;
	पूर्ण

	rb_erase(&bblock->node, &dd->badblocklist);
	dd->badblock_count--;
	अगर (!dd->quiet_mode)
		DMINFO("%s: badblock removed at block %llu", __func__, block);
	kमुक्त(bblock);
	spin_unlock_irqrestore(&dd->dust_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dust_add_block(काष्ठा dust_device *dd, अचिन्हित दीर्घ दीर्घ block,
			  अचिन्हित अक्षर wr_fail_cnt)
अणु
	काष्ठा badblock *bblock;
	अचिन्हित दीर्घ flags;

	bblock = kदो_स्मृति(माप(*bblock), GFP_KERNEL);
	अगर (bblock == शून्य) अणु
		अगर (!dd->quiet_mode)
			DMERR("%s: badblock allocation failed", __func__);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&dd->dust_lock, flags);
	bblock->bb = block;
	bblock->wr_fail_cnt = wr_fail_cnt;
	अगर (!dust_rb_insert(&dd->badblocklist, bblock)) अणु
		अगर (!dd->quiet_mode) अणु
			DMERR("%s: block %llu already in badblocklist",
			      __func__, block);
		पूर्ण
		spin_unlock_irqrestore(&dd->dust_lock, flags);
		kमुक्त(bblock);
		वापस -EINVAL;
	पूर्ण

	dd->badblock_count++;
	अगर (!dd->quiet_mode) अणु
		DMINFO("%s: badblock added at block %llu with write fail count %u",
		       __func__, block, wr_fail_cnt);
	पूर्ण
	spin_unlock_irqrestore(&dd->dust_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dust_query_block(काष्ठा dust_device *dd, अचिन्हित दीर्घ दीर्घ block, अक्षर *result,
			    अचिन्हित पूर्णांक maxlen, अचिन्हित पूर्णांक *sz_ptr)
अणु
	काष्ठा badblock *bblock;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक sz = *sz_ptr;

	spin_lock_irqsave(&dd->dust_lock, flags);
	bblock = dust_rb_search(&dd->badblocklist, block);
	अगर (bblock != शून्य)
		DMEMIT("%s: block %llu found in badblocklist", __func__, block);
	अन्यथा
		DMEMIT("%s: block %llu not found in badblocklist", __func__, block);
	spin_unlock_irqrestore(&dd->dust_lock, flags);

	वापस 1;
पूर्ण

अटल पूर्णांक __dust_map_पढ़ो(काष्ठा dust_device *dd, sector_t thisblock)
अणु
	काष्ठा badblock *bblk = dust_rb_search(&dd->badblocklist, thisblock);

	अगर (bblk)
		वापस DM_MAPIO_KILL;

	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल पूर्णांक dust_map_पढ़ो(काष्ठा dust_device *dd, sector_t thisblock,
			 bool fail_पढ़ो_on_bb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक r = DM_MAPIO_REMAPPED;

	अगर (fail_पढ़ो_on_bb) अणु
		thisblock >>= dd->sect_per_block_shअगरt;
		spin_lock_irqsave(&dd->dust_lock, flags);
		r = __dust_map_पढ़ो(dd, thisblock);
		spin_unlock_irqrestore(&dd->dust_lock, flags);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक __dust_map_ग_लिखो(काष्ठा dust_device *dd, sector_t thisblock)
अणु
	काष्ठा badblock *bblk = dust_rb_search(&dd->badblocklist, thisblock);

	अगर (bblk && bblk->wr_fail_cnt > 0) अणु
		bblk->wr_fail_cnt--;
		वापस DM_MAPIO_KILL;
	पूर्ण

	अगर (bblk) अणु
		rb_erase(&bblk->node, &dd->badblocklist);
		dd->badblock_count--;
		kमुक्त(bblk);
		अगर (!dd->quiet_mode) अणु
			sector_भाग(thisblock, dd->sect_per_block);
			DMINFO("block %llu removed from badblocklist by write",
			       (अचिन्हित दीर्घ दीर्घ)thisblock);
		पूर्ण
	पूर्ण

	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल पूर्णांक dust_map_ग_लिखो(काष्ठा dust_device *dd, sector_t thisblock,
			  bool fail_पढ़ो_on_bb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक r = DM_MAPIO_REMAPPED;

	अगर (fail_पढ़ो_on_bb) अणु
		thisblock >>= dd->sect_per_block_shअगरt;
		spin_lock_irqsave(&dd->dust_lock, flags);
		r = __dust_map_ग_लिखो(dd, thisblock);
		spin_unlock_irqrestore(&dd->dust_lock, flags);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक dust_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा dust_device *dd = ti->निजी;
	पूर्णांक r;

	bio_set_dev(bio, dd->dev->bdev);
	bio->bi_iter.bi_sector = dd->start + dm_target_offset(ti, bio->bi_iter.bi_sector);

	अगर (bio_data_dir(bio) == READ)
		r = dust_map_पढ़ो(dd, bio->bi_iter.bi_sector, dd->fail_पढ़ो_on_bb);
	अन्यथा
		r = dust_map_ग_लिखो(dd, bio->bi_iter.bi_sector, dd->fail_पढ़ो_on_bb);

	वापस r;
पूर्ण

अटल bool __dust_clear_badblocks(काष्ठा rb_root *tree,
				   अचिन्हित दीर्घ दीर्घ count)
अणु
	काष्ठा rb_node *node = शून्य, *nnode = शून्य;

	nnode = rb_first(tree);
	अगर (nnode == शून्य) अणु
		BUG_ON(count != 0);
		वापस false;
	पूर्ण

	जबतक (nnode) अणु
		node = nnode;
		nnode = rb_next(node);
		rb_erase(node, tree);
		count--;
		kमुक्त(node);
	पूर्ण
	BUG_ON(count != 0);
	BUG_ON(tree->rb_node != शून्य);

	वापस true;
पूर्ण

अटल पूर्णांक dust_clear_badblocks(काष्ठा dust_device *dd, अक्षर *result, अचिन्हित पूर्णांक maxlen,
				अचिन्हित पूर्णांक *sz_ptr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rb_root badblocklist;
	अचिन्हित दीर्घ दीर्घ badblock_count;
	अचिन्हित पूर्णांक sz = *sz_ptr;

	spin_lock_irqsave(&dd->dust_lock, flags);
	badblocklist = dd->badblocklist;
	badblock_count = dd->badblock_count;
	dd->badblocklist = RB_ROOT;
	dd->badblock_count = 0;
	spin_unlock_irqrestore(&dd->dust_lock, flags);

	अगर (!__dust_clear_badblocks(&badblocklist, badblock_count))
		DMEMIT("%s: no badblocks found", __func__);
	अन्यथा
		DMEMIT("%s: badblocks cleared", __func__);

	वापस 1;
पूर्ण

अटल पूर्णांक dust_list_badblocks(काष्ठा dust_device *dd, अक्षर *result, अचिन्हित पूर्णांक maxlen,
				अचिन्हित पूर्णांक *sz_ptr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rb_root badblocklist;
	काष्ठा rb_node *node;
	काष्ठा badblock *bblk;
	अचिन्हित पूर्णांक sz = *sz_ptr;
	अचिन्हित दीर्घ दीर्घ num = 0;

	spin_lock_irqsave(&dd->dust_lock, flags);
	badblocklist = dd->badblocklist;
	क्रम (node = rb_first(&badblocklist); node; node = rb_next(node)) अणु
		bblk = rb_entry(node, काष्ठा badblock, node);
		DMEMIT("%llu\n", bblk->bb);
		num++;
	पूर्ण

	spin_unlock_irqrestore(&dd->dust_lock, flags);
	अगर (!num)
		DMEMIT("No blocks in badblocklist");

	वापस 1;
पूर्ण

/*
 * Target parameters:
 *
 * <device_path> <offset> <blksz>
 *
 * device_path: path to the block device
 * offset: offset to data area from start of device_path
 * blksz: block size (minimum 512, maximum 1073741824, must be a घातer of 2)
 */
अटल पूर्णांक dust_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा dust_device *dd;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	अक्षर dummy;
	अचिन्हित पूर्णांक blksz;
	अचिन्हित पूर्णांक sect_per_block;
	sector_t DUST_MAX_BLKSZ_SECTORS = 2097152;
	sector_t max_block_sectors = min(ti->len, DUST_MAX_BLKSZ_SECTORS);

	अगर (argc != 3) अणु
		ti->error = "Invalid argument count";
		वापस -EINVAL;
	पूर्ण

	अगर (kstrtouपूर्णांक(argv[2], 10, &blksz) || !blksz) अणु
		ti->error = "Invalid block size parameter";
		वापस -EINVAL;
	पूर्ण

	अगर (blksz < 512) अणु
		ti->error = "Block size must be at least 512";
		वापस -EINVAL;
	पूर्ण

	अगर (!is_घातer_of_2(blksz)) अणु
		ti->error = "Block size must be a power of 2";
		वापस -EINVAL;
	पूर्ण

	अगर (to_sector(blksz) > max_block_sectors) अणु
		ti->error = "Block size is too large";
		वापस -EINVAL;
	पूर्ण

	sect_per_block = (blksz >> SECTOR_SHIFT);

	अगर (माला_पूछो(argv[1], "%llu%c", &पंचांगp, &dummy) != 1 || पंचांगp != (sector_t)पंचांगp) अणु
		ti->error = "Invalid device offset sector";
		वापस -EINVAL;
	पूर्ण

	dd = kzalloc(माप(काष्ठा dust_device), GFP_KERNEL);
	अगर (dd == शून्य) अणु
		ti->error = "Cannot allocate context";
		वापस -ENOMEM;
	पूर्ण

	अगर (dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &dd->dev)) अणु
		ti->error = "Device lookup failed";
		kमुक्त(dd);
		वापस -EINVAL;
	पूर्ण

	dd->sect_per_block = sect_per_block;
	dd->blksz = blksz;
	dd->start = पंचांगp;

	dd->sect_per_block_shअगरt = __ffs(sect_per_block);

	/*
	 * Whether to fail a पढ़ो on a "bad" block.
	 * Defaults to false; enabled later by message.
	 */
	dd->fail_पढ़ो_on_bb = false;

	/*
	 * Initialize bad block list rbtree.
	 */
	dd->badblocklist = RB_ROOT;
	dd->badblock_count = 0;
	spin_lock_init(&dd->dust_lock);

	dd->quiet_mode = false;

	BUG_ON(dm_set_target_max_io_len(ti, dd->sect_per_block) != 0);

	ti->num_discard_bios = 1;
	ti->num_flush_bios = 1;
	ti->निजी = dd;

	वापस 0;
पूर्ण

अटल व्योम dust_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा dust_device *dd = ti->निजी;

	__dust_clear_badblocks(&dd->badblocklist, dd->badblock_count);
	dm_put_device(ti, dd->dev);
	kमुक्त(dd);
पूर्ण

अटल पूर्णांक dust_message(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv,
			अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	काष्ठा dust_device *dd = ti->निजी;
	sector_t size = i_size_पढ़ो(dd->dev->bdev->bd_inode) >> SECTOR_SHIFT;
	bool invalid_msg = false;
	पूर्णांक r = -EINVAL;
	अचिन्हित दीर्घ दीर्घ पंचांगp, block;
	अचिन्हित अक्षर wr_fail_cnt;
	अचिन्हित पूर्णांक पंचांगp_ui;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक sz = 0;
	अक्षर dummy;

	अगर (argc == 1) अणु
		अगर (!strहालcmp(argv[0], "addbadblock") ||
		    !strहालcmp(argv[0], "removebadblock") ||
		    !strहालcmp(argv[0], "queryblock")) अणु
			DMERR("%s requires an additional argument", argv[0]);
		पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "disable")) अणु
			DMINFO("disabling read failures on bad sectors");
			dd->fail_पढ़ो_on_bb = false;
			r = 0;
		पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "enable")) अणु
			DMINFO("enabling read failures on bad sectors");
			dd->fail_पढ़ो_on_bb = true;
			r = 0;
		पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "countbadblocks")) अणु
			spin_lock_irqsave(&dd->dust_lock, flags);
			DMEMIT("countbadblocks: %llu badblock(s) found",
			       dd->badblock_count);
			spin_unlock_irqrestore(&dd->dust_lock, flags);
			r = 1;
		पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "clearbadblocks")) अणु
			r = dust_clear_badblocks(dd, result, maxlen, &sz);
		पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "quiet")) अणु
			अगर (!dd->quiet_mode)
				dd->quiet_mode = true;
			अन्यथा
				dd->quiet_mode = false;
			r = 0;
		पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "listbadblocks")) अणु
			r = dust_list_badblocks(dd, result, maxlen, &sz);
		पूर्ण अन्यथा अणु
			invalid_msg = true;
		पूर्ण
	पूर्ण अन्यथा अगर (argc == 2) अणु
		अगर (माला_पूछो(argv[1], "%llu%c", &पंचांगp, &dummy) != 1)
			वापस r;

		block = पंचांगp;
		sector_भाग(size, dd->sect_per_block);
		अगर (block > size) अणु
			DMERR("selected block value out of range");
			वापस r;
		पूर्ण

		अगर (!strहालcmp(argv[0], "addbadblock"))
			r = dust_add_block(dd, block, 0);
		अन्यथा अगर (!strहालcmp(argv[0], "removebadblock"))
			r = dust_हटाओ_block(dd, block);
		अन्यथा अगर (!strहालcmp(argv[0], "queryblock"))
			r = dust_query_block(dd, block, result, maxlen, &sz);
		अन्यथा
			invalid_msg = true;

	पूर्ण अन्यथा अगर (argc == 3) अणु
		अगर (माला_पूछो(argv[1], "%llu%c", &पंचांगp, &dummy) != 1)
			वापस r;

		अगर (माला_पूछो(argv[2], "%u%c", &पंचांगp_ui, &dummy) != 1)
			वापस r;

		block = पंचांगp;
		अगर (पंचांगp_ui > 255) अणु
			DMERR("selected write fail count out of range");
			वापस r;
		पूर्ण
		wr_fail_cnt = पंचांगp_ui;
		sector_भाग(size, dd->sect_per_block);
		अगर (block > size) अणु
			DMERR("selected block value out of range");
			वापस r;
		पूर्ण

		अगर (!strहालcmp(argv[0], "addbadblock"))
			r = dust_add_block(dd, block, wr_fail_cnt);
		अन्यथा
			invalid_msg = true;

	पूर्ण अन्यथा
		DMERR("invalid number of arguments '%d'", argc);

	अगर (invalid_msg)
		DMERR("unrecognized message '%s' received", argv[0]);

	वापस r;
पूर्ण

अटल व्योम dust_status(काष्ठा dm_target *ti, status_type_t type,
			अचिन्हित पूर्णांक status_flags, अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	काष्ठा dust_device *dd = ti->निजी;
	अचिन्हित पूर्णांक sz = 0;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%s %s %s", dd->dev->name,
		       dd->fail_पढ़ो_on_bb ? "fail_read_on_bad_block" : "bypass",
		       dd->quiet_mode ? "quiet" : "verbose");
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%s %llu %u", dd->dev->name,
		       (अचिन्हित दीर्घ दीर्घ)dd->start, dd->blksz);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dust_prepare_ioctl(काष्ठा dm_target *ti, काष्ठा block_device **bdev)
अणु
	काष्ठा dust_device *dd = ti->निजी;
	काष्ठा dm_dev *dev = dd->dev;

	*bdev = dev->bdev;

	/*
	 * Only pass ioctls through अगर the device sizes match exactly.
	 */
	अगर (dd->start ||
	    ti->len != i_size_पढ़ो(dev->bdev->bd_inode) >> SECTOR_SHIFT)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक dust_iterate_devices(काष्ठा dm_target *ti, iterate_devices_callout_fn fn,
				व्योम *data)
अणु
	काष्ठा dust_device *dd = ti->निजी;

	वापस fn(ti, dd->dev, dd->start, ti->len, data);
पूर्ण

अटल काष्ठा target_type dust_target = अणु
	.name = "dust",
	.version = अणु1, 0, 0पूर्ण,
	.module = THIS_MODULE,
	.ctr = dust_ctr,
	.dtr = dust_dtr,
	.iterate_devices = dust_iterate_devices,
	.map = dust_map,
	.message = dust_message,
	.status = dust_status,
	.prepare_ioctl = dust_prepare_ioctl,
पूर्ण;

अटल पूर्णांक __init dm_dust_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_target(&dust_target);

	अगर (r < 0)
		DMERR("dm_register_target failed %d", r);

	वापस r;
पूर्ण

अटल व्योम __निकास dm_dust_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&dust_target);
पूर्ण

module_init(dm_dust_init);
module_निकास(dm_dust_निकास);

MODULE_DESCRIPTION(DM_NAME " dust test target");
MODULE_AUTHOR("Bryan Gurney <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
