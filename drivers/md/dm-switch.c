<शैली गुरु>
/*
 * Copyright (C) 2010-2012 by Dell Inc.  All rights reserved.
 * Copyright (C) 2011-2013 Red Hat, Inc.
 *
 * This file is released under the GPL.
 *
 * dm-चयन is a device-mapper target that maps IO to underlying block
 * devices efficiently when there are a large number of fixed-sized
 * address regions but there is no simple pattern to allow क्रम a compact
 * mapping representation such as dm-stripe.
 */

#समावेश <linux/device-mapper.h>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>

#घोषणा DM_MSG_PREFIX "switch"

/*
 * One region_table_slot_t holds <region_entries_per_slot> region table
 * entries each of which is <region_table_entry_bits> in size.
 */
प्रकार अचिन्हित दीर्घ region_table_slot_t;

/*
 * A device with the offset to its start sector.
 */
काष्ठा चयन_path अणु
	काष्ठा dm_dev *dmdev;
	sector_t start;
पूर्ण;

/*
 * Context block क्रम a dm चयन device.
 */
काष्ठा चयन_ctx अणु
	काष्ठा dm_target *ti;

	अचिन्हित nr_paths;		/* Number of paths in path_list. */

	अचिन्हित region_size;		/* Region size in 512-byte sectors */
	अचिन्हित दीर्घ nr_regions;	/* Number of regions making up the device */
	चिन्हित अक्षर region_size_bits;	/* log2 of region_size or -1 */

	अचिन्हित अक्षर region_table_entry_bits;	/* Number of bits in one region table entry */
	अचिन्हित अक्षर region_entries_per_slot;	/* Number of entries in one region table slot */
	चिन्हित अक्षर region_entries_per_slot_bits;	/* log2 of region_entries_per_slot or -1 */

	region_table_slot_t *region_table;	/* Region table */

	/*
	 * Array of dm devices to चयन between.
	 */
	काष्ठा चयन_path path_list[];
पूर्ण;

अटल काष्ठा चयन_ctx *alloc_चयन_ctx(काष्ठा dm_target *ti, अचिन्हित nr_paths,
					   अचिन्हित region_size)
अणु
	काष्ठा चयन_ctx *sctx;

	sctx = kzalloc(काष्ठा_size(sctx, path_list, nr_paths), GFP_KERNEL);
	अगर (!sctx)
		वापस शून्य;

	sctx->ti = ti;
	sctx->region_size = region_size;

	ti->निजी = sctx;

	वापस sctx;
पूर्ण

अटल पूर्णांक alloc_region_table(काष्ठा dm_target *ti, अचिन्हित nr_paths)
अणु
	काष्ठा चयन_ctx *sctx = ti->निजी;
	sector_t nr_regions = ti->len;
	sector_t nr_slots;

	अगर (!(sctx->region_size & (sctx->region_size - 1)))
		sctx->region_size_bits = __ffs(sctx->region_size);
	अन्यथा
		sctx->region_size_bits = -1;

	sctx->region_table_entry_bits = 1;
	जबतक (sctx->region_table_entry_bits < माप(region_table_slot_t) * 8 &&
	       (region_table_slot_t)1 << sctx->region_table_entry_bits < nr_paths)
		sctx->region_table_entry_bits++;

	sctx->region_entries_per_slot = (माप(region_table_slot_t) * 8) / sctx->region_table_entry_bits;
	अगर (!(sctx->region_entries_per_slot & (sctx->region_entries_per_slot - 1)))
		sctx->region_entries_per_slot_bits = __ffs(sctx->region_entries_per_slot);
	अन्यथा
		sctx->region_entries_per_slot_bits = -1;

	अगर (sector_भाग(nr_regions, sctx->region_size))
		nr_regions++;

	अगर (nr_regions >= अच_दीर्घ_उच्च) अणु
		ti->error = "Region table too large";
		वापस -EINVAL;
	पूर्ण
	sctx->nr_regions = nr_regions;

	nr_slots = nr_regions;
	अगर (sector_भाग(nr_slots, sctx->region_entries_per_slot))
		nr_slots++;

	अगर (nr_slots > अच_दीर्घ_उच्च / माप(region_table_slot_t)) अणु
		ti->error = "Region table too large";
		वापस -EINVAL;
	पूर्ण

	sctx->region_table = vदो_स्मृति(array_size(nr_slots,
						माप(region_table_slot_t)));
	अगर (!sctx->region_table) अणु
		ti->error = "Cannot allocate region table";
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम चयन_get_position(काष्ठा चयन_ctx *sctx, अचिन्हित दीर्घ region_nr,
				अचिन्हित दीर्घ *region_index, अचिन्हित *bit)
