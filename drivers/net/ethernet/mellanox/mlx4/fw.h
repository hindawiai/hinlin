<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2006, 2007 Cisco Systems.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित MLX4_FW_H
#घोषणा MLX4_FW_H

#समावेश "mlx4.h"
#समावेश "icm.h"

काष्ठा mlx4_mod_stat_cfg अणु
	u8 log_pg_sz;
	u8 log_pg_sz_m;
पूर्ण;

काष्ठा mlx4_port_cap अणु
	u8  link_state;
	u8  supported_port_types;
	u8  suggested_type;
	u8  शेष_sense;
	u8  log_max_macs;
	u8  log_max_vlans;
	पूर्णांक ib_mtu;
	पूर्णांक max_port_width;
	पूर्णांक max_vl;
	पूर्णांक max_tc_eth;
	पूर्णांक max_gids;
	पूर्णांक max_pkeys;
	u64 def_mac;
	u16 eth_mtu;
	पूर्णांक trans_type;
	पूर्णांक venकरोr_oui;
	u16 wavelength;
	u64 trans_code;
	u8 dmfs_optimized_state;
पूर्ण;

काष्ठा mlx4_dev_cap अणु
	पूर्णांक max_srq_sz;
	पूर्णांक max_qp_sz;
	पूर्णांक reserved_qps;
	पूर्णांक max_qps;
	पूर्णांक reserved_srqs;
	पूर्णांक max_srqs;
	पूर्णांक max_cq_sz;
	पूर्णांक reserved_cqs;
	पूर्णांक max_cqs;
	पूर्णांक max_mpts;
	पूर्णांक reserved_eqs;
	पूर्णांक max_eqs;
	पूर्णांक num_sys_eqs;
	पूर्णांक reserved_mtts;
	पूर्णांक reserved_mrws;
	पूर्णांक max_requester_per_qp;
	पूर्णांक max_responder_per_qp;
	पूर्णांक max_rdma_global;
	पूर्णांक local_ca_ack_delay;
	पूर्णांक num_ports;
	u32 max_msg_sz;
	u16 stat_rate_support;
	पूर्णांक fs_log_max_ucast_qp_range_size;
	पूर्णांक fs_max_num_qp_per_entry;
	u64 flags;
	u64 flags2;
	पूर्णांक reserved_uars;
	पूर्णांक uar_size;
	पूर्णांक min_page_sz;
	पूर्णांक bf_reg_size;
	पूर्णांक bf_regs_per_page;
	पूर्णांक max_sq_sg;
	पूर्णांक max_sq_desc_sz;
	पूर्णांक max_rq_sg;
	पूर्णांक max_rq_desc_sz;
	पूर्णांक max_qp_per_mcg;
	पूर्णांक reserved_mgms;
	पूर्णांक max_mcgs;
	पूर्णांक reserved_pds;
	पूर्णांक max_pds;
	पूर्णांक reserved_xrcds;
	पूर्णांक max_xrcds;
	पूर्णांक qpc_entry_sz;
	पूर्णांक rdmarc_entry_sz;
	पूर्णांक altc_entry_sz;
	पूर्णांक aux_entry_sz;
	पूर्णांक srq_entry_sz;
	पूर्णांक cqc_entry_sz;
	पूर्णांक eqc_entry_sz;
	पूर्णांक dmpt_entry_sz;
	पूर्णांक cmpt_entry_sz;
	पूर्णांक mtt_entry_sz;
	पूर्णांक resize_srq;
	u32 bmme_flags;
	u32 reserved_lkey;
	u64 max_icm_sz;
	पूर्णांक max_gso_sz;
	पूर्णांक max_rss_tbl_sz;
	u32 max_counters;
	u32 dmfs_high_rate_qpn_base;
	u32 dmfs_high_rate_qpn_range;
	काष्ठा mlx4_rate_limit_caps rl_caps;
	u32 health_buffer_addrs;
	काष्ठा mlx4_port_cap port_cap[MLX4_MAX_PORTS + 1];
	bool wol_port[MLX4_MAX_PORTS + 1];
	bool map_घड़ी_प्रकारo_user;
पूर्ण;

काष्ठा mlx4_func_cap अणु
	u8	num_ports;
	u8	flags;
	u32	pf_context_behaviour;
	पूर्णांक	qp_quota;
	पूर्णांक	cq_quota;
	पूर्णांक	srq_quota;
	पूर्णांक	mpt_quota;
	पूर्णांक	mtt_quota;
	पूर्णांक	max_eq;
	पूर्णांक	reserved_eq;
	पूर्णांक	mcg_quota;
	काष्ठा mlx4_spec_qps spec_qps;
	u32	reserved_lkey;
	u8	physical_port;
	u8	flags0;
	u8	flags1;
	u64	phys_port_id;
	u32	extra_flags;
पूर्ण;

