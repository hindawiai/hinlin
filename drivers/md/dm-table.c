<शैली गुरु>
/*
 * Copyright (C) 2001 Sistina Software (UK) Limited.
 * Copyright (C) 2004-2008 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-core.h"

#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/namei.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/atomic.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/mount.h>
#समावेश <linux/dax.h>

#घोषणा DM_MSG_PREFIX "table"

#घोषणा NODE_SIZE L1_CACHE_BYTES
#घोषणा KEYS_PER_NODE (NODE_SIZE / माप(sector_t))
#घोषणा CHILDREN_PER_NODE (KEYS_PER_NODE + 1)

/*
 * Similar to उच्चमानing(log_size(n))
 */
अटल अचिन्हित पूर्णांक पूर्णांक_log(अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक base)
अणु
	पूर्णांक result = 0;

	जबतक (n > 1) अणु
		n = dm_भाग_up(n, base);
		result++;
	पूर्ण

	वापस result;
पूर्ण

/*
 * Calculate the index of the child node of the n'th node k'th key.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_child(अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक k)
अणु
	वापस (n * CHILDREN_PER_NODE) + k;
पूर्ण

/*
 * Return the n'th node of level l from table t.
 */
अटल अंतरभूत sector_t *get_node(काष्ठा dm_table *t,
				 अचिन्हित पूर्णांक l, अचिन्हित पूर्णांक n)
अणु
	वापस t->index[l] + (n * KEYS_PER_NODE);
पूर्ण

/*
 * Return the highest key that you could lookup from the n'th
 * node on level l of the btree.
 */
अटल sector_t high(काष्ठा dm_table *t, अचिन्हित पूर्णांक l, अचिन्हित पूर्णांक n)
अणु
	क्रम (; l < t->depth - 1; l++)
		n = get_child(n, CHILDREN_PER_NODE - 1);

	अगर (n >= t->counts[l])
		वापस (sector_t) - 1;

	वापस get_node(t, l, n)[KEYS_PER_NODE - 1];
पूर्ण

/*
 * Fills in a level of the btree based on the highs of the level
 * below it.
 */
अटल पूर्णांक setup_btree_index(अचिन्हित पूर्णांक l, काष्ठा dm_table *t)
अणु
	अचिन्हित पूर्णांक n, k;
	sector_t *node;

	क्रम (n = 0U; n < t->counts[l]; n++) अणु
		node = get_node(t, l, n);

		क्रम (k = 0U; k < KEYS_PER_NODE; k++)
			node[k] = high(t, l + 1, get_child(n, k));
	पूर्ण

	वापस 0;
पूर्ण

/*
 * highs, and tarमाला_लो are managed as dynamic arrays during a
 * table load.
 */
अटल पूर्णांक alloc_tarमाला_लो(काष्ठा dm_table *t, अचिन्हित पूर्णांक num)
अणु
	sector_t *n_highs;
	काष्ठा dm_target *n_tarमाला_लो;

	/*
	 * Allocate both the target array and offset array at once.
	 */
	n_highs = kvसुस्मृति(num, माप(काष्ठा dm_target) + माप(sector_t),
			   GFP_KERNEL);
	अगर (!n_highs)
		वापस -ENOMEM;

	n_tarमाला_लो = (काष्ठा dm_target *) (n_highs + num);

	स_रखो(n_highs, -1, माप(*n_highs) * num);
	kvमुक्त(t->highs);

	t->num_allocated = num;
	t->highs = n_highs;
	t->tarमाला_लो = n_tarमाला_लो;

	वापस 0;
पूर्ण

पूर्णांक dm_table_create(काष्ठा dm_table **result, भ_शेषe_t mode,
		    अचिन्हित num_tarमाला_लो, काष्ठा mapped_device *md)
अणु
	काष्ठा dm_table *t = kzalloc(माप(*t), GFP_KERNEL);

	अगर (!t)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&t->devices);

	अगर (!num_tarमाला_लो)
		num_tarमाला_लो = KEYS_PER_NODE;

	num_tarमाला_लो = dm_round_up(num_tarमाला_लो, KEYS_PER_NODE);

	अगर (!num_tarमाला_लो) अणु
		kमुक्त(t);
		वापस -ENOMEM;
	पूर्ण

	अगर (alloc_tarमाला_लो(t, num_tarमाला_लो)) अणु
		kमुक्त(t);
		वापस -ENOMEM;
	पूर्ण

	t->type = DM_TYPE_NONE;
	t->mode = mode;
	t->md = md;
	*result = t;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_devices(काष्ठा list_head *devices, काष्ठा mapped_device *md)
अणु
	काष्ठा list_head *पंचांगp, *next;

	list_क्रम_each_safe(पंचांगp, next, devices) अणु
		काष्ठा dm_dev_पूर्णांकernal *dd =
		    list_entry(पंचांगp, काष्ठा dm_dev_पूर्णांकernal, list);
		DMWARN("%s: dm_table_destroy: dm_put_device call missing for %s",
		       dm_device_name(md), dd->dm_dev->name);
		dm_put_table_device(md, dd->dm_dev);
		kमुक्त(dd);
	पूर्ण
पूर्ण

अटल व्योम dm_table_destroy_keyslot_manager(काष्ठा dm_table *t);

व्योम dm_table_destroy(काष्ठा dm_table *t)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!t)
		वापस;

	/* मुक्त the indexes */
	अगर (t->depth >= 2)
		kvमुक्त(t->index[t->depth - 2]);

	/* मुक्त the tarमाला_लो */
	क्रम (i = 0; i < t->num_tarमाला_लो; i++) अणु
		काष्ठा dm_target *tgt = t->tarमाला_लो + i;

		अगर (tgt->type->dtr)
			tgt->type->dtr(tgt);

		dm_put_target_type(tgt->type);
	पूर्ण

	kvमुक्त(t->highs);

	/* मुक्त the device list */
	मुक्त_devices(&t->devices, t->md);

	dm_मुक्त_md_mempools(t->mempools);

	dm_table_destroy_keyslot_manager(t);

	kमुक्त(t);
पूर्ण

/*
 * See अगर we've alपढ़ोy got a device in the list.
 */
अटल काष्ठा dm_dev_पूर्णांकernal *find_device(काष्ठा list_head *l, dev_t dev)
अणु
	काष्ठा dm_dev_पूर्णांकernal *dd;

	list_क्रम_each_entry (dd, l, list)
		अगर (dd->dm_dev->bdev->bd_dev == dev)
			वापस dd;

	वापस शून्य;
पूर्ण

/*
 * If possible, this checks an area of a destination device is invalid.
 */
