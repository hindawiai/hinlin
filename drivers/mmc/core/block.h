<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MMC_CORE_BLOCK_H
#घोषणा _MMC_CORE_BLOCK_H

काष्ठा mmc_queue;
काष्ठा request;

व्योम mmc_blk_cqe_recovery(काष्ठा mmc_queue *mq);

क्रमागत mmc_issued;

क्रमागत mmc_issued mmc_blk_mq_issue_rq(काष्ठा mmc_queue *mq, काष्ठा request *req);
व्योम mmc_blk_mq_complete(काष्ठा request *req);
व्योम mmc_blk_mq_recovery(काष्ठा mmc_queue *mq);

काष्ठा work_काष्ठा;

व्योम mmc_blk_mq_complete_work(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर
