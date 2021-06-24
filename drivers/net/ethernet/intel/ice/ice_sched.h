<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_SCHED_H_
#घोषणा _ICE_SCHED_H_

#समावेश "ice_common.h"

#घोषणा ICE_QGRP_LAYER_OFFSET	2
#घोषणा ICE_VSI_LAYER_OFFSET	4
#घोषणा ICE_AGG_LAYER_OFFSET	6
#घोषणा ICE_SCHED_INVAL_LAYER_NUM	0xFF
/* Burst size is a 12 bits रेजिस्टर that is configured जबतक creating the RL
 * profile(s). MSB is a granularity bit and tells the granularity type
 * 0 - LSB bits are in 64 bytes granularity
 * 1 - LSB bits are in 1K bytes granularity
 */
#घोषणा ICE_64_BYTE_GRANULARITY			0
#घोषणा ICE_KBYTE_GRANULARITY			BIT(11)
#घोषणा ICE_MIN_BURST_SIZE_ALLOWED		64 /* In Bytes */
#घोषणा ICE_MAX_BURST_SIZE_ALLOWED \
	((BIT(11) - 1) * 1024) /* In Bytes */
#घोषणा ICE_MAX_BURST_SIZE_64_BYTE_GRANULARITY \
	((BIT(11) - 1) * 64) /* In Bytes */
#घोषणा ICE_MAX_BURST_SIZE_KBYTE_GRANULARITY	ICE_MAX_BURST_SIZE_ALLOWED

#घोषणा ICE_RL_PROF_ACCURACY_BYTES 128
#घोषणा ICE_RL_PROF_MULTIPLIER 10000
#घोषणा ICE_RL_PROF_TS_MULTIPLIER 32
#घोषणा ICE_RL_PROF_FRACTION 512

#घोषणा ICE_PSM_CLK_367MHZ_IN_HZ 367647059
#घोषणा ICE_PSM_CLK_416MHZ_IN_HZ 416666667
#घोषणा ICE_PSM_CLK_446MHZ_IN_HZ 446428571
#घोषणा ICE_PSM_CLK_390MHZ_IN_HZ 390625000

/* BW rate limit profile parameters list entry aदीर्घ
 * with bandwidth मुख्यtained per layer in port info
 */
काष्ठा ice_aqc_rl_profile_info अणु
	काष्ठा ice_aqc_rl_profile_elem profile;
	काष्ठा list_head list_entry;
	u32 bw;			/* requested */
	u16 prof_id_ref;	/* profile ID to node association ref count */
पूर्ण;

काष्ठा ice_sched_agg_vsi_info अणु
	काष्ठा list_head list_entry;
	DECLARE_BITMAP(tc_biपंचांगap, ICE_MAX_TRAFFIC_CLASS);
	u16 vsi_handle;
	/* save aggregator VSI TC biपंचांगap */
	DECLARE_BITMAP(replay_tc_biपंचांगap, ICE_MAX_TRAFFIC_CLASS);
पूर्ण;

काष्ठा ice_sched_agg_info अणु
	काष्ठा list_head agg_vsi_list;
	काष्ठा list_head list_entry;
	DECLARE_BITMAP(tc_biपंचांगap, ICE_MAX_TRAFFIC_CLASS);
	u32 agg_id;
	क्रमागत ice_agg_type agg_type;
	/* save aggregator TC biपंचांगap */
	DECLARE_BITMAP(replay_tc_biपंचांगap, ICE_MAX_TRAFFIC_CLASS);
पूर्ण;

/* FW AQ command calls */
क्रमागत ice_status
ice_aq_query_sched_elems(काष्ठा ice_hw *hw, u16 elems_req,
			 काष्ठा ice_aqc_txsched_elem_data *buf, u16 buf_size,
			 u16 *elems_ret, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status ice_sched_init_port(काष्ठा ice_port_info *pi);
क्रमागत ice_status ice_sched_query_res_alloc(काष्ठा ice_hw *hw);
व्योम ice_sched_get_psm_clk_freq(काष्ठा ice_hw *hw);

व्योम ice_sched_clear_port(काष्ठा ice_port_info *pi);
व्योम ice_sched_cleanup_all(काष्ठा ice_hw *hw);
व्योम ice_sched_clear_agg(काष्ठा ice_hw *hw);

काष्ठा ice_sched_node *
ice_sched_find_node_by_teid(काष्ठा ice_sched_node *start_node, u32 teid);
क्रमागत ice_status
ice_sched_add_node(काष्ठा ice_port_info *pi, u8 layer,
		   काष्ठा ice_aqc_txsched_elem_data *info);
व्योम ice_मुक्त_sched_node(काष्ठा ice_port_info *pi, काष्ठा ice_sched_node *node);
काष्ठा ice_sched_node *ice_sched_get_tc_node(काष्ठा ice_port_info *pi, u8 tc);
काष्ठा ice_sched_node *
ice_sched_get_मुक्त_qparent(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc,
			   u8 owner);
क्रमागत ice_status
ice_sched_cfg_vsi(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc, u16 maxqs,
		  u8 owner, bool enable);
क्रमागत ice_status ice_rm_vsi_lan_cfg(काष्ठा ice_port_info *pi, u16 vsi_handle);

/* Tx scheduler rate limiter functions */
क्रमागत ice_status
ice_cfg_agg(काष्ठा ice_port_info *pi, u32 agg_id,
	    क्रमागत ice_agg_type agg_type, u8 tc_biपंचांगap);
क्रमागत ice_status
ice_move_vsi_to_agg(काष्ठा ice_port_info *pi, u32 agg_id, u16 vsi_handle,
		    u8 tc_biपंचांगap);
क्रमागत ice_status
ice_cfg_q_bw_lmt(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc,
		 u16 q_handle, क्रमागत ice_rl_type rl_type, u32 bw);
क्रमागत ice_status
ice_cfg_q_bw_dflt_lmt(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc,
		      u16 q_handle, क्रमागत ice_rl_type rl_type);
क्रमागत ice_status ice_cfg_rl_burst_size(काष्ठा ice_hw *hw, u32 bytes);
व्योम ice_sched_replay_agg_vsi_preinit(काष्ठा ice_hw *hw);
व्योम ice_sched_replay_agg(काष्ठा ice_hw *hw);
क्रमागत ice_status ice_replay_vsi_agg(काष्ठा ice_hw *hw, u16 vsi_handle);
क्रमागत ice_status
ice_sched_replay_q_bw(काष्ठा ice_port_info *pi, काष्ठा ice_q_ctx *q_ctx);
#पूर्ण_अगर /* _ICE_SCHED_H_ */