अटल पूर्णांक device_area_is_invalid(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
				  sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा queue_limits *limits = data;
	काष्ठा block_device *bdev = dev->bdev;
	sector_t dev_size =
		i_size_पढ़ो(bdev->bd_inode) >> SECTOR_SHIFT;
	अचिन्हित लघु logical_block_size_sectors =
		limits->logical_block_size >> SECTOR_SHIFT;
	अक्षर b[BDEVNAME_SIZE];

	अगर (!dev_size)
		वापस 0;

	अगर ((start >= dev_size) || (start + len > dev_size)) अणु
		DMWARN("%s: %s too small for target: "
		       "start=%llu, len=%llu, dev_size=%llu",
		       dm_device_name(ti->table->md), bdevname(bdev, b),
		       (अचिन्हित दीर्घ दीर्घ)start,
		       (अचिन्हित दीर्घ दीर्घ)len,
		       (अचिन्हित दीर्घ दीर्घ)dev_size);
		वापस 1;
	पूर्ण

	/*
	 * If the target is mapped to zoned block device(s), check
	 * that the zones are not partially mapped.
	 */
	अगर (bdev_zoned_model(bdev) != BLK_ZONED_NONE) अणु
		अचिन्हित पूर्णांक zone_sectors = bdev_zone_sectors(bdev);

		अगर (start & (zone_sectors - 1)) अणु
			DMWARN("%s: start=%llu not aligned to h/w zone size %u of %s",
			       dm_device_name(ti->table->md),
			       (अचिन्हित दीर्घ दीर्घ)start,
			       zone_sectors, bdevname(bdev, b));
			वापस 1;
		पूर्ण

		/*
		 * Note: The last zone of a zoned block device may be smaller
		 * than other zones. So क्रम a target mapping the end of a
		 * zoned block device with such a zone, len would not be zone
		 * aligned. We करो not allow such last smaller zone to be part
		 * of the mapping here to ensure that mappings with multiple
		 * devices करो not end up with a smaller zone in the middle of
		 * the sector range.
		 */
		अगर (len & (zone_sectors - 1)) अणु
			DMWARN("%s: len=%llu not aligned to h/w zone size %u of %s",
			       dm_device_name(ti->table->md),
			       (अचिन्हित दीर्घ दीर्घ)len,
			       zone_sectors, bdevname(bdev, b));
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (logical_block_size_sectors <= 1)
		वापस 0;

	अगर (start & (logical_block_size_sectors - 1)) अणु
		DMWARN("%s: start=%llu not aligned to h/w "
		       "logical block size %u of %s",
		       dm_device_name(ti->table->md),
		       (अचिन्हित दीर्घ दीर्घ)start,
		       limits->logical_block_size, bdevname(bdev, b));
		वापस 1;
	पूर्ण

	अगर (len & (logical_block_size_sectors - 1)) अणु
		DMWARN("%s: len=%llu not aligned to h/w "
		       "logical block size %u of %s",
		       dm_device_name(ti->table->md),
		       (अचिन्हित दीर्घ दीर्घ)len,
		       limits->logical_block_size, bdevname(bdev, b));
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This upgrades the mode on an alपढ़ोy खोलो dm_dev, being
 * careful to leave things as they were अगर we fail to reखोलो the
 * device and not to touch the existing bdev field in हाल
 * it is accessed concurrently.
 */
अटल पूर्णांक upgrade_mode(काष्ठा dm_dev_पूर्णांकernal *dd, भ_शेषe_t new_mode,
			काष्ठा mapped_device *md)
अणु
	पूर्णांक r;
	काष्ठा dm_dev *old_dev, *new_dev;

	old_dev = dd->dm_dev;

	r = dm_get_table_device(md, dd->dm_dev->bdev->bd_dev,
				dd->dm_dev->mode | new_mode, &new_dev);
	अगर (r)
		वापस r;

	dd->dm_dev = new_dev;
	dm_put_table_device(md, old_dev);

	वापस 0;
पूर्ण

/*
 * Convert the path to a device
 */
dev_t dm_get_dev_t(स्थिर अक्षर *path)
अणु
	dev_t dev;

	अगर (lookup_bdev(path, &dev))
		dev = name_to_dev_t(path);
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(dm_get_dev_t);

/*
 * Add a device to the list, or just increment the usage count अगर
 * it's alपढ़ोy present.
 */
पूर्णांक dm_get_device(काष्ठा dm_target *ti, स्थिर अक्षर *path, भ_शेषe_t mode,
		  काष्ठा dm_dev **result)
अणु
	पूर्णांक r;
	dev_t dev;
	अचिन्हित पूर्णांक major, minor;
	अक्षर dummy;
	काष्ठा dm_dev_पूर्णांकernal *dd;
	काष्ठा dm_table *t = ti->table;

	BUG_ON(!t);

	अगर (माला_पूछो(path, "%u:%u%c", &major, &minor, &dummy) == 2) अणु
		/* Extract the major/minor numbers */
		dev = MKDEV(major, minor);
		अगर (MAJOR(dev) != major || MINOR(dev) != minor)
			वापस -EOVERFLOW;
	पूर्ण अन्यथा अणु
		dev = dm_get_dev_t(path);
		अगर (!dev)
			वापस -ENODEV;
	पूर्ण

	dd = find_device(&t->devices, dev);
	अगर (!dd) अणु
		dd = kदो_स्मृति(माप(*dd), GFP_KERNEL);
		अगर (!dd)
			वापस -ENOMEM;

		अगर ((r = dm_get_table_device(t->md, dev, mode, &dd->dm_dev))) अणु
			kमुक्त(dd);
			वापस r;
		पूर्ण

		refcount_set(&dd->count, 1);
		list_add(&dd->list, &t->devices);
		जाओ out;

	पूर्ण अन्यथा अगर (dd->dm_dev->mode != (mode | dd->dm_dev->mode)) अणु
		r = upgrade_mode(dd, mode, t->md);
		अगर (r)
			वापस r;
	पूर्ण
	refcount_inc(&dd->count);
out:
	*result = dd->dm_dev;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dm_get_device);

अटल पूर्णांक dm_set_device_limits(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
				sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा queue_limits *limits = data;
	काष्ठा block_device *bdev = dev->bdev;
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	अक्षर b[BDEVNAME_SIZE];

	अगर (unlikely(!q)) अणु
		DMWARN("%s: Cannot set limits for nonexistent device %s",
		       dm_device_name(ti->table->md), bdevname(bdev, b));
		वापस 0;
	पूर्ण

	अगर (blk_stack_limits(limits, &q->limits,
			get_start_sect(bdev) + start) < 0)
		DMWARN("%s: adding target device %s caused an alignment inconsistency: "
		       "physical_block_size=%u, logical_block_size=%u, "
		       "alignment_offset=%u, start=%llu",
		       dm_device_name(ti->table->md), bdevname(bdev, b),
		       q->limits.physical_block_size,
		       q->limits.logical_block_size,
		       q->limits.alignment_offset,
		       (अचिन्हित दीर्घ दीर्घ) start << SECTOR_SHIFT);
	वापस 0;
पूर्ण

/*
 * Decrement a device's use count and हटाओ it अगर necessary.
 */
व्योम dm_put_device(काष्ठा dm_target *ti, काष्ठा dm_dev *d)
अणु
	पूर्णांक found = 0;
	काष्ठा list_head *devices = &ti->table->devices;
	काष्ठा dm_dev_पूर्णांकernal *dd;

	list_क्रम_each_entry(dd, devices, list) अणु
		अगर (dd->dm_dev == d) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		DMWARN("%s: device %s not in table devices list",
		       dm_device_name(ti->table->md), d->name);
		वापस;
	पूर्ण
	अगर (refcount_dec_and_test(&dd->count)) अणु
		dm_put_table_device(ti->table->md, d);
		list_del(&dd->list);
		kमुक्त(dd);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dm_put_device);

/*
 * Checks to see अगर the target joins onto the end of the table.
 */
अटल पूर्णांक adjoin(काष्ठा dm_table *table, काष्ठा dm_target *ti)
अणु
	काष्ठा dm_target *prev;

	अगर (!table->num_tarमाला_लो)
		वापस !ti->begin;

	prev = &table->tarमाला_लो[table->num_tarमाला_लो - 1];
	वापस (ti->begin == (prev->begin + prev->len));
पूर्ण

/*
 * Used to dynamically allocate the arg array.
 *
 * We करो first allocation with GFP_NOIO because dm-mpath and dm-thin must
 * process messages even अगर some device is suspended. These messages have a
 * small fixed number of arguments.
 *
 * On the other hand, dm-चयन needs to process bulk data using messages and
 * excessive use of GFP_NOIO could cause trouble.
 */
अटल अक्षर **पुनः_स्मृति_argv(अचिन्हित *size, अक्षर **old_argv)
अणु
	अक्षर **argv;
	अचिन्हित new_size;
	gfp_t gfp;

	अगर (*size) अणु
		new_size = *size * 2;
		gfp = GFP_KERNEL;
	पूर्ण अन्यथा अणु
		new_size = 8;
		gfp = GFP_NOIO;
	पूर्ण
	argv = kदो_स्मृति_array(new_size, माप(*argv), gfp);
	अगर (argv && old_argv) अणु
		स_नकल(argv, old_argv, *size * माप(*argv));
		*size = new_size;
	पूर्ण

	kमुक्त(old_argv);
	वापस argv;
पूर्ण

/*
 * Deकाष्ठाively splits up the argument list to pass to ctr.
 */
पूर्णांक dm_split_args(पूर्णांक *argc, अक्षर ***argvp, अक्षर *input)
अणु
	अक्षर *start, *end = input, *out, **argv = शून्य;
	अचिन्हित array_size = 0;

	*argc = 0;

	अगर (!input) अणु
		*argvp = शून्य;
		वापस 0;
	पूर्ण

	argv = पुनः_स्मृति_argv(&array_size, argv);
	अगर (!argv)
		वापस -ENOMEM;

	जबतक (1) अणु
		/* Skip whitespace */
		start = skip_spaces(end);

		अगर (!*start)
			अवरोध;	/* success, we hit the end */

		/* 'out' is used to हटाओ any back-quotes */
		end = out = start;
		जबतक (*end) अणु
			/* Everything apart from '\0' can be quoted */
			अगर (*end == '\\' && *(end + 1)) अणु
				*out++ = *(end + 1);
				end += 2;
				जारी;
			पूर्ण

			अगर (है_खाली(*end))
				अवरोध;	/* end of token */

			*out++ = *end++;
		पूर्ण

		/* have we alपढ़ोy filled the array ? */
		अगर ((*argc + 1) > array_size) अणु
			argv = पुनः_स्मृति_argv(&array_size, argv);
			अगर (!argv)
				वापस -ENOMEM;
		पूर्ण

		/* we know this is whitespace */
		अगर (*end)
			end++;

		/* terminate the string and put it in the array */
		*out = '\0';
		argv[*argc] = start;
		(*argc)++;
	पूर्ण

	*argvp = argv;
	वापस 0;
पूर्ण

/*
 * Impose necessary and sufficient conditions on a devices's table such
 * that any incoming bio which respects its logical_block_size can be
 * processed successfully.  If it falls across the boundary between
 * two or more tarमाला_लो, the size of each piece it माला_लो split पूर्णांकo must
 * be compatible with the logical_block_size of the target processing it.
 */
