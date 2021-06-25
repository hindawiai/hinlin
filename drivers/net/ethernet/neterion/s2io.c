<शैली गुरु>
/************************************************************************
 * s2io.c: A Linux PCI-X Ethernet driver क्रम Neterion 10GbE Server NIC
 * Copyright(c) 2002-2010 Exar Corp.
 *
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice.  This file is not
 * a complete program and may only be used when the entire operating
 * प्रणाली is licensed under the GPL.
 * See the file COPYING in this distribution क्रम more inक्रमmation.
 *
 * Credits:
 * Jeff Garzik		: For poपूर्णांकing out the improper error condition
 *			  check in the s2io_xmit routine and also some
 *			  issues in the Tx watch करोg function. Also क्रम
 *			  patiently answering all those innumerable
 *			  questions regaring the 2.6 porting issues.
 * Stephen Hemminger	: Providing proper 2.6 porting mechanism क्रम some
 *			  macros available only in 2.6 Kernel.
 * Francois Romieu	: For poपूर्णांकing out all code part that were
 *			  deprecated and also styling related comments.
 * Grant Grundler	: For helping me get rid of some Architecture
 *			  dependent code.
 * Christopher Hellwig	: Some more 2.6 specअगरic issues in the driver.
 *
 * The module loadable parameters that are supported by the driver and a brief
 * explanation of all the variables.
 *
 * rx_ring_num : This can be used to program the number of receive rings used
 * in the driver.
 * rx_ring_sz: This defines the number of receive blocks each ring can have.
 *     This is also an array of size 8.
 * rx_ring_mode: This defines the operation mode of all 8 rings. The valid
 *		values are 1, 2.
 * tx_fअगरo_num: This defines the number of Tx FIFOs thats used पूर्णांक the driver.
 * tx_fअगरo_len: This too is an array of 8. Each element defines the number of
 * Tx descriptors that can be associated with each corresponding FIFO.
 * पूर्णांकr_type: This defines the type of पूर्णांकerrupt. The values can be 0(INTA),
 *     2(MSI_X). Default value is '2(MSI_X)'
 * lro_max_pkts: This parameter defines maximum number of packets can be
 *     aggregated as a single large packet
 * napi: This parameter used to enable/disable NAPI (polling Rx)
 *     Possible values '1' for enable and '0' for disable. Default is '1'
 * vlan_tag_strip: This can be used to enable or disable vlan stripping.
 *                 Possible values '1' for enable , '0' क्रम disable.
 *                 Default is '2' - which means disable in promisc mode
 *                 and enable in non-promiscuous mode.
 * multiq: This parameter used to enable/disable MULTIQUEUE support.
 *      Possible values '1' for enable and '0' for disable. Default is '0'
 ************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/समयx.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/slab.h>
#समावेश <linux/prefetch.h>
#समावेश <net/tcp.h>
#समावेश <net/checksum.h>

#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/irq.h>

/* local include */
#समावेश "s2io.h"
#समावेश "s2io-regs.h"

#घोषणा DRV_VERSION "2.0.26.28"

/* S2io Driver name & version. */
अटल स्थिर अक्षर s2io_driver_name[] = "Neterion";
अटल स्थिर अक्षर s2io_driver_version[] = DRV_VERSION;

अटल स्थिर पूर्णांक rxd_size[2] = अणु32, 48पूर्ण;
अटल स्थिर पूर्णांक rxd_count[2] = अणु127, 85पूर्ण;

अटल अंतरभूत पूर्णांक RXD_IS_UP2DT(काष्ठा RxD_t *rxdp)
अणु
	पूर्णांक ret;

	ret = ((!(rxdp->Control_1 & RXD_OWN_XENA)) &&
	       (GET_RXD_MARKER(rxdp->Control_2) != THE_RXD_MARK));

	वापस ret;
पूर्ण

/*
 * Cards with following subप्रणाली_id have a link state indication
 * problem, 600B, 600C, 600D, 640B, 640C and 640D.
 * macro below identअगरies these cards given the subप्रणाली_id.
 */
#घोषणा CARDS_WITH_FAULTY_LINK_INDICATORS(dev_type, subid)		\
	(dev_type == XFRAME_I_DEVICE) ?					\
	((((subid >= 0x600B) && (subid <= 0x600D)) ||			\
	  ((subid >= 0x640B) && (subid <= 0x640D))) ? 1 : 0) : 0

#घोषणा LINK_IS_UP(val64) (!(val64 & (ADAPTER_STATUS_RMAC_REMOTE_FAULT | \
				      ADAPTER_STATUS_RMAC_LOCAL_FAULT)))

अटल अंतरभूत पूर्णांक is_s2io_card_up(स्थिर काष्ठा s2io_nic *sp)
अणु
	वापस test_bit(__S2IO_STATE_CARD_UP, &sp->state);
पूर्ण

/* Ethtool related variables and Macros. */
अटल स्थिर अक्षर s2io_gstrings[][ETH_GSTRING_LEN] = अणु
	"Register test\t(offline)",
	"Eeprom test\t(offline)",
	"Link test\t(online)",
	"RLDRAM test\t(offline)",
	"BIST Test\t(offline)"
पूर्ण;

अटल स्थिर अक्षर ethtool_xena_stats_keys[][ETH_GSTRING_LEN] = अणु
	अणु"tmac_frms"पूर्ण,
	अणु"tmac_data_octets"पूर्ण,
	अणु"tmac_drop_frms"पूर्ण,
	अणु"tmac_mcst_frms"पूर्ण,
	अणु"tmac_bcst_frms"पूर्ण,
	अणु"tmac_pause_ctrl_frms"पूर्ण,
	अणु"tmac_ttl_octets"पूर्ण,
	अणु"tmac_ucst_frms"पूर्ण,
	अणु"tmac_nucst_frms"पूर्ण,
	अणु"tmac_any_err_frms"पूर्ण,
	अणु"tmac_ttl_less_fb_octets"पूर्ण,
	अणु"tmac_vld_ip_octets"पूर्ण,
	अणु"tmac_vld_ip"पूर्ण,
	अणु"tmac_drop_ip"पूर्ण,
	अणु"tmac_icmp"पूर्ण,
	अणु"tmac_rst_tcp"पूर्ण,
	अणु"tmac_tcp"पूर्ण,
	अणु"tmac_udp"पूर्ण,
	अणु"rmac_vld_frms"पूर्ण,
	अणु"rmac_data_octets"पूर्ण,
	अणु"rmac_fcs_err_frms"पूर्ण,
	अणु"rmac_drop_frms"पूर्ण,
	अणु"rmac_vld_mcst_frms"पूर्ण,
	अणु"rmac_vld_bcst_frms"पूर्ण,
	अणु"rmac_in_rng_len_err_frms"पूर्ण,
	अणु"rmac_out_rng_len_err_frms"पूर्ण,
	अणु"rmac_long_frms"पूर्ण,
	अणु"rmac_pause_ctrl_frms"पूर्ण,
	अणु"rmac_unsup_ctrl_frms"पूर्ण,
	अणु"rmac_ttl_octets"पूर्ण,
	अणु"rmac_accepted_ucst_frms"पूर्ण,
	अणु"rmac_accepted_nucst_frms"पूर्ण,
	अणु"rmac_discarded_frms"पूर्ण,
	अणु"rmac_drop_events"पूर्ण,
	अणु"rmac_ttl_less_fb_octets"पूर्ण,
	अणु"rmac_ttl_frms"पूर्ण,
	अणु"rmac_usized_frms"पूर्ण,
	अणु"rmac_osized_frms"पूर्ण,
	अणु"rmac_frag_frms"पूर्ण,
	अणु"rmac_jabber_frms"पूर्ण,
	अणु"rmac_ttl_64_frms"पूर्ण,
	अणु"rmac_ttl_65_127_frms"पूर्ण,
	अणु"rmac_ttl_128_255_frms"पूर्ण,
	अणु"rmac_ttl_256_511_frms"पूर्ण,
	अणु"rmac_ttl_512_1023_frms"पूर्ण,
	अणु"rmac_ttl_1024_1518_frms"पूर्ण,
	अणु"rmac_ip"पूर्ण,
	अणु"rmac_ip_octets"पूर्ण,
	अणु"rmac_hdr_err_ip"पूर्ण,
	अणु"rmac_drop_ip"पूर्ण,
	अणु"rmac_icmp"पूर्ण,
	अणु"rmac_tcp"पूर्ण,
	अणु"rmac_udp"पूर्ण,
	अणु"rmac_err_drp_udp"पूर्ण,
	अणु"rmac_xgmii_err_sym"पूर्ण,
	अणु"rmac_frms_q0"पूर्ण,
	अणु"rmac_frms_q1"पूर्ण,
	अणु"rmac_frms_q2"पूर्ण,
	अणु"rmac_frms_q3"पूर्ण,
	अणु"rmac_frms_q4"पूर्ण,
	अणु"rmac_frms_q5"पूर्ण,
	अणु"rmac_frms_q6"पूर्ण,
	अणु"rmac_frms_q7"पूर्ण,
	अणु"rmac_full_q0"पूर्ण,
	अणु"rmac_full_q1"पूर्ण,
	अणु"rmac_full_q2"पूर्ण,
	अणु"rmac_full_q3"पूर्ण,
	अणु"rmac_full_q4"पूर्ण,
	अणु"rmac_full_q5"पूर्ण,
	अणु"rmac_full_q6"पूर्ण,
	अणु"rmac_full_q7"पूर्ण,
	अणु"rmac_pause_cnt"पूर्ण,
	अणु"rmac_xgmii_data_err_cnt"पूर्ण,
	अणु"rmac_xgmii_ctrl_err_cnt"पूर्ण,
	अणु"rmac_accepted_ip"पूर्ण,
	अणु"rmac_err_tcp"पूर्ण,
	अणु"rd_req_cnt"पूर्ण,
	अणु"new_rd_req_cnt"पूर्ण,
	अणु"new_rd_req_rtry_cnt"पूर्ण,
	अणु"rd_rtry_cnt"पूर्ण,
	अणु"wr_rtry_rd_ack_cnt"पूर्ण,
	अणु"wr_req_cnt"पूर्ण,
	अणु"new_wr_req_cnt"पूर्ण,
	अणु"new_wr_req_rtry_cnt"पूर्ण,
	अणु"wr_rtry_cnt"पूर्ण,
	अणु"wr_disc_cnt"पूर्ण,
	अणु"rd_rtry_wr_ack_cnt"पूर्ण,
	अणु"txp_wr_cnt"पूर्ण,
	अणु"txd_rd_cnt"पूर्ण,
	अणु"txd_wr_cnt"पूर्ण,
	अणु"rxd_rd_cnt"पूर्ण,
	अणु"rxd_wr_cnt"पूर्ण,
	अणु"txf_rd_cnt"पूर्ण,
	अणु"rxf_wr_cnt"पूर्ण
पूर्ण;

अटल स्थिर अक्षर ethtool_enhanced_stats_keys[][ETH_GSTRING_LEN] = अणु
	अणु"rmac_ttl_1519_4095_frms"पूर्ण,
	अणु"rmac_ttl_4096_8191_frms"पूर्ण,
	अणु"rmac_ttl_8192_max_frms"पूर्ण,
	अणु"rmac_ttl_gt_max_frms"पूर्ण,
	अणु"rmac_osized_alt_frms"पूर्ण,
	अणु"rmac_jabber_alt_frms"पूर्ण,
	अणु"rmac_gt_max_alt_frms"पूर्ण,
	अणु"rmac_vlan_frms"पूर्ण,
	अणु"rmac_len_discard"पूर्ण,
	अणु"rmac_fcs_discard"पूर्ण,
	अणु"rmac_pf_discard"पूर्ण,
	अणु"rmac_da_discard"पूर्ण,
	अणु"rmac_red_discard"पूर्ण,
	अणु"rmac_rts_discard"पूर्ण,
	अणु"rmac_ingm_full_discard"पूर्ण,
	अणु"link_fault_cnt"पूर्ण
पूर्ण;

अटल स्थिर अक्षर ethtool_driver_stats_keys[][ETH_GSTRING_LEN] = अणु
	अणु"\n DRIVER STATISTICS"पूर्ण,
	अणु"single_bit_ecc_errs"पूर्ण,
	अणु"double_bit_ecc_errs"पूर्ण,
	अणु"parity_err_cnt"पूर्ण,
	अणु"serious_err_cnt"पूर्ण,
	अणु"soft_reset_cnt"पूर्ण,
	अणु"fifo_full_cnt"पूर्ण,
	अणु"ring_0_full_cnt"पूर्ण,
	अणु"ring_1_full_cnt"पूर्ण,
	अणु"ring_2_full_cnt"पूर्ण,
	अणु"ring_3_full_cnt"पूर्ण,
	अणु"ring_4_full_cnt"पूर्ण,
	अणु"ring_5_full_cnt"पूर्ण,
	अणु"ring_6_full_cnt"पूर्ण,
	अणु"ring_7_full_cnt"पूर्ण,
	अणु"alarm_transceiver_temp_high"पूर्ण,
	अणु"alarm_transceiver_temp_low"पूर्ण,
	अणु"alarm_laser_bias_current_high"पूर्ण,
	अणु"alarm_laser_bias_current_low"पूर्ण,
	अणु"alarm_laser_output_power_high"पूर्ण,
	अणु"alarm_laser_output_power_low"पूर्ण,
	अणु"warn_transceiver_temp_high"पूर्ण,
	अणु"warn_transceiver_temp_low"पूर्ण,
	अणु"warn_laser_bias_current_high"पूर्ण,
	अणु"warn_laser_bias_current_low"पूर्ण,
	अणु"warn_laser_output_power_high"पूर्ण,
	अणु"warn_laser_output_power_low"पूर्ण,
	अणु"lro_aggregated_pkts"पूर्ण,
	अणु"lro_flush_both_count"पूर्ण,
	अणु"lro_out_of_sequence_pkts"पूर्ण,
	अणु"lro_flush_due_to_max_pkts"पूर्ण,
	अणु"lro_avg_aggr_pkts"पूर्ण,
	अणु"mem_alloc_fail_cnt"पूर्ण,
	अणु"pci_map_fail_cnt"पूर्ण,
	अणु"watchdog_timer_cnt"पूर्ण,
	अणु"mem_allocated"पूर्ण,
	अणु"mem_freed"पूर्ण,
	अणु"link_up_cnt"पूर्ण,
	अणु"link_down_cnt"पूर्ण,
	अणु"link_up_time"पूर्ण,
	अणु"link_down_time"पूर्ण,
	अणु"tx_tcode_buf_abort_cnt"पूर्ण,
	अणु"tx_tcode_desc_abort_cnt"पूर्ण,
	अणु"tx_tcode_parity_err_cnt"पूर्ण,
	अणु"tx_tcode_link_loss_cnt"पूर्ण,
	अणु"tx_tcode_list_proc_err_cnt"पूर्ण,
	अणु"rx_tcode_parity_err_cnt"पूर्ण,
	अणु"rx_tcode_abort_cnt"पूर्ण,
	अणु"rx_tcode_parity_abort_cnt"पूर्ण,
	अणु"rx_tcode_rda_fail_cnt"पूर्ण,
	अणु"rx_tcode_unkn_prot_cnt"पूर्ण,
	अणु"rx_tcode_fcs_err_cnt"पूर्ण,
	अणु"rx_tcode_buf_size_err_cnt"पूर्ण,
	अणु"rx_tcode_rxd_corrupt_cnt"पूर्ण,
	अणु"rx_tcode_unkn_err_cnt"पूर्ण,
	अणु"tda_err_cnt"पूर्ण,
	अणु"pfc_err_cnt"पूर्ण,
	अणु"pcc_err_cnt"पूर्ण,
	अणु"tti_err_cnt"पूर्ण,
	अणु"tpa_err_cnt"पूर्ण,
	अणु"sm_err_cnt"पूर्ण,
	अणु"lso_err_cnt"पूर्ण,
	अणु"mac_tmac_err_cnt"पूर्ण,
	अणु"mac_rmac_err_cnt"पूर्ण,
	अणु"xgxs_txgxs_err_cnt"पूर्ण,
	अणु"xgxs_rxgxs_err_cnt"पूर्ण,
	अणु"rc_err_cnt"पूर्ण,
	अणु"prc_pcix_err_cnt"पूर्ण,
	अणु"rpa_err_cnt"पूर्ण,
	अणु"rda_err_cnt"पूर्ण,
	अणु"rti_err_cnt"पूर्ण,
	अणु"mc_err_cnt"पूर्ण
पूर्ण;

#घोषणा S2IO_XENA_STAT_LEN	ARRAY_SIZE(ethtool_xena_stats_keys)
#घोषणा S2IO_ENHANCED_STAT_LEN	ARRAY_SIZE(ethtool_enhanced_stats_keys)
#घोषणा S2IO_DRIVER_STAT_LEN	ARRAY_SIZE(ethtool_driver_stats_keys)

#घोषणा XFRAME_I_STAT_LEN (S2IO_XENA_STAT_LEN + S2IO_DRIVER_STAT_LEN)
#घोषणा XFRAME_II_STAT_LEN (XFRAME_I_STAT_LEN + S2IO_ENHANCED_STAT_LEN)

#घोषणा XFRAME_I_STAT_STRINGS_LEN (XFRAME_I_STAT_LEN * ETH_GSTRING_LEN)
#घोषणा XFRAME_II_STAT_STRINGS_LEN (XFRAME_II_STAT_LEN * ETH_GSTRING_LEN)

#घोषणा S2IO_TEST_LEN	ARRAY_SIZE(s2io_gstrings)
#घोषणा S2IO_STRINGS_LEN	(S2IO_TEST_LEN * ETH_GSTRING_LEN)

/* copy mac addr to def_mac_addr array */
अटल व्योम करो_s2io_copy_mac_addr(काष्ठा s2io_nic *sp, पूर्णांक offset, u64 mac_addr)
अणु
	sp->def_mac_addr[offset].mac_addr[5] = (u8) (mac_addr);
	sp->def_mac_addr[offset].mac_addr[4] = (u8) (mac_addr >> 8);
	sp->def_mac_addr[offset].mac_addr[3] = (u8) (mac_addr >> 16);
	sp->def_mac_addr[offset].mac_addr[2] = (u8) (mac_addr >> 24);
	sp->def_mac_addr[offset].mac_addr[1] = (u8) (mac_addr >> 32);
	sp->def_mac_addr[offset].mac_addr[0] = (u8) (mac_addr >> 40);
पूर्ण

/*
 * Constants to be programmed पूर्णांकo the Xena's रेजिस्टरs, to configure
 * the XAUI.
 */

#घोषणा	END_SIGN	0x0
अटल स्थिर u64 herc_act_dtx_cfg[] = अणु
	/* Set address */
	0x8000051536750000ULL, 0x80000515367500E0ULL,
	/* Write data */
	0x8000051536750004ULL, 0x80000515367500E4ULL,
	/* Set address */
	0x80010515003F0000ULL, 0x80010515003F00E0ULL,
	/* Write data */
	0x80010515003F0004ULL, 0x80010515003F00E4ULL,
	/* Set address */
	0x801205150D440000ULL, 0x801205150D4400E0ULL,
	/* Write data */
	0x801205150D440004ULL, 0x801205150D4400E4ULL,
	/* Set address */
	0x80020515F2100000ULL, 0x80020515F21000E0ULL,
	/* Write data */
	0x80020515F2100004ULL, 0x80020515F21000E4ULL,
	/* Done */
	END_SIGN
पूर्ण;

अटल स्थिर u64 xena_dtx_cfg[] = अणु
	/* Set address */
	0x8000051500000000ULL, 0x80000515000000E0ULL,
	/* Write data */
	0x80000515D9350004ULL, 0x80000515D93500E4ULL,
	/* Set address */
	0x8001051500000000ULL, 0x80010515000000E0ULL,
	/* Write data */
	0x80010515001E0004ULL, 0x80010515001E00E4ULL,
	/* Set address */
	0x8002051500000000ULL, 0x80020515000000E0ULL,
	/* Write data */
	0x80020515F2100004ULL, 0x80020515F21000E4ULL,
	END_SIGN
पूर्ण;

/*
 * Constants क्रम Fixing the MacAddress problem seen mostly on
 * Alpha machines.
 */
अटल स्थिर u64 fix_mac[] = अणु
	0x0060000000000000ULL, 0x0060600000000000ULL,
	0x0040600000000000ULL, 0x0000600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0060600000000000ULL,
	0x0020600000000000ULL, 0x0000600000000000ULL,
	0x0040600000000000ULL, 0x0060600000000000ULL,
	END_SIGN
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);


/* Module Loadable parameters. */
S2IO_PARM_INT(tx_fअगरo_num, FIFO_DEFAULT_NUM);
S2IO_PARM_INT(rx_ring_num, 1);
S2IO_PARM_INT(multiq, 0);
S2IO_PARM_INT(rx_ring_mode, 1);
S2IO_PARM_INT(use_continuous_tx_पूर्णांकrs, 1);
S2IO_PARM_INT(rmac_छोड़ो_समय, 0x100);
S2IO_PARM_INT(mc_छोड़ो_threshold_q0q3, 187);
S2IO_PARM_INT(mc_छोड़ो_threshold_q4q7, 187);
S2IO_PARM_INT(shared_splits, 0);
S2IO_PARM_INT(पंचांगac_util_period, 5);
S2IO_PARM_INT(rmac_util_period, 5);
S2IO_PARM_INT(l3l4hdr_size, 128);
/* 0 is no steering, 1 is Priority steering, 2 is Default steering */
S2IO_PARM_INT(tx_steering_type, TX_DEFAULT_STEERING);
/* Frequency of Rx desc syncs expressed as घातer of 2 */
S2IO_PARM_INT(rxsync_frequency, 3);
/* Interrupt type. Values can be 0(INTA), 2(MSI_X) */
S2IO_PARM_INT(पूर्णांकr_type, 2);
/* Large receive offload feature */

/* Max pkts to be aggregated by LRO at one समय. If not specअगरied,
 * aggregation happens until we hit max IP pkt size(64K)
 */
S2IO_PARM_INT(lro_max_pkts, 0xFFFF);
S2IO_PARM_INT(indicate_max_pkts, 0);

S2IO_PARM_INT(napi, 1);
S2IO_PARM_INT(vlan_tag_strip, NO_STRIP_IN_PROMISC);

अटल अचिन्हित पूर्णांक tx_fअगरo_len[MAX_TX_FIFOS] =
अणुDEFAULT_FIFO_0_LEN, [1 ...(MAX_TX_FIFOS - 1)] = DEFAULT_FIFO_1_7_LENपूर्ण;
अटल अचिन्हित पूर्णांक rx_ring_sz[MAX_RX_RINGS] =
अणु[0 ...(MAX_RX_RINGS - 1)] = SMALL_BLK_CNTपूर्ण;
अटल अचिन्हित पूर्णांक rts_frm_len[MAX_RX_RINGS] =
अणु[0 ...(MAX_RX_RINGS - 1)] = 0 पूर्ण;

module_param_array(tx_fअगरo_len, uपूर्णांक, शून्य, 0);
module_param_array(rx_ring_sz, uपूर्णांक, शून्य, 0);
module_param_array(rts_frm_len, uपूर्णांक, शून्य, 0);

/*
 * S2IO device table.
 * This table lists all the devices that this driver supports.
 */
अटल स्थिर काष्ठा pci_device_id s2io_tbl[] = अणु
	अणुPCI_VENDOR_ID_S2IO, PCI_DEVICE_ID_S2IO_WIN,
	 PCI_ANY_ID, PCI_ANY_IDपूर्ण,
	अणुPCI_VENDOR_ID_S2IO, PCI_DEVICE_ID_S2IO_UNI,
	 PCI_ANY_ID, PCI_ANY_IDपूर्ण,
	अणुPCI_VENDOR_ID_S2IO, PCI_DEVICE_ID_HERC_WIN,
	 PCI_ANY_ID, PCI_ANY_IDपूर्ण,
	अणुPCI_VENDOR_ID_S2IO, PCI_DEVICE_ID_HERC_UNI,
	 PCI_ANY_ID, PCI_ANY_IDपूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, s2io_tbl);

अटल स्थिर काष्ठा pci_error_handlers s2io_err_handler = अणु
	.error_detected = s2io_io_error_detected,
	.slot_reset = s2io_io_slot_reset,
	.resume = s2io_io_resume,
पूर्ण;

अटल काष्ठा pci_driver s2io_driver = अणु
	.name = "S2IO",
	.id_table = s2io_tbl,
	.probe = s2io_init_nic,
	.हटाओ = s2io_rem_nic,
	.err_handler = &s2io_err_handler,
पूर्ण;

/* A simplअगरier macro used both by init and मुक्त shared_mem Fns(). */
#घोषणा TXD_MEM_PAGE_CNT(len, per_each) DIV_ROUND_UP(len, per_each)

/* netqueue manipulation helper functions */
अटल अंतरभूत व्योम s2io_stop_all_tx_queue(काष्ठा s2io_nic *sp)
अणु
	अगर (!sp->config.multiq) अणु
		पूर्णांक i;

		क्रम (i = 0; i < sp->config.tx_fअगरo_num; i++)
			sp->mac_control.fअगरos[i].queue_state = FIFO_QUEUE_STOP;
	पूर्ण
	netअगर_tx_stop_all_queues(sp->dev);
पूर्ण

अटल अंतरभूत व्योम s2io_stop_tx_queue(काष्ठा s2io_nic *sp, पूर्णांक fअगरo_no)
अणु
	अगर (!sp->config.multiq)
		sp->mac_control.fअगरos[fअगरo_no].queue_state =
			FIFO_QUEUE_STOP;

	netअगर_tx_stop_all_queues(sp->dev);
पूर्ण

अटल अंतरभूत व्योम s2io_start_all_tx_queue(काष्ठा s2io_nic *sp)
अणु
	अगर (!sp->config.multiq) अणु
		पूर्णांक i;

		क्रम (i = 0; i < sp->config.tx_fअगरo_num; i++)
			sp->mac_control.fअगरos[i].queue_state = FIFO_QUEUE_START;
	पूर्ण
	netअगर_tx_start_all_queues(sp->dev);
पूर्ण

अटल अंतरभूत व्योम s2io_wake_all_tx_queue(काष्ठा s2io_nic *sp)
अणु
	अगर (!sp->config.multiq) अणु
		पूर्णांक i;

		क्रम (i = 0; i < sp->config.tx_fअगरo_num; i++)
			sp->mac_control.fअगरos[i].queue_state = FIFO_QUEUE_START;
	पूर्ण
	netअगर_tx_wake_all_queues(sp->dev);
पूर्ण

अटल अंतरभूत व्योम s2io_wake_tx_queue(
	काष्ठा fअगरo_info *fअगरo, पूर्णांक cnt, u8 multiq)
अणु

	अगर (multiq) अणु
		अगर (cnt && __netअगर_subqueue_stopped(fअगरo->dev, fअगरo->fअगरo_no))
			netअगर_wake_subqueue(fअगरo->dev, fअगरo->fअगरo_no);
	पूर्ण अन्यथा अगर (cnt && (fअगरo->queue_state == FIFO_QUEUE_STOP)) अणु
		अगर (netअगर_queue_stopped(fअगरo->dev)) अणु
			fअगरo->queue_state = FIFO_QUEUE_START;
			netअगर_wake_queue(fअगरo->dev);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * init_shared_mem - Allocation and Initialization of Memory
 * @nic: Device निजी variable.
 * Description: The function allocates all the memory areas shared
 * between the NIC and the driver. This includes Tx descriptors,
 * Rx descriptors and the statistics block.
 */

अटल पूर्णांक init_shared_mem(काष्ठा s2io_nic *nic)
अणु
	u32 size;
	व्योम *पंचांगp_v_addr, *पंचांगp_v_addr_next;
	dma_addr_t पंचांगp_p_addr, पंचांगp_p_addr_next;
	काष्ठा RxD_block *pre_rxd_blk = शून्य;
	पूर्णांक i, j, blk_cnt;
	पूर्णांक lst_size, lst_per_page;
	काष्ठा net_device *dev = nic->dev;
	अचिन्हित दीर्घ पंचांगp;
	काष्ठा buffAdd *ba;
	काष्ठा config_param *config = &nic->config;
	काष्ठा mac_info *mac_control = &nic->mac_control;
	अचिन्हित दीर्घ दीर्घ mem_allocated = 0;

	/* Allocation and initialization of TXDLs in FIFOs */
	size = 0;
	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];

		size += tx_cfg->fअगरo_len;
	पूर्ण
	अगर (size > MAX_AVAILABLE_TXDS) अणु
		DBG_PRINT(ERR_DBG,
			  "Too many TxDs requested: %d, max supported: %d\n",
			  size, MAX_AVAILABLE_TXDS);
		वापस -EINVAL;
	पूर्ण

	size = 0;
	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];

		size = tx_cfg->fअगरo_len;
		/*
		 * Legal values are from 2 to 8192
		 */
		अगर (size < 2) अणु
			DBG_PRINT(ERR_DBG, "Fifo %d: Invalid length (%d) - "
				  "Valid lengths are 2 through 8192\n",
				  i, size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	lst_size = (माप(काष्ठा TxD) * config->max_txds);
	lst_per_page = PAGE_SIZE / lst_size;

	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		काष्ठा fअगरo_info *fअगरo = &mac_control->fअगरos[i];
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];
		पूर्णांक fअगरo_len = tx_cfg->fअगरo_len;
		पूर्णांक list_holder_size = fअगरo_len * माप(काष्ठा list_info_hold);

		fअगरo->list_info = kzalloc(list_holder_size, GFP_KERNEL);
		अगर (!fअगरo->list_info) अणु
			DBG_PRINT(INFO_DBG, "Malloc failed for list_info\n");
			वापस -ENOMEM;
		पूर्ण
		mem_allocated += list_holder_size;
	पूर्ण
	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		पूर्णांक page_num = TXD_MEM_PAGE_CNT(config->tx_cfg[i].fअगरo_len,
						lst_per_page);
		काष्ठा fअगरo_info *fअगरo = &mac_control->fअगरos[i];
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];

		fअगरo->tx_curr_put_info.offset = 0;
		fअगरo->tx_curr_put_info.fअगरo_len = tx_cfg->fअगरo_len - 1;
		fअगरo->tx_curr_get_info.offset = 0;
		fअगरo->tx_curr_get_info.fअगरo_len = tx_cfg->fअगरo_len - 1;
		fअगरo->fअगरo_no = i;
		fअगरo->nic = nic;
		fअगरo->max_txds = MAX_SKB_FRAGS + 2;
		fअगरo->dev = dev;

		क्रम (j = 0; j < page_num; j++) अणु
			पूर्णांक k = 0;
			dma_addr_t पंचांगp_p;
			व्योम *पंचांगp_v;
			पंचांगp_v = dma_alloc_coherent(&nic->pdev->dev, PAGE_SIZE,
						   &पंचांगp_p, GFP_KERNEL);
			अगर (!पंचांगp_v) अणु
				DBG_PRINT(INFO_DBG,
					  "dma_alloc_coherent failed for TxDL\n");
				वापस -ENOMEM;
			पूर्ण
			/* If we got a zero DMA address(can happen on
			 * certain platक्रमms like PPC), पुनः_स्मृतिate.
			 * Store भव address of page we करोn't want,
			 * to be मुक्तd later.
			 */
			अगर (!पंचांगp_p) अणु
				mac_control->zerodma_virt_addr = पंचांगp_v;
				DBG_PRINT(INIT_DBG,
					  "%s: Zero DMA address for TxDL. "
					  "Virtual address %p\n",
					  dev->name, पंचांगp_v);
				पंचांगp_v = dma_alloc_coherent(&nic->pdev->dev,
							   PAGE_SIZE, &पंचांगp_p,
							   GFP_KERNEL);
				अगर (!पंचांगp_v) अणु
					DBG_PRINT(INFO_DBG,
						  "dma_alloc_coherent failed for TxDL\n");
					वापस -ENOMEM;
				पूर्ण
				mem_allocated += PAGE_SIZE;
			पूर्ण
			जबतक (k < lst_per_page) अणु
				पूर्णांक l = (j * lst_per_page) + k;
				अगर (l == tx_cfg->fअगरo_len)
					अवरोध;
				fअगरo->list_info[l].list_virt_addr =
					पंचांगp_v + (k * lst_size);
				fअगरo->list_info[l].list_phy_addr =
					पंचांगp_p + (k * lst_size);
				k++;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		काष्ठा fअगरo_info *fअगरo = &mac_control->fअगरos[i];
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];

		size = tx_cfg->fअगरo_len;
		fअगरo->ufo_in_band_v = kसुस्मृति(size, माप(u64), GFP_KERNEL);
		अगर (!fअगरo->ufo_in_band_v)
			वापस -ENOMEM;
		mem_allocated += (size * माप(u64));
	पूर्ण

	/* Allocation and initialization of RXDs in Rings */
	size = 0;
	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा rx_ring_config *rx_cfg = &config->rx_cfg[i];
		काष्ठा ring_info *ring = &mac_control->rings[i];

		अगर (rx_cfg->num_rxd % (rxd_count[nic->rxd_mode] + 1)) अणु
			DBG_PRINT(ERR_DBG, "%s: Ring%d RxD count is not a "
				  "multiple of RxDs per Block\n",
				  dev->name, i);
			वापस FAILURE;
		पूर्ण
		size += rx_cfg->num_rxd;
		ring->block_count = rx_cfg->num_rxd /
			(rxd_count[nic->rxd_mode] + 1);
		ring->pkt_cnt = rx_cfg->num_rxd - ring->block_count;
	पूर्ण
	अगर (nic->rxd_mode == RXD_MODE_1)
		size = (size * (माप(काष्ठा RxD1)));
	अन्यथा
		size = (size * (माप(काष्ठा RxD3)));

	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा rx_ring_config *rx_cfg = &config->rx_cfg[i];
		काष्ठा ring_info *ring = &mac_control->rings[i];

		ring->rx_curr_get_info.block_index = 0;
		ring->rx_curr_get_info.offset = 0;
		ring->rx_curr_get_info.ring_len = rx_cfg->num_rxd - 1;
		ring->rx_curr_put_info.block_index = 0;
		ring->rx_curr_put_info.offset = 0;
		ring->rx_curr_put_info.ring_len = rx_cfg->num_rxd - 1;
		ring->nic = nic;
		ring->ring_no = i;

		blk_cnt = rx_cfg->num_rxd / (rxd_count[nic->rxd_mode] + 1);
		/*  Allocating all the Rx blocks */
		क्रम (j = 0; j < blk_cnt; j++) अणु
			काष्ठा rx_block_info *rx_blocks;
			पूर्णांक l;

			rx_blocks = &ring->rx_blocks[j];
			size = SIZE_OF_BLOCK;	/* size is always page size */
			पंचांगp_v_addr = dma_alloc_coherent(&nic->pdev->dev, size,
							&पंचांगp_p_addr, GFP_KERNEL);
			अगर (पंचांगp_v_addr == शून्य) अणु
				/*
				 * In हाल of failure, मुक्त_shared_mem()
				 * is called, which should मुक्त any
				 * memory that was alloced till the
				 * failure happened.
				 */
				rx_blocks->block_virt_addr = पंचांगp_v_addr;
				वापस -ENOMEM;
			पूर्ण
			mem_allocated += size;

			size = माप(काष्ठा rxd_info) *
				rxd_count[nic->rxd_mode];
			rx_blocks->block_virt_addr = पंचांगp_v_addr;
			rx_blocks->block_dma_addr = पंचांगp_p_addr;
			rx_blocks->rxds = kदो_स्मृति(size,  GFP_KERNEL);
			अगर (!rx_blocks->rxds)
				वापस -ENOMEM;
			mem_allocated += size;
			क्रम (l = 0; l < rxd_count[nic->rxd_mode]; l++) अणु
				rx_blocks->rxds[l].virt_addr =
					rx_blocks->block_virt_addr +
					(rxd_size[nic->rxd_mode] * l);
				rx_blocks->rxds[l].dma_addr =
					rx_blocks->block_dma_addr +
					(rxd_size[nic->rxd_mode] * l);
			पूर्ण
		पूर्ण
		/* Interlinking all Rx Blocks */
		क्रम (j = 0; j < blk_cnt; j++) अणु
			पूर्णांक next = (j + 1) % blk_cnt;
			पंचांगp_v_addr = ring->rx_blocks[j].block_virt_addr;
			पंचांगp_v_addr_next = ring->rx_blocks[next].block_virt_addr;
			पंचांगp_p_addr = ring->rx_blocks[j].block_dma_addr;
			पंचांगp_p_addr_next = ring->rx_blocks[next].block_dma_addr;

			pre_rxd_blk = पंचांगp_v_addr;
			pre_rxd_blk->reserved_2_pNext_RxD_block =
				(अचिन्हित दीर्घ)पंचांगp_v_addr_next;
			pre_rxd_blk->pNext_RxD_Blk_physical =
				(u64)पंचांगp_p_addr_next;
		पूर्ण
	पूर्ण
	अगर (nic->rxd_mode == RXD_MODE_3B) अणु
		/*
		 * Allocation of Storages क्रम buffer addresses in 2BUFF mode
		 * and the buffers as well.
		 */
		क्रम (i = 0; i < config->rx_ring_num; i++) अणु
			काष्ठा rx_ring_config *rx_cfg = &config->rx_cfg[i];
			काष्ठा ring_info *ring = &mac_control->rings[i];

			blk_cnt = rx_cfg->num_rxd /
				(rxd_count[nic->rxd_mode] + 1);
			size = माप(काष्ठा buffAdd *) * blk_cnt;
			ring->ba = kदो_स्मृति(size, GFP_KERNEL);
			अगर (!ring->ba)
				वापस -ENOMEM;
			mem_allocated += size;
			क्रम (j = 0; j < blk_cnt; j++) अणु
				पूर्णांक k = 0;

				size = माप(काष्ठा buffAdd) *
					(rxd_count[nic->rxd_mode] + 1);
				ring->ba[j] = kदो_स्मृति(size, GFP_KERNEL);
				अगर (!ring->ba[j])
					वापस -ENOMEM;
				mem_allocated += size;
				जबतक (k != rxd_count[nic->rxd_mode]) अणु
					ba = &ring->ba[j][k];
					size = BUF0_LEN + ALIGN_SIZE;
					ba->ba_0_org = kदो_स्मृति(size, GFP_KERNEL);
					अगर (!ba->ba_0_org)
						वापस -ENOMEM;
					mem_allocated += size;
					पंचांगp = (अचिन्हित दीर्घ)ba->ba_0_org;
					पंचांगp += ALIGN_SIZE;
					पंचांगp &= ~((अचिन्हित दीर्घ)ALIGN_SIZE);
					ba->ba_0 = (व्योम *)पंचांगp;

					size = BUF1_LEN + ALIGN_SIZE;
					ba->ba_1_org = kदो_स्मृति(size, GFP_KERNEL);
					अगर (!ba->ba_1_org)
						वापस -ENOMEM;
					mem_allocated += size;
					पंचांगp = (अचिन्हित दीर्घ)ba->ba_1_org;
					पंचांगp += ALIGN_SIZE;
					पंचांगp &= ~((अचिन्हित दीर्घ)ALIGN_SIZE);
					ba->ba_1 = (व्योम *)पंचांगp;
					k++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Allocation and initialization of Statistics block */
	size = माप(काष्ठा stat_block);
	mac_control->stats_mem =
		dma_alloc_coherent(&nic->pdev->dev, size,
				   &mac_control->stats_mem_phy, GFP_KERNEL);

	अगर (!mac_control->stats_mem) अणु
		/*
		 * In हाल of failure, मुक्त_shared_mem() is called, which
		 * should मुक्त any memory that was alloced till the
		 * failure happened.
		 */
		वापस -ENOMEM;
	पूर्ण
	mem_allocated += size;
	mac_control->stats_mem_sz = size;

	पंचांगp_v_addr = mac_control->stats_mem;
	mac_control->stats_info = पंचांगp_v_addr;
	स_रखो(पंचांगp_v_addr, 0, size);
	DBG_PRINT(INIT_DBG, "%s: Ring Mem PHY: 0x%llx\n",
		dev_name(&nic->pdev->dev), (अचिन्हित दीर्घ दीर्घ)पंचांगp_p_addr);
	mac_control->stats_info->sw_stat.mem_allocated += mem_allocated;
	वापस SUCCESS;
पूर्ण

/**
 * मुक्त_shared_mem - Free the allocated Memory
 * @nic:  Device निजी variable.
 * Description: This function is to मुक्त all memory locations allocated by
 * the init_shared_mem() function and वापस it to the kernel.
 */

अटल व्योम मुक्त_shared_mem(काष्ठा s2io_nic *nic)
अणु
	पूर्णांक i, j, blk_cnt, size;
	व्योम *पंचांगp_v_addr;
	dma_addr_t पंचांगp_p_addr;
	पूर्णांक lst_size, lst_per_page;
	काष्ठा net_device *dev;
	पूर्णांक page_num = 0;
	काष्ठा config_param *config;
	काष्ठा mac_info *mac_control;
	काष्ठा stat_block *stats;
	काष्ठा swStat *swstats;

	अगर (!nic)
		वापस;

	dev = nic->dev;

	config = &nic->config;
	mac_control = &nic->mac_control;
	stats = mac_control->stats_info;
	swstats = &stats->sw_stat;

	lst_size = माप(काष्ठा TxD) * config->max_txds;
	lst_per_page = PAGE_SIZE / lst_size;

	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		काष्ठा fअगरo_info *fअगरo = &mac_control->fअगरos[i];
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];

		page_num = TXD_MEM_PAGE_CNT(tx_cfg->fअगरo_len, lst_per_page);
		क्रम (j = 0; j < page_num; j++) अणु
			पूर्णांक mem_blks = (j * lst_per_page);
			काष्ठा list_info_hold *fli;

			अगर (!fअगरo->list_info)
				वापस;

			fli = &fअगरo->list_info[mem_blks];
			अगर (!fli->list_virt_addr)
				अवरोध;
			dma_मुक्त_coherent(&nic->pdev->dev, PAGE_SIZE,
					  fli->list_virt_addr,
					  fli->list_phy_addr);
			swstats->mem_मुक्तd += PAGE_SIZE;
		पूर्ण
		/* If we got a zero DMA address during allocation,
		 * मुक्त the page now
		 */
		अगर (mac_control->zerodma_virt_addr) अणु
			dma_मुक्त_coherent(&nic->pdev->dev, PAGE_SIZE,
					  mac_control->zerodma_virt_addr,
					  (dma_addr_t)0);
			DBG_PRINT(INIT_DBG,
				  "%s: Freeing TxDL with zero DMA address. "
				  "Virtual address %p\n",
				  dev->name, mac_control->zerodma_virt_addr);
			swstats->mem_मुक्तd += PAGE_SIZE;
		पूर्ण
		kमुक्त(fअगरo->list_info);
		swstats->mem_मुक्तd += tx_cfg->fअगरo_len *
			माप(काष्ठा list_info_hold);
	पूर्ण

	size = SIZE_OF_BLOCK;
	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा ring_info *ring = &mac_control->rings[i];

		blk_cnt = ring->block_count;
		क्रम (j = 0; j < blk_cnt; j++) अणु
			पंचांगp_v_addr = ring->rx_blocks[j].block_virt_addr;
			पंचांगp_p_addr = ring->rx_blocks[j].block_dma_addr;
			अगर (पंचांगp_v_addr == शून्य)
				अवरोध;
			dma_मुक्त_coherent(&nic->pdev->dev, size, पंचांगp_v_addr,
					  पंचांगp_p_addr);
			swstats->mem_मुक्तd += size;
			kमुक्त(ring->rx_blocks[j].rxds);
			swstats->mem_मुक्तd += माप(काष्ठा rxd_info) *
				rxd_count[nic->rxd_mode];
		पूर्ण
	पूर्ण

	अगर (nic->rxd_mode == RXD_MODE_3B) अणु
		/* Freeing buffer storage addresses in 2BUFF mode. */
		क्रम (i = 0; i < config->rx_ring_num; i++) अणु
			काष्ठा rx_ring_config *rx_cfg = &config->rx_cfg[i];
			काष्ठा ring_info *ring = &mac_control->rings[i];

			blk_cnt = rx_cfg->num_rxd /
				(rxd_count[nic->rxd_mode] + 1);
			क्रम (j = 0; j < blk_cnt; j++) अणु
				पूर्णांक k = 0;
				अगर (!ring->ba[j])
					जारी;
				जबतक (k != rxd_count[nic->rxd_mode]) अणु
					काष्ठा buffAdd *ba = &ring->ba[j][k];
					kमुक्त(ba->ba_0_org);
					swstats->mem_मुक्तd +=
						BUF0_LEN + ALIGN_SIZE;
					kमुक्त(ba->ba_1_org);
					swstats->mem_मुक्तd +=
						BUF1_LEN + ALIGN_SIZE;
					k++;
				पूर्ण
				kमुक्त(ring->ba[j]);
				swstats->mem_मुक्तd += माप(काष्ठा buffAdd) *
					(rxd_count[nic->rxd_mode] + 1);
			पूर्ण
			kमुक्त(ring->ba);
			swstats->mem_मुक्तd += माप(काष्ठा buffAdd *) *
				blk_cnt;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nic->config.tx_fअगरo_num; i++) अणु
		काष्ठा fअगरo_info *fअगरo = &mac_control->fअगरos[i];
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];

		अगर (fअगरo->ufo_in_band_v) अणु
			swstats->mem_मुक्तd += tx_cfg->fअगरo_len *
				माप(u64);
			kमुक्त(fअगरo->ufo_in_band_v);
		पूर्ण
	पूर्ण

	अगर (mac_control->stats_mem) अणु
		swstats->mem_मुक्तd += mac_control->stats_mem_sz;
		dma_मुक्त_coherent(&nic->pdev->dev, mac_control->stats_mem_sz,
				  mac_control->stats_mem,
				  mac_control->stats_mem_phy);
	पूर्ण
पूर्ण

/*
 * s2io_verअगरy_pci_mode -
 */

अटल पूर्णांक s2io_verअगरy_pci_mode(काष्ठा s2io_nic *nic)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	रेजिस्टर u64 val64 = 0;
	पूर्णांक     mode;

	val64 = पढ़ोq(&bar0->pci_mode);
	mode = (u8)GET_PCI_MODE(val64);

	अगर (val64 & PCI_MODE_UNKNOWN_MODE)
		वापस -1;      /* Unknown PCI mode */
	वापस mode;
पूर्ण

#घोषणा NEC_VENID   0x1033
#घोषणा NEC_DEVID   0x0125
अटल पूर्णांक s2io_on_nec_bridge(काष्ठा pci_dev *s2io_pdev)
अणु
	काष्ठा pci_dev *tdev = शून्य;
	क्रम_each_pci_dev(tdev) अणु
		अगर (tdev->venकरोr == NEC_VENID && tdev->device == NEC_DEVID) अणु
			अगर (tdev->bus == s2io_pdev->bus->parent) अणु
				pci_dev_put(tdev);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bus_speed[8] = अणु33, 133, 133, 200, 266, 133, 200, 266पूर्ण;
/*
 * s2io_prपूर्णांक_pci_mode -
 */
अटल पूर्णांक s2io_prपूर्णांक_pci_mode(काष्ठा s2io_nic *nic)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	रेजिस्टर u64 val64 = 0;
	पूर्णांक	mode;
	काष्ठा config_param *config = &nic->config;
	स्थिर अक्षर *pcimode;

	val64 = पढ़ोq(&bar0->pci_mode);
	mode = (u8)GET_PCI_MODE(val64);

	अगर (val64 & PCI_MODE_UNKNOWN_MODE)
		वापस -1;	/* Unknown PCI mode */

	config->bus_speed = bus_speed[mode];

	अगर (s2io_on_nec_bridge(nic->pdev)) अणु
		DBG_PRINT(ERR_DBG, "%s: Device is on PCI-E bus\n",
			  nic->dev->name);
		वापस mode;
	पूर्ण

	चयन (mode) अणु
	हाल PCI_MODE_PCI_33:
		pcimode = "33MHz PCI bus";
		अवरोध;
	हाल PCI_MODE_PCI_66:
		pcimode = "66MHz PCI bus";
		अवरोध;
	हाल PCI_MODE_PCIX_M1_66:
		pcimode = "66MHz PCIX(M1) bus";
		अवरोध;
	हाल PCI_MODE_PCIX_M1_100:
		pcimode = "100MHz PCIX(M1) bus";
		अवरोध;
	हाल PCI_MODE_PCIX_M1_133:
		pcimode = "133MHz PCIX(M1) bus";
		अवरोध;
	हाल PCI_MODE_PCIX_M2_66:
		pcimode = "133MHz PCIX(M2) bus";
		अवरोध;
	हाल PCI_MODE_PCIX_M2_100:
		pcimode = "200MHz PCIX(M2) bus";
		अवरोध;
	हाल PCI_MODE_PCIX_M2_133:
		pcimode = "266MHz PCIX(M2) bus";
		अवरोध;
	शेष:
		pcimode = "unsupported bus!";
		mode = -1;
	पूर्ण

	DBG_PRINT(ERR_DBG, "%s: Device is on %d bit %s\n",
		  nic->dev->name, val64 & PCI_MODE_32_BITS ? 32 : 64, pcimode);

	वापस mode;
पूर्ण

/**
 *  init_tti - Initialization transmit traffic पूर्णांकerrupt scheme
 *  @nic: device निजी variable
 *  @link: link status (UP/DOWN) used to enable/disable continuous
 *  transmit पूर्णांकerrupts
 *  Description: The function configures transmit traffic पूर्णांकerrupts
 *  Return Value:  SUCCESS on success and
 *  '-1' on failure
 */

अटल पूर्णांक init_tti(काष्ठा s2io_nic *nic, पूर्णांक link, bool may_sleep)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	रेजिस्टर u64 val64 = 0;
	पूर्णांक i;
	काष्ठा config_param *config = &nic->config;

	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		/*
		 * TTI Initialization. Default Tx समयr माला_लो us about
		 * 250 पूर्णांकerrupts per sec. Continuous पूर्णांकerrupts are enabled
		 * by शेष.
		 */
		अगर (nic->device_type == XFRAME_II_DEVICE) अणु
			पूर्णांक count = (nic->config.bus_speed * 125)/2;
			val64 = TTI_DATA1_MEM_TX_TIMER_VAL(count);
		पूर्ण अन्यथा
			val64 = TTI_DATA1_MEM_TX_TIMER_VAL(0x2078);

		val64 |= TTI_DATA1_MEM_TX_URNG_A(0xA) |
			TTI_DATA1_MEM_TX_URNG_B(0x10) |
			TTI_DATA1_MEM_TX_URNG_C(0x30) |
			TTI_DATA1_MEM_TX_TIMER_AC_EN;
		अगर (i == 0)
			अगर (use_continuous_tx_पूर्णांकrs && (link == LINK_UP))
				val64 |= TTI_DATA1_MEM_TX_TIMER_CI_EN;
		ग_लिखोq(val64, &bar0->tti_data1_mem);

		अगर (nic->config.पूर्णांकr_type == MSI_X) अणु
			val64 = TTI_DATA2_MEM_TX_UFC_A(0x10) |
				TTI_DATA2_MEM_TX_UFC_B(0x100) |
				TTI_DATA2_MEM_TX_UFC_C(0x200) |
				TTI_DATA2_MEM_TX_UFC_D(0x300);
		पूर्ण अन्यथा अणु
			अगर ((nic->config.tx_steering_type ==
			     TX_DEFAULT_STEERING) &&
			    (config->tx_fअगरo_num > 1) &&
			    (i >= nic->udp_fअगरo_idx) &&
			    (i < (nic->udp_fअगरo_idx +
				  nic->total_udp_fअगरos)))
				val64 = TTI_DATA2_MEM_TX_UFC_A(0x50) |
					TTI_DATA2_MEM_TX_UFC_B(0x80) |
					TTI_DATA2_MEM_TX_UFC_C(0x100) |
					TTI_DATA2_MEM_TX_UFC_D(0x120);
			अन्यथा
				val64 = TTI_DATA2_MEM_TX_UFC_A(0x10) |
					TTI_DATA2_MEM_TX_UFC_B(0x20) |
					TTI_DATA2_MEM_TX_UFC_C(0x40) |
					TTI_DATA2_MEM_TX_UFC_D(0x80);
		पूर्ण

		ग_लिखोq(val64, &bar0->tti_data2_mem);

		val64 = TTI_CMD_MEM_WE |
			TTI_CMD_MEM_STROBE_NEW_CMD |
			TTI_CMD_MEM_OFFSET(i);
		ग_लिखोq(val64, &bar0->tti_command_mem);

		अगर (रुको_क्रम_cmd_complete(&bar0->tti_command_mem,
					  TTI_CMD_MEM_STROBE_NEW_CMD,
					  S2IO_BIT_RESET, may_sleep) != SUCCESS)
			वापस FAILURE;
	पूर्ण

	वापस SUCCESS;
पूर्ण

/**
 *  init_nic - Initialization of hardware
 *  @nic: device निजी variable
 *  Description: The function sequentially configures every block
 *  of the H/W from their reset values.
 *  Return Value:  SUCCESS on success and
 *  '-1' on failure (endian settings incorrect).
 */

अटल पूर्णांक init_nic(काष्ठा s2io_nic *nic)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	काष्ठा net_device *dev = nic->dev;
	रेजिस्टर u64 val64 = 0;
	व्योम __iomem *add;
	u32 समय;
	पूर्णांक i, j;
	पूर्णांक dtx_cnt = 0;
	अचिन्हित दीर्घ दीर्घ mem_share;
	पूर्णांक mem_size;
	काष्ठा config_param *config = &nic->config;
	काष्ठा mac_info *mac_control = &nic->mac_control;

	/* to set the swapper controle on the card */
	अगर (s2io_set_swapper(nic)) अणु
		DBG_PRINT(ERR_DBG, "ERROR: Setting Swapper failed\n");
		वापस -EIO;
	पूर्ण

	/*
	 * Herc requires EOI to be हटाओd from reset beक्रमe XGXS, so..
	 */
	अगर (nic->device_type & XFRAME_II_DEVICE) अणु
		val64 = 0xA500000000ULL;
		ग_लिखोq(val64, &bar0->sw_reset);
		msleep(500);
		val64 = पढ़ोq(&bar0->sw_reset);
	पूर्ण

	/* Remove XGXS from reset state */
	val64 = 0;
	ग_लिखोq(val64, &bar0->sw_reset);
	msleep(500);
	val64 = पढ़ोq(&bar0->sw_reset);

	/* Ensure that it's safe to access रेजिस्टरs by checking
	 * RIC_RUNNING bit is reset. Check is valid only क्रम XframeII.
	 */
	अगर (nic->device_type == XFRAME_II_DEVICE) अणु
		क्रम (i = 0; i < 50; i++) अणु
			val64 = पढ़ोq(&bar0->adapter_status);
			अगर (!(val64 & ADAPTER_STATUS_RIC_RUNNING))
				अवरोध;
			msleep(10);
		पूर्ण
		अगर (i == 50)
			वापस -ENODEV;
	पूर्ण

	/*  Enable Receiving broadcasts */
	add = &bar0->mac_cfg;
	val64 = पढ़ोq(&bar0->mac_cfg);
	val64 |= MAC_RMAC_BCAST_ENABLE;
	ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
	ग_लिखोl((u32)val64, add);
	ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
	ग_लिखोl((u32) (val64 >> 32), (add + 4));

	/* Read रेजिस्टरs in all blocks */
	val64 = पढ़ोq(&bar0->mac_पूर्णांक_mask);
	val64 = पढ़ोq(&bar0->mc_पूर्णांक_mask);
	val64 = पढ़ोq(&bar0->xgxs_पूर्णांक_mask);

	/*  Set MTU */
	val64 = dev->mtu;
	ग_लिखोq(vBIT(val64, 2, 14), &bar0->rmac_max_pyld_len);

	अगर (nic->device_type & XFRAME_II_DEVICE) अणु
		जबतक (herc_act_dtx_cfg[dtx_cnt] != END_SIGN) अणु
			SPECIAL_REG_WRITE(herc_act_dtx_cfg[dtx_cnt],
					  &bar0->dtx_control, UF);
			अगर (dtx_cnt & 0x1)
				msleep(1); /* Necessary!! */
			dtx_cnt++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (xena_dtx_cfg[dtx_cnt] != END_SIGN) अणु
			SPECIAL_REG_WRITE(xena_dtx_cfg[dtx_cnt],
					  &bar0->dtx_control, UF);
			val64 = पढ़ोq(&bar0->dtx_control);
			dtx_cnt++;
		पूर्ण
	पूर्ण

	/*  Tx DMA Initialization */
	val64 = 0;
	ग_लिखोq(val64, &bar0->tx_fअगरo_partition_0);
	ग_लिखोq(val64, &bar0->tx_fअगरo_partition_1);
	ग_लिखोq(val64, &bar0->tx_fअगरo_partition_2);
	ग_लिखोq(val64, &bar0->tx_fअगरo_partition_3);

	क्रम (i = 0, j = 0; i < config->tx_fअगरo_num; i++) अणु
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];

		val64 |= vBIT(tx_cfg->fअगरo_len - 1, ((j * 32) + 19), 13) |
			vBIT(tx_cfg->fअगरo_priority, ((j * 32) + 5), 3);

		अगर (i == (config->tx_fअगरo_num - 1)) अणु
			अगर (i % 2 == 0)
				i++;
		पूर्ण

		चयन (i) अणु
		हाल 1:
			ग_लिखोq(val64, &bar0->tx_fअगरo_partition_0);
			val64 = 0;
			j = 0;
			अवरोध;
		हाल 3:
			ग_लिखोq(val64, &bar0->tx_fअगरo_partition_1);
			val64 = 0;
			j = 0;
			अवरोध;
		हाल 5:
			ग_लिखोq(val64, &bar0->tx_fअगरo_partition_2);
			val64 = 0;
			j = 0;
			अवरोध;
		हाल 7:
			ग_लिखोq(val64, &bar0->tx_fअगरo_partition_3);
			val64 = 0;
			j = 0;
			अवरोध;
		शेष:
			j++;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Disable 4 PCCs क्रम Xena1, 2 and 3 as per H/W bug
	 * SXE-008 TRANSMIT DMA ARBITRATION ISSUE.
	 */
	अगर ((nic->device_type == XFRAME_I_DEVICE) && (nic->pdev->revision < 4))
		ग_लिखोq(PCC_ENABLE_FOUR, &bar0->pcc_enable);

	val64 = पढ़ोq(&bar0->tx_fअगरo_partition_0);
	DBG_PRINT(INIT_DBG, "Fifo partition at: 0x%p is: 0x%llx\n",
		  &bar0->tx_fअगरo_partition_0, (अचिन्हित दीर्घ दीर्घ)val64);

	/*
	 * Initialization of Tx_PA_CONFIG रेजिस्टर to ignore packet
	 * पूर्णांकegrity checking.
	 */
	val64 = पढ़ोq(&bar0->tx_pa_cfg);
	val64 |= TX_PA_CFG_IGNORE_FRM_ERR |
		TX_PA_CFG_IGNORE_SNAP_OUI |
		TX_PA_CFG_IGNORE_LLC_CTRL |
		TX_PA_CFG_IGNORE_L2_ERR;
	ग_लिखोq(val64, &bar0->tx_pa_cfg);

	/* Rx DMA initialization. */
	val64 = 0;
	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा rx_ring_config *rx_cfg = &config->rx_cfg[i];

		val64 |= vBIT(rx_cfg->ring_priority, (5 + (i * 8)), 3);
	पूर्ण
	ग_लिखोq(val64, &bar0->rx_queue_priority);

	/*
	 * Allocating equal share of memory to all the
	 * configured Rings.
	 */
	val64 = 0;
	अगर (nic->device_type & XFRAME_II_DEVICE)
		mem_size = 32;
	अन्यथा
		mem_size = 64;

	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		चयन (i) अणु
		हाल 0:
			mem_share = (mem_size / config->rx_ring_num +
				     mem_size % config->rx_ring_num);
			val64 |= RX_QUEUE_CFG_Q0_SZ(mem_share);
			जारी;
		हाल 1:
			mem_share = (mem_size / config->rx_ring_num);
			val64 |= RX_QUEUE_CFG_Q1_SZ(mem_share);
			जारी;
		हाल 2:
			mem_share = (mem_size / config->rx_ring_num);
			val64 |= RX_QUEUE_CFG_Q2_SZ(mem_share);
			जारी;
		हाल 3:
			mem_share = (mem_size / config->rx_ring_num);
			val64 |= RX_QUEUE_CFG_Q3_SZ(mem_share);
			जारी;
		हाल 4:
			mem_share = (mem_size / config->rx_ring_num);
			val64 |= RX_QUEUE_CFG_Q4_SZ(mem_share);
			जारी;
		हाल 5:
			mem_share = (mem_size / config->rx_ring_num);
			val64 |= RX_QUEUE_CFG_Q5_SZ(mem_share);
			जारी;
		हाल 6:
			mem_share = (mem_size / config->rx_ring_num);
			val64 |= RX_QUEUE_CFG_Q6_SZ(mem_share);
			जारी;
		हाल 7:
			mem_share = (mem_size / config->rx_ring_num);
			val64 |= RX_QUEUE_CFG_Q7_SZ(mem_share);
			जारी;
		पूर्ण
	पूर्ण
	ग_लिखोq(val64, &bar0->rx_queue_cfg);

	/*
	 * Filling Tx round robin रेजिस्टरs
	 * as per the number of FIFOs क्रम equal scheduling priority
	 */
	चयन (config->tx_fअगरo_num) अणु
	हाल 1:
		val64 = 0x0;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_0);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_1);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_2);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_3);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_4);
		अवरोध;
	हाल 2:
		val64 = 0x0001000100010001ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_0);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_1);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_2);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_3);
		val64 = 0x0001000100000000ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_4);
		अवरोध;
	हाल 3:
		val64 = 0x0001020001020001ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_0);
		val64 = 0x0200010200010200ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_1);
		val64 = 0x0102000102000102ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_2);
		val64 = 0x0001020001020001ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_3);
		val64 = 0x0200010200000000ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_4);
		अवरोध;
	हाल 4:
		val64 = 0x0001020300010203ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_0);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_1);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_2);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_3);
		val64 = 0x0001020300000000ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_4);
		अवरोध;
	हाल 5:
		val64 = 0x0001020304000102ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_0);
		val64 = 0x0304000102030400ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_1);
		val64 = 0x0102030400010203ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_2);
		val64 = 0x0400010203040001ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_3);
		val64 = 0x0203040000000000ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_4);
		अवरोध;
	हाल 6:
		val64 = 0x0001020304050001ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_0);
		val64 = 0x0203040500010203ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_1);
		val64 = 0x0405000102030405ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_2);
		val64 = 0x0001020304050001ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_3);
		val64 = 0x0203040500000000ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_4);
		अवरोध;
	हाल 7:
		val64 = 0x0001020304050600ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_0);
		val64 = 0x0102030405060001ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_1);
		val64 = 0x0203040506000102ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_2);
		val64 = 0x0304050600010203ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_3);
		val64 = 0x0405060000000000ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_4);
		अवरोध;
	हाल 8:
		val64 = 0x0001020304050607ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_0);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_1);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_2);
		ग_लिखोq(val64, &bar0->tx_w_round_robin_3);
		val64 = 0x0001020300000000ULL;
		ग_लिखोq(val64, &bar0->tx_w_round_robin_4);
		अवरोध;
	पूर्ण

	/* Enable all configured Tx FIFO partitions */
	val64 = पढ़ोq(&bar0->tx_fअगरo_partition_0);
	val64 |= (TX_FIFO_PARTITION_EN);
	ग_लिखोq(val64, &bar0->tx_fअगरo_partition_0);

	/* Filling the Rx round robin रेजिस्टरs as per the
	 * number of Rings and steering based on QoS with
	 * equal priority.
	 */
	चयन (config->rx_ring_num) अणु
	हाल 1:
		val64 = 0x0;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_0);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_1);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_2);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_3);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_4);

		val64 = 0x8080808080808080ULL;
		ग_लिखोq(val64, &bar0->rts_qos_steering);
		अवरोध;
	हाल 2:
		val64 = 0x0001000100010001ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_0);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_1);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_2);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_3);
		val64 = 0x0001000100000000ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_4);

		val64 = 0x8080808040404040ULL;
		ग_लिखोq(val64, &bar0->rts_qos_steering);
		अवरोध;
	हाल 3:
		val64 = 0x0001020001020001ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_0);
		val64 = 0x0200010200010200ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_1);
		val64 = 0x0102000102000102ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_2);
		val64 = 0x0001020001020001ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_3);
		val64 = 0x0200010200000000ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_4);

		val64 = 0x8080804040402020ULL;
		ग_लिखोq(val64, &bar0->rts_qos_steering);
		अवरोध;
	हाल 4:
		val64 = 0x0001020300010203ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_0);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_1);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_2);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_3);
		val64 = 0x0001020300000000ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_4);

		val64 = 0x8080404020201010ULL;
		ग_लिखोq(val64, &bar0->rts_qos_steering);
		अवरोध;
	हाल 5:
		val64 = 0x0001020304000102ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_0);
		val64 = 0x0304000102030400ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_1);
		val64 = 0x0102030400010203ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_2);
		val64 = 0x0400010203040001ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_3);
		val64 = 0x0203040000000000ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_4);

		val64 = 0x8080404020201008ULL;
		ग_लिखोq(val64, &bar0->rts_qos_steering);
		अवरोध;
	हाल 6:
		val64 = 0x0001020304050001ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_0);
		val64 = 0x0203040500010203ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_1);
		val64 = 0x0405000102030405ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_2);
		val64 = 0x0001020304050001ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_3);
		val64 = 0x0203040500000000ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_4);

		val64 = 0x8080404020100804ULL;
		ग_लिखोq(val64, &bar0->rts_qos_steering);
		अवरोध;
	हाल 7:
		val64 = 0x0001020304050600ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_0);
		val64 = 0x0102030405060001ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_1);
		val64 = 0x0203040506000102ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_2);
		val64 = 0x0304050600010203ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_3);
		val64 = 0x0405060000000000ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_4);

		val64 = 0x8080402010080402ULL;
		ग_लिखोq(val64, &bar0->rts_qos_steering);
		अवरोध;
	हाल 8:
		val64 = 0x0001020304050607ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_0);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_1);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_2);
		ग_लिखोq(val64, &bar0->rx_w_round_robin_3);
		val64 = 0x0001020300000000ULL;
		ग_लिखोq(val64, &bar0->rx_w_round_robin_4);

		val64 = 0x8040201008040201ULL;
		ग_लिखोq(val64, &bar0->rts_qos_steering);
		अवरोध;
	पूर्ण

	/* UDP Fix */
	val64 = 0;
	क्रम (i = 0; i < 8; i++)
		ग_लिखोq(val64, &bar0->rts_frm_len_n[i]);

	/* Set the शेष rts frame length क्रम the rings configured */
	val64 = MAC_RTS_FRM_LEN_SET(dev->mtu+22);
	क्रम (i = 0 ; i < config->rx_ring_num ; i++)
		ग_लिखोq(val64, &bar0->rts_frm_len_n[i]);

	/* Set the frame length क्रम the configured rings
	 * desired by the user
	 */
	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		/* If rts_frm_len[i] == 0 then it is assumed that user not
		 * specअगरied frame length steering.
		 * If the user provides the frame length then program
		 * the rts_frm_len रेजिस्टर क्रम those values or अन्यथा
		 * leave it as it is.
		 */
		अगर (rts_frm_len[i] != 0) अणु
			ग_लिखोq(MAC_RTS_FRM_LEN_SET(rts_frm_len[i]),
			       &bar0->rts_frm_len_n[i]);
		पूर्ण
	पूर्ण

	/* Disable dअगरferentiated services steering logic */
	क्रम (i = 0; i < 64; i++) अणु
		अगर (rts_ds_steer(nic, i, 0) == FAILURE) अणु
			DBG_PRINT(ERR_DBG,
				  "%s: rts_ds_steer failed on codepoint %d\n",
				  dev->name, i);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Program statistics memory */
	ग_लिखोq(mac_control->stats_mem_phy, &bar0->stat_addr);

	अगर (nic->device_type == XFRAME_II_DEVICE) अणु
		val64 = STAT_BC(0x320);
		ग_लिखोq(val64, &bar0->stat_byte_cnt);
	पूर्ण

	/*
	 * Initializing the sampling rate क्रम the device to calculate the
	 * bandwidth utilization.
	 */
	val64 = MAC_TX_LINK_UTIL_VAL(पंचांगac_util_period) |
		MAC_RX_LINK_UTIL_VAL(rmac_util_period);
	ग_लिखोq(val64, &bar0->mac_link_util);

	/*
	 * Initializing the Transmit and Receive Traffic Interrupt
	 * Scheme.
	 */

	/* Initialize TTI */
	अगर (SUCCESS != init_tti(nic, nic->last_link_state, true))
		वापस -ENODEV;

	/* RTI Initialization */
	अगर (nic->device_type == XFRAME_II_DEVICE) अणु
		/*
		 * Programmed to generate Apprx 500 Intrs per
		 * second
		 */
		पूर्णांक count = (nic->config.bus_speed * 125)/4;
		val64 = RTI_DATA1_MEM_RX_TIMER_VAL(count);
	पूर्ण अन्यथा
		val64 = RTI_DATA1_MEM_RX_TIMER_VAL(0xFFF);
	val64 |= RTI_DATA1_MEM_RX_URNG_A(0xA) |
		RTI_DATA1_MEM_RX_URNG_B(0x10) |
		RTI_DATA1_MEM_RX_URNG_C(0x30) |
		RTI_DATA1_MEM_RX_TIMER_AC_EN;

	ग_लिखोq(val64, &bar0->rti_data1_mem);

	val64 = RTI_DATA2_MEM_RX_UFC_A(0x1) |
		RTI_DATA2_MEM_RX_UFC_B(0x2) ;
	अगर (nic->config.पूर्णांकr_type == MSI_X)
		val64 |= (RTI_DATA2_MEM_RX_UFC_C(0x20) |
			  RTI_DATA2_MEM_RX_UFC_D(0x40));
	अन्यथा
		val64 |= (RTI_DATA2_MEM_RX_UFC_C(0x40) |
			  RTI_DATA2_MEM_RX_UFC_D(0x80));
	ग_लिखोq(val64, &bar0->rti_data2_mem);

	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		val64 = RTI_CMD_MEM_WE |
			RTI_CMD_MEM_STROBE_NEW_CMD |
			RTI_CMD_MEM_OFFSET(i);
		ग_लिखोq(val64, &bar0->rti_command_mem);

		/*
		 * Once the operation completes, the Strobe bit of the
		 * command रेजिस्टर will be reset. We poll क्रम this
		 * particular condition. We रुको क्रम a maximum of 500ms
		 * क्रम the operation to complete, अगर it's not complete
		 * by then we वापस error.
		 */
		समय = 0;
		जबतक (true) अणु
			val64 = पढ़ोq(&bar0->rti_command_mem);
			अगर (!(val64 & RTI_CMD_MEM_STROBE_NEW_CMD))
				अवरोध;

			अगर (समय > 10) अणु
				DBG_PRINT(ERR_DBG, "%s: RTI init failed\n",
					  dev->name);
				वापस -ENODEV;
			पूर्ण
			समय++;
			msleep(50);
		पूर्ण
	पूर्ण

	/*
	 * Initializing proper values as Pause threshold पूर्णांकo all
	 * the 8 Queues on Rx side.
	 */
	ग_लिखोq(0xffbbffbbffbbffbbULL, &bar0->mc_छोड़ो_thresh_q0q3);
	ग_लिखोq(0xffbbffbbffbbffbbULL, &bar0->mc_छोड़ो_thresh_q4q7);

	/* Disable RMAC PAD STRIPPING */
	add = &bar0->mac_cfg;
	val64 = पढ़ोq(&bar0->mac_cfg);
	val64 &= ~(MAC_CFG_RMAC_STRIP_PAD);
	ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
	ग_लिखोl((u32) (val64), add);
	ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
	ग_लिखोl((u32) (val64 >> 32), (add + 4));
	val64 = पढ़ोq(&bar0->mac_cfg);

	/* Enable FCS stripping by adapter */
	add = &bar0->mac_cfg;
	val64 = पढ़ोq(&bar0->mac_cfg);
	val64 |= MAC_CFG_RMAC_STRIP_FCS;
	अगर (nic->device_type == XFRAME_II_DEVICE)
		ग_लिखोq(val64, &bar0->mac_cfg);
	अन्यथा अणु
		ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
		ग_लिखोl((u32) (val64), add);
		ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
		ग_लिखोl((u32) (val64 >> 32), (add + 4));
	पूर्ण

	/*
	 * Set the समय value to be inserted in the छोड़ो frame
	 * generated by xena.
	 */
	val64 = पढ़ोq(&bar0->rmac_छोड़ो_cfg);
	val64 &= ~(RMAC_PAUSE_HG_PTIME(0xffff));
	val64 |= RMAC_PAUSE_HG_PTIME(nic->mac_control.rmac_छोड़ो_समय);
	ग_लिखोq(val64, &bar0->rmac_छोड़ो_cfg);

	/*
	 * Set the Threshold Limit क्रम Generating the छोड़ो frame
	 * If the amount of data in any Queue exceeds ratio of
	 * (mac_control.mc_छोड़ो_threshold_q0q3 or q4q7)/256
	 * छोड़ो frame is generated
	 */
	val64 = 0;
	क्रम (i = 0; i < 4; i++) अणु
		val64 |= (((u64)0xFF00 |
			   nic->mac_control.mc_छोड़ो_threshold_q0q3)
			  << (i * 2 * 8));
	पूर्ण
	ग_लिखोq(val64, &bar0->mc_छोड़ो_thresh_q0q3);

	val64 = 0;
	क्रम (i = 0; i < 4; i++) अणु
		val64 |= (((u64)0xFF00 |
			   nic->mac_control.mc_छोड़ो_threshold_q4q7)
			  << (i * 2 * 8));
	पूर्ण
	ग_लिखोq(val64, &bar0->mc_छोड़ो_thresh_q4q7);

	/*
	 * TxDMA will stop Read request अगर the number of पढ़ो split has
	 * exceeded the limit poपूर्णांकed by shared_splits
	 */
	val64 = पढ़ोq(&bar0->pic_control);
	val64 |= PIC_CNTL_SHARED_SPLITS(shared_splits);
	ग_लिखोq(val64, &bar0->pic_control);

	अगर (nic->config.bus_speed == 266) अणु
		ग_लिखोq(TXREQTO_VAL(0x7f) | TXREQTO_EN, &bar0->txreqसमयout);
		ग_लिखोq(0x0, &bar0->पढ़ो_retry_delay);
		ग_लिखोq(0x0, &bar0->ग_लिखो_retry_delay);
	पूर्ण

	/*
	 * Programming the Herc to split every ग_लिखो transaction
	 * that करोes not start on an ADB to reduce disconnects.
	 */
	अगर (nic->device_type == XFRAME_II_DEVICE) अणु
		val64 = FAULT_BEHAVIOUR | EXT_REQ_EN |
			MISC_LINK_STABILITY_PRD(3);
		ग_लिखोq(val64, &bar0->misc_control);
		val64 = पढ़ोq(&bar0->pic_control2);
		val64 &= ~(s2BIT(13)|s2BIT(14)|s2BIT(15));
		ग_लिखोq(val64, &bar0->pic_control2);
	पूर्ण
	अगर (म_माला(nic->product_name, "CX4")) अणु
		val64 = TMAC_AVG_IPG(0x17);
		ग_लिखोq(val64, &bar0->पंचांगac_avg_ipg);
	पूर्ण

	वापस SUCCESS;
पूर्ण
#घोषणा LINK_UP_DOWN_INTERRUPT		1
#घोषणा MAC_RMAC_ERR_TIMER		2

अटल पूर्णांक s2io_link_fault_indication(काष्ठा s2io_nic *nic)
अणु
	अगर (nic->device_type == XFRAME_II_DEVICE)
		वापस LINK_UP_DOWN_INTERRUPT;
	अन्यथा
		वापस MAC_RMAC_ERR_TIMER;
पूर्ण

/**
 *  करो_s2io_ग_लिखो_bits -  update alarm bits in alarm रेजिस्टर
 *  @value: alarm bits
 *  @flag: पूर्णांकerrupt status
 *  @addr: address value
 *  Description: update alarm bits in alarm रेजिस्टर
 *  Return Value:
 *  NONE.
 */
अटल व्योम करो_s2io_ग_लिखो_bits(u64 value, पूर्णांक flag, व्योम __iomem *addr)
अणु
	u64 temp64;

	temp64 = पढ़ोq(addr);

	अगर (flag == ENABLE_INTRS)
		temp64 &= ~((u64)value);
	अन्यथा
		temp64 |= ((u64)value);
	ग_लिखोq(temp64, addr);
पूर्ण

अटल व्योम en_dis_err_alarms(काष्ठा s2io_nic *nic, u16 mask, पूर्णांक flag)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	रेजिस्टर u64 gen_पूर्णांक_mask = 0;
	u64 पूर्णांकerruptible;

	ग_लिखोq(DISABLE_ALL_INTRS, &bar0->general_पूर्णांक_mask);
	अगर (mask & TX_DMA_INTR) अणु
		gen_पूर्णांक_mask |= TXDMA_INT_M;

		करो_s2io_ग_लिखो_bits(TXDMA_TDA_INT | TXDMA_PFC_INT |
				   TXDMA_PCC_INT | TXDMA_TTI_INT |
				   TXDMA_LSO_INT | TXDMA_TPA_INT |
				   TXDMA_SM_INT, flag, &bar0->txdma_पूर्णांक_mask);

		करो_s2io_ग_लिखो_bits(PFC_ECC_DB_ERR | PFC_SM_ERR_ALARM |
				   PFC_MISC_0_ERR | PFC_MISC_1_ERR |
				   PFC_PCIX_ERR | PFC_ECC_SG_ERR, flag,
				   &bar0->pfc_err_mask);

		करो_s2io_ग_लिखो_bits(TDA_Fn_ECC_DB_ERR | TDA_SM0_ERR_ALARM |
				   TDA_SM1_ERR_ALARM | TDA_Fn_ECC_SG_ERR |
				   TDA_PCIX_ERR, flag, &bar0->tda_err_mask);

		करो_s2io_ग_लिखो_bits(PCC_FB_ECC_DB_ERR | PCC_TXB_ECC_DB_ERR |
				   PCC_SM_ERR_ALARM | PCC_WR_ERR_ALARM |
				   PCC_N_SERR | PCC_6_COF_OV_ERR |
				   PCC_7_COF_OV_ERR | PCC_6_LSO_OV_ERR |
				   PCC_7_LSO_OV_ERR | PCC_FB_ECC_SG_ERR |
				   PCC_TXB_ECC_SG_ERR,
				   flag, &bar0->pcc_err_mask);

		करो_s2io_ग_लिखो_bits(TTI_SM_ERR_ALARM | TTI_ECC_SG_ERR |
				   TTI_ECC_DB_ERR, flag, &bar0->tti_err_mask);

		करो_s2io_ग_लिखो_bits(LSO6_ABORT | LSO7_ABORT |
				   LSO6_SM_ERR_ALARM | LSO7_SM_ERR_ALARM |
				   LSO6_SEND_OFLOW | LSO7_SEND_OFLOW,
				   flag, &bar0->lso_err_mask);

		करो_s2io_ग_लिखो_bits(TPA_SM_ERR_ALARM | TPA_TX_FRM_DROP,
				   flag, &bar0->tpa_err_mask);

		करो_s2io_ग_लिखो_bits(SM_SM_ERR_ALARM, flag, &bar0->sm_err_mask);
	पूर्ण

	अगर (mask & TX_MAC_INTR) अणु
		gen_पूर्णांक_mask |= TXMAC_INT_M;
		करो_s2io_ग_लिखो_bits(MAC_INT_STATUS_TMAC_INT, flag,
				   &bar0->mac_पूर्णांक_mask);
		करो_s2io_ग_लिखो_bits(TMAC_TX_BUF_OVRN | TMAC_TX_SM_ERR |
				   TMAC_ECC_SG_ERR | TMAC_ECC_DB_ERR |
				   TMAC_DESC_ECC_SG_ERR | TMAC_DESC_ECC_DB_ERR,
				   flag, &bar0->mac_पंचांगac_err_mask);
	पूर्ण

	अगर (mask & TX_XGXS_INTR) अणु
		gen_पूर्णांक_mask |= TXXGXS_INT_M;
		करो_s2io_ग_लिखो_bits(XGXS_INT_STATUS_TXGXS, flag,
				   &bar0->xgxs_पूर्णांक_mask);
		करो_s2io_ग_लिखो_bits(TXGXS_ESTORE_UFLOW | TXGXS_TX_SM_ERR |
				   TXGXS_ECC_SG_ERR | TXGXS_ECC_DB_ERR,
				   flag, &bar0->xgxs_txgxs_err_mask);
	पूर्ण

	अगर (mask & RX_DMA_INTR) अणु
		gen_पूर्णांक_mask |= RXDMA_INT_M;
		करो_s2io_ग_लिखो_bits(RXDMA_INT_RC_INT_M | RXDMA_INT_RPA_INT_M |
				   RXDMA_INT_RDA_INT_M | RXDMA_INT_RTI_INT_M,
				   flag, &bar0->rxdma_पूर्णांक_mask);
		करो_s2io_ग_लिखो_bits(RC_PRCn_ECC_DB_ERR | RC_FTC_ECC_DB_ERR |
				   RC_PRCn_SM_ERR_ALARM | RC_FTC_SM_ERR_ALARM |
				   RC_PRCn_ECC_SG_ERR | RC_FTC_ECC_SG_ERR |
				   RC_RDA_FAIL_WR_Rn, flag, &bar0->rc_err_mask);
		करो_s2io_ग_लिखो_bits(PRC_PCI_AB_RD_Rn | PRC_PCI_AB_WR_Rn |
				   PRC_PCI_AB_F_WR_Rn | PRC_PCI_DP_RD_Rn |
				   PRC_PCI_DP_WR_Rn | PRC_PCI_DP_F_WR_Rn, flag,
				   &bar0->prc_pcix_err_mask);
		करो_s2io_ग_लिखो_bits(RPA_SM_ERR_ALARM | RPA_CREDIT_ERR |
				   RPA_ECC_SG_ERR | RPA_ECC_DB_ERR, flag,
				   &bar0->rpa_err_mask);
		करो_s2io_ग_लिखो_bits(RDA_RXDn_ECC_DB_ERR | RDA_FRM_ECC_DB_N_AERR |
				   RDA_SM1_ERR_ALARM | RDA_SM0_ERR_ALARM |
				   RDA_RXD_ECC_DB_SERR | RDA_RXDn_ECC_SG_ERR |
				   RDA_FRM_ECC_SG_ERR |
				   RDA_MISC_ERR|RDA_PCIX_ERR,
				   flag, &bar0->rda_err_mask);
		करो_s2io_ग_लिखो_bits(RTI_SM_ERR_ALARM |
				   RTI_ECC_SG_ERR | RTI_ECC_DB_ERR,
				   flag, &bar0->rti_err_mask);
	पूर्ण

	अगर (mask & RX_MAC_INTR) अणु
		gen_पूर्णांक_mask |= RXMAC_INT_M;
		करो_s2io_ग_लिखो_bits(MAC_INT_STATUS_RMAC_INT, flag,
				   &bar0->mac_पूर्णांक_mask);
		पूर्णांकerruptible = (RMAC_RX_BUFF_OVRN | RMAC_RX_SM_ERR |
				 RMAC_UNUSED_INT | RMAC_SINGLE_ECC_ERR |
				 RMAC_DOUBLE_ECC_ERR);
		अगर (s2io_link_fault_indication(nic) == MAC_RMAC_ERR_TIMER)
			पूर्णांकerruptible |= RMAC_LINK_STATE_CHANGE_INT;
		करो_s2io_ग_लिखो_bits(पूर्णांकerruptible,
				   flag, &bar0->mac_rmac_err_mask);
	पूर्ण

	अगर (mask & RX_XGXS_INTR) अणु
		gen_पूर्णांक_mask |= RXXGXS_INT_M;
		करो_s2io_ग_लिखो_bits(XGXS_INT_STATUS_RXGXS, flag,
				   &bar0->xgxs_पूर्णांक_mask);
		करो_s2io_ग_लिखो_bits(RXGXS_ESTORE_OFLOW | RXGXS_RX_SM_ERR, flag,
				   &bar0->xgxs_rxgxs_err_mask);
	पूर्ण

	अगर (mask & MC_INTR) अणु
		gen_पूर्णांक_mask |= MC_INT_M;
		करो_s2io_ग_लिखो_bits(MC_INT_MASK_MC_INT,
				   flag, &bar0->mc_पूर्णांक_mask);
		करो_s2io_ग_लिखो_bits(MC_ERR_REG_SM_ERR | MC_ERR_REG_ECC_ALL_SNG |
				   MC_ERR_REG_ECC_ALL_DBL | PLL_LOCK_N, flag,
				   &bar0->mc_err_mask);
	पूर्ण
	nic->general_पूर्णांक_mask = gen_पूर्णांक_mask;

	/* Remove this line when alarm पूर्णांकerrupts are enabled */
	nic->general_पूर्णांक_mask = 0;
पूर्ण

/**
 *  en_dis_able_nic_पूर्णांकrs - Enable or Disable the पूर्णांकerrupts
 *  @nic: device निजी variable,
 *  @mask: A mask indicating which Intr block must be modअगरied and,
 *  @flag: A flag indicating whether to enable or disable the Intrs.
 *  Description: This function will either disable or enable the पूर्णांकerrupts
 *  depending on the flag argument. The mask argument can be used to
 *  enable/disable any Intr block.
 *  Return Value: NONE.
 */

अटल व्योम en_dis_able_nic_पूर्णांकrs(काष्ठा s2io_nic *nic, u16 mask, पूर्णांक flag)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	रेजिस्टर u64 temp64 = 0, पूर्णांकr_mask = 0;

	पूर्णांकr_mask = nic->general_पूर्णांक_mask;

	/*  Top level पूर्णांकerrupt classअगरication */
	/*  PIC Interrupts */
	अगर (mask & TX_PIC_INTR) अणु
		/*  Enable PIC Intrs in the general पूर्णांकr mask रेजिस्टर */
		पूर्णांकr_mask |= TXPIC_INT_M;
		अगर (flag == ENABLE_INTRS) अणु
			/*
			 * If Hercules adapter enable GPIO otherwise
			 * disable all PCIX, Flash, MDIO, IIC and GPIO
			 * पूर्णांकerrupts क्रम now.
			 * TODO
			 */
			अगर (s2io_link_fault_indication(nic) ==
			    LINK_UP_DOWN_INTERRUPT) अणु
				करो_s2io_ग_लिखो_bits(PIC_INT_GPIO, flag,
						   &bar0->pic_पूर्णांक_mask);
				करो_s2io_ग_लिखो_bits(GPIO_INT_MASK_LINK_UP, flag,
						   &bar0->gpio_पूर्णांक_mask);
			पूर्ण अन्यथा
				ग_लिखोq(DISABLE_ALL_INTRS, &bar0->pic_पूर्णांक_mask);
		पूर्ण अन्यथा अगर (flag == DISABLE_INTRS) अणु
			/*
			 * Disable PIC Intrs in the general
			 * पूर्णांकr mask रेजिस्टर
			 */
			ग_लिखोq(DISABLE_ALL_INTRS, &bar0->pic_पूर्णांक_mask);
		पूर्ण
	पूर्ण

	/*  Tx traffic पूर्णांकerrupts */
	अगर (mask & TX_TRAFFIC_INTR) अणु
		पूर्णांकr_mask |= TXTRAFFIC_INT_M;
		अगर (flag == ENABLE_INTRS) अणु
			/*
			 * Enable all the Tx side पूर्णांकerrupts
			 * writing 0 Enables all 64 TX पूर्णांकerrupt levels
			 */
			ग_लिखोq(0x0, &bar0->tx_traffic_mask);
		पूर्ण अन्यथा अगर (flag == DISABLE_INTRS) अणु
			/*
			 * Disable Tx Traffic Intrs in the general पूर्णांकr mask
			 * रेजिस्टर.
			 */
			ग_लिखोq(DISABLE_ALL_INTRS, &bar0->tx_traffic_mask);
		पूर्ण
	पूर्ण

	/*  Rx traffic पूर्णांकerrupts */
	अगर (mask & RX_TRAFFIC_INTR) अणु
		पूर्णांकr_mask |= RXTRAFFIC_INT_M;
		अगर (flag == ENABLE_INTRS) अणु
			/* writing 0 Enables all 8 RX पूर्णांकerrupt levels */
			ग_लिखोq(0x0, &bar0->rx_traffic_mask);
		पूर्ण अन्यथा अगर (flag == DISABLE_INTRS) अणु
			/*
			 * Disable Rx Traffic Intrs in the general पूर्णांकr mask
			 * रेजिस्टर.
			 */
			ग_लिखोq(DISABLE_ALL_INTRS, &bar0->rx_traffic_mask);
		पूर्ण
	पूर्ण

	temp64 = पढ़ोq(&bar0->general_पूर्णांक_mask);
	अगर (flag == ENABLE_INTRS)
		temp64 &= ~((u64)पूर्णांकr_mask);
	अन्यथा
		temp64 = DISABLE_ALL_INTRS;
	ग_लिखोq(temp64, &bar0->general_पूर्णांक_mask);

	nic->general_पूर्णांक_mask = पढ़ोq(&bar0->general_पूर्णांक_mask);
पूर्ण

/**
 *  verअगरy_pcc_quiescent- Checks क्रम PCC quiescent state
 *  @sp : निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 *  s2io_nic काष्ठाure.
 *  @flag: boolean controlling function path
 *  Return: 1 If PCC is quiescence
 *          0 If PCC is not quiescence
 */
अटल पूर्णांक verअगरy_pcc_quiescent(काष्ठा s2io_nic *sp, पूर्णांक flag)
अणु
	पूर्णांक ret = 0, herc;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64 = पढ़ोq(&bar0->adapter_status);

	herc = (sp->device_type == XFRAME_II_DEVICE);

	अगर (flag == false) अणु
		अगर ((!herc && (sp->pdev->revision >= 4)) || herc) अणु
			अगर (!(val64 & ADAPTER_STATUS_RMAC_PCC_IDLE))
				ret = 1;
		पूर्ण अन्यथा अणु
			अगर (!(val64 & ADAPTER_STATUS_RMAC_PCC_FOUR_IDLE))
				ret = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((!herc && (sp->pdev->revision >= 4)) || herc) अणु
			अगर (((val64 & ADAPTER_STATUS_RMAC_PCC_IDLE) ==
			     ADAPTER_STATUS_RMAC_PCC_IDLE))
				ret = 1;
		पूर्ण अन्यथा अणु
			अगर (((val64 & ADAPTER_STATUS_RMAC_PCC_FOUR_IDLE) ==
			     ADAPTER_STATUS_RMAC_PCC_FOUR_IDLE))
				ret = 1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
/**
 *  verअगरy_xena_quiescence - Checks whether the H/W is पढ़ोy
 *  @sp : निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 *  s2io_nic काष्ठाure.
 *  Description: Returns whether the H/W is पढ़ोy to go or not. Depending
 *  on whether adapter enable bit was written or not the comparison
 *  dअगरfers and the calling function passes the input argument flag to
 *  indicate this.
 *  Return: 1 If xena is quiescence
 *          0 If Xena is not quiescence
 */

अटल पूर्णांक verअगरy_xena_quiescence(काष्ठा s2io_nic *sp)
अणु
	पूर्णांक  mode;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64 = पढ़ोq(&bar0->adapter_status);
	mode = s2io_verअगरy_pci_mode(sp);

	अगर (!(val64 & ADAPTER_STATUS_TDMA_READY)) अणु
		DBG_PRINT(ERR_DBG, "TDMA is not ready!\n");
		वापस 0;
	पूर्ण
	अगर (!(val64 & ADAPTER_STATUS_RDMA_READY)) अणु
		DBG_PRINT(ERR_DBG, "RDMA is not ready!\n");
		वापस 0;
	पूर्ण
	अगर (!(val64 & ADAPTER_STATUS_PFC_READY)) अणु
		DBG_PRINT(ERR_DBG, "PFC is not ready!\n");
		वापस 0;
	पूर्ण
	अगर (!(val64 & ADAPTER_STATUS_TMAC_BUF_EMPTY)) अणु
		DBG_PRINT(ERR_DBG, "TMAC BUF is not empty!\n");
		वापस 0;
	पूर्ण
	अगर (!(val64 & ADAPTER_STATUS_PIC_QUIESCENT)) अणु
		DBG_PRINT(ERR_DBG, "PIC is not QUIESCENT!\n");
		वापस 0;
	पूर्ण
	अगर (!(val64 & ADAPTER_STATUS_MC_DRAM_READY)) अणु
		DBG_PRINT(ERR_DBG, "MC_DRAM is not ready!\n");
		वापस 0;
	पूर्ण
	अगर (!(val64 & ADAPTER_STATUS_MC_QUEUES_READY)) अणु
		DBG_PRINT(ERR_DBG, "MC_QUEUES is not ready!\n");
		वापस 0;
	पूर्ण
	अगर (!(val64 & ADAPTER_STATUS_M_PLL_LOCK)) अणु
		DBG_PRINT(ERR_DBG, "M_PLL is not locked!\n");
		वापस 0;
	पूर्ण

	/*
	 * In PCI 33 mode, the P_PLL is not used, and thereक्रमe,
	 * the the P_PLL_LOCK bit in the adapter_status रेजिस्टर will
	 * not be निश्चितed.
	 */
	अगर (!(val64 & ADAPTER_STATUS_P_PLL_LOCK) &&
	    sp->device_type == XFRAME_II_DEVICE &&
	    mode != PCI_MODE_PCI_33) अणु
		DBG_PRINT(ERR_DBG, "P_PLL is not locked!\n");
		वापस 0;
	पूर्ण
	अगर (!((val64 & ADAPTER_STATUS_RC_PRC_QUIESCENT) ==
	      ADAPTER_STATUS_RC_PRC_QUIESCENT)) अणु
		DBG_PRINT(ERR_DBG, "RC_PRC is not QUIESCENT!\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * fix_mac_address -  Fix क्रम Mac addr problem on Alpha platक्रमms
 * @sp: Poपूर्णांकer to device specअगरc काष्ठाure
 * Description :
 * New procedure to clear mac address पढ़ोing  problems on Alpha platक्रमms
 *
 */

अटल व्योम fix_mac_address(काष्ठा s2io_nic *sp)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	पूर्णांक i = 0;

	जबतक (fix_mac[i] != END_SIGN) अणु
		ग_लिखोq(fix_mac[i++], &bar0->gpio_control);
		udelay(10);
		(व्योम) पढ़ोq(&bar0->gpio_control);
	पूर्ण
पूर्ण

/**
 *  start_nic - Turns the device on
 *  @nic : device निजी variable.
 *  Description:
 *  This function actually turns the device on. Beक्रमe this  function is
 *  called,all Registers are configured from their reset states
 *  and shared memory is allocated but the NIC is still quiescent. On
 *  calling this function, the device पूर्णांकerrupts are cleared and the NIC is
 *  literally चयनed on by writing पूर्णांकo the adapter control रेजिस्टर.
 *  Return Value:
 *  SUCCESS on success and -1 on failure.
 */

अटल पूर्णांक start_nic(काष्ठा s2io_nic *nic)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	काष्ठा net_device *dev = nic->dev;
	रेजिस्टर u64 val64 = 0;
	u16 subid, i;
	काष्ठा config_param *config = &nic->config;
	काष्ठा mac_info *mac_control = &nic->mac_control;

	/*  PRC Initialization and configuration */
	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा ring_info *ring = &mac_control->rings[i];

		ग_लिखोq((u64)ring->rx_blocks[0].block_dma_addr,
		       &bar0->prc_rxd0_n[i]);

		val64 = पढ़ोq(&bar0->prc_ctrl_n[i]);
		अगर (nic->rxd_mode == RXD_MODE_1)
			val64 |= PRC_CTRL_RC_ENABLED;
		अन्यथा
			val64 |= PRC_CTRL_RC_ENABLED | PRC_CTRL_RING_MODE_3;
		अगर (nic->device_type == XFRAME_II_DEVICE)
			val64 |= PRC_CTRL_GROUP_READS;
		val64 &= ~PRC_CTRL_RXD_BACKOFF_INTERVAL(0xFFFFFF);
		val64 |= PRC_CTRL_RXD_BACKOFF_INTERVAL(0x1000);
		ग_लिखोq(val64, &bar0->prc_ctrl_n[i]);
	पूर्ण

	अगर (nic->rxd_mode == RXD_MODE_3B) अणु
		/* Enabling 2 buffer mode by writing पूर्णांकo Rx_pa_cfg reg. */
		val64 = पढ़ोq(&bar0->rx_pa_cfg);
		val64 |= RX_PA_CFG_IGNORE_L2_ERR;
		ग_लिखोq(val64, &bar0->rx_pa_cfg);
	पूर्ण

	अगर (vlan_tag_strip == 0) अणु
		val64 = पढ़ोq(&bar0->rx_pa_cfg);
		val64 &= ~RX_PA_CFG_STRIP_VLAN_TAG;
		ग_लिखोq(val64, &bar0->rx_pa_cfg);
		nic->vlan_strip_flag = 0;
	पूर्ण

	/*
	 * Enabling MC-RLDRAM. After enabling the device, we समयout
	 * क्रम around 100ms, which is approximately the समय required
	 * क्रम the device to be पढ़ोy क्रम operation.
	 */
	val64 = पढ़ोq(&bar0->mc_rldram_mrs);
	val64 |= MC_RLDRAM_QUEUE_SIZE_ENABLE | MC_RLDRAM_MRS_ENABLE;
	SPECIAL_REG_WRITE(val64, &bar0->mc_rldram_mrs, UF);
	val64 = पढ़ोq(&bar0->mc_rldram_mrs);

	msleep(100);	/* Delay by around 100 ms. */

	/* Enabling ECC Protection. */
	val64 = पढ़ोq(&bar0->adapter_control);
	val64 &= ~ADAPTER_ECC_EN;
	ग_लिखोq(val64, &bar0->adapter_control);

	/*
	 * Verअगरy अगर the device is पढ़ोy to be enabled, अगर so enable
	 * it.
	 */
	val64 = पढ़ोq(&bar0->adapter_status);
	अगर (!verअगरy_xena_quiescence(nic)) अणु
		DBG_PRINT(ERR_DBG, "%s: device is not ready, "
			  "Adapter status reads: 0x%llx\n",
			  dev->name, (अचिन्हित दीर्घ दीर्घ)val64);
		वापस FAILURE;
	पूर्ण

	/*
	 * With some चयनes, link might be alपढ़ोy up at this poपूर्णांक.
	 * Because of this weird behavior, when we enable laser,
	 * we may not get link. We need to handle this. We cannot
	 * figure out which चयन is misbehaving. So we are क्रमced to
	 * make a global change.
	 */

	/* Enabling Laser. */
	val64 = पढ़ोq(&bar0->adapter_control);
	val64 |= ADAPTER_EOI_TX_ON;
	ग_लिखोq(val64, &bar0->adapter_control);

	अगर (s2io_link_fault_indication(nic) == MAC_RMAC_ERR_TIMER) अणु
		/*
		 * Dont see link state पूर्णांकerrupts initially on some चयनes,
		 * so directly scheduling the link state task here.
		 */
		schedule_work(&nic->set_link_task);
	पूर्ण
	/* SXE-002: Initialize link and activity LED */
	subid = nic->pdev->subप्रणाली_device;
	अगर (((subid & 0xFF) >= 0x07) &&
	    (nic->device_type == XFRAME_I_DEVICE)) अणु
		val64 = पढ़ोq(&bar0->gpio_control);
		val64 |= 0x0000800000000000ULL;
		ग_लिखोq(val64, &bar0->gpio_control);
		val64 = 0x0411040400000000ULL;
		ग_लिखोq(val64, (व्योम __iomem *)bar0 + 0x2700);
	पूर्ण

	वापस SUCCESS;
पूर्ण
/**
 * s2io_txdl_माला_लोkb - Get the skb from txdl, unmap and वापस skb
 * @fअगरo_data: fअगरo data poपूर्णांकer
 * @txdlp: descriptor
 * @get_off: unused
 */
अटल काष्ठा sk_buff *s2io_txdl_माला_लोkb(काष्ठा fअगरo_info *fअगरo_data,
					काष्ठा TxD *txdlp, पूर्णांक get_off)
अणु
	काष्ठा s2io_nic *nic = fअगरo_data->nic;
	काष्ठा sk_buff *skb;
	काष्ठा TxD *txds;
	u16 j, frg_cnt;

	txds = txdlp;
	अगर (txds->Host_Control == (u64)(दीर्घ)fअगरo_data->ufo_in_band_v) अणु
		dma_unmap_single(&nic->pdev->dev,
				 (dma_addr_t)txds->Buffer_Poपूर्णांकer,
				 माप(u64), DMA_TO_DEVICE);
		txds++;
	पूर्ण

	skb = (काष्ठा sk_buff *)((अचिन्हित दीर्घ)txds->Host_Control);
	अगर (!skb) अणु
		स_रखो(txdlp, 0, (माप(काष्ठा TxD) * fअगरo_data->max_txds));
		वापस शून्य;
	पूर्ण
	dma_unmap_single(&nic->pdev->dev, (dma_addr_t)txds->Buffer_Poपूर्णांकer,
			 skb_headlen(skb), DMA_TO_DEVICE);
	frg_cnt = skb_shinfo(skb)->nr_frags;
	अगर (frg_cnt) अणु
		txds++;
		क्रम (j = 0; j < frg_cnt; j++, txds++) अणु
			स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[j];
			अगर (!txds->Buffer_Poपूर्णांकer)
				अवरोध;
			dma_unmap_page(&nic->pdev->dev,
				       (dma_addr_t)txds->Buffer_Poपूर्णांकer,
				       skb_frag_size(frag), DMA_TO_DEVICE);
		पूर्ण
	पूर्ण
	स_रखो(txdlp, 0, (माप(काष्ठा TxD) * fअगरo_data->max_txds));
	वापस skb;
पूर्ण

/**
 *  मुक्त_tx_buffers - Free all queued Tx buffers
 *  @nic : device निजी variable.
 *  Description:
 *  Free all queued Tx buffers.
 *  Return Value: व्योम
 */

अटल व्योम मुक्त_tx_buffers(काष्ठा s2io_nic *nic)
अणु
	काष्ठा net_device *dev = nic->dev;
	काष्ठा sk_buff *skb;
	काष्ठा TxD *txdp;
	पूर्णांक i, j;
	पूर्णांक cnt = 0;
	काष्ठा config_param *config = &nic->config;
	काष्ठा mac_info *mac_control = &nic->mac_control;
	काष्ठा stat_block *stats = mac_control->stats_info;
	काष्ठा swStat *swstats = &stats->sw_stat;

	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];
		काष्ठा fअगरo_info *fअगरo = &mac_control->fअगरos[i];
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&fअगरo->tx_lock, flags);
		क्रम (j = 0; j < tx_cfg->fअगरo_len; j++) अणु
			txdp = fअगरo->list_info[j].list_virt_addr;
			skb = s2io_txdl_माला_लोkb(&mac_control->fअगरos[i], txdp, j);
			अगर (skb) अणु
				swstats->mem_मुक्तd += skb->truesize;
				dev_kमुक्त_skb(skb);
				cnt++;
			पूर्ण
		पूर्ण
		DBG_PRINT(INTR_DBG,
			  "%s: forcibly freeing %d skbs on FIFO%d\n",
			  dev->name, cnt, i);
		fअगरo->tx_curr_get_info.offset = 0;
		fअगरo->tx_curr_put_info.offset = 0;
		spin_unlock_irqrestore(&fअगरo->tx_lock, flags);
	पूर्ण
पूर्ण

/**
 *   stop_nic -  To stop the nic
 *   @nic : device निजी variable.
 *   Description:
 *   This function करोes exactly the opposite of what the start_nic()
 *   function करोes. This function is called to stop the device.
 *   Return Value:
 *   व्योम.
 */

अटल व्योम stop_nic(काष्ठा s2io_nic *nic)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	रेजिस्टर u64 val64 = 0;
	u16 पूर्णांकerruptible;

	/*  Disable all पूर्णांकerrupts */
	en_dis_err_alarms(nic, ENA_ALL_INTRS, DISABLE_INTRS);
	पूर्णांकerruptible = TX_TRAFFIC_INTR | RX_TRAFFIC_INTR;
	पूर्णांकerruptible |= TX_PIC_INTR;
	en_dis_able_nic_पूर्णांकrs(nic, पूर्णांकerruptible, DISABLE_INTRS);

	/* Clearing Adapter_En bit of ADAPTER_CONTROL Register */
	val64 = पढ़ोq(&bar0->adapter_control);
	val64 &= ~(ADAPTER_CNTL_EN);
	ग_लिखोq(val64, &bar0->adapter_control);
पूर्ण

/**
 *  fill_rx_buffers - Allocates the Rx side skbs
 *  @nic : device निजी variable.
 *  @ring: per ring काष्ठाure
 *  @from_card_up: If this is true, we will map the buffer to get
 *     the dma address क्रम buf0 and buf1 to give it to the card.
 *     Else we will sync the alपढ़ोy mapped buffer to give it to the card.
 *  Description:
 *  The function allocates Rx side skbs and माला_दो the physical
 *  address of these buffers पूर्णांकo the RxD buffer poपूर्णांकers, so that the NIC
 *  can DMA the received frame पूर्णांकo these locations.
 *  The NIC supports 3 receive modes, viz
 *  1. single buffer,
 *  2. three buffer and
 *  3. Five buffer modes.
 *  Each mode defines how many fragments the received frame will be split
 *  up पूर्णांकo by the NIC. The frame is split पूर्णांकo L3 header, L4 Header,
 *  L4 payload in three buffer mode and in 5 buffer mode, L4 payload itself
 *  is split पूर्णांकo 3 fragments. As of now only single buffer mode is
 *  supported.
 *   Return Value:
 *  SUCCESS on success or an appropriate -ve value on failure.
 */
अटल पूर्णांक fill_rx_buffers(काष्ठा s2io_nic *nic, काष्ठा ring_info *ring,
			   पूर्णांक from_card_up)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा RxD_t *rxdp;
	पूर्णांक off, size, block_no, block_no1;
	u32 alloc_tab = 0;
	u32 alloc_cnt;
	u64 पंचांगp;
	काष्ठा buffAdd *ba;
	काष्ठा RxD_t *first_rxdp = शून्य;
	u64 Buffer0_ptr = 0, Buffer1_ptr = 0;
	काष्ठा RxD1 *rxdp1;
	काष्ठा RxD3 *rxdp3;
	काष्ठा swStat *swstats = &ring->nic->mac_control.stats_info->sw_stat;

	alloc_cnt = ring->pkt_cnt - ring->rx_bufs_left;

	block_no1 = ring->rx_curr_get_info.block_index;
	जबतक (alloc_tab < alloc_cnt) अणु
		block_no = ring->rx_curr_put_info.block_index;

		off = ring->rx_curr_put_info.offset;

		rxdp = ring->rx_blocks[block_no].rxds[off].virt_addr;

		अगर ((block_no == block_no1) &&
		    (off == ring->rx_curr_get_info.offset) &&
		    (rxdp->Host_Control)) अणु
			DBG_PRINT(INTR_DBG, "%s: Get and Put info equated\n",
				  ring->dev->name);
			जाओ end;
		पूर्ण
		अगर (off && (off == ring->rxd_count)) अणु
			ring->rx_curr_put_info.block_index++;
			अगर (ring->rx_curr_put_info.block_index ==
			    ring->block_count)
				ring->rx_curr_put_info.block_index = 0;
			block_no = ring->rx_curr_put_info.block_index;
			off = 0;
			ring->rx_curr_put_info.offset = off;
			rxdp = ring->rx_blocks[block_no].block_virt_addr;
			DBG_PRINT(INTR_DBG, "%s: Next block at: %p\n",
				  ring->dev->name, rxdp);

		पूर्ण

		अगर ((rxdp->Control_1 & RXD_OWN_XENA) &&
		    ((ring->rxd_mode == RXD_MODE_3B) &&
		     (rxdp->Control_2 & s2BIT(0)))) अणु
			ring->rx_curr_put_info.offset = off;
			जाओ end;
		पूर्ण
		/* calculate size of skb based on ring mode */
		size = ring->mtu +
			HEADER_ETHERNET_II_802_3_SIZE +
			HEADER_802_2_SIZE + HEADER_SNAP_SIZE;
		अगर (ring->rxd_mode == RXD_MODE_1)
			size += NET_IP_ALIGN;
		अन्यथा
			size = ring->mtu + ALIGN_SIZE + BUF0_LEN + 4;

		/* allocate skb */
		skb = netdev_alloc_skb(nic->dev, size);
		अगर (!skb) अणु
			DBG_PRINT(INFO_DBG, "%s: Could not allocate skb\n",
				  ring->dev->name);
			अगर (first_rxdp) अणु
				dma_wmb();
				first_rxdp->Control_1 |= RXD_OWN_XENA;
			पूर्ण
			swstats->mem_alloc_fail_cnt++;

			वापस -ENOMEM ;
		पूर्ण
		swstats->mem_allocated += skb->truesize;

		अगर (ring->rxd_mode == RXD_MODE_1) अणु
			/* 1 buffer mode - normal operation mode */
			rxdp1 = (काष्ठा RxD1 *)rxdp;
			स_रखो(rxdp, 0, माप(काष्ठा RxD1));
			skb_reserve(skb, NET_IP_ALIGN);
			rxdp1->Buffer0_ptr =
				dma_map_single(&ring->pdev->dev, skb->data,
					       size - NET_IP_ALIGN,
					       DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&nic->pdev->dev, rxdp1->Buffer0_ptr))
				जाओ pci_map_failed;

			rxdp->Control_2 =
				SET_BUFFER0_SIZE_1(size - NET_IP_ALIGN);
			rxdp->Host_Control = (अचिन्हित दीर्घ)skb;
		पूर्ण अन्यथा अगर (ring->rxd_mode == RXD_MODE_3B) अणु
			/*
			 * 2 buffer mode -
			 * 2 buffer mode provides 128
			 * byte aligned receive buffers.
			 */

			rxdp3 = (काष्ठा RxD3 *)rxdp;
			/* save buffer poपूर्णांकers to aव्योम frequent dma mapping */
			Buffer0_ptr = rxdp3->Buffer0_ptr;
			Buffer1_ptr = rxdp3->Buffer1_ptr;
			स_रखो(rxdp, 0, माप(काष्ठा RxD3));
			/* restore the buffer poपूर्णांकers क्रम dma sync*/
			rxdp3->Buffer0_ptr = Buffer0_ptr;
			rxdp3->Buffer1_ptr = Buffer1_ptr;

			ba = &ring->ba[block_no][off];
			skb_reserve(skb, BUF0_LEN);
			पंचांगp = (u64)(अचिन्हित दीर्घ)skb->data;
			पंचांगp += ALIGN_SIZE;
			पंचांगp &= ~ALIGN_SIZE;
			skb->data = (व्योम *) (अचिन्हित दीर्घ)पंचांगp;
			skb_reset_tail_poपूर्णांकer(skb);

			अगर (from_card_up) अणु
				rxdp3->Buffer0_ptr =
					dma_map_single(&ring->pdev->dev,
						       ba->ba_0, BUF0_LEN,
						       DMA_FROM_DEVICE);
				अगर (dma_mapping_error(&nic->pdev->dev, rxdp3->Buffer0_ptr))
					जाओ pci_map_failed;
			पूर्ण अन्यथा
				dma_sync_single_क्रम_device(&ring->pdev->dev,
							   (dma_addr_t)rxdp3->Buffer0_ptr,
							   BUF0_LEN,
							   DMA_FROM_DEVICE);

			rxdp->Control_2 = SET_BUFFER0_SIZE_3(BUF0_LEN);
			अगर (ring->rxd_mode == RXD_MODE_3B) अणु
				/* Two buffer mode */

				/*
				 * Buffer2 will have L3/L4 header plus
				 * L4 payload
				 */
				rxdp3->Buffer2_ptr = dma_map_single(&ring->pdev->dev,
								    skb->data,
								    ring->mtu + 4,
								    DMA_FROM_DEVICE);

				अगर (dma_mapping_error(&nic->pdev->dev, rxdp3->Buffer2_ptr))
					जाओ pci_map_failed;

				अगर (from_card_up) अणु
					rxdp3->Buffer1_ptr =
						dma_map_single(&ring->pdev->dev,
							       ba->ba_1,
							       BUF1_LEN,
							       DMA_FROM_DEVICE);

					अगर (dma_mapping_error(&nic->pdev->dev,
							      rxdp3->Buffer1_ptr)) अणु
						dma_unmap_single(&ring->pdev->dev,
								 (dma_addr_t)(अचिन्हित दीर्घ)
								 skb->data,
								 ring->mtu + 4,
								 DMA_FROM_DEVICE);
						जाओ pci_map_failed;
					पूर्ण
				पूर्ण
				rxdp->Control_2 |= SET_BUFFER1_SIZE_3(1);
				rxdp->Control_2 |= SET_BUFFER2_SIZE_3
					(ring->mtu + 4);
			पूर्ण
			rxdp->Control_2 |= s2BIT(0);
			rxdp->Host_Control = (अचिन्हित दीर्घ) (skb);
		पूर्ण
		अगर (alloc_tab & ((1 << rxsync_frequency) - 1))
			rxdp->Control_1 |= RXD_OWN_XENA;
		off++;
		अगर (off == (ring->rxd_count + 1))
			off = 0;
		ring->rx_curr_put_info.offset = off;

		rxdp->Control_2 |= SET_RXD_MARKER;
		अगर (!(alloc_tab & ((1 << rxsync_frequency) - 1))) अणु
			अगर (first_rxdp) अणु
				dma_wmb();
				first_rxdp->Control_1 |= RXD_OWN_XENA;
			पूर्ण
			first_rxdp = rxdp;
		पूर्ण
		ring->rx_bufs_left += 1;
		alloc_tab++;
	पूर्ण

end:
	/* Transfer ownership of first descriptor to adapter just beक्रमe
	 * निकासing. Beक्रमe that, use memory barrier so that ownership
	 * and other fields are seen by adapter correctly.
	 */
	अगर (first_rxdp) अणु
		dma_wmb();
		first_rxdp->Control_1 |= RXD_OWN_XENA;
	पूर्ण

	वापस SUCCESS;

pci_map_failed:
	swstats->pci_map_fail_cnt++;
	swstats->mem_मुक्तd += skb->truesize;
	dev_kमुक्त_skb_irq(skb);
	वापस -ENOMEM;
पूर्ण

अटल व्योम मुक्त_rxd_blk(काष्ठा s2io_nic *sp, पूर्णांक ring_no, पूर्णांक blk)
अणु
	काष्ठा net_device *dev = sp->dev;
	पूर्णांक j;
	काष्ठा sk_buff *skb;
	काष्ठा RxD_t *rxdp;
	काष्ठा RxD1 *rxdp1;
	काष्ठा RxD3 *rxdp3;
	काष्ठा mac_info *mac_control = &sp->mac_control;
	काष्ठा stat_block *stats = mac_control->stats_info;
	काष्ठा swStat *swstats = &stats->sw_stat;

	क्रम (j = 0 ; j < rxd_count[sp->rxd_mode]; j++) अणु
		rxdp = mac_control->rings[ring_no].
			rx_blocks[blk].rxds[j].virt_addr;
		skb = (काष्ठा sk_buff *)((अचिन्हित दीर्घ)rxdp->Host_Control);
		अगर (!skb)
			जारी;
		अगर (sp->rxd_mode == RXD_MODE_1) अणु
			rxdp1 = (काष्ठा RxD1 *)rxdp;
			dma_unmap_single(&sp->pdev->dev,
					 (dma_addr_t)rxdp1->Buffer0_ptr,
					 dev->mtu +
					 HEADER_ETHERNET_II_802_3_SIZE +
					 HEADER_802_2_SIZE + HEADER_SNAP_SIZE,
					 DMA_FROM_DEVICE);
			स_रखो(rxdp, 0, माप(काष्ठा RxD1));
		पूर्ण अन्यथा अगर (sp->rxd_mode == RXD_MODE_3B) अणु
			rxdp3 = (काष्ठा RxD3 *)rxdp;
			dma_unmap_single(&sp->pdev->dev,
					 (dma_addr_t)rxdp3->Buffer0_ptr,
					 BUF0_LEN, DMA_FROM_DEVICE);
			dma_unmap_single(&sp->pdev->dev,
					 (dma_addr_t)rxdp3->Buffer1_ptr,
					 BUF1_LEN, DMA_FROM_DEVICE);
			dma_unmap_single(&sp->pdev->dev,
					 (dma_addr_t)rxdp3->Buffer2_ptr,
					 dev->mtu + 4, DMA_FROM_DEVICE);
			स_रखो(rxdp, 0, माप(काष्ठा RxD3));
		पूर्ण
		swstats->mem_मुक्तd += skb->truesize;
		dev_kमुक्त_skb(skb);
		mac_control->rings[ring_no].rx_bufs_left -= 1;
	पूर्ण
पूर्ण

/**
 *  मुक्त_rx_buffers - Frees all Rx buffers
 *  @sp: device निजी variable.
 *  Description:
 *  This function will मुक्त all Rx buffers allocated by host.
 *  Return Value:
 *  NONE.
 */

अटल व्योम मुक्त_rx_buffers(काष्ठा s2io_nic *sp)
अणु
	काष्ठा net_device *dev = sp->dev;
	पूर्णांक i, blk = 0, buf_cnt = 0;
	काष्ठा config_param *config = &sp->config;
	काष्ठा mac_info *mac_control = &sp->mac_control;

	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा ring_info *ring = &mac_control->rings[i];

		क्रम (blk = 0; blk < rx_ring_sz[i]; blk++)
			मुक्त_rxd_blk(sp, i, blk);

		ring->rx_curr_put_info.block_index = 0;
		ring->rx_curr_get_info.block_index = 0;
		ring->rx_curr_put_info.offset = 0;
		ring->rx_curr_get_info.offset = 0;
		ring->rx_bufs_left = 0;
		DBG_PRINT(INIT_DBG, "%s: Freed 0x%x Rx Buffers on ring%d\n",
			  dev->name, buf_cnt, i);
	पूर्ण
पूर्ण

अटल पूर्णांक s2io_chk_rx_buffers(काष्ठा s2io_nic *nic, काष्ठा ring_info *ring)
अणु
	अगर (fill_rx_buffers(nic, ring, 0) == -ENOMEM) अणु
		DBG_PRINT(INFO_DBG, "%s: Out of memory in Rx Intr!!\n",
			  ring->dev->name);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * s2io_poll - Rx पूर्णांकerrupt handler क्रम NAPI support
 * @napi : poपूर्णांकer to the napi काष्ठाure.
 * @budget : The number of packets that were budgeted to be processed
 * during  one pass through the 'Poll" function.
 * Description:
 * Comes पूर्णांकo picture only अगर NAPI support has been incorporated. It करोes
 * the same thing that rx_पूर्णांकr_handler करोes, but not in a पूर्णांकerrupt context
 * also It will process only a given number of packets.
 * Return value:
 * 0 on success and 1 अगर there are No Rx packets to be processed.
 */

अटल पूर्णांक s2io_poll_msix(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ring_info *ring = container_of(napi, काष्ठा ring_info, napi);
	काष्ठा net_device *dev = ring->dev;
	पूर्णांक pkts_processed = 0;
	u8 __iomem *addr = शून्य;
	u8 val8 = 0;
	काष्ठा s2io_nic *nic = netdev_priv(dev);
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	पूर्णांक budget_org = budget;

	अगर (unlikely(!is_s2io_card_up(nic)))
		वापस 0;

	pkts_processed = rx_पूर्णांकr_handler(ring, budget);
	s2io_chk_rx_buffers(nic, ring);

	अगर (pkts_processed < budget_org) अणु
		napi_complete_करोne(napi, pkts_processed);
		/*Re Enable MSI-Rx Vector*/
		addr = (u8 __iomem *)&bar0->xmsi_mask_reg;
		addr += 7 - ring->ring_no;
		val8 = (ring->ring_no == 0) ? 0x3f : 0xbf;
		ग_लिखोb(val8, addr);
		val8 = पढ़ोb(addr);
	पूर्ण
	वापस pkts_processed;
पूर्ण

अटल पूर्णांक s2io_poll_पूर्णांकa(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा s2io_nic *nic = container_of(napi, काष्ठा s2io_nic, napi);
	पूर्णांक pkts_processed = 0;
	पूर्णांक ring_pkts_processed, i;
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	पूर्णांक budget_org = budget;
	काष्ठा config_param *config = &nic->config;
	काष्ठा mac_info *mac_control = &nic->mac_control;

	अगर (unlikely(!is_s2io_card_up(nic)))
		वापस 0;

	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा ring_info *ring = &mac_control->rings[i];
		ring_pkts_processed = rx_पूर्णांकr_handler(ring, budget);
		s2io_chk_rx_buffers(nic, ring);
		pkts_processed += ring_pkts_processed;
		budget -= ring_pkts_processed;
		अगर (budget <= 0)
			अवरोध;
	पूर्ण
	अगर (pkts_processed < budget_org) अणु
		napi_complete_करोne(napi, pkts_processed);
		/* Re enable the Rx पूर्णांकerrupts क्रम the ring */
		ग_लिखोq(0, &bar0->rx_traffic_mask);
		पढ़ोl(&bar0->rx_traffic_mask);
	पूर्ण
	वापस pkts_processed;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * s2io_netpoll - netpoll event handler entry poपूर्णांक
 * @dev : poपूर्णांकer to the device काष्ठाure.
 * Description:
 * 	This function will be called by upper layer to check क्रम events on the
 * पूर्णांकerface in situations where पूर्णांकerrupts are disabled. It is used क्रम
 * specअगरic in-kernel networking tasks, such as remote consoles and kernel
 * debugging over the network (example netdump in RedHat).
 */
अटल व्योम s2io_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा s2io_nic *nic = netdev_priv(dev);
	स्थिर पूर्णांक irq = nic->pdev->irq;
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	u64 val64 = 0xFFFFFFFFFFFFFFFFULL;
	पूर्णांक i;
	काष्ठा config_param *config = &nic->config;
	काष्ठा mac_info *mac_control = &nic->mac_control;

	अगर (pci_channel_offline(nic->pdev))
		वापस;

	disable_irq(irq);

	ग_लिखोq(val64, &bar0->rx_traffic_पूर्णांक);
	ग_लिखोq(val64, &bar0->tx_traffic_पूर्णांक);

	/* we need to मुक्त up the transmitted skbufs or अन्यथा netpoll will
	 * run out of skbs and will fail and eventually netpoll application such
	 * as netdump will fail.
	 */
	क्रम (i = 0; i < config->tx_fअगरo_num; i++)
		tx_पूर्णांकr_handler(&mac_control->fअगरos[i]);

	/* check क्रम received packet and indicate up to network */
	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा ring_info *ring = &mac_control->rings[i];

		rx_पूर्णांकr_handler(ring, 0);
	पूर्ण

	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा ring_info *ring = &mac_control->rings[i];

		अगर (fill_rx_buffers(nic, ring, 0) == -ENOMEM) अणु
			DBG_PRINT(INFO_DBG,
				  "%s: Out of memory in Rx Netpoll!!\n",
				  dev->name);
			अवरोध;
		पूर्ण
	पूर्ण
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

/**
 *  rx_पूर्णांकr_handler - Rx पूर्णांकerrupt handler
 *  @ring_data: per ring काष्ठाure.
 *  @budget: budget क्रम napi processing.
 *  Description:
 *  If the पूर्णांकerrupt is because of a received frame or अगर the
 *  receive ring contains fresh as yet un-processed frames,this function is
 *  called. It picks out the RxD at which place the last Rx processing had
 *  stopped and sends the skb to the OSM's Rx handler and then increments
 *  the offset.
 *  Return Value:
 *  No. of napi packets processed.
 */
अटल पूर्णांक rx_पूर्णांकr_handler(काष्ठा ring_info *ring_data, पूर्णांक budget)
अणु
	पूर्णांक get_block, put_block;
	काष्ठा rx_curr_get_info get_info, put_info;
	काष्ठा RxD_t *rxdp;
	काष्ठा sk_buff *skb;
	पूर्णांक pkt_cnt = 0, napi_pkts = 0;
	पूर्णांक i;
	काष्ठा RxD1 *rxdp1;
	काष्ठा RxD3 *rxdp3;

	अगर (budget <= 0)
		वापस napi_pkts;

	get_info = ring_data->rx_curr_get_info;
	get_block = get_info.block_index;
	स_नकल(&put_info, &ring_data->rx_curr_put_info, माप(put_info));
	put_block = put_info.block_index;
	rxdp = ring_data->rx_blocks[get_block].rxds[get_info.offset].virt_addr;

	जबतक (RXD_IS_UP2DT(rxdp)) अणु
		/*
		 * If your are next to put index then it's
		 * FIFO full condition
		 */
		अगर ((get_block == put_block) &&
		    (get_info.offset + 1) == put_info.offset) अणु
			DBG_PRINT(INTR_DBG, "%s: Ring Full\n",
				  ring_data->dev->name);
			अवरोध;
		पूर्ण
		skb = (काष्ठा sk_buff *)((अचिन्हित दीर्घ)rxdp->Host_Control);
		अगर (skb == शून्य) अणु
			DBG_PRINT(ERR_DBG, "%s: NULL skb in Rx Intr\n",
				  ring_data->dev->name);
			वापस 0;
		पूर्ण
		अगर (ring_data->rxd_mode == RXD_MODE_1) अणु
			rxdp1 = (काष्ठा RxD1 *)rxdp;
			dma_unmap_single(&ring_data->pdev->dev,
					 (dma_addr_t)rxdp1->Buffer0_ptr,
					 ring_data->mtu +
					 HEADER_ETHERNET_II_802_3_SIZE +
					 HEADER_802_2_SIZE +
					 HEADER_SNAP_SIZE,
					 DMA_FROM_DEVICE);
		पूर्ण अन्यथा अगर (ring_data->rxd_mode == RXD_MODE_3B) अणु
			rxdp3 = (काष्ठा RxD3 *)rxdp;
			dma_sync_single_क्रम_cpu(&ring_data->pdev->dev,
						(dma_addr_t)rxdp3->Buffer0_ptr,
						BUF0_LEN, DMA_FROM_DEVICE);
			dma_unmap_single(&ring_data->pdev->dev,
					 (dma_addr_t)rxdp3->Buffer2_ptr,
					 ring_data->mtu + 4, DMA_FROM_DEVICE);
		पूर्ण
		prefetch(skb->data);
		rx_osm_handler(ring_data, rxdp);
		get_info.offset++;
		ring_data->rx_curr_get_info.offset = get_info.offset;
		rxdp = ring_data->rx_blocks[get_block].
			rxds[get_info.offset].virt_addr;
		अगर (get_info.offset == rxd_count[ring_data->rxd_mode]) अणु
			get_info.offset = 0;
			ring_data->rx_curr_get_info.offset = get_info.offset;
			get_block++;
			अगर (get_block == ring_data->block_count)
				get_block = 0;
			ring_data->rx_curr_get_info.block_index = get_block;
			rxdp = ring_data->rx_blocks[get_block].block_virt_addr;
		पूर्ण

		अगर (ring_data->nic->config.napi) अणु
			budget--;
			napi_pkts++;
			अगर (!budget)
				अवरोध;
		पूर्ण
		pkt_cnt++;
		अगर ((indicate_max_pkts) && (pkt_cnt > indicate_max_pkts))
			अवरोध;
	पूर्ण
	अगर (ring_data->lro) अणु
		/* Clear all LRO sessions beक्रमe निकासing */
		क्रम (i = 0; i < MAX_LRO_SESSIONS; i++) अणु
			काष्ठा lro *lro = &ring_data->lro0_n[i];
			अगर (lro->in_use) अणु
				update_L3L4_header(ring_data->nic, lro);
				queue_rx_frame(lro->parent, lro->vlan_tag);
				clear_lro_session(lro);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस napi_pkts;
पूर्ण

/**
 *  tx_पूर्णांकr_handler - Transmit पूर्णांकerrupt handler
 *  @fअगरo_data : fअगरo data poपूर्णांकer
 *  Description:
 *  If an पूर्णांकerrupt was उठाओd to indicate DMA complete of the
 *  Tx packet, this function is called. It identअगरies the last TxD
 *  whose buffer was मुक्तd and मुक्तs all skbs whose data have alपढ़ोy
 *  DMA'ed पूर्णांकo the NICs पूर्णांकernal memory.
 *  Return Value:
 *  NONE
 */

अटल व्योम tx_पूर्णांकr_handler(काष्ठा fअगरo_info *fअगरo_data)
अणु
	काष्ठा s2io_nic *nic = fअगरo_data->nic;
	काष्ठा tx_curr_get_info get_info, put_info;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा TxD *txdlp;
	पूर्णांक pkt_cnt = 0;
	अचिन्हित दीर्घ flags = 0;
	u8 err_mask;
	काष्ठा stat_block *stats = nic->mac_control.stats_info;
	काष्ठा swStat *swstats = &stats->sw_stat;

	अगर (!spin_trylock_irqsave(&fअगरo_data->tx_lock, flags))
		वापस;

	get_info = fअगरo_data->tx_curr_get_info;
	स_नकल(&put_info, &fअगरo_data->tx_curr_put_info, माप(put_info));
	txdlp = fअगरo_data->list_info[get_info.offset].list_virt_addr;
	जबतक ((!(txdlp->Control_1 & TXD_LIST_OWN_XENA)) &&
	       (get_info.offset != put_info.offset) &&
	       (txdlp->Host_Control)) अणु
		/* Check क्रम TxD errors */
		अगर (txdlp->Control_1 & TXD_T_CODE) अणु
			अचिन्हित दीर्घ दीर्घ err;
			err = txdlp->Control_1 & TXD_T_CODE;
			अगर (err & 0x1) अणु
				swstats->parity_err_cnt++;
			पूर्ण

			/* update t_code statistics */
			err_mask = err >> 48;
			चयन (err_mask) अणु
			हाल 2:
				swstats->tx_buf_पात_cnt++;
				अवरोध;

			हाल 3:
				swstats->tx_desc_पात_cnt++;
				अवरोध;

			हाल 7:
				swstats->tx_parity_err_cnt++;
				अवरोध;

			हाल 10:
				swstats->tx_link_loss_cnt++;
				अवरोध;

			हाल 15:
				swstats->tx_list_proc_err_cnt++;
				अवरोध;
			पूर्ण
		पूर्ण

		skb = s2io_txdl_माला_लोkb(fअगरo_data, txdlp, get_info.offset);
		अगर (skb == शून्य) अणु
			spin_unlock_irqrestore(&fअगरo_data->tx_lock, flags);
			DBG_PRINT(ERR_DBG, "%s: NULL skb in Tx Free Intr\n",
				  __func__);
			वापस;
		पूर्ण
		pkt_cnt++;

		/* Updating the statistics block */
		swstats->mem_मुक्तd += skb->truesize;
		dev_consume_skb_irq(skb);

		get_info.offset++;
		अगर (get_info.offset == get_info.fअगरo_len + 1)
			get_info.offset = 0;
		txdlp = fअगरo_data->list_info[get_info.offset].list_virt_addr;
		fअगरo_data->tx_curr_get_info.offset = get_info.offset;
	पूर्ण

	s2io_wake_tx_queue(fअगरo_data, pkt_cnt, nic->config.multiq);

	spin_unlock_irqrestore(&fअगरo_data->tx_lock, flags);
पूर्ण

/**
 *  s2io_mdio_ग_लिखो - Function to ग_लिखो in to MDIO रेजिस्टरs
 *  @mmd_type : MMD type value (PMA/PMD/WIS/PCS/PHYXS)
 *  @addr     : address value
 *  @value    : data value
 *  @dev      : poपूर्णांकer to net_device काष्ठाure
 *  Description:
 *  This function is used to ग_लिखो values to the MDIO रेजिस्टरs
 *  NONE
 */
अटल व्योम s2io_mdio_ग_लिखो(u32 mmd_type, u64 addr, u16 value,
			    काष्ठा net_device *dev)
अणु
	u64 val64;
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;

	/* address transaction */
	val64 = MDIO_MMD_INDX_ADDR(addr) |
		MDIO_MMD_DEV_ADDR(mmd_type) |
		MDIO_MMS_PRT_ADDR(0x0);
	ग_लिखोq(val64, &bar0->mdio_control);
	val64 = val64 | MDIO_CTRL_START_TRANS(0xE);
	ग_लिखोq(val64, &bar0->mdio_control);
	udelay(100);

	/* Data transaction */
	val64 = MDIO_MMD_INDX_ADDR(addr) |
		MDIO_MMD_DEV_ADDR(mmd_type) |
		MDIO_MMS_PRT_ADDR(0x0) |
		MDIO_MDIO_DATA(value) |
		MDIO_OP(MDIO_OP_WRITE_TRANS);
	ग_लिखोq(val64, &bar0->mdio_control);
	val64 = val64 | MDIO_CTRL_START_TRANS(0xE);
	ग_लिखोq(val64, &bar0->mdio_control);
	udelay(100);

	val64 = MDIO_MMD_INDX_ADDR(addr) |
		MDIO_MMD_DEV_ADDR(mmd_type) |
		MDIO_MMS_PRT_ADDR(0x0) |
		MDIO_OP(MDIO_OP_READ_TRANS);
	ग_लिखोq(val64, &bar0->mdio_control);
	val64 = val64 | MDIO_CTRL_START_TRANS(0xE);
	ग_लिखोq(val64, &bar0->mdio_control);
	udelay(100);
पूर्ण

/**
 *  s2io_mdio_पढ़ो - Function to ग_लिखो in to MDIO रेजिस्टरs
 *  @mmd_type : MMD type value (PMA/PMD/WIS/PCS/PHYXS)
 *  @addr     : address value
 *  @dev      : poपूर्णांकer to net_device काष्ठाure
 *  Description:
 *  This function is used to पढ़ो values to the MDIO रेजिस्टरs
 *  NONE
 */
अटल u64 s2io_mdio_पढ़ो(u32 mmd_type, u64 addr, काष्ठा net_device *dev)
अणु
	u64 val64 = 0x0;
	u64 rval64 = 0x0;
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;

	/* address transaction */
	val64 = val64 | (MDIO_MMD_INDX_ADDR(addr)
			 | MDIO_MMD_DEV_ADDR(mmd_type)
			 | MDIO_MMS_PRT_ADDR(0x0));
	ग_लिखोq(val64, &bar0->mdio_control);
	val64 = val64 | MDIO_CTRL_START_TRANS(0xE);
	ग_लिखोq(val64, &bar0->mdio_control);
	udelay(100);

	/* Data transaction */
	val64 = MDIO_MMD_INDX_ADDR(addr) |
		MDIO_MMD_DEV_ADDR(mmd_type) |
		MDIO_MMS_PRT_ADDR(0x0) |
		MDIO_OP(MDIO_OP_READ_TRANS);
	ग_लिखोq(val64, &bar0->mdio_control);
	val64 = val64 | MDIO_CTRL_START_TRANS(0xE);
	ग_लिखोq(val64, &bar0->mdio_control);
	udelay(100);

	/* Read the value from regs */
	rval64 = पढ़ोq(&bar0->mdio_control);
	rval64 = rval64 & 0xFFFF0000;
	rval64 = rval64 >> 16;
	वापस rval64;
पूर्ण

/**
 *  s2io_chk_xpak_counter - Function to check the status of the xpak counters
 *  @counter      : counter value to be updated
 *  @regs_stat    : रेजिस्टरs status
 *  @index        : index
 *  @flag         : flag to indicate the status
 *  @type         : counter type
 *  Description:
 *  This function is to check the status of the xpak counters value
 *  NONE
 */

अटल व्योम s2io_chk_xpak_counter(u64 *counter, u64 * regs_stat, u32 index,
				  u16 flag, u16 type)
अणु
	u64 mask = 0x3;
	u64 val64;
	पूर्णांक i;
	क्रम (i = 0; i < index; i++)
		mask = mask << 0x2;

	अगर (flag > 0) अणु
		*counter = *counter + 1;
		val64 = *regs_stat & mask;
		val64 = val64 >> (index * 0x2);
		val64 = val64 + 1;
		अगर (val64 == 3) अणु
			चयन (type) अणु
			हाल 1:
				DBG_PRINT(ERR_DBG,
					  "Take Xframe NIC out of service.\n");
				DBG_PRINT(ERR_DBG,
"Excessive temperatures may result in premature transceiver failure.\n");
				अवरोध;
			हाल 2:
				DBG_PRINT(ERR_DBG,
					  "Take Xframe NIC out of service.\n");
				DBG_PRINT(ERR_DBG,
"Excessive bias currents may indicate imminent laser diode failure.\n");
				अवरोध;
			हाल 3:
				DBG_PRINT(ERR_DBG,
					  "Take Xframe NIC out of service.\n");
				DBG_PRINT(ERR_DBG,
"Excessive laser output power may saturate far-end receiver.\n");
				अवरोध;
			शेष:
				DBG_PRINT(ERR_DBG,
					  "Incorrect XPAK Alarm type\n");
			पूर्ण
			val64 = 0x0;
		पूर्ण
		val64 = val64 << (index * 0x2);
		*regs_stat = (*regs_stat & (~mask)) | (val64);

	पूर्ण अन्यथा अणु
		*regs_stat = *regs_stat & (~mask);
	पूर्ण
पूर्ण

/**
 *  s2io_updt_xpak_counter - Function to update the xpak counters
 *  @dev         : poपूर्णांकer to net_device काष्ठा
 *  Description:
 *  This function is to upate the status of the xpak counters value
 *  NONE
 */
अटल व्योम s2io_updt_xpak_counter(काष्ठा net_device *dev)
अणु
	u16 flag  = 0x0;
	u16 type  = 0x0;
	u16 val16 = 0x0;
	u64 val64 = 0x0;
	u64 addr  = 0x0;

	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा stat_block *stats = sp->mac_control.stats_info;
	काष्ठा xpakStat *xstats = &stats->xpak_stat;

	/* Check the communication with the MDIO slave */
	addr = MDIO_CTRL1;
	val64 = 0x0;
	val64 = s2io_mdio_पढ़ो(MDIO_MMD_PMAPMD, addr, dev);
	अगर ((val64 == 0xFFFF) || (val64 == 0x0000)) अणु
		DBG_PRINT(ERR_DBG,
			  "ERR: MDIO slave access failed - Returned %llx\n",
			  (अचिन्हित दीर्घ दीर्घ)val64);
		वापस;
	पूर्ण

	/* Check क्रम the expected value of control reg 1 */
	अगर (val64 != MDIO_CTRL1_SPEED10G) अणु
		DBG_PRINT(ERR_DBG, "Incorrect value at PMA address 0x0000 - "
			  "Returned: %llx- Expected: 0x%x\n",
			  (अचिन्हित दीर्घ दीर्घ)val64, MDIO_CTRL1_SPEED10G);
		वापस;
	पूर्ण

	/* Loading the DOM रेजिस्टर to MDIO रेजिस्टर */
	addr = 0xA100;
	s2io_mdio_ग_लिखो(MDIO_MMD_PMAPMD, addr, val16, dev);
	val64 = s2io_mdio_पढ़ो(MDIO_MMD_PMAPMD, addr, dev);

	/* Reading the Alarm flags */
	addr = 0xA070;
	val64 = 0x0;
	val64 = s2io_mdio_पढ़ो(MDIO_MMD_PMAPMD, addr, dev);

	flag = CHECKBIT(val64, 0x7);
	type = 1;
	s2io_chk_xpak_counter(&xstats->alarm_transceiver_temp_high,
			      &xstats->xpak_regs_stat,
			      0x0, flag, type);

	अगर (CHECKBIT(val64, 0x6))
		xstats->alarm_transceiver_temp_low++;

	flag = CHECKBIT(val64, 0x3);
	type = 2;
	s2io_chk_xpak_counter(&xstats->alarm_laser_bias_current_high,
			      &xstats->xpak_regs_stat,
			      0x2, flag, type);

	अगर (CHECKBIT(val64, 0x2))
		xstats->alarm_laser_bias_current_low++;

	flag = CHECKBIT(val64, 0x1);
	type = 3;
	s2io_chk_xpak_counter(&xstats->alarm_laser_output_घातer_high,
			      &xstats->xpak_regs_stat,
			      0x4, flag, type);

	अगर (CHECKBIT(val64, 0x0))
		xstats->alarm_laser_output_घातer_low++;

	/* Reading the Warning flags */
	addr = 0xA074;
	val64 = 0x0;
	val64 = s2io_mdio_पढ़ो(MDIO_MMD_PMAPMD, addr, dev);

	अगर (CHECKBIT(val64, 0x7))
		xstats->warn_transceiver_temp_high++;

	अगर (CHECKBIT(val64, 0x6))
		xstats->warn_transceiver_temp_low++;

	अगर (CHECKBIT(val64, 0x3))
		xstats->warn_laser_bias_current_high++;

	अगर (CHECKBIT(val64, 0x2))
		xstats->warn_laser_bias_current_low++;

	अगर (CHECKBIT(val64, 0x1))
		xstats->warn_laser_output_घातer_high++;

	अगर (CHECKBIT(val64, 0x0))
		xstats->warn_laser_output_घातer_low++;
पूर्ण

/**
 *  रुको_क्रम_cmd_complete - रुकोs क्रम a command to complete.
 *  @addr: address
 *  @busy_bit: bit to check क्रम busy
 *  @bit_state: state to check
 *  Description: Function that रुकोs क्रम a command to Write पूर्णांकo RMAC
 *  ADDR DATA रेजिस्टरs to be completed and वापसs either success or
 *  error depending on whether the command was complete or not.
 *  Return value:
 *   SUCCESS on success and FAILURE on failure.
 */

अटल पूर्णांक रुको_क्रम_cmd_complete(व्योम __iomem *addr, u64 busy_bit,
				 पूर्णांक bit_state, bool may_sleep)
अणु
	पूर्णांक ret = FAILURE, cnt = 0, delay = 1;
	u64 val64;

	अगर ((bit_state != S2IO_BIT_RESET) && (bit_state != S2IO_BIT_SET))
		वापस FAILURE;

	करो अणु
		val64 = पढ़ोq(addr);
		अगर (bit_state == S2IO_BIT_RESET) अणु
			अगर (!(val64 & busy_bit)) अणु
				ret = SUCCESS;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (val64 & busy_bit) अणु
				ret = SUCCESS;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!may_sleep)
			mdelay(delay);
		अन्यथा
			msleep(delay);

		अगर (++cnt >= 10)
			delay = 50;
	पूर्ण जबतक (cnt < 20);
	वापस ret;
पूर्ण
/**
 * check_pci_device_id - Checks अगर the device id is supported
 * @id : device id
 * Description: Function to check अगर the pci device id is supported by driver.
 * Return value: Actual device id अगर supported अन्यथा PCI_ANY_ID
 */
अटल u16 check_pci_device_id(u16 id)
अणु
	चयन (id) अणु
	हाल PCI_DEVICE_ID_HERC_WIN:
	हाल PCI_DEVICE_ID_HERC_UNI:
		वापस XFRAME_II_DEVICE;
	हाल PCI_DEVICE_ID_S2IO_UNI:
	हाल PCI_DEVICE_ID_S2IO_WIN:
		वापस XFRAME_I_DEVICE;
	शेष:
		वापस PCI_ANY_ID;
	पूर्ण
पूर्ण

/**
 *  s2io_reset - Resets the card.
 *  @sp : निजी member of the device काष्ठाure.
 *  Description: Function to Reset the card. This function then also
 *  restores the previously saved PCI configuration space रेजिस्टरs as
 *  the card reset also resets the configuration space.
 *  Return value:
 *  व्योम.
 */

अटल व्योम s2io_reset(काष्ठा s2io_nic *sp)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64;
	u16 subid, pci_cmd;
	पूर्णांक i;
	u16 val16;
	अचिन्हित दीर्घ दीर्घ up_cnt, करोwn_cnt, up_समय, करोwn_समय, reset_cnt;
	अचिन्हित दीर्घ दीर्घ mem_alloc_cnt, mem_मुक्त_cnt, watchकरोg_cnt;
	काष्ठा stat_block *stats;
	काष्ठा swStat *swstats;

	DBG_PRINT(INIT_DBG, "%s: Resetting XFrame card %s\n",
		  __func__, pci_name(sp->pdev));

	/* Back up  the PCI-X CMD reg, करोnt want to lose MMRBC, OST settings */
	pci_पढ़ो_config_word(sp->pdev, PCIX_COMMAND_REGISTER, &(pci_cmd));

	val64 = SW_RESET_ALL;
	ग_लिखोq(val64, &bar0->sw_reset);
	अगर (म_माला(sp->product_name, "CX4"))
		msleep(750);
	msleep(250);
	क्रम (i = 0; i < S2IO_MAX_PCI_CONFIG_SPACE_REINIT; i++) अणु

		/* Restore the PCI state saved during initialization. */
		pci_restore_state(sp->pdev);
		pci_save_state(sp->pdev);
		pci_पढ़ो_config_word(sp->pdev, 0x2, &val16);
		अगर (check_pci_device_id(val16) != (u16)PCI_ANY_ID)
			अवरोध;
		msleep(200);
	पूर्ण

	अगर (check_pci_device_id(val16) == (u16)PCI_ANY_ID)
		DBG_PRINT(ERR_DBG, "%s SW_Reset failed!\n", __func__);

	pci_ग_लिखो_config_word(sp->pdev, PCIX_COMMAND_REGISTER, pci_cmd);

	s2io_init_pci(sp);

	/* Set swapper to enable I/O रेजिस्टर access */
	s2io_set_swapper(sp);

	/* restore mac_addr entries */
	करो_s2io_restore_unicast_mc(sp);

	/* Restore the MSIX table entries from local variables */
	restore_xmsi_data(sp);

	/* Clear certain PCI/PCI-X fields after reset */
	अगर (sp->device_type == XFRAME_II_DEVICE) अणु
		/* Clear "detected parity error" bit */
		pci_ग_लिखो_config_word(sp->pdev, PCI_STATUS, 0x8000);

		/* Clearing PCIX Ecc status रेजिस्टर */
		pci_ग_लिखो_config_dword(sp->pdev, 0x68, 0x7C);

		/* Clearing PCI_STATUS error reflected here */
		ग_लिखोq(s2BIT(62), &bar0->txpic_पूर्णांक_reg);
	पूर्ण

	/* Reset device statistics मुख्यtained by OS */
	स_रखो(&sp->stats, 0, माप(काष्ठा net_device_stats));

	stats = sp->mac_control.stats_info;
	swstats = &stats->sw_stat;

	/* save link up/करोwn समय/cnt, reset/memory/watchकरोg cnt */
	up_cnt = swstats->link_up_cnt;
	करोwn_cnt = swstats->link_करोwn_cnt;
	up_समय = swstats->link_up_समय;
	करोwn_समय = swstats->link_करोwn_समय;
	reset_cnt = swstats->soft_reset_cnt;
	mem_alloc_cnt = swstats->mem_allocated;
	mem_मुक्त_cnt = swstats->mem_मुक्तd;
	watchकरोg_cnt = swstats->watchकरोg_समयr_cnt;

	स_रखो(stats, 0, माप(काष्ठा stat_block));

	/* restore link up/करोwn समय/cnt, reset/memory/watchकरोg cnt */
	swstats->link_up_cnt = up_cnt;
	swstats->link_करोwn_cnt = करोwn_cnt;
	swstats->link_up_समय = up_समय;
	swstats->link_करोwn_समय = करोwn_समय;
	swstats->soft_reset_cnt = reset_cnt;
	swstats->mem_allocated = mem_alloc_cnt;
	swstats->mem_मुक्तd = mem_मुक्त_cnt;
	swstats->watchकरोg_समयr_cnt = watchकरोg_cnt;

	/* SXE-002: Configure link and activity LED to turn it off */
	subid = sp->pdev->subप्रणाली_device;
	अगर (((subid & 0xFF) >= 0x07) &&
	    (sp->device_type == XFRAME_I_DEVICE)) अणु
		val64 = पढ़ोq(&bar0->gpio_control);
		val64 |= 0x0000800000000000ULL;
		ग_लिखोq(val64, &bar0->gpio_control);
		val64 = 0x0411040400000000ULL;
		ग_लिखोq(val64, (व्योम __iomem *)bar0 + 0x2700);
	पूर्ण

	/*
	 * Clear spurious ECC पूर्णांकerrupts that would have occurred on
	 * XFRAME II cards after reset.
	 */
	अगर (sp->device_type == XFRAME_II_DEVICE) अणु
		val64 = पढ़ोq(&bar0->pcc_err_reg);
		ग_लिखोq(val64, &bar0->pcc_err_reg);
	पूर्ण

	sp->device_enabled_once = false;
पूर्ण

/**
 *  s2io_set_swapper - to set the swapper controle on the card
 *  @sp : निजी member of the device काष्ठाure,
 *  poपूर्णांकer to the s2io_nic काष्ठाure.
 *  Description: Function to set the swapper control on the card
 *  correctly depending on the 'endianness' of the प्रणाली.
 *  Return value:
 *  SUCCESS on success and FAILURE on failure.
 */

अटल पूर्णांक s2io_set_swapper(काष्ठा s2io_nic *sp)
अणु
	काष्ठा net_device *dev = sp->dev;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64, valt, valr;

	/*
	 * Set proper endian settings and verअगरy the same by पढ़ोing
	 * the PIF Feed-back रेजिस्टर.
	 */

	val64 = पढ़ोq(&bar0->pअगर_rd_swapper_fb);
	अगर (val64 != 0x0123456789ABCDEFULL) अणु
		पूर्णांक i = 0;
		अटल स्थिर u64 value[] = अणु
			0xC30000C3C30000C3ULL,	/* FE=1, SE=1 */
			0x8100008181000081ULL,	/* FE=1, SE=0 */
			0x4200004242000042ULL,	/* FE=0, SE=1 */
			0			/* FE=0, SE=0 */
		पूर्ण;

		जबतक (i < 4) अणु
			ग_लिखोq(value[i], &bar0->swapper_ctrl);
			val64 = पढ़ोq(&bar0->pअगर_rd_swapper_fb);
			अगर (val64 == 0x0123456789ABCDEFULL)
				अवरोध;
			i++;
		पूर्ण
		अगर (i == 4) अणु
			DBG_PRINT(ERR_DBG, "%s: Endian settings are wrong, "
				  "feedback read %llx\n",
				  dev->name, (अचिन्हित दीर्घ दीर्घ)val64);
			वापस FAILURE;
		पूर्ण
		valr = value[i];
	पूर्ण अन्यथा अणु
		valr = पढ़ोq(&bar0->swapper_ctrl);
	पूर्ण

	valt = 0x0123456789ABCDEFULL;
	ग_लिखोq(valt, &bar0->xmsi_address);
	val64 = पढ़ोq(&bar0->xmsi_address);

	अगर (val64 != valt) अणु
		पूर्णांक i = 0;
		अटल स्थिर u64 value[] = अणु
			0x00C3C30000C3C300ULL,	/* FE=1, SE=1 */
			0x0081810000818100ULL,	/* FE=1, SE=0 */
			0x0042420000424200ULL,	/* FE=0, SE=1 */
			0			/* FE=0, SE=0 */
		पूर्ण;

		जबतक (i < 4) अणु
			ग_लिखोq((value[i] | valr), &bar0->swapper_ctrl);
			ग_लिखोq(valt, &bar0->xmsi_address);
			val64 = पढ़ोq(&bar0->xmsi_address);
			अगर (val64 == valt)
				अवरोध;
			i++;
		पूर्ण
		अगर (i == 4) अणु
			अचिन्हित दीर्घ दीर्घ x = val64;
			DBG_PRINT(ERR_DBG,
				  "Write failed, Xmsi_addr reads:0x%llx\n", x);
			वापस FAILURE;
		पूर्ण
	पूर्ण
	val64 = पढ़ोq(&bar0->swapper_ctrl);
	val64 &= 0xFFFF000000000000ULL;

#अगर_घोषित __BIG_ENDIAN
	/*
	 * The device by शेष set to a big endian क्रमmat, so a
	 * big endian driver need not set anything.
	 */
	val64 |= (SWAPPER_CTRL_TXP_FE |
		  SWAPPER_CTRL_TXP_SE |
		  SWAPPER_CTRL_TXD_R_FE |
		  SWAPPER_CTRL_TXD_W_FE |
		  SWAPPER_CTRL_TXF_R_FE |
		  SWAPPER_CTRL_RXD_R_FE |
		  SWAPPER_CTRL_RXD_W_FE |
		  SWAPPER_CTRL_RXF_W_FE |
		  SWAPPER_CTRL_XMSI_FE |
		  SWAPPER_CTRL_STATS_FE |
		  SWAPPER_CTRL_STATS_SE);
	अगर (sp->config.पूर्णांकr_type == INTA)
		val64 |= SWAPPER_CTRL_XMSI_SE;
	ग_लिखोq(val64, &bar0->swapper_ctrl);
#अन्यथा
	/*
	 * Initially we enable all bits to make it accessible by the
	 * driver, then we selectively enable only those bits that
	 * we want to set.
	 */
	val64 |= (SWAPPER_CTRL_TXP_FE |
		  SWAPPER_CTRL_TXP_SE |
		  SWAPPER_CTRL_TXD_R_FE |
		  SWAPPER_CTRL_TXD_R_SE |
		  SWAPPER_CTRL_TXD_W_FE |
		  SWAPPER_CTRL_TXD_W_SE |
		  SWAPPER_CTRL_TXF_R_FE |
		  SWAPPER_CTRL_RXD_R_FE |
		  SWAPPER_CTRL_RXD_R_SE |
		  SWAPPER_CTRL_RXD_W_FE |
		  SWAPPER_CTRL_RXD_W_SE |
		  SWAPPER_CTRL_RXF_W_FE |
		  SWAPPER_CTRL_XMSI_FE |
		  SWAPPER_CTRL_STATS_FE |
		  SWAPPER_CTRL_STATS_SE);
	अगर (sp->config.पूर्णांकr_type == INTA)
		val64 |= SWAPPER_CTRL_XMSI_SE;
	ग_लिखोq(val64, &bar0->swapper_ctrl);
#पूर्ण_अगर
	val64 = पढ़ोq(&bar0->swapper_ctrl);

	/*
	 * Verअगरying अगर endian settings are accurate by पढ़ोing a
	 * feedback रेजिस्टर.
	 */
	val64 = पढ़ोq(&bar0->pअगर_rd_swapper_fb);
	अगर (val64 != 0x0123456789ABCDEFULL) अणु
		/* Endian settings are incorrect, calls क्रम another dekko. */
		DBG_PRINT(ERR_DBG,
			  "%s: Endian settings are wrong, feedback read %llx\n",
			  dev->name, (अचिन्हित दीर्घ दीर्घ)val64);
		वापस FAILURE;
	पूर्ण

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक रुको_क्रम_msix_trans(काष्ठा s2io_nic *nic, पूर्णांक i)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	u64 val64;
	पूर्णांक ret = 0, cnt = 0;

	करो अणु
		val64 = पढ़ोq(&bar0->xmsi_access);
		अगर (!(val64 & s2BIT(15)))
			अवरोध;
		mdelay(1);
		cnt++;
	पूर्ण जबतक (cnt < 5);
	अगर (cnt == 5) अणु
		DBG_PRINT(ERR_DBG, "XMSI # %d Access failed\n", i);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम restore_xmsi_data(काष्ठा s2io_nic *nic)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	u64 val64;
	पूर्णांक i, msix_index;

	अगर (nic->device_type == XFRAME_I_DEVICE)
		वापस;

	क्रम (i = 0; i < MAX_REQUESTED_MSI_X; i++) अणु
		msix_index = (i) ? ((i-1) * 8 + 1) : 0;
		ग_लिखोq(nic->msix_info[i].addr, &bar0->xmsi_address);
		ग_लिखोq(nic->msix_info[i].data, &bar0->xmsi_data);
		val64 = (s2BIT(7) | s2BIT(15) | vBIT(msix_index, 26, 6));
		ग_लिखोq(val64, &bar0->xmsi_access);
		अगर (रुको_क्रम_msix_trans(nic, msix_index))
			DBG_PRINT(ERR_DBG, "%s: index: %d failed\n",
				  __func__, msix_index);
	पूर्ण
पूर्ण

अटल व्योम store_xmsi_data(काष्ठा s2io_nic *nic)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	u64 val64, addr, data;
	पूर्णांक i, msix_index;

	अगर (nic->device_type == XFRAME_I_DEVICE)
		वापस;

	/* Store and display */
	क्रम (i = 0; i < MAX_REQUESTED_MSI_X; i++) अणु
		msix_index = (i) ? ((i-1) * 8 + 1) : 0;
		val64 = (s2BIT(15) | vBIT(msix_index, 26, 6));
		ग_लिखोq(val64, &bar0->xmsi_access);
		अगर (रुको_क्रम_msix_trans(nic, msix_index)) अणु
			DBG_PRINT(ERR_DBG, "%s: index: %d failed\n",
				  __func__, msix_index);
			जारी;
		पूर्ण
		addr = पढ़ोq(&bar0->xmsi_address);
		data = पढ़ोq(&bar0->xmsi_data);
		अगर (addr && data) अणु
			nic->msix_info[i].addr = addr;
			nic->msix_info[i].data = data;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक s2io_enable_msi_x(काष्ठा s2io_nic *nic)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	u64 rx_mat;
	u16 msi_control; /* Temp variable */
	पूर्णांक ret, i, j, msix_indx = 1;
	पूर्णांक size;
	काष्ठा stat_block *stats = nic->mac_control.stats_info;
	काष्ठा swStat *swstats = &stats->sw_stat;

	size = nic->num_entries * माप(काष्ठा msix_entry);
	nic->entries = kzalloc(size, GFP_KERNEL);
	अगर (!nic->entries) अणु
		DBG_PRINT(INFO_DBG, "%s: Memory allocation failed\n",
			  __func__);
		swstats->mem_alloc_fail_cnt++;
		वापस -ENOMEM;
	पूर्ण
	swstats->mem_allocated += size;

	size = nic->num_entries * माप(काष्ठा s2io_msix_entry);
	nic->s2io_entries = kzalloc(size, GFP_KERNEL);
	अगर (!nic->s2io_entries) अणु
		DBG_PRINT(INFO_DBG, "%s: Memory allocation failed\n",
			  __func__);
		swstats->mem_alloc_fail_cnt++;
		kमुक्त(nic->entries);
		swstats->mem_मुक्तd
			+= (nic->num_entries * माप(काष्ठा msix_entry));
		वापस -ENOMEM;
	पूर्ण
	swstats->mem_allocated += size;

	nic->entries[0].entry = 0;
	nic->s2io_entries[0].entry = 0;
	nic->s2io_entries[0].in_use = MSIX_FLG;
	nic->s2io_entries[0].type = MSIX_ALARM_TYPE;
	nic->s2io_entries[0].arg = &nic->mac_control.fअगरos;

	क्रम (i = 1; i < nic->num_entries; i++) अणु
		nic->entries[i].entry = ((i - 1) * 8) + 1;
		nic->s2io_entries[i].entry = ((i - 1) * 8) + 1;
		nic->s2io_entries[i].arg = शून्य;
		nic->s2io_entries[i].in_use = 0;
	पूर्ण

	rx_mat = पढ़ोq(&bar0->rx_mat);
	क्रम (j = 0; j < nic->config.rx_ring_num; j++) अणु
		rx_mat |= RX_MAT_SET(j, msix_indx);
		nic->s2io_entries[j+1].arg = &nic->mac_control.rings[j];
		nic->s2io_entries[j+1].type = MSIX_RING_TYPE;
		nic->s2io_entries[j+1].in_use = MSIX_FLG;
		msix_indx += 8;
	पूर्ण
	ग_लिखोq(rx_mat, &bar0->rx_mat);
	पढ़ोq(&bar0->rx_mat);

	ret = pci_enable_msix_range(nic->pdev, nic->entries,
				    nic->num_entries, nic->num_entries);
	/* We fail init अगर error or we get less vectors than min required */
	अगर (ret < 0) अणु
		DBG_PRINT(ERR_DBG, "Enabling MSI-X failed\n");
		kमुक्त(nic->entries);
		swstats->mem_मुक्तd += nic->num_entries *
			माप(काष्ठा msix_entry);
		kमुक्त(nic->s2io_entries);
		swstats->mem_मुक्तd += nic->num_entries *
			माप(काष्ठा s2io_msix_entry);
		nic->entries = शून्य;
		nic->s2io_entries = शून्य;
		वापस -ENOMEM;
	पूर्ण

	/*
	 * To enable MSI-X, MSI also needs to be enabled, due to a bug
	 * in the herc NIC. (Temp change, needs to be हटाओd later)
	 */
	pci_पढ़ो_config_word(nic->pdev, 0x42, &msi_control);
	msi_control |= 0x1; /* Enable MSI */
	pci_ग_लिखो_config_word(nic->pdev, 0x42, msi_control);

	वापस 0;
पूर्ण

/* Handle software पूर्णांकerrupt used during MSI(X) test */
अटल irqवापस_t s2io_test_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा s2io_nic *sp = dev_id;

	sp->msi_detected = 1;
	wake_up(&sp->msi_रुको);

	वापस IRQ_HANDLED;
पूर्ण

/* Test पूर्णांकerrupt path by क्रमcing a a software IRQ */
अटल पूर्णांक s2io_test_msi(काष्ठा s2io_nic *sp)
अणु
	काष्ठा pci_dev *pdev = sp->pdev;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	पूर्णांक err;
	u64 val64, saved64;

	err = request_irq(sp->entries[1].vector, s2io_test_पूर्णांकr, 0,
			  sp->name, sp);
	अगर (err) अणु
		DBG_PRINT(ERR_DBG, "%s: PCI %s: cannot assign irq %d\n",
			  sp->dev->name, pci_name(pdev), pdev->irq);
		वापस err;
	पूर्ण

	init_रुकोqueue_head(&sp->msi_रुको);
	sp->msi_detected = 0;

	saved64 = val64 = पढ़ोq(&bar0->scheduled_पूर्णांक_ctrl);
	val64 |= SCHED_INT_CTRL_ONE_SHOT;
	val64 |= SCHED_INT_CTRL_TIMER_EN;
	val64 |= SCHED_INT_CTRL_INT2MSI(1);
	ग_लिखोq(val64, &bar0->scheduled_पूर्णांक_ctrl);

	रुको_event_समयout(sp->msi_रुको, sp->msi_detected, HZ/10);

	अगर (!sp->msi_detected) अणु
		/* MSI(X) test failed, go back to INTx mode */
		DBG_PRINT(ERR_DBG, "%s: PCI %s: No interrupt was generated "
			  "using MSI(X) during test\n",
			  sp->dev->name, pci_name(pdev));

		err = -EOPNOTSUPP;
	पूर्ण

	मुक्त_irq(sp->entries[1].vector, sp);

	ग_लिखोq(saved64, &bar0->scheduled_पूर्णांक_ctrl);

	वापस err;
पूर्ण

अटल व्योम हटाओ_msix_isr(काष्ठा s2io_nic *sp)
अणु
	पूर्णांक i;
	u16 msi_control;

	क्रम (i = 0; i < sp->num_entries; i++) अणु
		अगर (sp->s2io_entries[i].in_use == MSIX_REGISTERED_SUCCESS) अणु
			पूर्णांक vector = sp->entries[i].vector;
			व्योम *arg = sp->s2io_entries[i].arg;
			मुक्त_irq(vector, arg);
		पूर्ण
	पूर्ण

	kमुक्त(sp->entries);
	kमुक्त(sp->s2io_entries);
	sp->entries = शून्य;
	sp->s2io_entries = शून्य;

	pci_पढ़ो_config_word(sp->pdev, 0x42, &msi_control);
	msi_control &= 0xFFFE; /* Disable MSI */
	pci_ग_लिखो_config_word(sp->pdev, 0x42, msi_control);

	pci_disable_msix(sp->pdev);
पूर्ण

अटल व्योम हटाओ_पूर्णांकa_isr(काष्ठा s2io_nic *sp)
अणु
	मुक्त_irq(sp->pdev->irq, sp->dev);
पूर्ण

/* ********************************************************* *
 * Functions defined below concern the OS part of the driver *
 * ********************************************************* */

/**
 *  s2io_खोलो - खोलो entry poपूर्णांक of the driver
 *  @dev : poपूर्णांकer to the device काष्ठाure.
 *  Description:
 *  This function is the खोलो entry poपूर्णांक of the driver. It मुख्यly calls a
 *  function to allocate Rx buffers and inserts them पूर्णांकo the buffer
 *  descriptors and then enables the Rx part of the NIC.
 *  Return value:
 *  0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *   file on failure.
 */

अटल पूर्णांक s2io_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा swStat *swstats = &sp->mac_control.stats_info->sw_stat;
	पूर्णांक err = 0;

	/*
	 * Make sure you have link off by शेष every समय
	 * Nic is initialized
	 */
	netअगर_carrier_off(dev);
	sp->last_link_state = 0;

	/* Initialize H/W and enable पूर्णांकerrupts */
	err = s2io_card_up(sp);
	अगर (err) अणु
		DBG_PRINT(ERR_DBG, "%s: H/W initialization failed\n",
			  dev->name);
		जाओ hw_init_failed;
	पूर्ण

	अगर (करो_s2io_prog_unicast(dev, dev->dev_addr) == FAILURE) अणु
		DBG_PRINT(ERR_DBG, "Set Mac Address Failed\n");
		s2io_card_करोwn(sp);
		err = -ENODEV;
		जाओ hw_init_failed;
	पूर्ण
	s2io_start_all_tx_queue(sp);
	वापस 0;

hw_init_failed:
	अगर (sp->config.पूर्णांकr_type == MSI_X) अणु
		अगर (sp->entries) अणु
			kमुक्त(sp->entries);
			swstats->mem_मुक्तd += sp->num_entries *
				माप(काष्ठा msix_entry);
		पूर्ण
		अगर (sp->s2io_entries) अणु
			kमुक्त(sp->s2io_entries);
			swstats->mem_मुक्तd += sp->num_entries *
				माप(काष्ठा s2io_msix_entry);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/**
 *  s2io_बंद -बंद entry poपूर्णांक of the driver
 *  @dev : device poपूर्णांकer.
 *  Description:
 *  This is the stop entry poपूर्णांक of the driver. It needs to unकरो exactly
 *  whatever was करोne by the खोलो entry poपूर्णांक,thus it's usually referred to
 *  as the बंद function.Among other things this function मुख्यly stops the
 *  Rx side of the NIC and मुक्तs all the Rx buffers in the Rx rings.
 *  Return value:
 *  0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *  file on failure.
 */

अटल पूर्णांक s2io_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा config_param *config = &sp->config;
	u64 पंचांगp64;
	पूर्णांक offset;

	/* Return अगर the device is alपढ़ोy बंदd               *
	 *  Can happen when s2io_card_up failed in change_mtu    *
	 */
	अगर (!is_s2io_card_up(sp))
		वापस 0;

	s2io_stop_all_tx_queue(sp);
	/* delete all populated mac entries */
	क्रम (offset = 1; offset < config->max_mc_addr; offset++) अणु
		पंचांगp64 = करो_s2io_पढ़ो_unicast_mc(sp, offset);
		अगर (पंचांगp64 != S2IO_DISABLE_MAC_ENTRY)
			करो_s2io_delete_unicast_mc(sp, पंचांगp64);
	पूर्ण

	s2io_card_करोwn(sp);

	वापस 0;
पूर्ण

/**
 *  s2io_xmit - Tx entry poपूर्णांक of te driver
 *  @skb : the socket buffer containing the Tx data.
 *  @dev : device poपूर्णांकer.
 *  Description :
 *  This function is the Tx entry poपूर्णांक of the driver. S2IO NIC supports
 *  certain protocol assist features on Tx side, namely  CSO, S/G, LSO.
 *  NOTE: when device can't queue the pkt,just the trans_start variable will
 *  not be upadted.
 *  Return value:
 *  0 on success & 1 on failure.
 */

अटल netdev_tx_t s2io_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	u16 frg_cnt, frg_len, i, queue, queue_len, put_off, get_off;
	रेजिस्टर u64 val64;
	काष्ठा TxD *txdp;
	काष्ठा TxFIFO_element __iomem *tx_fअगरo;
	अचिन्हित दीर्घ flags = 0;
	u16 vlan_tag = 0;
	काष्ठा fअगरo_info *fअगरo = शून्य;
	पूर्णांक offload_type;
	पूर्णांक enable_per_list_पूर्णांकerrupt = 0;
	काष्ठा config_param *config = &sp->config;
	काष्ठा mac_info *mac_control = &sp->mac_control;
	काष्ठा stat_block *stats = mac_control->stats_info;
	काष्ठा swStat *swstats = &stats->sw_stat;

	DBG_PRINT(TX_DBG, "%s: In Neterion Tx routine\n", dev->name);

	अगर (unlikely(skb->len <= 0)) अणु
		DBG_PRINT(TX_DBG, "%s: Buffer has no data..\n", dev->name);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (!is_s2io_card_up(sp)) अणु
		DBG_PRINT(TX_DBG, "%s: Card going down for reset\n",
			  dev->name);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	queue = 0;
	अगर (skb_vlan_tag_present(skb))
		vlan_tag = skb_vlan_tag_get(skb);
	अगर (sp->config.tx_steering_type == TX_DEFAULT_STEERING) अणु
		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			काष्ठा iphdr *ip;
			काष्ठा tcphdr *th;
			ip = ip_hdr(skb);

			अगर (!ip_is_fragment(ip)) अणु
				th = (काष्ठा tcphdr *)(((अचिन्हित अक्षर *)ip) +
						       ip->ihl*4);

				अगर (ip->protocol == IPPROTO_TCP) अणु
					queue_len = sp->total_tcp_fअगरos;
					queue = (ntohs(th->source) +
						 ntohs(th->dest)) &
						sp->fअगरo_selector[queue_len - 1];
					अगर (queue >= queue_len)
						queue = queue_len - 1;
				पूर्ण अन्यथा अगर (ip->protocol == IPPROTO_UDP) अणु
					queue_len = sp->total_udp_fअगरos;
					queue = (ntohs(th->source) +
						 ntohs(th->dest)) &
						sp->fअगरo_selector[queue_len - 1];
					अगर (queue >= queue_len)
						queue = queue_len - 1;
					queue += sp->udp_fअगरo_idx;
					अगर (skb->len > 1024)
						enable_per_list_पूर्णांकerrupt = 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (sp->config.tx_steering_type == TX_PRIORITY_STEERING)
		/* get fअगरo number based on skb->priority value */
		queue = config->fअगरo_mapping
			[skb->priority & (MAX_TX_FIFOS - 1)];
	fअगरo = &mac_control->fअगरos[queue];

	spin_lock_irqsave(&fअगरo->tx_lock, flags);

	अगर (sp->config.multiq) अणु
		अगर (__netअगर_subqueue_stopped(dev, fअगरo->fअगरo_no)) अणु
			spin_unlock_irqrestore(&fअगरo->tx_lock, flags);
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(fअगरo->queue_state == FIFO_QUEUE_STOP)) अणु
		अगर (netअगर_queue_stopped(dev)) अणु
			spin_unlock_irqrestore(&fअगरo->tx_lock, flags);
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण

	put_off = (u16)fअगरo->tx_curr_put_info.offset;
	get_off = (u16)fअगरo->tx_curr_get_info.offset;
	txdp = fअगरo->list_info[put_off].list_virt_addr;

	queue_len = fअगरo->tx_curr_put_info.fअगरo_len + 1;
	/* Aव्योम "put" poपूर्णांकer going beyond "get" poपूर्णांकer */
	अगर (txdp->Host_Control ||
	    ((put_off+1) == queue_len ? 0 : (put_off+1)) == get_off) अणु
		DBG_PRINT(TX_DBG, "Error in xmit, No free TXDs.\n");
		s2io_stop_tx_queue(sp, fअगरo->fअगरo_no);
		dev_kमुक्त_skb_any(skb);
		spin_unlock_irqrestore(&fअगरo->tx_lock, flags);
		वापस NETDEV_TX_OK;
	पूर्ण

	offload_type = s2io_offload_type(skb);
	अगर (offload_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)) अणु
		txdp->Control_1 |= TXD_TCP_LSO_EN;
		txdp->Control_1 |= TXD_TCP_LSO_MSS(s2io_tcp_mss(skb));
	पूर्ण
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		txdp->Control_2 |= (TXD_TX_CKO_IPV4_EN |
				    TXD_TX_CKO_TCP_EN |
				    TXD_TX_CKO_UDP_EN);
	पूर्ण
	txdp->Control_1 |= TXD_GATHER_CODE_FIRST;
	txdp->Control_1 |= TXD_LIST_OWN_XENA;
	txdp->Control_2 |= TXD_INT_NUMBER(fअगरo->fअगरo_no);
	अगर (enable_per_list_पूर्णांकerrupt)
		अगर (put_off & (queue_len >> 5))
			txdp->Control_2 |= TXD_INT_TYPE_PER_LIST;
	अगर (vlan_tag) अणु
		txdp->Control_2 |= TXD_VLAN_ENABLE;
		txdp->Control_2 |= TXD_VLAN_TAG(vlan_tag);
	पूर्ण

	frg_len = skb_headlen(skb);
	txdp->Buffer_Poपूर्णांकer = dma_map_single(&sp->pdev->dev, skb->data,
					      frg_len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&sp->pdev->dev, txdp->Buffer_Poपूर्णांकer))
		जाओ pci_map_failed;

	txdp->Host_Control = (अचिन्हित दीर्घ)skb;
	txdp->Control_1 |= TXD_BUFFER0_SIZE(frg_len);

	frg_cnt = skb_shinfo(skb)->nr_frags;
	/* For fragmented SKB. */
	क्रम (i = 0; i < frg_cnt; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		/* A '0' length fragment will be ignored */
		अगर (!skb_frag_size(frag))
			जारी;
		txdp++;
		txdp->Buffer_Poपूर्णांकer = (u64)skb_frag_dma_map(&sp->pdev->dev,
							     frag, 0,
							     skb_frag_size(frag),
							     DMA_TO_DEVICE);
		txdp->Control_1 = TXD_BUFFER0_SIZE(skb_frag_size(frag));
	पूर्ण
	txdp->Control_1 |= TXD_GATHER_CODE_LAST;

	tx_fअगरo = mac_control->tx_FIFO_start[queue];
	val64 = fअगरo->list_info[put_off].list_phy_addr;
	ग_लिखोq(val64, &tx_fअगरo->TxDL_Poपूर्णांकer);

	val64 = (TX_FIFO_LAST_TXD_NUM(frg_cnt) | TX_FIFO_FIRST_LIST |
		 TX_FIFO_LAST_LIST);
	अगर (offload_type)
		val64 |= TX_FIFO_SPECIAL_FUNC;

	ग_लिखोq(val64, &tx_fअगरo->List_Control);

	put_off++;
	अगर (put_off == fअगरo->tx_curr_put_info.fअगरo_len + 1)
		put_off = 0;
	fअगरo->tx_curr_put_info.offset = put_off;

	/* Aव्योम "put" poपूर्णांकer going beyond "get" poपूर्णांकer */
	अगर (((put_off+1) == queue_len ? 0 : (put_off+1)) == get_off) अणु
		swstats->fअगरo_full_cnt++;
		DBG_PRINT(TX_DBG,
			  "No free TxDs for xmit, Put: 0x%x Get:0x%x\n",
			  put_off, get_off);
		s2io_stop_tx_queue(sp, fअगरo->fअगरo_no);
	पूर्ण
	swstats->mem_allocated += skb->truesize;
	spin_unlock_irqrestore(&fअगरo->tx_lock, flags);

	अगर (sp->config.पूर्णांकr_type == MSI_X)
		tx_पूर्णांकr_handler(fअगरo);

	वापस NETDEV_TX_OK;

pci_map_failed:
	swstats->pci_map_fail_cnt++;
	s2io_stop_tx_queue(sp, fअगरo->fअगरo_no);
	swstats->mem_मुक्तd += skb->truesize;
	dev_kमुक्त_skb_any(skb);
	spin_unlock_irqrestore(&fअगरo->tx_lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम
s2io_alarm_handle(काष्ठा समयr_list *t)
अणु
	काष्ठा s2io_nic *sp = from_समयr(sp, t, alarm_समयr);
	काष्ठा net_device *dev = sp->dev;

	s2io_handle_errors(dev);
	mod_समयr(&sp->alarm_समयr, jअगरfies + HZ / 2);
पूर्ण

अटल irqवापस_t s2io_msix_ring_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ring_info *ring = (काष्ठा ring_info *)dev_id;
	काष्ठा s2io_nic *sp = ring->nic;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;

	अगर (unlikely(!is_s2io_card_up(sp)))
		वापस IRQ_HANDLED;

	अगर (sp->config.napi) अणु
		u8 __iomem *addr = शून्य;
		u8 val8 = 0;

		addr = (u8 __iomem *)&bar0->xmsi_mask_reg;
		addr += (7 - ring->ring_no);
		val8 = (ring->ring_no == 0) ? 0x7f : 0xff;
		ग_लिखोb(val8, addr);
		val8 = पढ़ोb(addr);
		napi_schedule(&ring->napi);
	पूर्ण अन्यथा अणु
		rx_पूर्णांकr_handler(ring, 0);
		s2io_chk_rx_buffers(sp, ring);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t s2io_msix_fअगरo_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक i;
	काष्ठा fअगरo_info *fअगरos = (काष्ठा fअगरo_info *)dev_id;
	काष्ठा s2io_nic *sp = fअगरos->nic;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	काष्ठा config_param *config  = &sp->config;
	u64 reason;

	अगर (unlikely(!is_s2io_card_up(sp)))
		वापस IRQ_NONE;

	reason = पढ़ोq(&bar0->general_पूर्णांक_status);
	अगर (unlikely(reason == S2IO_MINUS_ONE))
		/* Nothing much can be करोne. Get out */
		वापस IRQ_HANDLED;

	अगर (reason & (GEN_INTR_TXPIC | GEN_INTR_TXTRAFFIC)) अणु
		ग_लिखोq(S2IO_MINUS_ONE, &bar0->general_पूर्णांक_mask);

		अगर (reason & GEN_INTR_TXPIC)
			s2io_txpic_पूर्णांकr_handle(sp);

		अगर (reason & GEN_INTR_TXTRAFFIC)
			ग_लिखोq(S2IO_MINUS_ONE, &bar0->tx_traffic_पूर्णांक);

		क्रम (i = 0; i < config->tx_fअगरo_num; i++)
			tx_पूर्णांकr_handler(&fअगरos[i]);

		ग_लिखोq(sp->general_पूर्णांक_mask, &bar0->general_पूर्णांक_mask);
		पढ़ोl(&bar0->general_पूर्णांक_status);
		वापस IRQ_HANDLED;
	पूर्ण
	/* The पूर्णांकerrupt was not उठाओd by us */
	वापस IRQ_NONE;
पूर्ण

अटल व्योम s2io_txpic_पूर्णांकr_handle(काष्ठा s2io_nic *sp)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64;

	val64 = पढ़ोq(&bar0->pic_पूर्णांक_status);
	अगर (val64 & PIC_INT_GPIO) अणु
		val64 = पढ़ोq(&bar0->gpio_पूर्णांक_reg);
		अगर ((val64 & GPIO_INT_REG_LINK_DOWN) &&
		    (val64 & GPIO_INT_REG_LINK_UP)) अणु
			/*
			 * This is unstable state so clear both up/करोwn
			 * पूर्णांकerrupt and adapter to re-evaluate the link state.
			 */
			val64 |= GPIO_INT_REG_LINK_DOWN;
			val64 |= GPIO_INT_REG_LINK_UP;
			ग_लिखोq(val64, &bar0->gpio_पूर्णांक_reg);
			val64 = पढ़ोq(&bar0->gpio_पूर्णांक_mask);
			val64 &= ~(GPIO_INT_MASK_LINK_UP |
				   GPIO_INT_MASK_LINK_DOWN);
			ग_लिखोq(val64, &bar0->gpio_पूर्णांक_mask);
		पूर्ण अन्यथा अगर (val64 & GPIO_INT_REG_LINK_UP) अणु
			val64 = पढ़ोq(&bar0->adapter_status);
			/* Enable Adapter */
			val64 = पढ़ोq(&bar0->adapter_control);
			val64 |= ADAPTER_CNTL_EN;
			ग_लिखोq(val64, &bar0->adapter_control);
			val64 |= ADAPTER_LED_ON;
			ग_लिखोq(val64, &bar0->adapter_control);
			अगर (!sp->device_enabled_once)
				sp->device_enabled_once = 1;

			s2io_link(sp, LINK_UP);
			/*
			 * unmask link करोwn पूर्णांकerrupt and mask link-up
			 * पूर्णांकr
			 */
			val64 = पढ़ोq(&bar0->gpio_पूर्णांक_mask);
			val64 &= ~GPIO_INT_MASK_LINK_DOWN;
			val64 |= GPIO_INT_MASK_LINK_UP;
			ग_लिखोq(val64, &bar0->gpio_पूर्णांक_mask);

		पूर्ण अन्यथा अगर (val64 & GPIO_INT_REG_LINK_DOWN) अणु
			val64 = पढ़ोq(&bar0->adapter_status);
			s2io_link(sp, LINK_DOWN);
			/* Link is करोwn so unmaks link up पूर्णांकerrupt */
			val64 = पढ़ोq(&bar0->gpio_पूर्णांक_mask);
			val64 &= ~GPIO_INT_MASK_LINK_UP;
			val64 |= GPIO_INT_MASK_LINK_DOWN;
			ग_लिखोq(val64, &bar0->gpio_पूर्णांक_mask);

			/* turn off LED */
			val64 = पढ़ोq(&bar0->adapter_control);
			val64 = val64 & (~ADAPTER_LED_ON);
			ग_लिखोq(val64, &bar0->adapter_control);
		पूर्ण
	पूर्ण
	val64 = पढ़ोq(&bar0->gpio_पूर्णांक_mask);
पूर्ण

/**
 *  करो_s2io_chk_alarm_bit - Check क्रम alarm and incrment the counter
 *  @value: alarm bits
 *  @addr: address value
 *  @cnt: counter variable
 *  Description: Check क्रम alarm and increment the counter
 *  Return Value:
 *  1 - अगर alarm bit set
 *  0 - अगर alarm bit is not set
 */
अटल पूर्णांक करो_s2io_chk_alarm_bit(u64 value, व्योम __iomem *addr,
				 अचिन्हित दीर्घ दीर्घ *cnt)
अणु
	u64 val64;
	val64 = पढ़ोq(addr);
	अगर (val64 & value) अणु
		ग_लिखोq(val64, addr);
		(*cnt)++;
		वापस 1;
	पूर्ण
	वापस 0;

पूर्ण

/**
 *  s2io_handle_errors - Xframe error indication handler
 *  @dev_id: opaque handle to dev
 *  Description: Handle alarms such as loss of link, single or
 *  द्विगुन ECC errors, critical and serious errors.
 *  Return Value:
 *  NONE
 */
अटल व्योम s2io_handle_errors(व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 temp64 = 0, val64 = 0;
	पूर्णांक i = 0;

	काष्ठा swStat *sw_stat = &sp->mac_control.stats_info->sw_stat;
	काष्ठा xpakStat *stats = &sp->mac_control.stats_info->xpak_stat;

	अगर (!is_s2io_card_up(sp))
		वापस;

	अगर (pci_channel_offline(sp->pdev))
		वापस;

	स_रखो(&sw_stat->ring_full_cnt, 0,
	       माप(sw_stat->ring_full_cnt));

	/* Handling the XPAK counters update */
	अगर (stats->xpak_समयr_count < 72000) अणु
		/* रुकोing क्रम an hour */
		stats->xpak_समयr_count++;
	पूर्ण अन्यथा अणु
		s2io_updt_xpak_counter(dev);
		/* reset the count to zero */
		stats->xpak_समयr_count = 0;
	पूर्ण

	/* Handling link status change error Intr */
	अगर (s2io_link_fault_indication(sp) == MAC_RMAC_ERR_TIMER) अणु
		val64 = पढ़ोq(&bar0->mac_rmac_err_reg);
		ग_लिखोq(val64, &bar0->mac_rmac_err_reg);
		अगर (val64 & RMAC_LINK_STATE_CHANGE_INT)
			schedule_work(&sp->set_link_task);
	पूर्ण

	/* In हाल of a serious error, the device will be Reset. */
	अगर (करो_s2io_chk_alarm_bit(SERR_SOURCE_ANY, &bar0->serr_source,
				  &sw_stat->serious_err_cnt))
		जाओ reset;

	/* Check क्रम data parity error */
	अगर (करो_s2io_chk_alarm_bit(GPIO_INT_REG_DP_ERR_INT, &bar0->gpio_पूर्णांक_reg,
				  &sw_stat->parity_err_cnt))
		जाओ reset;

	/* Check क्रम ring full counter */
	अगर (sp->device_type == XFRAME_II_DEVICE) अणु
		val64 = पढ़ोq(&bar0->ring_bump_counter1);
		क्रम (i = 0; i < 4; i++) अणु
			temp64 = (val64 & vBIT(0xFFFF, (i*16), 16));
			temp64 >>= 64 - ((i+1)*16);
			sw_stat->ring_full_cnt[i] += temp64;
		पूर्ण

		val64 = पढ़ोq(&bar0->ring_bump_counter2);
		क्रम (i = 0; i < 4; i++) अणु
			temp64 = (val64 & vBIT(0xFFFF, (i*16), 16));
			temp64 >>= 64 - ((i+1)*16);
			sw_stat->ring_full_cnt[i+4] += temp64;
		पूर्ण
	पूर्ण

	val64 = पढ़ोq(&bar0->txdma_पूर्णांक_status);
	/*check क्रम pfc_err*/
	अगर (val64 & TXDMA_PFC_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(PFC_ECC_DB_ERR | PFC_SM_ERR_ALARM |
					  PFC_MISC_0_ERR | PFC_MISC_1_ERR |
					  PFC_PCIX_ERR,
					  &bar0->pfc_err_reg,
					  &sw_stat->pfc_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(PFC_ECC_SG_ERR,
				      &bar0->pfc_err_reg,
				      &sw_stat->pfc_err_cnt);
	पूर्ण

	/*check क्रम tda_err*/
	अगर (val64 & TXDMA_TDA_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(TDA_Fn_ECC_DB_ERR |
					  TDA_SM0_ERR_ALARM |
					  TDA_SM1_ERR_ALARM,
					  &bar0->tda_err_reg,
					  &sw_stat->tda_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(TDA_Fn_ECC_SG_ERR | TDA_PCIX_ERR,
				      &bar0->tda_err_reg,
				      &sw_stat->tda_err_cnt);
	पूर्ण
	/*check क्रम pcc_err*/
	अगर (val64 & TXDMA_PCC_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(PCC_SM_ERR_ALARM | PCC_WR_ERR_ALARM |
					  PCC_N_SERR | PCC_6_COF_OV_ERR |
					  PCC_7_COF_OV_ERR | PCC_6_LSO_OV_ERR |
					  PCC_7_LSO_OV_ERR | PCC_FB_ECC_DB_ERR |
					  PCC_TXB_ECC_DB_ERR,
					  &bar0->pcc_err_reg,
					  &sw_stat->pcc_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(PCC_FB_ECC_SG_ERR | PCC_TXB_ECC_SG_ERR,
				      &bar0->pcc_err_reg,
				      &sw_stat->pcc_err_cnt);
	पूर्ण

	/*check क्रम tti_err*/
	अगर (val64 & TXDMA_TTI_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(TTI_SM_ERR_ALARM,
					  &bar0->tti_err_reg,
					  &sw_stat->tti_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(TTI_ECC_SG_ERR | TTI_ECC_DB_ERR,
				      &bar0->tti_err_reg,
				      &sw_stat->tti_err_cnt);
	पूर्ण

	/*check क्रम lso_err*/
	अगर (val64 & TXDMA_LSO_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(LSO6_ABORT | LSO7_ABORT |
					  LSO6_SM_ERR_ALARM | LSO7_SM_ERR_ALARM,
					  &bar0->lso_err_reg,
					  &sw_stat->lso_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(LSO6_SEND_OFLOW | LSO7_SEND_OFLOW,
				      &bar0->lso_err_reg,
				      &sw_stat->lso_err_cnt);
	पूर्ण

	/*check क्रम tpa_err*/
	अगर (val64 & TXDMA_TPA_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(TPA_SM_ERR_ALARM,
					  &bar0->tpa_err_reg,
					  &sw_stat->tpa_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(TPA_TX_FRM_DROP,
				      &bar0->tpa_err_reg,
				      &sw_stat->tpa_err_cnt);
	पूर्ण

	/*check क्रम sm_err*/
	अगर (val64 & TXDMA_SM_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(SM_SM_ERR_ALARM,
					  &bar0->sm_err_reg,
					  &sw_stat->sm_err_cnt))
			जाओ reset;
	पूर्ण

	val64 = पढ़ोq(&bar0->mac_पूर्णांक_status);
	अगर (val64 & MAC_INT_STATUS_TMAC_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(TMAC_TX_BUF_OVRN | TMAC_TX_SM_ERR,
					  &bar0->mac_पंचांगac_err_reg,
					  &sw_stat->mac_पंचांगac_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(TMAC_ECC_SG_ERR | TMAC_ECC_DB_ERR |
				      TMAC_DESC_ECC_SG_ERR |
				      TMAC_DESC_ECC_DB_ERR,
				      &bar0->mac_पंचांगac_err_reg,
				      &sw_stat->mac_पंचांगac_err_cnt);
	पूर्ण

	val64 = पढ़ोq(&bar0->xgxs_पूर्णांक_status);
	अगर (val64 & XGXS_INT_STATUS_TXGXS) अणु
		अगर (करो_s2io_chk_alarm_bit(TXGXS_ESTORE_UFLOW | TXGXS_TX_SM_ERR,
					  &bar0->xgxs_txgxs_err_reg,
					  &sw_stat->xgxs_txgxs_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(TXGXS_ECC_SG_ERR | TXGXS_ECC_DB_ERR,
				      &bar0->xgxs_txgxs_err_reg,
				      &sw_stat->xgxs_txgxs_err_cnt);
	पूर्ण

	val64 = पढ़ोq(&bar0->rxdma_पूर्णांक_status);
	अगर (val64 & RXDMA_INT_RC_INT_M) अणु
		अगर (करो_s2io_chk_alarm_bit(RC_PRCn_ECC_DB_ERR |
					  RC_FTC_ECC_DB_ERR |
					  RC_PRCn_SM_ERR_ALARM |
					  RC_FTC_SM_ERR_ALARM,
					  &bar0->rc_err_reg,
					  &sw_stat->rc_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(RC_PRCn_ECC_SG_ERR |
				      RC_FTC_ECC_SG_ERR |
				      RC_RDA_FAIL_WR_Rn, &bar0->rc_err_reg,
				      &sw_stat->rc_err_cnt);
		अगर (करो_s2io_chk_alarm_bit(PRC_PCI_AB_RD_Rn |
					  PRC_PCI_AB_WR_Rn |
					  PRC_PCI_AB_F_WR_Rn,
					  &bar0->prc_pcix_err_reg,
					  &sw_stat->prc_pcix_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(PRC_PCI_DP_RD_Rn |
				      PRC_PCI_DP_WR_Rn |
				      PRC_PCI_DP_F_WR_Rn,
				      &bar0->prc_pcix_err_reg,
				      &sw_stat->prc_pcix_err_cnt);
	पूर्ण

	अगर (val64 & RXDMA_INT_RPA_INT_M) अणु
		अगर (करो_s2io_chk_alarm_bit(RPA_SM_ERR_ALARM | RPA_CREDIT_ERR,
					  &bar0->rpa_err_reg,
					  &sw_stat->rpa_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(RPA_ECC_SG_ERR | RPA_ECC_DB_ERR,
				      &bar0->rpa_err_reg,
				      &sw_stat->rpa_err_cnt);
	पूर्ण

	अगर (val64 & RXDMA_INT_RDA_INT_M) अणु
		अगर (करो_s2io_chk_alarm_bit(RDA_RXDn_ECC_DB_ERR |
					  RDA_FRM_ECC_DB_N_AERR |
					  RDA_SM1_ERR_ALARM |
					  RDA_SM0_ERR_ALARM |
					  RDA_RXD_ECC_DB_SERR,
					  &bar0->rda_err_reg,
					  &sw_stat->rda_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(RDA_RXDn_ECC_SG_ERR |
				      RDA_FRM_ECC_SG_ERR |
				      RDA_MISC_ERR |
				      RDA_PCIX_ERR,
				      &bar0->rda_err_reg,
				      &sw_stat->rda_err_cnt);
	पूर्ण

	अगर (val64 & RXDMA_INT_RTI_INT_M) अणु
		अगर (करो_s2io_chk_alarm_bit(RTI_SM_ERR_ALARM,
					  &bar0->rti_err_reg,
					  &sw_stat->rti_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(RTI_ECC_SG_ERR | RTI_ECC_DB_ERR,
				      &bar0->rti_err_reg,
				      &sw_stat->rti_err_cnt);
	पूर्ण

	val64 = पढ़ोq(&bar0->mac_पूर्णांक_status);
	अगर (val64 & MAC_INT_STATUS_RMAC_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(RMAC_RX_BUFF_OVRN | RMAC_RX_SM_ERR,
					  &bar0->mac_rmac_err_reg,
					  &sw_stat->mac_rmac_err_cnt))
			जाओ reset;
		करो_s2io_chk_alarm_bit(RMAC_UNUSED_INT |
				      RMAC_SINGLE_ECC_ERR |
				      RMAC_DOUBLE_ECC_ERR,
				      &bar0->mac_rmac_err_reg,
				      &sw_stat->mac_rmac_err_cnt);
	पूर्ण

	val64 = पढ़ोq(&bar0->xgxs_पूर्णांक_status);
	अगर (val64 & XGXS_INT_STATUS_RXGXS) अणु
		अगर (करो_s2io_chk_alarm_bit(RXGXS_ESTORE_OFLOW | RXGXS_RX_SM_ERR,
					  &bar0->xgxs_rxgxs_err_reg,
					  &sw_stat->xgxs_rxgxs_err_cnt))
			जाओ reset;
	पूर्ण

	val64 = पढ़ोq(&bar0->mc_पूर्णांक_status);
	अगर (val64 & MC_INT_STATUS_MC_INT) अणु
		अगर (करो_s2io_chk_alarm_bit(MC_ERR_REG_SM_ERR,
					  &bar0->mc_err_reg,
					  &sw_stat->mc_err_cnt))
			जाओ reset;

		/* Handling Ecc errors */
		अगर (val64 & (MC_ERR_REG_ECC_ALL_SNG | MC_ERR_REG_ECC_ALL_DBL)) अणु
			ग_लिखोq(val64, &bar0->mc_err_reg);
			अगर (val64 & MC_ERR_REG_ECC_ALL_DBL) अणु
				sw_stat->द्विगुन_ecc_errs++;
				अगर (sp->device_type != XFRAME_II_DEVICE) अणु
					/*
					 * Reset XframeI only अगर critical error
					 */
					अगर (val64 &
					    (MC_ERR_REG_MIRI_ECC_DB_ERR_0 |
					     MC_ERR_REG_MIRI_ECC_DB_ERR_1))
						जाओ reset;
				पूर्ण
			पूर्ण अन्यथा
				sw_stat->single_ecc_errs++;
		पूर्ण
	पूर्ण
	वापस;

reset:
	s2io_stop_all_tx_queue(sp);
	schedule_work(&sp->rst_समयr_task);
	sw_stat->soft_reset_cnt++;
पूर्ण

/**
 *  s2io_isr - ISR handler of the device .
 *  @irq: the irq of the device.
 *  @dev_id: a व्योम poपूर्णांकer to the dev काष्ठाure of the NIC.
 *  Description:  This function is the ISR handler of the device. It
 *  identअगरies the reason क्रम the पूर्णांकerrupt and calls the relevant
 *  service routines. As a contongency measure, this ISR allocates the
 *  recv buffers, अगर their numbers are below the panic value which is
 *  presently set to 25% of the original number of rcv buffers allocated.
 *  Return value:
 *   IRQ_HANDLED: will be वापसed अगर IRQ was handled by this routine
 *   IRQ_NONE: will be वापसed अगर पूर्णांकerrupt is not from our device
 */
अटल irqवापस_t s2io_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	पूर्णांक i;
	u64 reason = 0;
	काष्ठा mac_info *mac_control;
	काष्ठा config_param *config;

	/* Pretend we handled any irq's from a disconnected card */
	अगर (pci_channel_offline(sp->pdev))
		वापस IRQ_NONE;

	अगर (!is_s2io_card_up(sp))
		वापस IRQ_NONE;

	config = &sp->config;
	mac_control = &sp->mac_control;

	/*
	 * Identअगरy the cause क्रम पूर्णांकerrupt and call the appropriate
	 * पूर्णांकerrupt handler. Causes क्रम the पूर्णांकerrupt could be;
	 * 1. Rx of packet.
	 * 2. Tx complete.
	 * 3. Link करोwn.
	 */
	reason = पढ़ोq(&bar0->general_पूर्णांक_status);

	अगर (unlikely(reason == S2IO_MINUS_ONE))
		वापस IRQ_HANDLED;	/* Nothing much can be करोne. Get out */

	अगर (reason &
	    (GEN_INTR_RXTRAFFIC | GEN_INTR_TXTRAFFIC | GEN_INTR_TXPIC)) अणु
		ग_लिखोq(S2IO_MINUS_ONE, &bar0->general_पूर्णांक_mask);

		अगर (config->napi) अणु
			अगर (reason & GEN_INTR_RXTRAFFIC) अणु
				napi_schedule(&sp->napi);
				ग_लिखोq(S2IO_MINUS_ONE, &bar0->rx_traffic_mask);
				ग_लिखोq(S2IO_MINUS_ONE, &bar0->rx_traffic_पूर्णांक);
				पढ़ोl(&bar0->rx_traffic_पूर्णांक);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * rx_traffic_पूर्णांक reg is an R1 रेजिस्टर, writing all 1's
			 * will ensure that the actual पूर्णांकerrupt causing bit
			 * get's cleared and hence a पढ़ो can be aव्योमed.
			 */
			अगर (reason & GEN_INTR_RXTRAFFIC)
				ग_लिखोq(S2IO_MINUS_ONE, &bar0->rx_traffic_पूर्णांक);

			क्रम (i = 0; i < config->rx_ring_num; i++) अणु
				काष्ठा ring_info *ring = &mac_control->rings[i];

				rx_पूर्णांकr_handler(ring, 0);
			पूर्ण
		पूर्ण

		/*
		 * tx_traffic_पूर्णांक reg is an R1 रेजिस्टर, writing all 1's
		 * will ensure that the actual पूर्णांकerrupt causing bit get's
		 * cleared and hence a पढ़ो can be aव्योमed.
		 */
		अगर (reason & GEN_INTR_TXTRAFFIC)
			ग_लिखोq(S2IO_MINUS_ONE, &bar0->tx_traffic_पूर्णांक);

		क्रम (i = 0; i < config->tx_fअगरo_num; i++)
			tx_पूर्णांकr_handler(&mac_control->fअगरos[i]);

		अगर (reason & GEN_INTR_TXPIC)
			s2io_txpic_पूर्णांकr_handle(sp);

		/*
		 * Reallocate the buffers from the पूर्णांकerrupt handler itself.
		 */
		अगर (!config->napi) अणु
			क्रम (i = 0; i < config->rx_ring_num; i++) अणु
				काष्ठा ring_info *ring = &mac_control->rings[i];

				s2io_chk_rx_buffers(sp, ring);
			पूर्ण
		पूर्ण
		ग_लिखोq(sp->general_पूर्णांक_mask, &bar0->general_पूर्णांक_mask);
		पढ़ोl(&bar0->general_पूर्णांक_status);

		वापस IRQ_HANDLED;

	पूर्ण अन्यथा अगर (!reason) अणु
		/* The पूर्णांकerrupt was not उठाओd by us */
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * s2io_updt_stats -
 */
अटल व्योम s2io_updt_stats(काष्ठा s2io_nic *sp)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64;
	पूर्णांक cnt = 0;

	अगर (is_s2io_card_up(sp)) अणु
		/* Apprx 30us on a 133 MHz bus */
		val64 = SET_UPDT_CLICKS(10) |
			STAT_CFG_ONE_SHOT_EN | STAT_CFG_STAT_EN;
		ग_लिखोq(val64, &bar0->stat_cfg);
		करो अणु
			udelay(100);
			val64 = पढ़ोq(&bar0->stat_cfg);
			अगर (!(val64 & s2BIT(0)))
				अवरोध;
			cnt++;
			अगर (cnt == 5)
				अवरोध; /* Updt failed */
		पूर्ण जबतक (1);
	पूर्ण
पूर्ण

/**
 *  s2io_get_stats - Updates the device statistics काष्ठाure.
 *  @dev : poपूर्णांकer to the device काष्ठाure.
 *  Description:
 *  This function updates the device statistics काष्ठाure in the s2io_nic
 *  काष्ठाure and वापसs a poपूर्णांकer to the same.
 *  Return value:
 *  poपूर्णांकer to the updated net_device_stats काष्ठाure.
 */
अटल काष्ठा net_device_stats *s2io_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा mac_info *mac_control = &sp->mac_control;
	काष्ठा stat_block *stats = mac_control->stats_info;
	u64 delta;

	/* Configure Stats क्रम immediate updt */
	s2io_updt_stats(sp);

	/* A device reset will cause the on-adapter statistics to be zero'ed.
	 * This can be करोne जबतक running by changing the MTU.  To prevent the
	 * प्रणाली from having the stats zero'ed, the driver keeps a copy of the
	 * last update to the प्रणाली (which is also zero'ed on reset).  This
	 * enables the driver to accurately know the delta between the last
	 * update and the current update.
	 */
	delta = ((u64) le32_to_cpu(stats->rmac_vld_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_vld_frms)) - sp->stats.rx_packets;
	sp->stats.rx_packets += delta;
	dev->stats.rx_packets += delta;

	delta = ((u64) le32_to_cpu(stats->पंचांगac_frms_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_frms)) - sp->stats.tx_packets;
	sp->stats.tx_packets += delta;
	dev->stats.tx_packets += delta;

	delta = ((u64) le32_to_cpu(stats->rmac_data_octets_oflow) << 32 |
		le32_to_cpu(stats->rmac_data_octets)) - sp->stats.rx_bytes;
	sp->stats.rx_bytes += delta;
	dev->stats.rx_bytes += delta;

	delta = ((u64) le32_to_cpu(stats->पंचांगac_data_octets_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_data_octets)) - sp->stats.tx_bytes;
	sp->stats.tx_bytes += delta;
	dev->stats.tx_bytes += delta;

	delta = le64_to_cpu(stats->rmac_drop_frms) - sp->stats.rx_errors;
	sp->stats.rx_errors += delta;
	dev->stats.rx_errors += delta;

	delta = ((u64) le32_to_cpu(stats->पंचांगac_any_err_frms_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_any_err_frms)) - sp->stats.tx_errors;
	sp->stats.tx_errors += delta;
	dev->stats.tx_errors += delta;

	delta = le64_to_cpu(stats->rmac_drop_frms) - sp->stats.rx_dropped;
	sp->stats.rx_dropped += delta;
	dev->stats.rx_dropped += delta;

	delta = le64_to_cpu(stats->पंचांगac_drop_frms) - sp->stats.tx_dropped;
	sp->stats.tx_dropped += delta;
	dev->stats.tx_dropped += delta;

	/* The adapter MAC पूर्णांकerprets छोड़ो frames as multicast packets, but
	 * करोes not pass them up.  This erroneously increases the multicast
	 * packet count and needs to be deducted when the multicast frame count
	 * is queried.
	 */
	delta = (u64) le32_to_cpu(stats->rmac_vld_mcst_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_vld_mcst_frms);
	delta -= le64_to_cpu(stats->rmac_छोड़ो_ctrl_frms);
	delta -= sp->stats.multicast;
	sp->stats.multicast += delta;
	dev->stats.multicast += delta;

	delta = ((u64) le32_to_cpu(stats->rmac_usized_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_usized_frms)) +
		le64_to_cpu(stats->rmac_दीर्घ_frms) - sp->stats.rx_length_errors;
	sp->stats.rx_length_errors += delta;
	dev->stats.rx_length_errors += delta;

	delta = le64_to_cpu(stats->rmac_fcs_err_frms) - sp->stats.rx_crc_errors;
	sp->stats.rx_crc_errors += delta;
	dev->stats.rx_crc_errors += delta;

	वापस &dev->stats;
पूर्ण

/**
 *  s2io_set_multicast - entry poपूर्णांक क्रम multicast address enable/disable.
 *  @dev : poपूर्णांकer to the device काष्ठाure
 *  Description:
 *  This function is a driver entry poपूर्णांक which माला_लो called by the kernel
 *  whenever multicast addresses must be enabled/disabled. This also माला_लो
 *  called to set/reset promiscuous mode. Depending on the deivce flag, we
 *  determine, अगर multicast address must be enabled or अगर promiscuous mode
 *  is to be disabled etc.
 *  Return value:
 *  व्योम.
 */
अटल व्योम s2io_set_multicast(काष्ठा net_device *dev, bool may_sleep)
अणु
	पूर्णांक i, j, prev_cnt;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64 = 0, multi_mac = 0x010203040506ULL, mask =
		0xfeffffffffffULL;
	u64 dis_addr = S2IO_DISABLE_MAC_ENTRY, mac_addr = 0;
	व्योम __iomem *add;
	काष्ठा config_param *config = &sp->config;

	अगर ((dev->flags & IFF_ALLMULTI) && (!sp->m_cast_flg)) अणु
		/*  Enable all Multicast addresses */
		ग_लिखोq(RMAC_ADDR_DATA0_MEM_ADDR(multi_mac),
		       &bar0->rmac_addr_data0_mem);
		ग_लिखोq(RMAC_ADDR_DATA1_MEM_MASK(mask),
		       &bar0->rmac_addr_data1_mem);
		val64 = RMAC_ADDR_CMD_MEM_WE |
			RMAC_ADDR_CMD_MEM_STROBE_NEW_CMD |
			RMAC_ADDR_CMD_MEM_OFFSET(config->max_mc_addr - 1);
		ग_लिखोq(val64, &bar0->rmac_addr_cmd_mem);
		/* Wait till command completes */
		रुको_क्रम_cmd_complete(&bar0->rmac_addr_cmd_mem,
				      RMAC_ADDR_CMD_MEM_STROBE_CMD_EXECUTING,
				      S2IO_BIT_RESET, may_sleep);

		sp->m_cast_flg = 1;
		sp->all_multi_pos = config->max_mc_addr - 1;
	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI) && (sp->m_cast_flg)) अणु
		/*  Disable all Multicast addresses */
		ग_लिखोq(RMAC_ADDR_DATA0_MEM_ADDR(dis_addr),
		       &bar0->rmac_addr_data0_mem);
		ग_लिखोq(RMAC_ADDR_DATA1_MEM_MASK(0x0),
		       &bar0->rmac_addr_data1_mem);
		val64 = RMAC_ADDR_CMD_MEM_WE |
			RMAC_ADDR_CMD_MEM_STROBE_NEW_CMD |
			RMAC_ADDR_CMD_MEM_OFFSET(sp->all_multi_pos);
		ग_लिखोq(val64, &bar0->rmac_addr_cmd_mem);
		/* Wait till command completes */
		रुको_क्रम_cmd_complete(&bar0->rmac_addr_cmd_mem,
				      RMAC_ADDR_CMD_MEM_STROBE_CMD_EXECUTING,
				      S2IO_BIT_RESET, may_sleep);

		sp->m_cast_flg = 0;
		sp->all_multi_pos = 0;
	पूर्ण

	अगर ((dev->flags & IFF_PROMISC) && (!sp->promisc_flg)) अणु
		/*  Put the NIC पूर्णांकo promiscuous mode */
		add = &bar0->mac_cfg;
		val64 = पढ़ोq(&bar0->mac_cfg);
		val64 |= MAC_CFG_RMAC_PROM_ENABLE;

		ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
		ग_लिखोl((u32)val64, add);
		ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
		ग_लिखोl((u32) (val64 >> 32), (add + 4));

		अगर (vlan_tag_strip != 1) अणु
			val64 = पढ़ोq(&bar0->rx_pa_cfg);
			val64 &= ~RX_PA_CFG_STRIP_VLAN_TAG;
			ग_लिखोq(val64, &bar0->rx_pa_cfg);
			sp->vlan_strip_flag = 0;
		पूर्ण

		val64 = पढ़ोq(&bar0->mac_cfg);
		sp->promisc_flg = 1;
		DBG_PRINT(INFO_DBG, "%s: entered promiscuous mode\n",
			  dev->name);
	पूर्ण अन्यथा अगर (!(dev->flags & IFF_PROMISC) && (sp->promisc_flg)) अणु
		/*  Remove the NIC from promiscuous mode */
		add = &bar0->mac_cfg;
		val64 = पढ़ोq(&bar0->mac_cfg);
		val64 &= ~MAC_CFG_RMAC_PROM_ENABLE;

		ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
		ग_लिखोl((u32)val64, add);
		ग_लिखोq(RMAC_CFG_KEY(0x4C0D), &bar0->rmac_cfg_key);
		ग_लिखोl((u32) (val64 >> 32), (add + 4));

		अगर (vlan_tag_strip != 0) अणु
			val64 = पढ़ोq(&bar0->rx_pa_cfg);
			val64 |= RX_PA_CFG_STRIP_VLAN_TAG;
			ग_लिखोq(val64, &bar0->rx_pa_cfg);
			sp->vlan_strip_flag = 1;
		पूर्ण

		val64 = पढ़ोq(&bar0->mac_cfg);
		sp->promisc_flg = 0;
		DBG_PRINT(INFO_DBG, "%s: left promiscuous mode\n", dev->name);
	पूर्ण

	/*  Update inभागidual M_CAST address list */
	अगर ((!sp->m_cast_flg) && netdev_mc_count(dev)) अणु
		अगर (netdev_mc_count(dev) >
		    (config->max_mc_addr - config->max_mac_addr)) अणु
			DBG_PRINT(ERR_DBG,
				  "%s: No more Rx filters can be added - "
				  "please enable ALL_MULTI instead\n",
				  dev->name);
			वापस;
		पूर्ण

		prev_cnt = sp->mc_addr_count;
		sp->mc_addr_count = netdev_mc_count(dev);

		/* Clear out the previous list of Mc in the H/W. */
		क्रम (i = 0; i < prev_cnt; i++) अणु
			ग_लिखोq(RMAC_ADDR_DATA0_MEM_ADDR(dis_addr),
			       &bar0->rmac_addr_data0_mem);
			ग_लिखोq(RMAC_ADDR_DATA1_MEM_MASK(0ULL),
			       &bar0->rmac_addr_data1_mem);
			val64 = RMAC_ADDR_CMD_MEM_WE |
				RMAC_ADDR_CMD_MEM_STROBE_NEW_CMD |
				RMAC_ADDR_CMD_MEM_OFFSET
				(config->mc_start_offset + i);
			ग_लिखोq(val64, &bar0->rmac_addr_cmd_mem);

			/* Wait क्रम command completes */
			अगर (रुको_क्रम_cmd_complete(&bar0->rmac_addr_cmd_mem,
						  RMAC_ADDR_CMD_MEM_STROBE_CMD_EXECUTING,
						  S2IO_BIT_RESET, may_sleep)) अणु
				DBG_PRINT(ERR_DBG,
					  "%s: Adding Multicasts failed\n",
					  dev->name);
				वापस;
			पूर्ण
		पूर्ण

		/* Create the new Rx filter list and update the same in H/W. */
		i = 0;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			mac_addr = 0;
			क्रम (j = 0; j < ETH_ALEN; j++) अणु
				mac_addr |= ha->addr[j];
				mac_addr <<= 8;
			पूर्ण
			mac_addr >>= 8;
			ग_लिखोq(RMAC_ADDR_DATA0_MEM_ADDR(mac_addr),
			       &bar0->rmac_addr_data0_mem);
			ग_लिखोq(RMAC_ADDR_DATA1_MEM_MASK(0ULL),
			       &bar0->rmac_addr_data1_mem);
			val64 = RMAC_ADDR_CMD_MEM_WE |
				RMAC_ADDR_CMD_MEM_STROBE_NEW_CMD |
				RMAC_ADDR_CMD_MEM_OFFSET
				(i + config->mc_start_offset);
			ग_लिखोq(val64, &bar0->rmac_addr_cmd_mem);

			/* Wait क्रम command completes */
			अगर (रुको_क्रम_cmd_complete(&bar0->rmac_addr_cmd_mem,
						  RMAC_ADDR_CMD_MEM_STROBE_CMD_EXECUTING,
						  S2IO_BIT_RESET, may_sleep)) अणु
				DBG_PRINT(ERR_DBG,
					  "%s: Adding Multicasts failed\n",
					  dev->name);
				वापस;
			पूर्ण
			i++;
		पूर्ण
	पूर्ण
पूर्ण

/* NDO wrapper क्रम s2io_set_multicast */
अटल व्योम s2io_nकरो_set_multicast(काष्ठा net_device *dev)
अणु
	s2io_set_multicast(dev, false);
पूर्ण

/* पढ़ो from CAM unicast & multicast addresses and store it in
 * def_mac_addr काष्ठाure
 */
अटल व्योम करो_s2io_store_unicast_mc(काष्ठा s2io_nic *sp)
अणु
	पूर्णांक offset;
	u64 mac_addr = 0x0;
	काष्ठा config_param *config = &sp->config;

	/* store unicast & multicast mac addresses */
	क्रम (offset = 0; offset < config->max_mc_addr; offset++) अणु
		mac_addr = करो_s2io_पढ़ो_unicast_mc(sp, offset);
		/* अगर पढ़ो fails disable the entry */
		अगर (mac_addr == FAILURE)
			mac_addr = S2IO_DISABLE_MAC_ENTRY;
		करो_s2io_copy_mac_addr(sp, offset, mac_addr);
	पूर्ण
पूर्ण

/* restore unicast & multicast MAC to CAM from def_mac_addr काष्ठाure */
अटल व्योम करो_s2io_restore_unicast_mc(काष्ठा s2io_nic *sp)
अणु
	पूर्णांक offset;
	काष्ठा config_param *config = &sp->config;
	/* restore unicast mac address */
	क्रम (offset = 0; offset < config->max_mac_addr; offset++)
		करो_s2io_prog_unicast(sp->dev,
				     sp->def_mac_addr[offset].mac_addr);

	/* restore multicast mac address */
	क्रम (offset = config->mc_start_offset;
	     offset < config->max_mc_addr; offset++)
		करो_s2io_add_mc(sp, sp->def_mac_addr[offset].mac_addr);
पूर्ण

/* add a multicast MAC address to CAM */
अटल पूर्णांक करो_s2io_add_mc(काष्ठा s2io_nic *sp, u8 *addr)
अणु
	पूर्णांक i;
	u64 mac_addr = 0;
	काष्ठा config_param *config = &sp->config;

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		mac_addr <<= 8;
		mac_addr |= addr[i];
	पूर्ण
	अगर ((0ULL == mac_addr) || (mac_addr == S2IO_DISABLE_MAC_ENTRY))
		वापस SUCCESS;

	/* check अगर the multicast mac alपढ़ोy preset in CAM */
	क्रम (i = config->mc_start_offset; i < config->max_mc_addr; i++) अणु
		u64 पंचांगp64;
		पंचांगp64 = करो_s2io_पढ़ो_unicast_mc(sp, i);
		अगर (पंचांगp64 == S2IO_DISABLE_MAC_ENTRY) /* CAM entry is empty */
			अवरोध;

		अगर (पंचांगp64 == mac_addr)
			वापस SUCCESS;
	पूर्ण
	अगर (i == config->max_mc_addr) अणु
		DBG_PRINT(ERR_DBG,
			  "CAM full no space left for multicast MAC\n");
		वापस FAILURE;
	पूर्ण
	/* Update the पूर्णांकernal काष्ठाure with this new mac address */
	करो_s2io_copy_mac_addr(sp, i, mac_addr);

	वापस करो_s2io_add_mac(sp, mac_addr, i);
पूर्ण

/* add MAC address to CAM */
अटल पूर्णांक करो_s2io_add_mac(काष्ठा s2io_nic *sp, u64 addr, पूर्णांक off)
अणु
	u64 val64;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;

	ग_लिखोq(RMAC_ADDR_DATA0_MEM_ADDR(addr),
	       &bar0->rmac_addr_data0_mem);

	val64 =	RMAC_ADDR_CMD_MEM_WE | RMAC_ADDR_CMD_MEM_STROBE_NEW_CMD |
		RMAC_ADDR_CMD_MEM_OFFSET(off);
	ग_लिखोq(val64, &bar0->rmac_addr_cmd_mem);

	/* Wait till command completes */
	अगर (रुको_क्रम_cmd_complete(&bar0->rmac_addr_cmd_mem,
				  RMAC_ADDR_CMD_MEM_STROBE_CMD_EXECUTING,
				  S2IO_BIT_RESET, true)) अणु
		DBG_PRINT(INFO_DBG, "do_s2io_add_mac failed\n");
		वापस FAILURE;
	पूर्ण
	वापस SUCCESS;
पूर्ण
/* deletes a specअगरied unicast/multicast mac entry from CAM */
अटल पूर्णांक करो_s2io_delete_unicast_mc(काष्ठा s2io_nic *sp, u64 addr)
अणु
	पूर्णांक offset;
	u64 dis_addr = S2IO_DISABLE_MAC_ENTRY, पंचांगp64;
	काष्ठा config_param *config = &sp->config;

	क्रम (offset = 1;
	     offset < config->max_mc_addr; offset++) अणु
		पंचांगp64 = करो_s2io_पढ़ो_unicast_mc(sp, offset);
		अगर (पंचांगp64 == addr) अणु
			/* disable the entry by writing  0xffffffffffffULL */
			अगर (करो_s2io_add_mac(sp, dis_addr, offset) ==  FAILURE)
				वापस FAILURE;
			/* store the new mac list from CAM */
			करो_s2io_store_unicast_mc(sp);
			वापस SUCCESS;
		पूर्ण
	पूर्ण
	DBG_PRINT(ERR_DBG, "MAC address 0x%llx not found in CAM\n",
		  (अचिन्हित दीर्घ दीर्घ)addr);
	वापस FAILURE;
पूर्ण

/* पढ़ो mac entries from CAM */
अटल u64 करो_s2io_पढ़ो_unicast_mc(काष्ठा s2io_nic *sp, पूर्णांक offset)
अणु
	u64 पंचांगp64, val64;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;

	/* पढ़ो mac addr */
	val64 =	RMAC_ADDR_CMD_MEM_RD | RMAC_ADDR_CMD_MEM_STROBE_NEW_CMD |
		RMAC_ADDR_CMD_MEM_OFFSET(offset);
	ग_लिखोq(val64, &bar0->rmac_addr_cmd_mem);

	/* Wait till command completes */
	अगर (रुको_क्रम_cmd_complete(&bar0->rmac_addr_cmd_mem,
				  RMAC_ADDR_CMD_MEM_STROBE_CMD_EXECUTING,
				  S2IO_BIT_RESET, true)) अणु
		DBG_PRINT(INFO_DBG, "do_s2io_read_unicast_mc failed\n");
		वापस FAILURE;
	पूर्ण
	पंचांगp64 = पढ़ोq(&bar0->rmac_addr_data0_mem);

	वापस पंचांगp64 >> 16;
पूर्ण

/*
 * s2io_set_mac_addr - driver entry poपूर्णांक
 */

अटल पूर्णांक s2io_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	/* store the MAC address in CAM */
	वापस करो_s2io_prog_unicast(dev, dev->dev_addr);
पूर्ण
/**
 *  करो_s2io_prog_unicast - Programs the Xframe mac address
 *  @dev : poपूर्णांकer to the device काष्ठाure.
 *  @addr: a uअक्षर poपूर्णांकer to the new mac address which is to be set.
 *  Description : This procedure will program the Xframe to receive
 *  frames with new Mac Address
 *  Return value: SUCCESS on success and an appropriate (-)ve पूर्णांकeger
 *  as defined in त्रुटिसं.स file on failure.
 */

अटल पूर्णांक करो_s2io_prog_unicast(काष्ठा net_device *dev, u8 *addr)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	रेजिस्टर u64 mac_addr = 0, perm_addr = 0;
	पूर्णांक i;
	u64 पंचांगp64;
	काष्ठा config_param *config = &sp->config;

	/*
	 * Set the new MAC address as the new unicast filter and reflect this
	 * change on the device address रेजिस्टरed with the OS. It will be
	 * at offset 0.
	 */
	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		mac_addr <<= 8;
		mac_addr |= addr[i];
		perm_addr <<= 8;
		perm_addr |= sp->def_mac_addr[0].mac_addr[i];
	पूर्ण

	/* check अगर the dev_addr is dअगरferent than perm_addr */
	अगर (mac_addr == perm_addr)
		वापस SUCCESS;

	/* check अगर the mac alपढ़ोy preset in CAM */
	क्रम (i = 1; i < config->max_mac_addr; i++) अणु
		पंचांगp64 = करो_s2io_पढ़ो_unicast_mc(sp, i);
		अगर (पंचांगp64 == S2IO_DISABLE_MAC_ENTRY) /* CAM entry is empty */
			अवरोध;

		अगर (पंचांगp64 == mac_addr) अणु
			DBG_PRINT(INFO_DBG,
				  "MAC addr:0x%llx already present in CAM\n",
				  (अचिन्हित दीर्घ दीर्घ)mac_addr);
			वापस SUCCESS;
		पूर्ण
	पूर्ण
	अगर (i == config->max_mac_addr) अणु
		DBG_PRINT(ERR_DBG, "CAM full no space left for Unicast MAC\n");
		वापस FAILURE;
	पूर्ण
	/* Update the पूर्णांकernal काष्ठाure with this new mac address */
	करो_s2io_copy_mac_addr(sp, i, mac_addr);

	वापस करो_s2io_add_mac(sp, mac_addr, i);
पूर्ण

/**
 * s2io_ethtool_set_link_ksettings - Sets dअगरferent link parameters.
 * @dev : poपूर्णांकer to netdev
 * @cmd: poपूर्णांकer to the काष्ठाure with parameters given by ethtool to set
 * link inक्रमmation.
 * Description:
 * The function sets dअगरferent link parameters provided by the user onto
 * the NIC.
 * Return value:
 * 0 on success.
 */

अटल पूर्णांक
s2io_ethtool_set_link_ksettings(काष्ठा net_device *dev,
				स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	अगर ((cmd->base.स्वतःneg == AUTONEG_ENABLE) ||
	    (cmd->base.speed != SPEED_10000) ||
	    (cmd->base.duplex != DUPLEX_FULL))
		वापस -EINVAL;
	अन्यथा अणु
		s2io_बंद(sp->dev);
		s2io_खोलो(sp->dev);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * s2io_ethtol_get_link_ksettings - Return link specअगरic inक्रमmation.
 * @dev: poपूर्णांकer to netdev
 * @cmd : poपूर्णांकer to the काष्ठाure with parameters given by ethtool
 * to वापस link inक्रमmation.
 * Description:
 * Returns link specअगरic inक्रमmation like speed, duplex etc.. to ethtool.
 * Return value :
 * वापस 0 on success.
 */

अटल पूर्णांक
s2io_ethtool_get_link_ksettings(काष्ठा net_device *dev,
				काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);

	ethtool_link_ksettings_zero_link_mode(cmd, advertising);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, 10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, FIBRE);

	cmd->base.port = PORT_FIBRE;

	अगर (netअगर_carrier_ok(sp->dev)) अणु
		cmd->base.speed = SPEED_10000;
		cmd->base.duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	cmd->base.स्वतःneg = AUTONEG_DISABLE;
	वापस 0;
पूर्ण

/**
 * s2io_ethtool_gdrvinfo - Returns driver specअगरic inक्रमmation.
 * @dev: poपूर्णांकer to netdev
 * @info : poपूर्णांकer to the काष्ठाure with parameters given by ethtool to
 * वापस driver inक्रमmation.
 * Description:
 * Returns driver specefic inक्रमmation like name, version etc.. to ethtool.
 * Return value:
 *  व्योम
 */

अटल व्योम s2io_ethtool_gdrvinfo(काष्ठा net_device *dev,
				  काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);

	strlcpy(info->driver, s2io_driver_name, माप(info->driver));
	strlcpy(info->version, s2io_driver_version, माप(info->version));
	strlcpy(info->bus_info, pci_name(sp->pdev), माप(info->bus_info));
पूर्ण

/**
 *  s2io_ethtool_gregs - dumps the entire space of Xfame पूर्णांकo the buffer.
 *  @dev: poपूर्णांकer to netdev
 *  @regs : poपूर्णांकer to the काष्ठाure with parameters given by ethtool क्रम
 *          dumping the रेजिस्टरs.
 *  @space: The input argument पूर्णांकo which all the रेजिस्टरs are dumped.
 *  Description:
 *  Dumps the entire रेजिस्टर space of xFrame NIC पूर्णांकo the user given
 *  buffer area.
 * Return value :
 * व्योम .
 */

अटल व्योम s2io_ethtool_gregs(काष्ठा net_device *dev,
			       काष्ठा ethtool_regs *regs, व्योम *space)
अणु
	पूर्णांक i;
	u64 reg;
	u8 *reg_space = (u8 *)space;
	काष्ठा s2io_nic *sp = netdev_priv(dev);

	regs->len = XENA_REG_SPACE;
	regs->version = sp->pdev->subप्रणाली_device;

	क्रम (i = 0; i < regs->len; i += 8) अणु
		reg = पढ़ोq(sp->bar0 + i);
		स_नकल((reg_space + i), &reg, 8);
	पूर्ण
पूर्ण

/*
 *  s2io_set_led - control NIC led
 */
अटल व्योम s2io_set_led(काष्ठा s2io_nic *sp, bool on)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u16 subid = sp->pdev->subप्रणाली_device;
	u64 val64;

	अगर ((sp->device_type == XFRAME_II_DEVICE) ||
	    ((subid & 0xFF) >= 0x07)) अणु
		val64 = पढ़ोq(&bar0->gpio_control);
		अगर (on)
			val64 |= GPIO_CTRL_GPIO_0;
		अन्यथा
			val64 &= ~GPIO_CTRL_GPIO_0;

		ग_लिखोq(val64, &bar0->gpio_control);
	पूर्ण अन्यथा अणु
		val64 = पढ़ोq(&bar0->adapter_control);
		अगर (on)
			val64 |= ADAPTER_LED_ON;
		अन्यथा
			val64 &= ~ADAPTER_LED_ON;

		ग_लिखोq(val64, &bar0->adapter_control);
	पूर्ण

पूर्ण

/**
 * s2io_ethtool_set_led - To physically identअगरy the nic on the प्रणाली.
 * @dev : network device
 * @state: led setting
 *
 * Description: Used to physically identअगरy the NIC on the प्रणाली.
 * The Link LED will blink क्रम a समय specअगरied by the user क्रम
 * identअगरication.
 * NOTE: The Link has to be Up to be able to blink the LED. Hence
 * identअगरication is possible only अगर it's link is up.
 */

अटल पूर्णांक s2io_ethtool_set_led(काष्ठा net_device *dev,
				क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u16 subid = sp->pdev->subप्रणाली_device;

	अगर ((sp->device_type == XFRAME_I_DEVICE) && ((subid & 0xFF) < 0x07)) अणु
		u64 val64 = पढ़ोq(&bar0->adapter_control);
		अगर (!(val64 & ADAPTER_CNTL_EN)) अणु
			pr_err("Adapter Link down, cannot blink LED\n");
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		sp->adapt_ctrl_org = पढ़ोq(&bar0->gpio_control);
		वापस 1;	/* cycle on/off once per second */

	हाल ETHTOOL_ID_ON:
		s2io_set_led(sp, true);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		s2io_set_led(sp, false);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		अगर (CARDS_WITH_FAULTY_LINK_INDICATORS(sp->device_type, subid))
			ग_लिखोq(sp->adapt_ctrl_org, &bar0->gpio_control);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम s2io_ethtool_gringparam(काष्ठा net_device *dev,
				    काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	पूर्णांक i, tx_desc_count = 0, rx_desc_count = 0;

	अगर (sp->rxd_mode == RXD_MODE_1) अणु
		ering->rx_max_pending = MAX_RX_DESC_1;
		ering->rx_jumbo_max_pending = MAX_RX_DESC_1;
	पूर्ण अन्यथा अणु
		ering->rx_max_pending = MAX_RX_DESC_2;
		ering->rx_jumbo_max_pending = MAX_RX_DESC_2;
	पूर्ण

	ering->tx_max_pending = MAX_TX_DESC;

	क्रम (i = 0; i < sp->config.rx_ring_num; i++)
		rx_desc_count += sp->config.rx_cfg[i].num_rxd;
	ering->rx_pending = rx_desc_count;
	ering->rx_jumbo_pending = rx_desc_count;

	क्रम (i = 0; i < sp->config.tx_fअगरo_num; i++)
		tx_desc_count += sp->config.tx_cfg[i].fअगरo_len;
	ering->tx_pending = tx_desc_count;
	DBG_PRINT(INFO_DBG, "max txds: %d\n", sp->config.max_txds);
पूर्ण

/**
 * s2io_ethtool_getछोड़ो_data -Pause frame frame generation and reception.
 * @dev: poपूर्णांकer to netdev
 * @ep : poपूर्णांकer to the काष्ठाure with छोड़ो parameters given by ethtool.
 * Description:
 * Returns the Pause frame generation and reception capability of the NIC.
 * Return value:
 *  व्योम
 */
अटल व्योम s2io_ethtool_getछोड़ो_data(काष्ठा net_device *dev,
				       काष्ठा ethtool_छोड़ोparam *ep)
अणु
	u64 val64;
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;

	val64 = पढ़ोq(&bar0->rmac_छोड़ो_cfg);
	अगर (val64 & RMAC_PAUSE_GEN_ENABLE)
		ep->tx_छोड़ो = true;
	अगर (val64 & RMAC_PAUSE_RX_ENABLE)
		ep->rx_छोड़ो = true;
	ep->स्वतःneg = false;
पूर्ण

/**
 * s2io_ethtool_setछोड़ो_data -  set/reset छोड़ो frame generation.
 * @dev: poपूर्णांकer to netdev
 * @ep : poपूर्णांकer to the काष्ठाure with छोड़ो parameters given by ethtool.
 * Description:
 * It can be used to set or reset Pause frame generation or reception
 * support of the NIC.
 * Return value:
 * पूर्णांक, वापसs 0 on Success
 */

अटल पूर्णांक s2io_ethtool_setछोड़ो_data(काष्ठा net_device *dev,
				      काष्ठा ethtool_छोड़ोparam *ep)
अणु
	u64 val64;
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;

	val64 = पढ़ोq(&bar0->rmac_छोड़ो_cfg);
	अगर (ep->tx_छोड़ो)
		val64 |= RMAC_PAUSE_GEN_ENABLE;
	अन्यथा
		val64 &= ~RMAC_PAUSE_GEN_ENABLE;
	अगर (ep->rx_छोड़ो)
		val64 |= RMAC_PAUSE_RX_ENABLE;
	अन्यथा
		val64 &= ~RMAC_PAUSE_RX_ENABLE;
	ग_लिखोq(val64, &bar0->rmac_छोड़ो_cfg);
	वापस 0;
पूर्ण

#घोषणा S2IO_DEV_ID		5
/**
 * पढ़ो_eeprom - पढ़ोs 4 bytes of data from user given offset.
 * @sp : निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 *      s2io_nic काष्ठाure.
 * @off : offset at which the data must be written
 * @data : Its an output parameter where the data पढ़ो at the given
 *	offset is stored.
 * Description:
 * Will पढ़ो 4 bytes of data from the user given offset and वापस the
 * पढ़ो data.
 * NOTE: Will allow to पढ़ो only part of the EEPROM visible through the
 *   I2C bus.
 * Return value:
 *  -1 on failure and 0 on success.
 */
अटल पूर्णांक पढ़ो_eeprom(काष्ठा s2io_nic *sp, पूर्णांक off, u64 *data)
अणु
	पूर्णांक ret = -1;
	u32 निकास_cnt = 0;
	u64 val64;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;

	अगर (sp->device_type == XFRAME_I_DEVICE) अणु
		val64 = I2C_CONTROL_DEV_ID(S2IO_DEV_ID) |
			I2C_CONTROL_ADDR(off) |
			I2C_CONTROL_BYTE_CNT(0x3) |
			I2C_CONTROL_READ |
			I2C_CONTROL_CNTL_START;
		SPECIAL_REG_WRITE(val64, &bar0->i2c_control, LF);

		जबतक (निकास_cnt < 5) अणु
			val64 = पढ़ोq(&bar0->i2c_control);
			अगर (I2C_CONTROL_CNTL_END(val64)) अणु
				*data = I2C_CONTROL_GET_DATA(val64);
				ret = 0;
				अवरोध;
			पूर्ण
			msleep(50);
			निकास_cnt++;
		पूर्ण
	पूर्ण

	अगर (sp->device_type == XFRAME_II_DEVICE) अणु
		val64 = SPI_CONTROL_KEY(0x9) | SPI_CONTROL_SEL1 |
			SPI_CONTROL_BYTECNT(0x3) |
			SPI_CONTROL_CMD(0x3) | SPI_CONTROL_ADDR(off);
		SPECIAL_REG_WRITE(val64, &bar0->spi_control, LF);
		val64 |= SPI_CONTROL_REQ;
		SPECIAL_REG_WRITE(val64, &bar0->spi_control, LF);
		जबतक (निकास_cnt < 5) अणु
			val64 = पढ़ोq(&bar0->spi_control);
			अगर (val64 & SPI_CONTROL_NACK) अणु
				ret = 1;
				अवरोध;
			पूर्ण अन्यथा अगर (val64 & SPI_CONTROL_DONE) अणु
				*data = पढ़ोq(&bar0->spi_data);
				*data &= 0xffffff;
				ret = 0;
				अवरोध;
			पूर्ण
			msleep(50);
			निकास_cnt++;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 *  ग_लिखो_eeprom - actually ग_लिखोs the relevant part of the data value.
 *  @sp : निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 *       s2io_nic काष्ठाure.
 *  @off : offset at which the data must be written
 *  @data : The data that is to be written
 *  @cnt : Number of bytes of the data that are actually to be written पूर्णांकo
 *  the Eeprom. (max of 3)
 * Description:
 *  Actually ग_लिखोs the relevant part of the data value पूर्णांकo the Eeprom
 *  through the I2C bus.
 * Return value:
 *  0 on success, -1 on failure.
 */

अटल पूर्णांक ग_लिखो_eeprom(काष्ठा s2io_nic *sp, पूर्णांक off, u64 data, पूर्णांक cnt)
अणु
	पूर्णांक निकास_cnt = 0, ret = -1;
	u64 val64;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;

	अगर (sp->device_type == XFRAME_I_DEVICE) अणु
		val64 = I2C_CONTROL_DEV_ID(S2IO_DEV_ID) |
			I2C_CONTROL_ADDR(off) |
			I2C_CONTROL_BYTE_CNT(cnt) |
			I2C_CONTROL_SET_DATA((u32)data) |
			I2C_CONTROL_CNTL_START;
		SPECIAL_REG_WRITE(val64, &bar0->i2c_control, LF);

		जबतक (निकास_cnt < 5) अणु
			val64 = पढ़ोq(&bar0->i2c_control);
			अगर (I2C_CONTROL_CNTL_END(val64)) अणु
				अगर (!(val64 & I2C_CONTROL_NACK))
					ret = 0;
				अवरोध;
			पूर्ण
			msleep(50);
			निकास_cnt++;
		पूर्ण
	पूर्ण

	अगर (sp->device_type == XFRAME_II_DEVICE) अणु
		पूर्णांक ग_लिखो_cnt = (cnt == 8) ? 0 : cnt;
		ग_लिखोq(SPI_DATA_WRITE(data, (cnt << 3)), &bar0->spi_data);

		val64 = SPI_CONTROL_KEY(0x9) | SPI_CONTROL_SEL1 |
			SPI_CONTROL_BYTECNT(ग_लिखो_cnt) |
			SPI_CONTROL_CMD(0x2) | SPI_CONTROL_ADDR(off);
		SPECIAL_REG_WRITE(val64, &bar0->spi_control, LF);
		val64 |= SPI_CONTROL_REQ;
		SPECIAL_REG_WRITE(val64, &bar0->spi_control, LF);
		जबतक (निकास_cnt < 5) अणु
			val64 = पढ़ोq(&bar0->spi_control);
			अगर (val64 & SPI_CONTROL_NACK) अणु
				ret = 1;
				अवरोध;
			पूर्ण अन्यथा अगर (val64 & SPI_CONTROL_DONE) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			msleep(50);
			निकास_cnt++;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
अटल व्योम s2io_vpd_पढ़ो(काष्ठा s2io_nic *nic)
अणु
	u8 *vpd_data;
	u8 data;
	पूर्णांक i = 0, cnt, len, fail = 0;
	पूर्णांक vpd_addr = 0x80;
	काष्ठा swStat *swstats = &nic->mac_control.stats_info->sw_stat;

	अगर (nic->device_type == XFRAME_II_DEVICE) अणु
		म_नकल(nic->product_name, "Xframe II 10GbE network adapter");
		vpd_addr = 0x80;
	पूर्ण अन्यथा अणु
		म_नकल(nic->product_name, "Xframe I 10GbE network adapter");
		vpd_addr = 0x50;
	पूर्ण
	म_नकल(nic->serial_num, "NOT AVAILABLE");

	vpd_data = kदो_स्मृति(256, GFP_KERNEL);
	अगर (!vpd_data) अणु
		swstats->mem_alloc_fail_cnt++;
		वापस;
	पूर्ण
	swstats->mem_allocated += 256;

	क्रम (i = 0; i < 256; i += 4) अणु
		pci_ग_लिखो_config_byte(nic->pdev, (vpd_addr + 2), i);
		pci_पढ़ो_config_byte(nic->pdev,  (vpd_addr + 2), &data);
		pci_ग_लिखो_config_byte(nic->pdev, (vpd_addr + 3), 0);
		क्रम (cnt = 0; cnt < 5; cnt++) अणु
			msleep(2);
			pci_पढ़ो_config_byte(nic->pdev, (vpd_addr + 3), &data);
			अगर (data == 0x80)
				अवरोध;
		पूर्ण
		अगर (cnt >= 5) अणु
			DBG_PRINT(ERR_DBG, "Read of VPD data failed\n");
			fail = 1;
			अवरोध;
		पूर्ण
		pci_पढ़ो_config_dword(nic->pdev,  (vpd_addr + 4),
				      (u32 *)&vpd_data[i]);
	पूर्ण

	अगर (!fail) अणु
		/* पढ़ो serial number of adapter */
		क्रम (cnt = 0; cnt < 252; cnt++) अणु
			अगर ((vpd_data[cnt] == 'S') &&
			    (vpd_data[cnt+1] == 'N')) अणु
				len = vpd_data[cnt+2];
				अगर (len < min(VPD_STRING_LEN, 256-cnt-2)) अणु
					स_नकल(nic->serial_num,
					       &vpd_data[cnt + 3],
					       len);
					स_रखो(nic->serial_num+len,
					       0,
					       VPD_STRING_LEN-len);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((!fail) && (vpd_data[1] < VPD_STRING_LEN)) अणु
		len = vpd_data[1];
		स_नकल(nic->product_name, &vpd_data[3], len);
		nic->product_name[len] = 0;
	पूर्ण
	kमुक्त(vpd_data);
	swstats->mem_मुक्तd += 256;
पूर्ण

/**
 *  s2io_ethtool_geeprom  - पढ़ोs the value stored in the Eeprom.
 *  @dev: poपूर्णांकer to netdev
 *  @eeprom : poपूर्णांकer to the user level काष्ठाure provided by ethtool,
 *  containing all relevant inक्रमmation.
 *  @data_buf : user defined value to be written पूर्णांकo Eeprom.
 *  Description: Reads the values stored in the Eeprom at given offset
 *  क्रम a given length. Stores these values पूर्णांक the input argument data
 *  buffer 'data_buf' and वापसs these to the caller (ethtool.)
 *  Return value:
 *  पूर्णांक  0 on success
 */

अटल पूर्णांक s2io_ethtool_geeprom(काष्ठा net_device *dev,
				काष्ठा ethtool_eeprom *eeprom, u8 * data_buf)
अणु
	u32 i, valid;
	u64 data;
	काष्ठा s2io_nic *sp = netdev_priv(dev);

	eeprom->magic = sp->pdev->venकरोr | (sp->pdev->device << 16);

	अगर ((eeprom->offset + eeprom->len) > (XENA_EEPROM_SPACE))
		eeprom->len = XENA_EEPROM_SPACE - eeprom->offset;

	क्रम (i = 0; i < eeprom->len; i += 4) अणु
		अगर (पढ़ो_eeprom(sp, (eeprom->offset + i), &data)) अणु
			DBG_PRINT(ERR_DBG, "Read of EEPROM failed\n");
			वापस -EFAULT;
		पूर्ण
		valid = INV(data);
		स_नकल((data_buf + i), &valid, 4);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *  s2io_ethtool_seeprom - tries to ग_लिखो the user provided value in Eeprom
 *  @dev: poपूर्णांकer to netdev
 *  @eeprom : poपूर्णांकer to the user level काष्ठाure provided by ethtool,
 *  containing all relevant inक्रमmation.
 *  @data_buf : user defined value to be written पूर्णांकo Eeprom.
 *  Description:
 *  Tries to ग_लिखो the user provided value in the Eeprom, at the offset
 *  given by the user.
 *  Return value:
 *  0 on success, -EFAULT on failure.
 */

अटल पूर्णांक s2io_ethtool_seeprom(काष्ठा net_device *dev,
				काष्ठा ethtool_eeprom *eeprom,
				u8 *data_buf)
अणु
	पूर्णांक len = eeprom->len, cnt = 0;
	u64 valid = 0, data;
	काष्ठा s2io_nic *sp = netdev_priv(dev);

	अगर (eeprom->magic != (sp->pdev->venकरोr | (sp->pdev->device << 16))) अणु
		DBG_PRINT(ERR_DBG,
			  "ETHTOOL_WRITE_EEPROM Err: "
			  "Magic value is wrong, it is 0x%x should be 0x%x\n",
			  (sp->pdev->venकरोr | (sp->pdev->device << 16)),
			  eeprom->magic);
		वापस -EFAULT;
	पूर्ण

	जबतक (len) अणु
		data = (u32)data_buf[cnt] & 0x000000FF;
		अगर (data)
			valid = (u32)(data << 24);
		अन्यथा
			valid = data;

		अगर (ग_लिखो_eeprom(sp, (eeprom->offset + cnt), valid, 0)) अणु
			DBG_PRINT(ERR_DBG,
				  "ETHTOOL_WRITE_EEPROM Err: "
				  "Cannot write into the specified offset\n");
			वापस -EFAULT;
		पूर्ण
		cnt++;
		len--;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * s2io_रेजिस्टर_test - पढ़ोs and ग_लिखोs पूर्णांकo all घड़ी करोमुख्यs.
 * @sp : निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 * s2io_nic काष्ठाure.
 * @data : variable that वापसs the result of each of the test conducted b
 * by the driver.
 * Description:
 * Read and ग_लिखो पूर्णांकo all घड़ी करोमुख्यs. The NIC has 3 घड़ी करोमुख्यs,
 * see that रेजिस्टरs in all the three regions are accessible.
 * Return value:
 * 0 on success.
 */

अटल पूर्णांक s2io_रेजिस्टर_test(काष्ठा s2io_nic *sp, uपूर्णांक64_t *data)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64 = 0, exp_val;
	पूर्णांक fail = 0;

	val64 = पढ़ोq(&bar0->pअगर_rd_swapper_fb);
	अगर (val64 != 0x123456789abcdefULL) अणु
		fail = 1;
		DBG_PRINT(INFO_DBG, "Read Test level %d fails\n", 1);
	पूर्ण

	val64 = पढ़ोq(&bar0->rmac_छोड़ो_cfg);
	अगर (val64 != 0xc000ffff00000000ULL) अणु
		fail = 1;
		DBG_PRINT(INFO_DBG, "Read Test level %d fails\n", 2);
	पूर्ण

	val64 = पढ़ोq(&bar0->rx_queue_cfg);
	अगर (sp->device_type == XFRAME_II_DEVICE)
		exp_val = 0x0404040404040404ULL;
	अन्यथा
		exp_val = 0x0808080808080808ULL;
	अगर (val64 != exp_val) अणु
		fail = 1;
		DBG_PRINT(INFO_DBG, "Read Test level %d fails\n", 3);
	पूर्ण

	val64 = पढ़ोq(&bar0->xgxs_efअगरo_cfg);
	अगर (val64 != 0x000000001923141EULL) अणु
		fail = 1;
		DBG_PRINT(INFO_DBG, "Read Test level %d fails\n", 4);
	पूर्ण

	val64 = 0x5A5A5A5A5A5A5A5AULL;
	ग_लिखोq(val64, &bar0->xmsi_data);
	val64 = पढ़ोq(&bar0->xmsi_data);
	अगर (val64 != 0x5A5A5A5A5A5A5A5AULL) अणु
		fail = 1;
		DBG_PRINT(ERR_DBG, "Write Test level %d fails\n", 1);
	पूर्ण

	val64 = 0xA5A5A5A5A5A5A5A5ULL;
	ग_लिखोq(val64, &bar0->xmsi_data);
	val64 = पढ़ोq(&bar0->xmsi_data);
	अगर (val64 != 0xA5A5A5A5A5A5A5A5ULL) अणु
		fail = 1;
		DBG_PRINT(ERR_DBG, "Write Test level %d fails\n", 2);
	पूर्ण

	*data = fail;
	वापस fail;
पूर्ण

/**
 * s2io_eeprom_test - to verअगरy that EEprom in the xena can be programmed.
 * @sp : निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 * s2io_nic काष्ठाure.
 * @data:variable that वापसs the result of each of the test conducted by
 * the driver.
 * Description:
 * Verअगरy that EEPROM in the xena can be programmed using I2C_CONTROL
 * रेजिस्टर.
 * Return value:
 * 0 on success.
 */

अटल पूर्णांक s2io_eeprom_test(काष्ठा s2io_nic *sp, uपूर्णांक64_t *data)
अणु
	पूर्णांक fail = 0;
	u64 ret_data, org_4F0, org_7F0;
	u8 saved_4F0 = 0, saved_7F0 = 0;
	काष्ठा net_device *dev = sp->dev;

	/* Test Write Error at offset 0 */
	/* Note that SPI पूर्णांकerface allows ग_लिखो access to all areas
	 * of EEPROM. Hence करोing all negative testing only क्रम Xframe I.
	 */
	अगर (sp->device_type == XFRAME_I_DEVICE)
		अगर (!ग_लिखो_eeprom(sp, 0, 0, 3))
			fail = 1;

	/* Save current values at offsets 0x4F0 and 0x7F0 */
	अगर (!पढ़ो_eeprom(sp, 0x4F0, &org_4F0))
		saved_4F0 = 1;
	अगर (!पढ़ो_eeprom(sp, 0x7F0, &org_7F0))
		saved_7F0 = 1;

	/* Test Write at offset 4f0 */
	अगर (ग_लिखो_eeprom(sp, 0x4F0, 0x012345, 3))
		fail = 1;
	अगर (पढ़ो_eeprom(sp, 0x4F0, &ret_data))
		fail = 1;

	अगर (ret_data != 0x012345) अणु
		DBG_PRINT(ERR_DBG, "%s: eeprom test error at offset 0x4F0. "
			  "Data written %llx Data read %llx\n",
			  dev->name, (अचिन्हित दीर्घ दीर्घ)0x12345,
			  (अचिन्हित दीर्घ दीर्घ)ret_data);
		fail = 1;
	पूर्ण

	/* Reset the EEPROM data go FFFF */
	ग_लिखो_eeprom(sp, 0x4F0, 0xFFFFFF, 3);

	/* Test Write Request Error at offset 0x7c */
	अगर (sp->device_type == XFRAME_I_DEVICE)
		अगर (!ग_लिखो_eeprom(sp, 0x07C, 0, 3))
			fail = 1;

	/* Test Write Request at offset 0x7f0 */
	अगर (ग_लिखो_eeprom(sp, 0x7F0, 0x012345, 3))
		fail = 1;
	अगर (पढ़ो_eeprom(sp, 0x7F0, &ret_data))
		fail = 1;

	अगर (ret_data != 0x012345) अणु
		DBG_PRINT(ERR_DBG, "%s: eeprom test error at offset 0x7F0. "
			  "Data written %llx Data read %llx\n",
			  dev->name, (अचिन्हित दीर्घ दीर्घ)0x12345,
			  (अचिन्हित दीर्घ दीर्घ)ret_data);
		fail = 1;
	पूर्ण

	/* Reset the EEPROM data go FFFF */
	ग_लिखो_eeprom(sp, 0x7F0, 0xFFFFFF, 3);

	अगर (sp->device_type == XFRAME_I_DEVICE) अणु
		/* Test Write Error at offset 0x80 */
		अगर (!ग_लिखो_eeprom(sp, 0x080, 0, 3))
			fail = 1;

		/* Test Write Error at offset 0xfc */
		अगर (!ग_लिखो_eeprom(sp, 0x0FC, 0, 3))
			fail = 1;

		/* Test Write Error at offset 0x100 */
		अगर (!ग_लिखो_eeprom(sp, 0x100, 0, 3))
			fail = 1;

		/* Test Write Error at offset 4ec */
		अगर (!ग_लिखो_eeprom(sp, 0x4EC, 0, 3))
			fail = 1;
	पूर्ण

	/* Restore values at offsets 0x4F0 and 0x7F0 */
	अगर (saved_4F0)
		ग_लिखो_eeprom(sp, 0x4F0, org_4F0, 3);
	अगर (saved_7F0)
		ग_लिखो_eeprom(sp, 0x7F0, org_7F0, 3);

	*data = fail;
	वापस fail;
पूर्ण

/**
 * s2io_bist_test - invokes the MemBist test of the card .
 * @sp : निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 * s2io_nic काष्ठाure.
 * @data:variable that वापसs the result of each of the test conducted by
 * the driver.
 * Description:
 * This invokes the MemBist test of the card. We give around
 * 2 secs समय क्रम the Test to complete. If it's still not complete
 * within this peiod, we consider that the test failed.
 * Return value:
 * 0 on success and -1 on failure.
 */

अटल पूर्णांक s2io_bist_test(काष्ठा s2io_nic *sp, uपूर्णांक64_t *data)
अणु
	u8 bist = 0;
	पूर्णांक cnt = 0, ret = -1;

	pci_पढ़ो_config_byte(sp->pdev, PCI_BIST, &bist);
	bist |= PCI_BIST_START;
	pci_ग_लिखो_config_word(sp->pdev, PCI_BIST, bist);

	जबतक (cnt < 20) अणु
		pci_पढ़ो_config_byte(sp->pdev, PCI_BIST, &bist);
		अगर (!(bist & PCI_BIST_START)) अणु
			*data = (bist & PCI_BIST_CODE_MASK);
			ret = 0;
			अवरोध;
		पूर्ण
		msleep(100);
		cnt++;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * s2io_link_test - verअगरies the link state of the nic
 * @sp: निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 * s2io_nic काष्ठाure.
 * @data: variable that वापसs the result of each of the test conducted by
 * the driver.
 * Description:
 * The function verअगरies the link state of the NIC and updates the input
 * argument 'data' appropriately.
 * Return value:
 * 0 on success.
 */

अटल पूर्णांक s2io_link_test(काष्ठा s2io_nic *sp, uपूर्णांक64_t *data)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64;

	val64 = पढ़ोq(&bar0->adapter_status);
	अगर (!(LINK_IS_UP(val64)))
		*data = 1;
	अन्यथा
		*data = 0;

	वापस *data;
पूर्ण

/**
 * s2io_rldram_test - offline test क्रम access to the RldRam chip on the NIC
 * @sp: निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 * s2io_nic काष्ठाure.
 * @data: variable that वापसs the result of each of the test
 * conducted by the driver.
 * Description:
 *  This is one of the offline test that tests the पढ़ो and ग_लिखो
 *  access to the RldRam chip on the NIC.
 * Return value:
 *  0 on success.
 */

अटल पूर्णांक s2io_rldram_test(काष्ठा s2io_nic *sp, uपूर्णांक64_t *data)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64;
	पूर्णांक cnt, iteration = 0, test_fail = 0;

	val64 = पढ़ोq(&bar0->adapter_control);
	val64 &= ~ADAPTER_ECC_EN;
	ग_लिखोq(val64, &bar0->adapter_control);

	val64 = पढ़ोq(&bar0->mc_rldram_test_ctrl);
	val64 |= MC_RLDRAM_TEST_MODE;
	SPECIAL_REG_WRITE(val64, &bar0->mc_rldram_test_ctrl, LF);

	val64 = पढ़ोq(&bar0->mc_rldram_mrs);
	val64 |= MC_RLDRAM_QUEUE_SIZE_ENABLE;
	SPECIAL_REG_WRITE(val64, &bar0->mc_rldram_mrs, UF);

	val64 |= MC_RLDRAM_MRS_ENABLE;
	SPECIAL_REG_WRITE(val64, &bar0->mc_rldram_mrs, UF);

	जबतक (iteration < 2) अणु
		val64 = 0x55555555aaaa0000ULL;
		अगर (iteration == 1)
			val64 ^= 0xFFFFFFFFFFFF0000ULL;
		ग_लिखोq(val64, &bar0->mc_rldram_test_d0);

		val64 = 0xaaaa5a5555550000ULL;
		अगर (iteration == 1)
			val64 ^= 0xFFFFFFFFFFFF0000ULL;
		ग_लिखोq(val64, &bar0->mc_rldram_test_d1);

		val64 = 0x55aaaaaaaa5a0000ULL;
		अगर (iteration == 1)
			val64 ^= 0xFFFFFFFFFFFF0000ULL;
		ग_लिखोq(val64, &bar0->mc_rldram_test_d2);

		val64 = (u64) (0x0000003ffffe0100ULL);
		ग_लिखोq(val64, &bar0->mc_rldram_test_add);

		val64 = MC_RLDRAM_TEST_MODE |
			MC_RLDRAM_TEST_WRITE |
			MC_RLDRAM_TEST_GO;
		SPECIAL_REG_WRITE(val64, &bar0->mc_rldram_test_ctrl, LF);

		क्रम (cnt = 0; cnt < 5; cnt++) अणु
			val64 = पढ़ोq(&bar0->mc_rldram_test_ctrl);
			अगर (val64 & MC_RLDRAM_TEST_DONE)
				अवरोध;
			msleep(200);
		पूर्ण

		अगर (cnt == 5)
			अवरोध;

		val64 = MC_RLDRAM_TEST_MODE | MC_RLDRAM_TEST_GO;
		SPECIAL_REG_WRITE(val64, &bar0->mc_rldram_test_ctrl, LF);

		क्रम (cnt = 0; cnt < 5; cnt++) अणु
			val64 = पढ़ोq(&bar0->mc_rldram_test_ctrl);
			अगर (val64 & MC_RLDRAM_TEST_DONE)
				अवरोध;
			msleep(500);
		पूर्ण

		अगर (cnt == 5)
			अवरोध;

		val64 = पढ़ोq(&bar0->mc_rldram_test_ctrl);
		अगर (!(val64 & MC_RLDRAM_TEST_PASS))
			test_fail = 1;

		iteration++;
	पूर्ण

	*data = test_fail;

	/* Bring the adapter out of test mode */
	SPECIAL_REG_WRITE(0, &bar0->mc_rldram_test_ctrl, LF);

	वापस test_fail;
पूर्ण

/**
 *  s2io_ethtool_test - conducts 6 tsets to determine the health of card.
 *  @dev: poपूर्णांकer to netdev
 *  @ethtest : poपूर्णांकer to a ethtool command specअगरic काष्ठाure that will be
 *  वापसed to the user.
 *  @data : variable that वापसs the result of each of the test
 * conducted by the driver.
 * Description:
 *  This function conducts 6 tests ( 4 offline and 2 online) to determine
 *  the health of the card.
 * Return value:
 *  व्योम
 */

अटल व्योम s2io_ethtool_test(काष्ठा net_device *dev,
			      काष्ठा ethtool_test *ethtest,
			      uपूर्णांक64_t *data)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	पूर्णांक orig_state = netअगर_running(sp->dev);

	अगर (ethtest->flags == ETH_TEST_FL_OFFLINE) अणु
		/* Offline Tests. */
		अगर (orig_state)
			s2io_बंद(sp->dev);

		अगर (s2io_रेजिस्टर_test(sp, &data[0]))
			ethtest->flags |= ETH_TEST_FL_FAILED;

		s2io_reset(sp);

		अगर (s2io_rldram_test(sp, &data[3]))
			ethtest->flags |= ETH_TEST_FL_FAILED;

		s2io_reset(sp);

		अगर (s2io_eeprom_test(sp, &data[1]))
			ethtest->flags |= ETH_TEST_FL_FAILED;

		अगर (s2io_bist_test(sp, &data[4]))
			ethtest->flags |= ETH_TEST_FL_FAILED;

		अगर (orig_state)
			s2io_खोलो(sp->dev);

		data[2] = 0;
	पूर्ण अन्यथा अणु
		/* Online Tests. */
		अगर (!orig_state) अणु
			DBG_PRINT(ERR_DBG, "%s: is not up, cannot run test\n",
				  dev->name);
			data[0] = -1;
			data[1] = -1;
			data[2] = -1;
			data[3] = -1;
			data[4] = -1;
		पूर्ण

		अगर (s2io_link_test(sp, &data[2]))
			ethtest->flags |= ETH_TEST_FL_FAILED;

		data[0] = 0;
		data[1] = 0;
		data[3] = 0;
		data[4] = 0;
	पूर्ण
पूर्ण

अटल व्योम s2io_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *estats,
				   u64 *पंचांगp_stats)
अणु
	पूर्णांक i = 0, k;
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा stat_block *stats = sp->mac_control.stats_info;
	काष्ठा swStat *swstats = &stats->sw_stat;
	काष्ठा xpakStat *xstats = &stats->xpak_stat;

	s2io_updt_stats(sp);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_frms_oflow) << 32  |
		le32_to_cpu(stats->पंचांगac_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_data_octets_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_data_octets);
	पंचांगp_stats[i++] = le64_to_cpu(stats->पंचांगac_drop_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_mcst_frms_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_mcst_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_bcst_frms_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_bcst_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->पंचांगac_छोड़ो_ctrl_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_ttl_octets_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_ttl_octets);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_ucst_frms_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_ucst_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_nucst_frms_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_nucst_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_any_err_frms_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_any_err_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->पंचांगac_ttl_less_fb_octets);
	पंचांगp_stats[i++] = le64_to_cpu(stats->पंचांगac_vld_ip_octets);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_vld_ip_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_vld_ip);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_drop_ip_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_drop_ip);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_icmp_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_icmp);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->पंचांगac_rst_tcp_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_rst_tcp);
	पंचांगp_stats[i++] = le64_to_cpu(stats->पंचांगac_tcp);
	पंचांगp_stats[i++] = (u64)le32_to_cpu(stats->पंचांगac_udp_oflow) << 32 |
		le32_to_cpu(stats->पंचांगac_udp);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_vld_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_vld_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_data_octets_oflow) << 32 |
		le32_to_cpu(stats->rmac_data_octets);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_fcs_err_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_drop_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_vld_mcst_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_vld_mcst_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_vld_bcst_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_vld_bcst_frms);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_in_rng_len_err_frms);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_out_rng_len_err_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_दीर्घ_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_छोड़ो_ctrl_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_unsup_ctrl_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_ttl_octets_oflow) << 32 |
		le32_to_cpu(stats->rmac_ttl_octets);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_accepted_ucst_frms_oflow) << 32
		| le32_to_cpu(stats->rmac_accepted_ucst_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_accepted_nucst_frms_oflow)
		<< 32 | le32_to_cpu(stats->rmac_accepted_nucst_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_discarded_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_discarded_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_drop_events_oflow)
		<< 32 | le32_to_cpu(stats->rmac_drop_events);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ttl_less_fb_octets);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ttl_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_usized_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_usized_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_osized_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_osized_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_frag_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_frag_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_jabber_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_jabber_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ttl_64_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ttl_65_127_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ttl_128_255_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ttl_256_511_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ttl_512_1023_frms);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ttl_1024_1518_frms);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_ip_oflow) << 32 |
		le32_to_cpu(stats->rmac_ip);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ip_octets);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_hdr_err_ip);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_drop_ip_oflow) << 32 |
		le32_to_cpu(stats->rmac_drop_ip);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_icmp_oflow) << 32 |
		le32_to_cpu(stats->rmac_icmp);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_tcp);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_udp_oflow) << 32 |
		le32_to_cpu(stats->rmac_udp);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_err_drp_udp_oflow) << 32 |
		le32_to_cpu(stats->rmac_err_drp_udp);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_xgmii_err_sym);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_frms_q0);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_frms_q1);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_frms_q2);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_frms_q3);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_frms_q4);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_frms_q5);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_frms_q6);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_frms_q7);
	पंचांगp_stats[i++] = le16_to_cpu(stats->rmac_full_q0);
	पंचांगp_stats[i++] = le16_to_cpu(stats->rmac_full_q1);
	पंचांगp_stats[i++] = le16_to_cpu(stats->rmac_full_q2);
	पंचांगp_stats[i++] = le16_to_cpu(stats->rmac_full_q3);
	पंचांगp_stats[i++] = le16_to_cpu(stats->rmac_full_q4);
	पंचांगp_stats[i++] = le16_to_cpu(stats->rmac_full_q5);
	पंचांगp_stats[i++] = le16_to_cpu(stats->rmac_full_q6);
	पंचांगp_stats[i++] = le16_to_cpu(stats->rmac_full_q7);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_छोड़ो_cnt_oflow) << 32 |
		le32_to_cpu(stats->rmac_छोड़ो_cnt);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_xgmii_data_err_cnt);
	पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_xgmii_ctrl_err_cnt);
	पंचांगp_stats[i++] =
		(u64)le32_to_cpu(stats->rmac_accepted_ip_oflow) << 32 |
		le32_to_cpu(stats->rmac_accepted_ip);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_err_tcp);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rd_req_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->new_rd_req_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->new_rd_req_rtry_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rd_rtry_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->wr_rtry_rd_ack_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->wr_req_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->new_wr_req_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->new_wr_req_rtry_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->wr_rtry_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->wr_disc_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rd_rtry_wr_ack_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->txp_wr_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->txd_rd_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->txd_wr_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rxd_rd_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rxd_wr_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->txf_rd_cnt);
	पंचांगp_stats[i++] = le32_to_cpu(stats->rxf_wr_cnt);

	/* Enhanced statistics exist only क्रम Hercules */
	अगर (sp->device_type == XFRAME_II_DEVICE) अणु
		पंचांगp_stats[i++] =
			le64_to_cpu(stats->rmac_ttl_1519_4095_frms);
		पंचांगp_stats[i++] =
			le64_to_cpu(stats->rmac_ttl_4096_8191_frms);
		पंचांगp_stats[i++] =
			le64_to_cpu(stats->rmac_ttl_8192_max_frms);
		पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_ttl_gt_max_frms);
		पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_osized_alt_frms);
		पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_jabber_alt_frms);
		पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_gt_max_alt_frms);
		पंचांगp_stats[i++] = le64_to_cpu(stats->rmac_vlan_frms);
		पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_len_discard);
		पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_fcs_discard);
		पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_pf_discard);
		पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_da_discard);
		पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_red_discard);
		पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_rts_discard);
		पंचांगp_stats[i++] = le32_to_cpu(stats->rmac_ingm_full_discard);
		पंचांगp_stats[i++] = le32_to_cpu(stats->link_fault_cnt);
	पूर्ण

	पंचांगp_stats[i++] = 0;
	पंचांगp_stats[i++] = swstats->single_ecc_errs;
	पंचांगp_stats[i++] = swstats->द्विगुन_ecc_errs;
	पंचांगp_stats[i++] = swstats->parity_err_cnt;
	पंचांगp_stats[i++] = swstats->serious_err_cnt;
	पंचांगp_stats[i++] = swstats->soft_reset_cnt;
	पंचांगp_stats[i++] = swstats->fअगरo_full_cnt;
	क्रम (k = 0; k < MAX_RX_RINGS; k++)
		पंचांगp_stats[i++] = swstats->ring_full_cnt[k];
	पंचांगp_stats[i++] = xstats->alarm_transceiver_temp_high;
	पंचांगp_stats[i++] = xstats->alarm_transceiver_temp_low;
	पंचांगp_stats[i++] = xstats->alarm_laser_bias_current_high;
	पंचांगp_stats[i++] = xstats->alarm_laser_bias_current_low;
	पंचांगp_stats[i++] = xstats->alarm_laser_output_घातer_high;
	पंचांगp_stats[i++] = xstats->alarm_laser_output_घातer_low;
	पंचांगp_stats[i++] = xstats->warn_transceiver_temp_high;
	पंचांगp_stats[i++] = xstats->warn_transceiver_temp_low;
	पंचांगp_stats[i++] = xstats->warn_laser_bias_current_high;
	पंचांगp_stats[i++] = xstats->warn_laser_bias_current_low;
	पंचांगp_stats[i++] = xstats->warn_laser_output_घातer_high;
	पंचांगp_stats[i++] = xstats->warn_laser_output_घातer_low;
	पंचांगp_stats[i++] = swstats->clubbed_frms_cnt;
	पंचांगp_stats[i++] = swstats->sending_both;
	पंचांगp_stats[i++] = swstats->outof_sequence_pkts;
	पंचांगp_stats[i++] = swstats->flush_max_pkts;
	अगर (swstats->num_aggregations) अणु
		u64 पंचांगp = swstats->sum_avg_pkts_aggregated;
		पूर्णांक count = 0;
		/*
		 * Since 64-bit भागide करोes not work on all platक्रमms,
		 * करो repeated subtraction.
		 */
		जबतक (पंचांगp >= swstats->num_aggregations) अणु
			पंचांगp -= swstats->num_aggregations;
			count++;
		पूर्ण
		पंचांगp_stats[i++] = count;
	पूर्ण अन्यथा
		पंचांगp_stats[i++] = 0;
	पंचांगp_stats[i++] = swstats->mem_alloc_fail_cnt;
	पंचांगp_stats[i++] = swstats->pci_map_fail_cnt;
	पंचांगp_stats[i++] = swstats->watchकरोg_समयr_cnt;
	पंचांगp_stats[i++] = swstats->mem_allocated;
	पंचांगp_stats[i++] = swstats->mem_मुक्तd;
	पंचांगp_stats[i++] = swstats->link_up_cnt;
	पंचांगp_stats[i++] = swstats->link_करोwn_cnt;
	पंचांगp_stats[i++] = swstats->link_up_समय;
	पंचांगp_stats[i++] = swstats->link_करोwn_समय;

	पंचांगp_stats[i++] = swstats->tx_buf_पात_cnt;
	पंचांगp_stats[i++] = swstats->tx_desc_पात_cnt;
	पंचांगp_stats[i++] = swstats->tx_parity_err_cnt;
	पंचांगp_stats[i++] = swstats->tx_link_loss_cnt;
	पंचांगp_stats[i++] = swstats->tx_list_proc_err_cnt;

	पंचांगp_stats[i++] = swstats->rx_parity_err_cnt;
	पंचांगp_stats[i++] = swstats->rx_पात_cnt;
	पंचांगp_stats[i++] = swstats->rx_parity_पात_cnt;
	पंचांगp_stats[i++] = swstats->rx_rda_fail_cnt;
	पंचांगp_stats[i++] = swstats->rx_unkn_prot_cnt;
	पंचांगp_stats[i++] = swstats->rx_fcs_err_cnt;
	पंचांगp_stats[i++] = swstats->rx_buf_size_err_cnt;
	पंचांगp_stats[i++] = swstats->rx_rxd_corrupt_cnt;
	पंचांगp_stats[i++] = swstats->rx_unkn_err_cnt;
	पंचांगp_stats[i++] = swstats->tda_err_cnt;
	पंचांगp_stats[i++] = swstats->pfc_err_cnt;
	पंचांगp_stats[i++] = swstats->pcc_err_cnt;
	पंचांगp_stats[i++] = swstats->tti_err_cnt;
	पंचांगp_stats[i++] = swstats->tpa_err_cnt;
	पंचांगp_stats[i++] = swstats->sm_err_cnt;
	पंचांगp_stats[i++] = swstats->lso_err_cnt;
	पंचांगp_stats[i++] = swstats->mac_पंचांगac_err_cnt;
	पंचांगp_stats[i++] = swstats->mac_rmac_err_cnt;
	पंचांगp_stats[i++] = swstats->xgxs_txgxs_err_cnt;
	पंचांगp_stats[i++] = swstats->xgxs_rxgxs_err_cnt;
	पंचांगp_stats[i++] = swstats->rc_err_cnt;
	पंचांगp_stats[i++] = swstats->prc_pcix_err_cnt;
	पंचांगp_stats[i++] = swstats->rpa_err_cnt;
	पंचांगp_stats[i++] = swstats->rda_err_cnt;
	पंचांगp_stats[i++] = swstats->rti_err_cnt;
	पंचांगp_stats[i++] = swstats->mc_err_cnt;
पूर्ण

अटल पूर्णांक s2io_ethtool_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस XENA_REG_SPACE;
पूर्ण


अटल पूर्णांक s2io_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस XENA_EEPROM_SPACE;
पूर्ण

अटल पूर्णांक s2io_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस S2IO_TEST_LEN;
	हाल ETH_SS_STATS:
		चयन (sp->device_type) अणु
		हाल XFRAME_I_DEVICE:
			वापस XFRAME_I_STAT_LEN;
		हाल XFRAME_II_DEVICE:
			वापस XFRAME_II_STAT_LEN;
		शेष:
			वापस 0;
		पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम s2io_ethtool_get_strings(काष्ठा net_device *dev,
				     u32 stringset, u8 *data)
अणु
	पूर्णांक stat_size = 0;
	काष्ठा s2io_nic *sp = netdev_priv(dev);

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, s2io_gstrings, S2IO_STRINGS_LEN);
		अवरोध;
	हाल ETH_SS_STATS:
		stat_size = माप(ethtool_xena_stats_keys);
		स_नकल(data, &ethtool_xena_stats_keys, stat_size);
		अगर (sp->device_type == XFRAME_II_DEVICE) अणु
			स_नकल(data + stat_size,
			       &ethtool_enhanced_stats_keys,
			       माप(ethtool_enhanced_stats_keys));
			stat_size += माप(ethtool_enhanced_stats_keys);
		पूर्ण

		स_नकल(data + stat_size, &ethtool_driver_stats_keys,
		       माप(ethtool_driver_stats_keys));
	पूर्ण
पूर्ण

अटल पूर्णांक s2io_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	netdev_features_t changed = (features ^ dev->features) & NETIF_F_LRO;

	अगर (changed && netअगर_running(dev)) अणु
		पूर्णांक rc;

		s2io_stop_all_tx_queue(sp);
		s2io_card_करोwn(sp);
		dev->features = features;
		rc = s2io_card_up(sp);
		अगर (rc)
			s2io_reset(sp);
		अन्यथा
			s2io_start_all_tx_queue(sp);

		वापस rc ? rc : 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo = s2io_ethtool_gdrvinfo,
	.get_regs_len = s2io_ethtool_get_regs_len,
	.get_regs = s2io_ethtool_gregs,
	.get_link = ethtool_op_get_link,
	.get_eeprom_len = s2io_get_eeprom_len,
	.get_eeprom = s2io_ethtool_geeprom,
	.set_eeprom = s2io_ethtool_seeprom,
	.get_ringparam = s2io_ethtool_gringparam,
	.get_छोड़ोparam = s2io_ethtool_getछोड़ो_data,
	.set_छोड़ोparam = s2io_ethtool_setछोड़ो_data,
	.self_test = s2io_ethtool_test,
	.get_strings = s2io_ethtool_get_strings,
	.set_phys_id = s2io_ethtool_set_led,
	.get_ethtool_stats = s2io_get_ethtool_stats,
	.get_sset_count = s2io_get_sset_count,
	.get_link_ksettings = s2io_ethtool_get_link_ksettings,
	.set_link_ksettings = s2io_ethtool_set_link_ksettings,
पूर्ण;

/**
 *  s2io_ioctl - Entry poपूर्णांक क्रम the Ioctl
 *  @dev :  Device poपूर्णांकer.
 *  @rq :  An IOCTL specefic काष्ठाure, that can contain a poपूर्णांकer to
 *  a proprietary काष्ठाure used to pass inक्रमmation to the driver.
 *  @cmd :  This is used to distinguish between the dअगरferent commands that
 *  can be passed to the IOCTL functions.
 *  Description:
 *  Currently there are no special functionality supported in IOCTL, hence
 *  function always वापस EOPNOTSUPPORTED
 */

अटल पूर्णांक s2io_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/**
 *  s2io_change_mtu - entry poपूर्णांक to change MTU size क्रम the device.
 *   @dev : device poपूर्णांकer.
 *   @new_mtu : the new MTU size क्रम the device.
 *   Description: A driver entry poपूर्णांक to change MTU size क्रम the device.
 *   Beक्रमe changing the MTU the device must be stopped.
 *  Return value:
 *   0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *   file on failure.
 */

अटल पूर्णांक s2io_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	पूर्णांक ret = 0;

	dev->mtu = new_mtu;
	अगर (netअगर_running(dev)) अणु
		s2io_stop_all_tx_queue(sp);
		s2io_card_करोwn(sp);
		ret = s2io_card_up(sp);
		अगर (ret) अणु
			DBG_PRINT(ERR_DBG, "%s: Device bring up failed\n",
				  __func__);
			वापस ret;
		पूर्ण
		s2io_wake_all_tx_queue(sp);
	पूर्ण अन्यथा अणु /* Device is करोwn */
		काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
		u64 val64 = new_mtu;

		ग_लिखोq(vBIT(val64, 2, 14), &bar0->rmac_max_pyld_len);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * s2io_set_link - Set the LInk status
 * @work: work काष्ठा containing a poपूर्णांकer to device निजी काष्ठाure
 * Description: Sets the link status क्रम the adapter
 */

अटल व्योम s2io_set_link(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा s2io_nic *nic = container_of(work, काष्ठा s2io_nic,
					    set_link_task);
	काष्ठा net_device *dev = nic->dev;
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	रेजिस्टर u64 val64;
	u16 subid;

	rtnl_lock();

	अगर (!netअगर_running(dev))
		जाओ out_unlock;

	अगर (test_and_set_bit(__S2IO_STATE_LINK_TASK, &(nic->state))) अणु
		/* The card is being reset, no poपूर्णांक करोing anything */
		जाओ out_unlock;
	पूर्ण

	subid = nic->pdev->subप्रणाली_device;
	अगर (s2io_link_fault_indication(nic) == MAC_RMAC_ERR_TIMER) अणु
		/*
		 * Allow a small delay क्रम the NICs self initiated
		 * cleanup to complete.
		 */
		msleep(100);
	पूर्ण

	val64 = पढ़ोq(&bar0->adapter_status);
	अगर (LINK_IS_UP(val64)) अणु
		अगर (!(पढ़ोq(&bar0->adapter_control) & ADAPTER_CNTL_EN)) अणु
			अगर (verअगरy_xena_quiescence(nic)) अणु
				val64 = पढ़ोq(&bar0->adapter_control);
				val64 |= ADAPTER_CNTL_EN;
				ग_लिखोq(val64, &bar0->adapter_control);
				अगर (CARDS_WITH_FAULTY_LINK_INDICATORS(
					    nic->device_type, subid)) अणु
					val64 = पढ़ोq(&bar0->gpio_control);
					val64 |= GPIO_CTRL_GPIO_0;
					ग_लिखोq(val64, &bar0->gpio_control);
					val64 = पढ़ोq(&bar0->gpio_control);
				पूर्ण अन्यथा अणु
					val64 |= ADAPTER_LED_ON;
					ग_लिखोq(val64, &bar0->adapter_control);
				पूर्ण
				nic->device_enabled_once = true;
			पूर्ण अन्यथा अणु
				DBG_PRINT(ERR_DBG,
					  "%s: Error: device is not Quiescent\n",
					  dev->name);
				s2io_stop_all_tx_queue(nic);
			पूर्ण
		पूर्ण
		val64 = पढ़ोq(&bar0->adapter_control);
		val64 |= ADAPTER_LED_ON;
		ग_लिखोq(val64, &bar0->adapter_control);
		s2io_link(nic, LINK_UP);
	पूर्ण अन्यथा अणु
		अगर (CARDS_WITH_FAULTY_LINK_INDICATORS(nic->device_type,
						      subid)) अणु
			val64 = पढ़ोq(&bar0->gpio_control);
			val64 &= ~GPIO_CTRL_GPIO_0;
			ग_लिखोq(val64, &bar0->gpio_control);
			val64 = पढ़ोq(&bar0->gpio_control);
		पूर्ण
		/* turn off LED */
		val64 = पढ़ोq(&bar0->adapter_control);
		val64 = val64 & (~ADAPTER_LED_ON);
		ग_लिखोq(val64, &bar0->adapter_control);
		s2io_link(nic, LINK_DOWN);
	पूर्ण
	clear_bit(__S2IO_STATE_LINK_TASK, &(nic->state));

out_unlock:
	rtnl_unlock();
पूर्ण

अटल पूर्णांक set_rxd_buffer_poपूर्णांकer(काष्ठा s2io_nic *sp, काष्ठा RxD_t *rxdp,
				  काष्ठा buffAdd *ba,
				  काष्ठा sk_buff **skb, u64 *temp0, u64 *temp1,
				  u64 *temp2, पूर्णांक size)
अणु
	काष्ठा net_device *dev = sp->dev;
	काष्ठा swStat *stats = &sp->mac_control.stats_info->sw_stat;

	अगर ((sp->rxd_mode == RXD_MODE_1) && (rxdp->Host_Control == 0)) अणु
		काष्ठा RxD1 *rxdp1 = (काष्ठा RxD1 *)rxdp;
		/* allocate skb */
		अगर (*skb) अणु
			DBG_PRINT(INFO_DBG, "SKB is not NULL\n");
			/*
			 * As Rx frame are not going to be processed,
			 * using same mapped address क्रम the Rxd
			 * buffer poपूर्णांकer
			 */
			rxdp1->Buffer0_ptr = *temp0;
		पूर्ण अन्यथा अणु
			*skb = netdev_alloc_skb(dev, size);
			अगर (!(*skb)) अणु
				DBG_PRINT(INFO_DBG,
					  "%s: Out of memory to allocate %s\n",
					  dev->name, "1 buf mode SKBs");
				stats->mem_alloc_fail_cnt++;
				वापस -ENOMEM ;
			पूर्ण
			stats->mem_allocated += (*skb)->truesize;
			/* storing the mapped addr in a temp variable
			 * such it will be used क्रम next rxd whose
			 * Host Control is शून्य
			 */
			rxdp1->Buffer0_ptr = *temp0 =
				dma_map_single(&sp->pdev->dev, (*skb)->data,
					       size - NET_IP_ALIGN,
					       DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&sp->pdev->dev, rxdp1->Buffer0_ptr))
				जाओ meदो_स्मृति_failed;
			rxdp->Host_Control = (अचिन्हित दीर्घ) (*skb);
		पूर्ण
	पूर्ण अन्यथा अगर ((sp->rxd_mode == RXD_MODE_3B) && (rxdp->Host_Control == 0)) अणु
		काष्ठा RxD3 *rxdp3 = (काष्ठा RxD3 *)rxdp;
		/* Two buffer Mode */
		अगर (*skb) अणु
			rxdp3->Buffer2_ptr = *temp2;
			rxdp3->Buffer0_ptr = *temp0;
			rxdp3->Buffer1_ptr = *temp1;
		पूर्ण अन्यथा अणु
			*skb = netdev_alloc_skb(dev, size);
			अगर (!(*skb)) अणु
				DBG_PRINT(INFO_DBG,
					  "%s: Out of memory to allocate %s\n",
					  dev->name,
					  "2 buf mode SKBs");
				stats->mem_alloc_fail_cnt++;
				वापस -ENOMEM;
			पूर्ण
			stats->mem_allocated += (*skb)->truesize;
			rxdp3->Buffer2_ptr = *temp2 =
				dma_map_single(&sp->pdev->dev, (*skb)->data,
					       dev->mtu + 4, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&sp->pdev->dev, rxdp3->Buffer2_ptr))
				जाओ meदो_स्मृति_failed;
			rxdp3->Buffer0_ptr = *temp0 =
				dma_map_single(&sp->pdev->dev, ba->ba_0,
					       BUF0_LEN, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&sp->pdev->dev, rxdp3->Buffer0_ptr)) अणु
				dma_unmap_single(&sp->pdev->dev,
						 (dma_addr_t)rxdp3->Buffer2_ptr,
						 dev->mtu + 4,
						 DMA_FROM_DEVICE);
				जाओ meदो_स्मृति_failed;
			पूर्ण
			rxdp->Host_Control = (अचिन्हित दीर्घ) (*skb);

			/* Buffer-1 will be dummy buffer not used */
			rxdp3->Buffer1_ptr = *temp1 =
				dma_map_single(&sp->pdev->dev, ba->ba_1,
					       BUF1_LEN, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&sp->pdev->dev, rxdp3->Buffer1_ptr)) अणु
				dma_unmap_single(&sp->pdev->dev,
						 (dma_addr_t)rxdp3->Buffer0_ptr,
						 BUF0_LEN, DMA_FROM_DEVICE);
				dma_unmap_single(&sp->pdev->dev,
						 (dma_addr_t)rxdp3->Buffer2_ptr,
						 dev->mtu + 4,
						 DMA_FROM_DEVICE);
				जाओ meदो_स्मृति_failed;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;

meदो_स्मृति_failed:
	stats->pci_map_fail_cnt++;
	stats->mem_मुक्तd += (*skb)->truesize;
	dev_kमुक्त_skb(*skb);
	वापस -ENOMEM;
पूर्ण

अटल व्योम set_rxd_buffer_size(काष्ठा s2io_nic *sp, काष्ठा RxD_t *rxdp,
				पूर्णांक size)
अणु
	काष्ठा net_device *dev = sp->dev;
	अगर (sp->rxd_mode == RXD_MODE_1) अणु
		rxdp->Control_2 = SET_BUFFER0_SIZE_1(size - NET_IP_ALIGN);
	पूर्ण अन्यथा अगर (sp->rxd_mode == RXD_MODE_3B) अणु
		rxdp->Control_2 = SET_BUFFER0_SIZE_3(BUF0_LEN);
		rxdp->Control_2 |= SET_BUFFER1_SIZE_3(1);
		rxdp->Control_2 |= SET_BUFFER2_SIZE_3(dev->mtu + 4);
	पूर्ण
पूर्ण

अटल  पूर्णांक rxd_owner_bit_reset(काष्ठा s2io_nic *sp)
अणु
	पूर्णांक i, j, k, blk_cnt = 0, size;
	काष्ठा config_param *config = &sp->config;
	काष्ठा mac_info *mac_control = &sp->mac_control;
	काष्ठा net_device *dev = sp->dev;
	काष्ठा RxD_t *rxdp = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा buffAdd *ba = शून्य;
	u64 temp0_64 = 0, temp1_64 = 0, temp2_64 = 0;

	/* Calculate the size based on ring mode */
	size = dev->mtu + HEADER_ETHERNET_II_802_3_SIZE +
		HEADER_802_2_SIZE + HEADER_SNAP_SIZE;
	अगर (sp->rxd_mode == RXD_MODE_1)
		size += NET_IP_ALIGN;
	अन्यथा अगर (sp->rxd_mode == RXD_MODE_3B)
		size = dev->mtu + ALIGN_SIZE + BUF0_LEN + 4;

	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा rx_ring_config *rx_cfg = &config->rx_cfg[i];
		काष्ठा ring_info *ring = &mac_control->rings[i];

		blk_cnt = rx_cfg->num_rxd / (rxd_count[sp->rxd_mode] + 1);

		क्रम (j = 0; j < blk_cnt; j++) अणु
			क्रम (k = 0; k < rxd_count[sp->rxd_mode]; k++) अणु
				rxdp = ring->rx_blocks[j].rxds[k].virt_addr;
				अगर (sp->rxd_mode == RXD_MODE_3B)
					ba = &ring->ba[j][k];
				अगर (set_rxd_buffer_poपूर्णांकer(sp, rxdp, ba, &skb,
							   &temp0_64,
							   &temp1_64,
							   &temp2_64,
							   size) == -ENOMEM) अणु
					वापस 0;
				पूर्ण

				set_rxd_buffer_size(sp, rxdp, size);
				dma_wmb();
				/* flip the Ownership bit to Hardware */
				rxdp->Control_1 |= RXD_OWN_XENA;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;

पूर्ण

अटल पूर्णांक s2io_add_isr(काष्ठा s2io_nic *sp)
अणु
	पूर्णांक ret = 0;
	काष्ठा net_device *dev = sp->dev;
	पूर्णांक err = 0;

	अगर (sp->config.पूर्णांकr_type == MSI_X)
		ret = s2io_enable_msi_x(sp);
	अगर (ret) अणु
		DBG_PRINT(ERR_DBG, "%s: Defaulting to INTA\n", dev->name);
		sp->config.पूर्णांकr_type = INTA;
	पूर्ण

	/*
	 * Store the values of the MSIX table in
	 * the काष्ठा s2io_nic काष्ठाure
	 */
	store_xmsi_data(sp);

	/* After proper initialization of H/W, रेजिस्टर ISR */
	अगर (sp->config.पूर्णांकr_type == MSI_X) अणु
		पूर्णांक i, msix_rx_cnt = 0;

		क्रम (i = 0; i < sp->num_entries; i++) अणु
			अगर (sp->s2io_entries[i].in_use == MSIX_FLG) अणु
				अगर (sp->s2io_entries[i].type ==
				    MSIX_RING_TYPE) अणु
					snम_लिखो(sp->desc[i],
						माप(sp->desc[i]),
						"%s:MSI-X-%d-RX",
						dev->name, i);
					err = request_irq(sp->entries[i].vector,
							  s2io_msix_ring_handle,
							  0,
							  sp->desc[i],
							  sp->s2io_entries[i].arg);
				पूर्ण अन्यथा अगर (sp->s2io_entries[i].type ==
					   MSIX_ALARM_TYPE) अणु
					snम_लिखो(sp->desc[i],
						माप(sp->desc[i]),
						"%s:MSI-X-%d-TX",
						dev->name, i);
					err = request_irq(sp->entries[i].vector,
							  s2io_msix_fअगरo_handle,
							  0,
							  sp->desc[i],
							  sp->s2io_entries[i].arg);

				पूर्ण
				/* अगर either data or addr is zero prपूर्णांक it. */
				अगर (!(sp->msix_info[i].addr &&
				      sp->msix_info[i].data)) अणु
					DBG_PRINT(ERR_DBG,
						  "%s @Addr:0x%llx Data:0x%llx\n",
						  sp->desc[i],
						  (अचिन्हित दीर्घ दीर्घ)
						  sp->msix_info[i].addr,
						  (अचिन्हित दीर्घ दीर्घ)
						  ntohl(sp->msix_info[i].data));
				पूर्ण अन्यथा
					msix_rx_cnt++;
				अगर (err) अणु
					हटाओ_msix_isr(sp);

					DBG_PRINT(ERR_DBG,
						  "%s:MSI-X-%d registration "
						  "failed\n", dev->name, i);

					DBG_PRINT(ERR_DBG,
						  "%s: Defaulting to INTA\n",
						  dev->name);
					sp->config.पूर्णांकr_type = INTA;
					अवरोध;
				पूर्ण
				sp->s2io_entries[i].in_use =
					MSIX_REGISTERED_SUCCESS;
			पूर्ण
		पूर्ण
		अगर (!err) अणु
			pr_info("MSI-X-RX %d entries enabled\n", --msix_rx_cnt);
			DBG_PRINT(INFO_DBG,
				  "MSI-X-TX entries enabled through alarm vector\n");
		पूर्ण
	पूर्ण
	अगर (sp->config.पूर्णांकr_type == INTA) अणु
		err = request_irq(sp->pdev->irq, s2io_isr, IRQF_SHARED,
				  sp->name, dev);
		अगर (err) अणु
			DBG_PRINT(ERR_DBG, "%s: ISR registration failed\n",
				  dev->name);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम s2io_rem_isr(काष्ठा s2io_nic *sp)
अणु
	अगर (sp->config.पूर्णांकr_type == MSI_X)
		हटाओ_msix_isr(sp);
	अन्यथा
		हटाओ_पूर्णांकa_isr(sp);
पूर्ण

अटल व्योम करो_s2io_card_करोwn(काष्ठा s2io_nic *sp, पूर्णांक करो_io)
अणु
	पूर्णांक cnt = 0;
	काष्ठा XENA_dev_config __iomem *bar0 = sp->bar0;
	रेजिस्टर u64 val64 = 0;
	काष्ठा config_param *config;
	config = &sp->config;

	अगर (!is_s2io_card_up(sp))
		वापस;

	del_समयr_sync(&sp->alarm_समयr);
	/* If s2io_set_link task is executing, रुको till it completes. */
	जबतक (test_and_set_bit(__S2IO_STATE_LINK_TASK, &(sp->state)))
		msleep(50);
	clear_bit(__S2IO_STATE_CARD_UP, &sp->state);

	/* Disable napi */
	अगर (sp->config.napi) अणु
		पूर्णांक off = 0;
		अगर (config->पूर्णांकr_type ==  MSI_X) अणु
			क्रम (; off < sp->config.rx_ring_num; off++)
				napi_disable(&sp->mac_control.rings[off].napi);
		पूर्ण
		अन्यथा
			napi_disable(&sp->napi);
	पूर्ण

	/* disable Tx and Rx traffic on the NIC */
	अगर (करो_io)
		stop_nic(sp);

	s2io_rem_isr(sp);

	/* stop the tx queue, indicate link करोwn */
	s2io_link(sp, LINK_DOWN);

	/* Check अगर the device is Quiescent and then Reset the NIC */
	जबतक (करो_io) अणु
		/* As per the HW requirement we need to replenish the
		 * receive buffer to aव्योम the ring bump. Since there is
		 * no पूर्णांकention of processing the Rx frame at this poपूर्णांकwe are
		 * just setting the ownership bit of rxd in Each Rx
		 * ring to HW and set the appropriate buffer size
		 * based on the ring mode
		 */
		rxd_owner_bit_reset(sp);

		val64 = पढ़ोq(&bar0->adapter_status);
		अगर (verअगरy_xena_quiescence(sp)) अणु
			अगर (verअगरy_pcc_quiescent(sp, sp->device_enabled_once))
				अवरोध;
		पूर्ण

		msleep(50);
		cnt++;
		अगर (cnt == 10) अणु
			DBG_PRINT(ERR_DBG, "Device not Quiescent - "
				  "adapter status reads 0x%llx\n",
				  (अचिन्हित दीर्घ दीर्घ)val64);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (करो_io)
		s2io_reset(sp);

	/* Free all Tx buffers */
	मुक्त_tx_buffers(sp);

	/* Free all Rx buffers */
	मुक्त_rx_buffers(sp);

	clear_bit(__S2IO_STATE_LINK_TASK, &(sp->state));
पूर्ण

अटल व्योम s2io_card_करोwn(काष्ठा s2io_nic *sp)
अणु
	करो_s2io_card_करोwn(sp, 1);
पूर्ण

अटल पूर्णांक s2io_card_up(काष्ठा s2io_nic *sp)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा config_param *config;
	काष्ठा mac_info *mac_control;
	काष्ठा net_device *dev = sp->dev;
	u16 पूर्णांकerruptible;

	/* Initialize the H/W I/O रेजिस्टरs */
	ret = init_nic(sp);
	अगर (ret != 0) अणु
		DBG_PRINT(ERR_DBG, "%s: H/W initialization failed\n",
			  dev->name);
		अगर (ret != -EIO)
			s2io_reset(sp);
		वापस ret;
	पूर्ण

	/*
	 * Initializing the Rx buffers. For now we are considering only 1
	 * Rx ring and initializing buffers पूर्णांकo 30 Rx blocks
	 */
	config = &sp->config;
	mac_control = &sp->mac_control;

	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा ring_info *ring = &mac_control->rings[i];

		ring->mtu = dev->mtu;
		ring->lro = !!(dev->features & NETIF_F_LRO);
		ret = fill_rx_buffers(sp, ring, 1);
		अगर (ret) अणु
			DBG_PRINT(ERR_DBG, "%s: Out of memory in Open\n",
				  dev->name);
			s2io_reset(sp);
			मुक्त_rx_buffers(sp);
			वापस -ENOMEM;
		पूर्ण
		DBG_PRINT(INFO_DBG, "Buf in ring:%d is %d:\n", i,
			  ring->rx_bufs_left);
	पूर्ण

	/* Initialise napi */
	अगर (config->napi) अणु
		अगर (config->पूर्णांकr_type ==  MSI_X) अणु
			क्रम (i = 0; i < sp->config.rx_ring_num; i++)
				napi_enable(&sp->mac_control.rings[i].napi);
		पूर्ण अन्यथा अणु
			napi_enable(&sp->napi);
		पूर्ण
	पूर्ण

	/* Maपूर्णांकain the state prior to the खोलो */
	अगर (sp->promisc_flg)
		sp->promisc_flg = 0;
	अगर (sp->m_cast_flg) अणु
		sp->m_cast_flg = 0;
		sp->all_multi_pos = 0;
	पूर्ण

	/* Setting its receive mode */
	s2io_set_multicast(dev, true);

	अगर (dev->features & NETIF_F_LRO) अणु
		/* Initialize max aggregatable pkts per session based on MTU */
		sp->lro_max_aggr_per_sess = ((1<<16) - 1) / dev->mtu;
		/* Check अगर we can use (अगर specअगरied) user provided value */
		अगर (lro_max_pkts < sp->lro_max_aggr_per_sess)
			sp->lro_max_aggr_per_sess = lro_max_pkts;
	पूर्ण

	/* Enable Rx Traffic and पूर्णांकerrupts on the NIC */
	अगर (start_nic(sp)) अणु
		DBG_PRINT(ERR_DBG, "%s: Starting NIC failed\n", dev->name);
		s2io_reset(sp);
		मुक्त_rx_buffers(sp);
		वापस -ENODEV;
	पूर्ण

	/* Add पूर्णांकerrupt service routine */
	अगर (s2io_add_isr(sp) != 0) अणु
		अगर (sp->config.पूर्णांकr_type == MSI_X)
			s2io_rem_isr(sp);
		s2io_reset(sp);
		मुक्त_rx_buffers(sp);
		वापस -ENODEV;
	पूर्ण

	समयr_setup(&sp->alarm_समयr, s2io_alarm_handle, 0);
	mod_समयr(&sp->alarm_समयr, jअगरfies + HZ / 2);

	set_bit(__S2IO_STATE_CARD_UP, &sp->state);

	/*  Enable select पूर्णांकerrupts */
	en_dis_err_alarms(sp, ENA_ALL_INTRS, ENABLE_INTRS);
	अगर (sp->config.पूर्णांकr_type != INTA) अणु
		पूर्णांकerruptible = TX_TRAFFIC_INTR | TX_PIC_INTR;
		en_dis_able_nic_पूर्णांकrs(sp, पूर्णांकerruptible, ENABLE_INTRS);
	पूर्ण अन्यथा अणु
		पूर्णांकerruptible = TX_TRAFFIC_INTR | RX_TRAFFIC_INTR;
		पूर्णांकerruptible |= TX_PIC_INTR;
		en_dis_able_nic_पूर्णांकrs(sp, पूर्णांकerruptible, ENABLE_INTRS);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * s2io_restart_nic - Resets the NIC.
 * @work : work काष्ठा containing a poपूर्णांकer to the device निजी काष्ठाure
 * Description:
 * This function is scheduled to be run by the s2io_tx_watchकरोg
 * function after 0.5 secs to reset the NIC. The idea is to reduce
 * the run समय of the watch करोg routine which is run holding a
 * spin lock.
 */

अटल व्योम s2io_restart_nic(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा s2io_nic *sp = container_of(work, काष्ठा s2io_nic, rst_समयr_task);
	काष्ठा net_device *dev = sp->dev;

	rtnl_lock();

	अगर (!netअगर_running(dev))
		जाओ out_unlock;

	s2io_card_करोwn(sp);
	अगर (s2io_card_up(sp)) अणु
		DBG_PRINT(ERR_DBG, "%s: Device bring up failed\n", dev->name);
	पूर्ण
	s2io_wake_all_tx_queue(sp);
	DBG_PRINT(ERR_DBG, "%s: was reset by Tx watchdog timer\n", dev->name);
out_unlock:
	rtnl_unlock();
पूर्ण

/**
 *  s2io_tx_watchकरोg - Watchकरोg क्रम transmit side.
 *  @dev : Poपूर्णांकer to net device काष्ठाure
 *  @txqueue: index of the hanging queue
 *  Description:
 *  This function is triggered अगर the Tx Queue is stopped
 *  क्रम a pre-defined amount of समय when the Interface is still up.
 *  If the Interface is jammed in such a situation, the hardware is
 *  reset (by s2io_बंद) and restarted again (by s2io_खोलो) to
 *  overcome any problem that might have been caused in the hardware.
 *  Return value:
 *  व्योम
 */

अटल व्योम s2io_tx_watchकरोg(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा s2io_nic *sp = netdev_priv(dev);
	काष्ठा swStat *swstats = &sp->mac_control.stats_info->sw_stat;

	अगर (netअगर_carrier_ok(dev)) अणु
		swstats->watchकरोg_समयr_cnt++;
		schedule_work(&sp->rst_समयr_task);
		swstats->soft_reset_cnt++;
	पूर्ण
पूर्ण

/**
 *   rx_osm_handler - To perक्रमm some OS related operations on SKB.
 *   @ring_data : the ring from which this RxD was extracted.
 *   @rxdp: descriptor
 *   Description:
 *   This function is called by the Rx पूर्णांकerrupt serivce routine to perक्रमm
 *   some OS related operations on the SKB beक्रमe passing it to the upper
 *   layers. It मुख्यly checks अगर the checksum is OK, अगर so adds it to the
 *   SKBs cksum variable, increments the Rx packet count and passes the SKB
 *   to the upper layer. If the checksum is wrong, it increments the Rx
 *   packet error count, मुक्तs the SKB and वापसs error.
 *   Return value:
 *   SUCCESS on success and -1 on failure.
 */
अटल पूर्णांक rx_osm_handler(काष्ठा ring_info *ring_data, काष्ठा RxD_t * rxdp)
अणु
	काष्ठा s2io_nic *sp = ring_data->nic;
	काष्ठा net_device *dev = ring_data->dev;
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)
		((अचिन्हित दीर्घ)rxdp->Host_Control);
	पूर्णांक ring_no = ring_data->ring_no;
	u16 l3_csum, l4_csum;
	अचिन्हित दीर्घ दीर्घ err = rxdp->Control_1 & RXD_T_CODE;
	काष्ठा lro *lro;
	u8 err_mask;
	काष्ठा swStat *swstats = &sp->mac_control.stats_info->sw_stat;

	skb->dev = dev;

	अगर (err) अणु
		/* Check क्रम parity error */
		अगर (err & 0x1)
			swstats->parity_err_cnt++;

		err_mask = err >> 48;
		चयन (err_mask) अणु
		हाल 1:
			swstats->rx_parity_err_cnt++;
			अवरोध;

		हाल 2:
			swstats->rx_पात_cnt++;
			अवरोध;

		हाल 3:
			swstats->rx_parity_पात_cnt++;
			अवरोध;

		हाल 4:
			swstats->rx_rda_fail_cnt++;
			अवरोध;

		हाल 5:
			swstats->rx_unkn_prot_cnt++;
			अवरोध;

		हाल 6:
			swstats->rx_fcs_err_cnt++;
			अवरोध;

		हाल 7:
			swstats->rx_buf_size_err_cnt++;
			अवरोध;

		हाल 8:
			swstats->rx_rxd_corrupt_cnt++;
			अवरोध;

		हाल 15:
			swstats->rx_unkn_err_cnt++;
			अवरोध;
		पूर्ण
		/*
		 * Drop the packet अगर bad transfer code. Exception being
		 * 0x5, which could be due to unsupported IPv6 extension header.
		 * In this हाल, we let stack handle the packet.
		 * Note that in this हाल, since checksum will be incorrect,
		 * stack will validate the same.
		 */
		अगर (err_mask != 0x5) अणु
			DBG_PRINT(ERR_DBG, "%s: Rx error Value: 0x%x\n",
				  dev->name, err_mask);
			dev->stats.rx_crc_errors++;
			swstats->mem_मुक्तd
				+= skb->truesize;
			dev_kमुक्त_skb(skb);
			ring_data->rx_bufs_left -= 1;
			rxdp->Host_Control = 0;
			वापस 0;
		पूर्ण
	पूर्ण

	rxdp->Host_Control = 0;
	अगर (sp->rxd_mode == RXD_MODE_1) अणु
		पूर्णांक len = RXD_GET_BUFFER0_SIZE_1(rxdp->Control_2);

		skb_put(skb, len);
	पूर्ण अन्यथा अगर (sp->rxd_mode == RXD_MODE_3B) अणु
		पूर्णांक get_block = ring_data->rx_curr_get_info.block_index;
		पूर्णांक get_off = ring_data->rx_curr_get_info.offset;
		पूर्णांक buf0_len = RXD_GET_BUFFER0_SIZE_3(rxdp->Control_2);
		पूर्णांक buf2_len = RXD_GET_BUFFER2_SIZE_3(rxdp->Control_2);
		अचिन्हित अक्षर *buff = skb_push(skb, buf0_len);

		काष्ठा buffAdd *ba = &ring_data->ba[get_block][get_off];
		स_नकल(buff, ba->ba_0, buf0_len);
		skb_put(skb, buf2_len);
	पूर्ण

	अगर ((rxdp->Control_1 & TCP_OR_UDP_FRAME) &&
	    ((!ring_data->lro) ||
	     (!(rxdp->Control_1 & RXD_FRAME_IP_FRAG))) &&
	    (dev->features & NETIF_F_RXCSUM)) अणु
		l3_csum = RXD_GET_L3_CKSUM(rxdp->Control_1);
		l4_csum = RXD_GET_L4_CKSUM(rxdp->Control_1);
		अगर ((l3_csum == L3_CKSUM_OK) && (l4_csum == L4_CKSUM_OK)) अणु
			/*
			 * NIC verअगरies अगर the Checksum of the received
			 * frame is Ok or not and accordingly वापसs
			 * a flag in the RxD.
			 */
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			अगर (ring_data->lro) अणु
				u32 tcp_len = 0;
				u8 *tcp;
				पूर्णांक ret = 0;

				ret = s2io_club_tcp_session(ring_data,
							    skb->data, &tcp,
							    &tcp_len, &lro,
							    rxdp, sp);
				चयन (ret) अणु
				हाल 3: /* Begin anew */
					lro->parent = skb;
					जाओ aggregate;
				हाल 1: /* Aggregate */
					lro_append_pkt(sp, lro, skb, tcp_len);
					जाओ aggregate;
				हाल 4: /* Flush session */
					lro_append_pkt(sp, lro, skb, tcp_len);
					queue_rx_frame(lro->parent,
						       lro->vlan_tag);
					clear_lro_session(lro);
					swstats->flush_max_pkts++;
					जाओ aggregate;
				हाल 2: /* Flush both */
					lro->parent->data_len = lro->frags_len;
					swstats->sending_both++;
					queue_rx_frame(lro->parent,
						       lro->vlan_tag);
					clear_lro_session(lro);
					जाओ send_up;
				हाल 0: /* sessions exceeded */
				हाल -1: /* non-TCP or not L2 aggregatable */
				हाल 5: /*
					 * First pkt in session not
					 * L3/L4 aggregatable
					 */
					अवरोध;
				शेष:
					DBG_PRINT(ERR_DBG,
						  "%s: Samadhana!!\n",
						  __func__);
					BUG();
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Packet with erroneous checksum, let the
			 * upper layers deal with it.
			 */
			skb_checksum_none_निश्चित(skb);
		पूर्ण
	पूर्ण अन्यथा
		skb_checksum_none_निश्चित(skb);

	swstats->mem_मुक्तd += skb->truesize;
send_up:
	skb_record_rx_queue(skb, ring_no);
	queue_rx_frame(skb, RXD_GET_VLAN_TAG(rxdp->Control_2));
aggregate:
	sp->mac_control.rings[ring_no].rx_bufs_left -= 1;
	वापस SUCCESS;
पूर्ण

/**
 *  s2io_link - stops/starts the Tx queue.
 *  @sp : निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 *  s2io_nic काष्ठाure.
 *  @link : inidicates whether link is UP/DOWN.
 *  Description:
 *  This function stops/starts the Tx queue depending on whether the link
 *  status of the NIC is is करोwn or up. This is called by the Alarm
 *  पूर्णांकerrupt handler whenever a link change पूर्णांकerrupt comes up.
 *  Return value:
 *  व्योम.
 */

अटल व्योम s2io_link(काष्ठा s2io_nic *sp, पूर्णांक link)
अणु
	काष्ठा net_device *dev = sp->dev;
	काष्ठा swStat *swstats = &sp->mac_control.stats_info->sw_stat;

	अगर (link != sp->last_link_state) अणु
		init_tti(sp, link, false);
		अगर (link == LINK_DOWN) अणु
			DBG_PRINT(ERR_DBG, "%s: Link down\n", dev->name);
			s2io_stop_all_tx_queue(sp);
			netअगर_carrier_off(dev);
			अगर (swstats->link_up_cnt)
				swstats->link_up_समय =
					jअगरfies - sp->start_समय;
			swstats->link_करोwn_cnt++;
		पूर्ण अन्यथा अणु
			DBG_PRINT(ERR_DBG, "%s: Link Up\n", dev->name);
			अगर (swstats->link_करोwn_cnt)
				swstats->link_करोwn_समय =
					jअगरfies - sp->start_समय;
			swstats->link_up_cnt++;
			netअगर_carrier_on(dev);
			s2io_wake_all_tx_queue(sp);
		पूर्ण
	पूर्ण
	sp->last_link_state = link;
	sp->start_समय = jअगरfies;
पूर्ण

/**
 *  s2io_init_pci -Initialization of PCI and PCI-X configuration रेजिस्टरs .
 *  @sp : निजी member of the device काष्ठाure, which is a poपूर्णांकer to the
 *  s2io_nic काष्ठाure.
 *  Description:
 *  This function initializes a few of the PCI and PCI-X configuration रेजिस्टरs
 *  with recommended values.
 *  Return value:
 *  व्योम
 */

अटल व्योम s2io_init_pci(काष्ठा s2io_nic *sp)
अणु
	u16 pci_cmd = 0, pcix_cmd = 0;

	/* Enable Data Parity Error Recovery in PCI-X command रेजिस्टर. */
	pci_पढ़ो_config_word(sp->pdev, PCIX_COMMAND_REGISTER,
			     &(pcix_cmd));
	pci_ग_लिखो_config_word(sp->pdev, PCIX_COMMAND_REGISTER,
			      (pcix_cmd | 1));
	pci_पढ़ो_config_word(sp->pdev, PCIX_COMMAND_REGISTER,
			     &(pcix_cmd));

	/* Set the PErr Response bit in PCI command रेजिस्टर. */
	pci_पढ़ो_config_word(sp->pdev, PCI_COMMAND, &pci_cmd);
	pci_ग_लिखो_config_word(sp->pdev, PCI_COMMAND,
			      (pci_cmd | PCI_COMMAND_PARITY));
	pci_पढ़ो_config_word(sp->pdev, PCI_COMMAND, &pci_cmd);
पूर्ण

अटल पूर्णांक s2io_verअगरy_parm(काष्ठा pci_dev *pdev, u8 *dev_पूर्णांकr_type,
			    u8 *dev_multiq)
अणु
	पूर्णांक i;

	अगर ((tx_fअगरo_num > MAX_TX_FIFOS) || (tx_fअगरo_num < 1)) अणु
		DBG_PRINT(ERR_DBG, "Requested number of tx fifos "
			  "(%d) not supported\n", tx_fअगरo_num);

		अगर (tx_fअगरo_num < 1)
			tx_fअगरo_num = 1;
		अन्यथा
			tx_fअगरo_num = MAX_TX_FIFOS;

		DBG_PRINT(ERR_DBG, "Default to %d tx fifos\n", tx_fअगरo_num);
	पूर्ण

	अगर (multiq)
		*dev_multiq = multiq;

	अगर (tx_steering_type && (1 == tx_fअगरo_num)) अणु
		अगर (tx_steering_type != TX_DEFAULT_STEERING)
			DBG_PRINT(ERR_DBG,
				  "Tx steering is not supported with "
				  "one fifo. Disabling Tx steering.\n");
		tx_steering_type = NO_STEERING;
	पूर्ण

	अगर ((tx_steering_type < NO_STEERING) ||
	    (tx_steering_type > TX_DEFAULT_STEERING)) अणु
		DBG_PRINT(ERR_DBG,
			  "Requested transmit steering not supported\n");
		DBG_PRINT(ERR_DBG, "Disabling transmit steering\n");
		tx_steering_type = NO_STEERING;
	पूर्ण

	अगर (rx_ring_num > MAX_RX_RINGS) अणु
		DBG_PRINT(ERR_DBG,
			  "Requested number of rx rings not supported\n");
		DBG_PRINT(ERR_DBG, "Default to %d rx rings\n",
			  MAX_RX_RINGS);
		rx_ring_num = MAX_RX_RINGS;
	पूर्ण

	अगर ((*dev_पूर्णांकr_type != INTA) && (*dev_पूर्णांकr_type != MSI_X)) अणु
		DBG_PRINT(ERR_DBG, "Wrong intr_type requested. "
			  "Defaulting to INTA\n");
		*dev_पूर्णांकr_type = INTA;
	पूर्ण

	अगर ((*dev_पूर्णांकr_type == MSI_X) &&
	    ((pdev->device != PCI_DEVICE_ID_HERC_WIN) &&
	     (pdev->device != PCI_DEVICE_ID_HERC_UNI))) अणु
		DBG_PRINT(ERR_DBG, "Xframe I does not support MSI_X. "
			  "Defaulting to INTA\n");
		*dev_पूर्णांकr_type = INTA;
	पूर्ण

	अगर ((rx_ring_mode != 1) && (rx_ring_mode != 2)) अणु
		DBG_PRINT(ERR_DBG, "Requested ring mode not supported\n");
		DBG_PRINT(ERR_DBG, "Defaulting to 1-buffer mode\n");
		rx_ring_mode = 1;
	पूर्ण

	क्रम (i = 0; i < MAX_RX_RINGS; i++)
		अगर (rx_ring_sz[i] > MAX_RX_BLOCKS_PER_RING) अणु
			DBG_PRINT(ERR_DBG, "Requested rx ring size not "
				  "supported\nDefaulting to %d\n",
				  MAX_RX_BLOCKS_PER_RING);
			rx_ring_sz[i] = MAX_RX_BLOCKS_PER_RING;
		पूर्ण

	वापस SUCCESS;
पूर्ण

/**
 * rts_ds_steer - Receive traffic steering based on IPv4 or IPv6 TOS or Traffic class respectively.
 * @nic: device निजी variable
 * @ds_codepoपूर्णांक: data
 * @ring: ring index
 * Description: The function configures the receive steering to
 * desired receive ring.
 * Return Value:  SUCCESS on success and
 * '-1' on failure (endian settings incorrect).
 */
अटल पूर्णांक rts_ds_steer(काष्ठा s2io_nic *nic, u8 ds_codepoपूर्णांक, u8 ring)
अणु
	काष्ठा XENA_dev_config __iomem *bar0 = nic->bar0;
	रेजिस्टर u64 val64 = 0;

	अगर (ds_codepoपूर्णांक > 63)
		वापस FAILURE;

	val64 = RTS_DS_MEM_DATA(ring);
	ग_लिखोq(val64, &bar0->rts_ds_mem_data);

	val64 = RTS_DS_MEM_CTRL_WE |
		RTS_DS_MEM_CTRL_STROBE_NEW_CMD |
		RTS_DS_MEM_CTRL_OFFSET(ds_codepoपूर्णांक);

	ग_लिखोq(val64, &bar0->rts_ds_mem_ctrl);

	वापस रुको_क्रम_cmd_complete(&bar0->rts_ds_mem_ctrl,
				     RTS_DS_MEM_CTRL_STROBE_CMD_BEING_EXECUTED,
				     S2IO_BIT_RESET, true);
पूर्ण

अटल स्थिर काष्ठा net_device_ops s2io_netdev_ops = अणु
	.nकरो_खोलो	        = s2io_खोलो,
	.nकरो_stop	        = s2io_बंद,
	.nकरो_get_stats	        = s2io_get_stats,
	.nकरो_start_xmit    	= s2io_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= s2io_nकरो_set_multicast,
	.nकरो_करो_ioctl	   	= s2io_ioctl,
	.nकरो_set_mac_address    = s2io_set_mac_addr,
	.nकरो_change_mtu	   	= s2io_change_mtu,
	.nकरो_set_features	= s2io_set_features,
	.nकरो_tx_समयout	   	= s2io_tx_watchकरोg,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller    = s2io_netpoll,
#पूर्ण_अगर
पूर्ण;

/**
 *  s2io_init_nic - Initialization of the adapter .
 *  @pdev : काष्ठाure containing the PCI related inक्रमmation of the device.
 *  @pre: List of PCI devices supported by the driver listed in s2io_tbl.
 *  Description:
 *  The function initializes an adapter identअगरied by the pci_dec काष्ठाure.
 *  All OS related initialization including memory and device काष्ठाure and
 *  initlaization of the device निजी variable is करोne. Also the swapper
 *  control रेजिस्टर is initialized to enable पढ़ो and ग_लिखो पूर्णांकo the I/O
 *  रेजिस्टरs of the device.
 *  Return value:
 *  वापसs 0 on success and negative on failure.
 */

अटल पूर्णांक
s2io_init_nic(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *pre)
अणु
	काष्ठा s2io_nic *sp;
	काष्ठा net_device *dev;
	पूर्णांक i, j, ret;
	पूर्णांक dma_flag = false;
	u32 mac_up, mac_करोwn;
	u64 val64 = 0, पंचांगp64 = 0;
	काष्ठा XENA_dev_config __iomem *bar0 = शून्य;
	u16 subid;
	काष्ठा config_param *config;
	काष्ठा mac_info *mac_control;
	पूर्णांक mode;
	u8 dev_पूर्णांकr_type = पूर्णांकr_type;
	u8 dev_multiq = 0;

	ret = s2io_verअगरy_parm(pdev, &dev_पूर्णांकr_type, &dev_multiq);
	अगर (ret)
		वापस ret;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		DBG_PRINT(ERR_DBG,
			  "%s: pci_enable_device failed\n", __func__);
		वापस ret;
	पूर्ण

	अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
		DBG_PRINT(INIT_DBG, "%s: Using 64bit DMA\n", __func__);
		dma_flag = true;
		अगर (dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
			DBG_PRINT(ERR_DBG,
				  "Unable to obtain 64bit DMA for coherent allocations\n");
			pci_disable_device(pdev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		DBG_PRINT(INIT_DBG, "%s: Using 32bit DMA\n", __func__);
	पूर्ण अन्यथा अणु
		pci_disable_device(pdev);
		वापस -ENOMEM;
	पूर्ण
	ret = pci_request_regions(pdev, s2io_driver_name);
	अगर (ret) अणु
		DBG_PRINT(ERR_DBG, "%s: Request Regions failed - %x\n",
			  __func__, ret);
		pci_disable_device(pdev);
		वापस -ENODEV;
	पूर्ण
	अगर (dev_multiq)
		dev = alloc_etherdev_mq(माप(काष्ठा s2io_nic), tx_fअगरo_num);
	अन्यथा
		dev = alloc_etherdev(माप(काष्ठा s2io_nic));
	अगर (dev == शून्य) अणु
		pci_disable_device(pdev);
		pci_release_regions(pdev);
		वापस -ENODEV;
	पूर्ण

	pci_set_master(pdev);
	pci_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	/*  Private member variable initialized to s2io NIC काष्ठाure */
	sp = netdev_priv(dev);
	sp->dev = dev;
	sp->pdev = pdev;
	sp->high_dma_flag = dma_flag;
	sp->device_enabled_once = false;
	अगर (rx_ring_mode == 1)
		sp->rxd_mode = RXD_MODE_1;
	अगर (rx_ring_mode == 2)
		sp->rxd_mode = RXD_MODE_3B;

	sp->config.पूर्णांकr_type = dev_पूर्णांकr_type;

	अगर ((pdev->device == PCI_DEVICE_ID_HERC_WIN) ||
	    (pdev->device == PCI_DEVICE_ID_HERC_UNI))
		sp->device_type = XFRAME_II_DEVICE;
	अन्यथा
		sp->device_type = XFRAME_I_DEVICE;


	/* Initialize some PCI/PCI-X fields of the NIC. */
	s2io_init_pci(sp);

	/*
	 * Setting the device configuration parameters.
	 * Most of these parameters can be specअगरied by the user during
	 * module insertion as they are module loadable parameters. If
	 * these parameters are not not specअगरied during load समय, they
	 * are initialized with शेष values.
	 */
	config = &sp->config;
	mac_control = &sp->mac_control;

	config->napi = napi;
	config->tx_steering_type = tx_steering_type;

	/* Tx side parameters. */
	अगर (config->tx_steering_type == TX_PRIORITY_STEERING)
		config->tx_fअगरo_num = MAX_TX_FIFOS;
	अन्यथा
		config->tx_fअगरo_num = tx_fअगरo_num;

	/* Initialize the fअगरos used क्रम tx steering */
	अगर (config->tx_fअगरo_num < 5) अणु
		अगर (config->tx_fअगरo_num  == 1)
			sp->total_tcp_fअगरos = 1;
		अन्यथा
			sp->total_tcp_fअगरos = config->tx_fअगरo_num - 1;
		sp->udp_fअगरo_idx = config->tx_fअगरo_num - 1;
		sp->total_udp_fअगरos = 1;
		sp->other_fअगरo_idx = sp->total_tcp_fअगरos - 1;
	पूर्ण अन्यथा अणु
		sp->total_tcp_fअगरos = (tx_fअगरo_num - FIFO_UDP_MAX_NUM -
				       FIFO_OTHER_MAX_NUM);
		sp->udp_fअगरo_idx = sp->total_tcp_fअगरos;
		sp->total_udp_fअगरos = FIFO_UDP_MAX_NUM;
		sp->other_fअगरo_idx = sp->udp_fअगरo_idx + FIFO_UDP_MAX_NUM;
	पूर्ण

	config->multiq = dev_multiq;
	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];

		tx_cfg->fअगरo_len = tx_fअगरo_len[i];
		tx_cfg->fअगरo_priority = i;
	पूर्ण

	/* mapping the QoS priority to the configured fअगरos */
	क्रम (i = 0; i < MAX_TX_FIFOS; i++)
		config->fअगरo_mapping[i] = fअगरo_map[config->tx_fअगरo_num - 1][i];

	/* map the hashing selector table to the configured fअगरos */
	क्रम (i = 0; i < config->tx_fअगरo_num; i++)
		sp->fअगरo_selector[i] = fअगरo_selector[i];


	config->tx_पूर्णांकr_type = TXD_INT_TYPE_UTILZ;
	क्रम (i = 0; i < config->tx_fअगरo_num; i++) अणु
		काष्ठा tx_fअगरo_config *tx_cfg = &config->tx_cfg[i];

		tx_cfg->f_no_snoop = (NO_SNOOP_TXD | NO_SNOOP_TXD_BUFFER);
		अगर (tx_cfg->fअगरo_len < 65) अणु
			config->tx_पूर्णांकr_type = TXD_INT_TYPE_PER_LIST;
			अवरोध;
		पूर्ण
	पूर्ण
	/* + 2 because one Txd क्रम skb->data and one Txd क्रम UFO */
	config->max_txds = MAX_SKB_FRAGS + 2;

	/* Rx side parameters. */
	config->rx_ring_num = rx_ring_num;
	क्रम (i = 0; i < config->rx_ring_num; i++) अणु
		काष्ठा rx_ring_config *rx_cfg = &config->rx_cfg[i];
		काष्ठा ring_info *ring = &mac_control->rings[i];

		rx_cfg->num_rxd = rx_ring_sz[i] * (rxd_count[sp->rxd_mode] + 1);
		rx_cfg->ring_priority = i;
		ring->rx_bufs_left = 0;
		ring->rxd_mode = sp->rxd_mode;
		ring->rxd_count = rxd_count[sp->rxd_mode];
		ring->pdev = sp->pdev;
		ring->dev = sp->dev;
	पूर्ण

	क्रम (i = 0; i < rx_ring_num; i++) अणु
		काष्ठा rx_ring_config *rx_cfg = &config->rx_cfg[i];

		rx_cfg->ring_org = RING_ORG_BUFF1;
		rx_cfg->f_no_snoop = (NO_SNOOP_RXD | NO_SNOOP_RXD_BUFFER);
	पूर्ण

	/*  Setting Mac Control parameters */
	mac_control->rmac_छोड़ो_समय = rmac_छोड़ो_समय;
	mac_control->mc_छोड़ो_threshold_q0q3 = mc_छोड़ो_threshold_q0q3;
	mac_control->mc_छोड़ो_threshold_q4q7 = mc_छोड़ो_threshold_q4q7;


	/*  initialize the shared memory used by the NIC and the host */
	अगर (init_shared_mem(sp)) अणु
		DBG_PRINT(ERR_DBG, "%s: Memory allocation failed\n", dev->name);
		ret = -ENOMEM;
		जाओ mem_alloc_failed;
	पूर्ण

	sp->bar0 = pci_ioremap_bar(pdev, 0);
	अगर (!sp->bar0) अणु
		DBG_PRINT(ERR_DBG, "%s: Neterion: cannot remap io mem1\n",
			  dev->name);
		ret = -ENOMEM;
		जाओ bar0_remap_failed;
	पूर्ण

	sp->bar1 = pci_ioremap_bar(pdev, 2);
	अगर (!sp->bar1) अणु
		DBG_PRINT(ERR_DBG, "%s: Neterion: cannot remap io mem2\n",
			  dev->name);
		ret = -ENOMEM;
		जाओ bar1_remap_failed;
	पूर्ण

	/* Initializing the BAR1 address as the start of the FIFO poपूर्णांकer. */
	क्रम (j = 0; j < MAX_TX_FIFOS; j++) अणु
		mac_control->tx_FIFO_start[j] = sp->bar1 + (j * 0x00020000);
	पूर्ण

	/*  Driver entry poपूर्णांकs */
	dev->netdev_ops = &s2io_netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	dev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM |
		NETIF_F_TSO | NETIF_F_TSO6 |
		NETIF_F_RXCSUM | NETIF_F_LRO;
	dev->features |= dev->hw_features |
		NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
	अगर (sp->high_dma_flag == true)
		dev->features |= NETIF_F_HIGHDMA;
	dev->watchकरोg_समयo = WATCH_DOG_TIMEOUT;
	INIT_WORK(&sp->rst_समयr_task, s2io_restart_nic);
	INIT_WORK(&sp->set_link_task, s2io_set_link);

	pci_save_state(sp->pdev);

	/* Setting swapper control on the NIC, क्रम proper reset operation */
	अगर (s2io_set_swapper(sp)) अणु
		DBG_PRINT(ERR_DBG, "%s: swapper settings are wrong\n",
			  dev->name);
		ret = -EAGAIN;
		जाओ set_swap_failed;
	पूर्ण

	/* Verअगरy अगर the Herc works on the slot its placed पूर्णांकo */
	अगर (sp->device_type & XFRAME_II_DEVICE) अणु
		mode = s2io_verअगरy_pci_mode(sp);
		अगर (mode < 0) अणु
			DBG_PRINT(ERR_DBG, "%s: Unsupported PCI bus mode\n",
				  __func__);
			ret = -EBADSLT;
			जाओ set_swap_failed;
		पूर्ण
	पूर्ण

	अगर (sp->config.पूर्णांकr_type == MSI_X) अणु
		sp->num_entries = config->rx_ring_num + 1;
		ret = s2io_enable_msi_x(sp);

		अगर (!ret) अणु
			ret = s2io_test_msi(sp);
			/* rollback MSI-X, will re-enable during add_isr() */
			हटाओ_msix_isr(sp);
		पूर्ण
		अगर (ret) अणु

			DBG_PRINT(ERR_DBG,
				  "MSI-X requested but failed to enable\n");
			sp->config.पूर्णांकr_type = INTA;
		पूर्ण
	पूर्ण

	अगर (config->पूर्णांकr_type ==  MSI_X) अणु
		क्रम (i = 0; i < config->rx_ring_num ; i++) अणु
			काष्ठा ring_info *ring = &mac_control->rings[i];

			netअगर_napi_add(dev, &ring->napi, s2io_poll_msix, 64);
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_napi_add(dev, &sp->napi, s2io_poll_पूर्णांकa, 64);
	पूर्ण

	/* Not needed क्रम Herc */
	अगर (sp->device_type & XFRAME_I_DEVICE) अणु
		/*
		 * Fix क्रम all "FFs" MAC address problems observed on
		 * Alpha platक्रमms
		 */
		fix_mac_address(sp);
		s2io_reset(sp);
	पूर्ण

	/*
	 * MAC address initialization.
	 * For now only one mac address will be पढ़ो and used.
	 */
	bar0 = sp->bar0;
	val64 = RMAC_ADDR_CMD_MEM_RD | RMAC_ADDR_CMD_MEM_STROBE_NEW_CMD |
		RMAC_ADDR_CMD_MEM_OFFSET(0 + S2IO_MAC_ADDR_START_OFFSET);
	ग_लिखोq(val64, &bar0->rmac_addr_cmd_mem);
	रुको_क्रम_cmd_complete(&bar0->rmac_addr_cmd_mem,
			      RMAC_ADDR_CMD_MEM_STROBE_CMD_EXECUTING,
			      S2IO_BIT_RESET, true);
	पंचांगp64 = पढ़ोq(&bar0->rmac_addr_data0_mem);
	mac_करोwn = (u32)पंचांगp64;
	mac_up = (u32) (पंचांगp64 >> 32);

	sp->def_mac_addr[0].mac_addr[3] = (u8) (mac_up);
	sp->def_mac_addr[0].mac_addr[2] = (u8) (mac_up >> 8);
	sp->def_mac_addr[0].mac_addr[1] = (u8) (mac_up >> 16);
	sp->def_mac_addr[0].mac_addr[0] = (u8) (mac_up >> 24);
	sp->def_mac_addr[0].mac_addr[5] = (u8) (mac_करोwn >> 16);
	sp->def_mac_addr[0].mac_addr[4] = (u8) (mac_करोwn >> 24);

	/*  Set the factory defined MAC address initially   */
	dev->addr_len = ETH_ALEN;
	स_नकल(dev->dev_addr, sp->def_mac_addr, ETH_ALEN);

	/* initialize number of multicast & unicast MAC entries variables */
	अगर (sp->device_type == XFRAME_I_DEVICE) अणु
		config->max_mc_addr = S2IO_XENA_MAX_MC_ADDRESSES;
		config->max_mac_addr = S2IO_XENA_MAX_MAC_ADDRESSES;
		config->mc_start_offset = S2IO_XENA_MC_ADDR_START_OFFSET;
	पूर्ण अन्यथा अगर (sp->device_type == XFRAME_II_DEVICE) अणु
		config->max_mc_addr = S2IO_HERC_MAX_MC_ADDRESSES;
		config->max_mac_addr = S2IO_HERC_MAX_MAC_ADDRESSES;
		config->mc_start_offset = S2IO_HERC_MC_ADDR_START_OFFSET;
	पूर्ण

	/* MTU range: 46 - 9600 */
	dev->min_mtu = MIN_MTU;
	dev->max_mtu = S2IO_JUMBO_SIZE;

	/* store mac addresses from CAM to s2io_nic काष्ठाure */
	करो_s2io_store_unicast_mc(sp);

	/* Configure MSIX vector क्रम number of rings configured plus one */
	अगर ((sp->device_type == XFRAME_II_DEVICE) &&
	    (config->पूर्णांकr_type == MSI_X))
		sp->num_entries = config->rx_ring_num + 1;

	/* Store the values of the MSIX table in the s2io_nic काष्ठाure */
	store_xmsi_data(sp);
	/* reset Nic and bring it to known state */
	s2io_reset(sp);

	/*
	 * Initialize link state flags
	 * and the card state parameter
	 */
	sp->state = 0;

	/* Initialize spinlocks */
	क्रम (i = 0; i < sp->config.tx_fअगरo_num; i++) अणु
		काष्ठा fअगरo_info *fअगरo = &mac_control->fअगरos[i];

		spin_lock_init(&fअगरo->tx_lock);
	पूर्ण

	/*
	 * SXE-002: Configure link and activity LED to init state
	 * on driver load.
	 */
	subid = sp->pdev->subप्रणाली_device;
	अगर ((subid & 0xFF) >= 0x07) अणु
		val64 = पढ़ोq(&bar0->gpio_control);
		val64 |= 0x0000800000000000ULL;
		ग_लिखोq(val64, &bar0->gpio_control);
		val64 = 0x0411040400000000ULL;
		ग_लिखोq(val64, (व्योम __iomem *)bar0 + 0x2700);
		val64 = पढ़ोq(&bar0->gpio_control);
	पूर्ण

	sp->rx_csum = 1;	/* Rx chksum verअगरy enabled by शेष */

	अगर (रेजिस्टर_netdev(dev)) अणु
		DBG_PRINT(ERR_DBG, "Device registration failed\n");
		ret = -ENODEV;
		जाओ रेजिस्टर_failed;
	पूर्ण
	s2io_vpd_पढ़ो(sp);
	DBG_PRINT(ERR_DBG, "Copyright(c) 2002-2010 Exar Corp.\n");
	DBG_PRINT(ERR_DBG, "%s: Neterion %s (rev %d)\n", dev->name,
		  sp->product_name, pdev->revision);
	DBG_PRINT(ERR_DBG, "%s: Driver version %s\n", dev->name,
		  s2io_driver_version);
	DBG_PRINT(ERR_DBG, "%s: MAC Address: %pM\n", dev->name, dev->dev_addr);
	DBG_PRINT(ERR_DBG, "Serial number: %s\n", sp->serial_num);
	अगर (sp->device_type & XFRAME_II_DEVICE) अणु
		mode = s2io_prपूर्णांक_pci_mode(sp);
		अगर (mode < 0) अणु
			ret = -EBADSLT;
			unरेजिस्टर_netdev(dev);
			जाओ set_swap_failed;
		पूर्ण
	पूर्ण
	चयन (sp->rxd_mode) अणु
	हाल RXD_MODE_1:
		DBG_PRINT(ERR_DBG, "%s: 1-Buffer receive mode enabled\n",
			  dev->name);
		अवरोध;
	हाल RXD_MODE_3B:
		DBG_PRINT(ERR_DBG, "%s: 2-Buffer receive mode enabled\n",
			  dev->name);
		अवरोध;
	पूर्ण

	चयन (sp->config.napi) अणु
	हाल 0:
		DBG_PRINT(ERR_DBG, "%s: NAPI disabled\n", dev->name);
		अवरोध;
	हाल 1:
		DBG_PRINT(ERR_DBG, "%s: NAPI enabled\n", dev->name);
		अवरोध;
	पूर्ण

	DBG_PRINT(ERR_DBG, "%s: Using %d Tx fifo(s)\n", dev->name,
		  sp->config.tx_fअगरo_num);

	DBG_PRINT(ERR_DBG, "%s: Using %d Rx ring(s)\n", dev->name,
		  sp->config.rx_ring_num);

	चयन (sp->config.पूर्णांकr_type) अणु
	हाल INTA:
		DBG_PRINT(ERR_DBG, "%s: Interrupt type INTA\n", dev->name);
		अवरोध;
	हाल MSI_X:
		DBG_PRINT(ERR_DBG, "%s: Interrupt type MSI-X\n", dev->name);
		अवरोध;
	पूर्ण
	अगर (sp->config.multiq) अणु
		क्रम (i = 0; i < sp->config.tx_fअगरo_num; i++) अणु
			काष्ठा fअगरo_info *fअगरo = &mac_control->fअगरos[i];

			fअगरo->multiq = config->multiq;
		पूर्ण
		DBG_PRINT(ERR_DBG, "%s: Multiqueue support enabled\n",
			  dev->name);
	पूर्ण अन्यथा
		DBG_PRINT(ERR_DBG, "%s: Multiqueue support disabled\n",
			  dev->name);

	चयन (sp->config.tx_steering_type) अणु
	हाल NO_STEERING:
		DBG_PRINT(ERR_DBG, "%s: No steering enabled for transmit\n",
			  dev->name);
		अवरोध;
	हाल TX_PRIORITY_STEERING:
		DBG_PRINT(ERR_DBG,
			  "%s: Priority steering enabled for transmit\n",
			  dev->name);
		अवरोध;
	हाल TX_DEFAULT_STEERING:
		DBG_PRINT(ERR_DBG,
			  "%s: Default steering enabled for transmit\n",
			  dev->name);
	पूर्ण

	DBG_PRINT(ERR_DBG, "%s: Large receive offload enabled\n",
		  dev->name);
	/* Initialize device name */
	snम_लिखो(sp->name, माप(sp->name), "%s Neterion %s", dev->name,
		 sp->product_name);

	अगर (vlan_tag_strip)
		sp->vlan_strip_flag = 1;
	अन्यथा
		sp->vlan_strip_flag = 0;

	/*
	 * Make Link state as off at this poपूर्णांक, when the Link change
	 * पूर्णांकerrupt comes the state will be स्वतःmatically changed to
	 * the right state.
	 */
	netअगर_carrier_off(dev);

	वापस 0;

रेजिस्टर_failed:
set_swap_failed:
	iounmap(sp->bar1);
bar1_remap_failed:
	iounmap(sp->bar0);
bar0_remap_failed:
mem_alloc_failed:
	मुक्त_shared_mem(sp);
	pci_disable_device(pdev);
	pci_release_regions(pdev);
	मुक्त_netdev(dev);

	वापस ret;
पूर्ण

/**
 * s2io_rem_nic - Free the PCI device
 * @pdev: काष्ठाure containing the PCI related inक्रमmation of the device.
 * Description: This function is called by the Pci subप्रणाली to release a
 * PCI device and मुक्त up all resource held up by the device. This could
 * be in response to a Hot plug event or when the driver is to be हटाओd
 * from memory.
 */

अटल व्योम s2io_rem_nic(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा s2io_nic *sp;

	अगर (dev == शून्य) अणु
		DBG_PRINT(ERR_DBG, "Driver Data is NULL!!\n");
		वापस;
	पूर्ण

	sp = netdev_priv(dev);

	cancel_work_sync(&sp->rst_समयr_task);
	cancel_work_sync(&sp->set_link_task);

	unरेजिस्टर_netdev(dev);

	मुक्त_shared_mem(sp);
	iounmap(sp->bar0);
	iounmap(sp->bar1);
	pci_release_regions(pdev);
	मुक्त_netdev(dev);
	pci_disable_device(pdev);
पूर्ण

module_pci_driver(s2io_driver);

अटल पूर्णांक check_L2_lro_capable(u8 *buffer, काष्ठा iphdr **ip,
				काष्ठा tcphdr **tcp, काष्ठा RxD_t *rxdp,
				काष्ठा s2io_nic *sp)
अणु
	पूर्णांक ip_off;
	u8 l2_type = (u8)((rxdp->Control_1 >> 37) & 0x7), ip_len;

	अगर (!(rxdp->Control_1 & RXD_FRAME_PROTO_TCP)) अणु
		DBG_PRINT(INIT_DBG,
			  "%s: Non-TCP frames not supported for LRO\n",
			  __func__);
		वापस -1;
	पूर्ण

	/* Checking क्रम DIX type or DIX type with VLAN */
	अगर ((l2_type == 0) || (l2_type == 4)) अणु
		ip_off = HEADER_ETHERNET_II_802_3_SIZE;
		/*
		 * If vlan stripping is disabled and the frame is VLAN tagged,
		 * shअगरt the offset by the VLAN header size bytes.
		 */
		अगर ((!sp->vlan_strip_flag) &&
		    (rxdp->Control_1 & RXD_FRAME_VLAN_TAG))
			ip_off += HEADER_VLAN_SIZE;
	पूर्ण अन्यथा अणु
		/* LLC, SNAP etc are considered non-mergeable */
		वापस -1;
	पूर्ण

	*ip = (काष्ठा iphdr *)(buffer + ip_off);
	ip_len = (u8)((*ip)->ihl);
	ip_len <<= 2;
	*tcp = (काष्ठा tcphdr *)((अचिन्हित दीर्घ)*ip + ip_len);

	वापस 0;
पूर्ण

अटल पूर्णांक check_क्रम_socket_match(काष्ठा lro *lro, काष्ठा iphdr *ip,
				  काष्ठा tcphdr *tcp)
अणु
	DBG_PRINT(INFO_DBG, "%s: Been here...\n", __func__);
	अगर ((lro->iph->saddr != ip->saddr) ||
	    (lro->iph->daddr != ip->daddr) ||
	    (lro->tcph->source != tcp->source) ||
	    (lro->tcph->dest != tcp->dest))
		वापस -1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_l4_pyld_length(काष्ठा iphdr *ip, काष्ठा tcphdr *tcp)
अणु
	वापस ntohs(ip->tot_len) - (ip->ihl << 2) - (tcp->करोff << 2);
पूर्ण

अटल व्योम initiate_new_session(काष्ठा lro *lro, u8 *l2h,
				 काष्ठा iphdr *ip, काष्ठा tcphdr *tcp,
				 u32 tcp_pyld_len, u16 vlan_tag)
अणु
	DBG_PRINT(INFO_DBG, "%s: Been here...\n", __func__);
	lro->l2h = l2h;
	lro->iph = ip;
	lro->tcph = tcp;
	lro->tcp_next_seq = tcp_pyld_len + ntohl(tcp->seq);
	lro->tcp_ack = tcp->ack_seq;
	lro->sg_num = 1;
	lro->total_len = ntohs(ip->tot_len);
	lro->frags_len = 0;
	lro->vlan_tag = vlan_tag;
	/*
	 * Check अगर we saw TCP बारtamp.
	 * Other consistency checks have alपढ़ोy been करोne.
	 */
	अगर (tcp->करोff == 8) अणु
		__be32 *ptr;
		ptr = (__be32 *)(tcp+1);
		lro->saw_ts = 1;
		lro->cur_tsval = ntohl(*(ptr+1));
		lro->cur_tsecr = *(ptr+2);
	पूर्ण
	lro->in_use = 1;
पूर्ण

अटल व्योम update_L3L4_header(काष्ठा s2io_nic *sp, काष्ठा lro *lro)
अणु
	काष्ठा iphdr *ip = lro->iph;
	काष्ठा tcphdr *tcp = lro->tcph;
	काष्ठा swStat *swstats = &sp->mac_control.stats_info->sw_stat;

	DBG_PRINT(INFO_DBG, "%s: Been here...\n", __func__);

	/* Update L3 header */
	csum_replace2(&ip->check, ip->tot_len, htons(lro->total_len));
	ip->tot_len = htons(lro->total_len);

	/* Update L4 header */
	tcp->ack_seq = lro->tcp_ack;
	tcp->winकरोw = lro->winकरोw;

	/* Update tsecr field अगर this session has बारtamps enabled */
	अगर (lro->saw_ts) अणु
		__be32 *ptr = (__be32 *)(tcp + 1);
		*(ptr+2) = lro->cur_tsecr;
	पूर्ण

	/* Update counters required क्रम calculation of
	 * average no. of packets aggregated.
	 */
	swstats->sum_avg_pkts_aggregated += lro->sg_num;
	swstats->num_aggregations++;
पूर्ण

अटल व्योम aggregate_new_rx(काष्ठा lro *lro, काष्ठा iphdr *ip,
			     काष्ठा tcphdr *tcp, u32 l4_pyld)
अणु
	DBG_PRINT(INFO_DBG, "%s: Been here...\n", __func__);
	lro->total_len += l4_pyld;
	lro->frags_len += l4_pyld;
	lro->tcp_next_seq += l4_pyld;
	lro->sg_num++;

	/* Update ack seq no. and winकरोw ad(from this pkt) in LRO object */
	lro->tcp_ack = tcp->ack_seq;
	lro->winकरोw = tcp->winकरोw;

	अगर (lro->saw_ts) अणु
		__be32 *ptr;
		/* Update tsecr and tsval from this packet */
		ptr = (__be32 *)(tcp+1);
		lro->cur_tsval = ntohl(*(ptr+1));
		lro->cur_tsecr = *(ptr + 2);
	पूर्ण
पूर्ण

अटल पूर्णांक verअगरy_l3_l4_lro_capable(काष्ठा lro *l_lro, काष्ठा iphdr *ip,
				    काष्ठा tcphdr *tcp, u32 tcp_pyld_len)
अणु
	u8 *ptr;

	DBG_PRINT(INFO_DBG, "%s: Been here...\n", __func__);

	अगर (!tcp_pyld_len) अणु
		/* Runt frame or a pure ack */
		वापस -1;
	पूर्ण

	अगर (ip->ihl != 5) /* IP has options */
		वापस -1;

	/* If we see CE codepoपूर्णांक in IP header, packet is not mergeable */
	अगर (INET_ECN_is_ce(ipv4_get_dsfield(ip)))
		वापस -1;

	/* If we see ECE or CWR flags in TCP header, packet is not mergeable */
	अगर (tcp->urg || tcp->psh || tcp->rst ||
	    tcp->syn || tcp->fin ||
	    tcp->ece || tcp->cwr || !tcp->ack) अणु
		/*
		 * Currently recognize only the ack control word and
		 * any other control field being set would result in
		 * flushing the LRO session
		 */
		वापस -1;
	पूर्ण

	/*
	 * Allow only one TCP बारtamp option. Don't aggregate अगर
	 * any other options are detected.
	 */
	अगर (tcp->करोff != 5 && tcp->करोff != 8)
		वापस -1;

	अगर (tcp->करोff == 8) अणु
		ptr = (u8 *)(tcp + 1);
		जबतक (*ptr == TCPOPT_NOP)
			ptr++;
		अगर (*ptr != TCPOPT_TIMESTAMP || *(ptr+1) != TCPOLEN_TIMESTAMP)
			वापस -1;

		/* Ensure बारtamp value increases monotonically */
		अगर (l_lro)
			अगर (l_lro->cur_tsval > ntohl(*((__be32 *)(ptr+2))))
				वापस -1;

		/* बारtamp echo reply should be non-zero */
		अगर (*((__be32 *)(ptr+6)) == 0)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s2io_club_tcp_session(काष्ठा ring_info *ring_data, u8 *buffer,
				 u8 **tcp, u32 *tcp_len, काष्ठा lro **lro,
				 काष्ठा RxD_t *rxdp, काष्ठा s2io_nic *sp)
अणु
	काष्ठा iphdr *ip;
	काष्ठा tcphdr *tcph;
	पूर्णांक ret = 0, i;
	u16 vlan_tag = 0;
	काष्ठा swStat *swstats = &sp->mac_control.stats_info->sw_stat;

	ret = check_L2_lro_capable(buffer, &ip, (काष्ठा tcphdr **)tcp,
				   rxdp, sp);
	अगर (ret)
		वापस ret;

	DBG_PRINT(INFO_DBG, "IP Saddr: %x Daddr: %x\n", ip->saddr, ip->daddr);

	vlan_tag = RXD_GET_VLAN_TAG(rxdp->Control_2);
	tcph = (काष्ठा tcphdr *)*tcp;
	*tcp_len = get_l4_pyld_length(ip, tcph);
	क्रम (i = 0; i < MAX_LRO_SESSIONS; i++) अणु
		काष्ठा lro *l_lro = &ring_data->lro0_n[i];
		अगर (l_lro->in_use) अणु
			अगर (check_क्रम_socket_match(l_lro, ip, tcph))
				जारी;
			/* Sock pair matched */
			*lro = l_lro;

			अगर ((*lro)->tcp_next_seq != ntohl(tcph->seq)) अणु
				DBG_PRINT(INFO_DBG, "%s: Out of sequence. "
					  "expected 0x%x, actual 0x%x\n",
					  __func__,
					  (*lro)->tcp_next_seq,
					  ntohl(tcph->seq));

				swstats->outof_sequence_pkts++;
				ret = 2;
				अवरोध;
			पूर्ण

			अगर (!verअगरy_l3_l4_lro_capable(l_lro, ip, tcph,
						      *tcp_len))
				ret = 1; /* Aggregate */
			अन्यथा
				ret = 2; /* Flush both */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret == 0) अणु
		/* Beक्रमe searching क्रम available LRO objects,
		 * check अगर the pkt is L3/L4 aggregatable. If not
		 * करोn't create new LRO session. Just send this
		 * packet up.
		 */
		अगर (verअगरy_l3_l4_lro_capable(शून्य, ip, tcph, *tcp_len))
			वापस 5;

		क्रम (i = 0; i < MAX_LRO_SESSIONS; i++) अणु
			काष्ठा lro *l_lro = &ring_data->lro0_n[i];
			अगर (!(l_lro->in_use)) अणु
				*lro = l_lro;
				ret = 3; /* Begin anew */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ret == 0) अणु /* sessions exceeded */
		DBG_PRINT(INFO_DBG, "%s: All LRO sessions already in use\n",
			  __func__);
		*lro = शून्य;
		वापस ret;
	पूर्ण

	चयन (ret) अणु
	हाल 3:
		initiate_new_session(*lro, buffer, ip, tcph, *tcp_len,
				     vlan_tag);
		अवरोध;
	हाल 2:
		update_L3L4_header(sp, *lro);
		अवरोध;
	हाल 1:
		aggregate_new_rx(*lro, ip, tcph, *tcp_len);
		अगर ((*lro)->sg_num == sp->lro_max_aggr_per_sess) अणु
			update_L3L4_header(sp, *lro);
			ret = 4; /* Flush the LRO */
		पूर्ण
		अवरोध;
	शेष:
		DBG_PRINT(ERR_DBG, "%s: Don't know, can't say!!\n", __func__);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम clear_lro_session(काष्ठा lro *lro)
अणु
	अटल u16 lro_काष्ठा_size = माप(काष्ठा lro);

	स_रखो(lro, 0, lro_काष्ठा_size);
पूर्ण

अटल व्योम queue_rx_frame(काष्ठा sk_buff *skb, u16 vlan_tag)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा s2io_nic *sp = netdev_priv(dev);

	skb->protocol = eth_type_trans(skb, dev);
	अगर (vlan_tag && sp->vlan_strip_flag)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);
	अगर (sp->config.napi)
		netअगर_receive_skb(skb);
	अन्यथा
		netअगर_rx(skb);
पूर्ण

अटल व्योम lro_append_pkt(काष्ठा s2io_nic *sp, काष्ठा lro *lro,
			   काष्ठा sk_buff *skb, u32 tcp_len)
अणु
	काष्ठा sk_buff *first = lro->parent;
	काष्ठा swStat *swstats = &sp->mac_control.stats_info->sw_stat;

	first->len += tcp_len;
	first->data_len = lro->frags_len;
	skb_pull(skb, (skb->len - tcp_len));
	अगर (skb_shinfo(first)->frag_list)
		lro->last_frag->next = skb;
	अन्यथा
		skb_shinfo(first)->frag_list = skb;
	first->truesize += skb->truesize;
	lro->last_frag = skb;
	swstats->clubbed_frms_cnt++;
पूर्ण

/**
 * s2io_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t s2io_io_error_detected(काष्ठा pci_dev *pdev,
					       pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा s2io_nic *sp = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev)) अणु
		/* Bring करोwn the card, जबतक aव्योमing PCI I/O */
		करो_s2io_card_करोwn(sp, 0);
	पूर्ण
	pci_disable_device(pdev);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * s2io_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot.
 * At this poपूर्णांक, the card has exprienced a hard reset,
 * followed by fixups by BIOS, and has its config space
 * set up identically to what it was at cold boot.
 */
अटल pci_ers_result_t s2io_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा s2io_nic *sp = netdev_priv(netdev);

	अगर (pci_enable_device(pdev)) अणु
		pr_err("Cannot re-enable PCI device after reset.\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	pci_set_master(pdev);
	s2io_reset(sp);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * s2io_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells
 * us that its OK to resume normal operation.
 */
अटल व्योम s2io_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा s2io_nic *sp = netdev_priv(netdev);

	अगर (netअगर_running(netdev)) अणु
		अगर (s2io_card_up(sp)) अणु
			pr_err("Can't bring device back up after reset.\n");
			वापस;
		पूर्ण

		अगर (s2io_set_mac_addr(netdev, netdev->dev_addr) == FAILURE) अणु
			s2io_card_करोwn(sp);
			pr_err("Can't restore mac addr after reset.\n");
			वापस;
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);
	netअगर_tx_wake_all_queues(netdev);
पूर्ण
