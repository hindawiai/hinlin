<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2015 Linaro Ltd.
 * Copyright (c) 2015 Hisilicon Limited.
 */

#अगर_अघोषित _HISI_SAS_H_
#घोषणा _HISI_SAS_H_

#समावेश <linux/acpi.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-mq-pci.h>
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/lcm.h>
#समावेश <linux/libata.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/समयr.h>
#समावेश <scsi/sas_ata.h>
#समावेश <scsi/libsas.h>

#घोषणा HISI_SAS_MAX_PHYS	9
#घोषणा HISI_SAS_MAX_QUEUES	32
#घोषणा HISI_SAS_QUEUE_SLOTS	4096
#घोषणा HISI_SAS_MAX_ITCT_ENTRIES 1024
#घोषणा HISI_SAS_MAX_DEVICES HISI_SAS_MAX_ITCT_ENTRIES
#घोषणा HISI_SAS_RESET_BIT	0
#घोषणा HISI_SAS_REJECT_CMD_BIT	1
#घोषणा HISI_SAS_PM_BIT		2
#घोषणा HISI_SAS_MAX_COMMANDS (HISI_SAS_QUEUE_SLOTS)
#घोषणा HISI_SAS_RESERVED_IPTT  96
#घोषणा HISI_SAS_UNRESERVED_IPTT \
	(HISI_SAS_MAX_COMMANDS - HISI_SAS_RESERVED_IPTT)

#घोषणा HISI_SAS_IOST_ITCT_CACHE_NUM 64
#घोषणा HISI_SAS_IOST_ITCT_CACHE_DW_SZ 10
#घोषणा HISI_SAS_FIFO_DATA_DW_SIZE 32

#घोषणा HISI_SAS_STATUS_BUF_SZ (माप(काष्ठा hisi_sas_status_buffer))
#घोषणा HISI_SAS_COMMAND_TABLE_SZ (माप(जोड़ hisi_sas_command_table))

#घोषणा hisi_sas_status_buf_addr(buf) \
	((buf) + दुरत्व(काष्ठा hisi_sas_slot_buf_table, status_buffer))
#घोषणा hisi_sas_status_buf_addr_mem(slot) hisi_sas_status_buf_addr((slot)->buf)
#घोषणा hisi_sas_status_buf_addr_dma(slot) \
	hisi_sas_status_buf_addr((slot)->buf_dma)

#घोषणा hisi_sas_cmd_hdr_addr(buf) \
	((buf) + दुरत्व(काष्ठा hisi_sas_slot_buf_table, command_header))
#घोषणा hisi_sas_cmd_hdr_addr_mem(slot) hisi_sas_cmd_hdr_addr((slot)->buf)
#घोषणा hisi_sas_cmd_hdr_addr_dma(slot) hisi_sas_cmd_hdr_addr((slot)->buf_dma)

#घोषणा hisi_sas_sge_addr(buf) \
	((buf) + दुरत्व(काष्ठा hisi_sas_slot_buf_table, sge_page))
#घोषणा hisi_sas_sge_addr_mem(slot) hisi_sas_sge_addr((slot)->buf)
#घोषणा hisi_sas_sge_addr_dma(slot) hisi_sas_sge_addr((slot)->buf_dma)

#घोषणा hisi_sas_sge_dअगर_addr(buf) \
	((buf) + दुरत्व(काष्ठा hisi_sas_slot_dअगर_buf_table, sge_dअगर_page))
#घोषणा hisi_sas_sge_dअगर_addr_mem(slot) hisi_sas_sge_dअगर_addr((slot)->buf)
#घोषणा hisi_sas_sge_dअगर_addr_dma(slot) hisi_sas_sge_dअगर_addr((slot)->buf_dma)

#घोषणा HISI_SAS_MAX_SSP_RESP_SZ (माप(काष्ठा ssp_frame_hdr) + 1024)
#घोषणा HISI_SAS_MAX_SMP_RESP_SZ 1028
#घोषणा HISI_SAS_MAX_STP_RESP_SZ 28

