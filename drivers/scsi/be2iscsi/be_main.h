<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2017 Broadcom. All Rights Reserved.
 * The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 * Contact Inक्रमmation:
 * linux-drivers@broadcom.com
 */

#अगर_अघोषित _BEISCSI_MAIN_
#घोषणा _BEISCSI_MAIN_

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/aer.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <scsi/libiscsi.h>
#समावेश <scsi/scsi_transport_iscsi.h>

#घोषणा DRV_NAME		"be2iscsi"
#घोषणा BUILD_STR		"11.4.0.1"
#घोषणा BE_NAME			"Emulex OneConnect" \
				"Open-iSCSI Driver version" BUILD_STR
#घोषणा DRV_DESC		BE_NAME " " "Driver"

#घोषणा BE_VENDOR_ID		0x19A2
#घोषणा ELX_VENDOR_ID		0x10DF
/* DEVICE ID's क्रम BE2 */
#घोषणा BE_DEVICE_ID1		0x212
#घोषणा OC_DEVICE_ID1		0x702
#घोषणा OC_DEVICE_ID2		0x703

/* DEVICE ID's क्रम BE3 */
#घोषणा BE_DEVICE_ID2		0x222
#घोषणा OC_DEVICE_ID3		0x712

/* DEVICE ID क्रम SKH */
#घोषणा OC_SKH_ID1		0x722

#घोषणा BE2_IO_DEPTH		1024
#घोषणा BE2_MAX_SESSIONS	256
#घोषणा BE2_TMFS		16
#घोषणा BE2_NOPOUT_REQ		16
#घोषणा BE2_SGE			32
#घोषणा BE2_DEFPDU_HDR_SZ	64
#घोषणा BE2_DEFPDU_DATA_SZ	8192
#घोषणा BE2_MAX_NUM_CQ_PROC	512

#घोषणा MAX_CPUS		64U
#घोषणा BEISCSI_MAX_NUM_CPUS	7

#घोषणा BEISCSI_VER_STRLEN 32

#घोषणा BEISCSI_SGLIST_ELEMENTS	30

/**
 * BE_INVLDT_CMD_TBL_SZ is 128 which is total number commands that can
 * be invalidated at a समय, consider it beक्रमe changing the value of
 * BEISCSI_CMD_PER_LUN.
 */
#घोषणा BEISCSI_CMD_PER_LUN	128	/* scsi_host->cmd_per_lun */
#घोषणा BEISCSI_MAX_SECTORS	1024	/* scsi_host->max_sectors */
#घोषणा BEISCSI_TEMPLATE_HDR_PER_CXN_SIZE 128 /* Template size per cxn */

#घोषणा BEISCSI_MAX_CMD_LEN	16	/* scsi_host->max_cmd_len */
#घोषणा BEISCSI_NUM_MAX_LUN	256	/* scsi_host->max_lun */
#घोषणा BEISCSI_MAX_FRAGS_INIT	192

#घोषणा BE_SENSE_INFO_SIZE		258
#घोषणा BE_ISCSI_PDU_HEADER_SIZE	64
#घोषणा BE_MIN_MEM_SIZE			16384
#घोषणा MAX_CMD_SZ			65536
#घोषणा IIOC_SCSI_DATA                  0x05	/* Write Operation */

/**
 * hardware needs the async PDU buffers to be posted in multiples of 8
 * So have atleast 8 of them by शेष
 */

#घोषणा HWI_GET_ASYNC_PDU_CTX(phwi, ulp_num)	\
	(phwi->phwi_ctxt->pasync_ctx[ulp_num])

/********* Memory BAR रेजिस्टर ************/
#घोषणा PCICFG_MEMBAR_CTRL_INT_CTRL_OFFSET	0xfc
/**
 * Host Interrupt Enable, अगर set पूर्णांकerrupts are enabled although "PCI Interrupt
 * Disable" may still globally block पूर्णांकerrupts in addition to inभागidual
 * पूर्णांकerrupt masks; a mechanism क्रम the device driver to block all पूर्णांकerrupts
 * atomically without having to arbitrate क्रम the PCI Interrupt Disable bit
 * with the OS.
 */
#घोषणा MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK	(1 << 29)	/* bit 29 */

/********* ISR0 Register offset **********/
#घोषणा CEV_ISR0_OFFSET				0xC18
#घोषणा CEV_ISR_SIZE				4

/**
 * Macros क्रम पढ़ोing/writing a protection करोमुख्य or CSR रेजिस्टरs
 * in BladeEngine.
 */

#घोषणा DB_TXULP0_OFFSET 0x40
#घोषणा DB_RXULP0_OFFSET 0xA0
/********* Event Q करोor bell *************/
#घोषणा DB_EQ_OFFSET			DB_CQ_OFFSET
#घोषणा DB_EQ_RING_ID_LOW_MASK		0x1FF	/* bits 0 - 8 */
/* Clear the पूर्णांकerrupt क्रम this eq */
#घोषणा DB_EQ_CLR_SHIFT			(9)	/* bit 9 */
/* Must be 1 */
#घोषणा DB_EQ_EVNT_SHIFT		(10)	/* bit 10 */
/* Higher Order EQ_ID bit */
#घोषणा DB_EQ_RING_ID_HIGH_MASK	0x1F /* bits 11 - 15 */
#घोषणा DB_EQ_HIGH_SET_SHIFT	11
#घोषणा DB_EQ_HIGH_FEILD_SHIFT	9
/* Number of event entries processed */
#घोषणा DB_EQ_NUM_POPPED_SHIFT		(16)	/* bits 16 - 28 */
/* Rearm bit */
#घोषणा DB_EQ_REARM_SHIFT		(29)	/* bit 29 */

/********* Compl Q करोor bell *************/
#घोषणा DB_CQ_OFFSET			0x120
#घोषणा DB_CQ_RING_ID_LOW_MASK		0x3FF	/* bits 0 - 9 */
/* Higher Order CQ_ID bit */
#घोषणा DB_CQ_RING_ID_HIGH_MASK	0x1F /* bits 11 - 15 */
#घोषणा DB_CQ_HIGH_SET_SHIFT	11
#घोषणा DB_CQ_HIGH_FEILD_SHIFT	10