अटल पूर्णांक validate_hardware_logical_block_alignment(काष्ठा dm_table *table,
						 काष्ठा queue_limits *limits)
अणु
	/*
	 * This function uses arithmetic modulo the logical_block_size
	 * (in units of 512-byte sectors).
	 */
	अचिन्हित लघु device_logical_block_size_sects =
		limits->logical_block_size >> SECTOR_SHIFT;

	/*
	 * Offset of the start of the next table entry, mod logical_block_size.
	 */
	अचिन्हित लघु next_target_start = 0;

	/*
	 * Given an aligned bio that extends beyond the end of a
	 * target, how many sectors must the next target handle?
	 */
	अचिन्हित लघु reमुख्यing = 0;

	काष्ठा dm_target *ti;
	काष्ठा queue_limits ti_limits;
	अचिन्हित i;

	/*
	 * Check each entry in the table in turn.
	 */
	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(table); i++) अणु
		ti = dm_table_get_target(table, i);

		blk_set_stacking_limits(&ti_limits);

		/* combine all target devices' limits */
		अगर (ti->type->iterate_devices)
			ti->type->iterate_devices(ti, dm_set_device_limits,
						  &ti_limits);

		/*
		 * If the reमुख्यing sectors fall entirely within this
		 * table entry are they compatible with its logical_block_size?
		 */
		अगर (reमुख्यing < ti->len &&
		    reमुख्यing & ((ti_limits.logical_block_size >>
				  SECTOR_SHIFT) - 1))
			अवरोध;	/* Error */

		next_target_start =
		    (अचिन्हित लघु) ((next_target_start + ti->len) &
				      (device_logical_block_size_sects - 1));
		reमुख्यing = next_target_start ?
		    device_logical_block_size_sects - next_target_start : 0;
	पूर्ण

	अगर (reमुख्यing) अणु
		DMWARN("%s: table line %u (start sect %llu len %llu) "
		       "not aligned to h/w logical block size %u",
		       dm_device_name(table->md), i,
		       (अचिन्हित दीर्घ दीर्घ) ti->begin,
		       (अचिन्हित दीर्घ दीर्घ) ti->len,
		       limits->logical_block_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dm_table_add_target(काष्ठा dm_table *t, स्थिर अक्षर *type,
			sector_t start, sector_t len, अक्षर *params)
अणु
	पूर्णांक r = -EINVAL, argc;
	अक्षर **argv;
	काष्ठा dm_target *tgt;

	अगर (t->singleton) अणु
		DMERR("%s: target type %s must appear alone in table",
		      dm_device_name(t->md), t->tarमाला_लो->type->name);
		वापस -EINVAL;
	पूर्ण

	BUG_ON(t->num_tarमाला_लो >= t->num_allocated);

	tgt = t->tarमाला_लो + t->num_tarमाला_लो;
	स_रखो(tgt, 0, माप(*tgt));

	अगर (!len) अणु
		DMERR("%s: zero-length target", dm_device_name(t->md));
		वापस -EINVAL;
	पूर्ण

	tgt->type = dm_get_target_type(type);
	अगर (!tgt->type) अणु
		DMERR("%s: %s: unknown target type", dm_device_name(t->md), type);
		वापस -EINVAL;
	पूर्ण

	अगर (dm_target_needs_singleton(tgt->type)) अणु
		अगर (t->num_tarमाला_लो) अणु
			tgt->error = "singleton target type must appear alone in table";
			जाओ bad;
		पूर्ण
		t->singleton = true;
	पूर्ण

	अगर (dm_target_always_ग_लिखोable(tgt->type) && !(t->mode & FMODE_WRITE)) अणु
		tgt->error = "target type may not be included in a read-only table";
		जाओ bad;
	पूर्ण

	अगर (t->immutable_target_type) अणु
		अगर (t->immutable_target_type != tgt->type) अणु
			tgt->error = "immutable target type cannot be mixed with other target types";
			जाओ bad;
		पूर्ण
	पूर्ण अन्यथा अगर (dm_target_is_immutable(tgt->type)) अणु
		अगर (t->num_tarमाला_लो) अणु
			tgt->error = "immutable target type cannot be mixed with other target types";
			जाओ bad;
		पूर्ण
		t->immutable_target_type = tgt->type;
	पूर्ण

	अगर (dm_target_has_पूर्णांकegrity(tgt->type))
		t->पूर्णांकegrity_added = 1;

	tgt->table = t;
	tgt->begin = start;
	tgt->len = len;
	tgt->error = "Unknown error";

	/*
	 * Does this target adjoin the previous one ?
	 */
	अगर (!adjoin(t, tgt)) अणु
		tgt->error = "Gap in table";
		जाओ bad;
	पूर्ण

	r = dm_split_args(&argc, &argv, params);
	अगर (r) अणु
		tgt->error = "couldn't split parameters (insufficient memory)";
		जाओ bad;
	पूर्ण

	r = tgt->type->ctr(tgt, argc, argv);
	kमुक्त(argv);
	अगर (r)
		जाओ bad;

	t->highs[t->num_tarमाला_लो++] = tgt->begin + tgt->len - 1;

	अगर (!tgt->num_discard_bios && tgt->discards_supported)
		DMWARN("%s: %s: ignoring discards_supported because num_discard_bios is zero.",
		       dm_device_name(t->md), type);

	वापस 0;

 bad:
	DMERR("%s: %s: %s", dm_device_name(t->md), type, tgt->error);
	dm_put_target_type(tgt->type);
	वापस r;
पूर्ण

/*
 * Target argument parsing helpers.
 */
अटल पूर्णांक validate_next_arg(स्थिर काष्ठा dm_arg *arg,
			     काष्ठा dm_arg_set *arg_set,
			     अचिन्हित *value, अक्षर **error, अचिन्हित grouped)
अणु
	स्थिर अक्षर *arg_str = dm_shअगरt_arg(arg_set);
	अक्षर dummy;

	अगर (!arg_str ||
	    (माला_पूछो(arg_str, "%u%c", value, &dummy) != 1) ||
	    (*value < arg->min) ||
	    (*value > arg->max) ||
	    (grouped && arg_set->argc < *value)) अणु
		*error = arg->error;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dm_पढ़ो_arg(स्थिर काष्ठा dm_arg *arg, काष्ठा dm_arg_set *arg_set,
		अचिन्हित *value, अक्षर **error)
अणु
	वापस validate_next_arg(arg, arg_set, value, error, 0);
पूर्ण
EXPORT_SYMBOL(dm_पढ़ो_arg);

पूर्णांक dm_पढ़ो_arg_group(स्थिर काष्ठा dm_arg *arg, काष्ठा dm_arg_set *arg_set,
		      अचिन्हित *value, अक्षर **error)
अणु
	वापस validate_next_arg(arg, arg_set, value, error, 1);
पूर्ण
EXPORT_SYMBOL(dm_पढ़ो_arg_group);

स्थिर अक्षर *dm_shअगरt_arg(काष्ठा dm_arg_set *as)
अणु
	अक्षर *r;

	अगर (as->argc) अणु
		as->argc--;
		r = *as->argv;
		as->argv++;
		वापस r;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dm_shअगरt_arg);

व्योम dm_consume_args(काष्ठा dm_arg_set *as, अचिन्हित num_args)
अणु
	BUG_ON(as->argc < num_args);
	as->argc -= num_args;
	as->argv += num_args;
पूर्ण
EXPORT_SYMBOL(dm_consume_args);

अटल bool __table_type_bio_based(क्रमागत dm_queue_mode table_type)
अणु
	वापस (table_type == DM_TYPE_BIO_BASED ||
		table_type == DM_TYPE_DAX_BIO_BASED);
पूर्ण

अटल bool __table_type_request_based(क्रमागत dm_queue_mode table_type)
अणु
	वापस table_type == DM_TYPE_REQUEST_BASED;
पूर्ण

व्योम dm_table_set_type(काष्ठा dm_table *t, क्रमागत dm_queue_mode type)
अणु
	t->type = type;
पूर्ण
EXPORT_SYMBOL_GPL(dm_table_set_type);

/* validate the dax capability of the target device span */
पूर्णांक device_not_dax_capable(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
			sector_t start, sector_t len, व्योम *data)
अणु
	पूर्णांक blocksize = *(पूर्णांक *) data, id;
	bool rc;

	id = dax_पढ़ो_lock();
	rc = !dax_supported(dev->dax_dev, dev->bdev, blocksize, start, len);
	dax_पढ़ो_unlock(id);

	वापस rc;
पूर्ण

/* Check devices support synchronous DAX */
अटल पूर्णांक device_not_dax_synchronous_capable(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
					      sector_t start, sector_t len, व्योम *data)
अणु
	वापस !dev->dax_dev || !dax_synchronous(dev->dax_dev);
पूर्ण

