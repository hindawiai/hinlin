<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Declarations of X.25 Packet Layer type objects.
 *
 * 	History
 *	nov/17/96	Jonathan Naylor	  Initial version.		
 *	mar/20/00	Daniela Squassoni Disabling/enabling of facilities 
 *					  negotiation.
 */

#अगर_अघोषित _X25_H
#घोषणा _X25_H 
#समावेश <linux/x25.h>
#समावेश <linux/slab.h>
#समावेश <linux/refcount.h>
#समावेश <net/sock.h>

#घोषणा	X25_ADDR_LEN			16

#घोषणा	X25_MAX_L2_LEN			18	/* 802.2 LLC */

#घोषणा	X25_STD_MIN_LEN			3
#घोषणा	X25_EXT_MIN_LEN			4

#घोषणा	X25_GFI_SEQ_MASK		0x30
#घोषणा	X25_GFI_STDSEQ			0x10
#घोषणा	X25_GFI_EXTSEQ			0x20

#घोषणा	X25_Q_BIT			0x80
#घोषणा	X25_D_BIT			0x40
#घोषणा	X25_STD_M_BIT			0x10
#घोषणा	X25_EXT_M_BIT			0x01

#घोषणा	X25_CALL_REQUEST		0x0B
#घोषणा	X25_CALL_ACCEPTED		0x0F
#घोषणा	X25_CLEAR_REQUEST		0x13
#घोषणा	X25_CLEAR_CONFIRMATION		0x17
#घोषणा	X25_DATA			0x00
#घोषणा	X25_INTERRUPT			0x23
#घोषणा	X25_INTERRUPT_CONFIRMATION	0x27
#घोषणा	X25_RR				0x01
#घोषणा	X25_RNR				0x05
#घोषणा	X25_REJ				0x09
#घोषणा	X25_RESET_REQUEST		0x1B
#घोषणा	X25_RESET_CONFIRMATION		0x1F
#घोषणा	X25_REGISTRATION_REQUEST	0xF3
#घोषणा	X25_REGISTRATION_CONFIRMATION	0xF7
#घोषणा	X25_RESTART_REQUEST		0xFB
#घोषणा	X25_RESTART_CONFIRMATION	0xFF
#घोषणा	X25_DIAGNOSTIC			0xF1
#घोषणा	X25_ILLEGAL			0xFD

/* Define the various conditions that may exist */

#घोषणा	X25_COND_ACK_PENDING	0x01
#घोषणा	X25_COND_OWN_RX_BUSY	0x02
#घोषणा	X25_COND_PEER_RX_BUSY	0x04

/* Define Link State स्थिरants. */
क्रमागत अणु
	X25_STATE_0,		/* Ready */
	X25_STATE_1,		/* Aरुकोing Call Accepted */
	X25_STATE_2,		/* Aरुकोing Clear Confirmation */
	X25_STATE_3,		/* Data Transfer */
	X25_STATE_4,		/* Aरुकोing Reset Confirmation */
	X25_STATE_5		/* Call Accepted / Call Connected pending */
पूर्ण;

क्रमागत अणु
	X25_LINK_STATE_0,
	X25_LINK_STATE_1,
	X25_LINK_STATE_2,
	X25_LINK_STATE_3
पूर्ण;

#घोषणा X25_DEFAULT_T20		(180 * HZ)		/* Default T20 value */
#घोषणा X25_DEFAULT_T21		(200 * HZ)		/* Default T21 value */
#घोषणा X25_DEFAULT_T22		(180 * HZ)		/* Default T22 value */
#घोषणा	X25_DEFAULT_T23		(180 * HZ)		/* Default T23 value */
#घोषणा	X25_DEFAULT_T2		(3   * HZ)		/* Default ack holdback value */

#घोषणा	X25_DEFAULT_WINDOW_SIZE	2			/* Default Winकरोw Size	*/
#घोषणा	X25_DEFAULT_PACKET_SIZE	X25_PS128		/* Default Packet Size */
#घोषणा	X25_DEFAULT_THROUGHPUT	0x0A			/* Deafult Throughput */
#घोषणा	X25_DEFAULT_REVERSE	0x00			/* Default Reverse Charging */

