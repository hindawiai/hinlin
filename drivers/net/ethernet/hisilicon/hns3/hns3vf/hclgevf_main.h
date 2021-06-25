<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2016-2017 Hisilicon Limited. */

#अगर_अघोषित __HCLGEVF_MAIN_H
#घोषणा __HCLGEVF_MAIN_H
#समावेश <linux/fs.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/types.h>
#समावेश "hclge_mbx.h"
#समावेश "hclgevf_cmd.h"
#समावेश "hnae3.h"

#घोषणा HCLGEVF_MOD_VERSION "1.0"
#घोषणा HCLGEVF_DRIVER_NAME "hclgevf"

#घोषणा HCLGEVF_MAX_VLAN_ID	4095
#घोषणा HCLGEVF_MISC_VECTOR_NUM		0

#घोषणा HCLGEVF_INVALID_VPORT		0xffff
#घोषणा HCLGEVF_GENERAL_TASK_INTERVAL	  5
#घोषणा HCLGEVF_KEEP_ALIVE_TASK_INTERVAL  2

/* This number in actual depends upon the total number of VFs
 * created by physical function. But the maximum number of
 * possible vector-per-VF is अणुVFn(1-32), VECTn(32 + 1)पूर्ण.
 */
#घोषणा HCLGEVF_MAX_VF_VECTOR_NUM	(32 + 1)

#घोषणा HCLGEVF_VECTOR_REG_BASE		0x20000
#घोषणा HCLGEVF_MISC_VECTOR_REG_BASE	0x20400
#घोषणा HCLGEVF_VECTOR_REG_OFFSET	0x4
#घोषणा HCLGEVF_VECTOR_VF_OFFSET		0x100000

/* bar रेजिस्टरs क्रम cmdq */
#घोषणा HCLGEVF_CMDQ_TX_ADDR_L_REG		0x27000
#घोषणा HCLGEVF_CMDQ_TX_ADDR_H_REG		0x27004
#घोषणा HCLGEVF_CMDQ_TX_DEPTH_REG		0x27008
#घोषणा HCLGEVF_CMDQ_TX_TAIL_REG		0x27010
#घोषणा HCLGEVF_CMDQ_TX_HEAD_REG		0x27014
#घोषणा HCLGEVF_CMDQ_RX_ADDR_L_REG		0x27018
#घोषणा HCLGEVF_CMDQ_RX_ADDR_H_REG		0x2701C
#घोषणा HCLGEVF_CMDQ_RX_DEPTH_REG		0x27020
#घोषणा HCLGEVF_CMDQ_RX_TAIL_REG		0x27024
#घोषणा HCLGEVF_CMDQ_RX_HEAD_REG		0x27028
#घोषणा HCLGEVF_CMDQ_INTR_EN_REG		0x27108
#घोषणा HCLGEVF_CMDQ_INTR_GEN_REG		0x2710C

/* bar रेजिस्टरs क्रम common func */
#घोषणा HCLGEVF_GRO_EN_REG			0x28000

/* bar रेजिस्टरs क्रम rcb */
#घोषणा HCLGEVF_RING_RX_ADDR_L_REG		0x80000
#घोषणा HCLGEVF_RING_RX_ADDR_H_REG		0x80004
#घोषणा HCLGEVF_RING_RX_BD_NUM_REG		0x80008
#घोषणा HCLGEVF_RING_RX_BD_LENGTH_REG		0x8000C
#घोषणा HCLGEVF_RING_RX_MERGE_EN_REG		0x80014
#घोषणा HCLGEVF_RING_RX_TAIL_REG		0x80018
#घोषणा HCLGEVF_RING_RX_HEAD_REG		0x8001C
#घोषणा HCLGEVF_RING_RX_FBD_NUM_REG		0x80020
#घोषणा HCLGEVF_RING_RX_OFFSET_REG		0x80024
#घोषणा HCLGEVF_RING_RX_FBD_OFFSET_REG		0x80028
#घोषणा HCLGEVF_RING_RX_STASH_REG		0x80030
#घोषणा HCLGEVF_RING_RX_BD_ERR_REG		0x80034
#घोषणा HCLGEVF_RING_TX_ADDR_L_REG		0x80040
#घोषणा HCLGEVF_RING_TX_ADDR_H_REG		0x80044
#घोषणा HCLGEVF_RING_TX_BD_NUM_REG		0x80048
#घोषणा HCLGEVF_RING_TX_PRIORITY_REG		0x8004C
#घोषणा HCLGEVF_RING_TX_TC_REG			0x80050
#घोषणा HCLGEVF_RING_TX_MERGE_EN_REG		0x80054
#घोषणा HCLGEVF_RING_TX_TAIL_REG		0x80058
#घोषणा HCLGEVF_RING_TX_HEAD_REG		0x8005C
#घोषणा HCLGEVF_RING_TX_FBD_NUM_REG		0x80060
#घोषणा HCLGEVF_RING_TX_OFFSET_REG		0x80064
#घोषणा HCLGEVF_RING_TX_EBD_NUM_REG		0x80068
#घोषणा HCLGEVF_RING_TX_EBD_OFFSET_REG		0x80070
#घोषणा HCLGEVF_RING_TX_BD_ERR_REG		0x80074
#घोषणा HCLGEVF_RING_EN_REG			0x80090