/* Number of event entries processed */
#घोषणा DB_CQ_NUM_POPPED_SHIFT		(16)	/* bits 16 - 28 */
/* Rearm bit */
#घोषणा DB_CQ_REARM_SHIFT		(29)	/* bit 29 */

#घोषणा GET_HWI_CONTROLLER_WS(pc)	(pc->phwi_ctrlr)
#घोषणा HWI_GET_DEF_BUFQ_ID(pc, ulp_num) (((काष्ठा hwi_controller *)\
		(GET_HWI_CONTROLLER_WS(pc)))->शेष_pdu_data[ulp_num].id)
#घोषणा HWI_GET_DEF_HDRQ_ID(pc, ulp_num) (((काष्ठा hwi_controller *)\
		(GET_HWI_CONTROLLER_WS(pc)))->शेष_pdu_hdr[ulp_num].id)

#घोषणा PAGES_REQUIRED(x) \
	((x < PAGE_SIZE) ? 1 :  ((x + PAGE_SIZE - 1) / PAGE_SIZE))

#घोषणा MEM_DESCR_OFFSET 8
#घोषणा BEISCSI_DEFQ_HDR 1
#घोषणा BEISCSI_DEFQ_DATA 0
क्रमागत be_mem_क्रमागत अणु
	HWI_MEM_ADDN_CONTEXT,
	HWI_MEM_WRB,
	HWI_MEM_WRBH,
	HWI_MEM_SGLH,
	HWI_MEM_SGE,
	HWI_MEM_TEMPLATE_HDR_ULP0,
	HWI_MEM_ASYNC_HEADER_BUF_ULP0,	/* 6 */
	HWI_MEM_ASYNC_DATA_BUF_ULP0,
	HWI_MEM_ASYNC_HEADER_RING_ULP0,
	HWI_MEM_ASYNC_DATA_RING_ULP0,
	HWI_MEM_ASYNC_HEADER_HANDLE_ULP0,
	HWI_MEM_ASYNC_DATA_HANDLE_ULP0,	/* 11 */
	HWI_MEM_ASYNC_PDU_CONTEXT_ULP0,
	HWI_MEM_TEMPLATE_HDR_ULP1,
	HWI_MEM_ASYNC_HEADER_BUF_ULP1,	/* 14 */
	HWI_MEM_ASYNC_DATA_BUF_ULP1,
	HWI_MEM_ASYNC_HEADER_RING_ULP1,
	HWI_MEM_ASYNC_DATA_RING_ULP1,
	HWI_MEM_ASYNC_HEADER_HANDLE_ULP1,
	HWI_MEM_ASYNC_DATA_HANDLE_ULP1,	/* 19 */
	HWI_MEM_ASYNC_PDU_CONTEXT_ULP1,
	ISCSI_MEM_GLOBAL_HEADER,
	SE_MEM_MAX
पूर्ण;

काष्ठा be_bus_address32 अणु
	अचिन्हित पूर्णांक address_lo;
	अचिन्हित पूर्णांक address_hi;
पूर्ण;

काष्ठा be_bus_address64 अणु
	अचिन्हित दीर्घ दीर्घ address;
पूर्ण;

काष्ठा be_bus_address अणु
	जोड़ अणु
		काष्ठा be_bus_address32 a32;
		काष्ठा be_bus_address64 a64;
	पूर्ण u;
पूर्ण;

काष्ठा mem_array अणु
	काष्ठा be_bus_address bus_address;	/* Bus address of location */
	व्योम *भव_address;		/* भव address to the location */
	अचिन्हित पूर्णांक size;		/* Size required by memory block */
पूर्ण;

काष्ठा be_mem_descriptor अणु
	अचिन्हित पूर्णांक size_in_bytes;	/* Size required by memory block */
	अचिन्हित पूर्णांक num_elements;
	काष्ठा mem_array *mem_array;
पूर्ण;

काष्ठा sgl_handle अणु
	अचिन्हित पूर्णांक sgl_index;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक cid;
	काष्ठा iscsi_task *task;
	काष्ठा iscsi_sge *pfrag;
पूर्ण;

काष्ठा hba_parameters अणु
	अचिन्हित पूर्णांक ios_per_ctrl;
	अचिन्हित पूर्णांक cxns_per_ctrl;
	अचिन्हित पूर्णांक icds_per_ctrl;
	अचिन्हित पूर्णांक num_sge_per_io;
	अचिन्हित पूर्णांक defpdu_hdr_sz;
	अचिन्हित पूर्णांक defpdu_data_sz;
	अचिन्हित पूर्णांक num_cq_entries;
	अचिन्हित पूर्णांक num_eq_entries;
	अचिन्हित पूर्णांक wrbs_per_cxn;
	अचिन्हित पूर्णांक hwi_ws_sz;
पूर्ण;

#घोषणा BEISCSI_GET_ULP_FROM_CRI(phwi_ctrlr, cri) \
	(phwi_ctrlr->wrb_context[cri].ulp_num)
काष्ठा hwi_wrb_context अणु
	spinlock_t wrb_lock;
	काष्ठा wrb_handle **pwrb_handle_base;
	काष्ठा wrb_handle **pwrb_handle_basestd;
	काष्ठा iscsi_wrb *plast_wrb;
	अचिन्हित लघु alloc_index;
	अचिन्हित लघु मुक्त_index;
	अचिन्हित लघु wrb_handles_available;
	अचिन्हित लघु cid;
	uपूर्णांक8_t ulp_num;	/* ULP to which CID binded */
	uपूर्णांक32_t करोorbell_offset;
पूर्ण;

काष्ठा ulp_cid_info अणु
	अचिन्हित लघु *cid_array;
	अचिन्हित लघु avlbl_cids;
	अचिन्हित लघु cid_alloc;
	अचिन्हित लघु cid_मुक्त;
