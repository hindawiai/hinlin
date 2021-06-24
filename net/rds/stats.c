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
#समावेश <linux/export.h>

#समावेश "rds.h"

DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा rds_statistics, rds_stats);
EXPORT_PER_CPU_SYMBOL_GPL(rds_stats);

/* :.,$s/अचिन्हित दीर्घ\>.*\<s_\(.*\);/"\1",/g */

अटल स्थिर अक्षर *स्थिर rds_stat_names[] = अणु
	"conn_reset",
	"recv_drop_bad_checksum",
	"recv_drop_old_seq",
	"recv_drop_no_sock",
	"recv_drop_dead_sock",
	"recv_deliver_raced",
	"recv_delivered",
	"recv_queued",
	"recv_immediate_retry",
	"recv_delayed_retry",
	"recv_ack_required",
	"recv_rdma_bytes",
	"recv_ping",
	"send_queue_empty",
	"send_queue_full",
	"send_lock_contention",
	"send_lock_queue_raced",
	"send_immediate_retry",
	"send_delayed_retry",
	"send_drop_acked",
	"send_ack_required",
	"send_queued",
	"send_rdma",
	"send_rdma_bytes",
	"send_pong",
	"page_remainder_hit",
	"page_remainder_miss",
	"copy_to_user",
	"copy_from_user",
	"cong_update_queued",
	"cong_update_received",
	"cong_send_error",
	"cong_send_blocked",
	"recv_bytes_added_to_sock",
	"recv_bytes_freed_fromsock",
	"send_stuck_rm",
पूर्ण;

व्योम rds_stats_info_copy(काष्ठा rds_info_iterator *iter,
			 uपूर्णांक64_t *values, स्थिर अक्षर *स्थिर *names, माप_प्रकार nr)
अणु
	काष्ठा rds_info_counter ctr;
	माप_प्रकार i;

	क्रम (i = 0; i < nr; i++) अणु
		BUG_ON(म_माप(names[i]) >= माप(ctr.name));
		म_नकलन(ctr.name, names[i], माप(ctr.name) - 1);
		ctr.name[माप(ctr.name) - 1] = '\0';
		ctr.value = values[i];

		rds_info_copy(iter, &ctr, माप(ctr));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rds_stats_info_copy);

/*
 * This gives global counters across all the transports.  The strings
 * are copied in so that the tool करोesn't need knowledge of the specअगरic
 * stats that we're exporting.  Some are pretty implementation dependent
 * and may change over समय.  That करोesn't stop them from being useful.
 *
 * This is the only function in the chain that knows about the byte granular
 * length in userspace.  It converts it to number of stat entries that the
 * rest of the functions operate in.
 */
अटल व्योम rds_stats_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			   काष्ठा rds_info_iterator *iter,
			   काष्ठा rds_info_lengths *lens)
अणु
	काष्ठा rds_statistics stats = अणु0, पूर्ण;
	uपूर्णांक64_t *src;
	uपूर्णांक64_t *sum;
	माप_प्रकार i;
	पूर्णांक cpu;
	अचिन्हित पूर्णांक avail;

	avail = len / माप(काष्ठा rds_info_counter);

	अगर (avail < ARRAY_SIZE(rds_stat_names)) अणु
		avail = 0;
		जाओ trans;
	पूर्ण

	क्रम_each_online_cpu(cpu) अणु
		src = (uपूर्णांक64_t *)&(per_cpu(rds_stats, cpu));
		sum = (uपूर्णांक64_t *)&stats;
		क्रम (i = 0; i < माप(stats) / माप(uपूर्णांक64_t); i++)
			*(sum++) += *(src++);
	पूर्ण

	rds_stats_info_copy(iter, (uपूर्णांक64_t *)&stats, rds_stat_names,
			    ARRAY_SIZE(rds_stat_names));
	avail -= ARRAY_SIZE(rds_stat_names);

trans:
	lens->each = माप(काष्ठा rds_info_counter);
	lens->nr = rds_trans_stats_info_copy(iter, avail) +
		   ARRAY_SIZE(rds_stat_names);
पूर्ण

व्योम rds_stats_निकास(व्योम)
अणु
	rds_info_deरेजिस्टर_func(RDS_INFO_COUNTERS, rds_stats_info);
पूर्ण

पूर्णांक rds_stats_init(व्योम)
अणु
	rds_info_रेजिस्टर_func(RDS_INFO_COUNTERS, rds_stats_info);
	वापस 0;
पूर्ण
