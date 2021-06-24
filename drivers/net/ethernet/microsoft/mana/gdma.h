<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2021, Microsoft Corporation. */

#अगर_अघोषित _GDMA_H
#घोषणा _GDMA_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>

#समावेश "shm_channel.h"

/* Structures labeled with "HW DATA" are exchanged with the hardware. All of
 * them are naturally aligned and hence करोn't need __packed.
 */

क्रमागत gdma_request_type अणु
	GDMA_VERIFY_VF_DRIVER_VERSION	= 1,
	GDMA_QUERY_MAX_RESOURCES	= 2,
	GDMA_LIST_DEVICES		= 3,
	GDMA_REGISTER_DEVICE		= 4,
	GDMA_DEREGISTER_DEVICE		= 5,
	GDMA_GENERATE_TEST_EQE		= 10,
	GDMA_CREATE_QUEUE		= 12,
	GDMA_DISABLE_QUEUE		= 13,
	GDMA_CREATE_DMA_REGION		= 25,
	GDMA_DMA_REGION_ADD_PAGES	= 26,
	GDMA_DESTROY_DMA_REGION		= 27,
पूर्ण;

क्रमागत gdma_queue_type अणु
	GDMA_INVALID_QUEUE,
	GDMA_SQ,
	GDMA_RQ,
	GDMA_CQ,
	GDMA_EQ,
पूर्ण;

क्रमागत gdma_work_request_flags अणु
	GDMA_WR_NONE			= 0,
	GDMA_WR_OOB_IN_SGL		= BIT(0),
	GDMA_WR_PAD_BY_SGE0		= BIT(1),
पूर्ण;

क्रमागत gdma_eqe_type अणु
	GDMA_EQE_COMPLETION		= 3,
	GDMA_EQE_TEST_EVENT		= 64,
	GDMA_EQE_HWC_INIT_EQ_ID_DB	= 129,
	GDMA_EQE_HWC_INIT_DATA		= 130,
	GDMA_EQE_HWC_INIT_DONE		= 131,
पूर्ण;

क्रमागत अणु
	GDMA_DEVICE_NONE	= 0,
	GDMA_DEVICE_HWC		= 1,
	GDMA_DEVICE_MANA	= 2,
पूर्ण;

काष्ठा gdma_resource अणु
	/* Protect the biपंचांगap */
	spinlock_t lock;

	/* The biपंचांगap size in bits. */
	u32 size;

	/* The biपंचांगap tracks the resources. */
	अचिन्हित दीर्घ *map;
पूर्ण;

जोड़ gdma_करोorbell_entry अणु
	u64	as_uपूर्णांक64;

	काष्ठा अणु
		u64 id		: 24;
		u64 reserved	: 8;
		u64 tail_ptr	: 31;
		u64 arm		: 1;
	पूर्ण cq;

	काष्ठा अणु
		u64 id		: 24;
		u64 wqe_cnt	: 8;
		u64 tail_ptr	: 32;
	पूर्ण rq;

	काष्ठा अणु
		u64 id		: 24;
		u64 reserved	: 8;
		u64 tail_ptr	: 32;
	पूर्ण sq;

	काष्ठा अणु
		u64 id		: 16;
		u64 reserved	: 16;
		u64 tail_ptr	: 31;
		u64 arm		: 1;
	पूर्ण eq;
पूर्ण; /* HW DATA */

काष्ठा gdma_msg_hdr अणु
	u32 hdr_type;
	u32 msg_type;
	u16 msg_version;
	u16 hwc_msg_id;
	u32 msg_size;
पूर्ण; /* HW DATA */

काष्ठा gdma_dev_id अणु
	जोड़ अणु
		काष्ठा अणु
			u16 type;
			u16 instance;
		पूर्ण;

		u32 as_uपूर्णांक32;
	पूर्ण;
पूर्ण; /* HW DATA */

काष्ठा gdma_req_hdr अणु
	काष्ठा gdma_msg_hdr req;
	काष्ठा gdma_msg_hdr resp; /* The expected response */
	काष्ठा gdma_dev_id dev_id;
	u32 activity_id;
पूर्ण; /* HW DATA */

