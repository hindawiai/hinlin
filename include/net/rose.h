<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Declarations of Rose type objects.
 *
 *	Jonathan Naylor G4KLX	25/8/96
 */

#अगर_अघोषित _ROSE_H
#घोषणा _ROSE_H 

#समावेश <linux/rose.h>
#समावेश <net/sock.h>

#घोषणा	ROSE_ADDR_LEN			5

#घोषणा	ROSE_MIN_LEN			3

#घोषणा	ROSE_CALL_REQ_ADDR_LEN_OFF	3
#घोषणा	ROSE_CALL_REQ_ADDR_LEN_VAL	0xAA	/* each address is 10 digits */
#घोषणा	ROSE_CALL_REQ_DEST_ADDR_OFF	4
#घोषणा	ROSE_CALL_REQ_SRC_ADDR_OFF	9
#घोषणा	ROSE_CALL_REQ_FACILITIES_OFF	14

#घोषणा	ROSE_GFI			0x10
#घोषणा	ROSE_Q_BIT			0x80
#घोषणा	ROSE_D_BIT			0x40
#घोषणा	ROSE_M_BIT			0x10

#घोषणा	ROSE_CALL_REQUEST		0x0B
#घोषणा	ROSE_CALL_ACCEPTED		0x0F
#घोषणा	ROSE_CLEAR_REQUEST		0x13
#घोषणा	ROSE_CLEAR_CONFIRMATION		0x17
#घोषणा	ROSE_DATA			0x00
#घोषणा	ROSE_INTERRUPT			0x23
#घोषणा	ROSE_INTERRUPT_CONFIRMATION	0x27
#घोषणा	ROSE_RR				0x01
#घोषणा	ROSE_RNR			0x05
#घोषणा	ROSE_REJ			0x09
#घोषणा	ROSE_RESET_REQUEST		0x1B
#घोषणा	ROSE_RESET_CONFIRMATION		0x1F
#घोषणा	ROSE_REGISTRATION_REQUEST	0xF3
#घोषणा	ROSE_REGISTRATION_CONFIRMATION	0xF7
#घोषणा	ROSE_RESTART_REQUEST		0xFB
#घोषणा	ROSE_RESTART_CONFIRMATION	0xFF
#घोषणा	ROSE_DIAGNOSTIC			0xF1
#घोषणा	ROSE_ILLEGAL			0xFD

/* Define Link State स्थिरants. */

क्रमागत अणु
	ROSE_STATE_0,			/* Ready */
	ROSE_STATE_1,			/* Aरुकोing Call Accepted */
	ROSE_STATE_2,			/* Aरुकोing Clear Confirmation */
	ROSE_STATE_3,			/* Data Transfer */
	ROSE_STATE_4,			/* Aरुकोing Reset Confirmation */
	ROSE_STATE_5			/* Deferred Call Acceptance */
पूर्ण;

#घोषणा ROSE_DEFAULT_T0			180000		/* Default T10 T20 value */
#घोषणा ROSE_DEFAULT_T1			200000		/* Default T11 T21 value */
#घोषणा ROSE_DEFAULT_T2			180000		/* Default T12 T22 value */
#घोषणा	ROSE_DEFAULT_T3			180000		/* Default T13 T23 value */
#घोषणा	ROSE_DEFAULT_HB			5000		/* Default Holdback value */
#घोषणा	ROSE_DEFAULT_IDLE		0		/* No Activity Timeout - none */
#घोषणा	ROSE_DEFAULT_ROUTING		1		/* Default routing flag */
#घोषणा	ROSE_DEFAULT_FAIL_TIMEOUT	120000		/* Time until link considered usable */
#घोषणा	ROSE_DEFAULT_MAXVC		50		/* Maximum number of VCs per neighbour */
#घोषणा	ROSE_DEFAULT_WINDOW_SIZE	7		/* Default winकरोw size */

#घोषणा ROSE_MODULUS 			8
#घोषणा	ROSE_MAX_PACKET_SIZE		251		/* Maximum packet size */

#घोषणा	ROSE_COND_ACK_PENDING		0x01
#घोषणा	ROSE_COND_PEER_RX_BUSY		0x02
#घोषणा	ROSE_COND_OWN_RX_BUSY		0x04

#घोषणा	FAC_NATIONAL			0x00
#घोषणा	FAC_CCITT			0x0F

