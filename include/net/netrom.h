<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Declarations of NET/ROM type objects.
 *
 *	Jonathan Naylor G4KLX	9/4/95
 */

#अगर_अघोषित _NETROM_H
#घोषणा _NETROM_H 

#समावेश <linux/netrom.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/refcount.h>
#समावेश <linux/seq_file.h>

#घोषणा	NR_NETWORK_LEN			15
#घोषणा	NR_TRANSPORT_LEN		5

#घोषणा	NR_PROTO_IP			0x0C

#घोषणा	NR_PROTOEXT			0x00
#घोषणा	NR_CONNREQ			0x01
#घोषणा	NR_CONNACK			0x02
#घोषणा	NR_DISCREQ			0x03
#घोषणा	NR_DISCACK			0x04
#घोषणा	NR_INFO				0x05
#घोषणा	NR_INFOACK			0x06
#घोषणा	NR_RESET			0x07

#घोषणा	NR_CHOKE_FLAG			0x80
#घोषणा	NR_NAK_FLAG			0x40
#घोषणा	NR_MORE_FLAG			0x20

/* Define Link State स्थिरants. */
क्रमागत अणु
	NR_STATE_0,
	NR_STATE_1,
	NR_STATE_2,
	NR_STATE_3
पूर्ण;

#घोषणा	NR_COND_ACK_PENDING		0x01
#घोषणा	NR_COND_REJECT			0x02
#घोषणा	NR_COND_PEER_RX_BUSY		0x04
#घोषणा	NR_COND_OWN_RX_BUSY		0x08

#घोषणा NR_DEFAULT_T1			120000		/* Outstanding frames - 120 seconds */
#घोषणा NR_DEFAULT_T2			5000		/* Response delay     - 5 seconds */
#घोषणा NR_DEFAULT_N2			3		/* Number of Retries - 3 */
#घोषणा	NR_DEFAULT_T4			180000		/* Busy Delay - 180 seconds */
#घोषणा	NR_DEFAULT_IDLE			0		/* No Activity Timeout - none */
#घोषणा	NR_DEFAULT_WINDOW		4		/* Default Winकरोw Size - 4 */
#घोषणा	NR_DEFAULT_OBS			6		/* Default Obsolescence Count - 6 */
#घोषणा	NR_DEFAULT_QUAL			10		/* Default Neighbour Quality - 10 */
#घोषणा	NR_DEFAULT_TTL			16		/* Default Time To Live - 16 */
#घोषणा	NR_DEFAULT_ROUTING		1		/* Is routing enabled ? */
#घोषणा	NR_DEFAULT_FAILS		2		/* Link fails until route fails */
#घोषणा	NR_DEFAULT_RESET		0		/* Sent / accept reset cmds? */

#घोषणा NR_MODULUS 			256
#घोषणा NR_MAX_WINDOW_SIZE		127			/* Maximum Winकरोw Allowable - 127 */
#घोषणा	NR_MAX_PACKET_SIZE		236			/* Maximum Packet Length - 236 */

काष्ठा nr_sock अणु
	काष्ठा sock		sock;
	ax25_address		user_addr, source_addr, dest_addr;
	काष्ठा net_device		*device;
	अचिन्हित अक्षर		my_index,   my_id;
	अचिन्हित अक्षर		your_index, your_id;
	अचिन्हित अक्षर		state, condition, bpqext, winकरोw;
	अचिन्हित लघु		vs, vr, va, vl;
	अचिन्हित अक्षर		n2, n2count;
	अचिन्हित दीर्घ		t1, t2, t4, idle;
	अचिन्हित लघु		fraglen;
	काष्ठा समयr_list	t1समयr;
	काष्ठा समयr_list	t2समयr;
	काष्ठा समयr_list	t4समयr;
	काष्ठा समयr_list	idleसमयr;
	काष्ठा sk_buff_head	ack_queue;
	काष्ठा sk_buff_head	reseq_queue;
	काष्ठा sk_buff_head	frag_queue;
पूर्ण;

#घोषणा nr_sk(sk) ((काष्ठा nr_sock *)(sk))

