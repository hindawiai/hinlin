<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 *
 * ----
 *
 * Callers क्रम this were originally written against a very simple synchronus
 * API.  This implementation reflects those simple callers.  Some day I'm sure
 * we'll need to move to a more robust posting/callback mechanism.
 *
 * Transmit calls pass in kernel भव addresses and block copying this पूर्णांकo
 * the socket's tx buffers via a usual blocking sendmsg.  They'll block रुकोing
 * क्रम a failed socket to समयout.  TX callers can also pass in a poniter to an
 * 'int' which माला_लो filled with an त्रुटि_सं off the wire in response to the
 * message they send.
 *
 * Handlers क्रम unsolicited messages are रेजिस्टरed.  Each socket has a page
 * that incoming data is copied पूर्णांकo.  First the header, then the data.
 * Handlers are called from only one thपढ़ो with a reference to this per-socket
 * page.  This page is destroyed after the handler call, so it can't be
 * referenced beyond the call.  Handlers may block but are discouraged from
 * करोing so.
 *
 * Any framing errors (bad magic, large payload lengths) बंद a connection.
 *
 * Our sock_container holds the state we associate with a socket.  It's current
 * framing state is held there as well as the refcounting we करो around when it
 * is safe to tear करोwn the socket.  The socket is only finally torn करोwn from
 * the container when the container loses all of its references -- so as दीर्घ
 * as you hold a ref on the container you can trust that the socket is valid
 * क्रम use with kernel socket APIs.
 *
 * Connections are initiated between a pair of nodes when the node with the
 * higher node number माला_लो a heartbeat callback which indicates that the lower
 * numbered node has started heartbeating.  The lower numbered node is passive
 * and only accepts the connection अगर the higher numbered node is heartbeating.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/kref.h>
#समावेश <linux/net.h>
#समावेश <linux/export.h>
#समावेश <net/tcp.h>

#समावेश <linux/uaccess.h>

#समावेश "heartbeat.h"
#समावेश "tcp.h"
#समावेश "nodemanager.h"
#घोषणा MLOG_MASK_PREFIX ML_TCP
#समावेश "masklog.h"
#समावेश "quorum.h"

#समावेश "tcp_internal.h"

#घोषणा SC_NODEF_FMT "node %s (num %u) at %pI4:%u"
#घोषणा SC_NODEF_ARGS(sc) sc->sc_node->nd_name, sc->sc_node->nd_num,	\
			  &sc->sc_node->nd_ipv4_address,		\
			  ntohs(sc->sc_node->nd_ipv4_port)

/*
 * In the following two log macros, the whitespace after the ',' just
 * beक्रमe ##args is पूर्णांकentional. Otherwise, gcc 2.95 will eat the
 * previous token अगर args expands to nothing.
 */
