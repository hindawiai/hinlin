<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_CONNLIMIT_H
#घोषणा _XT_CONNLIMIT_H

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>

काष्ठा xt_connlimit_data;

क्रमागत अणु
	XT_CONNLIMIT_INVERT = 1 << 0,
	XT_CONNLIMIT_DADDR  = 1 << 1,
पूर्ण;

काष्ठा xt_connlimit_info अणु
	जोड़ अणु
		जोड़ nf_inet_addr mask;
#अगर_अघोषित __KERNEL__
		जोड़ अणु
			__be32 v4_mask;
			__be32 v6_mask[4];
		पूर्ण;
#पूर्ण_अगर
	पूर्ण;
	अचिन्हित पूर्णांक limit;
	/* revision 1 */
	__u32 flags;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा nf_conncount_data *data __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /* _XT_CONNLIMIT_H */
