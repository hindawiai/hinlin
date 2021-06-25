<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2014-2017 Oracle.  All rights reserved.
 * Copyright (c) 2003-2007 Network Appliance, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the BSD-type
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *      Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *      Redistributions in binary क्रमm must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the करोcumentation and/or other materials provided
 *      with the distribution.
 *
 *      Neither the name of the Network Appliance, Inc. nor the names of
 *      its contributors may be used to enकरोrse or promote products
 *      derived from this software without specअगरic prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * transport.c
 *
 * This file contains the top-level implementation of an RPC RDMA
 * transport.
 *
 * Naming convention: functions beginning with xprt_ are part of the
 * transport चयन. All others are RPC RDMA पूर्णांकernal.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/smp.h>

#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_TRANS
#पूर्ण_अगर

/*
 * tunables
 */

अटल अचिन्हित पूर्णांक xprt_rdma_slot_table_entries = RPCRDMA_DEF_SLOT_TABLE;
अचिन्हित पूर्णांक xprt_rdma_max_अंतरभूत_पढ़ो = RPCRDMA_DEF_INLINE;
अचिन्हित पूर्णांक xprt_rdma_max_अंतरभूत_ग_लिखो = RPCRDMA_DEF_INLINE;
अचिन्हित पूर्णांक xprt_rdma_memreg_strategy		= RPCRDMA_FRWR;
पूर्णांक xprt_rdma_pad_optimize;

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)

अटल अचिन्हित पूर्णांक min_slot_table_size = RPCRDMA_MIN_SLOT_TABLE;
अटल अचिन्हित पूर्णांक max_slot_table_size = RPCRDMA_MAX_SLOT_TABLE;
अटल अचिन्हित पूर्णांक min_अंतरभूत_size = RPCRDMA_MIN_INLINE;
अटल अचिन्हित पूर्णांक max_अंतरभूत_size = RPCRDMA_MAX_INLINE;
अटल अचिन्हित पूर्णांक max_padding = PAGE_SIZE;
अटल अचिन्हित पूर्णांक min_memreg = RPCRDMA_BOUNCEBUFFERS;
अटल अचिन्हित पूर्णांक max_memreg = RPCRDMA_LAST - 1;
अटल अचिन्हित पूर्णांक dummy;

अटल काष्ठा ctl_table_header *sunrpc_table_header;

अटल काष्ठा ctl_table xr_tunables_table[] = अणु
	अणु
		.procname	= "rdma_slot_table_entries",
		.data		= &xprt_rdma_slot_table_entries,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_slot_table_size,
		.extra2		= &max_slot_table_size
	पूर्ण,
	अणु
		.procname	= "rdma_max_inline_read",
		.data		= &xprt_rdma_max_अंतरभूत_पढ़ो,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_अंतरभूत_size,
		.extra2		= &max_अंतरभूत_size,
	पूर्ण,
	अणु
		.procname	= "rdma_max_inline_write",
		.data		= &xprt_rdma_max_अंतरभूत_ग_लिखो,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_अंतरभूत_size,
		.extra2		= &max_अंतरभूत_size,
	पूर्ण,
	अणु
		.procname	= "rdma_inline_write_padding",
		.data		= &dummy,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &max_padding,
	पूर्ण,
	अणु
		.procname	= "rdma_memreg_strategy",
		.data		= &xprt_rdma_memreg_strategy,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_memreg,
		.extra2		= &max_memreg,
	पूर्ण,
	अणु
		.procname	= "rdma_pad_optimize",
		.data		= &xprt_rdma_pad_optimize,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table sunrpc_table[] = अणु
	अणु
		.procname	= "sunrpc",
		.mode		= 0555,
		.child		= xr_tunables_table
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

#पूर्ण_अगर

अटल स्थिर काष्ठा rpc_xprt_ops xprt_rdma_procs;

अटल व्योम
xprt_rdma_क्रमmat_addresses4(काष्ठा rpc_xprt *xprt, काष्ठा sockaddr *sap)
अणु
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)sap;
	अक्षर buf[20];

	snम_लिखो(buf, माप(buf), "%08x", ntohl(sin->sin_addr.s_addr));
	xprt->address_strings[RPC_DISPLAY_HEX_ADDR] = kstrdup(buf, GFP_KERNEL);

	xprt->address_strings[RPC_DISPLAY_NETID] = RPCBIND_NETID_RDMA;
