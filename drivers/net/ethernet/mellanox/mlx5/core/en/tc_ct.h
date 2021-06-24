<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2018 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_TC_CT_H__
#घोषणा __MLX5_EN_TC_CT_H__

#समावेश <net/pkt_cls.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <net/tc_act/tc_ct.h>

#समावेश "en.h"

काष्ठा mlx5_flow_attr;
काष्ठा mlx5e_tc_mod_hdr_acts;
काष्ठा mlx5_rep_uplink_priv;
काष्ठा mlx5e_tc_flow;
काष्ठा mlx5e_priv;

काष्ठा mlx5_fs_chains;
काष्ठा mlx5_tc_ct_priv;
काष्ठा mlx5_ct_flow;

काष्ठा nf_flowtable;

काष्ठा mlx5_ct_attr अणु
	u16 zone;
	u16 ct_action;
	काष्ठा mlx5_ct_flow *ct_flow;
	काष्ठा nf_flowtable *nf_ft;
	u32 ct_labels_id;
पूर्ण;

#घोषणा zone_to_reg_ct अणु\
	.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_C_2,\
	.moffset = 0,\
	.mlen = 2,\
	.soffset = MLX5_BYTE_OFF(fte_match_param,\
				 misc_parameters_2.metadata_reg_c_2) + 2,\
पूर्ण

#घोषणा ctstate_to_reg_ct अणु\
	.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_C_2,\
	.moffset = 2,\
	.mlen = 2,\
	.soffset = MLX5_BYTE_OFF(fte_match_param,\
				 misc_parameters_2.metadata_reg_c_2),\
पूर्ण

#घोषणा mark_to_reg_ct अणु\
	.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_C_3,\
	.moffset = 0,\
	.mlen = 4,\
	.soffset = MLX5_BYTE_OFF(fte_match_param,\
				 misc_parameters_2.metadata_reg_c_3),\
पूर्ण

#घोषणा labels_to_reg_ct अणु\
	.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_C_4,\
	.moffset = 0,\
	.mlen = 4,\
	.soffset = MLX5_BYTE_OFF(fte_match_param,\
				 misc_parameters_2.metadata_reg_c_4),\
पूर्ण

#घोषणा fteid_to_reg_ct अणु\
	.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_C_5,\
	.moffset = 0,\
	.mlen = 4,\
	.soffset = MLX5_BYTE_OFF(fte_match_param,\
				 misc_parameters_2.metadata_reg_c_5),\
पूर्ण

#घोषणा zone_restore_to_reg_ct अणु\
	.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_C_1,\
	.moffset = 0,\
	.mlen = (ESW_ZONE_ID_BITS / 8),\
	.soffset = MLX5_BYTE_OFF(fte_match_param,\
				 misc_parameters_2.metadata_reg_c_1) + 3,\
पूर्ण

#घोषणा nic_zone_restore_to_reg_ct अणु\
	.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_B,\
	.moffset = 2,\
	.mlen = (ESW_ZONE_ID_BITS / 8),\
पूर्ण

#घोषणा REG_MAPPING_MLEN(reg) (mlx5e_tc_attr_to_reg_mappings[reg].mlen)
#घोषणा REG_MAPPING_MOFFSET(reg) (mlx5e_tc_attr_to_reg_mappings[reg].moffset)
#घोषणा REG_MAPPING_SHIFT(reg) (REG_MAPPING_MOFFSET(reg) * 8)

#अगर IS_ENABLED(CONFIG_MLX5_TC_CT)

काष्ठा mlx5_tc_ct_priv *
mlx5_tc_ct_init(काष्ठा mlx5e_priv *priv, काष्ठा mlx5_fs_chains *chains,
		काष्ठा mod_hdr_tbl *mod_hdr,
		क्रमागत mlx5_flow_namespace_type ns_type);
व्योम
mlx5_tc_ct_clean(काष्ठा mlx5_tc_ct_priv *ct_priv);

व्योम
mlx5_tc_ct_match_del(काष्ठा mlx5_tc_ct_priv *priv, काष्ठा mlx5_ct_attr *ct_attr);