काष्ठा gdma_resp_hdr अणु
	काष्ठा gdma_msg_hdr response;
	काष्ठा gdma_dev_id dev_id;
	u32 activity_id;
	u32 status;
	u32 reserved;
पूर्ण; /* HW DATA */

काष्ठा gdma_general_req अणु
	काष्ठा gdma_req_hdr hdr;
पूर्ण; /* HW DATA */

#घोषणा GDMA_MESSAGE_V1 1

काष्ठा gdma_general_resp अणु
	काष्ठा gdma_resp_hdr hdr;
पूर्ण; /* HW DATA */

#घोषणा GDMA_STANDARD_HEADER_TYPE 0

अटल अंतरभूत व्योम mana_gd_init_req_hdr(काष्ठा gdma_req_hdr *hdr, u32 code,
					u32 req_size, u32 resp_size)
अणु
	hdr->req.hdr_type = GDMA_STANDARD_HEADER_TYPE;
	hdr->req.msg_type = code;
	hdr->req.msg_version = GDMA_MESSAGE_V1;
	hdr->req.msg_size = req_size;

	hdr->resp.hdr_type = GDMA_STANDARD_HEADER_TYPE;
	hdr->resp.msg_type = code;
	hdr->resp.msg_version = GDMA_MESSAGE_V1;
	hdr->resp.msg_size = resp_size;
पूर्ण

/* The 16-byte काष्ठा is part of the GDMA work queue entry (WQE). */
काष्ठा gdma_sge अणु
	u64 address;
	u32 mem_key;
	u32 size;
पूर्ण; /* HW DATA */

काष्ठा gdma_wqe_request अणु
	काष्ठा gdma_sge *sgl;
	u32 num_sge;

	u32 अंतरभूत_oob_size;
	स्थिर व्योम *अंतरभूत_oob_data;

	u32 flags;
	u32 client_data_unit;
पूर्ण;

क्रमागत gdma_page_type अणु
	GDMA_PAGE_TYPE_4K,
पूर्ण;

#घोषणा GDMA_INVALID_DMA_REGION 0

काष्ठा gdma_mem_info अणु
	काष्ठा device *dev;

	dma_addr_t dma_handle;
	व्योम *virt_addr;
	u64 length;

	/* Allocated by the PF driver */
	u64 gdma_region;
पूर्ण;

#घोषणा REGISTER_ATB_MST_MKEY_LOWER_SIZE 8

काष्ठा gdma_dev अणु
	काष्ठा gdma_context *gdma_context;

	काष्ठा gdma_dev_id dev_id;

	u32 pdid;
	u32 करोorbell;
	u32 gpa_mkey;

	/* GDMA driver specअगरic poपूर्णांकer */
	व्योम *driver_data;
पूर्ण;

#घोषणा MINIMUM_SUPPORTED_PAGE_SIZE PAGE_SIZE

#घोषणा GDMA_CQE_SIZE 64
#घोषणा GDMA_EQE_SIZE 16
#घोषणा GDMA_MAX_SQE_SIZE 512
#घोषणा GDMA_MAX_RQE_SIZE 256

#घोषणा GDMA_COMP_DATA_SIZE 0x3C

#घोषणा GDMA_EVENT_DATA_SIZE 0xC

/* The WQE size must be a multiple of the Basic Unit, which is 32 bytes. */
#घोषणा GDMA_WQE_BU_SIZE 32

#घोषणा INVALID_PDID		अच_पूर्णांक_उच्च
#घोषणा INVALID_DOORBELL	अच_पूर्णांक_उच्च
#घोषणा INVALID_MEM_KEY		अच_पूर्णांक_उच्च
#घोषणा INVALID_QUEUE_ID	अच_पूर्णांक_उच्च
#घोषणा INVALID_PCI_MSIX_INDEX  अच_पूर्णांक_उच्च

काष्ठा gdma_comp अणु
	u32 cqe_data[GDMA_COMP_DATA_SIZE / 4];
	u32 wq_num;
	bool is_sq;
पूर्ण;

काष्ठा gdma_event अणु
	u32 details[GDMA_EVENT_DATA_SIZE / 4];
	u8  type;
