<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
  * Marvell UMI head file
  *
  * Copyright 2011 Marvell. <jyli@marvell.com>
 */

#अगर_अघोषित MVUMI_H
#घोषणा MVUMI_H

#घोषणा MAX_BASE_ADDRESS	6

#घोषणा VER_MAJOR		1
#घोषणा VER_MINOR		1
#घोषणा VER_OEM			0
#घोषणा VER_BUILD		1500

#घोषणा MV_DRIVER_NAME			"mvumi"
#घोषणा PCI_DEVICE_ID_MARVELL_MV9143	0x9143
#घोषणा PCI_DEVICE_ID_MARVELL_MV9580	0x9580

#घोषणा MVUMI_INTERNAL_CMD_WAIT_TIME	45
#घोषणा MVUMI_INQUIRY_LENGTH		44
#घोषणा MVUMI_INQUIRY_UUID_OFF		36
#घोषणा MVUMI_INQUIRY_UUID_LEN		8

#घोषणा IS_DMA64			(माप(dma_addr_t) == 8)

क्रमागत mvumi_qc_result अणु
	MV_QUEUE_COMMAND_RESULT_SENT = 0,
	MV_QUEUE_COMMAND_RESULT_NO_RESOURCE,
पूर्ण;

काष्ठा mvumi_hw_regs अणु
	/* For CPU */
	व्योम *मुख्य_पूर्णांक_cause_reg;
	व्योम *enpoपूर्णांकa_mask_reg;
	व्योम *enpoपूर्णांकb_mask_reg;
	व्योम *rstoutn_en_reg;
	व्योम *ctrl_sts_reg;
	व्योम *rstoutn_mask_reg;
	व्योम *sys_soft_rst_reg;

	/* For Doorbell */
	व्योम *pciea_to_arm_drbl_reg;
	व्योम *arm_to_pciea_drbl_reg;
	व्योम *arm_to_pciea_mask_reg;
	व्योम *pciea_to_arm_msg0;
	व्योम *pciea_to_arm_msg1;
	व्योम *arm_to_pciea_msg0;
	व्योम *arm_to_pciea_msg1;

	/* reset रेजिस्टर */
	व्योम *reset_request;
	व्योम *reset_enable;

	/* For Message Unit */
	व्योम *inb_list_basel;
	व्योम *inb_list_baseh;
	व्योम *inb_aval_count_basel;
	व्योम *inb_aval_count_baseh;
	व्योम *inb_ग_लिखो_poपूर्णांकer;
	व्योम *inb_पढ़ो_poपूर्णांकer;
	व्योम *outb_list_basel;
	व्योम *outb_list_baseh;
	व्योम *outb_copy_basel;
	व्योम *outb_copy_baseh;
	व्योम *outb_copy_poपूर्णांकer;
	व्योम *outb_पढ़ो_poपूर्णांकer;
	व्योम *inb_isr_cause;
	व्योम *outb_isr_cause;
	व्योम *outb_coal_cfg;
	व्योम *outb_coal_समयout;

	/* Bit setting क्रम HW */
	u32 पूर्णांक_comaout;
	u32 पूर्णांक_comaerr;
	u32 पूर्णांक_dl_cpu2pciea;
	u32 पूर्णांक_mu;
	u32 पूर्णांक_drbl_पूर्णांक_mask;
	u32 पूर्णांक_मुख्य_पूर्णांक_mask;
	u32 cl_poपूर्णांकer_toggle;
	u32 cl_slot_num_mask;
	u32 clic_irq;
	u32 clic_in_err;
	u32 clic_out_err;
पूर्ण;

काष्ठा mvumi_dyn_list_entry अणु
	u32 src_low_addr;
	u32 src_high_addr;
	u32 अगर_length;
	u32 reserve;
पूर्ण;

#घोषणा SCSI_CMD_MARVELL_SPECIFIC	0xE1
#घोषणा CDB_CORE_MODULE			0x1
#घोषणा CDB_CORE_SHUTDOWN		0xB

