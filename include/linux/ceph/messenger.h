<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __FS_CEPH_MESSENGER_H
#घोषणा __FS_CEPH_MESSENGER_H

#समावेश <linux/bvec.h>
#समावेश <linux/crypto.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/net.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/uपन.स>
#समावेश <linux/workqueue.h>
#समावेश <net/net_namespace.h>

#समावेश <linux/ceph/types.h>
#समावेश <linux/ceph/buffer.h>

काष्ठा ceph_msg;
काष्ठा ceph_connection;

/*
 * Ceph defines these callbacks क्रम handling connection events.
 */
काष्ठा ceph_connection_operations अणु
	काष्ठा ceph_connection *(*get)(काष्ठा ceph_connection *);
	व्योम (*put)(काष्ठा ceph_connection *);

	/* handle an incoming message. */
	व्योम (*dispatch) (काष्ठा ceph_connection *con, काष्ठा ceph_msg *m);

	/* authorize an outgoing connection */
	काष्ठा ceph_auth_handshake *(*get_authorizer) (
				काष्ठा ceph_connection *con,
			       पूर्णांक *proto, पूर्णांक क्रमce_new);
	पूर्णांक (*add_authorizer_challenge)(काष्ठा ceph_connection *con,
					व्योम *challenge_buf,
					पूर्णांक challenge_buf_len);
	पूर्णांक (*verअगरy_authorizer_reply) (काष्ठा ceph_connection *con);
	पूर्णांक (*invalidate_authorizer)(काष्ठा ceph_connection *con);

	/* there was some error on the socket (disconnect, whatever) */
	व्योम (*fault) (काष्ठा ceph_connection *con);

	/* a remote host as terminated a message exchange session, and messages
	 * we sent (or they tried to send us) may be lost. */
	व्योम (*peer_reset) (काष्ठा ceph_connection *con);

	काष्ठा ceph_msg * (*alloc_msg) (काष्ठा ceph_connection *con,
					काष्ठा ceph_msg_header *hdr,
					पूर्णांक *skip);

	व्योम (*reencode_message) (काष्ठा ceph_msg *msg);

	पूर्णांक (*sign_message) (काष्ठा ceph_msg *msg);
	पूर्णांक (*check_message_signature) (काष्ठा ceph_msg *msg);

	/* msgr2 authentication exchange */
	पूर्णांक (*get_auth_request)(काष्ठा ceph_connection *con,
				व्योम *buf, पूर्णांक *buf_len,
				व्योम **authorizer, पूर्णांक *authorizer_len);
	पूर्णांक (*handle_auth_reply_more)(काष्ठा ceph_connection *con,
				      व्योम *reply, पूर्णांक reply_len,
				      व्योम *buf, पूर्णांक *buf_len,
				      व्योम **authorizer, पूर्णांक *authorizer_len);
	पूर्णांक (*handle_auth_करोne)(काष्ठा ceph_connection *con,
				u64 global_id, व्योम *reply, पूर्णांक reply_len,
				u8 *session_key, पूर्णांक *session_key_len,
				u8 *con_secret, पूर्णांक *con_secret_len);
	पूर्णांक (*handle_auth_bad_method)(काष्ठा ceph_connection *con,
				      पूर्णांक used_proto, पूर्णांक result,
				      स्थिर पूर्णांक *allowed_protos, पूर्णांक proto_cnt,
				      स्थिर पूर्णांक *allowed_modes, पूर्णांक mode_cnt);
पूर्ण;

/* use क्रमmat string %s%lld */
#घोषणा ENTITY_NAME(n) ceph_entity_type_name((n).type), le64_to_cpu((n).num)

काष्ठा ceph_messenger अणु
	काष्ठा ceph_entity_inst inst;    /* my name+address */
	काष्ठा ceph_entity_addr my_enc_addr;

	atomic_t stopping;
	possible_net_t net;

	/*
	 * the global_seq counts connections i (attempt to) initiate
	 * in order to disambiguate certain connect race conditions.
	 */
	u32 global_seq;
	spinlock_t global_seq_lock;
पूर्ण;