#घोषणा HISI_SAS_SATA_PROTOCOL_NONDATA		0x1
#घोषणा HISI_SAS_SATA_PROTOCOL_PIO			0x2
#घोषणा HISI_SAS_SATA_PROTOCOL_DMA			0x4
#घोषणा HISI_SAS_SATA_PROTOCOL_FPDMA		0x8
#घोषणा HISI_SAS_SATA_PROTOCOL_ATAPI		0x10

#घोषणा HISI_SAS_DIF_PROT_MASK (SHOST_DIF_TYPE1_PROTECTION | \
				SHOST_DIF_TYPE2_PROTECTION | \
				SHOST_DIF_TYPE3_PROTECTION)

#घोषणा HISI_SAS_DIX_PROT_MASK (SHOST_DIX_TYPE1_PROTECTION | \
				SHOST_DIX_TYPE2_PROTECTION | \
				SHOST_DIX_TYPE3_PROTECTION)

#घोषणा HISI_SAS_PROT_MASK (HISI_SAS_DIF_PROT_MASK | HISI_SAS_DIX_PROT_MASK)

#घोषणा HISI_SAS_WAIT_PHYUP_TIMEOUT 20
#घोषणा CLEAR_ITCT_TIMEOUT	20

काष्ठा hisi_hba;

क्रमागत अणु
	PORT_TYPE_SAS = (1U << 1),
	PORT_TYPE_SATA = (1U << 0),
पूर्ण;

क्रमागत dev_status अणु
	HISI_SAS_DEV_INIT,
	HISI_SAS_DEV_NORMAL,
पूर्ण;

क्रमागत अणु
	HISI_SAS_INT_ABT_CMD = 0,
	HISI_SAS_INT_ABT_DEV = 1,
पूर्ण;

क्रमागत hisi_sas_dev_type अणु
	HISI_SAS_DEV_TYPE_STP = 0,
	HISI_SAS_DEV_TYPE_SSP,
	HISI_SAS_DEV_TYPE_SATA,
पूर्ण;

काष्ठा hisi_sas_hw_error अणु
	u32 irq_msk;
	u32 msk;
	पूर्णांक shअगरt;
	स्थिर अक्षर *msg;
	पूर्णांक reg;
	स्थिर काष्ठा hisi_sas_hw_error *sub;
पूर्ण;

काष्ठा hisi_sas_rst अणु
	काष्ठा hisi_hba *hisi_hba;
	काष्ठा completion *completion;
	काष्ठा work_काष्ठा work;
	bool करोne;
पूर्ण;

#घोषणा HISI_SAS_RST_WORK_INIT(r, c) \
	अणु	.hisi_hba = hisi_hba, \
		.completion = &c, \
		.work = __WORK_INITIALIZER(r.work, \
				hisi_sas_sync_rst_work_handler), \
		.करोne = false, \
		पूर्ण

#घोषणा HISI_SAS_DECLARE_RST_WORK_ON_STACK(r) \
	DECLARE_COMPLETION_ONSTACK(c); \
	काष्ठा hisi_sas_rst r = HISI_SAS_RST_WORK_INIT(r, c)

क्रमागत hisi_sas_bit_err_type अणु
	HISI_SAS_ERR_SINGLE_BIT_ECC = 0x0,
	HISI_SAS_ERR_MULTI_BIT_ECC = 0x1,
पूर्ण;

क्रमागत hisi_sas_phy_event अणु
	HISI_PHYE_PHY_UP   = 0U,
	HISI_PHYE_LINK_RESET,
	HISI_PHYES_NUM,
पूर्ण;

काष्ठा hisi_sas_debugfs_fअगरo अणु
	u32 संकेत_sel;
	u32 dump_msk;
	u32 dump_mode;
	u32 trigger;
	u32 trigger_msk;
	u32 trigger_mode;
	u32 rd_data[HISI_SAS_FIFO_DATA_DW_SIZE];
पूर्ण;

