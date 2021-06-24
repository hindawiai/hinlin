<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_HW_MGMT_H
#घोषणा HINIC_HW_MGMT_H

#समावेश <linux/types.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/completion.h>
#समावेश <linux/bitops.h>

#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_api_cmd.h"

#घोषणा HINIC_MSG_HEADER_MSG_LEN_SHIFT                          0
#घोषणा HINIC_MSG_HEADER_MODULE_SHIFT                           11
#घोषणा HINIC_MSG_HEADER_SEG_LEN_SHIFT                          16
#घोषणा HINIC_MSG_HEADER_NO_ACK_SHIFT                           22
#घोषणा HINIC_MSG_HEADER_ASYNC_MGMT_TO_PF_SHIFT                 23
#घोषणा HINIC_MSG_HEADER_SEQID_SHIFT                            24
#घोषणा HINIC_MSG_HEADER_LAST_SHIFT                             30
#घोषणा HINIC_MSG_HEADER_सूचीECTION_SHIFT                        31
#घोषणा HINIC_MSG_HEADER_CMD_SHIFT                              32
#घोषणा HINIC_MSG_HEADER_ZEROS_SHIFT                            40
#घोषणा HINIC_MSG_HEADER_PCI_INTF_SHIFT                         48
#घोषणा HINIC_MSG_HEADER_PF_IDX_SHIFT                           50
#घोषणा HINIC_MSG_HEADER_MSG_ID_SHIFT                           54

#घोषणा HINIC_MSG_HEADER_MSG_LEN_MASK                           0x7FF
#घोषणा HINIC_MSG_HEADER_MODULE_MASK                            0x1F
#घोषणा HINIC_MSG_HEADER_SEG_LEN_MASK                           0x3F
#घोषणा HINIC_MSG_HEADER_NO_ACK_MASK                            0x1
#घोषणा HINIC_MSG_HEADER_ASYNC_MGMT_TO_PF_MASK                  0x1
#घोषणा HINIC_MSG_HEADER_SEQID_MASK                             0x3F
#घोषणा HINIC_MSG_HEADER_LAST_MASK                              0x1
#घोषणा HINIC_MSG_HEADER_सूचीECTION_MASK                         0x1
#घोषणा HINIC_MSG_HEADER_CMD_MASK                               0xFF
#घोषणा HINIC_MSG_HEADER_ZEROS_MASK                             0xFF
#घोषणा HINIC_MSG_HEADER_PCI_INTF_MASK                          0x3
#घोषणा HINIC_MSG_HEADER_PF_IDX_MASK                            0xF
#घोषणा HINIC_MSG_HEADER_MSG_ID_MASK                            0x3FF

