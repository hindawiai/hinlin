<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019, Mellanox Technologies */

#अगर_अघोषित	_DR_TYPES_
#घोषणा	_DR_TYPES_

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/refcount.h>
#समावेश "fs_core.h"
#समावेश "wq.h"
#समावेश "lib/mlx5.h"
#समावेश "mlx5_ifc_dr.h"
#समावेश "mlx5dr.h"

#घोषणा DR_RULE_MAX_STES 18
#घोषणा DR_ACTION_MAX_STES 5
#घोषणा WIRE_PORT 0xFFFF
#घोषणा DR_STE_SVLAN 0x1
#घोषणा DR_STE_CVLAN 0x2
#घोषणा DR_SZ_MATCH_PARAM (MLX5_ST_SZ_DW_MATCH_PARAM * 4)
#घोषणा DR_NUM_OF_FLEX_PARSERS 8
#घोषणा DR_STE_MAX_FLEX_0_ID 3
#घोषणा DR_STE_MAX_FLEX_1_ID 7

#घोषणा mlx5dr_err(dmn, arg...) mlx5_core_err((dmn)->mdev, ##arg)
#घोषणा mlx5dr_info(dmn, arg...) mlx5_core_info((dmn)->mdev, ##arg)
#घोषणा mlx5dr_dbg(dmn, arg...) mlx5_core_dbg((dmn)->mdev, ##arg)

अटल अंतरभूत bool dr_is_flex_parser_0_id(u8 parser_id)
अणु
	वापस parser_id <= DR_STE_MAX_FLEX_0_ID;
पूर्ण

अटल अंतरभूत bool dr_is_flex_parser_1_id(u8 parser_id)
अणु
	वापस parser_id > DR_STE_MAX_FLEX_0_ID;
पूर्ण

क्रमागत mlx5dr_icm_chunk_size अणु
	DR_CHUNK_SIZE_1,
	DR_CHUNK_SIZE_MIN = DR_CHUNK_SIZE_1, /* keep updated when changing */
	DR_CHUNK_SIZE_2,
	DR_CHUNK_SIZE_4,
	DR_CHUNK_SIZE_8,
	DR_CHUNK_SIZE_16,
	DR_CHUNK_SIZE_32,
	DR_CHUNK_SIZE_64,
	DR_CHUNK_SIZE_128,
	DR_CHUNK_SIZE_256,
	DR_CHUNK_SIZE_512,
	DR_CHUNK_SIZE_1K,
	DR_CHUNK_SIZE_2K,
	DR_CHUNK_SIZE_4K,
	DR_CHUNK_SIZE_8K,
	DR_CHUNK_SIZE_16K,
	DR_CHUNK_SIZE_32K,
	DR_CHUNK_SIZE_64K,
	DR_CHUNK_SIZE_128K,
	DR_CHUNK_SIZE_256K,
	DR_CHUNK_SIZE_512K,
	DR_CHUNK_SIZE_1024K,
	DR_CHUNK_SIZE_2048K,
	DR_CHUNK_SIZE_MAX,
पूर्ण;

क्रमागत mlx5dr_icm_type अणु
	DR_ICM_TYPE_STE,
	DR_ICM_TYPE_MODIFY_ACTION,
पूर्ण;

अटल अंतरभूत क्रमागत mlx5dr_icm_chunk_size
mlx5dr_icm_next_higher_chunk(क्रमागत mlx5dr_icm_chunk_size chunk)
अणु
	chunk += 2;
	अगर (chunk < DR_CHUNK_SIZE_MAX)
		वापस chunk;

	वापस DR_CHUNK_SIZE_MAX;
पूर्ण

क्रमागत अणु
	DR_STE_SIZE = 64,
	DR_STE_SIZE_CTRL = 32,
	DR_STE_SIZE_TAG = 16,
	DR_STE_SIZE_MASK = 16,
पूर्ण;

क्रमागत अणु
	DR_STE_SIZE_REDUCED = DR_STE_SIZE - DR_STE_SIZE_MASK,
पूर्ण;

क्रमागत अणु
	DR_MODIFY_ACTION_SIZE = 8,
पूर्ण;

क्रमागत mlx5dr_matcher_criteria अणु
	DR_MATCHER_CRITERIA_EMPTY = 0,
	DR_MATCHER_CRITERIA_OUTER = 1 << 0,
	DR_MATCHER_CRITERIA_MISC = 1 << 1,
	DR_MATCHER_CRITERIA_INNER = 1 << 2,
	DR_MATCHER_CRITERIA_MISC2 = 1 << 3,
	DR_MATCHER_CRITERIA_MISC3 = 1 << 4,
	DR_MATCHER_CRITERIA_MISC4 = 1 << 5,
	DR_MATCHER_CRITERIA_MAX = 1 << 6,
पूर्ण;

क्रमागत mlx5dr_action_type अणु
	DR_ACTION_TYP_TNL_L2_TO_L2,
	DR_ACTION_TYP_L2_TO_TNL_L2,
	DR_ACTION_TYP_TNL_L3_TO_L2,
	DR_ACTION_TYP_L2_TO_TNL_L3,
	DR_ACTION_TYP_DROP,
	DR_ACTION_TYP_QP,
	DR_ACTION_TYP_FT,
	DR_ACTION_TYP_CTR,
	DR_ACTION_TYP_TAG,
	DR_ACTION_TYP_MODIFY_HDR,
	DR_ACTION_TYP_VPORT,
	DR_ACTION_TYP_POP_VLAN,
	DR_ACTION_TYP_PUSH_VLAN,
	DR_ACTION_TYP_MAX,
पूर्ण;

क्रमागत mlx5dr_ipv अणु
	DR_RULE_IPV4,
	DR_RULE_IPV6,
	DR_RULE_IPV_MAX,
पूर्ण;

काष्ठा mlx5dr_icm_pool;
काष्ठा mlx5dr_icm_chunk;
काष्ठा mlx5dr_icm_buddy_mem;
काष्ठा mlx5dr_ste_htbl;
काष्ठा mlx5dr_match_param;
काष्ठा mlx5dr_cmd_caps;
काष्ठा mlx5dr_matcher_rx_tx;
काष्ठा mlx5dr_ste_ctx;

काष्ठा mlx5dr_ste अणु
	u8 *hw_ste;
	/* refcount: indicates the num of rules that using this ste */
	u32 refcount;

	/* attached to the miss_list head at each htbl entry */
	काष्ठा list_head miss_list_node;

	/* each rule member that uses this ste attached here */
	काष्ठा list_head rule_list;

	/* this ste is member of htbl */
	काष्ठा mlx5dr_ste_htbl *htbl;

	काष्ठा mlx5dr_ste_htbl *next_htbl;

	/* this ste is part of a rule, located in ste's chain */
	u8 ste_chain_location;
पूर्ण;

काष्ठा mlx5dr_ste_htbl_ctrl अणु
	/* total number of valid entries beदीर्घing to this hash table. This
	 * includes the non collision and collision entries
	 */
	अचिन्हित पूर्णांक num_of_valid_entries;

	/* total number of collisions entries attached to this table */
	अचिन्हित पूर्णांक num_of_collisions;
	अचिन्हित पूर्णांक increase_threshold;
	u8 may_grow:1;
पूर्ण;

काष्ठा mlx5dr_ste_htbl अणु
	u16 lu_type;
	u16 byte_mask;
	u32 refcount;
	काष्ठा mlx5dr_icm_chunk *chunk;
	काष्ठा mlx5dr_ste *ste_arr;
	u8 *hw_ste_arr;

	काष्ठा list_head *miss_list;

	क्रमागत mlx5dr_icm_chunk_size chunk_size;
	काष्ठा mlx5dr_ste *poपूर्णांकing_ste;

	काष्ठा mlx5dr_ste_htbl_ctrl ctrl;
