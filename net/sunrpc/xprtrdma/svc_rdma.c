<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2015-2018 Oracle.  All rights reserved.
 * Copyright (c) 2005-2006 Network Appliance, Inc. All rights reserved.
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
 *
 * Author: Tom Tucker <tom@खोलोgridcomputing.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/svc_rdma.h>

#घोषणा RPCDBG_FACILITY	RPCDBG_SVCXPRT

/* RPC/RDMA parameters */
अचिन्हित पूर्णांक svcrdma_ord = 16;	/* historical शेष */
अटल अचिन्हित पूर्णांक min_ord = 1;
अटल अचिन्हित पूर्णांक max_ord = 255;
अचिन्हित पूर्णांक svcrdma_max_requests = RPCRDMA_MAX_REQUESTS;
अचिन्हित पूर्णांक svcrdma_max_bc_requests = RPCRDMA_MAX_BC_REQUESTS;
अटल अचिन्हित पूर्णांक min_max_requests = 4;
अटल अचिन्हित पूर्णांक max_max_requests = 16384;
अचिन्हित पूर्णांक svcrdma_max_req_size = RPCRDMA_DEF_INLINE_THRESH;
अटल अचिन्हित पूर्णांक min_max_अंतरभूत = RPCRDMA_DEF_INLINE_THRESH;
अटल अचिन्हित पूर्णांक max_max_अंतरभूत = RPCRDMA_MAX_INLINE_THRESH;
अटल अचिन्हित पूर्णांक svcrdma_stat_unused;
अटल अचिन्हित पूर्णांक zero;

काष्ठा percpu_counter svcrdma_stat_पढ़ो;
काष्ठा percpu_counter svcrdma_stat_recv;
काष्ठा percpu_counter svcrdma_stat_sq_starve;
काष्ठा percpu_counter svcrdma_stat_ग_लिखो;

क्रमागत अणु
	SVCRDMA_COUNTER_बफ_मान	= माप(अचिन्हित दीर्घ दीर्घ),
पूर्ण;

अटल पूर्णांक svcrdma_counter_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा percpu_counter *stat = (काष्ठा percpu_counter *)table->data;
	अक्षर पंचांगp[SVCRDMA_COUNTER_बफ_मान + 1];
	पूर्णांक len;

	अगर (ग_लिखो) अणु
		percpu_counter_set(stat, 0);
		वापस 0;
	पूर्ण

	len = snम_लिखो(पंचांगp, SVCRDMA_COUNTER_बफ_मान, "%lld\n",
		       percpu_counter_sum_positive(stat));
	अगर (len >= SVCRDMA_COUNTER_बफ_मान)
		वापस -EFAULT;
	len = म_माप(पंचांगp);
	अगर (*ppos > len) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण
	len -= *ppos;
	अगर (len > *lenp)
		len = *lenp;
	अगर (len)
		स_नकल(buffer, पंचांगp, len);
	*lenp = len;
	*ppos += len;

	वापस 0;
पूर्ण