क्रमागत ceph_msg_data_type अणु
	CEPH_MSG_DATA_NONE,	/* message contains no data payload */
	CEPH_MSG_DATA_PAGES,	/* data source/destination is a page array */
	CEPH_MSG_DATA_PAGELIST,	/* data source/destination is a pagelist */
#अगर_घोषित CONFIG_BLOCK
	CEPH_MSG_DATA_BIO,	/* data source/destination is a bio list */
#पूर्ण_अगर /* CONFIG_BLOCK */
	CEPH_MSG_DATA_BVECS,	/* data source/destination is a bio_vec array */
पूर्ण;

#अगर_घोषित CONFIG_BLOCK

काष्ठा ceph_bio_iter अणु
	काष्ठा bio *bio;
	काष्ठा bvec_iter iter;
पूर्ण;

#घोषणा __ceph_bio_iter_advance_step(it, n, STEP) करो अणु			      \
	अचिन्हित पूर्णांक __n = (n), __cur_n;				      \
									      \
	जबतक (__n) अणु							      \
		BUG_ON(!(it)->iter.bi_size);				      \
		__cur_n = min((it)->iter.bi_size, __n);			      \
		(व्योम)(STEP);						      \
		bio_advance_iter((it)->bio, &(it)->iter, __cur_n);	      \
		अगर (!(it)->iter.bi_size && (it)->bio->bi_next) अणु	      \
			करोut("__ceph_bio_iter_advance_step next bio\n");      \
			(it)->bio = (it)->bio->bi_next;			      \
			(it)->iter = (it)->bio->bi_iter;		      \
		पूर्ण							      \
		__n -= __cur_n;						      \
	पूर्ण								      \
पूर्ण जबतक (0)

/*
 * Advance @it by @n bytes.
 */
#घोषणा ceph_bio_iter_advance(it, n)					      \
	__ceph_bio_iter_advance_step(it, n, 0)

/*
 * Advance @it by @n bytes, executing BVEC_STEP क्रम each bio_vec.
 */
#घोषणा ceph_bio_iter_advance_step(it, n, BVEC_STEP)			      \
	__ceph_bio_iter_advance_step(it, n, (अणु				      \
		काष्ठा bio_vec bv;					      \
		काष्ठा bvec_iter __cur_iter;				      \
									      \
		__cur_iter = (it)->iter;				      \
		__cur_iter.bi_size = __cur_n;				      \
		__bio_क्रम_each_segment(bv, (it)->bio, __cur_iter, __cur_iter) \
			(व्योम)(BVEC_STEP);				      \
	पूर्ण))

#पूर्ण_अगर /* CONFIG_BLOCK */

काष्ठा ceph_bvec_iter अणु
	काष्ठा bio_vec *bvecs;
	काष्ठा bvec_iter iter;
पूर्ण;

#घोषणा __ceph_bvec_iter_advance_step(it, n, STEP) करो अणु			      \
	BUG_ON((n) > (it)->iter.bi_size);				      \
	(व्योम)(STEP);							      \
	bvec_iter_advance((it)->bvecs, &(it)->iter, (n));		      \
पूर्ण जबतक (0)

/*
 * Advance @it by @n bytes.
 */
#घोषणा ceph_bvec_iter_advance(it, n)					      \
	__ceph_bvec_iter_advance_step(it, n, 0)

/*
 * Advance @it by @n bytes, executing BVEC_STEP क्रम each bio_vec.
 */
#घोषणा ceph_bvec_iter_advance_step(it, n, BVEC_STEP)			      \
	__ceph_bvec_iter_advance_step(it, n, (अणु				      \
		काष्ठा bio_vec bv;					      \
		काष्ठा bvec_iter __cur_iter;				      \
									      \
		__cur_iter = (it)->iter;				      \
		__cur_iter.bi_size = (n);				      \
		क्रम_each_bvec(bv, (it)->bvecs, __cur_iter, __cur_iter)	      \
			(व्योम)(BVEC_STEP);				      \
	पूर्ण))

#घोषणा ceph_bvec_iter_लघुen(it, n) करो अणु				      \
	BUG_ON((n) > (it)->iter.bi_size);				      \
	(it)->iter.bi_size = (n);					      \
