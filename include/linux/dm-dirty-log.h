<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software
 * Copyright (C) 2004-2008 Red Hat, Inc. All rights reserved.
 *
 * Device-Mapper dirty region log.
 *
 * This file is released under the LGPL.
 */

#अगर_अघोषित _LINUX_DM_सूचीTY_LOG
#घोषणा _LINUX_DM_सूचीTY_LOG

#अगर_घोषित __KERNEL__

#समावेश <linux/types.h>
#समावेश <linux/device-mapper.h>

प्रकार sector_t region_t;

काष्ठा dm_dirty_log_type;

काष्ठा dm_dirty_log अणु
	काष्ठा dm_dirty_log_type *type;
	पूर्णांक (*flush_callback_fn)(काष्ठा dm_target *ti);
	व्योम *context;
पूर्ण;

काष्ठा dm_dirty_log_type अणु
	स्थिर अक्षर *name;
	काष्ठा module *module;

	/* For पूर्णांकernal device-mapper use */
	काष्ठा list_head list;

	पूर्णांक (*ctr)(काष्ठा dm_dirty_log *log, काष्ठा dm_target *ti,
		   अचिन्हित argc, अक्षर **argv);
	व्योम (*dtr)(काष्ठा dm_dirty_log *log);

	/*
	 * There are बार when we करोn't want the log to touch
	 * the disk.
	 */
	पूर्णांक (*presuspend)(काष्ठा dm_dirty_log *log);
	पूर्णांक (*postsuspend)(काष्ठा dm_dirty_log *log);
	पूर्णांक (*resume)(काष्ठा dm_dirty_log *log);

	/*
	 * Retrieves the smallest size of region that the log can
	 * deal with.
	 */
	uपूर्णांक32_t (*get_region_size)(काष्ठा dm_dirty_log *log);

	/*
	 * A predicate to say whether a region is clean or not.
	 * May block.
	 */
	पूर्णांक (*is_clean)(काष्ठा dm_dirty_log *log, region_t region);

	/*
	 *  Returns: 0, 1, -EWOULDBLOCK, < 0
	 *
	 * A predicate function to check the area given by
	 * [sector, sector + len) is in sync.
	 *
	 * If -EWOULDBLOCK is वापसed the state of the region is
	 * unknown, typically this will result in a पढ़ो being
	 * passed to a daemon to deal with, since a daemon is
	 * allowed to block.
	 */
	पूर्णांक (*in_sync)(काष्ठा dm_dirty_log *log, region_t region,
		       पूर्णांक can_block);

	/*
	 * Flush the current log state (eg, to disk).  This
	 * function may block.
	 */
	पूर्णांक (*flush)(काष्ठा dm_dirty_log *log);

	/*
	 * Mark an area as clean or dirty.  These functions may
	 * block, though क्रम perक्रमmance reasons blocking should
	 * be extremely rare (eg, allocating another chunk of
	 * memory क्रम some reason).
	 */
	व्योम (*mark_region)(काष्ठा dm_dirty_log *log, region_t region);
	व्योम (*clear_region)(काष्ठा dm_dirty_log *log, region_t region);

	/*
	 * Returns: <0 (error), 0 (no region), 1 (region)
	 *
	 * The mirrord will need perक्रमm recovery on regions of
	 * the mirror that are in the NOSYNC state.  This
	 * function asks the log to tell the caller about the
	 * next region that this machine should recover.
	 *
	 * Do not confuse this function with 'in_sync()', one
	 * tells you अगर an area is synchronised, the other
	 * assigns recovery work.
	*/
	पूर्णांक (*get_resync_work)(काष्ठा dm_dirty_log *log, region_t *region);

	/*
	 * This notअगरies the log that the resync status of a region
	 * has changed.  It also clears the region from the recovering
	 * list (अगर present).
	 */
	व्योम (*set_region_sync)(काष्ठा dm_dirty_log *log,
				region_t region, पूर्णांक in_sync);

	/*
	 * Returns the number of regions that are in sync.
	 */
	region_t (*get_sync_count)(काष्ठा dm_dirty_log *log);

	/*
	 * Support function क्रम mirror status requests.
	 */
	पूर्णांक (*status)(काष्ठा dm_dirty_log *log, status_type_t status_type,
		      अक्षर *result, अचिन्हित maxlen);

	/*
	 * is_remote_recovering is necessary क्रम cluster mirroring. It provides
	 * a way to detect recovery on another node, so we aren't writing
	 * concurrently.  This function is likely to block (when a cluster log
	 * is used).
	 *
	 * Returns: 0, 1
	 */
	पूर्णांक (*is_remote_recovering)(काष्ठा dm_dirty_log *log, region_t region);
पूर्ण;

पूर्णांक dm_dirty_log_type_रेजिस्टर(काष्ठा dm_dirty_log_type *type);
पूर्णांक dm_dirty_log_type_unरेजिस्टर(काष्ठा dm_dirty_log_type *type);

/*
 * Make sure you use these two functions, rather than calling
 * type->स्थिरructor/deकाष्ठाor() directly.
 */
काष्ठा dm_dirty_log *dm_dirty_log_create(स्थिर अक्षर *type_name,
			काष्ठा dm_target *ti,
			पूर्णांक (*flush_callback_fn)(काष्ठा dm_target *ti),
			अचिन्हित argc, अक्षर **argv);
व्योम dm_dirty_log_destroy(काष्ठा dm_dirty_log *log);

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _LINUX_DM_सूचीTY_LOG_H */
