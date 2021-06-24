<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software
 * Copyright (C) 2004-2008 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the LGPL.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/dm-पन.स>
#समावेश <linux/dm-dirty-log.h>

#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "dirty region log"

अटल LIST_HEAD(_log_types);
अटल DEFINE_SPINLOCK(_lock);

अटल काष्ठा dm_dirty_log_type *__find_dirty_log_type(स्थिर अक्षर *name)
अणु
	काष्ठा dm_dirty_log_type *log_type;

	list_क्रम_each_entry(log_type, &_log_types, list)
		अगर (!म_भेद(name, log_type->name))
			वापस log_type;

	वापस शून्य;
पूर्ण

अटल काष्ठा dm_dirty_log_type *_get_dirty_log_type(स्थिर अक्षर *name)
अणु
	काष्ठा dm_dirty_log_type *log_type;

	spin_lock(&_lock);

	log_type = __find_dirty_log_type(name);
	अगर (log_type && !try_module_get(log_type->module))
		log_type = शून्य;

	spin_unlock(&_lock);

	वापस log_type;
पूर्ण

/*
 * get_type
 * @type_name
 *
 * Attempt to retrieve the dm_dirty_log_type by name.  If not alपढ़ोy
 * available, attempt to load the appropriate module.
 *
 * Log modules are named "dm-log-" followed by the 'type_name'.
 * Modules may contain multiple types.
 * This function will first try the module "dm-log-<type_name>",
 * then truncate 'type_name' on the last '-' and try again.
 *
 * For example, अगर type_name was "clustered-disk", it would search
 * 'dm-log-clustered-disk' then 'dm-log-clustered'.
 *
 * Returns: dirty_log_type* on success, शून्य on failure
 */
अटल काष्ठा dm_dirty_log_type *get_type(स्थिर अक्षर *type_name)
अणु
	अक्षर *p, *type_name_dup;
	काष्ठा dm_dirty_log_type *log_type;

	अगर (!type_name)
		वापस शून्य;

	log_type = _get_dirty_log_type(type_name);
	अगर (log_type)
		वापस log_type;

	type_name_dup = kstrdup(type_name, GFP_KERNEL);
	अगर (!type_name_dup) अणु
		DMWARN("No memory left to attempt log module load for \"%s\"",
		       type_name);
		वापस शून्य;
	पूर्ण

	जबतक (request_module("dm-log-%s", type_name_dup) ||
	       !(log_type = _get_dirty_log_type(type_name))) अणु
		p = म_खोजप(type_name_dup, '-');
		अगर (!p)
			अवरोध;
		p[0] = '\0';
	पूर्ण

	अगर (!log_type)
		DMWARN("Module for logging type \"%s\" not found.", type_name);

	kमुक्त(type_name_dup);

	वापस log_type;
पूर्ण

अटल व्योम put_type(काष्ठा dm_dirty_log_type *type)
अणु
	अगर (!type)
		वापस;

	spin_lock(&_lock);
	अगर (!__find_dirty_log_type(type->name))
		जाओ out;

	module_put(type->module);

out:
	spin_unlock(&_lock);
पूर्ण

