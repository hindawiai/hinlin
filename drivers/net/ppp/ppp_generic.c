<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic PPP layer क्रम Linux.
 *
 * Copyright 1999-2002 Paul Mackerras.
 *
 * The generic PPP layer handles the PPP network पूर्णांकerfaces, the
 * /dev/ppp device, packet and VJ compression, and multilink.
 * It talks to PPP `channels' via the पूर्णांकerface defined in
 * include/linux/ppp_channel.h.  Channels provide the basic means क्रम
 * sending and receiving PPP frames on some kind of communications
 * channel.
 *
 * Part of the code in this driver was inspired by the old async-only
 * PPP driver, written by Michael Callahan and Al Longyear, and
 * subsequently hacked by Paul Mackerras.
 *
 * ==खाताVERSION 20041108==
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kmod.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/idr.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/poll.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/filter.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/ppp-comp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/slhc_vj.h>
#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>

#समावेश <linux/nsproxy.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#घोषणा PPP_VERSION	"2.4.2"

/*
 * Network protocols we support.
 */
#घोषणा NP_IP	0		/* Internet Protocol V4 */
#घोषणा NP_IPV6	1		/* Internet Protocol V6 */
#घोषणा NP_IPX	2		/* IPX protocol */
#घोषणा NP_AT	3		/* Appletalk protocol */
#घोषणा NP_MPLS_UC 4		/* MPLS unicast */
#घोषणा NP_MPLS_MC 5		/* MPLS multicast */
#घोषणा NUM_NP	6		/* Number of NPs. */

#घोषणा MPHDRLEN	6	/* multilink protocol header length */
#घोषणा MPHDRLEN_SSN	4	/* ditto with लघु sequence numbers */

/*
 * An instance of /dev/ppp can be associated with either a ppp
 * पूर्णांकerface unit or a ppp channel.  In both हालs, file->निजी_data
 * poपूर्णांकs to one of these.
 */
काष्ठा ppp_file अणु
	क्रमागत अणु
		INTERFACE=1, CHANNEL
	पूर्ण		kind;
	काष्ठा sk_buff_head xq;		/* pppd transmit queue */
	काष्ठा sk_buff_head rq;		/* receive queue क्रम pppd */
	रुको_queue_head_t rरुको;	/* क्रम poll on पढ़ोing /dev/ppp */
	refcount_t	refcnt;		/* # refs (incl /dev/ppp attached) */
	पूर्णांक		hdrlen;		/* space to leave क्रम headers */
	पूर्णांक		index;		/* पूर्णांकerface unit / channel number */
	पूर्णांक		dead;		/* unit/channel has been shut करोwn */
पूर्ण;

#घोषणा PF_TO_X(pf, X)		container_of(pf, X, file)

#घोषणा PF_TO_PPP(pf)		PF_TO_X(pf, काष्ठा ppp)
#घोषणा PF_TO_CHANNEL(pf)	PF_TO_X(pf, काष्ठा channel)

/*
 * Data काष्ठाure to hold primary network stats क्रम which
 * we want to use 64 bit storage.  Other network stats
 * are stored in dev->stats of the ppp strucute.
 */
काष्ठा ppp_link_stats अणु
	u64 rx_packets;
	u64 tx_packets;
	u64 rx_bytes;
	u64 tx_bytes;
पूर्ण;

/*
 * Data काष्ठाure describing one ppp unit.
 * A ppp unit corresponds to a ppp network पूर्णांकerface device
 * and represents a multilink bundle.
 * It can have 0 or more ppp channels connected to it.
 */
काष्ठा ppp अणु
	काष्ठा ppp_file	file;		/* stuff क्रम पढ़ो/ग_लिखो/poll 0 */
	काष्ठा file	*owner;		/* file that owns this unit 48 */
	काष्ठा list_head channels;	/* list of attached channels 4c */
	पूर्णांक		n_channels;	/* how many channels are attached 54 */
	spinlock_t	rlock;		/* lock क्रम receive side 58 */
	spinlock_t	wlock;		/* lock क्रम transmit side 5c */
	पूर्णांक __percpu	*xmit_recursion; /* xmit recursion detect */
	पूर्णांक		mru;		/* max receive unit 60 */
	अचिन्हित पूर्णांक	flags;		/* control bits 64 */
	अचिन्हित पूर्णांक	xstate;		/* transmit state bits 68 */
	अचिन्हित पूर्णांक	rstate;		/* receive state bits 6c */
	पूर्णांक		debug;		/* debug flags 70 */
	काष्ठा slcompress *vj;		/* state क्रम VJ header compression */
	क्रमागत NPmode	npmode[NUM_NP];	/* what to करो with each net proto 78 */
	काष्ठा sk_buff	*xmit_pending;	/* a packet पढ़ोy to go out 88 */
	काष्ठा compressor *xcomp;	/* transmit packet compressor 8c */
	व्योम		*xc_state;	/* its पूर्णांकernal state 90 */
	काष्ठा compressor *rcomp;	/* receive decompressor 94 */
	व्योम		*rc_state;	/* its पूर्णांकernal state 98 */
	अचिन्हित दीर्घ	last_xmit;	/* jअगरfies when last pkt sent 9c */
	अचिन्हित दीर्घ	last_recv;	/* jअगरfies when last pkt rcvd a0 */
	काष्ठा net_device *dev;		/* network पूर्णांकerface device a4 */
	पूर्णांक		closing;	/* is device closing करोwn? a8 */
#अगर_घोषित CONFIG_PPP_MULTILINK
	पूर्णांक		nxchan;		/* next channel to send something on */
	u32		nxseq;		/* next sequence number to send */
	पूर्णांक		mrru;		/* MP: max reस्थिर. receive unit */
	u32		nextseq;	/* MP: seq no of next packet */
	u32		minseq;		/* MP: min of most recent seqnos */
	काष्ठा sk_buff_head mrq;	/* MP: receive reस्थिरruction queue */
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */
#अगर_घोषित CONFIG_PPP_FILTER
	काष्ठा bpf_prog *pass_filter;	/* filter क्रम packets to pass */
	काष्ठा bpf_prog *active_filter; /* filter क्रम pkts to reset idle */
#पूर्ण_अगर /* CONFIG_PPP_FILTER */
	काष्ठा net	*ppp_net;	/* the net we beदीर्घ to */
	काष्ठा ppp_link_stats stats64;	/* 64 bit network stats */
पूर्ण;

/*
 * Bits in flags: SC_NO_TCP_CCID, SC_CCP_OPEN, SC_CCP_UP, SC_LOOP_TRAFFIC,
 * SC_MULTILINK, SC_MP_SHORTSEQ, SC_MP_XSHORTSEQ, SC_COMP_TCP, SC_REJ_COMP_TCP,
 * SC_MUST_COMP
 * Bits in rstate: SC_DECOMP_RUN, SC_DC_ERROR, SC_DC_FERROR.
 * Bits in xstate: SC_COMP_RUN
 */
#घोषणा SC_FLAG_BITS	(SC_NO_TCP_CCID|SC_CCP_OPEN|SC_CCP_UP|SC_LOOP_TRAFFIC \
			 |SC_MULTILINK|SC_MP_SHORTSEQ|SC_MP_XSHORTSEQ \
			 |SC_COMP_TCP|SC_REJ_COMP_TCP|SC_MUST_COMP)

/*
 * Private data काष्ठाure क्रम each channel.
 * This includes the data काष्ठाure used क्रम multilink.
 */
काष्ठा channel अणु
	काष्ठा ppp_file	file;		/* stuff क्रम पढ़ो/ग_लिखो/poll */
	काष्ठा list_head list;		/* link in all/new_channels list */
	काष्ठा ppp_channel *chan;	/* खुला channel data काष्ठाure */
	काष्ठा rw_semaphore chan_sem;	/* protects `chan' during chan ioctl */
	spinlock_t	करोwnl;		/* protects `chan', file.xq dequeue */
	काष्ठा ppp	*ppp;		/* ppp unit we're connected to */
	काष्ठा net	*chan_net;	/* the net channel beदीर्घs to */
	काष्ठा list_head clist;		/* link in list of channels per unit */
	rwlock_t	upl;		/* protects `ppp' and 'bridge' */
	काष्ठा channel __rcu *bridge;	/* "bridged" ppp channel */
#अगर_घोषित CONFIG_PPP_MULTILINK
	u8		avail;		/* flag used in multilink stuff */
	u8		had_frag;	/* >= 1 fragments have been sent */
	u32		lastseq;	/* MP: last sequence # received */
	पूर्णांक		speed;		/* speed of the corresponding ppp channel*/
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */
पूर्ण;

काष्ठा ppp_config अणु
	काष्ठा file *file;
	s32 unit;
	bool अगरname_is_set;
पूर्ण;

/*
 * SMP locking issues:
 * Both the ppp.rlock and ppp.wlock locks protect the ppp.channels
 * list and the ppp.n_channels field, you need to take both locks
 * beक्रमe you modअगरy them.
 * The lock ordering is: channel.upl -> ppp.wlock -> ppp.rlock ->
 * channel.करोwnl.
 */

अटल DEFINE_MUTEX(ppp_mutex);
अटल atomic_t ppp_unit_count = ATOMIC_INIT(0);
अटल atomic_t channel_count = ATOMIC_INIT(0);

/* per-net निजी data क्रम this module */
अटल अचिन्हित पूर्णांक ppp_net_id __पढ़ो_mostly;
काष्ठा ppp_net अणु
	/* units to ppp mapping */
	काष्ठा idr units_idr;

	/*
	 * all_ppp_mutex protects the units_idr mapping.
	 * It also ensures that finding a ppp unit in the units_idr
	 * map and updating its file.refcnt field is atomic.
	 */
	काष्ठा mutex all_ppp_mutex;

	/* channels */
	काष्ठा list_head all_channels;
	काष्ठा list_head new_channels;
	पूर्णांक last_channel_index;

	/*
	 * all_channels_lock protects all_channels and
	 * last_channel_index, and the atomicity of find
	 * a channel and updating its file.refcnt field.
	 */
	spinlock_t all_channels_lock;
पूर्ण;

/* Get the PPP protocol number from a skb */
#घोषणा PPP_PROTO(skb)	get_unaligned_be16((skb)->data)

/* We limit the length of ppp->file.rq to this (arbitrary) value */
#घोषणा PPP_MAX_RQLEN	32

/*
 * Maximum number of multilink fragments queued up.
 * This has to be large enough to cope with the maximum latency of
 * the slowest channel relative to the others.  Strictly it should
 * depend on the number of channels and their अक्षरacteristics.
 */
#घोषणा PPP_MP_MAX_QLEN	128

/* Multilink header bits. */
#घोषणा B	0x80		/* this fragment begins a packet */
#घोषणा E	0x40		/* this fragment ends a packet */

/* Compare multilink sequence numbers (assumed to be 32 bits wide) */
#घोषणा seq_beक्रमe(a, b)	((s32)((a) - (b)) < 0)
#घोषणा seq_after(a, b)		((s32)((a) - (b)) > 0)

/* Prototypes. */
अटल पूर्णांक ppp_unattached_ioctl(काष्ठा net *net, काष्ठा ppp_file *pf,
			काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल व्योम ppp_xmit_process(काष्ठा ppp *ppp, काष्ठा sk_buff *skb);
अटल व्योम ppp_send_frame(काष्ठा ppp *ppp, काष्ठा sk_buff *skb);
अटल व्योम ppp_push(काष्ठा ppp *ppp);
अटल व्योम ppp_channel_push(काष्ठा channel *pch);
अटल व्योम ppp_receive_frame(काष्ठा ppp *ppp, काष्ठा sk_buff *skb,
			      काष्ठा channel *pch);
अटल व्योम ppp_receive_error(काष्ठा ppp *ppp);
अटल व्योम ppp_receive_nonmp_frame(काष्ठा ppp *ppp, काष्ठा sk_buff *skb);
अटल काष्ठा sk_buff *ppp_decompress_frame(काष्ठा ppp *ppp,
					    काष्ठा sk_buff *skb);
#अगर_घोषित CONFIG_PPP_MULTILINK
अटल व्योम ppp_receive_mp_frame(काष्ठा ppp *ppp, काष्ठा sk_buff *skb,
				काष्ठा channel *pch);
अटल व्योम ppp_mp_insert(काष्ठा ppp *ppp, काष्ठा sk_buff *skb);
अटल काष्ठा sk_buff *ppp_mp_reस्थिरruct(काष्ठा ppp *ppp);
अटल पूर्णांक ppp_mp_explode(काष्ठा ppp *ppp, काष्ठा sk_buff *skb);
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */
अटल पूर्णांक ppp_set_compress(काष्ठा ppp *ppp, काष्ठा ppp_option_data *data);
अटल व्योम ppp_ccp_peek(काष्ठा ppp *ppp, काष्ठा sk_buff *skb, पूर्णांक inbound);
अटल व्योम ppp_ccp_बंदd(काष्ठा ppp *ppp);
अटल काष्ठा compressor *find_compressor(पूर्णांक type);
अटल व्योम ppp_get_stats(काष्ठा ppp *ppp, काष्ठा ppp_stats *st);
अटल पूर्णांक ppp_create_पूर्णांकerface(काष्ठा net *net, काष्ठा file *file, पूर्णांक *unit);
अटल व्योम init_ppp_file(काष्ठा ppp_file *pf, पूर्णांक kind);
अटल व्योम ppp_destroy_पूर्णांकerface(काष्ठा ppp *ppp);
अटल काष्ठा ppp *ppp_find_unit(काष्ठा ppp_net *pn, पूर्णांक unit);
अटल काष्ठा channel *ppp_find_channel(काष्ठा ppp_net *pn, पूर्णांक unit);
अटल पूर्णांक ppp_connect_channel(काष्ठा channel *pch, पूर्णांक unit);
अटल पूर्णांक ppp_disconnect_channel(काष्ठा channel *pch);
अटल व्योम ppp_destroy_channel(काष्ठा channel *pch);
अटल पूर्णांक unit_get(काष्ठा idr *p, व्योम *ptr);
अटल पूर्णांक unit_set(काष्ठा idr *p, व्योम *ptr, पूर्णांक n);
अटल व्योम unit_put(काष्ठा idr *p, पूर्णांक n);
अटल व्योम *unit_find(काष्ठा idr *p, पूर्णांक n);
अटल व्योम ppp_setup(काष्ठा net_device *dev);

अटल स्थिर काष्ठा net_device_ops ppp_netdev_ops;

अटल काष्ठा class *ppp_class;

/* per net-namespace data */
अटल अंतरभूत काष्ठा ppp_net *ppp_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, ppp_net_id);
पूर्ण

/* Translates a PPP protocol number to a NP index (NP == network protocol) */
अटल अंतरभूत पूर्णांक proto_to_npindex(पूर्णांक proto)
अणु
	चयन (proto) अणु
	हाल PPP_IP:
		वापस NP_IP;
	हाल PPP_IPV6:
		वापस NP_IPV6;
	हाल PPP_IPX:
		वापस NP_IPX;
	हाल PPP_AT:
		वापस NP_AT;
	हाल PPP_MPLS_UC:
		वापस NP_MPLS_UC;
	हाल PPP_MPLS_MC:
		वापस NP_MPLS_MC;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Translates an NP index पूर्णांकo a PPP protocol number */
अटल स्थिर पूर्णांक npindex_to_proto[NUM_NP] = अणु
	PPP_IP,
	PPP_IPV6,
	PPP_IPX,
	PPP_AT,
	PPP_MPLS_UC,
	PPP_MPLS_MC,
पूर्ण;