अणु
	अगर (sctx->region_entries_per_slot_bits >= 0) अणु
		*region_index = region_nr >> sctx->region_entries_per_slot_bits;
		*bit = region_nr & (sctx->region_entries_per_slot - 1);
	पूर्ण अन्यथा अणु
		*region_index = region_nr / sctx->region_entries_per_slot;
		*bit = region_nr % sctx->region_entries_per_slot;
	पूर्ण

	*bit *= sctx->region_table_entry_bits;
पूर्ण

अटल अचिन्हित चयन_region_table_पढ़ो(काष्ठा चयन_ctx *sctx, अचिन्हित दीर्घ region_nr)
अणु
	अचिन्हित दीर्घ region_index;
	अचिन्हित bit;

	चयन_get_position(sctx, region_nr, &region_index, &bit);

	वापस (READ_ONCE(sctx->region_table[region_index]) >> bit) &
		((1 << sctx->region_table_entry_bits) - 1);
पूर्ण

/*
 * Find which path to use at given offset.
 */
अटल अचिन्हित चयन_get_path_nr(काष्ठा चयन_ctx *sctx, sector_t offset)
अणु
	अचिन्हित path_nr;
	sector_t p;

	p = offset;
	अगर (sctx->region_size_bits >= 0)
		p >>= sctx->region_size_bits;
	अन्यथा
		sector_भाग(p, sctx->region_size);

	path_nr = चयन_region_table_पढ़ो(sctx, p);

	/* This can only happen अगर the processor uses non-atomic stores. */
	अगर (unlikely(path_nr >= sctx->nr_paths))
		path_nr = 0;

	वापस path_nr;
पूर्ण

अटल व्योम चयन_region_table_ग_लिखो(काष्ठा चयन_ctx *sctx, अचिन्हित दीर्घ region_nr,
				      अचिन्हित value)
अणु
	अचिन्हित दीर्घ region_index;
	अचिन्हित bit;
	region_table_slot_t pte;

	चयन_get_position(sctx, region_nr, &region_index, &bit);

	pte = sctx->region_table[region_index];
	pte &= ~((((region_table_slot_t)1 << sctx->region_table_entry_bits) - 1) << bit);
	pte |= (region_table_slot_t)value << bit;
	sctx->region_table[region_index] = pte;
पूर्ण

/*
 * Fill the region table with an initial round robin pattern.
 */
अटल व्योम initialise_region_table(काष्ठा चयन_ctx *sctx)
अणु
	अचिन्हित path_nr = 0;
	अचिन्हित दीर्घ region_nr;

	क्रम (region_nr = 0; region_nr < sctx->nr_regions; region_nr++) अणु
		चयन_region_table_ग_लिखो(sctx, region_nr, path_nr);
		अगर (++path_nr >= sctx->nr_paths)
			path_nr = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक parse_path(काष्ठा dm_arg_set *as, काष्ठा dm_target *ti)
