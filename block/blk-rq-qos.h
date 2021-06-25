<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित RQ_QOS_H
#घोषणा RQ_QOS_H

#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk_types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/रुको.h>

#समावेश "blk-mq-debugfs.h"

काष्ठा blk_mq_debugfs_attr;

क्रमागत rq_qos_id अणु
	RQ_QOS_WBT,
	RQ_QOS_LATENCY,
	RQ_QOS_COST,
पूर्ण;

काष्ठा rq_रुको अणु
	रुको_queue_head_t रुको;
	atomic_t inflight;
पूर्ण;

काष्ठा rq_qos अणु
	काष्ठा rq_qos_ops *ops;
	काष्ठा request_queue *q;
	क्रमागत rq_qos_id id;
	काष्ठा rq_qos *next;
#अगर_घोषित CONFIG_BLK_DEBUG_FS
	काष्ठा dentry *debugfs_dir;
#पूर्ण_अगर
पूर्ण;

काष्ठा rq_qos_ops अणु
	व्योम (*throttle)(काष्ठा rq_qos *, काष्ठा bio *);
	व्योम (*track)(काष्ठा rq_qos *, काष्ठा request *, काष्ठा bio *);
	व्योम (*merge)(काष्ठा rq_qos *, काष्ठा request *, काष्ठा bio *);
	व्योम (*issue)(काष्ठा rq_qos *, काष्ठा request *);
	व्योम (*requeue)(काष्ठा rq_qos *, काष्ठा request *);
	व्योम (*करोne)(काष्ठा rq_qos *, काष्ठा request *);
	व्योम (*करोne_bio)(काष्ठा rq_qos *, काष्ठा bio *);
	व्योम (*cleanup)(काष्ठा rq_qos *, काष्ठा bio *);
	व्योम (*queue_depth_changed)(काष्ठा rq_qos *);
	व्योम (*निकास)(काष्ठा rq_qos *);
	स्थिर काष्ठा blk_mq_debugfs_attr *debugfs_attrs;
पूर्ण;

काष्ठा rq_depth अणु
	अचिन्हित पूर्णांक max_depth;

	पूर्णांक scale_step;
	bool scaled_max;

	अचिन्हित पूर्णांक queue_depth;
	अचिन्हित पूर्णांक शेष_depth;
पूर्ण;

अटल अंतरभूत काष्ठा rq_qos *rq_qos_id(काष्ठा request_queue *q,
				       क्रमागत rq_qos_id id)
अणु
	काष्ठा rq_qos *rqos;
	क्रम (rqos = q->rq_qos; rqos; rqos = rqos->next) अणु
		अगर (rqos->id == id)
			अवरोध;
	पूर्ण
	वापस rqos;
पूर्ण

अटल अंतरभूत काष्ठा rq_qos *wbt_rq_qos(काष्ठा request_queue *q)
अणु
	वापस rq_qos_id(q, RQ_QOS_WBT);
पूर्ण

अटल अंतरभूत काष्ठा rq_qos *blkcg_rq_qos(काष्ठा request_queue *q)
अणु
	वापस rq_qos_id(q, RQ_QOS_LATENCY);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *rq_qos_id_to_name(क्रमागत rq_qos_id id)
अणु
	चयन (id) अणु
	हाल RQ_QOS_WBT:
		वापस "wbt";
	हाल RQ_QOS_LATENCY:
		वापस "latency";
	हाल RQ_QOS_COST:
		वापस "cost";
	पूर्ण
	वापस "unknown";
पूर्ण

अटल अंतरभूत व्योम rq_रुको_init(काष्ठा rq_रुको *rq_रुको)
अणु
	atomic_set(&rq_रुको->inflight, 0);
	init_रुकोqueue_head(&rq_रुको->रुको);
पूर्ण

अटल अंतरभूत व्योम rq_qos_add(काष्ठा request_queue *q, काष्ठा rq_qos *rqos)
अणु
	rqos->next = q->rq_qos;
	q->rq_qos = rqos;

	अगर (rqos->ops->debugfs_attrs)
		blk_mq_debugfs_रेजिस्टर_rqos(rqos);
पूर्ण

अटल अंतरभूत व्योम rq_qos_del(काष्ठा request_queue *q, काष्ठा rq_qos *rqos)
अणु
	काष्ठा rq_qos **cur;

	क्रम (cur = &q->rq_qos; *cur; cur = &(*cur)->next) अणु
		अगर (*cur == rqos) अणु
			*cur = rqos->next;
			अवरोध;
		पूर्ण
	पूर्ण

	blk_mq_debugfs_unरेजिस्टर_rqos(rqos);
