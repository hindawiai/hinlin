<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2018-2019 Hisilicon Limited. */

#अगर_अघोषित __HCLGE_DEBUGFS_H
#घोषणा __HCLGE_DEBUGFS_H

#समावेश <linux/etherdevice.h>
#समावेश "hclge_cmd.h"

#घोषणा HCLGE_DBG_BUF_LEN	   256
#घोषणा HCLGE_DBG_MNG_TBL_MAX	   64

#घोषणा HCLGE_DBG_MNG_VLAN_MASK_B  BIT(0)
#घोषणा HCLGE_DBG_MNG_MAC_MASK_B   BIT(1)
#घोषणा HCLGE_DBG_MNG_ETHER_MASK_B BIT(2)
#घोषणा HCLGE_DBG_MNG_E_TYPE_B	   BIT(11)
#घोषणा HCLGE_DBG_MNG_DROP_B	   BIT(13)
#घोषणा HCLGE_DBG_MNG_VLAN_TAG	   0x0FFF
#घोषणा HCLGE_DBG_MNG_PF_ID	   0x0007
#घोषणा HCLGE_DBG_MNG_VF_ID	   0x00FF

/* Get DFX BD number offset */
#घोषणा HCLGE_DBG_DFX_BIOS_OFFSET  1
#घोषणा HCLGE_DBG_DFX_SSU_0_OFFSET 2
#घोषणा HCLGE_DBG_DFX_SSU_1_OFFSET 3
#घोषणा HCLGE_DBG_DFX_IGU_OFFSET   4
#घोषणा HCLGE_DBG_DFX_RPU_0_OFFSET 5

#घोषणा HCLGE_DBG_DFX_RPU_1_OFFSET 6
#घोषणा HCLGE_DBG_DFX_NCSI_OFFSET  7
#घोषणा HCLGE_DBG_DFX_RTC_OFFSET   8
#घोषणा HCLGE_DBG_DFX_PPP_OFFSET   9
#घोषणा HCLGE_DBG_DFX_RCB_OFFSET   10
#घोषणा HCLGE_DBG_DFX_TQP_OFFSET   11

#घोषणा HCLGE_DBG_DFX_SSU_2_OFFSET 12

काष्ठा hclge_qos_pri_map_cmd अणु
	u8 pri0_tc  : 4,
	   pri1_tc  : 4;
	u8 pri2_tc  : 4,
	   pri3_tc  : 4;
	u8 pri4_tc  : 4,
	   pri5_tc  : 4;
	u8 pri6_tc  : 4,
	   pri7_tc  : 4;
	u8 vlan_pri : 4,
	   rev	    : 4;
पूर्ण;

काष्ठा hclge_dbg_biपंचांगap_cmd अणु
	जोड़ अणु
		u8 biपंचांगap;
		काष्ठा अणु
			u8 bit0 : 1,
			   bit1 : 1,
			   bit2 : 1,
			   bit3 : 1,
			   bit4 : 1,
			   bit5 : 1,
			   bit6 : 1,
			   bit7 : 1;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा hclge_dbg_reg_common_msg अणु
	पूर्णांक msg_num;
	पूर्णांक offset;
	क्रमागत hclge_opcode_type cmd;
पूर्ण;

#घोषणा	HCLGE_DBG_MAX_DFX_MSG_LEN	60
काष्ठा hclge_dbg_dfx_message अणु
	पूर्णांक flag;
	अक्षर message[HCLGE_DBG_MAX_DFX_MSG_LEN];
पूर्ण;

