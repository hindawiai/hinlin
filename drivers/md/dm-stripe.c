<शैली गुरु>
/*
 * Copyright (C) 2001-2003 Sistina Software (UK) Limited.
 *
 * This file is released under the GPL.
 */

#समावेश "dm.h"
#समावेश <linux/device-mapper.h>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/dax.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>

#घोषणा DM_MSG_PREFIX "striped"
#घोषणा DM_IO_ERROR_THRESHOLD 15

काष्ठा stripe अणु
	काष्ठा dm_dev *dev;
	sector_t physical_start;

	atomic_t error_count;
पूर्ण;

काष्ठा stripe_c अणु
	uपूर्णांक32_t stripes;
	पूर्णांक stripes_shअगरt;

	/* The size of this target / num. stripes */
	sector_t stripe_width;

	uपूर्णांक32_t chunk_size;
	पूर्णांक chunk_size_shअगरt;

	/* Needed क्रम handling events */
	काष्ठा dm_target *ti;

	/* Work काष्ठा used क्रम triggering events*/
	काष्ठा work_काष्ठा trigger_event;

	काष्ठा stripe stripe[];
पूर्ण;

/*
 * An event is triggered whenever a drive
 * drops out of a stripe volume.
 */
अटल व्योम trigger_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा stripe_c *sc = container_of(work, काष्ठा stripe_c,
					   trigger_event);
	dm_table_event(sc->ti->table);
पूर्ण

/*
 * Parse a single <dev> <sector> pair
 */
अटल पूर्णांक get_stripe(काष्ठा dm_target *ti, काष्ठा stripe_c *sc,
		      अचिन्हित पूर्णांक stripe, अक्षर **argv)
अणु
	अचिन्हित दीर्घ दीर्घ start;
	अक्षर dummy;
	पूर्णांक ret;

	अगर (माला_पूछो(argv[1], "%llu%c", &start, &dummy) != 1)
		वापस -EINVAL;

	ret = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table),
			    &sc->stripe[stripe].dev);
	अगर (ret)
		वापस ret;

	sc->stripe[stripe].physical_start = start;

	वापस 0;
पूर्ण

/*
 * Conकाष्ठा a striped mapping.
 * <number of stripes> <chunk size> [<dev_path> <offset>]+
 */
अटल पूर्णांक stripe_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा stripe_c *sc;
	sector_t width, पंचांगp_len;
	uपूर्णांक32_t stripes;
	uपूर्णांक32_t chunk_size;
	पूर्णांक r;
	अचिन्हित पूर्णांक i;

	अगर (argc < 2) अणु
		ti->error = "Not enough arguments";
		वापस -EINVAL;
	पूर्ण

	अगर (kstrtouपूर्णांक(argv[0], 10, &stripes) || !stripes) अणु
		ti->error = "Invalid stripe count";
		वापस -EINVAL;
	पूर्ण

	अगर (kstrtouपूर्णांक(argv[1], 10, &chunk_size) || !chunk_size) अणु
		ti->error = "Invalid chunk_size";
		वापस -EINVAL;
	पूर्ण

	width = ti->len;
	अगर (sector_भाग(width, stripes)) अणु
		ti->error = "Target length not divisible by "
		    "number of stripes";
		वापस -EINVAL;
	पूर्ण

	पंचांगp_len = width;
	अगर (sector_भाग(पंचांगp_len, chunk_size)) अणु
		ti->error = "Target length not divisible by "
		    "chunk size";
		वापस -EINVAL;
	पूर्ण

	/*
	 * Do we have enough arguments क्रम that many stripes ?
	 */
	अगर (argc != (2 + 2 * stripes)) अणु
		ti->error = "Not enough destinations "
			"specified";
		वापस -EINVAL;
	पूर्ण

	sc = kदो_स्मृति(काष्ठा_size(sc, stripe, stripes), GFP_KERNEL);
	अगर (!sc) अणु
		ti->error = "Memory allocation for striped context "
		    "failed";
		वापस -ENOMEM;
	पूर्ण

	INIT_WORK(&sc->trigger_event, trigger_event);

	/* Set poपूर्णांकer to dm target; used in trigger_event */
	sc->ti = ti;
	sc->stripes = stripes;
	sc->stripe_width = width;

	अगर (stripes & (stripes - 1))
		sc->stripes_shअगरt = -1;
	अन्यथा
		sc->stripes_shअगरt = __ffs(stripes);

	r = dm_set_target_max_io_len(ti, chunk_size);
	अगर (r) अणु
		kमुक्त(sc);
		वापस r;
	पूर्ण

	ti->num_flush_bios = stripes;
	ti->num_discard_bios = stripes;
	ti->num_secure_erase_bios = stripes;
	ti->num_ग_लिखो_same_bios = stripes;
	ti->num_ग_लिखो_zeroes_bios = stripes;

	sc->chunk_size = chunk_size;
	अगर (chunk_size & (chunk_size - 1))
		sc->chunk_size_shअगरt = -1;
	अन्यथा
		sc->chunk_size_shअगरt = __ffs(chunk_size);

	/*
	 * Get the stripe destinations.
	 */
	क्रम (i = 0; i < stripes; i++) अणु
		argv += 2;

		r = get_stripe(ti, sc, i, argv);
		अगर (r < 0) अणु
			ti->error = "Couldn't parse stripe destination";
			जबतक (i--)
				dm_put_device(ti, sc->stripe[i].dev);
			kमुक्त(sc);
			वापस r;
		पूर्ण
		atomic_set(&(sc->stripe[i].error_count), 0);
	पूर्ण

	ti->निजी = sc;

	वापस 0;
