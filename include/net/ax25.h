<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Declarations of AX.25 type objects.
 *
 *	Alan Cox (GW4PTS) 	10/11/93
 */
#अगर_अघोषित _AX25_H
#घोषणा _AX25_H 

#समावेश <linux/ax25.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/refcount.h>
#समावेश <net/neighbour.h>
#समावेश <net/sock.h>
#समावेश <linux/seq_file.h>

#घोषणा	AX25_T1CLAMPLO  		1
#घोषणा	AX25_T1CLAMPHI 			(30 * HZ)

#घोषणा	AX25_BPQ_HEADER_LEN		16
#घोषणा	AX25_KISS_HEADER_LEN		1

#घोषणा	AX25_HEADER_LEN			17
#घोषणा	AX25_ADDR_LEN			7
#घोषणा	AX25_DIGI_HEADER_LEN		(AX25_MAX_DIGIS * AX25_ADDR_LEN)
#घोषणा	AX25_MAX_HEADER_LEN		(AX25_HEADER_LEN + AX25_DIGI_HEADER_LEN)

/* AX.25 Protocol IDs */
#घोषणा AX25_P_ROSE			0x01
#घोषणा AX25_P_VJCOMP			0x06	/* Compressed TCP/IP packet   */
						/* Van Jacobsen (RFC 1144)    */
#घोषणा AX25_P_VJUNCOMP			0x07	/* Uncompressed TCP/IP packet */
						/* Van Jacobsen (RFC 1144)    */
#घोषणा	AX25_P_SEGMENT			0x08	/* Segmentation fragment      */
#घोषणा AX25_P_TEXNET			0xc3	/* TEXTNET datagram protocol  */
#घोषणा AX25_P_LQ			0xc4	/* Link Quality Protocol      */
#घोषणा AX25_P_ATALK			0xca	/* Appletalk                  */
#घोषणा AX25_P_ATALK_ARP		0xcb	/* Appletalk ARP              */
#घोषणा AX25_P_IP			0xcc	/* ARPA Internet Protocol     */
#घोषणा AX25_P_ARP			0xcd	/* ARPA Address Resolution    */
#घोषणा AX25_P_FLEXNET			0xce	/* FlexNet                    */
#घोषणा AX25_P_NETROM 			0xcf	/* NET/ROM                    */
#घोषणा AX25_P_TEXT 			0xF0	/* No layer 3 protocol impl.  */

/* AX.25 Segment control values */
#घोषणा	AX25_SEG_REM			0x7F
#घोषणा	AX25_SEG_FIRST			0x80

#घोषणा AX25_CBIT			0x80	/* Command/Response bit */
#घोषणा AX25_EBIT			0x01	/* HDLC Address Extension bit */
#घोषणा AX25_HBIT			0x80	/* Has been repeated bit */

#घोषणा AX25_SSSID_SPARE		0x60	/* Unused bits in SSID क्रम standard AX.25 */
#घोषणा AX25_ESSID_SPARE		0x20	/* Unused bits in SSID क्रम extended AX.25 */
#घोषणा AX25_DAMA_FLAG			0x20	/* Well, it is *NOT* unused! (dl1bke 951121 */

#घोषणा	AX25_COND_ACK_PENDING		0x01
#घोषणा	AX25_COND_REJECT		0x02
#घोषणा	AX25_COND_PEER_RX_BUSY		0x04
#घोषणा	AX25_COND_OWN_RX_BUSY		0x08
#घोषणा	AX25_COND_DAMA_MODE		0x10

#अगर_अघोषित _LINUX_NETDEVICE_H
#समावेश <linux/netdevice.h>
#पूर्ण_अगर

/* Upper sub-layer (LAPB) definitions */

/* Control field ढाँचाs */
#घोषणा	AX25_I			0x00	/* Inक्रमmation frames */
#घोषणा	AX25_S			0x01	/* Supervisory frames */
#घोषणा	AX25_RR			0x01	/* Receiver पढ़ोy */
#घोषणा	AX25_RNR		0x05	/* Receiver not पढ़ोy */
#घोषणा	AX25_REJ		0x09	/* Reject */
#घोषणा	AX25_U			0x03	/* Unnumbered frames */
#घोषणा	AX25_SABM		0x2f	/* Set Asynchronous Balanced Mode */
#घोषणा	AX25_SABME		0x6f	/* Set Asynchronous Balanced Mode Extended */
#घोषणा	AX25_DISC		0x43	/* Disconnect */
#घोषणा	AX25_DM			0x0f	/* Disconnected mode */
#घोषणा	AX25_UA			0x63	/* Unnumbered acknowledge */
#घोषणा	AX25_FRMR		0x87	/* Frame reject */
#घोषणा	AX25_UI			0x03	/* Unnumbered inक्रमmation */
#घोषणा	AX25_XID		0xaf	/* Exchange inक्रमmation */
#घोषणा	AX25_TEST		0xe3	/* Test */