पूर्ण;

#समावेश "be.h"
#घोषणा chip_be2(phba)      (phba->generation == BE_GEN2)
#घोषणा chip_be3_r(phba)    (phba->generation == BE_GEN3)
#घोषणा is_chip_be2_be3r(phba) (chip_be3_r(phba) || (chip_be2(phba)))

#घोषणा BEISCSI_ULP0    0
#घोषणा BEISCSI_ULP1    1
#घोषणा BEISCSI_ULP_COUNT   2
#घोषणा BEISCSI_ULP0_LOADED 0x01
#घोषणा BEISCSI_ULP1_LOADED 0x02

#घोषणा BEISCSI_ULP_AVLBL_CID(phba, ulp_num) \
	(((काष्ठा ulp_cid_info *)phba->cid_array_info[ulp_num])->avlbl_cids)
#घोषणा BEISCSI_ULP0_AVLBL_CID(phba) \
	BEISCSI_ULP_AVLBL_CID(phba, BEISCSI_ULP0)
#घोषणा BEISCSI_ULP1_AVLBL_CID(phba) \
	BEISCSI_ULP_AVLBL_CID(phba, BEISCSI_ULP1)

काष्ठा beiscsi_hba अणु
	काष्ठा hba_parameters params;
	काष्ठा hwi_controller *phwi_ctrlr;
	अचिन्हित पूर्णांक mem_req[SE_MEM_MAX];
	/* PCI BAR mapped addresses */
	u8 __iomem *csr_va;	/* CSR */
	u8 __iomem *db_va;	/* Door  Bell  */
	u8 __iomem *pci_va;	/* PCI Config */
	/* PCI representation of our HBA */
	काष्ठा pci_dev *pcidev;
	अचिन्हित पूर्णांक num_cpus;
	अचिन्हित पूर्णांक nxt_cqid;
	अक्षर *msi_name[MAX_CPUS];
	काष्ठा be_mem_descriptor *init_mem;

	अचिन्हित लघु io_sgl_alloc_index;
	अचिन्हित लघु io_sgl_मुक्त_index;
	अचिन्हित लघु io_sgl_hndl_avbl;
	काष्ठा sgl_handle **io_sgl_hndl_base;

	अचिन्हित लघु eh_sgl_alloc_index;
	अचिन्हित लघु eh_sgl_मुक्त_index;
	अचिन्हित लघु eh_sgl_hndl_avbl;
	काष्ठा sgl_handle **eh_sgl_hndl_base;
	spinlock_t io_sgl_lock;
	spinlock_t mgmt_sgl_lock;
	spinlock_t async_pdu_lock;
	काष्ठा list_head hba_queue;
#घोषणा BE_MAX_SESSION 2048
#घोषणा BE_INVALID_CID 0xffff
#घोषणा BE_SET_CID_TO_CRI(cri_index, cid) \
			  (phba->cid_to_cri_map[cid] = cri_index)
#घोषणा BE_GET_CRI_FROM_CID(cid) (phba->cid_to_cri_map[cid])
	अचिन्हित लघु cid_to_cri_map[BE_MAX_SESSION];
	काष्ठा ulp_cid_info *cid_array_info[BEISCSI_ULP_COUNT];
	काष्ठा iscsi_endpoपूर्णांक **ep_array;
	काष्ठा beiscsi_conn **conn_table;
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_अगरace *ipv4_अगरace;
	काष्ठा iscsi_अगरace *ipv6_अगरace;
	काष्ठा अणु
		/**
		 * group together since they are used most frequently
		 * क्रम cid to cri conversion
		 */
#घोषणा BEISCSI_PHYS_PORT_MAX	4
		अचिन्हित पूर्णांक phys_port;
		/* valid values of phys_port id are 0, 1, 2, 3 */
		अचिन्हित पूर्णांक eqid_count;
		अचिन्हित पूर्णांक cqid_count;
		अचिन्हित पूर्णांक iscsi_cid_start[BEISCSI_ULP_COUNT];
#घोषणा BEISCSI_GET_CID_COUNT(phba, ulp_num) \
		(phba->fw_config.iscsi_cid_count[ulp_num])
		अचिन्हित पूर्णांक iscsi_cid_count[BEISCSI_ULP_COUNT];
		अचिन्हित पूर्णांक iscsi_icd_count[BEISCSI_ULP_COUNT];
		अचिन्हित पूर्णांक iscsi_icd_start[BEISCSI_ULP_COUNT];
		अचिन्हित पूर्णांक iscsi_chain_start[BEISCSI_ULP_COUNT];
		अचिन्हित पूर्णांक iscsi_chain_count[BEISCSI_ULP_COUNT];

		अचिन्हित लघु iscsi_features;
		uपूर्णांक16_t dual_ulp_aware;
		अचिन्हित दीर्घ ulp_supported;
	पूर्ण fw_config;

	अचिन्हित दीर्घ state;
#घोषणा BEISCSI_HBA_ONLINE	0
#घोषणा BEISCSI_HBA_LINK_UP	1
#घोषणा BEISCSI_HBA_BOOT_FOUND	2
#घोषणा BEISCSI_HBA_BOOT_WORK	3
#घोषणा BEISCSI_HBA_UER_SUPP	4
#घोषणा BEISCSI_HBA_PCI_ERR	5
#घोषणा BEISCSI_HBA_FW_TIMEOUT	6
#घोषणा BEISCSI_HBA_IN_UE	7
#घोषणा BEISCSI_HBA_IN_TPE	8

/* error bits */
#घोषणा BEISCSI_HBA_IN_ERR	((1 << BEISCSI_HBA_PCI_ERR) | \
				 (1 << BEISCSI_HBA_FW_TIMEOUT) | \
				 (1 << BEISCSI_HBA_IN_UE) | \
				 (1 << BEISCSI_HBA_IN_TPE))

	u8 optic_state;
	काष्ठा delayed_work eqd_update;
	/* update EQ delay समयr every 1000ms */