पूर्ण

अटल व्योम
xprt_rdma_क्रमmat_addresses6(काष्ठा rpc_xprt *xprt, काष्ठा sockaddr *sap)
अणु
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sap;
	अक्षर buf[40];

	snम_लिखो(buf, माप(buf), "%pi6", &sin6->sin6_addr);
	xprt->address_strings[RPC_DISPLAY_HEX_ADDR] = kstrdup(buf, GFP_KERNEL);

	xprt->address_strings[RPC_DISPLAY_NETID] = RPCBIND_NETID_RDMA6;
पूर्ण

व्योम
xprt_rdma_क्रमmat_addresses(काष्ठा rpc_xprt *xprt, काष्ठा sockaddr *sap)
अणु
	अक्षर buf[128];

	चयन (sap->sa_family) अणु
	हाल AF_INET:
		xprt_rdma_क्रमmat_addresses4(xprt, sap);
		अवरोध;
	हाल AF_INET6:
		xprt_rdma_क्रमmat_addresses6(xprt, sap);
		अवरोध;
	शेष:
		pr_err("rpcrdma: Unrecognized address family\n");
		वापस;
	पूर्ण

	(व्योम)rpc_ntop(sap, buf, माप(buf));
	xprt->address_strings[RPC_DISPLAY_ADDR] = kstrdup(buf, GFP_KERNEL);

	snम_लिखो(buf, माप(buf), "%u", rpc_get_port(sap));
	xprt->address_strings[RPC_DISPLAY_PORT] = kstrdup(buf, GFP_KERNEL);

	snम_लिखो(buf, माप(buf), "%4hx", rpc_get_port(sap));
	xprt->address_strings[RPC_DISPLAY_HEX_PORT] = kstrdup(buf, GFP_KERNEL);

	xprt->address_strings[RPC_DISPLAY_PROTO] = "rdma";
पूर्ण

व्योम
xprt_rdma_मुक्त_addresses(काष्ठा rpc_xprt *xprt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < RPC_DISPLAY_MAX; i++)
		चयन (i) अणु
		हाल RPC_DISPLAY_PROTO:
		हाल RPC_DISPLAY_NETID:
			जारी;
		शेष:
			kमुक्त(xprt->address_strings[i]);
		पूर्ण
पूर्ण

/**
 * xprt_rdma_connect_worker - establish connection in the background
 * @work: worker thपढ़ो context
 *
 * Requester holds the xprt's send lock to prevent activity on this
 * transport जबतक a fresh connection is being established. RPC tasks
 * sleep on the xprt's pending queue रुकोing क्रम connect to complete.
 */
अटल व्योम
xprt_rdma_connect_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = container_of(work, काष्ठा rpcrdma_xprt,
						   rx_connect_worker.work);
	काष्ठा rpc_xprt *xprt = &r_xprt->rx_xprt;
	पूर्णांक rc;

	rc = rpcrdma_xprt_connect(r_xprt);
	xprt_clear_connecting(xprt);
	अगर (!rc) अणु
		xprt->connect_cookie++;
		xprt->stat.connect_count++;
		xprt->stat.connect_समय += (दीर्घ)jअगरfies -
					   xprt->stat.connect_start;
		xprt_set_connected(xprt);
		rc = -EAGAIN;
	पूर्ण अन्यथा अणु
		/* Force a call to xprt_rdma_बंद to clean up */
		spin_lock(&xprt->transport_lock);
		set_bit(XPRT_CLOSE_WAIT, &xprt->state);
		spin_unlock(&xprt->transport_lock);
	पूर्ण
	xprt_wake_pending_tasks(xprt, rc);
पूर्ण

/**
 * xprt_rdma_inject_disconnect - inject a connection fault
 * @xprt: transport context
 *
 * If @xprt is connected, disconnect it to simulate spurious
 * connection loss. Caller must hold @xprt's send lock to
 * ensure that data काष्ठाures and hardware resources are
 * stable during the rdma_disconnect() call.
 */
