<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित MMC_QUEUE_H
#घोषणा MMC_QUEUE_H

#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/host.h>

क्रमागत mmc_issued अणु
	MMC_REQ_STARTED,
	MMC_REQ_BUSY,
	MMC_REQ_FAILED_TO_START,
	MMC_REQ_FINISHED,
पूर्ण;

क्रमागत mmc_issue_type अणु
	MMC_ISSUE_SYNC,
	MMC_ISSUE_DCMD,
	MMC_ISSUE_ASYNC,
	MMC_ISSUE_MAX,
पूर्ण;

अटल अंतरभूत काष्ठा mmc_queue_req *req_to_mmc_queue_req(काष्ठा request *rq)
अणु
	वापस blk_mq_rq_to_pdu(rq);
पूर्ण

काष्ठा mmc_queue_req;

अटल अंतरभूत काष्ठा request *mmc_queue_req_to_req(काष्ठा mmc_queue_req *mqr)
अणु
	वापस blk_mq_rq_from_pdu(mqr);
पूर्ण

काष्ठा mmc_blk_data;
काष्ठा mmc_blk_ioc_data;

काष्ठा mmc_blk_request अणु
	काष्ठा mmc_request	mrq;
	काष्ठा mmc_command	sbc;
	काष्ठा mmc_command	cmd;
	काष्ठा mmc_command	stop;
	काष्ठा mmc_data		data;
पूर्ण;

/**
 * क्रमागत mmc_drv_op - क्रमागतerates the operations in the mmc_queue_req
 * @MMC_DRV_OP_IOCTL: ioctl operation
 * @MMC_DRV_OP_IOCTL_RPMB: RPMB-oriented ioctl operation
 * @MMC_DRV_OP_BOOT_WP: ग_लिखो protect boot partitions
 * @MMC_DRV_OP_GET_CARD_STATUS: get card status
 * @MMC_DRV_OP_GET_EXT_CSD: get the EXT CSD from an eMMC card
 */
क्रमागत mmc_drv_op अणु
	MMC_DRV_OP_IOCTL,
	MMC_DRV_OP_IOCTL_RPMB,
	MMC_DRV_OP_BOOT_WP,
	MMC_DRV_OP_GET_CARD_STATUS,
	MMC_DRV_OP_GET_EXT_CSD,
पूर्ण;

काष्ठा mmc_queue_req अणु
	काष्ठा mmc_blk_request	brq;
	काष्ठा scatterlist	*sg;
	क्रमागत mmc_drv_op		drv_op;
	पूर्णांक			drv_op_result;
	व्योम			*drv_op_data;
	अचिन्हित पूर्णांक		ioc_count;
	पूर्णांक			retries;
पूर्ण;

काष्ठा mmc_queue अणु
	काष्ठा mmc_card		*card;
	काष्ठा mmc_ctx		ctx;
	काष्ठा blk_mq_tag_set	tag_set;
	काष्ठा mmc_blk_data	*blkdata;
	काष्ठा request_queue	*queue;
	spinlock_t		lock;
	पूर्णांक			in_flight[MMC_ISSUE_MAX];
	अचिन्हित पूर्णांक		cqe_busy;
#घोषणा MMC_CQE_DCMD_BUSY	BIT(0)
	bool			busy;
	bool			recovery_needed;
	bool			in_recovery;
	bool			rw_रुको;
	bool			रुकोing;
	काष्ठा work_काष्ठा	recovery_work;
	रुको_queue_head_t	रुको;
	काष्ठा request		*recovery_req;
	काष्ठा request		*complete_req;
	काष्ठा mutex		complete_lock;
	काष्ठा work_काष्ठा	complete_work;
पूर्ण;

बाह्य पूर्णांक mmc_init_queue(काष्ठा mmc_queue *, काष्ठा mmc_card *);
बाह्य व्योम mmc_cleanup_queue(काष्ठा mmc_queue *);
बाह्य व्योम mmc_queue_suspend(काष्ठा mmc_queue *);
बाह्य व्योम mmc_queue_resume(काष्ठा mmc_queue *);
बाह्य अचिन्हित पूर्णांक mmc_queue_map_sg(काष्ठा mmc_queue *,
				     काष्ठा mmc_queue_req *);

व्योम mmc_cqe_check_busy(काष्ठा mmc_queue *mq);
व्योम mmc_cqe_recovery_notअगरier(काष्ठा mmc_request *mrq);

क्रमागत mmc_issue_type mmc_issue_type(काष्ठा mmc_queue *mq, काष्ठा request *req);

अटल अंतरभूत पूर्णांक mmc_tot_in_flight(काष्ठा mmc_queue *mq)
अणु
	वापस mq->in_flight[MMC_ISSUE_SYNC] +
	       mq->in_flight[MMC_ISSUE_DCMD] +
	       mq->in_flight[MMC_ISSUE_ASYNC];
पूर्ण

अटल अंतरभूत पूर्णांक mmc_cqe_qcnt(काष्ठा mmc_queue *mq)
अणु
	वापस mq->in_flight[MMC_ISSUE_DCMD] +
	       mq->in_flight[MMC_ISSUE_ASYNC];
पूर्ण

#पूर्ण_अगर
