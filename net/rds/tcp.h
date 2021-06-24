<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RDS_TCP_H
#घोषणा _RDS_TCP_H

#घोषणा RDS_TCP_PORT	16385

काष्ठा rds_tcp_incoming अणु
	काष्ठा rds_incoming	ti_inc;
	काष्ठा sk_buff_head	ti_skb_list;
पूर्ण;

काष्ठा rds_tcp_connection अणु

	काष्ठा list_head	t_tcp_node;
	bool			t_tcp_node_detached;
	काष्ठा rds_conn_path	*t_cpath;
	/* t_conn_path_lock synchronizes the connection establishment between
	 * rds_tcp_accept_one and rds_tcp_conn_path_connect
	 */
	काष्ठा mutex		t_conn_path_lock;
	काष्ठा socket		*t_sock;
	व्योम			*t_orig_ग_लिखो_space;
	व्योम			*t_orig_data_पढ़ोy;
	व्योम			*t_orig_state_change;

	काष्ठा rds_tcp_incoming	*t_tinc;
	माप_प्रकार			t_tinc_hdr_rem;
	माप_प्रकार			t_tinc_data_rem;

	/* XXX error report? */
	काष्ठा work_काष्ठा	t_conn_w;
	काष्ठा work_काष्ठा	t_send_w;
	काष्ठा work_काष्ठा	t_करोwn_w;
	काष्ठा work_काष्ठा	t_recv_w;

	/* क्रम info exporting only */
	काष्ठा list_head	t_list_item;
	u32			t_last_sent_nxt;
	u32			t_last_expected_una;
	u32			t_last_seen_una;
पूर्ण;

काष्ठा rds_tcp_statistics अणु
	uपूर्णांक64_t	s_tcp_data_पढ़ोy_calls;
	uपूर्णांक64_t	s_tcp_ग_लिखो_space_calls;
	uपूर्णांक64_t	s_tcp_sndbuf_full;
	uपूर्णांक64_t	s_tcp_connect_raced;
	uपूर्णांक64_t	s_tcp_listen_बंदd_stale;
पूर्ण;

/* tcp.c */
व्योम rds_tcp_tune(काष्ठा socket *sock);
व्योम rds_tcp_set_callbacks(काष्ठा socket *sock, काष्ठा rds_conn_path *cp);
व्योम rds_tcp_reset_callbacks(काष्ठा socket *sock, काष्ठा rds_conn_path *cp);
व्योम rds_tcp_restore_callbacks(काष्ठा socket *sock,
			       काष्ठा rds_tcp_connection *tc);
u32 rds_tcp_ग_लिखो_seq(काष्ठा rds_tcp_connection *tc);
u32 rds_tcp_snd_una(काष्ठा rds_tcp_connection *tc);
u64 rds_tcp_map_seq(काष्ठा rds_tcp_connection *tc, u32 seq);
बाह्य काष्ठा rds_transport rds_tcp_transport;
व्योम rds_tcp_accept_work(काष्ठा sock *sk);
पूर्णांक rds_tcp_laddr_check(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			__u32 scope_id);
/* tcp_connect.c */
पूर्णांक rds_tcp_conn_path_connect(काष्ठा rds_conn_path *cp);
व्योम rds_tcp_conn_path_shutकरोwn(काष्ठा rds_conn_path *conn);
व्योम rds_tcp_state_change(काष्ठा sock *sk);

/* tcp_listen.c */
काष्ठा socket *rds_tcp_listen_init(काष्ठा net *net, bool isv6);
व्योम rds_tcp_listen_stop(काष्ठा socket *sock, काष्ठा work_काष्ठा *acceptor);
व्योम rds_tcp_listen_data_पढ़ोy(काष्ठा sock *sk);
पूर्णांक rds_tcp_accept_one(काष्ठा socket *sock);
व्योम rds_tcp_keepalive(काष्ठा socket *sock);
व्योम *rds_tcp_listen_sock_def_पढ़ोable(काष्ठा net *net);

/* tcp_recv.c */
पूर्णांक rds_tcp_recv_init(व्योम);
व्योम rds_tcp_recv_निकास(व्योम);
व्योम rds_tcp_data_पढ़ोy(काष्ठा sock *sk);
पूर्णांक rds_tcp_recv_path(काष्ठा rds_conn_path *cp);
व्योम rds_tcp_inc_मुक्त(काष्ठा rds_incoming *inc);
पूर्णांक rds_tcp_inc_copy_to_user(काष्ठा rds_incoming *inc, काष्ठा iov_iter *to);

/* tcp_send.c */
व्योम rds_tcp_xmit_path_prepare(काष्ठा rds_conn_path *cp);
व्योम rds_tcp_xmit_path_complete(काष्ठा rds_conn_path *cp);
पूर्णांक rds_tcp_xmit(काष्ठा rds_connection *conn, काष्ठा rds_message *rm,
		 अचिन्हित पूर्णांक hdr_off, अचिन्हित पूर्णांक sg, अचिन्हित पूर्णांक off);
व्योम rds_tcp_ग_लिखो_space(काष्ठा sock *sk);

/* tcp_stats.c */
DECLARE_PER_CPU(काष्ठा rds_tcp_statistics, rds_tcp_stats);
#घोषणा rds_tcp_stats_inc(member) rds_stats_inc_which(rds_tcp_stats, member)
अचिन्हित पूर्णांक rds_tcp_stats_info_copy(काष्ठा rds_info_iterator *iter,
				     अचिन्हित पूर्णांक avail);

#पूर्ण_अगर