पूर्ण;

काष्ठा mlx5dr_ste_send_info अणु
	काष्ठा mlx5dr_ste *ste;
	काष्ठा list_head send_list;
	u16 size;
	u16 offset;
	u8 data_cont[DR_STE_SIZE];
	u8 *data;
पूर्ण;

व्योम mlx5dr_send_fill_and_append_ste_send_info(काष्ठा mlx5dr_ste *ste, u16 size,
					       u16 offset, u8 *data,
					       काष्ठा mlx5dr_ste_send_info *ste_info,
					       काष्ठा list_head *send_list,
					       bool copy_data);

काष्ठा mlx5dr_ste_build अणु
	u8 inner:1;
	u8 rx:1;
	u8 vhca_id_valid:1;
	काष्ठा mlx5dr_करोमुख्य *dmn;
	काष्ठा mlx5dr_cmd_caps *caps;
	u16 lu_type;
	u16 byte_mask;
	u8 bit_mask[DR_STE_SIZE_MASK];
	पूर्णांक (*ste_build_tag_func)(काष्ठा mlx5dr_match_param *spec,
				  काष्ठा mlx5dr_ste_build *sb,
				  u8 *tag);
पूर्ण;

काष्ठा mlx5dr_ste_htbl *
mlx5dr_ste_htbl_alloc(काष्ठा mlx5dr_icm_pool *pool,
		      क्रमागत mlx5dr_icm_chunk_size chunk_size,
		      u16 lu_type, u16 byte_mask);

पूर्णांक mlx5dr_ste_htbl_मुक्त(काष्ठा mlx5dr_ste_htbl *htbl);

अटल अंतरभूत व्योम mlx5dr_htbl_put(काष्ठा mlx5dr_ste_htbl *htbl)
अणु
	htbl->refcount--;
	अगर (!htbl->refcount)
		mlx5dr_ste_htbl_मुक्त(htbl);
पूर्ण

अटल अंतरभूत व्योम mlx5dr_htbl_get(काष्ठा mlx5dr_ste_htbl *htbl)
अणु
	htbl->refcount++;
पूर्ण

/* STE utils */
u32 mlx5dr_ste_calc_hash_index(u8 *hw_ste_p, काष्ठा mlx5dr_ste_htbl *htbl);
व्योम mlx5dr_ste_set_miss_addr(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			      u8 *hw_ste, u64 miss_addr);
व्योम mlx5dr_ste_set_hit_addr(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			     u8 *hw_ste, u64 icm_addr, u32 ht_size);
व्योम mlx5dr_ste_set_hit_addr_by_next_htbl(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					  u8 *hw_ste,
					  काष्ठा mlx5dr_ste_htbl *next_htbl);
व्योम mlx5dr_ste_set_bit_mask(u8 *hw_ste_p, u8 *bit_mask);
bool mlx5dr_ste_is_last_in_rule(काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				u8 ste_location);
u64 mlx5dr_ste_get_icm_addr(काष्ठा mlx5dr_ste *ste);
u64 mlx5dr_ste_get_mr_addr(काष्ठा mlx5dr_ste *ste);
काष्ठा list_head *mlx5dr_ste_get_miss_list(काष्ठा mlx5dr_ste *ste);

#घोषणा MLX5DR_MAX_VLANS 2

काष्ठा mlx5dr_ste_actions_attr अणु
	u32	modअगरy_index;
	u16	modअगरy_actions;
	u32	decap_index;
	u16	decap_actions;
	u8	decap_with_vlan:1;
	u64	final_icm_addr;
	u32	flow_tag;
	u32	ctr_id;
	u16	gvmi;
	u16	hit_gvmi;
	u32	reक्रमmat_id;
	u32	reक्रमmat_size;
	काष्ठा अणु
		पूर्णांक	count;
		u32	headers[MLX5DR_MAX_VLANS];
	पूर्ण vlans;
पूर्ण;

व्योम mlx5dr_ste_set_actions_rx(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       काष्ठा mlx5dr_करोमुख्य *dmn,
			       u8 *action_type_set,
			       u8 *last_ste,
			       काष्ठा mlx5dr_ste_actions_attr *attr,
			       u32 *added_stes);
व्योम mlx5dr_ste_set_actions_tx(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       काष्ठा mlx5dr_करोमुख्य *dmn,
			       u8 *action_type_set,
			       u8 *last_ste,
			       काष्ठा mlx5dr_ste_actions_attr *attr,
			       u32 *added_stes);

व्योम mlx5dr_ste_set_action_set(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       __be64 *hw_action,
			       u8 hw_field,
			       u8 shअगरter,
			       u8 length,
			       u32 data);
व्योम mlx5dr_ste_set_action_add(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       __be64 *hw_action,
			       u8 hw_field,
			       u8 shअगरter,
			       u8 length,
			       u32 data);
व्योम mlx5dr_ste_set_action_copy(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				__be64 *hw_action,
				u8 dst_hw_field,
				u8 dst_shअगरter,
				u8 dst_len,
				u8 src_hw_field,
				u8 src_shअगरter);
पूर्णांक mlx5dr_ste_set_action_decap_l3_list(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					व्योम *data,
					u32 data_sz,
					u8 *hw_action,
					u32 hw_action_sz,
					u16 *used_hw_action_num);

स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field *
mlx5dr_ste_conv_modअगरy_hdr_sw_field(काष्ठा mlx5dr_ste_ctx *ste_ctx, u16 sw_field);

काष्ठा mlx5dr_ste_ctx *mlx5dr_ste_get_ctx(u8 version);
व्योम mlx5dr_ste_मुक्त(काष्ठा mlx5dr_ste *ste,
		     काष्ठा mlx5dr_matcher *matcher,
		     काष्ठा mlx5dr_matcher_rx_tx *nic_matcher);
अटल अंतरभूत व्योम mlx5dr_ste_put(काष्ठा mlx5dr_ste *ste,
				  काष्ठा mlx5dr_matcher *matcher,
				  काष्ठा mlx5dr_matcher_rx_tx *nic_matcher)
अणु
	ste->refcount--;
	अगर (!ste->refcount)
		mlx5dr_ste_मुक्त(ste, matcher, nic_matcher);
पूर्ण

/* initial as 0, increased only when ste appears in a new rule */
अटल अंतरभूत व्योम mlx5dr_ste_get(काष्ठा mlx5dr_ste *ste)
अणु
	ste->refcount++;
पूर्ण

अटल अंतरभूत bool mlx5dr_ste_is_not_used(काष्ठा mlx5dr_ste *ste)
अणु
	वापस !ste->refcount;
पूर्ण

bool mlx5dr_ste_equal_tag(व्योम *src, व्योम *dst);
पूर्णांक mlx5dr_ste_create_next_htbl(काष्ठा mlx5dr_matcher *matcher,
				काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				काष्ठा mlx5dr_ste *ste,
				u8 *cur_hw_ste,
				क्रमागत mlx5dr_icm_chunk_size log_table_size);

/* STE build functions */
पूर्णांक mlx5dr_ste_build_pre_check(काष्ठा mlx5dr_करोमुख्य *dmn,
			       u8 match_criteria,
			       काष्ठा mlx5dr_match_param *mask,
			       काष्ठा mlx5dr_match_param *value);
