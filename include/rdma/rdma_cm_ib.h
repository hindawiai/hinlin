<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2006 Intel Corporation.  All rights reserved.
 */

#अगर_अघोषित RDMA_CM_IB_H
#घोषणा RDMA_CM_IB_H

#समावेश <rdma/rdma_cm.h>

/**
 * rdma_set_ib_path - Manually sets the path record used to establish a
 *   connection.
 * @id: Connection identअगरier associated with the request.
 * @path_rec: Reference to the path record
 *
 * This call permits a user to specअगरy routing inक्रमmation क्रम rdma_cm_id's
 * bound to InfiniBand devices. It is called on the client side of a
 * connection and replaces the call to rdma_resolve_route.
 */
पूर्णांक rdma_set_ib_path(काष्ठा rdma_cm_id *id,
		     काष्ठा sa_path_rec *path_rec);

/* Global qkey क्रम UDP QPs and multicast groups. */
#घोषणा RDMA_UDP_QKEY 0x01234567

#पूर्ण_अगर /* RDMA_CM_IB_H */