क्रमागत अणु
	DRBL_HANDSHAKE			= 1 << 0,
	DRBL_SOFT_RESET			= 1 << 1,
	DRBL_BUS_CHANGE			= 1 << 2,
	DRBL_EVENT_NOTIFY		= 1 << 3,
	DRBL_MU_RESET			= 1 << 4,
	DRBL_HANDSHAKE_ISR		= DRBL_HANDSHAKE,

	/*
	* Command flag is the flag क्रम the CDB command itself
	*/
	/* 1-non data; 0-data command */
	CMD_FLAG_NON_DATA		= 1 << 0,
	CMD_FLAG_DMA			= 1 << 1,
	CMD_FLAG_PIO			= 1 << 2,
	/* 1-host पढ़ो data */
	CMD_FLAG_DATA_IN		= 1 << 3,
	/* 1-host ग_लिखो data */
	CMD_FLAG_DATA_OUT		= 1 << 4,
	CMD_FLAG_PRDT_IN_HOST		= 1 << 5,
पूर्ण;

#घोषणा APICDB0_EVENT			0xF4
#घोषणा APICDB1_EVENT_GETEVENT		0
#घोषणा APICDB1_HOST_GETEVENT		1
#घोषणा MAX_EVENTS_RETURNED		6

#घोषणा DEVICE_OFFLINE	0
#घोषणा DEVICE_ONLINE	1

काष्ठा mvumi_hotplug_event अणु
	u16 size;
	u8 dummy[2];
	u8 biपंचांगap[];
पूर्ण;

काष्ठा mvumi_driver_event अणु
	u32	समय_stamp;
	u32	sequence_no;
	u32	event_id;
	u8	severity;
	u8	param_count;
	u16	device_id;
	u32	params[4];
	u8	sense_data_length;
	u8	Reserved1;
	u8	sense_data[30];
पूर्ण;

काष्ठा mvumi_event_req अणु
	अचिन्हित अक्षर	count;
	अचिन्हित अक्षर	reserved[3];
	काष्ठा mvumi_driver_event  events[MAX_EVENTS_RETURNED];
पूर्ण;

काष्ठा mvumi_events_wq अणु
	काष्ठा work_काष्ठा work_q;
	काष्ठा mvumi_hba *mhba;
	अचिन्हित पूर्णांक event;
	व्योम *param;
पूर्ण;

#घोषणा HS_CAPABILITY_SUPPORT_COMPACT_SG	(1U << 4)
#घोषणा HS_CAPABILITY_SUPPORT_PRD_HOST		(1U << 5)
#घोषणा HS_CAPABILITY_SUPPORT_DYN_SRC		(1U << 6)
#घोषणा HS_CAPABILITY_NEW_PAGE_IO_DEPTH_DEF	(1U << 14)

#घोषणा MVUMI_MAX_SG_ENTRY	32
#घोषणा SGD_EOT			(1L << 27)
#घोषणा SGD_EOT_CP		(1L << 22)

काष्ठा mvumi_sgl अणु
	u32	baseaddr_l;
	u32	baseaddr_h;
	u32	flags;
	u32	size;
पूर्ण;
काष्ठा mvumi_compact_sgl अणु
	u32	baseaddr_l;
	u32	baseaddr_h;
	u32	flags;
पूर्ण;

#घोषणा GET_COMPACT_SGD_SIZE(sgd)	\
	((((काष्ठा mvumi_compact_sgl *)(sgd))->flags) & 0x3FFFFFL)

#घोषणा SET_COMPACT_SGD_SIZE(sgd, sz) करो अणु			\
	(((काष्ठा mvumi_compact_sgl *)(sgd))->flags) &= ~0x3FFFFFL;	\
	(((काष्ठा mvumi_compact_sgl *)(sgd))->flags) |= (sz);		\
पूर्ण जबतक (0)
#घोषणा sgd_माला_लोz(_mhba, sgd, sz) करो अणु				\
	अगर (_mhba->hba_capability & HS_CAPABILITY_SUPPORT_COMPACT_SG)	\
		(sz) = GET_COMPACT_SGD_SIZE(sgd);	\
	अन्यथा \
		(sz) = (sgd)->size;			\
पूर्ण जबतक (0)

#घोषणा sgd_setsz(_mhba, sgd, sz) करो अणु				\
	अगर (_mhba->hba_capability & HS_CAPABILITY_SUPPORT_COMPACT_SG)	\
		SET_COMPACT_SGD_SIZE(sgd, sz);		\
	अन्यथा \
		(sgd)->size = (sz);			\
पूर्ण जबतक (0)