पूर्णांक dm_dirty_log_type_रेजिस्टर(काष्ठा dm_dirty_log_type *type)
अणु
	पूर्णांक r = 0;

	spin_lock(&_lock);
	अगर (!__find_dirty_log_type(type->name))
		list_add(&type->list, &_log_types);
	अन्यथा
		r = -EEXIST;
	spin_unlock(&_lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL(dm_dirty_log_type_रेजिस्टर);

पूर्णांक dm_dirty_log_type_unरेजिस्टर(काष्ठा dm_dirty_log_type *type)
अणु
	spin_lock(&_lock);

	अगर (!__find_dirty_log_type(type->name)) अणु
		spin_unlock(&_lock);
		वापस -EINVAL;
	पूर्ण

	list_del(&type->list);

	spin_unlock(&_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dm_dirty_log_type_unरेजिस्टर);

काष्ठा dm_dirty_log *dm_dirty_log_create(स्थिर अक्षर *type_name,
			काष्ठा dm_target *ti,
			पूर्णांक (*flush_callback_fn)(काष्ठा dm_target *ti),
			अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा dm_dirty_log_type *type;
	काष्ठा dm_dirty_log *log;

	log = kदो_स्मृति(माप(*log), GFP_KERNEL);
	अगर (!log)
		वापस शून्य;

	type = get_type(type_name);
	अगर (!type) अणु
		kमुक्त(log);
		वापस शून्य;
	पूर्ण

	log->flush_callback_fn = flush_callback_fn;
	log->type = type;
	अगर (type->ctr(log, ti, argc, argv)) अणु
		kमुक्त(log);
		put_type(type);
		वापस शून्य;
	पूर्ण

	वापस log;
पूर्ण
EXPORT_SYMBOL(dm_dirty_log_create);

व्योम dm_dirty_log_destroy(काष्ठा dm_dirty_log *log)
अणु
	log->type->dtr(log);
	put_type(log->type);
	kमुक्त(log);
पूर्ण
EXPORT_SYMBOL(dm_dirty_log_destroy);

/*-----------------------------------------------------------------
 * Persistent and core logs share a lot of their implementation.
 * FIXME: need a reload method to be called from a resume
 *---------------------------------------------------------------*/
/*
 * Magic क्रम persistent mirrors: "MiRr"
 */
#घोषणा MIRROR_MAGIC 0x4D695272

/*
 * The on-disk version of the metadata.
 */
#घोषणा MIRROR_DISK_VERSION 2
#घोषणा LOG_OFFSET 2

काष्ठा log_header_disk अणु
	__le32 magic;

	/*
	 * Simple, incrementing version. no backward
	 * compatibility.
	 */
	__le32 version;
	__le64 nr_regions;
पूर्ण __packed;

काष्ठा log_header_core अणु
	uपूर्णांक32_t magic;
	uपूर्णांक32_t version;
	uपूर्णांक64_t nr_regions;
पूर्ण;

काष्ठा log_c अणु
	काष्ठा dm_target *ti;
	पूर्णांक touched_dirtied;
	पूर्णांक touched_cleaned;
	पूर्णांक flush_failed;
	uपूर्णांक32_t region_size;
	अचिन्हित पूर्णांक region_count;
	region_t sync_count;

	अचिन्हित bitset_uपूर्णांक32_count;
	uपूर्णांक32_t *clean_bits;
	uपूर्णांक32_t *sync_bits;
	uपूर्णांक32_t *recovering_bits;	/* FIXME: this seems excessive */

	पूर्णांक sync_search;

	/* Resync flag */
	क्रमागत sync अणु
		DEFAULTSYNC,	/* Synchronize अगर necessary */
		NOSYNC,		/* Devices known to be alपढ़ोy in sync */
		FORCESYNC,	/* Force a sync to happen */
	पूर्ण sync;

	काष्ठा dm_io_request io_req;

	/*
	 * Disk log fields
	 */
	पूर्णांक log_dev_failed;
	पूर्णांक log_dev_flush_failed;
	काष्ठा dm_dev *log_dev;
	काष्ठा log_header_core header;

	काष्ठा dm_io_region header_location;
	काष्ठा log_header_disk *disk_header;
पूर्ण;

/*
 * The touched member needs to be updated every समय we access
 * one of the bitsets.
 */
अटल अंतरभूत पूर्णांक log_test_bit(uपूर्णांक32_t *bs, अचिन्हित bit)
अणु
	वापस test_bit_le(bit, bs) ? 1 : 0;
पूर्ण

अटल अंतरभूत व्योम log_set_bit(काष्ठा log_c *l,
			       uपूर्णांक32_t *bs, अचिन्हित bit)
अणु
	__set_bit_le(bit, bs);
	l->touched_cleaned = 1;
पूर्ण

अटल अंतरभूत व्योम log_clear_bit(काष्ठा log_c *l,
				 uपूर्णांक32_t *bs, अचिन्हित bit)
अणु
	__clear_bit_le(bit, bs);
	l->touched_dirtied = 1;
पूर्ण

/*----------------------------------------------------------------
 * Header IO
 *--------------------------------------------------------------*/
अटल व्योम header_to_disk(काष्ठा log_header_core *core, काष्ठा log_header_disk *disk)
अणु
	disk->magic = cpu_to_le32(core->magic);
	disk->version = cpu_to_le32(core->version);
	disk->nr_regions = cpu_to_le64(core->nr_regions);
पूर्ण

अटल व्योम header_from_disk(काष्ठा log_header_core *core, काष्ठा log_header_disk *disk)
अणु
	core->magic = le32_to_cpu(disk->magic);
	core->version = le32_to_cpu(disk->version);
	core->nr_regions = le64_to_cpu(disk->nr_regions);
पूर्ण

अटल पूर्णांक rw_header(काष्ठा log_c *lc, पूर्णांक op)
अणु
	lc->io_req.bi_op = op;
	lc->io_req.bi_op_flags = 0;

	वापस dm_io(&lc->io_req, 1, &lc->header_location, शून्य);
पूर्ण

अटल पूर्णांक flush_header(काष्ठा log_c *lc)
अणु
	काष्ठा dm_io_region null_location = अणु
		.bdev = lc->header_location.bdev,
		.sector = 0,
		.count = 0,
	पूर्ण;

	lc->io_req.bi_op = REQ_OP_WRITE;
	lc->io_req.bi_op_flags = REQ_PREFLUSH;

	वापस dm_io(&lc->io_req, 1, &null_location, शून्य);
पूर्ण

अटल पूर्णांक पढ़ो_header(काष्ठा log_c *log)
अणु
	पूर्णांक r;

	r = rw_header(log, REQ_OP_READ);
	अगर (r)
		वापस r;

	header_from_disk(&log->header, log->disk_header);

	/* New log required? */
	अगर (log->sync != DEFAULTSYNC || log->header.magic != MIRROR_MAGIC) अणु
		log->header.magic = MIRROR_MAGIC;
		log->header.version = MIRROR_DISK_VERSION;
		log->header.nr_regions = 0;
	पूर्ण

#अगर_घोषित __LITTLE_ENDIAN
	अगर (log->header.version == 1)
		log->header.version = 2;
#पूर्ण_अगर

	अगर (log->header.version != MIRROR_DISK_VERSION) अणु
		DMWARN("incompatible disk log version");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _check_region_size(काष्ठा dm_target *ti, uपूर्णांक32_t region_size)
अणु
	अगर (region_size < 2 || region_size > ti->len)
		वापस 0;

	अगर (!is_घातer_of_2(region_size))
		वापस 0;

	वापस 1;
पूर्ण

/*----------------------------------------------------------------
 * core log स्थिरructor/deकाष्ठाor
 *
 * argv contains region_size followed optionally by [no]sync
 *--------------------------------------------------------------*/
#घोषणा BYTE_SHIFT 3
अटल पूर्णांक create_log_context(काष्ठा dm_dirty_log *log, काष्ठा dm_target *ti,
			      अचिन्हित पूर्णांक argc, अक्षर **argv,
			      काष्ठा dm_dev *dev)
अणु
	क्रमागत sync sync = DEFAULTSYNC;

	काष्ठा log_c *lc;
	uपूर्णांक32_t region_size;
	अचिन्हित पूर्णांक region_count;
	माप_प्रकार bitset_size, buf_size;
	पूर्णांक r;
	अक्षर dummy;

	अगर (argc < 1 || argc > 2) अणु
		DMWARN("wrong number of arguments to dirty region log");
		वापस -EINVAL;
	पूर्ण

	अगर (argc > 1) अणु
		अगर (!म_भेद(argv[1], "sync"))
			sync = FORCESYNC;
		अन्यथा अगर (!म_भेद(argv[1], "nosync"))
			sync = NOSYNC;
		अन्यथा अणु
			DMWARN("unrecognised sync argument to "
			       "dirty region log: %s", argv[1]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (माला_पूछो(argv[0], "%u%c", &region_size, &dummy) != 1 ||
	    !_check_region_size(ti, region_size)) अणु
		DMWARN("invalid region size %s", argv[0]);
		वापस -EINVAL;
	पूर्ण

	region_count = dm_sector_भाग_up(ti->len, region_size);

	lc = kदो_स्मृति(माप(*lc), GFP_KERNEL);
	अगर (!lc) अणु
		DMWARN("couldn't allocate core log");
		वापस -ENOMEM;
	पूर्ण

	lc->ti = ti;
	lc->touched_dirtied = 0;
	lc->touched_cleaned = 0;
	lc->flush_failed = 0;
	lc->region_size = region_size;
	lc->region_count = region_count;
	lc->sync = sync;

	/*
	 * Work out how many "unsigned long"s we need to hold the bitset.
	 */
	bitset_size = dm_round_up(region_count,
				  माप(*lc->clean_bits) << BYTE_SHIFT);
	bitset_size >>= BYTE_SHIFT;

	lc->bitset_uपूर्णांक32_count = bitset_size / माप(*lc->clean_bits);

	/*
	 * Disk log?
	 */
	अगर (!dev) अणु
		lc->clean_bits = vदो_स्मृति(bitset_size);
		अगर (!lc->clean_bits) अणु
			DMWARN("couldn't allocate clean bitset");
			kमुक्त(lc);
			वापस -ENOMEM;
		पूर्ण
		lc->disk_header = शून्य;
	पूर्ण अन्यथा अणु
		lc->log_dev = dev;
		lc->log_dev_failed = 0;
		lc->log_dev_flush_failed = 0;
		lc->header_location.bdev = lc->log_dev->bdev;
		lc->header_location.sector = 0;

		/*
		 * Buffer holds both header and bitset.
		 */
		buf_size =
		    dm_round_up((LOG_OFFSET << SECTOR_SHIFT) + bitset_size,
				bdev_logical_block_size(lc->header_location.
							    bdev));

		अगर (buf_size > i_size_पढ़ो(dev->bdev->bd_inode)) अणु
			DMWARN("log device %s too small: need %llu bytes",
				dev->name, (अचिन्हित दीर्घ दीर्घ)buf_size);
			kमुक्त(lc);
			वापस -EINVAL;
		पूर्ण

		lc->header_location.count = buf_size >> SECTOR_SHIFT;

		lc->io_req.mem.type = DM_IO_VMA;
		lc->io_req.notअगरy.fn = शून्य;
		lc->io_req.client = dm_io_client_create();
		अगर (IS_ERR(lc->io_req.client)) अणु
			r = PTR_ERR(lc->io_req.client);
			DMWARN("couldn't allocate disk io client");
			kमुक्त(lc);
			वापस r;
		पूर्ण

		lc->disk_header = vदो_स्मृति(buf_size);
		अगर (!lc->disk_header) अणु
			DMWARN("couldn't allocate disk log buffer");
			dm_io_client_destroy(lc->io_req.client);
			kमुक्त(lc);
			वापस -ENOMEM;
		पूर्ण

		lc->io_req.mem.ptr.vma = lc->disk_header;
		lc->clean_bits = (व्योम *)lc->disk_header +
				 (LOG_OFFSET << SECTOR_SHIFT);
	पूर्ण

	स_रखो(lc->clean_bits, -1, bitset_size);

	lc->sync_bits = vदो_स्मृति(bitset_size);
	अगर (!lc->sync_bits) अणु
		DMWARN("couldn't allocate sync bitset");
		अगर (!dev)
			vमुक्त(lc->clean_bits);
		अन्यथा
			dm_io_client_destroy(lc->io_req.client);
		vमुक्त(lc->disk_header);
		kमुक्त(lc);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(lc->sync_bits, (sync == NOSYNC) ? -1 : 0, bitset_size);
	lc->sync_count = (sync == NOSYNC) ? region_count : 0;

	lc->recovering_bits = vzalloc(bitset_size);
	अगर (!lc->recovering_bits) अणु
		DMWARN("couldn't allocate sync bitset");
		vमुक्त(lc->sync_bits);
		अगर (!dev)
			vमुक्त(lc->clean_bits);
		अन्यथा
			dm_io_client_destroy(lc->io_req.client);
		vमुक्त(lc->disk_header);
		kमुक्त(lc);
		वापस -ENOMEM;
	पूर्ण
	lc->sync_search = 0;
	log->context = lc;

	वापस 0;
पूर्ण

अटल पूर्णांक core_ctr(काष्ठा dm_dirty_log *log, काष्ठा dm_target *ti,
		    अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	वापस create_log_context(log, ti, argc, argv, शून्य);
पूर्ण

अटल व्योम destroy_log_context(काष्ठा log_c *lc)
अणु
	vमुक्त(lc->sync_bits);
	vमुक्त(lc->recovering_bits);
	kमुक्त(lc);
पूर्ण

अटल व्योम core_dtr(काष्ठा dm_dirty_log *log)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;

	vमुक्त(lc->clean_bits);
	destroy_log_context(lc);
पूर्ण

/*----------------------------------------------------------------
 * disk log स्थिरructor/deकाष्ठाor
 *
 * argv contains log_device region_size followed optionally by [no]sync
 *--------------------------------------------------------------*/
अटल पूर्णांक disk_ctr(काष्ठा dm_dirty_log *log, काष्ठा dm_target *ti,
		    अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक r;
	काष्ठा dm_dev *dev;

	अगर (argc < 2 || argc > 3) अणु
		DMWARN("wrong number of arguments to disk dirty region log");
		वापस -EINVAL;
	पूर्ण

	r = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &dev);
	अगर (r)
		वापस r;

	r = create_log_context(log, ti, argc - 1, argv + 1, dev);
	अगर (r) अणु
		dm_put_device(ti, dev);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम disk_dtr(काष्ठा dm_dirty_log *log)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;

	dm_put_device(lc->ti, lc->log_dev);
	vमुक्त(lc->disk_header);
	dm_io_client_destroy(lc->io_req.client);
	destroy_log_context(lc);
पूर्ण

अटल व्योम fail_log_device(काष्ठा log_c *lc)
अणु
	अगर (lc->log_dev_failed)
		वापस;

	lc->log_dev_failed = 1;
	dm_table_event(lc->ti->table);
पूर्ण

अटल पूर्णांक disk_resume(काष्ठा dm_dirty_log *log)
अणु
	पूर्णांक r;
	अचिन्हित i;
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;
	माप_प्रकार size = lc->bitset_uपूर्णांक32_count * माप(uपूर्णांक32_t);

	/* पढ़ो the disk header */
	r = पढ़ो_header(lc);
	अगर (r) अणु
		DMWARN("%s: Failed to read header on dirty region log device",
		       lc->log_dev->name);
		fail_log_device(lc);
		/*
		 * If the log device cannot be पढ़ो, we must assume
		 * all regions are out-of-sync.  If we simply वापस
		 * here, the state will be uninitialized and could
		 * lead us to वापस 'in-sync' status क्रम regions
		 * that are actually 'out-of-sync'.
		 */
		lc->header.nr_regions = 0;
	पूर्ण

	/* set or clear any new bits -- device has grown */
	अगर (lc->sync == NOSYNC)
		क्रम (i = lc->header.nr_regions; i < lc->region_count; i++)
			/* FIXME: amazingly inefficient */
			log_set_bit(lc, lc->clean_bits, i);
	अन्यथा
		क्रम (i = lc->header.nr_regions; i < lc->region_count; i++)
			/* FIXME: amazingly inefficient */
			log_clear_bit(lc, lc->clean_bits, i);

	/* clear any old bits -- device has shrunk */
	क्रम (i = lc->region_count; i % (माप(*lc->clean_bits) << BYTE_SHIFT); i++)
		log_clear_bit(lc, lc->clean_bits, i);

	/* copy clean across to sync */
	स_नकल(lc->sync_bits, lc->clean_bits, size);
	lc->sync_count = memweight(lc->clean_bits,
				lc->bitset_uपूर्णांक32_count * माप(uपूर्णांक32_t));
	lc->sync_search = 0;

	/* set the correct number of regions in the header */
	lc->header.nr_regions = lc->region_count;

	header_to_disk(&lc->header, lc->disk_header);

	/* ग_लिखो the new header */
	r = rw_header(lc, REQ_OP_WRITE);
	अगर (!r) अणु
		r = flush_header(lc);
		अगर (r)
			lc->log_dev_flush_failed = 1;
	पूर्ण
	अगर (r) अणु
		DMWARN("%s: Failed to write header on dirty region log device",
		       lc->log_dev->name);
		fail_log_device(lc);
	पूर्ण

	वापस r;
पूर्ण

अटल uपूर्णांक32_t core_get_region_size(काष्ठा dm_dirty_log *log)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;
	वापस lc->region_size;
पूर्ण

अटल पूर्णांक core_resume(काष्ठा dm_dirty_log *log)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;
	lc->sync_search = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक core_is_clean(काष्ठा dm_dirty_log *log, region_t region)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;
	वापस log_test_bit(lc->clean_bits, region);
पूर्ण

अटल पूर्णांक core_in_sync(काष्ठा dm_dirty_log *log, region_t region, पूर्णांक block)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;
	वापस log_test_bit(lc->sync_bits, region);
पूर्ण

अटल पूर्णांक core_flush(काष्ठा dm_dirty_log *log)
अणु
	/* no op */
	वापस 0;
पूर्ण

अटल पूर्णांक disk_flush(काष्ठा dm_dirty_log *log)
अणु
	पूर्णांक r, i;
	काष्ठा log_c *lc = log->context;

	/* only ग_लिखो अगर the log has changed */
	अगर (!lc->touched_cleaned && !lc->touched_dirtied)
		वापस 0;

	अगर (lc->touched_cleaned && log->flush_callback_fn &&
	    log->flush_callback_fn(lc->ti)) अणु
		/*
		 * At this poपूर्णांक it is impossible to determine which
		 * regions are clean and which are dirty (without
		 * re-पढ़ोing the log off disk). So mark all of them
		 * dirty.
		 */
		lc->flush_failed = 1;
		क्रम (i = 0; i < lc->region_count; i++)
			log_clear_bit(lc, lc->clean_bits, i);
	पूर्ण

	r = rw_header(lc, REQ_OP_WRITE);
	अगर (r)
		fail_log_device(lc);
	अन्यथा अणु
		अगर (lc->touched_dirtied) अणु
			r = flush_header(lc);
			अगर (r) अणु
				lc->log_dev_flush_failed = 1;
				fail_log_device(lc);
			पूर्ण अन्यथा
				lc->touched_dirtied = 0;
		पूर्ण
		lc->touched_cleaned = 0;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम core_mark_region(काष्ठा dm_dirty_log *log, region_t region)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;
	log_clear_bit(lc, lc->clean_bits, region);
पूर्ण

अटल व्योम core_clear_region(काष्ठा dm_dirty_log *log, region_t region)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;
	अगर (likely(!lc->flush_failed))
		log_set_bit(lc, lc->clean_bits, region);
पूर्ण

अटल पूर्णांक core_get_resync_work(काष्ठा dm_dirty_log *log, region_t *region)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;

	अगर (lc->sync_search >= lc->region_count)
		वापस 0;

	करो अणु
		*region = find_next_zero_bit_le(lc->sync_bits,
					     lc->region_count,
					     lc->sync_search);
		lc->sync_search = *region + 1;

		अगर (*region >= lc->region_count)
			वापस 0;

	पूर्ण जबतक (log_test_bit(lc->recovering_bits, *region));

	log_set_bit(lc, lc->recovering_bits, *region);
	वापस 1;
पूर्ण

अटल व्योम core_set_region_sync(काष्ठा dm_dirty_log *log, region_t region,
				 पूर्णांक in_sync)
अणु
	काष्ठा log_c *lc = (काष्ठा log_c *) log->context;

	log_clear_bit(lc, lc->recovering_bits, region);
	अगर (in_sync) अणु
		log_set_bit(lc, lc->sync_bits, region);
                lc->sync_count++;
        पूर्ण अन्यथा अगर (log_test_bit(lc->sync_bits, region)) अणु
		lc->sync_count--;
		log_clear_bit(lc, lc->sync_bits, region);
	पूर्ण
पूर्ण

अटल region_t core_get_sync_count(काष्ठा dm_dirty_log *log)
अणु
        काष्ठा log_c *lc = (काष्ठा log_c *) log->context;

        वापस lc->sync_count;
पूर्ण

#घोषणा	DMEMIT_SYNC \
	अगर (lc->sync != DEFAULTSYNC) \
		DMEMIT("%ssync ", lc->sync == NOSYNC ? "no" : "")

अटल पूर्णांक core_status(काष्ठा dm_dirty_log *log, status_type_t status,
		       अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	पूर्णांक sz = 0;
	काष्ठा log_c *lc = log->context;

	चयन(status) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("1 %s", log->type->name);
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%s %u %u ", log->type->name,
		       lc->sync == DEFAULTSYNC ? 1 : 2, lc->region_size);
		DMEMIT_SYNC;
	पूर्ण

	वापस sz;
पूर्ण

अटल पूर्णांक disk_status(काष्ठा dm_dirty_log *log, status_type_t status,
		       अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	पूर्णांक sz = 0;
	काष्ठा log_c *lc = log->context;

	चयन(status) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("3 %s %s %c", log->type->name, lc->log_dev->name,
		       lc->log_dev_flush_failed ? 'F' :
		       lc->log_dev_failed ? 'D' :
		       'A');
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%s %u %s %u ", log->type->name,
		       lc->sync == DEFAULTSYNC ? 2 : 3, lc->log_dev->name,
		       lc->region_size);
		DMEMIT_SYNC;
	पूर्ण

	वापस sz;
पूर्ण

अटल काष्ठा dm_dirty_log_type _core_type = अणु
	.name = "core",
	.module = THIS_MODULE,
	.ctr = core_ctr,
	.dtr = core_dtr,
	.resume = core_resume,
	.get_region_size = core_get_region_size,
	.is_clean = core_is_clean,
	.in_sync = core_in_sync,
	.flush = core_flush,
	.mark_region = core_mark_region,
	.clear_region = core_clear_region,
	.get_resync_work = core_get_resync_work,
	.set_region_sync = core_set_region_sync,
	.get_sync_count = core_get_sync_count,
	.status = core_status,
पूर्ण;

अटल काष्ठा dm_dirty_log_type _disk_type = अणु
	.name = "disk",
	.module = THIS_MODULE,
	.ctr = disk_ctr,
	.dtr = disk_dtr,
	.postsuspend = disk_flush,
	.resume = disk_resume,
	.get_region_size = core_get_region_size,
	.is_clean = core_is_clean,
	.in_sync = core_in_sync,
	.flush = disk_flush,
	.mark_region = core_mark_region,
	.clear_region = core_clear_region,
	.get_resync_work = core_get_resync_work,
	.set_region_sync = core_set_region_sync,
	.get_sync_count = core_get_sync_count,
	.status = disk_status,
पूर्ण;

अटल पूर्णांक __init dm_dirty_log_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_dirty_log_type_रेजिस्टर(&_core_type);
	अगर (r)
		DMWARN("couldn't register core log");

	r = dm_dirty_log_type_रेजिस्टर(&_disk_type);
	अगर (r) अणु
		DMWARN("couldn't register disk type");
		dm_dirty_log_type_unरेजिस्टर(&_core_type);
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम __निकास dm_dirty_log_निकास(व्योम)
अणु
	dm_dirty_log_type_unरेजिस्टर(&_disk_type);
	dm_dirty_log_type_unरेजिस्टर(&_core_type);
पूर्ण

module_init(dm_dirty_log_init);
module_निकास(dm_dirty_log_निकास);

MODULE_DESCRIPTION(DM_NAME " dirty region log");
MODULE_AUTHOR("Joe Thornber, Heinz Mauelshagen <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
