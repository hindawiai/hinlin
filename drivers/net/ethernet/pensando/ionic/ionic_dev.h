<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#अगर_अघोषित _IONIC_DEV_H_
#घोषणा _IONIC_DEV_H_

#समावेश <linux/atomic.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>

#समावेश "ionic_if.h"
#समावेश "ionic_regs.h"

#घोषणा IONIC_MAX_TX_DESC		8192
#घोषणा IONIC_MAX_RX_DESC		16384
#घोषणा IONIC_MIN_TXRX_DESC		64
#घोषणा IONIC_DEF_TXRX_DESC		4096
#घोषणा IONIC_RX_FILL_THRESHOLD		16
#घोषणा IONIC_RX_FILL_DIV		8
#घोषणा IONIC_LIFS_MAX			1024
#घोषणा IONIC_WATCHDOG_SECS		5
#घोषणा IONIC_ITR_COAL_USEC_DEFAULT	64

#घोषणा IONIC_DEV_CMD_REG_VERSION	1
#घोषणा IONIC_DEV_INFO_REG_COUNT	32
#घोषणा IONIC_DEV_CMD_REG_COUNT		32

काष्ठा ionic_dev_bar अणु
	व्योम __iomem *vaddr;
	phys_addr_t bus_addr;
	अचिन्हित दीर्घ len;
	पूर्णांक res_index;
पूर्ण;

#अगर_अघोषित __CHECKER__
/* Registers */
अटल_निश्चित(माप(काष्ठा ionic_पूर्णांकr) == 32);

अटल_निश्चित(माप(काष्ठा ionic_करोorbell) == 8);
अटल_निश्चित(माप(काष्ठा ionic_पूर्णांकr_status) == 8);
अटल_निश्चित(माप(जोड़ ionic_dev_regs) == 4096);
अटल_निश्चित(माप(जोड़ ionic_dev_info_regs) == 2048);
अटल_निश्चित(माप(जोड़ ionic_dev_cmd_regs) == 2048);
अटल_निश्चित(माप(काष्ठा ionic_lअगर_stats) == 1024);

अटल_निश्चित(माप(काष्ठा ionic_admin_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_admin_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_nop_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_nop_comp) == 16);

/* Device commands */
अटल_निश्चित(माप(काष्ठा ionic_dev_identअगरy_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_dev_identअगरy_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_dev_init_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_dev_init_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_dev_reset_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_dev_reset_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_dev_getattr_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_dev_getattr_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_dev_setattr_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_dev_setattr_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_lअगर_setphc_cmd) == 64);

/* Port commands */
अटल_निश्चित(माप(काष्ठा ionic_port_identअगरy_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_port_identअगरy_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_port_init_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_port_init_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_port_reset_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_port_reset_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_port_getattr_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_port_getattr_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_port_setattr_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_port_setattr_comp) == 16);

/* LIF commands */
अटल_निश्चित(माप(काष्ठा ionic_lअगर_init_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_lअगर_init_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_lअगर_reset_cmd) == 64);
अटल_निश्चित(माप(ionic_lअगर_reset_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_lअगर_getattr_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_lअगर_getattr_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_lअगर_setattr_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_lअगर_setattr_comp) == 16);

अटल_निश्चित(माप(काष्ठा ionic_q_init_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_q_init_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_q_control_cmd) == 64);
अटल_निश्चित(माप(ionic_q_control_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_q_identअगरy_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_q_identअगरy_comp) == 16);

अटल_निश्चित(माप(काष्ठा ionic_rx_mode_set_cmd) == 64);
अटल_निश्चित(माप(ionic_rx_mode_set_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_rx_filter_add_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_rx_filter_add_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_rx_filter_del_cmd) == 64);
अटल_निश्चित(माप(ionic_rx_filter_del_comp) == 16);

/* RDMA commands */
अटल_निश्चित(माप(काष्ठा ionic_rdma_reset_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_rdma_queue_cmd) == 64);

/* Events */
अटल_निश्चित(माप(काष्ठा ionic_notअगरyq_cmd) == 4);
अटल_निश्चित(माप(जोड़ ionic_notअगरyq_comp) == 64);
अटल_निश्चित(माप(काष्ठा ionic_notअगरyq_event) == 64);
अटल_निश्चित(माप(काष्ठा ionic_link_change_event) == 64);
अटल_निश्चित(माप(काष्ठा ionic_reset_event) == 64);
अटल_निश्चित(माप(काष्ठा ionic_heartbeat_event) == 64);
अटल_निश्चित(माप(काष्ठा ionic_log_event) == 64);

