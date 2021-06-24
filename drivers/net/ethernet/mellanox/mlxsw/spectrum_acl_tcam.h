<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_SPECTRUM_ACL_TCAM_H
#घोषणा _MLXSW_SPECTRUM_ACL_TCAM_H

#समावेश <linux/list.h>
#समावेश <linux/parman.h>

#समावेश "reg.h"
#समावेश "spectrum.h"
#समावेश "core_acl_flex_keys.h"

काष्ठा mlxsw_sp_acl_tcam अणु
	अचिन्हित दीर्घ *used_regions; /* bit array */
	अचिन्हित पूर्णांक max_regions;
	अचिन्हित दीर्घ *used_groups;  /* bit array */
	अचिन्हित पूर्णांक max_groups;
	अचिन्हित पूर्णांक max_group_size;
	काष्ठा mutex lock; /* guards vregion list */
	काष्ठा list_head vregion_list;
	u32 vregion_rehash_पूर्णांकrvl;   /* ms */
	अचिन्हित दीर्घ priv[];
	/* priv has to be always the last item */
पूर्ण;

माप_प्रकार mlxsw_sp_acl_tcam_priv_size(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_acl_tcam_init(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_acl_tcam *tcam);
व्योम mlxsw_sp_acl_tcam_fini(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_acl_tcam *tcam);
u32 mlxsw_sp_acl_tcam_vregion_rehash_पूर्णांकrvl_get(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_acl_tcam *tcam);
पूर्णांक mlxsw_sp_acl_tcam_vregion_rehash_पूर्णांकrvl_set(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_acl_tcam *tcam,
						u32 val);
पूर्णांक mlxsw_sp_acl_tcam_priority_get(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_acl_rule_info *rulei,
				   u32 *priority, bool fillup_priority);

काष्ठा mlxsw_sp_acl_profile_ops अणु
	माप_प्रकार ruleset_priv_size;
	पूर्णांक (*ruleset_add)(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_acl_tcam *tcam, व्योम *ruleset_priv,
			   काष्ठा mlxsw_afk_element_usage *पंचांगplt_elusage,
			   अचिन्हित पूर्णांक *p_min_prio, अचिन्हित पूर्णांक *p_max_prio);
	व्योम (*ruleset_del)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *ruleset_priv);
	पूर्णांक (*ruleset_bind)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *ruleset_priv,
			    काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    bool ingress);
	व्योम (*ruleset_unbind)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *ruleset_priv,
			       काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       bool ingress);
	u16 (*ruleset_group_id)(व्योम *ruleset_priv);
	माप_प्रकार rule_priv_size;
	पूर्णांक (*rule_add)(काष्ठा mlxsw_sp *mlxsw_sp,
			व्योम *ruleset_priv, व्योम *rule_priv,
			काष्ठा mlxsw_sp_acl_rule_info *rulei);
	व्योम (*rule_del)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *rule_priv);
	पूर्णांक (*rule_action_replace)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *rule_priv,
				   काष्ठा mlxsw_sp_acl_rule_info *rulei);
	पूर्णांक (*rule_activity_get)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *rule_priv,
				 bool *activity);
पूर्ण;

स्थिर काष्ठा mlxsw_sp_acl_profile_ops *
mlxsw_sp_acl_tcam_profile_ops(काष्ठा mlxsw_sp *mlxsw_sp,
			      क्रमागत mlxsw_sp_acl_profile profile);

#घोषणा MLXSW_SP_ACL_TCAM_REGION_BASE_COUNT 16
#घोषणा MLXSW_SP_ACL_TCAM_REGION_RESIZE_STEP 16

#घोषणा MLXSW_SP_ACL_TCAM_CATCHALL_PRIO (~0U)

#घोषणा MLXSW_SP_ACL_TCAM_MASK_LEN \
	(MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN * BITS_PER_BYTE)

काष्ठा mlxsw_sp_acl_tcam_group;
काष्ठा mlxsw_sp_acl_tcam_vregion;

