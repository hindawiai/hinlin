<शैली गुरु>
/* This file is part of the Emulex RoCE Device Driver क्रम
 * RoCE (RDMA over Converged Ethernet) adapters.
 * Copyright (C) 2012-2015 Emulex. All rights reserved.
 * EMULEX and SLI are trademarks of Emulex.
 * www.emulex.com
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the मुख्य
 * directory of this source tree, or the BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#अगर_अघोषित __OCRDMA_STATS_H__
#घोषणा __OCRDMA_STATS_H__

#समावेश <linux/debugfs.h>
#समावेश "ocrdma.h"
#समावेश "ocrdma_hw.h"

#घोषणा OCRDMA_MAX_DBGFS_MEM 4096

क्रमागत OCRDMA_STATS_TYPE अणु
	OCRDMA_RSRC_STATS,
	OCRDMA_RXSTATS,
	OCRDMA_WQESTATS,
	OCRDMA_TXSTATS,
	OCRDMA_DB_ERRSTATS,
	OCRDMA_RXQP_ERRSTATS,
	OCRDMA_TXQP_ERRSTATS,
	OCRDMA_TX_DBG_STATS,
	OCRDMA_RX_DBG_STATS,
	OCRDMA_DRV_STATS,
	OCRDMA_RESET_STATS
पूर्ण;

व्योम ocrdma_rem_debugfs(व्योम);
व्योम ocrdma_init_debugfs(व्योम);
bool ocrdma_alloc_stats_resources(काष्ठा ocrdma_dev *dev);
व्योम ocrdma_release_stats_resources(काष्ठा ocrdma_dev *dev);
व्योम ocrdma_rem_port_stats(काष्ठा ocrdma_dev *dev);
व्योम ocrdma_add_port_stats(काष्ठा ocrdma_dev *dev);
व्योम ocrdma_pma_counters(काष्ठा ocrdma_dev *dev, काष्ठा ib_mad *out_mad);

#पूर्ण_अगर	/* __OCRDMA_STATS_H__ */
