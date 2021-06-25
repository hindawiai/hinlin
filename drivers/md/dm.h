<शैली गुरु>
/*
 * Internal header file क्रम device mapper
 *
 * Copyright (C) 2001, 2002 Sistina Software
 * Copyright (C) 2004-2006 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the LGPL.
 */

#अगर_अघोषित DM_INTERNAL_H
#घोषणा DM_INTERNAL_H

#समावेश <linux/fs.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/completion.h>
#समावेश <linux/kobject.h>
#समावेश <linux/refcount.h>

#समावेश "dm-stats.h"

/*
 * Suspend feature flags
 */
#घोषणा DM_SUSPEND_LOCKFS_FLAG		(1 << 0)
#घोषणा DM_SUSPEND_NOFLUSH_FLAG		(1 << 1)

/*
 * Status feature flags
 */
#घोषणा DM_STATUS_NOFLUSH_FLAG		(1 << 0)

/*
 * List of devices that a metadevice uses and should खोलो/बंद.
 */
काष्ठा dm_dev_पूर्णांकernal अणु
	काष्ठा list_head list;
	refcount_t count;
	काष्ठा dm_dev *dm_dev;
पूर्ण;

काष्ठा dm_table;
काष्ठा dm_md_mempools;

/*-----------------------------------------------------------------
 * Internal table functions.
 *---------------------------------------------------------------*/
व्योम dm_table_event_callback(काष्ठा dm_table *t,
			     व्योम (*fn)(व्योम *), व्योम *context);
काष्ठा dm_target *dm_table_get_target(काष्ठा dm_table *t, अचिन्हित पूर्णांक index);
काष्ठा dm_target *dm_table_find_target(काष्ठा dm_table *t, sector_t sector);
bool dm_table_has_no_data_devices(काष्ठा dm_table *table);
पूर्णांक dm_calculate_queue_limits(काष्ठा dm_table *table,
			      काष्ठा queue_limits *limits);
व्योम dm_table_set_restrictions(काष्ठा dm_table *t, काष्ठा request_queue *q,
			       काष्ठा queue_limits *limits);
काष्ठा list_head *dm_table_get_devices(काष्ठा dm_table *t);
व्योम dm_table_presuspend_tarमाला_लो(काष्ठा dm_table *t);
व्योम dm_table_presuspend_unकरो_tarमाला_लो(काष्ठा dm_table *t);
व्योम dm_table_postsuspend_tarमाला_लो(काष्ठा dm_table *t);
पूर्णांक dm_table_resume_tarमाला_लो(काष्ठा dm_table *t);
क्रमागत dm_queue_mode dm_table_get_type(काष्ठा dm_table *t);
काष्ठा target_type *dm_table_get_immutable_target_type(काष्ठा dm_table *t);
काष्ठा dm_target *dm_table_get_immutable_target(काष्ठा dm_table *t);
काष्ठा dm_target *dm_table_get_wildcard_target(काष्ठा dm_table *t);
bool dm_table_bio_based(काष्ठा dm_table *t);
bool dm_table_request_based(काष्ठा dm_table *t);
व्योम dm_table_मुक्त_md_mempools(काष्ठा dm_table *t);
काष्ठा dm_md_mempools *dm_table_get_md_mempools(काष्ठा dm_table *t);
bool dm_table_supports_dax(काष्ठा dm_table *t, iterate_devices_callout_fn fn,
			   पूर्णांक *blocksize);
पूर्णांक device_not_dax_capable(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
			   sector_t start, sector_t len, व्योम *data);

व्योम dm_lock_md_type(काष्ठा mapped_device *md);
व्योम dm_unlock_md_type(काष्ठा mapped_device *md);
व्योम dm_set_md_type(काष्ठा mapped_device *md, क्रमागत dm_queue_mode type);
क्रमागत dm_queue_mode dm_get_md_type(काष्ठा mapped_device *md);
काष्ठा target_type *dm_get_immutable_target_type(काष्ठा mapped_device *md);

पूर्णांक dm_setup_md_queue(काष्ठा mapped_device *md, काष्ठा dm_table *t);

/*
 * To check whether the target type is bio-based or not (request-based).
 */
#घोषणा dm_target_bio_based(t) ((t)->type->map != शून्य)

/*
 * To check whether the target type is request-based or not (bio-based).
 */
#घोषणा dm_target_request_based(t) ((t)->type->clone_and_map_rq != शून्य)

/*
 * To check whether the target type is a hybrid (capable of being
 * either request-based or bio-based).
 */
#घोषणा dm_target_hybrid(t) (dm_target_bio_based(t) && dm_target_request_based(t))

/*-----------------------------------------------------------------
 * A registry of target types.
 *---------------------------------------------------------------*/
