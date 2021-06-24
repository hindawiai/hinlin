<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 HiSilicon Limited. */
#अगर_अघोषित HISI_ACC_QM_H
#घोषणा HISI_ACC_QM_H

#समावेश <linux/bitfield.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#घोषणा QM_QNUM_V1			4096
#घोषणा QM_QNUM_V2			1024
#घोषणा QM_MAX_VFS_NUM_V2		63

/* qm user करोमुख्य */
#घोषणा QM_ARUSER_M_CFG_1		0x100088
#घोषणा AXUSER_SNOOP_ENABLE		BIT(30)
#घोषणा AXUSER_CMD_TYPE			GENMASK(14, 12)
#घोषणा AXUSER_CMD_SMMU_NORMAL		1
#घोषणा AXUSER_NS			BIT(6)
#घोषणा AXUSER_NO			BIT(5)
#घोषणा AXUSER_FP			BIT(4)
#घोषणा AXUSER_SSV			BIT(0)
#घोषणा AXUSER_BASE			(AXUSER_SNOOP_ENABLE |		\
					FIELD_PREP(AXUSER_CMD_TYPE,	\
					AXUSER_CMD_SMMU_NORMAL) |	\
					AXUSER_NS | AXUSER_NO | AXUSER_FP)
#घोषणा QM_ARUSER_M_CFG_ENABLE		0x100090
#घोषणा ARUSER_M_CFG_ENABLE		0xfffffffe
#घोषणा QM_AWUSER_M_CFG_1		0x100098
#घोषणा QM_AWUSER_M_CFG_ENABLE		0x1000a0
#घोषणा AWUSER_M_CFG_ENABLE		0xfffffffe
#घोषणा QM_WUSER_M_CFG_ENABLE		0x1000a8
#घोषणा WUSER_M_CFG_ENABLE		0xffffffff

/* qm cache */
#घोषणा QM_CACHE_CTL			0x100050
#घोषणा SQC_CACHE_ENABLE		BIT(0)
#घोषणा CQC_CACHE_ENABLE		BIT(1)
#घोषणा SQC_CACHE_WB_ENABLE		BIT(4)
#घोषणा SQC_CACHE_WB_THRD		GENMASK(10, 5)
#घोषणा CQC_CACHE_WB_ENABLE		BIT(11)
#घोषणा CQC_CACHE_WB_THRD		GENMASK(17, 12)
#घोषणा QM_AXI_M_CFG			0x1000ac
#घोषणा AXI_M_CFG			0xffff
#घोषणा QM_AXI_M_CFG_ENABLE		0x1000b0
#घोषणा AM_CFG_SINGLE_PORT_MAX_TRANS	0x300014
#घोषणा AXI_M_CFG_ENABLE		0xffffffff
#घोषणा QM_PEH_AXUSER_CFG		0x1000cc
#घोषणा QM_PEH_AXUSER_CFG_ENABLE	0x1000d0
#घोषणा PEH_AXUSER_CFG			0x401001
#घोषणा PEH_AXUSER_CFG_ENABLE		0xffffffff

#घोषणा QM_AXI_RRESP			BIT(0)
#घोषणा QM_AXI_BRESP			BIT(1)
#घोषणा QM_ECC_MBIT			BIT(2)
#घोषणा QM_ECC_1BIT			BIT(3)
#घोषणा QM_ACC_GET_TASK_TIMEOUT		BIT(4)
#घोषणा QM_ACC_DO_TASK_TIMEOUT		BIT(5)
#घोषणा QM_ACC_WB_NOT_READY_TIMEOUT	BIT(6)
#घोषणा QM_SQ_CQ_VF_INVALID		BIT(7)
#घोषणा QM_CQ_VF_INVALID		BIT(8)
#घोषणा QM_SQ_VF_INVALID		BIT(9)
#घोषणा QM_DB_TIMEOUT			BIT(10)
#घोषणा QM_OF_FIFO_OF			BIT(11)
#घोषणा QM_DB_RANDOM_INVALID		BIT(12)
#घोषणा QM_MAILBOX_TIMEOUT		BIT(13)
#घोषणा QM_FLR_TIMEOUT			BIT(14)

#घोषणा QM_BASE_NFE	(QM_AXI_RRESP | QM_AXI_BRESP | QM_ECC_MBIT | \
			 QM_ACC_GET_TASK_TIMEOUT | QM_DB_TIMEOUT | \
			 QM_OF_FIFO_OF | QM_DB_RANDOM_INVALID | \
			 QM_MAILBOX_TIMEOUT | QM_FLR_TIMEOUT)
#घोषणा QM_BASE_CE			QM_ECC_1BIT