पूर्ण जबतक (0)

काष्ठा ceph_msg_data अणु
	क्रमागत ceph_msg_data_type		type;
	जोड़ अणु
#अगर_घोषित CONFIG_BLOCK
		काष्ठा अणु
			काष्ठा ceph_bio_iter	bio_pos;
			u32			bio_length;
		पूर्ण;
#पूर्ण_अगर /* CONFIG_BLOCK */
		काष्ठा ceph_bvec_iter	bvec_pos;
		काष्ठा अणु
			काष्ठा page	**pages;
			माप_प्रकार		length;		/* total # bytes */
			अचिन्हित पूर्णांक	alignment;	/* first page */
			bool		own_pages;
		पूर्ण;
		काष्ठा ceph_pagelist	*pagelist;
	पूर्ण;
पूर्ण;

काष्ठा ceph_msg_data_cursor अणु
	माप_प्रकार			total_resid;	/* across all data items */

	काष्ठा ceph_msg_data	*data;		/* current data item */
	माप_प्रकार			resid;		/* bytes not yet consumed */
	bool			last_piece;	/* current is last piece */
	bool			need_crc;	/* crc update needed */
	जोड़ अणु
#अगर_घोषित CONFIG_BLOCK
		काष्ठा ceph_bio_iter	bio_iter;
#पूर्ण_अगर /* CONFIG_BLOCK */
		काष्ठा bvec_iter	bvec_iter;
		काष्ठा अणु				/* pages */
			अचिन्हित पूर्णांक	page_offset;	/* offset in page */
			अचिन्हित लघु	page_index;	/* index in array */
			अचिन्हित लघु	page_count;	/* pages in array */
		पूर्ण;
		काष्ठा अणु				/* pagelist */
			काष्ठा page	*page;		/* page from list */
			माप_प्रकार		offset;		/* bytes from list */
		पूर्ण;
	पूर्ण;
पूर्ण;

/*
 * a single message.  it contains a header (src, dest, message type, etc.),
 * footer (crc values, मुख्यly), a "front" message body, and possibly a
 * data payload (stored in some number of pages).
 */
काष्ठा ceph_msg अणु
	काष्ठा ceph_msg_header hdr;	/* header */
	जोड़ अणु
		काष्ठा ceph_msg_footer footer;		/* footer */
		काष्ठा ceph_msg_footer_old old_footer;	/* old क्रमmat footer */
	पूर्ण;
	काष्ठा kvec front;              /* unaligned blobs of message */
	काष्ठा ceph_buffer *middle;

	माप_प्रकार				data_length;
	काष्ठा ceph_msg_data		*data;
	पूर्णांक				num_data_items;
	पूर्णांक				max_data_items;
	काष्ठा ceph_msg_data_cursor	cursor;

	काष्ठा ceph_connection *con;
	काष्ठा list_head list_head;	/* links क्रम connection lists */

	काष्ठा kref kref;
	bool more_to_follow;
	bool needs_out_seq;
	पूर्णांक front_alloc_len;

	काष्ठा ceph_msgpool *pool;
पूर्ण;

/*
 * connection states
 */
#घोषणा CEPH_CON_S_CLOSED		1
#घोषणा CEPH_CON_S_PREOPEN		2
#घोषणा CEPH_CON_S_V1_BANNER		3
#घोषणा CEPH_CON_S_V1_CONNECT_MSG	4
#घोषणा CEPH_CON_S_V2_BANNER_PREFIX	5
#घोषणा CEPH_CON_S_V2_BANNER_PAYLOAD	6
#घोषणा CEPH_CON_S_V2_HELLO		7
#घोषणा CEPH_CON_S_V2_AUTH		8
#घोषणा CEPH_CON_S_V2_AUTH_SIGNATURE	9
#घोषणा CEPH_CON_S_V2_SESSION_CONNECT	10
#घोषणा CEPH_CON_S_V2_SESSION_RECONNECT	11
#घोषणा CEPH_CON_S_OPEN			12
#घोषणा CEPH_CON_S_STANDBY		13

/*
 * ceph_connection flag bits
 */
