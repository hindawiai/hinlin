<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_TPROXY_H
#घोषणा _XT_TPROXY_H

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>

/* TPROXY target is capable of marking the packet to perक्रमm
 * redirection. We can get rid of that whenever we get support क्रम
 * mutliple tarमाला_लो in the same rule. */
काष्ठा xt_tproxy_target_info अणु
	__u32 mark_mask;
	__u32 mark_value;
	__be32 laddr;
	__be16 lport;
पूर्ण;

काष्ठा xt_tproxy_target_info_v1 अणु
	__u32 mark_mask;
	__u32 mark_value;
	जोड़ nf_inet_addr laddr;
	__be16 lport;
पूर्ण;

#पूर्ण_अगर /* _XT_TPROXY_H */