#घोषणा	AX25_PF			0x10	/* Poll/final bit क्रम standard AX.25 */
#घोषणा	AX25_EPF		0x01	/* Poll/final bit क्रम extended AX.25 */

#घोषणा AX25_ILLEGAL		0x100	/* Impossible to be a real frame type */

#घोषणा	AX25_POLLOFF		0
#घोषणा	AX25_POLLON		1

/* AX25 L2 C-bit */
#घोषणा AX25_COMMAND		1
#घोषणा AX25_RESPONSE		2

/* Define Link State स्थिरants. */

क्रमागत अणु 
	AX25_STATE_0,			/* Listening */
	AX25_STATE_1,			/* SABM sent */
	AX25_STATE_2,			/* DISC sent */
	AX25_STATE_3,			/* Established */
	AX25_STATE_4			/* Recovery */
पूर्ण;

#घोषणा AX25_MODULUS 		8	/*  Standard AX.25 modulus */
#घोषणा	AX25_EMODULUS		128	/*  Extended AX.25 modulus */

क्रमागत अणु
	AX25_PROTO_STD_SIMPLEX,
	AX25_PROTO_STD_DUPLEX,
#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	AX25_PROTO_DAMA_SLAVE,
#अगर_घोषित CONFIG_AX25_DAMA_MASTER
	AX25_PROTO_DAMA_MASTER,
#घोषणा AX25_PROTO_MAX AX25_PROTO_DAMA_MASTER
#पूर्ण_अगर
#पूर्ण_अगर
	__AX25_PROTO_MAX,
	AX25_PROTO_MAX = __AX25_PROTO_MAX -1
पूर्ण;

क्रमागत अणु
	AX25_VALUES_IPDEFMODE,	/* 0=DG 1=VC */
	AX25_VALUES_AXDEFMODE,	/* 0=Normal 1=Extended Seq Nos */
	AX25_VALUES_BACKOFF,	/* 0=None 1=Linear 2=Exponential */
	AX25_VALUES_CONMODE,	/* Allow connected modes - 0=No 1=no "PID text" 2=all PIDs */
	AX25_VALUES_WINDOW,	/* Default winकरोw size क्रम standard AX.25 */
	AX25_VALUES_EWINDOW,	/* Default winकरोw size क्रम extended AX.25 */
	AX25_VALUES_T1,		/* Default T1 समयout value */
	AX25_VALUES_T2,		/* Default T2 समयout value */
	AX25_VALUES_T3,		/* Default T3 समयout value */
	AX25_VALUES_IDLE,	/* Connected mode idle समयr */
	AX25_VALUES_N2,		/* Default N2 value */
	AX25_VALUES_PACLEN,	/* AX.25 MTU */
	AX25_VALUES_PROTOCOL,	/* Std AX.25, DAMA Slave, DAMA Master */
	AX25_VALUES_DS_TIMEOUT,	/* DAMA Slave समयout */
	AX25_MAX_VALUES		/* THIS MUST REMAIN THE LAST ENTRY OF THIS LIST */
पूर्ण;

#घोषणा	AX25_DEF_IPDEFMODE	0			/* Datagram */
#घोषणा	AX25_DEF_AXDEFMODE	0			/* Normal */
#घोषणा	AX25_DEF_BACKOFF	1			/* Linear backoff */
#घोषणा	AX25_DEF_CONMODE	2			/* Connected mode allowed */
#घोषणा	AX25_DEF_WINDOW		2			/* Winकरोw=2 */
#घोषणा	AX25_DEF_EWINDOW	32			/* Module-128 Winकरोw=32 */
#घोषणा	AX25_DEF_T1		10000			/* T1=10s */
#घोषणा	AX25_DEF_T2		3000			/* T2=3s  */
#घोषणा	AX25_DEF_T3		300000			/* T3=300s */
#घोषणा	AX25_DEF_N2		10			/* N2=10 */
#घोषणा AX25_DEF_IDLE		0			/* Idle=None */
#घोषणा AX25_DEF_PACLEN		256			/* Paclen=256 */
#घोषणा	AX25_DEF_PROTOCOL	AX25_PROTO_STD_SIMPLEX	/* Standard AX.25 */
#घोषणा AX25_DEF_DS_TIMEOUT	180000			/* DAMA समयout 3 minutes */

