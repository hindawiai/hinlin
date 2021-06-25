<शैली गुरु>
/*
 * Copyright (C) 2017 Intel Corporation.
 *
 * This file is released under the GPL.
 */

#समावेश "dm.h"

#समावेश <linux/module.h>

काष्ठा unstripe_c अणु
	काष्ठा dm_dev *dev;
	sector_t physical_start;

	uपूर्णांक32_t stripes;

	uपूर्णांक32_t unstripe;
	sector_t unstripe_width;
	sector_t unstripe_offset;

	uपूर्णांक32_t chunk_size;
	u8 chunk_shअगरt;
पूर्ण;

#घोषणा DM_MSG_PREFIX "unstriped"

अटल व्योम cleanup_unstripe(काष्ठा unstripe_c *uc, काष्ठा dm_target *ti)
अणु
	अगर (uc->dev)
		dm_put_device(ti, uc->dev);
	kमुक्त(uc);
पूर्ण

/*
 * Contruct an unstriped mapping.
 * <number of stripes> <chunk size> <stripe #> <dev_path> <offset>
 */
अटल पूर्णांक unstripe_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा unstripe_c *uc;
	sector_t पंचांगp_len;
	अचिन्हित दीर्घ दीर्घ start;
	अक्षर dummy;

	अगर (argc != 5) अणु
		ti->error = "Invalid number of arguments";
		वापस -EINVAL;
	पूर्ण

	uc = kzalloc(माप(*uc), GFP_KERNEL);
	अगर (!uc) अणु
		ti->error = "Memory allocation for unstriped context failed";
		वापस -ENOMEM;
	पूर्ण

	अगर (kstrtouपूर्णांक(argv[0], 10, &uc->stripes) || !uc->stripes) अणु
		ti->error = "Invalid stripe count";
		जाओ err;
	पूर्ण

	अगर (kstrtouपूर्णांक(argv[1], 10, &uc->chunk_size) || !uc->chunk_size) अणु
		ti->error = "Invalid chunk_size";
		जाओ err;
	पूर्ण

	अगर (kstrtouपूर्णांक(argv[2], 10, &uc->unstripe)) अणु
		ti->error = "Invalid stripe number";
		जाओ err;
	पूर्ण

	अगर (uc->unstripe > uc->stripes && uc->stripes > 1) अणु
		ti->error = "Please provide stripe between [0, # of stripes]";
		जाओ err;
	पूर्ण

	अगर (dm_get_device(ti, argv[3], dm_table_get_mode(ti->table), &uc->dev)) अणु
		ti->error = "Couldn't get striped device";
		जाओ err;
	पूर्ण

	अगर (माला_पूछो(argv[4], "%llu%c", &start, &dummy) != 1 || start != (sector_t)start) अणु
		ti->error = "Invalid striped device offset";
		जाओ err;
	पूर्ण
	uc->physical_start = start;

	uc->unstripe_offset = uc->unstripe * uc->chunk_size;
	uc->unstripe_width = (uc->stripes - 1) * uc->chunk_size;
	uc->chunk_shअगरt = is_घातer_of_2(uc->chunk_size) ? fls(uc->chunk_size) - 1 : 0;

	पंचांगp_len = ti->len;
	अगर (sector_भाग(पंचांगp_len, uc->chunk_size)) अणु
		ti->error = "Target length not divisible by chunk size";
		जाओ err;
	पूर्ण

	अगर (dm_set_target_max_io_len(ti, uc->chunk_size)) अणु
		ti->error = "Failed to set max io len";
		जाओ err;
	पूर्ण

	ti->निजी = uc;
	वापस 0;
err:
	cleanup_unstripe(uc, ti);
	वापस -EINVAL;
पूर्ण

अटल व्योम unstripe_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा unstripe_c *uc = ti->निजी;

	cleanup_unstripe(uc, ti);
पूर्ण

अटल sector_t map_to_core(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा unstripe_c *uc = ti->निजी;
	sector_t sector = bio->bi_iter.bi_sector;
	sector_t पंचांगp_sector = sector;

	/* Shअगरt us up to the right "row" on the stripe */
	अगर (uc->chunk_shअगरt)
		पंचांगp_sector >>= uc->chunk_shअगरt;
	अन्यथा
		sector_भाग(पंचांगp_sector, uc->chunk_size);

	sector += uc->unstripe_width * पंचांगp_sector;

	/* Account क्रम what stripe we're operating on */
	वापस sector + uc->unstripe_offset;
पूर्ण

अटल पूर्णांक unstripe_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा unstripe_c *uc = ti->निजी;

	bio_set_dev(bio, uc->dev->bdev);
	bio->bi_iter.bi_sector = map_to_core(ti, bio) + uc->physical_start;

	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल व्योम unstripe_status(काष्ठा dm_target *ti, status_type_t type,
			    अचिन्हित पूर्णांक status_flags, अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	काष्ठा unstripe_c *uc = ti->निजी;
	अचिन्हित पूर्णांक sz = 0;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%d %llu %d %s %llu",
		       uc->stripes, (अचिन्हित दीर्घ दीर्घ)uc->chunk_size, uc->unstripe,
		       uc->dev->name, (अचिन्हित दीर्घ दीर्घ)uc->physical_start);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक unstripe_iterate_devices(काष्ठा dm_target *ti,
				    iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा unstripe_c *uc = ti->निजी;

	वापस fn(ti, uc->dev, uc->physical_start, ti->len, data);
पूर्ण

अटल व्योम unstripe_io_hपूर्णांकs(काष्ठा dm_target *ti,
			       काष्ठा queue_limits *limits)
अणु
	काष्ठा unstripe_c *uc = ti->निजी;

	limits->chunk_sectors = uc->chunk_size;
पूर्ण

अटल काष्ठा target_type unstripe_target = अणु
	.name = "unstriped",
	.version = अणु1, 1, 0पूर्ण,
	.features = DM_TARGET_NOWAIT,
	.module = THIS_MODULE,
	.ctr = unstripe_ctr,
	.dtr = unstripe_dtr,
	.map = unstripe_map,
	.status = unstripe_status,
	.iterate_devices = unstripe_iterate_devices,
	.io_hपूर्णांकs = unstripe_io_hपूर्णांकs,
पूर्ण;

अटल पूर्णांक __init dm_unstripe_init(व्योम)
अणु
	वापस dm_रेजिस्टर_target(&unstripe_target);
पूर्ण

अटल व्योम __निकास dm_unstripe_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&unstripe_target);
पूर्ण

module_init(dm_unstripe_init);
module_निकास(dm_unstripe_निकास);

MODULE_DESCRIPTION(DM_NAME " unstriped target");
MODULE_ALIAS("dm-unstriped");
MODULE_AUTHOR("Scott Bauer <scott.bauer@intel.com>");
MODULE_LICENSE("GPL");