काष्ठा hisi_sas_phy अणु
	काष्ठा work_काष्ठा	works[HISI_PHYES_NUM];
	काष्ठा hisi_hba	*hisi_hba;
	काष्ठा hisi_sas_port	*port;
	काष्ठा asd_sas_phy	sas_phy;
	काष्ठा sas_identअगरy	identअगरy;
	काष्ठा completion *reset_completion;
	काष्ठा समयr_list समयr;
	spinlock_t lock;
	u64		port_id; /* from hw */
	u64		frame_rcvd_size;
	u8		frame_rcvd[32];
	u8		phy_attached;
	u8		in_reset;
	u8		reserved[2];
	u32		phy_type;
	u32		code_violation_err_count;
	क्रमागत sas_linkrate	minimum_linkrate;
	क्रमागत sas_linkrate	maximum_linkrate;
	पूर्णांक enable;
	atomic_t करोwn_cnt;

	/* Trace FIFO */
	काष्ठा hisi_sas_debugfs_fअगरo fअगरo;
पूर्ण;

काष्ठा hisi_sas_port अणु
	काष्ठा asd_sas_port	sas_port;
	u8	port_attached;
	u8	id; /* from hw */
पूर्ण;

काष्ठा hisi_sas_cq अणु
	काष्ठा hisi_hba *hisi_hba;
	स्थिर काष्ठा cpumask *irq_mask;
	पूर्णांक	rd_poपूर्णांक;
	पूर्णांक	id;
	पूर्णांक	irq_no;
पूर्ण;

काष्ठा hisi_sas_dq अणु
	काष्ठा hisi_hba *hisi_hba;
	काष्ठा list_head list;
	spinlock_t lock;
	पूर्णांक	wr_poपूर्णांक;
	पूर्णांक	id;
पूर्ण;

काष्ठा hisi_sas_device अणु
	काष्ठा hisi_hba		*hisi_hba;
	काष्ठा करोमुख्य_device	*sas_device;
	काष्ठा completion *completion;
	काष्ठा hisi_sas_dq	*dq;
	काष्ठा list_head	list;
	क्रमागत sas_device_type	dev_type;
	क्रमागत dev_status dev_status;
	पूर्णांक device_id;
	पूर्णांक sata_idx;
	spinlock_t lock; /* For protecting slots */
पूर्ण;

काष्ठा hisi_sas_पंचांगf_task अणु
	पूर्णांक क्रमce_phy;
	पूर्णांक phy_id;
	u8 पंचांगf;
	u16 tag_of_task_to_be_managed;
पूर्ण;

काष्ठा hisi_sas_slot अणु
	काष्ठा list_head entry;
	काष्ठा list_head delivery;
	काष्ठा sas_task *task;
	काष्ठा hisi_sas_port	*port;
	u64	n_elem;
	u64	n_elem_dअगर;
	पूर्णांक	dlvry_queue;
	पूर्णांक	dlvry_queue_slot;
	पूर्णांक	cmplt_queue;
	पूर्णांक	cmplt_queue_slot;
	पूर्णांक	पात;
	पूर्णांक	पढ़ोy;
	पूर्णांक	device_id;
	व्योम	*cmd_hdr;
	dma_addr_t cmd_hdr_dma;
	काष्ठा समयr_list पूर्णांकernal_पात_समयr;
	bool is_पूर्णांकernal;
	काष्ठा hisi_sas_पंचांगf_task *पंचांगf;
	/* Do not reorder/change members after here */
	व्योम	*buf;
	dma_addr_t buf_dma;
	u16	idx;
पूर्ण;

काष्ठा hisi_sas_iost_itct_cache अणु
	u32 data[HISI_SAS_IOST_ITCT_CACHE_DW_SZ];
पूर्ण;

क्रमागत hisi_sas_debugfs_reg_array_member अणु
	DEBUGFS_GLOBAL = 0,
	DEBUGFS_AXI,
	DEBUGFS_RAS,
	DEBUGFS_REGS_NUM
पूर्ण;

क्रमागत hisi_sas_debugfs_cache_type अणु
	HISI_SAS_ITCT_CACHE,
	HISI_SAS_IOST_CACHE,
