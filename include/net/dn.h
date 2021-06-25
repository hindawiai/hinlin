<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_DN_H
#घोषणा _NET_DN_H

#समावेश <linux/dn.h>
#समावेश <net/sock.h>
#समावेश <net/flow.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

काष्ठा dn_scp                                   /* Session Control Port */
अणु
        अचिन्हित अक्षर           state;
#घोषणा DN_O     1                      /* Open                 */
#घोषणा DN_CR    2                      /* Connect Receive      */
#घोषणा DN_DR    3                      /* Disconnect Reject    */
#घोषणा DN_DRC   4                      /* Discon. Rej. Complete*/
#घोषणा DN_CC    5                      /* Connect Confirm      */
#घोषणा DN_CI    6                      /* Connect Initiate     */
#घोषणा DN_NR    7                      /* No resources         */
#घोषणा DN_NC    8                      /* No communication     */
#घोषणा DN_CD    9                      /* Connect Delivery     */
#घोषणा DN_RJ    10                     /* Rejected             */
#घोषणा DN_RUN   11                     /* Running              */
#घोषणा DN_DI    12                     /* Disconnect Initiate  */
#घोषणा DN_DIC   13                     /* Disconnect Complete  */
#घोषणा DN_DN    14                     /* Disconnect Notअगरicat */
#घोषणा DN_CL    15                     /* Closed               */
#घोषणा DN_CN    16                     /* Closed Notअगरication  */

        __le16          addrloc;
        __le16          addrrem;
        __u16          numdat;
        __u16          numoth;
        __u16          numoth_rcv;
        __u16          numdat_rcv;
        __u16          ackxmt_dat;
        __u16          ackxmt_oth;
        __u16          ackrcv_dat;
        __u16          ackrcv_oth;
        __u8           flowrem_sw;
	__u8           flowloc_sw;
#घोषणा DN_SEND         2
#घोषणा DN_DONTSEND     1
#घोषणा DN_NOCHANGE     0
	__u16		flowrem_dat;
	__u16		flowrem_oth;
	__u16		flowloc_dat;
	__u16		flowloc_oth;
	__u8		services_rem;
	__u8		services_loc;
	__u8		info_rem;
	__u8		info_loc;

	__u16		segsize_rem;
	__u16		segsize_loc;

	__u8		nonagle;
	__u8		multi_ireq;
	__u8		accept_mode;
	अचिन्हित दीर्घ		seg_total; /* Running total of current segment */

	काष्ठा optdata_dn     conndata_in;
	काष्ठा optdata_dn     conndata_out;
	काष्ठा optdata_dn     discdata_in;
	काष्ठा optdata_dn     discdata_out;
        काष्ठा accessdata_dn  accessdata;

        काष्ठा sockaddr_dn addr; /* Local address  */
	काष्ठा sockaddr_dn peer; /* Remote address */

	/*
	 * In this हाल the RTT estimation is not specअगरied in the
	 * करोcs, nor is any back off algorithm. Here we follow well
	 * known tcp algorithms with a few small variations.
	 *
	 * snd_winकरोw: Max number of packets we send beक्रमe we रुको क्रम
	 *             an ack to come back. This will become part of a
	 *             more complicated scheme when we support flow
	 *             control.
	 *
	 * nsp_srtt:   Round-Trip-Time (x8) in jअगरfies. This is a rolling
	 *             average.
	 * nsp_rttvar: Round-Trip-Time-Varience (x4) in jअगरfies. This is the
	 *             varience of the smoothed average (but calculated in
	 *             a simpler way than क्रम normal statistical varience
	 *             calculations).
	 *
	 * nsp_rxtshअगरt: Backoff counter. Value is zero normally, each समय
	 *               a packet is lost is increases by one until an ack
	 *               is received. Its used to index an array of backoff
	 *               multipliers.
	 */
#घोषणा NSP_MIN_WINDOW 1
#घोषणा NSP_MAX_WINDOW (0x07fe)
	अचिन्हित दीर्घ max_winकरोw;
	अचिन्हित दीर्घ snd_winकरोw;
#घोषणा NSP_INITIAL_SRTT (HZ)
	अचिन्हित दीर्घ nsp_srtt;
#घोषणा NSP_INITIAL_RTTVAR (HZ*3)
	अचिन्हित दीर्घ nsp_rttvar;
#घोषणा NSP_MAXRXTSHIFT 12
	अचिन्हित दीर्घ nsp_rxtshअगरt;

	/*
	 * Output queues, one क्रम data, one क्रम otherdata/linkservice
	 */
	काष्ठा sk_buff_head data_xmit_queue;
	काष्ठा sk_buff_head other_xmit_queue;

	/*
	 * Input queue क्रम other data
	 */
	काष्ठा sk_buff_head other_receive_queue;
	पूर्णांक other_report;

	/*
	 * Stuff to करो with the slow समयr
	 */
	अचिन्हित दीर्घ stamp;          /* समय of last transmit */
	अचिन्हित दीर्घ persist;
	पूर्णांक (*persist_fxn)(काष्ठा sock *sk);
	अचिन्हित दीर्घ keepalive;
	व्योम (*keepalive_fxn)(काष्ठा sock *sk);

