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

#समावेश "rds.h"

अटल काष्ठा ctl_table_header *rds_sysctl_reg_table;

अटल अचिन्हित दीर्घ rds_sysctl_reconnect_min = 1;
अटल अचिन्हित दीर्घ rds_sysctl_reconnect_max = ~0UL;

अचिन्हित दीर्घ rds_sysctl_reconnect_min_jअगरfies;
अचिन्हित दीर्घ rds_sysctl_reconnect_max_jअगरfies = HZ;

अचिन्हित पूर्णांक  rds_sysctl_max_unacked_packets = 8;
अचिन्हित पूर्णांक  rds_sysctl_max_unacked_bytes = (16 << 20);

अचिन्हित पूर्णांक rds_sysctl_ping_enable = 1;

अटल काष्ठा ctl_table rds_sysctl_rds_table[] = अणु
	अणु
		.procname       = "reconnect_min_delay_ms",
		.data		= &rds_sysctl_reconnect_min_jअगरfies,
		.maxlen         = माप(अचिन्हित दीर्घ),
		.mode           = 0644,
		.proc_handler   = proc_करोuदीर्घvec_ms_jअगरfies_minmax,
		.extra1		= &rds_sysctl_reconnect_min,
		.extra2		= &rds_sysctl_reconnect_max_jअगरfies,
	पूर्ण,
	अणु
		.procname       = "reconnect_max_delay_ms",
		.data		= &rds_sysctl_reconnect_max_jअगरfies,
		.maxlen         = माप(अचिन्हित दीर्घ),
		.mode           = 0644,
		.proc_handler   = proc_करोuदीर्घvec_ms_jअगरfies_minmax,
		.extra1		= &rds_sysctl_reconnect_min_jअगरfies,
		.extra2		= &rds_sysctl_reconnect_max,
	पूर्ण,
	अणु
		.procname	= "max_unacked_packets",
		.data		= &rds_sysctl_max_unacked_packets,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "max_unacked_bytes",
		.data		= &rds_sysctl_max_unacked_bytes,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "ping_enable",
		.data		= &rds_sysctl_ping_enable,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम rds_sysctl_निकास(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(rds_sysctl_reg_table);
पूर्ण

पूर्णांक rds_sysctl_init(व्योम)
अणु
	rds_sysctl_reconnect_min = msecs_to_jअगरfies(1);
	rds_sysctl_reconnect_min_jअगरfies = rds_sysctl_reconnect_min;

	rds_sysctl_reg_table =
		रेजिस्टर_net_sysctl(&init_net, "net/rds", rds_sysctl_rds_table);
	अगर (!rds_sysctl_reg_table)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
