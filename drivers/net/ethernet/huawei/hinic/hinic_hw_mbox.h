<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_MBOX_H_
#घोषणा HINIC_MBOX_H_

#घोषणा HINIC_MBOX_PF_SEND_ERR		0x1
#घोषणा HINIC_MBOX_PF_BUSY_ACTIVE_FW	0x2
#घोषणा HINIC_MBOX_VF_CMD_ERROR		0x3

#घोषणा HINIC_MAX_FUNCTIONS		512

#घोषणा HINIC_MAX_PF_FUNCS		16

#घोषणा HINIC_MBOX_WQ_NAME		"hinic_mbox"

#घोषणा HINIC_FUNC_CSR_MAILBOX_DATA_OFF			0x80
#घोषणा HINIC_FUNC_CSR_MAILBOX_CONTROL_OFF		0x0100
#घोषणा HINIC_FUNC_CSR_MAILBOX_INT_OFFSET_OFF		0x0104
#घोषणा HINIC_FUNC_CSR_MAILBOX_RESULT_H_OFF		0x0108
#घोषणा HINIC_FUNC_CSR_MAILBOX_RESULT_L_OFF		0x010C

#घोषणा MAX_FUNCTION_NUM		512

काष्ठा vf_cmd_check_handle अणु
	u8 cmd;
	bool (*check_cmd)(काष्ठा hinic_hwdev *hwdev, u16 src_func_idx,
			  व्योम *buf_in, u16 in_size);
पूर्ण;

क्रमागत hinic_mbox_ack_type अणु
	MBOX_ACK,
	MBOX_NO_ACK,
पूर्ण;

काष्ठा mbox_msg_info अणु
	u8 msg_id;
	u8 status;
पूर्ण;

काष्ठा hinic_recv_mbox अणु
	काष्ठा completion	recv_करोne;
	व्योम			*mbox;
	u8			cmd;
	क्रमागत hinic_mod_type	mod;
	u16			mbox_len;
	व्योम			*buf_out;
	क्रमागत hinic_mbox_ack_type ack_type;
	काष्ठा mbox_msg_info	msg_info;
	u8			seq_id;
	atomic_t		msg_cnt;
पूर्ण;

काष्ठा hinic_send_mbox अणु
	काष्ठा completion	send_करोne;
	u8			*data;

	u64			*wb_status;
	व्योम			*wb_vaddr;
	dma_addr_t		wb_paddr;
पूर्ण;

प्रकार व्योम (*hinic_vf_mbox_cb)(व्योम *handle, u8 cmd, व्योम *buf_in,
				u16 in_size, व्योम *buf_out, u16 *out_size);
प्रकार पूर्णांक (*hinic_pf_mbox_cb)(व्योम *handle, u16 vf_id, u8 cmd, व्योम *buf_in,
				u16 in_size, व्योम *buf_out, u16 *out_size);

क्रमागत mbox_event_state अणु
	EVENT_START = 0,
	EVENT_FAIL,
	EVENT_TIMEOUT,
	EVENT_END,
पूर्ण;

क्रमागत hinic_mbox_cb_state अणु
	HINIC_VF_MBOX_CB_REG = 0,
	HINIC_VF_MBOX_CB_RUNNING,
	HINIC_PF_MBOX_CB_REG,
	HINIC_PF_MBOX_CB_RUNNING,
	HINIC_PPF_MBOX_CB_REG,
	HINIC_PPF_MBOX_CB_RUNNING,
	HINIC_PPF_TO_PF_MBOX_CB_REG,
	HINIC_PPF_TO_PF_MBOX_CB_RUNNIG,
पूर्ण;

