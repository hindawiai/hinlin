<शैली गुरु>
/*
 * Copyright (c) 2012 - 2019 Intel Corporation.  All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation.  * All rights reserved.
 * Copyright (c) 2005, 2006 PathScale, Inc. All rights reserved.
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
 */

#समावेश <linux/err.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <rdma/rdma_vt.h>
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/seq_file.h>
#पूर्ण_अगर

#समावेश "qib.h"

अटल अंतरभूत अचिन्हित mk_qpn(काष्ठा rvt_qpn_table *qpt,
			      काष्ठा rvt_qpn_map *map, अचिन्हित off)
अणु
	वापस (map - qpt->map) * RVT_BITS_PER_PAGE + off;
पूर्ण

अटल अंतरभूत अचिन्हित find_next_offset(काष्ठा rvt_qpn_table *qpt,
					काष्ठा rvt_qpn_map *map, अचिन्हित off,
					अचिन्हित n, u16 qpt_mask)
अणु
	अगर (qpt_mask) अणु
		off++;
		अगर (((off & qpt_mask) >> 1) >= n)
			off = (off | qpt_mask) + 2;
	पूर्ण अन्यथा अणु
		off = find_next_zero_bit(map->page, RVT_BITS_PER_PAGE, off);
	पूर्ण
	वापस off;
पूर्ण

स्थिर काष्ठा rvt_operation_params qib_post_parms[RVT_OPERATION_MAX] = अणु
[IB_WR_RDMA_WRITE] = अणु
	.length = माप(काष्ठा ib_rdma_wr),
	.qpt_support = BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
पूर्ण,

[IB_WR_RDMA_READ] = अणु
	.length = माप(काष्ठा ib_rdma_wr),
	.qpt_support = BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_ATOMIC,
पूर्ण,

[IB_WR_ATOMIC_CMP_AND_SWP] = अणु
	.length = माप(काष्ठा ib_atomic_wr),
	.qpt_support = BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_ATOMIC | RVT_OPERATION_ATOMIC_SGE,
पूर्ण,

[IB_WR_ATOMIC_FETCH_AND_ADD] = अणु
	.length = माप(काष्ठा ib_atomic_wr),
	.qpt_support = BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_ATOMIC | RVT_OPERATION_ATOMIC_SGE,
पूर्ण,

[IB_WR_RDMA_WRITE_WITH_IMM] = अणु
	.length = माप(काष्ठा ib_rdma_wr),
	.qpt_support = BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
पूर्ण,

[IB_WR_SEND] = अणु
	.length = माप(काष्ठा ib_send_wr),
	.qpt_support = BIT(IB_QPT_UD) | BIT(IB_QPT_SMI) | BIT(IB_QPT_GSI) |
		       BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
पूर्ण,

[IB_WR_SEND_WITH_IMM] = अणु
	.length = माप(काष्ठा ib_send_wr),
	.qpt_support = BIT(IB_QPT_UD) | BIT(IB_QPT_SMI) | BIT(IB_QPT_GSI) |
		       BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
पूर्ण,

पूर्ण;

अटल व्योम get_map_page(काष्ठा rvt_qpn_table *qpt, काष्ठा rvt_qpn_map *map)
अणु
	अचिन्हित दीर्घ page = get_zeroed_page(GFP_KERNEL);

	/*
	 * Free the page अगर someone raced with us installing it.
	 */

	spin_lock(&qpt->lock);
	अगर (map->page)
		मुक्त_page(page);
	अन्यथा
		map->page = (व्योम *)page;
	spin_unlock(&qpt->lock);
पूर्ण

/*
 * Allocate the next available QPN or
 * zero/one क्रम QP type IB_QPT_SMI/IB_QPT_GSI.
 */
पूर्णांक qib_alloc_qpn(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qpn_table *qpt,
		  क्रमागत ib_qp_type type, u32 port)
