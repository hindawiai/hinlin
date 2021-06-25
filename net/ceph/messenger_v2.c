<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ceph msgr2 protocol implementation
 *
 * Copyright (C) 2020 Ilya Dryomov <idryomov@gmail.com>
 */

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <crypto/aead.h>
#समावेश <crypto/algapi.h>  /* क्रम crypto_memneq() */
#समावेश <crypto/hash.h>
#समावेश <crypto/sha2.h>
#समावेश <linux/bvec.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/net.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/socket.h>
#समावेश <linux/sched/mm.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>

#समावेश <linux/ceph/ceph_features.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/messenger.h>

#समावेश "crypto.h"  /* क्रम CEPH_KEY_LEN and CEPH_MAX_CON_SECRET_LEN */

#घोषणा FRAME_TAG_HELLO			1
#घोषणा FRAME_TAG_AUTH_REQUEST		2
#घोषणा FRAME_TAG_AUTH_BAD_METHOD	3
#घोषणा FRAME_TAG_AUTH_REPLY_MORE	4
#घोषणा FRAME_TAG_AUTH_REQUEST_MORE	5
#घोषणा FRAME_TAG_AUTH_DONE		6
#घोषणा FRAME_TAG_AUTH_SIGNATURE	7
#घोषणा FRAME_TAG_CLIENT_IDENT		8
#घोषणा FRAME_TAG_SERVER_IDENT		9
#घोषणा FRAME_TAG_IDENT_MISSING_FEATURES 10
#घोषणा FRAME_TAG_SESSION_RECONNECT	11
#घोषणा FRAME_TAG_SESSION_RESET		12
#घोषणा FRAME_TAG_SESSION_RETRY		13
#घोषणा FRAME_TAG_SESSION_RETRY_GLOBAL	14
#घोषणा FRAME_TAG_SESSION_RECONNECT_OK	15
#घोषणा FRAME_TAG_WAIT			16
#घोषणा FRAME_TAG_MESSAGE		17
#घोषणा FRAME_TAG_KEEPALIVE2		18
#घोषणा FRAME_TAG_KEEPALIVE2_ACK	19
#घोषणा FRAME_TAG_ACK			20

#घोषणा FRAME_LATE_STATUS_ABORTED	0x1
#घोषणा FRAME_LATE_STATUS_COMPLETE	0xe
#घोषणा FRAME_LATE_STATUS_ABORTED_MASK	0xf

#घोषणा IN_S_HANDLE_PREAMBLE		1
#घोषणा IN_S_HANDLE_CONTROL		2
#घोषणा IN_S_HANDLE_CONTROL_REMAINDER	3
#घोषणा IN_S_PREPARE_READ_DATA		4
#घोषणा IN_S_PREPARE_READ_DATA_CONT	5
#घोषणा IN_S_HANDLE_EPILOGUE		6
#घोषणा IN_S_FINISH_SKIP		7

#घोषणा OUT_S_QUEUE_DATA		1
#घोषणा OUT_S_QUEUE_DATA_CONT		2
#घोषणा OUT_S_QUEUE_ENC_PAGE		3
#घोषणा OUT_S_QUEUE_ZEROS		4
#घोषणा OUT_S_FINISH_MESSAGE		5
#घोषणा OUT_S_GET_NEXT			6

#घोषणा CTRL_BODY(p)	((व्योम *)(p) + CEPH_PREAMBLE_LEN)
#घोषणा FRONT_PAD(p)	((व्योम *)(p) + CEPH_EPILOGUE_SECURE_LEN)
#घोषणा MIDDLE_PAD(p)	(FRONT_PAD(p) + CEPH_GCM_BLOCK_LEN)
#घोषणा DATA_PAD(p)	(MIDDLE_PAD(p) + CEPH_GCM_BLOCK_LEN)

#घोषणा CEPH_MSG_FLAGS (MSG_DONTWAIT | MSG_NOSIGNAL)

अटल पूर्णांक करो_recvmsg(काष्ठा socket *sock, काष्ठा iov_iter *it)
अणु
	काष्ठा msghdr msg = अणु .msg_flags = CEPH_MSG_FLAGS पूर्ण;
	पूर्णांक ret;

	msg.msg_iter = *it;
	जबतक (iov_iter_count(it)) अणु
		ret = sock_recvmsg(sock, &msg, msg.msg_flags);
		अगर (ret <= 0) अणु
			अगर (ret == -EAGAIN)
				ret = 0;
			वापस ret;
		पूर्ण

		iov_iter_advance(it, ret);
	पूर्ण

	WARN_ON(msg_data_left(&msg));
	वापस 1;
पूर्ण

/*
 * Read as much as possible.
 *
 * Return:
 *   1 - करोne, nothing (अन्यथा) to पढ़ो
 *   0 - socket is empty, need to रुको
 *  <0 - error
 */
अटल पूर्णांक ceph_tcp_recv(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret;

	करोut("%s con %p %s %zu\n", __func__, con,
	     iov_iter_is_discard(&con->v2.in_iter) ? "discard" : "need",
	     iov_iter_count(&con->v2.in_iter));
	ret = करो_recvmsg(con->sock, &con->v2.in_iter);
	करोut("%s con %p ret %d left %zu\n", __func__, con, ret,
	     iov_iter_count(&con->v2.in_iter));
	वापस ret;
पूर्ण

अटल पूर्णांक करो_sendmsg(काष्ठा socket *sock, काष्ठा iov_iter *it)
अणु
	काष्ठा msghdr msg = अणु .msg_flags = CEPH_MSG_FLAGS पूर्ण;
	पूर्णांक ret;

	msg.msg_iter = *it;
	जबतक (iov_iter_count(it)) अणु
		ret = sock_sendmsg(sock, &msg);
		अगर (ret <= 0) अणु
			अगर (ret == -EAGAIN)
				ret = 0;
			वापस ret;
		पूर्ण

		iov_iter_advance(it, ret);
	पूर्ण

	WARN_ON(msg_data_left(&msg));
	वापस 1;
पूर्ण

अटल पूर्णांक करो_try_sendpage(काष्ठा socket *sock, काष्ठा iov_iter *it)
अणु
	काष्ठा msghdr msg = अणु .msg_flags = CEPH_MSG_FLAGS पूर्ण;
	काष्ठा bio_vec bv;
	पूर्णांक ret;

	अगर (WARN_ON(!iov_iter_is_bvec(it)))
		वापस -EINVAL;

	जबतक (iov_iter_count(it)) अणु
		/* iov_iter_iovec() क्रम ITER_BVEC */
		bv.bv_page = it->bvec->bv_page;
		bv.bv_offset = it->bvec->bv_offset + it->iov_offset;
		bv.bv_len = min(iov_iter_count(it),
				it->bvec->bv_len - it->iov_offset);

		/*
		 * sendpage cannot properly handle pages with
		 * page_count == 0, we need to fall back to sendmsg अगर
		 * that's the हाल.
		 *
		 * Same goes क्रम slab pages: skb_can_coalesce() allows
		 * coalescing neighboring slab objects पूर्णांकo a single frag
		 * which triggers one of hardened usercopy checks.
		 */
		अगर (sendpage_ok(bv.bv_page)) अणु
			ret = sock->ops->sendpage(sock, bv.bv_page,
						  bv.bv_offset, bv.bv_len,
						  CEPH_MSG_FLAGS);
		पूर्ण अन्यथा अणु
			iov_iter_bvec(&msg.msg_iter, WRITE, &bv, 1, bv.bv_len);
			ret = sock_sendmsg(sock, &msg);
		पूर्ण
		अगर (ret <= 0) अणु
			अगर (ret == -EAGAIN)
				ret = 0;
			वापस ret;
		पूर्ण

		iov_iter_advance(it, ret);
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Write as much as possible.  The socket is expected to be corked,
 * so we करोn't bother with MSG_MORE/MSG_SENDPAGE_NOTLAST here.
 *
 * Return:
 *   1 - करोne, nothing (अन्यथा) to ग_लिखो
 *   0 - socket is full, need to रुको
 *  <0 - error
 */
अटल पूर्णांक ceph_tcp_send(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret;

	करोut("%s con %p have %zu try_sendpage %d\n", __func__, con,
	     iov_iter_count(&con->v2.out_iter), con->v2.out_iter_sendpage);
	अगर (con->v2.out_iter_sendpage)
		ret = करो_try_sendpage(con->sock, &con->v2.out_iter);
	अन्यथा
		ret = करो_sendmsg(con->sock, &con->v2.out_iter);
	करोut("%s con %p ret %d left %zu\n", __func__, con, ret,
	     iov_iter_count(&con->v2.out_iter));
	वापस ret;
पूर्ण

अटल व्योम add_in_kvec(काष्ठा ceph_connection *con, व्योम *buf, पूर्णांक len)
अणु
	BUG_ON(con->v2.in_kvec_cnt >= ARRAY_SIZE(con->v2.in_kvecs));
	WARN_ON(!iov_iter_is_kvec(&con->v2.in_iter));

	con->v2.in_kvecs[con->v2.in_kvec_cnt].iov_base = buf;
	con->v2.in_kvecs[con->v2.in_kvec_cnt].iov_len = len;
	con->v2.in_kvec_cnt++;

	con->v2.in_iter.nr_segs++;
	con->v2.in_iter.count += len;
पूर्ण

अटल व्योम reset_in_kvecs(काष्ठा ceph_connection *con)
अणु
	WARN_ON(iov_iter_count(&con->v2.in_iter));

	con->v2.in_kvec_cnt = 0;
	iov_iter_kvec(&con->v2.in_iter, READ, con->v2.in_kvecs, 0, 0);
पूर्ण

अटल व्योम set_in_bvec(काष्ठा ceph_connection *con, स्थिर काष्ठा bio_vec *bv)
अणु
	WARN_ON(iov_iter_count(&con->v2.in_iter));

	con->v2.in_bvec = *bv;
	iov_iter_bvec(&con->v2.in_iter, READ, &con->v2.in_bvec, 1, bv->bv_len);
पूर्ण

अटल व्योम set_in_skip(काष्ठा ceph_connection *con, पूर्णांक len)
अणु
	WARN_ON(iov_iter_count(&con->v2.in_iter));

	करोut("%s con %p len %d\n", __func__, con, len);
	iov_iter_discard(&con->v2.in_iter, READ, len);
पूर्ण

अटल व्योम add_out_kvec(काष्ठा ceph_connection *con, व्योम *buf, पूर्णांक len)
अणु
	BUG_ON(con->v2.out_kvec_cnt >= ARRAY_SIZE(con->v2.out_kvecs));
	WARN_ON(!iov_iter_is_kvec(&con->v2.out_iter));
	WARN_ON(con->v2.out_zero);

	con->v2.out_kvecs[con->v2.out_kvec_cnt].iov_base = buf;
	con->v2.out_kvecs[con->v2.out_kvec_cnt].iov_len = len;
	con->v2.out_kvec_cnt++;

	con->v2.out_iter.nr_segs++;
	con->v2.out_iter.count += len;
पूर्ण

अटल व्योम reset_out_kvecs(काष्ठा ceph_connection *con)
अणु
	WARN_ON(iov_iter_count(&con->v2.out_iter));
	WARN_ON(con->v2.out_zero);

	con->v2.out_kvec_cnt = 0;

	iov_iter_kvec(&con->v2.out_iter, WRITE, con->v2.out_kvecs, 0, 0);
	con->v2.out_iter_sendpage = false;
पूर्ण

अटल व्योम set_out_bvec(काष्ठा ceph_connection *con, स्थिर काष्ठा bio_vec *bv,
			 bool zerocopy)
अणु
	WARN_ON(iov_iter_count(&con->v2.out_iter));
	WARN_ON(con->v2.out_zero);

	con->v2.out_bvec = *bv;
	con->v2.out_iter_sendpage = zerocopy;
	iov_iter_bvec(&con->v2.out_iter, WRITE, &con->v2.out_bvec, 1,
		      con->v2.out_bvec.bv_len);
पूर्ण

अटल व्योम set_out_bvec_zero(काष्ठा ceph_connection *con)
अणु
	WARN_ON(iov_iter_count(&con->v2.out_iter));
	WARN_ON(!con->v2.out_zero);

	con->v2.out_bvec.bv_page = ceph_zero_page;
	con->v2.out_bvec.bv_offset = 0;
	con->v2.out_bvec.bv_len = min(con->v2.out_zero, (पूर्णांक)PAGE_SIZE);
	con->v2.out_iter_sendpage = true;
	iov_iter_bvec(&con->v2.out_iter, WRITE, &con->v2.out_bvec, 1,
		      con->v2.out_bvec.bv_len);
पूर्ण

अटल व्योम out_zero_add(काष्ठा ceph_connection *con, पूर्णांक len)
अणु
	करोut("%s con %p len %d\n", __func__, con, len);
	con->v2.out_zero += len;
पूर्ण

अटल व्योम *alloc_conn_buf(काष्ठा ceph_connection *con, पूर्णांक len)
अणु
	व्योम *buf;

	करोut("%s con %p len %d\n", __func__, con, len);

	अगर (WARN_ON(con->v2.conn_buf_cnt >= ARRAY_SIZE(con->v2.conn_bufs)))
		वापस शून्य;

	buf = ceph_kvदो_स्मृति(len, GFP_NOIO);
	अगर (!buf)
		वापस शून्य;

	con->v2.conn_bufs[con->v2.conn_buf_cnt++] = buf;
	वापस buf;
पूर्ण

अटल व्योम मुक्त_conn_bufs(काष्ठा ceph_connection *con)
अणु
	जबतक (con->v2.conn_buf_cnt)
		kvमुक्त(con->v2.conn_bufs[--con->v2.conn_buf_cnt]);
पूर्ण

अटल व्योम add_in_sign_kvec(काष्ठा ceph_connection *con, व्योम *buf, पूर्णांक len)
अणु
	BUG_ON(con->v2.in_sign_kvec_cnt >= ARRAY_SIZE(con->v2.in_sign_kvecs));

	con->v2.in_sign_kvecs[con->v2.in_sign_kvec_cnt].iov_base = buf;
	con->v2.in_sign_kvecs[con->v2.in_sign_kvec_cnt].iov_len = len;
	con->v2.in_sign_kvec_cnt++;
पूर्ण

अटल व्योम clear_in_sign_kvecs(काष्ठा ceph_connection *con)
अणु
	con->v2.in_sign_kvec_cnt = 0;
पूर्ण

अटल व्योम add_out_sign_kvec(काष्ठा ceph_connection *con, व्योम *buf, पूर्णांक len)
अणु
	BUG_ON(con->v2.out_sign_kvec_cnt >= ARRAY_SIZE(con->v2.out_sign_kvecs));

	con->v2.out_sign_kvecs[con->v2.out_sign_kvec_cnt].iov_base = buf;
	con->v2.out_sign_kvecs[con->v2.out_sign_kvec_cnt].iov_len = len;
	con->v2.out_sign_kvec_cnt++;
पूर्ण

अटल व्योम clear_out_sign_kvecs(काष्ठा ceph_connection *con)
अणु
	con->v2.out_sign_kvec_cnt = 0;
पूर्ण

अटल bool con_secure(काष्ठा ceph_connection *con)
अणु
	वापस con->v2.con_mode == CEPH_CON_MODE_SECURE;
पूर्ण

अटल पूर्णांक front_len(स्थिर काष्ठा ceph_msg *msg)
अणु
	वापस le32_to_cpu(msg->hdr.front_len);
पूर्ण

अटल पूर्णांक middle_len(स्थिर काष्ठा ceph_msg *msg)
अणु
	वापस le32_to_cpu(msg->hdr.middle_len);
पूर्ण

अटल पूर्णांक data_len(स्थिर काष्ठा ceph_msg *msg)
अणु
	वापस le32_to_cpu(msg->hdr.data_len);
पूर्ण

अटल bool need_padding(पूर्णांक len)
अणु
	वापस !IS_ALIGNED(len, CEPH_GCM_BLOCK_LEN);
पूर्ण

अटल पूर्णांक padded_len(पूर्णांक len)
अणु
	वापस ALIGN(len, CEPH_GCM_BLOCK_LEN);
पूर्ण

अटल पूर्णांक padding_len(पूर्णांक len)
अणु
	वापस padded_len(len) - len;
पूर्ण

/* preamble + control segment */
अटल पूर्णांक head_onwire_len(पूर्णांक ctrl_len, bool secure)
अणु
	पूर्णांक head_len;
	पूर्णांक rem_len;

	अगर (secure) अणु
		head_len = CEPH_PREAMBLE_SECURE_LEN;
		अगर (ctrl_len > CEPH_PREAMBLE_INLINE_LEN) अणु
			rem_len = ctrl_len - CEPH_PREAMBLE_INLINE_LEN;
			head_len += padded_len(rem_len) + CEPH_GCM_TAG_LEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		head_len = CEPH_PREAMBLE_PLAIN_LEN;
		अगर (ctrl_len)
			head_len += ctrl_len + CEPH_CRC_LEN;
	पूर्ण
	वापस head_len;
पूर्ण

/* front, middle and data segments + epilogue */
अटल पूर्णांक __tail_onwire_len(पूर्णांक front_len, पूर्णांक middle_len, पूर्णांक data_len,
			     bool secure)
अणु
	अगर (!front_len && !middle_len && !data_len)
		वापस 0;

	अगर (!secure)
		वापस front_len + middle_len + data_len +
		       CEPH_EPILOGUE_PLAIN_LEN;

	वापस padded_len(front_len) + padded_len(middle_len) +
	       padded_len(data_len) + CEPH_EPILOGUE_SECURE_LEN;
पूर्ण

अटल पूर्णांक tail_onwire_len(स्थिर काष्ठा ceph_msg *msg, bool secure)
अणु
	वापस __tail_onwire_len(front_len(msg), middle_len(msg),
				 data_len(msg), secure);
पूर्ण

/* head_onwire_len(माप(काष्ठा ceph_msg_header2), false) */
#घोषणा MESSAGE_HEAD_PLAIN_LEN	(CEPH_PREAMBLE_PLAIN_LEN +		\
				 माप(काष्ठा ceph_msg_header2) +	\
				 CEPH_CRC_LEN)

अटल स्थिर पूर्णांक frame_aligns[] = अणु
	माप(व्योम *),
	माप(व्योम *),
	माप(व्योम *),
	PAGE_SIZE
पूर्ण;

/*
 * Discards trailing empty segments, unless there is just one segment.
 * A frame always has at least one (possibly empty) segment.
 */
अटल पूर्णांक calc_segment_count(स्थिर पूर्णांक *lens, पूर्णांक len_cnt)
अणु
	पूर्णांक i;

	क्रम (i = len_cnt - 1; i >= 0; i--) अणु
		अगर (lens[i])
			वापस i + 1;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम init_frame_desc(काष्ठा ceph_frame_desc *desc, पूर्णांक tag,
			    स्थिर पूर्णांक *lens, पूर्णांक len_cnt)
अणु
	पूर्णांक i;

	स_रखो(desc, 0, माप(*desc));

	desc->fd_tag = tag;
	desc->fd_seg_cnt = calc_segment_count(lens, len_cnt);
	BUG_ON(desc->fd_seg_cnt > CEPH_FRAME_MAX_SEGMENT_COUNT);
	क्रम (i = 0; i < desc->fd_seg_cnt; i++) अणु
		desc->fd_lens[i] = lens[i];
		desc->fd_aligns[i] = frame_aligns[i];
	पूर्ण
पूर्ण

/*
 * Preamble crc covers everything up to itself (28 bytes) and
 * is calculated and verअगरied irrespective of the connection mode
 * (i.e. even अगर the frame is encrypted).
 */
अटल व्योम encode_preamble(स्थिर काष्ठा ceph_frame_desc *desc, व्योम *p)
अणु
	व्योम *crcp = p + CEPH_PREAMBLE_LEN - CEPH_CRC_LEN;
	व्योम *start = p;
	पूर्णांक i;

	स_रखो(p, 0, CEPH_PREAMBLE_LEN);

	ceph_encode_8(&p, desc->fd_tag);
	ceph_encode_8(&p, desc->fd_seg_cnt);
	क्रम (i = 0; i < desc->fd_seg_cnt; i++) अणु
		ceph_encode_32(&p, desc->fd_lens[i]);
		ceph_encode_16(&p, desc->fd_aligns[i]);
	पूर्ण

	put_unaligned_le32(crc32c(0, start, crcp - start), crcp);
पूर्ण

अटल पूर्णांक decode_preamble(व्योम *p, काष्ठा ceph_frame_desc *desc)
अणु
	व्योम *crcp = p + CEPH_PREAMBLE_LEN - CEPH_CRC_LEN;
	u32 crc, expected_crc;
	पूर्णांक i;

	crc = crc32c(0, p, crcp - p);
	expected_crc = get_unaligned_le32(crcp);
	अगर (crc != expected_crc) अणु
		pr_err("bad preamble crc, calculated %u, expected %u\n",
		       crc, expected_crc);
		वापस -EBADMSG;
	पूर्ण

	स_रखो(desc, 0, माप(*desc));

	desc->fd_tag = ceph_decode_8(&p);
	desc->fd_seg_cnt = ceph_decode_8(&p);
	अगर (desc->fd_seg_cnt < 1 ||
	    desc->fd_seg_cnt > CEPH_FRAME_MAX_SEGMENT_COUNT) अणु
		pr_err("bad segment count %d\n", desc->fd_seg_cnt);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < desc->fd_seg_cnt; i++) अणु
		desc->fd_lens[i] = ceph_decode_32(&p);
		desc->fd_aligns[i] = ceph_decode_16(&p);
	पूर्ण

	/*
	 * This would fire क्रम FRAME_TAG_WAIT (it has one empty
	 * segment), but we should never get it as client.
	 */
	अगर (!desc->fd_lens[desc->fd_seg_cnt - 1]) अणु
		pr_err("last segment empty\n");
		वापस -EINVAL;
	पूर्ण

	अगर (desc->fd_lens[0] > CEPH_MSG_MAX_CONTROL_LEN) अणु
		pr_err("control segment too big %d\n", desc->fd_lens[0]);
		वापस -EINVAL;
	पूर्ण
	अगर (desc->fd_lens[1] > CEPH_MSG_MAX_FRONT_LEN) अणु
		pr_err("front segment too big %d\n", desc->fd_lens[1]);
		वापस -EINVAL;
	पूर्ण
	अगर (desc->fd_lens[2] > CEPH_MSG_MAX_MIDDLE_LEN) अणु
		pr_err("middle segment too big %d\n", desc->fd_lens[2]);
		वापस -EINVAL;
	पूर्ण
	अगर (desc->fd_lens[3] > CEPH_MSG_MAX_DATA_LEN) अणु
		pr_err("data segment too big %d\n", desc->fd_lens[3]);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम encode_epilogue_plain(काष्ठा ceph_connection *con, bool पातed)