/* I/O */
अटल_निश्चित(माप(काष्ठा ionic_txq_desc) == 16);
अटल_निश्चित(माप(काष्ठा ionic_txq_sg_desc) == 128);
अटल_निश्चित(माप(काष्ठा ionic_txq_comp) == 16);

अटल_निश्चित(माप(काष्ठा ionic_rxq_desc) == 16);
अटल_निश्चित(माप(काष्ठा ionic_rxq_sg_desc) == 128);
अटल_निश्चित(माप(काष्ठा ionic_rxq_comp) == 16);

/* SR/IOV */
अटल_निश्चित(माप(काष्ठा ionic_vf_setattr_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_vf_setattr_comp) == 16);
अटल_निश्चित(माप(काष्ठा ionic_vf_getattr_cmd) == 64);
अटल_निश्चित(माप(काष्ठा ionic_vf_getattr_comp) == 16);
#पूर्ण_अगर /* __CHECKER__ */

काष्ठा ionic_devinfo अणु
	u8 asic_type;
	u8 asic_rev;
	अक्षर fw_version[IONIC_DEVINFO_FWVERS_BUFLEN + 1];
	अक्षर serial_num[IONIC_DEVINFO_SERIAL_BUFLEN + 1];
पूर्ण;

काष्ठा ionic_dev अणु
	जोड़ ionic_dev_info_regs __iomem *dev_info_regs;
	जोड़ ionic_dev_cmd_regs __iomem *dev_cmd_regs;
	काष्ठा ionic_hwstamp_regs __iomem *hwstamp_regs;

	atomic_दीर्घ_t last_check_समय;
	अचिन्हित दीर्घ last_hb_समय;
	u32 last_fw_hb;
	bool fw_hb_पढ़ोy;
	bool fw_status_पढ़ोy;

	u64 __iomem *db_pages;
	dma_addr_t phy_db_pages;

	काष्ठा ionic_पूर्णांकr __iomem *पूर्णांकr_ctrl;
	u64 __iomem *पूर्णांकr_status;

	u32 port_info_sz;
	काष्ठा ionic_port_info *port_info;
	dma_addr_t port_info_pa;

	काष्ठा ionic_devinfo dev_info;
पूर्ण;

काष्ठा ionic_cq_info अणु
	जोड़ अणु
		व्योम *cq_desc;
		काष्ठा ionic_txq_comp *txcq;
		काष्ठा ionic_rxq_comp *rxcq;
		काष्ठा ionic_admin_comp *admincq;
		काष्ठा ionic_notअगरyq_event *notअगरyq;
	पूर्ण;
पूर्ण;

काष्ठा ionic_queue;
काष्ठा ionic_qcq;
काष्ठा ionic_desc_info;

प्रकार व्योम (*ionic_desc_cb)(काष्ठा ionic_queue *q,
			      काष्ठा ionic_desc_info *desc_info,
			      काष्ठा ionic_cq_info *cq_info, व्योम *cb_arg);

#घोषणा IONIC_PAGE_SIZE				PAGE_SIZE
#घोषणा IONIC_PAGE_SPLIT_SZ			(PAGE_SIZE / 2)
#घोषणा IONIC_PAGE_GFP_MASK			(GFP_ATOMIC | __GFP_NOWARN |\
						 __GFP_COMP | __GFP_MEMALLOC)

काष्ठा ionic_buf_info अणु
	काष्ठा page *page;
	dma_addr_t dma_addr;
	u32 page_offset;
	u32 len;
पूर्ण;

#घोषणा IONIC_MAX_FRAGS			(1 + IONIC_TX_MAX_SG_ELEMS_V1)

काष्ठा ionic_desc_info अणु
	जोड़ अणु
		व्योम *desc;
		काष्ठा ionic_txq_desc *txq_desc;
		काष्ठा ionic_rxq_desc *rxq_desc;
		काष्ठा ionic_admin_cmd *adminq_desc;
	पूर्ण;
	जोड़ अणु
		व्योम *sg_desc;
		काष्ठा ionic_txq_sg_desc *txq_sg_desc;
		काष्ठा ionic_rxq_sg_desc *rxq_sgl_desc;
	पूर्ण;
	अचिन्हित पूर्णांक bytes;
	अचिन्हित पूर्णांक nbufs;
	काष्ठा ionic_buf_info bufs[IONIC_MAX_FRAGS];
	ionic_desc_cb cb;
	व्योम *cb_arg;