काष्ठा mlxsw_sp_acl_tcam_region अणु
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion;
	काष्ठा mlxsw_sp_acl_tcam_group *group;
	काष्ठा list_head list; /* Member of a TCAM group */
	क्रमागत mlxsw_reg_ptar_key_type key_type;
	u16 id; /* ACL ID and region ID - they are same */
	अक्षर tcam_region_info[MLXSW_REG_PXXX_TCAM_REGION_INFO_LEN];
	काष्ठा mlxsw_afk_key_info *key_info;
	काष्ठा mlxsw_sp *mlxsw_sp;
	अचिन्हित दीर्घ priv[];
	/* priv has to be always the last item */
पूर्ण;

काष्ठा mlxsw_sp_acl_ctcam_region अणु
	काष्ठा parman *parman;
	स्थिर काष्ठा mlxsw_sp_acl_ctcam_region_ops *ops;
	काष्ठा mlxsw_sp_acl_tcam_region *region;
पूर्ण;

काष्ठा mlxsw_sp_acl_ctcam_chunk अणु
	काष्ठा parman_prio parman_prio;
पूर्ण;

काष्ठा mlxsw_sp_acl_ctcam_entry अणु
	काष्ठा parman_item parman_item;
पूर्ण;

काष्ठा mlxsw_sp_acl_ctcam_region_ops अणु
	पूर्णांक (*entry_insert)(काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
			    काष्ठा mlxsw_sp_acl_ctcam_entry *centry,
			    स्थिर अक्षर *mask);
	व्योम (*entry_हटाओ)(काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
			     काष्ठा mlxsw_sp_acl_ctcam_entry *centry);
पूर्ण;

पूर्णांक
mlxsw_sp_acl_ctcam_region_init(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
			       काष्ठा mlxsw_sp_acl_tcam_region *region,
			       स्थिर काष्ठा mlxsw_sp_acl_ctcam_region_ops *ops);
व्योम mlxsw_sp_acl_ctcam_region_fini(काष्ठा mlxsw_sp_acl_ctcam_region *cregion);
व्योम mlxsw_sp_acl_ctcam_chunk_init(काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
				   काष्ठा mlxsw_sp_acl_ctcam_chunk *cchunk,
				   अचिन्हित पूर्णांक priority);
व्योम mlxsw_sp_acl_ctcam_chunk_fini(काष्ठा mlxsw_sp_acl_ctcam_chunk *cchunk);
पूर्णांक mlxsw_sp_acl_ctcam_entry_add(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
				 काष्ठा mlxsw_sp_acl_ctcam_chunk *cchunk,
				 काष्ठा mlxsw_sp_acl_ctcam_entry *centry,
				 काष्ठा mlxsw_sp_acl_rule_info *rulei,
				 bool fillup_priority);
व्योम mlxsw_sp_acl_ctcam_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
				  काष्ठा mlxsw_sp_acl_ctcam_chunk *cchunk,
				  काष्ठा mlxsw_sp_acl_ctcam_entry *centry);
पूर्णांक mlxsw_sp_acl_ctcam_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					    काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
					    काष्ठा mlxsw_sp_acl_ctcam_entry *centry,
					    काष्ठा mlxsw_sp_acl_rule_info *rulei);
अटल अंतरभूत अचिन्हित पूर्णांक
mlxsw_sp_acl_ctcam_entry_offset(काष्ठा mlxsw_sp_acl_ctcam_entry *centry)
अणु
	वापस centry->parman_item.index;
पूर्ण

क्रमागत mlxsw_sp_acl_atcam_region_type अणु
	MLXSW_SP_ACL_ATCAM_REGION_TYPE_2KB,
	MLXSW_SP_ACL_ATCAM_REGION_TYPE_4KB,
	MLXSW_SP_ACL_ATCAM_REGION_TYPE_8KB,
	MLXSW_SP_ACL_ATCAM_REGION_TYPE_12KB,
	__MLXSW_SP_ACL_ATCAM_REGION_TYPE_MAX,
पूर्ण;

#घोषणा MLXSW_SP_ACL_ATCAM_REGION_TYPE_MAX \
	(__MLXSW_SP_ACL_ATCAM_REGION_TYPE_MAX - 1)

काष्ठा mlxsw_sp_acl_atcam अणु
	काष्ठा mlxsw_sp_acl_erp_core *erp_core;
