<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ELEVATOR_H
#घोषणा _LINUX_ELEVATOR_H

#समावेश <linux/percpu.h>
#समावेश <linux/hashtable.h>

#अगर_घोषित CONFIG_BLOCK

काष्ठा io_cq;
काष्ठा elevator_type;
#अगर_घोषित CONFIG_BLK_DEBUG_FS
काष्ठा blk_mq_debugfs_attr;
#पूर्ण_अगर

/*
 * Return values from elevator merger
 */
क्रमागत elv_merge अणु
	ELEVATOR_NO_MERGE	= 0,
	ELEVATOR_FRONT_MERGE	= 1,
	ELEVATOR_BACK_MERGE	= 2,
	ELEVATOR_DISCARD_MERGE	= 3,
पूर्ण;

काष्ठा blk_mq_alloc_data;
काष्ठा blk_mq_hw_ctx;

काष्ठा elevator_mq_ops अणु
	पूर्णांक (*init_sched)(काष्ठा request_queue *, काष्ठा elevator_type *);
	व्योम (*निकास_sched)(काष्ठा elevator_queue *);
	पूर्णांक (*init_hctx)(काष्ठा blk_mq_hw_ctx *, अचिन्हित पूर्णांक);
	व्योम (*निकास_hctx)(काष्ठा blk_mq_hw_ctx *, अचिन्हित पूर्णांक);
	व्योम (*depth_updated)(काष्ठा blk_mq_hw_ctx *);

	bool (*allow_merge)(काष्ठा request_queue *, काष्ठा request *, काष्ठा bio *);
	bool (*bio_merge)(काष्ठा request_queue *, काष्ठा bio *, अचिन्हित पूर्णांक);
	पूर्णांक (*request_merge)(काष्ठा request_queue *q, काष्ठा request **, काष्ठा bio *);
	व्योम (*request_merged)(काष्ठा request_queue *, काष्ठा request *, क्रमागत elv_merge);
	व्योम (*requests_merged)(काष्ठा request_queue *, काष्ठा request *, काष्ठा request *);
	व्योम (*limit_depth)(अचिन्हित पूर्णांक, काष्ठा blk_mq_alloc_data *);
	व्योम (*prepare_request)(काष्ठा request *);
	व्योम (*finish_request)(काष्ठा request *);
	व्योम (*insert_requests)(काष्ठा blk_mq_hw_ctx *, काष्ठा list_head *, bool);
	काष्ठा request *(*dispatch_request)(काष्ठा blk_mq_hw_ctx *);
	bool (*has_work)(काष्ठा blk_mq_hw_ctx *);
	व्योम (*completed_request)(काष्ठा request *, u64);
	व्योम (*requeue_request)(काष्ठा request *);
	काष्ठा request *(*क्रमmer_request)(काष्ठा request_queue *, काष्ठा request *);
	काष्ठा request *(*next_request)(काष्ठा request_queue *, काष्ठा request *);
	व्योम (*init_icq)(काष्ठा io_cq *);
	व्योम (*निकास_icq)(काष्ठा io_cq *);
पूर्ण;

#घोषणा ELV_NAME_MAX	(16)

काष्ठा elv_fs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा elevator_queue *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा elevator_queue *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

/*
 * identअगरies an elevator type, such as AS or deadline
 */
काष्ठा elevator_type
अणु
	/* managed by elevator core */
	काष्ठा kmem_cache *icq_cache;

	/* fields provided by elevator implementation */
	काष्ठा elevator_mq_ops ops;

	माप_प्रकार icq_size;	/* see iocontext.h */
	माप_प्रकार icq_align;	/* ditto */
	काष्ठा elv_fs_entry *elevator_attrs;
	स्थिर अक्षर *elevator_name;
	स्थिर अक्षर *elevator_alias;
	स्थिर अचिन्हित पूर्णांक elevator_features;
	काष्ठा module *elevator_owner;
#अगर_घोषित CONFIG_BLK_DEBUG_FS
	स्थिर काष्ठा blk_mq_debugfs_attr *queue_debugfs_attrs;
	स्थिर काष्ठा blk_mq_debugfs_attr *hctx_debugfs_attrs;
#पूर्ण_अगर

	/* managed by elevator core */
	अक्षर icq_cache_name[ELV_NAME_MAX + 6];	/* elvname + "_io_cq" */
	काष्ठा list_head list;
पूर्ण;