पूर्ण;

क्रमागत hisi_sas_debugfs_bist_ffe_cfg अणु
	FFE_SAS_1_5_GBPS,
	FFE_SAS_3_0_GBPS,
	FFE_SAS_6_0_GBPS,
	FFE_SAS_12_0_GBPS,
	FFE_RESV,
	FFE_SATA_1_5_GBPS,
	FFE_SATA_3_0_GBPS,
	FFE_SATA_6_0_GBPS,
	FFE_CFG_MAX
पूर्ण;

क्रमागत hisi_sas_debugfs_bist_fixed_code अणु
	FIXED_CODE,
	FIXED_CODE_1,
	FIXED_CODE_MAX
पूर्ण;

क्रमागत अणु
	HISI_SAS_BIST_CODE_MODE_PRBS7,
	HISI_SAS_BIST_CODE_MODE_PRBS23,
	HISI_SAS_BIST_CODE_MODE_PRBS31,
	HISI_SAS_BIST_CODE_MODE_JTPAT,
	HISI_SAS_BIST_CODE_MODE_CJTPAT,
	HISI_SAS_BIST_CODE_MODE_SCRAMBED_0,
	HISI_SAS_BIST_CODE_MODE_TRAIN,
	HISI_SAS_BIST_CODE_MODE_TRAIN_DONE,
	HISI_SAS_BIST_CODE_MODE_HFTP,
	HISI_SAS_BIST_CODE_MODE_MFTP,
	HISI_SAS_BIST_CODE_MODE_LFTP,
	HISI_SAS_BIST_CODE_MODE_FIXED_DATA,
पूर्ण;

काष्ठा hisi_sas_hw अणु
	पूर्णांक (*hw_init)(काष्ठा hisi_hba *hisi_hba);
	पूर्णांक (*पूर्णांकerrupt_preinit)(काष्ठा hisi_hba *hisi_hba);
	व्योम (*setup_itct)(काष्ठा hisi_hba *hisi_hba,
			   काष्ठा hisi_sas_device *device);
	पूर्णांक (*slot_index_alloc)(काष्ठा hisi_hba *hisi_hba,
				काष्ठा करोमुख्य_device *device);
	काष्ठा hisi_sas_device *(*alloc_dev)(काष्ठा करोमुख्य_device *device);
	व्योम (*sl_notअगरy_ssp)(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no);
	व्योम (*start_delivery)(काष्ठा hisi_sas_dq *dq);
	व्योम (*prep_ssp)(काष्ठा hisi_hba *hisi_hba,
			काष्ठा hisi_sas_slot *slot);
	व्योम (*prep_smp)(काष्ठा hisi_hba *hisi_hba,
			काष्ठा hisi_sas_slot *slot);
	व्योम (*prep_stp)(काष्ठा hisi_hba *hisi_hba,
			काष्ठा hisi_sas_slot *slot);
	व्योम (*prep_पात)(काष्ठा hisi_hba *hisi_hba,
			  काष्ठा hisi_sas_slot *slot,
			  पूर्णांक device_id, पूर्णांक पात_flag, पूर्णांक tag_to_पात);
	व्योम (*phys_init)(काष्ठा hisi_hba *hisi_hba);
	व्योम (*phy_start)(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no);
	व्योम (*phy_disable)(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no);
	व्योम (*phy_hard_reset)(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no);
	व्योम (*get_events)(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no);
	व्योम (*phy_set_linkrate)(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no,
			काष्ठा sas_phy_linkrates *linkrates);
	क्रमागत sas_linkrate (*phy_get_max_linkrate)(व्योम);
	पूर्णांक (*clear_itct)(काष्ठा hisi_hba *hisi_hba,
			  काष्ठा hisi_sas_device *dev);
	व्योम (*मुक्त_device)(काष्ठा hisi_sas_device *sas_dev);
	पूर्णांक (*get_wideport_biपंचांगap)(काष्ठा hisi_hba *hisi_hba, पूर्णांक port_id);
	व्योम (*dereg_device)(काष्ठा hisi_hba *hisi_hba,
				काष्ठा करोमुख्य_device *device);
	पूर्णांक (*soft_reset)(काष्ठा hisi_hba *hisi_hba);
	u32 (*get_phys_state)(काष्ठा hisi_hba *hisi_hba);
	पूर्णांक (*ग_लिखो_gpio)(काष्ठा hisi_hba *hisi_hba, u8 reg_type,
				u8 reg_index, u8 reg_count, u8 *ग_लिखो_data);
	व्योम (*रुको_cmds_complete_समयout)(काष्ठा hisi_hba *hisi_hba,
					   पूर्णांक delay_ms, पूर्णांक समयout_ms);
	व्योम (*debugfs_snapshot_regs)(काष्ठा hisi_hba *hisi_hba);
	पूर्णांक complete_hdr_size;
	काष्ठा scsi_host_ढाँचा *sht;