अणु
	काष्ठा चयन_ctx *sctx = ti->निजी;
	अचिन्हित दीर्घ दीर्घ start;
	पूर्णांक r;

	r = dm_get_device(ti, dm_shअगरt_arg(as), dm_table_get_mode(ti->table),
			  &sctx->path_list[sctx->nr_paths].dmdev);
	अगर (r) अणु
		ti->error = "Device lookup failed";
		वापस r;
	पूर्ण

	अगर (kम_से_अदीर्घl(dm_shअगरt_arg(as), 10, &start) || start != (sector_t)start) अणु
		ti->error = "Invalid device starting offset";
		dm_put_device(ti, sctx->path_list[sctx->nr_paths].dmdev);
		वापस -EINVAL;
	पूर्ण

	sctx->path_list[sctx->nr_paths].start = start;

	sctx->nr_paths++;

	वापस 0;
पूर्ण

/*
 * Deकाष्ठाor: Don't मुक्त the dm_target, just the ti->निजी data (अगर any).
 */
अटल व्योम चयन_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा चयन_ctx *sctx = ti->निजी;

	जबतक (sctx->nr_paths--)
		dm_put_device(ti, sctx->path_list[sctx->nr_paths].dmdev);

	vमुक्त(sctx->region_table);
	kमुक्त(sctx);
पूर्ण

/*
 * Conकाष्ठाor arguments:
 *   <num_paths> <region_size> <num_optional_args> [<optional_args>...]
 *   [<dev_path> <offset>]+
 *
 * Optional args are to allow क्रम future extension: currently this
 * parameter must be 0.
 */
अटल पूर्णांक चयन_ctr(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv)
अणु
	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु1, (KMALLOC_MAX_SIZE - माप(काष्ठा चयन_ctx)) / माप(काष्ठा चयन_path), "Invalid number of paths"पूर्ण,
		अणु1, अच_पूर्णांक_उच्च, "Invalid region size"पूर्ण,
		अणु0, 0, "Invalid number of optional args"पूर्ण,
	पूर्ण;

	काष्ठा चयन_ctx *sctx;
	काष्ठा dm_arg_set as;
	अचिन्हित nr_paths, region_size, nr_optional_args;
	पूर्णांक r;

	as.argc = argc;
	as.argv = argv;

	r = dm_पढ़ो_arg(_args, &as, &nr_paths, &ti->error);
	अगर (r)
		वापस -EINVAL;

	r = dm_पढ़ो_arg(_args + 1, &as, &region_size, &ti->error);
	अगर (r)
		वापस r;

	r = dm_पढ़ो_arg_group(_args + 2, &as, &nr_optional_args, &ti->error);
	अगर (r)
		वापस r;
	/* parse optional arguments here, अगर we add any */

	अगर (as.argc != nr_paths * 2) अणु
		ti->error = "Incorrect number of path arguments";
		वापस -EINVAL;
	पूर्ण

	sctx = alloc_चयन_ctx(ti, nr_paths, region_size);
	अगर (!sctx) अणु
		ti->error = "Cannot allocate redirection context";
		वापस -ENOMEM;
	पूर्ण

	r = dm_set_target_max_io_len(ti, region_size);
	अगर (r)
		जाओ error;

	जबतक (as.argc) अणु
		r = parse_path(&as, ti);
		अगर (r)
			जाओ error;
	पूर्ण

	r = alloc_region_table(ti, nr_paths);
	अगर (r)
		जाओ error;

	initialise_region_table(sctx);

	/* For UNMAP, sending the request करोwn any path is sufficient */
	ti->num_discard_bios = 1;

	वापस 0;

error:
	चयन_dtr(ti);

	वापस r;
पूर्ण

अटल पूर्णांक चयन_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा चयन_ctx *sctx = ti->निजी;
	sector_t offset = dm_target_offset(ti, bio->bi_iter.bi_sector);
	अचिन्हित path_nr = चयन_get_path_nr(sctx, offset);

	bio_set_dev(bio, sctx->path_list[path_nr].dmdev->bdev);
	bio->bi_iter.bi_sector = sctx->path_list[path_nr].start + offset;

	वापस DM_MAPIO_REMAPPED;
