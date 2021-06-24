<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * HighPoपूर्णांक RR3xxx/4xxx controller driver क्रम Linux
 * Copyright (C) 2006-2015 HighPoपूर्णांक Technologies, Inc. All Rights Reserved.
 *
 * Please report bugs/comments/suggestions to linux@highpoपूर्णांक-tech.com
 *
 * For more inक्रमmation, visit http://www.highpoपूर्णांक-tech.com
 */
#अगर_अघोषित _HPTIOP_H_
#घोषणा _HPTIOP_H_

काष्ठा hpt_iopmu_itl अणु
	__le32 resrved0[4];
	__le32 inbound_msgaddr0;
	__le32 inbound_msgaddr1;
	__le32 outbound_msgaddr0;
	__le32 outbound_msgaddr1;
	__le32 inbound_करोorbell;
	__le32 inbound_पूर्णांकstatus;
	__le32 inbound_पूर्णांकmask;
	__le32 outbound_करोorbell;
	__le32 outbound_पूर्णांकstatus;
	__le32 outbound_पूर्णांकmask;
	__le32 reserved1[2];
	__le32 inbound_queue;
	__le32 outbound_queue;
पूर्ण;

#घोषणा IOPMU_QUEUE_EMPTY            0xffffffff
#घोषणा IOPMU_QUEUE_MASK_HOST_BITS   0xf0000000
#घोषणा IOPMU_QUEUE_ADDR_HOST_BIT    0x80000000
#घोषणा IOPMU_QUEUE_REQUEST_SIZE_BIT    0x40000000
#घोषणा IOPMU_QUEUE_REQUEST_RESULT_BIT   0x40000000

#घोषणा IOPMU_OUTBOUND_INT_MSG0      1
#घोषणा IOPMU_OUTBOUND_INT_MSG1      2
#घोषणा IOPMU_OUTBOUND_INT_DOORBELL  4
#घोषणा IOPMU_OUTBOUND_INT_POSTQUEUE 8
#घोषणा IOPMU_OUTBOUND_INT_PCI       0x10

#घोषणा IOPMU_INBOUND_INT_MSG0       1
#घोषणा IOPMU_INBOUND_INT_MSG1       2
#घोषणा IOPMU_INBOUND_INT_DOORBELL   4
#घोषणा IOPMU_INBOUND_INT_ERROR      8
#घोषणा IOPMU_INBOUND_INT_POSTQUEUE  0x10

#घोषणा MVIOP_QUEUE_LEN  512

काष्ठा hpt_iopmu_mv अणु
	__le32 inbound_head;
	__le32 inbound_tail;
	__le32 outbound_head;
	__le32 outbound_tail;
	__le32 inbound_msg;
	__le32 outbound_msg;
	__le32 reserve[10];
	__le64 inbound_q[MVIOP_QUEUE_LEN];
	__le64 outbound_q[MVIOP_QUEUE_LEN];
पूर्ण;

काष्ठा hpt_iopmv_regs अणु
	__le32 reserved[0x20400 / 4];
	__le32 inbound_करोorbell;
	__le32 inbound_पूर्णांकmask;
	__le32 outbound_करोorbell;
	__le32 outbound_पूर्णांकmask;
पूर्ण;

#आशय pack(1)
काष्ठा hpt_iopmu_mvfrey अणु
	__le32 reserved0[(0x4000 - 0) / 4];
	__le32 inbound_base;
	__le32 inbound_base_high;
	__le32 reserved1[(0x4018 - 0x4008) / 4];
	__le32 inbound_ग_लिखो_ptr;
	__le32 reserved2[(0x402c - 0x401c) / 4];
	__le32 inbound_conf_ctl;
	__le32 reserved3[(0x4050 - 0x4030) / 4];
	__le32 outbound_base;
	__le32 outbound_base_high;
	__le32 outbound_shaकरोw_base;
	__le32 outbound_shaकरोw_base_high;
	__le32 reserved4[(0x4088 - 0x4060) / 4];
	__le32 isr_cause;
	__le32 isr_enable;
	__le32 reserved5[(0x1020c - 0x4090) / 4];
	__le32 pcie_f0_पूर्णांक_enable;
	__le32 reserved6[(0x10400 - 0x10210) / 4];
	__le32 f0_to_cpu_msg_a;
	__le32 reserved7[(0x10420 - 0x10404) / 4];
	__le32 cpu_to_f0_msg_a;
	__le32 reserved8[(0x10480 - 0x10424) / 4];
	__le32 f0_करोorbell;
	__le32 f0_करोorbell_enable;
