<शैली गुरु>
/*
 * Copyright(c) 2016 - 2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
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
 */

#अगर_अघोषित HFI1_VERBS_TXREQ_H
#घोषणा HFI1_VERBS_TXREQ_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#समावेश "verbs.h"
#समावेश "sdma_txreq.h"
#समावेश "iowait.h"

काष्ठा verbs_txreq अणु
	काष्ठा hfi1_sdma_header	phdr;
	काष्ठा sdma_txreq       txreq;
	काष्ठा rvt_qp           *qp;
	काष्ठा rvt_swqe         *wqe;
	काष्ठा rvt_mregion	*mr;
	काष्ठा rvt_sge_state    *ss;
	काष्ठा sdma_engine     *sde;
	काष्ठा send_context     *psc;
	u16                     hdr_dwords;
	u16			s_cur_size;
पूर्ण;

काष्ठा hfi1_ibdev;
काष्ठा verbs_txreq *__get_txreq(काष्ठा hfi1_ibdev *dev,
				काष्ठा rvt_qp *qp);

#घोषणा VERBS_TXREQ_GFP (GFP_ATOMIC | __GFP_NOWARN)
अटल अंतरभूत काष्ठा verbs_txreq *get_txreq(काष्ठा hfi1_ibdev *dev,
					    काष्ठा rvt_qp *qp)
	__must_hold(&qp->slock)
अणु
	काष्ठा verbs_txreq *tx;
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	tx = kmem_cache_alloc(dev->verbs_txreq_cache, VERBS_TXREQ_GFP);
	अगर (unlikely(!tx)) अणु
		/* call slow path to get the lock */
		tx = __get_txreq(dev, qp);
		अगर (!tx)
			वापस tx;
	पूर्ण
	tx->qp = qp;
	tx->mr = शून्य;
	tx->sde = priv->s_sde;
	tx->psc = priv->s_sendcontext;
	/* so that we can test अगर the sdma descriptors are there */
	tx->txreq.num_desc = 0;
	/* Set the header type */
	tx->phdr.hdr.hdr_type = priv->hdr_type;
	tx->txreq.flags = 0;
	वापस tx;
पूर्ण

अटल अंतरभूत काष्ठा verbs_txreq *get_रुकोing_verbs_txreq(काष्ठा ioरुको_work *w)
अणु
	काष्ठा sdma_txreq *stx;

	stx = ioरुको_get_txhead(w);
	अगर (stx)
		वापस container_of(stx, काष्ठा verbs_txreq, txreq);
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool verbs_txreq_queued(काष्ठा ioरुको_work *w)
अणु
	वापस ioरुको_packet_queued(w);
पूर्ण

व्योम hfi1_put_txreq(काष्ठा verbs_txreq *tx);
पूर्णांक verbs_txreq_init(काष्ठा hfi1_ibdev *dev);
व्योम verbs_txreq_निकास(काष्ठा hfi1_ibdev *dev);

#पूर्ण_अगर                         /* HFI1_VERBS_TXREQ_H */
