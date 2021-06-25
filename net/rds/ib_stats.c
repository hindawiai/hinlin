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
#समावेश "ib.h"

DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा rds_ib_statistics, rds_ib_stats);

अटल स्थिर अक्षर *स्थिर rds_ib_stat_names[] = अणु
	"ib_connect_raced",
	"ib_listen_closed_stale",
	"ib_evt_handler_call",
	"ib_tasklet_call",
	"ib_tx_cq_event",
	"ib_tx_ring_full",
	"ib_tx_throttle",
	"ib_tx_sg_mapping_failure",
	"ib_tx_stalled",
	"ib_tx_credit_updates",
	"ib_rx_cq_event",
	"ib_rx_ring_empty",
	"ib_rx_refill_from_cq",
	"ib_rx_refill_from_thread",
	"ib_rx_alloc_limit",
	"ib_rx_total_frags",
	"ib_rx_total_incs",
	"ib_rx_credit_updates",
	"ib_ack_sent",
	"ib_ack_send_failure",
	"ib_ack_send_delayed",
	"ib_ack_send_piggybacked",
	"ib_ack_received",
	"ib_rdma_mr_8k_alloc",
	"ib_rdma_mr_8k_free",
	"ib_rdma_mr_8k_used",
	"ib_rdma_mr_8k_pool_flush",
	"ib_rdma_mr_8k_pool_wait",
	"ib_rdma_mr_8k_pool_depleted",
	"ib_rdma_mr_1m_alloc",
	"ib_rdma_mr_1m_free",
	"ib_rdma_mr_1m_used",
	"ib_rdma_mr_1m_pool_flush",
	"ib_rdma_mr_1m_pool_wait",
	"ib_rdma_mr_1m_pool_depleted",
	"ib_rdma_mr_8k_reused",
	"ib_rdma_mr_1m_reused",
	"ib_atomic_cswp",
	"ib_atomic_fadd",
पूर्ण;

अचिन्हित पूर्णांक rds_ib_stats_info_copy(काष्ठा rds_info_iterator *iter,
				    अचिन्हित पूर्णांक avail)
अणु
	काष्ठा rds_ib_statistics stats = अणु0, पूर्ण;
	uपूर्णांक64_t *src;
	uपूर्णांक64_t *sum;
	माप_प्रकार i;
	पूर्णांक cpu;

	अगर (avail < ARRAY_SIZE(rds_ib_stat_names))
		जाओ out;

	क्रम_each_online_cpu(cpu) अणु
		src = (uपूर्णांक64_t *)&(per_cpu(rds_ib_stats, cpu));
		sum = (uपूर्णांक64_t *)&stats;
		क्रम (i = 0; i < माप(stats) / माप(uपूर्णांक64_t); i++)
			*(sum++) += *(src++);
	पूर्ण

	rds_stats_info_copy(iter, (uपूर्णांक64_t *)&stats, rds_ib_stat_names,
			    ARRAY_SIZE(rds_ib_stat_names));
out:
	वापस ARRAY_SIZE(rds_ib_stat_names);
पूर्ण
