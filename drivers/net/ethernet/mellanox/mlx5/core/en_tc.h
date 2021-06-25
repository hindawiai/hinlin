<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित __MLX5_EN_TC_H__
#घोषणा __MLX5_EN_TC_H__

#समावेश <net/pkt_cls.h>
#समावेश "en.h"
#समावेश "eswitch.h"
#समावेश "en/tc_ct.h"
#समावेश "en/tc_tun.h"
#समावेश "en_rep.h"

#घोषणा MLX5E_TC_FLOW_ID_MASK 0x0000ffff

#अगर_घोषित CONFIG_MLX5_ESWITCH

#घोषणा NIC_FLOW_ATTR_SZ (माप(काष्ठा mlx5_flow_attr) +\
			  माप(काष्ठा mlx5_nic_flow_attr))
#घोषणा ESW_FLOW_ATTR_SZ (माप(काष्ठा mlx5_flow_attr) +\
			  माप(काष्ठा mlx5_esw_flow_attr))
#घोषणा ns_to_attr_sz(ns) (((ns) == MLX5_FLOW_NAMESPACE_FDB) ?\
			    ESW_FLOW_ATTR_SZ :\
			    NIC_FLOW_ATTR_SZ)


पूर्णांक mlx5e_tc_num_filters(काष्ठा mlx5e_priv *priv, अचिन्हित दीर्घ flags);

काष्ठा mlx5e_tc_update_priv अणु
	काष्ठा net_device *tun_dev;
पूर्ण;

काष्ठा mlx5_nic_flow_attr अणु
	u32 flow_tag;
	u32 hairpin_tirn;
	काष्ठा mlx5_flow_table *hairpin_ft;
पूर्ण;

काष्ठा mlx5_flow_attr अणु
	u32 action;
	काष्ठा mlx5_fc *counter;
	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;
	काष्ठा mlx5_ct_attr ct_attr;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	u32 chain;
	u16 prio;
	u32 dest_chain;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_table *dest_ft;
	u8 inner_match_level;
	u8 outer_match_level;
	u8 ip_version;
	u8 tun_ip_version;
	u32 flags;
	जोड़ अणु
		काष्ठा mlx5_esw_flow_attr esw_attr[0];
		काष्ठा mlx5_nic_flow_attr nic_attr[0];
	पूर्ण;
पूर्ण;

काष्ठा mlx5_rx_tun_attr अणु
	u16 decap_vport;
	जोड़ अणु
		__be32 v4;
		काष्ठा in6_addr v6;
	पूर्ण src_ip; /* Valid अगर decap_vport is not zero */
	जोड़ अणु
		__be32 v4;
		काष्ठा in6_addr v6;
	पूर्ण dst_ip; /* Valid अगर decap_vport is not zero */
	u32 vni;
पूर्ण;

#घोषणा MLX5E_TC_TABLE_CHAIN_TAG_BITS 16
#घोषणा MLX5E_TC_TABLE_CHAIN_TAG_MASK GENMASK(MLX5E_TC_TABLE_CHAIN_TAG_BITS - 1, 0)

#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)

काष्ठा tunnel_match_key अणु
	काष्ठा flow_dissector_key_control enc_control;
	काष्ठा flow_dissector_key_keyid enc_key_id;
	काष्ठा flow_dissector_key_ports enc_tp;
	काष्ठा flow_dissector_key_ip enc_ip;
	जोड़ अणु
		काष्ठा flow_dissector_key_ipv4_addrs enc_ipv4;
		काष्ठा flow_dissector_key_ipv6_addrs enc_ipv6;
	पूर्ण;

	पूर्णांक filter_अगरindex;
पूर्ण;

काष्ठा tunnel_match_enc_opts अणु
	काष्ठा flow_dissector_key_enc_opts key;
	काष्ठा flow_dissector_key_enc_opts mask;
पूर्ण;

/* Tunnel_id mapping is TUNNEL_INFO_BITS + ENC_OPTS_BITS.
 * Upper TUNNEL_INFO_BITS क्रम general tunnel info.
 * Lower ENC_OPTS_BITS bits क्रम enc_opts.
 */
#घोषणा TUNNEL_INFO_BITS 12
#घोषणा TUNNEL_INFO_BITS_MASK GENMASK(TUNNEL_INFO_BITS - 1, 0)
#घोषणा ENC_OPTS_BITS 12
#घोषणा ENC_OPTS_BITS_MASK GENMASK(ENC_OPTS_BITS - 1, 0)
#घोषणा TUNNEL_ID_BITS (TUNNEL_INFO_BITS + ENC_OPTS_BITS)
#घोषणा TUNNEL_ID_MASK GENMASK(TUNNEL_ID_BITS - 1, 0)

क्रमागत अणु
	MLX5E_TC_FLAG_INGRESS_BIT,
	MLX5E_TC_FLAG_EGRESS_BIT,
	MLX5E_TC_FLAG_NIC_OFFLOAD_BIT,
	MLX5E_TC_FLAG_ESW_OFFLOAD_BIT,
	MLX5E_TC_FLAG_FT_OFFLOAD_BIT,
	MLX5E_TC_FLAG_LAST_EXPORTED_BIT = MLX5E_TC_FLAG_FT_OFFLOAD_BIT,