/* bar रेजिस्टरs क्रम tqp पूर्णांकerrupt */
#घोषणा HCLGEVF_TQP_INTR_CTRL_REG		0x20000
#घोषणा HCLGEVF_TQP_INTR_GL0_REG		0x20100
#घोषणा HCLGEVF_TQP_INTR_GL1_REG		0x20200
#घोषणा HCLGEVF_TQP_INTR_GL2_REG		0x20300
#घोषणा HCLGEVF_TQP_INTR_RL_REG			0x20900

/* Vector0 पूर्णांकerrupt CMDQ event source रेजिस्टर(RW) */
#घोषणा HCLGEVF_VECTOR0_CMDQ_SRC_REG	0x27100
/* Vector0 पूर्णांकerrupt CMDQ event status रेजिस्टर(RO) */
#घोषणा HCLGEVF_VECTOR0_CMDQ_STATE_REG	0x27104
/* CMDQ रेजिस्टर bits क्रम RX event(=MBX event) */
#घोषणा HCLGEVF_VECTOR0_RX_CMDQ_INT_B	1
/* RST रेजिस्टर bits क्रम RESET event */
#घोषणा HCLGEVF_VECTOR0_RST_INT_B	2

#घोषणा HCLGEVF_TQP_RESET_TRY_TIMES	10
/* Reset related Registers */
#घोषणा HCLGEVF_RST_ING			0x20C00
#घोषणा HCLGEVF_FUN_RST_ING_BIT		BIT(0)
#घोषणा HCLGEVF_GLOBAL_RST_ING_BIT	BIT(5)
#घोषणा HCLGEVF_CORE_RST_ING_BIT	BIT(6)
#घोषणा HCLGEVF_IMP_RST_ING_BIT		BIT(7)
#घोषणा HCLGEVF_RST_ING_BITS \
	(HCLGEVF_FUN_RST_ING_BIT | HCLGEVF_GLOBAL_RST_ING_BIT | \
	 HCLGEVF_CORE_RST_ING_BIT | HCLGEVF_IMP_RST_ING_BIT)

#घोषणा HCLGEVF_VF_RST_ING		0x07008
#घोषणा HCLGEVF_VF_RST_ING_BIT		BIT(16)

#घोषणा HCLGEVF_RSS_IND_TBL_SIZE		512
#घोषणा HCLGEVF_RSS_SET_BITMAP_MSK	0xffff
#घोषणा HCLGEVF_RSS_KEY_SIZE		40
#घोषणा HCLGEVF_RSS_HASH_ALGO_TOEPLITZ	0
#घोषणा HCLGEVF_RSS_HASH_ALGO_SIMPLE	1
#घोषणा HCLGEVF_RSS_HASH_ALGO_SYMMETRIC	2
#घोषणा HCLGEVF_RSS_HASH_ALGO_MASK	0xf

#घोषणा HCLGEVF_RSS_INPUT_TUPLE_OTHER	GENMASK(3, 0)
#घोषणा HCLGEVF_RSS_INPUT_TUPLE_SCTP	GENMASK(4, 0)
#घोषणा HCLGEVF_D_PORT_BIT		BIT(0)
#घोषणा HCLGEVF_S_PORT_BIT		BIT(1)
#घोषणा HCLGEVF_D_IP_BIT		BIT(2)
#घोषणा HCLGEVF_S_IP_BIT		BIT(3)
#घोषणा HCLGEVF_V_TAG_BIT		BIT(4)
#घोषणा HCLGEVF_RSS_INPUT_TUPLE_SCTP_NO_PORT	\
	(HCLGEVF_D_IP_BIT | HCLGEVF_S_IP_BIT | HCLGEVF_V_TAG_BIT)

#घोषणा HCLGEVF_MAC_MAX_FRAME		9728

#घोषणा HCLGEVF_STATS_TIMER_INTERVAL	36U

क्रमागत hclgevf_evt_cause अणु
	HCLGEVF_VECTOR0_EVENT_RST,
	HCLGEVF_VECTOR0_EVENT_MBX,
	HCLGEVF_VECTOR0_EVENT_OTHER,