#घोषणा QM_Q_DEPTH			1024
#घोषणा QM_MIN_QNUM                     2
#घोषणा HISI_ACC_SGL_SGE_NR_MAX		255

/* page number क्रम queue file region */
#घोषणा QM_DOORBELL_PAGE_NR		1

/* uacce mode of the driver */
#घोषणा UACCE_MODE_NOUACCE		0 /* करोn't use uacce */
#घोषणा UACCE_MODE_SVA			1 /* use uacce sva mode */
#घोषणा UACCE_MODE_DESC	"0(default) means only register to crypto, 1 means both register to crypto and uacce"

क्रमागत qm_stop_reason अणु
	QM_NORMAL,
	QM_SOFT_RESET,
	QM_FLR,
पूर्ण;

क्रमागत qm_state अणु
	QM_INIT = 0,
	QM_START,
	QM_CLOSE,
	QM_STOP,
पूर्ण;

क्रमागत qp_state अणु
	QP_INIT = 1,
	QP_START,
	QP_STOP,
	QP_CLOSE,
पूर्ण;

क्रमागत qm_hw_ver अणु
	QM_HW_UNKNOWN = -1,
	QM_HW_V1 = 0x20,
	QM_HW_V2 = 0x21,
	QM_HW_V3 = 0x30,
पूर्ण;

क्रमागत qm_fun_type अणु
	QM_HW_PF,
	QM_HW_VF,
पूर्ण;

क्रमागत qm_debug_file अणु
	CURRENT_QM,
	CURRENT_Q,
	CLEAR_ENABLE,
	DEBUG_खाता_NUM,
पूर्ण;

काष्ठा qm_dfx अणु
	atomic64_t err_irq_cnt;
	atomic64_t aeq_irq_cnt;
	atomic64_t abnormal_irq_cnt;
	atomic64_t create_qp_err_cnt;
	atomic64_t mb_err_cnt;
पूर्ण;

काष्ठा debugfs_file अणु
	क्रमागत qm_debug_file index;
	काष्ठा mutex lock;
	काष्ठा qm_debug *debug;
पूर्ण;

काष्ठा qm_debug अणु
	u32 curr_qm_qp_num;
	u32 sqe_mask_offset;
	u32 sqe_mask_len;
	काष्ठा qm_dfx dfx;
	काष्ठा dentry *debug_root;
	काष्ठा dentry *qm_d;
	काष्ठा debugfs_file files[DEBUG_खाता_NUM];
पूर्ण;

काष्ठा qm_dma अणु
	व्योम *va;
	dma_addr_t dma;
	माप_प्रकार size;
पूर्ण;

काष्ठा hisi_qm_status अणु
	u32 eq_head;
	bool eqc_phase;
	u32 aeq_head;
	bool aeqc_phase;
	atomic_t flags;
	पूर्णांक stop_reason;
पूर्ण;

काष्ठा hisi_qm;

काष्ठा hisi_qm_err_info अणु
	अक्षर *acpi_rst;
	u32 msi_wr_port;
	u32 ecc_2bits_mask;
	u32 dev_ce_mask;
	u32 ce;
	u32 nfe;
	u32 fe;
पूर्ण;

काष्ठा hisi_qm_err_status अणु
	u32 is_qm_ecc_mbit;
	u32 is_dev_ecc_mbit;
पूर्ण;

काष्ठा hisi_qm_err_ini अणु
	पूर्णांक (*hw_init)(काष्ठा hisi_qm *qm);
	व्योम (*hw_err_enable)(काष्ठा hisi_qm *qm);
	व्योम (*hw_err_disable)(काष्ठा hisi_qm *qm);
	u32 (*get_dev_hw_err_status)(काष्ठा hisi_qm *qm);
	व्योम (*clear_dev_hw_err_status)(काष्ठा hisi_qm *qm, u32 err_sts);
	व्योम (*खोलो_axi_master_ooo)(काष्ठा hisi_qm *qm);
	व्योम (*बंद_axi_master_ooo)(काष्ठा hisi_qm *qm);
	व्योम (*log_dev_hw_err)(काष्ठा hisi_qm *qm, u32 err_sts);
	व्योम (*err_info_init)(काष्ठा hisi_qm *qm);
पूर्ण;

काष्ठा hisi_qm_list अणु
	काष्ठा mutex lock;
	काष्ठा list_head list;
	पूर्णांक (*रेजिस्टर_to_crypto)(काष्ठा hisi_qm *qm);
	व्योम (*unरेजिस्टर_from_crypto)(काष्ठा hisi_qm *qm);
पूर्ण;

