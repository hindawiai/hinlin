<शैली गुरु>
/*
 * Copyright (C) 2001 Sistina Software (UK) Limited.
 * Copyright (C) 2004-2008 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the LGPL.
 */

#अगर_अघोषित _LINUX_DEVICE_MAPPER_H
#घोषणा _LINUX_DEVICE_MAPPER_H

#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/dm-ioctl.h>
#समावेश <linux/math64.h>
#समावेश <linux/ratelimit.h>

काष्ठा dm_dev;
काष्ठा dm_target;
काष्ठा dm_table;
काष्ठा dm_report_zones_args;
काष्ठा mapped_device;
काष्ठा bio_vec;

/*
 * Type of table, mapped_device's mempool and request_queue
 */
क्रमागत dm_queue_mode अणु
	DM_TYPE_NONE		 = 0,
	DM_TYPE_BIO_BASED	 = 1,
	DM_TYPE_REQUEST_BASED	 = 2,
	DM_TYPE_DAX_BIO_BASED	 = 3,
पूर्ण;

प्रकार क्रमागत अणु STATUSTYPE_INFO, STATUSTYPE_TABLE पूर्ण status_type_t;

जोड़ map_info अणु
	व्योम *ptr;
पूर्ण;

/*
 * In the स्थिरructor the target parameter will alपढ़ोy have the
 * table, type, begin and len fields filled in.
 */
प्रकार पूर्णांक (*dm_ctr_fn) (काष्ठा dm_target *target,
			  अचिन्हित पूर्णांक argc, अक्षर **argv);

/*
 * The deकाष्ठाor करोesn't need to मुक्त the dm_target, just
 * anything hidden ti->निजी.
 */
प्रकार व्योम (*dm_dtr_fn) (काष्ठा dm_target *ti);

/*
 * The map function must वापस:
 * < 0: error
 * = 0: The target will handle the io by resubmitting it later
 * = 1: simple remap complete
 * = 2: The target wants to push back the io
 */
प्रकार पूर्णांक (*dm_map_fn) (काष्ठा dm_target *ti, काष्ठा bio *bio);
प्रकार पूर्णांक (*dm_clone_and_map_request_fn) (काष्ठा dm_target *ti,
					    काष्ठा request *rq,
					    जोड़ map_info *map_context,
					    काष्ठा request **clone);
प्रकार व्योम (*dm_release_clone_request_fn) (काष्ठा request *clone,
					     जोड़ map_info *map_context);

/*
 * Returns:
 * < 0 : error (currently ignored)
 * 0   : ended successfully
 * 1   : क्रम some reason the io has still not completed (eg,
 *       multipath target might want to requeue a failed io).
 * 2   : The target wants to push back the io
 */
प्रकार पूर्णांक (*dm_endio_fn) (काष्ठा dm_target *ti,
			    काष्ठा bio *bio, blk_status_t *error);
प्रकार पूर्णांक (*dm_request_endio_fn) (काष्ठा dm_target *ti,
				    काष्ठा request *clone, blk_status_t error,
				    जोड़ map_info *map_context);

प्रकार व्योम (*dm_presuspend_fn) (काष्ठा dm_target *ti);
प्रकार व्योम (*dm_presuspend_unकरो_fn) (काष्ठा dm_target *ti);
प्रकार व्योम (*dm_postsuspend_fn) (काष्ठा dm_target *ti);
प्रकार पूर्णांक (*dm_preresume_fn) (काष्ठा dm_target *ti);
प्रकार व्योम (*dm_resume_fn) (काष्ठा dm_target *ti);

प्रकार व्योम (*dm_status_fn) (काष्ठा dm_target *ti, status_type_t status_type,
			      अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen);

प्रकार पूर्णांक (*dm_message_fn) (काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv,
			      अक्षर *result, अचिन्हित maxlen);

प्रकार पूर्णांक (*dm_prepare_ioctl_fn) (काष्ठा dm_target *ti, काष्ठा block_device **bdev);

#अगर_घोषित CONFIG_BLK_DEV_ZONED
प्रकार पूर्णांक (*dm_report_zones_fn) (काष्ठा dm_target *ti,
				   काष्ठा dm_report_zones_args *args,
				   अचिन्हित पूर्णांक nr_zones);
#अन्यथा
/*
 * Define dm_report_zones_fn so that tarमाला_लो can assign to शून्य अगर
 * CONFIG_BLK_DEV_ZONED disabled. Otherwise each target needs to करो
 * awkward #अगर_घोषितs in their target_type, etc.
 */