पूर्ण

अटल व्योम stripe_dtr(काष्ठा dm_target *ti)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा stripe_c *sc = (काष्ठा stripe_c *) ti->निजी;

	क्रम (i = 0; i < sc->stripes; i++)
		dm_put_device(ti, sc->stripe[i].dev);

	flush_work(&sc->trigger_event);
	kमुक्त(sc);
पूर्ण

अटल व्योम stripe_map_sector(काष्ठा stripe_c *sc, sector_t sector,
			      uपूर्णांक32_t *stripe, sector_t *result)
अणु
	sector_t chunk = dm_target_offset(sc->ti, sector);
	sector_t chunk_offset;

	अगर (sc->chunk_size_shअगरt < 0)
		chunk_offset = sector_भाग(chunk, sc->chunk_size);
	अन्यथा अणु
		chunk_offset = chunk & (sc->chunk_size - 1);
		chunk >>= sc->chunk_size_shअगरt;
	पूर्ण

	अगर (sc->stripes_shअगरt < 0)
		*stripe = sector_भाग(chunk, sc->stripes);
	अन्यथा अणु
		*stripe = chunk & (sc->stripes - 1);
		chunk >>= sc->stripes_shअगरt;
	पूर्ण

	अगर (sc->chunk_size_shअगरt < 0)
		chunk *= sc->chunk_size;
	अन्यथा
		chunk <<= sc->chunk_size_shअगरt;

	*result = chunk + chunk_offset;
पूर्ण

अटल व्योम stripe_map_range_sector(काष्ठा stripe_c *sc, sector_t sector,
				    uपूर्णांक32_t target_stripe, sector_t *result)
अणु
	uपूर्णांक32_t stripe;

	stripe_map_sector(sc, sector, &stripe, result);
	अगर (stripe == target_stripe)
		वापस;

	/* round करोwn */
	sector = *result;
	अगर (sc->chunk_size_shअगरt < 0)
		*result -= sector_भाग(sector, sc->chunk_size);
	अन्यथा
		*result = sector & ~(sector_t)(sc->chunk_size - 1);

	अगर (target_stripe < stripe)
		*result += sc->chunk_size;		/* next chunk */
पूर्ण

अटल पूर्णांक stripe_map_range(काष्ठा stripe_c *sc, काष्ठा bio *bio,
			    uपूर्णांक32_t target_stripe)