bool dm_table_supports_dax(काष्ठा dm_table *t,
			   iterate_devices_callout_fn iterate_fn, पूर्णांक *blocksize)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित i;

	/* Ensure that all tarमाला_लो support DAX. */
	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);

		अगर (!ti->type->direct_access)
			वापस false;

		अगर (!ti->type->iterate_devices ||
		    ti->type->iterate_devices(ti, iterate_fn, blocksize))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक device_is_rq_stackable(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
				  sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा block_device *bdev = dev->bdev;
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	/* request-based cannot stack on partitions! */
	अगर (bdev_is_partition(bdev))
		वापस false;

	वापस queue_is_mq(q);
पूर्ण

अटल पूर्णांक dm_table_determine_type(काष्ठा dm_table *t)
अणु
	अचिन्हित i;
	अचिन्हित bio_based = 0, request_based = 0, hybrid = 0;
	काष्ठा dm_target *tgt;
	काष्ठा list_head *devices = dm_table_get_devices(t);
	क्रमागत dm_queue_mode live_md_type = dm_get_md_type(t->md);
	पूर्णांक page_size = PAGE_SIZE;

	अगर (t->type != DM_TYPE_NONE) अणु
		/* target alपढ़ोy set the table's type */
		अगर (t->type == DM_TYPE_BIO_BASED) अणु
			/* possibly upgrade to a variant of bio-based */
			जाओ verअगरy_bio_based;
		पूर्ण
		BUG_ON(t->type == DM_TYPE_DAX_BIO_BASED);
		जाओ verअगरy_rq_based;
	पूर्ण

	क्रम (i = 0; i < t->num_tarमाला_लो; i++) अणु
		tgt = t->tarमाला_लो + i;
		अगर (dm_target_hybrid(tgt))
			hybrid = 1;
		अन्यथा अगर (dm_target_request_based(tgt))
			request_based = 1;
		अन्यथा
			bio_based = 1;

		अगर (bio_based && request_based) अणु
			DMERR("Inconsistent table: different target types"
			      " can't be mixed up");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (hybrid && !bio_based && !request_based) अणु
		/*
		 * The tarमाला_लो can work either way.
		 * Determine the type from the live device.
		 * Default to bio-based अगर device is new.
		 */
		अगर (__table_type_request_based(live_md_type))
			request_based = 1;
		अन्यथा
			bio_based = 1;
	पूर्ण

	अगर (bio_based) अणु
verअगरy_bio_based:
		/* We must use this table as bio-based */
		t->type = DM_TYPE_BIO_BASED;
		अगर (dm_table_supports_dax(t, device_not_dax_capable, &page_size) ||
		    (list_empty(devices) && live_md_type == DM_TYPE_DAX_BIO_BASED)) अणु
			t->type = DM_TYPE_DAX_BIO_BASED;
		पूर्ण
		वापस 0;
	पूर्ण

	BUG_ON(!request_based); /* No tarमाला_लो in this table */

	t->type = DM_TYPE_REQUEST_BASED;

verअगरy_rq_based:
	/*
	 * Request-based dm supports only tables that have a single target now.
	 * To support multiple tarमाला_लो, request splitting support is needed,
	 * and that needs lots of changes in the block-layer.
	 * (e.g. request completion process क्रम partial completion.)
	 */
	अगर (t->num_tarमाला_लो > 1) अणु
		DMERR("request-based DM doesn't support multiple targets");
		वापस -EINVAL;
	पूर्ण

	अगर (list_empty(devices)) अणु
		पूर्णांक srcu_idx;
		काष्ठा dm_table *live_table = dm_get_live_table(t->md, &srcu_idx);

		/* inherit live table's type */
		अगर (live_table)
			t->type = live_table->type;
		dm_put_live_table(t->md, srcu_idx);
		वापस 0;
	पूर्ण

	tgt = dm_table_get_immutable_target(t);
	अगर (!tgt) अणु
		DMERR("table load rejected: immutable target is required");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (tgt->max_io_len) अणु
		DMERR("table load rejected: immutable target that splits IO is not supported");
		वापस -EINVAL;
	पूर्ण

	/* Non-request-stackable devices can't be used क्रम request-based dm */
	अगर (!tgt->type->iterate_devices ||
	    !tgt->type->iterate_devices(tgt, device_is_rq_stackable, शून्य)) अणु
		DMERR("table load rejected: including non-request-stackable devices");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत dm_queue_mode dm_table_get_type(काष्ठा dm_table *t)
अणु
	वापस t->type;
पूर्ण

काष्ठा target_type *dm_table_get_immutable_target_type(काष्ठा dm_table *t)
अणु
	वापस t->immutable_target_type;
पूर्ण

काष्ठा dm_target *dm_table_get_immutable_target(काष्ठा dm_table *t)
अणु
	/* Immutable target is implicitly a singleton */
	अगर (t->num_tarमाला_लो > 1 ||
	    !dm_target_is_immutable(t->tarमाला_लो[0].type))
		वापस शून्य;

	वापस t->tarमाला_लो;
पूर्ण

काष्ठा dm_target *dm_table_get_wildcard_target(काष्ठा dm_table *t)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित i;

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);
		अगर (dm_target_is_wildcard(ti->type))
			वापस ti;
	पूर्ण

	वापस शून्य;
पूर्ण

bool dm_table_bio_based(काष्ठा dm_table *t)
अणु
	वापस __table_type_bio_based(dm_table_get_type(t));
पूर्ण

bool dm_table_request_based(काष्ठा dm_table *t)
अणु
	वापस __table_type_request_based(dm_table_get_type(t));
पूर्ण

अटल पूर्णांक dm_table_alloc_md_mempools(काष्ठा dm_table *t, काष्ठा mapped_device *md)
अणु
	क्रमागत dm_queue_mode type = dm_table_get_type(t);
	अचिन्हित per_io_data_size = 0;
	अचिन्हित min_pool_size = 0;
	काष्ठा dm_target *ti;
	अचिन्हित i;

	अगर (unlikely(type == DM_TYPE_NONE)) अणु
		DMWARN("no table type is set, can't allocate mempools");
		वापस -EINVAL;
	पूर्ण

	अगर (__table_type_bio_based(type))
		क्रम (i = 0; i < t->num_tarमाला_लो; i++) अणु
			ti = t->tarमाला_लो + i;
			per_io_data_size = max(per_io_data_size, ti->per_io_data_size);
			min_pool_size = max(min_pool_size, ti->num_flush_bios);
		पूर्ण

	t->mempools = dm_alloc_md_mempools(md, type, t->पूर्णांकegrity_supported,
					   per_io_data_size, min_pool_size);
	अगर (!t->mempools)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम dm_table_मुक्त_md_mempools(काष्ठा dm_table *t)
अणु
	dm_मुक्त_md_mempools(t->mempools);
	t->mempools = शून्य;
पूर्ण

काष्ठा dm_md_mempools *dm_table_get_md_mempools(काष्ठा dm_table *t)
अणु
	वापस t->mempools;
पूर्ण

अटल पूर्णांक setup_indexes(काष्ठा dm_table *t)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक total = 0;
	sector_t *indexes;

	/* allocate the space क्रम *all* the indexes */
	क्रम (i = t->depth - 2; i >= 0; i--) अणु
		t->counts[i] = dm_भाग_up(t->counts[i + 1], CHILDREN_PER_NODE);
		total += t->counts[i];
	पूर्ण

	indexes = kvसुस्मृति(total, NODE_SIZE, GFP_KERNEL);
	अगर (!indexes)
		वापस -ENOMEM;

	/* set up पूर्णांकernal nodes, bottom-up */
	क्रम (i = t->depth - 2; i >= 0; i--) अणु
		t->index[i] = indexes;
		indexes += (KEYS_PER_NODE * t->counts[i]);
		setup_btree_index(i, t);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Builds the btree to index the map.
 */
अटल पूर्णांक dm_table_build_index(काष्ठा dm_table *t)
अणु
	पूर्णांक r = 0;
	अचिन्हित पूर्णांक leaf_nodes;

	/* how many indexes will the btree have ? */
	leaf_nodes = dm_भाग_up(t->num_tarमाला_लो, KEYS_PER_NODE);
	t->depth = 1 + पूर्णांक_log(leaf_nodes, CHILDREN_PER_NODE);

	/* leaf layer has alपढ़ोy been set up */
	t->counts[t->depth - 1] = leaf_nodes;
	t->index[t->depth - 1] = t->highs;

	अगर (t->depth >= 2)
		r = setup_indexes(t);

	वापस r;
पूर्ण

अटल bool पूर्णांकegrity_profile_exists(काष्ठा gendisk *disk)
अणु
	वापस !!blk_get_पूर्णांकegrity(disk);
पूर्ण

/*
 * Get a disk whose पूर्णांकegrity profile reflects the table's profile.
 * Returns शून्य अगर पूर्णांकegrity support was inconsistent or unavailable.
 */
