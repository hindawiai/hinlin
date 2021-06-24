<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * * Copyright (c) 2020, Oracle and/or its affiliates.
 */

#अगर_अघोषित RPC_RDMA_CID_H
#घोषणा RPC_RDMA_CID_H

/*
 * The rpc_rdma_cid काष्ठा records completion ID inक्रमmation. A
 * completion ID matches an incoming Send or Receive completion
 * to a Completion Queue and to a previous ib_post_*(). The ID
 * can then be displayed in an error message or recorded in a
 * trace record.
 *
 * This काष्ठा is shared between the server and client RPC/RDMA
 * transport implementations.
 */
काष्ठा rpc_rdma_cid अणु
	u32			ci_queue_id;
	पूर्णांक			ci_completion_id;
पूर्ण;

#पूर्ण_अगर	/* RPC_RDMA_CID_H */
