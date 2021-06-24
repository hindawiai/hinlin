<शैली गुरु>
/*
 * Copyright(c) 2016 Intel Corporation.
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

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "srq.h"
#समावेश "vt.h"
#समावेश "qp.h"
/**
 * rvt_driver_srq_init - init srq resources on a per driver basis
 * @rdi: rvt dev काष्ठाure
 *
 * Do any initialization needed when a driver रेजिस्टरs with rdmavt.
 */
व्योम rvt_driver_srq_init(काष्ठा rvt_dev_info *rdi)
अणु
	spin_lock_init(&rdi->n_srqs_lock);
	rdi->n_srqs_allocated = 0;
पूर्ण

/**
 * rvt_create_srq - create a shared receive queue
 * @ibsrq: the protection करोमुख्य of the SRQ to create
 * @srq_init_attr: the attributes of the SRQ
 * @udata: data from libibverbs when creating a user SRQ
 *
 * Return: 0 on success
 */
पूर्णांक rvt_create_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_init_attr *srq_init_attr,
		   काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_dev_info *dev = ib_to_rvt(ibsrq->device);
	काष्ठा rvt_srq *srq = ibsrq_to_rvtsrq(ibsrq);
	u32 sz;
	पूर्णांक ret;

	अगर (srq_init_attr->srq_type != IB_SRQT_BASIC)
		वापस -EOPNOTSUPP;

	अगर (srq_init_attr->attr.max_sge == 0 ||
	    srq_init_attr->attr.max_sge > dev->dparms.props.max_srq_sge ||
	    srq_init_attr->attr.max_wr == 0 ||
	    srq_init_attr->attr.max_wr > dev->dparms.props.max_srq_wr)
		वापस -EINVAL;

	/*
	 * Need to use vदो_स्मृति() अगर we want to support large #s of entries.
	 */
	srq->rq.size = srq_init_attr->attr.max_wr + 1;
	srq->rq.max_sge = srq_init_attr->attr.max_sge;
	sz = माप(काष्ठा ib_sge) * srq->rq.max_sge +
		माप(काष्ठा rvt_rwqe);
	अगर (rvt_alloc_rq(&srq->rq, srq->rq.size * sz,
			 dev->dparms.node, udata)) अणु
		ret = -ENOMEM;
		जाओ bail_srq;
	पूर्ण

	/*
	 * Return the address of the RWQ as the offset to mmap.
	 * See rvt_mmap() क्रम details.
	 */
	अगर (udata && udata->outlen >= माप(__u64)) अणु
		u32 s = माप(काष्ठा rvt_rwq) + srq->rq.size * sz;

		srq->ip = rvt_create_mmap_info(dev, s, udata, srq->rq.wq);
		अगर (IS_ERR(srq->ip)) अणु
			ret = PTR_ERR(srq->ip);
			जाओ bail_wq;
		पूर्ण

		ret = ib_copy_to_udata(udata, &srq->ip->offset,
				       माप(srq->ip->offset));
		अगर (ret)
			जाओ bail_ip;
	पूर्ण

	/*
	 * ib_create_srq() will initialize srq->ibsrq.
	 */
	spin_lock_init(&srq->rq.lock);
	srq->limit = srq_init_attr->attr.srq_limit;

	spin_lock(&dev->n_srqs_lock);
	अगर (dev->n_srqs_allocated == dev->dparms.props.max_srq) अणु
		spin_unlock(&dev->n_srqs_lock);
		ret = -ENOMEM;
		जाओ bail_ip;
	पूर्ण

	dev->n_srqs_allocated++;
	spin_unlock(&dev->n_srqs_lock);

	अगर (srq->ip) अणु
		spin_lock_irq(&dev->pending_lock);
		list_add(&srq->ip->pending_mmaps, &dev->pending_mmaps);
		spin_unlock_irq(&dev->pending_lock);
	पूर्ण

	वापस 0;