अटल काष्ठा gendisk * dm_table_get_पूर्णांकegrity_disk(काष्ठा dm_table *t)
अणु
	काष्ठा list_head *devices = dm_table_get_devices(t);
	काष्ठा dm_dev_पूर्णांकernal *dd = शून्य;
	काष्ठा gendisk *prev_disk = शून्य, *ढाँचा_disk = शून्य;
	अचिन्हित i;

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		काष्ठा dm_target *ti = dm_table_get_target(t, i);
		अगर (!dm_target_passes_पूर्णांकegrity(ti->type))
			जाओ no_पूर्णांकegrity;
	पूर्ण

	list_क्रम_each_entry(dd, devices, list) अणु
		ढाँचा_disk = dd->dm_dev->bdev->bd_disk;
		अगर (!पूर्णांकegrity_profile_exists(ढाँचा_disk))
			जाओ no_पूर्णांकegrity;
		अन्यथा अगर (prev_disk &&
			 blk_पूर्णांकegrity_compare(prev_disk, ढाँचा_disk) < 0)
			जाओ no_पूर्णांकegrity;
		prev_disk = ढाँचा_disk;
	पूर्ण

	वापस ढाँचा_disk;

no_पूर्णांकegrity:
	अगर (prev_disk)
		DMWARN("%s: integrity not set: %s and %s profile mismatch",
		       dm_device_name(t->md),
		       prev_disk->disk_name,
		       ढाँचा_disk->disk_name);
	वापस शून्य;
पूर्ण

/*
 * Register the mapped device क्रम blk_पूर्णांकegrity support अगर the
 * underlying devices have an पूर्णांकegrity profile.  But all devices may
 * not have matching profiles (checking all devices isn't reliable
 * during table load because this table may use other DM device(s) which
 * must be resumed beक्रमe they will have an initialized पूर्णांकegity
 * profile).  Consequently, stacked DM devices क्रमce a 2 stage पूर्णांकegrity
 * profile validation: First pass during table load, final pass during
 * resume.
 */
अटल पूर्णांक dm_table_रेजिस्टर_पूर्णांकegrity(काष्ठा dm_table *t)
अणु
	काष्ठा mapped_device *md = t->md;
	काष्ठा gendisk *ढाँचा_disk = शून्य;

	/* If target handles पूर्णांकegrity itself करो not रेजिस्टर it here. */
	अगर (t->पूर्णांकegrity_added)
		वापस 0;

	ढाँचा_disk = dm_table_get_पूर्णांकegrity_disk(t);
	अगर (!ढाँचा_disk)
		वापस 0;

	अगर (!पूर्णांकegrity_profile_exists(dm_disk(md))) अणु
		t->पूर्णांकegrity_supported = true;
		/*
		 * Register पूर्णांकegrity profile during table load; we can करो
		 * this because the final profile must match during resume.
		 */
		blk_पूर्णांकegrity_रेजिस्टर(dm_disk(md),
				       blk_get_पूर्णांकegrity(ढाँचा_disk));
		वापस 0;
	पूर्ण

	/*
	 * If DM device alपढ़ोy has an initialized पूर्णांकegrity
	 * profile the new profile should not conflict.
	 */
	अगर (blk_पूर्णांकegrity_compare(dm_disk(md), ढाँचा_disk) < 0) अणु
		DMWARN("%s: conflict with existing integrity profile: "
		       "%s profile mismatch",
		       dm_device_name(t->md),
		       ढाँचा_disk->disk_name);
		वापस 1;
	पूर्ण

	/* Preserve existing पूर्णांकegrity profile */
	t->पूर्णांकegrity_supported = true;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION

काष्ठा dm_keyslot_manager अणु
	काष्ठा blk_keyslot_manager ksm;
	काष्ठा mapped_device *md;
पूर्ण;

काष्ठा dm_keyslot_evict_args अणु
	स्थिर काष्ठा blk_crypto_key *key;
	पूर्णांक err;
पूर्ण;

अटल पूर्णांक dm_keyslot_evict_callback(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
				     sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा dm_keyslot_evict_args *args = data;
	पूर्णांक err;

	err = blk_crypto_evict_key(bdev_get_queue(dev->bdev), args->key);
	अगर (!args->err)
		args->err = err;
	/* Always try to evict the key from all devices. */
	वापस 0;
पूर्ण

/*
 * When an अंतरभूत encryption key is evicted from a device-mapper device, evict
 * it from all the underlying devices.
 */
अटल पूर्णांक dm_keyslot_evict(काष्ठा blk_keyslot_manager *ksm,
			    स्थिर काष्ठा blk_crypto_key *key, अचिन्हित पूर्णांक slot)
अणु
	काष्ठा dm_keyslot_manager *dksm = container_of(ksm,
						       काष्ठा dm_keyslot_manager,
						       ksm);
	काष्ठा mapped_device *md = dksm->md;
	काष्ठा dm_keyslot_evict_args args = अणु key पूर्ण;
	काष्ठा dm_table *t;
	पूर्णांक srcu_idx;
	पूर्णांक i;
	काष्ठा dm_target *ti;

	t = dm_get_live_table(md, &srcu_idx);
	अगर (!t)
		वापस 0;
	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);
		अगर (!ti->type->iterate_devices)
			जारी;
		ti->type->iterate_devices(ti, dm_keyslot_evict_callback, &args);
	पूर्ण
	dm_put_live_table(md, srcu_idx);
	वापस args.err;
पूर्ण

अटल काष्ठा blk_ksm_ll_ops dm_ksm_ll_ops = अणु
	.keyslot_evict = dm_keyslot_evict,
पूर्ण;

अटल पूर्णांक device_पूर्णांकersect_crypto_modes(काष्ठा dm_target *ti,
					 काष्ठा dm_dev *dev, sector_t start,
					 sector_t len, व्योम *data)
अणु
	काष्ठा blk_keyslot_manager *parent = data;
	काष्ठा blk_keyslot_manager *child = bdev_get_queue(dev->bdev)->ksm;

	blk_ksm_पूर्णांकersect_modes(parent, child);
	वापस 0;
पूर्ण

व्योम dm_destroy_keyslot_manager(काष्ठा blk_keyslot_manager *ksm)
अणु
	काष्ठा dm_keyslot_manager *dksm = container_of(ksm,
						       काष्ठा dm_keyslot_manager,
						       ksm);

	अगर (!ksm)
		वापस;

	blk_ksm_destroy(ksm);
	kमुक्त(dksm);
पूर्ण

अटल व्योम dm_table_destroy_keyslot_manager(काष्ठा dm_table *t)
अणु
	dm_destroy_keyslot_manager(t->ksm);
	t->ksm = शून्य;
पूर्ण

/*
 * Conकाष्ठाs and initializes t->ksm with a keyslot manager that
 * represents the common set of crypto capabilities of the devices
 * described by the dm_table. However, अगर the स्थिरructed keyslot
 * manager करोes not support a superset of the crypto capabilities
 * supported by the current keyslot manager of the mapped_device,
 * it वापसs an error instead, since we करोn't support restricting
 * crypto capabilities on table changes. Finally, अगर the स्थिरructed
 * keyslot manager करोesn't actually support any crypto modes at all,
 * it just वापसs शून्य.
 */
अटल पूर्णांक dm_table_स्थिरruct_keyslot_manager(काष्ठा dm_table *t)
अणु
	काष्ठा dm_keyslot_manager *dksm;
	काष्ठा blk_keyslot_manager *ksm;
	काष्ठा dm_target *ti;
	अचिन्हित पूर्णांक i;
	bool ksm_is_empty = true;

	dksm = kदो_स्मृति(माप(*dksm), GFP_KERNEL);
	अगर (!dksm)
		वापस -ENOMEM;
	dksm->md = t->md;

	ksm = &dksm->ksm;
	blk_ksm_init_passthrough(ksm);
	ksm->ksm_ll_ops = dm_ksm_ll_ops;
	ksm->max_dun_bytes_supported = अच_पूर्णांक_उच्च;
	स_रखो(ksm->crypto_modes_supported, 0xFF,
	       माप(ksm->crypto_modes_supported));

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);

		अगर (!dm_target_passes_crypto(ti->type)) अणु
			blk_ksm_पूर्णांकersect_modes(ksm, शून्य);
			अवरोध;
		पूर्ण
		अगर (!ti->type->iterate_devices)
			जारी;
		ti->type->iterate_devices(ti, device_पूर्णांकersect_crypto_modes,
					  ksm);
	पूर्ण

	अगर (t->md->queue && !blk_ksm_is_superset(ksm, t->md->queue->ksm)) अणु
		DMWARN("Inline encryption capabilities of new DM table were more restrictive than the old table's. This is not supported!");
		dm_destroy_keyslot_manager(ksm);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If the new KSM करोesn't actually support any crypto modes, we may as
	 * well represent it with a शून्य ksm.
	 */
	ksm_is_empty = true;
	क्रम (i = 0; i < ARRAY_SIZE(ksm->crypto_modes_supported); i++) अणु
		अगर (ksm->crypto_modes_supported[i]) अणु
			ksm_is_empty = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ksm_is_empty) अणु
		dm_destroy_keyslot_manager(ksm);
		ksm = शून्य;
	पूर्ण

	/*
	 * t->ksm is only set temporarily जबतक the table is being set
	 * up, and it माला_लो set to शून्य after the capabilities have
	 * been transferred to the request_queue.
	 */
	t->ksm = ksm;

	वापस 0;