#घोषणा sgd_inc(_mhba, sgd) करो अणु	\
	अगर (_mhba->hba_capability & HS_CAPABILITY_SUPPORT_COMPACT_SG)	\
		sgd = (काष्ठा mvumi_sgl *)(((अचिन्हित अक्षर *) (sgd)) + 12); \
	अन्यथा \
		sgd = (काष्ठा mvumi_sgl *)(((अचिन्हित अक्षर *) (sgd)) + 16); \
पूर्ण जबतक (0)

काष्ठा mvumi_res अणु
	काष्ठा list_head entry;
	dma_addr_t bus_addr;
	व्योम *virt_addr;
	अचिन्हित पूर्णांक size;
	अचिन्हित लघु type;	/* क्रमागत Resource_Type */
पूर्ण;

/* Resource type */
क्रमागत resource_type अणु
	RESOURCE_CACHED_MEMORY = 0,
	RESOURCE_UNCACHED_MEMORY
पूर्ण;

काष्ठा mvumi_sense_data अणु
	u8 error_code:7;
	u8 valid:1;
	u8 segment_number;
	u8 sense_key:4;
	u8 reserved:1;
	u8 incorrect_length:1;
	u8 end_of_media:1;
	u8 file_mark:1;
	u8 inक्रमmation[4];
	u8 additional_sense_length;
	u8 command_specअगरic_inक्रमmation[4];
	u8 additional_sense_code;
	u8 additional_sense_code_qualअगरier;
	u8 field_replaceable_unit_code;
	u8 sense_key_specअगरic[3];
पूर्ण;

/* Request initiator must set the status to REQ_STATUS_PENDING. */
#घोषणा REQ_STATUS_PENDING		0x80

काष्ठा mvumi_cmd अणु
	काष्ठा list_head queue_poपूर्णांकer;
	काष्ठा mvumi_msg_frame *frame;
	dma_addr_t frame_phys;
	काष्ठा scsi_cmnd *scmd;
	atomic_t sync_cmd;
	व्योम *data_buf;
	अचिन्हित लघु request_id;
	अचिन्हित अक्षर cmd_status;
पूर्ण;

/*
 * the function type of the in bound frame
 */
#घोषणा CL_FUN_SCSI_CMD			0x1

काष्ठा mvumi_msg_frame अणु
	u16 device_id;
	u16 tag;
	u8 cmd_flag;
	u8 req_function;
	u8 cdb_length;
	u8 sg_counts;
	u32 data_transfer_length;
	u16 request_id;
	u16 reserved1;
	u8 cdb[MAX_COMMAND_SIZE];
	u32 payload[1];
पूर्ण;

/*
 * the respond flag क्रम data_payload of the out bound frame
 */
#घोषणा CL_RSP_FLAG_NODATA		0x0
#घोषणा CL_RSP_FLAG_SENSEDATA		0x1

काष्ठा mvumi_rsp_frame अणु
	u16 device_id;
	u16 tag;
	u8 req_status;
	u8 rsp_flag;	/* Indicates the type of Data_Payload.*/
	u16 request_id;
	u32 payload[1];
पूर्ण;

काष्ठा mvumi_ob_data अणु
	काष्ठा list_head list;
	अचिन्हित अक्षर data[];
पूर्ण;

काष्ठा version_info अणु
	u32 ver_major;
	u32 ver_minor;
	u32 ver_oem;
	u32 ver_build;
पूर्ण;

#घोषणा FW_MAX_DELAY			30
#घोषणा MVUMI_FW_BUSY			(1U << 0)
#घोषणा MVUMI_FW_ATTACH			(1U << 1)
#घोषणा MVUMI_FW_ALLOC			(1U << 2)

/*
 * State is the state of the MU
 */
#घोषणा FW_STATE_IDLE			0
#घोषणा FW_STATE_STARTING		1
#घोषणा FW_STATE_HANDSHAKING		2
#घोषणा FW_STATE_STARTED		3
#घोषणा FW_STATE_ABORT			4

#घोषणा HANDSHAKE_SIGNATURE		0x5A5A5A5AL
#घोषणा HANDSHAKE_READYSTATE		0x55AA5AA5L
#घोषणा HANDSHAKE_DONESTATE		0x55AAA55AL

/* HandShake Status definition */
#घोषणा HS_STATUS_OK			1
#घोषणा HS_STATUS_ERR			2
#घोषणा HS_STATUS_INVALID		3