पूर्ण

प्रकार bool (acquire_inflight_cb_t)(काष्ठा rq_रुको *rqw, व्योम *निजी_data);
प्रकार व्योम (cleanup_cb_t)(काष्ठा rq_रुको *rqw, व्योम *निजी_data);

व्योम rq_qos_रुको(काष्ठा rq_रुको *rqw, व्योम *निजी_data,
		 acquire_inflight_cb_t *acquire_inflight_cb,
		 cleanup_cb_t *cleanup_cb);
bool rq_रुको_inc_below(काष्ठा rq_रुको *rq_रुको, अचिन्हित पूर्णांक limit);
bool rq_depth_scale_up(काष्ठा rq_depth *rqd);
bool rq_depth_scale_करोwn(काष्ठा rq_depth *rqd, bool hard_throttle);
bool rq_depth_calc_max_depth(काष्ठा rq_depth *rqd);

व्योम __rq_qos_cleanup(काष्ठा rq_qos *rqos, काष्ठा bio *bio);
व्योम __rq_qos_करोne(काष्ठा rq_qos *rqos, काष्ठा request *rq);
व्योम __rq_qos_issue(काष्ठा rq_qos *rqos, काष्ठा request *rq);
व्योम __rq_qos_requeue(काष्ठा rq_qos *rqos, काष्ठा request *rq);
व्योम __rq_qos_throttle(काष्ठा rq_qos *rqos, काष्ठा bio *bio);
व्योम __rq_qos_track(काष्ठा rq_qos *rqos, काष्ठा request *rq, काष्ठा bio *bio);
व्योम __rq_qos_merge(काष्ठा rq_qos *rqos, काष्ठा request *rq, काष्ठा bio *bio);
व्योम __rq_qos_करोne_bio(काष्ठा rq_qos *rqos, काष्ठा bio *bio);
व्योम __rq_qos_queue_depth_changed(काष्ठा rq_qos *rqos);

अटल अंतरभूत व्योम rq_qos_cleanup(काष्ठा request_queue *q, काष्ठा bio *bio)
अणु
	अगर (q->rq_qos)
		__rq_qos_cleanup(q->rq_qos, bio);
पूर्ण

अटल अंतरभूत व्योम rq_qos_करोne(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	अगर (q->rq_qos)
		__rq_qos_करोne(q->rq_qos, rq);
पूर्ण

अटल अंतरभूत व्योम rq_qos_issue(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	अगर (q->rq_qos)
		__rq_qos_issue(q->rq_qos, rq);
पूर्ण

अटल अंतरभूत व्योम rq_qos_requeue(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	अगर (q->rq_qos)
		__rq_qos_requeue(q->rq_qos, rq);
पूर्ण

अटल अंतरभूत व्योम rq_qos_करोne_bio(काष्ठा request_queue *q, काष्ठा bio *bio)
अणु
	अगर (q->rq_qos)
		__rq_qos_करोne_bio(q->rq_qos, bio);
पूर्ण

अटल अंतरभूत व्योम rq_qos_throttle(काष्ठा request_queue *q, काष्ठा bio *bio)
अणु
	/*
	 * BIO_TRACKED lets controllers know that a bio went through the
	 * normal rq_qos path.
	 */
	bio_set_flag(bio, BIO_TRACKED);
	अगर (q->rq_qos)
		__rq_qos_throttle(q->rq_qos, bio);
पूर्ण

अटल अंतरभूत व्योम rq_qos_track(काष्ठा request_queue *q, काष्ठा request *rq,
				काष्ठा bio *bio)
अणु
	अगर (q->rq_qos)
		__rq_qos_track(q->rq_qos, rq, bio);
पूर्ण

अटल अंतरभूत व्योम rq_qos_merge(काष्ठा request_queue *q, काष्ठा request *rq,
				काष्ठा bio *bio)
अणु
	अगर (q->rq_qos)
		__rq_qos_merge(q->rq_qos, rq, bio);
पूर्ण

अटल अंतरभूत व्योम rq_qos_queue_depth_changed(काष्ठा request_queue *q)
अणु
	अगर (q->rq_qos)
		__rq_qos_queue_depth_changed(q->rq_qos);
पूर्ण

व्योम rq_qos_निकास(काष्ठा request_queue *);

#पूर्ण_अगर