पूर्ण;

#घोषणा IONIC_QUEUE_NAME_MAX_SZ		32

काष्ठा ionic_queue अणु
	काष्ठा device *dev;
	काष्ठा ionic_lअगर *lअगर;
	काष्ठा ionic_desc_info *info;
	u64 dbval;
	u16 head_idx;
	u16 tail_idx;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक num_descs;
	अचिन्हित पूर्णांक max_sg_elems;
	u64 features;
	u64 dbell_count;
	u64 stop;
	u64 wake;
	u64 drop;
	काष्ठा ionic_dev *idev;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक hw_index;
	अचिन्हित पूर्णांक hw_type;
	जोड़ अणु
		व्योम *base;
		काष्ठा ionic_txq_desc *txq;
		काष्ठा ionic_rxq_desc *rxq;
		काष्ठा ionic_admin_cmd *adminq;
	पूर्ण;
	जोड़ अणु
		व्योम *sg_base;
		काष्ठा ionic_txq_sg_desc *txq_sgl;
		काष्ठा ionic_rxq_sg_desc *rxq_sgl;
	पूर्ण;
	dma_addr_t base_pa;
	dma_addr_t sg_base_pa;
	अचिन्हित पूर्णांक desc_size;
	अचिन्हित पूर्णांक sg_desc_size;
	अचिन्हित पूर्णांक pid;
	अक्षर name[IONIC_QUEUE_NAME_MAX_SZ];
पूर्ण ____cacheline_aligned_in_smp;

#घोषणा IONIC_INTR_INDEX_NOT_ASSIGNED	-1
#घोषणा IONIC_INTR_NAME_MAX_SZ		32

काष्ठा ionic_पूर्णांकr_info अणु
	अक्षर name[IONIC_INTR_NAME_MAX_SZ];
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक vector;
	u64 rearm_count;
	अचिन्हित पूर्णांक cpu;
	cpumask_t affinity_mask;
	u32 dim_coal_hw;
पूर्ण;

काष्ठा ionic_cq अणु
	काष्ठा ionic_lअगर *lअगर;
	काष्ठा ionic_cq_info *info;
	काष्ठा ionic_queue *bound_q;
	काष्ठा ionic_पूर्णांकr_info *bound_पूर्णांकr;
	u16 tail_idx;
	bool करोne_color;
	अचिन्हित पूर्णांक num_descs;
	अचिन्हित पूर्णांक desc_size;
	u64 compl_count;
	व्योम *base;
	dma_addr_t base_pa;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा ionic;

अटल अंतरभूत व्योम ionic_पूर्णांकr_init(काष्ठा ionic_dev *idev,
				   काष्ठा ionic_पूर्णांकr_info *पूर्णांकr,
				   अचिन्हित दीर्घ index)
अणु
	ionic_पूर्णांकr_clean(idev->पूर्णांकr_ctrl, index);
	पूर्णांकr->index = index;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ionic_q_space_avail(काष्ठा ionic_queue *q)
अणु
	अचिन्हित पूर्णांक avail = q->tail_idx;

	अगर (q->head_idx >= avail)
		avail += q->num_descs - q->head_idx - 1;
	अन्यथा
		avail -= q->head_idx + 1;

	वापस avail;
पूर्ण

अटल अंतरभूत bool ionic_q_has_space(काष्ठा ionic_queue *q, अचिन्हित पूर्णांक want)
अणु
	वापस ionic_q_space_avail(q) >= want;
पूर्ण

व्योम ionic_init_devinfo(काष्ठा ionic *ionic);
पूर्णांक ionic_dev_setup(काष्ठा ionic *ionic);

व्योम ionic_dev_cmd_go(काष्ठा ionic_dev *idev, जोड़ ionic_dev_cmd *cmd);
u8 ionic_dev_cmd_status(काष्ठा ionic_dev *idev);
bool ionic_dev_cmd_करोne(काष्ठा ionic_dev *idev);
व्योम ionic_dev_cmd_comp(काष्ठा ionic_dev *idev, जोड़ ionic_dev_cmd_comp *comp);

