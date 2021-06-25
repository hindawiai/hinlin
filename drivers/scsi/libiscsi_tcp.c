<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * iSCSI over TCP/IP Data-Path lib
 *
 * Copyright (C) 2004 Dmitry Yusupov
 * Copyright (C) 2004 Alex Aizman
 * Copyright (C) 2005 - 2006 Mike Christie
 * Copyright (C) 2006 Red Hat, Inc.  All rights reserved.
 * मुख्यtained by खोलो-iscsi@googlegroups.com
 *
 * Credits:
 *	Christoph Hellwig
 *	FUJITA Tomonori
 *	Arne Redlich
 *	Zhenyu Wang
 */

#समावेश <crypto/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/inet.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/module.h>
#समावेश <net/tcp.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_transport_iscsi.h>
#समावेश <trace/events/iscsi.h>

#समावेश "iscsi_tcp.h"

MODULE_AUTHOR("Mike Christie <michaelc@cs.wisc.edu>, "
	      "Dmitry Yusupov <dmitry_yus@yahoo.com>, "
	      "Alex Aizman <itn780@yahoo.com>");
MODULE_DESCRIPTION("iSCSI/TCP data-path");
MODULE_LICENSE("GPL");

अटल पूर्णांक iscsi_dbg_libtcp;
module_param_named(debug_libiscsi_tcp, iscsi_dbg_libtcp, पूर्णांक,
		   S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_libiscsi_tcp, "Turn on debugging for libiscsi_tcp "
		 "module. Set to 1 to turn on, and zero to turn off. Default "
		 "is off.");

#घोषणा ISCSI_DBG_TCP(_conn, dbg_fmt, arg...)			\
	करो अणु							\
		अगर (iscsi_dbg_libtcp)				\
			iscsi_conn_prपूर्णांकk(KERN_INFO, _conn,	\
					     "%s " dbg_fmt,	\
					     __func__, ##arg);	\
		iscsi_dbg_trace(trace_iscsi_dbg_tcp,		\
				&(_conn)->cls_conn->dev,	\
				"%s " dbg_fmt, __func__, ##arg);\
	पूर्ण जबतक (0);

अटल पूर्णांक iscsi_tcp_hdr_recv_करोne(काष्ठा iscsi_tcp_conn *tcp_conn,
				   काष्ठा iscsi_segment *segment);

/*
 * Scatterlist handling: inside the iscsi_segment, we
 * remember an index पूर्णांकo the scatterlist, and set data/size
 * to the current scatterlist entry. For highmem pages, we
 * kmap as needed.
 *
 * Note that the page is unmapped when we वापस from
 * TCP's data_पढ़ोy handler, so we may end up mapping and
 * unmapping the same page repeatedly. The whole reason
 * क्रम this is that we shouldn't keep the page mapped
 * outside the softirq.
 */

/**
 * iscsi_tcp_segment_init_sg - init indicated scatterlist entry
 * @segment: the buffer object
 * @sg: scatterlist
 * @offset: byte offset पूर्णांकo that sg entry
 *
 * This function sets up the segment so that subsequent
 * data is copied to the indicated sg entry, at the given
 * offset.
 */
अटल अंतरभूत व्योम
iscsi_tcp_segment_init_sg(काष्ठा iscsi_segment *segment,
			  काष्ठा scatterlist *sg, अचिन्हित पूर्णांक offset)
अणु
	segment->sg = sg;
	segment->sg_offset = offset;
	segment->size = min(sg->length - offset,
			    segment->total_size - segment->total_copied);
	segment->data = शून्य;
पूर्ण

/**
 * iscsi_tcp_segment_map - map the current S/G page
 * @segment: iscsi_segment
 * @recv: 1 अगर called from recv path
 *
 * We only need to possibly kmap data अगर scatter lists are being used,
 * because the iscsi passthrough and पूर्णांकernal IO paths will never use high
 * mem pages.
 */
अटल व्योम iscsi_tcp_segment_map(काष्ठा iscsi_segment *segment, पूर्णांक recv)
अणु
	काष्ठा scatterlist *sg;

	अगर (segment->data != शून्य || !segment->sg)
		वापस;

	sg = segment->sg;
	BUG_ON(segment->sg_mapped);
	BUG_ON(sg->length == 0);

	/*
	 * We always map क्रम the recv path.
	 *
	 * If the page count is greater than one it is ok to send
	 * to the network layer's zero copy send path. If not we
	 * have to go the slow sendmsg path.
	 *
	 * Same goes क्रम slab pages: skb_can_coalesce() allows
	 * coalescing neighboring slab objects पूर्णांकo a single frag which
	 * triggers one of hardened usercopy checks.
	 */
	अगर (!recv && sendpage_ok(sg_page(sg)))
		वापस;

	अगर (recv) अणु
		segment->atomic_mapped = true;
		segment->sg_mapped = kmap_atomic(sg_page(sg));
	पूर्ण अन्यथा अणु
		segment->atomic_mapped = false;
		/* the xmit path can sleep with the page mapped so use kmap */
		segment->sg_mapped = kmap(sg_page(sg));
	पूर्ण

	segment->data = segment->sg_mapped + sg->offset + segment->sg_offset;
पूर्ण

व्योम iscsi_tcp_segment_unmap(काष्ठा iscsi_segment *segment)
अणु
	अगर (segment->sg_mapped) अणु
		अगर (segment->atomic_mapped)
			kunmap_atomic(segment->sg_mapped);
		अन्यथा
			kunmap(sg_page(segment->sg));
		segment->sg_mapped = शून्य;
		segment->data = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_segment_unmap);

/*
 * Splice the digest buffer पूर्णांकo the buffer
 */
अटल अंतरभूत व्योम
iscsi_tcp_segment_splice_digest(काष्ठा iscsi_segment *segment, व्योम *digest)
अणु
	segment->data = digest;
	segment->digest_len = ISCSI_DIGEST_SIZE;
	segment->total_size += ISCSI_DIGEST_SIZE;
	segment->size = ISCSI_DIGEST_SIZE;
	segment->copied = 0;
	segment->sg = शून्य;
	segment->hash = शून्य;
पूर्ण

/**
 * iscsi_tcp_segment_करोne - check whether the segment is complete
 * @tcp_conn: iscsi tcp connection
 * @segment: iscsi segment to check
 * @recv: set to one of this is called from the recv path
 * @copied: number of bytes copied
 *
 * Check अगर we're करोne receiving this segment. If the receive
 * buffer is full but we expect more data, move on to the
 * next entry in the scatterlist.
 *
 * If the amount of data we received isn't a multiple of 4,
 * we will transparently receive the pad bytes, too.
 *
 * This function must be re-entrant.
 */
पूर्णांक iscsi_tcp_segment_करोne(काष्ठा iscsi_tcp_conn *tcp_conn,
			   काष्ठा iscsi_segment *segment, पूर्णांक recv,
			   अचिन्हित copied)
अणु
	काष्ठा scatterlist sg;
	अचिन्हित पूर्णांक pad;

	ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "copied %u %u size %u %s\n",
		      segment->copied, copied, segment->size,
		      recv ? "recv" : "xmit");
	अगर (segment->hash && copied) अणु
		/*
		 * If a segment is kmapd we must unmap it beक्रमe sending
		 * to the crypto layer since that will try to kmap it again.
		 */
		iscsi_tcp_segment_unmap(segment);

		अगर (!segment->data) अणु
			sg_init_table(&sg, 1);
			sg_set_page(&sg, sg_page(segment->sg), copied,
				    segment->copied + segment->sg_offset +
							segment->sg->offset);
		पूर्ण अन्यथा
			sg_init_one(&sg, segment->data + segment->copied,
				    copied);
		ahash_request_set_crypt(segment->hash, &sg, शून्य, copied);
		crypto_ahash_update(segment->hash);
	पूर्ण

	segment->copied += copied;
	अगर (segment->copied < segment->size) अणु
		iscsi_tcp_segment_map(segment, recv);
		वापस 0;
	पूर्ण

	segment->total_copied += segment->copied;
	segment->copied = 0;
	segment->size = 0;

	/* Unmap the current scatterlist page, अगर there is one. */
	iscsi_tcp_segment_unmap(segment);

	/* Do we have more scatterlist entries? */
	ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "total copied %u total size %u\n",
		      segment->total_copied, segment->total_size);
	अगर (segment->total_copied < segment->total_size) अणु
		/* Proceed to the next entry in the scatterlist. */
		iscsi_tcp_segment_init_sg(segment, sg_next(segment->sg),
					  0);
		iscsi_tcp_segment_map(segment, recv);
		BUG_ON(segment->size == 0);
		वापस 0;
	पूर्ण

	/* Do we need to handle padding? */
	अगर (!(tcp_conn->iscsi_conn->session->tt->caps & CAP_PADDING_OFFLOAD)) अणु
		pad = iscsi_padding(segment->total_copied);
		अगर (pad != 0) अणु
			ISCSI_DBG_TCP(tcp_conn->iscsi_conn,
				      "consume %d pad bytes\n", pad);
			segment->total_size += pad;
			segment->size = pad;
			segment->data = segment->padbuf;
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Set us up क्रम transferring the data digest. hdr digest
	 * is completely handled in hdr करोne function.
	 */
	अगर (segment->hash) अणु
		ahash_request_set_crypt(segment->hash, शून्य,
					segment->digest, 0);
		crypto_ahash_final(segment->hash);
		iscsi_tcp_segment_splice_digest(segment,
				 recv ? segment->recv_digest : segment->digest);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_segment_करोne);

