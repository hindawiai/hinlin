<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2016-2017 Hisilicon Limited. */

#समावेश "hclge_err.h"

अटल स्थिर काष्ठा hclge_hw_error hclge_imp_tcm_ecc_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(1), .msg = "imp_itcm0_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "imp_itcm1_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "imp_itcm2_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "imp_itcm3_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "imp_dtcm0_mem0_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "imp_dtcm0_mem1_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "imp_dtcm1_mem0_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(15), .msg = "imp_dtcm1_mem1_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(17), .msg = "imp_itcm4_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_cmdq_nic_mem_ecc_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(1), .msg = "cmdq_nic_rx_depth_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "cmdq_nic_tx_depth_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "cmdq_nic_rx_tail_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "cmdq_nic_tx_tail_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "cmdq_nic_rx_head_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "cmdq_nic_tx_head_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "cmdq_nic_rx_addr_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(15), .msg = "cmdq_nic_tx_addr_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(17), .msg = "cmdq_rocee_rx_depth_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(19), .msg = "cmdq_rocee_tx_depth_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(21), .msg = "cmdq_rocee_rx_tail_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(23), .msg = "cmdq_rocee_tx_tail_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(25), .msg = "cmdq_rocee_rx_head_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(27), .msg = "cmdq_rocee_tx_head_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(29), .msg = "cmdq_rocee_rx_addr_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(31), .msg = "cmdq_rocee_tx_addr_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_tqp_पूर्णांक_ecc_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(6), .msg = "tqp_int_cfg_even_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "tqp_int_cfg_odd_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "tqp_int_ctrl_even_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "tqp_int_ctrl_odd_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(10), .msg = "tx_que_scan_int_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "rx_que_scan_int_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_msix_sram_ecc_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(1), .msg = "msix_nic_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "msix_rocee_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_igu_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "igu_rx_buf0_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "igu_rx_buf1_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_igu_egu_tnl_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "rx_buf_overflow",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "rx_stp_fifo_overflow",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "rx_stp_fifo_underflow",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "tx_buf_overflow",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "tx_buf_underrun",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "rx_stp_buf_overflow",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ncsi_err_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(1), .msg = "ncsi_tx_ecc_mbit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ppp_mpf_abnormal_पूर्णांक_st1[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "vf_vlan_ad_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "umv_mcast_group_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "umv_key_mem0_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "umv_key_mem1_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "umv_key_mem2_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "umv_key_mem3_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "umv_ad_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "rss_tc_mode_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "rss_idt_mem0_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "rss_idt_mem1_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(10), .msg = "rss_idt_mem2_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "rss_idt_mem3_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(12), .msg = "rss_idt_mem4_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "rss_idt_mem5_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(14), .msg = "rss_idt_mem6_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(15), .msg = "rss_idt_mem7_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(16), .msg = "rss_idt_mem8_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(17), .msg = "rss_idt_mem9_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(18), .msg = "rss_idt_mem10_ecc_m1bit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(19), .msg = "rss_idt_mem11_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(20), .msg = "rss_idt_mem12_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(21), .msg = "rss_idt_mem13_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(22), .msg = "rss_idt_mem14_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(23), .msg = "rss_idt_mem15_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(24), .msg = "port_vlan_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(25), .msg = "mcast_linear_table_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(26), .msg = "mcast_result_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(27), .msg = "flow_director_ad_mem0_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(28), .msg = "flow_director_ad_mem1_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(29), .msg = "rx_vlan_tag_memory_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(30), .msg = "Tx_UP_mapping_config_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ppp_pf_abnormal_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "tx_vlan_tag_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "rss_list_tc_unassigned_queue_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ppp_mpf_abnormal_पूर्णांक_st3[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "hfs_fifo_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "rslt_descr_fifo_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "tx_vlan_tag_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "FD_CN0_memory_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "FD_CN1_memory_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "GRO_AD_memory_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_पंचांग_sch_rपूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(1), .msg = "tm_sch_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "tm_sch_port_shap_sub_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "tm_sch_port_shap_sub_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "tm_sch_pg_pshap_sub_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "tm_sch_pg_pshap_sub_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "tm_sch_pg_cshap_sub_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "tm_sch_pg_cshap_sub_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "tm_sch_pri_pshap_sub_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "tm_sch_pri_pshap_sub_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(10), .msg = "tm_sch_pri_cshap_sub_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "tm_sch_pri_cshap_sub_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(12), .msg = "tm_sch_port_shap_offset_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "tm_sch_port_shap_offset_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(14), .msg = "tm_sch_pg_pshap_offset_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(15), .msg = "tm_sch_pg_pshap_offset_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(16), .msg = "tm_sch_pg_cshap_offset_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(17), .msg = "tm_sch_pg_cshap_offset_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(18), .msg = "tm_sch_pri_pshap_offset_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(19), .msg = "tm_sch_pri_pshap_offset_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(20), .msg = "tm_sch_pri_cshap_offset_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(21), .msg = "tm_sch_pri_cshap_offset_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(22), .msg = "tm_sch_rq_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(23), .msg = "tm_sch_rq_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(24), .msg = "tm_sch_nq_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(25), .msg = "tm_sch_nq_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(26), .msg = "tm_sch_roce_up_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(27), .msg = "tm_sch_roce_up_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(28), .msg = "tm_sch_rcb_byte_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(29), .msg = "tm_sch_rcb_byte_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(30), .msg = "tm_sch_ssu_byte_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(31), .msg = "tm_sch_ssu_byte_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_qcn_fअगरo_rपूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "qcn_shap_gp0_sch_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "qcn_shap_gp0_sch_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "qcn_shap_gp1_sch_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "qcn_shap_gp1_sch_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "qcn_shap_gp2_sch_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "qcn_shap_gp2_sch_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "qcn_shap_gp3_sch_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "qcn_shap_gp3_sch_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "qcn_shap_gp0_offset_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "qcn_shap_gp0_offset_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(10), .msg = "qcn_shap_gp1_offset_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "qcn_shap_gp1_offset_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(12), .msg = "qcn_shap_gp2_offset_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "qcn_shap_gp2_offset_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(14), .msg = "qcn_shap_gp3_offset_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(15), .msg = "qcn_shap_gp3_offset_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(16), .msg = "qcn_byte_info_fifo_rd_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(17), .msg = "qcn_byte_info_fifo_wr_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_qcn_ecc_rपूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(1), .msg = "qcn_byte_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "qcn_time_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "qcn_fb_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "qcn_link_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "qcn_rate_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "qcn_tmplt_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "qcn_shap_cfg_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(15), .msg = "qcn_gp0_barrel_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(17), .msg = "qcn_gp1_barrel_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(19), .msg = "qcn_gp2_barrel_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(21), .msg = "qcn_gp3_barral_mem_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_mac_afअगरo_tnl_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "egu_cge_afifo_ecc_1bit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "egu_cge_afifo_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "egu_lge_afifo_ecc_1bit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "egu_lge_afifo_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "cge_igu_afifo_ecc_1bit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "cge_igu_afifo_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "lge_igu_afifo_ecc_1bit_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "lge_igu_afifo_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "cge_igu_afifo_overflow_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "lge_igu_afifo_overflow_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(10), .msg = "egu_cge_afifo_underrun_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "egu_lge_afifo_underrun_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(12), .msg = "egu_ge_afifo_underrun_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "ge_igu_afifo_overflow_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ppu_mpf_abnormal_पूर्णांक_st2[] = अणु
	अणु .पूर्णांक_msk = BIT(13), .msg = "rpu_rx_pkt_bit32_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(14), .msg = "rpu_rx_pkt_bit33_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(15), .msg = "rpu_rx_pkt_bit34_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(16), .msg = "rpu_rx_pkt_bit35_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(17), .msg = "rcb_tx_ring_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(18), .msg = "rcb_rx_ring_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(19), .msg = "rcb_tx_fbd_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(20), .msg = "rcb_rx_ebd_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(21), .msg = "rcb_tso_info_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(22), .msg = "rcb_tx_int_info_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(23), .msg = "rcb_rx_int_info_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(24), .msg = "tpu_tx_pkt_0_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(25), .msg = "tpu_tx_pkt_1_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(26), .msg = "rd_bus_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(27), .msg = "wr_bus_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(28), .msg = "reg_search_miss",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(29), .msg = "rx_q_search_miss",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(30), .msg = "ooo_ecc_err_detect",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(31), .msg = "ooo_ecc_err_multpl",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ppu_mpf_abnormal_पूर्णांक_st3[] = अणु
	अणु .पूर्णांक_msk = BIT(4), .msg = "gro_bd_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "gro_context_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "rx_stash_cfg_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "axi_rd_fbd_ecc_mbit_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ppu_pf_abnormal_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "over_8bd_no_fe",
	  .reset_level = HNAE3_FUNC_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "tso_mss_cmp_min_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "tso_mss_cmp_max_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "tx_rd_fbd_poison",
	  .reset_level = HNAE3_FUNC_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "rx_rd_ebd_poison",
	  .reset_level = HNAE3_FUNC_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "buf_wait_timeout",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ssu_com_err_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "buf_sum_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "ppp_mb_num_err",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "ppp_mbid_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "ppp_rlt_mac_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "ppp_rlt_host_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "cks_edit_position_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "cks_edit_condition_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "vlan_edit_condition_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "vlan_num_ot_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "vlan_num_in_err",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

#घोषणा HCLGE_SSU_MEM_ECC_ERR(x) \
	अणु .पूर्णांक_msk = BIT(x), .msg = "ssu_mem" #x "_ecc_mbit_err", \
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण

अटल स्थिर काष्ठा hclge_hw_error hclge_ssu_mem_ecc_err_पूर्णांक[] = अणु
	HCLGE_SSU_MEM_ECC_ERR(0),
	HCLGE_SSU_MEM_ECC_ERR(1),
	HCLGE_SSU_MEM_ECC_ERR(2),
	HCLGE_SSU_MEM_ECC_ERR(3),
	HCLGE_SSU_MEM_ECC_ERR(4),
	HCLGE_SSU_MEM_ECC_ERR(5),
	HCLGE_SSU_MEM_ECC_ERR(6),
	HCLGE_SSU_MEM_ECC_ERR(7),
	HCLGE_SSU_MEM_ECC_ERR(8),
	HCLGE_SSU_MEM_ECC_ERR(9),
	HCLGE_SSU_MEM_ECC_ERR(10),
	HCLGE_SSU_MEM_ECC_ERR(11),
	HCLGE_SSU_MEM_ECC_ERR(12),
	HCLGE_SSU_MEM_ECC_ERR(13),
	HCLGE_SSU_MEM_ECC_ERR(14),
	HCLGE_SSU_MEM_ECC_ERR(15),
	HCLGE_SSU_MEM_ECC_ERR(16),
	HCLGE_SSU_MEM_ECC_ERR(17),
	HCLGE_SSU_MEM_ECC_ERR(18),
	HCLGE_SSU_MEM_ECC_ERR(19),
	HCLGE_SSU_MEM_ECC_ERR(20),
	HCLGE_SSU_MEM_ECC_ERR(21),
	HCLGE_SSU_MEM_ECC_ERR(22),
	HCLGE_SSU_MEM_ECC_ERR(23),
	HCLGE_SSU_MEM_ECC_ERR(24),
	HCLGE_SSU_MEM_ECC_ERR(25),
	HCLGE_SSU_MEM_ECC_ERR(26),
	HCLGE_SSU_MEM_ECC_ERR(27),
	HCLGE_SSU_MEM_ECC_ERR(28),
	HCLGE_SSU_MEM_ECC_ERR(29),
	HCLGE_SSU_MEM_ECC_ERR(30),
	HCLGE_SSU_MEM_ECC_ERR(31),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ssu_port_based_err_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "roc_pkt_without_key_port",
	  .reset_level = HNAE3_FUNC_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "tpu_pkt_without_key_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "igu_pkt_without_key_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "roc_eof_mis_match_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "tpu_eof_mis_match_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "igu_eof_mis_match_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "roc_sof_mis_match_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "tpu_sof_mis_match_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "igu_sof_mis_match_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "ets_rd_int_rx_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(12), .msg = "ets_wr_int_rx_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "ets_rd_int_tx_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(14), .msg = "ets_wr_int_tx_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ssu_fअगरo_overflow_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "ig_mac_inf_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "ig_host_inf_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "ig_roc_buf_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "ig_host_data_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "ig_host_key_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "tx_qcn_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "rx_qcn_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "tx_pf_rd_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "rx_pf_rd_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "qm_eof_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(10), .msg = "mb_rlt_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "dup_uncopy_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(12), .msg = "dup_cnt_rd_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(13), .msg = "dup_cnt_drop_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(14), .msg = "dup_cnt_wrb_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(15), .msg = "host_cmd_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(16), .msg = "mac_cmd_fifo_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(17), .msg = "host_cmd_bitmap_empty_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(18), .msg = "mac_cmd_bitmap_empty_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(19), .msg = "dup_bitmap_empty_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(20), .msg = "out_queue_bitmap_empty_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(21), .msg = "bank2_bitmap_empty_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(22), .msg = "bank1_bitmap_empty_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(23), .msg = "bank0_bitmap_empty_int",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ssu_ets_tcg_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "ets_rd_int_rx_tcg",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "ets_wr_int_rx_tcg",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "ets_rd_int_tx_tcg",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "ets_wr_int_tx_tcg",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_ssu_port_based_pf_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "roc_pkt_without_key_port",
	  .reset_level = HNAE3_FUNC_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "low_water_line_err_port",
	  .reset_level = HNAE3_NONE_RESET पूर्ण,
	अणु .पूर्णांक_msk = BIT(10), .msg = "hi_water_line_err_port",
	  .reset_level = HNAE3_GLOBAL_RESET पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hclge_hw_error hclge_rocee_qmm_ovf_err_पूर्णांक[] = अणु
	अणु .पूर्णांक_msk = 0, .msg = "rocee qmm ovf: sgid invalid err" पूर्ण,
	अणु .पूर्णांक_msk = 0x4, .msg = "rocee qmm ovf: sgid ovf err" पूर्ण,
	अणु .पूर्णांक_msk = 0x8, .msg = "rocee qmm ovf: smac invalid err" पूर्ण,
	अणु .पूर्णांक_msk = 0xC, .msg = "rocee qmm ovf: smac ovf err" पूर्ण,
	अणु .पूर्णांक_msk = 0x10, .msg = "rocee qmm ovf: cqc invalid err" पूर्ण,
	अणु .पूर्णांक_msk = 0x11, .msg = "rocee qmm ovf: cqc ovf err" पूर्ण,
	अणु .पूर्णांक_msk = 0x12, .msg = "rocee qmm ovf: cqc hopnum err" पूर्ण,
	अणु .पूर्णांक_msk = 0x13, .msg = "rocee qmm ovf: cqc ba0 err" पूर्ण,
	अणु .पूर्णांक_msk = 0x14, .msg = "rocee qmm ovf: srqc invalid err" पूर्ण,
	अणु .पूर्णांक_msk = 0x15, .msg = "rocee qmm ovf: srqc ovf err" पूर्ण,
	अणु .पूर्णांक_msk = 0x16, .msg = "rocee qmm ovf: srqc hopnum err" पूर्ण,
	अणु .पूर्णांक_msk = 0x17, .msg = "rocee qmm ovf: srqc ba0 err" पूर्ण,
	अणु .पूर्णांक_msk = 0x18, .msg = "rocee qmm ovf: mpt invalid err" पूर्ण,
	अणु .पूर्णांक_msk = 0x19, .msg = "rocee qmm ovf: mpt ovf err" पूर्ण,
	अणु .पूर्णांक_msk = 0x1A, .msg = "rocee qmm ovf: mpt hopnum err" पूर्ण,
	अणु .पूर्णांक_msk = 0x1B, .msg = "rocee qmm ovf: mpt ba0 err" पूर्ण,
	अणु .पूर्णांक_msk = 0x1C, .msg = "rocee qmm ovf: qpc invalid err" पूर्ण,
	अणु .पूर्णांक_msk = 0x1D, .msg = "rocee qmm ovf: qpc ovf err" पूर्ण,
	अणु .पूर्णांक_msk = 0x1E, .msg = "rocee qmm ovf: qpc hopnum err" पूर्ण,
	अणु .पूर्णांक_msk = 0x1F, .msg = "rocee qmm ovf: qpc ba0 err" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम hclge_log_error(काष्ठा device *dev, अक्षर *reg,
			    स्थिर काष्ठा hclge_hw_error *err,
			    u32 err_sts, अचिन्हित दीर्घ *reset_requests)
अणु
	जबतक (err->msg) अणु
		अगर (err->पूर्णांक_msk & err_sts) अणु
			dev_err(dev, "%s %s found [error status=0x%x]\n",
				reg, err->msg, err_sts);
			अगर (err->reset_level &&
			    err->reset_level != HNAE3_NONE_RESET)
				set_bit(err->reset_level, reset_requests);
		पूर्ण
		err++;
	पूर्ण
पूर्ण

/* hclge_cmd_query_error: पढ़ो the error inक्रमmation
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @desc: descriptor क्रम describing the command
 * @cmd:  command opcode
 * @flag: flag क्रम extended command काष्ठाure
 *
 * This function query the error info from hw रेजिस्टर/s using command
 */
अटल पूर्णांक hclge_cmd_query_error(काष्ठा hclge_dev *hdev,
				 काष्ठा hclge_desc *desc, u32 cmd, u16 flag)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	पूर्णांक desc_num = 1;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc[0], cmd, true);
	अगर (flag) अणु
		desc[0].flag |= cpu_to_le16(flag);
		hclge_cmd_setup_basic_desc(&desc[1], cmd, true);
		desc_num = 2;
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, &desc[0], desc_num);
	अगर (ret)
		dev_err(dev, "query error cmd failed (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_clear_mac_tnl_पूर्णांक(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CLEAR_MAC_TNL_INT, false);
	desc.data[0] = cpu_to_le32(HCLGE_MAC_TNL_INT_CLR);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_config_common_hw_err_पूर्णांक(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc[2];
	पूर्णांक ret;

	/* configure common error पूर्णांकerrupts */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_COMMON_ECC_INT_CFG, false);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_COMMON_ECC_INT_CFG, false);

	अगर (en) अणु
		desc[0].data[0] = cpu_to_le32(HCLGE_IMP_TCM_ECC_ERR_INT_EN);
		desc[0].data[2] = cpu_to_le32(HCLGE_CMDQ_NIC_ECC_ERR_INT_EN |
					HCLGE_CMDQ_ROCEE_ECC_ERR_INT_EN);
		desc[0].data[3] = cpu_to_le32(HCLGE_IMP_RD_POISON_ERR_INT_EN);
		desc[0].data[4] = cpu_to_le32(HCLGE_TQP_ECC_ERR_INT_EN |
					      HCLGE_MSIX_SRAM_ECC_ERR_INT_EN);
		desc[0].data[5] = cpu_to_le32(HCLGE_IMP_ITCM4_ECC_ERR_INT_EN);
	पूर्ण

	desc[1].data[0] = cpu_to_le32(HCLGE_IMP_TCM_ECC_ERR_INT_EN_MASK);
	desc[1].data[2] = cpu_to_le32(HCLGE_CMDQ_NIC_ECC_ERR_INT_EN_MASK |
				HCLGE_CMDQ_ROCEE_ECC_ERR_INT_EN_MASK);
	desc[1].data[3] = cpu_to_le32(HCLGE_IMP_RD_POISON_ERR_INT_EN_MASK);
	desc[1].data[4] = cpu_to_le32(HCLGE_TQP_ECC_ERR_INT_EN_MASK |
				      HCLGE_MSIX_SRAM_ECC_ERR_INT_EN_MASK);
	desc[1].data[5] = cpu_to_le32(HCLGE_IMP_ITCM4_ECC_ERR_INT_EN_MASK);

	ret = hclge_cmd_send(&hdev->hw, &desc[0], 2);
	अगर (ret)
		dev_err(dev,
			"fail(%d) to configure common err interrupts\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_ncsi_hw_err_पूर्णांक(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		वापस 0;

	/* configure NCSI error पूर्णांकerrupts */
	hclge_cmd_setup_basic_desc(&desc, HCLGE_NCSI_INT_EN, false);
	अगर (en)
		desc.data[0] = cpu_to_le32(HCLGE_NCSI_ERR_INT_EN);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(dev,
			"fail(%d) to configure  NCSI error interrupts\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_igu_egu_hw_err_पूर्णांक(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	/* configure IGU,EGU error पूर्णांकerrupts */
	hclge_cmd_setup_basic_desc(&desc, HCLGE_IGU_COMMON_INT_EN, false);
	desc.data[0] = cpu_to_le32(HCLGE_IGU_ERR_INT_TYPE);
	अगर (en)
		desc.data[0] |= cpu_to_le32(HCLGE_IGU_ERR_INT_EN);

	desc.data[1] = cpu_to_le32(HCLGE_IGU_ERR_INT_EN_MASK);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(dev,
			"fail(%d) to configure IGU common interrupts\n", ret);
		वापस ret;
	पूर्ण

	hclge_cmd_setup_basic_desc(&desc, HCLGE_IGU_EGU_TNL_INT_EN, false);
	अगर (en)
		desc.data[0] = cpu_to_le32(HCLGE_IGU_TNL_ERR_INT_EN);

	desc.data[1] = cpu_to_le32(HCLGE_IGU_TNL_ERR_INT_EN_MASK);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(dev,
			"fail(%d) to configure IGU-EGU TNL interrupts\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_config_ncsi_hw_err_पूर्णांक(hdev, en);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_ppp_error_पूर्णांकerrupt(काष्ठा hclge_dev *hdev, u32 cmd,
					    bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc[2];
	पूर्णांक ret;

	/* configure PPP error पूर्णांकerrupts */
	hclge_cmd_setup_basic_desc(&desc[0], cmd, false);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], cmd, false);

	अगर (cmd == HCLGE_PPP_CMD0_INT_CMD) अणु
		अगर (en) अणु
			desc[0].data[0] =
				cpu_to_le32(HCLGE_PPP_MPF_ECC_ERR_INT0_EN);
			desc[0].data[1] =
				cpu_to_le32(HCLGE_PPP_MPF_ECC_ERR_INT1_EN);
			desc[0].data[4] = cpu_to_le32(HCLGE_PPP_PF_ERR_INT_EN);
		पूर्ण

		desc[1].data[0] =
			cpu_to_le32(HCLGE_PPP_MPF_ECC_ERR_INT0_EN_MASK);
		desc[1].data[1] =
			cpu_to_le32(HCLGE_PPP_MPF_ECC_ERR_INT1_EN_MASK);
		अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2)
			desc[1].data[2] =
				cpu_to_le32(HCLGE_PPP_PF_ERR_INT_EN_MASK);
	पूर्ण अन्यथा अगर (cmd == HCLGE_PPP_CMD1_INT_CMD) अणु
		अगर (en) अणु
			desc[0].data[0] =
				cpu_to_le32(HCLGE_PPP_MPF_ECC_ERR_INT2_EN);
			desc[0].data[1] =
				cpu_to_le32(HCLGE_PPP_MPF_ECC_ERR_INT3_EN);
		पूर्ण

		desc[1].data[0] =
				cpu_to_le32(HCLGE_PPP_MPF_ECC_ERR_INT2_EN_MASK);
		desc[1].data[1] =
				cpu_to_le32(HCLGE_PPP_MPF_ECC_ERR_INT3_EN_MASK);
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, &desc[0], 2);
	अगर (ret)
		dev_err(dev, "fail(%d) to configure PPP error intr\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_ppp_hw_err_पूर्णांक(काष्ठा hclge_dev *hdev, bool en)
अणु
	पूर्णांक ret;

	ret = hclge_config_ppp_error_पूर्णांकerrupt(hdev, HCLGE_PPP_CMD0_INT_CMD,
					       en);
	अगर (ret)
		वापस ret;

	ret = hclge_config_ppp_error_पूर्णांकerrupt(hdev, HCLGE_PPP_CMD1_INT_CMD,
					       en);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_पंचांग_hw_err_पूर्णांक(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	/* configure TM SCH hw errors */
	hclge_cmd_setup_basic_desc(&desc, HCLGE_TM_SCH_ECC_INT_EN, false);
	अगर (en)
		desc.data[0] = cpu_to_le32(HCLGE_TM_SCH_ECC_ERR_INT_EN);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(dev, "fail(%d) to configure TM SCH errors\n", ret);
		वापस ret;
	पूर्ण

	/* configure TM QCN hw errors */
	hclge_cmd_setup_basic_desc(&desc, HCLGE_TM_QCN_MEM_INT_CFG, false);
	अगर (en)
		desc.data[1] = cpu_to_le32(HCLGE_TM_QCN_MEM_ERR_INT_EN);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(dev,
			"fail(%d) to configure TM QCN mem errors\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_mac_err_पूर्णांक(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	/* configure MAC common error पूर्णांकerrupts */
	hclge_cmd_setup_basic_desc(&desc, HCLGE_MAC_COMMON_INT_EN, false);
	अगर (en)
		desc.data[0] = cpu_to_le32(HCLGE_MAC_COMMON_ERR_INT_EN);

	desc.data[1] = cpu_to_le32(HCLGE_MAC_COMMON_ERR_INT_EN_MASK);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(dev,
			"fail(%d) to configure MAC COMMON error intr\n", ret);

	वापस ret;
पूर्ण

पूर्णांक hclge_config_mac_tnl_पूर्णांक(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_TNL_INT_EN, false);
	अगर (en)
		desc.data[0] = cpu_to_le32(HCLGE_MAC_TNL_INT_EN);
	अन्यथा
		desc.data[0] = 0;

	desc.data[1] = cpu_to_le32(HCLGE_MAC_TNL_INT_EN_MASK);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_config_ppu_error_पूर्णांकerrupts(काष्ठा hclge_dev *hdev, u32 cmd,
					     bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc[2];
	पूर्णांक desc_num = 1;
	पूर्णांक ret;

	/* configure PPU error पूर्णांकerrupts */
	अगर (cmd == HCLGE_PPU_MPF_ECC_INT_CMD) अणु
		hclge_cmd_setup_basic_desc(&desc[0], cmd, false);
		desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		hclge_cmd_setup_basic_desc(&desc[1], cmd, false);
		अगर (en) अणु
			desc[0].data[0] =
				cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT0_EN);
			desc[0].data[1] =
				cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT1_EN);
			desc[1].data[3] =
				cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT3_EN);
			desc[1].data[4] =
				cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT2_EN);
		पूर्ण

		desc[1].data[0] =
			cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT0_EN_MASK);
		desc[1].data[1] =
			cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT1_EN_MASK);
		desc[1].data[2] =
			cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT2_EN_MASK);
		desc[1].data[3] |=
			cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT3_EN_MASK);
		desc_num = 2;
	पूर्ण अन्यथा अगर (cmd == HCLGE_PPU_MPF_OTHER_INT_CMD) अणु
		hclge_cmd_setup_basic_desc(&desc[0], cmd, false);
		अगर (en)
			desc[0].data[0] =
				cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT2_EN2);

		desc[0].data[2] =
			cpu_to_le32(HCLGE_PPU_MPF_ABNORMAL_INT2_EN2_MASK);
	पूर्ण अन्यथा अगर (cmd == HCLGE_PPU_PF_OTHER_INT_CMD) अणु
		hclge_cmd_setup_basic_desc(&desc[0], cmd, false);
		अगर (en)
			desc[0].data[0] =
				cpu_to_le32(HCLGE_PPU_PF_ABNORMAL_INT_EN);

		desc[0].data[2] =
			cpu_to_le32(HCLGE_PPU_PF_ABNORMAL_INT_EN_MASK);
	पूर्ण अन्यथा अणु
		dev_err(dev, "Invalid cmd to configure PPU error interrupts\n");
		वापस -EINVAL;
	पूर्ण

	ret = hclge_cmd_send(&hdev->hw, &desc[0], desc_num);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_ppu_hw_err_पूर्णांक(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	पूर्णांक ret;

	ret = hclge_config_ppu_error_पूर्णांकerrupts(hdev, HCLGE_PPU_MPF_ECC_INT_CMD,
						en);
	अगर (ret) अणु
		dev_err(dev, "fail(%d) to configure PPU MPF ECC error intr\n",
			ret);
		वापस ret;
	पूर्ण

	ret = hclge_config_ppu_error_पूर्णांकerrupts(hdev,
						HCLGE_PPU_MPF_OTHER_INT_CMD,
						en);
	अगर (ret) अणु
		dev_err(dev, "fail(%d) to configure PPU MPF other intr\n", ret);
		वापस ret;
	पूर्ण

	ret = hclge_config_ppu_error_पूर्णांकerrupts(hdev,
						HCLGE_PPU_PF_OTHER_INT_CMD, en);
	अगर (ret)
		dev_err(dev, "fail(%d) to configure PPU PF error interrupts\n",
			ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hclge_config_ssu_hw_err_पूर्णांक(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc[2];
	पूर्णांक ret;

	/* configure SSU ecc error पूर्णांकerrupts */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_SSU_ECC_INT_CMD, false);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_SSU_ECC_INT_CMD, false);
	अगर (en) अणु
		desc[0].data[0] = cpu_to_le32(HCLGE_SSU_1BIT_ECC_ERR_INT_EN);
		desc[0].data[1] =
			cpu_to_le32(HCLGE_SSU_MULTI_BIT_ECC_ERR_INT_EN);
		desc[0].data[4] = cpu_to_le32(HCLGE_SSU_BIT32_ECC_ERR_INT_EN);
	पूर्ण

	desc[1].data[0] = cpu_to_le32(HCLGE_SSU_1BIT_ECC_ERR_INT_EN_MASK);
	desc[1].data[1] = cpu_to_le32(HCLGE_SSU_MULTI_BIT_ECC_ERR_INT_EN_MASK);
	desc[1].data[2] = cpu_to_le32(HCLGE_SSU_BIT32_ECC_ERR_INT_EN_MASK);

	ret = hclge_cmd_send(&hdev->hw, &desc[0], 2);
	अगर (ret) अणु
		dev_err(dev,
			"fail(%d) to configure SSU ECC error interrupt\n", ret);
		वापस ret;
	पूर्ण

	/* configure SSU common error पूर्णांकerrupts */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_SSU_COMMON_INT_CMD, false);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_SSU_COMMON_INT_CMD, false);

	अगर (en) अणु
		अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2)
			desc[0].data[0] =
				cpu_to_le32(HCLGE_SSU_COMMON_INT_EN);
		अन्यथा
			desc[0].data[0] =
				cpu_to_le32(HCLGE_SSU_COMMON_INT_EN & ~BIT(5));
		desc[0].data[1] = cpu_to_le32(HCLGE_SSU_PORT_BASED_ERR_INT_EN);
		desc[0].data[2] =
			cpu_to_le32(HCLGE_SSU_FIFO_OVERFLOW_ERR_INT_EN);
	पूर्ण

	desc[1].data[0] = cpu_to_le32(HCLGE_SSU_COMMON_INT_EN_MASK |
				HCLGE_SSU_PORT_BASED_ERR_INT_EN_MASK);
	desc[1].data[1] = cpu_to_le32(HCLGE_SSU_FIFO_OVERFLOW_ERR_INT_EN_MASK);

	ret = hclge_cmd_send(&hdev->hw, &desc[0], 2);
	अगर (ret)
		dev_err(dev,
			"fail(%d) to configure SSU COMMON error intr\n", ret);

	वापस ret;
