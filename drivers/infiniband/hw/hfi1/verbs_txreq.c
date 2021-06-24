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

#समावेश "hfi.h"
#समावेश "verbs_txreq.h"
#समावेश "qp.h"
#समावेश "trace.h"

#घोषणा TXREQ_LEN 24

व्योम hfi1_put_txreq(काष्ठा verbs_txreq *tx)
अणु
	काष्ठा hfi1_ibdev *dev;
	काष्ठा rvt_qp *qp;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक seq;
	काष्ठा hfi1_qp_priv *priv;

	qp = tx->qp;
	dev = to_idev(qp->ibqp.device);

	अगर (tx->mr)
		rvt_put_mr(tx->mr);

	sdma_txclean(dd_from_dev(dev), &tx->txreq);

	/* Free verbs_txreq and वापस to slab cache */
	kmem_cache_मुक्त(dev->verbs_txreq_cache, tx);

	करो अणु
		seq = पढ़ो_seqbegin(&dev->txरुको_lock);
		अगर (!list_empty(&dev->txरुको)) अणु
			काष्ठा ioरुको *रुको;

			ग_लिखो_seqlock_irqsave(&dev->txरुको_lock, flags);
			रुको = list_first_entry(&dev->txरुको, काष्ठा ioरुको,
						list);
			qp = ioरुको_to_qp(रुको);
			priv = qp->priv;
			list_del_init(&priv->s_ioरुको.list);
			/* refcount held until actual wake up */
			ग_लिखो_sequnlock_irqrestore(&dev->txरुको_lock, flags);
			hfi1_qp_wakeup(qp, RVT_S_WAIT_TX);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (पढ़ो_seqretry(&dev->txरुको_lock, seq));
पूर्ण

काष्ठा verbs_txreq *__get_txreq(काष्ठा hfi1_ibdev *dev,
				काष्ठा rvt_qp *qp)
	__must_hold(&qp->s_lock)
अणु
	काष्ठा verbs_txreq *tx = शून्य;

	ग_लिखो_seqlock(&dev->txरुको_lock);
	अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) अणु
		काष्ठा hfi1_qp_priv *priv;

		tx = kmem_cache_alloc(dev->verbs_txreq_cache, VERBS_TXREQ_GFP);
		अगर (tx)
			जाओ out;
		priv = qp->priv;
		अगर (list_empty(&priv->s_ioरुको.list)) अणु
			dev->n_txरुको++;
			qp->s_flags |= RVT_S_WAIT_TX;
			list_add_tail(&priv->s_ioरुको.list, &dev->txरुको);
			priv->s_ioरुको.lock = &dev->txरुको_lock;
			trace_hfi1_qpsleep(qp, RVT_S_WAIT_TX);
			rvt_get_qp(qp);
		पूर्ण
		qp->s_flags &= ~RVT_S_BUSY;
	पूर्ण
out:
	ग_लिखो_sequnlock(&dev->txरुको_lock);
	वापस tx;
पूर्ण

पूर्णांक verbs_txreq_init(काष्ठा hfi1_ibdev *dev)
अणु
	अक्षर buf[TXREQ_LEN];
	काष्ठा hfi1_devdata *dd = dd_from_dev(dev);

	snम_लिखो(buf, माप(buf), "hfi1_%u_vtxreq_cache", dd->unit);
	dev->verbs_txreq_cache = kmem_cache_create(buf,
						   माप(काष्ठा verbs_txreq),
						   0, SLAB_HWCACHE_ALIGN,
						   शून्य);
	अगर (!dev->verbs_txreq_cache)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम verbs_txreq_निकास(काष्ठा hfi1_ibdev *dev)
अणु
	kmem_cache_destroy(dev->verbs_txreq_cache);
	dev->verbs_txreq_cache = शून्य;
पूर्ण