अटल काष्ठा ctl_table_header *svcrdma_table_header;
अटल काष्ठा ctl_table svcrdma_parm_table[] = अणु
	अणु
		.procname	= "max_requests",
		.data		= &svcrdma_max_requests,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_max_requests,
		.extra2		= &max_max_requests
	पूर्ण,
	अणु
		.procname	= "max_req_size",
		.data		= &svcrdma_max_req_size,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_max_अंतरभूत,
		.extra2		= &max_max_अंतरभूत
	पूर्ण,
	अणु
		.procname	= "max_outbound_read_requests",
		.data		= &svcrdma_ord,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_ord,
		.extra2		= &max_ord,
	पूर्ण,

	अणु
		.procname	= "rdma_stat_read",
		.data		= &svcrdma_stat_पढ़ो,
		.maxlen		= SVCRDMA_COUNTER_बफ_मान,
		.mode		= 0644,
		.proc_handler	= svcrdma_counter_handler,
	पूर्ण,
	अणु
		.procname	= "rdma_stat_recv",
		.data		= &svcrdma_stat_recv,
		.maxlen		= SVCRDMA_COUNTER_बफ_मान,
		.mode		= 0644,
		.proc_handler	= svcrdma_counter_handler,
	पूर्ण,
	अणु
		.procname	= "rdma_stat_write",
		.data		= &svcrdma_stat_ग_लिखो,
		.maxlen		= SVCRDMA_COUNTER_बफ_मान,
		.mode		= 0644,
		.proc_handler	= svcrdma_counter_handler,
	पूर्ण,
	अणु
		.procname	= "rdma_stat_sq_starve",
		.data		= &svcrdma_stat_sq_starve,
		.maxlen		= SVCRDMA_COUNTER_बफ_मान,
		.mode		= 0644,
		.proc_handler	= svcrdma_counter_handler,
	पूर्ण,
	अणु
		.procname	= "rdma_stat_rq_starve",
		.data		= &svcrdma_stat_unused,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &zero,
		.extra2		= &zero,
	पूर्ण,
	अणु
		.procname	= "rdma_stat_rq_poll",
		.data		= &svcrdma_stat_unused,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &zero,
		.extra2		= &zero,
	पूर्ण,
	अणु
		.procname	= "rdma_stat_rq_prod",
		.data		= &svcrdma_stat_unused,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &zero,
		.extra2		= &zero,
	पूर्ण,
	अणु
		.procname	= "rdma_stat_sq_poll",
		.data		= &svcrdma_stat_unused,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &zero,
		.extra2		= &zero,
	पूर्ण,
	अणु
		.procname	= "rdma_stat_sq_prod",
		.data		= &svcrdma_stat_unused,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &zero,
		.extra2		= &zero,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table svcrdma_table[] = अणु
	अणु
		.procname	= "svc_rdma",
		.mode		= 0555,
		.child		= svcrdma_parm_table
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table svcrdma_root_table[] = अणु
	अणु
		.procname	= "sunrpc",
		.mode		= 0555,
		.child		= svcrdma_table
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम svc_rdma_proc_cleanup(व्योम)
अणु
	अगर (!svcrdma_table_header)
		वापस;
	unरेजिस्टर_sysctl_table(svcrdma_table_header);
	svcrdma_table_header = शून्य;

	percpu_counter_destroy(&svcrdma_stat_ग_लिखो);
	percpu_counter_destroy(&svcrdma_stat_sq_starve);
	percpu_counter_destroy(&svcrdma_stat_recv);
	percpu_counter_destroy(&svcrdma_stat_पढ़ो);
पूर्ण

अटल पूर्णांक svc_rdma_proc_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (svcrdma_table_header)
		वापस 0;

	rc = percpu_counter_init(&svcrdma_stat_पढ़ो, 0, GFP_KERNEL);
	अगर (rc)
		जाओ out_err;
	rc = percpu_counter_init(&svcrdma_stat_recv, 0, GFP_KERNEL);
	अगर (rc)
		जाओ out_err;
	rc = percpu_counter_init(&svcrdma_stat_sq_starve, 0, GFP_KERNEL);
	अगर (rc)
		जाओ out_err;
	rc = percpu_counter_init(&svcrdma_stat_ग_लिखो, 0, GFP_KERNEL);
	अगर (rc)
		जाओ out_err;

	svcrdma_table_header = रेजिस्टर_sysctl_table(svcrdma_root_table);
	वापस 0;

out_err:
	percpu_counter_destroy(&svcrdma_stat_sq_starve);
	percpu_counter_destroy(&svcrdma_stat_recv);
	percpu_counter_destroy(&svcrdma_stat_पढ़ो);
	वापस rc;
पूर्ण

व्योम svc_rdma_cleanup(व्योम)
अणु
	dprपूर्णांकk("SVCRDMA Module Removed, deregister RPC RDMA transport\n");
	svc_unreg_xprt_class(&svc_rdma_class);
	svc_rdma_proc_cleanup();
पूर्ण

पूर्णांक svc_rdma_init(व्योम)
अणु
	पूर्णांक rc;

	dprपूर्णांकk("SVCRDMA Module Init, register RPC RDMA transport\n");
	dprपूर्णांकk("\tsvcrdma_ord      : %d\n", svcrdma_ord);
	dprपूर्णांकk("\tmax_requests     : %u\n", svcrdma_max_requests);
	dprपूर्णांकk("\tmax_bc_requests  : %u\n", svcrdma_max_bc_requests);
	dprपूर्णांकk("\tmax_inline       : %d\n", svcrdma_max_req_size);

	rc = svc_rdma_proc_init();
	अगर (rc)
		वापस rc;

	/* Register RDMA with the SVC transport चयन */
	svc_reg_xprt_class(&svc_rdma_class);
	वापस 0;
पूर्ण