अणु
	con->v2.out_epil.late_status = पातed ? FRAME_LATE_STATUS_ABORTED :
						 FRAME_LATE_STATUS_COMPLETE;
	cpu_to_le32s(&con->v2.out_epil.front_crc);
	cpu_to_le32s(&con->v2.out_epil.middle_crc);
	cpu_to_le32s(&con->v2.out_epil.data_crc);
पूर्ण

अटल व्योम encode_epilogue_secure(काष्ठा ceph_connection *con, bool पातed)
अणु
	स_रखो(&con->v2.out_epil, 0, माप(con->v2.out_epil));
	con->v2.out_epil.late_status = पातed ? FRAME_LATE_STATUS_ABORTED :
						 FRAME_LATE_STATUS_COMPLETE;
पूर्ण

अटल पूर्णांक decode_epilogue(व्योम *p, u32 *front_crc, u32 *middle_crc,
			   u32 *data_crc)
अणु
	u8 late_status;

	late_status = ceph_decode_8(&p);
	अगर ((late_status & FRAME_LATE_STATUS_ABORTED_MASK) !=
			FRAME_LATE_STATUS_COMPLETE) अणु
		/* we should never get an पातed message as client */
		pr_err("bad late_status 0x%x\n", late_status);
		वापस -EINVAL;
	पूर्ण

	अगर (front_crc && middle_crc && data_crc) अणु
		*front_crc = ceph_decode_32(&p);
		*middle_crc = ceph_decode_32(&p);
		*data_crc = ceph_decode_32(&p);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fill_header(काष्ठा ceph_msg_header *hdr,
			स्थिर काष्ठा ceph_msg_header2 *hdr2,
			पूर्णांक front_len, पूर्णांक middle_len, पूर्णांक data_len,
			स्थिर काष्ठा ceph_entity_name *peer_name)
अणु
	hdr->seq = hdr2->seq;
	hdr->tid = hdr2->tid;
	hdr->type = hdr2->type;
	hdr->priority = hdr2->priority;
	hdr->version = hdr2->version;
	hdr->front_len = cpu_to_le32(front_len);
	hdr->middle_len = cpu_to_le32(middle_len);
	hdr->data_len = cpu_to_le32(data_len);
	hdr->data_off = hdr2->data_off;
	hdr->src = *peer_name;
	hdr->compat_version = hdr2->compat_version;
	hdr->reserved = 0;
	hdr->crc = 0;
पूर्ण

अटल व्योम fill_header2(काष्ठा ceph_msg_header2 *hdr2,
			 स्थिर काष्ठा ceph_msg_header *hdr, u64 ack_seq)
अणु
	hdr2->seq = hdr->seq;
	hdr2->tid = hdr->tid;
	hdr2->type = hdr->type;
	hdr2->priority = hdr->priority;
	hdr2->version = hdr->version;
	hdr2->data_pre_padding_len = 0;
	hdr2->data_off = hdr->data_off;
	hdr2->ack_seq = cpu_to_le64(ack_seq);
	hdr2->flags = 0;
	hdr2->compat_version = hdr->compat_version;
	hdr2->reserved = 0;
पूर्ण