पूर्ण

अटल व्योम dm_update_keyslot_manager(काष्ठा request_queue *q,
				      काष्ठा dm_table *t)
अणु
	अगर (!t->ksm)
		वापस;

	/* Make the ksm less restrictive */
	अगर (!q->ksm) अणु
		blk_ksm_रेजिस्टर(t->ksm, q);
	पूर्ण अन्यथा अणु
		blk_ksm_update_capabilities(q->ksm, t->ksm);
		dm_destroy_keyslot_manager(t->ksm);
	पूर्ण
	t->ksm = शून्य;
पूर्ण

#अन्यथा /* CONFIG_BLK_INLINE_ENCRYPTION */

अटल पूर्णांक dm_table_स्थिरruct_keyslot_manager(काष्ठा dm_table *t)
अणु
	वापस 0;
पूर्ण

व्योम dm_destroy_keyslot_manager(काष्ठा blk_keyslot_manager *ksm)
अणु
पूर्ण

अटल व्योम dm_table_destroy_keyslot_manager(काष्ठा dm_table *t)
अणु
पूर्ण

अटल व्योम dm_update_keyslot_manager(काष्ठा request_queue *q,
				      काष्ठा dm_table *t)
अणु
पूर्ण

#पूर्ण_अगर /* !CONFIG_BLK_INLINE_ENCRYPTION */

/*
 * Prepares the table क्रम use by building the indices,
 * setting the type, and allocating mempools.
 */
पूर्णांक dm_table_complete(काष्ठा dm_table *t)
अणु
	पूर्णांक r;

	r = dm_table_determine_type(t);
	अगर (r) अणु
		DMERR("unable to determine table type");
		वापस r;
	पूर्ण

	r = dm_table_build_index(t);
	अगर (r) अणु
		DMERR("unable to build btrees");
		वापस r;
	पूर्ण

	r = dm_table_रेजिस्टर_पूर्णांकegrity(t);
	अगर (r) अणु
		DMERR("could not register integrity profile.");
		वापस r;
	पूर्ण

	r = dm_table_स्थिरruct_keyslot_manager(t);
	अगर (r) अणु
		DMERR("could not construct keyslot manager.");
		वापस r;
	पूर्ण

	r = dm_table_alloc_md_mempools(t, t->md);
	अगर (r)
		DMERR("unable to allocate mempools");

	वापस r;
पूर्ण

अटल DEFINE_MUTEX(_event_lock);
व्योम dm_table_event_callback(काष्ठा dm_table *t,
			     व्योम (*fn)(व्योम *), व्योम *context)
अणु
	mutex_lock(&_event_lock);
	t->event_fn = fn;
	t->event_context = context;
	mutex_unlock(&_event_lock);
पूर्ण

व्योम dm_table_event(काष्ठा dm_table *t)
अणु
	mutex_lock(&_event_lock);
	अगर (t->event_fn)
		t->event_fn(t->event_context);
	mutex_unlock(&_event_lock);
पूर्ण
EXPORT_SYMBOL(dm_table_event);

अंतरभूत sector_t dm_table_get_size(काष्ठा dm_table *t)
अणु
	वापस t->num_tarमाला_लो ? (t->highs[t->num_tarमाला_लो - 1] + 1) : 0;
पूर्ण
EXPORT_SYMBOL(dm_table_get_size);

काष्ठा dm_target *dm_table_get_target(काष्ठा dm_table *t, अचिन्हित पूर्णांक index)
अणु
	अगर (index >= t->num_tarमाला_लो)
		वापस शून्य;

	वापस t->tarमाला_लो + index;
पूर्ण

/*
 * Search the btree क्रम the correct target.
 *
 * Caller should check वापसed poपूर्णांकer क्रम शून्य
 * to trap I/O beyond end of device.
 */
काष्ठा dm_target *dm_table_find_target(काष्ठा dm_table *t, sector_t sector)
अणु
	अचिन्हित पूर्णांक l, n = 0, k = 0;
	sector_t *node;

	अगर (unlikely(sector >= dm_table_get_size(t)))
		वापस शून्य;

	क्रम (l = 0; l < t->depth; l++) अणु
		n = get_child(n, k);
		node = get_node(t, l, n);

		क्रम (k = 0; k < KEYS_PER_NODE; k++)
			अगर (node[k] >= sector)
				अवरोध;
	पूर्ण

	वापस &t->tarमाला_लो[(KEYS_PER_NODE * n) + k];
पूर्ण

/*
 * type->iterate_devices() should be called when the sanity check needs to
 * iterate and check all underlying data devices. iterate_devices() will
 * iterate all underlying data devices until it encounters a non-zero वापस
 * code, वापसed by whether the input iterate_devices_callout_fn, or
 * iterate_devices() itself पूर्णांकernally.
 *
 * For some target type (e.g. dm-stripe), one call of iterate_devices() may
 * iterate multiple underlying devices पूर्णांकernally, in which हाल a non-zero
 * वापस code वापसed by iterate_devices_callout_fn will stop the iteration
 * in advance.
 *
 * Cases requiring _any_ underlying device supporting some kind of attribute,
 * should use the iteration काष्ठाure like dm_table_any_dev_attr(), or call
 * it directly. @func should handle semantics of positive examples, e.g.
 * capable of something.
 *
 * Cases requiring _all_ underlying devices supporting some kind of attribute,
 * should use the iteration काष्ठाure like dm_table_supports_noरुको() or
 * dm_table_supports_discards(). Or पूर्णांकroduce dm_table_all_devs_attr() that
 * uses an @anti_func that handle semantics of counter examples, e.g. not
 * capable of something. So: वापस !dm_table_any_dev_attr(t, anti_func, data);
 */
अटल bool dm_table_any_dev_attr(काष्ठा dm_table *t,
				  iterate_devices_callout_fn func, व्योम *data)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);

		अगर (ti->type->iterate_devices &&
		    ti->type->iterate_devices(ti, func, data))
			वापस true;
        पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक count_device(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
			sector_t start, sector_t len, व्योम *data)
अणु
	अचिन्हित *num_devices = data;

	(*num_devices)++;

	वापस 0;
पूर्ण

/*
 * Check whether a table has no data devices attached using each
 * target's iterate_devices method.
 * Returns false अगर the result is unknown because a target करोesn't
 * support iterate_devices.
 */
bool dm_table_has_no_data_devices(काष्ठा dm_table *table)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित i, num_devices;

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(table); i++) अणु
		ti = dm_table_get_target(table, i);

		अगर (!ti->type->iterate_devices)
			वापस false;

		num_devices = 0;
		ti->type->iterate_devices(ti, count_device, &num_devices);
		अगर (num_devices)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक device_not_zoned_model(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
				  sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);
	क्रमागत blk_zoned_model *zoned_model = data;

	वापस blk_queue_zoned_model(q) != *zoned_model;
पूर्ण

/*
 * Check the device zoned model based on the target feature flag. If the target
 * has the DM_TARGET_ZONED_HM feature flag set, host-managed zoned devices are
 * also accepted but all devices must have the same zoned model. If the target
 * has the DM_TARGET_MIXED_ZONED_MODEL feature set, the devices can have any
 * zoned model with all zoned devices having the same zone size.
 */
अटल bool dm_table_supports_zoned_model(काष्ठा dm_table *t,
					  क्रमागत blk_zoned_model zoned_model)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित i;

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);

		अगर (dm_target_supports_zoned_hm(ti->type)) अणु
			अगर (!ti->type->iterate_devices ||
			    ti->type->iterate_devices(ti, device_not_zoned_model,
						      &zoned_model))
				वापस false;
		पूर्ण अन्यथा अगर (!dm_target_supports_mixed_zoned_model(ti->type)) अणु
			अगर (zoned_model == BLK_ZONED_HM)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक device_not_matches_zone_sectors(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
					   sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);
	अचिन्हित पूर्णांक *zone_sectors = data;

	अगर (!blk_queue_is_zoned(q))
		वापस 0;

	वापस blk_queue_zone_sectors(q) != *zone_sectors;
पूर्ण

/*
 * Check consistency of zoned model and zone sectors across all tarमाला_लो. For
 * zone sectors, अगर the destination device is a zoned block device, it shall
 * have the specअगरied zone_sectors.
 */
अटल पूर्णांक validate_hardware_zoned_model(काष्ठा dm_table *table,
					 क्रमागत blk_zoned_model zoned_model,
					 अचिन्हित पूर्णांक zone_sectors)