#घोषणा X25_SMODULUS 		8
#घोषणा	X25_EMODULUS		128

/*
 *	X.25 Facilities स्थिरants.
 */

#घोषणा	X25_FAC_CLASS_MASK	0xC0

#घोषणा	X25_FAC_CLASS_A		0x00
#घोषणा	X25_FAC_CLASS_B		0x40
#घोषणा	X25_FAC_CLASS_C		0x80
#घोषणा	X25_FAC_CLASS_D		0xC0

#घोषणा	X25_FAC_REVERSE		0x01			/* also fast select */
#घोषणा	X25_FAC_THROUGHPUT	0x02
#घोषणा	X25_FAC_PACKET_SIZE	0x42
#घोषणा	X25_FAC_WINDOW_SIZE	0x43

#घोषणा X25_MAX_FAC_LEN 	60
#घोषणा	X25_MAX_CUD_LEN		128

#घोषणा X25_FAC_CALLING_AE 	0xCB
#घोषणा X25_FAC_CALLED_AE 	0xC9

#घोषणा X25_MARKER 		0x00
#घोषणा X25_DTE_SERVICES 	0x0F
#घोषणा X25_MAX_AE_LEN 		40			/* Max num of semi-octets in AE - OSI Nw */
#घोषणा X25_MAX_DTE_FACIL_LEN	21			/* Max length of DTE facility params */

/* Bitset in x25_sock->flags क्रम misc flags */
#घोषणा X25_Q_BIT_FLAG		0
#घोषणा X25_INTERRUPT_FLAG	1
#घोषणा X25_ACCPT_APPRV_FLAG	2

/**
 *	काष्ठा x25_route - x25 routing entry
 *	@node - entry in x25_list_lock
 *	@address - Start of address range
 *	@sigdigits - Number of sig digits
 *	@dev - More than one क्रम MLP
 *	@refcnt - reference counter
 */
काष्ठा x25_route अणु
	काष्ठा list_head	node;		
	काष्ठा x25_address	address;
	अचिन्हित पूर्णांक		sigdigits;
	काष्ठा net_device	*dev;
	refcount_t		refcnt;
पूर्ण;

काष्ठा x25_neigh अणु
	काष्ठा list_head	node;
	काष्ठा net_device	*dev;
	अचिन्हित पूर्णांक		state;
	अचिन्हित पूर्णांक		extended;
	काष्ठा sk_buff_head	queue;
	अचिन्हित दीर्घ		t20;
	काष्ठा समयr_list	t20समयr;
	अचिन्हित दीर्घ		global_facil_mask;
	refcount_t		refcnt;
पूर्ण;

काष्ठा x25_sock अणु
	काष्ठा sock		sk;
	काष्ठा x25_address	source_addr, dest_addr;
	काष्ठा x25_neigh	*neighbour;
	अचिन्हित पूर्णांक		lci, cudmatchlength;
	अचिन्हित अक्षर		state, condition;
	अचिन्हित लघु		vs, vr, va, vl;
	अचिन्हित दीर्घ		t2, t21, t22, t23;
	अचिन्हित लघु		fraglen;
	अचिन्हित दीर्घ		flags;
	काष्ठा sk_buff_head	ack_queue;
	काष्ठा sk_buff_head	fragment_queue;
	काष्ठा sk_buff_head	पूर्णांकerrupt_in_queue;
	काष्ठा sk_buff_head	पूर्णांकerrupt_out_queue;
	काष्ठा समयr_list	समयr;
	काष्ठा x25_causediag	causediag;
	काष्ठा x25_facilities	facilities;
	काष्ठा x25_dte_facilities dte_facilities;
	काष्ठा x25_calluserdata	calluserdata;
	अचिन्हित दीर्घ 		vc_facil_mask;	/* inc_call facilities mask */
पूर्ण;

काष्ठा x25_क्रमward अणु
	काष्ठा list_head	node;
	अचिन्हित पूर्णांक		lci;
	काष्ठा net_device	*dev1;
	काष्ठा net_device	*dev2;
	atomic_t		refcnt;
पूर्ण;

अटल अंतरभूत काष्ठा x25_sock *x25_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा x25_sock *)sk;
पूर्ण