काष्ठा hinic_mbox_func_to_func अणु
	काष्ठा hinic_hwdev	*hwdev;
	काष्ठा hinic_hwअगर		*hwअगर;

	काष्ठा semaphore	mbox_send_sem;
	काष्ठा semaphore	msg_send_sem;
	काष्ठा hinic_send_mbox	send_mbox;

	काष्ठा workqueue_काष्ठा *workq;

	काष्ठा hinic_recv_mbox	mbox_resp[HINIC_MAX_FUNCTIONS];
	काष्ठा hinic_recv_mbox	mbox_send[HINIC_MAX_FUNCTIONS];

	hinic_vf_mbox_cb	vf_mbox_cb[HINIC_MOD_MAX];
	hinic_pf_mbox_cb	pf_mbox_cb[HINIC_MOD_MAX];
	अचिन्हित दीर्घ		pf_mbox_cb_state[HINIC_MOD_MAX];
	अचिन्हित दीर्घ		vf_mbox_cb_state[HINIC_MOD_MAX];

	u8 send_msg_id;
	क्रमागत mbox_event_state event_flag;

	/* lock क्रम mbox event flag */
	spinlock_t mbox_lock;

	u32 vf_mbx_old_अक्रम_id[MAX_FUNCTION_NUM];
	u32 vf_mbx_अक्रम_id[MAX_FUNCTION_NUM];
	bool support_vf_अक्रमom;
पूर्ण;

काष्ठा hinic_mbox_work अणु
	काष्ठा work_काष्ठा work;
	u16 src_func_idx;
	काष्ठा hinic_mbox_func_to_func *func_to_func;
	काष्ठा hinic_recv_mbox *recv_mbox;
पूर्ण;

काष्ठा vf_cmd_msg_handle अणु
	u8 cmd;
	पूर्णांक (*cmd_msg_handler)(व्योम *hwdev, u16 vf_id,
			       व्योम *buf_in, u16 in_size,
			       व्योम *buf_out, u16 *out_size);
पूर्ण;

bool hinic_mbox_check_func_id_8B(काष्ठा hinic_hwdev *hwdev, u16 func_idx,
				 व्योम *buf_in, u16 in_size);

bool hinic_mbox_check_cmd_valid(काष्ठा hinic_hwdev *hwdev,
				काष्ठा vf_cmd_check_handle *cmd_handle,
				u16 vf_id, u8 cmd, व्योम *buf_in,
				u16 in_size, u8 size);

पूर्णांक hinic_रेजिस्टर_pf_mbox_cb(काष्ठा hinic_hwdev *hwdev,
			      क्रमागत hinic_mod_type mod,
			      hinic_pf_mbox_cb callback);

पूर्णांक hinic_रेजिस्टर_vf_mbox_cb(काष्ठा hinic_hwdev *hwdev,
			      क्रमागत hinic_mod_type mod,
			      hinic_vf_mbox_cb callback);

व्योम hinic_unरेजिस्टर_pf_mbox_cb(काष्ठा hinic_hwdev *hwdev,
				 क्रमागत hinic_mod_type mod);

व्योम hinic_unरेजिस्टर_vf_mbox_cb(काष्ठा hinic_hwdev *hwdev,
				 क्रमागत hinic_mod_type mod);

व्योम hinic_mbox_func_aeqe_handler(व्योम *handle, व्योम *header, u8 size);

व्योम hinic_mbox_self_aeqe_handler(व्योम *handle, व्योम *header, u8 size);

पूर्णांक hinic_func_to_func_init(काष्ठा hinic_hwdev *hwdev);

व्योम hinic_func_to_func_मुक्त(काष्ठा hinic_hwdev *hwdev);

पूर्णांक hinic_mbox_to_pf(काष्ठा hinic_hwdev *hwdev, क्रमागत hinic_mod_type mod,
		     u8 cmd, व्योम *buf_in, u16 in_size, व्योम *buf_out,
		     u16 *out_size, u32 समयout);

पूर्णांक hinic_mbox_to_func(काष्ठा hinic_mbox_func_to_func *func_to_func,
		       क्रमागत hinic_mod_type mod, u16 cmd, u16 dst_func,
		       व्योम *buf_in, u16 in_size, व्योम *buf_out,
		       u16 *out_size, u32 समयout);

पूर्णांक hinic_mbox_to_vf(काष्ठा hinic_hwdev *hwdev,
		     क्रमागत hinic_mod_type mod, u16 vf_id, u8 cmd, व्योम *buf_in,
		     u16 in_size, व्योम *buf_out, u16 *out_size, u32 समयout);

पूर्णांक hinic_vf_mbox_अक्रमom_id_init(काष्ठा hinic_hwdev *hwdev);

#पूर्ण_अगर