पूर्णांक dm_target_init(व्योम);
व्योम dm_target_निकास(व्योम);
काष्ठा target_type *dm_get_target_type(स्थिर अक्षर *name);
व्योम dm_put_target_type(काष्ठा target_type *tt);
पूर्णांक dm_target_iterate(व्योम (*iter_func)(काष्ठा target_type *tt,
					व्योम *param), व्योम *param);

पूर्णांक dm_split_args(पूर्णांक *argc, अक्षर ***argvp, अक्षर *input);

/*
 * Is this mapped_device being deleted?
 */
पूर्णांक dm_deleting_md(काष्ठा mapped_device *md);

/*
 * Is this mapped_device suspended?
 */
पूर्णांक dm_suspended_md(काष्ठा mapped_device *md);

/*
 * Internal suspend and resume methods.
 */
पूर्णांक dm_suspended_पूर्णांकernally_md(काष्ठा mapped_device *md);
व्योम dm_पूर्णांकernal_suspend_fast(काष्ठा mapped_device *md);
व्योम dm_पूर्णांकernal_resume_fast(काष्ठा mapped_device *md);
व्योम dm_पूर्णांकernal_suspend_noflush(काष्ठा mapped_device *md);
व्योम dm_पूर्णांकernal_resume(काष्ठा mapped_device *md);

/*
 * Test अगर the device is scheduled क्रम deferred हटाओ.
 */
पूर्णांक dm_test_deferred_हटाओ_flag(काष्ठा mapped_device *md);

/*
 * Try to हटाओ devices marked क्रम deferred removal.
 */
व्योम dm_deferred_हटाओ(व्योम);

/*
 * The device-mapper can be driven through one of two पूर्णांकerfaces;
 * ioctl or fileप्रणाली, depending which patch you have applied.
 */
पूर्णांक dm_पूर्णांकerface_init(व्योम);
व्योम dm_पूर्णांकerface_निकास(व्योम);

/*
 * sysfs पूर्णांकerface
 */
पूर्णांक dm_sysfs_init(काष्ठा mapped_device *md);
व्योम dm_sysfs_निकास(काष्ठा mapped_device *md);
काष्ठा kobject *dm_kobject(काष्ठा mapped_device *md);
काष्ठा mapped_device *dm_get_from_kobject(काष्ठा kobject *kobj);

/*
 * The kobject helper
 */
व्योम dm_kobject_release(काष्ठा kobject *kobj);

/*
 * Tarमाला_लो क्रम linear and striped mappings
 */
पूर्णांक dm_linear_init(व्योम);
व्योम dm_linear_निकास(व्योम);

पूर्णांक dm_stripe_init(व्योम);
व्योम dm_stripe_निकास(व्योम);

/*
 * mapped_device operations
 */
व्योम dm_destroy(काष्ठा mapped_device *md);
व्योम dm_destroy_immediate(काष्ठा mapped_device *md);
पूर्णांक dm_खोलो_count(काष्ठा mapped_device *md);
पूर्णांक dm_lock_क्रम_deletion(काष्ठा mapped_device *md, bool mark_deferred, bool only_deferred);
पूर्णांक dm_cancel_deferred_हटाओ(काष्ठा mapped_device *md);
पूर्णांक dm_request_based(काष्ठा mapped_device *md);
पूर्णांक dm_get_table_device(काष्ठा mapped_device *md, dev_t dev, भ_शेषe_t mode,
			काष्ठा dm_dev **result);
व्योम dm_put_table_device(काष्ठा mapped_device *md, काष्ठा dm_dev *d);

पूर्णांक dm_kobject_uevent(काष्ठा mapped_device *md, क्रमागत kobject_action action,
		      अचिन्हित cookie);

व्योम dm_पूर्णांकernal_suspend(काष्ठा mapped_device *md);
व्योम dm_पूर्णांकernal_resume(काष्ठा mapped_device *md);

पूर्णांक dm_io_init(व्योम);
व्योम dm_io_निकास(व्योम);

पूर्णांक dm_kcopyd_init(व्योम);
व्योम dm_kcopyd_निकास(व्योम);

/*
 * Mempool operations
 */
काष्ठा dm_md_mempools *dm_alloc_md_mempools(काष्ठा mapped_device *md, क्रमागत dm_queue_mode type,
					    अचिन्हित पूर्णांकegrity, अचिन्हित per_bio_data_size,
					    अचिन्हित min_pool_size);
व्योम dm_मुक्त_md_mempools(काष्ठा dm_md_mempools *pools);

/*
 * Various helpers
 */
अचिन्हित dm_get_reserved_bio_based_ios(व्योम);

#पूर्ण_अगर