/**
 * iscsi_tcp_segment_recv - copy data to segment
 * @tcp_conn: the iSCSI TCP connection
 * @segment: the buffer to copy to
 * @ptr: data poपूर्णांकer
 * @len: amount of data available
 *
 * This function copies up to @len bytes to the
 * given buffer, and वापसs the number of bytes
 * consumed, which can actually be less than @len.
 *
 * If hash digest is enabled, the function will update the
 * hash जबतक copying.
 * Combining these two operations करोesn't buy us a lot (yet),
 * but in the future we could implement combined copy+crc,
 * just way we करो क्रम network layer checksums.
 */
अटल पूर्णांक
iscsi_tcp_segment_recv(काष्ठा iscsi_tcp_conn *tcp_conn,
		       काष्ठा iscsi_segment *segment, स्थिर व्योम *ptr,
		       अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक copy = 0, copied = 0;

	जबतक (!iscsi_tcp_segment_करोne(tcp_conn, segment, 1, copy)) अणु
		अगर (copied == len) अणु
			ISCSI_DBG_TCP(tcp_conn->iscsi_conn,
				      "copied %d bytes\n", len);
			अवरोध;
		पूर्ण

		copy = min(len - copied, segment->size - segment->copied);
		ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "copying %d\n", copy);
		स_नकल(segment->data + segment->copied, ptr + copied, copy);
		copied += copy;
	पूर्ण
	वापस copied;
पूर्ण

अंतरभूत व्योम
iscsi_tcp_dgst_header(काष्ठा ahash_request *hash, स्थिर व्योम *hdr,
		      माप_प्रकार hdrlen, अचिन्हित अक्षर digest[ISCSI_DIGEST_SIZE])
अणु
	काष्ठा scatterlist sg;

	sg_init_one(&sg, hdr, hdrlen);
	ahash_request_set_crypt(hash, &sg, digest, hdrlen);
	crypto_ahash_digest(hash);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_dgst_header);