/* HandShake State/Cmd definition */
#घोषणा HS_S_START			1
#घोषणा HS_S_RESET			2
#घोषणा HS_S_PAGE_ADDR			3
#घोषणा HS_S_QUERY_PAGE			4
#घोषणा HS_S_SEND_PAGE			5
#घोषणा HS_S_END			6
#घोषणा HS_S_ABORT			7
#घोषणा HS_PAGE_VERIFY_SIZE		128

#घोषणा HS_GET_STATE(a)			(a & 0xFFFF)
#घोषणा HS_GET_STATUS(a)		((a & 0xFFFF0000) >> 16)
#घोषणा HS_SET_STATE(a, b)		(a |= (b & 0xFFFF))
#घोषणा HS_SET_STATUS(a, b)		(a |= ((b & 0xFFFF) << 16))

/* handshake frame */
काष्ठा mvumi_hs_frame अणु
	u16 size;
	/* host inक्रमmation */
	u8 host_type;
	u8 reserved_1[1];
	काष्ठा version_info host_ver; /* bios or driver version */

	/* controller inक्रमmation */
	u32 प्रणाली_io_bus;
	u32 slot_number;
	u32 पूर्णांकr_level;
	u32 पूर्णांकr_vector;

	/* communication list configuration */
	u32 ib_baseaddr_l;
	u32 ib_baseaddr_h;
	u32 ob_baseaddr_l;
	u32 ob_baseaddr_h;

	u8 ib_entry_size;
	u8 ob_entry_size;
	u8 ob_depth;
	u8 ib_depth;

	/* प्रणाली समय */
	u64 seconds_since1970;
पूर्ण;

काष्ठा mvumi_hs_header अणु
	u8	page_code;
	u8	checksum;
	u16	frame_length;
	u32	frame_content[1];
पूर्ण;

/*
 * the page code type of the handshake header
 */
#घोषणा HS_PAGE_FIRM_CAP	0x1
#घोषणा HS_PAGE_HOST_INFO	0x2
#घोषणा HS_PAGE_FIRM_CTL	0x3
#घोषणा HS_PAGE_CL_INFO		0x4
#घोषणा HS_PAGE_TOTAL		0x5

#घोषणा HSP_SIZE(i)	माप(काष्ठा mvumi_hs_page##i)

#घोषणा HSP_MAX_SIZE (अणु					\
	पूर्णांक size, m1, m2;				\
	m1 = max(HSP_SIZE(1), HSP_SIZE(3));		\
	m2 = max(HSP_SIZE(2), HSP_SIZE(4));		\
	size = max(m1, m2);				\
	size;						\
पूर्ण)

/* The क्रमmat of the page code क्रम Firmware capability */
काष्ठा mvumi_hs_page1 अणु
	u8 pagecode;
	u8 checksum;
	u16 frame_length;

	u16 number_of_ports;
	u16 max_devices_support;
	u16 max_io_support;
	u16 umi_ver;
	u32 max_transfer_size;
	काष्ठा version_info fw_ver;
	u8 cl_in_max_entry_size;
	u8 cl_out_max_entry_size;
	u8 cl_inout_list_depth;
	u8 total_pages;
	u16 capability;
	u16 reserved1;
पूर्ण;

/* The क्रमmat of the page code क्रम Host inक्रमmation */
काष्ठा mvumi_hs_page2 अणु
	u8 pagecode;
	u8 checksum;
	u16 frame_length;

	u8 host_type;
	u8 host_cap;
	u8 reserved[2];
	काष्ठा version_info host_ver;
	u32 प्रणाली_io_bus;
	u32 slot_number;
	u32 पूर्णांकr_level;
	u32 पूर्णांकr_vector;
	u64 seconds_since1970;
पूर्ण;

/* The क्रमmat of the page code क्रम firmware control  */
काष्ठा mvumi_hs_page3 अणु
	u8	pagecode;
	u8	checksum;
	u16	frame_length;
	u16	control;
	u8	reserved[2];
	u32	host_bufferaddr_l;
	u32	host_bufferaddr_h;
	u32	host_eventaddr_l;
	u32	host_eventaddr_h;
पूर्ण;

काष्ठा mvumi_hs_page4 अणु
	u8	pagecode;
	u8	checksum;
	u16	frame_length;
	u32	ib_baseaddr_l;
	u32	ib_baseaddr_h;
	u32	ob_baseaddr_l;
	u32	ob_baseaddr_h;
	u8	ib_entry_size;
	u8	ob_entry_size;
	u8	ob_depth;
	u8	ib_depth;
