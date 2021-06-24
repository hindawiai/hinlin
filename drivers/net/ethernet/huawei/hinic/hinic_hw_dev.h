<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_HW_DEV_H
#घोषणा HINIC_HW_DEV_H

#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <net/devlink.h>

#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_eqs.h"
#समावेश "hinic_hw_mgmt.h"
#समावेश "hinic_hw_qp.h"
#समावेश "hinic_hw_io.h"
#समावेश "hinic_hw_mbox.h"

#घोषणा HINIC_MAX_QPS   32

#घोषणा HINIC_MGMT_NUM_MSG_CMD  (HINIC_MGMT_MSG_CMD_MAX - \
				 HINIC_MGMT_MSG_CMD_BASE)

#घोषणा HINIC_PF_SET_VF_ALREADY				0x4
#घोषणा HINIC_MGMT_STATUS_EXIST				0x6
#घोषणा HINIC_MGMT_CMD_UNSUPPORTED			0xFF

#घोषणा HINIC_CMD_VER_FUNC_ID				2

काष्ठा hinic_cap अणु
	u16     max_qps;
	u16     num_qps;
	u8		max_vf;
	u16     max_vf_qps;
पूर्ण;

क्रमागत hw_ioctxt_set_cmdq_depth अणु
	HW_IOCTXT_SET_CMDQ_DEPTH_DEFAULT,
	HW_IOCTXT_SET_CMDQ_DEPTH_ENABLE,
पूर्ण;

क्रमागत hinic_port_cmd अणु
	HINIC_PORT_CMD_VF_REGISTER = 0x0,
	HINIC_PORT_CMD_VF_UNREGISTER = 0x1,

	HINIC_PORT_CMD_CHANGE_MTU       = 2,

	HINIC_PORT_CMD_ADD_VLAN         = 3,
	HINIC_PORT_CMD_DEL_VLAN         = 4,

	HINIC_PORT_CMD_SET_PFC		= 5,

	HINIC_PORT_CMD_SET_MAC          = 9,
	HINIC_PORT_CMD_GET_MAC          = 10,
	HINIC_PORT_CMD_DEL_MAC          = 11,

	HINIC_PORT_CMD_SET_RX_MODE      = 12,

	HINIC_PORT_CMD_GET_PAUSE_INFO	= 20,
	HINIC_PORT_CMD_SET_PAUSE_INFO	= 21,

	HINIC_PORT_CMD_GET_LINK_STATE   = 24,

	HINIC_PORT_CMD_SET_LRO		= 25,

	HINIC_PORT_CMD_SET_RX_CSUM	= 26,

	HINIC_PORT_CMD_SET_RX_VLAN_OFFLOAD = 27,

	HINIC_PORT_CMD_GET_PORT_STATISTICS = 28,

	HINIC_PORT_CMD_CLEAR_PORT_STATISTICS = 29,

	HINIC_PORT_CMD_GET_VPORT_STAT	= 30,

	HINIC_PORT_CMD_CLEAN_VPORT_STAT	= 31,

	HINIC_PORT_CMD_GET_RSS_TEMPLATE_INसूची_TBL = 37,

	HINIC_PORT_CMD_SET_PORT_STATE   = 41,

	HINIC_PORT_CMD_SET_RSS_TEMPLATE_TBL = 43,

	HINIC_PORT_CMD_GET_RSS_TEMPLATE_TBL = 44,

	HINIC_PORT_CMD_SET_RSS_HASH_ENGINE = 45,

	HINIC_PORT_CMD_GET_RSS_HASH_ENGINE = 46,

	HINIC_PORT_CMD_GET_RSS_CTX_TBL  = 47,

	HINIC_PORT_CMD_SET_RSS_CTX_TBL  = 48,

	HINIC_PORT_CMD_RSS_TEMP_MGR	= 49,

	HINIC_PORT_CMD_RD_LINE_TBL	= 57,

	HINIC_PORT_CMD_RSS_CFG		= 66,

	HINIC_PORT_CMD_FWCTXT_INIT      = 69,

	HINIC_PORT_CMD_GET_LOOPBACK_MODE = 72,
	HINIC_PORT_CMD_SET_LOOPBACK_MODE,

	HINIC_PORT_CMD_ENABLE_SPOOFCHK = 78,

	HINIC_PORT_CMD_GET_MGMT_VERSION = 88,

	HINIC_PORT_CMD_SET_FUNC_STATE   = 93,

	HINIC_PORT_CMD_GET_GLOBAL_QPN   = 102,

	HINIC_PORT_CMD_SET_VF_RATE = 105,

	HINIC_PORT_CMD_SET_VF_VLAN	= 106,

	HINIC_PORT_CMD_CLR_VF_VLAN,

	HINIC_PORT_CMD_SET_TSO          = 112,

	HINIC_PORT_CMD_UPDATE_FW	= 114,

	HINIC_PORT_CMD_SET_RQ_IQ_MAP	= 115,

	HINIC_PORT_CMD_LINK_STATUS_REPORT = 160,

	HINIC_PORT_CMD_UPDATE_MAC = 164,

	HINIC_PORT_CMD_GET_CAP          = 170,

	HINIC_PORT_CMD_GET_LINK_MODE	= 217,

	HINIC_PORT_CMD_SET_SPEED	= 218,

	HINIC_PORT_CMD_SET_AUTONEG	= 219,

	HINIC_PORT_CMD_GET_STD_SFP_INFO = 240,

	HINIC_PORT_CMD_SET_LRO_TIMER	= 244,

	HINIC_PORT_CMD_SET_VF_MAX_MIN_RATE = 249,

	HINIC_PORT_CMD_GET_SFP_ABS	= 251,