प्रकार काष्ठा ax25_uid_assoc अणु
	काष्ठा hlist_node	uid_node;
	refcount_t		refcount;
	kuid_t			uid;
	ax25_address		call;
पूर्ण ax25_uid_assoc;

#घोषणा ax25_uid_क्रम_each(__ax25, list) \
	hlist_क्रम_each_entry(__ax25, list, uid_node)

#घोषणा ax25_uid_hold(ax25) \
	refcount_inc(&((ax25)->refcount))

अटल अंतरभूत व्योम ax25_uid_put(ax25_uid_assoc *assoc)
अणु
	अगर (refcount_dec_and_test(&assoc->refcount)) अणु
		kमुक्त(assoc);
	पूर्ण
पूर्ण

प्रकार काष्ठा अणु
	ax25_address		calls[AX25_MAX_DIGIS];
	अचिन्हित अक्षर		repeated[AX25_MAX_DIGIS];
	अचिन्हित अक्षर		ndigi;
	चिन्हित अक्षर		lastrepeat;
पूर्ण ax25_digi;

प्रकार काष्ठा ax25_route अणु
	काष्ठा ax25_route	*next;
	refcount_t		refcount;
	ax25_address		callsign;
	काष्ठा net_device	*dev;
	ax25_digi		*digipeat;
	अक्षर			ip_mode;
पूर्ण ax25_route;

अटल अंतरभूत व्योम ax25_hold_route(ax25_route *ax25_rt)
अणु
	refcount_inc(&ax25_rt->refcount);
पूर्ण

व्योम __ax25_put_route(ax25_route *ax25_rt);

बाह्य rwlock_t ax25_route_lock;

अटल अंतरभूत व्योम ax25_route_lock_use(व्योम)
अणु
	पढ़ो_lock(&ax25_route_lock);
पूर्ण

अटल अंतरभूत व्योम ax25_route_lock_unuse(व्योम)
अणु
	पढ़ो_unlock(&ax25_route_lock);
पूर्ण

अटल अंतरभूत व्योम ax25_put_route(ax25_route *ax25_rt)
अणु
	अगर (refcount_dec_and_test(&ax25_rt->refcount))
		__ax25_put_route(ax25_rt);
पूर्ण

प्रकार काष्ठा अणु
	अक्षर			slave;			/* slave_mode?   */
	काष्ठा समयr_list	slave_समयr;		/* समयout समयr */
	अचिन्हित लघु		slave_समयout;		/* when? */
पूर्ण ax25_dama_info;

काष्ठा ctl_table;

प्रकार काष्ठा ax25_dev अणु
	काष्ठा ax25_dev		*next;
	काष्ठा net_device	*dev;
	काष्ठा net_device	*क्रमward;
	काष्ठा ctl_table_header *sysheader;
	पूर्णांक			values[AX25_MAX_VALUES];
#अगर defined(CONFIG_AX25_DAMA_SLAVE) || defined(CONFIG_AX25_DAMA_MASTER)
	ax25_dama_info		dama;
#पूर्ण_अगर
पूर्ण ax25_dev;

प्रकार काष्ठा ax25_cb अणु
	काष्ठा hlist_node	ax25_node;
	ax25_address		source_addr, dest_addr;
	ax25_digi		*digipeat;
	ax25_dev		*ax25_dev;
	अचिन्हित अक्षर		iamdigi;
	अचिन्हित अक्षर		state, modulus, pidincl;
	अचिन्हित लघु		vs, vr, va;
	अचिन्हित अक्षर		condition, backoff;
	अचिन्हित अक्षर		n2, n2count;
	काष्ठा समयr_list	t1समयr, t2समयr, t3समयr, idleसमयr;
	अचिन्हित दीर्घ		t1, t2, t3, idle, rtt;
	अचिन्हित लघु		paclen, fragno, fraglen;
	काष्ठा sk_buff_head	ग_लिखो_queue;
	काष्ठा sk_buff_head	reseq_queue;
	काष्ठा sk_buff_head	ack_queue;
	काष्ठा sk_buff_head	frag_queue;
	अचिन्हित अक्षर		winकरोw;
	काष्ठा समयr_list	समयr, dसमयr;
	काष्ठा sock		*sk;		/* Backlink to socket */
	refcount_t		refcount;