पूर्ण;

काष्ठा gdma_queue;

#घोषणा CQE_POLLING_BUFFER 512
काष्ठा mana_eq अणु
	काष्ठा gdma_queue *eq;
	काष्ठा gdma_comp cqe_poll[CQE_POLLING_BUFFER];
पूर्ण;

प्रकार व्योम gdma_eq_callback(व्योम *context, काष्ठा gdma_queue *q,
			      काष्ठा gdma_event *e);

प्रकार व्योम gdma_cq_callback(व्योम *context, काष्ठा gdma_queue *q);

/* The 'head' is the producer index. For SQ/RQ, when the driver posts a WQE
 * (Note: the WQE size must be a multiple of the 32-byte Basic Unit), the
 * driver increases the 'head' in BUs rather than in bytes, and notअगरies
 * the HW of the updated head. For EQ/CQ, the driver uses the 'head' to track
 * the HW head, and increases the 'head' by 1 क्रम every processed EQE/CQE.
 *
 * The 'tail' is the consumer index क्रम SQ/RQ. After the CQE of the SQ/RQ is
 * processed, the driver increases the 'tail' to indicate that WQEs have
 * been consumed by the HW, so the driver can post new WQEs पूर्णांकo the SQ/RQ.
 *
 * The driver करोesn't use the 'tail' क्रम EQ/CQ, because the driver ensures
 * that the EQ/CQ is big enough so they can't overflow, and the driver uses
 * the owner bits mechanism to detect अगर the queue has become empty.
 */
काष्ठा gdma_queue अणु
	काष्ठा gdma_dev *gdma_dev;

	क्रमागत gdma_queue_type type;
	u32 id;

	काष्ठा gdma_mem_info mem_info;

	व्योम *queue_mem_ptr;
	u32 queue_size;

	bool monitor_avl_buf;

	u32 head;
	u32 tail;

	/* Extra fields specअगरic to EQ/CQ. */
	जोड़ अणु
		काष्ठा अणु
			bool disable_needed;

			gdma_eq_callback *callback;
			व्योम *context;

			अचिन्हित पूर्णांक msix_index;

			u32 log2_throttle_limit;

			/* NAPI data */
			काष्ठा napi_काष्ठा napi;
			पूर्णांक work_करोne;
			पूर्णांक budget;
		पूर्ण eq;

		काष्ठा अणु
			gdma_cq_callback *callback;
			व्योम *context;

			काष्ठा gdma_queue *parent; /* For CQ/EQ relationship */
		पूर्ण cq;
	पूर्ण;
पूर्ण;

काष्ठा gdma_queue_spec अणु
	क्रमागत gdma_queue_type type;
	bool monitor_avl_buf;
	अचिन्हित पूर्णांक queue_size;

	/* Extra fields specअगरic to EQ/CQ. */
	जोड़ अणु
		काष्ठा अणु
			gdma_eq_callback *callback;
			व्योम *context;

			अचिन्हित दीर्घ log2_throttle_limit;

			/* Only used by the MANA device. */
			काष्ठा net_device *ndev;
		पूर्ण eq;

		काष्ठा अणु
			gdma_cq_callback *callback;
			व्योम *context;

			काष्ठा gdma_queue *parent_eq;

		पूर्ण cq;
	पूर्ण;
पूर्ण;

काष्ठा gdma_irq_context अणु
	व्योम (*handler)(व्योम *arg);
	व्योम *arg;
पूर्ण;

काष्ठा gdma_context अणु
	काष्ठा device		*dev;

	/* Per-vPort max number of queues */
	अचिन्हित पूर्णांक		max_num_queues;
	अचिन्हित पूर्णांक		max_num_msix;
	अचिन्हित पूर्णांक		num_msix_usable;
	काष्ठा gdma_resource	msix_resource;
	काष्ठा gdma_irq_context	*irq_contexts;

	/* This maps a CQ index to the queue काष्ठाure. */
	अचिन्हित पूर्णांक		max_num_cqs;
	काष्ठा gdma_queue	**cq_table;

	/* Protect eq_test_event and test_event_eq_id  */
	काष्ठा mutex		eq_test_event_mutex;
	काष्ठा completion	eq_test_event;
	u32			test_event_eq_id;

	व्योम __iomem		*bar0_va;
	व्योम __iomem		*shm_base;
	व्योम __iomem		*db_page_base;
	u32 db_page_size;

	/* Shared memory chanenl (used to bootstrap HWC) */
	काष्ठा shm_channel	shm_channel;

	/* Hardware communication channel (HWC) */
	काष्ठा gdma_dev		hwc;

	/* Azure network adapter */
	काष्ठा gdma_dev		mana;