/* Translates an ethertype पूर्णांकo an NP index */
अटल अंतरभूत पूर्णांक ethertype_to_npindex(पूर्णांक ethertype)
अणु
	चयन (ethertype) अणु
	हाल ETH_P_IP:
		वापस NP_IP;
	हाल ETH_P_IPV6:
		वापस NP_IPV6;
	हाल ETH_P_IPX:
		वापस NP_IPX;
	हाल ETH_P_PPPTALK:
	हाल ETH_P_ATALK:
		वापस NP_AT;
	हाल ETH_P_MPLS_UC:
		वापस NP_MPLS_UC;
	हाल ETH_P_MPLS_MC:
		वापस NP_MPLS_MC;
	पूर्ण
	वापस -1;
पूर्ण

/* Translates an NP index पूर्णांकo an ethertype */
अटल स्थिर पूर्णांक npindex_to_ethertype[NUM_NP] = अणु
	ETH_P_IP,
	ETH_P_IPV6,
	ETH_P_IPX,
	ETH_P_PPPTALK,
	ETH_P_MPLS_UC,
	ETH_P_MPLS_MC,
पूर्ण;

/*
 * Locking लघुhand.
 */
#घोषणा ppp_xmit_lock(ppp)	spin_lock_bh(&(ppp)->wlock)
#घोषणा ppp_xmit_unlock(ppp)	spin_unlock_bh(&(ppp)->wlock)
#घोषणा ppp_recv_lock(ppp)	spin_lock_bh(&(ppp)->rlock)
#घोषणा ppp_recv_unlock(ppp)	spin_unlock_bh(&(ppp)->rlock)
#घोषणा ppp_lock(ppp)		करो अणु ppp_xmit_lock(ppp); \
				     ppp_recv_lock(ppp); पूर्ण जबतक (0)
#घोषणा ppp_unlock(ppp)		करो अणु ppp_recv_unlock(ppp); \
				     ppp_xmit_unlock(ppp); पूर्ण जबतक (0)

/*
 * /dev/ppp device routines.
 * The /dev/ppp device is used by pppd to control the ppp unit.
 * It supports the पढ़ो, ग_लिखो, ioctl and poll functions.
 * Open instances of /dev/ppp can be in one of three states:
 * unattached, attached to a ppp unit, or attached to a ppp channel.
 */