अटल व्योम
xprt_rdma_inject_disconnect(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);

	trace_xprtrdma_op_inject_dsc(r_xprt);
	rdma_disconnect(r_xprt->rx_ep->re_id);
पूर्ण

/**
 * xprt_rdma_destroy - Full tear करोwn of transport
 * @xprt: करोomed transport context
 *
 * Caller guarantees there will be no more calls to us with
 * this @xprt.
 */
अटल व्योम
xprt_rdma_destroy(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);

	cancel_delayed_work_sync(&r_xprt->rx_connect_worker);

	rpcrdma_xprt_disconnect(r_xprt);
	rpcrdma_buffer_destroy(&r_xprt->rx_buf);

	xprt_rdma_मुक्त_addresses(xprt);
	xprt_मुक्त(xprt);

	module_put(THIS_MODULE);
पूर्ण

/* 60 second समयout, no retries */
अटल स्थिर काष्ठा rpc_समयout xprt_rdma_शेष_समयout = अणु
	.to_initval = 60 * HZ,
	.to_maxval = 60 * HZ,
पूर्ण;

/**
 * xprt_setup_rdma - Set up transport to use RDMA
 *
 * @args: rpc transport arguments
 */
अटल काष्ठा rpc_xprt *
xprt_setup_rdma(काष्ठा xprt_create *args)
अणु
	काष्ठा rpc_xprt *xprt;
	काष्ठा rpcrdma_xprt *new_xprt;
	काष्ठा sockaddr *sap;
	पूर्णांक rc;

	अगर (args->addrlen > माप(xprt->addr))
		वापस ERR_PTR(-EBADF);

	अगर (!try_module_get(THIS_MODULE))
		वापस ERR_PTR(-EIO);

	xprt = xprt_alloc(args->net, माप(काष्ठा rpcrdma_xprt), 0,
			  xprt_rdma_slot_table_entries);
	अगर (!xprt) अणु
		module_put(THIS_MODULE);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	xprt->समयout = &xprt_rdma_शेष_समयout;
	xprt->connect_समयout = xprt->समयout->to_initval;
	xprt->max_reconnect_समयout = xprt->समयout->to_maxval;
	xprt->bind_समयout = RPCRDMA_BIND_TO;
	xprt->reestablish_समयout = RPCRDMA_INIT_REEST_TO;
	xprt->idle_समयout = RPCRDMA_IDLE_DISC_TO;

	xprt->resvport = 0;		/* privileged port not needed */
	xprt->ops = &xprt_rdma_procs;

	/*
	 * Set up RDMA-specअगरic connect data.
	 */
	sap = args->dstaddr;

	/* Ensure xprt->addr holds valid server TCP (not RDMA)
	 * address, क्रम any side protocols which peek at it */
	xprt->prot = IPPROTO_TCP;
	xprt->addrlen = args->addrlen;
	स_नकल(&xprt->addr, sap, xprt->addrlen);

	अगर (rpc_get_port(sap))
		xprt_set_bound(xprt);
	xprt_rdma_क्रमmat_addresses(xprt, sap);

	new_xprt = rpcx_to_rdmax(xprt);
	rc = rpcrdma_buffer_create(new_xprt);
	अगर (rc) अणु
		xprt_rdma_मुक्त_addresses(xprt);
		xprt_मुक्त(xprt);
		module_put(THIS_MODULE);
		वापस ERR_PTR(rc);
	पूर्ण

	INIT_DELAYED_WORK(&new_xprt->rx_connect_worker,
			  xprt_rdma_connect_worker);

	xprt->max_payload = RPCRDMA_MAX_DATA_SEGS << PAGE_SHIFT;

	वापस xprt;
पूर्ण

/**
 * xprt_rdma_बंद - बंद a transport connection
 * @xprt: transport context
 *
 * Called during स्वतःबंद or device removal.
 *
 * Caller holds @xprt's send lock to prevent activity on this
 * transport जबतक the connection is torn करोwn.
 */