काष्ठा nr_neigh अणु
	काष्ठा hlist_node	neigh_node;
	ax25_address		callsign;
	ax25_digi		*digipeat;
	ax25_cb			*ax25;
	काष्ठा net_device	*dev;
	अचिन्हित अक्षर		quality;
	अचिन्हित अक्षर		locked;
	अचिन्हित लघु		count;
	अचिन्हित पूर्णांक		number;
	अचिन्हित अक्षर		failed;
	refcount_t		refcount;
पूर्ण;

काष्ठा nr_route अणु
	अचिन्हित अक्षर   quality;
	अचिन्हित अक्षर   obs_count;
	काष्ठा nr_neigh *neighbour;
पूर्ण;

काष्ठा nr_node अणु
	काष्ठा hlist_node	node_node;
	ax25_address		callsign;
	अक्षर			mnemonic[7];
	अचिन्हित अक्षर		which;
	अचिन्हित अक्षर		count;
	काष्ठा nr_route		routes[3];
	refcount_t		refcount;
	spinlock_t		node_lock;
पूर्ण;

/*********************************************************************
 *	nr_node & nr_neigh lists, refcounting and locking
 *********************************************************************/

#घोषणा nr_node_hold(__nr_node) \
	refcount_inc(&((__nr_node)->refcount))

अटल __अंतरभूत__ व्योम nr_node_put(काष्ठा nr_node *nr_node)
अणु
	अगर (refcount_dec_and_test(&nr_node->refcount)) अणु
		kमुक्त(nr_node);
	पूर्ण
पूर्ण

#घोषणा nr_neigh_hold(__nr_neigh) \
	refcount_inc(&((__nr_neigh)->refcount))

अटल __अंतरभूत__ व्योम nr_neigh_put(काष्ठा nr_neigh *nr_neigh)
अणु
	अगर (refcount_dec_and_test(&nr_neigh->refcount)) अणु
		अगर (nr_neigh->ax25)
			ax25_cb_put(nr_neigh->ax25);
		kमुक्त(nr_neigh->digipeat);
		kमुक्त(nr_neigh);
	पूर्ण
पूर्ण

/* nr_node_lock and nr_node_unlock also hold/put the node's refcounter.
 */
अटल __अंतरभूत__ व्योम nr_node_lock(काष्ठा nr_node *nr_node)
अणु
	nr_node_hold(nr_node);
	spin_lock_bh(&nr_node->node_lock);
पूर्ण

अटल __अंतरभूत__ व्योम nr_node_unlock(काष्ठा nr_node *nr_node)
अणु
	spin_unlock_bh(&nr_node->node_lock);
	nr_node_put(nr_node);
पूर्ण

#घोषणा nr_neigh_क्रम_each(__nr_neigh, list) \
	hlist_क्रम_each_entry(__nr_neigh, list, neigh_node)

#घोषणा nr_neigh_क्रम_each_safe(__nr_neigh, node2, list) \
	hlist_क्रम_each_entry_safe(__nr_neigh, node2, list, neigh_node)

#घोषणा nr_node_क्रम_each(__nr_node, list) \
	hlist_क्रम_each_entry(__nr_node, list, node_node)

#घोषणा nr_node_क्रम_each_safe(__nr_node, node2, list) \
	hlist_क्रम_each_entry_safe(__nr_node, node2, list, node_node)


/*********************************************************************/

/* af_netrom.c */
बाह्य पूर्णांक  sysctl_netrom_शेष_path_quality;
बाह्य पूर्णांक  sysctl_netrom_obsolescence_count_initialiser;
बाह्य पूर्णांक  sysctl_netrom_network_ttl_initialiser;
बाह्य पूर्णांक  sysctl_netrom_transport_समयout;
बाह्य पूर्णांक  sysctl_netrom_transport_maximum_tries;
बाह्य पूर्णांक  sysctl_netrom_transport_acknowledge_delay;
बाह्य पूर्णांक  sysctl_netrom_transport_busy_delay;
बाह्य पूर्णांक  sysctl_netrom_transport_requested_winकरोw_size;
बाह्य पूर्णांक  sysctl_netrom_transport_no_activity_समयout;
बाह्य पूर्णांक  sysctl_netrom_routing_control;
बाह्य पूर्णांक  sysctl_netrom_link_fails_count;
बाह्य पूर्णांक  sysctl_netrom_reset_circuit;

पूर्णांक nr_rx_frame(काष्ठा sk_buff *, काष्ठा net_device *);
व्योम nr_destroy_socket(काष्ठा sock *);

