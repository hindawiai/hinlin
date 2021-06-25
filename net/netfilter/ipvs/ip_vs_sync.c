<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IPVS         An implementation of the IP भव server support क्रम the
 *              LINUX operating प्रणाली.  IPVS is now implemented as a module
 *              over the NetFilter framework. IPVS can be used to build a
 *              high-perक्रमmance and highly available server based on a
 *              cluster of servers.
 *
 * Version 1,   is capable of handling both version 0 and 1 messages.
 *              Version 0 is the plain old क्रमmat.
 *              Note Version 0 receivers will just drop Ver 1 messages.
 *              Version 1 is capable of handle IPv6, Persistence data,
 *              समय-outs, and firewall marks.
 *              In ver.1 "ip_vs_sync_conn_options" will be sent in netw. order.
 *              Ver. 0 can be turned on by sysctl -w net.ipv4.vs.sync_version=0
 *
 * Definitions  Message: is a complete datagram
 *              Sync_conn: is a part of a Message
 *              Param Data is an option to a Sync_conn.
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *
 * ip_vs_sync:  sync connection info from master load balancer to backups
 *              through multicast
 *
 * Changes:
 *	Alexandre Cassen	:	Added master & backup support at a समय.
 *	Alexandre Cassen	:	Added SyncID support क्रम incoming sync
 *					messages filtering.
 *	Justin Ossevoort	:	Fix endian problem on sync message size.
 *	Hans Schillstrom	:	Added Version 1: i.e. IPv6,
 *					Persistence support, fwmark and समय-out.
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/net.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/igmp.h>                 /* क्रम ip_mc_join_group */
#समावेश <linux/udp.h>
#समावेश <linux/err.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/unaligned.h>		/* Used क्रम ntoh_seq and hton_seq */

#समावेश <net/ip.h>
#समावेश <net/sock.h>

#समावेश <net/ip_vs.h>

#घोषणा IP_VS_SYNC_GROUP 0xe0000051    /* multicast addr - 224.0.0.81 */
#घोषणा IP_VS_SYNC_PORT  8848          /* multicast port */

#घोषणा SYNC_PROTO_VER  1		/* Protocol version in header */

अटल काष्ठा lock_class_key __ipvs_sync_key;
/*
 *	IPVS sync connection entry
 *	Version 0, i.e. original version.
 */
काष्ठा ip_vs_sync_conn_v0 अणु
	__u8			reserved;

	/* Protocol, addresses and port numbers */
	__u8			protocol;       /* Which protocol (TCP/UDP) */
	__be16			cport;
	__be16                  vport;
	__be16                  dport;
	__be32                  caddr;          /* client address */
	__be32                  vaddr;          /* भव address */
	__be32                  daddr;          /* destination address */

	/* Flags and state transition */
	__be16                  flags;          /* status flags */
	__be16                  state;          /* state info */

	/* The sequence options start here */
पूर्ण;

काष्ठा ip_vs_sync_conn_options अणु
	काष्ठा ip_vs_seq        in_seq;         /* incoming seq. काष्ठा */
	काष्ठा ip_vs_seq        out_seq;        /* outgoing seq. काष्ठा */
पूर्ण;

/*
     Sync Connection क्रमmat (sync_conn)

       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |    Type       |    Protocol   | Ver.  |        Size           |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                             Flags                             |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |            State              |         cport                 |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |            vport              |         dport                 |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                             fwmark                            |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                             समयout  (in sec.)                |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                              ...                              |
      |                        IP-Addresses  (v4 or v6)               |
      |                              ...                              |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  Optional Parameters.
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      | Param. Type    | Param. Length |   Param. data                |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                               |
      |                              ...                              |
      |                               +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                               | Param Type    | Param. Length |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                           Param  data                         |
      |         Last Param data should be padded क्रम 32 bit alignment |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

/*
 *  Type 0, IPv4 sync connection क्रमmat
 */
काष्ठा ip_vs_sync_v4 अणु
	__u8			type;
	__u8			protocol;	/* Which protocol (TCP/UDP) */
	__be16			ver_size;	/* Version msb 4 bits */
	/* Flags and state transition */
	__be32			flags;		/* status flags */
	__be16			state;		/* state info 	*/
	/* Protocol, addresses and port numbers */
	__be16			cport;
	__be16			vport;
	__be16			dport;
	__be32			fwmark;		/* Firewall mark from skb */
	__be32			समयout;	/* cp समयout */
	__be32			caddr;		/* client address */
	__be32			vaddr;		/* भव address */
	__be32			daddr;		/* destination address */
	/* The sequence options start here */
	/* PE data padded to 32bit alignment after seq. options */
पूर्ण;
/*
 * Type 2 messages IPv6
 */
काष्ठा ip_vs_sync_v6 अणु
	__u8			type;
	__u8			protocol;	/* Which protocol (TCP/UDP) */
	__be16			ver_size;	/* Version msb 4 bits */
	/* Flags and state transition */
	__be32			flags;		/* status flags */
	__be16			state;		/* state info 	*/
	/* Protocol, addresses and port numbers */
	__be16			cport;
	__be16			vport;
	__be16			dport;
	__be32			fwmark;		/* Firewall mark from skb */
	__be32			समयout;	/* cp समयout */
	काष्ठा in6_addr		caddr;		/* client address */
	काष्ठा in6_addr		vaddr;		/* भव address */
	काष्ठा in6_addr		daddr;		/* destination address */
	/* The sequence options start here */
	/* PE data padded to 32bit alignment after seq. options */
पूर्ण;

जोड़ ip_vs_sync_conn अणु
	काष्ठा ip_vs_sync_v4	v4;
	काष्ठा ip_vs_sync_v6	v6;
पूर्ण;

/* Bits in Type field in above */
#घोषणा STYPE_INET6		0
#घोषणा STYPE_F_INET6		(1 << STYPE_INET6)

#घोषणा SVER_SHIFT		12		/* Shअगरt to get version */
#घोषणा SVER_MASK		0x0fff		/* Mask to strip version */

#घोषणा IPVS_OPT_SEQ_DATA	1
#घोषणा IPVS_OPT_PE_DATA	2
#घोषणा IPVS_OPT_PE_NAME	3
#घोषणा IPVS_OPT_PARAM		7

#घोषणा IPVS_OPT_F_SEQ_DATA	(1 << (IPVS_OPT_SEQ_DATA-1))
#घोषणा IPVS_OPT_F_PE_DATA	(1 << (IPVS_OPT_PE_DATA-1))
#घोषणा IPVS_OPT_F_PE_NAME	(1 << (IPVS_OPT_PE_NAME-1))
#घोषणा IPVS_OPT_F_PARAM	(1 << (IPVS_OPT_PARAM-1))

काष्ठा ip_vs_sync_thपढ़ो_data अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा netns_ipvs *ipvs;
	काष्ठा socket *sock;
	अक्षर *buf;
	पूर्णांक id;
पूर्ण;

/* Version 0 definition of packet sizes */
#घोषणा SIMPLE_CONN_SIZE  (माप(काष्ठा ip_vs_sync_conn_v0))
#घोषणा FULL_CONN_SIZE  \
(माप(काष्ठा ip_vs_sync_conn_v0) + माप(काष्ठा ip_vs_sync_conn_options))


/*
  The master mulitcasts messages (Datagrams) to the backup load balancers
  in the following क्रमmat.

 Version 1:
  Note, first byte should be Zero, so ver 0 receivers will drop the packet.

       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |      0        |    SyncID     |            Size               |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |  Count Conns  |    Version    |    Reserved, set to Zero      |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                                                               |
      |                    IPVS Sync Connection (1)                   |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                            .                                  |
      ~                            .                                  ~
      |                            .                                  |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                                                               |
      |                    IPVS Sync Connection (n)                   |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

 Version 0 Header
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |  Count Conns  |    SyncID     |            Size               |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                    IPVS Sync Connection (1)                   |
*/

/* Version 0 header */
काष्ठा ip_vs_sync_mesg_v0 अणु
	__u8                    nr_conns;
	__u8                    syncid;
	__be16                  size;

	/* ip_vs_sync_conn entries start here */
पूर्ण;

/* Version 1 header */
काष्ठा ip_vs_sync_mesg अणु
	__u8			reserved;	/* must be zero */
	__u8			syncid;
	__be16			size;
	__u8			nr_conns;
	__s8			version;	/* SYNC_PROTO_VER  */
	__u16			spare;
	/* ip_vs_sync_conn entries start here */
पूर्ण;

जोड़ ipvs_sockaddr अणु
	काष्ठा sockaddr_in	in;
	काष्ठा sockaddr_in6	in6;
पूर्ण;

काष्ठा ip_vs_sync_buff अणु
	काष्ठा list_head        list;
	अचिन्हित दीर्घ           firstuse;

	/* poपूर्णांकers क्रम the message data */
	काष्ठा ip_vs_sync_mesg  *mesg;
	अचिन्हित अक्षर           *head;
	अचिन्हित अक्षर           *end;
पूर्ण;

/*
 * Copy of काष्ठा ip_vs_seq
 * From unaligned network order to aligned host order
 */
अटल व्योम ntoh_seq(काष्ठा ip_vs_seq *no, काष्ठा ip_vs_seq *ho)
अणु
	स_रखो(ho, 0, माप(*ho));
	ho->init_seq       = get_unaligned_be32(&no->init_seq);
	ho->delta          = get_unaligned_be32(&no->delta);
	ho->previous_delta = get_unaligned_be32(&no->previous_delta);
पूर्ण

/*
 * Copy of काष्ठा ip_vs_seq
 * From Aligned host order to unaligned network order
 */
अटल व्योम hton_seq(काष्ठा ip_vs_seq *ho, काष्ठा ip_vs_seq *no)
अणु
	put_unaligned_be32(ho->init_seq, &no->init_seq);
	put_unaligned_be32(ho->delta, &no->delta);
	put_unaligned_be32(ho->previous_delta, &no->previous_delta);
पूर्ण

