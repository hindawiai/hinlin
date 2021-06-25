<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#अगर_अघोषित __MLX5_SF_H__
#घोषणा __MLX5_SF_H__

#समावेश <linux/mlx5/driver.h>

अटल अंतरभूत u16 mlx5_sf_start_function_id(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस MLX5_CAP_GEN(dev, sf_base_id);
पूर्ण

#अगर_घोषित CONFIG_MLX5_SF

अटल अंतरभूत bool mlx5_sf_supported(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस MLX5_CAP_GEN(dev, sf);
पूर्ण

अटल अंतरभूत u16 mlx5_sf_max_functions(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!mlx5_sf_supported(dev))
		वापस 0;
	अगर (MLX5_CAP_GEN(dev, max_num_sf))
		वापस MLX5_CAP_GEN(dev, max_num_sf);
	अन्यथा
		वापस 1 << MLX5_CAP_GEN(dev, log_max_sf);
पूर्ण

#अन्यथा

अटल अंतरभूत bool mlx5_sf_supported(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u16 mlx5_sf_max_functions(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_MLX5_SF_MANAGER

पूर्णांक mlx5_sf_hw_table_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_sf_hw_table_cleanup(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_sf_hw_table_create(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_sf_hw_table_destroy(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_sf_table_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_sf_table_cleanup(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_devlink_sf_port_new(काष्ठा devlink *devlink,
			     स्थिर काष्ठा devlink_port_new_attrs *add_attr,
			     काष्ठा netlink_ext_ack *extack,
			     अचिन्हित पूर्णांक *new_port_index);
पूर्णांक mlx5_devlink_sf_port_del(काष्ठा devlink *devlink, अचिन्हित पूर्णांक port_index,
			     काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5_devlink_sf_port_fn_state_get(काष्ठा devlink *devlink, काष्ठा devlink_port *dl_port,
				      क्रमागत devlink_port_fn_state *state,
				      क्रमागत devlink_port_fn_opstate *opstate,
				      काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5_devlink_sf_port_fn_state_set(काष्ठा devlink *devlink, काष्ठा devlink_port *dl_port,
				      क्रमागत devlink_port_fn_state state,
				      काष्ठा netlink_ext_ack *extack);
#अन्यथा

अटल अंतरभूत पूर्णांक mlx5_sf_hw_table_init(काष्ठा mlx5_core_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5_sf_hw_table_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_sf_hw_table_create(काष्ठा mlx5_core_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5_sf_hw_table_destroy(काष्ठा mlx5_core_dev *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_sf_table_init(काष्ठा mlx5_core_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5_sf_table_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