#घोषणा	FAC_NATIONAL_RAND		0x7F
#घोषणा	FAC_NATIONAL_FLAGS		0x3F
#घोषणा	FAC_NATIONAL_DEST_DIGI		0xE9
#घोषणा	FAC_NATIONAL_SRC_DIGI		0xEB
#घोषणा	FAC_NATIONAL_FAIL_CALL		0xED
#घोषणा	FAC_NATIONAL_FAIL_ADD		0xEE
#घोषणा	FAC_NATIONAL_DIGIS			0xEF

#घोषणा	FAC_CCITT_DEST_NSAP		0xC9
#घोषणा	FAC_CCITT_SRC_NSAP		0xCB

काष्ठा rose_neigh अणु
	काष्ठा rose_neigh	*next;
	ax25_address		callsign;
	ax25_digi		*digipeat;
	ax25_cb			*ax25;
	काष्ठा net_device		*dev;
	अचिन्हित लघु		count;
	अचिन्हित लघु		use;
	अचिन्हित पूर्णांक		number;
	अक्षर			restarted;
	अक्षर			dce_mode;
	अक्षर			loopback;
	काष्ठा sk_buff_head	queue;
	काष्ठा समयr_list	t0समयr;
	काष्ठा समयr_list	fसमयr;
पूर्ण;

काष्ठा rose_node अणु
	काष्ठा rose_node	*next;
	rose_address		address;
	अचिन्हित लघु		mask;
	अचिन्हित अक्षर		count;
	अक्षर			loopback;
	काष्ठा rose_neigh	*neighbour[3];
पूर्ण;

काष्ठा rose_route अणु
	काष्ठा rose_route	*next;
	अचिन्हित पूर्णांक		lci1, lci2;
	rose_address		src_addr, dest_addr;
	ax25_address		src_call, dest_call;
	काष्ठा rose_neigh 	*neigh1, *neigh2;
	अचिन्हित पूर्णांक		अक्रम;
पूर्ण;

काष्ठा rose_sock अणु
	काष्ठा sock		sock;
	rose_address		source_addr,   dest_addr;
	ax25_address		source_call,   dest_call;
	अचिन्हित अक्षर		source_ndigis, dest_ndigis;
	ax25_address		source_digis[ROSE_MAX_DIGIS];
	ax25_address		dest_digis[ROSE_MAX_DIGIS];
	काष्ठा rose_neigh	*neighbour;
	काष्ठा net_device		*device;
	अचिन्हित पूर्णांक		lci, अक्रम;
	अचिन्हित अक्षर		state, condition, qbitincl, defer;
	अचिन्हित अक्षर		cause, diagnostic;
	अचिन्हित लघु		vs, vr, va, vl;
	अचिन्हित दीर्घ		t1, t2, t3, hb, idle;
#अगर_घोषित M_BIT
	अचिन्हित लघु		fraglen;
	काष्ठा sk_buff_head	frag_queue;
#पूर्ण_अगर
	काष्ठा sk_buff_head	ack_queue;
	काष्ठा rose_facilities_काष्ठा facilities;
	काष्ठा समयr_list	समयr;
	काष्ठा समयr_list	idleसमयr;
पूर्ण;

#घोषणा rose_sk(sk) ((काष्ठा rose_sock *)(sk))

/* af_rose.c */
बाह्य ax25_address rose_callsign;
बाह्य पूर्णांक  sysctl_rose_restart_request_समयout;
बाह्य पूर्णांक  sysctl_rose_call_request_समयout;
बाह्य पूर्णांक  sysctl_rose_reset_request_समयout;
बाह्य पूर्णांक  sysctl_rose_clear_request_समयout;
बाह्य पूर्णांक  sysctl_rose_no_activity_समयout;
बाह्य पूर्णांक  sysctl_rose_ack_hold_back_समयout;
बाह्य पूर्णांक  sysctl_rose_routing_control;
बाह्य पूर्णांक  sysctl_rose_link_fail_समयout;
बाह्य पूर्णांक  sysctl_rose_maximum_vcs;
बाह्य पूर्णांक  sysctl_rose_winकरोw_size;

पूर्णांक rosecmp(rose_address *, rose_address *);
पूर्णांक rosecmpm(rose_address *, rose_address *, अचिन्हित लघु);
अक्षर *rose2asc(अक्षर *buf, स्थिर rose_address *);
काष्ठा sock *rose_find_socket(अचिन्हित पूर्णांक, काष्ठा rose_neigh *);
व्योम rose_समाप्त_by_neigh(काष्ठा rose_neigh *);
अचिन्हित पूर्णांक rose_new_lci(काष्ठा rose_neigh *);
पूर्णांक rose_rx_call_request(काष्ठा sk_buff *, काष्ठा net_device *,
			 काष्ठा rose_neigh *, अचिन्हित पूर्णांक);