अणु
	u32 i, offset, max_scan, qpn;
	काष्ठा rvt_qpn_map *map;
	u32 ret;
	काष्ठा qib_ibdev *verbs_dev = container_of(rdi, काष्ठा qib_ibdev, rdi);
	काष्ठा qib_devdata *dd = container_of(verbs_dev, काष्ठा qib_devdata,
					      verbs_dev);
	u16 qpt_mask = dd->qpn_mask;

	अगर (type == IB_QPT_SMI || type == IB_QPT_GSI) अणु
		u32 n;

		ret = type == IB_QPT_GSI;
		n = 1 << (ret + 2 * (port - 1));
		spin_lock(&qpt->lock);
		अगर (qpt->flags & n)
			ret = -EINVAL;
		अन्यथा
			qpt->flags |= n;
		spin_unlock(&qpt->lock);
		जाओ bail;
	पूर्ण

	qpn = qpt->last + 2;
	अगर (qpn >= RVT_QPN_MAX)
		qpn = 2;
	अगर (qpt_mask && ((qpn & qpt_mask) >> 1) >= dd->n_krcv_queues)
		qpn = (qpn | qpt_mask) + 2;
	offset = qpn & RVT_BITS_PER_PAGE_MASK;
	map = &qpt->map[qpn / RVT_BITS_PER_PAGE];
	max_scan = qpt->nmaps - !offset;
	क्रम (i = 0;;) अणु
		अगर (unlikely(!map->page)) अणु
			get_map_page(qpt, map);
			अगर (unlikely(!map->page))
				अवरोध;
		पूर्ण
		करो अणु
			अगर (!test_and_set_bit(offset, map->page)) अणु
				qpt->last = qpn;
				ret = qpn;
				जाओ bail;
			पूर्ण
			offset = find_next_offset(qpt, map, offset,
				dd->n_krcv_queues, qpt_mask);
			qpn = mk_qpn(qpt, map, offset);
			/*
			 * This test dअगरfers from alloc_pidmap().
			 * If find_next_offset() करोes find a zero
			 * bit, we करोn't need to check क्रम QPN
			 * wrapping around past our starting QPN.
			 * We just need to be sure we करोn't loop
			 * क्रमever.
			 */
		पूर्ण जबतक (offset < RVT_BITS_PER_PAGE && qpn < RVT_QPN_MAX);
		/*
		 * In order to keep the number of pages allocated to a
		 * minimum, we scan the all existing pages beक्रमe increasing
		 * the size of the biपंचांगap table.
		 */
		अगर (++i > max_scan) अणु
			अगर (qpt->nmaps == RVT_QPNMAP_ENTRIES)
				अवरोध;
			map = &qpt->map[qpt->nmaps++];
			offset = 0;
		पूर्ण अन्यथा अगर (map < &qpt->map[qpt->nmaps]) अणु
			++map;
			offset = 0;
		पूर्ण अन्यथा अणु
			map = &qpt->map[0];
			offset = 2;
		पूर्ण
		qpn = mk_qpn(qpt, map, offset);
	पूर्ण

	ret = -ENOMEM;

bail:
	वापस ret;
पूर्ण

/*
 * qib_मुक्त_all_qps - check क्रम QPs still in use
 */
अचिन्हित qib_मुक्त_all_qps(काष्ठा rvt_dev_info *rdi)
अणु
	काष्ठा qib_ibdev *verbs_dev = container_of(rdi, काष्ठा qib_ibdev, rdi);
	काष्ठा qib_devdata *dd = container_of(verbs_dev, काष्ठा qib_devdata,
					      verbs_dev);
	अचिन्हित n, qp_inuse = 0;

	क्रम (n = 0; n < dd->num_pports; n++) अणु
		काष्ठा qib_ibport *ibp = &dd->pport[n].ibport_data;

		rcu_पढ़ो_lock();
		अगर (rcu_dereference(ibp->rvp.qp[0]))
			qp_inuse++;
		अगर (rcu_dereference(ibp->rvp.qp[1]))
			qp_inuse++;
		rcu_पढ़ो_unlock();
	पूर्ण
	वापस qp_inuse;
पूर्ण