अटल अंतरभूत पूर्णांक
iscsi_tcp_dgst_verअगरy(काष्ठा iscsi_tcp_conn *tcp_conn,
		      काष्ठा iscsi_segment *segment)
अणु
	अगर (!segment->digest_len)
		वापस 1;

	अगर (स_भेद(segment->recv_digest, segment->digest,
		   segment->digest_len)) अणु
		ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "digest mismatch\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Helper function to set up segment buffer
 */
अटल अंतरभूत व्योम
__iscsi_segment_init(काष्ठा iscsi_segment *segment, माप_प्रकार size,
		     iscsi_segment_करोne_fn_t *करोne, काष्ठा ahash_request *hash)
अणु
	स_रखो(segment, 0, माप(*segment));
	segment->total_size = size;
	segment->करोne = करोne;

	अगर (hash) अणु
		segment->hash = hash;
		crypto_ahash_init(hash);
	पूर्ण
पूर्ण

अंतरभूत व्योम
iscsi_segment_init_linear(काष्ठा iscsi_segment *segment, व्योम *data,
			  माप_प्रकार size, iscsi_segment_करोne_fn_t *करोne,
			  काष्ठा ahash_request *hash)
अणु
	__iscsi_segment_init(segment, size, करोne, hash);
	segment->data = data;
	segment->size = size;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_segment_init_linear);

अंतरभूत पूर्णांक
iscsi_segment_seek_sg(काष्ठा iscsi_segment *segment,
		      काष्ठा scatterlist *sg_list, अचिन्हित पूर्णांक sg_count,
		      अचिन्हित पूर्णांक offset, माप_प्रकार size,
		      iscsi_segment_करोne_fn_t *करोne,
		      काष्ठा ahash_request *hash)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	__iscsi_segment_init(segment, size, करोne, hash);
	क्रम_each_sg(sg_list, sg, sg_count, i) अणु
		अगर (offset < sg->length) अणु
			iscsi_tcp_segment_init_sg(segment, sg, offset);
			वापस 0;
		पूर्ण
		offset -= sg->length;
	पूर्ण

	वापस ISCSI_ERR_DATA_OFFSET;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_segment_seek_sg);

/**
 * iscsi_tcp_hdr_recv_prep - prep segment क्रम hdr reception
 * @tcp_conn: iscsi connection to prep क्रम
 *
 * This function always passes शून्य क्रम the hash argument, because when this
 * function is called we करो not yet know the final size of the header and want
 * to delay the digest processing until we know that.
 */
व्योम iscsi_tcp_hdr_recv_prep(काष्ठा iscsi_tcp_conn *tcp_conn)
अणु
	ISCSI_DBG_TCP(tcp_conn->iscsi_conn,
		      "(%s)\n", tcp_conn->iscsi_conn->hdrdgst_en ?
		      "digest enabled" : "digest disabled");
	iscsi_segment_init_linear(&tcp_conn->in.segment,
				tcp_conn->in.hdr_buf, माप(काष्ठा iscsi_hdr),
				iscsi_tcp_hdr_recv_करोne, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_hdr_recv_prep);

/*
 * Handle incoming reply to any other type of command
 */
अटल पूर्णांक
iscsi_tcp_data_recv_करोne(काष्ठा iscsi_tcp_conn *tcp_conn,
			 काष्ठा iscsi_segment *segment)
अणु
	काष्ठा iscsi_conn *conn = tcp_conn->iscsi_conn;
	पूर्णांक rc = 0;

	अगर (!iscsi_tcp_dgst_verअगरy(tcp_conn, segment))
		वापस ISCSI_ERR_DATA_DGST;

	rc = iscsi_complete_pdu(conn, tcp_conn->in.hdr,
			conn->data, tcp_conn->in.datalen);
	अगर (rc)
		वापस rc;

	iscsi_tcp_hdr_recv_prep(tcp_conn);
	वापस 0;
पूर्ण

अटल व्योम
iscsi_tcp_data_recv_prep(काष्ठा iscsi_tcp_conn *tcp_conn)
अणु
	काष्ठा iscsi_conn *conn = tcp_conn->iscsi_conn;
	काष्ठा ahash_request *rx_hash = शून्य;

	अगर (conn->datadgst_en &&
	    !(conn->session->tt->caps & CAP_DIGEST_OFFLOAD))
		rx_hash = tcp_conn->rx_hash;

	iscsi_segment_init_linear(&tcp_conn->in.segment,
				conn->data, tcp_conn->in.datalen,
				iscsi_tcp_data_recv_करोne, rx_hash);
पूर्ण

/**
 * iscsi_tcp_cleanup_task - मुक्त tcp_task resources
 * @task: iscsi task
 *
 * must be called with session back_lock
 */
व्योम iscsi_tcp_cleanup_task(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
	काष्ठा iscsi_r2t_info *r2t;

	/* nothing to करो क्रम mgmt */
	अगर (!task->sc)
		वापस;

	spin_lock_bh(&tcp_task->queue2pool);
	/* flush task's r2t queues */
	जबतक (kfअगरo_out(&tcp_task->r2tqueue, (व्योम*)&r2t, माप(व्योम*))) अणु
		kfअगरo_in(&tcp_task->r2tpool.queue, (व्योम*)&r2t,
			    माप(व्योम*));
		ISCSI_DBG_TCP(task->conn, "pending r2t dropped\n");
	पूर्ण

	r2t = tcp_task->r2t;
	अगर (r2t != शून्य) अणु
		kfअगरo_in(&tcp_task->r2tpool.queue, (व्योम*)&r2t,
			    माप(व्योम*));
		tcp_task->r2t = शून्य;
	पूर्ण
	spin_unlock_bh(&tcp_task->queue2pool);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_cleanup_task);