पूर्ण;

#घोषणा MAX_NUM_GDMA_DEVICES	4

अटल अंतरभूत bool mana_gd_is_mana(काष्ठा gdma_dev *gd)
अणु
	वापस gd->dev_id.type == GDMA_DEVICE_MANA;
पूर्ण

अटल अंतरभूत bool mana_gd_is_hwc(काष्ठा gdma_dev *gd)
अणु
	वापस gd->dev_id.type == GDMA_DEVICE_HWC;
पूर्ण

u8 *mana_gd_get_wqe_ptr(स्थिर काष्ठा gdma_queue *wq, u32 wqe_offset);
u32 mana_gd_wq_avail_space(काष्ठा gdma_queue *wq);

पूर्णांक mana_gd_test_eq(काष्ठा gdma_context *gc, काष्ठा gdma_queue *eq);

पूर्णांक mana_gd_create_hwc_queue(काष्ठा gdma_dev *gd,
			     स्थिर काष्ठा gdma_queue_spec *spec,
			     काष्ठा gdma_queue **queue_ptr);

पूर्णांक mana_gd_create_mana_eq(काष्ठा gdma_dev *gd,
			   स्थिर काष्ठा gdma_queue_spec *spec,
			   काष्ठा gdma_queue **queue_ptr);

पूर्णांक mana_gd_create_mana_wq_cq(काष्ठा gdma_dev *gd,
			      स्थिर काष्ठा gdma_queue_spec *spec,
			      काष्ठा gdma_queue **queue_ptr);

व्योम mana_gd_destroy_queue(काष्ठा gdma_context *gc, काष्ठा gdma_queue *queue);

पूर्णांक mana_gd_poll_cq(काष्ठा gdma_queue *cq, काष्ठा gdma_comp *comp, पूर्णांक num_cqe);

व्योम mana_gd_arm_cq(काष्ठा gdma_queue *cq);

काष्ठा gdma_wqe अणु
	u32 reserved	:24;
	u32 last_vbytes	:8;

	जोड़ अणु
		u32 flags;

		काष्ठा अणु
			u32 num_sge		:8;
			u32 अंतरभूत_oob_size_भाग4:3;
			u32 client_oob_in_sgl	:1;
			u32 reserved1		:4;
			u32 client_data_unit	:14;
			u32 reserved2		:2;
		पूर्ण;
	पूर्ण;
पूर्ण; /* HW DATA */

#घोषणा INLINE_OOB_SMALL_SIZE 8
#घोषणा INLINE_OOB_LARGE_SIZE 24

#घोषणा MAX_TX_WQE_SIZE 512
#घोषणा MAX_RX_WQE_SIZE 256

काष्ठा gdma_cqe अणु
	u32 cqe_data[GDMA_COMP_DATA_SIZE / 4];

	जोड़ अणु
		u32 as_uपूर्णांक32;

		काष्ठा अणु
			u32 wq_num	: 24;
			u32 is_sq	: 1;
			u32 reserved	: 4;
			u32 owner_bits	: 3;
		पूर्ण;
	पूर्ण cqe_info;
पूर्ण; /* HW DATA */

#घोषणा GDMA_CQE_OWNER_BITS 3

#घोषणा GDMA_CQE_OWNER_MASK ((1 << GDMA_CQE_OWNER_BITS) - 1)

#घोषणा SET_ARM_BIT 1

#घोषणा GDMA_EQE_OWNER_BITS 3