bail_ip:
	kमुक्त(srq->ip);
bail_wq:
	rvt_मुक्त_rq(&srq->rq);
bail_srq:
	वापस ret;
पूर्ण

/**
 * rvt_modअगरy_srq - modअगरy a shared receive queue
 * @ibsrq: the SRQ to modअगरy
 * @attr: the new attributes of the SRQ
 * @attr_mask: indicates which attributes to modअगरy
 * @udata: user data क्रम libibverbs.so
 *
 * Return: 0 on success
 */
पूर्णांक rvt_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		   क्रमागत ib_srq_attr_mask attr_mask,
		   काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_srq *srq = ibsrq_to_rvtsrq(ibsrq);
	काष्ठा rvt_dev_info *dev = ib_to_rvt(ibsrq->device);
	काष्ठा rvt_rq पंचांगp_rq = अणुपूर्ण;
	पूर्णांक ret = 0;

	अगर (attr_mask & IB_SRQ_MAX_WR) अणु
		काष्ठा rvt_krwq *okwq = शून्य;
		काष्ठा rvt_rwq *owq = शून्य;
		काष्ठा rvt_rwqe *p;
		u32 sz, size, n, head, tail;

		/* Check that the requested sizes are below the limits. */
		अगर ((attr->max_wr > dev->dparms.props.max_srq_wr) ||
		    ((attr_mask & IB_SRQ_LIMIT) ?
		     attr->srq_limit : srq->limit) > attr->max_wr)
			वापस -EINVAL;
		sz = माप(काष्ठा rvt_rwqe) +
			srq->rq.max_sge * माप(काष्ठा ib_sge);
		size = attr->max_wr + 1;
		अगर (rvt_alloc_rq(&पंचांगp_rq, size * sz, dev->dparms.node,
				 udata))
			वापस -ENOMEM;
		/* Check that we can ग_लिखो the offset to mmap. */
		अगर (udata && udata->inlen >= माप(__u64)) अणु
			__u64 offset_addr;
			__u64 offset = 0;

			ret = ib_copy_from_udata(&offset_addr, udata,
						 माप(offset_addr));
			अगर (ret)
				जाओ bail_मुक्त;
			udata->outbuf = (व्योम __user *)
					(अचिन्हित दीर्घ)offset_addr;
			ret = ib_copy_to_udata(udata, &offset,
					       माप(offset));
			अगर (ret)
				जाओ bail_मुक्त;
		पूर्ण

		spin_lock_irq(&srq->rq.kwq->c_lock);
		/*
		 * validate head and tail poपूर्णांकer values and compute
		 * the number of reमुख्यing WQEs.
		 */
		अगर (udata) अणु
			owq = srq->rq.wq;
			head = RDMA_READ_UAPI_ATOMIC(owq->head);
			tail = RDMA_READ_UAPI_ATOMIC(owq->tail);
		पूर्ण अन्यथा अणु
			okwq = srq->rq.kwq;
			head = okwq->head;
			tail = okwq->tail;
		पूर्ण
		अगर (head >= srq->rq.size || tail >= srq->rq.size) अणु
			ret = -EINVAL;
			जाओ bail_unlock;
		पूर्ण
		n = head;
		अगर (n < tail)
			n += srq->rq.size - tail;
		अन्यथा
			n -= tail;
		अगर (size <= n) अणु
			ret = -EINVAL;
			जाओ bail_unlock;
		पूर्ण
		n = 0;
		p = पंचांगp_rq.kwq->curr_wq;
		जबतक (tail != head) अणु
			काष्ठा rvt_rwqe *wqe;
			पूर्णांक i;

			wqe = rvt_get_rwqe_ptr(&srq->rq, tail);
			p->wr_id = wqe->wr_id;
			p->num_sge = wqe->num_sge;
			क्रम (i = 0; i < wqe->num_sge; i++)
				p->sg_list[i] = wqe->sg_list[i];
			n++;
			p = (काष्ठा rvt_rwqe *)((अक्षर *)p + sz);
			अगर (++tail >= srq->rq.size)
				tail = 0;
		पूर्ण
		srq->rq.kwq = पंचांगp_rq.kwq;
		अगर (udata) अणु
			srq->rq.wq = पंचांगp_rq.wq;
			RDMA_WRITE_UAPI_ATOMIC(पंचांगp_rq.wq->head, n);
			RDMA_WRITE_UAPI_ATOMIC(पंचांगp_rq.wq->tail, 0);
		पूर्ण अन्यथा अणु
			पंचांगp_rq.kwq->head = n;
			पंचांगp_rq.kwq->tail = 0;
		पूर्ण
		srq->rq.size = size;
		अगर (attr_mask & IB_SRQ_LIMIT)
			srq->limit = attr->srq_limit;
		spin_unlock_irq(&srq->rq.kwq->c_lock);

		vमुक्त(owq);
		kvमुक्त(okwq);

		अगर (srq->ip) अणु
			काष्ठा rvt_mmap_info *ip = srq->ip;
			काष्ठा rvt_dev_info *dev = ib_to_rvt(srq->ibsrq.device);
			u32 s = माप(काष्ठा rvt_rwq) + size * sz;

			rvt_update_mmap_info(dev, ip, s, पंचांगp_rq.wq);

			/*
			 * Return the offset to mmap.
			 * See rvt_mmap() क्रम details.
			 */
			अगर (udata && udata->inlen >= माप(__u64)) अणु
				ret = ib_copy_to_udata(udata, &ip->offset,
						       माप(ip->offset));
				अगर (ret)
					वापस ret;
			पूर्ण

			/*
			 * Put user mapping info onto the pending list
			 * unless it alपढ़ोy is on the list.
			 */
			spin_lock_irq(&dev->pending_lock);
			अगर (list_empty(&ip->pending_mmaps))
				list_add(&ip->pending_mmaps,
					 &dev->pending_mmaps);
			spin_unlock_irq(&dev->pending_lock);
		पूर्ण
	पूर्ण अन्यथा अगर (attr_mask & IB_SRQ_LIMIT) अणु
		spin_lock_irq(&srq->rq.kwq->c_lock);
		अगर (attr->srq_limit >= srq->rq.size)
			ret = -EINVAL;
		अन्यथा
			srq->limit = attr->srq_limit;
		spin_unlock_irq(&srq->rq.kwq->c_lock);
	पूर्ण
	वापस ret;