पूर्ण;

/* states of hclgevf device & tasks */
क्रमागत hclgevf_states अणु
	/* device states */
	HCLGEVF_STATE_DOWN,
	HCLGEVF_STATE_DISABLED,
	HCLGEVF_STATE_IRQ_INITED,
	HCLGEVF_STATE_REMOVING,
	HCLGEVF_STATE_NIC_REGISTERED,
	HCLGEVF_STATE_ROCE_REGISTERED,
	/* task states */
	HCLGEVF_STATE_RST_SERVICE_SCHED,
	HCLGEVF_STATE_RST_HANDLING,
	HCLGEVF_STATE_MBX_SERVICE_SCHED,
	HCLGEVF_STATE_MBX_HANDLING,
	HCLGEVF_STATE_CMD_DISABLE,
	HCLGEVF_STATE_LINK_UPDATING,
	HCLGEVF_STATE_PROMISC_CHANGED,
	HCLGEVF_STATE_RST_FAIL,
	HCLGEVF_STATE_PF_PUSH_LINK_STATUS,
पूर्ण;

काष्ठा hclgevf_mac अणु
	u8 media_type;
	u8 module_type;
	u8 mac_addr[ETH_ALEN];
	पूर्णांक link;
	u8 duplex;
	u32 speed;
	u64 supported;
	u64 advertising;
पूर्ण;

काष्ठा hclgevf_hw अणु
	व्योम __iomem *io_base;
	व्योम __iomem *mem_base;
	पूर्णांक num_vec;
	काष्ठा hclgevf_cmq cmq;
	काष्ठा hclgevf_mac mac;
	व्योम *hdev; /* hchgevf device it is part of */
पूर्ण;

/* TQP stats */
काष्ठा hlcgevf_tqp_stats अणु
	/* query_tqp_tx_queue_statistics, opcode id: 0x0B03 */
	u64 rcb_tx_ring_pktnum_rcd; /* 32bit */
	/* query_tqp_rx_queue_statistics, opcode id: 0x0B13 */
	u64 rcb_rx_ring_pktnum_rcd; /* 32bit */
पूर्ण;

काष्ठा hclgevf_tqp अणु
	काष्ठा device *dev;	/* device क्रम DMA mapping */
	काष्ठा hnae3_queue q;
	काष्ठा hlcgevf_tqp_stats tqp_stats;
	u16 index;		/* global index in a NIC controller */

	bool alloced;
पूर्ण;

काष्ठा hclgevf_cfg अणु
	u8 tc_num;
	u16 tqp_desc_num;
	u16 rx_buf_len;
	u8 phy_addr;
	u8 media_type;
	u8 mac_addr[ETH_ALEN];
	u32 numa_node_map;
पूर्ण;

काष्ठा hclgevf_rss_tuple_cfg अणु
	u8 ipv4_tcp_en;
	u8 ipv4_udp_en;
	u8 ipv4_sctp_en;
	u8 ipv4_fragment_en;
	u8 ipv6_tcp_en;
	u8 ipv6_udp_en;
	u8 ipv6_sctp_en;
	u8 ipv6_fragment_en;
पूर्ण;

काष्ठा hclgevf_rss_cfg अणु
	u8  rss_hash_key[HCLGEVF_RSS_KEY_SIZE]; /* user configured hash keys */
	u32 hash_algo;
	u32 rss_size;
	u8 hw_tc_map;
	/* shaकरोw table */
	u8 *rss_indirection_tbl;
	काष्ठा hclgevf_rss_tuple_cfg rss_tuple_sets;
पूर्ण;

काष्ठा hclgevf_misc_vector अणु
	u8 __iomem *addr;
	पूर्णांक vector_irq;
	अक्षर name[HNAE3_INT_NAME_LEN];
पूर्ण;

काष्ठा hclgevf_rst_stats अणु
	u32 rst_cnt;			/* the number of reset */
	u32 vf_func_rst_cnt;		/* the number of VF function reset */
	u32 flr_rst_cnt;		/* the number of FLR */
	u32 vf_rst_cnt;			/* the number of VF reset */
	u32 rst_करोne_cnt;		/* the number of reset completed */
	u32 hw_rst_करोne_cnt;		/* the number of HW reset completed */
	u32 rst_fail_cnt;		/* the number of VF reset fail */
पूर्ण;

क्रमागत HCLGEVF_MAC_ADDR_TYPE अणु
	HCLGEVF_MAC_ADDR_UC,
	HCLGEVF_MAC_ADDR_MC
पूर्ण;

क्रमागत HCLGEVF_MAC_NODE_STATE अणु
	HCLGEVF_MAC_TO_ADD,
	HCLGEVF_MAC_TO_DEL,
	HCLGEVF_MAC_ACTIVE
