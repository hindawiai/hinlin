<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2018 Mellanox Technologies */

#अगर_अघोषित __LIB_MLX5_DEVCOM_H__
#घोषणा __LIB_MLX5_DEVCOM_H__

#समावेश <linux/mlx5/driver.h>

क्रमागत mlx5_devcom_components अणु
	MLX5_DEVCOM_ESW_OFFLOADS,

	MLX5_DEVCOM_NUM_COMPONENTS,
पूर्ण;

प्रकार पूर्णांक (*mlx5_devcom_event_handler_t)(पूर्णांक event,
					   व्योम *my_data,
					   व्योम *event_data);

काष्ठा mlx5_devcom *mlx5_devcom_रेजिस्टर_device(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_devcom_unरेजिस्टर_device(काष्ठा mlx5_devcom *devcom);

व्योम mlx5_devcom_रेजिस्टर_component(काष्ठा mlx5_devcom *devcom,
				    क्रमागत mlx5_devcom_components id,
				    mlx5_devcom_event_handler_t handler,
				    व्योम *data);
व्योम mlx5_devcom_unरेजिस्टर_component(काष्ठा mlx5_devcom *devcom,
				      क्रमागत mlx5_devcom_components id);

पूर्णांक mlx5_devcom_send_event(काष्ठा mlx5_devcom *devcom,
			   क्रमागत mlx5_devcom_components id,
			   पूर्णांक event,
			   व्योम *event_data);

व्योम mlx5_devcom_set_paired(काष्ठा mlx5_devcom *devcom,
			    क्रमागत mlx5_devcom_components id,
			    bool paired);
bool mlx5_devcom_is_paired(काष्ठा mlx5_devcom *devcom,
			   क्रमागत mlx5_devcom_components id);

व्योम *mlx5_devcom_get_peer_data(काष्ठा mlx5_devcom *devcom,
				क्रमागत mlx5_devcom_components id);
व्योम mlx5_devcom_release_peer_data(काष्ठा mlx5_devcom *devcom,
				   क्रमागत mlx5_devcom_components id);

#पूर्ण_अगर