पूर्ण

/*
 * We need to parse hex numbers in the message as quickly as possible.
 *
 * This table-based hex parser improves perक्रमmance.
 * It improves a समय to load 1000000 entries compared to the condition-based
 * parser.
 *		table-based parser	condition-based parser
 * PA-RISC	0.29s			0.31s
 * Opteron	0.0495s			0.0498s
 */
अटल स्थिर अचिन्हित अक्षर hex_table[256] = अणु
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 255, 255, 255, 255, 255, 255,
255, 10, 11, 12, 13, 14, 15, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 10, 11, 12, 13, 14, 15, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
पूर्ण;

अटल __always_अंतरभूत अचिन्हित दीर्घ parse_hex(स्थिर अक्षर **string)
अणु
	अचिन्हित अक्षर d;
	अचिन्हित दीर्घ r = 0;

	जबतक ((d = hex_table[(अचिन्हित अक्षर)**string]) < 16) अणु
		r = (r << 4) | d;
		(*string)++;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक process_set_region_mappings(काष्ठा चयन_ctx *sctx,
				       अचिन्हित argc, अक्षर **argv)
अणु
	अचिन्हित i;
	अचिन्हित दीर्घ region_index = 0;

	क्रम (i = 1; i < argc; i++) अणु
		अचिन्हित दीर्घ path_nr;
		स्थिर अक्षर *string = argv[i];

		अगर ((*string & 0xdf) == 'R') अणु
			अचिन्हित दीर्घ cycle_length, num_ग_लिखो;

			string++;
			अगर (unlikely(*string == ',')) अणु
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				वापस -EINVAL;
			पूर्ण
			cycle_length = parse_hex(&string);
			अगर (unlikely(*string != ',')) अणु
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				वापस -EINVAL;
			पूर्ण
			string++;
			अगर (unlikely(!*string)) अणु
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				वापस -EINVAL;
			पूर्ण
			num_ग_लिखो = parse_hex(&string);
			अगर (unlikely(*string)) अणु
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				वापस -EINVAL;
			पूर्ण

			अगर (unlikely(!cycle_length) || unlikely(cycle_length - 1 > region_index)) अणु
				DMWARN("invalid set_region_mappings cycle length: %lu > %lu",
				       cycle_length - 1, region_index);
				वापस -EINVAL;
			पूर्ण
			अगर (unlikely(region_index + num_ग_लिखो < region_index) ||
			    unlikely(region_index + num_ग_लिखो >= sctx->nr_regions)) अणु
				DMWARN("invalid set_region_mappings region number: %lu + %lu >= %lu",
				       region_index, num_ग_लिखो, sctx->nr_regions);
				वापस -EINVAL;
			पूर्ण

			जबतक (num_ग_लिखो--) अणु
				region_index++;
				path_nr = चयन_region_table_पढ़ो(sctx, region_index - cycle_length);
				चयन_region_table_ग_लिखो(sctx, region_index, path_nr);
			पूर्ण

			जारी;
		पूर्ण

		अगर (*string == ':')
			region_index++;
		अन्यथा अणु
			region_index = parse_hex(&string);
			अगर (unlikely(*string != ':')) अणु
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		string++;
		अगर (unlikely(!*string)) अणु
			DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
			वापस -EINVAL;
		पूर्ण

		path_nr = parse_hex(&string);
		अगर (unlikely(*string)) अणु
			DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely(region_index >= sctx->nr_regions)) अणु
			DMWARN("invalid set_region_mappings region number: %lu >= %lu", region_index, sctx->nr_regions);
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely(path_nr >= sctx->nr_paths)) अणु
			DMWARN("invalid set_region_mappings device: %lu >= %u", path_nr, sctx->nr_paths);
			वापस -EINVAL;
		पूर्ण

		चयन_region_table_ग_लिखो(sctx, region_index, path_nr);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Messages are processed one-at-a-समय.
 *
 * Only set_region_mappings is supported.
 */
