<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित INT_BLK_MQ_DEBUGFS_H
#घोषणा INT_BLK_MQ_DEBUGFS_H

#अगर_घोषित CONFIG_BLK_DEBUG_FS

#समावेश <linux/seq_file.h>

काष्ठा blk_mq_debugfs_attr अणु
	स्थिर अक्षर *name;
	umode_t mode;
	पूर्णांक (*show)(व्योम *, काष्ठा seq_file *);
	sमाप_प्रकार (*ग_लिखो)(व्योम *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
	/* Set either .show or .seq_ops. */
	स्थिर काष्ठा seq_operations *seq_ops;
पूर्ण;

पूर्णांक __blk_mq_debugfs_rq_show(काष्ठा seq_file *m, काष्ठा request *rq);
पूर्णांक blk_mq_debugfs_rq_show(काष्ठा seq_file *m, व्योम *v);

व्योम blk_mq_debugfs_रेजिस्टर(काष्ठा request_queue *q);
व्योम blk_mq_debugfs_unरेजिस्टर(काष्ठा request_queue *q);
व्योम blk_mq_debugfs_रेजिस्टर_hctx(काष्ठा request_queue *q,
				  काष्ठा blk_mq_hw_ctx *hctx);
व्योम blk_mq_debugfs_unरेजिस्टर_hctx(काष्ठा blk_mq_hw_ctx *hctx);
व्योम blk_mq_debugfs_रेजिस्टर_hctxs(काष्ठा request_queue *q);
व्योम blk_mq_debugfs_unरेजिस्टर_hctxs(काष्ठा request_queue *q);

व्योम blk_mq_debugfs_रेजिस्टर_sched(काष्ठा request_queue *q);
व्योम blk_mq_debugfs_unरेजिस्टर_sched(काष्ठा request_queue *q);
व्योम blk_mq_debugfs_रेजिस्टर_sched_hctx(काष्ठा request_queue *q,
				       काष्ठा blk_mq_hw_ctx *hctx);
व्योम blk_mq_debugfs_unरेजिस्टर_sched_hctx(काष्ठा blk_mq_hw_ctx *hctx);

व्योम blk_mq_debugfs_रेजिस्टर_rqos(काष्ठा rq_qos *rqos);
व्योम blk_mq_debugfs_unरेजिस्टर_rqos(काष्ठा rq_qos *rqos);
व्योम blk_mq_debugfs_unरेजिस्टर_queue_rqos(काष्ठा request_queue *q);
#अन्यथा
अटल अंतरभूत व्योम blk_mq_debugfs_रेजिस्टर(काष्ठा request_queue *q)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_unरेजिस्टर(काष्ठा request_queue *q)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_रेजिस्टर_hctx(काष्ठा request_queue *q,
						काष्ठा blk_mq_hw_ctx *hctx)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_unरेजिस्टर_hctx(काष्ठा blk_mq_hw_ctx *hctx)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_रेजिस्टर_hctxs(काष्ठा request_queue *q)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_unरेजिस्टर_hctxs(काष्ठा request_queue *q)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_रेजिस्टर_sched(काष्ठा request_queue *q)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_unरेजिस्टर_sched(काष्ठा request_queue *q)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_रेजिस्टर_sched_hctx(काष्ठा request_queue *q,
						      काष्ठा blk_mq_hw_ctx *hctx)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_unरेजिस्टर_sched_hctx(काष्ठा blk_mq_hw_ctx *hctx)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_रेजिस्टर_rqos(काष्ठा rq_qos *rqos)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_unरेजिस्टर_rqos(काष्ठा rq_qos *rqos)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_mq_debugfs_unरेजिस्टर_queue_rqos(काष्ठा request_queue *q)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_DEBUG_FS_ZONED
पूर्णांक queue_zone_wlock_show(व्योम *data, काष्ठा seq_file *m);
#अन्यथा
अटल अंतरभूत पूर्णांक queue_zone_wlock_show(व्योम *data, काष्ठा seq_file *m)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
