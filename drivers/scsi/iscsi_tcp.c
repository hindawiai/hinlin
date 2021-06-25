<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * iSCSI Initiator over TCP/IP Data-Path
 *
 * Copyright (C) 2004 Dmitry Yusupov
 * Copyright (C) 2004 Alex Aizman
 * Copyright (C) 2005 - 2006 Mike Christie
 * Copyright (C) 2006 Red Hat, Inc.  All rights reserved.
 * मुख्यtained by खोलो-iscsi@googlegroups.com
 *
 * See the file COPYING included with this distribution क्रम more details.
 *
 * Credits:
 *	Christoph Hellwig
 *	FUJITA Tomonori
 *	Arne Redlich
 *	Zhenyu Wang
 */

#समावेश <crypto/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/inet.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/file.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/module.h>
#समावेश <linux/backing-dev.h>
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

अटल काष्ठा scsi_transport_ढाँचा *iscsi_sw_tcp_scsi_transport;
अटल काष्ठा scsi_host_ढाँचा iscsi_sw_tcp_sht;
अटल काष्ठा iscsi_transport iscsi_sw_tcp_transport;

अटल अचिन्हित पूर्णांक iscsi_max_lun = ~0;
module_param_named(max_lun, iscsi_max_lun, uपूर्णांक, S_IRUGO);

अटल पूर्णांक iscsi_sw_tcp_dbg;
module_param_named(debug_iscsi_tcp, iscsi_sw_tcp_dbg, पूर्णांक,
		   S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_iscsi_tcp, "Turn on debugging for iscsi_tcp module "
		 "Set to 1 to turn on, and zero to turn off. Default is off.");