#घोषणा HINIC_MSG_HEADER_SET(val, member)                       \
		((u64)((val) & HINIC_MSG_HEADER_##member##_MASK) << \
		 HINIC_MSG_HEADER_##member##_SHIFT)

#घोषणा HINIC_MSG_HEADER_GET(val, member)                       \
		(((val) >> HINIC_MSG_HEADER_##member##_SHIFT) & \
		 HINIC_MSG_HEADER_##member##_MASK)

क्रमागत hinic_mgmt_msg_type अणु
	HINIC_MGMT_MSG_SYNC = 1,
पूर्ण;

क्रमागत hinic_cfg_cmd अणु
	HINIC_CFG_NIC_CAP = 0,
पूर्ण;

क्रमागत hinic_comm_cmd अणु
	HINIC_COMM_CMD_START_FLR          = 0x1,
	HINIC_COMM_CMD_IO_STATUS_GET    = 0x3,
	HINIC_COMM_CMD_DMA_ATTR_SET	    = 0x4,

	HINIC_COMM_CMD_CMDQ_CTXT_SET    = 0x10,
	HINIC_COMM_CMD_CMDQ_CTXT_GET    = 0x11,

	HINIC_COMM_CMD_HWCTXT_SET       = 0x12,
	HINIC_COMM_CMD_HWCTXT_GET       = 0x13,

	HINIC_COMM_CMD_SQ_HI_CI_SET     = 0x14,

	HINIC_COMM_CMD_RES_STATE_SET    = 0x24,

	HINIC_COMM_CMD_IO_RES_CLEAR     = 0x29,

	HINIC_COMM_CMD_CEQ_CTRL_REG_WR_BY_UP = 0x33,

	HINIC_COMM_CMD_MSI_CTRL_REG_WR_BY_UP,
	HINIC_COMM_CMD_MSI_CTRL_REG_RD_BY_UP,

	HINIC_COMM_CMD_FAULT_REPORT	= 0x37,

	HINIC_COMM_CMD_SET_LED_STATUS	= 0x4a,

	HINIC_COMM_CMD_L2NIC_RESET	= 0x4b,

	HINIC_COMM_CMD_PAGESIZE_SET	= 0x50,

	HINIC_COMM_CMD_GET_BOARD_INFO	= 0x52,

	HINIC_COMM_CMD_WATCHDOG_INFO	= 0x56,

	HINIC_MGMT_CMD_SET_VF_RANDOM_ID = 0x61,

	HINIC_COMM_CMD_MAX,
पूर्ण;

क्रमागत hinic_mgmt_cb_state अणु
	HINIC_MGMT_CB_ENABLED = BIT(0),
	HINIC_MGMT_CB_RUNNING = BIT(1),
पूर्ण;

काष्ठा hinic_recv_msg अणु
	u8                      *msg;
	u8                      *buf_out;

	काष्ठा completion       recv_करोne;

	u16                     cmd;
	क्रमागत hinic_mod_type     mod;
	पूर्णांक                     async_mgmt_to_pf;

	u16                     msg_len;
	u16                     msg_id;
पूर्ण;

काष्ठा hinic_mgmt_cb अणु
	व्योम    (*cb)(व्योम *handle, u8 cmd,
		      व्योम *buf_in, u16 in_size,
		      व्योम *buf_out, u16 *out_size);

	व्योम            *handle;
	अचिन्हित दीर्घ   state;
पूर्ण;

काष्ठा hinic_pf_to_mgmt अणु
	काष्ठा hinic_hwअगर               *hwअगर;
	काष्ठा hinic_hwdev		*hwdev;
	काष्ठा semaphore                sync_msg_lock;
	u16                             sync_msg_id;
	u8                              *sync_msg_buf;
	व्योम				*mgmt_ack_buf;

	काष्ठा hinic_recv_msg           recv_resp_msg_from_mgmt;
	काष्ठा hinic_recv_msg           recv_msg_from_mgmt;

	काष्ठा hinic_api_cmd_chain      *cmd_chain[HINIC_API_CMD_MAX];

	काष्ठा hinic_mgmt_cb            mgmt_cb[HINIC_MOD_MAX];

	काष्ठा workqueue_काष्ठा		*workq;
पूर्ण;

काष्ठा hinic_mgmt_msg_handle_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा hinic_pf_to_mgmt *pf_to_mgmt;

	व्योम			*msg;
	u16			msg_len;

	क्रमागत hinic_mod_type	mod;
	u8			cmd;
	u16			msg_id;
	पूर्णांक			async_mgmt_to_pf;
पूर्ण;

व्योम hinic_रेजिस्टर_mgmt_msg_cb(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
				क्रमागत hinic_mod_type mod,
				व्योम *handle,
				व्योम (*callback)(व्योम *handle,
						 u8 cmd, व्योम *buf_in,
						 u16 in_size, व्योम *buf_out,
						 u16 *out_size));

व्योम hinic_unरेजिस्टर_mgmt_msg_cb(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
				  क्रमागत hinic_mod_type mod);

पूर्णांक hinic_msg_to_mgmt(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
		      क्रमागत hinic_mod_type mod, u8 cmd,
		      व्योम *buf_in, u16 in_size, व्योम *buf_out, u16 *out_size,
		      क्रमागत hinic_mgmt_msg_type sync);

पूर्णांक hinic_pf_to_mgmt_init(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
			  काष्ठा hinic_hwअगर *hwअगर);

व्योम hinic_pf_to_mgmt_मुक्त(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt);

#पूर्ण_अगर
