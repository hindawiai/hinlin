<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2019 Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित _RDMA_COUNTER_H_
#घोषणा _RDMA_COUNTER_H_

#समावेश <linux/mutex.h>
#समावेश <linux/pid_namespace.h>

#समावेश <rdma/restrack.h>
#समावेश <rdma/rdma_netlink.h>

काष्ठा ib_device;
काष्ठा ib_qp;

काष्ठा स्वतः_mode_param अणु
	पूर्णांक qp_type;
पूर्ण;

काष्ठा rdma_counter_mode अणु
	क्रमागत rdma_nl_counter_mode mode;
	क्रमागत rdma_nl_counter_mask mask;
	काष्ठा स्वतः_mode_param param;
पूर्ण;

काष्ठा rdma_port_counter अणु
	काष्ठा rdma_counter_mode mode;
	काष्ठा rdma_hw_stats *hstats;
	अचिन्हित पूर्णांक num_counters;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा rdma_counter अणु
	काष्ठा rdma_restrack_entry	res;
	काष्ठा ib_device		*device;
	uपूर्णांक32_t			id;
	काष्ठा kref			kref;
	काष्ठा rdma_counter_mode	mode;
	काष्ठा mutex			lock;
	काष्ठा rdma_hw_stats		*stats;
	u32				port;
पूर्ण;

व्योम rdma_counter_init(काष्ठा ib_device *dev);
व्योम rdma_counter_release(काष्ठा ib_device *dev);
पूर्णांक rdma_counter_set_स्वतः_mode(काष्ठा ib_device *dev, u32 port,
			       क्रमागत rdma_nl_counter_mask mask,
			       काष्ठा netlink_ext_ack *extack);
पूर्णांक rdma_counter_bind_qp_स्वतः(काष्ठा ib_qp *qp, u32 port);
पूर्णांक rdma_counter_unbind_qp(काष्ठा ib_qp *qp, bool क्रमce);

पूर्णांक rdma_counter_query_stats(काष्ठा rdma_counter *counter);
u64 rdma_counter_get_hwstat_value(काष्ठा ib_device *dev, u32 port, u32 index);
पूर्णांक rdma_counter_bind_qpn(काष्ठा ib_device *dev, u32 port,
			  u32 qp_num, u32 counter_id);
पूर्णांक rdma_counter_bind_qpn_alloc(काष्ठा ib_device *dev, u32 port,
				u32 qp_num, u32 *counter_id);
पूर्णांक rdma_counter_unbind_qpn(काष्ठा ib_device *dev, u32 port,
			    u32 qp_num, u32 counter_id);
पूर्णांक rdma_counter_get_mode(काष्ठा ib_device *dev, u32 port,
			  क्रमागत rdma_nl_counter_mode *mode,
			  क्रमागत rdma_nl_counter_mask *mask);

#पूर्ण_अगर /* _RDMA_COUNTER_H_ */