पूर्ण;

काष्ठा mvfrey_inlist_entry अणु
	dma_addr_t addr;
	__le32 पूर्णांकrfc_len;
	__le32 reserved;
पूर्ण;

काष्ठा mvfrey_outlist_entry अणु
	__le32 val;
पूर्ण;
#आशय pack()

#घोषणा MVIOP_MU_QUEUE_ADDR_HOST_MASK   (~(0x1full))
#घोषणा MVIOP_MU_QUEUE_ADDR_HOST_BIT    4

#घोषणा MVIOP_MU_QUEUE_ADDR_IOP_HIGH32  0xffffffff
#घोषणा MVIOP_MU_QUEUE_REQUEST_RESULT_BIT   1
#घोषणा MVIOP_MU_QUEUE_REQUEST_RETURN_CONTEXT 2

#घोषणा MVIOP_MU_INBOUND_INT_MSG        1
#घोषणा MVIOP_MU_INBOUND_INT_POSTQUEUE  2
#घोषणा MVIOP_MU_OUTBOUND_INT_MSG       1
#घोषणा MVIOP_MU_OUTBOUND_INT_POSTQUEUE 2

#घोषणा CL_POINTER_TOGGLE        0x00004000
#घोषणा CPU_TO_F0_DRBL_MSG_BIT   0x02000000

क्रमागत hpt_iopmu_message अणु
	/* host-to-iop messages */
	IOPMU_INBOUND_MSG0_NOP = 0,
	IOPMU_INBOUND_MSG0_RESET,
	IOPMU_INBOUND_MSG0_FLUSH,
	IOPMU_INBOUND_MSG0_SHUTDOWN,
	IOPMU_INBOUND_MSG0_STOP_BACKGROUND_TASK,
	IOPMU_INBOUND_MSG0_START_BACKGROUND_TASK,
	IOPMU_INBOUND_MSG0_RESET_COMM,
	IOPMU_INBOUND_MSG0_MAX = 0xff,
	/* iop-to-host messages */
	IOPMU_OUTBOUND_MSG0_REGISTER_DEVICE_0 = 0x100,
	IOPMU_OUTBOUND_MSG0_REGISTER_DEVICE_MAX = 0x1ff,
	IOPMU_OUTBOUND_MSG0_UNREGISTER_DEVICE_0 = 0x200,
	IOPMU_OUTBOUND_MSG0_UNREGISTER_DEVICE_MAX = 0x2ff,
	IOPMU_OUTBOUND_MSG0_REVALIDATE_DEVICE_0 = 0x300,
	IOPMU_OUTBOUND_MSG0_REVALIDATE_DEVICE_MAX = 0x3ff,
पूर्ण;

काष्ठा hpt_iop_request_header अणु
	__le32 size;
	__le32 type;
	__le32 flags;
	__le32 result;
	__le32 context; /* host context */
	__le32 context_hi32;
पूर्ण;

#घोषणा IOP_REQUEST_FLAG_SYNC_REQUEST 1
#घोषणा IOP_REQUEST_FLAG_BIST_REQUEST 2
#घोषणा IOP_REQUEST_FLAG_REMAPPED     4
#घोषणा IOP_REQUEST_FLAG_OUTPUT_CONTEXT 8
#घोषणा IOP_REQUEST_FLAG_ADDR_BITS 0x40 /* flags[31:16] is phy_addr[47:32] */

क्रमागत hpt_iop_request_type अणु
	IOP_REQUEST_TYPE_GET_CONFIG = 0,
	IOP_REQUEST_TYPE_SET_CONFIG,
	IOP_REQUEST_TYPE_BLOCK_COMMAND,
	IOP_REQUEST_TYPE_SCSI_COMMAND,
	IOP_REQUEST_TYPE_IOCTL_COMMAND,
	IOP_REQUEST_TYPE_MAX
पूर्ण;