पूर्ण;

#घोषणा MLX5_TC_FLAG(flag) BIT(MLX5E_TC_FLAG_##flag##_BIT)

पूर्णांक mlx5e_tc_esw_init(काष्ठा rhashtable *tc_ht);
व्योम mlx5e_tc_esw_cleanup(काष्ठा rhashtable *tc_ht);
bool mlx5e_is_eचयन_flow(काष्ठा mlx5e_tc_flow *flow);

पूर्णांक mlx5e_configure_flower(काष्ठा net_device *dev, काष्ठा mlx5e_priv *priv,
			   काष्ठा flow_cls_offload *f, अचिन्हित दीर्घ flags);
पूर्णांक mlx5e_delete_flower(काष्ठा net_device *dev, काष्ठा mlx5e_priv *priv,
			काष्ठा flow_cls_offload *f, अचिन्हित दीर्घ flags);

पूर्णांक mlx5e_stats_flower(काष्ठा net_device *dev, काष्ठा mlx5e_priv *priv,
		       काष्ठा flow_cls_offload *f, अचिन्हित दीर्घ flags);

पूर्णांक mlx5e_tc_configure_matchall(काष्ठा mlx5e_priv *priv,
				काष्ठा tc_cls_matchall_offload *f);
पूर्णांक mlx5e_tc_delete_matchall(काष्ठा mlx5e_priv *priv,
			     काष्ठा tc_cls_matchall_offload *f);
व्योम mlx5e_tc_stats_matchall(काष्ठा mlx5e_priv *priv,
			     काष्ठा tc_cls_matchall_offload *ma);

काष्ठा mlx5e_encap_entry;
व्योम mlx5e_tc_encap_flows_add(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_encap_entry *e,
			      काष्ठा list_head *flow_list);
व्योम mlx5e_tc_encap_flows_del(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_encap_entry *e,
			      काष्ठा list_head *flow_list);
bool mlx5e_encap_take(काष्ठा mlx5e_encap_entry *e);
व्योम mlx5e_encap_put(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_encap_entry *e);

व्योम mlx5e_take_all_encap_flows(काष्ठा mlx5e_encap_entry *e, काष्ठा list_head *flow_list);
व्योम mlx5e_put_flow_list(काष्ठा mlx5e_priv *priv, काष्ठा list_head *flow_list);

काष्ठा mlx5e_neigh_hash_entry;
काष्ठा mlx5e_encap_entry *
mlx5e_get_next_init_encap(काष्ठा mlx5e_neigh_hash_entry *nhe,
			  काष्ठा mlx5e_encap_entry *e);
व्योम mlx5e_tc_update_neigh_used_value(काष्ठा mlx5e_neigh_hash_entry *nhe);

व्योम mlx5e_tc_reoffload_flows_work(काष्ठा work_काष्ठा *work);

क्रमागत mlx5e_tc_attr_to_reg अणु
	CHAIN_TO_REG,
	VPORT_TO_REG,
	TUNNEL_TO_REG,
	CTSTATE_TO_REG,
	ZONE_TO_REG,
	ZONE_RESTORE_TO_REG,
	MARK_TO_REG,
	LABELS_TO_REG,
	FTEID_TO_REG,
	NIC_CHAIN_TO_REG,
	NIC_ZONE_RESTORE_TO_REG,
पूर्ण;

काष्ठा mlx5e_tc_attr_to_reg_mapping अणु
	पूर्णांक mfield; /* reग_लिखो field */
	पूर्णांक moffset; /* offset of mfield */
	पूर्णांक mlen; /* bytes to reग_लिखो/match */

	पूर्णांक soffset; /* offset of spec क्रम match */
पूर्ण;

बाह्य काष्ठा mlx5e_tc_attr_to_reg_mapping mlx5e_tc_attr_to_reg_mappings[];

bool mlx5e_is_valid_eचयन_fwd_dev(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *out_dev);

पूर्णांक mlx5e_tc_match_to_reg_set(काष्ठा mlx5_core_dev *mdev,
			      काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts,
			      क्रमागत mlx5_flow_namespace_type ns,
			      क्रमागत mlx5e_tc_attr_to_reg type,
			      u32 data);

व्योम mlx5e_tc_match_to_reg_mod_hdr_change(काष्ठा mlx5_core_dev *mdev,
					  काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts,
					  क्रमागत mlx5e_tc_attr_to_reg type,
					  पूर्णांक act_id, u32 data);

व्योम mlx5e_tc_match_to_reg_match(काष्ठा mlx5_flow_spec *spec,
				 क्रमागत mlx5e_tc_attr_to_reg type,
				 u32 data,
				 u32 mask);

व्योम mlx5e_tc_match_to_reg_get_match(काष्ठा mlx5_flow_spec *spec,
				     क्रमागत mlx5e_tc_attr_to_reg type,
				     u32 *data,
				     u32 *mask);

