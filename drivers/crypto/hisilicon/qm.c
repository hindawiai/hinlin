<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 HiSilicon Limited. */
#समावेश <यंत्र/page.h>
#समावेश <linux/acpi.h>
#समावेश <linux/aer.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/idr.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqवापस.h>
#समावेश <linux/log2.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/uacce.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/misc/uacce/hisi_qm.h>
#समावेश "qm.h"

/* eq/aeq irq enable */
#घोषणा QM_VF_AEQ_INT_SOURCE		0x0
#घोषणा QM_VF_AEQ_INT_MASK		0x4
#घोषणा QM_VF_EQ_INT_SOURCE		0x8
#घोषणा QM_VF_EQ_INT_MASK		0xc
#घोषणा QM_IRQ_NUM_V1			1
#घोषणा QM_IRQ_NUM_PF_V2		4
#घोषणा QM_IRQ_NUM_VF_V2		2

#घोषणा QM_EQ_EVENT_IRQ_VECTOR		0
#घोषणा QM_AEQ_EVENT_IRQ_VECTOR		1
#घोषणा QM_ABNORMAL_EVENT_IRQ_VECTOR	3

/* mailbox */
#घोषणा QM_MB_CMD_SQC			0x0
#घोषणा QM_MB_CMD_CQC			0x1
#घोषणा QM_MB_CMD_EQC			0x2
#घोषणा QM_MB_CMD_AEQC			0x3
#घोषणा QM_MB_CMD_SQC_BT		0x4
#घोषणा QM_MB_CMD_CQC_BT		0x5
#घोषणा QM_MB_CMD_SQC_VFT_V2		0x6
#घोषणा QM_MB_CMD_STOP_QP		0x8

#घोषणा QM_MB_CMD_SEND_BASE		0x300
#घोषणा QM_MB_EVENT_SHIFT		8
#घोषणा QM_MB_BUSY_SHIFT		13
#घोषणा QM_MB_OP_SHIFT			14
#घोषणा QM_MB_CMD_DATA_ADDR_L		0x304
#घोषणा QM_MB_CMD_DATA_ADDR_H		0x308

/* sqc shअगरt */
#घोषणा QM_SQ_HOP_NUM_SHIFT		0
#घोषणा QM_SQ_PAGE_SIZE_SHIFT		4
#घोषणा QM_SQ_BUF_SIZE_SHIFT		8
#घोषणा QM_SQ_SQE_SIZE_SHIFT		12
#घोषणा QM_SQ_PRIORITY_SHIFT		0
#घोषणा QM_SQ_ORDERS_SHIFT		4
#घोषणा QM_SQ_TYPE_SHIFT		8
#घोषणा QM_QC_PASID_ENABLE		0x1
#घोषणा QM_QC_PASID_ENABLE_SHIFT	7

#घोषणा QM_SQ_TYPE_MASK			GENMASK(3, 0)
#घोषणा QM_SQ_TAIL_IDX(sqc)		((le16_to_cpu((sqc)->w11) >> 6) & 0x1)

/* cqc shअगरt */
#घोषणा QM_CQ_HOP_NUM_SHIFT		0
#घोषणा QM_CQ_PAGE_SIZE_SHIFT		4
#घोषणा QM_CQ_BUF_SIZE_SHIFT		8
#घोषणा QM_CQ_CQE_SIZE_SHIFT		12
#घोषणा QM_CQ_PHASE_SHIFT		0
#घोषणा QM_CQ_FLAG_SHIFT		1

#घोषणा QM_CQE_PHASE(cqe)		(le16_to_cpu((cqe)->w7) & 0x1)
#घोषणा QM_QC_CQE_SIZE			4
#घोषणा QM_CQ_TAIL_IDX(cqc)		((le16_to_cpu((cqc)->w11) >> 6) & 0x1)

/* eqc shअगरt */
#घोषणा QM_EQE_AEQE_SIZE		(2UL << 12)
#घोषणा QM_EQC_PHASE_SHIFT		16

#घोषणा QM_EQE_PHASE(eqe)		((le32_to_cpu((eqe)->dw0) >> 16) & 0x1)
#घोषणा QM_EQE_CQN_MASK			GENMASK(15, 0)

#घोषणा QM_AEQE_PHASE(aeqe)		((le32_to_cpu((aeqe)->dw0) >> 16) & 0x1)
#घोषणा QM_AEQE_TYPE_SHIFT		17

#घोषणा QM_DOORBELL_CMD_SQ		0
#घोषणा QM_DOORBELL_CMD_CQ		1
#घोषणा QM_DOORBELL_CMD_EQ		2
#घोषणा QM_DOORBELL_CMD_AEQ		3

#घोषणा QM_DOORBELL_BASE_V1		0x340
#घोषणा QM_DB_CMD_SHIFT_V1		16
#घोषणा QM_DB_INDEX_SHIFT_V1		32
#घोषणा QM_DB_PRIORITY_SHIFT_V1		48
#घोषणा QM_DOORBELL_SQ_CQ_BASE_V2	0x1000
#घोषणा QM_DOORBELL_EQ_AEQ_BASE_V2	0x2000
#घोषणा QM_QUE_ISO_CFG_V		0x0030
#घोषणा QM_QUE_ISO_EN			0x100154
#घोषणा QM_CAPBILITY			0x100158
#घोषणा QM_QP_NUN_MASK			GENMASK(10, 0)
#घोषणा QM_QP_DB_INTERVAL		0x10000
#घोषणा QM_QP_MAX_NUM_SHIFT		11
#घोषणा QM_DB_CMD_SHIFT_V2		12
#घोषणा QM_DB_RAND_SHIFT_V2		16
#घोषणा QM_DB_INDEX_SHIFT_V2		32
#घोषणा QM_DB_PRIORITY_SHIFT_V2		48

#घोषणा QM_MEM_START_INIT		0x100040
#घोषणा QM_MEM_INIT_DONE		0x100044
#घोषणा QM_VFT_CFG_RDY			0x10006c
#घोषणा QM_VFT_CFG_OP_WR		0x100058
#घोषणा QM_VFT_CFG_TYPE			0x10005c
#घोषणा QM_SQC_VFT			0x0
#घोषणा QM_CQC_VFT			0x1
#घोषणा QM_VFT_CFG			0x100060
#घोषणा QM_VFT_CFG_OP_ENABLE		0x100054

#घोषणा QM_VFT_CFG_DATA_L		0x100064
#घोषणा QM_VFT_CFG_DATA_H		0x100068
#घोषणा QM_SQC_VFT_BUF_SIZE		(7ULL << 8)
#घोषणा QM_SQC_VFT_SQC_SIZE		(5ULL << 12)
#घोषणा QM_SQC_VFT_INDEX_NUMBER		(1ULL << 16)
#घोषणा QM_SQC_VFT_START_SQN_SHIFT	28
#घोषणा QM_SQC_VFT_VALID		(1ULL << 44)
#घोषणा QM_SQC_VFT_SQN_SHIFT		45
#घोषणा QM_CQC_VFT_BUF_SIZE		(7ULL << 8)
#घोषणा QM_CQC_VFT_SQC_SIZE		(5ULL << 12)
#घोषणा QM_CQC_VFT_INDEX_NUMBER		(1ULL << 16)
#घोषणा QM_CQC_VFT_VALID		(1ULL << 28)

#घोषणा QM_SQC_VFT_BASE_SHIFT_V2	28
#घोषणा QM_SQC_VFT_BASE_MASK_V2		GENMASK(15, 0)
#घोषणा QM_SQC_VFT_NUM_SHIFT_V2		45
#घोषणा QM_SQC_VFT_NUM_MASK_v2		GENMASK(9, 0)

#घोषणा QM_DFX_CNT_CLR_CE		0x100118

#घोषणा QM_ABNORMAL_INT_SOURCE		0x100000
#घोषणा QM_ABNORMAL_INT_SOURCE_CLR	GENMASK(14, 0)
#घोषणा QM_ABNORMAL_INT_MASK		0x100004
#घोषणा QM_ABNORMAL_INT_MASK_VALUE	0x7fff
#घोषणा QM_ABNORMAL_INT_STATUS		0x100008
#घोषणा QM_ABNORMAL_INT_SET		0x10000c
#घोषणा QM_ABNORMAL_INF00		0x100010
#घोषणा QM_FIFO_OVERFLOW_TYPE		0xc0
#घोषणा QM_FIFO_OVERFLOW_TYPE_SHIFT	6
#घोषणा QM_FIFO_OVERFLOW_VF		0x3f
#घोषणा QM_ABNORMAL_INF01		0x100014
#घोषणा QM_DB_TIMEOUT_TYPE		0xc0
#घोषणा QM_DB_TIMEOUT_TYPE_SHIFT	6
#घोषणा QM_DB_TIMEOUT_VF		0x3f
#घोषणा QM_RAS_CE_ENABLE		0x1000ec
#घोषणा QM_RAS_FE_ENABLE		0x1000f0
#घोषणा QM_RAS_NFE_ENABLE		0x1000f4
#घोषणा QM_RAS_CE_THRESHOLD		0x1000f8
#घोषणा QM_RAS_CE_TIMES_PER_IRQ		1
#घोषणा QM_RAS_MSI_INT_SEL		0x1040f4

#घोषणा QM_RESET_WAIT_TIMEOUT		400
#घोषणा QM_PEH_VENDOR_ID		0x1000d8
#घोषणा ACC_VENDOR_ID_VALUE		0x5a5a
#घोषणा QM_PEH_DFX_INFO0		0x1000fc
#घोषणा ACC_PEH_SRIOV_CTRL_VF_MSE_SHIFT	3
#घोषणा ACC_PEH_MSI_DISABLE		GENMASK(31, 0)
#घोषणा ACC_MASTER_GLOBAL_CTRL_SHUTDOWN	0x1
#घोषणा ACC_MASTER_TRANS_RETURN_RW	3
#घोषणा ACC_MASTER_TRANS_RETURN		0x300150
#घोषणा ACC_MASTER_GLOBAL_CTRL		0x300000
#घोषणा ACC_AM_CFG_PORT_WR_EN		0x30001c
#घोषणा QM_RAS_NFE_MBIT_DISABLE		~QM_ECC_MBIT
#घोषणा ACC_AM_ROB_ECC_INT_STS		0x300104
#घोषणा ACC_ROB_ECC_ERR_MULTPL		BIT(1)

#घोषणा QM_DFX_MB_CNT_VF		0x104010
#घोषणा QM_DFX_DB_CNT_VF		0x104020
#घोषणा QM_DFX_SQE_CNT_VF_SQN		0x104030
#घोषणा QM_DFX_CQE_CNT_VF_CQN		0x104040
#घोषणा QM_DFX_QN_SHIFT			16
#घोषणा CURRENT_FUN_MASK		GENMASK(5, 0)
#घोषणा CURRENT_Q_MASK			GENMASK(31, 16)

#घोषणा POLL_PERIOD			10
#घोषणा POLL_TIMEOUT			1000
#घोषणा WAIT_PERIOD_US_MAX		200
#घोषणा WAIT_PERIOD_US_MIN		100
#घोषणा MAX_WAIT_COUNTS			1000
#घोषणा QM_CACHE_WB_START		0x204
#घोषणा QM_CACHE_WB_DONE		0x208

#घोषणा PCI_BAR_2			2
#घोषणा PCI_BAR_4			4
#घोषणा QM_SQE_DATA_ALIGN_MASK		GENMASK(6, 0)
#घोषणा QMC_ALIGN(sz)			ALIGN(sz, 32)

#घोषणा QM_DBG_READ_LEN		256
#घोषणा QM_DBG_WRITE_LEN		1024
#घोषणा QM_DBG_TMP_BUF_LEN		22
#घोषणा QM_PCI_COMMAND_INVALID		~0

#घोषणा WAIT_PERIOD			20
#घोषणा REMOVE_WAIT_DELAY		10
#घोषणा QM_SQE_ADDR_MASK		GENMASK(7, 0)
#घोषणा QM_EQ_DEPTH			(1024 * 2)

#घोषणा QM_DRIVER_REMOVING		0
#घोषणा QM_RST_SCHED			1
#घोषणा QM_RESETTING			2

#घोषणा QM_MK_CQC_DW3_V1(hop_num, pg_sz, buf_sz, cqe_sz) \
	(((hop_num) << QM_CQ_HOP_NUM_SHIFT)	| \
	((pg_sz) << QM_CQ_PAGE_SIZE_SHIFT)	| \
	((buf_sz) << QM_CQ_BUF_SIZE_SHIFT)	| \
	((cqe_sz) << QM_CQ_CQE_SIZE_SHIFT))

#घोषणा QM_MK_CQC_DW3_V2(cqe_sz) \
	((QM_Q_DEPTH - 1) | ((cqe_sz) << QM_CQ_CQE_SIZE_SHIFT))

#घोषणा QM_MK_SQC_W13(priority, orders, alg_type) \
	(((priority) << QM_SQ_PRIORITY_SHIFT)	| \
	((orders) << QM_SQ_ORDERS_SHIFT)	| \
	(((alg_type) & QM_SQ_TYPE_MASK) << QM_SQ_TYPE_SHIFT))

#घोषणा QM_MK_SQC_DW3_V1(hop_num, pg_sz, buf_sz, sqe_sz) \
	(((hop_num) << QM_SQ_HOP_NUM_SHIFT)	| \
	((pg_sz) << QM_SQ_PAGE_SIZE_SHIFT)	| \
	((buf_sz) << QM_SQ_BUF_SIZE_SHIFT)	| \
	((u32)ilog2(sqe_sz) << QM_SQ_SQE_SIZE_SHIFT))

#घोषणा QM_MK_SQC_DW3_V2(sqe_sz) \
	((QM_Q_DEPTH - 1) | ((u32)ilog2(sqe_sz) << QM_SQ_SQE_SIZE_SHIFT))

#घोषणा INIT_QC_COMMON(qc, base, pasid) करो अणु			\
	(qc)->head = 0;						\
	(qc)->tail = 0;						\
	(qc)->base_l = cpu_to_le32(lower_32_bits(base));	\
	(qc)->base_h = cpu_to_le32(upper_32_bits(base));	\
	(qc)->dw3 = 0;						\
	(qc)->w8 = 0;						\
	(qc)->rsvd0 = 0;					\
	(qc)->pasid = cpu_to_le16(pasid);			\
	(qc)->w11 = 0;						\
	(qc)->rsvd1 = 0;					\
पूर्ण जबतक (0)

क्रमागत vft_type अणु
	SQC_VFT = 0,
	CQC_VFT,
पूर्ण;

क्रमागत acc_err_result अणु
	ACC_ERR_NONE,
	ACC_ERR_NEED_RESET,
	ACC_ERR_RECOVERED,
पूर्ण;

काष्ठा qm_cqe अणु
	__le32 rsvd0;
	__le16 cmd_id;
	__le16 rsvd1;
	__le16 sq_head;
	__le16 sq_num;
	__le16 rsvd2;
	__le16 w7;
पूर्ण;

काष्ठा qm_eqe अणु
	__le32 dw0;
पूर्ण;

काष्ठा qm_aeqe अणु
	__le32 dw0;
पूर्ण;

काष्ठा qm_sqc अणु
	__le16 head;
	__le16 tail;
	__le32 base_l;
	__le32 base_h;
	__le32 dw3;
	__le16 w8;
	__le16 rsvd0;
	__le16 pasid;
	__le16 w11;
	__le16 cq_num;
	__le16 w13;
	__le32 rsvd1;
पूर्ण;

काष्ठा qm_cqc अणु
	__le16 head;
	__le16 tail;
	__le32 base_l;
	__le32 base_h;
	__le32 dw3;
	__le16 w8;
	__le16 rsvd0;
	__le16 pasid;
	__le16 w11;
	__le32 dw6;
	__le32 rsvd1;
पूर्ण;

काष्ठा qm_eqc अणु
	__le16 head;
	__le16 tail;
	__le32 base_l;
	__le32 base_h;
	__le32 dw3;
	__le32 rsvd[2];
	__le32 dw6;
पूर्ण;

काष्ठा qm_aeqc अणु
	__le16 head;
	__le16 tail;
	__le32 base_l;
	__le32 base_h;
	__le32 dw3;
	__le32 rsvd[2];
	__le32 dw6;
पूर्ण;

काष्ठा qm_mailbox अणु
	__le16 w0;
	__le16 queue_num;
	__le32 base_l;
	__le32 base_h;
	__le32 rsvd;
पूर्ण;

काष्ठा qm_करोorbell अणु
	__le16 queue_num;
	__le16 cmd;
	__le16 index;
	__le16 priority;
पूर्ण;

काष्ठा hisi_qm_resource अणु
	काष्ठा hisi_qm *qm;
	पूर्णांक distance;
	काष्ठा list_head list;
पूर्ण;

काष्ठा hisi_qm_hw_ops अणु
	पूर्णांक (*get_vft)(काष्ठा hisi_qm *qm, u32 *base, u32 *number);
	व्योम (*qm_db)(काष्ठा hisi_qm *qm, u16 qn,
		      u8 cmd, u16 index, u8 priority);
	u32 (*get_irq_num)(काष्ठा hisi_qm *qm);
	पूर्णांक (*debug_init)(काष्ठा hisi_qm *qm);
	व्योम (*hw_error_init)(काष्ठा hisi_qm *qm, u32 ce, u32 nfe, u32 fe);
	व्योम (*hw_error_uninit)(काष्ठा hisi_qm *qm);
	क्रमागत acc_err_result (*hw_error_handle)(काष्ठा hisi_qm *qm);
	पूर्णांक (*stop_qp)(काष्ठा hisi_qp *qp);
पूर्ण;

काष्ठा qm_dfx_item अणु
	स्थिर अक्षर *name;
	u32 offset;
पूर्ण;

अटल काष्ठा qm_dfx_item qm_dfx_files[] = अणु
	अणु"err_irq", दुरत्व(काष्ठा qm_dfx, err_irq_cnt)पूर्ण,
	अणु"aeq_irq", दुरत्व(काष्ठा qm_dfx, aeq_irq_cnt)पूर्ण,
	अणु"abnormal_irq", दुरत्व(काष्ठा qm_dfx, abnormal_irq_cnt)पूर्ण,
	अणु"create_qp_err", दुरत्व(काष्ठा qm_dfx, create_qp_err_cnt)पूर्ण,
	अणु"mb_err", दुरत्व(काष्ठा qm_dfx, mb_err_cnt)पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर qm_debug_file_name[] = अणु
	[CURRENT_QM]   = "current_qm",
	[CURRENT_Q]    = "current_q",
	[CLEAR_ENABLE] = "clear_enable",
पूर्ण;

काष्ठा hisi_qm_hw_error अणु
	u32 पूर्णांक_msk;
	स्थिर अक्षर *msg;
पूर्ण;