अटल अंतरभूत काष्ठा ip_vs_sync_buff *
sb_dequeue(काष्ठा netns_ipvs *ipvs, काष्ठा ipvs_master_sync_state *ms)
अणु
	काष्ठा ip_vs_sync_buff *sb;

	spin_lock_bh(&ipvs->sync_lock);
	अगर (list_empty(&ms->sync_queue)) अणु
		sb = शून्य;
		__set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण अन्यथा अणु
		sb = list_entry(ms->sync_queue.next, काष्ठा ip_vs_sync_buff,
				list);
		list_del(&sb->list);
		ms->sync_queue_len--;
		अगर (!ms->sync_queue_len)
			ms->sync_queue_delay = 0;
	पूर्ण
	spin_unlock_bh(&ipvs->sync_lock);

	वापस sb;
पूर्ण

/*
 * Create a new sync buffer क्रम Version 1 proto.
 */
अटल अंतरभूत काष्ठा ip_vs_sync_buff *
ip_vs_sync_buff_create(काष्ठा netns_ipvs *ipvs, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ip_vs_sync_buff *sb;

	अगर (!(sb=kदो_स्मृति(माप(काष्ठा ip_vs_sync_buff), GFP_ATOMIC)))
		वापस शून्य;

	len = max_t(अचिन्हित पूर्णांक, len + माप(काष्ठा ip_vs_sync_mesg),
		    ipvs->mcfg.sync_maxlen);
	sb->mesg = kदो_स्मृति(len, GFP_ATOMIC);
	अगर (!sb->mesg) अणु
		kमुक्त(sb);
		वापस शून्य;
	पूर्ण
	sb->mesg->reserved = 0;  /* old nr_conns i.e. must be zero now */
	sb->mesg->version = SYNC_PROTO_VER;
	sb->mesg->syncid = ipvs->mcfg.syncid;
	sb->mesg->size = htons(माप(काष्ठा ip_vs_sync_mesg));
	sb->mesg->nr_conns = 0;
	sb->mesg->spare = 0;
	sb->head = (अचिन्हित अक्षर *)sb->mesg + माप(काष्ठा ip_vs_sync_mesg);
	sb->end = (अचिन्हित अक्षर *)sb->mesg + len;

	sb->firstuse = jअगरfies;
	वापस sb;
पूर्ण

अटल अंतरभूत व्योम ip_vs_sync_buff_release(काष्ठा ip_vs_sync_buff *sb)
अणु
	kमुक्त(sb->mesg);
	kमुक्त(sb);
पूर्ण

अटल अंतरभूत व्योम sb_queue_tail(काष्ठा netns_ipvs *ipvs,
				 काष्ठा ipvs_master_sync_state *ms)
अणु
	काष्ठा ip_vs_sync_buff *sb = ms->sync_buff;

	spin_lock(&ipvs->sync_lock);
	अगर (ipvs->sync_state & IP_VS_STATE_MASTER &&
	    ms->sync_queue_len < sysctl_sync_qlen_max(ipvs)) अणु
		अगर (!ms->sync_queue_len)
			schedule_delayed_work(&ms->master_wakeup_work,
					      max(IPVS_SYNC_SEND_DELAY, 1));
		ms->sync_queue_len++;
		list_add_tail(&sb->list, &ms->sync_queue);
		अगर ((++ms->sync_queue_delay) == IPVS_SYNC_WAKEUP_RATE) अणु
			पूर्णांक id = (पूर्णांक)(ms - ipvs->ms);

			wake_up_process(ipvs->master_tinfo[id].task);
		पूर्ण
	पूर्ण अन्यथा
		ip_vs_sync_buff_release(sb);
	spin_unlock(&ipvs->sync_lock);
पूर्ण

/*
 *	Get the current sync buffer अगर it has been created क्रम more
 *	than the specअगरied समय or the specअगरied समय is zero.
 */
अटल अंतरभूत काष्ठा ip_vs_sync_buff *
get_curr_sync_buff(काष्ठा netns_ipvs *ipvs, काष्ठा ipvs_master_sync_state *ms,
		   अचिन्हित दीर्घ समय)
अणु
	काष्ठा ip_vs_sync_buff *sb;

	spin_lock_bh(&ipvs->sync_buff_lock);
	sb = ms->sync_buff;
	अगर (sb && समय_after_eq(jअगरfies - sb->firstuse, समय)) अणु
		ms->sync_buff = शून्य;
		__set_current_state(TASK_RUNNING);
	पूर्ण अन्यथा
		sb = शून्य;
	spin_unlock_bh(&ipvs->sync_buff_lock);
	वापस sb;
पूर्ण

अटल अंतरभूत पूर्णांक
select_master_thपढ़ो_id(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_conn *cp)
अणु
	वापस ((दीर्घ) cp >> (1 + ilog2(माप(*cp)))) & ipvs->thपढ़ोs_mask;
पूर्ण

/*
 * Create a new sync buffer क्रम Version 0 proto.
 */
अटल अंतरभूत काष्ठा ip_vs_sync_buff *
ip_vs_sync_buff_create_v0(काष्ठा netns_ipvs *ipvs, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ip_vs_sync_buff *sb;
	काष्ठा ip_vs_sync_mesg_v0 *mesg;

	अगर (!(sb=kदो_स्मृति(माप(काष्ठा ip_vs_sync_buff), GFP_ATOMIC)))
		वापस शून्य;

	len = max_t(अचिन्हित पूर्णांक, len + माप(काष्ठा ip_vs_sync_mesg_v0),
		    ipvs->mcfg.sync_maxlen);
	sb->mesg = kदो_स्मृति(len, GFP_ATOMIC);
	अगर (!sb->mesg) अणु
		kमुक्त(sb);
		वापस शून्य;
	पूर्ण
	mesg = (काष्ठा ip_vs_sync_mesg_v0 *)sb->mesg;
	mesg->nr_conns = 0;
	mesg->syncid = ipvs->mcfg.syncid;
	mesg->size = htons(माप(काष्ठा ip_vs_sync_mesg_v0));
	sb->head = (अचिन्हित अक्षर *)mesg + माप(काष्ठा ip_vs_sync_mesg_v0);
	sb->end = (अचिन्हित अक्षर *)mesg + len;
	sb->firstuse = jअगरfies;
	वापस sb;
पूर्ण

/* Check अगर connection is controlled by persistence */
अटल अंतरभूत bool in_persistence(काष्ठा ip_vs_conn *cp)
अणु
	क्रम (cp = cp->control; cp; cp = cp->control) अणु
		अगर (cp->flags & IP_VS_CONN_F_TEMPLATE)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Check अगर conn should be synced.
 * pkts: conn packets, use sysctl_sync_threshold to aव्योम packet check
 * - (1) sync_refresh_period: reduce sync rate. Additionally, retry
 *	sync_retries बार with period of sync_refresh_period/8
 * - (2) अगर both sync_refresh_period and sync_period are 0 send sync only
 *	क्रम state changes or only once when pkts matches sync_threshold
 * - (3) ढाँचाs: rate can be reduced only with sync_refresh_period or
 *	with (2)
 */
अटल पूर्णांक ip_vs_sync_conn_needed(काष्ठा netns_ipvs *ipvs,
				  काष्ठा ip_vs_conn *cp, पूर्णांक pkts)
अणु
	अचिन्हित दीर्घ orig = READ_ONCE(cp->sync_endसमय);
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ n = (now + cp->समयout) & ~3UL;
	अचिन्हित पूर्णांक sync_refresh_period;
	पूर्णांक sync_period;
	पूर्णांक क्रमce;

	/* Check अगर we sync in current state */
	अगर (unlikely(cp->flags & IP_VS_CONN_F_TEMPLATE))
		क्रमce = 0;
	अन्यथा अगर (unlikely(sysctl_sync_persist_mode(ipvs) && in_persistence(cp)))
		वापस 0;
	अन्यथा अगर (likely(cp->protocol == IPPROTO_TCP)) अणु
		अगर (!((1 << cp->state) &
		      ((1 << IP_VS_TCP_S_ESTABLISHED) |
		       (1 << IP_VS_TCP_S_FIN_WAIT) |
		       (1 << IP_VS_TCP_S_CLOSE) |
		       (1 << IP_VS_TCP_S_CLOSE_WAIT) |
		       (1 << IP_VS_TCP_S_TIME_WAIT))))
			वापस 0;
		क्रमce = cp->state != cp->old_state;
		अगर (क्रमce && cp->state != IP_VS_TCP_S_ESTABLISHED)
			जाओ set;
	पूर्ण अन्यथा अगर (unlikely(cp->protocol == IPPROTO_SCTP)) अणु
		अगर (!((1 << cp->state) &
		      ((1 << IP_VS_SCTP_S_ESTABLISHED) |
		       (1 << IP_VS_SCTP_S_SHUTDOWN_SENT) |
		       (1 << IP_VS_SCTP_S_SHUTDOWN_RECEIVED) |
		       (1 << IP_VS_SCTP_S_SHUTDOWN_ACK_SENT) |
		       (1 << IP_VS_SCTP_S_CLOSED))))
			वापस 0;
		क्रमce = cp->state != cp->old_state;
		अगर (क्रमce && cp->state != IP_VS_SCTP_S_ESTABLISHED)
			जाओ set;
	पूर्ण अन्यथा अणु
		/* UDP or another protocol with single state */
		क्रमce = 0;
	पूर्ण

	sync_refresh_period = sysctl_sync_refresh_period(ipvs);
	अगर (sync_refresh_period > 0) अणु
		दीर्घ dअगरf = n - orig;
		दीर्घ min_dअगरf = max(cp->समयout >> 1, 10UL * HZ);

		/* Aव्योम sync अगर dअगरference is below sync_refresh_period
		 * and below the half समयout.
		 */
		अगर (असल(dअगरf) < min_t(दीर्घ, sync_refresh_period, min_dअगरf)) अणु
			पूर्णांक retries = orig & 3;

			अगर (retries >= sysctl_sync_retries(ipvs))
				वापस 0;
			अगर (समय_beक्रमe(now, orig - cp->समयout +
					(sync_refresh_period >> 3)))
				वापस 0;
			n |= retries + 1;
		पूर्ण
	पूर्ण
	sync_period = sysctl_sync_period(ipvs);
	अगर (sync_period > 0) अणु
		अगर (!(cp->flags & IP_VS_CONN_F_TEMPLATE) &&
		    pkts % sync_period != sysctl_sync_threshold(ipvs))
			वापस 0;
	पूर्ण अन्यथा अगर (!sync_refresh_period &&
		   pkts != sysctl_sync_threshold(ipvs))
		वापस 0;

set:
	cp->old_state = cp->state;
	n = cmpxchg(&cp->sync_endसमय, orig, n);
	वापस n == orig || क्रमce;
पूर्ण

/*
 *      Version 0 , could be चयनed in by sys_ctl.
 *      Add an ip_vs_conn inक्रमmation पूर्णांकo the current sync_buff.
 */
अटल व्योम ip_vs_sync_conn_v0(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_conn *cp,
			       पूर्णांक pkts)
अणु
	काष्ठा ip_vs_sync_mesg_v0 *m;
	काष्ठा ip_vs_sync_conn_v0 *s;
	काष्ठा ip_vs_sync_buff *buff;
	काष्ठा ipvs_master_sync_state *ms;
	पूर्णांक id;
	अचिन्हित पूर्णांक len;

	अगर (unlikely(cp->af != AF_INET))
		वापस;
	/* Do not sync ONE PACKET */
	अगर (cp->flags & IP_VS_CONN_F_ONE_PACKET)
		वापस;

	अगर (!ip_vs_sync_conn_needed(ipvs, cp, pkts))
		वापस;

	spin_lock_bh(&ipvs->sync_buff_lock);
	अगर (!(ipvs->sync_state & IP_VS_STATE_MASTER)) अणु
		spin_unlock_bh(&ipvs->sync_buff_lock);
		वापस;
	पूर्ण

	id = select_master_thपढ़ो_id(ipvs, cp);
	ms = &ipvs->ms[id];
	buff = ms->sync_buff;
	len = (cp->flags & IP_VS_CONN_F_SEQ_MASK) ? FULL_CONN_SIZE :
		SIMPLE_CONN_SIZE;
	अगर (buff) अणु
		m = (काष्ठा ip_vs_sync_mesg_v0 *) buff->mesg;
		/* Send buffer अगर it is क्रम v1 */
		अगर (buff->head + len > buff->end || !m->nr_conns) अणु
			sb_queue_tail(ipvs, ms);
			ms->sync_buff = शून्य;
			buff = शून्य;
		पूर्ण
	पूर्ण
	अगर (!buff) अणु
		buff = ip_vs_sync_buff_create_v0(ipvs, len);
		अगर (!buff) अणु
			spin_unlock_bh(&ipvs->sync_buff_lock);
			pr_err("ip_vs_sync_buff_create failed.\n");
			वापस;
		पूर्ण
		ms->sync_buff = buff;
	पूर्ण

	m = (काष्ठा ip_vs_sync_mesg_v0 *) buff->mesg;
	s = (काष्ठा ip_vs_sync_conn_v0 *) buff->head;

	/* copy members */
	s->reserved = 0;
	s->protocol = cp->protocol;
	s->cport = cp->cport;
	s->vport = cp->vport;
	s->dport = cp->dport;
	s->caddr = cp->caddr.ip;
	s->vaddr = cp->vaddr.ip;
	s->daddr = cp->daddr.ip;
	s->flags = htons(cp->flags & ~IP_VS_CONN_F_HASHED);
	s->state = htons(cp->state);
	अगर (cp->flags & IP_VS_CONN_F_SEQ_MASK) अणु
		काष्ठा ip_vs_sync_conn_options *opt =
			(काष्ठा ip_vs_sync_conn_options *)&s[1];
		स_नकल(opt, &cp->in_seq, माप(*opt));
	पूर्ण

	m->nr_conns++;
	m->size = htons(ntohs(m->size) + len);
	buff->head += len;
	spin_unlock_bh(&ipvs->sync_buff_lock);

	/* synchronize its controller अगर it has */
	cp = cp->control;
	अगर (cp) अणु
		अगर (cp->flags & IP_VS_CONN_F_TEMPLATE)
			pkts = atomic_inc_वापस(&cp->in_pkts);
		अन्यथा
			pkts = sysctl_sync_threshold(ipvs);
		ip_vs_sync_conn(ipvs, cp, pkts);
	पूर्ण
पूर्ण

/*
 *      Add an ip_vs_conn inक्रमmation पूर्णांकo the current sync_buff.
 *      Called by ip_vs_in.
 *      Sending Version 1 messages
 */
व्योम ip_vs_sync_conn(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_conn *cp, पूर्णांक pkts)
अणु
	काष्ठा ip_vs_sync_mesg *m;
	जोड़ ip_vs_sync_conn *s;
	काष्ठा ip_vs_sync_buff *buff;
	काष्ठा ipvs_master_sync_state *ms;
	पूर्णांक id;
	__u8 *p;
	अचिन्हित पूर्णांक len, pe_name_len, pad;

	/* Handle old version of the protocol */
	अगर (sysctl_sync_ver(ipvs) == 0) अणु
		ip_vs_sync_conn_v0(ipvs, cp, pkts);
		वापस;
	पूर्ण
	/* Do not sync ONE PACKET */
	अगर (cp->flags & IP_VS_CONN_F_ONE_PACKET)
		जाओ control;
sloop:
	अगर (!ip_vs_sync_conn_needed(ipvs, cp, pkts))
		जाओ control;

	/* Sanity checks */
	pe_name_len = 0;
	अगर (cp->pe_data_len) अणु
		अगर (!cp->pe_data || !cp->dest) अणु
			IP_VS_ERR_RL("SYNC, connection pe_data invalid\n");
			वापस;
		पूर्ण
		pe_name_len = strnlen(cp->pe->name, IP_VS_PENAME_MAXLEN);
	पूर्ण

	spin_lock_bh(&ipvs->sync_buff_lock);
	अगर (!(ipvs->sync_state & IP_VS_STATE_MASTER)) अणु
		spin_unlock_bh(&ipvs->sync_buff_lock);
		वापस;
	पूर्ण

	id = select_master_thपढ़ो_id(ipvs, cp);
	ms = &ipvs->ms[id];

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (cp->af == AF_INET6)
		len = माप(काष्ठा ip_vs_sync_v6);
	अन्यथा
#पूर्ण_अगर
		len = माप(काष्ठा ip_vs_sync_v4);

	अगर (cp->flags & IP_VS_CONN_F_SEQ_MASK)
		len += माप(काष्ठा ip_vs_sync_conn_options) + 2;

	अगर (cp->pe_data_len)
		len += cp->pe_data_len + 2;	/* + Param hdr field */
	अगर (pe_name_len)
		len += pe_name_len + 2;

	/* check अगर there is a space क्रम this one  */
	pad = 0;
	buff = ms->sync_buff;
	अगर (buff) अणु
		m = buff->mesg;
		pad = (4 - (माप_प्रकार) buff->head) & 3;
		/* Send buffer अगर it is क्रम v0 */
		अगर (buff->head + len + pad > buff->end || m->reserved) अणु
			sb_queue_tail(ipvs, ms);
			ms->sync_buff = शून्य;
			buff = शून्य;
			pad = 0;
		पूर्ण
	पूर्ण

	अगर (!buff) अणु
		buff = ip_vs_sync_buff_create(ipvs, len);
		अगर (!buff) अणु
			spin_unlock_bh(&ipvs->sync_buff_lock);
			pr_err("ip_vs_sync_buff_create failed.\n");
			वापस;
		पूर्ण
		ms->sync_buff = buff;
		m = buff->mesg;
	पूर्ण

	p = buff->head;
	buff->head += pad + len;
	m->size = htons(ntohs(m->size) + pad + len);
	/* Add ev. padding from prev. sync_conn */
	जबतक (pad--)
		*(p++) = 0;

	s = (जोड़ ip_vs_sync_conn *)p;

	/* Set message type  & copy members */
	s->v4.type = (cp->af == AF_INET6 ? STYPE_F_INET6 : 0);
	s->v4.ver_size = htons(len & SVER_MASK);	/* Version 0 */
	s->v4.flags = htonl(cp->flags & ~IP_VS_CONN_F_HASHED);
	s->v4.state = htons(cp->state);
	s->v4.protocol = cp->protocol;
	s->v4.cport = cp->cport;
	s->v4.vport = cp->vport;
	s->v4.dport = cp->dport;
	s->v4.fwmark = htonl(cp->fwmark);
	s->v4.समयout = htonl(cp->समयout / HZ);
	m->nr_conns++;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (cp->af == AF_INET6) अणु
		p += माप(काष्ठा ip_vs_sync_v6);
		s->v6.caddr = cp->caddr.in6;
		s->v6.vaddr = cp->vaddr.in6;
		s->v6.daddr = cp->daddr.in6;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		p += माप(काष्ठा ip_vs_sync_v4);	/* options ptr */
		s->v4.caddr = cp->caddr.ip;
		s->v4.vaddr = cp->vaddr.ip;
		s->v4.daddr = cp->daddr.ip;
	पूर्ण
	अगर (cp->flags & IP_VS_CONN_F_SEQ_MASK) अणु
		*(p++) = IPVS_OPT_SEQ_DATA;
		*(p++) = माप(काष्ठा ip_vs_sync_conn_options);
		hton_seq((काष्ठा ip_vs_seq *)p, &cp->in_seq);
		p += माप(काष्ठा ip_vs_seq);
		hton_seq((काष्ठा ip_vs_seq *)p, &cp->out_seq);
		p += माप(काष्ठा ip_vs_seq);
	पूर्ण
	/* Handle pe data */
	अगर (cp->pe_data_len && cp->pe_data) अणु
		*(p++) = IPVS_OPT_PE_DATA;
		*(p++) = cp->pe_data_len;
		स_नकल(p, cp->pe_data, cp->pe_data_len);
		p += cp->pe_data_len;
		अगर (pe_name_len) अणु
			/* Add PE_NAME */
			*(p++) = IPVS_OPT_PE_NAME;
			*(p++) = pe_name_len;
			स_नकल(p, cp->pe->name, pe_name_len);
			p += pe_name_len;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ipvs->sync_buff_lock);

control:
	/* synchronize its controller अगर it has */
	cp = cp->control;
	अगर (!cp)
		वापस;
	अगर (cp->flags & IP_VS_CONN_F_TEMPLATE)
		pkts = atomic_inc_वापस(&cp->in_pkts);
	अन्यथा
		pkts = sysctl_sync_threshold(ipvs);
	जाओ sloop;
पूर्ण

/*
 *  fill_param used by version 1
 */
अटल अंतरभूत पूर्णांक
ip_vs_conn_fill_param_sync(काष्ठा netns_ipvs *ipvs, पूर्णांक af, जोड़ ip_vs_sync_conn *sc,
			   काष्ठा ip_vs_conn_param *p,
			   __u8 *pe_data, अचिन्हित पूर्णांक pe_data_len,
			   __u8 *pe_name, अचिन्हित पूर्णांक pe_name_len)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		ip_vs_conn_fill_param(ipvs, af, sc->v6.protocol,
				      (स्थिर जोड़ nf_inet_addr *)&sc->v6.caddr,
				      sc->v6.cport,
				      (स्थिर जोड़ nf_inet_addr *)&sc->v6.vaddr,
				      sc->v6.vport, p);
	अन्यथा
#पूर्ण_अगर
		ip_vs_conn_fill_param(ipvs, af, sc->v4.protocol,
				      (स्थिर जोड़ nf_inet_addr *)&sc->v4.caddr,
				      sc->v4.cport,
				      (स्थिर जोड़ nf_inet_addr *)&sc->v4.vaddr,
				      sc->v4.vport, p);
	/* Handle pe data */
	अगर (pe_data_len) अणु
		अगर (pe_name_len) अणु
			अक्षर buff[IP_VS_PENAME_MAXLEN+1];

			स_नकल(buff, pe_name, pe_name_len);
			buff[pe_name_len]=0;
			p->pe = __ip_vs_pe_getbyname(buff);
			अगर (!p->pe) अणु
				IP_VS_DBG(3, "BACKUP, no %s engine found/loaded\n",
					     buff);
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			IP_VS_ERR_RL("BACKUP, Invalid PE parameters\n");
			वापस 1;
		पूर्ण

		p->pe_data = kmemdup(pe_data, pe_data_len, GFP_ATOMIC);
		अगर (!p->pe_data) अणु
			module_put(p->pe->module);
			वापस -ENOMEM;
		पूर्ण
		p->pe_data_len = pe_data_len;
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  Connection Add / Update.
 *  Common क्रम version 0 and 1 reception of backup sync_conns.
 *  Param: ...
 *         समयout is in sec.
 */
अटल व्योम ip_vs_proc_conn(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_conn_param *param,
			    अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक state,
			    अचिन्हित पूर्णांक protocol, अचिन्हित पूर्णांक type,
			    स्थिर जोड़ nf_inet_addr *daddr, __be16 dport,
			    अचिन्हित दीर्घ समयout, __u32 fwmark,
			    काष्ठा ip_vs_sync_conn_options *opt)
अणु
	काष्ठा ip_vs_dest *dest;
	काष्ठा ip_vs_conn *cp;

	अगर (!(flags & IP_VS_CONN_F_TEMPLATE)) अणु
		cp = ip_vs_conn_in_get(param);
		अगर (cp && ((cp->dport != dport) ||
			   !ip_vs_addr_equal(cp->daf, &cp->daddr, daddr))) अणु
			अगर (!(flags & IP_VS_CONN_F_INACTIVE)) अणु
				ip_vs_conn_expire_now(cp);
				__ip_vs_conn_put(cp);
				cp = शून्य;
			पूर्ण अन्यथा अणु
				/* This is the expiration message क्रम the
				 * connection that was alपढ़ोy replaced, so we
				 * just ignore it.
				 */
				__ip_vs_conn_put(cp);
				kमुक्त(param->pe_data);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		cp = ip_vs_ct_in_get(param);
	पूर्ण

	अगर (cp) अणु
		/* Free pe_data */
		kमुक्त(param->pe_data);

		dest = cp->dest;
		spin_lock_bh(&cp->lock);
		अगर ((cp->flags ^ flags) & IP_VS_CONN_F_INACTIVE &&
		    !(flags & IP_VS_CONN_F_TEMPLATE) && dest) अणु
			अगर (flags & IP_VS_CONN_F_INACTIVE) अणु
				atomic_dec(&dest->activeconns);
				atomic_inc(&dest->inactconns);
			पूर्ण अन्यथा अणु
				atomic_inc(&dest->activeconns);
				atomic_dec(&dest->inactconns);
			पूर्ण
		पूर्ण
		flags &= IP_VS_CONN_F_BACKUP_UPD_MASK;
		flags |= cp->flags & ~IP_VS_CONN_F_BACKUP_UPD_MASK;
		cp->flags = flags;
		spin_unlock_bh(&cp->lock);
		अगर (!dest)
			ip_vs_try_bind_dest(cp);
	पूर्ण अन्यथा अणु
		/*
		 * Find the appropriate destination क्रम the connection.
		 * If it is not found the connection will reमुख्य unbound
		 * but still handled.
		 */
		rcu_पढ़ो_lock();
		/* This function is only invoked by the synchronization
		 * code. We करो not currently support heterogeneous pools
		 * with synchronization, so we can make the assumption that
		 * the svc_af is the same as the dest_af
		 */
		dest = ip_vs_find_dest(ipvs, type, type, daddr, dport,
				       param->vaddr, param->vport, protocol,
				       fwmark, flags);

		cp = ip_vs_conn_new(param, type, daddr, dport, flags, dest,
				    fwmark);
		rcu_पढ़ो_unlock();
		अगर (!cp) अणु
			kमुक्त(param->pe_data);
			IP_VS_DBG(2, "BACKUP, add new conn. failed\n");
			वापस;
		पूर्ण
		अगर (!(flags & IP_VS_CONN_F_TEMPLATE))
			kमुक्त(param->pe_data);
	पूर्ण

	अगर (opt) अणु
		cp->in_seq = opt->in_seq;
		cp->out_seq = opt->out_seq;
	पूर्ण
	atomic_set(&cp->in_pkts, sysctl_sync_threshold(ipvs));
	cp->state = state;
	cp->old_state = cp->state;
	/*
	 * For Ver 0 messages style
	 *  - Not possible to recover the right समयout क्रम ढाँचाs
	 *  - can not find the right fwmark
	 *    भव service. If needed, we can करो it क्रम
	 *    non-fwmark persistent services.
	 * Ver 1 messages style.
	 *  - No problem.
	 */
	अगर (समयout) अणु
		अगर (समयout > MAX_SCHEDULE_TIMEOUT / HZ)
			समयout = MAX_SCHEDULE_TIMEOUT / HZ;
		cp->समयout = समयout*HZ;
	पूर्ण अन्यथा अणु
		काष्ठा ip_vs_proto_data *pd;

		pd = ip_vs_proto_data_get(ipvs, protocol);
		अगर (!(flags & IP_VS_CONN_F_TEMPLATE) && pd && pd->समयout_table)
			cp->समयout = pd->समयout_table[state];
		अन्यथा
			cp->समयout = (3*60*HZ);
	पूर्ण
	ip_vs_conn_put(cp);
पूर्ण

/*
 *  Process received multicast message क्रम Version 0
 */
अटल व्योम ip_vs_process_message_v0(काष्ठा netns_ipvs *ipvs, स्थिर अक्षर *buffer,
				     स्थिर माप_प्रकार buflen)
अणु
	काष्ठा ip_vs_sync_mesg_v0 *m = (काष्ठा ip_vs_sync_mesg_v0 *)buffer;
	काष्ठा ip_vs_sync_conn_v0 *s;
	काष्ठा ip_vs_sync_conn_options *opt;
	काष्ठा ip_vs_protocol *pp;
	काष्ठा ip_vs_conn_param param;
	अक्षर *p;
	पूर्णांक i;

	p = (अक्षर *)buffer + माप(काष्ठा ip_vs_sync_mesg_v0);
	क्रम (i=0; i<m->nr_conns; i++) अणु
		अचिन्हित पूर्णांक flags, state;

		अगर (p + SIMPLE_CONN_SIZE > buffer+buflen) अणु
			IP_VS_ERR_RL("BACKUP v0, bogus conn\n");
			वापस;
		पूर्ण
		s = (काष्ठा ip_vs_sync_conn_v0 *) p;
		flags = ntohs(s->flags) | IP_VS_CONN_F_SYNC;
		flags &= ~IP_VS_CONN_F_HASHED;
		अगर (flags & IP_VS_CONN_F_SEQ_MASK) अणु
			opt = (काष्ठा ip_vs_sync_conn_options *)&s[1];
			p += FULL_CONN_SIZE;
			अगर (p > buffer+buflen) अणु
				IP_VS_ERR_RL("BACKUP v0, Dropping buffer bogus conn options\n");
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			opt = शून्य;
			p += SIMPLE_CONN_SIZE;
		पूर्ण

		state = ntohs(s->state);
		अगर (!(flags & IP_VS_CONN_F_TEMPLATE)) अणु
			pp = ip_vs_proto_get(s->protocol);
			अगर (!pp) अणु
				IP_VS_DBG(2, "BACKUP v0, Unsupported protocol %u\n",
					s->protocol);
				जारी;
			पूर्ण
			अगर (state >= pp->num_states) अणु
				IP_VS_DBG(2, "BACKUP v0, Invalid %s state %u\n",
					pp->name, state);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (state >= IP_VS_CTPL_S_LAST)
				IP_VS_DBG(7, "BACKUP v0, Invalid tpl state %u\n",
					  state);
		पूर्ण

		ip_vs_conn_fill_param(ipvs, AF_INET, s->protocol,
				      (स्थिर जोड़ nf_inet_addr *)&s->caddr,
				      s->cport,
				      (स्थिर जोड़ nf_inet_addr *)&s->vaddr,
				      s->vport, &param);

		/* Send समयout as Zero */
		ip_vs_proc_conn(ipvs, &param, flags, state, s->protocol, AF_INET,
				(जोड़ nf_inet_addr *)&s->daddr, s->dport,
				0, 0, opt);
	पूर्ण
पूर्ण

/*
 * Handle options
 */
अटल अंतरभूत पूर्णांक ip_vs_proc_seqopt(__u8 *p, अचिन्हित पूर्णांक plen,
				    __u32 *opt_flags,
				    काष्ठा ip_vs_sync_conn_options *opt)
अणु
	काष्ठा ip_vs_sync_conn_options *topt;

	topt = (काष्ठा ip_vs_sync_conn_options *)p;

	अगर (plen != माप(काष्ठा ip_vs_sync_conn_options)) अणु
		IP_VS_DBG(2, "BACKUP, bogus conn options length\n");
		वापस -EINVAL;
	पूर्ण
	अगर (*opt_flags & IPVS_OPT_F_SEQ_DATA) अणु
		IP_VS_DBG(2, "BACKUP, conn options found twice\n");
		वापस -EINVAL;
	पूर्ण
	ntoh_seq(&topt->in_seq, &opt->in_seq);
	ntoh_seq(&topt->out_seq, &opt->out_seq);
	*opt_flags |= IPVS_OPT_F_SEQ_DATA;
	वापस 0;
पूर्ण

अटल पूर्णांक ip_vs_proc_str(__u8 *p, अचिन्हित पूर्णांक plen, अचिन्हित पूर्णांक *data_len,
			  __u8 **data, अचिन्हित पूर्णांक maxlen,
			  __u32 *opt_flags, __u32 flag)
अणु
	अगर (plen > maxlen) अणु
		IP_VS_DBG(2, "BACKUP, bogus par.data len > %d\n", maxlen);
		वापस -EINVAL;
	पूर्ण
	अगर (*opt_flags & flag) अणु
		IP_VS_DBG(2, "BACKUP, Par.data found twice 0x%x\n", flag);
		वापस -EINVAL;
	पूर्ण
	*data_len = plen;
	*data = p;
	*opt_flags |= flag;
	वापस 0;
पूर्ण
/*
 *   Process a Version 1 sync. connection
 */
अटल अंतरभूत पूर्णांक ip_vs_proc_sync_conn(काष्ठा netns_ipvs *ipvs, __u8 *p, __u8 *msg_end)
अणु
	काष्ठा ip_vs_sync_conn_options opt;
	जोड़  ip_vs_sync_conn *s;
	काष्ठा ip_vs_protocol *pp;
	काष्ठा ip_vs_conn_param param;
	__u32 flags;
	अचिन्हित पूर्णांक af, state, pe_data_len=0, pe_name_len=0;
	__u8 *pe_data=शून्य, *pe_name=शून्य;
	__u32 opt_flags=0;
	पूर्णांक retc=0;

	s = (जोड़ ip_vs_sync_conn *) p;

	अगर (s->v6.type & STYPE_F_INET6) अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
		af = AF_INET6;
		p += माप(काष्ठा ip_vs_sync_v6);
#अन्यथा
		IP_VS_DBG(3,"BACKUP, IPv6 msg received, and IPVS is not compiled for IPv6\n");
		retc = 10;
		जाओ out;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (!s->v4.type) अणु
		af = AF_INET;
		p += माप(काष्ठा ip_vs_sync_v4);
	पूर्ण अन्यथा अणु
		वापस -10;
	पूर्ण
	अगर (p > msg_end)
		वापस -20;

	/* Process optional params check Type & Len. */
	जबतक (p < msg_end) अणु
		पूर्णांक ptype;
		पूर्णांक plen;

		अगर (p+2 > msg_end)
			वापस -30;
		ptype = *(p++);
		plen  = *(p++);

		अगर (!plen || ((p + plen) > msg_end))
			वापस -40;
		/* Handle seq option  p = param data */
		चयन (ptype & ~IPVS_OPT_F_PARAM) अणु
		हाल IPVS_OPT_SEQ_DATA:
			अगर (ip_vs_proc_seqopt(p, plen, &opt_flags, &opt))
				वापस -50;
			अवरोध;

		हाल IPVS_OPT_PE_DATA:
			अगर (ip_vs_proc_str(p, plen, &pe_data_len, &pe_data,
					   IP_VS_PEDATA_MAXLEN, &opt_flags,
					   IPVS_OPT_F_PE_DATA))
				वापस -60;
			अवरोध;

		हाल IPVS_OPT_PE_NAME:
			अगर (ip_vs_proc_str(p, plen,&pe_name_len, &pe_name,
					   IP_VS_PENAME_MAXLEN, &opt_flags,
					   IPVS_OPT_F_PE_NAME))
				वापस -70;
			अवरोध;

		शेष:
			/* Param data mandatory ? */
			अगर (!(ptype & IPVS_OPT_F_PARAM)) अणु
				IP_VS_DBG(3, "BACKUP, Unknown mandatory param %d found\n",
					  ptype & ~IPVS_OPT_F_PARAM);
				retc = 20;
				जाओ out;
			पूर्ण
		पूर्ण
		p += plen;  /* Next option */
	पूर्ण

	/* Get flags and Mask off unsupported */
	flags  = ntohl(s->v4.flags) & IP_VS_CONN_F_BACKUP_MASK;
	flags |= IP_VS_CONN_F_SYNC;
	state = ntohs(s->v4.state);

	अगर (!(flags & IP_VS_CONN_F_TEMPLATE)) अणु
		pp = ip_vs_proto_get(s->v4.protocol);
		अगर (!pp) अणु
			IP_VS_DBG(3,"BACKUP, Unsupported protocol %u\n",
				s->v4.protocol);
			retc = 30;
			जाओ out;
		पूर्ण
		अगर (state >= pp->num_states) अणु
			IP_VS_DBG(3, "BACKUP, Invalid %s state %u\n",
				pp->name, state);
			retc = 40;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (state >= IP_VS_CTPL_S_LAST)
			IP_VS_DBG(7, "BACKUP, Invalid tpl state %u\n",
				  state);
	पूर्ण
	अगर (ip_vs_conn_fill_param_sync(ipvs, af, s, &param, pe_data,
				       pe_data_len, pe_name, pe_name_len)) अणु
		retc = 50;
		जाओ out;
	पूर्ण
	/* If only IPv4, just silent skip IPv6 */
	अगर (af == AF_INET)
		ip_vs_proc_conn(ipvs, &param, flags, state, s->v4.protocol, af,
				(जोड़ nf_inet_addr *)&s->v4.daddr, s->v4.dport,
				ntohl(s->v4.समयout), ntohl(s->v4.fwmark),
				(opt_flags & IPVS_OPT_F_SEQ_DATA ? &opt : शून्य)
				);
#अगर_घोषित CONFIG_IP_VS_IPV6
	अन्यथा
		ip_vs_proc_conn(ipvs, &param, flags, state, s->v6.protocol, af,
				(जोड़ nf_inet_addr *)&s->v6.daddr, s->v6.dport,
				ntohl(s->v6.समयout), ntohl(s->v6.fwmark),
				(opt_flags & IPVS_OPT_F_SEQ_DATA ? &opt : शून्य)
				);
#पूर्ण_अगर
	ip_vs_pe_put(param.pe);
	वापस 0;
	/* Error निकास */
out:
	IP_VS_DBG(2, "BACKUP, Single msg dropped err:%d\n", retc);
	वापस retc;

पूर्ण
/*
 *      Process received multicast message and create the corresponding
 *      ip_vs_conn entries.
 *      Handles Version 0 & 1
 */
अटल व्योम ip_vs_process_message(काष्ठा netns_ipvs *ipvs, __u8 *buffer,
				  स्थिर माप_प्रकार buflen)
अणु
	काष्ठा ip_vs_sync_mesg *m2 = (काष्ठा ip_vs_sync_mesg *)buffer;
	__u8 *p, *msg_end;
	पूर्णांक i, nr_conns;

	अगर (buflen < माप(काष्ठा ip_vs_sync_mesg_v0)) अणु
		IP_VS_DBG(2, "BACKUP, message header too short\n");
		वापस;
	पूर्ण

	अगर (buflen != ntohs(m2->size)) अणु
		IP_VS_DBG(2, "BACKUP, bogus message size\n");
		वापस;
	पूर्ण
	/* SyncID sanity check */
	अगर (ipvs->bcfg.syncid != 0 && m2->syncid != ipvs->bcfg.syncid) अणु
		IP_VS_DBG(7, "BACKUP, Ignoring syncid = %d\n", m2->syncid);
		वापस;
	पूर्ण
	/* Handle version 1  message */
	अगर ((m2->version == SYNC_PROTO_VER) && (m2->reserved == 0)
	    && (m2->spare == 0)) अणु

		msg_end = buffer + माप(काष्ठा ip_vs_sync_mesg);
		nr_conns = m2->nr_conns;

		क्रम (i=0; i<nr_conns; i++) अणु
			जोड़ ip_vs_sync_conn *s;
			अचिन्हित पूर्णांक size;
			पूर्णांक retc;

			p = msg_end;
			अगर (p + माप(s->v4) > buffer+buflen) अणु
				IP_VS_ERR_RL("BACKUP, Dropping buffer, too small\n");
				वापस;
			पूर्ण
			s = (जोड़ ip_vs_sync_conn *)p;
			size = ntohs(s->v4.ver_size) & SVER_MASK;
			msg_end = p + size;
			/* Basic sanity checks */
			अगर (msg_end  > buffer+buflen) अणु
				IP_VS_ERR_RL("BACKUP, Dropping buffer, msg > buffer\n");
				वापस;
			पूर्ण
			अगर (ntohs(s->v4.ver_size) >> SVER_SHIFT) अणु
				IP_VS_ERR_RL("BACKUP, Dropping buffer, Unknown version %d\n",
					      ntohs(s->v4.ver_size) >> SVER_SHIFT);
				वापस;
			पूर्ण
			/* Process a single sync_conn */
			retc = ip_vs_proc_sync_conn(ipvs, p, msg_end);
			अगर (retc < 0) अणु
				IP_VS_ERR_RL("BACKUP, Dropping buffer, Err: %d in decoding\n",
					     retc);
				वापस;
			पूर्ण
			/* Make sure we have 32 bit alignment */
			msg_end = p + ((size + 3) & ~3);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Old type of message */
		ip_vs_process_message_v0(ipvs, buffer, buflen);
		वापस;
	पूर्ण
पूर्ण


/*
 *      Setup sndbuf (mode=1) or rcvbuf (mode=0)
 */
अटल व्योम set_sock_size(काष्ठा sock *sk, पूर्णांक mode, पूर्णांक val)
अणु
	/* setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &val, माप(val)); */
	/* setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &val, माप(val)); */
	lock_sock(sk);
	अगर (mode) अणु
		val = clamp_t(पूर्णांक, val, (SOCK_MIN_SNDBUF + 1) / 2,
			      sysctl_wmem_max);
		sk->sk_sndbuf = val * 2;
		sk->sk_userlocks |= SOCK_SNDBUF_LOCK;
	पूर्ण अन्यथा अणु
		val = clamp_t(पूर्णांक, val, (SOCK_MIN_RCVBUF + 1) / 2,
			      sysctl_rmem_max);
		sk->sk_rcvbuf = val * 2;
		sk->sk_userlocks |= SOCK_RCVBUF_LOCK;
	पूर्ण
	release_sock(sk);
पूर्ण

/*
 *      Setup loopback of outgoing multicasts on a sending socket
 */
अटल व्योम set_mcast_loop(काष्ठा sock *sk, u_अक्षर loop)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	/* setsockopt(sock, SOL_IP, IP_MULTICAST_LOOP, &loop, माप(loop)); */
	lock_sock(sk);
	inet->mc_loop = loop ? 1 : 0;
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (sk->sk_family == AF_INET6) अणु
		काष्ठा ipv6_pinfo *np = inet6_sk(sk);

		/* IPV6_MULTICAST_LOOP */
		np->mc_loop = loop ? 1 : 0;
	पूर्ण
#पूर्ण_अगर
	release_sock(sk);
पूर्ण

/*
 *      Specअगरy TTL क्रम outgoing multicasts on a sending socket
 */
अटल व्योम set_mcast_ttl(काष्ठा sock *sk, u_अक्षर ttl)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	/* setsockopt(sock, SOL_IP, IP_MULTICAST_TTL, &ttl, माप(ttl)); */
	lock_sock(sk);
	inet->mc_ttl = ttl;
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (sk->sk_family == AF_INET6) अणु
		काष्ठा ipv6_pinfo *np = inet6_sk(sk);

		/* IPV6_MULTICAST_HOPS */
		np->mcast_hops = ttl;
	पूर्ण
#पूर्ण_अगर
	release_sock(sk);
पूर्ण

/* Control fragmentation of messages */
अटल व्योम set_mcast_pmtudisc(काष्ठा sock *sk, पूर्णांक val)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	/* setsockopt(sock, SOL_IP, IP_MTU_DISCOVER, &val, माप(val)); */
	lock_sock(sk);
	inet->pmtudisc = val;
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (sk->sk_family == AF_INET6) अणु
		काष्ठा ipv6_pinfo *np = inet6_sk(sk);

		/* IPV6_MTU_DISCOVER */
		np->pmtudisc = val;
	पूर्ण
#पूर्ण_अगर
	release_sock(sk);
पूर्ण

/*
 *      Specअगरiy शेष पूर्णांकerface क्रम outgoing multicasts
 */
अटल पूर्णांक set_mcast_अगर(काष्ठा sock *sk, काष्ठा net_device *dev)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	अगर (sk->sk_bound_dev_अगर && dev->अगरindex != sk->sk_bound_dev_अगर)
		वापस -EINVAL;

	lock_sock(sk);
	inet->mc_index = dev->अगरindex;
	/*  inet->mc_addr  = 0; */
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (sk->sk_family == AF_INET6) अणु
		काष्ठा ipv6_pinfo *np = inet6_sk(sk);

		/* IPV6_MULTICAST_IF */
		np->mcast_oअगर = dev->अगरindex;
	पूर्ण
#पूर्ण_अगर
	release_sock(sk);

	वापस 0;
पूर्ण


/*
 *      Join a multicast group.
 *      the group is specअगरied by a class D multicast address 224.0.0.0/8
 *      in the in_addr काष्ठाure passed in as a parameter.
 */
अटल पूर्णांक
join_mcast_group(काष्ठा sock *sk, काष्ठा in_addr *addr, काष्ठा net_device *dev)
अणु
	काष्ठा ip_mreqn mreq;
	पूर्णांक ret;

	स_रखो(&mreq, 0, माप(mreq));
	स_नकल(&mreq.imr_multiaddr, addr, माप(काष्ठा in_addr));

	अगर (sk->sk_bound_dev_अगर && dev->अगरindex != sk->sk_bound_dev_अगर)
		वापस -EINVAL;

	mreq.imr_अगरindex = dev->अगरindex;

	lock_sock(sk);
	ret = ip_mc_join_group(sk, &mreq);
	release_sock(sk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल पूर्णांक join_mcast_group6(काष्ठा sock *sk, काष्ठा in6_addr *addr,
			     काष्ठा net_device *dev)
अणु
	पूर्णांक ret;

	अगर (sk->sk_bound_dev_अगर && dev->अगरindex != sk->sk_bound_dev_अगर)
		वापस -EINVAL;

	lock_sock(sk);
	ret = ipv6_sock_mc_join(sk, dev->अगरindex, addr);
	release_sock(sk);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक bind_mcastअगर_addr(काष्ठा socket *sock, काष्ठा net_device *dev)
अणु
	__be32 addr;
	काष्ठा sockaddr_in sin;

	addr = inet_select_addr(dev, 0, RT_SCOPE_UNIVERSE);
	अगर (!addr)
		pr_err("You probably need to specify IP address on "
		       "multicast interface.\n");

	IP_VS_DBG(7, "binding socket with (%s) %pI4\n",
		  dev->name, &addr);

	/* Now bind the socket with the address of multicast पूर्णांकerface */
	sin.sin_family	     = AF_INET;
	sin.sin_addr.s_addr  = addr;
	sin.sin_port         = 0;

	वापस sock->ops->bind(sock, (काष्ठा sockaddr*)&sin, माप(sin));
पूर्ण

अटल व्योम get_mcast_sockaddr(जोड़ ipvs_sockaddr *sa, पूर्णांक *salen,
			       काष्ठा ipvs_sync_daemon_cfg *c, पूर्णांक id)
अणु
	अगर (AF_INET6 == c->mcast_af) अणु
		sa->in6 = (काष्ठा sockaddr_in6) अणु
			.sin6_family = AF_INET6,
			.sin6_port = htons(c->mcast_port + id),
		पूर्ण;
		sa->in6.sin6_addr = c->mcast_group.in6;
		*salen = माप(sa->in6);
	पूर्ण अन्यथा अणु
		sa->in = (काष्ठा sockaddr_in) अणु
			.sin_family = AF_INET,
			.sin_port = htons(c->mcast_port + id),
		पूर्ण;
		sa->in.sin_addr = c->mcast_group.in;
		*salen = माप(sa->in);
	पूर्ण
पूर्ण

/*
 *      Set up sending multicast socket over UDP
 */
अटल पूर्णांक make_send_sock(काष्ठा netns_ipvs *ipvs, पूर्णांक id,
			  काष्ठा net_device *dev, काष्ठा socket **sock_ret)
अणु
	/* multicast addr */
	जोड़ ipvs_sockaddr mcast_addr;
	काष्ठा socket *sock;
	पूर्णांक result, salen;

	/* First create a socket */
	result = sock_create_kern(ipvs->net, ipvs->mcfg.mcast_af, SOCK_DGRAM,
				  IPPROTO_UDP, &sock);
	अगर (result < 0) अणु
		pr_err("Error during creation of socket; terminating\n");
		जाओ error;
	पूर्ण
	*sock_ret = sock;
	result = set_mcast_अगर(sock->sk, dev);
	अगर (result < 0) अणु
		pr_err("Error setting outbound mcast interface\n");
		जाओ error;
	पूर्ण

	set_mcast_loop(sock->sk, 0);
	set_mcast_ttl(sock->sk, ipvs->mcfg.mcast_ttl);
	/* Allow fragmentation अगर MTU changes */
	set_mcast_pmtudisc(sock->sk, IP_PMTUDISC_DONT);
	result = sysctl_sync_sock_size(ipvs);
	अगर (result > 0)
		set_sock_size(sock->sk, 1, result);

	अगर (AF_INET == ipvs->mcfg.mcast_af)
		result = bind_mcastअगर_addr(sock, dev);
	अन्यथा
		result = 0;
	अगर (result < 0) अणु
		pr_err("Error binding address of the mcast interface\n");
		जाओ error;
	पूर्ण

	get_mcast_sockaddr(&mcast_addr, &salen, &ipvs->mcfg, id);
	result = sock->ops->connect(sock, (काष्ठा sockaddr *) &mcast_addr,
				    salen, 0);
	अगर (result < 0) अणु
		pr_err("Error connecting to the multicast addr\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	वापस result;
पूर्ण


/*
 *      Set up receiving multicast socket over UDP
 */
अटल पूर्णांक make_receive_sock(काष्ठा netns_ipvs *ipvs, पूर्णांक id,
			     काष्ठा net_device *dev, काष्ठा socket **sock_ret)
अणु
	/* multicast addr */
	जोड़ ipvs_sockaddr mcast_addr;
	काष्ठा socket *sock;
	पूर्णांक result, salen;

	/* First create a socket */
	result = sock_create_kern(ipvs->net, ipvs->bcfg.mcast_af, SOCK_DGRAM,
				  IPPROTO_UDP, &sock);
	अगर (result < 0) अणु
		pr_err("Error during creation of socket; terminating\n");
		जाओ error;
	पूर्ण
	*sock_ret = sock;
	/* it is equivalent to the REUSEADDR option in user-space */
	sock->sk->sk_reuse = SK_CAN_REUSE;
	result = sysctl_sync_sock_size(ipvs);
	अगर (result > 0)
		set_sock_size(sock->sk, 0, result);

	get_mcast_sockaddr(&mcast_addr, &salen, &ipvs->bcfg, id);
	sock->sk->sk_bound_dev_अगर = dev->अगरindex;
	result = sock->ops->bind(sock, (काष्ठा sockaddr *)&mcast_addr, salen);
	अगर (result < 0) अणु
		pr_err("Error binding to the multicast addr\n");
		जाओ error;
	पूर्ण

	/* join the multicast group */
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (ipvs->bcfg.mcast_af == AF_INET6)
		result = join_mcast_group6(sock->sk, &mcast_addr.in6.sin6_addr,
					   dev);
	अन्यथा
#पूर्ण_अगर
		result = join_mcast_group(sock->sk, &mcast_addr.in.sin_addr,
					  dev);
	अगर (result < 0) अणु
		pr_err("Error joining to the multicast group\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	वापस result;
पूर्ण


अटल पूर्णांक
ip_vs_send_async(काष्ठा socket *sock, स्थिर अक्षर *buffer, स्थिर माप_प्रकार length)
अणु
	काष्ठा msghdr	msg = अणु.msg_flags = MSG_DONTWAIT|MSG_NOSIGNALपूर्ण;
	काष्ठा kvec	iov;
	पूर्णांक		len;

	EnterFunction(7);
	iov.iov_base     = (व्योम *)buffer;
	iov.iov_len      = length;

	len = kernel_sendmsg(sock, &msg, &iov, 1, (माप_प्रकार)(length));

	LeaveFunction(7);
	वापस len;
पूर्ण

अटल पूर्णांक
ip_vs_send_sync_msg(काष्ठा socket *sock, काष्ठा ip_vs_sync_mesg *msg)
अणु
	पूर्णांक msize;
	पूर्णांक ret;

	msize = ntohs(msg->size);

	ret = ip_vs_send_async(sock, (अक्षर *)msg, msize);
	अगर (ret >= 0 || ret == -EAGAIN)
		वापस ret;
	pr_err("ip_vs_send_async error %d\n", ret);
	वापस 0;
पूर्ण

अटल पूर्णांक
ip_vs_receive(काष्ठा socket *sock, अक्षर *buffer, स्थिर माप_प्रकार buflen)
अणु
	काष्ठा msghdr		msg = अणुशून्य,पूर्ण;
	काष्ठा kvec		iov = अणुbuffer, buflenपूर्ण;
	पूर्णांक			len;

	EnterFunction(7);

	/* Receive a packet */
	iov_iter_kvec(&msg.msg_iter, READ, &iov, 1, buflen);
	len = sock_recvmsg(sock, &msg, MSG_DONTWAIT);
	अगर (len < 0)
		वापस len;

	LeaveFunction(7);
	वापस len;
पूर्ण

/* Wakeup the master thपढ़ो क्रम sending */
अटल व्योम master_wakeup_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipvs_master_sync_state *ms =
		container_of(work, काष्ठा ipvs_master_sync_state,
			     master_wakeup_work.work);
	काष्ठा netns_ipvs *ipvs = ms->ipvs;

	spin_lock_bh(&ipvs->sync_lock);
	अगर (ms->sync_queue_len &&
	    ms->sync_queue_delay < IPVS_SYNC_WAKEUP_RATE) अणु
		पूर्णांक id = (पूर्णांक)(ms - ipvs->ms);

		ms->sync_queue_delay = IPVS_SYNC_WAKEUP_RATE;
		wake_up_process(ipvs->master_tinfo[id].task);
	पूर्ण
	spin_unlock_bh(&ipvs->sync_lock);
पूर्ण

/* Get next buffer to send */
अटल अंतरभूत काष्ठा ip_vs_sync_buff *
next_sync_buff(काष्ठा netns_ipvs *ipvs, काष्ठा ipvs_master_sync_state *ms)
अणु
	काष्ठा ip_vs_sync_buff *sb;

	sb = sb_dequeue(ipvs, ms);
	अगर (sb)
		वापस sb;
	/* Do not delay entries in buffer क्रम more than 2 seconds */
	वापस get_curr_sync_buff(ipvs, ms, IPVS_SYNC_FLUSH_TIME);
पूर्ण

अटल पूर्णांक sync_thपढ़ो_master(व्योम *data)
अणु
	काष्ठा ip_vs_sync_thपढ़ो_data *tinfo = data;
	काष्ठा netns_ipvs *ipvs = tinfo->ipvs;
	काष्ठा ipvs_master_sync_state *ms = &ipvs->ms[tinfo->id];
	काष्ठा sock *sk = tinfo->sock->sk;
	काष्ठा ip_vs_sync_buff *sb;

	pr_info("sync thread started: state = MASTER, mcast_ifn = %s, "
		"syncid = %d, id = %d\n",
		ipvs->mcfg.mcast_अगरn, ipvs->mcfg.syncid, tinfo->id);

	क्रम (;;) अणु
		sb = next_sync_buff(ipvs, ms);
		अगर (unlikely(kthपढ़ो_should_stop()))
			अवरोध;
		अगर (!sb) अणु
			schedule_समयout(IPVS_SYNC_CHECK_PERIOD);
			जारी;
		पूर्ण
		जबतक (ip_vs_send_sync_msg(tinfo->sock, sb->mesg) < 0) अणु
			/* (Ab)use पूर्णांकerruptible sleep to aव्योम increasing
			 * the load avg.
			 */
			__रुको_event_पूर्णांकerruptible(*sk_sleep(sk),
						   sock_ग_लिखोable(sk) ||
						   kthपढ़ो_should_stop());
			अगर (unlikely(kthपढ़ो_should_stop()))
				जाओ करोne;
		पूर्ण
		ip_vs_sync_buff_release(sb);
	पूर्ण

करोne:
	__set_current_state(TASK_RUNNING);
	अगर (sb)
		ip_vs_sync_buff_release(sb);

	/* clean up the sync_buff queue */
	जबतक ((sb = sb_dequeue(ipvs, ms)))
		ip_vs_sync_buff_release(sb);
	__set_current_state(TASK_RUNNING);

	/* clean up the current sync_buff */
	sb = get_curr_sync_buff(ipvs, ms, 0);
	अगर (sb)
		ip_vs_sync_buff_release(sb);

	वापस 0;
पूर्ण


अटल पूर्णांक sync_thपढ़ो_backup(व्योम *data)
अणु
	काष्ठा ip_vs_sync_thपढ़ो_data *tinfo = data;
	काष्ठा netns_ipvs *ipvs = tinfo->ipvs;
	काष्ठा sock *sk = tinfo->sock->sk;
	काष्ठा udp_sock *up = udp_sk(sk);
	पूर्णांक len;

	pr_info("sync thread started: state = BACKUP, mcast_ifn = %s, "
		"syncid = %d, id = %d\n",
		ipvs->bcfg.mcast_अगरn, ipvs->bcfg.syncid, tinfo->id);

	जबतक (!kthपढ़ो_should_stop()) अणु
		रुको_event_पूर्णांकerruptible(*sk_sleep(sk),
					 !skb_queue_empty_lockless(&sk->sk_receive_queue) ||
					 !skb_queue_empty_lockless(&up->पढ़ोer_queue) ||
					 kthपढ़ो_should_stop());

		/* करो we have data now? */
		जबतक (!skb_queue_empty_lockless(&sk->sk_receive_queue) ||
		       !skb_queue_empty_lockless(&up->पढ़ोer_queue)) अणु
			len = ip_vs_receive(tinfo->sock, tinfo->buf,
					ipvs->bcfg.sync_maxlen);
			अगर (len <= 0) अणु
				अगर (len != -EAGAIN)
					pr_err("receiving message error\n");
				अवरोध;
			पूर्ण

			ip_vs_process_message(ipvs, tinfo->buf, len);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


पूर्णांक start_sync_thपढ़ो(काष्ठा netns_ipvs *ipvs, काष्ठा ipvs_sync_daemon_cfg *c,
		      पूर्णांक state)
अणु
	काष्ठा ip_vs_sync_thपढ़ो_data *ti = शून्य, *tinfo;
	काष्ठा task_काष्ठा *task;
	काष्ठा net_device *dev;
	अक्षर *name;
	पूर्णांक (*thपढ़ोfn)(व्योम *data);
	पूर्णांक id = 0, count, hlen;
	पूर्णांक result = -ENOMEM;
	u16 mtu, min_mtu;

	IP_VS_DBG(7, "%s(): pid %d\n", __func__, task_pid_nr(current));
	IP_VS_DBG(7, "Each ip_vs_sync_conn entry needs %zd bytes\n",
		  माप(काष्ठा ip_vs_sync_conn_v0));

	/* increase the module use count */
	अगर (!ip_vs_use_count_inc())
		वापस -ENOPROTOOPT;

	/* Do not hold one mutex and then to block on another */
	क्रम (;;) अणु
		rtnl_lock();
		अगर (mutex_trylock(&ipvs->sync_mutex))
			अवरोध;
		rtnl_unlock();
		mutex_lock(&ipvs->sync_mutex);
		अगर (rtnl_trylock())
			अवरोध;
		mutex_unlock(&ipvs->sync_mutex);
	पूर्ण

	अगर (!ipvs->sync_state) अणु
		count = clamp(sysctl_sync_ports(ipvs), 1, IPVS_SYNC_PORTS_MAX);
		ipvs->thपढ़ोs_mask = count - 1;
	पूर्ण अन्यथा
		count = ipvs->thपढ़ोs_mask + 1;

	अगर (c->mcast_af == AF_UNSPEC) अणु
		c->mcast_af = AF_INET;
		c->mcast_group.ip = cpu_to_be32(IP_VS_SYNC_GROUP);
	पूर्ण
	अगर (!c->mcast_port)
		c->mcast_port = IP_VS_SYNC_PORT;
	अगर (!c->mcast_ttl)
		c->mcast_ttl = 1;

	dev = __dev_get_by_name(ipvs->net, c->mcast_अगरn);
	अगर (!dev) अणु
		pr_err("Unknown mcast interface: %s\n", c->mcast_अगरn);
		result = -ENODEV;
		जाओ out_early;
	पूर्ण
	hlen = (AF_INET6 == c->mcast_af) ?
	       माप(काष्ठा ipv6hdr) + माप(काष्ठा udphdr) :
	       माप(काष्ठा iphdr) + माप(काष्ठा udphdr);
	mtu = (state == IP_VS_STATE_BACKUP) ?
		  clamp(dev->mtu, 1500U, 65535U) : 1500U;
	min_mtu = (state == IP_VS_STATE_BACKUP) ? 1024 : 1;

	अगर (c->sync_maxlen)
		c->sync_maxlen = clamp_t(अचिन्हित पूर्णांक,
					 c->sync_maxlen, min_mtu,
					 65535 - hlen);
	अन्यथा
		c->sync_maxlen = mtu - hlen;

	अगर (state == IP_VS_STATE_MASTER) अणु
		result = -EEXIST;
		अगर (ipvs->ms)
			जाओ out_early;

		ipvs->mcfg = *c;
		name = "ipvs-m:%d:%d";
		thपढ़ोfn = sync_thपढ़ो_master;
	पूर्ण अन्यथा अगर (state == IP_VS_STATE_BACKUP) अणु
		result = -EEXIST;
		अगर (ipvs->backup_tinfo)
			जाओ out_early;

		ipvs->bcfg = *c;
		name = "ipvs-b:%d:%d";
		thपढ़ोfn = sync_thपढ़ो_backup;
	पूर्ण अन्यथा अणु
		result = -EINVAL;
		जाओ out_early;
	पूर्ण

	अगर (state == IP_VS_STATE_MASTER) अणु
		काष्ठा ipvs_master_sync_state *ms;

		result = -ENOMEM;
		ipvs->ms = kसुस्मृति(count, माप(ipvs->ms[0]), GFP_KERNEL);
		अगर (!ipvs->ms)
			जाओ out;
		ms = ipvs->ms;
		क्रम (id = 0; id < count; id++, ms++) अणु
			INIT_LIST_HEAD(&ms->sync_queue);
			ms->sync_queue_len = 0;
			ms->sync_queue_delay = 0;
			INIT_DELAYED_WORK(&ms->master_wakeup_work,
					  master_wakeup_work_handler);
			ms->ipvs = ipvs;
		पूर्ण
	पूर्ण
	result = -ENOMEM;
	ti = kसुस्मृति(count, माप(काष्ठा ip_vs_sync_thपढ़ो_data),
		     GFP_KERNEL);
	अगर (!ti)
		जाओ out;

	क्रम (id = 0; id < count; id++) अणु
		tinfo = &ti[id];
		tinfo->ipvs = ipvs;
		अगर (state == IP_VS_STATE_BACKUP) अणु
			result = -ENOMEM;
			tinfo->buf = kदो_स्मृति(ipvs->bcfg.sync_maxlen,
					     GFP_KERNEL);
			अगर (!tinfo->buf)
				जाओ out;
		पूर्ण
		tinfo->id = id;
		अगर (state == IP_VS_STATE_MASTER)
			result = make_send_sock(ipvs, id, dev, &tinfo->sock);
		अन्यथा
			result = make_receive_sock(ipvs, id, dev, &tinfo->sock);
		अगर (result < 0)
			जाओ out;

		task = kthपढ़ो_run(thपढ़ोfn, tinfo, name, ipvs->gen, id);
		अगर (IS_ERR(task)) अणु
			result = PTR_ERR(task);
			जाओ out;
		पूर्ण
		tinfo->task = task;
	पूर्ण

	/* mark as active */

	अगर (state == IP_VS_STATE_MASTER)
		ipvs->master_tinfo = ti;
	अन्यथा
		ipvs->backup_tinfo = ti;
	spin_lock_bh(&ipvs->sync_buff_lock);
	ipvs->sync_state |= state;
	spin_unlock_bh(&ipvs->sync_buff_lock);

	mutex_unlock(&ipvs->sync_mutex);
	rtnl_unlock();

	वापस 0;

out:
	/* We करो not need RTNL lock anymore, release it here so that
	 * sock_release below can use rtnl_lock to leave the mcast group.
	 */
	rtnl_unlock();
	id = min(id, count - 1);
	अगर (ti) अणु
		क्रम (tinfo = ti + id; tinfo >= ti; tinfo--) अणु
			अगर (tinfo->task)
				kthपढ़ो_stop(tinfo->task);
		पूर्ण
	पूर्ण
	अगर (!(ipvs->sync_state & IP_VS_STATE_MASTER)) अणु
		kमुक्त(ipvs->ms);
		ipvs->ms = शून्य;
	पूर्ण
	mutex_unlock(&ipvs->sync_mutex);

	/* No more mutexes, release socks */
	अगर (ti) अणु
		क्रम (tinfo = ti + id; tinfo >= ti; tinfo--) अणु
			अगर (tinfo->sock)
				sock_release(tinfo->sock);
			kमुक्त(tinfo->buf);
		पूर्ण
		kमुक्त(ti);
	पूर्ण

	/* decrease the module use count */
	ip_vs_use_count_dec();
	वापस result;

out_early:
	mutex_unlock(&ipvs->sync_mutex);
	rtnl_unlock();

	/* decrease the module use count */
	ip_vs_use_count_dec();
	वापस result;
पूर्ण


पूर्णांक stop_sync_thपढ़ो(काष्ठा netns_ipvs *ipvs, पूर्णांक state)
अणु
	काष्ठा ip_vs_sync_thपढ़ो_data *ti, *tinfo;
	पूर्णांक id;
	पूर्णांक retc = -EINVAL;

	IP_VS_DBG(7, "%s(): pid %d\n", __func__, task_pid_nr(current));

	mutex_lock(&ipvs->sync_mutex);
	अगर (state == IP_VS_STATE_MASTER) अणु
		retc = -ESRCH;
		अगर (!ipvs->ms)
			जाओ err;
		ti = ipvs->master_tinfo;

		/*
		 * The lock synchronizes with sb_queue_tail(), so that we करोn't
		 * add sync buffers to the queue, when we are alपढ़ोy in
		 * progress of stopping the master sync daemon.
		 */

		spin_lock_bh(&ipvs->sync_buff_lock);
		spin_lock(&ipvs->sync_lock);
		ipvs->sync_state &= ~IP_VS_STATE_MASTER;
		spin_unlock(&ipvs->sync_lock);
		spin_unlock_bh(&ipvs->sync_buff_lock);

		retc = 0;
		क्रम (id = ipvs->thपढ़ोs_mask; id >= 0; id--) अणु
			काष्ठा ipvs_master_sync_state *ms = &ipvs->ms[id];
			पूर्णांक ret;

			tinfo = &ti[id];
			pr_info("stopping master sync thread %d ...\n",
				task_pid_nr(tinfo->task));
			cancel_delayed_work_sync(&ms->master_wakeup_work);
			ret = kthपढ़ो_stop(tinfo->task);
			अगर (retc >= 0)
				retc = ret;
		पूर्ण
		kमुक्त(ipvs->ms);
		ipvs->ms = शून्य;
		ipvs->master_tinfo = शून्य;
	पूर्ण अन्यथा अगर (state == IP_VS_STATE_BACKUP) अणु
		retc = -ESRCH;
		अगर (!ipvs->backup_tinfo)
			जाओ err;
		ti = ipvs->backup_tinfo;

		ipvs->sync_state &= ~IP_VS_STATE_BACKUP;
		retc = 0;
		क्रम (id = ipvs->thपढ़ोs_mask; id >= 0; id--) अणु
			पूर्णांक ret;

			tinfo = &ti[id];
			pr_info("stopping backup sync thread %d ...\n",
				task_pid_nr(tinfo->task));
			ret = kthपढ़ो_stop(tinfo->task);
			अगर (retc >= 0)
				retc = ret;
		पूर्ण
		ipvs->backup_tinfo = शून्य;
	पूर्ण अन्यथा अणु
		जाओ err;
	पूर्ण
	id = ipvs->thपढ़ोs_mask;
	mutex_unlock(&ipvs->sync_mutex);

	/* No more mutexes, release socks */
	क्रम (tinfo = ti + id; tinfo >= ti; tinfo--) अणु
		अगर (tinfo->sock)
			sock_release(tinfo->sock);
		kमुक्त(tinfo->buf);
	पूर्ण
	kमुक्त(ti);

	/* decrease the module use count */
	ip_vs_use_count_dec();
	वापस retc;

err:
	mutex_unlock(&ipvs->sync_mutex);
	वापस retc;
पूर्ण

/*
 * Initialize data काष्ठा क्रम each netns
 */
पूर्णांक __net_init ip_vs_sync_net_init(काष्ठा netns_ipvs *ipvs)
अणु
	__mutex_init(&ipvs->sync_mutex, "ipvs->sync_mutex", &__ipvs_sync_key);
	spin_lock_init(&ipvs->sync_lock);
	spin_lock_init(&ipvs->sync_buff_lock);
	वापस 0;
पूर्ण

व्योम ip_vs_sync_net_cleanup(काष्ठा netns_ipvs *ipvs)
अणु
	पूर्णांक retc;

	retc = stop_sync_thपढ़ो(ipvs, IP_VS_STATE_MASTER);
	अगर (retc && retc != -ESRCH)
		pr_err("Failed to stop Master Daemon\n");

	retc = stop_sync_thपढ़ो(ipvs, IP_VS_STATE_BACKUP);
	अगर (retc && retc != -ESRCH)
		pr_err("Failed to stop Backup Daemon\n");
पूर्ण
