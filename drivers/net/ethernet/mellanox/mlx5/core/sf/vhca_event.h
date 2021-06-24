<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#अगर_अघोषित __MLX5_VHCA_EVENT_H__
#घोषणा __MLX5_VHCA_EVENT_H__

#अगर_घोषित CONFIG_MLX5_SF

काष्ठा mlx5_vhca_state_event अणु
	u16 function_id;
	u16 sw_function_id;
	u8 new_vhca_state;
पूर्ण;

अटल अंतरभूत bool mlx5_vhca_event_supported(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस MLX5_CAP_GEN_MAX(dev, vhca_state);
पूर्ण

व्योम mlx5_vhca_state_cap_handle(काष्ठा mlx5_core_dev *dev, व्योम *set_hca_cap);
पूर्णांक mlx5_vhca_event_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_vhca_event_cleanup(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_vhca_event_start(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_vhca_event_stop(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_vhca_event_notअगरier_रेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb);
व्योम mlx5_vhca_event_notअगरier_unरेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb);
पूर्णांक mlx5_modअगरy_vhca_sw_id(काष्ठा mlx5_core_dev *dev, u16 function_id, u32 sw_fn_id);
पूर्णांक mlx5_vhca_event_arm(काष्ठा mlx5_core_dev *dev, u16 function_id);
पूर्णांक mlx5_cmd_query_vhca_state(काष्ठा mlx5_core_dev *dev, u16 function_id,
			      u32 *out, u32 outlen);
#अन्यथा

अटल अंतरभूत व्योम mlx5_vhca_state_cap_handle(काष्ठा mlx5_core_dev *dev, व्योम *set_hca_cap)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_vhca_event_init(काष्ठा mlx5_core_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5_vhca_event_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम mlx5_vhca_event_start(काष्ठा mlx5_core_dev *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम mlx5_vhca_event_stop(काष्ठा mlx5_core_dev *dev)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