#घोषणा BEISCSI_EQD_UPDATE_INTERVAL	1000
	काष्ठा समयr_list hw_check;
	/* check क्रम UE every 1000ms */
#घोषणा BEISCSI_UE_DETECT_INTERVAL	1000
	u32 ue2rp;
	काष्ठा delayed_work recover_port;
	काष्ठा work_काष्ठा sess_work;

	bool mac_addr_set;
	u8 mac_address[ETH_ALEN];
	u8 port_name;
	u8 port_speed;
	अक्षर fw_ver_str[BEISCSI_VER_STRLEN];
	काष्ठा workqueue_काष्ठा *wq;	/* The actuak work queue */
	काष्ठा be_ctrl_info ctrl;
	अचिन्हित पूर्णांक generation;
	अचिन्हित पूर्णांक पूर्णांकerface_handle;

	काष्ठा be_aic_obj aic_obj[MAX_CPUS];
	अचिन्हित पूर्णांक attr_log_enable;
	पूर्णांक (*iotask_fn)(काष्ठा iscsi_task *,
			काष्ठा scatterlist *sg,
			uपूर्णांक32_t num_sg, uपूर्णांक32_t xferlen,
			uपूर्णांक32_t ग_लिखोdir);
	काष्ठा boot_काष्ठा अणु
		पूर्णांक retry;
		अचिन्हित पूर्णांक tag;
		अचिन्हित पूर्णांक s_handle;
		काष्ठा be_dma_mem nonemb_cmd;
		क्रमागत अणु
			BEISCSI_BOOT_REOPEN_SESS = 1,
			BEISCSI_BOOT_GET_SHANDLE,
			BEISCSI_BOOT_GET_SINFO,
			BEISCSI_BOOT_LOGOUT_SESS,
			BEISCSI_BOOT_CREATE_KSET,
		पूर्ण action;
		काष्ठा mgmt_session_info boot_sess;
		काष्ठा iscsi_boot_kset *boot_kset;
	पूर्ण boot_काष्ठा;
	काष्ठा work_काष्ठा boot_work;
पूर्ण;

#घोषणा beiscsi_hba_in_error(phba) ((phba)->state & BEISCSI_HBA_IN_ERR)
#घोषणा beiscsi_hba_is_online(phba) \
	(!beiscsi_hba_in_error((phba)) && \
	 test_bit(BEISCSI_HBA_ONLINE, &phba->state))

काष्ठा beiscsi_session अणु
	काष्ठा dma_pool *bhs_pool;
पूर्ण;

/**
 * काष्ठा beiscsi_conn - iscsi connection काष्ठाure
 */
काष्ठा beiscsi_conn अणु
	काष्ठा iscsi_conn *conn;
	काष्ठा beiscsi_hba *phba;
	u32 exp_statsn;
	u32 करोorbell_offset;
	u32 beiscsi_conn_cid;
	काष्ठा beiscsi_endpoपूर्णांक *ep;
	अचिन्हित लघु login_in_progress;
	काष्ठा wrb_handle *plogin_wrb_handle;
	काष्ठा sgl_handle *plogin_sgl_handle;
	काष्ठा beiscsi_session *beiscsi_sess;
	काष्ठा iscsi_task *task;
पूर्ण;

/* This काष्ठाure is used by the chip */
काष्ठा pdu_data_out अणु
	u32 dw[12];
पूर्ण;
/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_pdu_data_out अणु
	u8 opcode[6];		/* opcode */
	u8 rsvd0[2];		/* should be 0 */
	u8 rsvd1[7];
	u8 final_bit;		/* F bit */
	u8 rsvd2[16];
	u8 ahs_length[8];	/* no AHS */
	u8 data_len_hi[8];
	u8 data_len_lo[16];	/* DataSegmentLength */
	u8 lun[64];
	u8 itt[32];		/* ITT; initiator task tag */
	u8 ttt[32];		/* TTT; valid क्रम R2T or 0xffffffff */
	u8 rsvd3[32];
	u8 exp_stat_sn[32];
	u8 rsvd4[32];
	u8 data_sn[32];
	u8 buffer_offset[32];
	u8 rsvd5[32];
पूर्ण;

काष्ठा be_cmd_bhs अणु
	काष्ठा iscsi_scsi_req iscsi_hdr;
	अचिन्हित अक्षर pad1[16];
	काष्ठा pdu_data_out iscsi_data_pdu;
	अचिन्हित अक्षर pad2[BE_SENSE_INFO_SIZE -
			माप(काष्ठा pdu_data_out)];
पूर्ण;

काष्ठा beiscsi_io_task अणु
	काष्ठा wrb_handle *pwrb_handle;
	काष्ठा sgl_handle *psgl_handle;
	काष्ठा beiscsi_conn *conn;
	काष्ठा scsi_cmnd *scsi_cmnd;
	पूर्णांक num_sg;
	काष्ठा hwi_wrb_context *pwrb_context;
	itt_t libiscsi_itt;
	काष्ठा be_cmd_bhs *cmd_bhs;
	काष्ठा be_bus_address bhs_pa;
	अचिन्हित लघु bhs_len;
	dma_addr_t mtask_addr;
	uपूर्णांक32_t mtask_data_count;
	uपूर्णांक8_t wrb_type;
पूर्ण;

काष्ठा be_nonio_bhs अणु
	काष्ठा iscsi_hdr iscsi_hdr;
	अचिन्हित अक्षर pad1[16];
	काष्ठा pdu_data_out iscsi_data_pdu;
	अचिन्हित अक्षर pad2[BE_SENSE_INFO_SIZE -
			माप(काष्ठा pdu_data_out)];
पूर्ण;

काष्ठा be_status_bhs अणु
	काष्ठा iscsi_scsi_req iscsi_hdr;
	अचिन्हित अक्षर pad1[16];
	/**
	 * The plus 2 below is to hold the sense info length that माला_लो
	 * DMA'ed by RxULP
	 */
	अचिन्हित अक्षर sense_info[BE_SENSE_INFO_SIZE];