#घोषणा CEPH_CON_F_LOSSYTX		0  /* we can बंद channel or drop
					      messages on errors */
#घोषणा CEPH_CON_F_KEEPALIVE_PENDING	1  /* we need to send a keepalive */
#घोषणा CEPH_CON_F_WRITE_PENDING	2  /* we have data पढ़ोy to send */
#घोषणा CEPH_CON_F_SOCK_CLOSED		3  /* socket state changed to बंदd */
#घोषणा CEPH_CON_F_BACKOFF		4  /* need to retry queuing delayed
					      work */

/* ceph connection fault delay शेषs, क्रम exponential backoff */
#घोषणा BASE_DELAY_INTERVAL	(HZ / 4)
#घोषणा MAX_DELAY_INTERVAL	(15 * HZ)

काष्ठा ceph_connection_v1_info अणु
	काष्ठा kvec out_kvec[8],         /* sending header/footer data */
		*out_kvec_cur;
	पूर्णांक out_kvec_left;   /* kvec's left in out_kvec */
	पूर्णांक out_skip;        /* skip this many bytes */
	पूर्णांक out_kvec_bytes;  /* total bytes left */
	bool out_more;       /* there is more data after the kvecs */
	bool out_msg_करोne;

	काष्ठा ceph_auth_handshake *auth;
	पूर्णांक auth_retry;       /* true अगर we need a newer authorizer */

	/* connection negotiation temps */
	u8 in_banner[CEPH_BANNER_MAX_LEN];
	काष्ठा ceph_entity_addr actual_peer_addr;
	काष्ठा ceph_entity_addr peer_addr_क्रम_me;
	काष्ठा ceph_msg_connect out_connect;
	काष्ठा ceph_msg_connect_reply in_reply;

	पूर्णांक in_base_pos;     /* bytes पढ़ो */

	/* message in temps */
	u8 in_tag;           /* protocol control byte */
	काष्ठा ceph_msg_header in_hdr;
	__le64 in_temp_ack;  /* क्रम पढ़ोing an ack */

	/* message out temps */
	काष्ठा ceph_msg_header out_hdr;
	__le64 out_temp_ack;  /* क्रम writing an ack */
	काष्ठा ceph_बारpec out_temp_keepalive2;  /* क्रम writing keepalive2
						      stamp */

	u32 connect_seq;      /* identअगरy the most recent connection
				 attempt क्रम this session */
	u32 peer_global_seq;  /* peer's global seq क्रम this connection */
पूर्ण;

#घोषणा CEPH_CRC_LEN			4
#घोषणा CEPH_GCM_KEY_LEN		16
#घोषणा CEPH_GCM_IV_LEN			माप(काष्ठा ceph_gcm_nonce)
#घोषणा CEPH_GCM_BLOCK_LEN		16
#घोषणा CEPH_GCM_TAG_LEN		16

#घोषणा CEPH_PREAMBLE_LEN		32
#घोषणा CEPH_PREAMBLE_INLINE_LEN	48
#घोषणा CEPH_PREAMBLE_PLAIN_LEN		CEPH_PREAMBLE_LEN
#घोषणा CEPH_PREAMBLE_SECURE_LEN	(CEPH_PREAMBLE_LEN +		\
					 CEPH_PREAMBLE_INLINE_LEN +	\
					 CEPH_GCM_TAG_LEN)
#घोषणा CEPH_EPILOGUE_PLAIN_LEN		(1 + 3 * CEPH_CRC_LEN)
#घोषणा CEPH_EPILOGUE_SECURE_LEN	(CEPH_GCM_BLOCK_LEN + CEPH_GCM_TAG_LEN)

#घोषणा CEPH_FRAME_MAX_SEGMENT_COUNT	4

काष्ठा ceph_frame_desc अणु
	पूर्णांक fd_tag;  /* FRAME_TAG_* */
	पूर्णांक fd_seg_cnt;
	पूर्णांक fd_lens[CEPH_FRAME_MAX_SEGMENT_COUNT];  /* logical */
	पूर्णांक fd_aligns[CEPH_FRAME_MAX_SEGMENT_COUNT];