पूर्ण;

/* cmd of mgmt CPU message क्रम HILINK module */
क्रमागत hinic_hilink_cmd अणु
	HINIC_HILINK_CMD_GET_LINK_INFO		= 0x3,
	HINIC_HILINK_CMD_SET_LINK_SETTINGS	= 0x8,
पूर्ण;

क्रमागत hinic_ucode_cmd अणु
	HINIC_UCODE_CMD_MODIFY_QUEUE_CONTEXT    = 0,
	HINIC_UCODE_CMD_CLEAN_QUEUE_CONTEXT,
	HINIC_UCODE_CMD_ARM_SQ,
	HINIC_UCODE_CMD_ARM_RQ,
	HINIC_UCODE_CMD_SET_RSS_INसूची_TABLE,
	HINIC_UCODE_CMD_SET_RSS_CONTEXT_TABLE,
	HINIC_UCODE_CMD_GET_RSS_INसूची_TABLE,
	HINIC_UCODE_CMD_GET_RSS_CONTEXT_TABLE,
	HINIC_UCODE_CMD_SET_IQ_ENABLE,
	HINIC_UCODE_CMD_SET_RQ_FLUSH            = 10
पूर्ण;

#घोषणा NIC_RSS_CMD_TEMP_ALLOC  0x01
#घोषणा NIC_RSS_CMD_TEMP_FREE   0x02

क्रमागत hinic_mgmt_msg_cmd अणु
	HINIC_MGMT_MSG_CMD_BASE         = 0xA0,

	HINIC_MGMT_MSG_CMD_LINK_STATUS  = 0xA0,

	HINIC_MGMT_MSG_CMD_CABLE_PLUG_EVENT	= 0xE5,
	HINIC_MGMT_MSG_CMD_LINK_ERR_EVENT	= 0xE6,

	HINIC_MGMT_MSG_CMD_MAX,
पूर्ण;

क्रमागत hinic_cb_state अणु
	HINIC_CB_ENABLED = BIT(0),
	HINIC_CB_RUNNING = BIT(1),
पूर्ण;

क्रमागत hinic_res_state अणु
	HINIC_RES_CLEAN         = 0,
	HINIC_RES_ACTIVE        = 1,
पूर्ण;

काष्ठा hinic_cmd_fw_ctxt अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u16     rx_buf_sz;

	u32     rsvd1;