प्रकार पूर्णांक (*dm_report_zones_fn) (काष्ठा dm_target *dummy);
#पूर्ण_अगर

/*
 * These iteration functions are typically used to check (and combine)
 * properties of underlying devices.
 * E.g. Does at least one underlying device support flush?
 *      Does any underlying device not support WRITE_SAME?
 *
 * The callout function is called once क्रम each contiguous section of
 * an underlying device.  State can be मुख्यtained in *data.
 * Return non-zero to stop iterating through any further devices.
 */
प्रकार पूर्णांक (*iterate_devices_callout_fn) (काष्ठा dm_target *ti,
					   काष्ठा dm_dev *dev,
					   sector_t start, sector_t len,
					   व्योम *data);

/*
 * This function must iterate through each section of device used by the
 * target until it encounters a non-zero वापस code, which it then वापसs.
 * Returns zero अगर no callout वापसed non-zero.
 */
प्रकार पूर्णांक (*dm_iterate_devices_fn) (काष्ठा dm_target *ti,
				      iterate_devices_callout_fn fn,
				      व्योम *data);

प्रकार व्योम (*dm_io_hपूर्णांकs_fn) (काष्ठा dm_target *ti,
				काष्ठा queue_limits *limits);

/*
 * Returns:
 *    0: The target can handle the next I/O immediately.
 *    1: The target can't handle the next I/O immediately.
 */
प्रकार पूर्णांक (*dm_busy_fn) (काष्ठा dm_target *ti);

/*
 * Returns:
 *  < 0 : error
 * >= 0 : the number of bytes accessible at the address
 */
प्रकार दीर्घ (*dm_dax_direct_access_fn) (काष्ठा dm_target *ti, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn);
प्रकार माप_प्रकार (*dm_dax_copy_iter_fn)(काष्ठा dm_target *ti, pgoff_t pgoff,
		व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i);
प्रकार पूर्णांक (*dm_dax_zero_page_range_fn)(काष्ठा dm_target *ti, pgoff_t pgoff,
		माप_प्रकार nr_pages);
#घोषणा PAGE_SECTORS (PAGE_SIZE / 512)

व्योम dm_error(स्थिर अक्षर *message);

काष्ठा dm_dev अणु
	काष्ठा block_device *bdev;
	काष्ठा dax_device *dax_dev;
	भ_शेषe_t mode;
	अक्षर name[16];
पूर्ण;

dev_t dm_get_dev_t(स्थिर अक्षर *path);

/*
 * Conकाष्ठाors should call these functions to ensure destination devices
 * are खोलोed/बंदd correctly.
 */
पूर्णांक dm_get_device(काष्ठा dm_target *ti, स्थिर अक्षर *path, भ_शेषe_t mode,
		  काष्ठा dm_dev **result);
व्योम dm_put_device(काष्ठा dm_target *ti, काष्ठा dm_dev *d);

/*
 * Inक्रमmation about a target type
 */

काष्ठा target_type अणु
	uपूर्णांक64_t features;
	स्थिर अक्षर *name;
	काष्ठा module *module;
	अचिन्हित version[3];
	dm_ctr_fn ctr;
	dm_dtr_fn dtr;
	dm_map_fn map;
	dm_clone_and_map_request_fn clone_and_map_rq;
	dm_release_clone_request_fn release_clone_rq;
	dm_endio_fn end_io;
	dm_request_endio_fn rq_end_io;
	dm_presuspend_fn presuspend;
	dm_presuspend_unकरो_fn presuspend_unकरो;
	dm_postsuspend_fn postsuspend;
	dm_preresume_fn preresume;
	dm_resume_fn resume;
	dm_status_fn status;
	dm_message_fn message;
	dm_prepare_ioctl_fn prepare_ioctl;
	dm_report_zones_fn report_zones;
	dm_busy_fn busy;
	dm_iterate_devices_fn iterate_devices;
	dm_io_hपूर्णांकs_fn io_hपूर्णांकs;
	dm_dax_direct_access_fn direct_access;
	dm_dax_copy_iter_fn dax_copy_from_iter;
	dm_dax_copy_iter_fn dax_copy_to_iter;
	dm_dax_zero_page_range_fn dax_zero_page_range;

	/* For पूर्णांकernal device-mapper use. */
	काष्ठा list_head list;
पूर्ण;

/*
 * Target features
 */

/*
 * Any table that contains an instance of this target must have only one.
 */
