<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * iSCSI over TCP/IP Data-Path lib
 *
 * Copyright (C) 2008 Mike Christie
 * Copyright (C) 2008 Red Hat, Inc.  All rights reserved.
 * मुख्यtained by खोलो-iscsi@googlegroups.com
 */

#अगर_अघोषित LIBISCSI_TCP_H
#घोषणा LIBISCSI_TCP_H

#समावेश <scsi/libiscsi.h>

काष्ठा iscsi_tcp_conn;
काष्ठा iscsi_segment;
काष्ठा sk_buff;
काष्ठा ahash_request;

प्रकार पूर्णांक iscsi_segment_करोne_fn_t(काष्ठा iscsi_tcp_conn *,
				    काष्ठा iscsi_segment *);

काष्ठा iscsi_segment अणु
	अचिन्हित अक्षर		*data;
	अचिन्हित पूर्णांक		size;
	अचिन्हित पूर्णांक		copied;
	अचिन्हित पूर्णांक		total_size;
	अचिन्हित पूर्णांक		total_copied;

	काष्ठा ahash_request	*hash;
	अचिन्हित अक्षर		padbuf[ISCSI_PAD_LEN];
	अचिन्हित अक्षर		recv_digest[ISCSI_DIGEST_SIZE];
	अचिन्हित अक्षर		digest[ISCSI_DIGEST_SIZE];
	अचिन्हित पूर्णांक		digest_len;

	काष्ठा scatterlist	*sg;
	व्योम			*sg_mapped;
	अचिन्हित पूर्णांक		sg_offset;
	bool			atomic_mapped;

	iscsi_segment_करोne_fn_t	*करोne;
पूर्ण;

/* Socket connection receive helper */
काष्ठा iscsi_tcp_recv अणु
	काष्ठा iscsi_hdr	*hdr;
	काष्ठा iscsi_segment	segment;

	/* Allocate buffer क्रम BHS + AHS */
	uपूर्णांक32_t		hdr_buf[64];

	/* copied and flipped values */
	पूर्णांक			datalen;
पूर्ण;

काष्ठा iscsi_tcp_conn अणु
	काष्ठा iscsi_conn	*iscsi_conn;
	व्योम			*dd_data;
	पूर्णांक			stop_stage;	/* conn_stop() flag: *
						 * stop to recover,  *
						 * stop to terminate */
	/* control data */
	काष्ठा iscsi_tcp_recv	in;		/* TCP receive context */
	/* CRC32C (Rx) LLD should set this is they करो not offload */
	काष्ठा ahash_request	*rx_hash;
पूर्ण;

काष्ठा iscsi_tcp_task अणु
	uपूर्णांक32_t		exp_datasn;	/* expected target's R2TSN/DataSN */
	पूर्णांक			data_offset;
	काष्ठा iscsi_r2t_info	*r2t;		/* in progress solict R2T */
	काष्ठा iscsi_pool	r2tpool;
	काष्ठा kfअगरo		r2tqueue;
	व्योम			*dd_data;
	spinlock_t		pool2queue;
	spinlock_t		queue2pool;
पूर्ण;

क्रमागत अणु
	ISCSI_TCP_SEGMENT_DONE,		/* curr seg has been processed */
	ISCSI_TCP_SKB_DONE,		/* skb is out of data */
	ISCSI_TCP_CONN_ERR,		/* iscsi layer has fired a conn err */
	ISCSI_TCP_SUSPENDED,		/* conn is suspended */
पूर्ण;

बाह्य व्योम iscsi_tcp_hdr_recv_prep(काष्ठा iscsi_tcp_conn *tcp_conn);
बाह्य पूर्णांक iscsi_tcp_recv_skb(काष्ठा iscsi_conn *conn, काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक offset, bool offloaded, पूर्णांक *status);
बाह्य व्योम iscsi_tcp_cleanup_task(काष्ठा iscsi_task *task);
बाह्य पूर्णांक iscsi_tcp_task_init(काष्ठा iscsi_task *task);
बाह्य पूर्णांक iscsi_tcp_task_xmit(काष्ठा iscsi_task *task);

/* segment helpers */
बाह्य पूर्णांक iscsi_tcp_recv_segment_is_hdr(काष्ठा iscsi_tcp_conn *tcp_conn);
बाह्य पूर्णांक iscsi_tcp_segment_करोne(काष्ठा iscsi_tcp_conn *tcp_conn,
				  काष्ठा iscsi_segment *segment, पूर्णांक recv,
				  अचिन्हित copied);
बाह्य व्योम iscsi_tcp_segment_unmap(काष्ठा iscsi_segment *segment);

बाह्य व्योम iscsi_segment_init_linear(काष्ठा iscsi_segment *segment,
				      व्योम *data, माप_प्रकार size,
				      iscsi_segment_करोne_fn_t *करोne,
				      काष्ठा ahash_request *hash);
बाह्य पूर्णांक
iscsi_segment_seek_sg(काष्ठा iscsi_segment *segment,
		      काष्ठा scatterlist *sg_list, अचिन्हित पूर्णांक sg_count,
		      अचिन्हित पूर्णांक offset, माप_प्रकार size,
		      iscsi_segment_करोne_fn_t *करोne,
		      काष्ठा ahash_request *hash);

/* digest helpers */
बाह्य व्योम iscsi_tcp_dgst_header(काष्ठा ahash_request *hash, स्थिर व्योम *hdr,
				  माप_प्रकार hdrlen,
				  अचिन्हित अक्षर digest[ISCSI_DIGEST_SIZE]);
बाह्य काष्ठा iscsi_cls_conn *
iscsi_tcp_conn_setup(काष्ठा iscsi_cls_session *cls_session, पूर्णांक dd_data_size,
		     uपूर्णांक32_t conn_idx);
बाह्य व्योम iscsi_tcp_conn_tearकरोwn(काष्ठा iscsi_cls_conn *cls_conn);

/* misc helpers */
बाह्य पूर्णांक iscsi_tcp_r2tpool_alloc(काष्ठा iscsi_session *session);
बाह्य व्योम iscsi_tcp_r2tpool_मुक्त(काष्ठा iscsi_session *session);
बाह्य पूर्णांक iscsi_tcp_set_max_r2t(काष्ठा iscsi_conn *conn, अक्षर *buf);
बाह्य व्योम iscsi_tcp_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn,
				     काष्ठा iscsi_stats *stats);
#पूर्ण_अगर /* LIBISCSI_TCP_H */