/**
 * iscsi_tcp_data_in - SCSI Data-In Response processing
 * @conn: iscsi connection
 * @task: scsi command task
 */
अटल पूर्णांक iscsi_tcp_data_in(काष्ठा iscsi_conn *conn, काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
	काष्ठा iscsi_data_rsp *rhdr = (काष्ठा iscsi_data_rsp *)tcp_conn->in.hdr;
	पूर्णांक datasn = be32_to_cpu(rhdr->datasn);
	अचिन्हित total_in_length = task->sc->sdb.length;

	/*
	 * lib iscsi will update this in the completion handling अगर there
	 * is status.
	 */
	अगर (!(rhdr->flags & ISCSI_FLAG_DATA_STATUS))
		iscsi_update_cmdsn(conn->session, (काष्ठा iscsi_nopin*)rhdr);

	अगर (tcp_conn->in.datalen == 0)
		वापस 0;

	अगर (tcp_task->exp_datasn != datasn) अणु
		ISCSI_DBG_TCP(conn, "task->exp_datasn(%d) != rhdr->datasn(%d)"
			      "\n", tcp_task->exp_datasn, datasn);
		वापस ISCSI_ERR_DATASN;
	पूर्ण

	tcp_task->exp_datasn++;

	tcp_task->data_offset = be32_to_cpu(rhdr->offset);
	अगर (tcp_task->data_offset + tcp_conn->in.datalen > total_in_length) अणु
		ISCSI_DBG_TCP(conn, "data_offset(%d) + data_len(%d) > "
			      "total_length_in(%d)\n", tcp_task->data_offset,
			      tcp_conn->in.datalen, total_in_length);
		वापस ISCSI_ERR_DATA_OFFSET;
	पूर्ण

	conn->datain_pdus_cnt++;
	वापस 0;
पूर्ण

/**
 * iscsi_tcp_r2t_rsp - iSCSI R2T Response processing
 * @conn: iscsi connection
 * @hdr: PDU header
 */
अटल पूर्णांक iscsi_tcp_r2t_rsp(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr)
अणु
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा iscsi_tcp_task *tcp_task;
	काष्ठा iscsi_tcp_conn *tcp_conn;
	काष्ठा iscsi_r2t_rsp *rhdr;
	काष्ठा iscsi_r2t_info *r2t;
	काष्ठा iscsi_task *task;
	u32 data_length;
	u32 data_offset;
	पूर्णांक r2tsn;
	पूर्णांक rc;

	spin_lock(&session->back_lock);
	task = iscsi_itt_to_ctask(conn, hdr->itt);
	अगर (!task) अणु
		spin_unlock(&session->back_lock);
		वापस ISCSI_ERR_BAD_ITT;
	पूर्ण अन्यथा अगर (task->sc->sc_data_direction != DMA_TO_DEVICE) अणु
		spin_unlock(&session->back_lock);
		वापस ISCSI_ERR_PROTO;
	पूर्ण
	/*
	 * A bad target might complete the cmd beक्रमe we have handled R2Ts
	 * so get a ref to the task that will be dropped in the xmit path.
	 */
	अगर (task->state != ISCSI_TASK_RUNNING) अणु
		spin_unlock(&session->back_lock);
		/* Let the path that got the early rsp complete it */
		वापस 0;
	पूर्ण
	task->last_xfer = jअगरfies;
	__iscsi_get_task(task);

	tcp_conn = conn->dd_data;
	rhdr = (काष्ठा iscsi_r2t_rsp *)tcp_conn->in.hdr;
	/* fill-in new R2T associated with the task */
	iscsi_update_cmdsn(session, (काष्ठा iscsi_nopin *)rhdr);
	spin_unlock(&session->back_lock);

	अगर (tcp_conn->in.datalen) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "invalid R2t with datalen %d\n",
				  tcp_conn->in.datalen);
		rc = ISCSI_ERR_DATALEN;
		जाओ put_task;
	पूर्ण

	tcp_task = task->dd_data;
	r2tsn = be32_to_cpu(rhdr->r2tsn);
	अगर (tcp_task->exp_datasn != r2tsn)अणु
		ISCSI_DBG_TCP(conn, "task->exp_datasn(%d) != rhdr->r2tsn(%d)\n",
			      tcp_task->exp_datasn, r2tsn);
		rc = ISCSI_ERR_R2TSN;
		जाओ put_task;
	पूर्ण

	अगर (session->state != ISCSI_STATE_LOGGED_IN) अणु
		iscsi_conn_prपूर्णांकk(KERN_INFO, conn,
				  "dropping R2T itt %d in recovery.\n",
				  task->itt);
		rc = 0;
		जाओ put_task;
	पूर्ण

	data_length = be32_to_cpu(rhdr->data_length);
	अगर (data_length == 0) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "invalid R2T with zero data len\n");
		rc = ISCSI_ERR_DATALEN;
		जाओ put_task;
	पूर्ण

	अगर (data_length > session->max_burst)
		ISCSI_DBG_TCP(conn, "invalid R2T with data len %u and max "
			      "burst %u. Attempting to execute request.\n",
			      data_length, session->max_burst);

	data_offset = be32_to_cpu(rhdr->data_offset);
	अगर (data_offset + data_length > task->sc->sdb.length) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "invalid R2T with data len %u at offset %u "
				  "and total length %d\n", data_length,
				  data_offset, task->sc->sdb.length);
		rc = ISCSI_ERR_DATALEN;
		जाओ put_task;
	पूर्ण

	spin_lock(&tcp_task->pool2queue);
	rc = kfअगरo_out(&tcp_task->r2tpool.queue, (व्योम *)&r2t, माप(व्योम *));
	अगर (!rc) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "Could not allocate R2T. "
				  "Target has sent more R2Ts than it "
				  "negotiated for or driver has leaked.\n");
		spin_unlock(&tcp_task->pool2queue);
		rc = ISCSI_ERR_PROTO;
		जाओ put_task;
	पूर्ण

	r2t->exp_statsn = rhdr->statsn;
	r2t->data_length = data_length;
	r2t->data_offset = data_offset;

	r2t->ttt = rhdr->ttt; /* no flip */
	r2t->datasn = 0;
	r2t->sent = 0;

	tcp_task->exp_datasn = r2tsn + 1;
	kfअगरo_in(&tcp_task->r2tqueue, (व्योम*)&r2t, माप(व्योम*));
	conn->r2t_pdus_cnt++;
	spin_unlock(&tcp_task->pool2queue);

	iscsi_requeue_task(task);
	वापस 0;