#घोषणा DM_TARGET_SINGLETON		0x00000001
#घोषणा dm_target_needs_singleton(type)	((type)->features & DM_TARGET_SINGLETON)

/*
 * Indicates that a target करोes not support पढ़ो-only devices.
 */
#घोषणा DM_TARGET_ALWAYS_WRITEABLE	0x00000002
#घोषणा dm_target_always_ग_लिखोable(type) \
		((type)->features & DM_TARGET_ALWAYS_WRITEABLE)

/*
 * Any device that contains a table with an instance of this target may never
 * have tables containing any dअगरferent target type.
 */
#घोषणा DM_TARGET_IMMUTABLE		0x00000004
#घोषणा dm_target_is_immutable(type)	((type)->features & DM_TARGET_IMMUTABLE)

/*
 * Indicates that a target may replace any target; even immutable tarमाला_लो.
 * .map, .map_rq, .clone_and_map_rq and .release_clone_rq are all defined.
 */
#घोषणा DM_TARGET_WILDCARD		0x00000008
#घोषणा dm_target_is_wildcard(type)	((type)->features & DM_TARGET_WILDCARD)

/*
 * A target implements own bio data पूर्णांकegrity.
 */
#घोषणा DM_TARGET_INTEGRITY		0x00000010
#घोषणा dm_target_has_पूर्णांकegrity(type)	((type)->features & DM_TARGET_INTEGRITY)

/*
 * A target passes पूर्णांकegrity data to the lower device.
 */
#घोषणा DM_TARGET_PASSES_INTEGRITY	0x00000020
#घोषणा dm_target_passes_पूर्णांकegrity(type) ((type)->features & DM_TARGET_PASSES_INTEGRITY)

/*
 * Indicates support क्रम zoned block devices:
 * - DM_TARGET_ZONED_HM: the target also supports host-managed zoned
 *   block devices but करोes not support combining dअगरferent zoned models.
 * - DM_TARGET_MIXED_ZONED_MODEL: the target supports combining multiple
 *   devices with dअगरferent zoned models.
 */
#अगर_घोषित CONFIG_BLK_DEV_ZONED
#घोषणा DM_TARGET_ZONED_HM		0x00000040
#घोषणा dm_target_supports_zoned_hm(type) ((type)->features & DM_TARGET_ZONED_HM)
#अन्यथा
#घोषणा DM_TARGET_ZONED_HM		0x00000000
#घोषणा dm_target_supports_zoned_hm(type) (false)
#पूर्ण_अगर

/*
 * A target handles REQ_NOWAIT
 */
#घोषणा DM_TARGET_NOWAIT		0x00000080
#घोषणा dm_target_supports_noरुको(type) ((type)->features & DM_TARGET_NOWAIT)

/*
 * A target supports passing through अंतरभूत crypto support.
 */
#घोषणा DM_TARGET_PASSES_CRYPTO		0x00000100
#घोषणा dm_target_passes_crypto(type) ((type)->features & DM_TARGET_PASSES_CRYPTO)

#अगर_घोषित CONFIG_BLK_DEV_ZONED
#घोषणा DM_TARGET_MIXED_ZONED_MODEL	0x00000200
#घोषणा dm_target_supports_mixed_zoned_model(type) \
	((type)->features & DM_TARGET_MIXED_ZONED_MODEL)
#अन्यथा
#घोषणा DM_TARGET_MIXED_ZONED_MODEL	0x00000000
#घोषणा dm_target_supports_mixed_zoned_model(type) (false)
#पूर्ण_अगर