व्योम ionic_dev_cmd_identअगरy(काष्ठा ionic_dev *idev, u8 ver);
व्योम ionic_dev_cmd_init(काष्ठा ionic_dev *idev);
व्योम ionic_dev_cmd_reset(काष्ठा ionic_dev *idev);

व्योम ionic_dev_cmd_port_identअगरy(काष्ठा ionic_dev *idev);
व्योम ionic_dev_cmd_port_init(काष्ठा ionic_dev *idev);
व्योम ionic_dev_cmd_port_reset(काष्ठा ionic_dev *idev);
व्योम ionic_dev_cmd_port_state(काष्ठा ionic_dev *idev, u8 state);
व्योम ionic_dev_cmd_port_speed(काष्ठा ionic_dev *idev, u32 speed);
व्योम ionic_dev_cmd_port_स्वतःneg(काष्ठा ionic_dev *idev, u8 an_enable);
व्योम ionic_dev_cmd_port_fec(काष्ठा ionic_dev *idev, u8 fec_type);
व्योम ionic_dev_cmd_port_छोड़ो(काष्ठा ionic_dev *idev, u8 छोड़ो_type);

पूर्णांक ionic_set_vf_config(काष्ठा ionic *ionic, पूर्णांक vf, u8 attr, u8 *data);
व्योम ionic_dev_cmd_queue_identअगरy(काष्ठा ionic_dev *idev,
				  u16 lअगर_type, u8 qtype, u8 qver);
व्योम ionic_dev_cmd_lअगर_identअगरy(काष्ठा ionic_dev *idev, u8 type, u8 ver);
व्योम ionic_dev_cmd_lअगर_init(काष्ठा ionic_dev *idev, u16 lअगर_index,
			    dma_addr_t addr);
व्योम ionic_dev_cmd_lअगर_reset(काष्ठा ionic_dev *idev, u16 lअगर_index);
व्योम ionic_dev_cmd_adminq_init(काष्ठा ionic_dev *idev, काष्ठा ionic_qcq *qcq,
			       u16 lअगर_index, u16 पूर्णांकr_index);

पूर्णांक ionic_db_page_num(काष्ठा ionic_lअगर *lअगर, पूर्णांक pid);

पूर्णांक ionic_cq_init(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_cq *cq,
		  काष्ठा ionic_पूर्णांकr_info *पूर्णांकr,
		  अचिन्हित पूर्णांक num_descs, माप_प्रकार desc_size);
व्योम ionic_cq_map(काष्ठा ionic_cq *cq, व्योम *base, dma_addr_t base_pa);
व्योम ionic_cq_bind(काष्ठा ionic_cq *cq, काष्ठा ionic_queue *q);
प्रकार bool (*ionic_cq_cb)(काष्ठा ionic_cq *cq, काष्ठा ionic_cq_info *cq_info);
प्रकार व्योम (*ionic_cq_करोne_cb)(व्योम *करोne_arg);
अचिन्हित पूर्णांक ionic_cq_service(काष्ठा ionic_cq *cq, अचिन्हित पूर्णांक work_to_करो,
			      ionic_cq_cb cb, ionic_cq_करोne_cb करोne_cb,
			      व्योम *करोne_arg);

पूर्णांक ionic_q_init(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_dev *idev,
		 काष्ठा ionic_queue *q, अचिन्हित पूर्णांक index, स्थिर अक्षर *name,
		 अचिन्हित पूर्णांक num_descs, माप_प्रकार desc_size,
		 माप_प्रकार sg_desc_size, अचिन्हित पूर्णांक pid);
व्योम ionic_q_map(काष्ठा ionic_queue *q, व्योम *base, dma_addr_t base_pa);
व्योम ionic_q_sg_map(काष्ठा ionic_queue *q, व्योम *base, dma_addr_t base_pa);
व्योम ionic_q_post(काष्ठा ionic_queue *q, bool ring_करोorbell, ionic_desc_cb cb,
		  व्योम *cb_arg);
व्योम ionic_q_शुरुआत(काष्ठा ionic_queue *q, काष्ठा ionic_desc_info *start);
व्योम ionic_q_service(काष्ठा ionic_queue *q, काष्ठा ionic_cq_info *cq_info,
		     अचिन्हित पूर्णांक stop_index);
पूर्णांक ionic_heartbeat_check(काष्ठा ionic *ionic);

#पूर्ण_अगर /* _IONIC_DEV_H_ */