अणु
	अगर (zoned_model == BLK_ZONED_NONE)
		वापस 0;

	अगर (!dm_table_supports_zoned_model(table, zoned_model)) अणु
		DMERR("%s: zoned model is not consistent across all devices",
		      dm_device_name(table->md));
		वापस -EINVAL;
	पूर्ण

	/* Check zone size validity and compatibility */
	अगर (!zone_sectors || !is_घातer_of_2(zone_sectors))
		वापस -EINVAL;

	अगर (dm_table_any_dev_attr(table, device_not_matches_zone_sectors, &zone_sectors)) अणु
		DMERR("%s: zone sectors is not consistent across all zoned devices",
		      dm_device_name(table->md));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Establish the new table's queue_limits and validate them.
 */
पूर्णांक dm_calculate_queue_limits(काष्ठा dm_table *table,
			      काष्ठा queue_limits *limits)
अणु
	काष्ठा dm_target *ti;
	काष्ठा queue_limits ti_limits;
	अचिन्हित i;
	क्रमागत blk_zoned_model zoned_model = BLK_ZONED_NONE;
	अचिन्हित पूर्णांक zone_sectors = 0;

	blk_set_stacking_limits(limits);

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(table); i++) अणु
		blk_set_stacking_limits(&ti_limits);

		ti = dm_table_get_target(table, i);

		अगर (!ti->type->iterate_devices)
			जाओ combine_limits;

		/*
		 * Combine queue limits of all the devices this target uses.
		 */
		ti->type->iterate_devices(ti, dm_set_device_limits,
					  &ti_limits);

		अगर (zoned_model == BLK_ZONED_NONE && ti_limits.zoned != BLK_ZONED_NONE) अणु
			/*
			 * After stacking all limits, validate all devices
			 * in table support this zoned model and zone sectors.
			 */
			zoned_model = ti_limits.zoned;
			zone_sectors = ti_limits.chunk_sectors;
		पूर्ण

		/* Set I/O hपूर्णांकs portion of queue limits */
		अगर (ti->type->io_hपूर्णांकs)
			ti->type->io_hपूर्णांकs(ti, &ti_limits);

		/*
		 * Check each device area is consistent with the target's
		 * overall queue limits.
		 */
		अगर (ti->type->iterate_devices(ti, device_area_is_invalid,
					      &ti_limits))
			वापस -EINVAL;

combine_limits:
		/*
		 * Merge this target's queue limits पूर्णांकo the overall limits
		 * क्रम the table.
		 */
		अगर (blk_stack_limits(limits, &ti_limits, 0) < 0)
			DMWARN("%s: adding target device "
			       "(start sect %llu len %llu) "
			       "caused an alignment inconsistency",
			       dm_device_name(table->md),
			       (अचिन्हित दीर्घ दीर्घ) ti->begin,
			       (अचिन्हित दीर्घ दीर्घ) ti->len);
	पूर्ण

	/*
	 * Verअगरy that the zoned model and zone sectors, as determined beक्रमe
	 * any .io_hपूर्णांकs override, are the same across all devices in the table.
	 * - this is especially relevant अगर .io_hपूर्णांकs is emulating a disk-managed
	 *   zoned model (aka BLK_ZONED_NONE) on host-managed zoned block devices.
	 * BUT...
	 */
	अगर (limits->zoned != BLK_ZONED_NONE) अणु
		/*
		 * ...IF the above limits stacking determined a zoned model
		 * validate that all of the table's devices conक्रमm to it.
		 */
		zoned_model = limits->zoned;
		zone_sectors = limits->chunk_sectors;
	पूर्ण
	अगर (validate_hardware_zoned_model(table, zoned_model, zone_sectors))
		वापस -EINVAL;

	वापस validate_hardware_logical_block_alignment(table, limits);
पूर्ण

/*
 * Verअगरy that all devices have an पूर्णांकegrity profile that matches the
 * DM device's registered integrity profile.  If the profiles don't
 * match then unरेजिस्टर the DM device's पूर्णांकegrity profile.
 */
अटल व्योम dm_table_verअगरy_पूर्णांकegrity(काष्ठा dm_table *t)
अणु
	काष्ठा gendisk *ढाँचा_disk = शून्य;

	अगर (t->पूर्णांकegrity_added)
		वापस;

	अगर (t->पूर्णांकegrity_supported) अणु
		/*
		 * Verअगरy that the original पूर्णांकegrity profile
		 * matches all the devices in this table.
		 */
		ढाँचा_disk = dm_table_get_पूर्णांकegrity_disk(t);
		अगर (ढाँचा_disk &&
		    blk_पूर्णांकegrity_compare(dm_disk(t->md), ढाँचा_disk) >= 0)
			वापस;
	पूर्ण

	अगर (पूर्णांकegrity_profile_exists(dm_disk(t->md))) अणु
		DMWARN("%s: unable to establish an integrity profile",
		       dm_device_name(t->md));
		blk_पूर्णांकegrity_unरेजिस्टर(dm_disk(t->md));
	पूर्ण
पूर्ण

अटल पूर्णांक device_flush_capable(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
				sector_t start, sector_t len, व्योम *data)
अणु
	अचिन्हित दीर्घ flush = (अचिन्हित दीर्घ) data;
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);

	वापस (q->queue_flags & flush);
पूर्ण

अटल bool dm_table_supports_flush(काष्ठा dm_table *t, अचिन्हित दीर्घ flush)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित i;

	/*
	 * Require at least one underlying device to support flushes.
	 * t->devices includes पूर्णांकernal dm devices such as mirror logs
	 * so we need to use iterate_devices here, which tarमाला_लो
	 * supporting flushes must provide.
	 */
	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);

		अगर (!ti->num_flush_bios)
			जारी;

		अगर (ti->flush_supported)
			वापस true;

		अगर (ti->type->iterate_devices &&
		    ti->type->iterate_devices(ti, device_flush_capable, (व्योम *) flush))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक device_dax_ग_लिखो_cache_enabled(काष्ठा dm_target *ti,
					  काष्ठा dm_dev *dev, sector_t start,
					  sector_t len, व्योम *data)
अणु
	काष्ठा dax_device *dax_dev = dev->dax_dev;

	अगर (!dax_dev)
		वापस false;

	अगर (dax_ग_लिखो_cache_enabled(dax_dev))
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक device_is_rotational(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
				sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);

	वापस !blk_queue_nonrot(q);
पूर्ण

अटल पूर्णांक device_is_not_अक्रमom(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
			     sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);

	वापस !blk_queue_add_अक्रमom(q);
पूर्ण

अटल पूर्णांक device_not_ग_लिखो_same_capable(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
					 sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);

	वापस !q->limits.max_ग_लिखो_same_sectors;
पूर्ण

अटल bool dm_table_supports_ग_लिखो_same(काष्ठा dm_table *t)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित i;

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);

		अगर (!ti->num_ग_लिखो_same_bios)
			वापस false;

		अगर (!ti->type->iterate_devices ||
		    ti->type->iterate_devices(ti, device_not_ग_लिखो_same_capable, शून्य))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक device_not_ग_लिखो_zeroes_capable(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
					   sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);

	वापस !q->limits.max_ग_लिखो_zeroes_sectors;
पूर्ण

अटल bool dm_table_supports_ग_लिखो_zeroes(काष्ठा dm_table *t)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित i = 0;

	जबतक (i < dm_table_get_num_tarमाला_लो(t)) अणु
		ti = dm_table_get_target(t, i++);

		अगर (!ti->num_ग_लिखो_zeroes_bios)
			वापस false;

		अगर (!ti->type->iterate_devices ||
		    ti->type->iterate_devices(ti, device_not_ग_लिखो_zeroes_capable, शून्य))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक device_not_noरुको_capable(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
				     sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);

	वापस !blk_queue_noरुको(q);
पूर्ण

अटल bool dm_table_supports_noरुको(काष्ठा dm_table *t)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित i = 0;

	जबतक (i < dm_table_get_num_tarमाला_लो(t)) अणु
		ti = dm_table_get_target(t, i++);

		अगर (!dm_target_supports_noरुको(ti->type))
			वापस false;

		अगर (!ti->type->iterate_devices ||
		    ti->type->iterate_devices(ti, device_not_noरुको_capable, शून्य))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक device_not_discard_capable(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
				      sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);

	वापस !blk_queue_discard(q);
पूर्ण

अटल bool dm_table_supports_discards(काष्ठा dm_table *t)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित i;

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);

		अगर (!ti->num_discard_bios)
			वापस false;

		/*
		 * Either the target provides discard support (as implied by setting
		 * 'discards_supported') or it relies on _all_ data devices having
		 * discard support.
		 */
		अगर (!ti->discards_supported &&
		    (!ti->type->iterate_devices ||
		     ti->type->iterate_devices(ti, device_not_discard_capable, शून्य)))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक device_not_secure_erase_capable(काष्ठा dm_target *ti,
					   काष्ठा dm_dev *dev, sector_t start,
					   sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);

	वापस !blk_queue_secure_erase(q);