जोड़ gdma_eqe_info अणु
	u32 as_uपूर्णांक32;

	काष्ठा अणु
		u32 type	: 8;
		u32 reserved1	: 8;
		u32 client_id	: 2;
		u32 reserved2	: 11;
		u32 owner_bits	: 3;
	पूर्ण;
पूर्ण; /* HW DATA */

#घोषणा GDMA_EQE_OWNER_MASK ((1 << GDMA_EQE_OWNER_BITS) - 1)
#घोषणा INITIALIZED_OWNER_BIT(log2_num_entries) (1UL << (log2_num_entries))

काष्ठा gdma_eqe अणु
	u32 details[GDMA_EVENT_DATA_SIZE / 4];
	u32 eqe_info;
पूर्ण; /* HW DATA */

#घोषणा GDMA_REG_DB_PAGE_OFFSET	8
#घोषणा GDMA_REG_DB_PAGE_SIZE	0x10
#घोषणा GDMA_REG_SHM_OFFSET	0x18

काष्ठा gdma_posted_wqe_info अणु
	u32 wqe_size_in_bu;
पूर्ण;

/* GDMA_GENERATE_TEST_EQE */
काष्ठा gdma_generate_test_event_req अणु
	काष्ठा gdma_req_hdr hdr;
	u32 queue_index;
पूर्ण; /* HW DATA */

/* GDMA_VERIFY_VF_DRIVER_VERSION */
क्रमागत अणु
	GDMA_PROTOCOL_V1	= 1,
	GDMA_PROTOCOL_FIRST	= GDMA_PROTOCOL_V1,
	GDMA_PROTOCOL_LAST	= GDMA_PROTOCOL_V1,
पूर्ण;

काष्ठा gdma_verअगरy_ver_req अणु
	काष्ठा gdma_req_hdr hdr;

	/* Mandatory fields required क्रम protocol establishment */
	u64 protocol_ver_min;
	u64 protocol_ver_max;
	u64 drv_cap_flags1;
	u64 drv_cap_flags2;
	u64 drv_cap_flags3;
	u64 drv_cap_flags4;

	/* Advisory fields */
	u64 drv_ver;
	u32 os_type; /* Linux = 0x10; Winकरोws = 0x20; Other = 0x30 */
	u32 reserved;
	u32 os_ver_major;
	u32 os_ver_minor;
	u32 os_ver_build;
	u32 os_ver_platक्रमm;
	u64 reserved_2;
	u8 os_ver_str1[128];
	u8 os_ver_str2[128];
	u8 os_ver_str3[128];
	u8 os_ver_str4[128];
पूर्ण; /* HW DATA */

काष्ठा gdma_verअगरy_ver_resp अणु
	काष्ठा gdma_resp_hdr hdr;
	u64 gdma_protocol_ver;
	u64 pf_cap_flags1;
	u64 pf_cap_flags2;
	u64 pf_cap_flags3;
	u64 pf_cap_flags4;
पूर्ण; /* HW DATA */

/* GDMA_QUERY_MAX_RESOURCES */
काष्ठा gdma_query_max_resources_resp अणु
	काष्ठा gdma_resp_hdr hdr;
	u32 status;
	u32 max_sq;
	u32 max_rq;
	u32 max_cq;
	u32 max_eq;
	u32 max_db;
	u32 max_mst;
	u32 max_cq_mod_ctx;
	u32 max_mod_cq;
	u32 max_msix;
पूर्ण; /* HW DATA */

/* GDMA_LIST_DEVICES */
काष्ठा gdma_list_devices_resp अणु
	काष्ठा gdma_resp_hdr hdr;
	u32 num_of_devs;
	u32 reserved;
	काष्ठा gdma_dev_id devs[64];
पूर्ण; /* HW DATA */

/* GDMA_REGISTER_DEVICE */
काष्ठा gdma_रेजिस्टर_device_resp अणु
	काष्ठा gdma_resp_hdr hdr;
	u32 pdid;
	u32 gpa_mkey;
	u32 db_id;
पूर्ण; /* HW DATA */

