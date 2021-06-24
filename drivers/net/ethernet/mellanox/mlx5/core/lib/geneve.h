<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_GENEVE_H__
#घोषणा __MLX5_GENEVE_H__

#समावेश <net/geneve.h>
#समावेश <linux/mlx5/driver.h>

काष्ठा mlx5_geneve;

#अगर_घोषित CONFIG_MLX5_ESWITCH

काष्ठा mlx5_geneve *mlx5_geneve_create(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5_geneve_destroy(काष्ठा mlx5_geneve *geneve);

पूर्णांक mlx5_geneve_tlv_option_add(काष्ठा mlx5_geneve *geneve, काष्ठा geneve_opt *opt);
व्योम mlx5_geneve_tlv_option_del(काष्ठा mlx5_geneve *geneve);

#अन्यथा /* CONFIG_MLX5_ESWITCH */

अटल अंतरभूत काष्ठा mlx5_geneve
*mlx5_geneve_create(काष्ठा mlx5_core_dev *mdev) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम
mlx5_geneve_destroy(काष्ठा mlx5_geneve *geneve) अणुपूर्ण
अटल अंतरभूत पूर्णांक
mlx5_geneve_tlv_option_add(काष्ठा mlx5_geneve *geneve, काष्ठा geneve_opt *opt) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम
mlx5_geneve_tlv_option_del(काष्ठा mlx5_geneve *geneve) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_ESWITCH */

#पूर्ण_अगर /* __MLX5_GENEVE_H__ */