पूर्ण

अटल bool dm_table_supports_secure_erase(काष्ठा dm_table *t)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dm_table_get_num_tarमाला_लो(t); i++) अणु
		ti = dm_table_get_target(t, i);

		अगर (!ti->num_secure_erase_bios)
			वापस false;

		अगर (!ti->type->iterate_devices ||
		    ti->type->iterate_devices(ti, device_not_secure_erase_capable, शून्य))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक device_requires_stable_pages(काष्ठा dm_target *ti,
					काष्ठा dm_dev *dev, sector_t start,
					sector_t len, व्योम *data)
अणु
	काष्ठा request_queue *q = bdev_get_queue(dev->bdev);

	वापस blk_queue_stable_ग_लिखोs(q);
पूर्ण

व्योम dm_table_set_restrictions(काष्ठा dm_table *t, काष्ठा request_queue *q,
			       काष्ठा queue_limits *limits)
अणु
	bool wc = false, fua = false;
	पूर्णांक page_size = PAGE_SIZE;

	/*
	 * Copy table's limits to the DM device's request_queue
	 */
	q->limits = *limits;

	अगर (dm_table_supports_noरुको(t))
		blk_queue_flag_set(QUEUE_FLAG_NOWAIT, q);
	अन्यथा
		blk_queue_flag_clear(QUEUE_FLAG_NOWAIT, q);

	अगर (!dm_table_supports_discards(t)) अणु
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, q);
		/* Must also clear discard limits... */
		q->limits.max_discard_sectors = 0;
		q->limits.max_hw_discard_sectors = 0;
		q->limits.discard_granularity = 0;
		q->limits.discard_alignment = 0;
		q->limits.discard_misaligned = 0;
	पूर्ण अन्यथा
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);

	अगर (dm_table_supports_secure_erase(t))
		blk_queue_flag_set(QUEUE_FLAG_SECERASE, q);

	अगर (dm_table_supports_flush(t, (1UL << QUEUE_FLAG_WC))) अणु
		wc = true;
		अगर (dm_table_supports_flush(t, (1UL << QUEUE_FLAG_FUA)))
			fua = true;
	पूर्ण
	blk_queue_ग_लिखो_cache(q, wc, fua);

	अगर (dm_table_supports_dax(t, device_not_dax_capable, &page_size)) अणु
		blk_queue_flag_set(QUEUE_FLAG_DAX, q);
		अगर (dm_table_supports_dax(t, device_not_dax_synchronous_capable, शून्य))
			set_dax_synchronous(t->md->dax_dev);
	पूर्ण
	अन्यथा
		blk_queue_flag_clear(QUEUE_FLAG_DAX, q);

	अगर (dm_table_any_dev_attr(t, device_dax_ग_लिखो_cache_enabled, शून्य))
		dax_ग_लिखो_cache(t->md->dax_dev, true);

	/* Ensure that all underlying devices are non-rotational. */
	अगर (dm_table_any_dev_attr(t, device_is_rotational, शून्य))
		blk_queue_flag_clear(QUEUE_FLAG_NONROT, q);
	अन्यथा
		blk_queue_flag_set(QUEUE_FLAG_NONROT, q);

	अगर (!dm_table_supports_ग_लिखो_same(t))
		q->limits.max_ग_लिखो_same_sectors = 0;
	अगर (!dm_table_supports_ग_लिखो_zeroes(t))
		q->limits.max_ग_लिखो_zeroes_sectors = 0;

	dm_table_verअगरy_पूर्णांकegrity(t);

	/*
	 * Some devices करोn't use blk_पूर्णांकegrity but still want stable pages
	 * because they करो their own checksumming.
	 * If any underlying device requires stable pages, a table must require
	 * them as well.  Only tarमाला_लो that support iterate_devices are considered:
	 * करोn't want error, zero, etc to require stable pages.
	 */
	अगर (dm_table_any_dev_attr(t, device_requires_stable_pages, शून्य))
		blk_queue_flag_set(QUEUE_FLAG_STABLE_WRITES, q);
	अन्यथा
		blk_queue_flag_clear(QUEUE_FLAG_STABLE_WRITES, q);

	/*
	 * Determine whether or not this queue's I/O timings contribute
	 * to the entropy pool, Only request-based tarमाला_लो use this.
	 * Clear QUEUE_FLAG_ADD_RANDOM अगर any underlying device करोes not
	 * have it set.
	 */
	अगर (blk_queue_add_अक्रमom(q) &&
	    dm_table_any_dev_attr(t, device_is_not_अक्रमom, शून्य))
		blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, q);

	/*
	 * For a zoned target, the number of zones should be updated क्रम the
	 * correct value to be exposed in sysfs queue/nr_zones. For a BIO based
	 * target, this is all that is needed.
	 */
#अगर_घोषित CONFIG_BLK_DEV_ZONED
	अगर (blk_queue_is_zoned(q)) अणु
		WARN_ON_ONCE(queue_is_mq(q));
		q->nr_zones = blkdev_nr_zones(t->md->disk);
	पूर्ण
#पूर्ण_अगर

	dm_update_keyslot_manager(q, t);
	blk_queue_update_पढ़ोahead(q);
पूर्ण

अचिन्हित पूर्णांक dm_table_get_num_tarमाला_लो(काष्ठा dm_table *t)
अणु
	वापस t->num_tarमाला_लो;
पूर्ण

काष्ठा list_head *dm_table_get_devices(काष्ठा dm_table *t)
अणु
	वापस &t->devices;
पूर्ण

भ_शेषe_t dm_table_get_mode(काष्ठा dm_table *t)
अणु
	वापस t->mode;
पूर्ण
EXPORT_SYMBOL(dm_table_get_mode);

क्रमागत suspend_mode अणु
	PRESUSPEND,
	PRESUSPEND_UNDO,
	POSTSUSPEND,
पूर्ण;

अटल व्योम suspend_tarमाला_लो(काष्ठा dm_table *t, क्रमागत suspend_mode mode)
अणु
	पूर्णांक i = t->num_tarमाला_लो;
	काष्ठा dm_target *ti = t->tarमाला_लो;

	lockdep_निश्चित_held(&t->md->suspend_lock);

	जबतक (i--) अणु
		चयन (mode) अणु
		हाल PRESUSPEND:
			अगर (ti->type->presuspend)
				ti->type->presuspend(ti);
			अवरोध;
		हाल PRESUSPEND_UNDO:
			अगर (ti->type->presuspend_unकरो)
				ti->type->presuspend_unकरो(ti);
			अवरोध;
		हाल POSTSUSPEND:
			अगर (ti->type->postsuspend)
				ti->type->postsuspend(ti);
			अवरोध;
		पूर्ण
		ti++;
	पूर्ण
पूर्ण

व्योम dm_table_presuspend_tarमाला_लो(काष्ठा dm_table *t)
अणु
	अगर (!t)
		वापस;

	suspend_tarमाला_लो(t, PRESUSPEND);
पूर्ण

व्योम dm_table_presuspend_unकरो_tarमाला_लो(काष्ठा dm_table *t)
अणु
	अगर (!t)
		वापस;

	suspend_tarमाला_लो(t, PRESUSPEND_UNDO);
पूर्ण

व्योम dm_table_postsuspend_tarमाला_लो(काष्ठा dm_table *t)
अणु
	अगर (!t)
		वापस;

	suspend_tarमाला_लो(t, POSTSUSPEND);
पूर्ण

पूर्णांक dm_table_resume_tarमाला_लो(काष्ठा dm_table *t)
अणु
	पूर्णांक i, r = 0;

	lockdep_निश्चित_held(&t->md->suspend_lock);

	क्रम (i = 0; i < t->num_tarमाला_लो; i++) अणु
		काष्ठा dm_target *ti = t->tarमाला_लो + i;

		अगर (!ti->type->preresume)
			जारी;

		r = ti->type->preresume(ti);
		अगर (r) अणु
			DMERR("%s: %s: preresume failed, error = %d",
			      dm_device_name(t->md), ti->type->name, r);
			वापस r;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < t->num_tarमाला_लो; i++) अणु
		काष्ठा dm_target *ti = t->tarमाला_लो + i;

		अगर (ti->type->resume)
			ti->type->resume(ti);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा mapped_device *dm_table_get_md(काष्ठा dm_table *t)
अणु
	वापस t->md;
पूर्ण
EXPORT_SYMBOL(dm_table_get_md);

स्थिर अक्षर *dm_table_device_name(काष्ठा dm_table *t)
अणु
	वापस dm_device_name(t->md);
पूर्ण
EXPORT_SYMBOL_GPL(dm_table_device_name);

व्योम dm_table_run_md_queue_async(काष्ठा dm_table *t)
अणु
	अगर (!dm_table_request_based(t))
		वापस;

	अगर (t->md->queue)
		blk_mq_run_hw_queues(t->md->queue, true);
पूर्ण
EXPORT_SYMBOL(dm_table_run_md_queue_async);

