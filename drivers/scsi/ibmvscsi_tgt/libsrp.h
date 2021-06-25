<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBSRP_H__
#घोषणा __LIBSRP_H__

#समावेश <linux/list.h>
#समावेश <linux/kfअगरo.h>
#समावेश <scsi/srp.h>

क्रमागत srp_valid अणु
	INVALIDATE_CMD_RESP_EL = 0,
	VALID_CMD_RESP_EL = 0x80,
	VALID_INIT_MSG = 0xC0,
	VALID_TRANS_EVENT = 0xFF
पूर्ण;

क्रमागत srp_क्रमmat अणु
	SRP_FORMAT = 1,
	MAD_FORMAT = 2,
	OS400_FORMAT = 3,
	AIX_FORMAT = 4,
	LINUX_FORMAT = 5,
	MESSAGE_IN_CRQ = 6
पूर्ण;

क्रमागत srp_init_msg अणु
	INIT_MSG = 1,
	INIT_COMPLETE_MSG = 2
पूर्ण;

क्रमागत srp_trans_event अणु
	UNUSED_FORMAT = 0,
	PARTNER_FAILED = 1,
	PARTNER_DEREGISTER = 2,
	MIGRATED = 6,
	PREPARE_FOR_SUSPEND = 9,
	RESUME_FROM_SUSP = 0xA
पूर्ण;

क्रमागत srp_status अणु
	CRQ_ENTRY_OVERWRITTEN = 0x20,
	HEADER_DESCRIPTOR = 0xF1,
	PING = 0xF5,
	PING_RESPONSE = 0xF6
पूर्ण;

क्रमागत srp_mad_version अणु
	MAD_VERSION_1 = 1
पूर्ण;

क्रमागत srp_os_type अणु
	OS400 = 1,
	LINUX = 2,
	AIX = 3,
	OFW = 4
पूर्ण;

क्रमागत srp_task_attributes अणु
	SRP_SIMPLE_TASK = 0,
	SRP_HEAD_TASK = 1,
	SRP_ORDERED_TASK = 2,
	SRP_ACA_TASK = 4
पूर्ण;

क्रमागत अणु
	SRP_TASK_MANAGEMENT_FUNCTION_COMPLETE           = 0,
	SRP_REQUEST_FIELDS_INVALID                      = 2,
	SRP_TASK_MANAGEMENT_FUNCTION_NOT_SUPPORTED      = 4,
	SRP_TASK_MANAGEMENT_FUNCTION_FAILED             = 5
पूर्ण;

काष्ठा srp_buf अणु
	dma_addr_t dma;
	व्योम *buf;
पूर्ण;

काष्ठा srp_queue अणु
	व्योम *pool;
	व्योम *items;
	काष्ठा kfअगरo queue;
	spinlock_t lock;
पूर्ण;

काष्ठा srp_target अणु
	काष्ठा device *dev;

	spinlock_t lock;
	काष्ठा list_head cmd_queue;

	माप_प्रकार srp_iu_size;
	काष्ठा srp_queue iu_queue;
	माप_प्रकार rx_ring_size;
	काष्ठा srp_buf **rx_ring;

	व्योम *ldata;
पूर्ण;

काष्ठा iu_entry अणु
	काष्ठा srp_target *target;

	काष्ठा list_head ilist;
	dma_addr_t remote_token;
	अचिन्हित दीर्घ flags;

	काष्ठा srp_buf *sbuf;
	u16 iu_len;
पूर्ण;

काष्ठा ibmvscsis_cmd;

प्रकार पूर्णांक (srp_rdma_t)(काष्ठा ibmvscsis_cmd *, काष्ठा scatterlist *, पूर्णांक,
			 काष्ठा srp_direct_buf *, पूर्णांक,
			 क्रमागत dma_data_direction, अचिन्हित पूर्णांक);
पूर्णांक srp_target_alloc(काष्ठा srp_target *, काष्ठा device *, माप_प्रकार, माप_प्रकार);
व्योम srp_target_मुक्त(काष्ठा srp_target *);
काष्ठा iu_entry *srp_iu_get(काष्ठा srp_target *);
व्योम srp_iu_put(काष्ठा iu_entry *);
पूर्णांक srp_transfer_data(काष्ठा ibmvscsis_cmd *, काष्ठा srp_cmd *,
		      srp_rdma_t, पूर्णांक, पूर्णांक);
u64 srp_data_length(काष्ठा srp_cmd *cmd, क्रमागत dma_data_direction dir);
पूर्णांक srp_get_desc_table(काष्ठा srp_cmd *srp_cmd, क्रमागत dma_data_direction *dir,
		       u64 *data_len);
अटल अंतरभूत पूर्णांक srp_cmd_direction(काष्ठा srp_cmd *cmd)
अणु
	वापस (cmd->buf_fmt >> 4) ? DMA_TO_DEVICE : DMA_FROM_DEVICE;
पूर्ण

#पूर्ण_अगर