पूर्ण;

काष्ठा hinic_cmd_hw_ioctxt अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;

	u16     rsvd1;

	u8      set_cmdq_depth;
	u8      cmdq_depth;

	u8      lro_en;
	u8      rsvd3;
	u8      ppf_idx;
	u8      rsvd4;

	u16     rq_depth;
	u16     rx_buf_sz_idx;
	u16     sq_depth;
पूर्ण;

काष्ठा hinic_cmd_io_status अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u8      rsvd1;
	u8      rsvd2;
	u32     io_status;
पूर्ण;

काष्ठा hinic_cmd_clear_io_res अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u8      rsvd1;
	u8      rsvd2;
पूर्ण;

काष्ठा hinic_cmd_set_res_state अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u8      state;
	u8      rsvd1;
	u32     rsvd2;
पूर्ण;

काष्ठा hinic_ceq_ctrl_reg अणु
	u8 status;
	u8 version;
	u8 rsvd0[6];

	u16 func_id;
	u16 q_id;
	u32 ctrl0;
	u32 ctrl1;
पूर्ण;

काष्ठा hinic_cmd_base_qpn अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u16     qpn;
पूर्ण;

काष्ठा hinic_cmd_hw_ci अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;

	u8      dma_attr_off;
	u8      pending_limit;
	u8      coalesc_समयr;

	u8      msix_en;
	u16     msix_entry_idx;

	u32     sq_id;
	u32     rsvd1;
	u64     ci_addr;
पूर्ण;

काष्ठा hinic_cmd_l2nic_reset अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	reset_flag;
पूर्ण;

काष्ठा hinic_msix_config अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	msix_index;
	u8	pending_cnt;
	u8	coalesce_समयr_cnt;
	u8	lli_समयr_cnt;
	u8	lli_credit_cnt;
	u8	resend_समयr_cnt;
	u8	rsvd1[3];
पूर्ण;

काष्ठा hinic_set_अक्रमom_id अणु
	u8    status;
	u8    version;
	u8    rsvd0[6];

	u8    vf_in_pf;
	u8    rsvd1;
	u16   func_idx;
	u32   अक्रमom_id;
पूर्ण;

काष्ठा hinic_board_info अणु
	u32	board_type;
	u32	port_num;
	u32	port_speed;
	u32	pcie_width;
	u32	host_num;
	u32	pf_num;
	u32	vf_total_num;
	u32	tile_num;
	u32	qcm_num;
	u32	core_num;
	u32	work_mode;
	u32	service_mode;
	u32	pcie_mode;
	u32	cfg_addr;
	u32	boot_sel;
	u32	board_id;
पूर्ण;

काष्ठा hinic_comm_board_info अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	काष्ठा hinic_board_info info;

	u32	rsvd1[4];
पूर्ण;

काष्ठा hinic_hwdev अणु
	काष्ठा hinic_hwअगर               *hwअगर;
	काष्ठा msix_entry               *msix_entries;

	काष्ठा hinic_aeqs               aeqs;
	काष्ठा hinic_func_to_io         func_to_io;
	काष्ठा hinic_mbox_func_to_func  *func_to_func;

	काष्ठा hinic_cap                nic_cap;
	u8				port_id;
	काष्ठा hinic_devlink_priv	*devlink_dev;
पूर्ण;

काष्ठा hinic_nic_cb अणु
	व्योम    (*handler)(व्योम *handle, व्योम *buf_in,
			   u16 in_size, व्योम *buf_out,
			   u16 *out_size);

	व्योम            *handle;
	अचिन्हित दीर्घ   cb_state;
पूर्ण;

#घोषणा HINIC_COMM_SELF_CMD_MAX 4

प्रकार व्योम (*comm_mgmt_self_msg_proc)(व्योम *handle, व्योम *buf_in, u16 in_size,
					व्योम *buf_out, u16 *out_size);

काष्ठा comm_mgmt_self_msg_sub_info अणु
	u8 cmd;
	comm_mgmt_self_msg_proc proc;
