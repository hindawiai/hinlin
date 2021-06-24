<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित _RDMA_CORE_RESTRACK_H_
#घोषणा _RDMA_CORE_RESTRACK_H_

#समावेश <linux/mutex.h>

/**
 * काष्ठा rdma_restrack_root - मुख्य resource tracking management
 * entity, per-device
 */
काष्ठा rdma_restrack_root अणु
	/**
	 * @xa: Array of XArray काष्ठाure to hold restrack entries.
	 */
	काष्ठा xarray xa;
	/**
	 * @next_id: Next ID to support cyclic allocation
	 */
	u32 next_id;
पूर्ण;

पूर्णांक rdma_restrack_init(काष्ठा ib_device *dev);
व्योम rdma_restrack_clean(काष्ठा ib_device *dev);
व्योम rdma_restrack_add(काष्ठा rdma_restrack_entry *res);
व्योम rdma_restrack_del(काष्ठा rdma_restrack_entry *res);
व्योम rdma_restrack_new(काष्ठा rdma_restrack_entry *res,
		       क्रमागत rdma_restrack_type type);
व्योम rdma_restrack_set_name(काष्ठा rdma_restrack_entry *res,
			    स्थिर अक्षर *caller);
व्योम rdma_restrack_parent_name(काष्ठा rdma_restrack_entry *dst,
			       स्थिर काष्ठा rdma_restrack_entry *parent);
#पूर्ण_अगर /* _RDMA_CORE_RESTRACK_H_ */