पूर्ण;

काष्ठा mlxsw_sp_acl_atcam_region अणु
	काष्ठा rhashtable entries_ht; /* A-TCAM only */
	काष्ठा list_head entries_list; /* A-TCAM only */
	काष्ठा mlxsw_sp_acl_ctcam_region cregion;
	स्थिर काष्ठा mlxsw_sp_acl_atcam_region_ops *ops;
	काष्ठा mlxsw_sp_acl_tcam_region *region;
	काष्ठा mlxsw_sp_acl_atcam *atcam;
	क्रमागत mlxsw_sp_acl_atcam_region_type type;
	काष्ठा mlxsw_sp_acl_erp_table *erp_table;
	व्योम *priv;
पूर्ण;

काष्ठा mlxsw_sp_acl_atcam_entry_ht_key अणु
	अक्षर full_enc_key[MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN]; /* Encoded
								 * key.
								 */
	u8 erp_id;
पूर्ण;

काष्ठा mlxsw_sp_acl_atcam_chunk अणु
	काष्ठा mlxsw_sp_acl_ctcam_chunk cchunk;
पूर्ण;

काष्ठा mlxsw_sp_acl_atcam_entry अणु
	काष्ठा rhash_head ht_node;
	काष्ठा list_head list; /* Member in entries_list */
	काष्ठा mlxsw_sp_acl_atcam_entry_ht_key ht_key;
	अक्षर enc_key[MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN]; /* Encoded key,
							    * minus delta bits.
							    */
	काष्ठा अणु
		u16 start;
		u8 mask;
		u8 value;
	पूर्ण delta_info;
	काष्ठा mlxsw_sp_acl_ctcam_entry centry;
	काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id;
	काष्ठा mlxsw_sp_acl_erp_mask *erp_mask;
पूर्ण;

अटल अंतरभूत काष्ठा mlxsw_sp_acl_atcam_region *
mlxsw_sp_acl_tcam_cregion_aregion(काष्ठा mlxsw_sp_acl_ctcam_region *cregion)
अणु
	वापस container_of(cregion, काष्ठा mlxsw_sp_acl_atcam_region, cregion);
पूर्ण

अटल अंतरभूत काष्ठा mlxsw_sp_acl_atcam_entry *
mlxsw_sp_acl_tcam_centry_aentry(काष्ठा mlxsw_sp_acl_ctcam_entry *centry)
अणु
	वापस container_of(centry, काष्ठा mlxsw_sp_acl_atcam_entry, centry);
पूर्ण

पूर्णांक mlxsw_sp_acl_atcam_region_associate(काष्ठा mlxsw_sp *mlxsw_sp,
					u16 region_id);
पूर्णांक
mlxsw_sp_acl_atcam_region_init(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_atcam *atcam,
			       काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			       काष्ठा mlxsw_sp_acl_tcam_region *region,
			       व्योम *hपूर्णांकs_priv,
			       स्थिर काष्ठा mlxsw_sp_acl_ctcam_region_ops *ops);
व्योम mlxsw_sp_acl_atcam_region_fini(काष्ठा mlxsw_sp_acl_atcam_region *aregion);
व्योम mlxsw_sp_acl_atcam_chunk_init(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				   काष्ठा mlxsw_sp_acl_atcam_chunk *achunk,
				   अचिन्हित पूर्णांक priority);
व्योम mlxsw_sp_acl_atcam_chunk_fini(काष्ठा mlxsw_sp_acl_atcam_chunk *achunk);
पूर्णांक mlxsw_sp_acl_atcam_entry_add(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				 काष्ठा mlxsw_sp_acl_atcam_chunk *achunk,
				 काष्ठा mlxsw_sp_acl_atcam_entry *aentry,
				 काष्ठा mlxsw_sp_acl_rule_info *rulei);
व्योम mlxsw_sp_acl_atcam_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				  काष्ठा mlxsw_sp_acl_atcam_chunk *achunk,
				  काष्ठा mlxsw_sp_acl_atcam_entry *aentry);