अणु
	sector_t begin, end;

	stripe_map_range_sector(sc, bio->bi_iter.bi_sector,
				target_stripe, &begin);
	stripe_map_range_sector(sc, bio_end_sector(bio),
				target_stripe, &end);
	अगर (begin < end) अणु
		bio_set_dev(bio, sc->stripe[target_stripe].dev->bdev);
		bio->bi_iter.bi_sector = begin +
			sc->stripe[target_stripe].physical_start;
		bio->bi_iter.bi_size = to_bytes(end - begin);
		वापस DM_MAPIO_REMAPPED;
	पूर्ण अन्यथा अणु
		/* The range करोesn't map to the target stripe */
		bio_endio(bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण
पूर्ण

अटल पूर्णांक stripe_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा stripe_c *sc = ti->निजी;
	uपूर्णांक32_t stripe;
	अचिन्हित target_bio_nr;

	अगर (bio->bi_opf & REQ_PREFLUSH) अणु
		target_bio_nr = dm_bio_get_target_bio_nr(bio);
		BUG_ON(target_bio_nr >= sc->stripes);
		bio_set_dev(bio, sc->stripe[target_bio_nr].dev->bdev);
		वापस DM_MAPIO_REMAPPED;
	पूर्ण
	अगर (unlikely(bio_op(bio) == REQ_OP_DISCARD) ||
	    unlikely(bio_op(bio) == REQ_OP_SECURE_ERASE) ||
	    unlikely(bio_op(bio) == REQ_OP_WRITE_ZEROES) ||
	    unlikely(bio_op(bio) == REQ_OP_WRITE_SAME)) अणु
		target_bio_nr = dm_bio_get_target_bio_nr(bio);
		BUG_ON(target_bio_nr >= sc->stripes);
		वापस stripe_map_range(sc, bio, target_bio_nr);
	पूर्ण

	stripe_map_sector(sc, bio->bi_iter.bi_sector,
			  &stripe, &bio->bi_iter.bi_sector);

	bio->bi_iter.bi_sector += sc->stripe[stripe].physical_start;
	bio_set_dev(bio, sc->stripe[stripe].dev->bdev);

	वापस DM_MAPIO_REMAPPED;
पूर्ण

#अगर IS_ENABLED(CONFIG_DAX_DRIVER)
अटल दीर्घ stripe_dax_direct_access(काष्ठा dm_target *ti, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;
	काष्ठा stripe_c *sc = ti->निजी;
	काष्ठा dax_device *dax_dev;
	काष्ठा block_device *bdev;
	uपूर्णांक32_t stripe;
	दीर्घ ret;

	stripe_map_sector(sc, sector, &stripe, &dev_sector);
	dev_sector += sc->stripe[stripe].physical_start;
	dax_dev = sc->stripe[stripe].dev->dax_dev;
	bdev = sc->stripe[stripe].dev->bdev;

	ret = bdev_dax_pgoff(bdev, dev_sector, nr_pages * PAGE_SIZE, &pgoff);
	अगर (ret)
		वापस ret;
	वापस dax_direct_access(dax_dev, pgoff, nr_pages, kaddr, pfn);
पूर्ण

अटल माप_प्रकार stripe_dax_copy_from_iter(काष्ठा dm_target *ti, pgoff_t pgoff,
		व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;
	काष्ठा stripe_c *sc = ti->निजी;
	काष्ठा dax_device *dax_dev;
	काष्ठा block_device *bdev;
	uपूर्णांक32_t stripe;

	stripe_map_sector(sc, sector, &stripe, &dev_sector);
	dev_sector += sc->stripe[stripe].physical_start;
	dax_dev = sc->stripe[stripe].dev->dax_dev;
	bdev = sc->stripe[stripe].dev->bdev;

	अगर (bdev_dax_pgoff(bdev, dev_sector, ALIGN(bytes, PAGE_SIZE), &pgoff))
		वापस 0;
	वापस dax_copy_from_iter(dax_dev, pgoff, addr, bytes, i);
पूर्ण

अटल माप_प्रकार stripe_dax_copy_to_iter(काष्ठा dm_target *ti, pgoff_t pgoff,
		व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;
	काष्ठा stripe_c *sc = ti->निजी;
	काष्ठा dax_device *dax_dev;
	काष्ठा block_device *bdev;
	uपूर्णांक32_t stripe;

	stripe_map_sector(sc, sector, &stripe, &dev_sector);
	dev_sector += sc->stripe[stripe].physical_start;
	dax_dev = sc->stripe[stripe].dev->dax_dev;
	bdev = sc->stripe[stripe].dev->bdev;

	अगर (bdev_dax_pgoff(bdev, dev_sector, ALIGN(bytes, PAGE_SIZE), &pgoff))
		वापस 0;
	वापस dax_copy_to_iter(dax_dev, pgoff, addr, bytes, i);
पूर्ण

अटल पूर्णांक stripe_dax_zero_page_range(काष्ठा dm_target *ti, pgoff_t pgoff,
				      माप_प्रकार nr_pages)
अणु
	पूर्णांक ret;
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;
	काष्ठा stripe_c *sc = ti->निजी;
	काष्ठा dax_device *dax_dev;
	काष्ठा block_device *bdev;
	uपूर्णांक32_t stripe;

	stripe_map_sector(sc, sector, &stripe, &dev_sector);
	dev_sector += sc->stripe[stripe].physical_start;
	dax_dev = sc->stripe[stripe].dev->dax_dev;
	bdev = sc->stripe[stripe].dev->bdev;

	ret = bdev_dax_pgoff(bdev, dev_sector, nr_pages << PAGE_SHIFT, &pgoff);
	अगर (ret)
		वापस ret;
	वापस dax_zero_page_range(dax_dev, pgoff, nr_pages);
पूर्ण

#अन्यथा
#घोषणा stripe_dax_direct_access शून्य
#घोषणा stripe_dax_copy_from_iter शून्य
#घोषणा stripe_dax_copy_to_iter शून्य
#घोषणा stripe_dax_zero_page_range शून्य
#पूर्ण_अगर

/*
 * Stripe status:
 *
 * INFO
 * #stripes [stripe_name <stripe_name>] [group word count]
 * [error count 'A|D' <error count 'A|D'>]
 *
 * TABLE
 * #stripes [stripe chunk size]
 * [stripe_name physical_start <stripe_name physical_start>]
 *
 */

अटल व्योम stripe_status(काष्ठा dm_target *ti, status_type_t type,
			  अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा stripe_c *sc = (काष्ठा stripe_c *) ti->निजी;
	अचिन्हित पूर्णांक sz = 0;
	अचिन्हित पूर्णांक i;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%d ", sc->stripes);
		क्रम (i = 0; i < sc->stripes; i++)  अणु
			DMEMIT("%s ", sc->stripe[i].dev->name);
		पूर्ण
		DMEMIT("1 ");
		क्रम (i = 0; i < sc->stripes; i++) अणु
			DMEMIT("%c", atomic_पढ़ो(&(sc->stripe[i].error_count)) ?
			       'D' : 'A');
		पूर्ण
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%d %llu", sc->stripes,
			(अचिन्हित दीर्घ दीर्घ)sc->chunk_size);
		क्रम (i = 0; i < sc->stripes; i++)
			DMEMIT(" %s %llu", sc->stripe[i].dev->name,
			    (अचिन्हित दीर्घ दीर्घ)sc->stripe[i].physical_start);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक stripe_end_io(काष्ठा dm_target *ti, काष्ठा bio *bio,
		blk_status_t *error)
अणु
	अचिन्हित i;
	अक्षर major_minor[16];
	काष्ठा stripe_c *sc = ti->निजी;

	अगर (!*error)
		वापस DM_ENDIO_DONE; /* I/O complete */

	अगर (bio->bi_opf & REQ_RAHEAD)
		वापस DM_ENDIO_DONE;

	अगर (*error == BLK_STS_NOTSUPP)
		वापस DM_ENDIO_DONE;

	स_रखो(major_minor, 0, माप(major_minor));
	प्र_लिखो(major_minor, "%d:%d", MAJOR(bio_dev(bio)), MINOR(bio_dev(bio)));

	/*
	 * Test to see which stripe drive triggered the event
	 * and increment error count क्रम all stripes on that device.
	 * If the error count क्रम a given device exceeds the threshold
	 * value we will no दीर्घer trigger any further events.
	 */
	क्रम (i = 0; i < sc->stripes; i++)
		अगर (!म_भेद(sc->stripe[i].dev->name, major_minor)) अणु
			atomic_inc(&(sc->stripe[i].error_count));
			अगर (atomic_पढ़ो(&(sc->stripe[i].error_count)) <
			    DM_IO_ERROR_THRESHOLD)
				schedule_work(&sc->trigger_event);
		पूर्ण

	वापस DM_ENDIO_DONE;
पूर्ण

अटल पूर्णांक stripe_iterate_devices(काष्ठा dm_target *ti,
				  iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा stripe_c *sc = ti->निजी;
	पूर्णांक ret = 0;
	अचिन्हित i = 0;

	करो अणु
		ret = fn(ti, sc->stripe[i].dev,
			 sc->stripe[i].physical_start,
			 sc->stripe_width, data);
	पूर्ण जबतक (!ret && ++i < sc->stripes);

	वापस ret;
पूर्ण

अटल व्योम stripe_io_hपूर्णांकs(काष्ठा dm_target *ti,
			    काष्ठा queue_limits *limits)
अणु
	काष्ठा stripe_c *sc = ti->निजी;
	अचिन्हित chunk_size = sc->chunk_size << SECTOR_SHIFT;

	blk_limits_io_min(limits, chunk_size);
	blk_limits_io_opt(limits, chunk_size * sc->stripes);
पूर्ण

अटल काष्ठा target_type stripe_target = अणु
	.name   = "striped",
	.version = अणु1, 6, 0पूर्ण,
	.features = DM_TARGET_PASSES_INTEGRITY | DM_TARGET_NOWAIT,
	.module = THIS_MODULE,
	.ctr    = stripe_ctr,
	.dtr    = stripe_dtr,
	.map    = stripe_map,
	.end_io = stripe_end_io,
	.status = stripe_status,
	.iterate_devices = stripe_iterate_devices,
	.io_hपूर्णांकs = stripe_io_hपूर्णांकs,
	.direct_access = stripe_dax_direct_access,
	.dax_copy_from_iter = stripe_dax_copy_from_iter,
	.dax_copy_to_iter = stripe_dax_copy_to_iter,
	.dax_zero_page_range = stripe_dax_zero_page_range,
पूर्ण;

पूर्णांक __init dm_stripe_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_रेजिस्टर_target(&stripe_target);
	अगर (r < 0)
		DMWARN("target registration failed");

	वापस r;
पूर्ण

व्योम dm_stripe_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&stripe_target);
पूर्ण
