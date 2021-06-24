<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _NFNETLINK_COMPAT_H
#घोषणा _NFNETLINK_COMPAT_H

#समावेश <linux/types.h>

#अगर_अघोषित __KERNEL__
/* Old nfnetlink macros क्रम userspace */

/* nfnetlink groups: Up to 32 maximum */
#घोषणा NF_NETLINK_CONNTRACK_NEW 		0x00000001
#घोषणा NF_NETLINK_CONNTRACK_UPDATE		0x00000002
#घोषणा NF_NETLINK_CONNTRACK_DESTROY		0x00000004
#घोषणा NF_NETLINK_CONNTRACK_EXP_NEW		0x00000008
#घोषणा NF_NETLINK_CONNTRACK_EXP_UPDATE		0x00000010
#घोषणा NF_NETLINK_CONNTRACK_EXP_DESTROY	0x00000020

/* Generic काष्ठाure क्रम encapsulation optional netfilter inक्रमmation.
 * It is reminiscent of sockaddr, but with sa_family replaced
 * with attribute type.
 * ! This should someday be put somewhere generic as now rtnetlink and
 * ! nfnetlink use the same attributes methods. - J. Schulist.
 */

काष्ठा nfattr अणु
	__u16 nfa_len;
	__u16 nfa_type;	/* we use 15 bits क्रम the type, and the highest
				 * bit to indicate whether the payload is nested */
पूर्ण;

/* FIXME: Apart from NFNL_NFA_NESTED shamelessly copy and pasted from
 * rtnetlink.h, it's समय to put this in a generic file */

#घोषणा NFNL_NFA_NEST	0x8000
#घोषणा NFA_TYPE(attr) 	((attr)->nfa_type & 0x7fff)

#घोषणा NFA_ALIGNTO     4
#घोषणा NFA_ALIGN(len)	(((len) + NFA_ALIGNTO - 1) & ~(NFA_ALIGNTO - 1))
#घोषणा NFA_OK(nfa,len)	((len) > 0 && (nfa)->nfa_len >= माप(काष्ठा nfattr) \
	&& (nfa)->nfa_len <= (len))
#घोषणा NFA_NEXT(nfa,attrlen)	((attrlen) -= NFA_ALIGN((nfa)->nfa_len), \
	(काष्ठा nfattr *)(((अक्षर *)(nfa)) + NFA_ALIGN((nfa)->nfa_len)))
#घोषणा NFA_LENGTH(len)	(NFA_ALIGN(माप(काष्ठा nfattr)) + (len))
#घोषणा NFA_SPACE(len)	NFA_ALIGN(NFA_LENGTH(len))
#घोषणा NFA_DATA(nfa)   ((व्योम *)(((अक्षर *)(nfa)) + NFA_LENGTH(0)))
#घोषणा NFA_PAYLOAD(nfa) ((पूर्णांक)((nfa)->nfa_len) - NFA_LENGTH(0))
#घोषणा NFA_NEST(skb, type) \
(अणु	काष्ठा nfattr *__start = (काष्ठा nfattr *)skb_tail_poपूर्णांकer(skb); \
	NFA_PUT(skb, (NFNL_NFA_NEST | type), 0, शून्य); \
	__start;  पूर्ण)
#घोषणा NFA_NEST_END(skb, start) \
(अणु      (start)->nfa_len = skb_tail_poपूर्णांकer(skb) - (अचिन्हित अक्षर *)(start); \
        (skb)->len; पूर्ण)
#घोषणा NFA_NEST_CANCEL(skb, start) \
(अणु      अगर (start) \
                skb_trim(skb, (अचिन्हित अक्षर *) (start) - (skb)->data); \
        -1; पूर्ण)

#घोषणा NFM_NFA(n)      ((काष्ठा nfattr *)(((अक्षर *)(n)) \
        + NLMSG_ALIGN(माप(काष्ठा nfgenmsg))))
#घोषणा NFM_PAYLOAD(n)  NLMSG_PAYLOAD(n, माप(काष्ठा nfgenmsg))

#पूर्ण_अगर /* ! __KERNEL__ */
#पूर्ण_अगर /* _NFNETLINK_COMPAT_H */
