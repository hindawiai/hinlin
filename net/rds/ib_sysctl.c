<शैली गुरु>
/*
 * Copyright (c) 2006 Oracle.  All rights reserved.
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
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/proc_fs.h>

#समावेश "ib.h"

अटल काष्ठा ctl_table_header *rds_ib_sysctl_hdr;

अचिन्हित दीर्घ rds_ib_sysctl_max_send_wr = RDS_IB_DEFAULT_SEND_WR;
अचिन्हित दीर्घ rds_ib_sysctl_max_recv_wr = RDS_IB_DEFAULT_RECV_WR;
अचिन्हित दीर्घ rds_ib_sysctl_max_recv_allocation = (128 * 1024 * 1024) / RDS_FRAG_SIZE;
अटल अचिन्हित दीर्घ rds_ib_sysctl_max_wr_min = 1;
/* hardware will fail CQ creation दीर्घ beक्रमe this */
अटल अचिन्हित दीर्घ rds_ib_sysctl_max_wr_max = (u32)~0;

अचिन्हित दीर्घ rds_ib_sysctl_max_unsig_wrs = 16;
अटल अचिन्हित दीर्घ rds_ib_sysctl_max_unsig_wr_min = 1;
अटल अचिन्हित दीर्घ rds_ib_sysctl_max_unsig_wr_max = 64;

/*
 * This sysctl करोes nothing.
 *
 * Backwards compatibility with RDS 3.0 wire protocol
 * disables initial FC credit exchange.
 * If it's ever possible to drop 3.0 support,
 * setting this to 1 and moving init/refill of send/recv
 * rings from ib_cm_connect_complete() back पूर्णांकo ib_setup_qp()
 * will cause credits to be added beक्रमe protocol negotiation.
 */
अचिन्हित पूर्णांक rds_ib_sysctl_flow_control = 0;

अटल काष्ठा ctl_table rds_ib_sysctl_table[] = अणु
	अणु
		.procname       = "max_send_wr",
		.data		= &rds_ib_sysctl_max_send_wr,
		.maxlen         = माप(अचिन्हित दीर्घ),
		.mode           = 0644,
		.proc_handler   = proc_करोuदीर्घvec_minmax,
		.extra1		= &rds_ib_sysctl_max_wr_min,
		.extra2		= &rds_ib_sysctl_max_wr_max,
	पूर्ण,
	अणु
		.procname       = "max_recv_wr",
		.data		= &rds_ib_sysctl_max_recv_wr,
		.maxlen         = माप(अचिन्हित दीर्घ),
		.mode           = 0644,
		.proc_handler   = proc_करोuदीर्घvec_minmax,
		.extra1		= &rds_ib_sysctl_max_wr_min,
		.extra2		= &rds_ib_sysctl_max_wr_max,
	पूर्ण,
	अणु
		.procname       = "max_unsignaled_wr",
		.data		= &rds_ib_sysctl_max_unsig_wrs,
		.maxlen         = माप(अचिन्हित दीर्घ),
		.mode           = 0644,
		.proc_handler   = proc_करोuदीर्घvec_minmax,
		.extra1		= &rds_ib_sysctl_max_unsig_wr_min,
		.extra2		= &rds_ib_sysctl_max_unsig_wr_max,
	पूर्ण,
	अणु
		.procname       = "max_recv_allocation",
		.data		= &rds_ib_sysctl_max_recv_allocation,
		.maxlen         = माप(अचिन्हित दीर्घ),
		.mode           = 0644,
		.proc_handler   = proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "flow_control",
		.data		= &rds_ib_sysctl_flow_control,
		.maxlen		= माप(rds_ib_sysctl_flow_control),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम rds_ib_sysctl_निकास(व्योम)
अणु
	अगर (rds_ib_sysctl_hdr)
		unरेजिस्टर_net_sysctl_table(rds_ib_sysctl_hdr);
पूर्ण

पूर्णांक rds_ib_sysctl_init(व्योम)
अणु
	rds_ib_sysctl_hdr = रेजिस्टर_net_sysctl(&init_net, "net/rds/ib", rds_ib_sysctl_table);
	अगर (!rds_ib_sysctl_hdr)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
