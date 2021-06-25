<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies. */

#अगर_अघोषित __MLX5E_DCBNL_H__
#घोषणा __MLX5E_DCBNL_H__

#अगर_घोषित CONFIG_MLX5_CORE_EN_DCB

#घोषणा MLX5E_MAX_PRIORITY (8)

काष्ठा mlx5e_cee_config अणु
	/* bw pct क्रम priority group */
	u8                         pg_bw_pct[CEE_DCBX_MAX_PGS];
	u8                         prio_to_pg_map[CEE_DCBX_MAX_PRIO];
	bool                       pfc_setting[CEE_DCBX_MAX_PRIO];
	bool                       pfc_enable;
पूर्ण;

काष्ठा mlx5e_dcbx अणु
	क्रमागत mlx5_dcbx_oper_mode   mode;
	काष्ठा mlx5e_cee_config    cee_cfg; /* pending configuration */
	u8                         dscp_app_cnt;

	/* The only setting that cannot be पढ़ो from FW */
	u8                         tc_tsa[IEEE_8021QAZ_MAX_TCS];
	u8                         cap;

	/* Buffer configuration */
	bool                       manual_buffer;
	u32                        cable_len;
	u32                        xoff;
	u16                        port_buff_cell_sz;
पूर्ण;

#घोषणा MLX5E_MAX_DSCP (64)

काष्ठा mlx5e_dcbx_dp अणु
	u8                         dscp2prio[MLX5E_MAX_DSCP];
	u8                         trust_state;
पूर्ण;

व्योम mlx5e_dcbnl_build_netdev(काष्ठा net_device *netdev);
व्योम mlx5e_dcbnl_build_rep_netdev(काष्ठा net_device *netdev);
व्योम mlx5e_dcbnl_initialize(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_dcbnl_init_app(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_dcbnl_delete_app(काष्ठा mlx5e_priv *priv);
#अन्यथा
अटल अंतरभूत व्योम mlx5e_dcbnl_build_netdev(काष्ठा net_device *netdev) अणुपूर्ण
अटल अंतरभूत व्योम mlx5e_dcbnl_build_rep_netdev(काष्ठा net_device *netdev) अणुपूर्ण
अटल अंतरभूत व्योम mlx5e_dcbnl_initialize(काष्ठा mlx5e_priv *priv) अणुपूर्ण
अटल अंतरभूत व्योम mlx5e_dcbnl_init_app(काष्ठा mlx5e_priv *priv) अणुपूर्ण
अटल अंतरभूत व्योम mlx5e_dcbnl_delete_app(काष्ठा mlx5e_priv *priv) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MLX5E_DCBNL_H__ */