पूर्ण ax25_cb;

काष्ठा ax25_sock अणु
	काष्ठा sock		sk;
	काष्ठा ax25_cb		*cb;
पूर्ण;

अटल अंतरभूत काष्ठा ax25_sock *ax25_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा ax25_sock *) sk;
पूर्ण

अटल अंतरभूत काष्ठा ax25_cb *sk_to_ax25(स्थिर काष्ठा sock *sk)
अणु
	वापस ax25_sk(sk)->cb;
पूर्ण

#घोषणा ax25_क्रम_each(__ax25, list) \
	hlist_क्रम_each_entry(__ax25, list, ax25_node)

#घोषणा ax25_cb_hold(__ax25) \
	refcount_inc(&((__ax25)->refcount))

अटल __अंतरभूत__ व्योम ax25_cb_put(ax25_cb *ax25)
अणु
	अगर (refcount_dec_and_test(&ax25->refcount)) अणु
		kमुक्त(ax25->digipeat);
		kमुक्त(ax25);
	पूर्ण
पूर्ण

अटल अंतरभूत __be16 ax25_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	skb->dev      = dev;
	skb_reset_mac_header(skb);
	skb->pkt_type = PACKET_HOST;
	वापस htons(ETH_P_AX25);
पूर्ण

/* af_ax25.c */
बाह्य काष्ठा hlist_head ax25_list;
बाह्य spinlock_t ax25_list_lock;
व्योम ax25_cb_add(ax25_cb *);
काष्ठा sock *ax25_find_listener(ax25_address *, पूर्णांक, काष्ठा net_device *, पूर्णांक);
काष्ठा sock *ax25_get_socket(ax25_address *, ax25_address *, पूर्णांक);
ax25_cb *ax25_find_cb(ax25_address *, ax25_address *, ax25_digi *,
		      काष्ठा net_device *);
व्योम ax25_send_to_raw(ax25_address *, काष्ठा sk_buff *, पूर्णांक);
व्योम ax25_destroy_socket(ax25_cb *);
ax25_cb * __must_check ax25_create_cb(व्योम);
व्योम ax25_fillin_cb(ax25_cb *, ax25_dev *);
काष्ठा sock *ax25_make_new(काष्ठा sock *, काष्ठा ax25_dev *);

/* ax25_addr.c */
बाह्य स्थिर ax25_address ax25_bcast;
बाह्य स्थिर ax25_address ax25_defaddr;
बाह्य स्थिर ax25_address null_ax25_address;
अक्षर *ax2asc(अक्षर *buf, स्थिर ax25_address *);
व्योम asc2ax(ax25_address *addr, स्थिर अक्षर *callsign);
पूर्णांक ax25cmp(स्थिर ax25_address *, स्थिर ax25_address *);
पूर्णांक ax25digicmp(स्थिर ax25_digi *, स्थिर ax25_digi *);
स्थिर अचिन्हित अक्षर *ax25_addr_parse(स्थिर अचिन्हित अक्षर *, पूर्णांक,
	ax25_address *, ax25_address *, ax25_digi *, पूर्णांक *, पूर्णांक *);
पूर्णांक ax25_addr_build(अचिन्हित अक्षर *, स्थिर ax25_address *,
		    स्थिर ax25_address *, स्थिर ax25_digi *, पूर्णांक, पूर्णांक);
पूर्णांक ax25_addr_size(स्थिर ax25_digi *);
व्योम ax25_digi_invert(स्थिर ax25_digi *, ax25_digi *);

/* ax25_dev.c */
बाह्य ax25_dev *ax25_dev_list;
बाह्य spinlock_t ax25_dev_lock;

#अगर IS_ENABLED(CONFIG_AX25)
अटल अंतरभूत ax25_dev *ax25_dev_ax25dev(काष्ठा net_device *dev)
अणु
	वापस dev->ax25_ptr;
पूर्ण
#पूर्ण_अगर