put_task:
	iscsi_put_task(task);
	वापस rc;
पूर्ण

/*
 * Handle incoming reply to DataIn command
 */
अटल पूर्णांक
iscsi_tcp_process_data_in(काष्ठा iscsi_tcp_conn *tcp_conn,
			  काष्ठा iscsi_segment *segment)
अणु
	काष्ठा iscsi_conn *conn = tcp_conn->iscsi_conn;
	काष्ठा iscsi_hdr *hdr = tcp_conn->in.hdr;
	पूर्णांक rc;

	अगर (!iscsi_tcp_dgst_verअगरy(tcp_conn, segment))
		वापस ISCSI_ERR_DATA_DGST;

	/* check क्रम non-exceptional status */
	अगर (hdr->flags & ISCSI_FLAG_DATA_STATUS) अणु
		rc = iscsi_complete_pdu(conn, tcp_conn->in.hdr, शून्य, 0);
		अगर (rc)
			वापस rc;
	पूर्ण

	iscsi_tcp_hdr_recv_prep(tcp_conn);
	वापस 0;
पूर्ण

/**
 * iscsi_tcp_hdr_dissect - process PDU header
 * @conn: iSCSI connection
 * @hdr: PDU header
 *
 * This function analyzes the header of the PDU received,
 * and perक्रमms several sanity checks. If the PDU is accompanied
 * by data, the receive buffer is set up to copy the incoming data
 * to the correct location.
 */
अटल पूर्णांक
iscsi_tcp_hdr_dissect(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr)
अणु
	पूर्णांक rc = 0, opcode, ahslen;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_task *task;

	/* verअगरy PDU length */
	tcp_conn->in.datalen = ntoh24(hdr->dlength);
	अगर (tcp_conn->in.datalen > conn->max_recv_dlength) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "iscsi_tcp: datalen %d > %d\n",
				  tcp_conn->in.datalen, conn->max_recv_dlength);
		वापस ISCSI_ERR_DATALEN;
	पूर्ण

	/* Additional header segments. So far, we करोn't
	 * process additional headers.
	 */
	ahslen = hdr->hlength << 2;

	opcode = hdr->opcode & ISCSI_OPCODE_MASK;
	/* verअगरy itt (itt encoding: age+cid+itt) */
	rc = iscsi_verअगरy_itt(conn, hdr->itt);
	अगर (rc)
		वापस rc;

	ISCSI_DBG_TCP(conn, "opcode 0x%x ahslen %d datalen %d\n",
		      opcode, ahslen, tcp_conn->in.datalen);

	चयन(opcode) अणु
	हाल ISCSI_OP_SCSI_DATA_IN:
		spin_lock(&conn->session->back_lock);
		task = iscsi_itt_to_ctask(conn, hdr->itt);
		अगर (!task)
			rc = ISCSI_ERR_BAD_ITT;
		अन्यथा
			rc = iscsi_tcp_data_in(conn, task);
		अगर (rc) अणु
			spin_unlock(&conn->session->back_lock);
			अवरोध;
		पूर्ण

		अगर (tcp_conn->in.datalen) अणु
			काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
			काष्ठा ahash_request *rx_hash = शून्य;
			काष्ठा scsi_data_buffer *sdb = &task->sc->sdb;

			/*
			 * Setup copy of Data-In पूर्णांकo the काष्ठा scsi_cmnd
			 * Scatterlist हाल:
			 * We set up the iscsi_segment to poपूर्णांक to the next
			 * scatterlist entry to copy to. As we go aदीर्घ,
			 * we move on to the next scatterlist entry and
			 * update the digest per-entry.
			 */
			अगर (conn->datadgst_en &&
			    !(conn->session->tt->caps & CAP_DIGEST_OFFLOAD))
				rx_hash = tcp_conn->rx_hash;

			ISCSI_DBG_TCP(conn, "iscsi_tcp_begin_data_in( "
				     "offset=%d, datalen=%d)\n",
				      tcp_task->data_offset,
				      tcp_conn->in.datalen);
			task->last_xfer = jअगरfies;
			rc = iscsi_segment_seek_sg(&tcp_conn->in.segment,
						   sdb->table.sgl,
						   sdb->table.nents,
						   tcp_task->data_offset,
						   tcp_conn->in.datalen,
						   iscsi_tcp_process_data_in,
						   rx_hash);
			spin_unlock(&conn->session->back_lock);
			वापस rc;
		पूर्ण
		rc = __iscsi_complete_pdu(conn, hdr, शून्य, 0);
		spin_unlock(&conn->session->back_lock);
		अवरोध;
	हाल ISCSI_OP_SCSI_CMD_RSP:
		अगर (tcp_conn->in.datalen) अणु
			iscsi_tcp_data_recv_prep(tcp_conn);
			वापस 0;
		पूर्ण
		rc = iscsi_complete_pdu(conn, hdr, शून्य, 0);
		अवरोध;
	हाल ISCSI_OP_R2T:
		अगर (ahslen) अणु
			rc = ISCSI_ERR_AHSLEN;
			अवरोध;
		पूर्ण
		rc = iscsi_tcp_r2t_rsp(conn, hdr);
		अवरोध;
	हाल ISCSI_OP_LOGIN_RSP:
	हाल ISCSI_OP_TEXT_RSP:
	हाल ISCSI_OP_REJECT:
	हाल ISCSI_OP_ASYNC_EVENT:
		/*
		 * It is possible that we could get a PDU with a buffer larger
		 * than 8K, but there are no tarमाला_लो that currently करो this.
		 * For now we fail until we find a venकरोr that needs it
		 */
		अगर (ISCSI_DEF_MAX_RECV_SEG_LEN < tcp_conn->in.datalen) अणु
			iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
					  "iscsi_tcp: received buffer of "
					  "len %u but conn buffer is only %u "
					  "(opcode %0x)\n",
					  tcp_conn->in.datalen,
					  ISCSI_DEF_MAX_RECV_SEG_LEN, opcode);
			rc = ISCSI_ERR_PROTO;
			अवरोध;
		पूर्ण

		/* If there's data coming in with the response,
		 * receive it to the connection's buffer.
		 */
		अगर (tcp_conn->in.datalen) अणु
			iscsi_tcp_data_recv_prep(tcp_conn);
			वापस 0;
		पूर्ण
		fallthrough;
	हाल ISCSI_OP_LOGOUT_RSP:
	हाल ISCSI_OP_NOOP_IN:
	हाल ISCSI_OP_SCSI_TMFUNC_RSP:
		rc = iscsi_complete_pdu(conn, hdr, शून्य, 0);
		अवरोध;
	शेष:
		rc = ISCSI_ERR_BAD_OPCODE;
		अवरोध;
	पूर्ण

	अगर (rc == 0) अणु
		/* Anything that comes with data should have
		 * been handled above. */
		अगर (tcp_conn->in.datalen)
			वापस ISCSI_ERR_PROTO;
		iscsi_tcp_hdr_recv_prep(tcp_conn);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * iscsi_tcp_hdr_recv_करोne - process PDU header
 * @tcp_conn: iSCSI TCP connection
 * @segment: the buffer segment being processed
 *
 * This is the callback invoked when the PDU header has
 * been received. If the header is followed by additional
 * header segments, we go back क्रम more data.
 */