काष्ठा hisi_qm अणु
	क्रमागत qm_hw_ver ver;
	क्रमागत qm_fun_type fun_type;
	स्थिर अक्षर *dev_name;
	काष्ठा pci_dev *pdev;
	व्योम __iomem *io_base;
	व्योम __iomem *db_io_base;
	u32 sqe_size;
	u32 qp_base;
	u32 qp_num;
	u32 qp_in_used;
	u32 ctrl_qp_num;
	u32 max_qp_num;
	u32 vfs_num;
	u32 db_पूर्णांकerval;
	काष्ठा list_head list;
	काष्ठा hisi_qm_list *qm_list;

	काष्ठा qm_dma qdma;
	काष्ठा qm_sqc *sqc;
	काष्ठा qm_cqc *cqc;
	काष्ठा qm_eqe *eqe;
	काष्ठा qm_aeqe *aeqe;
	dma_addr_t sqc_dma;
	dma_addr_t cqc_dma;
	dma_addr_t eqe_dma;
	dma_addr_t aeqe_dma;

	काष्ठा hisi_qm_status status;
	स्थिर काष्ठा hisi_qm_err_ini *err_ini;
	काष्ठा hisi_qm_err_info err_info;
	काष्ठा hisi_qm_err_status err_status;
	अचिन्हित दीर्घ misc_ctl; /* driver removing and reset sched */

	काष्ठा rw_semaphore qps_lock;
	काष्ठा idr qp_idr;
	काष्ठा hisi_qp *qp_array;

	काष्ठा mutex mailbox_lock;

	स्थिर काष्ठा hisi_qm_hw_ops *ops;

	काष्ठा qm_debug debug;

	u32 error_mask;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा work;
	काष्ठा work_काष्ठा rst_work;

	स्थिर अक्षर *algs;
	bool use_sva;
	bool is_frozen;

	/* करोorbell isolation enable */
	bool use_db_isolation;
	resource_माप_प्रकार phys_base;
	resource_माप_प्रकार db_phys_base;
	काष्ठा uacce_device *uacce;
	पूर्णांक mode;
पूर्ण;

काष्ठा hisi_qp_status अणु
	atomic_t used;
	u16 sq_tail;
	u16 cq_head;
	bool cqc_phase;
	atomic_t flags;
पूर्ण;

काष्ठा hisi_qp_ops अणु
	पूर्णांक (*fill_sqe)(व्योम *sqe, व्योम *q_parm, व्योम *d_parm);
पूर्ण;

काष्ठा hisi_qp अणु
	u32 qp_id;
	u8 alg_type;
	u8 req_type;

	काष्ठा qm_dma qdma;
	व्योम *sqe;
	काष्ठा qm_cqe *cqe;
	dma_addr_t sqe_dma;
	dma_addr_t cqe_dma;

	काष्ठा hisi_qp_status qp_status;
	काष्ठा hisi_qp_ops *hw_ops;
	व्योम *qp_ctx;
	व्योम (*req_cb)(काष्ठा hisi_qp *qp, व्योम *data);
	व्योम (*event_cb)(काष्ठा hisi_qp *qp);

	काष्ठा hisi_qm *qm;
	bool is_resetting;
	bool is_in_kernel;
	u16 pasid;
	काष्ठा uacce_queue *uacce_q;
पूर्ण;

अटल अंतरभूत पूर्णांक q_num_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp,
			    अचिन्हित पूर्णांक device)
अणु
	काष्ठा pci_dev *pdev = pci_get_device(PCI_VENDOR_ID_HUAWEI,
					      device, शून्य);
	u32 n, q_num;
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;

	अगर (!pdev) अणु
		q_num = min_t(u32, QM_QNUM_V1, QM_QNUM_V2);
		pr_info("No device found currently, suppose queue number is %u\n",
			q_num);
	पूर्ण अन्यथा अणु
		अगर (pdev->revision == QM_HW_V1)
			q_num = QM_QNUM_V1;
		अन्यथा
			q_num = QM_QNUM_V2;
	पूर्ण

	ret = kstrtou32(val, 10, &n);
	अगर (ret || n < QM_MIN_QNUM || n > q_num)
		वापस -EINVAL;

	वापस param_set_पूर्णांक(val, kp);
पूर्ण

अटल अंतरभूत पूर्णांक vfs_num_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	u32 n;
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;

	ret = kstrtou32(val, 10, &n);
	अगर (ret < 0)
		वापस ret;

	अगर (n > QM_MAX_VFS_NUM_V2)
		वापस -EINVAL;

	वापस param_set_पूर्णांक(val, kp);
पूर्ण

अटल अंतरभूत पूर्णांक mode_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	u32 n;
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;

	ret = kstrtou32(val, 10, &n);
	अगर (ret != 0 || (n != UACCE_MODE_SVA &&
			 n != UACCE_MODE_NOUACCE))
		वापस -EINVAL;

	वापस param_set_पूर्णांक(val, kp);