/* af_x25.c */
बाह्य पूर्णांक  sysctl_x25_restart_request_समयout;
बाह्य पूर्णांक  sysctl_x25_call_request_समयout;
बाह्य पूर्णांक  sysctl_x25_reset_request_समयout;
बाह्य पूर्णांक  sysctl_x25_clear_request_समयout;
बाह्य पूर्णांक  sysctl_x25_ack_holdback_समयout;
बाह्य पूर्णांक  sysctl_x25_क्रमward;

पूर्णांक x25_parse_address_block(काष्ठा sk_buff *skb,
			    काष्ठा x25_address *called_addr,
			    काष्ठा x25_address *calling_addr);

पूर्णांक x25_addr_ntoa(अचिन्हित अक्षर *, काष्ठा x25_address *, काष्ठा x25_address *);
पूर्णांक x25_addr_aton(अचिन्हित अक्षर *, काष्ठा x25_address *, काष्ठा x25_address *);
काष्ठा sock *x25_find_socket(अचिन्हित पूर्णांक, काष्ठा x25_neigh *);
व्योम x25_destroy_socket_from_समयr(काष्ठा sock *);
पूर्णांक x25_rx_call_request(काष्ठा sk_buff *, काष्ठा x25_neigh *, अचिन्हित पूर्णांक);
व्योम x25_समाप्त_by_neigh(काष्ठा x25_neigh *);

/* x25_dev.c */
व्योम x25_send_frame(काष्ठा sk_buff *, काष्ठा x25_neigh *);
पूर्णांक x25_lapb_receive_frame(काष्ठा sk_buff *, काष्ठा net_device *,
			   काष्ठा packet_type *, काष्ठा net_device *);
व्योम x25_establish_link(काष्ठा x25_neigh *);
व्योम x25_terminate_link(काष्ठा x25_neigh *);

/* x25_facilities.c */
पूर्णांक x25_parse_facilities(काष्ठा sk_buff *, काष्ठा x25_facilities *,
			 काष्ठा x25_dte_facilities *, अचिन्हित दीर्घ *);
पूर्णांक x25_create_facilities(अचिन्हित अक्षर *, काष्ठा x25_facilities *,
			  काष्ठा x25_dte_facilities *, अचिन्हित दीर्घ);
पूर्णांक x25_negotiate_facilities(काष्ठा sk_buff *, काष्ठा sock *,
			     काष्ठा x25_facilities *,
			     काष्ठा x25_dte_facilities *);
व्योम x25_limit_facilities(काष्ठा x25_facilities *, काष्ठा x25_neigh *);

/* x25_क्रमward.c */
व्योम x25_clear_क्रमward_by_lci(अचिन्हित पूर्णांक lci);
व्योम x25_clear_क्रमward_by_dev(काष्ठा net_device *);
पूर्णांक x25_क्रमward_data(पूर्णांक, काष्ठा x25_neigh *, काष्ठा sk_buff *);
पूर्णांक x25_क्रमward_call(काष्ठा x25_address *, काष्ठा x25_neigh *, काष्ठा sk_buff *,
		     पूर्णांक);

/* x25_in.c */
पूर्णांक x25_process_rx_frame(काष्ठा sock *, काष्ठा sk_buff *);
पूर्णांक x25_backlog_rcv(काष्ठा sock *, काष्ठा sk_buff *);

/* x25_link.c */
व्योम x25_link_control(काष्ठा sk_buff *, काष्ठा x25_neigh *, अचिन्हित लघु);
व्योम x25_link_device_up(काष्ठा net_device *);
व्योम x25_link_device_करोwn(काष्ठा net_device *);
व्योम x25_link_established(काष्ठा x25_neigh *);
व्योम x25_link_terminated(काष्ठा x25_neigh *);
व्योम x25_transmit_clear_request(काष्ठा x25_neigh *, अचिन्हित पूर्णांक,
				अचिन्हित अक्षर);
व्योम x25_transmit_link(काष्ठा sk_buff *, काष्ठा x25_neigh *);
पूर्णांक x25_subscr_ioctl(अचिन्हित पूर्णांक, व्योम __user *);
काष्ठा x25_neigh *x25_get_neigh(काष्ठा net_device *);
व्योम x25_link_मुक्त(व्योम);

