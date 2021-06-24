<शैली गुरु>
/*
 * Copyright (c) 2006, 2020 Oracle and/or its affiliates.
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
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/list.h>
#समावेश <linux/errqueue.h>

#समावेश "rds.h"

अटल अचिन्हित पूर्णांक	rds_exthdr_size[__RDS_EXTHDR_MAX] = अणु
[RDS_EXTHDR_NONE]	= 0,
[RDS_EXTHDR_VERSION]	= माप(काष्ठा rds_ext_header_version),
[RDS_EXTHDR_RDMA]	= माप(काष्ठा rds_ext_header_rdma),
[RDS_EXTHDR_RDMA_DEST]	= माप(काष्ठा rds_ext_header_rdma_dest),
[RDS_EXTHDR_NPATHS]	= माप(u16),
[RDS_EXTHDR_GEN_NUM]	= माप(u32),
पूर्ण;

व्योम rds_message_addref(काष्ठा rds_message *rm)
अणु
	rdsdebug("addref rm %p ref %d\n", rm, refcount_पढ़ो(&rm->m_refcount));
	refcount_inc(&rm->m_refcount);
पूर्ण
EXPORT_SYMBOL_GPL(rds_message_addref);

अटल अंतरभूत bool rds_zcookie_add(काष्ठा rds_msg_zcopy_info *info, u32 cookie)
अणु
	काष्ठा rds_zcopy_cookies *ck = &info->zcookies;
	पूर्णांक ncookies = ck->num;

	अगर (ncookies == RDS_MAX_ZCOOKIES)
		वापस false;
	ck->cookies[ncookies] = cookie;
	ck->num =  ++ncookies;
	वापस true;
पूर्ण

अटल काष्ठा rds_msg_zcopy_info *rds_info_from_znotअगरier(काष्ठा rds_znotअगरier *znotअगर)
अणु
	वापस container_of(znotअगर, काष्ठा rds_msg_zcopy_info, znotअगर);
पूर्ण

व्योम rds_notअगरy_msg_zcopy_purge(काष्ठा rds_msg_zcopy_queue *q)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(copy);
	काष्ठा rds_msg_zcopy_info *info, *पंचांगp;

	spin_lock_irqsave(&q->lock, flags);
	list_splice(&q->zcookie_head, &copy);
	INIT_LIST_HEAD(&q->zcookie_head);
	spin_unlock_irqrestore(&q->lock, flags);

	list_क्रम_each_entry_safe(info, पंचांगp, &copy, rs_zcookie_next) अणु
		list_del(&info->rs_zcookie_next);
		kमुक्त(info);
	पूर्ण
पूर्ण

अटल व्योम rds_rm_zerocopy_callback(काष्ठा rds_sock *rs,
				     काष्ठा rds_znotअगरier *znotअगर)
अणु
	काष्ठा rds_msg_zcopy_info *info;
	काष्ठा rds_msg_zcopy_queue *q;
	u32 cookie = znotअगर->z_cookie;
	काष्ठा rds_zcopy_cookies *ck;
	काष्ठा list_head *head;
	अचिन्हित दीर्घ flags;

	mm_unaccount_pinned_pages(&znotअगर->z_mmp);
	q = &rs->rs_zcookie_queue;
	spin_lock_irqsave(&q->lock, flags);
	head = &q->zcookie_head;
	अगर (!list_empty(head)) अणु
		info = list_entry(head, काष्ठा rds_msg_zcopy_info,
				  rs_zcookie_next);
		अगर (info && rds_zcookie_add(info, cookie)) अणु
			spin_unlock_irqrestore(&q->lock, flags);
			kमुक्त(rds_info_from_znotअगरier(znotअगर));
			/* caller invokes rds_wake_sk_sleep() */
			वापस;
		पूर्ण
	पूर्ण

	info = rds_info_from_znotअगरier(znotअगर);
	ck = &info->zcookies;
	स_रखो(ck, 0, माप(*ck));
	WARN_ON(!rds_zcookie_add(info, cookie));
	list_add_tail(&q->zcookie_head, &info->rs_zcookie_next);

	spin_unlock_irqrestore(&q->lock, flags);
	/* caller invokes rds_wake_sk_sleep() */
पूर्ण

/*
 * This relies on dma_map_sg() not touching sg[].page during merging.
 */