क्रमागत hpt_iop_result_type अणु
	IOP_RESULT_PENDING = 0,
	IOP_RESULT_SUCCESS,
	IOP_RESULT_FAIL,
	IOP_RESULT_BUSY,
	IOP_RESULT_RESET,
	IOP_RESULT_INVALID_REQUEST,
	IOP_RESULT_BAD_TARGET,
	IOP_RESULT_CHECK_CONDITION,
पूर्ण;

काष्ठा hpt_iop_request_get_config अणु
	काष्ठा hpt_iop_request_header header;
	__le32 पूर्णांकerface_version;
	__le32 firmware_version;
	__le32 max_requests;
	__le32 request_size;
	__le32 max_sg_count;
	__le32 data_transfer_length;
	__le32 alignment_mask;
	__le32 max_devices;
	__le32 sdram_size;
पूर्ण;

काष्ठा hpt_iop_request_set_config अणु
	काष्ठा hpt_iop_request_header header;
	__le32 iop_id;
	__le16 vbus_id;
	__le16 max_host_request_size;
	__le32 reserve[6];
पूर्ण;

काष्ठा hpt_iopsg अणु
	__le32 size;
	__le32 eot; /* non-zero: end of table */
	__le64 pci_address;
पूर्ण;

काष्ठा hpt_iop_request_block_command अणु
	काष्ठा hpt_iop_request_header header;
	u8     channel;
	u8     target;
	u8     lun;
	u8     pad1;
	__le16 command; /* IOP_BLOCK_COMMAND_अणुREAD,WRITEपूर्ण */
	__le16 sectors;
	__le64 lba;
	काष्ठा hpt_iopsg sg_list[1];
पूर्ण;

#घोषणा IOP_BLOCK_COMMAND_READ     1
#घोषणा IOP_BLOCK_COMMAND_WRITE    2
#घोषणा IOP_BLOCK_COMMAND_VERIFY   3
#घोषणा IOP_BLOCK_COMMAND_FLUSH    4
#घोषणा IOP_BLOCK_COMMAND_SHUTDOWN 5

काष्ठा hpt_iop_request_scsi_command अणु
	काष्ठा hpt_iop_request_header header;
	u8     channel;
	u8     target;
	u8     lun;
	u8     pad1;
	u8     cdb[16];
	__le32 dataxfer_length;
	काष्ठा hpt_iopsg sg_list[1];
पूर्ण;

काष्ठा hpt_iop_request_ioctl_command अणु
	काष्ठा hpt_iop_request_header header;
	__le32 ioctl_code;
	__le32 inbuf_size;
	__le32 outbuf_size;
	__le32 bytes_वापसed;
	u8     buf[1];
	/* out data should be put at buf[(inbuf_size+3)&~3] */
पूर्ण;

#घोषणा HPTIOP_MAX_REQUESTS  256u

काष्ठा hptiop_request अणु
	काष्ठा hptiop_request *next;
	व्योम                  *req_virt;
	u32                   req_shअगरted_phy;
	काष्ठा scsi_cmnd      *scp;
	पूर्णांक                   index;
पूर्ण;

काष्ठा hpt_scsi_poपूर्णांकer अणु
	पूर्णांक mapped;
	पूर्णांक sgcnt;
	dma_addr_t dma_handle;
पूर्ण;

#घोषणा HPT_SCP(scp) ((काष्ठा hpt_scsi_poपूर्णांकer *)&(scp)->SCp)

क्रमागत hptiop_family अणु
	UNKNOWN_BASED_IOP,
	INTEL_BASED_IOP,
	MV_BASED_IOP,
	MVFREY_BASED_IOP
पूर्ण ;