व्योम xprt_rdma_बंद(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);

	rpcrdma_xprt_disconnect(r_xprt);

	xprt->reestablish_समयout = 0;
	++xprt->connect_cookie;
	xprt_disconnect_करोne(xprt);
पूर्ण

/**
 * xprt_rdma_set_port - update server port with rpcbind result
 * @xprt: controlling RPC transport
 * @port: new port value
 *
 * Transport connect status is unchanged.
 */
अटल व्योम
xprt_rdma_set_port(काष्ठा rpc_xprt *xprt, u16 port)
अणु
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&xprt->addr;
	अक्षर buf[8];

	rpc_set_port(sap, port);

	kमुक्त(xprt->address_strings[RPC_DISPLAY_PORT]);
	snम_लिखो(buf, माप(buf), "%u", port);
	xprt->address_strings[RPC_DISPLAY_PORT] = kstrdup(buf, GFP_KERNEL);

	kमुक्त(xprt->address_strings[RPC_DISPLAY_HEX_PORT]);
	snम_लिखो(buf, माप(buf), "%4hx", port);
	xprt->address_strings[RPC_DISPLAY_HEX_PORT] = kstrdup(buf, GFP_KERNEL);
पूर्ण

/**
 * xprt_rdma_समयr - invoked when an RPC बार out
 * @xprt: controlling RPC transport
 * @task: RPC task that समयd out
 *
 * Invoked when the transport is still connected, but an RPC
 * retransmit समयout occurs.
 *
 * Since RDMA connections करोn't have a keep-alive, क्रमcibly
 * disconnect and retry to connect. This drives full
 * detection of the network path, and retransmissions of
 * all pending RPCs.
 */
अटल व्योम
xprt_rdma_समयr(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	xprt_क्रमce_disconnect(xprt);
पूर्ण

/**
 * xprt_rdma_set_connect_समयout - set समयouts क्रम establishing a connection
 * @xprt: controlling transport instance
 * @connect_समयout: reconnect समयout after client disconnects
 * @reconnect_समयout: reconnect समयout after server disconnects
 *
 */
अटल व्योम xprt_rdma_set_connect_समयout(काष्ठा rpc_xprt *xprt,
					  अचिन्हित दीर्घ connect_समयout,
					  अचिन्हित दीर्घ reconnect_समयout)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);

	trace_xprtrdma_op_set_cto(r_xprt, connect_समयout, reconnect_समयout);

	spin_lock(&xprt->transport_lock);

	अगर (connect_समयout < xprt->connect_समयout) अणु
		काष्ठा rpc_समयout to;
		अचिन्हित दीर्घ initval;

		to = *xprt->समयout;
		initval = connect_समयout;
		अगर (initval < RPCRDMA_INIT_REEST_TO << 1)
			initval = RPCRDMA_INIT_REEST_TO << 1;
		to.to_initval = initval;
		to.to_maxval = initval;
		r_xprt->rx_समयout = to;
		xprt->समयout = &r_xprt->rx_समयout;
		xprt->connect_समयout = connect_समयout;
	पूर्ण

	अगर (reconnect_समयout < xprt->max_reconnect_समयout)
		xprt->max_reconnect_समयout = reconnect_समयout;

	spin_unlock(&xprt->transport_lock);
पूर्ण

/**
 * xprt_rdma_connect - schedule an attempt to reconnect
 * @xprt: transport state
 * @task: RPC scheduler context (unused)
 *
 */