अटल व्योम rds_message_purge(काष्ठा rds_message *rm)
अणु
	अचिन्हित दीर्घ i, flags;
	bool zcopy = false;

	अगर (unlikely(test_bit(RDS_MSG_PAGEVEC, &rm->m_flags)))
		वापस;

	spin_lock_irqsave(&rm->m_rs_lock, flags);
	अगर (rm->m_rs) अणु
		काष्ठा rds_sock *rs = rm->m_rs;

		अगर (rm->data.op_mmp_znotअगरier) अणु
			zcopy = true;
			rds_rm_zerocopy_callback(rs, rm->data.op_mmp_znotअगरier);
			rds_wake_sk_sleep(rs);
			rm->data.op_mmp_znotअगरier = शून्य;
		पूर्ण
		sock_put(rds_rs_to_sk(rs));
		rm->m_rs = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&rm->m_rs_lock, flags);

	क्रम (i = 0; i < rm->data.op_nents; i++) अणु
		/* XXX will have to put_page क्रम page refs */
		अगर (!zcopy)
			__मुक्त_page(sg_page(&rm->data.op_sg[i]));
		अन्यथा
			put_page(sg_page(&rm->data.op_sg[i]));
	पूर्ण
	rm->data.op_nents = 0;

	अगर (rm->rdma.op_active)
		rds_rdma_मुक्त_op(&rm->rdma);
	अगर (rm->rdma.op_rdma_mr)
		kref_put(&rm->rdma.op_rdma_mr->r_kref, __rds_put_mr_final);

	अगर (rm->atomic.op_active)
		rds_atomic_मुक्त_op(&rm->atomic);
	अगर (rm->atomic.op_rdma_mr)
		kref_put(&rm->atomic.op_rdma_mr->r_kref, __rds_put_mr_final);
पूर्ण

व्योम rds_message_put(काष्ठा rds_message *rm)
अणु
	rdsdebug("put rm %p ref %d\n", rm, refcount_पढ़ो(&rm->m_refcount));
	WARN(!refcount_पढ़ो(&rm->m_refcount), "danger refcount zero on %p\n", rm);
	अगर (refcount_dec_and_test(&rm->m_refcount)) अणु
		BUG_ON(!list_empty(&rm->m_sock_item));
		BUG_ON(!list_empty(&rm->m_conn_item));
		rds_message_purge(rm);

		kमुक्त(rm);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rds_message_put);

व्योम rds_message_populate_header(काष्ठा rds_header *hdr, __be16 sport,
				 __be16 dport, u64 seq)
अणु
	hdr->h_flags = 0;
	hdr->h_sport = sport;
	hdr->h_dport = dport;
	hdr->h_sequence = cpu_to_be64(seq);
	hdr->h_exthdr[0] = RDS_EXTHDR_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(rds_message_populate_header);