#घोषणा msglog(hdr, fmt, args...) करो अणु					\
	typeof(hdr) __hdr = (hdr);					\
	mlog(ML_MSG, "[mag %u len %u typ %u stat %d sys_stat %d "	\
	     "key %08x num %u] " fmt,					\
	     be16_to_cpu(__hdr->magic), be16_to_cpu(__hdr->data_len), 	\
	     be16_to_cpu(__hdr->msg_type), be32_to_cpu(__hdr->status),	\
	     be32_to_cpu(__hdr->sys_status), be32_to_cpu(__hdr->key),	\
	     be32_to_cpu(__hdr->msg_num) ,  ##args);			\
पूर्ण जबतक (0)

#घोषणा sclog(sc, fmt, args...) करो अणु					\
	typeof(sc) __sc = (sc);						\
	mlog(ML_SOCKET, "[sc %p refs %d sock %p node %u page %p "	\
	     "pg_off %zu] " fmt, __sc,					\
	     kref_पढ़ो(&__sc->sc_kref), __sc->sc_sock,	\
	    __sc->sc_node->nd_num, __sc->sc_page, __sc->sc_page_off ,	\
	    ##args);							\
पूर्ण जबतक (0)

अटल DEFINE_RWLOCK(o2net_handler_lock);
अटल काष्ठा rb_root o2net_handler_tree = RB_ROOT;

अटल काष्ठा o2net_node o2net_nodes[O2NM_MAX_NODES];

/* XXX someday we'll need better accounting */
अटल काष्ठा socket *o2net_listen_sock;

/*
 * listen work is only queued by the listening socket callbacks on the
 * o2net_wq.  tearकरोwn detaches the callbacks beक्रमe destroying the workqueue.
 * quorum work is queued as sock containers are shutकरोwn.. stop_listening
 * tears करोwn all the node's sock containers, preventing future shutकरोwns
 * and queued quroum work, beक्रमe canceling delayed quorum work and
 * destroying the work queue.
 */
अटल काष्ठा workqueue_काष्ठा *o2net_wq;
अटल काष्ठा work_काष्ठा o2net_listen_work;

अटल काष्ठा o2hb_callback_func o2net_hb_up, o2net_hb_करोwn;
#घोषणा O2NET_HB_PRI 0x1

अटल काष्ठा o2net_handshake *o2net_hand;
अटल काष्ठा o2net_msg *o2net_keep_req, *o2net_keep_resp;

अटल पूर्णांक o2net_sys_err_translations[O2NET_ERR_MAX] =
		अणु[O2NET_ERR_NONE]	= 0,
		 [O2NET_ERR_NO_HNDLR]	= -ENOPROTOOPT,
		 [O2NET_ERR_OVERFLOW]	= -EOVERFLOW,
		 [O2NET_ERR_DIED]	= -EHOSTDOWN,पूर्ण;

/* can't quite aव्योम *all* पूर्णांकernal declarations :/ */
अटल व्योम o2net_sc_connect_completed(काष्ठा work_काष्ठा *work);
अटल व्योम o2net_rx_until_empty(काष्ठा work_काष्ठा *work);
अटल व्योम o2net_shutकरोwn_sc(काष्ठा work_काष्ठा *work);
अटल व्योम o2net_listen_data_पढ़ोy(काष्ठा sock *sk);
अटल व्योम o2net_sc_send_keep_req(काष्ठा work_काष्ठा *work);
अटल व्योम o2net_idle_समयr(काष्ठा समयr_list *t);
अटल व्योम o2net_sc_postpone_idle(काष्ठा o2net_sock_container *sc);
अटल व्योम o2net_sc_reset_idle_समयr(काष्ठा o2net_sock_container *sc);

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम o2net_init_nst(काष्ठा o2net_send_tracking *nst, u32 msgtype,
			   u32 msgkey, काष्ठा task_काष्ठा *task, u8 node)
अणु
	INIT_LIST_HEAD(&nst->st_net_debug_item);
	nst->st_task = task;
	nst->st_msg_type = msgtype;
	nst->st_msg_key = msgkey;
	nst->st_node = node;
पूर्ण

अटल अंतरभूत व्योम o2net_set_nst_sock_समय(काष्ठा o2net_send_tracking *nst)
अणु
	nst->st_sock_समय = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम o2net_set_nst_send_समय(काष्ठा o2net_send_tracking *nst)
अणु
	nst->st_send_समय = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम o2net_set_nst_status_समय(काष्ठा o2net_send_tracking *nst)
अणु
	nst->st_status_समय = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम o2net_set_nst_sock_container(काष्ठा o2net_send_tracking *nst,
						काष्ठा o2net_sock_container *sc)
अणु
	nst->st_sc = sc;
पूर्ण

अटल अंतरभूत व्योम o2net_set_nst_msg_id(काष्ठा o2net_send_tracking *nst,
					u32 msg_id)
अणु
	nst->st_id = msg_id;
पूर्ण

अटल अंतरभूत व्योम o2net_set_sock_समयr(काष्ठा o2net_sock_container *sc)
अणु
	sc->sc_tv_समयr = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम o2net_set_data_पढ़ोy_समय(काष्ठा o2net_sock_container *sc)
अणु
	sc->sc_tv_data_पढ़ोy = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम o2net_set_advance_start_समय(काष्ठा o2net_sock_container *sc)
अणु
	sc->sc_tv_advance_start = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम o2net_set_advance_stop_समय(काष्ठा o2net_sock_container *sc)
अणु
	sc->sc_tv_advance_stop = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम o2net_set_func_start_समय(काष्ठा o2net_sock_container *sc)
अणु
	sc->sc_tv_func_start = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम o2net_set_func_stop_समय(काष्ठा o2net_sock_container *sc)
अणु
	sc->sc_tv_func_stop = kसमय_get();
पूर्ण

#अन्यथा  /* CONFIG_DEBUG_FS */
# define o2net_init_nst(a, b, c, d, e)
# define o2net_set_nst_sock_समय(a)
# define o2net_set_nst_send_समय(a)
# define o2net_set_nst_status_समय(a)
# define o2net_set_nst_sock_container(a, b)
# define o2net_set_nst_msg_id(a, b)
# define o2net_set_sock_समयr(a)
# define o2net_set_data_पढ़ोy_समय(a)
# define o2net_set_advance_start_समय(a)
# define o2net_set_advance_stop_समय(a)
# define o2net_set_func_start_समय(a)
# define o2net_set_func_stop_समय(a)
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#अगर_घोषित CONFIG_OCFS2_FS_STATS
अटल kसमय_प्रकार o2net_get_func_run_समय(काष्ठा o2net_sock_container *sc)
अणु
	वापस kसमय_sub(sc->sc_tv_func_stop, sc->sc_tv_func_start);
पूर्ण

अटल व्योम o2net_update_send_stats(काष्ठा o2net_send_tracking *nst,
				    काष्ठा o2net_sock_container *sc)
अणु
	sc->sc_tv_status_total = kसमय_add(sc->sc_tv_status_total,
					   kसमय_sub(kसमय_get(),
						     nst->st_status_समय));
	sc->sc_tv_send_total = kसमय_add(sc->sc_tv_send_total,
					 kसमय_sub(nst->st_status_समय,
						   nst->st_send_समय));
	sc->sc_tv_acquiry_total = kसमय_add(sc->sc_tv_acquiry_total,
					    kसमय_sub(nst->st_send_समय,
						      nst->st_sock_समय));
	sc->sc_send_count++;
पूर्ण

अटल व्योम o2net_update_recv_stats(काष्ठा o2net_sock_container *sc)
अणु
	sc->sc_tv_process_total = kसमय_add(sc->sc_tv_process_total,
					    o2net_get_func_run_समय(sc));
	sc->sc_recv_count++;
पूर्ण

#अन्यथा

# define o2net_update_send_stats(a, b)

# define o2net_update_recv_stats(sc)

#पूर्ण_अगर /* CONFIG_OCFS2_FS_STATS */

अटल अंतरभूत अचिन्हित पूर्णांक o2net_reconnect_delay(व्योम)
अणु
	वापस o2nm_single_cluster->cl_reconnect_delay_ms;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक o2net_keepalive_delay(व्योम)
अणु
	वापस o2nm_single_cluster->cl_keepalive_delay_ms;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक o2net_idle_समयout(व्योम)
अणु
	वापस o2nm_single_cluster->cl_idle_समयout_ms;
पूर्ण

अटल अंतरभूत पूर्णांक o2net_sys_err_to_त्रुटि_सं(क्रमागत o2net_प्रणाली_error err)
अणु
	पूर्णांक trans;
	BUG_ON(err >= O2NET_ERR_MAX);
	trans = o2net_sys_err_translations[err];

	/* Just in हाल we mess up the translation table above */
	BUG_ON(err != O2NET_ERR_NONE && trans == 0);
	वापस trans;
पूर्ण

अटल काष्ठा o2net_node * o2net_nn_from_num(u8 node_num)
अणु
	BUG_ON(node_num >= ARRAY_SIZE(o2net_nodes));
	वापस &o2net_nodes[node_num];
पूर्ण

अटल u8 o2net_num_from_nn(काष्ठा o2net_node *nn)
अणु
	BUG_ON(nn == शून्य);
	वापस nn - o2net_nodes;
पूर्ण

/* ------------------------------------------------------------ */

अटल पूर्णांक o2net_prep_nsw(काष्ठा o2net_node *nn, काष्ठा o2net_status_रुको *nsw)
अणु
	पूर्णांक ret;

	spin_lock(&nn->nn_lock);
	ret = idr_alloc(&nn->nn_status_idr, nsw, 0, 0, GFP_ATOMIC);
	अगर (ret >= 0) अणु
		nsw->ns_id = ret;
		list_add_tail(&nsw->ns_node_item, &nn->nn_status_list);
	पूर्ण
	spin_unlock(&nn->nn_lock);
	अगर (ret < 0)
		वापस ret;

	init_रुकोqueue_head(&nsw->ns_wq);
	nsw->ns_sys_status = O2NET_ERR_NONE;
	nsw->ns_status = 0;
	वापस 0;
पूर्ण

अटल व्योम o2net_complete_nsw_locked(काष्ठा o2net_node *nn,
				      काष्ठा o2net_status_रुको *nsw,
				      क्रमागत o2net_प्रणाली_error sys_status,
				      s32 status)
अणु
	निश्चित_spin_locked(&nn->nn_lock);

	अगर (!list_empty(&nsw->ns_node_item)) अणु
		list_del_init(&nsw->ns_node_item);
		nsw->ns_sys_status = sys_status;
		nsw->ns_status = status;
		idr_हटाओ(&nn->nn_status_idr, nsw->ns_id);
		wake_up(&nsw->ns_wq);
	पूर्ण
पूर्ण

अटल व्योम o2net_complete_nsw(काष्ठा o2net_node *nn,
			       काष्ठा o2net_status_रुको *nsw,
			       u64 id, क्रमागत o2net_प्रणाली_error sys_status,
			       s32 status)
अणु
	spin_lock(&nn->nn_lock);
	अगर (nsw == शून्य) अणु
		अगर (id > पूर्णांक_उच्च)
			जाओ out;

		nsw = idr_find(&nn->nn_status_idr, id);
		अगर (nsw == शून्य)
			जाओ out;
	पूर्ण

	o2net_complete_nsw_locked(nn, nsw, sys_status, status);

out:
	spin_unlock(&nn->nn_lock);
	वापस;
पूर्ण

अटल व्योम o2net_complete_nodes_nsw(काष्ठा o2net_node *nn)
अणु
	काष्ठा o2net_status_रुको *nsw, *पंचांगp;
	अचिन्हित पूर्णांक num_समाप्तs = 0;

	निश्चित_spin_locked(&nn->nn_lock);

	list_क्रम_each_entry_safe(nsw, पंचांगp, &nn->nn_status_list, ns_node_item) अणु
		o2net_complete_nsw_locked(nn, nsw, O2NET_ERR_DIED, 0);
		num_समाप्तs++;
	पूर्ण

	mlog(0, "completed %d messages for node %u\n", num_समाप्तs,
	     o2net_num_from_nn(nn));
पूर्ण

अटल पूर्णांक o2net_nsw_completed(काष्ठा o2net_node *nn,
			       काष्ठा o2net_status_रुको *nsw)
अणु
	पूर्णांक completed;
	spin_lock(&nn->nn_lock);
	completed = list_empty(&nsw->ns_node_item);
	spin_unlock(&nn->nn_lock);
	वापस completed;
पूर्ण

/* ------------------------------------------------------------ */

अटल व्योम sc_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा o2net_sock_container *sc = container_of(kref,
					काष्ठा o2net_sock_container, sc_kref);
	BUG_ON(समयr_pending(&sc->sc_idle_समयout));

	sclog(sc, "releasing\n");

	अगर (sc->sc_sock) अणु
		sock_release(sc->sc_sock);
		sc->sc_sock = शून्य;
	पूर्ण

	o2nm_undepend_item(&sc->sc_node->nd_item);
	o2nm_node_put(sc->sc_node);
	sc->sc_node = शून्य;

	o2net_debug_del_sc(sc);

	अगर (sc->sc_page)
		__मुक्त_page(sc->sc_page);
	kमुक्त(sc);
पूर्ण

अटल व्योम sc_put(काष्ठा o2net_sock_container *sc)
अणु
	sclog(sc, "put\n");
	kref_put(&sc->sc_kref, sc_kref_release);
पूर्ण
अटल व्योम sc_get(काष्ठा o2net_sock_container *sc)
अणु
	sclog(sc, "get\n");
	kref_get(&sc->sc_kref);
पूर्ण
अटल काष्ठा o2net_sock_container *sc_alloc(काष्ठा o2nm_node *node)
अणु
	काष्ठा o2net_sock_container *sc, *ret = शून्य;
	काष्ठा page *page = शून्य;
	पूर्णांक status = 0;

	page = alloc_page(GFP_NOFS);
	sc = kzalloc(माप(*sc), GFP_NOFS);
	अगर (sc == शून्य || page == शून्य)
		जाओ out;

	kref_init(&sc->sc_kref);
	o2nm_node_get(node);
	sc->sc_node = node;

	/* pin the node item of the remote node */
	status = o2nm_depend_item(&node->nd_item);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		o2nm_node_put(node);
		जाओ out;
	पूर्ण
	INIT_WORK(&sc->sc_connect_work, o2net_sc_connect_completed);
	INIT_WORK(&sc->sc_rx_work, o2net_rx_until_empty);
	INIT_WORK(&sc->sc_shutकरोwn_work, o2net_shutकरोwn_sc);
	INIT_DELAYED_WORK(&sc->sc_keepalive_work, o2net_sc_send_keep_req);

	समयr_setup(&sc->sc_idle_समयout, o2net_idle_समयr, 0);

	sclog(sc, "alloced\n");

	ret = sc;
	sc->sc_page = page;
	o2net_debug_add_sc(sc);
	sc = शून्य;
	page = शून्य;

out:
	अगर (page)
		__मुक्त_page(page);
	kमुक्त(sc);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------ */

अटल व्योम o2net_sc_queue_work(काष्ठा o2net_sock_container *sc,
				काष्ठा work_काष्ठा *work)
अणु
	sc_get(sc);
	अगर (!queue_work(o2net_wq, work))
		sc_put(sc);
पूर्ण
अटल व्योम o2net_sc_queue_delayed_work(काष्ठा o2net_sock_container *sc,
					काष्ठा delayed_work *work,
					पूर्णांक delay)
अणु
	sc_get(sc);
	अगर (!queue_delayed_work(o2net_wq, work, delay))
		sc_put(sc);
पूर्ण
अटल व्योम o2net_sc_cancel_delayed_work(काष्ठा o2net_sock_container *sc,
					 काष्ठा delayed_work *work)
अणु
	अगर (cancel_delayed_work(work))
		sc_put(sc);
पूर्ण

अटल atomic_t o2net_connected_peers = ATOMIC_INIT(0);

पूर्णांक o2net_num_connected_peers(व्योम)
अणु
	वापस atomic_पढ़ो(&o2net_connected_peers);
पूर्ण

अटल व्योम o2net_set_nn_state(काष्ठा o2net_node *nn,
			       काष्ठा o2net_sock_container *sc,
			       अचिन्हित valid, पूर्णांक err)
अणु
	पूर्णांक was_valid = nn->nn_sc_valid;
	पूर्णांक was_err = nn->nn_persistent_error;
	काष्ठा o2net_sock_container *old_sc = nn->nn_sc;

	निश्चित_spin_locked(&nn->nn_lock);

	अगर (old_sc && !sc)
		atomic_dec(&o2net_connected_peers);
	अन्यथा अगर (!old_sc && sc)
		atomic_inc(&o2net_connected_peers);

	/* the node num comparison and single connect/accept path should stop
	 * an non-null sc from being overwritten with another */
	BUG_ON(sc && nn->nn_sc && nn->nn_sc != sc);
	mlog_bug_on_msg(err && valid, "err %d valid %u\n", err, valid);
	mlog_bug_on_msg(valid && !sc, "valid %u sc %p\n", valid, sc);

	अगर (was_valid && !valid && err == 0)
		err = -ENOTCONN;

	mlog(ML_CONN, "node %u sc: %p -> %p, valid %u -> %u, err %d -> %d\n",
	     o2net_num_from_nn(nn), nn->nn_sc, sc, nn->nn_sc_valid, valid,
	     nn->nn_persistent_error, err);

	nn->nn_sc = sc;
	nn->nn_sc_valid = valid ? 1 : 0;
	nn->nn_persistent_error = err;

	/* mirrors o2net_tx_can_proceed() */
	अगर (nn->nn_persistent_error || nn->nn_sc_valid)
		wake_up(&nn->nn_sc_wq);

	अगर (was_valid && !was_err && nn->nn_persistent_error) अणु
		o2quo_conn_err(o2net_num_from_nn(nn));
		queue_delayed_work(o2net_wq, &nn->nn_still_up,
				   msecs_to_jअगरfies(O2NET_QUORUM_DELAY_MS));
	पूर्ण

	अगर (was_valid && !valid) अणु
		अगर (old_sc)
			prपूर्णांकk(KERN_NOTICE "o2net: No longer connected to "
				SC_NODEF_FMT "\n", SC_NODEF_ARGS(old_sc));
		o2net_complete_nodes_nsw(nn);
	पूर्ण

	अगर (!was_valid && valid) अणु
		o2quo_conn_up(o2net_num_from_nn(nn));
		cancel_delayed_work(&nn->nn_connect_expired);
		prपूर्णांकk(KERN_NOTICE "o2net: %s " SC_NODEF_FMT "\n",
		       o2nm_this_node() > sc->sc_node->nd_num ?
		       "Connected to" : "Accepted connection from",
		       SC_NODEF_ARGS(sc));
	पूर्ण

	/* trigger the connecting worker func as दीर्घ as we're not valid,
	 * it will back off अगर it shouldn't connect.  This can be called
	 * from node config tearकरोwn and so needs to be careful about
	 * the work queue actually being up. */
	अगर (!valid && o2net_wq) अणु
		अचिन्हित दीर्घ delay;
		/* delay अगर we're within a RECONNECT_DELAY of the
		 * last attempt */
		delay = (nn->nn_last_connect_attempt +
			 msecs_to_jअगरfies(o2net_reconnect_delay()))
			- jअगरfies;
		अगर (delay > msecs_to_jअगरfies(o2net_reconnect_delay()))
			delay = 0;
		mlog(ML_CONN, "queueing conn attempt in %lu jiffies\n", delay);
		queue_delayed_work(o2net_wq, &nn->nn_connect_work, delay);

		/*
		 * Delay the expired work after idle समयout.
		 *
		 * We might have lots of failed connection attempts that run
		 * through here but we only cancel the connect_expired work when
		 * a connection attempt succeeds.  So only the first enqueue of
		 * the connect_expired work will करो anything.  The rest will see
		 * that it's alपढ़ोy queued and करो nothing.
		 */
		delay += msecs_to_jअगरfies(o2net_idle_समयout());
		queue_delayed_work(o2net_wq, &nn->nn_connect_expired, delay);
	पूर्ण

	/* keep track of the nn's sc ref क्रम the caller */
	अगर ((old_sc == शून्य) && sc)
		sc_get(sc);
	अगर (old_sc && (old_sc != sc)) अणु
		o2net_sc_queue_work(old_sc, &old_sc->sc_shutकरोwn_work);
		sc_put(old_sc);
	पूर्ण
पूर्ण

/* see o2net_रेजिस्टर_callbacks() */
अटल व्योम o2net_data_पढ़ोy(काष्ठा sock *sk)
अणु
	व्योम (*पढ़ोy)(काष्ठा sock *sk);
	काष्ठा o2net_sock_container *sc;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	sc = sk->sk_user_data;
	अगर (sc) अणु
		sclog(sc, "data_ready hit\n");
		o2net_set_data_पढ़ोy_समय(sc);
		o2net_sc_queue_work(sc, &sc->sc_rx_work);
		पढ़ोy = sc->sc_data_पढ़ोy;
	पूर्ण अन्यथा अणु
		पढ़ोy = sk->sk_data_पढ़ोy;
	पूर्ण
	पढ़ो_unlock_bh(&sk->sk_callback_lock);

	पढ़ोy(sk);
पूर्ण

/* see o2net_रेजिस्टर_callbacks() */
अटल व्योम o2net_state_change(काष्ठा sock *sk)
अणु
	व्योम (*state_change)(काष्ठा sock *sk);
	काष्ठा o2net_sock_container *sc;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	sc = sk->sk_user_data;
	अगर (sc == शून्य) अणु
		state_change = sk->sk_state_change;
		जाओ out;
	पूर्ण

	sclog(sc, "state_change to %d\n", sk->sk_state);

	state_change = sc->sc_state_change;

	चयन(sk->sk_state) अणु
	/* ignore connecting sockets as they make progress */
	हाल TCP_SYN_SENT:
	हाल TCP_SYN_RECV:
		अवरोध;
	हाल TCP_ESTABLISHED:
		o2net_sc_queue_work(sc, &sc->sc_connect_work);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "o2net: Connection to " SC_NODEF_FMT
			" shutdown, state %d\n",
			SC_NODEF_ARGS(sc), sk->sk_state);
		o2net_sc_queue_work(sc, &sc->sc_shutकरोwn_work);
		अवरोध;
	पूर्ण
out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	state_change(sk);
पूर्ण

/*
 * we रेजिस्टर callbacks so we can queue work on events beक्रमe calling
 * the original callbacks.  our callbacks our careful to test user_data
 * to discover when they've reaced with o2net_unरेजिस्टर_callbacks().
 */
अटल व्योम o2net_रेजिस्टर_callbacks(काष्ठा sock *sk,
				     काष्ठा o2net_sock_container *sc)
अणु
	ग_लिखो_lock_bh(&sk->sk_callback_lock);

	/* accepted sockets inherit the old listen socket data पढ़ोy */
	अगर (sk->sk_data_पढ़ोy == o2net_listen_data_पढ़ोy) अणु
		sk->sk_data_पढ़ोy = sk->sk_user_data;
		sk->sk_user_data = शून्य;
	पूर्ण

	BUG_ON(sk->sk_user_data != शून्य);
	sk->sk_user_data = sc;
	sc_get(sc);

	sc->sc_data_पढ़ोy = sk->sk_data_पढ़ोy;
	sc->sc_state_change = sk->sk_state_change;
	sk->sk_data_पढ़ोy = o2net_data_पढ़ोy;
	sk->sk_state_change = o2net_state_change;

	mutex_init(&sc->sc_send_lock);

	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल पूर्णांक o2net_unरेजिस्टर_callbacks(काष्ठा sock *sk,
			           काष्ठा o2net_sock_container *sc)
अणु
	पूर्णांक ret = 0;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	अगर (sk->sk_user_data == sc) अणु
		ret = 1;
		sk->sk_user_data = शून्य;
		sk->sk_data_पढ़ोy = sc->sc_data_पढ़ोy;
		sk->sk_state_change = sc->sc_state_change;
	पूर्ण
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);

	वापस ret;