पूर्णांक mlx5e_tc_match_to_reg_set_and_get_id(काष्ठा mlx5_core_dev *mdev,
					 काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts,
					 क्रमागत mlx5_flow_namespace_type ns,
					 क्रमागत mlx5e_tc_attr_to_reg type,
					 u32 data);

पूर्णांक mlx5e_tc_add_flow_mod_hdr(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
			      काष्ठा mlx5e_tc_flow *flow);

पूर्णांक alloc_mod_hdr_actions(काष्ठा mlx5_core_dev *mdev,
			  पूर्णांक namespace,
			  काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts);
व्योम dealloc_mod_hdr_actions(काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts);

काष्ठा mlx5e_tc_flow;
u32 mlx5e_tc_get_flow_tun_id(काष्ठा mlx5e_tc_flow *flow);

व्योम mlx5e_tc_set_ethertype(काष्ठा mlx5_core_dev *mdev,
			    काष्ठा flow_match_basic *match, bool outer,
			    व्योम *headers_c, व्योम *headers_v);

पूर्णांक mlx5e_tc_nic_init(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_tc_nic_cleanup(काष्ठा mlx5e_priv *priv);

पूर्णांक mlx5e_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
			    व्योम *cb_priv);

काष्ठा mlx5_flow_handle *
mlx5e_add_offloaded_nic_rule(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5_flow_spec *spec,
			     काष्ठा mlx5_flow_attr *attr);
व्योम mlx5e_del_offloaded_nic_rule(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5_flow_handle *rule,
				  काष्ठा mlx5_flow_attr *attr);

काष्ठा mlx5_flow_handle *
mlx5_tc_rule_insert(काष्ठा mlx5e_priv *priv,
		    काष्ठा mlx5_flow_spec *spec,
		    काष्ठा mlx5_flow_attr *attr);
व्योम
mlx5_tc_rule_delete(काष्ठा mlx5e_priv *priv,
		    काष्ठा mlx5_flow_handle *rule,
		    काष्ठा mlx5_flow_attr *attr);

bool mlx5e_tc_is_vf_tunnel(काष्ठा net_device *out_dev, काष्ठा net_device *route_dev);
पूर्णांक mlx5e_tc_query_route_vport(काष्ठा net_device *out_dev, काष्ठा net_device *route_dev,
			       u16 *vport);

#अन्यथा /* CONFIG_MLX5_CLS_ACT */
अटल अंतरभूत पूर्णांक  mlx5e_tc_nic_init(काष्ठा mlx5e_priv *priv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5e_tc_nic_cleanup(काष्ठा mlx5e_priv *priv) अणुपूर्ण
अटल अंतरभूत पूर्णांक
mlx5e_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data, व्योम *cb_priv)
अणु वापस -EOPNOTSUPP; पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_CLS_ACT */

काष्ठा mlx5_flow_attr *mlx5_alloc_flow_attr(क्रमागत mlx5_flow_namespace_type type);

काष्ठा mlx5_flow_handle *
mlx5e_add_offloaded_nic_rule(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5_flow_spec *spec,
			     काष्ठा mlx5_flow_attr *attr);
व्योम mlx5e_del_offloaded_nic_rule(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5_flow_handle *rule,
				  काष्ठा mlx5_flow_attr *attr);

#अन्यथा /* CONFIG_MLX5_ESWITCH */
अटल अंतरभूत पूर्णांक  mlx5e_tc_nic_init(काष्ठा mlx5e_priv *priv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5e_tc_nic_cleanup(काष्ठा mlx5e_priv *priv) अणुपूर्ण
अटल अंतरभूत पूर्णांक  mlx5e_tc_num_filters(काष्ठा mlx5e_priv *priv,
					अचिन्हित दीर्घ flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
mlx5e_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data, व्योम *cb_priv)
अणु वापस -EOPNOTSUPP; पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)
अटल अंतरभूत bool mlx5e_cqe_regb_chain(काष्ठा mlx5_cqe64 *cqe)
अणु
#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
	u32 chain, reg_b;

	reg_b = be32_to_cpu(cqe->ft_metadata);

	अगर (reg_b >> (MLX5E_TC_TABLE_CHAIN_TAG_BITS + ESW_ZONE_ID_BITS))
		वापस false;

	chain = reg_b & MLX5E_TC_TABLE_CHAIN_TAG_MASK;
	अगर (chain)
		वापस true;
#पूर्ण_अगर

	वापस false;
पूर्ण

bool mlx5e_tc_update_skb(काष्ठा mlx5_cqe64 *cqe, काष्ठा sk_buff *skb);
#अन्यथा /* CONFIG_MLX5_CLS_ACT */
अटल अंतरभूत bool mlx5e_cqe_regb_chain(काष्ठा mlx5_cqe64 *cqe)
अणु वापस false; पूर्ण
अटल अंतरभूत bool
mlx5e_tc_update_skb(काष्ठा mlx5_cqe64 *cqe, काष्ठा sk_buff *skb)
अणु वापस true; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MLX5_EN_TC_H__ */