#घोषणा HCLGE_DBG_MAC_REG_TYPE_LEN	32
काष्ठा hclge_dbg_reg_type_info अणु
	स्थिर अक्षर *reg_type;
	स्थिर काष्ठा hclge_dbg_dfx_message *dfx_msg;
	काष्ठा hclge_dbg_reg_common_msg reg_msg;
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_bios_common_reg[] = अणु
	अणुfalse, "Reserved"पूर्ण,
	अणुtrue,	"BP_CPU_STATE"पूर्ण,
	अणुtrue,	"DFX_MSIX_INFO_NIC_0"पूर्ण,
	अणुtrue,	"DFX_MSIX_INFO_NIC_1"पूर्ण,
	अणुtrue,	"DFX_MSIX_INFO_NIC_2"पूर्ण,
	अणुtrue,	"DFX_MSIX_INFO_NIC_3"पूर्ण,

	अणुtrue,	"DFX_MSIX_INFO_ROC_0"पूर्ण,
	अणुtrue,	"DFX_MSIX_INFO_ROC_1"पूर्ण,
	अणुtrue,	"DFX_MSIX_INFO_ROC_2"पूर्ण,
	अणुtrue,	"DFX_MSIX_INFO_ROC_3"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_ssu_reg_0[] = अणु
	अणुfalse, "Reserved"पूर्ण,
	अणुtrue,	"SSU_ETS_PORT_STATUS"पूर्ण,
	अणुtrue,	"SSU_ETS_TCG_STATUS"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुtrue,	"SSU_BP_STATUS_0"पूर्ण,

	अणुtrue,	"SSU_BP_STATUS_1"पूर्ण,
	अणुtrue,	"SSU_BP_STATUS_2"पूर्ण,
	अणुtrue,	"SSU_BP_STATUS_3"पूर्ण,
	अणुtrue,	"SSU_BP_STATUS_4"पूर्ण,
	अणुtrue,	"SSU_BP_STATUS_5"पूर्ण,
	अणुtrue,	"SSU_MAC_TX_PFC_IND"पूर्ण,

	अणुtrue,	"MAC_SSU_RX_PFC_IND"पूर्ण,
	अणुtrue,	"BTMP_AGEING_ST_B0"पूर्ण,
	अणुtrue,	"BTMP_AGEING_ST_B1"पूर्ण,
	अणुtrue,	"BTMP_AGEING_ST_B2"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,

	अणुtrue,	"FULL_DROP_NUM"पूर्ण,
	अणुtrue,	"PART_DROP_NUM"पूर्ण,
	अणुtrue,	"PPP_KEY_DROP_NUM"पूर्ण,
	अणुtrue,	"PPP_RLT_DROP_NUM"पूर्ण,
	अणुtrue,	"LO_PRI_UNICAST_RLT_DROP_NUM"पूर्ण,
	अणुtrue,	"HI_PRI_MULTICAST_RLT_DROP_NUM"पूर्ण,

	अणुtrue,	"LO_PRI_MULTICAST_RLT_DROP_NUM"पूर्ण,
	अणुtrue,	"NCSI_PACKET_CURR_BUFFER_CNT"पूर्ण,
	अणुtrue,	"BTMP_AGEING_RLS_CNT_BANK0"पूर्ण,
	अणुtrue,	"BTMP_AGEING_RLS_CNT_BANK1"पूर्ण,
	अणुtrue,	"BTMP_AGEING_RLS_CNT_BANK2"पूर्ण,
	अणुtrue,	"SSU_MB_RD_RLT_DROP_CNT"पूर्ण,

	अणुtrue,	"SSU_PPP_MAC_KEY_NUM_L"पूर्ण,
	अणुtrue,	"SSU_PPP_MAC_KEY_NUM_H"पूर्ण,
	अणुtrue,	"SSU_PPP_HOST_KEY_NUM_L"पूर्ण,
	अणुtrue,	"SSU_PPP_HOST_KEY_NUM_H"पूर्ण,
	अणुtrue,	"PPP_SSU_MAC_RLT_NUM_L"पूर्ण,
	अणुtrue,	"PPP_SSU_MAC_RLT_NUM_H"पूर्ण,

	अणुtrue,	"PPP_SSU_HOST_RLT_NUM_L"पूर्ण,
	अणुtrue,	"PPP_SSU_HOST_RLT_NUM_H"पूर्ण,
	अणुtrue,	"NCSI_RX_PACKET_IN_CNT_L"पूर्ण,
	अणुtrue,	"NCSI_RX_PACKET_IN_CNT_H"पूर्ण,
	अणुtrue,	"NCSI_TX_PACKET_OUT_CNT_L"पूर्ण,
	अणुtrue,	"NCSI_TX_PACKET_OUT_CNT_H"पूर्ण,

	अणुtrue,	"SSU_KEY_DROP_NUM"पूर्ण,
	अणुtrue,	"MB_UNCOPY_NUM"पूर्ण,
	अणुtrue,	"RX_OQ_DROP_PKT_CNT"पूर्ण,
	अणुtrue,	"TX_OQ_DROP_PKT_CNT"पूर्ण,
	अणुtrue,	"BANK_UNBALANCE_DROP_CNT"पूर्ण,
	अणुtrue,	"BANK_UNBALANCE_RX_DROP_CNT"पूर्ण,

	अणुtrue,	"NIC_L2_ERR_DROP_PKT_CNT"पूर्ण,
	अणुtrue,	"ROC_L2_ERR_DROP_PKT_CNT"पूर्ण,
	अणुtrue,	"NIC_L2_ERR_DROP_PKT_CNT_RX"पूर्ण,
	अणुtrue,	"ROC_L2_ERR_DROP_PKT_CNT_RX"पूर्ण,
	अणुtrue,	"RX_OQ_GLB_DROP_PKT_CNT"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,

	अणुtrue,	"LO_PRI_UNICAST_CUR_CNT"पूर्ण,
	अणुtrue,	"HI_PRI_MULTICAST_CUR_CNT"पूर्ण,
	अणुtrue,	"LO_PRI_MULTICAST_CUR_CNT"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_ssu_reg_1[] = अणु
	अणुtrue,	"prt_id"पूर्ण,
	अणुtrue,	"PACKET_TC_CURR_BUFFER_CNT_0"पूर्ण,
	अणुtrue,	"PACKET_TC_CURR_BUFFER_CNT_1"पूर्ण,
	अणुtrue,	"PACKET_TC_CURR_BUFFER_CNT_2"पूर्ण,
	अणुtrue,	"PACKET_TC_CURR_BUFFER_CNT_3"पूर्ण,
	अणुtrue,	"PACKET_TC_CURR_BUFFER_CNT_4"पूर्ण,

	अणुtrue,	"PACKET_TC_CURR_BUFFER_CNT_5"पूर्ण,
	अणुtrue,	"PACKET_TC_CURR_BUFFER_CNT_6"पूर्ण,
	अणुtrue,	"PACKET_TC_CURR_BUFFER_CNT_7"पूर्ण,
	अणुtrue,	"PACKET_CURR_BUFFER_CNT"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,

	अणुtrue,	"RX_PACKET_IN_CNT_L"पूर्ण,
	अणुtrue,	"RX_PACKET_IN_CNT_H"पूर्ण,
	अणुtrue,	"RX_PACKET_OUT_CNT_L"पूर्ण,
	अणुtrue,	"RX_PACKET_OUT_CNT_H"पूर्ण,
	अणुtrue,	"TX_PACKET_IN_CNT_L"पूर्ण,
	अणुtrue,	"TX_PACKET_IN_CNT_H"पूर्ण,

	अणुtrue,	"TX_PACKET_OUT_CNT_L"पूर्ण,
	अणुtrue,	"TX_PACKET_OUT_CNT_H"पूर्ण,
	अणुtrue,	"ROC_RX_PACKET_IN_CNT_L"पूर्ण,
	अणुtrue,	"ROC_RX_PACKET_IN_CNT_H"पूर्ण,
	अणुtrue,	"ROC_TX_PACKET_OUT_CNT_L"पूर्ण,
	अणुtrue,	"ROC_TX_PACKET_OUT_CNT_H"पूर्ण,

	अणुtrue,	"RX_PACKET_TC_IN_CNT_0_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_0_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_1_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_1_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_2_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_2_H"पूर्ण,

	अणुtrue,	"RX_PACKET_TC_IN_CNT_3_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_3_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_4_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_4_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_5_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_5_H"पूर्ण,

	अणुtrue,	"RX_PACKET_TC_IN_CNT_6_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_6_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_7_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_IN_CNT_7_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_0_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_0_H"पूर्ण,

	अणुtrue,	"RX_PACKET_TC_OUT_CNT_1_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_1_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_2_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_2_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_3_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_3_H"पूर्ण,

	अणुtrue,	"RX_PACKET_TC_OUT_CNT_4_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_4_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_5_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_5_H"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_6_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_6_H"पूर्ण,

	अणुtrue,	"RX_PACKET_TC_OUT_CNT_7_L"पूर्ण,
	अणुtrue,	"RX_PACKET_TC_OUT_CNT_7_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_0_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_0_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_1_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_1_H"पूर्ण,

	अणुtrue,	"TX_PACKET_TC_IN_CNT_2_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_2_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_3_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_3_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_4_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_4_H"पूर्ण,

	अणुtrue,	"TX_PACKET_TC_IN_CNT_5_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_5_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_6_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_6_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_7_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_IN_CNT_7_H"पूर्ण,

	अणुtrue,	"TX_PACKET_TC_OUT_CNT_0_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_0_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_1_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_1_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_2_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_2_H"पूर्ण,

	अणुtrue,	"TX_PACKET_TC_OUT_CNT_3_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_3_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_4_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_4_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_5_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_5_H"पूर्ण,

	अणुtrue,	"TX_PACKET_TC_OUT_CNT_6_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_6_H"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_7_L"पूर्ण,
	अणुtrue,	"TX_PACKET_TC_OUT_CNT_7_H"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_ssu_reg_2[] = अणु
	अणुtrue,	"OQ_INDEX"पूर्ण,
	अणुtrue,	"QUEUE_CNT"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_igu_egu_reg[] = अणु
	अणुtrue,	"prt_id"पूर्ण,
	अणुtrue,	"IGU_RX_ERR_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_NO_SOF_PKT"पूर्ण,
	अणुtrue,	"EGU_TX_1588_SHORT_PKT"पूर्ण,
	अणुtrue,	"EGU_TX_1588_PKT"पूर्ण,
	अणुtrue,	"EGU_TX_ERR_PKT"पूर्ण,

	अणुtrue,	"IGU_RX_OUT_L2_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_OUT_L3_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_OUT_L4_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_IN_L2_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_IN_L3_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_IN_L4_PKT"पूर्ण,

	अणुtrue,	"IGU_RX_EL3E_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_EL4E_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_L3E_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_L4E_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_ROCEE_PKT"पूर्ण,
	अणुtrue,	"IGU_RX_OUT_UDP0_PKT"पूर्ण,

	अणुtrue,	"IGU_RX_IN_UDP0_PKT"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,

	अणुtrue,	"IGU_RX_OVERSIZE_PKT_L"पूर्ण,
	अणुtrue,	"IGU_RX_OVERSIZE_PKT_H"पूर्ण,
	अणुtrue,	"IGU_RX_UNDERSIZE_PKT_L"पूर्ण,
	अणुtrue,	"IGU_RX_UNDERSIZE_PKT_H"पूर्ण,
	अणुtrue,	"IGU_RX_OUT_ALL_PKT_L"पूर्ण,
	अणुtrue,	"IGU_RX_OUT_ALL_PKT_H"पूर्ण,

	अणुtrue,	"IGU_TX_OUT_ALL_PKT_L"पूर्ण,
	अणुtrue,	"IGU_TX_OUT_ALL_PKT_H"पूर्ण,
	अणुtrue,	"IGU_RX_UNI_PKT_L"पूर्ण,
	अणुtrue,	"IGU_RX_UNI_PKT_H"पूर्ण,
	अणुtrue,	"IGU_RX_MULTI_PKT_L"पूर्ण,
	अणुtrue,	"IGU_RX_MULTI_PKT_H"पूर्ण,

	अणुtrue,	"IGU_RX_BROAD_PKT_L"पूर्ण,
	अणुtrue,	"IGU_RX_BROAD_PKT_H"पूर्ण,
	अणुtrue,	"EGU_TX_OUT_ALL_PKT_L"पूर्ण,
	अणुtrue,	"EGU_TX_OUT_ALL_PKT_H"पूर्ण,
	अणुtrue,	"EGU_TX_UNI_PKT_L"पूर्ण,
	अणुtrue,	"EGU_TX_UNI_PKT_H"पूर्ण,

	अणुtrue,	"EGU_TX_MULTI_PKT_L"पूर्ण,
	अणुtrue,	"EGU_TX_MULTI_PKT_H"पूर्ण,
	अणुtrue,	"EGU_TX_BROAD_PKT_L"पूर्ण,
	अणुtrue,	"EGU_TX_BROAD_PKT_H"पूर्ण,
	अणुtrue,	"IGU_TX_KEY_NUM_L"पूर्ण,
	अणुtrue,	"IGU_TX_KEY_NUM_H"पूर्ण,

	अणुtrue,	"IGU_RX_NON_TUN_PKT_L"पूर्ण,
	अणुtrue,	"IGU_RX_NON_TUN_PKT_H"पूर्ण,
	अणुtrue,	"IGU_RX_TUN_PKT_L"पूर्ण,
	अणुtrue,	"IGU_RX_TUN_PKT_H"पूर्ण,
	अणुfalse,	"Reserved"पूर्ण,
	अणुfalse,	"Reserved"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_rpu_reg_0[] = अणु
	अणुtrue, "tc_queue_num"पूर्ण,
	अणुtrue, "FSM_DFX_ST0"पूर्ण,
	अणुtrue, "FSM_DFX_ST1"पूर्ण,
	अणुtrue, "RPU_RX_PKT_DROP_CNT"पूर्ण,
	अणुtrue, "BUF_WAIT_TIMEOUT"पूर्ण,
	अणुtrue, "BUF_WAIT_TIMEOUT_QID"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_rpu_reg_1[] = अणु
	अणुfalse, "Reserved"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST0"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST1"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST2"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST3"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST4"पूर्ण,

	अणुtrue,	"FIFO_DFX_ST5"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_ncsi_reg[] = अणु
	अणुfalse, "Reserved"पूर्ण,
	अणुtrue,	"NCSI_EGU_TX_FIFO_STS"पूर्ण,
	अणुtrue,	"NCSI_PAUSE_STATUS"पूर्ण,
	अणुtrue,	"NCSI_RX_CTRL_DMAC_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_RX_CTRL_SMAC_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_RX_CTRL_CKS_ERR_CNT"पूर्ण,

	अणुtrue,	"NCSI_RX_CTRL_PKT_CNT"पूर्ण,
	अणुtrue,	"NCSI_RX_PT_DMAC_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_RX_PT_SMAC_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_RX_PT_PKT_CNT"पूर्ण,
	अणुtrue,	"NCSI_RX_FCS_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_TX_CTRL_DMAC_ERR_CNT"पूर्ण,

	अणुtrue,	"NCSI_TX_CTRL_SMAC_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_TX_CTRL_PKT_CNT"पूर्ण,
	अणुtrue,	"NCSI_TX_PT_DMAC_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_TX_PT_SMAC_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_TX_PT_PKT_CNT"पूर्ण,
	अणुtrue,	"NCSI_TX_PT_PKT_TRUNC_CNT"पूर्ण,

	अणुtrue,	"NCSI_TX_PT_PKT_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_TX_CTRL_PKT_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_RX_CTRL_PKT_TRUNC_CNT"पूर्ण,
	अणुtrue,	"NCSI_RX_CTRL_PKT_CFLIT_CNT"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,

	अणुtrue,	"NCSI_MAC_RX_OCTETS_OK"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_OCTETS_BAD"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_UC_PKTS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_MC_PKTS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_BC_PKTS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_PKTS_64OCTETS"पूर्ण,

	अणुtrue,	"NCSI_MAC_RX_PKTS_65TO127OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_PKTS_128TO255OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_PKTS_255TO511OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_PKTS_512TO1023OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_PKTS_1024TO1518OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_PKTS_1519TOMAXOCTETS"पूर्ण,

	अणुtrue,	"NCSI_MAC_RX_FCS_ERRORS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_LONG_ERRORS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_JABBER_ERRORS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_RUNT_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_SHORT_ERR_CNT"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_FILT_PKT_CNT"पूर्ण,

	अणुtrue,	"NCSI_MAC_RX_OCTETS_TOTAL_FILT"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_OCTETS_OK"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_OCTETS_BAD"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_UC_PKTS"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_MC_PKTS"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_BC_PKTS"पूर्ण,

	अणुtrue,	"NCSI_MAC_TX_PKTS_64OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_PKTS_65TO127OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_PKTS_128TO255OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_PKTS_256TO511OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_PKTS_512TO1023OCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_PKTS_1024TO1518OCTETS"पूर्ण,

	अणुtrue,	"NCSI_MAC_TX_PKTS_1519TOMAXOCTETS"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_UNDERRUN"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_CRC_ERROR"पूर्ण,
	अणुtrue,	"NCSI_MAC_TX_PAUSE_FRAMES"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_PAD_PKTS"पूर्ण,
	अणुtrue,	"NCSI_MAC_RX_PAUSE_FRAMES"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_rtc_reg[] = अणु
	अणुfalse, "Reserved"पूर्ण,
	अणुtrue,	"LGE_IGU_AFIFO_DFX_0"पूर्ण,
	अणुtrue,	"LGE_IGU_AFIFO_DFX_1"पूर्ण,
	अणुtrue,	"LGE_IGU_AFIFO_DFX_2"पूर्ण,
	अणुtrue,	"LGE_IGU_AFIFO_DFX_3"पूर्ण,
	अणुtrue,	"LGE_IGU_AFIFO_DFX_4"पूर्ण,

	अणुtrue,	"LGE_IGU_AFIFO_DFX_5"पूर्ण,
	अणुtrue,	"LGE_IGU_AFIFO_DFX_6"पूर्ण,
	अणुtrue,	"LGE_IGU_AFIFO_DFX_7"पूर्ण,
	अणुtrue,	"LGE_EGU_AFIFO_DFX_0"पूर्ण,
	अणुtrue,	"LGE_EGU_AFIFO_DFX_1"पूर्ण,
	अणुtrue,	"LGE_EGU_AFIFO_DFX_2"पूर्ण,

	अणुtrue,	"LGE_EGU_AFIFO_DFX_3"पूर्ण,
	अणुtrue,	"LGE_EGU_AFIFO_DFX_4"पूर्ण,
	अणुtrue,	"LGE_EGU_AFIFO_DFX_5"पूर्ण,
	अणुtrue,	"LGE_EGU_AFIFO_DFX_6"पूर्ण,
	अणुtrue,	"LGE_EGU_AFIFO_DFX_7"पूर्ण,
	अणुtrue,	"CGE_IGU_AFIFO_DFX_0"पूर्ण,

	अणुtrue,	"CGE_IGU_AFIFO_DFX_1"पूर्ण,
	अणुtrue,	"CGE_EGU_AFIFO_DFX_0"पूर्ण,
	अणुtrue,	"CGE_EGU_AFIFO_DFX_1"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_ppp_reg[] = अणु
	अणुfalse, "Reserved"पूर्ण,
	अणुtrue,	"DROP_FROM_PRT_PKT_CNT"पूर्ण,
	अणुtrue,	"DROP_FROM_HOST_PKT_CNT"पूर्ण,
	अणुtrue,	"DROP_TX_VLAN_PROC_CNT"पूर्ण,
	अणुtrue,	"DROP_MNG_CNT"पूर्ण,
	अणुtrue,	"DROP_FD_CNT"पूर्ण,

	अणुtrue,	"DROP_NO_DST_CNT"पूर्ण,
	अणुtrue,	"DROP_MC_MBID_FULL_CNT"पूर्ण,
	अणुtrue,	"DROP_SC_FILTERED"पूर्ण,
	अणुtrue,	"PPP_MC_DROP_PKT_CNT"पूर्ण,
	अणुtrue,	"DROP_PT_CNT"पूर्ण,
	अणुtrue,	"DROP_MAC_ANTI_SPOOF_CNT"पूर्ण,

	अणुtrue,	"DROP_IG_VFV_CNT"पूर्ण,
	अणुtrue,	"DROP_IG_PRTV_CNT"पूर्ण,
	अणुtrue,	"DROP_CNM_PFC_PAUSE_CNT"पूर्ण,
	अणुtrue,	"DROP_TORUS_TC_CNT"पूर्ण,
	अणुtrue,	"DROP_TORUS_LPBK_CNT"पूर्ण,
	अणुtrue,	"PPP_HFS_STS"पूर्ण,

	अणुtrue,	"PPP_MC_RSLT_STS"पूर्ण,
	अणुtrue,	"PPP_P3U_STS"पूर्ण,
	अणुtrue,	"PPP_RSLT_DESCR_STS"पूर्ण,
	अणुtrue,	"PPP_UMV_STS_0"पूर्ण,
	अणुtrue,	"PPP_UMV_STS_1"पूर्ण,
	अणुtrue,	"PPP_VFV_STS"पूर्ण,

	अणुtrue,	"PPP_GRO_KEY_CNT"पूर्ण,
	अणुtrue,	"PPP_GRO_INFO_CNT"पूर्ण,
	अणुtrue,	"PPP_GRO_DROP_CNT"पूर्ण,
	अणुtrue,	"PPP_GRO_OUT_CNT"पूर्ण,
	अणुtrue,	"PPP_GRO_KEY_MATCH_DATA_CNT"पूर्ण,
	अणुtrue,	"PPP_GRO_KEY_MATCH_TCAM_CNT"पूर्ण,

	अणुtrue,	"PPP_GRO_INFO_MATCH_CNT"पूर्ण,
	अणुtrue,	"PPP_GRO_FREE_ENTRY_CNT"पूर्ण,
	अणुtrue,	"PPP_GRO_INNER_DFX_SIGNAL"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,

	अणुtrue,	"GET_RX_PKT_CNT_L"पूर्ण,
	अणुtrue,	"GET_RX_PKT_CNT_H"पूर्ण,
	अणुtrue,	"GET_TX_PKT_CNT_L"पूर्ण,
	अणुtrue,	"GET_TX_PKT_CNT_H"पूर्ण,
	अणुtrue,	"SEND_UC_PRT2HOST_PKT_CNT_L"पूर्ण,
	अणुtrue,	"SEND_UC_PRT2HOST_PKT_CNT_H"पूर्ण,

	अणुtrue,	"SEND_UC_PRT2PRT_PKT_CNT_L"पूर्ण,
	अणुtrue,	"SEND_UC_PRT2PRT_PKT_CNT_H"पूर्ण,
	अणुtrue,	"SEND_UC_HOST2HOST_PKT_CNT_L"पूर्ण,
	अणुtrue,	"SEND_UC_HOST2HOST_PKT_CNT_H"पूर्ण,
	अणुtrue,	"SEND_UC_HOST2PRT_PKT_CNT_L"पूर्ण,
	अणुtrue,	"SEND_UC_HOST2PRT_PKT_CNT_H"पूर्ण,

	अणुtrue,	"SEND_MC_FROM_PRT_CNT_L"पूर्ण,
	अणुtrue,	"SEND_MC_FROM_PRT_CNT_H"पूर्ण,
	अणुtrue,	"SEND_MC_FROM_HOST_CNT_L"पूर्ण,
	अणुtrue,	"SEND_MC_FROM_HOST_CNT_H"पूर्ण,
	अणुtrue,	"SSU_MC_RD_CNT_L"पूर्ण,
	अणुtrue,	"SSU_MC_RD_CNT_H"पूर्ण,

	अणुtrue,	"SSU_MC_DROP_CNT_L"पूर्ण,
	अणुtrue,	"SSU_MC_DROP_CNT_H"पूर्ण,
	अणुtrue,	"SSU_MC_RD_PKT_CNT_L"पूर्ण,
	अणुtrue,	"SSU_MC_RD_PKT_CNT_H"पूर्ण,
	अणुtrue,	"PPP_MC_2HOST_PKT_CNT_L"पूर्ण,
	अणुtrue,	"PPP_MC_2HOST_PKT_CNT_H"पूर्ण,

	अणुtrue,	"PPP_MC_2PRT_PKT_CNT_L"पूर्ण,
	अणुtrue,	"PPP_MC_2PRT_PKT_CNT_H"पूर्ण,
	अणुtrue,	"NTSNOS_PKT_CNT_L"पूर्ण,
	अणुtrue,	"NTSNOS_PKT_CNT_H"पूर्ण,
	अणुtrue,	"NTUP_PKT_CNT_L"पूर्ण,
	अणुtrue,	"NTUP_PKT_CNT_H"पूर्ण,

	अणुtrue,	"NTLCL_PKT_CNT_L"पूर्ण,
	अणुtrue,	"NTLCL_PKT_CNT_H"पूर्ण,
	अणुtrue,	"NTTGT_PKT_CNT_L"पूर्ण,
	अणुtrue,	"NTTGT_PKT_CNT_H"पूर्ण,
	अणुtrue,	"RTNS_PKT_CNT_L"पूर्ण,
	अणुtrue,	"RTNS_PKT_CNT_H"पूर्ण,

	अणुtrue,	"RTLPBK_PKT_CNT_L"पूर्ण,
	अणुtrue,	"RTLPBK_PKT_CNT_H"पूर्ण,
	अणुtrue,	"NR_PKT_CNT_L"पूर्ण,
	अणुtrue,	"NR_PKT_CNT_H"पूर्ण,
	अणुtrue,	"RR_PKT_CNT_L"पूर्ण,
	अणुtrue,	"RR_PKT_CNT_H"पूर्ण,

	अणुtrue,	"MNG_TBL_HIT_CNT_L"पूर्ण,
	अणुtrue,	"MNG_TBL_HIT_CNT_H"पूर्ण,
	अणुtrue,	"FD_TBL_HIT_CNT_L"पूर्ण,
	अणुtrue,	"FD_TBL_HIT_CNT_H"पूर्ण,
	अणुtrue,	"FD_LKUP_CNT_L"पूर्ण,
	अणुtrue,	"FD_LKUP_CNT_H"पूर्ण,

	अणुtrue,	"BC_HIT_CNT_L"पूर्ण,
	अणुtrue,	"BC_HIT_CNT_H"पूर्ण,
	अणुtrue,	"UM_TBL_UC_HIT_CNT_L"पूर्ण,
	अणुtrue,	"UM_TBL_UC_HIT_CNT_H"पूर्ण,
	अणुtrue,	"UM_TBL_MC_HIT_CNT_L"पूर्ण,
	अणुtrue,	"UM_TBL_MC_HIT_CNT_H"पूर्ण,

	अणुtrue,	"UM_TBL_VMDQ1_HIT_CNT_L"पूर्ण,
	अणुtrue,	"UM_TBL_VMDQ1_HIT_CNT_H"पूर्ण,
	अणुtrue,	"MTA_TBL_HIT_CNT_L"पूर्ण,
	अणुtrue,	"MTA_TBL_HIT_CNT_H"पूर्ण,
	अणुtrue,	"FWD_BONDING_HIT_CNT_L"पूर्ण,
	अणुtrue,	"FWD_BONDING_HIT_CNT_H"पूर्ण,

	अणुtrue,	"PROMIS_TBL_HIT_CNT_L"पूर्ण,
	अणुtrue,	"PROMIS_TBL_HIT_CNT_H"पूर्ण,
	अणुtrue,	"GET_TUNL_PKT_CNT_L"पूर्ण,
	अणुtrue,	"GET_TUNL_PKT_CNT_H"पूर्ण,
	अणुtrue,	"GET_BMC_PKT_CNT_L"पूर्ण,
	अणुtrue,	"GET_BMC_PKT_CNT_H"पूर्ण,

	अणुtrue,	"SEND_UC_PRT2BMC_PKT_CNT_L"पूर्ण,
	अणुtrue,	"SEND_UC_PRT2BMC_PKT_CNT_H"पूर्ण,
	अणुtrue,	"SEND_UC_HOST2BMC_PKT_CNT_L"पूर्ण,
	अणुtrue,	"SEND_UC_HOST2BMC_PKT_CNT_H"पूर्ण,
	अणुtrue,	"SEND_UC_BMC2HOST_PKT_CNT_L"पूर्ण,
	अणुtrue,	"SEND_UC_BMC2HOST_PKT_CNT_H"पूर्ण,

	अणुtrue,	"SEND_UC_BMC2PRT_PKT_CNT_L"पूर्ण,
	अणुtrue,	"SEND_UC_BMC2PRT_PKT_CNT_H"पूर्ण,
	अणुtrue,	"PPP_MC_2BMC_PKT_CNT_L"पूर्ण,
	अणुtrue,	"PPP_MC_2BMC_PKT_CNT_H"पूर्ण,
	अणुtrue,	"VLAN_MIRR_CNT_L"पूर्ण,
	अणुtrue,	"VLAN_MIRR_CNT_H"पूर्ण,

	अणुtrue,	"IG_MIRR_CNT_L"पूर्ण,
	अणुtrue,	"IG_MIRR_CNT_H"पूर्ण,
	अणुtrue,	"EG_MIRR_CNT_L"पूर्ण,
	अणुtrue,	"EG_MIRR_CNT_H"पूर्ण,
	अणुtrue,	"RX_DEFAULT_HOST_HIT_CNT_L"पूर्ण,
	अणुtrue,	"RX_DEFAULT_HOST_HIT_CNT_H"पूर्ण,

	अणुtrue,	"LAN_PAIR_CNT_L"पूर्ण,
	अणुtrue,	"LAN_PAIR_CNT_H"पूर्ण,
	अणुtrue,	"UM_TBL_MC_HIT_PKT_CNT_L"पूर्ण,
	अणुtrue,	"UM_TBL_MC_HIT_PKT_CNT_H"पूर्ण,
	अणुtrue,	"MTA_TBL_HIT_PKT_CNT_L"पूर्ण,
	अणुtrue,	"MTA_TBL_HIT_PKT_CNT_H"पूर्ण,

	अणुtrue,	"PROMIS_TBL_HIT_PKT_CNT_L"पूर्ण,
	अणुtrue,	"PROMIS_TBL_HIT_PKT_CNT_H"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_rcb_reg[] = अणु
	अणुfalse, "Reserved"पूर्ण,
	अणुtrue,	"FSM_DFX_ST0"पूर्ण,
	अणुtrue,	"FSM_DFX_ST1"पूर्ण,
	अणुtrue,	"FSM_DFX_ST2"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST0"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST1"पूर्ण,

	अणुtrue,	"FIFO_DFX_ST2"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST3"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST4"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST5"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST6"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST7"पूर्ण,

	अणुtrue,	"FIFO_DFX_ST8"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST9"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST10"पूर्ण,
	अणुtrue,	"FIFO_DFX_ST11"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_0"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_1"पूर्ण,

	अणुtrue,	"Q_CREDIT_VLD_2"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_3"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_4"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_5"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_6"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_7"पूर्ण,

	अणुtrue,	"Q_CREDIT_VLD_8"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_9"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_10"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_11"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_12"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_13"पूर्ण,

	अणुtrue,	"Q_CREDIT_VLD_14"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_15"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_16"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_17"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_18"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_19"पूर्ण,

	अणुtrue,	"Q_CREDIT_VLD_20"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_21"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_22"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_23"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_24"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_25"पूर्ण,

	अणुtrue,	"Q_CREDIT_VLD_26"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_27"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_28"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_29"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_30"पूर्ण,
	अणुtrue,	"Q_CREDIT_VLD_31"पूर्ण,

	अणुtrue,	"GRO_BD_SERR_CNT"पूर्ण,
	अणुtrue,	"GRO_CONTEXT_SERR_CNT"पूर्ण,
	अणुtrue,	"RX_STASH_CFG_SERR_CNT"पूर्ण,
	अणुtrue,	"AXI_RD_FBD_SERR_CNT"पूर्ण,
	अणुtrue,	"GRO_BD_MERR_CNT"पूर्ण,
	अणुtrue,	"GRO_CONTEXT_MERR_CNT"पूर्ण,

	अणुtrue,	"RX_STASH_CFG_MERR_CNT"पूर्ण,
	अणुtrue,	"AXI_RD_FBD_MERR_CNT"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
	अणुfalse, "Reserved"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hclge_dbg_dfx_message hclge_dbg_tqp_reg[] = अणु
	अणुtrue, "q_num"पूर्ण,
	अणुtrue, "RCB_CFG_RX_RING_TAIL"पूर्ण,
	अणुtrue, "RCB_CFG_RX_RING_HEAD"पूर्ण,
	अणुtrue, "RCB_CFG_RX_RING_FBDNUM"पूर्ण,
	अणुtrue, "RCB_CFG_RX_RING_OFFSET"पूर्ण,
	अणुtrue, "RCB_CFG_RX_RING_FBDOFFSET"पूर्ण,

	अणुtrue, "RCB_CFG_RX_RING_PKTNUM_RECORD"पूर्ण,
	अणुtrue, "RCB_CFG_TX_RING_TAIL"पूर्ण,
	अणुtrue, "RCB_CFG_TX_RING_HEAD"पूर्ण,
	अणुtrue, "RCB_CFG_TX_RING_FBDNUM"पूर्ण,
	अणुtrue, "RCB_CFG_TX_RING_OFFSET"पूर्ण,
	अणुtrue, "RCB_CFG_TX_RING_EBDNUM"पूर्ण,
पूर्ण;

#पूर्ण_अगर