पूर्ण;

काष्ठा iscsi_sge अणु
	u32 dw[4];
पूर्ण;

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_iscsi_sge अणु
	u8 addr_hi[32];
	u8 addr_lo[32];
	u8 sge_offset[22];	/* DWORD 2 */
	u8 rsvd0[9];		/* DWORD 2 */
	u8 last_sge;		/* DWORD 2 */
	u8 len[17];		/* DWORD 3 */
	u8 rsvd1[15];		/* DWORD 3 */
पूर्ण;

काष्ठा beiscsi_offload_params अणु
	u32 dw[6];
पूर्ण;

#घोषणा OFFLD_PARAMS_ERL	0x00000003
#घोषणा OFFLD_PARAMS_DDE	0x00000004
#घोषणा OFFLD_PARAMS_HDE	0x00000008
#घोषणा OFFLD_PARAMS_IR2T	0x00000010
#घोषणा OFFLD_PARAMS_IMD	0x00000020
#घोषणा OFFLD_PARAMS_DATA_SEQ_INORDER   0x00000040
#घोषणा OFFLD_PARAMS_PDU_SEQ_INORDER    0x00000080
#घोषणा OFFLD_PARAMS_MAX_R2T 0x00FFFF00

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_beiscsi_offload_params अणु
	u8 max_burst_length[32];
	u8 max_send_data_segment_length[32];
	u8 first_burst_length[32];
	u8 erl[2];
	u8 dde[1];
	u8 hde[1];
	u8 ir2t[1];
	u8 imd[1];
	u8 data_seq_inorder[1];
	u8 pdu_seq_inorder[1];
	u8 max_r2t[16];
	u8 pad[8];
	u8 exp_statsn[32];
	u8 max_recv_data_segment_length[32];
पूर्ण;

काष्ठा hd_async_handle अणु
	काष्ठा list_head link;
	काष्ठा be_bus_address pa;
	व्योम *pbuffer;
	u32 buffer_len;
	u16 index;
	u16 cri;
	u8 is_header;
	u8 is_final;
	u8 in_use;
पूर्ण;

#घोषणा BEISCSI_ASYNC_HDQ_SIZE(phba, ulp) \
	(BEISCSI_GET_CID_COUNT((phba), (ulp)) * 2)

/**
 * This has list of async PDUs that are रुकोing to be processed.
 * Buffers live in this list क्रम a brief duration beक्रमe they get
 * processed and posted back to hardware.
 * Note that we करोn't really need one cri_रुको_queue per async_entry.
 * We need one cri_रुको_queue per CRI. Its easier to manage अगर this
 * is tagged aदीर्घ with the async_entry.
 */
काष्ठा hd_async_entry अणु
	काष्ठा cri_रुको_queue अणु
		अचिन्हित लघु hdr_len;
		अचिन्हित पूर्णांक bytes_received;
		अचिन्हित पूर्णांक bytes_needed;
		काष्ठा list_head list;
	पूर्ण wq;
	/* handles posted to FW resides here */
	काष्ठा hd_async_handle *header;
	काष्ठा hd_async_handle *data;
पूर्ण;

काष्ठा hd_async_buf_context अणु
	काष्ठा be_bus_address pa_base;
	व्योम *va_base;
	व्योम *ring_base;
	काष्ठा hd_async_handle *handle_base;
	u32 buffer_size;
	u16 pi;
पूर्ण;

/**
 * hd_async_context is declared क्रम each ULP supporting iSCSI function.
 */
काष्ठा hd_async_context अणु
	काष्ठा hd_async_buf_context async_header;
	काष्ठा hd_async_buf_context async_data;
	u16 num_entries;
	/**
	 * When unsol PDU is in, it needs to be chained till all the bytes are
	 * received and then processing is करोne. hd_async_entry is created
	 * based on the cid_count क्रम each ULP. When unsol PDU comes in based
	 * on the conn_id it needs to be added to the correct async_entry wq.
	 * Below defined cid_to_async_cri_map is used to reterive the
	 * async_cri_map क्रम a particular connection.
	 *
	 * This array is initialized after beiscsi_create_wrb_rings वापसs.
	 *
	 * - this method takes more memory space, fixed to 2K
	 * - any support क्रम connections greater than this the array size needs
	 * to be incremented
	 */
#घोषणा BE_GET_ASYNC_CRI_FROM_CID(cid) (pasync_ctx->cid_to_async_cri_map[cid])
	अचिन्हित लघु cid_to_async_cri_map[BE_MAX_SESSION];
	/**
	 * This is a variable size array. Don`t add anything after this field!!
	 */
	काष्ठा hd_async_entry *async_entry;
पूर्ण;

काष्ठा i_t_dpdu_cqe अणु
	u32 dw[4];
पूर्ण __packed;

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_i_t_dpdu_cqe अणु
	u8 db_addr_hi[32];
	u8 db_addr_lo[32];
	u8 code[6];
	u8 cid[10];
	u8 dpl[16];
	u8 index[16];
	u8 num_cons[10];
	u8 rsvd0[4];
	u8 final;
	u8 valid;
पूर्ण __packed;

काष्ठा amap_i_t_dpdu_cqe_v2 अणु
	u8 db_addr_hi[32];  /* DWORD 0 */
	u8 db_addr_lo[32];  /* DWORD 1 */
	u8 code[6]; /* DWORD 2 */
	u8 num_cons; /* DWORD 2*/
	u8 rsvd0[8]; /* DWORD 2 */
	u8 dpl[17]; /* DWORD 2 */
	u8 index[16]; /* DWORD 3 */
	u8 cid[13]; /* DWORD 3 */
	u8 rsvd1; /* DWORD 3 */
	u8 final; /* DWORD 3 */
	u8 valid; /* DWORD 3 */
पूर्ण __packed;

#घोषणा CQE_VALID_MASK	0x80000000
#घोषणा CQE_CODE_MASK	0x0000003F
#घोषणा CQE_CID_MASK	0x0000FFC0