काष्ठा dm_target अणु
	काष्ठा dm_table *table;
	काष्ठा target_type *type;

	/* target limits */
	sector_t begin;
	sector_t len;

	/* If non-zero, maximum size of I/O submitted to a target. */
	uपूर्णांक32_t max_io_len;

	/*
	 * A number of zero-length barrier bios that will be submitted
	 * to the target क्रम the purpose of flushing cache.
	 *
	 * The bio number can be accessed with dm_bio_get_target_bio_nr.
	 * It is a responsibility of the target driver to remap these bios
	 * to the real underlying devices.
	 */
	अचिन्हित num_flush_bios;

	/*
	 * The number of discard bios that will be submitted to the target.
	 * The bio number can be accessed with dm_bio_get_target_bio_nr.
	 */
	अचिन्हित num_discard_bios;

	/*
	 * The number of secure erase bios that will be submitted to the target.
	 * The bio number can be accessed with dm_bio_get_target_bio_nr.
	 */
	अचिन्हित num_secure_erase_bios;

	/*
	 * The number of WRITE SAME bios that will be submitted to the target.
	 * The bio number can be accessed with dm_bio_get_target_bio_nr.
	 */
	अचिन्हित num_ग_लिखो_same_bios;

	/*
	 * The number of WRITE ZEROES bios that will be submitted to the target.
	 * The bio number can be accessed with dm_bio_get_target_bio_nr.
	 */
	अचिन्हित num_ग_लिखो_zeroes_bios;

	/*
	 * The minimum number of extra bytes allocated in each io क्रम the
	 * target to use.
	 */
	अचिन्हित per_io_data_size;

	/* target specअगरic data */
	व्योम *निजी;

	/* Used to provide an error string from the ctr */
	अक्षर *error;

	/*
	 * Set अगर this target needs to receive flushes regardless of
	 * whether or not its underlying devices have support.
	 */
	bool flush_supported:1;

	/*
	 * Set अगर this target needs to receive discards regardless of
	 * whether or not its underlying devices have support.
	 */
	bool discards_supported:1;

	/*
	 * Set अगर we need to limit the number of in-flight bios when swapping.
	 */
	bool limit_swap_bios:1;
पूर्ण;

व्योम *dm_per_bio_data(काष्ठा bio *bio, माप_प्रकार data_size);
काष्ठा bio *dm_bio_from_per_bio_data(व्योम *data, माप_प्रकार data_size);
अचिन्हित dm_bio_get_target_bio_nr(स्थिर काष्ठा bio *bio);

u64 dm_start_समय_ns_from_clone(काष्ठा bio *bio);

पूर्णांक dm_रेजिस्टर_target(काष्ठा target_type *t);
व्योम dm_unरेजिस्टर_target(काष्ठा target_type *t);

/*
 * Target argument parsing.
 */
काष्ठा dm_arg_set अणु
	अचिन्हित argc;
	अक्षर **argv;
पूर्ण;

/*
 * The minimum and maximum value of a numeric argument, together with
 * the error message to use अगर the number is found to be outside that range.
 */
काष्ठा dm_arg अणु
	अचिन्हित min;
	अचिन्हित max;
	अक्षर *error;
पूर्ण;

/*
 * Validate the next argument, either वापसing it as *value or, अगर invalid,
 * वापसing -EINVAL and setting *error.
 */
पूर्णांक dm_पढ़ो_arg(स्थिर काष्ठा dm_arg *arg, काष्ठा dm_arg_set *arg_set,
		अचिन्हित *value, अक्षर **error);

/*
 * Process the next argument as the start of a group containing between
 * arg->min and arg->max further arguments. Either वापस the size as
 * *num_args or, अगर invalid, वापस -EINVAL and set *error.
 */
पूर्णांक dm_पढ़ो_arg_group(स्थिर काष्ठा dm_arg *arg, काष्ठा dm_arg_set *arg_set,
		      अचिन्हित *num_args, अक्षर **error);

/*
 * Return the current argument and shअगरt to the next.
 */
स्थिर अक्षर *dm_shअगरt_arg(काष्ठा dm_arg_set *as);

/*
 * Move through num_args arguments.
 */
व्योम dm_consume_args(काष्ठा dm_arg_set *as, अचिन्हित num_args);

/*-----------------------------------------------------------------
 * Functions क्रम creating and manipulating mapped devices.
 * Drop the reference with dm_put when you finish with the object.
 *---------------------------------------------------------------*/

/*
 * DM_ANY_MINOR chooses the next available minor number.
 */
#घोषणा DM_ANY_MINOR (-1)
पूर्णांक dm_create(पूर्णांक minor, काष्ठा mapped_device **md);

/*
 * Reference counting क्रम md.
 */
काष्ठा mapped_device *dm_get_md(dev_t dev);
व्योम dm_get(काष्ठा mapped_device *md);
पूर्णांक dm_hold(काष्ठा mapped_device *md);
व्योम dm_put(काष्ठा mapped_device *md);

/*
 * An arbitrary poपूर्णांकer may be stored aदीर्घside a mapped device.
 */
व्योम dm_set_mdptr(काष्ठा mapped_device *md, व्योम *ptr);
व्योम *dm_get_mdptr(काष्ठा mapped_device *md);

/*
 * A device can still be used जबतक suspended, but I/O is deferred.
 */
पूर्णांक dm_suspend(काष्ठा mapped_device *md, अचिन्हित suspend_flags);
पूर्णांक dm_resume(काष्ठा mapped_device *md);

