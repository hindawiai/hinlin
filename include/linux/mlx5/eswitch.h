<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित _MLX5_ESWITCH_
#घोषणा _MLX5_ESWITCH_

#समावेश <linux/mlx5/driver.h>
#समावेश <net/devlink.h>

#घोषणा MLX5_ESWITCH_MANAGER(mdev) MLX5_CAP_GEN(mdev, eचयन_manager)

क्रमागत अणु
	MLX5_ESWITCH_NONE,
	MLX5_ESWITCH_LEGACY,
	MLX5_ESWITCH_OFFLOADS
पूर्ण;

क्रमागत अणु
	REP_ETH,
	REP_IB,
	NUM_REP_TYPES,
पूर्ण;

क्रमागत अणु
	REP_UNREGISTERED,
	REP_REGISTERED,
	REP_LOADED,
पूर्ण;

काष्ठा mlx5_eचयन_rep;
काष्ठा mlx5_eचयन_rep_ops अणु
	पूर्णांक (*load)(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eचयन_rep *rep);
	व्योम (*unload)(काष्ठा mlx5_eचयन_rep *rep);
	व्योम *(*get_proto_dev)(काष्ठा mlx5_eचयन_rep *rep);
पूर्ण;

काष्ठा mlx5_eचयन_rep_data अणु
	व्योम *priv;
	atomic_t state;
पूर्ण;

काष्ठा mlx5_eचयन_rep अणु
	काष्ठा mlx5_eचयन_rep_data rep_data[NUM_REP_TYPES];
	u16		       vport;
	u16		       vlan;
	/* Only IB rep is using vport_index */
	u16		       vport_index;
	u32		       vlan_refcount;
	काष्ठा                 mlx5_eचयन *esw;
पूर्ण;

व्योम mlx5_eचयन_रेजिस्टर_vport_reps(काष्ठा mlx5_eचयन *esw,
				      स्थिर काष्ठा mlx5_eचयन_rep_ops *ops,
				      u8 rep_type);
व्योम mlx5_eचयन_unरेजिस्टर_vport_reps(काष्ठा mlx5_eचयन *esw, u8 rep_type);
व्योम *mlx5_eचयन_get_proto_dev(काष्ठा mlx5_eचयन *esw,
				 u16 vport_num,
				 u8 rep_type);
काष्ठा mlx5_eचयन_rep *mlx5_eचयन_vport_rep(काष्ठा mlx5_eचयन *esw,
						u16 vport_num);
व्योम *mlx5_eचयन_uplink_get_proto_dev(काष्ठा mlx5_eचयन *esw, u8 rep_type);
काष्ठा mlx5_flow_handle *
mlx5_eचयन_add_send_to_vport_rule(काष्ठा mlx5_eचयन *on_esw,
				    काष्ठा mlx5_eचयन_rep *rep, u32 sqn);

#अगर_घोषित CONFIG_MLX5_ESWITCH
क्रमागत devlink_eचयन_encap_mode
mlx5_eचयन_get_encap_mode(स्थिर काष्ठा mlx5_core_dev *dev);

bool mlx5_eचयन_reg_c1_loopback_enabled(स्थिर काष्ठा mlx5_eचयन *esw);
bool mlx5_eचयन_vport_match_metadata_enabled(स्थिर काष्ठा mlx5_eचयन *esw);

/* Reg C0 usage:
 * Reg C0 = < ESW_PFNUM_BITS(4) | ESW_VPORT BITS(12) | ESW_REG_C0_OBJ(16) >
 *
 * Highest 4 bits of the reg c0 is the PF_NUM (range 0-15), 12 bits of
 * unique non-zero vport id (range 1-4095). The rest (lowest 16 bits) is left
 * क्रम user data objects managed by a common mapping context.
 * PFNUM + VPORT comprise the SOURCE_PORT matching.
 */
#घोषणा ESW_VPORT_BITS 12
#घोषणा ESW_PFNUM_BITS 4
#घोषणा ESW_SOURCE_PORT_METADATA_BITS (ESW_PFNUM_BITS + ESW_VPORT_BITS)
#घोषणा ESW_SOURCE_PORT_METADATA_OFFSET (32 - ESW_SOURCE_PORT_METADATA_BITS)
#घोषणा ESW_REG_C0_USER_DATA_METADATA_BITS (32 - ESW_SOURCE_PORT_METADATA_BITS)
#घोषणा ESW_REG_C0_USER_DATA_METADATA_MASK GENMASK(ESW_REG_C0_USER_DATA_METADATA_BITS - 1, 0)