#घोषणा ELV_HASH_BITS 6

व्योम elv_rqhash_del(काष्ठा request_queue *q, काष्ठा request *rq);
व्योम elv_rqhash_add(काष्ठा request_queue *q, काष्ठा request *rq);
व्योम elv_rqhash_reposition(काष्ठा request_queue *q, काष्ठा request *rq);
काष्ठा request *elv_rqhash_find(काष्ठा request_queue *q, sector_t offset);

/*
 * each queue has an elevator_queue associated with it
 */
काष्ठा elevator_queue
अणु
	काष्ठा elevator_type *type;
	व्योम *elevator_data;
	काष्ठा kobject kobj;
	काष्ठा mutex sysfs_lock;
	अचिन्हित पूर्णांक रेजिस्टरed:1;
	DECLARE_HASHTABLE(hash, ELV_HASH_BITS);
पूर्ण;

/*
 * block elevator पूर्णांकerface
 */
बाह्य क्रमागत elv_merge elv_merge(काष्ठा request_queue *, काष्ठा request **,
		काष्ठा bio *);
बाह्य व्योम elv_merge_requests(काष्ठा request_queue *, काष्ठा request *,
			       काष्ठा request *);
बाह्य व्योम elv_merged_request(काष्ठा request_queue *, काष्ठा request *,
		क्रमागत elv_merge);
बाह्य bool elv_attempt_insert_merge(काष्ठा request_queue *, काष्ठा request *);
बाह्य काष्ठा request *elv_क्रमmer_request(काष्ठा request_queue *, काष्ठा request *);
बाह्य काष्ठा request *elv_latter_request(काष्ठा request_queue *, काष्ठा request *);

/*
 * io scheduler registration
 */
बाह्य पूर्णांक elv_रेजिस्टर(काष्ठा elevator_type *);
बाह्य व्योम elv_unरेजिस्टर(काष्ठा elevator_type *);

/*
 * io scheduler sysfs चयनing
 */
बाह्य sमाप_प्रकार elv_iosched_show(काष्ठा request_queue *, अक्षर *);
बाह्य sमाप_प्रकार elv_iosched_store(काष्ठा request_queue *, स्थिर अक्षर *, माप_प्रकार);

बाह्य bool elv_bio_merge_ok(काष्ठा request *, काष्ठा bio *);
बाह्य काष्ठा elevator_queue *elevator_alloc(काष्ठा request_queue *,
					काष्ठा elevator_type *);

/*
 * Helper functions.
 */
बाह्य काष्ठा request *elv_rb_क्रमmer_request(काष्ठा request_queue *, काष्ठा request *);
बाह्य काष्ठा request *elv_rb_latter_request(काष्ठा request_queue *, काष्ठा request *);

/*
 * rb support functions.
 */
बाह्य व्योम elv_rb_add(काष्ठा rb_root *, काष्ठा request *);
बाह्य व्योम elv_rb_del(काष्ठा rb_root *, काष्ठा request *);
बाह्य काष्ठा request *elv_rb_find(काष्ठा rb_root *, sector_t);

/*
 * Insertion selection
 */
#घोषणा ELEVATOR_INSERT_FRONT	1
#घोषणा ELEVATOR_INSERT_BACK	2
#घोषणा ELEVATOR_INSERT_SORT	3
#घोषणा ELEVATOR_INSERT_REQUEUE	4
#घोषणा ELEVATOR_INSERT_FLUSH	5
#घोषणा ELEVATOR_INSERT_SORT_MERGE	6

#घोषणा rq_end_sector(rq)	(blk_rq_pos(rq) + blk_rq_sectors(rq))
#घोषणा rb_entry_rq(node)	rb_entry((node), काष्ठा request, rb_node)

#घोषणा rq_entry_fअगरo(ptr)	list_entry((ptr), काष्ठा request, queuelist)
#घोषणा rq_fअगरo_clear(rq)	list_del_init(&(rq)->queuelist)

/*
 * Elevator features.
 */

/* Supports zoned block devices sequential ग_लिखो स्थिरraपूर्णांक */
#घोषणा ELEVATOR_F_ZBD_SEQ_WRITE	(1U << 0)
/* Supports scheduling on multiple hardware queues */
#घोषणा ELEVATOR_F_MQ_AWARE		(1U << 1)

#पूर्ण_अगर /* CONFIG_BLOCK */
#पूर्ण_अगर