काष्ठा hptiop_hba अणु
	काष्ठा hptiop_adapter_ops *ops;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा hpt_iopmu_itl __iomem *iop;
			व्योम __iomem *plx;
		पूर्ण itl;
		काष्ठा अणु
			काष्ठा hpt_iopmv_regs *regs;
			काष्ठा hpt_iopmu_mv __iomem *mu;
			व्योम *पूर्णांकernal_req;
			dma_addr_t पूर्णांकernal_req_phy;
		पूर्ण mv;
		काष्ठा अणु
			काष्ठा hpt_iop_request_get_config __iomem *config;
			काष्ठा hpt_iopmu_mvfrey __iomem *mu;

			पूर्णांक पूर्णांकernal_mem_size;
			काष्ठा hptiop_request पूर्णांकernal_req;
			पूर्णांक list_count;
			काष्ठा mvfrey_inlist_entry *inlist;
			dma_addr_t inlist_phy;
			__le32 inlist_wptr;
			काष्ठा mvfrey_outlist_entry *outlist;
			dma_addr_t outlist_phy;
			__le32 *outlist_cptr; /* copy poपूर्णांकer shaकरोw */
			dma_addr_t outlist_cptr_phy;
			__le32 outlist_rptr;
		पूर्ण mvfrey;
	पूर्ण u;

	काष्ठा Scsi_Host *host;
	काष्ठा pci_dev *pcidev;

	/* IOP config info */
	u32     पूर्णांकerface_version;
	u32     firmware_version;
	u32     sdram_size;
	u32     max_devices;
	u32     max_requests;
	u32     max_request_size;
	u32     max_sg_descriptors;

	u32     req_size; /* host-allocated request buffer size */

	u32     iopपूर्णांकf_v2: 1;
	u32     initialized: 1;
	u32     msg_करोne: 1;

	काष्ठा hptiop_request * req_list;
	काष्ठा hptiop_request reqs[HPTIOP_MAX_REQUESTS];

	/* used to मुक्त allocated dma area */
	व्योम        *dma_coherent[HPTIOP_MAX_REQUESTS];
	dma_addr_t  dma_coherent_handle[HPTIOP_MAX_REQUESTS];

	atomic_t    reset_count;
	atomic_t    resetting;

	रुको_queue_head_t reset_wq;
	रुको_queue_head_t ioctl_wq;
पूर्ण;

काष्ठा hpt_ioctl_k अणु
	काष्ठा hptiop_hba * hba;
	u32    ioctl_code;
	u32    inbuf_size;
	u32    outbuf_size;
	व्योम   *inbuf;
	व्योम   *outbuf;
	u32    *bytes_वापसed;
	व्योम (*करोne)(काष्ठा hpt_ioctl_k *);
	पूर्णांक    result; /* HPT_IOCTL_RESULT_ */
पूर्ण;

काष्ठा hptiop_adapter_ops अणु
	क्रमागत hptiop_family family;
	पूर्णांक  (*iop_रुको_पढ़ोy)(काष्ठा hptiop_hba *hba, u32 millisec);
	पूर्णांक  (*पूर्णांकernal_meदो_स्मृति)(काष्ठा hptiop_hba *hba);
	पूर्णांक  (*पूर्णांकernal_memमुक्त)(काष्ठा hptiop_hba *hba);
	पूर्णांक  (*map_pci_bar)(काष्ठा hptiop_hba *hba);
	व्योम (*unmap_pci_bar)(काष्ठा hptiop_hba *hba);
	व्योम (*enable_पूर्णांकr)(काष्ठा hptiop_hba *hba);
	व्योम (*disable_पूर्णांकr)(काष्ठा hptiop_hba *hba);
	पूर्णांक  (*get_config)(काष्ठा hptiop_hba *hba,
				काष्ठा hpt_iop_request_get_config *config);
	पूर्णांक  (*set_config)(काष्ठा hptiop_hba *hba,
				काष्ठा hpt_iop_request_set_config *config);
	पूर्णांक  (*iop_पूर्णांकr)(काष्ठा hptiop_hba *hba);
	व्योम (*post_msg)(काष्ठा hptiop_hba *hba, u32 msg);
	व्योम (*post_req)(काष्ठा hptiop_hba *hba, काष्ठा hptiop_request *_req);
	पूर्णांक  hw_dma_bit_mask;
	पूर्णांक  (*reset_comm)(काष्ठा hptiop_hba *hba);
	__le64  host_phy_flag;
पूर्ण;

#घोषणा HPT_IOCTL_RESULT_OK         0
#घोषणा HPT_IOCTL_RESULT_FAILED     (-1)

#अगर 0
#घोषणा dprपूर्णांकk(fmt, args...) करो अणु prपूर्णांकk(fmt, ##args); पूर्ण जबतक(0)
#अन्यथा
#घोषणा dprपूर्णांकk(fmt, args...)
#पूर्ण_अगर

#पूर्ण_अगर