पूर्ण

/*
 * this is a little helper that is called by callers who have seen a problem
 * with an sc and want to detach it from the nn अगर someone alपढ़ोy hasn't beat
 * them to it.  अगर an error is given then the shutकरोwn will be persistent
 * and pending transmits will be canceled.
 */
अटल व्योम o2net_ensure_shutकरोwn(काष्ठा o2net_node *nn,
			           काष्ठा o2net_sock_container *sc,
				   पूर्णांक err)
अणु
	spin_lock(&nn->nn_lock);
	अगर (nn->nn_sc == sc)
		o2net_set_nn_state(nn, शून्य, 0, err);
	spin_unlock(&nn->nn_lock);
पूर्ण

/*
 * This work queue function perक्रमms the blocking parts of socket shutकरोwn.  A
 * few paths lead here.  set_nn_state will trigger this callback अगर it sees an
 * sc detached from the nn.  state_change will also trigger this callback
 * directly when it sees errors.  In that हाल we need to call set_nn_state
 * ourselves as state_change couldn't get the nn_lock and call set_nn_state
 * itself.
 */
अटल व्योम o2net_shutकरोwn_sc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा o2net_sock_container *sc =
		container_of(work, काष्ठा o2net_sock_container,
			     sc_shutकरोwn_work);
	काष्ठा o2net_node *nn = o2net_nn_from_num(sc->sc_node->nd_num);

	sclog(sc, "shutting down\n");

	/* drop the callbacks ref and call shutकरोwn only once */
	अगर (o2net_unरेजिस्टर_callbacks(sc->sc_sock->sk, sc)) अणु
		/* we shouldn't flush as we're in the thपढ़ो, the
		 * races with pending sc work काष्ठाs are harmless */
		del_समयr_sync(&sc->sc_idle_समयout);
		o2net_sc_cancel_delayed_work(sc, &sc->sc_keepalive_work);
		sc_put(sc);
		kernel_sock_shutकरोwn(sc->sc_sock, SHUT_RDWR);
	पूर्ण

	/* not fatal so failed connects beक्रमe the other guy has our
	 * heartbeat can be retried */
	o2net_ensure_shutकरोwn(nn, sc, 0);
	sc_put(sc);
पूर्ण

/* ------------------------------------------------------------ */

अटल पूर्णांक o2net_handler_cmp(काष्ठा o2net_msg_handler *nmh, u32 msg_type,
			     u32 key)
अणु
	पूर्णांक ret = स_भेद(&nmh->nh_key, &key, माप(key));

	अगर (ret == 0)
		ret = स_भेद(&nmh->nh_msg_type, &msg_type, माप(msg_type));

	वापस ret;
पूर्ण

अटल काष्ठा o2net_msg_handler *
o2net_handler_tree_lookup(u32 msg_type, u32 key, काष्ठा rb_node ***ret_p,
			  काष्ठा rb_node **ret_parent)
अणु
	काष्ठा rb_node **p = &o2net_handler_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा o2net_msg_handler *nmh, *ret = शून्य;
	पूर्णांक cmp;

	जबतक (*p) अणु
		parent = *p;
		nmh = rb_entry(parent, काष्ठा o2net_msg_handler, nh_node);
		cmp = o2net_handler_cmp(nmh, msg_type, key);

		अगर (cmp < 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (cmp > 0)
			p = &(*p)->rb_right;
		अन्यथा अणु
			ret = nmh;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret_p != शून्य)
		*ret_p = p;
	अगर (ret_parent != शून्य)
		*ret_parent = parent;

	वापस ret;
पूर्ण

अटल व्योम o2net_handler_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा o2net_msg_handler *nmh;
	nmh = container_of(kref, काष्ठा o2net_msg_handler, nh_kref);

	kमुक्त(nmh);
पूर्ण

अटल व्योम o2net_handler_put(काष्ठा o2net_msg_handler *nmh)
अणु
	kref_put(&nmh->nh_kref, o2net_handler_kref_release);
पूर्ण

/* max_len is protection क्रम the handler func.  incoming messages won't
 * be given to the handler अगर their payload is दीर्घer than the max. */
पूर्णांक o2net_रेजिस्टर_handler(u32 msg_type, u32 key, u32 max_len,
			   o2net_msg_handler_func *func, व्योम *data,
			   o2net_post_msg_handler_func *post_func,
			   काष्ठा list_head *unreg_list)
