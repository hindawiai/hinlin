<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause */

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/*          Greg Joyce <greg@खोलोgridcomputing.com> */
/* Copyright (c) 2008-2019, IBM Corporation */
/* Copyright (c) 2017, Open Grid Computing, Inc. */

#अगर_अघोषित _SIW_CM_H
#घोषणा _SIW_CM_H

#समावेश <net/sock.h>
#समावेश <linux/tcp.h>

#समावेश <rdma/iw_cm.h>

क्रमागत siw_cep_state अणु
	SIW_EPSTATE_IDLE = 1,
	SIW_EPSTATE_LISTENING,
	SIW_EPSTATE_CONNECTING,
	SIW_EPSTATE_AWAIT_MPAREQ,
	SIW_EPSTATE_RECVD_MPAREQ,
	SIW_EPSTATE_AWAIT_MPAREP,
	SIW_EPSTATE_RDMA_MODE,
	SIW_EPSTATE_CLOSED
पूर्ण;

काष्ठा siw_mpa_info अणु
	काष्ठा mpa_rr hdr; /* peer mpa hdr in host byte order */
	काष्ठा mpa_v2_data v2_ctrl;
	काष्ठा mpa_v2_data v2_ctrl_req;
	अक्षर *pdata;
	पूर्णांक bytes_rcvd;
पूर्ण;

काष्ठा siw_device;

काष्ठा siw_cep अणु
	काष्ठा iw_cm_id *cm_id;
	काष्ठा siw_device *sdev;
	काष्ठा list_head devq;
	spinlock_t lock;
	काष्ठा kref ref;
	पूर्णांक in_use;
	रुको_queue_head_t रुकोq;
	क्रमागत siw_cep_state state;

	काष्ठा list_head listenq;
	काष्ठा siw_cep *listen_cep;

	काष्ठा siw_qp *qp;
	काष्ठा socket *sock;

	काष्ठा siw_cm_work *mpa_समयr;
	काष्ठा list_head work_मुक्तlist;

	काष्ठा siw_mpa_info mpa;
	पूर्णांक ord;
	पूर्णांक ird;
	bool enhanced_rdma_conn_est;

	/* Saved upcalls of socket */
	व्योम (*sk_state_change)(काष्ठा sock *sk);
	व्योम (*sk_data_पढ़ोy)(काष्ठा sock *sk);
	व्योम (*sk_ग_लिखो_space)(काष्ठा sock *sk);
	व्योम (*sk_error_report)(काष्ठा sock *sk);
पूर्ण;

/*
 * Connection initiator रुकोs 10 seconds to receive an
 * MPA reply after sending out MPA request. Reponder रुकोs क्रम
 * 5 seconds क्रम MPA request to arrive अगर new TCP connection
 * was set up.
 */
#घोषणा MPAREQ_TIMEOUT (HZ * 10)
#घोषणा MPAREP_TIMEOUT (HZ * 5)

क्रमागत siw_work_type अणु
	SIW_CM_WORK_ACCEPT = 1,
	SIW_CM_WORK_READ_MPAHDR,
	SIW_CM_WORK_CLOSE_LLP, /* बंद socket */
	SIW_CM_WORK_PEER_CLOSE, /* socket indicated peer बंद */
	SIW_CM_WORK_MPATIMEOUT
पूर्ण;

काष्ठा siw_cm_work अणु
	काष्ठा delayed_work work;
	काष्ठा list_head list;
	क्रमागत siw_work_type type;
	काष्ठा siw_cep *cep;
पूर्ण;

#घोषणा to_sockaddr_in(a) (*(काष्ठा sockaddr_in *)(&(a)))
#घोषणा to_sockaddr_in6(a) (*(काष्ठा sockaddr_in6 *)(&(a)))

अटल अंतरभूत पूर्णांक getname_peer(काष्ठा socket *s, काष्ठा sockaddr_storage *a)
अणु
	वापस s->ops->getname(s, (काष्ठा sockaddr *)a, 1);
पूर्ण

अटल अंतरभूत पूर्णांक getname_local(काष्ठा socket *s, काष्ठा sockaddr_storage *a)
अणु
	वापस s->ops->getname(s, (काष्ठा sockaddr *)a, 0);
पूर्ण

अटल अंतरभूत पूर्णांक ksock_recv(काष्ठा socket *sock, अक्षर *buf, माप_प्रकार size,
			     पूर्णांक flags)
अणु
	काष्ठा kvec iov = अणु buf, size पूर्ण;
	काष्ठा msghdr msg = अणु .msg_name = शून्य, .msg_flags = flags पूर्ण;

	वापस kernel_recvmsg(sock, &msg, &iov, 1, size, flags);
पूर्ण

पूर्णांक siw_connect(काष्ठा iw_cm_id *id, काष्ठा iw_cm_conn_param *parm);
पूर्णांक siw_accept(काष्ठा iw_cm_id *id, काष्ठा iw_cm_conn_param *param);
पूर्णांक siw_reject(काष्ठा iw_cm_id *id, स्थिर व्योम *data, u8 len);
पूर्णांक siw_create_listen(काष्ठा iw_cm_id *id, पूर्णांक backlog);
पूर्णांक siw_destroy_listen(काष्ठा iw_cm_id *id);

व्योम siw_cep_get(काष्ठा siw_cep *cep);
व्योम siw_cep_put(काष्ठा siw_cep *cep);
पूर्णांक siw_cm_queue_work(काष्ठा siw_cep *cep, क्रमागत siw_work_type type);

पूर्णांक siw_cm_init(व्योम);
व्योम siw_cm_निकास(व्योम);

/*
 * TCP socket पूर्णांकerface
 */
#घोषणा sk_to_qp(sk) (((काष्ठा siw_cep *)((sk)->sk_user_data))->qp)
#घोषणा sk_to_cep(sk) ((काष्ठा siw_cep *)((sk)->sk_user_data))

#पूर्ण_अगर
