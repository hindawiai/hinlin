<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित __MLX5_ACCEL_IPSEC_H__
#घोषणा __MLX5_ACCEL_IPSEC_H__

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/accel.h>

#अगर_घोषित CONFIG_MLX5_ACCEL

#घोषणा MLX5_IPSEC_DEV(mdev) (mlx5_accel_ipsec_device_caps(mdev) & \
			      MLX5_ACCEL_IPSEC_CAP_DEVICE)

अचिन्हित पूर्णांक mlx5_accel_ipsec_counters_count(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5_accel_ipsec_counters_पढ़ो(काष्ठा mlx5_core_dev *mdev, u64 *counters,
				   अचिन्हित पूर्णांक count);

व्योम *mlx5_accel_esp_create_hw_context(काष्ठा mlx5_core_dev *mdev,
				       काष्ठा mlx5_accel_esp_xfrm *xfrm,
				       u32 *sa_handle);
व्योम mlx5_accel_esp_मुक्त_hw_context(काष्ठा mlx5_core_dev *mdev, व्योम *context);

व्योम mlx5_accel_ipsec_init(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5_accel_ipsec_cleanup(काष्ठा mlx5_core_dev *mdev);

काष्ठा mlx5_accel_ipsec_ops अणु
	u32 (*device_caps)(काष्ठा mlx5_core_dev *mdev);
	अचिन्हित पूर्णांक (*counters_count)(काष्ठा mlx5_core_dev *mdev);
	पूर्णांक (*counters_पढ़ो)(काष्ठा mlx5_core_dev *mdev, u64 *counters, अचिन्हित पूर्णांक count);
	व्योम* (*create_hw_context)(काष्ठा mlx5_core_dev *mdev,
				   काष्ठा mlx5_accel_esp_xfrm *xfrm,
				   स्थिर __be32 saddr[4], स्थिर __be32 daddr[4],
				   स्थिर __be32 spi, bool is_ipv6, u32 *sa_handle);
	व्योम (*मुक्त_hw_context)(व्योम *context);
	पूर्णांक (*init)(काष्ठा mlx5_core_dev *mdev);
	व्योम (*cleanup)(काष्ठा mlx5_core_dev *mdev);
	काष्ठा mlx5_accel_esp_xfrm* (*esp_create_xfrm)(काष्ठा mlx5_core_dev *mdev,
						       स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
						       u32 flags);
	पूर्णांक (*esp_modअगरy_xfrm)(काष्ठा mlx5_accel_esp_xfrm *xfrm,
			       स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs);
	व्योम (*esp_destroy_xfrm)(काष्ठा mlx5_accel_esp_xfrm *xfrm);
पूर्ण;

#अन्यथा

#घोषणा MLX5_IPSEC_DEV(mdev) false

अटल अंतरभूत व्योम *
mlx5_accel_esp_create_hw_context(काष्ठा mlx5_core_dev *mdev,
				 काष्ठा mlx5_accel_esp_xfrm *xfrm,
				 u32 *sa_handle)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mlx5_accel_esp_मुक्त_hw_context(काष्ठा mlx5_core_dev *mdev, व्योम *context) अणुपूर्ण

अटल अंतरभूत व्योम mlx5_accel_ipsec_init(काष्ठा mlx5_core_dev *mdev) अणुपूर्ण

अटल अंतरभूत व्योम mlx5_accel_ipsec_cleanup(काष्ठा mlx5_core_dev *mdev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_ACCEL */

#पूर्ण_अगर	/* __MLX5_ACCEL_IPSEC_H__ */