ax25_dev *ax25_addr_ax25dev(ax25_address *);
व्योम ax25_dev_device_up(काष्ठा net_device *);
व्योम ax25_dev_device_करोwn(काष्ठा net_device *);
पूर्णांक ax25_fwd_ioctl(अचिन्हित पूर्णांक, काष्ठा ax25_fwd_काष्ठा *);
काष्ठा net_device *ax25_fwd_dev(काष्ठा net_device *);
व्योम ax25_dev_मुक्त(व्योम);

/* ax25_ds_in.c */
पूर्णांक ax25_ds_frame_in(ax25_cb *, काष्ठा sk_buff *, पूर्णांक);

/* ax25_ds_subr.c */
व्योम ax25_ds_nr_error_recovery(ax25_cb *);
व्योम ax25_ds_enquiry_response(ax25_cb *);
व्योम ax25_ds_establish_data_link(ax25_cb *);
व्योम ax25_dev_dama_off(ax25_dev *);
व्योम ax25_dama_on(ax25_cb *);
व्योम ax25_dama_off(ax25_cb *);

/* ax25_ds_समयr.c */
व्योम ax25_ds_setup_समयr(ax25_dev *);
व्योम ax25_ds_set_समयr(ax25_dev *);
व्योम ax25_ds_del_समयr(ax25_dev *);
व्योम ax25_ds_समयr(ax25_cb *);
व्योम ax25_ds_t1_समयout(ax25_cb *);
व्योम ax25_ds_heartbeat_expiry(ax25_cb *);
व्योम ax25_ds_t3समयr_expiry(ax25_cb *);
व्योम ax25_ds_idleसमयr_expiry(ax25_cb *);

/* ax25_अगरace.c */

काष्ठा ax25_protocol अणु
	काष्ठा ax25_protocol *next;
	अचिन्हित पूर्णांक pid;
	पूर्णांक (*func)(काष्ठा sk_buff *, ax25_cb *);
पूर्ण;

व्योम ax25_रेजिस्टर_pid(काष्ठा ax25_protocol *ap);
व्योम ax25_protocol_release(अचिन्हित पूर्णांक);

काष्ठा ax25_linkfail अणु
	काष्ठा hlist_node lf_node;
	व्योम (*func)(ax25_cb *, पूर्णांक);
पूर्ण;

व्योम ax25_linkfail_रेजिस्टर(काष्ठा ax25_linkfail *lf);
व्योम ax25_linkfail_release(काष्ठा ax25_linkfail *lf);
पूर्णांक __must_check ax25_listen_रेजिस्टर(ax25_address *, काष्ठा net_device *);
व्योम ax25_listen_release(ax25_address *, काष्ठा net_device *);
पूर्णांक(*ax25_protocol_function(अचिन्हित पूर्णांक))(काष्ठा sk_buff *, ax25_cb *);
पूर्णांक ax25_listen_mine(ax25_address *, काष्ठा net_device *);
व्योम ax25_link_failed(ax25_cb *, पूर्णांक);
पूर्णांक ax25_protocol_is_रेजिस्टरed(अचिन्हित पूर्णांक);

/* ax25_in.c */
पूर्णांक ax25_rx_अगरrame(ax25_cb *, काष्ठा sk_buff *);
पूर्णांक ax25_kiss_rcv(काष्ठा sk_buff *, काष्ठा net_device *, काष्ठा packet_type *,
		  काष्ठा net_device *);

/* ax25_ip.c */
netdev_tx_t ax25_ip_xmit(काष्ठा sk_buff *skb);
बाह्य स्थिर काष्ठा header_ops ax25_header_ops;

/* ax25_out.c */
ax25_cb *ax25_send_frame(काष्ठा sk_buff *, पूर्णांक, ax25_address *, ax25_address *,
			 ax25_digi *, काष्ठा net_device *);
व्योम ax25_output(ax25_cb *, पूर्णांक, काष्ठा sk_buff *);
व्योम ax25_kick(ax25_cb *);
व्योम ax25_transmit_buffer(ax25_cb *, काष्ठा sk_buff *, पूर्णांक);
व्योम ax25_queue_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
पूर्णांक ax25_check_अगरrames_acked(ax25_cb *, अचिन्हित लघु);

