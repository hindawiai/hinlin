<शैली गुरु>
/*
 * Copyright (C) 2001-2003 Sistina Software (UK) Limited.
 *
 * This file is released under the GPL.
 */

#समावेश "dm.h"
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/dax.h>
#समावेश <linux/slab.h>
#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "linear"

/*
 * Linear: maps a linear range of a device.
 */
काष्ठा linear_c अणु
	काष्ठा dm_dev *dev;
	sector_t start;
पूर्ण;

/*
 * Conकाष्ठा a linear mapping: <dev_path> <offset>
 */
अटल पूर्णांक linear_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा linear_c *lc;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	अक्षर dummy;
	पूर्णांक ret;

	अगर (argc != 2) अणु
		ti->error = "Invalid argument count";
		वापस -EINVAL;
	पूर्ण

	lc = kदो_स्मृति(माप(*lc), GFP_KERNEL);
	अगर (lc == शून्य) अणु
		ti->error = "Cannot allocate linear context";
		वापस -ENOMEM;
	पूर्ण

	ret = -EINVAL;
	अगर (माला_पूछो(argv[1], "%llu%c", &पंचांगp, &dummy) != 1 || पंचांगp != (sector_t)पंचांगp) अणु
		ti->error = "Invalid device sector";
		जाओ bad;
	पूर्ण
	lc->start = पंचांगp;

	ret = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &lc->dev);
	अगर (ret) अणु
		ti->error = "Device lookup failed";
		जाओ bad;
	पूर्ण

	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->num_secure_erase_bios = 1;
	ti->num_ग_लिखो_same_bios = 1;
	ti->num_ग_लिखो_zeroes_bios = 1;
	ti->निजी = lc;
	वापस 0;

      bad:
	kमुक्त(lc);
	वापस ret;
पूर्ण

अटल व्योम linear_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा linear_c *lc = (काष्ठा linear_c *) ti->निजी;

	dm_put_device(ti, lc->dev);
	kमुक्त(lc);
पूर्ण

अटल sector_t linear_map_sector(काष्ठा dm_target *ti, sector_t bi_sector)
अणु
	काष्ठा linear_c *lc = ti->निजी;

	वापस lc->start + dm_target_offset(ti, bi_sector);
पूर्ण

