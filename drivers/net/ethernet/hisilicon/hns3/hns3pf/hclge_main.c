<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/crash_dump.h>
#समावेश <net/ipv6.h>
#समावेश <net/rtnetlink.h>
#समावेश "hclge_cmd.h"
#समावेश "hclge_dcb.h"
#समावेश "hclge_main.h"
#समावेश "hclge_mbx.h"
#समावेश "hclge_mdio.h"
#समावेश "hclge_tm.h"
#समावेश "hclge_err.h"
#समावेश "hnae3.h"

#घोषणा HCLGE_NAME			"hclge"
#घोषणा HCLGE_STATS_READ(p, offset) (*(u64 *)((u8 *)(p) + (offset)))
#घोषणा HCLGE_MAC_STATS_FIELD_OFF(f) (दुरत्व(काष्ठा hclge_mac_stats, f))

#घोषणा HCLGE_BUF_SIZE_UNIT	256U
#घोषणा HCLGE_BUF_MUL_BY	2
#घोषणा HCLGE_BUF_DIV_BY	2
#घोषणा NEED_RESERVE_TC_NUM	2
#घोषणा BUF_MAX_PERCENT		100
#घोषणा BUF_RESERVE_PERCENT	90

#घोषणा HCLGE_RESET_MAX_FAIL_CNT	5
#घोषणा HCLGE_RESET_SYNC_TIME		100
#घोषणा HCLGE_PF_RESET_SYNC_TIME	20
#घोषणा HCLGE_PF_RESET_SYNC_CNT		1500

/* Get DFX BD number offset */
#घोषणा HCLGE_DFX_BIOS_BD_OFFSET        1
#घोषणा HCLGE_DFX_SSU_0_BD_OFFSET       2
#घोषणा HCLGE_DFX_SSU_1_BD_OFFSET       3
#घोषणा HCLGE_DFX_IGU_BD_OFFSET         4
#घोषणा HCLGE_DFX_RPU_0_BD_OFFSET       5
#घोषणा HCLGE_DFX_RPU_1_BD_OFFSET       6
#घोषणा HCLGE_DFX_NCSI_BD_OFFSET        7
#घोषणा HCLGE_DFX_RTC_BD_OFFSET         8
#घोषणा HCLGE_DFX_PPP_BD_OFFSET         9
#घोषणा HCLGE_DFX_RCB_BD_OFFSET         10
#घोषणा HCLGE_DFX_TQP_BD_OFFSET         11
#घोषणा HCLGE_DFX_SSU_2_BD_OFFSET       12

#घोषणा HCLGE_LINK_STATUS_MS	10

अटल पूर्णांक hclge_set_mac_mtu(काष्ठा hclge_dev *hdev, पूर्णांक new_mps);
अटल पूर्णांक hclge_init_vlan_config(काष्ठा hclge_dev *hdev);
अटल व्योम hclge_sync_vlan_filter(काष्ठा hclge_dev *hdev);
अटल पूर्णांक hclge_reset_ae_dev(काष्ठा hnae3_ae_dev *ae_dev);
अटल bool hclge_get_hw_reset_stat(काष्ठा hnae3_handle *handle);
अटल व्योम hclge_rfs_filter_expire(काष्ठा hclge_dev *hdev);
अटल पूर्णांक hclge_clear_arfs_rules(काष्ठा hclge_dev *hdev);
अटल क्रमागत hnae3_reset_type hclge_get_reset_level(काष्ठा hnae3_ae_dev *ae_dev,
						   अचिन्हित दीर्घ *addr);
अटल पूर्णांक hclge_set_शेष_loopback(काष्ठा hclge_dev *hdev);

अटल व्योम hclge_sync_mac_table(काष्ठा hclge_dev *hdev);
अटल व्योम hclge_restore_hw_table(काष्ठा hclge_dev *hdev);
अटल व्योम hclge_sync_promisc_mode(काष्ठा hclge_dev *hdev);
अटल व्योम hclge_sync_fd_table(काष्ठा hclge_dev *hdev);

अटल काष्ठा hnae3_ae_algo ae_algo;

अटल काष्ठा workqueue_काष्ठा *hclge_wq;

अटल स्थिर काष्ठा pci_device_id ae_algo_pci_tbl[] = अणु
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_GE), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_25GE), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_25GE_RDMA), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_25GE_RDMA_MACSEC), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_50GE_RDMA), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_50GE_RDMA_MACSEC), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_100G_RDMA_MACSEC), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_200G_RDMA), 0पूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ae_algo_pci_tbl);

अटल स्थिर u32 cmdq_reg_addr_list[] = अणुHCLGE_CMDQ_TX_ADDR_L_REG,
					 HCLGE_CMDQ_TX_ADDR_H_REG,
					 HCLGE_CMDQ_TX_DEPTH_REG,
					 HCLGE_CMDQ_TX_TAIL_REG,
					 HCLGE_CMDQ_TX_HEAD_REG,
					 HCLGE_CMDQ_RX_ADDR_L_REG,
					 HCLGE_CMDQ_RX_ADDR_H_REG,
					 HCLGE_CMDQ_RX_DEPTH_REG,
					 HCLGE_CMDQ_RX_TAIL_REG,
					 HCLGE_CMDQ_RX_HEAD_REG,
					 HCLGE_VECTOR0_CMDQ_SRC_REG,
					 HCLGE_CMDQ_INTR_STS_REG,
					 HCLGE_CMDQ_INTR_EN_REG,
					 HCLGE_CMDQ_INTR_GEN_REGपूर्ण;

अटल स्थिर u32 common_reg_addr_list[] = अणुHCLGE_MISC_VECTOR_REG_BASE,
					   HCLGE_VECTOR0_OTER_EN_REG,
					   HCLGE_MISC_RESET_STS_REG,
					   HCLGE_MISC_VECTOR_INT_STS,
					   HCLGE_GLOBAL_RESET_REG,
					   HCLGE_FUN_RST_ING,
					   HCLGE_GRO_EN_REGपूर्ण;

अटल स्थिर u32 ring_reg_addr_list[] = अणुHCLGE_RING_RX_ADDR_L_REG,
					 HCLGE_RING_RX_ADDR_H_REG,
					 HCLGE_RING_RX_BD_NUM_REG,
					 HCLGE_RING_RX_BD_LENGTH_REG,
					 HCLGE_RING_RX_MERGE_EN_REG,
					 HCLGE_RING_RX_TAIL_REG,
					 HCLGE_RING_RX_HEAD_REG,
					 HCLGE_RING_RX_FBD_NUM_REG,
					 HCLGE_RING_RX_OFFSET_REG,
					 HCLGE_RING_RX_FBD_OFFSET_REG,
					 HCLGE_RING_RX_STASH_REG,
					 HCLGE_RING_RX_BD_ERR_REG,
					 HCLGE_RING_TX_ADDR_L_REG,
					 HCLGE_RING_TX_ADDR_H_REG,
					 HCLGE_RING_TX_BD_NUM_REG,
					 HCLGE_RING_TX_PRIORITY_REG,
					 HCLGE_RING_TX_TC_REG,
					 HCLGE_RING_TX_MERGE_EN_REG,
					 HCLGE_RING_TX_TAIL_REG,
					 HCLGE_RING_TX_HEAD_REG,
					 HCLGE_RING_TX_FBD_NUM_REG,
					 HCLGE_RING_TX_OFFSET_REG,
					 HCLGE_RING_TX_EBD_NUM_REG,
					 HCLGE_RING_TX_EBD_OFFSET_REG,
					 HCLGE_RING_TX_BD_ERR_REG,
					 HCLGE_RING_EN_REGपूर्ण;

अटल स्थिर u32 tqp_पूर्णांकr_reg_addr_list[] = अणुHCLGE_TQP_INTR_CTRL_REG,
					     HCLGE_TQP_INTR_GL0_REG,
					     HCLGE_TQP_INTR_GL1_REG,
					     HCLGE_TQP_INTR_GL2_REG,
					     HCLGE_TQP_INTR_RL_REGपूर्ण;

अटल स्थिर अक्षर hns3_nic_test_strs[][ETH_GSTRING_LEN] = अणु
	"App    Loopback test",
	"Serdes serial Loopback test",
	"Serdes parallel Loopback test",
	"Phy    Loopback test"
पूर्ण;

अटल स्थिर काष्ठा hclge_comm_stats_str g_mac_stats_string[] = अणु
	अणु"mac_tx_mac_pause_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_mac_छोड़ो_num)पूर्ण,
	अणु"mac_rx_mac_pause_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_mac_छोड़ो_num)पूर्ण,
	अणु"mac_tx_control_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_ctrl_pkt_num)पूर्ण,
	अणु"mac_rx_control_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_ctrl_pkt_num)पूर्ण,
	अणु"mac_tx_pfc_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_pfc_छोड़ो_pkt_num)पूर्ण,
	अणु"mac_tx_pfc_pri0_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_pfc_pri0_pkt_num)पूर्ण,
	अणु"mac_tx_pfc_pri1_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_pfc_pri1_pkt_num)पूर्ण,
	अणु"mac_tx_pfc_pri2_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_pfc_pri2_pkt_num)पूर्ण,
	अणु"mac_tx_pfc_pri3_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_pfc_pri3_pkt_num)पूर्ण,
	अणु"mac_tx_pfc_pri4_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_pfc_pri4_pkt_num)पूर्ण,
	अणु"mac_tx_pfc_pri5_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_pfc_pri5_pkt_num)पूर्ण,
	अणु"mac_tx_pfc_pri6_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_pfc_pri6_pkt_num)पूर्ण,
	अणु"mac_tx_pfc_pri7_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_pfc_pri7_pkt_num)पूर्ण,
	अणु"mac_rx_pfc_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_pfc_छोड़ो_pkt_num)पूर्ण,
	अणु"mac_rx_pfc_pri0_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_pfc_pri0_pkt_num)पूर्ण,
	अणु"mac_rx_pfc_pri1_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_pfc_pri1_pkt_num)पूर्ण,
	अणु"mac_rx_pfc_pri2_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_pfc_pri2_pkt_num)पूर्ण,
	अणु"mac_rx_pfc_pri3_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_pfc_pri3_pkt_num)पूर्ण,
	अणु"mac_rx_pfc_pri4_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_pfc_pri4_pkt_num)पूर्ण,
	अणु"mac_rx_pfc_pri5_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_pfc_pri5_pkt_num)पूर्ण,
	अणु"mac_rx_pfc_pri6_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_pfc_pri6_pkt_num)पूर्ण,
	अणु"mac_rx_pfc_pri7_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_pfc_pri7_pkt_num)पूर्ण,
	अणु"mac_tx_total_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_total_pkt_num)पूर्ण,
	अणु"mac_tx_total_oct_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_total_oct_num)पूर्ण,
	अणु"mac_tx_good_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_good_pkt_num)पूर्ण,
	अणु"mac_tx_bad_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_bad_pkt_num)पूर्ण,
	अणु"mac_tx_good_oct_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_good_oct_num)पूर्ण,
	अणु"mac_tx_bad_oct_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_bad_oct_num)पूर्ण,
	अणु"mac_tx_uni_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_uni_pkt_num)पूर्ण,
	अणु"mac_tx_multi_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_multi_pkt_num)पूर्ण,
	अणु"mac_tx_broad_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_broad_pkt_num)पूर्ण,
	अणु"mac_tx_undersize_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_undersize_pkt_num)पूर्ण,
	अणु"mac_tx_oversize_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_oversize_pkt_num)पूर्ण,
	अणु"mac_tx_64_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_64_oct_pkt_num)पूर्ण,
	अणु"mac_tx_65_127_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_65_127_oct_pkt_num)पूर्ण,
	अणु"mac_tx_128_255_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_128_255_oct_pkt_num)पूर्ण,
	अणु"mac_tx_256_511_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_256_511_oct_pkt_num)पूर्ण,
	अणु"mac_tx_512_1023_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_512_1023_oct_pkt_num)पूर्ण,
	अणु"mac_tx_1024_1518_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_1024_1518_oct_pkt_num)पूर्ण,
	अणु"mac_tx_1519_2047_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_1519_2047_oct_pkt_num)पूर्ण,
	अणु"mac_tx_2048_4095_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_2048_4095_oct_pkt_num)पूर्ण,
	अणु"mac_tx_4096_8191_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_4096_8191_oct_pkt_num)पूर्ण,
	अणु"mac_tx_8192_9216_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_8192_9216_oct_pkt_num)पूर्ण,
	अणु"mac_tx_9217_12287_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_9217_12287_oct_pkt_num)पूर्ण,
	अणु"mac_tx_12288_16383_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_12288_16383_oct_pkt_num)पूर्ण,
	अणु"mac_tx_1519_max_good_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_1519_max_good_oct_pkt_num)पूर्ण,
	अणु"mac_tx_1519_max_bad_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_1519_max_bad_oct_pkt_num)पूर्ण,
	अणु"mac_rx_total_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_total_pkt_num)पूर्ण,
	अणु"mac_rx_total_oct_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_total_oct_num)पूर्ण,
	अणु"mac_rx_good_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_good_pkt_num)पूर्ण,
	अणु"mac_rx_bad_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_bad_pkt_num)पूर्ण,
	अणु"mac_rx_good_oct_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_good_oct_num)पूर्ण,
	अणु"mac_rx_bad_oct_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_bad_oct_num)पूर्ण,
	अणु"mac_rx_uni_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_uni_pkt_num)पूर्ण,
	अणु"mac_rx_multi_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_multi_pkt_num)पूर्ण,
	अणु"mac_rx_broad_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_broad_pkt_num)पूर्ण,
	अणु"mac_rx_undersize_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_undersize_pkt_num)पूर्ण,
	अणु"mac_rx_oversize_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_oversize_pkt_num)पूर्ण,
	अणु"mac_rx_64_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_64_oct_pkt_num)पूर्ण,
	अणु"mac_rx_65_127_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_65_127_oct_pkt_num)पूर्ण,
	अणु"mac_rx_128_255_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_128_255_oct_pkt_num)पूर्ण,
	अणु"mac_rx_256_511_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_256_511_oct_pkt_num)पूर्ण,
	अणु"mac_rx_512_1023_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_512_1023_oct_pkt_num)पूर्ण,
	अणु"mac_rx_1024_1518_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_1024_1518_oct_pkt_num)पूर्ण,
	अणु"mac_rx_1519_2047_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_1519_2047_oct_pkt_num)पूर्ण,
	अणु"mac_rx_2048_4095_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_2048_4095_oct_pkt_num)पूर्ण,
	अणु"mac_rx_4096_8191_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_4096_8191_oct_pkt_num)पूर्ण,
	अणु"mac_rx_8192_9216_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_8192_9216_oct_pkt_num)पूर्ण,
	अणु"mac_rx_9217_12287_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_9217_12287_oct_pkt_num)पूर्ण,
	अणु"mac_rx_12288_16383_oct_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_12288_16383_oct_pkt_num)पूर्ण,
	अणु"mac_rx_1519_max_good_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_1519_max_good_oct_pkt_num)पूर्ण,
	अणु"mac_rx_1519_max_bad_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_1519_max_bad_oct_pkt_num)पूर्ण,

	अणु"mac_tx_fragment_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_fragment_pkt_num)पूर्ण,
	अणु"mac_tx_undermin_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_undermin_pkt_num)पूर्ण,
	अणु"mac_tx_jabber_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_jabber_pkt_num)पूर्ण,
	अणु"mac_tx_err_all_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_err_all_pkt_num)पूर्ण,
	अणु"mac_tx_from_app_good_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_from_app_good_pkt_num)पूर्ण,
	अणु"mac_tx_from_app_bad_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_tx_from_app_bad_pkt_num)पूर्ण,
	अणु"mac_rx_fragment_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_fragment_pkt_num)पूर्ण,
	अणु"mac_rx_undermin_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_undermin_pkt_num)पूर्ण,
	अणु"mac_rx_jabber_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_jabber_pkt_num)पूर्ण,
	अणु"mac_rx_fcs_err_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_fcs_err_pkt_num)पूर्ण,
	अणु"mac_rx_send_app_good_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_send_app_good_pkt_num)पूर्ण,
	अणु"mac_rx_send_app_bad_pkt_num",
		HCLGE_MAC_STATS_FIELD_OFF(mac_rx_send_app_bad_pkt_num)पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_mac_mgr_tbl_entry_cmd hclge_mgr_table[] = अणु
	अणु
		.flags = HCLGE_MAC_MGR_MASK_VLAN_B,
		.ethter_type = cpu_to_le16(ETH_P_LLDP),
		.mac_addr = अणु0x01, 0x80, 0xc2, 0x00, 0x00, 0x0eपूर्ण,
		.i_port_biपंचांगap = 0x1,
	पूर्ण,
पूर्ण;

अटल स्थिर u8 hclge_hash_key[] = अणु
	0x6D, 0x5A, 0x56, 0xDA, 0x25, 0x5B, 0x0E, 0xC2,
	0x41, 0x67, 0x25, 0x3D, 0x43, 0xA3, 0x8F, 0xB0,
	0xD0, 0xCA, 0x2B, 0xCB, 0xAE, 0x7B, 0x30, 0xB4,
	0x77, 0xCB, 0x2D, 0xA3, 0x80, 0x30, 0xF2, 0x0C,
	0x6A, 0x42, 0xB7, 0x3B, 0xBE, 0xAC, 0x01, 0xFA
पूर्ण;

अटल स्थिर u32 hclge_dfx_bd_offset_list[] = अणु
	HCLGE_DFX_BIOS_BD_OFFSET,
	HCLGE_DFX_SSU_0_BD_OFFSET,
	HCLGE_DFX_SSU_1_BD_OFFSET,
	HCLGE_DFX_IGU_BD_OFFSET,
	HCLGE_DFX_RPU_0_BD_OFFSET,
	HCLGE_DFX_RPU_1_BD_OFFSET,
	HCLGE_DFX_NCSI_BD_OFFSET,
	HCLGE_DFX_RTC_BD_OFFSET,
	HCLGE_DFX_PPP_BD_OFFSET,
	HCLGE_DFX_RCB_BD_OFFSET,
	HCLGE_DFX_TQP_BD_OFFSET,
	HCLGE_DFX_SSU_2_BD_OFFSET
पूर्ण;

अटल स्थिर क्रमागत hclge_opcode_type hclge_dfx_reg_opcode_list[] = अणु
	HCLGE_OPC_DFX_BIOS_COMMON_REG,
	HCLGE_OPC_DFX_SSU_REG_0,
	HCLGE_OPC_DFX_SSU_REG_1,
	HCLGE_OPC_DFX_IGU_EGU_REG,
	HCLGE_OPC_DFX_RPU_REG_0,
	HCLGE_OPC_DFX_RPU_REG_1,
	HCLGE_OPC_DFX_NCSI_REG,
	HCLGE_OPC_DFX_RTC_REG,
	HCLGE_OPC_DFX_PPP_REG,
	HCLGE_OPC_DFX_RCB_REG,
	HCLGE_OPC_DFX_TQP_REG,
	HCLGE_OPC_DFX_SSU_REG_2
पूर्ण;

अटल स्थिर काष्ठा key_info meta_data_key_info[] = अणु
	अणु PACKET_TYPE_ID, 6पूर्ण,
	अणु IP_FRAGEMENT, 1पूर्ण,
	अणु ROCE_TYPE, 1पूर्ण,
	अणु NEXT_KEY, 5पूर्ण,
	अणु VLAN_NUMBER, 2पूर्ण,
	अणु SRC_VPORT, 12पूर्ण,
	अणु DST_VPORT, 12पूर्ण,
	अणु TUNNEL_PACKET, 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा key_info tuple_key_info[] = अणु
	अणु OUTER_DST_MAC, 48, KEY_OPT_MAC, -1, -1 पूर्ण,
	अणु OUTER_SRC_MAC, 48, KEY_OPT_MAC, -1, -1 पूर्ण,
	अणु OUTER_VLAN_TAG_FST, 16, KEY_OPT_LE16, -1, -1 पूर्ण,
	अणु OUTER_VLAN_TAG_SEC, 16, KEY_OPT_LE16, -1, -1 पूर्ण,
	अणु OUTER_ETH_TYPE, 16, KEY_OPT_LE16, -1, -1 पूर्ण,
	अणु OUTER_L2_RSV, 16, KEY_OPT_LE16, -1, -1 पूर्ण,
	अणु OUTER_IP_TOS, 8, KEY_OPT_U8, -1, -1 पूर्ण,
	अणु OUTER_IP_PROTO, 8, KEY_OPT_U8, -1, -1 पूर्ण,
	अणु OUTER_SRC_IP, 32, KEY_OPT_IP, -1, -1 पूर्ण,
	अणु OUTER_DST_IP, 32, KEY_OPT_IP, -1, -1 पूर्ण,
	अणु OUTER_L3_RSV, 16, KEY_OPT_LE16, -1, -1 पूर्ण,
	अणु OUTER_SRC_PORT, 16, KEY_OPT_LE16, -1, -1 पूर्ण,
	अणु OUTER_DST_PORT, 16, KEY_OPT_LE16, -1, -1 पूर्ण,
	अणु OUTER_L4_RSV, 32, KEY_OPT_LE32, -1, -1 पूर्ण,
	अणु OUTER_TUN_VNI, 24, KEY_OPT_VNI, -1, -1 पूर्ण,
	अणु OUTER_TUN_FLOW_ID, 8, KEY_OPT_U8, -1, -1 पूर्ण,
	अणु INNER_DST_MAC, 48, KEY_OPT_MAC,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.dst_mac),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.dst_mac) पूर्ण,
	अणु INNER_SRC_MAC, 48, KEY_OPT_MAC,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.src_mac),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.src_mac) पूर्ण,
	अणु INNER_VLAN_TAG_FST, 16, KEY_OPT_LE16,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.vlan_tag1),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.vlan_tag1) पूर्ण,
	अणु INNER_VLAN_TAG_SEC, 16, KEY_OPT_LE16, -1, -1 पूर्ण,
	अणु INNER_ETH_TYPE, 16, KEY_OPT_LE16,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.ether_proto),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.ether_proto) पूर्ण,
	अणु INNER_L2_RSV, 16, KEY_OPT_LE16,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.l2_user_def),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.l2_user_def) पूर्ण,
	अणु INNER_IP_TOS, 8, KEY_OPT_U8,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.ip_tos),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.ip_tos) पूर्ण,
	अणु INNER_IP_PROTO, 8, KEY_OPT_U8,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.ip_proto),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.ip_proto) पूर्ण,
	अणु INNER_SRC_IP, 32, KEY_OPT_IP,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.src_ip),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.src_ip) पूर्ण,
	अणु INNER_DST_IP, 32, KEY_OPT_IP,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.dst_ip),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.dst_ip) पूर्ण,
	अणु INNER_L3_RSV, 16, KEY_OPT_LE16,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.l3_user_def),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.l3_user_def) पूर्ण,
	अणु INNER_SRC_PORT, 16, KEY_OPT_LE16,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.src_port),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.src_port) पूर्ण,
	अणु INNER_DST_PORT, 16, KEY_OPT_LE16,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.dst_port),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.dst_port) पूर्ण,
	अणु INNER_L4_RSV, 32, KEY_OPT_LE32,
	  दुरत्व(काष्ठा hclge_fd_rule, tuples.l4_user_def),
	  दुरत्व(काष्ठा hclge_fd_rule, tuples_mask.l4_user_def) पूर्ण,
पूर्ण;

अटल पूर्णांक hclge_mac_update_stats_defective(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_MAC_CMD_NUM 21

	u64 *data = (u64 *)(&hdev->mac_stats);
	काष्ठा hclge_desc desc[HCLGE_MAC_CMD_NUM];
	__le64 *desc_data;
	पूर्णांक i, k, n;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_STATS_MAC, true);
	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_MAC_CMD_NUM);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get MAC pkt stats fail, status = %d.\n", ret);

		वापस ret;
	पूर्ण

	क्रम (i = 0; i < HCLGE_MAC_CMD_NUM; i++) अणु
		/* क्रम special opcode 0032, only the first desc has the head */
		अगर (unlikely(i == 0)) अणु
			desc_data = (__le64 *)(&desc[i].data[0]);
			n = HCLGE_RD_FIRST_STATS_NUM;
		पूर्ण अन्यथा अणु
			desc_data = (__le64 *)(&desc[i]);
			n = HCLGE_RD_OTHER_STATS_NUM;
		पूर्ण

		क्रम (k = 0; k < n; k++) अणु
			*data += le64_to_cpu(*desc_data);
			data++;
			desc_data++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_mac_update_stats_complete(काष्ठा hclge_dev *hdev, u32 desc_num)
अणु
	u64 *data = (u64 *)(&hdev->mac_stats);
	काष्ठा hclge_desc *desc;
	__le64 *desc_data;
	u16 i, k, n;
	पूर्णांक ret;

	/* This may be called inside atomic sections,
	 * so GFP_ATOMIC is more suitalbe here
	 */
	desc = kसुस्मृति(desc_num, माप(काष्ठा hclge_desc), GFP_ATOMIC);
	अगर (!desc)
		वापस -ENOMEM;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_STATS_MAC_ALL, true);
	ret = hclge_cmd_send(&hdev->hw, desc, desc_num);
	अगर (ret) अणु
		kमुक्त(desc);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < desc_num; i++) अणु
		/* क्रम special opcode 0034, only the first desc has the head */
		अगर (i == 0) अणु
			desc_data = (__le64 *)(&desc[i].data[0]);
			n = HCLGE_RD_FIRST_STATS_NUM;
		पूर्ण अन्यथा अणु
			desc_data = (__le64 *)(&desc[i]);
			n = HCLGE_RD_OTHER_STATS_NUM;
		पूर्ण

		क्रम (k = 0; k < n; k++) अणु
			*data += le64_to_cpu(*desc_data);
			data++;
			desc_data++;
		पूर्ण
	पूर्ण

	kमुक्त(desc);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_mac_query_reg_num(काष्ठा hclge_dev *hdev, u32 *desc_num)
अणु
	काष्ठा hclge_desc desc;
	__le32 *desc_data;
	u32 reg_num;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_MAC_REG_NUM, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		वापस ret;

	desc_data = (__le32 *)(&desc.data[0]);
	reg_num = le32_to_cpu(*desc_data);

	*desc_num = 1 + ((reg_num - 3) >> 2) +
		    (u32)(((reg_num - 3) & 0x3) ? 1 : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_mac_update_stats(काष्ठा hclge_dev *hdev)
अणु
	u32 desc_num;
	पूर्णांक ret;

	ret = hclge_mac_query_reg_num(hdev, &desc_num);
	/* The firmware supports the new statistics acquisition method */
	अगर (!ret)
		ret = hclge_mac_update_stats_complete(hdev, desc_num);
	अन्यथा अगर (ret == -EOPNOTSUPP)
		ret = hclge_mac_update_stats_defective(hdev);
	अन्यथा
		dev_err(&hdev->pdev->dev, "query mac reg num fail!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_tqps_update_stats(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hnae3_queue *queue;
	काष्ठा hclge_desc desc[1];
	काष्ठा hclge_tqp *tqp;
	पूर्णांक ret, i;

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		queue = handle->kinfo.tqp[i];
		tqp = container_of(queue, काष्ठा hclge_tqp, q);
		/* command : HCLGE_OPC_QUERY_IGU_STAT */
		hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_QUERY_RX_STATS,
					   true);

		desc[0].data[0] = cpu_to_le32(tqp->index);
		ret = hclge_cmd_send(&hdev->hw, desc, 1);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"Query tqp stat fail, status = %d,queue = %d\n",
				ret, i);
			वापस ret;
		पूर्ण
		tqp->tqp_stats.rcb_rx_ring_pktnum_rcd +=
			le32_to_cpu(desc[0].data[1]);
	पूर्ण

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		queue = handle->kinfo.tqp[i];
		tqp = container_of(queue, काष्ठा hclge_tqp, q);
		/* command : HCLGE_OPC_QUERY_IGU_STAT */
		hclge_cmd_setup_basic_desc(&desc[0],
					   HCLGE_OPC_QUERY_TX_STATS,
					   true);

		desc[0].data[0] = cpu_to_le32(tqp->index);
		ret = hclge_cmd_send(&hdev->hw, desc, 1);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"Query tqp stat fail, status = %d,queue = %d\n",
				ret, i);
			वापस ret;
		पूर्ण
		tqp->tqp_stats.rcb_tx_ring_pktnum_rcd +=
			le32_to_cpu(desc[0].data[1]);
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 *hclge_tqps_get_stats(काष्ठा hnae3_handle *handle, u64 *data)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hclge_tqp *tqp;
	u64 *buff = data;
	पूर्णांक i;

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		tqp = container_of(kinfo->tqp[i], काष्ठा hclge_tqp, q);
		*buff++ = tqp->tqp_stats.rcb_tx_ring_pktnum_rcd;
	पूर्ण

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		tqp = container_of(kinfo->tqp[i], काष्ठा hclge_tqp, q);
		*buff++ = tqp->tqp_stats.rcb_rx_ring_pktnum_rcd;
	पूर्ण

	वापस buff;
पूर्ण

अटल पूर्णांक hclge_tqps_get_sset_count(काष्ठा hnae3_handle *handle, पूर्णांक stringset)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;

	/* each tqp has TX & RX two queues */
	वापस kinfo->num_tqps * (2);
पूर्ण

अटल u8 *hclge_tqps_get_strings(काष्ठा hnae3_handle *handle, u8 *data)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	u8 *buff = data;
	पूर्णांक i;

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		काष्ठा hclge_tqp *tqp = container_of(handle->kinfo.tqp[i],
			काष्ठा hclge_tqp, q);
		snम_लिखो(buff, ETH_GSTRING_LEN, "txq%u_pktnum_rcd",
			 tqp->index);
		buff = buff + ETH_GSTRING_LEN;
	पूर्ण

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		काष्ठा hclge_tqp *tqp = container_of(kinfo->tqp[i],
			काष्ठा hclge_tqp, q);
		snम_लिखो(buff, ETH_GSTRING_LEN, "rxq%u_pktnum_rcd",
			 tqp->index);
		buff = buff + ETH_GSTRING_LEN;
	पूर्ण

	वापस buff;
पूर्ण

अटल u64 *hclge_comm_get_stats(स्थिर व्योम *comm_stats,
				 स्थिर काष्ठा hclge_comm_stats_str strs[],
				 पूर्णांक size, u64 *data)
अणु
	u64 *buf = data;
	u32 i;

	क्रम (i = 0; i < size; i++)
		buf[i] = HCLGE_STATS_READ(comm_stats, strs[i].offset);

	वापस buf + size;
पूर्ण

अटल u8 *hclge_comm_get_strings(u32 stringset,
				  स्थिर काष्ठा hclge_comm_stats_str strs[],
				  पूर्णांक size, u8 *data)
अणु
	अक्षर *buff = (अक्षर *)data;
	u32 i;

	अगर (stringset != ETH_SS_STATS)
		वापस buff;

	क्रम (i = 0; i < size; i++) अणु
		snम_लिखो(buff, ETH_GSTRING_LEN, "%s", strs[i].desc);
		buff = buff + ETH_GSTRING_LEN;
	पूर्ण

	वापस (u8 *)buff;
पूर्ण

अटल व्योम hclge_update_stats_क्रम_all(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_handle *handle;
	पूर्णांक status;

	handle = &hdev->vport[0].nic;
	अगर (handle->client) अणु
		status = hclge_tqps_update_stats(handle);
		अगर (status) अणु
			dev_err(&hdev->pdev->dev,
				"Update TQPS stats fail, status = %d.\n",
				status);
		पूर्ण
	पूर्ण

	status = hclge_mac_update_stats(hdev);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"Update MAC stats fail, status = %d.\n", status);
पूर्ण

अटल व्योम hclge_update_stats(काष्ठा hnae3_handle *handle,
			       काष्ठा net_device_stats *net_stats)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक status;

	अगर (test_and_set_bit(HCLGE_STATE_STATISTICS_UPDATING, &hdev->state))
		वापस;

	status = hclge_mac_update_stats(hdev);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"Update MAC stats fail, status = %d.\n",
			status);

	status = hclge_tqps_update_stats(handle);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"Update TQPS stats fail, status = %d.\n",
			status);

	clear_bit(HCLGE_STATE_STATISTICS_UPDATING, &hdev->state);
पूर्ण

अटल पूर्णांक hclge_get_sset_count(काष्ठा hnae3_handle *handle, पूर्णांक stringset)
अणु
#घोषणा HCLGE_LOOPBACK_TEST_FLAGS (HNAE3_SUPPORT_APP_LOOPBACK |\
		HNAE3_SUPPORT_PHY_LOOPBACK |\
		HNAE3_SUPPORT_SERDES_SERIAL_LOOPBACK |\
		HNAE3_SUPPORT_SERDES_PARALLEL_LOOPBACK)

	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक count = 0;

	/* Loopback test support rules:
	 * mac: only GE mode support
	 * serdes: all mac mode will support include GE/XGE/LGE/CGE
	 * phy: only support when phy device exist on board
	 */
	अगर (stringset == ETH_SS_TEST) अणु
		/* clear loopback bit flags at first */
		handle->flags = (handle->flags & (~HCLGE_LOOPBACK_TEST_FLAGS));
		अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2 ||
		    hdev->hw.mac.speed == HCLGE_MAC_SPEED_10M ||
		    hdev->hw.mac.speed == HCLGE_MAC_SPEED_100M ||
		    hdev->hw.mac.speed == HCLGE_MAC_SPEED_1G) अणु
			count += 1;
			handle->flags |= HNAE3_SUPPORT_APP_LOOPBACK;
		पूर्ण

		count += 2;
		handle->flags |= HNAE3_SUPPORT_SERDES_SERIAL_LOOPBACK;
		handle->flags |= HNAE3_SUPPORT_SERDES_PARALLEL_LOOPBACK;

		अगर ((hdev->hw.mac.phydev && hdev->hw.mac.phydev->drv &&
		     hdev->hw.mac.phydev->drv->set_loopback) ||
		    hnae3_dev_phy_imp_supported(hdev)) अणु
			count += 1;
			handle->flags |= HNAE3_SUPPORT_PHY_LOOPBACK;
		पूर्ण
	पूर्ण अन्यथा अगर (stringset == ETH_SS_STATS) अणु
		count = ARRAY_SIZE(g_mac_stats_string) +
			hclge_tqps_get_sset_count(handle, stringset);
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम hclge_get_strings(काष्ठा hnae3_handle *handle, u32 stringset,
			      u8 *data)
अणु
	u8 *p = (अक्षर *)data;
	पूर्णांक size;

	अगर (stringset == ETH_SS_STATS) अणु
		size = ARRAY_SIZE(g_mac_stats_string);
		p = hclge_comm_get_strings(stringset, g_mac_stats_string,
					   size, p);
		p = hclge_tqps_get_strings(handle, p);
	पूर्ण अन्यथा अगर (stringset == ETH_SS_TEST) अणु
		अगर (handle->flags & HNAE3_SUPPORT_APP_LOOPBACK) अणु
			स_नकल(p, hns3_nic_test_strs[HNAE3_LOOP_APP],
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अगर (handle->flags & HNAE3_SUPPORT_SERDES_SERIAL_LOOPBACK) अणु
			स_नकल(p, hns3_nic_test_strs[HNAE3_LOOP_SERIAL_SERDES],
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अगर (handle->flags & HNAE3_SUPPORT_SERDES_PARALLEL_LOOPBACK) अणु
			स_नकल(p,
			       hns3_nic_test_strs[HNAE3_LOOP_PARALLEL_SERDES],
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अगर (handle->flags & HNAE3_SUPPORT_PHY_LOOPBACK) अणु
			स_नकल(p, hns3_nic_test_strs[HNAE3_LOOP_PHY],
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hclge_get_stats(काष्ठा hnae3_handle *handle, u64 *data)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	u64 *p;

	p = hclge_comm_get_stats(&hdev->mac_stats, g_mac_stats_string,
				 ARRAY_SIZE(g_mac_stats_string), data);
	p = hclge_tqps_get_stats(handle, p);
पूर्ण

अटल व्योम hclge_get_mac_stat(काष्ठा hnae3_handle *handle,
			       काष्ठा hns3_mac_stats *mac_stats)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	hclge_update_stats(handle, शून्य);

	mac_stats->tx_छोड़ो_cnt = hdev->mac_stats.mac_tx_mac_छोड़ो_num;
	mac_stats->rx_छोड़ो_cnt = hdev->mac_stats.mac_rx_mac_छोड़ो_num;
पूर्ण

अटल पूर्णांक hclge_parse_func_status(काष्ठा hclge_dev *hdev,
				   काष्ठा hclge_func_status_cmd *status)
अणु
#घोषणा HCLGE_MAC_ID_MASK	0xF

	अगर (!(status->pf_state & HCLGE_PF_STATE_DONE))
		वापस -EINVAL;

	/* Set the pf to मुख्य pf */
	अगर (status->pf_state & HCLGE_PF_STATE_MAIN)
		hdev->flag |= HCLGE_FLAG_MAIN;
	अन्यथा
		hdev->flag &= ~HCLGE_FLAG_MAIN;

	hdev->hw.mac.mac_id = status->mac_id & HCLGE_MAC_ID_MASK;
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_query_function_status(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_QUERY_MAX_CNT	5

	काष्ठा hclge_func_status_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक समयout = 0;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_FUNC_STATUS, true);
	req = (काष्ठा hclge_func_status_cmd *)desc.data;

	करो अणु
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"query function status failed %d.\n", ret);
			वापस ret;
		पूर्ण

		/* Check pf reset is करोne */
		अगर (req->pf_state)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण जबतक (समयout++ < HCLGE_QUERY_MAX_CNT);

	वापस hclge_parse_func_status(hdev, req);
पूर्ण

अटल पूर्णांक hclge_query_pf_resource(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_pf_res_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_PF_RSRC, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"query pf resource failed %d.\n", ret);
		वापस ret;
	पूर्ण

	req = (काष्ठा hclge_pf_res_cmd *)desc.data;
	hdev->num_tqps = le16_to_cpu(req->tqp_num) +
			 le16_to_cpu(req->ext_tqp_num);
	hdev->pkt_buf_size = le16_to_cpu(req->buf_size) << HCLGE_BUF_UNIT_S;

	अगर (req->tx_buf_size)
		hdev->tx_buf_size =
			le16_to_cpu(req->tx_buf_size) << HCLGE_BUF_UNIT_S;
	अन्यथा
		hdev->tx_buf_size = HCLGE_DEFAULT_TX_BUF;

	hdev->tx_buf_size = roundup(hdev->tx_buf_size, HCLGE_BUF_SIZE_UNIT);

	अगर (req->dv_buf_size)
		hdev->dv_buf_size =
			le16_to_cpu(req->dv_buf_size) << HCLGE_BUF_UNIT_S;
	अन्यथा
		hdev->dv_buf_size = HCLGE_DEFAULT_DV;

	hdev->dv_buf_size = roundup(hdev->dv_buf_size, HCLGE_BUF_SIZE_UNIT);

	hdev->num_nic_msi = le16_to_cpu(req->msixcap_localid_number_nic);
	अगर (hdev->num_nic_msi < HNAE3_MIN_VECTOR_NUM) अणु
		dev_err(&hdev->pdev->dev,
			"only %u msi resources available, not enough for pf(min:2).\n",
			hdev->num_nic_msi);
		वापस -EINVAL;
	पूर्ण

	अगर (hnae3_dev_roce_supported(hdev)) अणु
		hdev->num_roce_msi =
			le16_to_cpu(req->pf_पूर्णांकr_vector_number_roce);

		/* PF should have NIC vectors and Roce vectors,
		 * NIC vectors are queued beक्रमe Roce vectors.
		 */
		hdev->num_msi = hdev->num_nic_msi + hdev->num_roce_msi;
	पूर्ण अन्यथा अणु
		hdev->num_msi = hdev->num_nic_msi;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_parse_speed(u8 speed_cmd, u32 *speed)
अणु
	चयन (speed_cmd) अणु
	हाल 6:
		*speed = HCLGE_MAC_SPEED_10M;
		अवरोध;
	हाल 7:
		*speed = HCLGE_MAC_SPEED_100M;
		अवरोध;
	हाल 0:
		*speed = HCLGE_MAC_SPEED_1G;
		अवरोध;
	हाल 1:
		*speed = HCLGE_MAC_SPEED_10G;
		अवरोध;
	हाल 2:
		*speed = HCLGE_MAC_SPEED_25G;
		अवरोध;
	हाल 3:
		*speed = HCLGE_MAC_SPEED_40G;
		अवरोध;
	हाल 4:
		*speed = HCLGE_MAC_SPEED_50G;
		अवरोध;
	हाल 5:
		*speed = HCLGE_MAC_SPEED_100G;
		अवरोध;
	हाल 8:
		*speed = HCLGE_MAC_SPEED_200G;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_check_port_speed(काष्ठा hnae3_handle *handle, u32 speed)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	u32 speed_ability = hdev->hw.mac.speed_ability;
	u32 speed_bit = 0;

	चयन (speed) अणु
	हाल HCLGE_MAC_SPEED_10M:
		speed_bit = HCLGE_SUPPORT_10M_BIT;
		अवरोध;
	हाल HCLGE_MAC_SPEED_100M:
		speed_bit = HCLGE_SUPPORT_100M_BIT;
		अवरोध;
	हाल HCLGE_MAC_SPEED_1G:
		speed_bit = HCLGE_SUPPORT_1G_BIT;
		अवरोध;
	हाल HCLGE_MAC_SPEED_10G:
		speed_bit = HCLGE_SUPPORT_10G_BIT;
		अवरोध;
	हाल HCLGE_MAC_SPEED_25G:
		speed_bit = HCLGE_SUPPORT_25G_BIT;
		अवरोध;
	हाल HCLGE_MAC_SPEED_40G:
		speed_bit = HCLGE_SUPPORT_40G_BIT;
		अवरोध;
	हाल HCLGE_MAC_SPEED_50G:
		speed_bit = HCLGE_SUPPORT_50G_BIT;
		अवरोध;
	हाल HCLGE_MAC_SPEED_100G:
		speed_bit = HCLGE_SUPPORT_100G_BIT;
		अवरोध;
	हाल HCLGE_MAC_SPEED_200G:
		speed_bit = HCLGE_SUPPORT_200G_BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (speed_bit & speed_ability)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल व्योम hclge_convert_setting_sr(काष्ठा hclge_mac *mac, u16 speed_ability)
अणु
	अगर (speed_ability & HCLGE_SUPPORT_10G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_25G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_40G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_50G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_100G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_200G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_200000baseSR4_Full_BIT,
				 mac->supported);
पूर्ण

अटल व्योम hclge_convert_setting_lr(काष्ठा hclge_mac *mac, u16 speed_ability)
अणु
	अगर (speed_ability & HCLGE_SUPPORT_10G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_25G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_50G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_40G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_100G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_200G_BIT)
		linkmode_set_bit(
			ETHTOOL_LINK_MODE_200000baseLR4_ER4_FR4_Full_BIT,
			mac->supported);
पूर्ण

अटल व्योम hclge_convert_setting_cr(काष्ठा hclge_mac *mac, u16 speed_ability)
अणु
	अगर (speed_ability & HCLGE_SUPPORT_10G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseCR_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_25G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_40G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_50G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_100G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_200G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_200000baseCR4_Full_BIT,
				 mac->supported);
पूर्ण

अटल व्योम hclge_convert_setting_kr(काष्ठा hclge_mac *mac, u16 speed_ability)
अणु
	अगर (speed_ability & HCLGE_SUPPORT_1G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_10G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_25G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_40G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_50G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_100G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
				 mac->supported);
	अगर (speed_ability & HCLGE_SUPPORT_200G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_200000baseKR4_Full_BIT,
				 mac->supported);
पूर्ण

अटल व्योम hclge_convert_setting_fec(काष्ठा hclge_mac *mac)
अणु
	linkmode_clear_bit(ETHTOOL_LINK_MODE_FEC_BASER_BIT, mac->supported);
	linkmode_clear_bit(ETHTOOL_LINK_MODE_FEC_RS_BIT, mac->supported);

	चयन (mac->speed) अणु
	हाल HCLGE_MAC_SPEED_10G:
	हाल HCLGE_MAC_SPEED_40G:
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_BASER_BIT,
				 mac->supported);
		mac->fec_ability =
			BIT(HNAE3_FEC_BASER) | BIT(HNAE3_FEC_AUTO);
		अवरोध;
	हाल HCLGE_MAC_SPEED_25G:
	हाल HCLGE_MAC_SPEED_50G:
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_RS_BIT,
				 mac->supported);
		mac->fec_ability =
			BIT(HNAE3_FEC_BASER) | BIT(HNAE3_FEC_RS) |
			BIT(HNAE3_FEC_AUTO);
		अवरोध;
	हाल HCLGE_MAC_SPEED_100G:
	हाल HCLGE_MAC_SPEED_200G:
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_RS_BIT, mac->supported);
		mac->fec_ability = BIT(HNAE3_FEC_RS) | BIT(HNAE3_FEC_AUTO);
		अवरोध;
	शेष:
		mac->fec_ability = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hclge_parse_fiber_link_mode(काष्ठा hclge_dev *hdev,
					u16 speed_ability)
अणु
	काष्ठा hclge_mac *mac = &hdev->hw.mac;

	अगर (speed_ability & HCLGE_SUPPORT_1G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
				 mac->supported);

	hclge_convert_setting_sr(mac, speed_ability);
	hclge_convert_setting_lr(mac, speed_ability);
	hclge_convert_setting_cr(mac, speed_ability);
	अगर (hnae3_dev_fec_supported(hdev))
		hclge_convert_setting_fec(mac);

	अगर (hnae3_dev_छोड़ो_supported(hdev))
		linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT, mac->supported);

	linkmode_set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT, mac->supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_NONE_BIT, mac->supported);
पूर्ण

अटल व्योम hclge_parse_backplane_link_mode(काष्ठा hclge_dev *hdev,
					    u16 speed_ability)
अणु
	काष्ठा hclge_mac *mac = &hdev->hw.mac;

	hclge_convert_setting_kr(mac, speed_ability);
	अगर (hnae3_dev_fec_supported(hdev))
		hclge_convert_setting_fec(mac);

	अगर (hnae3_dev_छोड़ो_supported(hdev))
		linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT, mac->supported);

	linkmode_set_bit(ETHTOOL_LINK_MODE_Backplane_BIT, mac->supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_NONE_BIT, mac->supported);
पूर्ण

अटल व्योम hclge_parse_copper_link_mode(काष्ठा hclge_dev *hdev,
					 u16 speed_ability)
अणु
	अचिन्हित दीर्घ *supported = hdev->hw.mac.supported;

	/* शेष to support all speed क्रम GE port */
	अगर (!speed_ability)
		speed_ability = HCLGE_SUPPORT_GE;

	अगर (speed_ability & HCLGE_SUPPORT_1G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				 supported);

	अगर (speed_ability & HCLGE_SUPPORT_100M_BIT) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
				 supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
				 supported);
	पूर्ण

	अगर (speed_ability & HCLGE_SUPPORT_10M_BIT) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT, supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT, supported);
	पूर्ण

	अगर (hnae3_dev_छोड़ो_supported(hdev)) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT, supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, supported);
	पूर्ण

	linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_TP_BIT, supported);
पूर्ण

अटल व्योम hclge_parse_link_mode(काष्ठा hclge_dev *hdev, u16 speed_ability)
अणु
	u8 media_type = hdev->hw.mac.media_type;

	अगर (media_type == HNAE3_MEDIA_TYPE_FIBER)
		hclge_parse_fiber_link_mode(hdev, speed_ability);
	अन्यथा अगर (media_type == HNAE3_MEDIA_TYPE_COPPER)
		hclge_parse_copper_link_mode(hdev, speed_ability);
	अन्यथा अगर (media_type == HNAE3_MEDIA_TYPE_BACKPLANE)
		hclge_parse_backplane_link_mode(hdev, speed_ability);
पूर्ण

अटल u32 hclge_get_max_speed(u16 speed_ability)
अणु
	अगर (speed_ability & HCLGE_SUPPORT_200G_BIT)
		वापस HCLGE_MAC_SPEED_200G;

	अगर (speed_ability & HCLGE_SUPPORT_100G_BIT)
		वापस HCLGE_MAC_SPEED_100G;

	अगर (speed_ability & HCLGE_SUPPORT_50G_BIT)
		वापस HCLGE_MAC_SPEED_50G;

	अगर (speed_ability & HCLGE_SUPPORT_40G_BIT)
		वापस HCLGE_MAC_SPEED_40G;

	अगर (speed_ability & HCLGE_SUPPORT_25G_BIT)
		वापस HCLGE_MAC_SPEED_25G;

	अगर (speed_ability & HCLGE_SUPPORT_10G_BIT)
		वापस HCLGE_MAC_SPEED_10G;

	अगर (speed_ability & HCLGE_SUPPORT_1G_BIT)
		वापस HCLGE_MAC_SPEED_1G;

	अगर (speed_ability & HCLGE_SUPPORT_100M_BIT)
		वापस HCLGE_MAC_SPEED_100M;

	अगर (speed_ability & HCLGE_SUPPORT_10M_BIT)
		वापस HCLGE_MAC_SPEED_10M;

	वापस HCLGE_MAC_SPEED_1G;
पूर्ण

अटल व्योम hclge_parse_cfg(काष्ठा hclge_cfg *cfg, काष्ठा hclge_desc *desc)
अणु
#घोषणा SPEED_ABILITY_EXT_SHIFT			8

	काष्ठा hclge_cfg_param_cmd *req;
	u64 mac_addr_पंचांगp_high;
	u16 speed_ability_ext;
	u64 mac_addr_पंचांगp;
	अचिन्हित पूर्णांक i;

	req = (काष्ठा hclge_cfg_param_cmd *)desc[0].data;

	/* get the configuration */
	cfg->tc_num = hnae3_get_field(__le32_to_cpu(req->param[0]),
				      HCLGE_CFG_TC_NUM_M, HCLGE_CFG_TC_NUM_S);
	cfg->tqp_desc_num = hnae3_get_field(__le32_to_cpu(req->param[0]),
					    HCLGE_CFG_TQP_DESC_N_M,
					    HCLGE_CFG_TQP_DESC_N_S);

	cfg->phy_addr = hnae3_get_field(__le32_to_cpu(req->param[1]),
					HCLGE_CFG_PHY_ADDR_M,
					HCLGE_CFG_PHY_ADDR_S);
	cfg->media_type = hnae3_get_field(__le32_to_cpu(req->param[1]),
					  HCLGE_CFG_MEDIA_TP_M,
					  HCLGE_CFG_MEDIA_TP_S);
	cfg->rx_buf_len = hnae3_get_field(__le32_to_cpu(req->param[1]),
					  HCLGE_CFG_RX_BUF_LEN_M,
					  HCLGE_CFG_RX_BUF_LEN_S);
	/* get mac_address */
	mac_addr_पंचांगp = __le32_to_cpu(req->param[2]);
	mac_addr_पंचांगp_high = hnae3_get_field(__le32_to_cpu(req->param[3]),
					    HCLGE_CFG_MAC_ADDR_H_M,
					    HCLGE_CFG_MAC_ADDR_H_S);

	mac_addr_पंचांगp |= (mac_addr_पंचांगp_high << 31) << 1;

	cfg->शेष_speed = hnae3_get_field(__le32_to_cpu(req->param[3]),
					     HCLGE_CFG_DEFAULT_SPEED_M,
					     HCLGE_CFG_DEFAULT_SPEED_S);
	cfg->vf_rss_size_max = hnae3_get_field(__le32_to_cpu(req->param[3]),
					       HCLGE_CFG_RSS_SIZE_M,
					       HCLGE_CFG_RSS_SIZE_S);

	क्रम (i = 0; i < ETH_ALEN; i++)
		cfg->mac_addr[i] = (mac_addr_पंचांगp >> (8 * i)) & 0xff;

	req = (काष्ठा hclge_cfg_param_cmd *)desc[1].data;
	cfg->numa_node_map = __le32_to_cpu(req->param[0]);

	cfg->speed_ability = hnae3_get_field(__le32_to_cpu(req->param[1]),
					     HCLGE_CFG_SPEED_ABILITY_M,
					     HCLGE_CFG_SPEED_ABILITY_S);
	speed_ability_ext = hnae3_get_field(__le32_to_cpu(req->param[1]),
					    HCLGE_CFG_SPEED_ABILITY_EXT_M,
					    HCLGE_CFG_SPEED_ABILITY_EXT_S);
	cfg->speed_ability |= speed_ability_ext << SPEED_ABILITY_EXT_SHIFT;

	cfg->umv_space = hnae3_get_field(__le32_to_cpu(req->param[1]),
					 HCLGE_CFG_UMV_TBL_SPACE_M,
					 HCLGE_CFG_UMV_TBL_SPACE_S);
	अगर (!cfg->umv_space)
		cfg->umv_space = HCLGE_DEFAULT_UMV_SPACE_PER_PF;

	cfg->pf_rss_size_max = hnae3_get_field(__le32_to_cpu(req->param[2]),
					       HCLGE_CFG_PF_RSS_SIZE_M,
					       HCLGE_CFG_PF_RSS_SIZE_S);

	/* HCLGE_CFG_PF_RSS_SIZE_M is the PF max rss size, which is a
	 * घातer of 2, instead of पढ़ोing out directly. This would
	 * be more flexible क्रम future changes and expansions.
	 * When VF max  rss size field is HCLGE_CFG_RSS_SIZE_S,
	 * it करोes not make sense अगर PF's field is 0. In this हाल, PF and VF
	 * has the same max rss size filed: HCLGE_CFG_RSS_SIZE_S.
	 */
	cfg->pf_rss_size_max = cfg->pf_rss_size_max ?
			       1U << cfg->pf_rss_size_max :
			       cfg->vf_rss_size_max;
पूर्ण

/* hclge_get_cfg: query the अटल parameter from flash
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @hcfg: the config काष्ठाure to be getted
 */
अटल पूर्णांक hclge_get_cfg(काष्ठा hclge_dev *hdev, काष्ठा hclge_cfg *hcfg)
अणु
	काष्ठा hclge_desc desc[HCLGE_PF_CFG_DESC_NUM];
	काष्ठा hclge_cfg_param_cmd *req;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < HCLGE_PF_CFG_DESC_NUM; i++) अणु
		u32 offset = 0;

		req = (काष्ठा hclge_cfg_param_cmd *)desc[i].data;
		hclge_cmd_setup_basic_desc(&desc[i], HCLGE_OPC_GET_CFG_PARAM,
					   true);
		hnae3_set_field(offset, HCLGE_CFG_OFFSET_M,
				HCLGE_CFG_OFFSET_S, i * HCLGE_CFG_RD_LEN_BYTES);
		/* Len should be united by 4 bytes when send to hardware */
		hnae3_set_field(offset, HCLGE_CFG_RD_LEN_M, HCLGE_CFG_RD_LEN_S,
				HCLGE_CFG_RD_LEN_BYTES / HCLGE_CFG_RD_LEN_UNIT);
		req->offset = cpu_to_le32(offset);
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_PF_CFG_DESC_NUM);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "get config failed %d.\n", ret);
		वापस ret;
	पूर्ण

	hclge_parse_cfg(hcfg, desc);

	वापस 0;
पूर्ण

अटल व्योम hclge_set_शेष_dev_specs(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_MAX_NON_TSO_BD_NUM			8U

	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);

	ae_dev->dev_specs.max_non_tso_bd_num = HCLGE_MAX_NON_TSO_BD_NUM;
	ae_dev->dev_specs.rss_ind_tbl_size = HCLGE_RSS_IND_TBL_SIZE;
	ae_dev->dev_specs.rss_key_size = HCLGE_RSS_KEY_SIZE;
	ae_dev->dev_specs.max_पंचांग_rate = HCLGE_ETHER_MAX_RATE;
	ae_dev->dev_specs.max_पूर्णांक_gl = HCLGE_DEF_MAX_INT_GL;
	ae_dev->dev_specs.max_frm_size = HCLGE_MAC_MAX_FRAME;
	ae_dev->dev_specs.max_qset_num = HCLGE_MAX_QSET_NUM;
पूर्ण

अटल व्योम hclge_parse_dev_specs(काष्ठा hclge_dev *hdev,
				  काष्ठा hclge_desc *desc)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);
	काष्ठा hclge_dev_specs_0_cmd *req0;
	काष्ठा hclge_dev_specs_1_cmd *req1;

	req0 = (काष्ठा hclge_dev_specs_0_cmd *)desc[0].data;
	req1 = (काष्ठा hclge_dev_specs_1_cmd *)desc[1].data;

	ae_dev->dev_specs.max_non_tso_bd_num = req0->max_non_tso_bd_num;
	ae_dev->dev_specs.rss_ind_tbl_size =
		le16_to_cpu(req0->rss_ind_tbl_size);
	ae_dev->dev_specs.पूर्णांक_ql_max = le16_to_cpu(req0->पूर्णांक_ql_max);
	ae_dev->dev_specs.rss_key_size = le16_to_cpu(req0->rss_key_size);
	ae_dev->dev_specs.max_पंचांग_rate = le32_to_cpu(req0->max_पंचांग_rate);
	ae_dev->dev_specs.max_qset_num = le16_to_cpu(req1->max_qset_num);
	ae_dev->dev_specs.max_पूर्णांक_gl = le16_to_cpu(req1->max_पूर्णांक_gl);
	ae_dev->dev_specs.max_frm_size = le16_to_cpu(req1->max_frm_size);
पूर्ण

अटल व्योम hclge_check_dev_specs(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_dev_specs *dev_specs = &hdev->ae_dev->dev_specs;

	अगर (!dev_specs->max_non_tso_bd_num)
		dev_specs->max_non_tso_bd_num = HCLGE_MAX_NON_TSO_BD_NUM;
	अगर (!dev_specs->rss_ind_tbl_size)
		dev_specs->rss_ind_tbl_size = HCLGE_RSS_IND_TBL_SIZE;
	अगर (!dev_specs->rss_key_size)
		dev_specs->rss_key_size = HCLGE_RSS_KEY_SIZE;
	अगर (!dev_specs->max_पंचांग_rate)
		dev_specs->max_पंचांग_rate = HCLGE_ETHER_MAX_RATE;
	अगर (!dev_specs->max_qset_num)
		dev_specs->max_qset_num = HCLGE_MAX_QSET_NUM;
	अगर (!dev_specs->max_पूर्णांक_gl)
		dev_specs->max_पूर्णांक_gl = HCLGE_DEF_MAX_INT_GL;
	अगर (!dev_specs->max_frm_size)
		dev_specs->max_frm_size = HCLGE_MAC_MAX_FRAME;
पूर्ण

अटल पूर्णांक hclge_query_dev_specs(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_desc desc[HCLGE_QUERY_DEV_SPECS_BD_NUM];
	पूर्णांक ret;
	पूर्णांक i;

	/* set शेष specअगरications as devices lower than version V3 करो not
	 * support querying specअगरications from firmware.
	 */
	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V3) अणु
		hclge_set_शेष_dev_specs(hdev);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < HCLGE_QUERY_DEV_SPECS_BD_NUM - 1; i++) अणु
		hclge_cmd_setup_basic_desc(&desc[i], HCLGE_OPC_QUERY_DEV_SPECS,
					   true);
		desc[i].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	पूर्ण
	hclge_cmd_setup_basic_desc(&desc[i], HCLGE_OPC_QUERY_DEV_SPECS, true);

	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_QUERY_DEV_SPECS_BD_NUM);
	अगर (ret)
		वापस ret;

	hclge_parse_dev_specs(hdev, desc);
	hclge_check_dev_specs(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_cap(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_query_function_status(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"query function status error %d.\n", ret);
		वापस ret;
	पूर्ण

	/* get pf resource */
	वापस hclge_query_pf_resource(hdev);
पूर्ण

अटल व्योम hclge_init_kdump_kernel_config(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_MIN_TX_DESC	64
#घोषणा HCLGE_MIN_RX_DESC	64

	अगर (!is_kdump_kernel())
		वापस;

	dev_info(&hdev->pdev->dev,
		 "Running kdump kernel. Using minimal resources\n");

	/* minimal queue pairs equals to the number of vports */
	hdev->num_tqps = hdev->num_req_vfs + 1;
	hdev->num_tx_desc = HCLGE_MIN_TX_DESC;
	hdev->num_rx_desc = HCLGE_MIN_RX_DESC;
पूर्ण

अटल पूर्णांक hclge_configure(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_cfg cfg;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = hclge_get_cfg(hdev, &cfg);
	अगर (ret)
		वापस ret;

	hdev->base_tqp_pid = 0;
	hdev->vf_rss_size_max = cfg.vf_rss_size_max;
	hdev->pf_rss_size_max = cfg.pf_rss_size_max;
	hdev->rx_buf_len = cfg.rx_buf_len;
	ether_addr_copy(hdev->hw.mac.mac_addr, cfg.mac_addr);
	hdev->hw.mac.media_type = cfg.media_type;
	hdev->hw.mac.phy_addr = cfg.phy_addr;
	hdev->num_tx_desc = cfg.tqp_desc_num;
	hdev->num_rx_desc = cfg.tqp_desc_num;
	hdev->पंचांग_info.num_pg = 1;
	hdev->tc_max = cfg.tc_num;
	hdev->पंचांग_info.hw_pfc_map = 0;
	hdev->wanted_umv_size = cfg.umv_space;

	अगर (hnae3_dev_fd_supported(hdev)) अणु
		hdev->fd_en = true;
		hdev->fd_active_type = HCLGE_FD_RULE_NONE;
	पूर्ण

	ret = hclge_parse_speed(cfg.शेष_speed, &hdev->hw.mac.speed);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "failed to parse speed %u, ret = %d\n",
			cfg.शेष_speed, ret);
		वापस ret;
	पूर्ण

	hclge_parse_link_mode(hdev, cfg.speed_ability);

	hdev->hw.mac.max_speed = hclge_get_max_speed(cfg.speed_ability);

	अगर ((hdev->tc_max > HNAE3_MAX_TC) ||
	    (hdev->tc_max < 1)) अणु
		dev_warn(&hdev->pdev->dev, "TC num = %u.\n",
			 hdev->tc_max);
		hdev->tc_max = 1;
	पूर्ण

	/* Dev करोes not support DCB */
	अगर (!hnae3_dev_dcb_supported(hdev)) अणु
		hdev->tc_max = 1;
		hdev->pfc_max = 0;
	पूर्ण अन्यथा अणु
		hdev->pfc_max = hdev->tc_max;
	पूर्ण

	hdev->पंचांग_info.num_tc = 1;

	/* Currently not support uncontiuous tc */
	क्रम (i = 0; i < hdev->पंचांग_info.num_tc; i++)
		hnae3_set_bit(hdev->hw_tc_map, i, 1);

	hdev->tx_sch_mode = HCLGE_FLAG_TC_BASE_SCH_MODE;

	hclge_init_kdump_kernel_config(hdev);

	/* Set the init affinity based on pci func number */
	i = cpumask_weight(cpumask_of_node(dev_to_node(&hdev->pdev->dev)));
	i = i ? PCI_FUNC(hdev->pdev->devfn) % i : 0;
	cpumask_set_cpu(cpumask_local_spपढ़ो(i, dev_to_node(&hdev->pdev->dev)),
			&hdev->affinity_mask);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_tso(काष्ठा hclge_dev *hdev, u16 tso_mss_min,
			    u16 tso_mss_max)
अणु
	काष्ठा hclge_cfg_tso_status_cmd *req;
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TSO_GENERIC_CONFIG, false);

	req = (काष्ठा hclge_cfg_tso_status_cmd *)desc.data;
	req->tso_mss_min = cpu_to_le16(tso_mss_min);
	req->tso_mss_max = cpu_to_le16(tso_mss_max);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_config_gro(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा hclge_cfg_gro_status_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	अगर (!hnae3_dev_gro_supported(hdev))
		वापस 0;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_GRO_GENERIC_CONFIG, false);
	req = (काष्ठा hclge_cfg_gro_status_cmd *)desc.data;

	req->gro_en = en ? 1 : 0;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"GRO hardware config cmd failed, ret = %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_alloc_tqps(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_tqp *tqp;
	पूर्णांक i;

	hdev->htqp = devm_kसुस्मृति(&hdev->pdev->dev, hdev->num_tqps,
				  माप(काष्ठा hclge_tqp), GFP_KERNEL);
	अगर (!hdev->htqp)
		वापस -ENOMEM;

	tqp = hdev->htqp;

	क्रम (i = 0; i < hdev->num_tqps; i++) अणु
		tqp->dev = &hdev->pdev->dev;
		tqp->index = i;

		tqp->q.ae_algo = &ae_algo;
		tqp->q.buf_size = hdev->rx_buf_len;
		tqp->q.tx_desc_num = hdev->num_tx_desc;
		tqp->q.rx_desc_num = hdev->num_rx_desc;

		/* need an extended offset to configure queues >=
		 * HCLGE_TQP_MAX_SIZE_DEV_V2
		 */
		अगर (i < HCLGE_TQP_MAX_SIZE_DEV_V2)
			tqp->q.io_base = hdev->hw.io_base +
					 HCLGE_TQP_REG_OFFSET +
					 i * HCLGE_TQP_REG_SIZE;
		अन्यथा
			tqp->q.io_base = hdev->hw.io_base +
					 HCLGE_TQP_REG_OFFSET +
					 HCLGE_TQP_EXT_REG_OFFSET +
					 (i - HCLGE_TQP_MAX_SIZE_DEV_V2) *
					 HCLGE_TQP_REG_SIZE;

		tqp++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_map_tqps_to_func(काष्ठा hclge_dev *hdev, u16 func_id,
				  u16 tqp_pid, u16 tqp_vid, bool is_pf)
अणु
	काष्ठा hclge_tqp_map_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_SET_TQP_MAP, false);

	req = (काष्ठा hclge_tqp_map_cmd *)desc.data;
	req->tqp_id = cpu_to_le16(tqp_pid);
	req->tqp_vf = func_id;
	req->tqp_flag = 1U << HCLGE_TQP_MAP_EN_B;
	अगर (!is_pf)
		req->tqp_flag |= 1U << HCLGE_TQP_MAP_TYPE_B;
	req->tqp_vid = cpu_to_le16(tqp_vid);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "TQP map failed %d.\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक  hclge_assign_tqp(काष्ठा hclge_vport *vport, u16 num_tqps)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक i, alloced;

	क्रम (i = 0, alloced = 0; i < hdev->num_tqps &&
	     alloced < num_tqps; i++) अणु
		अगर (!hdev->htqp[i].alloced) अणु
			hdev->htqp[i].q.handle = &vport->nic;
			hdev->htqp[i].q.tqp_index = alloced;
			hdev->htqp[i].q.tx_desc_num = kinfo->num_tx_desc;
			hdev->htqp[i].q.rx_desc_num = kinfo->num_rx_desc;
			kinfo->tqp[alloced] = &hdev->htqp[i].q;
			hdev->htqp[i].alloced = true;
			alloced++;
		पूर्ण
	पूर्ण
	vport->alloc_tqps = alloced;
	kinfo->rss_size = min_t(u16, hdev->pf_rss_size_max,
				vport->alloc_tqps / hdev->पंचांग_info.num_tc);

	/* ensure one to one mapping between irq and queue at शेष */
	kinfo->rss_size = min_t(u16, kinfo->rss_size,
				(hdev->num_nic_msi - 1) / hdev->पंचांग_info.num_tc);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_knic_setup(काष्ठा hclge_vport *vport, u16 num_tqps,
			    u16 num_tx_desc, u16 num_rx_desc)

अणु
	काष्ठा hnae3_handle *nic = &vport->nic;
	काष्ठा hnae3_knic_निजी_info *kinfo = &nic->kinfo;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	kinfo->num_tx_desc = num_tx_desc;
	kinfo->num_rx_desc = num_rx_desc;

	kinfo->rx_buf_len = hdev->rx_buf_len;

	kinfo->tqp = devm_kसुस्मृति(&hdev->pdev->dev, num_tqps,
				  माप(काष्ठा hnae3_queue *), GFP_KERNEL);
	अगर (!kinfo->tqp)
		वापस -ENOMEM;

	ret = hclge_assign_tqp(vport, num_tqps);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "fail to assign TQPs %d.\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_map_tqp_to_vport(काष्ठा hclge_dev *hdev,
				  काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_handle *nic = &vport->nic;
	काष्ठा hnae3_knic_निजी_info *kinfo;
	u16 i;

	kinfo = &nic->kinfo;
	क्रम (i = 0; i < vport->alloc_tqps; i++) अणु
		काष्ठा hclge_tqp *q =
			container_of(kinfo->tqp[i], काष्ठा hclge_tqp, q);
		bool is_pf;
		पूर्णांक ret;

		is_pf = !(vport->vport_id);
		ret = hclge_map_tqps_to_func(hdev, vport->vport_id, q->index,
					     i, is_pf);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_map_tqp(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	u16 i, num_vport;

	num_vport = hdev->num_req_vfs + 1;
	क्रम (i = 0; i < num_vport; i++)	अणु
		पूर्णांक ret;

		ret = hclge_map_tqp_to_vport(hdev, vport);
		अगर (ret)
			वापस ret;

		vport++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_vport_setup(काष्ठा hclge_vport *vport, u16 num_tqps)
अणु
	काष्ठा hnae3_handle *nic = &vport->nic;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	nic->pdev = hdev->pdev;
	nic->ae_algo = &ae_algo;
	nic->numa_node_mask = hdev->numa_node_mask;

	ret = hclge_knic_setup(vport, num_tqps,
			       hdev->num_tx_desc, hdev->num_rx_desc);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "knic setup failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_alloc_vport(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	काष्ठा hclge_vport *vport;
	u32 tqp_मुख्य_vport;
	u32 tqp_per_vport;
	पूर्णांक num_vport, i;
	पूर्णांक ret;

	/* We need to alloc a vport क्रम मुख्य NIC of PF */
	num_vport = hdev->num_req_vfs + 1;

	अगर (hdev->num_tqps < num_vport) अणु
		dev_err(&hdev->pdev->dev, "tqps(%u) is less than vports(%d)",
			hdev->num_tqps, num_vport);
		वापस -EINVAL;
	पूर्ण

	/* Alloc the same number of TQPs क्रम every vport */
	tqp_per_vport = hdev->num_tqps / num_vport;
	tqp_मुख्य_vport = tqp_per_vport + hdev->num_tqps % num_vport;

	vport = devm_kसुस्मृति(&pdev->dev, num_vport, माप(काष्ठा hclge_vport),
			     GFP_KERNEL);
	अगर (!vport)
		वापस -ENOMEM;

	hdev->vport = vport;
	hdev->num_alloc_vport = num_vport;

	अगर (IS_ENABLED(CONFIG_PCI_IOV))
		hdev->num_alloc_vfs = hdev->num_req_vfs;

	क्रम (i = 0; i < num_vport; i++) अणु
		vport->back = hdev;
		vport->vport_id = i;
		vport->vf_info.link_state = IFLA_VF_LINK_STATE_AUTO;
		vport->mps = HCLGE_MAC_DEFAULT_FRAME;
		vport->port_base_vlan_cfg.state = HNAE3_PORT_BASE_VLAN_DISABLE;
		vport->rxvlan_cfg.rx_vlan_offload_en = true;
		INIT_LIST_HEAD(&vport->vlan_list);
		INIT_LIST_HEAD(&vport->uc_mac_list);
		INIT_LIST_HEAD(&vport->mc_mac_list);
		spin_lock_init(&vport->mac_list_lock);

		अगर (i == 0)
			ret = hclge_vport_setup(vport, tqp_मुख्य_vport);
		अन्यथा
			ret = hclge_vport_setup(vport, tqp_per_vport);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"vport setup failed for vport %d, %d\n",
				i, ret);
			वापस ret;
		पूर्ण

		vport++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक  hclge_cmd_alloc_tx_buff(काष्ठा hclge_dev *hdev,
				    काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
/* TX buffer size is unit by 128 byte */
#घोषणा HCLGE_BUF_SIZE_UNIT_SHIFT	7
#घोषणा HCLGE_BUF_SIZE_UPDATE_EN_MSK	BIT(15)
	काष्ठा hclge_tx_buff_alloc_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;
	u8 i;

	req = (काष्ठा hclge_tx_buff_alloc_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TX_BUFF_ALLOC, 0);
	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		u32 buf_size = buf_alloc->priv_buf[i].tx_buf_size;

		req->tx_pkt_buff[i] =
			cpu_to_le16((buf_size >> HCLGE_BUF_SIZE_UNIT_SHIFT) |
				     HCLGE_BUF_SIZE_UPDATE_EN_MSK);
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "tx buffer alloc cmd failed %d.\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_tx_buffer_alloc(काष्ठा hclge_dev *hdev,
				 काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	पूर्णांक ret = hclge_cmd_alloc_tx_buff(hdev, buf_alloc);

	अगर (ret)
		dev_err(&hdev->pdev->dev, "tx buffer alloc failed %d\n", ret);

	वापस ret;
पूर्ण

अटल u32 hclge_get_tc_num(काष्ठा hclge_dev *hdev)
अणु
	अचिन्हित पूर्णांक i;
	u32 cnt = 0;

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++)
		अगर (hdev->hw_tc_map & BIT(i))
			cnt++;
	वापस cnt;
पूर्ण

/* Get the number of pfc enabled TCs, which have निजी buffer */
अटल पूर्णांक hclge_get_pfc_priv_num(काष्ठा hclge_dev *hdev,
				  काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	काष्ठा hclge_priv_buf *priv;
	अचिन्हित पूर्णांक i;
	पूर्णांक cnt = 0;

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		priv = &buf_alloc->priv_buf[i];
		अगर ((hdev->पंचांग_info.hw_pfc_map & BIT(i)) &&
		    priv->enable)
			cnt++;
	पूर्ण

	वापस cnt;
पूर्ण

/* Get the number of pfc disabled TCs, which have निजी buffer */
अटल पूर्णांक hclge_get_no_pfc_priv_num(काष्ठा hclge_dev *hdev,
				     काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	काष्ठा hclge_priv_buf *priv;
	अचिन्हित पूर्णांक i;
	पूर्णांक cnt = 0;

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		priv = &buf_alloc->priv_buf[i];
		अगर (hdev->hw_tc_map & BIT(i) &&
		    !(hdev->पंचांग_info.hw_pfc_map & BIT(i)) &&
		    priv->enable)
			cnt++;
	पूर्ण

	वापस cnt;
पूर्ण

अटल u32 hclge_get_rx_priv_buff_alloced(काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	काष्ठा hclge_priv_buf *priv;
	u32 rx_priv = 0;
	पूर्णांक i;

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		priv = &buf_alloc->priv_buf[i];
		अगर (priv->enable)
			rx_priv += priv->buf_size;
	पूर्ण
	वापस rx_priv;
पूर्ण

अटल u32 hclge_get_tx_buff_alloced(काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	u32 i, total_tx_size = 0;

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++)
		total_tx_size += buf_alloc->priv_buf[i].tx_buf_size;

	वापस total_tx_size;
पूर्ण

अटल bool  hclge_is_rx_buf_ok(काष्ठा hclge_dev *hdev,
				काष्ठा hclge_pkt_buf_alloc *buf_alloc,
				u32 rx_all)
अणु
	u32 shared_buf_min, shared_buf_tc, shared_std, hi_thrd, lo_thrd;
	u32 tc_num = hclge_get_tc_num(hdev);
	u32 shared_buf, aligned_mps;
	u32 rx_priv;
	पूर्णांक i;

	aligned_mps = roundup(hdev->mps, HCLGE_BUF_SIZE_UNIT);

	अगर (hnae3_dev_dcb_supported(hdev))
		shared_buf_min = HCLGE_BUF_MUL_BY * aligned_mps +
					hdev->dv_buf_size;
	अन्यथा
		shared_buf_min = aligned_mps + HCLGE_NON_DCB_ADDITIONAL_BUF
					+ hdev->dv_buf_size;

	shared_buf_tc = tc_num * aligned_mps + aligned_mps;
	shared_std = roundup(max_t(u32, shared_buf_min, shared_buf_tc),
			     HCLGE_BUF_SIZE_UNIT);

	rx_priv = hclge_get_rx_priv_buff_alloced(buf_alloc);
	अगर (rx_all < rx_priv + shared_std)
		वापस false;

	shared_buf = roundकरोwn(rx_all - rx_priv, HCLGE_BUF_SIZE_UNIT);
	buf_alloc->s_buf.buf_size = shared_buf;
	अगर (hnae3_dev_dcb_supported(hdev)) अणु
		buf_alloc->s_buf.self.high = shared_buf - hdev->dv_buf_size;
		buf_alloc->s_buf.self.low = buf_alloc->s_buf.self.high
			- roundup(aligned_mps / HCLGE_BUF_DIV_BY,
				  HCLGE_BUF_SIZE_UNIT);
	पूर्ण अन्यथा अणु
		buf_alloc->s_buf.self.high = aligned_mps +
						HCLGE_NON_DCB_ADDITIONAL_BUF;
		buf_alloc->s_buf.self.low = aligned_mps;
	पूर्ण

	अगर (hnae3_dev_dcb_supported(hdev)) अणु
		hi_thrd = shared_buf - hdev->dv_buf_size;

		अगर (tc_num <= NEED_RESERVE_TC_NUM)
			hi_thrd = hi_thrd * BUF_RESERVE_PERCENT
					/ BUF_MAX_PERCENT;

		अगर (tc_num)
			hi_thrd = hi_thrd / tc_num;

		hi_thrd = max_t(u32, hi_thrd, HCLGE_BUF_MUL_BY * aligned_mps);
		hi_thrd = roundकरोwn(hi_thrd, HCLGE_BUF_SIZE_UNIT);
		lo_thrd = hi_thrd - aligned_mps / HCLGE_BUF_DIV_BY;
	पूर्ण अन्यथा अणु
		hi_thrd = aligned_mps + HCLGE_NON_DCB_ADDITIONAL_BUF;
		lo_thrd = aligned_mps;
	पूर्ण

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		buf_alloc->s_buf.tc_thrd[i].low = lo_thrd;
		buf_alloc->s_buf.tc_thrd[i].high = hi_thrd;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक hclge_tx_buffer_calc(काष्ठा hclge_dev *hdev,
				काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	u32 i, total_size;

	total_size = hdev->pkt_buf_size;

	/* alloc tx buffer क्रम all enabled tc */
	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		काष्ठा hclge_priv_buf *priv = &buf_alloc->priv_buf[i];

		अगर (hdev->hw_tc_map & BIT(i)) अणु
			अगर (total_size < hdev->tx_buf_size)
				वापस -ENOMEM;

			priv->tx_buf_size = hdev->tx_buf_size;
		पूर्ण अन्यथा अणु
			priv->tx_buf_size = 0;
		पूर्ण

		total_size -= priv->tx_buf_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool hclge_rx_buf_calc_all(काष्ठा hclge_dev *hdev, bool max,
				  काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	u32 rx_all = hdev->pkt_buf_size - hclge_get_tx_buff_alloced(buf_alloc);
	u32 aligned_mps = round_up(hdev->mps, HCLGE_BUF_SIZE_UNIT);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		काष्ठा hclge_priv_buf *priv = &buf_alloc->priv_buf[i];

		priv->enable = 0;
		priv->wl.low = 0;
		priv->wl.high = 0;
		priv->buf_size = 0;

		अगर (!(hdev->hw_tc_map & BIT(i)))
			जारी;

		priv->enable = 1;

		अगर (hdev->पंचांग_info.hw_pfc_map & BIT(i)) अणु
			priv->wl.low = max ? aligned_mps : HCLGE_BUF_SIZE_UNIT;
			priv->wl.high = roundup(priv->wl.low + aligned_mps,
						HCLGE_BUF_SIZE_UNIT);
		पूर्ण अन्यथा अणु
			priv->wl.low = 0;
			priv->wl.high = max ? (aligned_mps * HCLGE_BUF_MUL_BY) :
					aligned_mps;
		पूर्ण

		priv->buf_size = priv->wl.high + hdev->dv_buf_size;
	पूर्ण

	वापस hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all);
पूर्ण

अटल bool hclge_drop_nopfc_buf_till_fit(काष्ठा hclge_dev *hdev,
					  काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	u32 rx_all = hdev->pkt_buf_size - hclge_get_tx_buff_alloced(buf_alloc);
	पूर्णांक no_pfc_priv_num = hclge_get_no_pfc_priv_num(hdev, buf_alloc);
	पूर्णांक i;

	/* let the last to be cleared first */
	क्रम (i = HCLGE_MAX_TC_NUM - 1; i >= 0; i--) अणु
		काष्ठा hclge_priv_buf *priv = &buf_alloc->priv_buf[i];
		अचिन्हित पूर्णांक mask = BIT((अचिन्हित पूर्णांक)i);

		अगर (hdev->hw_tc_map & mask &&
		    !(hdev->पंचांग_info.hw_pfc_map & mask)) अणु
			/* Clear the no pfc TC निजी buffer */
			priv->wl.low = 0;
			priv->wl.high = 0;
			priv->buf_size = 0;
			priv->enable = 0;
			no_pfc_priv_num--;
		पूर्ण

		अगर (hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all) ||
		    no_pfc_priv_num == 0)
			अवरोध;
	पूर्ण

	वापस hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all);
पूर्ण

अटल bool hclge_drop_pfc_buf_till_fit(काष्ठा hclge_dev *hdev,
					काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	u32 rx_all = hdev->pkt_buf_size - hclge_get_tx_buff_alloced(buf_alloc);
	पूर्णांक pfc_priv_num = hclge_get_pfc_priv_num(hdev, buf_alloc);
	पूर्णांक i;

	/* let the last to be cleared first */
	क्रम (i = HCLGE_MAX_TC_NUM - 1; i >= 0; i--) अणु
		काष्ठा hclge_priv_buf *priv = &buf_alloc->priv_buf[i];
		अचिन्हित पूर्णांक mask = BIT((अचिन्हित पूर्णांक)i);

		अगर (hdev->hw_tc_map & mask &&
		    hdev->पंचांग_info.hw_pfc_map & mask) अणु
			/* Reduce the number of pfc TC with निजी buffer */
			priv->wl.low = 0;
			priv->enable = 0;
			priv->wl.high = 0;
			priv->buf_size = 0;
			pfc_priv_num--;
		पूर्ण

		अगर (hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all) ||
		    pfc_priv_num == 0)
			अवरोध;
	पूर्ण

	वापस hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all);
पूर्ण

अटल पूर्णांक hclge_only_alloc_priv_buff(काष्ठा hclge_dev *hdev,
				      काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
#घोषणा COMPENSATE_BUFFER	0x3C00
#घोषणा COMPENSATE_HALF_MPS_NUM	5
#घोषणा PRIV_WL_GAP		0x1800

	u32 rx_priv = hdev->pkt_buf_size - hclge_get_tx_buff_alloced(buf_alloc);
	u32 tc_num = hclge_get_tc_num(hdev);
	u32 half_mps = hdev->mps >> 1;
	u32 min_rx_priv;
	अचिन्हित पूर्णांक i;

	अगर (tc_num)
		rx_priv = rx_priv / tc_num;

	अगर (tc_num <= NEED_RESERVE_TC_NUM)
		rx_priv = rx_priv * BUF_RESERVE_PERCENT / BUF_MAX_PERCENT;

	min_rx_priv = hdev->dv_buf_size + COMPENSATE_BUFFER +
			COMPENSATE_HALF_MPS_NUM * half_mps;
	min_rx_priv = round_up(min_rx_priv, HCLGE_BUF_SIZE_UNIT);
	rx_priv = round_करोwn(rx_priv, HCLGE_BUF_SIZE_UNIT);
	अगर (rx_priv < min_rx_priv)
		वापस false;

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		काष्ठा hclge_priv_buf *priv = &buf_alloc->priv_buf[i];

		priv->enable = 0;
		priv->wl.low = 0;
		priv->wl.high = 0;
		priv->buf_size = 0;

		अगर (!(hdev->hw_tc_map & BIT(i)))
			जारी;

		priv->enable = 1;
		priv->buf_size = rx_priv;
		priv->wl.high = rx_priv - hdev->dv_buf_size;
		priv->wl.low = priv->wl.high - PRIV_WL_GAP;
	पूर्ण

	buf_alloc->s_buf.buf_size = 0;

	वापस true;
पूर्ण

/* hclge_rx_buffer_calc: calculate the rx निजी buffer size क्रम all TCs
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @buf_alloc: poपूर्णांकer to buffer calculation data
 * @वापस: 0: calculate successful, negative: fail
 */
अटल पूर्णांक hclge_rx_buffer_calc(काष्ठा hclge_dev *hdev,
				काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	/* When DCB is not supported, rx निजी buffer is not allocated. */
	अगर (!hnae3_dev_dcb_supported(hdev)) अणु
		u32 rx_all = hdev->pkt_buf_size;

		rx_all -= hclge_get_tx_buff_alloced(buf_alloc);
		अगर (!hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all))
			वापस -ENOMEM;

		वापस 0;
	पूर्ण

	अगर (hclge_only_alloc_priv_buff(hdev, buf_alloc))
		वापस 0;

	अगर (hclge_rx_buf_calc_all(hdev, true, buf_alloc))
		वापस 0;

	/* try to decrease the buffer size */
	अगर (hclge_rx_buf_calc_all(hdev, false, buf_alloc))
		वापस 0;

	अगर (hclge_drop_nopfc_buf_till_fit(hdev, buf_alloc))
		वापस 0;

	अगर (hclge_drop_pfc_buf_till_fit(hdev, buf_alloc))
		वापस 0;

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक hclge_rx_priv_buf_alloc(काष्ठा hclge_dev *hdev,
				   काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	काष्ठा hclge_rx_priv_buff_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;
	पूर्णांक i;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RX_PRIV_BUFF_ALLOC, false);
	req = (काष्ठा hclge_rx_priv_buff_cmd *)desc.data;

	/* Alloc निजी buffer TCs */
	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		काष्ठा hclge_priv_buf *priv = &buf_alloc->priv_buf[i];

		req->buf_num[i] =
			cpu_to_le16(priv->buf_size >> HCLGE_BUF_UNIT_S);
		req->buf_num[i] |=
			cpu_to_le16(1 << HCLGE_TC0_PRI_BUF_EN_B);
	पूर्ण

	req->shared_buf =
		cpu_to_le16((buf_alloc->s_buf.buf_size >> HCLGE_BUF_UNIT_S) |
			    (1 << HCLGE_TC0_PRI_BUF_EN_B));

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"rx private buffer alloc cmd failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_rx_priv_wl_config(काष्ठा hclge_dev *hdev,
				   काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	काष्ठा hclge_rx_priv_wl_buf *req;
	काष्ठा hclge_priv_buf *priv;
	काष्ठा hclge_desc desc[2];
	पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < 2; i++) अणु
		hclge_cmd_setup_basic_desc(&desc[i], HCLGE_OPC_RX_PRIV_WL_ALLOC,
					   false);
		req = (काष्ठा hclge_rx_priv_wl_buf *)desc[i].data;

		/* The first descriptor set the NEXT bit to 1 */
		अगर (i == 0)
			desc[i].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		अन्यथा
			desc[i].flag &= ~cpu_to_le16(HCLGE_CMD_FLAG_NEXT);

		क्रम (j = 0; j < HCLGE_TC_NUM_ONE_DESC; j++) अणु
			u32 idx = i * HCLGE_TC_NUM_ONE_DESC + j;

			priv = &buf_alloc->priv_buf[idx];
			req->tc_wl[j].high =
				cpu_to_le16(priv->wl.high >> HCLGE_BUF_UNIT_S);
			req->tc_wl[j].high |=
				cpu_to_le16(BIT(HCLGE_RX_PRIV_EN_B));
			req->tc_wl[j].low =
				cpu_to_le16(priv->wl.low >> HCLGE_BUF_UNIT_S);
			req->tc_wl[j].low |=
				 cpu_to_le16(BIT(HCLGE_RX_PRIV_EN_B));
		पूर्ण
	पूर्ण

	/* Send 2 descriptor at one समय */
	ret = hclge_cmd_send(&hdev->hw, desc, 2);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"rx private waterline config cmd failed %d\n",
			ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_common_thrd_config(काष्ठा hclge_dev *hdev,
				    काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	काष्ठा hclge_shared_buf *s_buf = &buf_alloc->s_buf;
	काष्ठा hclge_rx_com_thrd *req;
	काष्ठा hclge_desc desc[2];
	काष्ठा hclge_tc_thrd *tc;
	पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < 2; i++) अणु
		hclge_cmd_setup_basic_desc(&desc[i],
					   HCLGE_OPC_RX_COM_THRD_ALLOC, false);
		req = (काष्ठा hclge_rx_com_thrd *)&desc[i].data;

		/* The first descriptor set the NEXT bit to 1 */
		अगर (i == 0)
			desc[i].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		अन्यथा
			desc[i].flag &= ~cpu_to_le16(HCLGE_CMD_FLAG_NEXT);

		क्रम (j = 0; j < HCLGE_TC_NUM_ONE_DESC; j++) अणु
			tc = &s_buf->tc_thrd[i * HCLGE_TC_NUM_ONE_DESC + j];

			req->com_thrd[j].high =
				cpu_to_le16(tc->high >> HCLGE_BUF_UNIT_S);
			req->com_thrd[j].high |=
				 cpu_to_le16(BIT(HCLGE_RX_PRIV_EN_B));
			req->com_thrd[j].low =
				cpu_to_le16(tc->low >> HCLGE_BUF_UNIT_S);
			req->com_thrd[j].low |=
				 cpu_to_le16(BIT(HCLGE_RX_PRIV_EN_B));
		पूर्ण
	पूर्ण

	/* Send 2 descriptors at one समय */
	ret = hclge_cmd_send(&hdev->hw, desc, 2);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"common threshold config cmd failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_common_wl_config(काष्ठा hclge_dev *hdev,
				  काष्ठा hclge_pkt_buf_alloc *buf_alloc)
अणु
	काष्ठा hclge_shared_buf *buf = &buf_alloc->s_buf;
	काष्ठा hclge_rx_com_wl *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RX_COM_WL_ALLOC, false);

	req = (काष्ठा hclge_rx_com_wl *)desc.data;
	req->com_wl.high = cpu_to_le16(buf->self.high >> HCLGE_BUF_UNIT_S);
	req->com_wl.high |=  cpu_to_le16(BIT(HCLGE_RX_PRIV_EN_B));

	req->com_wl.low = cpu_to_le16(buf->self.low >> HCLGE_BUF_UNIT_S);
	req->com_wl.low |=  cpu_to_le16(BIT(HCLGE_RX_PRIV_EN_B));

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"common waterline config cmd failed %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक hclge_buffer_alloc(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_pkt_buf_alloc *pkt_buf;
	पूर्णांक ret;

	pkt_buf = kzalloc(माप(*pkt_buf), GFP_KERNEL);
	अगर (!pkt_buf)
		वापस -ENOMEM;

	ret = hclge_tx_buffer_calc(hdev, pkt_buf);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"could not calc tx buffer size for all TCs %d\n", ret);
		जाओ out;
	पूर्ण

	ret = hclge_tx_buffer_alloc(hdev, pkt_buf);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"could not alloc tx buffers %d\n", ret);
		जाओ out;
	पूर्ण

	ret = hclge_rx_buffer_calc(hdev, pkt_buf);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"could not calc rx priv buffer size for all TCs %d\n",
			ret);
		जाओ out;
	पूर्ण

	ret = hclge_rx_priv_buf_alloc(hdev, pkt_buf);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "could not alloc rx priv buffer %d\n",
			ret);
		जाओ out;
	पूर्ण

	अगर (hnae3_dev_dcb_supported(hdev)) अणु
		ret = hclge_rx_priv_wl_config(hdev, pkt_buf);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"could not configure rx private waterline %d\n",
				ret);
			जाओ out;
		पूर्ण

		ret = hclge_common_thrd_config(hdev, pkt_buf);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"could not configure common threshold %d\n",
				ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = hclge_common_wl_config(hdev, pkt_buf);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"could not configure common waterline %d\n", ret);

out:
	kमुक्त(pkt_buf);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_init_roce_base_info(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_handle *roce = &vport->roce;
	काष्ठा hnae3_handle *nic = &vport->nic;
	काष्ठा hclge_dev *hdev = vport->back;

	roce->rinfo.num_vectors = vport->back->num_roce_msi;

	अगर (hdev->num_msi < hdev->num_nic_msi + hdev->num_roce_msi)
		वापस -EINVAL;

	roce->rinfo.base_vector = hdev->roce_base_vector;

	roce->rinfo.netdev = nic->kinfo.netdev;
	roce->rinfo.roce_io_base = hdev->hw.io_base;
	roce->rinfo.roce_mem_base = hdev->hw.mem_base;

	roce->pdev = nic->pdev;
	roce->ae_algo = nic->ae_algo;
	roce->numa_node_mask = nic->numa_node_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_init_msi(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	पूर्णांक vectors;
	पूर्णांक i;

	vectors = pci_alloc_irq_vectors(pdev, HNAE3_MIN_VECTOR_NUM,
					hdev->num_msi,
					PCI_IRQ_MSI | PCI_IRQ_MSIX);
	अगर (vectors < 0) अणु
		dev_err(&pdev->dev,
			"failed(%d) to allocate MSI/MSI-X vectors\n",
			vectors);
		वापस vectors;
	पूर्ण
	अगर (vectors < hdev->num_msi)
		dev_warn(&hdev->pdev->dev,
			 "requested %u MSI/MSI-X, but allocated %d MSI/MSI-X\n",
			 hdev->num_msi, vectors);

	hdev->num_msi = vectors;
	hdev->num_msi_left = vectors;

	hdev->base_msi_vector = pdev->irq;
	hdev->roce_base_vector = hdev->base_msi_vector +
				hdev->num_nic_msi;

	hdev->vector_status = devm_kसुस्मृति(&pdev->dev, hdev->num_msi,
					   माप(u16), GFP_KERNEL);
	अगर (!hdev->vector_status) अणु
		pci_मुक्त_irq_vectors(pdev);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < hdev->num_msi; i++)
		hdev->vector_status[i] = HCLGE_INVALID_VPORT;

	hdev->vector_irq = devm_kसुस्मृति(&pdev->dev, hdev->num_msi,
					माप(पूर्णांक), GFP_KERNEL);
	अगर (!hdev->vector_irq) अणु
		pci_मुक्त_irq_vectors(pdev);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 hclge_check_speed_dup(u8 duplex, पूर्णांक speed)
अणु
	अगर (!(speed == HCLGE_MAC_SPEED_10M || speed == HCLGE_MAC_SPEED_100M))
		duplex = HCLGE_MAC_FULL;

	वापस duplex;
पूर्ण

अटल पूर्णांक hclge_cfg_mac_speed_dup_hw(काष्ठा hclge_dev *hdev, पूर्णांक speed,
				      u8 duplex)
अणु
	काष्ठा hclge_config_mac_speed_dup_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	req = (काष्ठा hclge_config_mac_speed_dup_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_SPEED_DUP, false);

	अगर (duplex)
		hnae3_set_bit(req->speed_dup, HCLGE_CFG_DUPLEX_B, 1);

	चयन (speed) अणु
	हाल HCLGE_MAC_SPEED_10M:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 6);
		अवरोध;
	हाल HCLGE_MAC_SPEED_100M:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 7);
		अवरोध;
	हाल HCLGE_MAC_SPEED_1G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 0);
		अवरोध;
	हाल HCLGE_MAC_SPEED_10G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 1);
		अवरोध;
	हाल HCLGE_MAC_SPEED_25G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 2);
		अवरोध;
	हाल HCLGE_MAC_SPEED_40G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 3);
		अवरोध;
	हाल HCLGE_MAC_SPEED_50G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 4);
		अवरोध;
	हाल HCLGE_MAC_SPEED_100G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 5);
		अवरोध;
	हाल HCLGE_MAC_SPEED_200G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 8);
		अवरोध;
	शेष:
		dev_err(&hdev->pdev->dev, "invalid speed (%d)\n", speed);
		वापस -EINVAL;
	पूर्ण

	hnae3_set_bit(req->mac_change_fec_en, HCLGE_CFG_MAC_SPEED_CHANGE_EN_B,
		      1);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"mac speed/duplex config cmd failed %d.\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hclge_cfg_mac_speed_dup(काष्ठा hclge_dev *hdev, पूर्णांक speed, u8 duplex)
अणु
	काष्ठा hclge_mac *mac = &hdev->hw.mac;
	पूर्णांक ret;

	duplex = hclge_check_speed_dup(duplex, speed);
	अगर (!mac->support_स्वतःneg && mac->speed == speed &&
	    mac->duplex == duplex)
		वापस 0;

	ret = hclge_cfg_mac_speed_dup_hw(hdev, speed, duplex);
	अगर (ret)
		वापस ret;

	hdev->hw.mac.speed = speed;
	hdev->hw.mac.duplex = duplex;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_cfg_mac_speed_dup_h(काष्ठा hnae3_handle *handle, पूर्णांक speed,
				     u8 duplex)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस hclge_cfg_mac_speed_dup(hdev, speed, duplex);
पूर्ण

अटल पूर्णांक hclge_set_स्वतःneg_en(काष्ठा hclge_dev *hdev, bool enable)
अणु
	काष्ठा hclge_config_स्वतः_neg_cmd *req;
	काष्ठा hclge_desc desc;
	u32 flag = 0;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_AN_MODE, false);

	req = (काष्ठा hclge_config_स्वतः_neg_cmd *)desc.data;
	अगर (enable)
		hnae3_set_bit(flag, HCLGE_MAC_CFG_AN_EN_B, 1U);
	req->cfg_an_cmd_flag = cpu_to_le32(flag);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "auto neg set cmd failed %d.\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_set_स्वतःneg(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (!hdev->hw.mac.support_स्वतःneg) अणु
		अगर (enable) अणु
			dev_err(&hdev->pdev->dev,
				"autoneg is not supported by current port\n");
			वापस -EOPNOTSUPP;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	वापस hclge_set_स्वतःneg_en(hdev, enable);
पूर्ण

अटल पूर्णांक hclge_get_स्वतःneg(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;

	अगर (phydev)
		वापस phydev->स्वतःneg;

	वापस hdev->hw.mac.स्वतःneg;
पूर्ण

अटल पूर्णांक hclge_restart_स्वतःneg(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	dev_dbg(&hdev->pdev->dev, "restart autoneg\n");

	ret = hclge_notअगरy_client(hdev, HNAE3_DOWN_CLIENT);
	अगर (ret)
		वापस ret;
	वापस hclge_notअगरy_client(hdev, HNAE3_UP_CLIENT);
पूर्ण

अटल पूर्णांक hclge_halt_स्वतःneg(काष्ठा hnae3_handle *handle, bool halt)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (hdev->hw.mac.support_स्वतःneg && hdev->hw.mac.स्वतःneg)
		वापस hclge_set_स्वतःneg_en(hdev, !halt);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_fec_hw(काष्ठा hclge_dev *hdev, u32 fec_mode)
अणु
	काष्ठा hclge_config_fec_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_FEC_MODE, false);

	req = (काष्ठा hclge_config_fec_cmd *)desc.data;
	अगर (fec_mode & BIT(HNAE3_FEC_AUTO))
		hnae3_set_bit(req->fec_mode, HCLGE_MAC_CFG_FEC_AUTO_EN_B, 1);
	अगर (fec_mode & BIT(HNAE3_FEC_RS))
		hnae3_set_field(req->fec_mode, HCLGE_MAC_CFG_FEC_MODE_M,
				HCLGE_MAC_CFG_FEC_MODE_S, HCLGE_MAC_FEC_RS);
	अगर (fec_mode & BIT(HNAE3_FEC_BASER))
		hnae3_set_field(req->fec_mode, HCLGE_MAC_CFG_FEC_MODE_M,
				HCLGE_MAC_CFG_FEC_MODE_S, HCLGE_MAC_FEC_BASER);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "set fec mode failed %d.\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_set_fec(काष्ठा hnae3_handle *handle, u32 fec_mode)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_mac *mac = &hdev->hw.mac;
	पूर्णांक ret;

	अगर (fec_mode && !(mac->fec_ability & fec_mode)) अणु
		dev_err(&hdev->pdev->dev, "unsupported fec mode\n");
		वापस -EINVAL;
	पूर्ण

	ret = hclge_set_fec_hw(hdev, fec_mode);
	अगर (ret)
		वापस ret;

	mac->user_fec_mode = fec_mode | BIT(HNAE3_FEC_USER_DEF);
	वापस 0;
पूर्ण

अटल व्योम hclge_get_fec(काष्ठा hnae3_handle *handle, u8 *fec_ability,
			  u8 *fec_mode)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_mac *mac = &hdev->hw.mac;

	अगर (fec_ability)
		*fec_ability = mac->fec_ability;
	अगर (fec_mode)
		*fec_mode = mac->fec_mode;
पूर्ण

अटल पूर्णांक hclge_mac_init(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_mac *mac = &hdev->hw.mac;
	पूर्णांक ret;

	hdev->support_sfp_query = true;
	hdev->hw.mac.duplex = HCLGE_MAC_FULL;
	ret = hclge_cfg_mac_speed_dup_hw(hdev, hdev->hw.mac.speed,
					 hdev->hw.mac.duplex);
	अगर (ret)
		वापस ret;

	अगर (hdev->hw.mac.support_स्वतःneg) अणु
		ret = hclge_set_स्वतःneg_en(hdev, hdev->hw.mac.स्वतःneg);
		अगर (ret)
			वापस ret;
	पूर्ण

	mac->link = 0;

	अगर (mac->user_fec_mode & BIT(HNAE3_FEC_USER_DEF)) अणु
		ret = hclge_set_fec_hw(hdev, mac->user_fec_mode);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hclge_set_mac_mtu(hdev, hdev->mps);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "set mtu failed ret=%d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_set_शेष_loopback(hdev);
	अगर (ret)
		वापस ret;

	ret = hclge_buffer_alloc(hdev);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"allocate buffer fail, ret=%d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम hclge_mbx_task_schedule(काष्ठा hclge_dev *hdev)
अणु
	अगर (!test_bit(HCLGE_STATE_REMOVING, &hdev->state) &&
	    !test_and_set_bit(HCLGE_STATE_MBX_SERVICE_SCHED, &hdev->state))
		mod_delayed_work_on(cpumask_first(&hdev->affinity_mask),
				    hclge_wq, &hdev->service_task, 0);
पूर्ण

अटल व्योम hclge_reset_task_schedule(काष्ठा hclge_dev *hdev)
अणु
	अगर (!test_bit(HCLGE_STATE_REMOVING, &hdev->state) &&
	    !test_and_set_bit(HCLGE_STATE_RST_SERVICE_SCHED, &hdev->state))
		mod_delayed_work_on(cpumask_first(&hdev->affinity_mask),
				    hclge_wq, &hdev->service_task, 0);
पूर्ण

व्योम hclge_task_schedule(काष्ठा hclge_dev *hdev, अचिन्हित दीर्घ delay_समय)
अणु
	अगर (!test_bit(HCLGE_STATE_REMOVING, &hdev->state) &&
	    !test_bit(HCLGE_STATE_RST_FAIL, &hdev->state))
		mod_delayed_work_on(cpumask_first(&hdev->affinity_mask),
				    hclge_wq, &hdev->service_task,
				    delay_समय);
पूर्ण

अटल पूर्णांक hclge_get_mac_link_status(काष्ठा hclge_dev *hdev, पूर्णांक *link_status)
अणु
	काष्ठा hclge_link_status_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_LINK_STATUS, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "get link status cmd failed %d\n",
			ret);
		वापस ret;
	पूर्ण

	req = (काष्ठा hclge_link_status_cmd *)desc.data;
	*link_status = (req->status & HCLGE_LINK_STATUS_UP_M) > 0 ?
		HCLGE_LINK_STATUS_UP : HCLGE_LINK_STATUS_DOWN;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_mac_phy_link(काष्ठा hclge_dev *hdev, पूर्णांक *link_status)
अणु
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;

	*link_status = HCLGE_LINK_STATUS_DOWN;

	अगर (test_bit(HCLGE_STATE_DOWN, &hdev->state))
		वापस 0;

	अगर (phydev && (phydev->state != PHY_RUNNING || !phydev->link))
		वापस 0;

	वापस hclge_get_mac_link_status(hdev, link_status);
पूर्ण

अटल व्योम hclge_push_link_status(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport;
	पूर्णांक ret;
	u16 i;

	क्रम (i = 0; i < pci_num_vf(hdev->pdev); i++) अणु
		vport = &hdev->vport[i + HCLGE_VF_VPORT_START_NUM];

		अगर (!test_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state) ||
		    vport->vf_info.link_state != IFLA_VF_LINK_STATE_AUTO)
			जारी;

		ret = hclge_push_vf_link_status(vport);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"failed to push link status to vf%u, ret = %d\n",
				i, ret);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hclge_update_link_status(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_handle *rhandle = &hdev->vport[0].roce;
	काष्ठा hnae3_handle *handle = &hdev->vport[0].nic;
	काष्ठा hnae3_client *rclient = hdev->roce_client;
	काष्ठा hnae3_client *client = hdev->nic_client;
	पूर्णांक state;
	पूर्णांक ret;

	अगर (!client)
		वापस;

	अगर (test_and_set_bit(HCLGE_STATE_LINK_UPDATING, &hdev->state))
		वापस;

	ret = hclge_get_mac_phy_link(hdev, &state);
	अगर (ret) अणु
		clear_bit(HCLGE_STATE_LINK_UPDATING, &hdev->state);
		वापस;
	पूर्ण

	अगर (state != hdev->hw.mac.link) अणु
		client->ops->link_status_change(handle, state);
		hclge_config_mac_tnl_पूर्णांक(hdev, state);
		अगर (rclient && rclient->ops->link_status_change)
			rclient->ops->link_status_change(rhandle, state);

		hdev->hw.mac.link = state;
		hclge_push_link_status(hdev);
	पूर्ण

	clear_bit(HCLGE_STATE_LINK_UPDATING, &hdev->state);
पूर्ण

अटल व्योम hclge_update_port_capability(काष्ठा hclge_dev *hdev,
					 काष्ठा hclge_mac *mac)
अणु
	अगर (hnae3_dev_fec_supported(hdev))
		/* update fec ability by speed */
		hclge_convert_setting_fec(mac);

	/* firmware can not identअगरy back plane type, the media type
	 * पढ़ो from configuration can help deal it
	 */
	अगर (mac->media_type == HNAE3_MEDIA_TYPE_BACKPLANE &&
	    mac->module_type == HNAE3_MODULE_TYPE_UNKNOWN)
		mac->module_type = HNAE3_MODULE_TYPE_KR;
	अन्यथा अगर (mac->media_type == HNAE3_MEDIA_TYPE_COPPER)
		mac->module_type = HNAE3_MODULE_TYPE_TP;

	अगर (mac->support_स्वतःneg) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, mac->supported);
		linkmode_copy(mac->advertising, mac->supported);
	पूर्ण अन्यथा अणु
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				   mac->supported);
		linkmode_zero(mac->advertising);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_get_sfp_speed(काष्ठा hclge_dev *hdev, u32 *speed)
अणु
	काष्ठा hclge_sfp_info_cmd *resp;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_GET_SFP_INFO, true);
	resp = (काष्ठा hclge_sfp_info_cmd *)desc.data;
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret == -EOPNOTSUPP) अणु
		dev_warn(&hdev->pdev->dev,
			 "IMP do not support get SFP speed %d\n", ret);
		वापस ret;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "get sfp speed failed %d\n", ret);
		वापस ret;
	पूर्ण

	*speed = le32_to_cpu(resp->speed);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_sfp_info(काष्ठा hclge_dev *hdev, काष्ठा hclge_mac *mac)
अणु
	काष्ठा hclge_sfp_info_cmd *resp;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_GET_SFP_INFO, true);
	resp = (काष्ठा hclge_sfp_info_cmd *)desc.data;

	resp->query_type = QUERY_ACTIVE_SPEED;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret == -EOPNOTSUPP) अणु
		dev_warn(&hdev->pdev->dev,
			 "IMP does not support get SFP info %d\n", ret);
		वापस ret;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "get sfp info failed %d\n", ret);
		वापस ret;
	पूर्ण

	/* In some हाल, mac speed get from IMP may be 0, it shouldn't be
	 * set to mac->speed.
	 */
	अगर (!le32_to_cpu(resp->speed))
		वापस 0;

	mac->speed = le32_to_cpu(resp->speed);
	/* अगर resp->speed_ability is 0, it means it's an old version
	 * firmware, करो not update these params
	 */
	अगर (resp->speed_ability) अणु
		mac->module_type = le32_to_cpu(resp->module_type);
		mac->speed_ability = le32_to_cpu(resp->speed_ability);
		mac->स्वतःneg = resp->स्वतःneg;
		mac->support_स्वतःneg = resp->स्वतःneg_ability;
		mac->speed_type = QUERY_ACTIVE_SPEED;
		अगर (!resp->active_fec)
			mac->fec_mode = 0;
		अन्यथा
			mac->fec_mode = BIT(resp->active_fec);
	पूर्ण अन्यथा अणु
		mac->speed_type = QUERY_SFP_SPEED;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_phy_link_ksettings(काष्ठा hnae3_handle *handle,
					काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा hclge_desc desc[HCLGE_PHY_LINK_SETTING_BD_NUM];
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_phy_link_ksetting_0_cmd *req0;
	काष्ठा hclge_phy_link_ksetting_1_cmd *req1;
	u32 supported, advertising, lp_advertising;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_PHY_LINK_KSETTING,
				   true);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_OPC_PHY_LINK_KSETTING,
				   true);

	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_PHY_LINK_SETTING_BD_NUM);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get phy link ksetting, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	req0 = (काष्ठा hclge_phy_link_ksetting_0_cmd *)desc[0].data;
	cmd->base.स्वतःneg = req0->स्वतःneg;
	cmd->base.speed = le32_to_cpu(req0->speed);
	cmd->base.duplex = req0->duplex;
	cmd->base.port = req0->port;
	cmd->base.transceiver = req0->transceiver;
	cmd->base.phy_address = req0->phy_address;
	cmd->base.eth_tp_mdix = req0->eth_tp_mdix;
	cmd->base.eth_tp_mdix_ctrl = req0->eth_tp_mdix_ctrl;
	supported = le32_to_cpu(req0->supported);
	advertising = le32_to_cpu(req0->advertising);
	lp_advertising = le32_to_cpu(req0->lp_advertising);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.lp_advertising,
						lp_advertising);

	req1 = (काष्ठा hclge_phy_link_ksetting_1_cmd *)desc[1].data;
	cmd->base.master_slave_cfg = req1->master_slave_cfg;
	cmd->base.master_slave_state = req1->master_slave_state;

	वापस 0;
पूर्ण

अटल पूर्णांक
hclge_set_phy_link_ksettings(काष्ठा hnae3_handle *handle,
			     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा hclge_desc desc[HCLGE_PHY_LINK_SETTING_BD_NUM];
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_phy_link_ksetting_0_cmd *req0;
	काष्ठा hclge_phy_link_ksetting_1_cmd *req1;
	काष्ठा hclge_dev *hdev = vport->back;
	u32 advertising;
	पूर्णांक ret;

	अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE &&
	    ((cmd->base.speed != SPEED_100 && cmd->base.speed != SPEED_10) ||
	     (cmd->base.duplex != DUPLEX_HALF &&
	      cmd->base.duplex != DUPLEX_FULL)))
		वापस -EINVAL;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_PHY_LINK_KSETTING,
				   false);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_OPC_PHY_LINK_KSETTING,
				   false);

	req0 = (काष्ठा hclge_phy_link_ksetting_0_cmd *)desc[0].data;
	req0->स्वतःneg = cmd->base.स्वतःneg;
	req0->speed = cpu_to_le32(cmd->base.speed);
	req0->duplex = cmd->base.duplex;
	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);
	req0->advertising = cpu_to_le32(advertising);
	req0->eth_tp_mdix_ctrl = cmd->base.eth_tp_mdix_ctrl;

	req1 = (काष्ठा hclge_phy_link_ksetting_1_cmd *)desc[1].data;
	req1->master_slave_cfg = cmd->base.master_slave_cfg;

	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_PHY_LINK_SETTING_BD_NUM);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to set phy link ksettings, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	hdev->hw.mac.स्वतःneg = cmd->base.स्वतःneg;
	hdev->hw.mac.speed = cmd->base.speed;
	hdev->hw.mac.duplex = cmd->base.duplex;
	linkmode_copy(hdev->hw.mac.advertising, cmd->link_modes.advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_update_tp_port_info(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा ethtool_link_ksettings cmd;
	पूर्णांक ret;

	अगर (!hnae3_dev_phy_imp_supported(hdev))
		वापस 0;

	ret = hclge_get_phy_link_ksettings(&hdev->vport->nic, &cmd);
	अगर (ret)
		वापस ret;

	hdev->hw.mac.स्वतःneg = cmd.base.स्वतःneg;
	hdev->hw.mac.speed = cmd.base.speed;
	hdev->hw.mac.duplex = cmd.base.duplex;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_tp_port_init(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा ethtool_link_ksettings cmd;

	अगर (!hnae3_dev_phy_imp_supported(hdev))
		वापस 0;

	cmd.base.स्वतःneg = hdev->hw.mac.स्वतःneg;
	cmd.base.speed = hdev->hw.mac.speed;
	cmd.base.duplex = hdev->hw.mac.duplex;
	linkmode_copy(cmd.link_modes.advertising, hdev->hw.mac.advertising);

	वापस hclge_set_phy_link_ksettings(&hdev->vport->nic, &cmd);
पूर्ण

अटल पूर्णांक hclge_update_port_info(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_mac *mac = &hdev->hw.mac;
	पूर्णांक speed = HCLGE_MAC_SPEED_UNKNOWN;
	पूर्णांक ret;

	/* get the port info from SFP cmd अगर not copper port */
	अगर (mac->media_type == HNAE3_MEDIA_TYPE_COPPER)
		वापस hclge_update_tp_port_info(hdev);

	/* अगर IMP करोes not support get SFP/qSFP info, वापस directly */
	अगर (!hdev->support_sfp_query)
		वापस 0;

	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2)
		ret = hclge_get_sfp_info(hdev, mac);
	अन्यथा
		ret = hclge_get_sfp_speed(hdev, &speed);

	अगर (ret == -EOPNOTSUPP) अणु
		hdev->support_sfp_query = false;
		वापस ret;
	पूर्ण अन्यथा अगर (ret) अणु
		वापस ret;
	पूर्ण

	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2) अणु
		अगर (mac->speed_type == QUERY_ACTIVE_SPEED) अणु
			hclge_update_port_capability(hdev, mac);
			वापस 0;
		पूर्ण
		वापस hclge_cfg_mac_speed_dup(hdev, mac->speed,
					       HCLGE_MAC_FULL);
	पूर्ण अन्यथा अणु
		अगर (speed == HCLGE_MAC_SPEED_UNKNOWN)
			वापस 0; /* करो nothing अगर no SFP */

		/* must config full duplex क्रम SFP */
		वापस hclge_cfg_mac_speed_dup(hdev, speed, HCLGE_MAC_FULL);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_get_status(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	hclge_update_link_status(hdev);

	वापस hdev->hw.mac.link;
पूर्ण

अटल काष्ठा hclge_vport *hclge_get_vf_vport(काष्ठा hclge_dev *hdev, पूर्णांक vf)
अणु
	अगर (!pci_num_vf(hdev->pdev)) अणु
		dev_err(&hdev->pdev->dev,
			"SRIOV is disabled, can not get vport(%d) info.\n", vf);
		वापस शून्य;
	पूर्ण

	अगर (vf < 0 || vf >= pci_num_vf(hdev->pdev)) अणु
		dev_err(&hdev->pdev->dev,
			"vf id(%d) is out of range(0 <= vfid < %d)\n",
			vf, pci_num_vf(hdev->pdev));
		वापस शून्य;
	पूर्ण

	/* VF start from 1 in vport */
	vf += HCLGE_VF_VPORT_START_NUM;
	वापस &hdev->vport[vf];
पूर्ण

अटल पूर्णांक hclge_get_vf_config(काष्ठा hnae3_handle *handle, पूर्णांक vf,
			       काष्ठा अगरla_vf_info *ivf)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	vport = hclge_get_vf_vport(hdev, vf);
	अगर (!vport)
		वापस -EINVAL;

	ivf->vf = vf;
	ivf->linkstate = vport->vf_info.link_state;
	ivf->spoofchk = vport->vf_info.spoofchk;
	ivf->trusted = vport->vf_info.trusted;
	ivf->min_tx_rate = 0;
	ivf->max_tx_rate = vport->vf_info.max_tx_rate;
	ivf->vlan = vport->port_base_vlan_cfg.vlan_info.vlan_tag;
	ivf->vlan_proto = htons(vport->port_base_vlan_cfg.vlan_info.vlan_proto);
	ivf->qos = vport->port_base_vlan_cfg.vlan_info.qos;
	ether_addr_copy(ivf->mac, vport->vf_info.mac);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_vf_link_state(काष्ठा hnae3_handle *handle, पूर्णांक vf,
				   पूर्णांक link_state)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक link_state_old;
	पूर्णांक ret;

	vport = hclge_get_vf_vport(hdev, vf);
	अगर (!vport)
		वापस -EINVAL;

	link_state_old = vport->vf_info.link_state;
	vport->vf_info.link_state = link_state;

	ret = hclge_push_vf_link_status(vport);
	अगर (ret) अणु
		vport->vf_info.link_state = link_state_old;
		dev_err(&hdev->pdev->dev,
			"failed to push vf%d link status, ret = %d\n", vf, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 hclge_check_event_cause(काष्ठा hclge_dev *hdev, u32 *clearval)
अणु
	u32 cmdq_src_reg, msix_src_reg;

	/* fetch the events from their corresponding regs */
	cmdq_src_reg = hclge_पढ़ो_dev(&hdev->hw, HCLGE_VECTOR0_CMDQ_SRC_REG);
	msix_src_reg = hclge_पढ़ो_dev(&hdev->hw, HCLGE_MISC_VECTOR_INT_STS);

	/* Assumption: If by any chance reset and mailbox events are reported
	 * together then we will only process reset event in this go and will
	 * defer the processing of the mailbox events. Since, we would have not
	 * cleared RX CMDQ event this समय we would receive again another
	 * पूर्णांकerrupt from H/W just क्रम the mailbox.
	 *
	 * check क्रम vector0 reset event sources
	 */
	अगर (BIT(HCLGE_VECTOR0_IMPRESET_INT_B) & msix_src_reg) अणु
		dev_info(&hdev->pdev->dev, "IMP reset interrupt\n");
		set_bit(HNAE3_IMP_RESET, &hdev->reset_pending);
		set_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);
		*clearval = BIT(HCLGE_VECTOR0_IMPRESET_INT_B);
		hdev->rst_stats.imp_rst_cnt++;
		वापस HCLGE_VECTOR0_EVENT_RST;
	पूर्ण

	अगर (BIT(HCLGE_VECTOR0_GLOBALRESET_INT_B) & msix_src_reg) अणु
		dev_info(&hdev->pdev->dev, "global reset interrupt\n");
		set_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);
		set_bit(HNAE3_GLOBAL_RESET, &hdev->reset_pending);
		*clearval = BIT(HCLGE_VECTOR0_GLOBALRESET_INT_B);
		hdev->rst_stats.global_rst_cnt++;
		वापस HCLGE_VECTOR0_EVENT_RST;
	पूर्ण

	/* check क्रम vector0 msix event source */
	अगर (msix_src_reg & HCLGE_VECTOR0_REG_MSIX_MASK) अणु
		*clearval = msix_src_reg;
		वापस HCLGE_VECTOR0_EVENT_ERR;
	पूर्ण

	/* check क्रम vector0 mailbox(=CMDQ RX) event source */
	अगर (BIT(HCLGE_VECTOR0_RX_CMDQ_INT_B) & cmdq_src_reg) अणु
		cmdq_src_reg &= ~BIT(HCLGE_VECTOR0_RX_CMDQ_INT_B);
		*clearval = cmdq_src_reg;
		वापस HCLGE_VECTOR0_EVENT_MBX;
	पूर्ण

	/* prपूर्णांक other vector0 event source */
	dev_info(&hdev->pdev->dev,
		 "CMDQ INT status:0x%x, other INT status:0x%x\n",
		 cmdq_src_reg, msix_src_reg);
	*clearval = msix_src_reg;

	वापस HCLGE_VECTOR0_EVENT_OTHER;
पूर्ण

अटल व्योम hclge_clear_event_cause(काष्ठा hclge_dev *hdev, u32 event_type,
				    u32 regclr)
अणु
	चयन (event_type) अणु
	हाल HCLGE_VECTOR0_EVENT_RST:
		hclge_ग_लिखो_dev(&hdev->hw, HCLGE_MISC_RESET_STS_REG, regclr);
		अवरोध;
	हाल HCLGE_VECTOR0_EVENT_MBX:
		hclge_ग_लिखो_dev(&hdev->hw, HCLGE_VECTOR0_CMDQ_SRC_REG, regclr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hclge_clear_all_event_cause(काष्ठा hclge_dev *hdev)
अणु
	hclge_clear_event_cause(hdev, HCLGE_VECTOR0_EVENT_RST,
				BIT(HCLGE_VECTOR0_GLOBALRESET_INT_B) |
				BIT(HCLGE_VECTOR0_CORERESET_INT_B) |
				BIT(HCLGE_VECTOR0_IMPRESET_INT_B));
	hclge_clear_event_cause(hdev, HCLGE_VECTOR0_EVENT_MBX, 0);
पूर्ण

अटल व्योम hclge_enable_vector(काष्ठा hclge_misc_vector *vector, bool enable)
अणु
	ग_लिखोl(enable ? 1 : 0, vector->addr);
पूर्ण

अटल irqवापस_t hclge_misc_irq_handle(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hclge_dev *hdev = data;
	u32 clearval = 0;
	u32 event_cause;

	hclge_enable_vector(&hdev->misc_vector, false);
	event_cause = hclge_check_event_cause(hdev, &clearval);

	/* vector 0 पूर्णांकerrupt is shared with reset and mailbox source events.*/
	चयन (event_cause) अणु
	हाल HCLGE_VECTOR0_EVENT_ERR:
		/* we करो not know what type of reset is required now. This could
		 * only be decided after we fetch the type of errors which
		 * caused this event. Thereक्रमe, we will करो below क्रम now:
		 * 1. Assert HNAE3_UNKNOWN_RESET type of reset. This means we
		 *    have defered type of reset to be used.
		 * 2. Schedule the reset service task.
		 * 3. When service task receives  HNAE3_UNKNOWN_RESET type it
		 *    will fetch the correct type of reset.  This would be करोne
		 *    by first decoding the types of errors.
		 */
		set_bit(HNAE3_UNKNOWN_RESET, &hdev->reset_request);
		fallthrough;
	हाल HCLGE_VECTOR0_EVENT_RST:
		hclge_reset_task_schedule(hdev);
		अवरोध;
	हाल HCLGE_VECTOR0_EVENT_MBX:
		/* If we are here then,
		 * 1. Either we are not handling any mbx task and we are not
		 *    scheduled as well
		 *                        OR
		 * 2. We could be handling a mbx task but nothing more is
		 *    scheduled.
		 * In both हालs, we should schedule mbx task as there are more
		 * mbx messages reported by this पूर्णांकerrupt.
		 */
		hclge_mbx_task_schedule(hdev);
		अवरोध;
	शेष:
		dev_warn(&hdev->pdev->dev,
			 "received unknown or unhandled event of vector0\n");
		अवरोध;
	पूर्ण

	hclge_clear_event_cause(hdev, event_cause, clearval);

	/* Enable पूर्णांकerrupt अगर it is not cause by reset. And when
	 * clearval equal to 0, it means पूर्णांकerrupt status may be
	 * cleared by hardware beक्रमe driver पढ़ोs status रेजिस्टर.
	 * For this हाल, vector0 पूर्णांकerrupt also should be enabled.
	 */
	अगर (!clearval ||
	    event_cause == HCLGE_VECTOR0_EVENT_MBX) अणु
		hclge_enable_vector(&hdev->misc_vector, true);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hclge_मुक्त_vector(काष्ठा hclge_dev *hdev, पूर्णांक vector_id)
अणु
	अगर (hdev->vector_status[vector_id] == HCLGE_INVALID_VPORT) अणु
		dev_warn(&hdev->pdev->dev,
			 "vector(vector_id %d) has been freed.\n", vector_id);
		वापस;
	पूर्ण

	hdev->vector_status[vector_id] = HCLGE_INVALID_VPORT;
	hdev->num_msi_left += 1;
	hdev->num_msi_used -= 1;
पूर्ण

अटल व्योम hclge_get_misc_vector(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_misc_vector *vector = &hdev->misc_vector;

	vector->vector_irq = pci_irq_vector(hdev->pdev, 0);

	vector->addr = hdev->hw.io_base + HCLGE_MISC_VECTOR_REG_BASE;
	hdev->vector_status[0] = 0;

	hdev->num_msi_left -= 1;
	hdev->num_msi_used += 1;
पूर्ण

अटल व्योम hclge_irq_affinity_notअगरy(काष्ठा irq_affinity_notअगरy *notअगरy,
				      स्थिर cpumask_t *mask)
अणु
	काष्ठा hclge_dev *hdev = container_of(notअगरy, काष्ठा hclge_dev,
					      affinity_notअगरy);

	cpumask_copy(&hdev->affinity_mask, mask);
पूर्ण

अटल व्योम hclge_irq_affinity_release(काष्ठा kref *ref)
अणु
पूर्ण

अटल व्योम hclge_misc_affinity_setup(काष्ठा hclge_dev *hdev)
अणु
	irq_set_affinity_hपूर्णांक(hdev->misc_vector.vector_irq,
			      &hdev->affinity_mask);

	hdev->affinity_notअगरy.notअगरy = hclge_irq_affinity_notअगरy;
	hdev->affinity_notअगरy.release = hclge_irq_affinity_release;
	irq_set_affinity_notअगरier(hdev->misc_vector.vector_irq,
				  &hdev->affinity_notअगरy);
पूर्ण

अटल व्योम hclge_misc_affinity_tearकरोwn(काष्ठा hclge_dev *hdev)
अणु
	irq_set_affinity_notअगरier(hdev->misc_vector.vector_irq, शून्य);
	irq_set_affinity_hपूर्णांक(hdev->misc_vector.vector_irq, शून्य);
पूर्ण

अटल पूर्णांक hclge_misc_irq_init(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	hclge_get_misc_vector(hdev);

	/* this would be explicitly मुक्तd in the end */
	snम_लिखो(hdev->misc_vector.name, HNAE3_INT_NAME_LEN, "%s-misc-%s",
		 HCLGE_NAME, pci_name(hdev->pdev));
	ret = request_irq(hdev->misc_vector.vector_irq, hclge_misc_irq_handle,
			  0, hdev->misc_vector.name, hdev);
	अगर (ret) अणु
		hclge_मुक्त_vector(hdev, 0);
		dev_err(&hdev->pdev->dev, "request misc irq(%d) fail\n",
			hdev->misc_vector.vector_irq);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hclge_misc_irq_uninit(काष्ठा hclge_dev *hdev)
अणु
	मुक्त_irq(hdev->misc_vector.vector_irq, hdev);
	hclge_मुक्त_vector(hdev, 0);
पूर्ण

पूर्णांक hclge_notअगरy_client(काष्ठा hclge_dev *hdev,
			क्रमागत hnae3_reset_notअगरy_type type)
अणु
	काष्ठा hnae3_handle *handle = &hdev->vport[0].nic;
	काष्ठा hnae3_client *client = hdev->nic_client;
	पूर्णांक ret;

	अगर (!test_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state) || !client)
		वापस 0;

	अगर (!client->ops->reset_notअगरy)
		वापस -EOPNOTSUPP;

	ret = client->ops->reset_notअगरy(handle, type);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "notify nic client failed %d(%d)\n",
			type, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_notअगरy_roce_client(काष्ठा hclge_dev *hdev,
				    क्रमागत hnae3_reset_notअगरy_type type)
अणु
	काष्ठा hnae3_handle *handle = &hdev->vport[0].roce;
	काष्ठा hnae3_client *client = hdev->roce_client;
	पूर्णांक ret;

	अगर (!test_bit(HCLGE_STATE_ROCE_REGISTERED, &hdev->state) || !client)
		वापस 0;

	अगर (!client->ops->reset_notअगरy)
		वापस -EOPNOTSUPP;

	ret = client->ops->reset_notअगरy(handle, type);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "notify roce client failed %d(%d)",
			type, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_reset_रुको(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_RESET_WATI_MS	100
#घोषणा HCLGE_RESET_WAIT_CNT	350

	u32 val, reg, reg_bit;
	u32 cnt = 0;

	चयन (hdev->reset_type) अणु
	हाल HNAE3_IMP_RESET:
		reg = HCLGE_GLOBAL_RESET_REG;
		reg_bit = HCLGE_IMP_RESET_BIT;
		अवरोध;
	हाल HNAE3_GLOBAL_RESET:
		reg = HCLGE_GLOBAL_RESET_REG;
		reg_bit = HCLGE_GLOBAL_RESET_BIT;
		अवरोध;
	हाल HNAE3_FUNC_RESET:
		reg = HCLGE_FUN_RST_ING;
		reg_bit = HCLGE_FUN_RST_ING_B;
		अवरोध;
	शेष:
		dev_err(&hdev->pdev->dev,
			"Wait for unsupported reset type: %d\n",
			hdev->reset_type);
		वापस -EINVAL;
	पूर्ण

	val = hclge_पढ़ो_dev(&hdev->hw, reg);
	जबतक (hnae3_get_bit(val, reg_bit) && cnt < HCLGE_RESET_WAIT_CNT) अणु
		msleep(HCLGE_RESET_WATI_MS);
		val = hclge_पढ़ो_dev(&hdev->hw, reg);
		cnt++;
	पूर्ण

	अगर (cnt >= HCLGE_RESET_WAIT_CNT) अणु
		dev_warn(&hdev->pdev->dev,
			 "Wait for reset timeout: %d\n", hdev->reset_type);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_vf_rst(काष्ठा hclge_dev *hdev, पूर्णांक func_id, bool reset)
अणु
	काष्ठा hclge_vf_rst_cmd *req;
	काष्ठा hclge_desc desc;

	req = (काष्ठा hclge_vf_rst_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_GBL_RST_STATUS, false);
	req->dest_vfid = func_id;

	अगर (reset)
		req->vf_rst = 0x1;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_set_all_vf_rst(काष्ठा hclge_dev *hdev, bool reset)
अणु
	पूर्णांक i;

	क्रम (i = HCLGE_VF_VPORT_START_NUM; i < hdev->num_alloc_vport; i++) अणु
		काष्ठा hclge_vport *vport = &hdev->vport[i];
		पूर्णांक ret;

		/* Send cmd to set/clear VF's FUNC_RST_ING */
		ret = hclge_set_vf_rst(hdev, vport->vport_id, reset);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"set vf(%u) rst failed %d!\n",
				vport->vport_id, ret);
			वापस ret;
		पूर्ण

		अगर (!reset || !test_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state))
			जारी;

		/* Inक्रमm VF to process the reset.
		 * hclge_inक्रमm_reset_निश्चित_to_vf may fail अगर VF
		 * driver is not loaded.
		 */
		ret = hclge_inक्रमm_reset_निश्चित_to_vf(vport);
		अगर (ret)
			dev_warn(&hdev->pdev->dev,
				 "inform reset to vf(%u) failed %d!\n",
				 vport->vport_id, ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclge_mailbox_service_task(काष्ठा hclge_dev *hdev)
अणु
	अगर (!test_and_clear_bit(HCLGE_STATE_MBX_SERVICE_SCHED, &hdev->state) ||
	    test_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state) ||
	    test_and_set_bit(HCLGE_STATE_MBX_HANDLING, &hdev->state))
		वापस;

	hclge_mbx_handler(hdev);

	clear_bit(HCLGE_STATE_MBX_HANDLING, &hdev->state);
पूर्ण

अटल व्योम hclge_func_reset_sync_vf(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_pf_rst_sync_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक cnt = 0;
	पूर्णांक ret;

	req = (काष्ठा hclge_pf_rst_sync_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_VF_RST_RDY, true);

	करो अणु
		/* vf need to करोwn netdev by mbx during PF or FLR reset */
		hclge_mailbox_service_task(hdev);

		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		/* क्रम compatible with old firmware, रुको
		 * 100 ms क्रम VF to stop IO
		 */
		अगर (ret == -EOPNOTSUPP) अणु
			msleep(HCLGE_RESET_SYNC_TIME);
			वापस;
		पूर्ण अन्यथा अगर (ret) अणु
			dev_warn(&hdev->pdev->dev, "sync with VF fail %d!\n",
				 ret);
			वापस;
		पूर्ण अन्यथा अगर (req->all_vf_पढ़ोy) अणु
			वापस;
		पूर्ण
		msleep(HCLGE_PF_RESET_SYNC_TIME);
		hclge_cmd_reuse_desc(&desc, true);
	पूर्ण जबतक (cnt++ < HCLGE_PF_RESET_SYNC_CNT);

	dev_warn(&hdev->pdev->dev, "sync with VF timeout!\n");
पूर्ण

व्योम hclge_report_hw_error(काष्ठा hclge_dev *hdev,
			   क्रमागत hnae3_hw_error_type type)
अणु
	काष्ठा hnae3_client *client = hdev->nic_client;

	अगर (!client || !client->ops->process_hw_error ||
	    !test_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state))
		वापस;

	client->ops->process_hw_error(&hdev->vport[0].nic, type);
पूर्ण

अटल व्योम hclge_handle_imp_error(काष्ठा hclge_dev *hdev)
अणु
	u32 reg_val;

	reg_val = hclge_पढ़ो_dev(&hdev->hw, HCLGE_PF_OTHER_INT_REG);
	अगर (reg_val & BIT(HCLGE_VECTOR0_IMP_RD_POISON_B)) अणु
		hclge_report_hw_error(hdev, HNAE3_IMP_RD_POISON_ERROR);
		reg_val &= ~BIT(HCLGE_VECTOR0_IMP_RD_POISON_B);
		hclge_ग_लिखो_dev(&hdev->hw, HCLGE_PF_OTHER_INT_REG, reg_val);
	पूर्ण

	अगर (reg_val & BIT(HCLGE_VECTOR0_IMP_CMDQ_ERR_B)) अणु
		hclge_report_hw_error(hdev, HNAE3_CMDQ_ECC_ERROR);
		reg_val &= ~BIT(HCLGE_VECTOR0_IMP_CMDQ_ERR_B);
		hclge_ग_लिखो_dev(&hdev->hw, HCLGE_PF_OTHER_INT_REG, reg_val);
	पूर्ण
पूर्ण

पूर्णांक hclge_func_reset_cmd(काष्ठा hclge_dev *hdev, पूर्णांक func_id)
अणु
	काष्ठा hclge_desc desc;
	काष्ठा hclge_reset_cmd *req = (काष्ठा hclge_reset_cmd *)desc.data;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_RST_TRIGGER, false);
	hnae3_set_bit(req->mac_func_reset, HCLGE_CFG_RESET_FUNC_B, 1);
	req->fun_reset_vfid = func_id;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"send function reset cmd fail, status =%d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम hclge_करो_reset(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_handle *handle = &hdev->vport[0].nic;
	काष्ठा pci_dev *pdev = hdev->pdev;
	u32 val;

	अगर (hclge_get_hw_reset_stat(handle)) अणु
		dev_info(&pdev->dev, "hardware reset not finish\n");
		dev_info(&pdev->dev, "func_rst_reg:0x%x, global_rst_reg:0x%x\n",
			 hclge_पढ़ो_dev(&hdev->hw, HCLGE_FUN_RST_ING),
			 hclge_पढ़ो_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG));
		वापस;
	पूर्ण

	चयन (hdev->reset_type) अणु
	हाल HNAE3_GLOBAL_RESET:
		dev_info(&pdev->dev, "global reset requested\n");
		val = hclge_पढ़ो_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG);
		hnae3_set_bit(val, HCLGE_GLOBAL_RESET_BIT, 1);
		hclge_ग_लिखो_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG, val);
		अवरोध;
	हाल HNAE3_FUNC_RESET:
		dev_info(&pdev->dev, "PF reset requested\n");
		/* schedule again to check later */
		set_bit(HNAE3_FUNC_RESET, &hdev->reset_pending);
		hclge_reset_task_schedule(hdev);
		अवरोध;
	शेष:
		dev_warn(&pdev->dev,
			 "unsupported reset type: %d\n", hdev->reset_type);
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत hnae3_reset_type hclge_get_reset_level(काष्ठा hnae3_ae_dev *ae_dev,
						   अचिन्हित दीर्घ *addr)
अणु
	क्रमागत hnae3_reset_type rst_level = HNAE3_NONE_RESET;
	काष्ठा hclge_dev *hdev = ae_dev->priv;

	/* first, resolve any unknown reset type to the known type(s) */
	अगर (test_bit(HNAE3_UNKNOWN_RESET, addr)) अणु
		u32 msix_sts_reg = hclge_पढ़ो_dev(&hdev->hw,
					HCLGE_MISC_VECTOR_INT_STS);
		/* we will पूर्णांकentionally ignore any errors from this function
		 *  as we will end up in *some* reset request in any हाल
		 */
		अगर (hclge_handle_hw_msix_error(hdev, addr))
			dev_info(&hdev->pdev->dev, "received msix interrupt 0x%x\n",
				 msix_sts_reg);

		clear_bit(HNAE3_UNKNOWN_RESET, addr);
		/* We defered the clearing of the error event which caused
		 * पूर्णांकerrupt since it was not posssible to करो that in
		 * पूर्णांकerrupt context (and this is the reason we पूर्णांकroduced
		 * new UNKNOWN reset type). Now, the errors have been
		 * handled and cleared in hardware we can safely enable
		 * पूर्णांकerrupts. This is an exception to the norm.
		 */
		hclge_enable_vector(&hdev->misc_vector, true);
	पूर्ण

	/* वापस the highest priority reset level amongst all */
	अगर (test_bit(HNAE3_IMP_RESET, addr)) अणु
		rst_level = HNAE3_IMP_RESET;
		clear_bit(HNAE3_IMP_RESET, addr);
		clear_bit(HNAE3_GLOBAL_RESET, addr);
		clear_bit(HNAE3_FUNC_RESET, addr);
	पूर्ण अन्यथा अगर (test_bit(HNAE3_GLOBAL_RESET, addr)) अणु
		rst_level = HNAE3_GLOBAL_RESET;
		clear_bit(HNAE3_GLOBAL_RESET, addr);
		clear_bit(HNAE3_FUNC_RESET, addr);
	पूर्ण अन्यथा अगर (test_bit(HNAE3_FUNC_RESET, addr)) अणु
		rst_level = HNAE3_FUNC_RESET;
		clear_bit(HNAE3_FUNC_RESET, addr);
	पूर्ण अन्यथा अगर (test_bit(HNAE3_FLR_RESET, addr)) अणु
		rst_level = HNAE3_FLR_RESET;
		clear_bit(HNAE3_FLR_RESET, addr);
	पूर्ण

	अगर (hdev->reset_type != HNAE3_NONE_RESET &&
	    rst_level < hdev->reset_type)
		वापस HNAE3_NONE_RESET;

	वापस rst_level;
पूर्ण

अटल व्योम hclge_clear_reset_cause(काष्ठा hclge_dev *hdev)
अणु
	u32 clearval = 0;

	चयन (hdev->reset_type) अणु
	हाल HNAE3_IMP_RESET:
		clearval = BIT(HCLGE_VECTOR0_IMPRESET_INT_B);
		अवरोध;
	हाल HNAE3_GLOBAL_RESET:
		clearval = BIT(HCLGE_VECTOR0_GLOBALRESET_INT_B);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!clearval)
		वापस;

	/* For revision 0x20, the reset पूर्णांकerrupt source
	 * can only be cleared after hardware reset करोne
	 */
	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		hclge_ग_लिखो_dev(&hdev->hw, HCLGE_MISC_RESET_STS_REG,
				clearval);

	hclge_enable_vector(&hdev->misc_vector, true);
पूर्ण

अटल व्योम hclge_reset_handshake(काष्ठा hclge_dev *hdev, bool enable)
अणु
	u32 reg_val;

	reg_val = hclge_पढ़ो_dev(&hdev->hw, HCLGE_NIC_CSQ_DEPTH_REG);
	अगर (enable)
		reg_val |= HCLGE_NIC_SW_RST_RDY;
	अन्यथा
		reg_val &= ~HCLGE_NIC_SW_RST_RDY;

	hclge_ग_लिखो_dev(&hdev->hw, HCLGE_NIC_CSQ_DEPTH_REG, reg_val);
पूर्ण

अटल पूर्णांक hclge_func_reset_notअगरy_vf(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_set_all_vf_rst(hdev, true);
	अगर (ret)
		वापस ret;

	hclge_func_reset_sync_vf(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_reset_prepare_रुको(काष्ठा hclge_dev *hdev)
अणु
	u32 reg_val;
	पूर्णांक ret = 0;

	चयन (hdev->reset_type) अणु
	हाल HNAE3_FUNC_RESET:
		ret = hclge_func_reset_notअगरy_vf(hdev);
		अगर (ret)
			वापस ret;

		ret = hclge_func_reset_cmd(hdev, 0);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"asserting function reset fail %d!\n", ret);
			वापस ret;
		पूर्ण

		/* After perक्रमmaning pf reset, it is not necessary to करो the
		 * mailbox handling or send any command to firmware, because
		 * any mailbox handling or command to firmware is only valid
		 * after hclge_cmd_init is called.
		 */
		set_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);
		hdev->rst_stats.pf_rst_cnt++;
		अवरोध;
	हाल HNAE3_FLR_RESET:
		ret = hclge_func_reset_notअगरy_vf(hdev);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल HNAE3_IMP_RESET:
		hclge_handle_imp_error(hdev);
		reg_val = hclge_पढ़ो_dev(&hdev->hw, HCLGE_PF_OTHER_INT_REG);
		hclge_ग_लिखो_dev(&hdev->hw, HCLGE_PF_OTHER_INT_REG,
				BIT(HCLGE_VECTOR0_IMP_RESET_INT_B) | reg_val);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* inक्रमm hardware that preparatory work is करोne */
	msleep(HCLGE_RESET_SYNC_TIME);
	hclge_reset_handshake(hdev, true);
	dev_info(&hdev->pdev->dev, "prepare wait ok\n");

	वापस ret;
पूर्ण

अटल bool hclge_reset_err_handle(काष्ठा hclge_dev *hdev)
अणु
#घोषणा MAX_RESET_FAIL_CNT 5

	अगर (hdev->reset_pending) अणु
		dev_info(&hdev->pdev->dev, "Reset pending %lu\n",
			 hdev->reset_pending);
		वापस true;
	पूर्ण अन्यथा अगर (hclge_पढ़ो_dev(&hdev->hw, HCLGE_MISC_VECTOR_INT_STS) &
		   HCLGE_RESET_INT_M) अणु
		dev_info(&hdev->pdev->dev,
			 "reset failed because new reset interrupt\n");
		hclge_clear_reset_cause(hdev);
		वापस false;
	पूर्ण अन्यथा अगर (hdev->rst_stats.reset_fail_cnt < MAX_RESET_FAIL_CNT) अणु
		hdev->rst_stats.reset_fail_cnt++;
		set_bit(hdev->reset_type, &hdev->reset_pending);
		dev_info(&hdev->pdev->dev,
			 "re-schedule reset task(%u)\n",
			 hdev->rst_stats.reset_fail_cnt);
		वापस true;
	पूर्ण

	hclge_clear_reset_cause(hdev);

	/* recover the handshake status when reset fail */
	hclge_reset_handshake(hdev, true);

	dev_err(&hdev->pdev->dev, "Reset fail!\n");

	hclge_dbg_dump_rst_info(hdev);

	set_bit(HCLGE_STATE_RST_FAIL, &hdev->state);

	वापस false;
पूर्ण

अटल व्योम hclge_update_reset_level(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);
	क्रमागत hnae3_reset_type reset_level;

	/* reset request will not be set during reset, so clear
	 * pending reset request to aव्योम unnecessary reset
	 * caused by the same reason.
	 */
	hclge_get_reset_level(ae_dev, &hdev->reset_request);

	/* अगर शेष_reset_request has a higher level reset request,
	 * it should be handled as soon as possible. since some errors
	 * need this kind of reset to fix.
	 */
	reset_level = hclge_get_reset_level(ae_dev,
					    &hdev->शेष_reset_request);
	अगर (reset_level != HNAE3_NONE_RESET)
		set_bit(reset_level, &hdev->reset_request);
पूर्ण

अटल पूर्णांक hclge_set_rst_करोne(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_pf_rst_करोne_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	req = (काष्ठा hclge_pf_rst_करोne_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_PF_RST_DONE, false);
	req->pf_rst_करोne |= HCLGE_PF_RESET_DONE_BIT;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	/* To be compatible with the old firmware, which करोes not support
	 * command HCLGE_OPC_PF_RST_DONE, just prपूर्णांक a warning and
	 * वापस success
	 */
	अगर (ret == -EOPNOTSUPP) अणु
		dev_warn(&hdev->pdev->dev,
			 "current firmware does not support command(0x%x)!\n",
			 HCLGE_OPC_PF_RST_DONE);
		वापस 0;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "assert PF reset done fail %d!\n",
			ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_reset_prepare_up(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret = 0;

	चयन (hdev->reset_type) अणु
	हाल HNAE3_FUNC_RESET:
	हाल HNAE3_FLR_RESET:
		ret = hclge_set_all_vf_rst(hdev, false);
		अवरोध;
	हाल HNAE3_GLOBAL_RESET:
	हाल HNAE3_IMP_RESET:
		ret = hclge_set_rst_करोne(hdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* clear up the handshake status after re-initialize करोne */
	hclge_reset_handshake(hdev, false);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_reset_stack(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_notअगरy_client(hdev, HNAE3_UNINIT_CLIENT);
	अगर (ret)
		वापस ret;

	ret = hclge_reset_ae_dev(hdev->ae_dev);
	अगर (ret)
		वापस ret;

	वापस hclge_notअगरy_client(hdev, HNAE3_INIT_CLIENT);
पूर्ण

अटल पूर्णांक hclge_reset_prepare(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	hdev->rst_stats.reset_cnt++;
	/* perक्रमm reset of the stack & ae device क्रम a client */
	ret = hclge_notअगरy_roce_client(hdev, HNAE3_DOWN_CLIENT);
	अगर (ret)
		वापस ret;

	rtnl_lock();
	ret = hclge_notअगरy_client(hdev, HNAE3_DOWN_CLIENT);
	rtnl_unlock();
	अगर (ret)
		वापस ret;

	वापस hclge_reset_prepare_रुको(hdev);
पूर्ण

अटल पूर्णांक hclge_reset_rebuild(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	hdev->rst_stats.hw_reset_करोne_cnt++;

	ret = hclge_notअगरy_roce_client(hdev, HNAE3_UNINIT_CLIENT);
	अगर (ret)
		वापस ret;

	rtnl_lock();
	ret = hclge_reset_stack(hdev);
	rtnl_unlock();
	अगर (ret)
		वापस ret;

	hclge_clear_reset_cause(hdev);

	ret = hclge_notअगरy_roce_client(hdev, HNAE3_INIT_CLIENT);
	/* ignore RoCE notअगरy error अगर it fails HCLGE_RESET_MAX_FAIL_CNT - 1
	 * बार
	 */
	अगर (ret &&
	    hdev->rst_stats.reset_fail_cnt < HCLGE_RESET_MAX_FAIL_CNT - 1)
		वापस ret;

	ret = hclge_reset_prepare_up(hdev);
	अगर (ret)
		वापस ret;

	rtnl_lock();
	ret = hclge_notअगरy_client(hdev, HNAE3_UP_CLIENT);
	rtnl_unlock();
	अगर (ret)
		वापस ret;

	ret = hclge_notअगरy_roce_client(hdev, HNAE3_UP_CLIENT);
	अगर (ret)
		वापस ret;

	hdev->last_reset_समय = jअगरfies;
	hdev->rst_stats.reset_fail_cnt = 0;
	hdev->rst_stats.reset_करोne_cnt++;
	clear_bit(HCLGE_STATE_RST_FAIL, &hdev->state);

	hclge_update_reset_level(hdev);

	वापस 0;
पूर्ण

अटल व्योम hclge_reset(काष्ठा hclge_dev *hdev)
अणु
	अगर (hclge_reset_prepare(hdev))
		जाओ err_reset;

	अगर (hclge_reset_रुको(hdev))
		जाओ err_reset;

	अगर (hclge_reset_rebuild(hdev))
		जाओ err_reset;

	वापस;

err_reset:
	अगर (hclge_reset_err_handle(hdev))
		hclge_reset_task_schedule(hdev);
पूर्ण

अटल व्योम hclge_reset_event(काष्ठा pci_dev *pdev, काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);
	काष्ठा hclge_dev *hdev = ae_dev->priv;

	/* We might end up getting called broadly because of 2 below हालs:
	 * 1. Recoverable error was conveyed through APEI and only way to bring
	 *    normalcy is to reset.
	 * 2. A new reset request from the stack due to समयout
	 *
	 * check अगर this is a new reset request and we are not here just because
	 * last reset attempt did not succeed and watchकरोg hit us again. We will
	 * know this अगर last reset request did not occur very recently (watchकरोg
	 * समयr = 5*HZ, let us check after sufficiently large समय, say 4*5*Hz)
	 * In हाल of new request we reset the "reset level" to PF reset.
	 * And अगर it is a repeat reset request of the most recent one then we
	 * want to make sure we throttle the reset request. Thereक्रमe, we will
	 * not allow it again beक्रमe 3*HZ बार.
	 */

	अगर (समय_beक्रमe(jअगरfies, (hdev->last_reset_समय +
				  HCLGE_RESET_INTERVAL))) अणु
		mod_समयr(&hdev->reset_समयr, jअगरfies + HCLGE_RESET_INTERVAL);
		वापस;
	पूर्ण

	अगर (hdev->शेष_reset_request) अणु
		hdev->reset_level =
			hclge_get_reset_level(ae_dev,
					      &hdev->शेष_reset_request);
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, (hdev->last_reset_समय + 4 * 5 * HZ))) अणु
		hdev->reset_level = HNAE3_FUNC_RESET;
	पूर्ण

	dev_info(&hdev->pdev->dev, "received reset event, reset type is %d\n",
		 hdev->reset_level);

	/* request reset & schedule reset task */
	set_bit(hdev->reset_level, &hdev->reset_request);
	hclge_reset_task_schedule(hdev);

	अगर (hdev->reset_level < HNAE3_GLOBAL_RESET)
		hdev->reset_level++;
पूर्ण

अटल व्योम hclge_set_def_reset_request(काष्ठा hnae3_ae_dev *ae_dev,
					क्रमागत hnae3_reset_type rst_type)
अणु
	काष्ठा hclge_dev *hdev = ae_dev->priv;

	set_bit(rst_type, &hdev->शेष_reset_request);
पूर्ण

अटल व्योम hclge_reset_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hclge_dev *hdev = from_समयr(hdev, t, reset_समयr);

	/* अगर शेष_reset_request has no value, it means that this reset
	 * request has alपढ़ोy be handled, so just वापस here
	 */
	अगर (!hdev->शेष_reset_request)
		वापस;

	dev_info(&hdev->pdev->dev,
		 "triggering reset in reset timer\n");
	hclge_reset_event(hdev->pdev, शून्य);
पूर्ण

अटल व्योम hclge_reset_subtask(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);

	/* check अगर there is any ongoing reset in the hardware. This status can
	 * be checked from reset_pending. If there is then, we need to रुको क्रम
	 * hardware to complete reset.
	 *    a. If we are able to figure out in reasonable समय that hardware
	 *       has fully resetted then, we can proceed with driver, client
	 *       reset.
	 *    b. अन्यथा, we can come back later to check this status so re-sched
	 *       now.
	 */
	hdev->last_reset_समय = jअगरfies;
	hdev->reset_type = hclge_get_reset_level(ae_dev, &hdev->reset_pending);
	अगर (hdev->reset_type != HNAE3_NONE_RESET)
		hclge_reset(hdev);

	/* check अगर we got any *new* reset requests to be honored */
	hdev->reset_type = hclge_get_reset_level(ae_dev, &hdev->reset_request);
	अगर (hdev->reset_type != HNAE3_NONE_RESET)
		hclge_करो_reset(hdev);

	hdev->reset_type = HNAE3_NONE_RESET;
पूर्ण

अटल व्योम hclge_reset_service_task(काष्ठा hclge_dev *hdev)
अणु
	अगर (!test_and_clear_bit(HCLGE_STATE_RST_SERVICE_SCHED, &hdev->state))
		वापस;

	करोwn(&hdev->reset_sem);
	set_bit(HCLGE_STATE_RST_HANDLING, &hdev->state);

	hclge_reset_subtask(hdev);

	clear_bit(HCLGE_STATE_RST_HANDLING, &hdev->state);
	up(&hdev->reset_sem);
पूर्ण

अटल व्योम hclge_update_vport_alive(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक i;

	/* start from vport 1 क्रम PF is always alive */
	क्रम (i = 1; i < hdev->num_alloc_vport; i++) अणु
		काष्ठा hclge_vport *vport = &hdev->vport[i];

		अगर (समय_after(jअगरfies, vport->last_active_jअगरfies + 8 * HZ))
			clear_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state);

		/* If vf is not alive, set to शेष value */
		अगर (!test_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state))
			vport->mps = HCLGE_MAC_DEFAULT_FRAME;
	पूर्ण
पूर्ण

अटल व्योम hclge_periodic_service_task(काष्ठा hclge_dev *hdev)
अणु
	अचिन्हित दीर्घ delta = round_jअगरfies_relative(HZ);

	अगर (test_bit(HCLGE_STATE_RST_FAIL, &hdev->state))
		वापस;

	/* Always handle the link updating to make sure link state is
	 * updated when it is triggered by mbx.
	 */
	hclge_update_link_status(hdev);
	hclge_sync_mac_table(hdev);
	hclge_sync_promisc_mode(hdev);
	hclge_sync_fd_table(hdev);

	अगर (समय_is_after_jअगरfies(hdev->last_serv_processed + HZ)) अणु
		delta = jअगरfies - hdev->last_serv_processed;

		अगर (delta < round_jअगरfies_relative(HZ)) अणु
			delta = round_jअगरfies_relative(HZ) - delta;
			जाओ out;
		पूर्ण
	पूर्ण

	hdev->serv_processed_cnt++;
	hclge_update_vport_alive(hdev);

	अगर (test_bit(HCLGE_STATE_DOWN, &hdev->state)) अणु
		hdev->last_serv_processed = jअगरfies;
		जाओ out;
	पूर्ण

	अगर (!(hdev->serv_processed_cnt % HCLGE_STATS_TIMER_INTERVAL))
		hclge_update_stats_क्रम_all(hdev);

	hclge_update_port_info(hdev);
	hclge_sync_vlan_filter(hdev);

	अगर (!(hdev->serv_processed_cnt % HCLGE_ARFS_EXPIRE_INTERVAL))
		hclge_rfs_filter_expire(hdev);

	hdev->last_serv_processed = jअगरfies;

out:
	hclge_task_schedule(hdev, delta);
पूर्ण

अटल व्योम hclge_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hclge_dev *hdev =
		container_of(work, काष्ठा hclge_dev, service_task.work);

	hclge_reset_service_task(hdev);
	hclge_mailbox_service_task(hdev);
	hclge_periodic_service_task(hdev);

	/* Handle reset and mbx again in हाल periodical task delays the
	 * handling by calling hclge_task_schedule() in
	 * hclge_periodic_service_task().
	 */
	hclge_reset_service_task(hdev);
	hclge_mailbox_service_task(hdev);
पूर्ण

काष्ठा hclge_vport *hclge_get_vport(काष्ठा hnae3_handle *handle)
अणु
	/* VF handle has no client */
	अगर (!handle->client)
		वापस container_of(handle, काष्ठा hclge_vport, nic);
	अन्यथा अगर (handle->client->type == HNAE3_CLIENT_ROCE)
		वापस container_of(handle, काष्ठा hclge_vport, roce);
	अन्यथा
		वापस container_of(handle, काष्ठा hclge_vport, nic);
पूर्ण

अटल व्योम hclge_get_vector_info(काष्ठा hclge_dev *hdev, u16 idx,
				  काष्ठा hnae3_vector_info *vector_info)
अणु
#घोषणा HCLGE_PF_MAX_VECTOR_NUM_DEV_V2	64

	vector_info->vector = pci_irq_vector(hdev->pdev, idx);

	/* need an extend offset to config vector >= 64 */
	अगर (idx - 1 < HCLGE_PF_MAX_VECTOR_NUM_DEV_V2)
		vector_info->io_addr = hdev->hw.io_base +
				HCLGE_VECTOR_REG_BASE +
				(idx - 1) * HCLGE_VECTOR_REG_OFFSET;
	अन्यथा
		vector_info->io_addr = hdev->hw.io_base +
				HCLGE_VECTOR_EXT_REG_BASE +
				(idx - 1) / HCLGE_PF_MAX_VECTOR_NUM_DEV_V2 *
				HCLGE_VECTOR_REG_OFFSET_H +
				(idx - 1) % HCLGE_PF_MAX_VECTOR_NUM_DEV_V2 *
				HCLGE_VECTOR_REG_OFFSET;

	hdev->vector_status[idx] = hdev->vport[0].vport_id;
	hdev->vector_irq[idx] = vector_info->vector;
पूर्ण

अटल पूर्णांक hclge_get_vector(काष्ठा hnae3_handle *handle, u16 vector_num,
			    काष्ठा hnae3_vector_info *vector_info)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hnae3_vector_info *vector = vector_info;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक alloc = 0;
	u16 i = 0;
	u16 j;

	vector_num = min_t(u16, hdev->num_nic_msi - 1, vector_num);
	vector_num = min(hdev->num_msi_left, vector_num);

	क्रम (j = 0; j < vector_num; j++) अणु
		जबतक (++i < hdev->num_nic_msi) अणु
			अगर (hdev->vector_status[i] == HCLGE_INVALID_VPORT) अणु
				hclge_get_vector_info(hdev, i, vector);
				vector++;
				alloc++;

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	hdev->num_msi_left -= alloc;
	hdev->num_msi_used += alloc;

	वापस alloc;
पूर्ण

अटल पूर्णांक hclge_get_vector_index(काष्ठा hclge_dev *hdev, पूर्णांक vector)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hdev->num_msi; i++)
		अगर (vector == hdev->vector_irq[i])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hclge_put_vector(काष्ठा hnae3_handle *handle, पूर्णांक vector)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक vector_id;

	vector_id = hclge_get_vector_index(hdev, vector);
	अगर (vector_id < 0) अणु
		dev_err(&hdev->pdev->dev,
			"Get vector index fail. vector = %d\n", vector);
		वापस vector_id;
	पूर्ण

	hclge_मुक्त_vector(hdev, vector_id);

	वापस 0;
पूर्ण

अटल u32 hclge_get_rss_key_size(काष्ठा hnae3_handle *handle)
अणु
	वापस HCLGE_RSS_KEY_SIZE;
पूर्ण

अटल पूर्णांक hclge_set_rss_algo_key(काष्ठा hclge_dev *hdev,
				  स्थिर u8 hfunc, स्थिर u8 *key)
अणु
	काष्ठा hclge_rss_config_cmd *req;
	अचिन्हित पूर्णांक key_offset = 0;
	काष्ठा hclge_desc desc;
	पूर्णांक key_counts;
	पूर्णांक key_size;
	पूर्णांक ret;

	key_counts = HCLGE_RSS_KEY_SIZE;
	req = (काष्ठा hclge_rss_config_cmd *)desc.data;

	जबतक (key_counts) अणु
		hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RSS_GENERIC_CONFIG,
					   false);

		req->hash_config |= (hfunc & HCLGE_RSS_HASH_ALGO_MASK);
		req->hash_config |= (key_offset << HCLGE_RSS_HASH_KEY_OFFSET_B);

		key_size = min(HCLGE_RSS_HASH_KEY_NUM, key_counts);
		स_नकल(req->hash_key,
		       key + key_offset * HCLGE_RSS_HASH_KEY_NUM, key_size);

		key_counts -= key_size;
		key_offset++;
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"Configure RSS config fail, status = %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_rss_indir_table(काष्ठा hclge_dev *hdev, स्थिर u16 *indir)
अणु
	काष्ठा hclge_rss_indirection_table_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक rss_cfg_tbl_num;
	u8 rss_msb_oft;
	u8 rss_msb_val;
	पूर्णांक ret;
	u16 qid;
	पूर्णांक i;
	u32 j;

	req = (काष्ठा hclge_rss_indirection_table_cmd *)desc.data;
	rss_cfg_tbl_num = hdev->ae_dev->dev_specs.rss_ind_tbl_size /
			  HCLGE_RSS_CFG_TBL_SIZE;

	क्रम (i = 0; i < rss_cfg_tbl_num; i++) अणु
		hclge_cmd_setup_basic_desc
			(&desc, HCLGE_OPC_RSS_INसूची_TABLE, false);

		req->start_table_index =
			cpu_to_le16(i * HCLGE_RSS_CFG_TBL_SIZE);
		req->rss_set_biपंचांगap = cpu_to_le16(HCLGE_RSS_SET_BITMAP_MSK);
		क्रम (j = 0; j < HCLGE_RSS_CFG_TBL_SIZE; j++) अणु
			qid = indir[i * HCLGE_RSS_CFG_TBL_SIZE + j];
			req->rss_qid_l[j] = qid & 0xff;
			rss_msb_oft =
				j * HCLGE_RSS_CFG_TBL_BW_H / BITS_PER_BYTE;
			rss_msb_val = (qid >> HCLGE_RSS_CFG_TBL_BW_L & 0x1) <<
				(j * HCLGE_RSS_CFG_TBL_BW_H % BITS_PER_BYTE);
			req->rss_qid_h[rss_msb_oft] |= rss_msb_val;
		पूर्ण
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"Configure rss indir table fail,status = %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_rss_tc_mode(काष्ठा hclge_dev *hdev, u16 *tc_valid,
				 u16 *tc_size, u16 *tc_offset)
अणु
	काष्ठा hclge_rss_tc_mode_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;
	पूर्णांक i;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RSS_TC_MODE, false);
	req = (काष्ठा hclge_rss_tc_mode_cmd *)desc.data;

	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		u16 mode = 0;

		hnae3_set_bit(mode, HCLGE_RSS_TC_VALID_B, (tc_valid[i] & 0x1));
		hnae3_set_field(mode, HCLGE_RSS_TC_SIZE_M,
				HCLGE_RSS_TC_SIZE_S, tc_size[i]);
		hnae3_set_bit(mode, HCLGE_RSS_TC_SIZE_MSB_B,
			      tc_size[i] >> HCLGE_RSS_TC_SIZE_MSB_OFFSET & 0x1);
		hnae3_set_field(mode, HCLGE_RSS_TC_OFFSET_M,
				HCLGE_RSS_TC_OFFSET_S, tc_offset[i]);

		req->rss_tc_mode[i] = cpu_to_le16(mode);
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"Configure rss tc mode fail, status = %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम hclge_get_rss_type(काष्ठा hclge_vport *vport)
अणु
	अगर (vport->rss_tuple_sets.ipv4_tcp_en ||
	    vport->rss_tuple_sets.ipv4_udp_en ||
	    vport->rss_tuple_sets.ipv4_sctp_en ||
	    vport->rss_tuple_sets.ipv6_tcp_en ||
	    vport->rss_tuple_sets.ipv6_udp_en ||
	    vport->rss_tuple_sets.ipv6_sctp_en)
		vport->nic.kinfo.rss_type = PKT_HASH_TYPE_L4;
	अन्यथा अगर (vport->rss_tuple_sets.ipv4_fragment_en ||
		 vport->rss_tuple_sets.ipv6_fragment_en)
		vport->nic.kinfo.rss_type = PKT_HASH_TYPE_L3;
	अन्यथा
		vport->nic.kinfo.rss_type = PKT_HASH_TYPE_NONE;
पूर्ण

अटल पूर्णांक hclge_set_rss_input_tuple(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_rss_input_tuple_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RSS_INPUT_TUPLE, false);

	req = (काष्ठा hclge_rss_input_tuple_cmd *)desc.data;

	/* Get the tuple cfg from pf */
	req->ipv4_tcp_en = hdev->vport[0].rss_tuple_sets.ipv4_tcp_en;
	req->ipv4_udp_en = hdev->vport[0].rss_tuple_sets.ipv4_udp_en;
	req->ipv4_sctp_en = hdev->vport[0].rss_tuple_sets.ipv4_sctp_en;
	req->ipv4_fragment_en = hdev->vport[0].rss_tuple_sets.ipv4_fragment_en;
	req->ipv6_tcp_en = hdev->vport[0].rss_tuple_sets.ipv6_tcp_en;
	req->ipv6_udp_en = hdev->vport[0].rss_tuple_sets.ipv6_udp_en;
	req->ipv6_sctp_en = hdev->vport[0].rss_tuple_sets.ipv6_sctp_en;
	req->ipv6_fragment_en = hdev->vport[0].rss_tuple_sets.ipv6_fragment_en;
	hclge_get_rss_type(&hdev->vport[0]);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"Configure rss input fail, status = %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_get_rss(काष्ठा hnae3_handle *handle, u32 *indir,
			 u8 *key, u8 *hfunc)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	पूर्णांक i;

	/* Get hash algorithm */
	अगर (hfunc) अणु
		चयन (vport->rss_algo) अणु
		हाल HCLGE_RSS_HASH_ALGO_TOEPLITZ:
			*hfunc = ETH_RSS_HASH_TOP;
			अवरोध;
		हाल HCLGE_RSS_HASH_ALGO_SIMPLE:
			*hfunc = ETH_RSS_HASH_XOR;
			अवरोध;
		शेष:
			*hfunc = ETH_RSS_HASH_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Get the RSS Key required by the user */
	अगर (key)
		स_नकल(key, vport->rss_hash_key, HCLGE_RSS_KEY_SIZE);

	/* Get indirect table */
	अगर (indir)
		क्रम (i = 0; i < ae_dev->dev_specs.rss_ind_tbl_size; i++)
			indir[i] =  vport->rss_indirection_tbl[i];

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_rss(काष्ठा hnae3_handle *handle, स्थिर u32 *indir,
			 स्थिर  u8 *key, स्थिर  u8 hfunc)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	u8 hash_algo;
	पूर्णांक ret, i;

	/* Set the RSS Hash Key अगर specअगरअगरed by the user */
	अगर (key) अणु
		चयन (hfunc) अणु
		हाल ETH_RSS_HASH_TOP:
			hash_algo = HCLGE_RSS_HASH_ALGO_TOEPLITZ;
			अवरोध;
		हाल ETH_RSS_HASH_XOR:
			hash_algo = HCLGE_RSS_HASH_ALGO_SIMPLE;
			अवरोध;
		हाल ETH_RSS_HASH_NO_CHANGE:
			hash_algo = vport->rss_algo;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = hclge_set_rss_algo_key(hdev, hash_algo, key);
		अगर (ret)
			वापस ret;

		/* Update the shaकरोw RSS key with user specअगरied qids */
		स_नकल(vport->rss_hash_key, key, HCLGE_RSS_KEY_SIZE);
		vport->rss_algo = hash_algo;
	पूर्ण

	/* Update the shaकरोw RSS table with user specअगरied qids */
	क्रम (i = 0; i < ae_dev->dev_specs.rss_ind_tbl_size; i++)
		vport->rss_indirection_tbl[i] = indir[i];

	/* Update the hardware */
	वापस hclge_set_rss_indir_table(hdev, vport->rss_indirection_tbl);
पूर्ण

अटल u8 hclge_get_rss_hash_bits(काष्ठा ethtool_rxnfc *nfc)
अणु
	u8 hash_sets = nfc->data & RXH_L4_B_0_1 ? HCLGE_S_PORT_BIT : 0;

	अगर (nfc->data & RXH_L4_B_2_3)
		hash_sets |= HCLGE_D_PORT_BIT;
	अन्यथा
		hash_sets &= ~HCLGE_D_PORT_BIT;

	अगर (nfc->data & RXH_IP_SRC)
		hash_sets |= HCLGE_S_IP_BIT;
	अन्यथा
		hash_sets &= ~HCLGE_S_IP_BIT;

	अगर (nfc->data & RXH_IP_DST)
		hash_sets |= HCLGE_D_IP_BIT;
	अन्यथा
		hash_sets &= ~HCLGE_D_IP_BIT;

	अगर (nfc->flow_type == SCTP_V4_FLOW || nfc->flow_type == SCTP_V6_FLOW)
		hash_sets |= HCLGE_V_TAG_BIT;

	वापस hash_sets;
पूर्ण

अटल पूर्णांक hclge_init_rss_tuple_cmd(काष्ठा hclge_vport *vport,
				    काष्ठा ethtool_rxnfc *nfc,
				    काष्ठा hclge_rss_input_tuple_cmd *req)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	u8 tuple_sets;

	req->ipv4_tcp_en = vport->rss_tuple_sets.ipv4_tcp_en;
	req->ipv4_udp_en = vport->rss_tuple_sets.ipv4_udp_en;
	req->ipv4_sctp_en = vport->rss_tuple_sets.ipv4_sctp_en;
	req->ipv4_fragment_en = vport->rss_tuple_sets.ipv4_fragment_en;
	req->ipv6_tcp_en = vport->rss_tuple_sets.ipv6_tcp_en;
	req->ipv6_udp_en = vport->rss_tuple_sets.ipv6_udp_en;
	req->ipv6_sctp_en = vport->rss_tuple_sets.ipv6_sctp_en;
	req->ipv6_fragment_en = vport->rss_tuple_sets.ipv6_fragment_en;

	tuple_sets = hclge_get_rss_hash_bits(nfc);
	चयन (nfc->flow_type) अणु
	हाल TCP_V4_FLOW:
		req->ipv4_tcp_en = tuple_sets;
		अवरोध;
	हाल TCP_V6_FLOW:
		req->ipv6_tcp_en = tuple_sets;
		अवरोध;
	हाल UDP_V4_FLOW:
		req->ipv4_udp_en = tuple_sets;
		अवरोध;
	हाल UDP_V6_FLOW:
		req->ipv6_udp_en = tuple_sets;
		अवरोध;
	हाल SCTP_V4_FLOW:
		req->ipv4_sctp_en = tuple_sets;
		अवरोध;
	हाल SCTP_V6_FLOW:
		अगर (hdev->ae_dev->dev_version <= HNAE3_DEVICE_VERSION_V2 &&
		    (nfc->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)))
			वापस -EINVAL;

		req->ipv6_sctp_en = tuple_sets;
		अवरोध;
	हाल IPV4_FLOW:
		req->ipv4_fragment_en = HCLGE_RSS_INPUT_TUPLE_OTHER;
		अवरोध;
	हाल IPV6_FLOW:
		req->ipv6_fragment_en = HCLGE_RSS_INPUT_TUPLE_OTHER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_rss_tuple(काष्ठा hnae3_handle *handle,
			       काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_rss_input_tuple_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	अगर (nfc->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		वापस -EINVAL;

	req = (काष्ठा hclge_rss_input_tuple_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RSS_INPUT_TUPLE, false);

	ret = hclge_init_rss_tuple_cmd(vport, nfc, req);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to init rss tuple cmd, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Set rss tuple fail, status = %d\n", ret);
		वापस ret;
	पूर्ण

	vport->rss_tuple_sets.ipv4_tcp_en = req->ipv4_tcp_en;
	vport->rss_tuple_sets.ipv4_udp_en = req->ipv4_udp_en;
	vport->rss_tuple_sets.ipv4_sctp_en = req->ipv4_sctp_en;
	vport->rss_tuple_sets.ipv4_fragment_en = req->ipv4_fragment_en;
	vport->rss_tuple_sets.ipv6_tcp_en = req->ipv6_tcp_en;
	vport->rss_tuple_sets.ipv6_udp_en = req->ipv6_udp_en;
	vport->rss_tuple_sets.ipv6_sctp_en = req->ipv6_sctp_en;
	vport->rss_tuple_sets.ipv6_fragment_en = req->ipv6_fragment_en;
	hclge_get_rss_type(vport);
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_vport_rss_tuple(काष्ठा hclge_vport *vport, पूर्णांक flow_type,
				     u8 *tuple_sets)
अणु
	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
		*tuple_sets = vport->rss_tuple_sets.ipv4_tcp_en;
		अवरोध;
	हाल UDP_V4_FLOW:
		*tuple_sets = vport->rss_tuple_sets.ipv4_udp_en;
		अवरोध;
	हाल TCP_V6_FLOW:
		*tuple_sets = vport->rss_tuple_sets.ipv6_tcp_en;
		अवरोध;
	हाल UDP_V6_FLOW:
		*tuple_sets = vport->rss_tuple_sets.ipv6_udp_en;
		अवरोध;
	हाल SCTP_V4_FLOW:
		*tuple_sets = vport->rss_tuple_sets.ipv4_sctp_en;
		अवरोध;
	हाल SCTP_V6_FLOW:
		*tuple_sets = vport->rss_tuple_sets.ipv6_sctp_en;
		अवरोध;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		*tuple_sets = HCLGE_S_IP_BIT | HCLGE_D_IP_BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 hclge_convert_rss_tuple(u8 tuple_sets)
अणु
	u64 tuple_data = 0;

	अगर (tuple_sets & HCLGE_D_PORT_BIT)
		tuple_data |= RXH_L4_B_2_3;
	अगर (tuple_sets & HCLGE_S_PORT_BIT)
		tuple_data |= RXH_L4_B_0_1;
	अगर (tuple_sets & HCLGE_D_IP_BIT)
		tuple_data |= RXH_IP_DST;
	अगर (tuple_sets & HCLGE_S_IP_BIT)
		tuple_data |= RXH_IP_SRC;

	वापस tuple_data;
पूर्ण

अटल पूर्णांक hclge_get_rss_tuple(काष्ठा hnae3_handle *handle,
			       काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	u8 tuple_sets;
	पूर्णांक ret;

	nfc->data = 0;

	ret = hclge_get_vport_rss_tuple(vport, nfc->flow_type, &tuple_sets);
	अगर (ret || !tuple_sets)
		वापस ret;

	nfc->data = hclge_convert_rss_tuple(tuple_sets);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_tc_size(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस hdev->pf_rss_size_max;
पूर्ण

अटल पूर्णांक hclge_init_rss_tc_mode(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = hdev->ae_dev;
	काष्ठा hclge_vport *vport = hdev->vport;
	u16 tc_offset[HCLGE_MAX_TC_NUM] = अणु0पूर्ण;
	u16 tc_valid[HCLGE_MAX_TC_NUM] = अणु0पूर्ण;
	u16 tc_size[HCLGE_MAX_TC_NUM] = अणु0पूर्ण;
	काष्ठा hnae3_tc_info *tc_info;
	u16 roundup_size;
	u16 rss_size;
	पूर्णांक i;

	tc_info = &vport->nic.kinfo.tc_info;
	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		rss_size = tc_info->tqp_count[i];
		tc_valid[i] = 0;

		अगर (!(hdev->hw_tc_map & BIT(i)))
			जारी;

		/* tc_size set to hardware is the log2 of roundup घातer of two
		 * of rss_size, the acutal queue size is limited by indirection
		 * table.
		 */
		अगर (rss_size > ae_dev->dev_specs.rss_ind_tbl_size ||
		    rss_size == 0) अणु
			dev_err(&hdev->pdev->dev,
				"Configure rss tc size failed, invalid TC_SIZE = %u\n",
				rss_size);
			वापस -EINVAL;
		पूर्ण

		roundup_size = roundup_घात_of_two(rss_size);
		roundup_size = ilog2(roundup_size);

		tc_valid[i] = 1;
		tc_size[i] = roundup_size;
		tc_offset[i] = tc_info->tqp_offset[i];
	पूर्ण

	वापस hclge_set_rss_tc_mode(hdev, tc_valid, tc_size, tc_offset);
पूर्ण

पूर्णांक hclge_rss_init_hw(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	u16 *rss_indir = vport[0].rss_indirection_tbl;
	u8 *key = vport[0].rss_hash_key;
	u8 hfunc = vport[0].rss_algo;
	पूर्णांक ret;

	ret = hclge_set_rss_indir_table(hdev, rss_indir);
	अगर (ret)
		वापस ret;

	ret = hclge_set_rss_algo_key(hdev, hfunc, key);
	अगर (ret)
		वापस ret;

	ret = hclge_set_rss_input_tuple(hdev);
	अगर (ret)
		वापस ret;

	वापस hclge_init_rss_tc_mode(hdev);
पूर्ण

व्योम hclge_rss_indir_init_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = &hdev->vport[0];
	पूर्णांक i;

	क्रम (i = 0; i < hdev->ae_dev->dev_specs.rss_ind_tbl_size; i++)
		vport->rss_indirection_tbl[i] = i % vport->alloc_rss_size;
पूर्ण

अटल पूर्णांक hclge_rss_init_cfg(काष्ठा hclge_dev *hdev)
अणु
	u16 rss_ind_tbl_size = hdev->ae_dev->dev_specs.rss_ind_tbl_size;
	पूर्णांक rss_algo = HCLGE_RSS_HASH_ALGO_TOEPLITZ;
	काष्ठा hclge_vport *vport = &hdev->vport[0];
	u16 *rss_ind_tbl;

	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2)
		rss_algo = HCLGE_RSS_HASH_ALGO_SIMPLE;

	vport->rss_tuple_sets.ipv4_tcp_en = HCLGE_RSS_INPUT_TUPLE_OTHER;
	vport->rss_tuple_sets.ipv4_udp_en = HCLGE_RSS_INPUT_TUPLE_OTHER;
	vport->rss_tuple_sets.ipv4_sctp_en = HCLGE_RSS_INPUT_TUPLE_SCTP;
	vport->rss_tuple_sets.ipv4_fragment_en = HCLGE_RSS_INPUT_TUPLE_OTHER;
	vport->rss_tuple_sets.ipv6_tcp_en = HCLGE_RSS_INPUT_TUPLE_OTHER;
	vport->rss_tuple_sets.ipv6_udp_en = HCLGE_RSS_INPUT_TUPLE_OTHER;
	vport->rss_tuple_sets.ipv6_sctp_en =
		hdev->ae_dev->dev_version <= HNAE3_DEVICE_VERSION_V2 ?
		HCLGE_RSS_INPUT_TUPLE_SCTP_NO_PORT :
		HCLGE_RSS_INPUT_TUPLE_SCTP;
	vport->rss_tuple_sets.ipv6_fragment_en = HCLGE_RSS_INPUT_TUPLE_OTHER;

	vport->rss_algo = rss_algo;

	rss_ind_tbl = devm_kसुस्मृति(&hdev->pdev->dev, rss_ind_tbl_size,
				   माप(*rss_ind_tbl), GFP_KERNEL);
	अगर (!rss_ind_tbl)
		वापस -ENOMEM;

	vport->rss_indirection_tbl = rss_ind_tbl;
	स_नकल(vport->rss_hash_key, hclge_hash_key, HCLGE_RSS_KEY_SIZE);

	hclge_rss_indir_init_cfg(hdev);

	वापस 0;
पूर्ण

पूर्णांक hclge_bind_ring_with_vector(काष्ठा hclge_vport *vport,
				पूर्णांक vector_id, bool en,
				काष्ठा hnae3_ring_chain_node *ring_chain)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hnae3_ring_chain_node *node;
	काष्ठा hclge_desc desc;
	काष्ठा hclge_ctrl_vector_chain_cmd *req =
		(काष्ठा hclge_ctrl_vector_chain_cmd *)desc.data;
	क्रमागत hclge_cmd_status status;
	क्रमागत hclge_opcode_type op;
	u16 tqp_type_and_id;
	पूर्णांक i;

	op = en ? HCLGE_OPC_ADD_RING_TO_VECTOR : HCLGE_OPC_DEL_RING_TO_VECTOR;
	hclge_cmd_setup_basic_desc(&desc, op, false);
	req->पूर्णांक_vector_id_l = hnae3_get_field(vector_id,
					       HCLGE_VECTOR_ID_L_M,
					       HCLGE_VECTOR_ID_L_S);
	req->पूर्णांक_vector_id_h = hnae3_get_field(vector_id,
					       HCLGE_VECTOR_ID_H_M,
					       HCLGE_VECTOR_ID_H_S);

	i = 0;
	क्रम (node = ring_chain; node; node = node->next) अणु
		tqp_type_and_id = le16_to_cpu(req->tqp_type_and_id[i]);
		hnae3_set_field(tqp_type_and_id,  HCLGE_INT_TYPE_M,
				HCLGE_INT_TYPE_S,
				hnae3_get_bit(node->flag, HNAE3_RING_TYPE_B));
		hnae3_set_field(tqp_type_and_id, HCLGE_TQP_ID_M,
				HCLGE_TQP_ID_S, node->tqp_index);
		hnae3_set_field(tqp_type_and_id, HCLGE_INT_GL_IDX_M,
				HCLGE_INT_GL_IDX_S,
				hnae3_get_field(node->पूर्णांक_gl_idx,
						HNAE3_RING_GL_IDX_M,
						HNAE3_RING_GL_IDX_S));
		req->tqp_type_and_id[i] = cpu_to_le16(tqp_type_and_id);
		अगर (++i >= HCLGE_VECTOR_ELEMENTS_PER_CMD) अणु
			req->पूर्णांक_cause_num = HCLGE_VECTOR_ELEMENTS_PER_CMD;
			req->vfid = vport->vport_id;

			status = hclge_cmd_send(&hdev->hw, &desc, 1);
			अगर (status) अणु
				dev_err(&hdev->pdev->dev,
					"Map TQP fail, status is %d.\n",
					status);
				वापस -EIO;
			पूर्ण
			i = 0;

			hclge_cmd_setup_basic_desc(&desc,
						   op,
						   false);
			req->पूर्णांक_vector_id_l =
				hnae3_get_field(vector_id,
						HCLGE_VECTOR_ID_L_M,
						HCLGE_VECTOR_ID_L_S);
			req->पूर्णांक_vector_id_h =
				hnae3_get_field(vector_id,
						HCLGE_VECTOR_ID_H_M,
						HCLGE_VECTOR_ID_H_S);
		पूर्ण
	पूर्ण

	अगर (i > 0) अणु
		req->पूर्णांक_cause_num = i;
		req->vfid = vport->vport_id;
		status = hclge_cmd_send(&hdev->hw, &desc, 1);
		अगर (status) अणु
			dev_err(&hdev->pdev->dev,
				"Map TQP fail, status is %d.\n", status);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_map_ring_to_vector(काष्ठा hnae3_handle *handle, पूर्णांक vector,
				    काष्ठा hnae3_ring_chain_node *ring_chain)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक vector_id;

	vector_id = hclge_get_vector_index(hdev, vector);
	अगर (vector_id < 0) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get vector index. vector=%d\n", vector);
		वापस vector_id;
	पूर्ण

	वापस hclge_bind_ring_with_vector(vport, vector_id, true, ring_chain);
पूर्ण

अटल पूर्णांक hclge_unmap_ring_frm_vector(काष्ठा hnae3_handle *handle, पूर्णांक vector,
				       काष्ठा hnae3_ring_chain_node *ring_chain)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक vector_id, ret;

	अगर (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
		वापस 0;

	vector_id = hclge_get_vector_index(hdev, vector);
	अगर (vector_id < 0) अणु
		dev_err(&handle->pdev->dev,
			"Get vector index fail. ret =%d\n", vector_id);
		वापस vector_id;
	पूर्ण

	ret = hclge_bind_ring_with_vector(vport, vector_id, false, ring_chain);
	अगर (ret)
		dev_err(&handle->pdev->dev,
			"Unmap ring from vector fail. vectorid=%d, ret =%d\n",
			vector_id, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_cmd_set_promisc_mode(काष्ठा hclge_dev *hdev, u8 vf_id,
				      bool en_uc, bool en_mc, bool en_bc)
अणु
	काष्ठा hclge_vport *vport = &hdev->vport[vf_id];
	काष्ठा hnae3_handle *handle = &vport->nic;
	काष्ठा hclge_promisc_cfg_cmd *req;
	काष्ठा hclge_desc desc;
	bool uc_tx_en = en_uc;
	u8 promisc_cfg = 0;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_PROMISC_MODE, false);

	req = (काष्ठा hclge_promisc_cfg_cmd *)desc.data;
	req->vf_id = vf_id;

	अगर (test_bit(HNAE3_PFLAG_LIMIT_PROMISC, &handle->priv_flags))
		uc_tx_en = false;

	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_UC_RX_EN, en_uc ? 1 : 0);
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_MC_RX_EN, en_mc ? 1 : 0);
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_BC_RX_EN, en_bc ? 1 : 0);
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_UC_TX_EN, uc_tx_en ? 1 : 0);
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_MC_TX_EN, en_mc ? 1 : 0);
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_BC_TX_EN, en_bc ? 1 : 0);
	req->extend_promisc = promisc_cfg;

	/* to be compatible with DEVICE_VERSION_V1/2 */
	promisc_cfg = 0;
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_EN_UC, en_uc ? 1 : 0);
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_EN_MC, en_mc ? 1 : 0);
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_EN_BC, en_bc ? 1 : 0);
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_TX_EN, 1);
	hnae3_set_bit(promisc_cfg, HCLGE_PROMISC_RX_EN, 1);
	req->promisc = promisc_cfg;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"failed to set vport %u promisc mode, ret = %d.\n",
			vf_id, ret);

	वापस ret;
पूर्ण

पूर्णांक hclge_set_vport_promisc_mode(काष्ठा hclge_vport *vport, bool en_uc_pmc,
				 bool en_mc_pmc, bool en_bc_pmc)
अणु
	वापस hclge_cmd_set_promisc_mode(vport->back, vport->vport_id,
					  en_uc_pmc, en_mc_pmc, en_bc_pmc);
पूर्ण

अटल पूर्णांक hclge_set_promisc_mode(काष्ठा hnae3_handle *handle, bool en_uc_pmc,
				  bool en_mc_pmc)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	bool en_bc_pmc = true;

	/* For device whose version below V2, अगर broadcast promisc enabled,
	 * vlan filter is always bypassed. So broadcast promisc should be
	 * disabled until user enable promisc mode
	 */
	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		en_bc_pmc = handle->netdev_flags & HNAE3_BPE ? true : false;

	वापस hclge_set_vport_promisc_mode(vport, en_uc_pmc, en_mc_pmc,
					    en_bc_pmc);
पूर्ण

अटल व्योम hclge_request_update_promisc_mode(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	set_bit(HCLGE_STATE_PROMISC_CHANGED, &hdev->state);
पूर्ण

अटल व्योम hclge_sync_fd_state(काष्ठा hclge_dev *hdev)
अणु
	अगर (hlist_empty(&hdev->fd_rule_list))
		hdev->fd_active_type = HCLGE_FD_RULE_NONE;
पूर्ण

अटल व्योम hclge_fd_inc_rule_cnt(काष्ठा hclge_dev *hdev, u16 location)
अणु
	अगर (!test_bit(location, hdev->fd_bmap)) अणु
		set_bit(location, hdev->fd_bmap);
		hdev->hclge_fd_rule_num++;
	पूर्ण
पूर्ण

अटल व्योम hclge_fd_dec_rule_cnt(काष्ठा hclge_dev *hdev, u16 location)
अणु
	अगर (test_bit(location, hdev->fd_bmap)) अणु
		clear_bit(location, hdev->fd_bmap);
		hdev->hclge_fd_rule_num--;
	पूर्ण
पूर्ण

अटल व्योम hclge_fd_मुक्त_node(काष्ठा hclge_dev *hdev,
			       काष्ठा hclge_fd_rule *rule)
अणु
	hlist_del(&rule->rule_node);
	kमुक्त(rule);
	hclge_sync_fd_state(hdev);
पूर्ण

अटल व्योम hclge_update_fd_rule_node(काष्ठा hclge_dev *hdev,
				      काष्ठा hclge_fd_rule *old_rule,
				      काष्ठा hclge_fd_rule *new_rule,
				      क्रमागत HCLGE_FD_NODE_STATE state)
अणु
	चयन (state) अणु
	हाल HCLGE_FD_TO_ADD:
	हाल HCLGE_FD_ACTIVE:
		/* 1) अगर the new state is TO_ADD, just replace the old rule
		 * with the same location, no matter its state, because the
		 * new rule will be configured to the hardware.
		 * 2) अगर the new state is ACTIVE, it means the new rule
		 * has been configured to the hardware, so just replace
		 * the old rule node with the same location.
		 * 3) क्रम it करोesn't add a new node to the list, so it's
		 * unnecessary to update the rule number and fd_bmap.
		 */
		new_rule->rule_node.next = old_rule->rule_node.next;
		new_rule->rule_node.pprev = old_rule->rule_node.pprev;
		स_नकल(old_rule, new_rule, माप(*old_rule));
		kमुक्त(new_rule);
		अवरोध;
	हाल HCLGE_FD_DELETED:
		hclge_fd_dec_rule_cnt(hdev, old_rule->location);
		hclge_fd_मुक्त_node(hdev, old_rule);
		अवरोध;
	हाल HCLGE_FD_TO_DEL:
		/* अगर new request is TO_DEL, and old rule is existent
		 * 1) the state of old rule is TO_DEL, we need करो nothing,
		 * because we delete rule by location, other rule content
		 * is unncessary.
		 * 2) the state of old rule is ACTIVE, we need to change its
		 * state to TO_DEL, so the rule will be deleted when periodic
		 * task being scheduled.
		 * 3) the state of old rule is TO_ADD, it means the rule hasn't
		 * been added to hardware, so we just delete the rule node from
		 * fd_rule_list directly.
		 */
		अगर (old_rule->state == HCLGE_FD_TO_ADD) अणु
			hclge_fd_dec_rule_cnt(hdev, old_rule->location);
			hclge_fd_मुक्त_node(hdev, old_rule);
			वापस;
		पूर्ण
		old_rule->state = HCLGE_FD_TO_DEL;
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा hclge_fd_rule *hclge_find_fd_rule(काष्ठा hlist_head *hlist,
						u16 location,
						काष्ठा hclge_fd_rule **parent)
अणु
	काष्ठा hclge_fd_rule *rule;
	काष्ठा hlist_node *node;

	hlist_क्रम_each_entry_safe(rule, node, hlist, rule_node) अणु
		अगर (rule->location == location)
			वापस rule;
		अन्यथा अगर (rule->location > location)
			वापस शून्य;
		/* record the parent node, use to keep the nodes in fd_rule_list
		 * in ascend order.
		 */
		*parent = rule;
	पूर्ण

	वापस शून्य;
पूर्ण

/* insert fd rule node in ascend order according to rule->location */
अटल व्योम hclge_fd_insert_rule_node(काष्ठा hlist_head *hlist,
				      काष्ठा hclge_fd_rule *rule,
				      काष्ठा hclge_fd_rule *parent)
अणु
	INIT_HLIST_NODE(&rule->rule_node);

	अगर (parent)
		hlist_add_behind(&rule->rule_node, &parent->rule_node);
	अन्यथा
		hlist_add_head(&rule->rule_node, hlist);
पूर्ण

अटल पूर्णांक hclge_fd_set_user_def_cmd(काष्ठा hclge_dev *hdev,
				     काष्ठा hclge_fd_user_def_cfg *cfg)
अणु
	काष्ठा hclge_fd_user_def_cfg_cmd *req;
	काष्ठा hclge_desc desc;
	u16 data = 0;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_FD_USER_DEF_OP, false);

	req = (काष्ठा hclge_fd_user_def_cfg_cmd *)desc.data;

	hnae3_set_bit(data, HCLGE_FD_USER_DEF_EN_B, cfg[0].ref_cnt > 0);
	hnae3_set_field(data, HCLGE_FD_USER_DEF_OFT_M,
			HCLGE_FD_USER_DEF_OFT_S, cfg[0].offset);
	req->ol2_cfg = cpu_to_le16(data);

	data = 0;
	hnae3_set_bit(data, HCLGE_FD_USER_DEF_EN_B, cfg[1].ref_cnt > 0);
	hnae3_set_field(data, HCLGE_FD_USER_DEF_OFT_M,
			HCLGE_FD_USER_DEF_OFT_S, cfg[1].offset);
	req->ol3_cfg = cpu_to_le16(data);

	data = 0;
	hnae3_set_bit(data, HCLGE_FD_USER_DEF_EN_B, cfg[2].ref_cnt > 0);
	hnae3_set_field(data, HCLGE_FD_USER_DEF_OFT_M,
			HCLGE_FD_USER_DEF_OFT_S, cfg[2].offset);
	req->ol4_cfg = cpu_to_le16(data);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"failed to set fd user def data, ret= %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम hclge_sync_fd_user_def_cfg(काष्ठा hclge_dev *hdev, bool locked)
अणु
	पूर्णांक ret;

	अगर (!test_and_clear_bit(HCLGE_STATE_FD_USER_DEF_CHANGED, &hdev->state))
		वापस;

	अगर (!locked)
		spin_lock_bh(&hdev->fd_rule_lock);

	ret = hclge_fd_set_user_def_cmd(hdev, hdev->fd_cfg.user_def_cfg);
	अगर (ret)
		set_bit(HCLGE_STATE_FD_USER_DEF_CHANGED, &hdev->state);

	अगर (!locked)
		spin_unlock_bh(&hdev->fd_rule_lock);
पूर्ण

अटल पूर्णांक hclge_fd_check_user_def_refcnt(काष्ठा hclge_dev *hdev,
					  काष्ठा hclge_fd_rule *rule)
अणु
	काष्ठा hlist_head *hlist = &hdev->fd_rule_list;
	काष्ठा hclge_fd_rule *fd_rule, *parent = शून्य;
	काष्ठा hclge_fd_user_def_info *info, *old_info;
	काष्ठा hclge_fd_user_def_cfg *cfg;

	अगर (!rule || rule->rule_type != HCLGE_FD_EP_ACTIVE ||
	    rule->ep.user_def.layer == HCLGE_FD_USER_DEF_NONE)
		वापस 0;

	/* क्रम valid layer is start from 1, so need minus 1 to get the cfg */
	cfg = &hdev->fd_cfg.user_def_cfg[rule->ep.user_def.layer - 1];
	info = &rule->ep.user_def;

	अगर (!cfg->ref_cnt || cfg->offset == info->offset)
		वापस 0;

	अगर (cfg->ref_cnt > 1)
		जाओ error;

	fd_rule = hclge_find_fd_rule(hlist, rule->location, &parent);
	अगर (fd_rule) अणु
		old_info = &fd_rule->ep.user_def;
		अगर (info->layer == old_info->layer)
			वापस 0;
	पूर्ण

error:
	dev_err(&hdev->pdev->dev,
		"No available offset for layer%d fd rule, each layer only support one user def offset.\n",
		info->layer + 1);
	वापस -ENOSPC;
पूर्ण

अटल व्योम hclge_fd_inc_user_def_refcnt(काष्ठा hclge_dev *hdev,
					 काष्ठा hclge_fd_rule *rule)
अणु
	काष्ठा hclge_fd_user_def_cfg *cfg;

	अगर (!rule || rule->rule_type != HCLGE_FD_EP_ACTIVE ||
	    rule->ep.user_def.layer == HCLGE_FD_USER_DEF_NONE)
		वापस;

	cfg = &hdev->fd_cfg.user_def_cfg[rule->ep.user_def.layer - 1];
	अगर (!cfg->ref_cnt) अणु
		cfg->offset = rule->ep.user_def.offset;
		set_bit(HCLGE_STATE_FD_USER_DEF_CHANGED, &hdev->state);
	पूर्ण
	cfg->ref_cnt++;
पूर्ण

अटल व्योम hclge_fd_dec_user_def_refcnt(काष्ठा hclge_dev *hdev,
					 काष्ठा hclge_fd_rule *rule)
अणु
	काष्ठा hclge_fd_user_def_cfg *cfg;

	अगर (!rule || rule->rule_type != HCLGE_FD_EP_ACTIVE ||
	    rule->ep.user_def.layer == HCLGE_FD_USER_DEF_NONE)
		वापस;

	cfg = &hdev->fd_cfg.user_def_cfg[rule->ep.user_def.layer - 1];
	अगर (!cfg->ref_cnt)
		वापस;

	cfg->ref_cnt--;
	अगर (!cfg->ref_cnt) अणु
		cfg->offset = 0;
		set_bit(HCLGE_STATE_FD_USER_DEF_CHANGED, &hdev->state);
	पूर्ण
पूर्ण

अटल व्योम hclge_update_fd_list(काष्ठा hclge_dev *hdev,
				 क्रमागत HCLGE_FD_NODE_STATE state, u16 location,
				 काष्ठा hclge_fd_rule *new_rule)
अणु
	काष्ठा hlist_head *hlist = &hdev->fd_rule_list;
	काष्ठा hclge_fd_rule *fd_rule, *parent = शून्य;

	fd_rule = hclge_find_fd_rule(hlist, location, &parent);
	अगर (fd_rule) अणु
		hclge_fd_dec_user_def_refcnt(hdev, fd_rule);
		अगर (state == HCLGE_FD_ACTIVE)
			hclge_fd_inc_user_def_refcnt(hdev, new_rule);
		hclge_sync_fd_user_def_cfg(hdev, true);

		hclge_update_fd_rule_node(hdev, fd_rule, new_rule, state);
		वापस;
	पूर्ण

	/* it's unlikely to fail here, because we have checked the rule
	 * exist beक्रमe.
	 */
	अगर (unlikely(state == HCLGE_FD_TO_DEL || state == HCLGE_FD_DELETED)) अणु
		dev_warn(&hdev->pdev->dev,
			 "failed to delete fd rule %u, it's inexistent\n",
			 location);
		वापस;
	पूर्ण

	hclge_fd_inc_user_def_refcnt(hdev, new_rule);
	hclge_sync_fd_user_def_cfg(hdev, true);

	hclge_fd_insert_rule_node(hlist, new_rule, parent);
	hclge_fd_inc_rule_cnt(hdev, new_rule->location);

	अगर (state == HCLGE_FD_TO_ADD) अणु
		set_bit(HCLGE_STATE_FD_TBL_CHANGED, &hdev->state);
		hclge_task_schedule(hdev, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_get_fd_mode(काष्ठा hclge_dev *hdev, u8 *fd_mode)
अणु
	काष्ठा hclge_get_fd_mode_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_FD_MODE_CTRL, true);

	req = (काष्ठा hclge_get_fd_mode_cmd *)desc.data;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "get fd mode fail, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	*fd_mode = req->mode;

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_get_fd_allocation(काष्ठा hclge_dev *hdev,
				   u32 *stage1_entry_num,
				   u32 *stage2_entry_num,
				   u16 *stage1_counter_num,
				   u16 *stage2_counter_num)
अणु
	काष्ठा hclge_get_fd_allocation_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_FD_GET_ALLOCATION, true);

	req = (काष्ठा hclge_get_fd_allocation_cmd *)desc.data;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "query fd allocation fail, ret=%d\n",
			ret);
		वापस ret;
	पूर्ण

	*stage1_entry_num = le32_to_cpu(req->stage1_entry_num);
	*stage2_entry_num = le32_to_cpu(req->stage2_entry_num);
	*stage1_counter_num = le16_to_cpu(req->stage1_counter_num);
	*stage2_counter_num = le16_to_cpu(req->stage2_counter_num);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_set_fd_key_config(काष्ठा hclge_dev *hdev,
				   क्रमागत HCLGE_FD_STAGE stage_num)
अणु
	काष्ठा hclge_set_fd_key_config_cmd *req;
	काष्ठा hclge_fd_key_cfg *stage;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_FD_KEY_CONFIG, false);

	req = (काष्ठा hclge_set_fd_key_config_cmd *)desc.data;
	stage = &hdev->fd_cfg.key_cfg[stage_num];
	req->stage = stage_num;
	req->key_select = stage->key_sel;
	req->inner_sipv6_word_en = stage->inner_sipv6_word_en;
	req->inner_dipv6_word_en = stage->inner_dipv6_word_en;
	req->outer_sipv6_word_en = stage->outer_sipv6_word_en;
	req->outer_dipv6_word_en = stage->outer_dipv6_word_en;
	req->tuple_mask = cpu_to_le32(~stage->tuple_active);
	req->meta_data_mask = cpu_to_le32(~stage->meta_data_active);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "set fd key fail, ret=%d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम hclge_fd_disable_user_def(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_fd_user_def_cfg *cfg = hdev->fd_cfg.user_def_cfg;

	spin_lock_bh(&hdev->fd_rule_lock);
	स_रखो(cfg, 0, माप(hdev->fd_cfg.user_def_cfg));
	spin_unlock_bh(&hdev->fd_rule_lock);

	hclge_fd_set_user_def_cmd(hdev, cfg);
पूर्ण

अटल पूर्णांक hclge_init_fd_config(काष्ठा hclge_dev *hdev)
अणु
#घोषणा LOW_2_WORDS		0x03
	काष्ठा hclge_fd_key_cfg *key_cfg;
	पूर्णांक ret;

	अगर (!hnae3_dev_fd_supported(hdev))
		वापस 0;

	ret = hclge_get_fd_mode(hdev, &hdev->fd_cfg.fd_mode);
	अगर (ret)
		वापस ret;

	चयन (hdev->fd_cfg.fd_mode) अणु
	हाल HCLGE_FD_MODE_DEPTH_2K_WIDTH_400B_STAGE_1:
		hdev->fd_cfg.max_key_length = MAX_KEY_LENGTH;
		अवरोध;
	हाल HCLGE_FD_MODE_DEPTH_4K_WIDTH_200B_STAGE_1:
		hdev->fd_cfg.max_key_length = MAX_KEY_LENGTH / 2;
		अवरोध;
	शेष:
		dev_err(&hdev->pdev->dev,
			"Unsupported flow director mode %u\n",
			hdev->fd_cfg.fd_mode);
		वापस -EOPNOTSUPP;
	पूर्ण

	key_cfg = &hdev->fd_cfg.key_cfg[HCLGE_FD_STAGE_1];
	key_cfg->key_sel = HCLGE_FD_KEY_BASE_ON_TUPLE;
	key_cfg->inner_sipv6_word_en = LOW_2_WORDS;
	key_cfg->inner_dipv6_word_en = LOW_2_WORDS;
	key_cfg->outer_sipv6_word_en = 0;
	key_cfg->outer_dipv6_word_en = 0;

	key_cfg->tuple_active = BIT(INNER_VLAN_TAG_FST) | BIT(INNER_ETH_TYPE) |
				BIT(INNER_IP_PROTO) | BIT(INNER_IP_TOS) |
				BIT(INNER_SRC_IP) | BIT(INNER_DST_IP) |
				BIT(INNER_SRC_PORT) | BIT(INNER_DST_PORT);

	/* If use max 400bit key, we can support tuples क्रम ether type */
	अगर (hdev->fd_cfg.fd_mode == HCLGE_FD_MODE_DEPTH_2K_WIDTH_400B_STAGE_1) अणु
		key_cfg->tuple_active |=
				BIT(INNER_DST_MAC) | BIT(INNER_SRC_MAC);
		अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V3)
			key_cfg->tuple_active |= HCLGE_FD_TUPLE_USER_DEF_TUPLES;
	पूर्ण

	/* roce_type is used to filter roce frames
	 * dst_vport is used to specअगरy the rule
	 */
	key_cfg->meta_data_active = BIT(ROCE_TYPE) | BIT(DST_VPORT);

	ret = hclge_get_fd_allocation(hdev,
				      &hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1],
				      &hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_2],
				      &hdev->fd_cfg.cnt_num[HCLGE_FD_STAGE_1],
				      &hdev->fd_cfg.cnt_num[HCLGE_FD_STAGE_2]);
	अगर (ret)
		वापस ret;

	वापस hclge_set_fd_key_config(hdev, HCLGE_FD_STAGE_1);
पूर्ण

अटल पूर्णांक hclge_fd_tcam_config(काष्ठा hclge_dev *hdev, u8 stage, bool sel_x,
				पूर्णांक loc, u8 *key, bool is_add)
अणु
	काष्ठा hclge_fd_tcam_config_1_cmd *req1;
	काष्ठा hclge_fd_tcam_config_2_cmd *req2;
	काष्ठा hclge_fd_tcam_config_3_cmd *req3;
	काष्ठा hclge_desc desc[3];
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_FD_TCAM_OP, false);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_OPC_FD_TCAM_OP, false);
	desc[1].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[2], HCLGE_OPC_FD_TCAM_OP, false);

	req1 = (काष्ठा hclge_fd_tcam_config_1_cmd *)desc[0].data;
	req2 = (काष्ठा hclge_fd_tcam_config_2_cmd *)desc[1].data;
	req3 = (काष्ठा hclge_fd_tcam_config_3_cmd *)desc[2].data;

	req1->stage = stage;
	req1->xy_sel = sel_x ? 1 : 0;
	hnae3_set_bit(req1->port_info, HCLGE_FD_EPORT_SW_EN_B, 0);
	req1->index = cpu_to_le32(loc);
	req1->entry_vld = sel_x ? is_add : 0;

	अगर (key) अणु
		स_नकल(req1->tcam_data, &key[0], माप(req1->tcam_data));
		स_नकल(req2->tcam_data, &key[माप(req1->tcam_data)],
		       माप(req2->tcam_data));
		स_नकल(req3->tcam_data, &key[माप(req1->tcam_data) +
		       माप(req2->tcam_data)], माप(req3->tcam_data));
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, desc, 3);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"config tcam key fail, ret=%d\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_fd_ad_config(काष्ठा hclge_dev *hdev, u8 stage, पूर्णांक loc,
			      काष्ठा hclge_fd_ad_data *action)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);
	काष्ठा hclge_fd_ad_config_cmd *req;
	काष्ठा hclge_desc desc;
	u64 ad_data = 0;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_FD_AD_OP, false);

	req = (काष्ठा hclge_fd_ad_config_cmd *)desc.data;
	req->index = cpu_to_le32(loc);
	req->stage = stage;

	hnae3_set_bit(ad_data, HCLGE_FD_AD_WR_RULE_ID_B,
		      action->ग_लिखो_rule_id_to_bd);
	hnae3_set_field(ad_data, HCLGE_FD_AD_RULE_ID_M, HCLGE_FD_AD_RULE_ID_S,
			action->rule_id);
	अगर (test_bit(HNAE3_DEV_SUPPORT_FD_FORWARD_TC_B, ae_dev->caps)) अणु
		hnae3_set_bit(ad_data, HCLGE_FD_AD_TC_OVRD_B,
			      action->override_tc);
		hnae3_set_field(ad_data, HCLGE_FD_AD_TC_SIZE_M,
				HCLGE_FD_AD_TC_SIZE_S, (u32)action->tc_size);
	पूर्ण
	ad_data <<= 32;
	hnae3_set_bit(ad_data, HCLGE_FD_AD_DROP_B, action->drop_packet);
	hnae3_set_bit(ad_data, HCLGE_FD_AD_सूचीECT_QID_B,
		      action->क्रमward_to_direct_queue);
	hnae3_set_field(ad_data, HCLGE_FD_AD_QID_M, HCLGE_FD_AD_QID_S,
			action->queue_id);
	hnae3_set_bit(ad_data, HCLGE_FD_AD_USE_COUNTER_B, action->use_counter);
	hnae3_set_field(ad_data, HCLGE_FD_AD_COUNTER_NUM_M,
			HCLGE_FD_AD_COUNTER_NUM_S, action->counter_id);
	hnae3_set_bit(ad_data, HCLGE_FD_AD_NXT_STEP_B, action->use_next_stage);
	hnae3_set_field(ad_data, HCLGE_FD_AD_NXT_KEY_M, HCLGE_FD_AD_NXT_KEY_S,
			action->counter_id);

	req->ad_data = cpu_to_le64(ad_data);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "fd ad config fail, ret=%d\n", ret);

	वापस ret;
पूर्ण

अटल bool hclge_fd_convert_tuple(u32 tuple_bit, u8 *key_x, u8 *key_y,
				   काष्ठा hclge_fd_rule *rule)
अणु
	पूर्णांक offset, moffset, ip_offset;
	क्रमागत HCLGE_FD_KEY_OPT key_opt;
	u16 पंचांगp_x_s, पंचांगp_y_s;
	u32 पंचांगp_x_l, पंचांगp_y_l;
	u8 *p = (u8 *)rule;
	पूर्णांक i;

	अगर (rule->unused_tuple & BIT(tuple_bit))
		वापस true;

	key_opt = tuple_key_info[tuple_bit].key_opt;
	offset = tuple_key_info[tuple_bit].offset;
	moffset = tuple_key_info[tuple_bit].moffset;

	चयन (key_opt) अणु
	हाल KEY_OPT_U8:
		calc_x(*key_x, p[offset], p[moffset]);
		calc_y(*key_y, p[offset], p[moffset]);

		वापस true;
	हाल KEY_OPT_LE16:
		calc_x(पंचांगp_x_s, *(u16 *)(&p[offset]), *(u16 *)(&p[moffset]));
		calc_y(पंचांगp_y_s, *(u16 *)(&p[offset]), *(u16 *)(&p[moffset]));
		*(__le16 *)key_x = cpu_to_le16(पंचांगp_x_s);
		*(__le16 *)key_y = cpu_to_le16(पंचांगp_y_s);

		वापस true;
	हाल KEY_OPT_LE32:
		calc_x(पंचांगp_x_l, *(u32 *)(&p[offset]), *(u32 *)(&p[moffset]));
		calc_y(पंचांगp_y_l, *(u32 *)(&p[offset]), *(u32 *)(&p[moffset]));
		*(__le32 *)key_x = cpu_to_le32(पंचांगp_x_l);
		*(__le32 *)key_y = cpu_to_le32(पंचांगp_y_l);

		वापस true;
	हाल KEY_OPT_MAC:
		क्रम (i = 0; i < ETH_ALEN; i++) अणु
			calc_x(key_x[ETH_ALEN - 1 - i], p[offset + i],
			       p[moffset + i]);
			calc_y(key_y[ETH_ALEN - 1 - i], p[offset + i],
			       p[moffset + i]);
		पूर्ण

		वापस true;
	हाल KEY_OPT_IP:
		ip_offset = IPV4_INDEX * माप(u32);
		calc_x(पंचांगp_x_l, *(u32 *)(&p[offset + ip_offset]),
		       *(u32 *)(&p[moffset + ip_offset]));
		calc_y(पंचांगp_y_l, *(u32 *)(&p[offset + ip_offset]),
		       *(u32 *)(&p[moffset + ip_offset]));
		*(__le32 *)key_x = cpu_to_le32(पंचांगp_x_l);
		*(__le32 *)key_y = cpu_to_le32(पंचांगp_y_l);

		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u32 hclge_get_port_number(क्रमागत HLCGE_PORT_TYPE port_type, u8 pf_id,
				 u8 vf_id, u8 network_port_id)
अणु
	u32 port_number = 0;

	अगर (port_type == HOST_PORT) अणु
		hnae3_set_field(port_number, HCLGE_PF_ID_M, HCLGE_PF_ID_S,
				pf_id);
		hnae3_set_field(port_number, HCLGE_VF_ID_M, HCLGE_VF_ID_S,
				vf_id);
		hnae3_set_bit(port_number, HCLGE_PORT_TYPE_B, HOST_PORT);
	पूर्ण अन्यथा अणु
		hnae3_set_field(port_number, HCLGE_NETWORK_PORT_ID_M,
				HCLGE_NETWORK_PORT_ID_S, network_port_id);
		hnae3_set_bit(port_number, HCLGE_PORT_TYPE_B, NETWORK_PORT);
	पूर्ण

	वापस port_number;
पूर्ण

अटल व्योम hclge_fd_convert_meta_data(काष्ठा hclge_fd_key_cfg *key_cfg,
				       __le32 *key_x, __le32 *key_y,
				       काष्ठा hclge_fd_rule *rule)
अणु
	u32 tuple_bit, meta_data = 0, पंचांगp_x, पंचांगp_y, port_number;
	u8 cur_pos = 0, tuple_size, shअगरt_bits;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_META_DATA; i++) अणु
		tuple_size = meta_data_key_info[i].key_length;
		tuple_bit = key_cfg->meta_data_active & BIT(i);

		चयन (tuple_bit) अणु
		हाल BIT(ROCE_TYPE):
			hnae3_set_bit(meta_data, cur_pos, NIC_PACKET);
			cur_pos += tuple_size;
			अवरोध;
		हाल BIT(DST_VPORT):
			port_number = hclge_get_port_number(HOST_PORT, 0,
							    rule->vf_id, 0);
			hnae3_set_field(meta_data,
					GENMASK(cur_pos + tuple_size, cur_pos),
					cur_pos, port_number);
			cur_pos += tuple_size;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	calc_x(पंचांगp_x, meta_data, 0xFFFFFFFF);
	calc_y(पंचांगp_y, meta_data, 0xFFFFFFFF);
	shअगरt_bits = माप(meta_data) * 8 - cur_pos;

	*key_x = cpu_to_le32(पंचांगp_x << shअगरt_bits);
	*key_y = cpu_to_le32(पंचांगp_y << shअगरt_bits);
पूर्ण

/* A complete key is combined with meta data key and tuple key.
 * Meta data key is stored at the MSB region, and tuple key is stored at
 * the LSB region, unused bits will be filled 0.
 */
अटल पूर्णांक hclge_config_key(काष्ठा hclge_dev *hdev, u8 stage,
			    काष्ठा hclge_fd_rule *rule)
अणु
	काष्ठा hclge_fd_key_cfg *key_cfg = &hdev->fd_cfg.key_cfg[stage];
	u8 key_x[MAX_KEY_BYTES], key_y[MAX_KEY_BYTES];
	u8 *cur_key_x, *cur_key_y;
	u8 meta_data_region;
	u8 tuple_size;
	पूर्णांक ret;
	u32 i;

	स_रखो(key_x, 0, माप(key_x));
	स_रखो(key_y, 0, माप(key_y));
	cur_key_x = key_x;
	cur_key_y = key_y;

	क्रम (i = 0 ; i < MAX_TUPLE; i++) अणु
		bool tuple_valid;

		tuple_size = tuple_key_info[i].key_length / 8;
		अगर (!(key_cfg->tuple_active & BIT(i)))
			जारी;

		tuple_valid = hclge_fd_convert_tuple(i, cur_key_x,
						     cur_key_y, rule);
		अगर (tuple_valid) अणु
			cur_key_x += tuple_size;
			cur_key_y += tuple_size;
		पूर्ण
	पूर्ण

	meta_data_region = hdev->fd_cfg.max_key_length / 8 -
			MAX_META_DATA_LENGTH / 8;

	hclge_fd_convert_meta_data(key_cfg,
				   (__le32 *)(key_x + meta_data_region),
				   (__le32 *)(key_y + meta_data_region),
				   rule);

	ret = hclge_fd_tcam_config(hdev, stage, false, rule->location, key_y,
				   true);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"fd key_y config fail, loc=%u, ret=%d\n",
			rule->queue_id, ret);
		वापस ret;
	पूर्ण

	ret = hclge_fd_tcam_config(hdev, stage, true, rule->location, key_x,
				   true);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"fd key_x config fail, loc=%u, ret=%d\n",
			rule->queue_id, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_action(काष्ठा hclge_dev *hdev, u8 stage,
			       काष्ठा hclge_fd_rule *rule)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hclge_fd_ad_data ad_data;

	स_रखो(&ad_data, 0, माप(काष्ठा hclge_fd_ad_data));
	ad_data.ad_id = rule->location;

	अगर (rule->action == HCLGE_FD_ACTION_DROP_PACKET) अणु
		ad_data.drop_packet = true;
	पूर्ण अन्यथा अगर (rule->action == HCLGE_FD_ACTION_SELECT_TC) अणु
		ad_data.override_tc = true;
		ad_data.queue_id =
			kinfo->tc_info.tqp_offset[rule->cls_flower.tc];
		ad_data.tc_size =
			ilog2(kinfo->tc_info.tqp_count[rule->cls_flower.tc]);
	पूर्ण अन्यथा अणु
		ad_data.क्रमward_to_direct_queue = true;
		ad_data.queue_id = rule->queue_id;
	पूर्ण

	ad_data.use_counter = false;
	ad_data.counter_id = 0;

	ad_data.use_next_stage = false;
	ad_data.next_input_key = 0;

	ad_data.ग_लिखो_rule_id_to_bd = true;
	ad_data.rule_id = rule->location;

	वापस hclge_fd_ad_config(hdev, stage, ad_data.ad_id, &ad_data);
पूर्ण

अटल पूर्णांक hclge_fd_check_tcpip4_tuple(काष्ठा ethtool_tcpip4_spec *spec,
				       u32 *unused_tuple)
अणु
	अगर (!spec || !unused_tuple)
		वापस -EINVAL;

	*unused_tuple |= BIT(INNER_SRC_MAC) | BIT(INNER_DST_MAC);

	अगर (!spec->ip4src)
		*unused_tuple |= BIT(INNER_SRC_IP);

	अगर (!spec->ip4dst)
		*unused_tuple |= BIT(INNER_DST_IP);

	अगर (!spec->psrc)
		*unused_tuple |= BIT(INNER_SRC_PORT);

	अगर (!spec->pdst)
		*unused_tuple |= BIT(INNER_DST_PORT);

	अगर (!spec->tos)
		*unused_tuple |= BIT(INNER_IP_TOS);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_fd_check_ip4_tuple(काष्ठा ethtool_usrip4_spec *spec,
				    u32 *unused_tuple)
अणु
	अगर (!spec || !unused_tuple)
		वापस -EINVAL;

	*unused_tuple |= BIT(INNER_SRC_MAC) | BIT(INNER_DST_MAC) |
		BIT(INNER_SRC_PORT) | BIT(INNER_DST_PORT);

	अगर (!spec->ip4src)
		*unused_tuple |= BIT(INNER_SRC_IP);

	अगर (!spec->ip4dst)
		*unused_tuple |= BIT(INNER_DST_IP);

	अगर (!spec->tos)
		*unused_tuple |= BIT(INNER_IP_TOS);

	अगर (!spec->proto)
		*unused_tuple |= BIT(INNER_IP_PROTO);

	अगर (spec->l4_4_bytes)
		वापस -EOPNOTSUPP;

	अगर (spec->ip_ver != ETH_RX_NFC_IP4)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_fd_check_tcpip6_tuple(काष्ठा ethtool_tcpip6_spec *spec,
				       u32 *unused_tuple)
अणु
	अगर (!spec || !unused_tuple)
		वापस -EINVAL;

	*unused_tuple |= BIT(INNER_SRC_MAC) | BIT(INNER_DST_MAC);

	/* check whether src/dst ip address used */
	अगर (ipv6_addr_any((काष्ठा in6_addr *)spec->ip6src))
		*unused_tuple |= BIT(INNER_SRC_IP);

	अगर (ipv6_addr_any((काष्ठा in6_addr *)spec->ip6dst))
		*unused_tuple |= BIT(INNER_DST_IP);

	अगर (!spec->psrc)
		*unused_tuple |= BIT(INNER_SRC_PORT);

	अगर (!spec->pdst)
		*unused_tuple |= BIT(INNER_DST_PORT);

	अगर (!spec->tclass)
		*unused_tuple |= BIT(INNER_IP_TOS);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_fd_check_ip6_tuple(काष्ठा ethtool_usrip6_spec *spec,
				    u32 *unused_tuple)
अणु
	अगर (!spec || !unused_tuple)
		वापस -EINVAL;

	*unused_tuple |= BIT(INNER_SRC_MAC) | BIT(INNER_DST_MAC) |
			BIT(INNER_SRC_PORT) | BIT(INNER_DST_PORT);

	/* check whether src/dst ip address used */
	अगर (ipv6_addr_any((काष्ठा in6_addr *)spec->ip6src))
		*unused_tuple |= BIT(INNER_SRC_IP);

	अगर (ipv6_addr_any((काष्ठा in6_addr *)spec->ip6dst))
		*unused_tuple |= BIT(INNER_DST_IP);

	अगर (!spec->l4_proto)
		*unused_tuple |= BIT(INNER_IP_PROTO);

	अगर (!spec->tclass)
		*unused_tuple |= BIT(INNER_IP_TOS);

	अगर (spec->l4_4_bytes)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_fd_check_ether_tuple(काष्ठा ethhdr *spec, u32 *unused_tuple)
अणु
	अगर (!spec || !unused_tuple)
		वापस -EINVAL;

	*unused_tuple |= BIT(INNER_SRC_IP) | BIT(INNER_DST_IP) |
		BIT(INNER_SRC_PORT) | BIT(INNER_DST_PORT) |
		BIT(INNER_IP_TOS) | BIT(INNER_IP_PROTO);

	अगर (is_zero_ether_addr(spec->h_source))
		*unused_tuple |= BIT(INNER_SRC_MAC);

	अगर (is_zero_ether_addr(spec->h_dest))
		*unused_tuple |= BIT(INNER_DST_MAC);

	अगर (!spec->h_proto)
		*unused_tuple |= BIT(INNER_ETH_TYPE);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_fd_check_ext_tuple(काष्ठा hclge_dev *hdev,
				    काष्ठा ethtool_rx_flow_spec *fs,
				    u32 *unused_tuple)
अणु
	अगर (fs->flow_type & FLOW_EXT) अणु
		अगर (fs->h_ext.vlan_etype) अणु
			dev_err(&hdev->pdev->dev, "vlan-etype is not supported!\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (!fs->h_ext.vlan_tci)
			*unused_tuple |= BIT(INNER_VLAN_TAG_FST);

		अगर (fs->m_ext.vlan_tci &&
		    be16_to_cpu(fs->h_ext.vlan_tci) >= VLAN_N_VID) अणु
			dev_err(&hdev->pdev->dev,
				"failed to config vlan_tci, invalid vlan_tci: %u, max is %d.\n",
				ntohs(fs->h_ext.vlan_tci), VLAN_N_VID - 1);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		*unused_tuple |= BIT(INNER_VLAN_TAG_FST);
	पूर्ण

	अगर (fs->flow_type & FLOW_MAC_EXT) अणु
		अगर (hdev->fd_cfg.fd_mode !=
		    HCLGE_FD_MODE_DEPTH_2K_WIDTH_400B_STAGE_1) अणु
			dev_err(&hdev->pdev->dev,
				"FLOW_MAC_EXT is not supported in current fd mode!\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (is_zero_ether_addr(fs->h_ext.h_dest))
			*unused_tuple |= BIT(INNER_DST_MAC);
		अन्यथा
			*unused_tuple &= ~BIT(INNER_DST_MAC);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_fd_get_user_def_layer(u32 flow_type, u32 *unused_tuple,
				       काष्ठा hclge_fd_user_def_info *info)
अणु
	चयन (flow_type) अणु
	हाल ETHER_FLOW:
		info->layer = HCLGE_FD_USER_DEF_L2;
		*unused_tuple &= ~BIT(INNER_L2_RSV);
		अवरोध;
	हाल IP_USER_FLOW:
	हाल IPV6_USER_FLOW:
		info->layer = HCLGE_FD_USER_DEF_L3;
		*unused_tuple &= ~BIT(INNER_L3_RSV);
		अवरोध;
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		info->layer = HCLGE_FD_USER_DEF_L4;
		*unused_tuple &= ~BIT(INNER_L4_RSV);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool hclge_fd_is_user_def_all_masked(काष्ठा ethtool_rx_flow_spec *fs)
अणु
	वापस be32_to_cpu(fs->m_ext.data[1] | fs->m_ext.data[0]) == 0;
पूर्ण

अटल पूर्णांक hclge_fd_parse_user_def_field(काष्ठा hclge_dev *hdev,
					 काष्ठा ethtool_rx_flow_spec *fs,
					 u32 *unused_tuple,
					 काष्ठा hclge_fd_user_def_info *info)
अणु
	u32 tuple_active = hdev->fd_cfg.key_cfg[HCLGE_FD_STAGE_1].tuple_active;
	u32 flow_type = fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT);
	u16 data, offset, data_mask, offset_mask;
	पूर्णांक ret;

	info->layer = HCLGE_FD_USER_DEF_NONE;
	*unused_tuple |= HCLGE_FD_TUPLE_USER_DEF_TUPLES;

	अगर (!(fs->flow_type & FLOW_EXT) || hclge_fd_is_user_def_all_masked(fs))
		वापस 0;

	/* user-def data from ethtool is 64 bit value, the bit0~15 is used
	 * क्रम data, and bit32~47 is used क्रम offset.
	 */
	data = be32_to_cpu(fs->h_ext.data[1]) & HCLGE_FD_USER_DEF_DATA;
	data_mask = be32_to_cpu(fs->m_ext.data[1]) & HCLGE_FD_USER_DEF_DATA;
	offset = be32_to_cpu(fs->h_ext.data[0]) & HCLGE_FD_USER_DEF_OFFSET;
	offset_mask = be32_to_cpu(fs->m_ext.data[0]) & HCLGE_FD_USER_DEF_OFFSET;

	अगर (!(tuple_active & HCLGE_FD_TUPLE_USER_DEF_TUPLES)) अणु
		dev_err(&hdev->pdev->dev, "user-def bytes are not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (offset > HCLGE_FD_MAX_USER_DEF_OFFSET) अणु
		dev_err(&hdev->pdev->dev,
			"user-def offset[%u] should be no more than %u\n",
			offset, HCLGE_FD_MAX_USER_DEF_OFFSET);
		वापस -EINVAL;
	पूर्ण

	अगर (offset_mask != HCLGE_FD_USER_DEF_OFFSET_UNMASK) अणु
		dev_err(&hdev->pdev->dev, "user-def offset can't be masked\n");
		वापस -EINVAL;
	पूर्ण

	ret = hclge_fd_get_user_def_layer(flow_type, unused_tuple, info);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"unsupported flow type for user-def bytes, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	info->data = data;
	info->data_mask = data_mask;
	info->offset = offset;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_fd_check_spec(काष्ठा hclge_dev *hdev,
			       काष्ठा ethtool_rx_flow_spec *fs,
			       u32 *unused_tuple,
			       काष्ठा hclge_fd_user_def_info *info)
अणु
	u32 flow_type;
	पूर्णांक ret;

	अगर (fs->location >= hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1]) अणु
		dev_err(&hdev->pdev->dev,
			"failed to config fd rules, invalid rule location: %u, max is %u\n.",
			fs->location,
			hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1] - 1);
		वापस -EINVAL;
	पूर्ण

	ret = hclge_fd_parse_user_def_field(hdev, fs, unused_tuple, info);
	अगर (ret)
		वापस ret;

	flow_type = fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT);
	चयन (flow_type) अणु
	हाल SCTP_V4_FLOW:
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		ret = hclge_fd_check_tcpip4_tuple(&fs->h_u.tcp_ip4_spec,
						  unused_tuple);
		अवरोध;
	हाल IP_USER_FLOW:
		ret = hclge_fd_check_ip4_tuple(&fs->h_u.usr_ip4_spec,
					       unused_tuple);
		अवरोध;
	हाल SCTP_V6_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		ret = hclge_fd_check_tcpip6_tuple(&fs->h_u.tcp_ip6_spec,
						  unused_tuple);
		अवरोध;
	हाल IPV6_USER_FLOW:
		ret = hclge_fd_check_ip6_tuple(&fs->h_u.usr_ip6_spec,
					       unused_tuple);
		अवरोध;
	हाल ETHER_FLOW:
		अगर (hdev->fd_cfg.fd_mode !=
			HCLGE_FD_MODE_DEPTH_2K_WIDTH_400B_STAGE_1) अणु
			dev_err(&hdev->pdev->dev,
				"ETHER_FLOW is not supported in current fd mode!\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		ret = hclge_fd_check_ether_tuple(&fs->h_u.ether_spec,
						 unused_tuple);
		अवरोध;
	शेष:
		dev_err(&hdev->pdev->dev,
			"unsupported protocol type, protocol type = %#x\n",
			flow_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to check flow union tuple, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस hclge_fd_check_ext_tuple(hdev, fs, unused_tuple);
पूर्ण

अटल व्योम hclge_fd_get_tcpip4_tuple(काष्ठा hclge_dev *hdev,
				      काष्ठा ethtool_rx_flow_spec *fs,
				      काष्ठा hclge_fd_rule *rule, u8 ip_proto)
अणु
	rule->tuples.src_ip[IPV4_INDEX] =
			be32_to_cpu(fs->h_u.tcp_ip4_spec.ip4src);
	rule->tuples_mask.src_ip[IPV4_INDEX] =
			be32_to_cpu(fs->m_u.tcp_ip4_spec.ip4src);

	rule->tuples.dst_ip[IPV4_INDEX] =
			be32_to_cpu(fs->h_u.tcp_ip4_spec.ip4dst);
	rule->tuples_mask.dst_ip[IPV4_INDEX] =
			be32_to_cpu(fs->m_u.tcp_ip4_spec.ip4dst);

	rule->tuples.src_port = be16_to_cpu(fs->h_u.tcp_ip4_spec.psrc);
	rule->tuples_mask.src_port = be16_to_cpu(fs->m_u.tcp_ip4_spec.psrc);

	rule->tuples.dst_port = be16_to_cpu(fs->h_u.tcp_ip4_spec.pdst);
	rule->tuples_mask.dst_port = be16_to_cpu(fs->m_u.tcp_ip4_spec.pdst);

	rule->tuples.ip_tos = fs->h_u.tcp_ip4_spec.tos;
	rule->tuples_mask.ip_tos = fs->m_u.tcp_ip4_spec.tos;

	rule->tuples.ether_proto = ETH_P_IP;
	rule->tuples_mask.ether_proto = 0xFFFF;

	rule->tuples.ip_proto = ip_proto;
	rule->tuples_mask.ip_proto = 0xFF;
पूर्ण

अटल व्योम hclge_fd_get_ip4_tuple(काष्ठा hclge_dev *hdev,
				   काष्ठा ethtool_rx_flow_spec *fs,
				   काष्ठा hclge_fd_rule *rule)
अणु
	rule->tuples.src_ip[IPV4_INDEX] =
			be32_to_cpu(fs->h_u.usr_ip4_spec.ip4src);
	rule->tuples_mask.src_ip[IPV4_INDEX] =
			be32_to_cpu(fs->m_u.usr_ip4_spec.ip4src);

	rule->tuples.dst_ip[IPV4_INDEX] =
			be32_to_cpu(fs->h_u.usr_ip4_spec.ip4dst);
	rule->tuples_mask.dst_ip[IPV4_INDEX] =
			be32_to_cpu(fs->m_u.usr_ip4_spec.ip4dst);

	rule->tuples.ip_tos = fs->h_u.usr_ip4_spec.tos;
	rule->tuples_mask.ip_tos = fs->m_u.usr_ip4_spec.tos;

	rule->tuples.ip_proto = fs->h_u.usr_ip4_spec.proto;
	rule->tuples_mask.ip_proto = fs->m_u.usr_ip4_spec.proto;

	rule->tuples.ether_proto = ETH_P_IP;
	rule->tuples_mask.ether_proto = 0xFFFF;
पूर्ण

अटल व्योम hclge_fd_get_tcpip6_tuple(काष्ठा hclge_dev *hdev,
				      काष्ठा ethtool_rx_flow_spec *fs,
				      काष्ठा hclge_fd_rule *rule, u8 ip_proto)
अणु
	be32_to_cpu_array(rule->tuples.src_ip, fs->h_u.tcp_ip6_spec.ip6src,
			  IPV6_SIZE);
	be32_to_cpu_array(rule->tuples_mask.src_ip, fs->m_u.tcp_ip6_spec.ip6src,
			  IPV6_SIZE);

	be32_to_cpu_array(rule->tuples.dst_ip, fs->h_u.tcp_ip6_spec.ip6dst,
			  IPV6_SIZE);
	be32_to_cpu_array(rule->tuples_mask.dst_ip, fs->m_u.tcp_ip6_spec.ip6dst,
			  IPV6_SIZE);

	rule->tuples.src_port = be16_to_cpu(fs->h_u.tcp_ip6_spec.psrc);
	rule->tuples_mask.src_port = be16_to_cpu(fs->m_u.tcp_ip6_spec.psrc);

	rule->tuples.dst_port = be16_to_cpu(fs->h_u.tcp_ip6_spec.pdst);
	rule->tuples_mask.dst_port = be16_to_cpu(fs->m_u.tcp_ip6_spec.pdst);

	rule->tuples.ether_proto = ETH_P_IPV6;
	rule->tuples_mask.ether_proto = 0xFFFF;

	rule->tuples.ip_tos = fs->h_u.tcp_ip6_spec.tclass;
	rule->tuples_mask.ip_tos = fs->m_u.tcp_ip6_spec.tclass;

	rule->tuples.ip_proto = ip_proto;
	rule->tuples_mask.ip_proto = 0xFF;
पूर्ण

अटल व्योम hclge_fd_get_ip6_tuple(काष्ठा hclge_dev *hdev,
				   काष्ठा ethtool_rx_flow_spec *fs,
				   काष्ठा hclge_fd_rule *rule)
अणु
	be32_to_cpu_array(rule->tuples.src_ip, fs->h_u.usr_ip6_spec.ip6src,
			  IPV6_SIZE);
	be32_to_cpu_array(rule->tuples_mask.src_ip, fs->m_u.usr_ip6_spec.ip6src,
			  IPV6_SIZE);

	be32_to_cpu_array(rule->tuples.dst_ip, fs->h_u.usr_ip6_spec.ip6dst,
			  IPV6_SIZE);
	be32_to_cpu_array(rule->tuples_mask.dst_ip, fs->m_u.usr_ip6_spec.ip6dst,
			  IPV6_SIZE);

	rule->tuples.ip_proto = fs->h_u.usr_ip6_spec.l4_proto;
	rule->tuples_mask.ip_proto = fs->m_u.usr_ip6_spec.l4_proto;

	rule->tuples.ip_tos = fs->h_u.tcp_ip6_spec.tclass;
	rule->tuples_mask.ip_tos = fs->m_u.tcp_ip6_spec.tclass;

	rule->tuples.ether_proto = ETH_P_IPV6;
	rule->tuples_mask.ether_proto = 0xFFFF;
पूर्ण

अटल व्योम hclge_fd_get_ether_tuple(काष्ठा hclge_dev *hdev,
				     काष्ठा ethtool_rx_flow_spec *fs,
				     काष्ठा hclge_fd_rule *rule)
अणु
	ether_addr_copy(rule->tuples.src_mac, fs->h_u.ether_spec.h_source);
	ether_addr_copy(rule->tuples_mask.src_mac, fs->m_u.ether_spec.h_source);

	ether_addr_copy(rule->tuples.dst_mac, fs->h_u.ether_spec.h_dest);
	ether_addr_copy(rule->tuples_mask.dst_mac, fs->m_u.ether_spec.h_dest);

	rule->tuples.ether_proto = be16_to_cpu(fs->h_u.ether_spec.h_proto);
	rule->tuples_mask.ether_proto = be16_to_cpu(fs->m_u.ether_spec.h_proto);
पूर्ण

अटल व्योम hclge_fd_get_user_def_tuple(काष्ठा hclge_fd_user_def_info *info,
					काष्ठा hclge_fd_rule *rule)
अणु
	चयन (info->layer) अणु
	हाल HCLGE_FD_USER_DEF_L2:
		rule->tuples.l2_user_def = info->data;
		rule->tuples_mask.l2_user_def = info->data_mask;
		अवरोध;
	हाल HCLGE_FD_USER_DEF_L3:
		rule->tuples.l3_user_def = info->data;
		rule->tuples_mask.l3_user_def = info->data_mask;
		अवरोध;
	हाल HCLGE_FD_USER_DEF_L4:
		rule->tuples.l4_user_def = (u32)info->data << 16;
		rule->tuples_mask.l4_user_def = (u32)info->data_mask << 16;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rule->ep.user_def = *info;
पूर्ण

अटल पूर्णांक hclge_fd_get_tuple(काष्ठा hclge_dev *hdev,
			      काष्ठा ethtool_rx_flow_spec *fs,
			      काष्ठा hclge_fd_rule *rule,
			      काष्ठा hclge_fd_user_def_info *info)
अणु
	u32 flow_type = fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT);

	चयन (flow_type) अणु
	हाल SCTP_V4_FLOW:
		hclge_fd_get_tcpip4_tuple(hdev, fs, rule, IPPROTO_SCTP);
		अवरोध;
	हाल TCP_V4_FLOW:
		hclge_fd_get_tcpip4_tuple(hdev, fs, rule, IPPROTO_TCP);
		अवरोध;
	हाल UDP_V4_FLOW:
		hclge_fd_get_tcpip4_tuple(hdev, fs, rule, IPPROTO_UDP);
		अवरोध;
	हाल IP_USER_FLOW:
		hclge_fd_get_ip4_tuple(hdev, fs, rule);
		अवरोध;
	हाल SCTP_V6_FLOW:
		hclge_fd_get_tcpip6_tuple(hdev, fs, rule, IPPROTO_SCTP);
		अवरोध;
	हाल TCP_V6_FLOW:
		hclge_fd_get_tcpip6_tuple(hdev, fs, rule, IPPROTO_TCP);
		अवरोध;
	हाल UDP_V6_FLOW:
		hclge_fd_get_tcpip6_tuple(hdev, fs, rule, IPPROTO_UDP);
		अवरोध;
	हाल IPV6_USER_FLOW:
		hclge_fd_get_ip6_tuple(hdev, fs, rule);
		अवरोध;
	हाल ETHER_FLOW:
		hclge_fd_get_ether_tuple(hdev, fs, rule);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (fs->flow_type & FLOW_EXT) अणु
		rule->tuples.vlan_tag1 = be16_to_cpu(fs->h_ext.vlan_tci);
		rule->tuples_mask.vlan_tag1 = be16_to_cpu(fs->m_ext.vlan_tci);
		hclge_fd_get_user_def_tuple(info, rule);
	पूर्ण

	अगर (fs->flow_type & FLOW_MAC_EXT) अणु
		ether_addr_copy(rule->tuples.dst_mac, fs->h_ext.h_dest);
		ether_addr_copy(rule->tuples_mask.dst_mac, fs->m_ext.h_dest);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_fd_config_rule(काष्ठा hclge_dev *hdev,
				काष्ठा hclge_fd_rule *rule)
अणु
	पूर्णांक ret;

	ret = hclge_config_action(hdev, HCLGE_FD_STAGE_1, rule);
	अगर (ret)
		वापस ret;

	वापस hclge_config_key(hdev, HCLGE_FD_STAGE_1, rule);
पूर्ण

अटल पूर्णांक hclge_add_fd_entry_common(काष्ठा hclge_dev *hdev,
				     काष्ठा hclge_fd_rule *rule)
अणु
	पूर्णांक ret;

	spin_lock_bh(&hdev->fd_rule_lock);

	अगर (hdev->fd_active_type != rule->rule_type &&
	    (hdev->fd_active_type == HCLGE_FD_TC_FLOWER_ACTIVE ||
	     hdev->fd_active_type == HCLGE_FD_EP_ACTIVE)) अणु
		dev_err(&hdev->pdev->dev,
			"mode conflict(new type %d, active type %d), please delete existent rules first\n",
			rule->rule_type, hdev->fd_active_type);
		spin_unlock_bh(&hdev->fd_rule_lock);
		वापस -EINVAL;
	पूर्ण

	ret = hclge_fd_check_user_def_refcnt(hdev, rule);
	अगर (ret)
		जाओ out;

	ret = hclge_clear_arfs_rules(hdev);
	अगर (ret)
		जाओ out;

	ret = hclge_fd_config_rule(hdev, rule);
	अगर (ret)
		जाओ out;

	rule->state = HCLGE_FD_ACTIVE;
	hdev->fd_active_type = rule->rule_type;
	hclge_update_fd_list(hdev, rule->state, rule->location, rule);

out:
	spin_unlock_bh(&hdev->fd_rule_lock);
	वापस ret;
पूर्ण

अटल bool hclge_is_cls_flower_active(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस hdev->fd_active_type == HCLGE_FD_TC_FLOWER_ACTIVE;
पूर्ण

अटल पूर्णांक hclge_fd_parse_ring_cookie(काष्ठा hclge_dev *hdev, u64 ring_cookie,
				      u16 *vport_id, u8 *action, u16 *queue_id)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;

	अगर (ring_cookie == RX_CLS_FLOW_DISC) अणु
		*action = HCLGE_FD_ACTION_DROP_PACKET;
	पूर्ण अन्यथा अणु
		u32 ring = ethtool_get_flow_spec_ring(ring_cookie);
		u8 vf = ethtool_get_flow_spec_ring_vf(ring_cookie);
		u16 tqps;

		अगर (vf > hdev->num_req_vfs) अणु
			dev_err(&hdev->pdev->dev,
				"Error: vf id (%u) > max vf num (%u)\n",
				vf, hdev->num_req_vfs);
			वापस -EINVAL;
		पूर्ण

		*vport_id = vf ? hdev->vport[vf].vport_id : vport->vport_id;
		tqps = hdev->vport[vf].nic.kinfo.num_tqps;

		अगर (ring >= tqps) अणु
			dev_err(&hdev->pdev->dev,
				"Error: queue id (%u) > max tqp num (%u)\n",
				ring, tqps - 1);
			वापस -EINVAL;
		पूर्ण

		*action = HCLGE_FD_ACTION_SELECT_QUEUE;
		*queue_id = ring;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_add_fd_entry(काष्ठा hnae3_handle *handle,
			      काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_fd_user_def_info info;
	u16 dst_vport_id = 0, q_index = 0;
	काष्ठा ethtool_rx_flow_spec *fs;
	काष्ठा hclge_fd_rule *rule;
	u32 unused = 0;
	u8 action;
	पूर्णांक ret;

	अगर (!hnae3_dev_fd_supported(hdev)) अणु
		dev_err(&hdev->pdev->dev,
			"flow table director is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!hdev->fd_en) अणु
		dev_err(&hdev->pdev->dev,
			"please enable flow director first\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	fs = (काष्ठा ethtool_rx_flow_spec *)&cmd->fs;

	ret = hclge_fd_check_spec(hdev, fs, &unused, &info);
	अगर (ret)
		वापस ret;

	ret = hclge_fd_parse_ring_cookie(hdev, fs->ring_cookie, &dst_vport_id,
					 &action, &q_index);
	अगर (ret)
		वापस ret;

	rule = kzalloc(माप(*rule), GFP_KERNEL);
	अगर (!rule)
		वापस -ENOMEM;

	ret = hclge_fd_get_tuple(hdev, fs, rule, &info);
	अगर (ret) अणु
		kमुक्त(rule);
		वापस ret;
	पूर्ण

	rule->flow_type = fs->flow_type;
	rule->location = fs->location;
	rule->unused_tuple = unused;
	rule->vf_id = dst_vport_id;
	rule->queue_id = q_index;
	rule->action = action;
	rule->rule_type = HCLGE_FD_EP_ACTIVE;

	ret = hclge_add_fd_entry_common(hdev, rule);
	अगर (ret)
		kमुक्त(rule);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_del_fd_entry(काष्ठा hnae3_handle *handle,
			      काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा ethtool_rx_flow_spec *fs;
	पूर्णांक ret;

	अगर (!hnae3_dev_fd_supported(hdev))
		वापस -EOPNOTSUPP;

	fs = (काष्ठा ethtool_rx_flow_spec *)&cmd->fs;

	अगर (fs->location >= hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1])
		वापस -EINVAL;

	spin_lock_bh(&hdev->fd_rule_lock);
	अगर (hdev->fd_active_type == HCLGE_FD_TC_FLOWER_ACTIVE ||
	    !test_bit(fs->location, hdev->fd_bmap)) अणु
		dev_err(&hdev->pdev->dev,
			"Delete fail, rule %u is inexistent\n", fs->location);
		spin_unlock_bh(&hdev->fd_rule_lock);
		वापस -ENOENT;
	पूर्ण

	ret = hclge_fd_tcam_config(hdev, HCLGE_FD_STAGE_1, true, fs->location,
				   शून्य, false);
	अगर (ret)
		जाओ out;

	hclge_update_fd_list(hdev, HCLGE_FD_DELETED, fs->location, शून्य);

out:
	spin_unlock_bh(&hdev->fd_rule_lock);
	वापस ret;
पूर्ण

अटल व्योम hclge_clear_fd_rules_in_list(काष्ठा hclge_dev *hdev,
					 bool clear_list)
अणु
	काष्ठा hclge_fd_rule *rule;
	काष्ठा hlist_node *node;
	u16 location;

	अगर (!hnae3_dev_fd_supported(hdev))
		वापस;

	spin_lock_bh(&hdev->fd_rule_lock);

	क्रम_each_set_bit(location, hdev->fd_bmap,
			 hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1])
		hclge_fd_tcam_config(hdev, HCLGE_FD_STAGE_1, true, location,
				     शून्य, false);

	अगर (clear_list) अणु
		hlist_क्रम_each_entry_safe(rule, node, &hdev->fd_rule_list,
					  rule_node) अणु
			hlist_del(&rule->rule_node);
			kमुक्त(rule);
		पूर्ण
		hdev->fd_active_type = HCLGE_FD_RULE_NONE;
		hdev->hclge_fd_rule_num = 0;
		biपंचांगap_zero(hdev->fd_bmap,
			    hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1]);
	पूर्ण

	spin_unlock_bh(&hdev->fd_rule_lock);
पूर्ण

अटल व्योम hclge_del_all_fd_entries(काष्ठा hclge_dev *hdev)
अणु
	hclge_clear_fd_rules_in_list(hdev, true);
	hclge_fd_disable_user_def(hdev);
पूर्ण

अटल पूर्णांक hclge_restore_fd_entries(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_fd_rule *rule;
	काष्ठा hlist_node *node;

	/* Return ok here, because reset error handling will check this
	 * वापस value. If error is वापसed here, the reset process will
	 * fail.
	 */
	अगर (!hnae3_dev_fd_supported(hdev))
		वापस 0;

	/* अगर fd is disabled, should not restore it when reset */
	अगर (!hdev->fd_en)
		वापस 0;

	spin_lock_bh(&hdev->fd_rule_lock);
	hlist_क्रम_each_entry_safe(rule, node, &hdev->fd_rule_list, rule_node) अणु
		अगर (rule->state == HCLGE_FD_ACTIVE)
			rule->state = HCLGE_FD_TO_ADD;
	पूर्ण
	spin_unlock_bh(&hdev->fd_rule_lock);
	set_bit(HCLGE_STATE_FD_TBL_CHANGED, &hdev->state);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_fd_rule_cnt(काष्ठा hnae3_handle *handle,
				 काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (!hnae3_dev_fd_supported(hdev) || hclge_is_cls_flower_active(handle))
		वापस -EOPNOTSUPP;

	cmd->rule_cnt = hdev->hclge_fd_rule_num;
	cmd->data = hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1];

	वापस 0;
पूर्ण

अटल व्योम hclge_fd_get_tcpip4_info(काष्ठा hclge_fd_rule *rule,
				     काष्ठा ethtool_tcpip4_spec *spec,
				     काष्ठा ethtool_tcpip4_spec *spec_mask)
अणु
	spec->ip4src = cpu_to_be32(rule->tuples.src_ip[IPV4_INDEX]);
	spec_mask->ip4src = rule->unused_tuple & BIT(INNER_SRC_IP) ?
			0 : cpu_to_be32(rule->tuples_mask.src_ip[IPV4_INDEX]);

	spec->ip4dst = cpu_to_be32(rule->tuples.dst_ip[IPV4_INDEX]);
	spec_mask->ip4dst = rule->unused_tuple & BIT(INNER_DST_IP) ?
			0 : cpu_to_be32(rule->tuples_mask.dst_ip[IPV4_INDEX]);

	spec->psrc = cpu_to_be16(rule->tuples.src_port);
	spec_mask->psrc = rule->unused_tuple & BIT(INNER_SRC_PORT) ?
			0 : cpu_to_be16(rule->tuples_mask.src_port);

	spec->pdst = cpu_to_be16(rule->tuples.dst_port);
	spec_mask->pdst = rule->unused_tuple & BIT(INNER_DST_PORT) ?
			0 : cpu_to_be16(rule->tuples_mask.dst_port);

	spec->tos = rule->tuples.ip_tos;
	spec_mask->tos = rule->unused_tuple & BIT(INNER_IP_TOS) ?
			0 : rule->tuples_mask.ip_tos;
पूर्ण

अटल व्योम hclge_fd_get_ip4_info(काष्ठा hclge_fd_rule *rule,
				  काष्ठा ethtool_usrip4_spec *spec,
				  काष्ठा ethtool_usrip4_spec *spec_mask)
अणु
	spec->ip4src = cpu_to_be32(rule->tuples.src_ip[IPV4_INDEX]);
	spec_mask->ip4src = rule->unused_tuple & BIT(INNER_SRC_IP) ?
			0 : cpu_to_be32(rule->tuples_mask.src_ip[IPV4_INDEX]);

	spec->ip4dst = cpu_to_be32(rule->tuples.dst_ip[IPV4_INDEX]);
	spec_mask->ip4dst = rule->unused_tuple & BIT(INNER_DST_IP) ?
			0 : cpu_to_be32(rule->tuples_mask.dst_ip[IPV4_INDEX]);

	spec->tos = rule->tuples.ip_tos;
	spec_mask->tos = rule->unused_tuple & BIT(INNER_IP_TOS) ?
			0 : rule->tuples_mask.ip_tos;

	spec->proto = rule->tuples.ip_proto;
	spec_mask->proto = rule->unused_tuple & BIT(INNER_IP_PROTO) ?
			0 : rule->tuples_mask.ip_proto;

	spec->ip_ver = ETH_RX_NFC_IP4;
पूर्ण

अटल व्योम hclge_fd_get_tcpip6_info(काष्ठा hclge_fd_rule *rule,
				     काष्ठा ethtool_tcpip6_spec *spec,
				     काष्ठा ethtool_tcpip6_spec *spec_mask)
अणु
	cpu_to_be32_array(spec->ip6src,
			  rule->tuples.src_ip, IPV6_SIZE);
	cpu_to_be32_array(spec->ip6dst,
			  rule->tuples.dst_ip, IPV6_SIZE);
	अगर (rule->unused_tuple & BIT(INNER_SRC_IP))
		स_रखो(spec_mask->ip6src, 0, माप(spec_mask->ip6src));
	अन्यथा
		cpu_to_be32_array(spec_mask->ip6src, rule->tuples_mask.src_ip,
				  IPV6_SIZE);

	अगर (rule->unused_tuple & BIT(INNER_DST_IP))
		स_रखो(spec_mask->ip6dst, 0, माप(spec_mask->ip6dst));
	अन्यथा
		cpu_to_be32_array(spec_mask->ip6dst, rule->tuples_mask.dst_ip,
				  IPV6_SIZE);

	spec->tclass = rule->tuples.ip_tos;
	spec_mask->tclass = rule->unused_tuple & BIT(INNER_IP_TOS) ?
			0 : rule->tuples_mask.ip_tos;

	spec->psrc = cpu_to_be16(rule->tuples.src_port);
	spec_mask->psrc = rule->unused_tuple & BIT(INNER_SRC_PORT) ?
			0 : cpu_to_be16(rule->tuples_mask.src_port);

	spec->pdst = cpu_to_be16(rule->tuples.dst_port);
	spec_mask->pdst = rule->unused_tuple & BIT(INNER_DST_PORT) ?
			0 : cpu_to_be16(rule->tuples_mask.dst_port);
पूर्ण

अटल व्योम hclge_fd_get_ip6_info(काष्ठा hclge_fd_rule *rule,
				  काष्ठा ethtool_usrip6_spec *spec,
				  काष्ठा ethtool_usrip6_spec *spec_mask)
अणु
	cpu_to_be32_array(spec->ip6src, rule->tuples.src_ip, IPV6_SIZE);
	cpu_to_be32_array(spec->ip6dst, rule->tuples.dst_ip, IPV6_SIZE);
	अगर (rule->unused_tuple & BIT(INNER_SRC_IP))
		स_रखो(spec_mask->ip6src, 0, माप(spec_mask->ip6src));
	अन्यथा
		cpu_to_be32_array(spec_mask->ip6src,
				  rule->tuples_mask.src_ip, IPV6_SIZE);

	अगर (rule->unused_tuple & BIT(INNER_DST_IP))
		स_रखो(spec_mask->ip6dst, 0, माप(spec_mask->ip6dst));
	अन्यथा
		cpu_to_be32_array(spec_mask->ip6dst,
				  rule->tuples_mask.dst_ip, IPV6_SIZE);

	spec->tclass = rule->tuples.ip_tos;
	spec_mask->tclass = rule->unused_tuple & BIT(INNER_IP_TOS) ?
			0 : rule->tuples_mask.ip_tos;

	spec->l4_proto = rule->tuples.ip_proto;
	spec_mask->l4_proto = rule->unused_tuple & BIT(INNER_IP_PROTO) ?
			0 : rule->tuples_mask.ip_proto;
पूर्ण

अटल व्योम hclge_fd_get_ether_info(काष्ठा hclge_fd_rule *rule,
				    काष्ठा ethhdr *spec,
				    काष्ठा ethhdr *spec_mask)
अणु
	ether_addr_copy(spec->h_source, rule->tuples.src_mac);
	ether_addr_copy(spec->h_dest, rule->tuples.dst_mac);

	अगर (rule->unused_tuple & BIT(INNER_SRC_MAC))
		eth_zero_addr(spec_mask->h_source);
	अन्यथा
		ether_addr_copy(spec_mask->h_source, rule->tuples_mask.src_mac);

	अगर (rule->unused_tuple & BIT(INNER_DST_MAC))
		eth_zero_addr(spec_mask->h_dest);
	अन्यथा
		ether_addr_copy(spec_mask->h_dest, rule->tuples_mask.dst_mac);

	spec->h_proto = cpu_to_be16(rule->tuples.ether_proto);
	spec_mask->h_proto = rule->unused_tuple & BIT(INNER_ETH_TYPE) ?
			0 : cpu_to_be16(rule->tuples_mask.ether_proto);
पूर्ण

अटल व्योम hclge_fd_get_user_def_info(काष्ठा ethtool_rx_flow_spec *fs,
				       काष्ठा hclge_fd_rule *rule)
अणु
	अगर ((rule->unused_tuple & HCLGE_FD_TUPLE_USER_DEF_TUPLES) ==
	    HCLGE_FD_TUPLE_USER_DEF_TUPLES) अणु
		fs->h_ext.data[0] = 0;
		fs->h_ext.data[1] = 0;
		fs->m_ext.data[0] = 0;
		fs->m_ext.data[1] = 0;
	पूर्ण अन्यथा अणु
		fs->h_ext.data[0] = cpu_to_be32(rule->ep.user_def.offset);
		fs->h_ext.data[1] = cpu_to_be32(rule->ep.user_def.data);
		fs->m_ext.data[0] =
				cpu_to_be32(HCLGE_FD_USER_DEF_OFFSET_UNMASK);
		fs->m_ext.data[1] = cpu_to_be32(rule->ep.user_def.data_mask);
	पूर्ण
पूर्ण

अटल व्योम hclge_fd_get_ext_info(काष्ठा ethtool_rx_flow_spec *fs,
				  काष्ठा hclge_fd_rule *rule)
अणु
	अगर (fs->flow_type & FLOW_EXT) अणु
		fs->h_ext.vlan_tci = cpu_to_be16(rule->tuples.vlan_tag1);
		fs->m_ext.vlan_tci =
				rule->unused_tuple & BIT(INNER_VLAN_TAG_FST) ?
				0 : cpu_to_be16(rule->tuples_mask.vlan_tag1);

		hclge_fd_get_user_def_info(fs, rule);
	पूर्ण

	अगर (fs->flow_type & FLOW_MAC_EXT) अणु
		ether_addr_copy(fs->h_ext.h_dest, rule->tuples.dst_mac);
		अगर (rule->unused_tuple & BIT(INNER_DST_MAC))
			eth_zero_addr(fs->m_u.ether_spec.h_dest);
		अन्यथा
			ether_addr_copy(fs->m_u.ether_spec.h_dest,
					rule->tuples_mask.dst_mac);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_get_fd_rule_info(काष्ठा hnae3_handle *handle,
				  काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_fd_rule *rule = शून्य;
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा ethtool_rx_flow_spec *fs;
	काष्ठा hlist_node *node2;

	अगर (!hnae3_dev_fd_supported(hdev))
		वापस -EOPNOTSUPP;

	fs = (काष्ठा ethtool_rx_flow_spec *)&cmd->fs;

	spin_lock_bh(&hdev->fd_rule_lock);

	hlist_क्रम_each_entry_safe(rule, node2, &hdev->fd_rule_list, rule_node) अणु
		अगर (rule->location >= fs->location)
			अवरोध;
	पूर्ण

	अगर (!rule || fs->location != rule->location) अणु
		spin_unlock_bh(&hdev->fd_rule_lock);

		वापस -ENOENT;
	पूर्ण

	fs->flow_type = rule->flow_type;
	चयन (fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) अणु
	हाल SCTP_V4_FLOW:
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		hclge_fd_get_tcpip4_info(rule, &fs->h_u.tcp_ip4_spec,
					 &fs->m_u.tcp_ip4_spec);
		अवरोध;
	हाल IP_USER_FLOW:
		hclge_fd_get_ip4_info(rule, &fs->h_u.usr_ip4_spec,
				      &fs->m_u.usr_ip4_spec);
		अवरोध;
	हाल SCTP_V6_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		hclge_fd_get_tcpip6_info(rule, &fs->h_u.tcp_ip6_spec,
					 &fs->m_u.tcp_ip6_spec);
		अवरोध;
	हाल IPV6_USER_FLOW:
		hclge_fd_get_ip6_info(rule, &fs->h_u.usr_ip6_spec,
				      &fs->m_u.usr_ip6_spec);
		अवरोध;
	/* The flow type of fd rule has been checked beक्रमe adding in to rule
	 * list. As other flow types have been handled, it must be ETHER_FLOW
	 * क्रम the शेष हाल
	 */
	शेष:
		hclge_fd_get_ether_info(rule, &fs->h_u.ether_spec,
					&fs->m_u.ether_spec);
		अवरोध;
	पूर्ण

	hclge_fd_get_ext_info(fs, rule);

	अगर (rule->action == HCLGE_FD_ACTION_DROP_PACKET) अणु
		fs->ring_cookie = RX_CLS_FLOW_DISC;
	पूर्ण अन्यथा अणु
		u64 vf_id;

		fs->ring_cookie = rule->queue_id;
		vf_id = rule->vf_id;
		vf_id <<= ETHTOOL_RX_FLOW_SPEC_RING_VF_OFF;
		fs->ring_cookie |= vf_id;
	पूर्ण

	spin_unlock_bh(&hdev->fd_rule_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_all_rules(काष्ठा hnae3_handle *handle,
			       काष्ठा ethtool_rxnfc *cmd, u32 *rule_locs)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_fd_rule *rule;
	काष्ठा hlist_node *node2;
	पूर्णांक cnt = 0;

	अगर (!hnae3_dev_fd_supported(hdev))
		वापस -EOPNOTSUPP;

	cmd->data = hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1];

	spin_lock_bh(&hdev->fd_rule_lock);
	hlist_क्रम_each_entry_safe(rule, node2,
				  &hdev->fd_rule_list, rule_node) अणु
		अगर (cnt == cmd->rule_cnt) अणु
			spin_unlock_bh(&hdev->fd_rule_lock);
			वापस -EMSGSIZE;
		पूर्ण

		अगर (rule->state == HCLGE_FD_TO_DEL)
			जारी;

		rule_locs[cnt] = rule->location;
		cnt++;
	पूर्ण

	spin_unlock_bh(&hdev->fd_rule_lock);

	cmd->rule_cnt = cnt;

	वापस 0;
पूर्ण

अटल व्योम hclge_fd_get_flow_tuples(स्थिर काष्ठा flow_keys *fkeys,
				     काष्ठा hclge_fd_rule_tuples *tuples)
अणु
#घोषणा flow_ip6_src fkeys->addrs.v6addrs.src.in6_u.u6_addr32
#घोषणा flow_ip6_dst fkeys->addrs.v6addrs.dst.in6_u.u6_addr32

	tuples->ether_proto = be16_to_cpu(fkeys->basic.n_proto);
	tuples->ip_proto = fkeys->basic.ip_proto;
	tuples->dst_port = be16_to_cpu(fkeys->ports.dst);

	अगर (fkeys->basic.n_proto == htons(ETH_P_IP)) अणु
		tuples->src_ip[3] = be32_to_cpu(fkeys->addrs.v4addrs.src);
		tuples->dst_ip[3] = be32_to_cpu(fkeys->addrs.v4addrs.dst);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < IPV6_SIZE; i++) अणु
			tuples->src_ip[i] = be32_to_cpu(flow_ip6_src[i]);
			tuples->dst_ip[i] = be32_to_cpu(flow_ip6_dst[i]);
		पूर्ण
	पूर्ण
पूर्ण

/* traverse all rules, check whether an existed rule has the same tuples */
अटल काष्ठा hclge_fd_rule *
hclge_fd_search_flow_keys(काष्ठा hclge_dev *hdev,
			  स्थिर काष्ठा hclge_fd_rule_tuples *tuples)
अणु
	काष्ठा hclge_fd_rule *rule = शून्य;
	काष्ठा hlist_node *node;

	hlist_क्रम_each_entry_safe(rule, node, &hdev->fd_rule_list, rule_node) अणु
		अगर (!स_भेद(tuples, &rule->tuples, माप(*tuples)))
			वापस rule;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम hclge_fd_build_arfs_rule(स्थिर काष्ठा hclge_fd_rule_tuples *tuples,
				     काष्ठा hclge_fd_rule *rule)
अणु
	rule->unused_tuple = BIT(INNER_SRC_MAC) | BIT(INNER_DST_MAC) |
			     BIT(INNER_VLAN_TAG_FST) | BIT(INNER_IP_TOS) |
			     BIT(INNER_SRC_PORT);
	rule->action = 0;
	rule->vf_id = 0;
	rule->rule_type = HCLGE_FD_ARFS_ACTIVE;
	rule->state = HCLGE_FD_TO_ADD;
	अगर (tuples->ether_proto == ETH_P_IP) अणु
		अगर (tuples->ip_proto == IPPROTO_TCP)
			rule->flow_type = TCP_V4_FLOW;
		अन्यथा
			rule->flow_type = UDP_V4_FLOW;
	पूर्ण अन्यथा अणु
		अगर (tuples->ip_proto == IPPROTO_TCP)
			rule->flow_type = TCP_V6_FLOW;
		अन्यथा
			rule->flow_type = UDP_V6_FLOW;
	पूर्ण
	स_नकल(&rule->tuples, tuples, माप(rule->tuples));
	स_रखो(&rule->tuples_mask, 0xFF, माप(rule->tuples_mask));
पूर्ण

अटल पूर्णांक hclge_add_fd_entry_by_arfs(काष्ठा hnae3_handle *handle, u16 queue_id,
				      u16 flow_id, काष्ठा flow_keys *fkeys)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_fd_rule_tuples new_tuples = अणुपूर्ण;
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_fd_rule *rule;
	u16 bit_id;

	अगर (!hnae3_dev_fd_supported(hdev))
		वापस -EOPNOTSUPP;

	/* when there is alपढ़ोy fd rule existed add by user,
	 * arfs should not work
	 */
	spin_lock_bh(&hdev->fd_rule_lock);
	अगर (hdev->fd_active_type != HCLGE_FD_ARFS_ACTIVE &&
	    hdev->fd_active_type != HCLGE_FD_RULE_NONE) अणु
		spin_unlock_bh(&hdev->fd_rule_lock);
		वापस -EOPNOTSUPP;
	पूर्ण

	hclge_fd_get_flow_tuples(fkeys, &new_tuples);

	/* check is there flow director filter existed क्रम this flow,
	 * अगर not, create a new filter क्रम it;
	 * अगर filter exist with dअगरferent queue id, modअगरy the filter;
	 * अगर filter exist with same queue id, करो nothing
	 */
	rule = hclge_fd_search_flow_keys(hdev, &new_tuples);
	अगर (!rule) अणु
		bit_id = find_first_zero_bit(hdev->fd_bmap, MAX_FD_FILTER_NUM);
		अगर (bit_id >= hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1]) अणु
			spin_unlock_bh(&hdev->fd_rule_lock);
			वापस -ENOSPC;
		पूर्ण

		rule = kzalloc(माप(*rule), GFP_ATOMIC);
		अगर (!rule) अणु
			spin_unlock_bh(&hdev->fd_rule_lock);
			वापस -ENOMEM;
		पूर्ण

		rule->location = bit_id;
		rule->arfs.flow_id = flow_id;
		rule->queue_id = queue_id;
		hclge_fd_build_arfs_rule(&new_tuples, rule);
		hclge_update_fd_list(hdev, rule->state, rule->location, rule);
		hdev->fd_active_type = HCLGE_FD_ARFS_ACTIVE;
	पूर्ण अन्यथा अगर (rule->queue_id != queue_id) अणु
		rule->queue_id = queue_id;
		rule->state = HCLGE_FD_TO_ADD;
		set_bit(HCLGE_STATE_FD_TBL_CHANGED, &hdev->state);
		hclge_task_schedule(hdev, 0);
	पूर्ण
	spin_unlock_bh(&hdev->fd_rule_lock);
	वापस rule->location;
पूर्ण

अटल व्योम hclge_rfs_filter_expire(काष्ठा hclge_dev *hdev)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा hnae3_handle *handle = &hdev->vport[0].nic;
	काष्ठा hclge_fd_rule *rule;
	काष्ठा hlist_node *node;

	spin_lock_bh(&hdev->fd_rule_lock);
	अगर (hdev->fd_active_type != HCLGE_FD_ARFS_ACTIVE) अणु
		spin_unlock_bh(&hdev->fd_rule_lock);
		वापस;
	पूर्ण
	hlist_क्रम_each_entry_safe(rule, node, &hdev->fd_rule_list, rule_node) अणु
		अगर (rule->state != HCLGE_FD_ACTIVE)
			जारी;
		अगर (rps_may_expire_flow(handle->netdev, rule->queue_id,
					rule->arfs.flow_id, rule->location)) अणु
			rule->state = HCLGE_FD_TO_DEL;
			set_bit(HCLGE_STATE_FD_TBL_CHANGED, &hdev->state);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&hdev->fd_rule_lock);
#पूर्ण_अगर
पूर्ण

/* make sure being called after lock up with fd_rule_lock */
अटल पूर्णांक hclge_clear_arfs_rules(काष्ठा hclge_dev *hdev)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा hclge_fd_rule *rule;
	काष्ठा hlist_node *node;
	पूर्णांक ret;

	अगर (hdev->fd_active_type != HCLGE_FD_ARFS_ACTIVE)
		वापस 0;

	hlist_क्रम_each_entry_safe(rule, node, &hdev->fd_rule_list, rule_node) अणु
		चयन (rule->state) अणु
		हाल HCLGE_FD_TO_DEL:
		हाल HCLGE_FD_ACTIVE:
			ret = hclge_fd_tcam_config(hdev, HCLGE_FD_STAGE_1, true,
						   rule->location, शून्य, false);
			अगर (ret)
				वापस ret;
			fallthrough;
		हाल HCLGE_FD_TO_ADD:
			hclge_fd_dec_rule_cnt(hdev, rule->location);
			hlist_del(&rule->rule_node);
			kमुक्त(rule);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	hclge_sync_fd_state(hdev);

#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम hclge_get_cls_key_basic(स्थिर काष्ठा flow_rule *flow,
				    काष्ठा hclge_fd_rule *rule)
अणु
	अगर (flow_rule_match_key(flow, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;
		u16 ethtype_key, ethtype_mask;

		flow_rule_match_basic(flow, &match);
		ethtype_key = ntohs(match.key->n_proto);
		ethtype_mask = ntohs(match.mask->n_proto);

		अगर (ethtype_key == ETH_P_ALL) अणु
			ethtype_key = 0;
			ethtype_mask = 0;
		पूर्ण
		rule->tuples.ether_proto = ethtype_key;
		rule->tuples_mask.ether_proto = ethtype_mask;
		rule->tuples.ip_proto = match.key->ip_proto;
		rule->tuples_mask.ip_proto = match.mask->ip_proto;
	पूर्ण अन्यथा अणु
		rule->unused_tuple |= BIT(INNER_IP_PROTO);
		rule->unused_tuple |= BIT(INNER_ETH_TYPE);
	पूर्ण
पूर्ण

अटल व्योम hclge_get_cls_key_mac(स्थिर काष्ठा flow_rule *flow,
				  काष्ठा hclge_fd_rule *rule)
अणु
	अगर (flow_rule_match_key(flow, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(flow, &match);
		ether_addr_copy(rule->tuples.dst_mac, match.key->dst);
		ether_addr_copy(rule->tuples_mask.dst_mac, match.mask->dst);
		ether_addr_copy(rule->tuples.src_mac, match.key->src);
		ether_addr_copy(rule->tuples_mask.src_mac, match.mask->src);
	पूर्ण अन्यथा अणु
		rule->unused_tuple |= BIT(INNER_DST_MAC);
		rule->unused_tuple |= BIT(INNER_SRC_MAC);
	पूर्ण
पूर्ण

अटल व्योम hclge_get_cls_key_vlan(स्थिर काष्ठा flow_rule *flow,
				   काष्ठा hclge_fd_rule *rule)
अणु
	अगर (flow_rule_match_key(flow, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(flow, &match);
		rule->tuples.vlan_tag1 = match.key->vlan_id |
				(match.key->vlan_priority << VLAN_PRIO_SHIFT);
		rule->tuples_mask.vlan_tag1 = match.mask->vlan_id |
				(match.mask->vlan_priority << VLAN_PRIO_SHIFT);
	पूर्ण अन्यथा अणु
		rule->unused_tuple |= BIT(INNER_VLAN_TAG_FST);
	पूर्ण
पूर्ण

अटल व्योम hclge_get_cls_key_ip(स्थिर काष्ठा flow_rule *flow,
				 काष्ठा hclge_fd_rule *rule)
अणु
	u16 addr_type = 0;

	अगर (flow_rule_match_key(flow, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(flow, &match);
		addr_type = match.key->addr_type;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(flow, &match);
		rule->tuples.src_ip[IPV4_INDEX] = be32_to_cpu(match.key->src);
		rule->tuples_mask.src_ip[IPV4_INDEX] =
						be32_to_cpu(match.mask->src);
		rule->tuples.dst_ip[IPV4_INDEX] = be32_to_cpu(match.key->dst);
		rule->tuples_mask.dst_ip[IPV4_INDEX] =
						be32_to_cpu(match.mask->dst);
	पूर्ण अन्यथा अगर (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(flow, &match);
		be32_to_cpu_array(rule->tuples.src_ip, match.key->src.s6_addr32,
				  IPV6_SIZE);
		be32_to_cpu_array(rule->tuples_mask.src_ip,
				  match.mask->src.s6_addr32, IPV6_SIZE);
		be32_to_cpu_array(rule->tuples.dst_ip, match.key->dst.s6_addr32,
				  IPV6_SIZE);
		be32_to_cpu_array(rule->tuples_mask.dst_ip,
				  match.mask->dst.s6_addr32, IPV6_SIZE);
	पूर्ण अन्यथा अणु
		rule->unused_tuple |= BIT(INNER_SRC_IP);
		rule->unused_tuple |= BIT(INNER_DST_IP);
	पूर्ण
पूर्ण

अटल व्योम hclge_get_cls_key_port(स्थिर काष्ठा flow_rule *flow,
				   काष्ठा hclge_fd_rule *rule)
अणु
	अगर (flow_rule_match_key(flow, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(flow, &match);

		rule->tuples.src_port = be16_to_cpu(match.key->src);
		rule->tuples_mask.src_port = be16_to_cpu(match.mask->src);
		rule->tuples.dst_port = be16_to_cpu(match.key->dst);
		rule->tuples_mask.dst_port = be16_to_cpu(match.mask->dst);
	पूर्ण अन्यथा अणु
		rule->unused_tuple |= BIT(INNER_SRC_PORT);
		rule->unused_tuple |= BIT(INNER_DST_PORT);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_parse_cls_flower(काष्ठा hclge_dev *hdev,
				  काष्ठा flow_cls_offload *cls_flower,
				  काष्ठा hclge_fd_rule *rule)
अणु
	काष्ठा flow_rule *flow = flow_cls_offload_flow_rule(cls_flower);
	काष्ठा flow_dissector *dissector = flow->match.dissector;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS))) अणु
		dev_err(&hdev->pdev->dev, "unsupported key set: %#x\n",
			dissector->used_keys);
		वापस -EOPNOTSUPP;
	पूर्ण

	hclge_get_cls_key_basic(flow, rule);
	hclge_get_cls_key_mac(flow, rule);
	hclge_get_cls_key_vlan(flow, rule);
	hclge_get_cls_key_ip(flow, rule);
	hclge_get_cls_key_port(flow, rule);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_check_cls_flower(काष्ठा hclge_dev *hdev,
				  काष्ठा flow_cls_offload *cls_flower, पूर्णांक tc)
अणु
	u32 prio = cls_flower->common.prio;

	अगर (tc < 0 || tc > hdev->tc_max) अणु
		dev_err(&hdev->pdev->dev, "invalid traffic class\n");
		वापस -EINVAL;
	पूर्ण

	अगर (prio == 0 ||
	    prio > hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1]) अणु
		dev_err(&hdev->pdev->dev,
			"prio %u should be in range[1, %u]\n",
			prio, hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1]);
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(prio - 1, hdev->fd_bmap)) अणु
		dev_err(&hdev->pdev->dev, "prio %u is already used\n", prio);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_add_cls_flower(काष्ठा hnae3_handle *handle,
				काष्ठा flow_cls_offload *cls_flower,
				पूर्णांक tc)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_fd_rule *rule;
	पूर्णांक ret;

	ret = hclge_check_cls_flower(hdev, cls_flower, tc);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to check cls flower params, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	rule = kzalloc(माप(*rule), GFP_KERNEL);
	अगर (!rule)
		वापस -ENOMEM;

	ret = hclge_parse_cls_flower(hdev, cls_flower, rule);
	अगर (ret) अणु
		kमुक्त(rule);
		वापस ret;
	पूर्ण

	rule->action = HCLGE_FD_ACTION_SELECT_TC;
	rule->cls_flower.tc = tc;
	rule->location = cls_flower->common.prio - 1;
	rule->vf_id = 0;
	rule->cls_flower.cookie = cls_flower->cookie;
	rule->rule_type = HCLGE_FD_TC_FLOWER_ACTIVE;

	ret = hclge_add_fd_entry_common(hdev, rule);
	अगर (ret)
		kमुक्त(rule);

	वापस ret;
पूर्ण

अटल काष्ठा hclge_fd_rule *hclge_find_cls_flower(काष्ठा hclge_dev *hdev,
						   अचिन्हित दीर्घ cookie)
अणु
	काष्ठा hclge_fd_rule *rule;
	काष्ठा hlist_node *node;

	hlist_क्रम_each_entry_safe(rule, node, &hdev->fd_rule_list, rule_node) अणु
		अगर (rule->cls_flower.cookie == cookie)
			वापस rule;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक hclge_del_cls_flower(काष्ठा hnae3_handle *handle,
				काष्ठा flow_cls_offload *cls_flower)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_fd_rule *rule;
	पूर्णांक ret;

	spin_lock_bh(&hdev->fd_rule_lock);

	rule = hclge_find_cls_flower(hdev, cls_flower->cookie);
	अगर (!rule) अणु
		spin_unlock_bh(&hdev->fd_rule_lock);
		वापस -EINVAL;
	पूर्ण

	ret = hclge_fd_tcam_config(hdev, HCLGE_FD_STAGE_1, true, rule->location,
				   शून्य, false);
	अगर (ret) अणु
		spin_unlock_bh(&hdev->fd_rule_lock);
		वापस ret;
	पूर्ण

	hclge_update_fd_list(hdev, HCLGE_FD_DELETED, rule->location, शून्य);
	spin_unlock_bh(&hdev->fd_rule_lock);

	वापस 0;
पूर्ण

अटल व्योम hclge_sync_fd_list(काष्ठा hclge_dev *hdev, काष्ठा hlist_head *hlist)
अणु
	काष्ठा hclge_fd_rule *rule;
	काष्ठा hlist_node *node;
	पूर्णांक ret = 0;

	अगर (!test_and_clear_bit(HCLGE_STATE_FD_TBL_CHANGED, &hdev->state))
		वापस;

	spin_lock_bh(&hdev->fd_rule_lock);

	hlist_क्रम_each_entry_safe(rule, node, hlist, rule_node) अणु
		चयन (rule->state) अणु
		हाल HCLGE_FD_TO_ADD:
			ret = hclge_fd_config_rule(hdev, rule);
			अगर (ret)
				जाओ out;
			rule->state = HCLGE_FD_ACTIVE;
			अवरोध;
		हाल HCLGE_FD_TO_DEL:
			ret = hclge_fd_tcam_config(hdev, HCLGE_FD_STAGE_1, true,
						   rule->location, शून्य, false);
			अगर (ret)
				जाओ out;
			hclge_fd_dec_rule_cnt(hdev, rule->location);
			hclge_fd_मुक्त_node(hdev, rule);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

out:
	अगर (ret)
		set_bit(HCLGE_STATE_FD_TBL_CHANGED, &hdev->state);

	spin_unlock_bh(&hdev->fd_rule_lock);
पूर्ण

अटल व्योम hclge_sync_fd_table(काष्ठा hclge_dev *hdev)
अणु
	अगर (test_and_clear_bit(HCLGE_STATE_FD_CLEAR_ALL, &hdev->state)) अणु
		bool clear_list = hdev->fd_active_type == HCLGE_FD_ARFS_ACTIVE;

		hclge_clear_fd_rules_in_list(hdev, clear_list);
	पूर्ण

	hclge_sync_fd_user_def_cfg(hdev, false);

	hclge_sync_fd_list(hdev, &hdev->fd_rule_list);
पूर्ण

अटल bool hclge_get_hw_reset_stat(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस hclge_पढ़ो_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG) ||
	       hclge_पढ़ो_dev(&hdev->hw, HCLGE_FUN_RST_ING);
पूर्ण

अटल bool hclge_get_cmdq_stat(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस test_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);
पूर्ण

अटल bool hclge_ae_dev_resetting(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state);
पूर्ण

अटल अचिन्हित दीर्घ hclge_ae_dev_reset_cnt(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस hdev->rst_stats.hw_reset_करोne_cnt;
पूर्ण

अटल व्योम hclge_enable_fd(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	hdev->fd_en = enable;

	अगर (!enable)
		set_bit(HCLGE_STATE_FD_CLEAR_ALL, &hdev->state);
	अन्यथा
		hclge_restore_fd_entries(handle);

	hclge_task_schedule(hdev, 0);
पूर्ण

अटल व्योम hclge_cfg_mac_mode(काष्ठा hclge_dev *hdev, bool enable)
अणु
	काष्ठा hclge_desc desc;
	काष्ठा hclge_config_mac_mode_cmd *req =
		(काष्ठा hclge_config_mac_mode_cmd *)desc.data;
	u32 loop_en = 0;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_MAC_MODE, false);

	अगर (enable) अणु
		hnae3_set_bit(loop_en, HCLGE_MAC_TX_EN_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_RX_EN_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_PAD_TX_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_PAD_RX_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_FCS_TX_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_RX_FCS_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_RX_FCS_STRIP_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_TX_OVERSIZE_TRUNCATE_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_RX_OVERSIZE_TRUNCATE_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_TX_UNDER_MIN_ERR_B, 1U);
	पूर्ण

	req->txrx_pad_fcs_loop_en = cpu_to_le32(loop_en);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"mac enable fail, ret =%d.\n", ret);
पूर्ण

अटल पूर्णांक hclge_config_चयन_param(काष्ठा hclge_dev *hdev, पूर्णांक vfid,
				     u8 चयन_param, u8 param_mask)
अणु
	काष्ठा hclge_mac_vlan_चयन_cmd *req;
	काष्ठा hclge_desc desc;
	u32 func_id;
	पूर्णांक ret;

	func_id = hclge_get_port_number(HOST_PORT, 0, vfid, 0);
	req = (काष्ठा hclge_mac_vlan_चयन_cmd *)desc.data;

	/* पढ़ो current config parameter */
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_VLAN_SWITCH_PARAM,
				   true);
	req->roce_sel = HCLGE_MAC_VLAN_NIC_SEL;
	req->func_id = cpu_to_le32(func_id);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"read mac vlan switch parameter fail, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	/* modअगरy and ग_लिखो new config parameter */
	hclge_cmd_reuse_desc(&desc, false);
	req->चयन_param = (req->चयन_param & param_mask) | चयन_param;
	req->param_mask = param_mask;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"set mac vlan switch parameter fail, ret = %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम hclge_phy_link_status_रुको(काष्ठा hclge_dev *hdev,
				       पूर्णांक link_ret)
अणु
#घोषणा HCLGE_PHY_LINK_STATUS_NUM  200

	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;
	पूर्णांक i = 0;
	पूर्णांक ret;

	करो अणु
		ret = phy_पढ़ो_status(phydev);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"phy update link status fail, ret = %d\n", ret);
			वापस;
		पूर्ण

		अगर (phydev->link == link_ret)
			अवरोध;

		msleep(HCLGE_LINK_STATUS_MS);
	पूर्ण जबतक (++i < HCLGE_PHY_LINK_STATUS_NUM);
पूर्ण

अटल पूर्णांक hclge_mac_link_status_रुको(काष्ठा hclge_dev *hdev, पूर्णांक link_ret)
अणु
#घोषणा HCLGE_MAC_LINK_STATUS_NUM  100

	पूर्णांक link_status;
	पूर्णांक i = 0;
	पूर्णांक ret;

	करो अणु
		ret = hclge_get_mac_link_status(hdev, &link_status);
		अगर (ret)
			वापस ret;
		अगर (link_status == link_ret)
			वापस 0;

		msleep(HCLGE_LINK_STATUS_MS);
	पूर्ण जबतक (++i < HCLGE_MAC_LINK_STATUS_NUM);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक hclge_mac_phy_link_status_रुको(काष्ठा hclge_dev *hdev, bool en,
					  bool is_phy)
अणु
	पूर्णांक link_ret;

	link_ret = en ? HCLGE_LINK_STATUS_UP : HCLGE_LINK_STATUS_DOWN;

	अगर (is_phy)
		hclge_phy_link_status_रुको(hdev, link_ret);

	वापस hclge_mac_link_status_रुको(hdev, link_ret);
पूर्ण

अटल पूर्णांक hclge_set_app_loopback(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा hclge_config_mac_mode_cmd *req;
	काष्ठा hclge_desc desc;
	u32 loop_en;
	पूर्णांक ret;

	req = (काष्ठा hclge_config_mac_mode_cmd *)&desc.data[0];
	/* 1 Read out the MAC mode config at first */
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_MAC_MODE, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"mac loopback get fail, ret =%d.\n", ret);
		वापस ret;
	पूर्ण

	/* 2 Then setup the loopback flag */
	loop_en = le32_to_cpu(req->txrx_pad_fcs_loop_en);
	hnae3_set_bit(loop_en, HCLGE_MAC_APP_LP_B, en ? 1 : 0);

	req->txrx_pad_fcs_loop_en = cpu_to_le32(loop_en);

	/* 3 Config mac work mode with loopback flag
	 * and its original configure parameters
	 */
	hclge_cmd_reuse_desc(&desc, false);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"mac loopback set fail, ret =%d.\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_cfg_common_loopback(काष्ठा hclge_dev *hdev, bool en,
				     क्रमागत hnae3_loop loop_mode)
अणु
#घोषणा HCLGE_COMMON_LB_RETRY_MS	10
#घोषणा HCLGE_COMMON_LB_RETRY_NUM	100

	काष्ठा hclge_common_lb_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret, i = 0;
	u8 loop_mode_b;

	req = (काष्ठा hclge_common_lb_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_COMMON_LOOPBACK, false);

	चयन (loop_mode) अणु
	हाल HNAE3_LOOP_SERIAL_SERDES:
		loop_mode_b = HCLGE_CMD_SERDES_SERIAL_INNER_LOOP_B;
		अवरोध;
	हाल HNAE3_LOOP_PARALLEL_SERDES:
		loop_mode_b = HCLGE_CMD_SERDES_PARALLEL_INNER_LOOP_B;
		अवरोध;
	हाल HNAE3_LOOP_PHY:
		loop_mode_b = HCLGE_CMD_GE_PHY_INNER_LOOP_B;
		अवरोध;
	शेष:
		dev_err(&hdev->pdev->dev,
			"unsupported common loopback mode %d\n", loop_mode);
		वापस -ENOTSUPP;
	पूर्ण

	अगर (en) अणु
		req->enable = loop_mode_b;
		req->mask = loop_mode_b;
	पूर्ण अन्यथा अणु
		req->mask = loop_mode_b;
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"common loopback set fail, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	करो अणु
		msleep(HCLGE_COMMON_LB_RETRY_MS);
		hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_COMMON_LOOPBACK,
					   true);
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"common loopback get, ret = %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण जबतक (++i < HCLGE_COMMON_LB_RETRY_NUM &&
		 !(req->result & HCLGE_CMD_COMMON_LB_DONE_B));

	अगर (!(req->result & HCLGE_CMD_COMMON_LB_DONE_B)) अणु
		dev_err(&hdev->pdev->dev, "common loopback set timeout\n");
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (!(req->result & HCLGE_CMD_COMMON_LB_SUCCESS_B)) अणु
		dev_err(&hdev->pdev->dev, "common loopback set failed in fw\n");
		वापस -EIO;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_set_common_loopback(काष्ठा hclge_dev *hdev, bool en,
				     क्रमागत hnae3_loop loop_mode)
अणु
	पूर्णांक ret;

	ret = hclge_cfg_common_loopback(hdev, en, loop_mode);
	अगर (ret)
		वापस ret;

	hclge_cfg_mac_mode(hdev, en);

	ret = hclge_mac_phy_link_status_रुको(hdev, en, false);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"serdes loopback config mac mode timeout\n");

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_enable_phy_loopback(काष्ठा hclge_dev *hdev,
				     काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	अगर (!phydev->suspended) अणु
		ret = phy_suspend(phydev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = phy_resume(phydev);
	अगर (ret)
		वापस ret;

	वापस phy_loopback(phydev, true);
पूर्ण

अटल पूर्णांक hclge_disable_phy_loopback(काष्ठा hclge_dev *hdev,
				      काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_loopback(phydev, false);
	अगर (ret)
		वापस ret;

	वापस phy_suspend(phydev);
पूर्ण

अटल पूर्णांक hclge_set_phy_loopback(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;
	पूर्णांक ret;

	अगर (!phydev) अणु
		अगर (hnae3_dev_phy_imp_supported(hdev))
			वापस hclge_set_common_loopback(hdev, en,
							 HNAE3_LOOP_PHY);
		वापस -ENOTSUPP;
	पूर्ण

	अगर (en)
		ret = hclge_enable_phy_loopback(hdev, phydev);
	अन्यथा
		ret = hclge_disable_phy_loopback(hdev, phydev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"set phy loopback fail, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	hclge_cfg_mac_mode(hdev, en);

	ret = hclge_mac_phy_link_status_रुको(hdev, en, true);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"phy loopback config mac mode timeout\n");

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_tqp_enable_cmd_send(काष्ठा hclge_dev *hdev, u16 tqp_id,
				     u16 stream_id, bool enable)
अणु
	काष्ठा hclge_desc desc;
	काष्ठा hclge_cfg_com_tqp_queue_cmd *req =
		(काष्ठा hclge_cfg_com_tqp_queue_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_COM_TQP_QUEUE, false);
	req->tqp_id = cpu_to_le16(tqp_id);
	req->stream_id = cpu_to_le16(stream_id);
	अगर (enable)
		req->enable |= 1U << HCLGE_TQP_ENABLE_B;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_tqp_enable(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;
	u16 i;

	क्रम (i = 0; i < handle->kinfo.num_tqps; i++) अणु
		ret = hclge_tqp_enable_cmd_send(hdev, i, 0, enable);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_loopback(काष्ठा hnae3_handle *handle,
			      क्रमागत hnae3_loop loop_mode, bool en)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	/* Loopback can be enabled in three places: SSU, MAC, and serdes. By
	 * शेष, SSU loopback is enabled, so अगर the SMAC and the DMAC are
	 * the same, the packets are looped back in the SSU. If SSU loopback
	 * is disabled, packets can reach MAC even अगर SMAC is the same as DMAC.
	 */
	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2) अणु
		u8 चयन_param = en ? 0 : BIT(HCLGE_SWITCH_ALW_LPBK_B);

		ret = hclge_config_चयन_param(hdev, PF_VPORT_ID, चयन_param,
						HCLGE_SWITCH_ALW_LPBK_MASK);
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (loop_mode) अणु
	हाल HNAE3_LOOP_APP:
		ret = hclge_set_app_loopback(hdev, en);
		अवरोध;
	हाल HNAE3_LOOP_SERIAL_SERDES:
	हाल HNAE3_LOOP_PARALLEL_SERDES:
		ret = hclge_set_common_loopback(hdev, en, loop_mode);
		अवरोध;
	हाल HNAE3_LOOP_PHY:
		ret = hclge_set_phy_loopback(hdev, en);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		dev_err(&hdev->pdev->dev,
			"loop_mode %d is not supported\n", loop_mode);
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	ret = hclge_tqp_enable(handle, en);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "failed to %s tqp in loopback, ret = %d\n",
			en ? "enable" : "disable", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_set_शेष_loopback(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_set_app_loopback(hdev, false);
	अगर (ret)
		वापस ret;

	ret = hclge_cfg_common_loopback(hdev, false, HNAE3_LOOP_SERIAL_SERDES);
	अगर (ret)
		वापस ret;

	वापस hclge_cfg_common_loopback(hdev, false,
					 HNAE3_LOOP_PARALLEL_SERDES);
पूर्ण

अटल व्योम hclge_reset_tqp_stats(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hnae3_knic_निजी_info *kinfo;
	काष्ठा hnae3_queue *queue;
	काष्ठा hclge_tqp *tqp;
	पूर्णांक i;

	kinfo = &vport->nic.kinfo;
	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		queue = handle->kinfo.tqp[i];
		tqp = container_of(queue, काष्ठा hclge_tqp, q);
		स_रखो(&tqp->tqp_stats, 0, माप(tqp->tqp_stats));
	पूर्ण
पूर्ण

अटल व्योम hclge_flush_link_update(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_FLUSH_LINK_TIMEOUT	100000

	अचिन्हित दीर्घ last = hdev->serv_processed_cnt;
	पूर्णांक i = 0;

	जबतक (test_bit(HCLGE_STATE_LINK_UPDATING, &hdev->state) &&
	       i++ < HCLGE_FLUSH_LINK_TIMEOUT &&
	       last == hdev->serv_processed_cnt)
		usleep_range(1, 1);
पूर्ण

अटल व्योम hclge_set_समयr_task(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (enable) अणु
		hclge_task_schedule(hdev, 0);
	पूर्ण अन्यथा अणु
		/* Set the DOWN flag here to disable link updating */
		set_bit(HCLGE_STATE_DOWN, &hdev->state);

		/* flush memory to make sure DOWN is seen by service task */
		smp_mb__beक्रमe_atomic();
		hclge_flush_link_update(hdev);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_ae_start(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	/* mac enable */
	hclge_cfg_mac_mode(hdev, true);
	clear_bit(HCLGE_STATE_DOWN, &hdev->state);
	hdev->hw.mac.link = 0;

	/* reset tqp stats */
	hclge_reset_tqp_stats(handle);

	hclge_mac_start_phy(hdev);

	वापस 0;
पूर्ण

अटल व्योम hclge_ae_stop(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	set_bit(HCLGE_STATE_DOWN, &hdev->state);
	spin_lock_bh(&hdev->fd_rule_lock);
	hclge_clear_arfs_rules(hdev);
	spin_unlock_bh(&hdev->fd_rule_lock);

	/* If it is not PF reset, the firmware will disable the MAC,
	 * so it only need to stop phy here.
	 */
	अगर (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state) &&
	    hdev->reset_type != HNAE3_FUNC_RESET) अणु
		hclge_mac_stop_phy(hdev);
		hclge_update_link_status(hdev);
		वापस;
	पूर्ण

	hclge_reset_tqp(handle);

	hclge_config_mac_tnl_पूर्णांक(hdev, false);

	/* Mac disable */
	hclge_cfg_mac_mode(hdev, false);

	hclge_mac_stop_phy(hdev);

	/* reset tqp stats */
	hclge_reset_tqp_stats(handle);
	hclge_update_link_status(hdev);
पूर्ण

पूर्णांक hclge_vport_start(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_dev *hdev = vport->back;

	set_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state);
	vport->last_active_jअगरfies = jअगरfies;

	अगर (test_bit(vport->vport_id, hdev->vport_config_block)) अणु
		अगर (vport->vport_id) अणु
			hclge_restore_mac_table_common(vport);
			hclge_restore_vport_vlan_table(vport);
		पूर्ण अन्यथा अणु
			hclge_restore_hw_table(hdev);
		पूर्ण
	पूर्ण

	clear_bit(vport->vport_id, hdev->vport_config_block);

	वापस 0;
पूर्ण

व्योम hclge_vport_stop(काष्ठा hclge_vport *vport)
अणु
	clear_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state);
पूर्ण

अटल पूर्णांक hclge_client_start(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);

	वापस hclge_vport_start(vport);
पूर्ण

अटल व्योम hclge_client_stop(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);

	hclge_vport_stop(vport);
पूर्ण

अटल पूर्णांक hclge_get_mac_vlan_cmd_status(काष्ठा hclge_vport *vport,
					 u16 cmdq_resp, u8  resp_code,
					 क्रमागत hclge_mac_vlan_tbl_opcode op)
अणु
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (cmdq_resp) अणु
		dev_err(&hdev->pdev->dev,
			"cmdq execute failed for get_mac_vlan_cmd_status,status=%u.\n",
			cmdq_resp);
		वापस -EIO;
	पूर्ण

	अगर (op == HCLGE_MAC_VLAN_ADD) अणु
		अगर (!resp_code || resp_code == 1)
			वापस 0;
		अन्यथा अगर (resp_code == HCLGE_ADD_UC_OVERFLOW ||
			 resp_code == HCLGE_ADD_MC_OVERFLOW)
			वापस -ENOSPC;

		dev_err(&hdev->pdev->dev,
			"add mac addr failed for undefined, code=%u.\n",
			resp_code);
		वापस -EIO;
	पूर्ण अन्यथा अगर (op == HCLGE_MAC_VLAN_REMOVE) अणु
		अगर (!resp_code) अणु
			वापस 0;
		पूर्ण अन्यथा अगर (resp_code == 1) अणु
			dev_dbg(&hdev->pdev->dev,
				"remove mac addr failed for miss.\n");
			वापस -ENOENT;
		पूर्ण

		dev_err(&hdev->pdev->dev,
			"remove mac addr failed for undefined, code=%u.\n",
			resp_code);
		वापस -EIO;
	पूर्ण अन्यथा अगर (op == HCLGE_MAC_VLAN_LKUP) अणु
		अगर (!resp_code) अणु
			वापस 0;
		पूर्ण अन्यथा अगर (resp_code == 1) अणु
			dev_dbg(&hdev->pdev->dev,
				"lookup mac addr failed for miss.\n");
			वापस -ENOENT;
		पूर्ण

		dev_err(&hdev->pdev->dev,
			"lookup mac addr failed for undefined, code=%u.\n",
			resp_code);
		वापस -EIO;
	पूर्ण

	dev_err(&hdev->pdev->dev,
		"unknown opcode for get_mac_vlan_cmd_status, opcode=%d.\n", op);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hclge_update_desc_vfid(काष्ठा hclge_desc *desc, पूर्णांक vfid, bool clr)
अणु
#घोषणा HCLGE_VF_NUM_IN_FIRST_DESC 192

	अचिन्हित पूर्णांक word_num;
	अचिन्हित पूर्णांक bit_num;

	अगर (vfid > 255 || vfid < 0)
		वापस -EIO;

	अगर (vfid >= 0 && vfid < HCLGE_VF_NUM_IN_FIRST_DESC) अणु
		word_num = vfid / 32;
		bit_num  = vfid % 32;
		अगर (clr)
			desc[1].data[word_num] &= cpu_to_le32(~(1 << bit_num));
		अन्यथा
			desc[1].data[word_num] |= cpu_to_le32(1 << bit_num);
	पूर्ण अन्यथा अणु
		word_num = (vfid - HCLGE_VF_NUM_IN_FIRST_DESC) / 32;
		bit_num  = vfid % 32;
		अगर (clr)
			desc[2].data[word_num] &= cpu_to_le32(~(1 << bit_num));
		अन्यथा
			desc[2].data[word_num] |= cpu_to_le32(1 << bit_num);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool hclge_is_all_function_id_zero(काष्ठा hclge_desc *desc)
अणु
#घोषणा HCLGE_DESC_NUMBER 3
#घोषणा HCLGE_FUNC_NUMBER_PER_DESC 6
	पूर्णांक i, j;

	क्रम (i = 1; i < HCLGE_DESC_NUMBER; i++)
		क्रम (j = 0; j < HCLGE_FUNC_NUMBER_PER_DESC; j++)
			अगर (desc[i].data[j])
				वापस false;

	वापस true;
पूर्ण

अटल व्योम hclge_prepare_mac_addr(काष्ठा hclge_mac_vlan_tbl_entry_cmd *new_req,
				   स्थिर u8 *addr, bool is_mc)
अणु
	स्थिर अचिन्हित अक्षर *mac_addr = addr;
	u32 high_val = mac_addr[2] << 16 | (mac_addr[3] << 24) |
		       (mac_addr[0]) | (mac_addr[1] << 8);
	u32 low_val  = mac_addr[4] | (mac_addr[5] << 8);

	hnae3_set_bit(new_req->flags, HCLGE_MAC_VLAN_BIT0_EN_B, 1);
	अगर (is_mc) अणु
		hnae3_set_bit(new_req->entry_type, HCLGE_MAC_VLAN_BIT1_EN_B, 1);
		hnae3_set_bit(new_req->mc_mac_en, HCLGE_MAC_VLAN_BIT0_EN_B, 1);
	पूर्ण

	new_req->mac_addr_hi32 = cpu_to_le32(high_val);
	new_req->mac_addr_lo16 = cpu_to_le16(low_val & 0xffff);
पूर्ण

अटल पूर्णांक hclge_हटाओ_mac_vlan_tbl(काष्ठा hclge_vport *vport,
				     काष्ठा hclge_mac_vlan_tbl_entry_cmd *req)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_desc desc;
	u8 resp_code;
	u16 retval;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_VLAN_REMOVE, false);

	स_नकल(desc.data, req, माप(काष्ठा hclge_mac_vlan_tbl_entry_cmd));

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"del mac addr failed for cmd_send, ret =%d.\n",
			ret);
		वापस ret;
	पूर्ण
	resp_code = (le32_to_cpu(desc.data[0]) >> 8) & 0xff;
	retval = le16_to_cpu(desc.retval);

	वापस hclge_get_mac_vlan_cmd_status(vport, retval, resp_code,
					     HCLGE_MAC_VLAN_REMOVE);
पूर्ण

अटल पूर्णांक hclge_lookup_mac_vlan_tbl(काष्ठा hclge_vport *vport,
				     काष्ठा hclge_mac_vlan_tbl_entry_cmd *req,
				     काष्ठा hclge_desc *desc,
				     bool is_mc)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	u8 resp_code;
	u16 retval;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_MAC_VLAN_ADD, true);
	अगर (is_mc) अणु
		desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		स_नकल(desc[0].data,
		       req,
		       माप(काष्ठा hclge_mac_vlan_tbl_entry_cmd));
		hclge_cmd_setup_basic_desc(&desc[1],
					   HCLGE_OPC_MAC_VLAN_ADD,
					   true);
		desc[1].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		hclge_cmd_setup_basic_desc(&desc[2],
					   HCLGE_OPC_MAC_VLAN_ADD,
					   true);
		ret = hclge_cmd_send(&hdev->hw, desc, 3);
	पूर्ण अन्यथा अणु
		स_नकल(desc[0].data,
		       req,
		       माप(काष्ठा hclge_mac_vlan_tbl_entry_cmd));
		ret = hclge_cmd_send(&hdev->hw, desc, 1);
	पूर्ण
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"lookup mac addr failed for cmd_send, ret =%d.\n",
			ret);
		वापस ret;
	पूर्ण
	resp_code = (le32_to_cpu(desc[0].data[0]) >> 8) & 0xff;
	retval = le16_to_cpu(desc[0].retval);

	वापस hclge_get_mac_vlan_cmd_status(vport, retval, resp_code,
					     HCLGE_MAC_VLAN_LKUP);
पूर्ण

अटल पूर्णांक hclge_add_mac_vlan_tbl(काष्ठा hclge_vport *vport,
				  काष्ठा hclge_mac_vlan_tbl_entry_cmd *req,
				  काष्ठा hclge_desc *mc_desc)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक cfg_status;
	u8 resp_code;
	u16 retval;
	पूर्णांक ret;

	अगर (!mc_desc) अणु
		काष्ठा hclge_desc desc;

		hclge_cmd_setup_basic_desc(&desc,
					   HCLGE_OPC_MAC_VLAN_ADD,
					   false);
		स_नकल(desc.data, req,
		       माप(काष्ठा hclge_mac_vlan_tbl_entry_cmd));
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		resp_code = (le32_to_cpu(desc.data[0]) >> 8) & 0xff;
		retval = le16_to_cpu(desc.retval);

		cfg_status = hclge_get_mac_vlan_cmd_status(vport, retval,
							   resp_code,
							   HCLGE_MAC_VLAN_ADD);
	पूर्ण अन्यथा अणु
		hclge_cmd_reuse_desc(&mc_desc[0], false);
		mc_desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		hclge_cmd_reuse_desc(&mc_desc[1], false);
		mc_desc[1].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		hclge_cmd_reuse_desc(&mc_desc[2], false);
		mc_desc[2].flag &= cpu_to_le16(~HCLGE_CMD_FLAG_NEXT);
		स_नकल(mc_desc[0].data, req,
		       माप(काष्ठा hclge_mac_vlan_tbl_entry_cmd));
		ret = hclge_cmd_send(&hdev->hw, mc_desc, 3);
		resp_code = (le32_to_cpu(mc_desc[0].data[0]) >> 8) & 0xff;
		retval = le16_to_cpu(mc_desc[0].retval);

		cfg_status = hclge_get_mac_vlan_cmd_status(vport, retval,
							   resp_code,
							   HCLGE_MAC_VLAN_ADD);
	पूर्ण

	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"add mac addr failed for cmd_send, ret =%d.\n",
			ret);
		वापस ret;
	पूर्ण

	वापस cfg_status;
पूर्ण

अटल पूर्णांक hclge_set_umv_space(काष्ठा hclge_dev *hdev, u16 space_size,
			       u16 *allocated_size)
अणु
	काष्ठा hclge_umv_spc_alc_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	req = (काष्ठा hclge_umv_spc_alc_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_VLAN_ALLOCATE, false);

	req->space_size = cpu_to_le32(space_size);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "failed to set umv space, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	*allocated_size = le32_to_cpu(desc.data[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_init_umv_space(काष्ठा hclge_dev *hdev)
अणु
	u16 allocated_size = 0;
	पूर्णांक ret;

	ret = hclge_set_umv_space(hdev, hdev->wanted_umv_size, &allocated_size);
	अगर (ret)
		वापस ret;

	अगर (allocated_size < hdev->wanted_umv_size)
		dev_warn(&hdev->pdev->dev,
			 "failed to alloc umv space, want %u, get %u\n",
			 hdev->wanted_umv_size, allocated_size);

	hdev->max_umv_size = allocated_size;
	hdev->priv_umv_size = hdev->max_umv_size / (hdev->num_alloc_vport + 1);
	hdev->share_umv_size = hdev->priv_umv_size +
			hdev->max_umv_size % (hdev->num_alloc_vport + 1);

	वापस 0;
पूर्ण

अटल व्योम hclge_reset_umv_space(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport;
	पूर्णांक i;

	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		vport = &hdev->vport[i];
		vport->used_umv_num = 0;
	पूर्ण

	mutex_lock(&hdev->vport_lock);
	hdev->share_umv_size = hdev->priv_umv_size +
			hdev->max_umv_size % (hdev->num_alloc_vport + 1);
	mutex_unlock(&hdev->vport_lock);
पूर्ण

अटल bool hclge_is_umv_space_full(काष्ठा hclge_vport *vport, bool need_lock)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	bool is_full;

	अगर (need_lock)
		mutex_lock(&hdev->vport_lock);

	is_full = (vport->used_umv_num >= hdev->priv_umv_size &&
		   hdev->share_umv_size == 0);

	अगर (need_lock)
		mutex_unlock(&hdev->vport_lock);

	वापस is_full;
पूर्ण

अटल व्योम hclge_update_umv_space(काष्ठा hclge_vport *vport, bool is_मुक्त)
अणु
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (is_मुक्त) अणु
		अगर (vport->used_umv_num > hdev->priv_umv_size)
			hdev->share_umv_size++;

		अगर (vport->used_umv_num > 0)
			vport->used_umv_num--;
	पूर्ण अन्यथा अणु
		अगर (vport->used_umv_num >= hdev->priv_umv_size &&
		    hdev->share_umv_size > 0)
			hdev->share_umv_size--;
		vport->used_umv_num++;
	पूर्ण
पूर्ण

अटल काष्ठा hclge_mac_node *hclge_find_mac_node(काष्ठा list_head *list,
						  स्थिर u8 *mac_addr)
अणु
	काष्ठा hclge_mac_node *mac_node, *पंचांगp;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node)
		अगर (ether_addr_equal(mac_addr, mac_node->mac_addr))
			वापस mac_node;

	वापस शून्य;
पूर्ण

अटल व्योम hclge_update_mac_node(काष्ठा hclge_mac_node *mac_node,
				  क्रमागत HCLGE_MAC_NODE_STATE state)
अणु
	चयन (state) अणु
	/* from set_rx_mode or पंचांगp_add_list */
	हाल HCLGE_MAC_TO_ADD:
		अगर (mac_node->state == HCLGE_MAC_TO_DEL)
			mac_node->state = HCLGE_MAC_ACTIVE;
		अवरोध;
	/* only from set_rx_mode */
	हाल HCLGE_MAC_TO_DEL:
		अगर (mac_node->state == HCLGE_MAC_TO_ADD) अणु
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण अन्यथा अणु
			mac_node->state = HCLGE_MAC_TO_DEL;
		पूर्ण
		अवरोध;
	/* only from पंचांगp_add_list, the mac_node->state won't be
	 * ACTIVE.
	 */
	हाल HCLGE_MAC_ACTIVE:
		अगर (mac_node->state == HCLGE_MAC_TO_ADD)
			mac_node->state = HCLGE_MAC_ACTIVE;

		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक hclge_update_mac_list(काष्ठा hclge_vport *vport,
			  क्रमागत HCLGE_MAC_NODE_STATE state,
			  क्रमागत HCLGE_MAC_ADDR_TYPE mac_type,
			  स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_mac_node *mac_node;
	काष्ठा list_head *list;

	list = (mac_type == HCLGE_MAC_ADDR_UC) ?
		&vport->uc_mac_list : &vport->mc_mac_list;

	spin_lock_bh(&vport->mac_list_lock);

	/* अगर the mac addr is alपढ़ोy in the mac list, no need to add a new
	 * one पूर्णांकo it, just check the mac addr state, convert it to a new
	 * state, or just हटाओ it, or करो nothing.
	 */
	mac_node = hclge_find_mac_node(list, addr);
	अगर (mac_node) अणु
		hclge_update_mac_node(mac_node, state);
		spin_unlock_bh(&vport->mac_list_lock);
		set_bit(HCLGE_VPORT_STATE_MAC_TBL_CHANGE, &vport->state);
		वापस 0;
	पूर्ण

	/* अगर this address is never added, unnecessary to delete */
	अगर (state == HCLGE_MAC_TO_DEL) अणु
		spin_unlock_bh(&vport->mac_list_lock);
		dev_err(&hdev->pdev->dev,
			"failed to delete address %pM from mac list\n",
			addr);
		वापस -ENOENT;
	पूर्ण

	mac_node = kzalloc(माप(*mac_node), GFP_ATOMIC);
	अगर (!mac_node) अणु
		spin_unlock_bh(&vport->mac_list_lock);
		वापस -ENOMEM;
	पूर्ण

	set_bit(HCLGE_VPORT_STATE_MAC_TBL_CHANGE, &vport->state);

	mac_node->state = state;
	ether_addr_copy(mac_node->mac_addr, addr);
	list_add_tail(&mac_node->node, list);

	spin_unlock_bh(&vport->mac_list_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_add_uc_addr(काष्ठा hnae3_handle *handle,
			     स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);

	वापस hclge_update_mac_list(vport, HCLGE_MAC_TO_ADD, HCLGE_MAC_ADDR_UC,
				     addr);
पूर्ण

पूर्णांक hclge_add_uc_addr_common(काष्ठा hclge_vport *vport,
			     स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_mac_vlan_tbl_entry_cmd req;
	काष्ठा hclge_desc desc;
	u16 egress_port = 0;
	पूर्णांक ret;

	/* mac addr check */
	अगर (is_zero_ether_addr(addr) ||
	    is_broadcast_ether_addr(addr) ||
	    is_multicast_ether_addr(addr)) अणु
		dev_err(&hdev->pdev->dev,
			"Set_uc mac err! invalid mac:%pM. is_zero:%d,is_br=%d,is_mul=%d\n",
			 addr, is_zero_ether_addr(addr),
			 is_broadcast_ether_addr(addr),
			 is_multicast_ether_addr(addr));
		वापस -EINVAL;
	पूर्ण

	स_रखो(&req, 0, माप(req));

	hnae3_set_field(egress_port, HCLGE_MAC_EPORT_VFID_M,
			HCLGE_MAC_EPORT_VFID_S, vport->vport_id);

	req.egress_port = cpu_to_le16(egress_port);

	hclge_prepare_mac_addr(&req, addr, false);

	/* Lookup the mac address in the mac_vlan table, and add
	 * it अगर the entry is inexistent. Repeated unicast entry
	 * is not allowed in the mac vlan table.
	 */
	ret = hclge_lookup_mac_vlan_tbl(vport, &req, &desc, false);
	अगर (ret == -ENOENT) अणु
		mutex_lock(&hdev->vport_lock);
		अगर (!hclge_is_umv_space_full(vport, false)) अणु
			ret = hclge_add_mac_vlan_tbl(vport, &req, शून्य);
			अगर (!ret)
				hclge_update_umv_space(vport, false);
			mutex_unlock(&hdev->vport_lock);
			वापस ret;
		पूर्ण
		mutex_unlock(&hdev->vport_lock);

		अगर (!(vport->overflow_promisc_flags & HNAE3_OVERFLOW_UPE))
			dev_err(&hdev->pdev->dev, "UC MAC table full(%u)\n",
				hdev->priv_umv_size);

		वापस -ENOSPC;
	पूर्ण

	/* check अगर we just hit the duplicate */
	अगर (!ret) अणु
		dev_warn(&hdev->pdev->dev, "VF %u mac(%pM) exists\n",
			 vport->vport_id, addr);
		वापस 0;
	पूर्ण

	dev_err(&hdev->pdev->dev,
		"PF failed to add unicast entry(%pM) in the MAC table\n",
		addr);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_rm_uc_addr(काष्ठा hnae3_handle *handle,
			    स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);

	वापस hclge_update_mac_list(vport, HCLGE_MAC_TO_DEL, HCLGE_MAC_ADDR_UC,
				     addr);
पूर्ण

पूर्णांक hclge_rm_uc_addr_common(काष्ठा hclge_vport *vport,
			    स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_mac_vlan_tbl_entry_cmd req;
	पूर्णांक ret;

	/* mac addr check */
	अगर (is_zero_ether_addr(addr) ||
	    is_broadcast_ether_addr(addr) ||
	    is_multicast_ether_addr(addr)) अणु
		dev_dbg(&hdev->pdev->dev, "Remove mac err! invalid mac:%pM.\n",
			addr);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&req, 0, माप(req));
	hnae3_set_bit(req.entry_type, HCLGE_MAC_VLAN_BIT0_EN_B, 0);
	hclge_prepare_mac_addr(&req, addr, false);
	ret = hclge_हटाओ_mac_vlan_tbl(vport, &req);
	अगर (!ret) अणु
		mutex_lock(&hdev->vport_lock);
		hclge_update_umv_space(vport, true);
		mutex_unlock(&hdev->vport_lock);
	पूर्ण अन्यथा अगर (ret == -ENOENT) अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_add_mc_addr(काष्ठा hnae3_handle *handle,
			     स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);

	वापस hclge_update_mac_list(vport, HCLGE_MAC_TO_ADD, HCLGE_MAC_ADDR_MC,
				     addr);
पूर्ण

पूर्णांक hclge_add_mc_addr_common(काष्ठा hclge_vport *vport,
			     स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_mac_vlan_tbl_entry_cmd req;
	काष्ठा hclge_desc desc[3];
	पूर्णांक status;

	/* mac addr check */
	अगर (!is_multicast_ether_addr(addr)) अणु
		dev_err(&hdev->pdev->dev,
			"Add mc mac err! invalid mac:%pM.\n",
			 addr);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&req, 0, माप(req));
	hclge_prepare_mac_addr(&req, addr, true);
	status = hclge_lookup_mac_vlan_tbl(vport, &req, desc, true);
	अगर (status) अणु
		/* This mac addr करो not exist, add new entry क्रम it */
		स_रखो(desc[0].data, 0, माप(desc[0].data));
		स_रखो(desc[1].data, 0, माप(desc[0].data));
		स_रखो(desc[2].data, 0, माप(desc[0].data));
	पूर्ण
	status = hclge_update_desc_vfid(desc, vport->vport_id, false);
	अगर (status)
		वापस status;
	status = hclge_add_mac_vlan_tbl(vport, &req, desc);
	/* अगर alपढ़ोy overflow, not to prपूर्णांक each समय */
	अगर (status == -ENOSPC &&
	    !(vport->overflow_promisc_flags & HNAE3_OVERFLOW_MPE))
		dev_err(&hdev->pdev->dev, "mc mac vlan table is full\n");

	वापस status;
पूर्ण

अटल पूर्णांक hclge_rm_mc_addr(काष्ठा hnae3_handle *handle,
			    स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);

	वापस hclge_update_mac_list(vport, HCLGE_MAC_TO_DEL, HCLGE_MAC_ADDR_MC,
				     addr);
पूर्ण

पूर्णांक hclge_rm_mc_addr_common(काष्ठा hclge_vport *vport,
			    स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_mac_vlan_tbl_entry_cmd req;
	क्रमागत hclge_cmd_status status;
	काष्ठा hclge_desc desc[3];

	/* mac addr check */
	अगर (!is_multicast_ether_addr(addr)) अणु
		dev_dbg(&hdev->pdev->dev,
			"Remove mc mac err! invalid mac:%pM.\n",
			 addr);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&req, 0, माप(req));
	hclge_prepare_mac_addr(&req, addr, true);
	status = hclge_lookup_mac_vlan_tbl(vport, &req, desc, true);
	अगर (!status) अणु
		/* This mac addr exist, हटाओ this handle's VFID क्रम it */
		status = hclge_update_desc_vfid(desc, vport->vport_id, true);
		अगर (status)
			वापस status;

		अगर (hclge_is_all_function_id_zero(desc))
			/* All the vfid is zero, so need to delete this entry */
			status = hclge_हटाओ_mac_vlan_tbl(vport, &req);
		अन्यथा
			/* Not all the vfid is zero, update the vfid */
			status = hclge_add_mac_vlan_tbl(vport, &req, desc);
	पूर्ण अन्यथा अगर (status == -ENOENT) अणु
		status = 0;
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम hclge_sync_vport_mac_list(काष्ठा hclge_vport *vport,
				      काष्ठा list_head *list,
				      पूर्णांक (*sync)(काष्ठा hclge_vport *,
						  स्थिर अचिन्हित अक्षर *))
अणु
	काष्ठा hclge_mac_node *mac_node, *पंचांगp;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node) अणु
		ret = sync(vport, mac_node->mac_addr);
		अगर (!ret) अणु
			mac_node->state = HCLGE_MAC_ACTIVE;
		पूर्ण अन्यथा अणु
			set_bit(HCLGE_VPORT_STATE_MAC_TBL_CHANGE,
				&vport->state);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hclge_unsync_vport_mac_list(काष्ठा hclge_vport *vport,
					काष्ठा list_head *list,
					पूर्णांक (*unsync)(काष्ठा hclge_vport *,
						      स्थिर अचिन्हित अक्षर *))
अणु
	काष्ठा hclge_mac_node *mac_node, *पंचांगp;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node) अणु
		ret = unsync(vport, mac_node->mac_addr);
		अगर (!ret || ret == -ENOENT) अणु
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण अन्यथा अणु
			set_bit(HCLGE_VPORT_STATE_MAC_TBL_CHANGE,
				&vport->state);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool hclge_sync_from_add_list(काष्ठा list_head *add_list,
				     काष्ठा list_head *mac_list)
अणु
	काष्ठा hclge_mac_node *mac_node, *पंचांगp, *new_node;
	bool all_added = true;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, add_list, node) अणु
		अगर (mac_node->state == HCLGE_MAC_TO_ADD)
			all_added = false;

		/* अगर the mac address from पंचांगp_add_list is not in the
		 * uc/mc_mac_list, it means have received a TO_DEL request
		 * during the समय winकरोw of adding the mac address पूर्णांकo mac
		 * table. अगर mac_node state is ACTIVE, then change it to TO_DEL,
		 * then it will be हटाओd at next समय. अन्यथा it must be TO_ADD,
		 * this address hasn't been added पूर्णांकo mac table,
		 * so just हटाओ the mac node.
		 */
		new_node = hclge_find_mac_node(mac_list, mac_node->mac_addr);
		अगर (new_node) अणु
			hclge_update_mac_node(new_node, mac_node->state);
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण अन्यथा अगर (mac_node->state == HCLGE_MAC_ACTIVE) अणु
			mac_node->state = HCLGE_MAC_TO_DEL;
			list_del(&mac_node->node);
			list_add_tail(&mac_node->node, mac_list);
		पूर्ण अन्यथा अणु
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण
	पूर्ण

	वापस all_added;
पूर्ण

अटल व्योम hclge_sync_from_del_list(काष्ठा list_head *del_list,
				     काष्ठा list_head *mac_list)
अणु
	काष्ठा hclge_mac_node *mac_node, *पंचांगp, *new_node;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, del_list, node) अणु
		new_node = hclge_find_mac_node(mac_list, mac_node->mac_addr);
		अगर (new_node) अणु
			/* If the mac addr exists in the mac list, it means
			 * received a new TO_ADD request during the समय winकरोw
			 * of configuring the mac address. For the mac node
			 * state is TO_ADD, and the address is alपढ़ोy in the
			 * in the hardware(due to delete fail), so we just need
			 * to change the mac node state to ACTIVE.
			 */
			new_node->state = HCLGE_MAC_ACTIVE;
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण अन्यथा अणु
			list_del(&mac_node->node);
			list_add_tail(&mac_node->node, mac_list);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hclge_update_overflow_flags(काष्ठा hclge_vport *vport,
					क्रमागत HCLGE_MAC_ADDR_TYPE mac_type,
					bool is_all_added)
अणु
	अगर (mac_type == HCLGE_MAC_ADDR_UC) अणु
		अगर (is_all_added)
			vport->overflow_promisc_flags &= ~HNAE3_OVERFLOW_UPE;
		अन्यथा
			vport->overflow_promisc_flags |= HNAE3_OVERFLOW_UPE;
	पूर्ण अन्यथा अणु
		अगर (is_all_added)
			vport->overflow_promisc_flags &= ~HNAE3_OVERFLOW_MPE;
		अन्यथा
			vport->overflow_promisc_flags |= HNAE3_OVERFLOW_MPE;
	पूर्ण
पूर्ण

अटल व्योम hclge_sync_vport_mac_table(काष्ठा hclge_vport *vport,
				       क्रमागत HCLGE_MAC_ADDR_TYPE mac_type)
अणु
	काष्ठा hclge_mac_node *mac_node, *पंचांगp, *new_node;
	काष्ठा list_head पंचांगp_add_list, पंचांगp_del_list;
	काष्ठा list_head *list;
	bool all_added;

	INIT_LIST_HEAD(&पंचांगp_add_list);
	INIT_LIST_HEAD(&पंचांगp_del_list);

	/* move the mac addr to the पंचांगp_add_list and पंचांगp_del_list, then
	 * we can add/delete these mac addr outside the spin lock
	 */
	list = (mac_type == HCLGE_MAC_ADDR_UC) ?
		&vport->uc_mac_list : &vport->mc_mac_list;

	spin_lock_bh(&vport->mac_list_lock);

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node) अणु
		चयन (mac_node->state) अणु
		हाल HCLGE_MAC_TO_DEL:
			list_del(&mac_node->node);
			list_add_tail(&mac_node->node, &पंचांगp_del_list);
			अवरोध;
		हाल HCLGE_MAC_TO_ADD:
			new_node = kzalloc(माप(*new_node), GFP_ATOMIC);
			अगर (!new_node)
				जाओ stop_traverse;
			ether_addr_copy(new_node->mac_addr, mac_node->mac_addr);
			new_node->state = mac_node->state;
			list_add_tail(&new_node->node, &पंचांगp_add_list);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

stop_traverse:
	spin_unlock_bh(&vport->mac_list_lock);

	/* delete first, in order to get max mac table space क्रम adding */
	अगर (mac_type == HCLGE_MAC_ADDR_UC) अणु
		hclge_unsync_vport_mac_list(vport, &पंचांगp_del_list,
					    hclge_rm_uc_addr_common);
		hclge_sync_vport_mac_list(vport, &पंचांगp_add_list,
					  hclge_add_uc_addr_common);
	पूर्ण अन्यथा अणु
		hclge_unsync_vport_mac_list(vport, &पंचांगp_del_list,
					    hclge_rm_mc_addr_common);
		hclge_sync_vport_mac_list(vport, &पंचांगp_add_list,
					  hclge_add_mc_addr_common);
	पूर्ण

	/* अगर some mac addresses were added/deleted fail, move back to the
	 * mac_list, and retry at next समय.
	 */
	spin_lock_bh(&vport->mac_list_lock);

	hclge_sync_from_del_list(&पंचांगp_del_list, list);
	all_added = hclge_sync_from_add_list(&पंचांगp_add_list, list);

	spin_unlock_bh(&vport->mac_list_lock);

	hclge_update_overflow_flags(vport, mac_type, all_added);
पूर्ण

अटल bool hclge_need_sync_mac_table(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (test_bit(vport->vport_id, hdev->vport_config_block))
		वापस false;

	अगर (test_and_clear_bit(HCLGE_VPORT_STATE_MAC_TBL_CHANGE, &vport->state))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम hclge_sync_mac_table(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		काष्ठा hclge_vport *vport = &hdev->vport[i];

		अगर (!hclge_need_sync_mac_table(vport))
			जारी;

		hclge_sync_vport_mac_table(vport, HCLGE_MAC_ADDR_UC);
		hclge_sync_vport_mac_table(vport, HCLGE_MAC_ADDR_MC);
	पूर्ण
पूर्ण

अटल व्योम hclge_build_del_list(काष्ठा list_head *list,
				 bool is_del_list,
				 काष्ठा list_head *पंचांगp_del_list)
अणु
	काष्ठा hclge_mac_node *mac_cfg, *पंचांगp;

	list_क्रम_each_entry_safe(mac_cfg, पंचांगp, list, node) अणु
		चयन (mac_cfg->state) अणु
		हाल HCLGE_MAC_TO_DEL:
		हाल HCLGE_MAC_ACTIVE:
			list_del(&mac_cfg->node);
			list_add_tail(&mac_cfg->node, पंचांगp_del_list);
			अवरोध;
		हाल HCLGE_MAC_TO_ADD:
			अगर (is_del_list) अणु
				list_del(&mac_cfg->node);
				kमुक्त(mac_cfg);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hclge_unsync_del_list(काष्ठा hclge_vport *vport,
				  पूर्णांक (*unsync)(काष्ठा hclge_vport *vport,
						स्थिर अचिन्हित अक्षर *addr),
				  bool is_del_list,
				  काष्ठा list_head *पंचांगp_del_list)
अणु
	काष्ठा hclge_mac_node *mac_cfg, *पंचांगp;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(mac_cfg, पंचांगp, पंचांगp_del_list, node) अणु
		ret = unsync(vport, mac_cfg->mac_addr);
		अगर (!ret || ret == -ENOENT) अणु
			/* clear all mac addr from hardware, but reमुख्य these
			 * mac addr in the mac list, and restore them after
			 * vf reset finished.
			 */
			अगर (!is_del_list &&
			    mac_cfg->state == HCLGE_MAC_ACTIVE) अणु
				mac_cfg->state = HCLGE_MAC_TO_ADD;
			पूर्ण अन्यथा अणु
				list_del(&mac_cfg->node);
				kमुक्त(mac_cfg);
			पूर्ण
		पूर्ण अन्यथा अगर (is_del_list) अणु
			mac_cfg->state = HCLGE_MAC_TO_DEL;
		पूर्ण
	पूर्ण
पूर्ण

व्योम hclge_rm_vport_all_mac_table(काष्ठा hclge_vport *vport, bool is_del_list,
				  क्रमागत HCLGE_MAC_ADDR_TYPE mac_type)
अणु
	पूर्णांक (*unsync)(काष्ठा hclge_vport *vport, स्थिर अचिन्हित अक्षर *addr);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा list_head पंचांगp_del_list, *list;

	अगर (mac_type == HCLGE_MAC_ADDR_UC) अणु
		list = &vport->uc_mac_list;
		unsync = hclge_rm_uc_addr_common;
	पूर्ण अन्यथा अणु
		list = &vport->mc_mac_list;
		unsync = hclge_rm_mc_addr_common;
	पूर्ण

	INIT_LIST_HEAD(&पंचांगp_del_list);

	अगर (!is_del_list)
		set_bit(vport->vport_id, hdev->vport_config_block);

	spin_lock_bh(&vport->mac_list_lock);

	hclge_build_del_list(list, is_del_list, &पंचांगp_del_list);

	spin_unlock_bh(&vport->mac_list_lock);

	hclge_unsync_del_list(vport, unsync, is_del_list, &पंचांगp_del_list);

	spin_lock_bh(&vport->mac_list_lock);

	hclge_sync_from_del_list(&पंचांगp_del_list, list);

	spin_unlock_bh(&vport->mac_list_lock);
पूर्ण

/* हटाओ all mac address when uninitailize */
अटल व्योम hclge_uninit_vport_mac_list(काष्ठा hclge_vport *vport,
					क्रमागत HCLGE_MAC_ADDR_TYPE mac_type)
अणु
	काष्ठा hclge_mac_node *mac_node, *पंचांगp;
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा list_head पंचांगp_del_list, *list;

	INIT_LIST_HEAD(&पंचांगp_del_list);

	list = (mac_type == HCLGE_MAC_ADDR_UC) ?
		&vport->uc_mac_list : &vport->mc_mac_list;

	spin_lock_bh(&vport->mac_list_lock);

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node) अणु
		चयन (mac_node->state) अणु
		हाल HCLGE_MAC_TO_DEL:
		हाल HCLGE_MAC_ACTIVE:
			list_del(&mac_node->node);
			list_add_tail(&mac_node->node, &पंचांगp_del_list);
			अवरोध;
		हाल HCLGE_MAC_TO_ADD:
			list_del(&mac_node->node);
			kमुक्त(mac_node);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&vport->mac_list_lock);

	अगर (mac_type == HCLGE_MAC_ADDR_UC)
		hclge_unsync_vport_mac_list(vport, &पंचांगp_del_list,
					    hclge_rm_uc_addr_common);
	अन्यथा
		hclge_unsync_vport_mac_list(vport, &पंचांगp_del_list,
					    hclge_rm_mc_addr_common);

	अगर (!list_empty(&पंचांगp_del_list))
		dev_warn(&hdev->pdev->dev,
			 "uninit %s mac list for vport %u not completely.\n",
			 mac_type == HCLGE_MAC_ADDR_UC ? "uc" : "mc",
			 vport->vport_id);

	list_क्रम_each_entry_safe(mac_node, पंचांगp, &पंचांगp_del_list, node) अणु
		list_del(&mac_node->node);
		kमुक्त(mac_node);
	पूर्ण
पूर्ण

अटल व्योम hclge_uninit_mac_table(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport;
	पूर्णांक i;

	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		vport = &hdev->vport[i];
		hclge_uninit_vport_mac_list(vport, HCLGE_MAC_ADDR_UC);
		hclge_uninit_vport_mac_list(vport, HCLGE_MAC_ADDR_MC);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_get_mac_ethertype_cmd_status(काष्ठा hclge_dev *hdev,
					      u16 cmdq_resp, u8 resp_code)
अणु
#घोषणा HCLGE_ETHERTYPE_SUCCESS_ADD		0
#घोषणा HCLGE_ETHERTYPE_ALREADY_ADD		1
#घोषणा HCLGE_ETHERTYPE_MGR_TBL_OVERFLOW	2
#घोषणा HCLGE_ETHERTYPE_KEY_CONFLICT		3

	पूर्णांक वापस_status;

	अगर (cmdq_resp) अणु
		dev_err(&hdev->pdev->dev,
			"cmdq execute failed for get_mac_ethertype_cmd_status, status=%u.\n",
			cmdq_resp);
		वापस -EIO;
	पूर्ण

	चयन (resp_code) अणु
	हाल HCLGE_ETHERTYPE_SUCCESS_ADD:
	हाल HCLGE_ETHERTYPE_ALREADY_ADD:
		वापस_status = 0;
		अवरोध;
	हाल HCLGE_ETHERTYPE_MGR_TBL_OVERFLOW:
		dev_err(&hdev->pdev->dev,
			"add mac ethertype failed for manager table overflow.\n");
		वापस_status = -EIO;
		अवरोध;
	हाल HCLGE_ETHERTYPE_KEY_CONFLICT:
		dev_err(&hdev->pdev->dev,
			"add mac ethertype failed for key conflict.\n");
		वापस_status = -EIO;
		अवरोध;
	शेष:
		dev_err(&hdev->pdev->dev,
			"add mac ethertype failed for undefined, code=%u.\n",
			resp_code);
		वापस_status = -EIO;
	पूर्ण

	वापस वापस_status;
पूर्ण

अटल bool hclge_check_vf_mac_exist(काष्ठा hclge_vport *vport, पूर्णांक vf_idx,
				     u8 *mac_addr)
अणु
	काष्ठा hclge_mac_vlan_tbl_entry_cmd req;
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_desc desc;
	u16 egress_port = 0;
	पूर्णांक i;

	अगर (is_zero_ether_addr(mac_addr))
		वापस false;

	स_रखो(&req, 0, माप(req));
	hnae3_set_field(egress_port, HCLGE_MAC_EPORT_VFID_M,
			HCLGE_MAC_EPORT_VFID_S, vport->vport_id);
	req.egress_port = cpu_to_le16(egress_port);
	hclge_prepare_mac_addr(&req, mac_addr, false);

	अगर (hclge_lookup_mac_vlan_tbl(vport, &req, &desc, false) != -ENOENT)
		वापस true;

	vf_idx += HCLGE_VF_VPORT_START_NUM;
	क्रम (i = HCLGE_VF_VPORT_START_NUM; i < hdev->num_alloc_vport; i++)
		अगर (i != vf_idx &&
		    ether_addr_equal(mac_addr, hdev->vport[i].vf_info.mac))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक hclge_set_vf_mac(काष्ठा hnae3_handle *handle, पूर्णांक vf,
			    u8 *mac_addr)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	vport = hclge_get_vf_vport(hdev, vf);
	अगर (!vport)
		वापस -EINVAL;

	अगर (ether_addr_equal(mac_addr, vport->vf_info.mac)) अणु
		dev_info(&hdev->pdev->dev,
			 "Specified MAC(=%pM) is same as before, no change committed!\n",
			 mac_addr);
		वापस 0;
	पूर्ण

	अगर (hclge_check_vf_mac_exist(vport, vf, mac_addr)) अणु
		dev_err(&hdev->pdev->dev, "Specified MAC(=%pM) exists!\n",
			mac_addr);
		वापस -EEXIST;
	पूर्ण

	ether_addr_copy(vport->vf_info.mac, mac_addr);

	अगर (test_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state)) अणु
		dev_info(&hdev->pdev->dev,
			 "MAC of VF %d has been set to %pM, and it will be reinitialized!\n",
			 vf, mac_addr);
		वापस hclge_inक्रमm_reset_निश्चित_to_vf(vport);
	पूर्ण

	dev_info(&hdev->pdev->dev, "MAC of VF %d has been set to %pM\n",
		 vf, mac_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_add_mgr_tbl(काष्ठा hclge_dev *hdev,
			     स्थिर काष्ठा hclge_mac_mgr_tbl_entry_cmd *req)
अणु
	काष्ठा hclge_desc desc;
	u8 resp_code;
	u16 retval;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_ETHTYPE_ADD, false);
	स_नकल(desc.data, req, माप(काष्ठा hclge_mac_mgr_tbl_entry_cmd));

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"add mac ethertype failed for cmd_send, ret =%d.\n",
			ret);
		वापस ret;
	पूर्ण

	resp_code = (le32_to_cpu(desc.data[0]) >> 8) & 0xff;
	retval = le16_to_cpu(desc.retval);

	वापस hclge_get_mac_ethertype_cmd_status(hdev, retval, resp_code);
पूर्ण

अटल पूर्णांक init_mgr_tbl(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hclge_mgr_table); i++) अणु
		ret = hclge_add_mgr_tbl(hdev, &hclge_mgr_table[i]);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"add mac ethertype failed, ret =%d.\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclge_get_mac_addr(काष्ठा hnae3_handle *handle, u8 *p)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	ether_addr_copy(p, hdev->hw.mac.mac_addr);
पूर्ण

पूर्णांक hclge_update_mac_node_क्रम_dev_addr(काष्ठा hclge_vport *vport,
				       स्थिर u8 *old_addr, स्थिर u8 *new_addr)
अणु
	काष्ठा list_head *list = &vport->uc_mac_list;
	काष्ठा hclge_mac_node *old_node, *new_node;

	new_node = hclge_find_mac_node(list, new_addr);
	अगर (!new_node) अणु
		new_node = kzalloc(माप(*new_node), GFP_ATOMIC);
		अगर (!new_node)
			वापस -ENOMEM;

		new_node->state = HCLGE_MAC_TO_ADD;
		ether_addr_copy(new_node->mac_addr, new_addr);
		list_add(&new_node->node, list);
	पूर्ण अन्यथा अणु
		अगर (new_node->state == HCLGE_MAC_TO_DEL)
			new_node->state = HCLGE_MAC_ACTIVE;

		/* make sure the new addr is in the list head, aव्योम dev
		 * addr may be not re-added पूर्णांकo mac table क्रम the umv space
		 * limitation after global/imp reset which will clear mac
		 * table by hardware.
		 */
		list_move(&new_node->node, list);
	पूर्ण

	अगर (old_addr && !ether_addr_equal(old_addr, new_addr)) अणु
		old_node = hclge_find_mac_node(list, old_addr);
		अगर (old_node) अणु
			अगर (old_node->state == HCLGE_MAC_TO_ADD) अणु
				list_del(&old_node->node);
				kमुक्त(old_node);
			पूर्ण अन्यथा अणु
				old_node->state = HCLGE_MAC_TO_DEL;
			पूर्ण
		पूर्ण
	पूर्ण

	set_bit(HCLGE_VPORT_STATE_MAC_TBL_CHANGE, &vport->state);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_mac_addr(काष्ठा hnae3_handle *handle, व्योम *p,
			      bool is_first)
अणु
	स्थिर अचिन्हित अक्षर *new_addr = (स्थिर अचिन्हित अक्षर *)p;
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	अचिन्हित अक्षर *old_addr = शून्य;
	पूर्णांक ret;

	/* mac addr check */
	अगर (is_zero_ether_addr(new_addr) ||
	    is_broadcast_ether_addr(new_addr) ||
	    is_multicast_ether_addr(new_addr)) अणु
		dev_err(&hdev->pdev->dev,
			"change uc mac err! invalid mac: %pM.\n",
			 new_addr);
		वापस -EINVAL;
	पूर्ण

	ret = hclge_छोड़ो_addr_cfg(hdev, new_addr);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to configure mac pause address, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (!is_first)
		old_addr = hdev->hw.mac.mac_addr;

	spin_lock_bh(&vport->mac_list_lock);
	ret = hclge_update_mac_node_क्रम_dev_addr(vport, old_addr, new_addr);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to change the mac addr:%pM, ret = %d\n",
			new_addr, ret);
		spin_unlock_bh(&vport->mac_list_lock);

		अगर (!is_first)
			hclge_छोड़ो_addr_cfg(hdev, old_addr);

		वापस ret;
	पूर्ण
	/* we must update dev addr with spin lock protect, preventing dev addr
	 * being हटाओd by set_rx_mode path.
	 */
	ether_addr_copy(hdev->hw.mac.mac_addr, new_addr);
	spin_unlock_bh(&vport->mac_list_lock);

	hclge_task_schedule(hdev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_mii_ioctl(काष्ठा hclge_dev *hdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);

	अगर (!hnae3_dev_phy_imp_supported(hdev))
		वापस -EOPNOTSUPP;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = hdev->hw.mac.phy_addr;
		/* this command पढ़ोs phy id and रेजिस्टर at the same समय */
		fallthrough;
	हाल SIOCGMIIREG:
		data->val_out = hclge_पढ़ो_phy_reg(hdev, data->reg_num);
		वापस 0;

	हाल SIOCSMIIREG:
		वापस hclge_ग_लिखो_phy_reg(hdev, data->reg_num, data->val_in);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_करो_ioctl(काष्ठा hnae3_handle *handle, काष्ठा अगरreq *अगरr,
			  पूर्णांक cmd)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (!hdev->hw.mac.phydev)
		वापस hclge_mii_ioctl(hdev, अगरr, cmd);

	वापस phy_mii_ioctl(hdev->hw.mac.phydev, अगरr, cmd);
पूर्ण

अटल पूर्णांक hclge_set_vlan_filter_ctrl(काष्ठा hclge_dev *hdev, u8 vlan_type,
				      u8 fe_type, bool filter_en, u8 vf_id)
अणु
	काष्ठा hclge_vlan_filter_ctrl_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	/* पढ़ो current vlan filter parameter */
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_VLAN_FILTER_CTRL, true);
	req = (काष्ठा hclge_vlan_filter_ctrl_cmd *)desc.data;
	req->vlan_type = vlan_type;
	req->vf_id = vf_id;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get vlan filter config, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	/* modअगरy and ग_लिखो new config parameter */
	hclge_cmd_reuse_desc(&desc, false);
	req->vlan_fe = filter_en ?
			(req->vlan_fe | fe_type) : (req->vlan_fe & ~fe_type);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "failed to set vlan filter, ret = %d.\n",
			ret);

	वापस ret;
पूर्ण

#घोषणा HCLGE_FILTER_TYPE_VF		0
#घोषणा HCLGE_FILTER_TYPE_PORT		1
#घोषणा HCLGE_FILTER_FE_EGRESS_V1_B	BIT(0)
#घोषणा HCLGE_FILTER_FE_NIC_INGRESS_B	BIT(0)
#घोषणा HCLGE_FILTER_FE_NIC_EGRESS_B	BIT(1)
#घोषणा HCLGE_FILTER_FE_ROCE_INGRESS_B	BIT(2)
#घोषणा HCLGE_FILTER_FE_ROCE_EGRESS_B	BIT(3)
#घोषणा HCLGE_FILTER_FE_EGRESS		(HCLGE_FILTER_FE_NIC_EGRESS_B \
					| HCLGE_FILTER_FE_ROCE_EGRESS_B)
#घोषणा HCLGE_FILTER_FE_INGRESS		(HCLGE_FILTER_FE_NIC_INGRESS_B \
					| HCLGE_FILTER_FE_ROCE_INGRESS_B)

अटल व्योम hclge_enable_vlan_filter(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2) अणु
		hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_VF,
					   HCLGE_FILTER_FE_EGRESS, enable, 0);
		hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_PORT,
					   HCLGE_FILTER_FE_INGRESS, enable, 0);
	पूर्ण अन्यथा अणु
		hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_VF,
					   HCLGE_FILTER_FE_EGRESS_V1_B, enable,
					   0);
	पूर्ण
	अगर (enable)
		handle->netdev_flags |= HNAE3_VLAN_FLTR;
	अन्यथा
		handle->netdev_flags &= ~HNAE3_VLAN_FLTR;
पूर्ण

अटल पूर्णांक hclge_set_vf_vlan_filter_cmd(काष्ठा hclge_dev *hdev, u16 vfid,
					bool is_समाप्त, u16 vlan,
					काष्ठा hclge_desc *desc)
अणु
	काष्ठा hclge_vlan_filter_vf_cfg_cmd *req0;
	काष्ठा hclge_vlan_filter_vf_cfg_cmd *req1;
	u8 vf_byte_val;
	u8 vf_byte_off;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc[0],
				   HCLGE_OPC_VLAN_FILTER_VF_CFG, false);
	hclge_cmd_setup_basic_desc(&desc[1],
				   HCLGE_OPC_VLAN_FILTER_VF_CFG, false);

	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);

	vf_byte_off = vfid / 8;
	vf_byte_val = 1 << (vfid % 8);

	req0 = (काष्ठा hclge_vlan_filter_vf_cfg_cmd *)desc[0].data;
	req1 = (काष्ठा hclge_vlan_filter_vf_cfg_cmd *)desc[1].data;

	req0->vlan_id  = cpu_to_le16(vlan);
	req0->vlan_cfg = is_समाप्त;

	अगर (vf_byte_off < HCLGE_MAX_VF_BYTES)
		req0->vf_biपंचांगap[vf_byte_off] = vf_byte_val;
	अन्यथा
		req1->vf_biपंचांगap[vf_byte_off - HCLGE_MAX_VF_BYTES] = vf_byte_val;

	ret = hclge_cmd_send(&hdev->hw, desc, 2);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Send vf vlan command fail, ret =%d.\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_check_vf_vlan_cmd_status(काष्ठा hclge_dev *hdev, u16 vfid,
					  bool is_समाप्त, काष्ठा hclge_desc *desc)
अणु
	काष्ठा hclge_vlan_filter_vf_cfg_cmd *req;

	req = (काष्ठा hclge_vlan_filter_vf_cfg_cmd *)desc[0].data;

	अगर (!is_समाप्त) अणु
#घोषणा HCLGE_VF_VLAN_NO_ENTRY	2
		अगर (!req->resp_code || req->resp_code == 1)
			वापस 0;

		अगर (req->resp_code == HCLGE_VF_VLAN_NO_ENTRY) अणु
			set_bit(vfid, hdev->vf_vlan_full);
			dev_warn(&hdev->pdev->dev,
				 "vf vlan table is full, vf vlan filter is disabled\n");
			वापस 0;
		पूर्ण

		dev_err(&hdev->pdev->dev,
			"Add vf vlan filter fail, ret =%u.\n",
			req->resp_code);
	पूर्ण अन्यथा अणु
#घोषणा HCLGE_VF_VLAN_DEL_NO_FOUND	1
		अगर (!req->resp_code)
			वापस 0;

		/* vf vlan filter is disabled when vf vlan table is full,
		 * then new vlan id will not be added पूर्णांकo vf vlan table.
		 * Just वापस 0 without warning, aव्योम massive verbose
		 * prपूर्णांक logs when unload.
		 */
		अगर (req->resp_code == HCLGE_VF_VLAN_DEL_NO_FOUND)
			वापस 0;

		dev_err(&hdev->pdev->dev,
			"Kill vf vlan filter fail, ret =%u.\n",
			req->resp_code);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक hclge_set_vf_vlan_common(काष्ठा hclge_dev *hdev, u16 vfid,
				    bool is_समाप्त, u16 vlan)
अणु
	काष्ठा hclge_vport *vport = &hdev->vport[vfid];
	काष्ठा hclge_desc desc[2];
	पूर्णांक ret;

	/* अगर vf vlan table is full, firmware will बंद vf vlan filter, it
	 * is unable and unnecessary to add new vlan id to vf vlan filter.
	 * If spoof check is enable, and vf vlan is full, it shouldn't add
	 * new vlan, because tx packets with these vlan id will be dropped.
	 */
	अगर (test_bit(vfid, hdev->vf_vlan_full) && !is_समाप्त) अणु
		अगर (vport->vf_info.spoofchk && vlan) अणु
			dev_err(&hdev->pdev->dev,
				"Can't add vlan due to spoof check is on and vf vlan table is full\n");
			वापस -EPERM;
		पूर्ण
		वापस 0;
	पूर्ण

	ret = hclge_set_vf_vlan_filter_cmd(hdev, vfid, is_समाप्त, vlan, desc);
	अगर (ret)
		वापस ret;

	वापस hclge_check_vf_vlan_cmd_status(hdev, vfid, is_समाप्त, desc);
पूर्ण

अटल पूर्णांक hclge_set_port_vlan_filter(काष्ठा hclge_dev *hdev, __be16 proto,
				      u16 vlan_id, bool is_समाप्त)
अणु
	काष्ठा hclge_vlan_filter_pf_cfg_cmd *req;
	काष्ठा hclge_desc desc;
	u8 vlan_offset_byte_val;
	u8 vlan_offset_byte;
	u8 vlan_offset_160;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_VLAN_FILTER_PF_CFG, false);

	vlan_offset_160 = vlan_id / HCLGE_VLAN_ID_OFFSET_STEP;
	vlan_offset_byte = (vlan_id % HCLGE_VLAN_ID_OFFSET_STEP) /
			   HCLGE_VLAN_BYTE_SIZE;
	vlan_offset_byte_val = 1 << (vlan_id % HCLGE_VLAN_BYTE_SIZE);

	req = (काष्ठा hclge_vlan_filter_pf_cfg_cmd *)desc.data;
	req->vlan_offset = vlan_offset_160;
	req->vlan_cfg = is_समाप्त;
	req->vlan_offset_biपंचांगap[vlan_offset_byte] = vlan_offset_byte_val;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"port vlan command, send fail, ret =%d.\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_set_vlan_filter_hw(काष्ठा hclge_dev *hdev, __be16 proto,
				    u16 vport_id, u16 vlan_id,
				    bool is_समाप्त)
अणु
	u16 vport_idx, vport_num = 0;
	पूर्णांक ret;

	अगर (is_समाप्त && !vlan_id)
		वापस 0;

	ret = hclge_set_vf_vlan_common(hdev, vport_id, is_समाप्त, vlan_id);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Set %u vport vlan filter config fail, ret =%d.\n",
			vport_id, ret);
		वापस ret;
	पूर्ण

	/* vlan 0 may be added twice when 8021q module is enabled */
	अगर (!is_समाप्त && !vlan_id &&
	    test_bit(vport_id, hdev->vlan_table[vlan_id]))
		वापस 0;

	अगर (!is_समाप्त && test_and_set_bit(vport_id, hdev->vlan_table[vlan_id])) अणु
		dev_err(&hdev->pdev->dev,
			"Add port vlan failed, vport %u is already in vlan %u\n",
			vport_id, vlan_id);
		वापस -EINVAL;
	पूर्ण

	अगर (is_समाप्त &&
	    !test_and_clear_bit(vport_id, hdev->vlan_table[vlan_id])) अणु
		dev_err(&hdev->pdev->dev,
			"Delete port vlan failed, vport %u is not in vlan %u\n",
			vport_id, vlan_id);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_set_bit(vport_idx, hdev->vlan_table[vlan_id], HCLGE_VPORT_NUM)
		vport_num++;

	अगर ((is_समाप्त && vport_num == 0) || (!is_समाप्त && vport_num == 1))
		ret = hclge_set_port_vlan_filter(hdev, proto, vlan_id,
						 is_समाप्त);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_set_vlan_tx_offload_cfg(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_tx_vtag_cfg *vcfg = &vport->txvlan_cfg;
	काष्ठा hclge_vport_vtag_tx_cfg_cmd *req;
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_desc desc;
	u16 bmap_index;
	पूर्णांक status;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_VLAN_PORT_TX_CFG, false);

	req = (काष्ठा hclge_vport_vtag_tx_cfg_cmd *)desc.data;
	req->def_vlan_tag1 = cpu_to_le16(vcfg->शेष_tag1);
	req->def_vlan_tag2 = cpu_to_le16(vcfg->शेष_tag2);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_ACCEPT_TAG1_B,
		      vcfg->accept_tag1 ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_ACCEPT_UNTAG1_B,
		      vcfg->accept_untag1 ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_ACCEPT_TAG2_B,
		      vcfg->accept_tag2 ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_ACCEPT_UNTAG2_B,
		      vcfg->accept_untag2 ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_PORT_INS_TAG1_EN_B,
		      vcfg->insert_tag1_en ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_PORT_INS_TAG2_EN_B,
		      vcfg->insert_tag2_en ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_TAG_SHIFT_MODE_EN_B,
		      vcfg->tag_shअगरt_mode_en ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_CFG_NIC_ROCE_SEL_B, 0);

	req->vf_offset = vport->vport_id / HCLGE_VF_NUM_PER_CMD;
	bmap_index = vport->vport_id % HCLGE_VF_NUM_PER_CMD /
			HCLGE_VF_NUM_PER_BYTE;
	req->vf_biपंचांगap[bmap_index] =
		1U << (vport->vport_id % HCLGE_VF_NUM_PER_BYTE);

	status = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"Send port txvlan cfg command fail, ret =%d\n",
			status);

	वापस status;
पूर्ण

अटल पूर्णांक hclge_set_vlan_rx_offload_cfg(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_rx_vtag_cfg *vcfg = &vport->rxvlan_cfg;
	काष्ठा hclge_vport_vtag_rx_cfg_cmd *req;
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_desc desc;
	u16 bmap_index;
	पूर्णांक status;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_VLAN_PORT_RX_CFG, false);

	req = (काष्ठा hclge_vport_vtag_rx_cfg_cmd *)desc.data;
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_REM_TAG1_EN_B,
		      vcfg->strip_tag1_en ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_REM_TAG2_EN_B,
		      vcfg->strip_tag2_en ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_SHOW_TAG1_EN_B,
		      vcfg->vlan1_vlan_prionly ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_SHOW_TAG2_EN_B,
		      vcfg->vlan2_vlan_prionly ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_DISCARD_TAG1_EN_B,
		      vcfg->strip_tag1_discard_en ? 1 : 0);
	hnae3_set_bit(req->vport_vlan_cfg, HCLGE_DISCARD_TAG2_EN_B,
		      vcfg->strip_tag2_discard_en ? 1 : 0);

	req->vf_offset = vport->vport_id / HCLGE_VF_NUM_PER_CMD;
	bmap_index = vport->vport_id % HCLGE_VF_NUM_PER_CMD /
			HCLGE_VF_NUM_PER_BYTE;
	req->vf_biपंचांगap[bmap_index] =
		1U << (vport->vport_id % HCLGE_VF_NUM_PER_BYTE);

	status = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"Send port rxvlan cfg command fail, ret =%d\n",
			status);

	वापस status;
पूर्ण

अटल पूर्णांक hclge_vlan_offload_cfg(काष्ठा hclge_vport *vport,
				  u16 port_base_vlan_state,
				  u16 vlan_tag)
अणु
	पूर्णांक ret;

	अगर (port_base_vlan_state == HNAE3_PORT_BASE_VLAN_DISABLE) अणु
		vport->txvlan_cfg.accept_tag1 = true;
		vport->txvlan_cfg.insert_tag1_en = false;
		vport->txvlan_cfg.शेष_tag1 = 0;
	पूर्ण अन्यथा अणु
		काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(vport->nic.pdev);

		vport->txvlan_cfg.accept_tag1 =
			ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V3;
		vport->txvlan_cfg.insert_tag1_en = true;
		vport->txvlan_cfg.शेष_tag1 = vlan_tag;
	पूर्ण

	vport->txvlan_cfg.accept_untag1 = true;

	/* accept_tag2 and accept_untag2 are not supported on
	 * pdev revision(0x20), new revision support them,
	 * this two fields can not be configured by user.
	 */
	vport->txvlan_cfg.accept_tag2 = true;
	vport->txvlan_cfg.accept_untag2 = true;
	vport->txvlan_cfg.insert_tag2_en = false;
	vport->txvlan_cfg.शेष_tag2 = 0;
	vport->txvlan_cfg.tag_shअगरt_mode_en = true;

	अगर (port_base_vlan_state == HNAE3_PORT_BASE_VLAN_DISABLE) अणु
		vport->rxvlan_cfg.strip_tag1_en = false;
		vport->rxvlan_cfg.strip_tag2_en =
				vport->rxvlan_cfg.rx_vlan_offload_en;
		vport->rxvlan_cfg.strip_tag2_discard_en = false;
	पूर्ण अन्यथा अणु
		vport->rxvlan_cfg.strip_tag1_en =
				vport->rxvlan_cfg.rx_vlan_offload_en;
		vport->rxvlan_cfg.strip_tag2_en = true;
		vport->rxvlan_cfg.strip_tag2_discard_en = true;
	पूर्ण

	vport->rxvlan_cfg.strip_tag1_discard_en = false;
	vport->rxvlan_cfg.vlan1_vlan_prionly = false;
	vport->rxvlan_cfg.vlan2_vlan_prionly = false;

	ret = hclge_set_vlan_tx_offload_cfg(vport);
	अगर (ret)
		वापस ret;

	वापस hclge_set_vlan_rx_offload_cfg(vport);
पूर्ण

अटल पूर्णांक hclge_set_vlan_protocol_type(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_rx_vlan_type_cfg_cmd *rx_req;
	काष्ठा hclge_tx_vlan_type_cfg_cmd *tx_req;
	काष्ठा hclge_desc desc;
	पूर्णांक status;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_VLAN_TYPE_ID, false);
	rx_req = (काष्ठा hclge_rx_vlan_type_cfg_cmd *)desc.data;
	rx_req->ot_fst_vlan_type =
		cpu_to_le16(hdev->vlan_type_cfg.rx_ot_fst_vlan_type);
	rx_req->ot_sec_vlan_type =
		cpu_to_le16(hdev->vlan_type_cfg.rx_ot_sec_vlan_type);
	rx_req->in_fst_vlan_type =
		cpu_to_le16(hdev->vlan_type_cfg.rx_in_fst_vlan_type);
	rx_req->in_sec_vlan_type =
		cpu_to_le16(hdev->vlan_type_cfg.rx_in_sec_vlan_type);

	status = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (status) अणु
		dev_err(&hdev->pdev->dev,
			"Send rxvlan protocol type command fail, ret =%d\n",
			status);
		वापस status;
	पूर्ण

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_VLAN_INSERT, false);

	tx_req = (काष्ठा hclge_tx_vlan_type_cfg_cmd *)desc.data;
	tx_req->ot_vlan_type = cpu_to_le16(hdev->vlan_type_cfg.tx_ot_vlan_type);
	tx_req->in_vlan_type = cpu_to_le16(hdev->vlan_type_cfg.tx_in_vlan_type);

	status = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"Send txvlan protocol type command fail, ret =%d\n",
			status);

	वापस status;
पूर्ण

अटल पूर्णांक hclge_init_vlan_config(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_DEF_VLAN_TYPE		0x8100

	काष्ठा hnae3_handle *handle = &hdev->vport[0].nic;
	काष्ठा hclge_vport *vport;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2) अणु
		/* क्रम revision 0x21, vf vlan filter is per function */
		क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
			vport = &hdev->vport[i];
			ret = hclge_set_vlan_filter_ctrl(hdev,
							 HCLGE_FILTER_TYPE_VF,
							 HCLGE_FILTER_FE_EGRESS,
							 true,
							 vport->vport_id);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_PORT,
						 HCLGE_FILTER_FE_INGRESS, true,
						 0);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_VF,
						 HCLGE_FILTER_FE_EGRESS_V1_B,
						 true, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	handle->netdev_flags |= HNAE3_VLAN_FLTR;

	hdev->vlan_type_cfg.rx_in_fst_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.rx_in_sec_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.rx_ot_fst_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.rx_ot_sec_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.tx_ot_vlan_type = HCLGE_DEF_VLAN_TYPE;
	hdev->vlan_type_cfg.tx_in_vlan_type = HCLGE_DEF_VLAN_TYPE;

	ret = hclge_set_vlan_protocol_type(hdev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		u16 vlan_tag;

		vport = &hdev->vport[i];
		vlan_tag = vport->port_base_vlan_cfg.vlan_info.vlan_tag;

		ret = hclge_vlan_offload_cfg(vport,
					     vport->port_base_vlan_cfg.state,
					     vlan_tag);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस hclge_set_vlan_filter(handle, htons(ETH_P_8021Q), 0, false);
पूर्ण

अटल व्योम hclge_add_vport_vlan_table(काष्ठा hclge_vport *vport, u16 vlan_id,
				       bool ग_लिखोn_to_tbl)
अणु
	काष्ठा hclge_vport_vlan_cfg *vlan;

	vlan = kzalloc(माप(*vlan), GFP_KERNEL);
	अगर (!vlan)
		वापस;

	vlan->hd_tbl_status = ग_लिखोn_to_tbl;
	vlan->vlan_id = vlan_id;

	list_add_tail(&vlan->node, &vport->vlan_list);
पूर्ण

अटल पूर्णांक hclge_add_vport_all_vlan_table(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_vport_vlan_cfg *vlan, *पंचांगp;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(vlan, पंचांगp, &vport->vlan_list, node) अणु
		अगर (!vlan->hd_tbl_status) अणु
			ret = hclge_set_vlan_filter_hw(hdev, htons(ETH_P_8021Q),
						       vport->vport_id,
						       vlan->vlan_id, false);
			अगर (ret) अणु
				dev_err(&hdev->pdev->dev,
					"restore vport vlan list failed, ret=%d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण
		vlan->hd_tbl_status = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclge_rm_vport_vlan_table(काष्ठा hclge_vport *vport, u16 vlan_id,
				      bool is_ग_लिखो_tbl)
अणु
	काष्ठा hclge_vport_vlan_cfg *vlan, *पंचांगp;
	काष्ठा hclge_dev *hdev = vport->back;

	list_क्रम_each_entry_safe(vlan, पंचांगp, &vport->vlan_list, node) अणु
		अगर (vlan->vlan_id == vlan_id) अणु
			अगर (is_ग_लिखो_tbl && vlan->hd_tbl_status)
				hclge_set_vlan_filter_hw(hdev,
							 htons(ETH_P_8021Q),
							 vport->vport_id,
							 vlan_id,
							 true);

			list_del(&vlan->node);
			kमुक्त(vlan);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम hclge_rm_vport_all_vlan_table(काष्ठा hclge_vport *vport, bool is_del_list)
अणु
	काष्ठा hclge_vport_vlan_cfg *vlan, *पंचांगp;
	काष्ठा hclge_dev *hdev = vport->back;

	list_क्रम_each_entry_safe(vlan, पंचांगp, &vport->vlan_list, node) अणु
		अगर (vlan->hd_tbl_status)
			hclge_set_vlan_filter_hw(hdev,
						 htons(ETH_P_8021Q),
						 vport->vport_id,
						 vlan->vlan_id,
						 true);

		vlan->hd_tbl_status = false;
		अगर (is_del_list) अणु
			list_del(&vlan->node);
			kमुक्त(vlan);
		पूर्ण
	पूर्ण
	clear_bit(vport->vport_id, hdev->vf_vlan_full);
पूर्ण

व्योम hclge_uninit_vport_vlan_table(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport_vlan_cfg *vlan, *पंचांगp;
	काष्ठा hclge_vport *vport;
	पूर्णांक i;

	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		vport = &hdev->vport[i];
		list_क्रम_each_entry_safe(vlan, पंचांगp, &vport->vlan_list, node) अणु
			list_del(&vlan->node);
			kमुक्त(vlan);
		पूर्ण
	पूर्ण
पूर्ण

व्योम hclge_restore_vport_vlan_table(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_vport_vlan_cfg *vlan, *पंचांगp;
	काष्ठा hclge_dev *hdev = vport->back;
	u16 vlan_proto;
	u16 vlan_id;
	u16 state;
	पूर्णांक ret;

	vlan_proto = vport->port_base_vlan_cfg.vlan_info.vlan_proto;
	vlan_id = vport->port_base_vlan_cfg.vlan_info.vlan_tag;
	state = vport->port_base_vlan_cfg.state;

	अगर (state != HNAE3_PORT_BASE_VLAN_DISABLE) अणु
		clear_bit(vport->vport_id, hdev->vlan_table[vlan_id]);
		hclge_set_vlan_filter_hw(hdev, htons(vlan_proto),
					 vport->vport_id, vlan_id,
					 false);
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(vlan, पंचांगp, &vport->vlan_list, node) अणु
		ret = hclge_set_vlan_filter_hw(hdev, htons(ETH_P_8021Q),
					       vport->vport_id,
					       vlan->vlan_id, false);
		अगर (ret)
			अवरोध;
		vlan->hd_tbl_status = true;
	पूर्ण
पूर्ण

/* For global reset and imp reset, hardware will clear the mac table,
 * so we change the mac address state from ACTIVE to TO_ADD, then they
 * can be restored in the service task after reset complete. Furtherly,
 * the mac addresses with state TO_DEL or DEL_FAIL are unnecessary to
 * be restored after reset, so just हटाओ these mac nodes from mac_list.
 */
अटल व्योम hclge_mac_node_convert_क्रम_reset(काष्ठा list_head *list)
अणु
	काष्ठा hclge_mac_node *mac_node, *पंचांगp;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node) अणु
		अगर (mac_node->state == HCLGE_MAC_ACTIVE) अणु
			mac_node->state = HCLGE_MAC_TO_ADD;
		पूर्ण अन्यथा अगर (mac_node->state == HCLGE_MAC_TO_DEL) अणु
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण
	पूर्ण
पूर्ण

व्योम hclge_restore_mac_table_common(काष्ठा hclge_vport *vport)
अणु
	spin_lock_bh(&vport->mac_list_lock);

	hclge_mac_node_convert_क्रम_reset(&vport->uc_mac_list);
	hclge_mac_node_convert_क्रम_reset(&vport->mc_mac_list);
	set_bit(HCLGE_VPORT_STATE_MAC_TBL_CHANGE, &vport->state);

	spin_unlock_bh(&vport->mac_list_lock);
पूर्ण

अटल व्योम hclge_restore_hw_table(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = &hdev->vport[0];
	काष्ठा hnae3_handle *handle = &vport->nic;

	hclge_restore_mac_table_common(vport);
	hclge_restore_vport_vlan_table(vport);
	set_bit(HCLGE_STATE_PROMISC_CHANGED, &hdev->state);
	set_bit(HCLGE_STATE_FD_USER_DEF_CHANGED, &hdev->state);
	hclge_restore_fd_entries(handle);
पूर्ण

पूर्णांक hclge_en_hw_strip_rxvtag(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);

	अगर (vport->port_base_vlan_cfg.state == HNAE3_PORT_BASE_VLAN_DISABLE) अणु
		vport->rxvlan_cfg.strip_tag1_en = false;
		vport->rxvlan_cfg.strip_tag2_en = enable;
		vport->rxvlan_cfg.strip_tag2_discard_en = false;
	पूर्ण अन्यथा अणु
		vport->rxvlan_cfg.strip_tag1_en = enable;
		vport->rxvlan_cfg.strip_tag2_en = true;
		vport->rxvlan_cfg.strip_tag2_discard_en = true;
	पूर्ण

	vport->rxvlan_cfg.strip_tag1_discard_en = false;
	vport->rxvlan_cfg.vlan1_vlan_prionly = false;
	vport->rxvlan_cfg.vlan2_vlan_prionly = false;
	vport->rxvlan_cfg.rx_vlan_offload_en = enable;

	वापस hclge_set_vlan_rx_offload_cfg(vport);
पूर्ण

अटल पूर्णांक hclge_update_vlan_filter_entries(काष्ठा hclge_vport *vport,
					    u16 port_base_vlan_state,
					    काष्ठा hclge_vlan_info *new_info,
					    काष्ठा hclge_vlan_info *old_info)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	अगर (port_base_vlan_state == HNAE3_PORT_BASE_VLAN_ENABLE) अणु
		hclge_rm_vport_all_vlan_table(vport, false);
		वापस hclge_set_vlan_filter_hw(hdev,
						 htons(new_info->vlan_proto),
						 vport->vport_id,
						 new_info->vlan_tag,
						 false);
	पूर्ण

	ret = hclge_set_vlan_filter_hw(hdev, htons(old_info->vlan_proto),
				       vport->vport_id, old_info->vlan_tag,
				       true);
	अगर (ret)
		वापस ret;

	वापस hclge_add_vport_all_vlan_table(vport);
पूर्ण

पूर्णांक hclge_update_port_base_vlan_cfg(काष्ठा hclge_vport *vport, u16 state,
				    काष्ठा hclge_vlan_info *vlan_info)
अणु
	काष्ठा hnae3_handle *nic = &vport->nic;
	काष्ठा hclge_vlan_info *old_vlan_info;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	old_vlan_info = &vport->port_base_vlan_cfg.vlan_info;

	ret = hclge_vlan_offload_cfg(vport, state, vlan_info->vlan_tag);
	अगर (ret)
		वापस ret;

	अगर (state == HNAE3_PORT_BASE_VLAN_MODIFY) अणु
		/* add new VLAN tag */
		ret = hclge_set_vlan_filter_hw(hdev,
					       htons(vlan_info->vlan_proto),
					       vport->vport_id,
					       vlan_info->vlan_tag,
					       false);
		अगर (ret)
			वापस ret;

		/* हटाओ old VLAN tag */
		ret = hclge_set_vlan_filter_hw(hdev,
					       htons(old_vlan_info->vlan_proto),
					       vport->vport_id,
					       old_vlan_info->vlan_tag,
					       true);
		अगर (ret)
			वापस ret;

		जाओ update;
	पूर्ण

	ret = hclge_update_vlan_filter_entries(vport, state, vlan_info,
					       old_vlan_info);
	अगर (ret)
		वापस ret;

	/* update state only when disable/enable port based VLAN */
	vport->port_base_vlan_cfg.state = state;
	अगर (state == HNAE3_PORT_BASE_VLAN_DISABLE)
		nic->port_base_vlan_state = HNAE3_PORT_BASE_VLAN_DISABLE;
	अन्यथा
		nic->port_base_vlan_state = HNAE3_PORT_BASE_VLAN_ENABLE;

update:
	vport->port_base_vlan_cfg.vlan_info.vlan_tag = vlan_info->vlan_tag;
	vport->port_base_vlan_cfg.vlan_info.qos = vlan_info->qos;
	vport->port_base_vlan_cfg.vlan_info.vlan_proto = vlan_info->vlan_proto;

	वापस 0;
पूर्ण

अटल u16 hclge_get_port_base_vlan_state(काष्ठा hclge_vport *vport,
					  क्रमागत hnae3_port_base_vlan_state state,
					  u16 vlan)
अणु
	अगर (state == HNAE3_PORT_BASE_VLAN_DISABLE) अणु
		अगर (!vlan)
			वापस HNAE3_PORT_BASE_VLAN_NOCHANGE;
		अन्यथा
			वापस HNAE3_PORT_BASE_VLAN_ENABLE;
	पूर्ण अन्यथा अणु
		अगर (!vlan)
			वापस HNAE3_PORT_BASE_VLAN_DISABLE;
		अन्यथा अगर (vport->port_base_vlan_cfg.vlan_info.vlan_tag == vlan)
			वापस HNAE3_PORT_BASE_VLAN_NOCHANGE;
		अन्यथा
			वापस HNAE3_PORT_BASE_VLAN_MODIFY;
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_set_vf_vlan_filter(काष्ठा hnae3_handle *handle, पूर्णांक vfid,
				    u16 vlan, u8 qos, __be16 proto)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_vlan_info vlan_info;
	u16 state;
	पूर्णांक ret;

	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		वापस -EOPNOTSUPP;

	vport = hclge_get_vf_vport(hdev, vfid);
	अगर (!vport)
		वापस -EINVAL;

	/* qos is a 3 bits value, so can not be bigger than 7 */
	अगर (vlan > VLAN_N_VID - 1 || qos > 7)
		वापस -EINVAL;
	अगर (proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	state = hclge_get_port_base_vlan_state(vport,
					       vport->port_base_vlan_cfg.state,
					       vlan);
	अगर (state == HNAE3_PORT_BASE_VLAN_NOCHANGE)
		वापस 0;

	vlan_info.vlan_tag = vlan;
	vlan_info.qos = qos;
	vlan_info.vlan_proto = ntohs(proto);

	ret = hclge_update_port_base_vlan_cfg(vport, state, &vlan_info);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to update port base vlan for vf %d, ret = %d\n",
			vfid, ret);
		वापस ret;
	पूर्ण

	/* क्रम DEVICE_VERSION_V3, vf करोesn't need to know about the port based
	 * VLAN state.
	 */
	अगर (ae_dev->dev_version < HNAE3_DEVICE_VERSION_V3 &&
	    test_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state))
		hclge_push_vf_port_base_vlan_info(&hdev->vport[0],
						  vport->vport_id, state,
						  vlan, qos,
						  ntohs(proto));

	वापस 0;
पूर्ण

अटल व्योम hclge_clear_vf_vlan(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vlan_info *vlan_info;
	काष्ठा hclge_vport *vport;
	पूर्णांक ret;
	पूर्णांक vf;

	/* clear port base vlan क्रम all vf */
	क्रम (vf = HCLGE_VF_VPORT_START_NUM; vf < hdev->num_alloc_vport; vf++) अणु
		vport = &hdev->vport[vf];
		vlan_info = &vport->port_base_vlan_cfg.vlan_info;

		ret = hclge_set_vlan_filter_hw(hdev, htons(ETH_P_8021Q),
					       vport->vport_id,
					       vlan_info->vlan_tag, true);
		अगर (ret)
			dev_err(&hdev->pdev->dev,
				"failed to clear vf vlan for vf%d, ret = %d\n",
				vf - HCLGE_VF_VPORT_START_NUM, ret);
	पूर्ण
पूर्ण

पूर्णांक hclge_set_vlan_filter(काष्ठा hnae3_handle *handle, __be16 proto,
			  u16 vlan_id, bool is_समाप्त)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	bool ग_लिखोn_to_tbl = false;
	पूर्णांक ret = 0;

	/* When device is resetting or reset failed, firmware is unable to
	 * handle mailbox. Just record the vlan id, and हटाओ it after
	 * reset finished.
	 */
	अगर ((test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state) ||
	     test_bit(HCLGE_STATE_RST_FAIL, &hdev->state)) && is_समाप्त) अणु
		set_bit(vlan_id, vport->vlan_del_fail_bmap);
		वापस -EBUSY;
	पूर्ण

	/* when port base vlan enabled, we use port base vlan as the vlan
	 * filter entry. In this हाल, we करोn't update vlan filter table
	 * when user add new vlan or हटाओ exist vlan, just update the vport
	 * vlan list. The vlan id in vlan list will be ग_लिखोn in vlan filter
	 * table until port base vlan disabled
	 */
	अगर (handle->port_base_vlan_state == HNAE3_PORT_BASE_VLAN_DISABLE) अणु
		ret = hclge_set_vlan_filter_hw(hdev, proto, vport->vport_id,
					       vlan_id, is_समाप्त);
		ग_लिखोn_to_tbl = true;
	पूर्ण

	अगर (!ret) अणु
		अगर (is_समाप्त)
			hclge_rm_vport_vlan_table(vport, vlan_id, false);
		अन्यथा
			hclge_add_vport_vlan_table(vport, vlan_id,
						   ग_लिखोn_to_tbl);
	पूर्ण अन्यथा अगर (is_समाप्त) अणु
		/* when हटाओ hw vlan filter failed, record the vlan id,
		 * and try to हटाओ it from hw later, to be consistence
		 * with stack
		 */
		set_bit(vlan_id, vport->vlan_del_fail_bmap);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम hclge_sync_vlan_filter(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_MAX_SYNC_COUNT	60

	पूर्णांक i, ret, sync_cnt = 0;
	u16 vlan_id;

	/* start from vport 1 क्रम PF is always alive */
	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		काष्ठा hclge_vport *vport = &hdev->vport[i];

		vlan_id = find_first_bit(vport->vlan_del_fail_bmap,
					 VLAN_N_VID);
		जबतक (vlan_id != VLAN_N_VID) अणु
			ret = hclge_set_vlan_filter_hw(hdev, htons(ETH_P_8021Q),
						       vport->vport_id, vlan_id,
						       true);
			अगर (ret && ret != -EINVAL)
				वापस;

			clear_bit(vlan_id, vport->vlan_del_fail_bmap);
			hclge_rm_vport_vlan_table(vport, vlan_id, false);

			sync_cnt++;
			अगर (sync_cnt >= HCLGE_MAX_SYNC_COUNT)
				वापस;

			vlan_id = find_first_bit(vport->vlan_del_fail_bmap,
						 VLAN_N_VID);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_set_mac_mtu(काष्ठा hclge_dev *hdev, पूर्णांक new_mps)
अणु
	काष्ठा hclge_config_max_frm_size_cmd *req;
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_MAX_FRM_SIZE, false);

	req = (काष्ठा hclge_config_max_frm_size_cmd *)desc.data;
	req->max_frm_size = cpu_to_le16(new_mps);
	req->min_frm_size = HCLGE_MAC_MIN_FRAME;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_set_mtu(काष्ठा hnae3_handle *handle, पूर्णांक new_mtu)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);

	वापस hclge_set_vport_mtu(vport, new_mtu);
पूर्ण

पूर्णांक hclge_set_vport_mtu(काष्ठा hclge_vport *vport, पूर्णांक new_mtu)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक i, max_frm_size, ret;

	/* HW supprt 2 layer vlan */
	max_frm_size = new_mtu + ETH_HLEN + ETH_FCS_LEN + 2 * VLAN_HLEN;
	अगर (max_frm_size < HCLGE_MAC_MIN_FRAME ||
	    max_frm_size > hdev->ae_dev->dev_specs.max_frm_size)
		वापस -EINVAL;

	max_frm_size = max(max_frm_size, HCLGE_MAC_DEFAULT_FRAME);
	mutex_lock(&hdev->vport_lock);
	/* VF's mps must fit within hdev->mps */
	अगर (vport->vport_id && max_frm_size > hdev->mps) अणु
		mutex_unlock(&hdev->vport_lock);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (vport->vport_id) अणु
		vport->mps = max_frm_size;
		mutex_unlock(&hdev->vport_lock);
		वापस 0;
	पूर्ण

	/* PF's mps must be greater then VF's mps */
	क्रम (i = 1; i < hdev->num_alloc_vport; i++)
		अगर (max_frm_size < hdev->vport[i].mps) अणु
			mutex_unlock(&hdev->vport_lock);
			वापस -EINVAL;
		पूर्ण

	hclge_notअगरy_client(hdev, HNAE3_DOWN_CLIENT);

	ret = hclge_set_mac_mtu(hdev, max_frm_size);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Change mtu fail, ret =%d\n", ret);
		जाओ out;
	पूर्ण

	hdev->mps = max_frm_size;
	vport->mps = max_frm_size;

	ret = hclge_buffer_alloc(hdev);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"Allocate buffer fail, ret =%d\n", ret);

out:
	hclge_notअगरy_client(hdev, HNAE3_UP_CLIENT);
	mutex_unlock(&hdev->vport_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_reset_tqp_cmd_send(काष्ठा hclge_dev *hdev, u16 queue_id,
				    bool enable)
अणु
	काष्ठा hclge_reset_tqp_queue_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RESET_TQP_QUEUE, false);

	req = (काष्ठा hclge_reset_tqp_queue_cmd *)desc.data;
	req->tqp_id = cpu_to_le16(queue_id);
	अगर (enable)
		hnae3_set_bit(req->reset_req, HCLGE_TQP_RESET_B, 1U);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Send tqp reset cmd error, status =%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_reset_status(काष्ठा hclge_dev *hdev, u16 queue_id)
अणु
	काष्ठा hclge_reset_tqp_queue_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RESET_TQP_QUEUE, true);

	req = (काष्ठा hclge_reset_tqp_queue_cmd *)desc.data;
	req->tqp_id = cpu_to_le16(queue_id);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get reset status error, status =%d\n", ret);
		वापस ret;
	पूर्ण

	वापस hnae3_get_bit(req->पढ़ोy_to_reset, HCLGE_TQP_RESET_B);
पूर्ण

u16 hclge_covert_handle_qid_global(काष्ठा hnae3_handle *handle, u16 queue_id)
अणु
	काष्ठा hnae3_queue *queue;
	काष्ठा hclge_tqp *tqp;

	queue = handle->kinfo.tqp[queue_id];
	tqp = container_of(queue, काष्ठा hclge_tqp, q);

	वापस tqp->index;
पूर्ण

अटल पूर्णांक hclge_reset_tqp_cmd(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	u16 reset_try_बार = 0;
	पूर्णांक reset_status;
	u16 queue_gid;
	पूर्णांक ret;
	u16 i;

	क्रम (i = 0; i < handle->kinfo.num_tqps; i++) अणु
		queue_gid = hclge_covert_handle_qid_global(handle, i);
		ret = hclge_reset_tqp_cmd_send(hdev, queue_gid, true);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"failed to send reset tqp cmd, ret = %d\n",
				ret);
			वापस ret;
		पूर्ण

		जबतक (reset_try_बार++ < HCLGE_TQP_RESET_TRY_TIMES) अणु
			reset_status = hclge_get_reset_status(hdev, queue_gid);
			अगर (reset_status)
				अवरोध;

			/* Wait क्रम tqp hw reset */
			usleep_range(1000, 1200);
		पूर्ण

		अगर (reset_try_बार >= HCLGE_TQP_RESET_TRY_TIMES) अणु
			dev_err(&hdev->pdev->dev,
				"wait for tqp hw reset timeout\n");
			वापस -ETIME;
		पूर्ण

		ret = hclge_reset_tqp_cmd_send(hdev, queue_gid, false);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"failed to deassert soft reset, ret = %d\n",
				ret);
			वापस ret;
		पूर्ण
		reset_try_बार = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_reset_rcb(काष्ठा hnae3_handle *handle)
अणु
#घोषणा HCLGE_RESET_RCB_NOT_SUPPORT	0U
#घोषणा HCLGE_RESET_RCB_SUCCESS		1U

	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_reset_cmd *req;
	काष्ठा hclge_desc desc;
	u8 वापस_status;
	u16 queue_gid;
	पूर्णांक ret;

	queue_gid = hclge_covert_handle_qid_global(handle, 0);

	req = (काष्ठा hclge_reset_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_RST_TRIGGER, false);
	hnae3_set_bit(req->fun_reset_rcb, HCLGE_CFG_RESET_RCB_B, 1);
	req->fun_reset_rcb_vqid_start = cpu_to_le16(queue_gid);
	req->fun_reset_rcb_vqid_num = cpu_to_le16(handle->kinfo.num_tqps);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to send rcb reset cmd, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	वापस_status = req->fun_reset_rcb_वापस_status;
	अगर (वापस_status == HCLGE_RESET_RCB_SUCCESS)
		वापस 0;

	अगर (वापस_status != HCLGE_RESET_RCB_NOT_SUPPORT) अणु
		dev_err(&hdev->pdev->dev, "failed to reset rcb, ret = %u\n",
			वापस_status);
		वापस -EIO;
	पूर्ण

	/* अगर reset rcb cmd is unsupported, we need to send reset tqp cmd
	 * again to reset all tqps
	 */
	वापस hclge_reset_tqp_cmd(handle);
पूर्ण

पूर्णांक hclge_reset_tqp(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	/* only need to disable PF's tqp */
	अगर (!vport->vport_id) अणु
		ret = hclge_tqp_enable(handle, false);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"failed to disable tqp, ret = %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस hclge_reset_rcb(handle);
पूर्ण

अटल u32 hclge_get_fw_version(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस hdev->fw_version;
पूर्ण

अटल व्योम hclge_set_flowctrl_adv(काष्ठा hclge_dev *hdev, u32 rx_en, u32 tx_en)
अणु
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;

	अगर (!phydev)
		वापस;

	phy_set_asym_छोड़ो(phydev, rx_en, tx_en);
पूर्ण

अटल पूर्णांक hclge_cfg_छोड़ोparam(काष्ठा hclge_dev *hdev, u32 rx_en, u32 tx_en)
अणु
	पूर्णांक ret;

	अगर (hdev->पंचांग_info.fc_mode == HCLGE_FC_PFC)
		वापस 0;

	ret = hclge_mac_छोड़ो_en_cfg(hdev, tx_en, rx_en);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"configure pauseparam error, ret = %d.\n", ret);

	वापस ret;
पूर्ण

पूर्णांक hclge_cfg_flowctrl(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;
	u16 remote_advertising = 0;
	u16 local_advertising;
	u32 rx_छोड़ो, tx_छोड़ो;
	u8 flowctl;

	अगर (!phydev->link || !phydev->स्वतःneg)
		वापस 0;

	local_advertising = linkmode_adv_to_lcl_adv_t(phydev->advertising);

	अगर (phydev->छोड़ो)
		remote_advertising = LPA_PAUSE_CAP;

	अगर (phydev->asym_छोड़ो)
		remote_advertising |= LPA_PAUSE_ASYM;

	flowctl = mii_resolve_flowctrl_fdx(local_advertising,
					   remote_advertising);
	tx_छोड़ो = flowctl & FLOW_CTRL_TX;
	rx_छोड़ो = flowctl & FLOW_CTRL_RX;

	अगर (phydev->duplex == HCLGE_MAC_HALF) अणु
		tx_छोड़ो = 0;
		rx_छोड़ो = 0;
	पूर्ण

	वापस hclge_cfg_छोड़ोparam(hdev, rx_छोड़ो, tx_छोड़ो);
पूर्ण

अटल व्योम hclge_get_छोड़ोparam(काष्ठा hnae3_handle *handle, u32 *स्वतः_neg,
				 u32 *rx_en, u32 *tx_en)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	u8 media_type = hdev->hw.mac.media_type;

	*स्वतः_neg = (media_type == HNAE3_MEDIA_TYPE_COPPER) ?
		    hclge_get_स्वतःneg(handle) : 0;

	अगर (hdev->पंचांग_info.fc_mode == HCLGE_FC_PFC) अणु
		*rx_en = 0;
		*tx_en = 0;
		वापस;
	पूर्ण

	अगर (hdev->पंचांग_info.fc_mode == HCLGE_FC_RX_PAUSE) अणु
		*rx_en = 1;
		*tx_en = 0;
	पूर्ण अन्यथा अगर (hdev->पंचांग_info.fc_mode == HCLGE_FC_TX_PAUSE) अणु
		*tx_en = 1;
		*rx_en = 0;
	पूर्ण अन्यथा अगर (hdev->पंचांग_info.fc_mode == HCLGE_FC_FULL) अणु
		*rx_en = 1;
		*tx_en = 1;
	पूर्ण अन्यथा अणु
		*rx_en = 0;
		*tx_en = 0;
	पूर्ण
पूर्ण

अटल व्योम hclge_record_user_छोड़ोparam(काष्ठा hclge_dev *hdev,
					 u32 rx_en, u32 tx_en)
अणु
	अगर (rx_en && tx_en)
		hdev->fc_mode_last_समय = HCLGE_FC_FULL;
	अन्यथा अगर (rx_en && !tx_en)
		hdev->fc_mode_last_समय = HCLGE_FC_RX_PAUSE;
	अन्यथा अगर (!rx_en && tx_en)
		hdev->fc_mode_last_समय = HCLGE_FC_TX_PAUSE;
	अन्यथा
		hdev->fc_mode_last_समय = HCLGE_FC_NONE;

	hdev->पंचांग_info.fc_mode = hdev->fc_mode_last_समय;
पूर्ण

अटल पूर्णांक hclge_set_छोड़ोparam(काष्ठा hnae3_handle *handle, u32 स्वतः_neg,
				u32 rx_en, u32 tx_en)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;
	u32 fc_स्वतःneg;

	अगर (phydev || hnae3_dev_phy_imp_supported(hdev)) अणु
		fc_स्वतःneg = hclge_get_स्वतःneg(handle);
		अगर (स्वतः_neg != fc_स्वतःneg) अणु
			dev_info(&hdev->pdev->dev,
				 "To change autoneg please use: ethtool -s <dev> autoneg <on|off>\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (hdev->पंचांग_info.fc_mode == HCLGE_FC_PFC) अणु
		dev_info(&hdev->pdev->dev,
			 "Priority flow control enabled. Cannot set link flow control.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	hclge_set_flowctrl_adv(hdev, rx_en, tx_en);

	hclge_record_user_छोड़ोparam(hdev, rx_en, tx_en);

	अगर (!स्वतः_neg || hnae3_dev_phy_imp_supported(hdev))
		वापस hclge_cfg_छोड़ोparam(hdev, rx_en, tx_en);

	अगर (phydev)
		वापस phy_start_aneg(phydev);

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम hclge_get_ksettings_an_result(काष्ठा hnae3_handle *handle,
					  u8 *स्वतः_neg, u32 *speed, u8 *duplex)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (speed)
		*speed = hdev->hw.mac.speed;
	अगर (duplex)
		*duplex = hdev->hw.mac.duplex;
	अगर (स्वतः_neg)
		*स्वतः_neg = hdev->hw.mac.स्वतःneg;
पूर्ण

अटल व्योम hclge_get_media_type(काष्ठा hnae3_handle *handle, u8 *media_type,
				 u8 *module_type)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	/* When nic is करोwn, the service task is not running, करोesn't update
	 * the port inक्रमmation per second. Query the port inक्रमmation beक्रमe
	 * वापस the media type, ensure getting the correct media inक्रमmation.
	 */
	hclge_update_port_info(hdev);

	अगर (media_type)
		*media_type = hdev->hw.mac.media_type;

	अगर (module_type)
		*module_type = hdev->hw.mac.module_type;
पूर्ण

अटल व्योम hclge_get_mdix_mode(काष्ठा hnae3_handle *handle,
				u8 *tp_mdix_ctrl, u8 *tp_mdix)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;
	पूर्णांक mdix_ctrl, mdix, is_resolved;
	अचिन्हित पूर्णांक retval;

	अगर (!phydev) अणु
		*tp_mdix_ctrl = ETH_TP_MDI_INVALID;
		*tp_mdix = ETH_TP_MDI_INVALID;
		वापस;
	पूर्ण

	phy_ग_लिखो(phydev, HCLGE_PHY_PAGE_REG, HCLGE_PHY_PAGE_MDIX);

	retval = phy_पढ़ो(phydev, HCLGE_PHY_CSC_REG);
	mdix_ctrl = hnae3_get_field(retval, HCLGE_PHY_MDIX_CTRL_M,
				    HCLGE_PHY_MDIX_CTRL_S);

	retval = phy_पढ़ो(phydev, HCLGE_PHY_CSS_REG);
	mdix = hnae3_get_bit(retval, HCLGE_PHY_MDIX_STATUS_B);
	is_resolved = hnae3_get_bit(retval, HCLGE_PHY_SPEED_DUP_RESOLVE_B);

	phy_ग_लिखो(phydev, HCLGE_PHY_PAGE_REG, HCLGE_PHY_PAGE_COPPER);

	चयन (mdix_ctrl) अणु
	हाल 0x0:
		*tp_mdix_ctrl = ETH_TP_MDI;
		अवरोध;
	हाल 0x1:
		*tp_mdix_ctrl = ETH_TP_MDI_X;
		अवरोध;
	हाल 0x3:
		*tp_mdix_ctrl = ETH_TP_MDI_AUTO;
		अवरोध;
	शेष:
		*tp_mdix_ctrl = ETH_TP_MDI_INVALID;
		अवरोध;
	पूर्ण

	अगर (!is_resolved)
		*tp_mdix = ETH_TP_MDI_INVALID;
	अन्यथा अगर (mdix)
		*tp_mdix = ETH_TP_MDI_X;
	अन्यथा
		*tp_mdix = ETH_TP_MDI;
पूर्ण

अटल व्योम hclge_info_show(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;

	dev_info(dev, "PF info begin:\n");

	dev_info(dev, "Task queue pairs numbers: %u\n", hdev->num_tqps);
	dev_info(dev, "Desc num per TX queue: %u\n", hdev->num_tx_desc);
	dev_info(dev, "Desc num per RX queue: %u\n", hdev->num_rx_desc);
	dev_info(dev, "Numbers of vports: %u\n", hdev->num_alloc_vport);
	dev_info(dev, "Numbers of VF for this PF: %u\n", hdev->num_req_vfs);
	dev_info(dev, "HW tc map: 0x%x\n", hdev->hw_tc_map);
	dev_info(dev, "Total buffer size for TX/RX: %u\n", hdev->pkt_buf_size);
	dev_info(dev, "TX buffer size for each TC: %u\n", hdev->tx_buf_size);
	dev_info(dev, "DV buffer size for each TC: %u\n", hdev->dv_buf_size);
	dev_info(dev, "This is %s PF\n",
		 hdev->flag & HCLGE_FLAG_MAIN ? "main" : "not main");
	dev_info(dev, "DCB %s\n",
		 hdev->flag & HCLGE_FLAG_DCB_ENABLE ? "enable" : "disable");
	dev_info(dev, "MQPRIO %s\n",
		 hdev->flag & HCLGE_FLAG_MQPRIO_ENABLE ? "enable" : "disable");

	dev_info(dev, "PF info end.\n");
पूर्ण

अटल पूर्णांक hclge_init_nic_client_instance(काष्ठा hnae3_ae_dev *ae_dev,
					  काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_client *client = vport->nic.client;
	काष्ठा hclge_dev *hdev = ae_dev->priv;
	पूर्णांक rst_cnt = hdev->rst_stats.reset_cnt;
	पूर्णांक ret;

	ret = client->ops->init_instance(&vport->nic);
	अगर (ret)
		वापस ret;

	set_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state);
	अगर (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state) ||
	    rst_cnt != hdev->rst_stats.reset_cnt) अणु
		ret = -EBUSY;
		जाओ init_nic_err;
	पूर्ण

	/* Enable nic hw error पूर्णांकerrupts */
	ret = hclge_config_nic_hw_error(hdev, true);
	अगर (ret) अणु
		dev_err(&ae_dev->pdev->dev,
			"fail(%d) to enable hw error interrupts\n", ret);
		जाओ init_nic_err;
	पूर्ण

	hnae3_set_client_init_flag(client, ae_dev, 1);

	अगर (netअगर_msg_drv(&hdev->vport->nic))
		hclge_info_show(hdev);

	वापस ret;

init_nic_err:
	clear_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state);
	जबतक (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
		msleep(HCLGE_WAIT_RESET_DONE);

	client->ops->uninit_instance(&vport->nic, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_init_roce_client_instance(काष्ठा hnae3_ae_dev *ae_dev,
					   काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_dev *hdev = ae_dev->priv;
	काष्ठा hnae3_client *client;
	पूर्णांक rst_cnt;
	पूर्णांक ret;

	अगर (!hnae3_dev_roce_supported(hdev) || !hdev->roce_client ||
	    !hdev->nic_client)
		वापस 0;

	client = hdev->roce_client;
	ret = hclge_init_roce_base_info(vport);
	अगर (ret)
		वापस ret;

	rst_cnt = hdev->rst_stats.reset_cnt;
	ret = client->ops->init_instance(&vport->roce);
	अगर (ret)
		वापस ret;

	set_bit(HCLGE_STATE_ROCE_REGISTERED, &hdev->state);
	अगर (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state) ||
	    rst_cnt != hdev->rst_stats.reset_cnt) अणु
		ret = -EBUSY;
		जाओ init_roce_err;
	पूर्ण

	/* Enable roce ras पूर्णांकerrupts */
	ret = hclge_config_rocee_ras_पूर्णांकerrupt(hdev, true);
	अगर (ret) अणु
		dev_err(&ae_dev->pdev->dev,
			"fail(%d) to enable roce ras interrupts\n", ret);
		जाओ init_roce_err;
	पूर्ण

	hnae3_set_client_init_flag(client, ae_dev, 1);

	वापस 0;

init_roce_err:
	clear_bit(HCLGE_STATE_ROCE_REGISTERED, &hdev->state);
	जबतक (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
		msleep(HCLGE_WAIT_RESET_DONE);

	hdev->roce_client->ops->uninit_instance(&vport->roce, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_init_client_instance(काष्ठा hnae3_client *client,
				      काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclge_dev *hdev = ae_dev->priv;
	काष्ठा hclge_vport *vport = &hdev->vport[0];
	पूर्णांक ret;

	चयन (client->type) अणु
	हाल HNAE3_CLIENT_KNIC:
		hdev->nic_client = client;
		vport->nic.client = client;
		ret = hclge_init_nic_client_instance(ae_dev, vport);
		अगर (ret)
			जाओ clear_nic;

		ret = hclge_init_roce_client_instance(ae_dev, vport);
		अगर (ret)
			जाओ clear_roce;

		अवरोध;
	हाल HNAE3_CLIENT_ROCE:
		अगर (hnae3_dev_roce_supported(hdev)) अणु
			hdev->roce_client = client;
			vport->roce.client = client;
		पूर्ण

		ret = hclge_init_roce_client_instance(ae_dev, vport);
		अगर (ret)
			जाओ clear_roce;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;

clear_nic:
	hdev->nic_client = शून्य;
	vport->nic.client = शून्य;
	वापस ret;
clear_roce:
	hdev->roce_client = शून्य;
	vport->roce.client = शून्य;
	वापस ret;
पूर्ण

अटल व्योम hclge_uninit_client_instance(काष्ठा hnae3_client *client,
					 काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclge_dev *hdev = ae_dev->priv;
	काष्ठा hclge_vport *vport = &hdev->vport[0];

	अगर (hdev->roce_client) अणु
		clear_bit(HCLGE_STATE_ROCE_REGISTERED, &hdev->state);
		जबतक (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
			msleep(HCLGE_WAIT_RESET_DONE);

		hdev->roce_client->ops->uninit_instance(&vport->roce, 0);
		hdev->roce_client = शून्य;
		vport->roce.client = शून्य;
	पूर्ण
	अगर (client->type == HNAE3_CLIENT_ROCE)
		वापस;
	अगर (hdev->nic_client && client->ops->uninit_instance) अणु
		clear_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state);
		जबतक (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
			msleep(HCLGE_WAIT_RESET_DONE);

		client->ops->uninit_instance(&vport->nic, 0);
		hdev->nic_client = शून्य;
		vport->nic.client = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_dev_mem_map(काष्ठा hclge_dev *hdev)
अणु
#घोषणा HCLGE_MEM_BAR		4

	काष्ठा pci_dev *pdev = hdev->pdev;
	काष्ठा hclge_hw *hw = &hdev->hw;

	/* क्रम device करोes not have device memory, वापस directly */
	अगर (!(pci_select_bars(pdev, IORESOURCE_MEM) & BIT(HCLGE_MEM_BAR)))
		वापस 0;

	hw->mem_base = devm_ioremap_wc(&pdev->dev,
				       pci_resource_start(pdev, HCLGE_MEM_BAR),
				       pci_resource_len(pdev, HCLGE_MEM_BAR));
	अगर (!hw->mem_base) अणु
		dev_err(&pdev->dev, "failed to map device memory\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_pci_init(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	काष्ठा hclge_hw *hw;
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable PCI device\n");
		वापस ret;
	पूर्ण

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"can't set consistent PCI DMA");
			जाओ err_disable_device;
		पूर्ण
		dev_warn(&pdev->dev, "set DMA mask to 32 bits\n");
	पूर्ण

	ret = pci_request_regions(pdev, HCLGE_DRIVER_NAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "PCI request regions failed %d\n", ret);
		जाओ err_disable_device;
	पूर्ण

	pci_set_master(pdev);
	hw = &hdev->hw;
	hw->io_base = pcim_iomap(pdev, 2, 0);
	अगर (!hw->io_base) अणु
		dev_err(&pdev->dev, "Can't map configuration register space\n");
		ret = -ENOMEM;
		जाओ err_clr_master;
	पूर्ण

	ret = hclge_dev_mem_map(hdev);
	अगर (ret)
		जाओ err_unmap_io_base;

	hdev->num_req_vfs = pci_sriov_get_totalvfs(pdev);

	वापस 0;

err_unmap_io_base:
	pcim_iounmap(pdev, hdev->hw.io_base);
err_clr_master:
	pci_clear_master(pdev);
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);

	वापस ret;
पूर्ण

अटल व्योम hclge_pci_uninit(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;

	अगर (hdev->hw.mem_base)
		devm_iounmap(&pdev->dev, hdev->hw.mem_base);

	pcim_iounmap(pdev, hdev->hw.io_base);
	pci_मुक्त_irq_vectors(pdev);
	pci_clear_master(pdev);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल व्योम hclge_state_init(काष्ठा hclge_dev *hdev)
अणु
	set_bit(HCLGE_STATE_SERVICE_INITED, &hdev->state);
	set_bit(HCLGE_STATE_DOWN, &hdev->state);
	clear_bit(HCLGE_STATE_RST_SERVICE_SCHED, &hdev->state);
	clear_bit(HCLGE_STATE_RST_HANDLING, &hdev->state);
	clear_bit(HCLGE_STATE_RST_FAIL, &hdev->state);
	clear_bit(HCLGE_STATE_MBX_SERVICE_SCHED, &hdev->state);
	clear_bit(HCLGE_STATE_MBX_HANDLING, &hdev->state);
पूर्ण

अटल व्योम hclge_state_uninit(काष्ठा hclge_dev *hdev)
अणु
	set_bit(HCLGE_STATE_DOWN, &hdev->state);
	set_bit(HCLGE_STATE_REMOVING, &hdev->state);

	अगर (hdev->reset_समयr.function)
		del_समयr_sync(&hdev->reset_समयr);
	अगर (hdev->service_task.work.func)
		cancel_delayed_work_sync(&hdev->service_task);
पूर्ण

अटल व्योम hclge_reset_prepare_general(काष्ठा hnae3_ae_dev *ae_dev,
					क्रमागत hnae3_reset_type rst_type)
अणु
#घोषणा HCLGE_RESET_RETRY_WAIT_MS	500
#घोषणा HCLGE_RESET_RETRY_CNT	5

	काष्ठा hclge_dev *hdev = ae_dev->priv;
	पूर्णांक retry_cnt = 0;
	पूर्णांक ret;

retry:
	करोwn(&hdev->reset_sem);
	set_bit(HCLGE_STATE_RST_HANDLING, &hdev->state);
	hdev->reset_type = rst_type;
	ret = hclge_reset_prepare(hdev);
	अगर (ret || hdev->reset_pending) अणु
		dev_err(&hdev->pdev->dev, "fail to prepare to reset, ret=%d\n",
			ret);
		अगर (hdev->reset_pending ||
		    retry_cnt++ < HCLGE_RESET_RETRY_CNT) अणु
			dev_err(&hdev->pdev->dev,
				"reset_pending:0x%lx, retry_cnt:%d\n",
				hdev->reset_pending, retry_cnt);
			clear_bit(HCLGE_STATE_RST_HANDLING, &hdev->state);
			up(&hdev->reset_sem);
			msleep(HCLGE_RESET_RETRY_WAIT_MS);
			जाओ retry;
		पूर्ण
	पूर्ण

	/* disable misc vector beक्रमe reset करोne */
	hclge_enable_vector(&hdev->misc_vector, false);
	set_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);

	अगर (hdev->reset_type == HNAE3_FLR_RESET)
		hdev->rst_stats.flr_rst_cnt++;
पूर्ण

अटल व्योम hclge_reset_करोne(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclge_dev *hdev = ae_dev->priv;
	पूर्णांक ret;

	hclge_enable_vector(&hdev->misc_vector, true);

	ret = hclge_reset_rebuild(hdev);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "fail to rebuild, ret=%d\n", ret);

	hdev->reset_type = HNAE3_NONE_RESET;
	clear_bit(HCLGE_STATE_RST_HANDLING, &hdev->state);
	up(&hdev->reset_sem);
पूर्ण

अटल व्योम hclge_clear_resetting_state(काष्ठा hclge_dev *hdev)
अणु
	u16 i;

	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		काष्ठा hclge_vport *vport = &hdev->vport[i];
		पूर्णांक ret;

		 /* Send cmd to clear VF's FUNC_RST_ING */
		ret = hclge_set_vf_rst(hdev, vport->vport_id, false);
		अगर (ret)
			dev_warn(&hdev->pdev->dev,
				 "clear vf(%u) rst failed %d!\n",
				 vport->vport_id, ret);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_init_ae_dev(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा pci_dev *pdev = ae_dev->pdev;
	काष्ठा hclge_dev *hdev;
	पूर्णांक ret;

	hdev = devm_kzalloc(&pdev->dev, माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस -ENOMEM;

	hdev->pdev = pdev;
	hdev->ae_dev = ae_dev;
	hdev->reset_type = HNAE3_NONE_RESET;
	hdev->reset_level = HNAE3_FUNC_RESET;
	ae_dev->priv = hdev;

	/* HW supprt 2 layer vlan */
	hdev->mps = ETH_FRAME_LEN + ETH_FCS_LEN + 2 * VLAN_HLEN;

	mutex_init(&hdev->vport_lock);
	spin_lock_init(&hdev->fd_rule_lock);
	sema_init(&hdev->reset_sem, 1);

	ret = hclge_pci_init(hdev);
	अगर (ret)
		जाओ out;

	/* Firmware command queue initialize */
	ret = hclge_cmd_queue_init(hdev);
	अगर (ret)
		जाओ err_pci_uninit;

	/* Firmware command initialize */
	ret = hclge_cmd_init(hdev);
	अगर (ret)
		जाओ err_cmd_uninit;

	ret = hclge_get_cap(hdev);
	अगर (ret)
		जाओ err_cmd_uninit;

	ret = hclge_query_dev_specs(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to query dev specifications, ret = %d.\n",
			ret);
		जाओ err_cmd_uninit;
	पूर्ण

	ret = hclge_configure(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Configure dev error, ret = %d.\n", ret);
		जाओ err_cmd_uninit;
	पूर्ण

	ret = hclge_init_msi(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Init MSI/MSI-X error, ret = %d.\n", ret);
		जाओ err_cmd_uninit;
	पूर्ण

	ret = hclge_misc_irq_init(hdev);
	अगर (ret)
		जाओ err_msi_uninit;

	ret = hclge_alloc_tqps(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Allocate TQPs error, ret = %d.\n", ret);
		जाओ err_msi_irq_uninit;
	पूर्ण

	ret = hclge_alloc_vport(hdev);
	अगर (ret)
		जाओ err_msi_irq_uninit;

	ret = hclge_map_tqp(hdev);
	अगर (ret)
		जाओ err_msi_irq_uninit;

	अगर (hdev->hw.mac.media_type == HNAE3_MEDIA_TYPE_COPPER &&
	    !hnae3_dev_phy_imp_supported(hdev)) अणु
		ret = hclge_mac_mdio_config(hdev);
		अगर (ret)
			जाओ err_msi_irq_uninit;
	पूर्ण

	ret = hclge_init_umv_space(hdev);
	अगर (ret)
		जाओ err_mdiobus_unreg;

	ret = hclge_mac_init(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Mac init error, ret = %d\n", ret);
		जाओ err_mdiobus_unreg;
	पूर्ण

	ret = hclge_config_tso(hdev, HCLGE_TSO_MSS_MIN, HCLGE_TSO_MSS_MAX);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Enable tso fail, ret =%d\n", ret);
		जाओ err_mdiobus_unreg;
	पूर्ण

	ret = hclge_config_gro(hdev, true);
	अगर (ret)
		जाओ err_mdiobus_unreg;

	ret = hclge_init_vlan_config(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "VLAN init fail, ret =%d\n", ret);
		जाओ err_mdiobus_unreg;
	पूर्ण

	ret = hclge_पंचांग_schd_init(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "tm schd init fail, ret =%d\n", ret);
		जाओ err_mdiobus_unreg;
	पूर्ण

	ret = hclge_rss_init_cfg(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to init rss cfg, ret = %d\n", ret);
		जाओ err_mdiobus_unreg;
	पूर्ण

	ret = hclge_rss_init_hw(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Rss init fail, ret =%d\n", ret);
		जाओ err_mdiobus_unreg;
	पूर्ण

	ret = init_mgr_tbl(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "manager table init fail, ret =%d\n", ret);
		जाओ err_mdiobus_unreg;
	पूर्ण

	ret = hclge_init_fd_config(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"fd table init fail, ret=%d\n", ret);
		जाओ err_mdiobus_unreg;
	पूर्ण

	INIT_KFIFO(hdev->mac_tnl_log);

	hclge_dcb_ops_set(hdev);

	समयr_setup(&hdev->reset_समयr, hclge_reset_समयr, 0);
	INIT_DELAYED_WORK(&hdev->service_task, hclge_service_task);

	/* Setup affinity after service समयr setup because add_समयr_on
	 * is called in affinity notअगरy.
	 */
	hclge_misc_affinity_setup(hdev);

	hclge_clear_all_event_cause(hdev);
	hclge_clear_resetting_state(hdev);

	/* Log and clear the hw errors those alपढ़ोy occurred */
	hclge_handle_all_hns_hw_errors(ae_dev);

	/* request delayed reset क्रम the error recovery because an immediate
	 * global reset on a PF affecting pending initialization of other PFs
	 */
	अगर (ae_dev->hw_err_reset_req) अणु
		क्रमागत hnae3_reset_type reset_level;

		reset_level = hclge_get_reset_level(ae_dev,
						    &ae_dev->hw_err_reset_req);
		hclge_set_def_reset_request(ae_dev, reset_level);
		mod_समयr(&hdev->reset_समयr, jअगरfies + HCLGE_RESET_INTERVAL);
	पूर्ण

	/* Enable MISC vector(vector0) */
	hclge_enable_vector(&hdev->misc_vector, true);

	hclge_state_init(hdev);
	hdev->last_reset_समय = jअगरfies;

	dev_info(&hdev->pdev->dev, "%s driver initialization finished.\n",
		 HCLGE_DRIVER_NAME);

	hclge_task_schedule(hdev, round_jअगरfies_relative(HZ));

	वापस 0;

err_mdiobus_unreg:
	अगर (hdev->hw.mac.phydev)
		mdiobus_unरेजिस्टर(hdev->hw.mac.mdio_bus);
err_msi_irq_uninit:
	hclge_misc_irq_uninit(hdev);
err_msi_uninit:
	pci_मुक्त_irq_vectors(pdev);
err_cmd_uninit:
	hclge_cmd_uninit(hdev);
err_pci_uninit:
	pcim_iounmap(pdev, hdev->hw.io_base);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
out:
	mutex_destroy(&hdev->vport_lock);
	वापस ret;
पूर्ण

अटल व्योम hclge_stats_clear(काष्ठा hclge_dev *hdev)
अणु
	स_रखो(&hdev->mac_stats, 0, माप(hdev->mac_stats));
पूर्ण

अटल पूर्णांक hclge_set_mac_spoofchk(काष्ठा hclge_dev *hdev, पूर्णांक vf, bool enable)
अणु
	वापस hclge_config_चयन_param(hdev, vf, enable,
					 HCLGE_SWITCH_ANTI_SPOOF_MASK);
पूर्ण

अटल पूर्णांक hclge_set_vlan_spoofchk(काष्ठा hclge_dev *hdev, पूर्णांक vf, bool enable)
अणु
	वापस hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_VF,
					  HCLGE_FILTER_FE_NIC_INGRESS_B,
					  enable, vf);
पूर्ण

अटल पूर्णांक hclge_set_vf_spoofchk_hw(काष्ठा hclge_dev *hdev, पूर्णांक vf, bool enable)
अणु
	पूर्णांक ret;

	ret = hclge_set_mac_spoofchk(hdev, vf, enable);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Set vf %d mac spoof check %s failed, ret=%d\n",
			vf, enable ? "on" : "off", ret);
		वापस ret;
	पूर्ण

	ret = hclge_set_vlan_spoofchk(hdev, vf, enable);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"Set vf %d vlan spoof check %s failed, ret=%d\n",
			vf, enable ? "on" : "off", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_set_vf_spoofchk(काष्ठा hnae3_handle *handle, पूर्णांक vf,
				 bool enable)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	u32 new_spoofchk = enable ? 1 : 0;
	पूर्णांक ret;

	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		वापस -EOPNOTSUPP;

	vport = hclge_get_vf_vport(hdev, vf);
	अगर (!vport)
		वापस -EINVAL;

	अगर (vport->vf_info.spoofchk == new_spoofchk)
		वापस 0;

	अगर (enable && test_bit(vport->vport_id, hdev->vf_vlan_full))
		dev_warn(&hdev->pdev->dev,
			 "vf %d vlan table is full, enable spoof check may cause its packet send fail\n",
			 vf);
	अन्यथा अगर (enable && hclge_is_umv_space_full(vport, true))
		dev_warn(&hdev->pdev->dev,
			 "vf %d mac table is full, enable spoof check may cause its packet send fail\n",
			 vf);

	ret = hclge_set_vf_spoofchk_hw(hdev, vport->vport_id, enable);
	अगर (ret)
		वापस ret;

	vport->vf_info.spoofchk = new_spoofchk;
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_reset_vport_spoofchk(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		वापस 0;

	/* resume the vf spoof check state after reset */
	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		ret = hclge_set_vf_spoofchk_hw(hdev, vport->vport_id,
					       vport->vf_info.spoofchk);
		अगर (ret)
			वापस ret;

		vport++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_vf_trust(काष्ठा hnae3_handle *handle, पूर्णांक vf, bool enable)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hnae3_ae_dev *ae_dev = hdev->ae_dev;
	u32 new_trusted = enable ? 1 : 0;
	bool en_bc_pmc;
	पूर्णांक ret;

	vport = hclge_get_vf_vport(hdev, vf);
	अगर (!vport)
		वापस -EINVAL;

	अगर (vport->vf_info.trusted == new_trusted)
		वापस 0;

	/* Disable promisc mode क्रम VF अगर it is not trusted any more. */
	अगर (!enable && vport->vf_info.promisc_enable) अणु
		en_bc_pmc = ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2;
		ret = hclge_set_vport_promisc_mode(vport, false, false,
						   en_bc_pmc);
		अगर (ret)
			वापस ret;
		vport->vf_info.promisc_enable = 0;
		hclge_inक्रमm_vf_promisc_info(vport);
	पूर्ण

	vport->vf_info.trusted = new_trusted;

	वापस 0;
पूर्ण

अटल व्योम hclge_reset_vf_rate(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;
	पूर्णांक vf;

	/* reset vf rate to शेष value */
	क्रम (vf = HCLGE_VF_VPORT_START_NUM; vf < hdev->num_alloc_vport; vf++) अणु
		काष्ठा hclge_vport *vport = &hdev->vport[vf];

		vport->vf_info.max_tx_rate = 0;
		ret = hclge_पंचांग_qs_shaper_cfg(vport, vport->vf_info.max_tx_rate);
		अगर (ret)
			dev_err(&hdev->pdev->dev,
				"vf%d failed to reset to default, ret=%d\n",
				vf - HCLGE_VF_VPORT_START_NUM, ret);
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_vf_rate_param_check(काष्ठा hclge_dev *hdev,
				     पूर्णांक min_tx_rate, पूर्णांक max_tx_rate)
अणु
	अगर (min_tx_rate != 0 ||
	    max_tx_rate < 0 || max_tx_rate > hdev->hw.mac.max_speed) अणु
		dev_err(&hdev->pdev->dev,
			"min_tx_rate:%d [0], max_tx_rate:%d [0, %u]\n",
			min_tx_rate, max_tx_rate, hdev->hw.mac.max_speed);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_set_vf_rate(काष्ठा hnae3_handle *handle, पूर्णांक vf,
			     पूर्णांक min_tx_rate, पूर्णांक max_tx_rate, bool क्रमce)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;

	ret = hclge_vf_rate_param_check(hdev, min_tx_rate, max_tx_rate);
	अगर (ret)
		वापस ret;

	vport = hclge_get_vf_vport(hdev, vf);
	अगर (!vport)
		वापस -EINVAL;

	अगर (!क्रमce && max_tx_rate == vport->vf_info.max_tx_rate)
		वापस 0;

	ret = hclge_पंचांग_qs_shaper_cfg(vport, max_tx_rate);
	अगर (ret)
		वापस ret;

	vport->vf_info.max_tx_rate = max_tx_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_resume_vf_rate(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_handle *handle = &hdev->vport->nic;
	काष्ठा hclge_vport *vport;
	पूर्णांक ret;
	पूर्णांक vf;

	/* resume the vf max_tx_rate after reset */
	क्रम (vf = 0; vf < pci_num_vf(hdev->pdev); vf++) अणु
		vport = hclge_get_vf_vport(hdev, vf);
		अगर (!vport)
			वापस -EINVAL;

		/* zero means max rate, after reset, firmware alपढ़ोy set it to
		 * max rate, so just जारी.
		 */
		अगर (!vport->vf_info.max_tx_rate)
			जारी;

		ret = hclge_set_vf_rate(handle, vf, 0,
					vport->vf_info.max_tx_rate, true);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"vf%d failed to resume tx_rate:%u, ret=%d\n",
				vf, vport->vf_info.max_tx_rate, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclge_reset_vport_state(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	पूर्णांक i;

	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		hclge_vport_stop(vport);
		vport++;
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_reset_ae_dev(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclge_dev *hdev = ae_dev->priv;
	काष्ठा pci_dev *pdev = ae_dev->pdev;
	पूर्णांक ret;

	set_bit(HCLGE_STATE_DOWN, &hdev->state);

	hclge_stats_clear(hdev);
	/* NOTE: pf reset needn't to clear or restore pf and vf table entry.
	 * so here should not clean table in memory.
	 */
	अगर (hdev->reset_type == HNAE3_IMP_RESET ||
	    hdev->reset_type == HNAE3_GLOBAL_RESET) अणु
		स_रखो(hdev->vlan_table, 0, माप(hdev->vlan_table));
		स_रखो(hdev->vf_vlan_full, 0, माप(hdev->vf_vlan_full));
		biपंचांगap_set(hdev->vport_config_block, 0, hdev->num_alloc_vport);
		hclge_reset_umv_space(hdev);
	पूर्ण

	ret = hclge_cmd_init(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cmd queue init failed\n");
		वापस ret;
	पूर्ण

	ret = hclge_map_tqp(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Map tqp error, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_mac_init(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Mac init error, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_tp_port_init(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to init tp port, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = hclge_config_tso(hdev, HCLGE_TSO_MSS_MIN, HCLGE_TSO_MSS_MAX);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Enable tso fail, ret =%d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_config_gro(hdev, true);
	अगर (ret)
		वापस ret;

	ret = hclge_init_vlan_config(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "VLAN init fail, ret =%d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_पंचांग_init_hw(hdev, true);
	अगर (ret) अणु
		dev_err(&pdev->dev, "tm init hw fail, ret =%d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_rss_init_hw(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Rss init fail, ret =%d\n", ret);
		वापस ret;
	पूर्ण

	ret = init_mgr_tbl(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to reinit manager table, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_init_fd_config(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "fd table init fail, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	/* Log and clear the hw errors those alपढ़ोy occurred */
	hclge_handle_all_hns_hw_errors(ae_dev);

	/* Re-enable the hw error पूर्णांकerrupts because
	 * the पूर्णांकerrupts get disabled on global reset.
	 */
	ret = hclge_config_nic_hw_error(hdev, true);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"fail(%d) to re-enable NIC hw error interrupts\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (hdev->roce_client) अणु
		ret = hclge_config_rocee_ras_पूर्णांकerrupt(hdev, true);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"fail(%d) to re-enable roce ras interrupts\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	hclge_reset_vport_state(hdev);
	ret = hclge_reset_vport_spoofchk(hdev);
	अगर (ret)
		वापस ret;

	ret = hclge_resume_vf_rate(hdev);
	अगर (ret)
		वापस ret;

	dev_info(&pdev->dev, "Reset done, %s driver initialization finished.\n",
		 HCLGE_DRIVER_NAME);

	वापस 0;
पूर्ण

अटल व्योम hclge_uninit_ae_dev(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclge_dev *hdev = ae_dev->priv;
	काष्ठा hclge_mac *mac = &hdev->hw.mac;

	hclge_reset_vf_rate(hdev);
	hclge_clear_vf_vlan(hdev);
	hclge_misc_affinity_tearकरोwn(hdev);
	hclge_state_uninit(hdev);
	hclge_uninit_mac_table(hdev);
	hclge_del_all_fd_entries(hdev);

	अगर (mac->phydev)
		mdiobus_unरेजिस्टर(mac->mdio_bus);

	/* Disable MISC vector(vector0) */
	hclge_enable_vector(&hdev->misc_vector, false);
	synchronize_irq(hdev->misc_vector.vector_irq);

	/* Disable all hw पूर्णांकerrupts */
	hclge_config_mac_tnl_पूर्णांक(hdev, false);
	hclge_config_nic_hw_error(hdev, false);
	hclge_config_rocee_ras_पूर्णांकerrupt(hdev, false);

	hclge_cmd_uninit(hdev);
	hclge_misc_irq_uninit(hdev);
	hclge_pci_uninit(hdev);
	mutex_destroy(&hdev->vport_lock);
	hclge_uninit_vport_vlan_table(hdev);
	ae_dev->priv = शून्य;
पूर्ण

अटल u32 hclge_get_max_channels(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस min_t(u32, hdev->pf_rss_size_max, vport->alloc_tqps);
पूर्ण

अटल व्योम hclge_get_channels(काष्ठा hnae3_handle *handle,
			       काष्ठा ethtool_channels *ch)
अणु
	ch->max_combined = hclge_get_max_channels(handle);
	ch->other_count = 1;
	ch->max_other = 1;
	ch->combined_count = handle->kinfo.rss_size;
पूर्ण

अटल व्योम hclge_get_tqps_and_rss_info(काष्ठा hnae3_handle *handle,
					u16 *alloc_tqps, u16 *max_rss_size)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	*alloc_tqps = vport->alloc_tqps;
	*max_rss_size = hdev->pf_rss_size_max;
पूर्ण

अटल पूर्णांक hclge_set_channels(काष्ठा hnae3_handle *handle, u32 new_tqps_num,
			      bool rxfh_configured)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	u16 tc_offset[HCLGE_MAX_TC_NUM] = अणु0पूर्ण;
	काष्ठा hclge_dev *hdev = vport->back;
	u16 tc_size[HCLGE_MAX_TC_NUM] = अणु0पूर्ण;
	u16 cur_rss_size = kinfo->rss_size;
	u16 cur_tqps = kinfo->num_tqps;
	u16 tc_valid[HCLGE_MAX_TC_NUM];
	u16 roundup_size;
	u32 *rss_indir;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	kinfo->req_rss_size = new_tqps_num;

	ret = hclge_पंचांग_vport_map_update(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "tm vport map fail, ret =%d\n", ret);
		वापस ret;
	पूर्ण

	roundup_size = roundup_घात_of_two(kinfo->rss_size);
	roundup_size = ilog2(roundup_size);
	/* Set the RSS TC mode according to the new RSS size */
	क्रम (i = 0; i < HCLGE_MAX_TC_NUM; i++) अणु
		tc_valid[i] = 0;

		अगर (!(hdev->hw_tc_map & BIT(i)))
			जारी;

		tc_valid[i] = 1;
		tc_size[i] = roundup_size;
		tc_offset[i] = kinfo->rss_size * i;
	पूर्ण
	ret = hclge_set_rss_tc_mode(hdev, tc_valid, tc_size, tc_offset);
	अगर (ret)
		वापस ret;

	/* RSS indirection table has been configured by user */
	अगर (rxfh_configured)
		जाओ out;

	/* Reinitializes the rss indirect table according to the new RSS size */
	rss_indir = kसुस्मृति(ae_dev->dev_specs.rss_ind_tbl_size, माप(u32),
			    GFP_KERNEL);
	अगर (!rss_indir)
		वापस -ENOMEM;

	क्रम (i = 0; i < ae_dev->dev_specs.rss_ind_tbl_size; i++)
		rss_indir[i] = i % kinfo->rss_size;

	ret = hclge_set_rss(handle, rss_indir, शून्य, 0);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "set rss indir table fail, ret=%d\n",
			ret);

	kमुक्त(rss_indir);

out:
	अगर (!ret)
		dev_info(&hdev->pdev->dev,
			 "Channels changed, rss_size from %u to %u, tqps from %u to %u",
			 cur_rss_size, kinfo->rss_size,
			 cur_tqps, kinfo->rss_size * kinfo->tc_info.num_tc);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_get_regs_num(काष्ठा hclge_dev *hdev, u32 *regs_num_32_bit,
			      u32 *regs_num_64_bit)
अणु
	काष्ठा hclge_desc desc;
	u32 total_num;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_REG_NUM, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Query register number cmd failed, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	*regs_num_32_bit = le32_to_cpu(desc.data[0]);
	*regs_num_64_bit = le32_to_cpu(desc.data[1]);

	total_num = *regs_num_32_bit + *regs_num_64_bit;
	अगर (!total_num)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_32_bit_regs(काष्ठा hclge_dev *hdev, u32 regs_num,
				 व्योम *data)
अणु
#घोषणा HCLGE_32_BIT_REG_RTN_DATANUM 8
#घोषणा HCLGE_32_BIT_DESC_NODATA_LEN 2

	काष्ठा hclge_desc *desc;
	u32 *reg_val = data;
	__le32 *desc_data;
	पूर्णांक nodata_num;
	पूर्णांक cmd_num;
	पूर्णांक i, k, n;
	पूर्णांक ret;

	अगर (regs_num == 0)
		वापस 0;

	nodata_num = HCLGE_32_BIT_DESC_NODATA_LEN;
	cmd_num = DIV_ROUND_UP(regs_num + nodata_num,
			       HCLGE_32_BIT_REG_RTN_DATANUM);
	desc = kसुस्मृति(cmd_num, माप(काष्ठा hclge_desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_QUERY_32_BIT_REG, true);
	ret = hclge_cmd_send(&hdev->hw, desc, cmd_num);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Query 32 bit register cmd failed, ret = %d.\n", ret);
		kमुक्त(desc);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < cmd_num; i++) अणु
		अगर (i == 0) अणु
			desc_data = (__le32 *)(&desc[i].data[0]);
			n = HCLGE_32_BIT_REG_RTN_DATANUM - nodata_num;
		पूर्ण अन्यथा अणु
			desc_data = (__le32 *)(&desc[i]);
			n = HCLGE_32_BIT_REG_RTN_DATANUM;
		पूर्ण
		क्रम (k = 0; k < n; k++) अणु
			*reg_val++ = le32_to_cpu(*desc_data++);

			regs_num--;
			अगर (!regs_num)
				अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(desc);
	वापस 0;
पूर्ण

अटल पूर्णांक hclge_get_64_bit_regs(काष्ठा hclge_dev *hdev, u32 regs_num,
				 व्योम *data)
अणु
#घोषणा HCLGE_64_BIT_REG_RTN_DATANUM 4
#घोषणा HCLGE_64_BIT_DESC_NODATA_LEN 1

	काष्ठा hclge_desc *desc;
	u64 *reg_val = data;
	__le64 *desc_data;
	पूर्णांक nodata_len;
	पूर्णांक cmd_num;
	पूर्णांक i, k, n;
	पूर्णांक ret;

	अगर (regs_num == 0)
		वापस 0;

	nodata_len = HCLGE_64_BIT_DESC_NODATA_LEN;
	cmd_num = DIV_ROUND_UP(regs_num + nodata_len,
			       HCLGE_64_BIT_REG_RTN_DATANUM);
	desc = kसुस्मृति(cmd_num, माप(काष्ठा hclge_desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_QUERY_64_BIT_REG, true);
	ret = hclge_cmd_send(&hdev->hw, desc, cmd_num);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Query 64 bit register cmd failed, ret = %d.\n", ret);
		kमुक्त(desc);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < cmd_num; i++) अणु
		अगर (i == 0) अणु
			desc_data = (__le64 *)(&desc[i].data[0]);
			n = HCLGE_64_BIT_REG_RTN_DATANUM - nodata_len;
		पूर्ण अन्यथा अणु
			desc_data = (__le64 *)(&desc[i]);
			n = HCLGE_64_BIT_REG_RTN_DATANUM;
		पूर्ण
		क्रम (k = 0; k < n; k++) अणु
			*reg_val++ = le64_to_cpu(*desc_data++);

			regs_num--;
			अगर (!regs_num)
				अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(desc);
	वापस 0;
पूर्ण

#घोषणा MAX_SEPARATE_NUM	4
#घोषणा SEPARATOR_VALUE		0xFDFCFBFA
#घोषणा REG_NUM_PER_LINE	4
#घोषणा REG_LEN_PER_LINE	(REG_NUM_PER_LINE * माप(u32))
#घोषणा REG_SEPARATOR_LINE	1
#घोषणा REG_NUM_REMAIN_MASK	3

पूर्णांक hclge_query_bd_num_cmd_send(काष्ठा hclge_dev *hdev, काष्ठा hclge_desc *desc)
अणु
	पूर्णांक i;

	/* initialize command BD except the last one */
	क्रम (i = 0; i < HCLGE_GET_DFX_REG_TYPE_CNT - 1; i++) अणु
		hclge_cmd_setup_basic_desc(&desc[i], HCLGE_OPC_DFX_BD_NUM,
					   true);
		desc[i].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	पूर्ण

	/* initialize the last command BD */
	hclge_cmd_setup_basic_desc(&desc[i], HCLGE_OPC_DFX_BD_NUM, true);

	वापस hclge_cmd_send(&hdev->hw, desc, HCLGE_GET_DFX_REG_TYPE_CNT);
पूर्ण

अटल पूर्णांक hclge_get_dfx_reg_bd_num(काष्ठा hclge_dev *hdev,
				    पूर्णांक *bd_num_list,
				    u32 type_num)
अणु
	u32 entries_per_desc, desc_index, index, offset, i;
	काष्ठा hclge_desc desc[HCLGE_GET_DFX_REG_TYPE_CNT];
	पूर्णांक ret;

	ret = hclge_query_bd_num_cmd_send(hdev, desc);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get dfx bd num fail, status is %d.\n", ret);
		वापस ret;
	पूर्ण

	entries_per_desc = ARRAY_SIZE(desc[0].data);
	क्रम (i = 0; i < type_num; i++) अणु
		offset = hclge_dfx_bd_offset_list[i];
		index = offset % entries_per_desc;
		desc_index = offset / entries_per_desc;
		bd_num_list[i] = le32_to_cpu(desc[desc_index].data[index]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_dfx_reg_cmd_send(काष्ठा hclge_dev *hdev,
				  काष्ठा hclge_desc *desc_src, पूर्णांक bd_num,
				  क्रमागत hclge_opcode_type cmd)
अणु
	काष्ठा hclge_desc *desc = desc_src;
	पूर्णांक i, ret;

	hclge_cmd_setup_basic_desc(desc, cmd, true);
	क्रम (i = 0; i < bd_num - 1; i++) अणु
		desc->flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		desc++;
		hclge_cmd_setup_basic_desc(desc, cmd, true);
	पूर्ण

	desc = desc_src;
	ret = hclge_cmd_send(&hdev->hw, desc, bd_num);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"Query dfx reg cmd(0x%x) send fail, status is %d.\n",
			cmd, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_dfx_reg_fetch_data(काष्ठा hclge_desc *desc_src, पूर्णांक bd_num,
				    व्योम *data)
अणु
	पूर्णांक entries_per_desc, reg_num, separator_num, desc_index, index, i;
	काष्ठा hclge_desc *desc = desc_src;
	u32 *reg = data;

	entries_per_desc = ARRAY_SIZE(desc->data);
	reg_num = entries_per_desc * bd_num;
	separator_num = REG_NUM_PER_LINE - (reg_num & REG_NUM_REMAIN_MASK);
	क्रम (i = 0; i < reg_num; i++) अणु
		index = i % entries_per_desc;
		desc_index = i / entries_per_desc;
		*reg++ = le32_to_cpu(desc[desc_index].data[index]);
	पूर्ण
	क्रम (i = 0; i < separator_num; i++)
		*reg++ = SEPARATOR_VALUE;

	वापस reg_num + separator_num;
पूर्ण

अटल पूर्णांक hclge_get_dfx_reg_len(काष्ठा hclge_dev *hdev, पूर्णांक *len)
अणु
	u32 dfx_reg_type_num = ARRAY_SIZE(hclge_dfx_bd_offset_list);
	पूर्णांक data_len_per_desc, bd_num, i;
	पूर्णांक *bd_num_list;
	u32 data_len;
	पूर्णांक ret;

	bd_num_list = kसुस्मृति(dfx_reg_type_num, माप(पूर्णांक), GFP_KERNEL);
	अगर (!bd_num_list)
		वापस -ENOMEM;

	ret = hclge_get_dfx_reg_bd_num(hdev, bd_num_list, dfx_reg_type_num);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get dfx reg bd num fail, status is %d.\n", ret);
		जाओ out;
	पूर्ण

	data_len_per_desc = माप_field(काष्ठा hclge_desc, data);
	*len = 0;
	क्रम (i = 0; i < dfx_reg_type_num; i++) अणु
		bd_num = bd_num_list[i];
		data_len = data_len_per_desc * bd_num;
		*len += (data_len / REG_LEN_PER_LINE + 1) * REG_LEN_PER_LINE;
	पूर्ण

out:
	kमुक्त(bd_num_list);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_get_dfx_reg(काष्ठा hclge_dev *hdev, व्योम *data)
अणु
	u32 dfx_reg_type_num = ARRAY_SIZE(hclge_dfx_bd_offset_list);
	पूर्णांक bd_num, bd_num_max, buf_len, i;
	काष्ठा hclge_desc *desc_src;
	पूर्णांक *bd_num_list;
	u32 *reg = data;
	पूर्णांक ret;

	bd_num_list = kसुस्मृति(dfx_reg_type_num, माप(पूर्णांक), GFP_KERNEL);
	अगर (!bd_num_list)
		वापस -ENOMEM;

	ret = hclge_get_dfx_reg_bd_num(hdev, bd_num_list, dfx_reg_type_num);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get dfx reg bd num fail, status is %d.\n", ret);
		जाओ out;
	पूर्ण

	bd_num_max = bd_num_list[0];
	क्रम (i = 1; i < dfx_reg_type_num; i++)
		bd_num_max = max_t(पूर्णांक, bd_num_max, bd_num_list[i]);

	buf_len = माप(*desc_src) * bd_num_max;
	desc_src = kzalloc(buf_len, GFP_KERNEL);
	अगर (!desc_src) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < dfx_reg_type_num; i++) अणु
		bd_num = bd_num_list[i];
		ret = hclge_dfx_reg_cmd_send(hdev, desc_src, bd_num,
					     hclge_dfx_reg_opcode_list[i]);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"Get dfx reg fail, status is %d.\n", ret);
			अवरोध;
		पूर्ण

		reg += hclge_dfx_reg_fetch_data(desc_src, bd_num, reg);
	पूर्ण

	kमुक्त(desc_src);
out:
	kमुक्त(bd_num_list);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_fetch_pf_reg(काष्ठा hclge_dev *hdev, व्योम *data,
			      काष्ठा hnae3_knic_निजी_info *kinfo)
अणु
#घोषणा HCLGE_RING_REG_OFFSET		0x200
#घोषणा HCLGE_RING_INT_REG_OFFSET	0x4

	पूर्णांक i, j, reg_num, separator_num;
	पूर्णांक data_num_sum;
	u32 *reg = data;

	/* fetching per-PF रेजिस्टरs valus from PF PCIe रेजिस्टर space */
	reg_num = ARRAY_SIZE(cmdq_reg_addr_list);
	separator_num = MAX_SEPARATE_NUM - (reg_num & REG_NUM_REMAIN_MASK);
	क्रम (i = 0; i < reg_num; i++)
		*reg++ = hclge_पढ़ो_dev(&hdev->hw, cmdq_reg_addr_list[i]);
	क्रम (i = 0; i < separator_num; i++)
		*reg++ = SEPARATOR_VALUE;
	data_num_sum = reg_num + separator_num;

	reg_num = ARRAY_SIZE(common_reg_addr_list);
	separator_num = MAX_SEPARATE_NUM - (reg_num & REG_NUM_REMAIN_MASK);
	क्रम (i = 0; i < reg_num; i++)
		*reg++ = hclge_पढ़ो_dev(&hdev->hw, common_reg_addr_list[i]);
	क्रम (i = 0; i < separator_num; i++)
		*reg++ = SEPARATOR_VALUE;
	data_num_sum += reg_num + separator_num;

	reg_num = ARRAY_SIZE(ring_reg_addr_list);
	separator_num = MAX_SEPARATE_NUM - (reg_num & REG_NUM_REMAIN_MASK);
	क्रम (j = 0; j < kinfo->num_tqps; j++) अणु
		क्रम (i = 0; i < reg_num; i++)
			*reg++ = hclge_पढ़ो_dev(&hdev->hw,
						ring_reg_addr_list[i] +
						HCLGE_RING_REG_OFFSET * j);
		क्रम (i = 0; i < separator_num; i++)
			*reg++ = SEPARATOR_VALUE;
	पूर्ण
	data_num_sum += (reg_num + separator_num) * kinfo->num_tqps;

	reg_num = ARRAY_SIZE(tqp_पूर्णांकr_reg_addr_list);
	separator_num = MAX_SEPARATE_NUM - (reg_num & REG_NUM_REMAIN_MASK);
	क्रम (j = 0; j < hdev->num_msi_used - 1; j++) अणु
		क्रम (i = 0; i < reg_num; i++)
			*reg++ = hclge_पढ़ो_dev(&hdev->hw,
						tqp_पूर्णांकr_reg_addr_list[i] +
						HCLGE_RING_INT_REG_OFFSET * j);
		क्रम (i = 0; i < separator_num; i++)
			*reg++ = SEPARATOR_VALUE;
	पूर्ण
	data_num_sum += (reg_num + separator_num) * (hdev->num_msi_used - 1);

	वापस data_num_sum;
पूर्ण

अटल पूर्णांक hclge_get_regs_len(काष्ठा hnae3_handle *handle)
अणु
	पूर्णांक cmdq_lines, common_lines, ring_lines, tqp_पूर्णांकr_lines;
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक regs_num_32_bit, regs_num_64_bit, dfx_regs_len;
	पूर्णांक regs_lines_32_bit, regs_lines_64_bit;
	पूर्णांक ret;

	ret = hclge_get_regs_num(hdev, &regs_num_32_bit, &regs_num_64_bit);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get register number failed, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_get_dfx_reg_len(hdev, &dfx_regs_len);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get dfx reg len failed, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	cmdq_lines = माप(cmdq_reg_addr_list) / REG_LEN_PER_LINE +
		REG_SEPARATOR_LINE;
	common_lines = माप(common_reg_addr_list) / REG_LEN_PER_LINE +
		REG_SEPARATOR_LINE;
	ring_lines = माप(ring_reg_addr_list) / REG_LEN_PER_LINE +
		REG_SEPARATOR_LINE;
	tqp_पूर्णांकr_lines = माप(tqp_पूर्णांकr_reg_addr_list) / REG_LEN_PER_LINE +
		REG_SEPARATOR_LINE;
	regs_lines_32_bit = regs_num_32_bit * माप(u32) / REG_LEN_PER_LINE +
		REG_SEPARATOR_LINE;
	regs_lines_64_bit = regs_num_64_bit * माप(u64) / REG_LEN_PER_LINE +
		REG_SEPARATOR_LINE;

	वापस (cmdq_lines + common_lines + ring_lines * kinfo->num_tqps +
		tqp_पूर्णांकr_lines * (hdev->num_msi_used - 1) + regs_lines_32_bit +
		regs_lines_64_bit) * REG_LEN_PER_LINE + dfx_regs_len;
पूर्ण

अटल व्योम hclge_get_regs(काष्ठा hnae3_handle *handle, u32 *version,
			   व्योम *data)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	u32 regs_num_32_bit, regs_num_64_bit;
	पूर्णांक i, reg_num, separator_num, ret;
	u32 *reg = data;

	*version = hdev->fw_version;

	ret = hclge_get_regs_num(hdev, &regs_num_32_bit, &regs_num_64_bit);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get register number failed, ret = %d.\n", ret);
		वापस;
	पूर्ण

	reg += hclge_fetch_pf_reg(hdev, reg, kinfo);

	ret = hclge_get_32_bit_regs(hdev, regs_num_32_bit, reg);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get 32 bit register failed, ret = %d.\n", ret);
		वापस;
	पूर्ण
	reg_num = regs_num_32_bit;
	reg += reg_num;
	separator_num = MAX_SEPARATE_NUM - (reg_num & REG_NUM_REMAIN_MASK);
	क्रम (i = 0; i < separator_num; i++)
		*reg++ = SEPARATOR_VALUE;

	ret = hclge_get_64_bit_regs(hdev, regs_num_64_bit, reg);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Get 64 bit register failed, ret = %d.\n", ret);
		वापस;
	पूर्ण
	reg_num = regs_num_64_bit * 2;
	reg += reg_num;
	separator_num = MAX_SEPARATE_NUM - (reg_num & REG_NUM_REMAIN_MASK);
	क्रम (i = 0; i < separator_num; i++)
		*reg++ = SEPARATOR_VALUE;

	ret = hclge_get_dfx_reg(hdev, reg);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"Get dfx register failed, ret = %d.\n", ret);
पूर्ण

अटल पूर्णांक hclge_set_led_status(काष्ठा hclge_dev *hdev, u8 locate_led_status)
अणु
	काष्ठा hclge_set_led_state_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_LED_STATUS_CFG, false);

	req = (काष्ठा hclge_set_led_state_cmd *)desc.data;
	hnae3_set_field(req->locate_led_config, HCLGE_LED_LOCATE_STATE_M,
			HCLGE_LED_LOCATE_STATE_S, locate_led_status);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"Send set led state cmd error, ret =%d\n", ret);

	वापस ret;
पूर्ण

क्रमागत hclge_led_status अणु
	HCLGE_LED_OFF,
	HCLGE_LED_ON,
	HCLGE_LED_NO_CHANGE = 0xFF,
पूर्ण;

अटल पूर्णांक hclge_set_led_id(काष्ठा hnae3_handle *handle,
			    क्रमागत ethtool_phys_id_state status)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	चयन (status) अणु
	हाल ETHTOOL_ID_ACTIVE:
		वापस hclge_set_led_status(hdev, HCLGE_LED_ON);
	हाल ETHTOOL_ID_INACTIVE:
		वापस hclge_set_led_status(hdev, HCLGE_LED_OFF);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम hclge_get_link_mode(काष्ठा hnae3_handle *handle,
				अचिन्हित दीर्घ *supported,
				अचिन्हित दीर्घ *advertising)
अणु
	अचिन्हित पूर्णांक size = BITS_TO_LONGS(__ETHTOOL_LINK_MODE_MASK_NBITS);
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	अचिन्हित पूर्णांक idx = 0;

	क्रम (; idx < size; idx++) अणु
		supported[idx] = hdev->hw.mac.supported[idx];
		advertising[idx] = hdev->hw.mac.advertising[idx];
	पूर्ण
पूर्ण

अटल पूर्णांक hclge_gro_en(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;

	वापस hclge_config_gro(hdev, enable);
पूर्ण

अटल व्योम hclge_sync_promisc_mode(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = &hdev->vport[0];
	काष्ठा hnae3_handle *handle = &vport->nic;
	u8 पंचांगp_flags;
	पूर्णांक ret;

	अगर (vport->last_promisc_flags != vport->overflow_promisc_flags) अणु
		set_bit(HCLGE_STATE_PROMISC_CHANGED, &hdev->state);
		vport->last_promisc_flags = vport->overflow_promisc_flags;
	पूर्ण

	अगर (test_bit(HCLGE_STATE_PROMISC_CHANGED, &hdev->state)) अणु
		पंचांगp_flags = handle->netdev_flags | vport->last_promisc_flags;
		ret = hclge_set_promisc_mode(handle, पंचांगp_flags & HNAE3_UPE,
					     पंचांगp_flags & HNAE3_MPE);
		अगर (!ret) अणु
			clear_bit(HCLGE_STATE_PROMISC_CHANGED, &hdev->state);
			hclge_enable_vlan_filter(handle,
						 पंचांगp_flags & HNAE3_VLAN_FLTR);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool hclge_module_existed(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_desc desc;
	u32 existed;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_GET_SFP_EXIST, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get SFP exist state, ret = %d\n", ret);
		वापस false;
	पूर्ण

	existed = le32_to_cpu(desc.data[0]);

	वापस existed != 0;
पूर्ण

/* need 6 bds(total 140 bytes) in one पढ़ोing
 * वापस the number of bytes actually पढ़ो, 0 means पढ़ो failed.
 */
अटल u16 hclge_get_sfp_eeprom_info(काष्ठा hclge_dev *hdev, u32 offset,
				     u32 len, u8 *data)
अणु
	काष्ठा hclge_desc desc[HCLGE_SFP_INFO_CMD_NUM];
	काष्ठा hclge_sfp_info_bd0_cmd *sfp_info_bd0;
	u16 पढ़ो_len;
	u16 copy_len;
	पूर्णांक ret;
	पूर्णांक i;

	/* setup all 6 bds to पढ़ो module eeprom info. */
	क्रम (i = 0; i < HCLGE_SFP_INFO_CMD_NUM; i++) अणु
		hclge_cmd_setup_basic_desc(&desc[i], HCLGE_OPC_GET_SFP_EEPROM,
					   true);

		/* bd0~bd4 need next flag */
		अगर (i < HCLGE_SFP_INFO_CMD_NUM - 1)
			desc[i].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	पूर्ण

	/* setup bd0, this bd contains offset and पढ़ो length. */
	sfp_info_bd0 = (काष्ठा hclge_sfp_info_bd0_cmd *)desc[0].data;
	sfp_info_bd0->offset = cpu_to_le16((u16)offset);
	पढ़ो_len = min_t(u16, len, HCLGE_SFP_INFO_MAX_LEN);
	sfp_info_bd0->पढ़ो_len = cpu_to_le16(पढ़ो_len);

	ret = hclge_cmd_send(&hdev->hw, desc, i);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get SFP eeprom info, ret = %d\n", ret);
		वापस 0;
	पूर्ण

	/* copy sfp info from bd0 to out buffer. */
	copy_len = min_t(u16, len, HCLGE_SFP_INFO_BD0_LEN);
	स_नकल(data, sfp_info_bd0->data, copy_len);
	पढ़ो_len = copy_len;

	/* copy sfp info from bd1~bd5 to out buffer अगर needed. */
	क्रम (i = 1; i < HCLGE_SFP_INFO_CMD_NUM; i++) अणु
		अगर (पढ़ो_len >= len)
			वापस पढ़ो_len;

		copy_len = min_t(u16, len - पढ़ो_len, HCLGE_SFP_INFO_BDX_LEN);
		स_नकल(data + पढ़ो_len, desc[i].data, copy_len);
		पढ़ो_len += copy_len;
	पूर्ण

	वापस पढ़ो_len;
पूर्ण

अटल पूर्णांक hclge_get_module_eeprom(काष्ठा hnae3_handle *handle, u32 offset,
				   u32 len, u8 *data)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	u32 पढ़ो_len = 0;
	u16 data_len;

	अगर (hdev->hw.mac.media_type != HNAE3_MEDIA_TYPE_FIBER)
		वापस -EOPNOTSUPP;

	अगर (!hclge_module_existed(hdev))
		वापस -ENXIO;

	जबतक (पढ़ो_len < len) अणु
		data_len = hclge_get_sfp_eeprom_info(hdev,
						     offset + पढ़ो_len,
						     len - पढ़ो_len,
						     data + पढ़ो_len);
		अगर (!data_len)
			वापस -EIO;

		पढ़ो_len += data_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hnae3_ae_ops hclge_ops = अणु
	.init_ae_dev = hclge_init_ae_dev,
	.uninit_ae_dev = hclge_uninit_ae_dev,
	.reset_prepare = hclge_reset_prepare_general,
	.reset_करोne = hclge_reset_करोne,
	.init_client_instance = hclge_init_client_instance,
	.uninit_client_instance = hclge_uninit_client_instance,
	.map_ring_to_vector = hclge_map_ring_to_vector,
	.unmap_ring_from_vector = hclge_unmap_ring_frm_vector,
	.get_vector = hclge_get_vector,
	.put_vector = hclge_put_vector,
	.set_promisc_mode = hclge_set_promisc_mode,
	.request_update_promisc_mode = hclge_request_update_promisc_mode,
	.set_loopback = hclge_set_loopback,
	.start = hclge_ae_start,
	.stop = hclge_ae_stop,
	.client_start = hclge_client_start,
	.client_stop = hclge_client_stop,
	.get_status = hclge_get_status,
	.get_ksettings_an_result = hclge_get_ksettings_an_result,
	.cfg_mac_speed_dup_h = hclge_cfg_mac_speed_dup_h,
	.get_media_type = hclge_get_media_type,
	.check_port_speed = hclge_check_port_speed,
	.get_fec = hclge_get_fec,
	.set_fec = hclge_set_fec,
	.get_rss_key_size = hclge_get_rss_key_size,
	.get_rss = hclge_get_rss,
	.set_rss = hclge_set_rss,
	.set_rss_tuple = hclge_set_rss_tuple,
	.get_rss_tuple = hclge_get_rss_tuple,
	.get_tc_size = hclge_get_tc_size,
	.get_mac_addr = hclge_get_mac_addr,
	.set_mac_addr = hclge_set_mac_addr,
	.करो_ioctl = hclge_करो_ioctl,
	.add_uc_addr = hclge_add_uc_addr,
	.rm_uc_addr = hclge_rm_uc_addr,
	.add_mc_addr = hclge_add_mc_addr,
	.rm_mc_addr = hclge_rm_mc_addr,
	.set_स्वतःneg = hclge_set_स्वतःneg,
	.get_स्वतःneg = hclge_get_स्वतःneg,
	.restart_स्वतःneg = hclge_restart_स्वतःneg,
	.halt_स्वतःneg = hclge_halt_स्वतःneg,
	.get_छोड़ोparam = hclge_get_छोड़ोparam,
	.set_छोड़ोparam = hclge_set_छोड़ोparam,
	.set_mtu = hclge_set_mtu,
	.reset_queue = hclge_reset_tqp,
	.get_stats = hclge_get_stats,
	.get_mac_stats = hclge_get_mac_stat,
	.update_stats = hclge_update_stats,
	.get_strings = hclge_get_strings,
	.get_sset_count = hclge_get_sset_count,
	.get_fw_version = hclge_get_fw_version,
	.get_mdix_mode = hclge_get_mdix_mode,
	.enable_vlan_filter = hclge_enable_vlan_filter,
	.set_vlan_filter = hclge_set_vlan_filter,
	.set_vf_vlan_filter = hclge_set_vf_vlan_filter,
	.enable_hw_strip_rxvtag = hclge_en_hw_strip_rxvtag,
	.reset_event = hclge_reset_event,
	.get_reset_level = hclge_get_reset_level,
	.set_शेष_reset_request = hclge_set_def_reset_request,
	.get_tqps_and_rss_info = hclge_get_tqps_and_rss_info,
	.set_channels = hclge_set_channels,
	.get_channels = hclge_get_channels,
	.get_regs_len = hclge_get_regs_len,
	.get_regs = hclge_get_regs,
	.set_led_id = hclge_set_led_id,
	.get_link_mode = hclge_get_link_mode,
	.add_fd_entry = hclge_add_fd_entry,
	.del_fd_entry = hclge_del_fd_entry,
	.get_fd_rule_cnt = hclge_get_fd_rule_cnt,
	.get_fd_rule_info = hclge_get_fd_rule_info,
	.get_fd_all_rules = hclge_get_all_rules,
	.enable_fd = hclge_enable_fd,
	.add_arfs_entry = hclge_add_fd_entry_by_arfs,
	.dbg_run_cmd = hclge_dbg_run_cmd,
	.dbg_पढ़ो_cmd = hclge_dbg_पढ़ो_cmd,
	.handle_hw_ras_error = hclge_handle_hw_ras_error,
	.get_hw_reset_stat = hclge_get_hw_reset_stat,
	.ae_dev_resetting = hclge_ae_dev_resetting,
	.ae_dev_reset_cnt = hclge_ae_dev_reset_cnt,
	.set_gro_en = hclge_gro_en,
	.get_global_queue_id = hclge_covert_handle_qid_global,
	.set_समयr_task = hclge_set_समयr_task,
	.mac_connect_phy = hclge_mac_connect_phy,
	.mac_disconnect_phy = hclge_mac_disconnect_phy,
	.get_vf_config = hclge_get_vf_config,
	.set_vf_link_state = hclge_set_vf_link_state,
	.set_vf_spoofchk = hclge_set_vf_spoofchk,
	.set_vf_trust = hclge_set_vf_trust,
	.set_vf_rate = hclge_set_vf_rate,
	.set_vf_mac = hclge_set_vf_mac,
	.get_module_eeprom = hclge_get_module_eeprom,
	.get_cmdq_stat = hclge_get_cmdq_stat,
	.add_cls_flower = hclge_add_cls_flower,
	.del_cls_flower = hclge_del_cls_flower,
	.cls_flower_active = hclge_is_cls_flower_active,
	.get_phy_link_ksettings = hclge_get_phy_link_ksettings,
	.set_phy_link_ksettings = hclge_set_phy_link_ksettings,
पूर्ण;

अटल काष्ठा hnae3_ae_algo ae_algo = अणु
	.ops = &hclge_ops,
	.pdev_id_table = ae_algo_pci_tbl,
पूर्ण;

अटल पूर्णांक hclge_init(व्योम)
अणु
	pr_info("%s is initializing\n", HCLGE_NAME);

	hclge_wq = alloc_workqueue("%s", 0, 0, HCLGE_NAME);
	अगर (!hclge_wq) अणु
		pr_err("%s: failed to create workqueue\n", HCLGE_NAME);
		वापस -ENOMEM;
	पूर्ण

	hnae3_रेजिस्टर_ae_algo(&ae_algo);

	वापस 0;
पूर्ण

अटल व्योम hclge_निकास(व्योम)
अणु
	hnae3_unरेजिस्टर_ae_algo(&ae_algo);
	destroy_workqueue(hclge_wq);
पूर्ण
module_init(hclge_init);
module_निकास(hclge_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huawei Tech. Co., Ltd.");
MODULE_DESCRIPTION("HCLGE Driver");
MODULE_VERSION(HCLGE_MOD_VERSION);