पूर्ण

/* hclge_query_bd_num: query number of buffer descriptors
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @is_ras: true क्रम ras, false क्रम msix
 * @mpf_bd_num: number of मुख्य PF पूर्णांकerrupt buffer descriptors
 * @pf_bd_num: number of not मुख्य PF पूर्णांकerrupt buffer descriptors
 *
 * This function querys number of mpf and pf buffer descriptors.
 */
अटल पूर्णांक hclge_query_bd_num(काष्ठा hclge_dev *hdev, bool is_ras,
			      u32 *mpf_bd_num, u32 *pf_bd_num)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	u32 mpf_min_bd_num, pf_min_bd_num;
	क्रमागत hclge_opcode_type opcode;
	काष्ठा hclge_desc desc_bd;
	पूर्णांक ret;

	अगर (is_ras) अणु
		opcode = HCLGE_QUERY_RAS_INT_STS_BD_NUM;
		mpf_min_bd_num = HCLGE_MPF_RAS_पूर्णांक_न्यून_BD_NUM;
		pf_min_bd_num = HCLGE_PF_RAS_पूर्णांक_न्यून_BD_NUM;
	पूर्ण अन्यथा अणु
		opcode = HCLGE_QUERY_MSIX_INT_STS_BD_NUM;
		mpf_min_bd_num = HCLGE_MPF_MSIX_पूर्णांक_न्यून_BD_NUM;
		pf_min_bd_num = HCLGE_PF_MSIX_पूर्णांक_न्यून_BD_NUM;
	पूर्ण

	hclge_cmd_setup_basic_desc(&desc_bd, opcode, true);
	ret = hclge_cmd_send(&hdev->hw, &desc_bd, 1);
	अगर (ret) अणु
		dev_err(dev, "fail(%d) to query msix int status bd num\n",
			ret);
		वापस ret;
	पूर्ण

	*mpf_bd_num = le32_to_cpu(desc_bd.data[0]);
	*pf_bd_num = le32_to_cpu(desc_bd.data[1]);
	अगर (*mpf_bd_num < mpf_min_bd_num || *pf_bd_num < pf_min_bd_num) अणु
		dev_err(dev, "Invalid bd num: mpf(%u), pf(%u)\n",
			*mpf_bd_num, *pf_bd_num);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* hclge_handle_mpf_ras_error: handle all मुख्य PF RAS errors
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @desc: descriptor क्रम describing the command
 * @num:  number of extended command काष्ठाures
 *
 * This function handles all the मुख्य PF RAS errors in the
 * hw रेजिस्टर/s using command.
 */