अटल पूर्णांक verअगरy_control_crc(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ctrl_len = con->v2.in_desc.fd_lens[0];
	u32 crc, expected_crc;

	WARN_ON(con->v2.in_kvecs[0].iov_len != ctrl_len);
	WARN_ON(con->v2.in_kvecs[1].iov_len != CEPH_CRC_LEN);

	crc = crc32c(-1, con->v2.in_kvecs[0].iov_base, ctrl_len);
	expected_crc = get_unaligned_le32(con->v2.in_kvecs[1].iov_base);
	अगर (crc != expected_crc) अणु
		pr_err("bad control crc, calculated %u, expected %u\n",
		       crc, expected_crc);
		वापस -EBADMSG;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_epilogue_crcs(काष्ठा ceph_connection *con, u32 front_crc,
				u32 middle_crc, u32 data_crc)
अणु
	अगर (front_len(con->in_msg)) अणु
		con->in_front_crc = crc32c(-1, con->in_msg->front.iov_base,
					   front_len(con->in_msg));
	पूर्ण अन्यथा अणु
		WARN_ON(!middle_len(con->in_msg) && !data_len(con->in_msg));
		con->in_front_crc = -1;
	पूर्ण

	अगर (middle_len(con->in_msg))
		con->in_middle_crc = crc32c(-1,
					    con->in_msg->middle->vec.iov_base,
					    middle_len(con->in_msg));
	अन्यथा अगर (data_len(con->in_msg))
		con->in_middle_crc = -1;
	अन्यथा
		con->in_middle_crc = 0;

	अगर (!data_len(con->in_msg))
		con->in_data_crc = 0;

	करोut("%s con %p msg %p crcs %u %u %u\n", __func__, con, con->in_msg,
	     con->in_front_crc, con->in_middle_crc, con->in_data_crc);

	अगर (con->in_front_crc != front_crc) अणु
		pr_err("bad front crc, calculated %u, expected %u\n",
		       con->in_front_crc, front_crc);
		वापस -EBADMSG;
	पूर्ण
	अगर (con->in_middle_crc != middle_crc) अणु
		pr_err("bad middle crc, calculated %u, expected %u\n",
		       con->in_middle_crc, middle_crc);
		वापस -EBADMSG;
	पूर्ण
	अगर (con->in_data_crc != data_crc) अणु
		pr_err("bad data crc, calculated %u, expected %u\n",
		       con->in_data_crc, data_crc);
		वापस -EBADMSG;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_crypto(काष्ठा ceph_connection *con,
			स्थिर u8 *session_key, पूर्णांक session_key_len,
			स्थिर u8 *con_secret, पूर्णांक con_secret_len)
अणु
	अचिन्हित पूर्णांक noio_flag;
	पूर्णांक ret;

	करोut("%s con %p con_mode %d session_key_len %d con_secret_len %d\n",
	     __func__, con, con->v2.con_mode, session_key_len, con_secret_len);
	WARN_ON(con->v2.hmac_tfm || con->v2.gcm_tfm || con->v2.gcm_req);

	अगर (con->v2.con_mode != CEPH_CON_MODE_CRC &&
	    con->v2.con_mode != CEPH_CON_MODE_SECURE) अणु
		pr_err("bad con_mode %d\n", con->v2.con_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (!session_key_len) अणु
		WARN_ON(con->v2.con_mode != CEPH_CON_MODE_CRC);
		WARN_ON(con_secret_len);
		वापस 0;  /* auth_none */
	पूर्ण

	noio_flag = meदो_स्मृति_noio_save();
	con->v2.hmac_tfm = crypto_alloc_shash("hmac(sha256)", 0, 0);
	meदो_स्मृति_noio_restore(noio_flag);
	अगर (IS_ERR(con->v2.hmac_tfm)) अणु
		ret = PTR_ERR(con->v2.hmac_tfm);
		con->v2.hmac_tfm = शून्य;
		pr_err("failed to allocate hmac tfm context: %d\n", ret);
		वापस ret;
	पूर्ण

	WARN_ON((अचिन्हित दीर्घ)session_key &
		crypto_shash_alignmask(con->v2.hmac_tfm));
	ret = crypto_shash_setkey(con->v2.hmac_tfm, session_key,
				  session_key_len);
	अगर (ret) अणु
		pr_err("failed to set hmac key: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (con->v2.con_mode == CEPH_CON_MODE_CRC) अणु
		WARN_ON(con_secret_len);
		वापस 0;  /* auth_x, plain mode */
	पूर्ण

	अगर (con_secret_len < CEPH_GCM_KEY_LEN + 2 * CEPH_GCM_IV_LEN) अणु
		pr_err("con_secret too small %d\n", con_secret_len);
		वापस -EINVAL;
	पूर्ण

	noio_flag = meदो_स्मृति_noio_save();
	con->v2.gcm_tfm = crypto_alloc_aead("gcm(aes)", 0, 0);
	meदो_स्मृति_noio_restore(noio_flag);
	अगर (IS_ERR(con->v2.gcm_tfm)) अणु
		ret = PTR_ERR(con->v2.gcm_tfm);
		con->v2.gcm_tfm = शून्य;
		pr_err("failed to allocate gcm tfm context: %d\n", ret);
		वापस ret;
	पूर्ण

	WARN_ON((अचिन्हित दीर्घ)con_secret &
		crypto_aead_alignmask(con->v2.gcm_tfm));
	ret = crypto_aead_setkey(con->v2.gcm_tfm, con_secret, CEPH_GCM_KEY_LEN);
	अगर (ret) अणु
		pr_err("failed to set gcm key: %d\n", ret);
		वापस ret;
	पूर्ण

	WARN_ON(crypto_aead_ivsize(con->v2.gcm_tfm) != CEPH_GCM_IV_LEN);
	ret = crypto_aead_setauthsize(con->v2.gcm_tfm, CEPH_GCM_TAG_LEN);
	अगर (ret) अणु
		pr_err("failed to set gcm tag size: %d\n", ret);
		वापस ret;
	पूर्ण

	con->v2.gcm_req = aead_request_alloc(con->v2.gcm_tfm, GFP_NOIO);
	अगर (!con->v2.gcm_req) अणु
		pr_err("failed to allocate gcm request\n");
		वापस -ENOMEM;
	पूर्ण

	crypto_init_रुको(&con->v2.gcm_रुको);
	aead_request_set_callback(con->v2.gcm_req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  crypto_req_करोne, &con->v2.gcm_रुको);

	स_नकल(&con->v2.in_gcm_nonce, con_secret + CEPH_GCM_KEY_LEN,
	       CEPH_GCM_IV_LEN);
	स_नकल(&con->v2.out_gcm_nonce,
	       con_secret + CEPH_GCM_KEY_LEN + CEPH_GCM_IV_LEN,
	       CEPH_GCM_IV_LEN);
	वापस 0;  /* auth_x, secure mode */
पूर्ण

अटल पूर्णांक hmac_sha256(काष्ठा ceph_connection *con, स्थिर काष्ठा kvec *kvecs,
		       पूर्णांक kvec_cnt, u8 *hmac)
अणु
	SHASH_DESC_ON_STACK(desc, con->v2.hmac_tfm);  /* tfm arg is ignored */
	पूर्णांक ret;
	पूर्णांक i;

	करोut("%s con %p hmac_tfm %p kvec_cnt %d\n", __func__, con,
	     con->v2.hmac_tfm, kvec_cnt);

	अगर (!con->v2.hmac_tfm) अणु
		स_रखो(hmac, 0, SHA256_DIGEST_SIZE);
		वापस 0;  /* auth_none */
	पूर्ण

	desc->tfm = con->v2.hmac_tfm;
	ret = crypto_shash_init(desc);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < kvec_cnt; i++) अणु
		WARN_ON((अचिन्हित दीर्घ)kvecs[i].iov_base &
			crypto_shash_alignmask(con->v2.hmac_tfm));
		ret = crypto_shash_update(desc, kvecs[i].iov_base,
					  kvecs[i].iov_len);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = crypto_shash_final(desc, hmac);

out:
	shash_desc_zero(desc);
	वापस ret;  /* auth_x, both plain and secure modes */
पूर्ण

अटल व्योम gcm_inc_nonce(काष्ठा ceph_gcm_nonce *nonce)
अणु
	u64 counter;

	counter = le64_to_cpu(nonce->counter);
	nonce->counter = cpu_to_le64(counter + 1);
पूर्ण

अटल पूर्णांक gcm_crypt(काष्ठा ceph_connection *con, bool encrypt,
		     काष्ठा scatterlist *src, काष्ठा scatterlist *dst,
		     पूर्णांक src_len)
अणु
	काष्ठा ceph_gcm_nonce *nonce;
	पूर्णांक ret;

	nonce = encrypt ? &con->v2.out_gcm_nonce : &con->v2.in_gcm_nonce;

	aead_request_set_ad(con->v2.gcm_req, 0);  /* no AAD */
	aead_request_set_crypt(con->v2.gcm_req, src, dst, src_len, (u8 *)nonce);
	ret = crypto_रुको_req(encrypt ? crypto_aead_encrypt(con->v2.gcm_req) :
					crypto_aead_decrypt(con->v2.gcm_req),
			      &con->v2.gcm_रुको);
	अगर (ret)
		वापस ret;

	gcm_inc_nonce(nonce);
	वापस 0;
पूर्ण

अटल व्योम get_bvec_at(काष्ठा ceph_msg_data_cursor *cursor,
			काष्ठा bio_vec *bv)
अणु
	काष्ठा page *page;
	माप_प्रकार off, len;

	WARN_ON(!cursor->total_resid);

	/* skip zero-length data items */
	जबतक (!cursor->resid)
		ceph_msg_data_advance(cursor, 0);

	/* get a piece of data, cursor isn't advanced */
	page = ceph_msg_data_next(cursor, &off, &len, शून्य);

	bv->bv_page = page;
	bv->bv_offset = off;
	bv->bv_len = len;
पूर्ण

अटल पूर्णांक calc_sg_cnt(व्योम *buf, पूर्णांक buf_len)
अणु
	पूर्णांक sg_cnt;

	अगर (!buf_len)
		वापस 0;

	sg_cnt = need_padding(buf_len) ? 1 : 0;
	अगर (is_vदो_स्मृति_addr(buf)) अणु
		WARN_ON(offset_in_page(buf));
		sg_cnt += PAGE_ALIGN(buf_len) >> PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		sg_cnt++;
	पूर्ण

	वापस sg_cnt;
पूर्ण

अटल पूर्णांक calc_sg_cnt_cursor(काष्ठा ceph_msg_data_cursor *cursor)
अणु
	पूर्णांक data_len = cursor->total_resid;
	काष्ठा bio_vec bv;
	पूर्णांक sg_cnt;

	अगर (!data_len)
		वापस 0;

	sg_cnt = need_padding(data_len) ? 1 : 0;
	करो अणु
		get_bvec_at(cursor, &bv);
		sg_cnt++;

		ceph_msg_data_advance(cursor, bv.bv_len);
	पूर्ण जबतक (cursor->total_resid);

	वापस sg_cnt;
पूर्ण

अटल व्योम init_sgs(काष्ठा scatterlist **sg, व्योम *buf, पूर्णांक buf_len, u8 *pad)
अणु
	व्योम *end = buf + buf_len;
	काष्ठा page *page;
	पूर्णांक len;
	व्योम *p;

	अगर (!buf_len)
		वापस;

	अगर (is_vदो_स्मृति_addr(buf)) अणु
		p = buf;
		करो अणु
			page = vदो_स्मृति_to_page(p);
			len = min_t(पूर्णांक, end - p, PAGE_SIZE);
			WARN_ON(!page || !len || offset_in_page(p));
			sg_set_page(*sg, page, len, 0);
			*sg = sg_next(*sg);
			p += len;
		पूर्ण जबतक (p != end);
	पूर्ण अन्यथा अणु
		sg_set_buf(*sg, buf, buf_len);
		*sg = sg_next(*sg);
	पूर्ण

	अगर (need_padding(buf_len)) अणु
		sg_set_buf(*sg, pad, padding_len(buf_len));
		*sg = sg_next(*sg);
	पूर्ण
पूर्ण

अटल व्योम init_sgs_cursor(काष्ठा scatterlist **sg,
			    काष्ठा ceph_msg_data_cursor *cursor, u8 *pad)
अणु
	पूर्णांक data_len = cursor->total_resid;
	काष्ठा bio_vec bv;

	अगर (!data_len)
		वापस;

	करो अणु
		get_bvec_at(cursor, &bv);
		sg_set_page(*sg, bv.bv_page, bv.bv_len, bv.bv_offset);
		*sg = sg_next(*sg);

		ceph_msg_data_advance(cursor, bv.bv_len);
	पूर्ण जबतक (cursor->total_resid);

	अगर (need_padding(data_len)) अणु
		sg_set_buf(*sg, pad, padding_len(data_len));
		*sg = sg_next(*sg);
	पूर्ण
पूर्ण

अटल पूर्णांक setup_message_sgs(काष्ठा sg_table *sgt, काष्ठा ceph_msg *msg,
			     u8 *front_pad, u8 *middle_pad, u8 *data_pad,
			     व्योम *epilogue, bool add_tag)
अणु
	काष्ठा ceph_msg_data_cursor cursor;
	काष्ठा scatterlist *cur_sg;
	पूर्णांक sg_cnt;
	पूर्णांक ret;

	अगर (!front_len(msg) && !middle_len(msg) && !data_len(msg))
		वापस 0;

	sg_cnt = 1;  /* epilogue + [auth tag] */
	अगर (front_len(msg))
		sg_cnt += calc_sg_cnt(msg->front.iov_base,
				      front_len(msg));
	अगर (middle_len(msg))
		sg_cnt += calc_sg_cnt(msg->middle->vec.iov_base,
				      middle_len(msg));
	अगर (data_len(msg)) अणु
		ceph_msg_data_cursor_init(&cursor, msg, data_len(msg));
		sg_cnt += calc_sg_cnt_cursor(&cursor);
	पूर्ण

	ret = sg_alloc_table(sgt, sg_cnt, GFP_NOIO);
	अगर (ret)
		वापस ret;

	cur_sg = sgt->sgl;
	अगर (front_len(msg))
		init_sgs(&cur_sg, msg->front.iov_base, front_len(msg),
			 front_pad);
	अगर (middle_len(msg))
		init_sgs(&cur_sg, msg->middle->vec.iov_base, middle_len(msg),
			 middle_pad);
	अगर (data_len(msg)) अणु
		ceph_msg_data_cursor_init(&cursor, msg, data_len(msg));
		init_sgs_cursor(&cur_sg, &cursor, data_pad);
	पूर्ण

	WARN_ON(!sg_is_last(cur_sg));
	sg_set_buf(cur_sg, epilogue,
		   CEPH_GCM_BLOCK_LEN + (add_tag ? CEPH_GCM_TAG_LEN : 0));
	वापस 0;
पूर्ण

अटल पूर्णांक decrypt_preamble(काष्ठा ceph_connection *con)
अणु
	काष्ठा scatterlist sg;

	sg_init_one(&sg, con->v2.in_buf, CEPH_PREAMBLE_SECURE_LEN);
	वापस gcm_crypt(con, false, &sg, &sg, CEPH_PREAMBLE_SECURE_LEN);
पूर्ण

अटल पूर्णांक decrypt_control_reमुख्यder(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ctrl_len = con->v2.in_desc.fd_lens[0];
	पूर्णांक rem_len = ctrl_len - CEPH_PREAMBLE_INLINE_LEN;
	पूर्णांक pt_len = padding_len(rem_len) + CEPH_GCM_TAG_LEN;
	काष्ठा scatterlist sgs[2];

	WARN_ON(con->v2.in_kvecs[0].iov_len != rem_len);
	WARN_ON(con->v2.in_kvecs[1].iov_len != pt_len);

	sg_init_table(sgs, 2);
	sg_set_buf(&sgs[0], con->v2.in_kvecs[0].iov_base, rem_len);
	sg_set_buf(&sgs[1], con->v2.in_buf, pt_len);

	वापस gcm_crypt(con, false, sgs, sgs,
			 padded_len(rem_len) + CEPH_GCM_TAG_LEN);
पूर्ण

अटल पूर्णांक decrypt_message(काष्ठा ceph_connection *con)
अणु
	काष्ठा sg_table sgt = अणुपूर्ण;
	पूर्णांक ret;

	ret = setup_message_sgs(&sgt, con->in_msg, FRONT_PAD(con->v2.in_buf),
			MIDDLE_PAD(con->v2.in_buf), DATA_PAD(con->v2.in_buf),
			con->v2.in_buf, true);
	अगर (ret)
		जाओ out;

	ret = gcm_crypt(con, false, sgt.sgl, sgt.sgl,
			tail_onwire_len(con->in_msg, true));

out:
	sg_मुक्त_table(&sgt);
	वापस ret;
पूर्ण

अटल पूर्णांक prepare_banner(काष्ठा ceph_connection *con)
अणु
	पूर्णांक buf_len = CEPH_BANNER_V2_LEN + 2 + 8 + 8;
	व्योम *buf, *p;

	buf = alloc_conn_buf(con, buf_len);
	अगर (!buf)
		वापस -ENOMEM;

	p = buf;
	ceph_encode_copy(&p, CEPH_BANNER_V2, CEPH_BANNER_V2_LEN);
	ceph_encode_16(&p, माप(u64) + माप(u64));
	ceph_encode_64(&p, CEPH_MSGR2_SUPPORTED_FEATURES);
	ceph_encode_64(&p, CEPH_MSGR2_REQUIRED_FEATURES);
	WARN_ON(p != buf + buf_len);

	add_out_kvec(con, buf, buf_len);
	add_out_sign_kvec(con, buf, buf_len);
	ceph_con_flag_set(con, CEPH_CON_F_WRITE_PENDING);
	वापस 0;
पूर्ण

/*
 * base:
 *   preamble
 *   control body (ctrl_len bytes)
 *   space क्रम control crc
 *
 * extdata (optional):
 *   control body (extdata_len bytes)
 *
 * Compute control crc and gather base and extdata पूर्णांकo:
 *
 *   preamble
 *   control body (ctrl_len + extdata_len bytes)
 *   control crc
 *
 * Preamble should alपढ़ोy be encoded at the start of base.
 */
अटल व्योम prepare_head_plain(काष्ठा ceph_connection *con, व्योम *base,
			       पूर्णांक ctrl_len, व्योम *extdata, पूर्णांक extdata_len,
			       bool to_be_चिन्हित)
अणु
	पूर्णांक base_len = CEPH_PREAMBLE_LEN + ctrl_len + CEPH_CRC_LEN;
	व्योम *crcp = base + base_len - CEPH_CRC_LEN;
	u32 crc;

	crc = crc32c(-1, CTRL_BODY(base), ctrl_len);
	अगर (extdata_len)
		crc = crc32c(crc, extdata, extdata_len);
	put_unaligned_le32(crc, crcp);

	अगर (!extdata_len) अणु
		add_out_kvec(con, base, base_len);
		अगर (to_be_चिन्हित)
			add_out_sign_kvec(con, base, base_len);
		वापस;
	पूर्ण

	add_out_kvec(con, base, crcp - base);
	add_out_kvec(con, extdata, extdata_len);
	add_out_kvec(con, crcp, CEPH_CRC_LEN);
	अगर (to_be_चिन्हित) अणु
		add_out_sign_kvec(con, base, crcp - base);
		add_out_sign_kvec(con, extdata, extdata_len);
		add_out_sign_kvec(con, crcp, CEPH_CRC_LEN);
	पूर्ण
पूर्ण

अटल पूर्णांक prepare_head_secure_small(काष्ठा ceph_connection *con,
				     व्योम *base, पूर्णांक ctrl_len)
अणु
	काष्ठा scatterlist sg;
	पूर्णांक ret;

	/* अंतरभूत buffer padding? */
	अगर (ctrl_len < CEPH_PREAMBLE_INLINE_LEN)
		स_रखो(CTRL_BODY(base) + ctrl_len, 0,
		       CEPH_PREAMBLE_INLINE_LEN - ctrl_len);

	sg_init_one(&sg, base, CEPH_PREAMBLE_SECURE_LEN);
	ret = gcm_crypt(con, true, &sg, &sg,
			CEPH_PREAMBLE_SECURE_LEN - CEPH_GCM_TAG_LEN);
	अगर (ret)
		वापस ret;

	add_out_kvec(con, base, CEPH_PREAMBLE_SECURE_LEN);
	वापस 0;
पूर्ण

/*
 * base:
 *   preamble
 *   control body (ctrl_len bytes)
 *   space क्रम padding, अगर needed
 *   space क्रम control reमुख्यder auth tag
 *   space क्रम preamble auth tag
 *
 * Encrypt preamble and the अंतरभूत portion, then encrypt the reमुख्यder
 * and gather पूर्णांकo:
 *
 *   preamble
 *   control body (48 bytes)
 *   preamble auth tag
 *   control body (ctrl_len - 48 bytes)
 *   zero padding, अगर needed
 *   control reमुख्यder auth tag
 *
 * Preamble should alपढ़ोy be encoded at the start of base.
 */
अटल पूर्णांक prepare_head_secure_big(काष्ठा ceph_connection *con,
				   व्योम *base, पूर्णांक ctrl_len)
अणु
	पूर्णांक rem_len = ctrl_len - CEPH_PREAMBLE_INLINE_LEN;
	व्योम *rem = CTRL_BODY(base) + CEPH_PREAMBLE_INLINE_LEN;
	व्योम *rem_tag = rem + padded_len(rem_len);
	व्योम *pmbl_tag = rem_tag + CEPH_GCM_TAG_LEN;
	काष्ठा scatterlist sgs[2];
	पूर्णांक ret;

	sg_init_table(sgs, 2);
	sg_set_buf(&sgs[0], base, rem - base);
	sg_set_buf(&sgs[1], pmbl_tag, CEPH_GCM_TAG_LEN);
	ret = gcm_crypt(con, true, sgs, sgs, rem - base);
	अगर (ret)
		वापस ret;

	/* control reमुख्यder padding? */
	अगर (need_padding(rem_len))
		स_रखो(rem + rem_len, 0, padding_len(rem_len));

	sg_init_one(&sgs[0], rem, pmbl_tag - rem);
	ret = gcm_crypt(con, true, sgs, sgs, rem_tag - rem);
	अगर (ret)
		वापस ret;

	add_out_kvec(con, base, rem - base);
	add_out_kvec(con, pmbl_tag, CEPH_GCM_TAG_LEN);
	add_out_kvec(con, rem, pmbl_tag - rem);
	वापस 0;
पूर्ण

अटल पूर्णांक __prepare_control(काष्ठा ceph_connection *con, पूर्णांक tag,
			     व्योम *base, पूर्णांक ctrl_len, व्योम *extdata,
			     पूर्णांक extdata_len, bool to_be_चिन्हित)
अणु
	पूर्णांक total_len = ctrl_len + extdata_len;
	काष्ठा ceph_frame_desc desc;
	पूर्णांक ret;

	करोut("%s con %p tag %d len %d (%d+%d)\n", __func__, con, tag,
	     total_len, ctrl_len, extdata_len);

	/* extdata may be vदो_स्मृति'ed but not base */
	अगर (WARN_ON(is_vदो_स्मृति_addr(base) || !ctrl_len))
		वापस -EINVAL;

	init_frame_desc(&desc, tag, &total_len, 1);
	encode_preamble(&desc, base);

	अगर (con_secure(con)) अणु
		अगर (WARN_ON(extdata_len || to_be_चिन्हित))
			वापस -EINVAL;

		अगर (ctrl_len <= CEPH_PREAMBLE_INLINE_LEN)
			/* fully अंतरभूतd, अंतरभूत buffer may need padding */
			ret = prepare_head_secure_small(con, base, ctrl_len);
		अन्यथा
			/* partially अंतरभूतd, अंतरभूत buffer is full */
			ret = prepare_head_secure_big(con, base, ctrl_len);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		prepare_head_plain(con, base, ctrl_len, extdata, extdata_len,
				   to_be_चिन्हित);
	पूर्ण

	ceph_con_flag_set(con, CEPH_CON_F_WRITE_PENDING);
	वापस 0;
पूर्ण

अटल पूर्णांक prepare_control(काष्ठा ceph_connection *con, पूर्णांक tag,
			   व्योम *base, पूर्णांक ctrl_len)
अणु
	वापस __prepare_control(con, tag, base, ctrl_len, शून्य, 0, false);
पूर्ण

अटल पूर्णांक prepare_hello(काष्ठा ceph_connection *con)
अणु
	व्योम *buf, *p;
	पूर्णांक ctrl_len;

	ctrl_len = 1 + ceph_entity_addr_encoding_len(&con->peer_addr);
	buf = alloc_conn_buf(con, head_onwire_len(ctrl_len, false));
	अगर (!buf)
		वापस -ENOMEM;

	p = CTRL_BODY(buf);
	ceph_encode_8(&p, CEPH_ENTITY_TYPE_CLIENT);
	ceph_encode_entity_addr(&p, &con->peer_addr);
	WARN_ON(p != CTRL_BODY(buf) + ctrl_len);

	वापस __prepare_control(con, FRAME_TAG_HELLO, buf, ctrl_len,
				 शून्य, 0, true);
पूर्ण

/* so that head_onwire_len(AUTH_BUF_LEN, false) is 512 */
#घोषणा AUTH_BUF_LEN	(512 - CEPH_CRC_LEN - CEPH_PREAMBLE_PLAIN_LEN)

अटल पूर्णांक prepare_auth_request(काष्ठा ceph_connection *con)
अणु
	व्योम *authorizer, *authorizer_copy;
	पूर्णांक ctrl_len, authorizer_len;
	व्योम *buf;
	पूर्णांक ret;

	ctrl_len = AUTH_BUF_LEN;
	buf = alloc_conn_buf(con, head_onwire_len(ctrl_len, false));
	अगर (!buf)
		वापस -ENOMEM;

	mutex_unlock(&con->mutex);
	ret = con->ops->get_auth_request(con, CTRL_BODY(buf), &ctrl_len,
					 &authorizer, &authorizer_len);
	mutex_lock(&con->mutex);
	अगर (con->state != CEPH_CON_S_V2_HELLO) अणु
		करोut("%s con %p state changed to %d\n", __func__, con,
		     con->state);
		वापस -EAGAIN;
	पूर्ण

	करोut("%s con %p get_auth_request ret %d\n", __func__, con, ret);
	अगर (ret)
		वापस ret;

	authorizer_copy = alloc_conn_buf(con, authorizer_len);
	अगर (!authorizer_copy)
		वापस -ENOMEM;

	स_नकल(authorizer_copy, authorizer, authorizer_len);

	वापस __prepare_control(con, FRAME_TAG_AUTH_REQUEST, buf, ctrl_len,
				 authorizer_copy, authorizer_len, true);
पूर्ण

अटल पूर्णांक prepare_auth_request_more(काष्ठा ceph_connection *con,
				     व्योम *reply, पूर्णांक reply_len)
अणु
	पूर्णांक ctrl_len, authorizer_len;
	व्योम *authorizer;
	व्योम *buf;
	पूर्णांक ret;

	ctrl_len = AUTH_BUF_LEN;
	buf = alloc_conn_buf(con, head_onwire_len(ctrl_len, false));
	अगर (!buf)
		वापस -ENOMEM;

	mutex_unlock(&con->mutex);
	ret = con->ops->handle_auth_reply_more(con, reply, reply_len,
					       CTRL_BODY(buf), &ctrl_len,
					       &authorizer, &authorizer_len);
	mutex_lock(&con->mutex);
	अगर (con->state != CEPH_CON_S_V2_AUTH) अणु
		करोut("%s con %p state changed to %d\n", __func__, con,
		     con->state);
		वापस -EAGAIN;
	पूर्ण

	करोut("%s con %p handle_auth_reply_more ret %d\n", __func__, con, ret);
	अगर (ret)
		वापस ret;

	वापस __prepare_control(con, FRAME_TAG_AUTH_REQUEST_MORE, buf,
				 ctrl_len, authorizer, authorizer_len, true);
पूर्ण

अटल पूर्णांक prepare_auth_signature(काष्ठा ceph_connection *con)
अणु
	व्योम *buf;
	पूर्णांक ret;

	buf = alloc_conn_buf(con, head_onwire_len(SHA256_DIGEST_SIZE,
						  con_secure(con)));
	अगर (!buf)
		वापस -ENOMEM;

	ret = hmac_sha256(con, con->v2.in_sign_kvecs, con->v2.in_sign_kvec_cnt,
			  CTRL_BODY(buf));
	अगर (ret)
		वापस ret;

	वापस prepare_control(con, FRAME_TAG_AUTH_SIGNATURE, buf,
			       SHA256_DIGEST_SIZE);
पूर्ण

अटल पूर्णांक prepare_client_ident(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_entity_addr *my_addr = &con->msgr->inst.addr;
	काष्ठा ceph_client *client = from_msgr(con->msgr);
	u64 global_id = ceph_client_gid(client);
	व्योम *buf, *p;
	पूर्णांक ctrl_len;

	WARN_ON(con->v2.server_cookie);
	WARN_ON(con->v2.connect_seq);
	WARN_ON(con->v2.peer_global_seq);

	अगर (!con->v2.client_cookie) अणु
		करो अणु
			get_अक्रमom_bytes(&con->v2.client_cookie,
					 माप(con->v2.client_cookie));
		पूर्ण जबतक (!con->v2.client_cookie);
		करोut("%s con %p generated cookie 0x%llx\n", __func__, con,
		     con->v2.client_cookie);
	पूर्ण अन्यथा अणु
		करोut("%s con %p cookie already set 0x%llx\n", __func__, con,
		     con->v2.client_cookie);
	पूर्ण

	करोut("%s con %p my_addr %s/%u peer_addr %s/%u global_id %llu global_seq %llu features 0x%llx required_features 0x%llx cookie 0x%llx\n",
	     __func__, con, ceph_pr_addr(my_addr), le32_to_cpu(my_addr->nonce),
	     ceph_pr_addr(&con->peer_addr), le32_to_cpu(con->peer_addr.nonce),
	     global_id, con->v2.global_seq, client->supported_features,
	     client->required_features, con->v2.client_cookie);

	ctrl_len = 1 + 4 + ceph_entity_addr_encoding_len(my_addr) +
		   ceph_entity_addr_encoding_len(&con->peer_addr) + 6 * 8;
	buf = alloc_conn_buf(con, head_onwire_len(ctrl_len, con_secure(con)));
	अगर (!buf)
		वापस -ENOMEM;

	p = CTRL_BODY(buf);
	ceph_encode_8(&p, 2);  /* addrvec marker */
	ceph_encode_32(&p, 1);  /* addr_cnt */
	ceph_encode_entity_addr(&p, my_addr);
	ceph_encode_entity_addr(&p, &con->peer_addr);
	ceph_encode_64(&p, global_id);
	ceph_encode_64(&p, con->v2.global_seq);
	ceph_encode_64(&p, client->supported_features);
	ceph_encode_64(&p, client->required_features);
	ceph_encode_64(&p, 0);  /* flags */
	ceph_encode_64(&p, con->v2.client_cookie);
	WARN_ON(p != CTRL_BODY(buf) + ctrl_len);

	वापस prepare_control(con, FRAME_TAG_CLIENT_IDENT, buf, ctrl_len);
पूर्ण

अटल पूर्णांक prepare_session_reconnect(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_entity_addr *my_addr = &con->msgr->inst.addr;
	व्योम *buf, *p;
	पूर्णांक ctrl_len;

	WARN_ON(!con->v2.client_cookie);
	WARN_ON(!con->v2.server_cookie);
	WARN_ON(!con->v2.connect_seq);
	WARN_ON(!con->v2.peer_global_seq);

	करोut("%s con %p my_addr %s/%u client_cookie 0x%llx server_cookie 0x%llx global_seq %llu connect_seq %llu in_seq %llu\n",
	     __func__, con, ceph_pr_addr(my_addr), le32_to_cpu(my_addr->nonce),
	     con->v2.client_cookie, con->v2.server_cookie, con->v2.global_seq,
	     con->v2.connect_seq, con->in_seq);

	ctrl_len = 1 + 4 + ceph_entity_addr_encoding_len(my_addr) + 5 * 8;
	buf = alloc_conn_buf(con, head_onwire_len(ctrl_len, con_secure(con)));
	अगर (!buf)
		वापस -ENOMEM;

	p = CTRL_BODY(buf);
	ceph_encode_8(&p, 2);  /* entity_addrvec_t marker */
	ceph_encode_32(&p, 1);  /* my_addrs len */
	ceph_encode_entity_addr(&p, my_addr);
	ceph_encode_64(&p, con->v2.client_cookie);
	ceph_encode_64(&p, con->v2.server_cookie);
	ceph_encode_64(&p, con->v2.global_seq);
	ceph_encode_64(&p, con->v2.connect_seq);
	ceph_encode_64(&p, con->in_seq);
	WARN_ON(p != CTRL_BODY(buf) + ctrl_len);

	वापस prepare_control(con, FRAME_TAG_SESSION_RECONNECT, buf, ctrl_len);
पूर्ण

अटल पूर्णांक prepare_keepalive2(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_बारpec *ts = CTRL_BODY(con->v2.out_buf);
	काष्ठा बारpec64 now;

	kसमय_get_real_ts64(&now);
	करोut("%s con %p timestamp %lld.%09ld\n", __func__, con, now.tv_sec,
	     now.tv_nsec);

	ceph_encode_बारpec64(ts, &now);

	reset_out_kvecs(con);
	वापस prepare_control(con, FRAME_TAG_KEEPALIVE2, con->v2.out_buf,
			       माप(काष्ठा ceph_बारpec));
पूर्ण

अटल पूर्णांक prepare_ack(काष्ठा ceph_connection *con)
अणु
	व्योम *p;

	करोut("%s con %p in_seq_acked %llu -> %llu\n", __func__, con,
	     con->in_seq_acked, con->in_seq);
	con->in_seq_acked = con->in_seq;

	p = CTRL_BODY(con->v2.out_buf);
	ceph_encode_64(&p, con->in_seq_acked);

	reset_out_kvecs(con);
	वापस prepare_control(con, FRAME_TAG_ACK, con->v2.out_buf, 8);
पूर्ण

अटल व्योम prepare_epilogue_plain(काष्ठा ceph_connection *con, bool पातed)
अणु
	करोut("%s con %p msg %p aborted %d crcs %u %u %u\n", __func__, con,
	     con->out_msg, पातed, con->v2.out_epil.front_crc,
	     con->v2.out_epil.middle_crc, con->v2.out_epil.data_crc);

	encode_epilogue_plain(con, पातed);
	add_out_kvec(con, &con->v2.out_epil, CEPH_EPILOGUE_PLAIN_LEN);
पूर्ण

/*
 * For "used" empty segments, crc is -1.  For unused (trailing)
 * segments, crc is 0.
 */
अटल व्योम prepare_message_plain(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_msg *msg = con->out_msg;

	prepare_head_plain(con, con->v2.out_buf,
			   माप(काष्ठा ceph_msg_header2), शून्य, 0, false);

	अगर (!front_len(msg) && !middle_len(msg)) अणु
		अगर (!data_len(msg)) अणु
			/*
			 * Empty message: once the head is written,
			 * we are करोne -- there is no epilogue.
			 */
			con->v2.out_state = OUT_S_FINISH_MESSAGE;
			वापस;
		पूर्ण

		con->v2.out_epil.front_crc = -1;
		con->v2.out_epil.middle_crc = -1;
		con->v2.out_state = OUT_S_QUEUE_DATA;
		वापस;
	पूर्ण

	अगर (front_len(msg)) अणु
		con->v2.out_epil.front_crc = crc32c(-1, msg->front.iov_base,
						    front_len(msg));
		add_out_kvec(con, msg->front.iov_base, front_len(msg));
	पूर्ण अन्यथा अणु
		/* middle (at least) is there, checked above */
		con->v2.out_epil.front_crc = -1;
	पूर्ण

	अगर (middle_len(msg)) अणु
		con->v2.out_epil.middle_crc =
			crc32c(-1, msg->middle->vec.iov_base, middle_len(msg));
		add_out_kvec(con, msg->middle->vec.iov_base, middle_len(msg));
	पूर्ण अन्यथा अणु
		con->v2.out_epil.middle_crc = data_len(msg) ? -1 : 0;
	पूर्ण

	अगर (data_len(msg)) अणु
		con->v2.out_state = OUT_S_QUEUE_DATA;
	पूर्ण अन्यथा अणु
		con->v2.out_epil.data_crc = 0;
		prepare_epilogue_plain(con, false);
		con->v2.out_state = OUT_S_FINISH_MESSAGE;
	पूर्ण
पूर्ण

/*
 * Unक्रमtunately the kernel crypto API करोesn't support streaming
 * (piecewise) operation क्रम AEAD algorithms, so we can't get away
 * with a fixed size buffer and a couple sgs.  Instead, we have to
 * allocate pages क्रम the entire tail of the message (currently up
 * to ~32M) and two sgs arrays (up to ~256K each)...
 */
अटल पूर्णांक prepare_message_secure(काष्ठा ceph_connection *con)
अणु
	व्योम *zerop = page_address(ceph_zero_page);
	काष्ठा sg_table enc_sgt = अणुपूर्ण;
	काष्ठा sg_table sgt = अणुपूर्ण;
	काष्ठा page **enc_pages;
	पूर्णांक enc_page_cnt;
	पूर्णांक tail_len;
	पूर्णांक ret;

	ret = prepare_head_secure_small(con, con->v2.out_buf,
					माप(काष्ठा ceph_msg_header2));
	अगर (ret)
		वापस ret;

	tail_len = tail_onwire_len(con->out_msg, true);
	अगर (!tail_len) अणु
		/*
		 * Empty message: once the head is written,
		 * we are करोne -- there is no epilogue.
		 */
		con->v2.out_state = OUT_S_FINISH_MESSAGE;
		वापस 0;
	पूर्ण

	encode_epilogue_secure(con, false);
	ret = setup_message_sgs(&sgt, con->out_msg, zerop, zerop, zerop,
				&con->v2.out_epil, false);
	अगर (ret)
		जाओ out;

	enc_page_cnt = calc_pages_क्रम(0, tail_len);
	enc_pages = ceph_alloc_page_vector(enc_page_cnt, GFP_NOIO);
	अगर (IS_ERR(enc_pages)) अणु
		ret = PTR_ERR(enc_pages);
		जाओ out;
	पूर्ण

	WARN_ON(con->v2.out_enc_pages || con->v2.out_enc_page_cnt);
	con->v2.out_enc_pages = enc_pages;
	con->v2.out_enc_page_cnt = enc_page_cnt;
	con->v2.out_enc_resid = tail_len;
	con->v2.out_enc_i = 0;

	ret = sg_alloc_table_from_pages(&enc_sgt, enc_pages, enc_page_cnt,
					0, tail_len, GFP_NOIO);
	अगर (ret)
		जाओ out;

	ret = gcm_crypt(con, true, sgt.sgl, enc_sgt.sgl,
			tail_len - CEPH_GCM_TAG_LEN);
	अगर (ret)
		जाओ out;

	करोut("%s con %p msg %p sg_cnt %d enc_page_cnt %d\n", __func__, con,
	     con->out_msg, sgt.orig_nents, enc_page_cnt);
	con->v2.out_state = OUT_S_QUEUE_ENC_PAGE;

out:
	sg_मुक्त_table(&sgt);
	sg_मुक्त_table(&enc_sgt);
	वापस ret;
पूर्ण

अटल पूर्णांक prepare_message(काष्ठा ceph_connection *con)
अणु
	पूर्णांक lens[] = अणु
		माप(काष्ठा ceph_msg_header2),
		front_len(con->out_msg),
		middle_len(con->out_msg),
		data_len(con->out_msg)
	पूर्ण;
	काष्ठा ceph_frame_desc desc;
	पूर्णांक ret;

	करोut("%s con %p msg %p logical %d+%d+%d+%d\n", __func__, con,
	     con->out_msg, lens[0], lens[1], lens[2], lens[3]);

	अगर (con->in_seq > con->in_seq_acked) अणु
		करोut("%s con %p in_seq_acked %llu -> %llu\n", __func__, con,
		     con->in_seq_acked, con->in_seq);
		con->in_seq_acked = con->in_seq;
	पूर्ण

	reset_out_kvecs(con);
	init_frame_desc(&desc, FRAME_TAG_MESSAGE, lens, 4);
	encode_preamble(&desc, con->v2.out_buf);
	fill_header2(CTRL_BODY(con->v2.out_buf), &con->out_msg->hdr,
		     con->in_seq_acked);

	अगर (con_secure(con)) अणु
		ret = prepare_message_secure(con);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		prepare_message_plain(con);
	पूर्ण

	ceph_con_flag_set(con, CEPH_CON_F_WRITE_PENDING);
	वापस 0;
पूर्ण

अटल पूर्णांक prepare_पढ़ो_banner_prefix(काष्ठा ceph_connection *con)
अणु
	व्योम *buf;

	buf = alloc_conn_buf(con, CEPH_BANNER_V2_PREFIX_LEN);
	अगर (!buf)
		वापस -ENOMEM;

	reset_in_kvecs(con);
	add_in_kvec(con, buf, CEPH_BANNER_V2_PREFIX_LEN);
	add_in_sign_kvec(con, buf, CEPH_BANNER_V2_PREFIX_LEN);
	con->state = CEPH_CON_S_V2_BANNER_PREFIX;
	वापस 0;
पूर्ण

अटल पूर्णांक prepare_पढ़ो_banner_payload(काष्ठा ceph_connection *con,
				       पूर्णांक payload_len)
अणु
	व्योम *buf;

	buf = alloc_conn_buf(con, payload_len);
	अगर (!buf)
		वापस -ENOMEM;

	reset_in_kvecs(con);
	add_in_kvec(con, buf, payload_len);
	add_in_sign_kvec(con, buf, payload_len);
	con->state = CEPH_CON_S_V2_BANNER_PAYLOAD;
	वापस 0;
पूर्ण

अटल व्योम prepare_पढ़ो_preamble(काष्ठा ceph_connection *con)
अणु
	reset_in_kvecs(con);
	add_in_kvec(con, con->v2.in_buf,
		    con_secure(con) ? CEPH_PREAMBLE_SECURE_LEN :
				      CEPH_PREAMBLE_PLAIN_LEN);
	con->v2.in_state = IN_S_HANDLE_PREAMBLE;
पूर्ण

अटल पूर्णांक prepare_पढ़ो_control(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ctrl_len = con->v2.in_desc.fd_lens[0];
	पूर्णांक head_len;
	व्योम *buf;

	reset_in_kvecs(con);
	अगर (con->state == CEPH_CON_S_V2_HELLO ||
	    con->state == CEPH_CON_S_V2_AUTH) अणु
		head_len = head_onwire_len(ctrl_len, false);
		buf = alloc_conn_buf(con, head_len);
		अगर (!buf)
			वापस -ENOMEM;

		/* preserve preamble */
		स_नकल(buf, con->v2.in_buf, CEPH_PREAMBLE_LEN);

		add_in_kvec(con, CTRL_BODY(buf), ctrl_len);
		add_in_kvec(con, CTRL_BODY(buf) + ctrl_len, CEPH_CRC_LEN);
		add_in_sign_kvec(con, buf, head_len);
	पूर्ण अन्यथा अणु
		अगर (ctrl_len > CEPH_PREAMBLE_INLINE_LEN) अणु
			buf = alloc_conn_buf(con, ctrl_len);
			अगर (!buf)
				वापस -ENOMEM;

			add_in_kvec(con, buf, ctrl_len);
		पूर्ण अन्यथा अणु
			add_in_kvec(con, CTRL_BODY(con->v2.in_buf), ctrl_len);
		पूर्ण
		add_in_kvec(con, con->v2.in_buf, CEPH_CRC_LEN);
	पूर्ण
	con->v2.in_state = IN_S_HANDLE_CONTROL;
	वापस 0;
पूर्ण

अटल पूर्णांक prepare_पढ़ो_control_reमुख्यder(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ctrl_len = con->v2.in_desc.fd_lens[0];
	पूर्णांक rem_len = ctrl_len - CEPH_PREAMBLE_INLINE_LEN;
	व्योम *buf;

	buf = alloc_conn_buf(con, ctrl_len);
	अगर (!buf)
		वापस -ENOMEM;

	स_नकल(buf, CTRL_BODY(con->v2.in_buf), CEPH_PREAMBLE_INLINE_LEN);

	reset_in_kvecs(con);
	add_in_kvec(con, buf + CEPH_PREAMBLE_INLINE_LEN, rem_len);
	add_in_kvec(con, con->v2.in_buf,
		    padding_len(rem_len) + CEPH_GCM_TAG_LEN);
	con->v2.in_state = IN_S_HANDLE_CONTROL_REMAINDER;
	वापस 0;
पूर्ण

अटल व्योम prepare_पढ़ो_data(काष्ठा ceph_connection *con)
अणु
	काष्ठा bio_vec bv;

	अगर (!con_secure(con))
		con->in_data_crc = -1;
	ceph_msg_data_cursor_init(&con->v2.in_cursor, con->in_msg,
				  data_len(con->in_msg));

	get_bvec_at(&con->v2.in_cursor, &bv);
	set_in_bvec(con, &bv);
	con->v2.in_state = IN_S_PREPARE_READ_DATA_CONT;
पूर्ण

अटल व्योम prepare_पढ़ो_data_cont(काष्ठा ceph_connection *con)
अणु
	काष्ठा bio_vec bv;

	अगर (!con_secure(con))
		con->in_data_crc = ceph_crc32c_page(con->in_data_crc,
						    con->v2.in_bvec.bv_page,
						    con->v2.in_bvec.bv_offset,
						    con->v2.in_bvec.bv_len);

	ceph_msg_data_advance(&con->v2.in_cursor, con->v2.in_bvec.bv_len);
	अगर (con->v2.in_cursor.total_resid) अणु
		get_bvec_at(&con->v2.in_cursor, &bv);
		set_in_bvec(con, &bv);
		WARN_ON(con->v2.in_state != IN_S_PREPARE_READ_DATA_CONT);
		वापस;
	पूर्ण

	/*
	 * We've पढ़ो all data.  Prepare to पढ़ो data padding (अगर any)
	 * and epilogue.
	 */
	reset_in_kvecs(con);
	अगर (con_secure(con)) अणु
		अगर (need_padding(data_len(con->in_msg)))
			add_in_kvec(con, DATA_PAD(con->v2.in_buf),
				    padding_len(data_len(con->in_msg)));
		add_in_kvec(con, con->v2.in_buf, CEPH_EPILOGUE_SECURE_LEN);
	पूर्ण अन्यथा अणु
		add_in_kvec(con, con->v2.in_buf, CEPH_EPILOGUE_PLAIN_LEN);
	पूर्ण
	con->v2.in_state = IN_S_HANDLE_EPILOGUE;
पूर्ण

अटल व्योम __finish_skip(काष्ठा ceph_connection *con)
अणु
	con->in_seq++;
	prepare_पढ़ो_preamble(con);
पूर्ण

अटल व्योम prepare_skip_message(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_frame_desc *desc = &con->v2.in_desc;
	पूर्णांक tail_len;

	करोut("%s con %p %d+%d+%d\n", __func__, con, desc->fd_lens[1],
	     desc->fd_lens[2], desc->fd_lens[3]);

	tail_len = __tail_onwire_len(desc->fd_lens[1], desc->fd_lens[2],
				     desc->fd_lens[3], con_secure(con));
	अगर (!tail_len) अणु
		__finish_skip(con);
	पूर्ण अन्यथा अणु
		set_in_skip(con, tail_len);
		con->v2.in_state = IN_S_FINISH_SKIP;
	पूर्ण
पूर्ण

अटल पूर्णांक process_banner_prefix(काष्ठा ceph_connection *con)
अणु
	पूर्णांक payload_len;
	व्योम *p;

	WARN_ON(con->v2.in_kvecs[0].iov_len != CEPH_BANNER_V2_PREFIX_LEN);

	p = con->v2.in_kvecs[0].iov_base;
	अगर (स_भेद(p, CEPH_BANNER_V2, CEPH_BANNER_V2_LEN)) अणु
		अगर (!स_भेद(p, CEPH_BANNER, CEPH_BANNER_LEN))
			con->error_msg = "server is speaking msgr1 protocol";
		अन्यथा
			con->error_msg = "protocol error, bad banner";
		वापस -EINVAL;
	पूर्ण

	p += CEPH_BANNER_V2_LEN;
	payload_len = ceph_decode_16(&p);
	करोut("%s con %p payload_len %d\n", __func__, con, payload_len);

	वापस prepare_पढ़ो_banner_payload(con, payload_len);
पूर्ण

अटल पूर्णांक process_banner_payload(काष्ठा ceph_connection *con)
अणु
	व्योम *end = con->v2.in_kvecs[0].iov_base + con->v2.in_kvecs[0].iov_len;
	u64 feat = CEPH_MSGR2_SUPPORTED_FEATURES;
	u64 req_feat = CEPH_MSGR2_REQUIRED_FEATURES;
	u64 server_feat, server_req_feat;
	व्योम *p;
	पूर्णांक ret;

	p = con->v2.in_kvecs[0].iov_base;
	ceph_decode_64_safe(&p, end, server_feat, bad);
	ceph_decode_64_safe(&p, end, server_req_feat, bad);

	करोut("%s con %p server_feat 0x%llx server_req_feat 0x%llx\n",
	     __func__, con, server_feat, server_req_feat);

	अगर (req_feat & ~server_feat) अणु
		pr_err("msgr2 feature set mismatch: my required > server's supported 0x%llx, need 0x%llx\n",
		       server_feat, req_feat & ~server_feat);
		con->error_msg = "missing required protocol features";
		वापस -EINVAL;
	पूर्ण
	अगर (server_req_feat & ~feat) अणु
		pr_err("msgr2 feature set mismatch: server's required > my supported 0x%llx, missing 0x%llx\n",
		       feat, server_req_feat & ~feat);
		con->error_msg = "missing required protocol features";
		वापस -EINVAL;
	पूर्ण

	/* no reset_out_kvecs() as our banner may still be pending */
	ret = prepare_hello(con);
	अगर (ret) अणु
		pr_err("prepare_hello failed: %d\n", ret);
		वापस ret;
	पूर्ण

	con->state = CEPH_CON_S_V2_HELLO;
	prepare_पढ़ो_preamble(con);
	वापस 0;

bad:
	pr_err("failed to decode banner payload\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_hello(काष्ठा ceph_connection *con, व्योम *p, व्योम *end)
अणु
	काष्ठा ceph_entity_addr *my_addr = &con->msgr->inst.addr;
	काष्ठा ceph_entity_addr addr_क्रम_me;
	u8 entity_type;
	पूर्णांक ret;

	अगर (con->state != CEPH_CON_S_V2_HELLO) अणु
		con->error_msg = "protocol error, unexpected hello";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_8_safe(&p, end, entity_type, bad);
	ret = ceph_decode_entity_addr(&p, end, &addr_क्रम_me);
	अगर (ret) अणु
		pr_err("failed to decode addr_for_me: %d\n", ret);
		वापस ret;
	पूर्ण

	करोut("%s con %p entity_type %d addr_for_me %s\n", __func__, con,
	     entity_type, ceph_pr_addr(&addr_क्रम_me));

	अगर (entity_type != con->peer_name.type) अणु
		pr_err("bad peer type, want %d, got %d\n",
		       con->peer_name.type, entity_type);
		con->error_msg = "wrong peer at address";
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set our address to the address our first peer (i.e. monitor)
	 * sees that we are connecting from.  If we are behind some sort
	 * of NAT and want to be identअगरied by some निजी (not NATed)
	 * address, ip option should be used.
	 */
	अगर (ceph_addr_is_blank(my_addr)) अणु
		स_नकल(&my_addr->in_addr, &addr_क्रम_me.in_addr,
		       माप(my_addr->in_addr));
		ceph_addr_set_port(my_addr, 0);
		करोut("%s con %p set my addr %s, as seen by peer %s\n",
		     __func__, con, ceph_pr_addr(my_addr),
		     ceph_pr_addr(&con->peer_addr));
	पूर्ण अन्यथा अणु
		करोut("%s con %p my addr already set %s\n",
		     __func__, con, ceph_pr_addr(my_addr));
	पूर्ण

	WARN_ON(ceph_addr_is_blank(my_addr) || ceph_addr_port(my_addr));
	WARN_ON(my_addr->type != CEPH_ENTITY_ADDR_TYPE_ANY);
	WARN_ON(!my_addr->nonce);

	/* no reset_out_kvecs() as our hello may still be pending */
	ret = prepare_auth_request(con);
	अगर (ret) अणु
		अगर (ret != -EAGAIN)
			pr_err("prepare_auth_request failed: %d\n", ret);
		वापस ret;
	पूर्ण

	con->state = CEPH_CON_S_V2_AUTH;
	वापस 0;

bad:
	pr_err("failed to decode hello\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_auth_bad_method(काष्ठा ceph_connection *con,
				   व्योम *p, व्योम *end)
अणु
	पूर्णांक allowed_protos[8], allowed_modes[8];
	पूर्णांक allowed_proto_cnt, allowed_mode_cnt;
	पूर्णांक used_proto, result;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (con->state != CEPH_CON_S_V2_AUTH) अणु
		con->error_msg = "protocol error, unexpected auth_bad_method";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_32_safe(&p, end, used_proto, bad);
	ceph_decode_32_safe(&p, end, result, bad);
	करोut("%s con %p used_proto %d result %d\n", __func__, con, used_proto,
	     result);

	ceph_decode_32_safe(&p, end, allowed_proto_cnt, bad);
	अगर (allowed_proto_cnt > ARRAY_SIZE(allowed_protos)) अणु
		pr_err("allowed_protos too big %d\n", allowed_proto_cnt);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < allowed_proto_cnt; i++) अणु
		ceph_decode_32_safe(&p, end, allowed_protos[i], bad);
		करोut("%s con %p allowed_protos[%d] %d\n", __func__, con,
		     i, allowed_protos[i]);
	पूर्ण

	ceph_decode_32_safe(&p, end, allowed_mode_cnt, bad);
	अगर (allowed_mode_cnt > ARRAY_SIZE(allowed_modes)) अणु
		pr_err("allowed_modes too big %d\n", allowed_mode_cnt);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < allowed_mode_cnt; i++) अणु
		ceph_decode_32_safe(&p, end, allowed_modes[i], bad);
		करोut("%s con %p allowed_modes[%d] %d\n", __func__, con,
		     i, allowed_modes[i]);
	पूर्ण

	mutex_unlock(&con->mutex);
	ret = con->ops->handle_auth_bad_method(con, used_proto, result,
					       allowed_protos,
					       allowed_proto_cnt,
					       allowed_modes,
					       allowed_mode_cnt);
	mutex_lock(&con->mutex);
	अगर (con->state != CEPH_CON_S_V2_AUTH) अणु
		करोut("%s con %p state changed to %d\n", __func__, con,
		     con->state);
		वापस -EAGAIN;
	पूर्ण

	करोut("%s con %p handle_auth_bad_method ret %d\n", __func__, con, ret);
	वापस ret;

bad:
	pr_err("failed to decode auth_bad_method\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_auth_reply_more(काष्ठा ceph_connection *con,
				   व्योम *p, व्योम *end)
अणु
	पूर्णांक payload_len;
	पूर्णांक ret;

	अगर (con->state != CEPH_CON_S_V2_AUTH) अणु
		con->error_msg = "protocol error, unexpected auth_reply_more";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_32_safe(&p, end, payload_len, bad);
	ceph_decode_need(&p, end, payload_len, bad);

	करोut("%s con %p payload_len %d\n", __func__, con, payload_len);

	reset_out_kvecs(con);
	ret = prepare_auth_request_more(con, p, payload_len);
	अगर (ret) अणु
		अगर (ret != -EAGAIN)
			pr_err("prepare_auth_request_more failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;

bad:
	pr_err("failed to decode auth_reply_more\n");
	वापस -EINVAL;
पूर्ण

/*
 * Align session_key and con_secret to aव्योम GFP_ATOMIC allocation
 * inside crypto_shash_setkey() and crypto_aead_setkey() called from
 * setup_crypto().  __aligned(16) isn't guaranteed to work क्रम stack
 * objects, so करो it by hand.
 */
अटल पूर्णांक process_auth_करोne(काष्ठा ceph_connection *con, व्योम *p, व्योम *end)
अणु
	u8 session_key_buf[CEPH_KEY_LEN + 16];
	u8 con_secret_buf[CEPH_MAX_CON_SECRET_LEN + 16];
	u8 *session_key = PTR_ALIGN(&session_key_buf[0], 16);
	u8 *con_secret = PTR_ALIGN(&con_secret_buf[0], 16);
	पूर्णांक session_key_len, con_secret_len;
	पूर्णांक payload_len;
	u64 global_id;
	पूर्णांक ret;

	अगर (con->state != CEPH_CON_S_V2_AUTH) अणु
		con->error_msg = "protocol error, unexpected auth_done";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_64_safe(&p, end, global_id, bad);
	ceph_decode_32_safe(&p, end, con->v2.con_mode, bad);
	ceph_decode_32_safe(&p, end, payload_len, bad);

	करोut("%s con %p global_id %llu con_mode %d payload_len %d\n",
	     __func__, con, global_id, con->v2.con_mode, payload_len);

	mutex_unlock(&con->mutex);
	session_key_len = 0;
	con_secret_len = 0;
	ret = con->ops->handle_auth_करोne(con, global_id, p, payload_len,
					 session_key, &session_key_len,
					 con_secret, &con_secret_len);
	mutex_lock(&con->mutex);
	अगर (con->state != CEPH_CON_S_V2_AUTH) अणु
		करोut("%s con %p state changed to %d\n", __func__, con,
		     con->state);
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	करोut("%s con %p handle_auth_done ret %d\n", __func__, con, ret);
	अगर (ret)
		जाओ out;

	ret = setup_crypto(con, session_key, session_key_len, con_secret,
			   con_secret_len);
	अगर (ret)
		जाओ out;

	reset_out_kvecs(con);
	ret = prepare_auth_signature(con);
	अगर (ret) अणु
		pr_err("prepare_auth_signature failed: %d\n", ret);
		जाओ out;
	पूर्ण

	con->state = CEPH_CON_S_V2_AUTH_SIGNATURE;

out:
	memzero_explicit(session_key_buf, माप(session_key_buf));
	memzero_explicit(con_secret_buf, माप(con_secret_buf));
	वापस ret;

bad:
	pr_err("failed to decode auth_done\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_auth_signature(काष्ठा ceph_connection *con,
				  व्योम *p, व्योम *end)
अणु
	u8 hmac[SHA256_DIGEST_SIZE];
	पूर्णांक ret;

	अगर (con->state != CEPH_CON_S_V2_AUTH_SIGNATURE) अणु
		con->error_msg = "protocol error, unexpected auth_signature";
		वापस -EINVAL;
	पूर्ण

	ret = hmac_sha256(con, con->v2.out_sign_kvecs,
			  con->v2.out_sign_kvec_cnt, hmac);
	अगर (ret)
		वापस ret;

	ceph_decode_need(&p, end, SHA256_DIGEST_SIZE, bad);
	अगर (crypto_memneq(p, hmac, SHA256_DIGEST_SIZE)) अणु
		con->error_msg = "integrity error, bad auth signature";
		वापस -EBADMSG;
	पूर्ण

	करोut("%s con %p auth signature ok\n", __func__, con);

	/* no reset_out_kvecs() as our auth_signature may still be pending */
	अगर (!con->v2.server_cookie) अणु
		ret = prepare_client_ident(con);
		अगर (ret) अणु
			pr_err("prepare_client_ident failed: %d\n", ret);
			वापस ret;
		पूर्ण

		con->state = CEPH_CON_S_V2_SESSION_CONNECT;
	पूर्ण अन्यथा अणु
		ret = prepare_session_reconnect(con);
		अगर (ret) अणु
			pr_err("prepare_session_reconnect failed: %d\n", ret);
			वापस ret;
		पूर्ण

		con->state = CEPH_CON_S_V2_SESSION_RECONNECT;
	पूर्ण

	वापस 0;

bad:
	pr_err("failed to decode auth_signature\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_server_ident(काष्ठा ceph_connection *con,
				व्योम *p, व्योम *end)
अणु
	काष्ठा ceph_client *client = from_msgr(con->msgr);
	u64 features, required_features;
	काष्ठा ceph_entity_addr addr;
	u64 global_seq;
	u64 global_id;
	u64 cookie;
	u64 flags;
	पूर्णांक ret;

	अगर (con->state != CEPH_CON_S_V2_SESSION_CONNECT) अणु
		con->error_msg = "protocol error, unexpected server_ident";
		वापस -EINVAL;
	पूर्ण

	ret = ceph_decode_entity_addrvec(&p, end, true, &addr);
	अगर (ret) अणु
		pr_err("failed to decode server addrs: %d\n", ret);
		वापस ret;
	पूर्ण

	ceph_decode_64_safe(&p, end, global_id, bad);
	ceph_decode_64_safe(&p, end, global_seq, bad);
	ceph_decode_64_safe(&p, end, features, bad);
	ceph_decode_64_safe(&p, end, required_features, bad);
	ceph_decode_64_safe(&p, end, flags, bad);
	ceph_decode_64_safe(&p, end, cookie, bad);

	करोut("%s con %p addr %s/%u global_id %llu global_seq %llu features 0x%llx required_features 0x%llx flags 0x%llx cookie 0x%llx\n",
	     __func__, con, ceph_pr_addr(&addr), le32_to_cpu(addr.nonce),
	     global_id, global_seq, features, required_features, flags, cookie);

	/* is this who we पूर्णांकended to talk to? */
	अगर (स_भेद(&addr, &con->peer_addr, माप(con->peer_addr))) अणु
		pr_err("bad peer addr/nonce, want %s/%u, got %s/%u\n",
		       ceph_pr_addr(&con->peer_addr),
		       le32_to_cpu(con->peer_addr.nonce),
		       ceph_pr_addr(&addr), le32_to_cpu(addr.nonce));
		con->error_msg = "wrong peer at address";
		वापस -EINVAL;
	पूर्ण

	अगर (client->required_features & ~features) अणु
		pr_err("RADOS feature set mismatch: my required > server's supported 0x%llx, need 0x%llx\n",
		       features, client->required_features & ~features);
		con->error_msg = "missing required protocol features";
		वापस -EINVAL;
	पूर्ण

	/*
	 * Both name->type and name->num are set in ceph_con_खोलो() but
	 * name->num may be bogus in the initial monmap.  name->type is
	 * verअगरied in handle_hello().
	 */
	WARN_ON(!con->peer_name.type);
	con->peer_name.num = cpu_to_le64(global_id);
	con->v2.peer_global_seq = global_seq;
	con->peer_features = features;
	WARN_ON(required_features & ~client->supported_features);
	con->v2.server_cookie = cookie;

	अगर (flags & CEPH_MSG_CONNECT_LOSSY) अणु
		ceph_con_flag_set(con, CEPH_CON_F_LOSSYTX);
		WARN_ON(con->v2.server_cookie);
	पूर्ण अन्यथा अणु
		WARN_ON(!con->v2.server_cookie);
	पूर्ण

	clear_in_sign_kvecs(con);
	clear_out_sign_kvecs(con);
	मुक्त_conn_bufs(con);
	con->delay = 0;  /* reset backoff memory */

	con->state = CEPH_CON_S_OPEN;
	con->v2.out_state = OUT_S_GET_NEXT;
	वापस 0;

bad:
	pr_err("failed to decode server_ident\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_ident_missing_features(काष्ठा ceph_connection *con,
					  व्योम *p, व्योम *end)
अणु
	काष्ठा ceph_client *client = from_msgr(con->msgr);
	u64 missing_features;

	अगर (con->state != CEPH_CON_S_V2_SESSION_CONNECT) अणु
		con->error_msg = "protocol error, unexpected ident_missing_features";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_64_safe(&p, end, missing_features, bad);
	pr_err("RADOS feature set mismatch: server's required > my supported 0x%llx, missing 0x%llx\n",
	       client->supported_features, missing_features);
	con->error_msg = "missing required protocol features";
	वापस -EINVAL;

bad:
	pr_err("failed to decode ident_missing_features\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_session_reconnect_ok(काष्ठा ceph_connection *con,
					व्योम *p, व्योम *end)
अणु
	u64 seq;

	अगर (con->state != CEPH_CON_S_V2_SESSION_RECONNECT) अणु
		con->error_msg = "protocol error, unexpected session_reconnect_ok";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_64_safe(&p, end, seq, bad);

	करोut("%s con %p seq %llu\n", __func__, con, seq);
	ceph_con_discard_requeued(con, seq);

	clear_in_sign_kvecs(con);
	clear_out_sign_kvecs(con);
	मुक्त_conn_bufs(con);
	con->delay = 0;  /* reset backoff memory */

	con->state = CEPH_CON_S_OPEN;
	con->v2.out_state = OUT_S_GET_NEXT;
	वापस 0;

bad:
	pr_err("failed to decode session_reconnect_ok\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_session_retry(काष्ठा ceph_connection *con,
				 व्योम *p, व्योम *end)
अणु
	u64 connect_seq;
	पूर्णांक ret;

	अगर (con->state != CEPH_CON_S_V2_SESSION_RECONNECT) अणु
		con->error_msg = "protocol error, unexpected session_retry";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_64_safe(&p, end, connect_seq, bad);

	करोut("%s con %p connect_seq %llu\n", __func__, con, connect_seq);
	WARN_ON(connect_seq <= con->v2.connect_seq);
	con->v2.connect_seq = connect_seq + 1;

	मुक्त_conn_bufs(con);

	reset_out_kvecs(con);
	ret = prepare_session_reconnect(con);
	अगर (ret) अणु
		pr_err("prepare_session_reconnect (cseq) failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;

bad:
	pr_err("failed to decode session_retry\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_session_retry_global(काष्ठा ceph_connection *con,
					व्योम *p, व्योम *end)
अणु
	u64 global_seq;
	पूर्णांक ret;

	अगर (con->state != CEPH_CON_S_V2_SESSION_RECONNECT) अणु
		con->error_msg = "protocol error, unexpected session_retry_global";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_64_safe(&p, end, global_seq, bad);

	करोut("%s con %p global_seq %llu\n", __func__, con, global_seq);
	WARN_ON(global_seq <= con->v2.global_seq);
	con->v2.global_seq = ceph_get_global_seq(con->msgr, global_seq);

	मुक्त_conn_bufs(con);

	reset_out_kvecs(con);
	ret = prepare_session_reconnect(con);
	अगर (ret) अणु
		pr_err("prepare_session_reconnect (gseq) failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;

bad:
	pr_err("failed to decode session_retry_global\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_session_reset(काष्ठा ceph_connection *con,
				 व्योम *p, व्योम *end)
अणु
	bool full;
	पूर्णांक ret;

	अगर (con->state != CEPH_CON_S_V2_SESSION_RECONNECT) अणु
		con->error_msg = "protocol error, unexpected session_reset";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_8_safe(&p, end, full, bad);
	अगर (!full) अणु
		con->error_msg = "protocol error, bad session_reset";
		वापस -EINVAL;
	पूर्ण

	pr_info("%s%lld %s session reset\n", ENTITY_NAME(con->peer_name),
		ceph_pr_addr(&con->peer_addr));
	ceph_con_reset_session(con);

	mutex_unlock(&con->mutex);
	अगर (con->ops->peer_reset)
		con->ops->peer_reset(con);
	mutex_lock(&con->mutex);
	अगर (con->state != CEPH_CON_S_V2_SESSION_RECONNECT) अणु
		करोut("%s con %p state changed to %d\n", __func__, con,
		     con->state);
		वापस -EAGAIN;
	पूर्ण

	मुक्त_conn_bufs(con);

	reset_out_kvecs(con);
	ret = prepare_client_ident(con);
	अगर (ret) अणु
		pr_err("prepare_client_ident (rst) failed: %d\n", ret);
		वापस ret;
	पूर्ण

	con->state = CEPH_CON_S_V2_SESSION_CONNECT;
	वापस 0;

bad:
	pr_err("failed to decode session_reset\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_keepalive2_ack(काष्ठा ceph_connection *con,
				  व्योम *p, व्योम *end)
अणु
	अगर (con->state != CEPH_CON_S_OPEN) अणु
		con->error_msg = "protocol error, unexpected keepalive2_ack";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_need(&p, end, माप(काष्ठा ceph_बारpec), bad);
	ceph_decode_बारpec64(&con->last_keepalive_ack, p);

	करोut("%s con %p timestamp %lld.%09ld\n", __func__, con,
	     con->last_keepalive_ack.tv_sec, con->last_keepalive_ack.tv_nsec);

	वापस 0;

bad:
	pr_err("failed to decode keepalive2_ack\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_ack(काष्ठा ceph_connection *con, व्योम *p, व्योम *end)
अणु
	u64 seq;

	अगर (con->state != CEPH_CON_S_OPEN) अणु
		con->error_msg = "protocol error, unexpected ack";
		वापस -EINVAL;
	पूर्ण

	ceph_decode_64_safe(&p, end, seq, bad);

	करोut("%s con %p seq %llu\n", __func__, con, seq);
	ceph_con_discard_sent(con, seq);
	वापस 0;

bad:
	pr_err("failed to decode ack\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_control(काष्ठा ceph_connection *con, व्योम *p, व्योम *end)
अणु
	पूर्णांक tag = con->v2.in_desc.fd_tag;
	पूर्णांक ret;

	करोut("%s con %p tag %d len %d\n", __func__, con, tag, (पूर्णांक)(end - p));

	चयन (tag) अणु
	हाल FRAME_TAG_HELLO:
		ret = process_hello(con, p, end);
		अवरोध;
	हाल FRAME_TAG_AUTH_BAD_METHOD:
		ret = process_auth_bad_method(con, p, end);
		अवरोध;
	हाल FRAME_TAG_AUTH_REPLY_MORE:
		ret = process_auth_reply_more(con, p, end);
		अवरोध;
	हाल FRAME_TAG_AUTH_DONE:
		ret = process_auth_करोne(con, p, end);
		अवरोध;
	हाल FRAME_TAG_AUTH_SIGNATURE:
		ret = process_auth_signature(con, p, end);
		अवरोध;
	हाल FRAME_TAG_SERVER_IDENT:
		ret = process_server_ident(con, p, end);
		अवरोध;
	हाल FRAME_TAG_IDENT_MISSING_FEATURES:
		ret = process_ident_missing_features(con, p, end);
		अवरोध;
	हाल FRAME_TAG_SESSION_RECONNECT_OK:
		ret = process_session_reconnect_ok(con, p, end);
		अवरोध;
	हाल FRAME_TAG_SESSION_RETRY:
		ret = process_session_retry(con, p, end);
		अवरोध;
	हाल FRAME_TAG_SESSION_RETRY_GLOBAL:
		ret = process_session_retry_global(con, p, end);
		अवरोध;
	हाल FRAME_TAG_SESSION_RESET:
		ret = process_session_reset(con, p, end);
		अवरोध;
	हाल FRAME_TAG_KEEPALIVE2_ACK:
		ret = process_keepalive2_ack(con, p, end);
		अवरोध;
	हाल FRAME_TAG_ACK:
		ret = process_ack(con, p, end);
		अवरोध;
	शेष:
		pr_err("bad tag %d\n", tag);
		con->error_msg = "protocol error, bad tag";
		वापस -EINVAL;
	पूर्ण
	अगर (ret) अणु
		करोut("%s con %p error %d\n", __func__, con, ret);
		वापस ret;
	पूर्ण

	prepare_पढ़ो_preamble(con);
	वापस 0;
पूर्ण

/*
 * Return:
 *   1 - con->in_msg set, पढ़ो message
 *   0 - skip message
 *  <0 - error
 */
अटल पूर्णांक process_message_header(काष्ठा ceph_connection *con,
				  व्योम *p, व्योम *end)
अणु
	काष्ठा ceph_frame_desc *desc = &con->v2.in_desc;
	काष्ठा ceph_msg_header2 *hdr2 = p;
	काष्ठा ceph_msg_header hdr;
	पूर्णांक skip;
	पूर्णांक ret;
	u64 seq;

	/* verअगरy seq# */
	seq = le64_to_cpu(hdr2->seq);
	अगर ((s64)seq - (s64)con->in_seq < 1) अणु
		pr_info("%s%lld %s skipping old message: seq %llu, expected %llu\n",
			ENTITY_NAME(con->peer_name),
			ceph_pr_addr(&con->peer_addr),
			seq, con->in_seq + 1);
		वापस 0;
	पूर्ण
	अगर ((s64)seq - (s64)con->in_seq > 1) अणु
		pr_err("bad seq %llu, expected %llu\n", seq, con->in_seq + 1);
		con->error_msg = "bad message sequence # for incoming message";
		वापस -EBADE;
	पूर्ण

	ceph_con_discard_sent(con, le64_to_cpu(hdr2->ack_seq));

	fill_header(&hdr, hdr2, desc->fd_lens[1], desc->fd_lens[2],
		    desc->fd_lens[3], &con->peer_name);
	ret = ceph_con_in_msg_alloc(con, &hdr, &skip);
	अगर (ret)
		वापस ret;

	WARN_ON(!con->in_msg ^ skip);
	अगर (skip)
		वापस 0;

	WARN_ON(!con->in_msg);
	WARN_ON(con->in_msg->con != con);
	वापस 1;
पूर्ण

अटल पूर्णांक process_message(काष्ठा ceph_connection *con)
अणु
	ceph_con_process_message(con);

	/*
	 * We could have been बंदd by ceph_con_बंद() because
	 * ceph_con_process_message() temporarily drops con->mutex.
	 */
	अगर (con->state != CEPH_CON_S_OPEN) अणु
		करोut("%s con %p state changed to %d\n", __func__, con,
		     con->state);
		वापस -EAGAIN;
	पूर्ण

	prepare_पढ़ो_preamble(con);
	वापस 0;
पूर्ण

अटल पूर्णांक __handle_control(काष्ठा ceph_connection *con, व्योम *p)
अणु
	व्योम *end = p + con->v2.in_desc.fd_lens[0];
	काष्ठा ceph_msg *msg;
	पूर्णांक ret;

	अगर (con->v2.in_desc.fd_tag != FRAME_TAG_MESSAGE)
		वापस process_control(con, p, end);

	ret = process_message_header(con, p, end);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0) अणु
		prepare_skip_message(con);
		वापस 0;
	पूर्ण

	msg = con->in_msg;  /* set in process_message_header() */
	अगर (!front_len(msg) && !middle_len(msg)) अणु
		अगर (!data_len(msg))
			वापस process_message(con);

		prepare_पढ़ो_data(con);
		वापस 0;
	पूर्ण

	reset_in_kvecs(con);
	अगर (front_len(msg)) अणु
		WARN_ON(front_len(msg) > msg->front_alloc_len);
		add_in_kvec(con, msg->front.iov_base, front_len(msg));
		msg->front.iov_len = front_len(msg);

		अगर (con_secure(con) && need_padding(front_len(msg)))
			add_in_kvec(con, FRONT_PAD(con->v2.in_buf),
				    padding_len(front_len(msg)));
	पूर्ण अन्यथा अणु
		msg->front.iov_len = 0;
	पूर्ण
	अगर (middle_len(msg)) अणु
		WARN_ON(middle_len(msg) > msg->middle->alloc_len);
		add_in_kvec(con, msg->middle->vec.iov_base, middle_len(msg));
		msg->middle->vec.iov_len = middle_len(msg);

		अगर (con_secure(con) && need_padding(middle_len(msg)))
			add_in_kvec(con, MIDDLE_PAD(con->v2.in_buf),
				    padding_len(middle_len(msg)));
	पूर्ण अन्यथा अगर (msg->middle) अणु
		msg->middle->vec.iov_len = 0;
	पूर्ण

	अगर (data_len(msg)) अणु
		con->v2.in_state = IN_S_PREPARE_READ_DATA;
	पूर्ण अन्यथा अणु
		add_in_kvec(con, con->v2.in_buf,
			    con_secure(con) ? CEPH_EPILOGUE_SECURE_LEN :
					      CEPH_EPILOGUE_PLAIN_LEN);
		con->v2.in_state = IN_S_HANDLE_EPILOGUE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक handle_preamble(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_frame_desc *desc = &con->v2.in_desc;
	पूर्णांक ret;

	अगर (con_secure(con)) अणु
		ret = decrypt_preamble(con);
		अगर (ret) अणु
			अगर (ret == -EBADMSG)
				con->error_msg = "integrity error, bad preamble auth tag";
			वापस ret;
		पूर्ण
	पूर्ण

	ret = decode_preamble(con->v2.in_buf, desc);
	अगर (ret) अणु
		अगर (ret == -EBADMSG)
			con->error_msg = "integrity error, bad crc";
		अन्यथा
			con->error_msg = "protocol error, bad preamble";
		वापस ret;
	पूर्ण

	करोut("%s con %p tag %d seg_cnt %d %d+%d+%d+%d\n", __func__,
	     con, desc->fd_tag, desc->fd_seg_cnt, desc->fd_lens[0],
	     desc->fd_lens[1], desc->fd_lens[2], desc->fd_lens[3]);

	अगर (!con_secure(con))
		वापस prepare_पढ़ो_control(con);

	अगर (desc->fd_lens[0] > CEPH_PREAMBLE_INLINE_LEN)
		वापस prepare_पढ़ो_control_reमुख्यder(con);

	वापस __handle_control(con, CTRL_BODY(con->v2.in_buf));
पूर्ण

अटल पूर्णांक handle_control(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ctrl_len = con->v2.in_desc.fd_lens[0];
	व्योम *buf;
	पूर्णांक ret;

	WARN_ON(con_secure(con));

	ret = verअगरy_control_crc(con);
	अगर (ret) अणु
		con->error_msg = "integrity error, bad crc";
		वापस ret;
	पूर्ण

	अगर (con->state == CEPH_CON_S_V2_AUTH) अणु
		buf = alloc_conn_buf(con, ctrl_len);
		अगर (!buf)
			वापस -ENOMEM;

		स_नकल(buf, con->v2.in_kvecs[0].iov_base, ctrl_len);
		वापस __handle_control(con, buf);
	पूर्ण

	वापस __handle_control(con, con->v2.in_kvecs[0].iov_base);
पूर्ण

अटल पूर्णांक handle_control_reमुख्यder(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret;

	WARN_ON(!con_secure(con));

	ret = decrypt_control_reमुख्यder(con);
	अगर (ret) अणु
		अगर (ret == -EBADMSG)
			con->error_msg = "integrity error, bad control remainder auth tag";
		वापस ret;
	पूर्ण

	वापस __handle_control(con, con->v2.in_kvecs[0].iov_base -
				     CEPH_PREAMBLE_INLINE_LEN);
पूर्ण

अटल पूर्णांक handle_epilogue(काष्ठा ceph_connection *con)
अणु
	u32 front_crc, middle_crc, data_crc;
	पूर्णांक ret;

	अगर (con_secure(con)) अणु
		ret = decrypt_message(con);
		अगर (ret) अणु
			अगर (ret == -EBADMSG)
				con->error_msg = "integrity error, bad epilogue auth tag";
			वापस ret;
		पूर्ण

		/* just late_status */
		ret = decode_epilogue(con->v2.in_buf, शून्य, शून्य, शून्य);
		अगर (ret) अणु
			con->error_msg = "protocol error, bad epilogue";
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = decode_epilogue(con->v2.in_buf, &front_crc,
				      &middle_crc, &data_crc);
		अगर (ret) अणु
			con->error_msg = "protocol error, bad epilogue";
			वापस ret;
		पूर्ण

		ret = verअगरy_epilogue_crcs(con, front_crc, middle_crc,
					   data_crc);
		अगर (ret) अणु
			con->error_msg = "integrity error, bad crc";
			वापस ret;
		पूर्ण
	पूर्ण

	वापस process_message(con);
पूर्ण

अटल व्योम finish_skip(काष्ठा ceph_connection *con)
अणु
	करोut("%s con %p\n", __func__, con);

	अगर (con_secure(con))
		gcm_inc_nonce(&con->v2.in_gcm_nonce);

	__finish_skip(con);
पूर्ण

अटल पूर्णांक populate_in_iter(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret;

	करोut("%s con %p state %d in_state %d\n", __func__, con, con->state,
	     con->v2.in_state);
	WARN_ON(iov_iter_count(&con->v2.in_iter));

	अगर (con->state == CEPH_CON_S_V2_BANNER_PREFIX) अणु
		ret = process_banner_prefix(con);
	पूर्ण अन्यथा अगर (con->state == CEPH_CON_S_V2_BANNER_PAYLOAD) अणु
		ret = process_banner_payload(con);
	पूर्ण अन्यथा अगर ((con->state >= CEPH_CON_S_V2_HELLO &&
		    con->state <= CEPH_CON_S_V2_SESSION_RECONNECT) ||
		   con->state == CEPH_CON_S_OPEN) अणु
		चयन (con->v2.in_state) अणु
		हाल IN_S_HANDLE_PREAMBLE:
			ret = handle_preamble(con);
			अवरोध;
		हाल IN_S_HANDLE_CONTROL:
			ret = handle_control(con);
			अवरोध;
		हाल IN_S_HANDLE_CONTROL_REMAINDER:
			ret = handle_control_reमुख्यder(con);
			अवरोध;
		हाल IN_S_PREPARE_READ_DATA:
			prepare_पढ़ो_data(con);
			ret = 0;
			अवरोध;
		हाल IN_S_PREPARE_READ_DATA_CONT:
			prepare_पढ़ो_data_cont(con);
			ret = 0;
			अवरोध;
		हाल IN_S_HANDLE_EPILOGUE:
			ret = handle_epilogue(con);
			अवरोध;
		हाल IN_S_FINISH_SKIP:
			finish_skip(con);
			ret = 0;
			अवरोध;
		शेष:
			WARN(1, "bad in_state %d", con->v2.in_state);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN(1, "bad state %d", con->state);
		वापस -EINVAL;
	पूर्ण
	अगर (ret) अणु
		करोut("%s con %p error %d\n", __func__, con, ret);
		वापस ret;
	पूर्ण

	अगर (WARN_ON(!iov_iter_count(&con->v2.in_iter)))
		वापस -ENODATA;
	करोut("%s con %p populated %zu\n", __func__, con,
	     iov_iter_count(&con->v2.in_iter));
	वापस 1;
पूर्ण

पूर्णांक ceph_con_v2_try_पढ़ो(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret;

	करोut("%s con %p state %d need %zu\n", __func__, con, con->state,
	     iov_iter_count(&con->v2.in_iter));

	अगर (con->state == CEPH_CON_S_PREOPEN)
		वापस 0;

	/*
	 * We should always have something pending here.  If not,
	 * aव्योम calling populate_in_iter() as अगर we पढ़ो something
	 * (ceph_tcp_recv() would immediately वापस 1).
	 */
	अगर (WARN_ON(!iov_iter_count(&con->v2.in_iter)))
		वापस -ENODATA;

	क्रम (;;) अणु
		ret = ceph_tcp_recv(con);
		अगर (ret <= 0)
			वापस ret;

		ret = populate_in_iter(con);
		अगर (ret <= 0) अणु
			अगर (ret && ret != -EAGAIN && !con->error_msg)
				con->error_msg = "read processing error";
			वापस ret;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम queue_data(काष्ठा ceph_connection *con)
अणु
	काष्ठा bio_vec bv;

	con->v2.out_epil.data_crc = -1;
	ceph_msg_data_cursor_init(&con->v2.out_cursor, con->out_msg,
				  data_len(con->out_msg));

	get_bvec_at(&con->v2.out_cursor, &bv);
	set_out_bvec(con, &bv, true);
	con->v2.out_state = OUT_S_QUEUE_DATA_CONT;
पूर्ण

अटल व्योम queue_data_cont(काष्ठा ceph_connection *con)
अणु
	काष्ठा bio_vec bv;

	con->v2.out_epil.data_crc = ceph_crc32c_page(
		con->v2.out_epil.data_crc, con->v2.out_bvec.bv_page,
		con->v2.out_bvec.bv_offset, con->v2.out_bvec.bv_len);

	ceph_msg_data_advance(&con->v2.out_cursor, con->v2.out_bvec.bv_len);
	अगर (con->v2.out_cursor.total_resid) अणु
		get_bvec_at(&con->v2.out_cursor, &bv);
		set_out_bvec(con, &bv, true);
		WARN_ON(con->v2.out_state != OUT_S_QUEUE_DATA_CONT);
		वापस;
	पूर्ण

	/*
	 * We've written all data.  Queue epilogue.  Once it's written,
	 * we are करोne.
	 */
	reset_out_kvecs(con);
	prepare_epilogue_plain(con, false);
	con->v2.out_state = OUT_S_FINISH_MESSAGE;
पूर्ण

अटल व्योम queue_enc_page(काष्ठा ceph_connection *con)
अणु
	काष्ठा bio_vec bv;

	करोut("%s con %p i %d resid %d\n", __func__, con, con->v2.out_enc_i,
	     con->v2.out_enc_resid);
	WARN_ON(!con->v2.out_enc_resid);

	bv.bv_page = con->v2.out_enc_pages[con->v2.out_enc_i];
	bv.bv_offset = 0;
	bv.bv_len = min(con->v2.out_enc_resid, (पूर्णांक)PAGE_SIZE);

	set_out_bvec(con, &bv, false);
	con->v2.out_enc_i++;
	con->v2.out_enc_resid -= bv.bv_len;

	अगर (con->v2.out_enc_resid) अणु
		WARN_ON(con->v2.out_state != OUT_S_QUEUE_ENC_PAGE);
		वापस;
	पूर्ण

	/*
	 * We've queued the last piece of ciphertext (ending with
	 * epilogue) + auth tag.  Once it's written, we are करोne.
	 */
	WARN_ON(con->v2.out_enc_i != con->v2.out_enc_page_cnt);
	con->v2.out_state = OUT_S_FINISH_MESSAGE;
पूर्ण

अटल व्योम queue_zeros(काष्ठा ceph_connection *con)
अणु
	करोut("%s con %p out_zero %d\n", __func__, con, con->v2.out_zero);

	अगर (con->v2.out_zero) अणु
		set_out_bvec_zero(con);
		con->v2.out_zero -= con->v2.out_bvec.bv_len;
		con->v2.out_state = OUT_S_QUEUE_ZEROS;
		वापस;
	पूर्ण

	/*
	 * We've zero-filled everything up to epilogue.  Queue epilogue
	 * with late_status set to ABORTED and crcs adjusted क्रम zeros.
	 * Once it's written, we are करोne patching up क्रम the revoke.
	 */
	reset_out_kvecs(con);
	prepare_epilogue_plain(con, true);
	con->v2.out_state = OUT_S_FINISH_MESSAGE;
पूर्ण

अटल व्योम finish_message(काष्ठा ceph_connection *con)
अणु
	करोut("%s con %p msg %p\n", __func__, con, con->out_msg);

	/* we end up here both plain and secure modes */
	अगर (con->v2.out_enc_pages) अणु
		WARN_ON(!con->v2.out_enc_page_cnt);
		ceph_release_page_vector(con->v2.out_enc_pages,
					 con->v2.out_enc_page_cnt);
		con->v2.out_enc_pages = शून्य;
		con->v2.out_enc_page_cnt = 0;
	पूर्ण
	/* message may have been revoked */
	अगर (con->out_msg) अणु
		ceph_msg_put(con->out_msg);
		con->out_msg = शून्य;
	पूर्ण

	con->v2.out_state = OUT_S_GET_NEXT;
पूर्ण

अटल पूर्णांक populate_out_iter(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret;

	करोut("%s con %p state %d out_state %d\n", __func__, con, con->state,
	     con->v2.out_state);
	WARN_ON(iov_iter_count(&con->v2.out_iter));

	अगर (con->state != CEPH_CON_S_OPEN) अणु
		WARN_ON(con->state < CEPH_CON_S_V2_BANNER_PREFIX ||
			con->state > CEPH_CON_S_V2_SESSION_RECONNECT);
		जाओ nothing_pending;
	पूर्ण

	चयन (con->v2.out_state) अणु
	हाल OUT_S_QUEUE_DATA:
		WARN_ON(!con->out_msg);
		queue_data(con);
		जाओ populated;
	हाल OUT_S_QUEUE_DATA_CONT:
		WARN_ON(!con->out_msg);
		queue_data_cont(con);
		जाओ populated;
	हाल OUT_S_QUEUE_ENC_PAGE:
		queue_enc_page(con);
		जाओ populated;
	हाल OUT_S_QUEUE_ZEROS:
		WARN_ON(con->out_msg);  /* revoked */
		queue_zeros(con);
		जाओ populated;
	हाल OUT_S_FINISH_MESSAGE:
		finish_message(con);
		अवरोध;
	हाल OUT_S_GET_NEXT:
		अवरोध;
	शेष:
		WARN(1, "bad out_state %d", con->v2.out_state);
		वापस -EINVAL;
	पूर्ण

	WARN_ON(con->v2.out_state != OUT_S_GET_NEXT);
	अगर (ceph_con_flag_test_and_clear(con, CEPH_CON_F_KEEPALIVE_PENDING)) अणु
		ret = prepare_keepalive2(con);
		अगर (ret) अणु
			pr_err("prepare_keepalive2 failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (!list_empty(&con->out_queue)) अणु
		ceph_con_get_out_msg(con);
		ret = prepare_message(con);
		अगर (ret) अणु
			pr_err("prepare_message failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (con->in_seq > con->in_seq_acked) अणु
		ret = prepare_ack(con);
		अगर (ret) अणु
			pr_err("prepare_ack failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		जाओ nothing_pending;
	पूर्ण

populated:
	अगर (WARN_ON(!iov_iter_count(&con->v2.out_iter)))
		वापस -ENODATA;
	करोut("%s con %p populated %zu\n", __func__, con,
	     iov_iter_count(&con->v2.out_iter));
	वापस 1;

nothing_pending:
	WARN_ON(iov_iter_count(&con->v2.out_iter));
	करोut("%s con %p nothing pending\n", __func__, con);
	ceph_con_flag_clear(con, CEPH_CON_F_WRITE_PENDING);
	वापस 0;
पूर्ण

पूर्णांक ceph_con_v2_try_ग_लिखो(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret;

	करोut("%s con %p state %d have %zu\n", __func__, con, con->state,
	     iov_iter_count(&con->v2.out_iter));

	/* खोलो the socket first? */
	अगर (con->state == CEPH_CON_S_PREOPEN) अणु
		WARN_ON(con->peer_addr.type != CEPH_ENTITY_ADDR_TYPE_MSGR2);

		/*
		 * Always bump global_seq.  Bump connect_seq only अगर
		 * there is a session (i.e. we are reconnecting and will
		 * send session_reconnect instead of client_ident).
		 */
		con->v2.global_seq = ceph_get_global_seq(con->msgr, 0);
		अगर (con->v2.server_cookie)
			con->v2.connect_seq++;

		ret = prepare_पढ़ो_banner_prefix(con);
		अगर (ret) अणु
			pr_err("prepare_read_banner_prefix failed: %d\n", ret);
			con->error_msg = "connect error";
			वापस ret;
		पूर्ण

		reset_out_kvecs(con);
		ret = prepare_banner(con);
		अगर (ret) अणु
			pr_err("prepare_banner failed: %d\n", ret);
			con->error_msg = "connect error";
			वापस ret;
		पूर्ण

		ret = ceph_tcp_connect(con);
		अगर (ret) अणु
			pr_err("ceph_tcp_connect failed: %d\n", ret);
			con->error_msg = "connect error";
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!iov_iter_count(&con->v2.out_iter)) अणु
		ret = populate_out_iter(con);
		अगर (ret <= 0) अणु
			अगर (ret && ret != -EAGAIN && !con->error_msg)
				con->error_msg = "write processing error";
			वापस ret;
		पूर्ण
	पूर्ण

	tcp_sock_set_cork(con->sock->sk, true);
	क्रम (;;) अणु
		ret = ceph_tcp_send(con);
		अगर (ret <= 0)
			अवरोध;

		ret = populate_out_iter(con);
		अगर (ret <= 0) अणु
			अगर (ret && ret != -EAGAIN && !con->error_msg)
				con->error_msg = "write processing error";
			अवरोध;
		पूर्ण
	पूर्ण

	tcp_sock_set_cork(con->sock->sk, false);
	वापस ret;
पूर्ण

अटल u32 crc32c_zeros(u32 crc, पूर्णांक zero_len)
अणु
	पूर्णांक len;

	जबतक (zero_len) अणु
		len = min(zero_len, (पूर्णांक)PAGE_SIZE);
		crc = crc32c(crc, page_address(ceph_zero_page), len);
		zero_len -= len;
	पूर्ण

	वापस crc;
पूर्ण

अटल व्योम prepare_zero_front(काष्ठा ceph_connection *con, पूर्णांक resid)
अणु
	पूर्णांक sent;

	WARN_ON(!resid || resid > front_len(con->out_msg));
	sent = front_len(con->out_msg) - resid;
	करोut("%s con %p sent %d resid %d\n", __func__, con, sent, resid);

	अगर (sent) अणु
		con->v2.out_epil.front_crc =
			crc32c(-1, con->out_msg->front.iov_base, sent);
		con->v2.out_epil.front_crc =
			crc32c_zeros(con->v2.out_epil.front_crc, resid);
	पूर्ण अन्यथा अणु
		con->v2.out_epil.front_crc = crc32c_zeros(-1, resid);
	पूर्ण

	con->v2.out_iter.count -= resid;
	out_zero_add(con, resid);
पूर्ण

अटल व्योम prepare_zero_middle(काष्ठा ceph_connection *con, पूर्णांक resid)
अणु
	पूर्णांक sent;

	WARN_ON(!resid || resid > middle_len(con->out_msg));
	sent = middle_len(con->out_msg) - resid;
	करोut("%s con %p sent %d resid %d\n", __func__, con, sent, resid);

	अगर (sent) अणु
		con->v2.out_epil.middle_crc =
			crc32c(-1, con->out_msg->middle->vec.iov_base, sent);
		con->v2.out_epil.middle_crc =
			crc32c_zeros(con->v2.out_epil.middle_crc, resid);
	पूर्ण अन्यथा अणु
		con->v2.out_epil.middle_crc = crc32c_zeros(-1, resid);
	पूर्ण

	con->v2.out_iter.count -= resid;
	out_zero_add(con, resid);
पूर्ण

अटल व्योम prepare_zero_data(काष्ठा ceph_connection *con)
अणु
	करोut("%s con %p\n", __func__, con);
	con->v2.out_epil.data_crc = crc32c_zeros(-1, data_len(con->out_msg));
	out_zero_add(con, data_len(con->out_msg));
पूर्ण

अटल व्योम revoke_at_queue_data(काष्ठा ceph_connection *con)
अणु
	पूर्णांक boundary;
	पूर्णांक resid;

	WARN_ON(!data_len(con->out_msg));
	WARN_ON(!iov_iter_is_kvec(&con->v2.out_iter));
	resid = iov_iter_count(&con->v2.out_iter);

	boundary = front_len(con->out_msg) + middle_len(con->out_msg);
	अगर (resid > boundary) अणु
		resid -= boundary;
		WARN_ON(resid > MESSAGE_HEAD_PLAIN_LEN);
		करोut("%s con %p was sending head\n", __func__, con);
		अगर (front_len(con->out_msg))
			prepare_zero_front(con, front_len(con->out_msg));
		अगर (middle_len(con->out_msg))
			prepare_zero_middle(con, middle_len(con->out_msg));
		prepare_zero_data(con);
		WARN_ON(iov_iter_count(&con->v2.out_iter) != resid);
		con->v2.out_state = OUT_S_QUEUE_ZEROS;
		वापस;
	पूर्ण

	boundary = middle_len(con->out_msg);
	अगर (resid > boundary) अणु
		resid -= boundary;
		करोut("%s con %p was sending front\n", __func__, con);
		prepare_zero_front(con, resid);
		अगर (middle_len(con->out_msg))
			prepare_zero_middle(con, middle_len(con->out_msg));
		prepare_zero_data(con);
		queue_zeros(con);
		वापस;
	पूर्ण

	WARN_ON(!resid);
	करोut("%s con %p was sending middle\n", __func__, con);
	prepare_zero_middle(con, resid);
	prepare_zero_data(con);
	queue_zeros(con);
पूर्ण

अटल व्योम revoke_at_queue_data_cont(काष्ठा ceph_connection *con)
अणु
	पूर्णांक sent, resid;  /* current piece of data */

	WARN_ON(!data_len(con->out_msg));
	WARN_ON(!iov_iter_is_bvec(&con->v2.out_iter));
	resid = iov_iter_count(&con->v2.out_iter);
	WARN_ON(!resid || resid > con->v2.out_bvec.bv_len);
	sent = con->v2.out_bvec.bv_len - resid;
	करोut("%s con %p sent %d resid %d\n", __func__, con, sent, resid);

	अगर (sent) अणु
		con->v2.out_epil.data_crc = ceph_crc32c_page(
			con->v2.out_epil.data_crc, con->v2.out_bvec.bv_page,
			con->v2.out_bvec.bv_offset, sent);
		ceph_msg_data_advance(&con->v2.out_cursor, sent);
	पूर्ण
	WARN_ON(resid > con->v2.out_cursor.total_resid);
	con->v2.out_epil.data_crc = crc32c_zeros(con->v2.out_epil.data_crc,
						con->v2.out_cursor.total_resid);

	con->v2.out_iter.count -= resid;
	out_zero_add(con, con->v2.out_cursor.total_resid);
	queue_zeros(con);
पूर्ण

अटल व्योम revoke_at_finish_message(काष्ठा ceph_connection *con)
अणु
	पूर्णांक boundary;
	पूर्णांक resid;

	WARN_ON(!iov_iter_is_kvec(&con->v2.out_iter));
	resid = iov_iter_count(&con->v2.out_iter);

	अगर (!front_len(con->out_msg) && !middle_len(con->out_msg) &&
	    !data_len(con->out_msg)) अणु
		WARN_ON(!resid || resid > MESSAGE_HEAD_PLAIN_LEN);
		करोut("%s con %p was sending head (empty message) - noop\n",
		     __func__, con);
		वापस;
	पूर्ण

	boundary = front_len(con->out_msg) + middle_len(con->out_msg) +
		   CEPH_EPILOGUE_PLAIN_LEN;
	अगर (resid > boundary) अणु
		resid -= boundary;
		WARN_ON(resid > MESSAGE_HEAD_PLAIN_LEN);
		करोut("%s con %p was sending head\n", __func__, con);
		अगर (front_len(con->out_msg))
			prepare_zero_front(con, front_len(con->out_msg));
		अगर (middle_len(con->out_msg))
			prepare_zero_middle(con, middle_len(con->out_msg));
		con->v2.out_iter.count -= CEPH_EPILOGUE_PLAIN_LEN;
		WARN_ON(iov_iter_count(&con->v2.out_iter) != resid);
		con->v2.out_state = OUT_S_QUEUE_ZEROS;
		वापस;
	पूर्ण

	boundary = middle_len(con->out_msg) + CEPH_EPILOGUE_PLAIN_LEN;
	अगर (resid > boundary) अणु
		resid -= boundary;
		करोut("%s con %p was sending front\n", __func__, con);
		prepare_zero_front(con, resid);
		अगर (middle_len(con->out_msg))
			prepare_zero_middle(con, middle_len(con->out_msg));
		con->v2.out_iter.count -= CEPH_EPILOGUE_PLAIN_LEN;
		queue_zeros(con);
		वापस;
	पूर्ण

	boundary = CEPH_EPILOGUE_PLAIN_LEN;
	अगर (resid > boundary) अणु
		resid -= boundary;
		करोut("%s con %p was sending middle\n", __func__, con);
		prepare_zero_middle(con, resid);
		con->v2.out_iter.count -= CEPH_EPILOGUE_PLAIN_LEN;
		queue_zeros(con);
		वापस;
	पूर्ण

	WARN_ON(!resid);
	करोut("%s con %p was sending epilogue - noop\n", __func__, con);
पूर्ण

व्योम ceph_con_v2_revoke(काष्ठा ceph_connection *con)
अणु
	WARN_ON(con->v2.out_zero);

	अगर (con_secure(con)) अणु
		WARN_ON(con->v2.out_state != OUT_S_QUEUE_ENC_PAGE &&
			con->v2.out_state != OUT_S_FINISH_MESSAGE);
		करोut("%s con %p secure - noop\n", __func__, con);
		वापस;
	पूर्ण

	चयन (con->v2.out_state) अणु
	हाल OUT_S_QUEUE_DATA:
		revoke_at_queue_data(con);
		अवरोध;
	हाल OUT_S_QUEUE_DATA_CONT:
		revoke_at_queue_data_cont(con);
		अवरोध;
	हाल OUT_S_FINISH_MESSAGE:
		revoke_at_finish_message(con);
		अवरोध;
	शेष:
		WARN(1, "bad out_state %d", con->v2.out_state);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम revoke_at_prepare_पढ़ो_data(काष्ठा ceph_connection *con)
अणु
	पूर्णांक reमुख्यing;  /* data + [data padding] + epilogue */
	पूर्णांक resid;

	WARN_ON(!data_len(con->in_msg));
	WARN_ON(!iov_iter_is_kvec(&con->v2.in_iter));
	resid = iov_iter_count(&con->v2.in_iter);
	WARN_ON(!resid);

	अगर (con_secure(con))
		reमुख्यing = padded_len(data_len(con->in_msg)) +
			    CEPH_EPILOGUE_SECURE_LEN;
	अन्यथा
		reमुख्यing = data_len(con->in_msg) + CEPH_EPILOGUE_PLAIN_LEN;

	करोut("%s con %p resid %d remaining %d\n", __func__, con, resid,
	     reमुख्यing);
	con->v2.in_iter.count -= resid;
	set_in_skip(con, resid + reमुख्यing);
	con->v2.in_state = IN_S_FINISH_SKIP;
पूर्ण

अटल व्योम revoke_at_prepare_पढ़ो_data_cont(काष्ठा ceph_connection *con)
अणु
	पूर्णांक recved, resid;  /* current piece of data */
	पूर्णांक reमुख्यing;  /* [data padding] + epilogue */

	WARN_ON(!data_len(con->in_msg));
	WARN_ON(!iov_iter_is_bvec(&con->v2.in_iter));
	resid = iov_iter_count(&con->v2.in_iter);
	WARN_ON(!resid || resid > con->v2.in_bvec.bv_len);
	recved = con->v2.in_bvec.bv_len - resid;
	करोut("%s con %p recved %d resid %d\n", __func__, con, recved, resid);

	अगर (recved)
		ceph_msg_data_advance(&con->v2.in_cursor, recved);
	WARN_ON(resid > con->v2.in_cursor.total_resid);

	अगर (con_secure(con))
		reमुख्यing = padding_len(data_len(con->in_msg)) +
			    CEPH_EPILOGUE_SECURE_LEN;
	अन्यथा
		reमुख्यing = CEPH_EPILOGUE_PLAIN_LEN;

	करोut("%s con %p total_resid %zu remaining %d\n", __func__, con,
	     con->v2.in_cursor.total_resid, reमुख्यing);
	con->v2.in_iter.count -= resid;
	set_in_skip(con, con->v2.in_cursor.total_resid + reमुख्यing);
	con->v2.in_state = IN_S_FINISH_SKIP;
पूर्ण

अटल व्योम revoke_at_handle_epilogue(काष्ठा ceph_connection *con)
अणु
	पूर्णांक resid;

	WARN_ON(!iov_iter_is_kvec(&con->v2.in_iter));
	resid = iov_iter_count(&con->v2.in_iter);
	WARN_ON(!resid);

	करोut("%s con %p resid %d\n", __func__, con, resid);
	con->v2.in_iter.count -= resid;
	set_in_skip(con, resid);
	con->v2.in_state = IN_S_FINISH_SKIP;
पूर्ण

व्योम ceph_con_v2_revoke_incoming(काष्ठा ceph_connection *con)
अणु
	चयन (con->v2.in_state) अणु
	हाल IN_S_PREPARE_READ_DATA:
		revoke_at_prepare_पढ़ो_data(con);
		अवरोध;
	हाल IN_S_PREPARE_READ_DATA_CONT:
		revoke_at_prepare_पढ़ो_data_cont(con);
		अवरोध;
	हाल IN_S_HANDLE_EPILOGUE:
		revoke_at_handle_epilogue(con);
		अवरोध;
	शेष:
		WARN(1, "bad in_state %d", con->v2.in_state);
		अवरोध;
	पूर्ण
पूर्ण

bool ceph_con_v2_खोलोed(काष्ठा ceph_connection *con)
अणु
	वापस con->v2.peer_global_seq;
पूर्ण

व्योम ceph_con_v2_reset_session(काष्ठा ceph_connection *con)
अणु
	con->v2.client_cookie = 0;
	con->v2.server_cookie = 0;
	con->v2.global_seq = 0;
	con->v2.connect_seq = 0;
	con->v2.peer_global_seq = 0;
पूर्ण

व्योम ceph_con_v2_reset_protocol(काष्ठा ceph_connection *con)
अणु
	iov_iter_truncate(&con->v2.in_iter, 0);
	iov_iter_truncate(&con->v2.out_iter, 0);
	con->v2.out_zero = 0;

	clear_in_sign_kvecs(con);
	clear_out_sign_kvecs(con);
	मुक्त_conn_bufs(con);

	अगर (con->v2.out_enc_pages) अणु
		WARN_ON(!con->v2.out_enc_page_cnt);
		ceph_release_page_vector(con->v2.out_enc_pages,
					 con->v2.out_enc_page_cnt);
		con->v2.out_enc_pages = शून्य;
		con->v2.out_enc_page_cnt = 0;
	पूर्ण

	con->v2.con_mode = CEPH_CON_MODE_UNKNOWN;
	memzero_explicit(&con->v2.in_gcm_nonce, CEPH_GCM_IV_LEN);
	memzero_explicit(&con->v2.out_gcm_nonce, CEPH_GCM_IV_LEN);

	अगर (con->v2.hmac_tfm) अणु
		crypto_मुक्त_shash(con->v2.hmac_tfm);
		con->v2.hmac_tfm = शून्य;
	पूर्ण
	अगर (con->v2.gcm_req) अणु
		aead_request_मुक्त(con->v2.gcm_req);
		con->v2.gcm_req = शून्य;
	पूर्ण
	अगर (con->v2.gcm_tfm) अणु
		crypto_मुक्त_aead(con->v2.gcm_tfm);
		con->v2.gcm_tfm = शून्य;
	पूर्ण
पूर्ण