पूर्ण;

#घोषणा HISI_SAS_MAX_DEBUGFS_DUMP (50)

काष्ठा hisi_sas_debugfs_cq अणु
	काष्ठा hisi_sas_cq *cq;
	व्योम *complete_hdr;
पूर्ण;

काष्ठा hisi_sas_debugfs_dq अणु
	काष्ठा hisi_sas_dq *dq;
	काष्ठा hisi_sas_cmd_hdr *hdr;
पूर्ण;

काष्ठा hisi_sas_debugfs_regs अणु
	काष्ठा hisi_hba *hisi_hba;
	u32 *data;
पूर्ण;

काष्ठा hisi_sas_debugfs_port अणु
	काष्ठा hisi_sas_phy *phy;
	u32 *data;
पूर्ण;

काष्ठा hisi_sas_debugfs_iost अणु
	काष्ठा hisi_sas_iost *iost;
पूर्ण;

काष्ठा hisi_sas_debugfs_itct अणु
	काष्ठा hisi_sas_itct *itct;
पूर्ण;

काष्ठा hisi_sas_debugfs_iost_cache अणु
	काष्ठा hisi_sas_iost_itct_cache *cache;
पूर्ण;

काष्ठा hisi_sas_debugfs_itct_cache अणु
	काष्ठा hisi_sas_iost_itct_cache *cache;
पूर्ण;