/* x25_neigh.c */
अटल __अंतरभूत__ व्योम x25_neigh_hold(काष्ठा x25_neigh *nb)
अणु
	refcount_inc(&nb->refcnt);
पूर्ण

अटल __अंतरभूत__ व्योम x25_neigh_put(काष्ठा x25_neigh *nb)
अणु
	अगर (refcount_dec_and_test(&nb->refcnt))
		kमुक्त(nb);
पूर्ण

/* x25_out.c */
पूर्णांक x25_output(काष्ठा sock *, काष्ठा sk_buff *);
व्योम x25_kick(काष्ठा sock *);
व्योम x25_enquiry_response(काष्ठा sock *);

/* x25_route.c */
काष्ठा x25_route *x25_get_route(काष्ठा x25_address *addr);
काष्ठा net_device *x25_dev_get(अक्षर *);
व्योम x25_route_device_करोwn(काष्ठा net_device *dev);
पूर्णांक x25_route_ioctl(अचिन्हित पूर्णांक, व्योम __user *);
व्योम x25_route_मुक्त(व्योम);

अटल __अंतरभूत__ व्योम x25_route_hold(काष्ठा x25_route *rt)
अणु
	refcount_inc(&rt->refcnt);
पूर्ण

अटल __अंतरभूत__ व्योम x25_route_put(काष्ठा x25_route *rt)
अणु
	अगर (refcount_dec_and_test(&rt->refcnt))
		kमुक्त(rt);
पूर्ण

/* x25_subr.c */
व्योम x25_clear_queues(काष्ठा sock *);
व्योम x25_frames_acked(काष्ठा sock *, अचिन्हित लघु);
व्योम x25_requeue_frames(काष्ठा sock *);
पूर्णांक x25_validate_nr(काष्ठा sock *, अचिन्हित लघु);
व्योम x25_ग_लिखो_पूर्णांकernal(काष्ठा sock *, पूर्णांक);
पूर्णांक x25_decode(काष्ठा sock *, काष्ठा sk_buff *, पूर्णांक *, पूर्णांक *, पूर्णांक *, पूर्णांक *,
	       पूर्णांक *);
व्योम x25_disconnect(काष्ठा sock *, पूर्णांक, अचिन्हित अक्षर, अचिन्हित अक्षर);

/* x25_समयr.c */
व्योम x25_init_समयrs(काष्ठा sock *sk);
व्योम x25_start_heartbeat(काष्ठा sock *);
व्योम x25_start_t2समयr(काष्ठा sock *);
व्योम x25_start_t21समयr(काष्ठा sock *);
व्योम x25_start_t22समयr(काष्ठा sock *);
व्योम x25_start_t23समयr(काष्ठा sock *);
व्योम x25_stop_heartbeat(काष्ठा sock *);
व्योम x25_stop_समयr(काष्ठा sock *);
अचिन्हित दीर्घ x25_display_समयr(काष्ठा sock *);
व्योम x25_check_rbuf(काष्ठा sock *);

/* sysctl_net_x25.c */
#अगर_घोषित CONFIG_SYSCTL
पूर्णांक x25_रेजिस्टर_sysctl(व्योम);
व्योम x25_unरेजिस्टर_sysctl(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक x25_रेजिस्टर_sysctl(व्योम) अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम x25_unरेजिस्टर_sysctl(व्योम) अणुपूर्ण;
#पूर्ण_अगर /* CONFIG_SYSCTL */

काष्ठा x25_skb_cb अणु
	अचिन्हित पूर्णांक flags;
पूर्ण;
#घोषणा X25_SKB_CB(s) ((काष्ठा x25_skb_cb *) ((s)->cb))

बाह्य काष्ठा hlist_head x25_list;
बाह्य rwlock_t x25_list_lock;
बाह्य काष्ठा list_head x25_route_list;
बाह्य rwlock_t x25_route_list_lock;
बाह्य काष्ठा list_head x25_क्रमward_list;
बाह्य rwlock_t x25_क्रमward_list_lock;
बाह्य काष्ठा list_head x25_neigh_list;
बाह्य rwlock_t x25_neigh_list_lock;

पूर्णांक x25_proc_init(व्योम);
व्योम x25_proc_निकास(व्योम);
#पूर्ण_अगर
