<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SCM_BLK_H
#घोषणा SCM_BLK_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/genhd.h>
#समावेश <linux/list.h>

#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/eadm.h>

#घोषणा SCM_NR_PARTS 8
#घोषणा SCM_QUEUE_DELAY 5

काष्ठा scm_blk_dev अणु
	काष्ठा request_queue *rq;
	काष्ठा gendisk *gendisk;
	काष्ठा blk_mq_tag_set tag_set;
	काष्ठा scm_device *scmdev;
	spinlock_t lock;
	atomic_t queued_reqs;
	क्रमागत अणुSCM_OPER, SCM_WR_PROHIBITपूर्ण state;
	काष्ठा list_head finished_requests;
पूर्ण;

काष्ठा scm_request अणु
	काष्ठा scm_blk_dev *bdev;
	काष्ठा aidaw *next_aidaw;
	काष्ठा request **request;
	काष्ठा aob *aob;
	काष्ठा list_head list;
	u8 retries;
	blk_status_t error;
पूर्ण;

#घोषणा to_aobrq(rq) container_of((व्योम *) rq, काष्ठा aob_rq_header, data)

पूर्णांक scm_blk_dev_setup(काष्ठा scm_blk_dev *, काष्ठा scm_device *);
व्योम scm_blk_dev_cleanup(काष्ठा scm_blk_dev *);
व्योम scm_blk_set_available(काष्ठा scm_blk_dev *);
व्योम scm_blk_irq(काष्ठा scm_device *, व्योम *, blk_status_t);

काष्ठा aidaw *scm_aidaw_fetch(काष्ठा scm_request *scmrq, अचिन्हित पूर्णांक bytes);

पूर्णांक scm_drv_init(व्योम);
व्योम scm_drv_cleanup(व्योम);

बाह्य debug_info_t *scm_debug;

#घोषणा SCM_LOG(imp, txt) करो अणु					\
		debug_text_event(scm_debug, imp, txt);		\
	पूर्ण जबतक (0)

अटल अंतरभूत व्योम SCM_LOG_HEX(पूर्णांक level, व्योम *data, पूर्णांक length)
अणु
	debug_event(scm_debug, level, data, length);
पूर्ण

अटल अंतरभूत व्योम SCM_LOG_STATE(पूर्णांक level, काष्ठा scm_device *scmdev)
अणु
	काष्ठा अणु
		u64 address;
		u8 oper_state;
		u8 rank;
	पूर्ण __packed data = अणु
		.address = scmdev->address,
		.oper_state = scmdev->attrs.oper_state,
		.rank = scmdev->attrs.rank,
	पूर्ण;

	SCM_LOG_HEX(level, &data, माप(data));
पूर्ण

#पूर्ण_अगर /* SCM_BLK_H */