पूर्णांक mlx5dr_ste_build_ste_arr(काष्ठा mlx5dr_matcher *matcher,
			     काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
			     काष्ठा mlx5dr_match_param *value,
			     u8 *ste_arr);
व्योम mlx5dr_ste_build_eth_l2_src_dst(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				     काष्ठा mlx5dr_ste_build *builder,
				     काष्ठा mlx5dr_match_param *mask,
				     bool inner, bool rx);
व्योम mlx5dr_ste_build_eth_l3_ipv4_5_tuple(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					  काष्ठा mlx5dr_ste_build *sb,
					  काष्ठा mlx5dr_match_param *mask,
					  bool inner, bool rx);
व्योम mlx5dr_ste_build_eth_l3_ipv4_misc(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				       काष्ठा mlx5dr_ste_build *sb,
				       काष्ठा mlx5dr_match_param *mask,
				       bool inner, bool rx);
व्योम mlx5dr_ste_build_eth_l3_ipv6_dst(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				      काष्ठा mlx5dr_ste_build *sb,
				      काष्ठा mlx5dr_match_param *mask,
				      bool inner, bool rx);
व्योम mlx5dr_ste_build_eth_l3_ipv6_src(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				      काष्ठा mlx5dr_ste_build *sb,
				      काष्ठा mlx5dr_match_param *mask,
				      bool inner, bool rx);
व्योम mlx5dr_ste_build_eth_l2_src(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx);
व्योम mlx5dr_ste_build_eth_l2_dst(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx);
व्योम mlx5dr_ste_build_eth_l2_tnl(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx);
व्योम mlx5dr_ste_build_eth_ipv6_l3_l4(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				     काष्ठा mlx5dr_ste_build *sb,
				     काष्ठा mlx5dr_match_param *mask,
				     bool inner, bool rx);
