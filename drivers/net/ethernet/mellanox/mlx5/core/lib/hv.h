<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __LIB_HV_H__
#घोषणा __LIB_HV_H__

#अगर IS_ENABLED(CONFIG_PCI_HYPERV_INTERFACE)

#समावेश <linux/hyperv.h>
#समावेश <linux/mlx5/driver.h>

पूर्णांक mlx5_hv_पढ़ो_config(काष्ठा mlx5_core_dev *dev, व्योम *buf, पूर्णांक len,
			पूर्णांक offset);
पूर्णांक mlx5_hv_ग_लिखो_config(काष्ठा mlx5_core_dev *dev, व्योम *buf, पूर्णांक len,
			 पूर्णांक offset);
पूर्णांक mlx5_hv_रेजिस्टर_invalidate(काष्ठा mlx5_core_dev *dev, व्योम *context,
				व्योम (*block_invalidate)(व्योम *context,
							 u64 block_mask));
व्योम mlx5_hv_unरेजिस्टर_invalidate(काष्ठा mlx5_core_dev *dev);
#पूर्ण_अगर

#पूर्ण_अगर /* __LIB_HV_H__ */