/* ax25_route.c */
व्योम ax25_rt_device_करोwn(काष्ठा net_device *);
पूर्णांक ax25_rt_ioctl(अचिन्हित पूर्णांक, व्योम __user *);
बाह्य स्थिर काष्ठा seq_operations ax25_rt_seqops;
ax25_route *ax25_get_route(ax25_address *addr, काष्ठा net_device *dev);
पूर्णांक ax25_rt_स्वतःbind(ax25_cb *, ax25_address *);
काष्ठा sk_buff *ax25_rt_build_path(काष्ठा sk_buff *, ax25_address *,
				   ax25_address *, ax25_digi *);
व्योम ax25_rt_मुक्त(व्योम);

/* ax25_std_in.c */
पूर्णांक ax25_std_frame_in(ax25_cb *, काष्ठा sk_buff *, पूर्णांक);

/* ax25_std_subr.c */
व्योम ax25_std_nr_error_recovery(ax25_cb *);
व्योम ax25_std_establish_data_link(ax25_cb *);
व्योम ax25_std_transmit_enquiry(ax25_cb *);
व्योम ax25_std_enquiry_response(ax25_cb *);
व्योम ax25_std_समयout_response(ax25_cb *);

/* ax25_std_समयr.c */
व्योम ax25_std_heartbeat_expiry(ax25_cb *);
व्योम ax25_std_t1समयr_expiry(ax25_cb *);
व्योम ax25_std_t2समयr_expiry(ax25_cb *);
व्योम ax25_std_t3समयr_expiry(ax25_cb *);
व्योम ax25_std_idleसमयr_expiry(ax25_cb *);

/* ax25_subr.c */
व्योम ax25_clear_queues(ax25_cb *);
व्योम ax25_frames_acked(ax25_cb *, अचिन्हित लघु);
व्योम ax25_requeue_frames(ax25_cb *);
पूर्णांक ax25_validate_nr(ax25_cb *, अचिन्हित लघु);
पूर्णांक ax25_decode(ax25_cb *, काष्ठा sk_buff *, पूर्णांक *, पूर्णांक *, पूर्णांक *);
व्योम ax25_send_control(ax25_cb *, पूर्णांक, पूर्णांक, पूर्णांक);
व्योम ax25_वापस_dm(काष्ठा net_device *, ax25_address *, ax25_address *,
		    ax25_digi *);
व्योम ax25_calculate_t1(ax25_cb *);
व्योम ax25_calculate_rtt(ax25_cb *);
व्योम ax25_disconnect(ax25_cb *, पूर्णांक);

/* ax25_समयr.c */
व्योम ax25_setup_समयrs(ax25_cb *);
व्योम ax25_start_heartbeat(ax25_cb *);
व्योम ax25_start_t1समयr(ax25_cb *);
व्योम ax25_start_t2समयr(ax25_cb *);
व्योम ax25_start_t3समयr(ax25_cb *);
व्योम ax25_start_idleसमयr(ax25_cb *);
व्योम ax25_stop_heartbeat(ax25_cb *);
व्योम ax25_stop_t1समयr(ax25_cb *);
व्योम ax25_stop_t2समयr(ax25_cb *);
व्योम ax25_stop_t3समयr(ax25_cb *);
व्योम ax25_stop_idleसमयr(ax25_cb *);
पूर्णांक ax25_t1समयr_running(ax25_cb *);
अचिन्हित दीर्घ ax25_display_समयr(काष्ठा समयr_list *);

/* ax25_uid.c */
बाह्य पूर्णांक  ax25_uid_policy;
ax25_uid_assoc *ax25_findbyuid(kuid_t);
पूर्णांक __must_check ax25_uid_ioctl(पूर्णांक, काष्ठा sockaddr_ax25 *);
बाह्य स्थिर काष्ठा seq_operations ax25_uid_seqops;
व्योम ax25_uid_मुक्त(व्योम);

/* sysctl_net_ax25.c */
#अगर_घोषित CONFIG_SYSCTL
पूर्णांक ax25_रेजिस्टर_dev_sysctl(ax25_dev *ax25_dev);
व्योम ax25_unरेजिस्टर_dev_sysctl(ax25_dev *ax25_dev);
#अन्यथा
अटल अंतरभूत पूर्णांक ax25_रेजिस्टर_dev_sysctl(ax25_dev *ax25_dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ax25_unरेजिस्टर_dev_sysctl(ax25_dev *ax25_dev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

#पूर्ण_अगर