/*
 * Event functions.
 */
uपूर्णांक32_t dm_get_event_nr(काष्ठा mapped_device *md);
पूर्णांक dm_रुको_event(काष्ठा mapped_device *md, पूर्णांक event_nr);
uपूर्णांक32_t dm_next_uevent_seq(काष्ठा mapped_device *md);
व्योम dm_uevent_add(काष्ठा mapped_device *md, काष्ठा list_head *elist);

/*
 * Info functions.
 */
स्थिर अक्षर *dm_device_name(काष्ठा mapped_device *md);
पूर्णांक dm_copy_name_and_uuid(काष्ठा mapped_device *md, अक्षर *name, अक्षर *uuid);
काष्ठा gendisk *dm_disk(काष्ठा mapped_device *md);
पूर्णांक dm_suspended(काष्ठा dm_target *ti);
पूर्णांक dm_post_suspending(काष्ठा dm_target *ti);
पूर्णांक dm_noflush_suspending(काष्ठा dm_target *ti);
व्योम dm_accept_partial_bio(काष्ठा bio *bio, अचिन्हित n_sectors);
जोड़ map_info *dm_get_rq_mapinfo(काष्ठा request *rq);

#अगर_घोषित CONFIG_BLK_DEV_ZONED
काष्ठा dm_report_zones_args अणु
	काष्ठा dm_target *tgt;
	sector_t next_sector;

	व्योम *orig_data;
	report_zones_cb orig_cb;
	अचिन्हित पूर्णांक zone_idx;

	/* must be filled by ->report_zones beक्रमe calling dm_report_zones_cb */
	sector_t start;
पूर्ण;
पूर्णांक dm_report_zones_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx, व्योम *data);
#पूर्ण_अगर /* CONFIG_BLK_DEV_ZONED */

/*
 * Device mapper functions to parse and create devices specअगरied by the
 * parameter "dm-mod.create="
 */
पूर्णांक __init dm_early_create(काष्ठा dm_ioctl *dmi,
			   काष्ठा dm_target_spec **spec_array,
			   अक्षर **target_params_array);

काष्ठा queue_limits *dm_get_queue_limits(काष्ठा mapped_device *md);

/*
 * Geometry functions.
 */
पूर्णांक dm_get_geometry(काष्ठा mapped_device *md, काष्ठा hd_geometry *geo);
पूर्णांक dm_set_geometry(काष्ठा mapped_device *md, काष्ठा hd_geometry *geo);

/*-----------------------------------------------------------------
 * Functions क्रम manipulating device-mapper tables.
 *---------------------------------------------------------------*/

/*
 * First create an empty table.
 */
पूर्णांक dm_table_create(काष्ठा dm_table **result, भ_शेषe_t mode,
		    अचिन्हित num_tarमाला_लो, काष्ठा mapped_device *md);

/*
 * Then call this once क्रम each target.
 */
पूर्णांक dm_table_add_target(काष्ठा dm_table *t, स्थिर अक्षर *type,
			sector_t start, sector_t len, अक्षर *params);

/*
 * Target can use this to set the table's type.
 * Can only ever be called from a target's ctr.
 * Useful क्रम "hybrid" target (supports both bio-based
 * and request-based).
 */
व्योम dm_table_set_type(काष्ठा dm_table *t, क्रमागत dm_queue_mode type);

/*
 * Finally call this to make the table पढ़ोy क्रम use.
 */
पूर्णांक dm_table_complete(काष्ठा dm_table *t);

/*
 * Destroy the table when finished.
 */
व्योम dm_table_destroy(काष्ठा dm_table *t);

/*
 * Target may require that it is never sent I/O larger than len.
 */
पूर्णांक __must_check dm_set_target_max_io_len(काष्ठा dm_target *ti, sector_t len);

/*
 * Table reference counting.
 */
काष्ठा dm_table *dm_get_live_table(काष्ठा mapped_device *md, पूर्णांक *srcu_idx);
व्योम dm_put_live_table(काष्ठा mapped_device *md, पूर्णांक srcu_idx);
व्योम dm_sync_table(काष्ठा mapped_device *md);

/*
 * Queries
 */
sector_t dm_table_get_size(काष्ठा dm_table *t);
अचिन्हित पूर्णांक dm_table_get_num_tarमाला_लो(काष्ठा dm_table *t);
भ_शेषe_t dm_table_get_mode(काष्ठा dm_table *t);
काष्ठा mapped_device *dm_table_get_md(काष्ठा dm_table *t);
स्थिर अक्षर *dm_table_device_name(काष्ठा dm_table *t);

