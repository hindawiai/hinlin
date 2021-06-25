<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Linux NET3:	Internet Group Management Protocol  [IGMP]
 *
 *	Authors:
 *		Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	Extended to talk the BSD extended IGMP protocol of mrouted 3.6
 */
#अगर_अघोषित _LINUX_IGMP_H
#घोषणा _LINUX_IGMP_H

#समावेश <linux/skbuff.h>
#समावेश <linux/समयr.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/refcount.h>
#समावेश <uapi/linux/igmp.h>

अटल अंतरभूत काष्ठा igmphdr *igmp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा igmphdr *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा igmpv3_report *
			igmpv3_report_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा igmpv3_report *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा igmpv3_query *
			igmpv3_query_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा igmpv3_query *)skb_transport_header(skb);
पूर्ण

काष्ठा ip_sf_socklist अणु
	अचिन्हित पूर्णांक		sl_max;
	अचिन्हित पूर्णांक		sl_count;
	काष्ठा rcu_head		rcu;
	__be32			sl_addr[];
पूर्ण;

#घोषणा IP_SFLSIZE(count)	(माप(काष्ठा ip_sf_socklist) + \
	(count) * माप(__be32))

#घोषणा IP_SFBLOCK	10	/* allocate this many at once */

/* ip_mc_socklist is real list now. Speed is not argument;
   this list never used in fast path code
 */

काष्ठा ip_mc_socklist अणु
	काष्ठा ip_mc_socklist __rcu *next_rcu;
	काष्ठा ip_mreqn		multi;
	अचिन्हित पूर्णांक		sभ_शेषe;		/* MCAST_अणुINCLUDE,EXCLUDEपूर्ण */
	काष्ठा ip_sf_socklist __rcu	*sflist;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा ip_sf_list अणु
	काष्ठा ip_sf_list	*sf_next;
	अचिन्हित दीर्घ		sf_count[2];	/* include/exclude counts */
	__be32			sf_inaddr;
	अचिन्हित अक्षर		sf_gsresp;	/* include in g & s response? */
	अचिन्हित अक्षर		sf_oldin;	/* change state */
	अचिन्हित अक्षर		sf_crcount;	/* retrans. left to send */
पूर्ण;

काष्ठा ip_mc_list अणु
	काष्ठा in_device	*पूर्णांकerface;
	__be32			multiaddr;
	अचिन्हित पूर्णांक		sभ_शेषe;
	काष्ठा ip_sf_list	*sources;
	काष्ठा ip_sf_list	*tomb;
	अचिन्हित दीर्घ		sfcount[2];
	जोड़ अणु
		काष्ठा ip_mc_list *next;
		काष्ठा ip_mc_list __rcu *next_rcu;
	पूर्ण;
	काष्ठा ip_mc_list __rcu *next_hash;
	काष्ठा समयr_list	समयr;
	पूर्णांक			users;
	refcount_t		refcnt;
	spinlock_t		lock;
	अक्षर			पंचांग_running;
	अक्षर			reporter;
	अक्षर			unsolicit_count;
	अक्षर			loaded;
	अचिन्हित अक्षर		gsquery;	/* check source marks? */
	अचिन्हित अक्षर		crcount;
	काष्ठा rcu_head		rcu;
पूर्ण;

/* V3 exponential field decoding */
#घोषणा IGMPV3_MASK(value, nb) ((nb)>=32 ? (value) : ((1<<(nb))-1) & (value))
#घोषणा IGMPV3_EXP(thresh, nbmant, nbexp, value) \
	((value) < (thresh) ? (value) : \
        ((IGMPV3_MASK(value, nbmant) | (1<<(nbmant))) << \
         (IGMPV3_MASK((value) >> (nbmant), nbexp) + (nbexp))))

#घोषणा IGMPV3_QQIC(value) IGMPV3_EXP(0x80, 4, 3, value)
#घोषणा IGMPV3_MRC(value) IGMPV3_EXP(0x80, 4, 3, value)

अटल अंतरभूत पूर्णांक ip_mc_may_pull(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	अगर (skb_transport_offset(skb) + ip_transport_len(skb) < len)
		वापस 0;

	वापस pskb_may_pull(skb, len);
पूर्ण

बाह्य पूर्णांक ip_check_mc_rcu(काष्ठा in_device *dev, __be32 mc_addr, __be32 src_addr, u8 proto);
बाह्य पूर्णांक igmp_rcv(काष्ठा sk_buff *);
बाह्य पूर्णांक ip_mc_join_group(काष्ठा sock *sk, काष्ठा ip_mreqn *imr);
बाह्य पूर्णांक ip_mc_join_group_ssm(काष्ठा sock *sk, काष्ठा ip_mreqn *imr,
				अचिन्हित पूर्णांक mode);
बाह्य पूर्णांक ip_mc_leave_group(काष्ठा sock *sk, काष्ठा ip_mreqn *imr);
बाह्य व्योम ip_mc_drop_socket(काष्ठा sock *sk);
बाह्य पूर्णांक ip_mc_source(पूर्णांक add, पूर्णांक omode, काष्ठा sock *sk,
		काष्ठा ip_mreq_source *mreqs, पूर्णांक अगरindex);
बाह्य पूर्णांक ip_mc_msfilter(काष्ठा sock *sk, काष्ठा ip_msfilter *msf,पूर्णांक अगरindex);
बाह्य पूर्णांक ip_mc_msfget(काष्ठा sock *sk, काष्ठा ip_msfilter *msf,
		काष्ठा ip_msfilter __user *optval, पूर्णांक __user *optlen);
बाह्य पूर्णांक ip_mc_gsfget(काष्ठा sock *sk, काष्ठा group_filter *gsf,
			काष्ठा sockaddr_storage __user *p);
बाह्य पूर्णांक ip_mc_sf_allow(काष्ठा sock *sk, __be32 local, __be32 rmt,
			  पूर्णांक dअगर, पूर्णांक sdअगर);
बाह्य व्योम ip_mc_init_dev(काष्ठा in_device *);
बाह्य व्योम ip_mc_destroy_dev(काष्ठा in_device *);
बाह्य व्योम ip_mc_up(काष्ठा in_device *);
बाह्य व्योम ip_mc_करोwn(काष्ठा in_device *);
बाह्य व्योम ip_mc_unmap(काष्ठा in_device *);
बाह्य व्योम ip_mc_remap(काष्ठा in_device *);
बाह्य व्योम __ip_mc_dec_group(काष्ठा in_device *in_dev, __be32 addr, gfp_t gfp);
अटल अंतरभूत व्योम ip_mc_dec_group(काष्ठा in_device *in_dev, __be32 addr)
अणु
	वापस __ip_mc_dec_group(in_dev, addr, GFP_KERNEL);
पूर्ण
बाह्य व्योम __ip_mc_inc_group(काष्ठा in_device *in_dev, __be32 addr,
			      gfp_t gfp);
बाह्य व्योम ip_mc_inc_group(काष्ठा in_device *in_dev, __be32 addr);
पूर्णांक ip_mc_check_igmp(काष्ठा sk_buff *skb);

#पूर्ण_अगर