अटल पूर्णांक
iscsi_tcp_hdr_recv_करोne(काष्ठा iscsi_tcp_conn *tcp_conn,
			काष्ठा iscsi_segment *segment)
अणु
	काष्ठा iscsi_conn *conn = tcp_conn->iscsi_conn;
	काष्ठा iscsi_hdr *hdr;

	/* Check अगर there are additional header segments
	 * *prior* to computing the digest, because we
	 * may need to go back to the caller क्रम more.
	 */
	hdr = (काष्ठा iscsi_hdr *) tcp_conn->in.hdr_buf;
	अगर (segment->copied == माप(काष्ठा iscsi_hdr) && hdr->hlength) अणु
		/* Bump the header length - the caller will
		 * just loop around and get the AHS क्रम us, and
		 * call again. */
		अचिन्हित पूर्णांक ahslen = hdr->hlength << 2;

		/* Make sure we करोn't overflow */
		अगर (माप(*hdr) + ahslen > माप(tcp_conn->in.hdr_buf))
			वापस ISCSI_ERR_AHSLEN;

		segment->total_size += ahslen;
		segment->size += ahslen;
		वापस 0;
	पूर्ण

	/* We're done processing the header. See if we're करोing
	 * header digests; अगर so, set up the recv_digest buffer
	 * and go back क्रम more. */
	अगर (conn->hdrdgst_en &&
	    !(conn->session->tt->caps & CAP_DIGEST_OFFLOAD)) अणु
		अगर (segment->digest_len == 0) अणु
			/*
			 * Even अगर we offload the digest processing we
			 * splice it in so we can increment the skb/segment
			 * counters in preparation क्रम the data segment.
			 */
			iscsi_tcp_segment_splice_digest(segment,
							segment->recv_digest);
			वापस 0;
		पूर्ण

		iscsi_tcp_dgst_header(tcp_conn->rx_hash, hdr,
				      segment->total_copied - ISCSI_DIGEST_SIZE,
				      segment->digest);

		अगर (!iscsi_tcp_dgst_verअगरy(tcp_conn, segment))
			वापस ISCSI_ERR_HDR_DGST;
	पूर्ण

	tcp_conn->in.hdr = hdr;
	वापस iscsi_tcp_hdr_dissect(conn, hdr);
पूर्ण

/**
 * iscsi_tcp_recv_segment_is_hdr - tests अगर we are पढ़ोing in a header
 * @tcp_conn: iscsi tcp conn
 *
 * वापसs non zero अगर we are currently processing or setup to process
 * a header.
 */
अंतरभूत पूर्णांक iscsi_tcp_recv_segment_is_hdr(काष्ठा iscsi_tcp_conn *tcp_conn)
अणु
	वापस tcp_conn->in.segment.करोne == iscsi_tcp_hdr_recv_करोne;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_recv_segment_is_hdr);

/**
 * iscsi_tcp_recv_skb - Process skb
 * @conn: iscsi connection
 * @skb: network buffer with header and/or data segment
 * @offset: offset in skb
 * @offloaded: bool indicating अगर transfer was offloaded
 * @status: iscsi TCP status result
 *
 * Will वापस status of transfer in @status. And will वापस
 * number of bytes copied.
 */