/*
 * Trigger an event.
 */
व्योम dm_table_event(काष्ठा dm_table *t);

/*
 * Run the queue क्रम request-based tarमाला_लो.
 */
व्योम dm_table_run_md_queue_async(काष्ठा dm_table *t);

/*
 * The device must be suspended beक्रमe calling this method.
 * Returns the previous table, which the caller must destroy.
 */
काष्ठा dm_table *dm_swap_table(काष्ठा mapped_device *md,
			       काष्ठा dm_table *t);

/*
 * Table keyslot manager functions
 */
व्योम dm_destroy_keyslot_manager(काष्ठा blk_keyslot_manager *ksm);

/*-----------------------------------------------------------------
 * Macros.
 *---------------------------------------------------------------*/
#घोषणा DM_NAME "device-mapper"

#घोषणा DM_FMT(fmt) DM_NAME ": " DM_MSG_PREFIX ": " fmt "\n"

#घोषणा DMCRIT(fmt, ...) pr_crit(DM_FMT(fmt), ##__VA_ARGS__)

#घोषणा DMERR(fmt, ...) pr_err(DM_FMT(fmt), ##__VA_ARGS__)
#घोषणा DMERR_LIMIT(fmt, ...) pr_err_ratelimited(DM_FMT(fmt), ##__VA_ARGS__)
#घोषणा DMWARN(fmt, ...) pr_warn(DM_FMT(fmt), ##__VA_ARGS__)
#घोषणा DMWARN_LIMIT(fmt, ...) pr_warn_ratelimited(DM_FMT(fmt), ##__VA_ARGS__)
#घोषणा DMINFO(fmt, ...) pr_info(DM_FMT(fmt), ##__VA_ARGS__)
#घोषणा DMINFO_LIMIT(fmt, ...) pr_info_ratelimited(DM_FMT(fmt), ##__VA_ARGS__)

#घोषणा DMDEBUG(fmt, ...) pr_debug(DM_FMT(fmt), ##__VA_ARGS__)
#घोषणा DMDEBUG_LIMIT(fmt, ...) pr_debug_ratelimited(DM_FMT(fmt), ##__VA_ARGS__)

#घोषणा DMEMIT(x...) sz += ((sz >= maxlen) ? \
			  0 : scnम_लिखो(result + sz, maxlen - sz, x))

/*
 * Definitions of वापस values from target end_io function.
 */
#घोषणा DM_ENDIO_DONE		0
#घोषणा DM_ENDIO_INCOMPLETE	1
#घोषणा DM_ENDIO_REQUEUE	2
#घोषणा DM_ENDIO_DELAY_REQUEUE	3

/*
 * Definitions of वापस values from target map function.
 */
#घोषणा DM_MAPIO_SUBMITTED	0
#घोषणा DM_MAPIO_REMAPPED	1
#घोषणा DM_MAPIO_REQUEUE	DM_ENDIO_REQUEUE
#घोषणा DM_MAPIO_DELAY_REQUEUE	DM_ENDIO_DELAY_REQUEUE
#घोषणा DM_MAPIO_KILL		4

#घोषणा dm_sector_भाग64(x, y)( \
अणु \
	u64 _res; \
	(x) = भाग64_u64_rem(x, y, &_res); \
	_res; \
पूर्ण \
)

/*
 * Ceiling(n / sz)
 */
#घोषणा dm_भाग_up(n, sz) (((n) + (sz) - 1) / (sz))

#घोषणा dm_sector_भाग_up(n, sz) ( \
अणु \
	sector_t _r = ((n) + (sz) - 1); \
	sector_भाग(_r, (sz)); \
	_r; \
पूर्ण \
)

/*
 * उच्चमानing(n / size) * size
 */
#घोषणा dm_round_up(n, sz) (dm_भाग_up((n), (sz)) * (sz))

/*
 * Sector offset taken relative to the start of the target instead of
 * relative to the start of the device.
 */
#घोषणा dm_target_offset(ti, sector) ((sector) - (ti)->begin)

अटल अंतरभूत sector_t to_sector(अचिन्हित दीर्घ दीर्घ n)
अणु
	वापस (n >> SECTOR_SHIFT);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ to_bytes(sector_t n)
अणु
	वापस (n << SECTOR_SHIFT);
पूर्ण

#पूर्ण_अगर	/* _LINUX_DEVICE_MAPPER_H */