अटल व्योम linear_map_bio(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा linear_c *lc = ti->निजी;

	bio_set_dev(bio, lc->dev->bdev);
	अगर (bio_sectors(bio) || op_is_zone_mgmt(bio_op(bio)))
		bio->bi_iter.bi_sector =
			linear_map_sector(ti, bio->bi_iter.bi_sector);
पूर्ण

अटल पूर्णांक linear_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	linear_map_bio(ti, bio);

	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल व्योम linear_status(काष्ठा dm_target *ti, status_type_t type,
			  अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा linear_c *lc = (काष्ठा linear_c *) ti->निजी;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		result[0] = '\0';
		अवरोध;

	हाल STATUSTYPE_TABLE:
		snम_लिखो(result, maxlen, "%s %llu", lc->dev->name,
				(अचिन्हित दीर्घ दीर्घ)lc->start);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक linear_prepare_ioctl(काष्ठा dm_target *ti, काष्ठा block_device **bdev)
अणु
	काष्ठा linear_c *lc = (काष्ठा linear_c *) ti->निजी;
	काष्ठा dm_dev *dev = lc->dev;

	*bdev = dev->bdev;

	/*
	 * Only pass ioctls through अगर the device sizes match exactly.
	 */
	अगर (lc->start ||
	    ti->len != i_size_पढ़ो(dev->bdev->bd_inode) >> SECTOR_SHIFT)
		वापस 1;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED
अटल पूर्णांक linear_report_zones(काष्ठा dm_target *ti,
		काष्ठा dm_report_zones_args *args, अचिन्हित पूर्णांक nr_zones)
अणु
	काष्ठा linear_c *lc = ti->निजी;
	sector_t sector = linear_map_sector(ti, args->next_sector);

	args->start = lc->start;
	वापस blkdev_report_zones(lc->dev->bdev, sector, nr_zones,
				   dm_report_zones_cb, args);
पूर्ण
#अन्यथा
#घोषणा linear_report_zones शून्य
#पूर्ण_अगर

अटल पूर्णांक linear_iterate_devices(काष्ठा dm_target *ti,
				  iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा linear_c *lc = ti->निजी;

	वापस fn(ti, lc->dev, lc->start, ti->len, data);
पूर्ण

#अगर IS_ENABLED(CONFIG_DAX_DRIVER)
अटल दीर्घ linear_dax_direct_access(काष्ठा dm_target *ti, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	दीर्घ ret;
	काष्ठा linear_c *lc = ti->निजी;
	काष्ठा block_device *bdev = lc->dev->bdev;
	काष्ठा dax_device *dax_dev = lc->dev->dax_dev;
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;

	dev_sector = linear_map_sector(ti, sector);
	ret = bdev_dax_pgoff(bdev, dev_sector, nr_pages * PAGE_SIZE, &pgoff);
	अगर (ret)
		वापस ret;
	वापस dax_direct_access(dax_dev, pgoff, nr_pages, kaddr, pfn);
पूर्ण

अटल माप_प्रकार linear_dax_copy_from_iter(काष्ठा dm_target *ti, pgoff_t pgoff,
		व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	काष्ठा linear_c *lc = ti->निजी;
	काष्ठा block_device *bdev = lc->dev->bdev;
	काष्ठा dax_device *dax_dev = lc->dev->dax_dev;
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;

	dev_sector = linear_map_sector(ti, sector);
	अगर (bdev_dax_pgoff(bdev, dev_sector, ALIGN(bytes, PAGE_SIZE), &pgoff))
		वापस 0;
	वापस dax_copy_from_iter(dax_dev, pgoff, addr, bytes, i);
पूर्ण

अटल माप_प्रकार linear_dax_copy_to_iter(काष्ठा dm_target *ti, pgoff_t pgoff,
		व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	काष्ठा linear_c *lc = ti->निजी;
	काष्ठा block_device *bdev = lc->dev->bdev;
	काष्ठा dax_device *dax_dev = lc->dev->dax_dev;
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;

	dev_sector = linear_map_sector(ti, sector);
	अगर (bdev_dax_pgoff(bdev, dev_sector, ALIGN(bytes, PAGE_SIZE), &pgoff))
		वापस 0;
	वापस dax_copy_to_iter(dax_dev, pgoff, addr, bytes, i);
पूर्ण

अटल पूर्णांक linear_dax_zero_page_range(काष्ठा dm_target *ti, pgoff_t pgoff,
				      माप_प्रकार nr_pages)
अणु
	पूर्णांक ret;
	काष्ठा linear_c *lc = ti->निजी;
	काष्ठा block_device *bdev = lc->dev->bdev;
	काष्ठा dax_device *dax_dev = lc->dev->dax_dev;
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;

	dev_sector = linear_map_sector(ti, sector);
	ret = bdev_dax_pgoff(bdev, dev_sector, nr_pages << PAGE_SHIFT, &pgoff);
	अगर (ret)
		वापस ret;
	वापस dax_zero_page_range(dax_dev, pgoff, nr_pages);
पूर्ण

#अन्यथा
#घोषणा linear_dax_direct_access शून्य
#घोषणा linear_dax_copy_from_iter शून्य
#घोषणा linear_dax_copy_to_iter शून्य
#घोषणा linear_dax_zero_page_range शून्य
#पूर्ण_अगर

अटल काष्ठा target_type linear_target = अणु
	.name   = "linear",
	.version = अणु1, 4, 0पूर्ण,
	.features = DM_TARGET_PASSES_INTEGRITY | DM_TARGET_NOWAIT |
		    DM_TARGET_ZONED_HM | DM_TARGET_PASSES_CRYPTO,
	.report_zones = linear_report_zones,
	.module = THIS_MODULE,
	.ctr    = linear_ctr,
	.dtr    = linear_dtr,
	.map    = linear_map,
	.status = linear_status,
	.prepare_ioctl = linear_prepare_ioctl,
	.iterate_devices = linear_iterate_devices,
	.direct_access = linear_dax_direct_access,
	.dax_copy_from_iter = linear_dax_copy_from_iter,
	.dax_copy_to_iter = linear_dax_copy_to_iter,
	.dax_zero_page_range = linear_dax_zero_page_range,
पूर्ण;

पूर्णांक __init dm_linear_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_target(&linear_target);

	अगर (r < 0)
		DMERR("register failed %d", r);

	वापस r;
पूर्ण

व्योम dm_linear_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&linear_target);
पूर्ण
