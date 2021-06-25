<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2005-2006 Intel Corporation.  All rights reserved.
 */

#अगर_अघोषित IB_USER_MARSHALL_H
#घोषणा IB_USER_MARSHALL_H

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_sa.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_user_sa.h>

व्योम ib_copy_qp_attr_to_user(काष्ठा ib_device *device,
			     काष्ठा ib_uverbs_qp_attr *dst,
			     काष्ठा ib_qp_attr *src);

व्योम ib_copy_ah_attr_to_user(काष्ठा ib_device *device,
			     काष्ठा ib_uverbs_ah_attr *dst,
			     काष्ठा rdma_ah_attr *src);

व्योम ib_copy_path_rec_to_user(काष्ठा ib_user_path_rec *dst,
			      काष्ठा sa_path_rec *src);

व्योम ib_copy_path_rec_from_user(काष्ठा sa_path_rec *dst,
				काष्ठा ib_user_path_rec *src);

#पूर्ण_अगर /* IB_USER_MARSHALL_H */