पूर्ण;

काष्ठा ceph_gcm_nonce अणु
	__le32 fixed;
	__le64 counter __packed;
पूर्ण;

काष्ठा ceph_connection_v2_info अणु
	काष्ठा iov_iter in_iter;
	काष्ठा kvec in_kvecs[5];  /* recvmsg */
	काष्ठा bio_vec in_bvec;  /* recvmsg (in_cursor) */
	पूर्णांक in_kvec_cnt;
	पूर्णांक in_state;  /* IN_S_* */

	काष्ठा iov_iter out_iter;
	काष्ठा kvec out_kvecs[8];  /* sendmsg */
	काष्ठा bio_vec out_bvec;  /* sendpage (out_cursor, out_zero),
				     sendmsg (out_enc_pages) */
	पूर्णांक out_kvec_cnt;
	पूर्णांक out_state;  /* OUT_S_* */

	पूर्णांक out_zero;  /* # of zero bytes to send */
	bool out_iter_sendpage;  /* use sendpage अगर possible */

	काष्ठा ceph_frame_desc in_desc;
	काष्ठा ceph_msg_data_cursor in_cursor;
	काष्ठा ceph_msg_data_cursor out_cursor;

	काष्ठा crypto_shash *hmac_tfm;  /* post-auth signature */
	काष्ठा crypto_aead *gcm_tfm;  /* on-wire encryption */
	काष्ठा aead_request *gcm_req;
	काष्ठा crypto_रुको gcm_रुको;
	काष्ठा ceph_gcm_nonce in_gcm_nonce;
	काष्ठा ceph_gcm_nonce out_gcm_nonce;

	काष्ठा page **out_enc_pages;
	पूर्णांक out_enc_page_cnt;
	पूर्णांक out_enc_resid;
	पूर्णांक out_enc_i;

	पूर्णांक con_mode;  /* CEPH_CON_MODE_* */

	व्योम *conn_bufs[16];
	पूर्णांक conn_buf_cnt;

	काष्ठा kvec in_sign_kvecs[8];
	काष्ठा kvec out_sign_kvecs[8];
	पूर्णांक in_sign_kvec_cnt;
	पूर्णांक out_sign_kvec_cnt;

	u64 client_cookie;
	u64 server_cookie;
	u64 global_seq;
	u64 connect_seq;
	u64 peer_global_seq;

	u8 in_buf[CEPH_PREAMBLE_SECURE_LEN];
	u8 out_buf[CEPH_PREAMBLE_SECURE_LEN];
	काष्ठा अणु
		u8 late_status;  /* FRAME_LATE_STATUS_* */
		जोड़ अणु
			काष्ठा अणु
				u32 front_crc;
				u32 middle_crc;
				u32 data_crc;
			पूर्ण __packed;
			u8 pad[CEPH_GCM_BLOCK_LEN - 1];
		पूर्ण;
	पूर्ण out_epil;
पूर्ण;

/*
 * A single connection with another host.
 *
 * We मुख्यtain a queue of outgoing messages, and some session state to
 * ensure that we can preserve the lossless, ordered delivery of
 * messages in the हाल of a TCP disconnect.
 */
काष्ठा ceph_connection अणु
	व्योम *निजी;

	स्थिर काष्ठा ceph_connection_operations *ops;

	काष्ठा ceph_messenger *msgr;

	पूर्णांक state;  /* CEPH_CON_S_* */
	atomic_t sock_state;
	काष्ठा socket *sock;

	अचिन्हित दीर्घ flags;  /* CEPH_CON_F_* */
	स्थिर अक्षर *error_msg;  /* error message, अगर any */

	काष्ठा ceph_entity_name peer_name; /* peer name */
	काष्ठा ceph_entity_addr peer_addr; /* peer address */
	u64 peer_features;

	काष्ठा mutex mutex;

	/* out queue */
	काष्ठा list_head out_queue;
	काष्ठा list_head out_sent;   /* sending or sent but unacked */
	u64 out_seq;		     /* last message queued क्रम send */

	u64 in_seq, in_seq_acked;  /* last message received, acked */

	काष्ठा ceph_msg *in_msg;
	काष्ठा ceph_msg *out_msg;        /* sending message (== tail of
					    out_sent) */

	u32 in_front_crc, in_middle_crc, in_data_crc;  /* calculated crc */

	काष्ठा बारpec64 last_keepalive_ack; /* keepalive2 ack stamp */

	काष्ठा delayed_work work;	    /* send|recv work */
	अचिन्हित दीर्घ       delay;          /* current delay पूर्णांकerval */

	जोड़ अणु
		काष्ठा ceph_connection_v1_info v1;
		काष्ठा ceph_connection_v2_info v2;
	पूर्ण;