#घोषणा EQE_VALID_MASK		0x00000001
#घोषणा EQE_MAJORCODE_MASK	0x0000000E
#घोषणा EQE_RESID_MASK		0xFFFF0000

काष्ठा be_eq_entry अणु
	u32 dw[1];
पूर्ण __packed;

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_eq_entry अणु
	u8 valid;		/* DWORD 0 */
	u8 major_code[3];	/* DWORD 0 */
	u8 minor_code[12];	/* DWORD 0 */
	u8 resource_id[16];	/* DWORD 0 */

पूर्ण __packed;

काष्ठा cq_db अणु
	u32 dw[1];
पूर्ण __packed;

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_cq_db अणु
	u8 qid[10];
	u8 event[1];
	u8 rsvd0[5];
	u8 num_popped[13];
	u8 rearm[1];
	u8 rsvd1[2];
पूर्ण __packed;

व्योम beiscsi_process_eq(काष्ठा beiscsi_hba *phba);

काष्ठा iscsi_wrb अणु
	u32 dw[16];
पूर्ण __packed;

#घोषणा WRB_TYPE_MASK 0xF0000000
#घोषणा SKH_WRB_TYPE_OFFSET 27
#घोषणा BE_WRB_TYPE_OFFSET  28

#घोषणा ADAPTER_SET_WRB_TYPE(pwrb, wrb_type, type_offset) \
		(pwrb->dw[0] |= (wrb_type << type_offset))

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_iscsi_wrb अणु
	u8 lun[14];		/* DWORD 0 */
	u8 lt;			/* DWORD 0 */
	u8 invld;		/* DWORD 0 */
	u8 wrb_idx[8];		/* DWORD 0 */
	u8 dsp;			/* DWORD 0 */
	u8 dmsg;		/* DWORD 0 */
	u8 undr_run;		/* DWORD 0 */
	u8 over_run;		/* DWORD 0 */
	u8 type[4];		/* DWORD 0 */
	u8 ptr2nextwrb[8];	/* DWORD 1 */
	u8 r2t_exp_dtl[24];	/* DWORD 1 */
	u8 sgl_icd_idx[12];	/* DWORD 2 */
	u8 rsvd0[20];		/* DWORD 2 */
	u8 exp_data_sn[32];	/* DWORD 3 */
	u8 iscsi_bhs_addr_hi[32];	/* DWORD 4 */
	u8 iscsi_bhs_addr_lo[32];	/* DWORD 5 */
	u8 cmdsn_itt[32];	/* DWORD 6 */
	u8 dअगर_ref_tag[32];	/* DWORD 7 */
	u8 sge0_addr_hi[32];	/* DWORD 8 */
	u8 sge0_addr_lo[32];	/* DWORD 9  */
	u8 sge0_offset[22];	/* DWORD 10 */
	u8 pbs;			/* DWORD 10 */
	u8 dअगर_mode[2];		/* DWORD 10 */
	u8 rsvd1[6];		/* DWORD 10 */
	u8 sge0_last;		/* DWORD 10 */
	u8 sge0_len[17];	/* DWORD 11 */
	u8 dअगर_meta_tag[14];	/* DWORD 11 */
	u8 sge0_in_ddr;		/* DWORD 11 */
	u8 sge1_addr_hi[32];	/* DWORD 12 */
	u8 sge1_addr_lo[32];	/* DWORD 13 */
	u8 sge1_r2t_offset[22];	/* DWORD 14 */
	u8 rsvd2[9];		/* DWORD 14 */
	u8 sge1_last;		/* DWORD 14 */
	u8 sge1_len[17];	/* DWORD 15 */
	u8 ref_sgl_icd_idx[12];	/* DWORD 15 */
	u8 rsvd3[2];		/* DWORD 15 */
	u8 sge1_in_ddr;		/* DWORD 15 */

पूर्ण __packed;

काष्ठा amap_iscsi_wrb_v2 अणु
	u8 r2t_exp_dtl[25]; /* DWORD 0 */
	u8 rsvd0[2];    /* DWORD 0*/
	u8 type[5];     /* DWORD 0 */
	u8 ptr2nextwrb[8];  /* DWORD 1 */
	u8 wrb_idx[8];      /* DWORD 1 */
	u8 lun[16];     /* DWORD 1 */
	u8 sgl_idx[16]; /* DWORD 2 */
	u8 ref_sgl_icd_idx[16]; /* DWORD 2 */
	u8 exp_data_sn[32]; /* DWORD 3 */
	u8 iscsi_bhs_addr_hi[32];   /* DWORD 4 */
	u8 iscsi_bhs_addr_lo[32];   /* DWORD 5 */
	u8 cq_id[16];   /* DWORD 6 */
	u8 rsvd1[16];   /* DWORD 6 */
	u8 cmdsn_itt[32];   /* DWORD 7 */
	u8 sge0_addr_hi[32];    /* DWORD 8 */
	u8 sge0_addr_lo[32];    /* DWORD 9 */
	u8 sge0_offset[24]; /* DWORD 10 */
	u8 rsvd2[7];    /* DWORD 10 */
	u8 sge0_last;   /* DWORD 10 */
	u8 sge0_len[17];    /* DWORD 11 */
	u8 rsvd3[7];    /* DWORD 11 */
	u8 dअगरf_enbl;   /* DWORD 11 */
	u8 u_run;       /* DWORD 11 */
	u8 o_run;       /* DWORD 11 */
	u8 invld;     /* DWORD 11 */
	u8 dsp;         /* DWORD 11 */
	u8 dmsg;        /* DWORD 11 */
	u8 rsvd4;       /* DWORD 11 */
	u8 lt;          /* DWORD 11 */
	u8 sge1_addr_hi[32];    /* DWORD 12 */
	u8 sge1_addr_lo[32];    /* DWORD 13 */
	u8 sge1_r2t_offset[24]; /* DWORD 14 */
	u8 rsvd5[7];    /* DWORD 14 */
	u8 sge1_last;   /* DWORD 14 */
	u8 sge1_len[17];    /* DWORD 15 */
	u8 rsvd6[15];   /* DWORD 15 */