अटल अंतरभूत u32 mlx5_eचयन_get_vport_metadata_mask(व्योम)
अणु
	वापस GENMASK(31, 32 - ESW_SOURCE_PORT_METADATA_BITS);
पूर्ण

u32 mlx5_eचयन_get_vport_metadata_क्रम_match(काष्ठा mlx5_eचयन *esw,
					      u16 vport_num);
u32 mlx5_eचयन_get_vport_metadata_क्रम_set(काष्ठा mlx5_eचयन *esw,
					    u16 vport_num);

/* Reg C1 usage:
 * Reg C1 = < ESW_TUN_ID(12) | ESW_TUN_OPTS(12) | ESW_ZONE_ID(8) >
 *
 * Highest 12 bits of reg c1 is the encapsulation tunnel id, next 12 bits is
 * encapsulation tunnel options, and the lowest 8 bits are used क्रम zone id.
 *
 * Zone id is used to restore CT flow when packet misses on chain.
 *
 * Tunnel id and options are used together to restore the tunnel info metadata
 * on miss and to support inner header reग_लिखो by means of implicit chain 0
 * flows.
 */
#घोषणा ESW_ZONE_ID_BITS 8
#घोषणा ESW_TUN_OPTS_BITS 12
#घोषणा ESW_TUN_ID_BITS 12
#घोषणा ESW_TUN_OPTS_OFFSET ESW_ZONE_ID_BITS
#घोषणा ESW_TUN_OFFSET ESW_TUN_OPTS_OFFSET
#घोषणा ESW_ZONE_ID_MASK GENMASK(ESW_ZONE_ID_BITS - 1, 0)
#घोषणा ESW_TUN_OPTS_MASK GENMASK(32 - ESW_TUN_ID_BITS - 1, ESW_TUN_OPTS_OFFSET)
#घोषणा ESW_TUN_MASK GENMASK(31, ESW_TUN_OFFSET)
#घोषणा ESW_TUN_ID_SLOW_TABLE_GOTO_VPORT 0 /* 0 is not a valid tunnel id */
#घोषणा ESW_TUN_OPTS_SLOW_TABLE_GOTO_VPORT 0xFFF /* 0xFFF is a reserved mapping */
#घोषणा ESW_TUN_SLOW_TABLE_GOTO_VPORT ((ESW_TUN_ID_SLOW_TABLE_GOTO_VPORT << ESW_TUN_OPTS_BITS) | \
				       ESW_TUN_OPTS_SLOW_TABLE_GOTO_VPORT)
#घोषणा ESW_TUN_SLOW_TABLE_GOTO_VPORT_MARK ESW_TUN_OPTS_MASK

u8 mlx5_eचयन_mode(काष्ठा mlx5_core_dev *dev);
u16 mlx5_eचयन_get_total_vports(स्थिर काष्ठा mlx5_core_dev *dev);

#अन्यथा  /* CONFIG_MLX5_ESWITCH */

अटल अंतरभूत u8 mlx5_eचयन_mode(काष्ठा mlx5_core_dev *dev)
अणु
	वापस MLX5_ESWITCH_NONE;
पूर्ण

अटल अंतरभूत क्रमागत devlink_eचयन_encap_mode
mlx5_eचयन_get_encap_mode(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस DEVLINK_ESWITCH_ENCAP_MODE_NONE;
पूर्ण

अटल अंतरभूत bool
mlx5_eचयन_reg_c1_loopback_enabled(स्थिर काष्ठा mlx5_eचयन *esw)
अणु
	वापस false;
पूर्ण;

अटल अंतरभूत bool
mlx5_eचयन_vport_match_metadata_enabled(स्थिर काष्ठा mlx5_eचयन *esw)
अणु
	वापस false;
पूर्ण;

अटल अंतरभूत u32
mlx5_eचयन_get_vport_metadata_क्रम_match(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	वापस 0;
पूर्ण;

अटल अंतरभूत u32
mlx5_eचयन_get_vport_metadata_mask(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u16 mlx5_eचयन_get_total_vports(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_ESWITCH */

अटल अंतरभूत bool is_mdev_चयनdev_mode(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_eचयन_mode(dev) == MLX5_ESWITCH_OFFLOADS;
पूर्ण

#पूर्ण_अगर
