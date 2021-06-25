<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित __MLX5_IB_REP_H__
#घोषणा __MLX5_IB_REP_H__

#समावेश <linux/mlx5/eचयन.h>
#समावेश "mlx5_ib.h"

बाह्य स्थिर काष्ठा mlx5_ib_profile raw_eth_profile;

#अगर_घोषित CONFIG_MLX5_ESWITCH
पूर्णांक mlx5r_rep_init(व्योम);
व्योम mlx5r_rep_cleanup(व्योम);
काष्ठा mlx5_flow_handle *create_flow_rule_vport_sq(काष्ठा mlx5_ib_dev *dev,
						   काष्ठा mlx5_ib_sq *sq,
						   u32 port);
काष्ठा net_device *mlx5_ib_get_rep_netdev(काष्ठा mlx5_eचयन *esw,
					  u16 vport_num);
#अन्यथा /* CONFIG_MLX5_ESWITCH */
अटल अंतरभूत पूर्णांक mlx5r_rep_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5r_rep_cleanup(व्योम) अणुपूर्ण
अटल अंतरभूत
काष्ठा mlx5_flow_handle *create_flow_rule_vport_sq(काष्ठा mlx5_ib_dev *dev,
						   काष्ठा mlx5_ib_sq *sq,
						   u32 port)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा net_device *mlx5_ib_get_rep_netdev(काष्ठा mlx5_eचयन *esw,
					  u16 vport_num)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __MLX5_IB_REP_H__ */
