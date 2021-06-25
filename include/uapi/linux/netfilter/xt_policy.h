<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_POLICY_H
#घोषणा _XT_POLICY_H

#समावेश <linux/netfilter.h>
#समावेश <linux/types.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

#घोषणा XT_POLICY_MAX_ELEM	4

क्रमागत xt_policy_flags अणु
	XT_POLICY_MATCH_IN	= 0x1,
	XT_POLICY_MATCH_OUT	= 0x2,
	XT_POLICY_MATCH_NONE	= 0x4,
	XT_POLICY_MATCH_STRICT	= 0x8,
पूर्ण;

क्रमागत xt_policy_modes अणु
	XT_POLICY_MODE_TRANSPORT,
	XT_POLICY_MODE_TUNNEL
पूर्ण;

काष्ठा xt_policy_spec अणु
	__u8	saddr:1,
			daddr:1,
			proto:1,
			mode:1,
			spi:1,
			reqid:1;
पूर्ण;

#अगर_अघोषित __KERNEL__
जोड़ xt_policy_addr अणु
	काष्ठा in_addr	a4;
	काष्ठा in6_addr	a6;
पूर्ण;
#पूर्ण_अगर

काष्ठा xt_policy_elem अणु
	जोड़ अणु
#अगर_घोषित __KERNEL__
		काष्ठा अणु
			जोड़ nf_inet_addr saddr;
			जोड़ nf_inet_addr smask;
			जोड़ nf_inet_addr daddr;
			जोड़ nf_inet_addr dmask;
		पूर्ण;
#अन्यथा
		काष्ठा अणु
			जोड़ xt_policy_addr saddr;
			जोड़ xt_policy_addr smask;
			जोड़ xt_policy_addr daddr;
			जोड़ xt_policy_addr dmask;
		पूर्ण;
#पूर्ण_अगर
	पूर्ण;
	__be32			spi;
	__u32		reqid;
	__u8		proto;
	__u8		mode;

	काष्ठा xt_policy_spec	match;
	काष्ठा xt_policy_spec	invert;
पूर्ण;

काष्ठा xt_policy_info अणु
	काष्ठा xt_policy_elem pol[XT_POLICY_MAX_ELEM];
	__u16 flags;
	__u16 len;
पूर्ण;

#पूर्ण_अगर /* _XT_POLICY_H */