पूर्णांक
mlx5_tc_ct_match_add(काष्ठा mlx5_tc_ct_priv *priv,
		     काष्ठा mlx5_flow_spec *spec,
		     काष्ठा flow_cls_offload *f,
		     काष्ठा mlx5_ct_attr *ct_attr,
		     काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5_tc_ct_add_no_trk_match(काष्ठा mlx5_flow_spec *spec);
पूर्णांक
mlx5_tc_ct_parse_action(काष्ठा mlx5_tc_ct_priv *priv,
			काष्ठा mlx5_flow_attr *attr,
			स्थिर काष्ठा flow_action_entry *act,
			काष्ठा netlink_ext_ack *extack);

काष्ठा mlx5_flow_handle *
mlx5_tc_ct_flow_offload(काष्ठा mlx5_tc_ct_priv *priv,
			काष्ठा mlx5e_tc_flow *flow,
			काष्ठा mlx5_flow_spec *spec,
			काष्ठा mlx5_flow_attr *attr,
			काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts);
व्योम
mlx5_tc_ct_delete_flow(काष्ठा mlx5_tc_ct_priv *priv,
		       काष्ठा mlx5e_tc_flow *flow,
		       काष्ठा mlx5_flow_attr *attr);

bool
mlx5e_tc_ct_restore_flow(काष्ठा mlx5_tc_ct_priv *ct_priv,
			 काष्ठा sk_buff *skb, u8 zone_restore_id);

#अन्यथा /* CONFIG_MLX5_TC_CT */

अटल अंतरभूत काष्ठा mlx5_tc_ct_priv *
mlx5_tc_ct_init(काष्ठा mlx5e_priv *priv, काष्ठा mlx5_fs_chains *chains,
		काष्ठा mod_hdr_tbl *mod_hdr,
		क्रमागत mlx5_flow_namespace_type ns_type)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
mlx5_tc_ct_clean(काष्ठा mlx5_tc_ct_priv *ct_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम
mlx5_tc_ct_match_del(काष्ठा mlx5_tc_ct_priv *priv, काष्ठा mlx5_ct_attr *ct_attr) अणुपूर्ण

अटल अंतरभूत पूर्णांक
mlx5_tc_ct_match_add(काष्ठा mlx5_tc_ct_priv *priv,
		     काष्ठा mlx5_flow_spec *spec,
		     काष्ठा flow_cls_offload *f,
		     काष्ठा mlx5_ct_attr *ct_attr,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CT))
		वापस 0;

	NL_SET_ERR_MSG_MOD(extack, "mlx5 tc ct offload isn't enabled.");
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
mlx5_tc_ct_add_no_trk_match(काष्ठा mlx5_flow_spec *spec)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
mlx5_tc_ct_parse_action(काष्ठा mlx5_tc_ct_priv *priv,
			काष्ठा mlx5_flow_attr *attr,
			स्थिर काष्ठा flow_action_entry *act,
			काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG_MOD(extack, "mlx5 tc ct offload isn't enabled.");
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा mlx5_flow_handle *
mlx5_tc_ct_flow_offload(काष्ठा mlx5_tc_ct_priv *priv,
			काष्ठा mlx5e_tc_flow *flow,
			काष्ठा mlx5_flow_spec *spec,
			काष्ठा mlx5_flow_attr *attr,
			काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम
mlx5_tc_ct_delete_flow(काष्ठा mlx5_tc_ct_priv *priv,
		       काष्ठा mlx5e_tc_flow *flow,
		       काष्ठा mlx5_flow_attr *attr)
अणु
पूर्ण

अटल अंतरभूत bool
mlx5e_tc_ct_restore_flow(काष्ठा mlx5_tc_ct_priv *ct_priv,
			 काष्ठा sk_buff *skb, u8 zone_restore_id)
अणु
	अगर (!zone_restore_id)
		वापस true;

	वापस false;
पूर्ण

#पूर्ण_अगर /* !IS_ENABLED(CONFIG_MLX5_TC_CT) */
#पूर्ण_अगर /* __MLX5_EN_TC_CT_H__ */