पूर्ण;

बाह्य काष्ठा page *ceph_zero_page;

व्योम ceph_con_flag_clear(काष्ठा ceph_connection *con, अचिन्हित दीर्घ con_flag);
व्योम ceph_con_flag_set(काष्ठा ceph_connection *con, अचिन्हित दीर्घ con_flag);
bool ceph_con_flag_test(काष्ठा ceph_connection *con, अचिन्हित दीर्घ con_flag);
bool ceph_con_flag_test_and_clear(काष्ठा ceph_connection *con,
				  अचिन्हित दीर्घ con_flag);
bool ceph_con_flag_test_and_set(काष्ठा ceph_connection *con,
				अचिन्हित दीर्घ con_flag);

व्योम ceph_encode_my_addr(काष्ठा ceph_messenger *msgr);

पूर्णांक ceph_tcp_connect(काष्ठा ceph_connection *con);
पूर्णांक ceph_con_बंद_socket(काष्ठा ceph_connection *con);
व्योम ceph_con_reset_session(काष्ठा ceph_connection *con);

u32 ceph_get_global_seq(काष्ठा ceph_messenger *msgr, u32 gt);
व्योम ceph_con_discard_sent(काष्ठा ceph_connection *con, u64 ack_seq);
व्योम ceph_con_discard_requeued(काष्ठा ceph_connection *con, u64 reconnect_seq);

व्योम ceph_msg_data_cursor_init(काष्ठा ceph_msg_data_cursor *cursor,
			       काष्ठा ceph_msg *msg, माप_प्रकार length);
काष्ठा page *ceph_msg_data_next(काष्ठा ceph_msg_data_cursor *cursor,
				माप_प्रकार *page_offset, माप_प्रकार *length,
				bool *last_piece);
व्योम ceph_msg_data_advance(काष्ठा ceph_msg_data_cursor *cursor, माप_प्रकार bytes);

u32 ceph_crc32c_page(u32 crc, काष्ठा page *page, अचिन्हित पूर्णांक page_offset,
		     अचिन्हित पूर्णांक length);

bool ceph_addr_is_blank(स्थिर काष्ठा ceph_entity_addr *addr);
पूर्णांक ceph_addr_port(स्थिर काष्ठा ceph_entity_addr *addr);
व्योम ceph_addr_set_port(काष्ठा ceph_entity_addr *addr, पूर्णांक p);

व्योम ceph_con_process_message(काष्ठा ceph_connection *con);
पूर्णांक ceph_con_in_msg_alloc(काष्ठा ceph_connection *con,
			  काष्ठा ceph_msg_header *hdr, पूर्णांक *skip);
व्योम ceph_con_get_out_msg(काष्ठा ceph_connection *con);

/* messenger_v1.c */
पूर्णांक ceph_con_v1_try_पढ़ो(काष्ठा ceph_connection *con);
पूर्णांक ceph_con_v1_try_ग_लिखो(काष्ठा ceph_connection *con);
व्योम ceph_con_v1_revoke(काष्ठा ceph_connection *con);
व्योम ceph_con_v1_revoke_incoming(काष्ठा ceph_connection *con);
bool ceph_con_v1_खोलोed(काष्ठा ceph_connection *con);
व्योम ceph_con_v1_reset_session(काष्ठा ceph_connection *con);
व्योम ceph_con_v1_reset_protocol(काष्ठा ceph_connection *con);