/* nr_dev.c */
पूर्णांक nr_rx_ip(काष्ठा sk_buff *, काष्ठा net_device *);
व्योम nr_setup(काष्ठा net_device *);

/* nr_in.c */
पूर्णांक nr_process_rx_frame(काष्ठा sock *, काष्ठा sk_buff *);

/* nr_loopback.c */
व्योम nr_loopback_init(व्योम);
व्योम nr_loopback_clear(व्योम);
पूर्णांक nr_loopback_queue(काष्ठा sk_buff *);

/* nr_out.c */
व्योम nr_output(काष्ठा sock *, काष्ठा sk_buff *);
व्योम nr_send_nak_frame(काष्ठा sock *);
व्योम nr_kick(काष्ठा sock *);
व्योम nr_transmit_buffer(काष्ठा sock *, काष्ठा sk_buff *);
व्योम nr_establish_data_link(काष्ठा sock *);
व्योम nr_enquiry_response(काष्ठा sock *);
व्योम nr_check_अगरrames_acked(काष्ठा sock *, अचिन्हित लघु);

/* nr_route.c */
व्योम nr_rt_device_करोwn(काष्ठा net_device *);
काष्ठा net_device *nr_dev_first(व्योम);
काष्ठा net_device *nr_dev_get(ax25_address *);
पूर्णांक nr_rt_ioctl(अचिन्हित पूर्णांक, व्योम __user *);
व्योम nr_link_failed(ax25_cb *, पूर्णांक);
पूर्णांक nr_route_frame(काष्ठा sk_buff *, ax25_cb *);
बाह्य स्थिर काष्ठा seq_operations nr_node_seqops;
बाह्य स्थिर काष्ठा seq_operations nr_neigh_seqops;
व्योम nr_rt_मुक्त(व्योम);

/* nr_subr.c */
व्योम nr_clear_queues(काष्ठा sock *);
व्योम nr_frames_acked(काष्ठा sock *, अचिन्हित लघु);
व्योम nr_requeue_frames(काष्ठा sock *);
पूर्णांक nr_validate_nr(काष्ठा sock *, अचिन्हित लघु);
पूर्णांक nr_in_rx_winकरोw(काष्ठा sock *, अचिन्हित लघु);
व्योम nr_ग_लिखो_पूर्णांकernal(काष्ठा sock *, पूर्णांक);

व्योम __nr_transmit_reply(काष्ठा sk_buff *skb, पूर्णांक mine, अचिन्हित अक्षर cmdflags);

/*
 * This routine is called when a Connect Acknowledge with the Choke Flag
 * set is needed to refuse a connection.
 */
#घोषणा nr_transmit_refusal(skb, mine)					\
करो अणु									\
	__nr_transmit_reply((skb), (mine), NR_CONNACK | NR_CHOKE_FLAG);	\
पूर्ण जबतक (0)

/*
 * This routine is called when we करोn't have a circuit matching an incoming
 * NET/ROM packet.  This is an G8PZT Xrouter extension.
 */
#घोषणा nr_transmit_reset(skb, mine)					\
करो अणु									\
	__nr_transmit_reply((skb), (mine), NR_RESET);			\
पूर्ण जबतक (0)

व्योम nr_disconnect(काष्ठा sock *, पूर्णांक);

/* nr_समयr.c */
व्योम nr_init_समयrs(काष्ठा sock *sk);
व्योम nr_start_heartbeat(काष्ठा sock *);
व्योम nr_start_t1समयr(काष्ठा sock *);
व्योम nr_start_t2समयr(काष्ठा sock *);
व्योम nr_start_t4समयr(काष्ठा sock *);
व्योम nr_start_idleसमयr(काष्ठा sock *);
व्योम nr_stop_heartbeat(काष्ठा sock *);
व्योम nr_stop_t1समयr(काष्ठा sock *);
व्योम nr_stop_t2समयr(काष्ठा sock *);
व्योम nr_stop_t4समयr(काष्ठा sock *);
व्योम nr_stop_idleसमयr(काष्ठा sock *);
पूर्णांक nr_t1समयr_running(काष्ठा sock *);

/* sysctl_net_netrom.c */
पूर्णांक nr_रेजिस्टर_sysctl(व्योम);
व्योम nr_unरेजिस्टर_sysctl(व्योम);

#पूर्ण_अगर
