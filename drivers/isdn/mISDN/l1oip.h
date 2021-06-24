<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * see notice in l1oip.c
 */

/* debugging */
#घोषणा DEBUG_L1OIP_INIT	0x00010000
#घोषणा DEBUG_L1OIP_SOCKET	0x00020000
#घोषणा DEBUG_L1OIP_MGR		0x00040000
#घोषणा DEBUG_L1OIP_MSG		0x00080000

/* enable to disorder received bchannels by sequence 2143658798... */
/*
  #घोषणा REORDER_DEBUG
*/

/* frames */
#घोषणा L1OIP_MAX_LEN		2048		/* max packet size क्रमm l2 */
#घोषणा L1OIP_MAX_PERFRAME	1400		/* max data size in one frame */


/* समयrs */
#घोषणा L1OIP_KEEPALIVE		15
#घोषणा L1OIP_TIMEOUT		65


/* socket */
#घोषणा L1OIP_DEFAULTPORT	931


/* channel काष्ठाure */
काष्ठा l1oip_chan अणु
	काष्ठा dchannel		*dch;
	काष्ठा bchannel		*bch;
	u32			tx_counter;	/* counts xmit bytes/packets */
	u32			rx_counter;	/* counts recv bytes/packets */
	u32			codecstate;	/* used by codec to save data */
#अगर_घोषित REORDER_DEBUG
	पूर्णांक			disorder_flag;
	काष्ठा sk_buff		*disorder_skb;
	u32			disorder_cnt;
#पूर्ण_अगर
पूर्ण;


/* card काष्ठाure */
काष्ठा l1oip अणु
	काष्ठा list_head        list;

	/* card */
	पूर्णांक			रेजिस्टरed;	/* अगर रेजिस्टरed with mISDN */
	अक्षर			name[MISDN_MAX_IDLEN];
	पूर्णांक			idx;		/* card index */
	पूर्णांक			pri;		/* 1=pri, 0=bri */
	पूर्णांक			d_idx;		/* current dchannel number */
	पूर्णांक			b_num;		/* number of bchannels */
	u32			id;		/* id of connection */
	पूर्णांक			ondemand;	/* अगर transmis. is on demand */
	पूर्णांक			bundle;		/* bundle channels in one frm */
	पूर्णांक			codec;		/* codec to use क्रम transmis. */
	पूर्णांक			limit;		/* limit number of bchannels */

	/* समयr */
	काष्ठा समयr_list	keep_tl;
	काष्ठा समयr_list	समयout_tl;
	पूर्णांक			समयout_on;
	काष्ठा work_काष्ठा	workq;

	/* socket */
	काष्ठा socket		*socket;	/* अगर set, socket is created */
	काष्ठा completion	socket_complete;/* completion of sock thपढ़ो */
	काष्ठा task_काष्ठा	*socket_thपढ़ो;
	spinlock_t		socket_lock;	/* access sock outside thपढ़ो */
	u32			remoteip;	/* अगर all set, ip is asचिन्हित */
	u16			localport;	/* must always be set */
	u16			remoteport;	/* must always be set */
	काष्ठा sockaddr_in	sin_local;	/* local socket name */
	काष्ठा sockaddr_in	sin_remote;	/* remote socket name */
	काष्ठा msghdr		sendmsg;	/* ip message to send */
	काष्ठा kvec		sendiov;	/* iov क्रम message */

	/* frame */
	काष्ठा l1oip_chan	chan[128];	/* channel instances */
पूर्ण;

बाह्य पूर्णांक l1oip_law_to_4bit(u8 *data, पूर्णांक len, u8 *result, u32 *state);
बाह्य पूर्णांक l1oip_4bit_to_law(u8 *data, पूर्णांक len, u8 *result);
बाह्य पूर्णांक l1oip_alaw_to_ulaw(u8 *data, पूर्णांक len, u8 *result);
बाह्य पूर्णांक l1oip_ulaw_to_alaw(u8 *data, पूर्णांक len, u8 *result);
बाह्य व्योम l1oip_4bit_मुक्त(व्योम);
बाह्य पूर्णांक l1oip_4bit_alloc(पूर्णांक ulaw);