पूर्णांक rds_message_add_extension(काष्ठा rds_header *hdr, अचिन्हित पूर्णांक type,
			      स्थिर व्योम *data, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक ext_len = माप(u8) + len;
	अचिन्हित अक्षर *dst;

	/* For now, refuse to add more than one extension header */
	अगर (hdr->h_exthdr[0] != RDS_EXTHDR_NONE)
		वापस 0;

	अगर (type >= __RDS_EXTHDR_MAX || len != rds_exthdr_size[type])
		वापस 0;

	अगर (ext_len >= RDS_HEADER_EXT_SPACE)
		वापस 0;
	dst = hdr->h_exthdr;

	*dst++ = type;
	स_नकल(dst, data, len);

	dst[len] = RDS_EXTHDR_NONE;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(rds_message_add_extension);

/*
 * If a message has extension headers, retrieve them here.
 * Call like this:
 *
 * अचिन्हित पूर्णांक pos = 0;
 *
 * जबतक (1) अणु
 *	buflen = माप(buffer);
 *	type = rds_message_next_extension(hdr, &pos, buffer, &buflen);
 *	अगर (type == RDS_EXTHDR_NONE)
 *		अवरोध;
 *	...
 * पूर्ण
 */
पूर्णांक rds_message_next_extension(काष्ठा rds_header *hdr,
		अचिन्हित पूर्णांक *pos, व्योम *buf, अचिन्हित पूर्णांक *buflen)
अणु
	अचिन्हित पूर्णांक offset, ext_type, ext_len;
	u8 *src = hdr->h_exthdr;

	offset = *pos;
	अगर (offset >= RDS_HEADER_EXT_SPACE)
		जाओ none;

	/* Get the extension type and length. For now, the
	 * length is implied by the extension type. */
	ext_type = src[offset++];

	अगर (ext_type == RDS_EXTHDR_NONE || ext_type >= __RDS_EXTHDR_MAX)
		जाओ none;
	ext_len = rds_exthdr_size[ext_type];
	अगर (offset + ext_len > RDS_HEADER_EXT_SPACE)
		जाओ none;

	*pos = offset + ext_len;
	अगर (ext_len < *buflen)
		*buflen = ext_len;
	स_नकल(buf, src + offset, *buflen);
	वापस ext_type;

none:
	*pos = RDS_HEADER_EXT_SPACE;
	*buflen = 0;
	वापस RDS_EXTHDR_NONE;
पूर्ण

पूर्णांक rds_message_add_rdma_dest_extension(काष्ठा rds_header *hdr, u32 r_key, u32 offset)
अणु
	काष्ठा rds_ext_header_rdma_dest ext_hdr;

	ext_hdr.h_rdma_rkey = cpu_to_be32(r_key);
	ext_hdr.h_rdma_offset = cpu_to_be32(offset);
	वापस rds_message_add_extension(hdr, RDS_EXTHDR_RDMA_DEST, &ext_hdr, माप(ext_hdr));
पूर्ण
EXPORT_SYMBOL_GPL(rds_message_add_rdma_dest_extension);

/*
 * Each rds_message is allocated with extra space क्रम the scatterlist entries
 * rds ops will need. This is to minimize memory allocation count. Then, each rds op
 * can grab SGs when initializing its part of the rds_message.
 */
काष्ठा rds_message *rds_message_alloc(अचिन्हित पूर्णांक extra_len, gfp_t gfp)
अणु
	काष्ठा rds_message *rm;

	अगर (extra_len > KMALLOC_MAX_SIZE - माप(काष्ठा rds_message))
		वापस शून्य;

	rm = kzalloc(माप(काष्ठा rds_message) + extra_len, gfp);
	अगर (!rm)
		जाओ out;

	rm->m_used_sgs = 0;
	rm->m_total_sgs = extra_len / माप(काष्ठा scatterlist);

	refcount_set(&rm->m_refcount, 1);
	INIT_LIST_HEAD(&rm->m_sock_item);
	INIT_LIST_HEAD(&rm->m_conn_item);
	spin_lock_init(&rm->m_rs_lock);
	init_रुकोqueue_head(&rm->m_flush_रुको);

out:
	वापस rm;
पूर्ण

/*
 * RDS ops use this to grab SG entries from the rm's sg pool.
 */
काष्ठा scatterlist *rds_message_alloc_sgs(काष्ठा rds_message *rm, पूर्णांक nents)
अणु
	काष्ठा scatterlist *sg_first = (काष्ठा scatterlist *) &rm[1];
	काष्ठा scatterlist *sg_ret;

	अगर (nents <= 0) अणु
		pr_warn("rds: alloc sgs failed! nents <= 0\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (rm->m_used_sgs + nents > rm->m_total_sgs) अणु
		pr_warn("rds: alloc sgs failed! total %d used %d nents %d\n",
			rm->m_total_sgs, rm->m_used_sgs, nents);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	sg_ret = &sg_first[rm->m_used_sgs];
	sg_init_table(sg_ret, nents);
	rm->m_used_sgs += nents;

	वापस sg_ret;
पूर्ण

काष्ठा rds_message *rds_message_map_pages(अचिन्हित दीर्घ *page_addrs, अचिन्हित पूर्णांक total_len)
अणु
	काष्ठा rds_message *rm;
	अचिन्हित पूर्णांक i;
	पूर्णांक num_sgs = DIV_ROUND_UP(total_len, PAGE_SIZE);
	पूर्णांक extra_bytes = num_sgs * माप(काष्ठा scatterlist);

	rm = rds_message_alloc(extra_bytes, GFP_NOWAIT);
	अगर (!rm)
		वापस ERR_PTR(-ENOMEM);

	set_bit(RDS_MSG_PAGEVEC, &rm->m_flags);
	rm->m_inc.i_hdr.h_len = cpu_to_be32(total_len);
	rm->data.op_nents = DIV_ROUND_UP(total_len, PAGE_SIZE);
	rm->data.op_sg = rds_message_alloc_sgs(rm, num_sgs);
	अगर (IS_ERR(rm->data.op_sg)) अणु
		व्योम *err = ERR_CAST(rm->data.op_sg);
		rds_message_put(rm);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < rm->data.op_nents; ++i) अणु
		sg_set_page(&rm->data.op_sg[i],
				virt_to_page(page_addrs[i]),
				PAGE_SIZE, 0);
	पूर्ण

	वापस rm;
पूर्ण

अटल पूर्णांक rds_message_zcopy_from_user(काष्ठा rds_message *rm, काष्ठा iov_iter *from)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक ret = 0;
	पूर्णांक length = iov_iter_count(from);
	पूर्णांक total_copied = 0;
	काष्ठा rds_msg_zcopy_info *info;

	rm->m_inc.i_hdr.h_len = cpu_to_be32(iov_iter_count(from));

	/*
	 * now allocate and copy in the data payload.
	 */
	sg = rm->data.op_sg;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&info->rs_zcookie_next);
	rm->data.op_mmp_znotअगरier = &info->znotअगर;
	अगर (mm_account_pinned_pages(&rm->data.op_mmp_znotअगरier->z_mmp,
				    length)) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	जबतक (iov_iter_count(from)) अणु
		काष्ठा page *pages;
		माप_प्रकार start;
		sमाप_प्रकार copied;

		copied = iov_iter_get_pages(from, &pages, PAGE_SIZE,
					    1, &start);
		अगर (copied < 0) अणु
			काष्ठा mmpin *mmp;
			पूर्णांक i;

			क्रम (i = 0; i < rm->data.op_nents; i++)
				put_page(sg_page(&rm->data.op_sg[i]));
			mmp = &rm->data.op_mmp_znotअगरier->z_mmp;
			mm_unaccount_pinned_pages(mmp);
			ret = -EFAULT;
			जाओ err;
		पूर्ण
		total_copied += copied;
		iov_iter_advance(from, copied);
		length -= copied;
		sg_set_page(sg, pages, copied, start);
		rm->data.op_nents++;
		sg++;
	पूर्ण
	WARN_ON_ONCE(length != 0);
	वापस ret;