अटल स्थिर काष्ठा hisi_qm_hw_error qm_hw_error[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "qm_axi_rresp" पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "qm_axi_bresp" पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "qm_ecc_mbit" पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "qm_ecc_1bit" पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "qm_acc_get_task_timeout" पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "qm_acc_do_task_timeout" पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "qm_acc_wb_not_ready_timeout" पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "qm_sq_cq_vf_invalid" पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "qm_cq_vf_invalid" पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "qm_sq_vf_invalid" पूर्ण,
	अणु .पूर्णांक_msk = BIT(10), .msg = "qm_db_timeout" पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "qm_of_fifo_of" पूर्ण,
	अणु .पूर्णांक_msk = BIT(12), .msg = "qm_db_random_invalid" पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "qm_mailbox_timeout" पूर्ण,
	अणु .पूर्णांक_msk = BIT(14), .msg = "qm_flr_timeout" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर qm_db_समयout[] = अणु
	"sq", "cq", "eq", "aeq",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qm_fअगरo_overflow[] = अणु
	"cq", "eq", "aeq",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qm_s[] = अणु
	"init", "start", "close", "stop",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qp_s[] = अणु
	"none", "init", "start", "stop", "close",
पूर्ण;

अटल bool qm_avail_state(काष्ठा hisi_qm *qm, क्रमागत qm_state new)
अणु
	क्रमागत qm_state curr = atomic_पढ़ो(&qm->status.flags);
	bool avail = false;

	चयन (curr) अणु
	हाल QM_INIT:
		अगर (new == QM_START || new == QM_CLOSE)
			avail = true;
		अवरोध;
	हाल QM_START:
		अगर (new == QM_STOP)
			avail = true;
		अवरोध;
	हाल QM_STOP:
		अगर (new == QM_CLOSE || new == QM_START)
			avail = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(&qm->pdev->dev, "change qm state from %s to %s\n",
		qm_s[curr], qm_s[new]);

	अगर (!avail)
		dev_warn(&qm->pdev->dev, "Can not change qm state from %s to %s\n",
			 qm_s[curr], qm_s[new]);

	वापस avail;
पूर्ण

अटल bool qm_qp_avail_state(काष्ठा hisi_qm *qm, काष्ठा hisi_qp *qp,
			      क्रमागत qp_state new)
अणु
	क्रमागत qm_state qm_curr = atomic_पढ़ो(&qm->status.flags);
	क्रमागत qp_state qp_curr = 0;
	bool avail = false;

	अगर (qp)
		qp_curr = atomic_पढ़ो(&qp->qp_status.flags);

	चयन (new) अणु
	हाल QP_INIT:
		अगर (qm_curr == QM_START || qm_curr == QM_INIT)
			avail = true;
		अवरोध;
	हाल QP_START:
		अगर ((qm_curr == QM_START && qp_curr == QP_INIT) ||
		    (qm_curr == QM_START && qp_curr == QP_STOP))
			avail = true;
		अवरोध;
	हाल QP_STOP:
		अगर ((qm_curr == QM_START && qp_curr == QP_START) ||
		    (qp_curr == QP_INIT))
			avail = true;
		अवरोध;
	हाल QP_CLOSE:
		अगर ((qm_curr == QM_START && qp_curr == QP_INIT) ||
		    (qm_curr == QM_START && qp_curr == QP_STOP) ||
		    (qm_curr == QM_STOP && qp_curr == QP_STOP)  ||
		    (qm_curr == QM_STOP && qp_curr == QP_INIT))
			avail = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(&qm->pdev->dev, "change qp state from %s to %s in QM %s\n",
		qp_s[qp_curr], qp_s[new], qm_s[qm_curr]);

	अगर (!avail)
		dev_warn(&qm->pdev->dev,
			 "Can not change qp state from %s to %s in QM %s\n",
			 qp_s[qp_curr], qp_s[new], qm_s[qm_curr]);

	वापस avail;
पूर्ण

/* वापस 0 mailbox पढ़ोy, -ETIMEDOUT hardware समयout */
अटल पूर्णांक qm_रुको_mb_पढ़ोy(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	वापस पढ़ोl_relaxed_poll_समयout(qm->io_base + QM_MB_CMD_SEND_BASE,
					  val, !((val >> QM_MB_BUSY_SHIFT) &
					  0x1), POLL_PERIOD, POLL_TIMEOUT);
पूर्ण

/* 128 bit should be written to hardware at one समय to trigger a mailbox */
अटल व्योम qm_mb_ग_लिखो(काष्ठा hisi_qm *qm, स्थिर व्योम *src)
अणु
	व्योम __iomem *fun_base = qm->io_base + QM_MB_CMD_SEND_BASE;
	अचिन्हित दीर्घ पंचांगp0 = 0, पंचांगp1 = 0;

	अगर (!IS_ENABLED(CONFIG_ARM64)) अणु
		स_नकल_toio(fun_base, src, 16);
		wmb();
		वापस;
	पूर्ण

	यंत्र अस्थिर("ldp %0, %1, %3\n"
		     "stp %0, %1, %2\n"
		     "dsb sy\n"
		     : "=&r" (पंचांगp0),
		       "=&r" (पंचांगp1),
		       "+Q" (*((अक्षर __iomem *)fun_base))
		     : "Q" (*((अक्षर *)src))
		     : "memory");
पूर्ण

अटल पूर्णांक qm_mb(काष्ठा hisi_qm *qm, u8 cmd, dma_addr_t dma_addr, u16 queue,
		 bool op)
अणु
	काष्ठा qm_mailbox mailbox;
	पूर्णांक ret = 0;

	dev_dbg(&qm->pdev->dev, "QM mailbox request to q%u: %u-%llx\n",
		queue, cmd, (अचिन्हित दीर्घ दीर्घ)dma_addr);

	mailbox.w0 = cpu_to_le16(cmd |
		     (op ? 0x1 << QM_MB_OP_SHIFT : 0) |
		     (0x1 << QM_MB_BUSY_SHIFT));
	mailbox.queue_num = cpu_to_le16(queue);
	mailbox.base_l = cpu_to_le32(lower_32_bits(dma_addr));
	mailbox.base_h = cpu_to_le32(upper_32_bits(dma_addr));
	mailbox.rsvd = 0;

	mutex_lock(&qm->mailbox_lock);

	अगर (unlikely(qm_रुको_mb_पढ़ोy(qm))) अणु
		ret = -EBUSY;
		dev_err(&qm->pdev->dev, "QM mailbox is busy to start!\n");
		जाओ busy_unlock;
	पूर्ण

	qm_mb_ग_लिखो(qm, &mailbox);

	अगर (unlikely(qm_रुको_mb_पढ़ोy(qm))) अणु
		ret = -EBUSY;
		dev_err(&qm->pdev->dev, "QM mailbox operation timeout!\n");
		जाओ busy_unlock;
	पूर्ण

busy_unlock:
	mutex_unlock(&qm->mailbox_lock);

	अगर (ret)
		atomic64_inc(&qm->debug.dfx.mb_err_cnt);
	वापस ret;
पूर्ण

अटल व्योम qm_db_v1(काष्ठा hisi_qm *qm, u16 qn, u8 cmd, u16 index, u8 priority)
अणु
	u64 करोorbell;

	करोorbell = qn | ((u64)cmd << QM_DB_CMD_SHIFT_V1) |
		   ((u64)index << QM_DB_INDEX_SHIFT_V1)  |
		   ((u64)priority << QM_DB_PRIORITY_SHIFT_V1);

	ग_लिखोq(करोorbell, qm->io_base + QM_DOORBELL_BASE_V1);
पूर्ण

अटल व्योम qm_db_v2(काष्ठा hisi_qm *qm, u16 qn, u8 cmd, u16 index, u8 priority)
अणु
	व्योम __iomem *io_base = qm->io_base;
	u16 अक्रमata = 0;
	u64 करोorbell;

	अगर (cmd == QM_DOORBELL_CMD_SQ || cmd == QM_DOORBELL_CMD_CQ)
		io_base = qm->db_io_base + (u64)qn * qm->db_पूर्णांकerval +
			  QM_DOORBELL_SQ_CQ_BASE_V2;
	अन्यथा
		io_base += QM_DOORBELL_EQ_AEQ_BASE_V2;

	करोorbell = qn | ((u64)cmd << QM_DB_CMD_SHIFT_V2) |
		   ((u64)अक्रमata << QM_DB_RAND_SHIFT_V2) |
		   ((u64)index << QM_DB_INDEX_SHIFT_V2)	 |
		   ((u64)priority << QM_DB_PRIORITY_SHIFT_V2);

	ग_लिखोq(करोorbell, io_base);
पूर्ण

अटल व्योम qm_db(काष्ठा hisi_qm *qm, u16 qn, u8 cmd, u16 index, u8 priority)
अणु
	dev_dbg(&qm->pdev->dev, "QM doorbell request: qn=%u, cmd=%u, index=%u\n",
		qn, cmd, index);

	qm->ops->qm_db(qm, qn, cmd, index, priority);
पूर्ण

अटल पूर्णांक qm_dev_mem_reset(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	ग_लिखोl(0x1, qm->io_base + QM_MEM_START_INIT);
	वापस पढ़ोl_relaxed_poll_समयout(qm->io_base + QM_MEM_INIT_DONE, val,
					  val & BIT(0), POLL_PERIOD,
					  POLL_TIMEOUT);
पूर्ण

अटल u32 qm_get_irq_num_v1(काष्ठा hisi_qm *qm)
अणु
	वापस QM_IRQ_NUM_V1;
पूर्ण

अटल u32 qm_get_irq_num_v2(काष्ठा hisi_qm *qm)
अणु
	अगर (qm->fun_type == QM_HW_PF)
		वापस QM_IRQ_NUM_PF_V2;
	अन्यथा
		वापस QM_IRQ_NUM_VF_V2;
पूर्ण

अटल काष्ठा hisi_qp *qm_to_hisi_qp(काष्ठा hisi_qm *qm, काष्ठा qm_eqe *eqe)
अणु
	u16 cqn = le32_to_cpu(eqe->dw0) & QM_EQE_CQN_MASK;

	वापस &qm->qp_array[cqn];
पूर्ण

अटल व्योम qm_cq_head_update(काष्ठा hisi_qp *qp)
अणु
	अगर (qp->qp_status.cq_head == QM_Q_DEPTH - 1) अणु
		qp->qp_status.cqc_phase = !qp->qp_status.cqc_phase;
		qp->qp_status.cq_head = 0;
	पूर्ण अन्यथा अणु
		qp->qp_status.cq_head++;
	पूर्ण
पूर्ण

अटल व्योम qm_poll_qp(काष्ठा hisi_qp *qp, काष्ठा hisi_qm *qm)
अणु
	अगर (unlikely(atomic_पढ़ो(&qp->qp_status.flags) == QP_STOP))
		वापस;

	अगर (qp->event_cb) अणु
		qp->event_cb(qp);
		वापस;
	पूर्ण

	अगर (qp->req_cb) अणु
		काष्ठा qm_cqe *cqe = qp->cqe + qp->qp_status.cq_head;

		जबतक (QM_CQE_PHASE(cqe) == qp->qp_status.cqc_phase) अणु
			dma_rmb();
			qp->req_cb(qp, qp->sqe + qm->sqe_size *
				   le16_to_cpu(cqe->sq_head));
			qm_cq_head_update(qp);
			cqe = qp->cqe + qp->qp_status.cq_head;
			qm_db(qm, qp->qp_id, QM_DOORBELL_CMD_CQ,
			      qp->qp_status.cq_head, 0);
			atomic_dec(&qp->qp_status.used);
		पूर्ण

		/* set c_flag */
		qm_db(qm, qp->qp_id, QM_DOORBELL_CMD_CQ,
		      qp->qp_status.cq_head, 1);
	पूर्ण
पूर्ण

अटल व्योम qm_work_process(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hisi_qm *qm = container_of(work, काष्ठा hisi_qm, work);
	काष्ठा qm_eqe *eqe = qm->eqe + qm->status.eq_head;
	काष्ठा hisi_qp *qp;
	पूर्णांक eqe_num = 0;

	जबतक (QM_EQE_PHASE(eqe) == qm->status.eqc_phase) अणु
		eqe_num++;
		qp = qm_to_hisi_qp(qm, eqe);
		qm_poll_qp(qp, qm);

		अगर (qm->status.eq_head == QM_EQ_DEPTH - 1) अणु
			qm->status.eqc_phase = !qm->status.eqc_phase;
			eqe = qm->eqe;
			qm->status.eq_head = 0;
		पूर्ण अन्यथा अणु
			eqe++;
			qm->status.eq_head++;
		पूर्ण

		अगर (eqe_num == QM_EQ_DEPTH / 2 - 1) अणु
			eqe_num = 0;
			qm_db(qm, 0, QM_DOORBELL_CMD_EQ, qm->status.eq_head, 0);
		पूर्ण
	पूर्ण

	qm_db(qm, 0, QM_DOORBELL_CMD_EQ, qm->status.eq_head, 0);
पूर्ण

अटल irqवापस_t करो_qm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hisi_qm *qm = (काष्ठा hisi_qm *)data;

	/* the workqueue created by device driver of QM */
	अगर (qm->wq)
		queue_work(qm->wq, &qm->work);
	अन्यथा
		schedule_work(&qm->work);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hisi_qm *qm = data;

	अगर (पढ़ोl(qm->io_base + QM_VF_EQ_INT_SOURCE))
		वापस करो_qm_irq(irq, data);

	atomic64_inc(&qm->debug.dfx.err_irq_cnt);
	dev_err(&qm->pdev->dev, "invalid int source\n");
	qm_db(qm, 0, QM_DOORBELL_CMD_EQ, qm->status.eq_head, 0);

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t qm_aeq_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hisi_qm *qm = data;
	काष्ठा qm_aeqe *aeqe = qm->aeqe + qm->status.aeq_head;
	u32 type;

	atomic64_inc(&qm->debug.dfx.aeq_irq_cnt);
	अगर (!पढ़ोl(qm->io_base + QM_VF_AEQ_INT_SOURCE))
		वापस IRQ_NONE;

	जबतक (QM_AEQE_PHASE(aeqe) == qm->status.aeqc_phase) अणु
		type = le32_to_cpu(aeqe->dw0) >> QM_AEQE_TYPE_SHIFT;
		अगर (type < ARRAY_SIZE(qm_fअगरo_overflow))
			dev_err(&qm->pdev->dev, "%s overflow\n",
				qm_fअगरo_overflow[type]);
		अन्यथा
			dev_err(&qm->pdev->dev, "unknown error type %u\n",
				type);

		अगर (qm->status.aeq_head == QM_Q_DEPTH - 1) अणु
			qm->status.aeqc_phase = !qm->status.aeqc_phase;
			aeqe = qm->aeqe;
			qm->status.aeq_head = 0;
		पूर्ण अन्यथा अणु
			aeqe++;
			qm->status.aeq_head++;
		पूर्ण

		qm_db(qm, 0, QM_DOORBELL_CMD_AEQ, qm->status.aeq_head, 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम qm_irq_unरेजिस्टर(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;

	मुक्त_irq(pci_irq_vector(pdev, QM_EQ_EVENT_IRQ_VECTOR), qm);

	अगर (qm->ver == QM_HW_V1)
		वापस;

	मुक्त_irq(pci_irq_vector(pdev, QM_AEQ_EVENT_IRQ_VECTOR), qm);

	अगर (qm->fun_type == QM_HW_PF)
		मुक्त_irq(pci_irq_vector(pdev,
			 QM_ABNORMAL_EVENT_IRQ_VECTOR), qm);
पूर्ण

अटल व्योम qm_init_qp_status(काष्ठा hisi_qp *qp)
अणु
	काष्ठा hisi_qp_status *qp_status = &qp->qp_status;

	qp_status->sq_tail = 0;
	qp_status->cq_head = 0;
	qp_status->cqc_phase = true;
	atomic_set(&qp_status->used, 0);
पूर्ण

अटल व्योम qm_vft_data_cfg(काष्ठा hisi_qm *qm, क्रमागत vft_type type, u32 base,
			    u32 number)
अणु
	u64 पंचांगp = 0;

	अगर (number > 0) अणु
		चयन (type) अणु
		हाल SQC_VFT:
			अगर (qm->ver == QM_HW_V1) अणु
				पंचांगp = QM_SQC_VFT_BUF_SIZE	|
				      QM_SQC_VFT_SQC_SIZE	|
				      QM_SQC_VFT_INDEX_NUMBER	|
				      QM_SQC_VFT_VALID		|
				      (u64)base << QM_SQC_VFT_START_SQN_SHIFT;
			पूर्ण अन्यथा अणु
				पंचांगp = (u64)base << QM_SQC_VFT_START_SQN_SHIFT |
				      QM_SQC_VFT_VALID |
				      (u64)(number - 1) << QM_SQC_VFT_SQN_SHIFT;
			पूर्ण
			अवरोध;
		हाल CQC_VFT:
			अगर (qm->ver == QM_HW_V1) अणु
				पंचांगp = QM_CQC_VFT_BUF_SIZE	|
				      QM_CQC_VFT_SQC_SIZE	|
				      QM_CQC_VFT_INDEX_NUMBER	|
				      QM_CQC_VFT_VALID;
			पूर्ण अन्यथा अणु
				पंचांगp = QM_CQC_VFT_VALID;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखोl(lower_32_bits(पंचांगp), qm->io_base + QM_VFT_CFG_DATA_L);
	ग_लिखोl(upper_32_bits(पंचांगp), qm->io_base + QM_VFT_CFG_DATA_H);
पूर्ण

अटल पूर्णांक qm_set_vft_common(काष्ठा hisi_qm *qm, क्रमागत vft_type type,
			     u32 fun_num, u32 base, u32 number)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = पढ़ोl_relaxed_poll_समयout(qm->io_base + QM_VFT_CFG_RDY, val,
					 val & BIT(0), POLL_PERIOD,
					 POLL_TIMEOUT);
	अगर (ret)
		वापस ret;

	ग_लिखोl(0x0, qm->io_base + QM_VFT_CFG_OP_WR);
	ग_लिखोl(type, qm->io_base + QM_VFT_CFG_TYPE);
	ग_लिखोl(fun_num, qm->io_base + QM_VFT_CFG);

	qm_vft_data_cfg(qm, type, base, number);

	ग_लिखोl(0x0, qm->io_base + QM_VFT_CFG_RDY);
	ग_लिखोl(0x1, qm->io_base + QM_VFT_CFG_OP_ENABLE);

	वापस पढ़ोl_relaxed_poll_समयout(qm->io_base + QM_VFT_CFG_RDY, val,
					  val & BIT(0), POLL_PERIOD,
					  POLL_TIMEOUT);
पूर्ण

/* The config should be conducted after qm_dev_mem_reset() */
अटल पूर्णांक qm_set_sqc_cqc_vft(काष्ठा hisi_qm *qm, u32 fun_num, u32 base,
			      u32 number)
अणु
	पूर्णांक ret, i;

	क्रम (i = SQC_VFT; i <= CQC_VFT; i++) अणु
		ret = qm_set_vft_common(qm, i, fun_num, base, number);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qm_get_vft_v2(काष्ठा hisi_qm *qm, u32 *base, u32 *number)
अणु
	u64 sqc_vft;
	पूर्णांक ret;

	ret = qm_mb(qm, QM_MB_CMD_SQC_VFT_V2, 0, 0, 1);
	अगर (ret)
		वापस ret;

	sqc_vft = पढ़ोl(qm->io_base + QM_MB_CMD_DATA_ADDR_L) |
		  ((u64)पढ़ोl(qm->io_base + QM_MB_CMD_DATA_ADDR_H) << 32);
	*base = QM_SQC_VFT_BASE_MASK_V2 & (sqc_vft >> QM_SQC_VFT_BASE_SHIFT_V2);
	*number = (QM_SQC_VFT_NUM_MASK_v2 &
		   (sqc_vft >> QM_SQC_VFT_NUM_SHIFT_V2)) + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक qm_get_vf_qp_num(काष्ठा hisi_qm *qm, u32 fun_num)
अणु
	u32 reमुख्य_q_num, vfq_num;
	u32 num_vfs = qm->vfs_num;

	vfq_num = (qm->ctrl_qp_num - qm->qp_num) / num_vfs;
	अगर (vfq_num >= qm->max_qp_num)
		वापस qm->max_qp_num;

	reमुख्य_q_num = (qm->ctrl_qp_num - qm->qp_num) % num_vfs;
	अगर (vfq_num + reमुख्य_q_num <= qm->max_qp_num)
		वापस fun_num == num_vfs ? vfq_num + reमुख्य_q_num : vfq_num;

	/*
	 * अगर vfq_num + reमुख्य_q_num > max_qp_num, the last VFs,
	 * each with one more queue.
	 */
	वापस fun_num + reमुख्य_q_num > num_vfs ? vfq_num + 1 : vfq_num;
पूर्ण

अटल काष्ठा hisi_qm *file_to_qm(काष्ठा debugfs_file *file)
अणु
	काष्ठा qm_debug *debug = file->debug;

	वापस container_of(debug, काष्ठा hisi_qm, debug);
पूर्ण

अटल u32 current_q_पढ़ो(काष्ठा debugfs_file *file)
अणु
	काष्ठा hisi_qm *qm = file_to_qm(file);

	वापस पढ़ोl(qm->io_base + QM_DFX_SQE_CNT_VF_SQN) >> QM_DFX_QN_SHIFT;
पूर्ण

अटल पूर्णांक current_q_ग_लिखो(काष्ठा debugfs_file *file, u32 val)
अणु
	काष्ठा hisi_qm *qm = file_to_qm(file);
	u32 पंचांगp;

	अगर (val >= qm->debug.curr_qm_qp_num)
		वापस -EINVAL;

	पंचांगp = val << QM_DFX_QN_SHIFT |
	      (पढ़ोl(qm->io_base + QM_DFX_SQE_CNT_VF_SQN) & CURRENT_FUN_MASK);
	ग_लिखोl(पंचांगp, qm->io_base + QM_DFX_SQE_CNT_VF_SQN);

	पंचांगp = val << QM_DFX_QN_SHIFT |
	      (पढ़ोl(qm->io_base + QM_DFX_CQE_CNT_VF_CQN) & CURRENT_FUN_MASK);
	ग_लिखोl(पंचांगp, qm->io_base + QM_DFX_CQE_CNT_VF_CQN);

	वापस 0;
पूर्ण

अटल u32 clear_enable_पढ़ो(काष्ठा debugfs_file *file)
अणु
	काष्ठा hisi_qm *qm = file_to_qm(file);

	वापस पढ़ोl(qm->io_base + QM_DFX_CNT_CLR_CE);
पूर्ण

/* rd_clr_ctrl 1 enable पढ़ो clear, otherwise 0 disable it */
अटल पूर्णांक clear_enable_ग_लिखो(काष्ठा debugfs_file *file, u32 rd_clr_ctrl)
अणु
	काष्ठा hisi_qm *qm = file_to_qm(file);

	अगर (rd_clr_ctrl > 1)
		वापस -EINVAL;

	ग_लिखोl(rd_clr_ctrl, qm->io_base + QM_DFX_CNT_CLR_CE);

	वापस 0;
पूर्ण

अटल u32 current_qm_पढ़ो(काष्ठा debugfs_file *file)
अणु
	काष्ठा hisi_qm *qm = file_to_qm(file);

	वापस पढ़ोl(qm->io_base + QM_DFX_MB_CNT_VF);
पूर्ण

अटल पूर्णांक current_qm_ग_लिखो(काष्ठा debugfs_file *file, u32 val)
अणु
	काष्ठा hisi_qm *qm = file_to_qm(file);
	u32 पंचांगp;

	अगर (val > qm->vfs_num)
		वापस -EINVAL;

	/* According PF or VF Dev ID to calculation curr_qm_qp_num and store */
	अगर (!val)
		qm->debug.curr_qm_qp_num = qm->qp_num;
	अन्यथा
		qm->debug.curr_qm_qp_num = qm_get_vf_qp_num(qm, val);

	ग_लिखोl(val, qm->io_base + QM_DFX_MB_CNT_VF);
	ग_लिखोl(val, qm->io_base + QM_DFX_DB_CNT_VF);

	पंचांगp = val |
	      (पढ़ोl(qm->io_base + QM_DFX_SQE_CNT_VF_SQN) & CURRENT_Q_MASK);
	ग_लिखोl(पंचांगp, qm->io_base + QM_DFX_SQE_CNT_VF_SQN);

	पंचांगp = val |
	      (पढ़ोl(qm->io_base + QM_DFX_CQE_CNT_VF_CQN) & CURRENT_Q_MASK);
	ग_लिखोl(पंचांगp, qm->io_base + QM_DFX_CQE_CNT_VF_CQN);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार qm_debug_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा debugfs_file *file = filp->निजी_data;
	क्रमागत qm_debug_file index = file->index;
	अक्षर tbuf[QM_DBG_TMP_BUF_LEN];
	u32 val;
	पूर्णांक ret;

	mutex_lock(&file->lock);
	चयन (index) अणु
	हाल CURRENT_QM:
		val = current_qm_पढ़ो(file);
		अवरोध;
	हाल CURRENT_Q:
		val = current_q_पढ़ो(file);
		अवरोध;
	हाल CLEAR_ENABLE:
		val = clear_enable_पढ़ो(file);
		अवरोध;
	शेष:
		mutex_unlock(&file->lock);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(&file->lock);

	ret = scnम_लिखो(tbuf, QM_DBG_TMP_BUF_LEN, "%u\n", val);
	वापस simple_पढ़ो_from_buffer(buf, count, pos, tbuf, ret);
पूर्ण

अटल sमाप_प्रकार qm_debug_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा debugfs_file *file = filp->निजी_data;
	क्रमागत qm_debug_file index = file->index;
	अचिन्हित दीर्घ val;
	अक्षर tbuf[QM_DBG_TMP_BUF_LEN];
	पूर्णांक len, ret;

	अगर (*pos != 0)
		वापस 0;

	अगर (count >= QM_DBG_TMP_BUF_LEN)
		वापस -ENOSPC;

	len = simple_ग_लिखो_to_buffer(tbuf, QM_DBG_TMP_BUF_LEN - 1, pos, buf,
				     count);
	अगर (len < 0)
		वापस len;

	tbuf[len] = '\0';
	अगर (kम_से_अदीर्घ(tbuf, 0, &val))
		वापस -EFAULT;

	mutex_lock(&file->lock);
	चयन (index) अणु
	हाल CURRENT_QM:
		ret = current_qm_ग_लिखो(file, val);
		अवरोध;
	हाल CURRENT_Q:
		ret = current_q_ग_लिखो(file, val);
		अवरोध;
	हाल CLEAR_ENABLE:
		ret = clear_enable_ग_लिखो(file, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&file->lock);

	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations qm_debug_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = qm_debug_पढ़ो,
	.ग_लिखो = qm_debug_ग_लिखो,
पूर्ण;

काष्ठा qm_dfx_रेजिस्टरs अणु
	अक्षर  *reg_name;
	u64   reg_offset;
पूर्ण;

#घोषणा CNT_CYC_REGS_NUM		10
अटल काष्ठा qm_dfx_रेजिस्टरs qm_dfx_regs[] = अणु
	/* XXX_CNT are पढ़ोing clear रेजिस्टर */
	अणु"QM_ECC_1BIT_CNT               ",  0x104000ullपूर्ण,
	अणु"QM_ECC_MBIT_CNT               ",  0x104008ullपूर्ण,
	अणु"QM_DFX_MB_CNT                 ",  0x104018ullपूर्ण,
	अणु"QM_DFX_DB_CNT                 ",  0x104028ullपूर्ण,
	अणु"QM_DFX_SQE_CNT                ",  0x104038ullपूर्ण,
	अणु"QM_DFX_CQE_CNT                ",  0x104048ullपूर्ण,
	अणु"QM_DFX_SEND_SQE_TO_ACC_CNT    ",  0x104050ullपूर्ण,
	अणु"QM_DFX_WB_SQE_FROM_ACC_CNT    ",  0x104058ullपूर्ण,
	अणु"QM_DFX_ACC_FINISH_CNT         ",  0x104060ullपूर्ण,
	अणु"QM_DFX_CQE_ERR_CNT            ",  0x1040b4ullपूर्ण,
	अणु"QM_DFX_FUNS_ACTIVE_ST         ",  0x200ullपूर्ण,
	अणु"QM_ECC_1BIT_INF               ",  0x104004ullपूर्ण,
	अणु"QM_ECC_MBIT_INF               ",  0x10400cullपूर्ण,
	अणु"QM_DFX_ACC_RDY_VLD0           ",  0x1040a0ullपूर्ण,
	अणु"QM_DFX_ACC_RDY_VLD1           ",  0x1040a4ullपूर्ण,
	अणु"QM_DFX_AXI_RDY_VLD            ",  0x1040a8ullपूर्ण,
	अणु"QM_DFX_FF_ST0                 ",  0x1040c8ullपूर्ण,
	अणु"QM_DFX_FF_ST1                 ",  0x1040ccullपूर्ण,
	अणु"QM_DFX_FF_ST2                 ",  0x1040d0ullपूर्ण,
	अणु"QM_DFX_FF_ST3                 ",  0x1040d4ullपूर्ण,
	अणु"QM_DFX_FF_ST4                 ",  0x1040d8ullपूर्ण,
	अणु"QM_DFX_FF_ST5                 ",  0x1040dcullपूर्ण,
	अणु"QM_DFX_FF_ST6                 ",  0x1040e0ullपूर्ण,
	अणु"QM_IN_IDLE_ST                 ",  0x1040e4ullपूर्ण,
	अणु शून्य, 0पूर्ण
पूर्ण;

अटल काष्ठा qm_dfx_रेजिस्टरs qm_vf_dfx_regs[] = अणु
	अणु"QM_DFX_FUNS_ACTIVE_ST         ",  0x200ullपूर्ण,
	अणु शून्य, 0पूर्ण
पूर्ण;

अटल पूर्णांक qm_regs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा hisi_qm *qm = s->निजी;
	काष्ठा qm_dfx_रेजिस्टरs *regs;
	u32 val;

	अगर (qm->fun_type == QM_HW_PF)
		regs = qm_dfx_regs;
	अन्यथा
		regs = qm_vf_dfx_regs;

	जबतक (regs->reg_name) अणु
		val = पढ़ोl(qm->io_base + regs->reg_offset);
		seq_म_लिखो(s, "%s= 0x%08x\n", regs->reg_name, val);
		regs++;
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(qm_regs);

अटल sमाप_प्रकार qm_cmd_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
			   माप_प्रकार count, loff_t *pos)
अणु
	अक्षर buf[QM_DBG_READ_LEN];
	पूर्णांक len;

	len = scnम_लिखो(buf, QM_DBG_READ_LEN, "%s\n",
			"Please echo help to cmd to get help information");

	वापस simple_पढ़ो_from_buffer(buffer, count, pos, buf, len);
पूर्ण

अटल व्योम *qm_ctx_alloc(काष्ठा hisi_qm *qm, माप_प्रकार ctx_size,
			  dma_addr_t *dma_addr)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	व्योम *ctx_addr;

	ctx_addr = kzalloc(ctx_size, GFP_KERNEL);
	अगर (!ctx_addr)
		वापस ERR_PTR(-ENOMEM);

	*dma_addr = dma_map_single(dev, ctx_addr, ctx_size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, *dma_addr)) अणु
		dev_err(dev, "DMA mapping error!\n");
		kमुक्त(ctx_addr);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस ctx_addr;
पूर्ण

अटल व्योम qm_ctx_मुक्त(काष्ठा hisi_qm *qm, माप_प्रकार ctx_size,
			स्थिर व्योम *ctx_addr, dma_addr_t *dma_addr)
अणु
	काष्ठा device *dev = &qm->pdev->dev;

	dma_unmap_single(dev, *dma_addr, ctx_size, DMA_FROM_DEVICE);
	kमुक्त(ctx_addr);
पूर्ण

अटल पूर्णांक dump_show(काष्ठा hisi_qm *qm, व्योम *info,
		     अचिन्हित पूर्णांक info_size, अक्षर *info_name)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	u8 *info_buf, *info_curr = info;
	u32 i;
#घोषणा BYTE_PER_DW	4

	info_buf = kzalloc(info_size, GFP_KERNEL);
	अगर (!info_buf)
		वापस -ENOMEM;

	क्रम (i = 0; i < info_size; i++, info_curr++) अणु
		अगर (i % BYTE_PER_DW == 0)
			info_buf[i + 3UL] = *info_curr;
		अन्यथा अगर (i % BYTE_PER_DW == 1)
			info_buf[i + 1UL] = *info_curr;
		अन्यथा अगर (i % BYTE_PER_DW == 2)
			info_buf[i - 1] = *info_curr;
		अन्यथा अगर (i % BYTE_PER_DW == 3)
			info_buf[i - 3] = *info_curr;
	पूर्ण

	dev_info(dev, "%s DUMP\n", info_name);
	क्रम (i = 0; i < info_size; i += BYTE_PER_DW) अणु
		pr_info("DW%u: %02X%02X %02X%02X\n", i / BYTE_PER_DW,
			info_buf[i], info_buf[i + 1UL],
			info_buf[i + 2UL], info_buf[i + 3UL]);
	पूर्ण

	kमुक्त(info_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक qm_dump_sqc_raw(काष्ठा hisi_qm *qm, dma_addr_t dma_addr, u16 qp_id)
अणु
	वापस qm_mb(qm, QM_MB_CMD_SQC, dma_addr, qp_id, 1);
पूर्ण

अटल पूर्णांक qm_dump_cqc_raw(काष्ठा hisi_qm *qm, dma_addr_t dma_addr, u16 qp_id)
अणु
	वापस qm_mb(qm, QM_MB_CMD_CQC, dma_addr, qp_id, 1);
पूर्ण

अटल पूर्णांक qm_sqc_dump(काष्ठा hisi_qm *qm, स्थिर अक्षर *s)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा qm_sqc *sqc, *sqc_curr;
	dma_addr_t sqc_dma;
	u32 qp_id;
	पूर्णांक ret;

	अगर (!s)
		वापस -EINVAL;

	ret = kstrtou32(s, 0, &qp_id);
	अगर (ret || qp_id >= qm->qp_num) अणु
		dev_err(dev, "Please input qp num (0-%u)", qm->qp_num - 1);
		वापस -EINVAL;
	पूर्ण

	sqc = qm_ctx_alloc(qm, माप(*sqc), &sqc_dma);
	अगर (IS_ERR(sqc))
		वापस PTR_ERR(sqc);

	ret = qm_dump_sqc_raw(qm, sqc_dma, qp_id);
	अगर (ret) अणु
		करोwn_पढ़ो(&qm->qps_lock);
		अगर (qm->sqc) अणु
			sqc_curr = qm->sqc + qp_id;

			ret = dump_show(qm, sqc_curr, माप(*sqc),
					"SOFT SQC");
			अगर (ret)
				dev_info(dev, "Show soft sqc failed!\n");
		पूर्ण
		up_पढ़ो(&qm->qps_lock);

		जाओ err_मुक्त_ctx;
	पूर्ण

	ret = dump_show(qm, sqc, माप(*sqc), "SQC");
	अगर (ret)
		dev_info(dev, "Show hw sqc failed!\n");

err_मुक्त_ctx:
	qm_ctx_मुक्त(qm, माप(*sqc), sqc, &sqc_dma);
	वापस ret;
पूर्ण

अटल पूर्णांक qm_cqc_dump(काष्ठा hisi_qm *qm, स्थिर अक्षर *s)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा qm_cqc *cqc, *cqc_curr;
	dma_addr_t cqc_dma;
	u32 qp_id;
	पूर्णांक ret;

	अगर (!s)
		वापस -EINVAL;

	ret = kstrtou32(s, 0, &qp_id);
	अगर (ret || qp_id >= qm->qp_num) अणु
		dev_err(dev, "Please input qp num (0-%u)", qm->qp_num - 1);
		वापस -EINVAL;
	पूर्ण

	cqc = qm_ctx_alloc(qm, माप(*cqc), &cqc_dma);
	अगर (IS_ERR(cqc))
		वापस PTR_ERR(cqc);

	ret = qm_dump_cqc_raw(qm, cqc_dma, qp_id);
	अगर (ret) अणु
		करोwn_पढ़ो(&qm->qps_lock);
		अगर (qm->cqc) अणु
			cqc_curr = qm->cqc + qp_id;

			ret = dump_show(qm, cqc_curr, माप(*cqc),
					"SOFT CQC");
			अगर (ret)
				dev_info(dev, "Show soft cqc failed!\n");
		पूर्ण
		up_पढ़ो(&qm->qps_lock);

		जाओ err_मुक्त_ctx;
	पूर्ण

	ret = dump_show(qm, cqc, माप(*cqc), "CQC");
	अगर (ret)
		dev_info(dev, "Show hw cqc failed!\n");

err_मुक्त_ctx:
	qm_ctx_मुक्त(qm, माप(*cqc), cqc, &cqc_dma);
	वापस ret;
पूर्ण

अटल पूर्णांक qm_eqc_aeqc_dump(काष्ठा hisi_qm *qm, अक्षर *s, माप_प्रकार size,
			    पूर्णांक cmd, अक्षर *name)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	dma_addr_t xeqc_dma;
	व्योम *xeqc;
	पूर्णांक ret;

	अगर (strsep(&s, " ")) अणु
		dev_err(dev, "Please do not input extra characters!\n");
		वापस -EINVAL;
	पूर्ण

	xeqc = qm_ctx_alloc(qm, size, &xeqc_dma);
	अगर (IS_ERR(xeqc))
		वापस PTR_ERR(xeqc);

	ret = qm_mb(qm, cmd, xeqc_dma, 0, 1);
	अगर (ret)
		जाओ err_मुक्त_ctx;

	ret = dump_show(qm, xeqc, size, name);
	अगर (ret)
		dev_info(dev, "Show hw %s failed!\n", name);

err_मुक्त_ctx:
	qm_ctx_मुक्त(qm, size, xeqc, &xeqc_dma);
	वापस ret;
पूर्ण

अटल पूर्णांक q_dump_param_parse(काष्ठा hisi_qm *qm, अक्षर *s,
			      u32 *e_id, u32 *q_id)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	अचिन्हित पूर्णांक qp_num = qm->qp_num;
	अक्षर *presult;
	पूर्णांक ret;

	presult = strsep(&s, " ");
	अगर (!presult) अणु
		dev_err(dev, "Please input qp number!\n");
		वापस -EINVAL;
	पूर्ण

	ret = kstrtou32(presult, 0, q_id);
	अगर (ret || *q_id >= qp_num) अणु
		dev_err(dev, "Please input qp num (0-%u)", qp_num - 1);
		वापस -EINVAL;
	पूर्ण

	presult = strsep(&s, " ");
	अगर (!presult) अणु
		dev_err(dev, "Please input sqe number!\n");
		वापस -EINVAL;
	पूर्ण

	ret = kstrtou32(presult, 0, e_id);
	अगर (ret || *e_id >= QM_Q_DEPTH) अणु
		dev_err(dev, "Please input sqe num (0-%d)", QM_Q_DEPTH - 1);
		वापस -EINVAL;
	पूर्ण

	अगर (strsep(&s, " ")) अणु
		dev_err(dev, "Please do not input extra characters!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qm_sq_dump(काष्ठा hisi_qm *qm, अक्षर *s)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	व्योम *sqe, *sqe_curr;
	काष्ठा hisi_qp *qp;
	u32 qp_id, sqe_id;
	पूर्णांक ret;

	ret = q_dump_param_parse(qm, s, &sqe_id, &qp_id);
	अगर (ret)
		वापस ret;

	sqe = kzalloc(qm->sqe_size * QM_Q_DEPTH, GFP_KERNEL);
	अगर (!sqe)
		वापस -ENOMEM;

	qp = &qm->qp_array[qp_id];
	स_नकल(sqe, qp->sqe, qm->sqe_size * QM_Q_DEPTH);
	sqe_curr = sqe + (u32)(sqe_id * qm->sqe_size);
	स_रखो(sqe_curr + qm->debug.sqe_mask_offset, QM_SQE_ADDR_MASK,
	       qm->debug.sqe_mask_len);

	ret = dump_show(qm, sqe_curr, qm->sqe_size, "SQE");
	अगर (ret)
		dev_info(dev, "Show sqe failed!\n");

	kमुक्त(sqe);

	वापस ret;
पूर्ण

अटल पूर्णांक qm_cq_dump(काष्ठा hisi_qm *qm, अक्षर *s)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा qm_cqe *cqe_curr;
	काष्ठा hisi_qp *qp;
	u32 qp_id, cqe_id;
	पूर्णांक ret;

	ret = q_dump_param_parse(qm, s, &cqe_id, &qp_id);
	अगर (ret)
		वापस ret;

	qp = &qm->qp_array[qp_id];
	cqe_curr = qp->cqe + cqe_id;
	ret = dump_show(qm, cqe_curr, माप(काष्ठा qm_cqe), "CQE");
	अगर (ret)
		dev_info(dev, "Show cqe failed!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक qm_eq_aeq_dump(काष्ठा hisi_qm *qm, स्थिर अक्षर *s,
			  माप_प्रकार size, अक्षर *name)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	व्योम *xeqe;
	u32 xeqe_id;
	पूर्णांक ret;

	अगर (!s)
		वापस -EINVAL;

	ret = kstrtou32(s, 0, &xeqe_id);
	अगर (ret)
		वापस -EINVAL;

	अगर (!म_भेद(name, "EQE") && xeqe_id >= QM_EQ_DEPTH) अणु
		dev_err(dev, "Please input eqe num (0-%d)", QM_EQ_DEPTH - 1);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!म_भेद(name, "AEQE") && xeqe_id >= QM_Q_DEPTH) अणु
		dev_err(dev, "Please input aeqe num (0-%d)", QM_Q_DEPTH - 1);
		वापस -EINVAL;
	पूर्ण

	करोwn_पढ़ो(&qm->qps_lock);

	अगर (qm->eqe && !म_भेद(name, "EQE")) अणु
		xeqe = qm->eqe + xeqe_id;
	पूर्ण अन्यथा अगर (qm->aeqe && !म_भेद(name, "AEQE")) अणु
		xeqe = qm->aeqe + xeqe_id;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	ret = dump_show(qm, xeqe, size, name);
	अगर (ret)
		dev_info(dev, "Show %s failed!\n", name);

err_unlock:
	up_पढ़ो(&qm->qps_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक qm_dbg_help(काष्ठा hisi_qm *qm, अक्षर *s)
अणु
	काष्ठा device *dev = &qm->pdev->dev;

	अगर (strsep(&s, " ")) अणु
		dev_err(dev, "Please do not input extra characters!\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(dev, "available commands:\n");
	dev_info(dev, "sqc <num>\n");
	dev_info(dev, "cqc <num>\n");
	dev_info(dev, "eqc\n");
	dev_info(dev, "aeqc\n");
	dev_info(dev, "sq <num> <e>\n");
	dev_info(dev, "cq <num> <e>\n");
	dev_info(dev, "eq <e>\n");
	dev_info(dev, "aeq <e>\n");

	वापस 0;
पूर्ण

अटल पूर्णांक qm_cmd_ग_लिखो_dump(काष्ठा hisi_qm *qm, स्थिर अक्षर *cmd_buf)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	अक्षर *presult, *s, *s_पंचांगp;
	पूर्णांक ret;

	s = kstrdup(cmd_buf, GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	s_पंचांगp = s;
	presult = strsep(&s, " ");
	अगर (!presult) अणु
		ret = -EINVAL;
		जाओ err_buffer_मुक्त;
	पूर्ण

	अगर (!म_भेद(presult, "sqc"))
		ret = qm_sqc_dump(qm, s);
	अन्यथा अगर (!म_भेद(presult, "cqc"))
		ret = qm_cqc_dump(qm, s);
	अन्यथा अगर (!म_भेद(presult, "eqc"))
		ret = qm_eqc_aeqc_dump(qm, s, माप(काष्ठा qm_eqc),
				       QM_MB_CMD_EQC, "EQC");
	अन्यथा अगर (!म_भेद(presult, "aeqc"))
		ret = qm_eqc_aeqc_dump(qm, s, माप(काष्ठा qm_aeqc),
				       QM_MB_CMD_AEQC, "AEQC");
	अन्यथा अगर (!म_भेद(presult, "sq"))
		ret = qm_sq_dump(qm, s);
	अन्यथा अगर (!म_भेद(presult, "cq"))
		ret = qm_cq_dump(qm, s);
	अन्यथा अगर (!म_भेद(presult, "eq"))
		ret = qm_eq_aeq_dump(qm, s, माप(काष्ठा qm_eqe), "EQE");
	अन्यथा अगर (!म_भेद(presult, "aeq"))
		ret = qm_eq_aeq_dump(qm, s, माप(काष्ठा qm_aeqe), "AEQE");
	अन्यथा अगर (!म_भेद(presult, "help"))
		ret = qm_dbg_help(qm, s);
	अन्यथा
		ret = -EINVAL;

	अगर (ret)
		dev_info(dev, "Please echo help\n");

err_buffer_मुक्त:
	kमुक्त(s_पंचांगp);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार qm_cmd_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
			    माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा hisi_qm *qm = filp->निजी_data;
	अक्षर *cmd_buf, *cmd_buf_पंचांगp;
	पूर्णांक ret;

	अगर (*pos)
		वापस 0;

	/* Judge अगर the instance is being reset. */
	अगर (unlikely(atomic_पढ़ो(&qm->status.flags) == QM_STOP))
		वापस 0;

	अगर (count > QM_DBG_WRITE_LEN)
		वापस -ENOSPC;

	cmd_buf = kzalloc(count + 1, GFP_KERNEL);
	अगर (!cmd_buf)
		वापस -ENOMEM;

	अगर (copy_from_user(cmd_buf, buffer, count)) अणु
		kमुक्त(cmd_buf);
		वापस -EFAULT;
	पूर्ण

	cmd_buf[count] = '\0';

	cmd_buf_पंचांगp = म_अक्षर(cmd_buf, '\n');
	अगर (cmd_buf_पंचांगp) अणु
		*cmd_buf_पंचांगp = '\0';
		count = cmd_buf_पंचांगp - cmd_buf + 1;
	पूर्ण

	ret = qm_cmd_ग_लिखो_dump(qm, cmd_buf);
	अगर (ret) अणु
		kमुक्त(cmd_buf);
		वापस ret;
	पूर्ण

	kमुक्त(cmd_buf);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations qm_cmd_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = qm_cmd_पढ़ो,
	.ग_लिखो = qm_cmd_ग_लिखो,
पूर्ण;

अटल व्योम qm_create_debugfs_file(काष्ठा hisi_qm *qm, काष्ठा dentry *dir,
				   क्रमागत qm_debug_file index)
अणु
	काष्ठा debugfs_file *file = qm->debug.files + index;

	debugfs_create_file(qm_debug_file_name[index], 0600, dir, file,
			    &qm_debug_fops);

	file->index = index;
	mutex_init(&file->lock);
	file->debug = &qm->debug;
पूर्ण

अटल व्योम qm_hw_error_init_v1(काष्ठा hisi_qm *qm, u32 ce, u32 nfe, u32 fe)
अणु
	ग_लिखोl(QM_ABNORMAL_INT_MASK_VALUE, qm->io_base + QM_ABNORMAL_INT_MASK);
पूर्ण

अटल व्योम qm_hw_error_init_v2(काष्ठा hisi_qm *qm, u32 ce, u32 nfe, u32 fe)
अणु
	u32 irq_enable = ce | nfe | fe;
	u32 irq_unmask = ~irq_enable;

	qm->error_mask = ce | nfe | fe;

	/* clear QM hw residual error source */
	ग_लिखोl(QM_ABNORMAL_INT_SOURCE_CLR,
	       qm->io_base + QM_ABNORMAL_INT_SOURCE);

	/* configure error type */
	ग_लिखोl(ce, qm->io_base + QM_RAS_CE_ENABLE);
	ग_लिखोl(QM_RAS_CE_TIMES_PER_IRQ, qm->io_base + QM_RAS_CE_THRESHOLD);
	ग_लिखोl(nfe, qm->io_base + QM_RAS_NFE_ENABLE);
	ग_लिखोl(fe, qm->io_base + QM_RAS_FE_ENABLE);

	irq_unmask &= पढ़ोl(qm->io_base + QM_ABNORMAL_INT_MASK);
	ग_लिखोl(irq_unmask, qm->io_base + QM_ABNORMAL_INT_MASK);
पूर्ण

अटल व्योम qm_hw_error_uninit_v2(काष्ठा hisi_qm *qm)
अणु
	ग_लिखोl(QM_ABNORMAL_INT_MASK_VALUE, qm->io_base + QM_ABNORMAL_INT_MASK);
पूर्ण

अटल व्योम qm_log_hw_error(काष्ठा hisi_qm *qm, u32 error_status)
अणु
	स्थिर काष्ठा hisi_qm_hw_error *err;
	काष्ठा device *dev = &qm->pdev->dev;
	u32 reg_val, type, vf_num;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(qm_hw_error); i++) अणु
		err = &qm_hw_error[i];
		अगर (!(err->पूर्णांक_msk & error_status))
			जारी;

		dev_err(dev, "%s [error status=0x%x] found\n",
			err->msg, err->पूर्णांक_msk);

		अगर (err->पूर्णांक_msk & QM_DB_TIMEOUT) अणु
			reg_val = पढ़ोl(qm->io_base + QM_ABNORMAL_INF01);
			type = (reg_val & QM_DB_TIMEOUT_TYPE) >>
			       QM_DB_TIMEOUT_TYPE_SHIFT;
			vf_num = reg_val & QM_DB_TIMEOUT_VF;
			dev_err(dev, "qm %s doorbell timeout in function %u\n",
				qm_db_समयout[type], vf_num);
		पूर्ण अन्यथा अगर (err->पूर्णांक_msk & QM_OF_FIFO_OF) अणु
			reg_val = पढ़ोl(qm->io_base + QM_ABNORMAL_INF00);
			type = (reg_val & QM_FIFO_OVERFLOW_TYPE) >>
			       QM_FIFO_OVERFLOW_TYPE_SHIFT;
			vf_num = reg_val & QM_FIFO_OVERFLOW_VF;

			अगर (type < ARRAY_SIZE(qm_fअगरo_overflow))
				dev_err(dev, "qm %s fifo overflow in function %u\n",
					qm_fअगरo_overflow[type], vf_num);
			अन्यथा
				dev_err(dev, "unknown error type\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल क्रमागत acc_err_result qm_hw_error_handle_v2(काष्ठा hisi_qm *qm)
अणु
	u32 error_status, पंचांगp, val;

	/* पढ़ो err sts */
	पंचांगp = पढ़ोl(qm->io_base + QM_ABNORMAL_INT_STATUS);
	error_status = qm->error_mask & पंचांगp;

	अगर (error_status) अणु
		अगर (error_status & QM_ECC_MBIT)
			qm->err_status.is_qm_ecc_mbit = true;

		qm_log_hw_error(qm, error_status);
		val = error_status | QM_DB_RANDOM_INVALID | QM_BASE_CE;
		/* ce error करोes not need to be reset */
		अगर (val == (QM_DB_RANDOM_INVALID | QM_BASE_CE)) अणु
			ग_लिखोl(error_status, qm->io_base +
			       QM_ABNORMAL_INT_SOURCE);
			ग_लिखोl(qm->err_info.nfe,
			       qm->io_base + QM_RAS_NFE_ENABLE);
			वापस ACC_ERR_RECOVERED;
		पूर्ण

		वापस ACC_ERR_NEED_RESET;
	पूर्ण

	वापस ACC_ERR_RECOVERED;
पूर्ण

अटल पूर्णांक qm_stop_qp(काष्ठा hisi_qp *qp)
अणु
	वापस qm_mb(qp->qm, QM_MB_CMD_STOP_QP, 0, qp->qp_id, 0);
पूर्ण

अटल स्थिर काष्ठा hisi_qm_hw_ops qm_hw_ops_v1 = अणु
	.qm_db = qm_db_v1,
	.get_irq_num = qm_get_irq_num_v1,
	.hw_error_init = qm_hw_error_init_v1,
पूर्ण;

अटल स्थिर काष्ठा hisi_qm_hw_ops qm_hw_ops_v2 = अणु
	.get_vft = qm_get_vft_v2,
	.qm_db = qm_db_v2,
	.get_irq_num = qm_get_irq_num_v2,
	.hw_error_init = qm_hw_error_init_v2,
	.hw_error_uninit = qm_hw_error_uninit_v2,
	.hw_error_handle = qm_hw_error_handle_v2,
पूर्ण;

अटल स्थिर काष्ठा hisi_qm_hw_ops qm_hw_ops_v3 = अणु
	.get_vft = qm_get_vft_v2,
	.qm_db = qm_db_v2,
	.get_irq_num = qm_get_irq_num_v2,
	.hw_error_init = qm_hw_error_init_v2,
	.hw_error_uninit = qm_hw_error_uninit_v2,
	.hw_error_handle = qm_hw_error_handle_v2,
	.stop_qp = qm_stop_qp,
पूर्ण;

अटल व्योम *qm_get_avail_sqe(काष्ठा hisi_qp *qp)
अणु
	काष्ठा hisi_qp_status *qp_status = &qp->qp_status;
	u16 sq_tail = qp_status->sq_tail;

	अगर (unlikely(atomic_पढ़ो(&qp->qp_status.used) == QM_Q_DEPTH - 1))
		वापस शून्य;

	वापस qp->sqe + sq_tail * qp->qm->sqe_size;
पूर्ण

अटल काष्ठा hisi_qp *qm_create_qp_nolock(काष्ठा hisi_qm *qm, u8 alg_type)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा hisi_qp *qp;
	पूर्णांक qp_id;

	अगर (!qm_qp_avail_state(qm, शून्य, QP_INIT))
		वापस ERR_PTR(-EPERM);

	अगर (qm->qp_in_used == qm->qp_num) अणु
		dev_info_ratelimited(dev, "All %u queues of QM are busy!\n",
				     qm->qp_num);
		atomic64_inc(&qm->debug.dfx.create_qp_err_cnt);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	qp_id = idr_alloc_cyclic(&qm->qp_idr, शून्य, 0, qm->qp_num, GFP_ATOMIC);
	अगर (qp_id < 0) अणु
		dev_info_ratelimited(dev, "All %u queues of QM are busy!\n",
				    qm->qp_num);
		atomic64_inc(&qm->debug.dfx.create_qp_err_cnt);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	qp = &qm->qp_array[qp_id];

	स_रखो(qp->cqe, 0, माप(काष्ठा qm_cqe) * QM_Q_DEPTH);

	qp->event_cb = शून्य;
	qp->req_cb = शून्य;
	qp->qp_id = qp_id;
	qp->alg_type = alg_type;
	qp->is_in_kernel = true;
	qm->qp_in_used++;
	atomic_set(&qp->qp_status.flags, QP_INIT);

	वापस qp;
पूर्ण

/**
 * hisi_qm_create_qp() - Create a queue pair from qm.
 * @qm: The qm we create a qp from.
 * @alg_type: Accelerator specअगरic algorithm type in sqc.
 *
 * वापस created qp, -EBUSY अगर all qps in qm allocated, -ENOMEM अगर allocating
 * qp memory fails.
 */
काष्ठा hisi_qp *hisi_qm_create_qp(काष्ठा hisi_qm *qm, u8 alg_type)
अणु
	काष्ठा hisi_qp *qp;

	करोwn_ग_लिखो(&qm->qps_lock);
	qp = qm_create_qp_nolock(qm, alg_type);
	up_ग_लिखो(&qm->qps_lock);

	वापस qp;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_create_qp);

/**
 * hisi_qm_release_qp() - Release a qp back to its qm.
 * @qp: The qp we want to release.
 *
 * This function releases the resource of a qp.
 */
व्योम hisi_qm_release_qp(काष्ठा hisi_qp *qp)
अणु
	काष्ठा hisi_qm *qm = qp->qm;

	करोwn_ग_लिखो(&qm->qps_lock);

	अगर (!qm_qp_avail_state(qm, qp, QP_CLOSE)) अणु
		up_ग_लिखो(&qm->qps_lock);
		वापस;
	पूर्ण

	qm->qp_in_used--;
	idr_हटाओ(&qm->qp_idr, qp->qp_id);

	up_ग_लिखो(&qm->qps_lock);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_release_qp);

अटल पूर्णांक qm_sq_ctx_cfg(काष्ठा hisi_qp *qp, पूर्णांक qp_id, u32 pasid)
अणु
	काष्ठा hisi_qm *qm = qp->qm;
	काष्ठा device *dev = &qm->pdev->dev;
	क्रमागत qm_hw_ver ver = qm->ver;
	काष्ठा qm_sqc *sqc;
	dma_addr_t sqc_dma;
	पूर्णांक ret;

	sqc = kzalloc(माप(काष्ठा qm_sqc), GFP_KERNEL);
	अगर (!sqc)
		वापस -ENOMEM;

	INIT_QC_COMMON(sqc, qp->sqe_dma, pasid);
	अगर (ver == QM_HW_V1) अणु
		sqc->dw3 = cpu_to_le32(QM_MK_SQC_DW3_V1(0, 0, 0, qm->sqe_size));
		sqc->w8 = cpu_to_le16(QM_Q_DEPTH - 1);
	पूर्ण अन्यथा अणु
		sqc->dw3 = cpu_to_le32(QM_MK_SQC_DW3_V2(qm->sqe_size));
		sqc->w8 = 0; /* अक्रम_qc */
	पूर्ण
	sqc->cq_num = cpu_to_le16(qp_id);
	sqc->w13 = cpu_to_le16(QM_MK_SQC_W13(0, 1, qp->alg_type));

	अगर (ver >= QM_HW_V3 && qm->use_sva && !qp->is_in_kernel)
		sqc->w11 = cpu_to_le16(QM_QC_PASID_ENABLE <<
				       QM_QC_PASID_ENABLE_SHIFT);

	sqc_dma = dma_map_single(dev, sqc, माप(काष्ठा qm_sqc),
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, sqc_dma)) अणु
		kमुक्त(sqc);
		वापस -ENOMEM;
	पूर्ण

	ret = qm_mb(qm, QM_MB_CMD_SQC, sqc_dma, qp_id, 0);
	dma_unmap_single(dev, sqc_dma, माप(काष्ठा qm_sqc), DMA_TO_DEVICE);
	kमुक्त(sqc);

	वापस ret;
पूर्ण

अटल पूर्णांक qm_cq_ctx_cfg(काष्ठा hisi_qp *qp, पूर्णांक qp_id, u32 pasid)
अणु
	काष्ठा hisi_qm *qm = qp->qm;
	काष्ठा device *dev = &qm->pdev->dev;
	क्रमागत qm_hw_ver ver = qm->ver;
	काष्ठा qm_cqc *cqc;
	dma_addr_t cqc_dma;
	पूर्णांक ret;

	cqc = kzalloc(माप(काष्ठा qm_cqc), GFP_KERNEL);
	अगर (!cqc)
		वापस -ENOMEM;

	INIT_QC_COMMON(cqc, qp->cqe_dma, pasid);
	अगर (ver == QM_HW_V1) अणु
		cqc->dw3 = cpu_to_le32(QM_MK_CQC_DW3_V1(0, 0, 0,
							QM_QC_CQE_SIZE));
		cqc->w8 = cpu_to_le16(QM_Q_DEPTH - 1);
	पूर्ण अन्यथा अणु
		cqc->dw3 = cpu_to_le32(QM_MK_CQC_DW3_V2(QM_QC_CQE_SIZE));
		cqc->w8 = 0; /* अक्रम_qc */
	पूर्ण
	cqc->dw6 = cpu_to_le32(1 << QM_CQ_PHASE_SHIFT | 1 << QM_CQ_FLAG_SHIFT);

	अगर (ver >= QM_HW_V3 && qm->use_sva && !qp->is_in_kernel)
		cqc->w11 = cpu_to_le16(QM_QC_PASID_ENABLE);

	cqc_dma = dma_map_single(dev, cqc, माप(काष्ठा qm_cqc),
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, cqc_dma)) अणु
		kमुक्त(cqc);
		वापस -ENOMEM;
	पूर्ण

	ret = qm_mb(qm, QM_MB_CMD_CQC, cqc_dma, qp_id, 0);
	dma_unmap_single(dev, cqc_dma, माप(काष्ठा qm_cqc), DMA_TO_DEVICE);
	kमुक्त(cqc);

	वापस ret;
पूर्ण

अटल पूर्णांक qm_qp_ctx_cfg(काष्ठा hisi_qp *qp, पूर्णांक qp_id, u32 pasid)
अणु
	पूर्णांक ret;

	qm_init_qp_status(qp);

	ret = qm_sq_ctx_cfg(qp, qp_id, pasid);
	अगर (ret)
		वापस ret;

	वापस qm_cq_ctx_cfg(qp, qp_id, pasid);
पूर्ण

अटल पूर्णांक qm_start_qp_nolock(काष्ठा hisi_qp *qp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hisi_qm *qm = qp->qm;
	काष्ठा device *dev = &qm->pdev->dev;
	पूर्णांक qp_id = qp->qp_id;
	u32 pasid = arg;
	पूर्णांक ret;

	अगर (!qm_qp_avail_state(qm, qp, QP_START))
		वापस -EPERM;

	ret = qm_qp_ctx_cfg(qp, qp_id, pasid);
	अगर (ret)
		वापस ret;

	atomic_set(&qp->qp_status.flags, QP_START);
	dev_dbg(dev, "queue %d started\n", qp_id);

	वापस 0;
पूर्ण

/**
 * hisi_qm_start_qp() - Start a qp पूर्णांकo running.
 * @qp: The qp we want to start to run.
 * @arg: Accelerator specअगरic argument.
 *
 * After this function, qp can receive request from user. Return 0 अगर
 * successful, Return -EBUSY अगर failed.
 */
पूर्णांक hisi_qm_start_qp(काष्ठा hisi_qp *qp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hisi_qm *qm = qp->qm;
	पूर्णांक ret;

	करोwn_ग_लिखो(&qm->qps_lock);
	ret = qm_start_qp_nolock(qp, arg);
	up_ग_लिखो(&qm->qps_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_start_qp);

/**
 * qp_stop_fail_cb() - call request cb.
 * @qp: stopped failed qp.
 *
 * Callback function should be called whether task completed or not.
 */
अटल व्योम qp_stop_fail_cb(काष्ठा hisi_qp *qp)
अणु
	पूर्णांक qp_used = atomic_पढ़ो(&qp->qp_status.used);
	u16 cur_tail = qp->qp_status.sq_tail;
	u16 cur_head = (cur_tail + QM_Q_DEPTH - qp_used) % QM_Q_DEPTH;
	काष्ठा hisi_qm *qm = qp->qm;
	u16 pos;
	पूर्णांक i;

	क्रम (i = 0; i < qp_used; i++) अणु
		pos = (i + cur_head) % QM_Q_DEPTH;
		qp->req_cb(qp, qp->sqe + (u32)(qm->sqe_size * pos));
		atomic_dec(&qp->qp_status.used);
	पूर्ण
पूर्ण

/**
 * qm_drain_qp() - Drain a qp.
 * @qp: The qp we want to drain.
 *
 * Determine whether the queue is cleared by judging the tail poपूर्णांकers of
 * sq and cq.
 */
अटल पूर्णांक qm_drain_qp(काष्ठा hisi_qp *qp)
अणु
	माप_प्रकार size = माप(काष्ठा qm_sqc) + माप(काष्ठा qm_cqc);
	काष्ठा hisi_qm *qm = qp->qm;
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा qm_sqc *sqc;
	काष्ठा qm_cqc *cqc;
	dma_addr_t dma_addr;
	पूर्णांक ret = 0, i = 0;
	व्योम *addr;

	/*
	 * No need to judge अगर ECC multi-bit error occurs because the
	 * master OOO will be blocked.
	 */
	अगर (qm->err_status.is_qm_ecc_mbit || qm->err_status.is_dev_ecc_mbit)
		वापस 0;

	/* Kunpeng930 supports drain qp by device */
	अगर (qm->ops->stop_qp) अणु
		ret = qm->ops->stop_qp(qp);
		अगर (ret)
			dev_err(dev, "Failed to stop qp(%u)!\n", qp->qp_id);
		वापस ret;
	पूर्ण

	addr = qm_ctx_alloc(qm, size, &dma_addr);
	अगर (IS_ERR(addr)) अणु
		dev_err(dev, "Failed to alloc ctx for sqc and cqc!\n");
		वापस -ENOMEM;
	पूर्ण

	जबतक (++i) अणु
		ret = qm_dump_sqc_raw(qm, dma_addr, qp->qp_id);
		अगर (ret) अणु
			dev_err_ratelimited(dev, "Failed to dump sqc!\n");
			अवरोध;
		पूर्ण
		sqc = addr;

		ret = qm_dump_cqc_raw(qm, (dma_addr + माप(काष्ठा qm_sqc)),
				      qp->qp_id);
		अगर (ret) अणु
			dev_err_ratelimited(dev, "Failed to dump cqc!\n");
			अवरोध;
		पूर्ण
		cqc = addr + माप(काष्ठा qm_sqc);

		अगर ((sqc->tail == cqc->tail) &&
		    (QM_SQ_TAIL_IDX(sqc) == QM_CQ_TAIL_IDX(cqc)))
			अवरोध;

		अगर (i == MAX_WAIT_COUNTS) अणु
			dev_err(dev, "Fail to empty queue %u!\n", qp->qp_id);
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		usleep_range(WAIT_PERIOD_US_MIN, WAIT_PERIOD_US_MAX);
	पूर्ण

	qm_ctx_मुक्त(qm, size, addr, &dma_addr);

	वापस ret;
पूर्ण

अटल पूर्णांक qm_stop_qp_nolock(काष्ठा hisi_qp *qp)
अणु
	काष्ठा device *dev = &qp->qm->pdev->dev;
	पूर्णांक ret;

	/*
	 * It is allowed to stop and release qp when reset, If the qp is
	 * stopped when reset but still want to be released then, the
	 * is_resetting flag should be set negative so that this qp will not
	 * be restarted after reset.
	 */
	अगर (atomic_पढ़ो(&qp->qp_status.flags) == QP_STOP) अणु
		qp->is_resetting = false;
		वापस 0;
	पूर्ण

	अगर (!qm_qp_avail_state(qp->qm, qp, QP_STOP))
		वापस -EPERM;

	atomic_set(&qp->qp_status.flags, QP_STOP);

	ret = qm_drain_qp(qp);
	अगर (ret)
		dev_err(dev, "Failed to drain out data for stopping!\n");

	अगर (qp->qm->wq)
		flush_workqueue(qp->qm->wq);
	अन्यथा
		flush_work(&qp->qm->work);

	अगर (unlikely(qp->is_resetting && atomic_पढ़ो(&qp->qp_status.used)))
		qp_stop_fail_cb(qp);

	dev_dbg(dev, "stop queue %u!", qp->qp_id);

	वापस 0;
पूर्ण

/**
 * hisi_qm_stop_qp() - Stop a qp in qm.
 * @qp: The qp we want to stop.
 *
 * This function is reverse of hisi_qm_start_qp. Return 0 अगर successful.
 */
पूर्णांक hisi_qm_stop_qp(काष्ठा hisi_qp *qp)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&qp->qm->qps_lock);
	ret = qm_stop_qp_nolock(qp);
	up_ग_लिखो(&qp->qm->qps_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_stop_qp);

/**
 * hisi_qp_send() - Queue up a task in the hardware queue.
 * @qp: The qp in which to put the message.
 * @msg: The message.
 *
 * This function will वापस -EBUSY अगर qp is currently full, and -EAGAIN
 * अगर qp related qm is resetting.
 *
 * Note: This function may run with qm_irq_thपढ़ो and ACC reset at same समय.
 *       It has no race with qm_irq_thपढ़ो. However, during hisi_qp_send, ACC
 *       reset may happen, we have no lock here considering perक्रमmance. This
 *       causes current qm_db sending fail or can not receive sended sqe. QM
 *       sync/async receive function should handle the error sqe. ACC reset
 *       करोne function should clear used sqe to 0.
 */
पूर्णांक hisi_qp_send(काष्ठा hisi_qp *qp, स्थिर व्योम *msg)
अणु
	काष्ठा hisi_qp_status *qp_status = &qp->qp_status;
	u16 sq_tail = qp_status->sq_tail;
	u16 sq_tail_next = (sq_tail + 1) % QM_Q_DEPTH;
	व्योम *sqe = qm_get_avail_sqe(qp);

	अगर (unlikely(atomic_पढ़ो(&qp->qp_status.flags) == QP_STOP ||
		     atomic_पढ़ो(&qp->qm->status.flags) == QM_STOP ||
		     qp->is_resetting)) अणु
		dev_info_ratelimited(&qp->qm->pdev->dev, "QP is stopped or resetting\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (!sqe)
		वापस -EBUSY;

	स_नकल(sqe, msg, qp->qm->sqe_size);

	qm_db(qp->qm, qp->qp_id, QM_DOORBELL_CMD_SQ, sq_tail_next, 0);
	atomic_inc(&qp->qp_status.used);
	qp_status->sq_tail = sq_tail_next;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qp_send);

अटल व्योम hisi_qm_cache_wb(काष्ठा hisi_qm *qm)
अणु
	अचिन्हित पूर्णांक val;

	अगर (qm->ver == QM_HW_V1)
		वापस;

	ग_लिखोl(0x1, qm->io_base + QM_CACHE_WB_START);
	अगर (पढ़ोl_relaxed_poll_समयout(qm->io_base + QM_CACHE_WB_DONE,
				       val, val & BIT(0), POLL_PERIOD,
				       POLL_TIMEOUT))
		dev_err(&qm->pdev->dev, "QM writeback sqc cache fail!\n");
पूर्ण

अटल व्योम qm_qp_event_notअगरier(काष्ठा hisi_qp *qp)
अणु
	wake_up_पूर्णांकerruptible(&qp->uacce_q->रुको);
पूर्ण

अटल पूर्णांक hisi_qm_get_available_instances(काष्ठा uacce_device *uacce)
अणु
	वापस hisi_qm_get_मुक्त_qp_num(uacce->priv);
पूर्ण

अटल पूर्णांक hisi_qm_uacce_get_queue(काष्ठा uacce_device *uacce,
				   अचिन्हित दीर्घ arg,
				   काष्ठा uacce_queue *q)
अणु
	काष्ठा hisi_qm *qm = uacce->priv;
	काष्ठा hisi_qp *qp;
	u8 alg_type = 0;

	qp = hisi_qm_create_qp(qm, alg_type);
	अगर (IS_ERR(qp))
		वापस PTR_ERR(qp);

	q->priv = qp;
	q->uacce = uacce;
	qp->uacce_q = q;
	qp->event_cb = qm_qp_event_notअगरier;
	qp->pasid = arg;
	qp->is_in_kernel = false;

	वापस 0;
पूर्ण

अटल व्योम hisi_qm_uacce_put_queue(काष्ठा uacce_queue *q)
अणु
	काष्ठा hisi_qp *qp = q->priv;

	hisi_qm_cache_wb(qp->qm);
	hisi_qm_release_qp(qp);
पूर्ण

/* map sq/cq/करोorbell to user space */
अटल पूर्णांक hisi_qm_uacce_mmap(काष्ठा uacce_queue *q,
			      काष्ठा vm_area_काष्ठा *vma,
			      काष्ठा uacce_qfile_region *qfr)
अणु
	काष्ठा hisi_qp *qp = q->priv;
	काष्ठा hisi_qm *qm = qp->qm;
	resource_माप_प्रकार phys_base = qm->db_phys_base +
				    qp->qp_id * qm->db_पूर्णांकerval;
	माप_प्रकार sz = vma->vm_end - vma->vm_start;
	काष्ठा pci_dev *pdev = qm->pdev;
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित दीर्घ vm_pgoff;
	पूर्णांक ret;

	चयन (qfr->type) अणु
	हाल UACCE_QFRT_MMIO:
		अगर (qm->ver == QM_HW_V1) अणु
			अगर (sz > PAGE_SIZE * QM_DOORBELL_PAGE_NR)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (qm->ver == QM_HW_V2 || !qm->use_db_isolation) अणु
			अगर (sz > PAGE_SIZE * (QM_DOORBELL_PAGE_NR +
			    QM_DOORBELL_SQ_CQ_BASE_V2 / PAGE_SIZE))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (sz > qm->db_पूर्णांकerval)
				वापस -EINVAL;
		पूर्ण

		vma->vm_flags |= VM_IO;

		वापस remap_pfn_range(vma, vma->vm_start,
				       phys_base >> PAGE_SHIFT,
				       sz, pgprot_noncached(vma->vm_page_prot));
	हाल UACCE_QFRT_DUS:
		अगर (sz != qp->qdma.size)
			वापस -EINVAL;

		/*
		 * dma_mmap_coherent() requires vm_pgoff as 0
		 * restore vm_pfoff to initial value क्रम mmap()
		 */
		vm_pgoff = vma->vm_pgoff;
		vma->vm_pgoff = 0;
		ret = dma_mmap_coherent(dev, vma, qp->qdma.va,
					qp->qdma.dma, sz);
		vma->vm_pgoff = vm_pgoff;
		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_qm_uacce_start_queue(काष्ठा uacce_queue *q)
अणु
	काष्ठा hisi_qp *qp = q->priv;

	वापस hisi_qm_start_qp(qp, qp->pasid);
पूर्ण

अटल व्योम hisi_qm_uacce_stop_queue(काष्ठा uacce_queue *q)
अणु
	hisi_qm_stop_qp(q->priv);
पूर्ण

अटल व्योम qm_set_sqctype(काष्ठा uacce_queue *q, u16 type)
अणु
	काष्ठा hisi_qm *qm = q->uacce->priv;
	काष्ठा hisi_qp *qp = q->priv;

	करोwn_ग_लिखो(&qm->qps_lock);
	qp->alg_type = type;
	up_ग_लिखो(&qm->qps_lock);
पूर्ण

अटल दीर्घ hisi_qm_uacce_ioctl(काष्ठा uacce_queue *q, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा hisi_qp *qp = q->priv;
	काष्ठा hisi_qp_ctx qp_ctx;

	अगर (cmd == UACCE_CMD_QM_SET_QP_CTX) अणु
		अगर (copy_from_user(&qp_ctx, (व्योम __user *)arg,
				   माप(काष्ठा hisi_qp_ctx)))
			वापस -EFAULT;

		अगर (qp_ctx.qc_type != 0 && qp_ctx.qc_type != 1)
			वापस -EINVAL;

		qm_set_sqctype(q, qp_ctx.qc_type);
		qp_ctx.id = qp->qp_id;

		अगर (copy_to_user((व्योम __user *)arg, &qp_ctx,
				 माप(काष्ठा hisi_qp_ctx)))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uacce_ops uacce_qm_ops = अणु
	.get_available_instances = hisi_qm_get_available_instances,
	.get_queue = hisi_qm_uacce_get_queue,
	.put_queue = hisi_qm_uacce_put_queue,
	.start_queue = hisi_qm_uacce_start_queue,
	.stop_queue = hisi_qm_uacce_stop_queue,
	.mmap = hisi_qm_uacce_mmap,
	.ioctl = hisi_qm_uacce_ioctl,
पूर्ण;

अटल पूर्णांक qm_alloc_uacce(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	काष्ठा uacce_device *uacce;
	अचिन्हित दीर्घ mmio_page_nr;
	अचिन्हित दीर्घ dus_page_nr;
	काष्ठा uacce_पूर्णांकerface पूर्णांकerface = अणु
		.flags = UACCE_DEV_SVA,
		.ops = &uacce_qm_ops,
	पूर्ण;
	पूर्णांक ret;

	ret = strscpy(पूर्णांकerface.name, pdev->driver->name,
		      माप(पूर्णांकerface.name));
	अगर (ret < 0)
		वापस -ENAMETOOLONG;

	uacce = uacce_alloc(&pdev->dev, &पूर्णांकerface);
	अगर (IS_ERR(uacce))
		वापस PTR_ERR(uacce);

	अगर (uacce->flags & UACCE_DEV_SVA && qm->mode == UACCE_MODE_SVA) अणु
		qm->use_sva = true;
	पूर्ण अन्यथा अणु
		/* only consider sva हाल */
		uacce_हटाओ(uacce);
		qm->uacce = शून्य;
		वापस -EINVAL;
	पूर्ण

	uacce->is_vf = pdev->is_virtfn;
	uacce->priv = qm;
	uacce->algs = qm->algs;

	अगर (qm->ver == QM_HW_V1)
		uacce->api_ver = HISI_QM_API_VER_BASE;
	अन्यथा अगर (qm->ver == QM_HW_V2)
		uacce->api_ver = HISI_QM_API_VER2_BASE;
	अन्यथा
		uacce->api_ver = HISI_QM_API_VER3_BASE;

	अगर (qm->ver == QM_HW_V1)
		mmio_page_nr = QM_DOORBELL_PAGE_NR;
	अन्यथा अगर (qm->ver == QM_HW_V2 || !qm->use_db_isolation)
		mmio_page_nr = QM_DOORBELL_PAGE_NR +
			QM_DOORBELL_SQ_CQ_BASE_V2 / PAGE_SIZE;
	अन्यथा
		mmio_page_nr = qm->db_पूर्णांकerval / PAGE_SIZE;

	dus_page_nr = (PAGE_SIZE - 1 + qm->sqe_size * QM_Q_DEPTH +
		       माप(काष्ठा qm_cqe) * QM_Q_DEPTH) >> PAGE_SHIFT;

	uacce->qf_pg_num[UACCE_QFRT_MMIO] = mmio_page_nr;
	uacce->qf_pg_num[UACCE_QFRT_DUS]  = dus_page_nr;

	qm->uacce = uacce;

	वापस 0;
पूर्ण

/**
 * qm_frozen() - Try to froze QM to cut continuous queue request. If
 * there is user on the QM, वापस failure without करोing anything.
 * @qm: The qm needed to be fronzen.
 *
 * This function frozes QM, then we can करो SRIOV disabling.
 */
अटल पूर्णांक qm_frozen(काष्ठा hisi_qm *qm)
अणु
	अगर (test_bit(QM_DRIVER_REMOVING, &qm->misc_ctl))
		वापस 0;

	करोwn_ग_लिखो(&qm->qps_lock);

	अगर (!qm->qp_in_used) अणु
		qm->qp_in_used = qm->qp_num;
		up_ग_लिखो(&qm->qps_lock);
		set_bit(QM_DRIVER_REMOVING, &qm->misc_ctl);
		वापस 0;
	पूर्ण

	up_ग_लिखो(&qm->qps_lock);

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक qm_try_frozen_vfs(काष्ठा pci_dev *pdev,
			     काष्ठा hisi_qm_list *qm_list)
अणु
	काष्ठा hisi_qm *qm, *vf_qm;
	काष्ठा pci_dev *dev;
	पूर्णांक ret = 0;

	अगर (!qm_list || !pdev)
		वापस -EINVAL;

	/* Try to frozen all the VFs as disable SRIOV */
	mutex_lock(&qm_list->lock);
	list_क्रम_each_entry(qm, &qm_list->list, list) अणु
		dev = qm->pdev;
		अगर (dev == pdev)
			जारी;
		अगर (pci_physfn(dev) == pdev) अणु
			vf_qm = pci_get_drvdata(dev);
			ret = qm_frozen(vf_qm);
			अगर (ret)
				जाओ frozen_fail;
		पूर्ण
	पूर्ण

frozen_fail:
	mutex_unlock(&qm_list->lock);

	वापस ret;
पूर्ण

/**
 * hisi_qm_रुको_task_finish() - Wait until the task is finished
 * when removing the driver.
 * @qm: The qm needed to रुको क्रम the task to finish.
 * @qm_list: The list of all available devices.
 */
व्योम hisi_qm_रुको_task_finish(काष्ठा hisi_qm *qm, काष्ठा hisi_qm_list *qm_list)
अणु
	जबतक (qm_frozen(qm) ||
	       ((qm->fun_type == QM_HW_PF) &&
	       qm_try_frozen_vfs(qm->pdev, qm_list))) अणु
		msleep(WAIT_PERIOD);
	पूर्ण

	जबतक (test_bit(QM_RST_SCHED, &qm->misc_ctl) ||
	       test_bit(QM_RESETTING, &qm->misc_ctl))
		msleep(WAIT_PERIOD);

	udelay(REMOVE_WAIT_DELAY);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_रुको_task_finish);

/**
 * hisi_qm_get_मुक्त_qp_num() - Get मुक्त number of qp in qm.
 * @qm: The qm which want to get मुक्त qp.
 *
 * This function वापस मुक्त number of qp in qm.
 */
पूर्णांक hisi_qm_get_मुक्त_qp_num(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक ret;

	करोwn_पढ़ो(&qm->qps_lock);
	ret = qm->qp_num - qm->qp_in_used;
	up_पढ़ो(&qm->qps_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_get_मुक्त_qp_num);

अटल व्योम hisi_qp_memory_uninit(काष्ठा hisi_qm *qm, पूर्णांक num)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा qm_dma *qdma;
	पूर्णांक i;

	क्रम (i = num - 1; i >= 0; i--) अणु
		qdma = &qm->qp_array[i].qdma;
		dma_मुक्त_coherent(dev, qdma->size, qdma->va, qdma->dma);
	पूर्ण

	kमुक्त(qm->qp_array);
पूर्ण

अटल पूर्णांक hisi_qp_memory_init(काष्ठा hisi_qm *qm, माप_प्रकार dma_size, पूर्णांक id)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	माप_प्रकार off = qm->sqe_size * QM_Q_DEPTH;
	काष्ठा hisi_qp *qp;

	qp = &qm->qp_array[id];
	qp->qdma.va = dma_alloc_coherent(dev, dma_size, &qp->qdma.dma,
					 GFP_KERNEL);
	अगर (!qp->qdma.va)
		वापस -ENOMEM;

	qp->sqe = qp->qdma.va;
	qp->sqe_dma = qp->qdma.dma;
	qp->cqe = qp->qdma.va + off;
	qp->cqe_dma = qp->qdma.dma + off;
	qp->qdma.size = dma_size;
	qp->qm = qm;
	qp->qp_id = id;

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_qm_memory_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	माप_प्रकार qp_dma_size, off = 0;
	पूर्णांक i, ret = 0;

#घोषणा QM_INIT_BUF(qm, type, num) करो अणु \
	(qm)->type = ((qm)->qdma.va + (off)); \
	(qm)->type##_dma = (qm)->qdma.dma + (off); \
	off += QMC_ALIGN(माप(काष्ठा qm_##type) * (num)); \
पूर्ण जबतक (0)

	idr_init(&qm->qp_idr);
	qm->qdma.size = QMC_ALIGN(माप(काष्ठा qm_eqe) * QM_EQ_DEPTH) +
			QMC_ALIGN(माप(काष्ठा qm_aeqe) * QM_Q_DEPTH) +
			QMC_ALIGN(माप(काष्ठा qm_sqc) * qm->qp_num) +
			QMC_ALIGN(माप(काष्ठा qm_cqc) * qm->qp_num);
	qm->qdma.va = dma_alloc_coherent(dev, qm->qdma.size, &qm->qdma.dma,
					 GFP_ATOMIC);
	dev_dbg(dev, "allocate qm dma buf size=%zx)\n", qm->qdma.size);
	अगर (!qm->qdma.va)
		वापस -ENOMEM;

	QM_INIT_BUF(qm, eqe, QM_EQ_DEPTH);
	QM_INIT_BUF(qm, aeqe, QM_Q_DEPTH);
	QM_INIT_BUF(qm, sqc, qm->qp_num);
	QM_INIT_BUF(qm, cqc, qm->qp_num);

	qm->qp_array = kसुस्मृति(qm->qp_num, माप(काष्ठा hisi_qp), GFP_KERNEL);
	अगर (!qm->qp_array) अणु
		ret = -ENOMEM;
		जाओ err_alloc_qp_array;
	पूर्ण

	/* one more page क्रम device or qp statuses */
	qp_dma_size = qm->sqe_size * QM_Q_DEPTH +
		      माप(काष्ठा qm_cqe) * QM_Q_DEPTH;
	qp_dma_size = PAGE_ALIGN(qp_dma_size);
	क्रम (i = 0; i < qm->qp_num; i++) अणु
		ret = hisi_qp_memory_init(qm, qp_dma_size, i);
		अगर (ret)
			जाओ err_init_qp_mem;

		dev_dbg(dev, "allocate qp dma buf size=%zx)\n", qp_dma_size);
	पूर्ण

	वापस ret;

err_init_qp_mem:
	hisi_qp_memory_uninit(qm, i);
err_alloc_qp_array:
	dma_मुक्त_coherent(dev, qm->qdma.size, qm->qdma.va, qm->qdma.dma);

	वापस ret;
पूर्ण

अटल व्योम hisi_qm_pre_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;

	अगर (qm->ver == QM_HW_V1)
		qm->ops = &qm_hw_ops_v1;
	अन्यथा अगर (qm->ver == QM_HW_V2)
		qm->ops = &qm_hw_ops_v2;
	अन्यथा
		qm->ops = &qm_hw_ops_v3;

	pci_set_drvdata(pdev, qm);
	mutex_init(&qm->mailbox_lock);
	init_rwsem(&qm->qps_lock);
	qm->qp_in_used = 0;
	qm->misc_ctl = false;
पूर्ण

अटल व्योम qm_put_pci_res(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;

	अगर (qm->use_db_isolation)
		iounmap(qm->db_io_base);

	iounmap(qm->io_base);
	pci_release_mem_regions(pdev);
पूर्ण

अटल व्योम hisi_qm_pci_uninit(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;

	pci_मुक्त_irq_vectors(pdev);
	qm_put_pci_res(qm);
	pci_disable_device(pdev);
पूर्ण

/**
 * hisi_qm_uninit() - Uninitialize qm.
 * @qm: The qm needed uninit.
 *
 * This function uninits qm related device resources.
 */
व्योम hisi_qm_uninit(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	काष्ठा device *dev = &pdev->dev;

	करोwn_ग_लिखो(&qm->qps_lock);

	अगर (!qm_avail_state(qm, QM_CLOSE)) अणु
		up_ग_लिखो(&qm->qps_lock);
		वापस;
	पूर्ण

	hisi_qp_memory_uninit(qm, qm->qp_num);
	idr_destroy(&qm->qp_idr);

	अगर (qm->qdma.va) अणु
		hisi_qm_cache_wb(qm);
		dma_मुक्त_coherent(dev, qm->qdma.size,
				  qm->qdma.va, qm->qdma.dma);
	पूर्ण

	qm_irq_unरेजिस्टर(qm);
	hisi_qm_pci_uninit(qm);
	uacce_हटाओ(qm->uacce);
	qm->uacce = शून्य;

	up_ग_लिखो(&qm->qps_lock);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_uninit);

/**
 * hisi_qm_get_vft() - Get vft from a qm.
 * @qm: The qm we want to get its vft.
 * @base: The base number of queue in vft.
 * @number: The number of queues in vft.
 *
 * We can allocate multiple queues to a qm by configuring भव function
 * table. We get related configures by this function. Normally, we call this
 * function in VF driver to get the queue inक्रमmation.
 *
 * qm hw v1 करोes not support this पूर्णांकerface.
 */
पूर्णांक hisi_qm_get_vft(काष्ठा hisi_qm *qm, u32 *base, u32 *number)
अणु
	अगर (!base || !number)
		वापस -EINVAL;

	अगर (!qm->ops->get_vft) अणु
		dev_err(&qm->pdev->dev, "Don't support vft read!\n");
		वापस -EINVAL;
	पूर्ण

	वापस qm->ops->get_vft(qm, base, number);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_get_vft);

/**
 * hisi_qm_set_vft() - Set vft to a qm.
 * @qm: The qm we want to set its vft.
 * @fun_num: The function number.
 * @base: The base number of queue in vft.
 * @number: The number of queues in vft.
 *
 * This function is alway called in PF driver, it is used to assign queues
 * among PF and VFs.
 *
 * Assign queues A~B to PF: hisi_qm_set_vft(qm, 0, A, B - A + 1)
 * Assign queues A~B to VF: hisi_qm_set_vft(qm, 2, A, B - A + 1)
 * (VF function number 0x2)
 */
अटल पूर्णांक hisi_qm_set_vft(काष्ठा hisi_qm *qm, u32 fun_num, u32 base,
		    u32 number)
अणु
	u32 max_q_num = qm->ctrl_qp_num;

	अगर (base >= max_q_num || number > max_q_num ||
	    (base + number) > max_q_num)
		वापस -EINVAL;

	वापस qm_set_sqc_cqc_vft(qm, fun_num, base, number);
पूर्ण

अटल व्योम qm_init_eq_aeq_status(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hisi_qm_status *status = &qm->status;

	status->eq_head = 0;
	status->aeq_head = 0;
	status->eqc_phase = true;
	status->aeqc_phase = true;
पूर्ण

अटल पूर्णांक qm_eq_ctx_cfg(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा qm_eqc *eqc;
	dma_addr_t eqc_dma;
	पूर्णांक ret;

	eqc = kzalloc(माप(काष्ठा qm_eqc), GFP_KERNEL);
	अगर (!eqc)
		वापस -ENOMEM;

	eqc->base_l = cpu_to_le32(lower_32_bits(qm->eqe_dma));
	eqc->base_h = cpu_to_le32(upper_32_bits(qm->eqe_dma));
	अगर (qm->ver == QM_HW_V1)
		eqc->dw3 = cpu_to_le32(QM_EQE_AEQE_SIZE);
	eqc->dw6 = cpu_to_le32((QM_EQ_DEPTH - 1) | (1 << QM_EQC_PHASE_SHIFT));

	eqc_dma = dma_map_single(dev, eqc, माप(काष्ठा qm_eqc),
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, eqc_dma)) अणु
		kमुक्त(eqc);
		वापस -ENOMEM;
	पूर्ण

	ret = qm_mb(qm, QM_MB_CMD_EQC, eqc_dma, 0, 0);
	dma_unmap_single(dev, eqc_dma, माप(काष्ठा qm_eqc), DMA_TO_DEVICE);
	kमुक्त(eqc);

	वापस ret;
पूर्ण

अटल पूर्णांक qm_aeq_ctx_cfg(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा qm_aeqc *aeqc;
	dma_addr_t aeqc_dma;
	पूर्णांक ret;

	aeqc = kzalloc(माप(काष्ठा qm_aeqc), GFP_KERNEL);
	अगर (!aeqc)
		वापस -ENOMEM;

	aeqc->base_l = cpu_to_le32(lower_32_bits(qm->aeqe_dma));
	aeqc->base_h = cpu_to_le32(upper_32_bits(qm->aeqe_dma));
	aeqc->dw6 = cpu_to_le32((QM_Q_DEPTH - 1) | (1 << QM_EQC_PHASE_SHIFT));

	aeqc_dma = dma_map_single(dev, aeqc, माप(काष्ठा qm_aeqc),
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, aeqc_dma)) अणु
		kमुक्त(aeqc);
		वापस -ENOMEM;
	पूर्ण

	ret = qm_mb(qm, QM_MB_CMD_AEQC, aeqc_dma, 0, 0);
	dma_unmap_single(dev, aeqc_dma, माप(काष्ठा qm_aeqc), DMA_TO_DEVICE);
	kमुक्त(aeqc);

	वापस ret;
पूर्ण

अटल पूर्णांक qm_eq_aeq_ctx_cfg(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	पूर्णांक ret;

	qm_init_eq_aeq_status(qm);

	ret = qm_eq_ctx_cfg(qm);
	अगर (ret) अणु
		dev_err(dev, "Set eqc failed!\n");
		वापस ret;
	पूर्ण

	वापस qm_aeq_ctx_cfg(qm);
पूर्ण

अटल पूर्णांक __hisi_qm_start(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक ret;

	WARN_ON(!qm->qdma.va);

	अगर (qm->fun_type == QM_HW_PF) अणु
		ret = qm_dev_mem_reset(qm);
		अगर (ret)
			वापस ret;

		ret = hisi_qm_set_vft(qm, 0, qm->qp_base, qm->qp_num);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = qm_eq_aeq_ctx_cfg(qm);
	अगर (ret)
		वापस ret;

	ret = qm_mb(qm, QM_MB_CMD_SQC_BT, qm->sqc_dma, 0, 0);
	अगर (ret)
		वापस ret;

	ret = qm_mb(qm, QM_MB_CMD_CQC_BT, qm->cqc_dma, 0, 0);
	अगर (ret)
		वापस ret;

	ग_लिखोl(0x0, qm->io_base + QM_VF_EQ_INT_MASK);
	ग_लिखोl(0x0, qm->io_base + QM_VF_AEQ_INT_MASK);

	वापस 0;
पूर्ण

/**
 * hisi_qm_start() - start qm
 * @qm: The qm to be started.
 *
 * This function starts a qm, then we can allocate qp from this qm.
 */
पूर्णांक hisi_qm_start(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	पूर्णांक ret = 0;

	करोwn_ग_लिखो(&qm->qps_lock);

	अगर (!qm_avail_state(qm, QM_START)) अणु
		up_ग_लिखो(&qm->qps_lock);
		वापस -EPERM;
	पूर्ण

	dev_dbg(dev, "qm start with %u queue pairs\n", qm->qp_num);

	अगर (!qm->qp_num) अणु
		dev_err(dev, "qp_num should not be 0\n");
		ret = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	ret = __hisi_qm_start(qm);
	अगर (!ret)
		atomic_set(&qm->status.flags, QM_START);

err_unlock:
	up_ग_लिखो(&qm->qps_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_start);

अटल पूर्णांक qm_restart(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा hisi_qp *qp;
	पूर्णांक ret, i;

	ret = hisi_qm_start(qm);
	अगर (ret < 0)
		वापस ret;

	करोwn_ग_लिखो(&qm->qps_lock);
	क्रम (i = 0; i < qm->qp_num; i++) अणु
		qp = &qm->qp_array[i];
		अगर (atomic_पढ़ो(&qp->qp_status.flags) == QP_STOP &&
		    qp->is_resetting == true) अणु
			ret = qm_start_qp_nolock(qp, 0);
			अगर (ret < 0) अणु
				dev_err(dev, "Failed to start qp%d!\n", i);

				up_ग_लिखो(&qm->qps_lock);
				वापस ret;
			पूर्ण
			qp->is_resetting = false;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&qm->qps_lock);

	वापस 0;
पूर्ण

/* Stop started qps in reset flow */
अटल पूर्णांक qm_stop_started_qp(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा hisi_qp *qp;
	पूर्णांक i, ret;

	क्रम (i = 0; i < qm->qp_num; i++) अणु
		qp = &qm->qp_array[i];
		अगर (qp && atomic_पढ़ो(&qp->qp_status.flags) == QP_START) अणु
			qp->is_resetting = true;
			ret = qm_stop_qp_nolock(qp);
			अगर (ret < 0) अणु
				dev_err(dev, "Failed to stop qp%d!\n", i);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/**
 * qm_clear_queues() - Clear all queues memory in a qm.
 * @qm: The qm in which the queues will be cleared.
 *
 * This function clears all queues memory in a qm. Reset of accelerator can
 * use this to clear queues.
 */
अटल व्योम qm_clear_queues(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hisi_qp *qp;
	पूर्णांक i;

	क्रम (i = 0; i < qm->qp_num; i++) अणु
		qp = &qm->qp_array[i];
		अगर (qp->is_resetting)
			स_रखो(qp->qdma.va, 0, qp->qdma.size);
	पूर्ण

	स_रखो(qm->qdma.va, 0, qm->qdma.size);
पूर्ण

/**
 * hisi_qm_stop() - Stop a qm.
 * @qm: The qm which will be stopped.
 * @r: The reason to stop qm.
 *
 * This function stops qm and its qps, then qm can not accept request.
 * Related resources are not released at this state, we can use hisi_qm_start
 * to let qm start again.
 */
पूर्णांक hisi_qm_stop(काष्ठा hisi_qm *qm, क्रमागत qm_stop_reason r)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	पूर्णांक ret = 0;

	करोwn_ग_लिखो(&qm->qps_lock);

	qm->status.stop_reason = r;
	अगर (!qm_avail_state(qm, QM_STOP)) अणु
		ret = -EPERM;
		जाओ err_unlock;
	पूर्ण

	अगर (qm->status.stop_reason == QM_SOFT_RESET ||
	    qm->status.stop_reason == QM_FLR) अणु
		ret = qm_stop_started_qp(qm);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to stop started qp!\n");
			जाओ err_unlock;
		पूर्ण
	पूर्ण

	/* Mask eq and aeq irq */
	ग_लिखोl(0x1, qm->io_base + QM_VF_EQ_INT_MASK);
	ग_लिखोl(0x1, qm->io_base + QM_VF_AEQ_INT_MASK);

	अगर (qm->fun_type == QM_HW_PF) अणु
		ret = hisi_qm_set_vft(qm, 0, 0, 0);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to set vft!\n");
			ret = -EBUSY;
			जाओ err_unlock;
		पूर्ण
	पूर्ण

	qm_clear_queues(qm);
	atomic_set(&qm->status.flags, QM_STOP);

err_unlock:
	up_ग_लिखो(&qm->qps_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_stop);

अटल sमाप_प्रकार qm_status_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
			      माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा hisi_qm *qm = filp->निजी_data;
	अक्षर buf[QM_DBG_READ_LEN];
	पूर्णांक val, len;

	val = atomic_पढ़ो(&qm->status.flags);
	len = scnम_लिखो(buf, QM_DBG_READ_LEN, "%s\n", qm_s[val]);

	वापस simple_पढ़ो_from_buffer(buffer, count, pos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations qm_status_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = qm_status_पढ़ो,
पूर्ण;

अटल पूर्णांक qm_debugfs_atomic64_set(व्योम *data, u64 val)
अणु
	अगर (val)
		वापस -EINVAL;

	atomic64_set((atomic64_t *)data, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक qm_debugfs_atomic64_get(व्योम *data, u64 *val)
अणु
	*val = atomic64_पढ़ो((atomic64_t *)data);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(qm_atomic64_ops, qm_debugfs_atomic64_get,
			 qm_debugfs_atomic64_set, "%llu\n");

/**
 * hisi_qm_debug_init() - Initialize qm related debugfs files.
 * @qm: The qm क्रम which we want to add debugfs files.
 *
 * Create qm related debugfs files.
 */
व्योम hisi_qm_debug_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा qm_dfx *dfx = &qm->debug.dfx;
	काष्ठा dentry *qm_d;
	व्योम *data;
	पूर्णांक i;

	qm_d = debugfs_create_dir("qm", qm->debug.debug_root);
	qm->debug.qm_d = qm_d;

	/* only show this in PF */
	अगर (qm->fun_type == QM_HW_PF) अणु
		qm_create_debugfs_file(qm, qm->debug.debug_root, CURRENT_QM);
		क्रम (i = CURRENT_Q; i < DEBUG_खाता_NUM; i++)
			qm_create_debugfs_file(qm, qm_d, i);
	पूर्ण

	debugfs_create_file("regs", 0444, qm->debug.qm_d, qm, &qm_regs_fops);

	debugfs_create_file("cmd", 0444, qm->debug.qm_d, qm, &qm_cmd_fops);

	debugfs_create_file("status", 0444, qm->debug.qm_d, qm,
			&qm_status_fops);
	क्रम (i = 0; i < ARRAY_SIZE(qm_dfx_files); i++) अणु
		data = (atomic64_t *)((uपूर्णांकptr_t)dfx + qm_dfx_files[i].offset);
		debugfs_create_file(qm_dfx_files[i].name,
			0644,
			qm_d,
			data,
			&qm_atomic64_ops);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_debug_init);

/**
 * hisi_qm_debug_regs_clear() - clear qm debug related रेजिस्टरs.
 * @qm: The qm क्रम which we want to clear its debug रेजिस्टरs.
 */
व्योम hisi_qm_debug_regs_clear(काष्ठा hisi_qm *qm)
अणु
	काष्ठा qm_dfx_रेजिस्टरs *regs;
	पूर्णांक i;

	/* clear current_qm */
	ग_लिखोl(0x0, qm->io_base + QM_DFX_MB_CNT_VF);
	ग_लिखोl(0x0, qm->io_base + QM_DFX_DB_CNT_VF);

	/* clear current_q */
	ग_लिखोl(0x0, qm->io_base + QM_DFX_SQE_CNT_VF_SQN);
	ग_लिखोl(0x0, qm->io_base + QM_DFX_CQE_CNT_VF_CQN);

	/*
	 * these रेजिस्टरs are पढ़ोing and clearing, so clear them after
	 * पढ़ोing them.
	 */
	ग_लिखोl(0x1, qm->io_base + QM_DFX_CNT_CLR_CE);

	regs = qm_dfx_regs;
	क्रम (i = 0; i < CNT_CYC_REGS_NUM; i++) अणु
		पढ़ोl(qm->io_base + regs->reg_offset);
		regs++;
	पूर्ण

	ग_लिखोl(0x0, qm->io_base + QM_DFX_CNT_CLR_CE);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_debug_regs_clear);

अटल व्योम qm_hw_error_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hisi_qm_err_info *err_info = &qm->err_info;

	अगर (!qm->ops->hw_error_init) अणु
		dev_err(&qm->pdev->dev, "QM doesn't support hw error handling!\n");
		वापस;
	पूर्ण

	qm->ops->hw_error_init(qm, err_info->ce, err_info->nfe, err_info->fe);
पूर्ण

अटल व्योम qm_hw_error_uninit(काष्ठा hisi_qm *qm)
अणु
	अगर (!qm->ops->hw_error_uninit) अणु
		dev_err(&qm->pdev->dev, "Unexpected QM hw error uninit!\n");
		वापस;
	पूर्ण

	qm->ops->hw_error_uninit(qm);
पूर्ण

अटल क्रमागत acc_err_result qm_hw_error_handle(काष्ठा hisi_qm *qm)
अणु
	अगर (!qm->ops->hw_error_handle) अणु
		dev_err(&qm->pdev->dev, "QM doesn't support hw error report!\n");
		वापस ACC_ERR_NONE;
	पूर्ण

	वापस qm->ops->hw_error_handle(qm);
पूर्ण

/**
 * hisi_qm_dev_err_init() - Initialize device error configuration.
 * @qm: The qm क्रम which we want to करो error initialization.
 *
 * Initialize QM and device error related configuration.
 */
व्योम hisi_qm_dev_err_init(काष्ठा hisi_qm *qm)
अणु
	अगर (qm->fun_type == QM_HW_VF)
		वापस;

	qm_hw_error_init(qm);

	अगर (!qm->err_ini->hw_err_enable) अणु
		dev_err(&qm->pdev->dev, "Device doesn't support hw error init!\n");
		वापस;
	पूर्ण
	qm->err_ini->hw_err_enable(qm);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_dev_err_init);

/**
 * hisi_qm_dev_err_uninit() - Uninitialize device error configuration.
 * @qm: The qm क्रम which we want to करो error uninitialization.
 *
 * Uninitialize QM and device error related configuration.
 */
व्योम hisi_qm_dev_err_uninit(काष्ठा hisi_qm *qm)
अणु
	अगर (qm->fun_type == QM_HW_VF)
		वापस;

	qm_hw_error_uninit(qm);

	अगर (!qm->err_ini->hw_err_disable) अणु
		dev_err(&qm->pdev->dev, "Unexpected device hw error uninit!\n");
		वापस;
	पूर्ण
	qm->err_ini->hw_err_disable(qm);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_dev_err_uninit);

/**
 * hisi_qm_मुक्त_qps() - मुक्त multiple queue pairs.
 * @qps: The queue pairs need to be मुक्तd.
 * @qp_num: The num of queue pairs.
 */
व्योम hisi_qm_मुक्त_qps(काष्ठा hisi_qp **qps, पूर्णांक qp_num)
अणु
	पूर्णांक i;

	अगर (!qps || qp_num <= 0)
		वापस;

	क्रम (i = qp_num - 1; i >= 0; i--)
		hisi_qm_release_qp(qps[i]);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_मुक्त_qps);

अटल व्योम मुक्त_list(काष्ठा list_head *head)
अणु
	काष्ठा hisi_qm_resource *res, *पंचांगp;

	list_क्रम_each_entry_safe(res, पंचांगp, head, list) अणु
		list_del(&res->list);
		kमुक्त(res);
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_qm_sort_devices(पूर्णांक node, काष्ठा list_head *head,
				काष्ठा hisi_qm_list *qm_list)
अणु
	काष्ठा hisi_qm_resource *res, *पंचांगp;
	काष्ठा hisi_qm *qm;
	काष्ठा list_head *n;
	काष्ठा device *dev;
	पूर्णांक dev_node = 0;

	list_क्रम_each_entry(qm, &qm_list->list, list) अणु
		dev = &qm->pdev->dev;

		अगर (IS_ENABLED(CONFIG_NUMA)) अणु
			dev_node = dev_to_node(dev);
			अगर (dev_node < 0)
				dev_node = 0;
		पूर्ण

		res = kzalloc(माप(*res), GFP_KERNEL);
		अगर (!res)
			वापस -ENOMEM;

		res->qm = qm;
		res->distance = node_distance(dev_node, node);
		n = head;
		list_क्रम_each_entry(पंचांगp, head, list) अणु
			अगर (res->distance < पंचांगp->distance) अणु
				n = &पंचांगp->list;
				अवरोध;
			पूर्ण
		पूर्ण
		list_add_tail(&res->list, n);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hisi_qm_alloc_qps_node() - Create multiple queue pairs.
 * @qm_list: The list of all available devices.
 * @qp_num: The number of queue pairs need created.
 * @alg_type: The algorithm type.
 * @node: The numa node.
 * @qps: The queue pairs need created.
 *
 * This function will sort all available device according to numa distance.
 * Then try to create all queue pairs from one device, अगर all devices करो
 * not meet the requirements will वापस error.
 */
पूर्णांक hisi_qm_alloc_qps_node(काष्ठा hisi_qm_list *qm_list, पूर्णांक qp_num,
			   u8 alg_type, पूर्णांक node, काष्ठा hisi_qp **qps)
अणु
	काष्ठा hisi_qm_resource *पंचांगp;
	पूर्णांक ret = -ENODEV;
	LIST_HEAD(head);
	पूर्णांक i;

	अगर (!qps || !qm_list || qp_num <= 0)
		वापस -EINVAL;

	mutex_lock(&qm_list->lock);
	अगर (hisi_qm_sort_devices(node, &head, qm_list)) अणु
		mutex_unlock(&qm_list->lock);
		जाओ err;
	पूर्ण

	list_क्रम_each_entry(पंचांगp, &head, list) अणु
		क्रम (i = 0; i < qp_num; i++) अणु
			qps[i] = hisi_qm_create_qp(पंचांगp->qm, alg_type);
			अगर (IS_ERR(qps[i])) अणु
				hisi_qm_मुक्त_qps(qps, i);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == qp_num) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&qm_list->lock);
	अगर (ret)
		pr_info("Failed to create qps, node[%d], alg[%u], qp[%d]!\n",
			node, alg_type, qp_num);

err:
	मुक्त_list(&head);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_alloc_qps_node);

अटल पूर्णांक qm_vf_q_assign(काष्ठा hisi_qm *qm, u32 num_vfs)
अणु
	u32 reमुख्य_q_num, vfs_q_num, act_q_num, q_num, i, j;
	u32 max_qp_num = qm->max_qp_num;
	u32 q_base = qm->qp_num;
	पूर्णांक ret;

	अगर (!num_vfs)
		वापस -EINVAL;

	vfs_q_num = qm->ctrl_qp_num - qm->qp_num;

	/* If vfs_q_num is less than num_vfs, वापस error. */
	अगर (vfs_q_num < num_vfs)
		वापस -EINVAL;

	q_num = vfs_q_num / num_vfs;
	reमुख्य_q_num = vfs_q_num % num_vfs;

	क्रम (i = num_vfs; i > 0; i--) अणु
		/*
		 * अगर q_num + reमुख्य_q_num > max_qp_num in last vf, भागide the
		 * reमुख्यing queues equally.
		 */
		अगर (i == num_vfs && q_num + reमुख्य_q_num <= max_qp_num) अणु
			act_q_num = q_num + reमुख्य_q_num;
			reमुख्य_q_num = 0;
		पूर्ण अन्यथा अगर (reमुख्य_q_num > 0) अणु
			act_q_num = q_num + 1;
			reमुख्य_q_num--;
		पूर्ण अन्यथा अणु
			act_q_num = q_num;
		पूर्ण

		act_q_num = min_t(पूर्णांक, act_q_num, max_qp_num);
		ret = hisi_qm_set_vft(qm, i, q_base, act_q_num);
		अगर (ret) अणु
			क्रम (j = num_vfs; j > i; j--)
				hisi_qm_set_vft(qm, j, 0, 0);
			वापस ret;
		पूर्ण
		q_base += act_q_num;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qm_clear_vft_config(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक ret;
	u32 i;

	क्रम (i = 1; i <= qm->vfs_num; i++) अणु
		ret = hisi_qm_set_vft(qm, i, 0, 0);
		अगर (ret)
			वापस ret;
	पूर्ण
	qm->vfs_num = 0;

	वापस 0;
पूर्ण

/**
 * hisi_qm_sriov_enable() - enable भव functions
 * @pdev: the PCIe device
 * @max_vfs: the number of भव functions to enable
 *
 * Returns the number of enabled VFs. If there are VFs enabled alपढ़ोy or
 * max_vfs is more than the total number of device can be enabled, वापसs
 * failure.
 */
पूर्णांक hisi_qm_sriov_enable(काष्ठा pci_dev *pdev, पूर्णांक max_vfs)
अणु
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);
	पूर्णांक pre_existing_vfs, num_vfs, total_vfs, ret;

	total_vfs = pci_sriov_get_totalvfs(pdev);
	pre_existing_vfs = pci_num_vf(pdev);
	अगर (pre_existing_vfs) अणु
		pci_err(pdev, "%d VFs already enabled. Please disable pre-enabled VFs!\n",
			pre_existing_vfs);
		वापस 0;
	पूर्ण

	num_vfs = min_t(पूर्णांक, max_vfs, total_vfs);
	ret = qm_vf_q_assign(qm, num_vfs);
	अगर (ret) अणु
		pci_err(pdev, "Can't assign queues for VF!\n");
		वापस ret;
	पूर्ण

	qm->vfs_num = num_vfs;

	ret = pci_enable_sriov(pdev, num_vfs);
	अगर (ret) अणु
		pci_err(pdev, "Can't enable VF!\n");
		qm_clear_vft_config(qm);
		वापस ret;
	पूर्ण

	pci_info(pdev, "VF enabled, vfs_num(=%d)!\n", num_vfs);

	वापस num_vfs;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_sriov_enable);

/**
 * hisi_qm_sriov_disable - disable भव functions
 * @pdev: the PCI device.
 * @is_frozen: true when all the VFs are frozen.
 *
 * Return failure अगर there are VFs asचिन्हित alपढ़ोy or VF is in used.
 */
पूर्णांक hisi_qm_sriov_disable(काष्ठा pci_dev *pdev, bool is_frozen)
अणु
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);

	अगर (pci_vfs_asचिन्हित(pdev)) अणु
		pci_err(pdev, "Failed to disable VFs as VFs are assigned!\n");
		वापस -EPERM;
	पूर्ण

	/* While VF is in used, SRIOV cannot be disabled. */
	अगर (!is_frozen && qm_try_frozen_vfs(pdev, qm->qm_list)) अणु
		pci_err(pdev, "Task is using its VF!\n");
		वापस -EBUSY;
	पूर्ण

	pci_disable_sriov(pdev);
	वापस qm_clear_vft_config(qm);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_sriov_disable);

/**
 * hisi_qm_sriov_configure - configure the number of VFs
 * @pdev: The PCI device
 * @num_vfs: The number of VFs need enabled
 *
 * Enable SR-IOV according to num_vfs, 0 means disable.
 */
पूर्णांक hisi_qm_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	अगर (num_vfs == 0)
		वापस hisi_qm_sriov_disable(pdev, false);
	अन्यथा
		वापस hisi_qm_sriov_enable(pdev, num_vfs);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_sriov_configure);

अटल क्रमागत acc_err_result qm_dev_err_handle(काष्ठा hisi_qm *qm)
अणु
	u32 err_sts;

	अगर (!qm->err_ini->get_dev_hw_err_status) अणु
		dev_err(&qm->pdev->dev, "Device doesn't support get hw error status!\n");
		वापस ACC_ERR_NONE;
	पूर्ण

	/* get device hardware error status */
	err_sts = qm->err_ini->get_dev_hw_err_status(qm);
	अगर (err_sts) अणु
		अगर (err_sts & qm->err_info.ecc_2bits_mask)
			qm->err_status.is_dev_ecc_mbit = true;

		अगर (qm->err_ini->log_dev_hw_err)
			qm->err_ini->log_dev_hw_err(qm, err_sts);

		/* ce error करोes not need to be reset */
		अगर ((err_sts | qm->err_info.dev_ce_mask) ==
		     qm->err_info.dev_ce_mask) अणु
			अगर (qm->err_ini->clear_dev_hw_err_status)
				qm->err_ini->clear_dev_hw_err_status(qm,
								err_sts);

			वापस ACC_ERR_RECOVERED;
		पूर्ण

		वापस ACC_ERR_NEED_RESET;
	पूर्ण

	वापस ACC_ERR_RECOVERED;
पूर्ण

अटल क्रमागत acc_err_result qm_process_dev_error(काष्ठा hisi_qm *qm)
अणु
	क्रमागत acc_err_result qm_ret, dev_ret;

	/* log qm error */
	qm_ret = qm_hw_error_handle(qm);

	/* log device error */
	dev_ret = qm_dev_err_handle(qm);

	वापस (qm_ret == ACC_ERR_NEED_RESET ||
		dev_ret == ACC_ERR_NEED_RESET) ?
		ACC_ERR_NEED_RESET : ACC_ERR_RECOVERED;
पूर्ण

/**
 * hisi_qm_dev_err_detected() - Get device and qm error status then log it.
 * @pdev: The PCI device which need report error.
 * @state: The connectivity between CPU and device.
 *
 * We रेजिस्टर this function पूर्णांकo PCIe AER handlers, It will report device or
 * qm hardware error status when error occur.
 */
pci_ers_result_t hisi_qm_dev_err_detected(काष्ठा pci_dev *pdev,
					  pci_channel_state_t state)
अणु
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);
	क्रमागत acc_err_result ret;

	अगर (pdev->is_virtfn)
		वापस PCI_ERS_RESULT_NONE;

	pci_info(pdev, "PCI error detected, state(=%u)!!\n", state);
	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	ret = qm_process_dev_error(qm);
	अगर (ret == ACC_ERR_NEED_RESET)
		वापस PCI_ERS_RESULT_NEED_RESET;

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_dev_err_detected);

अटल u32 qm_get_hw_error_status(काष्ठा hisi_qm *qm)
अणु
	वापस पढ़ोl(qm->io_base + QM_ABNORMAL_INT_STATUS);
पूर्ण

अटल पूर्णांक qm_check_req_recv(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	पूर्णांक ret;
	u32 val;

	ग_लिखोl(ACC_VENDOR_ID_VALUE, qm->io_base + QM_PEH_VENDOR_ID);
	ret = पढ़ोl_relaxed_poll_समयout(qm->io_base + QM_PEH_VENDOR_ID, val,
					 (val == ACC_VENDOR_ID_VALUE),
					 POLL_PERIOD, POLL_TIMEOUT);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Fails to read QM reg!\n");
		वापस ret;
	पूर्ण

	ग_लिखोl(PCI_VENDOR_ID_HUAWEI, qm->io_base + QM_PEH_VENDOR_ID);
	ret = पढ़ोl_relaxed_poll_समयout(qm->io_base + QM_PEH_VENDOR_ID, val,
					 (val == PCI_VENDOR_ID_HUAWEI),
					 POLL_PERIOD, POLL_TIMEOUT);
	अगर (ret)
		dev_err(&pdev->dev, "Fails to read QM reg in the second time!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक qm_set_pf_mse(काष्ठा hisi_qm *qm, bool set)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	u16 cmd;
	पूर्णांक i;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	अगर (set)
		cmd |= PCI_COMMAND_MEMORY;
	अन्यथा
		cmd &= ~PCI_COMMAND_MEMORY;

	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);
	क्रम (i = 0; i < MAX_WAIT_COUNTS; i++) अणु
		pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
		अगर (set == ((cmd & PCI_COMMAND_MEMORY) >> 1))
			वापस 0;

		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक qm_set_vf_mse(काष्ठा hisi_qm *qm, bool set)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	u16 sriov_ctrl;
	पूर्णांक pos;
	पूर्णांक i;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	pci_पढ़ो_config_word(pdev, pos + PCI_SRIOV_CTRL, &sriov_ctrl);
	अगर (set)
		sriov_ctrl |= PCI_SRIOV_CTRL_MSE;
	अन्यथा
		sriov_ctrl &= ~PCI_SRIOV_CTRL_MSE;
	pci_ग_लिखो_config_word(pdev, pos + PCI_SRIOV_CTRL, sriov_ctrl);

	क्रम (i = 0; i < MAX_WAIT_COUNTS; i++) अणु
		pci_पढ़ो_config_word(pdev, pos + PCI_SRIOV_CTRL, &sriov_ctrl);
		अगर (set == (sriov_ctrl & PCI_SRIOV_CTRL_MSE) >>
		    ACC_PEH_SRIOV_CTRL_VF_MSE_SHIFT)
			वापस 0;

		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक qm_set_msi(काष्ठा hisi_qm *qm, bool set)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;

	अगर (set) अणु
		pci_ग_लिखो_config_dword(pdev, pdev->msi_cap + PCI_MSI_MASK_64,
				       0);
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_config_dword(pdev, pdev->msi_cap + PCI_MSI_MASK_64,
				       ACC_PEH_MSI_DISABLE);
		अगर (qm->err_status.is_qm_ecc_mbit ||
		    qm->err_status.is_dev_ecc_mbit)
			वापस 0;

		mdelay(1);
		अगर (पढ़ोl(qm->io_base + QM_PEH_DFX_INFO0))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qm_vf_reset_prepare(काष्ठा hisi_qm *qm,
			       क्रमागत qm_stop_reason stop_reason)
अणु
	काष्ठा hisi_qm_list *qm_list = qm->qm_list;
	काष्ठा pci_dev *pdev = qm->pdev;
	काष्ठा pci_dev *virtfn;
	काष्ठा hisi_qm *vf_qm;
	पूर्णांक ret = 0;

	mutex_lock(&qm_list->lock);
	list_क्रम_each_entry(vf_qm, &qm_list->list, list) अणु
		virtfn = vf_qm->pdev;
		अगर (virtfn == pdev)
			जारी;

		अगर (pci_physfn(virtfn) == pdev) अणु
			/* save VFs PCIE BAR configuration */
			pci_save_state(virtfn);

			ret = hisi_qm_stop(vf_qm, stop_reason);
			अगर (ret)
				जाओ stop_fail;
		पूर्ण
	पूर्ण

stop_fail:
	mutex_unlock(&qm_list->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक qm_reset_prepare_पढ़ोy(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	काष्ठा hisi_qm *pf_qm = pci_get_drvdata(pci_physfn(pdev));
	पूर्णांक delay = 0;

	/* All reset requests need to be queued क्रम processing */
	जबतक (test_and_set_bit(QM_RESETTING, &pf_qm->misc_ctl)) अणु
		msleep(++delay);
		अगर (delay > QM_RESET_WAIT_TIMEOUT)
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qm_controller_reset_prepare(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	पूर्णांक ret;

	ret = qm_reset_prepare_पढ़ोy(qm);
	अगर (ret) अणु
		pci_err(pdev, "Controller reset not ready!\n");
		वापस ret;
	पूर्ण

	अगर (qm->vfs_num) अणु
		ret = qm_vf_reset_prepare(qm, QM_SOFT_RESET);
		अगर (ret) अणु
			pci_err(pdev, "Fails to stop VFs!\n");
			clear_bit(QM_RESETTING, &qm->misc_ctl);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = hisi_qm_stop(qm, QM_SOFT_RESET);
	अगर (ret) अणु
		pci_err(pdev, "Fails to stop QM!\n");
		clear_bit(QM_RESETTING, &qm->misc_ctl);
		वापस ret;
	पूर्ण

	clear_bit(QM_RST_SCHED, &qm->misc_ctl);

	वापस 0;
पूर्ण

अटल व्योम qm_dev_ecc_mbit_handle(काष्ठा hisi_qm *qm)
अणु
	u32 nfe_enb = 0;

	अगर (!qm->err_status.is_dev_ecc_mbit &&
	    qm->err_status.is_qm_ecc_mbit &&
	    qm->err_ini->बंद_axi_master_ooo) अणु

		qm->err_ini->बंद_axi_master_ooo(qm);

	पूर्ण अन्यथा अगर (qm->err_status.is_dev_ecc_mbit &&
		   !qm->err_status.is_qm_ecc_mbit &&
		   !qm->err_ini->बंद_axi_master_ooo) अणु

		nfe_enb = पढ़ोl(qm->io_base + QM_RAS_NFE_ENABLE);
		ग_लिखोl(nfe_enb & QM_RAS_NFE_MBIT_DISABLE,
		       qm->io_base + QM_RAS_NFE_ENABLE);
		ग_लिखोl(QM_ECC_MBIT, qm->io_base + QM_ABNORMAL_INT_SET);
	पूर्ण
पूर्ण

अटल पूर्णांक qm_soft_reset(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	पूर्णांक ret;
	u32 val;

	/* Ensure all करोorbells and mailboxes received by QM */
	ret = qm_check_req_recv(qm);
	अगर (ret)
		वापस ret;

	अगर (qm->vfs_num) अणु
		ret = qm_set_vf_mse(qm, false);
		अगर (ret) अणु
			pci_err(pdev, "Fails to disable vf MSE bit.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = qm_set_msi(qm, false);
	अगर (ret) अणु
		pci_err(pdev, "Fails to disable PEH MSI bit.\n");
		वापस ret;
	पूर्ण

	qm_dev_ecc_mbit_handle(qm);

	/* OOO रेजिस्टर set and check */
	ग_लिखोl(ACC_MASTER_GLOBAL_CTRL_SHUTDOWN,
	       qm->io_base + ACC_MASTER_GLOBAL_CTRL);

	/* If bus lock, reset chip */
	ret = पढ़ोl_relaxed_poll_समयout(qm->io_base + ACC_MASTER_TRANS_RETURN,
					 val,
					 (val == ACC_MASTER_TRANS_RETURN_RW),
					 POLL_PERIOD, POLL_TIMEOUT);
	अगर (ret) अणु
		pci_emerg(pdev, "Bus lock! Please reset system.\n");
		वापस ret;
	पूर्ण

	ret = qm_set_pf_mse(qm, false);
	अगर (ret) अणु
		pci_err(pdev, "Fails to disable pf MSE bit.\n");
		वापस ret;
	पूर्ण

	/* The reset related sub-control रेजिस्टरs are not in PCI BAR */
	अगर (ACPI_HANDLE(&pdev->dev)) अणु
		अचिन्हित दीर्घ दीर्घ value = 0;
		acpi_status s;

		s = acpi_evaluate_पूर्णांकeger(ACPI_HANDLE(&pdev->dev),
					  qm->err_info.acpi_rst,
					  शून्य, &value);
		अगर (ACPI_FAILURE(s)) अणु
			pci_err(pdev, "NO controller reset method!\n");
			वापस -EIO;
		पूर्ण

		अगर (value) अणु
			pci_err(pdev, "Reset step %llu failed!\n", value);
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		pci_err(pdev, "No reset method!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qm_vf_reset_करोne(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hisi_qm_list *qm_list = qm->qm_list;
	काष्ठा pci_dev *pdev = qm->pdev;
	काष्ठा pci_dev *virtfn;
	काष्ठा hisi_qm *vf_qm;
	पूर्णांक ret = 0;

	mutex_lock(&qm_list->lock);
	list_क्रम_each_entry(vf_qm, &qm_list->list, list) अणु
		virtfn = vf_qm->pdev;
		अगर (virtfn == pdev)
			जारी;

		अगर (pci_physfn(virtfn) == pdev) अणु
			/* enable VFs PCIE BAR configuration */
			pci_restore_state(virtfn);

			ret = qm_restart(vf_qm);
			अगर (ret)
				जाओ restart_fail;
		पूर्ण
	पूर्ण

restart_fail:
	mutex_unlock(&qm_list->lock);
	वापस ret;
पूर्ण

अटल u32 qm_get_dev_err_status(काष्ठा hisi_qm *qm)
अणु
	वापस qm->err_ini->get_dev_hw_err_status(qm);
पूर्ण

अटल पूर्णांक qm_dev_hw_init(काष्ठा hisi_qm *qm)
अणु
	वापस qm->err_ini->hw_init(qm);
पूर्ण

अटल व्योम qm_restart_prepare(काष्ठा hisi_qm *qm)
अणु
	u32 value;

	अगर (!qm->err_status.is_qm_ecc_mbit &&
	    !qm->err_status.is_dev_ecc_mbit)
		वापस;

	/* temporarily बंद the OOO port used क्रम PEH to ग_लिखो out MSI */
	value = पढ़ोl(qm->io_base + ACC_AM_CFG_PORT_WR_EN);
	ग_लिखोl(value & ~qm->err_info.msi_wr_port,
	       qm->io_base + ACC_AM_CFG_PORT_WR_EN);

	/* clear dev ecc 2bit error source अगर having */
	value = qm_get_dev_err_status(qm) & qm->err_info.ecc_2bits_mask;
	अगर (value && qm->err_ini->clear_dev_hw_err_status)
		qm->err_ini->clear_dev_hw_err_status(qm, value);

	/* clear QM ecc mbit error source */
	ग_लिखोl(QM_ECC_MBIT, qm->io_base + QM_ABNORMAL_INT_SOURCE);

	/* clear AM Reorder Buffer ecc mbit source */
	ग_लिखोl(ACC_ROB_ECC_ERR_MULTPL, qm->io_base + ACC_AM_ROB_ECC_INT_STS);

	अगर (qm->err_ini->खोलो_axi_master_ooo)
		qm->err_ini->खोलो_axi_master_ooo(qm);
पूर्ण

अटल व्योम qm_restart_करोne(काष्ठा hisi_qm *qm)
अणु
	u32 value;

	अगर (!qm->err_status.is_qm_ecc_mbit &&
	    !qm->err_status.is_dev_ecc_mbit)
		वापस;

	/* खोलो the OOO port क्रम PEH to ग_लिखो out MSI */
	value = पढ़ोl(qm->io_base + ACC_AM_CFG_PORT_WR_EN);
	value |= qm->err_info.msi_wr_port;
	ग_लिखोl(value, qm->io_base + ACC_AM_CFG_PORT_WR_EN);

	qm->err_status.is_qm_ecc_mbit = false;
	qm->err_status.is_dev_ecc_mbit = false;
पूर्ण

अटल पूर्णांक qm_controller_reset_करोne(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	पूर्णांक ret;

	ret = qm_set_msi(qm, true);
	अगर (ret) अणु
		pci_err(pdev, "Fails to enable PEH MSI bit!\n");
		वापस ret;
	पूर्ण

	ret = qm_set_pf_mse(qm, true);
	अगर (ret) अणु
		pci_err(pdev, "Fails to enable pf MSE bit!\n");
		वापस ret;
	पूर्ण

	अगर (qm->vfs_num) अणु
		ret = qm_set_vf_mse(qm, true);
		अगर (ret) अणु
			pci_err(pdev, "Fails to enable vf MSE bit!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = qm_dev_hw_init(qm);
	अगर (ret) अणु
		pci_err(pdev, "Failed to init device\n");
		वापस ret;
	पूर्ण

	qm_restart_prepare(qm);

	ret = qm_restart(qm);
	अगर (ret) अणु
		pci_err(pdev, "Failed to start QM!\n");
		वापस ret;
	पूर्ण

	अगर (qm->vfs_num) अणु
		ret = qm_vf_q_assign(qm, qm->vfs_num);
		अगर (ret) अणु
			pci_err(pdev, "Failed to assign queue!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = qm_vf_reset_करोne(qm);
	अगर (ret) अणु
		pci_err(pdev, "Failed to start VFs!\n");
		वापस -EPERM;
	पूर्ण

	hisi_qm_dev_err_init(qm);
	qm_restart_करोne(qm);

	clear_bit(QM_RESETTING, &qm->misc_ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक qm_controller_reset(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	पूर्णांक ret;

	pci_info(pdev, "Controller resetting...\n");

	ret = qm_controller_reset_prepare(qm);
	अगर (ret) अणु
		clear_bit(QM_RST_SCHED, &qm->misc_ctl);
		वापस ret;
	पूर्ण

	ret = qm_soft_reset(qm);
	अगर (ret) अणु
		pci_err(pdev, "Controller reset failed (%d)\n", ret);
		clear_bit(QM_RESETTING, &qm->misc_ctl);
		वापस ret;
	पूर्ण

	ret = qm_controller_reset_करोne(qm);
	अगर (ret) अणु
		clear_bit(QM_RESETTING, &qm->misc_ctl);
		वापस ret;
	पूर्ण

	pci_info(pdev, "Controller reset complete\n");

	वापस 0;
पूर्ण

/**
 * hisi_qm_dev_slot_reset() - slot reset
 * @pdev: the PCIe device
 *
 * This function offers QM relate PCIe device reset पूर्णांकerface. Drivers which
 * use QM can use this function as slot_reset in its काष्ठा pci_error_handlers.
 */
pci_ers_result_t hisi_qm_dev_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (pdev->is_virtfn)
		वापस PCI_ERS_RESULT_RECOVERED;

	pci_aer_clear_nonfatal_status(pdev);

	/* reset pcie device controller */
	ret = qm_controller_reset(qm);
	अगर (ret) अणु
		pci_err(pdev, "Controller reset failed (%d)\n", ret);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_dev_slot_reset);

/* check the पूर्णांकerrupt is ecc-mbit error or not */
अटल पूर्णांक qm_check_dev_error(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक ret;

	अगर (qm->fun_type == QM_HW_VF)
		वापस 0;

	ret = qm_get_hw_error_status(qm) & QM_ECC_MBIT;
	अगर (ret)
		वापस ret;

	वापस (qm_get_dev_err_status(qm) & qm->err_info.ecc_2bits_mask);
पूर्ण

व्योम hisi_qm_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hisi_qm *pf_qm = pci_get_drvdata(pci_physfn(pdev));
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);
	u32 delay = 0;
	पूर्णांक ret;

	hisi_qm_dev_err_uninit(pf_qm);

	/*
	 * Check whether there is an ECC mbit error, If it occurs, need to
	 * रुको क्रम soft reset to fix it.
	 */
	जबतक (qm_check_dev_error(pf_qm)) अणु
		msleep(++delay);
		अगर (delay > QM_RESET_WAIT_TIMEOUT)
			वापस;
	पूर्ण

	ret = qm_reset_prepare_पढ़ोy(qm);
	अगर (ret) अणु
		pci_err(pdev, "FLR not ready!\n");
		वापस;
	पूर्ण

	अगर (qm->vfs_num) अणु
		ret = qm_vf_reset_prepare(qm, QM_FLR);
		अगर (ret) अणु
			pci_err(pdev, "Failed to prepare reset, ret = %d.\n",
				ret);
			वापस;
		पूर्ण
	पूर्ण

	ret = hisi_qm_stop(qm, QM_FLR);
	अगर (ret) अणु
		pci_err(pdev, "Failed to stop QM, ret = %d.\n", ret);
		वापस;
	पूर्ण

	pci_info(pdev, "FLR resetting...\n");
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_reset_prepare);

अटल bool qm_flr_reset_complete(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *pf_pdev = pci_physfn(pdev);
	काष्ठा hisi_qm *qm = pci_get_drvdata(pf_pdev);
	u32 id;

	pci_पढ़ो_config_dword(qm->pdev, PCI_COMMAND, &id);
	अगर (id == QM_PCI_COMMAND_INVALID) अणु
		pci_err(pdev, "Device can not be used!\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम hisi_qm_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hisi_qm *pf_qm = pci_get_drvdata(pci_physfn(pdev));
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);
	पूर्णांक ret;

	hisi_qm_dev_err_init(pf_qm);

	ret = qm_restart(qm);
	अगर (ret) अणु
		pci_err(pdev, "Failed to start QM, ret = %d.\n", ret);
		जाओ flr_करोne;
	पूर्ण

	अगर (qm->fun_type == QM_HW_PF) अणु
		ret = qm_dev_hw_init(qm);
		अगर (ret) अणु
			pci_err(pdev, "Failed to init PF, ret = %d.\n", ret);
			जाओ flr_करोne;
		पूर्ण

		अगर (!qm->vfs_num)
			जाओ flr_करोne;

		ret = qm_vf_q_assign(qm, qm->vfs_num);
		अगर (ret) अणु
			pci_err(pdev, "Failed to assign VFs, ret = %d.\n", ret);
			जाओ flr_करोne;
		पूर्ण

		ret = qm_vf_reset_करोne(qm);
		अगर (ret) अणु
			pci_err(pdev, "Failed to start VFs, ret = %d.\n", ret);
			जाओ flr_करोne;
		पूर्ण
	पूर्ण

flr_करोne:
	अगर (qm_flr_reset_complete(pdev))
		pci_info(pdev, "FLR reset complete\n");

	clear_bit(QM_RESETTING, &qm->misc_ctl);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_reset_करोne);

अटल irqवापस_t qm_abnormal_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hisi_qm *qm = data;
	क्रमागत acc_err_result ret;

	atomic64_inc(&qm->debug.dfx.abnormal_irq_cnt);
	ret = qm_process_dev_error(qm);
	अगर (ret == ACC_ERR_NEED_RESET &&
	    !test_bit(QM_DRIVER_REMOVING, &qm->misc_ctl) &&
	    !test_and_set_bit(QM_RST_SCHED, &qm->misc_ctl))
		schedule_work(&qm->rst_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qm_irq_रेजिस्टर(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	पूर्णांक ret;

	ret = request_irq(pci_irq_vector(pdev, QM_EQ_EVENT_IRQ_VECTOR),
			  qm_irq, 0, qm->dev_name, qm);
	अगर (ret)
		वापस ret;

	अगर (qm->ver != QM_HW_V1) अणु
		ret = request_irq(pci_irq_vector(pdev, QM_AEQ_EVENT_IRQ_VECTOR),
				  qm_aeq_irq, 0, qm->dev_name, qm);
		अगर (ret)
			जाओ err_aeq_irq;

		अगर (qm->fun_type == QM_HW_PF) अणु
			ret = request_irq(pci_irq_vector(pdev,
					  QM_ABNORMAL_EVENT_IRQ_VECTOR),
					  qm_abnormal_irq, 0, qm->dev_name, qm);
			अगर (ret)
				जाओ err_abonormal_irq;
		पूर्ण
	पूर्ण

	वापस 0;

err_abonormal_irq:
	मुक्त_irq(pci_irq_vector(pdev, QM_AEQ_EVENT_IRQ_VECTOR), qm);
err_aeq_irq:
	मुक्त_irq(pci_irq_vector(pdev, QM_EQ_EVENT_IRQ_VECTOR), qm);
	वापस ret;
पूर्ण

/**
 * hisi_qm_dev_shutकरोwn() - Shutकरोwn device.
 * @pdev: The device will be shutकरोwn.
 *
 * This function will stop qm when OS shutकरोwn or rebooting.
 */
व्योम hisi_qm_dev_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);
	पूर्णांक ret;

	ret = hisi_qm_stop(qm, QM_NORMAL);
	अगर (ret)
		dev_err(&pdev->dev, "Fail to stop qm in shutdown!\n");
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_dev_shutकरोwn);

अटल व्योम hisi_qm_controller_reset(काष्ठा work_काष्ठा *rst_work)
अणु
	काष्ठा hisi_qm *qm = container_of(rst_work, काष्ठा hisi_qm, rst_work);
	पूर्णांक ret;

	/* reset pcie device controller */
	ret = qm_controller_reset(qm);
	अगर (ret)
		dev_err(&qm->pdev->dev, "controller reset failed (%d)\n", ret);

पूर्ण

/**
 * hisi_qm_alg_रेजिस्टर() - Register alg to crypto and add qm to qm_list.
 * @qm: The qm needs add.
 * @qm_list: The qm list.
 *
 * This function adds qm to qm list, and will रेजिस्टर algorithm to
 * crypto when the qm list is empty.
 */
पूर्णांक hisi_qm_alg_रेजिस्टर(काष्ठा hisi_qm *qm, काष्ठा hisi_qm_list *qm_list)
अणु
	पूर्णांक flag = 0;
	पूर्णांक ret = 0;
	/* HW V2 not support both use uacce sva mode and hardware crypto algs */
	अगर (qm->ver <= QM_HW_V2 && qm->use_sva)
		वापस 0;

	mutex_lock(&qm_list->lock);
	अगर (list_empty(&qm_list->list))
		flag = 1;
	list_add_tail(&qm->list, &qm_list->list);
	mutex_unlock(&qm_list->lock);

	अगर (flag) अणु
		ret = qm_list->रेजिस्टर_to_crypto(qm);
		अगर (ret) अणु
			mutex_lock(&qm_list->lock);
			list_del(&qm->list);
			mutex_unlock(&qm_list->lock);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_alg_रेजिस्टर);

/**
 * hisi_qm_alg_unरेजिस्टर() - Unरेजिस्टर alg from crypto and delete qm from
 * qm list.
 * @qm: The qm needs delete.
 * @qm_list: The qm list.
 *
 * This function deletes qm from qm list, and will unरेजिस्टर algorithm
 * from crypto when the qm list is empty.
 */
व्योम hisi_qm_alg_unरेजिस्टर(काष्ठा hisi_qm *qm, काष्ठा hisi_qm_list *qm_list)
अणु
	अगर (qm->ver <= QM_HW_V2 && qm->use_sva)
		वापस;

	mutex_lock(&qm_list->lock);
	list_del(&qm->list);
	mutex_unlock(&qm_list->lock);

	अगर (list_empty(&qm_list->list))
		qm_list->unरेजिस्टर_from_crypto(qm);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_alg_unरेजिस्टर);

अटल पूर्णांक qm_get_qp_num(काष्ठा hisi_qm *qm)
अणु
	अगर (qm->ver == QM_HW_V1)
		qm->ctrl_qp_num = QM_QNUM_V1;
	अन्यथा अगर (qm->ver == QM_HW_V2)
		qm->ctrl_qp_num = QM_QNUM_V2;
	अन्यथा
		qm->ctrl_qp_num = पढ़ोl(qm->io_base + QM_CAPBILITY) &
					QM_QP_NUN_MASK;

	अगर (qm->use_db_isolation)
		qm->max_qp_num = (पढ़ोl(qm->io_base + QM_CAPBILITY) >>
				  QM_QP_MAX_NUM_SHIFT) & QM_QP_NUN_MASK;
	अन्यथा
		qm->max_qp_num = qm->ctrl_qp_num;

	/* check अगर qp number is valid */
	अगर (qm->qp_num > qm->max_qp_num) अणु
		dev_err(&qm->pdev->dev, "qp num(%u) is more than max qp num(%u)!\n",
			qm->qp_num, qm->max_qp_num);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qm_get_pci_res(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	ret = pci_request_mem_regions(pdev, qm->dev_name);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request mem regions!\n");
		वापस ret;
	पूर्ण

	qm->phys_base = pci_resource_start(pdev, PCI_BAR_2);
	qm->io_base = ioremap(qm->phys_base, pci_resource_len(pdev, PCI_BAR_2));
	अगर (!qm->io_base) अणु
		ret = -EIO;
		जाओ err_request_mem_regions;
	पूर्ण

	अगर (qm->ver > QM_HW_V2) अणु
		अगर (qm->fun_type == QM_HW_PF)
			qm->use_db_isolation = पढ़ोl(qm->io_base +
						     QM_QUE_ISO_EN) & BIT(0);
		अन्यथा
			qm->use_db_isolation = पढ़ोl(qm->io_base +
						     QM_QUE_ISO_CFG_V) & BIT(0);
	पूर्ण

	अगर (qm->use_db_isolation) अणु
		qm->db_पूर्णांकerval = QM_QP_DB_INTERVAL;
		qm->db_phys_base = pci_resource_start(pdev, PCI_BAR_4);
		qm->db_io_base = ioremap(qm->db_phys_base,
					 pci_resource_len(pdev, PCI_BAR_4));
		अगर (!qm->db_io_base) अणु
			ret = -EIO;
			जाओ err_ioremap;
		पूर्ण
	पूर्ण अन्यथा अणु
		qm->db_phys_base = qm->phys_base;
		qm->db_io_base = qm->io_base;
		qm->db_पूर्णांकerval = 0;
	पूर्ण

	अगर (qm->fun_type == QM_HW_PF) अणु
		ret = qm_get_qp_num(qm);
		अगर (ret)
			जाओ err_db_ioremap;
	पूर्ण

	वापस 0;

err_db_ioremap:
	अगर (qm->use_db_isolation)
		iounmap(qm->db_io_base);
err_ioremap:
	iounmap(qm->io_base);
err_request_mem_regions:
	pci_release_mem_regions(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक hisi_qm_pci_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित पूर्णांक num_vec;
	पूर्णांक ret;

	ret = pci_enable_device_mem(pdev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable device mem!\n");
		वापस ret;
	पूर्ण

	ret = qm_get_pci_res(qm);
	अगर (ret)
		जाओ err_disable_pcidev;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (ret < 0)
		जाओ err_get_pci_res;
	pci_set_master(pdev);

	अगर (!qm->ops->get_irq_num) अणु
		ret = -EOPNOTSUPP;
		जाओ err_get_pci_res;
	पूर्ण
	num_vec = qm->ops->get_irq_num(qm);
	ret = pci_alloc_irq_vectors(pdev, num_vec, num_vec, PCI_IRQ_MSI);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable MSI vectors!\n");
		जाओ err_get_pci_res;
	पूर्ण

	वापस 0;

err_get_pci_res:
	qm_put_pci_res(qm);
err_disable_pcidev:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

/**
 * hisi_qm_init() - Initialize configures about qm.
 * @qm: The qm needing init.
 *
 * This function init qm, then we can call hisi_qm_start to put qm पूर्णांकo work.
 */
पूर्णांक hisi_qm_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा pci_dev *pdev = qm->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	hisi_qm_pre_init(qm);

	ret = hisi_qm_pci_init(qm);
	अगर (ret)
		वापस ret;

	ret = qm_irq_रेजिस्टर(qm);
	अगर (ret)
		जाओ err_pci_init;

	अगर (qm->fun_type == QM_HW_VF && qm->ver != QM_HW_V1) अणु
		/* v2 starts to support get vft by mailbox */
		ret = hisi_qm_get_vft(qm, &qm->qp_base, &qm->qp_num);
		अगर (ret)
			जाओ err_irq_रेजिस्टर;
	पूर्ण

	ret = qm_alloc_uacce(qm);
	अगर (ret < 0)
		dev_warn(dev, "fail to alloc uacce (%d)\n", ret);

	ret = hisi_qm_memory_init(qm);
	अगर (ret)
		जाओ err_alloc_uacce;

	INIT_WORK(&qm->work, qm_work_process);
	अगर (qm->fun_type == QM_HW_PF)
		INIT_WORK(&qm->rst_work, hisi_qm_controller_reset);

	atomic_set(&qm->status.flags, QM_INIT);

	वापस 0;

err_alloc_uacce:
	uacce_हटाओ(qm->uacce);
	qm->uacce = शून्य;
err_irq_रेजिस्टर:
	qm_irq_unरेजिस्टर(qm);
err_pci_init:
	hisi_qm_pci_uninit(qm);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_qm_init);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zhou Wang <wangzhou1@hisilicon.com>");
MODULE_DESCRIPTION("HiSilicon Accelerator queue manager driver");
