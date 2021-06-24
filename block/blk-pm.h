<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _BLOCK_BLK_PM_H_
#घोषणा _BLOCK_BLK_PM_H_

#समावेश <linux/pm_runसमय.स>

#अगर_घोषित CONFIG_PM
अटल अंतरभूत पूर्णांक blk_pm_resume_queue(स्थिर bool pm, काष्ठा request_queue *q)
अणु
	अगर (!q->dev || !blk_queue_pm_only(q))
		वापस 1;	/* Nothing to करो */
	अगर (pm && q->rpm_status != RPM_SUSPENDED)
		वापस 1;	/* Request allowed */
	pm_request_resume(q->dev);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम blk_pm_mark_last_busy(काष्ठा request *rq)
अणु
	अगर (rq->q->dev && !(rq->rq_flags & RQF_PM))
		pm_runसमय_mark_last_busy(rq->q->dev);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक blk_pm_resume_queue(स्थिर bool pm, काष्ठा request_queue *q)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम blk_pm_mark_last_busy(काष्ठा request *rq)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _BLOCK_BLK_PM_H_ */