err:
	kमुक्त(info);
	rm->data.op_mmp_znotअगरier = शून्य;
	वापस ret;
पूर्ण

पूर्णांक rds_message_copy_from_user(काष्ठा rds_message *rm, काष्ठा iov_iter *from,
			       bool zcopy)
अणु
	अचिन्हित दीर्घ to_copy, nbytes;
	अचिन्हित दीर्घ sg_off;
	काष्ठा scatterlist *sg;
	पूर्णांक ret = 0;

	rm->m_inc.i_hdr.h_len = cpu_to_be32(iov_iter_count(from));

	/* now allocate and copy in the data payload.  */
	sg = rm->data.op_sg;
	sg_off = 0; /* Dear gcc, sg->page will be null from kzalloc. */

	अगर (zcopy)
		वापस rds_message_zcopy_from_user(rm, from);

	जबतक (iov_iter_count(from)) अणु
		अगर (!sg_page(sg)) अणु
			ret = rds_page_reमुख्यder_alloc(sg, iov_iter_count(from),
						       GFP_HIGHUSER);
			अगर (ret)
				वापस ret;
			rm->data.op_nents++;
			sg_off = 0;
		पूर्ण

		to_copy = min_t(अचिन्हित दीर्घ, iov_iter_count(from),
				sg->length - sg_off);

		rds_stats_add(s_copy_from_user, to_copy);
		nbytes = copy_page_from_iter(sg_page(sg), sg->offset + sg_off,
					     to_copy, from);
		अगर (nbytes != to_copy)
			वापस -EFAULT;

		sg_off += to_copy;

		अगर (sg_off == sg->length)
			sg++;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक rds_message_inc_copy_to_user(काष्ठा rds_incoming *inc, काष्ठा iov_iter *to)
अणु
	काष्ठा rds_message *rm;
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ to_copy;
	अचिन्हित दीर्घ vec_off;
	पूर्णांक copied;
	पूर्णांक ret;
	u32 len;

	rm = container_of(inc, काष्ठा rds_message, m_inc);
	len = be32_to_cpu(rm->m_inc.i_hdr.h_len);

	sg = rm->data.op_sg;
	vec_off = 0;
	copied = 0;

	जबतक (iov_iter_count(to) && copied < len) अणु
		to_copy = min_t(अचिन्हित दीर्घ, iov_iter_count(to),
				sg->length - vec_off);
		to_copy = min_t(अचिन्हित दीर्घ, to_copy, len - copied);

		rds_stats_add(s_copy_to_user, to_copy);
		ret = copy_page_to_iter(sg_page(sg), sg->offset + vec_off,
					to_copy, to);
		अगर (ret != to_copy)
			वापस -EFAULT;

		vec_off += to_copy;
		copied += to_copy;

		अगर (vec_off == sg->length) अणु
			vec_off = 0;
			sg++;
		पूर्ण
	पूर्ण

	वापस copied;
पूर्ण

/*
 * If the message is still on the send queue, रुको until the transport
 * is करोne with it. This is particularly important क्रम RDMA operations.
 */
व्योम rds_message_रुको(काष्ठा rds_message *rm)
अणु
	रुको_event_पूर्णांकerruptible(rm->m_flush_रुको,
			!test_bit(RDS_MSG_MAPPED, &rm->m_flags));
पूर्ण

व्योम rds_message_unmapped(काष्ठा rds_message *rm)
अणु
	clear_bit(RDS_MSG_MAPPED, &rm->m_flags);
	wake_up_पूर्णांकerruptible(&rm->m_flush_रुको);
पूर्ण
EXPORT_SYMBOL_GPL(rds_message_unmapped);