पूर्ण;

काष्ठा comm_mgmt_self_msg_info अणु
	u8 cmd_num;
	काष्ठा comm_mgmt_self_msg_sub_info info[HINIC_COMM_SELF_CMD_MAX];
पूर्ण;

काष्ठा hinic_pfhwdev अणु
	काष्ठा hinic_hwdev              hwdev;

	काष्ठा hinic_pf_to_mgmt         pf_to_mgmt;

	काष्ठा hinic_nic_cb             nic_cb[HINIC_MGMT_NUM_MSG_CMD];

	काष्ठा comm_mgmt_self_msg_info	proc;
पूर्ण;

काष्ठा hinic_dev_cap अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u8      rsvd1[5];
	u8      पूर्णांकr_type;
	u8	max_cos_id;
	u8	er_id;
	u8	port_id;
	u8      max_vf;
	u8      rsvd2[62];
	u16     max_sqs;
	u16	max_rqs;
	u16	max_vf_sqs;
	u16     max_vf_rqs;
	u8      rsvd3[204];
पूर्ण;

जोड़ hinic_fault_hw_mgmt अणु
	u32 val[4];
	/* valid only type == FAULT_TYPE_CHIP */
	काष्ठा अणु
		u8 node_id;
		u8 err_level;
		u16 err_type;
		u32 err_csr_addr;
		u32 err_csr_value;
		/* func_id valid only अगर err_level == FAULT_LEVEL_SERIOUS_FLR */
		u16 func_id;
		u16 rsvd2;
	पूर्ण chip;

	/* valid only अगर type == FAULT_TYPE_UCODE */
	काष्ठा अणु
		u8 cause_id;
		u8 core_id;
		u8 c_id;
		u8 rsvd3;
		u32 epc;
		u32 rsvd4;
		u32 rsvd5;
	पूर्ण ucode;

	/* valid only अगर type == FAULT_TYPE_MEM_RD_TIMEOUT ||
	 * FAULT_TYPE_MEM_WR_TIMEOUT
	 */
	काष्ठा अणु
		u32 err_csr_ctrl;
		u32 err_csr_data;
		u32 ctrl_tab;
		u32 mem_index;
	पूर्ण mem_समयout;

	/* valid only अगर type == FAULT_TYPE_REG_RD_TIMEOUT ||
	 * FAULT_TYPE_REG_WR_TIMEOUT
	 */
	काष्ठा अणु
		u32 err_csr;
		u32 rsvd6;
		u32 rsvd7;
		u32 rsvd8;
	पूर्ण reg_समयout;

	काष्ठा अणु
		/* 0: पढ़ो; 1: ग_लिखो */
		u8 op_type;
		u8 port_id;
		u8 dev_ad;
		u8 rsvd9;
		u32 csr_addr;
		u32 op_data;
		u32 rsvd10;
	पूर्ण phy_fault;
पूर्ण;

काष्ठा hinic_fault_event अणु
	u8 type;
	u8 fault_level;
	u8 rsvd0[2];
	जोड़ hinic_fault_hw_mgmt event;
पूर्ण;

काष्ठा hinic_cmd_fault_event अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	काष्ठा hinic_fault_event event;
पूर्ण;

क्रमागत hinic_fault_type अणु
	FAULT_TYPE_CHIP,
	FAULT_TYPE_UCODE,
	FAULT_TYPE_MEM_RD_TIMEOUT,
	FAULT_TYPE_MEM_WR_TIMEOUT,
	FAULT_TYPE_REG_RD_TIMEOUT,
	FAULT_TYPE_REG_WR_TIMEOUT,
	FAULT_TYPE_PHY_FAULT,
	FAULT_TYPE_MAX,
पूर्ण;

क्रमागत hinic_fault_err_level अणु
	FAULT_LEVEL_FATAL,
	FAULT_LEVEL_SERIOUS_RESET,
	FAULT_LEVEL_SERIOUS_FLR,
	FAULT_LEVEL_GENERAL,
	FAULT_LEVEL_SUGGESTION,
	FAULT_LEVEL_MAX
