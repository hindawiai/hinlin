<शैली गुरु>
/*
 * Copyright (c) 2005 Voltaire Inc.  All rights reserved.
 * Copyright (c) 2002-2005, Network Appliance, Inc. All rights reserved.
 * Copyright (c) 1999-2005, Mellanox Technologies, Inc. All rights reserved.
 * Copyright (c) 2005-2006 Intel Corporation.  All rights reserved.
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
 */

#अगर_अघोषित _CMA_PRIV_H
#घोषणा _CMA_PRIV_H

क्रमागत rdma_cm_state अणु
	RDMA_CM_IDLE,
	RDMA_CM_ADDR_QUERY,
	RDMA_CM_ADDR_RESOLVED,
	RDMA_CM_ROUTE_QUERY,
	RDMA_CM_ROUTE_RESOLVED,
	RDMA_CM_CONNECT,
	RDMA_CM_DISCONNECT,
	RDMA_CM_ADDR_BOUND,
	RDMA_CM_LISTEN,
	RDMA_CM_DEVICE_REMOVAL,
	RDMA_CM_DESTROYING
पूर्ण;

काष्ठा rdma_id_निजी अणु
	काष्ठा rdma_cm_id	id;

	काष्ठा rdma_bind_list	*bind_list;
	काष्ठा hlist_node	node;
	काष्ठा list_head	list; /* listen_any_list or cma_device.list */
	काष्ठा list_head	listen_list; /* per device listens */
	काष्ठा cma_device	*cma_dev;
	काष्ठा list_head	mc_list;

	पूर्णांक			पूर्णांकernal_id;
	क्रमागत rdma_cm_state	state;
	spinlock_t		lock;
	काष्ठा mutex		qp_mutex;

	काष्ठा completion	comp;
	refcount_t refcount;
	काष्ठा mutex		handler_mutex;

	पूर्णांक			backlog;
	पूर्णांक			समयout_ms;
	काष्ठा ib_sa_query	*query;
	पूर्णांक			query_id;
	जोड़ अणु
		काष्ठा ib_cm_id	*ib;
		काष्ठा iw_cm_id	*iw;
	पूर्ण cm_id;

	u32			seq_num;
	u32			qkey;
	u32			qp_num;
	u32			options;
	u8			srq;
	u8			tos;
	u8			tos_set:1;
	u8                      समयout_set:1;
	u8			min_rnr_समयr_set:1;
	u8			reuseaddr;
	u8			afonly;
	u8			समयout;
	u8			min_rnr_समयr;
	क्रमागत ib_gid_type	gid_type;

	/*
	 * Internal to RDMA/core, करोn't use in the drivers
	 */
	काष्ठा rdma_restrack_entry     res;
	काष्ठा rdma_ucm_ece ece;
पूर्ण;

#अगर IS_ENABLED(CONFIG_INFINIBAND_ADDR_TRANS_CONFIGFS)
पूर्णांक cma_configfs_init(व्योम);
व्योम cma_configfs_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक cma_configfs_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cma_configfs_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

व्योम cma_dev_get(काष्ठा cma_device *dev);
व्योम cma_dev_put(काष्ठा cma_device *dev);
प्रकार bool (*cma_device_filter)(काष्ठा ib_device *, व्योम *);
काष्ठा cma_device *cma_क्रमागत_devices_by_ibdev(cma_device_filter filter,
					     व्योम *cookie);
पूर्णांक cma_get_शेष_gid_type(काष्ठा cma_device *dev, u32 port);
पूर्णांक cma_set_शेष_gid_type(काष्ठा cma_device *dev, u32 port,
			     क्रमागत ib_gid_type शेष_gid_type);
पूर्णांक cma_get_शेष_roce_tos(काष्ठा cma_device *dev, u32 port);
पूर्णांक cma_set_शेष_roce_tos(काष्ठा cma_device *dev, u32 port,
			     u8 शेष_roce_tos);
काष्ठा ib_device *cma_get_ib_dev(काष्ठा cma_device *dev);

#पूर्ण_अगर /* _CMA_PRIV_H */
