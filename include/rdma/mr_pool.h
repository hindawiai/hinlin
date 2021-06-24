<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 HGST, a Western Digital Company.
 */
#अगर_अघोषित _RDMA_MR_POOL_H
#घोषणा _RDMA_MR_POOL_H 1

#समावेश <rdma/ib_verbs.h>

काष्ठा ib_mr *ib_mr_pool_get(काष्ठा ib_qp *qp, काष्ठा list_head *list);
व्योम ib_mr_pool_put(काष्ठा ib_qp *qp, काष्ठा list_head *list, काष्ठा ib_mr *mr);

पूर्णांक ib_mr_pool_init(काष्ठा ib_qp *qp, काष्ठा list_head *list, पूर्णांक nr,
		क्रमागत ib_mr_type type, u32 max_num_sg, u32 max_num_meta_sg);
व्योम ib_mr_pool_destroy(काष्ठा ib_qp *qp, काष्ठा list_head *list);

#पूर्ण_अगर /* _RDMA_MR_POOL_H */