पूर्ण;

काष्ठा hinic_mgmt_watchकरोg_info अणु
	u8 status;
	u8 version;
	u8 rsvd0[6];

	u32 curr_समय_h;
	u32 curr_समय_l;
	u32 task_id;
	u32 rsv;

	u32 reg[13];
	u32 pc;
	u32 lr;
	u32 cpsr;

	u32 stack_top;
	u32 stack_bottom;
	u32 sp;
	u32 curr_used;
	u32 peak_used;
	u32 is_overflow;

	u32 stack_actlen;
	u8 data[1024];
पूर्ण;

व्योम hinic_hwdev_cb_रेजिस्टर(काष्ठा hinic_hwdev *hwdev,
			     क्रमागत hinic_mgmt_msg_cmd cmd, व्योम *handle,
			     व्योम (*handler)(व्योम *handle, व्योम *buf_in,
					     u16 in_size, व्योम *buf_out,
					     u16 *out_size));

व्योम hinic_hwdev_cb_unरेजिस्टर(काष्ठा hinic_hwdev *hwdev,
			       क्रमागत hinic_mgmt_msg_cmd cmd);

पूर्णांक hinic_port_msg_cmd(काष्ठा hinic_hwdev *hwdev, क्रमागत hinic_port_cmd cmd,
		       व्योम *buf_in, u16 in_size, व्योम *buf_out,
		       u16 *out_size);

पूर्णांक hinic_hilink_msg_cmd(काष्ठा hinic_hwdev *hwdev, क्रमागत hinic_hilink_cmd cmd,
			 व्योम *buf_in, u16 in_size, व्योम *buf_out,
			 u16 *out_size);

पूर्णांक hinic_hwdev_अगरup(काष्ठा hinic_hwdev *hwdev, u16 sq_depth, u16 rq_depth);

व्योम hinic_hwdev_अगरकरोwn(काष्ठा hinic_hwdev *hwdev);

काष्ठा hinic_hwdev *hinic_init_hwdev(काष्ठा pci_dev *pdev, काष्ठा devlink *devlink);

व्योम hinic_मुक्त_hwdev(काष्ठा hinic_hwdev *hwdev);

पूर्णांक hinic_hwdev_max_num_qps(काष्ठा hinic_hwdev *hwdev);

पूर्णांक hinic_hwdev_num_qps(काष्ठा hinic_hwdev *hwdev);

काष्ठा hinic_sq *hinic_hwdev_get_sq(काष्ठा hinic_hwdev *hwdev, पूर्णांक i);

काष्ठा hinic_rq *hinic_hwdev_get_rq(काष्ठा hinic_hwdev *hwdev, पूर्णांक i);

पूर्णांक hinic_hwdev_msix_cnt_set(काष्ठा hinic_hwdev *hwdev, u16 msix_index);

पूर्णांक hinic_hwdev_msix_set(काष्ठा hinic_hwdev *hwdev, u16 msix_index,
			 u8 pending_limit, u8 coalesc_समयr,
			 u8 lli_समयr_cfg, u8 lli_credit_limit,
			 u8 resend_समयr);

पूर्णांक hinic_hwdev_hw_ci_addr_set(काष्ठा hinic_hwdev *hwdev, काष्ठा hinic_sq *sq,
			       u8 pending_limit, u8 coalesc_समयr);

व्योम hinic_hwdev_set_msix_state(काष्ठा hinic_hwdev *hwdev, u16 msix_index,
				क्रमागत hinic_msix_state flag);

पूर्णांक hinic_get_पूर्णांकerrupt_cfg(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_msix_config *पूर्णांकerrupt_info);

पूर्णांक hinic_set_पूर्णांकerrupt_cfg(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_msix_config *पूर्णांकerrupt_info);

पूर्णांक hinic_get_board_info(काष्ठा hinic_hwdev *hwdev,
			 काष्ठा hinic_comm_board_info *board_info);

#पूर्ण_अगर
