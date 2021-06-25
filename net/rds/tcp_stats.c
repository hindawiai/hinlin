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
#समावेश <linux/percpu.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>

#समावेश "rds.h"
#समावेश "tcp.h"

DEFINE_PER_CPU(काष्ठा rds_tcp_statistics, rds_tcp_stats)
	____cacheline_aligned;

अटल स्थिर अक्षर * स्थिर rds_tcp_stat_names[] = अणु
	"tcp_data_ready_calls",
	"tcp_write_space_calls",
	"tcp_sndbuf_full",
	"tcp_connect_raced",
	"tcp_listen_closed_stale",
पूर्ण;

अचिन्हित पूर्णांक rds_tcp_stats_info_copy(काष्ठा rds_info_iterator *iter,
				     अचिन्हित पूर्णांक avail)
अणु
	काष्ठा rds_tcp_statistics stats = अणु0, पूर्ण;
	uपूर्णांक64_t *src;
	uपूर्णांक64_t *sum;
	माप_प्रकार i;
	पूर्णांक cpu;

	अगर (avail < ARRAY_SIZE(rds_tcp_stat_names))
		जाओ out;

	क्रम_each_online_cpu(cpu) अणु
		src = (uपूर्णांक64_t *)&(per_cpu(rds_tcp_stats, cpu));
		sum = (uपूर्णांक64_t *)&stats;
		क्रम (i = 0; i < माप(stats) / माप(uपूर्णांक64_t); i++)
			*(sum++) += *(src++);
	पूर्ण

	rds_stats_info_copy(iter, (uपूर्णांक64_t *)&stats, rds_tcp_stat_names,
			    ARRAY_SIZE(rds_tcp_stat_names));
out:
	वापस ARRAY_SIZE(rds_tcp_stat_names);
पूर्ण