अटल पूर्णांक चयन_message(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv,
			  अक्षर *result, अचिन्हित maxlen)
अणु
	अटल DEFINE_MUTEX(message_mutex);

	काष्ठा चयन_ctx *sctx = ti->निजी;
	पूर्णांक r = -EINVAL;

	mutex_lock(&message_mutex);

	अगर (!strहालcmp(argv[0], "set_region_mappings"))
		r = process_set_region_mappings(sctx, argc, argv);
	अन्यथा
		DMWARN("Unrecognised message received.");

	mutex_unlock(&message_mutex);

	वापस r;
पूर्ण

अटल व्योम चयन_status(काष्ठा dm_target *ti, status_type_t type,
			  अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा चयन_ctx *sctx = ti->निजी;
	अचिन्हित sz = 0;
	पूर्णांक path_nr;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		result[0] = '\0';
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%u %u 0", sctx->nr_paths, sctx->region_size);
		क्रम (path_nr = 0; path_nr < sctx->nr_paths; path_nr++)
			DMEMIT(" %s %llu", sctx->path_list[path_nr].dmdev->name,
			       (अचिन्हित दीर्घ दीर्घ)sctx->path_list[path_nr].start);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Switch ioctl:
 *
 * Passthrough all ioctls to the path क्रम sector 0
 */
अटल पूर्णांक चयन_prepare_ioctl(काष्ठा dm_target *ti, काष्ठा block_device **bdev)
अणु
	काष्ठा चयन_ctx *sctx = ti->निजी;
	अचिन्हित path_nr;

	path_nr = चयन_get_path_nr(sctx, 0);

	*bdev = sctx->path_list[path_nr].dmdev->bdev;

	/*
	 * Only pass ioctls through अगर the device sizes match exactly.
	 */
	अगर (ti->len + sctx->path_list[path_nr].start !=
	    i_size_पढ़ो((*bdev)->bd_inode) >> SECTOR_SHIFT)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक चयन_iterate_devices(काष्ठा dm_target *ti,
				  iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा चयन_ctx *sctx = ti->निजी;
	पूर्णांक path_nr;
	पूर्णांक r;

	क्रम (path_nr = 0; path_nr < sctx->nr_paths; path_nr++) अणु
		r = fn(ti, sctx->path_list[path_nr].dmdev,
			 sctx->path_list[path_nr].start, ti->len, data);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा target_type चयन_target = अणु
	.name = "switch",
	.version = अणु1, 1, 0पूर्ण,
	.features = DM_TARGET_NOWAIT,
	.module = THIS_MODULE,
	.ctr = चयन_ctr,
	.dtr = चयन_dtr,
	.map = चयन_map,
	.message = चयन_message,
	.status = चयन_status,
	.prepare_ioctl = चयन_prepare_ioctl,
	.iterate_devices = चयन_iterate_devices,
पूर्ण;

अटल पूर्णांक __init dm_चयन_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_रेजिस्टर_target(&चयन_target);
	अगर (r < 0)
		DMERR("dm_register_target() failed %d", r);

	वापस r;
पूर्ण

अटल व्योम __निकास dm_चयन_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&चयन_target);
पूर्ण

module_init(dm_चयन_init);
module_निकास(dm_चयन_निकास);

MODULE_DESCRIPTION(DM_NAME " dynamic path switching target");
MODULE_AUTHOR("Kevin D. O'Kelley <Kevin_OKelley@dell.com>");
MODULE_AUTHOR("Narendran Ganapathy <Narendran_Ganapathy@dell.com>");
MODULE_AUTHOR("Jim Ramsay <Jim_Ramsay@dell.com>");
MODULE_AUTHOR("Mikulas Patocka <mpatocka@redhat.com>");
MODULE_LICENSE("GPL");