व्योम qib_notअगरy_qp_reset(काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;

	atomic_set(&priv->s_dma_busy, 0);
पूर्ण

व्योम qib_notअगरy_error_qp(काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा qib_ibdev *dev = to_idev(qp->ibqp.device);

	spin_lock(&dev->rdi.pending_lock);
	अगर (!list_empty(&priv->ioरुको) && !(qp->s_flags & RVT_S_BUSY)) अणु
		qp->s_flags &= ~RVT_S_ANY_WAIT_IO;
		list_del_init(&priv->ioरुको);
	पूर्ण
	spin_unlock(&dev->rdi.pending_lock);

	अगर (!(qp->s_flags & RVT_S_BUSY)) अणु
		qp->s_hdrwords = 0;
		अगर (qp->s_rdma_mr) अणु
			rvt_put_mr(qp->s_rdma_mr);
			qp->s_rdma_mr = शून्य;
		पूर्ण
		अगर (priv->s_tx) अणु
			qib_put_txreq(priv->s_tx);
			priv->s_tx = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mtu_to_क्रमागत(u32 mtu)
अणु
	पूर्णांक क्रमागत_mtu;

	चयन (mtu) अणु
	हाल 4096:
		क्रमागत_mtu = IB_MTU_4096;
		अवरोध;
	हाल 2048:
		क्रमागत_mtu = IB_MTU_2048;
		अवरोध;
	हाल 1024:
		क्रमागत_mtu = IB_MTU_1024;
		अवरोध;
	हाल 512:
		क्रमागत_mtu = IB_MTU_512;
		अवरोध;
	हाल 256:
		क्रमागत_mtu = IB_MTU_256;
		अवरोध;
	शेष:
		क्रमागत_mtu = IB_MTU_2048;
	पूर्ण
	वापस क्रमागत_mtu;
पूर्ण

पूर्णांक qib_get_pmtu_from_attr(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
			   काष्ठा ib_qp_attr *attr)
अणु
	पूर्णांक mtu, pmtu, pidx = qp->port_num - 1;
	काष्ठा qib_ibdev *verbs_dev = container_of(rdi, काष्ठा qib_ibdev, rdi);
	काष्ठा qib_devdata *dd = container_of(verbs_dev, काष्ठा qib_devdata,
					      verbs_dev);
	mtu = ib_mtu_क्रमागत_to_पूर्णांक(attr->path_mtu);
	अगर (mtu == -1)
		वापस -EINVAL;

	अगर (mtu > dd->pport[pidx].ibmtu)
		pmtu = mtu_to_क्रमागत(dd->pport[pidx].ibmtu);
	अन्यथा
		pmtu = attr->path_mtu;
	वापस pmtu;
पूर्ण

पूर्णांक qib_mtu_to_path_mtu(u32 mtu)
अणु
	वापस mtu_to_क्रमागत(mtu);
पूर्ण

u32 qib_mtu_from_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp, u32 pmtu)
अणु
	वापस ib_mtu_क्रमागत_to_पूर्णांक(pmtu);
पूर्ण

व्योम *qib_qp_priv_alloc(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);
	priv->owner = qp;

	priv->s_hdr = kzalloc(माप(*priv->s_hdr), GFP_KERNEL);
	अगर (!priv->s_hdr) अणु
		kमुक्त(priv);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	init_रुकोqueue_head(&priv->रुको_dma);
	INIT_WORK(&priv->s_work, _qib_करो_send);
	INIT_LIST_HEAD(&priv->ioरुको);

	वापस priv;
पूर्ण

व्योम qib_qp_priv_मुक्त(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;

	kमुक्त(priv->s_hdr);
	kमुक्त(priv);
पूर्ण

व्योम qib_stop_send_queue(काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;

	cancel_work_sync(&priv->s_work);
पूर्ण

व्योम qib_quiesce_qp(काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;

	रुको_event(priv->रुको_dma, !atomic_पढ़ो(&priv->s_dma_busy));
	अगर (priv->s_tx) अणु
		qib_put_txreq(priv->s_tx);
		priv->s_tx = शून्य;
	पूर्ण
पूर्ण

व्योम qib_flush_qp_रुकोers(काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा qib_ibdev *dev = to_idev(qp->ibqp.device);

	spin_lock(&dev->rdi.pending_lock);
	अगर (!list_empty(&priv->ioरुको))
		list_del_init(&priv->ioरुको);
	spin_unlock(&dev->rdi.pending_lock);
पूर्ण

/**
 * qib_check_send_wqe - validate wr/wqe
 * @qp: The qp
 * @wqe: The built wqe
 * @call_send: Determine अगर the send should be posted or scheduled
 *
 * Returns 0 on success, -EINVAL on failure
 */
पूर्णांक qib_check_send_wqe(काष्ठा rvt_qp *qp,
		       काष्ठा rvt_swqe *wqe, bool *call_send)
अणु
	काष्ठा rvt_ah *ah;

	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_RC:
	हाल IB_QPT_UC:
		अगर (wqe->length > 0x80000000U)
			वापस -EINVAL;
		अगर (wqe->length > qp->pmtu)
			*call_send = false;
		अवरोध;
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
	हाल IB_QPT_UD:
		ah = rvt_get_swqe_ah(wqe);
		अगर (wqe->length > (1 << ah->log_pmtu))
			वापस -EINVAL;
		/* progress hपूर्णांक */
		*call_send = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

अटल स्थिर अक्षर * स्थिर qp_type_str[] = अणु
	"SMI", "GSI", "RC", "UC", "UD",
पूर्ण;

/**
 * qib_qp_iter_prपूर्णांक - prपूर्णांक inक्रमmation to seq_file
 * @s: the seq_file
 * @iter: the iterator
 */
व्योम qib_qp_iter_prपूर्णांक(काष्ठा seq_file *s, काष्ठा rvt_qp_iter *iter)
अणु
	काष्ठा rvt_swqe *wqe;
	काष्ठा rvt_qp *qp = iter->qp;
	काष्ठा qib_qp_priv *priv = qp->priv;

	wqe = rvt_get_swqe_ptr(qp, qp->s_last);
	seq_म_लिखो(s,
		   "N %d QP%u %s %u %u %u f=%x %u %u %u %u %u PSN %x %x %x %x %x (%u %u %u %u %u %u) QP%u LID %x\n",
		   iter->n,
		   qp->ibqp.qp_num,
		   qp_type_str[qp->ibqp.qp_type],
		   qp->state,
		   wqe->wr.opcode,
		   qp->s_hdrwords,
		   qp->s_flags,
		   atomic_पढ़ो(&priv->s_dma_busy),
		   !list_empty(&priv->ioरुको),
		   qp->समयout,
		   wqe->ssn,
		   qp->s_lsn,
		   qp->s_last_psn,
		   qp->s_psn, qp->s_next_psn,
		   qp->s_sending_psn, qp->s_sending_hpsn,
		   qp->s_last, qp->s_acked, qp->s_cur,
		   qp->s_tail, qp->s_head, qp->s_size,
		   qp->remote_qpn,
		   rdma_ah_get_dlid(&qp->remote_ah_attr));
पूर्ण

#पूर्ण_अगर
