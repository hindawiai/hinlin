<शैली गुरु>
/*
 * Internal header file _only_ क्रम device mapper core
 *
 * Copyright (C) 2016 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the LGPL.
 */

#अगर_अघोषित DM_CORE_INTERNAL_H
#घोषणा DM_CORE_INTERNAL_H

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/genhd.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/keyslot-manager.h>

#समावेश <trace/events/block.h>

#समावेश "dm.h"

#घोषणा DM_RESERVED_MAX_IOS		1024

काष्ठा dm_kobject_holder अणु
	काष्ठा kobject kobj;
	काष्ठा completion completion;
पूर्ण;

/*
 * DM core पूर्णांकernal काष्ठाures used directly by dm.c, dm-rq.c and dm-table.c.
 * DM tarमाला_लो must _not_ deference a mapped_device or dm_table to directly
 * access their members!
 */

काष्ठा mapped_device अणु
	काष्ठा mutex suspend_lock;

	काष्ठा mutex table_devices_lock;
	काष्ठा list_head table_devices;

	/*
	 * The current mapping (काष्ठा dm_table *).
	 * Use dm_get_live_tableअणु_fastपूर्ण or take suspend_lock क्रम
	 * dereference.
	 */
	व्योम __rcu *map;

	अचिन्हित दीर्घ flags;

	/* Protect queue and type against concurrent access. */
	काष्ठा mutex type_lock;
	क्रमागत dm_queue_mode type;

	पूर्णांक numa_node_id;
	काष्ठा request_queue *queue;

	atomic_t holders;
	atomic_t खोलो_count;

	काष्ठा dm_target *immutable_target;
	काष्ठा target_type *immutable_target_type;

	अक्षर name[16];
	काष्ठा gendisk *disk;
	काष्ठा dax_device *dax_dev;

	/*
	 * A list of ios that arrived जबतक we were suspended.
	 */
	काष्ठा work_काष्ठा work;
	रुको_queue_head_t रुको;
	spinlock_t deferred_lock;
	काष्ठा bio_list deferred;

	व्योम *पूर्णांकerface_ptr;

	/*
	 * Event handling.
	 */
	रुको_queue_head_t eventq;
	atomic_t event_nr;
	atomic_t uevent_seq;
	काष्ठा list_head uevent_list;
	spinlock_t uevent_lock; /* Protect access to uevent_list */

	/* the number of पूर्णांकernal suspends */
	अचिन्हित पूर्णांकernal_suspend_count;

	/*
	 * io objects are allocated from here.
	 */
	काष्ठा bio_set io_bs;
	काष्ठा bio_set bs;

	/*
	 * Processing queue (flush)
	 */
	काष्ठा workqueue_काष्ठा *wq;

	/* क्रमced geometry settings */
	काष्ठा hd_geometry geometry;

	/* kobject and completion */
	काष्ठा dm_kobject_holder kobj_holder;

	पूर्णांक swap_bios;
	काष्ठा semaphore swap_bios_semaphore;
	काष्ठा mutex swap_bios_lock;

	काष्ठा dm_stats stats;

	/* क्रम blk-mq request-based DM support */
	काष्ठा blk_mq_tag_set *tag_set;
	bool init_tio_pdu:1;

	काष्ठा srcu_काष्ठा io_barrier;
पूर्ण;

व्योम disable_discard(काष्ठा mapped_device *md);
व्योम disable_ग_लिखो_same(काष्ठा mapped_device *md);
व्योम disable_ग_लिखो_zeroes(काष्ठा mapped_device *md);

अटल अंतरभूत sector_t dm_get_size(काष्ठा mapped_device *md)
अणु
	वापस get_capacity(md->disk);
पूर्ण

अटल अंतरभूत काष्ठा dm_stats *dm_get_stats(काष्ठा mapped_device *md)
अणु
	वापस &md->stats;
पूर्ण

#घोषणा DM_TABLE_MAX_DEPTH 16

काष्ठा dm_table अणु
	काष्ठा mapped_device *md;
	क्रमागत dm_queue_mode type;

	/* btree table */
	अचिन्हित पूर्णांक depth;
	अचिन्हित पूर्णांक counts[DM_TABLE_MAX_DEPTH]; /* in nodes */
	sector_t *index[DM_TABLE_MAX_DEPTH];

	अचिन्हित पूर्णांक num_tarमाला_लो;
	अचिन्हित पूर्णांक num_allocated;
	sector_t *highs;
	काष्ठा dm_target *tarमाला_लो;

	काष्ठा target_type *immutable_target_type;

	bool पूर्णांकegrity_supported:1;
	bool singleton:1;
	अचिन्हित पूर्णांकegrity_added:1;

	/*
	 * Indicates the rw permissions क्रम the new logical
	 * device.  This should be a combination of FMODE_READ
	 * and FMODE_WRITE.
	 */
	भ_शेषe_t mode;

	/* a list of devices used by this table */
	काष्ठा list_head devices;

	/* events get handed up using this callback */
	व्योम (*event_fn)(व्योम *);
	व्योम *event_context;

	काष्ठा dm_md_mempools *mempools;

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION
	काष्ठा blk_keyslot_manager *ksm;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा completion *dm_get_completion_from_kobject(काष्ठा kobject *kobj)
अणु
	वापस &container_of(kobj, काष्ठा dm_kobject_holder, kobj)->completion;
पूर्ण

अचिन्हित __dm_get_module_param(अचिन्हित *module_param, अचिन्हित def, अचिन्हित max);

अटल अंतरभूत bool dm_message_test_buffer_overflow(अक्षर *result, अचिन्हित maxlen)
अणु
	वापस !maxlen || म_माप(result) + 1 >= maxlen;
पूर्ण

बाह्य atomic_t dm_global_event_nr;
बाह्य रुको_queue_head_t dm_global_eventq;
व्योम dm_issue_global_event(व्योम);

#पूर्ण_अगर