व्योम rose_destroy_socket(काष्ठा sock *);

/* rose_dev.c */
व्योम rose_setup(काष्ठा net_device *);

/* rose_in.c */
पूर्णांक rose_process_rx_frame(काष्ठा sock *, काष्ठा sk_buff *);

/* rose_link.c */
व्योम rose_start_fसमयr(काष्ठा rose_neigh *);
व्योम rose_stop_fसमयr(काष्ठा rose_neigh *);
व्योम rose_stop_t0समयr(काष्ठा rose_neigh *);
पूर्णांक rose_fसमयr_running(काष्ठा rose_neigh *);
व्योम rose_link_rx_restart(काष्ठा sk_buff *, काष्ठा rose_neigh *,
			  अचिन्हित लघु);
व्योम rose_transmit_clear_request(काष्ठा rose_neigh *, अचिन्हित पूर्णांक,
				 अचिन्हित अक्षर, अचिन्हित अक्षर);
व्योम rose_transmit_link(काष्ठा sk_buff *, काष्ठा rose_neigh *);

/* rose_loopback.c */
व्योम rose_loopback_init(व्योम);
व्योम rose_loopback_clear(व्योम);
पूर्णांक rose_loopback_queue(काष्ठा sk_buff *, काष्ठा rose_neigh *);

/* rose_out.c */
व्योम rose_kick(काष्ठा sock *);
व्योम rose_enquiry_response(काष्ठा sock *);

/* rose_route.c */
बाह्य काष्ठा rose_neigh *rose_loopback_neigh;
बाह्य स्थिर काष्ठा seq_operations rose_neigh_seqops;
बाह्य स्थिर काष्ठा seq_operations rose_node_seqops;
बाह्य काष्ठा seq_operations rose_route_seqops;

व्योम rose_add_loopback_neigh(व्योम);
पूर्णांक __must_check rose_add_loopback_node(rose_address *);
व्योम rose_del_loopback_node(rose_address *);
व्योम rose_rt_device_करोwn(काष्ठा net_device *);
व्योम rose_link_device_करोwn(काष्ठा net_device *);
काष्ठा net_device *rose_dev_first(व्योम);
काष्ठा net_device *rose_dev_get(rose_address *);
काष्ठा rose_route *rose_route_मुक्त_lci(अचिन्हित पूर्णांक, काष्ठा rose_neigh *);
काष्ठा rose_neigh *rose_get_neigh(rose_address *, अचिन्हित अक्षर *,
				  अचिन्हित अक्षर *, पूर्णांक);
पूर्णांक rose_rt_ioctl(अचिन्हित पूर्णांक, व्योम __user *);
व्योम rose_link_failed(ax25_cb *, पूर्णांक);
पूर्णांक rose_route_frame(काष्ठा sk_buff *, ax25_cb *);
व्योम rose_rt_मुक्त(व्योम);

/* rose_subr.c */
व्योम rose_clear_queues(काष्ठा sock *);
व्योम rose_frames_acked(काष्ठा sock *, अचिन्हित लघु);
व्योम rose_requeue_frames(काष्ठा sock *);
पूर्णांक rose_validate_nr(काष्ठा sock *, अचिन्हित लघु);
व्योम rose_ग_लिखो_पूर्णांकernal(काष्ठा sock *, पूर्णांक);
पूर्णांक rose_decode(काष्ठा sk_buff *, पूर्णांक *, पूर्णांक *, पूर्णांक *, पूर्णांक *, पूर्णांक *);
पूर्णांक rose_parse_facilities(अचिन्हित अक्षर *, अचिन्हित पूर्णांक,
			  काष्ठा rose_facilities_काष्ठा *);
व्योम rose_disconnect(काष्ठा sock *, पूर्णांक, पूर्णांक, पूर्णांक);

/* rose_समयr.c */
व्योम rose_start_heartbeat(काष्ठा sock *);
व्योम rose_start_t1समयr(काष्ठा sock *);
व्योम rose_start_t2समयr(काष्ठा sock *);
व्योम rose_start_t3समयr(काष्ठा sock *);
व्योम rose_start_hbसमयr(काष्ठा sock *);
व्योम rose_start_idleसमयr(काष्ठा sock *);
व्योम rose_stop_heartbeat(काष्ठा sock *);
व्योम rose_stop_समयr(काष्ठा sock *);
व्योम rose_stop_idleसमयr(काष्ठा sock *);

/* sysctl_net_rose.c */
व्योम rose_रेजिस्टर_sysctl(व्योम);
व्योम rose_unरेजिस्टर_sysctl(व्योम);

#पूर्ण_अगर
