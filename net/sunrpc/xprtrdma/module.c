<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2015, 2017 Oracle.  All rights reserved.
 */

/* rpcrdma.ko module initialization
 */

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश <यंत्र/swab.h>

#समावेश "xprt_rdma.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/rpcrdma.h>

MODULE_AUTHOR("Open Grid Computing and Network Appliance, Inc.");
MODULE_DESCRIPTION("RPC/RDMA Transport");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("svcrdma");
MODULE_ALIAS("xprtrdma");
MODULE_ALIAS("rpcrdma6");

अटल व्योम __निकास rpc_rdma_cleanup(व्योम)
अणु
	xprt_rdma_cleanup();
	svc_rdma_cleanup();
पूर्ण

अटल पूर्णांक __init rpc_rdma_init(व्योम)
अणु
	पूर्णांक rc;

	rc = svc_rdma_init();
	अगर (rc)
		जाओ out;

	rc = xprt_rdma_init();
	अगर (rc)
		svc_rdma_cleanup();

out:
	वापस rc;
पूर्ण

module_init(rpc_rdma_init);
module_निकास(rpc_rdma_cleanup);