अटल व्योम
xprt_rdma_connect(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	अचिन्हित दीर्घ delay;

	delay = 0;
	अगर (ep && ep->re_connect_status != 0) अणु
		delay = xprt_reconnect_delay(xprt);
		xprt_reconnect_backoff(xprt, RPCRDMA_INIT_REEST_TO);
	पूर्ण
	trace_xprtrdma_op_connect(r_xprt, delay);
	queue_delayed_work(xprtiod_workqueue, &r_xprt->rx_connect_worker,
			   delay);
पूर्ण

/**
 * xprt_rdma_alloc_slot - allocate an rpc_rqst
 * @xprt: controlling RPC transport
 * @task: RPC task requesting a fresh rpc_rqst
 *
 * tk_status values:
 *	%0 अगर task->tk_rqstp poपूर्णांकs to a fresh rpc_rqst
 *	%-EAGAIN अगर no rpc_rqst is available; queued on backlog
 */
अटल व्योम
xprt_rdma_alloc_slot(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	काष्ठा rpcrdma_req *req;

	req = rpcrdma_buffer_get(&r_xprt->rx_buf);
	अगर (!req)
		जाओ out_sleep;
	task->tk_rqstp = &req->rl_slot;
	task->tk_status = 0;
	वापस;

out_sleep:
	task->tk_status = -EAGAIN;
	xprt_add_backlog(xprt, task);
पूर्ण

/**
 * xprt_rdma_मुक्त_slot - release an rpc_rqst
 * @xprt: controlling RPC transport
 * @rqst: rpc_rqst to release
 *
 */
अटल व्योम
xprt_rdma_मुक्त_slot(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा rpcrdma_xprt *r_xprt =
		container_of(xprt, काष्ठा rpcrdma_xprt, rx_xprt);

	rpcrdma_reply_put(&r_xprt->rx_buf, rpcr_to_rdmar(rqst));
	अगर (!xprt_wake_up_backlog(xprt, rqst)) अणु
		स_रखो(rqst, 0, माप(*rqst));
		rpcrdma_buffer_put(&r_xprt->rx_buf, rpcr_to_rdmar(rqst));
	पूर्ण
पूर्ण

अटल bool rpcrdma_check_regbuf(काष्ठा rpcrdma_xprt *r_xprt,
				 काष्ठा rpcrdma_regbuf *rb, माप_प्रकार size,
				 gfp_t flags)
अणु
	अगर (unlikely(rdmab_length(rb) < size)) अणु
		अगर (!rpcrdma_regbuf_पुनः_स्मृति(rb, size, flags))
			वापस false;
		r_xprt->rx_stats.hardway_रेजिस्टर_count += size;
	पूर्ण
	वापस true;
पूर्ण

/**
 * xprt_rdma_allocate - allocate transport resources क्रम an RPC
 * @task: RPC task
 *
 * Return values:
 *        0:	Success; rq_buffer poपूर्णांकs to RPC buffer to use
 *   ENOMEM:	Out of memory, call again later
 *      EIO:	A permanent error occurred, करो not retry
 */
अटल पूर्णांक
xprt_rdma_allocate(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *rqst = task->tk_rqstp;
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(rqst->rq_xprt);
	काष्ठा rpcrdma_req *req = rpcr_to_rdmar(rqst);
	gfp_t flags;

	flags = RPCRDMA_DEF_GFP;
	अगर (RPC_IS_SWAPPER(task))
		flags = __GFP_MEMALLOC | GFP_NOWAIT | __GFP_NOWARN;

	अगर (!rpcrdma_check_regbuf(r_xprt, req->rl_sendbuf, rqst->rq_callsize,
				  flags))
		जाओ out_fail;
	अगर (!rpcrdma_check_regbuf(r_xprt, req->rl_recvbuf, rqst->rq_rcvsize,
				  flags))
		जाओ out_fail;

	rqst->rq_buffer = rdmab_data(req->rl_sendbuf);
	rqst->rq_rbuffer = rdmab_data(req->rl_recvbuf);
	वापस 0;

out_fail:
	वापस -ENOMEM;
पूर्ण

/**
 * xprt_rdma_मुक्त - release resources allocated by xprt_rdma_allocate
 * @task: RPC task
 *
 * Caller guarantees rqst->rq_buffer is non-शून्य.
 */
अटल व्योम
xprt_rdma_मुक्त(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *rqst = task->tk_rqstp;
	काष्ठा rpcrdma_req *req = rpcr_to_rdmar(rqst);

	अगर (unlikely(!list_empty(&req->rl_रेजिस्टरed))) अणु
		trace_xprtrdma_mrs_zap(task);
		frwr_unmap_sync(rpcx_to_rdmax(rqst->rq_xprt), req);
	पूर्ण

	/* XXX: If the RPC is completing because of a संकेत and
	 * not because a reply was received, we ought to ensure
	 * that the Send completion has fired, so that memory
	 * involved with the Send is not still visible to the NIC.
	 */
पूर्ण

/**
 * xprt_rdma_send_request - marshal and send an RPC request
 * @rqst: RPC message in rq_snd_buf
 *
 * Caller holds the transport's ग_लिखो lock.
 *
 * Returns:
 *	%0 अगर the RPC message has been sent
 *	%-ENOTCONN अगर the caller should reconnect and call again
 *	%-EAGAIN अगर the caller should call again
 *	%-ENOBUFS अगर the caller should call again after a delay
 *	%-EMSGSIZE अगर encoding ran out of buffer space. The request
 *		was not sent. Do not try to send this message again.
 *	%-EIO अगर an I/O error occurred. The request was not sent.
 *		Do not try to send this message again.
 */
अटल पूर्णांक
xprt_rdma_send_request(काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा rpc_xprt *xprt = rqst->rq_xprt;
	काष्ठा rpcrdma_req *req = rpcr_to_rdmar(rqst);
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	पूर्णांक rc = 0;

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
	अगर (unlikely(!rqst->rq_buffer))
		वापस xprt_rdma_bc_send_reply(rqst);
#पूर्ण_अगर	/* CONFIG_SUNRPC_BACKCHANNEL */

	अगर (!xprt_connected(xprt))
		वापस -ENOTCONN;

	अगर (!xprt_request_get_cong(xprt, rqst))
		वापस -EBADSLT;

	rc = rpcrdma_marshal_req(r_xprt, rqst);
	अगर (rc < 0)
		जाओ failed_marshal;

	/* Must suppress retransmit to मुख्यtain credits */
	अगर (rqst->rq_connect_cookie == xprt->connect_cookie)
		जाओ drop_connection;
	rqst->rq_xसमय = kसमय_get();

	अगर (rpcrdma_post_sends(r_xprt, req))
		जाओ drop_connection;

	rqst->rq_xmit_bytes_sent += rqst->rq_snd_buf.len;

	/* An RPC with no reply will throw off credit accounting,
	 * so drop the connection to reset the credit grant.
	 */
	अगर (!rpc_reply_expected(rqst->rq_task))
		जाओ drop_connection;
	वापस 0;

failed_marshal:
	अगर (rc != -ENOTCONN)
		वापस rc;
drop_connection:
	xprt_rdma_बंद(xprt);
	वापस -ENOTCONN;
पूर्ण

व्योम xprt_rdma_prपूर्णांक_stats(काष्ठा rpc_xprt *xprt, काष्ठा seq_file *seq)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	दीर्घ idle_समय = 0;

	अगर (xprt_connected(xprt))
		idle_समय = (दीर्घ)(jअगरfies - xprt->last_used) / HZ;

	seq_माला_दो(seq, "\txprt:\trdma ");
	seq_म_लिखो(seq, "%u %lu %lu %lu %ld %lu %lu %lu %llu %llu ",
		   0,	/* need a local port? */
		   xprt->stat.bind_count,
		   xprt->stat.connect_count,
		   xprt->stat.connect_समय / HZ,
		   idle_समय,
		   xprt->stat.sends,
		   xprt->stat.recvs,
		   xprt->stat.bad_xids,
		   xprt->stat.req_u,
		   xprt->stat.bklog_u);
	seq_म_लिखो(seq, "%lu %lu %lu %llu %llu %llu %llu %lu %lu %lu %lu ",
		   r_xprt->rx_stats.पढ़ो_chunk_count,
		   r_xprt->rx_stats.ग_लिखो_chunk_count,
		   r_xprt->rx_stats.reply_chunk_count,
		   r_xprt->rx_stats.total_rdma_request,
		   r_xprt->rx_stats.total_rdma_reply,
		   r_xprt->rx_stats.pullup_copy_count,
		   r_xprt->rx_stats.fixup_copy_count,
		   r_xprt->rx_stats.hardway_रेजिस्टर_count,
		   r_xprt->rx_stats.failed_marshal_count,
		   r_xprt->rx_stats.bad_reply_count,
		   r_xprt->rx_stats.nomsg_call_count);
	seq_म_लिखो(seq, "%lu %lu %lu %lu %lu %lu\n",
		   r_xprt->rx_stats.mrs_recycled,
		   r_xprt->rx_stats.mrs_orphaned,
		   r_xprt->rx_stats.mrs_allocated,
		   r_xprt->rx_stats.local_inv_needed,
		   r_xprt->rx_stats.empty_sendctx_q,
		   r_xprt->rx_stats.reply_रुकोs_क्रम_send);
पूर्ण

अटल पूर्णांक
xprt_rdma_enable_swap(काष्ठा rpc_xprt *xprt)
अणु
	वापस 0;
पूर्ण

अटल व्योम
xprt_rdma_disable_swap(काष्ठा rpc_xprt *xprt)
अणु
पूर्ण

/*
 * Plumbing क्रम rpc transport चयन and kernel module
 */

अटल स्थिर काष्ठा rpc_xprt_ops xprt_rdma_procs = अणु
	.reserve_xprt		= xprt_reserve_xprt_cong,
	.release_xprt		= xprt_release_xprt_cong, /* sunrpc/xprt.c */
	.alloc_slot		= xprt_rdma_alloc_slot,
	.मुक्त_slot		= xprt_rdma_मुक्त_slot,
	.release_request	= xprt_release_rqst_cong,       /* ditto */
	.रुको_क्रम_reply_request	= xprt_रुको_क्रम_reply_request_def, /* ditto */
	.समयr			= xprt_rdma_समयr,
	.rpcbind		= rpcb_getport_async,	/* sunrpc/rpcb_clnt.c */
	.set_port		= xprt_rdma_set_port,
	.connect		= xprt_rdma_connect,
	.buf_alloc		= xprt_rdma_allocate,
	.buf_मुक्त		= xprt_rdma_मुक्त,
	.send_request		= xprt_rdma_send_request,
	.बंद			= xprt_rdma_बंद,
	.destroy		= xprt_rdma_destroy,
	.set_connect_समयout	= xprt_rdma_set_connect_समयout,
	.prपूर्णांक_stats		= xprt_rdma_prपूर्णांक_stats,
	.enable_swap		= xprt_rdma_enable_swap,
	.disable_swap		= xprt_rdma_disable_swap,
	.inject_disconnect	= xprt_rdma_inject_disconnect,
#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
	.bc_setup		= xprt_rdma_bc_setup,
	.bc_maxpayload		= xprt_rdma_bc_maxpayload,
	.bc_num_slots		= xprt_rdma_bc_max_slots,
	.bc_मुक्त_rqst		= xprt_rdma_bc_मुक्त_rqst,
	.bc_destroy		= xprt_rdma_bc_destroy,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा xprt_class xprt_rdma = अणु
	.list			= LIST_HEAD_INIT(xprt_rdma.list),
	.name			= "rdma",
	.owner			= THIS_MODULE,
	.ident			= XPRT_TRANSPORT_RDMA,
	.setup			= xprt_setup_rdma,
	.netid			= अणु "rdma", "rdma6", "" पूर्ण,
पूर्ण;

व्योम xprt_rdma_cleanup(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
	अगर (sunrpc_table_header) अणु
		unरेजिस्टर_sysctl_table(sunrpc_table_header);
		sunrpc_table_header = शून्य;
	पूर्ण
#पूर्ण_अगर

	xprt_unरेजिस्टर_transport(&xprt_rdma);
	xprt_unरेजिस्टर_transport(&xprt_rdma_bc);
पूर्ण

पूर्णांक xprt_rdma_init(व्योम)
अणु
	पूर्णांक rc;

	rc = xprt_रेजिस्टर_transport(&xprt_rdma);
	अगर (rc)
		वापस rc;

	rc = xprt_रेजिस्टर_transport(&xprt_rdma_bc);
	अगर (rc) अणु
		xprt_unरेजिस्टर_transport(&xprt_rdma);
		वापस rc;
	पूर्ण

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
	अगर (!sunrpc_table_header)
		sunrpc_table_header = रेजिस्टर_sysctl_table(sunrpc_table);
#पूर्ण_अगर
	वापस 0;
पूर्ण