/* GDMA_CREATE_QUEUE */
काष्ठा gdma_create_queue_req अणु
	काष्ठा gdma_req_hdr hdr;
	u32 type;
	u32 reserved1;
	u32 pdid;
	u32 करोolbell_id;
	u64 gdma_region;
	u32 reserved2;
	u32 queue_size;
	u32 log2_throttle_limit;
	u32 eq_pci_msix_index;
	u32 cq_mod_ctx_id;
	u32 cq_parent_eq_id;
	u8  rq_drop_on_overrun;
	u8  rq_err_on_wqe_overflow;
	u8  rq_chain_rec_wqes;
	u8  sq_hw_db;
	u32 reserved3;
पूर्ण; /* HW DATA */

काष्ठा gdma_create_queue_resp अणु
	काष्ठा gdma_resp_hdr hdr;
	u32 queue_index;
पूर्ण; /* HW DATA */

/* GDMA_DISABLE_QUEUE */
काष्ठा gdma_disable_queue_req अणु
	काष्ठा gdma_req_hdr hdr;
	u32 type;
	u32 queue_index;
	u32 alloc_res_id_on_creation;
पूर्ण; /* HW DATA */

/* GDMA_CREATE_DMA_REGION */
काष्ठा gdma_create_dma_region_req अणु
	काष्ठा gdma_req_hdr hdr;

	/* The total size of the DMA region */
	u64 length;

	/* The offset in the first page */
	u32 offset_in_page;

	/* क्रमागत gdma_page_type */
	u32 gdma_page_type;

	/* The total number of pages */
	u32 page_count;

	/* If page_addr_list_len is smaller than page_count,
	 * the reमुख्यing page addresses will be added via the
	 * message GDMA_DMA_REGION_ADD_PAGES.
	 */
	u32 page_addr_list_len;
	u64 page_addr_list[];
पूर्ण; /* HW DATA */

काष्ठा gdma_create_dma_region_resp अणु
	काष्ठा gdma_resp_hdr hdr;
	u64 gdma_region;
पूर्ण; /* HW DATA */

/* GDMA_DMA_REGION_ADD_PAGES */
काष्ठा gdma_dma_region_add_pages_req अणु
	काष्ठा gdma_req_hdr hdr;

	u64 gdma_region;

	u32 page_addr_list_len;
	u32 reserved3;

	u64 page_addr_list[];
पूर्ण; /* HW DATA */

/* GDMA_DESTROY_DMA_REGION */
काष्ठा gdma_destroy_dma_region_req अणु
	काष्ठा gdma_req_hdr hdr;

	u64 gdma_region;
पूर्ण; /* HW DATA */

पूर्णांक mana_gd_verअगरy_vf_version(काष्ठा pci_dev *pdev);

पूर्णांक mana_gd_रेजिस्टर_device(काष्ठा gdma_dev *gd);
पूर्णांक mana_gd_deरेजिस्टर_device(काष्ठा gdma_dev *gd);

पूर्णांक mana_gd_post_work_request(काष्ठा gdma_queue *wq,
			      स्थिर काष्ठा gdma_wqe_request *wqe_req,
			      काष्ठा gdma_posted_wqe_info *wqe_info);

पूर्णांक mana_gd_post_and_ring(काष्ठा gdma_queue *queue,
			  स्थिर काष्ठा gdma_wqe_request *wqe,
			  काष्ठा gdma_posted_wqe_info *wqe_info);

पूर्णांक mana_gd_alloc_res_map(u32 res_avail, काष्ठा gdma_resource *r);
व्योम mana_gd_मुक्त_res_map(काष्ठा gdma_resource *r);

व्योम mana_gd_wq_ring_करोorbell(काष्ठा gdma_context *gc,
			      काष्ठा gdma_queue *queue);

पूर्णांक mana_gd_alloc_memory(काष्ठा gdma_context *gc, अचिन्हित पूर्णांक length,
			 काष्ठा gdma_mem_info *gmi);

व्योम mana_gd_मुक्त_memory(काष्ठा gdma_mem_info *gmi);

पूर्णांक mana_gd_send_request(काष्ठा gdma_context *gc, u32 req_len, स्थिर व्योम *req,
			 u32 resp_len, व्योम *resp);
#पूर्ण_अगर /* _GDMA_H */