अटल पूर्णांक hclge_handle_mpf_ras_error(काष्ठा hclge_dev *hdev,
				      काष्ठा hclge_desc *desc,
				      पूर्णांक num)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = hdev->ae_dev;
	काष्ठा device *dev = &hdev->pdev->dev;
	__le32 *desc_data;
	u32 status;
	पूर्णांक ret;

	/* query all मुख्य PF RAS errors */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_QUERY_CLEAR_MPF_RAS_INT,
				   true);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], num);
	अगर (ret) अणु
		dev_err(dev, "query all mpf ras int cmd failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* log HNS common errors */
	status = le32_to_cpu(desc[0].data[0]);
	अगर (status)
		hclge_log_error(dev, "IMP_TCM_ECC_INT_STS",
				&hclge_imp_tcm_ecc_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	status = le32_to_cpu(desc[0].data[1]);
	अगर (status)
		hclge_log_error(dev, "CMDQ_MEM_ECC_INT_STS",
				&hclge_cmdq_nic_mem_ecc_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	अगर ((le32_to_cpu(desc[0].data[2])) & BIT(0))
		dev_warn(dev, "imp_rd_data_poison_err found\n");

	status = le32_to_cpu(desc[0].data[3]);
	अगर (status)
		hclge_log_error(dev, "TQP_INT_ECC_INT_STS",
				&hclge_tqp_पूर्णांक_ecc_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	status = le32_to_cpu(desc[0].data[4]);
	अगर (status)
		hclge_log_error(dev, "MSIX_ECC_INT_STS",
				&hclge_msix_sram_ecc_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	/* log SSU(Storage Switch Unit) errors */
	desc_data = (__le32 *)&desc[2];
	status = le32_to_cpu(*(desc_data + 2));
	अगर (status)
		hclge_log_error(dev, "SSU_ECC_MULTI_BIT_INT_0",
				&hclge_ssu_mem_ecc_err_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	status = le32_to_cpu(*(desc_data + 3)) & BIT(0);
	अगर (status) अणु
		dev_err(dev, "SSU_ECC_MULTI_BIT_INT_1 ssu_mem32_ecc_mbit_err found [error status=0x%x]\n",
			status);
		set_bit(HNAE3_GLOBAL_RESET, &ae_dev->hw_err_reset_req);
	पूर्ण

	status = le32_to_cpu(*(desc_data + 4)) & HCLGE_SSU_COMMON_ERR_INT_MASK;
	अगर (status)
		hclge_log_error(dev, "SSU_COMMON_ERR_INT",
				&hclge_ssu_com_err_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	/* log IGU(Ingress Unit) errors */
	desc_data = (__le32 *)&desc[3];
	status = le32_to_cpu(*desc_data) & HCLGE_IGU_INT_MASK;
	अगर (status)
		hclge_log_error(dev, "IGU_INT_STS",
				&hclge_igu_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	/* log PPP(Programmable Packet Process) errors */
	desc_data = (__le32 *)&desc[4];
	status = le32_to_cpu(*(desc_data + 1));
	अगर (status)
		hclge_log_error(dev, "PPP_MPF_ABNORMAL_INT_ST1",
				&hclge_ppp_mpf_abnormal_पूर्णांक_st1[0], status,
				&ae_dev->hw_err_reset_req);

	status = le32_to_cpu(*(desc_data + 3)) & HCLGE_PPP_MPF_INT_ST3_MASK;
	अगर (status)
		hclge_log_error(dev, "PPP_MPF_ABNORMAL_INT_ST3",
				&hclge_ppp_mpf_abnormal_पूर्णांक_st3[0], status,
				&ae_dev->hw_err_reset_req);

	/* log PPU(RCB) errors */
	desc_data = (__le32 *)&desc[5];
	status = le32_to_cpu(*(desc_data + 1));
	अगर (status) अणु
		dev_err(dev,
			"PPU_MPF_ABNORMAL_INT_ST1 rpu_rx_pkt_ecc_mbit_err found\n");
		set_bit(HNAE3_GLOBAL_RESET, &ae_dev->hw_err_reset_req);
	पूर्ण

	status = le32_to_cpu(*(desc_data + 2));
	अगर (status)
		hclge_log_error(dev, "PPU_MPF_ABNORMAL_INT_ST2",
				&hclge_ppu_mpf_abnormal_पूर्णांक_st2[0], status,
				&ae_dev->hw_err_reset_req);

	status = le32_to_cpu(*(desc_data + 3)) & HCLGE_PPU_MPF_INT_ST3_MASK;
	अगर (status)
		hclge_log_error(dev, "PPU_MPF_ABNORMAL_INT_ST3",
				&hclge_ppu_mpf_abnormal_पूर्णांक_st3[0], status,
				&ae_dev->hw_err_reset_req);

	/* log TM(Traffic Manager) errors */
	desc_data = (__le32 *)&desc[6];
	status = le32_to_cpu(*desc_data);
	अगर (status)
		hclge_log_error(dev, "TM_SCH_RINT",
				&hclge_पंचांग_sch_rपूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	/* log QCN(Quantized Congestion Control) errors */
	desc_data = (__le32 *)&desc[7];
	status = le32_to_cpu(*desc_data) & HCLGE_QCN_FIFO_INT_MASK;
	अगर (status)
		hclge_log_error(dev, "QCN_FIFO_RINT",
				&hclge_qcn_fअगरo_rपूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	status = le32_to_cpu(*(desc_data + 1)) & HCLGE_QCN_ECC_INT_MASK;
	अगर (status)
		hclge_log_error(dev, "QCN_ECC_RINT",
				&hclge_qcn_ecc_rपूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	/* log NCSI errors */
	desc_data = (__le32 *)&desc[9];
	status = le32_to_cpu(*desc_data) & HCLGE_NCSI_ECC_INT_MASK;
	अगर (status)
		hclge_log_error(dev, "NCSI_ECC_INT_RPT",
				&hclge_ncsi_err_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	/* clear all मुख्य PF RAS errors */
	hclge_cmd_reuse_desc(&desc[0], false);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], num);
	अगर (ret)
		dev_err(dev, "clear all mpf ras int cmd failed (%d)\n", ret);

	वापस ret;
पूर्ण

/* hclge_handle_pf_ras_error: handle all PF RAS errors
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @desc: descriptor क्रम describing the command
 * @num:  number of extended command काष्ठाures
 *
 * This function handles all the PF RAS errors in the
 * hw रेजिस्टर/s using command.
 */
अटल पूर्णांक hclge_handle_pf_ras_error(काष्ठा hclge_dev *hdev,
				     काष्ठा hclge_desc *desc,
				     पूर्णांक num)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = hdev->ae_dev;
	काष्ठा device *dev = &hdev->pdev->dev;
	__le32 *desc_data;
	u32 status;
	पूर्णांक ret;

	/* query all PF RAS errors */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_QUERY_CLEAR_PF_RAS_INT,
				   true);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], num);
	अगर (ret) अणु
		dev_err(dev, "query all pf ras int cmd failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* log SSU(Storage Switch Unit) errors */
	status = le32_to_cpu(desc[0].data[0]);
	अगर (status)
		hclge_log_error(dev, "SSU_PORT_BASED_ERR_INT",
				&hclge_ssu_port_based_err_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	status = le32_to_cpu(desc[0].data[1]);
	अगर (status)
		hclge_log_error(dev, "SSU_FIFO_OVERFLOW_INT",
				&hclge_ssu_fअगरo_overflow_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	status = le32_to_cpu(desc[0].data[2]);
	अगर (status)
		hclge_log_error(dev, "SSU_ETS_TCG_INT",
				&hclge_ssu_ets_tcg_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	/* log IGU(Ingress Unit) EGU(Egress Unit) TNL errors */
	desc_data = (__le32 *)&desc[1];
	status = le32_to_cpu(*desc_data) & HCLGE_IGU_EGU_TNL_INT_MASK;
	अगर (status)
		hclge_log_error(dev, "IGU_EGU_TNL_INT_STS",
				&hclge_igu_egu_tnl_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);

	/* log PPU(RCB) errors */
	desc_data = (__le32 *)&desc[3];
	status = le32_to_cpu(*desc_data) & HCLGE_PPU_PF_INT_RAS_MASK;
	अगर (status) अणु
		hclge_log_error(dev, "PPU_PF_ABNORMAL_INT_ST0",
				&hclge_ppu_pf_abnormal_पूर्णांक[0], status,
				&ae_dev->hw_err_reset_req);
		hclge_report_hw_error(hdev, HNAE3_PPU_POISON_ERROR);
	पूर्ण

	/* clear all PF RAS errors */
	hclge_cmd_reuse_desc(&desc[0], false);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], num);
	अगर (ret)
		dev_err(dev, "clear all pf ras int cmd failed (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_handle_all_ras_errors(काष्ठा hclge_dev *hdev)
अणु
	u32 mpf_bd_num, pf_bd_num, bd_num;
	काष्ठा hclge_desc *desc;
	पूर्णांक ret;

	/* query the number of रेजिस्टरs in the RAS पूर्णांक status */
	ret = hclge_query_bd_num(hdev, true, &mpf_bd_num, &pf_bd_num);
	अगर (ret)
		वापस ret;

	bd_num = max_t(u32, mpf_bd_num, pf_bd_num);
	desc = kसुस्मृति(bd_num, माप(काष्ठा hclge_desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	/* handle all मुख्य PF RAS errors */
	ret = hclge_handle_mpf_ras_error(hdev, desc, mpf_bd_num);
	अगर (ret) अणु
		kमुक्त(desc);
		वापस ret;
	पूर्ण
	स_रखो(desc, 0, bd_num * माप(काष्ठा hclge_desc));

	/* handle all PF RAS errors */
	ret = hclge_handle_pf_ras_error(hdev, desc, pf_bd_num);
	kमुक्त(desc);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_log_rocee_axi_error(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc[3];
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_QUERY_ROCEE_AXI_RAS_INFO_CMD,
				   true);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_QUERY_ROCEE_AXI_RAS_INFO_CMD,
				   true);
	hclge_cmd_setup_basic_desc(&desc[2], HCLGE_QUERY_ROCEE_AXI_RAS_INFO_CMD,
				   true);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	desc[1].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);

	ret = hclge_cmd_send(&hdev->hw, &desc[0], 3);
	अगर (ret) अणु
		dev_err(dev, "failed(%d) to query ROCEE AXI error sts\n", ret);
		वापस ret;
	पूर्ण

	dev_err(dev, "AXI1: %08X %08X %08X %08X %08X %08X\n",
		le32_to_cpu(desc[0].data[0]), le32_to_cpu(desc[0].data[1]),
		le32_to_cpu(desc[0].data[2]), le32_to_cpu(desc[0].data[3]),
		le32_to_cpu(desc[0].data[4]), le32_to_cpu(desc[0].data[5]));
	dev_err(dev, "AXI2: %08X %08X %08X %08X %08X %08X\n",
		le32_to_cpu(desc[1].data[0]), le32_to_cpu(desc[1].data[1]),
		le32_to_cpu(desc[1].data[2]), le32_to_cpu(desc[1].data[3]),
		le32_to_cpu(desc[1].data[4]), le32_to_cpu(desc[1].data[5]));
	dev_err(dev, "AXI3: %08X %08X %08X %08X\n",
		le32_to_cpu(desc[2].data[0]), le32_to_cpu(desc[2].data[1]),
		le32_to_cpu(desc[2].data[2]), le32_to_cpu(desc[2].data[3]));

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_log_rocee_ecc_error(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc[2];
	पूर्णांक ret;

	ret = hclge_cmd_query_error(hdev, &desc[0],
				    HCLGE_QUERY_ROCEE_ECC_RAS_INFO_CMD,
				    HCLGE_CMD_FLAG_NEXT);
	अगर (ret) अणु
		dev_err(dev, "failed(%d) to query ROCEE ECC error sts\n", ret);
		वापस ret;
	पूर्ण

	dev_err(dev, "ECC1: %08X %08X %08X %08X %08X %08X\n",
		le32_to_cpu(desc[0].data[0]), le32_to_cpu(desc[0].data[1]),
		le32_to_cpu(desc[0].data[2]), le32_to_cpu(desc[0].data[3]),
		le32_to_cpu(desc[0].data[4]), le32_to_cpu(desc[0].data[5]));
	dev_err(dev, "ECC2: %08X %08X %08X\n", le32_to_cpu(desc[1].data[0]),
		le32_to_cpu(desc[1].data[1]), le32_to_cpu(desc[1].data[2]));

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_log_rocee_ovf_error(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc[2];
	पूर्णांक ret;

	/* पढ़ो overflow error status */
	ret = hclge_cmd_query_error(hdev, &desc[0], HCLGE_ROCEE_PF_RAS_INT_CMD,
				    0);
	अगर (ret) अणु
		dev_err(dev, "failed(%d) to query ROCEE OVF error sts\n", ret);
		वापस ret;
	पूर्ण

	/* log overflow error */
	अगर (le32_to_cpu(desc[0].data[0]) & HCLGE_ROCEE_OVF_ERR_INT_MASK) अणु
		स्थिर काष्ठा hclge_hw_error *err;
		u32 err_sts;

		err = &hclge_rocee_qmm_ovf_err_पूर्णांक[0];
		err_sts = HCLGE_ROCEE_OVF_ERR_TYPE_MASK &
			  le32_to_cpu(desc[0].data[0]);
		जबतक (err->msg) अणु
			अगर (err->पूर्णांक_msk == err_sts) अणु
				dev_err(dev, "%s [error status=0x%x] found\n",
					err->msg,
					le32_to_cpu(desc[0].data[0]));
				अवरोध;
			पूर्ण
			err++;
		पूर्ण
	पूर्ण

	अगर (le32_to_cpu(desc[0].data[1]) & HCLGE_ROCEE_OVF_ERR_INT_MASK) अणु
		dev_err(dev, "ROCEE TSP OVF [error status=0x%x] found\n",
			le32_to_cpu(desc[0].data[1]));
	पूर्ण

	अगर (le32_to_cpu(desc[0].data[2]) & HCLGE_ROCEE_OVF_ERR_INT_MASK) अणु
		dev_err(dev, "ROCEE SCC OVF [error status=0x%x] found\n",
			le32_to_cpu(desc[0].data[2]));
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत hnae3_reset_type
hclge_log_and_clear_rocee_ras_error(काष्ठा hclge_dev *hdev)
अणु
	क्रमागत hnae3_reset_type reset_type = HNAE3_NONE_RESET;
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc[2];
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	/* पढ़ो RAS error पूर्णांकerrupt status */
	ret = hclge_cmd_query_error(hdev, &desc[0],
				    HCLGE_QUERY_CLEAR_ROCEE_RAS_INT, 0);
	अगर (ret) अणु
		dev_err(dev, "failed(%d) to query ROCEE RAS INT SRC\n", ret);
		/* reset everything क्रम now */
		वापस HNAE3_GLOBAL_RESET;
	पूर्ण

	status = le32_to_cpu(desc[0].data[0]);
	अगर (status & HCLGE_ROCEE_AXI_ERR_INT_MASK) अणु
		अगर (status & HCLGE_ROCEE_RERR_INT_MASK)
			dev_err(dev, "ROCEE RAS AXI rresp error\n");

		अगर (status & HCLGE_ROCEE_BERR_INT_MASK)
			dev_err(dev, "ROCEE RAS AXI bresp error\n");

		reset_type = HNAE3_FUNC_RESET;

		hclge_report_hw_error(hdev, HNAE3_ROCEE_AXI_RESP_ERROR);

		ret = hclge_log_rocee_axi_error(hdev);
		अगर (ret)
			वापस HNAE3_GLOBAL_RESET;
	पूर्ण

	अगर (status & HCLGE_ROCEE_ECC_INT_MASK) अणु
		dev_err(dev, "ROCEE RAS 2bit ECC error\n");
		reset_type = HNAE3_GLOBAL_RESET;

		ret = hclge_log_rocee_ecc_error(hdev);
		अगर (ret)
			वापस HNAE3_GLOBAL_RESET;
	पूर्ण

	अगर (status & HCLGE_ROCEE_OVF_INT_MASK) अणु
		ret = hclge_log_rocee_ovf_error(hdev);
		अगर (ret) अणु
			dev_err(dev, "failed(%d) to process ovf error\n", ret);
			/* reset everything क्रम now */
			वापस HNAE3_GLOBAL_RESET;
		पूर्ण
	पूर्ण

	/* clear error status */
	hclge_cmd_reuse_desc(&desc[0], false);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], 1);
	अगर (ret) अणु
		dev_err(dev, "failed(%d) to clear ROCEE RAS error\n", ret);
		/* reset everything क्रम now */
		वापस HNAE3_GLOBAL_RESET;
	पूर्ण

	वापस reset_type;
पूर्ण

पूर्णांक hclge_config_rocee_ras_पूर्णांकerrupt(काष्ठा hclge_dev *hdev, bool en)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2 ||
	    !hnae3_dev_roce_supported(hdev))
		वापस 0;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_CONFIG_ROCEE_RAS_INT_EN, false);
	अगर (en) अणु
		/* enable ROCEE hw error पूर्णांकerrupts */
		desc.data[0] = cpu_to_le32(HCLGE_ROCEE_RAS_NFE_INT_EN);
		desc.data[1] = cpu_to_le32(HCLGE_ROCEE_RAS_CE_INT_EN);

		hclge_log_and_clear_rocee_ras_error(hdev);
	पूर्ण
	desc.data[2] = cpu_to_le32(HCLGE_ROCEE_RAS_NFE_INT_EN_MASK);
	desc.data[3] = cpu_to_le32(HCLGE_ROCEE_RAS_CE_INT_EN_MASK);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(dev, "failed(%d) to config ROCEE RAS interrupt\n", ret);

	वापस ret;
पूर्ण

अटल व्योम hclge_handle_rocee_ras_error(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclge_dev *hdev = ae_dev->priv;
	क्रमागत hnae3_reset_type reset_type;

	अगर (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
		वापस;

	reset_type = hclge_log_and_clear_rocee_ras_error(hdev);
	अगर (reset_type != HNAE3_NONE_RESET)
		set_bit(reset_type, &ae_dev->hw_err_reset_req);
पूर्ण

अटल स्थिर काष्ठा hclge_hw_blk hw_blk[] = अणु
	अणु
	  .msk = BIT(0), .name = "IGU_EGU",
	  .config_err_पूर्णांक = hclge_config_igu_egu_hw_err_पूर्णांक,
	पूर्ण,
	अणु
	  .msk = BIT(1), .name = "PPP",
	  .config_err_पूर्णांक = hclge_config_ppp_hw_err_पूर्णांक,
	पूर्ण,
	अणु
	  .msk = BIT(2), .name = "SSU",
	  .config_err_पूर्णांक = hclge_config_ssu_hw_err_पूर्णांक,
	पूर्ण,
	अणु
	  .msk = BIT(3), .name = "PPU",
	  .config_err_पूर्णांक = hclge_config_ppu_hw_err_पूर्णांक,
	पूर्ण,
	अणु
	  .msk = BIT(4), .name = "TM",
	  .config_err_पूर्णांक = hclge_config_पंचांग_hw_err_पूर्णांक,
	पूर्ण,
	अणु
	  .msk = BIT(5), .name = "COMMON",
	  .config_err_पूर्णांक = hclge_config_common_hw_err_पूर्णांक,
	पूर्ण,
	अणु
	  .msk = BIT(8), .name = "MAC",
	  .config_err_पूर्णांक = hclge_config_mac_err_पूर्णांक,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

पूर्णांक hclge_config_nic_hw_error(काष्ठा hclge_dev *hdev, bool state)
अणु
	स्थिर काष्ठा hclge_hw_blk *module = hw_blk;
	पूर्णांक ret = 0;

	जबतक (module->name) अणु
		अगर (module->config_err_पूर्णांक) अणु
			ret = module->config_err_पूर्णांक(hdev, state);
			अगर (ret)
				वापस ret;
		पूर्ण
		module++;
	पूर्ण

	वापस ret;
पूर्ण

pci_ers_result_t hclge_handle_hw_ras_error(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclge_dev *hdev = ae_dev->priv;
	काष्ठा device *dev = &hdev->pdev->dev;
	u32 status;

	अगर (!test_bit(HCLGE_STATE_SERVICE_INITED, &hdev->state)) अणु
		dev_err(dev,
			"Can't recover - RAS error reported during dev init\n");
		वापस PCI_ERS_RESULT_NONE;
	पूर्ण

	status = hclge_पढ़ो_dev(&hdev->hw, HCLGE_RAS_PF_OTHER_INT_STS_REG);
	अगर (status & HCLGE_RAS_REG_NFE_MASK ||
	    status & HCLGE_RAS_REG_ROCEE_ERR_MASK)
		ae_dev->hw_err_reset_req = 0;
	अन्यथा
		जाओ out;

	/* Handling Non-fatal HNS RAS errors */
	अगर (status & HCLGE_RAS_REG_NFE_MASK) अणु
		dev_err(dev,
			"HNS Non-Fatal RAS error(status=0x%x) identified\n",
			status);
		hclge_handle_all_ras_errors(hdev);
	पूर्ण

	/* Handling Non-fatal Rocee RAS errors */
	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2 &&
	    status & HCLGE_RAS_REG_ROCEE_ERR_MASK) अणु
		dev_err(dev, "ROCEE Non-Fatal RAS error identified\n");
		hclge_handle_rocee_ras_error(ae_dev);
	पूर्ण

	अगर (ae_dev->hw_err_reset_req)
		वापस PCI_ERS_RESULT_NEED_RESET;

out:
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल पूर्णांक hclge_clear_hw_msix_error(काष्ठा hclge_dev *hdev,
				     काष्ठा hclge_desc *desc, bool is_mpf,
				     u32 bd_num)
अणु
	अगर (is_mpf)
		desc[0].opcode =
			cpu_to_le16(HCLGE_QUERY_CLEAR_ALL_MPF_MSIX_INT);
	अन्यथा
		desc[0].opcode = cpu_to_le16(HCLGE_QUERY_CLEAR_ALL_PF_MSIX_INT);

	desc[0].flag = cpu_to_le16(HCLGE_CMD_FLAG_NO_INTR | HCLGE_CMD_FLAG_IN);

	वापस hclge_cmd_send(&hdev->hw, &desc[0], bd_num);
पूर्ण

/* hclge_query_8bd_info: query inक्रमmation about over_8bd_nfe_err
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @vf_id: Index of the भव function with error
 * @q_id: Physical index of the queue with error
 *
 * This function get specअगरic index of queue and function which causes
 * over_8bd_nfe_err by using command. If vf_id is 0, it means error is
 * caused by PF instead of VF.
 */
अटल पूर्णांक hclge_query_over_8bd_err_info(काष्ठा hclge_dev *hdev, u16 *vf_id,
					 u16 *q_id)
अणु
	काष्ठा hclge_query_ppu_pf_other_पूर्णांक_dfx_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_PPU_PF_OTHER_INT_DFX, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		वापस ret;

	req = (काष्ठा hclge_query_ppu_pf_other_पूर्णांक_dfx_cmd *)desc.data;
	*vf_id = le16_to_cpu(req->over_8bd_no_fe_vf_id);
	*q_id = le16_to_cpu(req->over_8bd_no_fe_qid);

	वापस 0;
पूर्ण

/* hclge_handle_over_8bd_err: handle MSI-X error named over_8bd_nfe_err
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @reset_requests: reset level that we need to trigger later
 *
 * over_8bd_nfe_err is a special MSI-X because it may caused by a VF, in
 * that हाल, we need to trigger VF reset. Otherwise, a PF reset is needed.
 */
अटल व्योम hclge_handle_over_8bd_err(काष्ठा hclge_dev *hdev,
				      अचिन्हित दीर्घ *reset_requests)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	u16 vf_id;
	u16 q_id;
	पूर्णांक ret;

	ret = hclge_query_over_8bd_err_info(hdev, &vf_id, &q_id);
	अगर (ret) अणु
		dev_err(dev, "fail(%d) to query over_8bd_no_fe info\n",
			ret);
		वापस;
	पूर्ण

	dev_err(dev, "PPU_PF_ABNORMAL_INT_ST over_8bd_no_fe found, vf_id(%u), queue_id(%u)\n",
		vf_id, q_id);

	अगर (vf_id) अणु
		अगर (vf_id >= hdev->num_alloc_vport) अणु
			dev_err(dev, "invalid vf id(%u)\n", vf_id);
			वापस;
		पूर्ण

		/* If we need to trigger other reset whose level is higher
		 * than HNAE3_VF_FUNC_RESET, no need to trigger a VF reset
		 * here.
		 */
		अगर (*reset_requests != 0)
			वापस;

		ret = hclge_inक्रमm_reset_निश्चित_to_vf(&hdev->vport[vf_id]);
		अगर (ret)
			dev_err(dev, "inform reset to vf(%u) failed %d!\n",
				hdev->vport->vport_id, ret);
	पूर्ण अन्यथा अणु
		set_bit(HNAE3_FUNC_RESET, reset_requests);
	पूर्ण
पूर्ण

/* hclge_handle_mpf_msix_error: handle all मुख्य PF MSI-X errors
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @desc: descriptor क्रम describing the command
 * @mpf_bd_num: number of extended command काष्ठाures
 * @reset_requests: record of the reset level that we need
 *
 * This function handles all the मुख्य PF MSI-X errors in the hw रेजिस्टर/s
 * using command.
 */
अटल पूर्णांक hclge_handle_mpf_msix_error(काष्ठा hclge_dev *hdev,
				       काष्ठा hclge_desc *desc,
				       पूर्णांक mpf_bd_num,
				       अचिन्हित दीर्घ *reset_requests)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	__le32 *desc_data;
	u32 status;
	पूर्णांक ret;
	/* query all मुख्य PF MSIx errors */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_QUERY_CLEAR_ALL_MPF_MSIX_INT,
				   true);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], mpf_bd_num);
	अगर (ret) अणु
		dev_err(dev, "query all mpf msix int cmd failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* log MAC errors */
	desc_data = (__le32 *)&desc[1];
	status = le32_to_cpu(*desc_data);
	अगर (status)
		hclge_log_error(dev, "MAC_AFIFO_TNL_INT_R",
				&hclge_mac_afअगरo_tnl_पूर्णांक[0], status,
				reset_requests);

	/* log PPU(RCB) MPF errors */
	desc_data = (__le32 *)&desc[5];
	status = le32_to_cpu(*(desc_data + 2)) &
			HCLGE_PPU_MPF_INT_ST2_MSIX_MASK;
	अगर (status)
		dev_err(dev, "PPU_MPF_ABNORMAL_INT_ST2 rx_q_search_miss found [dfx status=0x%x\n]",
			status);

	/* clear all मुख्य PF MSIx errors */
	ret = hclge_clear_hw_msix_error(hdev, desc, true, mpf_bd_num);
	अगर (ret)
		dev_err(dev, "clear all mpf msix int cmd failed (%d)\n", ret);

	वापस ret;
पूर्ण

/* hclge_handle_pf_msix_error: handle all PF MSI-X errors
 * @hdev: poपूर्णांकer to काष्ठा hclge_dev
 * @desc: descriptor क्रम describing the command
 * @mpf_bd_num: number of extended command काष्ठाures
 * @reset_requests: record of the reset level that we need
 *
 * This function handles all the PF MSI-X errors in the hw रेजिस्टर/s using
 * command.
 */
अटल पूर्णांक hclge_handle_pf_msix_error(काष्ठा hclge_dev *hdev,
				      काष्ठा hclge_desc *desc,
				      पूर्णांक pf_bd_num,
				      अचिन्हित दीर्घ *reset_requests)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;
	__le32 *desc_data;
	u32 status;
	पूर्णांक ret;

	/* query all PF MSIx errors */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_QUERY_CLEAR_ALL_PF_MSIX_INT,
				   true);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], pf_bd_num);
	अगर (ret) अणु
		dev_err(dev, "query all pf msix int cmd failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* log SSU PF errors */
	status = le32_to_cpu(desc[0].data[0]) & HCLGE_SSU_PORT_INT_MSIX_MASK;
	अगर (status)
		hclge_log_error(dev, "SSU_PORT_BASED_ERR_INT",
				&hclge_ssu_port_based_pf_पूर्णांक[0],
				status, reset_requests);

	/* पढ़ो and log PPP PF errors */
	desc_data = (__le32 *)&desc[2];
	status = le32_to_cpu(*desc_data);
	अगर (status)
		hclge_log_error(dev, "PPP_PF_ABNORMAL_INT_ST0",
				&hclge_ppp_pf_abnormal_पूर्णांक[0],
				status, reset_requests);

	/* log PPU(RCB) PF errors */
	desc_data = (__le32 *)&desc[3];
	status = le32_to_cpu(*desc_data) & HCLGE_PPU_PF_INT_MSIX_MASK;
	अगर (status)
		hclge_log_error(dev, "PPU_PF_ABNORMAL_INT_ST",
				&hclge_ppu_pf_abnormal_पूर्णांक[0],
				status, reset_requests);

	status = le32_to_cpu(*desc_data) & HCLGE_PPU_PF_OVER_8BD_ERR_MASK;
	अगर (status)
		hclge_handle_over_8bd_err(hdev, reset_requests);

	/* clear all PF MSIx errors */
	ret = hclge_clear_hw_msix_error(hdev, desc, false, pf_bd_num);
	अगर (ret)
		dev_err(dev, "clear all pf msix int cmd failed (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_handle_all_hw_msix_error(काष्ठा hclge_dev *hdev,
					  अचिन्हित दीर्घ *reset_requests)
अणु
	काष्ठा hclge_mac_tnl_stats mac_tnl_stats;
	काष्ठा device *dev = &hdev->pdev->dev;
	u32 mpf_bd_num, pf_bd_num, bd_num;
	काष्ठा hclge_desc *desc;
	u32 status;
	पूर्णांक ret;

	/* query the number of bds क्रम the MSIx पूर्णांक status */
	ret = hclge_query_bd_num(hdev, false, &mpf_bd_num, &pf_bd_num);
	अगर (ret)
		जाओ out;

	bd_num = max_t(u32, mpf_bd_num, pf_bd_num);
	desc = kसुस्मृति(bd_num, माप(काष्ठा hclge_desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	ret = hclge_handle_mpf_msix_error(hdev, desc, mpf_bd_num,
					  reset_requests);
	अगर (ret)
		जाओ msi_error;

	स_रखो(desc, 0, bd_num * माप(काष्ठा hclge_desc));
	ret = hclge_handle_pf_msix_error(hdev, desc, pf_bd_num, reset_requests);
	अगर (ret)
		जाओ msi_error;

	/* query and clear mac tnl पूर्णांकerruptions */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_QUERY_MAC_TNL_INT,
				   true);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], 1);
	अगर (ret) अणु
		dev_err(dev, "query mac tnl int cmd failed (%d)\n", ret);
		जाओ msi_error;
	पूर्ण

	status = le32_to_cpu(desc->data[0]);
	अगर (status) अणु
		/* When mac tnl पूर्णांकerrupt occurs, we record current समय and
		 * रेजिस्टर status here in a fअगरo, then clear the status. So
		 * that अगर link status changes suddenly at some समय, we can
		 * query them by debugfs.
		 */
		mac_tnl_stats.समय = local_घड़ी();
		mac_tnl_stats.status = status;
		kfअगरo_put(&hdev->mac_tnl_log, mac_tnl_stats);
		ret = hclge_clear_mac_tnl_पूर्णांक(hdev);
		अगर (ret)
			dev_err(dev, "clear mac tnl int failed (%d)\n", ret);
	पूर्ण

msi_error:
	kमुक्त(desc);
out:
	वापस ret;
पूर्ण

पूर्णांक hclge_handle_hw_msix_error(काष्ठा hclge_dev *hdev,
			       अचिन्हित दीर्घ *reset_requests)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;

	अगर (!test_bit(HCLGE_STATE_SERVICE_INITED, &hdev->state)) अणु
		dev_err(dev,
			"Can't handle - MSIx error reported during dev init\n");
		वापस 0;
	पूर्ण

	वापस hclge_handle_all_hw_msix_error(hdev, reset_requests);
पूर्ण

व्योम hclge_handle_all_hns_hw_errors(काष्ठा hnae3_ae_dev *ae_dev)
अणु
#घोषणा HCLGE_DESC_NO_DATA_LEN 8

	काष्ठा hclge_dev *hdev = ae_dev->priv;
	काष्ठा device *dev = &hdev->pdev->dev;
	u32 mpf_bd_num, pf_bd_num, bd_num;
	काष्ठा hclge_desc *desc;
	u32 status;
	पूर्णांक ret;

	ae_dev->hw_err_reset_req = 0;
	status = hclge_पढ़ो_dev(&hdev->hw, HCLGE_RAS_PF_OTHER_INT_STS_REG);

	/* query the number of bds क्रम the MSIx पूर्णांक status */
	ret = hclge_query_bd_num(hdev, false, &mpf_bd_num, &pf_bd_num);
	अगर (ret)
		वापस;

	bd_num = max_t(u32, mpf_bd_num, pf_bd_num);
	desc = kसुस्मृति(bd_num, माप(काष्ठा hclge_desc), GFP_KERNEL);
	अगर (!desc)
		वापस;

	/* Clear HNS hw errors reported through msix  */
	स_रखो(&desc[0].data[0], 0xFF, mpf_bd_num * माप(काष्ठा hclge_desc) -
	       HCLGE_DESC_NO_DATA_LEN);
	ret = hclge_clear_hw_msix_error(hdev, desc, true, mpf_bd_num);
	अगर (ret) अणु
		dev_err(dev, "fail(%d) to clear mpf msix int during init\n",
			ret);
		जाओ msi_error;
	पूर्ण

	स_रखो(&desc[0].data[0], 0xFF, pf_bd_num * माप(काष्ठा hclge_desc) -
	       HCLGE_DESC_NO_DATA_LEN);
	ret = hclge_clear_hw_msix_error(hdev, desc, false, pf_bd_num);
	अगर (ret) अणु
		dev_err(dev, "fail(%d) to clear pf msix int during init\n",
			ret);
		जाओ msi_error;
	पूर्ण

	/* Handle Non-fatal HNS RAS errors */
	अगर (status & HCLGE_RAS_REG_NFE_MASK) अणु
		dev_err(dev, "HNS hw error(RAS) identified during init\n");
		hclge_handle_all_ras_errors(hdev);
	पूर्ण

msi_error:
	kमुक्त(desc);
पूर्ण