पूर्णांक iscsi_tcp_recv_skb(काष्ठा iscsi_conn *conn, काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक offset, bool offloaded, पूर्णांक *status)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_segment *segment = &tcp_conn->in.segment;
	काष्ठा skb_seq_state seq;
	अचिन्हित पूर्णांक consumed = 0;
	पूर्णांक rc = 0;

	ISCSI_DBG_TCP(conn, "in %d bytes\n", skb->len - offset);
	/*
	 * Update क्रम each skb instead of pdu, because over slow networks a
	 * data_in's data could take a जबतक to पढ़ो in. We also want to
	 * account क्रम r2ts.
	 */
	conn->last_recv = jअगरfies;

	अगर (unlikely(conn->suspend_rx)) अणु
		ISCSI_DBG_TCP(conn, "Rx suspended!\n");
		*status = ISCSI_TCP_SUSPENDED;
		वापस 0;
	पूर्ण

	अगर (offloaded) अणु
		segment->total_copied = segment->total_size;
		जाओ segment_करोne;
	पूर्ण

	skb_prepare_seq_पढ़ो(skb, offset, skb->len, &seq);
	जबतक (1) अणु
		अचिन्हित पूर्णांक avail;
		स्थिर u8 *ptr;

		avail = skb_seq_पढ़ो(consumed, &ptr, &seq);
		अगर (avail == 0) अणु
			ISCSI_DBG_TCP(conn, "no more data avail. Consumed %d\n",
				      consumed);
			*status = ISCSI_TCP_SKB_DONE;
			जाओ skb_करोne;
		पूर्ण
		BUG_ON(segment->copied >= segment->size);

		ISCSI_DBG_TCP(conn, "skb %p ptr=%p avail=%u\n", skb, ptr,
			      avail);
		rc = iscsi_tcp_segment_recv(tcp_conn, segment, ptr, avail);
		BUG_ON(rc == 0);
		consumed += rc;

		अगर (segment->total_copied >= segment->total_size) अणु
			skb_पात_seq_पढ़ो(&seq);
			जाओ segment_करोne;
		पूर्ण
	पूर्ण

segment_करोne:
	*status = ISCSI_TCP_SEGMENT_DONE;
	ISCSI_DBG_TCP(conn, "segment done\n");
	rc = segment->करोne(tcp_conn, segment);
	अगर (rc != 0) अणु
		*status = ISCSI_TCP_CONN_ERR;
		ISCSI_DBG_TCP(conn, "Error receiving PDU, errno=%d\n", rc);
		iscsi_conn_failure(conn, rc);
		वापस 0;
	पूर्ण
	/* The करोne() functions sets up the next segment. */

skb_करोne:
	conn->rxdata_octets += consumed;
	वापस consumed;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_recv_skb);

/**
 * iscsi_tcp_task_init - Initialize iSCSI SCSI_READ or SCSI_WRITE commands
 * @task: scsi command task
 */
पूर्णांक iscsi_tcp_task_init(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा scsi_cmnd *sc = task->sc;
	पूर्णांक err;

	अगर (!sc) अणु
		/*
		 * mgmt tasks करो not have a scatterlist since they come
		 * in from the iscsi पूर्णांकerface.
		 */
		ISCSI_DBG_TCP(conn, "mtask deq [itt 0x%x]\n", task->itt);

		वापस conn->session->tt->init_pdu(task, 0, task->data_count);
	पूर्ण

	BUG_ON(kfअगरo_len(&tcp_task->r2tqueue));
	tcp_task->exp_datasn = 0;

	/* Prepare PDU, optionally w/ immediate data */
	ISCSI_DBG_TCP(conn, "task deq [itt 0x%x imm %d unsol %d]\n",
		      task->itt, task->imm_count, task->unsol_r2t.data_length);

	err = conn->session->tt->init_pdu(task, 0, task->imm_count);
	अगर (err)
		वापस err;
	task->imm_count = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_task_init);