काष्ठा hisi_hba अणु
	/* This must be the first element, used by SHOST_TO_SAS_HA */
	काष्ठा sas_ha_काष्ठा *p;

	काष्ठा platक्रमm_device *platक्रमm_dev;
	काष्ठा pci_dev *pci_dev;
	काष्ठा device *dev;

	पूर्णांक prot_mask;

	व्योम __iomem *regs;
	व्योम __iomem *sgpio_regs;
	काष्ठा regmap *ctrl;
	u32 ctrl_reset_reg;
	u32 ctrl_reset_sts_reg;
	u32 ctrl_घड़ी_ena_reg;
	u32 refclk_frequency_mhz;
	u8 sas_addr[SAS_ADDR_SIZE];

	पूर्णांक *irq_map; /* v2 hw */

	पूर्णांक n_phy;
	spinlock_t lock;
	काष्ठा semaphore sem;

	काष्ठा समयr_list समयr;
	काष्ठा workqueue_काष्ठा *wq;

	पूर्णांक slot_index_count;
	पूर्णांक last_slot_index;
	पूर्णांक last_dev_id;
	अचिन्हित दीर्घ *slot_index_tags;
	अचिन्हित दीर्घ reject_stp_links_msk;

	/* SCSI/SAS glue */
	काष्ठा sas_ha_काष्ठा sha;
	काष्ठा Scsi_Host *shost;

	काष्ठा hisi_sas_cq cq[HISI_SAS_MAX_QUEUES];
	काष्ठा hisi_sas_dq dq[HISI_SAS_MAX_QUEUES];
	काष्ठा hisi_sas_phy phy[HISI_SAS_MAX_PHYS];
	काष्ठा hisi_sas_port port[HISI_SAS_MAX_PHYS];

	पूर्णांक	queue_count;

	काष्ठा hisi_sas_device	devices[HISI_SAS_MAX_DEVICES];
	काष्ठा hisi_sas_cmd_hdr	*cmd_hdr[HISI_SAS_MAX_QUEUES];
	dma_addr_t cmd_hdr_dma[HISI_SAS_MAX_QUEUES];
	व्योम *complete_hdr[HISI_SAS_MAX_QUEUES];
	dma_addr_t complete_hdr_dma[HISI_SAS_MAX_QUEUES];
	काष्ठा hisi_sas_initial_fis *initial_fis;
	dma_addr_t initial_fis_dma;
	काष्ठा hisi_sas_itct *itct;
	dma_addr_t itct_dma;
	काष्ठा hisi_sas_iost *iost;
	dma_addr_t iost_dma;
	काष्ठा hisi_sas_अवरोधpoपूर्णांक *अवरोधpoपूर्णांक;
	dma_addr_t अवरोधpoपूर्णांक_dma;
	काष्ठा hisi_sas_अवरोधpoपूर्णांक *sata_अवरोधpoपूर्णांक;
	dma_addr_t sata_अवरोधpoपूर्णांक_dma;
	काष्ठा hisi_sas_slot	*slot_info;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा hisi_sas_hw *hw;	/* Low level hw पूर्णांकerface */
	अचिन्हित दीर्घ sata_dev_biपंचांगap[BITS_TO_LONGS(HISI_SAS_MAX_DEVICES)];
	काष्ठा work_काष्ठा rst_work;
	काष्ठा work_काष्ठा debugfs_work;
	u32 phy_state;
	u32 पूर्णांकr_coal_ticks;	/* Time of पूर्णांकerrupt coalesce in us */
	u32 पूर्णांकr_coal_count;	/* Interrupt count to coalesce */

	पूर्णांक cq_nvecs;

	/* bist */
	क्रमागत sas_linkrate debugfs_bist_linkrate;
	पूर्णांक debugfs_bist_code_mode;
	पूर्णांक debugfs_bist_phy_no;
	पूर्णांक debugfs_bist_mode;
	u32 debugfs_bist_cnt;
	पूर्णांक debugfs_bist_enable;
	u32 debugfs_bist_ffe[HISI_SAS_MAX_PHYS][FFE_CFG_MAX];
	u32 debugfs_bist_fixed_code[FIXED_CODE_MAX];

	/* debugfs memories */
	/* Put Global AXI and RAS Register पूर्णांकo रेजिस्टर array */
	काष्ठा hisi_sas_debugfs_regs debugfs_regs[HISI_SAS_MAX_DEBUGFS_DUMP][DEBUGFS_REGS_NUM];
	काष्ठा hisi_sas_debugfs_port debugfs_port_reg[HISI_SAS_MAX_DEBUGFS_DUMP][HISI_SAS_MAX_PHYS];
	काष्ठा hisi_sas_debugfs_cq debugfs_cq[HISI_SAS_MAX_DEBUGFS_DUMP][HISI_SAS_MAX_QUEUES];
	काष्ठा hisi_sas_debugfs_dq debugfs_dq[HISI_SAS_MAX_DEBUGFS_DUMP][HISI_SAS_MAX_QUEUES];
	काष्ठा hisi_sas_debugfs_iost debugfs_iost[HISI_SAS_MAX_DEBUGFS_DUMP];
	काष्ठा hisi_sas_debugfs_itct debugfs_itct[HISI_SAS_MAX_DEBUGFS_DUMP];
	काष्ठा hisi_sas_debugfs_iost_cache debugfs_iost_cache[HISI_SAS_MAX_DEBUGFS_DUMP];
	काष्ठा hisi_sas_debugfs_itct_cache debugfs_itct_cache[HISI_SAS_MAX_DEBUGFS_DUMP];

	u64 debugfs_बारtamp[HISI_SAS_MAX_DEBUGFS_DUMP];
	पूर्णांक debugfs_dump_index;
	काष्ठा dentry *debugfs_dir;
	काष्ठा dentry *debugfs_dump_dentry;
	काष्ठा dentry *debugfs_bist_dentry;
	काष्ठा dentry *debugfs_fअगरo_dentry;