पूर्णांक mlxsw_sp_acl_atcam_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					    काष्ठा mlxsw_sp_acl_atcam_region *aregion,
					    काष्ठा mlxsw_sp_acl_atcam_entry *aentry,
					    काष्ठा mlxsw_sp_acl_rule_info *rulei);
पूर्णांक mlxsw_sp_acl_atcam_init(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_acl_atcam *atcam);
व्योम mlxsw_sp_acl_atcam_fini(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_acl_atcam *atcam);
व्योम *
mlxsw_sp_acl_atcam_rehash_hपूर्णांकs_get(काष्ठा mlxsw_sp_acl_atcam_region *aregion);
व्योम mlxsw_sp_acl_atcam_rehash_hपूर्णांकs_put(व्योम *hपूर्णांकs_priv);

काष्ठा mlxsw_sp_acl_erp_delta;

u16 mlxsw_sp_acl_erp_delta_start(स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta);
u8 mlxsw_sp_acl_erp_delta_mask(स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta);
u8 mlxsw_sp_acl_erp_delta_value(स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta,
				स्थिर अक्षर *enc_key);
व्योम mlxsw_sp_acl_erp_delta_clear(स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta,
				  स्थिर अक्षर *enc_key);

काष्ठा mlxsw_sp_acl_erp_mask;

bool
mlxsw_sp_acl_erp_mask_is_ctcam(स्थिर काष्ठा mlxsw_sp_acl_erp_mask *erp_mask);
u8 mlxsw_sp_acl_erp_mask_erp_id(स्थिर काष्ठा mlxsw_sp_acl_erp_mask *erp_mask);
स्थिर काष्ठा mlxsw_sp_acl_erp_delta *
mlxsw_sp_acl_erp_delta(स्थिर काष्ठा mlxsw_sp_acl_erp_mask *erp_mask);
काष्ठा mlxsw_sp_acl_erp_mask *
mlxsw_sp_acl_erp_mask_get(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			  स्थिर अक्षर *mask, bool ctcam);
व्योम mlxsw_sp_acl_erp_mask_put(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			       काष्ठा mlxsw_sp_acl_erp_mask *erp_mask);
पूर्णांक mlxsw_sp_acl_erp_bf_insert(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			       काष्ठा mlxsw_sp_acl_erp_mask *erp_mask,
			       काष्ठा mlxsw_sp_acl_atcam_entry *aentry);
व्योम mlxsw_sp_acl_erp_bf_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				काष्ठा mlxsw_sp_acl_erp_mask *erp_mask,
				काष्ठा mlxsw_sp_acl_atcam_entry *aentry);
व्योम *
mlxsw_sp_acl_erp_rehash_hपूर्णांकs_get(काष्ठा mlxsw_sp_acl_atcam_region *aregion);
व्योम mlxsw_sp_acl_erp_rehash_hपूर्णांकs_put(व्योम *hपूर्णांकs_priv);
पूर्णांक mlxsw_sp_acl_erp_region_init(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				 व्योम *hपूर्णांकs_priv);
व्योम mlxsw_sp_acl_erp_region_fini(काष्ठा mlxsw_sp_acl_atcam_region *aregion);
पूर्णांक mlxsw_sp_acl_erps_init(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_acl_atcam *atcam);
व्योम mlxsw_sp_acl_erps_fini(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_acl_atcam *atcam);

काष्ठा mlxsw_sp_acl_bf;

पूर्णांक
mlxsw_sp_acl_bf_entry_add(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_acl_bf *bf,
			  काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			  अचिन्हित पूर्णांक erp_bank,
			  काष्ठा mlxsw_sp_acl_atcam_entry *aentry);
व्योम
mlxsw_sp_acl_bf_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_acl_bf *bf,
			  काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			  अचिन्हित पूर्णांक erp_bank,
			  काष्ठा mlxsw_sp_acl_atcam_entry *aentry);
काष्ठा mlxsw_sp_acl_bf *
mlxsw_sp_acl_bf_init(काष्ठा mlxsw_sp *mlxsw_sp, अचिन्हित पूर्णांक num_erp_banks);
व्योम mlxsw_sp_acl_bf_fini(काष्ठा mlxsw_sp_acl_bf *bf);

#पूर्ण_अगर
