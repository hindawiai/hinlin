<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2020 Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित _RDMA_LAG_H_
#घोषणा _RDMA_LAG_H_

#समावेश <net/lag.h>

काष्ठा ib_device;
काष्ठा rdma_ah_attr;

क्रमागत rdma_lag_flags अणु
	RDMA_LAG_FLAGS_HASH_ALL_SLAVES = 1 << 0
पूर्ण;

व्योम rdma_lag_put_ah_roce_slave(काष्ठा net_device *xmit_slave);
काष्ठा net_device *rdma_lag_get_ah_roce_slave(काष्ठा ib_device *device,
					      काष्ठा rdma_ah_attr *ah_attr,
					      gfp_t flags);

#पूर्ण_अगर /* _RDMA_LAG_H_ */