पूर्ण;

अटल अंतरभूत काष्ठा dn_scp *DN_SK(काष्ठा sock *sk)
अणु
	वापस (काष्ठा dn_scp *)(sk + 1);
पूर्ण

/*
 * src,dst : Source and Destination DECnet addresses
 * hops : Number of hops through the network
 * dst_port, src_port : NSP port numbers
 * services, info : Useful data extracted from conninit messages
 * rt_flags : Routing flags byte
 * nsp_flags : NSP layer flags byte
 * segsize : Size of segment
 * segnum : Number, क्रम data, otherdata and linkservice
 * xmit_count : Number of बार we've transmitted this skb
 * stamp : Time stamp of most recent transmission, used in RTT calculations
 * iअगर: Input पूर्णांकerface number
 *
 * As a general policy, this काष्ठाure keeps all addresses in network
 * byte order, and all अन्यथा in host byte order. Thus dst, src, dst_port
 * and src_port are in network order. All अन्यथा is in host order.
 * 
 */
#घोषणा DN_SKB_CB(skb) ((काष्ठा dn_skb_cb *)(skb)->cb)
काष्ठा dn_skb_cb अणु
	__le16 dst;
	__le16 src;
	__u16 hops;
	__le16 dst_port;
	__le16 src_port;
	__u8 services;
	__u8 info;
	__u8 rt_flags;
	__u8 nsp_flags;
	__u16 segsize;
	__u16 segnum;
	__u16 xmit_count;
	अचिन्हित दीर्घ stamp;
	पूर्णांक iअगर;
पूर्ण;

अटल अंतरभूत __le16 dn_eth2dn(अचिन्हित अक्षर *ethaddr)
अणु
	वापस get_unaligned((__le16 *)(ethaddr + 4));
पूर्ण

अटल अंतरभूत __le16 dn_saddr2dn(काष्ठा sockaddr_dn *saddr)
अणु
	वापस *(__le16 *)saddr->sdn_nodeaddr;
पूर्ण

अटल अंतरभूत व्योम dn_dn2eth(अचिन्हित अक्षर *ethaddr, __le16 addr)
अणु
	__u16 a = le16_to_cpu(addr);
	ethaddr[0] = 0xAA;
	ethaddr[1] = 0x00;
	ethaddr[2] = 0x04;
	ethaddr[3] = 0x00;
	ethaddr[4] = (__u8)(a & 0xff);
	ethaddr[5] = (__u8)(a >> 8);
पूर्ण

अटल अंतरभूत व्योम dn_sk_ports_copy(काष्ठा flowidn *fld, काष्ठा dn_scp *scp)
अणु
	fld->fld_sport = scp->addrloc;
	fld->fld_dport = scp->addrrem;
पूर्ण

अचिन्हित पूर्णांक dn_mss_from_pmtu(काष्ठा net_device *dev, पूर्णांक mtu);
व्योम dn_रेजिस्टर_sysctl(व्योम);
व्योम dn_unरेजिस्टर_sysctl(व्योम);

#घोषणा DN_MENUVER_ACC 0x01
#घोषणा DN_MENUVER_USR 0x02
#घोषणा DN_MENUVER_PRX 0x04
#घोषणा DN_MENUVER_UIC 0x08

काष्ठा sock *dn_sklist_find_listener(काष्ठा sockaddr_dn *addr);
काष्ठा sock *dn_find_by_skb(काष्ठा sk_buff *skb);
#घोषणा DN_ASCBUF_LEN 9
अक्षर *dn_addr2asc(__u16, अक्षर *);
पूर्णांक dn_destroy_समयr(काष्ठा sock *sk);

पूर्णांक dn_sockaddr2username(काष्ठा sockaddr_dn *addr, अचिन्हित अक्षर *buf,
			 अचिन्हित अक्षर type);
पूर्णांक dn_username2sockaddr(अचिन्हित अक्षर *data, पूर्णांक len, काष्ठा sockaddr_dn *addr,
			 अचिन्हित अक्षर *type);

व्योम dn_start_slow_समयr(काष्ठा sock *sk);
व्योम dn_stop_slow_समयr(काष्ठा sock *sk);

बाह्य __le16 decnet_address;
बाह्य पूर्णांक decnet_debug_level;
बाह्य पूर्णांक decnet_समय_रुको;
बाह्य पूर्णांक decnet_dn_count;
बाह्य पूर्णांक decnet_di_count;
बाह्य पूर्णांक decnet_dr_count;
बाह्य पूर्णांक decnet_no_fc_max_cwnd;

बाह्य दीर्घ sysctl_decnet_mem[3];
बाह्य पूर्णांक sysctl_decnet_wmem[3];
बाह्य पूर्णांक sysctl_decnet_rmem[3];

#पूर्ण_अगर /* _NET_DN_H */