पूर्ण __packed;


काष्ठा wrb_handle *alloc_wrb_handle(काष्ठा beiscsi_hba *phba, अचिन्हित पूर्णांक cid,
				     काष्ठा hwi_wrb_context **pcontext);
व्योम
मुक्त_mgmt_sgl_handle(काष्ठा beiscsi_hba *phba, काष्ठा sgl_handle *psgl_handle);

व्योम beiscsi_मुक्त_mgmt_task_handles(काष्ठा beiscsi_conn *beiscsi_conn,
				     काष्ठा iscsi_task *task);

व्योम hwi_ring_cq_db(काष्ठा beiscsi_hba *phba,
		     अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक num_processed,
		     अचिन्हित अक्षर rearm);

अचिन्हित पूर्णांक beiscsi_process_cq(काष्ठा be_eq_obj *pbe_eq, पूर्णांक budget);
व्योम beiscsi_process_mcc_cq(काष्ठा beiscsi_hba *phba);

काष्ठा pdu_nop_out अणु
	u32 dw[12];
पूर्ण;

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_pdu_nop_out अणु
	u8 opcode[6];		/* opcode 0x00 */
	u8 i_bit;		/* I Bit */
	u8 x_bit;		/* reserved; should be 0 */
	u8 fp_bit_filler1[7];
	u8 f_bit;		/* always 1 */
	u8 reserved1[16];
	u8 ahs_length[8];	/* no AHS */
	u8 data_len_hi[8];
	u8 data_len_lo[16];	/* DataSegmentLength */
	u8 lun[64];
	u8 itt[32];		/* initiator id क्रम ping or 0xffffffff */
	u8 ttt[32];		/* target id क्रम ping or 0xffffffff */
	u8 cmd_sn[32];
	u8 exp_stat_sn[32];
	u8 reserved5[128];
पूर्ण;

#घोषणा PDUBASE_OPCODE_MASK	0x0000003F
#घोषणा PDUBASE_DATALENHI_MASK	0x0000FF00
#घोषणा PDUBASE_DATALENLO_MASK	0xFFFF0000

काष्ठा pdu_base अणु
	u32 dw[16];
पूर्ण __packed;

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_pdu_base अणु
	u8 opcode[6];
	u8 i_bit;		/* immediate bit */
	u8 x_bit;		/* reserved, always 0 */
	u8 reserved1[24];	/* opcode-specअगरic fields */
	u8 ahs_length[8];	/* length units is 4 byte words */
	u8 data_len_hi[8];
	u8 data_len_lo[16];	/* DatasegmentLength */
	u8 lun[64];		/* lun or opcode-specअगरic fields */
	u8 itt[32];		/* initiator task tag */
	u8 reserved4[224];
पूर्ण;

काष्ठा iscsi_target_context_update_wrb अणु
	u32 dw[16];
पूर्ण __packed;

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field
 */
#घोषणा BE_TGT_CTX_UPDT_CMD 0x07
काष्ठा amap_iscsi_target_context_update_wrb अणु
	u8 lun[14];		/* DWORD 0 */
	u8 lt;			/* DWORD 0 */
	u8 invld;		/* DWORD 0 */
	u8 wrb_idx[8];		/* DWORD 0 */
	u8 dsp;			/* DWORD 0 */
	u8 dmsg;		/* DWORD 0 */
	u8 undr_run;		/* DWORD 0 */
	u8 over_run;		/* DWORD 0 */
	u8 type[4];		/* DWORD 0 */
	u8 ptr2nextwrb[8];	/* DWORD 1 */
	u8 max_burst_length[19];	/* DWORD 1 */
	u8 rsvd0[5];		/* DWORD 1 */
	u8 rsvd1[15];		/* DWORD 2 */
	u8 max_send_data_segment_length[17];	/* DWORD 2 */
	u8 first_burst_length[14];	/* DWORD 3 */
	u8 rsvd2[2];		/* DWORD 3 */
	u8 tx_wrbindex_drv_msg[8];	/* DWORD 3 */
	u8 rsvd3[5];		/* DWORD 3 */
	u8 session_state[3];	/* DWORD 3 */
	u8 rsvd4[16];		/* DWORD 4 */
	u8 tx_jumbo;		/* DWORD 4 */
	u8 hde;			/* DWORD 4 */
	u8 dde;			/* DWORD 4 */
	u8 erl[2];		/* DWORD 4 */
	u8 करोमुख्य_id[5];		/* DWORD 4 */
	u8 mode;		/* DWORD 4 */
	u8 imd;			/* DWORD 4 */
	u8 ir2t;		/* DWORD 4 */
	u8 notpredblq[2];	/* DWORD 4 */
	u8 compltonack;		/* DWORD 4 */
	u8 stat_sn[32];		/* DWORD 5 */
	u8 pad_buffer_addr_hi[32];	/* DWORD 6 */
	u8 pad_buffer_addr_lo[32];	/* DWORD 7 */
	u8 pad_addr_hi[32];	/* DWORD 8 */
	u8 pad_addr_lo[32];	/* DWORD 9 */
	u8 rsvd5[32];		/* DWORD 10 */
	u8 rsvd6[32];		/* DWORD 11 */
	u8 rsvd7[32];		/* DWORD 12 */
	u8 rsvd8[32];		/* DWORD 13 */
	u8 rsvd9[32];		/* DWORD 14 */
	u8 rsvd10[32];		/* DWORD 15 */

पूर्ण __packed;