काष्ठा mlx4_func अणु
	पूर्णांक	bus;
	पूर्णांक	device;
	पूर्णांक	function;
	पूर्णांक	physical_function;
	पूर्णांक	rsvd_eqs;
	पूर्णांक	max_eq;
	पूर्णांक	rsvd_uars;
पूर्ण;

काष्ठा mlx4_adapter अणु
	अक्षर board_id[MLX4_BOARD_ID_LEN];
	u8   पूर्णांकa_pin;
पूर्ण;

काष्ठा mlx4_init_hca_param अणु
	u64 qpc_base;
	u64 rdmarc_base;
	u64 auxc_base;
	u64 altc_base;
	u64 srqc_base;
	u64 cqc_base;
	u64 eqc_base;
	u64 mc_base;
	u64 dmpt_base;
	u64 cmpt_base;
	u64 mtt_base;
	u64 global_caps;
	u8 log_mc_entry_sz;
	u8 log_mc_hash_sz;
	u16 hca_core_घड़ी; /* Internal Clock Frequency (in MHz) */
	u8  log_num_qps;
	u8  log_num_srqs;
	u8  log_num_cqs;
	u8  log_num_eqs;
	u16 num_sys_eqs;
	u8  log_rd_per_qp;
	u8  log_mc_table_sz;
	u8  log_mpt_sz;
	u8  log_uar_sz;
	u8  mw_enabled;  /* Enable memory winकरोws */
	u8  uar_page_sz; /* log pg sz in 4k chunks */
	u8  steering_mode; /* क्रम QUERY_HCA */
	u8  dmfs_high_steer_mode; /* क्रम QUERY_HCA */
	u64 dev_cap_enabled;
	u16 cqe_size; /* For use only when CQE stride feature enabled */
	u16 eqe_size; /* For use only when EQE stride feature enabled */
	u8 rss_ip_frags;
	u8 phv_check_en; /* क्रम QUERY_HCA */
पूर्ण;

काष्ठा mlx4_init_ib_param अणु
	पूर्णांक port_width;
	पूर्णांक vl_cap;
	पूर्णांक mtu_cap;
	u16 gid_cap;
	u16 pkey_cap;
	पूर्णांक set_guid0;
	u64 guid0;
	पूर्णांक set_node_guid;
	u64 node_guid;
	पूर्णांक set_si_guid;
	u64 si_guid;
पूर्ण;

काष्ठा mlx4_set_ib_param अणु
	पूर्णांक set_si_guid;
	पूर्णांक reset_qkey_viol;
	u64 si_guid;
	u32 cap_mask;
पूर्ण;

व्योम mlx4_dev_cap_dump(काष्ठा mlx4_dev *dev, काष्ठा mlx4_dev_cap *dev_cap);
पूर्णांक mlx4_QUERY_DEV_CAP(काष्ठा mlx4_dev *dev, काष्ठा mlx4_dev_cap *dev_cap);
पूर्णांक mlx4_QUERY_PORT(काष्ठा mlx4_dev *dev, पूर्णांक port, काष्ठा mlx4_port_cap *port_cap);
पूर्णांक mlx4_QUERY_FUNC_CAP(काष्ठा mlx4_dev *dev, u8 gen_or_port,
			काष्ठा mlx4_func_cap *func_cap);
पूर्णांक mlx4_QUERY_FUNC_CAP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				काष्ठा mlx4_vhcr *vhcr,
				काष्ठा mlx4_cmd_mailbox *inbox,
				काष्ठा mlx4_cmd_mailbox *outbox,
				काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QUERY_FUNC(काष्ठा mlx4_dev *dev, काष्ठा mlx4_func *func, पूर्णांक slave);
पूर्णांक mlx4_MAP_FA(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm *icm);
पूर्णांक mlx4_UNMAP_FA(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_RUN_FW(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_QUERY_FW(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_QUERY_ADAPTER(काष्ठा mlx4_dev *dev, काष्ठा mlx4_adapter *adapter);
पूर्णांक mlx4_INIT_HCA(काष्ठा mlx4_dev *dev, काष्ठा mlx4_init_hca_param *param);
पूर्णांक mlx4_QUERY_HCA(काष्ठा mlx4_dev *dev, काष्ठा mlx4_init_hca_param *param);
पूर्णांक mlx4_CLOSE_HCA(काष्ठा mlx4_dev *dev, पूर्णांक panic);
पूर्णांक mlx4_map_cmd(काष्ठा mlx4_dev *dev, u16 op, काष्ठा mlx4_icm *icm, u64 virt);
पूर्णांक mlx4_SET_ICM_SIZE(काष्ठा mlx4_dev *dev, u64 icm_size, u64 *aux_pages);
पूर्णांक mlx4_MAP_ICM_AUX(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm *icm);
पूर्णांक mlx4_UNMAP_ICM_AUX(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_NOP(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_MOD_STAT_CFG(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mod_stat_cfg *cfg);
व्योम mlx4_opreq_action(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर /* MLX4_FW_H */