अटल काष्ठा iscsi_r2t_info *iscsi_tcp_get_curr_r2t(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
	काष्ठा iscsi_r2t_info *r2t = शून्य;

	अगर (iscsi_task_has_unsol_data(task))
		r2t = &task->unsol_r2t;
	अन्यथा अणु
		spin_lock_bh(&tcp_task->queue2pool);
		अगर (tcp_task->r2t) अणु
			r2t = tcp_task->r2t;
			/* Continue with this R2T? */
			अगर (r2t->data_length <= r2t->sent) अणु
				ISCSI_DBG_TCP(task->conn,
					      "  done with r2t %p\n", r2t);
				kfअगरo_in(&tcp_task->r2tpool.queue,
					    (व्योम *)&tcp_task->r2t,
					    माप(व्योम *));
				tcp_task->r2t = r2t = शून्य;
			पूर्ण
		पूर्ण

		अगर (r2t == शून्य) अणु
			अगर (kfअगरo_out(&tcp_task->r2tqueue,
			    (व्योम *)&tcp_task->r2t, माप(व्योम *)) !=
			    माप(व्योम *))
				r2t = शून्य;
			अन्यथा
				r2t = tcp_task->r2t;
		पूर्ण
		spin_unlock_bh(&tcp_task->queue2pool);
	पूर्ण

	वापस r2t;
पूर्ण

/**
 * iscsi_tcp_task_xmit - xmit normal PDU task
 * @task: iscsi command task
 *
 * We're expected to वापस 0 when everything was transmitted successfully,
 * -EAGAIN अगर there's still data in the queue, or != 0 क्रम any other kind
 * of error.
 */
पूर्णांक iscsi_tcp_task_xmit(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा iscsi_r2t_info *r2t;
	पूर्णांक rc = 0;

flush:
	/* Flush any pending data first. */
	rc = session->tt->xmit_pdu(task);
	अगर (rc < 0)
		वापस rc;

	/* mgmt command */
	अगर (!task->sc) अणु
		अगर (task->hdr->itt == RESERVED_ITT)
			iscsi_put_task(task);
		वापस 0;
	पूर्ण

	/* Are we करोne alपढ़ोy? */
	अगर (task->sc->sc_data_direction != DMA_TO_DEVICE)
		वापस 0;

	r2t = iscsi_tcp_get_curr_r2t(task);
	अगर (r2t == शून्य) अणु
		/* Waiting क्रम more R2Ts to arrive. */
		ISCSI_DBG_TCP(conn, "no R2Ts yet\n");
		वापस 0;
	पूर्ण

	rc = conn->session->tt->alloc_pdu(task, ISCSI_OP_SCSI_DATA_OUT);
	अगर (rc)
		वापस rc;
	iscsi_prep_data_out_pdu(task, r2t, (काष्ठा iscsi_data *) task->hdr);

	ISCSI_DBG_TCP(conn, "sol dout %p [dsn %d itt 0x%x doff %d dlen %d]\n",
		      r2t, r2t->datasn - 1, task->hdr->itt,
		      r2t->data_offset + r2t->sent, r2t->data_count);

	rc = conn->session->tt->init_pdu(task, r2t->data_offset + r2t->sent,
					 r2t->data_count);
	अगर (rc) अणु
		iscsi_conn_failure(conn, ISCSI_ERR_XMIT_FAILED);
		वापस rc;
	पूर्ण

	r2t->sent += r2t->data_count;
	जाओ flush;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_task_xmit);

काष्ठा iscsi_cls_conn *
iscsi_tcp_conn_setup(काष्ठा iscsi_cls_session *cls_session, पूर्णांक dd_data_size,
		      uपूर्णांक32_t conn_idx)

अणु
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_tcp_conn *tcp_conn;

	cls_conn = iscsi_conn_setup(cls_session,
				    माप(*tcp_conn) + dd_data_size, conn_idx);
	अगर (!cls_conn)
		वापस शून्य;
	conn = cls_conn->dd_data;
	/*
	 * due to strange issues with iser these are not set
	 * in iscsi_conn_setup
	 */
	conn->max_recv_dlength = ISCSI_DEF_MAX_RECV_SEG_LEN;

	tcp_conn = conn->dd_data;
	tcp_conn->iscsi_conn = conn;
	tcp_conn->dd_data = conn->dd_data + माप(*tcp_conn);
	वापस cls_conn;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_conn_setup);

व्योम iscsi_tcp_conn_tearकरोwn(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	iscsi_conn_tearकरोwn(cls_conn);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_conn_tearकरोwn);

पूर्णांक iscsi_tcp_r2tpool_alloc(काष्ठा iscsi_session *session)
अणु
	पूर्णांक i;
	पूर्णांक cmd_i;

	/*
	 * initialize per-task: R2T pool and xmit queue
	 */
	क्रम (cmd_i = 0; cmd_i < session->cmds_max; cmd_i++) अणु
	        काष्ठा iscsi_task *task = session->cmds[cmd_i];
		काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;

		/*
		 * pre-allocated x2 as much r2ts to handle race when
		 * target acks DataOut faster than we data_xmit() queues
		 * could replenish r2tqueue.
		 */

		/* R2T pool */
		अगर (iscsi_pool_init(&tcp_task->r2tpool,
				    session->max_r2t * 2, शून्य,
				    माप(काष्ठा iscsi_r2t_info))) अणु
			जाओ r2t_alloc_fail;
		पूर्ण

		/* R2T xmit queue */
		अगर (kfअगरo_alloc(&tcp_task->r2tqueue,
		      session->max_r2t * 4 * माप(व्योम*), GFP_KERNEL)) अणु
			iscsi_pool_मुक्त(&tcp_task->r2tpool);
			जाओ r2t_alloc_fail;
		पूर्ण
		spin_lock_init(&tcp_task->pool2queue);
		spin_lock_init(&tcp_task->queue2pool);
	पूर्ण

	वापस 0;

r2t_alloc_fail:
	क्रम (i = 0; i < cmd_i; i++) अणु
		काष्ठा iscsi_task *task = session->cmds[i];
		काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;

		kfअगरo_मुक्त(&tcp_task->r2tqueue);
		iscsi_pool_मुक्त(&tcp_task->r2tpool);
	पूर्ण
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_r2tpool_alloc);

व्योम iscsi_tcp_r2tpool_मुक्त(काष्ठा iscsi_session *session)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < session->cmds_max; i++) अणु
		काष्ठा iscsi_task *task = session->cmds[i];
		काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;

		kfअगरo_मुक्त(&tcp_task->r2tqueue);
		iscsi_pool_मुक्त(&tcp_task->r2tpool);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_r2tpool_मुक्त);

पूर्णांक iscsi_tcp_set_max_r2t(काष्ठा iscsi_conn *conn, अक्षर *buf)
अणु
	काष्ठा iscsi_session *session = conn->session;
	अचिन्हित लघु r2ts = 0;

	माला_पूछो(buf, "%hu", &r2ts);
	अगर (session->max_r2t == r2ts)
		वापस 0;

	अगर (!r2ts || !is_घातer_of_2(r2ts))
		वापस -EINVAL;

	session->max_r2t = r2ts;
	iscsi_tcp_r2tpool_मुक्त(session);
	वापस iscsi_tcp_r2tpool_alloc(session);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_set_max_r2t);

व्योम iscsi_tcp_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn,
			      काष्ठा iscsi_stats *stats)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;

	stats->txdata_octets = conn->txdata_octets;
	stats->rxdata_octets = conn->rxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsirsp_pdus = conn->scsirsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->r2t_pdus = conn->r2t_pdus_cnt;
	stats->पंचांगfcmd_pdus = conn->पंचांगfcmd_pdus_cnt;
	stats->पंचांगfrsp_pdus = conn->पंचांगfrsp_pdus_cnt;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_tcp_conn_get_stats);