#घोषणा BEISCSI_MAX_RECV_DATASEG_LEN    (64 * 1024)
#घोषणा BEISCSI_MAX_CXNS    1
काष्ठा amap_iscsi_target_context_update_wrb_v2 अणु
	u8 max_burst_length[24];    /* DWORD 0 */
	u8 rsvd0[3];    /* DWORD 0 */
	u8 type[5];     /* DWORD 0 */
	u8 ptr2nextwrb[8];  /* DWORD 1 */
	u8 wrb_idx[8];      /* DWORD 1 */
	u8 rsvd1[16];       /* DWORD 1 */
	u8 max_send_data_segment_length[24];    /* DWORD 2 */
	u8 rsvd2[8];    /* DWORD 2 */
	u8 first_burst_length[24]; /* DWORD 3 */
	u8 rsvd3[8]; /* DOWRD 3 */
	u8 max_r2t[16]; /* DWORD 4 */
	u8 rsvd4;       /* DWORD 4 */
	u8 hde;         /* DWORD 4 */
	u8 dde;         /* DWORD 4 */
	u8 erl[2];      /* DWORD 4 */
	u8 rsvd5[6];    /* DWORD 4 */
	u8 imd;         /* DWORD 4 */
	u8 ir2t;        /* DWORD 4 */
	u8 rsvd6[3];    /* DWORD 4 */
	u8 stat_sn[32];     /* DWORD 5 */
	u8 rsvd7[32];   /* DWORD 6 */
	u8 rsvd8[32];   /* DWORD 7 */
	u8 max_recv_dataseg_len[24];    /* DWORD 8 */
	u8 rsvd9[8]; /* DWORD 8 */
	u8 rsvd10[32];   /* DWORD 9 */
	u8 rsvd11[32];   /* DWORD 10 */
	u8 max_cxns[16]; /* DWORD 11 */
	u8 rsvd12[11]; /* DWORD  11*/
	u8 invld; /* DWORD 11 */
	u8 rsvd13;/* DWORD 11*/
	u8 dmsg; /* DWORD 11 */
	u8 data_seq_inorder; /* DWORD 11 */
	u8 pdu_seq_inorder; /* DWORD 11 */
	u8 rsvd14[32]; /*DWORD 12 */
	u8 rsvd15[32]; /* DWORD 13 */
	u8 rsvd16[32]; /* DWORD 14 */
	u8 rsvd17[32]; /* DWORD 15 */
पूर्ण __packed;


काष्ठा be_ring अणु
	u32 pages;		/* queue size in pages */
	u32 id;			/* queue id asचिन्हित by beklib */
	u32 num;		/* number of elements in queue */
	u32 cidx;		/* consumer index */
	u32 pidx;		/* producer index -- not used by most rings */
	u32 item_size;		/* size in bytes of one object */
	u8 ulp_num;	/* ULP to which CID binded */
	u16 रेजिस्टर_set;
	u16 करोorbell_क्रमmat;
	u32 करोorbell_offset;

	व्योम *va;		/* The भव address of the ring.  This
				 * should be last to allow 32 & 64 bit debugger
				 * extensions to work.
				 */
पूर्ण;

काष्ठा hwi_controller अणु
	काष्ठा hwi_wrb_context *wrb_context;
	काष्ठा be_ring शेष_pdu_hdr[BEISCSI_ULP_COUNT];
	काष्ठा be_ring शेष_pdu_data[BEISCSI_ULP_COUNT];
	काष्ठा hwi_context_memory *phwi_ctxt;
पूर्ण;

क्रमागत hwh_type_क्रमागत अणु
	HWH_TYPE_IO = 1,
	HWH_TYPE_LOGOUT = 2,
	HWH_TYPE_TMF = 3,
	HWH_TYPE_NOP = 4,
	HWH_TYPE_IO_RD = 5,
	HWH_TYPE_LOGIN = 11,
	HWH_TYPE_INVALID = 0xFFFFFFFF
पूर्ण;

काष्ठा wrb_handle अणु
	अचिन्हित लघु wrb_index;
	काष्ठा iscsi_task *pio_handle;
	काष्ठा iscsi_wrb *pwrb;
पूर्ण;

काष्ठा hwi_context_memory अणु
	काष्ठा be_eq_obj be_eq[MAX_CPUS];
	काष्ठा be_queue_info be_cq[MAX_CPUS - 1];

	काष्ठा be_queue_info *be_wrbq;
	/**
	 * Create array of ULP number क्रम below entries as DEFQ
	 * will be created क्रम both ULP अगर iSCSI Protocol is
	 * loaded on both ULP.
	 */
	काष्ठा be_queue_info be_def_hdrq[BEISCSI_ULP_COUNT];
	काष्ठा be_queue_info be_def_dataq[BEISCSI_ULP_COUNT];
	काष्ठा hd_async_context *pasync_ctx[BEISCSI_ULP_COUNT];
पूर्ण;

व्योम beiscsi_start_boot_work(काष्ठा beiscsi_hba *phba, अचिन्हित पूर्णांक s_handle);

/* Logging related definitions */
#घोषणा BEISCSI_LOG_INIT	0x0001	/* Initialization events */
#घोषणा BEISCSI_LOG_MBOX	0x0002	/* Mailbox Events */
#घोषणा BEISCSI_LOG_MISC	0x0004	/* Miscllaneous Events */
#घोषणा BEISCSI_LOG_EH		0x0008	/* Error Handler */
#घोषणा BEISCSI_LOG_IO		0x0010	/* IO Code Path */
#घोषणा BEISCSI_LOG_CONFIG	0x0020	/* CONFIG Code Path */
#घोषणा BEISCSI_LOG_ISCSI	0x0040	/* SCSI/iSCSI Protocol related Logs */

#घोषणा __beiscsi_log(phba, level, fmt, arg...) \
	shost_prपूर्णांकk(level, phba->shost, fmt, __LINE__, ##arg)

#घोषणा beiscsi_log(phba, level, mask, fmt, arg...) \
करो अणु \
	uपूर्णांक32_t log_value = phba->attr_log_enable; \
		अगर (((mask) & log_value) || (level[1] <= '3')) \
			__beiscsi_log(phba, level, fmt, ##arg); \
पूर्ण जबतक (0);

#पूर्ण_अगर