पूर्ण

अटल अंतरभूत पूर्णांक uacce_mode_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस mode_set(val, kp);
पूर्ण

अटल अंतरभूत व्योम hisi_qm_init_list(काष्ठा hisi_qm_list *qm_list)
अणु
	INIT_LIST_HEAD(&qm_list->list);
	mutex_init(&qm_list->lock);
पूर्ण

पूर्णांक hisi_qm_init(काष्ठा hisi_qm *qm);
व्योम hisi_qm_uninit(काष्ठा hisi_qm *qm);
पूर्णांक hisi_qm_start(काष्ठा hisi_qm *qm);
पूर्णांक hisi_qm_stop(काष्ठा hisi_qm *qm, क्रमागत qm_stop_reason r);
काष्ठा hisi_qp *hisi_qm_create_qp(काष्ठा hisi_qm *qm, u8 alg_type);
पूर्णांक hisi_qm_start_qp(काष्ठा hisi_qp *qp, अचिन्हित दीर्घ arg);
पूर्णांक hisi_qm_stop_qp(काष्ठा hisi_qp *qp);
व्योम hisi_qm_release_qp(काष्ठा hisi_qp *qp);
पूर्णांक hisi_qp_send(काष्ठा hisi_qp *qp, स्थिर व्योम *msg);
पूर्णांक hisi_qm_get_मुक्त_qp_num(काष्ठा hisi_qm *qm);
पूर्णांक hisi_qm_get_vft(काष्ठा hisi_qm *qm, u32 *base, u32 *number);
व्योम hisi_qm_debug_init(काष्ठा hisi_qm *qm);
क्रमागत qm_hw_ver hisi_qm_get_hw_version(काष्ठा pci_dev *pdev);
व्योम hisi_qm_debug_regs_clear(काष्ठा hisi_qm *qm);
पूर्णांक hisi_qm_sriov_enable(काष्ठा pci_dev *pdev, पूर्णांक max_vfs);
पूर्णांक hisi_qm_sriov_disable(काष्ठा pci_dev *pdev, bool is_frozen);
पूर्णांक hisi_qm_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs);
व्योम hisi_qm_dev_err_init(काष्ठा hisi_qm *qm);
व्योम hisi_qm_dev_err_uninit(काष्ठा hisi_qm *qm);
pci_ers_result_t hisi_qm_dev_err_detected(काष्ठा pci_dev *pdev,
					  pci_channel_state_t state);
pci_ers_result_t hisi_qm_dev_slot_reset(काष्ठा pci_dev *pdev);
व्योम hisi_qm_reset_prepare(काष्ठा pci_dev *pdev);
व्योम hisi_qm_reset_करोne(काष्ठा pci_dev *pdev);

काष्ठा hisi_acc_sgl_pool;
काष्ठा hisi_acc_hw_sgl *hisi_acc_sg_buf_map_to_hw_sgl(काष्ठा device *dev,
	काष्ठा scatterlist *sgl, काष्ठा hisi_acc_sgl_pool *pool,
	u32 index, dma_addr_t *hw_sgl_dma);
व्योम hisi_acc_sg_buf_unmap(काष्ठा device *dev, काष्ठा scatterlist *sgl,
			   काष्ठा hisi_acc_hw_sgl *hw_sgl);
काष्ठा hisi_acc_sgl_pool *hisi_acc_create_sgl_pool(काष्ठा device *dev,
						   u32 count, u32 sge_nr);
व्योम hisi_acc_मुक्त_sgl_pool(काष्ठा device *dev,
			    काष्ठा hisi_acc_sgl_pool *pool);
पूर्णांक hisi_qm_alloc_qps_node(काष्ठा hisi_qm_list *qm_list, पूर्णांक qp_num,
			   u8 alg_type, पूर्णांक node, काष्ठा hisi_qp **qps);
व्योम hisi_qm_मुक्त_qps(काष्ठा hisi_qp **qps, पूर्णांक qp_num);
व्योम hisi_qm_dev_shutकरोwn(काष्ठा pci_dev *pdev);
व्योम hisi_qm_रुको_task_finish(काष्ठा hisi_qm *qm, काष्ठा hisi_qm_list *qm_list);
पूर्णांक hisi_qm_alg_रेजिस्टर(काष्ठा hisi_qm *qm, काष्ठा hisi_qm_list *qm_list);
व्योम hisi_qm_alg_unरेजिस्टर(काष्ठा hisi_qm *qm, काष्ठा hisi_qm_list *qm_list);
#पूर्ण_अगर