अटल पूर्णांक ppp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 * This could (should?) be enक्रमced by the permissions on /dev/ppp.
	 */
	अगर (!ns_capable(file->f_cred->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;
	वापस 0;
पूर्ण

अटल पूर्णांक ppp_release(काष्ठा inode *unused, काष्ठा file *file)
अणु
	काष्ठा ppp_file *pf = file->निजी_data;
	काष्ठा ppp *ppp;

	अगर (pf) अणु
		file->निजी_data = शून्य;
		अगर (pf->kind == INTERFACE) अणु
			ppp = PF_TO_PPP(pf);
			rtnl_lock();
			अगर (file == ppp->owner)
				unरेजिस्टर_netdevice(ppp->dev);
			rtnl_unlock();
		पूर्ण
		अगर (refcount_dec_and_test(&pf->refcnt)) अणु
			चयन (pf->kind) अणु
			हाल INTERFACE:
				ppp_destroy_पूर्णांकerface(PF_TO_PPP(pf));
				अवरोध;
			हाल CHANNEL:
				ppp_destroy_channel(PF_TO_CHANNEL(pf));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ppp_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ppp_file *pf = file->निजी_data;
	DECLARE_WAITQUEUE(रुको, current);
	sमाप_प्रकार ret;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा iovec iov;
	काष्ठा iov_iter to;

	ret = count;

	अगर (!pf)
		वापस -ENXIO;
	add_रुको_queue(&pf->rरुको, &रुको);
	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		skb = skb_dequeue(&pf->rq);
		अगर (skb)
			अवरोध;
		ret = 0;
		अगर (pf->dead)
			अवरोध;
		अगर (pf->kind == INTERFACE) अणु
			/*
			 * Return 0 (खातापूर्ण) on an पूर्णांकerface that has no
			 * channels connected, unless it is looping
			 * network traffic (demand mode).
			 */
			काष्ठा ppp *ppp = PF_TO_PPP(pf);

			ppp_recv_lock(ppp);
			अगर (ppp->n_channels == 0 &&
			    (ppp->flags & SC_LOOP_TRAFFIC) == 0) अणु
				ppp_recv_unlock(ppp);
				अवरोध;
			पूर्ण
			ppp_recv_unlock(ppp);
		पूर्ण
		ret = -EAGAIN;
		अगर (file->f_flags & O_NONBLOCK)
			अवरोध;
		ret = -ERESTARTSYS;
		अगर (संकेत_pending(current))
			अवरोध;
		schedule();
	पूर्ण
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&pf->rरुको, &रुको);

	अगर (!skb)
		जाओ out;

	ret = -EOVERFLOW;
	अगर (skb->len > count)
		जाओ outf;
	ret = -EFAULT;
	iov.iov_base = buf;
	iov.iov_len = count;
	iov_iter_init(&to, READ, &iov, 1, count);
	अगर (skb_copy_datagram_iter(skb, 0, &to, skb->len))
		जाओ outf;
	ret = skb->len;

 outf:
	kमुक्त_skb(skb);
 out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ppp_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ppp_file *pf = file->निजी_data;
	काष्ठा sk_buff *skb;
	sमाप_प्रकार ret;

	अगर (!pf)
		वापस -ENXIO;
	ret = -ENOMEM;
	skb = alloc_skb(count + pf->hdrlen, GFP_KERNEL);
	अगर (!skb)
		जाओ out;
	skb_reserve(skb, pf->hdrlen);
	ret = -EFAULT;
	अगर (copy_from_user(skb_put(skb, count), buf, count)) अणु
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	चयन (pf->kind) अणु
	हाल INTERFACE:
		ppp_xmit_process(PF_TO_PPP(pf), skb);
		अवरोध;
	हाल CHANNEL:
		skb_queue_tail(&pf->xq, skb);
		ppp_channel_push(PF_TO_CHANNEL(pf));
		अवरोध;
	पूर्ण

	ret = count;

 out:
	वापस ret;
पूर्ण

/* No kernel lock - fine */
अटल __poll_t ppp_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा ppp_file *pf = file->निजी_data;
	__poll_t mask;

	अगर (!pf)
		वापस 0;
	poll_रुको(file, &pf->rरुको, रुको);
	mask = EPOLLOUT | EPOLLWRNORM;
	अगर (skb_peek(&pf->rq))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (pf->dead)
		mask |= EPOLLHUP;
	अन्यथा अगर (pf->kind == INTERFACE) अणु
		/* see comment in ppp_पढ़ो */
		काष्ठा ppp *ppp = PF_TO_PPP(pf);

		ppp_recv_lock(ppp);
		अगर (ppp->n_channels == 0 &&
		    (ppp->flags & SC_LOOP_TRAFFIC) == 0)
			mask |= EPOLLIN | EPOLLRDNORM;
		ppp_recv_unlock(ppp);
	पूर्ण

	वापस mask;
पूर्ण

#अगर_घोषित CONFIG_PPP_FILTER
अटल काष्ठा bpf_prog *get_filter(काष्ठा sock_fprog *uprog)
अणु
	काष्ठा sock_fprog_kern fprog;
	काष्ठा bpf_prog *res = शून्य;
	पूर्णांक err;

	अगर (!uprog->len)
		वापस शून्य;

	/* uprog->len is अचिन्हित लघु, so no overflow here */
	fprog.len = uprog->len;
	fprog.filter = memdup_user(uprog->filter,
				   uprog->len * माप(काष्ठा sock_filter));
	अगर (IS_ERR(fprog.filter))
		वापस ERR_CAST(fprog.filter);

	err = bpf_prog_create(&res, &fprog);
	kमुक्त(fprog.filter);

	वापस err ? ERR_PTR(err) : res;
पूर्ण

अटल काष्ठा bpf_prog *ppp_get_filter(काष्ठा sock_fprog __user *p)
अणु
	काष्ठा sock_fprog uprog;

	अगर (copy_from_user(&uprog, p, माप(काष्ठा sock_fprog)))
		वापस ERR_PTR(-EFAULT);
	वापस get_filter(&uprog);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा sock_fprog32 अणु
	अचिन्हित लघु len;
	compat_caddr_t filter;
पूर्ण;

#घोषणा PPPIOCSPASS32		_IOW('t', 71, काष्ठा sock_fprog32)
#घोषणा PPPIOCSACTIVE32		_IOW('t', 70, काष्ठा sock_fprog32)

अटल काष्ठा bpf_prog *compat_ppp_get_filter(काष्ठा sock_fprog32 __user *p)
अणु
	काष्ठा sock_fprog32 uprog32;
	काष्ठा sock_fprog uprog;

	अगर (copy_from_user(&uprog32, p, माप(काष्ठा sock_fprog32)))
		वापस ERR_PTR(-EFAULT);
	uprog.len = uprog32.len;
	uprog.filter = compat_ptr(uprog32.filter);
	वापस get_filter(&uprog);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

/* Bridge one PPP channel to another.
 * When two channels are bridged, ppp_input on one channel is redirected to
 * the other's ops->start_xmit handler.
 * In order to safely bridge channels we must reject channels which are alपढ़ोy
 * part of a bridge instance, or which क्रमm part of an existing unit.
 * Once successfully bridged, each channel holds a reference on the other
 * to prevent it being मुक्तd जबतक the bridge is extant.
 */
अटल पूर्णांक ppp_bridge_channels(काष्ठा channel *pch, काष्ठा channel *pchb)
अणु
	ग_लिखो_lock_bh(&pch->upl);
	अगर (pch->ppp ||
	    rcu_dereference_रक्षित(pch->bridge, lockdep_is_held(&pch->upl))) अणु
		ग_लिखो_unlock_bh(&pch->upl);
		वापस -EALREADY;
	पूर्ण
	refcount_inc(&pchb->file.refcnt);
	rcu_assign_poपूर्णांकer(pch->bridge, pchb);
	ग_लिखो_unlock_bh(&pch->upl);

	ग_लिखो_lock_bh(&pchb->upl);
	अगर (pchb->ppp ||
	    rcu_dereference_रक्षित(pchb->bridge, lockdep_is_held(&pchb->upl))) अणु
		ग_लिखो_unlock_bh(&pchb->upl);
		जाओ err_unset;
	पूर्ण
	refcount_inc(&pch->file.refcnt);
	rcu_assign_poपूर्णांकer(pchb->bridge, pch);
	ग_लिखो_unlock_bh(&pchb->upl);

	वापस 0;

err_unset:
	ग_लिखो_lock_bh(&pch->upl);
	/* Re-पढ़ो pch->bridge with upl held in हाल it was modअगरied concurrently */
	pchb = rcu_dereference_रक्षित(pch->bridge, lockdep_is_held(&pch->upl));
	RCU_INIT_POINTER(pch->bridge, शून्य);
	ग_लिखो_unlock_bh(&pch->upl);
	synchronize_rcu();

	अगर (pchb)
		अगर (refcount_dec_and_test(&pchb->file.refcnt))
			ppp_destroy_channel(pchb);

	वापस -EALREADY;
पूर्ण

अटल पूर्णांक ppp_unbridge_channels(काष्ठा channel *pch)
अणु
	काष्ठा channel *pchb, *pchbb;

	ग_लिखो_lock_bh(&pch->upl);
	pchb = rcu_dereference_रक्षित(pch->bridge, lockdep_is_held(&pch->upl));
	अगर (!pchb) अणु
		ग_लिखो_unlock_bh(&pch->upl);
		वापस -EINVAL;
	पूर्ण
	RCU_INIT_POINTER(pch->bridge, शून्य);
	ग_लिखो_unlock_bh(&pch->upl);

	/* Only modअगरy pchb अगर phcb->bridge poपूर्णांकs back to pch.
	 * If not, it implies that there has been a race unbridging (and possibly
	 * even rebridging) pchb.  We should leave pchb alone to aव्योम either a
	 * refcount underflow, or अवरोधing another established bridge instance.
	 */
	ग_लिखो_lock_bh(&pchb->upl);
	pchbb = rcu_dereference_रक्षित(pchb->bridge, lockdep_is_held(&pchb->upl));
	अगर (pchbb == pch)
		RCU_INIT_POINTER(pchb->bridge, शून्य);
	ग_लिखो_unlock_bh(&pchb->upl);

	synchronize_rcu();

	अगर (pchbb == pch)
		अगर (refcount_dec_and_test(&pch->file.refcnt))
			ppp_destroy_channel(pch);

	अगर (refcount_dec_and_test(&pchb->file.refcnt))
		ppp_destroy_channel(pchb);

	वापस 0;
पूर्ण

अटल दीर्घ ppp_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ppp_file *pf;
	काष्ठा ppp *ppp;
	पूर्णांक err = -EFAULT, val, val2, i;
	काष्ठा ppp_idle32 idle32;
	काष्ठा ppp_idle64 idle64;
	काष्ठा npioctl npi;
	पूर्णांक unit, cflags;
	काष्ठा slcompress *vj;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;

	mutex_lock(&ppp_mutex);

	pf = file->निजी_data;
	अगर (!pf) अणु
		err = ppp_unattached_ioctl(current->nsproxy->net_ns,
					   pf, file, cmd, arg);
		जाओ out;
	पूर्ण

	अगर (cmd == PPPIOCDETACH) अणु
		/*
		 * PPPIOCDETACH is no दीर्घer supported as it was heavily broken,
		 * and is only known to have been used by pppd older than
		 * ppp-2.4.2 (released November 2003).
		 */
		pr_warn_once("%s (%d) used obsolete PPPIOCDETACH ioctl\n",
			     current->comm, current->pid);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (pf->kind == CHANNEL) अणु
		काष्ठा channel *pch, *pchb;
		काष्ठा ppp_channel *chan;
		काष्ठा ppp_net *pn;

		pch = PF_TO_CHANNEL(pf);

		चयन (cmd) अणु
		हाल PPPIOCCONNECT:
			अगर (get_user(unit, p))
				अवरोध;
			err = ppp_connect_channel(pch, unit);
			अवरोध;

		हाल PPPIOCDISCONN:
			err = ppp_disconnect_channel(pch);
			अवरोध;

		हाल PPPIOCBRIDGECHAN:
			अगर (get_user(unit, p))
				अवरोध;
			err = -ENXIO;
			pn = ppp_pernet(current->nsproxy->net_ns);
			spin_lock_bh(&pn->all_channels_lock);
			pchb = ppp_find_channel(pn, unit);
			/* Hold a reference to prevent pchb being मुक्तd जबतक
			 * we establish the bridge.
			 */
			अगर (pchb)
				refcount_inc(&pchb->file.refcnt);
			spin_unlock_bh(&pn->all_channels_lock);
			अगर (!pchb)
				अवरोध;
			err = ppp_bridge_channels(pch, pchb);
			/* Drop earlier refcount now bridge establishment is complete */
			अगर (refcount_dec_and_test(&pchb->file.refcnt))
				ppp_destroy_channel(pchb);
			अवरोध;

		हाल PPPIOCUNBRIDGECHAN:
			err = ppp_unbridge_channels(pch);
			अवरोध;

		शेष:
			करोwn_पढ़ो(&pch->chan_sem);
			chan = pch->chan;
			err = -ENOTTY;
			अगर (chan && chan->ops->ioctl)
				err = chan->ops->ioctl(chan, cmd, arg);
			up_पढ़ो(&pch->chan_sem);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (pf->kind != INTERFACE) अणु
		/* can't happen */
		pr_err("PPP: not interface or channel??\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	ppp = PF_TO_PPP(pf);
	चयन (cmd) अणु
	हाल PPPIOCSMRU:
		अगर (get_user(val, p))
			अवरोध;
		ppp->mru = val;
		err = 0;
		अवरोध;

	हाल PPPIOCSFLAGS:
		अगर (get_user(val, p))
			अवरोध;
		ppp_lock(ppp);
		cflags = ppp->flags & ~val;
#अगर_घोषित CONFIG_PPP_MULTILINK
		अगर (!(ppp->flags & SC_MULTILINK) && (val & SC_MULTILINK))
			ppp->nextseq = 0;
#पूर्ण_अगर
		ppp->flags = val & SC_FLAG_BITS;
		ppp_unlock(ppp);
		अगर (cflags & SC_CCP_OPEN)
			ppp_ccp_बंदd(ppp);
		err = 0;
		अवरोध;

	हाल PPPIOCGFLAGS:
		val = ppp->flags | ppp->xstate | ppp->rstate;
		अगर (put_user(val, p))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCSCOMPRESS:
	अणु
		काष्ठा ppp_option_data data;
		अगर (copy_from_user(&data, argp, माप(data)))
			err = -EFAULT;
		अन्यथा
			err = ppp_set_compress(ppp, &data);
		अवरोध;
	पूर्ण
	हाल PPPIOCGUNIT:
		अगर (put_user(ppp->file.index, p))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCSDEBUG:
		अगर (get_user(val, p))
			अवरोध;
		ppp->debug = val;
		err = 0;
		अवरोध;

	हाल PPPIOCGDEBUG:
		अगर (put_user(ppp->debug, p))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCGIDLE32:
                idle32.xmit_idle = (jअगरfies - ppp->last_xmit) / HZ;
                idle32.recv_idle = (jअगरfies - ppp->last_recv) / HZ;
                अगर (copy_to_user(argp, &idle32, माप(idle32)))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCGIDLE64:
		idle64.xmit_idle = (jअगरfies - ppp->last_xmit) / HZ;
		idle64.recv_idle = (jअगरfies - ppp->last_recv) / HZ;
		अगर (copy_to_user(argp, &idle64, माप(idle64)))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCSMAXCID:
		अगर (get_user(val, p))
			अवरोध;
		val2 = 15;
		अगर ((val >> 16) != 0) अणु
			val2 = val >> 16;
			val &= 0xffff;
		पूर्ण
		vj = slhc_init(val2+1, val+1);
		अगर (IS_ERR(vj)) अणु
			err = PTR_ERR(vj);
			अवरोध;
		पूर्ण
		ppp_lock(ppp);
		अगर (ppp->vj)
			slhc_मुक्त(ppp->vj);
		ppp->vj = vj;
		ppp_unlock(ppp);
		err = 0;
		अवरोध;

	हाल PPPIOCGNPMODE:
	हाल PPPIOCSNPMODE:
		अगर (copy_from_user(&npi, argp, माप(npi)))
			अवरोध;
		err = proto_to_npindex(npi.protocol);
		अगर (err < 0)
			अवरोध;
		i = err;
		अगर (cmd == PPPIOCGNPMODE) अणु
			err = -EFAULT;
			npi.mode = ppp->npmode[i];
			अगर (copy_to_user(argp, &npi, माप(npi)))
				अवरोध;
		पूर्ण अन्यथा अणु
			ppp->npmode[i] = npi.mode;
			/* we may be able to transmit more packets now (??) */
			netअगर_wake_queue(ppp->dev);
		पूर्ण
		err = 0;
		अवरोध;

#अगर_घोषित CONFIG_PPP_FILTER
	हाल PPPIOCSPASS:
	हाल PPPIOCSACTIVE:
	अणु
		काष्ठा bpf_prog *filter = ppp_get_filter(argp);
		काष्ठा bpf_prog **which;

		अगर (IS_ERR(filter)) अणु
			err = PTR_ERR(filter);
			अवरोध;
		पूर्ण
		अगर (cmd == PPPIOCSPASS)
			which = &ppp->pass_filter;
		अन्यथा
			which = &ppp->active_filter;
		ppp_lock(ppp);
		अगर (*which)
			bpf_prog_destroy(*which);
		*which = filter;
		ppp_unlock(ppp);
		err = 0;
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPP_FILTER */

#अगर_घोषित CONFIG_PPP_MULTILINK
	हाल PPPIOCSMRRU:
		अगर (get_user(val, p))
			अवरोध;
		ppp_recv_lock(ppp);
		ppp->mrru = val;
		ppp_recv_unlock(ppp);
		err = 0;
		अवरोध;
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */

	शेष:
		err = -ENOTTY;
	पूर्ण

out:
	mutex_unlock(&ppp_mutex);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा ppp_option_data32 अणु
	compat_uptr_t		ptr;
	u32			length;
	compat_पूर्णांक_t		transmit;
पूर्ण;
#घोषणा PPPIOCSCOMPRESS32	_IOW('t', 77, काष्ठा ppp_option_data32)

अटल दीर्घ ppp_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ppp_file *pf;
	पूर्णांक err = -ENOIOCTLCMD;
	व्योम __user *argp = (व्योम __user *)arg;

	mutex_lock(&ppp_mutex);

	pf = file->निजी_data;
	अगर (pf && pf->kind == INTERFACE) अणु
		काष्ठा ppp *ppp = PF_TO_PPP(pf);
		चयन (cmd) अणु
#अगर_घोषित CONFIG_PPP_FILTER
		हाल PPPIOCSPASS32:
		हाल PPPIOCSACTIVE32:
		अणु
			काष्ठा bpf_prog *filter = compat_ppp_get_filter(argp);
			काष्ठा bpf_prog **which;

			अगर (IS_ERR(filter)) अणु
				err = PTR_ERR(filter);
				अवरोध;
			पूर्ण
			अगर (cmd == PPPIOCSPASS32)
				which = &ppp->pass_filter;
			अन्यथा
				which = &ppp->active_filter;
			ppp_lock(ppp);
			अगर (*which)
				bpf_prog_destroy(*which);
			*which = filter;
			ppp_unlock(ppp);
			err = 0;
			अवरोध;
		पूर्ण
#पूर्ण_अगर /* CONFIG_PPP_FILTER */
		हाल PPPIOCSCOMPRESS32:
		अणु
			काष्ठा ppp_option_data32 data32;
			अगर (copy_from_user(&data32, argp, माप(data32))) अणु
				err = -EFAULT;
			पूर्ण अन्यथा अणु
				काष्ठा ppp_option_data data = अणु
					.ptr = compat_ptr(data32.ptr),
					.length = data32.length,
					.transmit = data32.transmit
				पूर्ण;
				err = ppp_set_compress(ppp, &data);
			पूर्ण
			अवरोध;
		पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&ppp_mutex);

	/* all other commands have compatible arguments */
	अगर (err == -ENOIOCTLCMD)
		err = ppp_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ppp_unattached_ioctl(काष्ठा net *net, काष्ठा ppp_file *pf,
			काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक unit, err = -EFAULT;
	काष्ठा ppp *ppp;
	काष्ठा channel *chan;
	काष्ठा ppp_net *pn;
	पूर्णांक __user *p = (पूर्णांक __user *)arg;

	चयन (cmd) अणु
	हाल PPPIOCNEWUNIT:
		/* Create a new ppp unit */
		अगर (get_user(unit, p))
			अवरोध;
		err = ppp_create_पूर्णांकerface(net, file, &unit);
		अगर (err < 0)
			अवरोध;

		err = -EFAULT;
		अगर (put_user(unit, p))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCATTACH:
		/* Attach to an existing ppp unit */
		अगर (get_user(unit, p))
			अवरोध;
		err = -ENXIO;
		pn = ppp_pernet(net);
		mutex_lock(&pn->all_ppp_mutex);
		ppp = ppp_find_unit(pn, unit);
		अगर (ppp) अणु
			refcount_inc(&ppp->file.refcnt);
			file->निजी_data = &ppp->file;
			err = 0;
		पूर्ण
		mutex_unlock(&pn->all_ppp_mutex);
		अवरोध;

	हाल PPPIOCATTCHAN:
		अगर (get_user(unit, p))
			अवरोध;
		err = -ENXIO;
		pn = ppp_pernet(net);
		spin_lock_bh(&pn->all_channels_lock);
		chan = ppp_find_channel(pn, unit);
		अगर (chan) अणु
			refcount_inc(&chan->file.refcnt);
			file->निजी_data = &chan->file;
			err = 0;
		पूर्ण
		spin_unlock_bh(&pn->all_channels_lock);
		अवरोध;

	शेष:
		err = -ENOTTY;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations ppp_device_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= ppp_पढ़ो,
	.ग_लिखो		= ppp_ग_लिखो,
	.poll		= ppp_poll,
	.unlocked_ioctl	= ppp_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= ppp_compat_ioctl,
#पूर्ण_अगर
	.खोलो		= ppp_खोलो,
	.release	= ppp_release,
	.llseek		= noop_llseek,
पूर्ण;

अटल __net_init पूर्णांक ppp_init_net(काष्ठा net *net)
अणु
	काष्ठा ppp_net *pn = net_generic(net, ppp_net_id);

	idr_init(&pn->units_idr);
	mutex_init(&pn->all_ppp_mutex);

	INIT_LIST_HEAD(&pn->all_channels);
	INIT_LIST_HEAD(&pn->new_channels);

	spin_lock_init(&pn->all_channels_lock);

	वापस 0;
पूर्ण

अटल __net_निकास व्योम ppp_निकास_net(काष्ठा net *net)
अणु
	काष्ठा ppp_net *pn = net_generic(net, ppp_net_id);
	काष्ठा net_device *dev;
	काष्ठा net_device *aux;
	काष्ठा ppp *ppp;
	LIST_HEAD(list);
	पूर्णांक id;

	rtnl_lock();
	क्रम_each_netdev_safe(net, dev, aux) अणु
		अगर (dev->netdev_ops == &ppp_netdev_ops)
			unरेजिस्टर_netdevice_queue(dev, &list);
	पूर्ण

	idr_क्रम_each_entry(&pn->units_idr, ppp, id)
		/* Skip devices alपढ़ोy unरेजिस्टरed by previous loop */
		अगर (!net_eq(dev_net(ppp->dev), net))
			unरेजिस्टर_netdevice_queue(ppp->dev, &list);

	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();

	mutex_destroy(&pn->all_ppp_mutex);
	idr_destroy(&pn->units_idr);
	WARN_ON_ONCE(!list_empty(&pn->all_channels));
	WARN_ON_ONCE(!list_empty(&pn->new_channels));
पूर्ण

अटल काष्ठा pernet_operations ppp_net_ops = अणु
	.init = ppp_init_net,
	.निकास = ppp_निकास_net,
	.id   = &ppp_net_id,
	.size = माप(काष्ठा ppp_net),
पूर्ण;

अटल पूर्णांक ppp_unit_रेजिस्टर(काष्ठा ppp *ppp, पूर्णांक unit, bool अगरname_is_set)
अणु
	काष्ठा ppp_net *pn = ppp_pernet(ppp->ppp_net);
	पूर्णांक ret;

	mutex_lock(&pn->all_ppp_mutex);

	अगर (unit < 0) अणु
		ret = unit_get(&pn->units_idr, ppp);
		अगर (ret < 0)
			जाओ err;
	पूर्ण अन्यथा अणु
		/* Caller asked क्रम a specअगरic unit number. Fail with -EEXIST
		 * अगर unavailable. For backward compatibility, वापस -EEXIST
		 * too अगर idr allocation fails; this makes pppd retry without
		 * requesting a specअगरic unit number.
		 */
		अगर (unit_find(&pn->units_idr, unit)) अणु
			ret = -EEXIST;
			जाओ err;
		पूर्ण
		ret = unit_set(&pn->units_idr, ppp, unit);
		अगर (ret < 0) अणु
			/* Reग_लिखो error क्रम backward compatibility */
			ret = -EEXIST;
			जाओ err;
		पूर्ण
	पूर्ण
	ppp->file.index = ret;

	अगर (!अगरname_is_set)
		snम_लिखो(ppp->dev->name, IFNAMSIZ, "ppp%i", ppp->file.index);

	mutex_unlock(&pn->all_ppp_mutex);

	ret = रेजिस्टर_netdevice(ppp->dev);
	अगर (ret < 0)
		जाओ err_unit;

	atomic_inc(&ppp_unit_count);

	वापस 0;

err_unit:
	mutex_lock(&pn->all_ppp_mutex);
	unit_put(&pn->units_idr, ppp->file.index);
err:
	mutex_unlock(&pn->all_ppp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ppp_dev_configure(काष्ठा net *src_net, काष्ठा net_device *dev,
			     स्थिर काष्ठा ppp_config *conf)
अणु
	काष्ठा ppp *ppp = netdev_priv(dev);
	पूर्णांक indx;
	पूर्णांक err;
	पूर्णांक cpu;

	ppp->dev = dev;
	ppp->ppp_net = src_net;
	ppp->mru = PPP_MRU;
	ppp->owner = conf->file;

	init_ppp_file(&ppp->file, INTERFACE);
	ppp->file.hdrlen = PPP_HDRLEN - 2; /* करोn't count proto bytes */

	क्रम (indx = 0; indx < NUM_NP; ++indx)
		ppp->npmode[indx] = NPMODE_PASS;
	INIT_LIST_HEAD(&ppp->channels);
	spin_lock_init(&ppp->rlock);
	spin_lock_init(&ppp->wlock);

	ppp->xmit_recursion = alloc_percpu(पूर्णांक);
	अगर (!ppp->xmit_recursion) अणु
		err = -ENOMEM;
		जाओ err1;
	पूर्ण
	क्रम_each_possible_cpu(cpu)
		(*per_cpu_ptr(ppp->xmit_recursion, cpu)) = 0;

#अगर_घोषित CONFIG_PPP_MULTILINK
	ppp->minseq = -1;
	skb_queue_head_init(&ppp->mrq);
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */
#अगर_घोषित CONFIG_PPP_FILTER
	ppp->pass_filter = शून्य;
	ppp->active_filter = शून्य;
#पूर्ण_अगर /* CONFIG_PPP_FILTER */

	err = ppp_unit_रेजिस्टर(ppp, conf->unit, conf->अगरname_is_set);
	अगर (err < 0)
		जाओ err2;

	conf->file->निजी_data = &ppp->file;

	वापस 0;
err2:
	मुक्त_percpu(ppp->xmit_recursion);
err1:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy ppp_nl_policy[IFLA_PPP_MAX + 1] = अणु
	[IFLA_PPP_DEV_FD]	= अणु .type = NLA_S32 पूर्ण,
पूर्ण;

अटल पूर्णांक ppp_nl_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	अगर (!data)
		वापस -EINVAL;

	अगर (!data[IFLA_PPP_DEV_FD])
		वापस -EINVAL;
	अगर (nla_get_s32(data[IFLA_PPP_DEV_FD]) < 0)
		वापस -EBADF;

	वापस 0;
पूर्ण

अटल पूर्णांक ppp_nl_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ppp_config conf = अणु
		.unit = -1,
		.अगरname_is_set = true,
	पूर्ण;
	काष्ठा file *file;
	पूर्णांक err;

	file = fget(nla_get_s32(data[IFLA_PPP_DEV_FD]));
	अगर (!file)
		वापस -EBADF;

	/* rtnl_lock is alपढ़ोy held here, but ppp_create_पूर्णांकerface() locks
	 * ppp_mutex beक्रमe holding rtnl_lock. Using mutex_trylock() aव्योमs
	 * possible deadlock due to lock order inversion, at the cost of
	 * pushing the problem back to userspace.
	 */
	अगर (!mutex_trylock(&ppp_mutex)) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (file->f_op != &ppp_device_fops || file->निजी_data) अणु
		err = -EBADF;
		जाओ out_unlock;
	पूर्ण

	conf.file = file;

	/* Don't use device name generated by the rtnetlink layer when अगरname
	 * isn't specअगरied. Let ppp_dev_configure() set the device name using
	 * the PPP unit identअगरer as suffix (i.e. ppp<unit_id>). This allows
	 * userspace to infer the device name using to the PPPIOCGUNIT ioctl.
	 */
	अगर (!tb[IFLA_IFNAME])
		conf.अगरname_is_set = false;

	err = ppp_dev_configure(src_net, dev, &conf);

out_unlock:
	mutex_unlock(&ppp_mutex);
out:
	fput(file);

	वापस err;
पूर्ण

अटल व्योम ppp_nl_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल माप_प्रकार ppp_nl_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ppp_nl_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा net *ppp_nl_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ppp *ppp = netdev_priv(dev);

	वापस ppp->ppp_net;
पूर्ण

अटल काष्ठा rtnl_link_ops ppp_link_ops __पढ़ो_mostly = अणु
	.kind		= "ppp",
	.maxtype	= IFLA_PPP_MAX,
	.policy		= ppp_nl_policy,
	.priv_size	= माप(काष्ठा ppp),
	.setup		= ppp_setup,
	.validate	= ppp_nl_validate,
	.newlink	= ppp_nl_newlink,
	.dellink	= ppp_nl_dellink,
	.get_size	= ppp_nl_get_size,
	.fill_info	= ppp_nl_fill_info,
	.get_link_net	= ppp_nl_get_link_net,
पूर्ण;

#घोषणा PPP_MAJOR	108

/* Called at boot समय अगर ppp is compiled पूर्णांकo the kernel,
   or at module load समय (from init_module) अगर compiled as a module. */
अटल पूर्णांक __init ppp_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("PPP generic driver version " PPP_VERSION "\n");

	err = रेजिस्टर_pernet_device(&ppp_net_ops);
	अगर (err) अणु
		pr_err("failed to register PPP pernet device (%d)\n", err);
		जाओ out;
	पूर्ण

	err = रेजिस्टर_chrdev(PPP_MAJOR, "ppp", &ppp_device_fops);
	अगर (err) अणु
		pr_err("failed to register PPP device (%d)\n", err);
		जाओ out_net;
	पूर्ण

	ppp_class = class_create(THIS_MODULE, "ppp");
	अगर (IS_ERR(ppp_class)) अणु
		err = PTR_ERR(ppp_class);
		जाओ out_chrdev;
	पूर्ण

	err = rtnl_link_रेजिस्टर(&ppp_link_ops);
	अगर (err) अणु
		pr_err("failed to register rtnetlink PPP handler\n");
		जाओ out_class;
	पूर्ण

	/* not a big deal अगर we fail here :-) */
	device_create(ppp_class, शून्य, MKDEV(PPP_MAJOR, 0), शून्य, "ppp");

	वापस 0;

out_class:
	class_destroy(ppp_class);
out_chrdev:
	unरेजिस्टर_chrdev(PPP_MAJOR, "ppp");
out_net:
	unरेजिस्टर_pernet_device(&ppp_net_ops);
out:
	वापस err;
पूर्ण

/*
 * Network पूर्णांकerface unit routines.
 */
अटल netdev_tx_t
ppp_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ppp *ppp = netdev_priv(dev);
	पूर्णांक npi, proto;
	अचिन्हित अक्षर *pp;

	npi = ethertype_to_npindex(ntohs(skb->protocol));
	अगर (npi < 0)
		जाओ outf;

	/* Drop, accept or reject the packet */
	चयन (ppp->npmode[npi]) अणु
	हाल NPMODE_PASS:
		अवरोध;
	हाल NPMODE_QUEUE:
		/* it would be nice to have a way to tell the network
		   प्रणाली to queue this one up क्रम later. */
		जाओ outf;
	हाल NPMODE_DROP:
	हाल NPMODE_ERROR:
		जाओ outf;
	पूर्ण

	/* Put the 2-byte PPP protocol number on the front,
	   making sure there is room क्रम the address and control fields. */
	अगर (skb_cow_head(skb, PPP_HDRLEN))
		जाओ outf;

	pp = skb_push(skb, 2);
	proto = npindex_to_proto[npi];
	put_unaligned_be16(proto, pp);

	skb_scrub_packet(skb, !net_eq(ppp->ppp_net, dev_net(dev)));
	ppp_xmit_process(ppp, skb);

	वापस NETDEV_TX_OK;

 outf:
	kमुक्त_skb(skb);
	++dev->stats.tx_dropped;
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक
ppp_net_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा ppp *ppp = netdev_priv(dev);
	पूर्णांक err = -EFAULT;
	व्योम __user *addr = (व्योम __user *) अगरr->अगरr_अगरru.अगरru_data;
	काष्ठा ppp_stats stats;
	काष्ठा ppp_comp_stats cstats;
	अक्षर *vers;

	चयन (cmd) अणु
	हाल SIOCGPPPSTATS:
		ppp_get_stats(ppp, &stats);
		अगर (copy_to_user(addr, &stats, माप(stats)))
			अवरोध;
		err = 0;
		अवरोध;

	हाल SIOCGPPPCSTATS:
		स_रखो(&cstats, 0, माप(cstats));
		अगर (ppp->xc_state)
			ppp->xcomp->comp_stat(ppp->xc_state, &cstats.c);
		अगर (ppp->rc_state)
			ppp->rcomp->decomp_stat(ppp->rc_state, &cstats.d);
		अगर (copy_to_user(addr, &cstats, माप(cstats)))
			अवरोध;
		err = 0;
		अवरोध;

	हाल SIOCGPPPVER:
		vers = PPP_VERSION;
		अगर (copy_to_user(addr, vers, म_माप(vers) + 1))
			अवरोध;
		err = 0;
		अवरोध;

	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम
ppp_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats64)
अणु
	काष्ठा ppp *ppp = netdev_priv(dev);

	ppp_recv_lock(ppp);
	stats64->rx_packets = ppp->stats64.rx_packets;
	stats64->rx_bytes   = ppp->stats64.rx_bytes;
	ppp_recv_unlock(ppp);

	ppp_xmit_lock(ppp);
	stats64->tx_packets = ppp->stats64.tx_packets;
	stats64->tx_bytes   = ppp->stats64.tx_bytes;
	ppp_xmit_unlock(ppp);

	stats64->rx_errors        = dev->stats.rx_errors;
	stats64->tx_errors        = dev->stats.tx_errors;
	stats64->rx_dropped       = dev->stats.rx_dropped;
	stats64->tx_dropped       = dev->stats.tx_dropped;
	stats64->rx_length_errors = dev->stats.rx_length_errors;
पूर्ण

अटल पूर्णांक ppp_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा ppp *ppp;

	netdev_lockdep_set_classes(dev);

	ppp = netdev_priv(dev);
	/* Let the netdevice take a reference on the ppp file. This ensures
	 * that ppp_destroy_पूर्णांकerface() won't run beक्रमe the device माला_लो
	 * unरेजिस्टरed.
	 */
	refcount_inc(&ppp->file.refcnt);

	वापस 0;
पूर्ण

अटल व्योम ppp_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ppp *ppp = netdev_priv(dev);
	काष्ठा ppp_net *pn = ppp_pernet(ppp->ppp_net);

	ppp_lock(ppp);
	ppp->closing = 1;
	ppp_unlock(ppp);

	mutex_lock(&pn->all_ppp_mutex);
	unit_put(&pn->units_idr, ppp->file.index);
	mutex_unlock(&pn->all_ppp_mutex);

	ppp->owner = शून्य;

	ppp->file.dead = 1;
	wake_up_पूर्णांकerruptible(&ppp->file.rरुको);
पूर्ण

अटल व्योम ppp_dev_priv_deकाष्ठाor(काष्ठा net_device *dev)
अणु
	काष्ठा ppp *ppp;

	ppp = netdev_priv(dev);
	अगर (refcount_dec_and_test(&ppp->file.refcnt))
		ppp_destroy_पूर्णांकerface(ppp);
पूर्ण

अटल पूर्णांक ppp_fill_क्रमward_path(काष्ठा net_device_path_ctx *ctx,
				 काष्ठा net_device_path *path)
अणु
	काष्ठा ppp *ppp = netdev_priv(ctx->dev);
	काष्ठा ppp_channel *chan;
	काष्ठा channel *pch;

	अगर (ppp->flags & SC_MULTILINK)
		वापस -EOPNOTSUPP;

	अगर (list_empty(&ppp->channels))
		वापस -ENODEV;

	pch = list_first_entry(&ppp->channels, काष्ठा channel, clist);
	chan = pch->chan;
	अगर (!chan->ops->fill_क्रमward_path)
		वापस -EOPNOTSUPP;

	वापस chan->ops->fill_क्रमward_path(ctx, path, chan);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ppp_netdev_ops = अणु
	.nकरो_init	 = ppp_dev_init,
	.nकरो_uninit      = ppp_dev_uninit,
	.nकरो_start_xmit  = ppp_start_xmit,
	.nकरो_करो_ioctl    = ppp_net_ioctl,
	.nकरो_get_stats64 = ppp_get_stats64,
	.nकरो_fill_क्रमward_path = ppp_fill_क्रमward_path,
पूर्ण;

अटल काष्ठा device_type ppp_type = अणु
	.name = "ppp",
पूर्ण;

अटल व्योम ppp_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &ppp_netdev_ops;
	SET_NETDEV_DEVTYPE(dev, &ppp_type);

	dev->features |= NETIF_F_LLTX;

	dev->hard_header_len = PPP_HDRLEN;
	dev->mtu = PPP_MRU;
	dev->addr_len = 0;
	dev->tx_queue_len = 3;
	dev->type = ARPHRD_PPP;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	dev->priv_deकाष्ठाor = ppp_dev_priv_deकाष्ठाor;
	netअगर_keep_dst(dev);
पूर्ण

/*
 * Transmit-side routines.
 */

/* Called to करो any work queued up on the transmit side that can now be करोne */
अटल व्योम __ppp_xmit_process(काष्ठा ppp *ppp, काष्ठा sk_buff *skb)
अणु
	ppp_xmit_lock(ppp);
	अगर (!ppp->closing) अणु
		ppp_push(ppp);

		अगर (skb)
			skb_queue_tail(&ppp->file.xq, skb);
		जबतक (!ppp->xmit_pending &&
		       (skb = skb_dequeue(&ppp->file.xq)))
			ppp_send_frame(ppp, skb);
		/* If there's no work left to करो, tell the core net
		   code that we can accept some more. */
		अगर (!ppp->xmit_pending && !skb_peek(&ppp->file.xq))
			netअगर_wake_queue(ppp->dev);
		अन्यथा
			netअगर_stop_queue(ppp->dev);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण
	ppp_xmit_unlock(ppp);
पूर्ण

अटल व्योम ppp_xmit_process(काष्ठा ppp *ppp, काष्ठा sk_buff *skb)
अणु
	local_bh_disable();

	अगर (unlikely(*this_cpu_ptr(ppp->xmit_recursion)))
		जाओ err;

	(*this_cpu_ptr(ppp->xmit_recursion))++;
	__ppp_xmit_process(ppp, skb);
	(*this_cpu_ptr(ppp->xmit_recursion))--;

	local_bh_enable();

	वापस;

err:
	local_bh_enable();

	kमुक्त_skb(skb);

	अगर (net_ratelimit())
		netdev_err(ppp->dev, "recursion detected\n");
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
pad_compress_skb(काष्ठा ppp *ppp, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *new_skb;
	पूर्णांक len;
	पूर्णांक new_skb_size = ppp->dev->mtu +
		ppp->xcomp->comp_extra + ppp->dev->hard_header_len;
	पूर्णांक compressor_skb_size = ppp->dev->mtu +
		ppp->xcomp->comp_extra + PPP_HDRLEN;
	new_skb = alloc_skb(new_skb_size, GFP_ATOMIC);
	अगर (!new_skb) अणु
		अगर (net_ratelimit())
			netdev_err(ppp->dev, "PPP: no memory (comp pkt)\n");
		वापस शून्य;
	पूर्ण
	अगर (ppp->dev->hard_header_len > PPP_HDRLEN)
		skb_reserve(new_skb,
			    ppp->dev->hard_header_len - PPP_HDRLEN);

	/* compressor still expects A/C bytes in hdr */
	len = ppp->xcomp->compress(ppp->xc_state, skb->data - 2,
				   new_skb->data, skb->len + 2,
				   compressor_skb_size);
	अगर (len > 0 && (ppp->flags & SC_CCP_UP)) अणु
		consume_skb(skb);
		skb = new_skb;
		skb_put(skb, len);
		skb_pull(skb, 2);	/* pull off A/C bytes */
	पूर्ण अन्यथा अगर (len == 0) अणु
		/* didn't compress, or CCP not up yet */
		consume_skb(new_skb);
		new_skb = skb;
	पूर्ण अन्यथा अणु
		/*
		 * (len < 0)
		 * MPPE requires that we करो not send unencrypted
		 * frames.  The compressor will वापस -1 अगर we
		 * should drop the frame.  We cannot simply test
		 * the compress_proto because MPPE and MPPC share
		 * the same number.
		 */
		अगर (net_ratelimit())
			netdev_err(ppp->dev, "ppp: compressor dropped pkt\n");
		kमुक्त_skb(skb);
		consume_skb(new_skb);
		new_skb = शून्य;
	पूर्ण
	वापस new_skb;
पूर्ण

/*
 * Compress and send a frame.
 * The caller should have locked the xmit path,
 * and xmit_pending should be 0.
 */
अटल व्योम
ppp_send_frame(काष्ठा ppp *ppp, काष्ठा sk_buff *skb)
अणु
	पूर्णांक proto = PPP_PROTO(skb);
	काष्ठा sk_buff *new_skb;
	पूर्णांक len;
	अचिन्हित अक्षर *cp;

	अगर (proto < 0x8000) अणु
#अगर_घोषित CONFIG_PPP_FILTER
		/* check अगर we should pass this packet */
		/* the filter inकाष्ठाions are स्थिरructed assuming
		   a four-byte PPP header on each packet */
		*(u8 *)skb_push(skb, 2) = 1;
		अगर (ppp->pass_filter &&
		    BPF_PROG_RUN(ppp->pass_filter, skb) == 0) अणु
			अगर (ppp->debug & 1)
				netdev_prपूर्णांकk(KERN_DEBUG, ppp->dev,
					      "PPP: outbound frame "
					      "not passed\n");
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
		/* अगर this packet passes the active filter, record the समय */
		अगर (!(ppp->active_filter &&
		      BPF_PROG_RUN(ppp->active_filter, skb) == 0))
			ppp->last_xmit = jअगरfies;
		skb_pull(skb, 2);
#अन्यथा
		/* क्रम data packets, record the समय */
		ppp->last_xmit = jअगरfies;
#पूर्ण_अगर /* CONFIG_PPP_FILTER */
	पूर्ण

	++ppp->stats64.tx_packets;
	ppp->stats64.tx_bytes += skb->len - 2;

	चयन (proto) अणु
	हाल PPP_IP:
		अगर (!ppp->vj || (ppp->flags & SC_COMP_TCP) == 0)
			अवरोध;
		/* try to करो VJ TCP header compression */
		new_skb = alloc_skb(skb->len + ppp->dev->hard_header_len - 2,
				    GFP_ATOMIC);
		अगर (!new_skb) अणु
			netdev_err(ppp->dev, "PPP: no memory (VJ comp pkt)\n");
			जाओ drop;
		पूर्ण
		skb_reserve(new_skb, ppp->dev->hard_header_len - 2);
		cp = skb->data + 2;
		len = slhc_compress(ppp->vj, cp, skb->len - 2,
				    new_skb->data + 2, &cp,
				    !(ppp->flags & SC_NO_TCP_CCID));
		अगर (cp == skb->data + 2) अणु
			/* didn't compress */
			consume_skb(new_skb);
		पूर्ण अन्यथा अणु
			अगर (cp[0] & SL_TYPE_COMPRESSED_TCP) अणु
				proto = PPP_VJC_COMP;
				cp[0] &= ~SL_TYPE_COMPRESSED_TCP;
			पूर्ण अन्यथा अणु
				proto = PPP_VJC_UNCOMP;
				cp[0] = skb->data[2];
			पूर्ण
			consume_skb(skb);
			skb = new_skb;
			cp = skb_put(skb, len + 2);
			cp[0] = 0;
			cp[1] = proto;
		पूर्ण
		अवरोध;

	हाल PPP_CCP:
		/* peek at outbound CCP frames */
		ppp_ccp_peek(ppp, skb, 0);
		अवरोध;
	पूर्ण

	/* try to करो packet compression */
	अगर ((ppp->xstate & SC_COMP_RUN) && ppp->xc_state &&
	    proto != PPP_LCP && proto != PPP_CCP) अणु
		अगर (!(ppp->flags & SC_CCP_UP) && (ppp->flags & SC_MUST_COMP)) अणु
			अगर (net_ratelimit())
				netdev_err(ppp->dev,
					   "ppp: compression required but "
					   "down - pkt dropped.\n");
			जाओ drop;
		पूर्ण
		skb = pad_compress_skb(ppp, skb);
		अगर (!skb)
			जाओ drop;
	पूर्ण

	/*
	 * If we are रुकोing क्रम traffic (demand dialling),
	 * queue it up क्रम pppd to receive.
	 */
	अगर (ppp->flags & SC_LOOP_TRAFFIC) अणु
		अगर (ppp->file.rq.qlen > PPP_MAX_RQLEN)
			जाओ drop;
		skb_queue_tail(&ppp->file.rq, skb);
		wake_up_पूर्णांकerruptible(&ppp->file.rरुको);
		वापस;
	पूर्ण

	ppp->xmit_pending = skb;
	ppp_push(ppp);
	वापस;

 drop:
	kमुक्त_skb(skb);
	++ppp->dev->stats.tx_errors;
पूर्ण

/*
 * Try to send the frame in xmit_pending.
 * The caller should have the xmit path locked.
 */
अटल व्योम
ppp_push(काष्ठा ppp *ppp)
अणु
	काष्ठा list_head *list;
	काष्ठा channel *pch;
	काष्ठा sk_buff *skb = ppp->xmit_pending;

	अगर (!skb)
		वापस;

	list = &ppp->channels;
	अगर (list_empty(list)) अणु
		/* nowhere to send the packet, just drop it */
		ppp->xmit_pending = शून्य;
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर ((ppp->flags & SC_MULTILINK) == 0) अणु
		/* not करोing multilink: send it करोwn the first channel */
		list = list->next;
		pch = list_entry(list, काष्ठा channel, clist);

		spin_lock(&pch->करोwnl);
		अगर (pch->chan) अणु
			अगर (pch->chan->ops->start_xmit(pch->chan, skb))
				ppp->xmit_pending = शून्य;
		पूर्ण अन्यथा अणु
			/* channel got unरेजिस्टरed */
			kमुक्त_skb(skb);
			ppp->xmit_pending = शून्य;
		पूर्ण
		spin_unlock(&pch->करोwnl);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_PPP_MULTILINK
	/* Multilink: fragment the packet over as many links
	   as can take the packet at the moment. */
	अगर (!ppp_mp_explode(ppp, skb))
		वापस;
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */

	ppp->xmit_pending = शून्य;
	kमुक्त_skb(skb);
पूर्ण

#अगर_घोषित CONFIG_PPP_MULTILINK
अटल bool mp_protocol_compress __पढ़ो_mostly = true;
module_param(mp_protocol_compress, bool, 0644);
MODULE_PARM_DESC(mp_protocol_compress,
		 "compress protocol id in multilink fragments");

/*
 * Divide a packet to be transmitted पूर्णांकo fragments and
 * send them out the inभागidual links.
 */
अटल पूर्णांक ppp_mp_explode(काष्ठा ppp *ppp, काष्ठा sk_buff *skb)
अणु
	पूर्णांक len, totlen;
	पूर्णांक i, bits, hdrlen, mtu;
	पूर्णांक flen;
	पूर्णांक navail, nमुक्त, nzero;
	पूर्णांक nbigger;
	पूर्णांक totspeed;
	पूर्णांक totमुक्त;
	अचिन्हित अक्षर *p, *q;
	काष्ठा list_head *list;
	काष्ठा channel *pch;
	काष्ठा sk_buff *frag;
	काष्ठा ppp_channel *chan;

	totspeed = 0; /*total bitrate of the bundle*/
	nमुक्त = 0; /* # channels which have no packet alपढ़ोy queued */
	navail = 0; /* total # of usable channels (not deरेजिस्टरed) */
	nzero = 0; /* number of channels with zero speed associated*/
	totमुक्त = 0; /*total # of channels available and
				  *having no queued packets beक्रमe
				  *starting the fragmentation*/

	hdrlen = (ppp->flags & SC_MP_XSHORTSEQ)? MPHDRLEN_SSN: MPHDRLEN;
	i = 0;
	list_क्रम_each_entry(pch, &ppp->channels, clist) अणु
		अगर (pch->chan) अणु
			pch->avail = 1;
			navail++;
			pch->speed = pch->chan->speed;
		पूर्ण अन्यथा अणु
			pch->avail = 0;
		पूर्ण
		अगर (pch->avail) अणु
			अगर (skb_queue_empty(&pch->file.xq) ||
				!pch->had_frag) अणु
					अगर (pch->speed == 0)
						nzero++;
					अन्यथा
						totspeed += pch->speed;

					pch->avail = 2;
					++nमुक्त;
					++totमुक्त;
				पूर्ण
			अगर (!pch->had_frag && i < ppp->nxchan)
				ppp->nxchan = i;
		पूर्ण
		++i;
	पूर्ण
	/*
	 * Don't start sending this packet unless at least half of
	 * the channels are मुक्त.  This gives much better TCP
	 * perक्रमmance अगर we have a lot of channels.
	 */
	अगर (nमुक्त == 0 || nमुक्त < navail / 2)
		वापस 0; /* can't take now, leave it in xmit_pending */

	/* Do protocol field compression */
	p = skb->data;
	len = skb->len;
	अगर (*p == 0 && mp_protocol_compress) अणु
		++p;
		--len;
	पूर्ण

	totlen = len;
	nbigger = len % nमुक्त;

	/* skip to the channel after the one we last used
	   and start at that one */
	list = &ppp->channels;
	क्रम (i = 0; i < ppp->nxchan; ++i) अणु
		list = list->next;
		अगर (list == &ppp->channels) अणु
			i = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* create a fragment क्रम each channel */
	bits = B;
	जबतक (len > 0) अणु
		list = list->next;
		अगर (list == &ppp->channels) अणु
			i = 0;
			जारी;
		पूर्ण
		pch = list_entry(list, काष्ठा channel, clist);
		++i;
		अगर (!pch->avail)
			जारी;

		/*
		 * Skip this channel अगर it has a fragment pending alपढ़ोy and
		 * we haven't given a fragment to all of the मुक्त channels.
		 */
		अगर (pch->avail == 1) अणु
			अगर (nमुक्त > 0)
				जारी;
		पूर्ण अन्यथा अणु
			pch->avail = 1;
		पूर्ण

		/* check the channel's mtu and whether it is still attached. */
		spin_lock(&pch->करोwnl);
		अगर (pch->chan == शून्य) अणु
			/* can't use this channel, it's being deरेजिस्टरed */
			अगर (pch->speed == 0)
				nzero--;
			अन्यथा
				totspeed -= pch->speed;

			spin_unlock(&pch->करोwnl);
			pch->avail = 0;
			totlen = len;
			totमुक्त--;
			nमुक्त--;
			अगर (--navail == 0)
				अवरोध;
			जारी;
		पूर्ण

		/*
		*अगर the channel speed is not set भागide
		*the packet evenly among the मुक्त channels;
		*otherwise भागide it according to the speed
		*of the channel we are going to transmit on
		*/
		flen = len;
		अगर (nमुक्त > 0) अणु
			अगर (pch->speed == 0) अणु
				flen = len/nमुक्त;
				अगर (nbigger > 0) अणु
					flen++;
					nbigger--;
				पूर्ण
			पूर्ण अन्यथा अणु
				flen = (((totमुक्त - nzero)*(totlen + hdrlen*totमुक्त)) /
					((totspeed*totमुक्त)/pch->speed)) - hdrlen;
				अगर (nbigger > 0) अणु
					flen += ((totमुक्त - nzero)*pch->speed)/totspeed;
					nbigger -= ((totमुक्त - nzero)*pch->speed)/
							totspeed;
				पूर्ण
			पूर्ण
			nमुक्त--;
		पूर्ण

		/*
		 *check अगर we are on the last channel or
		 *we exceded the length of the data to
		 *fragment
		 */
		अगर ((nमुक्त <= 0) || (flen > len))
			flen = len;
		/*
		 *it is not worth to tx on slow channels:
		 *in that हाल from the resulting flen according to the
		 *above क्रमmula will be equal or less than zero.
		 *Skip the channel in this हाल
		 */
		अगर (flen <= 0) अणु
			pch->avail = 2;
			spin_unlock(&pch->करोwnl);
			जारी;
		पूर्ण

		/*
		 * hdrlen includes the 2-byte PPP protocol field, but the
		 * MTU counts only the payload excluding the protocol field.
		 * (RFC1661 Section 2)
		 */
		mtu = pch->chan->mtu - (hdrlen - 2);
		अगर (mtu < 4)
			mtu = 4;
		अगर (flen > mtu)
			flen = mtu;
		अगर (flen == len)
			bits |= E;
		frag = alloc_skb(flen + hdrlen + (flen == 0), GFP_ATOMIC);
		अगर (!frag)
			जाओ noskb;
		q = skb_put(frag, flen + hdrlen);

		/* make the MP header */
		put_unaligned_be16(PPP_MP, q);
		अगर (ppp->flags & SC_MP_XSHORTSEQ) अणु
			q[2] = bits + ((ppp->nxseq >> 8) & 0xf);
			q[3] = ppp->nxseq;
		पूर्ण अन्यथा अणु
			q[2] = bits;
			q[3] = ppp->nxseq >> 16;
			q[4] = ppp->nxseq >> 8;
			q[5] = ppp->nxseq;
		पूर्ण

		स_नकल(q + hdrlen, p, flen);

		/* try to send it करोwn the channel */
		chan = pch->chan;
		अगर (!skb_queue_empty(&pch->file.xq) ||
			!chan->ops->start_xmit(chan, frag))
			skb_queue_tail(&pch->file.xq, frag);
		pch->had_frag = 1;
		p += flen;
		len -= flen;
		++ppp->nxseq;
		bits = 0;
		spin_unlock(&pch->करोwnl);
	पूर्ण
	ppp->nxchan = i;

	वापस 1;

 noskb:
	spin_unlock(&pch->करोwnl);
	अगर (ppp->debug & 1)
		netdev_err(ppp->dev, "PPP: no memory (fragment)\n");
	++ppp->dev->stats.tx_errors;
	++ppp->nxseq;
	वापस 1;	/* abanकरोn the frame */
पूर्ण
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */

/* Try to send data out on a channel */
अटल व्योम __ppp_channel_push(काष्ठा channel *pch)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ppp *ppp;

	spin_lock(&pch->करोwnl);
	अगर (pch->chan) अणु
		जबतक (!skb_queue_empty(&pch->file.xq)) अणु
			skb = skb_dequeue(&pch->file.xq);
			अगर (!pch->chan->ops->start_xmit(pch->chan, skb)) अणु
				/* put the packet back and try again later */
				skb_queue_head(&pch->file.xq, skb);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* channel got deरेजिस्टरed */
		skb_queue_purge(&pch->file.xq);
	पूर्ण
	spin_unlock(&pch->करोwnl);
	/* see अगर there is anything from the attached unit to be sent */
	अगर (skb_queue_empty(&pch->file.xq)) अणु
		ppp = pch->ppp;
		अगर (ppp)
			__ppp_xmit_process(ppp, शून्य);
	पूर्ण
पूर्ण

अटल व्योम ppp_channel_push(काष्ठा channel *pch)
अणु
	पढ़ो_lock_bh(&pch->upl);
	अगर (pch->ppp) अणु
		(*this_cpu_ptr(pch->ppp->xmit_recursion))++;
		__ppp_channel_push(pch);
		(*this_cpu_ptr(pch->ppp->xmit_recursion))--;
	पूर्ण अन्यथा अणु
		__ppp_channel_push(pch);
	पूर्ण
	पढ़ो_unlock_bh(&pch->upl);
पूर्ण

/*
 * Receive-side routines.
 */

काष्ठा ppp_mp_skb_parm अणु
	u32		sequence;
	u8		BEbits;
पूर्ण;
#घोषणा PPP_MP_CB(skb)	((काष्ठा ppp_mp_skb_parm *)((skb)->cb))

अटल अंतरभूत व्योम
ppp_करो_recv(काष्ठा ppp *ppp, काष्ठा sk_buff *skb, काष्ठा channel *pch)
अणु
	ppp_recv_lock(ppp);
	अगर (!ppp->closing)
		ppp_receive_frame(ppp, skb, pch);
	अन्यथा
		kमुक्त_skb(skb);
	ppp_recv_unlock(ppp);
पूर्ण

/**
 * __ppp_decompress_proto - Decompress protocol field, slim version.
 * @skb: Socket buffer where protocol field should be decompressed. It must have
 *	 at least 1 byte of head room and 1 byte of linear data. First byte of
 *	 data must be a protocol field byte.
 *
 * Decompress protocol field in PPP header अगर it's compressed, e.g. when
 * Protocol-Field-Compression (PFC) was negotiated. No checks w.r.t. skb data
 * length are करोne in this function.
 */
अटल व्योम __ppp_decompress_proto(काष्ठा sk_buff *skb)
अणु
	अगर (skb->data[0] & 0x01)
		*(u8 *)skb_push(skb, 1) = 0x00;
पूर्ण

/**
 * ppp_decompress_proto - Check skb data room and decompress protocol field.
 * @skb: Socket buffer where protocol field should be decompressed. First byte
 *	 of data must be a protocol field byte.
 *
 * Decompress protocol field in PPP header अगर it's compressed, e.g. when
 * Protocol-Field-Compression (PFC) was negotiated. This function also makes
 * sure that skb data room is sufficient क्रम Protocol field, beक्रमe and after
 * decompression.
 *
 * Return: true - decompressed successfully, false - not enough room in skb.
 */
अटल bool ppp_decompress_proto(काष्ठा sk_buff *skb)
अणु
	/* At least one byte should be present (अगर protocol is compressed) */
	अगर (!pskb_may_pull(skb, 1))
		वापस false;

	__ppp_decompress_proto(skb);

	/* Protocol field should occupy 2 bytes when not compressed */
	वापस pskb_may_pull(skb, 2);
पूर्ण

/* Attempt to handle a frame via. a bridged channel, अगर one exists.
 * If the channel is bridged, the frame is consumed by the bridge.
 * If not, the caller must handle the frame by normal recv mechanisms.
 * Returns true अगर the frame is consumed, false otherwise.
 */
अटल bool ppp_channel_bridge_input(काष्ठा channel *pch, काष्ठा sk_buff *skb)
अणु
	काष्ठा channel *pchb;

	rcu_पढ़ो_lock();
	pchb = rcu_dereference(pch->bridge);
	अगर (!pchb)
		जाओ out_rcu;

	spin_lock(&pchb->करोwnl);
	अगर (!pchb->chan) अणु
		/* channel got unरेजिस्टरed */
		kमुक्त_skb(skb);
		जाओ outl;
	पूर्ण

	skb_scrub_packet(skb, !net_eq(pch->chan_net, pchb->chan_net));
	अगर (!pchb->chan->ops->start_xmit(pchb->chan, skb))
		kमुक्त_skb(skb);

outl:
	spin_unlock(&pchb->करोwnl);
out_rcu:
	rcu_पढ़ो_unlock();

	/* If pchb is set then we've consumed the packet */
	वापस !!pchb;
पूर्ण

व्योम
ppp_input(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा channel *pch = chan->ppp;
	पूर्णांक proto;

	अगर (!pch) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* If the channel is bridged, transmit via. bridge */
	अगर (ppp_channel_bridge_input(pch, skb))
		वापस;

	पढ़ो_lock_bh(&pch->upl);
	अगर (!ppp_decompress_proto(skb)) अणु
		kमुक्त_skb(skb);
		अगर (pch->ppp) अणु
			++pch->ppp->dev->stats.rx_length_errors;
			ppp_receive_error(pch->ppp);
		पूर्ण
		जाओ करोne;
	पूर्ण

	proto = PPP_PROTO(skb);
	अगर (!pch->ppp || proto >= 0xc000 || proto == PPP_CCPFRAG) अणु
		/* put it on the channel queue */
		skb_queue_tail(&pch->file.rq, skb);
		/* drop old frames अगर queue too दीर्घ */
		जबतक (pch->file.rq.qlen > PPP_MAX_RQLEN &&
		       (skb = skb_dequeue(&pch->file.rq)))
			kमुक्त_skb(skb);
		wake_up_पूर्णांकerruptible(&pch->file.rरुको);
	पूर्ण अन्यथा अणु
		ppp_करो_recv(pch->ppp, skb, pch);
	पूर्ण

करोne:
	पढ़ो_unlock_bh(&pch->upl);
पूर्ण

/* Put a 0-length skb in the receive queue as an error indication */
व्योम
ppp_input_error(काष्ठा ppp_channel *chan, पूर्णांक code)
अणु
	काष्ठा channel *pch = chan->ppp;
	काष्ठा sk_buff *skb;

	अगर (!pch)
		वापस;

	पढ़ो_lock_bh(&pch->upl);
	अगर (pch->ppp) अणु
		skb = alloc_skb(0, GFP_ATOMIC);
		अगर (skb) अणु
			skb->len = 0;		/* probably unnecessary */
			skb->cb[0] = code;
			ppp_करो_recv(pch->ppp, skb, pch);
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&pch->upl);
पूर्ण

/*
 * We come in here to process a received frame.
 * The receive side of the ppp unit is locked.
 */
अटल व्योम
ppp_receive_frame(काष्ठा ppp *ppp, काष्ठा sk_buff *skb, काष्ठा channel *pch)
अणु
	/* note: a 0-length skb is used as an error indication */
	अगर (skb->len > 0) अणु
		skb_checksum_complete_unset(skb);
#अगर_घोषित CONFIG_PPP_MULTILINK
		/* XXX करो channel-level decompression here */
		अगर (PPP_PROTO(skb) == PPP_MP)
			ppp_receive_mp_frame(ppp, skb, pch);
		अन्यथा
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */
			ppp_receive_nonmp_frame(ppp, skb);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
		ppp_receive_error(ppp);
	पूर्ण
पूर्ण

अटल व्योम
ppp_receive_error(काष्ठा ppp *ppp)
अणु
	++ppp->dev->stats.rx_errors;
	अगर (ppp->vj)
		slhc_toss(ppp->vj);
पूर्ण

अटल व्योम
ppp_receive_nonmp_frame(काष्ठा ppp *ppp, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *ns;
	पूर्णांक proto, len, npi;

	/*
	 * Decompress the frame, अगर compressed.
	 * Note that some decompressors need to see uncompressed frames
	 * that come in as well as compressed frames.
	 */
	अगर (ppp->rc_state && (ppp->rstate & SC_DECOMP_RUN) &&
	    (ppp->rstate & (SC_DC_FERROR | SC_DC_ERROR)) == 0)
		skb = ppp_decompress_frame(ppp, skb);

	अगर (ppp->flags & SC_MUST_COMP && ppp->rstate & SC_DC_FERROR)
		जाओ err;

	/* At this poपूर्णांक the "Protocol" field MUST be decompressed, either in
	 * ppp_input(), ppp_decompress_frame() or in ppp_receive_mp_frame().
	 */
	proto = PPP_PROTO(skb);
	चयन (proto) अणु
	हाल PPP_VJC_COMP:
		/* decompress VJ compressed packets */
		अगर (!ppp->vj || (ppp->flags & SC_REJ_COMP_TCP))
			जाओ err;

		अगर (skb_tailroom(skb) < 124 || skb_cloned(skb)) अणु
			/* copy to a new sk_buff with more tailroom */
			ns = dev_alloc_skb(skb->len + 128);
			अगर (!ns) अणु
				netdev_err(ppp->dev, "PPP: no memory "
					   "(VJ decomp)\n");
				जाओ err;
			पूर्ण
			skb_reserve(ns, 2);
			skb_copy_bits(skb, 0, skb_put(ns, skb->len), skb->len);
			consume_skb(skb);
			skb = ns;
		पूर्ण
		अन्यथा
			skb->ip_summed = CHECKSUM_NONE;

		len = slhc_uncompress(ppp->vj, skb->data + 2, skb->len - 2);
		अगर (len <= 0) अणु
			netdev_prपूर्णांकk(KERN_DEBUG, ppp->dev,
				      "PPP: VJ decompression error\n");
			जाओ err;
		पूर्ण
		len += 2;
		अगर (len > skb->len)
			skb_put(skb, len - skb->len);
		अन्यथा अगर (len < skb->len)
			skb_trim(skb, len);
		proto = PPP_IP;
		अवरोध;

	हाल PPP_VJC_UNCOMP:
		अगर (!ppp->vj || (ppp->flags & SC_REJ_COMP_TCP))
			जाओ err;

		/* Until we fix the decompressor need to make sure
		 * data portion is linear.
		 */
		अगर (!pskb_may_pull(skb, skb->len))
			जाओ err;

		अगर (slhc_remember(ppp->vj, skb->data + 2, skb->len - 2) <= 0) अणु
			netdev_err(ppp->dev, "PPP: VJ uncompressed error\n");
			जाओ err;
		पूर्ण
		proto = PPP_IP;
		अवरोध;

	हाल PPP_CCP:
		ppp_ccp_peek(ppp, skb, 1);
		अवरोध;
	पूर्ण

	++ppp->stats64.rx_packets;
	ppp->stats64.rx_bytes += skb->len - 2;

	npi = proto_to_npindex(proto);
	अगर (npi < 0) अणु
		/* control or unknown frame - pass it to pppd */
		skb_queue_tail(&ppp->file.rq, skb);
		/* limit queue length by dropping old frames */
		जबतक (ppp->file.rq.qlen > PPP_MAX_RQLEN &&
		       (skb = skb_dequeue(&ppp->file.rq)))
			kमुक्त_skb(skb);
		/* wake up any process polling or blocking on पढ़ो */
		wake_up_पूर्णांकerruptible(&ppp->file.rरुको);

	पूर्ण अन्यथा अणु
		/* network protocol frame - give it to the kernel */

#अगर_घोषित CONFIG_PPP_FILTER
		/* check अगर the packet passes the pass and active filters */
		/* the filter inकाष्ठाions are स्थिरructed assuming
		   a four-byte PPP header on each packet */
		अगर (ppp->pass_filter || ppp->active_filter) अणु
			अगर (skb_unclone(skb, GFP_ATOMIC))
				जाओ err;

			*(u8 *)skb_push(skb, 2) = 0;
			अगर (ppp->pass_filter &&
			    BPF_PROG_RUN(ppp->pass_filter, skb) == 0) अणु
				अगर (ppp->debug & 1)
					netdev_prपूर्णांकk(KERN_DEBUG, ppp->dev,
						      "PPP: inbound frame "
						      "not passed\n");
				kमुक्त_skb(skb);
				वापस;
			पूर्ण
			अगर (!(ppp->active_filter &&
			      BPF_PROG_RUN(ppp->active_filter, skb) == 0))
				ppp->last_recv = jअगरfies;
			__skb_pull(skb, 2);
		पूर्ण अन्यथा
#पूर्ण_अगर /* CONFIG_PPP_FILTER */
			ppp->last_recv = jअगरfies;

		अगर ((ppp->dev->flags & IFF_UP) == 0 ||
		    ppp->npmode[npi] != NPMODE_PASS) अणु
			kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			/* chop off protocol */
			skb_pull_rcsum(skb, 2);
			skb->dev = ppp->dev;
			skb->protocol = htons(npindex_to_ethertype[npi]);
			skb_reset_mac_header(skb);
			skb_scrub_packet(skb, !net_eq(ppp->ppp_net,
						      dev_net(ppp->dev)));
			netअगर_rx(skb);
		पूर्ण
	पूर्ण
	वापस;

 err:
	kमुक्त_skb(skb);
	ppp_receive_error(ppp);
पूर्ण

अटल काष्ठा sk_buff *
ppp_decompress_frame(काष्ठा ppp *ppp, काष्ठा sk_buff *skb)
अणु
	पूर्णांक proto = PPP_PROTO(skb);
	काष्ठा sk_buff *ns;
	पूर्णांक len;

	/* Until we fix all the decompressor's need to make sure
	 * data portion is linear.
	 */
	अगर (!pskb_may_pull(skb, skb->len))
		जाओ err;

	अगर (proto == PPP_COMP) अणु
		पूर्णांक obuff_size;

		चयन(ppp->rcomp->compress_proto) अणु
		हाल CI_MPPE:
			obuff_size = ppp->mru + PPP_HDRLEN + 1;
			अवरोध;
		शेष:
			obuff_size = ppp->mru + PPP_HDRLEN;
			अवरोध;
		पूर्ण

		ns = dev_alloc_skb(obuff_size);
		अगर (!ns) अणु
			netdev_err(ppp->dev, "ppp_decompress_frame: "
				   "no memory\n");
			जाओ err;
		पूर्ण
		/* the decompressor still expects the A/C bytes in the hdr */
		len = ppp->rcomp->decompress(ppp->rc_state, skb->data - 2,
				skb->len + 2, ns->data, obuff_size);
		अगर (len < 0) अणु
			/* Pass the compressed frame to pppd as an
			   error indication. */
			अगर (len == DECOMP_FATALERROR)
				ppp->rstate |= SC_DC_FERROR;
			kमुक्त_skb(ns);
			जाओ err;
		पूर्ण

		consume_skb(skb);
		skb = ns;
		skb_put(skb, len);
		skb_pull(skb, 2);	/* pull off the A/C bytes */

		/* Don't call __ppp_decompress_proto() here, but instead rely on
		 * corresponding algo (mppe/bsd/deflate) to decompress it.
		 */
	पूर्ण अन्यथा अणु
		/* Uncompressed frame - pass to decompressor so it
		   can update its dictionary अगर necessary. */
		अगर (ppp->rcomp->incomp)
			ppp->rcomp->incomp(ppp->rc_state, skb->data - 2,
					   skb->len + 2);
	पूर्ण

	वापस skb;

 err:
	ppp->rstate |= SC_DC_ERROR;
	ppp_receive_error(ppp);
	वापस skb;
पूर्ण

#अगर_घोषित CONFIG_PPP_MULTILINK
/*
 * Receive a multilink frame.
 * We put it on the reस्थिरruction queue and then pull off
 * as many completed frames as we can.
 */
अटल व्योम
ppp_receive_mp_frame(काष्ठा ppp *ppp, काष्ठा sk_buff *skb, काष्ठा channel *pch)
अणु
	u32 mask, seq;
	काष्ठा channel *ch;
	पूर्णांक mphdrlen = (ppp->flags & SC_MP_SHORTSEQ)? MPHDRLEN_SSN: MPHDRLEN;

	अगर (!pskb_may_pull(skb, mphdrlen + 1) || ppp->mrru == 0)
		जाओ err;		/* no good, throw it away */

	/* Decode sequence number and begin/end bits */
	अगर (ppp->flags & SC_MP_SHORTSEQ) अणु
		seq = ((skb->data[2] & 0x0f) << 8) | skb->data[3];
		mask = 0xfff;
	पूर्ण अन्यथा अणु
		seq = (skb->data[3] << 16) | (skb->data[4] << 8)| skb->data[5];
		mask = 0xffffff;
	पूर्ण
	PPP_MP_CB(skb)->BEbits = skb->data[2];
	skb_pull(skb, mphdrlen);	/* pull off PPP and MP headers */

	/*
	 * Do protocol ID decompression on the first fragment of each packet.
	 * We have to करो that here, because ppp_receive_nonmp_frame() expects
	 * decompressed protocol field.
	 */
	अगर (PPP_MP_CB(skb)->BEbits & B)
		__ppp_decompress_proto(skb);

	/*
	 * Expand sequence number to 32 bits, making it as बंद
	 * as possible to ppp->minseq.
	 */
	seq |= ppp->minseq & ~mask;
	अगर ((पूर्णांक)(ppp->minseq - seq) > (पूर्णांक)(mask >> 1))
		seq += mask + 1;
	अन्यथा अगर ((पूर्णांक)(seq - ppp->minseq) > (पूर्णांक)(mask >> 1))
		seq -= mask + 1;	/* should never happen */
	PPP_MP_CB(skb)->sequence = seq;
	pch->lastseq = seq;

	/*
	 * If this packet comes beक्रमe the next one we were expecting,
	 * drop it.
	 */
	अगर (seq_beक्रमe(seq, ppp->nextseq)) अणु
		kमुक्त_skb(skb);
		++ppp->dev->stats.rx_dropped;
		ppp_receive_error(ppp);
		वापस;
	पूर्ण

	/*
	 * Reevaluate minseq, the minimum over all channels of the
	 * last sequence number received on each channel.  Because of
	 * the increasing sequence number rule, we know that any fragment
	 * beक्रमe `minseq' which hasn't arrived is never going to arrive.
	 * The list of channels can't change because we have the receive
	 * side of the ppp unit locked.
	 */
	list_क्रम_each_entry(ch, &ppp->channels, clist) अणु
		अगर (seq_beक्रमe(ch->lastseq, seq))
			seq = ch->lastseq;
	पूर्ण
	अगर (seq_beक्रमe(ppp->minseq, seq))
		ppp->minseq = seq;

	/* Put the fragment on the reस्थिरruction queue */
	ppp_mp_insert(ppp, skb);

	/* If the queue is getting दीर्घ, करोn't रुको any दीर्घer क्रम packets
	   beक्रमe the start of the queue. */
	अगर (skb_queue_len(&ppp->mrq) >= PPP_MP_MAX_QLEN) अणु
		काष्ठा sk_buff *mskb = skb_peek(&ppp->mrq);
		अगर (seq_beक्रमe(ppp->minseq, PPP_MP_CB(mskb)->sequence))
			ppp->minseq = PPP_MP_CB(mskb)->sequence;
	पूर्ण

	/* Pull completed packets off the queue and receive them. */
	जबतक ((skb = ppp_mp_reस्थिरruct(ppp))) अणु
		अगर (pskb_may_pull(skb, 2))
			ppp_receive_nonmp_frame(ppp, skb);
		अन्यथा अणु
			++ppp->dev->stats.rx_length_errors;
			kमुक्त_skb(skb);
			ppp_receive_error(ppp);
		पूर्ण
	पूर्ण

	वापस;

 err:
	kमुक्त_skb(skb);
	ppp_receive_error(ppp);
पूर्ण

/*
 * Insert a fragment on the MP reस्थिरruction queue.
 * The queue is ordered by increasing sequence number.
 */
अटल व्योम
ppp_mp_insert(काष्ठा ppp *ppp, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *p;
	काष्ठा sk_buff_head *list = &ppp->mrq;
	u32 seq = PPP_MP_CB(skb)->sequence;

	/* N.B. we करोn't need to lock the list lock because we have the
	   ppp unit receive-side lock. */
	skb_queue_walk(list, p) अणु
		अगर (seq_beक्रमe(seq, PPP_MP_CB(p)->sequence))
			अवरोध;
	पूर्ण
	__skb_queue_beक्रमe(list, p, skb);
पूर्ण

/*
 * Reस्थिरruct a packet from the MP fragment queue.
 * We go through increasing sequence numbers until we find a
 * complete packet, or we get to the sequence number क्रम a fragment
 * which hasn't arrived but might still करो so.
 */
अटल काष्ठा sk_buff *
ppp_mp_reस्थिरruct(काष्ठा ppp *ppp)
अणु
	u32 seq = ppp->nextseq;
	u32 minseq = ppp->minseq;
	काष्ठा sk_buff_head *list = &ppp->mrq;
	काष्ठा sk_buff *p, *पंचांगp;
	काष्ठा sk_buff *head, *tail;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक lost = 0, len = 0;

	अगर (ppp->mrru == 0)	/* करो nothing until mrru is set */
		वापस शून्य;
	head = __skb_peek(list);
	tail = शून्य;
	skb_queue_walk_safe(list, p, पंचांगp) अणु
	again:
		अगर (seq_beक्रमe(PPP_MP_CB(p)->sequence, seq)) अणु
			/* this can't happen, anyway ignore the skb */
			netdev_err(ppp->dev, "ppp_mp_reconstruct bad "
				   "seq %u < %u\n",
				   PPP_MP_CB(p)->sequence, seq);
			__skb_unlink(p, list);
			kमुक्त_skb(p);
			जारी;
		पूर्ण
		अगर (PPP_MP_CB(p)->sequence != seq) अणु
			u32 oldseq;
			/* Fragment `seq' is missing.  If it is after
			   minseq, it might arrive later, so stop here. */
			अगर (seq_after(seq, minseq))
				अवरोध;
			/* Fragment `seq' is lost, keep going. */
			lost = 1;
			oldseq = seq;
			seq = seq_beक्रमe(minseq, PPP_MP_CB(p)->sequence)?
				minseq + 1: PPP_MP_CB(p)->sequence;

			अगर (ppp->debug & 1)
				netdev_prपूर्णांकk(KERN_DEBUG, ppp->dev,
					      "lost frag %u..%u\n",
					      oldseq, seq-1);

			जाओ again;
		पूर्ण

		/*
		 * At this poपूर्णांक we know that all the fragments from
		 * ppp->nextseq to seq are either present or lost.
		 * Also, there are no complete packets in the queue
		 * that have no missing fragments and end beक्रमe this
		 * fragment.
		 */

		/* B bit set indicates this fragment starts a packet */
		अगर (PPP_MP_CB(p)->BEbits & B) अणु
			head = p;
			lost = 0;
			len = 0;
		पूर्ण

		len += p->len;

		/* Got a complete packet yet? */
		अगर (lost == 0 && (PPP_MP_CB(p)->BEbits & E) &&
		    (PPP_MP_CB(head)->BEbits & B)) अणु
			अगर (len > ppp->mrru + 2) अणु
				++ppp->dev->stats.rx_length_errors;
				netdev_prपूर्णांकk(KERN_DEBUG, ppp->dev,
					      "PPP: reconstructed packet"
					      " is too long (%d)\n", len);
			पूर्ण अन्यथा अणु
				tail = p;
				अवरोध;
			पूर्ण
			ppp->nextseq = seq + 1;
		पूर्ण

		/*
		 * If this is the ending fragment of a packet,
		 * and we haven't found a complete valid packet yet,
		 * we can discard up to and including this fragment.
		 */
		अगर (PPP_MP_CB(p)->BEbits & E) अणु
			काष्ठा sk_buff *पंचांगp2;

			skb_queue_reverse_walk_from_safe(list, p, पंचांगp2) अणु
				अगर (ppp->debug & 1)
					netdev_prपूर्णांकk(KERN_DEBUG, ppp->dev,
						      "discarding frag %u\n",
						      PPP_MP_CB(p)->sequence);
				__skb_unlink(p, list);
				kमुक्त_skb(p);
			पूर्ण
			head = skb_peek(list);
			अगर (!head)
				अवरोध;
		पूर्ण
		++seq;
	पूर्ण

	/* If we have a complete packet, copy it all पूर्णांकo one skb. */
	अगर (tail != शून्य) अणु
		/* If we have discarded any fragments,
		   संकेत a receive error. */
		अगर (PPP_MP_CB(head)->sequence != ppp->nextseq) अणु
			skb_queue_walk_safe(list, p, पंचांगp) अणु
				अगर (p == head)
					अवरोध;
				अगर (ppp->debug & 1)
					netdev_prपूर्णांकk(KERN_DEBUG, ppp->dev,
						      "discarding frag %u\n",
						      PPP_MP_CB(p)->sequence);
				__skb_unlink(p, list);
				kमुक्त_skb(p);
			पूर्ण

			अगर (ppp->debug & 1)
				netdev_prपूर्णांकk(KERN_DEBUG, ppp->dev,
					      "  missed pkts %u..%u\n",
					      ppp->nextseq,
					      PPP_MP_CB(head)->sequence-1);
			++ppp->dev->stats.rx_dropped;
			ppp_receive_error(ppp);
		पूर्ण

		skb = head;
		अगर (head != tail) अणु
			काष्ठा sk_buff **fragpp = &skb_shinfo(skb)->frag_list;
			p = skb_queue_next(list, head);
			__skb_unlink(skb, list);
			skb_queue_walk_from_safe(list, p, पंचांगp) अणु
				__skb_unlink(p, list);
				*fragpp = p;
				p->next = शून्य;
				fragpp = &p->next;

				skb->len += p->len;
				skb->data_len += p->len;
				skb->truesize += p->truesize;

				अगर (p == tail)
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			__skb_unlink(skb, list);
		पूर्ण

		ppp->nextseq = PPP_MP_CB(tail)->sequence + 1;
	पूर्ण

	वापस skb;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */

/*
 * Channel पूर्णांकerface.
 */

/* Create a new, unattached ppp channel. */
पूर्णांक ppp_रेजिस्टर_channel(काष्ठा ppp_channel *chan)
अणु
	वापस ppp_रेजिस्टर_net_channel(current->nsproxy->net_ns, chan);
पूर्ण

/* Create a new, unattached ppp channel क्रम specअगरied net. */
पूर्णांक ppp_रेजिस्टर_net_channel(काष्ठा net *net, काष्ठा ppp_channel *chan)
अणु
	काष्ठा channel *pch;
	काष्ठा ppp_net *pn;

	pch = kzalloc(माप(काष्ठा channel), GFP_KERNEL);
	अगर (!pch)
		वापस -ENOMEM;

	pn = ppp_pernet(net);

	pch->ppp = शून्य;
	pch->chan = chan;
	pch->chan_net = get_net(net);
	chan->ppp = pch;
	init_ppp_file(&pch->file, CHANNEL);
	pch->file.hdrlen = chan->hdrlen;
#अगर_घोषित CONFIG_PPP_MULTILINK
	pch->lastseq = -1;
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */
	init_rwsem(&pch->chan_sem);
	spin_lock_init(&pch->करोwnl);
	rwlock_init(&pch->upl);

	spin_lock_bh(&pn->all_channels_lock);
	pch->file.index = ++pn->last_channel_index;
	list_add(&pch->list, &pn->new_channels);
	atomic_inc(&channel_count);
	spin_unlock_bh(&pn->all_channels_lock);

	वापस 0;
पूर्ण

/*
 * Return the index of a channel.
 */
पूर्णांक ppp_channel_index(काष्ठा ppp_channel *chan)
अणु
	काष्ठा channel *pch = chan->ppp;

	अगर (pch)
		वापस pch->file.index;
	वापस -1;
पूर्ण

/*
 * Return the PPP unit number to which a channel is connected.
 */
पूर्णांक ppp_unit_number(काष्ठा ppp_channel *chan)
अणु
	काष्ठा channel *pch = chan->ppp;
	पूर्णांक unit = -1;

	अगर (pch) अणु
		पढ़ो_lock_bh(&pch->upl);
		अगर (pch->ppp)
			unit = pch->ppp->file.index;
		पढ़ो_unlock_bh(&pch->upl);
	पूर्ण
	वापस unit;
पूर्ण

/*
 * Return the PPP device पूर्णांकerface name of a channel.
 */
अक्षर *ppp_dev_name(काष्ठा ppp_channel *chan)
अणु
	काष्ठा channel *pch = chan->ppp;
	अक्षर *name = शून्य;

	अगर (pch) अणु
		पढ़ो_lock_bh(&pch->upl);
		अगर (pch->ppp && pch->ppp->dev)
			name = pch->ppp->dev->name;
		पढ़ो_unlock_bh(&pch->upl);
	पूर्ण
	वापस name;
पूर्ण


/*
 * Disconnect a channel from the generic layer.
 * This must be called in process context.
 */
व्योम
ppp_unरेजिस्टर_channel(काष्ठा ppp_channel *chan)
अणु
	काष्ठा channel *pch = chan->ppp;
	काष्ठा ppp_net *pn;

	अगर (!pch)
		वापस;		/* should never happen */

	chan->ppp = शून्य;

	/*
	 * This ensures that we have वापसed from any calls पूर्णांकo the
	 * the channel's start_xmit or ioctl routine beक्रमe we proceed.
	 */
	करोwn_ग_लिखो(&pch->chan_sem);
	spin_lock_bh(&pch->करोwnl);
	pch->chan = शून्य;
	spin_unlock_bh(&pch->करोwnl);
	up_ग_लिखो(&pch->chan_sem);
	ppp_disconnect_channel(pch);

	pn = ppp_pernet(pch->chan_net);
	spin_lock_bh(&pn->all_channels_lock);
	list_del(&pch->list);
	spin_unlock_bh(&pn->all_channels_lock);

	ppp_unbridge_channels(pch);

	pch->file.dead = 1;
	wake_up_पूर्णांकerruptible(&pch->file.rरुको);

	अगर (refcount_dec_and_test(&pch->file.refcnt))
		ppp_destroy_channel(pch);
पूर्ण

/*
 * Callback from a channel when it can accept more to transmit.
 * This should be called at BH/softirq level, not पूर्णांकerrupt level.
 */
व्योम
ppp_output_wakeup(काष्ठा ppp_channel *chan)
अणु
	काष्ठा channel *pch = chan->ppp;

	अगर (!pch)
		वापस;
	ppp_channel_push(pch);
पूर्ण

/*
 * Compression control.
 */

/* Process the PPPIOCSCOMPRESS ioctl. */
अटल पूर्णांक
ppp_set_compress(काष्ठा ppp *ppp, काष्ठा ppp_option_data *data)
अणु
	पूर्णांक err = -EFAULT;
	काष्ठा compressor *cp, *ocomp;
	व्योम *state, *ostate;
	अचिन्हित अक्षर ccp_option[CCP_MAX_OPTION_LENGTH];

	अगर (data->length > CCP_MAX_OPTION_LENGTH)
		जाओ out;
	अगर (copy_from_user(ccp_option, data->ptr, data->length))
		जाओ out;

	err = -EINVAL;
	अगर (data->length < 2 || ccp_option[1] < 2 || ccp_option[1] > data->length)
		जाओ out;

	cp = try_then_request_module(
		find_compressor(ccp_option[0]),
		"ppp-compress-%d", ccp_option[0]);
	अगर (!cp)
		जाओ out;

	err = -ENOBUFS;
	अगर (data->transmit) अणु
		state = cp->comp_alloc(ccp_option, data->length);
		अगर (state) अणु
			ppp_xmit_lock(ppp);
			ppp->xstate &= ~SC_COMP_RUN;
			ocomp = ppp->xcomp;
			ostate = ppp->xc_state;
			ppp->xcomp = cp;
			ppp->xc_state = state;
			ppp_xmit_unlock(ppp);
			अगर (ostate) अणु
				ocomp->comp_मुक्त(ostate);
				module_put(ocomp->owner);
			पूर्ण
			err = 0;
		पूर्ण अन्यथा
			module_put(cp->owner);

	पूर्ण अन्यथा अणु
		state = cp->decomp_alloc(ccp_option, data->length);
		अगर (state) अणु
			ppp_recv_lock(ppp);
			ppp->rstate &= ~SC_DECOMP_RUN;
			ocomp = ppp->rcomp;
			ostate = ppp->rc_state;
			ppp->rcomp = cp;
			ppp->rc_state = state;
			ppp_recv_unlock(ppp);
			अगर (ostate) अणु
				ocomp->decomp_मुक्त(ostate);
				module_put(ocomp->owner);
			पूर्ण
			err = 0;
		पूर्ण अन्यथा
			module_put(cp->owner);
	पूर्ण

 out:
	वापस err;
पूर्ण

/*
 * Look at a CCP packet and update our state accordingly.
 * We assume the caller has the xmit or recv path locked.
 */
अटल व्योम
ppp_ccp_peek(काष्ठा ppp *ppp, काष्ठा sk_buff *skb, पूर्णांक inbound)
अणु
	अचिन्हित अक्षर *dp;
	पूर्णांक len;

	अगर (!pskb_may_pull(skb, CCP_HDRLEN + 2))
		वापस;	/* no header */
	dp = skb->data + 2;

	चयन (CCP_CODE(dp)) अणु
	हाल CCP_CONFREQ:

		/* A ConfReq starts negotiation of compression
		 * in one direction of transmission,
		 * and hence brings it करोwn...but which way?
		 *
		 * Remember:
		 * A ConfReq indicates what the sender would like to receive
		 */
		अगर(inbound)
			/* He is proposing what I should send */
			ppp->xstate &= ~SC_COMP_RUN;
		अन्यथा
			/* I am proposing to what he should send */
			ppp->rstate &= ~SC_DECOMP_RUN;

		अवरोध;

	हाल CCP_TERMREQ:
	हाल CCP_TERMACK:
		/*
		 * CCP is going करोwn, both directions of transmission
		 */
		ppp->rstate &= ~SC_DECOMP_RUN;
		ppp->xstate &= ~SC_COMP_RUN;
		अवरोध;

	हाल CCP_CONFACK:
		अगर ((ppp->flags & (SC_CCP_OPEN | SC_CCP_UP)) != SC_CCP_OPEN)
			अवरोध;
		len = CCP_LENGTH(dp);
		अगर (!pskb_may_pull(skb, len + 2))
			वापस;		/* too लघु */
		dp += CCP_HDRLEN;
		len -= CCP_HDRLEN;
		अगर (len < CCP_OPT_MINLEN || len < CCP_OPT_LENGTH(dp))
			अवरोध;
		अगर (inbound) अणु
			/* we will start receiving compressed packets */
			अगर (!ppp->rc_state)
				अवरोध;
			अगर (ppp->rcomp->decomp_init(ppp->rc_state, dp, len,
					ppp->file.index, 0, ppp->mru, ppp->debug)) अणु
				ppp->rstate |= SC_DECOMP_RUN;
				ppp->rstate &= ~(SC_DC_ERROR | SC_DC_FERROR);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* we will soon start sending compressed packets */
			अगर (!ppp->xc_state)
				अवरोध;
			अगर (ppp->xcomp->comp_init(ppp->xc_state, dp, len,
					ppp->file.index, 0, ppp->debug))
				ppp->xstate |= SC_COMP_RUN;
		पूर्ण
		अवरोध;

	हाल CCP_RESETACK:
		/* reset the [de]compressor */
		अगर ((ppp->flags & SC_CCP_UP) == 0)
			अवरोध;
		अगर (inbound) अणु
			अगर (ppp->rc_state && (ppp->rstate & SC_DECOMP_RUN)) अणु
				ppp->rcomp->decomp_reset(ppp->rc_state);
				ppp->rstate &= ~SC_DC_ERROR;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ppp->xc_state && (ppp->xstate & SC_COMP_RUN))
				ppp->xcomp->comp_reset(ppp->xc_state);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/* Free up compression resources. */
अटल व्योम
ppp_ccp_बंदd(काष्ठा ppp *ppp)
अणु
	व्योम *xstate, *rstate;
	काष्ठा compressor *xcomp, *rcomp;

	ppp_lock(ppp);
	ppp->flags &= ~(SC_CCP_OPEN | SC_CCP_UP);
	ppp->xstate = 0;
	xcomp = ppp->xcomp;
	xstate = ppp->xc_state;
	ppp->xc_state = शून्य;
	ppp->rstate = 0;
	rcomp = ppp->rcomp;
	rstate = ppp->rc_state;
	ppp->rc_state = शून्य;
	ppp_unlock(ppp);

	अगर (xstate) अणु
		xcomp->comp_मुक्त(xstate);
		module_put(xcomp->owner);
	पूर्ण
	अगर (rstate) अणु
		rcomp->decomp_मुक्त(rstate);
		module_put(rcomp->owner);
	पूर्ण
पूर्ण

/* List of compressors. */
अटल LIST_HEAD(compressor_list);
अटल DEFINE_SPINLOCK(compressor_list_lock);

काष्ठा compressor_entry अणु
	काष्ठा list_head list;
	काष्ठा compressor *comp;
पूर्ण;

अटल काष्ठा compressor_entry *
find_comp_entry(पूर्णांक proto)
अणु
	काष्ठा compressor_entry *ce;

	list_क्रम_each_entry(ce, &compressor_list, list) अणु
		अगर (ce->comp->compress_proto == proto)
			वापस ce;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Register a compressor */
पूर्णांक
ppp_रेजिस्टर_compressor(काष्ठा compressor *cp)
अणु
	काष्ठा compressor_entry *ce;
	पूर्णांक ret;
	spin_lock(&compressor_list_lock);
	ret = -EEXIST;
	अगर (find_comp_entry(cp->compress_proto))
		जाओ out;
	ret = -ENOMEM;
	ce = kदो_स्मृति(माप(काष्ठा compressor_entry), GFP_ATOMIC);
	अगर (!ce)
		जाओ out;
	ret = 0;
	ce->comp = cp;
	list_add(&ce->list, &compressor_list);
 out:
	spin_unlock(&compressor_list_lock);
	वापस ret;
पूर्ण

/* Unरेजिस्टर a compressor */
व्योम
ppp_unरेजिस्टर_compressor(काष्ठा compressor *cp)
अणु
	काष्ठा compressor_entry *ce;

	spin_lock(&compressor_list_lock);
	ce = find_comp_entry(cp->compress_proto);
	अगर (ce && ce->comp == cp) अणु
		list_del(&ce->list);
		kमुक्त(ce);
	पूर्ण
	spin_unlock(&compressor_list_lock);
पूर्ण

/* Find a compressor. */
अटल काष्ठा compressor *
find_compressor(पूर्णांक type)
अणु
	काष्ठा compressor_entry *ce;
	काष्ठा compressor *cp = शून्य;

	spin_lock(&compressor_list_lock);
	ce = find_comp_entry(type);
	अगर (ce) अणु
		cp = ce->comp;
		अगर (!try_module_get(cp->owner))
			cp = शून्य;
	पूर्ण
	spin_unlock(&compressor_list_lock);
	वापस cp;
पूर्ण

/*
 * Miscelleneous stuff.
 */

अटल व्योम
ppp_get_stats(काष्ठा ppp *ppp, काष्ठा ppp_stats *st)
अणु
	काष्ठा slcompress *vj = ppp->vj;

	स_रखो(st, 0, माप(*st));
	st->p.ppp_ipackets = ppp->stats64.rx_packets;
	st->p.ppp_ierrors = ppp->dev->stats.rx_errors;
	st->p.ppp_ibytes = ppp->stats64.rx_bytes;
	st->p.ppp_opackets = ppp->stats64.tx_packets;
	st->p.ppp_oerrors = ppp->dev->stats.tx_errors;
	st->p.ppp_obytes = ppp->stats64.tx_bytes;
	अगर (!vj)
		वापस;
	st->vj.vjs_packets = vj->sls_o_compressed + vj->sls_o_uncompressed;
	st->vj.vjs_compressed = vj->sls_o_compressed;
	st->vj.vjs_searches = vj->sls_o_searches;
	st->vj.vjs_misses = vj->sls_o_misses;
	st->vj.vjs_errorin = vj->sls_i_error;
	st->vj.vjs_tossed = vj->sls_i_tossed;
	st->vj.vjs_uncompressedin = vj->sls_i_uncompressed;
	st->vj.vjs_compressedin = vj->sls_i_compressed;
पूर्ण

/*
 * Stuff क्रम handling the lists of ppp units and channels
 * and क्रम initialization.
 */

/*
 * Create a new ppp पूर्णांकerface unit.  Fails अगर it can't allocate memory
 * or अगर there is alपढ़ोy a unit with the requested number.
 * unit == -1 means allocate a new number.
 */
अटल पूर्णांक ppp_create_पूर्णांकerface(काष्ठा net *net, काष्ठा file *file, पूर्णांक *unit)
अणु
	काष्ठा ppp_config conf = अणु
		.file = file,
		.unit = *unit,
		.अगरname_is_set = false,
	पूर्ण;
	काष्ठा net_device *dev;
	काष्ठा ppp *ppp;
	पूर्णांक err;

	dev = alloc_netdev(माप(काष्ठा ppp), "", NET_NAME_ENUM, ppp_setup);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण
	dev_net_set(dev, net);
	dev->rtnl_link_ops = &ppp_link_ops;

	rtnl_lock();

	err = ppp_dev_configure(net, dev, &conf);
	अगर (err < 0)
		जाओ err_dev;
	ppp = netdev_priv(dev);
	*unit = ppp->file.index;

	rtnl_unlock();

	वापस 0;

err_dev:
	rtnl_unlock();
	मुक्त_netdev(dev);
err:
	वापस err;
पूर्ण

/*
 * Initialize a ppp_file काष्ठाure.
 */
अटल व्योम
init_ppp_file(काष्ठा ppp_file *pf, पूर्णांक kind)
अणु
	pf->kind = kind;
	skb_queue_head_init(&pf->xq);
	skb_queue_head_init(&pf->rq);
	refcount_set(&pf->refcnt, 1);
	init_रुकोqueue_head(&pf->rरुको);
पूर्ण

/*
 * Free the memory used by a ppp unit.  This is only called once
 * there are no channels connected to the unit and no file काष्ठाs
 * that reference the unit.
 */
अटल व्योम ppp_destroy_पूर्णांकerface(काष्ठा ppp *ppp)
अणु
	atomic_dec(&ppp_unit_count);

	अगर (!ppp->file.dead || ppp->n_channels) अणु
		/* "can't happen" */
		netdev_err(ppp->dev, "ppp: destroying ppp struct %p "
			   "but dead=%d n_channels=%d !\n",
			   ppp, ppp->file.dead, ppp->n_channels);
		वापस;
	पूर्ण

	ppp_ccp_बंदd(ppp);
	अगर (ppp->vj) अणु
		slhc_मुक्त(ppp->vj);
		ppp->vj = शून्य;
	पूर्ण
	skb_queue_purge(&ppp->file.xq);
	skb_queue_purge(&ppp->file.rq);
#अगर_घोषित CONFIG_PPP_MULTILINK
	skb_queue_purge(&ppp->mrq);
#पूर्ण_अगर /* CONFIG_PPP_MULTILINK */
#अगर_घोषित CONFIG_PPP_FILTER
	अगर (ppp->pass_filter) अणु
		bpf_prog_destroy(ppp->pass_filter);
		ppp->pass_filter = शून्य;
	पूर्ण

	अगर (ppp->active_filter) अणु
		bpf_prog_destroy(ppp->active_filter);
		ppp->active_filter = शून्य;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPP_FILTER */

	kमुक्त_skb(ppp->xmit_pending);
	मुक्त_percpu(ppp->xmit_recursion);

	मुक्त_netdev(ppp->dev);
पूर्ण

/*
 * Locate an existing ppp unit.
 * The caller should have locked the all_ppp_mutex.
 */
अटल काष्ठा ppp *
ppp_find_unit(काष्ठा ppp_net *pn, पूर्णांक unit)
अणु
	वापस unit_find(&pn->units_idr, unit);
पूर्ण

/*
 * Locate an existing ppp channel.
 * The caller should have locked the all_channels_lock.
 * First we look in the new_channels list, then in the
 * all_channels list.  If found in the new_channels list,
 * we move it to the all_channels list.  This is क्रम speed
 * when we have a lot of channels in use.
 */
अटल काष्ठा channel *
ppp_find_channel(काष्ठा ppp_net *pn, पूर्णांक unit)
अणु
	काष्ठा channel *pch;

	list_क्रम_each_entry(pch, &pn->new_channels, list) अणु
		अगर (pch->file.index == unit) अणु
			list_move(&pch->list, &pn->all_channels);
			वापस pch;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(pch, &pn->all_channels, list) अणु
		अगर (pch->file.index == unit)
			वापस pch;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Connect a PPP channel to a PPP पूर्णांकerface unit.
 */
अटल पूर्णांक
ppp_connect_channel(काष्ठा channel *pch, पूर्णांक unit)
अणु
	काष्ठा ppp *ppp;
	काष्ठा ppp_net *pn;
	पूर्णांक ret = -ENXIO;
	पूर्णांक hdrlen;

	pn = ppp_pernet(pch->chan_net);

	mutex_lock(&pn->all_ppp_mutex);
	ppp = ppp_find_unit(pn, unit);
	अगर (!ppp)
		जाओ out;
	ग_लिखो_lock_bh(&pch->upl);
	ret = -EINVAL;
	अगर (pch->ppp ||
	    rcu_dereference_रक्षित(pch->bridge, lockdep_is_held(&pch->upl)))
		जाओ outl;

	ppp_lock(ppp);
	spin_lock_bh(&pch->करोwnl);
	अगर (!pch->chan) अणु
		/* Don't connect unरेजिस्टरed channels */
		spin_unlock_bh(&pch->करोwnl);
		ppp_unlock(ppp);
		ret = -ENOTCONN;
		जाओ outl;
	पूर्ण
	spin_unlock_bh(&pch->करोwnl);
	अगर (pch->file.hdrlen > ppp->file.hdrlen)
		ppp->file.hdrlen = pch->file.hdrlen;
	hdrlen = pch->file.hdrlen + 2;	/* क्रम protocol bytes */
	अगर (hdrlen > ppp->dev->hard_header_len)
		ppp->dev->hard_header_len = hdrlen;
	list_add_tail(&pch->clist, &ppp->channels);
	++ppp->n_channels;
	pch->ppp = ppp;
	refcount_inc(&ppp->file.refcnt);
	ppp_unlock(ppp);
	ret = 0;

 outl:
	ग_लिखो_unlock_bh(&pch->upl);
 out:
	mutex_unlock(&pn->all_ppp_mutex);
	वापस ret;
पूर्ण

/*
 * Disconnect a channel from its ppp unit.
 */
अटल पूर्णांक
ppp_disconnect_channel(काष्ठा channel *pch)
अणु
	काष्ठा ppp *ppp;
	पूर्णांक err = -EINVAL;

	ग_लिखो_lock_bh(&pch->upl);
	ppp = pch->ppp;
	pch->ppp = शून्य;
	ग_लिखो_unlock_bh(&pch->upl);
	अगर (ppp) अणु
		/* हटाओ it from the ppp unit's list */
		ppp_lock(ppp);
		list_del(&pch->clist);
		अगर (--ppp->n_channels == 0)
			wake_up_पूर्णांकerruptible(&ppp->file.rरुको);
		ppp_unlock(ppp);
		अगर (refcount_dec_and_test(&ppp->file.refcnt))
			ppp_destroy_पूर्णांकerface(ppp);
		err = 0;
	पूर्ण
	वापस err;
पूर्ण

/*
 * Free up the resources used by a ppp channel.
 */
अटल व्योम ppp_destroy_channel(काष्ठा channel *pch)
अणु
	put_net(pch->chan_net);
	pch->chan_net = शून्य;

	atomic_dec(&channel_count);

	अगर (!pch->file.dead) अणु
		/* "can't happen" */
		pr_err("ppp: destroying undead channel %p !\n", pch);
		वापस;
	पूर्ण
	skb_queue_purge(&pch->file.xq);
	skb_queue_purge(&pch->file.rq);
	kमुक्त(pch);
पूर्ण

अटल व्योम __निकास ppp_cleanup(व्योम)
अणु
	/* should never happen */
	अगर (atomic_पढ़ो(&ppp_unit_count) || atomic_पढ़ो(&channel_count))
		pr_err("PPP: removing module but units remain!\n");
	rtnl_link_unरेजिस्टर(&ppp_link_ops);
	unरेजिस्टर_chrdev(PPP_MAJOR, "ppp");
	device_destroy(ppp_class, MKDEV(PPP_MAJOR, 0));
	class_destroy(ppp_class);
	unरेजिस्टर_pernet_device(&ppp_net_ops);
पूर्ण

/*
 * Units handling. Caller must protect concurrent access
 * by holding all_ppp_mutex
 */

/* associate poपूर्णांकer with specअगरied number */
अटल पूर्णांक unit_set(काष्ठा idr *p, व्योम *ptr, पूर्णांक n)
अणु
	पूर्णांक unit;

	unit = idr_alloc(p, ptr, n, n + 1, GFP_KERNEL);
	अगर (unit == -ENOSPC)
		unit = -EINVAL;
	वापस unit;
पूर्ण

/* get new मुक्त unit number and associate poपूर्णांकer with it */
अटल पूर्णांक unit_get(काष्ठा idr *p, व्योम *ptr)
अणु
	वापस idr_alloc(p, ptr, 0, 0, GFP_KERNEL);
पूर्ण

/* put unit number back to a pool */
अटल व्योम unit_put(काष्ठा idr *p, पूर्णांक n)
अणु
	idr_हटाओ(p, n);
पूर्ण

/* get poपूर्णांकer associated with the number */
अटल व्योम *unit_find(काष्ठा idr *p, पूर्णांक n)
अणु
	वापस idr_find(p, n);
पूर्ण

/* Module/initialization stuff */

module_init(ppp_init);
module_निकास(ppp_cleanup);

EXPORT_SYMBOL(ppp_रेजिस्टर_net_channel);
EXPORT_SYMBOL(ppp_रेजिस्टर_channel);
EXPORT_SYMBOL(ppp_unरेजिस्टर_channel);
EXPORT_SYMBOL(ppp_channel_index);
EXPORT_SYMBOL(ppp_unit_number);
EXPORT_SYMBOL(ppp_dev_name);
EXPORT_SYMBOL(ppp_input);
EXPORT_SYMBOL(ppp_input_error);
EXPORT_SYMBOL(ppp_output_wakeup);
EXPORT_SYMBOL(ppp_रेजिस्टर_compressor);
EXPORT_SYMBOL(ppp_unरेजिस्टर_compressor);
MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV(PPP_MAJOR, 0);
MODULE_ALIAS_RTNL_LINK("ppp");
MODULE_ALIAS("devname:ppp");