अणु
	काष्ठा o2net_msg_handler *nmh = शून्य;
	काष्ठा rb_node **p, *parent;
	पूर्णांक ret = 0;

	अगर (max_len > O2NET_MAX_PAYLOAD_BYTES) अणु
		mlog(0, "max_len for message handler out of range: %u\n",
			max_len);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!msg_type) अणु
		mlog(0, "no message type provided: %u, %p\n", msg_type, func);
		ret = -EINVAL;
		जाओ out;

	पूर्ण
	अगर (!func) अणु
		mlog(0, "no message handler provided: %u, %p\n",
		       msg_type, func);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

       	nmh = kzalloc(माप(काष्ठा o2net_msg_handler), GFP_NOFS);
	अगर (nmh == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	nmh->nh_func = func;
	nmh->nh_func_data = data;
	nmh->nh_post_func = post_func;
	nmh->nh_msg_type = msg_type;
	nmh->nh_max_len = max_len;
	nmh->nh_key = key;
	/* the tree and list get this ref.. they're both हटाओd in
	 * unरेजिस्टर when this ref is dropped */
	kref_init(&nmh->nh_kref);
	INIT_LIST_HEAD(&nmh->nh_unरेजिस्टर_item);

	ग_लिखो_lock(&o2net_handler_lock);
	अगर (o2net_handler_tree_lookup(msg_type, key, &p, &parent))
		ret = -EEXIST;
	अन्यथा अणु
	        rb_link_node(&nmh->nh_node, parent, p);
		rb_insert_color(&nmh->nh_node, &o2net_handler_tree);
		list_add_tail(&nmh->nh_unरेजिस्टर_item, unreg_list);

		mlog(ML_TCP, "registered handler func %p type %u key %08x\n",
		     func, msg_type, key);
		/* we've had some trouble with handlers seemingly vanishing. */
		mlog_bug_on_msg(o2net_handler_tree_lookup(msg_type, key, &p,
							  &parent) == शून्य,
			        "couldn't find handler we *just* registered "
				"for type %u key %08x\n", msg_type, key);
	पूर्ण
	ग_लिखो_unlock(&o2net_handler_lock);

out:
	अगर (ret)
		kमुक्त(nmh);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(o2net_रेजिस्टर_handler);

व्योम o2net_unरेजिस्टर_handler_list(काष्ठा list_head *list)
अणु
	काष्ठा o2net_msg_handler *nmh, *n;

	ग_लिखो_lock(&o2net_handler_lock);
	list_क्रम_each_entry_safe(nmh, n, list, nh_unरेजिस्टर_item) अणु
		mlog(ML_TCP, "unregistering handler func %p type %u key %08x\n",
		     nmh->nh_func, nmh->nh_msg_type, nmh->nh_key);
		rb_erase(&nmh->nh_node, &o2net_handler_tree);
		list_del_init(&nmh->nh_unरेजिस्टर_item);
		kref_put(&nmh->nh_kref, o2net_handler_kref_release);
	पूर्ण
	ग_लिखो_unlock(&o2net_handler_lock);
पूर्ण
EXPORT_SYMBOL_GPL(o2net_unरेजिस्टर_handler_list);

अटल काष्ठा o2net_msg_handler *o2net_handler_get(u32 msg_type, u32 key)
अणु
	काष्ठा o2net_msg_handler *nmh;

	पढ़ो_lock(&o2net_handler_lock);
	nmh = o2net_handler_tree_lookup(msg_type, key, शून्य, शून्य);
	अगर (nmh)
		kref_get(&nmh->nh_kref);
	पढ़ो_unlock(&o2net_handler_lock);

	वापस nmh;
पूर्ण

/* ------------------------------------------------------------ */

अटल पूर्णांक o2net_recv_tcp_msg(काष्ठा socket *sock, व्योम *data, माप_प्रकार len)
अणु
	काष्ठा kvec vec = अणु .iov_len = len, .iov_base = data, पूर्ण;
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT, पूर्ण;
	iov_iter_kvec(&msg.msg_iter, READ, &vec, 1, len);
	वापस sock_recvmsg(sock, &msg, MSG_DONTWAIT);
पूर्ण

अटल पूर्णांक o2net_send_tcp_msg(काष्ठा socket *sock, काष्ठा kvec *vec,
			      माप_प्रकार veclen, माप_प्रकार total)
अणु
	पूर्णांक ret;
	काष्ठा msghdr msg = अणु.msg_flags = 0,पूर्ण;

	अगर (sock == शून्य) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = kernel_sendmsg(sock, &msg, vec, veclen, total);
	अगर (likely(ret == total))
		वापस 0;
	mlog(ML_ERROR, "sendmsg returned %d instead of %zu\n", ret, total);
	अगर (ret >= 0)
		ret = -EPIPE; /* should be smarter, I bet */
out:
	mlog(0, "returning error: %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम o2net_sendpage(काष्ठा o2net_sock_container *sc,
			   व्योम *kदो_स्मृतिed_virt,
			   माप_प्रकार size)
अणु
	काष्ठा o2net_node *nn = o2net_nn_from_num(sc->sc_node->nd_num);
	sमाप_प्रकार ret;

	जबतक (1) अणु
		mutex_lock(&sc->sc_send_lock);
		ret = sc->sc_sock->ops->sendpage(sc->sc_sock,
						 virt_to_page(kदो_स्मृतिed_virt),
						 offset_in_page(kदो_स्मृतिed_virt),
						 size, MSG_DONTWAIT);
		mutex_unlock(&sc->sc_send_lock);
		अगर (ret == size)
			अवरोध;
		अगर (ret == (sमाप_प्रकार)-EAGAIN) अणु
			mlog(0, "sendpage of size %zu to " SC_NODEF_FMT
			     " returned EAGAIN\n", size, SC_NODEF_ARGS(sc));
			cond_resched();
			जारी;
		पूर्ण
		mlog(ML_ERROR, "sendpage of size %zu to " SC_NODEF_FMT
		     " failed with %zd\n", size, SC_NODEF_ARGS(sc), ret);
		o2net_ensure_shutकरोwn(nn, sc, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम o2net_init_msg(काष्ठा o2net_msg *msg, u16 data_len, u16 msg_type, u32 key)
अणु
	स_रखो(msg, 0, माप(काष्ठा o2net_msg));
	msg->magic = cpu_to_be16(O2NET_MSG_MAGIC);
	msg->data_len = cpu_to_be16(data_len);
	msg->msg_type = cpu_to_be16(msg_type);
	msg->sys_status = cpu_to_be32(O2NET_ERR_NONE);
	msg->status = 0;
	msg->key = cpu_to_be32(key);
पूर्ण

अटल पूर्णांक o2net_tx_can_proceed(काष्ठा o2net_node *nn,
			        काष्ठा o2net_sock_container **sc_ret,
				पूर्णांक *error)
अणु
	पूर्णांक ret = 0;

	spin_lock(&nn->nn_lock);
	अगर (nn->nn_persistent_error) अणु
		ret = 1;
		*sc_ret = शून्य;
		*error = nn->nn_persistent_error;
	पूर्ण अन्यथा अगर (nn->nn_sc_valid) अणु
		kref_get(&nn->nn_sc->sc_kref);

		ret = 1;
		*sc_ret = nn->nn_sc;
		*error = 0;
	पूर्ण
	spin_unlock(&nn->nn_lock);

	वापस ret;
पूर्ण

/* Get a map of all nodes to which this node is currently connected to */
व्योम o2net_fill_node_map(अचिन्हित दीर्घ *map, अचिन्हित bytes)
अणु
	काष्ठा o2net_sock_container *sc;
	पूर्णांक node, ret;

	BUG_ON(bytes < (BITS_TO_LONGS(O2NM_MAX_NODES) * माप(अचिन्हित दीर्घ)));

	स_रखो(map, 0, bytes);
	क्रम (node = 0; node < O2NM_MAX_NODES; ++node) अणु
		अगर (!o2net_tx_can_proceed(o2net_nn_from_num(node), &sc, &ret))
			जारी;
		अगर (!ret) अणु
			set_bit(node, map);
			sc_put(sc);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(o2net_fill_node_map);

पूर्णांक o2net_send_message_vec(u32 msg_type, u32 key, काष्ठा kvec *caller_vec,
			   माप_प्रकार caller_veclen, u8 target_node, पूर्णांक *status)
अणु
	पूर्णांक ret = 0;
	काष्ठा o2net_msg *msg = शून्य;
	माप_प्रकार veclen, caller_bytes = 0;
	काष्ठा kvec *vec = शून्य;
	काष्ठा o2net_sock_container *sc = शून्य;
	काष्ठा o2net_node *nn = o2net_nn_from_num(target_node);
	काष्ठा o2net_status_रुको nsw = अणु
		.ns_node_item = LIST_HEAD_INIT(nsw.ns_node_item),
	पूर्ण;
	काष्ठा o2net_send_tracking nst;

	o2net_init_nst(&nst, msg_type, key, current, target_node);

	अगर (o2net_wq == शून्य) अणु
		mlog(0, "attempt to tx without o2netd running\n");
		ret = -ESRCH;
		जाओ out;
	पूर्ण

	अगर (caller_veclen == 0) अणु
		mlog(0, "bad kvec array length\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	caller_bytes = iov_length((काष्ठा iovec *)caller_vec, caller_veclen);
	अगर (caller_bytes > O2NET_MAX_PAYLOAD_BYTES) अणु
		mlog(0, "total payload len %zu too large\n", caller_bytes);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (target_node == o2nm_this_node()) अणु
		ret = -ELOOP;
		जाओ out;
	पूर्ण

	o2net_debug_add_nst(&nst);

	o2net_set_nst_sock_समय(&nst);

	रुको_event(nn->nn_sc_wq, o2net_tx_can_proceed(nn, &sc, &ret));
	अगर (ret)
		जाओ out;

	o2net_set_nst_sock_container(&nst, sc);

	veclen = caller_veclen + 1;
	vec = kदो_स्मृति_array(veclen, माप(काष्ठा kvec), GFP_ATOMIC);
	अगर (vec == शून्य) अणु
		mlog(0, "failed to %zu element kvec!\n", veclen);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	msg = kदो_स्मृति(माप(काष्ठा o2net_msg), GFP_ATOMIC);
	अगर (!msg) अणु
		mlog(0, "failed to allocate a o2net_msg!\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	o2net_init_msg(msg, caller_bytes, msg_type, key);

	vec[0].iov_len = माप(काष्ठा o2net_msg);
	vec[0].iov_base = msg;
	स_नकल(&vec[1], caller_vec, caller_veclen * माप(काष्ठा kvec));

	ret = o2net_prep_nsw(nn, &nsw);
	अगर (ret)
		जाओ out;

	msg->msg_num = cpu_to_be32(nsw.ns_id);
	o2net_set_nst_msg_id(&nst, nsw.ns_id);

	o2net_set_nst_send_समय(&nst);

	/* finally, convert the message header to network byte-order
	 * and send */
	mutex_lock(&sc->sc_send_lock);
	ret = o2net_send_tcp_msg(sc->sc_sock, vec, veclen,
				 माप(काष्ठा o2net_msg) + caller_bytes);
	mutex_unlock(&sc->sc_send_lock);
	msglog(msg, "sending returned %d\n", ret);
	अगर (ret < 0) अणु
		mlog(0, "error returned from o2net_send_tcp_msg=%d\n", ret);
		जाओ out;
	पूर्ण

	/* रुको on other node's handler */
	o2net_set_nst_status_समय(&nst);
	रुको_event(nsw.ns_wq, o2net_nsw_completed(nn, &nsw));

	o2net_update_send_stats(&nst, sc);

	/* Note that we aव्योम overwriting the callers status वापस
	 * variable अगर a प्रणाली error was reported on the other
	 * side. Callers beware. */
	ret = o2net_sys_err_to_त्रुटि_सं(nsw.ns_sys_status);
	अगर (status && !ret)
		*status = nsw.ns_status;

	mlog(0, "woken, returning system status %d, user status %d\n",
	     ret, nsw.ns_status);
out:
	o2net_debug_del_nst(&nst); /* must be beक्रमe dropping sc and node */
	अगर (sc)
		sc_put(sc);
	kमुक्त(vec);
	kमुक्त(msg);
	o2net_complete_nsw(nn, &nsw, 0, 0, 0);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(o2net_send_message_vec);

पूर्णांक o2net_send_message(u32 msg_type, u32 key, व्योम *data, u32 len,
		       u8 target_node, पूर्णांक *status)
अणु
	काष्ठा kvec vec = अणु
		.iov_base = data,
		.iov_len = len,
	पूर्ण;
	वापस o2net_send_message_vec(msg_type, key, &vec, 1,
				      target_node, status);
पूर्ण
EXPORT_SYMBOL_GPL(o2net_send_message);

अटल पूर्णांक o2net_send_status_magic(काष्ठा socket *sock, काष्ठा o2net_msg *hdr,
				   क्रमागत o2net_प्रणाली_error syserr, पूर्णांक err)
अणु
	काष्ठा kvec vec = अणु
		.iov_base = hdr,
		.iov_len = माप(काष्ठा o2net_msg),
	पूर्ण;

	BUG_ON(syserr >= O2NET_ERR_MAX);

	/* leave other fields पूर्णांकact from the incoming message, msg_num
	 * in particular */
	hdr->sys_status = cpu_to_be32(syserr);
	hdr->status = cpu_to_be32(err);
	hdr->magic = cpu_to_be16(O2NET_MSG_STATUS_MAGIC);  // twiddle the magic
	hdr->data_len = 0;

	msglog(hdr, "about to send status magic %d\n", err);
	/* hdr has been in host byteorder this whole समय */
	वापस o2net_send_tcp_msg(sock, &vec, 1, माप(काष्ठा o2net_msg));
पूर्ण

/* this वापसs -त्रुटि_सं अगर the header was unknown or too large, etc.
 * after this is called the buffer us reused क्रम the next message */
अटल पूर्णांक o2net_process_message(काष्ठा o2net_sock_container *sc,
				 काष्ठा o2net_msg *hdr)
अणु
	काष्ठा o2net_node *nn = o2net_nn_from_num(sc->sc_node->nd_num);
	पूर्णांक ret = 0, handler_status;
	क्रमागत  o2net_प्रणाली_error syserr;
	काष्ठा o2net_msg_handler *nmh = शून्य;
	व्योम *ret_data = शून्य;

	msglog(hdr, "processing message\n");

	o2net_sc_postpone_idle(sc);

	चयन(be16_to_cpu(hdr->magic)) अणु
		हाल O2NET_MSG_STATUS_MAGIC:
			/* special type क्रम वापसing message status */
			o2net_complete_nsw(nn, शून्य,
					   be32_to_cpu(hdr->msg_num),
					   be32_to_cpu(hdr->sys_status),
					   be32_to_cpu(hdr->status));
			जाओ out;
		हाल O2NET_MSG_KEEP_REQ_MAGIC:
			o2net_sendpage(sc, o2net_keep_resp,
				       माप(*o2net_keep_resp));
			जाओ out;
		हाल O2NET_MSG_KEEP_RESP_MAGIC:
			जाओ out;
		हाल O2NET_MSG_MAGIC:
			अवरोध;
		शेष:
			msglog(hdr, "bad magic\n");
			ret = -EINVAL;
			जाओ out;
	पूर्ण

	/* find a handler क्रम it */
	handler_status = 0;
	nmh = o2net_handler_get(be16_to_cpu(hdr->msg_type),
				be32_to_cpu(hdr->key));
	अगर (!nmh) अणु
		mlog(ML_TCP, "couldn't find handler for type %u key %08x\n",
		     be16_to_cpu(hdr->msg_type), be32_to_cpu(hdr->key));
		syserr = O2NET_ERR_NO_HNDLR;
		जाओ out_respond;
	पूर्ण

	syserr = O2NET_ERR_NONE;

	अगर (be16_to_cpu(hdr->data_len) > nmh->nh_max_len)
		syserr = O2NET_ERR_OVERFLOW;

	अगर (syserr != O2NET_ERR_NONE)
		जाओ out_respond;

	o2net_set_func_start_समय(sc);
	sc->sc_msg_key = be32_to_cpu(hdr->key);
	sc->sc_msg_type = be16_to_cpu(hdr->msg_type);
	handler_status = (nmh->nh_func)(hdr, माप(काष्ठा o2net_msg) +
					     be16_to_cpu(hdr->data_len),
					nmh->nh_func_data, &ret_data);
	o2net_set_func_stop_समय(sc);

	o2net_update_recv_stats(sc);

out_respond:
	/* this destroys the hdr, so करोn't use it after this */
	mutex_lock(&sc->sc_send_lock);
	ret = o2net_send_status_magic(sc->sc_sock, hdr, syserr,
				      handler_status);
	mutex_unlock(&sc->sc_send_lock);
	hdr = शून्य;
	mlog(0, "sending handler status %d, syserr %d returned %d\n",
	     handler_status, syserr, ret);

	अगर (nmh) अणु
		BUG_ON(ret_data != शून्य && nmh->nh_post_func == शून्य);
		अगर (nmh->nh_post_func)
			(nmh->nh_post_func)(handler_status, nmh->nh_func_data,
					    ret_data);
	पूर्ण

out:
	अगर (nmh)
		o2net_handler_put(nmh);
	वापस ret;
पूर्ण

अटल पूर्णांक o2net_check_handshake(काष्ठा o2net_sock_container *sc)
अणु
	काष्ठा o2net_handshake *hand = page_address(sc->sc_page);
	काष्ठा o2net_node *nn = o2net_nn_from_num(sc->sc_node->nd_num);

	अगर (hand->protocol_version != cpu_to_be64(O2NET_PROTOCOL_VERSION)) अणु
		prपूर्णांकk(KERN_NOTICE "o2net: " SC_NODEF_FMT " Advertised net "
		       "protocol version %llu but %llu is required. "
		       "Disconnecting.\n", SC_NODEF_ARGS(sc),
		       (अचिन्हित दीर्घ दीर्घ)be64_to_cpu(hand->protocol_version),
		       O2NET_PROTOCOL_VERSION);

		/* करोn't bother reconnecting अगर its the wrong version. */
		o2net_ensure_shutकरोwn(nn, sc, -ENOTCONN);
		वापस -1;
	पूर्ण

	/*
	 * Ensure समयouts are consistent with other nodes, otherwise
	 * we can end up with one node thinking that the other must be करोwn,
	 * but isn't. This can ultimately cause corruption.
	 */
	अगर (be32_to_cpu(hand->o2net_idle_समयout_ms) !=
				o2net_idle_समयout()) अणु
		prपूर्णांकk(KERN_NOTICE "o2net: " SC_NODEF_FMT " uses a network "
		       "idle timeout of %u ms, but we use %u ms locally. "
		       "Disconnecting.\n", SC_NODEF_ARGS(sc),
		       be32_to_cpu(hand->o2net_idle_समयout_ms),
		       o2net_idle_समयout());
		o2net_ensure_shutकरोwn(nn, sc, -ENOTCONN);
		वापस -1;
	पूर्ण

	अगर (be32_to_cpu(hand->o2net_keepalive_delay_ms) !=
			o2net_keepalive_delay()) अणु
		prपूर्णांकk(KERN_NOTICE "o2net: " SC_NODEF_FMT " uses a keepalive "
		       "delay of %u ms, but we use %u ms locally. "
		       "Disconnecting.\n", SC_NODEF_ARGS(sc),
		       be32_to_cpu(hand->o2net_keepalive_delay_ms),
		       o2net_keepalive_delay());
		o2net_ensure_shutकरोwn(nn, sc, -ENOTCONN);
		वापस -1;
	पूर्ण

	अगर (be32_to_cpu(hand->o2hb_heartbeat_समयout_ms) !=
			O2HB_MAX_WRITE_TIMEOUT_MS) अणु
		prपूर्णांकk(KERN_NOTICE "o2net: " SC_NODEF_FMT " uses a heartbeat "
		       "timeout of %u ms, but we use %u ms locally. "
		       "Disconnecting.\n", SC_NODEF_ARGS(sc),
		       be32_to_cpu(hand->o2hb_heartbeat_समयout_ms),
		       O2HB_MAX_WRITE_TIMEOUT_MS);
		o2net_ensure_shutकरोwn(nn, sc, -ENOTCONN);
		वापस -1;
	पूर्ण

	sc->sc_handshake_ok = 1;

	spin_lock(&nn->nn_lock);
	/* set valid and queue the idle समयrs only अगर it hasn't been
	 * shut करोwn alपढ़ोy */
	अगर (nn->nn_sc == sc) अणु
		o2net_sc_reset_idle_समयr(sc);
		atomic_set(&nn->nn_समयout, 0);
		o2net_set_nn_state(nn, sc, 1, 0);
	पूर्ण
	spin_unlock(&nn->nn_lock);

	/* shअगरt everything up as though it wasn't there */
	sc->sc_page_off -= माप(काष्ठा o2net_handshake);
	अगर (sc->sc_page_off)
		स_हटाओ(hand, hand + 1, sc->sc_page_off);

	वापस 0;
पूर्ण

/* this demuxes the queued rx bytes पूर्णांकo header or payload bits and calls
 * handlers as each full message is पढ़ो off the socket.  it वापसs -error,
 * == 0 eof, or > 0 क्रम progress made.*/
अटल पूर्णांक o2net_advance_rx(काष्ठा o2net_sock_container *sc)
अणु
	काष्ठा o2net_msg *hdr;
	पूर्णांक ret = 0;
	व्योम *data;
	माप_प्रकार datalen;

	sclog(sc, "receiving\n");
	o2net_set_advance_start_समय(sc);

	अगर (unlikely(sc->sc_handshake_ok == 0)) अणु
		अगर(sc->sc_page_off < माप(काष्ठा o2net_handshake)) अणु
			data = page_address(sc->sc_page) + sc->sc_page_off;
			datalen = माप(काष्ठा o2net_handshake) - sc->sc_page_off;
			ret = o2net_recv_tcp_msg(sc->sc_sock, data, datalen);
			अगर (ret > 0)
				sc->sc_page_off += ret;
		पूर्ण

		अगर (sc->sc_page_off == माप(काष्ठा o2net_handshake)) अणु
			o2net_check_handshake(sc);
			अगर (unlikely(sc->sc_handshake_ok == 0))
				ret = -EPROTO;
		पूर्ण
		जाओ out;
	पूर्ण

	/* करो we need more header? */
	अगर (sc->sc_page_off < माप(काष्ठा o2net_msg)) अणु
		data = page_address(sc->sc_page) + sc->sc_page_off;
		datalen = माप(काष्ठा o2net_msg) - sc->sc_page_off;
		ret = o2net_recv_tcp_msg(sc->sc_sock, data, datalen);
		अगर (ret > 0) अणु
			sc->sc_page_off += ret;
			/* only swab incoming here.. we can
			 * only get here once as we cross from
			 * being under to over */
			अगर (sc->sc_page_off == माप(काष्ठा o2net_msg)) अणु
				hdr = page_address(sc->sc_page);
				अगर (be16_to_cpu(hdr->data_len) >
				    O2NET_MAX_PAYLOAD_BYTES)
					ret = -EOVERFLOW;
			पूर्ण
		पूर्ण
		अगर (ret <= 0)
			जाओ out;
	पूर्ण

	अगर (sc->sc_page_off < माप(काष्ठा o2net_msg)) अणु
		/* oof, still करोn't have a header */
		जाओ out;
	पूर्ण

	/* this was swabbed above when we first पढ़ो it */
	hdr = page_address(sc->sc_page);

	msglog(hdr, "at page_off %zu\n", sc->sc_page_off);

	/* करो we need more payload? */
	अगर (sc->sc_page_off - माप(काष्ठा o2net_msg) < be16_to_cpu(hdr->data_len)) अणु
		/* need more payload */
		data = page_address(sc->sc_page) + sc->sc_page_off;
		datalen = (माप(काष्ठा o2net_msg) + be16_to_cpu(hdr->data_len)) -
			  sc->sc_page_off;
		ret = o2net_recv_tcp_msg(sc->sc_sock, data, datalen);
		अगर (ret > 0)
			sc->sc_page_off += ret;
		अगर (ret <= 0)
			जाओ out;
	पूर्ण

	अगर (sc->sc_page_off - माप(काष्ठा o2net_msg) == be16_to_cpu(hdr->data_len)) अणु
		/* we can only get here once, the first समय we पढ़ो
		 * the payload.. so set ret to progress अगर the handler
		 * works out. after calling this the message is toast */
		ret = o2net_process_message(sc, hdr);
		अगर (ret == 0)
			ret = 1;
		sc->sc_page_off = 0;
	पूर्ण

out:
	sclog(sc, "ret = %d\n", ret);
	o2net_set_advance_stop_समय(sc);
	वापस ret;
पूर्ण

/* this work func is triggerd by data पढ़ोy.  it पढ़ोs until it can पढ़ो no
 * more.  it पूर्णांकerprets 0, eof, as fatal.  अगर data_पढ़ोy hits जबतक we're करोing
 * our work the work काष्ठा will be marked and we'll be called again. */
अटल व्योम o2net_rx_until_empty(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा o2net_sock_container *sc =
		container_of(work, काष्ठा o2net_sock_container, sc_rx_work);
	पूर्णांक ret;

	करो अणु
		ret = o2net_advance_rx(sc);
	पूर्ण जबतक (ret > 0);

	अगर (ret <= 0 && ret != -EAGAIN) अणु
		काष्ठा o2net_node *nn = o2net_nn_from_num(sc->sc_node->nd_num);
		sclog(sc, "saw error %d, closing\n", ret);
		/* not permanent so पढ़ो failed handshake can retry */
		o2net_ensure_shutकरोwn(nn, sc, 0);
	पूर्ण

	sc_put(sc);
पूर्ण

अटल व्योम o2net_initialize_handshake(व्योम)
अणु
	o2net_hand->o2hb_heartbeat_समयout_ms = cpu_to_be32(
		O2HB_MAX_WRITE_TIMEOUT_MS);
	o2net_hand->o2net_idle_समयout_ms = cpu_to_be32(o2net_idle_समयout());
	o2net_hand->o2net_keepalive_delay_ms = cpu_to_be32(
		o2net_keepalive_delay());
	o2net_hand->o2net_reconnect_delay_ms = cpu_to_be32(
		o2net_reconnect_delay());
पूर्ण

/* ------------------------------------------------------------ */

/* called when a connect completes and after a sock is accepted.  the
 * rx path will see the response and mark the sc valid */
अटल व्योम o2net_sc_connect_completed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा o2net_sock_container *sc =
		container_of(work, काष्ठा o2net_sock_container,
			     sc_connect_work);

	mlog(ML_MSG, "sc sending handshake with ver %llu id %llx\n",
              (अचिन्हित दीर्घ दीर्घ)O2NET_PROTOCOL_VERSION,
	      (अचिन्हित दीर्घ दीर्घ)be64_to_cpu(o2net_hand->connector_id));

	o2net_initialize_handshake();
	o2net_sendpage(sc, o2net_hand, माप(*o2net_hand));
	sc_put(sc);
पूर्ण

/* this is called as a work_काष्ठा func. */
अटल व्योम o2net_sc_send_keep_req(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा o2net_sock_container *sc =
		container_of(work, काष्ठा o2net_sock_container,
			     sc_keepalive_work.work);

	o2net_sendpage(sc, o2net_keep_req, माप(*o2net_keep_req));
	sc_put(sc);
पूर्ण

/* socket shutकरोwn करोes a del_समयr_sync against this as it tears करोwn.
 * we can't start this timer until we've got to the poपूर्णांक in sc buildup
 * where shutकरोwn is going to be involved */
अटल व्योम o2net_idle_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा o2net_sock_container *sc = from_समयr(sc, t, sc_idle_समयout);
	काष्ठा o2net_node *nn = o2net_nn_from_num(sc->sc_node->nd_num);
#अगर_घोषित CONFIG_DEBUG_FS
	अचिन्हित दीर्घ msecs = kसमय_प्रकारo_ms(kसमय_get()) -
		kसमय_प्रकारo_ms(sc->sc_tv_समयr);
#अन्यथा
	अचिन्हित दीर्घ msecs = o2net_idle_समयout();
#पूर्ण_अगर

	prपूर्णांकk(KERN_NOTICE "o2net: Connection to " SC_NODEF_FMT " has been "
	       "idle for %lu.%lu secs.\n",
	       SC_NODEF_ARGS(sc), msecs / 1000, msecs % 1000);

	/* idle समयrout happen, करोn't shutकरोwn the connection, but
	 * make fence decision. Maybe the connection can recover beक्रमe
	 * the decision is made.
	 */
	atomic_set(&nn->nn_समयout, 1);
	o2quo_conn_err(o2net_num_from_nn(nn));
	queue_delayed_work(o2net_wq, &nn->nn_still_up,
			msecs_to_jअगरfies(O2NET_QUORUM_DELAY_MS));

	o2net_sc_reset_idle_समयr(sc);

पूर्ण

अटल व्योम o2net_sc_reset_idle_समयr(काष्ठा o2net_sock_container *sc)
अणु
	o2net_sc_cancel_delayed_work(sc, &sc->sc_keepalive_work);
	o2net_sc_queue_delayed_work(sc, &sc->sc_keepalive_work,
		      msecs_to_jअगरfies(o2net_keepalive_delay()));
	o2net_set_sock_समयr(sc);
	mod_समयr(&sc->sc_idle_समयout,
	       jअगरfies + msecs_to_jअगरfies(o2net_idle_समयout()));
पूर्ण

अटल व्योम o2net_sc_postpone_idle(काष्ठा o2net_sock_container *sc)
अणु
	काष्ठा o2net_node *nn = o2net_nn_from_num(sc->sc_node->nd_num);

	/* clear fence decision since the connection recover from समयout*/
	अगर (atomic_पढ़ो(&nn->nn_समयout)) अणु
		o2quo_conn_up(o2net_num_from_nn(nn));
		cancel_delayed_work(&nn->nn_still_up);
		atomic_set(&nn->nn_समयout, 0);
	पूर्ण

	/* Only push out an existing समयr */
	अगर (समयr_pending(&sc->sc_idle_समयout))
		o2net_sc_reset_idle_समयr(sc);
पूर्ण

/* this work func is kicked whenever a path sets the nn state which करोesn't
 * have valid set.  This includes seeing hb come up, losing a connection,
 * having a connect attempt fail, etc. This centralizes the logic which decides
 * अगर a connect attempt should be made or अगर we should give up and all future
 * transmit attempts should fail */
अटल व्योम o2net_start_connect(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा o2net_node *nn =
		container_of(work, काष्ठा o2net_node, nn_connect_work.work);
	काष्ठा o2net_sock_container *sc = शून्य;
	काष्ठा o2nm_node *node = शून्य, *mynode = शून्य;
	काष्ठा socket *sock = शून्य;
	काष्ठा sockaddr_in myaddr = अणु0, पूर्ण, remoteaddr = अणु0, पूर्ण;
	पूर्णांक ret = 0, stop;
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक nofs_flag;

	/*
	 * sock_create allocates the sock with GFP_KERNEL. We must
	 * prevent the fileप्रणाली from being reentered by memory reclaim.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	/* अगर we're greater we initiate tx, otherwise we accept */
	अगर (o2nm_this_node() <= o2net_num_from_nn(nn))
		जाओ out;

	/* watch क्रम racing with tearing a node करोwn */
	node = o2nm_get_node_by_num(o2net_num_from_nn(nn));
	अगर (node == शून्य)
		जाओ out;

	mynode = o2nm_get_node_by_num(o2nm_this_node());
	अगर (mynode == शून्य)
		जाओ out;

	spin_lock(&nn->nn_lock);
	/*
	 * see अगर we alपढ़ोy have one pending or have given up.
	 * For nn_समयout, it is set when we बंद the connection
	 * because of the idle समय out. So it means that we have
	 * at least connected to that node successfully once,
	 * now try to connect to it again.
	 */
	समयout = atomic_पढ़ो(&nn->nn_समयout);
	stop = (nn->nn_sc ||
		(nn->nn_persistent_error &&
		(nn->nn_persistent_error != -ENOTCONN || समयout == 0)));
	spin_unlock(&nn->nn_lock);
	अगर (stop)
		जाओ out;

	nn->nn_last_connect_attempt = jअगरfies;

	sc = sc_alloc(node);
	अगर (sc == शून्य) अणु
		mlog(0, "couldn't allocate sc\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = sock_create(PF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	अगर (ret < 0) अणु
		mlog(0, "can't create socket: %d\n", ret);
		जाओ out;
	पूर्ण
	sc->sc_sock = sock; /* मुक्तd by sc_kref_release */

	sock->sk->sk_allocation = GFP_ATOMIC;

	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = mynode->nd_ipv4_address;
	myaddr.sin_port = htons(0); /* any port */

	ret = sock->ops->bind(sock, (काष्ठा sockaddr *)&myaddr,
			      माप(myaddr));
	अगर (ret) अणु
		mlog(ML_ERROR, "bind failed with %d at address %pI4\n",
		     ret, &mynode->nd_ipv4_address);
		जाओ out;
	पूर्ण

	tcp_sock_set_nodelay(sc->sc_sock->sk);
	tcp_sock_set_user_समयout(sock->sk, O2NET_TCP_USER_TIMEOUT);

	o2net_रेजिस्टर_callbacks(sc->sc_sock->sk, sc);

	spin_lock(&nn->nn_lock);
	/* handshake completion will set nn->nn_sc_valid */
	o2net_set_nn_state(nn, sc, 0, 0);
	spin_unlock(&nn->nn_lock);

	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_addr.s_addr = node->nd_ipv4_address;
	remoteaddr.sin_port = node->nd_ipv4_port;

	ret = sc->sc_sock->ops->connect(sc->sc_sock,
					(काष्ठा sockaddr *)&remoteaddr,
					माप(remoteaddr),
					O_NONBLOCK);
	अगर (ret == -EINPROGRESS)
		ret = 0;

out:
	अगर (ret && sc) अणु
		prपूर्णांकk(KERN_NOTICE "o2net: Connect attempt to " SC_NODEF_FMT
		       " failed with errno %d\n", SC_NODEF_ARGS(sc), ret);
		/* 0 err so that another will be queued and attempted
		 * from set_nn_state */
		o2net_ensure_shutकरोwn(nn, sc, 0);
	पूर्ण
	अगर (sc)
		sc_put(sc);
	अगर (node)
		o2nm_node_put(node);
	अगर (mynode)
		o2nm_node_put(mynode);

	meदो_स्मृति_nofs_restore(nofs_flag);
	वापस;
पूर्ण

अटल व्योम o2net_connect_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा o2net_node *nn =
		container_of(work, काष्ठा o2net_node, nn_connect_expired.work);

	spin_lock(&nn->nn_lock);
	अगर (!nn->nn_sc_valid) अणु
		prपूर्णांकk(KERN_NOTICE "o2net: No connection established with "
		       "node %u after %u.%u seconds, check network and"
		       " cluster configuration.\n",
		     o2net_num_from_nn(nn),
		     o2net_idle_समयout() / 1000,
		     o2net_idle_समयout() % 1000);

		o2net_set_nn_state(nn, शून्य, 0, 0);
	पूर्ण
	spin_unlock(&nn->nn_lock);
पूर्ण

अटल व्योम o2net_still_up(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा o2net_node *nn =
		container_of(work, काष्ठा o2net_node, nn_still_up.work);

	o2quo_hb_still_up(o2net_num_from_nn(nn));
पूर्ण

/* ------------------------------------------------------------ */

व्योम o2net_disconnect_node(काष्ठा o2nm_node *node)
अणु
	काष्ठा o2net_node *nn = o2net_nn_from_num(node->nd_num);

	/* करोn't reconnect until it's heartbeating again */
	spin_lock(&nn->nn_lock);
	atomic_set(&nn->nn_समयout, 0);
	o2net_set_nn_state(nn, शून्य, 0, -ENOTCONN);
	spin_unlock(&nn->nn_lock);

	अगर (o2net_wq) अणु
		cancel_delayed_work(&nn->nn_connect_expired);
		cancel_delayed_work(&nn->nn_connect_work);
		cancel_delayed_work(&nn->nn_still_up);
		flush_workqueue(o2net_wq);
	पूर्ण
पूर्ण

अटल व्योम o2net_hb_node_करोwn_cb(काष्ठा o2nm_node *node, पूर्णांक node_num,
				  व्योम *data)
अणु
	o2quo_hb_करोwn(node_num);

	अगर (!node)
		वापस;

	अगर (node_num != o2nm_this_node())
		o2net_disconnect_node(node);

	BUG_ON(atomic_पढ़ो(&o2net_connected_peers) < 0);
पूर्ण

अटल व्योम o2net_hb_node_up_cb(काष्ठा o2nm_node *node, पूर्णांक node_num,
				व्योम *data)
अणु
	काष्ठा o2net_node *nn = o2net_nn_from_num(node_num);

	o2quo_hb_up(node_num);

	BUG_ON(!node);

	/* ensure an immediate connect attempt */
	nn->nn_last_connect_attempt = jअगरfies -
		(msecs_to_jअगरfies(o2net_reconnect_delay()) + 1);

	अगर (node_num != o2nm_this_node()) अणु
		/* believe it or not, accept and node heartbeating testing
		 * can succeed क्रम this node beक्रमe we got here.. so
		 * only use set_nn_state to clear the persistent error
		 * अगर that hasn't alपढ़ोy happened */
		spin_lock(&nn->nn_lock);
		atomic_set(&nn->nn_समयout, 0);
		अगर (nn->nn_persistent_error)
			o2net_set_nn_state(nn, शून्य, 0, 0);
		spin_unlock(&nn->nn_lock);
	पूर्ण
पूर्ण

व्योम o2net_unरेजिस्टर_hb_callbacks(व्योम)
अणु
	o2hb_unरेजिस्टर_callback(शून्य, &o2net_hb_up);
	o2hb_unरेजिस्टर_callback(शून्य, &o2net_hb_करोwn);
पूर्ण

पूर्णांक o2net_रेजिस्टर_hb_callbacks(व्योम)
अणु
	पूर्णांक ret;

	o2hb_setup_callback(&o2net_hb_करोwn, O2HB_NODE_DOWN_CB,
			    o2net_hb_node_करोwn_cb, शून्य, O2NET_HB_PRI);
	o2hb_setup_callback(&o2net_hb_up, O2HB_NODE_UP_CB,
			    o2net_hb_node_up_cb, शून्य, O2NET_HB_PRI);

	ret = o2hb_रेजिस्टर_callback(शून्य, &o2net_hb_up);
	अगर (ret == 0)
		ret = o2hb_रेजिस्टर_callback(शून्य, &o2net_hb_करोwn);

	अगर (ret)
		o2net_unरेजिस्टर_hb_callbacks();

	वापस ret;
पूर्ण

/* ------------------------------------------------------------ */

अटल पूर्णांक o2net_accept_one(काष्ठा socket *sock, पूर्णांक *more)
अणु
	पूर्णांक ret;
	काष्ठा sockaddr_in sin;
	काष्ठा socket *new_sock = शून्य;
	काष्ठा o2nm_node *node = शून्य;
	काष्ठा o2nm_node *local_node = शून्य;
	काष्ठा o2net_sock_container *sc = शून्य;
	काष्ठा o2net_node *nn;
	अचिन्हित पूर्णांक nofs_flag;

	/*
	 * sock_create_lite allocates the sock with GFP_KERNEL. We must
	 * prevent the fileप्रणाली from being reentered by memory reclaim.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();

	BUG_ON(sock == शून्य);
	*more = 0;
	ret = sock_create_lite(sock->sk->sk_family, sock->sk->sk_type,
			       sock->sk->sk_protocol, &new_sock);
	अगर (ret)
		जाओ out;

	new_sock->type = sock->type;
	new_sock->ops = sock->ops;
	ret = sock->ops->accept(sock, new_sock, O_NONBLOCK, false);
	अगर (ret < 0)
		जाओ out;

	*more = 1;
	new_sock->sk->sk_allocation = GFP_ATOMIC;

	tcp_sock_set_nodelay(new_sock->sk);
	tcp_sock_set_user_समयout(new_sock->sk, O2NET_TCP_USER_TIMEOUT);

	ret = new_sock->ops->getname(new_sock, (काष्ठा sockaddr *) &sin, 1);
	अगर (ret < 0)
		जाओ out;

	node = o2nm_get_node_by_ip(sin.sin_addr.s_addr);
	अगर (node == शून्य) अणु
		prपूर्णांकk(KERN_NOTICE "o2net: Attempt to connect from unknown "
		       "node at %pI4:%d\n", &sin.sin_addr.s_addr,
		       ntohs(sin.sin_port));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (o2nm_this_node() >= node->nd_num) अणु
		local_node = o2nm_get_node_by_num(o2nm_this_node());
		अगर (local_node)
			prपूर्णांकk(KERN_NOTICE "o2net: Unexpected connect attempt "
					"seen at node '%s' (%u, %pI4:%d) from "
					"node '%s' (%u, %pI4:%d)\n",
					local_node->nd_name, local_node->nd_num,
					&(local_node->nd_ipv4_address),
					ntohs(local_node->nd_ipv4_port),
					node->nd_name,
					node->nd_num, &sin.sin_addr.s_addr,
					ntohs(sin.sin_port));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* this happens all the समय when the other node sees our heartbeat
	 * and tries to connect beक्रमe we see their heartbeat */
	अगर (!o2hb_check_node_heartbeating_from_callback(node->nd_num)) अणु
		mlog(ML_CONN, "attempt to connect from node '%s' at "
		     "%pI4:%d but it isn't heartbeating\n",
		     node->nd_name, &sin.sin_addr.s_addr,
		     ntohs(sin.sin_port));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	nn = o2net_nn_from_num(node->nd_num);

	spin_lock(&nn->nn_lock);
	अगर (nn->nn_sc)
		ret = -EBUSY;
	अन्यथा
		ret = 0;
	spin_unlock(&nn->nn_lock);
	अगर (ret) अणु
		prपूर्णांकk(KERN_NOTICE "o2net: Attempt to connect from node '%s' "
		       "at %pI4:%d but it already has an open connection\n",
		       node->nd_name, &sin.sin_addr.s_addr,
		       ntohs(sin.sin_port));
		जाओ out;
	पूर्ण

	sc = sc_alloc(node);
	अगर (sc == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	sc->sc_sock = new_sock;
	new_sock = शून्य;

	spin_lock(&nn->nn_lock);
	atomic_set(&nn->nn_समयout, 0);
	o2net_set_nn_state(nn, sc, 0, 0);
	spin_unlock(&nn->nn_lock);

	o2net_रेजिस्टर_callbacks(sc->sc_sock->sk, sc);
	o2net_sc_queue_work(sc, &sc->sc_rx_work);

	o2net_initialize_handshake();
	o2net_sendpage(sc, o2net_hand, माप(*o2net_hand));

out:
	अगर (new_sock)
		sock_release(new_sock);
	अगर (node)
		o2nm_node_put(node);
	अगर (local_node)
		o2nm_node_put(local_node);
	अगर (sc)
		sc_put(sc);

	meदो_स्मृति_nofs_restore(nofs_flag);
	वापस ret;
पूर्ण

/*
 * This function is invoked in response to one or more
 * pending accepts at softIRQ level. We must drain the
 * entire que beक्रमe वापसing.
 */

अटल व्योम o2net_accept_many(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा socket *sock = o2net_listen_sock;
	पूर्णांक	more;

	/*
	 * It is critical to note that due to पूर्णांकerrupt moderation
	 * at the network driver level, we can't assume to get a
	 * softIRQ क्रम every single conn since tcp SYN packets
	 * can arrive back-to-back, and thereक्रमe many pending
	 * accepts may result in just 1 softIRQ. If we terminate
	 * the o2net_accept_one() loop upon seeing an err, what happens
	 * to the rest of the conns in the queue? If no new SYN
	 * arrives क्रम hours, no softIRQ  will be delivered,
	 * and the connections will just sit in the queue.
	 */

	क्रम (;;) अणु
		o2net_accept_one(sock, &more);
		अगर (!more)
			अवरोध;
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम o2net_listen_data_पढ़ोy(काष्ठा sock *sk)
अणु
	व्योम (*पढ़ोy)(काष्ठा sock *sk);

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	पढ़ोy = sk->sk_user_data;
	अगर (पढ़ोy == शून्य) अणु /* check क्रम tearकरोwn race */
		पढ़ोy = sk->sk_data_पढ़ोy;
		जाओ out;
	पूर्ण

	/* This callback may called twice when a new connection
	 * is  being established as a child socket inherits everything
	 * from a parent LISTEN socket, including the data_पढ़ोy cb of
	 * the parent. This leads to a hazard. In o2net_accept_one()
	 * we are still initializing the child socket but have not
	 * changed the inherited data_पढ़ोy callback yet when
	 * data starts arriving.
	 * We aव्योम this hazard by checking the state.
	 * For the listening socket,  the state will be TCP_LISTEN; क्रम the new
	 * socket, will be  TCP_ESTABLISHED. Also, in this हाल,
	 * sk->sk_user_data is not a valid function poपूर्णांकer.
	 */

	अगर (sk->sk_state == TCP_LISTEN) अणु
		queue_work(o2net_wq, &o2net_listen_work);
	पूर्ण अन्यथा अणु
		पढ़ोy = शून्य;
	पूर्ण

out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	अगर (पढ़ोy != शून्य)
		पढ़ोy(sk);
पूर्ण

अटल पूर्णांक o2net_खोलो_listening_sock(__be32 addr, __be16 port)
अणु
	काष्ठा socket *sock = शून्य;
	पूर्णांक ret;
	काष्ठा sockaddr_in sin = अणु
		.sin_family = PF_INET,
		.sin_addr = अणु .s_addr = addr पूर्ण,
		.sin_port = port,
	पूर्ण;

	ret = sock_create(PF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "o2net: Error %d while creating socket\n", ret);
		जाओ out;
	पूर्ण

	sock->sk->sk_allocation = GFP_ATOMIC;

	ग_लिखो_lock_bh(&sock->sk->sk_callback_lock);
	sock->sk->sk_user_data = sock->sk->sk_data_पढ़ोy;
	sock->sk->sk_data_पढ़ोy = o2net_listen_data_पढ़ोy;
	ग_लिखो_unlock_bh(&sock->sk->sk_callback_lock);

	o2net_listen_sock = sock;
	INIT_WORK(&o2net_listen_work, o2net_accept_many);

	sock->sk->sk_reuse = SK_CAN_REUSE;
	ret = sock->ops->bind(sock, (काष्ठा sockaddr *)&sin, माप(sin));
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "o2net: Error %d while binding socket at "
		       "%pI4:%u\n", ret, &addr, ntohs(port)); 
		जाओ out;
	पूर्ण

	ret = sock->ops->listen(sock, 64);
	अगर (ret < 0)
		prपूर्णांकk(KERN_ERR "o2net: Error %d while listening on %pI4:%u\n",
		       ret, &addr, ntohs(port));

out:
	अगर (ret) अणु
		o2net_listen_sock = शून्य;
		अगर (sock)
			sock_release(sock);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * called from node manager when we should bring up our network listening
 * socket.  node manager handles all the serialization to only call this
 * once and to match it with o2net_stop_listening().  note,
 * o2nm_this_node() करोesn't work yet as we're being called जबतक it
 * is being set up.
 */
पूर्णांक o2net_start_listening(काष्ठा o2nm_node *node)
अणु
	पूर्णांक ret = 0;

	BUG_ON(o2net_wq != शून्य);
	BUG_ON(o2net_listen_sock != शून्य);

	mlog(ML_KTHREAD, "starting o2net thread...\n");
	o2net_wq = alloc_ordered_workqueue("o2net", WQ_MEM_RECLAIM);
	अगर (o2net_wq == शून्य) अणु
		mlog(ML_ERROR, "unable to launch o2net thread\n");
		वापस -ENOMEM; /* ? */
	पूर्ण

	ret = o2net_खोलो_listening_sock(node->nd_ipv4_address,
					node->nd_ipv4_port);
	अगर (ret) अणु
		destroy_workqueue(o2net_wq);
		o2net_wq = शून्य;
	पूर्ण अन्यथा
		o2quo_conn_up(node->nd_num);

	वापस ret;
पूर्ण

/* again, o2nm_this_node() करोesn't work here as we're involved in
 * tearing it करोwn */
व्योम o2net_stop_listening(काष्ठा o2nm_node *node)
अणु
	काष्ठा socket *sock = o2net_listen_sock;
	माप_प्रकार i;

	BUG_ON(o2net_wq == शून्य);
	BUG_ON(o2net_listen_sock == शून्य);

	/* stop the listening socket from generating work */
	ग_लिखो_lock_bh(&sock->sk->sk_callback_lock);
	sock->sk->sk_data_पढ़ोy = sock->sk->sk_user_data;
	sock->sk->sk_user_data = शून्य;
	ग_लिखो_unlock_bh(&sock->sk->sk_callback_lock);

	क्रम (i = 0; i < ARRAY_SIZE(o2net_nodes); i++) अणु
		काष्ठा o2nm_node *node = o2nm_get_node_by_num(i);
		अगर (node) अणु
			o2net_disconnect_node(node);
			o2nm_node_put(node);
		पूर्ण
	पूर्ण

	/* finish all work and tear करोwn the work queue */
	mlog(ML_KTHREAD, "waiting for o2net thread to exit....\n");
	destroy_workqueue(o2net_wq);
	o2net_wq = शून्य;

	sock_release(o2net_listen_sock);
	o2net_listen_sock = शून्य;

	o2quo_conn_err(node->nd_num);
पूर्ण

/* ------------------------------------------------------------ */

पूर्णांक o2net_init(व्योम)
अणु
	अचिन्हित दीर्घ i;

	o2quo_init();

	o2net_debugfs_init();

	o2net_hand = kzalloc(माप(काष्ठा o2net_handshake), GFP_KERNEL);
	o2net_keep_req = kzalloc(माप(काष्ठा o2net_msg), GFP_KERNEL);
	o2net_keep_resp = kzalloc(माप(काष्ठा o2net_msg), GFP_KERNEL);
	अगर (!o2net_hand || !o2net_keep_req || !o2net_keep_resp)
		जाओ out;

	o2net_hand->protocol_version = cpu_to_be64(O2NET_PROTOCOL_VERSION);
	o2net_hand->connector_id = cpu_to_be64(1);

	o2net_keep_req->magic = cpu_to_be16(O2NET_MSG_KEEP_REQ_MAGIC);
	o2net_keep_resp->magic = cpu_to_be16(O2NET_MSG_KEEP_RESP_MAGIC);

	क्रम (i = 0; i < ARRAY_SIZE(o2net_nodes); i++) अणु
		काष्ठा o2net_node *nn = o2net_nn_from_num(i);

		atomic_set(&nn->nn_समयout, 0);
		spin_lock_init(&nn->nn_lock);
		INIT_DELAYED_WORK(&nn->nn_connect_work, o2net_start_connect);
		INIT_DELAYED_WORK(&nn->nn_connect_expired,
				  o2net_connect_expired);
		INIT_DELAYED_WORK(&nn->nn_still_up, o2net_still_up);
		/* until we see hb from a node we'll वापस einval */
		nn->nn_persistent_error = -ENOTCONN;
		init_रुकोqueue_head(&nn->nn_sc_wq);
		idr_init(&nn->nn_status_idr);
		INIT_LIST_HEAD(&nn->nn_status_list);
	पूर्ण

	वापस 0;

out:
	kमुक्त(o2net_hand);
	kमुक्त(o2net_keep_req);
	kमुक्त(o2net_keep_resp);
	o2net_debugfs_निकास();
	o2quo_निकास();
	वापस -ENOMEM;
पूर्ण

व्योम o2net_निकास(व्योम)
अणु
	o2quo_निकास();
	kमुक्त(o2net_hand);
	kमुक्त(o2net_keep_req);
	kमुक्त(o2net_keep_resp);
	o2net_debugfs_निकास();
पूर्ण