व्योम mlx5dr_ste_build_eth_l4_misc(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				  काष्ठा mlx5dr_ste_build *sb,
				  काष्ठा mlx5dr_match_param *mask,
				  bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_gre(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			      काष्ठा mlx5dr_ste_build *sb,
			      काष्ठा mlx5dr_match_param *mask,
			      bool inner, bool rx);
व्योम mlx5dr_ste_build_mpls(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			   काष्ठा mlx5dr_ste_build *sb,
			   काष्ठा mlx5dr_match_param *mask,
			   bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_mpls(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       काष्ठा mlx5dr_ste_build *sb,
			       काष्ठा mlx5dr_match_param *mask,
			       bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_mpls_over_gre(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					काष्ठा mlx5dr_ste_build *sb,
					काष्ठा mlx5dr_match_param *mask,
					काष्ठा mlx5dr_cmd_caps *caps,
					bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_mpls_over_udp(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					काष्ठा mlx5dr_ste_build *sb,
					काष्ठा mlx5dr_match_param *mask,
					काष्ठा mlx5dr_cmd_caps *caps,
					bool inner, bool rx);
व्योम mlx5dr_ste_build_icmp(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			   काष्ठा mlx5dr_ste_build *sb,
			   काष्ठा mlx5dr_match_param *mask,
			   काष्ठा mlx5dr_cmd_caps *caps,
			   bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_vxlan_gpe(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				    काष्ठा mlx5dr_ste_build *sb,
				    काष्ठा mlx5dr_match_param *mask,
				    bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_geneve(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_geneve_tlv_opt(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					 काष्ठा mlx5dr_ste_build *sb,
					 काष्ठा mlx5dr_match_param *mask,
					 काष्ठा mlx5dr_cmd_caps *caps,
					 bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_gtpu(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       काष्ठा mlx5dr_ste_build *sb,
			       काष्ठा mlx5dr_match_param *mask,
			       bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_gtpu_flex_parser_0(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					     काष्ठा mlx5dr_ste_build *sb,
					     काष्ठा mlx5dr_match_param *mask,
					     काष्ठा mlx5dr_cmd_caps *caps,
					     bool inner, bool rx);
व्योम mlx5dr_ste_build_tnl_gtpu_flex_parser_1(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					     काष्ठा mlx5dr_ste_build *sb,
					     काष्ठा mlx5dr_match_param *mask,
					     काष्ठा mlx5dr_cmd_caps *caps,
					     bool inner, bool rx);
व्योम mlx5dr_ste_build_general_purpose(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				      काष्ठा mlx5dr_ste_build *sb,
				      काष्ठा mlx5dr_match_param *mask,
				      bool inner, bool rx);
व्योम mlx5dr_ste_build_रेजिस्टर_0(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx);
व्योम mlx5dr_ste_build_रेजिस्टर_1(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx);
व्योम mlx5dr_ste_build_src_gvmi_qpn(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				   काष्ठा mlx5dr_ste_build *sb,
				   काष्ठा mlx5dr_match_param *mask,
				   काष्ठा mlx5dr_करोमुख्य *dmn,
				   bool inner, bool rx);
व्योम mlx5dr_ste_build_flex_parser_0(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				    काष्ठा mlx5dr_ste_build *sb,
				    काष्ठा mlx5dr_match_param *mask,
				    bool inner, bool rx);
व्योम mlx5dr_ste_build_flex_parser_1(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				    काष्ठा mlx5dr_ste_build *sb,
				    काष्ठा mlx5dr_match_param *mask,
				    bool inner, bool rx);
व्योम mlx5dr_ste_build_empty_always_hit(काष्ठा mlx5dr_ste_build *sb, bool rx);

/* Actions utils */
पूर्णांक mlx5dr_actions_build_ste_arr(काष्ठा mlx5dr_matcher *matcher,
				 काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				 काष्ठा mlx5dr_action *actions[],
				 u32 num_actions,
				 u8 *ste_arr,
				 u32 *new_hw_ste_arr_sz);

काष्ठा mlx5dr_match_spec अणु
	u32 smac_47_16;		/* Source MAC address of incoming packet */
	/* Incoming packet Ethertype - this is the Ethertype
	 * following the last VLAN tag of the packet
	 */
	u32 ethertype:16;
	u32 smac_15_0:16;	/* Source MAC address of incoming packet */
	u32 dmac_47_16;		/* Destination MAC address of incoming packet */
	/* VLAN ID of first VLAN tag in the incoming packet.
	 * Valid only when cvlan_tag==1 or svlan_tag==1
	 */
	u32 first_vid:12;
	/* CFI bit of first VLAN tag in the incoming packet.
	 * Valid only when cvlan_tag==1 or svlan_tag==1
	 */
	u32 first_cfi:1;
	/* Priority of first VLAN tag in the incoming packet.
	 * Valid only when cvlan_tag==1 or svlan_tag==1
	 */
	u32 first_prio:3;
	u32 dmac_15_0:16;	/* Destination MAC address of incoming packet */
	/* TCP flags. ;Bit 0: FIN;Bit 1: SYN;Bit 2: RST;Bit 3: PSH;Bit 4: ACK;
	 *             Bit 5: URG;Bit 6: ECE;Bit 7: CWR;Bit 8: NS
	 */
	u32 tcp_flags:9;
	u32 ip_version:4;	/* IP version */
	u32 frag:1;		/* Packet is an IP fragment */
	/* The first vlan in the packet is s-vlan (0x8a88).
	 * cvlan_tag and svlan_tag cannot be set together
	 */
	u32 svlan_tag:1;
	/* The first vlan in the packet is c-vlan (0x8100).
	 * cvlan_tag and svlan_tag cannot be set together
	 */
	u32 cvlan_tag:1;
	/* Explicit Congestion Notअगरication derived from
	 * Traffic Class/TOS field of IPv6/v4
	 */
	u32 ip_ecn:2;
	/* Dअगरferentiated Services Code Poपूर्णांक derived from
	 * Traffic Class/TOS field of IPv6/v4
	 */
	u32 ip_dscp:6;
	u32 ip_protocol:8;	/* IP protocol */
	/* TCP destination port.
	 * tcp and udp sport/dport are mutually exclusive
	 */
	u32 tcp_dport:16;
	/* TCP source port.;tcp and udp sport/dport are mutually exclusive */
	u32 tcp_sport:16;
	u32 ttl_hoplimit:8;
	u32 reserved:24;
	/* UDP destination port.;tcp and udp sport/dport are mutually exclusive */
	u32 udp_dport:16;
	/* UDP source port.;tcp and udp sport/dport are mutually exclusive */
	u32 udp_sport:16;
	/* IPv6 source address of incoming packets
	 * For IPv4 address use bits 31:0 (rest of the bits are reserved)
	 * This field should be qualअगरied by an appropriate ethertype
	 */
	u32 src_ip_127_96;
	/* IPv6 source address of incoming packets
	 * For IPv4 address use bits 31:0 (rest of the bits are reserved)
	 * This field should be qualअगरied by an appropriate ethertype
	 */
	u32 src_ip_95_64;
	/* IPv6 source address of incoming packets
	 * For IPv4 address use bits 31:0 (rest of the bits are reserved)
	 * This field should be qualअगरied by an appropriate ethertype
	 */
	u32 src_ip_63_32;
	/* IPv6 source address of incoming packets
	 * For IPv4 address use bits 31:0 (rest of the bits are reserved)
	 * This field should be qualअगरied by an appropriate ethertype
	 */
	u32 src_ip_31_0;
	/* IPv6 destination address of incoming packets
	 * For IPv4 address use bits 31:0 (rest of the bits are reserved)
	 * This field should be qualअगरied by an appropriate ethertype
	 */
	u32 dst_ip_127_96;
	/* IPv6 destination address of incoming packets
	 * For IPv4 address use bits 31:0 (rest of the bits are reserved)
	 * This field should be qualअगरied by an appropriate ethertype
	 */
	u32 dst_ip_95_64;
	/* IPv6 destination address of incoming packets
	 * For IPv4 address use bits 31:0 (rest of the bits are reserved)
	 * This field should be qualअगरied by an appropriate ethertype
	 */
	u32 dst_ip_63_32;
	/* IPv6 destination address of incoming packets
	 * For IPv4 address use bits 31:0 (rest of the bits are reserved)
	 * This field should be qualअगरied by an appropriate ethertype
	 */
	u32 dst_ip_31_0;
पूर्ण;

काष्ठा mlx5dr_match_misc अणु
	u32 source_sqn:24;		/* Source SQN */
	u32 source_vhca_port:4;
	/* used with GRE, sequence number exist when gre_s_present == 1 */
	u32 gre_s_present:1;
	/* used with GRE, key exist when gre_k_present == 1 */
	u32 gre_k_present:1;
	u32 reserved_स्वतः1:1;
	/* used with GRE, checksum exist when gre_c_present == 1 */
	u32 gre_c_present:1;
	/* Source port.;0xffff determines wire port */
	u32 source_port:16;
	u32 source_eचयन_owner_vhca_id:16;
	/* VLAN ID of first VLAN tag the inner header of the incoming packet.
	 * Valid only when inner_second_cvlan_tag ==1 or inner_second_svlan_tag ==1
	 */
	u32 inner_second_vid:12;
	/* CFI bit of first VLAN tag in the inner header of the incoming packet.
	 * Valid only when inner_second_cvlan_tag ==1 or inner_second_svlan_tag ==1
	 */
	u32 inner_second_cfi:1;
	/* Priority of second VLAN tag in the inner header of the incoming packet.
	 * Valid only when inner_second_cvlan_tag ==1 or inner_second_svlan_tag ==1
	 */
	u32 inner_second_prio:3;
	/* VLAN ID of first VLAN tag the outer header of the incoming packet.
	 * Valid only when outer_second_cvlan_tag ==1 or outer_second_svlan_tag ==1
	 */
	u32 outer_second_vid:12;
	/* CFI bit of first VLAN tag in the outer header of the incoming packet.
	 * Valid only when outer_second_cvlan_tag ==1 or outer_second_svlan_tag ==1
	 */
	u32 outer_second_cfi:1;
	/* Priority of second VLAN tag in the outer header of the incoming packet.
	 * Valid only when outer_second_cvlan_tag ==1 or outer_second_svlan_tag ==1
	 */
	u32 outer_second_prio:3;
	u32 gre_protocol:16;		/* GRE Protocol (outer) */
	u32 reserved_स्वतः3:12;
	/* The second vlan in the inner header of the packet is s-vlan (0x8a88).
	 * inner_second_cvlan_tag and inner_second_svlan_tag cannot be set together
	 */
	u32 inner_second_svlan_tag:1;
	/* The second vlan in the outer header of the packet is s-vlan (0x8a88).
	 * outer_second_cvlan_tag and outer_second_svlan_tag cannot be set together
	 */
	u32 outer_second_svlan_tag:1;
	/* The second vlan in the inner header of the packet is c-vlan (0x8100).
	 * inner_second_cvlan_tag and inner_second_svlan_tag cannot be set together
	 */
	u32 inner_second_cvlan_tag:1;
	/* The second vlan in the outer header of the packet is c-vlan (0x8100).
	 * outer_second_cvlan_tag and outer_second_svlan_tag cannot be set together
	 */
	u32 outer_second_cvlan_tag:1;
	u32 gre_key_l:8;		/* GRE Key [7:0] (outer) */
	u32 gre_key_h:24;		/* GRE Key[31:8] (outer) */
	u32 reserved_स्वतः4:8;
	u32 vxlan_vni:24;		/* VXLAN VNI (outer) */
	u32 geneve_oam:1;		/* GENEVE OAM field (outer) */
	u32 reserved_स्वतः5:7;
	u32 geneve_vni:24;		/* GENEVE VNI field (outer) */
	u32 outer_ipv6_flow_label:20;	/* Flow label of incoming IPv6 packet (outer) */
	u32 reserved_स्वतः6:12;
	u32 inner_ipv6_flow_label:20;	/* Flow label of incoming IPv6 packet (inner) */
	u32 reserved_स्वतः7:12;
	u32 geneve_protocol_type:16;	/* GENEVE protocol type (outer) */
	u32 geneve_opt_len:6;		/* GENEVE OptLen (outer) */
	u32 reserved_स्वतः8:10;
	u32 bth_dst_qp:24;		/* Destination QP in BTH header */
	u32 reserved_स्वतः9:8;
	u8 reserved_स्वतः10[20];
पूर्ण;

काष्ठा mlx5dr_match_misc2 अणु
	u32 outer_first_mpls_ttl:8;		/* First MPLS TTL (outer) */
	u32 outer_first_mpls_s_bos:1;		/* First MPLS S_BOS (outer) */
	u32 outer_first_mpls_exp:3;		/* First MPLS EXP (outer) */
	u32 outer_first_mpls_label:20;		/* First MPLS LABEL (outer) */
	u32 inner_first_mpls_ttl:8;		/* First MPLS TTL (inner) */
	u32 inner_first_mpls_s_bos:1;		/* First MPLS S_BOS (inner) */
	u32 inner_first_mpls_exp:3;		/* First MPLS EXP (inner) */
	u32 inner_first_mpls_label:20;		/* First MPLS LABEL (inner) */
	u32 outer_first_mpls_over_gre_ttl:8;	/* last MPLS TTL (outer) */
	u32 outer_first_mpls_over_gre_s_bos:1;	/* last MPLS S_BOS (outer) */
	u32 outer_first_mpls_over_gre_exp:3;	/* last MPLS EXP (outer) */
	u32 outer_first_mpls_over_gre_label:20;	/* last MPLS LABEL (outer) */
	u32 outer_first_mpls_over_udp_ttl:8;	/* last MPLS TTL (outer) */
	u32 outer_first_mpls_over_udp_s_bos:1;	/* last MPLS S_BOS (outer) */
	u32 outer_first_mpls_over_udp_exp:3;	/* last MPLS EXP (outer) */
	u32 outer_first_mpls_over_udp_label:20;	/* last MPLS LABEL (outer) */
	u32 metadata_reg_c_7;			/* metadata_reg_c_7 */
	u32 metadata_reg_c_6;			/* metadata_reg_c_6 */
	u32 metadata_reg_c_5;			/* metadata_reg_c_5 */
	u32 metadata_reg_c_4;			/* metadata_reg_c_4 */
	u32 metadata_reg_c_3;			/* metadata_reg_c_3 */
	u32 metadata_reg_c_2;			/* metadata_reg_c_2 */
	u32 metadata_reg_c_1;			/* metadata_reg_c_1 */
	u32 metadata_reg_c_0;			/* metadata_reg_c_0 */
	u32 metadata_reg_a;			/* metadata_reg_a */
	u8 reserved_स्वतः2[12];
पूर्ण;

काष्ठा mlx5dr_match_misc3 अणु
	u32 inner_tcp_seq_num;
	u32 outer_tcp_seq_num;
	u32 inner_tcp_ack_num;
	u32 outer_tcp_ack_num;
	u32 outer_vxlan_gpe_vni:24;
	u32 reserved_स्वतः1:8;
	u32 reserved_स्वतः2:16;
	u32 outer_vxlan_gpe_flags:8;
	u32 outer_vxlan_gpe_next_protocol:8;
	u32 icmpv4_header_data;
	u32 icmpv6_header_data;
	u8 icmpv6_code;
	u8 icmpv6_type;
	u8 icmpv4_code;
	u8 icmpv4_type;
	u32 geneve_tlv_option_0_data;
	u8 gtpu_msg_flags;
	u8 gtpu_msg_type;
	u32 gtpu_teid;
	u32 gtpu_dw_2;
	u32 gtpu_first_ext_dw_0;
	u32 gtpu_dw_0;
पूर्ण;

काष्ठा mlx5dr_match_misc4 अणु
	u32 prog_sample_field_value_0;
	u32 prog_sample_field_id_0;
	u32 prog_sample_field_value_1;
	u32 prog_sample_field_id_1;
	u32 prog_sample_field_value_2;
	u32 prog_sample_field_id_2;
	u32 prog_sample_field_value_3;
	u32 prog_sample_field_id_3;
पूर्ण;

काष्ठा mlx5dr_match_param अणु
	काष्ठा mlx5dr_match_spec outer;
	काष्ठा mlx5dr_match_misc misc;
	काष्ठा mlx5dr_match_spec inner;
	काष्ठा mlx5dr_match_misc2 misc2;
	काष्ठा mlx5dr_match_misc3 misc3;
	काष्ठा mlx5dr_match_misc4 misc4;
पूर्ण;

#घोषणा DR_MASK_IS_ICMPV4_SET(_misc3) ((_misc3)->icmpv4_type || \
				       (_misc3)->icmpv4_code || \
				       (_misc3)->icmpv4_header_data)

काष्ठा mlx5dr_esw_caps अणु
	u64 drop_icm_address_rx;
	u64 drop_icm_address_tx;
	u64 uplink_icm_address_rx;
	u64 uplink_icm_address_tx;
	u8 sw_owner:1;
	u8 sw_owner_v2:1;
पूर्ण;

काष्ठा mlx5dr_cmd_vport_cap अणु
	u16 vport_gvmi;
	u16 vhca_gvmi;
	u64 icm_address_rx;
	u64 icm_address_tx;
	u32 num;
पूर्ण;

काष्ठा mlx5dr_roce_cap अणु
	u8 roce_en:1;
	u8 fl_rc_qp_when_roce_disabled:1;
	u8 fl_rc_qp_when_roce_enabled:1;
पूर्ण;

काष्ठा mlx5dr_cmd_caps अणु
	u16 gvmi;
	u64 nic_rx_drop_address;
	u64 nic_tx_drop_address;
	u64 nic_tx_allow_address;
	u64 esw_rx_drop_address;
	u64 esw_tx_drop_address;
	u32 log_icm_size;
	u64 hdr_modअगरy_icm_addr;
	u32 flex_protocols;
	u8 flex_parser_id_icmp_dw0;
	u8 flex_parser_id_icmp_dw1;
	u8 flex_parser_id_icmpv6_dw0;
	u8 flex_parser_id_icmpv6_dw1;
	u8 flex_parser_id_geneve_tlv_option_0;
	u8 flex_parser_id_mpls_over_gre;
	u8 flex_parser_id_mpls_over_udp;
	u8 flex_parser_id_gtpu_dw_0;
	u8 flex_parser_id_gtpu_teid;
	u8 flex_parser_id_gtpu_dw_2;
	u8 flex_parser_id_gtpu_first_ext_dw_0;
	u8 max_ft_level;
	u16 roce_min_src_udp;
	u8 num_esw_ports;
	u8 sw_क्रमmat_ver;
	bool eचयन_manager;
	bool rx_sw_owner;
	bool tx_sw_owner;
	bool fdb_sw_owner;
	u8 rx_sw_owner_v2:1;
	u8 tx_sw_owner_v2:1;
	u8 fdb_sw_owner_v2:1;
	u32 num_vports;
	काष्ठा mlx5dr_esw_caps esw_caps;
	काष्ठा mlx5dr_cmd_vport_cap *vports_caps;
	bool prio_tag_required;
	काष्ठा mlx5dr_roce_cap roce_caps;
	u8 isolate_vl_tc:1;
पूर्ण;

काष्ठा mlx5dr_करोमुख्य_rx_tx अणु
	u64 drop_icm_addr;
	u64 शेष_icm_addr;
	क्रमागत mlx5dr_ste_entry_type ste_type;
	काष्ठा mutex mutex; /* protect rx/tx करोमुख्य */
पूर्ण;

काष्ठा mlx5dr_करोमुख्य_info अणु
	bool supp_sw_steering;
	u32 max_अंतरभूत_size;
	u32 max_send_wr;
	u32 max_log_sw_icm_sz;
	u32 max_log_action_icm_sz;
	काष्ठा mlx5dr_करोमुख्य_rx_tx rx;
	काष्ठा mlx5dr_करोमुख्य_rx_tx tx;
	काष्ठा mlx5dr_cmd_caps caps;
पूर्ण;

काष्ठा mlx5dr_करोमुख्य_cache अणु
	काष्ठा mlx5dr_fw_recalc_cs_ft **recalc_cs_ft;
पूर्ण;

काष्ठा mlx5dr_करोमुख्य अणु
	काष्ठा mlx5dr_करोमुख्य *peer_dmn;
	काष्ठा mlx5_core_dev *mdev;
	u32 pdn;
	काष्ठा mlx5_uars_page *uar;
	क्रमागत mlx5dr_करोमुख्य_type type;
	refcount_t refcount;
	काष्ठा mlx5dr_icm_pool *ste_icm_pool;
	काष्ठा mlx5dr_icm_pool *action_icm_pool;
	काष्ठा mlx5dr_send_ring *send_ring;
	काष्ठा mlx5dr_करोमुख्य_info info;
	काष्ठा mlx5dr_करोमुख्य_cache cache;
	काष्ठा mlx5dr_ste_ctx *ste_ctx;
पूर्ण;

काष्ठा mlx5dr_table_rx_tx अणु
	काष्ठा mlx5dr_ste_htbl *s_anchor;
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn;
	u64 शेष_icm_addr;
पूर्ण;

काष्ठा mlx5dr_table अणु
	काष्ठा mlx5dr_करोमुख्य *dmn;
	काष्ठा mlx5dr_table_rx_tx rx;
	काष्ठा mlx5dr_table_rx_tx tx;
	u32 level;
	u32 table_type;
	u32 table_id;
	u32 flags;
	काष्ठा list_head matcher_list;
	काष्ठा mlx5dr_action *miss_action;
	refcount_t refcount;
पूर्ण;

काष्ठा mlx5dr_matcher_rx_tx अणु
	काष्ठा mlx5dr_ste_htbl *s_htbl;
	काष्ठा mlx5dr_ste_htbl *e_anchor;
	काष्ठा mlx5dr_ste_build *ste_builder;
	काष्ठा mlx5dr_ste_build ste_builder_arr[DR_RULE_IPV_MAX]
					       [DR_RULE_IPV_MAX]
					       [DR_RULE_MAX_STES];
	u8 num_of_builders;
	u8 num_of_builders_arr[DR_RULE_IPV_MAX][DR_RULE_IPV_MAX];
	u64 शेष_icm_addr;
	काष्ठा mlx5dr_table_rx_tx *nic_tbl;
पूर्ण;

काष्ठा mlx5dr_matcher अणु
	काष्ठा mlx5dr_table *tbl;
	काष्ठा mlx5dr_matcher_rx_tx rx;
	काष्ठा mlx5dr_matcher_rx_tx tx;
	काष्ठा list_head matcher_list;
	u32 prio;
	काष्ठा mlx5dr_match_param mask;
	u8 match_criteria;
	refcount_t refcount;
	काष्ठा mlx5dv_flow_matcher *dv_matcher;
पूर्ण;

काष्ठा mlx5dr_rule_member अणु
	काष्ठा mlx5dr_ste *ste;
	/* attached to mlx5dr_rule via this */
	काष्ठा list_head list;
	/* attached to mlx5dr_ste via this */
	काष्ठा list_head use_ste_list;
पूर्ण;

काष्ठा mlx5dr_ste_action_modअगरy_field अणु
	u16 hw_field;
	u8 start;
	u8 end;
	u8 l3_type;
	u8 l4_type;
पूर्ण;

काष्ठा mlx5dr_action_reग_लिखो अणु
	काष्ठा mlx5dr_करोमुख्य *dmn;
	काष्ठा mlx5dr_icm_chunk *chunk;
	u8 *data;
	u16 num_of_actions;
	u32 index;
	u8 allow_rx:1;
	u8 allow_tx:1;
	u8 modअगरy_ttl:1;
पूर्ण;

काष्ठा mlx5dr_action_reक्रमmat अणु
	काष्ठा mlx5dr_करोमुख्य *dmn;
	u32 reक्रमmat_id;
	u32 reक्रमmat_size;
पूर्ण;

काष्ठा mlx5dr_action_dest_tbl अणु
	u8 is_fw_tbl:1;
	जोड़ अणु
		काष्ठा mlx5dr_table *tbl;
		काष्ठा अणु
			काष्ठा mlx5dr_करोमुख्य *dmn;
			u32 id;
			u32 group_id;
			क्रमागत fs_flow_table_type type;
			u64 rx_icm_addr;
			u64 tx_icm_addr;
			काष्ठा mlx5dr_action **ref_actions;
			u32 num_of_ref_actions;
		पूर्ण fw_tbl;
	पूर्ण;
पूर्ण;

काष्ठा mlx5dr_action_ctr अणु
	u32 ctr_id;
	u32 offeset;
पूर्ण;

काष्ठा mlx5dr_action_vport अणु
	काष्ठा mlx5dr_करोमुख्य *dmn;
	काष्ठा mlx5dr_cmd_vport_cap *caps;
पूर्ण;

काष्ठा mlx5dr_action_push_vlan अणु
	u32 vlan_hdr; /* tpid_pcp_dei_vid */
पूर्ण;

काष्ठा mlx5dr_action_flow_tag अणु
	u32 flow_tag;
पूर्ण;

काष्ठा mlx5dr_action अणु
	क्रमागत mlx5dr_action_type action_type;
	refcount_t refcount;

	जोड़ अणु
		व्योम *data;
		काष्ठा mlx5dr_action_reग_लिखो *reग_लिखो;
		काष्ठा mlx5dr_action_reक्रमmat *reक्रमmat;
		काष्ठा mlx5dr_action_dest_tbl *dest_tbl;
		काष्ठा mlx5dr_action_ctr *ctr;
		काष्ठा mlx5dr_action_vport *vport;
		काष्ठा mlx5dr_action_push_vlan *push_vlan;
		काष्ठा mlx5dr_action_flow_tag *flow_tag;
	पूर्ण;
पूर्ण;

क्रमागत mlx5dr_connect_type अणु
	CONNECT_HIT	= 1,
	CONNECT_MISS	= 2,
पूर्ण;

काष्ठा mlx5dr_htbl_connect_info अणु
	क्रमागत mlx5dr_connect_type type;
	जोड़ अणु
		काष्ठा mlx5dr_ste_htbl *hit_next_htbl;
		u64 miss_icm_addr;
	पूर्ण;
पूर्ण;

काष्ठा mlx5dr_rule_rx_tx अणु
	काष्ठा list_head rule_members_list;
	काष्ठा mlx5dr_matcher_rx_tx *nic_matcher;
पूर्ण;

काष्ठा mlx5dr_rule अणु
	काष्ठा mlx5dr_matcher *matcher;
	काष्ठा mlx5dr_rule_rx_tx rx;
	काष्ठा mlx5dr_rule_rx_tx tx;
	काष्ठा list_head rule_actions_list;
	u32 flow_source;
पूर्ण;

व्योम mlx5dr_rule_update_rule_member(काष्ठा mlx5dr_ste *new_ste,
				    काष्ठा mlx5dr_ste *ste);

काष्ठा mlx5dr_icm_chunk अणु
	काष्ठा mlx5dr_icm_buddy_mem *buddy_mem;
	काष्ठा list_head chunk_list;
	u32 rkey;
	u32 num_of_entries;
	u32 byte_size;
	u64 icm_addr;
	u64 mr_addr;

	/* indicates the index of this chunk in the whole memory,
	 * used क्रम deleting the chunk from the buddy
	 */
	अचिन्हित पूर्णांक seg;

	/* Memory optimisation */
	काष्ठा mlx5dr_ste *ste_arr;
	u8 *hw_ste_arr;
	काष्ठा list_head *miss_list;
पूर्ण;

अटल अंतरभूत व्योम mlx5dr_करोमुख्य_nic_lock(काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn)
अणु
	mutex_lock(&nic_dmn->mutex);
पूर्ण

अटल अंतरभूत व्योम mlx5dr_करोमुख्य_nic_unlock(काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn)
अणु
	mutex_unlock(&nic_dmn->mutex);
पूर्ण

अटल अंतरभूत व्योम mlx5dr_करोमुख्य_lock(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	mlx5dr_करोमुख्य_nic_lock(&dmn->info.rx);
	mlx5dr_करोमुख्य_nic_lock(&dmn->info.tx);
पूर्ण

अटल अंतरभूत व्योम mlx5dr_करोमुख्य_unlock(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	mlx5dr_करोमुख्य_nic_unlock(&dmn->info.tx);
	mlx5dr_करोमुख्य_nic_unlock(&dmn->info.rx);
पूर्ण

पूर्णांक mlx5dr_matcher_select_builders(काष्ठा mlx5dr_matcher *matcher,
				   काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				   क्रमागत mlx5dr_ipv outer_ipv,
				   क्रमागत mlx5dr_ipv inner_ipv);

अटल अंतरभूत पूर्णांक
mlx5dr_icm_pool_dm_type_to_entry_size(क्रमागत mlx5dr_icm_type icm_type)
अणु
	अगर (icm_type == DR_ICM_TYPE_STE)
		वापस DR_STE_SIZE;

	वापस DR_MODIFY_ACTION_SIZE;
पूर्ण

अटल अंतरभूत u32
mlx5dr_icm_pool_chunk_माप_प्रकारo_entries(क्रमागत mlx5dr_icm_chunk_size chunk_size)
अणु
	वापस 1 << chunk_size;
पूर्ण

अटल अंतरभूत पूर्णांक
mlx5dr_icm_pool_chunk_माप_प्रकारo_byte(क्रमागत mlx5dr_icm_chunk_size chunk_size,
				   क्रमागत mlx5dr_icm_type icm_type)
अणु
	पूर्णांक num_of_entries;
	पूर्णांक entry_size;

	entry_size = mlx5dr_icm_pool_dm_type_to_entry_size(icm_type);
	num_of_entries = mlx5dr_icm_pool_chunk_माप_प्रकारo_entries(chunk_size);

	वापस entry_size * num_of_entries;
पूर्ण

अटल अंतरभूत काष्ठा mlx5dr_cmd_vport_cap *
mlx5dr_get_vport_cap(काष्ठा mlx5dr_cmd_caps *caps, u32 vport)
अणु
	अगर (!caps->vports_caps ||
	    (vport >= caps->num_vports && vport != WIRE_PORT))
		वापस शून्य;

	अगर (vport == WIRE_PORT)
		vport = caps->num_vports;

	वापस &caps->vports_caps[vport];
पूर्ण

काष्ठा mlx5dr_cmd_query_flow_table_details अणु
	u8 status;
	u8 level;
	u64 sw_owner_icm_root_1;
	u64 sw_owner_icm_root_0;
पूर्ण;

काष्ठा mlx5dr_cmd_create_flow_table_attr अणु
	u32 table_type;
	u64 icm_addr_rx;
	u64 icm_addr_tx;
	u8 level;
	bool sw_owner;
	bool term_tbl;
	bool decap_en;
	bool reक्रमmat_en;
पूर्ण;

/* पूर्णांकernal API functions */
पूर्णांक mlx5dr_cmd_query_device(काष्ठा mlx5_core_dev *mdev,
			    काष्ठा mlx5dr_cmd_caps *caps);
पूर्णांक mlx5dr_cmd_query_esw_vport_context(काष्ठा mlx5_core_dev *mdev,
				       bool other_vport, u16 vport_number,
				       u64 *icm_address_rx,
				       u64 *icm_address_tx);
पूर्णांक mlx5dr_cmd_query_gvmi(काष्ठा mlx5_core_dev *mdev,
			  bool other_vport, u16 vport_number, u16 *gvmi);
पूर्णांक mlx5dr_cmd_query_esw_caps(काष्ठा mlx5_core_dev *mdev,
			      काष्ठा mlx5dr_esw_caps *caps);
पूर्णांक mlx5dr_cmd_sync_steering(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5dr_cmd_set_fte_modअगरy_and_vport(काष्ठा mlx5_core_dev *mdev,
					u32 table_type,
					u32 table_id,
					u32 group_id,
					u32 modअगरy_header_id,
					u32 vport_id);
पूर्णांक mlx5dr_cmd_del_flow_table_entry(काष्ठा mlx5_core_dev *mdev,
				    u32 table_type,
				    u32 table_id);
पूर्णांक mlx5dr_cmd_alloc_modअगरy_header(काष्ठा mlx5_core_dev *mdev,
				   u32 table_type,
				   u8 num_of_actions,
				   u64 *actions,
				   u32 *modअगरy_header_id);
पूर्णांक mlx5dr_cmd_dealloc_modअगरy_header(काष्ठा mlx5_core_dev *mdev,
				     u32 modअगरy_header_id);
पूर्णांक mlx5dr_cmd_create_empty_flow_group(काष्ठा mlx5_core_dev *mdev,
				       u32 table_type,
				       u32 table_id,
				       u32 *group_id);
पूर्णांक mlx5dr_cmd_destroy_flow_group(काष्ठा mlx5_core_dev *mdev,
				  u32 table_type,
				  u32 table_id,
				  u32 group_id);
पूर्णांक mlx5dr_cmd_create_flow_table(काष्ठा mlx5_core_dev *mdev,
				 काष्ठा mlx5dr_cmd_create_flow_table_attr *attr,
				 u64 *fdb_rx_icm_addr,
				 u32 *table_id);
पूर्णांक mlx5dr_cmd_destroy_flow_table(काष्ठा mlx5_core_dev *mdev,
				  u32 table_id,
				  u32 table_type);
पूर्णांक mlx5dr_cmd_query_flow_table(काष्ठा mlx5_core_dev *dev,
				क्रमागत fs_flow_table_type type,
				u32 table_id,
				काष्ठा mlx5dr_cmd_query_flow_table_details *output);
पूर्णांक mlx5dr_cmd_create_reक्रमmat_ctx(काष्ठा mlx5_core_dev *mdev,
				   क्रमागत mlx5_reक्रमmat_ctx_type rt,
				   माप_प्रकार reक्रमmat_size,
				   व्योम *reक्रमmat_data,
				   u32 *reक्रमmat_id);
व्योम mlx5dr_cmd_destroy_reक्रमmat_ctx(काष्ठा mlx5_core_dev *mdev,
				     u32 reक्रमmat_id);

काष्ठा mlx5dr_cmd_gid_attr अणु
	u8 gid[16];
	u8 mac[6];
	u32 roce_ver;
पूर्ण;

काष्ठा mlx5dr_cmd_qp_create_attr अणु
	u32 page_id;
	u32 pdn;
	u32 cqn;
	u32 pm_state;
	u32 service_type;
	u32 buff_umem_id;
	u32 db_umem_id;
	u32 sq_wqe_cnt;
	u32 rq_wqe_cnt;
	u32 rq_wqe_shअगरt;
	u8 isolate_vl_tc:1;
पूर्ण;

पूर्णांक mlx5dr_cmd_query_gid(काष्ठा mlx5_core_dev *mdev, u8 vhca_port_num,
			 u16 index, काष्ठा mlx5dr_cmd_gid_attr *attr);

काष्ठा mlx5dr_icm_pool *mlx5dr_icm_pool_create(काष्ठा mlx5dr_करोमुख्य *dmn,
					       क्रमागत mlx5dr_icm_type icm_type);
व्योम mlx5dr_icm_pool_destroy(काष्ठा mlx5dr_icm_pool *pool);

काष्ठा mlx5dr_icm_chunk *
mlx5dr_icm_alloc_chunk(काष्ठा mlx5dr_icm_pool *pool,
		       क्रमागत mlx5dr_icm_chunk_size chunk_size);
व्योम mlx5dr_icm_मुक्त_chunk(काष्ठा mlx5dr_icm_chunk *chunk);

व्योम mlx5dr_ste_prepare_क्रम_postsend(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				     u8 *hw_ste_p, u32 ste_size);
पूर्णांक mlx5dr_ste_htbl_init_and_postsend(काष्ठा mlx5dr_करोमुख्य *dmn,
				      काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn,
				      काष्ठा mlx5dr_ste_htbl *htbl,
				      काष्ठा mlx5dr_htbl_connect_info *connect_info,
				      bool update_hw_ste);
व्योम mlx5dr_ste_set_क्रमmatted_ste(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				  u16 gvmi,
				  काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn,
				  काष्ठा mlx5dr_ste_htbl *htbl,
				  u8 *क्रमmatted_ste,
				  काष्ठा mlx5dr_htbl_connect_info *connect_info);
व्योम mlx5dr_ste_copy_param(u8 match_criteria,
			   काष्ठा mlx5dr_match_param *set_param,
			   काष्ठा mlx5dr_match_parameters *mask);

काष्ठा mlx5dr_qp अणु
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5_wq_qp wq;
	काष्ठा mlx5_uars_page *uar;
	काष्ठा mlx5_wq_ctrl wq_ctrl;
	u32 qpn;
	काष्ठा अणु
		अचिन्हित पूर्णांक pc;
		अचिन्हित पूर्णांक cc;
		अचिन्हित पूर्णांक size;
		अचिन्हित पूर्णांक *wqe_head;
		अचिन्हित पूर्णांक wqe_cnt;
	पूर्ण sq;
	काष्ठा अणु
		अचिन्हित पूर्णांक pc;
		अचिन्हित पूर्णांक cc;
		अचिन्हित पूर्णांक size;
		अचिन्हित पूर्णांक wqe_cnt;
	पूर्ण rq;
	पूर्णांक max_अंतरभूत_data;
पूर्ण;

काष्ठा mlx5dr_cq अणु
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5_cqwq wq;
	काष्ठा mlx5_wq_ctrl wq_ctrl;
	काष्ठा mlx5_core_cq mcq;
	काष्ठा mlx5dr_qp *qp;
पूर्ण;

काष्ठा mlx5dr_mr अणु
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5_core_mkey mkey;
	dma_addr_t dma_addr;
	व्योम *addr;
	माप_प्रकार size;
पूर्ण;

#घोषणा MAX_SEND_CQE		64
#घोषणा MIN_READ_SYNC		64

काष्ठा mlx5dr_send_ring अणु
	काष्ठा mlx5dr_cq *cq;
	काष्ठा mlx5dr_qp *qp;
	काष्ठा mlx5dr_mr *mr;
	/* How much wqes are रुकोing क्रम completion */
	u32 pending_wqe;
	/* Signal request per this trash hold value */
	u16 संकेत_th;
	/* Each post_send_size less than max_post_send_size */
	u32 max_post_send_size;
	/* manage the send queue */
	u32 tx_head;
	व्योम *buf;
	u32 buf_size;
	काष्ठा ib_wc wc[MAX_SEND_CQE];
	u8 sync_buff[MIN_READ_SYNC];
	काष्ठा mlx5dr_mr *sync_mr;
	spinlock_t lock; /* Protect the data path of the send ring */
पूर्ण;

पूर्णांक mlx5dr_send_ring_alloc(काष्ठा mlx5dr_करोमुख्य *dmn);
व्योम mlx5dr_send_ring_मुक्त(काष्ठा mlx5dr_करोमुख्य *dmn,
			   काष्ठा mlx5dr_send_ring *send_ring);
पूर्णांक mlx5dr_send_ring_क्रमce_drain(काष्ठा mlx5dr_करोमुख्य *dmn);
पूर्णांक mlx5dr_send_postsend_ste(काष्ठा mlx5dr_करोमुख्य *dmn,
			     काष्ठा mlx5dr_ste *ste,
			     u8 *data,
			     u16 size,
			     u16 offset);
पूर्णांक mlx5dr_send_postsend_htbl(काष्ठा mlx5dr_करोमुख्य *dmn,
			      काष्ठा mlx5dr_ste_htbl *htbl,
			      u8 *क्रमmatted_ste, u8 *mask);
पूर्णांक mlx5dr_send_postsend_क्रमmatted_htbl(काष्ठा mlx5dr_करोमुख्य *dmn,
					काष्ठा mlx5dr_ste_htbl *htbl,
					u8 *ste_init_data,
					bool update_hw_ste);
पूर्णांक mlx5dr_send_postsend_action(काष्ठा mlx5dr_करोमुख्य *dmn,
				काष्ठा mlx5dr_action *action);

काष्ठा mlx5dr_cmd_ft_info अणु
	u32 id;
	u16 vport;
	क्रमागत fs_flow_table_type type;
पूर्ण;

काष्ठा mlx5dr_cmd_flow_destination_hw_info अणु
	क्रमागत mlx5_flow_destination_type type;
	जोड़ अणु
		u32 tir_num;
		u32 ft_num;
		u32 ft_id;
		u32 counter_id;
		काष्ठा अणु
			u16 num;
			u16 vhca_id;
			u32 reक्रमmat_id;
			u8 flags;
		पूर्ण vport;
	पूर्ण;
पूर्ण;

काष्ठा mlx5dr_cmd_fte_info अणु
	u32 dests_size;
	u32 index;
	काष्ठा mlx5_flow_context flow_context;
	u32 *val;
	काष्ठा mlx5_flow_act action;
	काष्ठा mlx5dr_cmd_flow_destination_hw_info *dest_arr;
पूर्ण;

पूर्णांक mlx5dr_cmd_set_fte(काष्ठा mlx5_core_dev *dev,
		       पूर्णांक opmod, पूर्णांक modअगरy_mask,
		       काष्ठा mlx5dr_cmd_ft_info *ft,
		       u32 group_id,
		       काष्ठा mlx5dr_cmd_fte_info *fte);

bool mlx5dr_ste_supp_ttl_cs_recalc(काष्ठा mlx5dr_cmd_caps *caps);

काष्ठा mlx5dr_fw_recalc_cs_ft अणु
	u64 rx_icm_addr;
	u32 table_id;
	u32 group_id;
	u32 modअगरy_hdr_id;
पूर्ण;

काष्ठा mlx5dr_fw_recalc_cs_ft *
mlx5dr_fw_create_recalc_cs_ft(काष्ठा mlx5dr_करोमुख्य *dmn, u32 vport_num);
व्योम mlx5dr_fw_destroy_recalc_cs_ft(काष्ठा mlx5dr_करोमुख्य *dmn,
				    काष्ठा mlx5dr_fw_recalc_cs_ft *recalc_cs_ft);
पूर्णांक mlx5dr_करोमुख्य_cache_get_recalc_cs_ft_addr(काष्ठा mlx5dr_करोमुख्य *dmn,
					      u32 vport_num,
					      u64 *rx_icm_addr);
पूर्णांक mlx5dr_fw_create_md_tbl(काष्ठा mlx5dr_करोमुख्य *dmn,
			    काष्ठा mlx5dr_cmd_flow_destination_hw_info *dest,
			    पूर्णांक num_dest,
			    bool reक्रमmat_req,
			    u32 *tbl_id,
			    u32 *group_id);
व्योम mlx5dr_fw_destroy_md_tbl(काष्ठा mlx5dr_करोमुख्य *dmn, u32 tbl_id,
			      u32 group_id);
#पूर्ण_अगर  /* _DR_TYPES_H_ */
