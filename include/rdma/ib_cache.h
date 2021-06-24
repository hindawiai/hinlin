<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Intel Corporation. All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 */

#अगर_अघोषित _IB_CACHE_H
#घोषणा _IB_CACHE_H

#समावेश <rdma/ib_verbs.h>

पूर्णांक rdma_query_gid(काष्ठा ib_device *device, u32 port_num, पूर्णांक index,
		   जोड़ ib_gid *gid);
व्योम *rdma_पढ़ो_gid_hw_context(स्थिर काष्ठा ib_gid_attr *attr);
स्थिर काष्ठा ib_gid_attr *rdma_find_gid(काष्ठा ib_device *device,
					स्थिर जोड़ ib_gid *gid,
					क्रमागत ib_gid_type gid_type,
					काष्ठा net_device *ndev);
स्थिर काष्ठा ib_gid_attr *rdma_find_gid_by_port(काष्ठा ib_device *ib_dev,
						स्थिर जोड़ ib_gid *gid,
						क्रमागत ib_gid_type gid_type,
						u32 port,
						काष्ठा net_device *ndev);
स्थिर काष्ठा ib_gid_attr *rdma_find_gid_by_filter(
	काष्ठा ib_device *device, स्थिर जोड़ ib_gid *gid, u32 port_num,
	bool (*filter)(स्थिर जोड़ ib_gid *gid, स्थिर काष्ठा ib_gid_attr *,
		       व्योम *),
	व्योम *context);

पूर्णांक rdma_पढ़ो_gid_l2_fields(स्थिर काष्ठा ib_gid_attr *attr,
			    u16 *vlan_id, u8 *smac);
काष्ठा net_device *rdma_पढ़ो_gid_attr_ndev_rcu(स्थिर काष्ठा ib_gid_attr *attr);

/**
 * ib_get_cached_pkey - Returns a cached PKey table entry
 * @device: The device to query.
 * @port_num: The port number of the device to query.
 * @index: The index पूर्णांकo the cached PKey table to query.
 * @pkey: The PKey value found at the specअगरied index.
 *
 * ib_get_cached_pkey() fetches the specअगरied PKey table entry stored in
 * the local software cache.
 */
पूर्णांक ib_get_cached_pkey(काष्ठा ib_device    *device_handle,
		       u32                  port_num,
		       पूर्णांक                  index,
		       u16                 *pkey);

/**
 * ib_find_cached_pkey - Returns the PKey table index where a specअगरied
 *   PKey value occurs.
 * @device: The device to query.
 * @port_num: The port number of the device to search क्रम the PKey.
 * @pkey: The PKey value to search क्रम.
 * @index: The index पूर्णांकo the cached PKey table where the PKey was found.
 *
 * ib_find_cached_pkey() searches the specअगरied PKey table in
 * the local software cache.
 */
पूर्णांक ib_find_cached_pkey(काष्ठा ib_device    *device,
			u32                  port_num,
			u16                  pkey,
			u16                 *index);

/**
 * ib_find_exact_cached_pkey - Returns the PKey table index where a specअगरied
 *   PKey value occurs. Comparison uses the FULL 16 bits (incl membership bit)
 * @device: The device to query.
 * @port_num: The port number of the device to search क्रम the PKey.
 * @pkey: The PKey value to search क्रम.
 * @index: The index पूर्णांकo the cached PKey table where the PKey was found.
 *
 * ib_find_exact_cached_pkey() searches the specअगरied PKey table in
 * the local software cache.
 */
पूर्णांक ib_find_exact_cached_pkey(काष्ठा ib_device    *device,
			      u32                  port_num,
			      u16                  pkey,
			      u16                 *index);

/**
 * ib_get_cached_lmc - Returns a cached lmc table entry
 * @device: The device to query.
 * @port_num: The port number of the device to query.
 * @lmc: The lmc value क्रम the specअगरied port क्रम that device.
 *
 * ib_get_cached_lmc() fetches the specअगरied lmc table entry stored in
 * the local software cache.
 */
पूर्णांक ib_get_cached_lmc(काष्ठा ib_device *device,
		      u32               port_num,
		      u8                *lmc);

/**
 * ib_get_cached_port_state - Returns a cached port state table entry
 * @device: The device to query.
 * @port_num: The port number of the device to query.
 * @port_state: port_state क्रम the specअगरied port क्रम that device.
 *
 * ib_get_cached_port_state() fetches the specअगरied port_state table entry stored in
 * the local software cache.
 */
पूर्णांक ib_get_cached_port_state(काष्ठा ib_device *device,
			     u32               port_num,
			      क्रमागत ib_port_state *port_active);

bool rdma_is_zero_gid(स्थिर जोड़ ib_gid *gid);
स्थिर काष्ठा ib_gid_attr *rdma_get_gid_attr(काष्ठा ib_device *device,
					    u32 port_num, पूर्णांक index);
व्योम rdma_put_gid_attr(स्थिर काष्ठा ib_gid_attr *attr);
व्योम rdma_hold_gid_attr(स्थिर काष्ठा ib_gid_attr *attr);
sमाप_प्रकार rdma_query_gid_table(काष्ठा ib_device *device,
			     काष्ठा ib_uverbs_gid_entry *entries,
			     माप_प्रकार max_entries);

#पूर्ण_अगर /* _IB_CACHE_H */