पूर्ण;

काष्ठा mvumi_tag अणु
	अचिन्हित लघु *stack;
	अचिन्हित लघु top;
	अचिन्हित लघु size;
पूर्ण;

काष्ठा mvumi_device अणु
	काष्ठा list_head list;
	काष्ठा scsi_device *sdev;
	u64	wwid;
	u8	dev_type;
	पूर्णांक	id;
पूर्ण;

काष्ठा mvumi_hba अणु
	व्योम *base_addr[MAX_BASE_ADDRESS];
	u32 pci_base[MAX_BASE_ADDRESS];
	व्योम *mmio;
	काष्ठा list_head cmd_pool;
	काष्ठा Scsi_Host *shost;
	रुको_queue_head_t पूर्णांक_cmd_रुको_q;
	काष्ठा pci_dev *pdev;
	अचिन्हित पूर्णांक unique_id;
	atomic_t fw_outstanding;
	काष्ठा mvumi_instance_ढाँचा *instancet;

	व्योम *ib_list;
	dma_addr_t ib_list_phys;

	व्योम *ib_frame;
	dma_addr_t ib_frame_phys;

	व्योम *ob_list;
	dma_addr_t ob_list_phys;

	व्योम *ib_shaकरोw;
	dma_addr_t ib_shaकरोw_phys;

	व्योम *ob_shaकरोw;
	dma_addr_t ob_shaकरोw_phys;

	व्योम *handshake_page;
	dma_addr_t handshake_page_phys;

	अचिन्हित पूर्णांक global_isr;
	अचिन्हित पूर्णांक isr_status;

	अचिन्हित लघु max_sge;
	अचिन्हित लघु max_target_id;
	अचिन्हित अक्षर *target_map;
	अचिन्हित पूर्णांक max_io;
	अचिन्हित पूर्णांक list_num_io;
	अचिन्हित पूर्णांक ib_max_size;
	अचिन्हित पूर्णांक ob_max_size;
	अचिन्हित पूर्णांक ib_max_size_setting;
	अचिन्हित पूर्णांक ob_max_size_setting;
	अचिन्हित पूर्णांक max_transfer_size;
	अचिन्हित अक्षर hba_total_pages;
	अचिन्हित अक्षर fw_flag;
	अचिन्हित अक्षर request_id_enabled;
	अचिन्हित अक्षर eot_flag;
	अचिन्हित लघु hba_capability;
	अचिन्हित लघु io_seq;

	अचिन्हित पूर्णांक ib_cur_slot;
	अचिन्हित पूर्णांक ob_cur_slot;
	अचिन्हित पूर्णांक fw_state;
	काष्ठा mutex sas_discovery_mutex;

	काष्ठा list_head ob_data_list;
	काष्ठा list_head मुक्त_ob_list;
	काष्ठा list_head res_list;
	काष्ठा list_head रुकोing_req_list;

	काष्ठा mvumi_tag tag_pool;
	काष्ठा mvumi_cmd **tag_cmd;
	काष्ठा mvumi_hw_regs *regs;
	काष्ठा mutex device_lock;
	काष्ठा list_head mhba_dev_list;
	काष्ठा list_head shost_dev_list;
	काष्ठा task_काष्ठा *dm_thपढ़ो;
	atomic_t pnp_count;
पूर्ण;

काष्ठा mvumi_instance_ढाँचा अणु
	व्योम (*fire_cmd) (काष्ठा mvumi_hba *, काष्ठा mvumi_cmd *);
	व्योम (*enable_पूर्णांकr) (काष्ठा mvumi_hba *);
	व्योम (*disable_पूर्णांकr) (काष्ठा mvumi_hba *);
	पूर्णांक (*clear_पूर्णांकr) (व्योम *);
	अचिन्हित पूर्णांक (*पढ़ो_fw_status_reg) (काष्ठा mvumi_hba *);
	अचिन्हित पूर्णांक (*check_ib_list) (काष्ठा mvumi_hba *);
	पूर्णांक (*check_ob_list) (काष्ठा mvumi_hba *, अचिन्हित पूर्णांक *,
			      अचिन्हित पूर्णांक *);
	पूर्णांक (*reset_host) (काष्ठा mvumi_hba *);
पूर्ण;

बाह्य काष्ठा समयzone sys_tz;
#पूर्ण_अगर
