<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
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

#अगर_अघोषित _LINUX_SUNRPC_XPRTRDMA_H
#घोषणा _LINUX_SUNRPC_XPRTRDMA_H

/*
 * Constants. Max RPC/NFS header is big enough to account क्रम
 * additional marshaling buffers passed करोwn by Linux client.
 *
 * RDMA header is currently fixed max size, and is big enough क्रम a
 * fully-chunked NFS message (पढ़ो chunks are the largest). Note only
 * a single chunk type per message is supported currently.
 */
#घोषणा RPCRDMA_MIN_SLOT_TABLE	(4U)
#घोषणा RPCRDMA_DEF_SLOT_TABLE	(128U)
#घोषणा RPCRDMA_MAX_SLOT_TABLE	(16384U)

#घोषणा RPCRDMA_MIN_INLINE  (1024)	/* min अंतरभूत thresh */
#घोषणा RPCRDMA_DEF_INLINE  (4096)	/* शेष अंतरभूत thresh */
#घोषणा RPCRDMA_MAX_INLINE  (65536)	/* max अंतरभूत thresh */

/* Memory registration strategies, by number.
 * This is part of a kernel / user space API. Do not हटाओ. */
क्रमागत rpcrdma_memreg अणु
	RPCRDMA_BOUNCEBUFFERS = 0,
	RPCRDMA_REGISTER,
	RPCRDMA_MEMWINDOWS,
	RPCRDMA_MEMWINDOWS_ASYNC,
	RPCRDMA_MTHCAFMR,
	RPCRDMA_FRWR,
	RPCRDMA_ALLPHYSICAL,
	RPCRDMA_LAST
पूर्ण;

#पूर्ण_अगर /* _LINUX_SUNRPC_XPRTRDMA_H */
