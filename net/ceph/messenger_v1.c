<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/bvec.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/net.h>
#समावेश <linux/socket.h>
#समावेश <net/sock.h>

#समावेश <linux/ceph/ceph_features.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/messenger.h>

/* अटल tag bytes (protocol control messages) */
अटल अक्षर tag_msg = CEPH_MSGR_TAG_MSG;
अटल अक्षर tag_ack = CEPH_MSGR_TAG_ACK;
अटल अक्षर tag_keepalive = CEPH_MSGR_TAG_KEEPALIVE;
अटल अक्षर tag_keepalive2 = CEPH_MSGR_TAG_KEEPALIVE2;

/*
 * If @buf is शून्य, discard up to @len bytes.
 */
अटल पूर्णांक ceph_tcp_recvmsg(काष्ठा socket *sock, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा kvec iov = अणुbuf, lenपूर्ण;
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL पूर्ण;
	पूर्णांक r;

	अगर (!buf)
		msg.msg_flags |= MSG_TRUNC;

	iov_iter_kvec(&msg.msg_iter, READ, &iov, 1, len);
	r = sock_recvmsg(sock, &msg, msg.msg_flags);
	अगर (r == -EAGAIN)
		r = 0;
	वापस r;
पूर्ण

अटल पूर्णांक ceph_tcp_recvpage(काष्ठा socket *sock, काष्ठा page *page,
		     पूर्णांक page_offset, माप_प्रकार length)
अणु
	काष्ठा bio_vec bvec = अणु
		.bv_page = page,
		.bv_offset = page_offset,
		.bv_len = length
	पूर्ण;
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL पूर्ण;
	पूर्णांक r;

	BUG_ON(page_offset + length > PAGE_SIZE);
	iov_iter_bvec(&msg.msg_iter, READ, &bvec, 1, length);
	r = sock_recvmsg(sock, &msg, msg.msg_flags);
	अगर (r == -EAGAIN)
		r = 0;
	वापस r;
पूर्ण

/*
 * ग_लिखो something.  @more is true अगर caller will be sending more data
 * लघुly.
 */
अटल पूर्णांक ceph_tcp_sendmsg(काष्ठा socket *sock, काष्ठा kvec *iov,
			    माप_प्रकार kvlen, माप_प्रकार len, bool more)
अणु
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL पूर्ण;
	पूर्णांक r;

	अगर (more)
		msg.msg_flags |= MSG_MORE;
	अन्यथा
		msg.msg_flags |= MSG_EOR;  /* superfluous, but what the hell */

	r = kernel_sendmsg(sock, &msg, iov, kvlen, len);
	अगर (r == -EAGAIN)
		r = 0;
	वापस r;
पूर्ण

/*
 * @more: either or both of MSG_MORE and MSG_SENDPAGE_NOTLAST
 */
अटल पूर्णांक ceph_tcp_sendpage(काष्ठा socket *sock, काष्ठा page *page,
			     पूर्णांक offset, माप_प्रकार size, पूर्णांक more)
अणु
	sमाप_प्रकार (*sendpage)(काष्ठा socket *sock, काष्ठा page *page,
			    पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);
	पूर्णांक flags = MSG_DONTWAIT | MSG_NOSIGNAL | more;
	पूर्णांक ret;

	/*
	 * sendpage cannot properly handle pages with page_count == 0,
	 * we need to fall back to sendmsg अगर that's the हाल.
	 *
	 * Same goes क्रम slab pages: skb_can_coalesce() allows
	 * coalescing neighboring slab objects पूर्णांकo a single frag which
	 * triggers one of hardened usercopy checks.
	 */
	अगर (sendpage_ok(page))
		sendpage = sock->ops->sendpage;
	अन्यथा
		sendpage = sock_no_sendpage;

	ret = sendpage(sock, page, offset, size, flags);
	अगर (ret == -EAGAIN)
		ret = 0;

	वापस ret;
पूर्ण

अटल व्योम con_out_kvec_reset(काष्ठा ceph_connection *con)
अणु
	BUG_ON(con->v1.out_skip);

	con->v1.out_kvec_left = 0;
	con->v1.out_kvec_bytes = 0;
	con->v1.out_kvec_cur = &con->v1.out_kvec[0];
पूर्ण

अटल व्योम con_out_kvec_add(काष्ठा ceph_connection *con,
				माप_प्रकार size, व्योम *data)
अणु
	पूर्णांक index = con->v1.out_kvec_left;

	BUG_ON(con->v1.out_skip);
	BUG_ON(index >= ARRAY_SIZE(con->v1.out_kvec));

	con->v1.out_kvec[index].iov_len = size;
	con->v1.out_kvec[index].iov_base = data;
	con->v1.out_kvec_left++;
	con->v1.out_kvec_bytes += size;
पूर्ण

/*
 * Chop off a kvec from the end.  Return residual number of bytes क्रम
 * that kvec, i.e. how many bytes would have been written अगर the kvec
 * hadn't been nuked.
 */
अटल पूर्णांक con_out_kvec_skip(काष्ठा ceph_connection *con)
अणु
	पूर्णांक skip = 0;

	अगर (con->v1.out_kvec_bytes > 0) अणु
		skip = con->v1.out_kvec_cur[con->v1.out_kvec_left - 1].iov_len;
		BUG_ON(con->v1.out_kvec_bytes < skip);
		BUG_ON(!con->v1.out_kvec_left);
		con->v1.out_kvec_bytes -= skip;
		con->v1.out_kvec_left--;
	पूर्ण

	वापस skip;
पूर्ण

अटल माप_प्रकार माप_footer(काष्ठा ceph_connection *con)
अणु
	वापस (con->peer_features & CEPH_FEATURE_MSG_AUTH) ?
	    माप(काष्ठा ceph_msg_footer) :
	    माप(काष्ठा ceph_msg_footer_old);
पूर्ण

अटल व्योम prepare_message_data(काष्ठा ceph_msg *msg, u32 data_len)
अणु
	/* Initialize data cursor */

	ceph_msg_data_cursor_init(&msg->cursor, msg, data_len);
पूर्ण

/*
 * Prepare footer क्रम currently outgoing message, and finish things
 * off.  Assumes out_kvec* are alपढ़ोy valid.. we just add on to the end.
 */
अटल व्योम prepare_ग_लिखो_message_footer(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_msg *m = con->out_msg;

	m->footer.flags |= CEPH_MSG_FOOTER_COMPLETE;

	करोut("prepare_write_message_footer %p\n", con);
	con_out_kvec_add(con, माप_footer(con), &m->footer);
	अगर (con->peer_features & CEPH_FEATURE_MSG_AUTH) अणु
		अगर (con->ops->sign_message)
			con->ops->sign_message(m);
		अन्यथा
			m->footer.sig = 0;
	पूर्ण अन्यथा अणु
		m->old_footer.flags = m->footer.flags;
	पूर्ण
	con->v1.out_more = m->more_to_follow;
	con->v1.out_msg_करोne = true;
पूर्ण

/*
 * Prepare headers क्रम the next outgoing message.
 */
अटल व्योम prepare_ग_लिखो_message(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_msg *m;
	u32 crc;

	con_out_kvec_reset(con);
	con->v1.out_msg_करोne = false;

	/* Sneak an ack in there first?  If we can get it पूर्णांकo the same
	 * TCP packet that's a good thing. */
	अगर (con->in_seq > con->in_seq_acked) अणु
		con->in_seq_acked = con->in_seq;
		con_out_kvec_add(con, माप (tag_ack), &tag_ack);
		con->v1.out_temp_ack = cpu_to_le64(con->in_seq_acked);
		con_out_kvec_add(con, माप(con->v1.out_temp_ack),
			&con->v1.out_temp_ack);
	पूर्ण

	ceph_con_get_out_msg(con);
	m = con->out_msg;

	करोut("prepare_write_message %p seq %lld type %d len %d+%d+%zd\n",
	     m, con->out_seq, le16_to_cpu(m->hdr.type),
	     le32_to_cpu(m->hdr.front_len), le32_to_cpu(m->hdr.middle_len),
	     m->data_length);
	WARN_ON(m->front.iov_len != le32_to_cpu(m->hdr.front_len));
	WARN_ON(m->data_length != le32_to_cpu(m->hdr.data_len));

	/* tag + hdr + front + middle */
	con_out_kvec_add(con, माप (tag_msg), &tag_msg);
	con_out_kvec_add(con, माप(con->v1.out_hdr), &con->v1.out_hdr);
	con_out_kvec_add(con, m->front.iov_len, m->front.iov_base);

	अगर (m->middle)
		con_out_kvec_add(con, m->middle->vec.iov_len,
			m->middle->vec.iov_base);

	/* fill in hdr crc and finalize hdr */
	crc = crc32c(0, &m->hdr, दुरत्व(काष्ठा ceph_msg_header, crc));
	con->out_msg->hdr.crc = cpu_to_le32(crc);
	स_नकल(&con->v1.out_hdr, &con->out_msg->hdr, माप(con->v1.out_hdr));

	/* fill in front and middle crc, footer */
	crc = crc32c(0, m->front.iov_base, m->front.iov_len);
	con->out_msg->footer.front_crc = cpu_to_le32(crc);
	अगर (m->middle) अणु
		crc = crc32c(0, m->middle->vec.iov_base,
				m->middle->vec.iov_len);
		con->out_msg->footer.middle_crc = cpu_to_le32(crc);
	पूर्ण अन्यथा
		con->out_msg->footer.middle_crc = 0;
	करोut("%s front_crc %u middle_crc %u\n", __func__,
	     le32_to_cpu(con->out_msg->footer.front_crc),
	     le32_to_cpu(con->out_msg->footer.middle_crc));
	con->out_msg->footer.flags = 0;

	/* is there a data payload? */
	con->out_msg->footer.data_crc = 0;
	अगर (m->data_length) अणु
		prepare_message_data(con->out_msg, m->data_length);
		con->v1.out_more = 1;  /* data + footer will follow */
	पूर्ण अन्यथा अणु
		/* no, queue up footer too and be करोne */
		prepare_ग_लिखो_message_footer(con);
	पूर्ण

	ceph_con_flag_set(con, CEPH_CON_F_WRITE_PENDING);
पूर्ण

/*
 * Prepare an ack.
 */
अटल व्योम prepare_ग_लिखो_ack(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_write_ack %p %llu -> %llu\n", con,
	     con->in_seq_acked, con->in_seq);
	con->in_seq_acked = con->in_seq;

	con_out_kvec_reset(con);

	con_out_kvec_add(con, माप (tag_ack), &tag_ack);

	con->v1.out_temp_ack = cpu_to_le64(con->in_seq_acked);
	con_out_kvec_add(con, माप(con->v1.out_temp_ack),
			 &con->v1.out_temp_ack);

	con->v1.out_more = 1;  /* more will follow.. eventually.. */
	ceph_con_flag_set(con, CEPH_CON_F_WRITE_PENDING);
पूर्ण

/*
 * Prepare to share the seq during handshake
 */
अटल व्योम prepare_ग_लिखो_seq(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_write_seq %p %llu -> %llu\n", con,
	     con->in_seq_acked, con->in_seq);
	con->in_seq_acked = con->in_seq;

	con_out_kvec_reset(con);

	con->v1.out_temp_ack = cpu_to_le64(con->in_seq_acked);
	con_out_kvec_add(con, माप(con->v1.out_temp_ack),
			 &con->v1.out_temp_ack);

	ceph_con_flag_set(con, CEPH_CON_F_WRITE_PENDING);
पूर्ण

/*
 * Prepare to ग_लिखो keepalive byte.
 */
अटल व्योम prepare_ग_लिखो_keepalive(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_write_keepalive %p\n", con);
	con_out_kvec_reset(con);
	अगर (con->peer_features & CEPH_FEATURE_MSGR_KEEPALIVE2) अणु
		काष्ठा बारpec64 now;

		kसमय_get_real_ts64(&now);
		con_out_kvec_add(con, माप(tag_keepalive2), &tag_keepalive2);
		ceph_encode_बारpec64(&con->v1.out_temp_keepalive2, &now);
		con_out_kvec_add(con, माप(con->v1.out_temp_keepalive2),
				 &con->v1.out_temp_keepalive2);
	पूर्ण अन्यथा अणु
		con_out_kvec_add(con, माप(tag_keepalive), &tag_keepalive);
	पूर्ण
	ceph_con_flag_set(con, CEPH_CON_F_WRITE_PENDING);
पूर्ण

/*
 * Connection negotiation.
 */

अटल पूर्णांक get_connect_authorizer(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_auth_handshake *auth;
	पूर्णांक auth_proto;

	अगर (!con->ops->get_authorizer) अणु
		con->v1.auth = शून्य;
		con->v1.out_connect.authorizer_protocol = CEPH_AUTH_UNKNOWN;
		con->v1.out_connect.authorizer_len = 0;
		वापस 0;
	पूर्ण

	auth = con->ops->get_authorizer(con, &auth_proto, con->v1.auth_retry);
	अगर (IS_ERR(auth))
		वापस PTR_ERR(auth);

	con->v1.auth = auth;
	con->v1.out_connect.authorizer_protocol = cpu_to_le32(auth_proto);
	con->v1.out_connect.authorizer_len =
		cpu_to_le32(auth->authorizer_buf_len);
	वापस 0;
पूर्ण

/*
 * We connected to a peer and are saying hello.
 */
अटल व्योम prepare_ग_लिखो_banner(काष्ठा ceph_connection *con)
अणु
	con_out_kvec_add(con, म_माप(CEPH_BANNER), CEPH_BANNER);
	con_out_kvec_add(con, माप (con->msgr->my_enc_addr),
					&con->msgr->my_enc_addr);

	con->v1.out_more = 0;
	ceph_con_flag_set(con, CEPH_CON_F_WRITE_PENDING);
पूर्ण

अटल व्योम __prepare_ग_लिखो_connect(काष्ठा ceph_connection *con)
अणु
	con_out_kvec_add(con, माप(con->v1.out_connect),
			 &con->v1.out_connect);
	अगर (con->v1.auth)
		con_out_kvec_add(con, con->v1.auth->authorizer_buf_len,
				 con->v1.auth->authorizer_buf);

	con->v1.out_more = 0;
	ceph_con_flag_set(con, CEPH_CON_F_WRITE_PENDING);
पूर्ण

अटल पूर्णांक prepare_ग_लिखो_connect(काष्ठा ceph_connection *con)
अणु
	अचिन्हित पूर्णांक global_seq = ceph_get_global_seq(con->msgr, 0);
	पूर्णांक proto;
	पूर्णांक ret;

	चयन (con->peer_name.type) अणु
	हाल CEPH_ENTITY_TYPE_MON:
		proto = CEPH_MONC_PROTOCOL;
		अवरोध;
	हाल CEPH_ENTITY_TYPE_OSD:
		proto = CEPH_OSDC_PROTOCOL;
		अवरोध;
	हाल CEPH_ENTITY_TYPE_MDS:
		proto = CEPH_MDSC_PROTOCOL;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	करोut("prepare_write_connect %p cseq=%d gseq=%d proto=%d\n", con,
	     con->v1.connect_seq, global_seq, proto);

	con->v1.out_connect.features =
		cpu_to_le64(from_msgr(con->msgr)->supported_features);
	con->v1.out_connect.host_type = cpu_to_le32(CEPH_ENTITY_TYPE_CLIENT);
	con->v1.out_connect.connect_seq = cpu_to_le32(con->v1.connect_seq);
	con->v1.out_connect.global_seq = cpu_to_le32(global_seq);
	con->v1.out_connect.protocol_version = cpu_to_le32(proto);
	con->v1.out_connect.flags = 0;

	ret = get_connect_authorizer(con);
	अगर (ret)
		वापस ret;

	__prepare_ग_लिखो_connect(con);
	वापस 0;
पूर्ण

/*
 * ग_लिखो as much of pending kvecs to the socket as we can.
 *  1 -> करोne
 *  0 -> socket full, but more to करो
 * <0 -> error
 */
अटल पूर्णांक ग_लिखो_partial_kvec(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret;

	करोut("write_partial_kvec %p %d left\n", con, con->v1.out_kvec_bytes);
	जबतक (con->v1.out_kvec_bytes > 0) अणु
		ret = ceph_tcp_sendmsg(con->sock, con->v1.out_kvec_cur,
				       con->v1.out_kvec_left,
				       con->v1.out_kvec_bytes,
				       con->v1.out_more);
		अगर (ret <= 0)
			जाओ out;
		con->v1.out_kvec_bytes -= ret;
		अगर (!con->v1.out_kvec_bytes)
			अवरोध;            /* करोne */

		/* account क्रम full iov entries consumed */
		जबतक (ret >= con->v1.out_kvec_cur->iov_len) अणु
			BUG_ON(!con->v1.out_kvec_left);
			ret -= con->v1.out_kvec_cur->iov_len;
			con->v1.out_kvec_cur++;
			con->v1.out_kvec_left--;
		पूर्ण
		/* and क्रम a partially-consumed entry */
		अगर (ret) अणु
			con->v1.out_kvec_cur->iov_len -= ret;
			con->v1.out_kvec_cur->iov_base += ret;
		पूर्ण
	पूर्ण
	con->v1.out_kvec_left = 0;
	ret = 1;
out:
	करोut("write_partial_kvec %p %d left in %d kvecs ret = %d\n", con,
	     con->v1.out_kvec_bytes, con->v1.out_kvec_left, ret);
	वापस ret;  /* करोne! */
पूर्ण

/*
 * Write as much message data payload as we can.  If we finish, queue
 * up the footer.
 *  1 -> करोne, footer is now queued in out_kvec[].
 *  0 -> socket full, but more to करो
 * <0 -> error
 */
अटल पूर्णांक ग_लिखो_partial_message_data(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_msg *msg = con->out_msg;
	काष्ठा ceph_msg_data_cursor *cursor = &msg->cursor;
	bool करो_datacrc = !ceph_test_opt(from_msgr(con->msgr), NOCRC);
	पूर्णांक more = MSG_MORE | MSG_SENDPAGE_NOTLAST;
	u32 crc;

	करोut("%s %p msg %p\n", __func__, con, msg);

	अगर (!msg->num_data_items)
		वापस -EINVAL;

	/*
	 * Iterate through each page that contains data to be
	 * written, and send as much as possible क्रम each.
	 *
	 * If we are calculating the data crc (the शेष), we will
	 * need to map the page.  If we have no pages, they have
	 * been revoked, so use the zero page.
	 */
	crc = करो_datacrc ? le32_to_cpu(msg->footer.data_crc) : 0;
	जबतक (cursor->total_resid) अणु
		काष्ठा page *page;
		माप_प्रकार page_offset;
		माप_प्रकार length;
		पूर्णांक ret;

		अगर (!cursor->resid) अणु
			ceph_msg_data_advance(cursor, 0);
			जारी;
		पूर्ण

		page = ceph_msg_data_next(cursor, &page_offset, &length, शून्य);
		अगर (length == cursor->total_resid)
			more = MSG_MORE;
		ret = ceph_tcp_sendpage(con->sock, page, page_offset, length,
					more);
		अगर (ret <= 0) अणु
			अगर (करो_datacrc)
				msg->footer.data_crc = cpu_to_le32(crc);

			वापस ret;
		पूर्ण
		अगर (करो_datacrc && cursor->need_crc)
			crc = ceph_crc32c_page(crc, page, page_offset, length);
		ceph_msg_data_advance(cursor, (माप_प्रकार)ret);
	पूर्ण

	करोut("%s %p msg %p done\n", __func__, con, msg);

	/* prepare and queue up footer, too */
	अगर (करो_datacrc)
		msg->footer.data_crc = cpu_to_le32(crc);
	अन्यथा
		msg->footer.flags |= CEPH_MSG_FOOTER_NOCRC;
	con_out_kvec_reset(con);
	prepare_ग_लिखो_message_footer(con);

	वापस 1;	/* must वापस > 0 to indicate success */
पूर्ण

/*
 * ग_लिखो some zeros
 */
अटल पूर्णांक ग_लिखो_partial_skip(काष्ठा ceph_connection *con)
अणु
	पूर्णांक more = MSG_MORE | MSG_SENDPAGE_NOTLAST;
	पूर्णांक ret;

	करोut("%s %p %d left\n", __func__, con, con->v1.out_skip);
	जबतक (con->v1.out_skip > 0) अणु
		माप_प्रकार size = min(con->v1.out_skip, (पूर्णांक)PAGE_SIZE);

		अगर (size == con->v1.out_skip)
			more = MSG_MORE;
		ret = ceph_tcp_sendpage(con->sock, ceph_zero_page, 0, size,
					more);
		अगर (ret <= 0)
			जाओ out;
		con->v1.out_skip -= ret;
	पूर्ण
	ret = 1;
out:
	वापस ret;
पूर्ण

/*
 * Prepare to पढ़ो connection handshake, or an ack.
 */
अटल व्योम prepare_पढ़ो_banner(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_read_banner %p\n", con);
	con->v1.in_base_pos = 0;
पूर्ण

अटल व्योम prepare_पढ़ो_connect(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_read_connect %p\n", con);
	con->v1.in_base_pos = 0;
पूर्ण

अटल व्योम prepare_पढ़ो_ack(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_read_ack %p\n", con);
	con->v1.in_base_pos = 0;
पूर्ण

अटल व्योम prepare_पढ़ो_seq(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_read_seq %p\n", con);
	con->v1.in_base_pos = 0;
	con->v1.in_tag = CEPH_MSGR_TAG_SEQ;
पूर्ण

अटल व्योम prepare_पढ़ो_tag(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_read_tag %p\n", con);
	con->v1.in_base_pos = 0;
	con->v1.in_tag = CEPH_MSGR_TAG_READY;
पूर्ण

अटल व्योम prepare_पढ़ो_keepalive_ack(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_read_keepalive_ack %p\n", con);
	con->v1.in_base_pos = 0;
पूर्ण

/*
 * Prepare to पढ़ो a message.
 */
अटल पूर्णांक prepare_पढ़ो_message(काष्ठा ceph_connection *con)
अणु
	करोut("prepare_read_message %p\n", con);
	BUG_ON(con->in_msg != शून्य);
	con->v1.in_base_pos = 0;
	con->in_front_crc = con->in_middle_crc = con->in_data_crc = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_partial(काष्ठा ceph_connection *con,
			पूर्णांक end, पूर्णांक size, व्योम *object)
अणु
	जबतक (con->v1.in_base_pos < end) अणु
		पूर्णांक left = end - con->v1.in_base_pos;
		पूर्णांक have = size - left;
		पूर्णांक ret = ceph_tcp_recvmsg(con->sock, object + have, left);
		अगर (ret <= 0)
			वापस ret;
		con->v1.in_base_pos += ret;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Read all or part of the connect-side handshake on a new connection
 */
अटल पूर्णांक पढ़ो_partial_banner(काष्ठा ceph_connection *con)
अणु
	पूर्णांक size;
	पूर्णांक end;
	पूर्णांक ret;

	करोut("read_partial_banner %p at %d\n", con, con->v1.in_base_pos);

	/* peer's banner */
	size = म_माप(CEPH_BANNER);
	end = size;
	ret = पढ़ो_partial(con, end, size, con->v1.in_banner);
	अगर (ret <= 0)
		जाओ out;

	size = माप(con->v1.actual_peer_addr);
	end += size;
	ret = पढ़ो_partial(con, end, size, &con->v1.actual_peer_addr);
	अगर (ret <= 0)
		जाओ out;
	ceph_decode_banner_addr(&con->v1.actual_peer_addr);

	size = माप(con->v1.peer_addr_क्रम_me);
	end += size;
	ret = पढ़ो_partial(con, end, size, &con->v1.peer_addr_क्रम_me);
	अगर (ret <= 0)
		जाओ out;
	ceph_decode_banner_addr(&con->v1.peer_addr_क्रम_me);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_partial_connect(काष्ठा ceph_connection *con)
अणु
	पूर्णांक size;
	पूर्णांक end;
	पूर्णांक ret;

	करोut("read_partial_connect %p at %d\n", con, con->v1.in_base_pos);

	size = माप(con->v1.in_reply);
	end = size;
	ret = पढ़ो_partial(con, end, size, &con->v1.in_reply);
	अगर (ret <= 0)
		जाओ out;

	अगर (con->v1.auth) अणु
		size = le32_to_cpu(con->v1.in_reply.authorizer_len);
		अगर (size > con->v1.auth->authorizer_reply_buf_len) अणु
			pr_err("authorizer reply too big: %d > %zu\n", size,
			       con->v1.auth->authorizer_reply_buf_len);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		end += size;
		ret = पढ़ो_partial(con, end, size,
				   con->v1.auth->authorizer_reply_buf);
		अगर (ret <= 0)
			जाओ out;
	पूर्ण

	करोut("read_partial_connect %p tag %d, con_seq = %u, g_seq = %u\n",
	     con, con->v1.in_reply.tag,
	     le32_to_cpu(con->v1.in_reply.connect_seq),
	     le32_to_cpu(con->v1.in_reply.global_seq));
out:
	वापस ret;
पूर्ण

/*
 * Verअगरy the hello banner looks okay.
 */
अटल पूर्णांक verअगरy_hello(काष्ठा ceph_connection *con)
अणु
	अगर (स_भेद(con->v1.in_banner, CEPH_BANNER, म_माप(CEPH_BANNER))) अणु
		pr_err("connect to %s got bad banner\n",
		       ceph_pr_addr(&con->peer_addr));
		con->error_msg = "protocol error, bad banner";
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक process_banner(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_entity_addr *my_addr = &con->msgr->inst.addr;

	करोut("process_banner on %p\n", con);

	अगर (verअगरy_hello(con) < 0)
		वापस -1;

	/*
	 * Make sure the other end is who we wanted.  note that the other
	 * end may not yet know their ip address, so अगर it's 0.0.0.0, give
	 * them the benefit of the करोubt.
	 */
	अगर (स_भेद(&con->peer_addr, &con->v1.actual_peer_addr,
		   माप(con->peer_addr)) != 0 &&
	    !(ceph_addr_is_blank(&con->v1.actual_peer_addr) &&
	      con->v1.actual_peer_addr.nonce == con->peer_addr.nonce)) अणु
		pr_warn("wrong peer, want %s/%u, got %s/%u\n",
			ceph_pr_addr(&con->peer_addr),
			le32_to_cpu(con->peer_addr.nonce),
			ceph_pr_addr(&con->v1.actual_peer_addr),
			le32_to_cpu(con->v1.actual_peer_addr.nonce));
		con->error_msg = "wrong peer at address";
		वापस -1;
	पूर्ण

	/*
	 * did we learn our address?
	 */
	अगर (ceph_addr_is_blank(my_addr)) अणु
		स_नकल(&my_addr->in_addr,
		       &con->v1.peer_addr_क्रम_me.in_addr,
		       माप(con->v1.peer_addr_क्रम_me.in_addr));
		ceph_addr_set_port(my_addr, 0);
		ceph_encode_my_addr(con->msgr);
		करोut("process_banner learned my addr is %s\n",
		     ceph_pr_addr(my_addr));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_connect(काष्ठा ceph_connection *con)
अणु
	u64 sup_feat = from_msgr(con->msgr)->supported_features;
	u64 req_feat = from_msgr(con->msgr)->required_features;
	u64 server_feat = le64_to_cpu(con->v1.in_reply.features);
	पूर्णांक ret;

	करोut("process_connect on %p tag %d\n", con, con->v1.in_tag);

	अगर (con->v1.auth) अणु
		पूर्णांक len = le32_to_cpu(con->v1.in_reply.authorizer_len);

		/*
		 * Any connection that defines ->get_authorizer()
		 * should also define ->add_authorizer_challenge() and
		 * ->verअगरy_authorizer_reply().
		 *
		 * See get_connect_authorizer().
		 */
		अगर (con->v1.in_reply.tag ==
				CEPH_MSGR_TAG_CHALLENGE_AUTHORIZER) अणु
			ret = con->ops->add_authorizer_challenge(
				con, con->v1.auth->authorizer_reply_buf, len);
			अगर (ret < 0)
				वापस ret;

			con_out_kvec_reset(con);
			__prepare_ग_लिखो_connect(con);
			prepare_पढ़ो_connect(con);
			वापस 0;
		पूर्ण

		अगर (len) अणु
			ret = con->ops->verअगरy_authorizer_reply(con);
			अगर (ret < 0) अणु
				con->error_msg = "bad authorize reply";
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (con->v1.in_reply.tag) अणु
	हाल CEPH_MSGR_TAG_FEATURES:
		pr_err("%s%lld %s feature set mismatch,"
		       " my %llx < server's %llx, missing %llx\n",
		       ENTITY_NAME(con->peer_name),
		       ceph_pr_addr(&con->peer_addr),
		       sup_feat, server_feat, server_feat & ~sup_feat);
		con->error_msg = "missing required protocol features";
		वापस -1;

	हाल CEPH_MSGR_TAG_BADPROTOVER:
		pr_err("%s%lld %s protocol version mismatch,"
		       " my %d != server's %d\n",
		       ENTITY_NAME(con->peer_name),
		       ceph_pr_addr(&con->peer_addr),
		       le32_to_cpu(con->v1.out_connect.protocol_version),
		       le32_to_cpu(con->v1.in_reply.protocol_version));
		con->error_msg = "protocol version mismatch";
		वापस -1;

	हाल CEPH_MSGR_TAG_BADAUTHORIZER:
		con->v1.auth_retry++;
		करोut("process_connect %p got BADAUTHORIZER attempt %d\n", con,
		     con->v1.auth_retry);
		अगर (con->v1.auth_retry == 2) अणु
			con->error_msg = "connect authorization failure";
			वापस -1;
		पूर्ण
		con_out_kvec_reset(con);
		ret = prepare_ग_लिखो_connect(con);
		अगर (ret < 0)
			वापस ret;
		prepare_पढ़ो_connect(con);
		अवरोध;

	हाल CEPH_MSGR_TAG_RESETSESSION:
		/*
		 * If we connected with a large connect_seq but the peer
		 * has no record of a session with us (no connection, or
		 * connect_seq == 0), they will send RESETSESION to indicate
		 * that they must have reset their session, and may have
		 * dropped messages.
		 */
		करोut("process_connect got RESET peer seq %u\n",
		     le32_to_cpu(con->v1.in_reply.connect_seq));
		pr_info("%s%lld %s session reset\n",
			ENTITY_NAME(con->peer_name),
			ceph_pr_addr(&con->peer_addr));
		ceph_con_reset_session(con);
		con_out_kvec_reset(con);
		ret = prepare_ग_लिखो_connect(con);
		अगर (ret < 0)
			वापस ret;
		prepare_पढ़ो_connect(con);

		/* Tell ceph about it. */
		mutex_unlock(&con->mutex);
		अगर (con->ops->peer_reset)
			con->ops->peer_reset(con);
		mutex_lock(&con->mutex);
		अगर (con->state != CEPH_CON_S_V1_CONNECT_MSG)
			वापस -EAGAIN;
		अवरोध;

	हाल CEPH_MSGR_TAG_RETRY_SESSION:
		/*
		 * If we sent a smaller connect_seq than the peer has, try
		 * again with a larger value.
		 */
		करोut("process_connect got RETRY_SESSION my seq %u, peer %u\n",
		     le32_to_cpu(con->v1.out_connect.connect_seq),
		     le32_to_cpu(con->v1.in_reply.connect_seq));
		con->v1.connect_seq = le32_to_cpu(con->v1.in_reply.connect_seq);
		con_out_kvec_reset(con);
		ret = prepare_ग_लिखो_connect(con);
		अगर (ret < 0)
			वापस ret;
		prepare_पढ़ो_connect(con);
		अवरोध;

	हाल CEPH_MSGR_TAG_RETRY_GLOBAL:
		/*
		 * If we sent a smaller global_seq than the peer has, try
		 * again with a larger value.
		 */
		करोut("process_connect got RETRY_GLOBAL my %u peer_gseq %u\n",
		     con->v1.peer_global_seq,
		     le32_to_cpu(con->v1.in_reply.global_seq));
		ceph_get_global_seq(con->msgr,
				    le32_to_cpu(con->v1.in_reply.global_seq));
		con_out_kvec_reset(con);
		ret = prepare_ग_लिखो_connect(con);
		अगर (ret < 0)
			वापस ret;
		prepare_पढ़ो_connect(con);
		अवरोध;

	हाल CEPH_MSGR_TAG_SEQ:
	हाल CEPH_MSGR_TAG_READY:
		अगर (req_feat & ~server_feat) अणु
			pr_err("%s%lld %s protocol feature mismatch,"
			       " my required %llx > server's %llx, need %llx\n",
			       ENTITY_NAME(con->peer_name),
			       ceph_pr_addr(&con->peer_addr),
			       req_feat, server_feat, req_feat & ~server_feat);
			con->error_msg = "missing required protocol features";
			वापस -1;
		पूर्ण

		WARN_ON(con->state != CEPH_CON_S_V1_CONNECT_MSG);
		con->state = CEPH_CON_S_OPEN;
		con->v1.auth_retry = 0;    /* we authenticated; clear flag */
		con->v1.peer_global_seq =
			le32_to_cpu(con->v1.in_reply.global_seq);
		con->v1.connect_seq++;
		con->peer_features = server_feat;
		करोut("process_connect got READY gseq %d cseq %d (%d)\n",
		     con->v1.peer_global_seq,
		     le32_to_cpu(con->v1.in_reply.connect_seq),
		     con->v1.connect_seq);
		WARN_ON(con->v1.connect_seq !=
			le32_to_cpu(con->v1.in_reply.connect_seq));

		अगर (con->v1.in_reply.flags & CEPH_MSG_CONNECT_LOSSY)
			ceph_con_flag_set(con, CEPH_CON_F_LOSSYTX);

		con->delay = 0;      /* reset backoff memory */

		अगर (con->v1.in_reply.tag == CEPH_MSGR_TAG_SEQ) अणु
			prepare_ग_लिखो_seq(con);
			prepare_पढ़ो_seq(con);
		पूर्ण अन्यथा अणु
			prepare_पढ़ो_tag(con);
		पूर्ण
		अवरोध;

	हाल CEPH_MSGR_TAG_WAIT:
		/*
		 * If there is a connection race (we are खोलोing
		 * connections to each other), one of us may just have
		 * to WAIT.  This shouldn't happen अगर we are the
		 * client.
		 */
		con->error_msg = "protocol error, got WAIT as client";
		वापस -1;

	शेष:
		con->error_msg = "protocol error, garbage tag during connect";
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * पढ़ो (part of) an ack
 */
अटल पूर्णांक पढ़ो_partial_ack(काष्ठा ceph_connection *con)
अणु
	पूर्णांक size = माप(con->v1.in_temp_ack);
	पूर्णांक end = size;

	वापस पढ़ो_partial(con, end, size, &con->v1.in_temp_ack);
पूर्ण

/*
 * We can finally discard anything that's been acked.
 */
अटल व्योम process_ack(काष्ठा ceph_connection *con)
अणु
	u64 ack = le64_to_cpu(con->v1.in_temp_ack);

	अगर (con->v1.in_tag == CEPH_MSGR_TAG_ACK)
		ceph_con_discard_sent(con, ack);
	अन्यथा
		ceph_con_discard_requeued(con, ack);

	prepare_पढ़ो_tag(con);
पूर्ण

अटल पूर्णांक पढ़ो_partial_message_section(काष्ठा ceph_connection *con,
					काष्ठा kvec *section,
					अचिन्हित पूर्णांक sec_len, u32 *crc)
अणु
	पूर्णांक ret, left;

	BUG_ON(!section);

	जबतक (section->iov_len < sec_len) अणु
		BUG_ON(section->iov_base == शून्य);
		left = sec_len - section->iov_len;
		ret = ceph_tcp_recvmsg(con->sock, (अक्षर *)section->iov_base +
				       section->iov_len, left);
		अगर (ret <= 0)
			वापस ret;
		section->iov_len += ret;
	पूर्ण
	अगर (section->iov_len == sec_len)
		*crc = crc32c(0, section->iov_base, section->iov_len);

	वापस 1;
पूर्ण

अटल पूर्णांक पढ़ो_partial_msg_data(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_msg *msg = con->in_msg;
	काष्ठा ceph_msg_data_cursor *cursor = &msg->cursor;
	bool करो_datacrc = !ceph_test_opt(from_msgr(con->msgr), NOCRC);
	काष्ठा page *page;
	माप_प्रकार page_offset;
	माप_प्रकार length;
	u32 crc = 0;
	पूर्णांक ret;

	अगर (!msg->num_data_items)
		वापस -EIO;

	अगर (करो_datacrc)
		crc = con->in_data_crc;
	जबतक (cursor->total_resid) अणु
		अगर (!cursor->resid) अणु
			ceph_msg_data_advance(cursor, 0);
			जारी;
		पूर्ण

		page = ceph_msg_data_next(cursor, &page_offset, &length, शून्य);
		ret = ceph_tcp_recvpage(con->sock, page, page_offset, length);
		अगर (ret <= 0) अणु
			अगर (करो_datacrc)
				con->in_data_crc = crc;

			वापस ret;
		पूर्ण

		अगर (करो_datacrc)
			crc = ceph_crc32c_page(crc, page, page_offset, ret);
		ceph_msg_data_advance(cursor, (माप_प्रकार)ret);
	पूर्ण
	अगर (करो_datacrc)
		con->in_data_crc = crc;

	वापस 1;	/* must वापस > 0 to indicate success */
पूर्ण

/*
 * पढ़ो (part of) a message.
 */
अटल पूर्णांक पढ़ो_partial_message(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_msg *m = con->in_msg;
	पूर्णांक size;
	पूर्णांक end;
	पूर्णांक ret;
	अचिन्हित पूर्णांक front_len, middle_len, data_len;
	bool करो_datacrc = !ceph_test_opt(from_msgr(con->msgr), NOCRC);
	bool need_sign = (con->peer_features & CEPH_FEATURE_MSG_AUTH);
	u64 seq;
	u32 crc;

	करोut("read_partial_message con %p msg %p\n", con, m);

	/* header */
	size = माप(con->v1.in_hdr);
	end = size;
	ret = पढ़ो_partial(con, end, size, &con->v1.in_hdr);
	अगर (ret <= 0)
		वापस ret;

	crc = crc32c(0, &con->v1.in_hdr, दुरत्व(काष्ठा ceph_msg_header, crc));
	अगर (cpu_to_le32(crc) != con->v1.in_hdr.crc) अणु
		pr_err("read_partial_message bad hdr crc %u != expected %u\n",
		       crc, con->v1.in_hdr.crc);
		वापस -EBADMSG;
	पूर्ण

	front_len = le32_to_cpu(con->v1.in_hdr.front_len);
	अगर (front_len > CEPH_MSG_MAX_FRONT_LEN)
		वापस -EIO;
	middle_len = le32_to_cpu(con->v1.in_hdr.middle_len);
	अगर (middle_len > CEPH_MSG_MAX_MIDDLE_LEN)
		वापस -EIO;
	data_len = le32_to_cpu(con->v1.in_hdr.data_len);
	अगर (data_len > CEPH_MSG_MAX_DATA_LEN)
		वापस -EIO;

	/* verअगरy seq# */
	seq = le64_to_cpu(con->v1.in_hdr.seq);
	अगर ((s64)seq - (s64)con->in_seq < 1) अणु
		pr_info("skipping %s%lld %s seq %lld expected %lld\n",
			ENTITY_NAME(con->peer_name),
			ceph_pr_addr(&con->peer_addr),
			seq, con->in_seq + 1);
		con->v1.in_base_pos = -front_len - middle_len - data_len -
				      माप_footer(con);
		con->v1.in_tag = CEPH_MSGR_TAG_READY;
		वापस 1;
	पूर्ण अन्यथा अगर ((s64)seq - (s64)con->in_seq > 1) अणु
		pr_err("read_partial_message bad seq %lld expected %lld\n",
		       seq, con->in_seq + 1);
		con->error_msg = "bad message sequence # for incoming message";
		वापस -EBADE;
	पूर्ण

	/* allocate message? */
	अगर (!con->in_msg) अणु
		पूर्णांक skip = 0;

		करोut("got hdr type %d front %d data %d\n", con->v1.in_hdr.type,
		     front_len, data_len);
		ret = ceph_con_in_msg_alloc(con, &con->v1.in_hdr, &skip);
		अगर (ret < 0)
			वापस ret;

		BUG_ON((!con->in_msg) ^ skip);
		अगर (skip) अणु
			/* skip this message */
			करोut("alloc_msg said skip message\n");
			con->v1.in_base_pos = -front_len - middle_len -
					      data_len - माप_footer(con);
			con->v1.in_tag = CEPH_MSGR_TAG_READY;
			con->in_seq++;
			वापस 1;
		पूर्ण

		BUG_ON(!con->in_msg);
		BUG_ON(con->in_msg->con != con);
		m = con->in_msg;
		m->front.iov_len = 0;    /* haven't पढ़ो it yet */
		अगर (m->middle)
			m->middle->vec.iov_len = 0;

		/* prepare क्रम data payload, अगर any */

		अगर (data_len)
			prepare_message_data(con->in_msg, data_len);
	पूर्ण

	/* front */
	ret = पढ़ो_partial_message_section(con, &m->front, front_len,
					   &con->in_front_crc);
	अगर (ret <= 0)
		वापस ret;

	/* middle */
	अगर (m->middle) अणु
		ret = पढ़ो_partial_message_section(con, &m->middle->vec,
						   middle_len,
						   &con->in_middle_crc);
		अगर (ret <= 0)
			वापस ret;
	पूर्ण

	/* (page) data */
	अगर (data_len) अणु
		ret = पढ़ो_partial_msg_data(con);
		अगर (ret <= 0)
			वापस ret;
	पूर्ण

	/* footer */
	size = माप_footer(con);
	end += size;
	ret = पढ़ो_partial(con, end, size, &m->footer);
	अगर (ret <= 0)
		वापस ret;

	अगर (!need_sign) अणु
		m->footer.flags = m->old_footer.flags;
		m->footer.sig = 0;
	पूर्ण

	करोut("read_partial_message got msg %p %d (%u) + %d (%u) + %d (%u)\n",
	     m, front_len, m->footer.front_crc, middle_len,
	     m->footer.middle_crc, data_len, m->footer.data_crc);

	/* crc ok? */
	अगर (con->in_front_crc != le32_to_cpu(m->footer.front_crc)) अणु
		pr_err("read_partial_message %p front crc %u != exp. %u\n",
		       m, con->in_front_crc, m->footer.front_crc);
		वापस -EBADMSG;
	पूर्ण
	अगर (con->in_middle_crc != le32_to_cpu(m->footer.middle_crc)) अणु
		pr_err("read_partial_message %p middle crc %u != exp %u\n",
		       m, con->in_middle_crc, m->footer.middle_crc);
		वापस -EBADMSG;
	पूर्ण
	अगर (करो_datacrc &&
	    (m->footer.flags & CEPH_MSG_FOOTER_NOCRC) == 0 &&
	    con->in_data_crc != le32_to_cpu(m->footer.data_crc)) अणु
		pr_err("read_partial_message %p data crc %u != exp. %u\n", m,
		       con->in_data_crc, le32_to_cpu(m->footer.data_crc));
		वापस -EBADMSG;
	पूर्ण

	अगर (need_sign && con->ops->check_message_signature &&
	    con->ops->check_message_signature(m)) अणु
		pr_err("read_partial_message %p signature check failed\n", m);
		वापस -EBADMSG;
	पूर्ण

	वापस 1; /* करोne! */
पूर्ण

अटल पूर्णांक पढ़ो_keepalive_ack(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_बारpec ceph_ts;
	माप_प्रकार size = माप(ceph_ts);
	पूर्णांक ret = पढ़ो_partial(con, size, size, &ceph_ts);
	अगर (ret <= 0)
		वापस ret;
	ceph_decode_बारpec64(&con->last_keepalive_ack, &ceph_ts);
	prepare_पढ़ो_tag(con);
	वापस 1;
पूर्ण

/*
 * Read what we can from the socket.
 */
पूर्णांक ceph_con_v1_try_पढ़ो(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret = -1;

more:
	करोut("try_read start %p state %d\n", con, con->state);
	अगर (con->state != CEPH_CON_S_V1_BANNER &&
	    con->state != CEPH_CON_S_V1_CONNECT_MSG &&
	    con->state != CEPH_CON_S_OPEN)
		वापस 0;

	BUG_ON(!con->sock);

	करोut("try_read tag %d in_base_pos %d\n", con->v1.in_tag,
	     con->v1.in_base_pos);

	अगर (con->state == CEPH_CON_S_V1_BANNER) अणु
		ret = पढ़ो_partial_banner(con);
		अगर (ret <= 0)
			जाओ out;
		ret = process_banner(con);
		अगर (ret < 0)
			जाओ out;

		con->state = CEPH_CON_S_V1_CONNECT_MSG;

		/*
		 * Received banner is good, exchange connection info.
		 * Do not reset out_kvec, as sending our banner raced
		 * with receiving peer banner after connect completed.
		 */
		ret = prepare_ग_लिखो_connect(con);
		अगर (ret < 0)
			जाओ out;
		prepare_पढ़ो_connect(con);

		/* Send connection info beक्रमe aरुकोing response */
		जाओ out;
	पूर्ण

	अगर (con->state == CEPH_CON_S_V1_CONNECT_MSG) अणु
		ret = पढ़ो_partial_connect(con);
		अगर (ret <= 0)
			जाओ out;
		ret = process_connect(con);
		अगर (ret < 0)
			जाओ out;
		जाओ more;
	पूर्ण

	WARN_ON(con->state != CEPH_CON_S_OPEN);

	अगर (con->v1.in_base_pos < 0) अणु
		/*
		 * skipping + discarding content.
		 */
		ret = ceph_tcp_recvmsg(con->sock, शून्य, -con->v1.in_base_pos);
		अगर (ret <= 0)
			जाओ out;
		करोut("skipped %d / %d bytes\n", ret, -con->v1.in_base_pos);
		con->v1.in_base_pos += ret;
		अगर (con->v1.in_base_pos)
			जाओ more;
	पूर्ण
	अगर (con->v1.in_tag == CEPH_MSGR_TAG_READY) अणु
		/*
		 * what's next?
		 */
		ret = ceph_tcp_recvmsg(con->sock, &con->v1.in_tag, 1);
		अगर (ret <= 0)
			जाओ out;
		करोut("try_read got tag %d\n", con->v1.in_tag);
		चयन (con->v1.in_tag) अणु
		हाल CEPH_MSGR_TAG_MSG:
			prepare_पढ़ो_message(con);
			अवरोध;
		हाल CEPH_MSGR_TAG_ACK:
			prepare_पढ़ो_ack(con);
			अवरोध;
		हाल CEPH_MSGR_TAG_KEEPALIVE2_ACK:
			prepare_पढ़ो_keepalive_ack(con);
			अवरोध;
		हाल CEPH_MSGR_TAG_CLOSE:
			ceph_con_बंद_socket(con);
			con->state = CEPH_CON_S_CLOSED;
			जाओ out;
		शेष:
			जाओ bad_tag;
		पूर्ण
	पूर्ण
	अगर (con->v1.in_tag == CEPH_MSGR_TAG_MSG) अणु
		ret = पढ़ो_partial_message(con);
		अगर (ret <= 0) अणु
			चयन (ret) अणु
			हाल -EBADMSG:
				con->error_msg = "bad crc/signature";
				fallthrough;
			हाल -EBADE:
				ret = -EIO;
				अवरोध;
			हाल -EIO:
				con->error_msg = "io error";
				अवरोध;
			पूर्ण
			जाओ out;
		पूर्ण
		अगर (con->v1.in_tag == CEPH_MSGR_TAG_READY)
			जाओ more;
		ceph_con_process_message(con);
		अगर (con->state == CEPH_CON_S_OPEN)
			prepare_पढ़ो_tag(con);
		जाओ more;
	पूर्ण
	अगर (con->v1.in_tag == CEPH_MSGR_TAG_ACK ||
	    con->v1.in_tag == CEPH_MSGR_TAG_SEQ) अणु
		/*
		 * the final handshake seq exchange is semantically
		 * equivalent to an ACK
		 */
		ret = पढ़ो_partial_ack(con);
		अगर (ret <= 0)
			जाओ out;
		process_ack(con);
		जाओ more;
	पूर्ण
	अगर (con->v1.in_tag == CEPH_MSGR_TAG_KEEPALIVE2_ACK) अणु
		ret = पढ़ो_keepalive_ack(con);
		अगर (ret <= 0)
			जाओ out;
		जाओ more;
	पूर्ण

out:
	करोut("try_read done on %p ret %d\n", con, ret);
	वापस ret;

bad_tag:
	pr_err("try_read bad tag %d\n", con->v1.in_tag);
	con->error_msg = "protocol error, garbage tag";
	ret = -1;
	जाओ out;
पूर्ण

/*
 * Write something to the socket.  Called in a worker thपढ़ो when the
 * socket appears to be ग_लिखोable and we have something पढ़ोy to send.
 */
पूर्णांक ceph_con_v1_try_ग_लिखो(काष्ठा ceph_connection *con)
अणु
	पूर्णांक ret = 1;

	करोut("try_write start %p state %d\n", con, con->state);
	अगर (con->state != CEPH_CON_S_PREOPEN &&
	    con->state != CEPH_CON_S_V1_BANNER &&
	    con->state != CEPH_CON_S_V1_CONNECT_MSG &&
	    con->state != CEPH_CON_S_OPEN)
		वापस 0;

	/* खोलो the socket first? */
	अगर (con->state == CEPH_CON_S_PREOPEN) अणु
		BUG_ON(con->sock);
		con->state = CEPH_CON_S_V1_BANNER;

		con_out_kvec_reset(con);
		prepare_ग_लिखो_banner(con);
		prepare_पढ़ो_banner(con);

		BUG_ON(con->in_msg);
		con->v1.in_tag = CEPH_MSGR_TAG_READY;
		करोut("try_write initiating connect on %p new state %d\n",
		     con, con->state);
		ret = ceph_tcp_connect(con);
		अगर (ret < 0) अणु
			con->error_msg = "connect error";
			जाओ out;
		पूर्ण
	पूर्ण

more:
	करोut("try_write out_kvec_bytes %d\n", con->v1.out_kvec_bytes);
	BUG_ON(!con->sock);

	/* kvec data queued? */
	अगर (con->v1.out_kvec_left) अणु
		ret = ग_लिखो_partial_kvec(con);
		अगर (ret <= 0)
			जाओ out;
	पूर्ण
	अगर (con->v1.out_skip) अणु
		ret = ग_लिखो_partial_skip(con);
		अगर (ret <= 0)
			जाओ out;
	पूर्ण

	/* msg pages? */
	अगर (con->out_msg) अणु
		अगर (con->v1.out_msg_करोne) अणु
			ceph_msg_put(con->out_msg);
			con->out_msg = शून्य;   /* we're करोne with this one */
			जाओ करो_next;
		पूर्ण

		ret = ग_लिखो_partial_message_data(con);
		अगर (ret == 1)
			जाओ more;  /* we need to send the footer, too! */
		अगर (ret == 0)
			जाओ out;
		अगर (ret < 0) अणु
			करोut("try_write write_partial_message_data err %d\n",
			     ret);
			जाओ out;
		पूर्ण
	पूर्ण

करो_next:
	अगर (con->state == CEPH_CON_S_OPEN) अणु
		अगर (ceph_con_flag_test_and_clear(con,
				CEPH_CON_F_KEEPALIVE_PENDING)) अणु
			prepare_ग_लिखो_keepalive(con);
			जाओ more;
		पूर्ण
		/* is anything अन्यथा pending? */
		अगर (!list_empty(&con->out_queue)) अणु
			prepare_ग_लिखो_message(con);
			जाओ more;
		पूर्ण
		अगर (con->in_seq > con->in_seq_acked) अणु
			prepare_ग_लिखो_ack(con);
			जाओ more;
		पूर्ण
	पूर्ण

	/* Nothing to करो! */
	ceph_con_flag_clear(con, CEPH_CON_F_WRITE_PENDING);
	करोut("try_write nothing else to write.\n");
	ret = 0;
out:
	करोut("try_write done on %p ret %d\n", con, ret);
	वापस ret;
पूर्ण

व्योम ceph_con_v1_revoke(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_msg *msg = con->out_msg;

	WARN_ON(con->v1.out_skip);
	/* footer */
	अगर (con->v1.out_msg_करोne) अणु
		con->v1.out_skip += con_out_kvec_skip(con);
	पूर्ण अन्यथा अणु
		WARN_ON(!msg->data_length);
		con->v1.out_skip += माप_footer(con);
	पूर्ण
	/* data, middle, front */
	अगर (msg->data_length)
		con->v1.out_skip += msg->cursor.total_resid;
	अगर (msg->middle)
		con->v1.out_skip += con_out_kvec_skip(con);
	con->v1.out_skip += con_out_kvec_skip(con);

	करोut("%s con %p out_kvec_bytes %d out_skip %d\n", __func__, con,
	     con->v1.out_kvec_bytes, con->v1.out_skip);
पूर्ण

व्योम ceph_con_v1_revoke_incoming(काष्ठा ceph_connection *con)
अणु
	अचिन्हित पूर्णांक front_len = le32_to_cpu(con->v1.in_hdr.front_len);
	अचिन्हित पूर्णांक middle_len = le32_to_cpu(con->v1.in_hdr.middle_len);
	अचिन्हित पूर्णांक data_len = le32_to_cpu(con->v1.in_hdr.data_len);

	/* skip rest of message */
	con->v1.in_base_pos = con->v1.in_base_pos -
			माप(काष्ठा ceph_msg_header) -
			front_len -
			middle_len -
			data_len -
			माप(काष्ठा ceph_msg_footer);

	con->v1.in_tag = CEPH_MSGR_TAG_READY;
	con->in_seq++;

	करोut("%s con %p in_base_pos %d\n", __func__, con, con->v1.in_base_pos);
पूर्ण

bool ceph_con_v1_खोलोed(काष्ठा ceph_connection *con)
अणु
	वापस con->v1.connect_seq;
पूर्ण

व्योम ceph_con_v1_reset_session(काष्ठा ceph_connection *con)
अणु
	con->v1.connect_seq = 0;
	con->v1.peer_global_seq = 0;
पूर्ण

व्योम ceph_con_v1_reset_protocol(काष्ठा ceph_connection *con)
अणु
	con->v1.out_skip = 0;
पूर्ण