/* messenger_v2.c */
पूर्णांक ceph_con_v2_try_पढ़ो(काष्ठा ceph_connection *con);
पूर्णांक ceph_con_v2_try_ग_लिखो(काष्ठा ceph_connection *con);
व्योम ceph_con_v2_revoke(काष्ठा ceph_connection *con);
व्योम ceph_con_v2_revoke_incoming(काष्ठा ceph_connection *con);
bool ceph_con_v2_खोलोed(काष्ठा ceph_connection *con);
व्योम ceph_con_v2_reset_session(काष्ठा ceph_connection *con);
व्योम ceph_con_v2_reset_protocol(काष्ठा ceph_connection *con);


बाह्य स्थिर अक्षर *ceph_pr_addr(स्थिर काष्ठा ceph_entity_addr *addr);

बाह्य पूर्णांक ceph_parse_ips(स्थिर अक्षर *c, स्थिर अक्षर *end,
			  काष्ठा ceph_entity_addr *addr,
			  पूर्णांक max_count, पूर्णांक *count);

बाह्य पूर्णांक ceph_msgr_init(व्योम);
बाह्य व्योम ceph_msgr_निकास(व्योम);
बाह्य व्योम ceph_msgr_flush(व्योम);

बाह्य व्योम ceph_messenger_init(काष्ठा ceph_messenger *msgr,
				काष्ठा ceph_entity_addr *myaddr);
बाह्य व्योम ceph_messenger_fini(काष्ठा ceph_messenger *msgr);
बाह्य व्योम ceph_messenger_reset_nonce(काष्ठा ceph_messenger *msgr);

बाह्य व्योम ceph_con_init(काष्ठा ceph_connection *con, व्योम *निजी,
			स्थिर काष्ठा ceph_connection_operations *ops,
			काष्ठा ceph_messenger *msgr);
बाह्य व्योम ceph_con_खोलो(काष्ठा ceph_connection *con,
			  __u8 entity_type, __u64 entity_num,
			  काष्ठा ceph_entity_addr *addr);
बाह्य bool ceph_con_खोलोed(काष्ठा ceph_connection *con);
बाह्य व्योम ceph_con_बंद(काष्ठा ceph_connection *con);
बाह्य व्योम ceph_con_send(काष्ठा ceph_connection *con, काष्ठा ceph_msg *msg);

बाह्य व्योम ceph_msg_revoke(काष्ठा ceph_msg *msg);
बाह्य व्योम ceph_msg_revoke_incoming(काष्ठा ceph_msg *msg);

बाह्य व्योम ceph_con_keepalive(काष्ठा ceph_connection *con);
बाह्य bool ceph_con_keepalive_expired(काष्ठा ceph_connection *con,
				       अचिन्हित दीर्घ पूर्णांकerval);

व्योम ceph_msg_data_add_pages(काष्ठा ceph_msg *msg, काष्ठा page **pages,
			     माप_प्रकार length, माप_प्रकार alignment, bool own_pages);
बाह्य व्योम ceph_msg_data_add_pagelist(काष्ठा ceph_msg *msg,
				काष्ठा ceph_pagelist *pagelist);
#अगर_घोषित CONFIG_BLOCK
व्योम ceph_msg_data_add_bio(काष्ठा ceph_msg *msg, काष्ठा ceph_bio_iter *bio_pos,
			   u32 length);
#पूर्ण_अगर /* CONFIG_BLOCK */
व्योम ceph_msg_data_add_bvecs(काष्ठा ceph_msg *msg,
			     काष्ठा ceph_bvec_iter *bvec_pos);

काष्ठा ceph_msg *ceph_msg_new2(पूर्णांक type, पूर्णांक front_len, पूर्णांक max_data_items,
			       gfp_t flags, bool can_fail);
बाह्य काष्ठा ceph_msg *ceph_msg_new(पूर्णांक type, पूर्णांक front_len, gfp_t flags,
				     bool can_fail);

बाह्य काष्ठा ceph_msg *ceph_msg_get(काष्ठा ceph_msg *msg);
बाह्य व्योम ceph_msg_put(काष्ठा ceph_msg *msg);

बाह्य व्योम ceph_msg_dump(काष्ठा ceph_msg *msg);

#पूर्ण_अगर