पूर्ण;

/* Generic HW DMA host memory काष्ठाures */
/* Delivery queue header */
काष्ठा hisi_sas_cmd_hdr अणु
	/* dw0 */
	__le32 dw0;

	/* dw1 */
	__le32 dw1;

	/* dw2 */
	__le32 dw2;

	/* dw3 */
	__le32 transfer_tags;

	/* dw4 */
	__le32 data_transfer_len;

	/* dw5 */
	__le32 first_burst_num;

	/* dw6 */
	__le32 sg_len;

	/* dw7 */
	__le32 dw7;

	/* dw8-9 */
	__le64 cmd_table_addr;

	/* dw10-11 */
	__le64 sts_buffer_addr;

	/* dw12-13 */
	__le64 prd_table_addr;

	/* dw14-15 */
	__le64 dअगर_prd_table_addr;
पूर्ण;

काष्ठा hisi_sas_itct अणु
	__le64 qw0;
	__le64 sas_addr;
	__le64 qw2;
	__le64 qw3;
	__le64 qw4_15[12];
पूर्ण;

काष्ठा hisi_sas_iost अणु
	__le64 qw0;
	__le64 qw1;
	__le64 qw2;
	__le64 qw3;
पूर्ण;

काष्ठा hisi_sas_err_record अणु
	u32	data[4];
पूर्ण;

काष्ठा hisi_sas_initial_fis अणु
	काष्ठा hisi_sas_err_record err_record;
	काष्ठा dev_to_host_fis fis;
	u32 rsvd[3];
पूर्ण;

काष्ठा hisi_sas_अवरोधpoपूर्णांक अणु
	u8	data[128];
पूर्ण;

काष्ठा hisi_sas_sata_अवरोधpoपूर्णांक अणु
	काष्ठा hisi_sas_अवरोधpoपूर्णांक tag[32];
पूर्ण;

काष्ठा hisi_sas_sge अणु
	__le64 addr;
	__le32 page_ctrl_0;
	__le32 page_ctrl_1;
	__le32 data_len;
	__le32 data_off;
पूर्ण;

काष्ठा hisi_sas_command_table_smp अणु
	u8 bytes[44];
पूर्ण;

काष्ठा hisi_sas_command_table_stp अणु
	काष्ठा	host_to_dev_fis command_fis;
	u8	dummy[12];
	u8	atapi_cdb[ATAPI_CDB_LEN];
पूर्ण;

#घोषणा HISI_SAS_SGE_PAGE_CNT (124)
काष्ठा hisi_sas_sge_page अणु
	काष्ठा hisi_sas_sge sge[HISI_SAS_SGE_PAGE_CNT];
पूर्ण  __aligned(16);

#घोषणा HISI_SAS_SGE_DIF_PAGE_CNT   HISI_SAS_SGE_PAGE_CNT
काष्ठा hisi_sas_sge_dअगर_page अणु
	काष्ठा hisi_sas_sge sge[HISI_SAS_SGE_DIF_PAGE_CNT];
पूर्ण  __aligned(16);

काष्ठा hisi_sas_command_table_ssp अणु
	काष्ठा ssp_frame_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा ssp_command_iu task;
			u32 prot[7];
		पूर्ण;
		काष्ठा ssp_पंचांगf_iu ssp_task;
		काष्ठा xfer_rdy_iu xfer_rdy;
		काष्ठा ssp_response_iu ssp_res;
	पूर्ण u;
पूर्ण;

जोड़ hisi_sas_command_table अणु
	काष्ठा hisi_sas_command_table_ssp ssp;
	काष्ठा hisi_sas_command_table_smp smp;
	काष्ठा hisi_sas_command_table_stp stp;
पूर्ण  __aligned(16);

काष्ठा hisi_sas_status_buffer अणु
	काष्ठा hisi_sas_err_record err;
	u8	iu[1024];
