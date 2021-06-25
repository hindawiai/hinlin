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

#समावेश <linux/mlx5/device.h>

#समावेश "accel/ipsec.h"
#समावेश "mlx5_core.h"
#समावेश "fpga/ipsec.h"
#समावेश "accel/ipsec_offload.h"

व्योम mlx5_accel_ipsec_init(काष्ठा mlx5_core_dev *mdev)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops;
	पूर्णांक err = 0;

	ipsec_ops = (mlx5_ipsec_offload_ops(mdev)) ?
		     mlx5_ipsec_offload_ops(mdev) :
		     mlx5_fpga_ipsec_ops(mdev);

	अगर (!ipsec_ops || !ipsec_ops->init) अणु
		mlx5_core_dbg(mdev, "IPsec ops is not supported\n");
		वापस;
	पूर्ण

	err = ipsec_ops->init(mdev);
	अगर (err) अणु
		mlx5_core_warn_once(mdev, "Failed to start IPsec device, err = %d\n", err);
		वापस;
	पूर्ण

	mdev->ipsec_ops = ipsec_ops;
पूर्ण

व्योम mlx5_accel_ipsec_cleanup(काष्ठा mlx5_core_dev *mdev)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops = mdev->ipsec_ops;

	अगर (!ipsec_ops || !ipsec_ops->cleanup)
		वापस;

	ipsec_ops->cleanup(mdev);
पूर्ण

u32 mlx5_accel_ipsec_device_caps(काष्ठा mlx5_core_dev *mdev)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops = mdev->ipsec_ops;

	अगर (!ipsec_ops || !ipsec_ops->device_caps)
		वापस 0;

	वापस ipsec_ops->device_caps(mdev);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_accel_ipsec_device_caps);

अचिन्हित पूर्णांक mlx5_accel_ipsec_counters_count(काष्ठा mlx5_core_dev *mdev)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops = mdev->ipsec_ops;

	अगर (!ipsec_ops || !ipsec_ops->counters_count)
		वापस -EOPNOTSUPP;

	वापस ipsec_ops->counters_count(mdev);
पूर्ण

पूर्णांक mlx5_accel_ipsec_counters_पढ़ो(काष्ठा mlx5_core_dev *mdev, u64 *counters,
				   अचिन्हित पूर्णांक count)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops = mdev->ipsec_ops;

	अगर (!ipsec_ops || !ipsec_ops->counters_पढ़ो)
		वापस -EOPNOTSUPP;

	वापस ipsec_ops->counters_पढ़ो(mdev, counters, count);
पूर्ण

व्योम *mlx5_accel_esp_create_hw_context(काष्ठा mlx5_core_dev *mdev,
				       काष्ठा mlx5_accel_esp_xfrm *xfrm,
				       u32 *sa_handle)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops = mdev->ipsec_ops;
	__be32 saddr[4] = अणुपूर्ण, daddr[4] = अणुपूर्ण;

	अगर (!ipsec_ops || !ipsec_ops->create_hw_context)
		वापस  ERR_PTR(-EOPNOTSUPP);

	अगर (!xfrm->attrs.is_ipv6) अणु
		saddr[3] = xfrm->attrs.saddr.a4;
		daddr[3] = xfrm->attrs.daddr.a4;
	पूर्ण अन्यथा अणु
		स_नकल(saddr, xfrm->attrs.saddr.a6, माप(saddr));
		स_नकल(daddr, xfrm->attrs.daddr.a6, माप(daddr));
	पूर्ण

	वापस ipsec_ops->create_hw_context(mdev, xfrm, saddr, daddr, xfrm->attrs.spi,
					    xfrm->attrs.is_ipv6, sa_handle);
पूर्ण

व्योम mlx5_accel_esp_मुक्त_hw_context(काष्ठा mlx5_core_dev *mdev, व्योम *context)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops = mdev->ipsec_ops;

	अगर (!ipsec_ops || !ipsec_ops->मुक्त_hw_context)
		वापस;

	ipsec_ops->मुक्त_hw_context(context);
पूर्ण

काष्ठा mlx5_accel_esp_xfrm *
mlx5_accel_esp_create_xfrm(काष्ठा mlx5_core_dev *mdev,
			   स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
			   u32 flags)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops = mdev->ipsec_ops;
	काष्ठा mlx5_accel_esp_xfrm *xfrm;

	अगर (!ipsec_ops || !ipsec_ops->esp_create_xfrm)
		वापस ERR_PTR(-EOPNOTSUPP);

	xfrm = ipsec_ops->esp_create_xfrm(mdev, attrs, flags);
	अगर (IS_ERR(xfrm))
		वापस xfrm;

	xfrm->mdev = mdev;
	वापस xfrm;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_accel_esp_create_xfrm);

व्योम mlx5_accel_esp_destroy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops = xfrm->mdev->ipsec_ops;

	अगर (!ipsec_ops || !ipsec_ops->esp_destroy_xfrm)
		वापस;

	ipsec_ops->esp_destroy_xfrm(xfrm);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_accel_esp_destroy_xfrm);

पूर्णांक mlx5_accel_esp_modअगरy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm,
			       स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs)
अणु
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops = xfrm->mdev->ipsec_ops;

	अगर (!ipsec_ops || !ipsec_ops->esp_modअगरy_xfrm)
		वापस -EOPNOTSUPP;

	वापस ipsec_ops->esp_modअगरy_xfrm(xfrm, attrs);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_accel_esp_modअगरy_xfrm);