पूर्ण;

काष्ठा hclgevf_mac_addr_node अणु
	काष्ठा list_head node;
	क्रमागत HCLGEVF_MAC_NODE_STATE state;
	u8 mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा hclgevf_mac_table_cfg अणु
	spinlock_t mac_list_lock; /* protect mac address need to add/detele */
	काष्ठा list_head uc_mac_list;
	काष्ठा list_head mc_mac_list;
पूर्ण;

काष्ठा hclgevf_dev अणु
	काष्ठा pci_dev *pdev;
	काष्ठा hnae3_ae_dev *ae_dev;
	काष्ठा hclgevf_hw hw;
	काष्ठा hclgevf_misc_vector misc_vector;
	काष्ठा hclgevf_rss_cfg rss_cfg;
	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ flr_state;
	अचिन्हित दीर्घ शेष_reset_request;
	अचिन्हित दीर्घ last_reset_समय;
	क्रमागत hnae3_reset_type reset_level;
	अचिन्हित दीर्घ reset_pending;
	क्रमागत hnae3_reset_type reset_type;

#घोषणा HCLGEVF_RESET_REQUESTED		0
#घोषणा HCLGEVF_RESET_PENDING		1
	अचिन्हित दीर्घ reset_state;	/* requested, pending */
	काष्ठा hclgevf_rst_stats rst_stats;
	u32 reset_attempts;
	काष्ठा semaphore reset_sem;	/* protect reset process */

	u32 fw_version;
	u16 num_tqps;		/* num task queue pairs of this VF */

	u16 alloc_rss_size;	/* allocated RSS task queue */
	u16 rss_size_max;	/* HW defined max RSS task queue */

	u16 num_alloc_vport;	/* num vports this driver supports */
	u32 numa_node_mask;
	u16 rx_buf_len;
	u16 num_tx_desc;	/* desc num of per tx queue */
	u16 num_rx_desc;	/* desc num of per rx queue */
	u8 hw_tc_map;
	u8 has_pf_mac;

	u16 num_msi;
	u16 num_msi_left;
	u16 num_msi_used;
	u16 num_nic_msix;	/* Num of nic vectors क्रम this VF */
	u16 num_roce_msix;	/* Num of roce vectors क्रम this VF */
	u16 roce_base_msix_offset;
	पूर्णांक roce_base_vector;
	u32 base_msi_vector;
	u16 *vector_status;
	पूर्णांक *vector_irq;

	अचिन्हित दीर्घ vlan_del_fail_bmap[BITS_TO_LONGS(VLAN_N_VID)];

	काष्ठा hclgevf_mac_table_cfg mac_table;

	bool mbx_event_pending;
	काष्ठा hclgevf_mbx_resp_status mbx_resp; /* mailbox response */
	काष्ठा hclgevf_mbx_arq_ring arq; /* mailbox async rx queue */

	काष्ठा delayed_work service_task;

	काष्ठा hclgevf_tqp *htqp;

	काष्ठा hnae3_handle nic;
	काष्ठा hnae3_handle roce;

	काष्ठा hnae3_client *nic_client;
	काष्ठा hnae3_client *roce_client;
	u32 flag;
	अचिन्हित दीर्घ serv_processed_cnt;
	अचिन्हित दीर्घ last_serv_processed;
पूर्ण;

अटल अंतरभूत bool hclgevf_is_reset_pending(काष्ठा hclgevf_dev *hdev)
अणु
	वापस !!hdev->reset_pending;
पूर्ण

पूर्णांक hclgevf_send_mbx_msg(काष्ठा hclgevf_dev *hdev,
			 काष्ठा hclge_vf_to_pf_msg *send_msg, bool need_resp,
			 u8 *resp_data, u16 resp_len);
व्योम hclgevf_mbx_handler(काष्ठा hclgevf_dev *hdev);
व्योम hclgevf_mbx_async_handler(काष्ठा hclgevf_dev *hdev);

व्योम hclgevf_update_link_status(काष्ठा hclgevf_dev *hdev, पूर्णांक link_state);
व्योम hclgevf_update_speed_duplex(काष्ठा hclgevf_dev *hdev, u32 speed,
				 u8 duplex);
व्योम hclgevf_reset_task_schedule(काष्ठा hclgevf_dev *hdev);
व्योम hclgevf_mbx_task_schedule(काष्ठा hclgevf_dev *hdev);
व्योम hclgevf_update_port_base_vlan_info(काष्ठा hclgevf_dev *hdev, u16 state,
					u8 *port_base_vlan_info, u8 data_size);
#पूर्ण_अगर