पूर्ण  __aligned(16);

काष्ठा hisi_sas_slot_buf_table अणु
	काष्ठा hisi_sas_status_buffer status_buffer;
	जोड़ hisi_sas_command_table command_header;
	काष्ठा hisi_sas_sge_page sge_page;
पूर्ण;

काष्ठा hisi_sas_slot_dअगर_buf_table अणु
	काष्ठा hisi_sas_slot_buf_table slot_buf;
	काष्ठा hisi_sas_sge_dअगर_page sge_dअगर_page;
पूर्ण;

बाह्य काष्ठा scsi_transport_ढाँचा *hisi_sas_stt;

बाह्य bool hisi_sas_debugfs_enable;
बाह्य u32 hisi_sas_debugfs_dump_count;
बाह्य काष्ठा dentry *hisi_sas_debugfs_dir;

बाह्य व्योम hisi_sas_stop_phys(काष्ठा hisi_hba *hisi_hba);
बाह्य पूर्णांक hisi_sas_alloc(काष्ठा hisi_hba *hisi_hba);
बाह्य व्योम hisi_sas_मुक्त(काष्ठा hisi_hba *hisi_hba);
बाह्य u8 hisi_sas_get_ata_protocol(काष्ठा host_to_dev_fis *fis,
				पूर्णांक direction);
बाह्य काष्ठा hisi_sas_port *to_hisi_sas_port(काष्ठा asd_sas_port *sas_port);
बाह्य व्योम hisi_sas_sata_करोne(काष्ठा sas_task *task,
			    काष्ठा hisi_sas_slot *slot);
बाह्य पूर्णांक hisi_sas_get_fw_info(काष्ठा hisi_hba *hisi_hba);
बाह्य पूर्णांक hisi_sas_probe(काष्ठा platक्रमm_device *pdev,
			  स्थिर काष्ठा hisi_sas_hw *ops);
बाह्य पूर्णांक hisi_sas_हटाओ(काष्ठा platक्रमm_device *pdev);

बाह्य पूर्णांक hisi_sas_slave_configure(काष्ठा scsi_device *sdev);
बाह्य पूर्णांक hisi_sas_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय);
बाह्य व्योम hisi_sas_scan_start(काष्ठा Scsi_Host *shost);
बाह्य पूर्णांक hisi_sas_host_reset(काष्ठा Scsi_Host *shost, पूर्णांक reset_type);
बाह्य व्योम hisi_sas_phy_enable(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no,
				पूर्णांक enable);
बाह्य व्योम hisi_sas_phy_करोwn(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no, पूर्णांक rdy,
			      gfp_t gfp_flags);
बाह्य व्योम hisi_sas_slot_task_मुक्त(काष्ठा hisi_hba *hisi_hba,
				    काष्ठा sas_task *task,
				    काष्ठा hisi_sas_slot *slot);
बाह्य व्योम hisi_sas_init_mem(काष्ठा hisi_hba *hisi_hba);
बाह्य व्योम hisi_sas_rst_work_handler(काष्ठा work_काष्ठा *work);
बाह्य व्योम hisi_sas_sync_rst_work_handler(काष्ठा work_काष्ठा *work);
बाह्य व्योम hisi_sas_sync_irqs(काष्ठा hisi_hba *hisi_hba);
बाह्य व्योम hisi_sas_phy_oob_पढ़ोy(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no);
बाह्य bool hisi_sas_notअगरy_phy_event(काष्ठा hisi_sas_phy *phy,
				क्रमागत hisi_sas_phy_event event);
बाह्य व्योम hisi_sas_release_tasks(काष्ठा hisi_hba *hisi_hba);
बाह्य u8 hisi_sas_get_prog_phy_linkrate_mask(क्रमागत sas_linkrate max);
बाह्य व्योम hisi_sas_controller_reset_prepare(काष्ठा hisi_hba *hisi_hba);
बाह्य व्योम hisi_sas_controller_reset_करोne(काष्ठा hisi_hba *hisi_hba);
#पूर्ण_अगर