bail_unlock:
	spin_unlock_irq(&srq->rq.kwq->c_lock);
bail_मुक्त:
	rvt_मुक्त_rq(&पंचांगp_rq);
	वापस ret;
पूर्ण

/**
 * rvt_query_srq - query srq data
 * @ibsrq: srq to query
 * @attr: वापस info in attr
 *
 * Return: always 0
 */
पूर्णांक rvt_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr)
अणु
	काष्ठा rvt_srq *srq = ibsrq_to_rvtsrq(ibsrq);

	attr->max_wr = srq->rq.size - 1;
	attr->max_sge = srq->rq.max_sge;
	attr->srq_limit = srq->limit;
	वापस 0;
पूर्ण

/**
 * rvt_destroy_srq - destory an srq
 * @ibsrq: srq object to destroy
 * @udata: user data क्रम libibverbs.so
 */
पूर्णांक rvt_destroy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_srq *srq = ibsrq_to_rvtsrq(ibsrq);
	काष्ठा rvt_dev_info *dev = ib_to_rvt(ibsrq->device);

	spin_lock(&dev->n_srqs_lock);
	dev->n_srqs_allocated--;
	spin_unlock(&dev->n_srqs_lock);
	अगर (srq->ip)
		kref_put(&srq->ip->ref, rvt_release_mmap_info);
	kvमुक्त(srq->rq.kwq);
	वापस 0;
पूर्ण