#घोषणा ISCSI_SW_TCP_DBG(_conn, dbg_fmt, arg...)		\
	करो अणु							\
		अगर (iscsi_sw_tcp_dbg)				\
			iscsi_conn_prपूर्णांकk(KERN_INFO, _conn,	\
					     "%s " dbg_fmt,	\
					     __func__, ##arg);	\
		iscsi_dbg_trace(trace_iscsi_dbg_sw_tcp,		\
				&(_conn)->cls_conn->dev,	\
				"%s " dbg_fmt, __func__, ##arg);\
	पूर्ण जबतक (0);


/**
 * iscsi_sw_tcp_recv - TCP receive in sendfile fashion
 * @rd_desc: पढ़ो descriptor
 * @skb: socket buffer
 * @offset: offset in skb
 * @len: skb->len - offset
 */
अटल पूर्णांक iscsi_sw_tcp_recv(पढ़ो_descriptor_t *rd_desc, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक offset, माप_प्रकार len)
अणु
	काष्ठा iscsi_conn *conn = rd_desc->arg.data;
	अचिन्हित पूर्णांक consumed, total_consumed = 0;
	पूर्णांक status;

	ISCSI_SW_TCP_DBG(conn, "in %d bytes\n", skb->len - offset);

	करो अणु
		status = 0;
		consumed = iscsi_tcp_recv_skb(conn, skb, offset, 0, &status);
		offset += consumed;
		total_consumed += consumed;
	पूर्ण जबतक (consumed != 0 && status != ISCSI_TCP_SKB_DONE);

	ISCSI_SW_TCP_DBG(conn, "read %d bytes status %d\n",
			 skb->len - offset, status);
	वापस total_consumed;
पूर्ण

/**
 * iscsi_sw_sk_state_check - check socket state
 * @sk: socket
 *
 * If the socket is in CLOSE or CLOSE_WAIT we should
 * not बंद the connection अगर there is still some
 * data pending.
 *
 * Must be called with sk_callback_lock.
 */
अटल अंतरभूत पूर्णांक iscsi_sw_sk_state_check(काष्ठा sock *sk)
अणु
	काष्ठा iscsi_conn *conn = sk->sk_user_data;

	अगर ((sk->sk_state == TCP_CLOSE_WAIT || sk->sk_state == TCP_CLOSE) &&
	    (conn->session->state != ISCSI_STATE_LOGGING_OUT) &&
	    !atomic_पढ़ो(&sk->sk_rmem_alloc)) अणु
		ISCSI_SW_TCP_DBG(conn, "TCP_CLOSE|TCP_CLOSE_WAIT\n");
		iscsi_conn_failure(conn, ISCSI_ERR_TCP_CONN_CLOSE);
		वापस -ECONNRESET;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम iscsi_sw_tcp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_tcp_conn *tcp_conn;
	पढ़ो_descriptor_t rd_desc;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	conn = sk->sk_user_data;
	अगर (!conn) अणु
		पढ़ो_unlock_bh(&sk->sk_callback_lock);
		वापस;
	पूर्ण
	tcp_conn = conn->dd_data;

	/*
	 * Use rd_desc to pass 'conn' to iscsi_tcp_recv.
	 * We set count to 1 because we want the network layer to
	 * hand us all the skbs that are available. iscsi_tcp_recv
	 * handled pdus that cross buffers or pdus that still need data.
	 */
	rd_desc.arg.data = conn;
	rd_desc.count = 1;
	tcp_पढ़ो_sock(sk, &rd_desc, iscsi_sw_tcp_recv);

	iscsi_sw_sk_state_check(sk);

	/* If we had to (atomically) map a highmem page,
	 * unmap it now. */
	iscsi_tcp_segment_unmap(&tcp_conn->in.segment);
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम iscsi_sw_tcp_state_change(काष्ठा sock *sk)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn;
	काष्ठा iscsi_conn *conn;
	व्योम (*old_state_change)(काष्ठा sock *);

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	conn = sk->sk_user_data;
	अगर (!conn) अणु
		पढ़ो_unlock_bh(&sk->sk_callback_lock);
		वापस;
	पूर्ण

	iscsi_sw_sk_state_check(sk);

	tcp_conn = conn->dd_data;
	tcp_sw_conn = tcp_conn->dd_data;
	old_state_change = tcp_sw_conn->old_state_change;

	पढ़ो_unlock_bh(&sk->sk_callback_lock);

	old_state_change(sk);
पूर्ण

/**
 * iscsi_sw_tcp_ग_लिखो_space - Called when more output buffer space is available
 * @sk: socket space is available क्रम
 **/
अटल व्योम iscsi_sw_tcp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_tcp_conn *tcp_conn;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn;
	व्योम (*old_ग_लिखो_space)(काष्ठा sock *);

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	conn = sk->sk_user_data;
	अगर (!conn) अणु
		पढ़ो_unlock_bh(&sk->sk_callback_lock);
		वापस;
	पूर्ण

	tcp_conn = conn->dd_data;
	tcp_sw_conn = tcp_conn->dd_data;
	old_ग_लिखो_space = tcp_sw_conn->old_ग_लिखो_space;
	पढ़ो_unlock_bh(&sk->sk_callback_lock);

	old_ग_लिखो_space(sk);

	ISCSI_SW_TCP_DBG(conn, "iscsi_write_space\n");
	iscsi_conn_queue_work(conn);
पूर्ण

अटल व्योम iscsi_sw_tcp_conn_set_callbacks(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा sock *sk = tcp_sw_conn->sock->sk;

	/* assign new callbacks */
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk->sk_user_data = conn;
	tcp_sw_conn->old_data_पढ़ोy = sk->sk_data_पढ़ोy;
	tcp_sw_conn->old_state_change = sk->sk_state_change;
	tcp_sw_conn->old_ग_लिखो_space = sk->sk_ग_लिखो_space;
	sk->sk_data_पढ़ोy = iscsi_sw_tcp_data_पढ़ोy;
	sk->sk_state_change = iscsi_sw_tcp_state_change;
	sk->sk_ग_लिखो_space = iscsi_sw_tcp_ग_लिखो_space;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम
iscsi_sw_tcp_conn_restore_callbacks(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा sock *sk = tcp_sw_conn->sock->sk;

	/* restore socket callbacks, see also: iscsi_conn_set_callbacks() */
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk->sk_user_data    = शून्य;
	sk->sk_data_पढ़ोy   = tcp_sw_conn->old_data_पढ़ोy;
	sk->sk_state_change = tcp_sw_conn->old_state_change;
	sk->sk_ग_लिखो_space  = tcp_sw_conn->old_ग_लिखो_space;
	sk->sk_no_check_tx = 0;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

/**
 * iscsi_sw_tcp_xmit_segment - transmit segment
 * @tcp_conn: the iSCSI TCP connection
 * @segment: the buffer to transmnit
 *
 * This function transmits as much of the buffer as
 * the network layer will accept, and वापसs the number of
 * bytes transmitted.
 *
 * If CRC hashing is enabled, the function will compute the
 * hash as it goes. When the entire segment has been transmitted,
 * it will retrieve the hash value and send it as well.
 */
अटल पूर्णांक iscsi_sw_tcp_xmit_segment(काष्ठा iscsi_tcp_conn *tcp_conn,
				     काष्ठा iscsi_segment *segment)
अणु
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा socket *sk = tcp_sw_conn->sock;
	अचिन्हित पूर्णांक copied = 0;
	पूर्णांक r = 0;

	जबतक (!iscsi_tcp_segment_करोne(tcp_conn, segment, 0, r)) अणु
		काष्ठा scatterlist *sg;
		अचिन्हित पूर्णांक offset, copy;
		पूर्णांक flags = 0;

		r = 0;
		offset = segment->copied;
		copy = segment->size - offset;

		अगर (segment->total_copied + segment->size < segment->total_size)
			flags |= MSG_MORE;

		/* Use sendpage अगर we can; अन्यथा fall back to sendmsg */
		अगर (!segment->data) अणु
			sg = segment->sg;
			offset += segment->sg_offset + sg->offset;
			r = tcp_sw_conn->sendpage(sk, sg_page(sg), offset,
						  copy, flags);
		पूर्ण अन्यथा अणु
			काष्ठा msghdr msg = अणु .msg_flags = flags पूर्ण;
			काष्ठा kvec iov = अणु
				.iov_base = segment->data + offset,
				.iov_len = copy
			पूर्ण;

			r = kernel_sendmsg(sk, &msg, &iov, 1, copy);
		पूर्ण

		अगर (r < 0) अणु
			iscsi_tcp_segment_unmap(segment);
			वापस r;
		पूर्ण
		copied += r;
	पूर्ण
	वापस copied;
पूर्ण

/**
 * iscsi_sw_tcp_xmit - TCP transmit
 * @conn: iscsi connection
 **/
अटल पूर्णांक iscsi_sw_tcp_xmit(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा iscsi_segment *segment = &tcp_sw_conn->out.segment;
	अचिन्हित पूर्णांक consumed = 0;
	पूर्णांक rc = 0;

	जबतक (1) अणु
		rc = iscsi_sw_tcp_xmit_segment(tcp_conn, segment);
		/*
		 * We may not have been able to send data because the conn
		 * is getting stopped. libiscsi will know so propagate err
		 * क्रम it to करो the right thing.
		 */
		अगर (rc == -EAGAIN)
			वापस rc;
		अन्यथा अगर (rc < 0) अणु
			rc = ISCSI_ERR_XMIT_FAILED;
			जाओ error;
		पूर्ण अन्यथा अगर (rc == 0)
			अवरोध;

		consumed += rc;

		अगर (segment->total_copied >= segment->total_size) अणु
			अगर (segment->करोne != शून्य) अणु
				rc = segment->करोne(tcp_conn, segment);
				अगर (rc != 0)
					जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	ISCSI_SW_TCP_DBG(conn, "xmit %d bytes\n", consumed);

	conn->txdata_octets += consumed;
	वापस consumed;

error:
	/* Transmit error. We could initiate error recovery
	 * here. */
	ISCSI_SW_TCP_DBG(conn, "Error sending PDU, errno=%d\n", rc);
	iscsi_conn_failure(conn, rc);
	वापस -EIO;
पूर्ण

/**
 * iscsi_sw_tcp_xmit_qlen - वापस the number of bytes queued क्रम xmit
 * @conn: iscsi connection
 */
अटल अंतरभूत पूर्णांक iscsi_sw_tcp_xmit_qlen(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा iscsi_segment *segment = &tcp_sw_conn->out.segment;

	वापस segment->total_copied - segment->total_size;
पूर्ण

अटल पूर्णांक iscsi_sw_tcp_pdu_xmit(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	अचिन्हित पूर्णांक noreclaim_flag;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	पूर्णांक rc = 0;

	अगर (!tcp_sw_conn->sock) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "Transport not bound to socket!\n");
		वापस -EINVAL;
	पूर्ण

	noreclaim_flag = meदो_स्मृति_noreclaim_save();

	जबतक (iscsi_sw_tcp_xmit_qlen(conn)) अणु
		rc = iscsi_sw_tcp_xmit(conn);
		अगर (rc == 0) अणु
			rc = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (rc < 0)
			अवरोध;
		rc = 0;
	पूर्ण

	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	वापस rc;
पूर्ण

/*
 * This is called when we're करोne sending the header.
 * Simply copy the data_segment to the send segment, and वापस.
 */
अटल पूर्णांक iscsi_sw_tcp_send_hdr_करोne(काष्ठा iscsi_tcp_conn *tcp_conn,
				      काष्ठा iscsi_segment *segment)
अणु
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	tcp_sw_conn->out.segment = tcp_sw_conn->out.data_segment;
	ISCSI_SW_TCP_DBG(tcp_conn->iscsi_conn,
			 "Header done. Next segment size %u total_size %u\n",
			 tcp_sw_conn->out.segment.size,
			 tcp_sw_conn->out.segment.total_size);
	वापस 0;
पूर्ण

अटल व्योम iscsi_sw_tcp_send_hdr_prep(काष्ठा iscsi_conn *conn, व्योम *hdr,
				       माप_प्रकार hdrlen)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	ISCSI_SW_TCP_DBG(conn, "%s\n", conn->hdrdgst_en ?
			 "digest enabled" : "digest disabled");

	/* Clear the data segment - needs to be filled in by the
	 * caller using iscsi_tcp_send_data_prep() */
	स_रखो(&tcp_sw_conn->out.data_segment, 0,
	       माप(काष्ठा iscsi_segment));

	/* If header digest is enabled, compute the CRC and
	 * place the digest पूर्णांकo the same buffer. We make
	 * sure that both iscsi_tcp_task and mtask have
	 * sufficient room.
	 */
	अगर (conn->hdrdgst_en) अणु
		iscsi_tcp_dgst_header(tcp_sw_conn->tx_hash, hdr, hdrlen,
				      hdr + hdrlen);
		hdrlen += ISCSI_DIGEST_SIZE;
	पूर्ण

	/* Remember header poपूर्णांकer क्रम later, when we need
	 * to decide whether there's a payload to go aदीर्घ
	 * with the header. */
	tcp_sw_conn->out.hdr = hdr;

	iscsi_segment_init_linear(&tcp_sw_conn->out.segment, hdr, hdrlen,
				  iscsi_sw_tcp_send_hdr_करोne, शून्य);
पूर्ण

/*
 * Prepare the send buffer क्रम the payload data.
 * Padding and checksumming will all be taken care
 * of by the iscsi_segment routines.
 */
अटल पूर्णांक
iscsi_sw_tcp_send_data_prep(काष्ठा iscsi_conn *conn, काष्ठा scatterlist *sg,
			    अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक offset,
			    अचिन्हित पूर्णांक len)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा ahash_request *tx_hash = शून्य;
	अचिन्हित पूर्णांक hdr_spec_len;

	ISCSI_SW_TCP_DBG(conn, "offset=%d, datalen=%d %s\n", offset, len,
			 conn->datadgst_en ?
			 "digest enabled" : "digest disabled");

	/* Make sure the datalen matches what the caller
	   said he would send. */
	hdr_spec_len = ntoh24(tcp_sw_conn->out.hdr->dlength);
	WARN_ON(iscsi_padded(len) != iscsi_padded(hdr_spec_len));

	अगर (conn->datadgst_en)
		tx_hash = tcp_sw_conn->tx_hash;

	वापस iscsi_segment_seek_sg(&tcp_sw_conn->out.data_segment,
				     sg, count, offset, len,
				     शून्य, tx_hash);
पूर्ण

अटल व्योम
iscsi_sw_tcp_send_linear_data_prep(काष्ठा iscsi_conn *conn, व्योम *data,
				   माप_प्रकार len)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा ahash_request *tx_hash = शून्य;
	अचिन्हित पूर्णांक hdr_spec_len;

	ISCSI_SW_TCP_DBG(conn, "datalen=%zd %s\n", len, conn->datadgst_en ?
			 "digest enabled" : "digest disabled");

	/* Make sure the datalen matches what the caller
	   said he would send. */
	hdr_spec_len = ntoh24(tcp_sw_conn->out.hdr->dlength);
	WARN_ON(iscsi_padded(len) != iscsi_padded(hdr_spec_len));

	अगर (conn->datadgst_en)
		tx_hash = tcp_sw_conn->tx_hash;

	iscsi_segment_init_linear(&tcp_sw_conn->out.data_segment,
				data, len, शून्य, tx_hash);
पूर्ण

अटल पूर्णांक iscsi_sw_tcp_pdu_init(काष्ठा iscsi_task *task,
				 अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक count)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	पूर्णांक err = 0;

	iscsi_sw_tcp_send_hdr_prep(conn, task->hdr, task->hdr_len);

	अगर (!count)
		वापस 0;

	अगर (!task->sc)
		iscsi_sw_tcp_send_linear_data_prep(conn, task->data, count);
	अन्यथा अणु
		काष्ठा scsi_data_buffer *sdb = &task->sc->sdb;

		err = iscsi_sw_tcp_send_data_prep(conn, sdb->table.sgl,
						  sdb->table.nents, offset,
						  count);
	पूर्ण

	अगर (err) अणु
		/* got invalid offset/len */
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_sw_tcp_pdu_alloc(काष्ठा iscsi_task *task, uपूर्णांक8_t opcode)
अणु
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;

	task->hdr = task->dd_data + माप(*tcp_task);
	task->hdr_max = माप(काष्ठा iscsi_sw_tcp_hdrbuf) - ISCSI_DIGEST_SIZE;
	वापस 0;
पूर्ण

अटल काष्ठा iscsi_cls_conn *
iscsi_sw_tcp_conn_create(काष्ठा iscsi_cls_session *cls_session,
			 uपूर्णांक32_t conn_idx)
अणु
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_tcp_conn *tcp_conn;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn;
	काष्ठा crypto_ahash *tfm;

	cls_conn = iscsi_tcp_conn_setup(cls_session, माप(*tcp_sw_conn),
					conn_idx);
	अगर (!cls_conn)
		वापस शून्य;
	conn = cls_conn->dd_data;
	tcp_conn = conn->dd_data;
	tcp_sw_conn = tcp_conn->dd_data;

	tfm = crypto_alloc_ahash("crc32c", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm))
		जाओ मुक्त_conn;

	tcp_sw_conn->tx_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!tcp_sw_conn->tx_hash)
		जाओ मुक्त_tfm;
	ahash_request_set_callback(tcp_sw_conn->tx_hash, 0, शून्य, शून्य);

	tcp_sw_conn->rx_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!tcp_sw_conn->rx_hash)
		जाओ मुक्त_tx_hash;
	ahash_request_set_callback(tcp_sw_conn->rx_hash, 0, शून्य, शून्य);

	tcp_conn->rx_hash = tcp_sw_conn->rx_hash;

	वापस cls_conn;

मुक्त_tx_hash:
	ahash_request_मुक्त(tcp_sw_conn->tx_hash);
मुक्त_tfm:
	crypto_मुक्त_ahash(tfm);
मुक्त_conn:
	iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
			  "Could not create connection due to crc32c "
			  "loading error. Make sure the crc32c "
			  "module is built as a module or into the "
			  "kernel\n");
	iscsi_tcp_conn_tearकरोwn(cls_conn);
	वापस शून्य;
पूर्ण

अटल व्योम iscsi_sw_tcp_release_conn(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा socket *sock = tcp_sw_conn->sock;

	अगर (!sock)
		वापस;

	sock_hold(sock->sk);
	iscsi_sw_tcp_conn_restore_callbacks(conn);
	sock_put(sock->sk);

	spin_lock_bh(&session->frwd_lock);
	tcp_sw_conn->sock = शून्य;
	spin_unlock_bh(&session->frwd_lock);
	sockfd_put(sock);
पूर्ण

अटल व्योम iscsi_sw_tcp_conn_destroy(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	iscsi_sw_tcp_release_conn(conn);

	ahash_request_मुक्त(tcp_sw_conn->rx_hash);
	अगर (tcp_sw_conn->tx_hash) अणु
		काष्ठा crypto_ahash *tfm;

		tfm = crypto_ahash_reqtfm(tcp_sw_conn->tx_hash);
		ahash_request_मुक्त(tcp_sw_conn->tx_hash);
		crypto_मुक्त_ahash(tfm);
	पूर्ण

	iscsi_tcp_conn_tearकरोwn(cls_conn);
पूर्ण

अटल व्योम iscsi_sw_tcp_conn_stop(काष्ठा iscsi_cls_conn *cls_conn, पूर्णांक flag)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा socket *sock = tcp_sw_conn->sock;

	/* userspace may have goofed up and not bound us */
	अगर (!sock)
		वापस;

	sock->sk->sk_err = EIO;
	wake_up_पूर्णांकerruptible(sk_sleep(sock->sk));

	/* stop xmit side */
	iscsi_suspend_tx(conn);

	/* stop recv side and release socket */
	iscsi_sw_tcp_release_conn(conn);

	iscsi_conn_stop(cls_conn, flag);
पूर्ण

अटल पूर्णांक
iscsi_sw_tcp_conn_bind(काष्ठा iscsi_cls_session *cls_session,
		       काष्ठा iscsi_cls_conn *cls_conn, uपूर्णांक64_t transport_eph,
		       पूर्णांक is_leading)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा sock *sk;
	काष्ठा socket *sock;
	पूर्णांक err;

	/* lookup क्रम existing socket */
	sock = sockfd_lookup((पूर्णांक)transport_eph, &err);
	अगर (!sock) अणु
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn,
				  "sockfd_lookup failed %d\n", err);
		वापस -EEXIST;
	पूर्ण

	err = iscsi_conn_bind(cls_session, cls_conn, is_leading);
	अगर (err)
		जाओ मुक्त_socket;

	spin_lock_bh(&session->frwd_lock);
	/* bind iSCSI connection and socket */
	tcp_sw_conn->sock = sock;
	spin_unlock_bh(&session->frwd_lock);

	/* setup Socket parameters */
	sk = sock->sk;
	sk->sk_reuse = SK_CAN_REUSE;
	sk->sk_sndसमयo = 15 * HZ; /* FIXME: make it configurable */
	sk->sk_allocation = GFP_ATOMIC;
	sk_set_meदो_स्मृति(sk);

	iscsi_sw_tcp_conn_set_callbacks(conn);
	tcp_sw_conn->sendpage = tcp_sw_conn->sock->ops->sendpage;
	/*
	 * set receive state machine पूर्णांकo initial state
	 */
	iscsi_tcp_hdr_recv_prep(tcp_conn);
	वापस 0;

मुक्त_socket:
	sockfd_put(sock);
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_sw_tcp_conn_set_param(काष्ठा iscsi_cls_conn *cls_conn,
				       क्रमागत iscsi_param param, अक्षर *buf,
				       पूर्णांक buflen)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	चयन(param) अणु
	हाल ISCSI_PARAM_HDRDGST_EN:
		iscsi_set_param(cls_conn, param, buf, buflen);
		अवरोध;
	हाल ISCSI_PARAM_DATADGST_EN:
		iscsi_set_param(cls_conn, param, buf, buflen);
		tcp_sw_conn->sendpage = conn->datadgst_en ?
			sock_no_sendpage : tcp_sw_conn->sock->ops->sendpage;
		अवरोध;
	हाल ISCSI_PARAM_MAX_R2T:
		वापस iscsi_tcp_set_max_r2t(conn, buf);
	शेष:
		वापस iscsi_set_param(cls_conn, param, buf, buflen);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_sw_tcp_conn_get_param(काष्ठा iscsi_cls_conn *cls_conn,
				       क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	काष्ठा sockaddr_in6 addr;
	काष्ठा socket *sock;
	पूर्णांक rc;

	चयन(param) अणु
	हाल ISCSI_PARAM_CONN_PORT:
	हाल ISCSI_PARAM_CONN_ADDRESS:
	हाल ISCSI_PARAM_LOCAL_PORT:
		spin_lock_bh(&conn->session->frwd_lock);
		अगर (!tcp_sw_conn || !tcp_sw_conn->sock) अणु
			spin_unlock_bh(&conn->session->frwd_lock);
			वापस -ENOTCONN;
		पूर्ण
		sock = tcp_sw_conn->sock;
		sock_hold(sock->sk);
		spin_unlock_bh(&conn->session->frwd_lock);

		अगर (param == ISCSI_PARAM_LOCAL_PORT)
			rc = kernel_माला_लोockname(sock,
						(काष्ठा sockaddr *)&addr);
		अन्यथा
			rc = kernel_getpeername(sock,
						(काष्ठा sockaddr *)&addr);
		sock_put(sock->sk);
		अगर (rc < 0)
			वापस rc;

		वापस iscsi_conn_get_addr_param((काष्ठा sockaddr_storage *)
						 &addr, param, buf);
	शेष:
		वापस iscsi_conn_get_param(cls_conn, param, buf);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_sw_tcp_host_get_param(काष्ठा Scsi_Host *shost,
				       क्रमागत iscsi_host_param param, अक्षर *buf)
अणु
	काष्ठा iscsi_sw_tcp_host *tcp_sw_host = iscsi_host_priv(shost);
	काष्ठा iscsi_session *session = tcp_sw_host->session;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_tcp_conn *tcp_conn;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn;
	काष्ठा sockaddr_in6 addr;
	काष्ठा socket *sock;
	पूर्णांक rc;

	चयन (param) अणु
	हाल ISCSI_HOST_PARAM_IPADDRESS:
		अगर (!session)
			वापस -ENOTCONN;

		spin_lock_bh(&session->frwd_lock);
		conn = session->leadconn;
		अगर (!conn) अणु
			spin_unlock_bh(&session->frwd_lock);
			वापस -ENOTCONN;
		पूर्ण
		tcp_conn = conn->dd_data;
		tcp_sw_conn = tcp_conn->dd_data;
		sock = tcp_sw_conn->sock;
		अगर (!sock) अणु
			spin_unlock_bh(&session->frwd_lock);
			वापस -ENOTCONN;
		पूर्ण
		sock_hold(sock->sk);
		spin_unlock_bh(&session->frwd_lock);

		rc = kernel_माला_लोockname(sock,
					(काष्ठा sockaddr *)&addr);
		sock_put(sock->sk);
		अगर (rc < 0)
			वापस rc;

		वापस iscsi_conn_get_addr_param((काष्ठा sockaddr_storage *)
						 &addr,
						 (क्रमागत iscsi_param)param, buf);
	शेष:
		वापस iscsi_host_get_param(shost, param, buf);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
iscsi_sw_tcp_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn,
			    काष्ठा iscsi_stats *stats)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	stats->custom_length = 3;
	म_नकल(stats->custom[0].desc, "tx_sendpage_failures");
	stats->custom[0].value = tcp_sw_conn->sendpage_failures_cnt;
	म_नकल(stats->custom[1].desc, "rx_discontiguous_hdr");
	stats->custom[1].value = tcp_sw_conn->discontiguous_hdr_cnt;
	म_नकल(stats->custom[2].desc, "eh_abort_cnt");
	stats->custom[2].value = conn->eh_पात_cnt;

	iscsi_tcp_conn_get_stats(cls_conn, stats);
पूर्ण

अटल काष्ठा iscsi_cls_session *
iscsi_sw_tcp_session_create(काष्ठा iscsi_endpoपूर्णांक *ep, uपूर्णांक16_t cmds_max,
			    uपूर्णांक16_t qdepth, uपूर्णांक32_t initial_cmdsn)
अणु
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा iscsi_session *session;
	काष्ठा iscsi_sw_tcp_host *tcp_sw_host;
	काष्ठा Scsi_Host *shost;
	पूर्णांक rc;

	अगर (ep) अणु
		prपूर्णांकk(KERN_ERR "iscsi_tcp: invalid ep %p.\n", ep);
		वापस शून्य;
	पूर्ण

	shost = iscsi_host_alloc(&iscsi_sw_tcp_sht,
				 माप(काष्ठा iscsi_sw_tcp_host), 1);
	अगर (!shost)
		वापस शून्य;
	shost->transportt = iscsi_sw_tcp_scsi_transport;
	shost->cmd_per_lun = qdepth;
	shost->max_lun = iscsi_max_lun;
	shost->max_id = 0;
	shost->max_channel = 0;
	shost->max_cmd_len = SCSI_MAX_VARLEN_CDB_SIZE;

	rc = iscsi_host_get_max_scsi_cmds(shost, cmds_max);
	अगर (rc < 0)
		जाओ मुक्त_host;
	shost->can_queue = rc;

	अगर (iscsi_host_add(shost, शून्य))
		जाओ मुक्त_host;

	cls_session = iscsi_session_setup(&iscsi_sw_tcp_transport, shost,
					  cmds_max, 0,
					  माप(काष्ठा iscsi_tcp_task) +
					  माप(काष्ठा iscsi_sw_tcp_hdrbuf),
					  initial_cmdsn, 0);
	अगर (!cls_session)
		जाओ हटाओ_host;
	session = cls_session->dd_data;
	tcp_sw_host = iscsi_host_priv(shost);
	tcp_sw_host->session = session;

	अगर (iscsi_tcp_r2tpool_alloc(session))
		जाओ हटाओ_session;
	वापस cls_session;

हटाओ_session:
	iscsi_session_tearकरोwn(cls_session);
हटाओ_host:
	iscsi_host_हटाओ(shost);
मुक्त_host:
	iscsi_host_मुक्त(shost);
	वापस शून्य;
पूर्ण

अटल व्योम iscsi_sw_tcp_session_destroy(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	काष्ठा iscsi_session *session = cls_session->dd_data;

	अगर (WARN_ON_ONCE(session->leadconn))
		वापस;

	iscsi_tcp_r2tpool_मुक्त(cls_session->dd_data);
	iscsi_session_tearकरोwn(cls_session);

	iscsi_host_हटाओ(shost);
	iscsi_host_मुक्त(shost);
पूर्ण

अटल umode_t iscsi_sw_tcp_attr_is_visible(पूर्णांक param_type, पूर्णांक param)
अणु
	चयन (param_type) अणु
	हाल ISCSI_HOST_PARAM:
		चयन (param) अणु
		हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		हाल ISCSI_HOST_PARAM_HWADDRESS:
		हाल ISCSI_HOST_PARAM_IPADDRESS:
		हाल ISCSI_HOST_PARAM_INITIATOR_NAME:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_PARAM:
		चयन (param) अणु
		हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		हाल ISCSI_PARAM_HDRDGST_EN:
		हाल ISCSI_PARAM_DATADGST_EN:
		हाल ISCSI_PARAM_CONN_ADDRESS:
		हाल ISCSI_PARAM_CONN_PORT:
		हाल ISCSI_PARAM_LOCAL_PORT:
		हाल ISCSI_PARAM_EXP_STATSN:
		हाल ISCSI_PARAM_PERSISTENT_ADDRESS:
		हाल ISCSI_PARAM_PERSISTENT_PORT:
		हाल ISCSI_PARAM_PING_TMO:
		हाल ISCSI_PARAM_RECV_TMO:
		हाल ISCSI_PARAM_INITIAL_R2T_EN:
		हाल ISCSI_PARAM_MAX_R2T:
		हाल ISCSI_PARAM_IMM_DATA_EN:
		हाल ISCSI_PARAM_FIRST_BURST:
		हाल ISCSI_PARAM_MAX_BURST:
		हाल ISCSI_PARAM_PDU_INORDER_EN:
		हाल ISCSI_PARAM_DATASEQ_INORDER_EN:
		हाल ISCSI_PARAM_ERL:
		हाल ISCSI_PARAM_TARGET_NAME:
		हाल ISCSI_PARAM_TPGT:
		हाल ISCSI_PARAM_USERNAME:
		हाल ISCSI_PARAM_PASSWORD:
		हाल ISCSI_PARAM_USERNAME_IN:
		हाल ISCSI_PARAM_PASSWORD_IN:
		हाल ISCSI_PARAM_FAST_ABORT:
		हाल ISCSI_PARAM_ABORT_TMO:
		हाल ISCSI_PARAM_LU_RESET_TMO:
		हाल ISCSI_PARAM_TGT_RESET_TMO:
		हाल ISCSI_PARAM_IFACE_NAME:
		हाल ISCSI_PARAM_INITIATOR_NAME:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_sw_tcp_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा iscsi_sw_tcp_host *tcp_sw_host = iscsi_host_priv(sdev->host);
	काष्ठा iscsi_session *session = tcp_sw_host->session;
	काष्ठा iscsi_conn *conn = session->leadconn;

	अगर (conn->datadgst_en)
		blk_queue_flag_set(QUEUE_FLAG_STABLE_WRITES,
				   sdev->request_queue);
	blk_queue_dma_alignment(sdev->request_queue, 0);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा iscsi_sw_tcp_sht = अणु
	.module			= THIS_MODULE,
	.name			= "iSCSI Initiator over TCP/IP",
	.queuecommand           = iscsi_queuecommand,
	.change_queue_depth	= scsi_change_queue_depth,
	.can_queue		= ISCSI_TOTAL_CMDS_MAX,
	.sg_tablesize		= 4096,
	.max_sectors		= 0xFFFF,
	.cmd_per_lun		= ISCSI_DEF_CMD_PER_LUN,
	.eh_समयd_out		= iscsi_eh_cmd_समयd_out,
	.eh_पात_handler       = iscsi_eh_पात,
	.eh_device_reset_handler= iscsi_eh_device_reset,
	.eh_target_reset_handler = iscsi_eh_recover_target,
	.dma_boundary		= PAGE_SIZE - 1,
	.slave_configure        = iscsi_sw_tcp_slave_configure,
	.target_alloc		= iscsi_target_alloc,
	.proc_name		= "iscsi_tcp",
	.this_id		= -1,
	.track_queue_depth	= 1,
पूर्ण;

अटल काष्ठा iscsi_transport iscsi_sw_tcp_transport = अणु
	.owner			= THIS_MODULE,
	.name			= "tcp",
	.caps			= CAP_RECOVERY_L0 | CAP_MULTI_R2T | CAP_HDRDGST
				  | CAP_DATADGST,
	/* session management */
	.create_session		= iscsi_sw_tcp_session_create,
	.destroy_session	= iscsi_sw_tcp_session_destroy,
	/* connection management */
	.create_conn		= iscsi_sw_tcp_conn_create,
	.bind_conn		= iscsi_sw_tcp_conn_bind,
	.destroy_conn		= iscsi_sw_tcp_conn_destroy,
	.attr_is_visible	= iscsi_sw_tcp_attr_is_visible,
	.set_param		= iscsi_sw_tcp_conn_set_param,
	.get_conn_param		= iscsi_sw_tcp_conn_get_param,
	.get_session_param	= iscsi_session_get_param,
	.start_conn		= iscsi_conn_start,
	.stop_conn		= iscsi_sw_tcp_conn_stop,
	/* iscsi host params */
	.get_host_param		= iscsi_sw_tcp_host_get_param,
	.set_host_param		= iscsi_host_set_param,
	/* IO */
	.send_pdu		= iscsi_conn_send_pdu,
	.get_stats		= iscsi_sw_tcp_conn_get_stats,
	/* iscsi task/cmd helpers */
	.init_task		= iscsi_tcp_task_init,
	.xmit_task		= iscsi_tcp_task_xmit,
	.cleanup_task		= iscsi_tcp_cleanup_task,
	/* low level pdu helpers */
	.xmit_pdu		= iscsi_sw_tcp_pdu_xmit,
	.init_pdu		= iscsi_sw_tcp_pdu_init,
	.alloc_pdu		= iscsi_sw_tcp_pdu_alloc,
	/* recovery */
	.session_recovery_समयकरोut = iscsi_session_recovery_समयकरोut,
पूर्ण;

अटल पूर्णांक __init iscsi_sw_tcp_init(व्योम)
अणु
	अगर (iscsi_max_lun < 1) अणु
		prपूर्णांकk(KERN_ERR "iscsi_tcp: Invalid max_lun value of %u\n",
		       iscsi_max_lun);
		वापस -EINVAL;
	पूर्ण

	iscsi_sw_tcp_scsi_transport = iscsi_रेजिस्टर_transport(
						&iscsi_sw_tcp_transport);
	अगर (!iscsi_sw_tcp_scsi_transport)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम __निकास iscsi_sw_tcp_निकास(व्योम)
अणु
	iscsi_unरेजिस्टर_transport(&iscsi_sw_tcp_transport);
पूर्ण

module_init(iscsi_sw_tcp_init);
module_निकास(iscsi_sw_tcp_निकास);
